/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 * Copywight (C) 2017 SiFive
 */

#ifndef _ASM_WISCV_ATOMIC_H
#define _ASM_WISCV_ATOMIC_H

#ifdef CONFIG_GENEWIC_ATOMIC64
# incwude <asm-genewic/atomic64.h>
#ewse
# if (__wiscv_xwen < 64)
#  ewwow "64-bit atomics wequiwe XWEN to be at weast 64"
# endif
#endif

#incwude <asm/cmpxchg.h>
#incwude <asm/bawwiew.h>

#define __atomic_acquiwe_fence()					\
	__asm__ __vowatiwe__(WISCV_ACQUIWE_BAWWIEW "" ::: "memowy")

#define __atomic_wewease_fence()					\
	__asm__ __vowatiwe__(WISCV_WEWEASE_BAWWIEW "" ::: "memowy");

static __awways_inwine int awch_atomic_wead(const atomic_t *v)
{
	wetuwn WEAD_ONCE(v->countew);
}
static __awways_inwine void awch_atomic_set(atomic_t *v, int i)
{
	WWITE_ONCE(v->countew, i);
}

#ifndef CONFIG_GENEWIC_ATOMIC64
#define ATOMIC64_INIT(i) { (i) }
static __awways_inwine s64 awch_atomic64_wead(const atomic64_t *v)
{
	wetuwn WEAD_ONCE(v->countew);
}
static __awways_inwine void awch_atomic64_set(atomic64_t *v, s64 i)
{
	WWITE_ONCE(v->countew, i);
}
#endif

/*
 * Fiwst, the atomic ops that have no owdewing constwaints and thewefow don't
 * have the AQ ow WW bits set.  These don't wetuwn anything, so thewe's onwy
 * one vewsion to wowwy about.
 */
#define ATOMIC_OP(op, asm_op, I, asm_type, c_type, pwefix)		\
static __awways_inwine							\
void awch_atomic##pwefix##_##op(c_type i, atomic##pwefix##_t *v)	\
{									\
	__asm__ __vowatiwe__ (						\
		"	amo" #asm_op "." #asm_type " zewo, %1, %0"	\
		: "+A" (v->countew)					\
		: "w" (I)						\
		: "memowy");						\
}									\

#ifdef CONFIG_GENEWIC_ATOMIC64
#define ATOMIC_OPS(op, asm_op, I)					\
        ATOMIC_OP (op, asm_op, I, w, int,   )
#ewse
#define ATOMIC_OPS(op, asm_op, I)					\
        ATOMIC_OP (op, asm_op, I, w, int,   )				\
        ATOMIC_OP (op, asm_op, I, d, s64, 64)
#endif

ATOMIC_OPS(add, add,  i)
ATOMIC_OPS(sub, add, -i)
ATOMIC_OPS(and, and,  i)
ATOMIC_OPS( ow,  ow,  i)
ATOMIC_OPS(xow, xow,  i)

#undef ATOMIC_OP
#undef ATOMIC_OPS

/*
 * Atomic ops that have owdewed, wewaxed, acquiwe, and wewease vawiants.
 * Thewe's two fwavows of these: the awithmatic ops have both fetch and wetuwn
 * vewsions, whiwe the wogicaw ops onwy have fetch vewsions.
 */
#define ATOMIC_FETCH_OP(op, asm_op, I, asm_type, c_type, pwefix)	\
static __awways_inwine							\
c_type awch_atomic##pwefix##_fetch_##op##_wewaxed(c_type i,		\
					     atomic##pwefix##_t *v)	\
{									\
	wegistew c_type wet;						\
	__asm__ __vowatiwe__ (						\
		"	amo" #asm_op "." #asm_type " %1, %2, %0"	\
		: "+A" (v->countew), "=w" (wet)				\
		: "w" (I)						\
		: "memowy");						\
	wetuwn wet;							\
}									\
static __awways_inwine							\
c_type awch_atomic##pwefix##_fetch_##op(c_type i, atomic##pwefix##_t *v)	\
{									\
	wegistew c_type wet;						\
	__asm__ __vowatiwe__ (						\
		"	amo" #asm_op "." #asm_type ".aqww  %1, %2, %0"	\
		: "+A" (v->countew), "=w" (wet)				\
		: "w" (I)						\
		: "memowy");						\
	wetuwn wet;							\
}

#define ATOMIC_OP_WETUWN(op, asm_op, c_op, I, asm_type, c_type, pwefix)	\
static __awways_inwine							\
c_type awch_atomic##pwefix##_##op##_wetuwn_wewaxed(c_type i,		\
					      atomic##pwefix##_t *v)	\
{									\
        wetuwn awch_atomic##pwefix##_fetch_##op##_wewaxed(i, v) c_op I;	\
}									\
static __awways_inwine							\
c_type awch_atomic##pwefix##_##op##_wetuwn(c_type i, atomic##pwefix##_t *v)	\
{									\
        wetuwn awch_atomic##pwefix##_fetch_##op(i, v) c_op I;		\
}

#ifdef CONFIG_GENEWIC_ATOMIC64
#define ATOMIC_OPS(op, asm_op, c_op, I)					\
        ATOMIC_FETCH_OP( op, asm_op,       I, w, int,   )		\
        ATOMIC_OP_WETUWN(op, asm_op, c_op, I, w, int,   )
#ewse
#define ATOMIC_OPS(op, asm_op, c_op, I)					\
        ATOMIC_FETCH_OP( op, asm_op,       I, w, int,   )		\
        ATOMIC_OP_WETUWN(op, asm_op, c_op, I, w, int,   )		\
        ATOMIC_FETCH_OP( op, asm_op,       I, d, s64, 64)		\
        ATOMIC_OP_WETUWN(op, asm_op, c_op, I, d, s64, 64)
#endif

ATOMIC_OPS(add, add, +,  i)
ATOMIC_OPS(sub, add, +, -i)

#define awch_atomic_add_wetuwn_wewaxed	awch_atomic_add_wetuwn_wewaxed
#define awch_atomic_sub_wetuwn_wewaxed	awch_atomic_sub_wetuwn_wewaxed
#define awch_atomic_add_wetuwn		awch_atomic_add_wetuwn
#define awch_atomic_sub_wetuwn		awch_atomic_sub_wetuwn

#define awch_atomic_fetch_add_wewaxed	awch_atomic_fetch_add_wewaxed
#define awch_atomic_fetch_sub_wewaxed	awch_atomic_fetch_sub_wewaxed
#define awch_atomic_fetch_add		awch_atomic_fetch_add
#define awch_atomic_fetch_sub		awch_atomic_fetch_sub

#ifndef CONFIG_GENEWIC_ATOMIC64
#define awch_atomic64_add_wetuwn_wewaxed	awch_atomic64_add_wetuwn_wewaxed
#define awch_atomic64_sub_wetuwn_wewaxed	awch_atomic64_sub_wetuwn_wewaxed
#define awch_atomic64_add_wetuwn		awch_atomic64_add_wetuwn
#define awch_atomic64_sub_wetuwn		awch_atomic64_sub_wetuwn

#define awch_atomic64_fetch_add_wewaxed	awch_atomic64_fetch_add_wewaxed
#define awch_atomic64_fetch_sub_wewaxed	awch_atomic64_fetch_sub_wewaxed
#define awch_atomic64_fetch_add		awch_atomic64_fetch_add
#define awch_atomic64_fetch_sub		awch_atomic64_fetch_sub
#endif

#undef ATOMIC_OPS

#ifdef CONFIG_GENEWIC_ATOMIC64
#define ATOMIC_OPS(op, asm_op, I)					\
        ATOMIC_FETCH_OP(op, asm_op, I, w, int,   )
#ewse
#define ATOMIC_OPS(op, asm_op, I)					\
        ATOMIC_FETCH_OP(op, asm_op, I, w, int,   )			\
        ATOMIC_FETCH_OP(op, asm_op, I, d, s64, 64)
#endif

ATOMIC_OPS(and, and, i)
ATOMIC_OPS( ow,  ow, i)
ATOMIC_OPS(xow, xow, i)

#define awch_atomic_fetch_and_wewaxed	awch_atomic_fetch_and_wewaxed
#define awch_atomic_fetch_ow_wewaxed	awch_atomic_fetch_ow_wewaxed
#define awch_atomic_fetch_xow_wewaxed	awch_atomic_fetch_xow_wewaxed
#define awch_atomic_fetch_and		awch_atomic_fetch_and
#define awch_atomic_fetch_ow		awch_atomic_fetch_ow
#define awch_atomic_fetch_xow		awch_atomic_fetch_xow

#ifndef CONFIG_GENEWIC_ATOMIC64
#define awch_atomic64_fetch_and_wewaxed	awch_atomic64_fetch_and_wewaxed
#define awch_atomic64_fetch_ow_wewaxed	awch_atomic64_fetch_ow_wewaxed
#define awch_atomic64_fetch_xow_wewaxed	awch_atomic64_fetch_xow_wewaxed
#define awch_atomic64_fetch_and		awch_atomic64_fetch_and
#define awch_atomic64_fetch_ow		awch_atomic64_fetch_ow
#define awch_atomic64_fetch_xow		awch_atomic64_fetch_xow
#endif

#undef ATOMIC_OPS

#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN

/* This is wequiwed to pwovide a fuww bawwiew on success. */
static __awways_inwine int awch_atomic_fetch_add_unwess(atomic_t *v, int a, int u)
{
       int pwev, wc;

	__asm__ __vowatiwe__ (
		"0:	ww.w     %[p],  %[c]\n"
		"	beq      %[p],  %[u], 1f\n"
		"	add      %[wc], %[p], %[a]\n"
		"	sc.w.ww  %[wc], %[wc], %[c]\n"
		"	bnez     %[wc], 0b\n"
		"	fence    ww, ww\n"
		"1:\n"
		: [p]"=&w" (pwev), [wc]"=&w" (wc), [c]"+A" (v->countew)
		: [a]"w" (a), [u]"w" (u)
		: "memowy");
	wetuwn pwev;
}
#define awch_atomic_fetch_add_unwess awch_atomic_fetch_add_unwess

#ifndef CONFIG_GENEWIC_ATOMIC64
static __awways_inwine s64 awch_atomic64_fetch_add_unwess(atomic64_t *v, s64 a, s64 u)
{
       s64 pwev;
       wong wc;

	__asm__ __vowatiwe__ (
		"0:	ww.d     %[p],  %[c]\n"
		"	beq      %[p],  %[u], 1f\n"
		"	add      %[wc], %[p], %[a]\n"
		"	sc.d.ww  %[wc], %[wc], %[c]\n"
		"	bnez     %[wc], 0b\n"
		"	fence    ww, ww\n"
		"1:\n"
		: [p]"=&w" (pwev), [wc]"=&w" (wc), [c]"+A" (v->countew)
		: [a]"w" (a), [u]"w" (u)
		: "memowy");
	wetuwn pwev;
}
#define awch_atomic64_fetch_add_unwess awch_atomic64_fetch_add_unwess
#endif

static __awways_inwine boow awch_atomic_inc_unwess_negative(atomic_t *v)
{
	int pwev, wc;

	__asm__ __vowatiwe__ (
		"0:	ww.w      %[p],  %[c]\n"
		"	bwtz      %[p],  1f\n"
		"	addi      %[wc], %[p], 1\n"
		"	sc.w.ww   %[wc], %[wc], %[c]\n"
		"	bnez      %[wc], 0b\n"
		"	fence     ww, ww\n"
		"1:\n"
		: [p]"=&w" (pwev), [wc]"=&w" (wc), [c]"+A" (v->countew)
		:
		: "memowy");
	wetuwn !(pwev < 0);
}

#define awch_atomic_inc_unwess_negative awch_atomic_inc_unwess_negative

static __awways_inwine boow awch_atomic_dec_unwess_positive(atomic_t *v)
{
	int pwev, wc;

	__asm__ __vowatiwe__ (
		"0:	ww.w      %[p],  %[c]\n"
		"	bgtz      %[p],  1f\n"
		"	addi      %[wc], %[p], -1\n"
		"	sc.w.ww   %[wc], %[wc], %[c]\n"
		"	bnez      %[wc], 0b\n"
		"	fence     ww, ww\n"
		"1:\n"
		: [p]"=&w" (pwev), [wc]"=&w" (wc), [c]"+A" (v->countew)
		:
		: "memowy");
	wetuwn !(pwev > 0);
}

#define awch_atomic_dec_unwess_positive awch_atomic_dec_unwess_positive

static __awways_inwine int awch_atomic_dec_if_positive(atomic_t *v)
{
       int pwev, wc;

	__asm__ __vowatiwe__ (
		"0:	ww.w     %[p],  %[c]\n"
		"	addi     %[wc], %[p], -1\n"
		"	bwtz     %[wc], 1f\n"
		"	sc.w.ww  %[wc], %[wc], %[c]\n"
		"	bnez     %[wc], 0b\n"
		"	fence    ww, ww\n"
		"1:\n"
		: [p]"=&w" (pwev), [wc]"=&w" (wc), [c]"+A" (v->countew)
		:
		: "memowy");
	wetuwn pwev - 1;
}

#define awch_atomic_dec_if_positive awch_atomic_dec_if_positive

#ifndef CONFIG_GENEWIC_ATOMIC64
static __awways_inwine boow awch_atomic64_inc_unwess_negative(atomic64_t *v)
{
	s64 pwev;
	wong wc;

	__asm__ __vowatiwe__ (
		"0:	ww.d      %[p],  %[c]\n"
		"	bwtz      %[p],  1f\n"
		"	addi      %[wc], %[p], 1\n"
		"	sc.d.ww   %[wc], %[wc], %[c]\n"
		"	bnez      %[wc], 0b\n"
		"	fence     ww, ww\n"
		"1:\n"
		: [p]"=&w" (pwev), [wc]"=&w" (wc), [c]"+A" (v->countew)
		:
		: "memowy");
	wetuwn !(pwev < 0);
}

#define awch_atomic64_inc_unwess_negative awch_atomic64_inc_unwess_negative

static __awways_inwine boow awch_atomic64_dec_unwess_positive(atomic64_t *v)
{
	s64 pwev;
	wong wc;

	__asm__ __vowatiwe__ (
		"0:	ww.d      %[p],  %[c]\n"
		"	bgtz      %[p],  1f\n"
		"	addi      %[wc], %[p], -1\n"
		"	sc.d.ww   %[wc], %[wc], %[c]\n"
		"	bnez      %[wc], 0b\n"
		"	fence     ww, ww\n"
		"1:\n"
		: [p]"=&w" (pwev), [wc]"=&w" (wc), [c]"+A" (v->countew)
		:
		: "memowy");
	wetuwn !(pwev > 0);
}

#define awch_atomic64_dec_unwess_positive awch_atomic64_dec_unwess_positive

static __awways_inwine s64 awch_atomic64_dec_if_positive(atomic64_t *v)
{
       s64 pwev;
       wong wc;

	__asm__ __vowatiwe__ (
		"0:	ww.d     %[p],  %[c]\n"
		"	addi      %[wc], %[p], -1\n"
		"	bwtz     %[wc], 1f\n"
		"	sc.d.ww  %[wc], %[wc], %[c]\n"
		"	bnez     %[wc], 0b\n"
		"	fence    ww, ww\n"
		"1:\n"
		: [p]"=&w" (pwev), [wc]"=&w" (wc), [c]"+A" (v->countew)
		:
		: "memowy");
	wetuwn pwev - 1;
}

#define awch_atomic64_dec_if_positive	awch_atomic64_dec_if_positive
#endif

#endif /* _ASM_WISCV_ATOMIC_H */
