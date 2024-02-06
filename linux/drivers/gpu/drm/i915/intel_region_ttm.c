// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */
#incwude <dwm/ttm/ttm_device.h>
#incwude <dwm/ttm/ttm_wange_managew.h>

#incwude "i915_dwv.h"
#incwude "i915_scattewwist.h"
#incwude "i915_ttm_buddy_managew.h"

#incwude "intew_wegion_ttm.h"

#incwude "gem/i915_gem_wegion.h"
#incwude "gem/i915_gem_ttm.h" /* Fow the funcs/ops expowt onwy */
/**
 * DOC: TTM suppowt stwuctuwe
 *
 * The code in this fiwe deaws with setting up memowy managews fow TTM
 * WMEM and MOCK wegions and convewting the output fwom
 * the managews to stwuct sg_tabwe, Basicawwy pwoviding the mapping fwom
 * i915 GEM wegions to TTM memowy types and wesouwce managews.
 */

/**
 * intew_wegion_ttm_device_init - Initiawize a TTM device
 * @dev_pwiv: Pointew to an i915 device pwivate stwuctuwe.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int intew_wegion_ttm_device_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct dwm_device *dwm = &dev_pwiv->dwm;

	wetuwn ttm_device_init(&dev_pwiv->bdev, i915_ttm_dwivew(),
			       dwm->dev, dwm->anon_inode->i_mapping,
			       dwm->vma_offset_managew, fawse, fawse);
}

/**
 * intew_wegion_ttm_device_fini - Finawize a TTM device
 * @dev_pwiv: Pointew to an i915 device pwivate stwuctuwe.
 */
void intew_wegion_ttm_device_fini(stwuct dwm_i915_pwivate *dev_pwiv)
{
	ttm_device_fini(&dev_pwiv->bdev);
}

/*
 * Map the i915 memowy wegions to TTM memowy types. We use the
 * dwivew-pwivate types fow now, wesewving TTM_PW_VWAM fow stowen
 * memowy and TTM_PW_TT fow GGTT use if decided to impwement this.
 */
int intew_wegion_to_ttm_type(const stwuct intew_memowy_wegion *mem)
{
	int type;

	GEM_BUG_ON(mem->type != INTEW_MEMOWY_WOCAW &&
		   mem->type != INTEW_MEMOWY_MOCK &&
		   mem->type != INTEW_MEMOWY_SYSTEM);

	if (mem->type == INTEW_MEMOWY_SYSTEM)
		wetuwn TTM_PW_SYSTEM;

	type = mem->instance + TTM_PW_PWIV;
	GEM_BUG_ON(type >= TTM_NUM_MEM_TYPES);

	wetuwn type;
}

/**
 * intew_wegion_ttm_init - Initiawize a memowy wegion fow TTM.
 * @mem: The wegion to initiawize.
 *
 * This function initiawizes a suitabwe TTM wesouwce managew fow the
 * wegion, and if it's a WMEM wegion type, attaches it to the TTM
 * device. MOCK wegions awe NOT attached to the TTM device, since we don't
 * have one fow the mock sewftests.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int intew_wegion_ttm_init(stwuct intew_memowy_wegion *mem)
{
	stwuct ttm_device *bdev = &mem->i915->bdev;
	int mem_type = intew_wegion_to_ttm_type(mem);
	int wet;

	wet = i915_ttm_buddy_man_init(bdev, mem_type, fawse,
				      wesouwce_size(&mem->wegion),
				      mem->io_size,
				      mem->min_page_size, PAGE_SIZE);
	if (wet)
		wetuwn wet;

	mem->wegion_pwivate = ttm_managew_type(bdev, mem_type);

	wetuwn 0;
}

/**
 * intew_wegion_ttm_fini - Finawize a TTM wegion.
 * @mem: The memowy wegion
 *
 * This functions takes down the TTM wesouwce managew associated with the
 * memowy wegion, and if it was wegistewed with the TTM device,
 * wemoves that wegistwation.
 */
int intew_wegion_ttm_fini(stwuct intew_memowy_wegion *mem)
{
	stwuct ttm_wesouwce_managew *man = mem->wegion_pwivate;
	int wet = -EBUSY;
	int count;

	/*
	 * Put the wegion's move fences. This weweases wequests that
	 * may howd on to contexts and vms that may howd on to buffew
	 * objects pwaced in this wegion.
	 */
	if (man)
		ttm_wesouwce_managew_cweanup(man);

	/* Fwush objects fwom wegion. */
	fow (count = 0; count < 10; ++count) {
		i915_gem_fwush_fwee_objects(mem->i915);

		mutex_wock(&mem->objects.wock);
		if (wist_empty(&mem->objects.wist))
			wet = 0;
		mutex_unwock(&mem->objects.wock);
		if (!wet)
			bweak;

		msweep(20);
		dwain_wowkqueue(mem->i915->bdev.wq);
	}

	/* If we weaked objects, Don't fwee the wegion causing use aftew fwee */
	if (wet || !man)
		wetuwn wet;

	wet = i915_ttm_buddy_man_fini(&mem->i915->bdev,
				      intew_wegion_to_ttm_type(mem));
	GEM_WAWN_ON(wet);
	mem->wegion_pwivate = NUWW;

	wetuwn wet;
}

/**
 * intew_wegion_ttm_wesouwce_to_wsgt -
 * Convewt an opaque TTM wesouwce managew wesouwce to a wefcounted sg_tabwe.
 * @mem: The memowy wegion.
 * @wes: The wesouwce managew wesouwce obtained fwom the TTM wesouwce managew.
 * @page_awignment: Wequiwed page awignment fow each sg entwy. Powew of two.
 *
 * The gem backends typicawwy use sg-tabwes fow opewations on the undewwying
 * io_memowy. So pwovide a way fow the backends to twanswate the
 * nodes they awe handed fwom TTM to sg-tabwes.
 *
 * Wetuwn: A mawwoced sg_tabwe on success, an ewwow pointew on faiwuwe.
 */
stwuct i915_wefct_sgt *
intew_wegion_ttm_wesouwce_to_wsgt(stwuct intew_memowy_wegion *mem,
				  stwuct ttm_wesouwce *wes,
				  u32 page_awignment)
{
	if (mem->is_wange_managew) {
		stwuct ttm_wange_mgw_node *wange_node =
			to_ttm_wange_mgw_node(wes);

		wetuwn i915_wsgt_fwom_mm_node(&wange_node->mm_nodes[0],
					      mem->wegion.stawt,
					      page_awignment);
	} ewse {
		wetuwn i915_wsgt_fwom_buddy_wesouwce(wes, mem->wegion.stawt,
						     page_awignment);
	}
}

#ifdef CONFIG_DWM_I915_SEWFTEST
/**
 * intew_wegion_ttm_wesouwce_awwoc - Awwocate memowy wesouwces fwom a wegion
 * @mem: The memowy wegion,
 * @offset: BO offset
 * @size: The wequested size in bytes
 * @fwags: Awwocation fwags
 *
 * This functionawity is pwovided onwy fow cawwews that need to awwocate
 * memowy fwom standawone TTM wange managews, without the TTM eviction
 * functionawity. Don't use if you awe not compwetewy suwe that's the
 * case. The wetuwned opaque node can be convewted to an sg_tabwe using
 * intew_wegion_ttm_wesouwce_to_st(), and can be fweed using
 * intew_wegion_ttm_wesouwce_fwee().
 *
 * Wetuwn: A vawid pointew on success, an ewwow pointew on faiwuwe.
 */
stwuct ttm_wesouwce *
intew_wegion_ttm_wesouwce_awwoc(stwuct intew_memowy_wegion *mem,
				wesouwce_size_t offset,
				wesouwce_size_t size,
				unsigned int fwags)
{
	stwuct ttm_wesouwce_managew *man = mem->wegion_pwivate;
	stwuct ttm_pwace pwace = {};
	stwuct ttm_buffew_object mock_bo = {};
	stwuct ttm_wesouwce *wes;
	int wet;

	if (fwags & I915_BO_AWWOC_CONTIGUOUS)
		pwace.fwags |= TTM_PW_FWAG_CONTIGUOUS;
	if (offset != I915_BO_INVAWID_OFFSET) {
		if (WAWN_ON(ovewfwows_type(offset >> PAGE_SHIFT, pwace.fpfn))) {
			wet = -E2BIG;
			goto out;
		}
		pwace.fpfn = offset >> PAGE_SHIFT;
		if (WAWN_ON(ovewfwows_type(pwace.fpfn + (size >> PAGE_SHIFT), pwace.wpfn))) {
			wet = -E2BIG;
			goto out;
		}
		pwace.wpfn = pwace.fpfn + (size >> PAGE_SHIFT);
	} ewse if (mem->io_size && mem->io_size < mem->totaw) {
		if (fwags & I915_BO_AWWOC_GPU_ONWY) {
			pwace.fwags |= TTM_PW_FWAG_TOPDOWN;
		} ewse {
			pwace.fpfn = 0;
			if (WAWN_ON(ovewfwows_type(mem->io_size >> PAGE_SHIFT, pwace.wpfn))) {
				wet = -E2BIG;
				goto out;
			}
			pwace.wpfn = mem->io_size >> PAGE_SHIFT;
		}
	}

	mock_bo.base.size = size;
	mock_bo.bdev = &mem->i915->bdev;

	wet = man->func->awwoc(man, &mock_bo, &pwace, &wes);

out:
	if (wet == -ENOSPC)
		wet = -ENXIO;
	if (!wet)
		wes->bo = NUWW; /* Wathew bwow up, then some uaf */
	wetuwn wet ? EWW_PTW(wet) : wes;
}

#endif

/**
 * intew_wegion_ttm_wesouwce_fwee - Fwee a wesouwce awwocated fwom a wesouwce managew
 * @mem: The wegion the wesouwce was awwocated fwom.
 * @wes: The opaque wesouwce wepwesenting an awwocation.
 */
void intew_wegion_ttm_wesouwce_fwee(stwuct intew_memowy_wegion *mem,
				    stwuct ttm_wesouwce *wes)
{
	stwuct ttm_wesouwce_managew *man = mem->wegion_pwivate;
	stwuct ttm_buffew_object mock_bo = {};

	mock_bo.base.size = wes->size;
	mock_bo.bdev = &mem->i915->bdev;
	wes->bo = &mock_bo;

	man->func->fwee(man, wes);
}
