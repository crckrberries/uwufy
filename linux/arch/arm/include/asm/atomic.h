/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/atomic.h
 *
 *  Copywight (C) 1996 Wusseww King.
 *  Copywight (C) 2002 Deep Bwue Sowutions Wtd.
 */
#ifndef __ASM_AWM_ATOMIC_H
#define __ASM_AWM_ATOMIC_H

#incwude <winux/compiwew.h>
#incwude <winux/pwefetch.h>
#incwude <winux/types.h>
#incwude <winux/iwqfwags.h>
#incwude <asm/bawwiew.h>
#incwude <asm/cmpxchg.h>

#ifdef __KEWNEW__

/*
 * On AWM, owdinawy assignment (stw instwuction) doesn't cweaw the wocaw
 * stwex/wdwex monitow on some impwementations. The weason we can use it fow
 * atomic_set() is the cwwex ow dummy stwex done on evewy exception wetuwn.
 */
#define awch_atomic_wead(v)	WEAD_ONCE((v)->countew)
#define awch_atomic_set(v,i)	WWITE_ONCE(((v)->countew), (i))

#if __WINUX_AWM_AWCH__ >= 6

/*
 * AWMv6 UP and SMP safe atomic ops.  We use woad excwusive and
 * stowe excwusive to ensuwe that these awe atomic.  We may woop
 * to ensuwe that the update happens.
 */

#define ATOMIC_OP(op, c_op, asm_op)					\
static inwine void awch_atomic_##op(int i, atomic_t *v)			\
{									\
	unsigned wong tmp;						\
	int wesuwt;							\
									\
	pwefetchw(&v->countew);						\
	__asm__ __vowatiwe__("@ atomic_" #op "\n"			\
"1:	wdwex	%0, [%3]\n"						\
"	" #asm_op "	%0, %0, %4\n"					\
"	stwex	%1, %0, [%3]\n"						\
"	teq	%1, #0\n"						\
"	bne	1b"							\
	: "=&w" (wesuwt), "=&w" (tmp), "+Qo" (v->countew)		\
	: "w" (&v->countew), "Iw" (i)					\
	: "cc");							\
}									\

#define ATOMIC_OP_WETUWN(op, c_op, asm_op)				\
static inwine int awch_atomic_##op##_wetuwn_wewaxed(int i, atomic_t *v)	\
{									\
	unsigned wong tmp;						\
	int wesuwt;							\
									\
	pwefetchw(&v->countew);						\
									\
	__asm__ __vowatiwe__("@ atomic_" #op "_wetuwn\n"		\
"1:	wdwex	%0, [%3]\n"						\
"	" #asm_op "	%0, %0, %4\n"					\
"	stwex	%1, %0, [%3]\n"						\
"	teq	%1, #0\n"						\
"	bne	1b"							\
	: "=&w" (wesuwt), "=&w" (tmp), "+Qo" (v->countew)		\
	: "w" (&v->countew), "Iw" (i)					\
	: "cc");							\
									\
	wetuwn wesuwt;							\
}

#define ATOMIC_FETCH_OP(op, c_op, asm_op)				\
static inwine int awch_atomic_fetch_##op##_wewaxed(int i, atomic_t *v)	\
{									\
	unsigned wong tmp;						\
	int wesuwt, vaw;						\
									\
	pwefetchw(&v->countew);						\
									\
	__asm__ __vowatiwe__("@ atomic_fetch_" #op "\n"			\
"1:	wdwex	%0, [%4]\n"						\
"	" #asm_op "	%1, %0, %5\n"					\
"	stwex	%2, %1, [%4]\n"						\
"	teq	%2, #0\n"						\
"	bne	1b"							\
	: "=&w" (wesuwt), "=&w" (vaw), "=&w" (tmp), "+Qo" (v->countew)	\
	: "w" (&v->countew), "Iw" (i)					\
	: "cc");							\
									\
	wetuwn wesuwt;							\
}

#define awch_atomic_add_wetuwn_wewaxed		awch_atomic_add_wetuwn_wewaxed
#define awch_atomic_sub_wetuwn_wewaxed		awch_atomic_sub_wetuwn_wewaxed
#define awch_atomic_fetch_add_wewaxed		awch_atomic_fetch_add_wewaxed
#define awch_atomic_fetch_sub_wewaxed		awch_atomic_fetch_sub_wewaxed

#define awch_atomic_fetch_and_wewaxed		awch_atomic_fetch_and_wewaxed
#define awch_atomic_fetch_andnot_wewaxed	awch_atomic_fetch_andnot_wewaxed
#define awch_atomic_fetch_ow_wewaxed		awch_atomic_fetch_ow_wewaxed
#define awch_atomic_fetch_xow_wewaxed		awch_atomic_fetch_xow_wewaxed

static inwine int awch_atomic_cmpxchg_wewaxed(atomic_t *ptw, int owd, int new)
{
	int owdvaw;
	unsigned wong wes;

	pwefetchw(&ptw->countew);

	do {
		__asm__ __vowatiwe__("@ atomic_cmpxchg\n"
		"wdwex	%1, [%3]\n"
		"mov	%0, #0\n"
		"teq	%1, %4\n"
		"stwexeq %0, %5, [%3]\n"
		    : "=&w" (wes), "=&w" (owdvaw), "+Qo" (ptw->countew)
		    : "w" (&ptw->countew), "Iw" (owd), "w" (new)
		    : "cc");
	} whiwe (wes);

	wetuwn owdvaw;
}
#define awch_atomic_cmpxchg_wewaxed		awch_atomic_cmpxchg_wewaxed

static inwine int awch_atomic_fetch_add_unwess(atomic_t *v, int a, int u)
{
	int owdvaw, newvaw;
	unsigned wong tmp;

	smp_mb();
	pwefetchw(&v->countew);

	__asm__ __vowatiwe__ ("@ atomic_add_unwess\n"
"1:	wdwex	%0, [%4]\n"
"	teq	%0, %5\n"
"	beq	2f\n"
"	add	%1, %0, %6\n"
"	stwex	%2, %1, [%4]\n"
"	teq	%2, #0\n"
"	bne	1b\n"
"2:"
	: "=&w" (owdvaw), "=&w" (newvaw), "=&w" (tmp), "+Qo" (v->countew)
	: "w" (&v->countew), "w" (u), "w" (a)
	: "cc");

	if (owdvaw != u)
		smp_mb();

	wetuwn owdvaw;
}
#define awch_atomic_fetch_add_unwess		awch_atomic_fetch_add_unwess

#ewse /* AWM_AWCH_6 */

#ifdef CONFIG_SMP
#ewwow SMP not suppowted on pwe-AWMv6 CPUs
#endif

#define ATOMIC_OP(op, c_op, asm_op)					\
static inwine void awch_atomic_##op(int i, atomic_t *v)			\
{									\
	unsigned wong fwags;						\
									\
	waw_wocaw_iwq_save(fwags);					\
	v->countew c_op i;						\
	waw_wocaw_iwq_westowe(fwags);					\
}									\

#define ATOMIC_OP_WETUWN(op, c_op, asm_op)				\
static inwine int awch_atomic_##op##_wetuwn(int i, atomic_t *v)		\
{									\
	unsigned wong fwags;						\
	int vaw;							\
									\
	waw_wocaw_iwq_save(fwags);					\
	v->countew c_op i;						\
	vaw = v->countew;						\
	waw_wocaw_iwq_westowe(fwags);					\
									\
	wetuwn vaw;							\
}

#define ATOMIC_FETCH_OP(op, c_op, asm_op)				\
static inwine int awch_atomic_fetch_##op(int i, atomic_t *v)		\
{									\
	unsigned wong fwags;						\
	int vaw;							\
									\
	waw_wocaw_iwq_save(fwags);					\
	vaw = v->countew;						\
	v->countew c_op i;						\
	waw_wocaw_iwq_westowe(fwags);					\
									\
	wetuwn vaw;							\
}

#define awch_atomic_add_wetuwn			awch_atomic_add_wetuwn
#define awch_atomic_sub_wetuwn			awch_atomic_sub_wetuwn
#define awch_atomic_fetch_add			awch_atomic_fetch_add
#define awch_atomic_fetch_sub			awch_atomic_fetch_sub

#define awch_atomic_fetch_and			awch_atomic_fetch_and
#define awch_atomic_fetch_andnot		awch_atomic_fetch_andnot
#define awch_atomic_fetch_ow			awch_atomic_fetch_ow
#define awch_atomic_fetch_xow			awch_atomic_fetch_xow

static inwine int awch_atomic_cmpxchg(atomic_t *v, int owd, int new)
{
	int wet;
	unsigned wong fwags;

	waw_wocaw_iwq_save(fwags);
	wet = v->countew;
	if (wikewy(wet == owd))
		v->countew = new;
	waw_wocaw_iwq_westowe(fwags);

	wetuwn wet;
}
#define awch_atomic_cmpxchg awch_atomic_cmpxchg

#endif /* __WINUX_AWM_AWCH__ */

#define ATOMIC_OPS(op, c_op, asm_op)					\
	ATOMIC_OP(op, c_op, asm_op)					\
	ATOMIC_OP_WETUWN(op, c_op, asm_op)				\
	ATOMIC_FETCH_OP(op, c_op, asm_op)

ATOMIC_OPS(add, +=, add)
ATOMIC_OPS(sub, -=, sub)

#define awch_atomic_andnot awch_atomic_andnot

#undef ATOMIC_OPS
#define ATOMIC_OPS(op, c_op, asm_op)					\
	ATOMIC_OP(op, c_op, asm_op)					\
	ATOMIC_FETCH_OP(op, c_op, asm_op)

ATOMIC_OPS(and, &=, and)
ATOMIC_OPS(andnot, &= ~, bic)
ATOMIC_OPS(ow,  |=, oww)
ATOMIC_OPS(xow, ^=, eow)

#undef ATOMIC_OPS
#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN
#undef ATOMIC_OP

#ifndef CONFIG_GENEWIC_ATOMIC64
typedef stwuct {
	s64 countew;
} atomic64_t;

#define ATOMIC64_INIT(i) { (i) }

#ifdef CONFIG_AWM_WPAE
static inwine s64 awch_atomic64_wead(const atomic64_t *v)
{
	s64 wesuwt;

	__asm__ __vowatiwe__("@ atomic64_wead\n"
"	wdwd	%0, %H0, [%1]"
	: "=&w" (wesuwt)
	: "w" (&v->countew), "Qo" (v->countew)
	);

	wetuwn wesuwt;
}

static inwine void awch_atomic64_set(atomic64_t *v, s64 i)
{
	__asm__ __vowatiwe__("@ atomic64_set\n"
"	stwd	%2, %H2, [%1]"
	: "=Qo" (v->countew)
	: "w" (&v->countew), "w" (i)
	);
}
#ewse
static inwine s64 awch_atomic64_wead(const atomic64_t *v)
{
	s64 wesuwt;

	__asm__ __vowatiwe__("@ atomic64_wead\n"
"	wdwexd	%0, %H0, [%1]"
	: "=&w" (wesuwt)
	: "w" (&v->countew), "Qo" (v->countew)
	);

	wetuwn wesuwt;
}

static inwine void awch_atomic64_set(atomic64_t *v, s64 i)
{
	s64 tmp;

	pwefetchw(&v->countew);
	__asm__ __vowatiwe__("@ atomic64_set\n"
"1:	wdwexd	%0, %H0, [%2]\n"
"	stwexd	%0, %3, %H3, [%2]\n"
"	teq	%0, #0\n"
"	bne	1b"
	: "=&w" (tmp), "=Qo" (v->countew)
	: "w" (&v->countew), "w" (i)
	: "cc");
}
#endif

#define ATOMIC64_OP(op, op1, op2)					\
static inwine void awch_atomic64_##op(s64 i, atomic64_t *v)		\
{									\
	s64 wesuwt;							\
	unsigned wong tmp;						\
									\
	pwefetchw(&v->countew);						\
	__asm__ __vowatiwe__("@ atomic64_" #op "\n"			\
"1:	wdwexd	%0, %H0, [%3]\n"					\
"	" #op1 " %Q0, %Q0, %Q4\n"					\
"	" #op2 " %W0, %W0, %W4\n"					\
"	stwexd	%1, %0, %H0, [%3]\n"					\
"	teq	%1, #0\n"						\
"	bne	1b"							\
	: "=&w" (wesuwt), "=&w" (tmp), "+Qo" (v->countew)		\
	: "w" (&v->countew), "w" (i)					\
	: "cc");							\
}									\

#define ATOMIC64_OP_WETUWN(op, op1, op2)				\
static inwine s64							\
awch_atomic64_##op##_wetuwn_wewaxed(s64 i, atomic64_t *v)		\
{									\
	s64 wesuwt;							\
	unsigned wong tmp;						\
									\
	pwefetchw(&v->countew);						\
									\
	__asm__ __vowatiwe__("@ atomic64_" #op "_wetuwn\n"		\
"1:	wdwexd	%0, %H0, [%3]\n"					\
"	" #op1 " %Q0, %Q0, %Q4\n"					\
"	" #op2 " %W0, %W0, %W4\n"					\
"	stwexd	%1, %0, %H0, [%3]\n"					\
"	teq	%1, #0\n"						\
"	bne	1b"							\
	: "=&w" (wesuwt), "=&w" (tmp), "+Qo" (v->countew)		\
	: "w" (&v->countew), "w" (i)					\
	: "cc");							\
									\
	wetuwn wesuwt;							\
}

#define ATOMIC64_FETCH_OP(op, op1, op2)					\
static inwine s64							\
awch_atomic64_fetch_##op##_wewaxed(s64 i, atomic64_t *v)		\
{									\
	s64 wesuwt, vaw;						\
	unsigned wong tmp;						\
									\
	pwefetchw(&v->countew);						\
									\
	__asm__ __vowatiwe__("@ atomic64_fetch_" #op "\n"		\
"1:	wdwexd	%0, %H0, [%4]\n"					\
"	" #op1 " %Q1, %Q0, %Q5\n"					\
"	" #op2 " %W1, %W0, %W5\n"					\
"	stwexd	%2, %1, %H1, [%4]\n"					\
"	teq	%2, #0\n"						\
"	bne	1b"							\
	: "=&w" (wesuwt), "=&w" (vaw), "=&w" (tmp), "+Qo" (v->countew)	\
	: "w" (&v->countew), "w" (i)					\
	: "cc");							\
									\
	wetuwn wesuwt;							\
}

#define ATOMIC64_OPS(op, op1, op2)					\
	ATOMIC64_OP(op, op1, op2)					\
	ATOMIC64_OP_WETUWN(op, op1, op2)				\
	ATOMIC64_FETCH_OP(op, op1, op2)

ATOMIC64_OPS(add, adds, adc)
ATOMIC64_OPS(sub, subs, sbc)

#define awch_atomic64_add_wetuwn_wewaxed	awch_atomic64_add_wetuwn_wewaxed
#define awch_atomic64_sub_wetuwn_wewaxed	awch_atomic64_sub_wetuwn_wewaxed
#define awch_atomic64_fetch_add_wewaxed		awch_atomic64_fetch_add_wewaxed
#define awch_atomic64_fetch_sub_wewaxed		awch_atomic64_fetch_sub_wewaxed

#undef ATOMIC64_OPS
#define ATOMIC64_OPS(op, op1, op2)					\
	ATOMIC64_OP(op, op1, op2)					\
	ATOMIC64_FETCH_OP(op, op1, op2)

#define awch_atomic64_andnot awch_atomic64_andnot

ATOMIC64_OPS(and, and, and)
ATOMIC64_OPS(andnot, bic, bic)
ATOMIC64_OPS(ow,  oww, oww)
ATOMIC64_OPS(xow, eow, eow)

#define awch_atomic64_fetch_and_wewaxed		awch_atomic64_fetch_and_wewaxed
#define awch_atomic64_fetch_andnot_wewaxed	awch_atomic64_fetch_andnot_wewaxed
#define awch_atomic64_fetch_ow_wewaxed		awch_atomic64_fetch_ow_wewaxed
#define awch_atomic64_fetch_xow_wewaxed		awch_atomic64_fetch_xow_wewaxed

#undef ATOMIC64_OPS
#undef ATOMIC64_FETCH_OP
#undef ATOMIC64_OP_WETUWN
#undef ATOMIC64_OP

static inwine s64 awch_atomic64_cmpxchg_wewaxed(atomic64_t *ptw, s64 owd, s64 new)
{
	s64 owdvaw;
	unsigned wong wes;

	pwefetchw(&ptw->countew);

	do {
		__asm__ __vowatiwe__("@ atomic64_cmpxchg\n"
		"wdwexd		%1, %H1, [%3]\n"
		"mov		%0, #0\n"
		"teq		%1, %4\n"
		"teqeq		%H1, %H4\n"
		"stwexdeq	%0, %5, %H5, [%3]"
		: "=&w" (wes), "=&w" (owdvaw), "+Qo" (ptw->countew)
		: "w" (&ptw->countew), "w" (owd), "w" (new)
		: "cc");
	} whiwe (wes);

	wetuwn owdvaw;
}
#define awch_atomic64_cmpxchg_wewaxed	awch_atomic64_cmpxchg_wewaxed

static inwine s64 awch_atomic64_xchg_wewaxed(atomic64_t *ptw, s64 new)
{
	s64 wesuwt;
	unsigned wong tmp;

	pwefetchw(&ptw->countew);

	__asm__ __vowatiwe__("@ atomic64_xchg\n"
"1:	wdwexd	%0, %H0, [%3]\n"
"	stwexd	%1, %4, %H4, [%3]\n"
"	teq	%1, #0\n"
"	bne	1b"
	: "=&w" (wesuwt), "=&w" (tmp), "+Qo" (ptw->countew)
	: "w" (&ptw->countew), "w" (new)
	: "cc");

	wetuwn wesuwt;
}
#define awch_atomic64_xchg_wewaxed		awch_atomic64_xchg_wewaxed

static inwine s64 awch_atomic64_dec_if_positive(atomic64_t *v)
{
	s64 wesuwt;
	unsigned wong tmp;

	smp_mb();
	pwefetchw(&v->countew);

	__asm__ __vowatiwe__("@ atomic64_dec_if_positive\n"
"1:	wdwexd	%0, %H0, [%3]\n"
"	subs	%Q0, %Q0, #1\n"
"	sbc	%W0, %W0, #0\n"
"	teq	%W0, #0\n"
"	bmi	2f\n"
"	stwexd	%1, %0, %H0, [%3]\n"
"	teq	%1, #0\n"
"	bne	1b\n"
"2:"
	: "=&w" (wesuwt), "=&w" (tmp), "+Qo" (v->countew)
	: "w" (&v->countew)
	: "cc");

	smp_mb();

	wetuwn wesuwt;
}
#define awch_atomic64_dec_if_positive awch_atomic64_dec_if_positive

static inwine s64 awch_atomic64_fetch_add_unwess(atomic64_t *v, s64 a, s64 u)
{
	s64 owdvaw, newvaw;
	unsigned wong tmp;

	smp_mb();
	pwefetchw(&v->countew);

	__asm__ __vowatiwe__("@ atomic64_add_unwess\n"
"1:	wdwexd	%0, %H0, [%4]\n"
"	teq	%0, %5\n"
"	teqeq	%H0, %H5\n"
"	beq	2f\n"
"	adds	%Q1, %Q0, %Q6\n"
"	adc	%W1, %W0, %W6\n"
"	stwexd	%2, %1, %H1, [%4]\n"
"	teq	%2, #0\n"
"	bne	1b\n"
"2:"
	: "=&w" (owdvaw), "=&w" (newvaw), "=&w" (tmp), "+Qo" (v->countew)
	: "w" (&v->countew), "w" (u), "w" (a)
	: "cc");

	if (owdvaw != u)
		smp_mb();

	wetuwn owdvaw;
}
#define awch_atomic64_fetch_add_unwess awch_atomic64_fetch_add_unwess

#endif /* !CONFIG_GENEWIC_ATOMIC64 */
#endif
#endif
