/**
 * @file macros.h
 *
 * Common macros definitions
 *
 * This file must not include any other header files, as many will rely on it.
 */

#ifndef _MACROS_H
#define _MACROS_H

/**
 * Provide a means to test if a character is a digit.
 */
#define is_digit(c) ((c) >= '0' && (c) <= '9')

/**
 * Stringify (works on strings and macros).
 */
#define __stringify(x)	___stringify(x)

/**
 * Internal stringification.
 */
#define ___stringify(x) #x

/**
 * Concatenate two strings.
 */
#define __concat(x, y)	__stringify(x ## y)

/*
 * Redefine the keywords disabled by -std option.
 *
 *   See: http://gcc.gnu.org/onlinedocs/gcc-4.3.4/gcc/Alternate-Keywords.html
 */
#ifdef __GNUC__
/**
 * Re-enables disabled keyword. See <a
 href="http://gcc.gnu.org/onlinedocs/gcc-4.3.4/gcc/Alternate-Keywords.html"
 target="_blank">Alternate Keywords (GCC Manual)</a> for more information.
 */
#define asm		__asm__

/**
 * Re-enables disabled keyword. See <a
 href="http://gcc.gnu.org/onlinedocs/gcc-4.3.4/gcc/Alternate-Keywords.html"
 target="_blank">Alternate Keywords (GCC Manual)</a> for more information.
 */
#define inline		__inline__

/**
 * Re-enables disabled keyword. See <a
 href="http://gcc.gnu.org/onlinedocs/gcc-4.3.4/gcc/Alternate-Keywords.html"
 target="_blank">Alternate Keywords (GCC Manual)</a> for more information.
 */
#define typeof		__typeof__
#endif /* __GNUC__ */

#if defined(__GNUC__) && (__GNUC__ > 2) && defined(NDEBUG)

/**
 * Cast any true-false expression to boolean.
 */
#define __boolean_expression(x)			\
	({ int __boolean;			\
	   if (x)				\
		   __boolean = 1;		\
	   else					\
		   __boolean = 0;		\
	   __boolean; })

/**
 * Optimise for true branch.
 */
#define likely(x) __builtin_expect(__boolean_expression(x), 1)

/**
 * Optimise for false branch.
 */
#define unlikely(x) __builtin_expect(__boolean_expression(x), 0)

#else /* not GNUC */

/**
 * Optimise for true branch.
 */
#define likely(x) (x)

/**
 * Optimise for false branch.
 */
#define unlikely(x) (x)

#endif /* __GNUC__ */

/**
 * Test if an address is within a given region of memory.
 */
#define __is_in_region(addr, base, end)			\
	(((addr) >= (base)) && ((addr) <= (end)))

#ifndef NDEBUG

/**
 * Provide means for early exiting of a function if an expression is false.
 */
#define return_if_fail(x)						\
	if (unlikely(!(x))) {						\
		printf(STRLOC " return_if_fail(" #x ")");		\
		return;							\
	}

/**
 * Provide means for early exiting of a function if an expression is false.
 */
#define return_val_if_fail(x, val)					\
	if (unlikely(!(x))) {						\
		printf(STRLOC " return_val_if_fail(" #x ", " #val")");	\
		return (val);						\
	}
#else

#define return_if_fail(x)
#define return_val_if_fail(x, val)

#endif /* __OPTIMIZE__ */


#ifndef __GNUC__
/**
 * Protect against compiling without GCC
 */
#define __attribute__
#endif

/* Diagnostic pragmas.
 *
 * This provides the various macros for enabling and disabling warnings,
 * printing messages and other compile-time activities. These should not be used
 * without good cause and care should be made to ensure that each disabling of a
 * warning is a matched with an enable for the same warning after use.
 *
 * Note that these cannot be used to disable errors. Compiler errors should be
 * resolved, not ignored.
 *
 * For more on pragmas, see here:
 *     http://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html
 */
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)

/**
 * Perform a pragma.
 */
#define __do_pragma(x)			_Pragma (#x)

/**
 * Perform a diagnostic pragma.
 */
#define __diagnostic_pragma(x)		__do_pragma(GCC diagnostic x)

/**
 * Perform a message pragma.
 */
#define __message_pragma(x)		__do_pragma(message __stringify(x))

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)

/**
 * Disable a diagnostic warning.
 */
#define __diagnostic_disable(x)				\
	__diagnostic_pragma(push)			\
	__diagnostic_pragma(ignored __concat(-W,x))

/**
 * Enable a diagnostic warning.
 */
#define __diagnostic_enable(x)		__diagnostic_pragma(pop)

/**
 * Send a build message.
 */
#define __build_message(x)		__message_pragma(x)

/**
 * Send a build warning.
 */
#define __build_warning(x)		__message_pragma(WARNING: x)

#else /* 4.2 < GCC version > 4.2 */

#define __diagnostic_disable(x)				\
	__diagnostic_pragma(ignored __concat(-W,x))
#define __diagnostic_enable(x)				\
	__diagnostic_pragma(warning __concat(-W,x))
#define __build_message(x)		__message_pragma(x)
#define __build_warning(x)		__message_pragma(WARNING: x)

#endif

#else /* GCC version < 4.2, or undefined */

#define __do_pragma(x)
#define __diagnostic_disable(x)
#define __diagnostic_enable(x)
#define __build_message(x)
#define __build_warning(x)

#endif /* __GNUC__ */

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
/**
 * Provide a means for warning when a function's result is unused.
 */
#define __warn_unused_result __attribute__((warn_unused_result))
#else
#define __warn_unused_result
#endif

#ifdef __GNUC__
/**
 * Provides a string identifying the current function.
 */
#define STRFUNC		((const char*)(__PRETTY_FUNCTION__))
#elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 19901L
#define STRFUNC		((const char*)(__func__))
#elif defined(_MSC_VER) && (_MSC_VER > 1300)
#define STRFUNC		((const char*)(__FUNCTION__))
#else
#define STRFUNC		((const char*)("???"))
#endif /* __GNUC__ */

#if defined (__GNUC__) && (__GNUC__ < 3)
#define STRLOC								\
	__FILE__ ":" __stringify(__LINE__) ":" __PRETTY_FUNCTION__ "()"
#else
/**
 * Provides a string identifying the current code position.
 */
#define STRLOC		__FILE__ ":" __stringify(__LINE__)
#endif /* __GNUC__ */

#ifndef FALSE
/**
 * Provide boolean false value
 */
#define FALSE (0)
#endif

#ifndef TRUE
/**
 * Provide boolean true value
 */
#define TRUE (!FALSE)
#endif

/**
 * Return the maximum of two values.
 */
#define max(x,y)	(((x) > (y)) ? (x) : (y))

/**
 * Return the minimum of two values.
 */
#define min(x,y)	(((x) < (y)) ? (x) : (y))

/**
 * Return the absolute size of a value.
 */
#define abs(x)		(((x) < 0) ? -(x) : (x))

/**
 * Clamp a value in a bounded range.
 */
#define clamp(x, min, max) (((x) > (max)) ? (max) : (((x) < (min))	\
						     ? (min) : (x)))

/**
 * Count the number of elements in a fixed-size array.
 */
#define n_elements(a) (sizeof(a) / sizeof((a)[0]))

/**
 * Provides a way to round a non-negative integer up to the next multiple of
 * sizeof(int). For example, sizeof(short) is 2, but _INTSIZEOF(short) is 4.
 */
#define _INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))

#endif /* _MACROS_H */
