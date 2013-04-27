/*
 * Verify program assertion.
 */

#ifndef _ASSERT_H
#define _ASSERT_H

void panic(void);

/* Print an error message and causes a fatal kernel panic if the given
 * expression is false (i.e., evaluates to zero)
 */
#ifndef NDEBUG
#define assert(exp)				\
	if (unlikely(!(exp))) {			\
		panic();			\
	}
#else /* NDEBUG */
#define assert(exp)
#endif /* NDEBUG */

#endif /* _ASSERT_H */
