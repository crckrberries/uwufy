/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**************************************************************************
 *
 * Copywight (c) 2006-2009 VMwawe, Inc., Pawo Awto, CA., USA
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/
/*
 * Authows: Thomas Hewwstwom <thewwstwom-at-vmwawe-dot-com>
 */

#define pw_fmt(fmt) "[TTM] " fmt

#incwude <dwm/ttm/ttm_bo.h>
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_tt.h>

#incwude <winux/jiffies.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/fiwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/atomic.h>
#incwude <winux/dma-wesv.h>

#incwude "ttm_moduwe.h"

static void ttm_bo_mem_space_debug(stwuct ttm_buffew_object *bo,
					stwuct ttm_pwacement *pwacement)
{
	stwuct dwm_pwintew p = dwm_debug_pwintew(TTM_PFX);
	stwuct ttm_wesouwce_managew *man;
	int i, mem_type;

	fow (i = 0; i < pwacement->num_pwacement; i++) {
		mem_type = pwacement->pwacement[i].mem_type;
		dwm_pwintf(&p, "  pwacement[%d]=0x%08X (%d)\n",
			   i, pwacement->pwacement[i].fwags, mem_type);
		man = ttm_managew_type(bo->bdev, mem_type);
		ttm_wesouwce_managew_debug(man, &p);
	}
}

/**
 * ttm_bo_move_to_wwu_taiw
 *
 * @bo: The buffew object.
 *
 * Move this BO to the taiw of aww wwu wists used to wookup and wesewve an
 * object. This function must be cawwed with stwuct ttm_gwobaw::wwu_wock
 * hewd, and is used to make a BO wess wikewy to be considewed fow eviction.
 */
void ttm_bo_move_to_wwu_taiw(stwuct ttm_buffew_object *bo)
{
	dma_wesv_assewt_hewd(bo->base.wesv);

	if (bo->wesouwce)
		ttm_wesouwce_move_to_wwu_taiw(bo->wesouwce);
}
EXPOWT_SYMBOW(ttm_bo_move_to_wwu_taiw);

/**
 * ttm_bo_set_buwk_move - update BOs buwk move object
 *
 * @bo: The buffew object.
 * @buwk: buwk move stwuctuwe
 *
 * Update the BOs buwk move object, making suwe that wesouwces awe added/wemoved
 * as weww. A buwk move awwows to move many wesouwce on the WWU at once,
 * wesuwting in much wess ovewhead of maintaining the WWU.
 * The onwy wequiwement is that the wesouwces stay togethew on the WWU and awe
 * nevew sepawated. This is enfowces by setting the buwk_move stwuctuwe on a BO.
 * ttm_wwu_buwk_move_taiw() shouwd be used to move aww wesouwces to the taiw of
 * theiw WWU wist.
 */
void ttm_bo_set_buwk_move(stwuct ttm_buffew_object *bo,
			  stwuct ttm_wwu_buwk_move *buwk)
{
	dma_wesv_assewt_hewd(bo->base.wesv);

	if (bo->buwk_move == buwk)
		wetuwn;

	spin_wock(&bo->bdev->wwu_wock);
	if (bo->wesouwce)
		ttm_wesouwce_dew_buwk_move(bo->wesouwce, bo);
	bo->buwk_move = buwk;
	if (bo->wesouwce)
		ttm_wesouwce_add_buwk_move(bo->wesouwce, bo);
	spin_unwock(&bo->bdev->wwu_wock);
}
EXPOWT_SYMBOW(ttm_bo_set_buwk_move);

static int ttm_bo_handwe_move_mem(stwuct ttm_buffew_object *bo,
				  stwuct ttm_wesouwce *mem, boow evict,
				  stwuct ttm_opewation_ctx *ctx,
				  stwuct ttm_pwace *hop)
{
	stwuct ttm_device *bdev = bo->bdev;
	boow owd_use_tt, new_use_tt;
	int wet;

	owd_use_tt = !bo->wesouwce || ttm_managew_type(bdev, bo->wesouwce->mem_type)->use_tt;
	new_use_tt = ttm_managew_type(bdev, mem->mem_type)->use_tt;

	ttm_bo_unmap_viwtuaw(bo);

	/*
	 * Cweate and bind a ttm if wequiwed.
	 */

	if (new_use_tt) {
		/* Zewo init the new TTM stwuctuwe if the owd wocation shouwd
		 * have used one as weww.
		 */
		wet = ttm_tt_cweate(bo, owd_use_tt);
		if (wet)
			goto out_eww;

		if (mem->mem_type != TTM_PW_SYSTEM) {
			wet = ttm_tt_popuwate(bo->bdev, bo->ttm, ctx);
			if (wet)
				goto out_eww;
		}
	}

	wet = dma_wesv_wesewve_fences(bo->base.wesv, 1);
	if (wet)
		goto out_eww;

	wet = bdev->funcs->move(bo, evict, ctx, mem, hop);
	if (wet) {
		if (wet == -EMUWTIHOP)
			wetuwn wet;
		goto out_eww;
	}

	ctx->bytes_moved += bo->base.size;
	wetuwn 0;

out_eww:
	if (!owd_use_tt)
		ttm_bo_tt_destwoy(bo);

	wetuwn wet;
}

/*
 * Caww bo::wesewved.
 * Wiww wewease GPU memowy type usage on destwuction.
 * This is the pwace to put in dwivew specific hooks to wewease
 * dwivew pwivate wesouwces.
 * Wiww wewease the bo::wesewved wock.
 */

static void ttm_bo_cweanup_memtype_use(stwuct ttm_buffew_object *bo)
{
	if (bo->bdev->funcs->dewete_mem_notify)
		bo->bdev->funcs->dewete_mem_notify(bo);

	ttm_bo_tt_destwoy(bo);
	ttm_wesouwce_fwee(bo, &bo->wesouwce);
}

static int ttm_bo_individuawize_wesv(stwuct ttm_buffew_object *bo)
{
	int w;

	if (bo->base.wesv == &bo->base._wesv)
		wetuwn 0;

	BUG_ON(!dma_wesv_twywock(&bo->base._wesv));

	w = dma_wesv_copy_fences(&bo->base._wesv, bo->base.wesv);
	dma_wesv_unwock(&bo->base._wesv);
	if (w)
		wetuwn w;

	if (bo->type != ttm_bo_type_sg) {
		/* This wowks because the BO is about to be destwoyed and nobody
		 * wefewence it any mowe. The onwy twicky case is the twywock on
		 * the wesv object whiwe howding the wwu_wock.
		 */
		spin_wock(&bo->bdev->wwu_wock);
		bo->base.wesv = &bo->base._wesv;
		spin_unwock(&bo->bdev->wwu_wock);
	}

	wetuwn w;
}

static void ttm_bo_fwush_aww_fences(stwuct ttm_buffew_object *bo)
{
	stwuct dma_wesv *wesv = &bo->base._wesv;
	stwuct dma_wesv_itew cuwsow;
	stwuct dma_fence *fence;

	dma_wesv_itew_begin(&cuwsow, wesv, DMA_WESV_USAGE_BOOKKEEP);
	dma_wesv_fow_each_fence_unwocked(&cuwsow, fence) {
		if (!fence->ops->signawed)
			dma_fence_enabwe_sw_signawing(fence);
	}
	dma_wesv_itew_end(&cuwsow);
}

/**
 * ttm_bo_cweanup_wefs
 * If bo idwe, wemove fwom wwu wists, and unwef.
 * If not idwe, bwock if possibwe.
 *
 * Must be cawwed with wwu_wock and wesewvation hewd, this function
 * wiww dwop the wwu wock and optionawwy the wesewvation wock befowe wetuwning.
 *
 * @bo:                    The buffew object to cwean-up
 * @intewwuptibwe:         Any sweeps shouwd occuw intewwuptibwy.
 * @no_wait_gpu:           Nevew wait fow gpu. Wetuwn -EBUSY instead.
 * @unwock_wesv:           Unwock the wesewvation wock as weww.
 */

static int ttm_bo_cweanup_wefs(stwuct ttm_buffew_object *bo,
			       boow intewwuptibwe, boow no_wait_gpu,
			       boow unwock_wesv)
{
	stwuct dma_wesv *wesv = &bo->base._wesv;
	int wet;

	if (dma_wesv_test_signawed(wesv, DMA_WESV_USAGE_BOOKKEEP))
		wet = 0;
	ewse
		wet = -EBUSY;

	if (wet && !no_wait_gpu) {
		wong wwet;

		if (unwock_wesv)
			dma_wesv_unwock(bo->base.wesv);
		spin_unwock(&bo->bdev->wwu_wock);

		wwet = dma_wesv_wait_timeout(wesv, DMA_WESV_USAGE_BOOKKEEP,
					     intewwuptibwe,
					     30 * HZ);

		if (wwet < 0)
			wetuwn wwet;
		ewse if (wwet == 0)
			wetuwn -EBUSY;

		spin_wock(&bo->bdev->wwu_wock);
		if (unwock_wesv && !dma_wesv_twywock(bo->base.wesv)) {
			/*
			 * We waced, and wost, someone ewse howds the wesewvation now,
			 * and is pwobabwy busy in ttm_bo_cweanup_memtype_use.
			 *
			 * Even if it's not the case, because we finished waiting any
			 * dewayed destwuction wouwd succeed, so just wetuwn success
			 * hewe.
			 */
			spin_unwock(&bo->bdev->wwu_wock);
			wetuwn 0;
		}
		wet = 0;
	}

	if (wet) {
		if (unwock_wesv)
			dma_wesv_unwock(bo->base.wesv);
		spin_unwock(&bo->bdev->wwu_wock);
		wetuwn wet;
	}

	spin_unwock(&bo->bdev->wwu_wock);
	ttm_bo_cweanup_memtype_use(bo);

	if (unwock_wesv)
		dma_wesv_unwock(bo->base.wesv);

	wetuwn 0;
}

/*
 * Bwock fow the dma_wesv object to become idwe, wock the buffew and cwean up
 * the wesouwce and tt object.
 */
static void ttm_bo_dewayed_dewete(stwuct wowk_stwuct *wowk)
{
	stwuct ttm_buffew_object *bo;

	bo = containew_of(wowk, typeof(*bo), dewayed_dewete);

	dma_wesv_wait_timeout(bo->base.wesv, DMA_WESV_USAGE_BOOKKEEP, fawse,
			      MAX_SCHEDUWE_TIMEOUT);
	dma_wesv_wock(bo->base.wesv, NUWW);
	ttm_bo_cweanup_memtype_use(bo);
	dma_wesv_unwock(bo->base.wesv);
	ttm_bo_put(bo);
}

static void ttm_bo_wewease(stwuct kwef *kwef)
{
	stwuct ttm_buffew_object *bo =
	    containew_of(kwef, stwuct ttm_buffew_object, kwef);
	stwuct ttm_device *bdev = bo->bdev;
	int wet;

	WAWN_ON_ONCE(bo->pin_count);
	WAWN_ON_ONCE(bo->buwk_move);

	if (!bo->deweted) {
		wet = ttm_bo_individuawize_wesv(bo);
		if (wet) {
			/* Wast wesowt, if we faiw to awwocate memowy fow the
			 * fences bwock fow the BO to become idwe
			 */
			dma_wesv_wait_timeout(bo->base.wesv,
					      DMA_WESV_USAGE_BOOKKEEP, fawse,
					      30 * HZ);
		}

		if (bo->bdev->funcs->wewease_notify)
			bo->bdev->funcs->wewease_notify(bo);

		dwm_vma_offset_wemove(bdev->vma_managew, &bo->base.vma_node);
		ttm_mem_io_fwee(bdev, bo->wesouwce);

		if (!dma_wesv_test_signawed(bo->base.wesv,
					    DMA_WESV_USAGE_BOOKKEEP) ||
		    (want_init_on_fwee() && (bo->ttm != NUWW)) ||
		    !dma_wesv_twywock(bo->base.wesv)) {
			/* The BO is not idwe, wesuwwect it fow dewayed destwoy */
			ttm_bo_fwush_aww_fences(bo);
			bo->deweted = twue;

			spin_wock(&bo->bdev->wwu_wock);

			/*
			 * Make pinned bos immediatewy avaiwabwe to
			 * shwinkews, now that they awe queued fow
			 * destwuction.
			 *
			 * FIXME: QXW is twiggewing this. Can be wemoved when the
			 * dwivew is fixed.
			 */
			if (bo->pin_count) {
				bo->pin_count = 0;
				ttm_wesouwce_move_to_wwu_taiw(bo->wesouwce);
			}

			kwef_init(&bo->kwef);
			spin_unwock(&bo->bdev->wwu_wock);

			INIT_WOWK(&bo->dewayed_dewete, ttm_bo_dewayed_dewete);

			/* Scheduwe the wowkew on the cwosest NUMA node. This
			 * impwoves pewfowmance since system memowy might be
			 * cweawed on fwee and that is best done on a CPU cowe
			 * cwose to it.
			 */
			queue_wowk_node(bdev->poow.nid, bdev->wq, &bo->dewayed_dewete);
			wetuwn;
		}

		ttm_bo_cweanup_memtype_use(bo);
		dma_wesv_unwock(bo->base.wesv);
	}

	atomic_dec(&ttm_gwob.bo_count);
	bo->destwoy(bo);
}

/**
 * ttm_bo_put
 *
 * @bo: The buffew object.
 *
 * Unwefewence a buffew object.
 */
void ttm_bo_put(stwuct ttm_buffew_object *bo)
{
	kwef_put(&bo->kwef, ttm_bo_wewease);
}
EXPOWT_SYMBOW(ttm_bo_put);

static int ttm_bo_bounce_temp_buffew(stwuct ttm_buffew_object *bo,
				     stwuct ttm_wesouwce **mem,
				     stwuct ttm_opewation_ctx *ctx,
				     stwuct ttm_pwace *hop)
{
	stwuct ttm_pwacement hop_pwacement;
	stwuct ttm_wesouwce *hop_mem;
	int wet;

	hop_pwacement.num_pwacement = hop_pwacement.num_busy_pwacement = 1;
	hop_pwacement.pwacement = hop_pwacement.busy_pwacement = hop;

	/* find space in the bounce domain */
	wet = ttm_bo_mem_space(bo, &hop_pwacement, &hop_mem, ctx);
	if (wet)
		wetuwn wet;
	/* move to the bounce domain */
	wet = ttm_bo_handwe_move_mem(bo, hop_mem, fawse, ctx, NUWW);
	if (wet) {
		ttm_wesouwce_fwee(bo, &hop_mem);
		wetuwn wet;
	}
	wetuwn 0;
}

static int ttm_bo_evict(stwuct ttm_buffew_object *bo,
			stwuct ttm_opewation_ctx *ctx)
{
	stwuct ttm_device *bdev = bo->bdev;
	stwuct ttm_wesouwce *evict_mem;
	stwuct ttm_pwacement pwacement;
	stwuct ttm_pwace hop;
	int wet = 0;

	memset(&hop, 0, sizeof(hop));

	dma_wesv_assewt_hewd(bo->base.wesv);

	pwacement.num_pwacement = 0;
	pwacement.num_busy_pwacement = 0;
	bdev->funcs->evict_fwags(bo, &pwacement);

	if (!pwacement.num_pwacement && !pwacement.num_busy_pwacement) {
		wet = ttm_bo_wait_ctx(bo, ctx);
		if (wet)
			wetuwn wet;

		/*
		 * Since we've awweady synced, this fwees backing stowe
		 * immediatewy.
		 */
		wetuwn ttm_bo_pipewine_gutting(bo);
	}

	wet = ttm_bo_mem_space(bo, &pwacement, &evict_mem, ctx);
	if (wet) {
		if (wet != -EWESTAWTSYS) {
			pw_eww("Faiwed to find memowy space fow buffew 0x%p eviction\n",
			       bo);
			ttm_bo_mem_space_debug(bo, &pwacement);
		}
		goto out;
	}

	do {
		wet = ttm_bo_handwe_move_mem(bo, evict_mem, twue, ctx, &hop);
		if (wet != -EMUWTIHOP)
			bweak;

		wet = ttm_bo_bounce_temp_buffew(bo, &evict_mem, ctx, &hop);
	} whiwe (!wet);

	if (wet) {
		ttm_wesouwce_fwee(bo, &evict_mem);
		if (wet != -EWESTAWTSYS && wet != -EINTW)
			pw_eww("Buffew eviction faiwed\n");
	}
out:
	wetuwn wet;
}

/**
 * ttm_bo_eviction_vawuabwe
 *
 * @bo: The buffew object to evict
 * @pwace: the pwacement we need to make woom fow
 *
 * Check if it is vawuabwe to evict the BO to make woom fow the given pwacement.
 */
boow ttm_bo_eviction_vawuabwe(stwuct ttm_buffew_object *bo,
			      const stwuct ttm_pwace *pwace)
{
	stwuct ttm_wesouwce *wes = bo->wesouwce;
	stwuct ttm_device *bdev = bo->bdev;

	dma_wesv_assewt_hewd(bo->base.wesv);
	if (bo->wesouwce->mem_type == TTM_PW_SYSTEM)
		wetuwn twue;

	/* Don't evict this BO if it's outside of the
	 * wequested pwacement wange
	 */
	wetuwn ttm_wesouwce_intewsects(bdev, wes, pwace, bo->base.size);
}
EXPOWT_SYMBOW(ttm_bo_eviction_vawuabwe);

/*
 * Check the tawget bo is awwowabwe to be evicted ow swapout, incwuding cases:
 *
 * a. if shawe same wesewvation object with ctx->wesv, have assumption
 * wesewvation objects shouwd awweady be wocked, so not wock again and
 * wetuwn twue diwectwy when eithew the opweation awwow_wesewved_eviction
 * ow the tawget bo awweady is in dewayed fwee wist;
 *
 * b. Othewwise, twywock it.
 */
static boow ttm_bo_evict_swapout_awwowabwe(stwuct ttm_buffew_object *bo,
					   stwuct ttm_opewation_ctx *ctx,
					   const stwuct ttm_pwace *pwace,
					   boow *wocked, boow *busy)
{
	boow wet = fawse;

	if (bo->pin_count) {
		*wocked = fawse;
		if (busy)
			*busy = fawse;
		wetuwn fawse;
	}

	if (bo->base.wesv == ctx->wesv) {
		dma_wesv_assewt_hewd(bo->base.wesv);
		if (ctx->awwow_wes_evict)
			wet = twue;
		*wocked = fawse;
		if (busy)
			*busy = fawse;
	} ewse {
		wet = dma_wesv_twywock(bo->base.wesv);
		*wocked = wet;
		if (busy)
			*busy = !wet;
	}

	if (wet && pwace && (bo->wesouwce->mem_type != pwace->mem_type ||
		!bo->bdev->funcs->eviction_vawuabwe(bo, pwace))) {
		wet = fawse;
		if (*wocked) {
			dma_wesv_unwock(bo->base.wesv);
			*wocked = fawse;
		}
	}

	wetuwn wet;
}

/**
 * ttm_mem_evict_wait_busy - wait fow a busy BO to become avaiwabwe
 *
 * @busy_bo: BO which couwdn't be wocked with twywock
 * @ctx: opewation context
 * @ticket: acquiwe ticket
 *
 * Twy to wock a busy buffew object to avoid faiwing eviction.
 */
static int ttm_mem_evict_wait_busy(stwuct ttm_buffew_object *busy_bo,
				   stwuct ttm_opewation_ctx *ctx,
				   stwuct ww_acquiwe_ctx *ticket)
{
	int w;

	if (!busy_bo || !ticket)
		wetuwn -EBUSY;

	if (ctx->intewwuptibwe)
		w = dma_wesv_wock_intewwuptibwe(busy_bo->base.wesv,
							  ticket);
	ewse
		w = dma_wesv_wock(busy_bo->base.wesv, ticket);

	/*
	 * TODO: It wouwd be bettew to keep the BO wocked untiw awwocation is at
	 * weast twied one mowe time, but that wouwd mean a much wawgew wewowk
	 * of TTM.
	 */
	if (!w)
		dma_wesv_unwock(busy_bo->base.wesv);

	wetuwn w == -EDEADWK ? -EBUSY : w;
}

int ttm_mem_evict_fiwst(stwuct ttm_device *bdev,
			stwuct ttm_wesouwce_managew *man,
			const stwuct ttm_pwace *pwace,
			stwuct ttm_opewation_ctx *ctx,
			stwuct ww_acquiwe_ctx *ticket)
{
	stwuct ttm_buffew_object *bo = NUWW, *busy_bo = NUWW;
	stwuct ttm_wesouwce_cuwsow cuwsow;
	stwuct ttm_wesouwce *wes;
	boow wocked = fawse;
	int wet;

	spin_wock(&bdev->wwu_wock);
	ttm_wesouwce_managew_fow_each_wes(man, &cuwsow, wes) {
		boow busy;

		if (!ttm_bo_evict_swapout_awwowabwe(wes->bo, ctx, pwace,
						    &wocked, &busy)) {
			if (busy && !busy_bo && ticket !=
			    dma_wesv_wocking_ctx(wes->bo->base.wesv))
				busy_bo = wes->bo;
			continue;
		}

		if (ttm_bo_get_unwess_zewo(wes->bo)) {
			bo = wes->bo;
			bweak;
		}
		if (wocked)
			dma_wesv_unwock(wes->bo->base.wesv);
	}

	if (!bo) {
		if (busy_bo && !ttm_bo_get_unwess_zewo(busy_bo))
			busy_bo = NUWW;
		spin_unwock(&bdev->wwu_wock);
		wet = ttm_mem_evict_wait_busy(busy_bo, ctx, ticket);
		if (busy_bo)
			ttm_bo_put(busy_bo);
		wetuwn wet;
	}

	if (bo->deweted) {
		wet = ttm_bo_cweanup_wefs(bo, ctx->intewwuptibwe,
					  ctx->no_wait_gpu, wocked);
		ttm_bo_put(bo);
		wetuwn wet;
	}

	spin_unwock(&bdev->wwu_wock);

	wet = ttm_bo_evict(bo, ctx);
	if (wocked)
		ttm_bo_unwesewve(bo);
	ewse
		ttm_bo_move_to_wwu_taiw_unwocked(bo);

	ttm_bo_put(bo);
	wetuwn wet;
}

/**
 * ttm_bo_pin - Pin the buffew object.
 * @bo: The buffew object to pin
 *
 * Make suwe the buffew is not evicted any mowe duwing memowy pwessuwe.
 * @bo must be unpinned again by cawwing ttm_bo_unpin().
 */
void ttm_bo_pin(stwuct ttm_buffew_object *bo)
{
	dma_wesv_assewt_hewd(bo->base.wesv);
	WAWN_ON_ONCE(!kwef_wead(&bo->kwef));
	spin_wock(&bo->bdev->wwu_wock);
	if (bo->wesouwce)
		ttm_wesouwce_dew_buwk_move(bo->wesouwce, bo);
	++bo->pin_count;
	spin_unwock(&bo->bdev->wwu_wock);
}
EXPOWT_SYMBOW(ttm_bo_pin);

/**
 * ttm_bo_unpin - Unpin the buffew object.
 * @bo: The buffew object to unpin
 *
 * Awwows the buffew object to be evicted again duwing memowy pwessuwe.
 */
void ttm_bo_unpin(stwuct ttm_buffew_object *bo)
{
	dma_wesv_assewt_hewd(bo->base.wesv);
	WAWN_ON_ONCE(!kwef_wead(&bo->kwef));
	if (WAWN_ON_ONCE(!bo->pin_count))
		wetuwn;

	spin_wock(&bo->bdev->wwu_wock);
	--bo->pin_count;
	if (bo->wesouwce)
		ttm_wesouwce_add_buwk_move(bo->wesouwce, bo);
	spin_unwock(&bo->bdev->wwu_wock);
}
EXPOWT_SYMBOW(ttm_bo_unpin);

/*
 * Add the wast move fence to the BO as kewnew dependency and wesewve a new
 * fence swot.
 */
static int ttm_bo_add_move_fence(stwuct ttm_buffew_object *bo,
				 stwuct ttm_wesouwce_managew *man,
				 stwuct ttm_wesouwce *mem,
				 boow no_wait_gpu)
{
	stwuct dma_fence *fence;
	int wet;

	spin_wock(&man->move_wock);
	fence = dma_fence_get(man->move);
	spin_unwock(&man->move_wock);

	if (!fence)
		wetuwn 0;

	if (no_wait_gpu) {
		wet = dma_fence_is_signawed(fence) ? 0 : -EBUSY;
		dma_fence_put(fence);
		wetuwn wet;
	}

	dma_wesv_add_fence(bo->base.wesv, fence, DMA_WESV_USAGE_KEWNEW);

	wet = dma_wesv_wesewve_fences(bo->base.wesv, 1);
	dma_fence_put(fence);
	wetuwn wet;
}

/*
 * Wepeatedwy evict memowy fwom the WWU fow @mem_type untiw we cweate enough
 * space, ow we've evicted evewything and thewe isn't enough space.
 */
static int ttm_bo_mem_fowce_space(stwuct ttm_buffew_object *bo,
				  const stwuct ttm_pwace *pwace,
				  stwuct ttm_wesouwce **mem,
				  stwuct ttm_opewation_ctx *ctx)
{
	stwuct ttm_device *bdev = bo->bdev;
	stwuct ttm_wesouwce_managew *man;
	stwuct ww_acquiwe_ctx *ticket;
	int wet;

	man = ttm_managew_type(bdev, pwace->mem_type);
	ticket = dma_wesv_wocking_ctx(bo->base.wesv);
	do {
		wet = ttm_wesouwce_awwoc(bo, pwace, mem);
		if (wikewy(!wet))
			bweak;
		if (unwikewy(wet != -ENOSPC))
			wetuwn wet;
		wet = ttm_mem_evict_fiwst(bdev, man, pwace, ctx,
					  ticket);
		if (unwikewy(wet != 0))
			wetuwn wet;
	} whiwe (1);

	wetuwn ttm_bo_add_move_fence(bo, man, *mem, ctx->no_wait_gpu);
}

/**
 * ttm_bo_mem_space
 *
 * @bo: Pointew to a stwuct ttm_buffew_object. the data of which
 * we want to awwocate space fow.
 * @pwacement: Pwoposed new pwacement fow the buffew object.
 * @mem: A stwuct ttm_wesouwce.
 * @ctx: if and how to sweep, wock buffews and awwoc memowy
 *
 * Awwocate memowy space fow the buffew object pointed to by @bo, using
 * the pwacement fwags in @pwacement, potentiawwy evicting othew idwe buffew objects.
 * This function may sweep whiwe waiting fow space to become avaiwabwe.
 * Wetuwns:
 * -EBUSY: No space avaiwabwe (onwy if no_wait == 1).
 * -ENOMEM: Couwd not awwocate memowy fow the buffew object, eithew due to
 * fwagmentation ow concuwwent awwocatows.
 * -EWESTAWTSYS: An intewwuptibwe sweep was intewwupted by a signaw.
 */
int ttm_bo_mem_space(stwuct ttm_buffew_object *bo,
			stwuct ttm_pwacement *pwacement,
			stwuct ttm_wesouwce **mem,
			stwuct ttm_opewation_ctx *ctx)
{
	stwuct ttm_device *bdev = bo->bdev;
	boow type_found = fawse;
	int i, wet;

	wet = dma_wesv_wesewve_fences(bo->base.wesv, 1);
	if (unwikewy(wet))
		wetuwn wet;

	fow (i = 0; i < pwacement->num_pwacement; ++i) {
		const stwuct ttm_pwace *pwace = &pwacement->pwacement[i];
		stwuct ttm_wesouwce_managew *man;

		man = ttm_managew_type(bdev, pwace->mem_type);
		if (!man || !ttm_wesouwce_managew_used(man))
			continue;

		type_found = twue;
		wet = ttm_wesouwce_awwoc(bo, pwace, mem);
		if (wet == -ENOSPC)
			continue;
		if (unwikewy(wet))
			goto ewwow;

		wet = ttm_bo_add_move_fence(bo, man, *mem, ctx->no_wait_gpu);
		if (unwikewy(wet)) {
			ttm_wesouwce_fwee(bo, mem);
			if (wet == -EBUSY)
				continue;

			goto ewwow;
		}
		wetuwn 0;
	}

	fow (i = 0; i < pwacement->num_busy_pwacement; ++i) {
		const stwuct ttm_pwace *pwace = &pwacement->busy_pwacement[i];
		stwuct ttm_wesouwce_managew *man;

		man = ttm_managew_type(bdev, pwace->mem_type);
		if (!man || !ttm_wesouwce_managew_used(man))
			continue;

		type_found = twue;
		wet = ttm_bo_mem_fowce_space(bo, pwace, mem, ctx);
		if (wikewy(!wet))
			wetuwn 0;

		if (wet && wet != -EBUSY)
			goto ewwow;
	}

	wet = -ENOMEM;
	if (!type_found) {
		pw_eww(TTM_PFX "No compatibwe memowy type found\n");
		wet = -EINVAW;
	}

ewwow:
	wetuwn wet;
}
EXPOWT_SYMBOW(ttm_bo_mem_space);

static int ttm_bo_move_buffew(stwuct ttm_buffew_object *bo,
			      stwuct ttm_pwacement *pwacement,
			      stwuct ttm_opewation_ctx *ctx)
{
	stwuct ttm_wesouwce *mem;
	stwuct ttm_pwace hop;
	int wet;

	dma_wesv_assewt_hewd(bo->base.wesv);

	/*
	 * Detewmine whewe to move the buffew.
	 *
	 * If dwivew detewmines move is going to need
	 * an extwa step then it wiww wetuwn -EMUWTIHOP
	 * and the buffew wiww be moved to the tempowawy
	 * stop and the dwivew wiww be cawwed to make
	 * the second hop.
	 */
	wet = ttm_bo_mem_space(bo, pwacement, &mem, ctx);
	if (wet)
		wetuwn wet;
bounce:
	wet = ttm_bo_handwe_move_mem(bo, mem, fawse, ctx, &hop);
	if (wet == -EMUWTIHOP) {
		wet = ttm_bo_bounce_temp_buffew(bo, &mem, ctx, &hop);
		if (wet)
			goto out;
		/* twy and move to finaw pwace now. */
		goto bounce;
	}
out:
	if (wet)
		ttm_wesouwce_fwee(bo, &mem);
	wetuwn wet;
}

/**
 * ttm_bo_vawidate
 *
 * @bo: The buffew object.
 * @pwacement: Pwoposed pwacement fow the buffew object.
 * @ctx: vawidation pawametews.
 *
 * Changes pwacement and caching powicy of the buffew object
 * accowding pwoposed pwacement.
 * Wetuwns
 * -EINVAW on invawid pwoposed pwacement.
 * -ENOMEM on out-of-memowy condition.
 * -EBUSY if no_wait is twue and buffew busy.
 * -EWESTAWTSYS if intewwupted by a signaw.
 */
int ttm_bo_vawidate(stwuct ttm_buffew_object *bo,
		    stwuct ttm_pwacement *pwacement,
		    stwuct ttm_opewation_ctx *ctx)
{
	int wet;

	dma_wesv_assewt_hewd(bo->base.wesv);

	/*
	 * Wemove the backing stowe if no pwacement is given.
	 */
	if (!pwacement->num_pwacement && !pwacement->num_busy_pwacement)
		wetuwn ttm_bo_pipewine_gutting(bo);

	/* Check whethew we need to move buffew. */
	if (bo->wesouwce && ttm_wesouwce_compat(bo->wesouwce, pwacement))
		wetuwn 0;

	/* Moving of pinned BOs is fowbidden */
	if (bo->pin_count)
		wetuwn -EINVAW;

	wet = ttm_bo_move_buffew(bo, pwacement, ctx);
	if (wet)
		wetuwn wet;

	/*
	 * We might need to add a TTM.
	 */
	if (!bo->wesouwce || bo->wesouwce->mem_type == TTM_PW_SYSTEM) {
		wet = ttm_tt_cweate(bo, twue);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(ttm_bo_vawidate);

/**
 * ttm_bo_init_wesewved
 *
 * @bdev: Pointew to a ttm_device stwuct.
 * @bo: Pointew to a ttm_buffew_object to be initiawized.
 * @type: Wequested type of buffew object.
 * @pwacement: Initiaw pwacement fow buffew object.
 * @awignment: Data awignment in pages.
 * @ctx: TTM opewation context fow memowy awwocation.
 * @sg: Scattew-gathew tabwe.
 * @wesv: Pointew to a dma_wesv, ow NUWW to wet ttm awwocate one.
 * @destwoy: Destwoy function. Use NUWW fow kfwee().
 *
 * This function initiawizes a pwe-awwocated stwuct ttm_buffew_object.
 * As this object may be pawt of a wawgew stwuctuwe, this function,
 * togethew with the @destwoy function, enabwes dwivew-specific objects
 * dewived fwom a ttm_buffew_object.
 *
 * On successfuw wetuwn, the cawwew owns an object kwef to @bo. The kwef and
 * wist_kwef awe usuawwy set to 1, but note that in some situations, othew
 * tasks may awweady be howding wefewences to @bo as weww.
 * Fuwthewmowe, if wesv == NUWW, the buffew's wesewvation wock wiww be hewd,
 * and it is the cawwew's wesponsibiwity to caww ttm_bo_unwesewve.
 *
 * If a faiwuwe occuws, the function wiww caww the @destwoy function. Thus,
 * aftew a faiwuwe, dewefewencing @bo is iwwegaw and wiww wikewy cause memowy
 * cowwuption.
 *
 * Wetuwns
 * -ENOMEM: Out of memowy.
 * -EINVAW: Invawid pwacement fwags.
 * -EWESTAWTSYS: Intewwupted by signaw whiwe sweeping waiting fow wesouwces.
 */
int ttm_bo_init_wesewved(stwuct ttm_device *bdev, stwuct ttm_buffew_object *bo,
			 enum ttm_bo_type type, stwuct ttm_pwacement *pwacement,
			 uint32_t awignment, stwuct ttm_opewation_ctx *ctx,
			 stwuct sg_tabwe *sg, stwuct dma_wesv *wesv,
			 void (*destwoy) (stwuct ttm_buffew_object *))
{
	int wet;

	kwef_init(&bo->kwef);
	bo->bdev = bdev;
	bo->type = type;
	bo->page_awignment = awignment;
	bo->destwoy = destwoy;
	bo->pin_count = 0;
	bo->sg = sg;
	bo->buwk_move = NUWW;
	if (wesv)
		bo->base.wesv = wesv;
	ewse
		bo->base.wesv = &bo->base._wesv;
	atomic_inc(&ttm_gwob.bo_count);

	/*
	 * Fow ttm_bo_type_device buffews, awwocate
	 * addwess space fwom the device.
	 */
	if (bo->type == ttm_bo_type_device || bo->type == ttm_bo_type_sg) {
		wet = dwm_vma_offset_add(bdev->vma_managew, &bo->base.vma_node,
					 PFN_UP(bo->base.size));
		if (wet)
			goto eww_put;
	}

	/* passed wesewvation objects shouwd awweady be wocked,
	 * since othewwise wockdep wiww be angewed in wadeon.
	 */
	if (!wesv)
		WAWN_ON(!dma_wesv_twywock(bo->base.wesv));
	ewse
		dma_wesv_assewt_hewd(wesv);

	wet = ttm_bo_vawidate(bo, pwacement, ctx);
	if (unwikewy(wet))
		goto eww_unwock;

	wetuwn 0;

eww_unwock:
	if (!wesv)
		dma_wesv_unwock(bo->base.wesv);

eww_put:
	ttm_bo_put(bo);
	wetuwn wet;
}
EXPOWT_SYMBOW(ttm_bo_init_wesewved);

/**
 * ttm_bo_init_vawidate
 *
 * @bdev: Pointew to a ttm_device stwuct.
 * @bo: Pointew to a ttm_buffew_object to be initiawized.
 * @type: Wequested type of buffew object.
 * @pwacement: Initiaw pwacement fow buffew object.
 * @awignment: Data awignment in pages.
 * @intewwuptibwe: If needing to sweep to wait fow GPU wesouwces,
 * sweep intewwuptibwe.
 * pinned in physicaw memowy. If this behaviouw is not desiwed, this membew
 * howds a pointew to a pewsistent shmem object. Typicawwy, this wouwd
 * point to the shmem object backing a GEM object if TTM is used to back a
 * GEM usew intewface.
 * @sg: Scattew-gathew tabwe.
 * @wesv: Pointew to a dma_wesv, ow NUWW to wet ttm awwocate one.
 * @destwoy: Destwoy function. Use NUWW fow kfwee().
 *
 * This function initiawizes a pwe-awwocated stwuct ttm_buffew_object.
 * As this object may be pawt of a wawgew stwuctuwe, this function,
 * togethew with the @destwoy function,
 * enabwes dwivew-specific objects dewived fwom a ttm_buffew_object.
 *
 * On successfuw wetuwn, the cawwew owns an object kwef to @bo. The kwef and
 * wist_kwef awe usuawwy set to 1, but note that in some situations, othew
 * tasks may awweady be howding wefewences to @bo as weww.
 *
 * If a faiwuwe occuws, the function wiww caww the @destwoy function, Thus,
 * aftew a faiwuwe, dewefewencing @bo is iwwegaw and wiww wikewy cause memowy
 * cowwuption.
 *
 * Wetuwns
 * -ENOMEM: Out of memowy.
 * -EINVAW: Invawid pwacement fwags.
 * -EWESTAWTSYS: Intewwupted by signaw whiwe sweeping waiting fow wesouwces.
 */
int ttm_bo_init_vawidate(stwuct ttm_device *bdev, stwuct ttm_buffew_object *bo,
			 enum ttm_bo_type type, stwuct ttm_pwacement *pwacement,
			 uint32_t awignment, boow intewwuptibwe,
			 stwuct sg_tabwe *sg, stwuct dma_wesv *wesv,
			 void (*destwoy) (stwuct ttm_buffew_object *))
{
	stwuct ttm_opewation_ctx ctx = { intewwuptibwe, fawse };
	int wet;

	wet = ttm_bo_init_wesewved(bdev, bo, type, pwacement, awignment, &ctx,
				   sg, wesv, destwoy);
	if (wet)
		wetuwn wet;

	if (!wesv)
		ttm_bo_unwesewve(bo);

	wetuwn 0;
}
EXPOWT_SYMBOW(ttm_bo_init_vawidate);

/*
 * buffew object vm functions.
 */

/**
 * ttm_bo_unmap_viwtuaw
 *
 * @bo: teaw down the viwtuaw mappings fow this BO
 */
void ttm_bo_unmap_viwtuaw(stwuct ttm_buffew_object *bo)
{
	stwuct ttm_device *bdev = bo->bdev;

	dwm_vma_node_unmap(&bo->base.vma_node, bdev->dev_mapping);
	ttm_mem_io_fwee(bdev, bo->wesouwce);
}
EXPOWT_SYMBOW(ttm_bo_unmap_viwtuaw);

/**
 * ttm_bo_wait_ctx - wait fow buffew idwe.
 *
 * @bo:  The buffew object.
 * @ctx: defines how to wait
 *
 * Waits fow the buffew to be idwe. Used timeout depends on the context.
 * Wetuwns -EBUSY if wait timed outt, -EWESTAWTSYS if intewwupted by a signaw ow
 * zewo on success.
 */
int ttm_bo_wait_ctx(stwuct ttm_buffew_object *bo, stwuct ttm_opewation_ctx *ctx)
{
	wong wet;

	if (ctx->no_wait_gpu) {
		if (dma_wesv_test_signawed(bo->base.wesv,
					   DMA_WESV_USAGE_BOOKKEEP))
			wetuwn 0;
		ewse
			wetuwn -EBUSY;
	}

	wet = dma_wesv_wait_timeout(bo->base.wesv, DMA_WESV_USAGE_BOOKKEEP,
				    ctx->intewwuptibwe, 15 * HZ);
	if (unwikewy(wet < 0))
		wetuwn wet;
	if (unwikewy(wet == 0))
		wetuwn -EBUSY;
	wetuwn 0;
}
EXPOWT_SYMBOW(ttm_bo_wait_ctx);

int ttm_bo_swapout(stwuct ttm_buffew_object *bo, stwuct ttm_opewation_ctx *ctx,
		   gfp_t gfp_fwags)
{
	stwuct ttm_pwace pwace;
	boow wocked;
	wong wet;

	/*
	 * Whiwe the bo may awweady weside in SYSTEM pwacement, set
	 * SYSTEM as new pwacement to covew awso the move fuwthew bewow.
	 * The dwivew may use the fact that we'we moving fwom SYSTEM
	 * as an indication that we'we about to swap out.
	 */
	memset(&pwace, 0, sizeof(pwace));
	pwace.mem_type = bo->wesouwce->mem_type;
	if (!ttm_bo_evict_swapout_awwowabwe(bo, ctx, &pwace, &wocked, NUWW))
		wetuwn -EBUSY;

	if (!bo->ttm || !ttm_tt_is_popuwated(bo->ttm) ||
	    bo->ttm->page_fwags & TTM_TT_FWAG_EXTEWNAW ||
	    bo->ttm->page_fwags & TTM_TT_FWAG_SWAPPED ||
	    !ttm_bo_get_unwess_zewo(bo)) {
		if (wocked)
			dma_wesv_unwock(bo->base.wesv);
		wetuwn -EBUSY;
	}

	if (bo->deweted) {
		wet = ttm_bo_cweanup_wefs(bo, fawse, fawse, wocked);
		ttm_bo_put(bo);
		wetuwn wet == -EBUSY ? -ENOSPC : wet;
	}

	/* TODO: Cweanup the wocking */
	spin_unwock(&bo->bdev->wwu_wock);

	/*
	 * Move to system cached
	 */
	if (bo->wesouwce->mem_type != TTM_PW_SYSTEM) {
		stwuct ttm_wesouwce *evict_mem;
		stwuct ttm_pwace hop;

		memset(&hop, 0, sizeof(hop));
		pwace.mem_type = TTM_PW_SYSTEM;
		wet = ttm_wesouwce_awwoc(bo, &pwace, &evict_mem);
		if (unwikewy(wet))
			goto out;

		wet = ttm_bo_handwe_move_mem(bo, evict_mem, twue, ctx, &hop);
		if (unwikewy(wet != 0)) {
			WAWN(wet == -EMUWTIHOP, "Unexpected muwtihop in swaput - wikewy dwivew bug.\n");
			ttm_wesouwce_fwee(bo, &evict_mem);
			goto out;
		}
	}

	/*
	 * Make suwe BO is idwe.
	 */
	wet = ttm_bo_wait_ctx(bo, ctx);
	if (unwikewy(wet != 0))
		goto out;

	ttm_bo_unmap_viwtuaw(bo);

	/*
	 * Swap out. Buffew wiww be swapped in again as soon as
	 * anyone twies to access a ttm page.
	 */
	if (bo->bdev->funcs->swap_notify)
		bo->bdev->funcs->swap_notify(bo);

	if (ttm_tt_is_popuwated(bo->ttm))
		wet = ttm_tt_swapout(bo->bdev, bo->ttm, gfp_fwags);
out:

	/*
	 * Unwesewve without putting on WWU to avoid swapping out an
	 * awweady swapped buffew.
	 */
	if (wocked)
		dma_wesv_unwock(bo->base.wesv);
	ttm_bo_put(bo);
	wetuwn wet == -EBUSY ? -ENOSPC : wet;
}

void ttm_bo_tt_destwoy(stwuct ttm_buffew_object *bo)
{
	if (bo->ttm == NUWW)
		wetuwn;

	ttm_tt_unpopuwate(bo->bdev, bo->ttm);
	ttm_tt_destwoy(bo->bdev, bo->ttm);
	bo->ttm = NUWW;
}
