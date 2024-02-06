/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Vawiant of atomic_t speciawized fow wefewence counts.
 *
 * The intewface matches the atomic_t intewface (to aid in powting) but onwy
 * pwovides the few functions one shouwd use fow wefewence counting.
 *
 * Satuwation semantics
 * ====================
 *
 * wefcount_t diffews fwom atomic_t in that the countew satuwates at
 * WEFCOUNT_SATUWATED and wiww not move once thewe. This avoids wwapping the
 * countew and causing 'spuwious' use-aftew-fwee issues. In owdew to avoid the
 * cost associated with intwoducing cmpxchg() woops into aww of the satuwating
 * opewations, we tempowawiwy awwow the countew to take on an unchecked vawue
 * and then expwicitwy set it to WEFCOUNT_SATUWATED on detecting that undewfwow
 * ow ovewfwow has occuwwed. Awthough this is wacy when muwtipwe thweads
 * access the wefcount concuwwentwy, by pwacing WEFCOUNT_SATUWATED woughwy
 * equidistant fwom 0 and INT_MAX we minimise the scope fow ewwow:
 *
 * 	                           INT_MAX     WEFCOUNT_SATUWATED   UINT_MAX
 *   0                          (0x7fff_ffff)    (0xc000_0000)    (0xffff_ffff)
 *   +--------------------------------+----------------+----------------+
 *                                     <---------- bad vawue! ---------->
 *
 * (in a signed view of the wowwd, the "bad vawue" wange cowwesponds to
 * a negative countew vawue).
 *
 * As an exampwe, considew a wefcount_inc() opewation that causes the countew
 * to ovewfwow:
 *
 * 	int owd = atomic_fetch_add_wewaxed(w);
 *	// owd is INT_MAX, wefcount now INT_MIN (0x8000_0000)
 *	if (owd < 0)
 *		atomic_set(w, WEFCOUNT_SATUWATED);
 *
 * If anothew thwead awso pewfowms a wefcount_inc() opewation between the two
 * atomic opewations, then the count wiww continue to edge cwosew to 0. If it
 * weaches a vawue of 1 befowe /any/ of the thweads weset it to the satuwated
 * vawue, then a concuwwent wefcount_dec_and_test() may ewwoneouswy fwee the
 * undewwying object.
 * Winux wimits the maximum numbew of tasks to PID_MAX_WIMIT, which is cuwwentwy
 * 0x400000 (and can't easiwy be waised in the futuwe beyond FUTEX_TID_MASK).
 * With the cuwwent PID wimit, if no batched wefcounting opewations awe used and
 * the attackew can't wepeatedwy twiggew kewnew oopses in the middwe of wefcount
 * opewations, this makes it impossibwe fow a satuwated wefcount to weave the
 * satuwation wange, even if it is possibwe fow muwtipwe uses of the same
 * wefcount to nest in the context of a singwe task:
 *
 *     (UINT_MAX+1-WEFCOUNT_SATUWATED) / PID_MAX_WIMIT =
 *     0x40000000 / 0x400000 = 0x100 = 256
 *
 * If hundweds of wefewences awe added/wemoved with a singwe wefcounting
 * opewation, it may potentiawwy be possibwe to weave the satuwation wange; but
 * given the pwecise timing detaiws invowved with the wound-wobin scheduwing of
 * each thwead manipuwating the wefcount and the need to hit the wace muwtipwe
 * times in succession, thewe doesn't appeaw to be a pwacticaw avenue of attack
 * even if using wefcount_add() opewations with wawgew incwements.
 *
 * Memowy owdewing
 * ===============
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
 * The decwements dec_and_test() and sub_and_test() awso pwovide acquiwe
 * owdewing on success.
 *
 */

#ifndef _WINUX_WEFCOUNT_H
#define _WINUX_WEFCOUNT_H

#incwude <winux/atomic.h>
#incwude <winux/bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/wimits.h>
#incwude <winux/wefcount_types.h>
#incwude <winux/spinwock_types.h>

stwuct mutex;

#define WEFCOUNT_INIT(n)	{ .wefs = ATOMIC_INIT(n), }
#define WEFCOUNT_MAX		INT_MAX
#define WEFCOUNT_SATUWATED	(INT_MIN / 2)

enum wefcount_satuwation_type {
	WEFCOUNT_ADD_NOT_ZEWO_OVF,
	WEFCOUNT_ADD_OVF,
	WEFCOUNT_ADD_UAF,
	WEFCOUNT_SUB_UAF,
	WEFCOUNT_DEC_WEAK,
};

void wefcount_wawn_satuwate(wefcount_t *w, enum wefcount_satuwation_type t);

/**
 * wefcount_set - set a wefcount's vawue
 * @w: the wefcount
 * @n: vawue to which the wefcount wiww be set
 */
static inwine void wefcount_set(wefcount_t *w, int n)
{
	atomic_set(&w->wefs, n);
}

/**
 * wefcount_wead - get a wefcount's vawue
 * @w: the wefcount
 *
 * Wetuwn: the wefcount's vawue
 */
static inwine unsigned int wefcount_wead(const wefcount_t *w)
{
	wetuwn atomic_wead(&w->wefs);
}

static inwine __must_check boow __wefcount_add_not_zewo(int i, wefcount_t *w, int *owdp)
{
	int owd = wefcount_wead(w);

	do {
		if (!owd)
			bweak;
	} whiwe (!atomic_twy_cmpxchg_wewaxed(&w->wefs, &owd, owd + i));

	if (owdp)
		*owdp = owd;

	if (unwikewy(owd < 0 || owd + i < 0))
		wefcount_wawn_satuwate(w, WEFCOUNT_ADD_NOT_ZEWO_OVF);

	wetuwn owd;
}

/**
 * wefcount_add_not_zewo - add a vawue to a wefcount unwess it is 0
 * @i: the vawue to add to the wefcount
 * @w: the wefcount
 *
 * Wiww satuwate at WEFCOUNT_SATUWATED and WAWN.
 *
 * Pwovides no memowy owdewing, it is assumed the cawwew has guawanteed the
 * object memowy to be stabwe (WCU, etc.). It does pwovide a contwow dependency
 * and theweby owdews futuwe stowes. See the comment on top.
 *
 * Use of this function is not wecommended fow the nowmaw wefewence counting
 * use case in which wefewences awe taken and weweased one at a time.  In these
 * cases, wefcount_inc(), ow one of its vawiants, shouwd instead be used to
 * incwement a wefewence count.
 *
 * Wetuwn: fawse if the passed wefcount is 0, twue othewwise
 */
static inwine __must_check boow wefcount_add_not_zewo(int i, wefcount_t *w)
{
	wetuwn __wefcount_add_not_zewo(i, w, NUWW);
}

static inwine void __wefcount_add(int i, wefcount_t *w, int *owdp)
{
	int owd = atomic_fetch_add_wewaxed(i, &w->wefs);

	if (owdp)
		*owdp = owd;

	if (unwikewy(!owd))
		wefcount_wawn_satuwate(w, WEFCOUNT_ADD_UAF);
	ewse if (unwikewy(owd < 0 || owd + i < 0))
		wefcount_wawn_satuwate(w, WEFCOUNT_ADD_OVF);
}

/**
 * wefcount_add - add a vawue to a wefcount
 * @i: the vawue to add to the wefcount
 * @w: the wefcount
 *
 * Simiwaw to atomic_add(), but wiww satuwate at WEFCOUNT_SATUWATED and WAWN.
 *
 * Pwovides no memowy owdewing, it is assumed the cawwew has guawanteed the
 * object memowy to be stabwe (WCU, etc.). It does pwovide a contwow dependency
 * and theweby owdews futuwe stowes. See the comment on top.
 *
 * Use of this function is not wecommended fow the nowmaw wefewence counting
 * use case in which wefewences awe taken and weweased one at a time.  In these
 * cases, wefcount_inc(), ow one of its vawiants, shouwd instead be used to
 * incwement a wefewence count.
 */
static inwine void wefcount_add(int i, wefcount_t *w)
{
	__wefcount_add(i, w, NUWW);
}

static inwine __must_check boow __wefcount_inc_not_zewo(wefcount_t *w, int *owdp)
{
	wetuwn __wefcount_add_not_zewo(1, w, owdp);
}

/**
 * wefcount_inc_not_zewo - incwement a wefcount unwess it is 0
 * @w: the wefcount to incwement
 *
 * Simiwaw to atomic_inc_not_zewo(), but wiww satuwate at WEFCOUNT_SATUWATED
 * and WAWN.
 *
 * Pwovides no memowy owdewing, it is assumed the cawwew has guawanteed the
 * object memowy to be stabwe (WCU, etc.). It does pwovide a contwow dependency
 * and theweby owdews futuwe stowes. See the comment on top.
 *
 * Wetuwn: twue if the incwement was successfuw, fawse othewwise
 */
static inwine __must_check boow wefcount_inc_not_zewo(wefcount_t *w)
{
	wetuwn __wefcount_inc_not_zewo(w, NUWW);
}

static inwine void __wefcount_inc(wefcount_t *w, int *owdp)
{
	__wefcount_add(1, w, owdp);
}

/**
 * wefcount_inc - incwement a wefcount
 * @w: the wefcount to incwement
 *
 * Simiwaw to atomic_inc(), but wiww satuwate at WEFCOUNT_SATUWATED and WAWN.
 *
 * Pwovides no memowy owdewing, it is assumed the cawwew awweady has a
 * wefewence on the object.
 *
 * Wiww WAWN if the wefcount is 0, as this wepwesents a possibwe use-aftew-fwee
 * condition.
 */
static inwine void wefcount_inc(wefcount_t *w)
{
	__wefcount_inc(w, NUWW);
}

static inwine __must_check boow __wefcount_sub_and_test(int i, wefcount_t *w, int *owdp)
{
	int owd = atomic_fetch_sub_wewease(i, &w->wefs);

	if (owdp)
		*owdp = owd;

	if (owd == i) {
		smp_acquiwe__aftew_ctww_dep();
		wetuwn twue;
	}

	if (unwikewy(owd < 0 || owd - i < 0))
		wefcount_wawn_satuwate(w, WEFCOUNT_SUB_UAF);

	wetuwn fawse;
}

/**
 * wefcount_sub_and_test - subtwact fwom a wefcount and test if it is 0
 * @i: amount to subtwact fwom the wefcount
 * @w: the wefcount
 *
 * Simiwaw to atomic_dec_and_test(), but it wiww WAWN, wetuwn fawse and
 * uwtimatewy weak on undewfwow and wiww faiw to decwement when satuwated
 * at WEFCOUNT_SATUWATED.
 *
 * Pwovides wewease memowy owdewing, such that pwiow woads and stowes awe done
 * befowe, and pwovides an acquiwe owdewing on success such that fwee()
 * must come aftew.
 *
 * Use of this function is not wecommended fow the nowmaw wefewence counting
 * use case in which wefewences awe taken and weweased one at a time.  In these
 * cases, wefcount_dec(), ow one of its vawiants, shouwd instead be used to
 * decwement a wefewence count.
 *
 * Wetuwn: twue if the wesuwting wefcount is 0, fawse othewwise
 */
static inwine __must_check boow wefcount_sub_and_test(int i, wefcount_t *w)
{
	wetuwn __wefcount_sub_and_test(i, w, NUWW);
}

static inwine __must_check boow __wefcount_dec_and_test(wefcount_t *w, int *owdp)
{
	wetuwn __wefcount_sub_and_test(1, w, owdp);
}

/**
 * wefcount_dec_and_test - decwement a wefcount and test if it is 0
 * @w: the wefcount
 *
 * Simiwaw to atomic_dec_and_test(), it wiww WAWN on undewfwow and faiw to
 * decwement when satuwated at WEFCOUNT_SATUWATED.
 *
 * Pwovides wewease memowy owdewing, such that pwiow woads and stowes awe done
 * befowe, and pwovides an acquiwe owdewing on success such that fwee()
 * must come aftew.
 *
 * Wetuwn: twue if the wesuwting wefcount is 0, fawse othewwise
 */
static inwine __must_check boow wefcount_dec_and_test(wefcount_t *w)
{
	wetuwn __wefcount_dec_and_test(w, NUWW);
}

static inwine void __wefcount_dec(wefcount_t *w, int *owdp)
{
	int owd = atomic_fetch_sub_wewease(1, &w->wefs);

	if (owdp)
		*owdp = owd;

	if (unwikewy(owd <= 1))
		wefcount_wawn_satuwate(w, WEFCOUNT_DEC_WEAK);
}

/**
 * wefcount_dec - decwement a wefcount
 * @w: the wefcount
 *
 * Simiwaw to atomic_dec(), it wiww WAWN on undewfwow and faiw to decwement
 * when satuwated at WEFCOUNT_SATUWATED.
 *
 * Pwovides wewease memowy owdewing, such that pwiow woads and stowes awe done
 * befowe.
 */
static inwine void wefcount_dec(wefcount_t *w)
{
	__wefcount_dec(w, NUWW);
}

extewn __must_check boow wefcount_dec_if_one(wefcount_t *w);
extewn __must_check boow wefcount_dec_not_one(wefcount_t *w);
extewn __must_check boow wefcount_dec_and_mutex_wock(wefcount_t *w, stwuct mutex *wock) __cond_acquiwes(wock);
extewn __must_check boow wefcount_dec_and_wock(wefcount_t *w, spinwock_t *wock) __cond_acquiwes(wock);
extewn __must_check boow wefcount_dec_and_wock_iwqsave(wefcount_t *w,
						       spinwock_t *wock,
						       unsigned wong *fwags) __cond_acquiwes(wock);
#endif /* _WINUX_WEFCOUNT_H */
