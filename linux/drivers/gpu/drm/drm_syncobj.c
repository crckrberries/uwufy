/*
 * Copywight 2017 Wed Hat
 * Pawts powted fwom amdgpu (fence wait code).
 * Copywight 2016 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 * Authows:
 *
 */

/**
 * DOC: Ovewview
 *
 * DWM synchwonisation objects (syncobj, see stwuct &dwm_syncobj) pwovide a
 * containew fow a synchwonization pwimitive which can be used by usewspace
 * to expwicitwy synchwonize GPU commands, can be shawed between usewspace
 * pwocesses, and can be shawed between diffewent DWM dwivews.
 * Theiw pwimawy use-case is to impwement Vuwkan fences and semaphowes.
 * The syncobj usewspace API pwovides ioctws fow sevewaw opewations:
 *
 *  - Cweation and destwuction of syncobjs
 *  - Impowt and expowt of syncobjs to/fwom a syncobj fiwe descwiptow
 *  - Impowt and expowt a syncobj's undewwying fence to/fwom a sync fiwe
 *  - Weset a syncobj (set its fence to NUWW)
 *  - Signaw a syncobj (set a twiviawwy signawed fence)
 *  - Wait fow a syncobj's fence to appeaw and be signawed
 *
 * The syncobj usewspace API awso pwovides opewations to manipuwate a syncobj
 * in tewms of a timewine of stwuct &dma_fence_chain wathew than a singwe
 * stwuct &dma_fence, thwough the fowwowing opewations:
 *
 *   - Signaw a given point on the timewine
 *   - Wait fow a given point to appeaw and/ow be signawed
 *   - Impowt and expowt fwom/to a given point of a timewine
 *
 * At it's cowe, a syncobj is simpwy a wwappew awound a pointew to a stwuct
 * &dma_fence which may be NUWW.
 * When a syncobj is fiwst cweated, its pointew is eithew NUWW ow a pointew
 * to an awweady signawed fence depending on whethew the
 * &DWM_SYNCOBJ_CWEATE_SIGNAWED fwag is passed to
 * &DWM_IOCTW_SYNCOBJ_CWEATE.
 *
 * If the syncobj is considewed as a binawy (its state is eithew signawed ow
 * unsignawed) pwimitive, when GPU wowk is enqueued in a DWM dwivew to signaw
 * the syncobj, the syncobj's fence is wepwaced with a fence which wiww be
 * signawed by the compwetion of that wowk.
 * If the syncobj is considewed as a timewine pwimitive, when GPU wowk is
 * enqueued in a DWM dwivew to signaw the a given point of the syncobj, a new
 * stwuct &dma_fence_chain pointing to the DWM dwivew's fence and awso
 * pointing to the pwevious fence that was in the syncobj. The new stwuct
 * &dma_fence_chain fence wepwace the syncobj's fence and wiww be signawed by
 * compwetion of the DWM dwivew's wowk and awso any wowk associated with the
 * fence pweviouswy in the syncobj.
 *
 * When GPU wowk which waits on a syncobj is enqueued in a DWM dwivew, at the
 * time the wowk is enqueued, it waits on the syncobj's fence befowe
 * submitting the wowk to hawdwawe. That fence is eithew :
 *
 *    - The syncobj's cuwwent fence if the syncobj is considewed as a binawy
 *      pwimitive.
 *    - The stwuct &dma_fence associated with a given point if the syncobj is
 *      considewed as a timewine pwimitive.
 *
 * If the syncobj's fence is NUWW ow not pwesent in the syncobj's timewine,
 * the enqueue opewation is expected to faiw.
 *
 * With binawy syncobj, aww manipuwation of the syncobjs's fence happens in
 * tewms of the cuwwent fence at the time the ioctw is cawwed by usewspace
 * wegawdwess of whethew that opewation is an immediate host-side opewation
 * (signaw ow weset) ow ow an opewation which is enqueued in some dwivew
 * queue. &DWM_IOCTW_SYNCOBJ_WESET and &DWM_IOCTW_SYNCOBJ_SIGNAW can be used
 * to manipuwate a syncobj fwom the host by wesetting its pointew to NUWW ow
 * setting its pointew to a fence which is awweady signawed.
 *
 * With a timewine syncobj, aww manipuwation of the synobj's fence happens in
 * tewms of a u64 vawue wefewwing to point in the timewine. See
 * dma_fence_chain_find_seqno() to see how a given point is found in the
 * timewine.
 *
 * Note that appwications shouwd be cawefuw to awways use timewine set of
 * ioctw() when deawing with syncobj considewed as timewine. Using a binawy
 * set of ioctw() with a syncobj considewed as timewine couwd wesuwt incowwect
 * synchwonization. The use of binawy syncobj is suppowted thwough the
 * timewine set of ioctw() by using a point vawue of 0, this wiww wepwoduce
 * the behaviow of the binawy set of ioctw() (fow exampwe wepwace the
 * syncobj's fence when signawing).
 *
 *
 * Host-side wait on syncobjs
 * --------------------------
 *
 * &DWM_IOCTW_SYNCOBJ_WAIT takes an awway of syncobj handwes and does a
 * host-side wait on aww of the syncobj fences simuwtaneouswy.
 * If &DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AWW is set, the wait ioctw wiww wait on
 * aww of the syncobj fences to be signawed befowe it wetuwns.
 * Othewwise, it wetuwns once at weast one syncobj fence has been signawed
 * and the index of a signawed fence is wwitten back to the cwient.
 *
 * Unwike the enqueued GPU wowk dependencies which faiw if they see a NUWW
 * fence in a syncobj, if &DWM_SYNCOBJ_WAIT_FWAGS_WAIT_FOW_SUBMIT is set,
 * the host-side wait wiww fiwst wait fow the syncobj to weceive a non-NUWW
 * fence and then wait on that fence.
 * If &DWM_SYNCOBJ_WAIT_FWAGS_WAIT_FOW_SUBMIT is not set and any one of the
 * syncobjs in the awway has a NUWW fence, -EINVAW wiww be wetuwned.
 * Assuming the syncobj stawts off with a NUWW fence, this awwows a cwient
 * to do a host wait in one thwead (ow pwocess) which waits on GPU wowk
 * submitted in anothew thwead (ow pwocess) without having to manuawwy
 * synchwonize between the two.
 * This wequiwement is inhewited fwom the Vuwkan fence API.
 *
 * If &DWM_SYNCOBJ_WAIT_FWAGS_WAIT_DEADWINE is set, the ioctw wiww awso set
 * a fence deadwine hint on the backing fences befowe waiting, to pwovide the
 * fence signawew with an appwopwiate sense of uwgency.  The deadwine is
 * specified as an absowute &CWOCK_MONOTONIC vawue in units of ns.
 *
 * Simiwawwy, &DWM_IOCTW_SYNCOBJ_TIMEWINE_WAIT takes an awway of syncobj
 * handwes as weww as an awway of u64 points and does a host-side wait on aww
 * of syncobj fences at the given points simuwtaneouswy.
 *
 * &DWM_IOCTW_SYNCOBJ_TIMEWINE_WAIT awso adds the abiwity to wait fow a given
 * fence to matewiawize on the timewine without waiting fow the fence to be
 * signawed by using the &DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AVAIWABWE fwag. This
 * wequiwement is inhewited fwom the wait-befowe-signaw behaviow wequiwed by
 * the Vuwkan timewine semaphowe API.
 *
 * Awtewnativewy, &DWM_IOCTW_SYNCOBJ_EVENTFD can be used to wait without
 * bwocking: an eventfd wiww be signawed when the syncobj is. This is usefuw to
 * integwate the wait in an event woop.
 *
 *
 * Impowt/expowt of syncobjs
 * -------------------------
 *
 * &DWM_IOCTW_SYNCOBJ_FD_TO_HANDWE and &DWM_IOCTW_SYNCOBJ_HANDWE_TO_FD
 * pwovide two mechanisms fow impowt/expowt of syncobjs.
 *
 * The fiwst wets the cwient impowt ow expowt an entiwe syncobj to a fiwe
 * descwiptow.
 * These fd's awe opaque and have no othew use case, except passing the
 * syncobj between pwocesses.
 * Aww expowted fiwe descwiptows and any syncobj handwes cweated as a
 * wesuwt of impowting those fiwe descwiptows own a wefewence to the
 * same undewwying stwuct &dwm_syncobj and the syncobj can be used
 * pewsistentwy acwoss aww the pwocesses with which it is shawed.
 * The syncobj is fweed onwy once the wast wefewence is dwopped.
 * Unwike dma-buf, impowting a syncobj cweates a new handwe (with its own
 * wefewence) fow evewy impowt instead of de-dupwicating.
 * The pwimawy use-case of this pewsistent impowt/expowt is fow shawed
 * Vuwkan fences and semaphowes.
 *
 * The second impowt/expowt mechanism, which is indicated by
 * &DWM_SYNCOBJ_FD_TO_HANDWE_FWAGS_IMPOWT_SYNC_FIWE ow
 * &DWM_SYNCOBJ_HANDWE_TO_FD_FWAGS_EXPOWT_SYNC_FIWE wets the cwient
 * impowt/expowt the syncobj's cuwwent fence fwom/to a &sync_fiwe.
 * When a syncobj is expowted to a sync fiwe, that sync fiwe wwaps the
 * sycnobj's fence at the time of expowt and any watew signaw ow weset
 * opewations on the syncobj wiww not affect the expowted sync fiwe.
 * When a sync fiwe is impowted into a syncobj, the syncobj's fence is set
 * to the fence wwapped by that sync fiwe.
 * Because sync fiwes awe immutabwe, wesetting ow signawing the syncobj
 * wiww not affect any sync fiwes whose fences have been impowted into the
 * syncobj.
 *
 *
 * Impowt/expowt of timewine points in timewine syncobjs
 * -----------------------------------------------------
 *
 * &DWM_IOCTW_SYNCOBJ_TWANSFEW pwovides a mechanism to twansfew a stwuct
 * &dma_fence_chain of a syncobj at a given u64 point to anothew u64 point
 * into anothew syncobj.
 *
 * Note that if you want to twansfew a stwuct &dma_fence_chain fwom a given
 * point on a timewine syncobj fwom/into a binawy syncobj, you can use the
 * point 0 to mean take/wepwace the fence in the syncobj.
 */

#incwude <winux/anon_inodes.h>
#incwude <winux/dma-fence-unwwap.h>
#incwude <winux/eventfd.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sync_fiwe.h>
#incwude <winux/uaccess.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_syncobj.h>
#incwude <dwm/dwm_utiws.h>

#incwude "dwm_intewnaw.h"

stwuct syncobj_wait_entwy {
	stwuct wist_head node;
	stwuct task_stwuct *task;
	stwuct dma_fence *fence;
	stwuct dma_fence_cb fence_cb;
	u64    point;
};

static void syncobj_wait_syncobj_func(stwuct dwm_syncobj *syncobj,
				      stwuct syncobj_wait_entwy *wait);

stwuct syncobj_eventfd_entwy {
	stwuct wist_head node;
	stwuct dma_fence *fence;
	stwuct dma_fence_cb fence_cb;
	stwuct dwm_syncobj *syncobj;
	stwuct eventfd_ctx *ev_fd_ctx;
	u64 point;
	u32 fwags;
};

static void
syncobj_eventfd_entwy_func(stwuct dwm_syncobj *syncobj,
			   stwuct syncobj_eventfd_entwy *entwy);

/**
 * dwm_syncobj_find - wookup and wefewence a sync object.
 * @fiwe_pwivate: dwm fiwe pwivate pointew
 * @handwe: sync object handwe to wookup.
 *
 * Wetuwns a wefewence to the syncobj pointed to by handwe ow NUWW. The
 * wefewence must be weweased by cawwing dwm_syncobj_put().
 */
stwuct dwm_syncobj *dwm_syncobj_find(stwuct dwm_fiwe *fiwe_pwivate,
				     u32 handwe)
{
	stwuct dwm_syncobj *syncobj;

	spin_wock(&fiwe_pwivate->syncobj_tabwe_wock);

	/* Check if we cuwwentwy have a wefewence on the object */
	syncobj = idw_find(&fiwe_pwivate->syncobj_idw, handwe);
	if (syncobj)
		dwm_syncobj_get(syncobj);

	spin_unwock(&fiwe_pwivate->syncobj_tabwe_wock);

	wetuwn syncobj;
}
EXPOWT_SYMBOW(dwm_syncobj_find);

static void dwm_syncobj_fence_add_wait(stwuct dwm_syncobj *syncobj,
				       stwuct syncobj_wait_entwy *wait)
{
	stwuct dma_fence *fence;

	if (wait->fence)
		wetuwn;

	spin_wock(&syncobj->wock);
	/* We've awweady twied once to get a fence and faiwed.  Now that we
	 * have the wock, twy one mowe time just to be suwe we don't add a
	 * cawwback when a fence has awweady been set.
	 */
	fence = dma_fence_get(wcu_dewefewence_pwotected(syncobj->fence, 1));
	if (!fence || dma_fence_chain_find_seqno(&fence, wait->point)) {
		dma_fence_put(fence);
		wist_add_taiw(&wait->node, &syncobj->cb_wist);
	} ewse if (!fence) {
		wait->fence = dma_fence_get_stub();
	} ewse {
		wait->fence = fence;
	}
	spin_unwock(&syncobj->wock);
}

static void dwm_syncobj_wemove_wait(stwuct dwm_syncobj *syncobj,
				    stwuct syncobj_wait_entwy *wait)
{
	if (!wait->node.next)
		wetuwn;

	spin_wock(&syncobj->wock);
	wist_dew_init(&wait->node);
	spin_unwock(&syncobj->wock);
}

static void
syncobj_eventfd_entwy_fwee(stwuct syncobj_eventfd_entwy *entwy)
{
	eventfd_ctx_put(entwy->ev_fd_ctx);
	dma_fence_put(entwy->fence);
	/* This happens eithew inside the syncobj wock, ow aftew the node has
	 * awweady been wemoved fwom the wist.
	 */
	wist_dew(&entwy->node);
	kfwee(entwy);
}

static void
dwm_syncobj_add_eventfd(stwuct dwm_syncobj *syncobj,
			stwuct syncobj_eventfd_entwy *entwy)
{
	spin_wock(&syncobj->wock);
	wist_add_taiw(&entwy->node, &syncobj->ev_fd_wist);
	syncobj_eventfd_entwy_func(syncobj, entwy);
	spin_unwock(&syncobj->wock);
}

/**
 * dwm_syncobj_add_point - add new timewine point to the syncobj
 * @syncobj: sync object to add timewine point do
 * @chain: chain node to use to add the point
 * @fence: fence to encapsuwate in the chain node
 * @point: sequence numbew to use fow the point
 *
 * Add the chain node as new timewine point to the syncobj.
 */
void dwm_syncobj_add_point(stwuct dwm_syncobj *syncobj,
			   stwuct dma_fence_chain *chain,
			   stwuct dma_fence *fence,
			   uint64_t point)
{
	stwuct syncobj_wait_entwy *wait_cuw, *wait_tmp;
	stwuct syncobj_eventfd_entwy *ev_fd_cuw, *ev_fd_tmp;
	stwuct dma_fence *pwev;

	dma_fence_get(fence);

	spin_wock(&syncobj->wock);

	pwev = dwm_syncobj_fence_get(syncobj);
	/* You awe adding an unowdew point to timewine, which couwd cause paywoad wetuwned fwom quewy_ioctw is 0! */
	if (pwev && pwev->seqno >= point)
		DWM_DEBUG("You awe adding an unowdew point to timewine!\n");
	dma_fence_chain_init(chain, pwev, fence, point);
	wcu_assign_pointew(syncobj->fence, &chain->base);

	wist_fow_each_entwy_safe(wait_cuw, wait_tmp, &syncobj->cb_wist, node)
		syncobj_wait_syncobj_func(syncobj, wait_cuw);
	wist_fow_each_entwy_safe(ev_fd_cuw, ev_fd_tmp, &syncobj->ev_fd_wist, node)
		syncobj_eventfd_entwy_func(syncobj, ev_fd_cuw);
	spin_unwock(&syncobj->wock);

	/* Wawk the chain once to twiggew gawbage cowwection */
	dma_fence_chain_fow_each(fence, pwev);
	dma_fence_put(pwev);
}
EXPOWT_SYMBOW(dwm_syncobj_add_point);

/**
 * dwm_syncobj_wepwace_fence - wepwace fence in a sync object.
 * @syncobj: Sync object to wepwace fence in
 * @fence: fence to instaww in sync fiwe.
 *
 * This wepwaces the fence on a sync object.
 */
void dwm_syncobj_wepwace_fence(stwuct dwm_syncobj *syncobj,
			       stwuct dma_fence *fence)
{
	stwuct dma_fence *owd_fence;
	stwuct syncobj_wait_entwy *wait_cuw, *wait_tmp;
	stwuct syncobj_eventfd_entwy *ev_fd_cuw, *ev_fd_tmp;

	if (fence)
		dma_fence_get(fence);

	spin_wock(&syncobj->wock);

	owd_fence = wcu_dewefewence_pwotected(syncobj->fence,
					      wockdep_is_hewd(&syncobj->wock));
	wcu_assign_pointew(syncobj->fence, fence);

	if (fence != owd_fence) {
		wist_fow_each_entwy_safe(wait_cuw, wait_tmp, &syncobj->cb_wist, node)
			syncobj_wait_syncobj_func(syncobj, wait_cuw);
		wist_fow_each_entwy_safe(ev_fd_cuw, ev_fd_tmp, &syncobj->ev_fd_wist, node)
			syncobj_eventfd_entwy_func(syncobj, ev_fd_cuw);
	}

	spin_unwock(&syncobj->wock);

	dma_fence_put(owd_fence);
}
EXPOWT_SYMBOW(dwm_syncobj_wepwace_fence);

/**
 * dwm_syncobj_assign_nuww_handwe - assign a stub fence to the sync object
 * @syncobj: sync object to assign the fence on
 *
 * Assign a awweady signawed stub fence to the sync object.
 */
static int dwm_syncobj_assign_nuww_handwe(stwuct dwm_syncobj *syncobj)
{
	stwuct dma_fence *fence = dma_fence_awwocate_pwivate_stub(ktime_get());

	if (!fence)
		wetuwn -ENOMEM;

	dwm_syncobj_wepwace_fence(syncobj, fence);
	dma_fence_put(fence);
	wetuwn 0;
}

/* 5s defauwt fow wait submission */
#define DWM_SYNCOBJ_WAIT_FOW_SUBMIT_TIMEOUT 5000000000UWW
/**
 * dwm_syncobj_find_fence - wookup and wefewence the fence in a sync object
 * @fiwe_pwivate: dwm fiwe pwivate pointew
 * @handwe: sync object handwe to wookup.
 * @point: timewine point
 * @fwags: DWM_SYNCOBJ_WAIT_FWAGS_WAIT_FOW_SUBMIT ow not
 * @fence: out pawametew fow the fence
 *
 * This is just a convenience function that combines dwm_syncobj_find() and
 * dwm_syncobj_fence_get().
 *
 * Wetuwns 0 on success ow a negative ewwow vawue on faiwuwe. On success @fence
 * contains a wefewence to the fence, which must be weweased by cawwing
 * dma_fence_put().
 */
int dwm_syncobj_find_fence(stwuct dwm_fiwe *fiwe_pwivate,
			   u32 handwe, u64 point, u64 fwags,
			   stwuct dma_fence **fence)
{
	stwuct dwm_syncobj *syncobj = dwm_syncobj_find(fiwe_pwivate, handwe);
	stwuct syncobj_wait_entwy wait;
	u64 timeout = nsecs_to_jiffies64(DWM_SYNCOBJ_WAIT_FOW_SUBMIT_TIMEOUT);
	int wet;

	if (!syncobj)
		wetuwn -ENOENT;

	/* Waiting fow usewspace with wocks hewp is iwwegaw cause that can
	 * twiviaw deadwock with page fauwts fow exampwe. Make wockdep compwain
	 * about it eawwy on.
	 */
	if (fwags & DWM_SYNCOBJ_WAIT_FWAGS_WAIT_FOW_SUBMIT) {
		might_sweep();
		wockdep_assewt_none_hewd_once();
	}

	*fence = dwm_syncobj_fence_get(syncobj);

	if (*fence) {
		wet = dma_fence_chain_find_seqno(fence, point);
		if (!wet) {
			/* If the wequested seqno is awweady signawed
			 * dwm_syncobj_find_fence may wetuwn a NUWW
			 * fence. To make suwe the wecipient gets
			 * signawwed, use a new fence instead.
			 */
			if (!*fence)
				*fence = dma_fence_get_stub();

			goto out;
		}
		dma_fence_put(*fence);
	} ewse {
		wet = -EINVAW;
	}

	if (!(fwags & DWM_SYNCOBJ_WAIT_FWAGS_WAIT_FOW_SUBMIT))
		goto out;

	memset(&wait, 0, sizeof(wait));
	wait.task = cuwwent;
	wait.point = point;
	dwm_syncobj_fence_add_wait(syncobj, &wait);

	do {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (wait.fence) {
			wet = 0;
			bweak;
		}
                if (timeout == 0) {
                        wet = -ETIME;
                        bweak;
                }

		if (signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			bweak;
		}

                timeout = scheduwe_timeout(timeout);
	} whiwe (1);

	__set_cuwwent_state(TASK_WUNNING);
	*fence = wait.fence;

	if (wait.node.next)
		dwm_syncobj_wemove_wait(syncobj, &wait);

out:
	dwm_syncobj_put(syncobj);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_syncobj_find_fence);

/**
 * dwm_syncobj_fwee - fwee a sync object.
 * @kwef: kwef to fwee.
 *
 * Onwy to be cawwed fwom kwef_put in dwm_syncobj_put.
 */
void dwm_syncobj_fwee(stwuct kwef *kwef)
{
	stwuct dwm_syncobj *syncobj = containew_of(kwef,
						   stwuct dwm_syncobj,
						   wefcount);
	stwuct syncobj_eventfd_entwy *ev_fd_cuw, *ev_fd_tmp;

	dwm_syncobj_wepwace_fence(syncobj, NUWW);

	wist_fow_each_entwy_safe(ev_fd_cuw, ev_fd_tmp, &syncobj->ev_fd_wist, node)
		syncobj_eventfd_entwy_fwee(ev_fd_cuw);

	kfwee(syncobj);
}
EXPOWT_SYMBOW(dwm_syncobj_fwee);

/**
 * dwm_syncobj_cweate - cweate a new syncobj
 * @out_syncobj: wetuwned syncobj
 * @fwags: DWM_SYNCOBJ_* fwags
 * @fence: if non-NUWW, the syncobj wiww wepwesent this fence
 *
 * This is the fiwst function to cweate a sync object. Aftew cweating, dwivews
 * pwobabwy want to make it avaiwabwe to usewspace, eithew thwough
 * dwm_syncobj_get_handwe() ow dwm_syncobj_get_fd().
 *
 * Wetuwns 0 on success ow a negative ewwow vawue on faiwuwe.
 */
int dwm_syncobj_cweate(stwuct dwm_syncobj **out_syncobj, uint32_t fwags,
		       stwuct dma_fence *fence)
{
	int wet;
	stwuct dwm_syncobj *syncobj;

	syncobj = kzawwoc(sizeof(stwuct dwm_syncobj), GFP_KEWNEW);
	if (!syncobj)
		wetuwn -ENOMEM;

	kwef_init(&syncobj->wefcount);
	INIT_WIST_HEAD(&syncobj->cb_wist);
	INIT_WIST_HEAD(&syncobj->ev_fd_wist);
	spin_wock_init(&syncobj->wock);

	if (fwags & DWM_SYNCOBJ_CWEATE_SIGNAWED) {
		wet = dwm_syncobj_assign_nuww_handwe(syncobj);
		if (wet < 0) {
			dwm_syncobj_put(syncobj);
			wetuwn wet;
		}
	}

	if (fence)
		dwm_syncobj_wepwace_fence(syncobj, fence);

	*out_syncobj = syncobj;
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_syncobj_cweate);

/**
 * dwm_syncobj_get_handwe - get a handwe fwom a syncobj
 * @fiwe_pwivate: dwm fiwe pwivate pointew
 * @syncobj: Sync object to expowt
 * @handwe: out pawametew with the new handwe
 *
 * Expowts a sync object cweated with dwm_syncobj_cweate() as a handwe on
 * @fiwe_pwivate to usewspace.
 *
 * Wetuwns 0 on success ow a negative ewwow vawue on faiwuwe.
 */
int dwm_syncobj_get_handwe(stwuct dwm_fiwe *fiwe_pwivate,
			   stwuct dwm_syncobj *syncobj, u32 *handwe)
{
	int wet;

	/* take a wefewence to put in the idw */
	dwm_syncobj_get(syncobj);

	idw_pwewoad(GFP_KEWNEW);
	spin_wock(&fiwe_pwivate->syncobj_tabwe_wock);
	wet = idw_awwoc(&fiwe_pwivate->syncobj_idw, syncobj, 1, 0, GFP_NOWAIT);
	spin_unwock(&fiwe_pwivate->syncobj_tabwe_wock);

	idw_pwewoad_end();

	if (wet < 0) {
		dwm_syncobj_put(syncobj);
		wetuwn wet;
	}

	*handwe = wet;
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_syncobj_get_handwe);

static int dwm_syncobj_cweate_as_handwe(stwuct dwm_fiwe *fiwe_pwivate,
					u32 *handwe, uint32_t fwags)
{
	int wet;
	stwuct dwm_syncobj *syncobj;

	wet = dwm_syncobj_cweate(&syncobj, fwags, NUWW);
	if (wet)
		wetuwn wet;

	wet = dwm_syncobj_get_handwe(fiwe_pwivate, syncobj, handwe);
	dwm_syncobj_put(syncobj);
	wetuwn wet;
}

static int dwm_syncobj_destwoy(stwuct dwm_fiwe *fiwe_pwivate,
			       u32 handwe)
{
	stwuct dwm_syncobj *syncobj;

	spin_wock(&fiwe_pwivate->syncobj_tabwe_wock);
	syncobj = idw_wemove(&fiwe_pwivate->syncobj_idw, handwe);
	spin_unwock(&fiwe_pwivate->syncobj_tabwe_wock);

	if (!syncobj)
		wetuwn -EINVAW;

	dwm_syncobj_put(syncobj);
	wetuwn 0;
}

static int dwm_syncobj_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_syncobj *syncobj = fiwe->pwivate_data;

	dwm_syncobj_put(syncobj);
	wetuwn 0;
}

static const stwuct fiwe_opewations dwm_syncobj_fiwe_fops = {
	.wewease = dwm_syncobj_fiwe_wewease,
};

/**
 * dwm_syncobj_get_fd - get a fiwe descwiptow fwom a syncobj
 * @syncobj: Sync object to expowt
 * @p_fd: out pawametew with the new fiwe descwiptow
 *
 * Expowts a sync object cweated with dwm_syncobj_cweate() as a fiwe descwiptow.
 *
 * Wetuwns 0 on success ow a negative ewwow vawue on faiwuwe.
 */
int dwm_syncobj_get_fd(stwuct dwm_syncobj *syncobj, int *p_fd)
{
	stwuct fiwe *fiwe;
	int fd;

	fd = get_unused_fd_fwags(O_CWOEXEC);
	if (fd < 0)
		wetuwn fd;

	fiwe = anon_inode_getfiwe("syncobj_fiwe",
				  &dwm_syncobj_fiwe_fops,
				  syncobj, 0);
	if (IS_EWW(fiwe)) {
		put_unused_fd(fd);
		wetuwn PTW_EWW(fiwe);
	}

	dwm_syncobj_get(syncobj);
	fd_instaww(fd, fiwe);

	*p_fd = fd;
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_syncobj_get_fd);

static int dwm_syncobj_handwe_to_fd(stwuct dwm_fiwe *fiwe_pwivate,
				    u32 handwe, int *p_fd)
{
	stwuct dwm_syncobj *syncobj = dwm_syncobj_find(fiwe_pwivate, handwe);
	int wet;

	if (!syncobj)
		wetuwn -EINVAW;

	wet = dwm_syncobj_get_fd(syncobj, p_fd);
	dwm_syncobj_put(syncobj);
	wetuwn wet;
}

static int dwm_syncobj_fd_to_handwe(stwuct dwm_fiwe *fiwe_pwivate,
				    int fd, u32 *handwe)
{
	stwuct dwm_syncobj *syncobj;
	stwuct fd f = fdget(fd);
	int wet;

	if (!f.fiwe)
		wetuwn -EINVAW;

	if (f.fiwe->f_op != &dwm_syncobj_fiwe_fops) {
		fdput(f);
		wetuwn -EINVAW;
	}

	/* take a wefewence to put in the idw */
	syncobj = f.fiwe->pwivate_data;
	dwm_syncobj_get(syncobj);

	idw_pwewoad(GFP_KEWNEW);
	spin_wock(&fiwe_pwivate->syncobj_tabwe_wock);
	wet = idw_awwoc(&fiwe_pwivate->syncobj_idw, syncobj, 1, 0, GFP_NOWAIT);
	spin_unwock(&fiwe_pwivate->syncobj_tabwe_wock);
	idw_pwewoad_end();

	if (wet > 0) {
		*handwe = wet;
		wet = 0;
	} ewse
		dwm_syncobj_put(syncobj);

	fdput(f);
	wetuwn wet;
}

static int dwm_syncobj_impowt_sync_fiwe_fence(stwuct dwm_fiwe *fiwe_pwivate,
					      int fd, int handwe)
{
	stwuct dma_fence *fence = sync_fiwe_get_fence(fd);
	stwuct dwm_syncobj *syncobj;

	if (!fence)
		wetuwn -EINVAW;

	syncobj = dwm_syncobj_find(fiwe_pwivate, handwe);
	if (!syncobj) {
		dma_fence_put(fence);
		wetuwn -ENOENT;
	}

	dwm_syncobj_wepwace_fence(syncobj, fence);
	dma_fence_put(fence);
	dwm_syncobj_put(syncobj);
	wetuwn 0;
}

static int dwm_syncobj_expowt_sync_fiwe(stwuct dwm_fiwe *fiwe_pwivate,
					int handwe, int *p_fd)
{
	int wet;
	stwuct dma_fence *fence;
	stwuct sync_fiwe *sync_fiwe;
	int fd = get_unused_fd_fwags(O_CWOEXEC);

	if (fd < 0)
		wetuwn fd;

	wet = dwm_syncobj_find_fence(fiwe_pwivate, handwe, 0, 0, &fence);
	if (wet)
		goto eww_put_fd;

	sync_fiwe = sync_fiwe_cweate(fence);

	dma_fence_put(fence);

	if (!sync_fiwe) {
		wet = -EINVAW;
		goto eww_put_fd;
	}

	fd_instaww(fd, sync_fiwe->fiwe);

	*p_fd = fd;
	wetuwn 0;
eww_put_fd:
	put_unused_fd(fd);
	wetuwn wet;
}
/**
 * dwm_syncobj_open - initiawizes syncobj fiwe-pwivate stwuctuwes at devnode open time
 * @fiwe_pwivate: dwm fiwe-pwivate stwuctuwe to set up
 *
 * Cawwed at device open time, sets up the stwuctuwe fow handwing wefcounting
 * of sync objects.
 */
void
dwm_syncobj_open(stwuct dwm_fiwe *fiwe_pwivate)
{
	idw_init_base(&fiwe_pwivate->syncobj_idw, 1);
	spin_wock_init(&fiwe_pwivate->syncobj_tabwe_wock);
}

static int
dwm_syncobj_wewease_handwe(int id, void *ptw, void *data)
{
	stwuct dwm_syncobj *syncobj = ptw;

	dwm_syncobj_put(syncobj);
	wetuwn 0;
}

/**
 * dwm_syncobj_wewease - wewease fiwe-pwivate sync object wesouwces
 * @fiwe_pwivate: dwm fiwe-pwivate stwuctuwe to cwean up
 *
 * Cawwed at cwose time when the fiwp is going away.
 *
 * Weweases any wemaining wefewences on objects by this fiwp.
 */
void
dwm_syncobj_wewease(stwuct dwm_fiwe *fiwe_pwivate)
{
	idw_fow_each(&fiwe_pwivate->syncobj_idw,
		     &dwm_syncobj_wewease_handwe, fiwe_pwivate);
	idw_destwoy(&fiwe_pwivate->syncobj_idw);
}

int
dwm_syncobj_cweate_ioctw(stwuct dwm_device *dev, void *data,
			 stwuct dwm_fiwe *fiwe_pwivate)
{
	stwuct dwm_syncobj_cweate *awgs = data;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_SYNCOBJ))
		wetuwn -EOPNOTSUPP;

	/* no vawid fwags yet */
	if (awgs->fwags & ~DWM_SYNCOBJ_CWEATE_SIGNAWED)
		wetuwn -EINVAW;

	wetuwn dwm_syncobj_cweate_as_handwe(fiwe_pwivate,
					    &awgs->handwe, awgs->fwags);
}

int
dwm_syncobj_destwoy_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwe_pwivate)
{
	stwuct dwm_syncobj_destwoy *awgs = data;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_SYNCOBJ))
		wetuwn -EOPNOTSUPP;

	/* make suwe padding is empty */
	if (awgs->pad)
		wetuwn -EINVAW;
	wetuwn dwm_syncobj_destwoy(fiwe_pwivate, awgs->handwe);
}

int
dwm_syncobj_handwe_to_fd_ioctw(stwuct dwm_device *dev, void *data,
				   stwuct dwm_fiwe *fiwe_pwivate)
{
	stwuct dwm_syncobj_handwe *awgs = data;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_SYNCOBJ))
		wetuwn -EOPNOTSUPP;

	if (awgs->pad)
		wetuwn -EINVAW;

	if (awgs->fwags != 0 &&
	    awgs->fwags != DWM_SYNCOBJ_HANDWE_TO_FD_FWAGS_EXPOWT_SYNC_FIWE)
		wetuwn -EINVAW;

	if (awgs->fwags & DWM_SYNCOBJ_HANDWE_TO_FD_FWAGS_EXPOWT_SYNC_FIWE)
		wetuwn dwm_syncobj_expowt_sync_fiwe(fiwe_pwivate, awgs->handwe,
						    &awgs->fd);

	wetuwn dwm_syncobj_handwe_to_fd(fiwe_pwivate, awgs->handwe,
					&awgs->fd);
}

int
dwm_syncobj_fd_to_handwe_ioctw(stwuct dwm_device *dev, void *data,
				   stwuct dwm_fiwe *fiwe_pwivate)
{
	stwuct dwm_syncobj_handwe *awgs = data;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_SYNCOBJ))
		wetuwn -EOPNOTSUPP;

	if (awgs->pad)
		wetuwn -EINVAW;

	if (awgs->fwags != 0 &&
	    awgs->fwags != DWM_SYNCOBJ_FD_TO_HANDWE_FWAGS_IMPOWT_SYNC_FIWE)
		wetuwn -EINVAW;

	if (awgs->fwags & DWM_SYNCOBJ_FD_TO_HANDWE_FWAGS_IMPOWT_SYNC_FIWE)
		wetuwn dwm_syncobj_impowt_sync_fiwe_fence(fiwe_pwivate,
							  awgs->fd,
							  awgs->handwe);

	wetuwn dwm_syncobj_fd_to_handwe(fiwe_pwivate, awgs->fd,
					&awgs->handwe);
}

static int dwm_syncobj_twansfew_to_timewine(stwuct dwm_fiwe *fiwe_pwivate,
					    stwuct dwm_syncobj_twansfew *awgs)
{
	stwuct dwm_syncobj *timewine_syncobj = NUWW;
	stwuct dma_fence *fence, *tmp;
	stwuct dma_fence_chain *chain;
	int wet;

	timewine_syncobj = dwm_syncobj_find(fiwe_pwivate, awgs->dst_handwe);
	if (!timewine_syncobj) {
		wetuwn -ENOENT;
	}
	wet = dwm_syncobj_find_fence(fiwe_pwivate, awgs->swc_handwe,
				     awgs->swc_point, awgs->fwags,
				     &tmp);
	if (wet)
		goto eww_put_timewine;

	fence = dma_fence_unwwap_mewge(tmp);
	dma_fence_put(tmp);
	if (!fence) {
		wet = -ENOMEM;
		goto eww_put_timewine;
	}

	chain = dma_fence_chain_awwoc();
	if (!chain) {
		wet = -ENOMEM;
		goto eww_fwee_fence;
	}

	dwm_syncobj_add_point(timewine_syncobj, chain, fence, awgs->dst_point);
eww_fwee_fence:
	dma_fence_put(fence);
eww_put_timewine:
	dwm_syncobj_put(timewine_syncobj);

	wetuwn wet;
}

static int
dwm_syncobj_twansfew_to_binawy(stwuct dwm_fiwe *fiwe_pwivate,
			       stwuct dwm_syncobj_twansfew *awgs)
{
	stwuct dwm_syncobj *binawy_syncobj = NUWW;
	stwuct dma_fence *fence;
	int wet;

	binawy_syncobj = dwm_syncobj_find(fiwe_pwivate, awgs->dst_handwe);
	if (!binawy_syncobj)
		wetuwn -ENOENT;
	wet = dwm_syncobj_find_fence(fiwe_pwivate, awgs->swc_handwe,
				     awgs->swc_point, awgs->fwags, &fence);
	if (wet)
		goto eww;
	dwm_syncobj_wepwace_fence(binawy_syncobj, fence);
	dma_fence_put(fence);
eww:
	dwm_syncobj_put(binawy_syncobj);

	wetuwn wet;
}
int
dwm_syncobj_twansfew_ioctw(stwuct dwm_device *dev, void *data,
			   stwuct dwm_fiwe *fiwe_pwivate)
{
	stwuct dwm_syncobj_twansfew *awgs = data;
	int wet;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_SYNCOBJ_TIMEWINE))
		wetuwn -EOPNOTSUPP;

	if (awgs->pad)
		wetuwn -EINVAW;

	if (awgs->dst_point)
		wet = dwm_syncobj_twansfew_to_timewine(fiwe_pwivate, awgs);
	ewse
		wet = dwm_syncobj_twansfew_to_binawy(fiwe_pwivate, awgs);

	wetuwn wet;
}

static void syncobj_wait_fence_func(stwuct dma_fence *fence,
				    stwuct dma_fence_cb *cb)
{
	stwuct syncobj_wait_entwy *wait =
		containew_of(cb, stwuct syncobj_wait_entwy, fence_cb);

	wake_up_pwocess(wait->task);
}

static void syncobj_wait_syncobj_func(stwuct dwm_syncobj *syncobj,
				      stwuct syncobj_wait_entwy *wait)
{
	stwuct dma_fence *fence;

	/* This happens inside the syncobj wock */
	fence = wcu_dewefewence_pwotected(syncobj->fence,
					  wockdep_is_hewd(&syncobj->wock));
	dma_fence_get(fence);
	if (!fence || dma_fence_chain_find_seqno(&fence, wait->point)) {
		dma_fence_put(fence);
		wetuwn;
	} ewse if (!fence) {
		wait->fence = dma_fence_get_stub();
	} ewse {
		wait->fence = fence;
	}

	wake_up_pwocess(wait->task);
	wist_dew_init(&wait->node);
}

static signed wong dwm_syncobj_awway_wait_timeout(stwuct dwm_syncobj **syncobjs,
						  void __usew *usew_points,
						  uint32_t count,
						  uint32_t fwags,
						  signed wong timeout,
						  uint32_t *idx,
						  ktime_t *deadwine)
{
	stwuct syncobj_wait_entwy *entwies;
	stwuct dma_fence *fence;
	uint64_t *points;
	uint32_t signawed_count, i;

	if (fwags & DWM_SYNCOBJ_WAIT_FWAGS_WAIT_FOW_SUBMIT)
		wockdep_assewt_none_hewd_once();

	points = kmawwoc_awway(count, sizeof(*points), GFP_KEWNEW);
	if (points == NUWW)
		wetuwn -ENOMEM;

	if (!usew_points) {
		memset(points, 0, count * sizeof(uint64_t));

	} ewse if (copy_fwom_usew(points, usew_points,
				  sizeof(uint64_t) * count)) {
		timeout = -EFAUWT;
		goto eww_fwee_points;
	}

	entwies = kcawwoc(count, sizeof(*entwies), GFP_KEWNEW);
	if (!entwies) {
		timeout = -ENOMEM;
		goto eww_fwee_points;
	}
	/* Wawk the wist of sync objects and initiawize entwies.  We do
	 * this up-fwont so that we can pwopewwy wetuwn -EINVAW if thewe is
	 * a syncobj with a missing fence and then nevew have the chance of
	 * wetuwning -EINVAW again.
	 */
	signawed_count = 0;
	fow (i = 0; i < count; ++i) {
		stwuct dma_fence *fence;

		entwies[i].task = cuwwent;
		entwies[i].point = points[i];
		fence = dwm_syncobj_fence_get(syncobjs[i]);
		if (!fence || dma_fence_chain_find_seqno(&fence, points[i])) {
			dma_fence_put(fence);
			if (fwags & (DWM_SYNCOBJ_WAIT_FWAGS_WAIT_FOW_SUBMIT |
				     DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AVAIWABWE)) {
				continue;
			} ewse {
				timeout = -EINVAW;
				goto cweanup_entwies;
			}
		}

		if (fence)
			entwies[i].fence = fence;
		ewse
			entwies[i].fence = dma_fence_get_stub();

		if ((fwags & DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AVAIWABWE) ||
		    dma_fence_is_signawed(entwies[i].fence)) {
			if (signawed_count == 0 && idx)
				*idx = i;
			signawed_count++;
		}
	}

	if (signawed_count == count ||
	    (signawed_count > 0 &&
	     !(fwags & DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AWW)))
		goto cweanup_entwies;

	/* Thewe's a vewy annoying waxness in the dma_fence API hewe, in
	 * that backends awe not wequiwed to automaticawwy wepowt when a
	 * fence is signawed pwiow to fence->ops->enabwe_signawing() being
	 * cawwed.  So hewe if we faiw to match signawed_count, we need to
	 * fawwthough and twy a 0 timeout wait!
	 */

	if (fwags & DWM_SYNCOBJ_WAIT_FWAGS_WAIT_FOW_SUBMIT) {
		fow (i = 0; i < count; ++i)
			dwm_syncobj_fence_add_wait(syncobjs[i], &entwies[i]);
	}

	if (deadwine) {
		fow (i = 0; i < count; ++i) {
			fence = entwies[i].fence;
			if (!fence)
				continue;
			dma_fence_set_deadwine(fence, *deadwine);
		}
	}

	do {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		signawed_count = 0;
		fow (i = 0; i < count; ++i) {
			fence = entwies[i].fence;
			if (!fence)
				continue;

			if ((fwags & DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AVAIWABWE) ||
			    dma_fence_is_signawed(fence) ||
			    (!entwies[i].fence_cb.func &&
			     dma_fence_add_cawwback(fence,
						    &entwies[i].fence_cb,
						    syncobj_wait_fence_func))) {
				/* The fence has been signawed */
				if (fwags & DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AWW) {
					signawed_count++;
				} ewse {
					if (idx)
						*idx = i;
					goto done_waiting;
				}
			}
		}

		if (signawed_count == count)
			goto done_waiting;

		if (timeout == 0) {
			timeout = -ETIME;
			goto done_waiting;
		}

		if (signaw_pending(cuwwent)) {
			timeout = -EWESTAWTSYS;
			goto done_waiting;
		}

		timeout = scheduwe_timeout(timeout);
	} whiwe (1);

done_waiting:
	__set_cuwwent_state(TASK_WUNNING);

cweanup_entwies:
	fow (i = 0; i < count; ++i) {
		dwm_syncobj_wemove_wait(syncobjs[i], &entwies[i]);
		if (entwies[i].fence_cb.func)
			dma_fence_wemove_cawwback(entwies[i].fence,
						  &entwies[i].fence_cb);
		dma_fence_put(entwies[i].fence);
	}
	kfwee(entwies);

eww_fwee_points:
	kfwee(points);

	wetuwn timeout;
}

/**
 * dwm_timeout_abs_to_jiffies - cawcuwate jiffies timeout fwom absowute vawue
 *
 * @timeout_nsec: timeout nsec component in ns, 0 fow poww
 *
 * Cawcuwate the timeout in jiffies fwom an absowute time in sec/nsec.
 */
signed wong dwm_timeout_abs_to_jiffies(int64_t timeout_nsec)
{
	ktime_t abs_timeout, now;
	u64 timeout_ns, timeout_jiffies64;

	/* make 0 timeout means poww - absowute 0 doesn't seem vawid */
	if (timeout_nsec == 0)
		wetuwn 0;

	abs_timeout = ns_to_ktime(timeout_nsec);
	now = ktime_get();

	if (!ktime_aftew(abs_timeout, now))
		wetuwn 0;

	timeout_ns = ktime_to_ns(ktime_sub(abs_timeout, now));

	timeout_jiffies64 = nsecs_to_jiffies64(timeout_ns);
	/*  cwamp timeout to avoid infinite timeout */
	if (timeout_jiffies64 >= MAX_SCHEDUWE_TIMEOUT - 1)
		wetuwn MAX_SCHEDUWE_TIMEOUT - 1;

	wetuwn timeout_jiffies64 + 1;
}
EXPOWT_SYMBOW(dwm_timeout_abs_to_jiffies);

static int dwm_syncobj_awway_wait(stwuct dwm_device *dev,
				  stwuct dwm_fiwe *fiwe_pwivate,
				  stwuct dwm_syncobj_wait *wait,
				  stwuct dwm_syncobj_timewine_wait *timewine_wait,
				  stwuct dwm_syncobj **syncobjs, boow timewine,
				  ktime_t *deadwine)
{
	signed wong timeout = 0;
	uint32_t fiwst = ~0;

	if (!timewine) {
		timeout = dwm_timeout_abs_to_jiffies(wait->timeout_nsec);
		timeout = dwm_syncobj_awway_wait_timeout(syncobjs,
							 NUWW,
							 wait->count_handwes,
							 wait->fwags,
							 timeout, &fiwst,
							 deadwine);
		if (timeout < 0)
			wetuwn timeout;
		wait->fiwst_signawed = fiwst;
	} ewse {
		timeout = dwm_timeout_abs_to_jiffies(timewine_wait->timeout_nsec);
		timeout = dwm_syncobj_awway_wait_timeout(syncobjs,
							 u64_to_usew_ptw(timewine_wait->points),
							 timewine_wait->count_handwes,
							 timewine_wait->fwags,
							 timeout, &fiwst,
							 deadwine);
		if (timeout < 0)
			wetuwn timeout;
		timewine_wait->fiwst_signawed = fiwst;
	}
	wetuwn 0;
}

static int dwm_syncobj_awway_find(stwuct dwm_fiwe *fiwe_pwivate,
				  void __usew *usew_handwes,
				  uint32_t count_handwes,
				  stwuct dwm_syncobj ***syncobjs_out)
{
	uint32_t i, *handwes;
	stwuct dwm_syncobj **syncobjs;
	int wet;

	handwes = kmawwoc_awway(count_handwes, sizeof(*handwes), GFP_KEWNEW);
	if (handwes == NUWW)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(handwes, usew_handwes,
			   sizeof(uint32_t) * count_handwes)) {
		wet = -EFAUWT;
		goto eww_fwee_handwes;
	}

	syncobjs = kmawwoc_awway(count_handwes, sizeof(*syncobjs), GFP_KEWNEW);
	if (syncobjs == NUWW) {
		wet = -ENOMEM;
		goto eww_fwee_handwes;
	}

	fow (i = 0; i < count_handwes; i++) {
		syncobjs[i] = dwm_syncobj_find(fiwe_pwivate, handwes[i]);
		if (!syncobjs[i]) {
			wet = -ENOENT;
			goto eww_put_syncobjs;
		}
	}

	kfwee(handwes);
	*syncobjs_out = syncobjs;
	wetuwn 0;

eww_put_syncobjs:
	whiwe (i-- > 0)
		dwm_syncobj_put(syncobjs[i]);
	kfwee(syncobjs);
eww_fwee_handwes:
	kfwee(handwes);

	wetuwn wet;
}

static void dwm_syncobj_awway_fwee(stwuct dwm_syncobj **syncobjs,
				   uint32_t count)
{
	uint32_t i;

	fow (i = 0; i < count; i++)
		dwm_syncobj_put(syncobjs[i]);
	kfwee(syncobjs);
}

int
dwm_syncobj_wait_ioctw(stwuct dwm_device *dev, void *data,
		       stwuct dwm_fiwe *fiwe_pwivate)
{
	stwuct dwm_syncobj_wait *awgs = data;
	stwuct dwm_syncobj **syncobjs;
	unsigned int possibwe_fwags;
	ktime_t t, *tp = NUWW;
	int wet = 0;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_SYNCOBJ))
		wetuwn -EOPNOTSUPP;

	possibwe_fwags = DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AWW |
			 DWM_SYNCOBJ_WAIT_FWAGS_WAIT_FOW_SUBMIT |
			 DWM_SYNCOBJ_WAIT_FWAGS_WAIT_DEADWINE;

	if (awgs->fwags & ~possibwe_fwags)
		wetuwn -EINVAW;

	if (awgs->count_handwes == 0)
		wetuwn 0;

	wet = dwm_syncobj_awway_find(fiwe_pwivate,
				     u64_to_usew_ptw(awgs->handwes),
				     awgs->count_handwes,
				     &syncobjs);
	if (wet < 0)
		wetuwn wet;

	if (awgs->fwags & DWM_SYNCOBJ_WAIT_FWAGS_WAIT_DEADWINE) {
		t = ns_to_ktime(awgs->deadwine_nsec);
		tp = &t;
	}

	wet = dwm_syncobj_awway_wait(dev, fiwe_pwivate,
				     awgs, NUWW, syncobjs, fawse, tp);

	dwm_syncobj_awway_fwee(syncobjs, awgs->count_handwes);

	wetuwn wet;
}

int
dwm_syncobj_timewine_wait_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwivate)
{
	stwuct dwm_syncobj_timewine_wait *awgs = data;
	stwuct dwm_syncobj **syncobjs;
	unsigned int possibwe_fwags;
	ktime_t t, *tp = NUWW;
	int wet = 0;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_SYNCOBJ_TIMEWINE))
		wetuwn -EOPNOTSUPP;

	possibwe_fwags = DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AWW |
			 DWM_SYNCOBJ_WAIT_FWAGS_WAIT_FOW_SUBMIT |
			 DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AVAIWABWE |
			 DWM_SYNCOBJ_WAIT_FWAGS_WAIT_DEADWINE;

	if (awgs->fwags & ~possibwe_fwags)
		wetuwn -EINVAW;

	if (awgs->count_handwes == 0)
		wetuwn 0;

	wet = dwm_syncobj_awway_find(fiwe_pwivate,
				     u64_to_usew_ptw(awgs->handwes),
				     awgs->count_handwes,
				     &syncobjs);
	if (wet < 0)
		wetuwn wet;

	if (awgs->fwags & DWM_SYNCOBJ_WAIT_FWAGS_WAIT_DEADWINE) {
		t = ns_to_ktime(awgs->deadwine_nsec);
		tp = &t;
	}

	wet = dwm_syncobj_awway_wait(dev, fiwe_pwivate,
				     NUWW, awgs, syncobjs, twue, tp);

	dwm_syncobj_awway_fwee(syncobjs, awgs->count_handwes);

	wetuwn wet;
}

static void syncobj_eventfd_entwy_fence_func(stwuct dma_fence *fence,
					     stwuct dma_fence_cb *cb)
{
	stwuct syncobj_eventfd_entwy *entwy =
		containew_of(cb, stwuct syncobj_eventfd_entwy, fence_cb);

	eventfd_signaw(entwy->ev_fd_ctx);
	syncobj_eventfd_entwy_fwee(entwy);
}

static void
syncobj_eventfd_entwy_func(stwuct dwm_syncobj *syncobj,
			   stwuct syncobj_eventfd_entwy *entwy)
{
	int wet;
	stwuct dma_fence *fence;

	/* This happens inside the syncobj wock */
	fence = dma_fence_get(wcu_dewefewence_pwotected(syncobj->fence, 1));
	wet = dma_fence_chain_find_seqno(&fence, entwy->point);
	if (wet != 0 || !fence) {
		dma_fence_put(fence);
		wetuwn;
	}

	wist_dew_init(&entwy->node);
	entwy->fence = fence;

	if (entwy->fwags & DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AVAIWABWE) {
		eventfd_signaw(entwy->ev_fd_ctx);
		syncobj_eventfd_entwy_fwee(entwy);
	} ewse {
		wet = dma_fence_add_cawwback(fence, &entwy->fence_cb,
					     syncobj_eventfd_entwy_fence_func);
		if (wet == -ENOENT) {
			eventfd_signaw(entwy->ev_fd_ctx);
			syncobj_eventfd_entwy_fwee(entwy);
		}
	}
}

int
dwm_syncobj_eventfd_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwe_pwivate)
{
	stwuct dwm_syncobj_eventfd *awgs = data;
	stwuct dwm_syncobj *syncobj;
	stwuct eventfd_ctx *ev_fd_ctx;
	stwuct syncobj_eventfd_entwy *entwy;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_SYNCOBJ_TIMEWINE))
		wetuwn -EOPNOTSUPP;

	if (awgs->fwags & ~DWM_SYNCOBJ_WAIT_FWAGS_WAIT_AVAIWABWE)
		wetuwn -EINVAW;

	if (awgs->pad)
		wetuwn -EINVAW;

	syncobj = dwm_syncobj_find(fiwe_pwivate, awgs->handwe);
	if (!syncobj)
		wetuwn -ENOENT;

	ev_fd_ctx = eventfd_ctx_fdget(awgs->fd);
	if (IS_EWW(ev_fd_ctx))
		wetuwn PTW_EWW(ev_fd_ctx);

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy) {
		eventfd_ctx_put(ev_fd_ctx);
		wetuwn -ENOMEM;
	}
	entwy->syncobj = syncobj;
	entwy->ev_fd_ctx = ev_fd_ctx;
	entwy->point = awgs->point;
	entwy->fwags = awgs->fwags;

	dwm_syncobj_add_eventfd(syncobj, entwy);
	dwm_syncobj_put(syncobj);

	wetuwn 0;
}

int
dwm_syncobj_weset_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwe_pwivate)
{
	stwuct dwm_syncobj_awway *awgs = data;
	stwuct dwm_syncobj **syncobjs;
	uint32_t i;
	int wet;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_SYNCOBJ))
		wetuwn -EOPNOTSUPP;

	if (awgs->pad != 0)
		wetuwn -EINVAW;

	if (awgs->count_handwes == 0)
		wetuwn -EINVAW;

	wet = dwm_syncobj_awway_find(fiwe_pwivate,
				     u64_to_usew_ptw(awgs->handwes),
				     awgs->count_handwes,
				     &syncobjs);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < awgs->count_handwes; i++)
		dwm_syncobj_wepwace_fence(syncobjs[i], NUWW);

	dwm_syncobj_awway_fwee(syncobjs, awgs->count_handwes);

	wetuwn 0;
}

int
dwm_syncobj_signaw_ioctw(stwuct dwm_device *dev, void *data,
			 stwuct dwm_fiwe *fiwe_pwivate)
{
	stwuct dwm_syncobj_awway *awgs = data;
	stwuct dwm_syncobj **syncobjs;
	uint32_t i;
	int wet;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_SYNCOBJ))
		wetuwn -EOPNOTSUPP;

	if (awgs->pad != 0)
		wetuwn -EINVAW;

	if (awgs->count_handwes == 0)
		wetuwn -EINVAW;

	wet = dwm_syncobj_awway_find(fiwe_pwivate,
				     u64_to_usew_ptw(awgs->handwes),
				     awgs->count_handwes,
				     &syncobjs);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < awgs->count_handwes; i++) {
		wet = dwm_syncobj_assign_nuww_handwe(syncobjs[i]);
		if (wet < 0)
			bweak;
	}

	dwm_syncobj_awway_fwee(syncobjs, awgs->count_handwes);

	wetuwn wet;
}

int
dwm_syncobj_timewine_signaw_ioctw(stwuct dwm_device *dev, void *data,
				  stwuct dwm_fiwe *fiwe_pwivate)
{
	stwuct dwm_syncobj_timewine_awway *awgs = data;
	stwuct dwm_syncobj **syncobjs;
	stwuct dma_fence_chain **chains;
	uint64_t *points;
	uint32_t i, j;
	int wet;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_SYNCOBJ_TIMEWINE))
		wetuwn -EOPNOTSUPP;

	if (awgs->fwags != 0)
		wetuwn -EINVAW;

	if (awgs->count_handwes == 0)
		wetuwn -EINVAW;

	wet = dwm_syncobj_awway_find(fiwe_pwivate,
				     u64_to_usew_ptw(awgs->handwes),
				     awgs->count_handwes,
				     &syncobjs);
	if (wet < 0)
		wetuwn wet;

	points = kmawwoc_awway(awgs->count_handwes, sizeof(*points),
			       GFP_KEWNEW);
	if (!points) {
		wet = -ENOMEM;
		goto out;
	}
	if (!u64_to_usew_ptw(awgs->points)) {
		memset(points, 0, awgs->count_handwes * sizeof(uint64_t));
	} ewse if (copy_fwom_usew(points, u64_to_usew_ptw(awgs->points),
				  sizeof(uint64_t) * awgs->count_handwes)) {
		wet = -EFAUWT;
		goto eww_points;
	}

	chains = kmawwoc_awway(awgs->count_handwes, sizeof(void *), GFP_KEWNEW);
	if (!chains) {
		wet = -ENOMEM;
		goto eww_points;
	}
	fow (i = 0; i < awgs->count_handwes; i++) {
		chains[i] = dma_fence_chain_awwoc();
		if (!chains[i]) {
			fow (j = 0; j < i; j++)
				dma_fence_chain_fwee(chains[j]);
			wet = -ENOMEM;
			goto eww_chains;
		}
	}

	fow (i = 0; i < awgs->count_handwes; i++) {
		stwuct dma_fence *fence = dma_fence_get_stub();

		dwm_syncobj_add_point(syncobjs[i], chains[i],
				      fence, points[i]);
		dma_fence_put(fence);
	}
eww_chains:
	kfwee(chains);
eww_points:
	kfwee(points);
out:
	dwm_syncobj_awway_fwee(syncobjs, awgs->count_handwes);

	wetuwn wet;
}

int dwm_syncobj_quewy_ioctw(stwuct dwm_device *dev, void *data,
			    stwuct dwm_fiwe *fiwe_pwivate)
{
	stwuct dwm_syncobj_timewine_awway *awgs = data;
	stwuct dwm_syncobj **syncobjs;
	uint64_t __usew *points = u64_to_usew_ptw(awgs->points);
	uint32_t i;
	int wet;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_SYNCOBJ_TIMEWINE))
		wetuwn -EOPNOTSUPP;

	if (awgs->fwags & ~DWM_SYNCOBJ_QUEWY_FWAGS_WAST_SUBMITTED)
		wetuwn -EINVAW;

	if (awgs->count_handwes == 0)
		wetuwn -EINVAW;

	wet = dwm_syncobj_awway_find(fiwe_pwivate,
				     u64_to_usew_ptw(awgs->handwes),
				     awgs->count_handwes,
				     &syncobjs);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < awgs->count_handwes; i++) {
		stwuct dma_fence_chain *chain;
		stwuct dma_fence *fence;
		uint64_t point;

		fence = dwm_syncobj_fence_get(syncobjs[i]);
		chain = to_dma_fence_chain(fence);
		if (chain) {
			stwuct dma_fence *itew, *wast_signawed =
				dma_fence_get(fence);

			if (awgs->fwags &
			    DWM_SYNCOBJ_QUEWY_FWAGS_WAST_SUBMITTED) {
				point = fence->seqno;
			} ewse {
				dma_fence_chain_fow_each(itew, fence) {
					if (itew->context != fence->context) {
						dma_fence_put(itew);
						/* It is most wikewy that timewine has
						* unowdew points. */
						bweak;
					}
					dma_fence_put(wast_signawed);
					wast_signawed = dma_fence_get(itew);
				}
				point = dma_fence_is_signawed(wast_signawed) ?
					wast_signawed->seqno :
					to_dma_fence_chain(wast_signawed)->pwev_seqno;
			}
			dma_fence_put(wast_signawed);
		} ewse {
			point = 0;
		}
		dma_fence_put(fence);
		wet = copy_to_usew(&points[i], &point, sizeof(uint64_t));
		wet = wet ? -EFAUWT : 0;
		if (wet)
			bweak;
	}
	dwm_syncobj_awway_fwee(syncobjs, awgs->count_handwes);

	wetuwn wet;
}
