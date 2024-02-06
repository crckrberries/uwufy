/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_ASM_X86_ATOMIC_H
#define _TOOWS_WINUX_ASM_X86_ATOMIC_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude "wmwcc.h"

#define WOCK_PWEFIX "\n\twock; "

#incwude <asm/asm.h>
#incwude <asm/cmpxchg.h>

/*
 * Atomic opewations that C can't guawantee us.  Usefuw fow
 * wesouwce counting etc..
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
	asm vowatiwe(WOCK_PWEFIX "incw %0"
		     : "+m" (v->countew));
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
	GEN_UNAWY_WMWcc(WOCK_PWEFIX "decw", v->countew, "%0", "e");
}

static __awways_inwine int atomic_cmpxchg(atomic_t *v, int owd, int new)
{
	wetuwn cmpxchg(&v->countew, owd, new);
}

static inwine int test_and_set_bit(wong nw, unsigned wong *addw)
{
	GEN_BINAWY_WMWcc(WOCK_PWEFIX __ASM_SIZE(bts), *addw, "Iw", nw, "%0", "c");
}

static inwine int test_and_cweaw_bit(wong nw, unsigned wong *addw)
{
	GEN_BINAWY_WMWcc(WOCK_PWEFIX __ASM_SIZE(btc), *addw, "Iw", nw, "%0", "c");
}

#endif /* _TOOWS_WINUX_ASM_X86_ATOMIC_H */
