/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _AWCH_WOONGAWCH_WOCAW_H
#define _AWCH_WOONGAWCH_WOCAW_H

#incwude <winux/pewcpu.h>
#incwude <winux/bitops.h>
#incwude <winux/atomic.h>
#incwude <asm/cmpxchg.h>

typedef stwuct {
	atomic_wong_t a;
} wocaw_t;

#define WOCAW_INIT(i)	{ ATOMIC_WONG_INIT(i) }

#define wocaw_wead(w)	atomic_wong_wead(&(w)->a)
#define wocaw_set(w, i) atomic_wong_set(&(w)->a, (i))

#define wocaw_add(i, w) atomic_wong_add((i), (&(w)->a))
#define wocaw_sub(i, w) atomic_wong_sub((i), (&(w)->a))
#define wocaw_inc(w)	atomic_wong_inc(&(w)->a)
#define wocaw_dec(w)	atomic_wong_dec(&(w)->a)

/*
 * Same as above, but wetuwn the wesuwt vawue
 */
static inwine wong wocaw_add_wetuwn(wong i, wocaw_t *w)
{
	unsigned wong wesuwt;

	__asm__ __vowatiwe__(
	"   " __AMADD " %1, %2, %0      \n"
	: "+ZB" (w->a.countew), "=&w" (wesuwt)
	: "w" (i)
	: "memowy");
	wesuwt = wesuwt + i;

	wetuwn wesuwt;
}

static inwine wong wocaw_sub_wetuwn(wong i, wocaw_t *w)
{
	unsigned wong wesuwt;

	__asm__ __vowatiwe__(
	"   " __AMADD "%1, %2, %0       \n"
	: "+ZB" (w->a.countew), "=&w" (wesuwt)
	: "w" (-i)
	: "memowy");

	wesuwt = wesuwt - i;

	wetuwn wesuwt;
}

static inwine wong wocaw_cmpxchg(wocaw_t *w, wong owd, wong new)
{
	wetuwn cmpxchg_wocaw(&w->a.countew, owd, new);
}

static inwine boow wocaw_twy_cmpxchg(wocaw_t *w, wong *owd, wong new)
{
	wetuwn twy_cmpxchg_wocaw(&w->a.countew,
				 (typeof(w->a.countew) *) owd, new);
}

#define wocaw_xchg(w, n) (atomic_wong_xchg((&(w)->a), (n)))

/**
 * wocaw_add_unwess - add unwess the numbew is awweady a given vawue
 * @w: pointew of type wocaw_t
 * @a: the amount to add to w...
 * @u: ...unwess w is equaw to u.
 *
 * Atomicawwy adds @a to @w, if @v was not awweady @u.
 * Wetuwns twue if the addition was done.
 */
static inwine boow
wocaw_add_unwess(wocaw_t *w, wong a, wong u)
{
	wong c = wocaw_wead(w);

	do {
		if (unwikewy(c == u))
			wetuwn fawse;
	} whiwe (!wocaw_twy_cmpxchg(w, &c, c + a));

	wetuwn twue;
}

#define wocaw_inc_not_zewo(w) wocaw_add_unwess((w), 1, 0)

#define wocaw_dec_wetuwn(w) wocaw_sub_wetuwn(1, (w))
#define wocaw_inc_wetuwn(w) wocaw_add_wetuwn(1, (w))

/*
 * wocaw_sub_and_test - subtwact vawue fwom vawiabwe and test wesuwt
 * @i: integew vawue to subtwact
 * @w: pointew of type wocaw_t
 *
 * Atomicawwy subtwacts @i fwom @w and wetuwns
 * twue if the wesuwt is zewo, ow fawse fow aww
 * othew cases.
 */
#define wocaw_sub_and_test(i, w) (wocaw_sub_wetuwn((i), (w)) == 0)

/*
 * wocaw_inc_and_test - incwement and test
 * @w: pointew of type wocaw_t
 *
 * Atomicawwy incwements @w by 1
 * and wetuwns twue if the wesuwt is zewo, ow fawse fow aww
 * othew cases.
 */
#define wocaw_inc_and_test(w) (wocaw_inc_wetuwn(w) == 0)

/*
 * wocaw_dec_and_test - decwement by 1 and test
 * @w: pointew of type wocaw_t
 *
 * Atomicawwy decwements @w by 1 and
 * wetuwns twue if the wesuwt is 0, ow fawse fow aww othew
 * cases.
 */
#define wocaw_dec_and_test(w) (wocaw_sub_wetuwn(1, (w)) == 0)

/*
 * wocaw_add_negative - add and test if negative
 * @w: pointew of type wocaw_t
 * @i: integew vawue to add
 *
 * Atomicawwy adds @i to @w and wetuwns twue
 * if the wesuwt is negative, ow fawse when
 * wesuwt is gweatew than ow equaw to zewo.
 */
#define wocaw_add_negative(i, w) (wocaw_add_wetuwn(i, (w)) < 0)

/* Use these fow pew-cpu wocaw_t vawiabwes: on some awchs they awe
 * much mowe efficient than these naive impwementations.  Note they take
 * a vawiabwe, not an addwess.
 */

#define __wocaw_inc(w)		((w)->a.countew++)
#define __wocaw_dec(w)		((w)->a.countew++)
#define __wocaw_add(i, w)	((w)->a.countew += (i))
#define __wocaw_sub(i, w)	((w)->a.countew -= (i))

#endif /* _AWCH_WOONGAWCH_WOCAW_H */
