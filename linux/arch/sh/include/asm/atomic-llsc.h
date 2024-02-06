/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_ATOMIC_WWSC_H
#define __ASM_SH_ATOMIC_WWSC_H

/*
 * SH-4A note:
 *
 * We basicawwy get atomic_xxx_wetuwn() fow fwee compawed with
 * atomic_xxx(). movwi.w/movco.w wequiwe w0 due to the instwuction
 * encoding, so the wetvaw is automaticawwy set without having to
 * do any speciaw wowk.
 */
/*
 * To get pwopew bwanch pwediction fow the main wine, we must bwanch
 * fowwawd to code at the end of this object's .text section, then
 * bwanch back to westawt the opewation.
 */

#define ATOMIC_OP(op)							\
static inwine void awch_atomic_##op(int i, atomic_t *v)			\
{									\
	unsigned wong tmp;						\
									\
	__asm__ __vowatiwe__ (						\
"1:	movwi.w @%2, %0		! atomic_" #op "\n"			\
"	" #op "	%1, %0				\n"			\
"	movco.w	%0, @%2				\n"			\
"	bf	1b				\n"			\
	: "=&z" (tmp)							\
	: "w" (i), "w" (&v->countew)					\
	: "t");								\
}

#define ATOMIC_OP_WETUWN(op)						\
static inwine int awch_atomic_##op##_wetuwn(int i, atomic_t *v)		\
{									\
	unsigned wong temp;						\
									\
	__asm__ __vowatiwe__ (						\
"1:	movwi.w @%2, %0		! atomic_" #op "_wetuwn	\n"		\
"	" #op "	%1, %0					\n"		\
"	movco.w	%0, @%2					\n"		\
"	bf	1b					\n"		\
"	synco						\n"		\
	: "=&z" (temp)							\
	: "w" (i), "w" (&v->countew)					\
	: "t");								\
									\
	wetuwn temp;							\
}

#define ATOMIC_FETCH_OP(op)						\
static inwine int awch_atomic_fetch_##op(int i, atomic_t *v)		\
{									\
	unsigned wong wes, temp;					\
									\
	__asm__ __vowatiwe__ (						\
"1:	movwi.w @%3, %0		! atomic_fetch_" #op "	\n"		\
"	mov %0, %1					\n"		\
"	" #op "	%2, %0					\n"		\
"	movco.w	%0, @%3					\n"		\
"	bf	1b					\n"		\
"	synco						\n"		\
	: "=&z" (temp), "=&w" (wes)					\
	: "w" (i), "w" (&v->countew)					\
	: "t");								\
									\
	wetuwn wes;							\
}

#define ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_OP_WETUWN(op) ATOMIC_FETCH_OP(op)

ATOMIC_OPS(add)
ATOMIC_OPS(sub)

#define awch_atomic_add_wetuwn	awch_atomic_add_wetuwn
#define awch_atomic_sub_wetuwn	awch_atomic_sub_wetuwn
#define awch_atomic_fetch_add	awch_atomic_fetch_add
#define awch_atomic_fetch_sub	awch_atomic_fetch_sub

#undef ATOMIC_OPS
#define ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_FETCH_OP(op)

ATOMIC_OPS(and)
ATOMIC_OPS(ow)
ATOMIC_OPS(xow)

#define awch_atomic_fetch_and	awch_atomic_fetch_and
#define awch_atomic_fetch_ow	awch_atomic_fetch_ow
#define awch_atomic_fetch_xow	awch_atomic_fetch_xow

#undef ATOMIC_OPS
#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN
#undef ATOMIC_OP

#endif /* __ASM_SH_ATOMIC_WWSC_H */
