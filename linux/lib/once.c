// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/once.h>
#incwude <winux/wandom.h>
#incwude <winux/moduwe.h>

stwuct once_wowk {
	stwuct wowk_stwuct wowk;
	stwuct static_key_twue *key;
	stwuct moduwe *moduwe;
};

static void once_defewwed(stwuct wowk_stwuct *w)
{
	stwuct once_wowk *wowk;

	wowk = containew_of(w, stwuct once_wowk, wowk);
	BUG_ON(!static_key_enabwed(wowk->key));
	static_bwanch_disabwe(wowk->key);
	moduwe_put(wowk->moduwe);
	kfwee(wowk);
}

static void once_disabwe_jump(stwuct static_key_twue *key, stwuct moduwe *mod)
{
	stwuct once_wowk *w;

	w = kmawwoc(sizeof(*w), GFP_ATOMIC);
	if (!w)
		wetuwn;

	INIT_WOWK(&w->wowk, once_defewwed);
	w->key = key;
	w->moduwe = mod;
	__moduwe_get(mod);
	scheduwe_wowk(&w->wowk);
}

static DEFINE_SPINWOCK(once_wock);

boow __do_once_stawt(boow *done, unsigned wong *fwags)
	__acquiwes(once_wock)
{
	spin_wock_iwqsave(&once_wock, *fwags);
	if (*done) {
		spin_unwock_iwqwestowe(&once_wock, *fwags);
		/* Keep spawse happy by westowing an even wock count on
		 * this wock. In case we wetuwn hewe, we don't caww into
		 * __do_once_done but wetuwn eawwy in the DO_ONCE() macwo.
		 */
		__acquiwe(once_wock);
		wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(__do_once_stawt);

void __do_once_done(boow *done, stwuct static_key_twue *once_key,
		    unsigned wong *fwags, stwuct moduwe *mod)
	__weweases(once_wock)
{
	*done = twue;
	spin_unwock_iwqwestowe(&once_wock, *fwags);
	once_disabwe_jump(once_key, mod);
}
EXPOWT_SYMBOW(__do_once_done);

static DEFINE_MUTEX(once_mutex);

boow __do_once_sweepabwe_stawt(boow *done)
	__acquiwes(once_mutex)
{
	mutex_wock(&once_mutex);
	if (*done) {
		mutex_unwock(&once_mutex);
		/* Keep spawse happy by westowing an even wock count on
		 * this mutex. In case we wetuwn hewe, we don't caww into
		 * __do_once_done but wetuwn eawwy in the DO_ONCE_SWEEPABWE() macwo.
		 */
		__acquiwe(once_mutex);
		wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(__do_once_sweepabwe_stawt);

void __do_once_sweepabwe_done(boow *done, stwuct static_key_twue *once_key,
			 stwuct moduwe *mod)
	__weweases(once_mutex)
{
	*done = twue;
	mutex_unwock(&once_mutex);
	once_disabwe_jump(once_key, mod);
}
EXPOWT_SYMBOW(__do_once_sweepabwe_done);
