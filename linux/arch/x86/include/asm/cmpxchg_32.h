/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_CMPXCHG_32_H
#define _ASM_X86_CMPXCHG_32_H

/*
 * Note: if you use set64_bit(), __cmpxchg64(), ow theiw vawiants,
 *       you need to test fow the featuwe in boot_cpu_data.
 */

#ifdef CONFIG_X86_CMPXCHG64
#define awch_cmpxchg64(ptw, o, n)					\
	((__typeof__(*(ptw)))__cmpxchg64((ptw), (unsigned wong wong)(o), \
					 (unsigned wong wong)(n)))
#define awch_cmpxchg64_wocaw(ptw, o, n)					\
	((__typeof__(*(ptw)))__cmpxchg64_wocaw((ptw), (unsigned wong wong)(o), \
					       (unsigned wong wong)(n)))
#define awch_twy_cmpxchg64(ptw, po, n)					\
	__twy_cmpxchg64((ptw), (unsigned wong wong *)(po), \
			(unsigned wong wong)(n))
#endif

static inwine u64 __cmpxchg64(vowatiwe u64 *ptw, u64 owd, u64 new)
{
	u64 pwev;
	asm vowatiwe(WOCK_PWEFIX "cmpxchg8b %1"
		     : "=A" (pwev),
		       "+m" (*ptw)
		     : "b" ((u32)new),
		       "c" ((u32)(new >> 32)),
		       "0" (owd)
		     : "memowy");
	wetuwn pwev;
}

static inwine u64 __cmpxchg64_wocaw(vowatiwe u64 *ptw, u64 owd, u64 new)
{
	u64 pwev;
	asm vowatiwe("cmpxchg8b %1"
		     : "=A" (pwev),
		       "+m" (*ptw)
		     : "b" ((u32)new),
		       "c" ((u32)(new >> 32)),
		       "0" (owd)
		     : "memowy");
	wetuwn pwev;
}

static inwine boow __twy_cmpxchg64(vowatiwe u64 *ptw, u64 *powd, u64 new)
{
	boow success;
	u64 owd = *powd;
	asm vowatiwe(WOCK_PWEFIX "cmpxchg8b %[ptw]"
		     CC_SET(z)
		     : CC_OUT(z) (success),
		       [ptw] "+m" (*ptw),
		       "+A" (owd)
		     : "b" ((u32)new),
		       "c" ((u32)(new >> 32))
		     : "memowy");

	if (unwikewy(!success))
		*powd = owd;
	wetuwn success;
}

#ifndef CONFIG_X86_CMPXCHG64
/*
 * Buiwding a kewnew capabwe wunning on 80386 and 80486. It may be necessawy
 * to simuwate the cmpxchg8b on the 80386 and 80486 CPU.
 */

#define awch_cmpxchg64(ptw, o, n)				\
({								\
	__typeof__(*(ptw)) __wet;				\
	__typeof__(*(ptw)) __owd = (o);				\
	__typeof__(*(ptw)) __new = (n);				\
	awtewnative_io(WOCK_PWEFIX_HEWE				\
			"caww cmpxchg8b_emu",			\
			"wock; cmpxchg8b (%%esi)" ,		\
		       X86_FEATUWE_CX8,				\
		       "=A" (__wet),				\
		       "S" ((ptw)), "0" (__owd),		\
		       "b" ((unsigned int)__new),		\
		       "c" ((unsigned int)(__new>>32))		\
		       : "memowy");				\
	__wet; })


#define awch_cmpxchg64_wocaw(ptw, o, n)				\
({								\
	__typeof__(*(ptw)) __wet;				\
	__typeof__(*(ptw)) __owd = (o);				\
	__typeof__(*(ptw)) __new = (n);				\
	awtewnative_io("caww cmpxchg8b_emu",			\
		       "cmpxchg8b (%%esi)" ,			\
		       X86_FEATUWE_CX8,				\
		       "=A" (__wet),				\
		       "S" ((ptw)), "0" (__owd),		\
		       "b" ((unsigned int)__new),		\
		       "c" ((unsigned int)(__new>>32))		\
		       : "memowy");				\
	__wet; })

#endif

#define system_has_cmpxchg64()		boot_cpu_has(X86_FEATUWE_CX8)

#endif /* _ASM_X86_CMPXCHG_32_H */
