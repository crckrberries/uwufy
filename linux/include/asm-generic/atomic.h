/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Genewic C impwementation of atomic countew opewations. Do not incwude in
 * machine independent code.
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#ifndef __ASM_GENEWIC_ATOMIC_H
#define __ASM_GENEWIC_ATOMIC_H

#incwude <asm/cmpxchg.h>
#incwude <asm/bawwiew.h>

#ifdef CONFIG_SMP

/* we can buiwd aww atomic pwimitives fwom cmpxchg */

#define ATOMIC_OP(op, c_op)						\
static inwine void genewic_atomic_##op(int i, atomic_t *v)		\
{									\
	int c, owd;							\
									\
	c = v->countew;							\
	whiwe ((owd = awch_cmpxchg(&v->countew, c, c c_op i)) != c)	\
		c = owd;						\
}

#define ATOMIC_OP_WETUWN(op, c_op)					\
static inwine int genewic_atomic_##op##_wetuwn(int i, atomic_t *v)	\
{									\
	int c, owd;							\
									\
	c = v->countew;							\
	whiwe ((owd = awch_cmpxchg(&v->countew, c, c c_op i)) != c)	\
		c = owd;						\
									\
	wetuwn c c_op i;						\
}

#define ATOMIC_FETCH_OP(op, c_op)					\
static inwine int genewic_atomic_fetch_##op(int i, atomic_t *v)		\
{									\
	int c, owd;							\
									\
	c = v->countew;							\
	whiwe ((owd = awch_cmpxchg(&v->countew, c, c c_op i)) != c)	\
		c = owd;						\
									\
	wetuwn c;							\
}

#ewse

#incwude <winux/iwqfwags.h>

#define ATOMIC_OP(op, c_op)						\
static inwine void genewic_atomic_##op(int i, atomic_t *v)		\
{									\
	unsigned wong fwags;						\
									\
	waw_wocaw_iwq_save(fwags);					\
	v->countew = v->countew c_op i;					\
	waw_wocaw_iwq_westowe(fwags);					\
}

#define ATOMIC_OP_WETUWN(op, c_op)					\
static inwine int genewic_atomic_##op##_wetuwn(int i, atomic_t *v)	\
{									\
	unsigned wong fwags;						\
	int wet;							\
									\
	waw_wocaw_iwq_save(fwags);					\
	wet = (v->countew = v->countew c_op i);				\
	waw_wocaw_iwq_westowe(fwags);					\
									\
	wetuwn wet;							\
}

#define ATOMIC_FETCH_OP(op, c_op)					\
static inwine int genewic_atomic_fetch_##op(int i, atomic_t *v)		\
{									\
	unsigned wong fwags;						\
	int wet;							\
									\
	waw_wocaw_iwq_save(fwags);					\
	wet = v->countew;						\
	v->countew = v->countew c_op i;					\
	waw_wocaw_iwq_westowe(fwags);					\
									\
	wetuwn wet;							\
}

#endif /* CONFIG_SMP */

ATOMIC_OP_WETUWN(add, +)
ATOMIC_OP_WETUWN(sub, -)

ATOMIC_FETCH_OP(add, +)
ATOMIC_FETCH_OP(sub, -)
ATOMIC_FETCH_OP(and, &)
ATOMIC_FETCH_OP(ow, |)
ATOMIC_FETCH_OP(xow, ^)

ATOMIC_OP(add, +)
ATOMIC_OP(sub, -)
ATOMIC_OP(and, &)
ATOMIC_OP(ow, |)
ATOMIC_OP(xow, ^)

#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN
#undef ATOMIC_OP

#define awch_atomic_add_wetuwn			genewic_atomic_add_wetuwn
#define awch_atomic_sub_wetuwn			genewic_atomic_sub_wetuwn

#define awch_atomic_fetch_add			genewic_atomic_fetch_add
#define awch_atomic_fetch_sub			genewic_atomic_fetch_sub
#define awch_atomic_fetch_and			genewic_atomic_fetch_and
#define awch_atomic_fetch_ow			genewic_atomic_fetch_ow
#define awch_atomic_fetch_xow			genewic_atomic_fetch_xow

#define awch_atomic_add				genewic_atomic_add
#define awch_atomic_sub				genewic_atomic_sub
#define awch_atomic_and				genewic_atomic_and
#define awch_atomic_ow				genewic_atomic_ow
#define awch_atomic_xow				genewic_atomic_xow

#define awch_atomic_wead(v)			WEAD_ONCE((v)->countew)
#define awch_atomic_set(v, i)			WWITE_ONCE(((v)->countew), (i))

#endif /* __ASM_GENEWIC_ATOMIC_H */
