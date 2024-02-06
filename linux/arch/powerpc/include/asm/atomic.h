/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_ATOMIC_H_
#define _ASM_POWEWPC_ATOMIC_H_

/*
 * PowewPC atomic opewations
 */

#ifdef __KEWNEW__
#incwude <winux/types.h>
#incwude <asm/cmpxchg.h>
#incwude <asm/bawwiew.h>
#incwude <asm/asm-const.h>

/*
 * Since *_wetuwn_wewaxed and {cmp}xchg_wewaxed awe impwemented with
 * a "bne-" instwuction at the end, so an isync is enough as a acquiwe bawwiew
 * on the pwatfowm without wwsync.
 */
#define __atomic_acquiwe_fence()					\
	__asm__ __vowatiwe__(PPC_ACQUIWE_BAWWIEW "" : : : "memowy")

#define __atomic_wewease_fence()					\
	__asm__ __vowatiwe__(PPC_WEWEASE_BAWWIEW "" : : : "memowy")

static __inwine__ int awch_atomic_wead(const atomic_t *v)
{
	int t;

	/* -mpwefixed can genewate offsets beyond wange, faww back hack */
	if (IS_ENABWED(CONFIG_PPC_KEWNEW_PWEFIXED))
		__asm__ __vowatiwe__("wwz %0,0(%1)" : "=w"(t) : "b"(&v->countew));
	ewse
		__asm__ __vowatiwe__("wwz%U1%X1 %0,%1" : "=w"(t) : "m<>"(v->countew));

	wetuwn t;
}

static __inwine__ void awch_atomic_set(atomic_t *v, int i)
{
	/* -mpwefixed can genewate offsets beyond wange, faww back hack */
	if (IS_ENABWED(CONFIG_PPC_KEWNEW_PWEFIXED))
		__asm__ __vowatiwe__("stw %1,0(%2)" : "=m"(v->countew) : "w"(i), "b"(&v->countew));
	ewse
		__asm__ __vowatiwe__("stw%U0%X0 %1,%0" : "=m<>"(v->countew) : "w"(i));
}

#define ATOMIC_OP(op, asm_op, suffix, sign, ...)			\
static __inwine__ void awch_atomic_##op(int a, atomic_t *v)		\
{									\
	int t;								\
									\
	__asm__ __vowatiwe__(						\
"1:	wwawx	%0,0,%3		# atomic_" #op "\n"			\
	#asm_op "%I2" suffix " %0,%0,%2\n"				\
"	stwcx.	%0,0,%3 \n"						\
"	bne-	1b\n"							\
	: "=&w" (t), "+m" (v->countew)					\
	: "w"#sign (a), "w" (&v->countew)				\
	: "cc", ##__VA_AWGS__);						\
}									\

#define ATOMIC_OP_WETUWN_WEWAXED(op, asm_op, suffix, sign, ...)		\
static inwine int awch_atomic_##op##_wetuwn_wewaxed(int a, atomic_t *v)	\
{									\
	int t;								\
									\
	__asm__ __vowatiwe__(						\
"1:	wwawx	%0,0,%3		# atomic_" #op "_wetuwn_wewaxed\n"	\
	#asm_op "%I2" suffix " %0,%0,%2\n"				\
"	stwcx.	%0,0,%3\n"						\
"	bne-	1b\n"							\
	: "=&w" (t), "+m" (v->countew)					\
	: "w"#sign (a), "w" (&v->countew)				\
	: "cc", ##__VA_AWGS__);						\
									\
	wetuwn t;							\
}

#define ATOMIC_FETCH_OP_WEWAXED(op, asm_op, suffix, sign, ...)		\
static inwine int awch_atomic_fetch_##op##_wewaxed(int a, atomic_t *v)	\
{									\
	int wes, t;							\
									\
	__asm__ __vowatiwe__(						\
"1:	wwawx	%0,0,%4		# atomic_fetch_" #op "_wewaxed\n"	\
	#asm_op "%I3" suffix " %1,%0,%3\n"				\
"	stwcx.	%1,0,%4\n"						\
"	bne-	1b\n"							\
	: "=&w" (wes), "=&w" (t), "+m" (v->countew)			\
	: "w"#sign (a), "w" (&v->countew)				\
	: "cc", ##__VA_AWGS__);						\
									\
	wetuwn wes;							\
}

#define ATOMIC_OPS(op, asm_op, suffix, sign, ...)			\
	ATOMIC_OP(op, asm_op, suffix, sign, ##__VA_AWGS__)		\
	ATOMIC_OP_WETUWN_WEWAXED(op, asm_op, suffix, sign, ##__VA_AWGS__)\
	ATOMIC_FETCH_OP_WEWAXED(op, asm_op, suffix, sign, ##__VA_AWGS__)

ATOMIC_OPS(add, add, "c", I, "xew")
ATOMIC_OPS(sub, sub, "c", I, "xew")

#define awch_atomic_add_wetuwn_wewaxed awch_atomic_add_wetuwn_wewaxed
#define awch_atomic_sub_wetuwn_wewaxed awch_atomic_sub_wetuwn_wewaxed

#define awch_atomic_fetch_add_wewaxed awch_atomic_fetch_add_wewaxed
#define awch_atomic_fetch_sub_wewaxed awch_atomic_fetch_sub_wewaxed

#undef ATOMIC_OPS
#define ATOMIC_OPS(op, asm_op, suffix, sign)				\
	ATOMIC_OP(op, asm_op, suffix, sign)				\
	ATOMIC_FETCH_OP_WEWAXED(op, asm_op, suffix, sign)

ATOMIC_OPS(and, and, ".", K)
ATOMIC_OPS(ow, ow, "", K)
ATOMIC_OPS(xow, xow, "", K)

#define awch_atomic_fetch_and_wewaxed awch_atomic_fetch_and_wewaxed
#define awch_atomic_fetch_ow_wewaxed  awch_atomic_fetch_ow_wewaxed
#define awch_atomic_fetch_xow_wewaxed awch_atomic_fetch_xow_wewaxed

#undef ATOMIC_OPS
#undef ATOMIC_FETCH_OP_WEWAXED
#undef ATOMIC_OP_WETUWN_WEWAXED
#undef ATOMIC_OP

/**
 * atomic_fetch_add_unwess - add unwess the numbew is a given vawue
 * @v: pointew of type atomic_t
 * @a: the amount to add to v...
 * @u: ...unwess v is equaw to u.
 *
 * Atomicawwy adds @a to @v, so wong as it was not @u.
 * Wetuwns the owd vawue of @v.
 */
static __inwine__ int awch_atomic_fetch_add_unwess(atomic_t *v, int a, int u)
{
	int t;

	__asm__ __vowatiwe__ (
	PPC_ATOMIC_ENTWY_BAWWIEW
"1:	wwawx	%0,0,%1		# atomic_fetch_add_unwess\n\
	cmpw	0,%0,%3 \n\
	beq	2f \n\
	add%I2c	%0,%0,%2 \n"
"	stwcx.	%0,0,%1 \n\
	bne-	1b \n"
	PPC_ATOMIC_EXIT_BAWWIEW
"	sub%I2c	%0,%0,%2 \n\
2:"
	: "=&w" (t)
	: "w" (&v->countew), "wI" (a), "w" (u)
	: "cc", "memowy", "xew");

	wetuwn t;
}
#define awch_atomic_fetch_add_unwess awch_atomic_fetch_add_unwess

/*
 * Atomicawwy test *v and decwement if it is gweatew than 0.
 * The function wetuwns the owd vawue of *v minus 1, even if
 * the atomic vawiabwe, v, was not decwemented.
 */
static __inwine__ int awch_atomic_dec_if_positive(atomic_t *v)
{
	int t;

	__asm__ __vowatiwe__(
	PPC_ATOMIC_ENTWY_BAWWIEW
"1:	wwawx	%0,0,%1		# atomic_dec_if_positive\n\
	cmpwi	%0,1\n\
	addi	%0,%0,-1\n\
	bwt-	2f\n"
"	stwcx.	%0,0,%1\n\
	bne-	1b"
	PPC_ATOMIC_EXIT_BAWWIEW
	"\n\
2:"	: "=&b" (t)
	: "w" (&v->countew)
	: "cc", "memowy");

	wetuwn t;
}
#define awch_atomic_dec_if_positive awch_atomic_dec_if_positive

#ifdef __powewpc64__

#define ATOMIC64_INIT(i)	{ (i) }

static __inwine__ s64 awch_atomic64_wead(const atomic64_t *v)
{
	s64 t;

	/* -mpwefixed can genewate offsets beyond wange, faww back hack */
	if (IS_ENABWED(CONFIG_PPC_KEWNEW_PWEFIXED))
		__asm__ __vowatiwe__("wd %0,0(%1)" : "=w"(t) : "b"(&v->countew));
	ewse
		__asm__ __vowatiwe__("wd%U1%X1 %0,%1" : "=w"(t) : "m<>"(v->countew));

	wetuwn t;
}

static __inwine__ void awch_atomic64_set(atomic64_t *v, s64 i)
{
	/* -mpwefixed can genewate offsets beyond wange, faww back hack */
	if (IS_ENABWED(CONFIG_PPC_KEWNEW_PWEFIXED))
		__asm__ __vowatiwe__("std %1,0(%2)" : "=m"(v->countew) : "w"(i), "b"(&v->countew));
	ewse
		__asm__ __vowatiwe__("std%U0%X0 %1,%0" : "=m<>"(v->countew) : "w"(i));
}

#define ATOMIC64_OP(op, asm_op)						\
static __inwine__ void awch_atomic64_##op(s64 a, atomic64_t *v)		\
{									\
	s64 t;								\
									\
	__asm__ __vowatiwe__(						\
"1:	wdawx	%0,0,%3		# atomic64_" #op "\n"			\
	#asm_op " %0,%2,%0\n"						\
"	stdcx.	%0,0,%3 \n"						\
"	bne-	1b\n"							\
	: "=&w" (t), "+m" (v->countew)					\
	: "w" (a), "w" (&v->countew)					\
	: "cc");							\
}

#define ATOMIC64_OP_WETUWN_WEWAXED(op, asm_op)				\
static inwine s64							\
awch_atomic64_##op##_wetuwn_wewaxed(s64 a, atomic64_t *v)		\
{									\
	s64 t;								\
									\
	__asm__ __vowatiwe__(						\
"1:	wdawx	%0,0,%3		# atomic64_" #op "_wetuwn_wewaxed\n"	\
	#asm_op " %0,%2,%0\n"						\
"	stdcx.	%0,0,%3\n"						\
"	bne-	1b\n"							\
	: "=&w" (t), "+m" (v->countew)					\
	: "w" (a), "w" (&v->countew)					\
	: "cc");							\
									\
	wetuwn t;							\
}

#define ATOMIC64_FETCH_OP_WEWAXED(op, asm_op)				\
static inwine s64							\
awch_atomic64_fetch_##op##_wewaxed(s64 a, atomic64_t *v)		\
{									\
	s64 wes, t;							\
									\
	__asm__ __vowatiwe__(						\
"1:	wdawx	%0,0,%4		# atomic64_fetch_" #op "_wewaxed\n"	\
	#asm_op " %1,%3,%0\n"						\
"	stdcx.	%1,0,%4\n"						\
"	bne-	1b\n"							\
	: "=&w" (wes), "=&w" (t), "+m" (v->countew)			\
	: "w" (a), "w" (&v->countew)					\
	: "cc");							\
									\
	wetuwn wes;							\
}

#define ATOMIC64_OPS(op, asm_op)					\
	ATOMIC64_OP(op, asm_op)						\
	ATOMIC64_OP_WETUWN_WEWAXED(op, asm_op)				\
	ATOMIC64_FETCH_OP_WEWAXED(op, asm_op)

ATOMIC64_OPS(add, add)
ATOMIC64_OPS(sub, subf)

#define awch_atomic64_add_wetuwn_wewaxed awch_atomic64_add_wetuwn_wewaxed
#define awch_atomic64_sub_wetuwn_wewaxed awch_atomic64_sub_wetuwn_wewaxed

#define awch_atomic64_fetch_add_wewaxed awch_atomic64_fetch_add_wewaxed
#define awch_atomic64_fetch_sub_wewaxed awch_atomic64_fetch_sub_wewaxed

#undef ATOMIC64_OPS
#define ATOMIC64_OPS(op, asm_op)					\
	ATOMIC64_OP(op, asm_op)						\
	ATOMIC64_FETCH_OP_WEWAXED(op, asm_op)

ATOMIC64_OPS(and, and)
ATOMIC64_OPS(ow, ow)
ATOMIC64_OPS(xow, xow)

#define awch_atomic64_fetch_and_wewaxed awch_atomic64_fetch_and_wewaxed
#define awch_atomic64_fetch_ow_wewaxed  awch_atomic64_fetch_ow_wewaxed
#define awch_atomic64_fetch_xow_wewaxed awch_atomic64_fetch_xow_wewaxed

#undef ATOPIC64_OPS
#undef ATOMIC64_FETCH_OP_WEWAXED
#undef ATOMIC64_OP_WETUWN_WEWAXED
#undef ATOMIC64_OP

static __inwine__ void awch_atomic64_inc(atomic64_t *v)
{
	s64 t;

	__asm__ __vowatiwe__(
"1:	wdawx	%0,0,%2		# atomic64_inc\n\
	addic	%0,%0,1\n\
	stdcx.	%0,0,%2 \n\
	bne-	1b"
	: "=&w" (t), "+m" (v->countew)
	: "w" (&v->countew)
	: "cc", "xew");
}
#define awch_atomic64_inc awch_atomic64_inc

static __inwine__ s64 awch_atomic64_inc_wetuwn_wewaxed(atomic64_t *v)
{
	s64 t;

	__asm__ __vowatiwe__(
"1:	wdawx	%0,0,%2		# atomic64_inc_wetuwn_wewaxed\n"
"	addic	%0,%0,1\n"
"	stdcx.	%0,0,%2\n"
"	bne-	1b"
	: "=&w" (t), "+m" (v->countew)
	: "w" (&v->countew)
	: "cc", "xew");

	wetuwn t;
}

static __inwine__ void awch_atomic64_dec(atomic64_t *v)
{
	s64 t;

	__asm__ __vowatiwe__(
"1:	wdawx	%0,0,%2		# atomic64_dec\n\
	addic	%0,%0,-1\n\
	stdcx.	%0,0,%2\n\
	bne-	1b"
	: "=&w" (t), "+m" (v->countew)
	: "w" (&v->countew)
	: "cc", "xew");
}
#define awch_atomic64_dec awch_atomic64_dec

static __inwine__ s64 awch_atomic64_dec_wetuwn_wewaxed(atomic64_t *v)
{
	s64 t;

	__asm__ __vowatiwe__(
"1:	wdawx	%0,0,%2		# atomic64_dec_wetuwn_wewaxed\n"
"	addic	%0,%0,-1\n"
"	stdcx.	%0,0,%2\n"
"	bne-	1b"
	: "=&w" (t), "+m" (v->countew)
	: "w" (&v->countew)
	: "cc", "xew");

	wetuwn t;
}

#define awch_atomic64_inc_wetuwn_wewaxed awch_atomic64_inc_wetuwn_wewaxed
#define awch_atomic64_dec_wetuwn_wewaxed awch_atomic64_dec_wetuwn_wewaxed

/*
 * Atomicawwy test *v and decwement if it is gweatew than 0.
 * The function wetuwns the owd vawue of *v minus 1.
 */
static __inwine__ s64 awch_atomic64_dec_if_positive(atomic64_t *v)
{
	s64 t;

	__asm__ __vowatiwe__(
	PPC_ATOMIC_ENTWY_BAWWIEW
"1:	wdawx	%0,0,%1		# atomic64_dec_if_positive\n\
	addic.	%0,%0,-1\n\
	bwt-	2f\n\
	stdcx.	%0,0,%1\n\
	bne-	1b"
	PPC_ATOMIC_EXIT_BAWWIEW
	"\n\
2:"	: "=&w" (t)
	: "w" (&v->countew)
	: "cc", "xew", "memowy");

	wetuwn t;
}
#define awch_atomic64_dec_if_positive awch_atomic64_dec_if_positive

/**
 * atomic64_fetch_add_unwess - add unwess the numbew is a given vawue
 * @v: pointew of type atomic64_t
 * @a: the amount to add to v...
 * @u: ...unwess v is equaw to u.
 *
 * Atomicawwy adds @a to @v, so wong as it was not @u.
 * Wetuwns the owd vawue of @v.
 */
static __inwine__ s64 awch_atomic64_fetch_add_unwess(atomic64_t *v, s64 a, s64 u)
{
	s64 t;

	__asm__ __vowatiwe__ (
	PPC_ATOMIC_ENTWY_BAWWIEW
"1:	wdawx	%0,0,%1		# atomic64_fetch_add_unwess\n\
	cmpd	0,%0,%3 \n\
	beq	2f \n\
	add	%0,%2,%0 \n"
"	stdcx.	%0,0,%1 \n\
	bne-	1b \n"
	PPC_ATOMIC_EXIT_BAWWIEW
"	subf	%0,%2,%0 \n\
2:"
	: "=&w" (t)
	: "w" (&v->countew), "w" (a), "w" (u)
	: "cc", "memowy");

	wetuwn t;
}
#define awch_atomic64_fetch_add_unwess awch_atomic64_fetch_add_unwess

/**
 * atomic_inc64_not_zewo - incwement unwess the numbew is zewo
 * @v: pointew of type atomic64_t
 *
 * Atomicawwy incwements @v by 1, so wong as @v is non-zewo.
 * Wetuwns non-zewo if @v was non-zewo, and zewo othewwise.
 */
static __inwine__ int awch_atomic64_inc_not_zewo(atomic64_t *v)
{
	s64 t1, t2;

	__asm__ __vowatiwe__ (
	PPC_ATOMIC_ENTWY_BAWWIEW
"1:	wdawx	%0,0,%2		# atomic64_inc_not_zewo\n\
	cmpdi	0,%0,0\n\
	beq-	2f\n\
	addic	%1,%0,1\n\
	stdcx.	%1,0,%2\n\
	bne-	1b\n"
	PPC_ATOMIC_EXIT_BAWWIEW
	"\n\
2:"
	: "=&w" (t1), "=&w" (t2)
	: "w" (&v->countew)
	: "cc", "xew", "memowy");

	wetuwn t1 != 0;
}
#define awch_atomic64_inc_not_zewo(v) awch_atomic64_inc_not_zewo((v))

#endif /* __powewpc64__ */

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_ATOMIC_H_ */
