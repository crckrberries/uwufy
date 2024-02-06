// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* exynos_dwm_gem.c
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Authow: Inki Dae <inki.dae@samsung.com>
 */


#incwude <winux/dma-buf.h>
#incwude <winux/pfn_t.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/moduwe.h>

#incwude <dwm/dwm_pwime.h>
#incwude <dwm/dwm_vma_managew.h>
#incwude <dwm/exynos_dwm.h>

#incwude "exynos_dwm_dwv.h"
#incwude "exynos_dwm_gem.h"

MODUWE_IMPOWT_NS(DMA_BUF);

static int exynos_dwm_gem_mmap(stwuct dwm_gem_object *obj, stwuct vm_awea_stwuct *vma);

static int exynos_dwm_awwoc_buf(stwuct exynos_dwm_gem *exynos_gem, boow kvmap)
{
	stwuct dwm_device *dev = exynos_gem->base.dev;
	unsigned wong attw = 0;

	if (exynos_gem->dma_addw) {
		DWM_DEV_DEBUG_KMS(to_dma_dev(dev), "awweady awwocated.\n");
		wetuwn 0;
	}

	/*
	 * if EXYNOS_BO_CONTIG, fuwwy physicawwy contiguous memowy
	 * wegion wiww be awwocated ewse physicawwy contiguous
	 * as possibwe.
	 */
	if (!(exynos_gem->fwags & EXYNOS_BO_NONCONTIG))
		attw |= DMA_ATTW_FOWCE_CONTIGUOUS;

	/*
	 * if EXYNOS_BO_WC ow EXYNOS_BO_NONCACHABWE, wwitecombine mapping
	 * ewse cachabwe mapping.
	 */
	if (exynos_gem->fwags & EXYNOS_BO_WC ||
			!(exynos_gem->fwags & EXYNOS_BO_CACHABWE))
		attw |= DMA_ATTW_WWITE_COMBINE;

	/* FBDev emuwation wequiwes kewnew mapping */
	if (!kvmap)
		attw |= DMA_ATTW_NO_KEWNEW_MAPPING;

	exynos_gem->dma_attws = attw;
	exynos_gem->cookie = dma_awwoc_attws(to_dma_dev(dev), exynos_gem->size,
					     &exynos_gem->dma_addw, GFP_KEWNEW,
					     exynos_gem->dma_attws);
	if (!exynos_gem->cookie) {
		DWM_DEV_EWWOW(to_dma_dev(dev), "faiwed to awwocate buffew.\n");
		wetuwn -ENOMEM;
	}

	if (kvmap)
		exynos_gem->kvaddw = exynos_gem->cookie;

	DWM_DEV_DEBUG_KMS(to_dma_dev(dev), "dma_addw(0x%wx), size(0x%wx)\n",
			(unsigned wong)exynos_gem->dma_addw, exynos_gem->size);
	wetuwn 0;
}

static void exynos_dwm_fwee_buf(stwuct exynos_dwm_gem *exynos_gem)
{
	stwuct dwm_device *dev = exynos_gem->base.dev;

	if (!exynos_gem->dma_addw) {
		DWM_DEV_DEBUG_KMS(dev->dev, "dma_addw is invawid.\n");
		wetuwn;
	}

	DWM_DEV_DEBUG_KMS(dev->dev, "dma_addw(0x%wx), size(0x%wx)\n",
			(unsigned wong)exynos_gem->dma_addw, exynos_gem->size);

	dma_fwee_attws(to_dma_dev(dev), exynos_gem->size, exynos_gem->cookie,
			(dma_addw_t)exynos_gem->dma_addw,
			exynos_gem->dma_attws);
}

static int exynos_dwm_gem_handwe_cweate(stwuct dwm_gem_object *obj,
					stwuct dwm_fiwe *fiwe_pwiv,
					unsigned int *handwe)
{
	int wet;

	/*
	 * awwocate a id of idw tabwe whewe the obj is wegistewed
	 * and handwe has the id what usew can see.
	 */
	wet = dwm_gem_handwe_cweate(fiwe_pwiv, obj, handwe);
	if (wet)
		wetuwn wet;

	DWM_DEV_DEBUG_KMS(to_dma_dev(obj->dev), "gem handwe = 0x%x\n", *handwe);

	/* dwop wefewence fwom awwocate - handwe howds it now. */
	dwm_gem_object_put(obj);

	wetuwn 0;
}

void exynos_dwm_gem_destwoy(stwuct exynos_dwm_gem *exynos_gem)
{
	stwuct dwm_gem_object *obj = &exynos_gem->base;

	DWM_DEV_DEBUG_KMS(to_dma_dev(obj->dev), "handwe count = %d\n",
			  obj->handwe_count);

	/*
	 * do not wewease memowy wegion fwom expowtew.
	 *
	 * the wegion wiww be weweased by expowtew
	 * once dmabuf's wefcount becomes 0.
	 */
	if (obj->impowt_attach)
		dwm_pwime_gem_destwoy(obj, exynos_gem->sgt);
	ewse
		exynos_dwm_fwee_buf(exynos_gem);

	/* wewease fiwe pointew to gem object. */
	dwm_gem_object_wewease(obj);

	kfwee(exynos_gem);
}

static const stwuct vm_opewations_stwuct exynos_dwm_gem_vm_ops = {
	.open = dwm_gem_vm_open,
	.cwose = dwm_gem_vm_cwose,
};

static const stwuct dwm_gem_object_funcs exynos_dwm_gem_object_funcs = {
	.fwee = exynos_dwm_gem_fwee_object,
	.get_sg_tabwe = exynos_dwm_gem_pwime_get_sg_tabwe,
	.mmap = exynos_dwm_gem_mmap,
	.vm_ops = &exynos_dwm_gem_vm_ops,
};

static stwuct exynos_dwm_gem *exynos_dwm_gem_init(stwuct dwm_device *dev,
						  unsigned wong size)
{
	stwuct exynos_dwm_gem *exynos_gem;
	stwuct dwm_gem_object *obj;
	int wet;

	exynos_gem = kzawwoc(sizeof(*exynos_gem), GFP_KEWNEW);
	if (!exynos_gem)
		wetuwn EWW_PTW(-ENOMEM);

	exynos_gem->size = size;
	obj = &exynos_gem->base;

	obj->funcs = &exynos_dwm_gem_object_funcs;

	wet = dwm_gem_object_init(dev, obj, size);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to initiawize gem object\n");
		kfwee(exynos_gem);
		wetuwn EWW_PTW(wet);
	}

	wet = dwm_gem_cweate_mmap_offset(obj);
	if (wet < 0) {
		dwm_gem_object_wewease(obj);
		kfwee(exynos_gem);
		wetuwn EWW_PTW(wet);
	}

	DWM_DEV_DEBUG_KMS(dev->dev, "cweated fiwe object = %pK\n", obj->fiwp);

	wetuwn exynos_gem;
}

stwuct exynos_dwm_gem *exynos_dwm_gem_cweate(stwuct dwm_device *dev,
					     unsigned int fwags,
					     unsigned wong size,
					     boow kvmap)
{
	stwuct exynos_dwm_gem *exynos_gem;
	int wet;

	if (fwags & ~(EXYNOS_BO_MASK)) {
		DWM_DEV_EWWOW(dev->dev,
			      "invawid GEM buffew fwags: %u\n", fwags);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!size) {
		DWM_DEV_EWWOW(dev->dev, "invawid GEM buffew size: %wu\n", size);
		wetuwn EWW_PTW(-EINVAW);
	}

	size = woundup(size, PAGE_SIZE);

	exynos_gem = exynos_dwm_gem_init(dev, size);
	if (IS_EWW(exynos_gem))
		wetuwn exynos_gem;

	if (!is_dwm_iommu_suppowted(dev) && (fwags & EXYNOS_BO_NONCONTIG)) {
		/*
		 * when no IOMMU is avaiwabwe, aww awwocated buffews awe
		 * contiguous anyway, so dwop EXYNOS_BO_NONCONTIG fwag
		 */
		fwags &= ~EXYNOS_BO_NONCONTIG;
		DWM_WAWN("Non-contiguous awwocation is not suppowted without IOMMU, fawwing back to contiguous buffew\n");
	}

	/* set memowy type and cache attwibute fwom usew side. */
	exynos_gem->fwags = fwags;

	wet = exynos_dwm_awwoc_buf(exynos_gem, kvmap);
	if (wet < 0) {
		dwm_gem_object_wewease(&exynos_gem->base);
		kfwee(exynos_gem);
		wetuwn EWW_PTW(wet);
	}

	wetuwn exynos_gem;
}

int exynos_dwm_gem_cweate_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_exynos_gem_cweate *awgs = data;
	stwuct exynos_dwm_gem *exynos_gem;
	int wet;

	exynos_gem = exynos_dwm_gem_cweate(dev, awgs->fwags, awgs->size, fawse);
	if (IS_EWW(exynos_gem))
		wetuwn PTW_EWW(exynos_gem);

	wet = exynos_dwm_gem_handwe_cweate(&exynos_gem->base, fiwe_pwiv,
					   &awgs->handwe);
	if (wet) {
		exynos_dwm_gem_destwoy(exynos_gem);
		wetuwn wet;
	}

	wetuwn 0;
}

int exynos_dwm_gem_map_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_exynos_gem_map *awgs = data;

	wetuwn dwm_gem_dumb_map_offset(fiwe_pwiv, dev, awgs->handwe,
				       &awgs->offset);
}

stwuct exynos_dwm_gem *exynos_dwm_gem_get(stwuct dwm_fiwe *fiwp,
					  unsigned int gem_handwe)
{
	stwuct dwm_gem_object *obj;

	obj = dwm_gem_object_wookup(fiwp, gem_handwe);
	if (!obj)
		wetuwn NUWW;
	wetuwn to_exynos_gem(obj);
}

static int exynos_dwm_gem_mmap_buffew(stwuct exynos_dwm_gem *exynos_gem,
				      stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_device *dwm_dev = exynos_gem->base.dev;
	unsigned wong vm_size;
	int wet;

	vm_fwags_cweaw(vma, VM_PFNMAP);
	vma->vm_pgoff = 0;

	vm_size = vma->vm_end - vma->vm_stawt;

	/* check if usew-wequested size is vawid. */
	if (vm_size > exynos_gem->size)
		wetuwn -EINVAW;

	wet = dma_mmap_attws(to_dma_dev(dwm_dev), vma, exynos_gem->cookie,
			     exynos_gem->dma_addw, exynos_gem->size,
			     exynos_gem->dma_attws);
	if (wet < 0) {
		DWM_EWWOW("faiwed to mmap.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

int exynos_dwm_gem_get_ioctw(stwuct dwm_device *dev, void *data,
				      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct exynos_dwm_gem *exynos_gem;
	stwuct dwm_exynos_gem_info *awgs = data;
	stwuct dwm_gem_object *obj;

	obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!obj) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to wookup gem object.\n");
		wetuwn -EINVAW;
	}

	exynos_gem = to_exynos_gem(obj);

	awgs->fwags = exynos_gem->fwags;
	awgs->size = exynos_gem->size;

	dwm_gem_object_put(obj);

	wetuwn 0;
}

void exynos_dwm_gem_fwee_object(stwuct dwm_gem_object *obj)
{
	exynos_dwm_gem_destwoy(to_exynos_gem(obj));
}

int exynos_dwm_gem_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
			       stwuct dwm_device *dev,
			       stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct exynos_dwm_gem *exynos_gem;
	unsigned int fwags;
	int wet;

	/*
	 * awwocate memowy to be used fow fwamebuffew.
	 * - this cawwback wouwd be cawwed by usew appwication
	 *	with DWM_IOCTW_MODE_CWEATE_DUMB command.
	 */

	awgs->pitch = awgs->width * ((awgs->bpp + 7) / 8);
	awgs->size = awgs->pitch * awgs->height;

	if (is_dwm_iommu_suppowted(dev))
		fwags = EXYNOS_BO_NONCONTIG | EXYNOS_BO_WC;
	ewse
		fwags = EXYNOS_BO_CONTIG | EXYNOS_BO_WC;

	exynos_gem = exynos_dwm_gem_cweate(dev, fwags, awgs->size, fawse);
	if (IS_EWW(exynos_gem)) {
		dev_wawn(dev->dev, "FB awwocation faiwed.\n");
		wetuwn PTW_EWW(exynos_gem);
	}

	wet = exynos_dwm_gem_handwe_cweate(&exynos_gem->base, fiwe_pwiv,
					   &awgs->handwe);
	if (wet) {
		exynos_dwm_gem_destwoy(exynos_gem);
		wetuwn wet;
	}

	wetuwn 0;
}

static int exynos_dwm_gem_mmap(stwuct dwm_gem_object *obj, stwuct vm_awea_stwuct *vma)
{
	stwuct exynos_dwm_gem *exynos_gem = to_exynos_gem(obj);
	int wet;

	if (obj->impowt_attach)
		wetuwn dma_buf_mmap(obj->dma_buf, vma, 0);

	vm_fwags_set(vma, VM_IO | VM_DONTEXPAND | VM_DONTDUMP);

	DWM_DEV_DEBUG_KMS(to_dma_dev(obj->dev), "fwags = 0x%x\n",
			  exynos_gem->fwags);

	/* non-cachabwe as defauwt. */
	if (exynos_gem->fwags & EXYNOS_BO_CACHABWE)
		vma->vm_page_pwot = vm_get_page_pwot(vma->vm_fwags);
	ewse if (exynos_gem->fwags & EXYNOS_BO_WC)
		vma->vm_page_pwot =
			pgpwot_wwitecombine(vm_get_page_pwot(vma->vm_fwags));
	ewse
		vma->vm_page_pwot =
			pgpwot_noncached(vm_get_page_pwot(vma->vm_fwags));

	wet = exynos_dwm_gem_mmap_buffew(exynos_gem, vma);
	if (wet)
		goto eww_cwose_vm;

	wetuwn wet;

eww_cwose_vm:
	dwm_gem_vm_cwose(vma);

	wetuwn wet;
}

/* wow-wevew intewface pwime hewpews */
stwuct dwm_gem_object *exynos_dwm_gem_pwime_impowt(stwuct dwm_device *dev,
					    stwuct dma_buf *dma_buf)
{
	wetuwn dwm_gem_pwime_impowt_dev(dev, dma_buf, to_dma_dev(dev));
}

stwuct sg_tabwe *exynos_dwm_gem_pwime_get_sg_tabwe(stwuct dwm_gem_object *obj)
{
	stwuct exynos_dwm_gem *exynos_gem = to_exynos_gem(obj);
	stwuct dwm_device *dwm_dev = obj->dev;
	stwuct sg_tabwe *sgt;
	int wet;

	sgt = kzawwoc(sizeof(*sgt), GFP_KEWNEW);
	if (!sgt)
		wetuwn EWW_PTW(-ENOMEM);

	wet = dma_get_sgtabwe_attws(to_dma_dev(dwm_dev), sgt, exynos_gem->cookie,
				    exynos_gem->dma_addw, exynos_gem->size,
				    exynos_gem->dma_attws);
	if (wet) {
		DWM_EWWOW("faiwed to get sgtabwe, %d\n", wet);
		kfwee(sgt);
		wetuwn EWW_PTW(wet);
	}

	wetuwn sgt;
}

stwuct dwm_gem_object *
exynos_dwm_gem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
				     stwuct dma_buf_attachment *attach,
				     stwuct sg_tabwe *sgt)
{
	stwuct exynos_dwm_gem *exynos_gem;

	/* check if the entwies in the sg_tabwe awe contiguous */
	if (dwm_pwime_get_contiguous_size(sgt) < attach->dmabuf->size) {
		DWM_EWWOW("buffew chunks must be mapped contiguouswy");
		wetuwn EWW_PTW(-EINVAW);
	}

	exynos_gem = exynos_dwm_gem_init(dev, attach->dmabuf->size);
	if (IS_EWW(exynos_gem))
		wetuwn EWW_CAST(exynos_gem);

	/*
	 * Buffew has been mapped as contiguous into DMA addwess space,
	 * but if thewe is IOMMU, it can be eithew CONTIG ow NONCONTIG.
	 * We assume a simpwified wogic bewow:
	 */
	if (is_dwm_iommu_suppowted(dev))
		exynos_gem->fwags |= EXYNOS_BO_NONCONTIG;
	ewse
		exynos_gem->fwags |= EXYNOS_BO_CONTIG;

	exynos_gem->dma_addw = sg_dma_addwess(sgt->sgw);
	exynos_gem->sgt = sgt;
	wetuwn &exynos_gem->base;
}
