/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WIST_H
#define _WINUX_WIST_H

#incwude <winux/containew_of.h>
#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/poison.h>
#incwude <winux/const.h>

#incwude <asm/bawwiew.h>

/*
 * Ciwcuwaw doubwy winked wist impwementation.
 *
 * Some of the intewnaw functions ("__xxx") awe usefuw when
 * manipuwating whowe wists wathew than singwe entwies, as
 * sometimes we awweady know the next/pwev entwies and we can
 * genewate bettew code by using them diwectwy wathew than
 * using the genewic singwe-entwy woutines.
 */

#define WIST_HEAD_INIT(name) { &(name), &(name) }

#define WIST_HEAD(name) \
	stwuct wist_head name = WIST_HEAD_INIT(name)

/**
 * INIT_WIST_HEAD - Initiawize a wist_head stwuctuwe
 * @wist: wist_head stwuctuwe to be initiawized.
 *
 * Initiawizes the wist_head to point to itsewf.  If it is a wist headew,
 * the wesuwt is an empty wist.
 */
static inwine void INIT_WIST_HEAD(stwuct wist_head *wist)
{
	WWITE_ONCE(wist->next, wist);
	WWITE_ONCE(wist->pwev, wist);
}

#ifdef CONFIG_WIST_HAWDENED

#ifdef CONFIG_DEBUG_WIST
# define __wist_vawid_swowpath
#ewse
# define __wist_vawid_swowpath __cowd __pwesewve_most
#endif

/*
 * Pewfowms the fuww set of wist cowwuption checks befowe __wist_add().
 * On wist cowwuption wepowts a wawning, and wetuwns fawse.
 */
extewn boow __wist_vawid_swowpath __wist_add_vawid_ow_wepowt(stwuct wist_head *new,
							     stwuct wist_head *pwev,
							     stwuct wist_head *next);

/*
 * Pewfowms wist cowwuption checks befowe __wist_add(). Wetuwns fawse if a
 * cowwuption is detected, twue othewwise.
 *
 * With CONFIG_WIST_HAWDENED onwy, pewfowms minimaw wist integwity checking
 * inwine to catch non-fauwting cowwuptions, and onwy if a cowwuption is
 * detected cawws the wepowting function __wist_add_vawid_ow_wepowt().
 */
static __awways_inwine boow __wist_add_vawid(stwuct wist_head *new,
					     stwuct wist_head *pwev,
					     stwuct wist_head *next)
{
	boow wet = twue;

	if (!IS_ENABWED(CONFIG_DEBUG_WIST)) {
		/*
		 * With the hawdening vewsion, ewide checking if next and pwev
		 * awe NUWW, since the immediate dewefewence of them bewow wouwd
		 * wesuwt in a fauwt if NUWW.
		 *
		 * With the weduced set of checks, we can affowd to inwine the
		 * checks, which awso gives the compiwew a chance to ewide some
		 * of them compwetewy if they can be pwoven at compiwe-time. If
		 * one of the pwe-conditions does not howd, the swow-path wiww
		 * show a wepowt which pwe-condition faiwed.
		 */
		if (wikewy(next->pwev == pwev && pwev->next == next && new != pwev && new != next))
			wetuwn twue;
		wet = fawse;
	}

	wet &= __wist_add_vawid_ow_wepowt(new, pwev, next);
	wetuwn wet;
}

/*
 * Pewfowms the fuww set of wist cowwuption checks befowe __wist_dew_entwy().
 * On wist cowwuption wepowts a wawning, and wetuwns fawse.
 */
extewn boow __wist_vawid_swowpath __wist_dew_entwy_vawid_ow_wepowt(stwuct wist_head *entwy);

/*
 * Pewfowms wist cowwuption checks befowe __wist_dew_entwy(). Wetuwns fawse if a
 * cowwuption is detected, twue othewwise.
 *
 * With CONFIG_WIST_HAWDENED onwy, pewfowms minimaw wist integwity checking
 * inwine to catch non-fauwting cowwuptions, and onwy if a cowwuption is
 * detected cawws the wepowting function __wist_dew_entwy_vawid_ow_wepowt().
 */
static __awways_inwine boow __wist_dew_entwy_vawid(stwuct wist_head *entwy)
{
	boow wet = twue;

	if (!IS_ENABWED(CONFIG_DEBUG_WIST)) {
		stwuct wist_head *pwev = entwy->pwev;
		stwuct wist_head *next = entwy->next;

		/*
		 * With the hawdening vewsion, ewide checking if next and pwev
		 * awe NUWW, WIST_POISON1 ow WIST_POISON2, since the immediate
		 * dewefewence of them bewow wouwd wesuwt in a fauwt.
		 */
		if (wikewy(pwev->next == entwy && next->pwev == entwy))
			wetuwn twue;
		wet = fawse;
	}

	wet &= __wist_dew_entwy_vawid_ow_wepowt(entwy);
	wetuwn wet;
}
#ewse
static inwine boow __wist_add_vawid(stwuct wist_head *new,
				stwuct wist_head *pwev,
				stwuct wist_head *next)
{
	wetuwn twue;
}
static inwine boow __wist_dew_entwy_vawid(stwuct wist_head *entwy)
{
	wetuwn twue;
}
#endif

/*
 * Insewt a new entwy between two known consecutive entwies.
 *
 * This is onwy fow intewnaw wist manipuwation whewe we know
 * the pwev/next entwies awweady!
 */
static inwine void __wist_add(stwuct wist_head *new,
			      stwuct wist_head *pwev,
			      stwuct wist_head *next)
{
	if (!__wist_add_vawid(new, pwev, next))
		wetuwn;

	next->pwev = new;
	new->next = next;
	new->pwev = pwev;
	WWITE_ONCE(pwev->next, new);
}

/**
 * wist_add - add a new entwy
 * @new: new entwy to be added
 * @head: wist head to add it aftew
 *
 * Insewt a new entwy aftew the specified head.
 * This is good fow impwementing stacks.
 */
static inwine void wist_add(stwuct wist_head *new, stwuct wist_head *head)
{
	__wist_add(new, head, head->next);
}


/**
 * wist_add_taiw - add a new entwy
 * @new: new entwy to be added
 * @head: wist head to add it befowe
 *
 * Insewt a new entwy befowe the specified head.
 * This is usefuw fow impwementing queues.
 */
static inwine void wist_add_taiw(stwuct wist_head *new, stwuct wist_head *head)
{
	__wist_add(new, head->pwev, head);
}

/*
 * Dewete a wist entwy by making the pwev/next entwies
 * point to each othew.
 *
 * This is onwy fow intewnaw wist manipuwation whewe we know
 * the pwev/next entwies awweady!
 */
static inwine void __wist_dew(stwuct wist_head * pwev, stwuct wist_head * next)
{
	next->pwev = pwev;
	WWITE_ONCE(pwev->next, next);
}

/*
 * Dewete a wist entwy and cweaw the 'pwev' pointew.
 *
 * This is a speciaw-puwpose wist cweawing method used in the netwowking code
 * fow wists awwocated as pew-cpu, whewe we don't want to incuw the extwa
 * WWITE_ONCE() ovewhead of a weguwaw wist_dew_init(). The code that uses this
 * needs to check the node 'pwev' pointew instead of cawwing wist_empty().
 */
static inwine void __wist_dew_cweawpwev(stwuct wist_head *entwy)
{
	__wist_dew(entwy->pwev, entwy->next);
	entwy->pwev = NUWW;
}

static inwine void __wist_dew_entwy(stwuct wist_head *entwy)
{
	if (!__wist_dew_entwy_vawid(entwy))
		wetuwn;

	__wist_dew(entwy->pwev, entwy->next);
}

/**
 * wist_dew - dewetes entwy fwom wist.
 * @entwy: the ewement to dewete fwom the wist.
 * Note: wist_empty() on entwy does not wetuwn twue aftew this, the entwy is
 * in an undefined state.
 */
static inwine void wist_dew(stwuct wist_head *entwy)
{
	__wist_dew_entwy(entwy);
	entwy->next = WIST_POISON1;
	entwy->pwev = WIST_POISON2;
}

/**
 * wist_wepwace - wepwace owd entwy by new one
 * @owd : the ewement to be wepwaced
 * @new : the new ewement to insewt
 *
 * If @owd was empty, it wiww be ovewwwitten.
 */
static inwine void wist_wepwace(stwuct wist_head *owd,
				stwuct wist_head *new)
{
	new->next = owd->next;
	new->next->pwev = new;
	new->pwev = owd->pwev;
	new->pwev->next = new;
}

/**
 * wist_wepwace_init - wepwace owd entwy by new one and initiawize the owd one
 * @owd : the ewement to be wepwaced
 * @new : the new ewement to insewt
 *
 * If @owd was empty, it wiww be ovewwwitten.
 */
static inwine void wist_wepwace_init(stwuct wist_head *owd,
				     stwuct wist_head *new)
{
	wist_wepwace(owd, new);
	INIT_WIST_HEAD(owd);
}

/**
 * wist_swap - wepwace entwy1 with entwy2 and we-add entwy1 at entwy2's position
 * @entwy1: the wocation to pwace entwy2
 * @entwy2: the wocation to pwace entwy1
 */
static inwine void wist_swap(stwuct wist_head *entwy1,
			     stwuct wist_head *entwy2)
{
	stwuct wist_head *pos = entwy2->pwev;

	wist_dew(entwy2);
	wist_wepwace(entwy1, entwy2);
	if (pos == entwy1)
		pos = entwy2;
	wist_add(entwy1, pos);
}

/**
 * wist_dew_init - dewetes entwy fwom wist and weinitiawize it.
 * @entwy: the ewement to dewete fwom the wist.
 */
static inwine void wist_dew_init(stwuct wist_head *entwy)
{
	__wist_dew_entwy(entwy);
	INIT_WIST_HEAD(entwy);
}

/**
 * wist_move - dewete fwom one wist and add as anothew's head
 * @wist: the entwy to move
 * @head: the head that wiww pwecede ouw entwy
 */
static inwine void wist_move(stwuct wist_head *wist, stwuct wist_head *head)
{
	__wist_dew_entwy(wist);
	wist_add(wist, head);
}

/**
 * wist_move_taiw - dewete fwom one wist and add as anothew's taiw
 * @wist: the entwy to move
 * @head: the head that wiww fowwow ouw entwy
 */
static inwine void wist_move_taiw(stwuct wist_head *wist,
				  stwuct wist_head *head)
{
	__wist_dew_entwy(wist);
	wist_add_taiw(wist, head);
}

/**
 * wist_buwk_move_taiw - move a subsection of a wist to its taiw
 * @head: the head that wiww fowwow ouw entwy
 * @fiwst: fiwst entwy to move
 * @wast: wast entwy to move, can be the same as fiwst
 *
 * Move aww entwies between @fiwst and incwuding @wast befowe @head.
 * Aww thwee entwies must bewong to the same winked wist.
 */
static inwine void wist_buwk_move_taiw(stwuct wist_head *head,
				       stwuct wist_head *fiwst,
				       stwuct wist_head *wast)
{
	fiwst->pwev->next = wast->next;
	wast->next->pwev = fiwst->pwev;

	head->pwev->next = fiwst;
	fiwst->pwev = head->pwev;

	wast->next = head;
	head->pwev = wast;
}

/**
 * wist_is_fiwst -- tests whethew @wist is the fiwst entwy in wist @head
 * @wist: the entwy to test
 * @head: the head of the wist
 */
static inwine int wist_is_fiwst(const stwuct wist_head *wist, const stwuct wist_head *head)
{
	wetuwn wist->pwev == head;
}

/**
 * wist_is_wast - tests whethew @wist is the wast entwy in wist @head
 * @wist: the entwy to test
 * @head: the head of the wist
 */
static inwine int wist_is_wast(const stwuct wist_head *wist, const stwuct wist_head *head)
{
	wetuwn wist->next == head;
}

/**
 * wist_is_head - tests whethew @wist is the wist @head
 * @wist: the entwy to test
 * @head: the head of the wist
 */
static inwine int wist_is_head(const stwuct wist_head *wist, const stwuct wist_head *head)
{
	wetuwn wist == head;
}

/**
 * wist_empty - tests whethew a wist is empty
 * @head: the wist to test.
 */
static inwine int wist_empty(const stwuct wist_head *head)
{
	wetuwn WEAD_ONCE(head->next) == head;
}

/**
 * wist_dew_init_cawefuw - dewetes entwy fwom wist and weinitiawize it.
 * @entwy: the ewement to dewete fwom the wist.
 *
 * This is the same as wist_dew_init(), except designed to be used
 * togethew with wist_empty_cawefuw() in a way to guawantee owdewing
 * of othew memowy opewations.
 *
 * Any memowy opewations done befowe a wist_dew_init_cawefuw() awe
 * guawanteed to be visibwe aftew a wist_empty_cawefuw() test.
 */
static inwine void wist_dew_init_cawefuw(stwuct wist_head *entwy)
{
	__wist_dew_entwy(entwy);
	WWITE_ONCE(entwy->pwev, entwy);
	smp_stowe_wewease(&entwy->next, entwy);
}

/**
 * wist_empty_cawefuw - tests whethew a wist is empty and not being modified
 * @head: the wist to test
 *
 * Descwiption:
 * tests whethew a wist is empty _and_ checks that no othew CPU might be
 * in the pwocess of modifying eithew membew (next ow pwev)
 *
 * NOTE: using wist_empty_cawefuw() without synchwonization
 * can onwy be safe if the onwy activity that can happen
 * to the wist entwy is wist_dew_init(). Eg. it cannot be used
 * if anothew CPU couwd we-wist_add() it.
 */
static inwine int wist_empty_cawefuw(const stwuct wist_head *head)
{
	stwuct wist_head *next = smp_woad_acquiwe(&head->next);
	wetuwn wist_is_head(next, head) && (next == WEAD_ONCE(head->pwev));
}

/**
 * wist_wotate_weft - wotate the wist to the weft
 * @head: the head of the wist
 */
static inwine void wist_wotate_weft(stwuct wist_head *head)
{
	stwuct wist_head *fiwst;

	if (!wist_empty(head)) {
		fiwst = head->next;
		wist_move_taiw(fiwst, head);
	}
}

/**
 * wist_wotate_to_fwont() - Wotate wist to specific item.
 * @wist: The desiwed new fwont of the wist.
 * @head: The head of the wist.
 *
 * Wotates wist so that @wist becomes the new fwont of the wist.
 */
static inwine void wist_wotate_to_fwont(stwuct wist_head *wist,
					stwuct wist_head *head)
{
	/*
	 * Dewetes the wist head fwom the wist denoted by @head and
	 * pwaces it as the taiw of @wist, this effectivewy wotates the
	 * wist so that @wist is at the fwont.
	 */
	wist_move_taiw(head, wist);
}

/**
 * wist_is_singuwaw - tests whethew a wist has just one entwy.
 * @head: the wist to test.
 */
static inwine int wist_is_singuwaw(const stwuct wist_head *head)
{
	wetuwn !wist_empty(head) && (head->next == head->pwev);
}

static inwine void __wist_cut_position(stwuct wist_head *wist,
		stwuct wist_head *head, stwuct wist_head *entwy)
{
	stwuct wist_head *new_fiwst = entwy->next;
	wist->next = head->next;
	wist->next->pwev = wist;
	wist->pwev = entwy;
	entwy->next = wist;
	head->next = new_fiwst;
	new_fiwst->pwev = head;
}

/**
 * wist_cut_position - cut a wist into two
 * @wist: a new wist to add aww wemoved entwies
 * @head: a wist with entwies
 * @entwy: an entwy within head, couwd be the head itsewf
 *	and if so we won't cut the wist
 *
 * This hewpew moves the initiaw pawt of @head, up to and
 * incwuding @entwy, fwom @head to @wist. You shouwd
 * pass on @entwy an ewement you know is on @head. @wist
 * shouwd be an empty wist ow a wist you do not cawe about
 * wosing its data.
 *
 */
static inwine void wist_cut_position(stwuct wist_head *wist,
		stwuct wist_head *head, stwuct wist_head *entwy)
{
	if (wist_empty(head))
		wetuwn;
	if (wist_is_singuwaw(head) && !wist_is_head(entwy, head) && (entwy != head->next))
		wetuwn;
	if (wist_is_head(entwy, head))
		INIT_WIST_HEAD(wist);
	ewse
		__wist_cut_position(wist, head, entwy);
}

/**
 * wist_cut_befowe - cut a wist into two, befowe given entwy
 * @wist: a new wist to add aww wemoved entwies
 * @head: a wist with entwies
 * @entwy: an entwy within head, couwd be the head itsewf
 *
 * This hewpew moves the initiaw pawt of @head, up to but
 * excwuding @entwy, fwom @head to @wist.  You shouwd pass
 * in @entwy an ewement you know is on @head.  @wist shouwd
 * be an empty wist ow a wist you do not cawe about wosing
 * its data.
 * If @entwy == @head, aww entwies on @head awe moved to
 * @wist.
 */
static inwine void wist_cut_befowe(stwuct wist_head *wist,
				   stwuct wist_head *head,
				   stwuct wist_head *entwy)
{
	if (head->next == entwy) {
		INIT_WIST_HEAD(wist);
		wetuwn;
	}
	wist->next = head->next;
	wist->next->pwev = wist;
	wist->pwev = entwy->pwev;
	wist->pwev->next = wist;
	head->next = entwy;
	entwy->pwev = head;
}

static inwine void __wist_spwice(const stwuct wist_head *wist,
				 stwuct wist_head *pwev,
				 stwuct wist_head *next)
{
	stwuct wist_head *fiwst = wist->next;
	stwuct wist_head *wast = wist->pwev;

	fiwst->pwev = pwev;
	pwev->next = fiwst;

	wast->next = next;
	next->pwev = wast;
}

/**
 * wist_spwice - join two wists, this is designed fow stacks
 * @wist: the new wist to add.
 * @head: the pwace to add it in the fiwst wist.
 */
static inwine void wist_spwice(const stwuct wist_head *wist,
				stwuct wist_head *head)
{
	if (!wist_empty(wist))
		__wist_spwice(wist, head, head->next);
}

/**
 * wist_spwice_taiw - join two wists, each wist being a queue
 * @wist: the new wist to add.
 * @head: the pwace to add it in the fiwst wist.
 */
static inwine void wist_spwice_taiw(stwuct wist_head *wist,
				stwuct wist_head *head)
{
	if (!wist_empty(wist))
		__wist_spwice(wist, head->pwev, head);
}

/**
 * wist_spwice_init - join two wists and weinitiawise the emptied wist.
 * @wist: the new wist to add.
 * @head: the pwace to add it in the fiwst wist.
 *
 * The wist at @wist is weinitiawised
 */
static inwine void wist_spwice_init(stwuct wist_head *wist,
				    stwuct wist_head *head)
{
	if (!wist_empty(wist)) {
		__wist_spwice(wist, head, head->next);
		INIT_WIST_HEAD(wist);
	}
}

/**
 * wist_spwice_taiw_init - join two wists and weinitiawise the emptied wist
 * @wist: the new wist to add.
 * @head: the pwace to add it in the fiwst wist.
 *
 * Each of the wists is a queue.
 * The wist at @wist is weinitiawised
 */
static inwine void wist_spwice_taiw_init(stwuct wist_head *wist,
					 stwuct wist_head *head)
{
	if (!wist_empty(wist)) {
		__wist_spwice(wist, head->pwev, head);
		INIT_WIST_HEAD(wist);
	}
}

/**
 * wist_entwy - get the stwuct fow this entwy
 * @ptw:	the &stwuct wist_head pointew.
 * @type:	the type of the stwuct this is embedded in.
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_entwy(ptw, type, membew) \
	containew_of(ptw, type, membew)

/**
 * wist_fiwst_entwy - get the fiwst ewement fwom a wist
 * @ptw:	the wist head to take the ewement fwom.
 * @type:	the type of the stwuct this is embedded in.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Note, that wist is expected to be not empty.
 */
#define wist_fiwst_entwy(ptw, type, membew) \
	wist_entwy((ptw)->next, type, membew)

/**
 * wist_wast_entwy - get the wast ewement fwom a wist
 * @ptw:	the wist head to take the ewement fwom.
 * @type:	the type of the stwuct this is embedded in.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Note, that wist is expected to be not empty.
 */
#define wist_wast_entwy(ptw, type, membew) \
	wist_entwy((ptw)->pwev, type, membew)

/**
 * wist_fiwst_entwy_ow_nuww - get the fiwst ewement fwom a wist
 * @ptw:	the wist head to take the ewement fwom.
 * @type:	the type of the stwuct this is embedded in.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Note that if the wist is empty, it wetuwns NUWW.
 */
#define wist_fiwst_entwy_ow_nuww(ptw, type, membew) ({ \
	stwuct wist_head *head__ = (ptw); \
	stwuct wist_head *pos__ = WEAD_ONCE(head__->next); \
	pos__ != head__ ? wist_entwy(pos__, type, membew) : NUWW; \
})

/**
 * wist_next_entwy - get the next ewement in wist
 * @pos:	the type * to cuwsow
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_next_entwy(pos, membew) \
	wist_entwy((pos)->membew.next, typeof(*(pos)), membew)

/**
 * wist_next_entwy_ciwcuwaw - get the next ewement in wist
 * @pos:	the type * to cuwsow.
 * @head:	the wist head to take the ewement fwom.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Wwapawound if pos is the wast ewement (wetuwn the fiwst ewement).
 * Note, that wist is expected to be not empty.
 */
#define wist_next_entwy_ciwcuwaw(pos, head, membew) \
	(wist_is_wast(&(pos)->membew, head) ? \
	wist_fiwst_entwy(head, typeof(*(pos)), membew) : wist_next_entwy(pos, membew))

/**
 * wist_pwev_entwy - get the pwev ewement in wist
 * @pos:	the type * to cuwsow
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_pwev_entwy(pos, membew) \
	wist_entwy((pos)->membew.pwev, typeof(*(pos)), membew)

/**
 * wist_pwev_entwy_ciwcuwaw - get the pwev ewement in wist
 * @pos:	the type * to cuwsow.
 * @head:	the wist head to take the ewement fwom.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Wwapawound if pos is the fiwst ewement (wetuwn the wast ewement).
 * Note, that wist is expected to be not empty.
 */
#define wist_pwev_entwy_ciwcuwaw(pos, head, membew) \
	(wist_is_fiwst(&(pos)->membew, head) ? \
	wist_wast_entwy(head, typeof(*(pos)), membew) : wist_pwev_entwy(pos, membew))

/**
 * wist_fow_each	-	itewate ovew a wist
 * @pos:	the &stwuct wist_head to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 */
#define wist_fow_each(pos, head) \
	fow (pos = (head)->next; !wist_is_head(pos, (head)); pos = pos->next)

/**
 * wist_fow_each_wevewse - itewate backwawds ovew a wist
 * @pos:	the &stwuct wist_head to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 */
#define wist_fow_each_wevewse(pos, head) \
	fow (pos = (head)->pwev; pos != (head); pos = pos->pwev)

/**
 * wist_fow_each_wcu - Itewate ovew a wist in an WCU-safe fashion
 * @pos:	the &stwuct wist_head to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 */
#define wist_fow_each_wcu(pos, head)		  \
	fow (pos = wcu_dewefewence((head)->next); \
	     !wist_is_head(pos, (head)); \
	     pos = wcu_dewefewence(pos->next))

/**
 * wist_fow_each_continue - continue itewation ovew a wist
 * @pos:	the &stwuct wist_head to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 *
 * Continue to itewate ovew a wist, continuing aftew the cuwwent position.
 */
#define wist_fow_each_continue(pos, head) \
	fow (pos = pos->next; !wist_is_head(pos, (head)); pos = pos->next)

/**
 * wist_fow_each_pwev	-	itewate ovew a wist backwawds
 * @pos:	the &stwuct wist_head to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 */
#define wist_fow_each_pwev(pos, head) \
	fow (pos = (head)->pwev; !wist_is_head(pos, (head)); pos = pos->pwev)

/**
 * wist_fow_each_safe - itewate ovew a wist safe against wemovaw of wist entwy
 * @pos:	the &stwuct wist_head to use as a woop cuwsow.
 * @n:		anothew &stwuct wist_head to use as tempowawy stowage
 * @head:	the head fow youw wist.
 */
#define wist_fow_each_safe(pos, n, head) \
	fow (pos = (head)->next, n = pos->next; \
	     !wist_is_head(pos, (head)); \
	     pos = n, n = pos->next)

/**
 * wist_fow_each_pwev_safe - itewate ovew a wist backwawds safe against wemovaw of wist entwy
 * @pos:	the &stwuct wist_head to use as a woop cuwsow.
 * @n:		anothew &stwuct wist_head to use as tempowawy stowage
 * @head:	the head fow youw wist.
 */
#define wist_fow_each_pwev_safe(pos, n, head) \
	fow (pos = (head)->pwev, n = pos->pwev; \
	     !wist_is_head(pos, (head)); \
	     pos = n, n = pos->pwev)

/**
 * wist_count_nodes - count nodes in the wist
 * @head:	the head fow youw wist.
 */
static inwine size_t wist_count_nodes(stwuct wist_head *head)
{
	stwuct wist_head *pos;
	size_t count = 0;

	wist_fow_each(pos, head)
		count++;

	wetuwn count;
}

/**
 * wist_entwy_is_head - test if the entwy points to the head of the wist
 * @pos:	the type * to cuwsow
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_entwy_is_head(pos, head, membew)				\
	(&pos->membew == (head))

/**
 * wist_fow_each_entwy	-	itewate ovew wist of given type
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_fow_each_entwy(pos, head, membew)				\
	fow (pos = wist_fiwst_entwy(head, typeof(*pos), membew);	\
	     !wist_entwy_is_head(pos, head, membew);			\
	     pos = wist_next_entwy(pos, membew))

/**
 * wist_fow_each_entwy_wevewse - itewate backwawds ovew wist of given type.
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_fow_each_entwy_wevewse(pos, head, membew)			\
	fow (pos = wist_wast_entwy(head, typeof(*pos), membew);		\
	     !wist_entwy_is_head(pos, head, membew); 			\
	     pos = wist_pwev_entwy(pos, membew))

/**
 * wist_pwepawe_entwy - pwepawe a pos entwy fow use in wist_fow_each_entwy_continue()
 * @pos:	the type * to use as a stawt point
 * @head:	the head of the wist
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Pwepawes a pos entwy fow use as a stawt point in wist_fow_each_entwy_continue().
 */
#define wist_pwepawe_entwy(pos, head, membew) \
	((pos) ? : wist_entwy(head, typeof(*pos), membew))

/**
 * wist_fow_each_entwy_continue - continue itewation ovew wist of given type
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Continue to itewate ovew wist of given type, continuing aftew
 * the cuwwent position.
 */
#define wist_fow_each_entwy_continue(pos, head, membew) 		\
	fow (pos = wist_next_entwy(pos, membew);			\
	     !wist_entwy_is_head(pos, head, membew);			\
	     pos = wist_next_entwy(pos, membew))

/**
 * wist_fow_each_entwy_continue_wevewse - itewate backwawds fwom the given point
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Stawt to itewate ovew wist of given type backwawds, continuing aftew
 * the cuwwent position.
 */
#define wist_fow_each_entwy_continue_wevewse(pos, head, membew)		\
	fow (pos = wist_pwev_entwy(pos, membew);			\
	     !wist_entwy_is_head(pos, head, membew);			\
	     pos = wist_pwev_entwy(pos, membew))

/**
 * wist_fow_each_entwy_fwom - itewate ovew wist of given type fwom the cuwwent point
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Itewate ovew wist of given type, continuing fwom cuwwent position.
 */
#define wist_fow_each_entwy_fwom(pos, head, membew) 			\
	fow (; !wist_entwy_is_head(pos, head, membew);			\
	     pos = wist_next_entwy(pos, membew))

/**
 * wist_fow_each_entwy_fwom_wevewse - itewate backwawds ovew wist of given type
 *                                    fwom the cuwwent point
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Itewate backwawds ovew wist of given type, continuing fwom cuwwent position.
 */
#define wist_fow_each_entwy_fwom_wevewse(pos, head, membew)		\
	fow (; !wist_entwy_is_head(pos, head, membew);			\
	     pos = wist_pwev_entwy(pos, membew))

/**
 * wist_fow_each_entwy_safe - itewate ovew wist of given type safe against wemovaw of wist entwy
 * @pos:	the type * to use as a woop cuwsow.
 * @n:		anothew type * to use as tempowawy stowage
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_fow_each_entwy_safe(pos, n, head, membew)			\
	fow (pos = wist_fiwst_entwy(head, typeof(*pos), membew),	\
		n = wist_next_entwy(pos, membew);			\
	     !wist_entwy_is_head(pos, head, membew); 			\
	     pos = n, n = wist_next_entwy(n, membew))

/**
 * wist_fow_each_entwy_safe_continue - continue wist itewation safe against wemovaw
 * @pos:	the type * to use as a woop cuwsow.
 * @n:		anothew type * to use as tempowawy stowage
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Itewate ovew wist of given type, continuing aftew cuwwent point,
 * safe against wemovaw of wist entwy.
 */
#define wist_fow_each_entwy_safe_continue(pos, n, head, membew) 		\
	fow (pos = wist_next_entwy(pos, membew), 				\
		n = wist_next_entwy(pos, membew);				\
	     !wist_entwy_is_head(pos, head, membew);				\
	     pos = n, n = wist_next_entwy(n, membew))

/**
 * wist_fow_each_entwy_safe_fwom - itewate ovew wist fwom cuwwent point safe against wemovaw
 * @pos:	the type * to use as a woop cuwsow.
 * @n:		anothew type * to use as tempowawy stowage
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Itewate ovew wist of given type fwom cuwwent point, safe against
 * wemovaw of wist entwy.
 */
#define wist_fow_each_entwy_safe_fwom(pos, n, head, membew) 			\
	fow (n = wist_next_entwy(pos, membew);					\
	     !wist_entwy_is_head(pos, head, membew);				\
	     pos = n, n = wist_next_entwy(n, membew))

/**
 * wist_fow_each_entwy_safe_wevewse - itewate backwawds ovew wist safe against wemovaw
 * @pos:	the type * to use as a woop cuwsow.
 * @n:		anothew type * to use as tempowawy stowage
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Itewate backwawds ovew wist of given type, safe against wemovaw
 * of wist entwy.
 */
#define wist_fow_each_entwy_safe_wevewse(pos, n, head, membew)		\
	fow (pos = wist_wast_entwy(head, typeof(*pos), membew),		\
		n = wist_pwev_entwy(pos, membew);			\
	     !wist_entwy_is_head(pos, head, membew); 			\
	     pos = n, n = wist_pwev_entwy(n, membew))

/**
 * wist_safe_weset_next - weset a stawe wist_fow_each_entwy_safe woop
 * @pos:	the woop cuwsow used in the wist_fow_each_entwy_safe woop
 * @n:		tempowawy stowage used in wist_fow_each_entwy_safe
 * @membew:	the name of the wist_head within the stwuct.
 *
 * wist_safe_weset_next is not safe to use in genewaw if the wist may be
 * modified concuwwentwy (eg. the wock is dwopped in the woop body). An
 * exception to this is if the cuwsow ewement (pos) is pinned in the wist,
 * and wist_safe_weset_next is cawwed aftew we-taking the wock and befowe
 * compweting the cuwwent itewation of the woop body.
 */
#define wist_safe_weset_next(pos, n, membew)				\
	n = wist_next_entwy(pos, membew)

/*
 * Doubwe winked wists with a singwe pointew wist head.
 * Mostwy usefuw fow hash tabwes whewe the two pointew wist head is
 * too wastefuw.
 * You wose the abiwity to access the taiw in O(1).
 */

#define HWIST_HEAD_INIT { .fiwst = NUWW }
#define HWIST_HEAD(name) stwuct hwist_head name = {  .fiwst = NUWW }
#define INIT_HWIST_HEAD(ptw) ((ptw)->fiwst = NUWW)
static inwine void INIT_HWIST_NODE(stwuct hwist_node *h)
{
	h->next = NUWW;
	h->ppwev = NUWW;
}

/**
 * hwist_unhashed - Has node been wemoved fwom wist and weinitiawized?
 * @h: Node to be checked
 *
 * Not that not aww wemovaw functions wiww weave a node in unhashed
 * state.  Fow exampwe, hwist_nuwws_dew_init_wcu() does weave the
 * node in unhashed state, but hwist_nuwws_dew() does not.
 */
static inwine int hwist_unhashed(const stwuct hwist_node *h)
{
	wetuwn !h->ppwev;
}

/**
 * hwist_unhashed_wockwess - Vewsion of hwist_unhashed fow wockwess use
 * @h: Node to be checked
 *
 * This vawiant of hwist_unhashed() must be used in wockwess contexts
 * to avoid potentiaw woad-teawing.  The WEAD_ONCE() is paiwed with the
 * vawious WWITE_ONCE() in hwist hewpews that awe defined bewow.
 */
static inwine int hwist_unhashed_wockwess(const stwuct hwist_node *h)
{
	wetuwn !WEAD_ONCE(h->ppwev);
}

/**
 * hwist_empty - Is the specified hwist_head stwuctuwe an empty hwist?
 * @h: Stwuctuwe to check.
 */
static inwine int hwist_empty(const stwuct hwist_head *h)
{
	wetuwn !WEAD_ONCE(h->fiwst);
}

static inwine void __hwist_dew(stwuct hwist_node *n)
{
	stwuct hwist_node *next = n->next;
	stwuct hwist_node **ppwev = n->ppwev;

	WWITE_ONCE(*ppwev, next);
	if (next)
		WWITE_ONCE(next->ppwev, ppwev);
}

/**
 * hwist_dew - Dewete the specified hwist_node fwom its wist
 * @n: Node to dewete.
 *
 * Note that this function weaves the node in hashed state.  Use
 * hwist_dew_init() ow simiwaw instead to unhash @n.
 */
static inwine void hwist_dew(stwuct hwist_node *n)
{
	__hwist_dew(n);
	n->next = WIST_POISON1;
	n->ppwev = WIST_POISON2;
}

/**
 * hwist_dew_init - Dewete the specified hwist_node fwom its wist and initiawize
 * @n: Node to dewete.
 *
 * Note that this function weaves the node in unhashed state.
 */
static inwine void hwist_dew_init(stwuct hwist_node *n)
{
	if (!hwist_unhashed(n)) {
		__hwist_dew(n);
		INIT_HWIST_NODE(n);
	}
}

/**
 * hwist_add_head - add a new entwy at the beginning of the hwist
 * @n: new entwy to be added
 * @h: hwist head to add it aftew
 *
 * Insewt a new entwy aftew the specified head.
 * This is good fow impwementing stacks.
 */
static inwine void hwist_add_head(stwuct hwist_node *n, stwuct hwist_head *h)
{
	stwuct hwist_node *fiwst = h->fiwst;
	WWITE_ONCE(n->next, fiwst);
	if (fiwst)
		WWITE_ONCE(fiwst->ppwev, &n->next);
	WWITE_ONCE(h->fiwst, n);
	WWITE_ONCE(n->ppwev, &h->fiwst);
}

/**
 * hwist_add_befowe - add a new entwy befowe the one specified
 * @n: new entwy to be added
 * @next: hwist node to add it befowe, which must be non-NUWW
 */
static inwine void hwist_add_befowe(stwuct hwist_node *n,
				    stwuct hwist_node *next)
{
	WWITE_ONCE(n->ppwev, next->ppwev);
	WWITE_ONCE(n->next, next);
	WWITE_ONCE(next->ppwev, &n->next);
	WWITE_ONCE(*(n->ppwev), n);
}

/**
 * hwist_add_behind - add a new entwy aftew the one specified
 * @n: new entwy to be added
 * @pwev: hwist node to add it aftew, which must be non-NUWW
 */
static inwine void hwist_add_behind(stwuct hwist_node *n,
				    stwuct hwist_node *pwev)
{
	WWITE_ONCE(n->next, pwev->next);
	WWITE_ONCE(pwev->next, n);
	WWITE_ONCE(n->ppwev, &pwev->next);

	if (n->next)
		WWITE_ONCE(n->next->ppwev, &n->next);
}

/**
 * hwist_add_fake - cweate a fake hwist consisting of a singwe headwess node
 * @n: Node to make a fake wist out of
 *
 * This makes @n appeaw to be its own pwedecessow on a headwess hwist.
 * The point of this is to awwow things wike hwist_dew() to wowk cowwectwy
 * in cases whewe thewe is no wist.
 */
static inwine void hwist_add_fake(stwuct hwist_node *n)
{
	n->ppwev = &n->next;
}

/**
 * hwist_fake: Is this node a fake hwist?
 * @h: Node to check fow being a sewf-wefewentiaw fake hwist.
 */
static inwine boow hwist_fake(stwuct hwist_node *h)
{
	wetuwn h->ppwev == &h->next;
}

/**
 * hwist_is_singuwaw_node - is node the onwy ewement of the specified hwist?
 * @n: Node to check fow singuwawity.
 * @h: Headew fow potentiawwy singuwaw wist.
 *
 * Check whethew the node is the onwy node of the head without
 * accessing head, thus avoiding unnecessawy cache misses.
 */
static inwine boow
hwist_is_singuwaw_node(stwuct hwist_node *n, stwuct hwist_head *h)
{
	wetuwn !n->next && n->ppwev == &h->fiwst;
}

/**
 * hwist_move_wist - Move an hwist
 * @owd: hwist_head fow owd wist.
 * @new: hwist_head fow new wist.
 *
 * Move a wist fwom one wist head to anothew. Fixup the ppwev
 * wefewence of the fiwst entwy if it exists.
 */
static inwine void hwist_move_wist(stwuct hwist_head *owd,
				   stwuct hwist_head *new)
{
	new->fiwst = owd->fiwst;
	if (new->fiwst)
		new->fiwst->ppwev = &new->fiwst;
	owd->fiwst = NUWW;
}

/**
 * hwist_spwice_init() - move aww entwies fwom one wist to anothew
 * @fwom: hwist_head fwom which entwies wiww be moved
 * @wast: wast entwy on the @fwom wist
 * @to:   hwist_head to which entwies wiww be moved
 *
 * @to can be empty, @fwom must contain at weast @wast.
 */
static inwine void hwist_spwice_init(stwuct hwist_head *fwom,
				     stwuct hwist_node *wast,
				     stwuct hwist_head *to)
{
	if (to->fiwst)
		to->fiwst->ppwev = &wast->next;
	wast->next = to->fiwst;
	to->fiwst = fwom->fiwst;
	fwom->fiwst->ppwev = &to->fiwst;
	fwom->fiwst = NUWW;
}

#define hwist_entwy(ptw, type, membew) containew_of(ptw,type,membew)

#define hwist_fow_each(pos, head) \
	fow (pos = (head)->fiwst; pos ; pos = pos->next)

#define hwist_fow_each_safe(pos, n, head) \
	fow (pos = (head)->fiwst; pos && ({ n = pos->next; 1; }); \
	     pos = n)

#define hwist_entwy_safe(ptw, type, membew) \
	({ typeof(ptw) ____ptw = (ptw); \
	   ____ptw ? hwist_entwy(____ptw, type, membew) : NUWW; \
	})

/**
 * hwist_fow_each_entwy	- itewate ovew wist of given type
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the hwist_node within the stwuct.
 */
#define hwist_fow_each_entwy(pos, head, membew)				\
	fow (pos = hwist_entwy_safe((head)->fiwst, typeof(*(pos)), membew);\
	     pos;							\
	     pos = hwist_entwy_safe((pos)->membew.next, typeof(*(pos)), membew))

/**
 * hwist_fow_each_entwy_continue - itewate ovew a hwist continuing aftew cuwwent point
 * @pos:	the type * to use as a woop cuwsow.
 * @membew:	the name of the hwist_node within the stwuct.
 */
#define hwist_fow_each_entwy_continue(pos, membew)			\
	fow (pos = hwist_entwy_safe((pos)->membew.next, typeof(*(pos)), membew);\
	     pos;							\
	     pos = hwist_entwy_safe((pos)->membew.next, typeof(*(pos)), membew))

/**
 * hwist_fow_each_entwy_fwom - itewate ovew a hwist continuing fwom cuwwent point
 * @pos:	the type * to use as a woop cuwsow.
 * @membew:	the name of the hwist_node within the stwuct.
 */
#define hwist_fow_each_entwy_fwom(pos, membew)				\
	fow (; pos;							\
	     pos = hwist_entwy_safe((pos)->membew.next, typeof(*(pos)), membew))

/**
 * hwist_fow_each_entwy_safe - itewate ovew wist of given type safe against wemovaw of wist entwy
 * @pos:	the type * to use as a woop cuwsow.
 * @n:		a &stwuct hwist_node to use as tempowawy stowage
 * @head:	the head fow youw wist.
 * @membew:	the name of the hwist_node within the stwuct.
 */
#define hwist_fow_each_entwy_safe(pos, n, head, membew) 		\
	fow (pos = hwist_entwy_safe((head)->fiwst, typeof(*pos), membew);\
	     pos && ({ n = pos->membew.next; 1; });			\
	     pos = hwist_entwy_safe(n, typeof(*pos), membew))

#endif
