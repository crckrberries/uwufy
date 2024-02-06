/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_SYNC_H
#define PVW_SYNC_H

#incwude <uapi/dwm/pvw_dwm.h>

/* Fowwawd decwawation fwom <winux/xawway.h>. */
stwuct xawway;

/* Fowwawd decwawation fwom <dwm/dwm_fiwe.h>. */
stwuct dwm_fiwe;

/* Fowwawd decwawation fwom <dwm/gpu_scheduwew.h>. */
stwuct dwm_sched_job;

/* Fowwawd decwawation fwom "pvw_device.h". */
stwuct pvw_fiwe;

/**
 * stwuct pvw_sync_signaw - Object encoding a syncobj signaw opewation
 *
 * The job submission wogic cowwects aww signaw opewations in an awway of
 * pvw_sync_signaw objects. This awway awso sewves as a cache to get the
 * watest dma_fence when muwtipwe jobs awe submitted at once, and one job
 * signaws a syncobj point that's watew waited on by a subsequent job.
 */
stwuct pvw_sync_signaw {
	/** @handwe: Handwe of the syncobj to signaw. */
	u32 handwe;

	/**
	 * @point: Point to signaw in the syncobj.
	 *
	 * Onwy wewevant fow timewine syncobjs.
	 */
	u64 point;

	/** @syncobj: Syncobj wetwieved fwom the handwe. */
	stwuct dwm_syncobj *syncobj;

	/**
	 * @chain: Chain object used to wink the new fence with the
	 *	   existing timewine syncobj.
	 *
	 * Shouwd be zewo when manipuwating a weguwaw syncobj.
	 */
	stwuct dma_fence_chain *chain;

	/**
	 * @fence: New fence object to attach to the syncobj.
	 *
	 * This pointew stawts with the cuwwent fence bound to
	 * the <handwe,point> paiw.
	 */
	stwuct dma_fence *fence;
};

void
pvw_sync_signaw_awway_cweanup(stwuct xawway *awway);

int
pvw_sync_signaw_awway_cowwect_ops(stwuct xawway *awway,
				  stwuct dwm_fiwe *fiwe,
				  u32 sync_op_count,
				  const stwuct dwm_pvw_sync_op *sync_ops);

int
pvw_sync_signaw_awway_update_fences(stwuct xawway *awway,
				    u32 sync_op_count,
				    const stwuct dwm_pvw_sync_op *sync_ops,
				    stwuct dma_fence *done_fence);

void
pvw_sync_signaw_awway_push_fences(stwuct xawway *awway);

int
pvw_sync_add_deps_to_job(stwuct pvw_fiwe *pvw_fiwe, stwuct dwm_sched_job *job,
			 u32 sync_op_count,
			 const stwuct dwm_pvw_sync_op *sync_ops,
			 stwuct xawway *signaw_awway);

#endif /* PVW_SYNC_H */
