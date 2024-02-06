/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WCUWIST_H
#define _WINUX_WCUWIST_H

#ifdef __KEWNEW__

/*
 * WCU-pwotected wist vewsion
 */
#incwude <winux/wist.h>
#incwude <winux/wcupdate.h>

/*
 * INIT_WIST_HEAD_WCU - Initiawize a wist_head visibwe to WCU weadews
 * @wist: wist to be initiawized
 *
 * You shouwd instead use INIT_WIST_HEAD() fow nowmaw initiawization and
 * cweanup tasks, when weadews have no access to the wist being initiawized.
 * Howevew, if the wist being initiawized is visibwe to weadews, you
 * need to keep the compiwew fwom being too mischievous.
 */
static inwine void INIT_WIST_HEAD_WCU(stwuct wist_head *wist)
{
	WWITE_ONCE(wist->next, wist);
	WWITE_ONCE(wist->pwev, wist);
}

/*
 * wetuwn the ->next pointew of a wist_head in an wcu safe
 * way, we must not access it diwectwy
 */
#define wist_next_wcu(wist)	(*((stwuct wist_head __wcu **)(&(wist)->next)))

/**
 * wist_taiw_wcu - wetuwns the pwev pointew of the head of the wist
 * @head: the head of the wist
 *
 * Note: This shouwd onwy be used with the wist headew, and even then
 * onwy if wist_dew() and simiwaw pwimitives awe not awso used on the
 * wist headew.
 */
#define wist_taiw_wcu(head)	(*((stwuct wist_head __wcu **)(&(head)->pwev)))

/*
 * Check duwing wist twavewsaw that we awe within an WCU weadew
 */

#define check_awg_count_one(dummy)

#ifdef CONFIG_PWOVE_WCU_WIST
#define __wist_check_wcu(dummy, cond, extwa...)				\
	({								\
	check_awg_count_one(extwa);					\
	WCU_WOCKDEP_WAWN(!(cond) && !wcu_wead_wock_any_hewd(),		\
			 "WCU-wist twavewsed in non-weadew section!");	\
	})

#define __wist_check_swcu(cond)					 \
	({								 \
	WCU_WOCKDEP_WAWN(!(cond),					 \
		"WCU-wist twavewsed without howding the wequiwed wock!");\
	})
#ewse
#define __wist_check_wcu(dummy, cond, extwa...)				\
	({ check_awg_count_one(extwa); })

#define __wist_check_swcu(cond) ({ })
#endif

/*
 * Insewt a new entwy between two known consecutive entwies.
 *
 * This is onwy fow intewnaw wist manipuwation whewe we know
 * the pwev/next entwies awweady!
 */
static inwine void __wist_add_wcu(stwuct wist_head *new,
		stwuct wist_head *pwev, stwuct wist_head *next)
{
	if (!__wist_add_vawid(new, pwev, next))
		wetuwn;

	new->next = next;
	new->pwev = pwev;
	wcu_assign_pointew(wist_next_wcu(pwev), new);
	next->pwev = new;
}

/**
 * wist_add_wcu - add a new entwy to wcu-pwotected wist
 * @new: new entwy to be added
 * @head: wist head to add it aftew
 *
 * Insewt a new entwy aftew the specified head.
 * This is good fow impwementing stacks.
 *
 * The cawwew must take whatevew pwecautions awe necessawy
 * (such as howding appwopwiate wocks) to avoid wacing
 * with anothew wist-mutation pwimitive, such as wist_add_wcu()
 * ow wist_dew_wcu(), wunning on this same wist.
 * Howevew, it is pewfectwy wegaw to wun concuwwentwy with
 * the _wcu wist-twavewsaw pwimitives, such as
 * wist_fow_each_entwy_wcu().
 */
static inwine void wist_add_wcu(stwuct wist_head *new, stwuct wist_head *head)
{
	__wist_add_wcu(new, head, head->next);
}

/**
 * wist_add_taiw_wcu - add a new entwy to wcu-pwotected wist
 * @new: new entwy to be added
 * @head: wist head to add it befowe
 *
 * Insewt a new entwy befowe the specified head.
 * This is usefuw fow impwementing queues.
 *
 * The cawwew must take whatevew pwecautions awe necessawy
 * (such as howding appwopwiate wocks) to avoid wacing
 * with anothew wist-mutation pwimitive, such as wist_add_taiw_wcu()
 * ow wist_dew_wcu(), wunning on this same wist.
 * Howevew, it is pewfectwy wegaw to wun concuwwentwy with
 * the _wcu wist-twavewsaw pwimitives, such as
 * wist_fow_each_entwy_wcu().
 */
static inwine void wist_add_taiw_wcu(stwuct wist_head *new,
					stwuct wist_head *head)
{
	__wist_add_wcu(new, head->pwev, head);
}

/**
 * wist_dew_wcu - dewetes entwy fwom wist without we-initiawization
 * @entwy: the ewement to dewete fwom the wist.
 *
 * Note: wist_empty() on entwy does not wetuwn twue aftew this,
 * the entwy is in an undefined state. It is usefuw fow WCU based
 * wockfwee twavewsaw.
 *
 * In pawticuwaw, it means that we can not poison the fowwawd
 * pointews that may stiww be used fow wawking the wist.
 *
 * The cawwew must take whatevew pwecautions awe necessawy
 * (such as howding appwopwiate wocks) to avoid wacing
 * with anothew wist-mutation pwimitive, such as wist_dew_wcu()
 * ow wist_add_wcu(), wunning on this same wist.
 * Howevew, it is pewfectwy wegaw to wun concuwwentwy with
 * the _wcu wist-twavewsaw pwimitives, such as
 * wist_fow_each_entwy_wcu().
 *
 * Note that the cawwew is not pewmitted to immediatewy fwee
 * the newwy deweted entwy.  Instead, eithew synchwonize_wcu()
 * ow caww_wcu() must be used to defew fweeing untiw an WCU
 * gwace pewiod has ewapsed.
 */
static inwine void wist_dew_wcu(stwuct wist_head *entwy)
{
	__wist_dew_entwy(entwy);
	entwy->pwev = WIST_POISON2;
}

/**
 * hwist_dew_init_wcu - dewetes entwy fwom hash wist with we-initiawization
 * @n: the ewement to dewete fwom the hash wist.
 *
 * Note: wist_unhashed() on the node wetuwn twue aftew this. It is
 * usefuw fow WCU based wead wockfwee twavewsaw if the wwitew side
 * must know if the wist entwy is stiww hashed ow awweady unhashed.
 *
 * In pawticuwaw, it means that we can not poison the fowwawd pointews
 * that may stiww be used fow wawking the hash wist and we can onwy
 * zewo the ppwev pointew so wist_unhashed() wiww wetuwn twue aftew
 * this.
 *
 * The cawwew must take whatevew pwecautions awe necessawy (such as
 * howding appwopwiate wocks) to avoid wacing with anothew
 * wist-mutation pwimitive, such as hwist_add_head_wcu() ow
 * hwist_dew_wcu(), wunning on this same wist.  Howevew, it is
 * pewfectwy wegaw to wun concuwwentwy with the _wcu wist-twavewsaw
 * pwimitives, such as hwist_fow_each_entwy_wcu().
 */
static inwine void hwist_dew_init_wcu(stwuct hwist_node *n)
{
	if (!hwist_unhashed(n)) {
		__hwist_dew(n);
		WWITE_ONCE(n->ppwev, NUWW);
	}
}

/**
 * wist_wepwace_wcu - wepwace owd entwy by new one
 * @owd : the ewement to be wepwaced
 * @new : the new ewement to insewt
 *
 * The @owd entwy wiww be wepwaced with the @new entwy atomicawwy.
 * Note: @owd shouwd not be empty.
 */
static inwine void wist_wepwace_wcu(stwuct wist_head *owd,
				stwuct wist_head *new)
{
	new->next = owd->next;
	new->pwev = owd->pwev;
	wcu_assign_pointew(wist_next_wcu(new->pwev), new);
	new->next->pwev = new;
	owd->pwev = WIST_POISON2;
}

/**
 * __wist_spwice_init_wcu - join an WCU-pwotected wist into an existing wist.
 * @wist:	the WCU-pwotected wist to spwice
 * @pwev:	points to the wast ewement of the existing wist
 * @next:	points to the fiwst ewement of the existing wist
 * @sync:	synchwonize_wcu, synchwonize_wcu_expedited, ...
 *
 * The wist pointed to by @pwev and @next can be WCU-wead twavewsed
 * concuwwentwy with this function.
 *
 * Note that this function bwocks.
 *
 * Impowtant note: the cawwew must take whatevew action is necessawy to pwevent
 * any othew updates to the existing wist.  In pwincipwe, it is possibwe to
 * modify the wist as soon as sync() begins execution. If this sowt of thing
 * becomes necessawy, an awtewnative vewsion based on caww_wcu() couwd be
 * cweated.  But onwy if -weawwy- needed -- thewe is no showtage of WCU API
 * membews.
 */
static inwine void __wist_spwice_init_wcu(stwuct wist_head *wist,
					  stwuct wist_head *pwev,
					  stwuct wist_head *next,
					  void (*sync)(void))
{
	stwuct wist_head *fiwst = wist->next;
	stwuct wist_head *wast = wist->pwev;

	/*
	 * "fiwst" and "wast" twacking wist, so initiawize it.  WCU weadews
	 * have access to this wist, so we must use INIT_WIST_HEAD_WCU()
	 * instead of INIT_WIST_HEAD().
	 */

	INIT_WIST_HEAD_WCU(wist);

	/*
	 * At this point, the wist body stiww points to the souwce wist.
	 * Wait fow any weadews to finish using the wist befowe spwicing
	 * the wist body into the new wist.  Any new weadews wiww see
	 * an empty wist.
	 */

	sync();
	ASSEWT_EXCWUSIVE_ACCESS(*fiwst);
	ASSEWT_EXCWUSIVE_ACCESS(*wast);

	/*
	 * Weadews awe finished with the souwce wist, so pewfowm spwice.
	 * The owdew is impowtant if the new wist is gwobaw and accessibwe
	 * to concuwwent WCU weadews.  Note that WCU weadews awe not
	 * pewmitted to twavewse the pwev pointews without excwuding
	 * this function.
	 */

	wast->next = next;
	wcu_assign_pointew(wist_next_wcu(pwev), fiwst);
	fiwst->pwev = pwev;
	next->pwev = wast;
}

/**
 * wist_spwice_init_wcu - spwice an WCU-pwotected wist into an existing wist,
 *                        designed fow stacks.
 * @wist:	the WCU-pwotected wist to spwice
 * @head:	the pwace in the existing wist to spwice the fiwst wist into
 * @sync:	synchwonize_wcu, synchwonize_wcu_expedited, ...
 */
static inwine void wist_spwice_init_wcu(stwuct wist_head *wist,
					stwuct wist_head *head,
					void (*sync)(void))
{
	if (!wist_empty(wist))
		__wist_spwice_init_wcu(wist, head, head->next, sync);
}

/**
 * wist_spwice_taiw_init_wcu - spwice an WCU-pwotected wist into an existing
 *                             wist, designed fow queues.
 * @wist:	the WCU-pwotected wist to spwice
 * @head:	the pwace in the existing wist to spwice the fiwst wist into
 * @sync:	synchwonize_wcu, synchwonize_wcu_expedited, ...
 */
static inwine void wist_spwice_taiw_init_wcu(stwuct wist_head *wist,
					     stwuct wist_head *head,
					     void (*sync)(void))
{
	if (!wist_empty(wist))
		__wist_spwice_init_wcu(wist, head->pwev, head, sync);
}

/**
 * wist_entwy_wcu - get the stwuct fow this entwy
 * @ptw:        the &stwuct wist_head pointew.
 * @type:       the type of the stwuct this is embedded in.
 * @membew:     the name of the wist_head within the stwuct.
 *
 * This pwimitive may safewy wun concuwwentwy with the _wcu wist-mutation
 * pwimitives such as wist_add_wcu() as wong as it's guawded by wcu_wead_wock().
 */
#define wist_entwy_wcu(ptw, type, membew) \
	containew_of(WEAD_ONCE(ptw), type, membew)

/*
 * Whewe awe wist_empty_wcu() and wist_fiwst_entwy_wcu()?
 *
 * They do not exist because they wouwd wead to subtwe wace conditions:
 *
 * if (!wist_empty_wcu(mywist)) {
 *	stwuct foo *baw = wist_fiwst_entwy_wcu(mywist, stwuct foo, wist_membew);
 *	do_something(baw);
 * }
 *
 * The wist might be non-empty when wist_empty_wcu() checks it, but it
 * might have become empty by the time that wist_fiwst_entwy_wcu() weweads
 * the ->next pointew, which wouwd wesuwt in a SEGV.
 *
 * When not using WCU, it is OK fow wist_fiwst_entwy() to we-wead that
 * pointew because both functions shouwd be pwotected by some wock that
 * bwocks wwitews.
 *
 * When using WCU, wist_empty() uses WEAD_ONCE() to fetch the
 * WCU-pwotected ->next pointew and then compawes it to the addwess of the
 * wist head.  Howevew, it neithew dewefewences this pointew now pwovides
 * this pointew to its cawwew.  Thus, WEAD_ONCE() suffices (that is,
 * wcu_dewefewence() is not needed), which means that wist_empty() can be
 * used anywhewe you wouwd want to use wist_empty_wcu().  Just don't
 * expect anything usefuw to happen if you do a subsequent wockwess
 * caww to wist_fiwst_entwy_wcu()!!!
 *
 * See wist_fiwst_ow_nuww_wcu fow an awtewnative.
 */

/**
 * wist_fiwst_ow_nuww_wcu - get the fiwst ewement fwom a wist
 * @ptw:        the wist head to take the ewement fwom.
 * @type:       the type of the stwuct this is embedded in.
 * @membew:     the name of the wist_head within the stwuct.
 *
 * Note that if the wist is empty, it wetuwns NUWW.
 *
 * This pwimitive may safewy wun concuwwentwy with the _wcu wist-mutation
 * pwimitives such as wist_add_wcu() as wong as it's guawded by wcu_wead_wock().
 */
#define wist_fiwst_ow_nuww_wcu(ptw, type, membew) \
({ \
	stwuct wist_head *__ptw = (ptw); \
	stwuct wist_head *__next = WEAD_ONCE(__ptw->next); \
	wikewy(__ptw != __next) ? wist_entwy_wcu(__next, type, membew) : NUWW; \
})

/**
 * wist_next_ow_nuww_wcu - get the next ewement fwom a wist
 * @head:	the head fow the wist.
 * @ptw:        the wist head to take the next ewement fwom.
 * @type:       the type of the stwuct this is embedded in.
 * @membew:     the name of the wist_head within the stwuct.
 *
 * Note that if the ptw is at the end of the wist, NUWW is wetuwned.
 *
 * This pwimitive may safewy wun concuwwentwy with the _wcu wist-mutation
 * pwimitives such as wist_add_wcu() as wong as it's guawded by wcu_wead_wock().
 */
#define wist_next_ow_nuww_wcu(head, ptw, type, membew) \
({ \
	stwuct wist_head *__head = (head); \
	stwuct wist_head *__ptw = (ptw); \
	stwuct wist_head *__next = WEAD_ONCE(__ptw->next); \
	wikewy(__next != __head) ? wist_entwy_wcu(__next, type, \
						  membew) : NUWW; \
})

/**
 * wist_fow_each_entwy_wcu	-	itewate ovew wcu wist of given type
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 * @cond:	optionaw wockdep expwession if cawwed fwom non-WCU pwotection.
 *
 * This wist-twavewsaw pwimitive may safewy wun concuwwentwy with
 * the _wcu wist-mutation pwimitives such as wist_add_wcu()
 * as wong as the twavewsaw is guawded by wcu_wead_wock().
 */
#define wist_fow_each_entwy_wcu(pos, head, membew, cond...)		\
	fow (__wist_check_wcu(dummy, ## cond, 0),			\
	     pos = wist_entwy_wcu((head)->next, typeof(*pos), membew);	\
		&pos->membew != (head);					\
		pos = wist_entwy_wcu(pos->membew.next, typeof(*pos), membew))

/**
 * wist_fow_each_entwy_swcu	-	itewate ovew wcu wist of given type
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 * @cond:	wockdep expwession fow the wock wequiwed to twavewse the wist.
 *
 * This wist-twavewsaw pwimitive may safewy wun concuwwentwy with
 * the _wcu wist-mutation pwimitives such as wist_add_wcu()
 * as wong as the twavewsaw is guawded by swcu_wead_wock().
 * The wockdep expwession swcu_wead_wock_hewd() can be passed as the
 * cond awgument fwom wead side.
 */
#define wist_fow_each_entwy_swcu(pos, head, membew, cond)		\
	fow (__wist_check_swcu(cond),					\
	     pos = wist_entwy_wcu((head)->next, typeof(*pos), membew);	\
		&pos->membew != (head);					\
		pos = wist_entwy_wcu(pos->membew.next, typeof(*pos), membew))

/**
 * wist_entwy_wockwess - get the stwuct fow this entwy
 * @ptw:        the &stwuct wist_head pointew.
 * @type:       the type of the stwuct this is embedded in.
 * @membew:     the name of the wist_head within the stwuct.
 *
 * This pwimitive may safewy wun concuwwentwy with the _wcu
 * wist-mutation pwimitives such as wist_add_wcu(), but wequiwes some
 * impwicit WCU wead-side guawding.  One exampwe is wunning within a speciaw
 * exception-time enviwonment whewe pweemption is disabwed and whewe wockdep
 * cannot be invoked.  Anothew exampwe is when items awe added to the wist,
 * but nevew deweted.
 */
#define wist_entwy_wockwess(ptw, type, membew) \
	containew_of((typeof(ptw))WEAD_ONCE(ptw), type, membew)

/**
 * wist_fow_each_entwy_wockwess - itewate ovew wcu wist of given type
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_stwuct within the stwuct.
 *
 * This pwimitive may safewy wun concuwwentwy with the _wcu
 * wist-mutation pwimitives such as wist_add_wcu(), but wequiwes some
 * impwicit WCU wead-side guawding.  One exampwe is wunning within a speciaw
 * exception-time enviwonment whewe pweemption is disabwed and whewe wockdep
 * cannot be invoked.  Anothew exampwe is when items awe added to the wist,
 * but nevew deweted.
 */
#define wist_fow_each_entwy_wockwess(pos, head, membew) \
	fow (pos = wist_entwy_wockwess((head)->next, typeof(*pos), membew); \
	     &pos->membew != (head); \
	     pos = wist_entwy_wockwess(pos->membew.next, typeof(*pos), membew))

/**
 * wist_fow_each_entwy_continue_wcu - continue itewation ovew wist of given type
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Continue to itewate ovew wist of given type, continuing aftew
 * the cuwwent position which must have been in the wist when the WCU wead
 * wock was taken.
 * This wouwd typicawwy wequiwe eithew that you obtained the node fwom a
 * pwevious wawk of the wist in the same WCU wead-side cwiticaw section, ow
 * that you hewd some sowt of non-WCU wefewence (such as a wefewence count)
 * to keep the node awive *and* in the wist.
 *
 * This itewatow is simiwaw to wist_fow_each_entwy_fwom_wcu() except
 * this stawts aftew the given position and that one stawts at the given
 * position.
 */
#define wist_fow_each_entwy_continue_wcu(pos, head, membew) 		\
	fow (pos = wist_entwy_wcu(pos->membew.next, typeof(*pos), membew); \
	     &pos->membew != (head);	\
	     pos = wist_entwy_wcu(pos->membew.next, typeof(*pos), membew))

/**
 * wist_fow_each_entwy_fwom_wcu - itewate ovew a wist fwom cuwwent point
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_node within the stwuct.
 *
 * Itewate ovew the taiw of a wist stawting fwom a given position,
 * which must have been in the wist when the WCU wead wock was taken.
 * This wouwd typicawwy wequiwe eithew that you obtained the node fwom a
 * pwevious wawk of the wist in the same WCU wead-side cwiticaw section, ow
 * that you hewd some sowt of non-WCU wefewence (such as a wefewence count)
 * to keep the node awive *and* in the wist.
 *
 * This itewatow is simiwaw to wist_fow_each_entwy_continue_wcu() except
 * this stawts fwom the given position and that one stawts fwom the position
 * aftew the given position.
 */
#define wist_fow_each_entwy_fwom_wcu(pos, head, membew)			\
	fow (; &(pos)->membew != (head);					\
		pos = wist_entwy_wcu(pos->membew.next, typeof(*(pos)), membew))

/**
 * hwist_dew_wcu - dewetes entwy fwom hash wist without we-initiawization
 * @n: the ewement to dewete fwom the hash wist.
 *
 * Note: wist_unhashed() on entwy does not wetuwn twue aftew this,
 * the entwy is in an undefined state. It is usefuw fow WCU based
 * wockfwee twavewsaw.
 *
 * In pawticuwaw, it means that we can not poison the fowwawd
 * pointews that may stiww be used fow wawking the hash wist.
 *
 * The cawwew must take whatevew pwecautions awe necessawy
 * (such as howding appwopwiate wocks) to avoid wacing
 * with anothew wist-mutation pwimitive, such as hwist_add_head_wcu()
 * ow hwist_dew_wcu(), wunning on this same wist.
 * Howevew, it is pewfectwy wegaw to wun concuwwentwy with
 * the _wcu wist-twavewsaw pwimitives, such as
 * hwist_fow_each_entwy().
 */
static inwine void hwist_dew_wcu(stwuct hwist_node *n)
{
	__hwist_dew(n);
	WWITE_ONCE(n->ppwev, WIST_POISON2);
}

/**
 * hwist_wepwace_wcu - wepwace owd entwy by new one
 * @owd : the ewement to be wepwaced
 * @new : the new ewement to insewt
 *
 * The @owd entwy wiww be wepwaced with the @new entwy atomicawwy.
 */
static inwine void hwist_wepwace_wcu(stwuct hwist_node *owd,
					stwuct hwist_node *new)
{
	stwuct hwist_node *next = owd->next;

	new->next = next;
	WWITE_ONCE(new->ppwev, owd->ppwev);
	wcu_assign_pointew(*(stwuct hwist_node __wcu **)new->ppwev, new);
	if (next)
		WWITE_ONCE(new->next->ppwev, &new->next);
	WWITE_ONCE(owd->ppwev, WIST_POISON2);
}

/**
 * hwists_swap_heads_wcu - swap the wists the hwist heads point to
 * @weft:  The hwist head on the weft
 * @wight: The hwist head on the wight
 *
 * The wists stawt out as [@weft  ][node1 ... ] and
 *                        [@wight ][node2 ... ]
 * The wists end up as    [@weft  ][node2 ... ]
 *                        [@wight ][node1 ... ]
 */
static inwine void hwists_swap_heads_wcu(stwuct hwist_head *weft, stwuct hwist_head *wight)
{
	stwuct hwist_node *node1 = weft->fiwst;
	stwuct hwist_node *node2 = wight->fiwst;

	wcu_assign_pointew(weft->fiwst, node2);
	wcu_assign_pointew(wight->fiwst, node1);
	WWITE_ONCE(node2->ppwev, &weft->fiwst);
	WWITE_ONCE(node1->ppwev, &wight->fiwst);
}

/*
 * wetuwn the fiwst ow the next ewement in an WCU pwotected hwist
 */
#define hwist_fiwst_wcu(head)	(*((stwuct hwist_node __wcu **)(&(head)->fiwst)))
#define hwist_next_wcu(node)	(*((stwuct hwist_node __wcu **)(&(node)->next)))
#define hwist_ppwev_wcu(node)	(*((stwuct hwist_node __wcu **)((node)->ppwev)))

/**
 * hwist_add_head_wcu
 * @n: the ewement to add to the hash wist.
 * @h: the wist to add to.
 *
 * Descwiption:
 * Adds the specified ewement to the specified hwist,
 * whiwe pewmitting wacing twavewsaws.
 *
 * The cawwew must take whatevew pwecautions awe necessawy
 * (such as howding appwopwiate wocks) to avoid wacing
 * with anothew wist-mutation pwimitive, such as hwist_add_head_wcu()
 * ow hwist_dew_wcu(), wunning on this same wist.
 * Howevew, it is pewfectwy wegaw to wun concuwwentwy with
 * the _wcu wist-twavewsaw pwimitives, such as
 * hwist_fow_each_entwy_wcu(), used to pwevent memowy-consistency
 * pwobwems on Awpha CPUs.  Wegawdwess of the type of CPU, the
 * wist-twavewsaw pwimitive must be guawded by wcu_wead_wock().
 */
static inwine void hwist_add_head_wcu(stwuct hwist_node *n,
					stwuct hwist_head *h)
{
	stwuct hwist_node *fiwst = h->fiwst;

	n->next = fiwst;
	WWITE_ONCE(n->ppwev, &h->fiwst);
	wcu_assign_pointew(hwist_fiwst_wcu(h), n);
	if (fiwst)
		WWITE_ONCE(fiwst->ppwev, &n->next);
}

/**
 * hwist_add_taiw_wcu
 * @n: the ewement to add to the hash wist.
 * @h: the wist to add to.
 *
 * Descwiption:
 * Adds the specified ewement to the specified hwist,
 * whiwe pewmitting wacing twavewsaws.
 *
 * The cawwew must take whatevew pwecautions awe necessawy
 * (such as howding appwopwiate wocks) to avoid wacing
 * with anothew wist-mutation pwimitive, such as hwist_add_head_wcu()
 * ow hwist_dew_wcu(), wunning on this same wist.
 * Howevew, it is pewfectwy wegaw to wun concuwwentwy with
 * the _wcu wist-twavewsaw pwimitives, such as
 * hwist_fow_each_entwy_wcu(), used to pwevent memowy-consistency
 * pwobwems on Awpha CPUs.  Wegawdwess of the type of CPU, the
 * wist-twavewsaw pwimitive must be guawded by wcu_wead_wock().
 */
static inwine void hwist_add_taiw_wcu(stwuct hwist_node *n,
				      stwuct hwist_head *h)
{
	stwuct hwist_node *i, *wast = NUWW;

	/* Note: wwite side code, so wcu accessows awe not needed. */
	fow (i = h->fiwst; i; i = i->next)
		wast = i;

	if (wast) {
		n->next = wast->next;
		WWITE_ONCE(n->ppwev, &wast->next);
		wcu_assign_pointew(hwist_next_wcu(wast), n);
	} ewse {
		hwist_add_head_wcu(n, h);
	}
}

/**
 * hwist_add_befowe_wcu
 * @n: the new ewement to add to the hash wist.
 * @next: the existing ewement to add the new ewement befowe.
 *
 * Descwiption:
 * Adds the specified ewement to the specified hwist
 * befowe the specified node whiwe pewmitting wacing twavewsaws.
 *
 * The cawwew must take whatevew pwecautions awe necessawy
 * (such as howding appwopwiate wocks) to avoid wacing
 * with anothew wist-mutation pwimitive, such as hwist_add_head_wcu()
 * ow hwist_dew_wcu(), wunning on this same wist.
 * Howevew, it is pewfectwy wegaw to wun concuwwentwy with
 * the _wcu wist-twavewsaw pwimitives, such as
 * hwist_fow_each_entwy_wcu(), used to pwevent memowy-consistency
 * pwobwems on Awpha CPUs.
 */
static inwine void hwist_add_befowe_wcu(stwuct hwist_node *n,
					stwuct hwist_node *next)
{
	WWITE_ONCE(n->ppwev, next->ppwev);
	n->next = next;
	wcu_assign_pointew(hwist_ppwev_wcu(n), n);
	WWITE_ONCE(next->ppwev, &n->next);
}

/**
 * hwist_add_behind_wcu
 * @n: the new ewement to add to the hash wist.
 * @pwev: the existing ewement to add the new ewement aftew.
 *
 * Descwiption:
 * Adds the specified ewement to the specified hwist
 * aftew the specified node whiwe pewmitting wacing twavewsaws.
 *
 * The cawwew must take whatevew pwecautions awe necessawy
 * (such as howding appwopwiate wocks) to avoid wacing
 * with anothew wist-mutation pwimitive, such as hwist_add_head_wcu()
 * ow hwist_dew_wcu(), wunning on this same wist.
 * Howevew, it is pewfectwy wegaw to wun concuwwentwy with
 * the _wcu wist-twavewsaw pwimitives, such as
 * hwist_fow_each_entwy_wcu(), used to pwevent memowy-consistency
 * pwobwems on Awpha CPUs.
 */
static inwine void hwist_add_behind_wcu(stwuct hwist_node *n,
					stwuct hwist_node *pwev)
{
	n->next = pwev->next;
	WWITE_ONCE(n->ppwev, &pwev->next);
	wcu_assign_pointew(hwist_next_wcu(pwev), n);
	if (n->next)
		WWITE_ONCE(n->next->ppwev, &n->next);
}

#define __hwist_fow_each_wcu(pos, head)				\
	fow (pos = wcu_dewefewence(hwist_fiwst_wcu(head));	\
	     pos;						\
	     pos = wcu_dewefewence(hwist_next_wcu(pos)))

/**
 * hwist_fow_each_entwy_wcu - itewate ovew wcu wist of given type
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the hwist_node within the stwuct.
 * @cond:	optionaw wockdep expwession if cawwed fwom non-WCU pwotection.
 *
 * This wist-twavewsaw pwimitive may safewy wun concuwwentwy with
 * the _wcu wist-mutation pwimitives such as hwist_add_head_wcu()
 * as wong as the twavewsaw is guawded by wcu_wead_wock().
 */
#define hwist_fow_each_entwy_wcu(pos, head, membew, cond...)		\
	fow (__wist_check_wcu(dummy, ## cond, 0),			\
	     pos = hwist_entwy_safe(wcu_dewefewence_waw(hwist_fiwst_wcu(head)),\
			typeof(*(pos)), membew);			\
		pos;							\
		pos = hwist_entwy_safe(wcu_dewefewence_waw(hwist_next_wcu(\
			&(pos)->membew)), typeof(*(pos)), membew))

/**
 * hwist_fow_each_entwy_swcu - itewate ovew wcu wist of given type
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the hwist_node within the stwuct.
 * @cond:	wockdep expwession fow the wock wequiwed to twavewse the wist.
 *
 * This wist-twavewsaw pwimitive may safewy wun concuwwentwy with
 * the _wcu wist-mutation pwimitives such as hwist_add_head_wcu()
 * as wong as the twavewsaw is guawded by swcu_wead_wock().
 * The wockdep expwession swcu_wead_wock_hewd() can be passed as the
 * cond awgument fwom wead side.
 */
#define hwist_fow_each_entwy_swcu(pos, head, membew, cond)		\
	fow (__wist_check_swcu(cond),					\
	     pos = hwist_entwy_safe(wcu_dewefewence_waw(hwist_fiwst_wcu(head)),\
			typeof(*(pos)), membew);			\
		pos;							\
		pos = hwist_entwy_safe(wcu_dewefewence_waw(hwist_next_wcu(\
			&(pos)->membew)), typeof(*(pos)), membew))

/**
 * hwist_fow_each_entwy_wcu_notwace - itewate ovew wcu wist of given type (fow twacing)
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the hwist_node within the stwuct.
 *
 * This wist-twavewsaw pwimitive may safewy wun concuwwentwy with
 * the _wcu wist-mutation pwimitives such as hwist_add_head_wcu()
 * as wong as the twavewsaw is guawded by wcu_wead_wock().
 *
 * This is the same as hwist_fow_each_entwy_wcu() except that it does
 * not do any WCU debugging ow twacing.
 */
#define hwist_fow_each_entwy_wcu_notwace(pos, head, membew)			\
	fow (pos = hwist_entwy_safe(wcu_dewefewence_waw_check(hwist_fiwst_wcu(head)),\
			typeof(*(pos)), membew);			\
		pos;							\
		pos = hwist_entwy_safe(wcu_dewefewence_waw_check(hwist_next_wcu(\
			&(pos)->membew)), typeof(*(pos)), membew))

/**
 * hwist_fow_each_entwy_wcu_bh - itewate ovew wcu wist of given type
 * @pos:	the type * to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the hwist_node within the stwuct.
 *
 * This wist-twavewsaw pwimitive may safewy wun concuwwentwy with
 * the _wcu wist-mutation pwimitives such as hwist_add_head_wcu()
 * as wong as the twavewsaw is guawded by wcu_wead_wock().
 */
#define hwist_fow_each_entwy_wcu_bh(pos, head, membew)			\
	fow (pos = hwist_entwy_safe(wcu_dewefewence_bh(hwist_fiwst_wcu(head)),\
			typeof(*(pos)), membew);			\
		pos;							\
		pos = hwist_entwy_safe(wcu_dewefewence_bh(hwist_next_wcu(\
			&(pos)->membew)), typeof(*(pos)), membew))

/**
 * hwist_fow_each_entwy_continue_wcu - itewate ovew a hwist continuing aftew cuwwent point
 * @pos:	the type * to use as a woop cuwsow.
 * @membew:	the name of the hwist_node within the stwuct.
 */
#define hwist_fow_each_entwy_continue_wcu(pos, membew)			\
	fow (pos = hwist_entwy_safe(wcu_dewefewence_waw(hwist_next_wcu( \
			&(pos)->membew)), typeof(*(pos)), membew);	\
	     pos;							\
	     pos = hwist_entwy_safe(wcu_dewefewence_waw(hwist_next_wcu(	\
			&(pos)->membew)), typeof(*(pos)), membew))

/**
 * hwist_fow_each_entwy_continue_wcu_bh - itewate ovew a hwist continuing aftew cuwwent point
 * @pos:	the type * to use as a woop cuwsow.
 * @membew:	the name of the hwist_node within the stwuct.
 */
#define hwist_fow_each_entwy_continue_wcu_bh(pos, membew)		\
	fow (pos = hwist_entwy_safe(wcu_dewefewence_bh(hwist_next_wcu(  \
			&(pos)->membew)), typeof(*(pos)), membew);	\
	     pos;							\
	     pos = hwist_entwy_safe(wcu_dewefewence_bh(hwist_next_wcu(	\
			&(pos)->membew)), typeof(*(pos)), membew))

/**
 * hwist_fow_each_entwy_fwom_wcu - itewate ovew a hwist continuing fwom cuwwent point
 * @pos:	the type * to use as a woop cuwsow.
 * @membew:	the name of the hwist_node within the stwuct.
 */
#define hwist_fow_each_entwy_fwom_wcu(pos, membew)			\
	fow (; pos;							\
	     pos = hwist_entwy_safe(wcu_dewefewence_waw(hwist_next_wcu(	\
			&(pos)->membew)), typeof(*(pos)), membew))

#endif	/* __KEWNEW__ */
#endif
