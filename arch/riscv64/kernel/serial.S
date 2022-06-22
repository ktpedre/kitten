// TODO Brian Needs to have a better location
#define UART_PHYS_ADDR _AC(CONFIG_SERIAL_PHYS,u)
/*#define UART_PHYS_ADDR _AC(0x1C021000,u)*/
#define UART_VIRT_ADDR _AC(0xffffffbffbc15040,ull)

  /* JRL: Note this is an infinite loop that doesn't do anything */
.macro serial_write, tmp64, tmp32, num
	// wait
	1:
		ldr \tmp64, =UART_PHYS_ADDR
		// read LSR
		ldrb \tmp32, [\tmp64, #0x14]
		and \tmp32, \tmp32, #0x20
		cmp \tmp32, #0
	beq 1b

	lsr \tmp64, \num, #4
	// num / 16 (2^4) right shift by 4
.endm

.macro wait_for_xmit, port
#ifndef CONFIG_ARCH_QEMU
1001:
    ldrb w17, [\port, #0x14]
    and w17, w17, #0x20
    cmp w17, #0
    beq 1001b
#endif
.endm

.macro _serial_write_bytes port, val, more:vararg
    ldr x14, =\port

    wait_for_xmit x14


    ldr x15, =\val
    str x15, [x14]

    .ifnb \more
    _serial_write_bytes \port, \more
    .endif


.endm


.macro serial_write_bytes, byte, args:vararg
    _serial_write_bytes UART_PHYS_ADDR, \byte, \args
.endm

.macro vserial_write_bytes, byte, args:vararg
    _serial_write_bytes UART_VIRT_ADDR, \byte, \args
.endm


.macro _serial_write_str, port:req, byte:req, more:vararg
    _serial_write_bytes \port, \byte, \more

    ldr x14, =\port

    wait_for_xmit x14
    ldr x15, =0x0d
    str x15, [x14]

    wait_for_xmit x14
    ldr x15, =0x0a
    str x15, [x14]

.endm

.macro serial_write_str, byte, args:vararg  
    _serial_write_str UART_PHYS_ADDR, \byte, \args
.endm

.macro vserial_write_str, byte, args:vararg  
    _serial_write_str UART_VIRT_ADDR, \byte, \args
.endm

.macro _serial_write_reg, port, reg
    ldr x14, =\port
    ldr x11, =64
    mov x15, \reg

1000:
    sub x11, x11, 4

    mov x15, \reg
    lsr x15, x15, x11
    and x15, x15, 0xf


    cmp x15, #9
    bgt 2000f

    add x15, x15, #48
    b 3000f
2000:
    add x15, x15,  #55
3000:

    wait_for_xmit x14
    str x15, [x14]

    cmp x11, #0
    bne 1000b

    wait_for_xmit x14
    ldr x15, =0x0d
    str x15, [x14]

    wait_for_xmit x14
    ldr x15, =0x0a
    str x15, [x14]

.endm

.macro serial_write_reg reg
    _serial_write_reg UART_PHYS_ADDR, \reg
.endm

.macro vserial_write_reg reg
    _serial_write_reg UART_VIRT_ADDR, \reg
.endm
