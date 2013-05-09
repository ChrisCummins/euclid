/**
 * @file assert.h
 *
 * Verify program assertion. The <assert.h> header defines the assert() macro.
 * It refers to the macro `NDEBUG` which is not defined in the header. If `NDEBUG`
 * is defined as a macro name before the inclusion of this header, the assert()
 * macro generates no code. The assert() macro shall be redefined according to
 * the current state of `NDEBUG` each time <assert.h> is included.
 */

#ifndef _ASSERT_H
#define _ASSERT_H

#include <kernel/panic.h>

#include <macros.h>

#ifndef NDEBUG

/**
 * Abort the kernel if assertion is false. If the macro `NDEBUG` was defined at
 * the moment <assert.h> was last included, this generates no code, and hence
 * does nothing at all.  Otherwise, this prints an error message and terminates
 * the kernel by calling @ref panic() if expression is false (i.e., compares
 * equal to zero).
 *
 * This is implemented as a macro; if the expression tested has side-effects,
 * program behavior will be different depending on whether `NDEBUG` is
 * defined. This may create Heisenbugs which go away when debugging is turned
 * on.
 */
#define assert(exp)						\
	if (unlikely(!(exp))) {					\
		panic(STRLOC " assertion failed (%s)", #exp);	\
		}

/**
 * Abort the kernel if executed. This is useful for testing invalid code
 * paths. If the macro `NDEBUG` was defined at the moment <assert.h> was last
 * included, this generates no code, and hence does nothing at all.  Otherwise,
 * this prints an error message and terminates the kernel by calling @ref
 * panic().
 */
#define assert_not_reached() panic(STRLOC " assert not reached!")

#else /* NDEBUG */

#define assert(exp)
#define assert_not_reached()

#endif /* NDEBUG */

#endif /* _ASSERT_H */
