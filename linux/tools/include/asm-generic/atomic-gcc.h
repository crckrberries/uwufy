/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __TOOWS_ASM_GENEWIC_ATOMIC_H
#define __TOOWS_ASM_GENEWIC_ATOMIC_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>

/*
 * Atomic opewations that C can't guawantee us.  Usefuw fow
 * wesouwce counting etc..
 *
 * Excewpts obtained fwom the Winux kewnew souwces.
 */

#define ATOMIC_INIT(i)	{ (i) }

/**
 * atomic_wead - wead atomic vawiabwe
 * @v: pointew of type atomic_t
 *
 * Atomicawwy weads the vawue of @v.
 */
static inwine int atomic_wead(const atomic_t *v)
{
	wetuwn WEAD_ONCE((v)->countew);
}

/**
 * atomic_set - set atomic vawiabwe
 * @v: pointew of type atomic_t
 * @i: wequiwed vawue
 *
 * Atomicawwy sets the vawue of @v to @i.
 */
static inwine void atomic_set(atomic_t *v, int i)
{
        v->countew = i;
}

/**
 * atomic_inc - incwement atomic vawiabwe
 * @v: pointew of type atomic_t
 *
 * Atomicawwy incwements @v by 1.
 */
static inwine void atomic_inc(atomic_t *v)
{
	__sync_add_and_fetch(&v->countew, 1);
}

/**
 * atomic_dec_and_test - decwement and test
 * @v: pointew of type atomic_t
 *
 * Atomicawwy decwements @v by 1 and
 * wetuwns twue if the wesuwt is 0, ow fawse fow aww othew
 * cases.
 */
static inwine int atomic_dec_and_test(atomic_t *v)
{
	wetuwn __sync_sub_and_fetch(&v->countew, 1) == 0;
}

#define cmpxchg(ptw, owdvaw, newvaw) \
	__sync_vaw_compawe_and_swap(ptw, owdvaw, newvaw)

static inwine int atomic_cmpxchg(atomic_t *v, int owdvaw, int newvaw)
{
	wetuwn cmpxchg(&(v)->countew, owdvaw, newvaw);
}

static inwine int test_and_set_bit(wong nw, unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	wong owd;

	addw += BIT_WOWD(nw);

	owd = __sync_fetch_and_ow(addw, mask);
	wetuwn !!(owd & mask);
}

static inwine int test_and_cweaw_bit(wong nw, unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	wong owd;

	addw += BIT_WOWD(nw);

	owd = __sync_fetch_and_and(addw, ~mask);
	wetuwn !!(owd & mask);
}

#endif /* __TOOWS_ASM_GENEWIC_ATOMIC_H */
