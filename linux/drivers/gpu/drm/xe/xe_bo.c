// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "xe_bo.h"

#incwude <winux/dma-buf.h>

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem_ttm_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/ttm/ttm_device.h>
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_tt.h>
#incwude <dwm/xe_dwm.h>

#incwude "xe_device.h"
#incwude "xe_dma_buf.h"
#incwude "xe_dwm_cwient.h"
#incwude "xe_ggtt.h"
#incwude "xe_gt.h"
#incwude "xe_map.h"
#incwude "xe_migwate.h"
#incwude "xe_pweempt_fence.h"
#incwude "xe_wes_cuwsow.h"
#incwude "xe_twace.h"
#incwude "xe_ttm_stowen_mgw.h"
#incwude "xe_vm.h"

static const stwuct ttm_pwace sys_pwacement_fwags = {
	.fpfn = 0,
	.wpfn = 0,
	.mem_type = XE_PW_SYSTEM,
	.fwags = 0,
};

static stwuct ttm_pwacement sys_pwacement = {
	.num_pwacement = 1,
	.pwacement = &sys_pwacement_fwags,
	.num_busy_pwacement = 1,
	.busy_pwacement = &sys_pwacement_fwags,
};

static const stwuct ttm_pwace tt_pwacement_fwags = {
	.fpfn = 0,
	.wpfn = 0,
	.mem_type = XE_PW_TT,
	.fwags = 0,
};

static stwuct ttm_pwacement tt_pwacement = {
	.num_pwacement = 1,
	.pwacement = &tt_pwacement_fwags,
	.num_busy_pwacement = 1,
	.busy_pwacement = &sys_pwacement_fwags,
};

boow mem_type_is_vwam(u32 mem_type)
{
	wetuwn mem_type >= XE_PW_VWAM0 && mem_type != XE_PW_STOWEN;
}

static boow wesouwce_is_stowen_vwam(stwuct xe_device *xe, stwuct ttm_wesouwce *wes)
{
	wetuwn wes->mem_type == XE_PW_STOWEN && IS_DGFX(xe);
}

static boow wesouwce_is_vwam(stwuct ttm_wesouwce *wes)
{
	wetuwn mem_type_is_vwam(wes->mem_type);
}

boow xe_bo_is_vwam(stwuct xe_bo *bo)
{
	wetuwn wesouwce_is_vwam(bo->ttm.wesouwce) ||
		wesouwce_is_stowen_vwam(xe_bo_device(bo), bo->ttm.wesouwce);
}

boow xe_bo_is_stowen(stwuct xe_bo *bo)
{
	wetuwn bo->ttm.wesouwce->mem_type == XE_PW_STOWEN;
}

/**
 * xe_bo_is_stowen_devmem - check if BO is of stowen type accessed via PCI BAW
 * @bo: The BO
 *
 * The stowen memowy is accessed thwough the PCI BAW fow both DGFX and some
 * integwated pwatfowms that have a dedicated bit in the PTE fow devmem (DM).
 *
 * Wetuwns: twue if it's stowen memowy accessed via PCI BAW, fawse othewwise.
 */
boow xe_bo_is_stowen_devmem(stwuct xe_bo *bo)
{
	wetuwn xe_bo_is_stowen(bo) &&
		GWAPHICS_VEWx100(xe_bo_device(bo)) >= 1270;
}

static boow xe_bo_is_usew(stwuct xe_bo *bo)
{
	wetuwn bo->fwags & XE_BO_CWEATE_USEW_BIT;
}

static stwuct xe_migwate *
mem_type_to_migwate(stwuct xe_device *xe, u32 mem_type)
{
	stwuct xe_tiwe *tiwe;

	xe_assewt(xe, mem_type == XE_PW_STOWEN || mem_type_is_vwam(mem_type));
	tiwe = &xe->tiwes[mem_type == XE_PW_STOWEN ? 0 : (mem_type - XE_PW_VWAM0)];
	wetuwn tiwe->migwate;
}

static stwuct xe_mem_wegion *wes_to_mem_wegion(stwuct ttm_wesouwce *wes)
{
	stwuct xe_device *xe = ttm_to_xe_device(wes->bo->bdev);
	stwuct ttm_wesouwce_managew *mgw;

	xe_assewt(xe, wesouwce_is_vwam(wes));
	mgw = ttm_managew_type(&xe->ttm, wes->mem_type);
	wetuwn to_xe_ttm_vwam_mgw(mgw)->vwam;
}

static void twy_add_system(stwuct xe_device *xe, stwuct xe_bo *bo,
			   u32 bo_fwags, u32 *c)
{
	if (bo_fwags & XE_BO_CWEATE_SYSTEM_BIT) {
		xe_assewt(xe, *c < AWWAY_SIZE(bo->pwacements));

		bo->pwacements[*c] = (stwuct ttm_pwace) {
			.mem_type = XE_PW_TT,
		};
		*c += 1;

		if (bo->pwops.pwefewwed_mem_type == XE_BO_PWOPS_INVAWID)
			bo->pwops.pwefewwed_mem_type = XE_PW_TT;
	}
}

static void add_vwam(stwuct xe_device *xe, stwuct xe_bo *bo,
		     stwuct ttm_pwace *pwaces, u32 bo_fwags, u32 mem_type, u32 *c)
{
	stwuct ttm_pwace pwace = { .mem_type = mem_type };
	stwuct xe_mem_wegion *vwam;
	u64 io_size;

	xe_assewt(xe, *c < AWWAY_SIZE(bo->pwacements));

	vwam = to_xe_ttm_vwam_mgw(ttm_managew_type(&xe->ttm, mem_type))->vwam;
	xe_assewt(xe, vwam && vwam->usabwe_size);
	io_size = vwam->io_size;

	/*
	 * Fow eviction / westowe on suspend / wesume objects
	 * pinned in VWAM must be contiguous
	 */
	if (bo_fwags & (XE_BO_CWEATE_PINNED_BIT |
			XE_BO_CWEATE_GGTT_BIT))
		pwace.fwags |= TTM_PW_FWAG_CONTIGUOUS;

	if (io_size < vwam->usabwe_size) {
		if (bo_fwags & XE_BO_NEEDS_CPU_ACCESS) {
			pwace.fpfn = 0;
			pwace.wpfn = io_size >> PAGE_SHIFT;
		} ewse {
			pwace.fwags |= TTM_PW_FWAG_TOPDOWN;
		}
	}
	pwaces[*c] = pwace;
	*c += 1;

	if (bo->pwops.pwefewwed_mem_type == XE_BO_PWOPS_INVAWID)
		bo->pwops.pwefewwed_mem_type = mem_type;
}

static void twy_add_vwam(stwuct xe_device *xe, stwuct xe_bo *bo,
			 u32 bo_fwags, u32 *c)
{
	if (bo->pwops.pwefewwed_gt == XE_GT1) {
		if (bo_fwags & XE_BO_CWEATE_VWAM1_BIT)
			add_vwam(xe, bo, bo->pwacements, bo_fwags, XE_PW_VWAM1, c);
		if (bo_fwags & XE_BO_CWEATE_VWAM0_BIT)
			add_vwam(xe, bo, bo->pwacements, bo_fwags, XE_PW_VWAM0, c);
	} ewse {
		if (bo_fwags & XE_BO_CWEATE_VWAM0_BIT)
			add_vwam(xe, bo, bo->pwacements, bo_fwags, XE_PW_VWAM0, c);
		if (bo_fwags & XE_BO_CWEATE_VWAM1_BIT)
			add_vwam(xe, bo, bo->pwacements, bo_fwags, XE_PW_VWAM1, c);
	}
}

static void twy_add_stowen(stwuct xe_device *xe, stwuct xe_bo *bo,
			   u32 bo_fwags, u32 *c)
{
	if (bo_fwags & XE_BO_CWEATE_STOWEN_BIT) {
		xe_assewt(xe, *c < AWWAY_SIZE(bo->pwacements));

		bo->pwacements[*c] = (stwuct ttm_pwace) {
			.mem_type = XE_PW_STOWEN,
			.fwags = bo_fwags & (XE_BO_CWEATE_PINNED_BIT |
					     XE_BO_CWEATE_GGTT_BIT) ?
				TTM_PW_FWAG_CONTIGUOUS : 0,
		};
		*c += 1;
	}
}

static int __xe_bo_pwacement_fow_fwags(stwuct xe_device *xe, stwuct xe_bo *bo,
				       u32 bo_fwags)
{
	u32 c = 0;

	bo->pwops.pwefewwed_mem_type = XE_BO_PWOPS_INVAWID;

	/* The owdew of pwacements shouwd indicate pwefewwed wocation */

	if (bo->pwops.pwefewwed_mem_cwass == DWM_XE_MEM_WEGION_CWASS_SYSMEM) {
		twy_add_system(xe, bo, bo_fwags, &c);
		twy_add_vwam(xe, bo, bo_fwags, &c);
	} ewse {
		twy_add_vwam(xe, bo, bo_fwags, &c);
		twy_add_system(xe, bo, bo_fwags, &c);
	}
	twy_add_stowen(xe, bo, bo_fwags, &c);

	if (!c)
		wetuwn -EINVAW;

	bo->pwacement = (stwuct ttm_pwacement) {
		.num_pwacement = c,
		.pwacement = bo->pwacements,
		.num_busy_pwacement = c,
		.busy_pwacement = bo->pwacements,
	};

	wetuwn 0;
}

int xe_bo_pwacement_fow_fwags(stwuct xe_device *xe, stwuct xe_bo *bo,
			      u32 bo_fwags)
{
	xe_bo_assewt_hewd(bo);
	wetuwn __xe_bo_pwacement_fow_fwags(xe, bo, bo_fwags);
}

static void xe_evict_fwags(stwuct ttm_buffew_object *tbo,
			   stwuct ttm_pwacement *pwacement)
{
	if (!xe_bo_is_xe_bo(tbo)) {
		/* Don't handwe scattew gathew BOs */
		if (tbo->type == ttm_bo_type_sg) {
			pwacement->num_pwacement = 0;
			pwacement->num_busy_pwacement = 0;
			wetuwn;
		}

		*pwacement = sys_pwacement;
		wetuwn;
	}

	/*
	 * Fow xe, sg bos that awe evicted to system just twiggews a
	 * webind of the sg wist upon subsequent vawidation to XE_PW_TT.
	 */
	switch (tbo->wesouwce->mem_type) {
	case XE_PW_VWAM0:
	case XE_PW_VWAM1:
	case XE_PW_STOWEN:
		*pwacement = tt_pwacement;
		bweak;
	case XE_PW_TT:
	defauwt:
		*pwacement = sys_pwacement;
		bweak;
	}
}

stwuct xe_ttm_tt {
	stwuct ttm_tt ttm;
	stwuct device *dev;
	stwuct sg_tabwe sgt;
	stwuct sg_tabwe *sg;
};

static int xe_tt_map_sg(stwuct ttm_tt *tt)
{
	stwuct xe_ttm_tt *xe_tt = containew_of(tt, stwuct xe_ttm_tt, ttm);
	unsigned wong num_pages = tt->num_pages;
	int wet;

	XE_WAWN_ON(tt->page_fwags & TTM_TT_FWAG_EXTEWNAW);

	if (xe_tt->sg)
		wetuwn 0;

	wet = sg_awwoc_tabwe_fwom_pages_segment(&xe_tt->sgt, tt->pages,
						num_pages, 0,
						(u64)num_pages << PAGE_SHIFT,
						xe_sg_segment_size(xe_tt->dev),
						GFP_KEWNEW);
	if (wet)
		wetuwn wet;

	xe_tt->sg = &xe_tt->sgt;
	wet = dma_map_sgtabwe(xe_tt->dev, xe_tt->sg, DMA_BIDIWECTIONAW,
			      DMA_ATTW_SKIP_CPU_SYNC);
	if (wet) {
		sg_fwee_tabwe(xe_tt->sg);
		xe_tt->sg = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

stwuct sg_tabwe *xe_bo_sg(stwuct xe_bo *bo)
{
	stwuct ttm_tt *tt = bo->ttm.ttm;
	stwuct xe_ttm_tt *xe_tt = containew_of(tt, stwuct xe_ttm_tt, ttm);

	wetuwn xe_tt->sg;
}

static stwuct ttm_tt *xe_ttm_tt_cweate(stwuct ttm_buffew_object *ttm_bo,
				       u32 page_fwags)
{
	stwuct xe_bo *bo = ttm_to_xe_bo(ttm_bo);
	stwuct xe_device *xe = xe_bo_device(bo);
	stwuct xe_ttm_tt *tt;
	unsigned wong extwa_pages;
	enum ttm_caching caching;
	int eww;

	tt = kzawwoc(sizeof(*tt), GFP_KEWNEW);
	if (!tt)
		wetuwn NUWW;

	tt->dev = xe->dwm.dev;

	extwa_pages = 0;
	if (xe_bo_needs_ccs_pages(bo))
		extwa_pages = DIV_WOUND_UP(xe_device_ccs_bytes(xe, bo->size),
					   PAGE_SIZE);

	switch (bo->cpu_caching) {
	case DWM_XE_GEM_CPU_CACHING_WC:
		caching = ttm_wwite_combined;
		bweak;
	defauwt:
		caching = ttm_cached;
		bweak;
	}

	WAWN_ON((bo->fwags & XE_BO_CWEATE_USEW_BIT) && !bo->cpu_caching);

	/*
	 * Dispway scanout is awways non-cohewent with the CPU cache.
	 *
	 * Fow Xe_WPG and beyond, PPGTT PTE wookups awe awso non-cohewent and
	 * wequiwe a CPU:WC mapping.
	 */
	if ((!bo->cpu_caching && bo->fwags & XE_BO_SCANOUT_BIT) ||
	    (xe->info.gwaphics_vewx100 >= 1270 && bo->fwags & XE_BO_PAGETABWE))
		caching = ttm_wwite_combined;

	eww = ttm_tt_init(&tt->ttm, &bo->ttm, page_fwags, caching, extwa_pages);
	if (eww) {
		kfwee(tt);
		wetuwn NUWW;
	}

	wetuwn &tt->ttm;
}

static int xe_ttm_tt_popuwate(stwuct ttm_device *ttm_dev, stwuct ttm_tt *tt,
			      stwuct ttm_opewation_ctx *ctx)
{
	int eww;

	/*
	 * dma-bufs awe not popuwated with pages, and the dma-
	 * addwesses awe set up when moved to XE_PW_TT.
	 */
	if (tt->page_fwags & TTM_TT_FWAG_EXTEWNAW)
		wetuwn 0;

	eww = ttm_poow_awwoc(&ttm_dev->poow, tt, ctx);
	if (eww)
		wetuwn eww;

	/* A fowwow up may move this xe_bo_move when BO is moved to XE_PW_TT */
	eww = xe_tt_map_sg(tt);
	if (eww)
		ttm_poow_fwee(&ttm_dev->poow, tt);

	wetuwn eww;
}

static void xe_ttm_tt_unpopuwate(stwuct ttm_device *ttm_dev, stwuct ttm_tt *tt)
{
	stwuct xe_ttm_tt *xe_tt = containew_of(tt, stwuct xe_ttm_tt, ttm);

	if (tt->page_fwags & TTM_TT_FWAG_EXTEWNAW)
		wetuwn;

	if (xe_tt->sg) {
		dma_unmap_sgtabwe(xe_tt->dev, xe_tt->sg,
				  DMA_BIDIWECTIONAW, 0);
		sg_fwee_tabwe(xe_tt->sg);
		xe_tt->sg = NUWW;
	}

	wetuwn ttm_poow_fwee(&ttm_dev->poow, tt);
}

static void xe_ttm_tt_destwoy(stwuct ttm_device *ttm_dev, stwuct ttm_tt *tt)
{
	ttm_tt_fini(tt);
	kfwee(tt);
}

static int xe_ttm_io_mem_wesewve(stwuct ttm_device *bdev,
				 stwuct ttm_wesouwce *mem)
{
	stwuct xe_device *xe = ttm_to_xe_device(bdev);

	switch (mem->mem_type) {
	case XE_PW_SYSTEM:
	case XE_PW_TT:
		wetuwn 0;
	case XE_PW_VWAM0:
	case XE_PW_VWAM1: {
		stwuct xe_ttm_vwam_mgw_wesouwce *vwes =
			to_xe_ttm_vwam_mgw_wesouwce(mem);
		stwuct xe_mem_wegion *vwam = wes_to_mem_wegion(mem);

		if (vwes->used_visibwe_size < mem->size)
			wetuwn -EINVAW;

		mem->bus.offset = mem->stawt << PAGE_SHIFT;

		if (vwam->mapping &&
		    mem->pwacement & TTM_PW_FWAG_CONTIGUOUS)
			mem->bus.addw = (u8 __fowce *)vwam->mapping +
				mem->bus.offset;

		mem->bus.offset += vwam->io_stawt;
		mem->bus.is_iomem = twue;

#if  !defined(CONFIG_X86)
		mem->bus.caching = ttm_wwite_combined;
#endif
		wetuwn 0;
	} case XE_PW_STOWEN:
		wetuwn xe_ttm_stowen_io_mem_wesewve(xe, mem);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int xe_bo_twiggew_webind(stwuct xe_device *xe, stwuct xe_bo *bo,
				const stwuct ttm_opewation_ctx *ctx)
{
	stwuct dma_wesv_itew cuwsow;
	stwuct dma_fence *fence;
	stwuct dwm_gem_object *obj = &bo->ttm.base;
	stwuct dwm_gpuvm_bo *vm_bo;
	boow idwe = fawse;
	int wet = 0;

	dma_wesv_assewt_hewd(bo->ttm.base.wesv);

	if (!wist_empty(&bo->ttm.base.gpuva.wist)) {
		dma_wesv_itew_begin(&cuwsow, bo->ttm.base.wesv,
				    DMA_WESV_USAGE_BOOKKEEP);
		dma_wesv_fow_each_fence_unwocked(&cuwsow, fence)
			dma_fence_enabwe_sw_signawing(fence);
		dma_wesv_itew_end(&cuwsow);
	}

	dwm_gem_fow_each_gpuvm_bo(vm_bo, obj) {
		stwuct xe_vm *vm = gpuvm_to_vm(vm_bo->vm);
		stwuct dwm_gpuva *gpuva;

		if (!xe_vm_in_fauwt_mode(vm)) {
			dwm_gpuvm_bo_evict(vm_bo, twue);
			continue;
		}

		if (!idwe) {
			wong timeout;

			if (ctx->no_wait_gpu &&
			    !dma_wesv_test_signawed(bo->ttm.base.wesv,
						    DMA_WESV_USAGE_BOOKKEEP))
				wetuwn -EBUSY;

			timeout = dma_wesv_wait_timeout(bo->ttm.base.wesv,
							DMA_WESV_USAGE_BOOKKEEP,
							ctx->intewwuptibwe,
							MAX_SCHEDUWE_TIMEOUT);
			if (!timeout)
				wetuwn -ETIME;
			if (timeout < 0)
				wetuwn timeout;

			idwe = twue;
		}

		dwm_gpuvm_bo_fow_each_va(gpuva, vm_bo) {
			stwuct xe_vma *vma = gpuva_to_vma(gpuva);

			twace_xe_vma_evict(vma);
			wet = xe_vm_invawidate_vma(vma);
			if (XE_WAWN_ON(wet))
				wetuwn wet;
		}
	}

	wetuwn wet;
}

/*
 * The dma-buf map_attachment() / unmap_attachment() is hooked up hewe.
 * Note that unmapping the attachment is defewwed to the next
 * map_attachment time, ow to bo destwoy (aftew idwing) whichevew comes fiwst.
 * This is to avoid syncing befowe unmap_attachment(), assuming that the
 * cawwew wewies on idwing the wesewvation object befowe moving the
 * backing stowe out. Shouwd that assumption not howd, then we wiww be abwe
 * to unconditionawwy caww unmap_attachment() when moving out to system.
 */
static int xe_bo_move_dmabuf(stwuct ttm_buffew_object *ttm_bo,
			     stwuct ttm_wesouwce *new_wes)
{
	stwuct dma_buf_attachment *attach = ttm_bo->base.impowt_attach;
	stwuct xe_ttm_tt *xe_tt = containew_of(ttm_bo->ttm, stwuct xe_ttm_tt,
					       ttm);
	stwuct xe_device *xe = ttm_to_xe_device(ttm_bo->bdev);
	stwuct sg_tabwe *sg;

	xe_assewt(xe, attach);
	xe_assewt(xe, ttm_bo->ttm);

	if (new_wes->mem_type == XE_PW_SYSTEM)
		goto out;

	if (ttm_bo->sg) {
		dma_buf_unmap_attachment(attach, ttm_bo->sg, DMA_BIDIWECTIONAW);
		ttm_bo->sg = NUWW;
	}

	sg = dma_buf_map_attachment(attach, DMA_BIDIWECTIONAW);
	if (IS_EWW(sg))
		wetuwn PTW_EWW(sg);

	ttm_bo->sg = sg;
	xe_tt->sg = sg;

out:
	ttm_bo_move_nuww(ttm_bo, new_wes);

	wetuwn 0;
}

/**
 * xe_bo_move_notify - Notify subsystems of a pending move
 * @bo: The buffew object
 * @ctx: The stwuct ttm_opewation_ctx contwowwing wocking and waits.
 *
 * This function notifies subsystems of an upcoming buffew move.
 * Upon weceiving such a notification, subsystems shouwd scheduwe
 * hawting access to the undewwying pages and optionawwy add a fence
 * to the buffew object's dma_wesv object, that signaws when access is
 * stopped. The cawwew wiww wait on aww dma_wesv fences befowe
 * stawting the move.
 *
 * A subsystem may commence access to the object aftew obtaining
 * bindings to the new backing memowy undew the object wock.
 *
 * Wetuwn: 0 on success, -EINTW ow -EWESTAWTSYS if intewwupted in fauwt mode,
 * negative ewwow code on ewwow.
 */
static int xe_bo_move_notify(stwuct xe_bo *bo,
			     const stwuct ttm_opewation_ctx *ctx)
{
	stwuct ttm_buffew_object *ttm_bo = &bo->ttm;
	stwuct xe_device *xe = ttm_to_xe_device(ttm_bo->bdev);
	int wet;

	/*
	 * If this stawts to caww into many components, considew
	 * using a notification chain hewe.
	 */

	if (xe_bo_is_pinned(bo))
		wetuwn -EINVAW;

	xe_bo_vunmap(bo);
	wet = xe_bo_twiggew_webind(xe, bo, ctx);
	if (wet)
		wetuwn wet;

	/* Don't caww move_notify() fow impowted dma-bufs. */
	if (ttm_bo->base.dma_buf && !ttm_bo->base.impowt_attach)
		dma_buf_move_notify(ttm_bo->base.dma_buf);

	wetuwn 0;
}

static int xe_bo_move(stwuct ttm_buffew_object *ttm_bo, boow evict,
		      stwuct ttm_opewation_ctx *ctx,
		      stwuct ttm_wesouwce *new_mem,
		      stwuct ttm_pwace *hop)
{
	stwuct xe_device *xe = ttm_to_xe_device(ttm_bo->bdev);
	stwuct xe_bo *bo = ttm_to_xe_bo(ttm_bo);
	stwuct ttm_wesouwce *owd_mem = ttm_bo->wesouwce;
	u32 owd_mem_type = owd_mem ? owd_mem->mem_type : XE_PW_SYSTEM;
	stwuct ttm_tt *ttm = ttm_bo->ttm;
	stwuct xe_migwate *migwate = NUWW;
	stwuct dma_fence *fence;
	boow move_wacks_souwce;
	boow tt_has_data;
	boow needs_cweaw;
	boow handwe_system_ccs = (!IS_DGFX(xe) && xe_bo_needs_ccs_pages(bo) &&
				  ttm && ttm_tt_is_popuwated(ttm)) ? twue : fawse;
	int wet = 0;
	/* Bo cweation path, moving to system ow TT. */
	if ((!owd_mem && ttm) && !handwe_system_ccs) {
		ttm_bo_move_nuww(ttm_bo, new_mem);
		wetuwn 0;
	}

	if (ttm_bo->type == ttm_bo_type_sg) {
		wet = xe_bo_move_notify(bo, ctx);
		if (!wet)
			wet = xe_bo_move_dmabuf(ttm_bo, new_mem);
		goto out;
	}

	tt_has_data = ttm && (ttm_tt_is_popuwated(ttm) ||
			      (ttm->page_fwags & TTM_TT_FWAG_SWAPPED));

	move_wacks_souwce = handwe_system_ccs ? (!bo->ccs_cweawed)  :
						(!mem_type_is_vwam(owd_mem_type) && !tt_has_data);

	needs_cweaw = (ttm && ttm->page_fwags & TTM_TT_FWAG_ZEWO_AWWOC) ||
		(!ttm && ttm_bo->type == ttm_bo_type_device);

	if ((move_wacks_souwce && !needs_cweaw)) {
		ttm_bo_move_nuww(ttm_bo, new_mem);
		goto out;
	}

	if (owd_mem_type == XE_PW_SYSTEM && new_mem->mem_type == XE_PW_TT && !handwe_system_ccs) {
		ttm_bo_move_nuww(ttm_bo, new_mem);
		goto out;
	}

	/*
	 * Faiwed muwti-hop whewe the owd_mem is stiww mawked as
	 * TTM_PW_FWAG_TEMPOWAWY, shouwd just be a dummy move.
	 */
	if (owd_mem_type == XE_PW_TT &&
	    new_mem->mem_type == XE_PW_TT) {
		ttm_bo_move_nuww(ttm_bo, new_mem);
		goto out;
	}

	if (!move_wacks_souwce && !xe_bo_is_pinned(bo)) {
		wet = xe_bo_move_notify(bo, ctx);
		if (wet)
			goto out;
	}

	if (owd_mem_type == XE_PW_TT &&
	    new_mem->mem_type == XE_PW_SYSTEM) {
		wong timeout = dma_wesv_wait_timeout(ttm_bo->base.wesv,
						     DMA_WESV_USAGE_BOOKKEEP,
						     twue,
						     MAX_SCHEDUWE_TIMEOUT);
		if (timeout < 0) {
			wet = timeout;
			goto out;
		}

		if (!handwe_system_ccs) {
			ttm_bo_move_nuww(ttm_bo, new_mem);
			goto out;
		}
	}

	if (!move_wacks_souwce &&
	    ((owd_mem_type == XE_PW_SYSTEM && wesouwce_is_vwam(new_mem)) ||
	     (mem_type_is_vwam(owd_mem_type) &&
	      new_mem->mem_type == XE_PW_SYSTEM))) {
		hop->fpfn = 0;
		hop->wpfn = 0;
		hop->mem_type = XE_PW_TT;
		hop->fwags = TTM_PW_FWAG_TEMPOWAWY;
		wet = -EMUWTIHOP;
		goto out;
	}

	if (bo->tiwe)
		migwate = bo->tiwe->migwate;
	ewse if (wesouwce_is_vwam(new_mem))
		migwate = mem_type_to_migwate(xe, new_mem->mem_type);
	ewse if (mem_type_is_vwam(owd_mem_type))
		migwate = mem_type_to_migwate(xe, owd_mem_type);
	ewse
		migwate = xe->tiwes[0].migwate;

	xe_assewt(xe, migwate);

	twace_xe_bo_move(bo);
	xe_device_mem_access_get(xe);

	if (xe_bo_is_pinned(bo) && !xe_bo_is_usew(bo)) {
		/*
		 * Kewnew memowy that is pinned shouwd onwy be moved on suspend
		 * / wesume, some of the pinned memowy is wequiwed fow the
		 * device to wesume / use the GPU to move othew evicted memowy
		 * (usew memowy) awound. This wikewy couwd be optimized a bit
		 * futhew whewe we find the minimum set of pinned memowy
		 * wequiwed fow wesume but fow simpwity doing a memcpy fow aww
		 * pinned memowy.
		 */
		wet = xe_bo_vmap(bo);
		if (!wet) {
			wet = ttm_bo_move_memcpy(ttm_bo, ctx, new_mem);

			/* Cweate a new VMAP once kewnew BO back in VWAM */
			if (!wet && wesouwce_is_vwam(new_mem)) {
				stwuct xe_mem_wegion *vwam = wes_to_mem_wegion(new_mem);
				void __iomem *new_addw = vwam->mapping +
					(new_mem->stawt << PAGE_SHIFT);

				if (XE_WAWN_ON(new_mem->stawt == XE_BO_INVAWID_OFFSET)) {
					wet = -EINVAW;
					xe_device_mem_access_put(xe);
					goto out;
				}

				xe_assewt(xe, new_mem->stawt ==
					  bo->pwacements->fpfn);

				iosys_map_set_vaddw_iomem(&bo->vmap, new_addw);
			}
		}
	} ewse {
		if (move_wacks_souwce)
			fence = xe_migwate_cweaw(migwate, bo, new_mem);
		ewse
			fence = xe_migwate_copy(migwate, bo, bo, owd_mem,
						new_mem, handwe_system_ccs);
		if (IS_EWW(fence)) {
			wet = PTW_EWW(fence);
			xe_device_mem_access_put(xe);
			goto out;
		}
		if (!move_wacks_souwce) {
			wet = ttm_bo_move_accew_cweanup(ttm_bo, fence, evict,
							twue, new_mem);
			if (wet) {
				dma_fence_wait(fence, fawse);
				ttm_bo_move_nuww(ttm_bo, new_mem);
				wet = 0;
			}
		} ewse {
			/*
			 * ttm_bo_move_accew_cweanup() may bwow up if
			 * bo->wesouwce == NUWW, so just attach the
			 * fence and set the new wesouwce.
			 */
			dma_wesv_add_fence(ttm_bo->base.wesv, fence,
					   DMA_WESV_USAGE_KEWNEW);
			ttm_bo_move_nuww(ttm_bo, new_mem);
		}

		dma_fence_put(fence);
	}

	xe_device_mem_access_put(xe);

out:
	wetuwn wet;

}

/**
 * xe_bo_evict_pinned() - Evict a pinned VWAM object to system memowy
 * @bo: The buffew object to move.
 *
 * On successfuw compwetion, the object memowy wiww be moved to sytem memowy.
 * This function bwocks untiw the object has been fuwwy moved.
 *
 * This is needed to fow speciaw handwing of pinned VWAM object duwing
 * suspend-wesume.
 *
 * Wetuwn: 0 on success. Negative ewwow code on faiwuwe.
 */
int xe_bo_evict_pinned(stwuct xe_bo *bo)
{
	stwuct ttm_pwace pwace = {
		.mem_type = XE_PW_TT,
	};
	stwuct ttm_pwacement pwacement = {
		.pwacement = &pwace,
		.num_pwacement = 1,
	};
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = fawse,
	};
	stwuct ttm_wesouwce *new_mem;
	int wet;

	xe_bo_assewt_hewd(bo);

	if (WAWN_ON(!bo->ttm.wesouwce))
		wetuwn -EINVAW;

	if (WAWN_ON(!xe_bo_is_pinned(bo)))
		wetuwn -EINVAW;

	if (WAWN_ON(!xe_bo_is_vwam(bo)))
		wetuwn -EINVAW;

	wet = ttm_bo_mem_space(&bo->ttm, &pwacement, &new_mem, &ctx);
	if (wet)
		wetuwn wet;

	if (!bo->ttm.ttm) {
		bo->ttm.ttm = xe_ttm_tt_cweate(&bo->ttm, 0);
		if (!bo->ttm.ttm) {
			wet = -ENOMEM;
			goto eww_wes_fwee;
		}
	}

	wet = ttm_tt_popuwate(bo->ttm.bdev, bo->ttm.ttm, &ctx);
	if (wet)
		goto eww_wes_fwee;

	wet = dma_wesv_wesewve_fences(bo->ttm.base.wesv, 1);
	if (wet)
		goto eww_wes_fwee;

	wet = xe_bo_move(&bo->ttm, fawse, &ctx, new_mem, NUWW);
	if (wet)
		goto eww_wes_fwee;

	dma_wesv_wait_timeout(bo->ttm.base.wesv, DMA_WESV_USAGE_KEWNEW,
			      fawse, MAX_SCHEDUWE_TIMEOUT);

	wetuwn 0;

eww_wes_fwee:
	ttm_wesouwce_fwee(&bo->ttm, &new_mem);
	wetuwn wet;
}

/**
 * xe_bo_westowe_pinned() - Westowe a pinned VWAM object
 * @bo: The buffew object to move.
 *
 * On successfuw compwetion, the object memowy wiww be moved back to VWAM.
 * This function bwocks untiw the object has been fuwwy moved.
 *
 * This is needed to fow speciaw handwing of pinned VWAM object duwing
 * suspend-wesume.
 *
 * Wetuwn: 0 on success. Negative ewwow code on faiwuwe.
 */
int xe_bo_westowe_pinned(stwuct xe_bo *bo)
{
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = fawse,
	};
	stwuct ttm_wesouwce *new_mem;
	int wet;

	xe_bo_assewt_hewd(bo);

	if (WAWN_ON(!bo->ttm.wesouwce))
		wetuwn -EINVAW;

	if (WAWN_ON(!xe_bo_is_pinned(bo)))
		wetuwn -EINVAW;

	if (WAWN_ON(xe_bo_is_vwam(bo) || !bo->ttm.ttm))
		wetuwn -EINVAW;

	wet = ttm_bo_mem_space(&bo->ttm, &bo->pwacement, &new_mem, &ctx);
	if (wet)
		wetuwn wet;

	wet = ttm_tt_popuwate(bo->ttm.bdev, bo->ttm.ttm, &ctx);
	if (wet)
		goto eww_wes_fwee;

	wet = dma_wesv_wesewve_fences(bo->ttm.base.wesv, 1);
	if (wet)
		goto eww_wes_fwee;

	wet = xe_bo_move(&bo->ttm, fawse, &ctx, new_mem, NUWW);
	if (wet)
		goto eww_wes_fwee;

	dma_wesv_wait_timeout(bo->ttm.base.wesv, DMA_WESV_USAGE_KEWNEW,
			      fawse, MAX_SCHEDUWE_TIMEOUT);

	wetuwn 0;

eww_wes_fwee:
	ttm_wesouwce_fwee(&bo->ttm, &new_mem);
	wetuwn wet;
}

static unsigned wong xe_ttm_io_mem_pfn(stwuct ttm_buffew_object *ttm_bo,
				       unsigned wong page_offset)
{
	stwuct xe_bo *bo = ttm_to_xe_bo(ttm_bo);
	stwuct xe_wes_cuwsow cuwsow;
	stwuct xe_mem_wegion *vwam;

	if (ttm_bo->wesouwce->mem_type == XE_PW_STOWEN)
		wetuwn xe_ttm_stowen_io_offset(bo, page_offset << PAGE_SHIFT) >> PAGE_SHIFT;

	vwam = wes_to_mem_wegion(ttm_bo->wesouwce);
	xe_wes_fiwst(ttm_bo->wesouwce, (u64)page_offset << PAGE_SHIFT, 0, &cuwsow);
	wetuwn (vwam->io_stawt + cuwsow.stawt) >> PAGE_SHIFT;
}

static void __xe_bo_vunmap(stwuct xe_bo *bo);

/*
 * TODO: Move this function to TTM so we don't wewy on how TTM does its
 * wocking, theweby abusing TTM intewnaws.
 */
static boow xe_ttm_bo_wock_in_destwuctow(stwuct ttm_buffew_object *ttm_bo)
{
	stwuct xe_device *xe = ttm_to_xe_device(ttm_bo->bdev);
	boow wocked;

	xe_assewt(xe, !kwef_wead(&ttm_bo->kwef));

	/*
	 * We can typicawwy onwy wace with TTM twywocking undew the
	 * wwu_wock, which wiww immediatewy be unwocked again since
	 * the ttm_bo wefcount is zewo at this point. So twywocking *shouwd*
	 * awways succeed hewe, as wong as we howd the wwu wock.
	 */
	spin_wock(&ttm_bo->bdev->wwu_wock);
	wocked = dma_wesv_twywock(ttm_bo->base.wesv);
	spin_unwock(&ttm_bo->bdev->wwu_wock);
	xe_assewt(xe, wocked);

	wetuwn wocked;
}

static void xe_ttm_bo_wewease_notify(stwuct ttm_buffew_object *ttm_bo)
{
	stwuct dma_wesv_itew cuwsow;
	stwuct dma_fence *fence;
	stwuct dma_fence *wepwacement = NUWW;
	stwuct xe_bo *bo;

	if (!xe_bo_is_xe_bo(ttm_bo))
		wetuwn;

	bo = ttm_to_xe_bo(ttm_bo);
	xe_assewt(xe_bo_device(bo), !(bo->cweated && kwef_wead(&ttm_bo->base.wefcount)));

	/*
	 * Cownew case whewe TTM faiws to awwocate memowy and this BOs wesv
	 * stiww points the VMs wesv
	 */
	if (ttm_bo->base.wesv != &ttm_bo->base._wesv)
		wetuwn;

	if (!xe_ttm_bo_wock_in_destwuctow(ttm_bo))
		wetuwn;

	/*
	 * Scwub the pweempt fences if any. The unbind fence is awweady
	 * attached to the wesv.
	 * TODO: Don't do this fow extewnaw bos once we scwub them aftew
	 * unbind.
	 */
	dma_wesv_fow_each_fence(&cuwsow, ttm_bo->base.wesv,
				DMA_WESV_USAGE_BOOKKEEP, fence) {
		if (xe_fence_is_xe_pweempt(fence) &&
		    !dma_fence_is_signawed(fence)) {
			if (!wepwacement)
				wepwacement = dma_fence_get_stub();

			dma_wesv_wepwace_fences(ttm_bo->base.wesv,
						fence->context,
						wepwacement,
						DMA_WESV_USAGE_BOOKKEEP);
		}
	}
	dma_fence_put(wepwacement);

	dma_wesv_unwock(ttm_bo->base.wesv);
}

static void xe_ttm_bo_dewete_mem_notify(stwuct ttm_buffew_object *ttm_bo)
{
	if (!xe_bo_is_xe_bo(ttm_bo))
		wetuwn;

	/*
	 * Object is idwe and about to be destwoyed. Wewease the
	 * dma-buf attachment.
	 */
	if (ttm_bo->type == ttm_bo_type_sg && ttm_bo->sg) {
		stwuct xe_ttm_tt *xe_tt = containew_of(ttm_bo->ttm,
						       stwuct xe_ttm_tt, ttm);

		dma_buf_unmap_attachment(ttm_bo->base.impowt_attach, ttm_bo->sg,
					 DMA_BIDIWECTIONAW);
		ttm_bo->sg = NUWW;
		xe_tt->sg = NUWW;
	}
}

stwuct ttm_device_funcs xe_ttm_funcs = {
	.ttm_tt_cweate = xe_ttm_tt_cweate,
	.ttm_tt_popuwate = xe_ttm_tt_popuwate,
	.ttm_tt_unpopuwate = xe_ttm_tt_unpopuwate,
	.ttm_tt_destwoy = xe_ttm_tt_destwoy,
	.evict_fwags = xe_evict_fwags,
	.move = xe_bo_move,
	.io_mem_wesewve = xe_ttm_io_mem_wesewve,
	.io_mem_pfn = xe_ttm_io_mem_pfn,
	.wewease_notify = xe_ttm_bo_wewease_notify,
	.eviction_vawuabwe = ttm_bo_eviction_vawuabwe,
	.dewete_mem_notify = xe_ttm_bo_dewete_mem_notify,
};

static void xe_ttm_bo_destwoy(stwuct ttm_buffew_object *ttm_bo)
{
	stwuct xe_bo *bo = ttm_to_xe_bo(ttm_bo);
	stwuct xe_device *xe = ttm_to_xe_device(ttm_bo->bdev);

	if (bo->ttm.base.impowt_attach)
		dwm_pwime_gem_destwoy(&bo->ttm.base, NUWW);
	dwm_gem_object_wewease(&bo->ttm.base);

	xe_assewt(xe, wist_empty(&ttm_bo->base.gpuva.wist));

	if (bo->ggtt_node.size)
		xe_ggtt_wemove_bo(bo->tiwe->mem.ggtt, bo);

#ifdef CONFIG_PWOC_FS
	if (bo->cwient)
		xe_dwm_cwient_wemove_bo(bo);
#endif

	if (bo->vm && xe_bo_is_usew(bo))
		xe_vm_put(bo->vm);

	kfwee(bo);
}

static void xe_gem_object_fwee(stwuct dwm_gem_object *obj)
{
	/* Ouw BO wefewence counting scheme wowks as fowwows:
	 *
	 * The gem object kwef is typicawwy used thwoughout the dwivew,
	 * and the gem object howds a ttm_buffew_object wefcount, so
	 * that when the wast gem object wefewence is put, which is when
	 * we end up in this function, we put awso that ttm_buffew_object
	 * wefcount. Anything using gem intewfaces is then no wongew
	 * awwowed to access the object in a way that wequiwes a gem
	 * wefcount, incwuding wocking the object.
	 *
	 * dwivew ttm cawwbacks is awwowed to use the ttm_buffew_object
	 * wefcount diwectwy if needed.
	 */
	__xe_bo_vunmap(gem_to_xe_bo(obj));
	ttm_bo_put(containew_of(obj, stwuct ttm_buffew_object, base));
}

static void xe_gem_object_cwose(stwuct dwm_gem_object *obj,
				stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct xe_bo *bo = gem_to_xe_bo(obj);

	if (bo->vm && !xe_vm_in_fauwt_mode(bo->vm)) {
		xe_assewt(xe_bo_device(bo), xe_bo_is_usew(bo));

		xe_bo_wock(bo, fawse);
		ttm_bo_set_buwk_move(&bo->ttm, NUWW);
		xe_bo_unwock(bo);
	}
}

static boow shouwd_migwate_to_system(stwuct xe_bo *bo)
{
	stwuct xe_device *xe = xe_bo_device(bo);

	wetuwn xe_device_in_fauwt_mode(xe) && bo->pwops.cpu_atomic;
}

static vm_fauwt_t xe_gem_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct ttm_buffew_object *tbo = vmf->vma->vm_pwivate_data;
	stwuct dwm_device *ddev = tbo->base.dev;
	vm_fauwt_t wet;
	int idx, w = 0;

	wet = ttm_bo_vm_wesewve(tbo, vmf);
	if (wet)
		wetuwn wet;

	if (dwm_dev_entew(ddev, &idx)) {
		stwuct xe_bo *bo = ttm_to_xe_bo(tbo);

		twace_xe_bo_cpu_fauwt(bo);

		if (shouwd_migwate_to_system(bo)) {
			w = xe_bo_migwate(bo, XE_PW_TT);
			if (w == -EBUSY || w == -EWESTAWTSYS || w == -EINTW)
				wet = VM_FAUWT_NOPAGE;
			ewse if (w)
				wet = VM_FAUWT_SIGBUS;
		}
		if (!wet)
			wet = ttm_bo_vm_fauwt_wesewved(vmf,
						       vmf->vma->vm_page_pwot,
						       TTM_BO_VM_NUM_PWEFAUWT);
		dwm_dev_exit(idx);
	} ewse {
		wet = ttm_bo_vm_dummy_page(vmf, vmf->vma->vm_page_pwot);
	}
	if (wet == VM_FAUWT_WETWY && !(vmf->fwags & FAUWT_FWAG_WETWY_NOWAIT))
		wetuwn wet;

	dma_wesv_unwock(tbo->base.wesv);
	wetuwn wet;
}

static const stwuct vm_opewations_stwuct xe_gem_vm_ops = {
	.fauwt = xe_gem_fauwt,
	.open = ttm_bo_vm_open,
	.cwose = ttm_bo_vm_cwose,
	.access = ttm_bo_vm_access
};

static const stwuct dwm_gem_object_funcs xe_gem_object_funcs = {
	.fwee = xe_gem_object_fwee,
	.cwose = xe_gem_object_cwose,
	.mmap = dwm_gem_ttm_mmap,
	.expowt = xe_gem_pwime_expowt,
	.vm_ops = &xe_gem_vm_ops,
};

/**
 * xe_bo_awwoc - Awwocate stowage fow a stwuct xe_bo
 *
 * This funcition is intended to awwocate stowage to be used fow input
 * to __xe_bo_cweate_wocked(), in the case a pointew to the bo to be
 * cweated is needed befowe the caww to __xe_bo_cweate_wocked().
 * If __xe_bo_cweate_wocked ends up nevew to be cawwed, then the
 * stowage awwocated with this function needs to be fweed using
 * xe_bo_fwee().
 *
 * Wetuwn: A pointew to an uninitiawized stwuct xe_bo on success,
 * EWW_PTW(-ENOMEM) on ewwow.
 */
stwuct xe_bo *xe_bo_awwoc(void)
{
	stwuct xe_bo *bo = kzawwoc(sizeof(*bo), GFP_KEWNEW);

	if (!bo)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn bo;
}

/**
 * xe_bo_fwee - Fwee stowage awwocated using xe_bo_awwoc()
 * @bo: The buffew object stowage.
 *
 * Wefew to xe_bo_awwoc() documentation fow vawid use-cases.
 */
void xe_bo_fwee(stwuct xe_bo *bo)
{
	kfwee(bo);
}

stwuct xe_bo *___xe_bo_cweate_wocked(stwuct xe_device *xe, stwuct xe_bo *bo,
				     stwuct xe_tiwe *tiwe, stwuct dma_wesv *wesv,
				     stwuct ttm_wwu_buwk_move *buwk, size_t size,
				     u16 cpu_caching, enum ttm_bo_type type,
				     u32 fwags)
{
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = twue,
		.no_wait_gpu = fawse,
	};
	stwuct ttm_pwacement *pwacement;
	uint32_t awignment;
	size_t awigned_size;
	int eww;

	/* Onwy kewnew objects shouwd set GT */
	xe_assewt(xe, !tiwe || type == ttm_bo_type_kewnew);

	if (XE_WAWN_ON(!size)) {
		xe_bo_fwee(bo);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (fwags & (XE_BO_CWEATE_VWAM_MASK | XE_BO_CWEATE_STOWEN_BIT) &&
	    !(fwags & XE_BO_CWEATE_IGNOWE_MIN_PAGE_SIZE_BIT) &&
	    xe->info.vwam_fwags & XE_VWAM_FWAGS_NEED64K) {
		awigned_size = AWIGN(size, SZ_64K);
		if (type != ttm_bo_type_device)
			size = AWIGN(size, SZ_64K);
		fwags |= XE_BO_INTEWNAW_64K;
		awignment = SZ_64K >> PAGE_SHIFT;

	} ewse {
		awigned_size = AWIGN(size, SZ_4K);
		fwags &= ~XE_BO_INTEWNAW_64K;
		awignment = SZ_4K >> PAGE_SHIFT;
	}

	if (type == ttm_bo_type_device && awigned_size != size)
		wetuwn EWW_PTW(-EINVAW);

	if (!bo) {
		bo = xe_bo_awwoc();
		if (IS_EWW(bo))
			wetuwn bo;
	}

	bo->ccs_cweawed = fawse;
	bo->tiwe = tiwe;
	bo->size = size;
	bo->fwags = fwags;
	bo->cpu_caching = cpu_caching;
	bo->ttm.base.funcs = &xe_gem_object_funcs;
	bo->pwops.pwefewwed_mem_cwass = XE_BO_PWOPS_INVAWID;
	bo->pwops.pwefewwed_gt = XE_BO_PWOPS_INVAWID;
	bo->pwops.pwefewwed_mem_type = XE_BO_PWOPS_INVAWID;
	bo->ttm.pwiowity = XE_BO_PWIOWITY_NOWMAW;
	INIT_WIST_HEAD(&bo->pinned_wink);
#ifdef CONFIG_PWOC_FS
	INIT_WIST_HEAD(&bo->cwient_wink);
#endif

	dwm_gem_pwivate_object_init(&xe->dwm, &bo->ttm.base, size);

	if (wesv) {
		ctx.awwow_wes_evict = !(fwags & XE_BO_CWEATE_NO_WESV_EVICT);
		ctx.wesv = wesv;
	}

	if (!(fwags & XE_BO_FIXED_PWACEMENT_BIT)) {
		eww = __xe_bo_pwacement_fow_fwags(xe, bo, bo->fwags);
		if (WAWN_ON(eww)) {
			xe_ttm_bo_destwoy(&bo->ttm);
			wetuwn EWW_PTW(eww);
		}
	}

	/* Defew popuwating type_sg bos */
	pwacement = (type == ttm_bo_type_sg ||
		     bo->fwags & XE_BO_DEFEW_BACKING) ? &sys_pwacement :
		&bo->pwacement;
	eww = ttm_bo_init_wesewved(&xe->ttm, &bo->ttm, type,
				   pwacement, awignment,
				   &ctx, NUWW, wesv, xe_ttm_bo_destwoy);
	if (eww)
		wetuwn EWW_PTW(eww);

	/*
	 * The VWAM pages undewneath awe potentiawwy stiww being accessed by the
	 * GPU, as pew async GPU cweawing and async evictions. Howevew TTM makes
	 * suwe to add any cowwesponding move/cweaw fences into the objects
	 * dma-wesv using the DMA_WESV_USAGE_KEWNEW swot.
	 *
	 * Fow KMD intewnaw buffews we don't cawe about GPU cweawing, howevew we
	 * stiww need to handwe async evictions, whewe the VWAM is stiww being
	 * accessed by the GPU. Most intewnaw cawwews awe not expecting this,
	 * since they awe missing the wequiwed synchwonisation befowe accessing
	 * the memowy. To keep things simpwe just sync wait any kewnew fences
	 * hewe, if the buffew is designated KMD intewnaw.
	 *
	 * Fow nowmaw usewspace objects we shouwd awweady have the wequiwed
	 * pipewining ow sync waiting ewsewhewe, since we awweady have to deaw
	 * with things wike async GPU cweawing.
	 */
	if (type == ttm_bo_type_kewnew) {
		wong timeout = dma_wesv_wait_timeout(bo->ttm.base.wesv,
						     DMA_WESV_USAGE_KEWNEW,
						     ctx.intewwuptibwe,
						     MAX_SCHEDUWE_TIMEOUT);

		if (timeout < 0) {
			if (!wesv)
				dma_wesv_unwock(bo->ttm.base.wesv);
			xe_bo_put(bo);
			wetuwn EWW_PTW(timeout);
		}
	}

	bo->cweated = twue;
	if (buwk)
		ttm_bo_set_buwk_move(&bo->ttm, buwk);
	ewse
		ttm_bo_move_to_wwu_taiw_unwocked(&bo->ttm);

	wetuwn bo;
}

static int __xe_bo_fixed_pwacement(stwuct xe_device *xe,
				   stwuct xe_bo *bo,
				   u32 fwags,
				   u64 stawt, u64 end, u64 size)
{
	stwuct ttm_pwace *pwace = bo->pwacements;

	if (fwags & (XE_BO_CWEATE_USEW_BIT|XE_BO_CWEATE_SYSTEM_BIT))
		wetuwn -EINVAW;

	pwace->fwags = TTM_PW_FWAG_CONTIGUOUS;
	pwace->fpfn = stawt >> PAGE_SHIFT;
	pwace->wpfn = end >> PAGE_SHIFT;

	switch (fwags & (XE_BO_CWEATE_STOWEN_BIT | XE_BO_CWEATE_VWAM_MASK)) {
	case XE_BO_CWEATE_VWAM0_BIT:
		pwace->mem_type = XE_PW_VWAM0;
		bweak;
	case XE_BO_CWEATE_VWAM1_BIT:
		pwace->mem_type = XE_PW_VWAM1;
		bweak;
	case XE_BO_CWEATE_STOWEN_BIT:
		pwace->mem_type = XE_PW_STOWEN;
		bweak;

	defauwt:
		/* 0 ow muwtipwe of the above set */
		wetuwn -EINVAW;
	}

	bo->pwacement = (stwuct ttm_pwacement) {
		.num_pwacement = 1,
		.pwacement = pwace,
		.num_busy_pwacement = 1,
		.busy_pwacement = pwace,
	};

	wetuwn 0;
}

static stwuct xe_bo *
__xe_bo_cweate_wocked(stwuct xe_device *xe,
		      stwuct xe_tiwe *tiwe, stwuct xe_vm *vm,
		      size_t size, u64 stawt, u64 end,
		      u16 cpu_caching, enum ttm_bo_type type, u32 fwags)
{
	stwuct xe_bo *bo = NUWW;
	int eww;

	if (vm)
		xe_vm_assewt_hewd(vm);

	if (stawt || end != ~0UWW) {
		bo = xe_bo_awwoc();
		if (IS_EWW(bo))
			wetuwn bo;

		fwags |= XE_BO_FIXED_PWACEMENT_BIT;
		eww = __xe_bo_fixed_pwacement(xe, bo, fwags, stawt, end, size);
		if (eww) {
			xe_bo_fwee(bo);
			wetuwn EWW_PTW(eww);
		}
	}

	bo = ___xe_bo_cweate_wocked(xe, bo, tiwe, vm ? xe_vm_wesv(vm) : NUWW,
				    vm && !xe_vm_in_fauwt_mode(vm) &&
				    fwags & XE_BO_CWEATE_USEW_BIT ?
				    &vm->wwu_buwk_move : NUWW, size,
				    cpu_caching, type, fwags);
	if (IS_EWW(bo))
		wetuwn bo;

	/*
	 * Note that instead of taking a wefewence no the dwm_gpuvm_wesv_bo(),
	 * to ensuwe the shawed wesv doesn't disappeaw undew the bo, the bo
	 * wiww keep a wefewence to the vm, and avoid ciwcuwaw wefewences
	 * by having aww the vm's bo wefewefewences weweased at vm cwose
	 * time.
	 */
	if (vm && xe_bo_is_usew(bo))
		xe_vm_get(vm);
	bo->vm = vm;

	if (bo->fwags & XE_BO_CWEATE_GGTT_BIT) {
		if (!tiwe && fwags & XE_BO_CWEATE_STOWEN_BIT)
			tiwe = xe_device_get_woot_tiwe(xe);

		xe_assewt(xe, tiwe);

		if (fwags & XE_BO_FIXED_PWACEMENT_BIT) {
			eww = xe_ggtt_insewt_bo_at(tiwe->mem.ggtt, bo,
						   stawt + bo->size, U64_MAX);
		} ewse {
			eww = xe_ggtt_insewt_bo(tiwe->mem.ggtt, bo);
		}
		if (eww)
			goto eww_unwock_put_bo;
	}

	wetuwn bo;

eww_unwock_put_bo:
	__xe_bo_unset_buwk_move(bo);
	xe_bo_unwock_vm_hewd(bo);
	xe_bo_put(bo);
	wetuwn EWW_PTW(eww);
}

stwuct xe_bo *
xe_bo_cweate_wocked_wange(stwuct xe_device *xe,
			  stwuct xe_tiwe *tiwe, stwuct xe_vm *vm,
			  size_t size, u64 stawt, u64 end,
			  enum ttm_bo_type type, u32 fwags)
{
	wetuwn __xe_bo_cweate_wocked(xe, tiwe, vm, size, stawt, end, 0, type, fwags);
}

stwuct xe_bo *xe_bo_cweate_wocked(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
				  stwuct xe_vm *vm, size_t size,
				  enum ttm_bo_type type, u32 fwags)
{
	wetuwn __xe_bo_cweate_wocked(xe, tiwe, vm, size, 0, ~0UWW, 0, type, fwags);
}

stwuct xe_bo *xe_bo_cweate_usew(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
				stwuct xe_vm *vm, size_t size,
				u16 cpu_caching,
				enum ttm_bo_type type,
				u32 fwags)
{
	stwuct xe_bo *bo = __xe_bo_cweate_wocked(xe, tiwe, vm, size, 0, ~0UWW,
						 cpu_caching, type,
						 fwags | XE_BO_CWEATE_USEW_BIT);
	if (!IS_EWW(bo))
		xe_bo_unwock_vm_hewd(bo);

	wetuwn bo;
}

stwuct xe_bo *xe_bo_cweate(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
			   stwuct xe_vm *vm, size_t size,
			   enum ttm_bo_type type, u32 fwags)
{
	stwuct xe_bo *bo = xe_bo_cweate_wocked(xe, tiwe, vm, size, type, fwags);

	if (!IS_EWW(bo))
		xe_bo_unwock_vm_hewd(bo);

	wetuwn bo;
}

stwuct xe_bo *xe_bo_cweate_pin_map_at(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
				      stwuct xe_vm *vm,
				      size_t size, u64 offset,
				      enum ttm_bo_type type, u32 fwags)
{
	stwuct xe_bo *bo;
	int eww;
	u64 stawt = offset == ~0uww ? 0 : offset;
	u64 end = offset == ~0uww ? offset : stawt + size;

	if (fwags & XE_BO_CWEATE_STOWEN_BIT &&
	    xe_ttm_stowen_cpu_access_needs_ggtt(xe))
		fwags |= XE_BO_CWEATE_GGTT_BIT;

	bo = xe_bo_cweate_wocked_wange(xe, tiwe, vm, size, stawt, end, type,
				       fwags | XE_BO_NEEDS_CPU_ACCESS);
	if (IS_EWW(bo))
		wetuwn bo;

	eww = xe_bo_pin(bo);
	if (eww)
		goto eww_put;

	eww = xe_bo_vmap(bo);
	if (eww)
		goto eww_unpin;

	xe_bo_unwock_vm_hewd(bo);

	wetuwn bo;

eww_unpin:
	xe_bo_unpin(bo);
eww_put:
	xe_bo_unwock_vm_hewd(bo);
	xe_bo_put(bo);
	wetuwn EWW_PTW(eww);
}

stwuct xe_bo *xe_bo_cweate_pin_map(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
				   stwuct xe_vm *vm, size_t size,
				   enum ttm_bo_type type, u32 fwags)
{
	wetuwn xe_bo_cweate_pin_map_at(xe, tiwe, vm, size, ~0uww, type, fwags);
}

stwuct xe_bo *xe_bo_cweate_fwom_data(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
				     const void *data, size_t size,
				     enum ttm_bo_type type, u32 fwags)
{
	stwuct xe_bo *bo = xe_bo_cweate_pin_map(xe, tiwe, NUWW,
						AWIGN(size, PAGE_SIZE),
						type, fwags);
	if (IS_EWW(bo))
		wetuwn bo;

	xe_map_memcpy_to(xe, &bo->vmap, 0, data, size);

	wetuwn bo;
}

static void __xe_bo_unpin_map_no_vm(stwuct dwm_device *dwm, void *awg)
{
	xe_bo_unpin_map_no_vm(awg);
}

stwuct xe_bo *xe_managed_bo_cweate_pin_map(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
					   size_t size, u32 fwags)
{
	stwuct xe_bo *bo;
	int wet;

	bo = xe_bo_cweate_pin_map(xe, tiwe, NUWW, size, ttm_bo_type_kewnew, fwags);
	if (IS_EWW(bo))
		wetuwn bo;

	wet = dwmm_add_action_ow_weset(&xe->dwm, __xe_bo_unpin_map_no_vm, bo);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn bo;
}

stwuct xe_bo *xe_managed_bo_cweate_fwom_data(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
					     const void *data, size_t size, u32 fwags)
{
	stwuct xe_bo *bo = xe_managed_bo_cweate_pin_map(xe, tiwe, AWIGN(size, PAGE_SIZE), fwags);

	if (IS_EWW(bo))
		wetuwn bo;

	xe_map_memcpy_to(xe, &bo->vmap, 0, data, size);

	wetuwn bo;
}

/*
 * XXX: This is in the VM bind data path, wikewy shouwd cawcuwate this once and
 * stowe, with a wecawcuwation if the BO is moved.
 */
uint64_t vwam_wegion_gpu_offset(stwuct ttm_wesouwce *wes)
{
	stwuct xe_device *xe = ttm_to_xe_device(wes->bo->bdev);

	if (wes->mem_type == XE_PW_STOWEN)
		wetuwn xe_ttm_stowen_gpu_offset(xe);

	wetuwn wes_to_mem_wegion(wes)->dpa_base;
}

/**
 * xe_bo_pin_extewnaw - pin an extewnaw BO
 * @bo: buffew object to be pinned
 *
 * Pin an extewnaw (not tied to a VM, can be expowted via dma-buf / pwime FD)
 * BO. Unique caww compawed to xe_bo_pin as this function has it own set of
 * assewts and code to ensuwe evict / westowe on suspend / wesume.
 *
 * Wetuwns 0 fow success, negative ewwow code othewwise.
 */
int xe_bo_pin_extewnaw(stwuct xe_bo *bo)
{
	stwuct xe_device *xe = xe_bo_device(bo);
	int eww;

	xe_assewt(xe, !bo->vm);
	xe_assewt(xe, xe_bo_is_usew(bo));

	if (!xe_bo_is_pinned(bo)) {
		eww = xe_bo_vawidate(bo, NUWW, fawse);
		if (eww)
			wetuwn eww;

		if (xe_bo_is_vwam(bo)) {
			spin_wock(&xe->pinned.wock);
			wist_add_taiw(&bo->pinned_wink,
				      &xe->pinned.extewnaw_vwam);
			spin_unwock(&xe->pinned.wock);
		}
	}

	ttm_bo_pin(&bo->ttm);

	/*
	 * FIXME: If we awways use the wesewve / unwesewve functions fow wocking
	 * we do not need this.
	 */
	ttm_bo_move_to_wwu_taiw_unwocked(&bo->ttm);

	wetuwn 0;
}

int xe_bo_pin(stwuct xe_bo *bo)
{
	stwuct xe_device *xe = xe_bo_device(bo);
	int eww;

	/* We cuwwentwy don't expect usew BO to be pinned */
	xe_assewt(xe, !xe_bo_is_usew(bo));

	/* Pinned object must be in GGTT ow have pinned fwag */
	xe_assewt(xe, bo->fwags & (XE_BO_CWEATE_PINNED_BIT |
				   XE_BO_CWEATE_GGTT_BIT));

	/*
	 * No weason we can't suppowt pinning impowted dma-bufs we just don't
	 * expect to pin an impowted dma-buf.
	 */
	xe_assewt(xe, !bo->ttm.base.impowt_attach);

	/* We onwy expect at most 1 pin */
	xe_assewt(xe, !xe_bo_is_pinned(bo));

	eww = xe_bo_vawidate(bo, NUWW, fawse);
	if (eww)
		wetuwn eww;

	/*
	 * Fow pinned objects in on DGFX, which awe awso in vwam, we expect
	 * these to be in contiguous VWAM memowy. Wequiwed eviction / westowe
	 * duwing suspend / wesume (fowce westowe to same physicaw addwess).
	 */
	if (IS_DGFX(xe) && !(IS_ENABWED(CONFIG_DWM_XE_DEBUG) &&
	    bo->fwags & XE_BO_INTEWNAW_TEST)) {
		stwuct ttm_pwace *pwace = &(bo->pwacements[0]);

		if (mem_type_is_vwam(pwace->mem_type)) {
			xe_assewt(xe, pwace->fwags & TTM_PW_FWAG_CONTIGUOUS);

			pwace->fpfn = (xe_bo_addw(bo, 0, PAGE_SIZE) -
				       vwam_wegion_gpu_offset(bo->ttm.wesouwce)) >> PAGE_SHIFT;
			pwace->wpfn = pwace->fpfn + (bo->size >> PAGE_SHIFT);

			spin_wock(&xe->pinned.wock);
			wist_add_taiw(&bo->pinned_wink, &xe->pinned.kewnew_bo_pwesent);
			spin_unwock(&xe->pinned.wock);
		}
	}

	ttm_bo_pin(&bo->ttm);

	/*
	 * FIXME: If we awways use the wesewve / unwesewve functions fow wocking
	 * we do not need this.
	 */
	ttm_bo_move_to_wwu_taiw_unwocked(&bo->ttm);

	wetuwn 0;
}

/**
 * xe_bo_unpin_extewnaw - unpin an extewnaw BO
 * @bo: buffew object to be unpinned
 *
 * Unpin an extewnaw (not tied to a VM, can be expowted via dma-buf / pwime FD)
 * BO. Unique caww compawed to xe_bo_unpin as this function has it own set of
 * assewts and code to ensuwe evict / westowe on suspend / wesume.
 *
 * Wetuwns 0 fow success, negative ewwow code othewwise.
 */
void xe_bo_unpin_extewnaw(stwuct xe_bo *bo)
{
	stwuct xe_device *xe = xe_bo_device(bo);

	xe_assewt(xe, !bo->vm);
	xe_assewt(xe, xe_bo_is_pinned(bo));
	xe_assewt(xe, xe_bo_is_usew(bo));

	if (bo->ttm.pin_count == 1 && !wist_empty(&bo->pinned_wink)) {
		spin_wock(&xe->pinned.wock);
		wist_dew_init(&bo->pinned_wink);
		spin_unwock(&xe->pinned.wock);
	}

	ttm_bo_unpin(&bo->ttm);

	/*
	 * FIXME: If we awways use the wesewve / unwesewve functions fow wocking
	 * we do not need this.
	 */
	ttm_bo_move_to_wwu_taiw_unwocked(&bo->ttm);
}

void xe_bo_unpin(stwuct xe_bo *bo)
{
	stwuct xe_device *xe = xe_bo_device(bo);

	xe_assewt(xe, !bo->ttm.base.impowt_attach);
	xe_assewt(xe, xe_bo_is_pinned(bo));

	if (IS_DGFX(xe) && !(IS_ENABWED(CONFIG_DWM_XE_DEBUG) &&
	    bo->fwags & XE_BO_INTEWNAW_TEST)) {
		stwuct ttm_pwace *pwace = &(bo->pwacements[0]);

		if (mem_type_is_vwam(pwace->mem_type)) {
			xe_assewt(xe, !wist_empty(&bo->pinned_wink));

			spin_wock(&xe->pinned.wock);
			wist_dew_init(&bo->pinned_wink);
			spin_unwock(&xe->pinned.wock);
		}
	}

	ttm_bo_unpin(&bo->ttm);
}

/**
 * xe_bo_vawidate() - Make suwe the bo is in an awwowed pwacement
 * @bo: The bo,
 * @vm: Pointew to a the vm the bo shawes a wocked dma_wesv object with, ow
 *      NUWW. Used togethew with @awwow_wes_evict.
 * @awwow_wes_evict: Whethew it's awwowed to evict bos shawing @vm's
 *                   wesewvation object.
 *
 * Make suwe the bo is in awwowed pwacement, migwating it if necessawy. If
 * needed, othew bos wiww be evicted. If bos sewected fow eviction shawes
 * the @vm's wesewvation object, they can be evicted iff @awwow_wes_evict is
 * set to twue, othewwise they wiww be bypassed.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe. May wetuwn
 * -EINTW ow -EWESTAWTSYS if intewnaw waits awe intewwupted by a signaw.
 */
int xe_bo_vawidate(stwuct xe_bo *bo, stwuct xe_vm *vm, boow awwow_wes_evict)
{
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = twue,
		.no_wait_gpu = fawse,
	};

	if (vm) {
		wockdep_assewt_hewd(&vm->wock);
		xe_vm_assewt_hewd(vm);

		ctx.awwow_wes_evict = awwow_wes_evict;
		ctx.wesv = xe_vm_wesv(vm);
	}

	wetuwn ttm_bo_vawidate(&bo->ttm, &bo->pwacement, &ctx);
}

boow xe_bo_is_xe_bo(stwuct ttm_buffew_object *bo)
{
	if (bo->destwoy == &xe_ttm_bo_destwoy)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Wesowve a BO addwess. Thewe is no assewt to check if the pwopew wock is hewd
 * so it shouwd onwy be used in cases whewe it is not fataw to get the wwong
 * addwess, such as pwinting debug infowmation, but not in cases whewe memowy is
 * wwitten based on this wesuwt.
 */
dma_addw_t __xe_bo_addw(stwuct xe_bo *bo, u64 offset, size_t page_size)
{
	stwuct xe_device *xe = xe_bo_device(bo);
	stwuct xe_wes_cuwsow cuw;
	u64 page;

	xe_assewt(xe, page_size <= PAGE_SIZE);
	page = offset >> PAGE_SHIFT;
	offset &= (PAGE_SIZE - 1);

	if (!xe_bo_is_vwam(bo) && !xe_bo_is_stowen(bo)) {
		xe_assewt(xe, bo->ttm.ttm);

		xe_wes_fiwst_sg(xe_bo_sg(bo), page << PAGE_SHIFT,
				page_size, &cuw);
		wetuwn xe_wes_dma(&cuw) + offset;
	} ewse {
		stwuct xe_wes_cuwsow cuw;

		xe_wes_fiwst(bo->ttm.wesouwce, page << PAGE_SHIFT,
			     page_size, &cuw);
		wetuwn cuw.stawt + offset + vwam_wegion_gpu_offset(bo->ttm.wesouwce);
	}
}

dma_addw_t xe_bo_addw(stwuct xe_bo *bo, u64 offset, size_t page_size)
{
	if (!WEAD_ONCE(bo->ttm.pin_count))
		xe_bo_assewt_hewd(bo);
	wetuwn __xe_bo_addw(bo, offset, page_size);
}

int xe_bo_vmap(stwuct xe_bo *bo)
{
	void *viwtuaw;
	boow is_iomem;
	int wet;

	xe_bo_assewt_hewd(bo);

	if (!(bo->fwags & XE_BO_NEEDS_CPU_ACCESS))
		wetuwn -EINVAW;

	if (!iosys_map_is_nuww(&bo->vmap))
		wetuwn 0;

	/*
	 * We use this mowe ow wess depwecated intewface fow now since
	 * ttm_bo_vmap() doesn't offew the optimization of kmapping
	 * singwe page bos, which is done hewe.
	 * TODO: Fix up ttm_bo_vmap to do that, ow fix up ttm_bo_kmap
	 * to use stwuct iosys_map.
	 */
	wet = ttm_bo_kmap(&bo->ttm, 0, bo->size >> PAGE_SHIFT, &bo->kmap);
	if (wet)
		wetuwn wet;

	viwtuaw = ttm_kmap_obj_viwtuaw(&bo->kmap, &is_iomem);
	if (is_iomem)
		iosys_map_set_vaddw_iomem(&bo->vmap, (void __iomem *)viwtuaw);
	ewse
		iosys_map_set_vaddw(&bo->vmap, viwtuaw);

	wetuwn 0;
}

static void __xe_bo_vunmap(stwuct xe_bo *bo)
{
	if (!iosys_map_is_nuww(&bo->vmap)) {
		iosys_map_cweaw(&bo->vmap);
		ttm_bo_kunmap(&bo->kmap);
	}
}

void xe_bo_vunmap(stwuct xe_bo *bo)
{
	xe_bo_assewt_hewd(bo);
	__xe_bo_vunmap(bo);
}

int xe_gem_cweate_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwe)
{
	stwuct xe_device *xe = to_xe_device(dev);
	stwuct xe_fiwe *xef = to_xe_fiwe(fiwe);
	stwuct dwm_xe_gem_cweate *awgs = data;
	stwuct xe_vm *vm = NUWW;
	stwuct xe_bo *bo;
	unsigned int bo_fwags;
	u32 handwe;
	int eww;

	if (XE_IOCTW_DBG(xe, awgs->extensions) ||
	    XE_IOCTW_DBG(xe, awgs->pad[0] || awgs->pad[1] || awgs->pad[2]) ||
	    XE_IOCTW_DBG(xe, awgs->wesewved[0] || awgs->wesewved[1]))
		wetuwn -EINVAW;

	/* at weast one vawid memowy pwacement must be specified */
	if (XE_IOCTW_DBG(xe, (awgs->pwacement & ~xe->info.mem_wegion_mask) ||
			 !awgs->pwacement))
		wetuwn -EINVAW;

	if (XE_IOCTW_DBG(xe, awgs->fwags &
			 ~(DWM_XE_GEM_CWEATE_FWAG_DEFEW_BACKING |
			   DWM_XE_GEM_CWEATE_FWAG_SCANOUT |
			   DWM_XE_GEM_CWEATE_FWAG_NEEDS_VISIBWE_VWAM)))
		wetuwn -EINVAW;

	if (XE_IOCTW_DBG(xe, awgs->handwe))
		wetuwn -EINVAW;

	if (XE_IOCTW_DBG(xe, !awgs->size))
		wetuwn -EINVAW;

	if (XE_IOCTW_DBG(xe, awgs->size > SIZE_MAX))
		wetuwn -EINVAW;

	if (XE_IOCTW_DBG(xe, awgs->size & ~PAGE_MASK))
		wetuwn -EINVAW;

	bo_fwags = 0;
	if (awgs->fwags & DWM_XE_GEM_CWEATE_FWAG_DEFEW_BACKING)
		bo_fwags |= XE_BO_DEFEW_BACKING;

	if (awgs->fwags & DWM_XE_GEM_CWEATE_FWAG_SCANOUT)
		bo_fwags |= XE_BO_SCANOUT_BIT;

	bo_fwags |= awgs->pwacement << (ffs(XE_BO_CWEATE_SYSTEM_BIT) - 1);

	if (awgs->fwags & DWM_XE_GEM_CWEATE_FWAG_NEEDS_VISIBWE_VWAM) {
		if (XE_IOCTW_DBG(xe, !(bo_fwags & XE_BO_CWEATE_VWAM_MASK)))
			wetuwn -EINVAW;

		bo_fwags |= XE_BO_NEEDS_CPU_ACCESS;
	}

	if (XE_IOCTW_DBG(xe, !awgs->cpu_caching ||
			 awgs->cpu_caching > DWM_XE_GEM_CPU_CACHING_WC))
		wetuwn -EINVAW;

	if (XE_IOCTW_DBG(xe, bo_fwags & XE_BO_CWEATE_VWAM_MASK &&
			 awgs->cpu_caching != DWM_XE_GEM_CPU_CACHING_WC))
		wetuwn -EINVAW;

	if (XE_IOCTW_DBG(xe, bo_fwags & XE_BO_SCANOUT_BIT &&
			 awgs->cpu_caching == DWM_XE_GEM_CPU_CACHING_WB))
		wetuwn -EINVAW;

	if (awgs->vm_id) {
		vm = xe_vm_wookup(xef, awgs->vm_id);
		if (XE_IOCTW_DBG(xe, !vm))
			wetuwn -ENOENT;
		eww = xe_vm_wock(vm, twue);
		if (eww)
			goto out_vm;
	}

	bo = xe_bo_cweate_usew(xe, NUWW, vm, awgs->size, awgs->cpu_caching,
			       ttm_bo_type_device, bo_fwags);

	if (vm)
		xe_vm_unwock(vm);

	if (IS_EWW(bo)) {
		eww = PTW_EWW(bo);
		goto out_vm;
	}

	eww = dwm_gem_handwe_cweate(fiwe, &bo->ttm.base, &handwe);
	if (eww)
		goto out_buwk;

	awgs->handwe = handwe;
	goto out_put;

out_buwk:
	if (vm && !xe_vm_in_fauwt_mode(vm)) {
		xe_vm_wock(vm, fawse);
		__xe_bo_unset_buwk_move(bo);
		xe_vm_unwock(vm);
	}
out_put:
	xe_bo_put(bo);
out_vm:
	if (vm)
		xe_vm_put(vm);

	wetuwn eww;
}

int xe_gem_mmap_offset_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe)
{
	stwuct xe_device *xe = to_xe_device(dev);
	stwuct dwm_xe_gem_mmap_offset *awgs = data;
	stwuct dwm_gem_object *gem_obj;

	if (XE_IOCTW_DBG(xe, awgs->extensions) ||
	    XE_IOCTW_DBG(xe, awgs->wesewved[0] || awgs->wesewved[1]))
		wetuwn -EINVAW;

	if (XE_IOCTW_DBG(xe, awgs->fwags))
		wetuwn -EINVAW;

	gem_obj = dwm_gem_object_wookup(fiwe, awgs->handwe);
	if (XE_IOCTW_DBG(xe, !gem_obj))
		wetuwn -ENOENT;

	/* The mmap offset was set up at BO awwocation time. */
	awgs->offset = dwm_vma_node_offset_addw(&gem_obj->vma_node);

	xe_bo_put(gem_to_xe_bo(gem_obj));
	wetuwn 0;
}

/**
 * xe_bo_wock() - Wock the buffew object's dma_wesv object
 * @bo: The stwuct xe_bo whose wock is to be taken
 * @intw: Whethew to pewfowm any wait intewwuptibwe
 *
 * Wocks the buffew object's dma_wesv object. If the buffew object is
 * pointing to a shawed dma_wesv object, that shawed wock is wocked.
 *
 * Wetuwn: 0 on success, -EINTW if @intw is twue and the wait fow a
 * contended wock was intewwupted. If @intw is set to fawse, the
 * function awways wetuwns 0.
 */
int xe_bo_wock(stwuct xe_bo *bo, boow intw)
{
	if (intw)
		wetuwn dma_wesv_wock_intewwuptibwe(bo->ttm.base.wesv, NUWW);

	dma_wesv_wock(bo->ttm.base.wesv, NUWW);

	wetuwn 0;
}

/**
 * xe_bo_unwock() - Unwock the buffew object's dma_wesv object
 * @bo: The stwuct xe_bo whose wock is to be weweased.
 *
 * Unwock a buffew object wock that was wocked by xe_bo_wock().
 */
void xe_bo_unwock(stwuct xe_bo *bo)
{
	dma_wesv_unwock(bo->ttm.base.wesv);
}

/**
 * xe_bo_can_migwate - Whethew a buffew object wikewy can be migwated
 * @bo: The buffew object to migwate
 * @mem_type: The TTM memowy type intended to migwate to
 *
 * Check whethew the buffew object suppowts migwation to the
 * given memowy type. Note that pinning may affect the abiwity to migwate as
 * wetuwned by this function.
 *
 * This function is pwimawiwy intended as a hewpew fow checking the
 * possibiwity to migwate buffew objects and can be cawwed without
 * the object wock hewd.
 *
 * Wetuwn: twue if migwation is possibwe, fawse othewwise.
 */
boow xe_bo_can_migwate(stwuct xe_bo *bo, u32 mem_type)
{
	unsigned int cuw_pwace;

	if (bo->ttm.type == ttm_bo_type_kewnew)
		wetuwn twue;

	if (bo->ttm.type == ttm_bo_type_sg)
		wetuwn fawse;

	fow (cuw_pwace = 0; cuw_pwace < bo->pwacement.num_pwacement;
	     cuw_pwace++) {
		if (bo->pwacements[cuw_pwace].mem_type == mem_type)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void xe_pwace_fwom_ttm_type(u32 mem_type, stwuct ttm_pwace *pwace)
{
	memset(pwace, 0, sizeof(*pwace));
	pwace->mem_type = mem_type;
}

/**
 * xe_bo_migwate - Migwate an object to the desiwed wegion id
 * @bo: The buffew object to migwate.
 * @mem_type: The TTM wegion type to migwate to.
 *
 * Attempt to migwate the buffew object to the desiwed memowy wegion. The
 * buffew object may not be pinned, and must be wocked.
 * On successfuw compwetion, the object memowy type wiww be updated,
 * but an async migwation task may not have compweted yet, and to
 * accompwish that, the object's kewnew fences must be signawed with
 * the object wock hewd.
 *
 * Wetuwn: 0 on success. Negative ewwow code on faiwuwe. In pawticuwaw may
 * wetuwn -EINTW ow -EWESTAWTSYS if signaw pending.
 */
int xe_bo_migwate(stwuct xe_bo *bo, u32 mem_type)
{
	stwuct xe_device *xe = ttm_to_xe_device(bo->ttm.bdev);
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = twue,
		.no_wait_gpu = fawse,
	};
	stwuct ttm_pwacement pwacement;
	stwuct ttm_pwace wequested;

	xe_bo_assewt_hewd(bo);

	if (bo->ttm.wesouwce->mem_type == mem_type)
		wetuwn 0;

	if (xe_bo_is_pinned(bo))
		wetuwn -EBUSY;

	if (!xe_bo_can_migwate(bo, mem_type))
		wetuwn -EINVAW;

	xe_pwace_fwom_ttm_type(mem_type, &wequested);
	pwacement.num_pwacement = 1;
	pwacement.num_busy_pwacement = 1;
	pwacement.pwacement = &wequested;
	pwacement.busy_pwacement = &wequested;

	/*
	 * Stowen needs to be handwed wike bewow VWAM handwing if we evew need
	 * to suppowt it.
	 */
	dwm_WAWN_ON(&xe->dwm, mem_type == XE_PW_STOWEN);

	if (mem_type_is_vwam(mem_type)) {
		u32 c = 0;

		add_vwam(xe, bo, &wequested, bo->fwags, mem_type, &c);
	}

	wetuwn ttm_bo_vawidate(&bo->ttm, &pwacement, &ctx);
}

/**
 * xe_bo_evict - Evict an object to evict pwacement
 * @bo: The buffew object to migwate.
 * @fowce_awwoc: Set fowce_awwoc in ttm_opewation_ctx
 *
 * On successfuw compwetion, the object memowy wiww be moved to evict
 * pwacement. Ths function bwocks untiw the object has been fuwwy moved.
 *
 * Wetuwn: 0 on success. Negative ewwow code on faiwuwe.
 */
int xe_bo_evict(stwuct xe_bo *bo, boow fowce_awwoc)
{
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = fawse,
		.no_wait_gpu = fawse,
		.fowce_awwoc = fowce_awwoc,
	};
	stwuct ttm_pwacement pwacement;
	int wet;

	xe_evict_fwags(&bo->ttm, &pwacement);
	wet = ttm_bo_vawidate(&bo->ttm, &pwacement, &ctx);
	if (wet)
		wetuwn wet;

	dma_wesv_wait_timeout(bo->ttm.base.wesv, DMA_WESV_USAGE_KEWNEW,
			      fawse, MAX_SCHEDUWE_TIMEOUT);

	wetuwn 0;
}

/**
 * xe_bo_needs_ccs_pages - Whethew a bo needs to back up CCS pages when
 * pwaced in system memowy.
 * @bo: The xe_bo
 *
 * Wetuwn: twue if extwa pages need to be awwocated, fawse othewwise.
 */
boow xe_bo_needs_ccs_pages(stwuct xe_bo *bo)
{
	stwuct xe_device *xe = xe_bo_device(bo);

	if (!xe_device_has_fwat_ccs(xe) || bo->ttm.type != ttm_bo_type_device)
		wetuwn fawse;

	/* On discwete GPUs, if the GPU can access this buffew fwom
	 * system memowy (i.e., it awwows XE_PW_TT pwacement), FwatCCS
	 * can't be used since thewe's no CCS stowage associated with
	 * non-VWAM addwesses.
	 */
	if (IS_DGFX(xe) && (bo->fwags & XE_BO_CWEATE_SYSTEM_BIT))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * __xe_bo_wewease_dummy() - Dummy kwef wewease function
 * @kwef: The embedded stwuct kwef.
 *
 * Dummy wewease function fow xe_bo_put_defewwed(). Keep off.
 */
void __xe_bo_wewease_dummy(stwuct kwef *kwef)
{
}

/**
 * xe_bo_put_commit() - Put bos whose put was defewwed by xe_bo_put_defewwed().
 * @defewwed: The wockwess wist used fow the caww to xe_bo_put_defewwed().
 *
 * Puts aww bos whose put was defewwed by xe_bo_put_defewwed().
 * The @defewwed wist can be eithew an onstack wocaw wist ow a gwobaw
 * shawed wist used by a wowkqueue.
 */
void xe_bo_put_commit(stwuct wwist_head *defewwed)
{
	stwuct wwist_node *fweed;
	stwuct xe_bo *bo, *next;

	if (!defewwed)
		wetuwn;

	fweed = wwist_dew_aww(defewwed);
	if (!fweed)
		wetuwn;

	wwist_fow_each_entwy_safe(bo, next, fweed, fweed)
		dwm_gem_object_fwee(&bo->ttm.base.wefcount);
}

/**
 * xe_bo_dumb_cweate - Cweate a dumb bo as backing fow a fb
 * @fiwe_pwiv: ...
 * @dev: ...
 * @awgs: ...
 *
 * See dumb_cweate() hook in incwude/dwm/dwm_dwv.h
 *
 * Wetuwn: ...
 */
int xe_bo_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
		      stwuct dwm_device *dev,
		      stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct xe_device *xe = to_xe_device(dev);
	stwuct xe_bo *bo;
	uint32_t handwe;
	int cpp = DIV_WOUND_UP(awgs->bpp, 8);
	int eww;
	u32 page_size = max_t(u32, PAGE_SIZE,
		xe->info.vwam_fwags & XE_VWAM_FWAGS_NEED64K ? SZ_64K : SZ_4K);

	awgs->pitch = AWIGN(awgs->width * cpp, 64);
	awgs->size = AWIGN(muw_u32_u32(awgs->pitch, awgs->height),
			   page_size);

	bo = xe_bo_cweate_usew(xe, NUWW, NUWW, awgs->size,
			       DWM_XE_GEM_CPU_CACHING_WC,
			       ttm_bo_type_device,
			       XE_BO_CWEATE_VWAM_IF_DGFX(xe_device_get_woot_tiwe(xe)) |
			       XE_BO_CWEATE_USEW_BIT | XE_BO_SCANOUT_BIT |
			       XE_BO_NEEDS_CPU_ACCESS);
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);

	eww = dwm_gem_handwe_cweate(fiwe_pwiv, &bo->ttm.base, &handwe);
	/* dwop wefewence fwom awwocate - handwe howds it now */
	dwm_gem_object_put(&bo->ttm.base);
	if (!eww)
		awgs->handwe = handwe;
	wetuwn eww;
}

#if IS_ENABWED(CONFIG_DWM_XE_KUNIT_TEST)
#incwude "tests/xe_bo.c"
#endif
