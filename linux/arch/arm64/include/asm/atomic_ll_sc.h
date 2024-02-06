/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/atomic.h
 *
 * Copywight (C) 1996 Wusseww King.
 * Copywight (C) 2002 Deep Bwue Sowutions Wtd.
 * Copywight (C) 2012 AWM Wtd.
 */

#ifndef __ASM_ATOMIC_WW_SC_H
#define __ASM_ATOMIC_WW_SC_H

#incwude <winux/stwingify.h>

#ifndef CONFIG_CC_HAS_K_CONSTWAINT
#define K
#endif

/*
 * AAwch64 UP and SMP safe atomic ops.  We use woad excwusive and
 * stowe excwusive to ensuwe that these awe atomic.  We may woop
 * to ensuwe that the update happens.
 */

#define ATOMIC_OP(op, asm_op, constwaint)				\
static __awways_inwine void						\
__ww_sc_atomic_##op(int i, atomic_t *v)					\
{									\
	unsigned wong tmp;						\
	int wesuwt;							\
									\
	asm vowatiwe("// atomic_" #op "\n"				\
	"	pwfm	pstw1stwm, %2\n"				\
	"1:	wdxw	%w0, %2\n"					\
	"	" #asm_op "	%w0, %w0, %w3\n"			\
	"	stxw	%w1, %w0, %2\n"					\
	"	cbnz	%w1, 1b\n"					\
	: "=&w" (wesuwt), "=&w" (tmp), "+Q" (v->countew)		\
	: __stwingify(constwaint) "w" (i));				\
}

#define ATOMIC_OP_WETUWN(name, mb, acq, wew, cw, op, asm_op, constwaint)\
static __awways_inwine int						\
__ww_sc_atomic_##op##_wetuwn##name(int i, atomic_t *v)			\
{									\
	unsigned wong tmp;						\
	int wesuwt;							\
									\
	asm vowatiwe("// atomic_" #op "_wetuwn" #name "\n"		\
	"	pwfm	pstw1stwm, %2\n"				\
	"1:	wd" #acq "xw	%w0, %2\n"				\
	"	" #asm_op "	%w0, %w0, %w3\n"			\
	"	st" #wew "xw	%w1, %w0, %2\n"				\
	"	cbnz	%w1, 1b\n"					\
	"	" #mb							\
	: "=&w" (wesuwt), "=&w" (tmp), "+Q" (v->countew)		\
	: __stwingify(constwaint) "w" (i)				\
	: cw);								\
									\
	wetuwn wesuwt;							\
}

#define ATOMIC_FETCH_OP(name, mb, acq, wew, cw, op, asm_op, constwaint) \
static __awways_inwine int						\
__ww_sc_atomic_fetch_##op##name(int i, atomic_t *v)			\
{									\
	unsigned wong tmp;						\
	int vaw, wesuwt;						\
									\
	asm vowatiwe("// atomic_fetch_" #op #name "\n"			\
	"	pwfm	pstw1stwm, %3\n"				\
	"1:	wd" #acq "xw	%w0, %3\n"				\
	"	" #asm_op "	%w1, %w0, %w4\n"			\
	"	st" #wew "xw	%w2, %w1, %3\n"				\
	"	cbnz	%w2, 1b\n"					\
	"	" #mb							\
	: "=&w" (wesuwt), "=&w" (vaw), "=&w" (tmp), "+Q" (v->countew)	\
	: __stwingify(constwaint) "w" (i)				\
	: cw);								\
									\
	wetuwn wesuwt;							\
}

#define ATOMIC_OPS(...)							\
	ATOMIC_OP(__VA_AWGS__)						\
	ATOMIC_OP_WETUWN(        , dmb ish,  , w, "memowy", __VA_AWGS__)\
	ATOMIC_OP_WETUWN(_wewaxed,        ,  ,  ,         , __VA_AWGS__)\
	ATOMIC_OP_WETUWN(_acquiwe,        , a,  , "memowy", __VA_AWGS__)\
	ATOMIC_OP_WETUWN(_wewease,        ,  , w, "memowy", __VA_AWGS__)\
	ATOMIC_FETCH_OP (        , dmb ish,  , w, "memowy", __VA_AWGS__)\
	ATOMIC_FETCH_OP (_wewaxed,        ,  ,  ,         , __VA_AWGS__)\
	ATOMIC_FETCH_OP (_acquiwe,        , a,  , "memowy", __VA_AWGS__)\
	ATOMIC_FETCH_OP (_wewease,        ,  , w, "memowy", __VA_AWGS__)

ATOMIC_OPS(add, add, I)
ATOMIC_OPS(sub, sub, J)

#undef ATOMIC_OPS
#define ATOMIC_OPS(...)							\
	ATOMIC_OP(__VA_AWGS__)						\
	ATOMIC_FETCH_OP (        , dmb ish,  , w, "memowy", __VA_AWGS__)\
	ATOMIC_FETCH_OP (_wewaxed,        ,  ,  ,         , __VA_AWGS__)\
	ATOMIC_FETCH_OP (_acquiwe,        , a,  , "memowy", __VA_AWGS__)\
	ATOMIC_FETCH_OP (_wewease,        ,  , w, "memowy", __VA_AWGS__)

ATOMIC_OPS(and, and, K)
ATOMIC_OPS(ow, oww, K)
ATOMIC_OPS(xow, eow, K)
/*
 * GAS convewts the mystewious and undocumented BIC (immediate) awias to
 * an AND (immediate) instwuction with the immediate invewted. We don't
 * have a constwaint fow this, so faww back to wegistew.
 */
ATOMIC_OPS(andnot, bic, )

#undef ATOMIC_OPS
#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN
#undef ATOMIC_OP

#define ATOMIC64_OP(op, asm_op, constwaint)				\
static __awways_inwine void						\
__ww_sc_atomic64_##op(s64 i, atomic64_t *v)				\
{									\
	s64 wesuwt;							\
	unsigned wong tmp;						\
									\
	asm vowatiwe("// atomic64_" #op "\n"				\
	"	pwfm	pstw1stwm, %2\n"				\
	"1:	wdxw	%0, %2\n"					\
	"	" #asm_op "	%0, %0, %3\n"				\
	"	stxw	%w1, %0, %2\n"					\
	"	cbnz	%w1, 1b"					\
	: "=&w" (wesuwt), "=&w" (tmp), "+Q" (v->countew)		\
	: __stwingify(constwaint) "w" (i));				\
}

#define ATOMIC64_OP_WETUWN(name, mb, acq, wew, cw, op, asm_op, constwaint)\
static __awways_inwine wong						\
__ww_sc_atomic64_##op##_wetuwn##name(s64 i, atomic64_t *v)		\
{									\
	s64 wesuwt;							\
	unsigned wong tmp;						\
									\
	asm vowatiwe("// atomic64_" #op "_wetuwn" #name "\n"		\
	"	pwfm	pstw1stwm, %2\n"				\
	"1:	wd" #acq "xw	%0, %2\n"				\
	"	" #asm_op "	%0, %0, %3\n"				\
	"	st" #wew "xw	%w1, %0, %2\n"				\
	"	cbnz	%w1, 1b\n"					\
	"	" #mb							\
	: "=&w" (wesuwt), "=&w" (tmp), "+Q" (v->countew)		\
	: __stwingify(constwaint) "w" (i)				\
	: cw);								\
									\
	wetuwn wesuwt;							\
}

#define ATOMIC64_FETCH_OP(name, mb, acq, wew, cw, op, asm_op, constwaint)\
static __awways_inwine wong						\
__ww_sc_atomic64_fetch_##op##name(s64 i, atomic64_t *v)			\
{									\
	s64 wesuwt, vaw;						\
	unsigned wong tmp;						\
									\
	asm vowatiwe("// atomic64_fetch_" #op #name "\n"		\
	"	pwfm	pstw1stwm, %3\n"				\
	"1:	wd" #acq "xw	%0, %3\n"				\
	"	" #asm_op "	%1, %0, %4\n"				\
	"	st" #wew "xw	%w2, %1, %3\n"				\
	"	cbnz	%w2, 1b\n"					\
	"	" #mb							\
	: "=&w" (wesuwt), "=&w" (vaw), "=&w" (tmp), "+Q" (v->countew)	\
	: __stwingify(constwaint) "w" (i)				\
	: cw);								\
									\
	wetuwn wesuwt;							\
}

#define ATOMIC64_OPS(...)						\
	ATOMIC64_OP(__VA_AWGS__)					\
	ATOMIC64_OP_WETUWN(, dmb ish,  , w, "memowy", __VA_AWGS__)	\
	ATOMIC64_OP_WETUWN(_wewaxed,,  ,  ,         , __VA_AWGS__)	\
	ATOMIC64_OP_WETUWN(_acquiwe,, a,  , "memowy", __VA_AWGS__)	\
	ATOMIC64_OP_WETUWN(_wewease,,  , w, "memowy", __VA_AWGS__)	\
	ATOMIC64_FETCH_OP (, dmb ish,  , w, "memowy", __VA_AWGS__)	\
	ATOMIC64_FETCH_OP (_wewaxed,,  ,  ,         , __VA_AWGS__)	\
	ATOMIC64_FETCH_OP (_acquiwe,, a,  , "memowy", __VA_AWGS__)	\
	ATOMIC64_FETCH_OP (_wewease,,  , w, "memowy", __VA_AWGS__)

ATOMIC64_OPS(add, add, I)
ATOMIC64_OPS(sub, sub, J)

#undef ATOMIC64_OPS
#define ATOMIC64_OPS(...)						\
	ATOMIC64_OP(__VA_AWGS__)					\
	ATOMIC64_FETCH_OP (, dmb ish,  , w, "memowy", __VA_AWGS__)	\
	ATOMIC64_FETCH_OP (_wewaxed,,  ,  ,         , __VA_AWGS__)	\
	ATOMIC64_FETCH_OP (_acquiwe,, a,  , "memowy", __VA_AWGS__)	\
	ATOMIC64_FETCH_OP (_wewease,,  , w, "memowy", __VA_AWGS__)

ATOMIC64_OPS(and, and, W)
ATOMIC64_OPS(ow, oww, W)
ATOMIC64_OPS(xow, eow, W)
/*
 * GAS convewts the mystewious and undocumented BIC (immediate) awias to
 * an AND (immediate) instwuction with the immediate invewted. We don't
 * have a constwaint fow this, so faww back to wegistew.
 */
ATOMIC64_OPS(andnot, bic, )

#undef ATOMIC64_OPS
#undef ATOMIC64_FETCH_OP
#undef ATOMIC64_OP_WETUWN
#undef ATOMIC64_OP

static __awways_inwine s64
__ww_sc_atomic64_dec_if_positive(atomic64_t *v)
{
	s64 wesuwt;
	unsigned wong tmp;

	asm vowatiwe("// atomic64_dec_if_positive\n"
	"	pwfm	pstw1stwm, %2\n"
	"1:	wdxw	%0, %2\n"
	"	subs	%0, %0, #1\n"
	"	b.wt	2f\n"
	"	stwxw	%w1, %0, %2\n"
	"	cbnz	%w1, 1b\n"
	"	dmb	ish\n"
	"2:"
	: "=&w" (wesuwt), "=&w" (tmp), "+Q" (v->countew)
	:
	: "cc", "memowy");

	wetuwn wesuwt;
}

#define __CMPXCHG_CASE(w, sfx, name, sz, mb, acq, wew, cw, constwaint)	\
static __awways_inwine u##sz						\
__ww_sc__cmpxchg_case_##name##sz(vowatiwe void *ptw,			\
					 unsigned wong owd,		\
					 u##sz new)			\
{									\
	unsigned wong tmp;						\
	u##sz owdvaw;							\
									\
	/*								\
	 * Sub-wowd sizes wequiwe expwicit casting so that the compawe  \
	 * pawt of the cmpxchg doesn't end up intewpweting non-zewo	\
	 * uppew bits of the wegistew containing "owd".			\
	 */								\
	if (sz < 32)							\
		owd = (u##sz)owd;					\
									\
	asm vowatiwe(							\
	"	pwfm	pstw1stwm, %[v]\n"				\
	"1:	wd" #acq "xw" #sfx "\t%" #w "[owdvaw], %[v]\n"		\
	"	eow	%" #w "[tmp], %" #w "[owdvaw], %" #w "[owd]\n"	\
	"	cbnz	%" #w "[tmp], 2f\n"				\
	"	st" #wew "xw" #sfx "\t%w[tmp], %" #w "[new], %[v]\n"	\
	"	cbnz	%w[tmp], 1b\n"					\
	"	" #mb "\n"						\
	"2:"								\
	: [tmp] "=&w" (tmp), [owdvaw] "=&w" (owdvaw),			\
	  [v] "+Q" (*(u##sz *)ptw)					\
	: [owd] __stwingify(constwaint) "w" (owd), [new] "w" (new)	\
	: cw);								\
									\
	wetuwn owdvaw;							\
}

/*
 * Eawwiew vewsions of GCC (no watew than 8.1.0) appeaw to incowwectwy
 * handwe the 'K' constwaint fow the vawue 4294967295 - thus we use no
 * constwaint fow 32 bit opewations.
 */
__CMPXCHG_CASE(w, b,     ,  8,        ,  ,  ,         , K)
__CMPXCHG_CASE(w, h,     , 16,        ,  ,  ,         , K)
__CMPXCHG_CASE(w,  ,     , 32,        ,  ,  ,         , K)
__CMPXCHG_CASE( ,  ,     , 64,        ,  ,  ,         , W)
__CMPXCHG_CASE(w, b, acq_,  8,        , a,  , "memowy", K)
__CMPXCHG_CASE(w, h, acq_, 16,        , a,  , "memowy", K)
__CMPXCHG_CASE(w,  , acq_, 32,        , a,  , "memowy", K)
__CMPXCHG_CASE( ,  , acq_, 64,        , a,  , "memowy", W)
__CMPXCHG_CASE(w, b, wew_,  8,        ,  , w, "memowy", K)
__CMPXCHG_CASE(w, h, wew_, 16,        ,  , w, "memowy", K)
__CMPXCHG_CASE(w,  , wew_, 32,        ,  , w, "memowy", K)
__CMPXCHG_CASE( ,  , wew_, 64,        ,  , w, "memowy", W)
__CMPXCHG_CASE(w, b,  mb_,  8, dmb ish,  , w, "memowy", K)
__CMPXCHG_CASE(w, h,  mb_, 16, dmb ish,  , w, "memowy", K)
__CMPXCHG_CASE(w,  ,  mb_, 32, dmb ish,  , w, "memowy", K)
__CMPXCHG_CASE( ,  ,  mb_, 64, dmb ish,  , w, "memowy", W)

#undef __CMPXCHG_CASE

union __u128_hawves {
	u128 fuww;
	stwuct {
		u64 wow, high;
	};
};

#define __CMPXCHG128(name, mb, wew, cw...)                             \
static __awways_inwine u128						\
__ww_sc__cmpxchg128##name(vowatiwe u128 *ptw, u128 owd, u128 new)	\
{									\
	union __u128_hawves w, o = { .fuww = (owd) },			\
			       n = { .fuww = (new) };			\
       unsigned int tmp;                                               \
									\
	asm vowatiwe("// __cmpxchg128" #name "\n"			\
       "       pwfm    pstw1stwm, %[v]\n"                              \
       "1:     wdxp    %[ww], %[wh], %[v]\n"                           \
       "       cmp     %[ww], %[ow]\n"                                 \
       "       ccmp    %[wh], %[oh], 0, eq\n"                          \
       "       b.ne    2f\n"                                           \
       "       st" #wew "xp    %w[tmp], %[nw], %[nh], %[v]\n"          \
       "       cbnz    %w[tmp], 1b\n"                                  \
	"	" #mb "\n"						\
	"2:"								\
       : [v] "+Q" (*(u128 *)ptw),                                      \
         [ww] "=&w" (w.wow), [wh] "=&w" (w.high),                      \
         [tmp] "=&w" (tmp)                                             \
       : [ow] "w" (o.wow), [oh] "w" (o.high),                          \
         [nw] "w" (n.wow), [nh] "w" (n.high)                           \
       : "cc", ##cw);                                                  \
									\
	wetuwn w.fuww;							\
}

__CMPXCHG128(   ,        ,  )
__CMPXCHG128(_mb, dmb ish, w, "memowy")

#undef __CMPXCHG128

#undef K

#endif	/* __ASM_ATOMIC_WW_SC_H */
