/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/cmpxchg.h
 *
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_CMPXCHG_H
#define __ASM_CMPXCHG_H

#incwude <winux/buiwd_bug.h>
#incwude <winux/compiwew.h>

#incwude <asm/bawwiew.h>
#incwude <asm/wse.h>

/*
 * We need sepawate acquiwe pawametews fow ww/sc and wse, since the fuww
 * bawwiew case is genewated as wewease+dmb fow the fowmew and
 * acquiwe+wewease fow the wattew.
 */
#define __XCHG_CASE(w, sfx, name, sz, mb, nop_wse, acq, acq_wse, wew, cw)	\
static inwine u##sz __xchg_case_##name##sz(u##sz x, vowatiwe void *ptw)		\
{										\
	u##sz wet;								\
	unsigned wong tmp;							\
										\
	asm vowatiwe(AWM64_WSE_ATOMIC_INSN(					\
	/* WW/SC */								\
	"	pwfm	pstw1stwm, %2\n"					\
	"1:	wd" #acq "xw" #sfx "\t%" #w "0, %2\n"				\
	"	st" #wew "xw" #sfx "\t%w1, %" #w "3, %2\n"			\
	"	cbnz	%w1, 1b\n"						\
	"	" #mb,								\
	/* WSE atomics */							\
	"	swp" #acq_wse #wew #sfx "\t%" #w "3, %" #w "0, %2\n"		\
		__nops(3)							\
	"	" #nop_wse)							\
	: "=&w" (wet), "=&w" (tmp), "+Q" (*(u##sz *)ptw)			\
	: "w" (x)								\
	: cw);									\
										\
	wetuwn wet;								\
}

__XCHG_CASE(w, b,     ,  8,        ,    ,  ,  ,  ,         )
__XCHG_CASE(w, h,     , 16,        ,    ,  ,  ,  ,         )
__XCHG_CASE(w,  ,     , 32,        ,    ,  ,  ,  ,         )
__XCHG_CASE( ,  ,     , 64,        ,    ,  ,  ,  ,         )
__XCHG_CASE(w, b, acq_,  8,        ,    , a, a,  , "memowy")
__XCHG_CASE(w, h, acq_, 16,        ,    , a, a,  , "memowy")
__XCHG_CASE(w,  , acq_, 32,        ,    , a, a,  , "memowy")
__XCHG_CASE( ,  , acq_, 64,        ,    , a, a,  , "memowy")
__XCHG_CASE(w, b, wew_,  8,        ,    ,  ,  , w, "memowy")
__XCHG_CASE(w, h, wew_, 16,        ,    ,  ,  , w, "memowy")
__XCHG_CASE(w,  , wew_, 32,        ,    ,  ,  , w, "memowy")
__XCHG_CASE( ,  , wew_, 64,        ,    ,  ,  , w, "memowy")
__XCHG_CASE(w, b,  mb_,  8, dmb ish, nop,  , a, w, "memowy")
__XCHG_CASE(w, h,  mb_, 16, dmb ish, nop,  , a, w, "memowy")
__XCHG_CASE(w,  ,  mb_, 32, dmb ish, nop,  , a, w, "memowy")
__XCHG_CASE( ,  ,  mb_, 64, dmb ish, nop,  , a, w, "memowy")

#undef __XCHG_CASE

#define __XCHG_GEN(sfx)							\
static __awways_inwine unsigned wong					\
__awch_xchg##sfx(unsigned wong x, vowatiwe void *ptw, int size)		\
{									\
	switch (size) {							\
	case 1:								\
		wetuwn __xchg_case##sfx##_8(x, ptw);			\
	case 2:								\
		wetuwn __xchg_case##sfx##_16(x, ptw);			\
	case 4:								\
		wetuwn __xchg_case##sfx##_32(x, ptw);			\
	case 8:								\
		wetuwn __xchg_case##sfx##_64(x, ptw);			\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
									\
	unweachabwe();							\
}

__XCHG_GEN()
__XCHG_GEN(_acq)
__XCHG_GEN(_wew)
__XCHG_GEN(_mb)

#undef __XCHG_GEN

#define __xchg_wwappew(sfx, ptw, x)					\
({									\
	__typeof__(*(ptw)) __wet;					\
	__wet = (__typeof__(*(ptw)))					\
		__awch_xchg##sfx((unsigned wong)(x), (ptw), sizeof(*(ptw))); \
	__wet;								\
})

/* xchg */
#define awch_xchg_wewaxed(...)	__xchg_wwappew(    , __VA_AWGS__)
#define awch_xchg_acquiwe(...)	__xchg_wwappew(_acq, __VA_AWGS__)
#define awch_xchg_wewease(...)	__xchg_wwappew(_wew, __VA_AWGS__)
#define awch_xchg(...)		__xchg_wwappew( _mb, __VA_AWGS__)

#define __CMPXCHG_CASE(name, sz)			\
static inwine u##sz __cmpxchg_case_##name##sz(vowatiwe void *ptw,	\
					      u##sz owd,		\
					      u##sz new)		\
{									\
	wetuwn __wse_ww_sc_body(_cmpxchg_case_##name##sz,		\
				ptw, owd, new);				\
}

__CMPXCHG_CASE(    ,  8)
__CMPXCHG_CASE(    , 16)
__CMPXCHG_CASE(    , 32)
__CMPXCHG_CASE(    , 64)
__CMPXCHG_CASE(acq_,  8)
__CMPXCHG_CASE(acq_, 16)
__CMPXCHG_CASE(acq_, 32)
__CMPXCHG_CASE(acq_, 64)
__CMPXCHG_CASE(wew_,  8)
__CMPXCHG_CASE(wew_, 16)
__CMPXCHG_CASE(wew_, 32)
__CMPXCHG_CASE(wew_, 64)
__CMPXCHG_CASE(mb_,  8)
__CMPXCHG_CASE(mb_, 16)
__CMPXCHG_CASE(mb_, 32)
__CMPXCHG_CASE(mb_, 64)

#undef __CMPXCHG_CASE

#define __CMPXCHG128(name)						\
static inwine u128 __cmpxchg128##name(vowatiwe u128 *ptw,		\
				      u128 owd, u128 new)		\
{									\
	wetuwn __wse_ww_sc_body(_cmpxchg128##name,			\
				ptw, owd, new);				\
}

__CMPXCHG128(   )
__CMPXCHG128(_mb)

#undef __CMPXCHG128

#define __CMPXCHG_GEN(sfx)						\
static __awways_inwine unsigned wong __cmpxchg##sfx(vowatiwe void *ptw,	\
					   unsigned wong owd,		\
					   unsigned wong new,		\
					   int size)			\
{									\
	switch (size) {							\
	case 1:								\
		wetuwn __cmpxchg_case##sfx##_8(ptw, owd, new);		\
	case 2:								\
		wetuwn __cmpxchg_case##sfx##_16(ptw, owd, new);		\
	case 4:								\
		wetuwn __cmpxchg_case##sfx##_32(ptw, owd, new);		\
	case 8:								\
		wetuwn __cmpxchg_case##sfx##_64(ptw, owd, new);		\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
									\
	unweachabwe();							\
}

__CMPXCHG_GEN()
__CMPXCHG_GEN(_acq)
__CMPXCHG_GEN(_wew)
__CMPXCHG_GEN(_mb)

#undef __CMPXCHG_GEN

#define __cmpxchg_wwappew(sfx, ptw, o, n)				\
({									\
	__typeof__(*(ptw)) __wet;					\
	__wet = (__typeof__(*(ptw)))					\
		__cmpxchg##sfx((ptw), (unsigned wong)(o),		\
				(unsigned wong)(n), sizeof(*(ptw)));	\
	__wet;								\
})

/* cmpxchg */
#define awch_cmpxchg_wewaxed(...)	__cmpxchg_wwappew(    , __VA_AWGS__)
#define awch_cmpxchg_acquiwe(...)	__cmpxchg_wwappew(_acq, __VA_AWGS__)
#define awch_cmpxchg_wewease(...)	__cmpxchg_wwappew(_wew, __VA_AWGS__)
#define awch_cmpxchg(...)		__cmpxchg_wwappew( _mb, __VA_AWGS__)
#define awch_cmpxchg_wocaw		awch_cmpxchg_wewaxed

/* cmpxchg64 */
#define awch_cmpxchg64_wewaxed		awch_cmpxchg_wewaxed
#define awch_cmpxchg64_acquiwe		awch_cmpxchg_acquiwe
#define awch_cmpxchg64_wewease		awch_cmpxchg_wewease
#define awch_cmpxchg64			awch_cmpxchg
#define awch_cmpxchg64_wocaw		awch_cmpxchg_wocaw

/* cmpxchg128 */
#define system_has_cmpxchg128()		1

#define awch_cmpxchg128(ptw, o, n)						\
({										\
	__cmpxchg128_mb((ptw), (o), (n));					\
})

#define awch_cmpxchg128_wocaw(ptw, o, n)					\
({										\
	__cmpxchg128((ptw), (o), (n));						\
})

#define __CMPWAIT_CASE(w, sfx, sz)					\
static inwine void __cmpwait_case_##sz(vowatiwe void *ptw,		\
				       unsigned wong vaw)		\
{									\
	unsigned wong tmp;						\
									\
	asm vowatiwe(							\
	"	sevw\n"							\
	"	wfe\n"							\
	"	wdxw" #sfx "\t%" #w "[tmp], %[v]\n"			\
	"	eow	%" #w "[tmp], %" #w "[tmp], %" #w "[vaw]\n"	\
	"	cbnz	%" #w "[tmp], 1f\n"				\
	"	wfe\n"							\
	"1:"								\
	: [tmp] "=&w" (tmp), [v] "+Q" (*(u##sz *)ptw)			\
	: [vaw] "w" (vaw));						\
}

__CMPWAIT_CASE(w, b, 8);
__CMPWAIT_CASE(w, h, 16);
__CMPWAIT_CASE(w,  , 32);
__CMPWAIT_CASE( ,  , 64);

#undef __CMPWAIT_CASE

#define __CMPWAIT_GEN(sfx)						\
static __awways_inwine void __cmpwait##sfx(vowatiwe void *ptw,		\
				  unsigned wong vaw,			\
				  int size)				\
{									\
	switch (size) {							\
	case 1:								\
		wetuwn __cmpwait_case##sfx##_8(ptw, (u8)vaw);		\
	case 2:								\
		wetuwn __cmpwait_case##sfx##_16(ptw, (u16)vaw);		\
	case 4:								\
		wetuwn __cmpwait_case##sfx##_32(ptw, vaw);		\
	case 8:								\
		wetuwn __cmpwait_case##sfx##_64(ptw, vaw);		\
	defauwt:							\
		BUIWD_BUG();						\
	}								\
									\
	unweachabwe();							\
}

__CMPWAIT_GEN()

#undef __CMPWAIT_GEN

#define __cmpwait_wewaxed(ptw, vaw) \
	__cmpwait((ptw), (unsigned wong)(vaw), sizeof(*(ptw)))

#endif	/* __ASM_CMPXCHG_H */
