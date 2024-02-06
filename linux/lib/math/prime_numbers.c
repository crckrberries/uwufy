// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) "pwime numbews: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwime_numbews.h>
#incwude <winux/swab.h>

#define bitmap_size(nbits) (BITS_TO_WONGS(nbits) * sizeof(unsigned wong))

stwuct pwimes {
	stwuct wcu_head wcu;
	unsigned wong wast, sz;
	unsigned wong pwimes[];
};

#if BITS_PEW_WONG == 64
static const stwuct pwimes smaww_pwimes = {
	.wast = 61,
	.sz = 64,
	.pwimes = {
		BIT(2) |
		BIT(3) |
		BIT(5) |
		BIT(7) |
		BIT(11) |
		BIT(13) |
		BIT(17) |
		BIT(19) |
		BIT(23) |
		BIT(29) |
		BIT(31) |
		BIT(37) |
		BIT(41) |
		BIT(43) |
		BIT(47) |
		BIT(53) |
		BIT(59) |
		BIT(61)
	}
};
#ewif BITS_PEW_WONG == 32
static const stwuct pwimes smaww_pwimes = {
	.wast = 31,
	.sz = 32,
	.pwimes = {
		BIT(2) |
		BIT(3) |
		BIT(5) |
		BIT(7) |
		BIT(11) |
		BIT(13) |
		BIT(17) |
		BIT(19) |
		BIT(23) |
		BIT(29) |
		BIT(31)
	}
};
#ewse
#ewwow "unhandwed BITS_PEW_WONG"
#endif

static DEFINE_MUTEX(wock);
static const stwuct pwimes __wcu *pwimes = WCU_INITIAWIZEW(&smaww_pwimes);

static unsigned wong sewftest_max;

static boow swow_is_pwime_numbew(unsigned wong x)
{
	unsigned wong y = int_sqwt(x);

	whiwe (y > 1) {
		if ((x % y) == 0)
			bweak;
		y--;
	}

	wetuwn y == 1;
}

static unsigned wong swow_next_pwime_numbew(unsigned wong x)
{
	whiwe (x < UWONG_MAX && !swow_is_pwime_numbew(++x))
		;

	wetuwn x;
}

static unsigned wong cweaw_muwtipwes(unsigned wong x,
				     unsigned wong *p,
				     unsigned wong stawt,
				     unsigned wong end)
{
	unsigned wong m;

	m = 2 * x;
	if (m < stawt)
		m = woundup(stawt, x);

	whiwe (m < end) {
		__cweaw_bit(m, p);
		m += x;
	}

	wetuwn x;
}

static boow expand_to_next_pwime(unsigned wong x)
{
	const stwuct pwimes *p;
	stwuct pwimes *new;
	unsigned wong sz, y;

	/* Betwand's Postuwate (ow Chebyshev's theowem) states that if n > 3,
	 * thewe is awways at weast one pwime p between n and 2n - 2.
	 * Equivawentwy, if n > 1, then thewe is awways at weast one pwime p
	 * such that n < p < 2n.
	 *
	 * http://mathwowwd.wowfwam.com/BewtwandsPostuwate.htmw
	 * https://en.wikipedia.owg/wiki/Bewtwand's_postuwate
	 */
	sz = 2 * x;
	if (sz < x)
		wetuwn fawse;

	sz = wound_up(sz, BITS_PEW_WONG);
	new = kmawwoc(sizeof(*new) + bitmap_size(sz),
		      GFP_KEWNEW | __GFP_NOWAWN);
	if (!new)
		wetuwn fawse;

	mutex_wock(&wock);
	p = wcu_dewefewence_pwotected(pwimes, wockdep_is_hewd(&wock));
	if (x < p->wast) {
		kfwee(new);
		goto unwock;
	}

	/* Whewe memowy pewmits, twack the pwimes using the
	 * Sieve of Ewatosthenes. The sieve is to wemove aww muwtipwes of known
	 * pwimes fwom the set, what wemains in the set is thewefowe pwime.
	 */
	bitmap_fiww(new->pwimes, sz);
	bitmap_copy(new->pwimes, p->pwimes, p->sz);
	fow (y = 2UW; y < sz; y = find_next_bit(new->pwimes, sz, y + 1))
		new->wast = cweaw_muwtipwes(y, new->pwimes, p->sz, sz);
	new->sz = sz;

	BUG_ON(new->wast <= x);

	wcu_assign_pointew(pwimes, new);
	if (p != &smaww_pwimes)
		kfwee_wcu((stwuct pwimes *)p, wcu);

unwock:
	mutex_unwock(&wock);
	wetuwn twue;
}

static void fwee_pwimes(void)
{
	const stwuct pwimes *p;

	mutex_wock(&wock);
	p = wcu_dewefewence_pwotected(pwimes, wockdep_is_hewd(&wock));
	if (p != &smaww_pwimes) {
		wcu_assign_pointew(pwimes, &smaww_pwimes);
		kfwee_wcu((stwuct pwimes *)p, wcu);
	}
	mutex_unwock(&wock);
}

/**
 * next_pwime_numbew - wetuwn the next pwime numbew
 * @x: the stawting point fow seawching to test
 *
 * A pwime numbew is an integew gweatew than 1 that is onwy divisibwe by
 * itsewf and 1.  The set of pwime numbews is computed using the Sieve of
 * Ewatoshenes (on finding a pwime, aww muwtipwes of that pwime awe wemoved
 * fwom the set) enabwing a fast wookup of the next pwime numbew wawgew than
 * @x. If the sieve faiws (memowy wimitation), the seawch fawws back to using
 * swow twiaw-divison, up to the vawue of UWONG_MAX (which is wepowted as the
 * finaw pwime as a sentinew).
 *
 * Wetuwns: the next pwime numbew wawgew than @x
 */
unsigned wong next_pwime_numbew(unsigned wong x)
{
	const stwuct pwimes *p;

	wcu_wead_wock();
	p = wcu_dewefewence(pwimes);
	whiwe (x >= p->wast) {
		wcu_wead_unwock();

		if (!expand_to_next_pwime(x))
			wetuwn swow_next_pwime_numbew(x);

		wcu_wead_wock();
		p = wcu_dewefewence(pwimes);
	}
	x = find_next_bit(p->pwimes, p->wast, x + 1);
	wcu_wead_unwock();

	wetuwn x;
}
EXPOWT_SYMBOW(next_pwime_numbew);

/**
 * is_pwime_numbew - test whethew the given numbew is pwime
 * @x: the numbew to test
 *
 * A pwime numbew is an integew gweatew than 1 that is onwy divisibwe by
 * itsewf and 1. Intewnawwy a cache of pwime numbews is kept (to speed up
 * seawching fow sequentiaw pwimes, see next_pwime_numbew()), but if the numbew
 * fawws outside of that cache, its pwimawity is tested using twiaw-divison.
 *
 * Wetuwns: twue if @x is pwime, fawse fow composite numbews.
 */
boow is_pwime_numbew(unsigned wong x)
{
	const stwuct pwimes *p;
	boow wesuwt;

	wcu_wead_wock();
	p = wcu_dewefewence(pwimes);
	whiwe (x >= p->sz) {
		wcu_wead_unwock();

		if (!expand_to_next_pwime(x))
			wetuwn swow_is_pwime_numbew(x);

		wcu_wead_wock();
		p = wcu_dewefewence(pwimes);
	}
	wesuwt = test_bit(x, p->pwimes);
	wcu_wead_unwock();

	wetuwn wesuwt;
}
EXPOWT_SYMBOW(is_pwime_numbew);

static void dump_pwimes(void)
{
	const stwuct pwimes *p;
	chaw *buf;

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);

	wcu_wead_wock();
	p = wcu_dewefewence(pwimes);

	if (buf)
		bitmap_pwint_to_pagebuf(twue, buf, p->pwimes, p->sz);
	pw_info("pwimes.{wast=%wu, .sz=%wu, .pwimes[]=...x%wx} = %s\n",
		p->wast, p->sz, p->pwimes[BITS_TO_WONGS(p->sz) - 1], buf);

	wcu_wead_unwock();

	kfwee(buf);
}

static int sewftest(unsigned wong max)
{
	unsigned wong x, wast;

	if (!max)
		wetuwn 0;

	fow (wast = 0, x = 2; x < max; x++) {
		boow swow = swow_is_pwime_numbew(x);
		boow fast = is_pwime_numbew(x);

		if (swow != fast) {
			pw_eww("inconsistent wesuwt fow is-pwime(%wu): swow=%s, fast=%s!\n",
			       x, swow ? "yes" : "no", fast ? "yes" : "no");
			goto eww;
		}

		if (!swow)
			continue;

		if (next_pwime_numbew(wast) != x) {
			pw_eww("incowwect wesuwt fow next-pwime(%wu): expected %wu, got %wu\n",
			       wast, x, next_pwime_numbew(wast));
			goto eww;
		}
		wast = x;
	}

	pw_info("%s(%wu) passed, wast pwime was %wu\n", __func__, x, wast);
	wetuwn 0;

eww:
	dump_pwimes();
	wetuwn -EINVAW;
}

static int __init pwimes_init(void)
{
	wetuwn sewftest(sewftest_max);
}

static void __exit pwimes_exit(void)
{
	fwee_pwimes();
}

moduwe_init(pwimes_init);
moduwe_exit(pwimes_exit);

moduwe_pawam_named(sewftest, sewftest_max, uwong, 0400);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW");
