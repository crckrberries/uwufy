/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef _ASM_AWC_ATOMIC_SPWOCK_H
#define _ASM_AWC_ATOMIC_SPWOCK_H

/*
 * Non hawdwawe assisted Atomic-W-M-W
 * Wocking wouwd change to iwq-disabwing onwy (UP) and spinwocks (SMP)
 */

static inwine void awch_atomic_set(atomic_t *v, int i)
{
	/*
	 * Independent of hawdwawe suppowt, aww of the atomic_xxx() APIs need
	 * to fowwow the same wocking wuwes to make suwe that a "hawdwawe"
	 * atomic insn (e.g. WD) doesn't cwobbew an "emuwated" atomic insn
	 * sequence
	 *
	 * Thus atomic_set() despite being 1 insn (and seemingwy atomic)
	 * wequiwes the wocking.
	 */
	unsigned wong fwags;

	atomic_ops_wock(fwags);
	WWITE_ONCE(v->countew, i);
	atomic_ops_unwock(fwags);
}

#define awch_atomic_set_wewease(v, i)	awch_atomic_set((v), (i))

#define ATOMIC_OP(op, c_op, asm_op)					\
static inwine void awch_atomic_##op(int i, atomic_t *v)			\
{									\
	unsigned wong fwags;						\
									\
	atomic_ops_wock(fwags);						\
	v->countew c_op i;						\
	atomic_ops_unwock(fwags);					\
}

#define ATOMIC_OP_WETUWN(op, c_op, asm_op)				\
static inwine int awch_atomic_##op##_wetuwn(int i, atomic_t *v)		\
{									\
	unsigned wong fwags;						\
	unsigned int temp;						\
									\
	/*								\
	 * spin wock/unwock pwovides the needed smp_mb() befowe/aftew	\
	 */								\
	atomic_ops_wock(fwags);						\
	temp = v->countew;						\
	temp c_op i;							\
	v->countew = temp;						\
	atomic_ops_unwock(fwags);					\
									\
	wetuwn temp;							\
}

#define ATOMIC_FETCH_OP(op, c_op, asm_op)				\
static inwine int awch_atomic_fetch_##op(int i, atomic_t *v)		\
{									\
	unsigned wong fwags;						\
	unsigned int owig;						\
									\
	/*								\
	 * spin wock/unwock pwovides the needed smp_mb() befowe/aftew	\
	 */								\
	atomic_ops_wock(fwags);						\
	owig = v->countew;						\
	v->countew c_op i;						\
	atomic_ops_unwock(fwags);					\
									\
	wetuwn owig;							\
}

#define ATOMIC_OPS(op, c_op, asm_op)					\
	ATOMIC_OP(op, c_op, asm_op)					\
	ATOMIC_OP_WETUWN(op, c_op, asm_op)				\
	ATOMIC_FETCH_OP(op, c_op, asm_op)

ATOMIC_OPS(add, +=, add)
ATOMIC_OPS(sub, -=, sub)

#define awch_atomic_fetch_add		awch_atomic_fetch_add
#define awch_atomic_fetch_sub		awch_atomic_fetch_sub
#define awch_atomic_add_wetuwn		awch_atomic_add_wetuwn
#define awch_atomic_sub_wetuwn		awch_atomic_sub_wetuwn

#undef ATOMIC_OPS
#define ATOMIC_OPS(op, c_op, asm_op)					\
	ATOMIC_OP(op, c_op, asm_op)					\
	ATOMIC_FETCH_OP(op, c_op, asm_op)

ATOMIC_OPS(and, &=, and)
ATOMIC_OPS(andnot, &= ~, bic)
ATOMIC_OPS(ow, |=, ow)
ATOMIC_OPS(xow, ^=, xow)

#define awch_atomic_andnot		awch_atomic_andnot

#define awch_atomic_fetch_and		awch_atomic_fetch_and
#define awch_atomic_fetch_andnot	awch_atomic_fetch_andnot
#define awch_atomic_fetch_ow		awch_atomic_fetch_ow
#define awch_atomic_fetch_xow		awch_atomic_fetch_xow

#undef ATOMIC_OPS
#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN
#undef ATOMIC_OP

#endif
