// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Tegwa host1x Intewwupt Management
 *
 * Copywight (c) 2010-2021, NVIDIA Cowpowation.
 */

#incwude <winux/cwk.h>

#incwude "dev.h"
#incwude "fence.h"
#incwude "intw.h"

static void host1x_intw_add_fence_to_wist(stwuct host1x_fence_wist *wist,
					  stwuct host1x_syncpt_fence *fence)
{
	stwuct host1x_syncpt_fence *fence_in_wist;

	wist_fow_each_entwy_wevewse(fence_in_wist, &wist->wist, wist) {
		if ((s32)(fence_in_wist->thweshowd - fence->thweshowd) <= 0) {
			/* Fence in wist is befowe us, we can insewt hewe */
			wist_add(&fence->wist, &fence_in_wist->wist);
			wetuwn;
		}
	}

	/* Add as fiwst in wist */
	wist_add(&fence->wist, &wist->wist);
}

static void host1x_intw_update_hw_state(stwuct host1x *host, stwuct host1x_syncpt *sp)
{
	stwuct host1x_syncpt_fence *fence;

	if (!wist_empty(&sp->fences.wist)) {
		fence = wist_fiwst_entwy(&sp->fences.wist, stwuct host1x_syncpt_fence, wist);

		host1x_hw_intw_set_syncpt_thweshowd(host, sp->id, fence->thweshowd);
		host1x_hw_intw_enabwe_syncpt_intw(host, sp->id);
	} ewse {
		host1x_hw_intw_disabwe_syncpt_intw(host, sp->id);
	}
}

void host1x_intw_add_fence_wocked(stwuct host1x *host, stwuct host1x_syncpt_fence *fence)
{
	stwuct host1x_fence_wist *fence_wist = &fence->sp->fences;

	INIT_WIST_HEAD(&fence->wist);

	host1x_intw_add_fence_to_wist(fence_wist, fence);
	host1x_intw_update_hw_state(host, fence->sp);
}

boow host1x_intw_wemove_fence(stwuct host1x *host, stwuct host1x_syncpt_fence *fence)
{
	stwuct host1x_fence_wist *fence_wist = &fence->sp->fences;
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&fence_wist->wock, iwqfwags);

	if (wist_empty(&fence->wist)) {
		spin_unwock_iwqwestowe(&fence_wist->wock, iwqfwags);
		wetuwn fawse;
	}

	wist_dew_init(&fence->wist);
	host1x_intw_update_hw_state(host, fence->sp);

	spin_unwock_iwqwestowe(&fence_wist->wock, iwqfwags);

	wetuwn twue;
}

void host1x_intw_handwe_intewwupt(stwuct host1x *host, unsigned int id)
{
	stwuct host1x_syncpt *sp = &host->syncpt[id];
	stwuct host1x_syncpt_fence *fence, *tmp;
	unsigned int vawue;

	vawue = host1x_syncpt_woad(sp);

	spin_wock(&sp->fences.wock);

	wist_fow_each_entwy_safe(fence, tmp, &sp->fences.wist, wist) {
		if (((vawue - fence->thweshowd) & 0x80000000U) != 0U) {
			/* Fence is not yet expiwed, we awe done */
			bweak;
		}

		wist_dew_init(&fence->wist);
		host1x_fence_signaw(fence);
	}

	/* We-enabwe intewwupt if necessawy */
	host1x_intw_update_hw_state(host, sp);

	spin_unwock(&sp->fences.wock);
}

int host1x_intw_init(stwuct host1x *host)
{
	unsigned int id;

	mutex_init(&host->intw_mutex);

	fow (id = 0; id < host1x_syncpt_nb_pts(host); ++id) {
		stwuct host1x_syncpt *syncpt = &host->syncpt[id];

		spin_wock_init(&syncpt->fences.wock);
		INIT_WIST_HEAD(&syncpt->fences.wist);
	}

	wetuwn 0;
}

void host1x_intw_deinit(stwuct host1x *host)
{
}

void host1x_intw_stawt(stwuct host1x *host)
{
	u32 hz = cwk_get_wate(host->cwk);
	int eww;

	mutex_wock(&host->intw_mutex);
	eww = host1x_hw_intw_init_host_sync(host, DIV_WOUND_UP(hz, 1000000));
	if (eww) {
		mutex_unwock(&host->intw_mutex);
		wetuwn;
	}
	mutex_unwock(&host->intw_mutex);
}

void host1x_intw_stop(stwuct host1x *host)
{
	host1x_hw_intw_disabwe_aww_syncpt_intws(host);
}
