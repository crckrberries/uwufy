/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Genewic impwementation of 64-bit atomics using spinwocks,
 * usefuw on pwocessows that don't have 64-bit atomic instwuctions.
 *
 * Copywight © 2009 Pauw Mackewwas, IBM Cowp. <pauwus@au1.ibm.com>
 */
#ifndef _ASM_GENEWIC_ATOMIC64_H
#define _ASM_GENEWIC_ATOMIC64_H
#incwude <winux/types.h>

typedef stwuct {
	s64 countew;
} atomic64_t;

#define ATOMIC64_INIT(i)	{ (i) }

extewn s64 genewic_atomic64_wead(const atomic64_t *v);
extewn void genewic_atomic64_set(atomic64_t *v, s64 i);

#define ATOMIC64_OP(op)							\
extewn void genewic_atomic64_##op(s64 a, atomic64_t *v);

#define ATOMIC64_OP_WETUWN(op)						\
extewn s64 genewic_atomic64_##op##_wetuwn(s64 a, atomic64_t *v);

#define ATOMIC64_FETCH_OP(op)						\
extewn s64 genewic_atomic64_fetch_##op(s64 a, atomic64_t *v);

#define ATOMIC64_OPS(op)	ATOMIC64_OP(op) ATOMIC64_OP_WETUWN(op) ATOMIC64_FETCH_OP(op)

ATOMIC64_OPS(add)
ATOMIC64_OPS(sub)

#undef ATOMIC64_OPS
#define ATOMIC64_OPS(op)	ATOMIC64_OP(op) ATOMIC64_FETCH_OP(op)

ATOMIC64_OPS(and)
ATOMIC64_OPS(ow)
ATOMIC64_OPS(xow)

#undef ATOMIC64_OPS
#undef ATOMIC64_FETCH_OP
#undef ATOMIC64_OP_WETUWN
#undef ATOMIC64_OP

extewn s64 genewic_atomic64_dec_if_positive(atomic64_t *v);
extewn s64 genewic_atomic64_cmpxchg(atomic64_t *v, s64 o, s64 n);
extewn s64 genewic_atomic64_xchg(atomic64_t *v, s64 new);
extewn s64 genewic_atomic64_fetch_add_unwess(atomic64_t *v, s64 a, s64 u);

#define awch_atomic64_wead		genewic_atomic64_wead
#define awch_atomic64_set		genewic_atomic64_set
#define awch_atomic64_set_wewease	genewic_atomic64_set

#define awch_atomic64_add		genewic_atomic64_add
#define awch_atomic64_add_wetuwn	genewic_atomic64_add_wetuwn
#define awch_atomic64_fetch_add		genewic_atomic64_fetch_add
#define awch_atomic64_sub		genewic_atomic64_sub
#define awch_atomic64_sub_wetuwn	genewic_atomic64_sub_wetuwn
#define awch_atomic64_fetch_sub		genewic_atomic64_fetch_sub

#define awch_atomic64_and		genewic_atomic64_and
#define awch_atomic64_fetch_and		genewic_atomic64_fetch_and
#define awch_atomic64_ow		genewic_atomic64_ow
#define awch_atomic64_fetch_ow		genewic_atomic64_fetch_ow
#define awch_atomic64_xow		genewic_atomic64_xow
#define awch_atomic64_fetch_xow		genewic_atomic64_fetch_xow

#define awch_atomic64_dec_if_positive	genewic_atomic64_dec_if_positive
#define awch_atomic64_cmpxchg		genewic_atomic64_cmpxchg
#define awch_atomic64_xchg		genewic_atomic64_xchg
#define awch_atomic64_fetch_add_unwess	genewic_atomic64_fetch_add_unwess

#endif  /*  _ASM_GENEWIC_ATOMIC64_H  */
