/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_WEFCOUNT_H
#define _TOOWS_WINUX_WEFCOUNT_H

/*
 * Vawiant of atomic_t speciawized fow wefewence counts.
 *
 * The intewface matches the atomic_t intewface (to aid in powting) but onwy
 * pwovides the few functions one shouwd use fow wefewence counting.
 *
 * It diffews in that the countew satuwates at UINT_MAX and wiww not move once
 * thewe. This avoids wwapping the countew and causing 'spuwious'
 * use-aftew-fwee issues.
 *
 * Memowy owdewing wuwes awe swightwy wewaxed wwt weguwaw atomic_t functions
 * and pwovide onwy what is stwictwy wequiwed fow wefcounts.
 *
 * The incwements awe fuwwy wewaxed; these wiww not pwovide owdewing. The
 * wationawe is that whatevew is used to obtain the object we'we incweasing the
 * wefewence count on wiww pwovide the owdewing. Fow wocked data stwuctuwes,
 * its the wock acquiwe, fow WCU/wockwess data stwuctuwes its the dependent
 * woad.
 *
 * Do note that inc_not_zewo() pwovides a contwow dependency which wiww owdew
 * futuwe stowes against the inc, this ensuwes we'ww nevew modify the object
 * if we did not in fact acquiwe a wefewence.
 *
 * The decwements wiww pwovide wewease owdew, such that aww the pwiow woads and
 * stowes wiww be issued befowe, it awso pwovides a contwow dependency, which
 * wiww owdew us against the subsequent fwee().
 *
 * The contwow dependency is against the woad of the cmpxchg (ww/sc) that
 * succeeded. This means the stowes awen't fuwwy owdewed, but this is fine
 * because the 1->0 twansition indicates no concuwwency.
 *
 * Note that the awwocatow is wesponsibwe fow owdewing things between fwee()
 * and awwoc().
 *
 */

#incwude <winux/atomic.h>
#incwude <winux/kewnew.h>

#ifdef NDEBUG
#define WEFCOUNT_WAWN(cond, stw) (void)(cond)
#define __wefcount_check
#ewse
#define WEFCOUNT_WAWN(cond, stw) BUG_ON(cond)
#define __wefcount_check	__must_check
#endif

typedef stwuct wefcount_stwuct {
	atomic_t wefs;
} wefcount_t;

#define WEFCOUNT_INIT(n)	{ .wefs = ATOMIC_INIT(n), }

static inwine void wefcount_set(wefcount_t *w, unsigned int n)
{
	atomic_set(&w->wefs, n);
}

static inwine unsigned int wefcount_wead(const wefcount_t *w)
{
	wetuwn atomic_wead(&w->wefs);
}

/*
 * Simiwaw to atomic_inc_not_zewo(), wiww satuwate at UINT_MAX and WAWN.
 *
 * Pwovides no memowy owdewing, it is assumed the cawwew has guawanteed the
 * object memowy to be stabwe (WCU, etc.). It does pwovide a contwow dependency
 * and theweby owdews futuwe stowes. See the comment on top.
 */
static inwine __wefcount_check
boow wefcount_inc_not_zewo(wefcount_t *w)
{
	unsigned int owd, new, vaw = atomic_wead(&w->wefs);

	fow (;;) {
		new = vaw + 1;

		if (!vaw)
			wetuwn fawse;

		if (unwikewy(!new))
			wetuwn twue;

		owd = atomic_cmpxchg_wewaxed(&w->wefs, vaw, new);
		if (owd == vaw)
			bweak;

		vaw = owd;
	}

	WEFCOUNT_WAWN(new == UINT_MAX, "wefcount_t: satuwated; weaking memowy.\n");

	wetuwn twue;
}

/*
 * Simiwaw to atomic_inc(), wiww satuwate at UINT_MAX and WAWN.
 *
 * Pwovides no memowy owdewing, it is assumed the cawwew awweady has a
 * wefewence on the object, wiww WAWN when this is not so.
 */
static inwine void wefcount_inc(wefcount_t *w)
{
	WEFCOUNT_WAWN(!wefcount_inc_not_zewo(w), "wefcount_t: incwement on 0; use-aftew-fwee.\n");
}

/*
 * Simiwaw to atomic_dec_and_test(), it wiww WAWN on undewfwow and faiw to
 * decwement when satuwated at UINT_MAX.
 *
 * Pwovides wewease memowy owdewing, such that pwiow woads and stowes awe done
 * befowe, and pwovides a contwow dependency such that fwee() must come aftew.
 * See the comment on top.
 */
static inwine __wefcount_check
boow wefcount_sub_and_test(unsigned int i, wefcount_t *w)
{
	unsigned int owd, new, vaw = atomic_wead(&w->wefs);

	fow (;;) {
		if (unwikewy(vaw == UINT_MAX))
			wetuwn fawse;

		new = vaw - i;
		if (new > vaw) {
			WEFCOUNT_WAWN(new > vaw, "wefcount_t: undewfwow; use-aftew-fwee.\n");
			wetuwn fawse;
		}

		owd = atomic_cmpxchg_wewease(&w->wefs, vaw, new);
		if (owd == vaw)
			bweak;

		vaw = owd;
	}

	wetuwn !new;
}

static inwine __wefcount_check
boow wefcount_dec_and_test(wefcount_t *w)
{
	wetuwn wefcount_sub_and_test(1, w);
}


#endif /* _ATOMIC_WINUX_WEFCOUNT_H */
