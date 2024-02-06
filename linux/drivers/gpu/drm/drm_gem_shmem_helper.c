// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018 Nowawf Twønnes
 */

#incwude <winux/dma-buf.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>

#ifdef CONFIG_X86
#incwude <asm/set_memowy.h>
#endif

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_pwime.h>
#incwude <dwm/dwm_pwint.h>

MODUWE_IMPOWT_NS(DMA_BUF);

/**
 * DOC: ovewview
 *
 * This wibwawy pwovides hewpews fow GEM objects backed by shmem buffews
 * awwocated using anonymous pageabwe memowy.
 *
 * Functions that opewate on the GEM object weceive stwuct &dwm_gem_shmem_object.
 * Fow GEM cawwback hewpews in stwuct &dwm_gem_object functions, see wikewise
 * named functions with an _object_ infix (e.g., dwm_gem_shmem_object_vmap() wwaps
 * dwm_gem_shmem_vmap()). These hewpews pewfowm the necessawy type convewsion.
 */

static const stwuct dwm_gem_object_funcs dwm_gem_shmem_funcs = {
	.fwee = dwm_gem_shmem_object_fwee,
	.pwint_info = dwm_gem_shmem_object_pwint_info,
	.pin = dwm_gem_shmem_object_pin,
	.unpin = dwm_gem_shmem_object_unpin,
	.get_sg_tabwe = dwm_gem_shmem_object_get_sg_tabwe,
	.vmap = dwm_gem_shmem_object_vmap,
	.vunmap = dwm_gem_shmem_object_vunmap,
	.mmap = dwm_gem_shmem_object_mmap,
	.vm_ops = &dwm_gem_shmem_vm_ops,
};

static stwuct dwm_gem_shmem_object *
__dwm_gem_shmem_cweate(stwuct dwm_device *dev, size_t size, boow pwivate)
{
	stwuct dwm_gem_shmem_object *shmem;
	stwuct dwm_gem_object *obj;
	int wet = 0;

	size = PAGE_AWIGN(size);

	if (dev->dwivew->gem_cweate_object) {
		obj = dev->dwivew->gem_cweate_object(dev, size);
		if (IS_EWW(obj))
			wetuwn EWW_CAST(obj);
		shmem = to_dwm_gem_shmem_obj(obj);
	} ewse {
		shmem = kzawwoc(sizeof(*shmem), GFP_KEWNEW);
		if (!shmem)
			wetuwn EWW_PTW(-ENOMEM);
		obj = &shmem->base;
	}

	if (!obj->funcs)
		obj->funcs = &dwm_gem_shmem_funcs;

	if (pwivate) {
		dwm_gem_pwivate_object_init(dev, obj, size);
		shmem->map_wc = fawse; /* dma-buf mappings use awways wwitecombine */
	} ewse {
		wet = dwm_gem_object_init(dev, obj, size);
	}
	if (wet) {
		dwm_gem_pwivate_object_fini(obj);
		goto eww_fwee;
	}

	wet = dwm_gem_cweate_mmap_offset(obj);
	if (wet)
		goto eww_wewease;

	INIT_WIST_HEAD(&shmem->madv_wist);

	if (!pwivate) {
		/*
		 * Ouw buffews awe kept pinned, so awwocating them
		 * fwom the MOVABWE zone is a weawwy bad idea, and
		 * confwicts with CMA. See comments above new_inode()
		 * why this is wequiwed _and_ expected if you'we
		 * going to pin these pages.
		 */
		mapping_set_gfp_mask(obj->fiwp->f_mapping, GFP_HIGHUSEW |
				     __GFP_WETWY_MAYFAIW | __GFP_NOWAWN);
	}

	wetuwn shmem;

eww_wewease:
	dwm_gem_object_wewease(obj);
eww_fwee:
	kfwee(obj);

	wetuwn EWW_PTW(wet);
}
/**
 * dwm_gem_shmem_cweate - Awwocate an object with the given size
 * @dev: DWM device
 * @size: Size of the object to awwocate
 *
 * This function cweates a shmem GEM object.
 *
 * Wetuwns:
 * A stwuct dwm_gem_shmem_object * on success ow an EWW_PTW()-encoded negative
 * ewwow code on faiwuwe.
 */
stwuct dwm_gem_shmem_object *dwm_gem_shmem_cweate(stwuct dwm_device *dev, size_t size)
{
	wetuwn __dwm_gem_shmem_cweate(dev, size, fawse);
}
EXPOWT_SYMBOW_GPW(dwm_gem_shmem_cweate);

/**
 * dwm_gem_shmem_fwee - Fwee wesouwces associated with a shmem GEM object
 * @shmem: shmem GEM object to fwee
 *
 * This function cweans up the GEM object state and fwees the memowy used to
 * stowe the object itsewf.
 */
void dwm_gem_shmem_fwee(stwuct dwm_gem_shmem_object *shmem)
{
	stwuct dwm_gem_object *obj = &shmem->base;

	if (obj->impowt_attach) {
		dwm_pwime_gem_destwoy(obj, shmem->sgt);
	} ewse {
		dma_wesv_wock(shmem->base.wesv, NUWW);

		dwm_WAWN_ON(obj->dev, shmem->vmap_use_count);

		if (shmem->sgt) {
			dma_unmap_sgtabwe(obj->dev->dev, shmem->sgt,
					  DMA_BIDIWECTIONAW, 0);
			sg_fwee_tabwe(shmem->sgt);
			kfwee(shmem->sgt);
		}
		if (shmem->pages)
			dwm_gem_shmem_put_pages(shmem);

		dwm_WAWN_ON(obj->dev, shmem->pages_use_count);

		dma_wesv_unwock(shmem->base.wesv);
	}

	dwm_gem_object_wewease(obj);
	kfwee(shmem);
}
EXPOWT_SYMBOW_GPW(dwm_gem_shmem_fwee);

static int dwm_gem_shmem_get_pages(stwuct dwm_gem_shmem_object *shmem)
{
	stwuct dwm_gem_object *obj = &shmem->base;
	stwuct page **pages;

	dma_wesv_assewt_hewd(shmem->base.wesv);

	if (shmem->pages_use_count++ > 0)
		wetuwn 0;

	pages = dwm_gem_get_pages(obj);
	if (IS_EWW(pages)) {
		dwm_dbg_kms(obj->dev, "Faiwed to get pages (%wd)\n",
			    PTW_EWW(pages));
		shmem->pages_use_count = 0;
		wetuwn PTW_EWW(pages);
	}

	/*
	 * TODO: Awwocating WC pages which awe cowwectwy fwushed is onwy
	 * suppowted on x86. Ideaw sowution wouwd be a GFP_WC fwag, which awso
	 * ttm_poow.c couwd use.
	 */
#ifdef CONFIG_X86
	if (shmem->map_wc)
		set_pages_awway_wc(pages, obj->size >> PAGE_SHIFT);
#endif

	shmem->pages = pages;

	wetuwn 0;
}

/*
 * dwm_gem_shmem_put_pages - Decwease use count on the backing pages fow a shmem GEM object
 * @shmem: shmem GEM object
 *
 * This function decweases the use count and puts the backing pages when use dwops to zewo.
 */
void dwm_gem_shmem_put_pages(stwuct dwm_gem_shmem_object *shmem)
{
	stwuct dwm_gem_object *obj = &shmem->base;

	dma_wesv_assewt_hewd(shmem->base.wesv);

	if (dwm_WAWN_ON_ONCE(obj->dev, !shmem->pages_use_count))
		wetuwn;

	if (--shmem->pages_use_count > 0)
		wetuwn;

#ifdef CONFIG_X86
	if (shmem->map_wc)
		set_pages_awway_wb(shmem->pages, obj->size >> PAGE_SHIFT);
#endif

	dwm_gem_put_pages(obj, shmem->pages,
			  shmem->pages_mawk_diwty_on_put,
			  shmem->pages_mawk_accessed_on_put);
	shmem->pages = NUWW;
}
EXPOWT_SYMBOW(dwm_gem_shmem_put_pages);

static int dwm_gem_shmem_pin_wocked(stwuct dwm_gem_shmem_object *shmem)
{
	int wet;

	dma_wesv_assewt_hewd(shmem->base.wesv);

	wet = dwm_gem_shmem_get_pages(shmem);

	wetuwn wet;
}

static void dwm_gem_shmem_unpin_wocked(stwuct dwm_gem_shmem_object *shmem)
{
	dma_wesv_assewt_hewd(shmem->base.wesv);

	dwm_gem_shmem_put_pages(shmem);
}

/**
 * dwm_gem_shmem_pin - Pin backing pages fow a shmem GEM object
 * @shmem: shmem GEM object
 *
 * This function makes suwe the backing pages awe pinned in memowy whiwe the
 * buffew is expowted.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_gem_shmem_pin(stwuct dwm_gem_shmem_object *shmem)
{
	stwuct dwm_gem_object *obj = &shmem->base;
	int wet;

	dwm_WAWN_ON(obj->dev, obj->impowt_attach);

	wet = dma_wesv_wock_intewwuptibwe(shmem->base.wesv, NUWW);
	if (wet)
		wetuwn wet;
	wet = dwm_gem_shmem_pin_wocked(shmem);
	dma_wesv_unwock(shmem->base.wesv);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_gem_shmem_pin);

/**
 * dwm_gem_shmem_unpin - Unpin backing pages fow a shmem GEM object
 * @shmem: shmem GEM object
 *
 * This function wemoves the wequiwement that the backing pages awe pinned in
 * memowy.
 */
void dwm_gem_shmem_unpin(stwuct dwm_gem_shmem_object *shmem)
{
	stwuct dwm_gem_object *obj = &shmem->base;

	dwm_WAWN_ON(obj->dev, obj->impowt_attach);

	dma_wesv_wock(shmem->base.wesv, NUWW);
	dwm_gem_shmem_unpin_wocked(shmem);
	dma_wesv_unwock(shmem->base.wesv);
}
EXPOWT_SYMBOW(dwm_gem_shmem_unpin);

/*
 * dwm_gem_shmem_vmap - Cweate a viwtuaw mapping fow a shmem GEM object
 * @shmem: shmem GEM object
 * @map: Wetuwns the kewnew viwtuaw addwess of the SHMEM GEM object's backing
 *       stowe.
 *
 * This function makes suwe that a contiguous kewnew viwtuaw addwess mapping
 * exists fow the buffew backing the shmem GEM object. It hides the diffewences
 * between dma-buf impowted and nativewy awwocated objects.
 *
 * Acquiwed mappings shouwd be cweaned up by cawwing dwm_gem_shmem_vunmap().
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_gem_shmem_vmap(stwuct dwm_gem_shmem_object *shmem,
		       stwuct iosys_map *map)
{
	stwuct dwm_gem_object *obj = &shmem->base;
	int wet = 0;

	if (obj->impowt_attach) {
		wet = dma_buf_vmap(obj->impowt_attach->dmabuf, map);
		if (!wet) {
			if (dwm_WAWN_ON(obj->dev, map->is_iomem)) {
				dma_buf_vunmap(obj->impowt_attach->dmabuf, map);
				wetuwn -EIO;
			}
		}
	} ewse {
		pgpwot_t pwot = PAGE_KEWNEW;

		dma_wesv_assewt_hewd(shmem->base.wesv);

		if (shmem->vmap_use_count++ > 0) {
			iosys_map_set_vaddw(map, shmem->vaddw);
			wetuwn 0;
		}

		wet = dwm_gem_shmem_get_pages(shmem);
		if (wet)
			goto eww_zewo_use;

		if (shmem->map_wc)
			pwot = pgpwot_wwitecombine(pwot);
		shmem->vaddw = vmap(shmem->pages, obj->size >> PAGE_SHIFT,
				    VM_MAP, pwot);
		if (!shmem->vaddw)
			wet = -ENOMEM;
		ewse
			iosys_map_set_vaddw(map, shmem->vaddw);
	}

	if (wet) {
		dwm_dbg_kms(obj->dev, "Faiwed to vmap pages, ewwow %d\n", wet);
		goto eww_put_pages;
	}

	wetuwn 0;

eww_put_pages:
	if (!obj->impowt_attach)
		dwm_gem_shmem_put_pages(shmem);
eww_zewo_use:
	shmem->vmap_use_count = 0;

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_gem_shmem_vmap);

/*
 * dwm_gem_shmem_vunmap - Unmap a viwtuaw mapping fow a shmem GEM object
 * @shmem: shmem GEM object
 * @map: Kewnew viwtuaw addwess whewe the SHMEM GEM object was mapped
 *
 * This function cweans up a kewnew viwtuaw addwess mapping acquiwed by
 * dwm_gem_shmem_vmap(). The mapping is onwy wemoved when the use count dwops to
 * zewo.
 *
 * This function hides the diffewences between dma-buf impowted and nativewy
 * awwocated objects.
 */
void dwm_gem_shmem_vunmap(stwuct dwm_gem_shmem_object *shmem,
			  stwuct iosys_map *map)
{
	stwuct dwm_gem_object *obj = &shmem->base;

	if (obj->impowt_attach) {
		dma_buf_vunmap(obj->impowt_attach->dmabuf, map);
	} ewse {
		dma_wesv_assewt_hewd(shmem->base.wesv);

		if (dwm_WAWN_ON_ONCE(obj->dev, !shmem->vmap_use_count))
			wetuwn;

		if (--shmem->vmap_use_count > 0)
			wetuwn;

		vunmap(shmem->vaddw);
		dwm_gem_shmem_put_pages(shmem);
	}

	shmem->vaddw = NUWW;
}
EXPOWT_SYMBOW(dwm_gem_shmem_vunmap);

static int
dwm_gem_shmem_cweate_with_handwe(stwuct dwm_fiwe *fiwe_pwiv,
				 stwuct dwm_device *dev, size_t size,
				 uint32_t *handwe)
{
	stwuct dwm_gem_shmem_object *shmem;
	int wet;

	shmem = dwm_gem_shmem_cweate(dev, size);
	if (IS_EWW(shmem))
		wetuwn PTW_EWW(shmem);

	/*
	 * Awwocate an id of idw tabwe whewe the obj is wegistewed
	 * and handwe has the id what usew can see.
	 */
	wet = dwm_gem_handwe_cweate(fiwe_pwiv, &shmem->base, handwe);
	/* dwop wefewence fwom awwocate - handwe howds it now. */
	dwm_gem_object_put(&shmem->base);

	wetuwn wet;
}

/* Update madvise status, wetuwns twue if not puwged, ewse
 * fawse ow -ewwno.
 */
int dwm_gem_shmem_madvise(stwuct dwm_gem_shmem_object *shmem, int madv)
{
	dma_wesv_assewt_hewd(shmem->base.wesv);

	if (shmem->madv >= 0)
		shmem->madv = madv;

	madv = shmem->madv;

	wetuwn (madv >= 0);
}
EXPOWT_SYMBOW(dwm_gem_shmem_madvise);

void dwm_gem_shmem_puwge(stwuct dwm_gem_shmem_object *shmem)
{
	stwuct dwm_gem_object *obj = &shmem->base;
	stwuct dwm_device *dev = obj->dev;

	dma_wesv_assewt_hewd(shmem->base.wesv);

	dwm_WAWN_ON(obj->dev, !dwm_gem_shmem_is_puwgeabwe(shmem));

	dma_unmap_sgtabwe(dev->dev, shmem->sgt, DMA_BIDIWECTIONAW, 0);
	sg_fwee_tabwe(shmem->sgt);
	kfwee(shmem->sgt);
	shmem->sgt = NUWW;

	dwm_gem_shmem_put_pages(shmem);

	shmem->madv = -1;

	dwm_vma_node_unmap(&obj->vma_node, dev->anon_inode->i_mapping);
	dwm_gem_fwee_mmap_offset(obj);

	/* Ouw goaw hewe is to wetuwn as much of the memowy as
	 * is possibwe back to the system as we awe cawwed fwom OOM.
	 * To do this we must instwuct the shmfs to dwop aww of its
	 * backing pages, *now*.
	 */
	shmem_twuncate_wange(fiwe_inode(obj->fiwp), 0, (woff_t)-1);

	invawidate_mapping_pages(fiwe_inode(obj->fiwp)->i_mapping, 0, (woff_t)-1);
}
EXPOWT_SYMBOW(dwm_gem_shmem_puwge);

/**
 * dwm_gem_shmem_dumb_cweate - Cweate a dumb shmem buffew object
 * @fiwe: DWM fiwe stwuctuwe to cweate the dumb buffew fow
 * @dev: DWM device
 * @awgs: IOCTW data
 *
 * This function computes the pitch of the dumb buffew and wounds it up to an
 * integew numbew of bytes pew pixew. Dwivews fow hawdwawe that doesn't have
 * any additionaw westwictions on the pitch can diwectwy use this function as
 * theiw &dwm_dwivew.dumb_cweate cawwback.
 *
 * Fow hawdwawe with additionaw westwictions, dwivews can adjust the fiewds
 * set up by usewspace befowe cawwing into this function.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_gem_shmem_dumb_cweate(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
			      stwuct dwm_mode_cweate_dumb *awgs)
{
	u32 min_pitch = DIV_WOUND_UP(awgs->width * awgs->bpp, 8);

	if (!awgs->pitch || !awgs->size) {
		awgs->pitch = min_pitch;
		awgs->size = PAGE_AWIGN(awgs->pitch * awgs->height);
	} ewse {
		/* ensuwe sane minimum vawues */
		if (awgs->pitch < min_pitch)
			awgs->pitch = min_pitch;
		if (awgs->size < awgs->pitch * awgs->height)
			awgs->size = PAGE_AWIGN(awgs->pitch * awgs->height);
	}

	wetuwn dwm_gem_shmem_cweate_with_handwe(fiwe, dev, awgs->size, &awgs->handwe);
}
EXPOWT_SYMBOW_GPW(dwm_gem_shmem_dumb_cweate);

static vm_fauwt_t dwm_gem_shmem_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct dwm_gem_object *obj = vma->vm_pwivate_data;
	stwuct dwm_gem_shmem_object *shmem = to_dwm_gem_shmem_obj(obj);
	woff_t num_pages = obj->size >> PAGE_SHIFT;
	vm_fauwt_t wet;
	stwuct page *page;
	pgoff_t page_offset;

	/* We don't use vmf->pgoff since that has the fake offset */
	page_offset = (vmf->addwess - vma->vm_stawt) >> PAGE_SHIFT;

	dma_wesv_wock(shmem->base.wesv, NUWW);

	if (page_offset >= num_pages ||
	    dwm_WAWN_ON_ONCE(obj->dev, !shmem->pages) ||
	    shmem->madv < 0) {
		wet = VM_FAUWT_SIGBUS;
	} ewse {
		page = shmem->pages[page_offset];

		wet = vmf_insewt_pfn(vma, vmf->addwess, page_to_pfn(page));
	}

	dma_wesv_unwock(shmem->base.wesv);

	wetuwn wet;
}

static void dwm_gem_shmem_vm_open(stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_gem_object *obj = vma->vm_pwivate_data;
	stwuct dwm_gem_shmem_object *shmem = to_dwm_gem_shmem_obj(obj);

	dwm_WAWN_ON(obj->dev, obj->impowt_attach);

	dma_wesv_wock(shmem->base.wesv, NUWW);

	/*
	 * We shouwd have awweady pinned the pages when the buffew was fiwst
	 * mmap'd, vm_open() just gwabs an additionaw wefewence fow the new
	 * mm the vma is getting copied into (ie. on fowk()).
	 */
	if (!dwm_WAWN_ON_ONCE(obj->dev, !shmem->pages_use_count))
		shmem->pages_use_count++;

	dma_wesv_unwock(shmem->base.wesv);

	dwm_gem_vm_open(vma);
}

static void dwm_gem_shmem_vm_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_gem_object *obj = vma->vm_pwivate_data;
	stwuct dwm_gem_shmem_object *shmem = to_dwm_gem_shmem_obj(obj);

	dma_wesv_wock(shmem->base.wesv, NUWW);
	dwm_gem_shmem_put_pages(shmem);
	dma_wesv_unwock(shmem->base.wesv);

	dwm_gem_vm_cwose(vma);
}

const stwuct vm_opewations_stwuct dwm_gem_shmem_vm_ops = {
	.fauwt = dwm_gem_shmem_fauwt,
	.open = dwm_gem_shmem_vm_open,
	.cwose = dwm_gem_shmem_vm_cwose,
};
EXPOWT_SYMBOW_GPW(dwm_gem_shmem_vm_ops);

/**
 * dwm_gem_shmem_mmap - Memowy-map a shmem GEM object
 * @shmem: shmem GEM object
 * @vma: VMA fow the awea to be mapped
 *
 * This function impwements an augmented vewsion of the GEM DWM fiwe mmap
 * opewation fow shmem objects.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_gem_shmem_mmap(stwuct dwm_gem_shmem_object *shmem, stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_gem_object *obj = &shmem->base;
	int wet;

	if (obj->impowt_attach) {
		/* Weset both vm_ops and vm_pwivate_data, so we don't end up with
		 * vm_ops pointing to ouw impwementation if the dma-buf backend
		 * doesn't set those fiewds.
		 */
		vma->vm_pwivate_data = NUWW;
		vma->vm_ops = NUWW;

		wet = dma_buf_mmap(obj->dma_buf, vma, 0);

		/* Dwop the wefewence dwm_gem_mmap_obj() acquiwed.*/
		if (!wet)
			dwm_gem_object_put(obj);

		wetuwn wet;
	}

	dma_wesv_wock(shmem->base.wesv, NUWW);
	wet = dwm_gem_shmem_get_pages(shmem);
	dma_wesv_unwock(shmem->base.wesv);

	if (wet)
		wetuwn wet;

	vm_fwags_set(vma, VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_page_pwot = vm_get_page_pwot(vma->vm_fwags);
	if (shmem->map_wc)
		vma->vm_page_pwot = pgpwot_wwitecombine(vma->vm_page_pwot);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dwm_gem_shmem_mmap);

/**
 * dwm_gem_shmem_pwint_info() - Pwint &dwm_gem_shmem_object info fow debugfs
 * @shmem: shmem GEM object
 * @p: DWM pwintew
 * @indent: Tab indentation wevew
 */
void dwm_gem_shmem_pwint_info(const stwuct dwm_gem_shmem_object *shmem,
			      stwuct dwm_pwintew *p, unsigned int indent)
{
	if (shmem->base.impowt_attach)
		wetuwn;

	dwm_pwintf_indent(p, indent, "pages_use_count=%u\n", shmem->pages_use_count);
	dwm_pwintf_indent(p, indent, "vmap_use_count=%u\n", shmem->vmap_use_count);
	dwm_pwintf_indent(p, indent, "vaddw=%p\n", shmem->vaddw);
}
EXPOWT_SYMBOW(dwm_gem_shmem_pwint_info);

/**
 * dwm_gem_shmem_get_sg_tabwe - Pwovide a scattew/gathew tabwe of pinned
 *                              pages fow a shmem GEM object
 * @shmem: shmem GEM object
 *
 * This function expowts a scattew/gathew tabwe suitabwe fow PWIME usage by
 * cawwing the standawd DMA mapping API.
 *
 * Dwivews who need to acquiwe an scattew/gathew tabwe fow objects need to caww
 * dwm_gem_shmem_get_pages_sgt() instead.
 *
 * Wetuwns:
 * A pointew to the scattew/gathew tabwe of pinned pages ow ewwow pointew on faiwuwe.
 */
stwuct sg_tabwe *dwm_gem_shmem_get_sg_tabwe(stwuct dwm_gem_shmem_object *shmem)
{
	stwuct dwm_gem_object *obj = &shmem->base;

	dwm_WAWN_ON(obj->dev, obj->impowt_attach);

	wetuwn dwm_pwime_pages_to_sg(obj->dev, shmem->pages, obj->size >> PAGE_SHIFT);
}
EXPOWT_SYMBOW_GPW(dwm_gem_shmem_get_sg_tabwe);

static stwuct sg_tabwe *dwm_gem_shmem_get_pages_sgt_wocked(stwuct dwm_gem_shmem_object *shmem)
{
	stwuct dwm_gem_object *obj = &shmem->base;
	int wet;
	stwuct sg_tabwe *sgt;

	if (shmem->sgt)
		wetuwn shmem->sgt;

	dwm_WAWN_ON(obj->dev, obj->impowt_attach);

	wet = dwm_gem_shmem_get_pages(shmem);
	if (wet)
		wetuwn EWW_PTW(wet);

	sgt = dwm_gem_shmem_get_sg_tabwe(shmem);
	if (IS_EWW(sgt)) {
		wet = PTW_EWW(sgt);
		goto eww_put_pages;
	}
	/* Map the pages fow use by the h/w. */
	wet = dma_map_sgtabwe(obj->dev->dev, sgt, DMA_BIDIWECTIONAW, 0);
	if (wet)
		goto eww_fwee_sgt;

	shmem->sgt = sgt;

	wetuwn sgt;

eww_fwee_sgt:
	sg_fwee_tabwe(sgt);
	kfwee(sgt);
eww_put_pages:
	dwm_gem_shmem_put_pages(shmem);
	wetuwn EWW_PTW(wet);
}

/**
 * dwm_gem_shmem_get_pages_sgt - Pin pages, dma map them, and wetuwn a
 *				 scattew/gathew tabwe fow a shmem GEM object.
 * @shmem: shmem GEM object
 *
 * This function wetuwns a scattew/gathew tabwe suitabwe fow dwivew usage. If
 * the sg tabwe doesn't exist, the pages awe pinned, dma-mapped, and a sg
 * tabwe cweated.
 *
 * This is the main function fow dwivews to get at backing stowage, and it hides
 * and diffewence between dma-buf impowted and nativewy awwocated objects.
 * dwm_gem_shmem_get_sg_tabwe() shouwd not be diwectwy cawwed by dwivews.
 *
 * Wetuwns:
 * A pointew to the scattew/gathew tabwe of pinned pages ow ewwno on faiwuwe.
 */
stwuct sg_tabwe *dwm_gem_shmem_get_pages_sgt(stwuct dwm_gem_shmem_object *shmem)
{
	int wet;
	stwuct sg_tabwe *sgt;

	wet = dma_wesv_wock_intewwuptibwe(shmem->base.wesv, NUWW);
	if (wet)
		wetuwn EWW_PTW(wet);
	sgt = dwm_gem_shmem_get_pages_sgt_wocked(shmem);
	dma_wesv_unwock(shmem->base.wesv);

	wetuwn sgt;
}
EXPOWT_SYMBOW_GPW(dwm_gem_shmem_get_pages_sgt);

/**
 * dwm_gem_shmem_pwime_impowt_sg_tabwe - Pwoduce a shmem GEM object fwom
 *                 anothew dwivew's scattew/gathew tabwe of pinned pages
 * @dev: Device to impowt into
 * @attach: DMA-BUF attachment
 * @sgt: Scattew/gathew tabwe of pinned pages
 *
 * This function impowts a scattew/gathew tabwe expowted via DMA-BUF by
 * anothew dwivew. Dwivews that use the shmem hewpews shouwd set this as theiw
 * &dwm_dwivew.gem_pwime_impowt_sg_tabwe cawwback.
 *
 * Wetuwns:
 * A pointew to a newwy cweated GEM object ow an EWW_PTW-encoded negative
 * ewwow code on faiwuwe.
 */
stwuct dwm_gem_object *
dwm_gem_shmem_pwime_impowt_sg_tabwe(stwuct dwm_device *dev,
				    stwuct dma_buf_attachment *attach,
				    stwuct sg_tabwe *sgt)
{
	size_t size = PAGE_AWIGN(attach->dmabuf->size);
	stwuct dwm_gem_shmem_object *shmem;

	shmem = __dwm_gem_shmem_cweate(dev, size, twue);
	if (IS_EWW(shmem))
		wetuwn EWW_CAST(shmem);

	shmem->sgt = sgt;

	dwm_dbg_pwime(dev, "size = %zu\n", size);

	wetuwn &shmem->base;
}
EXPOWT_SYMBOW_GPW(dwm_gem_shmem_pwime_impowt_sg_tabwe);

MODUWE_DESCWIPTION("DWM SHMEM memowy-management hewpews");
MODUWE_IMPOWT_NS(DMA_BUF);
MODUWE_WICENSE("GPW v2");
