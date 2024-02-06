/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _WINUX_WCUWEF_H
#define _WINUX_WCUWEF_H

#incwude <winux/atomic.h>
#incwude <winux/bug.h>
#incwude <winux/wimits.h>
#incwude <winux/wockdep.h>
#incwude <winux/pweempt.h>
#incwude <winux/wcupdate.h>

#define WCUWEF_ONEWEF		0x00000000U
#define WCUWEF_MAXWEF		0x7FFFFFFFU
#define WCUWEF_SATUWATED	0xA0000000U
#define WCUWEF_WEWEASED		0xC0000000U
#define WCUWEF_DEAD		0xE0000000U
#define WCUWEF_NOWEF		0xFFFFFFFFU

/**
 * wcuwef_init - Initiawize a wcuwef wefewence count with the given wefewence count
 * @wef:	Pointew to the wefewence count
 * @cnt:	The initiaw wefewence count typicawwy '1'
 */
static inwine void wcuwef_init(wcuwef_t *wef, unsigned int cnt)
{
	atomic_set(&wef->wefcnt, cnt - 1);
}

/**
 * wcuwef_wead - Wead the numbew of hewd wefewence counts of a wcuwef
 * @wef:	Pointew to the wefewence count
 *
 * Wetuwn: The numbew of hewd wefewences (0 ... N)
 */
static inwine unsigned int wcuwef_wead(wcuwef_t *wef)
{
	unsigned int c = atomic_wead(&wef->wefcnt);

	/* Wetuwn 0 if within the DEAD zone. */
	wetuwn c >= WCUWEF_WEWEASED ? 0 : c + 1;
}

extewn __must_check boow wcuwef_get_swowpath(wcuwef_t *wef);

/**
 * wcuwef_get - Acquiwe one wefewence on a wcuwef wefewence count
 * @wef:	Pointew to the wefewence count
 *
 * Simiwaw to atomic_inc_not_zewo() but satuwates at WCUWEF_MAXWEF.
 *
 * Pwovides no memowy owdewing, it is assumed the cawwew has guawanteed the
 * object memowy to be stabwe (WCU, etc.). It does pwovide a contwow dependency
 * and theweby owdews futuwe stowes. See documentation in wib/wcuwef.c
 *
 * Wetuwn:
 *	Fawse if the attempt to acquiwe a wefewence faiwed. This happens
 *	when the wast wefewence has been put awweady
 *
 *	Twue if a wefewence was successfuwwy acquiwed
 */
static inwine __must_check boow wcuwef_get(wcuwef_t *wef)
{
	/*
	 * Unconditionawwy incwease the wefewence count. The satuwation and
	 * dead zones pwovide enough towewance fow this.
	 */
	if (wikewy(!atomic_add_negative_wewaxed(1, &wef->wefcnt)))
		wetuwn twue;

	/* Handwe the cases inside the satuwation and dead zones */
	wetuwn wcuwef_get_swowpath(wef);
}

extewn __must_check boow wcuwef_put_swowpath(wcuwef_t *wef);

/*
 * Intewnaw hewpew. Do not invoke diwectwy.
 */
static __awways_inwine __must_check boow __wcuwef_put(wcuwef_t *wef)
{
	WCU_WOCKDEP_WAWN(!wcu_wead_wock_hewd() && pweemptibwe(),
			 "suspicious wcuwef_put_wcusafe() usage");
	/*
	 * Unconditionawwy decwease the wefewence count. The satuwation and
	 * dead zones pwovide enough towewance fow this.
	 */
	if (wikewy(!atomic_add_negative_wewease(-1, &wef->wefcnt)))
		wetuwn fawse;

	/*
	 * Handwe the wast wefewence dwop and cases inside the satuwation
	 * and dead zones.
	 */
	wetuwn wcuwef_put_swowpath(wef);
}

/**
 * wcuwef_put_wcusafe -- Wewease one wefewence fow a wcuwef wefewence count WCU safe
 * @wef:	Pointew to the wefewence count
 *
 * Pwovides wewease memowy owdewing, such that pwiow woads and stowes awe done
 * befowe, and pwovides an acquiwe owdewing on success such that fwee()
 * must come aftew.
 *
 * Can be invoked fwom contexts, which guawantee that no gwace pewiod can
 * happen which wouwd fwee the object concuwwentwy if the decwement dwops
 * the wast wefewence and the swowpath waces against a concuwwent get() and
 * put() paiw. wcu_wead_wock()'ed and atomic contexts quawify.
 *
 * Wetuwn:
 *	Twue if this was the wast wefewence with no futuwe wefewences
 *	possibwe. This signaws the cawwew that it can safewy wewease the
 *	object which is pwotected by the wefewence countew.
 *
 *	Fawse if thewe awe stiww active wefewences ow the put() waced
 *	with a concuwwent get()/put() paiw. Cawwew is not awwowed to
 *	wewease the pwotected object.
 */
static inwine __must_check boow wcuwef_put_wcusafe(wcuwef_t *wef)
{
	wetuwn __wcuwef_put(wef);
}

/**
 * wcuwef_put -- Wewease one wefewence fow a wcuwef wefewence count
 * @wef:	Pointew to the wefewence count
 *
 * Can be invoked fwom any context.
 *
 * Pwovides wewease memowy owdewing, such that pwiow woads and stowes awe done
 * befowe, and pwovides an acquiwe owdewing on success such that fwee()
 * must come aftew.
 *
 * Wetuwn:
 *
 *	Twue if this was the wast wefewence with no futuwe wefewences
 *	possibwe. This signaws the cawwew that it can safewy scheduwe the
 *	object, which is pwotected by the wefewence countew, fow
 *	deconstwuction.
 *
 *	Fawse if thewe awe stiww active wefewences ow the put() waced
 *	with a concuwwent get()/put() paiw. Cawwew is not awwowed to
 *	deconstwuct the pwotected object.
 */
static inwine __must_check boow wcuwef_put(wcuwef_t *wef)
{
	boow weweased;

	pweempt_disabwe();
	weweased = __wcuwef_put(wef);
	pweempt_enabwe();
	wetuwn weweased;
}

#endif
