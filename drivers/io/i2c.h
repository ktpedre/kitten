#ifndef _DRIVERS_IO_I2C_H
#define _DRIVERS_IO_I2C_H

#include <lwk/types.h>

/*
   Directly from the PINE64 manual regarding TWI/2WIRE (read: I2C):

   There are four operation modes on the TWI bus which dictates the
   communications method. They are Master Transmit, Master Receive,
   Slave Transmit and Slave Receive. In general, CPU host controls TWI
   by writing commands and data to its registers. The TWI interrupts
   the CPU host for the attention each time a byte transfer is done or
   a START/STOP conditions is detected. The CPU host can also poll the
   status register for current status if the interrupt mechanism is
   not disabled by the CPU host.

   When the CPU host wants to start a bus transfer, it initiates a bus
   START to enter the master mode by setting IM_STA bit in the
   2WIRE_CNTR register to high (before it must be low). The TWI will
   assert INT line and INT_FLAG to indicate a completion for the START
   condition and each consequent byte transfer. At each interrupt, the
   micro-processor needs to check the 2WIRE_STAT register for current
   status. A transfer has to be concluded with STOP condition by
   setting M_STP bit high.

   In Slave Mode, the TWI also constantly samples the bus and look for
   its own slave address during addressing cycles. Once a match is
   found, it is addressed and interruptted the CPU host with the
   corresponding status. Upon request, the CPU host should read the
   status, read/write 2WIRE_DATA data register, and set the 2WIRE_CNTR
   control register. After each byte transfer, a slave device always
   halt the operation of remote master by holding the next low pulse
   on SCL line until the microprocessor responds to the status of
   previous byte transfer or START condition.
 */

/* TWI register offsets */
#define I2C_ADDR	0x0  /* Slave Address */
#define I2C_XADDR	0x4  /* Extended slave address */
#define I2C_DATA	0x8  /* Data byte */
#define I2C_CNTR	0xC  /* Control */
#define I2C_STAT	0x10 /* Status */
#define I2C_CCR		0x14 /* Clock control */
#define I2C_SRST	0x18 /* Software reset */
#define I2C_EFR		0x1C /* Enhance feature */
#define I2C_LCR		0x20 /* Line control */

struct i2c_control_register {
	union {
		u32 value;
		struct {
			u32 rsvd1     : 2;
			u32 a_ack     : 1;
			u32 int_flag  : 1;
			u32 m_stp     : 1;
			u32 m_sta     : 1;
			u32 bus_en    : 1;
			u32 int_en    : 1;
			u32 rsvd2     : 24;
		};
	};
} __attribute__((packed));


/*
  Code Status
  0x00: Bus error
  0x08: START condition transmitted
  0x10: Repeated START condition transmitted
  0x18: Address + Write bit transmitted, ACK received
  0x20: Address + Write bit transmitted, ACK not received
  0x28: Data byte transmitted in master mode, ACK received
  0x30: Data byte transmitted in master mode, ACK not received
  0x38: Arbitration lost in address or data byte
  0x40: Address + Read bit transmitted, ACK received
  0x48: Address + Read bit transmitted, ACK not received
  0x50: Data byte received in master mode, ACK transmitted
  0x58: Data byte received in master mode, not ACK transmitted
  0x60: Slave address + Write bit received, ACK transmitted
  0x68: Arbitration lost in address as master, slave address + Write bit
        received, ACK transmitted
  0x70: General Call address received, ACK transmitted
  0x78: Arbitration lost in address as master, General Call address received,
        ACK transmitted
  0x80: Data byte received after slave address received, ACK transmitted
  0x88: Data byte received after slave address received, not ACK
        transmitted
  0x90: Data byte received after General Call received, ACK transmitted
  0x98: Data byte received after General Call received, not ACK transmitted
  0xA0: STOP or repeated START condition received in slave mode
  0xA8: Slave address + Read bit received, ACK transmitted
  0xB0: Arbitration lost in address as master, slave address + Read bit
        received, ACK transmitted
  0xB8: Data byte transmitted in slave mode, ACK received
  0xC0: Data byte transmitted in slave mode, ACK not received
  0xC8: Last byte transmitted in slave mode, ACK received
  0xD0: Second Address byte + Write bit transmitted, ACK received
  0xD8: Second Address byte + Write bit transmitted, ACK not received
  0xF8: No relevant status information, INT_FLAG=0
*/

/* I2C Status register codes */
typedef enum  {
	I2C_DEVICE_STATUS_BUS_ERR		    = 0X0,
	I2C_DEVICE_STATUS_START			    = 0X8,
	I2C_DEVICE_STATUS_REPEATED_START	    = 0X10,
	I2C_DEVICE_STATUS_ADDR_WRITE_ACK	    = 0X18,
	I2C_DEVICE_STATUS_ADDR_WRITE_NOACK	    = 0X20,
	I2C_DEVICE_STATUS_DATA_MWRITE_ACK	    = 0X28,
	I2C_DEVICE_STATUS_DATA_MWRITE_NOACK	    = 0X30,
	I2C_DEVICE_STATUS_ARB_LOST		    = 0X38,
	I2C_DEVICE_STATUS_ADDR_READ_ACK		    = 0X40,
	I2C_DEVICE_STATUS_ADDR_READ_NOACK	    = 0X48,
	I2C_DEVICE_STATUS_DATA_MRECV_ACK	    = 0X50,
	I2C_DEVICE_STATUS_DATA_MRECV_NOACK	    = 0X58,
	I2C_DEVICE_STATUS_SADDR_WRITE_ACK	    = 0X60,
	I2C_DEVICE_STATUS_MARB_LOST_SADDR_WRITE_ACK = 0X68,
	I2C_DEVICE_STATUS_GEN_CALL_ACK		    = 0X70,
	I2C_DEVICE_STATUS_MARB_LOST_GEN_CALL_ACK    = 0X78,
	I2C_DEVICE_STATUS_SADDR_DATA_RECV_ACK	    = 0X80,
	I2C_DEVICE_STATUS_SADDR_DATA_RECV_NOACK	    = 0X88,
	I2C_DEVICE_STATUS_GEN_CALL_DATA_RECV_ACK    = 0X90,
	I2C_DEVICE_STATUS_GEN_CALL_DATA_RECV_NOACK  = 0X98,
	I2C_DEVICE_STATUS_STOP_REPEATED_START_SLAVE = 0XA0,
	I2C_DEVICE_STATUS_SADDR_READ_ACK	    = 0XA8,
	I2C_DEVICE_STATUS_MARB_LOST_SADDR_READ_ACK  = 0XB0,
	I2C_DEVICE_STATUS_DATA_SWRITE_ACK	    = 0XB8,
	I2C_DEVICE_STATUS_DATA_SWRITE_NOACK	    = 0XC0,
	I2C_DEVICE_STATUS_LAST_DATA_SWRITE_ACK	    = 0XC8,
	I2C_DEVICE_STATUS_SECOND_ADDR_WRITE_ACK	    = 0XD0,
	I2C_DEVICE_STATUS_SECOND_ADDR_WRITE_NOACK   = 0XD8,
	I2C_DEVICE_STATUS_OTHER			    = 0XF8,

} i2c_device_status_t;

struct i2c_status_register {
	union {
		u32 value;
		struct {
			u32 sta  : 8;
			u32 rsvd : 24;
		};
	};
} __attribute__((packed));

struct i2c_slave_address_register {
	union {
		u32 value;
		struct {
			u32 gce     : 1;
			u32 address : 7;
			u32 rsvd    : 24;
		};
	};
} __attribute__((packed));

struct i2c_clock_register {
	union {
		u32 value;
		struct {
			u32 clk_n : 3;
			u32 clk_m : 4;
			u32 rsvd  : 25;
		};
	};
} __attribute__((packed));

struct i2c_lcr_register {
	union {
		u32 value;
		struct {
			u32 sda_ctl_en : 1;
			u32 sda_ctl    : 1;
			u32 scl_ctl_en : 1;
			u32 scl_ctl    : 1;
			u32 sda_state  : 1;
			u32 scl_state  : 1;
			u32 rsvd       : 26;
		};
	};
} __attribute__((packed));

struct i2c_dvfs_register {
	union {
		u32 value;
		struct {
			u32 dvfc_busy_set : 1;
			u32 cpu_busy_set  : 1;
			u32 ms_priority   : 1;
			u32 rsvd          : 29;
		};
	};
} __attribute__((packed));

typedef enum {
	I2C_STATE_INVALID                 = 1,
	I2C_STATE_IDLE                    = 2,
	I2C_STATE_WAITING_FOR_START_COND  = 3,
	I2C_STATE_WAITING_FOR_RESTART     = 4,
	I2C_STATE_WAITING_FOR_ADDR_1_ACK  = 5,
	I2C_STATE_WAITING_FOR_ADDR_2_ACK  = 6,
	I2C_STATE_WAITING_FOR_SLAVE_ACK   = 7,
	I2C_STATE_WAITING_FOR_SLAVE_DATA  = 8,
} i2c_state_t;

typedef enum {
	I2C_ACTION_INVALID                = 1,
	I2C_ACTION_CONTINUE               = 2,
	I2C_ACTION_SEND_RESTART           = 3,
	I2C_ACTION_SEND_ADDR_1            = 4,
	I2C_ACTION_SEND_ADDR_2            = 5,
	I2C_ACTION_SEND_DATA              = 6,
	I2C_ACTION_RCV_DATA               = 7,
	I2C_ACTION_RCV_DATA_STOP          = 8,
	I2C_ACTION_SEND_STOP              = 9,
} i2c_action_t;

#define I2C_BUFLEN 128

struct i2c_msg {
	u32 address;
	u16 length;
	u16 flags;
#define I2C_M_RD 0x0001 /* read data, from slave to master */
	u8  msg[I2C_BUFLEN];
};

struct i2c_fsm {
	struct i2c_msg * current_msg;
	struct i2c_msg * msgs;
	u32		 num_msgs;

	/* We don't support 10-bit addresses. */
	u32 addr;

	i2c_state_t  state;
	i2c_action_t action;

	struct i2c_control_register control_bits;

	u32 block; // Used to break the loop when we are done
	u32 send_stop;

	u32 bytes_left;
	u32 byte_position;

	struct {
		struct i2c_control_register * control;
		u32                         * data;
		struct i2c_status_register  * status;
		struct i2c_clock_register   * clock;
		u32                         * addr;
		u32                         * xaddr;
		u32                         * reset;
	} registers;
};

#endif /* _DRIVERS_IO_I2C_H */
