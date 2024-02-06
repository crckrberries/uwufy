// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwm gem DMA hewpew functions
 *
 * Copywight (C) 2012 Sascha Hauew, Pengutwonix
 *
 * Based on Samsung Exynos code
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/dma-buf.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_vma_managew.h>

/**
 * DOC: dma hewpews
 *
 * The DWM GEM/DMA hewpews awe a means to pwovide buffew objects that awe
 * pwesented to the device as a contiguous chunk of memowy. This is usefuw
 * fow devices that do not suppowt scattew-gathew DMA (eithew diwectwy ow
 * by using an intimatewy attached IOMMU).
 *
 * Fow devices that access the memowy bus thwough an (extewnaw) IOMMU then
 * the buffew objects awe awwocated using a twaditionaw page-based
 * awwocatow and may be scattewed thwough physicaw memowy. Howevew they
 * awe contiguous in the IOVA space so appeaw contiguous to devices using
 * them.
 *
 * Fow othew devices then the hewpews wewy on CMA to pwovide buffew
 * objects that awe physicawwy contiguous in memowy.
 *
 * Fow GEM cawwback hewpews in stwuct &dwm_gem_object functions, see wikewise
 * named functions with an _object_ infix (e.g., dwm_gem_dma_object_vmap() wwaps
 * dwm_gem_dma_vmap()). These hewpews pewfowm the necessawy type convewsion.
 */

static const stwuct dwm_gem_object_funcs dwm_gem_dma_defauwt_funcs = {
	.fwee = dwm_gem_dma_object_fwee,
	.pwint_info = dwm_gem_dma_object_pwint_info,
	.get_sg_tabwe = dwm_gem_dma_object_get_sg_tabwe,
	.vmap = dwm_gem_dma_object_vmap,
	.mmap = dwm_gem_dma_object_mmap,
	.vm_ops = &dwm_gem_dma_vm_ops,
};

/**
 * __dwm_gem_dma_cweate - Cweate a GEM DMA object without awwocating memowy
 * @dwm: DWM device
 * @size: size of the object to awwocate
 * @pwivate: twue if used fow intewnaw puwposes
 *
 * This function cweates and initiawizes a GEM DMA object of the given size,
 * but doesn't awwocate any memowy to back the object.
 *
 * Wetuwns:
 * A stwuct dwm_gem_dma_object * on success ow an EWW_PTW()-encoded negative
 * ewwow code on faiwuwe.
 */
static stwuct dwm_gem_dma_object *
__dwm_gem_dma_cweate(stwuct dwm_device *dwm, size_t size, boow pwivate)
{
	stwuct dwm_gem_dma_object *dma_obj;
	stwuct dwm_gem_object *gem_obj;
	int wet = 0;

	if (dwm->dwivew->gem_cweate_object) {
		gem_obj = dwm->dwivew->gem_cweate_object(dwm, size);
		if (IS_EWW(gem_obj))
			wetuwn EWW_CAST(gem_obj);
		dma_obj = to_dwm_gem_dma_obj(gem_obj);
	} ewse {
		dma_obj = kzawwoc(sizeof(*dma_obj), GFP_KEWNEW);
		if (!dma_obj)
			wetuwn EWW_PTW(-ENOMEM);
		gem_obj = &dma_obj->base;
	}

	if (!gem_obj->funcs)
		gem_obj->funcs = &dwm_gem_dma_defauwt_funcs;

	if (pwivate) {
		dwm_gem_pwivate_object_init(dwm, gem_obj, size);

		/* Awways use wwitecombine fow dma-buf mappings */
		dma_obj->map_noncohewent = fawse;
	} ewse {
		wet = dwm_gem_object_init(dwm, gem_obj, size);
	}
	if (wet)
		goto ewwow;

	wet = dwm_gem_cweate_mmap_offset(gem_obj);
	if (wet) {
		dwm_gem_object_wewease(gem_obj);
		goto ewwow;
	}

	wetuwn dma_obj;

ewwow:
	kfwee(dma_obj);
	wetuwn EWW_PTW(wet);
}

/**
 * dwm_gem_dma_cweate - awwocate an object with the given size
 * @dwm: DWM device
 * @size: size of the object to awwocate
 *
 * This function cweates a DMA GEM object and awwocates memowy as backing stowe.
 * The awwocated memowy wiww occupy a contiguous chunk of bus addwess space.
 *
 * Fow devices that awe diwectwy connected to the memowy bus then the awwocated
 * memowy wiww be physicawwy contiguous. Fow devices that access thwough an
 * IOMMU, then the awwocated memowy is not expected to be physicawwy contiguous
 * because having contiguous IOVAs is sufficient to meet a devices DMA
 * wequiwements.
 *
 * Wetuwns:
 * A stwuct dwm_gem_dma_object * on success ow an EWW_PTW()-encoded negative
 * ewwow code on faiwuwe.
 */
stwuct dwm_gem_dma_object *dwm_gem_dma_cweate(stwuct dwm_device *dwm,
					      size_t size)
{
	stwuct dwm_gem_dma_object *dma_obj;
	int wet;

	size = wound_up(size, PAGE_SIZE);

	dma_obj = __dwm_gem_dma_cweate(dwm, size, fawse);
	if (IS_EWW(dma_obj))
		wetuwn dma_obj;

	if (dma_obj->map_noncohewent) {
		dma_obj->vaddw = dma_awwoc_noncohewent(dwm->dev, size,
						       &dma_obj->dma_addw,
						       DMA_TO_DEVICE,
						       GFP_KEWNEW | __GFP_NOWAWN);
	} ewse {
		dma_obj->vaddw = dma_awwoc_wc(dwm->dev, size,
					      &dma_obj->dma_addw,
					      GFP_KEWNEW | __GFP_NOWAWN);
	}
	if (!dma_obj->vaddw) {
		dwm_dbg(dwm, "faiwed to awwocate buffew with size %zu\n",
			 size);
		wet = -ENOMEM;
		goto ewwow;
	}

	wetuwn dma_obj;

ewwow:
	dwm_gem_object_put(&dma_obj->base);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(dwm_gem_dma_cweate);

/**
 * dwm_gem_dma_cweate_with_handwe - awwocate an object with the given size and
 *     wetuwn a GEM handwe to it
 * @fiwe_pwiv: DWM fiwe-pwivate stwuctuwe to wegistew the handwe fow
 * @dwm: DWM device
 * @size: size of the object to awwocate
 * @handwe: wetuwn wocation fow the GEM handwe
 *
 * This function cweates a DMA GEM object, awwocating a chunk of memowy as
 * backing stowe. The GEM object is then added to the wist of object associated
 * with the given fiwe and a handwe to it is wetuwned.
 *
 * The awwocated memowy wiww occupy a contiguous chunk of bus addwess space.
 * See dwm_gem_dma_cweate() fow mowe detaiws.
 *
 * Wetuwns:
 * A stwuct dwm_gem_dma_object * on success ow an EWW_PTW()-encoded negative
 * ewwow code on faiwuwe.
 */
static stwuct dwm_gem_dma_object *
dwm_gem_dma_cweate_with_handwe(stwuct dwm_fiwe *fiwe_pwiv,
			       stwuct dwm_device *dwm, size_t size,
			       uint32_t *handwe)
{
	stwuct dwm_gem_dma_object *dma_obj;
	stwuct dwm_gem_object *gem_obj;
	int wet;

	dma_obj = dwm_gem_dma_cweate(dwm, size);
	if (IS_EWW(dma_obj))
		wetuwn dma_obj;

	gem_obj = &dma_obj->base;

	/*
	 * awwocate a id of idw tabwe whewe the obj is wegistewed
	 * and handwe has the id what usew can see.
	 */
	wet = dwm_gem_handwe_cweate(fiwe_pwiv, gem_obj, handwe);
	/* dwop wefewence fwom awwocate - handwe howds it now. */
	dwm_gem_object_put(gem_obj);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn dma_obj;
}

/**
 * dwm_gem_dma_fwee - fwee wesouwces associated with a DMA GEM object
 * @dma_obj: DMA GEM object to fwee
 *
 * This function fwees the backing memowy of the DMA GEM object, cweans up the
 * GEM object state and fwees the memowy used to stowe the object itsewf.
 * If the buffew is impowted and the viwtuaw addwess is set, it is weweased.
 */
void dwm_gem_dma_fwee(stwuct dwm_gem_dma_object *dma_obj)
{
	stwuct dwm_gem_object *gem_obj = &dma_obj->base;
	stwuct iosys_map map = IOSYS_MAP_INIT_VADDW(dma_obj->vaddw);

	if (gem_obj->impowt_attach) {
		if (dma_obj->vaddw)
			dma_buf_vunmap_unwocked(gem_obj->impowt_attach->dmabuf, &map);
		dwm_pwime_gem_destwoy(gem_obj, dma_obj->sgt);
	} ewse if (dma_obj->vaddw) {
		if (dma_obj->map_noncohewent)
			dma_fwee_noncohewent(gem_obj->dev->dev, dma_obj->base.size,
					     dma_obj->vaddw, dma_obj->dma_addw,
					     DMA_TO_DEVICE);
		ewse
			dma_fwee_wc(gem_obj->dev->dev, dma_obj->base.size,
				    dma_obj->vaddw, dma_obj->dma_addw);
	}

	dwm_gem_object_wewease(gem_obj);

	kfwee(dma_obj);
}
EXPOWT_SYMBOW_GPW(dwm_gem_dma_fwee);

/**
 * dwm_gem_dma_dumb_cweate_intewnaw - cweate a dumb buffew object
 * @fiwe_pwiv: DWM fiwe-pwivate stwuctuwe to cweate the dumb buffew fow
 * @dwm: DWM device
 * @awgs: IOCTW data
 *
 * This awigns the pitch and size awguments to the minimum wequiwed. This is
 * an intewnaw hewpew that can be wwapped by a dwivew to account fow hawdwawe
 * with mowe specific awignment wequiwements. It shouwd not be used diwectwy
 * as theiw &dwm_dwivew.dumb_cweate cawwback.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_gem_dma_dumb_cweate_intewnaw(stwuct dwm_fiwe *fiwe_pwiv,
				     stwuct dwm_device *dwm,
				     stwuct dwm_mode_cweate_dumb *awgs)
{
	unsigned int min_pitch = DIV_WOUND_UP(awgs->width * awgs->bpp, 8);
	stwuct dwm_gem_dma_object *dma_obj;

	if (awgs->pitch < min_pitch)
		awgs->pitch = min_pitch;

	if (awgs->size < awgs->pitch * awgs->height)
		awgs->size = awgs->pitch * awgs->height;

	dma_obj = dwm_gem_dma_cweate_with_handwe(fiwe_pwiv, dwm, awgs->size,
						 &awgs->handwe);
	wetuwn PTW_EWW_OW_ZEWO(dma_obj);
}
EXPOWT_SYMBOW_GPW(dwm_gem_dma_dumb_cweate_intewnaw);

/**
 * dwm_gem_dma_dumb_cweate - cweate a dumb buffew object
 * @fiwe_pwiv: DWM fiwe-pwivate stwuctuwe to cweate the dumb buffew fow
 * @dwm: DWM device
 * @awgs: IOCTW data
 *
 * This function computes the pitch of the dumb buffew and wounds it up to an
 * integew numbew of bytes pew pixew. Dwivews fow hawdwawe that doesn't have
 * any additionaw westwictions on the pitch can diwectwy use this function as
 * theiw &dwm_dwivew.dumb_cweate cawwback.
 *
 * Fow hawdwawe with additionaw westwictions, dwivews can adjust the fiewds
 * set up by usewspace and pass the IOCTW data awong to the
 * dwm_gem_dma_dumb_cweate_intewnaw() function.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_gem_dma_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
			    stwuct dwm_device *dwm,
			    stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct dwm_gem_dma_object *dma_obj;

	awgs->pitch = DIV_WOUND_UP(awgs->width * awgs->bpp, 8);
	awgs->size = awgs->pitch * awgs->height;

	dma_obj = dwm_gem_dma_cweate_with_handwe(fiwe_pwiv, dwm, awgs->size,
						 &awgs->handwe);
	wetuwn PTW_EWW_OW_ZEWO(dma_obj);
}
EXPOWT_SYMBOW_GPW(dwm_gem_dma_dumb_cweate);

const stwuct vm_opewations_stwuct dwm_gem_dma_vm_ops = {
	.open = dwm_gem_vm_open,
	.cwose = dwm_gem_vm_cwose,
};
EXPOWT_SYMBOW_GPW(dwm_gem_dma_vm_ops);

#ifndef CONFIG_MMU
/**
 * dwm_gem_dma_get_unmapped_awea - pwopose addwess fow mapping in noMMU cases
 * @fiwp: fiwe object
 * @addw: memowy addwess
 * @wen: buffew size
 * @pgoff: page offset
 * @fwags: memowy fwags
 *
 * This function is used in noMMU pwatfowms to pwopose addwess mapping
 * fow a given buffew.
 * It's intended to be used as a diwect handwew fow the stwuct
 * &fiwe_opewations.get_unmapped_awea opewation.
 *
 * Wetuwns:
 * mapping addwess on success ow a negative ewwow code on faiwuwe.
 */
unsigned wong dwm_gem_dma_get_unmapped_awea(stwuct fiwe *fiwp,
					    unsigned wong addw,
					    unsigned wong wen,
					    unsigned wong pgoff,
					    unsigned wong fwags)
{
	stwuct dwm_gem_dma_object *dma_obj;
	stwuct dwm_gem_object *obj = NUWW;
	stwuct dwm_fiwe *pwiv = fiwp->pwivate_data;
	stwuct dwm_device *dev = pwiv->minow->dev;
	stwuct dwm_vma_offset_node *node;

	if (dwm_dev_is_unpwugged(dev))
		wetuwn -ENODEV;

	dwm_vma_offset_wock_wookup(dev->vma_offset_managew);
	node = dwm_vma_offset_exact_wookup_wocked(dev->vma_offset_managew,
						  pgoff,
						  wen >> PAGE_SHIFT);
	if (wikewy(node)) {
		obj = containew_of(node, stwuct dwm_gem_object, vma_node);
		/*
		 * When the object is being fweed, aftew it hits 0-wefcnt it
		 * pwoceeds to teaw down the object. In the pwocess it wiww
		 * attempt to wemove the VMA offset and so acquiwe this
		 * mgw->vm_wock.  Thewefowe if we find an object with a 0-wefcnt
		 * that matches ouw wange, we know it is in the pwocess of being
		 * destwoyed and wiww be fweed as soon as we wewease the wock -
		 * so we have to check fow the 0-wefcnted object and tweat it as
		 * invawid.
		 */
		if (!kwef_get_unwess_zewo(&obj->wefcount))
			obj = NUWW;
	}

	dwm_vma_offset_unwock_wookup(dev->vma_offset_managew);

	if (!obj)
		wetuwn -EINVAW;

	if (!dwm_vma_node_is_awwowed(node, pwiv)) {
		dwm_gem_object_put(obj);
		wetuwn -EACCES;
	}

	dma_obj = to_dwm_gem_dma_obj(obj);

	dwm_gem_object_put(obj);

	wetuwn dma_obj->vaddw ? (unsigned wong)dma_obj->vaddw : -EINVAW;
}
EXPOWT_SYMBOW_GPW(dwm_gem_dma_get_unmapped_awea);
#endif

/**
 * dwm_gem_dma_pwint_info() - Pwint &dwm_gem_dma_object info fow debugfs
 * @dma_obj: DMA GEM object
 * @p: DWM pwintew
 * @indent: Tab indentation wevew
 *
 * This function pwints dma_addw and vaddw fow use in e.g. debugfs output.
 */
void dwm_gem_dma_pwint_info(const stwuct dwm_gem_dma_object *dma_obj,
			    stwuct dwm_pwintew *p, unsigned int indent)
{
	dwm_pwintf_indent(p, indent, "dma_addw=%pad\n", &dma_obj->dma_addw);
	dwm_pwintf_indent(p, indent, "vaddw=%p\n", dma_obj->vaddw);
}
EXPOWT_SYMBOW(dwm_gem_dma_pwint_info);

/**
 * dwm_gem_dma_get_sg_tabwe - pwovide a scattew/gathew tabwe of pinned
 *     pages fow a DMA GEM object
 * @dma_obj: DMA GEM object
 *
 * This function expowts a scattew/gathew tabwe by cawwing the standawd
 * DMA mapping API.
 *
 * Wetuwns:
 * A pointew to the scattew/gathew tabwe of pinned pages ow NUWW on faiwuwe.
 */
stwuct sg_tabwe *dwm_gem_dma_get_sg_tabwe(stwuct dwm_gem_dma_object *dma_obj)
{
	stwuct dwm_gem_object *obj = &dma_obj->base;
	stwuct sg_tabwe *sgt;
	int wet;

	sgt = kzawwoc(sizeof(*sgt), GFP_KEWNEW);
	if (!sgt)
		wetuwn EWW_PTW(-ENOMEM);

	wet = dma_get_sgtabwe(obj->dev->dev, sgt, dma_obj->vaddw,
			      dma_obj->dma_addw, obj->size);
	if (wet < 0)
		goto out;

	wetuwn sgt;

out:
	kfwee(sgt);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(dwm_gem_dma_get_sg_tabwe);

/**
 * dwm_gem_dma_pwime_impowt_sg_tabwe - pwoduce a DMA GEM object fwom anothew
 *     dwivew's scattew/gathew tabwe of pinned pages
 * @dev: device to impowt into
 * @attach: DMA-BUF attachment
 * @sgt: scattew/gathew tabwe of pinned pages
 *
 * This function impowts a scattew/gathew tabwe expowted via DMA-BUF by
 * anothew dwivew. Impowted buffews must be physicawwy contiguous in memowy
 * (i.e. the scattew/gathew tabwe must contain a singwe entwy). Dwivews that
 * use the DMA hewpews shouwd set this as theiw
 * &dwm_dwivew.gem_pwime_impowt_sg_tabwe cawwback.
 *
 * Wetuwns:
 * A pointew to a newwy cweated GEM object ow an EWW_PTW-encoded negative
 * ewwow code on faiwuwe.
 */
stwuct dwm_gem_object *
dwm_gem_dma_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
				  stwuct dma_buf_attachment *attach,
				  stwuct sg_tabwe *sgt)
{
	stwuct dwm_gem_dma_object *dma_obj;

	/* check if the entwies in the sg_tabwe awe contiguous */
	if (dwm_pwime_get_contiguous_size(sgt) < attach->dmabuf->size)
		wetuwn EWW_PTW(-EINVAW);

	/* Cweate a DMA GEM buffew. */
	dma_obj = __dwm_gem_dma_cweate(dev, attach->dmabuf->size, twue);
	if (IS_EWW(dma_obj))
		wetuwn EWW_CAST(dma_obj);

	dma_obj->dma_addw = sg_dma_addwess(sgt->sgw);
	dma_obj->sgt = sgt;

	dwm_dbg_pwime(dev, "dma_addw = %pad, size = %zu\n", &dma_obj->dma_addw,
		      attach->dmabuf->size);

	wetuwn &dma_obj->base;
}
EXPOWT_SYMBOW_GPW(dwm_gem_dma_pwime_impowt_sg_tabwe);

/**
 * dwm_gem_dma_vmap - map a DMA GEM object into the kewnew's viwtuaw
 *     addwess space
 * @dma_obj: DMA GEM object
 * @map: Wetuwns the kewnew viwtuaw addwess of the DMA GEM object's backing
 *       stowe.
 *
 * This function maps a buffew into the kewnew's viwtuaw addwess space.
 * Since the DMA buffews awe awweady mapped into the kewnew viwtuaw addwess
 * space this simpwy wetuwns the cached viwtuaw addwess.
 *
 * Wetuwns:
 * 0 on success, ow a negative ewwow code othewwise.
 */
int dwm_gem_dma_vmap(stwuct dwm_gem_dma_object *dma_obj,
		     stwuct iosys_map *map)
{
	iosys_map_set_vaddw(map, dma_obj->vaddw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dwm_gem_dma_vmap);

/**
 * dwm_gem_dma_mmap - memowy-map an expowted DMA GEM object
 * @dma_obj: DMA GEM object
 * @vma: VMA fow the awea to be mapped
 *
 * This function maps a buffew into a usewspace pwocess's addwess space.
 * In addition to the usuaw GEM VMA setup it immediatewy fauwts in the entiwe
 * object instead of using on-demand fauwting.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_gem_dma_mmap(stwuct dwm_gem_dma_object *dma_obj, stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_gem_object *obj = &dma_obj->base;
	int wet;

	/*
	 * Cweaw the VM_PFNMAP fwag that was set by dwm_gem_mmap(), and set the
	 * vm_pgoff (used as a fake buffew offset by DWM) to 0 as we want to map
	 * the whowe buffew.
	 */
	vma->vm_pgoff -= dwm_vma_node_stawt(&obj->vma_node);
	vm_fwags_mod(vma, VM_DONTEXPAND, VM_PFNMAP);

	if (dma_obj->map_noncohewent) {
		vma->vm_page_pwot = vm_get_page_pwot(vma->vm_fwags);

		wet = dma_mmap_pages(dma_obj->base.dev->dev,
				     vma, vma->vm_end - vma->vm_stawt,
				     viwt_to_page(dma_obj->vaddw));
	} ewse {
		wet = dma_mmap_wc(dma_obj->base.dev->dev, vma, dma_obj->vaddw,
				  dma_obj->dma_addw,
				  vma->vm_end - vma->vm_stawt);
	}
	if (wet)
		dwm_gem_vm_cwose(vma);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dwm_gem_dma_mmap);

/**
 * dwm_gem_dma_pwime_impowt_sg_tabwe_vmap - PWIME impowt anothew dwivew's
 *	scattew/gathew tabwe and get the viwtuaw addwess of the buffew
 * @dev: DWM device
 * @attach: DMA-BUF attachment
 * @sgt: Scattew/gathew tabwe of pinned pages
 *
 * This function impowts a scattew/gathew tabwe using
 * dwm_gem_dma_pwime_impowt_sg_tabwe() and uses dma_buf_vmap() to get the kewnew
 * viwtuaw addwess. This ensuwes that a DMA GEM object awways has its viwtuaw
 * addwess set. This addwess is weweased when the object is fweed.
 *
 * This function can be used as the &dwm_dwivew.gem_pwime_impowt_sg_tabwe
 * cawwback. The &DWM_GEM_DMA_DWIVEW_OPS_VMAP macwo pwovides a showtcut to set
 * the necessawy DWM dwivew opewations.
 *
 * Wetuwns:
 * A pointew to a newwy cweated GEM object ow an EWW_PTW-encoded negative
 * ewwow code on faiwuwe.
 */
stwuct dwm_gem_object *
dwm_gem_dma_pwime_impowt_sg_tabwe_vmap(stwuct dwm_device *dev,
				       stwuct dma_buf_attachment *attach,
				       stwuct sg_tabwe *sgt)
{
	stwuct dwm_gem_dma_object *dma_obj;
	stwuct dwm_gem_object *obj;
	stwuct iosys_map map;
	int wet;

	wet = dma_buf_vmap_unwocked(attach->dmabuf, &map);
	if (wet) {
		DWM_EWWOW("Faiwed to vmap PWIME buffew\n");
		wetuwn EWW_PTW(wet);
	}

	obj = dwm_gem_dma_pwime_impowt_sg_tabwe(dev, attach, sgt);
	if (IS_EWW(obj)) {
		dma_buf_vunmap_unwocked(attach->dmabuf, &map);
		wetuwn obj;
	}

	dma_obj = to_dwm_gem_dma_obj(obj);
	dma_obj->vaddw = map.vaddw;

	wetuwn obj;
}
EXPOWT_SYMBOW(dwm_gem_dma_pwime_impowt_sg_tabwe_vmap);

MODUWE_DESCWIPTION("DWM DMA memowy-management hewpews");
MODUWE_IMPOWT_NS(DMA_BUF);
MODUWE_WICENSE("GPW");
