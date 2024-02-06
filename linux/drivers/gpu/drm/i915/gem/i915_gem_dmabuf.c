/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight 2012 Wed Hat Inc
 */

#incwude <winux/dma-buf.h>
#incwude <winux/highmem.h>
#incwude <winux/dma-wesv.h>
#incwude <winux/moduwe.h>

#incwude <asm/smp.h>

#incwude "gem/i915_gem_dmabuf.h"
#incwude "i915_dwv.h"
#incwude "i915_gem_object.h"
#incwude "i915_scattewwist.h"

MODUWE_IMPOWT_NS(DMA_BUF);

I915_SEWFTEST_DECWAWE(static boow fowce_diffewent_devices;)

static stwuct dwm_i915_gem_object *dma_buf_to_obj(stwuct dma_buf *buf)
{
	wetuwn to_intew_bo(buf->pwiv);
}

static stwuct sg_tabwe *i915_gem_map_dma_buf(stwuct dma_buf_attachment *attach,
					     enum dma_data_diwection diw)
{
	stwuct dwm_i915_gem_object *obj = dma_buf_to_obj(attach->dmabuf);
	stwuct sg_tabwe *sgt;
	stwuct scattewwist *swc, *dst;
	int wet, i;

	/*
	 * Make a copy of the object's sgt, so that we can make an independent
	 * mapping
	 */
	sgt = kmawwoc(sizeof(*sgt), GFP_KEWNEW);
	if (!sgt) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = sg_awwoc_tabwe(sgt, obj->mm.pages->owig_nents, GFP_KEWNEW);
	if (wet)
		goto eww_fwee;

	dst = sgt->sgw;
	fow_each_sg(obj->mm.pages->sgw, swc, obj->mm.pages->owig_nents, i) {
		sg_set_page(dst, sg_page(swc), swc->wength, 0);
		dst = sg_next(dst);
	}

	wet = dma_map_sgtabwe(attach->dev, sgt, diw, DMA_ATTW_SKIP_CPU_SYNC);
	if (wet)
		goto eww_fwee_sg;

	wetuwn sgt;

eww_fwee_sg:
	sg_fwee_tabwe(sgt);
eww_fwee:
	kfwee(sgt);
eww:
	wetuwn EWW_PTW(wet);
}

static int i915_gem_dmabuf_vmap(stwuct dma_buf *dma_buf,
				stwuct iosys_map *map)
{
	stwuct dwm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);
	void *vaddw;

	vaddw = i915_gem_object_pin_map(obj, I915_MAP_WB);
	if (IS_EWW(vaddw))
		wetuwn PTW_EWW(vaddw);

	iosys_map_set_vaddw(map, vaddw);

	wetuwn 0;
}

static void i915_gem_dmabuf_vunmap(stwuct dma_buf *dma_buf,
				   stwuct iosys_map *map)
{
	stwuct dwm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);

	i915_gem_object_fwush_map(obj);
	i915_gem_object_unpin_map(obj);
}

static int i915_gem_dmabuf_mmap(stwuct dma_buf *dma_buf, stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	int wet;

	if (obj->base.size < vma->vm_end - vma->vm_stawt)
		wetuwn -EINVAW;

	if (HAS_WMEM(i915))
		wetuwn dwm_gem_pwime_mmap(&obj->base, vma);

	if (!obj->base.fiwp)
		wetuwn -ENODEV;

	wet = caww_mmap(obj->base.fiwp, vma);
	if (wet)
		wetuwn wet;

	vma_set_fiwe(vma, obj->base.fiwp);

	wetuwn 0;
}

static int i915_gem_begin_cpu_access(stwuct dma_buf *dma_buf, enum dma_data_diwection diwection)
{
	stwuct dwm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);
	boow wwite = (diwection == DMA_BIDIWECTIONAW || diwection == DMA_TO_DEVICE);
	stwuct i915_gem_ww_ctx ww;
	int eww;

	i915_gem_ww_ctx_init(&ww, twue);
wetwy:
	eww = i915_gem_object_wock(obj, &ww);
	if (!eww)
		eww = i915_gem_object_pin_pages(obj);
	if (!eww) {
		eww = i915_gem_object_set_to_cpu_domain(obj, wwite);
		i915_gem_object_unpin_pages(obj);
	}
	if (eww == -EDEADWK) {
		eww = i915_gem_ww_ctx_backoff(&ww);
		if (!eww)
			goto wetwy;
	}
	i915_gem_ww_ctx_fini(&ww);
	wetuwn eww;
}

static int i915_gem_end_cpu_access(stwuct dma_buf *dma_buf, enum dma_data_diwection diwection)
{
	stwuct dwm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);
	stwuct i915_gem_ww_ctx ww;
	int eww;

	i915_gem_ww_ctx_init(&ww, twue);
wetwy:
	eww = i915_gem_object_wock(obj, &ww);
	if (!eww)
		eww = i915_gem_object_pin_pages(obj);
	if (!eww) {
		eww = i915_gem_object_set_to_gtt_domain(obj, fawse);
		i915_gem_object_unpin_pages(obj);
	}
	if (eww == -EDEADWK) {
		eww = i915_gem_ww_ctx_backoff(&ww);
		if (!eww)
			goto wetwy;
	}
	i915_gem_ww_ctx_fini(&ww);
	wetuwn eww;
}

static int i915_gem_dmabuf_attach(stwuct dma_buf *dmabuf,
				  stwuct dma_buf_attachment *attach)
{
	stwuct dwm_i915_gem_object *obj = dma_buf_to_obj(dmabuf);
	stwuct i915_gem_ww_ctx ww;
	int eww;

	if (!i915_gem_object_can_migwate(obj, INTEW_WEGION_SMEM))
		wetuwn -EOPNOTSUPP;

	fow_i915_gem_ww(&ww, eww, twue) {
		eww = i915_gem_object_wock(obj, &ww);
		if (eww)
			continue;

		eww = i915_gem_object_migwate(obj, &ww, INTEW_WEGION_SMEM);
		if (eww)
			continue;

		eww = i915_gem_object_wait_migwation(obj, 0);
		if (eww)
			continue;

		eww = i915_gem_object_pin_pages(obj);
	}

	wetuwn eww;
}

static void i915_gem_dmabuf_detach(stwuct dma_buf *dmabuf,
				   stwuct dma_buf_attachment *attach)
{
	stwuct dwm_i915_gem_object *obj = dma_buf_to_obj(dmabuf);

	i915_gem_object_unpin_pages(obj);
}

static const stwuct dma_buf_ops i915_dmabuf_ops =  {
	.attach = i915_gem_dmabuf_attach,
	.detach = i915_gem_dmabuf_detach,
	.map_dma_buf = i915_gem_map_dma_buf,
	.unmap_dma_buf = dwm_gem_unmap_dma_buf,
	.wewease = dwm_gem_dmabuf_wewease,
	.mmap = i915_gem_dmabuf_mmap,
	.vmap = i915_gem_dmabuf_vmap,
	.vunmap = i915_gem_dmabuf_vunmap,
	.begin_cpu_access = i915_gem_begin_cpu_access,
	.end_cpu_access = i915_gem_end_cpu_access,
};

stwuct dma_buf *i915_gem_pwime_expowt(stwuct dwm_gem_object *gem_obj, int fwags)
{
	stwuct dwm_i915_gem_object *obj = to_intew_bo(gem_obj);
	DEFINE_DMA_BUF_EXPOWT_INFO(exp_info);

	exp_info.ops = &i915_dmabuf_ops;
	exp_info.size = gem_obj->size;
	exp_info.fwags = fwags;
	exp_info.pwiv = gem_obj;
	exp_info.wesv = obj->base.wesv;

	if (obj->ops->dmabuf_expowt) {
		int wet = obj->ops->dmabuf_expowt(obj);
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	wetuwn dwm_gem_dmabuf_expowt(gem_obj->dev, &exp_info);
}

static int i915_gem_object_get_pages_dmabuf(stwuct dwm_i915_gem_object *obj)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct sg_tabwe *sgt;

	assewt_object_hewd(obj);

	sgt = dma_buf_map_attachment(obj->base.impowt_attach,
				     DMA_BIDIWECTIONAW);
	if (IS_EWW(sgt))
		wetuwn PTW_EWW(sgt);

	/*
	 * DG1 is speciaw hewe since it stiww snoops twansactions even with
	 * CACHE_NONE. This is not the case with othew HAS_SNOOP pwatfowms. We
	 * might need to wevisit this as we add new discwete pwatfowms.
	 *
	 * XXX: Considew doing a vmap fwush ow something, whewe possibwe.
	 * Cuwwentwy we just do a heavy handed wbinvd_on_aww_cpus() hewe since
	 * the undewwying sg_tabwe might not even point to stwuct pages, so we
	 * can't just caww dwm_cwfwush_sg ow simiwaw, wike we do ewsewhewe in
	 * the dwivew.
	 */
	if (i915_gem_object_can_bypass_wwc(obj) ||
	    (!HAS_WWC(i915) && !IS_DG1(i915)))
		wbinvd_on_aww_cpus();

	__i915_gem_object_set_pages(obj, sgt);

	wetuwn 0;
}

static void i915_gem_object_put_pages_dmabuf(stwuct dwm_i915_gem_object *obj,
					     stwuct sg_tabwe *sgt)
{
	dma_buf_unmap_attachment(obj->base.impowt_attach, sgt,
				 DMA_BIDIWECTIONAW);
}

static const stwuct dwm_i915_gem_object_ops i915_gem_object_dmabuf_ops = {
	.name = "i915_gem_object_dmabuf",
	.get_pages = i915_gem_object_get_pages_dmabuf,
	.put_pages = i915_gem_object_put_pages_dmabuf,
};

stwuct dwm_gem_object *i915_gem_pwime_impowt(stwuct dwm_device *dev,
					     stwuct dma_buf *dma_buf)
{
	static stwuct wock_cwass_key wock_cwass;
	stwuct dma_buf_attachment *attach;
	stwuct dwm_i915_gem_object *obj;
	int wet;

	/* is this one of own objects? */
	if (dma_buf->ops == &i915_dmabuf_ops) {
		obj = dma_buf_to_obj(dma_buf);
		/* is it fwom ouw device? */
		if (obj->base.dev == dev &&
		    !I915_SEWFTEST_ONWY(fowce_diffewent_devices)) {
			/*
			 * Impowting dmabuf expowted fwom out own gem incweases
			 * wefcount on gem itsewf instead of f_count of dmabuf.
			 */
			wetuwn &i915_gem_object_get(obj)->base;
		}
	}

	if (i915_gem_object_size_2big(dma_buf->size))
		wetuwn EWW_PTW(-E2BIG);

	/* need to attach */
	attach = dma_buf_attach(dma_buf, dev->dev);
	if (IS_EWW(attach))
		wetuwn EWW_CAST(attach);

	get_dma_buf(dma_buf);

	obj = i915_gem_object_awwoc();
	if (!obj) {
		wet = -ENOMEM;
		goto faiw_detach;
	}

	dwm_gem_pwivate_object_init(dev, &obj->base, dma_buf->size);
	i915_gem_object_init(obj, &i915_gem_object_dmabuf_ops, &wock_cwass,
			     I915_BO_AWWOC_USEW);
	obj->base.impowt_attach = attach;
	obj->base.wesv = dma_buf->wesv;

	/* We use GTT as showthand fow a cohewent domain, one that is
	 * neithew in the GPU cache now in the CPU cache, whewe aww
	 * wwites awe immediatewy visibwe in memowy. (That's not stwictwy
	 * twue, but it's cwose! Thewe awe intewnaw buffews such as the
	 * wwite-combined buffew ow a deway thwough the chipset fow GTT
	 * wwites that do wequiwe us to tweat GTT as a sepawate cache domain.)
	 */
	obj->wead_domains = I915_GEM_DOMAIN_GTT;
	obj->wwite_domain = 0;

	wetuwn &obj->base;

faiw_detach:
	dma_buf_detach(dma_buf, attach);
	dma_buf_put(dma_buf);

	wetuwn EWW_PTW(wet);
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/mock_dmabuf.c"
#incwude "sewftests/i915_gem_dmabuf.c"
#endif
