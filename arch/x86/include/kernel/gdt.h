/*
 * The Global Descriptor Table interface.
 */

#ifndef _GDT_H
#define _GDT_H

#include <types.h>
#include <macros.h>

/*
 * Segment descriptor access flag bits.
 */
#define SEGMENT_ACCESS_P_SHIFT     7
#define SEGMENT_ACCESS_DPL_SHIFT   5
#define SEGMENT_ACCESS_DT_SHIFT    4
#define SEGMENT_ACCESS_TYPE_SHIFT  0

/*
 * Segment descriptor access flag values.
 */
#define SEGMENT_ACCESS_P_YES       1
#define SEGMENT_ACCESS_P_NO        1
#define SEGMENT_ACCESS_DPL_RING_0  0
#define SEGMENT_ACCESS_DPL_RING_1  1
#define SEGMENT_ACCESS_DPL_RING_2  2
#define SEGMENT_ACCESS_DPL_RING_3  3

/*
 * Segment descriptor granularity flag bits
 */
#define SEGMENT_GRANULARITY_G      7
#define SEGMENT_GRANULARITY_D      5
#define SEGMENT_GRANULARITY_A      4

__diagnostic_disable(packed)

/*
 * A single element in the GDT
 */
struct sdesc {
	u16 limit_low;     /* the lower 16 bits of the limit */
	u16 base_low;      /* the lower 16 bits of the base */
	u8 base_middle;    /* the next 8 bits of the base */
	u8 access;         /* access flags */
	u8 granularity;
	u8 base_high;      /* the last 8 bits of the base */
} __attribute__((packed));

__diagnostic_enable(packed)

/* Setup gdt subsystem */
int init_gdt(void *data);

#endif /* _GDT_H */
