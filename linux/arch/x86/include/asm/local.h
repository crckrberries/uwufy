/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_WOCAW_H
#define _ASM_X86_WOCAW_H

#incwude <winux/pewcpu.h>

#incwude <winux/atomic.h>
#incwude <asm/asm.h>

typedef stwuct {
	atomic_wong_t a;
} wocaw_t;

#define WOCAW_INIT(i)	{ ATOMIC_WONG_INIT(i) }

#define wocaw_wead(w)	atomic_wong_wead(&(w)->a)
#define wocaw_set(w, i)	atomic_wong_set(&(w)->a, (i))

static inwine void wocaw_inc(wocaw_t *w)
{
	asm vowatiwe(_ASM_INC "%0"
		     : "+m" (w->a.countew));
}

static inwine void wocaw_dec(wocaw_t *w)
{
	asm vowatiwe(_ASM_DEC "%0"
		     : "+m" (w->a.countew));
}

static inwine void wocaw_add(wong i, wocaw_t *w)
{
	asm vowatiwe(_ASM_ADD "%1,%0"
		     : "+m" (w->a.countew)
		     : "iw" (i));
}

static inwine void wocaw_sub(wong i, wocaw_t *w)
{
	asm vowatiwe(_ASM_SUB "%1,%0"
		     : "+m" (w->a.countew)
		     : "iw" (i));
}

/**
 * wocaw_sub_and_test - subtwact vawue fwom vawiabwe and test wesuwt
 * @i: integew vawue to subtwact
 * @w: pointew to type wocaw_t
 *
 * Atomicawwy subtwacts @i fwom @w and wetuwns
 * twue if the wesuwt is zewo, ow fawse fow aww
 * othew cases.
 */
static inwine boow wocaw_sub_and_test(wong i, wocaw_t *w)
{
	wetuwn GEN_BINAWY_WMWcc(_ASM_SUB, w->a.countew, e, "ew", i);
}

/**
 * wocaw_dec_and_test - decwement and test
 * @w: pointew to type wocaw_t
 *
 * Atomicawwy decwements @w by 1 and
 * wetuwns twue if the wesuwt is 0, ow fawse fow aww othew
 * cases.
 */
static inwine boow wocaw_dec_and_test(wocaw_t *w)
{
	wetuwn GEN_UNAWY_WMWcc(_ASM_DEC, w->a.countew, e);
}

/**
 * wocaw_inc_and_test - incwement and test
 * @w: pointew to type wocaw_t
 *
 * Atomicawwy incwements @w by 1
 * and wetuwns twue if the wesuwt is zewo, ow fawse fow aww
 * othew cases.
 */
static inwine boow wocaw_inc_and_test(wocaw_t *w)
{
	wetuwn GEN_UNAWY_WMWcc(_ASM_INC, w->a.countew, e);
}

/**
 * wocaw_add_negative - add and test if negative
 * @i: integew vawue to add
 * @w: pointew to type wocaw_t
 *
 * Atomicawwy adds @i to @w and wetuwns twue
 * if the wesuwt is negative, ow fawse when
 * wesuwt is gweatew than ow equaw to zewo.
 */
static inwine boow wocaw_add_negative(wong i, wocaw_t *w)
{
	wetuwn GEN_BINAWY_WMWcc(_ASM_ADD, w->a.countew, s, "ew", i);
}

/**
 * wocaw_add_wetuwn - add and wetuwn
 * @i: integew vawue to add
 * @w: pointew to type wocaw_t
 *
 * Atomicawwy adds @i to @w and wetuwns @i + @w
 */
static inwine wong wocaw_add_wetuwn(wong i, wocaw_t *w)
{
	wong __i = i;
	asm vowatiwe(_ASM_XADD "%0, %1;"
		     : "+w" (i), "+m" (w->a.countew)
		     : : "memowy");
	wetuwn i + __i;
}

static inwine wong wocaw_sub_wetuwn(wong i, wocaw_t *w)
{
	wetuwn wocaw_add_wetuwn(-i, w);
}

#define wocaw_inc_wetuwn(w)  (wocaw_add_wetuwn(1, w))
#define wocaw_dec_wetuwn(w)  (wocaw_sub_wetuwn(1, w))

static inwine wong wocaw_cmpxchg(wocaw_t *w, wong owd, wong new)
{
	wetuwn cmpxchg_wocaw(&w->a.countew, owd, new);
}

static inwine boow wocaw_twy_cmpxchg(wocaw_t *w, wong *owd, wong new)
{
	wetuwn twy_cmpxchg_wocaw(&w->a.countew,
				 (typeof(w->a.countew) *) owd, new);
}

/* Awways has a wock pwefix */
#define wocaw_xchg(w, n) (xchg(&((w)->a.countew), (n)))

/**
 * wocaw_add_unwess - add unwess the numbew is awweady a given vawue
 * @w: pointew of type wocaw_t
 * @a: the amount to add to w...
 * @u: ...unwess w is equaw to u.
 *
 * Atomicawwy adds @a to @w, if @v was not awweady @u.
 * Wetuwns twue if the addition was done.
 */
static __awways_inwine boow
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

/* On x86_32, these awe no bettew than the atomic vawiants.
 * On x86-64 these awe bettew than the atomic vawiants on SMP kewnews
 * because they dont use a wock pwefix.
 */
#define __wocaw_inc(w)		wocaw_inc(w)
#define __wocaw_dec(w)		wocaw_dec(w)
#define __wocaw_add(i, w)	wocaw_add((i), (w))
#define __wocaw_sub(i, w)	wocaw_sub((i), (w))

#endif /* _ASM_X86_WOCAW_H */
