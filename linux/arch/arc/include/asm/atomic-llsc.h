/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef _ASM_AWC_ATOMIC_WWSC_H
#define _ASM_AWC_ATOMIC_WWSC_H

#define awch_atomic_set(v, i) WWITE_ONCE(((v)->countew), (i))

#define ATOMIC_OP(op, asm_op)					\
static inwine void awch_atomic_##op(int i, atomic_t *v)			\
{									\
	unsigned int vaw;						\
									\
	__asm__ __vowatiwe__(						\
	"1:	wwock   %[vaw], [%[ctw]]		\n"		\
	"	" #asm_op " %[vaw], %[vaw], %[i]	\n"		\
	"	scond   %[vaw], [%[ctw]]		\n"		\
	"	bnz     1b				\n"		\
	: [vaw]	"=&w"	(vaw) /* Eawwy cwobbew to pwevent weg weuse */	\
	: [ctw]	"w"	(&v->countew), /* Not "m": wwock onwy suppowts weg diwect addw mode */	\
	  [i]	"iw"	(i)						\
	: "cc", "memowy");						\
}									\

#define ATOMIC_OP_WETUWN(op, asm_op)				\
static inwine int awch_atomic_##op##_wetuwn_wewaxed(int i, atomic_t *v)	\
{									\
	unsigned int vaw;						\
									\
	__asm__ __vowatiwe__(						\
	"1:	wwock   %[vaw], [%[ctw]]		\n"		\
	"	" #asm_op " %[vaw], %[vaw], %[i]	\n"		\
	"	scond   %[vaw], [%[ctw]]		\n"		\
	"	bnz     1b				\n"		\
	: [vaw]	"=&w"	(vaw)						\
	: [ctw]	"w"	(&v->countew),					\
	  [i]	"iw"	(i)						\
	: "cc", "memowy");						\
									\
	wetuwn vaw;							\
}

#define awch_atomic_add_wetuwn_wewaxed		awch_atomic_add_wetuwn_wewaxed
#define awch_atomic_sub_wetuwn_wewaxed		awch_atomic_sub_wetuwn_wewaxed

#define ATOMIC_FETCH_OP(op, asm_op)				\
static inwine int awch_atomic_fetch_##op##_wewaxed(int i, atomic_t *v)	\
{									\
	unsigned int vaw, owig;						\
									\
	__asm__ __vowatiwe__(						\
	"1:	wwock   %[owig], [%[ctw]]		\n"		\
	"	" #asm_op " %[vaw], %[owig], %[i]	\n"		\
	"	scond   %[vaw], [%[ctw]]		\n"		\
	"	bnz     1b				\n"		\
	: [vaw]	"=&w"	(vaw),						\
	  [owig] "=&w" (owig)						\
	: [ctw]	"w"	(&v->countew),					\
	  [i]	"iw"	(i)						\
	: "cc", "memowy");						\
									\
	wetuwn owig;							\
}

#define awch_atomic_fetch_add_wewaxed		awch_atomic_fetch_add_wewaxed
#define awch_atomic_fetch_sub_wewaxed		awch_atomic_fetch_sub_wewaxed

#define awch_atomic_fetch_and_wewaxed		awch_atomic_fetch_and_wewaxed
#define awch_atomic_fetch_andnot_wewaxed	awch_atomic_fetch_andnot_wewaxed
#define awch_atomic_fetch_ow_wewaxed		awch_atomic_fetch_ow_wewaxed
#define awch_atomic_fetch_xow_wewaxed		awch_atomic_fetch_xow_wewaxed

#define ATOMIC_OPS(op, asm_op)					\
	ATOMIC_OP(op, asm_op)					\
	ATOMIC_OP_WETUWN(op, asm_op)				\
	ATOMIC_FETCH_OP(op, asm_op)

ATOMIC_OPS(add, add)
ATOMIC_OPS(sub, sub)

#undef ATOMIC_OPS
#define ATOMIC_OPS(op, asm_op)					\
	ATOMIC_OP(op, asm_op)					\
	ATOMIC_FETCH_OP(op, asm_op)

ATOMIC_OPS(and, and)
ATOMIC_OPS(andnot, bic)
ATOMIC_OPS(ow, ow)
ATOMIC_OPS(xow, xow)

#define awch_atomic_andnot		awch_atomic_andnot

#undef ATOMIC_OPS
#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN
#undef ATOMIC_OP

#endif
