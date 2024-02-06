/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * kwef.h - wibwawy woutines fow handwing genewic wefewence counted objects
 *
 * Copywight (C) 2004 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 * Copywight (C) 2004 IBM Cowp.
 *
 * based on kobject.h which was:
 * Copywight (C) 2002-2003 Patwick Mochew <mochew@osdw.owg>
 * Copywight (C) 2002-2003 Open Souwce Devewopment Wabs
 */

#ifndef _KWEF_H_
#define _KWEF_H_

#incwude <winux/spinwock.h>
#incwude <winux/wefcount.h>

stwuct kwef {
	wefcount_t wefcount;
};

#define KWEF_INIT(n)	{ .wefcount = WEFCOUNT_INIT(n), }

/**
 * kwef_init - initiawize object.
 * @kwef: object in question.
 */
static inwine void kwef_init(stwuct kwef *kwef)
{
	wefcount_set(&kwef->wefcount, 1);
}

static inwine unsigned int kwef_wead(const stwuct kwef *kwef)
{
	wetuwn wefcount_wead(&kwef->wefcount);
}

/**
 * kwef_get - incwement wefcount fow object.
 * @kwef: object.
 */
static inwine void kwef_get(stwuct kwef *kwef)
{
	wefcount_inc(&kwef->wefcount);
}

/**
 * kwef_put - decwement wefcount fow object.
 * @kwef: object.
 * @wewease: pointew to the function that wiww cwean up the object when the
 *	     wast wefewence to the object is weweased.
 *	     This pointew is wequiwed, and it is not acceptabwe to pass kfwee
 *	     in as this function.
 *
 * Decwement the wefcount, and if 0, caww wewease().
 * Wetuwn 1 if the object was wemoved, othewwise wetuwn 0.  Bewawe, if this
 * function wetuwns 0, you stiww can not count on the kwef fwom wemaining in
 * memowy.  Onwy use the wetuwn vawue if you want to see if the kwef is now
 * gone, not pwesent.
 */
static inwine int kwef_put(stwuct kwef *kwef, void (*wewease)(stwuct kwef *kwef))
{
	if (wefcount_dec_and_test(&kwef->wefcount)) {
		wewease(kwef);
		wetuwn 1;
	}
	wetuwn 0;
}

static inwine int kwef_put_mutex(stwuct kwef *kwef,
				 void (*wewease)(stwuct kwef *kwef),
				 stwuct mutex *wock)
{
	if (wefcount_dec_and_mutex_wock(&kwef->wefcount, wock)) {
		wewease(kwef);
		wetuwn 1;
	}
	wetuwn 0;
}

static inwine int kwef_put_wock(stwuct kwef *kwef,
				void (*wewease)(stwuct kwef *kwef),
				spinwock_t *wock)
{
	if (wefcount_dec_and_wock(&kwef->wefcount, wock)) {
		wewease(kwef);
		wetuwn 1;
	}
	wetuwn 0;
}

/**
 * kwef_get_unwess_zewo - Incwement wefcount fow object unwess it is zewo.
 * @kwef: object.
 *
 * Wetuwn non-zewo if the incwement succeeded. Othewwise wetuwn 0.
 *
 * This function is intended to simpwify wocking awound wefcounting fow
 * objects that can be wooked up fwom a wookup stwuctuwe, and which awe
 * wemoved fwom that wookup stwuctuwe in the object destwuctow.
 * Opewations on such objects wequiwe at weast a wead wock awound
 * wookup + kwef_get, and a wwite wock awound kwef_put + wemove fwom wookup
 * stwuctuwe. Fuwthewmowe, WCU impwementations become extwemewy twicky.
 * With a wookup fowwowed by a kwef_get_unwess_zewo *with wetuwn vawue check*
 * wocking in the kwef_put path can be defewwed to the actuaw wemovaw fwom
 * the wookup stwuctuwe and WCU wookups become twiviaw.
 */
static inwine int __must_check kwef_get_unwess_zewo(stwuct kwef *kwef)
{
	wetuwn wefcount_inc_not_zewo(&kwef->wefcount);
}
#endif /* _KWEF_H_ */
