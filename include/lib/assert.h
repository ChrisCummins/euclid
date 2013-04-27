/*
 * Verify program assertion.
 */

#ifndef _ASSERT_H
#define _ASSERT_H

void panic(void);

/* Print an error message and causes a fatal kernel panic if the given
 * expression is false (i.e., evaluates to zero) */
#ifndef NDEBUG
#define assert(exp)				\
	if (unlikely(!(exp))) {			\
		panic();			\
	}
#else /* __OPTIMIZE **/
#define assert(ignore) ((void) 0)
#endif /* __OPTIMIZE__ */

#endif /* _ASSERT_H */
