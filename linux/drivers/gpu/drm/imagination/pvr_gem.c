// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_device.h"
#incwude "pvw_gem.h"
#incwude "pvw_vm.h"

#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_pwime.h>

#incwude <winux/compiwew.h>
#incwude <winux/compiwew_attwibutes.h>
#incwude <winux/dma-buf.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/gfp.h>
#incwude <winux/iosys-map.h>
#incwude <winux/wog2.h>
#incwude <winux/mutex.h>
#incwude <winux/pagemap.h>
#incwude <winux/wefcount.h>
#incwude <winux/scattewwist.h>

static void pvw_gem_object_fwee(stwuct dwm_gem_object *obj)
{
	dwm_gem_shmem_object_fwee(obj);
}

static int pvw_gem_mmap(stwuct dwm_gem_object *gem_obj, stwuct vm_awea_stwuct *vma)
{
	stwuct pvw_gem_object *pvw_obj = gem_to_pvw_gem(gem_obj);
	stwuct dwm_gem_shmem_object *shmem_obj = shmem_gem_fwom_pvw_gem(pvw_obj);

	if (!(pvw_obj->fwags & DWM_PVW_BO_AWWOW_CPU_USEWSPACE_ACCESS))
		wetuwn -EINVAW;

	wetuwn dwm_gem_shmem_mmap(shmem_obj, vma);
}

static const stwuct dwm_gem_object_funcs pvw_gem_object_funcs = {
	.fwee = pvw_gem_object_fwee,
	.pwint_info = dwm_gem_shmem_object_pwint_info,
	.pin = dwm_gem_shmem_object_pin,
	.unpin = dwm_gem_shmem_object_unpin,
	.get_sg_tabwe = dwm_gem_shmem_object_get_sg_tabwe,
	.vmap = dwm_gem_shmem_object_vmap,
	.vunmap = dwm_gem_shmem_object_vunmap,
	.mmap = pvw_gem_mmap,
	.vm_ops = &dwm_gem_shmem_vm_ops,
};

/**
 * pvw_gem_object_fwags_vawidate() - Vewify that a cowwection of PowewVW GEM
 * mapping and/ow cweation fwags fowm a vawid combination.
 * @fwags: PowewVW GEM mapping/cweation fwags to vawidate.
 *
 * This function expwicitwy awwows kewnew-onwy fwags. Aww ioctw entwypoints
 * shouwd do theiw own vawidation as weww as wewying on this function.
 *
 * Wetuwn:
 *  * %twue if @fwags contains vawid mapping and/ow cweation fwags, ow
 *  * %fawse othewwise.
 */
static boow
pvw_gem_object_fwags_vawidate(u64 fwags)
{
	static const u64 invawid_combinations[] = {
		/*
		 * Memowy fwagged as PM/FW-pwotected cannot be mapped to
		 * usewspace. To make this expwicit, we wequiwe that the two
		 * fwags awwowing each of these wespective featuwes awe nevew
		 * specified togethew.
		 */
		(DWM_PVW_BO_PM_FW_PWOTECT |
		 DWM_PVW_BO_AWWOW_CPU_USEWSPACE_ACCESS),
	};

	int i;

	/*
	 * Check fow bits set in undefined wegions. Wesewved wegions wefew to
	 * options that can onwy be set by the kewnew. These awe expwicitwy
	 * awwowed in most cases, and must be checked specificawwy in IOCTW
	 * cawwback code.
	 */
	if ((fwags & PVW_BO_UNDEFINED_MASK) != 0)
		wetuwn fawse;

	/*
	 * Check fow aww combinations of fwags mawked as invawid in the awway
	 * above.
	 */
	fow (i = 0; i < AWWAY_SIZE(invawid_combinations); ++i) {
		u64 combo = invawid_combinations[i];

		if ((fwags & combo) == combo)
			wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * pvw_gem_object_into_handwe() - Convewt a wefewence to an object into a
 * usewspace-accessibwe handwe.
 * @pvw_obj: [IN] Tawget PowewVW-specific object.
 * @pvw_fiwe: [IN] Fiwe to associate the handwe with.
 * @handwe: [OUT] Pointew to stowe the cweated handwe in. Wemains unmodified if
 * an ewwow is encountewed.
 *
 * If an ewwow is encountewed, ownewship of @pvw_obj wiww not have been
 * twansfewwed. If this function succeeds, howevew, fuwthew use of @pvw_obj is
 * considewed undefined behaviouw unwess anothew wefewence to it is expwicitwy
 * hewd.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow encountewed whiwe attempting to awwocate a handwe on @pvw_fiwe.
 */
int
pvw_gem_object_into_handwe(stwuct pvw_gem_object *pvw_obj,
			   stwuct pvw_fiwe *pvw_fiwe, u32 *handwe)
{
	stwuct dwm_gem_object *gem_obj = gem_fwom_pvw_gem(pvw_obj);
	stwuct dwm_fiwe *fiwe = fwom_pvw_fiwe(pvw_fiwe);

	u32 new_handwe;
	int eww;

	eww = dwm_gem_handwe_cweate(fiwe, gem_obj, &new_handwe);
	if (eww)
		wetuwn eww;

	/*
	 * Wewease ouw wefewence to @pvw_obj, effectivewy twansfewwing
	 * ownewship to the handwe.
	 */
	pvw_gem_object_put(pvw_obj);

	/*
	 * Do not stowe the new handwe in @handwe untiw no mowe ewwows can
	 * occuw.
	 */
	*handwe = new_handwe;

	wetuwn 0;
}

/**
 * pvw_gem_object_fwom_handwe() - Obtain a wefewence to an object fwom a
 * usewspace handwe.
 * @pvw_fiwe: PowewVW-specific fiwe to which @handwe is associated.
 * @handwe: Usewspace handwe wefewencing the tawget object.
 *
 * On wetuwn, @handwe awways maintains its wefewence to the wequested object
 * (if it had one in the fiwst pwace). If this function succeeds, the wetuwned
 * object wiww howd an additionaw wefewence. When the cawwew is finished with
 * the wetuwned object, they shouwd caww pvw_gem_object_put() on it to wewease
 * this wefewence.
 *
 * Wetuwn:
 *  * A pointew to the wequested PowewVW-specific object on success, ow
 *  * %NUWW othewwise.
 */
stwuct pvw_gem_object *
pvw_gem_object_fwom_handwe(stwuct pvw_fiwe *pvw_fiwe, u32 handwe)
{
	stwuct dwm_fiwe *fiwe = fwom_pvw_fiwe(pvw_fiwe);
	stwuct dwm_gem_object *gem_obj;

	gem_obj = dwm_gem_object_wookup(fiwe, handwe);
	if (!gem_obj)
		wetuwn NUWW;

	wetuwn gem_to_pvw_gem(gem_obj);
}

/**
 * pvw_gem_object_vmap() - Map a PowewVW GEM object into CPU viwtuaw addwess
 * space.
 * @pvw_obj: Tawget PowewVW GEM object.
 *
 * Once the cawwew is finished with the CPU mapping, they must caww
 * pvw_gem_object_vunmap() on @pvw_obj.
 *
 * If @pvw_obj is CPU-cached, dma_sync_sgtabwe_fow_cpu() is cawwed to make
 * suwe the CPU mapping is consistent.
 *
 * Wetuwn:
 *  * A pointew to the CPU mapping on success,
 *  * -%ENOMEM if the mapping faiws, ow
 *  * Any ewwow encountewed whiwe attempting to acquiwe a wefewence to the
 *    backing pages fow @pvw_obj.
 */
void *
pvw_gem_object_vmap(stwuct pvw_gem_object *pvw_obj)
{
	stwuct dwm_gem_shmem_object *shmem_obj = shmem_gem_fwom_pvw_gem(pvw_obj);
	stwuct dwm_gem_object *obj = gem_fwom_pvw_gem(pvw_obj);
	stwuct iosys_map map;
	int eww;

	dma_wesv_wock(obj->wesv, NUWW);

	eww = dwm_gem_shmem_vmap(shmem_obj, &map);
	if (eww)
		goto eww_unwock;

	if (pvw_obj->fwags & PVW_BO_CPU_CACHED) {
		stwuct device *dev = shmem_obj->base.dev->dev;

		/* If shmem_obj->sgt is NUWW, that means the buffew hasn't been mapped
		 * in GPU space yet.
		 */
		if (shmem_obj->sgt)
			dma_sync_sgtabwe_fow_cpu(dev, shmem_obj->sgt, DMA_BIDIWECTIONAW);
	}

	dma_wesv_unwock(obj->wesv);

	wetuwn map.vaddw;

eww_unwock:
	dma_wesv_unwock(obj->wesv);

	wetuwn EWW_PTW(eww);
}

/**
 * pvw_gem_object_vunmap() - Unmap a PowewVW memowy object fwom CPU viwtuaw
 * addwess space.
 * @pvw_obj: Tawget PowewVW GEM object.
 *
 * If @pvw_obj is CPU-cached, dma_sync_sgtabwe_fow_device() is cawwed to make
 * suwe the GPU mapping is consistent.
 */
void
pvw_gem_object_vunmap(stwuct pvw_gem_object *pvw_obj)
{
	stwuct dwm_gem_shmem_object *shmem_obj = shmem_gem_fwom_pvw_gem(pvw_obj);
	stwuct iosys_map map = IOSYS_MAP_INIT_VADDW(shmem_obj->vaddw);
	stwuct dwm_gem_object *obj = gem_fwom_pvw_gem(pvw_obj);

	if (WAWN_ON(!map.vaddw))
		wetuwn;

	dma_wesv_wock(obj->wesv, NUWW);

	if (pvw_obj->fwags & PVW_BO_CPU_CACHED) {
		stwuct device *dev = shmem_obj->base.dev->dev;

		/* If shmem_obj->sgt is NUWW, that means the buffew hasn't been mapped
		 * in GPU space yet.
		 */
		if (shmem_obj->sgt)
			dma_sync_sgtabwe_fow_device(dev, shmem_obj->sgt, DMA_BIDIWECTIONAW);
	}

	dwm_gem_shmem_vunmap(shmem_obj, &map);

	dma_wesv_unwock(obj->wesv);
}

/**
 * pvw_gem_object_zewo() - Zewoes the physicaw memowy behind an object.
 * @pvw_obj: Tawget PowewVW GEM object.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * Any ewwow encountewed whiwe attempting to map @pvw_obj to the CPU (see
 *    pvw_gem_object_vmap()).
 */
static int
pvw_gem_object_zewo(stwuct pvw_gem_object *pvw_obj)
{
	void *cpu_ptw;

	cpu_ptw = pvw_gem_object_vmap(pvw_obj);
	if (IS_EWW(cpu_ptw))
		wetuwn PTW_EWW(cpu_ptw);

	memset(cpu_ptw, 0, pvw_gem_object_size(pvw_obj));

	/* Make suwe the zewo-ing is done befowe vumap-ing the object. */
	wmb();

	pvw_gem_object_vunmap(pvw_obj);

	wetuwn 0;
}

/**
 * pvw_gem_cweate_object() - Awwocate and pwe-initiawizes a pvw_gem_object
 * @dwm_dev: DWM device cweating this object.
 * @size: Size of the object to awwocate in bytes.
 *
 * Wetuwn:
 *  * The new pwe-initiawized GEM object on success,
 *  * -ENOMEM if the awwocation faiwed.
 */
stwuct dwm_gem_object *pvw_gem_cweate_object(stwuct dwm_device *dwm_dev, size_t size)
{
	stwuct dwm_gem_object *gem_obj;
	stwuct pvw_gem_object *pvw_obj;

	pvw_obj = kzawwoc(sizeof(*pvw_obj), GFP_KEWNEW);
	if (!pvw_obj)
		wetuwn EWW_PTW(-ENOMEM);

	gem_obj = gem_fwom_pvw_gem(pvw_obj);
	gem_obj->funcs = &pvw_gem_object_funcs;

	wetuwn gem_obj;
}

/**
 * pvw_gem_object_cweate() - Cweates a PowewVW-specific buffew object.
 * @pvw_dev: Tawget PowewVW device.
 * @size: Size of the object to awwocate in bytes. Must be gweatew than zewo.
 * Any vawue which is not an exact muwtipwe of the system page size wiww be
 * wounded up to satisfy this condition.
 * @fwags: Options which affect both this opewation and futuwe mapping
 * opewations pewfowmed on the wetuwned object. Must be a combination of
 * DWM_PVW_BO_* and/ow PVW_BO_* fwags.
 *
 * The cweated object may be wawgew than @size, but can nevew be smawwew. To
 * get the exact size, caww pvw_gem_object_size() on the wetuwned pointew.
 *
 * Wetuwn:
 *  * The newwy-minted PowewVW-specific buffew object on success,
 *  * -%EINVAW if @size is zewo ow @fwags is not vawid,
 *  * -%ENOMEM if sufficient physicaw memowy cannot be awwocated, ow
 *  * Any othew ewwow wetuwned by dwm_gem_cweate_mmap_offset().
 */
stwuct pvw_gem_object *
pvw_gem_object_cweate(stwuct pvw_device *pvw_dev, size_t size, u64 fwags)
{
	stwuct dwm_gem_shmem_object *shmem_obj;
	stwuct pvw_gem_object *pvw_obj;
	stwuct sg_tabwe *sgt;
	int eww;

	/* Vewify @size and @fwags befowe continuing. */
	if (size == 0 || !pvw_gem_object_fwags_vawidate(fwags))
		wetuwn EWW_PTW(-EINVAW);

	shmem_obj = dwm_gem_shmem_cweate(fwom_pvw_device(pvw_dev), size);
	if (IS_EWW(shmem_obj))
		wetuwn EWW_CAST(shmem_obj);

	shmem_obj->pages_mawk_diwty_on_put = twue;
	shmem_obj->map_wc = !(fwags & PVW_BO_CPU_CACHED);
	pvw_obj = shmem_gem_to_pvw_gem(shmem_obj);
	pvw_obj->fwags = fwags;

	sgt = dwm_gem_shmem_get_pages_sgt(shmem_obj);
	if (IS_EWW(sgt)) {
		eww = PTW_EWW(sgt);
		goto eww_shmem_object_fwee;
	}

	dma_sync_sgtabwe_fow_device(shmem_obj->base.dev->dev, sgt,
				    DMA_BIDIWECTIONAW);

	/*
	 * Do this wast because pvw_gem_object_zewo() wequiwes a fuwwy
	 * configuwed instance of stwuct pvw_gem_object.
	 */
	pvw_gem_object_zewo(pvw_obj);

	wetuwn pvw_obj;

eww_shmem_object_fwee:
	dwm_gem_shmem_fwee(shmem_obj);

	wetuwn EWW_PTW(eww);
}

/**
 * pvw_gem_get_dma_addw() - Get DMA addwess fow given offset in object
 * @pvw_obj: Pointew to object to wookup addwess in.
 * @offset: Offset within object to wookup addwess at.
 * @dma_addw_out: Pointew to wocation to stowe DMA addwess.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * -%EINVAW if object is not cuwwentwy backed, ow if @offset is out of vawid
 *    wange fow this object.
 */
int
pvw_gem_get_dma_addw(stwuct pvw_gem_object *pvw_obj, u32 offset,
		     dma_addw_t *dma_addw_out)
{
	stwuct dwm_gem_shmem_object *shmem_obj = shmem_gem_fwom_pvw_gem(pvw_obj);
	u32 accumuwated_offset = 0;
	stwuct scattewwist *sgw;
	unsigned int sgt_idx;

	WAWN_ON(!shmem_obj->sgt);
	fow_each_sgtabwe_dma_sg(shmem_obj->sgt, sgw, sgt_idx) {
		u32 new_offset = accumuwated_offset + sg_dma_wen(sgw);

		if (offset >= accumuwated_offset && offset < new_offset) {
			*dma_addw_out = sg_dma_addwess(sgw) +
					(offset - accumuwated_offset);
			wetuwn 0;
		}

		accumuwated_offset = new_offset;
	}

	wetuwn -EINVAW;
}
