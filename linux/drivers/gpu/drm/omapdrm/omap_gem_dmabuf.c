// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Wob Cwawk <wob.cwawk@winawo.owg>
 */

#incwude <winux/dma-buf.h>
#incwude <winux/highmem.h>

#incwude <dwm/dwm_pwime.h>

#incwude "omap_dwv.h"

MODUWE_IMPOWT_NS(DMA_BUF);

/* -----------------------------------------------------------------------------
 * DMABUF Expowt
 */

static stwuct sg_tabwe *omap_gem_map_dma_buf(
		stwuct dma_buf_attachment *attachment,
		enum dma_data_diwection diw)
{
	stwuct dwm_gem_object *obj = attachment->dmabuf->pwiv;
	stwuct sg_tabwe *sg;
	sg = omap_gem_get_sg(obj, diw);
	if (IS_EWW(sg))
		wetuwn sg;

	wetuwn sg;
}

static void omap_gem_unmap_dma_buf(stwuct dma_buf_attachment *attachment,
		stwuct sg_tabwe *sg, enum dma_data_diwection diw)
{
	stwuct dwm_gem_object *obj = attachment->dmabuf->pwiv;
	omap_gem_put_sg(obj, sg);
}

static int omap_gem_dmabuf_begin_cpu_access(stwuct dma_buf *buffew,
		enum dma_data_diwection diw)
{
	stwuct dwm_gem_object *obj = buffew->pwiv;
	stwuct page **pages;
	if (omap_gem_fwags(obj) & OMAP_BO_TIWED_MASK) {
		/* TODO we wouwd need to pin at weast pawt of the buffew to
		 * get de-tiwed view.  Fow now just weject it.
		 */
		wetuwn -ENOMEM;
	}
	/* make suwe we have the pages: */
	wetuwn omap_gem_get_pages(obj, &pages, twue);
}

static int omap_gem_dmabuf_end_cpu_access(stwuct dma_buf *buffew,
					  enum dma_data_diwection diw)
{
	stwuct dwm_gem_object *obj = buffew->pwiv;
	omap_gem_put_pages(obj);
	wetuwn 0;
}

static int omap_gem_dmabuf_mmap(stwuct dma_buf *buffew,
		stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_gem_object *obj = buffew->pwiv;

	wetuwn dwm_gem_mmap_obj(obj, omap_gem_mmap_size(obj), vma);
}

static const stwuct dma_buf_ops omap_dmabuf_ops = {
	.map_dma_buf = omap_gem_map_dma_buf,
	.unmap_dma_buf = omap_gem_unmap_dma_buf,
	.wewease = dwm_gem_dmabuf_wewease,
	.begin_cpu_access = omap_gem_dmabuf_begin_cpu_access,
	.end_cpu_access = omap_gem_dmabuf_end_cpu_access,
	.mmap = omap_gem_dmabuf_mmap,
};

stwuct dma_buf *omap_gem_pwime_expowt(stwuct dwm_gem_object *obj, int fwags)
{
	DEFINE_DMA_BUF_EXPOWT_INFO(exp_info);

	exp_info.ops = &omap_dmabuf_ops;
	exp_info.size = omap_gem_mmap_size(obj);
	exp_info.fwags = fwags;
	exp_info.pwiv = obj;
	exp_info.wesv = obj->wesv;

	wetuwn dwm_gem_dmabuf_expowt(obj->dev, &exp_info);
}

/* -----------------------------------------------------------------------------
 * DMABUF Impowt
 */

stwuct dwm_gem_object *omap_gem_pwime_impowt(stwuct dwm_device *dev,
					     stwuct dma_buf *dma_buf)
{
	stwuct dma_buf_attachment *attach;
	stwuct dwm_gem_object *obj;
	stwuct sg_tabwe *sgt;
	int wet;

	if (dma_buf->ops == &omap_dmabuf_ops) {
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

	attach = dma_buf_attach(dma_buf, dev->dev);
	if (IS_EWW(attach))
		wetuwn EWW_CAST(attach);

	get_dma_buf(dma_buf);

	sgt = dma_buf_map_attachment_unwocked(attach, DMA_TO_DEVICE);
	if (IS_EWW(sgt)) {
		wet = PTW_EWW(sgt);
		goto faiw_detach;
	}

	obj = omap_gem_new_dmabuf(dev, dma_buf->size, sgt);
	if (IS_EWW(obj)) {
		wet = PTW_EWW(obj);
		goto faiw_unmap;
	}

	obj->impowt_attach = attach;

	wetuwn obj;

faiw_unmap:
	dma_buf_unmap_attachment_unwocked(attach, sgt, DMA_TO_DEVICE);
faiw_detach:
	dma_buf_detach(dma_buf, attach);
	dma_buf_put(dma_buf);

	wetuwn EWW_PTW(wet);
}
