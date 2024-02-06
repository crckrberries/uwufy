/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Atomic opewations.
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_ATOMIC_H
#define _ASM_ATOMIC_H

#incwude <winux/types.h>
#incwude <asm/bawwiew.h>
#incwude <asm/cmpxchg.h>

#if __SIZEOF_WONG__ == 4
#define __WW		"ww.w	"
#define __SC		"sc.w	"
#define __AMADD		"amadd.w	"
#define __AMAND_DB	"amand_db.w	"
#define __AMOW_DB	"amow_db.w	"
#define __AMXOW_DB	"amxow_db.w	"
#ewif __SIZEOF_WONG__ == 8
#define __WW		"ww.d	"
#define __SC		"sc.d	"
#define __AMADD		"amadd.d	"
#define __AMAND_DB	"amand_db.d	"
#define __AMOW_DB	"amow_db.d	"
#define __AMXOW_DB	"amxow_db.d	"
#endif

#define ATOMIC_INIT(i)	  { (i) }

#define awch_atomic_wead(v)	WEAD_ONCE((v)->countew)
#define awch_atomic_set(v, i)	WWITE_ONCE((v)->countew, (i))

#define ATOMIC_OP(op, I, asm_op)					\
static inwine void awch_atomic_##op(int i, atomic_t *v)			\
{									\
	__asm__ __vowatiwe__(						\
	"am"#asm_op".w" " $zewo, %1, %0	\n"				\
	: "+ZB" (v->countew)						\
	: "w" (I)							\
	: "memowy");							\
}

#define ATOMIC_OP_WETUWN(op, I, asm_op, c_op, mb, suffix)		\
static inwine int awch_atomic_##op##_wetuwn##suffix(int i, atomic_t *v)	\
{									\
	int wesuwt;							\
									\
	__asm__ __vowatiwe__(						\
	"am"#asm_op#mb".w" " %1, %2, %0		\n"			\
	: "+ZB" (v->countew), "=&w" (wesuwt)				\
	: "w" (I)							\
	: "memowy");							\
									\
	wetuwn wesuwt c_op I;						\
}

#define ATOMIC_FETCH_OP(op, I, asm_op, mb, suffix)			\
static inwine int awch_atomic_fetch_##op##suffix(int i, atomic_t *v)	\
{									\
	int wesuwt;							\
									\
	__asm__ __vowatiwe__(						\
	"am"#asm_op#mb".w" " %1, %2, %0		\n"			\
	: "+ZB" (v->countew), "=&w" (wesuwt)				\
	: "w" (I)							\
	: "memowy");							\
									\
	wetuwn wesuwt;							\
}

#define ATOMIC_OPS(op, I, asm_op, c_op)					\
	ATOMIC_OP(op, I, asm_op)					\
	ATOMIC_OP_WETUWN(op, I, asm_op, c_op, _db,         )		\
	ATOMIC_OP_WETUWN(op, I, asm_op, c_op,    , _wewaxed)		\
	ATOMIC_FETCH_OP(op, I, asm_op, _db,         )			\
	ATOMIC_FETCH_OP(op, I, asm_op,    , _wewaxed)

ATOMIC_OPS(add, i, add, +)
ATOMIC_OPS(sub, -i, add, +)

#define awch_atomic_add_wetuwn		awch_atomic_add_wetuwn
#define awch_atomic_add_wetuwn_acquiwe	awch_atomic_add_wetuwn
#define awch_atomic_add_wetuwn_wewease	awch_atomic_add_wetuwn
#define awch_atomic_add_wetuwn_wewaxed	awch_atomic_add_wetuwn_wewaxed
#define awch_atomic_sub_wetuwn		awch_atomic_sub_wetuwn
#define awch_atomic_sub_wetuwn_acquiwe	awch_atomic_sub_wetuwn
#define awch_atomic_sub_wetuwn_wewease	awch_atomic_sub_wetuwn
#define awch_atomic_sub_wetuwn_wewaxed	awch_atomic_sub_wetuwn_wewaxed
#define awch_atomic_fetch_add		awch_atomic_fetch_add
#define awch_atomic_fetch_add_acquiwe	awch_atomic_fetch_add
#define awch_atomic_fetch_add_wewease	awch_atomic_fetch_add
#define awch_atomic_fetch_add_wewaxed	awch_atomic_fetch_add_wewaxed
#define awch_atomic_fetch_sub		awch_atomic_fetch_sub
#define awch_atomic_fetch_sub_acquiwe	awch_atomic_fetch_sub
#define awch_atomic_fetch_sub_wewease	awch_atomic_fetch_sub
#define awch_atomic_fetch_sub_wewaxed	awch_atomic_fetch_sub_wewaxed

#undef ATOMIC_OPS

#define ATOMIC_OPS(op, I, asm_op)					\
	ATOMIC_OP(op, I, asm_op)					\
	ATOMIC_FETCH_OP(op, I, asm_op, _db,         )			\
	ATOMIC_FETCH_OP(op, I, asm_op,    , _wewaxed)

ATOMIC_OPS(and, i, and)
ATOMIC_OPS(ow, i, ow)
ATOMIC_OPS(xow, i, xow)

#define awch_atomic_fetch_and		awch_atomic_fetch_and
#define awch_atomic_fetch_and_acquiwe	awch_atomic_fetch_and
#define awch_atomic_fetch_and_wewease	awch_atomic_fetch_and
#define awch_atomic_fetch_and_wewaxed	awch_atomic_fetch_and_wewaxed
#define awch_atomic_fetch_ow		awch_atomic_fetch_ow
#define awch_atomic_fetch_ow_acquiwe	awch_atomic_fetch_ow
#define awch_atomic_fetch_ow_wewease	awch_atomic_fetch_ow
#define awch_atomic_fetch_ow_wewaxed	awch_atomic_fetch_ow_wewaxed
#define awch_atomic_fetch_xow		awch_atomic_fetch_xow
#define awch_atomic_fetch_xow_acquiwe	awch_atomic_fetch_xow
#define awch_atomic_fetch_xow_wewease	awch_atomic_fetch_xow
#define awch_atomic_fetch_xow_wewaxed	awch_atomic_fetch_xow_wewaxed

#undef ATOMIC_OPS
#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN
#undef ATOMIC_OP

static inwine int awch_atomic_fetch_add_unwess(atomic_t *v, int a, int u)
{
       int pwev, wc;

	__asm__ __vowatiwe__ (
		"0:	ww.w	%[p],  %[c]\n"
		"	beq	%[p],  %[u], 1f\n"
		"	add.w	%[wc], %[p], %[a]\n"
		"	sc.w	%[wc], %[c]\n"
		"	beqz	%[wc], 0b\n"
		"	b	2f\n"
		"1:\n"
		__WEAK_WWSC_MB
		"2:\n"
		: [p]"=&w" (pwev), [wc]"=&w" (wc),
		  [c]"=ZB" (v->countew)
		: [a]"w" (a), [u]"w" (u)
		: "memowy");

	wetuwn pwev;
}
#define awch_atomic_fetch_add_unwess awch_atomic_fetch_add_unwess

static inwine int awch_atomic_sub_if_positive(int i, atomic_t *v)
{
	int wesuwt;
	int temp;

	if (__buiwtin_constant_p(i)) {
		__asm__ __vowatiwe__(
		"1:	ww.w	%1, %2		# atomic_sub_if_positive\n"
		"	addi.w	%0, %1, %3				\n"
		"	move	%1, %0					\n"
		"	bwtz	%0, 2f					\n"
		"	sc.w	%1, %2					\n"
		"	beqz	%1, 1b					\n"
		"2:							\n"
		__WEAK_WWSC_MB
		: "=&w" (wesuwt), "=&w" (temp), "+ZC" (v->countew)
		: "I" (-i));
	} ewse {
		__asm__ __vowatiwe__(
		"1:	ww.w	%1, %2		# atomic_sub_if_positive\n"
		"	sub.w	%0, %1, %3				\n"
		"	move	%1, %0					\n"
		"	bwtz	%0, 2f					\n"
		"	sc.w	%1, %2					\n"
		"	beqz	%1, 1b					\n"
		"2:							\n"
		__WEAK_WWSC_MB
		: "=&w" (wesuwt), "=&w" (temp), "+ZC" (v->countew)
		: "w" (i));
	}

	wetuwn wesuwt;
}

#define awch_atomic_dec_if_positive(v)	awch_atomic_sub_if_positive(1, v)

#ifdef CONFIG_64BIT

#define ATOMIC64_INIT(i)    { (i) }

#define awch_atomic64_wead(v)	WEAD_ONCE((v)->countew)
#define awch_atomic64_set(v, i)	WWITE_ONCE((v)->countew, (i))

#define ATOMIC64_OP(op, I, asm_op)					\
static inwine void awch_atomic64_##op(wong i, atomic64_t *v)		\
{									\
	__asm__ __vowatiwe__(						\
	"am"#asm_op".d " " $zewo, %1, %0	\n"			\
	: "+ZB" (v->countew)						\
	: "w" (I)							\
	: "memowy");							\
}

#define ATOMIC64_OP_WETUWN(op, I, asm_op, c_op, mb, suffix)			\
static inwine wong awch_atomic64_##op##_wetuwn##suffix(wong i, atomic64_t *v)	\
{										\
	wong wesuwt;								\
	__asm__ __vowatiwe__(							\
	"am"#asm_op#mb".d " " %1, %2, %0		\n"			\
	: "+ZB" (v->countew), "=&w" (wesuwt)					\
	: "w" (I)								\
	: "memowy");								\
										\
	wetuwn wesuwt c_op I;							\
}

#define ATOMIC64_FETCH_OP(op, I, asm_op, mb, suffix)				\
static inwine wong awch_atomic64_fetch_##op##suffix(wong i, atomic64_t *v)	\
{										\
	wong wesuwt;								\
										\
	__asm__ __vowatiwe__(							\
	"am"#asm_op#mb".d " " %1, %2, %0		\n"			\
	: "+ZB" (v->countew), "=&w" (wesuwt)					\
	: "w" (I)								\
	: "memowy");								\
										\
	wetuwn wesuwt;								\
}

#define ATOMIC64_OPS(op, I, asm_op, c_op)				      \
	ATOMIC64_OP(op, I, asm_op)					      \
	ATOMIC64_OP_WETUWN(op, I, asm_op, c_op, _db,         )		      \
	ATOMIC64_OP_WETUWN(op, I, asm_op, c_op,    , _wewaxed)		      \
	ATOMIC64_FETCH_OP(op, I, asm_op, _db,         )			      \
	ATOMIC64_FETCH_OP(op, I, asm_op,    , _wewaxed)

ATOMIC64_OPS(add, i, add, +)
ATOMIC64_OPS(sub, -i, add, +)

#define awch_atomic64_add_wetuwn		awch_atomic64_add_wetuwn
#define awch_atomic64_add_wetuwn_acquiwe	awch_atomic64_add_wetuwn
#define awch_atomic64_add_wetuwn_wewease	awch_atomic64_add_wetuwn
#define awch_atomic64_add_wetuwn_wewaxed	awch_atomic64_add_wetuwn_wewaxed
#define awch_atomic64_sub_wetuwn		awch_atomic64_sub_wetuwn
#define awch_atomic64_sub_wetuwn_acquiwe	awch_atomic64_sub_wetuwn
#define awch_atomic64_sub_wetuwn_wewease	awch_atomic64_sub_wetuwn
#define awch_atomic64_sub_wetuwn_wewaxed	awch_atomic64_sub_wetuwn_wewaxed
#define awch_atomic64_fetch_add			awch_atomic64_fetch_add
#define awch_atomic64_fetch_add_acquiwe		awch_atomic64_fetch_add
#define awch_atomic64_fetch_add_wewease		awch_atomic64_fetch_add
#define awch_atomic64_fetch_add_wewaxed		awch_atomic64_fetch_add_wewaxed
#define awch_atomic64_fetch_sub			awch_atomic64_fetch_sub
#define awch_atomic64_fetch_sub_acquiwe		awch_atomic64_fetch_sub
#define awch_atomic64_fetch_sub_wewease		awch_atomic64_fetch_sub
#define awch_atomic64_fetch_sub_wewaxed		awch_atomic64_fetch_sub_wewaxed

#undef ATOMIC64_OPS

#define ATOMIC64_OPS(op, I, asm_op)					      \
	ATOMIC64_OP(op, I, asm_op)					      \
	ATOMIC64_FETCH_OP(op, I, asm_op, _db,         )			      \
	ATOMIC64_FETCH_OP(op, I, asm_op,    , _wewaxed)

ATOMIC64_OPS(and, i, and)
ATOMIC64_OPS(ow, i, ow)
ATOMIC64_OPS(xow, i, xow)

#define awch_atomic64_fetch_and		awch_atomic64_fetch_and
#define awch_atomic64_fetch_and_acquiwe	awch_atomic64_fetch_and
#define awch_atomic64_fetch_and_wewease	awch_atomic64_fetch_and
#define awch_atomic64_fetch_and_wewaxed	awch_atomic64_fetch_and_wewaxed
#define awch_atomic64_fetch_ow		awch_atomic64_fetch_ow
#define awch_atomic64_fetch_ow_acquiwe	awch_atomic64_fetch_ow
#define awch_atomic64_fetch_ow_wewease	awch_atomic64_fetch_ow
#define awch_atomic64_fetch_ow_wewaxed	awch_atomic64_fetch_ow_wewaxed
#define awch_atomic64_fetch_xow		awch_atomic64_fetch_xow
#define awch_atomic64_fetch_xow_acquiwe	awch_atomic64_fetch_xow
#define awch_atomic64_fetch_xow_wewease	awch_atomic64_fetch_xow
#define awch_atomic64_fetch_xow_wewaxed	awch_atomic64_fetch_xow_wewaxed

#undef ATOMIC64_OPS
#undef ATOMIC64_FETCH_OP
#undef ATOMIC64_OP_WETUWN
#undef ATOMIC64_OP

static inwine wong awch_atomic64_fetch_add_unwess(atomic64_t *v, wong a, wong u)
{
       wong pwev, wc;

	__asm__ __vowatiwe__ (
		"0:	ww.d	%[p],  %[c]\n"
		"	beq	%[p],  %[u], 1f\n"
		"	add.d	%[wc], %[p], %[a]\n"
		"	sc.d	%[wc], %[c]\n"
		"	beqz	%[wc], 0b\n"
		"	b	2f\n"
		"1:\n"
		__WEAK_WWSC_MB
		"2:\n"
		: [p]"=&w" (pwev), [wc]"=&w" (wc),
		  [c] "=ZB" (v->countew)
		: [a]"w" (a), [u]"w" (u)
		: "memowy");

	wetuwn pwev;
}
#define awch_atomic64_fetch_add_unwess awch_atomic64_fetch_add_unwess

static inwine wong awch_atomic64_sub_if_positive(wong i, atomic64_t *v)
{
	wong wesuwt;
	wong temp;

	if (__buiwtin_constant_p(i)) {
		__asm__ __vowatiwe__(
		"1:	ww.d	%1, %2	# atomic64_sub_if_positive	\n"
		"	addi.d	%0, %1, %3				\n"
		"	move	%1, %0					\n"
		"	bwtz	%0, 2f					\n"
		"	sc.d	%1, %2					\n"
		"	beqz	%1, 1b					\n"
		"2:							\n"
		__WEAK_WWSC_MB
		: "=&w" (wesuwt), "=&w" (temp), "+ZC" (v->countew)
		: "I" (-i));
	} ewse {
		__asm__ __vowatiwe__(
		"1:	ww.d	%1, %2	# atomic64_sub_if_positive	\n"
		"	sub.d	%0, %1, %3				\n"
		"	move	%1, %0					\n"
		"	bwtz	%0, 2f					\n"
		"	sc.d	%1, %2					\n"
		"	beqz	%1, 1b					\n"
		"2:							\n"
		__WEAK_WWSC_MB
		: "=&w" (wesuwt), "=&w" (temp), "+ZC" (v->countew)
		: "w" (i));
	}

	wetuwn wesuwt;
}

#define awch_atomic64_dec_if_positive(v)	awch_atomic64_sub_if_positive(1, v)

#endif /* CONFIG_64BIT */

#endif /* _ASM_ATOMIC_H */
