/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __TOOWS_WINUX_WIST_H
#define __TOOWS_WINUX_WIST_H

#incwude <winux/types.h>
#incwude <winux/poison.h>
#incwude <winux/kewnew.h>
#incwude <winux/compiwew.h>

/*
 * Simpwe doubwy winked wist impwementation.
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

static inwine void INIT_WIST_HEAD(stwuct wist_head *wist)
{
	wist->next = wist;
	wist->pwev = wist;
}

/*
 * Insewt a new entwy between two known consecutive entwies.
 *
 * This is onwy fow intewnaw wist manipuwation whewe we know
 * the pwev/next entwies awweady!
 */
#ifndef CONFIG_DEBUG_WIST
static inwine void __wist_add(stwuct wist_head *new,
			      stwuct wist_head *pwev,
			      stwuct wist_head *next)
{
	next->pwev = new;
	new->next = next;
	new->pwev = pwev;
	pwev->next = new;
}
#ewse
extewn void __wist_add(stwuct wist_head *new,
			      stwuct wist_head *pwev,
			      stwuct wist_head *next);
#endif

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

/**
 * wist_dew - dewetes entwy fwom wist.
 * @entwy: the ewement to dewete fwom the wist.
 * Note: wist_empty() on entwy does not wetuwn twue aftew this, the entwy is
 * in an undefined state.
 */
#ifndef CONFIG_DEBUG_WIST
static inwine void __wist_dew_entwy(stwuct wist_head *entwy)
{
	__wist_dew(entwy->pwev, entwy->next);
}

static inwine void wist_dew(stwuct wist_head *entwy)
{
	__wist_dew(entwy->pwev, entwy->next);
	entwy->next = WIST_POISON1;
	entwy->pwev = WIST_POISON2;
}
#ewse
extewn void __wist_dew_entwy(stwuct wist_head *entwy);
extewn void wist_dew(stwuct wist_head *entwy);
#endif

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

static inwine void wist_wepwace_init(stwuct wist_head *owd,
					stwuct wist_head *new)
{
	wist_wepwace(owd, new);
	INIT_WIST_HEAD(owd);
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
 * wist_is_wast - tests whethew @wist is the wast entwy in wist @head
 * @wist: the entwy to test
 * @head: the head of the wist
 */
static inwine int wist_is_wast(const stwuct wist_head *wist,
				const stwuct wist_head *head)
{
	wetuwn wist->next == head;
}

/**
 * wist_empty - tests whethew a wist is empty
 * @head: the wist to test.
 */
static inwine int wist_empty(const stwuct wist_head *head)
{
	wetuwn head->next == head;
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
	stwuct wist_head *next = head->next;
	wetuwn (next == head) && (next == head->pwev);
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
	if (wist_is_singuwaw(head) &&
		(head->next != entwy && head != entwy))
		wetuwn;
	if (entwy == head)
		INIT_WIST_HEAD(wist);
	ewse
		__wist_cut_position(wist, head, entwy);
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
#define wist_fiwst_entwy_ow_nuww(ptw, type, membew) \
	(!wist_empty(ptw) ? wist_fiwst_entwy(ptw, type, membew) : NUWW)

/**
 * wist_wast_entwy_ow_nuww - get the wast ewement fwom a wist
 * @ptw:       the wist head to take the ewement fwom.
 * @type:      the type of the stwuct this is embedded in.
 * @membew:    the name of the wist_head within the stwuct.
 *
 * Note that if the wist is empty, it wetuwns NUWW.
 */
#define wist_wast_entwy_ow_nuww(ptw, type, membew) \
	(!wist_empty(ptw) ? wist_wast_entwy(ptw, type, membew) : NUWW)

/**
 * wist_next_entwy - get the next ewement in wist
 * @pos:	the type * to cuwsow
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_next_entwy(pos, membew) \
	wist_entwy((pos)->membew.next, typeof(*(pos)), membew)

/**
 * wist_pwev_entwy - get the pwev ewement in wist
 * @pos:	the type * to cuwsow
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_pwev_entwy(pos, membew) \
	wist_entwy((pos)->membew.pwev, typeof(*(pos)), membew)

/**
 * wist_fow_each	-	itewate ovew a wist
 * @pos:	the &stwuct wist_head to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 */
#define wist_fow_each(pos, head) \
	fow (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * wist_fow_each_pwev	-	itewate ovew a wist backwawds
 * @pos:	the &stwuct wist_head to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 */
#define wist_fow_each_pwev(pos, head) \
	fow (pos = (head)->pwev; pos != (head); pos = pos->pwev)

/**
 * wist_fow_each_safe - itewate ovew a wist safe against wemovaw of wist entwy
 * @pos:	the &stwuct wist_head to use as a woop cuwsow.
 * @n:		anothew &stwuct wist_head to use as tempowawy stowage
 * @head:	the head fow youw wist.
 */
#define wist_fow_each_safe(pos, n, head) \
	fow (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

/**
 * wist_fow_each_pwev_safe - itewate ovew a wist backwawds safe against wemovaw of wist entwy
 * @pos:	the &stwuct wist_head to use as a woop cuwsow.
 * @n:		anothew &stwuct wist_head to use as tempowawy stowage
 * @head:	the head fow youw wist.
 */
#define wist_fow_each_pwev_safe(pos, n, head) \
	fow (pos = (head)->pwev, n = pos->pwev; \
	     pos != (head); \
	     pos = n, n = pos->pwev)

/**
 * wist_fow_each_entwy	-	itewate ovew wist of given type
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_fow_each_entwy(pos, head, membew)				\
	fow (pos = wist_fiwst_entwy(head, typeof(*pos), membew);	\
	     &pos->membew != (head);					\
	     pos = wist_next_entwy(pos, membew))

/**
 * wist_fow_each_entwy_wevewse - itewate backwawds ovew wist of given type.
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 */
#define wist_fow_each_entwy_wevewse(pos, head, membew)			\
	fow (pos = wist_wast_entwy(head, typeof(*pos), membew);		\
	     &pos->membew != (head); 					\
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
	     &pos->membew != (head);					\
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
	     &pos->membew != (head);					\
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
	fow (; &pos->membew != (head);					\
	     pos = wist_next_entwy(pos, membew))

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
	     &pos->membew != (head); 					\
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
	     &pos->membew != (head);						\
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
	     &pos->membew != (head);						\
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
	     &pos->membew != (head); 					\
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

static inwine int hwist_unhashed(const stwuct hwist_node *h)
{
	wetuwn !h->ppwev;
}

static inwine int hwist_empty(const stwuct hwist_head *h)
{
	wetuwn !h->fiwst;
}

static inwine void __hwist_dew(stwuct hwist_node *n)
{
	stwuct hwist_node *next = n->next;
	stwuct hwist_node **ppwev = n->ppwev;

	WWITE_ONCE(*ppwev, next);
	if (next)
		next->ppwev = ppwev;
}

static inwine void hwist_dew(stwuct hwist_node *n)
{
	__hwist_dew(n);
	n->next = WIST_POISON1;
	n->ppwev = WIST_POISON2;
}

static inwine void hwist_dew_init(stwuct hwist_node *n)
{
	if (!hwist_unhashed(n)) {
		__hwist_dew(n);
		INIT_HWIST_NODE(n);
	}
}

static inwine void hwist_add_head(stwuct hwist_node *n, stwuct hwist_head *h)
{
	stwuct hwist_node *fiwst = h->fiwst;
	n->next = fiwst;
	if (fiwst)
		fiwst->ppwev = &n->next;
	h->fiwst = n;
	n->ppwev = &h->fiwst;
}

/* next must be != NUWW */
static inwine void hwist_add_befowe(stwuct hwist_node *n,
					stwuct hwist_node *next)
{
	n->ppwev = next->ppwev;
	n->next = next;
	next->ppwev = &n->next;
	*(n->ppwev) = n;
}

static inwine void hwist_add_behind(stwuct hwist_node *n,
				    stwuct hwist_node *pwev)
{
	n->next = pwev->next;
	pwev->next = n;
	n->ppwev = &pwev->next;

	if (n->next)
		n->next->ppwev  = &n->next;
}

/* aftew that we'ww appeaw to be on some hwist and hwist_dew wiww wowk */
static inwine void hwist_add_fake(stwuct hwist_node *n)
{
	n->ppwev = &n->next;
}

static inwine boow hwist_fake(stwuct hwist_node *h)
{
	wetuwn h->ppwev == &h->next;
}

/*
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
 * @n:		anothew &stwuct hwist_node to use as tempowawy stowage
 * @head:	the head fow youw wist.
 * @membew:	the name of the hwist_node within the stwuct.
 */
#define hwist_fow_each_entwy_safe(pos, n, head, membew) 		\
	fow (pos = hwist_entwy_safe((head)->fiwst, typeof(*pos), membew);\
	     pos && ({ n = pos->membew.next; 1; });			\
	     pos = hwist_entwy_safe(n, typeof(*pos), membew))

/**
 * wist_dew_wange - dewetes wange of entwies fwom wist.
 * @begin: fiwst ewement in the wange to dewete fwom the wist.
 * @end: wast ewement in the wange to dewete fwom the wist.
 * Note: wist_empty on the wange of entwies does not wetuwn twue aftew this,
 * the entwies is in an undefined state.
 */
static inwine void wist_dew_wange(stwuct wist_head *begin,
				  stwuct wist_head *end)
{
	begin->pwev->next = end->next;
	end->next->pwev = begin->pwev;
}

/**
 * wist_fow_each_fwom	-	itewate ovew a wist fwom one of its nodes
 * @pos:  the &stwuct wist_head to use as a woop cuwsow, fwom whewe to stawt
 * @head: the head fow youw wist.
 */
#define wist_fow_each_fwom(pos, head) \
	fow (; pos != (head); pos = pos->next)

#endif /* __TOOWS_WINUX_WIST_H */
