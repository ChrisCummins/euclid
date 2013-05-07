#include <kernel/idt.h>

#include <kernel/port.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>

/* defined in arch/x86/boot/idt.s */
extern void flush_idt(u32);

#define IDT_SIZE (sizeof(struct idesc) * 256 - 1)
#define IVT_SIZE (sizeof(ihandler) * 256 - 1)

static int idt_initialised = 0;

/*
 * Pointer to the IDT
 */
static struct {
	u16 limit;
	u32 base;       /* the address of the first IDT element */
} __attribute__((packed)) idt_ptr;

/* The Interrupt Descriptor Table (IDT) and Interrupt Vector Tables (IVT) */
static struct idesc idt[256];
static ihandler ivt[256];

static void set_gate (unsigned int index, u32 base, u16 sel, u8 flags)
{
	struct idesc *desc;

	debug("Interrupt descriptor [%u] 0x%x, 0x%x, 0x%x",
	      index, base, sel, flags);

	assert(index < n_elements(idt));

	desc = &idt[index];

	desc->base_lo = base & 0xFFFF;
	desc->base_hi = (base >> 16) & 0xFFFF;

	desc->sel = sel;
	desc->__always0__ = 0;
	desc->flags = flags;
}

int init_idt(void *data)
{
	return_val_if_fail(!idt_initialised, -1);

	/* zero the idt & ivt */
	memset(&idt, 0, IDT_SIZE);
	memset(&ivt, 0, IVT_SIZE);

	/* setup the pointer to the idt */
	idt_ptr.limit = IDT_SIZE;
	idt_ptr.base = (u32)&idt;

	/* When the computer boots, the default interrupt mappings are:
	 *    IRQ 0..7 - INT 0x8..0xF
	 *    IRQ 8..15 - INT 0x70..0x77
	 *
	 * This causes a problem. The master's IRQ mappings (0x8-0xF) conflict
	 * with the interrupt numbers used by the CPU to signal exceptions and
	 * faults. The normal thing to do is to remap the PICs so that IRQs
	 * 0..15 correspond to ISRs 32..47 (31 being the last CPU-used ISR).
	 */
	pic_master_command_out(0x11);
	pic_slave_command_out(0x11);
	pic_master_data_out(0x20);
	pic_slave_data_out(0x28);
	pic_master_data_out(0x04);
	pic_slave_data_out(0x02);
	pic_master_data_out(0x01);
	pic_slave_data_out(0x01);
	pic_master_data_out(0x00);
	pic_slave_data_out(0x00);

	set_gate(0, (u32)isr0, 0x08, 0x8E);
	set_gate(1, (u32)isr1, 0x08, 0x8E);
	set_gate(2, (u32)isr2, 0x08, 0x8E);
	set_gate(3, (u32)isr3, 0x08, 0x8E);
	set_gate(4, (u32)isr4, 0x08, 0x8E);
	set_gate(5, (u32)isr5, 0x08, 0x8E);
	set_gate(6, (u32)isr6, 0x08, 0x8E);
	set_gate(7, (u32)isr7, 0x08, 0x8E);
	set_gate(8, (u32)isr8, 0x08, 0x8E);
	set_gate(9, (u32)isr9, 0x08, 0x8E);
	set_gate(10, (u32)isr10, 0x08, 0x8E);
	set_gate(11, (u32)isr11, 0x08, 0x8E);
	set_gate(12, (u32)isr12, 0x08, 0x8E);
	set_gate(13, (u32)isr13, 0x08, 0x8E);
	set_gate(14, (u32)isr14, 0x08, 0x8E);
	set_gate(15, (u32)isr15, 0x08, 0x8E);
	set_gate(16, (u32)isr16, 0x08, 0x8E);
	set_gate(17, (u32)isr17, 0x08, 0x8E);
	set_gate(18, (u32)isr18, 0x08, 0x8E);
	set_gate(19, (u32)isr19, 0x08, 0x8E);
	set_gate(20, (u32)isr20, 0x08, 0x8E);
	set_gate(21, (u32)isr21, 0x08, 0x8E);
	set_gate(22, (u32)isr22, 0x08, 0x8E);
	set_gate(23, (u32)isr23, 0x08, 0x8E);
	set_gate(24, (u32)isr24, 0x08, 0x8E);
	set_gate(25, (u32)isr25, 0x08, 0x8E);
	set_gate(26, (u32)isr26, 0x08, 0x8E);
	set_gate(27, (u32)isr27, 0x08, 0x8E);
	set_gate(28, (u32)isr28, 0x08, 0x8E);
	set_gate(29, (u32)isr29, 0x08, 0x8E);
	set_gate(30, (u32)isr30, 0x08, 0x8E);
	set_gate(31, (u32)isr31, 0x08, 0x8E);
	set_gate(32, (u32)irq0, 0x08, 0x8E);
	set_gate(33, (u32)irq1, 0x08, 0x8E);
	set_gate(34, (u32)irq2, 0x08, 0x8E);
	set_gate(35, (u32)irq3, 0x08, 0x8E);
	set_gate(36, (u32)irq4, 0x08, 0x8E);
	set_gate(37, (u32)irq5, 0x08, 0x8E);
	set_gate(38, (u32)irq6, 0x08, 0x8E);
	set_gate(39, (u32)irq7, 0x08, 0x8E);
	set_gate(40, (u32)irq8, 0x08, 0x8E);
	set_gate(41, (u32)irq9, 0x08, 0x8E);
	set_gate(42, (u32)irq10, 0x08, 0x8E);
	set_gate(43, (u32)irq11, 0x08, 0x8E);
	set_gate(44, (u32)irq12, 0x08, 0x8E);
	set_gate(45, (u32)irq13, 0x08, 0x8E);
	set_gate(46, (u32)irq14, 0x08, 0x8E);
	set_gate(47, (u32)irq15, 0x08, 0x8E);
	set_gate(255, (u32)isr255, 0x08, 0x8E);

	flush_idt((u32)&idt_ptr);

	idt_initialised = 1;

	return 0;
}

void disaptch_idt_handler(struct r *r);
void disaptch_irq_handler(struct r *r);

void disaptch_idt_handler (struct r *r)
{
	if (likely(ivt[r->int_no]))
		ivt[r->int_no](r);
	else
		panic("Unhandled interrupt: %d", r->int_no);
}

void disaptch_irq_handler (struct r *r)
{
	if (r->int_no >= 40)
		pic_slave_command_out(0x20);

	pic_master_command_out(0x20);

	if (ivt[r->int_no] != 0)
		ivt[r->int_no](r);
}

inline void register_interrupt_handler (u8 index, ihandler handler)
{
	assert(idt_initialised);

	ivt[index] = handler;
}
