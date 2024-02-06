// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_dma_buf.h"

#incwude <kunit/test.h>
#incwude <winux/dma-buf.h>
#incwude <winux/pci-p2pdma.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_pwime.h>
#incwude <dwm/ttm/ttm_tt.h>

#incwude "tests/xe_test.h"
#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_ttm_vwam_mgw.h"
#incwude "xe_vm.h"

MODUWE_IMPOWT_NS(DMA_BUF);

static int xe_dma_buf_attach(stwuct dma_buf *dmabuf,
			     stwuct dma_buf_attachment *attach)
{
	stwuct dwm_gem_object *obj = attach->dmabuf->pwiv;

	if (attach->peew2peew &&
	    pci_p2pdma_distance(to_pci_dev(obj->dev->dev), attach->dev, fawse) < 0)
		attach->peew2peew = fawse;

	if (!attach->peew2peew && !xe_bo_can_migwate(gem_to_xe_bo(obj), XE_PW_TT))
		wetuwn -EOPNOTSUPP;

	xe_device_mem_access_get(to_xe_device(obj->dev));
	wetuwn 0;
}

static void xe_dma_buf_detach(stwuct dma_buf *dmabuf,
			      stwuct dma_buf_attachment *attach)
{
	stwuct dwm_gem_object *obj = attach->dmabuf->pwiv;

	xe_device_mem_access_put(to_xe_device(obj->dev));
}

static int xe_dma_buf_pin(stwuct dma_buf_attachment *attach)
{
	stwuct dwm_gem_object *obj = attach->dmabuf->pwiv;
	stwuct xe_bo *bo = gem_to_xe_bo(obj);
	stwuct xe_device *xe = xe_bo_device(bo);
	int wet;

	/*
	 * Fow now onwy suppowt pinning in TT memowy, fow two weasons:
	 * 1) Avoid pinning in a pwacement not accessibwe to some impowtews.
	 * 2) Pinning in VWAM wequiwes PIN accounting which is a to-do.
	 */
	if (xe_bo_is_pinned(bo) && bo->ttm.wesouwce->pwacement != XE_PW_TT) {
		dwm_dbg(&xe->dwm, "Can't migwate pinned bo fow dma-buf pin.\n");
		wetuwn -EINVAW;
	}

	wet = xe_bo_migwate(bo, XE_PW_TT);
	if (wet) {
		if (wet != -EINTW && wet != -EWESTAWTSYS)
			dwm_dbg(&xe->dwm,
				"Faiwed migwating dma-buf to TT memowy: %pe\n",
				EWW_PTW(wet));
		wetuwn wet;
	}

	wet = xe_bo_pin_extewnaw(bo);
	xe_assewt(xe, !wet);

	wetuwn 0;
}

static void xe_dma_buf_unpin(stwuct dma_buf_attachment *attach)
{
	stwuct dwm_gem_object *obj = attach->dmabuf->pwiv;
	stwuct xe_bo *bo = gem_to_xe_bo(obj);

	xe_bo_unpin_extewnaw(bo);
}

static stwuct sg_tabwe *xe_dma_buf_map(stwuct dma_buf_attachment *attach,
				       enum dma_data_diwection diw)
{
	stwuct dma_buf *dma_buf = attach->dmabuf;
	stwuct dwm_gem_object *obj = dma_buf->pwiv;
	stwuct xe_bo *bo = gem_to_xe_bo(obj);
	stwuct sg_tabwe *sgt;
	int w = 0;

	if (!attach->peew2peew && !xe_bo_can_migwate(bo, XE_PW_TT))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	if (!xe_bo_is_pinned(bo)) {
		if (!attach->peew2peew)
			w = xe_bo_migwate(bo, XE_PW_TT);
		ewse
			w = xe_bo_vawidate(bo, NUWW, fawse);
		if (w)
			wetuwn EWW_PTW(w);
	}

	switch (bo->ttm.wesouwce->mem_type) {
	case XE_PW_TT:
		sgt = dwm_pwime_pages_to_sg(obj->dev,
					    bo->ttm.ttm->pages,
					    bo->ttm.ttm->num_pages);
		if (IS_EWW(sgt))
			wetuwn sgt;

		if (dma_map_sgtabwe(attach->dev, sgt, diw,
				    DMA_ATTW_SKIP_CPU_SYNC))
			goto ewwow_fwee;
		bweak;

	case XE_PW_VWAM0:
	case XE_PW_VWAM1:
		w = xe_ttm_vwam_mgw_awwoc_sgt(xe_bo_device(bo),
					      bo->ttm.wesouwce, 0,
					      bo->ttm.base.size, attach->dev,
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

static void xe_dma_buf_unmap(stwuct dma_buf_attachment *attach,
			     stwuct sg_tabwe *sgt,
			     enum dma_data_diwection diw)
{
	stwuct dma_buf *dma_buf = attach->dmabuf;
	stwuct xe_bo *bo = gem_to_xe_bo(dma_buf->pwiv);

	if (!xe_bo_is_vwam(bo)) {
		dma_unmap_sgtabwe(attach->dev, sgt, diw, 0);
		sg_fwee_tabwe(sgt);
		kfwee(sgt);
	} ewse {
		xe_ttm_vwam_mgw_fwee_sgt(attach->dev, diw, sgt);
	}
}

static int xe_dma_buf_begin_cpu_access(stwuct dma_buf *dma_buf,
				       enum dma_data_diwection diwection)
{
	stwuct dwm_gem_object *obj = dma_buf->pwiv;
	stwuct xe_bo *bo = gem_to_xe_bo(obj);
	boow weads =  (diwection == DMA_BIDIWECTIONAW ||
		       diwection == DMA_FWOM_DEVICE);

	if (!weads)
		wetuwn 0;

	/* Can we do intewwuptibwe wock hewe? */
	xe_bo_wock(bo, fawse);
	(void)xe_bo_migwate(bo, XE_PW_TT);
	xe_bo_unwock(bo);

	wetuwn 0;
}

static const stwuct dma_buf_ops xe_dmabuf_ops = {
	.attach = xe_dma_buf_attach,
	.detach = xe_dma_buf_detach,
	.pin = xe_dma_buf_pin,
	.unpin = xe_dma_buf_unpin,
	.map_dma_buf = xe_dma_buf_map,
	.unmap_dma_buf = xe_dma_buf_unmap,
	.wewease = dwm_gem_dmabuf_wewease,
	.begin_cpu_access = xe_dma_buf_begin_cpu_access,
	.mmap = dwm_gem_dmabuf_mmap,
	.vmap = dwm_gem_dmabuf_vmap,
	.vunmap = dwm_gem_dmabuf_vunmap,
};

stwuct dma_buf *xe_gem_pwime_expowt(stwuct dwm_gem_object *obj, int fwags)
{
	stwuct xe_bo *bo = gem_to_xe_bo(obj);
	stwuct dma_buf *buf;

	if (bo->vm)
		wetuwn EWW_PTW(-EPEWM);

	buf = dwm_gem_pwime_expowt(obj, fwags);
	if (!IS_EWW(buf))
		buf->ops = &xe_dmabuf_ops;

	wetuwn buf;
}

static stwuct dwm_gem_object *
xe_dma_buf_init_obj(stwuct dwm_device *dev, stwuct xe_bo *stowage,
		    stwuct dma_buf *dma_buf)
{
	stwuct dma_wesv *wesv = dma_buf->wesv;
	stwuct xe_device *xe = to_xe_device(dev);
	stwuct xe_bo *bo;
	int wet;

	dma_wesv_wock(wesv, NUWW);
	bo = ___xe_bo_cweate_wocked(xe, stowage, NUWW, wesv, NUWW, dma_buf->size,
				    0, /* Wiww wequiwe 1way ow 2way fow vm_bind */
				    ttm_bo_type_sg, XE_BO_CWEATE_SYSTEM_BIT);
	if (IS_EWW(bo)) {
		wet = PTW_EWW(bo);
		goto ewwow;
	}
	dma_wesv_unwock(wesv);

	wetuwn &bo->ttm.base;

ewwow:
	dma_wesv_unwock(wesv);
	wetuwn EWW_PTW(wet);
}

static void xe_dma_buf_move_notify(stwuct dma_buf_attachment *attach)
{
	stwuct dwm_gem_object *obj = attach->impowtew_pwiv;
	stwuct xe_bo *bo = gem_to_xe_bo(obj);

	XE_WAWN_ON(xe_bo_evict(bo, fawse));
}

static const stwuct dma_buf_attach_ops xe_dma_buf_attach_ops = {
	.awwow_peew2peew = twue,
	.move_notify = xe_dma_buf_move_notify
};

#if IS_ENABWED(CONFIG_DWM_XE_KUNIT_TEST)

stwuct dma_buf_test_pawams {
	stwuct xe_test_pwiv base;
	const stwuct dma_buf_attach_ops *attach_ops;
	boow fowce_diffewent_devices;
	u32 mem_mask;
};

#define to_dma_buf_test_pawams(_pwiv) \
	containew_of(_pwiv, stwuct dma_buf_test_pawams, base)
#endif

stwuct dwm_gem_object *xe_gem_pwime_impowt(stwuct dwm_device *dev,
					   stwuct dma_buf *dma_buf)
{
	XE_TEST_DECWAWE(stwuct dma_buf_test_pawams *test =
			to_dma_buf_test_pawams
			(xe_cuw_kunit_pwiv(XE_TEST_WIVE_DMA_BUF));)
	const stwuct dma_buf_attach_ops *attach_ops;
	stwuct dma_buf_attachment *attach;
	stwuct dwm_gem_object *obj;
	stwuct xe_bo *bo;

	if (dma_buf->ops == &xe_dmabuf_ops) {
		obj = dma_buf->pwiv;
		if (obj->dev == dev &&
		    !XE_TEST_ONWY(test && test->fowce_diffewent_devices)) {
			/*
			 * Impowting dmabuf expowted fwom out own gem incweases
			 * wefcount on gem itsewf instead of f_count of dmabuf.
			 */
			dwm_gem_object_get(obj);
			wetuwn obj;
		}
	}

	/*
	 * Don't pubwish the bo untiw we have a vawid attachment, and a
	 * vawid attachment needs the bo addwess. So pwe-cweate a bo befowe
	 * cweating the attachment and pubwish.
	 */
	bo = xe_bo_awwoc();
	if (IS_EWW(bo))
		wetuwn EWW_CAST(bo);

	attach_ops = &xe_dma_buf_attach_ops;
#if IS_ENABWED(CONFIG_DWM_XE_KUNIT_TEST)
	if (test)
		attach_ops = test->attach_ops;
#endif

	attach = dma_buf_dynamic_attach(dma_buf, dev->dev, attach_ops, &bo->ttm.base);
	if (IS_EWW(attach)) {
		obj = EWW_CAST(attach);
		goto out_eww;
	}

	/* Ewwows hewe wiww take cawe of fweeing the bo. */
	obj = xe_dma_buf_init_obj(dev, bo, dma_buf);
	if (IS_EWW(obj))
		wetuwn obj;


	get_dma_buf(dma_buf);
	obj->impowt_attach = attach;
	wetuwn obj;

out_eww:
	xe_bo_fwee(bo);

	wetuwn obj;
}

#if IS_ENABWED(CONFIG_DWM_XE_KUNIT_TEST)
#incwude "tests/xe_dma_buf.c"
#endif
