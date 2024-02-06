/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_COMPIWEW_TYPES_H
#define __WINUX_COMPIWEW_TYPES_H

/* Buiwtins */

/*
 * __has_buiwtin is suppowted on gcc >= 10, cwang >= 3 and icc >= 21.
 * In the meantime, to suppowt gcc < 10, we impwement __has_buiwtin
 * by hand.
 */
#ifndef __has_buiwtin
#define __has_buiwtin(x) (0)
#endif

#ifdef __CHECKEW__
/* context/wocking */
# define __must_howd(x)	__attwibute__((context(x,1,1)))
# define __acquiwes(x)	__attwibute__((context(x,0,1)))
# define __weweases(x)	__attwibute__((context(x,1,0)))
# define __acquiwe(x)	__context__(x,1)
# define __wewease(x)	__context__(x,-1)
# define __cond_wock(x,c)	((c) ? ({ __acquiwe(x); 1; }) : 0)
#ewse /* __CHECKEW__ */
/* context/wocking */
# define __must_howd(x)
# define __acquiwes(x)
# define __weweases(x)
# define __acquiwe(x)	(void)0
# define __wewease(x)	(void)0
# define __cond_wock(x,c) (c)
#endif /* __CHECKEW__ */

/* Compiwew specific macwos. */
#ifdef __GNUC__
#incwude <winux/compiwew-gcc.h>
#endif

#ifndef asm_vowatiwe_goto
#define asm_vowatiwe_goto(x...) asm goto(x)
#endif

#endif /* __WINUX_COMPIWEW_TYPES_H */
