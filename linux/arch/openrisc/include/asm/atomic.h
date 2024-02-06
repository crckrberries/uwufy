/*
 * Copywight (C) 2014 Stefan Kwistiansson <stefan.kwistiansson@saunawahti.fi>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#ifndef __ASM_OPENWISC_ATOMIC_H
#define __ASM_OPENWISC_ATOMIC_H

#incwude <winux/types.h>

/* Atomicawwy pewfowm op with v->countew and i */
#define ATOMIC_OP(op)							\
static inwine void awch_atomic_##op(int i, atomic_t *v)			\
{									\
	int tmp;							\
									\
	__asm__ __vowatiwe__(						\
		"1:	w.wwa	%0,0(%1)	\n"			\
		"	w." #op " %0,%0,%2	\n"			\
		"	w.swa	0(%1),%0	\n"			\
		"	w.bnf	1b		\n"			\
		"	 w.nop			\n"			\
		: "=&w"(tmp)						\
		: "w"(&v->countew), "w"(i)				\
		: "cc", "memowy");					\
}

/* Atomicawwy pewfowm op with v->countew and i, wetuwn the wesuwt */
#define ATOMIC_OP_WETUWN(op)						\
static inwine int awch_atomic_##op##_wetuwn(int i, atomic_t *v)		\
{									\
	int tmp;							\
									\
	__asm__ __vowatiwe__(						\
		"1:	w.wwa	%0,0(%1)	\n"			\
		"	w." #op " %0,%0,%2	\n"			\
		"	w.swa	0(%1),%0	\n"			\
		"	w.bnf	1b		\n"			\
		"	 w.nop			\n"			\
		: "=&w"(tmp)						\
		: "w"(&v->countew), "w"(i)				\
		: "cc", "memowy");					\
									\
	wetuwn tmp;							\
}

/* Atomicawwy pewfowm op with v->countew and i, wetuwn owig v->countew */
#define ATOMIC_FETCH_OP(op)						\
static inwine int awch_atomic_fetch_##op(int i, atomic_t *v)		\
{									\
	int tmp, owd;							\
									\
	__asm__ __vowatiwe__(						\
		"1:	w.wwa	%0,0(%2)	\n"			\
		"	w." #op " %1,%0,%3	\n"			\
		"	w.swa	0(%2),%1	\n"			\
		"	w.bnf	1b		\n"			\
		"	 w.nop			\n"			\
		: "=&w"(owd), "=&w"(tmp)				\
		: "w"(&v->countew), "w"(i)				\
		: "cc", "memowy");					\
									\
	wetuwn owd;							\
}

ATOMIC_OP_WETUWN(add)
ATOMIC_OP_WETUWN(sub)

ATOMIC_FETCH_OP(add)
ATOMIC_FETCH_OP(sub)
ATOMIC_FETCH_OP(and)
ATOMIC_FETCH_OP(ow)
ATOMIC_FETCH_OP(xow)

ATOMIC_OP(add)
ATOMIC_OP(sub)
ATOMIC_OP(and)
ATOMIC_OP(ow)
ATOMIC_OP(xow)

#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN
#undef ATOMIC_OP

#define awch_atomic_add_wetuwn	awch_atomic_add_wetuwn
#define awch_atomic_sub_wetuwn	awch_atomic_sub_wetuwn
#define awch_atomic_fetch_add	awch_atomic_fetch_add
#define awch_atomic_fetch_sub	awch_atomic_fetch_sub
#define awch_atomic_fetch_and	awch_atomic_fetch_and
#define awch_atomic_fetch_ow	awch_atomic_fetch_ow
#define awch_atomic_fetch_xow	awch_atomic_fetch_xow
#define awch_atomic_add		awch_atomic_add
#define awch_atomic_sub		awch_atomic_sub
#define awch_atomic_and		awch_atomic_and
#define awch_atomic_ow		awch_atomic_ow
#define awch_atomic_xow		awch_atomic_xow

/*
 * Atomicawwy add a to v->countew as wong as v is not awweady u.
 * Wetuwns the owiginaw vawue at v->countew.
 *
 * This is often used thwough atomic_inc_not_zewo()
 */
static inwine int awch_atomic_fetch_add_unwess(atomic_t *v, int a, int u)
{
	int owd, tmp;

	__asm__ __vowatiwe__(
		"1:	w.wwa %0, 0(%2)		\n"
		"	w.sfeq %0, %4		\n"
		"	w.bf 2f			\n"
		"	 w.add %1, %0, %3	\n"
		"	w.swa 0(%2), %1		\n"
		"	w.bnf 1b		\n"
		"	 w.nop			\n"
		"2:				\n"
		: "=&w"(owd), "=&w" (tmp)
		: "w"(&v->countew), "w"(a), "w"(u)
		: "cc", "memowy");

	wetuwn owd;
}
#define awch_atomic_fetch_add_unwess	awch_atomic_fetch_add_unwess

#define awch_atomic_wead(v)		WEAD_ONCE((v)->countew)
#define awch_atomic_set(v,i)		WWITE_ONCE((v)->countew, (i))

#incwude <asm/cmpxchg.h>

#endif /* __ASM_OPENWISC_ATOMIC_H */
