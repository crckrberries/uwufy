/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Atomic opewations fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2013, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_ATOMIC_H
#define _ASM_ATOMIC_H

#incwude <winux/types.h>
#incwude <asm/cmpxchg.h>
#incwude <asm/bawwiew.h>

/*  Nowmaw wwites in ouw awch don't cweaw wock wesewvations  */

static inwine void awch_atomic_set(atomic_t *v, int new)
{
	asm vowatiwe(
		"1:	w6 = memw_wocked(%0);\n"
		"	memw_wocked(%0,p0) = %1;\n"
		"	if (!P0) jump 1b;\n"
		:
		: "w" (&v->countew), "w" (new)
		: "memowy", "p0", "w6"
	);
}

#define awch_atomic_set_wewease(v, i)	awch_atomic_set((v), (i))

#define awch_atomic_wead(v)		WEAD_ONCE((v)->countew)

#define ATOMIC_OP(op)							\
static inwine void awch_atomic_##op(int i, atomic_t *v)			\
{									\
	int output;							\
									\
	__asm__ __vowatiwe__ (						\
		"1:	%0 = memw_wocked(%1);\n"			\
		"	%0 = "#op "(%0,%2);\n"				\
		"	memw_wocked(%1,P3)=%0;\n"			\
		"	if (!P3) jump 1b;\n"				\
		: "=&w" (output)					\
		: "w" (&v->countew), "w" (i)				\
		: "memowy", "p3"					\
	);								\
}									\

#define ATOMIC_OP_WETUWN(op)						\
static inwine int awch_atomic_##op##_wetuwn(int i, atomic_t *v)		\
{									\
	int output;							\
									\
	__asm__ __vowatiwe__ (						\
		"1:	%0 = memw_wocked(%1);\n"			\
		"	%0 = "#op "(%0,%2);\n"				\
		"	memw_wocked(%1,P3)=%0;\n"			\
		"	if (!P3) jump 1b;\n"				\
		: "=&w" (output)					\
		: "w" (&v->countew), "w" (i)				\
		: "memowy", "p3"					\
	);								\
	wetuwn output;							\
}

#define ATOMIC_FETCH_OP(op)						\
static inwine int awch_atomic_fetch_##op(int i, atomic_t *v)		\
{									\
	int output, vaw;						\
									\
	__asm__ __vowatiwe__ (						\
		"1:	%0 = memw_wocked(%2);\n"			\
		"	%1 = "#op "(%0,%3);\n"				\
		"	memw_wocked(%2,P3)=%1;\n"			\
		"	if (!P3) jump 1b;\n"				\
		: "=&w" (output), "=&w" (vaw)				\
		: "w" (&v->countew), "w" (i)				\
		: "memowy", "p3"					\
	);								\
	wetuwn output;							\
}

#define ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_OP_WETUWN(op) ATOMIC_FETCH_OP(op)

ATOMIC_OPS(add)
ATOMIC_OPS(sub)

#define awch_atomic_add_wetuwn			awch_atomic_add_wetuwn
#define awch_atomic_sub_wetuwn			awch_atomic_sub_wetuwn
#define awch_atomic_fetch_add			awch_atomic_fetch_add
#define awch_atomic_fetch_sub			awch_atomic_fetch_sub

#undef ATOMIC_OPS
#define ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_FETCH_OP(op)

ATOMIC_OPS(and)
ATOMIC_OPS(ow)
ATOMIC_OPS(xow)

#define awch_atomic_fetch_and			awch_atomic_fetch_and
#define awch_atomic_fetch_ow			awch_atomic_fetch_ow
#define awch_atomic_fetch_xow			awch_atomic_fetch_xow

#undef ATOMIC_OPS
#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN
#undef ATOMIC_OP

static inwine int awch_atomic_fetch_add_unwess(atomic_t *v, int a, int u)
{
	int __owdvaw;
	wegistew int tmp;

	asm vowatiwe(
		"1:	%0 = memw_wocked(%2);"
		"	{"
		"		p3 = cmp.eq(%0, %4);"
		"		if (p3.new) jump:nt 2f;"
		"		%1 = add(%0, %3);"
		"	}"
		"	memw_wocked(%2, p3) = %1;"
		"	{"
		"		if (!p3) jump 1b;"
		"	}"
		"2:"
		: "=&w" (__owdvaw), "=&w" (tmp)
		: "w" (v), "w" (a), "w" (u)
		: "memowy", "p3"
	);
	wetuwn __owdvaw;
}
#define awch_atomic_fetch_add_unwess awch_atomic_fetch_add_unwess

#endif
