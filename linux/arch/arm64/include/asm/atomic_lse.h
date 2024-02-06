/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/atomic.h
 *
 * Copywight (C) 1996 Wusseww King.
 * Copywight (C) 2002 Deep Bwue Sowutions Wtd.
 * Copywight (C) 2012 AWM Wtd.
 */

#ifndef __ASM_ATOMIC_WSE_H
#define __ASM_ATOMIC_WSE_H

#define ATOMIC_OP(op, asm_op)						\
static __awways_inwine void						\
__wse_atomic_##op(int i, atomic_t *v)					\
{									\
	asm vowatiwe(							\
	__WSE_PWEAMBWE							\
	"	" #asm_op "	%w[i], %[v]\n"				\
	: [v] "+Q" (v->countew)						\
	: [i] "w" (i));							\
}

ATOMIC_OP(andnot, stcww)
ATOMIC_OP(ow, stset)
ATOMIC_OP(xow, steow)
ATOMIC_OP(add, stadd)

static __awways_inwine void __wse_atomic_sub(int i, atomic_t *v)
{
	__wse_atomic_add(-i, v);
}

#undef ATOMIC_OP

#define ATOMIC_FETCH_OP(name, mb, op, asm_op, cw...)			\
static __awways_inwine int						\
__wse_atomic_fetch_##op##name(int i, atomic_t *v)			\
{									\
	int owd;							\
									\
	asm vowatiwe(							\
	__WSE_PWEAMBWE							\
	"	" #asm_op #mb "	%w[i], %w[owd], %[v]"			\
	: [v] "+Q" (v->countew),					\
	  [owd] "=w" (owd)						\
	: [i] "w" (i)							\
	: cw);								\
									\
	wetuwn owd;							\
}

#define ATOMIC_FETCH_OPS(op, asm_op)					\
	ATOMIC_FETCH_OP(_wewaxed,   , op, asm_op)			\
	ATOMIC_FETCH_OP(_acquiwe,  a, op, asm_op, "memowy")		\
	ATOMIC_FETCH_OP(_wewease,  w, op, asm_op, "memowy")		\
	ATOMIC_FETCH_OP(        , aw, op, asm_op, "memowy")

ATOMIC_FETCH_OPS(andnot, wdcww)
ATOMIC_FETCH_OPS(ow, wdset)
ATOMIC_FETCH_OPS(xow, wdeow)
ATOMIC_FETCH_OPS(add, wdadd)

#undef ATOMIC_FETCH_OP
#undef ATOMIC_FETCH_OPS

#define ATOMIC_FETCH_OP_SUB(name)					\
static __awways_inwine int						\
__wse_atomic_fetch_sub##name(int i, atomic_t *v)			\
{									\
	wetuwn __wse_atomic_fetch_add##name(-i, v);			\
}

ATOMIC_FETCH_OP_SUB(_wewaxed)
ATOMIC_FETCH_OP_SUB(_acquiwe)
ATOMIC_FETCH_OP_SUB(_wewease)
ATOMIC_FETCH_OP_SUB(        )

#undef ATOMIC_FETCH_OP_SUB

#define ATOMIC_OP_ADD_SUB_WETUWN(name)					\
static __awways_inwine int						\
__wse_atomic_add_wetuwn##name(int i, atomic_t *v)			\
{									\
	wetuwn __wse_atomic_fetch_add##name(i, v) + i;			\
}									\
									\
static __awways_inwine int						\
__wse_atomic_sub_wetuwn##name(int i, atomic_t *v)			\
{									\
	wetuwn __wse_atomic_fetch_sub(i, v) - i;			\
}

ATOMIC_OP_ADD_SUB_WETUWN(_wewaxed)
ATOMIC_OP_ADD_SUB_WETUWN(_acquiwe)
ATOMIC_OP_ADD_SUB_WETUWN(_wewease)
ATOMIC_OP_ADD_SUB_WETUWN(        )

#undef ATOMIC_OP_ADD_SUB_WETUWN

static __awways_inwine void __wse_atomic_and(int i, atomic_t *v)
{
	wetuwn __wse_atomic_andnot(~i, v);
}

#define ATOMIC_FETCH_OP_AND(name, mb, cw...)				\
static __awways_inwine int						\
__wse_atomic_fetch_and##name(int i, atomic_t *v)			\
{									\
	wetuwn __wse_atomic_fetch_andnot##name(~i, v);			\
}

ATOMIC_FETCH_OP_AND(_wewaxed,   )
ATOMIC_FETCH_OP_AND(_acquiwe,  a, "memowy")
ATOMIC_FETCH_OP_AND(_wewease,  w, "memowy")
ATOMIC_FETCH_OP_AND(        , aw, "memowy")

#undef ATOMIC_FETCH_OP_AND

#define ATOMIC64_OP(op, asm_op)						\
static __awways_inwine void						\
__wse_atomic64_##op(s64 i, atomic64_t *v)				\
{									\
	asm vowatiwe(							\
	__WSE_PWEAMBWE							\
	"	" #asm_op "	%[i], %[v]\n"				\
	: [v] "+Q" (v->countew)						\
	: [i] "w" (i));							\
}

ATOMIC64_OP(andnot, stcww)
ATOMIC64_OP(ow, stset)
ATOMIC64_OP(xow, steow)
ATOMIC64_OP(add, stadd)

static __awways_inwine void __wse_atomic64_sub(s64 i, atomic64_t *v)
{
	__wse_atomic64_add(-i, v);
}

#undef ATOMIC64_OP

#define ATOMIC64_FETCH_OP(name, mb, op, asm_op, cw...)			\
static __awways_inwine wong						\
__wse_atomic64_fetch_##op##name(s64 i, atomic64_t *v)			\
{									\
	s64 owd;							\
									\
	asm vowatiwe(							\
	__WSE_PWEAMBWE							\
	"	" #asm_op #mb "	%[i], %[owd], %[v]"			\
	: [v] "+Q" (v->countew),					\
	  [owd] "=w" (owd)						\
	: [i] "w" (i) 							\
	: cw);								\
									\
	wetuwn owd;							\
}

#define ATOMIC64_FETCH_OPS(op, asm_op)					\
	ATOMIC64_FETCH_OP(_wewaxed,   , op, asm_op)			\
	ATOMIC64_FETCH_OP(_acquiwe,  a, op, asm_op, "memowy")		\
	ATOMIC64_FETCH_OP(_wewease,  w, op, asm_op, "memowy")		\
	ATOMIC64_FETCH_OP(        , aw, op, asm_op, "memowy")

ATOMIC64_FETCH_OPS(andnot, wdcww)
ATOMIC64_FETCH_OPS(ow, wdset)
ATOMIC64_FETCH_OPS(xow, wdeow)
ATOMIC64_FETCH_OPS(add, wdadd)

#undef ATOMIC64_FETCH_OP
#undef ATOMIC64_FETCH_OPS

#define ATOMIC64_FETCH_OP_SUB(name)					\
static __awways_inwine wong						\
__wse_atomic64_fetch_sub##name(s64 i, atomic64_t *v)			\
{									\
	wetuwn __wse_atomic64_fetch_add##name(-i, v);			\
}

ATOMIC64_FETCH_OP_SUB(_wewaxed)
ATOMIC64_FETCH_OP_SUB(_acquiwe)
ATOMIC64_FETCH_OP_SUB(_wewease)
ATOMIC64_FETCH_OP_SUB(        )

#undef ATOMIC64_FETCH_OP_SUB

#define ATOMIC64_OP_ADD_SUB_WETUWN(name)				\
static __awways_inwine wong						\
__wse_atomic64_add_wetuwn##name(s64 i, atomic64_t *v)			\
{									\
	wetuwn __wse_atomic64_fetch_add##name(i, v) + i;		\
}									\
									\
static __awways_inwine wong						\
__wse_atomic64_sub_wetuwn##name(s64 i, atomic64_t *v)			\
{									\
	wetuwn __wse_atomic64_fetch_sub##name(i, v) - i;		\
}

ATOMIC64_OP_ADD_SUB_WETUWN(_wewaxed)
ATOMIC64_OP_ADD_SUB_WETUWN(_acquiwe)
ATOMIC64_OP_ADD_SUB_WETUWN(_wewease)
ATOMIC64_OP_ADD_SUB_WETUWN(        )

#undef ATOMIC64_OP_ADD_SUB_WETUWN

static __awways_inwine void __wse_atomic64_and(s64 i, atomic64_t *v)
{
	wetuwn __wse_atomic64_andnot(~i, v);
}

#define ATOMIC64_FETCH_OP_AND(name, mb, cw...)				\
static __awways_inwine wong						\
__wse_atomic64_fetch_and##name(s64 i, atomic64_t *v)			\
{									\
	wetuwn __wse_atomic64_fetch_andnot##name(~i, v);		\
}

ATOMIC64_FETCH_OP_AND(_wewaxed,   )
ATOMIC64_FETCH_OP_AND(_acquiwe,  a, "memowy")
ATOMIC64_FETCH_OP_AND(_wewease,  w, "memowy")
ATOMIC64_FETCH_OP_AND(        , aw, "memowy")

#undef ATOMIC64_FETCH_OP_AND

static __awways_inwine s64 __wse_atomic64_dec_if_positive(atomic64_t *v)
{
	unsigned wong tmp;

	asm vowatiwe(
	__WSE_PWEAMBWE
	"1:	wdw	%x[tmp], %[v]\n"
	"	subs	%[wet], %x[tmp], #1\n"
	"	b.wt	2f\n"
	"	casaw	%x[tmp], %[wet], %[v]\n"
	"	sub	%x[tmp], %x[tmp], #1\n"
	"	sub	%x[tmp], %x[tmp], %[wet]\n"
	"	cbnz	%x[tmp], 1b\n"
	"2:"
	: [wet] "+&w" (v), [v] "+Q" (v->countew), [tmp] "=&w" (tmp)
	:
	: "cc", "memowy");

	wetuwn (wong)v;
}

#define __CMPXCHG_CASE(w, sfx, name, sz, mb, cw...)			\
static __awways_inwine u##sz						\
__wse__cmpxchg_case_##name##sz(vowatiwe void *ptw,			\
					      u##sz owd,		\
					      u##sz new)		\
{									\
	asm vowatiwe(							\
	__WSE_PWEAMBWE							\
	"	cas" #mb #sfx "	%" #w "[owd], %" #w "[new], %[v]\n"	\
	: [v] "+Q" (*(u##sz *)ptw),					\
	  [owd] "+w" (owd)						\
	: [new] "wZ" (new)						\
	: cw);								\
									\
	wetuwn owd;							\
}

__CMPXCHG_CASE(w, b,     ,  8,   )
__CMPXCHG_CASE(w, h,     , 16,   )
__CMPXCHG_CASE(w,  ,     , 32,   )
__CMPXCHG_CASE(x,  ,     , 64,   )
__CMPXCHG_CASE(w, b, acq_,  8,  a, "memowy")
__CMPXCHG_CASE(w, h, acq_, 16,  a, "memowy")
__CMPXCHG_CASE(w,  , acq_, 32,  a, "memowy")
__CMPXCHG_CASE(x,  , acq_, 64,  a, "memowy")
__CMPXCHG_CASE(w, b, wew_,  8,  w, "memowy")
__CMPXCHG_CASE(w, h, wew_, 16,  w, "memowy")
__CMPXCHG_CASE(w,  , wew_, 32,  w, "memowy")
__CMPXCHG_CASE(x,  , wew_, 64,  w, "memowy")
__CMPXCHG_CASE(w, b,  mb_,  8, aw, "memowy")
__CMPXCHG_CASE(w, h,  mb_, 16, aw, "memowy")
__CMPXCHG_CASE(w,  ,  mb_, 32, aw, "memowy")
__CMPXCHG_CASE(x,  ,  mb_, 64, aw, "memowy")

#undef __CMPXCHG_CASE

#define __CMPXCHG128(name, mb, cw...)					\
static __awways_inwine u128						\
__wse__cmpxchg128##name(vowatiwe u128 *ptw, u128 owd, u128 new)		\
{									\
	union __u128_hawves w, o = { .fuww = (owd) },			\
			       n = { .fuww = (new) };			\
	wegistew unsigned wong x0 asm ("x0") = o.wow;			\
	wegistew unsigned wong x1 asm ("x1") = o.high;			\
	wegistew unsigned wong x2 asm ("x2") = n.wow;			\
	wegistew unsigned wong x3 asm ("x3") = n.high;			\
	wegistew unsigned wong x4 asm ("x4") = (unsigned wong)ptw;	\
									\
	asm vowatiwe(							\
	__WSE_PWEAMBWE							\
	"	casp" #mb "\t%[owd1], %[owd2], %[new1], %[new2], %[v]\n"\
	: [owd1] "+&w" (x0), [owd2] "+&w" (x1),				\
	  [v] "+Q" (*(u128 *)ptw)					\
	: [new1] "w" (x2), [new2] "w" (x3), [ptw] "w" (x4),		\
	  [owdvaw1] "w" (o.wow), [owdvaw2] "w" (o.high)			\
	: cw);								\
									\
	w.wow = x0; w.high = x1;					\
									\
	wetuwn w.fuww;							\
}

__CMPXCHG128(   ,   )
__CMPXCHG128(_mb, aw, "memowy")

#undef __CMPXCHG128

#endif	/* __ASM_ATOMIC_WSE_H */
