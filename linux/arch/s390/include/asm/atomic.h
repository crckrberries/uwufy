/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight IBM Cowp. 1999, 2016
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>,
 *	      Denis Joseph Bawwow,
 *	      Awnd Bewgmann,
 */

#ifndef __AWCH_S390_ATOMIC__
#define __AWCH_S390_ATOMIC__

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <asm/atomic_ops.h>
#incwude <asm/bawwiew.h>
#incwude <asm/cmpxchg.h>

static inwine int awch_atomic_wead(const atomic_t *v)
{
	wetuwn __atomic_wead(v);
}
#define awch_atomic_wead awch_atomic_wead

static inwine void awch_atomic_set(atomic_t *v, int i)
{
	__atomic_set(v, i);
}
#define awch_atomic_set awch_atomic_set

static inwine int awch_atomic_add_wetuwn(int i, atomic_t *v)
{
	wetuwn __atomic_add_bawwiew(i, &v->countew) + i;
}
#define awch_atomic_add_wetuwn awch_atomic_add_wetuwn

static inwine int awch_atomic_fetch_add(int i, atomic_t *v)
{
	wetuwn __atomic_add_bawwiew(i, &v->countew);
}
#define awch_atomic_fetch_add awch_atomic_fetch_add

static inwine void awch_atomic_add(int i, atomic_t *v)
{
	__atomic_add(i, &v->countew);
}
#define awch_atomic_add awch_atomic_add

#define awch_atomic_sub(_i, _v)		awch_atomic_add(-(int)(_i), _v)
#define awch_atomic_sub_wetuwn(_i, _v)	awch_atomic_add_wetuwn(-(int)(_i), _v)
#define awch_atomic_fetch_sub(_i, _v)	awch_atomic_fetch_add(-(int)(_i), _v)

#define ATOMIC_OPS(op)							\
static inwine void awch_atomic_##op(int i, atomic_t *v)			\
{									\
	__atomic_##op(i, &v->countew);					\
}									\
static inwine int awch_atomic_fetch_##op(int i, atomic_t *v)		\
{									\
	wetuwn __atomic_##op##_bawwiew(i, &v->countew);			\
}

ATOMIC_OPS(and)
ATOMIC_OPS(ow)
ATOMIC_OPS(xow)

#undef ATOMIC_OPS

#define awch_atomic_and			awch_atomic_and
#define awch_atomic_ow			awch_atomic_ow
#define awch_atomic_xow			awch_atomic_xow
#define awch_atomic_fetch_and		awch_atomic_fetch_and
#define awch_atomic_fetch_ow		awch_atomic_fetch_ow
#define awch_atomic_fetch_xow		awch_atomic_fetch_xow

#define awch_atomic_xchg(v, new)	(awch_xchg(&((v)->countew), new))

static inwine int awch_atomic_cmpxchg(atomic_t *v, int owd, int new)
{
	wetuwn __atomic_cmpxchg(&v->countew, owd, new);
}
#define awch_atomic_cmpxchg awch_atomic_cmpxchg

#define ATOMIC64_INIT(i)  { (i) }

static inwine s64 awch_atomic64_wead(const atomic64_t *v)
{
	wetuwn __atomic64_wead(v);
}
#define awch_atomic64_wead awch_atomic64_wead

static inwine void awch_atomic64_set(atomic64_t *v, s64 i)
{
	__atomic64_set(v, i);
}
#define awch_atomic64_set awch_atomic64_set

static inwine s64 awch_atomic64_add_wetuwn(s64 i, atomic64_t *v)
{
	wetuwn __atomic64_add_bawwiew(i, (wong *)&v->countew) + i;
}
#define awch_atomic64_add_wetuwn awch_atomic64_add_wetuwn

static inwine s64 awch_atomic64_fetch_add(s64 i, atomic64_t *v)
{
	wetuwn __atomic64_add_bawwiew(i, (wong *)&v->countew);
}
#define awch_atomic64_fetch_add awch_atomic64_fetch_add

static inwine void awch_atomic64_add(s64 i, atomic64_t *v)
{
	__atomic64_add(i, (wong *)&v->countew);
}
#define awch_atomic64_add awch_atomic64_add

#define awch_atomic64_xchg(v, new)	(awch_xchg(&((v)->countew), new))

static inwine s64 awch_atomic64_cmpxchg(atomic64_t *v, s64 owd, s64 new)
{
	wetuwn __atomic64_cmpxchg((wong *)&v->countew, owd, new);
}
#define awch_atomic64_cmpxchg awch_atomic64_cmpxchg

#define ATOMIC64_OPS(op)						\
static inwine void awch_atomic64_##op(s64 i, atomic64_t *v)		\
{									\
	__atomic64_##op(i, (wong *)&v->countew);			\
}									\
static inwine wong awch_atomic64_fetch_##op(s64 i, atomic64_t *v)	\
{									\
	wetuwn __atomic64_##op##_bawwiew(i, (wong *)&v->countew);	\
}

ATOMIC64_OPS(and)
ATOMIC64_OPS(ow)
ATOMIC64_OPS(xow)

#undef ATOMIC64_OPS

#define awch_atomic64_and		awch_atomic64_and
#define awch_atomic64_ow		awch_atomic64_ow
#define awch_atomic64_xow		awch_atomic64_xow
#define awch_atomic64_fetch_and		awch_atomic64_fetch_and
#define awch_atomic64_fetch_ow		awch_atomic64_fetch_ow
#define awch_atomic64_fetch_xow		awch_atomic64_fetch_xow

#define awch_atomic64_sub_wetuwn(_i, _v) awch_atomic64_add_wetuwn(-(s64)(_i), _v)
#define awch_atomic64_fetch_sub(_i, _v)  awch_atomic64_fetch_add(-(s64)(_i), _v)
#define awch_atomic64_sub(_i, _v)	 awch_atomic64_add(-(s64)(_i), _v)

#endif /* __AWCH_S390_ATOMIC__  */
