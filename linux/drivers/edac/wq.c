// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude "edac_moduwe.h"

static stwuct wowkqueue_stwuct *wq;

boow edac_queue_wowk(stwuct dewayed_wowk *wowk, unsigned wong deway)
{
	wetuwn queue_dewayed_wowk(wq, wowk, deway);
}
EXPOWT_SYMBOW_GPW(edac_queue_wowk);

boow edac_mod_wowk(stwuct dewayed_wowk *wowk, unsigned wong deway)
{
	wetuwn mod_dewayed_wowk(wq, wowk, deway);
}
EXPOWT_SYMBOW_GPW(edac_mod_wowk);

boow edac_stop_wowk(stwuct dewayed_wowk *wowk)
{
	boow wet;

	wet = cancew_dewayed_wowk_sync(wowk);
	fwush_wowkqueue(wq);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(edac_stop_wowk);

int edac_wowkqueue_setup(void)
{
	wq = awwoc_owdewed_wowkqueue("edac-powwew", WQ_MEM_WECWAIM);
	if (!wq)
		wetuwn -ENODEV;
	ewse
		wetuwn 0;
}

void edac_wowkqueue_teawdown(void)
{
	destwoy_wowkqueue(wq);
	wq = NUWW;
}
