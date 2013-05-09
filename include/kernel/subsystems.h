/**
 * @file subsystems.h
 *
 * This defines the subsystem interface for Euclid. This adds a very simple
 * infrastructure for supporting a subsystems abstraction. A subsystem
 * represents a single component of the operating system; it does not
 * necessarily directly map to a single device, but rather a subset of common
 * functionality, for example, a tty device, a memory manager, process manager
 * etc.
 */

#ifndef _SUBSYSTEMS_H
#define _SUBSYSTEMS_H

#include <stddef.h>

/**
 * The subsystem object. The subsystem component consists solely of a name, and
 * optionally defines function pointers to perform the initialisation,
 * post-initialisation tests and teardown operations. Additionally a data
 * payload may be assigned. If intialised, this data pointer will be passed as
 * the argument to the subsystem functions. Ommitting any or all of these
 * functions and the payload is not an error.
 *
 * @todo Add a typedef for subsystem functions.
 */
struct subsystem {
	/**
	 * The subsystem name.
	 */
	const char *name;

	/**
	 * The subsystem functions data payload (optional).
	 */
	void *data;

	/**
	 * The subsystem initialisation routine.
	 *
	 * @param data The data payload, or NULL if none is specified.
	 * @return Zero on success, else a non-zero error code.
	 */
	int (*init)(void *data);

	/**
	 * The subsystem test routine. This is called immediately after
	 * initialisation and validates that the subsystem is behaving
	 * correctly.
	 *
	 * @param data The data payload, or NULL if none is specified.
	 * @return Zero on success, else a non-zero error code.
	 */
	int (*test)(void *data);

	/**
	 * The subsystem teardown routine. This performs and deinitialisation
	 * actions.
	 *
	 * @param data The data payload, or NULL if none is specified.
	 * @return Zero on success, else a non-zero error code.
	 */
	int (*teardown)(void *data);
};

/**
 * Get the address of the first subsystem in the s_table. Implementations for
 * this function are architecture specific.
 *
 * @return A pointer to the first subsystem in the s_table.
 */
struct subsystem *s_table_base(void);

/**
 * Return the number of subsystems in the s_table. Implementations for this
 * function are architecture specific.
 *
 * @return the size of the s_table.
 */
int s_table_size(void);

/**
 * Bring up the kernel subsystems. Errors in this early stage of the bootprocess
 * are fatal and unrecoverable, so do as little initialisation as is possible to
 * bring the system into a working state. At this point in the boot process, you
 * cannot rely on the functioning of any other kernel components
 */
void init_subsystems(void);

/**
 * Bring down the kernel subsystems. This iterates backwards through the
 * s_table, tearing down each subsystem sequentially.
 */
void teardown_subsystems(void);

#endif /* _SUBSYSTEMS_H */
