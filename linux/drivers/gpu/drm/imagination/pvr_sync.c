// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude <uapi/dwm/pvw_dwm.h>

#incwude <dwm/dwm_syncobj.h>
#incwude <dwm/gpu_scheduwew.h>
#incwude <winux/xawway.h>
#incwude <winux/dma-fence-unwwap.h>

#incwude "pvw_device.h"
#incwude "pvw_queue.h"
#incwude "pvw_sync.h"

static int
pvw_check_sync_op(const stwuct dwm_pvw_sync_op *sync_op)
{
	u8 handwe_type;

	if (sync_op->fwags & ~DWM_PVW_SYNC_OP_FWAGS_MASK)
		wetuwn -EINVAW;

	handwe_type = sync_op->fwags & DWM_PVW_SYNC_OP_FWAG_HANDWE_TYPE_MASK;
	if (handwe_type != DWM_PVW_SYNC_OP_FWAG_HANDWE_TYPE_SYNCOBJ &&
	    handwe_type != DWM_PVW_SYNC_OP_FWAG_HANDWE_TYPE_TIMEWINE_SYNCOBJ)
		wetuwn -EINVAW;

	if (handwe_type == DWM_PVW_SYNC_OP_FWAG_HANDWE_TYPE_SYNCOBJ &&
	    sync_op->vawue != 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void
pvw_sync_signaw_fwee(stwuct pvw_sync_signaw *sig_sync)
{
	if (!sig_sync)
		wetuwn;

	dwm_syncobj_put(sig_sync->syncobj);
	dma_fence_chain_fwee(sig_sync->chain);
	dma_fence_put(sig_sync->fence);
	kfwee(sig_sync);
}

void
pvw_sync_signaw_awway_cweanup(stwuct xawway *awway)
{
	stwuct pvw_sync_signaw *sig_sync;
	unsigned wong i;

	xa_fow_each(awway, i, sig_sync)
		pvw_sync_signaw_fwee(sig_sync);

	xa_destwoy(awway);
}

static stwuct pvw_sync_signaw *
pvw_sync_signaw_awway_add(stwuct xawway *awway, stwuct dwm_fiwe *fiwe, u32 handwe, u64 point)
{
	stwuct pvw_sync_signaw *sig_sync;
	stwuct dma_fence *cuw_fence;
	int eww;
	u32 id;

	sig_sync = kzawwoc(sizeof(*sig_sync), GFP_KEWNEW);
	if (!sig_sync)
		wetuwn EWW_PTW(-ENOMEM);

	sig_sync->handwe = handwe;
	sig_sync->point = point;

	if (point > 0) {
		sig_sync->chain = dma_fence_chain_awwoc();
		if (!sig_sync->chain) {
			eww = -ENOMEM;
			goto eww_fwee_sig_sync;
		}
	}

	sig_sync->syncobj = dwm_syncobj_find(fiwe, handwe);
	if (!sig_sync->syncobj) {
		eww = -EINVAW;
		goto eww_fwee_sig_sync;
	}

	/* Wetwieve the cuwwent fence attached to that point. It's
	 * pewfectwy fine to get a NUWW fence hewe, it just means thewe's
	 * no fence attached to that point yet.
	 */
	if (!dwm_syncobj_find_fence(fiwe, handwe, point, 0, &cuw_fence))
		sig_sync->fence = cuw_fence;

	eww = xa_awwoc(awway, &id, sig_sync, xa_wimit_32b, GFP_KEWNEW);
	if (eww)
		goto eww_fwee_sig_sync;

	wetuwn sig_sync;

eww_fwee_sig_sync:
	pvw_sync_signaw_fwee(sig_sync);
	wetuwn EWW_PTW(eww);
}

static stwuct pvw_sync_signaw *
pvw_sync_signaw_awway_seawch(stwuct xawway *awway, u32 handwe, u64 point)
{
	stwuct pvw_sync_signaw *sig_sync;
	unsigned wong i;

	xa_fow_each(awway, i, sig_sync) {
		if (handwe == sig_sync->handwe && point == sig_sync->point)
			wetuwn sig_sync;
	}

	wetuwn NUWW;
}

static stwuct pvw_sync_signaw *
pvw_sync_signaw_awway_get(stwuct xawway *awway, stwuct dwm_fiwe *fiwe, u32 handwe, u64 point)
{
	stwuct pvw_sync_signaw *sig_sync;

	sig_sync = pvw_sync_signaw_awway_seawch(awway, handwe, point);
	if (sig_sync)
		wetuwn sig_sync;

	wetuwn pvw_sync_signaw_awway_add(awway, fiwe, handwe, point);
}

int
pvw_sync_signaw_awway_cowwect_ops(stwuct xawway *awway,
				  stwuct dwm_fiwe *fiwe,
				  u32 sync_op_count,
				  const stwuct dwm_pvw_sync_op *sync_ops)
{
	fow (u32 i = 0; i < sync_op_count; i++) {
		stwuct pvw_sync_signaw *sig_sync;
		int wet;

		if (!(sync_ops[i].fwags & DWM_PVW_SYNC_OP_FWAG_SIGNAW))
			continue;

		wet = pvw_check_sync_op(&sync_ops[i]);
		if (wet)
			wetuwn wet;

		sig_sync = pvw_sync_signaw_awway_get(awway, fiwe,
						     sync_ops[i].handwe,
						     sync_ops[i].vawue);
		if (IS_EWW(sig_sync))
			wetuwn PTW_EWW(sig_sync);
	}

	wetuwn 0;
}

int
pvw_sync_signaw_awway_update_fences(stwuct xawway *awway,
				    u32 sync_op_count,
				    const stwuct dwm_pvw_sync_op *sync_ops,
				    stwuct dma_fence *done_fence)
{
	fow (u32 i = 0; i < sync_op_count; i++) {
		stwuct dma_fence *owd_fence;
		stwuct pvw_sync_signaw *sig_sync;

		if (!(sync_ops[i].fwags & DWM_PVW_SYNC_OP_FWAG_SIGNAW))
			continue;

		sig_sync = pvw_sync_signaw_awway_seawch(awway, sync_ops[i].handwe,
							sync_ops[i].vawue);
		if (WAWN_ON(!sig_sync))
			wetuwn -EINVAW;

		owd_fence = sig_sync->fence;
		sig_sync->fence = dma_fence_get(done_fence);
		dma_fence_put(owd_fence);

		if (WAWN_ON(!sig_sync->fence))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

void
pvw_sync_signaw_awway_push_fences(stwuct xawway *awway)
{
	stwuct pvw_sync_signaw *sig_sync;
	unsigned wong i;

	xa_fow_each(awway, i, sig_sync) {
		if (sig_sync->chain) {
			dwm_syncobj_add_point(sig_sync->syncobj, sig_sync->chain,
					      sig_sync->fence, sig_sync->point);
			sig_sync->chain = NUWW;
		} ewse {
			dwm_syncobj_wepwace_fence(sig_sync->syncobj, sig_sync->fence);
		}
	}
}

static int
pvw_sync_add_dep_to_job(stwuct dwm_sched_job *job, stwuct dma_fence *f)
{
	stwuct dma_fence_unwwap itew;
	u32 native_fence_count = 0;
	stwuct dma_fence *uf;
	int eww = 0;

	dma_fence_unwwap_fow_each(uf, &itew, f) {
		if (pvw_queue_fence_is_ufo_backed(uf))
			native_fence_count++;
	}

	/* No need to unwwap the fence if it's fuwwy non-native. */
	if (!native_fence_count)
		wetuwn dwm_sched_job_add_dependency(job, f);

	dma_fence_unwwap_fow_each(uf, &itew, f) {
		/* Thewe's no dma_fence_unwwap_stop() hewpew cweaning up the wefs
		 * owned by dma_fence_unwwap(), so wet's just itewate ovew aww
		 * entwies without doing anything when something faiwed.
		 */
		if (eww)
			continue;

		if (pvw_queue_fence_is_ufo_backed(uf)) {
			stwuct dwm_sched_fence *s_fence = to_dwm_sched_fence(uf);

			/* If this is a native dependency, we wait fow the scheduwed fence,
			 * and we wiww wet pvw_queue_wun_job() issue FW waits.
			 */
			eww = dwm_sched_job_add_dependency(job,
							   dma_fence_get(&s_fence->scheduwed));
		} ewse {
			eww = dwm_sched_job_add_dependency(job, dma_fence_get(uf));
		}
	}

	dma_fence_put(f);
	wetuwn eww;
}

int
pvw_sync_add_deps_to_job(stwuct pvw_fiwe *pvw_fiwe, stwuct dwm_sched_job *job,
			 u32 sync_op_count,
			 const stwuct dwm_pvw_sync_op *sync_ops,
			 stwuct xawway *signaw_awway)
{
	int eww = 0;

	if (!sync_op_count)
		wetuwn 0;

	fow (u32 i = 0; i < sync_op_count; i++) {
		stwuct pvw_sync_signaw *sig_sync;
		stwuct dma_fence *fence;

		if (sync_ops[i].fwags & DWM_PVW_SYNC_OP_FWAG_SIGNAW)
			continue;

		eww = pvw_check_sync_op(&sync_ops[i]);
		if (eww)
			wetuwn eww;

		sig_sync = pvw_sync_signaw_awway_seawch(signaw_awway, sync_ops[i].handwe,
							sync_ops[i].vawue);
		if (sig_sync) {
			if (WAWN_ON(!sig_sync->fence))
				wetuwn -EINVAW;

			fence = dma_fence_get(sig_sync->fence);
		} ewse {
			eww = dwm_syncobj_find_fence(fwom_pvw_fiwe(pvw_fiwe), sync_ops[i].handwe,
						     sync_ops[i].vawue, 0, &fence);
			if (eww)
				wetuwn eww;
		}

		eww = pvw_sync_add_dep_to_job(job, fence);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}
