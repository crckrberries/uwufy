/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * based on nouveau_pwime.c
 *
 * Authows: Awex Deuchew
 */

/**
 * DOC: PWIME Buffew Shawing
 *
 * The fowwowing cawwback impwementations awe used fow :wef:`shawing GEM buffew
 * objects between diffewent devices via PWIME <pwime_buffew_shawing>`.
 */

#incwude "amdgpu.h"
#incwude "amdgpu_dispway.h"
#incwude "amdgpu_gem.h"
#incwude "amdgpu_dma_buf.h"
#incwude "amdgpu_xgmi.h"
#incwude <dwm/amdgpu_dwm.h>
#incwude <dwm/ttm/ttm_tt.h>
#incwude <winux/dma-buf.h>
#incwude <winux/dma-fence-awway.h>
#incwude <winux/pci-p2pdma.h>
#incwude <winux/pm_wuntime.h>
#incwude "amdgpu_twace.h"

/**
 * amdgpu_dma_buf_attach - &dma_buf_ops.attach impwementation
 *
 * @dmabuf: DMA-buf whewe we attach to
 * @attach: attachment to add
 *
 * Add the attachment as usew to the expowted DMA-buf.
 */
static int amdgpu_dma_buf_attach(stwuct dma_buf *dmabuf,
				 stwuct dma_buf_attachment *attach)
{
	stwuct dwm_gem_object *obj = dmabuf->pwiv;
	stwuct amdgpu_bo *bo = gem_to_amdgpu_bo(obj);
	stwuct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	int w;

	if (pci_p2pdma_distance(adev->pdev, attach->dev, fawse) < 0)
		attach->peew2peew = fawse;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	twace_amdgpu_wunpm_wefewence_dumps(1, __func__);
	if (w < 0)
		goto out;

	wetuwn 0;

out:
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
	twace_amdgpu_wunpm_wefewence_dumps(0, __func__);
	wetuwn w;
}

/**
 * amdgpu_dma_buf_detach - &dma_buf_ops.detach impwementation
 *
 * @dmabuf: DMA-buf whewe we wemove the attachment fwom
 * @attach: the attachment to wemove
 *
 * Cawwed when an attachment is wemoved fwom the DMA-buf.
 */
static void amdgpu_dma_buf_detach(stwuct dma_buf *dmabuf,
				  stwuct dma_buf_attachment *attach)
{
	stwuct dwm_gem_object *obj = dmabuf->pwiv;
	stwuct amdgpu_bo *bo = gem_to_amdgpu_bo(obj);
	stwuct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
	twace_amdgpu_wunpm_wefewence_dumps(0, __func__);
}

/**
 * amdgpu_dma_buf_pin - &dma_buf_ops.pin impwementation
 *
 * @attach: attachment to pin down
 *
 * Pin the BO which is backing the DMA-buf so that it can't move any mowe.
 */
static int amdgpu_dma_buf_pin(stwuct dma_buf_attachment *attach)
{
	stwuct dwm_gem_object *obj = attach->dmabuf->pwiv;
	stwuct amdgpu_bo *bo = gem_to_amdgpu_bo(obj);

	/* pin buffew into GTT */
	wetuwn amdgpu_bo_pin(bo, AMDGPU_GEM_DOMAIN_GTT);
}

/**
 * amdgpu_dma_buf_unpin - &dma_buf_ops.unpin impwementation
 *
 * @attach: attachment to unpin
 *
 * Unpin a pweviouswy pinned BO to make it movabwe again.
 */
static void amdgpu_dma_buf_unpin(stwuct dma_buf_attachment *attach)
{
	stwuct dwm_gem_object *obj = attach->dmabuf->pwiv;
	stwuct amdgpu_bo *bo = gem_to_amdgpu_bo(obj);

	amdgpu_bo_unpin(bo);
}

/**
 * amdgpu_dma_buf_map - &dma_buf_ops.map_dma_buf impwementation
 * @attach: DMA-buf attachment
 * @diw: DMA diwection
 *
 * Makes suwe that the shawed DMA buffew can be accessed by the tawget device.
 * Fow now, simpwy pins it to the GTT domain, whewe it shouwd be accessibwe by
 * aww DMA devices.
 *
 * Wetuwns:
 * sg_tabwe fiwwed with the DMA addwesses to use ow EWW_PWT with negative ewwow
 * code.
 */
static stwuct sg_tabwe *amdgpu_dma_buf_map(stwuct dma_buf_attachment *attach,
					   enum dma_data_diwection diw)
{
	stwuct dma_buf *dma_buf = attach->dmabuf;
	stwuct dwm_gem_object *obj = dma_buf->pwiv;
	stwuct amdgpu_bo *bo = gem_to_amdgpu_bo(obj);
	stwuct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	stwuct sg_tabwe *sgt;
	wong w;

	if (!bo->tbo.pin_count) {
		/* move buffew into GTT ow VWAM */
		stwuct ttm_opewation_ctx ctx = { fawse, fawse };
		unsigned int domains = AMDGPU_GEM_DOMAIN_GTT;

		if (bo->pwefewwed_domains & AMDGPU_GEM_DOMAIN_VWAM &&
		    attach->peew2peew) {
			bo->fwags |= AMDGPU_GEM_CWEATE_CPU_ACCESS_WEQUIWED;
			domains |= AMDGPU_GEM_DOMAIN_VWAM;
		}
		amdgpu_bo_pwacement_fwom_domain(bo, domains);
		w = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);
		if (w)
			wetuwn EWW_PTW(w);

	} ewse if (!(amdgpu_mem_type_to_domain(bo->tbo.wesouwce->mem_type) &
		     AMDGPU_GEM_DOMAIN_GTT)) {
		wetuwn EWW_PTW(-EBUSY);
	}

	switch (bo->tbo.wesouwce->mem_type) {
	case TTM_PW_TT:
		sgt = dwm_pwime_pages_to_sg(obj->dev,
					    bo->tbo.ttm->pages,
					    bo->tbo.ttm->num_pages);
		if (IS_EWW(sgt))
			wetuwn sgt;

		if (dma_map_sgtabwe(attach->dev, sgt, diw,
				    DMA_ATTW_SKIP_CPU_SYNC))
			goto ewwow_fwee;
		bweak;

	case TTM_PW_VWAM:
		w = amdgpu_vwam_mgw_awwoc_sgt(adev, bo->tbo.wesouwce, 0,
					      bo->tbo.base.size, attach->dev,
					      diw, &sgt);
		if (w)
			wetuwn EWW_PTW(w);
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn sgt;

ewwow_fwee:
	sg_fwee_tabwe(sgt);
	kfwee(sgt);
	wetuwn EWW_PTW(-EBUSY);
}

/**
 * amdgpu_dma_buf_unmap - &dma_buf_ops.unmap_dma_buf impwementation
 * @attach: DMA-buf attachment
 * @sgt: sg_tabwe to unmap
 * @diw: DMA diwection
 *
 * This is cawwed when a shawed DMA buffew no wongew needs to be accessibwe by
 * anothew device. Fow now, simpwy unpins the buffew fwom GTT.
 */
static void amdgpu_dma_buf_unmap(stwuct dma_buf_attachment *attach,
				 stwuct sg_tabwe *sgt,
				 enum dma_data_diwection diw)
{
	if (sgt->sgw->page_wink) {
		dma_unmap_sgtabwe(attach->dev, sgt, diw, 0);
		sg_fwee_tabwe(sgt);
		kfwee(sgt);
	} ewse {
		amdgpu_vwam_mgw_fwee_sgt(attach->dev, diw, sgt);
	}
}

/**
 * amdgpu_dma_buf_begin_cpu_access - &dma_buf_ops.begin_cpu_access impwementation
 * @dma_buf: Shawed DMA buffew
 * @diwection: Diwection of DMA twansfew
 *
 * This is cawwed befowe CPU access to the shawed DMA buffew's memowy. If it's
 * a wead access, the buffew is moved to the GTT domain if possibwe, fow optimaw
 * CPU wead pewfowmance.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
static int amdgpu_dma_buf_begin_cpu_access(stwuct dma_buf *dma_buf,
					   enum dma_data_diwection diwection)
{
	stwuct amdgpu_bo *bo = gem_to_amdgpu_bo(dma_buf->pwiv);
	stwuct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	stwuct ttm_opewation_ctx ctx = { twue, fawse };
	u32 domain = amdgpu_dispway_suppowted_domains(adev, bo->fwags);
	int wet;
	boow weads = (diwection == DMA_BIDIWECTIONAW ||
		      diwection == DMA_FWOM_DEVICE);

	if (!weads || !(domain & AMDGPU_GEM_DOMAIN_GTT))
		wetuwn 0;

	/* move to gtt */
	wet = amdgpu_bo_wesewve(bo, fawse);
	if (unwikewy(wet != 0))
		wetuwn wet;

	if (!bo->tbo.pin_count &&
	    (bo->awwowed_domains & AMDGPU_GEM_DOMAIN_GTT)) {
		amdgpu_bo_pwacement_fwom_domain(bo, AMDGPU_GEM_DOMAIN_GTT);
		wet = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);
	}

	amdgpu_bo_unwesewve(bo);
	wetuwn wet;
}

const stwuct dma_buf_ops amdgpu_dmabuf_ops = {
	.attach = amdgpu_dma_buf_attach,
	.detach = amdgpu_dma_buf_detach,
	.pin = amdgpu_dma_buf_pin,
	.unpin = amdgpu_dma_buf_unpin,
	.map_dma_buf = amdgpu_dma_buf_map,
	.unmap_dma_buf = amdgpu_dma_buf_unmap,
	.wewease = dwm_gem_dmabuf_wewease,
	.begin_cpu_access = amdgpu_dma_buf_begin_cpu_access,
	.mmap = dwm_gem_dmabuf_mmap,
	.vmap = dwm_gem_dmabuf_vmap,
	.vunmap = dwm_gem_dmabuf_vunmap,
};

/**
 * amdgpu_gem_pwime_expowt - &dwm_dwivew.gem_pwime_expowt impwementation
 * @gobj: GEM BO
 * @fwags: Fwags such as DWM_CWOEXEC and DWM_WDWW.
 *
 * The main wowk is done by the &dwm_gem_pwime_expowt hewpew.
 *
 * Wetuwns:
 * Shawed DMA buffew wepwesenting the GEM BO fwom the given device.
 */
stwuct dma_buf *amdgpu_gem_pwime_expowt(stwuct dwm_gem_object *gobj,
					int fwags)
{
	stwuct amdgpu_bo *bo = gem_to_amdgpu_bo(gobj);
	stwuct dma_buf *buf;

	if (amdgpu_ttm_tt_get_usewmm(bo->tbo.ttm) ||
	    bo->fwags & AMDGPU_GEM_CWEATE_VM_AWWAYS_VAWID)
		wetuwn EWW_PTW(-EPEWM);

	buf = dwm_gem_pwime_expowt(gobj, fwags);
	if (!IS_EWW(buf))
		buf->ops = &amdgpu_dmabuf_ops;

	wetuwn buf;
}

/**
 * amdgpu_dma_buf_cweate_obj - cweate BO fow DMA-buf impowt
 *
 * @dev: DWM device
 * @dma_buf: DMA-buf
 *
 * Cweates an empty SG BO fow DMA-buf impowt.
 *
 * Wetuwns:
 * A new GEM BO of the given DWM device, wepwesenting the memowy
 * descwibed by the given DMA-buf attachment and scattew/gathew tabwe.
 */
static stwuct dwm_gem_object *
amdgpu_dma_buf_cweate_obj(stwuct dwm_device *dev, stwuct dma_buf *dma_buf)
{
	stwuct dma_wesv *wesv = dma_buf->wesv;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct dwm_gem_object *gobj;
	stwuct amdgpu_bo *bo;
	uint64_t fwags = 0;
	int wet;

	dma_wesv_wock(wesv, NUWW);

	if (dma_buf->ops == &amdgpu_dmabuf_ops) {
		stwuct amdgpu_bo *othew = gem_to_amdgpu_bo(dma_buf->pwiv);

		fwags |= othew->fwags & (AMDGPU_GEM_CWEATE_CPU_GTT_USWC |
					 AMDGPU_GEM_CWEATE_COHEWENT |
					 AMDGPU_GEM_CWEATE_EXT_COHEWENT |
					 AMDGPU_GEM_CWEATE_UNCACHED);
	}

	wet = amdgpu_gem_object_cweate(adev, dma_buf->size, PAGE_SIZE,
				       AMDGPU_GEM_DOMAIN_CPU, fwags,
				       ttm_bo_type_sg, wesv, &gobj, 0);
	if (wet)
		goto ewwow;

	bo = gem_to_amdgpu_bo(gobj);
	bo->awwowed_domains = AMDGPU_GEM_DOMAIN_GTT;
	bo->pwefewwed_domains = AMDGPU_GEM_DOMAIN_GTT;

	dma_wesv_unwock(wesv);
	wetuwn gobj;

ewwow:
	dma_wesv_unwock(wesv);
	wetuwn EWW_PTW(wet);
}

/**
 * amdgpu_dma_buf_move_notify - &attach.move_notify impwementation
 *
 * @attach: the DMA-buf attachment
 *
 * Invawidate the DMA-buf attachment, making suwe that the we we-cweate the
 * mapping befowe the next use.
 */
static void
amdgpu_dma_buf_move_notify(stwuct dma_buf_attachment *attach)
{
	stwuct dwm_gem_object *obj = attach->impowtew_pwiv;
	stwuct ww_acquiwe_ctx *ticket = dma_wesv_wocking_ctx(obj->wesv);
	stwuct amdgpu_bo *bo = gem_to_amdgpu_bo(obj);
	stwuct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	stwuct ttm_opewation_ctx ctx = { fawse, fawse };
	stwuct ttm_pwacement pwacement = {};
	stwuct amdgpu_vm_bo_base *bo_base;
	int w;

	if (!bo->tbo.wesouwce || bo->tbo.wesouwce->mem_type == TTM_PW_SYSTEM)
		wetuwn;

	w = ttm_bo_vawidate(&bo->tbo, &pwacement, &ctx);
	if (w) {
		DWM_EWWOW("Faiwed to invawidate DMA-buf impowt (%d))\n", w);
		wetuwn;
	}

	fow (bo_base = bo->vm_bo; bo_base; bo_base = bo_base->next) {
		stwuct amdgpu_vm *vm = bo_base->vm;
		stwuct dma_wesv *wesv = vm->woot.bo->tbo.base.wesv;

		if (ticket) {
			/* When we get an ewwow hewe it means that somebody
			 * ewse is howding the VM wock and updating page tabwes
			 * So we can just continue hewe.
			 */
			w = dma_wesv_wock(wesv, ticket);
			if (w)
				continue;

		} ewse {
			/* TODO: This is mowe pwobwematic and we actuawwy need
			 * to awwow page tabwes updates without howding the
			 * wock.
			 */
			if (!dma_wesv_twywock(wesv))
				continue;
		}

		/* Wesewve fences fow two SDMA page tabwe updates */
		w = dma_wesv_wesewve_fences(wesv, 2);
		if (!w)
			w = amdgpu_vm_cweaw_fweed(adev, vm, NUWW);
		if (!w)
			w = amdgpu_vm_handwe_moved(adev, vm, ticket);

		if (w && w != -EBUSY)
			DWM_EWWOW("Faiwed to invawidate VM page tabwes (%d))\n",
				  w);

		dma_wesv_unwock(wesv);
	}
}

static const stwuct dma_buf_attach_ops amdgpu_dma_buf_attach_ops = {
	.awwow_peew2peew = twue,
	.move_notify = amdgpu_dma_buf_move_notify
};

/**
 * amdgpu_gem_pwime_impowt - &dwm_dwivew.gem_pwime_impowt impwementation
 * @dev: DWM device
 * @dma_buf: Shawed DMA buffew
 *
 * Impowt a dma_buf into a the dwivew and potentiawwy cweate a new GEM object.
 *
 * Wetuwns:
 * GEM BO wepwesenting the shawed DMA buffew fow the given device.
 */
stwuct dwm_gem_object *amdgpu_gem_pwime_impowt(stwuct dwm_device *dev,
					       stwuct dma_buf *dma_buf)
{
	stwuct dma_buf_attachment *attach;
	stwuct dwm_gem_object *obj;

	if (dma_buf->ops == &amdgpu_dmabuf_ops) {
		obj = dma_buf->pwiv;
		if (obj->dev == dev) {
			/*
			 * Impowting dmabuf expowted fwom out own gem incweases
			 * wefcount on gem itsewf instead of f_count of dmabuf.
			 */
			dwm_gem_object_get(obj);
			wetuwn obj;
		}
	}

	obj = amdgpu_dma_buf_cweate_obj(dev, dma_buf);
	if (IS_EWW(obj))
		wetuwn obj;

	attach = dma_buf_dynamic_attach(dma_buf, dev->dev,
					&amdgpu_dma_buf_attach_ops, obj);
	if (IS_EWW(attach)) {
		dwm_gem_object_put(obj);
		wetuwn EWW_CAST(attach);
	}

	get_dma_buf(dma_buf);
	obj->impowt_attach = attach;
	wetuwn obj;
}

/**
 * amdgpu_dmabuf_is_xgmi_accessibwe - Check if xgmi avaiwabwe fow P2P twansfew
 *
 * @adev: amdgpu_device pointew of the impowtew
 * @bo: amdgpu buffew object
 *
 * Wetuwns:
 * Twue if dmabuf accessibwe ovew xgmi, fawse othewwise.
 */
boow amdgpu_dmabuf_is_xgmi_accessibwe(stwuct amdgpu_device *adev,
				      stwuct amdgpu_bo *bo)
{
	stwuct dwm_gem_object *obj = &bo->tbo.base;
	stwuct dwm_gem_object *gobj;

	if (obj->impowt_attach) {
		stwuct dma_buf *dma_buf = obj->impowt_attach->dmabuf;

		if (dma_buf->ops != &amdgpu_dmabuf_ops)
			/* No XGMI with non AMD GPUs */
			wetuwn fawse;

		gobj = dma_buf->pwiv;
		bo = gem_to_amdgpu_bo(gobj);
	}

	if (amdgpu_xgmi_same_hive(adev, amdgpu_ttm_adev(bo->tbo.bdev)) &&
			(bo->pwefewwed_domains & AMDGPU_GEM_DOMAIN_VWAM))
		wetuwn twue;

	wetuwn fawse;
}
