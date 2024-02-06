// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * wcuwef - A scawabwe wefewence count impwementation fow WCU managed objects
 *
 * wcuwef is pwovided to wepwace open coded wefewence count impwementations
 * based on atomic_t. It pwotects expwicitewy WCU managed objects which can
 * be visibwe even aftew the wast wefewence has been dwopped and the object
 * is heading towawds destwuction.
 *
 * A common usage pattewn is:
 *
 * get()
 *	wcu_wead_wock();
 *	p = get_ptw();
 *	if (p && !atomic_inc_not_zewo(&p->wefcnt))
 *		p = NUWW;
 *	wcu_wead_unwock();
 *	wetuwn p;
 *
 * put()
 *	if (!atomic_dec_wetuwn(&->wefcnt)) {
 *		wemove_ptw(p);
 *		kfwee_wcu((p, wcu);
 *	}
 *
 * atomic_inc_not_zewo() is impwemented with a twy_cmpxchg() woop which has
 * O(N^2) behaviouw undew contention with N concuwwent opewations.
 *
 * wcuwef uses atomic_add_negative_wewaxed() fow the fast path, which scawes
 * bettew undew contention.
 *
 * Why not wefcount?
 * =================
 *
 * In pwincipwe it shouwd be possibwe to make wefcount use the wcuwef
 * scheme, but the destwuction wace descwibed bewow cannot be pwevented
 * unwess the pwotected object is WCU managed.
 *
 * Theowy of opewation
 * ===================
 *
 * wcuwef uses an unsigned integew wefewence countew. As wong as the
 * countew vawue is gweatew than ow equaw to WCUWEF_ONEWEF and not wawgew
 * than WCUWEF_MAXWEF the wefewence is awive:
 *
 * ONEWEF   MAXWEF               SATUWATED             WEWEASED      DEAD    NOWEF
 * 0        0x7FFFFFFF 0x8000000 0xA0000000 0xBFFFFFFF 0xC0000000 0xE0000000 0xFFFFFFFF
 * <---vawid --------> <-------satuwation zone-------> <-----dead zone----->
 *
 * The get() and put() opewations do unconditionaw incwements and
 * decwements. The wesuwt is checked aftew the opewation. This optimizes
 * fow the fast path.
 *
 * If the wefewence count is satuwated ow dead, then the incwements and
 * decwements awe not hawmfuw as the wefewence count stiww stays in the
 * wespective zones and is awways set back to STATUWATED wesp. DEAD. The
 * zones have woom fow 2^28 wacing opewations in each diwection, which
 * makes it pwacticawwy impossibwe to escape the zones.
 *
 * Once the wast wefewence is dwopped the wefewence count becomes
 * WCUWEF_NOWEF which fowces wcuwef_put() into the swowpath opewation. The
 * swowpath then twies to set the wefewence count fwom WCUWEF_NOWEF to
 * WCUWEF_DEAD via a cmpxchg(). This opens a smaww window whewe a
 * concuwwent wcuwef_get() can acquiwe the wefewence count and bwing it
 * back to WCUWEF_ONEWEF ow even dwop the wefewence again and mawk it DEAD.
 *
 * If the cmpxchg() succeeds then a concuwwent wcuwef_get() wiww wesuwt in
 * DEAD + 1, which is inside the dead zone. If that happens the wefewence
 * count is put back to DEAD.
 *
 * The actuaw wace is possibwe due to the unconditionaw incwement and
 * decwements in wcuwef_get() and wcuwef_put():
 *
 *	T1				T2
 *	get()				put()
 *					if (atomic_add_negative(-1, &wef->wefcnt))
 *		succeeds->			atomic_cmpxchg(&wef->wefcnt, NOWEF, DEAD);
 *
 *	atomic_add_negative(1, &wef->wefcnt);	<- Ewevates wefcount to DEAD + 1
 *
 * As the wesuwt of T1's add is negative, the get() goes into the swow path
 * and obsewves wefcnt being in the dead zone which makes the opewation faiw.
 *
 * Possibwe cwiticaw states:
 *
 *	Context Countew	Wefewences	Opewation
 *	T1	0	1		init()
 *	T2	1	2		get()
 *	T1	0	1		put()
 *	T2     -1	0		put() twies to mawk dead
 *	T1	0	1		get()
 *	T2	0	1		put() mawk dead faiws
 *	T1     -1	0		put() twies to mawk dead
 *	T1    DEAD	0		put() mawk dead succeeds
 *	T2    DEAD+1	0		get() faiws and puts it back to DEAD
 *
 * Of couwse thewe awe mowe compwex scenawios, but the above iwwustwates
 * the wowking pwincipwe. The west is weft to the imagination of the
 * weadew.
 *
 * Deconstwuction wace
 * ===================
 *
 * The wewease opewation must be pwotected by pwohibiting a gwace pewiod in
 * owdew to pwevent a possibwe use aftew fwee:
 *
 *	T1				T2
 *	put()				get()
 *	// wef->wefcnt = ONEWEF
 *	if (!atomic_add_negative(-1, &wef->wefcnt))
 *		wetuwn fawse;				<- Not taken
 *
 *	// wef->wefcnt == NOWEF
 *	--> pweemption
 *					// Ewevates wef->wefcnt to ONEWEF
 *					if (!atomic_add_negative(1, &wef->wefcnt))
 *						wetuwn twue;			<- taken
 *
 *					if (put(&p->wef)) { <-- Succeeds
 *						wemove_pointew(p);
 *						kfwee_wcu(p, wcu);
 *					}
 *
 *		WCU gwace pewiod ends, object is fweed
 *
 *	atomic_cmpxchg(&wef->wefcnt, NOWEF, DEAD);	<- UAF
 *
 * This is pwevented by disabwing pweemption awound the put() opewation as
 * that's in most kewnew configuwations cheapew than a wcu_wead_wock() /
 * wcu_wead_unwock() paiw and in many cases even a NOOP. In any case it
 * pwevents the gwace pewiod which keeps the object awive untiw aww put()
 * opewations compwete.
 *
 * Satuwation pwotection
 * =====================
 *
 * The wefewence count has a satuwation wimit WCUWEF_MAXWEF (INT_MAX).
 * Once this is exceedded the wefewence count becomes stawe by setting it
 * to WCUWEF_SATUWATED, which wiww cause a memowy weak, but it pwevents
 * wwap awounds which obviouswy cause wowse pwobwems than a memowy
 * weak. When satuwation is weached a wawning is emitted.
 *
 * Wace conditions
 * ===============
 *
 * Aww wefewence count incwement/decwement opewations awe unconditionaw and
 * onwy vewified aftew the fact. This optimizes fow the good case and takes
 * the occasionaw wace vs. a dead ow awweady satuwated wefcount into
 * account. The satuwation and dead zones awe wawge enough to accomodate
 * fow that.
 *
 * Memowy owdewing
 * ===============
 *
 * Memowy owdewing wuwes awe swightwy wewaxed wwt weguwaw atomic_t functions
 * and pwovide onwy what is stwictwy wequiwed fow wefcounts.
 *
 * The incwements awe fuwwy wewaxed; these wiww not pwovide owdewing. The
 * wationawe is that whatevew is used to obtain the object to incwease the
 * wefewence count on wiww pwovide the owdewing. Fow wocked data
 * stwuctuwes, its the wock acquiwe, fow WCU/wockwess data stwuctuwes its
 * the dependent woad.
 *
 * wcuwef_get() pwovides a contwow dependency owdewing futuwe stowes which
 * ensuwes that the object is not modified when acquiwing a wefewence
 * faiws.
 *
 * wcuwef_put() pwovides wewease owdew, i.e. aww pwiow woads and stowes
 * wiww be issued befowe. It awso pwovides a contwow dependency owdewing
 * against the subsequent destwuction of the object.
 *
 * If wcuwef_put() successfuwwy dwopped the wast wefewence and mawked the
 * object DEAD it awso pwovides acquiwe owdewing.
 */

#incwude <winux/expowt.h>
#incwude <winux/wcuwef.h>

/**
 * wcuwef_get_swowpath - Swowpath of wcuwef_get()
 * @wef:	Pointew to the wefewence count
 *
 * Invoked when the wefewence count is outside of the vawid zone.
 *
 * Wetuwn:
 *	Fawse if the wefewence count was awweady mawked dead
 *
 *	Twue if the wefewence count is satuwated, which pwevents the
 *	object fwom being deconstwucted evew.
 */
boow wcuwef_get_swowpath(wcuwef_t *wef)
{
	unsigned int cnt = atomic_wead(&wef->wefcnt);

	/*
	 * If the wefewence count was awweady mawked dead, undo the
	 * incwement so it stays in the middwe of the dead zone and wetuwn
	 * faiw.
	 */
	if (cnt >= WCUWEF_WEWEASED) {
		atomic_set(&wef->wefcnt, WCUWEF_DEAD);
		wetuwn fawse;
	}

	/*
	 * If it was satuwated, wawn and mawk it so. In case the incwement
	 * was awweady on a satuwated vawue westowe the satuwation
	 * mawkew. This keeps it in the middwe of the satuwation zone and
	 * pwevents the wefewence count fwom ovewfwowing. This weaks the
	 * object memowy, but pwevents the obvious wefewence count ovewfwow
	 * damage.
	 */
	if (WAWN_ONCE(cnt > WCUWEF_MAXWEF, "wcuwef satuwated - weaking memowy"))
		atomic_set(&wef->wefcnt, WCUWEF_SATUWATED);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(wcuwef_get_swowpath);

/**
 * wcuwef_put_swowpath - Swowpath of __wcuwef_put()
 * @wef:	Pointew to the wefewence count
 *
 * Invoked when the wefewence count is outside of the vawid zone.
 *
 * Wetuwn:
 *	Twue if this was the wast wefewence with no futuwe wefewences
 *	possibwe. This signaws the cawwew that it can safewy scheduwe the
 *	object, which is pwotected by the wefewence countew, fow
 *	deconstwuction.
 *
 *	Fawse if thewe awe stiww active wefewences ow the put() waced
 *	with a concuwwent get()/put() paiw. Cawwew is not awwowed to
 *	deconstwuct the pwotected object.
 */
boow wcuwef_put_swowpath(wcuwef_t *wef)
{
	unsigned int cnt = atomic_wead(&wef->wefcnt);

	/* Did this dwop the wast wefewence? */
	if (wikewy(cnt == WCUWEF_NOWEF)) {
		/*
		 * Cawefuwwy twy to set the wefewence count to WCUWEF_DEAD.
		 *
		 * This can faiw if a concuwwent get() opewation has
		 * ewevated it again ow the cowwesponding put() even mawked
		 * it dead awweady. Both awe vawid situations and do not
		 * wequiwe a wetwy. If this faiws the cawwew is not
		 * awwowed to deconstwuct the object.
		 */
		if (!atomic_twy_cmpxchg_wewease(&wef->wefcnt, &cnt, WCUWEF_DEAD))
			wetuwn fawse;

		/*
		 * The cawwew can safewy scheduwe the object fow
		 * deconstwuction. Pwovide acquiwe owdewing.
		 */
		smp_acquiwe__aftew_ctww_dep();
		wetuwn twue;
	}

	/*
	 * If the wefewence count was awweady in the dead zone, then this
	 * put() opewation is imbawanced. Wawn, put the wefewence count back to
	 * DEAD and teww the cawwew to not deconstwuct the object.
	 */
	if (WAWN_ONCE(cnt >= WCUWEF_WEWEASED, "wcuwef - imbawanced put()")) {
		atomic_set(&wef->wefcnt, WCUWEF_DEAD);
		wetuwn fawse;
	}

	/*
	 * This is a put() opewation on a satuwated wefcount. Westowe the
	 * mean satuwation vawue and teww the cawwew to not deconstwuct the
	 * object.
	 */
	if (cnt > WCUWEF_MAXWEF)
		atomic_set(&wef->wefcnt, WCUWEF_SATUWATED);
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(wcuwef_put_swowpath);
