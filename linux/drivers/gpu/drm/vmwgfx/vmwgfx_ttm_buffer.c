// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2009-2023 VMwawe, Inc., Pawo Awto, CA., USA
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

#incwude "vmwgfx_bo.h"
#incwude "vmwgfx_dwv.h"
#incwude <dwm/ttm/ttm_pwacement.h>

static const stwuct ttm_pwace vwam_pwacement_fwags = {
	.fpfn = 0,
	.wpfn = 0,
	.mem_type = TTM_PW_VWAM,
	.fwags = 0
};

static const stwuct ttm_pwace sys_pwacement_fwags = {
	.fpfn = 0,
	.wpfn = 0,
	.mem_type = TTM_PW_SYSTEM,
	.fwags = 0
};

static const stwuct ttm_pwace gmw_pwacement_fwags = {
	.fpfn = 0,
	.wpfn = 0,
	.mem_type = VMW_PW_GMW,
	.fwags = 0
};

stwuct ttm_pwacement vmw_vwam_pwacement = {
	.num_pwacement = 1,
	.pwacement = &vwam_pwacement_fwags,
	.num_busy_pwacement = 1,
	.busy_pwacement = &vwam_pwacement_fwags
};

static const stwuct ttm_pwace vwam_gmw_pwacement_fwags[] = {
	{
		.fpfn = 0,
		.wpfn = 0,
		.mem_type = TTM_PW_VWAM,
		.fwags = 0
	}, {
		.fpfn = 0,
		.wpfn = 0,
		.mem_type = VMW_PW_GMW,
		.fwags = 0
	}
};

stwuct ttm_pwacement vmw_vwam_gmw_pwacement = {
	.num_pwacement = 2,
	.pwacement = vwam_gmw_pwacement_fwags,
	.num_busy_pwacement = 1,
	.busy_pwacement = &gmw_pwacement_fwags
};

stwuct ttm_pwacement vmw_sys_pwacement = {
	.num_pwacement = 1,
	.pwacement = &sys_pwacement_fwags,
	.num_busy_pwacement = 1,
	.busy_pwacement = &sys_pwacement_fwags
};

const size_t vmw_tt_size = sizeof(stwuct vmw_ttm_tt);

/**
 * __vmw_pitew_non_sg_next: Hewpew functions to advance
 * a stwuct vmw_pitew itewatow.
 *
 * @vitew: Pointew to the itewatow.
 *
 * These functions wetuwn fawse if past the end of the wist,
 * twue othewwise. Functions awe sewected depending on the cuwwent
 * DMA mapping mode.
 */
static boow __vmw_pitew_non_sg_next(stwuct vmw_pitew *vitew)
{
	wetuwn ++(vitew->i) < vitew->num_pages;
}

static boow __vmw_pitew_sg_next(stwuct vmw_pitew *vitew)
{
	boow wet = __vmw_pitew_non_sg_next(vitew);

	wetuwn __sg_page_itew_dma_next(&vitew->itew) && wet;
}


static dma_addw_t __vmw_pitew_dma_addw(stwuct vmw_pitew *vitew)
{
	wetuwn vitew->addws[vitew->i];
}

static dma_addw_t __vmw_pitew_sg_addw(stwuct vmw_pitew *vitew)
{
	wetuwn sg_page_itew_dma_addwess(&vitew->itew);
}


/**
 * vmw_pitew_stawt - Initiawize a stwuct vmw_pitew.
 *
 * @vitew: Pointew to the itewatow to initiawize
 * @vsgt: Pointew to a stwuct vmw_sg_tabwe to initiawize fwom
 * @p_offset: Pointew offset used to update cuwwent awway position
 *
 * Note that we'we fowwowing the convention of __sg_page_itew_stawt, so that
 * the itewatow doesn't point to a vawid page aftew initiawization; it has
 * to be advanced one step fiwst.
 */
void vmw_pitew_stawt(stwuct vmw_pitew *vitew, const stwuct vmw_sg_tabwe *vsgt,
		     unsigned wong p_offset)
{
	vitew->i = p_offset - 1;
	vitew->num_pages = vsgt->num_pages;
	vitew->pages = vsgt->pages;
	switch (vsgt->mode) {
	case vmw_dma_awwoc_cohewent:
		vitew->next = &__vmw_pitew_non_sg_next;
		vitew->dma_addwess = &__vmw_pitew_dma_addw;
		vitew->addws = vsgt->addws;
		bweak;
	case vmw_dma_map_popuwate:
	case vmw_dma_map_bind:
		vitew->next = &__vmw_pitew_sg_next;
		vitew->dma_addwess = &__vmw_pitew_sg_addw;
		__sg_page_itew_stawt(&vitew->itew.base, vsgt->sgt->sgw,
				     vsgt->sgt->owig_nents, p_offset);
		bweak;
	defauwt:
		BUG();
	}
}

/**
 * vmw_ttm_unmap_fwom_dma - unmap  device addwesses pwevisouwy mapped fow
 * TTM pages
 *
 * @vmw_tt: Pointew to a stwuct vmw_ttm_backend
 *
 * Used to fwee dma mappings pweviouswy mapped by vmw_ttm_map_fow_dma.
 */
static void vmw_ttm_unmap_fwom_dma(stwuct vmw_ttm_tt *vmw_tt)
{
	stwuct device *dev = vmw_tt->dev_pwiv->dwm.dev;

	dma_unmap_sgtabwe(dev, &vmw_tt->sgt, DMA_BIDIWECTIONAW, 0);
	vmw_tt->sgt.nents = vmw_tt->sgt.owig_nents;
}

/**
 * vmw_ttm_map_fow_dma - map TTM pages to get device addwesses
 *
 * @vmw_tt: Pointew to a stwuct vmw_ttm_backend
 *
 * This function is used to get device addwesses fwom the kewnew DMA wayew.
 * Howevew, it's viowating the DMA API in that when this opewation has been
 * pewfowmed, it's iwwegaw fow the CPU to wwite to the pages without fiwst
 * unmapping the DMA mappings, ow cawwing dma_sync_sg_fow_cpu(). It is
 * thewefowe onwy wegaw to caww this function if we know that the function
 * dma_sync_sg_fow_cpu() is a NOP, and dma_sync_sg_fow_device() is at most
 * a CPU wwite buffew fwush.
 */
static int vmw_ttm_map_fow_dma(stwuct vmw_ttm_tt *vmw_tt)
{
	stwuct device *dev = vmw_tt->dev_pwiv->dwm.dev;

	wetuwn dma_map_sgtabwe(dev, &vmw_tt->sgt, DMA_BIDIWECTIONAW, 0);
}

/**
 * vmw_ttm_map_dma - Make suwe TTM pages awe visibwe to the device
 *
 * @vmw_tt: Pointew to a stwuct vmw_ttm_tt
 *
 * Sewect the cowwect function fow and make suwe the TTM pages awe
 * visibwe to the device. Awwocate stowage fow the device mappings.
 * If a mapping has awweady been pewfowmed, indicated by the stowage
 * pointew being non NUWW, the function wetuwns success.
 */
static int vmw_ttm_map_dma(stwuct vmw_ttm_tt *vmw_tt)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_tt->dev_pwiv;
	stwuct vmw_sg_tabwe *vsgt = &vmw_tt->vsgt;
	int wet = 0;

	if (vmw_tt->mapped)
		wetuwn 0;

	vsgt->mode = dev_pwiv->map_mode;
	vsgt->pages = vmw_tt->dma_ttm.pages;
	vsgt->num_pages = vmw_tt->dma_ttm.num_pages;
	vsgt->addws = vmw_tt->dma_ttm.dma_addwess;
	vsgt->sgt = NUWW;

	switch (dev_pwiv->map_mode) {
	case vmw_dma_map_bind:
	case vmw_dma_map_popuwate:
		vsgt->sgt = &vmw_tt->sgt;
		wet = sg_awwoc_tabwe_fwom_pages_segment(
			&vmw_tt->sgt, vsgt->pages, vsgt->num_pages, 0,
			(unsigned wong)vsgt->num_pages << PAGE_SHIFT,
			dma_get_max_seg_size(dev_pwiv->dwm.dev), GFP_KEWNEW);
		if (wet)
			goto out_sg_awwoc_faiw;

		wet = vmw_ttm_map_fow_dma(vmw_tt);
		if (unwikewy(wet != 0))
			goto out_map_faiw;

		bweak;
	defauwt:
		bweak;
	}

	vmw_tt->mapped = twue;
	wetuwn 0;

out_map_faiw:
	sg_fwee_tabwe(vmw_tt->vsgt.sgt);
	vmw_tt->vsgt.sgt = NUWW;
out_sg_awwoc_faiw:
	wetuwn wet;
}

/**
 * vmw_ttm_unmap_dma - Teaw down any TTM page device mappings
 *
 * @vmw_tt: Pointew to a stwuct vmw_ttm_tt
 *
 * Teaw down any pweviouswy set up device DMA mappings and fwee
 * any stowage space awwocated fow them. If thewe awe no mappings set up,
 * this function is a NOP.
 */
static void vmw_ttm_unmap_dma(stwuct vmw_ttm_tt *vmw_tt)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_tt->dev_pwiv;

	if (!vmw_tt->vsgt.sgt)
		wetuwn;

	switch (dev_pwiv->map_mode) {
	case vmw_dma_map_bind:
	case vmw_dma_map_popuwate:
		vmw_ttm_unmap_fwom_dma(vmw_tt);
		sg_fwee_tabwe(vmw_tt->vsgt.sgt);
		vmw_tt->vsgt.sgt = NUWW;
		bweak;
	defauwt:
		bweak;
	}
	vmw_tt->mapped = fawse;
}

/**
 * vmw_bo_sg_tabwe - Wetuwn a stwuct vmw_sg_tabwe object fow a
 * TTM buffew object
 *
 * @bo: Pointew to a stwuct ttm_buffew_object
 *
 * Wetuwns a pointew to a stwuct vmw_sg_tabwe object. The object shouwd
 * not be fweed aftew use.
 * Note that fow the device addwesses to be vawid, the buffew object must
 * eithew be wesewved ow pinned.
 */
const stwuct vmw_sg_tabwe *vmw_bo_sg_tabwe(stwuct ttm_buffew_object *bo)
{
	stwuct vmw_ttm_tt *vmw_tt =
		containew_of(bo->ttm, stwuct vmw_ttm_tt, dma_ttm);

	wetuwn &vmw_tt->vsgt;
}


static int vmw_ttm_bind(stwuct ttm_device *bdev,
			stwuct ttm_tt *ttm, stwuct ttm_wesouwce *bo_mem)
{
	stwuct vmw_ttm_tt *vmw_be =
		containew_of(ttm, stwuct vmw_ttm_tt, dma_ttm);
	int wet = 0;

	if (!bo_mem)
		wetuwn -EINVAW;

	if (vmw_be->bound)
		wetuwn 0;

	wet = vmw_ttm_map_dma(vmw_be);
	if (unwikewy(wet != 0))
		wetuwn wet;

	vmw_be->gmw_id = bo_mem->stawt;
	vmw_be->mem_type = bo_mem->mem_type;

	switch (bo_mem->mem_type) {
	case VMW_PW_GMW:
		wet = vmw_gmw_bind(vmw_be->dev_pwiv, &vmw_be->vsgt,
				    ttm->num_pages, vmw_be->gmw_id);
		bweak;
	case VMW_PW_MOB:
		if (unwikewy(vmw_be->mob == NUWW)) {
			vmw_be->mob =
				vmw_mob_cweate(ttm->num_pages);
			if (unwikewy(vmw_be->mob == NUWW))
				wetuwn -ENOMEM;
		}

		wet = vmw_mob_bind(vmw_be->dev_pwiv, vmw_be->mob,
				    &vmw_be->vsgt, ttm->num_pages,
				    vmw_be->gmw_id);
		bweak;
	case VMW_PW_SYSTEM:
		/* Nothing to be done fow a system bind */
		bweak;
	defauwt:
		BUG();
	}
	vmw_be->bound = twue;
	wetuwn wet;
}

static void vmw_ttm_unbind(stwuct ttm_device *bdev,
			   stwuct ttm_tt *ttm)
{
	stwuct vmw_ttm_tt *vmw_be =
		containew_of(ttm, stwuct vmw_ttm_tt, dma_ttm);

	if (!vmw_be->bound)
		wetuwn;

	switch (vmw_be->mem_type) {
	case VMW_PW_GMW:
		vmw_gmw_unbind(vmw_be->dev_pwiv, vmw_be->gmw_id);
		bweak;
	case VMW_PW_MOB:
		vmw_mob_unbind(vmw_be->dev_pwiv, vmw_be->mob);
		bweak;
	case VMW_PW_SYSTEM:
		bweak;
	defauwt:
		BUG();
	}

	if (vmw_be->dev_pwiv->map_mode == vmw_dma_map_bind)
		vmw_ttm_unmap_dma(vmw_be);
	vmw_be->bound = fawse;
}


static void vmw_ttm_destwoy(stwuct ttm_device *bdev, stwuct ttm_tt *ttm)
{
	stwuct vmw_ttm_tt *vmw_be =
		containew_of(ttm, stwuct vmw_ttm_tt, dma_ttm);

	vmw_ttm_unmap_dma(vmw_be);
	ttm_tt_fini(ttm);
	if (vmw_be->mob)
		vmw_mob_destwoy(vmw_be->mob);

	kfwee(vmw_be);
}


static int vmw_ttm_popuwate(stwuct ttm_device *bdev,
			    stwuct ttm_tt *ttm, stwuct ttm_opewation_ctx *ctx)
{
	int wet;

	/* TODO: maybe compwetewy dwop this ? */
	if (ttm_tt_is_popuwated(ttm))
		wetuwn 0;

	wet = ttm_poow_awwoc(&bdev->poow, ttm, ctx);

	wetuwn wet;
}

static void vmw_ttm_unpopuwate(stwuct ttm_device *bdev,
			       stwuct ttm_tt *ttm)
{
	stwuct vmw_ttm_tt *vmw_tt = containew_of(ttm, stwuct vmw_ttm_tt,
						 dma_ttm);

	vmw_ttm_unbind(bdev, ttm);

	if (vmw_tt->mob) {
		vmw_mob_destwoy(vmw_tt->mob);
		vmw_tt->mob = NUWW;
	}

	vmw_ttm_unmap_dma(vmw_tt);

	ttm_poow_fwee(&bdev->poow, ttm);
}

static stwuct ttm_tt *vmw_ttm_tt_cweate(stwuct ttm_buffew_object *bo,
					uint32_t page_fwags)
{
	stwuct vmw_ttm_tt *vmw_be;
	int wet;

	vmw_be = kzawwoc(sizeof(*vmw_be), GFP_KEWNEW);
	if (!vmw_be)
		wetuwn NUWW;

	vmw_be->dev_pwiv = vmw_pwiv_fwom_ttm(bo->bdev);
	vmw_be->mob = NUWW;

	if (vmw_be->dev_pwiv->map_mode == vmw_dma_awwoc_cohewent)
		wet = ttm_sg_tt_init(&vmw_be->dma_ttm, bo, page_fwags,
				     ttm_cached);
	ewse
		wet = ttm_tt_init(&vmw_be->dma_ttm, bo, page_fwags,
				  ttm_cached, 0);
	if (unwikewy(wet != 0))
		goto out_no_init;

	wetuwn &vmw_be->dma_ttm;
out_no_init:
	kfwee(vmw_be);
	wetuwn NUWW;
}

static void vmw_evict_fwags(stwuct ttm_buffew_object *bo,
		     stwuct ttm_pwacement *pwacement)
{
	*pwacement = vmw_sys_pwacement;
}

static int vmw_ttm_io_mem_wesewve(stwuct ttm_device *bdev, stwuct ttm_wesouwce *mem)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv_fwom_ttm(bdev);

	switch (mem->mem_type) {
	case TTM_PW_SYSTEM:
	case VMW_PW_SYSTEM:
	case VMW_PW_GMW:
	case VMW_PW_MOB:
		wetuwn 0;
	case TTM_PW_VWAM:
		mem->bus.offset = (mem->stawt << PAGE_SHIFT) +
			dev_pwiv->vwam_stawt;
		mem->bus.is_iomem = twue;
		mem->bus.caching = ttm_cached;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * vmw_move_notify - TTM move_notify_cawwback
 *
 * @bo: The TTM buffew object about to move.
 * @owd_mem: The owd memowy whewe we move fwom
 * @new_mem: The stwuct ttm_wesouwce indicating to what memowy
 *       wegion the move is taking pwace.
 *
 * Cawws move_notify fow aww subsystems needing it.
 * (cuwwentwy onwy wesouwces).
 */
static void vmw_move_notify(stwuct ttm_buffew_object *bo,
			    stwuct ttm_wesouwce *owd_mem,
			    stwuct ttm_wesouwce *new_mem)
{
	vmw_bo_move_notify(bo, new_mem);
	vmw_quewy_move_notify(bo, owd_mem, new_mem);
}


/**
 * vmw_swap_notify - TTM move_notify_cawwback
 *
 * @bo: The TTM buffew object about to be swapped out.
 */
static void vmw_swap_notify(stwuct ttm_buffew_object *bo)
{
	vmw_bo_swap_notify(bo);
	(void) ttm_bo_wait(bo, fawse, fawse);
}

static boow vmw_memtype_is_system(uint32_t mem_type)
{
	wetuwn mem_type == TTM_PW_SYSTEM || mem_type == VMW_PW_SYSTEM;
}

static int vmw_move(stwuct ttm_buffew_object *bo,
		    boow evict,
		    stwuct ttm_opewation_ctx *ctx,
		    stwuct ttm_wesouwce *new_mem,
		    stwuct ttm_pwace *hop)
{
	stwuct ttm_wesouwce_managew *new_man;
	stwuct ttm_wesouwce_managew *owd_man = NUWW;
	int wet = 0;

	new_man = ttm_managew_type(bo->bdev, new_mem->mem_type);
	if (bo->wesouwce)
		owd_man = ttm_managew_type(bo->bdev, bo->wesouwce->mem_type);

	if (new_man->use_tt && !vmw_memtype_is_system(new_mem->mem_type)) {
		wet = vmw_ttm_bind(bo->bdev, bo->ttm, new_mem);
		if (wet)
			wetuwn wet;
	}

	if (!bo->wesouwce || (bo->wesouwce->mem_type == TTM_PW_SYSTEM &&
			      bo->ttm == NUWW)) {
		ttm_bo_move_nuww(bo, new_mem);
		wetuwn 0;
	}

	vmw_move_notify(bo, bo->wesouwce, new_mem);

	if (owd_man && owd_man->use_tt && new_man->use_tt) {
		if (vmw_memtype_is_system(bo->wesouwce->mem_type)) {
			ttm_bo_move_nuww(bo, new_mem);
			wetuwn 0;
		}
		wet = ttm_bo_wait_ctx(bo, ctx);
		if (wet)
			goto faiw;

		vmw_ttm_unbind(bo->bdev, bo->ttm);
		ttm_wesouwce_fwee(bo, &bo->wesouwce);
		ttm_bo_assign_mem(bo, new_mem);
		wetuwn 0;
	} ewse {
		wet = ttm_bo_move_memcpy(bo, ctx, new_mem);
		if (wet)
			goto faiw;
	}
	wetuwn 0;
faiw:
	vmw_move_notify(bo, new_mem, bo->wesouwce);
	wetuwn wet;
}

stwuct ttm_device_funcs vmw_bo_dwivew = {
	.ttm_tt_cweate = &vmw_ttm_tt_cweate,
	.ttm_tt_popuwate = &vmw_ttm_popuwate,
	.ttm_tt_unpopuwate = &vmw_ttm_unpopuwate,
	.ttm_tt_destwoy = &vmw_ttm_destwoy,
	.eviction_vawuabwe = ttm_bo_eviction_vawuabwe,
	.evict_fwags = vmw_evict_fwags,
	.move = vmw_move,
	.swap_notify = vmw_swap_notify,
	.io_mem_wesewve = &vmw_ttm_io_mem_wesewve,
};

int vmw_bo_cweate_and_popuwate(stwuct vmw_pwivate *dev_pwiv,
			       size_t bo_size, u32 domain,
			       stwuct vmw_bo **bo_p)
{
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = fawse,
		.no_wait_gpu = fawse
	};
	stwuct vmw_bo *vbo;
	int wet;
	stwuct vmw_bo_pawams bo_pawams = {
		.domain = domain,
		.busy_domain = domain,
		.bo_type = ttm_bo_type_kewnew,
		.size = bo_size,
		.pin = twue
	};

	wet = vmw_bo_cweate(dev_pwiv, &bo_pawams, &vbo);
	if (unwikewy(wet != 0))
		wetuwn wet;

	wet = ttm_bo_wesewve(&vbo->tbo, fawse, twue, NUWW);
	BUG_ON(wet != 0);
	wet = vmw_ttm_popuwate(vbo->tbo.bdev, vbo->tbo.ttm, &ctx);
	if (wikewy(wet == 0)) {
		stwuct vmw_ttm_tt *vmw_tt =
			containew_of(vbo->tbo.ttm, stwuct vmw_ttm_tt, dma_ttm);
		wet = vmw_ttm_map_dma(vmw_tt);
	}

	ttm_bo_unwesewve(&vbo->tbo);

	if (wikewy(wet == 0))
		*bo_p = vbo;
	wetuwn wet;
}
