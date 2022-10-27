/*
  I2C controller driver based on Linux's mv64xxx driver. Originally
  targeted for the Allwinner controllers, but these guts also mostly
  work with Marvell's mv64xxx line of system controller chips. Though
  some things, like the register layout and the interrupt flag
  mapping, need to be changed.

  This driver does not employ interrupts; it busywaits for
  transactions to finish.

  2022, Nick Gordon <nick.gordon@cs.pitt.edu>
 */

#include "i2c.h"

#include <arch/io.h>
#include <lwk/driver.h>
#include <lwk/types.h>
#include <lwk/delay.h>

static void * i2c_phys_base      = 0x01C2B000;
static void * pinctrl_phys_base  = 0x01c20800; /* NMG Todo define according to DTS */
static void * ccu_phys_base      = 0x01c20000; /* NMG Todo define according to DTS */
static int    initialized        = 0;

static struct i2c_fsm i2c;

static inline u32
i2c_make_addr(u32 address)
{
	return (address & 0x7f) << 1;
}

int
i2c_fsm_do_action(struct i2c_fsm * i2c,
                  i2c_action_t     action)
{
	int ret = 0;

	switch (action) {
		case I2C_ACTION_CONTINUE:
		{
			writel(i2c->control_bits.value, i2c->registers.control);
			break;
		}
		/* Unsupported/unused in single-message mode. Send the next message. */
		case I2C_ACTION_SEND_RESTART:
		{
			i2c->msgs        += 1;
			i2c->current_msg  = i2c->msgs;
			i2c->num_msgs    -= 1;
			i2c->send_stop    = (i2c->num_msgs == 1);
			break;
		}
		case I2C_ACTION_SEND_ADDR_1:
		{
			u32 data = 0;

			writeb(i2c->addr,               i2c->registers.data);
			writel(i2c->control_bits.value, i2c->registers.control);
			data = readl(i2c->registers.data);

			break;
		}
		/* We don't support 10-bit addressing so we won't get here. */
		case I2C_ACTION_SEND_ADDR_2:
		{
			writel(i2c->control_bits.value, i2c->registers.control);

			break;
		}
		case I2C_ACTION_SEND_DATA:
		{
			writel(i2c->current_msg->msg[i2c->byte_position], i2c->registers.data);
			i2c->byte_position += 1;
			writel(i2c->control_bits.value,                   i2c->registers.control);

			break;
		}
		case I2C_ACTION_RCV_DATA:
		{
			i2c->current_msg->msg[i2c->byte_position] = readl(i2c->registers.data);
			i2c->byte_position += 1;
			writel(i2c->control_bits.value, i2c->registers.control);

			break;
		}
		case I2C_ACTION_RCV_DATA_STOP:
		{
			i2c->current_msg->msg[i2c->byte_position] = readl(i2c->registers.data);
			i2c->byte_position      += 1;
			i2c->control_bits.m_stp  = 1;

			writel(i2c->control_bits.value, i2c->registers.control);

			i2c->control_bits.m_stp  = 0;
			i2c->block               = 0;
			break;
		}
		case I2C_ACTION_SEND_STOP:
		{
			i2c->control_bits.m_stp = 1;
			writel(i2c->control_bits.value, i2c->registers.control);
			i2c->control_bits.m_stp = 0;
			i2c->block              = 0;

			break;
		}
		case I2C_ACTION_INVALID:
		default:
			printk(KERN_ERR "Tried to do invalid or unknown action %d\n", action);
			break;
	}
	return ret;
}

i2c_action_t
i2c_fsm_change_state(struct i2c_fsm      * i2c, 
                     i2c_device_status_t   device_status)
{
	int ret = 0;

	i2c_state_t oldstate = i2c->state;
	i2c_action_t action  = I2C_ACTION_INVALID;

	switch (device_status) {
		case I2C_DEVICE_STATUS_START:
		case I2C_DEVICE_STATUS_REPEATED_START:
		{
			action	   = I2C_ACTION_SEND_ADDR_1;
			i2c->state = I2C_STATE_WAITING_FOR_ADDR_1_ACK;
			break;
		}
		case I2C_DEVICE_STATUS_ADDR_WRITE_ACK:
		{
			if (0) {
				action	   = I2C_ACTION_SEND_ADDR_2;
				i2c->state = I2C_STATE_WAITING_FOR_ADDR_2_ACK;
				break;
			}
		}
		// fallthrough
		case I2C_DEVICE_STATUS_SECOND_ADDR_WRITE_ACK:
		case I2C_DEVICE_STATUS_DATA_MWRITE_ACK:
		{
			/* Basically, if we have to abort but have already sent some bytes,
			 * we have to first stop, then try again.
			 * 
			 * Or, if we are just done sending data.
			 */
			if (i2c->bytes_left == 0) {
				/* || (i2c->aborting && (i2c->byte_position != 0))) */

				/* Send stop will be always 1, since we don't support sending multiple messages at a time. */
				if (i2c->send_stop) /* || i2c->aborting) */
				{
					action	   = I2C_ACTION_SEND_STOP;
					i2c->state = I2C_STATE_IDLE;
				} else {
					action	   = I2C_ACTION_SEND_RESTART;
					i2c->state = I2C_STATE_WAITING_FOR_RESTART;
				}
			} else {
				/* Simpler case, there's more stuff to send. */
				action	         = I2C_ACTION_SEND_DATA;
				i2c->state       = I2C_STATE_WAITING_FOR_SLAVE_ACK;
				i2c->bytes_left -= 1;
			}
			break;
		}
		case I2C_DEVICE_STATUS_ADDR_READ_ACK:
		{
			/* Don't support 10-bit addressing. */
			if (0) {
			}
		}
		// fallthrough
		case I2C_DEVICE_STATUS_DATA_MRECV_ACK:
		{
			
			if (device_status != I2C_DEVICE_STATUS_DATA_MRECV_ACK) {
				/* We just continue if we are receiving data from the slave. */
				action           = I2C_ACTION_CONTINUE;
			} else {
				/* If we are receiving data from the slave. */
				action           = I2C_ACTION_RCV_DATA;
				i2c->bytes_left -= 1;
			}

			i2c->state = I2C_STATE_WAITING_FOR_SLAVE_DATA;

			
			if (i2c->bytes_left == 1) /* || i2c->aborting) */
			{
				/* Stop acking on the bus. */
				i2c->control_bits.a_ack = 0;
			}

			break;
		}
		case I2C_DEVICE_STATUS_DATA_MRECV_NOACK:
		{
			action	   = I2C_ACTION_RCV_DATA_STOP;
			i2c->state = I2C_STATE_IDLE;
			break;
		}
		case I2C_DEVICE_STATUS_ADDR_WRITE_NOACK:
		case I2C_DEVICE_STATUS_DATA_MWRITE_NOACK:
		case I2C_DEVICE_STATUS_ADDR_READ_NOACK:
		{
			action	   = I2C_ACTION_SEND_STOP;
			i2c->state = I2C_STATE_IDLE;
			ret	   = -1;

			printk(KERN_ERR "Received I2C NACK: %d\n", device_status);
			break;
		}
		case I2C_DEVICE_STATUS_GEN_CALL_ACK:
		case I2C_DEVICE_STATUS_SADDR_DATA_RECV_ACK:
		case I2C_DEVICE_STATUS_GEN_CALL_DATA_RECV_ACK:
		case I2C_DEVICE_STATUS_STOP_REPEATED_START_SLAVE:
		case I2C_DEVICE_STATUS_SADDR_READ_ACK:
		case I2C_DEVICE_STATUS_DATA_SWRITE_ACK:
		case I2C_DEVICE_STATUS_LAST_DATA_SWRITE_ACK:
		case I2C_DEVICE_STATUS_SADDR_WRITE_ACK:
		case I2C_DEVICE_STATUS_MARB_LOST_SADDR_WRITE_ACK:
		case I2C_DEVICE_STATUS_MARB_LOST_GEN_CALL_ACK:
		case I2C_DEVICE_STATUS_MARB_LOST_SADDR_READ_ACK:
		case I2C_DEVICE_STATUS_SADDR_DATA_RECV_NOACK:
		case I2C_DEVICE_STATUS_GEN_CALL_DATA_RECV_NOACK:
		case I2C_DEVICE_STATUS_DATA_SWRITE_NOACK:
		case I2C_DEVICE_STATUS_SECOND_ADDR_WRITE_NOACK:
		case I2C_DEVICE_STATUS_ARB_LOST:
		case I2C_DEVICE_STATUS_BUS_ERR:
		case I2C_DEVICE_STATUS_OTHER:
		default:
			action = I2C_ACTION_SEND_STOP;
			ret    = -1;

			printk(KERN_ERR "Unexpected I2C device state %d\n", device_status);
	}

	// Useful for debugging.
	//printk("STATUS 0x%x CONTROL 0x%x ACTION %d OLD %d NEW %d\n", device_status, *i2c->registers.control, action, oldstate, i2c->state);

	return action;
}

int
i2c_intr(struct i2c_fsm * i2c)
{
	int ret = 0;

	i2c_device_status_t device_status = 0;
	i2c_action_t        action        = 0;

	while (i2c->registers.control->int_flag) {
		device_status = readl(i2c->registers.status);
		action        = i2c_fsm_change_state(i2c, device_status);
		i2c_fsm_do_action(i2c, action);

		i2c->control_bits.int_flag = 1;
		writel(i2c->control_bits.value, i2c->registers.control);
		i2c->control_bits.int_flag = 0;
	}

	return ret;
}

int
i2c_wait(struct i2c_fsm * i2c)
{
	int ret = 0;

	/* Shouldn't really take longer than a second to send any message to a responding device. */
	u32 timeout_msecs = 1000;
	u32 elapsed_msecs = 0;

	/* Core busywait loop */
	while ( (ACCESS_ONCE(i2c->block)) &&
	        (elapsed_msecs < timeout_msecs) ) {

		elapsed_msecs += 10;
		mdelay(10);

		i2c_intr(i2c);
	}

	ret = elapsed_msecs >= timeout_msecs;

	return ret;
}

int
i2c_set_addr(struct i2c_fsm * i2c, 
             struct i2c_msg * msg)
{
	int ret = 0;

	i2c->addr = ( i2c_make_addr(msg->address) | (msg->flags & I2C_M_RD) );

	return ret;
}

int
i2c_send_start(struct i2c_fsm * i2c)
{
	int ret = 0;

	i2c->control_bits.bus_en = 1;
	/* i2c->control_bits.a_ack  = 1; */
	i2c->control_bits.m_sta  = 1;

	writel(i2c->control_bits.value, i2c->registers.control);

	i2c->control_bits.m_sta = 0;

	return ret;
}


int
i2c_execute_msg(struct i2c_fsm * i2c, 
                struct i2c_msg * msg)
{
	int ret = 0;

	i2c->current_msg   = msg;
	i2c->num_msgs	   = 1;
	i2c->block	   = 1;
	i2c->state	   = I2C_STATE_WAITING_FOR_START_COND;
	i2c->byte_position = 0;
	i2c->bytes_left	   = msg->length;

	i2c->send_stop     = 1; /* Only support sending one message at a time. */

	i2c_send_start(i2c);

	i2c_set_addr(i2c, msg);

	/* Break out of this once i2c->block goes back to zero. Then we are done. */
	i2c_wait(i2c);

	return ret;
}

int
i2c_send_msg(struct i2c_fsm * i2c, 
             struct i2c_msg * msg)
{
	int ret = 0;

	i2c_execute_msg(i2c, msg);

	return ret;
}

int
i2c_init(void)
{
	void * i2c_virt_base = 0;

	if (initialized) {
		printk(KERN_ERR "I2C driver already initialized.\n");
		return -1;
	}

	printk("Initializing Allwinner I2C driver\n");
	initialized = 1;

	/* IOREMAP a bunch of stuff to make the I2C work */
	{
		static void * pinctrl_virt_base  = 0;
		static void * ccu_virt_base      = 0;

		i2c_virt_base     = (void *)ioremap_nocache(i2c_phys_base,     1024);
		pinctrl_virt_base = (void *)ioremap_nocache(pinctrl_phys_base, 1024);
		ccu_virt_base     = (void *)ioremap_nocache(ccu_phys_base,     1024);

		/* Do CCU enabling stuff that should be done elsewhere. */
		{
			u32 * bus_rst_reg4  = ccu_virt_base + 0x2D8;
			u32 * bus_gate_reg3 = ccu_virt_base + 0x6C;

			writel(0x30003, bus_rst_reg4);
			writel(0x30003, bus_gate_reg3);
		}

		/* Do pincontrol enabling stuff that should be done elsewhere. */
		{
			u32 * phconf_0 = pinctrl_virt_base + 0xFC;

			writel(0x22222222, phconf_0);
		}
	}

	memset(&i2c, 0, sizeof(struct i2c_fsm));

	i2c.registers.control = i2c_virt_base + I2C_CNTR;
	i2c.registers.status  = i2c_virt_base + I2C_STAT;
	i2c.registers.clock   = i2c_virt_base + I2C_CCR;
	i2c.registers.data    = i2c_virt_base + I2C_DATA;
	i2c.registers.addr    = i2c_virt_base + I2C_ADDR;
	i2c.registers.xaddr   = i2c_virt_base + I2C_XADDR;
	i2c.registers.reset   = i2c_virt_base + I2C_SRST;

	writel(0, i2c.registers.addr);
	writel(0, i2c.registers.xaddr);
	writel(0, i2c.registers.reset);

	i2c.registers.clock->clk_n = 2; // or should this be 1???
	i2c.registers.clock->clk_m = 11;

	i2c.control_bits.bus_en    = 1;
	i2c.control_bits.m_stp     = 1;

	writel(i2c.control_bits.value, i2c.registers.control);

	i2c.control_bits.m_stp     = 0;
	i2c.control_bits.bus_en    = 1;
	i2c.control_bits.a_ack     = 1; /* According to mv64xxx driver this should not be set if driver is idle? */

	return 0;
}

DRIVER_INIT("module", i2c_init);

DRIVER_PARAM(i2c_phys_base,     ulong);
DRIVER_PARAM(pinctrl_phys_base, ulong);
DRIVER_PARAM(ccu_phys_base,     ulong);
