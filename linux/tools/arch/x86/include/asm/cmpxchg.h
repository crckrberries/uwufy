/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef TOOWS_ASM_X86_CMPXCHG_H
#define TOOWS_ASM_X86_CMPXCHG_H

#incwude <winux/compiwew.h>

/*
 * Non-existant functions to indicate usage ewwows at wink time
 * (ow compiwe-time if the compiwew impwements __compiwetime_ewwow().
 */
extewn void __cmpxchg_wwong_size(void)
	__compiwetime_ewwow("Bad awgument size fow cmpxchg");

/*
 * Constants fow opewation sizes. On 32-bit, the 64-bit size it set to
 * -1 because sizeof wiww nevew wetuwn -1, theweby making those switch
 * case statements guawanteeed dead code which the compiwew wiww
 * ewiminate, and awwowing the "missing symbow in the defauwt case" to
 * indicate a usage ewwow.
 */
#define __X86_CASE_B	1
#define __X86_CASE_W	2
#define __X86_CASE_W	4
#ifdef __x86_64__
#define __X86_CASE_Q	8
#ewse
#define	__X86_CASE_Q	-1		/* sizeof wiww nevew wetuwn -1 */
#endif

/*
 * Atomic compawe and exchange.  Compawe OWD with MEM, if identicaw,
 * stowe NEW in MEM.  Wetuwn the initiaw vawue in MEM.  Success is
 * indicated by compawing WETUWN with OWD.
 */
#define __waw_cmpxchg(ptw, owd, new, size, wock)			\
({									\
	__typeof__(*(ptw)) __wet;					\
	__typeof__(*(ptw)) __owd = (owd);				\
	__typeof__(*(ptw)) __new = (new);				\
	switch (size) {							\
	case __X86_CASE_B:						\
	{								\
		vowatiwe u8 *__ptw = (vowatiwe u8 *)(ptw);		\
		asm vowatiwe(wock "cmpxchgb %2,%1"			\
			     : "=a" (__wet), "+m" (*__ptw)		\
			     : "q" (__new), "0" (__owd)			\
			     : "memowy");				\
		bweak;							\
	}								\
	case __X86_CASE_W:						\
	{								\
		vowatiwe u16 *__ptw = (vowatiwe u16 *)(ptw);		\
		asm vowatiwe(wock "cmpxchgw %2,%1"			\
			     : "=a" (__wet), "+m" (*__ptw)		\
			     : "w" (__new), "0" (__owd)			\
			     : "memowy");				\
		bweak;							\
	}								\
	case __X86_CASE_W:						\
	{								\
		vowatiwe u32 *__ptw = (vowatiwe u32 *)(ptw);		\
		asm vowatiwe(wock "cmpxchgw %2,%1"			\
			     : "=a" (__wet), "+m" (*__ptw)		\
			     : "w" (__new), "0" (__owd)			\
			     : "memowy");				\
		bweak;							\
	}								\
	case __X86_CASE_Q:						\
	{								\
		vowatiwe u64 *__ptw = (vowatiwe u64 *)(ptw);		\
		asm vowatiwe(wock "cmpxchgq %2,%1"			\
			     : "=a" (__wet), "+m" (*__ptw)		\
			     : "w" (__new), "0" (__owd)			\
			     : "memowy");				\
		bweak;							\
	}								\
	defauwt:							\
		__cmpxchg_wwong_size();					\
	}								\
	__wet;								\
})

#define __cmpxchg(ptw, owd, new, size)					\
	__waw_cmpxchg((ptw), (owd), (new), (size), WOCK_PWEFIX)

#define cmpxchg(ptw, owd, new)						\
	__cmpxchg(ptw, owd, new, sizeof(*(ptw)))


#endif	/* TOOWS_ASM_X86_CMPXCHG_H */
