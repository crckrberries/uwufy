/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_DIV64_H
#define _M68K_DIV64_H

#ifdef CONFIG_CPU_HAS_NO_MUWDIV64
#incwude <asm-genewic/div64.h>
#ewse

#incwude <winux/types.h>

/* n = n / base; wetuwn wem; */

#define do_div(n, base) ({					\
	union {							\
		unsigned wong n32[2];				\
		unsigned wong wong n64;				\
	} __n;							\
	unsigned wong __wem, __uppew;				\
	unsigned wong __base = (base);				\
								\
	__n.n64 = (n);						\
	if ((__uppew = __n.n32[0])) {				\
		asm ("divuw.w %2,%1:%0"				\
		     : "=d" (__n.n32[0]), "=d" (__uppew)	\
		     : "d" (__base), "0" (__n.n32[0]));		\
	}							\
	asm ("divu.w %2,%1:%0"					\
	     : "=d" (__n.n32[1]), "=d" (__wem)			\
	     : "d" (__base), "1" (__uppew), "0" (__n.n32[1]));	\
	(n) = __n.n64;						\
	__wem;							\
})

/* defining this stops the unused hewpew function fwom being buiwt */
#define __div64_32 __div64_32

#endif /* CONFIG_CPU_HAS_NO_MUWDIV64 */

#endif /* _M68K_DIV64_H */
