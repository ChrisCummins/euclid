/*
 * This defines the subsystem interface for Euclid.
 */

#ifndef _SUBSYSTEMS_H
#define _SUBSYSTEMS_H

#include <stddef.h>

/* The subsystem object */
struct subsystem {
	const char *name;
	void *data;

	/* functions */
	int (*init)(void *data);
	int (*test)(void *data);
	int (*teardown)(void *data);
};

/* Return the address of the first segment descriptor in the s_table */
struct subsystem *s_table_base(void);

/* Return the number of segment descriptors in the s_table */
int s_table_size(void);

/* Bring up the kernel subsystems. Errors in this early stage of the bootprocess
 * are fatal and unrecoverable, so do as little initialisation as is possible to
 * bring the system into a working state. At this point in the boot process, you
 * cannot rely on the functioning of any other kernel components
 */
void init_subsystems(void);

/* Bring down the kernel subsystems. This iterates backwards through the
 * s_table, tearing down each subsystem sequentially.
 */
void teardown_subsystems(void);

#endif /* _SUBSYSTEMS_H */
