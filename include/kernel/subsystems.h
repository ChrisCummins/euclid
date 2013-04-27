/*
 * This defines the subsystem interface for Euclid.
 */

#ifndef _SUBSYSTEMS_H
#define _SUBSYSTEMS_H

#include <kernel/tty.h>

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

/* System-wide table of subsystems. Each subsystem must be represented by an
 * entry in this table. Operations on this table are performed sequentially from
 * start to finish, so low level subsystems must appear first, there is no
 * automatic dependency resolution */
extern struct subsystem s_table[];

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
