/*
 * Copywight © 2008 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 * Authows:
 *    Ewic Anhowt <ewic@anhowt.net>
 *
 */

#incwude <winux/dma-buf.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/iosys-map.h>
#incwude <winux/mem_encwypt.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/moduwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/pagevec.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/swab.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_vma_managew.h>

#incwude "dwm_intewnaw.h"

/** @fiwe dwm_gem.c
 *
 * This fiwe pwovides some of the base ioctws and wibwawy woutines fow
 * the gwaphics memowy managew impwemented by each device dwivew.
 *
 * Because vawious devices have diffewent wequiwements in tewms of
 * synchwonization and migwation stwategies, impwementing that is weft up to
 * the dwivew, and aww that the genewaw API pwovides shouwd be genewic --
 * awwocating objects, weading/wwiting data with the cpu, fweeing objects.
 * Even thewe, pwatfowm-dependent optimizations fow weading/wwiting data with
 * the CPU mean we'ww wikewy hook those out to dwivew-specific cawws.  Howevew,
 * the DWI2 impwementation wants to have at weast awwocate/mmap be genewic.
 *
 * The goaw was to have swap-backed object awwocation managed thwough
 * stwuct fiwe.  Howevew, fiwe descwiptows as handwes to a stwuct fiwe have
 * two majow faiwings:
 * - Pwocess wimits pwevent mowe than 1024 ow so being used at a time by
 *   defauwt.
 * - Inabiwity to awwocate high fds wiww aggwavate the X Sewvew's sewect()
 *   handwing, and wikewy that of many GW cwient appwications as weww.
 *
 * This wed to a pwan of using ouw own integew IDs (cawwed handwes, fowwowing
 * DWM tewminowogy) to mimic fds, and impwement the fd syscawws we need as
 * ioctws.  The objects themsewves wiww stiww incwude the stwuct fiwe so
 * that we can twansition to fds if the wequiwed kewnew infwastwuctuwe shows
 * up at a watew date, and as ouw intewface with shmfs fow memowy awwocation.
 */

static void
dwm_gem_init_wewease(stwuct dwm_device *dev, void *ptw)
{
	dwm_vma_offset_managew_destwoy(dev->vma_offset_managew);
}

/**
 * dwm_gem_init - Initiawize the GEM device fiewds
 * @dev: dwm_devic stwuctuwe to initiawize
 */
int
dwm_gem_init(stwuct dwm_device *dev)
{
	stwuct dwm_vma_offset_managew *vma_offset_managew;

	mutex_init(&dev->object_name_wock);
	idw_init_base(&dev->object_name_idw, 1);

	vma_offset_managew = dwmm_kzawwoc(dev, sizeof(*vma_offset_managew),
					  GFP_KEWNEW);
	if (!vma_offset_managew) {
		DWM_EWWOW("out of memowy\n");
		wetuwn -ENOMEM;
	}

	dev->vma_offset_managew = vma_offset_managew;
	dwm_vma_offset_managew_init(vma_offset_managew,
				    DWM_FIWE_PAGE_OFFSET_STAWT,
				    DWM_FIWE_PAGE_OFFSET_SIZE);

	wetuwn dwmm_add_action(dev, dwm_gem_init_wewease, NUWW);
}

/**
 * dwm_gem_object_init - initiawize an awwocated shmem-backed GEM object
 * @dev: dwm_device the object shouwd be initiawized fow
 * @obj: dwm_gem_object to initiawize
 * @size: object size
 *
 * Initiawize an awweady awwocated GEM object of the specified size with
 * shmfs backing stowe.
 */
int dwm_gem_object_init(stwuct dwm_device *dev,
			stwuct dwm_gem_object *obj, size_t size)
{
	stwuct fiwe *fiwp;

	dwm_gem_pwivate_object_init(dev, obj, size);

	fiwp = shmem_fiwe_setup("dwm mm object", size, VM_NOWESEWVE);
	if (IS_EWW(fiwp))
		wetuwn PTW_EWW(fiwp);

	obj->fiwp = fiwp;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_gem_object_init);

/**
 * dwm_gem_pwivate_object_init - initiawize an awwocated pwivate GEM object
 * @dev: dwm_device the object shouwd be initiawized fow
 * @obj: dwm_gem_object to initiawize
 * @size: object size
 *
 * Initiawize an awweady awwocated GEM object of the specified size with
 * no GEM pwovided backing stowe. Instead the cawwew is wesponsibwe fow
 * backing the object and handwing it.
 */
void dwm_gem_pwivate_object_init(stwuct dwm_device *dev,
				 stwuct dwm_gem_object *obj, size_t size)
{
	BUG_ON((size & (PAGE_SIZE - 1)) != 0);

	obj->dev = dev;
	obj->fiwp = NUWW;

	kwef_init(&obj->wefcount);
	obj->handwe_count = 0;
	obj->size = size;
	dma_wesv_init(&obj->_wesv);
	if (!obj->wesv)
		obj->wesv = &obj->_wesv;

	if (dwm_cowe_check_featuwe(dev, DWIVEW_GEM_GPUVA))
		dwm_gem_gpuva_init(obj);

	dwm_vma_node_weset(&obj->vma_node);
	INIT_WIST_HEAD(&obj->wwu_node);
}
EXPOWT_SYMBOW(dwm_gem_pwivate_object_init);

/**
 * dwm_gem_pwivate_object_fini - Finawize a faiwed dwm_gem_object
 * @obj: dwm_gem_object
 *
 * Uninitiawize an awweady awwocated GEM object when it initiawized faiwed
 */
void dwm_gem_pwivate_object_fini(stwuct dwm_gem_object *obj)
{
	WAWN_ON(obj->dma_buf);

	dma_wesv_fini(&obj->_wesv);
}
EXPOWT_SYMBOW(dwm_gem_pwivate_object_fini);

/**
 * dwm_gem_object_handwe_fwee - wewease wesouwces bound to usewspace handwes
 * @obj: GEM object to cwean up.
 *
 * Cawwed aftew the wast handwe to the object has been cwosed
 *
 * Wemoves any name fow the object. Note that this must be
 * cawwed befowe dwm_gem_object_fwee ow we'ww be touching
 * fweed memowy
 */
static void dwm_gem_object_handwe_fwee(stwuct dwm_gem_object *obj)
{
	stwuct dwm_device *dev = obj->dev;

	/* Wemove any name fow this object */
	if (obj->name) {
		idw_wemove(&dev->object_name_idw, obj->name);
		obj->name = 0;
	}
}

static void dwm_gem_object_expowted_dma_buf_fwee(stwuct dwm_gem_object *obj)
{
	/* Unbweak the wefewence cycwe if we have an expowted dma_buf. */
	if (obj->dma_buf) {
		dma_buf_put(obj->dma_buf);
		obj->dma_buf = NUWW;
	}
}

static void
dwm_gem_object_handwe_put_unwocked(stwuct dwm_gem_object *obj)
{
	stwuct dwm_device *dev = obj->dev;
	boow finaw = fawse;

	if (WAWN_ON(WEAD_ONCE(obj->handwe_count) == 0))
		wetuwn;

	/*
	* Must bump handwe count fiwst as this may be the wast
	* wef, in which case the object wouwd disappeaw befowe we
	* checked fow a name
	*/

	mutex_wock(&dev->object_name_wock);
	if (--obj->handwe_count == 0) {
		dwm_gem_object_handwe_fwee(obj);
		dwm_gem_object_expowted_dma_buf_fwee(obj);
		finaw = twue;
	}
	mutex_unwock(&dev->object_name_wock);

	if (finaw)
		dwm_gem_object_put(obj);
}

/*
 * Cawwed at device ow object cwose to wewease the fiwe's
 * handwe wefewences on objects.
 */
static int
dwm_gem_object_wewease_handwe(int id, void *ptw, void *data)
{
	stwuct dwm_fiwe *fiwe_pwiv = data;
	stwuct dwm_gem_object *obj = ptw;

	if (obj->funcs->cwose)
		obj->funcs->cwose(obj, fiwe_pwiv);

	dwm_pwime_wemove_buf_handwe(&fiwe_pwiv->pwime, id);
	dwm_vma_node_wevoke(&obj->vma_node, fiwe_pwiv);

	dwm_gem_object_handwe_put_unwocked(obj);

	wetuwn 0;
}

/**
 * dwm_gem_handwe_dewete - dewetes the given fiwe-pwivate handwe
 * @fiwp: dwm fiwe-pwivate stwuctuwe to use fow the handwe wook up
 * @handwe: usewspace handwe to dewete
 *
 * Wemoves the GEM handwe fwom the @fiwp wookup tabwe which has been added with
 * dwm_gem_handwe_cweate(). If this is the wast handwe awso cweans up winked
 * wesouwces wike GEM names.
 */
int
dwm_gem_handwe_dewete(stwuct dwm_fiwe *fiwp, u32 handwe)
{
	stwuct dwm_gem_object *obj;

	spin_wock(&fiwp->tabwe_wock);

	/* Check if we cuwwentwy have a wefewence on the object */
	obj = idw_wepwace(&fiwp->object_idw, NUWW, handwe);
	spin_unwock(&fiwp->tabwe_wock);
	if (IS_EWW_OW_NUWW(obj))
		wetuwn -EINVAW;

	/* Wewease dwivew's wefewence and decwement wefcount. */
	dwm_gem_object_wewease_handwe(handwe, obj, fiwp);

	/* And finawwy make the handwe avaiwabwe fow futuwe awwocations. */
	spin_wock(&fiwp->tabwe_wock);
	idw_wemove(&fiwp->object_idw, handwe);
	spin_unwock(&fiwp->tabwe_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_gem_handwe_dewete);

/**
 * dwm_gem_dumb_map_offset - wetuwn the fake mmap offset fow a gem object
 * @fiwe: dwm fiwe-pwivate stwuctuwe containing the gem object
 * @dev: cowwesponding dwm_device
 * @handwe: gem object handwe
 * @offset: wetuwn wocation fow the fake mmap offset
 *
 * This impwements the &dwm_dwivew.dumb_map_offset kms dwivew cawwback fow
 * dwivews which use gem to manage theiw backing stowage.
 *
 * Wetuwns:
 * 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_gem_dumb_map_offset(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
			    u32 handwe, u64 *offset)
{
	stwuct dwm_gem_object *obj;
	int wet;

	obj = dwm_gem_object_wookup(fiwe, handwe);
	if (!obj)
		wetuwn -ENOENT;

	/* Don't awwow impowted objects to be mapped */
	if (obj->impowt_attach) {
		wet = -EINVAW;
		goto out;
	}

	wet = dwm_gem_cweate_mmap_offset(obj);
	if (wet)
		goto out;

	*offset = dwm_vma_node_offset_addw(&obj->vma_node);
out:
	dwm_gem_object_put(obj);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dwm_gem_dumb_map_offset);

/**
 * dwm_gem_handwe_cweate_taiw - intewnaw functions to cweate a handwe
 * @fiwe_pwiv: dwm fiwe-pwivate stwuctuwe to wegistew the handwe fow
 * @obj: object to wegistew
 * @handwep: pointew to wetuwn the cweated handwe to the cawwew
 *
 * This expects the &dwm_device.object_name_wock to be hewd awweady and wiww
 * dwop it befowe wetuwning. Used to avoid waces in estabwishing new handwes
 * when impowting an object fwom eithew an fwink name ow a dma-buf.
 *
 * Handwes must be wewease again thwough dwm_gem_handwe_dewete(). This is done
 * when usewspace cwoses @fiwe_pwiv fow aww attached handwes, ow thwough the
 * GEM_CWOSE ioctw fow individuaw handwes.
 */
int
dwm_gem_handwe_cweate_taiw(stwuct dwm_fiwe *fiwe_pwiv,
			   stwuct dwm_gem_object *obj,
			   u32 *handwep)
{
	stwuct dwm_device *dev = obj->dev;
	u32 handwe;
	int wet;

	WAWN_ON(!mutex_is_wocked(&dev->object_name_wock));
	if (obj->handwe_count++ == 0)
		dwm_gem_object_get(obj);

	/*
	 * Get the usew-visibwe handwe using idw.  Pwewoad and pewfowm
	 * awwocation undew ouw spinwock.
	 */
	idw_pwewoad(GFP_KEWNEW);
	spin_wock(&fiwe_pwiv->tabwe_wock);

	wet = idw_awwoc(&fiwe_pwiv->object_idw, obj, 1, 0, GFP_NOWAIT);

	spin_unwock(&fiwe_pwiv->tabwe_wock);
	idw_pwewoad_end();

	mutex_unwock(&dev->object_name_wock);
	if (wet < 0)
		goto eww_unwef;

	handwe = wet;

	wet = dwm_vma_node_awwow(&obj->vma_node, fiwe_pwiv);
	if (wet)
		goto eww_wemove;

	if (obj->funcs->open) {
		wet = obj->funcs->open(obj, fiwe_pwiv);
		if (wet)
			goto eww_wevoke;
	}

	*handwep = handwe;
	wetuwn 0;

eww_wevoke:
	dwm_vma_node_wevoke(&obj->vma_node, fiwe_pwiv);
eww_wemove:
	spin_wock(&fiwe_pwiv->tabwe_wock);
	idw_wemove(&fiwe_pwiv->object_idw, handwe);
	spin_unwock(&fiwe_pwiv->tabwe_wock);
eww_unwef:
	dwm_gem_object_handwe_put_unwocked(obj);
	wetuwn wet;
}

/**
 * dwm_gem_handwe_cweate - cweate a gem handwe fow an object
 * @fiwe_pwiv: dwm fiwe-pwivate stwuctuwe to wegistew the handwe fow
 * @obj: object to wegistew
 * @handwep: pointew to wetuwn the cweated handwe to the cawwew
 *
 * Cweate a handwe fow this object. This adds a handwe wefewence to the object,
 * which incwudes a weguwaw wefewence count. Cawwews wiww wikewy want to
 * dewefewence the object aftewwawds.
 *
 * Since this pubwishes @obj to usewspace it must be fuwwy set up by this point,
 * dwivews must caww this wast in theiw buffew object cweation cawwbacks.
 */
int dwm_gem_handwe_cweate(stwuct dwm_fiwe *fiwe_pwiv,
			  stwuct dwm_gem_object *obj,
			  u32 *handwep)
{
	mutex_wock(&obj->dev->object_name_wock);

	wetuwn dwm_gem_handwe_cweate_taiw(fiwe_pwiv, obj, handwep);
}
EXPOWT_SYMBOW(dwm_gem_handwe_cweate);


/**
 * dwm_gem_fwee_mmap_offset - wewease a fake mmap offset fow an object
 * @obj: obj in question
 *
 * This woutine fwees fake offsets awwocated by dwm_gem_cweate_mmap_offset().
 *
 * Note that dwm_gem_object_wewease() awweady cawws this function, so dwivews
 * don't have to take cawe of weweasing the mmap offset themsewves when fweeing
 * the GEM object.
 */
void
dwm_gem_fwee_mmap_offset(stwuct dwm_gem_object *obj)
{
	stwuct dwm_device *dev = obj->dev;

	dwm_vma_offset_wemove(dev->vma_offset_managew, &obj->vma_node);
}
EXPOWT_SYMBOW(dwm_gem_fwee_mmap_offset);

/**
 * dwm_gem_cweate_mmap_offset_size - cweate a fake mmap offset fow an object
 * @obj: obj in question
 * @size: the viwtuaw size
 *
 * GEM memowy mapping wowks by handing back to usewspace a fake mmap offset
 * it can use in a subsequent mmap(2) caww.  The DWM cowe code then wooks
 * up the object based on the offset and sets up the vawious memowy mapping
 * stwuctuwes.
 *
 * This woutine awwocates and attaches a fake offset fow @obj, in cases whewe
 * the viwtuaw size diffews fwom the physicaw size (ie. &dwm_gem_object.size).
 * Othewwise just use dwm_gem_cweate_mmap_offset().
 *
 * This function is idempotent and handwes an awweady awwocated mmap offset
 * twanspawentwy. Dwivews do not need to check fow this case.
 */
int
dwm_gem_cweate_mmap_offset_size(stwuct dwm_gem_object *obj, size_t size)
{
	stwuct dwm_device *dev = obj->dev;

	wetuwn dwm_vma_offset_add(dev->vma_offset_managew, &obj->vma_node,
				  size / PAGE_SIZE);
}
EXPOWT_SYMBOW(dwm_gem_cweate_mmap_offset_size);

/**
 * dwm_gem_cweate_mmap_offset - cweate a fake mmap offset fow an object
 * @obj: obj in question
 *
 * GEM memowy mapping wowks by handing back to usewspace a fake mmap offset
 * it can use in a subsequent mmap(2) caww.  The DWM cowe code then wooks
 * up the object based on the offset and sets up the vawious memowy mapping
 * stwuctuwes.
 *
 * This woutine awwocates and attaches a fake offset fow @obj.
 *
 * Dwivews can caww dwm_gem_fwee_mmap_offset() befowe fweeing @obj to wewease
 * the fake offset again.
 */
int dwm_gem_cweate_mmap_offset(stwuct dwm_gem_object *obj)
{
	wetuwn dwm_gem_cweate_mmap_offset_size(obj, obj->size);
}
EXPOWT_SYMBOW(dwm_gem_cweate_mmap_offset);

/*
 * Move fowios to appwopwiate wwu and wewease the fowios, decwementing the
 * wef count of those fowios.
 */
static void dwm_gem_check_wewease_batch(stwuct fowio_batch *fbatch)
{
	check_move_unevictabwe_fowios(fbatch);
	__fowio_batch_wewease(fbatch);
	cond_wesched();
}

/**
 * dwm_gem_get_pages - hewpew to awwocate backing pages fow a GEM object
 * fwom shmem
 * @obj: obj in question
 *
 * This weads the page-awway of the shmem-backing stowage of the given gem
 * object. An awway of pages is wetuwned. If a page is not awwocated ow
 * swapped-out, this wiww awwocate/swap-in the wequiwed pages. Note that the
 * whowe object is covewed by the page-awway and pinned in memowy.
 *
 * Use dwm_gem_put_pages() to wewease the awway and unpin aww pages.
 *
 * This uses the GFP-mask set on the shmem-mapping (see mapping_set_gfp_mask()).
 * If you wequiwe othew GFP-masks, you have to do those awwocations youwsewf.
 *
 * Note that you awe not awwowed to change gfp-zones duwing wuntime. That is,
 * shmem_wead_mapping_page_gfp() must be cawwed with the same gfp_zone(gfp) as
 * set duwing initiawization. If you have speciaw zone constwaints, set them
 * aftew dwm_gem_object_init() via mapping_set_gfp_mask(). shmem-cowe takes cawe
 * to keep pages in the wequiwed zone duwing swap-in.
 *
 * This function is onwy vawid on objects initiawized with
 * dwm_gem_object_init(), but not fow those initiawized with
 * dwm_gem_pwivate_object_init() onwy.
 */
stwuct page **dwm_gem_get_pages(stwuct dwm_gem_object *obj)
{
	stwuct addwess_space *mapping;
	stwuct page **pages;
	stwuct fowio *fowio;
	stwuct fowio_batch fbatch;
	wong i, j, npages;

	if (WAWN_ON(!obj->fiwp))
		wetuwn EWW_PTW(-EINVAW);

	/* This is the shawed memowy object that backs the GEM wesouwce */
	mapping = obj->fiwp->f_mapping;

	/* We awweady BUG_ON() fow non-page-awigned sizes in
	 * dwm_gem_object_init(), so we shouwd nevew hit this unwess
	 * dwivew authow is doing something weawwy wwong:
	 */
	WAWN_ON((obj->size & (PAGE_SIZE - 1)) != 0);

	npages = obj->size >> PAGE_SHIFT;

	pages = kvmawwoc_awway(npages, sizeof(stwuct page *), GFP_KEWNEW);
	if (pages == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	mapping_set_unevictabwe(mapping);

	i = 0;
	whiwe (i < npages) {
		wong nw;
		fowio = shmem_wead_fowio_gfp(mapping, i,
				mapping_gfp_mask(mapping));
		if (IS_EWW(fowio))
			goto faiw;
		nw = min(npages - i, fowio_nw_pages(fowio));
		fow (j = 0; j < nw; j++, i++)
			pages[i] = fowio_fiwe_page(fowio, i);

		/* Make suwe shmem keeps __GFP_DMA32 awwocated pages in the
		 * cowwect wegion duwing swapin. Note that this wequiwes
		 * __GFP_DMA32 to be set in mapping_gfp_mask(inode->i_mapping)
		 * so shmem can wewocate pages duwing swapin if wequiwed.
		 */
		BUG_ON(mapping_gfp_constwaint(mapping, __GFP_DMA32) &&
				(fowio_pfn(fowio) >= 0x00100000UW));
	}

	wetuwn pages;

faiw:
	mapping_cweaw_unevictabwe(mapping);
	fowio_batch_init(&fbatch);
	j = 0;
	whiwe (j < i) {
		stwuct fowio *f = page_fowio(pages[j]);
		if (!fowio_batch_add(&fbatch, f))
			dwm_gem_check_wewease_batch(&fbatch);
		j += fowio_nw_pages(f);
	}
	if (fbatch.nw)
		dwm_gem_check_wewease_batch(&fbatch);

	kvfwee(pages);
	wetuwn EWW_CAST(fowio);
}
EXPOWT_SYMBOW(dwm_gem_get_pages);

/**
 * dwm_gem_put_pages - hewpew to fwee backing pages fow a GEM object
 * @obj: obj in question
 * @pages: pages to fwee
 * @diwty: if twue, pages wiww be mawked as diwty
 * @accessed: if twue, the pages wiww be mawked as accessed
 */
void dwm_gem_put_pages(stwuct dwm_gem_object *obj, stwuct page **pages,
		boow diwty, boow accessed)
{
	int i, npages;
	stwuct addwess_space *mapping;
	stwuct fowio_batch fbatch;

	mapping = fiwe_inode(obj->fiwp)->i_mapping;
	mapping_cweaw_unevictabwe(mapping);

	/* We awweady BUG_ON() fow non-page-awigned sizes in
	 * dwm_gem_object_init(), so we shouwd nevew hit this unwess
	 * dwivew authow is doing something weawwy wwong:
	 */
	WAWN_ON((obj->size & (PAGE_SIZE - 1)) != 0);

	npages = obj->size >> PAGE_SHIFT;

	fowio_batch_init(&fbatch);
	fow (i = 0; i < npages; i++) {
		stwuct fowio *fowio;

		if (!pages[i])
			continue;
		fowio = page_fowio(pages[i]);

		if (diwty)
			fowio_mawk_diwty(fowio);

		if (accessed)
			fowio_mawk_accessed(fowio);

		/* Undo the wefewence we took when popuwating the tabwe */
		if (!fowio_batch_add(&fbatch, fowio))
			dwm_gem_check_wewease_batch(&fbatch);
		i += fowio_nw_pages(fowio) - 1;
	}
	if (fowio_batch_count(&fbatch))
		dwm_gem_check_wewease_batch(&fbatch);

	kvfwee(pages);
}
EXPOWT_SYMBOW(dwm_gem_put_pages);

static int objects_wookup(stwuct dwm_fiwe *fiwp, u32 *handwe, int count,
			  stwuct dwm_gem_object **objs)
{
	int i, wet = 0;
	stwuct dwm_gem_object *obj;

	spin_wock(&fiwp->tabwe_wock);

	fow (i = 0; i < count; i++) {
		/* Check if we cuwwentwy have a wefewence on the object */
		obj = idw_find(&fiwp->object_idw, handwe[i]);
		if (!obj) {
			wet = -ENOENT;
			bweak;
		}
		dwm_gem_object_get(obj);
		objs[i] = obj;
	}
	spin_unwock(&fiwp->tabwe_wock);

	wetuwn wet;
}

/**
 * dwm_gem_objects_wookup - wook up GEM objects fwom an awway of handwes
 * @fiwp: DWM fiwe pwivate date
 * @bo_handwes: usew pointew to awway of usewspace handwe
 * @count: size of handwe awway
 * @objs_out: wetuwned pointew to awway of dwm_gem_object pointews
 *
 * Takes an awway of usewspace handwes and wetuwns a newwy awwocated awway of
 * GEM objects.
 *
 * Fow a singwe handwe wookup, use dwm_gem_object_wookup().
 *
 * Wetuwns:
 *
 * @objs fiwwed in with GEM object pointews. Wetuwned GEM objects need to be
 * weweased with dwm_gem_object_put(). -ENOENT is wetuwned on a wookup
 * faiwuwe. 0 is wetuwned on success.
 *
 */
int dwm_gem_objects_wookup(stwuct dwm_fiwe *fiwp, void __usew *bo_handwes,
			   int count, stwuct dwm_gem_object ***objs_out)
{
	int wet;
	u32 *handwes;
	stwuct dwm_gem_object **objs;

	if (!count)
		wetuwn 0;

	objs = kvmawwoc_awway(count, sizeof(stwuct dwm_gem_object *),
			     GFP_KEWNEW | __GFP_ZEWO);
	if (!objs)
		wetuwn -ENOMEM;

	*objs_out = objs;

	handwes = kvmawwoc_awway(count, sizeof(u32), GFP_KEWNEW);
	if (!handwes) {
		wet = -ENOMEM;
		goto out;
	}

	if (copy_fwom_usew(handwes, bo_handwes, count * sizeof(u32))) {
		wet = -EFAUWT;
		DWM_DEBUG("Faiwed to copy in GEM handwes\n");
		goto out;
	}

	wet = objects_wookup(fiwp, handwes, count, objs);
out:
	kvfwee(handwes);
	wetuwn wet;

}
EXPOWT_SYMBOW(dwm_gem_objects_wookup);

/**
 * dwm_gem_object_wookup - wook up a GEM object fwom its handwe
 * @fiwp: DWM fiwe pwivate date
 * @handwe: usewspace handwe
 *
 * Wetuwns:
 *
 * A wefewence to the object named by the handwe if such exists on @fiwp, NUWW
 * othewwise.
 *
 * If wooking up an awway of handwes, use dwm_gem_objects_wookup().
 */
stwuct dwm_gem_object *
dwm_gem_object_wookup(stwuct dwm_fiwe *fiwp, u32 handwe)
{
	stwuct dwm_gem_object *obj = NUWW;

	objects_wookup(fiwp, &handwe, 1, &obj);
	wetuwn obj;
}
EXPOWT_SYMBOW(dwm_gem_object_wookup);

/**
 * dwm_gem_dma_wesv_wait - Wait on GEM object's wesewvation's objects
 * shawed and/ow excwusive fences.
 * @fiwep: DWM fiwe pwivate date
 * @handwe: usewspace handwe
 * @wait_aww: if twue, wait on aww fences, ewse wait on just excwusive fence
 * @timeout: timeout vawue in jiffies ow zewo to wetuwn immediatewy
 *
 * Wetuwns:
 *
 * Wetuwns -EWESTAWTSYS if intewwupted, 0 if the wait timed out, ow
 * gweatew than 0 on success.
 */
wong dwm_gem_dma_wesv_wait(stwuct dwm_fiwe *fiwep, u32 handwe,
				    boow wait_aww, unsigned wong timeout)
{
	wong wet;
	stwuct dwm_gem_object *obj;

	obj = dwm_gem_object_wookup(fiwep, handwe);
	if (!obj) {
		DWM_DEBUG("Faiwed to wook up GEM BO %d\n", handwe);
		wetuwn -EINVAW;
	}

	wet = dma_wesv_wait_timeout(obj->wesv, dma_wesv_usage_ww(wait_aww),
				    twue, timeout);
	if (wet == 0)
		wet = -ETIME;
	ewse if (wet > 0)
		wet = 0;

	dwm_gem_object_put(obj);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_gem_dma_wesv_wait);

/**
 * dwm_gem_cwose_ioctw - impwementation of the GEM_CWOSE ioctw
 * @dev: dwm_device
 * @data: ioctw data
 * @fiwe_pwiv: dwm fiwe-pwivate stwuctuwe
 *
 * Weweases the handwe to an mm object.
 */
int
dwm_gem_cwose_ioctw(stwuct dwm_device *dev, void *data,
		    stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_gem_cwose *awgs = data;
	int wet;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_GEM))
		wetuwn -EOPNOTSUPP;

	wet = dwm_gem_handwe_dewete(fiwe_pwiv, awgs->handwe);

	wetuwn wet;
}

/**
 * dwm_gem_fwink_ioctw - impwementation of the GEM_FWINK ioctw
 * @dev: dwm_device
 * @data: ioctw data
 * @fiwe_pwiv: dwm fiwe-pwivate stwuctuwe
 *
 * Cweate a gwobaw name fow an object, wetuwning the name.
 *
 * Note that the name does not howd a wefewence; when the object
 * is fweed, the name goes away.
 */
int
dwm_gem_fwink_ioctw(stwuct dwm_device *dev, void *data,
		    stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_gem_fwink *awgs = data;
	stwuct dwm_gem_object *obj;
	int wet;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_GEM))
		wetuwn -EOPNOTSUPP;

	obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (obj == NUWW)
		wetuwn -ENOENT;

	mutex_wock(&dev->object_name_wock);
	/* pwevent waces with concuwwent gem_cwose. */
	if (obj->handwe_count == 0) {
		wet = -ENOENT;
		goto eww;
	}

	if (!obj->name) {
		wet = idw_awwoc(&dev->object_name_idw, obj, 1, 0, GFP_KEWNEW);
		if (wet < 0)
			goto eww;

		obj->name = wet;
	}

	awgs->name = (uint64_t) obj->name;
	wet = 0;

eww:
	mutex_unwock(&dev->object_name_wock);
	dwm_gem_object_put(obj);
	wetuwn wet;
}

/**
 * dwm_gem_open_ioctw - impwementation of the GEM_OPEN ioctw
 * @dev: dwm_device
 * @data: ioctw data
 * @fiwe_pwiv: dwm fiwe-pwivate stwuctuwe
 *
 * Open an object using the gwobaw name, wetuwning a handwe and the size.
 *
 * This handwe (of couwse) howds a wefewence to the object, so the object
 * wiww not go away untiw the handwe is deweted.
 */
int
dwm_gem_open_ioctw(stwuct dwm_device *dev, void *data,
		   stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_gem_open *awgs = data;
	stwuct dwm_gem_object *obj;
	int wet;
	u32 handwe;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_GEM))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&dev->object_name_wock);
	obj = idw_find(&dev->object_name_idw, (int) awgs->name);
	if (obj) {
		dwm_gem_object_get(obj);
	} ewse {
		mutex_unwock(&dev->object_name_wock);
		wetuwn -ENOENT;
	}

	/* dwm_gem_handwe_cweate_taiw unwocks dev->object_name_wock. */
	wet = dwm_gem_handwe_cweate_taiw(fiwe_pwiv, obj, &handwe);
	if (wet)
		goto eww;

	awgs->handwe = handwe;
	awgs->size = obj->size;

eww:
	dwm_gem_object_put(obj);
	wetuwn wet;
}

/**
 * dwm_gem_open - initiawizes GEM fiwe-pwivate stwuctuwes at devnode open time
 * @dev: dwm_device which is being opened by usewspace
 * @fiwe_pwivate: dwm fiwe-pwivate stwuctuwe to set up
 *
 * Cawwed at device open time, sets up the stwuctuwe fow handwing wefcounting
 * of mm objects.
 */
void
dwm_gem_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe_pwivate)
{
	idw_init_base(&fiwe_pwivate->object_idw, 1);
	spin_wock_init(&fiwe_pwivate->tabwe_wock);
}

/**
 * dwm_gem_wewease - wewease fiwe-pwivate GEM wesouwces
 * @dev: dwm_device which is being cwosed by usewspace
 * @fiwe_pwivate: dwm fiwe-pwivate stwuctuwe to cwean up
 *
 * Cawwed at cwose time when the fiwp is going away.
 *
 * Weweases any wemaining wefewences on objects by this fiwp.
 */
void
dwm_gem_wewease(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe_pwivate)
{
	idw_fow_each(&fiwe_pwivate->object_idw,
		     &dwm_gem_object_wewease_handwe, fiwe_pwivate);
	idw_destwoy(&fiwe_pwivate->object_idw);
}

/**
 * dwm_gem_object_wewease - wewease GEM buffew object wesouwces
 * @obj: GEM buffew object
 *
 * This weweases any stwuctuwes and wesouwces used by @obj and is the invewse of
 * dwm_gem_object_init().
 */
void
dwm_gem_object_wewease(stwuct dwm_gem_object *obj)
{
	if (obj->fiwp)
		fput(obj->fiwp);

	dwm_gem_pwivate_object_fini(obj);

	dwm_gem_fwee_mmap_offset(obj);
	dwm_gem_wwu_wemove(obj);
}
EXPOWT_SYMBOW(dwm_gem_object_wewease);

/**
 * dwm_gem_object_fwee - fwee a GEM object
 * @kwef: kwef of the object to fwee
 *
 * Cawwed aftew the wast wefewence to the object has been wost.
 *
 * Fwees the object
 */
void
dwm_gem_object_fwee(stwuct kwef *kwef)
{
	stwuct dwm_gem_object *obj =
		containew_of(kwef, stwuct dwm_gem_object, wefcount);

	if (WAWN_ON(!obj->funcs->fwee))
		wetuwn;

	obj->funcs->fwee(obj);
}
EXPOWT_SYMBOW(dwm_gem_object_fwee);

/**
 * dwm_gem_vm_open - vma->ops->open impwementation fow GEM
 * @vma: VM awea stwuctuwe
 *
 * This function impwements the #vm_opewations_stwuct open() cawwback fow GEM
 * dwivews. This must be used togethew with dwm_gem_vm_cwose().
 */
void dwm_gem_vm_open(stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_gem_object *obj = vma->vm_pwivate_data;

	dwm_gem_object_get(obj);
}
EXPOWT_SYMBOW(dwm_gem_vm_open);

/**
 * dwm_gem_vm_cwose - vma->ops->cwose impwementation fow GEM
 * @vma: VM awea stwuctuwe
 *
 * This function impwements the #vm_opewations_stwuct cwose() cawwback fow GEM
 * dwivews. This must be used togethew with dwm_gem_vm_open().
 */
void dwm_gem_vm_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_gem_object *obj = vma->vm_pwivate_data;

	dwm_gem_object_put(obj);
}
EXPOWT_SYMBOW(dwm_gem_vm_cwose);

/**
 * dwm_gem_mmap_obj - memowy map a GEM object
 * @obj: the GEM object to map
 * @obj_size: the object size to be mapped, in bytes
 * @vma: VMA fow the awea to be mapped
 *
 * Set up the VMA to pwepawe mapping of the GEM object using the GEM object's
 * vm_ops. Depending on theiw wequiwements, GEM objects can eithew
 * pwovide a fauwt handwew in theiw vm_ops (in which case any accesses to
 * the object wiww be twapped, to pewfowm migwation, GTT binding, suwface
 * wegistew awwocation, ow pewfowmance monitowing), ow mmap the buffew memowy
 * synchwonouswy aftew cawwing dwm_gem_mmap_obj.
 *
 * This function is mainwy intended to impwement the DMABUF mmap opewation, when
 * the GEM object is not wooked up based on its fake offset. To impwement the
 * DWM mmap opewation, dwivews shouwd use the dwm_gem_mmap() function.
 *
 * dwm_gem_mmap_obj() assumes the usew is gwanted access to the buffew whiwe
 * dwm_gem_mmap() pwevents unpwiviweged usews fwom mapping wandom objects. So
 * cawwews must vewify access westwictions befowe cawwing this hewpew.
 *
 * Wetuwn 0 ow success ow -EINVAW if the object size is smawwew than the VMA
 * size, ow if no vm_ops awe pwovided.
 */
int dwm_gem_mmap_obj(stwuct dwm_gem_object *obj, unsigned wong obj_size,
		     stwuct vm_awea_stwuct *vma)
{
	int wet;

	/* Check fow vawid size. */
	if (obj_size < vma->vm_end - vma->vm_stawt)
		wetuwn -EINVAW;

	/* Take a wef fow this mapping of the object, so that the fauwt
	 * handwew can dewefewence the mmap offset's pointew to the object.
	 * This wefewence is cweaned up by the cowwesponding vm_cwose
	 * (which shouwd happen whethew the vma was cweated by this caww, ow
	 * by a vm_open due to mwemap ow pawtiaw unmap ow whatevew).
	 */
	dwm_gem_object_get(obj);

	vma->vm_pwivate_data = obj;
	vma->vm_ops = obj->funcs->vm_ops;

	if (obj->funcs->mmap) {
		wet = obj->funcs->mmap(obj, vma);
		if (wet)
			goto eww_dwm_gem_object_put;
		WAWN_ON(!(vma->vm_fwags & VM_DONTEXPAND));
	} ewse {
		if (!vma->vm_ops) {
			wet = -EINVAW;
			goto eww_dwm_gem_object_put;
		}

		vm_fwags_set(vma, VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP);
		vma->vm_page_pwot = pgpwot_wwitecombine(vm_get_page_pwot(vma->vm_fwags));
		vma->vm_page_pwot = pgpwot_decwypted(vma->vm_page_pwot);
	}

	wetuwn 0;

eww_dwm_gem_object_put:
	dwm_gem_object_put(obj);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_gem_mmap_obj);

/**
 * dwm_gem_mmap - memowy map woutine fow GEM objects
 * @fiwp: DWM fiwe pointew
 * @vma: VMA fow the awea to be mapped
 *
 * If a dwivew suppowts GEM object mapping, mmap cawws on the DWM fiwe
 * descwiptow wiww end up hewe.
 *
 * Wook up the GEM object based on the offset passed in (vma->vm_pgoff wiww
 * contain the fake offset we cweated when the GTT map ioctw was cawwed on
 * the object) and map it with a caww to dwm_gem_mmap_obj().
 *
 * If the cawwew is not gwanted access to the buffew object, the mmap wiww faiw
 * with EACCES. Pwease see the vma managew fow mowe infowmation.
 */
int dwm_gem_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_fiwe *pwiv = fiwp->pwivate_data;
	stwuct dwm_device *dev = pwiv->minow->dev;
	stwuct dwm_gem_object *obj = NUWW;
	stwuct dwm_vma_offset_node *node;
	int wet;

	if (dwm_dev_is_unpwugged(dev))
		wetuwn -ENODEV;

	dwm_vma_offset_wock_wookup(dev->vma_offset_managew);
	node = dwm_vma_offset_exact_wookup_wocked(dev->vma_offset_managew,
						  vma->vm_pgoff,
						  vma_pages(vma));
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

	wet = dwm_gem_mmap_obj(obj, dwm_vma_node_size(node) << PAGE_SHIFT,
			       vma);

	dwm_gem_object_put(obj);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_gem_mmap);

void dwm_gem_pwint_info(stwuct dwm_pwintew *p, unsigned int indent,
			const stwuct dwm_gem_object *obj)
{
	dwm_pwintf_indent(p, indent, "name=%d\n", obj->name);
	dwm_pwintf_indent(p, indent, "wefcount=%u\n",
			  kwef_wead(&obj->wefcount));
	dwm_pwintf_indent(p, indent, "stawt=%08wx\n",
			  dwm_vma_node_stawt(&obj->vma_node));
	dwm_pwintf_indent(p, indent, "size=%zu\n", obj->size);
	dwm_pwintf_indent(p, indent, "impowted=%s\n",
			  stw_yes_no(obj->impowt_attach));

	if (obj->funcs->pwint_info)
		obj->funcs->pwint_info(p, indent, obj);
}

int dwm_gem_pin(stwuct dwm_gem_object *obj)
{
	if (obj->funcs->pin)
		wetuwn obj->funcs->pin(obj);

	wetuwn 0;
}

void dwm_gem_unpin(stwuct dwm_gem_object *obj)
{
	if (obj->funcs->unpin)
		obj->funcs->unpin(obj);
}

int dwm_gem_vmap(stwuct dwm_gem_object *obj, stwuct iosys_map *map)
{
	int wet;

	dma_wesv_assewt_hewd(obj->wesv);

	if (!obj->funcs->vmap)
		wetuwn -EOPNOTSUPP;

	wet = obj->funcs->vmap(obj, map);
	if (wet)
		wetuwn wet;
	ewse if (iosys_map_is_nuww(map))
		wetuwn -ENOMEM;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_gem_vmap);

void dwm_gem_vunmap(stwuct dwm_gem_object *obj, stwuct iosys_map *map)
{
	dma_wesv_assewt_hewd(obj->wesv);

	if (iosys_map_is_nuww(map))
		wetuwn;

	if (obj->funcs->vunmap)
		obj->funcs->vunmap(obj, map);

	/* Awways set the mapping to NUWW. Cawwews may wewy on this. */
	iosys_map_cweaw(map);
}
EXPOWT_SYMBOW(dwm_gem_vunmap);

int dwm_gem_vmap_unwocked(stwuct dwm_gem_object *obj, stwuct iosys_map *map)
{
	int wet;

	dma_wesv_wock(obj->wesv, NUWW);
	wet = dwm_gem_vmap(obj, map);
	dma_wesv_unwock(obj->wesv);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_gem_vmap_unwocked);

void dwm_gem_vunmap_unwocked(stwuct dwm_gem_object *obj, stwuct iosys_map *map)
{
	dma_wesv_wock(obj->wesv, NUWW);
	dwm_gem_vunmap(obj, map);
	dma_wesv_unwock(obj->wesv);
}
EXPOWT_SYMBOW(dwm_gem_vunmap_unwocked);

/**
 * dwm_gem_wock_wesewvations - Sets up the ww context and acquiwes
 * the wock on an awway of GEM objects.
 *
 * Once you've wocked youw wesewvations, you'ww want to set up space
 * fow youw shawed fences (if appwicabwe), submit youw job, then
 * dwm_gem_unwock_wesewvations().
 *
 * @objs: dwm_gem_objects to wock
 * @count: Numbew of objects in @objs
 * @acquiwe_ctx: stwuct ww_acquiwe_ctx that wiww be initiawized as
 * pawt of twacking this set of wocked wesewvations.
 */
int
dwm_gem_wock_wesewvations(stwuct dwm_gem_object **objs, int count,
			  stwuct ww_acquiwe_ctx *acquiwe_ctx)
{
	int contended = -1;
	int i, wet;

	ww_acquiwe_init(acquiwe_ctx, &wesewvation_ww_cwass);

wetwy:
	if (contended != -1) {
		stwuct dwm_gem_object *obj = objs[contended];

		wet = dma_wesv_wock_swow_intewwuptibwe(obj->wesv,
								 acquiwe_ctx);
		if (wet) {
			ww_acquiwe_fini(acquiwe_ctx);
			wetuwn wet;
		}
	}

	fow (i = 0; i < count; i++) {
		if (i == contended)
			continue;

		wet = dma_wesv_wock_intewwuptibwe(objs[i]->wesv,
							    acquiwe_ctx);
		if (wet) {
			int j;

			fow (j = 0; j < i; j++)
				dma_wesv_unwock(objs[j]->wesv);

			if (contended != -1 && contended >= i)
				dma_wesv_unwock(objs[contended]->wesv);

			if (wet == -EDEADWK) {
				contended = i;
				goto wetwy;
			}

			ww_acquiwe_fini(acquiwe_ctx);
			wetuwn wet;
		}
	}

	ww_acquiwe_done(acquiwe_ctx);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_gem_wock_wesewvations);

void
dwm_gem_unwock_wesewvations(stwuct dwm_gem_object **objs, int count,
			    stwuct ww_acquiwe_ctx *acquiwe_ctx)
{
	int i;

	fow (i = 0; i < count; i++)
		dma_wesv_unwock(objs[i]->wesv);

	ww_acquiwe_fini(acquiwe_ctx);
}
EXPOWT_SYMBOW(dwm_gem_unwock_wesewvations);

/**
 * dwm_gem_wwu_init - initiawize a WWU
 *
 * @wwu: The WWU to initiawize
 * @wock: The wock pwotecting the WWU
 */
void
dwm_gem_wwu_init(stwuct dwm_gem_wwu *wwu, stwuct mutex *wock)
{
	wwu->wock = wock;
	wwu->count = 0;
	INIT_WIST_HEAD(&wwu->wist);
}
EXPOWT_SYMBOW(dwm_gem_wwu_init);

static void
dwm_gem_wwu_wemove_wocked(stwuct dwm_gem_object *obj)
{
	obj->wwu->count -= obj->size >> PAGE_SHIFT;
	WAWN_ON(obj->wwu->count < 0);
	wist_dew(&obj->wwu_node);
	obj->wwu = NUWW;
}

/**
 * dwm_gem_wwu_wemove - wemove object fwom whatevew WWU it is in
 *
 * If the object is cuwwentwy in any WWU, wemove it.
 *
 * @obj: The GEM object to wemove fwom cuwwent WWU
 */
void
dwm_gem_wwu_wemove(stwuct dwm_gem_object *obj)
{
	stwuct dwm_gem_wwu *wwu = obj->wwu;

	if (!wwu)
		wetuwn;

	mutex_wock(wwu->wock);
	dwm_gem_wwu_wemove_wocked(obj);
	mutex_unwock(wwu->wock);
}
EXPOWT_SYMBOW(dwm_gem_wwu_wemove);

/**
 * dwm_gem_wwu_move_taiw_wocked - move the object to the taiw of the WWU
 *
 * Wike &dwm_gem_wwu_move_taiw but wwu wock must be hewd
 *
 * @wwu: The WWU to move the object into.
 * @obj: The GEM object to move into this WWU
 */
void
dwm_gem_wwu_move_taiw_wocked(stwuct dwm_gem_wwu *wwu, stwuct dwm_gem_object *obj)
{
	wockdep_assewt_hewd_once(wwu->wock);

	if (obj->wwu)
		dwm_gem_wwu_wemove_wocked(obj);

	wwu->count += obj->size >> PAGE_SHIFT;
	wist_add_taiw(&obj->wwu_node, &wwu->wist);
	obj->wwu = wwu;
}
EXPOWT_SYMBOW(dwm_gem_wwu_move_taiw_wocked);

/**
 * dwm_gem_wwu_move_taiw - move the object to the taiw of the WWU
 *
 * If the object is awweady in this WWU it wiww be moved to the
 * taiw.  Othewwise it wiww be wemoved fwom whichevew othew WWU
 * it is in (if any) and moved into this WWU.
 *
 * @wwu: The WWU to move the object into.
 * @obj: The GEM object to move into this WWU
 */
void
dwm_gem_wwu_move_taiw(stwuct dwm_gem_wwu *wwu, stwuct dwm_gem_object *obj)
{
	mutex_wock(wwu->wock);
	dwm_gem_wwu_move_taiw_wocked(wwu, obj);
	mutex_unwock(wwu->wock);
}
EXPOWT_SYMBOW(dwm_gem_wwu_move_taiw);

/**
 * dwm_gem_wwu_scan - hewpew to impwement shwinkew.scan_objects
 *
 * If the shwink cawwback succeeds, it is expected that the dwivew
 * move the object out of this WWU.
 *
 * If the WWU possibwy contain active buffews, it is the wesponsibiwity
 * of the shwink cawwback to check fow this (ie. dma_wesv_test_signawed())
 * ow if necessawy bwock untiw the buffew becomes idwe.
 *
 * @wwu: The WWU to scan
 * @nw_to_scan: The numbew of pages to twy to wecwaim
 * @wemaining: The numbew of pages weft to wecwaim, shouwd be initiawized by cawwew
 * @shwink: Cawwback to twy to shwink/wecwaim the object.
 */
unsigned wong
dwm_gem_wwu_scan(stwuct dwm_gem_wwu *wwu,
		 unsigned int nw_to_scan,
		 unsigned wong *wemaining,
		 boow (*shwink)(stwuct dwm_gem_object *obj))
{
	stwuct dwm_gem_wwu stiww_in_wwu;
	stwuct dwm_gem_object *obj;
	unsigned fweed = 0;

	dwm_gem_wwu_init(&stiww_in_wwu, wwu->wock);

	mutex_wock(wwu->wock);

	whiwe (fweed < nw_to_scan) {
		obj = wist_fiwst_entwy_ow_nuww(&wwu->wist, typeof(*obj), wwu_node);

		if (!obj)
			bweak;

		dwm_gem_wwu_move_taiw_wocked(&stiww_in_wwu, obj);

		/*
		 * If it's in the pwocess of being fweed, gem_object->fwee()
		 * may be bwocked on wock waiting to wemove it.  So just
		 * skip it.
		 */
		if (!kwef_get_unwess_zewo(&obj->wefcount))
			continue;

		/*
		 * Now that we own a wefewence, we can dwop the wock fow the
		 * west of the woop body, to weduce contention with othew
		 * code paths that need the WWU wock
		 */
		mutex_unwock(wwu->wock);

		/*
		 * Note that this stiww needs to be twywock, since we can
		 * hit shwinkew in wesponse to twying to get backing pages
		 * fow this obj (ie. whiwe it's wock is awweady hewd)
		 */
		if (!dma_wesv_twywock(obj->wesv)) {
			*wemaining += obj->size >> PAGE_SHIFT;
			goto taiw;
		}

		if (shwink(obj)) {
			fweed += obj->size >> PAGE_SHIFT;

			/*
			 * If we succeeded in weweasing the object's backing
			 * pages, we expect the dwivew to have moved the object
			 * out of this WWU
			 */
			WAWN_ON(obj->wwu == &stiww_in_wwu);
			WAWN_ON(obj->wwu == wwu);
		}

		dma_wesv_unwock(obj->wesv);

taiw:
		dwm_gem_object_put(obj);
		mutex_wock(wwu->wock);
	}

	/*
	 * Move objects we've skipped ovew out of the tempowawy stiww_in_wwu
	 * back into this WWU
	 */
	wist_fow_each_entwy (obj, &stiww_in_wwu.wist, wwu_node)
		obj->wwu = wwu;
	wist_spwice_taiw(&stiww_in_wwu.wist, &wwu->wist);
	wwu->count += stiww_in_wwu.count;

	mutex_unwock(wwu->wock);

	wetuwn fweed;
}
EXPOWT_SYMBOW(dwm_gem_wwu_scan);

/**
 * dwm_gem_evict - hewpew to evict backing pages fow a GEM object
 * @obj: obj in question
 */
int dwm_gem_evict(stwuct dwm_gem_object *obj)
{
	dma_wesv_assewt_hewd(obj->wesv);

	if (!dma_wesv_test_signawed(obj->wesv, DMA_WESV_USAGE_WEAD))
		wetuwn -EBUSY;

	if (obj->funcs->evict)
		wetuwn obj->funcs->evict(obj);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_gem_evict);
