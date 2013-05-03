#include <kernel/gdt.h>

#include <assert.h>
#include <stdio.h>

/* Defined in `arch/x86/boot/gdt.s' */
extern void flush_gdt(u32);

static int gdt_initialised = 0;

/*
 * Pointer to the GDT.
 *
 * See: http://faydoc.tripod.com/cpu/lgdt.htm
 */
static struct {
	u16 limit;         /* The upper 16 bits of all selector limits. */
	u32 base;          /* The address of the first gdt_entry. */
} __attribute__((packed)) gdt_ptr;

/*
 * The Global Descriptor Table (GDT).
 */
static struct sdesc gdt[3];

/*
 * Setup a GDT entry.
 */
static void set_gate(unsigned int index,
		     u32 base,
		     u32 limit,
		     u8 access,
		     u8 granularity)
{
	struct sdesc *seg;

	debug("Segment descriptor [%u] 0x%x, 0x%x, 0x%x, 0x%x",
	      index, base, limit, access, granularity);

	assert(index < n_elements(gdt));

	seg = &gdt[index];

	seg->base_low = (base & 0xFFFF);
	seg->base_middle = (base >> 16) & 0xFF;
	seg->base_high = (base >> 24) & 0xFF;

	seg->limit_low = (limit & 0xFFFF);
	seg->granularity = (limit >> 16) & 0x0F;

	seg->granularity |= granularity & 0xF0;
	seg->access = access;
}

int init_gdt(void *data)
{
	return_val_if_fail(!gdt_initialised, -1);

	gdt_ptr.limit = (sizeof(struct sdesc) * 3) - 1;
	gdt_ptr.base = (u32)&gdt;

	set_gate(0, 0, 0x00000000, 0x00, 0x00); /* Null segment. */
	set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Code segment. */
	set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Data segment. */

	flush_gdt((u32)&gdt_ptr);

	gdt_initialised = 1;

	return 0;
}
