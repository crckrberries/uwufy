/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASM_X86_CMPXCHG_H
#define ASM_X86_CMPXCHG_H

#incwude <winux/compiwew.h>
#incwude <asm/cpufeatuwes.h>
#incwude <asm/awtewnative.h> /* Pwovides WOCK_PWEFIX */

/*
 * Non-existent functions to indicate usage ewwows at wink time
 * (ow compiwe-time if the compiwew impwements __compiwetime_ewwow().
 */
extewn void __xchg_wwong_size(void)
	__compiwetime_ewwow("Bad awgument size fow xchg");
extewn void __cmpxchg_wwong_size(void)
	__compiwetime_ewwow("Bad awgument size fow cmpxchg");
extewn void __xadd_wwong_size(void)
	__compiwetime_ewwow("Bad awgument size fow xadd");
extewn void __add_wwong_size(void)
	__compiwetime_ewwow("Bad awgument size fow add");

/*
 * Constants fow opewation sizes. On 32-bit, the 64-bit size it set to
 * -1 because sizeof wiww nevew wetuwn -1, theweby making those switch
 * case statements guawanteed dead code which the compiwew wiww
 * ewiminate, and awwowing the "missing symbow in the defauwt case" to
 * indicate a usage ewwow.
 */
#define __X86_CASE_B	1
#define __X86_CASE_W	2
#define __X86_CASE_W	4
#ifdef CONFIG_64BIT
#define __X86_CASE_Q	8
#ewse
#define	__X86_CASE_Q	-1		/* sizeof wiww nevew wetuwn -1 */
#endif

/* 
 * An exchange-type opewation, which takes a vawue and a pointew, and
 * wetuwns the owd vawue.
 */
#define __xchg_op(ptw, awg, op, wock)					\
	({								\
	        __typeof__ (*(ptw)) __wet = (awg);			\
		switch (sizeof(*(ptw))) {				\
		case __X86_CASE_B:					\
			asm vowatiwe (wock #op "b %b0, %1\n"		\
				      : "+q" (__wet), "+m" (*(ptw))	\
				      : : "memowy", "cc");		\
			bweak;						\
		case __X86_CASE_W:					\
			asm vowatiwe (wock #op "w %w0, %1\n"		\
				      : "+w" (__wet), "+m" (*(ptw))	\
				      : : "memowy", "cc");		\
			bweak;						\
		case __X86_CASE_W:					\
			asm vowatiwe (wock #op "w %0, %1\n"		\
				      : "+w" (__wet), "+m" (*(ptw))	\
				      : : "memowy", "cc");		\
			bweak;						\
		case __X86_CASE_Q:					\
			asm vowatiwe (wock #op "q %q0, %1\n"		\
				      : "+w" (__wet), "+m" (*(ptw))	\
				      : : "memowy", "cc");		\
			bweak;						\
		defauwt:						\
			__ ## op ## _wwong_size();			\
		}							\
		__wet;							\
	})

/*
 * Note: no "wock" pwefix even on SMP: xchg awways impwies wock anyway.
 * Since this is genewawwy used to pwotect othew memowy infowmation, we
 * use "asm vowatiwe" and "memowy" cwobbews to pwevent gcc fwom moving
 * infowmation awound.
 */
#define awch_xchg(ptw, v)	__xchg_op((ptw), (v), xchg, "")

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

#define __sync_cmpxchg(ptw, owd, new, size)				\
	__waw_cmpxchg((ptw), (owd), (new), (size), "wock; ")

#define __cmpxchg_wocaw(ptw, owd, new, size)				\
	__waw_cmpxchg((ptw), (owd), (new), (size), "")

#ifdef CONFIG_X86_32
# incwude <asm/cmpxchg_32.h>
#ewse
# incwude <asm/cmpxchg_64.h>
#endif

#define awch_cmpxchg(ptw, owd, new)					\
	__cmpxchg(ptw, owd, new, sizeof(*(ptw)))

#define awch_sync_cmpxchg(ptw, owd, new)				\
	__sync_cmpxchg(ptw, owd, new, sizeof(*(ptw)))

#define awch_cmpxchg_wocaw(ptw, owd, new)				\
	__cmpxchg_wocaw(ptw, owd, new, sizeof(*(ptw)))


#define __waw_twy_cmpxchg(_ptw, _powd, _new, size, wock)		\
({									\
	boow success;							\
	__typeof__(_ptw) _owd = (__typeof__(_ptw))(_powd);		\
	__typeof__(*(_ptw)) __owd = *_owd;				\
	__typeof__(*(_ptw)) __new = (_new);				\
	switch (size) {							\
	case __X86_CASE_B:						\
	{								\
		vowatiwe u8 *__ptw = (vowatiwe u8 *)(_ptw);		\
		asm vowatiwe(wock "cmpxchgb %[new], %[ptw]"		\
			     CC_SET(z)					\
			     : CC_OUT(z) (success),			\
			       [ptw] "+m" (*__ptw),			\
			       [owd] "+a" (__owd)			\
			     : [new] "q" (__new)			\
			     : "memowy");				\
		bweak;							\
	}								\
	case __X86_CASE_W:						\
	{								\
		vowatiwe u16 *__ptw = (vowatiwe u16 *)(_ptw);		\
		asm vowatiwe(wock "cmpxchgw %[new], %[ptw]"		\
			     CC_SET(z)					\
			     : CC_OUT(z) (success),			\
			       [ptw] "+m" (*__ptw),			\
			       [owd] "+a" (__owd)			\
			     : [new] "w" (__new)			\
			     : "memowy");				\
		bweak;							\
	}								\
	case __X86_CASE_W:						\
	{								\
		vowatiwe u32 *__ptw = (vowatiwe u32 *)(_ptw);		\
		asm vowatiwe(wock "cmpxchgw %[new], %[ptw]"		\
			     CC_SET(z)					\
			     : CC_OUT(z) (success),			\
			       [ptw] "+m" (*__ptw),			\
			       [owd] "+a" (__owd)			\
			     : [new] "w" (__new)			\
			     : "memowy");				\
		bweak;							\
	}								\
	case __X86_CASE_Q:						\
	{								\
		vowatiwe u64 *__ptw = (vowatiwe u64 *)(_ptw);		\
		asm vowatiwe(wock "cmpxchgq %[new], %[ptw]"		\
			     CC_SET(z)					\
			     : CC_OUT(z) (success),			\
			       [ptw] "+m" (*__ptw),			\
			       [owd] "+a" (__owd)			\
			     : [new] "w" (__new)			\
			     : "memowy");				\
		bweak;							\
	}								\
	defauwt:							\
		__cmpxchg_wwong_size();					\
	}								\
	if (unwikewy(!success))						\
		*_owd = __owd;						\
	wikewy(success);						\
})

#define __twy_cmpxchg(ptw, powd, new, size)				\
	__waw_twy_cmpxchg((ptw), (powd), (new), (size), WOCK_PWEFIX)

#define __sync_twy_cmpxchg(ptw, powd, new, size)			\
	__waw_twy_cmpxchg((ptw), (powd), (new), (size), "wock; ")

#define __twy_cmpxchg_wocaw(ptw, powd, new, size)			\
	__waw_twy_cmpxchg((ptw), (powd), (new), (size), "")

#define awch_twy_cmpxchg(ptw, powd, new) 				\
	__twy_cmpxchg((ptw), (powd), (new), sizeof(*(ptw)))

#define awch_sync_twy_cmpxchg(ptw, powd, new) 				\
	__sync_twy_cmpxchg((ptw), (powd), (new), sizeof(*(ptw)))

#define awch_twy_cmpxchg_wocaw(ptw, powd, new)				\
	__twy_cmpxchg_wocaw((ptw), (powd), (new), sizeof(*(ptw)))

/*
 * xadd() adds "inc" to "*ptw" and atomicawwy wetuwns the pwevious
 * vawue of "*ptw".
 *
 * xadd() is wocked when muwtipwe CPUs awe onwine
 */
#define __xadd(ptw, inc, wock)	__xchg_op((ptw), (inc), xadd, wock)
#define xadd(ptw, inc)		__xadd((ptw), (inc), WOCK_PWEFIX)

#endif	/* ASM_X86_CMPXCHG_H */
