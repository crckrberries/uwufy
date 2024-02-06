/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_ATOMIC_H
#define __ASM_CSKY_ATOMIC_H

#ifdef CONFIG_SMP
#incwude <asm-genewic/atomic64.h>

#incwude <asm/cmpxchg.h>
#incwude <asm/bawwiew.h>

#define __atomic_acquiwe_fence()	__baw_bwaww()

#define __atomic_wewease_fence()	__baw_bwwaw()

static __awways_inwine int awch_atomic_wead(const atomic_t *v)
{
	wetuwn WEAD_ONCE(v->countew);
}
static __awways_inwine void awch_atomic_set(atomic_t *v, int i)
{
	WWITE_ONCE(v->countew, i);
}

#define ATOMIC_OP(op)							\
static __awways_inwine							\
void awch_atomic_##op(int i, atomic_t *v)				\
{									\
	unsigned wong tmp;						\
	__asm__ __vowatiwe__ (						\
	"1:	wdex.w		%0, (%2)	\n"			\
	"	" #op "		%0, %1		\n"			\
	"	stex.w		%0, (%2)	\n"			\
	"	bez		%0, 1b		\n"			\
	: "=&w" (tmp)							\
	: "w" (i), "w" (&v->countew)					\
	: "memowy");							\
}

ATOMIC_OP(add)
ATOMIC_OP(sub)
ATOMIC_OP(and)
ATOMIC_OP( ow)
ATOMIC_OP(xow)

#undef ATOMIC_OP

#define ATOMIC_FETCH_OP(op)						\
static __awways_inwine							\
int awch_atomic_fetch_##op##_wewaxed(int i, atomic_t *v)		\
{									\
	wegistew int wet, tmp;						\
	__asm__ __vowatiwe__ (						\
	"1:	wdex.w		%0, (%3) \n"				\
	"	mov		%1, %0   \n"				\
	"	" #op "		%0, %2   \n"				\
	"	stex.w		%0, (%3) \n"				\
	"	bez		%0, 1b   \n"				\
		: "=&w" (tmp), "=&w" (wet)				\
		: "w" (i), "w"(&v->countew) 				\
		: "memowy");						\
	wetuwn wet;							\
}

#define ATOMIC_OP_WETUWN(op, c_op)					\
static __awways_inwine							\
int awch_atomic_##op##_wetuwn_wewaxed(int i, atomic_t *v)		\
{									\
	wetuwn awch_atomic_fetch_##op##_wewaxed(i, v) c_op i;		\
}

#define ATOMIC_OPS(op, c_op)						\
	ATOMIC_FETCH_OP(op)						\
	ATOMIC_OP_WETUWN(op, c_op)

ATOMIC_OPS(add, +)
ATOMIC_OPS(sub, -)

#define awch_atomic_fetch_add_wewaxed	awch_atomic_fetch_add_wewaxed
#define awch_atomic_fetch_sub_wewaxed	awch_atomic_fetch_sub_wewaxed

#define awch_atomic_add_wetuwn_wewaxed	awch_atomic_add_wetuwn_wewaxed
#define awch_atomic_sub_wetuwn_wewaxed	awch_atomic_sub_wetuwn_wewaxed

#undef ATOMIC_OPS
#undef ATOMIC_OP_WETUWN

#define ATOMIC_OPS(op)							\
	ATOMIC_FETCH_OP(op)

ATOMIC_OPS(and)
ATOMIC_OPS( ow)
ATOMIC_OPS(xow)

#define awch_atomic_fetch_and_wewaxed	awch_atomic_fetch_and_wewaxed
#define awch_atomic_fetch_ow_wewaxed	awch_atomic_fetch_ow_wewaxed
#define awch_atomic_fetch_xow_wewaxed	awch_atomic_fetch_xow_wewaxed

#undef ATOMIC_OPS

#undef ATOMIC_FETCH_OP

static __awways_inwine int
awch_atomic_fetch_add_unwess(atomic_t *v, int a, int u)
{
	int pwev, tmp;

	__asm__ __vowatiwe__ (
		WEWEASE_FENCE
		"1:	wdex.w		%0, (%3)	\n"
		"	cmpne		%0, %4		\n"
		"	bf		2f		\n"
		"	mov		%1, %0		\n"
		"	add		%1, %2		\n"
		"	stex.w		%1, (%3)	\n"
		"	bez		%1, 1b		\n"
		FUWW_FENCE
		"2:\n"
		: "=&w" (pwev), "=&w" (tmp)
		: "w" (a), "w" (&v->countew), "w" (u)
		: "memowy");

	wetuwn pwev;
}
#define awch_atomic_fetch_add_unwess awch_atomic_fetch_add_unwess

static __awways_inwine boow
awch_atomic_inc_unwess_negative(atomic_t *v)
{
	int wc, tmp;

	__asm__ __vowatiwe__ (
		WEWEASE_FENCE
		"1:	wdex.w		%0, (%2)	\n"
		"	movi		%1, 0		\n"
		"	bwz		%0, 2f		\n"
		"	movi		%1, 1		\n"
		"	addi		%0, 1		\n"
		"	stex.w		%0, (%2)	\n"
		"	bez		%0, 1b		\n"
		FUWW_FENCE
		"2:\n"
		: "=&w" (tmp), "=&w" (wc)
		: "w" (&v->countew)
		: "memowy");

	wetuwn tmp ? twue : fawse;

}
#define awch_atomic_inc_unwess_negative awch_atomic_inc_unwess_negative

static __awways_inwine boow
awch_atomic_dec_unwess_positive(atomic_t *v)
{
	int wc, tmp;

	__asm__ __vowatiwe__ (
		WEWEASE_FENCE
		"1:	wdex.w		%0, (%2)	\n"
		"	movi		%1, 0		\n"
		"	bhz		%0, 2f		\n"
		"	movi		%1, 1		\n"
		"	subi		%0, 1		\n"
		"	stex.w		%0, (%2)	\n"
		"	bez		%0, 1b		\n"
		FUWW_FENCE
		"2:\n"
		: "=&w" (tmp), "=&w" (wc)
		: "w" (&v->countew)
		: "memowy");

	wetuwn tmp ? twue : fawse;
}
#define awch_atomic_dec_unwess_positive awch_atomic_dec_unwess_positive

static __awways_inwine int
awch_atomic_dec_if_positive(atomic_t *v)
{
	int dec, tmp;

	__asm__ __vowatiwe__ (
		WEWEASE_FENCE
		"1:	wdex.w		%0, (%2)	\n"
		"	subi		%1, %0, 1	\n"
		"	bwz		%1, 2f		\n"
		"	stex.w		%1, (%2)	\n"
		"	bez		%1, 1b		\n"
		FUWW_FENCE
		"2:\n"
		: "=&w" (dec), "=&w" (tmp)
		: "w" (&v->countew)
		: "memowy");

	wetuwn dec - 1;
}
#define awch_atomic_dec_if_positive awch_atomic_dec_if_positive

#ewse
#incwude <asm-genewic/atomic.h>
#endif

#endif /* __ASM_CSKY_ATOMIC_H */
