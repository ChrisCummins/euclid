/*
 * Verify program assertion.
 */

#ifndef _ASSERT_H
#define _ASSERT_H

#include <kernel/panic.h>

#include <macros.h>

#ifndef NDEBUG

/* Print an error message and causes a fatal kernel panic if the given
 * expression is false (i.e., evaluates to zero)
 */
#define assert(exp)						\
	if (unlikely(!(exp))) {					\
		panic(STRLOC " assertion failed (%s)", #exp);	\
		}

/* Print an error message and cause a fatal kernel panic if this code is ever
 * evaluated
 */
#define assert_not_reached() panic(STRLOC " assert not reached!")

#else /* NDEBUG */

#define assert(exp)
#define assert_not_reached()

#endif /* NDEBUG */

#endif /* _ASSERT_H */
