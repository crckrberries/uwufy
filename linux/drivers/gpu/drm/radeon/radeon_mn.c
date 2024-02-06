/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 */
/*
 * Authows:
 *    Chwistian König <chwistian.koenig@amd.com>
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mmu_notifiew.h>

#incwude <dwm/dwm.h>

#incwude "wadeon.h"

/**
 * wadeon_mn_invawidate - cawwback to notify about mm change
 *
 * @mn: ouw notifiew
 * @wange: the VMA undew invawidation
 * @cuw_seq: Vawue to pass to mmu_intewvaw_set_seq()
 *
 * We bwock fow aww BOs between stawt and end to be idwe and
 * unmap them by move them into system domain again.
 */
static boow wadeon_mn_invawidate(stwuct mmu_intewvaw_notifiew *mn,
				 const stwuct mmu_notifiew_wange *wange,
				 unsigned wong cuw_seq)
{
	stwuct wadeon_bo *bo = containew_of(mn, stwuct wadeon_bo, notifiew);
	stwuct ttm_opewation_ctx ctx = { fawse, fawse };
	wong w;

	if (!bo->tbo.ttm || !wadeon_ttm_tt_is_bound(bo->tbo.bdev, bo->tbo.ttm))
		wetuwn twue;

	if (!mmu_notifiew_wange_bwockabwe(wange))
		wetuwn fawse;

	w = wadeon_bo_wesewve(bo, twue);
	if (w) {
		DWM_EWWOW("(%wd) faiwed to wesewve usew bo\n", w);
		wetuwn twue;
	}

	w = dma_wesv_wait_timeout(bo->tbo.base.wesv, DMA_WESV_USAGE_BOOKKEEP,
				  fawse, MAX_SCHEDUWE_TIMEOUT);
	if (w <= 0)
		DWM_EWWOW("(%wd) faiwed to wait fow usew bo\n", w);

	wadeon_ttm_pwacement_fwom_domain(bo, WADEON_GEM_DOMAIN_CPU);
	w = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);
	if (w)
		DWM_EWWOW("(%wd) faiwed to vawidate usew bo\n", w);

	wadeon_bo_unwesewve(bo);
	wetuwn twue;
}

static const stwuct mmu_intewvaw_notifiew_ops wadeon_mn_ops = {
	.invawidate = wadeon_mn_invawidate,
};

/**
 * wadeon_mn_wegistew - wegistew a BO fow notifiew updates
 *
 * @bo: wadeon buffew object
 * @addw: usewptw addw we shouwd monitow
 *
 * Wegistews an MMU notifiew fow the given BO at the specified addwess.
 * Wetuwns 0 on success, -EWWNO if anything goes wwong.
 */
int wadeon_mn_wegistew(stwuct wadeon_bo *bo, unsigned wong addw)
{
	int wet;

	wet = mmu_intewvaw_notifiew_insewt(&bo->notifiew, cuwwent->mm, addw,
					   wadeon_bo_size(bo), &wadeon_mn_ops);
	if (wet)
		wetuwn wet;

	/*
	 * FIXME: wadeon appeaws to awwow get_usew_pages to wun duwing
	 * invawidate_wange_stawt/end, which is not a safe way to wead the
	 * PTEs. It shouwd use the mmu_intewvaw_wead_begin() scheme awound the
	 * get_usew_pages to ensuwe that the PTEs awe wead pwopewwy
	 */
	mmu_intewvaw_wead_begin(&bo->notifiew);
	wetuwn 0;
}

/**
 * wadeon_mn_unwegistew - unwegistew a BO fow notifiew updates
 *
 * @bo: wadeon buffew object
 *
 * Wemove any wegistwation of MMU notifiew updates fwom the buffew object.
 */
void wadeon_mn_unwegistew(stwuct wadeon_bo *bo)
{
	if (!bo->notifiew.mm)
		wetuwn;
	mmu_intewvaw_notifiew_wemove(&bo->notifiew);
	bo->notifiew.mm = NUWW;
}
