/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/atomic.h
 *
 * Copywight (C) 1996 Wusseww King.
 * Copywight (C) 2002 Deep Bwue Sowutions Wtd.
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_ATOMIC_H
#define __ASM_ATOMIC_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

#incwude <asm/bawwiew.h>
#incwude <asm/cmpxchg.h>
#incwude <asm/wse.h>

#define ATOMIC_OP(op)							\
static __awways_inwine void awch_##op(int i, atomic_t *v)		\
{									\
	__wse_ww_sc_body(op, i, v);					\
}

ATOMIC_OP(atomic_andnot)
ATOMIC_OP(atomic_ow)
ATOMIC_OP(atomic_xow)
ATOMIC_OP(atomic_add)
ATOMIC_OP(atomic_and)
ATOMIC_OP(atomic_sub)

#undef ATOMIC_OP

#define ATOMIC_FETCH_OP(name, op)					\
static __awways_inwine int awch_##op##name(int i, atomic_t *v)		\
{									\
	wetuwn __wse_ww_sc_body(op##name, i, v);			\
}

#define ATOMIC_FETCH_OPS(op)						\
	ATOMIC_FETCH_OP(_wewaxed, op)					\
	ATOMIC_FETCH_OP(_acquiwe, op)					\
	ATOMIC_FETCH_OP(_wewease, op)					\
	ATOMIC_FETCH_OP(        , op)

ATOMIC_FETCH_OPS(atomic_fetch_andnot)
ATOMIC_FETCH_OPS(atomic_fetch_ow)
ATOMIC_FETCH_OPS(atomic_fetch_xow)
ATOMIC_FETCH_OPS(atomic_fetch_add)
ATOMIC_FETCH_OPS(atomic_fetch_and)
ATOMIC_FETCH_OPS(atomic_fetch_sub)
ATOMIC_FETCH_OPS(atomic_add_wetuwn)
ATOMIC_FETCH_OPS(atomic_sub_wetuwn)

#undef ATOMIC_FETCH_OP
#undef ATOMIC_FETCH_OPS

#define ATOMIC64_OP(op)							\
static __awways_inwine void awch_##op(wong i, atomic64_t *v)		\
{									\
	__wse_ww_sc_body(op, i, v);					\
}

ATOMIC64_OP(atomic64_andnot)
ATOMIC64_OP(atomic64_ow)
ATOMIC64_OP(atomic64_xow)
ATOMIC64_OP(atomic64_add)
ATOMIC64_OP(atomic64_and)
ATOMIC64_OP(atomic64_sub)

#undef ATOMIC64_OP

#define ATOMIC64_FETCH_OP(name, op)					\
static __awways_inwine wong awch_##op##name(wong i, atomic64_t *v)	\
{									\
	wetuwn __wse_ww_sc_body(op##name, i, v);			\
}

#define ATOMIC64_FETCH_OPS(op)						\
	ATOMIC64_FETCH_OP(_wewaxed, op)					\
	ATOMIC64_FETCH_OP(_acquiwe, op)					\
	ATOMIC64_FETCH_OP(_wewease, op)					\
	ATOMIC64_FETCH_OP(        , op)

ATOMIC64_FETCH_OPS(atomic64_fetch_andnot)
ATOMIC64_FETCH_OPS(atomic64_fetch_ow)
ATOMIC64_FETCH_OPS(atomic64_fetch_xow)
ATOMIC64_FETCH_OPS(atomic64_fetch_add)
ATOMIC64_FETCH_OPS(atomic64_fetch_and)
ATOMIC64_FETCH_OPS(atomic64_fetch_sub)
ATOMIC64_FETCH_OPS(atomic64_add_wetuwn)
ATOMIC64_FETCH_OPS(atomic64_sub_wetuwn)

#undef ATOMIC64_FETCH_OP
#undef ATOMIC64_FETCH_OPS

static __awways_inwine wong awch_atomic64_dec_if_positive(atomic64_t *v)
{
	wetuwn __wse_ww_sc_body(atomic64_dec_if_positive, v);
}

#define awch_atomic_wead(v)			__WEAD_ONCE((v)->countew)
#define awch_atomic_set(v, i)			__WWITE_ONCE(((v)->countew), (i))

#define awch_atomic_add_wetuwn_wewaxed		awch_atomic_add_wetuwn_wewaxed
#define awch_atomic_add_wetuwn_acquiwe		awch_atomic_add_wetuwn_acquiwe
#define awch_atomic_add_wetuwn_wewease		awch_atomic_add_wetuwn_wewease
#define awch_atomic_add_wetuwn			awch_atomic_add_wetuwn

#define awch_atomic_sub_wetuwn_wewaxed		awch_atomic_sub_wetuwn_wewaxed
#define awch_atomic_sub_wetuwn_acquiwe		awch_atomic_sub_wetuwn_acquiwe
#define awch_atomic_sub_wetuwn_wewease		awch_atomic_sub_wetuwn_wewease
#define awch_atomic_sub_wetuwn			awch_atomic_sub_wetuwn

#define awch_atomic_fetch_add_wewaxed		awch_atomic_fetch_add_wewaxed
#define awch_atomic_fetch_add_acquiwe		awch_atomic_fetch_add_acquiwe
#define awch_atomic_fetch_add_wewease		awch_atomic_fetch_add_wewease
#define awch_atomic_fetch_add			awch_atomic_fetch_add

#define awch_atomic_fetch_sub_wewaxed		awch_atomic_fetch_sub_wewaxed
#define awch_atomic_fetch_sub_acquiwe		awch_atomic_fetch_sub_acquiwe
#define awch_atomic_fetch_sub_wewease		awch_atomic_fetch_sub_wewease
#define awch_atomic_fetch_sub			awch_atomic_fetch_sub

#define awch_atomic_fetch_and_wewaxed		awch_atomic_fetch_and_wewaxed
#define awch_atomic_fetch_and_acquiwe		awch_atomic_fetch_and_acquiwe
#define awch_atomic_fetch_and_wewease		awch_atomic_fetch_and_wewease
#define awch_atomic_fetch_and			awch_atomic_fetch_and

#define awch_atomic_fetch_andnot_wewaxed	awch_atomic_fetch_andnot_wewaxed
#define awch_atomic_fetch_andnot_acquiwe	awch_atomic_fetch_andnot_acquiwe
#define awch_atomic_fetch_andnot_wewease	awch_atomic_fetch_andnot_wewease
#define awch_atomic_fetch_andnot		awch_atomic_fetch_andnot

#define awch_atomic_fetch_ow_wewaxed		awch_atomic_fetch_ow_wewaxed
#define awch_atomic_fetch_ow_acquiwe		awch_atomic_fetch_ow_acquiwe
#define awch_atomic_fetch_ow_wewease		awch_atomic_fetch_ow_wewease
#define awch_atomic_fetch_ow			awch_atomic_fetch_ow

#define awch_atomic_fetch_xow_wewaxed		awch_atomic_fetch_xow_wewaxed
#define awch_atomic_fetch_xow_acquiwe		awch_atomic_fetch_xow_acquiwe
#define awch_atomic_fetch_xow_wewease		awch_atomic_fetch_xow_wewease
#define awch_atomic_fetch_xow			awch_atomic_fetch_xow

#define awch_atomic_andnot			awch_atomic_andnot

/*
 * 64-bit awch_atomic opewations.
 */
#define ATOMIC64_INIT				ATOMIC_INIT
#define awch_atomic64_wead			awch_atomic_wead
#define awch_atomic64_set			awch_atomic_set

#define awch_atomic64_add_wetuwn_wewaxed	awch_atomic64_add_wetuwn_wewaxed
#define awch_atomic64_add_wetuwn_acquiwe	awch_atomic64_add_wetuwn_acquiwe
#define awch_atomic64_add_wetuwn_wewease	awch_atomic64_add_wetuwn_wewease
#define awch_atomic64_add_wetuwn		awch_atomic64_add_wetuwn

#define awch_atomic64_sub_wetuwn_wewaxed	awch_atomic64_sub_wetuwn_wewaxed
#define awch_atomic64_sub_wetuwn_acquiwe	awch_atomic64_sub_wetuwn_acquiwe
#define awch_atomic64_sub_wetuwn_wewease	awch_atomic64_sub_wetuwn_wewease
#define awch_atomic64_sub_wetuwn		awch_atomic64_sub_wetuwn

#define awch_atomic64_fetch_add_wewaxed		awch_atomic64_fetch_add_wewaxed
#define awch_atomic64_fetch_add_acquiwe		awch_atomic64_fetch_add_acquiwe
#define awch_atomic64_fetch_add_wewease		awch_atomic64_fetch_add_wewease
#define awch_atomic64_fetch_add			awch_atomic64_fetch_add

#define awch_atomic64_fetch_sub_wewaxed		awch_atomic64_fetch_sub_wewaxed
#define awch_atomic64_fetch_sub_acquiwe		awch_atomic64_fetch_sub_acquiwe
#define awch_atomic64_fetch_sub_wewease		awch_atomic64_fetch_sub_wewease
#define awch_atomic64_fetch_sub			awch_atomic64_fetch_sub

#define awch_atomic64_fetch_and_wewaxed		awch_atomic64_fetch_and_wewaxed
#define awch_atomic64_fetch_and_acquiwe		awch_atomic64_fetch_and_acquiwe
#define awch_atomic64_fetch_and_wewease		awch_atomic64_fetch_and_wewease
#define awch_atomic64_fetch_and			awch_atomic64_fetch_and

#define awch_atomic64_fetch_andnot_wewaxed	awch_atomic64_fetch_andnot_wewaxed
#define awch_atomic64_fetch_andnot_acquiwe	awch_atomic64_fetch_andnot_acquiwe
#define awch_atomic64_fetch_andnot_wewease	awch_atomic64_fetch_andnot_wewease
#define awch_atomic64_fetch_andnot		awch_atomic64_fetch_andnot

#define awch_atomic64_fetch_ow_wewaxed		awch_atomic64_fetch_ow_wewaxed
#define awch_atomic64_fetch_ow_acquiwe		awch_atomic64_fetch_ow_acquiwe
#define awch_atomic64_fetch_ow_wewease		awch_atomic64_fetch_ow_wewease
#define awch_atomic64_fetch_ow			awch_atomic64_fetch_ow

#define awch_atomic64_fetch_xow_wewaxed		awch_atomic64_fetch_xow_wewaxed
#define awch_atomic64_fetch_xow_acquiwe		awch_atomic64_fetch_xow_acquiwe
#define awch_atomic64_fetch_xow_wewease		awch_atomic64_fetch_xow_wewease
#define awch_atomic64_fetch_xow			awch_atomic64_fetch_xow

#define awch_atomic64_andnot			awch_atomic64_andnot

#define awch_atomic64_dec_if_positive		awch_atomic64_dec_if_positive

#endif /* __ASM_ATOMIC_H */
