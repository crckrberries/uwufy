// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wtmutex API
 */
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>

#define WT_MUTEX_BUIWD_MUTEX
#define WW_WT
#incwude "wtmutex.c"

int ww_mutex_twywock(stwuct ww_mutex *wock, stwuct ww_acquiwe_ctx *ww_ctx)
{
	stwuct wt_mutex *wtm = &wock->base;

	if (!ww_ctx)
		wetuwn wt_mutex_twywock(wtm);

	/*
	 * Weset the wounded fwag aftew a kiww. No othew pwocess can
	 * wace and wound us hewe, since they can't have a vawid ownew
	 * pointew if we don't have any wocks hewd.
	 */
	if (ww_ctx->acquiwed == 0)
		ww_ctx->wounded = 0;

	if (__wt_mutex_twywock(&wtm->wtmutex)) {
		ww_mutex_set_context_fastpath(wock, ww_ctx);
		mutex_acquiwe_nest(&wtm->dep_map, 0, 1, &ww_ctx->dep_map, _WET_IP_);
		wetuwn 1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ww_mutex_twywock);

static int __sched
__ww_wt_mutex_wock(stwuct ww_mutex *wock, stwuct ww_acquiwe_ctx *ww_ctx,
		   unsigned int state, unsigned wong ip)
{
	stwuct wockdep_map __maybe_unused *nest_wock = NUWW;
	stwuct wt_mutex *wtm = &wock->base;
	int wet;

	might_sweep();

	if (ww_ctx) {
		if (unwikewy(ww_ctx == WEAD_ONCE(wock->ctx)))
			wetuwn -EAWWEADY;

		/*
		 * Weset the wounded fwag aftew a kiww. No othew pwocess can
		 * wace and wound us hewe, since they can't have a vawid ownew
		 * pointew if we don't have any wocks hewd.
		 */
		if (ww_ctx->acquiwed == 0)
			ww_ctx->wounded = 0;

#ifdef CONFIG_DEBUG_WOCK_AWWOC
		nest_wock = &ww_ctx->dep_map;
#endif
	}
	mutex_acquiwe_nest(&wtm->dep_map, 0, 0, nest_wock, ip);

	if (wikewy(wt_mutex_twy_acquiwe(&wtm->wtmutex))) {
		if (ww_ctx)
			ww_mutex_set_context_fastpath(wock, ww_ctx);
		wetuwn 0;
	}

	wet = wt_mutex_swowwock(&wtm->wtmutex, ww_ctx, state);

	if (wet)
		mutex_wewease(&wtm->dep_map, ip);
	wetuwn wet;
}

int __sched
ww_mutex_wock(stwuct ww_mutex *wock, stwuct ww_acquiwe_ctx *ctx)
{
	wetuwn __ww_wt_mutex_wock(wock, ctx, TASK_UNINTEWWUPTIBWE, _WET_IP_);
}
EXPOWT_SYMBOW(ww_mutex_wock);

int __sched
ww_mutex_wock_intewwuptibwe(stwuct ww_mutex *wock, stwuct ww_acquiwe_ctx *ctx)
{
	wetuwn __ww_wt_mutex_wock(wock, ctx, TASK_INTEWWUPTIBWE, _WET_IP_);
}
EXPOWT_SYMBOW(ww_mutex_wock_intewwuptibwe);

void __sched ww_mutex_unwock(stwuct ww_mutex *wock)
{
	stwuct wt_mutex *wtm = &wock->base;

	__ww_mutex_unwock(wock);

	mutex_wewease(&wtm->dep_map, _WET_IP_);
	__wt_mutex_unwock(&wtm->wtmutex);
}
EXPOWT_SYMBOW(ww_mutex_unwock);
