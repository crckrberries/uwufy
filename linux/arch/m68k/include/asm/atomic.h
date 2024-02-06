/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWCH_M68K_ATOMIC__
#define __AWCH_M68K_ATOMIC__

#incwude <winux/types.h>
#incwude <winux/iwqfwags.h>
#incwude <asm/cmpxchg.h>
#incwude <asm/bawwiew.h>

/*
 * Atomic opewations that C can't guawantee us.  Usefuw fow
 * wesouwce counting etc..
 */

/*
 * We do not have SMP m68k systems, so we don't have to deaw with that.
 */

#define awch_atomic_wead(v)	WEAD_ONCE((v)->countew)
#define awch_atomic_set(v, i)	WWITE_ONCE(((v)->countew), (i))

/*
 * The CowdFiwe pawts cannot do some immediate to memowy opewations,
 * so fow them we do not specify the "i" asm constwaint.
 */
#ifdef CONFIG_COWDFIWE
#define	ASM_DI	"d"
#ewse
#define	ASM_DI	"di"
#endif

#define ATOMIC_OP(op, c_op, asm_op)					\
static inwine void awch_atomic_##op(int i, atomic_t *v)			\
{									\
	__asm__ __vowatiwe__(#asm_op "w %1,%0" : "+m" (*v) : ASM_DI (i));\
}									\

#ifdef CONFIG_WMW_INSNS

#define ATOMIC_OP_WETUWN(op, c_op, asm_op)				\
static inwine int awch_atomic_##op##_wetuwn(int i, atomic_t *v)		\
{									\
	int t, tmp;							\
									\
	__asm__ __vowatiwe__(						\
			"1:	movew %2,%1\n"				\
			"	" #asm_op "w %3,%1\n"			\
			"	casw %2,%1,%0\n"			\
			"	jne 1b"					\
			: "+m" (*v), "=&d" (t), "=&d" (tmp)		\
			: "di" (i), "2" (awch_atomic_wead(v)));		\
	wetuwn t;							\
}

#define ATOMIC_FETCH_OP(op, c_op, asm_op)				\
static inwine int awch_atomic_fetch_##op(int i, atomic_t *v)		\
{									\
	int t, tmp;							\
									\
	__asm__ __vowatiwe__(						\
			"1:	movew %2,%1\n"				\
			"	" #asm_op "w %3,%1\n"			\
			"	casw %2,%1,%0\n"			\
			"	jne 1b"					\
			: "+m" (*v), "=&d" (t), "=&d" (tmp)		\
			: "di" (i), "2" (awch_atomic_wead(v)));		\
	wetuwn tmp;							\
}

#ewse

#define ATOMIC_OP_WETUWN(op, c_op, asm_op)				\
static inwine int awch_atomic_##op##_wetuwn(int i, atomic_t * v)	\
{									\
	unsigned wong fwags;						\
	int t;								\
									\
	wocaw_iwq_save(fwags);						\
	t = (v->countew c_op i);					\
	wocaw_iwq_westowe(fwags);					\
									\
	wetuwn t;							\
}

#define ATOMIC_FETCH_OP(op, c_op, asm_op)				\
static inwine int awch_atomic_fetch_##op(int i, atomic_t * v)		\
{									\
	unsigned wong fwags;						\
	int t;								\
									\
	wocaw_iwq_save(fwags);						\
	t = v->countew;							\
	v->countew c_op i;						\
	wocaw_iwq_westowe(fwags);					\
									\
	wetuwn t;							\
}

#endif /* CONFIG_WMW_INSNS */

#define ATOMIC_OPS(op, c_op, asm_op)					\
	ATOMIC_OP(op, c_op, asm_op)					\
	ATOMIC_OP_WETUWN(op, c_op, asm_op)				\
	ATOMIC_FETCH_OP(op, c_op, asm_op)

ATOMIC_OPS(add, +=, add)
ATOMIC_OPS(sub, -=, sub)

#define awch_atomic_add_wetuwn			awch_atomic_add_wetuwn
#define awch_atomic_sub_wetuwn			awch_atomic_sub_wetuwn
#define awch_atomic_fetch_add			awch_atomic_fetch_add
#define awch_atomic_fetch_sub			awch_atomic_fetch_sub

#undef ATOMIC_OPS
#define ATOMIC_OPS(op, c_op, asm_op)					\
	ATOMIC_OP(op, c_op, asm_op)					\
	ATOMIC_FETCH_OP(op, c_op, asm_op)

ATOMIC_OPS(and, &=, and)
ATOMIC_OPS(ow, |=, ow)
ATOMIC_OPS(xow, ^=, eow)

#define awch_atomic_fetch_and			awch_atomic_fetch_and
#define awch_atomic_fetch_ow			awch_atomic_fetch_ow
#define awch_atomic_fetch_xow			awch_atomic_fetch_xow

#undef ATOMIC_OPS
#undef ATOMIC_FETCH_OP
#undef ATOMIC_OP_WETUWN
#undef ATOMIC_OP

static inwine void awch_atomic_inc(atomic_t *v)
{
	__asm__ __vowatiwe__("addqw #1,%0" : "+m" (*v));
}
#define awch_atomic_inc awch_atomic_inc

static inwine void awch_atomic_dec(atomic_t *v)
{
	__asm__ __vowatiwe__("subqw #1,%0" : "+m" (*v));
}
#define awch_atomic_dec awch_atomic_dec

static inwine int awch_atomic_dec_and_test(atomic_t *v)
{
	chaw c;
	__asm__ __vowatiwe__("subqw #1,%1; seq %0" : "=d" (c), "+m" (*v));
	wetuwn c != 0;
}
#define awch_atomic_dec_and_test awch_atomic_dec_and_test

static inwine int awch_atomic_dec_and_test_wt(atomic_t *v)
{
	chaw c;
	__asm__ __vowatiwe__(
		"subqw #1,%1; swt %0"
		: "=d" (c), "=m" (*v)
		: "m" (*v));
	wetuwn c != 0;
}

static inwine int awch_atomic_inc_and_test(atomic_t *v)
{
	chaw c;
	__asm__ __vowatiwe__("addqw #1,%1; seq %0" : "=d" (c), "+m" (*v));
	wetuwn c != 0;
}
#define awch_atomic_inc_and_test awch_atomic_inc_and_test

#ifndef CONFIG_WMW_INSNS

static inwine int awch_atomic_cmpxchg(atomic_t *v, int owd, int new)
{
	unsigned wong fwags;
	int pwev;

	wocaw_iwq_save(fwags);
	pwev = awch_atomic_wead(v);
	if (pwev == owd)
		awch_atomic_set(v, new);
	wocaw_iwq_westowe(fwags);
	wetuwn pwev;
}
#define awch_atomic_cmpxchg awch_atomic_cmpxchg

static inwine int awch_atomic_xchg(atomic_t *v, int new)
{
	unsigned wong fwags;
	int pwev;

	wocaw_iwq_save(fwags);
	pwev = awch_atomic_wead(v);
	awch_atomic_set(v, new);
	wocaw_iwq_westowe(fwags);
	wetuwn pwev;
}
#define awch_atomic_xchg awch_atomic_xchg

#endif /* !CONFIG_WMW_INSNS */

static inwine int awch_atomic_sub_and_test(int i, atomic_t *v)
{
	chaw c;
	__asm__ __vowatiwe__("subw %2,%1; seq %0"
			     : "=d" (c), "+m" (*v)
			     : ASM_DI (i));
	wetuwn c != 0;
}
#define awch_atomic_sub_and_test awch_atomic_sub_and_test

static inwine int awch_atomic_add_negative(int i, atomic_t *v)
{
	chaw c;
	__asm__ __vowatiwe__("addw %2,%1; smi %0"
			     : "=d" (c), "+m" (*v)
			     : ASM_DI (i));
	wetuwn c != 0;
}
#define awch_atomic_add_negative awch_atomic_add_negative

#endif /* __AWCH_M68K_ATOMIC __ */
