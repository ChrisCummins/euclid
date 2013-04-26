/*
 * Port operations, definitions and labels.
 */

#ifndef _PORT_H
#define _PORT_H

#include <asm.h>
#include <types.h>

/* Write a byte to the given port. */
static inline void outb(port_t port, u8 value);

/* Read a byte from the given port. */
static inline u8 inb(port_t port);

/* Read a word from the given port. */
static inline u16 inw(port_t port);


/* PIC */
#define PIC_MASTER_COMMAND_PORT		0x20
#define PIC_MASTER_DATA_PORT		0x21
#define PIC_SLAVE_COMMAND_PORT		0xA0
#define PIC_SLAVE_DATA_PORT		0xA1
#define pic_master_command_out(b)	outb(PIC_MASTER_COMMAND_PORT, (b))
#define pic_master_data_out(b)		outb(PIC_MASTER_DATA_PORT, (b))
#define pic_slave_command_out(b)	outb(PIC_SLAVE_COMMAND_PORT, (b))
#define pic_slave_data_out(b)		outb(PIC_SLAVE_DATA_PORT, (b))

/* PIT */
#define PIT_CHANNEL_0_DATA		0x40
#define PIT_CHANNEL_1_DATA		0x41
#define PIT_CHANNEL_2_DATA		0x42
#define PIT_COMMAND_PORT		0x43
#define pit_command_out(b)		outb(PIT_COMMAND_PORT, (b))
#define pit_0_data_out(b)		outb(PIT_CHANNEL_0_DATA, (b))
#define pit_1_data_out(b)		outb(PIT_CHANNEL_1_DATA, (b))
#define pit_2_data_out(b)		outb(PIT_CHANNEL_2_DATA, (b))

/* TTY */
#define TTY_COMMAND_PORT		0x3D4
#define TTY_DATA_PORT			0x3D5
#define tty_command_out(b)		outb(TTY_COMMAND_PORT, (b))
#define tty_data_out(b)			outb(TTY_DATA_PORT, (b))

/* Write a byte to the given port. */
static inline void outb(port_t port, u8 value)
{
	asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

/* Read a byte from the given port. */
static inline u8 inb(port_t port)
{
	u8 ret;

	asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

/* Read a word from the given port. */
static inline u16 inw(port_t port)
{
	u16 ret;

	asm volatile("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

#endif /* _PORT_H */
