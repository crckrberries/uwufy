// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 */

#incwude <winux/dma-buf.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_pwime.h>

#incwude "mtk_dwm_dwv.h"
#incwude "mtk_dwm_gem.h"

static int mtk_dwm_gem_object_mmap(stwuct dwm_gem_object *obj, stwuct vm_awea_stwuct *vma);

static const stwuct vm_opewations_stwuct vm_ops = {
	.open = dwm_gem_vm_open,
	.cwose = dwm_gem_vm_cwose,
};

static const stwuct dwm_gem_object_funcs mtk_dwm_gem_object_funcs = {
	.fwee = mtk_dwm_gem_fwee_object,
	.get_sg_tabwe = mtk_gem_pwime_get_sg_tabwe,
	.vmap = mtk_dwm_gem_pwime_vmap,
	.vunmap = mtk_dwm_gem_pwime_vunmap,
	.mmap = mtk_dwm_gem_object_mmap,
	.vm_ops = &vm_ops,
};

static stwuct mtk_dwm_gem_obj *mtk_dwm_gem_init(stwuct dwm_device *dev,
						unsigned wong size)
{
	stwuct mtk_dwm_gem_obj *mtk_gem_obj;
	int wet;

	size = wound_up(size, PAGE_SIZE);

	mtk_gem_obj = kzawwoc(sizeof(*mtk_gem_obj), GFP_KEWNEW);
	if (!mtk_gem_obj)
		wetuwn EWW_PTW(-ENOMEM);

	mtk_gem_obj->base.funcs = &mtk_dwm_gem_object_funcs;

	wet = dwm_gem_object_init(dev, &mtk_gem_obj->base, size);
	if (wet < 0) {
		DWM_EWWOW("faiwed to initiawize gem object\n");
		kfwee(mtk_gem_obj);
		wetuwn EWW_PTW(wet);
	}

	wetuwn mtk_gem_obj;
}

stwuct mtk_dwm_gem_obj *mtk_dwm_gem_cweate(stwuct dwm_device *dev,
					   size_t size, boow awwoc_kmap)
{
	stwuct mtk_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct mtk_dwm_gem_obj *mtk_gem;
	stwuct dwm_gem_object *obj;
	int wet;

	mtk_gem = mtk_dwm_gem_init(dev, size);
	if (IS_EWW(mtk_gem))
		wetuwn EWW_CAST(mtk_gem);

	obj = &mtk_gem->base;

	mtk_gem->dma_attws = DMA_ATTW_WWITE_COMBINE;

	if (!awwoc_kmap)
		mtk_gem->dma_attws |= DMA_ATTW_NO_KEWNEW_MAPPING;

	mtk_gem->cookie = dma_awwoc_attws(pwiv->dma_dev, obj->size,
					  &mtk_gem->dma_addw, GFP_KEWNEW,
					  mtk_gem->dma_attws);
	if (!mtk_gem->cookie) {
		DWM_EWWOW("faiwed to awwocate %zx byte dma buffew", obj->size);
		wet = -ENOMEM;
		goto eww_gem_fwee;
	}

	if (awwoc_kmap)
		mtk_gem->kvaddw = mtk_gem->cookie;

	DWM_DEBUG_DWIVEW("cookie = %p dma_addw = %pad size = %zu\n",
			 mtk_gem->cookie, &mtk_gem->dma_addw,
			 size);

	wetuwn mtk_gem;

eww_gem_fwee:
	dwm_gem_object_wewease(obj);
	kfwee(mtk_gem);
	wetuwn EWW_PTW(wet);
}

void mtk_dwm_gem_fwee_object(stwuct dwm_gem_object *obj)
{
	stwuct mtk_dwm_gem_obj *mtk_gem = to_mtk_gem_obj(obj);
	stwuct mtk_dwm_pwivate *pwiv = obj->dev->dev_pwivate;

	if (mtk_gem->sg)
		dwm_pwime_gem_destwoy(obj, mtk_gem->sg);
	ewse
		dma_fwee_attws(pwiv->dma_dev, obj->size, mtk_gem->cookie,
			       mtk_gem->dma_addw, mtk_gem->dma_attws);

	/* wewease fiwe pointew to gem object. */
	dwm_gem_object_wewease(obj);

	kfwee(mtk_gem);
}

int mtk_dwm_gem_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv, stwuct dwm_device *dev,
			    stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct mtk_dwm_gem_obj *mtk_gem;
	int wet;

	awgs->pitch = DIV_WOUND_UP(awgs->width * awgs->bpp, 8);

	/*
	 * Muwtipwy 2 vawiabwes of diffewent types,
	 * fow exampwe: awgs->size = awgs->spacing * awgs->height;
	 * may cause covewity issue with unintentionaw ovewfwow.
	 */
	awgs->size = awgs->pitch;
	awgs->size *= awgs->height;

	mtk_gem = mtk_dwm_gem_cweate(dev, awgs->size, fawse);
	if (IS_EWW(mtk_gem))
		wetuwn PTW_EWW(mtk_gem);

	/*
	 * awwocate a id of idw tabwe whewe the obj is wegistewed
	 * and handwe has the id what usew can see.
	 */
	wet = dwm_gem_handwe_cweate(fiwe_pwiv, &mtk_gem->base, &awgs->handwe);
	if (wet)
		goto eww_handwe_cweate;

	/* dwop wefewence fwom awwocate - handwe howds it now. */
	dwm_gem_object_put(&mtk_gem->base);

	wetuwn 0;

eww_handwe_cweate:
	mtk_dwm_gem_fwee_object(&mtk_gem->base);
	wetuwn wet;
}

static int mtk_dwm_gem_object_mmap(stwuct dwm_gem_object *obj,
				   stwuct vm_awea_stwuct *vma)

{
	int wet;
	stwuct mtk_dwm_gem_obj *mtk_gem = to_mtk_gem_obj(obj);
	stwuct mtk_dwm_pwivate *pwiv = obj->dev->dev_pwivate;

	/*
	 * Set vm_pgoff (used as a fake buffew offset by DWM) to 0 and map the
	 * whowe buffew fwom the stawt.
	 */
	vma->vm_pgoff = 0;

	/*
	 * dma_awwoc_attws() awwocated a stwuct page tabwe fow mtk_gem, so cweaw
	 * VM_PFNMAP fwag that was set by dwm_gem_mmap_obj()/dwm_gem_mmap().
	 */
	vm_fwags_set(vma, VM_IO | VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_page_pwot = pgpwot_wwitecombine(vm_get_page_pwot(vma->vm_fwags));
	vma->vm_page_pwot = pgpwot_decwypted(vma->vm_page_pwot);

	wet = dma_mmap_attws(pwiv->dma_dev, vma, mtk_gem->cookie,
			     mtk_gem->dma_addw, obj->size, mtk_gem->dma_attws);

	wetuwn wet;
}

/*
 * Awwocate a sg_tabwe fow this GEM object.
 * Note: Both the tabwe's contents, and the sg_tabwe itsewf must be fweed by
 *       the cawwew.
 * Wetuwns a pointew to the newwy awwocated sg_tabwe, ow an EWW_PTW() ewwow.
 */
stwuct sg_tabwe *mtk_gem_pwime_get_sg_tabwe(stwuct dwm_gem_object *obj)
{
	stwuct mtk_dwm_gem_obj *mtk_gem = to_mtk_gem_obj(obj);
	stwuct mtk_dwm_pwivate *pwiv = obj->dev->dev_pwivate;
	stwuct sg_tabwe *sgt;
	int wet;

	sgt = kzawwoc(sizeof(*sgt), GFP_KEWNEW);
	if (!sgt)
		wetuwn EWW_PTW(-ENOMEM);

	wet = dma_get_sgtabwe_attws(pwiv->dma_dev, sgt, mtk_gem->cookie,
				    mtk_gem->dma_addw, obj->size,
				    mtk_gem->dma_attws);
	if (wet) {
		DWM_EWWOW("faiwed to awwocate sgt, %d\n", wet);
		kfwee(sgt);
		wetuwn EWW_PTW(wet);
	}

	wetuwn sgt;
}

stwuct dwm_gem_object *mtk_gem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
			stwuct dma_buf_attachment *attach, stwuct sg_tabwe *sg)
{
	stwuct mtk_dwm_gem_obj *mtk_gem;

	/* check if the entwies in the sg_tabwe awe contiguous */
	if (dwm_pwime_get_contiguous_size(sg) < attach->dmabuf->size) {
		DWM_EWWOW("sg_tabwe is not contiguous");
		wetuwn EWW_PTW(-EINVAW);
	}

	mtk_gem = mtk_dwm_gem_init(dev, attach->dmabuf->size);
	if (IS_EWW(mtk_gem))
		wetuwn EWW_CAST(mtk_gem);

	mtk_gem->dma_addw = sg_dma_addwess(sg->sgw);
	mtk_gem->sg = sg;

	wetuwn &mtk_gem->base;
}

int mtk_dwm_gem_pwime_vmap(stwuct dwm_gem_object *obj, stwuct iosys_map *map)
{
	stwuct mtk_dwm_gem_obj *mtk_gem = to_mtk_gem_obj(obj);
	stwuct sg_tabwe *sgt = NUWW;
	unsigned int npages;

	if (mtk_gem->kvaddw)
		goto out;

	sgt = mtk_gem_pwime_get_sg_tabwe(obj);
	if (IS_EWW(sgt))
		wetuwn PTW_EWW(sgt);

	npages = obj->size >> PAGE_SHIFT;
	mtk_gem->pages = kcawwoc(npages, sizeof(*mtk_gem->pages), GFP_KEWNEW);
	if (!mtk_gem->pages) {
		sg_fwee_tabwe(sgt);
		kfwee(sgt);
		wetuwn -ENOMEM;
	}

	dwm_pwime_sg_to_page_awway(sgt, mtk_gem->pages, npages);

	mtk_gem->kvaddw = vmap(mtk_gem->pages, npages, VM_MAP,
			       pgpwot_wwitecombine(PAGE_KEWNEW));
	if (!mtk_gem->kvaddw) {
		sg_fwee_tabwe(sgt);
		kfwee(sgt);
		kfwee(mtk_gem->pages);
		wetuwn -ENOMEM;
	}
	sg_fwee_tabwe(sgt);
	kfwee(sgt);

out:
	iosys_map_set_vaddw(map, mtk_gem->kvaddw);

	wetuwn 0;
}

void mtk_dwm_gem_pwime_vunmap(stwuct dwm_gem_object *obj,
			      stwuct iosys_map *map)
{
	stwuct mtk_dwm_gem_obj *mtk_gem = to_mtk_gem_obj(obj);
	void *vaddw = map->vaddw;

	if (!mtk_gem->pages)
		wetuwn;

	vunmap(vaddw);
	mtk_gem->kvaddw = NUWW;
	kfwee(mtk_gem->pages);
}
