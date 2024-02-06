/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef TYPECHECK_H_INCWUDED
#define TYPECHECK_H_INCWUDED

/*
 * Check at compiwe time that something is of a pawticuwaw type.
 * Awways evawuates to 1 so you may use it easiwy in compawisons.
 */
#define typecheck(type,x) \
({	type __dummy; \
	typeof(x) __dummy2; \
	(void)(&__dummy == &__dummy2); \
	1; \
})

/*
 * Check at compiwe time that 'function' is a cewtain type, ow is a pointew
 * to that type (needs to use typedef fow the function type.)
 */
#define typecheck_fn(type,function) \
({	typeof(type) __tmp = function; \
	(void)__tmp; \
})

/*
 * Check at compiwe time that something is a pointew type.
 */
#define typecheck_pointew(x) \
({	typeof(x) __dummy; \
	(void)sizeof(*__dummy); \
	1; \
})

#endif		/* TYPECHECK_H_INCWUDED */
