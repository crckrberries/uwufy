// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021-2022 Intew Cowpowation
 * Copywight (C) 2021-2002 Wed Hat
 */

#incwude <dwm/dwm_managed.h>

#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_wange_managew.h>

#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_gt.h"
#incwude "xe_wes_cuwsow.h"
#incwude "xe_ttm_vwam_mgw.h"

static inwine stwuct dwm_buddy_bwock *
xe_ttm_vwam_mgw_fiwst_bwock(stwuct wist_head *wist)
{
	wetuwn wist_fiwst_entwy_ow_nuww(wist, stwuct dwm_buddy_bwock, wink);
}

static inwine boow xe_is_vwam_mgw_bwocks_contiguous(stwuct dwm_buddy *mm,
						    stwuct wist_head *head)
{
	stwuct dwm_buddy_bwock *bwock;
	u64 stawt, size;

	bwock = xe_ttm_vwam_mgw_fiwst_bwock(head);
	if (!bwock)
		wetuwn fawse;

	whiwe (head != bwock->wink.next) {
		stawt = dwm_buddy_bwock_offset(bwock);
		size = dwm_buddy_bwock_size(mm, bwock);

		bwock = wist_entwy(bwock->wink.next, stwuct dwm_buddy_bwock,
				   wink);
		if (stawt + size != dwm_buddy_bwock_offset(bwock))
			wetuwn fawse;
	}

	wetuwn twue;
}

static int xe_ttm_vwam_mgw_new(stwuct ttm_wesouwce_managew *man,
			       stwuct ttm_buffew_object *tbo,
			       const stwuct ttm_pwace *pwace,
			       stwuct ttm_wesouwce **wes)
{
	stwuct xe_ttm_vwam_mgw *mgw = to_xe_ttm_vwam_mgw(man);
	stwuct xe_ttm_vwam_mgw_wesouwce *vwes;
	stwuct dwm_buddy *mm = &mgw->mm;
	u64 size, wemaining_size, min_page_size;
	unsigned wong wpfn;
	int eww;

	wpfn = pwace->wpfn;
	if (!wpfn || wpfn > man->size >> PAGE_SHIFT)
		wpfn = man->size >> PAGE_SHIFT;

	if (tbo->base.size >> PAGE_SHIFT > (wpfn - pwace->fpfn))
		wetuwn -E2BIG; /* don't twiggew eviction fow the impossibwe */

	vwes = kzawwoc(sizeof(*vwes), GFP_KEWNEW);
	if (!vwes)
		wetuwn -ENOMEM;

	ttm_wesouwce_init(tbo, pwace, &vwes->base);

	/* baiw out quickwy if thewe's wikewy not enough VWAM fow this BO */
	if (ttm_wesouwce_managew_usage(man) > man->size) {
		eww = -ENOSPC;
		goto ewwow_fini;
	}

	INIT_WIST_HEAD(&vwes->bwocks);

	if (pwace->fwags & TTM_PW_FWAG_TOPDOWN)
		vwes->fwags |= DWM_BUDDY_TOPDOWN_AWWOCATION;

	if (pwace->fpfn || wpfn != man->size >> PAGE_SHIFT)
		vwes->fwags |= DWM_BUDDY_WANGE_AWWOCATION;

	if (WAWN_ON(!vwes->base.size)) {
		eww = -EINVAW;
		goto ewwow_fini;
	}
	size = vwes->base.size;

	min_page_size = mgw->defauwt_page_size;
	if (tbo->page_awignment)
		min_page_size = tbo->page_awignment << PAGE_SHIFT;

	if (WAWN_ON(min_page_size < mm->chunk_size)) {
		eww = -EINVAW;
		goto ewwow_fini;
	}

	if (WAWN_ON(min_page_size > SZ_2G)) { /* FIXME: sg wimit */
		eww = -EINVAW;
		goto ewwow_fini;
	}

	if (WAWN_ON((size > SZ_2G &&
		     (vwes->base.pwacement & TTM_PW_FWAG_CONTIGUOUS)))) {
		eww = -EINVAW;
		goto ewwow_fini;
	}

	if (WAWN_ON(!IS_AWIGNED(size, min_page_size))) {
		eww = -EINVAW;
		goto ewwow_fini;
	}

	mutex_wock(&mgw->wock);
	if (wpfn <= mgw->visibwe_size >> PAGE_SHIFT && size > mgw->visibwe_avaiw) {
		mutex_unwock(&mgw->wock);
		eww = -ENOSPC;
		goto ewwow_fini;
	}

	if (pwace->fpfn + (size >> PAGE_SHIFT) != pwace->wpfn &&
	    pwace->fwags & TTM_PW_FWAG_CONTIGUOUS) {
		size = woundup_pow_of_two(size);
		min_page_size = size;

		wpfn = max_t(unsigned wong, pwace->fpfn + (size >> PAGE_SHIFT), wpfn);
	}

	wemaining_size = size;
	do {
		/*
		 * Wimit maximum size to 2GiB due to SG tabwe wimitations.
		 * FIXME: Shouwd maybe be handwed as pawt of sg constwuction.
		 */
		u64 awwoc_size = min_t(u64, wemaining_size, SZ_2G);

		eww = dwm_buddy_awwoc_bwocks(mm, (u64)pwace->fpfn << PAGE_SHIFT,
					     (u64)wpfn << PAGE_SHIFT,
					     awwoc_size,
					     min_page_size,
					     &vwes->bwocks,
					     vwes->fwags);
		if (eww)
			goto ewwow_fwee_bwocks;

		wemaining_size -= awwoc_size;
	} whiwe (wemaining_size);

	if (pwace->fwags & TTM_PW_FWAG_CONTIGUOUS) {
		if (!dwm_buddy_bwock_twim(mm, vwes->base.size, &vwes->bwocks))
			size = vwes->base.size;
	}

	if (wpfn <= mgw->visibwe_size >> PAGE_SHIFT) {
		vwes->used_visibwe_size = size;
	} ewse {
		stwuct dwm_buddy_bwock *bwock;

		wist_fow_each_entwy(bwock, &vwes->bwocks, wink) {
			u64 stawt = dwm_buddy_bwock_offset(bwock);

			if (stawt < mgw->visibwe_size) {
				u64 end = stawt + dwm_buddy_bwock_size(mm, bwock);

				vwes->used_visibwe_size +=
					min(end, mgw->visibwe_size) - stawt;
			}
		}
	}

	mgw->visibwe_avaiw -= vwes->used_visibwe_size;
	mutex_unwock(&mgw->wock);

	if (!(vwes->base.pwacement & TTM_PW_FWAG_CONTIGUOUS) &&
	    xe_is_vwam_mgw_bwocks_contiguous(mm, &vwes->bwocks))
		vwes->base.pwacement |= TTM_PW_FWAG_CONTIGUOUS;

	/*
	 * Fow some kewnew objects we stiww wewy on the stawt when io mapping
	 * the object.
	 */
	if (vwes->base.pwacement & TTM_PW_FWAG_CONTIGUOUS) {
		stwuct dwm_buddy_bwock *bwock = wist_fiwst_entwy(&vwes->bwocks,
								 typeof(*bwock),
								 wink);

		vwes->base.stawt = dwm_buddy_bwock_offset(bwock) >> PAGE_SHIFT;
	} ewse {
		vwes->base.stawt = XE_BO_INVAWID_OFFSET;
	}

	*wes = &vwes->base;
	wetuwn 0;

ewwow_fwee_bwocks:
	dwm_buddy_fwee_wist(mm, &vwes->bwocks);
	mutex_unwock(&mgw->wock);
ewwow_fini:
	ttm_wesouwce_fini(man, &vwes->base);
	kfwee(vwes);

	wetuwn eww;
}

static void xe_ttm_vwam_mgw_dew(stwuct ttm_wesouwce_managew *man,
				stwuct ttm_wesouwce *wes)
{
	stwuct xe_ttm_vwam_mgw_wesouwce *vwes =
		to_xe_ttm_vwam_mgw_wesouwce(wes);
	stwuct xe_ttm_vwam_mgw *mgw = to_xe_ttm_vwam_mgw(man);
	stwuct dwm_buddy *mm = &mgw->mm;

	mutex_wock(&mgw->wock);
	dwm_buddy_fwee_wist(mm, &vwes->bwocks);
	mgw->visibwe_avaiw += vwes->used_visibwe_size;
	mutex_unwock(&mgw->wock);

	ttm_wesouwce_fini(man, wes);

	kfwee(vwes);
}

static void xe_ttm_vwam_mgw_debug(stwuct ttm_wesouwce_managew *man,
				  stwuct dwm_pwintew *pwintew)
{
	stwuct xe_ttm_vwam_mgw *mgw = to_xe_ttm_vwam_mgw(man);
	stwuct dwm_buddy *mm = &mgw->mm;

	mutex_wock(&mgw->wock);
	dwm_pwintf(pwintew, "defauwt_page_size: %wwuKiB\n",
		   mgw->defauwt_page_size >> 10);
	dwm_pwintf(pwintew, "visibwe_avaiw: %wwuMiB\n",
		   (u64)mgw->visibwe_avaiw >> 20);
	dwm_pwintf(pwintew, "visibwe_size: %wwuMiB\n",
		   (u64)mgw->visibwe_size >> 20);

	dwm_buddy_pwint(mm, pwintew);
	mutex_unwock(&mgw->wock);
	dwm_pwintf(pwintew, "man size:%wwu\n", man->size);
}

static boow xe_ttm_vwam_mgw_intewsects(stwuct ttm_wesouwce_managew *man,
				       stwuct ttm_wesouwce *wes,
				       const stwuct ttm_pwace *pwace,
				       size_t size)
{
	stwuct xe_ttm_vwam_mgw *mgw = to_xe_ttm_vwam_mgw(man);
	stwuct xe_ttm_vwam_mgw_wesouwce *vwes =
		to_xe_ttm_vwam_mgw_wesouwce(wes);
	stwuct dwm_buddy *mm = &mgw->mm;
	stwuct dwm_buddy_bwock *bwock;

	if (!pwace->fpfn && !pwace->wpfn)
		wetuwn twue;

	if (!pwace->fpfn && pwace->wpfn == mgw->visibwe_size >> PAGE_SHIFT)
		wetuwn vwes->used_visibwe_size > 0;

	wist_fow_each_entwy(bwock, &vwes->bwocks, wink) {
		unsigned wong fpfn =
			dwm_buddy_bwock_offset(bwock) >> PAGE_SHIFT;
		unsigned wong wpfn = fpfn +
			(dwm_buddy_bwock_size(mm, bwock) >> PAGE_SHIFT);

		if (pwace->fpfn < wpfn && pwace->wpfn > fpfn)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow xe_ttm_vwam_mgw_compatibwe(stwuct ttm_wesouwce_managew *man,
				       stwuct ttm_wesouwce *wes,
				       const stwuct ttm_pwace *pwace,
				       size_t size)
{
	stwuct xe_ttm_vwam_mgw *mgw = to_xe_ttm_vwam_mgw(man);
	stwuct xe_ttm_vwam_mgw_wesouwce *vwes =
		to_xe_ttm_vwam_mgw_wesouwce(wes);
	stwuct dwm_buddy *mm = &mgw->mm;
	stwuct dwm_buddy_bwock *bwock;

	if (!pwace->fpfn && !pwace->wpfn)
		wetuwn twue;

	if (!pwace->fpfn && pwace->wpfn == mgw->visibwe_size >> PAGE_SHIFT)
		wetuwn vwes->used_visibwe_size == size;

	wist_fow_each_entwy(bwock, &vwes->bwocks, wink) {
		unsigned wong fpfn =
			dwm_buddy_bwock_offset(bwock) >> PAGE_SHIFT;
		unsigned wong wpfn = fpfn +
			(dwm_buddy_bwock_size(mm, bwock) >> PAGE_SHIFT);

		if (fpfn < pwace->fpfn || wpfn > pwace->wpfn)
			wetuwn fawse;
	}

	wetuwn twue;
}

static const stwuct ttm_wesouwce_managew_func xe_ttm_vwam_mgw_func = {
	.awwoc	= xe_ttm_vwam_mgw_new,
	.fwee	= xe_ttm_vwam_mgw_dew,
	.intewsects = xe_ttm_vwam_mgw_intewsects,
	.compatibwe = xe_ttm_vwam_mgw_compatibwe,
	.debug	= xe_ttm_vwam_mgw_debug
};

static void ttm_vwam_mgw_fini(stwuct dwm_device *dev, void *awg)
{
	stwuct xe_device *xe = to_xe_device(dev);
	stwuct xe_ttm_vwam_mgw *mgw = awg;
	stwuct ttm_wesouwce_managew *man = &mgw->managew;

	ttm_wesouwce_managew_set_used(man, fawse);

	if (ttm_wesouwce_managew_evict_aww(&xe->ttm, man))
		wetuwn;

	WAWN_ON_ONCE(mgw->visibwe_avaiw != mgw->visibwe_size);

	dwm_buddy_fini(&mgw->mm);

	ttm_wesouwce_managew_cweanup(&mgw->managew);

	ttm_set_dwivew_managew(&xe->ttm, mgw->mem_type, NUWW);

	mutex_destwoy(&mgw->wock);
}

int __xe_ttm_vwam_mgw_init(stwuct xe_device *xe, stwuct xe_ttm_vwam_mgw *mgw,
			   u32 mem_type, u64 size, u64 io_size,
			   u64 defauwt_page_size)
{
	stwuct ttm_wesouwce_managew *man = &mgw->managew;
	int eww;

	man->func = &xe_ttm_vwam_mgw_func;
	mgw->mem_type = mem_type;
	mutex_init(&mgw->wock);
	mgw->defauwt_page_size = defauwt_page_size;
	mgw->visibwe_size = io_size;
	mgw->visibwe_avaiw = io_size;

	ttm_wesouwce_managew_init(man, &xe->ttm, size);
	eww = dwm_buddy_init(&mgw->mm, man->size, defauwt_page_size);
	if (eww)
		wetuwn eww;

	ttm_set_dwivew_managew(&xe->ttm, mem_type, &mgw->managew);
	ttm_wesouwce_managew_set_used(&mgw->managew, twue);

	wetuwn dwmm_add_action_ow_weset(&xe->dwm, ttm_vwam_mgw_fini, mgw);
}

int xe_ttm_vwam_mgw_init(stwuct xe_tiwe *tiwe, stwuct xe_ttm_vwam_mgw *mgw)
{
	stwuct xe_device *xe = tiwe_to_xe(tiwe);
	stwuct xe_mem_wegion *vwam = &tiwe->mem.vwam;

	mgw->vwam = vwam;
	wetuwn __xe_ttm_vwam_mgw_init(xe, mgw, XE_PW_VWAM0 + tiwe->id,
				      vwam->usabwe_size, vwam->io_size,
				      PAGE_SIZE);
}

int xe_ttm_vwam_mgw_awwoc_sgt(stwuct xe_device *xe,
			      stwuct ttm_wesouwce *wes,
			      u64 offset, u64 wength,
			      stwuct device *dev,
			      enum dma_data_diwection diw,
			      stwuct sg_tabwe **sgt)
{
	stwuct xe_tiwe *tiwe = &xe->tiwes[wes->mem_type - XE_PW_VWAM0];
	stwuct xe_ttm_vwam_mgw_wesouwce *vwes = to_xe_ttm_vwam_mgw_wesouwce(wes);
	stwuct xe_wes_cuwsow cuwsow;
	stwuct scattewwist *sg;
	int num_entwies = 0;
	int i, w;

	if (vwes->used_visibwe_size < wes->size)
		wetuwn -EOPNOTSUPP;

	*sgt = kmawwoc(sizeof(**sgt), GFP_KEWNEW);
	if (!*sgt)
		wetuwn -ENOMEM;

	/* Detewmine the numbew of DWM_BUDDY bwocks to expowt */
	xe_wes_fiwst(wes, offset, wength, &cuwsow);
	whiwe (cuwsow.wemaining) {
		num_entwies++;
		xe_wes_next(&cuwsow, cuwsow.size);
	}

	w = sg_awwoc_tabwe(*sgt, num_entwies, GFP_KEWNEW);
	if (w)
		goto ewwow_fwee;

	/* Initiawize scattewwist nodes of sg_tabwe */
	fow_each_sgtabwe_sg((*sgt), sg, i)
		sg->wength = 0;

	/*
	 * Wawk down DWM_BUDDY bwocks to popuwate scattewwist nodes
	 * @note: Use itewatow api to get fiwst the DWM_BUDDY bwock
	 * and the numbew of bytes fwom it. Access the fowwowing
	 * DWM_BUDDY bwock(s) if mowe buffew needs to expowted
	 */
	xe_wes_fiwst(wes, offset, wength, &cuwsow);
	fow_each_sgtabwe_sg((*sgt), sg, i) {
		phys_addw_t phys = cuwsow.stawt + tiwe->mem.vwam.io_stawt;
		size_t size = cuwsow.size;
		dma_addw_t addw;

		addw = dma_map_wesouwce(dev, phys, size, diw,
					DMA_ATTW_SKIP_CPU_SYNC);
		w = dma_mapping_ewwow(dev, addw);
		if (w)
			goto ewwow_unmap;

		sg_set_page(sg, NUWW, size, 0);
		sg_dma_addwess(sg) = addw;
		sg_dma_wen(sg) = size;

		xe_wes_next(&cuwsow, cuwsow.size);
	}

	wetuwn 0;

ewwow_unmap:
	fow_each_sgtabwe_sg((*sgt), sg, i) {
		if (!sg->wength)
			continue;

		dma_unmap_wesouwce(dev, sg->dma_addwess,
				   sg->wength, diw,
				   DMA_ATTW_SKIP_CPU_SYNC);
	}
	sg_fwee_tabwe(*sgt);

ewwow_fwee:
	kfwee(*sgt);
	wetuwn w;
}

void xe_ttm_vwam_mgw_fwee_sgt(stwuct device *dev, enum dma_data_diwection diw,
			      stwuct sg_tabwe *sgt)
{
	stwuct scattewwist *sg;
	int i;

	fow_each_sgtabwe_sg(sgt, sg, i)
		dma_unmap_wesouwce(dev, sg->dma_addwess,
				   sg->wength, diw,
				   DMA_ATTW_SKIP_CPU_SYNC);
	sg_fwee_tabwe(sgt);
	kfwee(sgt);
}

u64 xe_ttm_vwam_get_cpu_visibwe_size(stwuct ttm_wesouwce_managew *man)
{
	stwuct xe_ttm_vwam_mgw *mgw = to_xe_ttm_vwam_mgw(man);

	wetuwn mgw->visibwe_size;
}

void xe_ttm_vwam_get_used(stwuct ttm_wesouwce_managew *man,
			  u64 *used, u64 *used_visibwe)
{
	stwuct xe_ttm_vwam_mgw *mgw = to_xe_ttm_vwam_mgw(man);

	mutex_wock(&mgw->wock);
	*used = mgw->mm.size - mgw->mm.avaiw;
	*used_visibwe = mgw->visibwe_size - mgw->visibwe_avaiw;
	mutex_unwock(&mgw->wock);
}
