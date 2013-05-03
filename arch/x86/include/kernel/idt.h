/*
 * The Interrupt Descriptor Table interface.
 */

#ifndef _IDT_H
#define _IDT_H

#include <types.h>
#include <macros.h>

/* Interrupt descriptor access flag positions */
#define IDT_FLAGS_P_SHIFT     7
#define IDT_FLAGS_DPL_SHIFT   5

/* The interrupts */
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

/*
 * A description of the processor's registers
 */
struct r {
	u32 ds;       /* data segment selector */
	u32 edi;
	u32 esi;
	u32 ebp;
	u32 esp;
	u32 ebx;
	u32 edx;
	u32 ecx;
	u32 eax;      /* pushed by pusha */
	u32 int_no;   /* interrupt number */
	u32 err_code; /* error code */
	u32 eip;
	u32 cs;
	u32 eflags;
	u32 useresp;
	u32 ss;       /* pushed by the processor automatically */
};

__diagnostic_disable(packed)

/*
 * A single element in the IDT
 */
struct idesc {
	u16 base_lo;    /* the lower 16 bits of the address to jump to */
	u16 sel;        /* kernel segment selector */
	u8 __always0__; /* this must always be zero */
	u8 flags;       /* flags */
	u16 base_hi;    /* the upper 16 bits of the address to jump to */
} __attribute__((packed));

__diagnostic_enable(packed)

/*
 * An interrupt handler
 */
typedef void (*ihandler)(struct r *);

/*
 * Register an interrupt handler in the interrupt vector array
 */
void register_interrupt_handler (u8 index, ihandler handler);

/* Setup idt subsystem */
int init_idt(void *data);

/*
 * Defined in arch/x86/boot/idt.s
 */
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);
extern void isr255(void);
extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

#endif /* _IDT_H */
