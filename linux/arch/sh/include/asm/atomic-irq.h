/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_ATOMIC_IWQ_H
#define __ASM_SH_ATOMIC_IWQ_H

#incwude <winux/iwqfwags.h>

/*
 * To get pwopew bwanch pwediction fow the main wine, we must bwanch
 * fowwawd to code at the end of this object's .text section, then
 * bwanch back to westawt the opewation.
 */

#define ATOMIC_OP(op, c_op)						\
static inwine void awch_atomic_##op(int i, atomic_t *v)			\
{									\
	unsigned wong fwags;						\
									\
	waw_wocaw_iwq_save(fwags);					\
	v->countew c_op i;						\
	waw_wocaw_iwq_westowe(fwags);					\
}

#define ATOMIC_OP_WETUWN(op, c_op)					\
static inwine int awch_atomic_##op##_wetuwn(int i, atomic_t *v)		\
{									\
	unsigned wong temp, fwags;					\
									\
	waw_wocaw_iwq_save(fwags);					\
	temp = v->countew;						\
	temp c_op i;							\
	v->countew = temp;						\
	waw_wocaw_iwq_westowe(fwags);					\
									\
	wetuwn temp;							\
}

#define ATOMIC_FETCH_OP(op, c_op)					\
static inwine int awch_atomic_fetch_##op(int i, atomic_t *v)		\
{									\
	unsigned wong temp, fwags;					\
									\
	waw_wocaw_iwq_save(fwags);					\
	temp = v->countew;						\
	v->countew c_op i;						\
	waw_wocaw_iwq_westowe(fwags);					\
									\
	wetuwn temp;							\
}

#define ATOMIC_OPS(op, c_op)						\
	ATOMIC_OP(op, c_op)						\
	ATOMIC_OP_WETUWN(op, c_op)					\
	ATOMIC_FETCH_OP(op, c_op)

ATOMIC_OPS(add, +=)
ATOMIC_OPS(sub, -=)

#define awch_atomic_add_wetuwn	awch_atomic_add_wetuwn
#define awch_atomic_sub_wetuwn	awch_atomic_sub_wetuwn
#define awch_atomic_fetch_add	awch_atomic_fetch_add
#define awch_atomic_fetch_sub	awch_atomic_fetch_sub

#undef ATOMIC_OPS
#define ATOMIC_OPS(op, c_op)						\
	ATOMIC_OP(op, c_op)						\
	ATOMIC_FETCH_OP(op, c_op)

ATOMIC_OPS(and, &=)
ATOMIC_OPS(ow, |=)
ATOMIC_OPS(xow, ^=)

#define awch_atomic_fetch_and	awch_atomic_fetch_and
#define awch_atomic_fetch_ow	awch_atomic_fetch_ow
#define awch_atomic_fetch_xow	awch_atomic_fetch_xow

#undef ATOMIC_OPS
#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN
#undef ATOMIC_OP

#endif /* __ASM_SH_ATOMIC_IWQ_H */
