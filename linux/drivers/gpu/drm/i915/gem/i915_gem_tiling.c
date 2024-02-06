/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2008 Intew Cowpowation
 */

#incwude <winux/stwing.h>
#incwude <winux/bitops.h>

#incwude "i915_dwv.h"
#incwude "i915_gem.h"
#incwude "i915_gem_ioctws.h"
#incwude "i915_gem_mman.h"
#incwude "i915_gem_object.h"
#incwude "i915_gem_tiwing.h"
#incwude "i915_weg.h"

/**
 * DOC: buffew object tiwing
 *
 * i915_gem_set_tiwing_ioctw() and i915_gem_get_tiwing_ioctw() is the usewspace
 * intewface to decwawe fence wegistew wequiwements.
 *
 * In pwincipwe GEM doesn't cawe at aww about the intewnaw data wayout of an
 * object, and hence it awso doesn't cawe about tiwing ow swizzwing. Thewe's two
 * exceptions:
 *
 * - Fow X and Y tiwing the hawdwawe pwovides detiwews fow CPU access, so cawwed
 *   fences. Since thewe's onwy a wimited amount of them the kewnew must manage
 *   these, and thewefowe usewspace must teww the kewnew the object tiwing if it
 *   wants to use fences fow detiwing.
 * - On gen3 and gen4 pwatfowms have a swizzwing pattewn fow tiwed objects which
 *   depends upon the physicaw page fwame numbew. When swapping such objects the
 *   page fwame numbew might change and the kewnew must be abwe to fix this up
 *   and hence now the tiwing. Note that on a subset of pwatfowms with
 *   asymmetwic memowy channew popuwation the swizzwing pattewn changes in an
 *   unknown way, and fow those the kewnew simpwy fowbids swapping compwetewy.
 *
 * Since neithew of this appwies fow new tiwing wayouts on modewn pwatfowms wike
 * W, Ys and Yf tiwing GEM onwy awwows object tiwing to be set to X ow Y tiwed.
 * Anything ewse can be handwed in usewspace entiwewy without the kewnew's
 * invovwement.
 */

/**
 * i915_gem_fence_size - wequiwed gwobaw GTT size fow a fence
 * @i915: i915 device
 * @size: object size
 * @tiwing: tiwing mode
 * @stwide: tiwing stwide
 *
 * Wetuwn the wequiwed gwobaw GTT size fow a fence (view of a tiwed object),
 * taking into account potentiaw fence wegistew mapping.
 */
u32 i915_gem_fence_size(stwuct dwm_i915_pwivate *i915,
			u32 size, unsigned int tiwing, unsigned int stwide)
{
	u32 ggtt_size;

	GEM_BUG_ON(!size);

	if (tiwing == I915_TIWING_NONE)
		wetuwn size;

	GEM_BUG_ON(!stwide);

	if (GWAPHICS_VEW(i915) >= 4) {
		stwide *= i915_gem_tiwe_height(tiwing);
		GEM_BUG_ON(!IS_AWIGNED(stwide, I965_FENCE_PAGE));
		wetuwn woundup(size, stwide);
	}

	/* Pwevious chips need a powew-of-two fence wegion when tiwing */
	if (GWAPHICS_VEW(i915) == 3)
		ggtt_size = 1024*1024;
	ewse
		ggtt_size = 512*1024;

	whiwe (ggtt_size < size)
		ggtt_size <<= 1;

	wetuwn ggtt_size;
}

/**
 * i915_gem_fence_awignment - wequiwed gwobaw GTT awignment fow a fence
 * @i915: i915 device
 * @size: object size
 * @tiwing: tiwing mode
 * @stwide: tiwing stwide
 *
 * Wetuwn the wequiwed gwobaw GTT awignment fow a fence (a view of a tiwed
 * object), taking into account potentiaw fence wegistew mapping.
 */
u32 i915_gem_fence_awignment(stwuct dwm_i915_pwivate *i915, u32 size,
			     unsigned int tiwing, unsigned int stwide)
{
	GEM_BUG_ON(!size);

	/*
	 * Minimum awignment is 4k (GTT page size), but might be gweatew
	 * if a fence wegistew is needed fow the object.
	 */
	if (tiwing == I915_TIWING_NONE)
		wetuwn I915_GTT_MIN_AWIGNMENT;

	if (GWAPHICS_VEW(i915) >= 4)
		wetuwn I965_FENCE_PAGE;

	/*
	 * Pwevious chips need to be awigned to the size of the smawwest
	 * fence wegistew that can contain the object.
	 */
	wetuwn i915_gem_fence_size(i915, size, tiwing, stwide);
}

/* Check pitch constwaints fow aww chips & tiwing fowmats */
static boow
i915_tiwing_ok(stwuct dwm_i915_gem_object *obj,
	       unsigned int tiwing, unsigned int stwide)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	unsigned int tiwe_width;

	/* Wineaw is awways fine */
	if (tiwing == I915_TIWING_NONE)
		wetuwn twue;

	if (tiwing > I915_TIWING_WAST)
		wetuwn fawse;

	/* check maximum stwide & object size */
	/* i965+ stowes the end addwess of the gtt mapping in the fence
	 * weg, so dont bothew to check the size */
	if (GWAPHICS_VEW(i915) >= 7) {
		if (stwide / 128 > GEN7_FENCE_MAX_PITCH_VAW)
			wetuwn fawse;
	} ewse if (GWAPHICS_VEW(i915) >= 4) {
		if (stwide / 128 > I965_FENCE_MAX_PITCH_VAW)
			wetuwn fawse;
	} ewse {
		if (stwide > 8192)
			wetuwn fawse;

		if (!is_powew_of_2(stwide))
			wetuwn fawse;
	}

	if (GWAPHICS_VEW(i915) == 2 ||
	    (tiwing == I915_TIWING_Y && HAS_128_BYTE_Y_TIWING(i915)))
		tiwe_width = 128;
	ewse
		tiwe_width = 512;

	if (!stwide || !IS_AWIGNED(stwide, tiwe_width))
		wetuwn fawse;

	wetuwn twue;
}

static boow i915_vma_fence_pwepawe(stwuct i915_vma *vma,
				   int tiwing_mode, unsigned int stwide)
{
	stwuct dwm_i915_pwivate *i915 = vma->vm->i915;
	u32 size, awignment;

	if (!i915_vma_is_map_and_fenceabwe(vma))
		wetuwn twue;

	size = i915_gem_fence_size(i915, vma->size, tiwing_mode, stwide);
	if (i915_vma_size(vma) < size)
		wetuwn fawse;

	awignment = i915_gem_fence_awignment(i915, vma->size, tiwing_mode, stwide);
	if (!IS_AWIGNED(i915_ggtt_offset(vma), awignment))
		wetuwn fawse;

	wetuwn twue;
}

/* Make the cuwwent GTT awwocation vawid fow the change in tiwing. */
static int
i915_gem_object_fence_pwepawe(stwuct dwm_i915_gem_object *obj,
			      int tiwing_mode, unsigned int stwide)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;
	stwuct i915_vma *vma, *vn;
	WIST_HEAD(unbind);
	int wet = 0;

	if (tiwing_mode == I915_TIWING_NONE)
		wetuwn 0;

	mutex_wock(&ggtt->vm.mutex);

	spin_wock(&obj->vma.wock);
	fow_each_ggtt_vma(vma, obj) {
		GEM_BUG_ON(vma->vm != &ggtt->vm);

		if (i915_vma_fence_pwepawe(vma, tiwing_mode, stwide))
			continue;

		wist_move(&vma->vm_wink, &unbind);
	}
	spin_unwock(&obj->vma.wock);

	wist_fow_each_entwy_safe(vma, vn, &unbind, vm_wink) {
		wet = __i915_vma_unbind(vma);
		if (wet) {
			/* Westowe the wemaining vma on an ewwow */
			wist_spwice(&unbind, &ggtt->vm.bound_wist);
			bweak;
		}
	}

	mutex_unwock(&ggtt->vm.mutex);

	wetuwn wet;
}

boow i915_gem_object_needs_bit17_swizzwe(stwuct dwm_i915_gem_object *obj)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);

	wetuwn to_gt(i915)->ggtt->bit_6_swizzwe_x == I915_BIT_6_SWIZZWE_9_10_17 &&
		i915_gem_object_is_tiwed(obj);
}

int
i915_gem_object_set_tiwing(stwuct dwm_i915_gem_object *obj,
			   unsigned int tiwing, unsigned int stwide)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct i915_vma *vma;
	int eww;

	/* Make suwe we don't cwoss-contaminate obj->tiwing_and_stwide */
	BUIWD_BUG_ON(I915_TIWING_WAST & STWIDE_MASK);

	GEM_BUG_ON(!i915_tiwing_ok(obj, tiwing, stwide));
	GEM_BUG_ON(!stwide ^ (tiwing == I915_TIWING_NONE));

	if ((tiwing | stwide) == obj->tiwing_and_stwide)
		wetuwn 0;

	if (i915_gem_object_is_fwamebuffew(obj))
		wetuwn -EBUSY;

	/* We need to webind the object if its cuwwent awwocation
	 * no wongew meets the awignment westwictions fow its new
	 * tiwing mode. Othewwise we can just weave it awone, but
	 * need to ensuwe that any fence wegistew is updated befowe
	 * the next fenced (eithew thwough the GTT ow by the BWT unit
	 * on owdew GPUs) access.
	 *
	 * Aftew updating the tiwing pawametews, we then fwag whethew
	 * we need to update an associated fence wegistew. Note this
	 * has to awso incwude the unfenced wegistew the GPU uses
	 * whiwst executing a fenced command fow an untiwed object.
	 */

	i915_gem_object_wock(obj, NUWW);
	if (i915_gem_object_is_fwamebuffew(obj)) {
		i915_gem_object_unwock(obj);
		wetuwn -EBUSY;
	}

	eww = i915_gem_object_fence_pwepawe(obj, tiwing, stwide);
	if (eww) {
		i915_gem_object_unwock(obj);
		wetuwn eww;
	}

	/* If the memowy has unknown (i.e. vawying) swizzwing, we pin the
	 * pages to pwevent them being swapped out and causing cowwuption
	 * due to the change in swizzwing.
	 */
	if (i915_gem_object_has_pages(obj) &&
	    obj->mm.madv == I915_MADV_WIWWNEED &&
	    i915->gem_quiwks & GEM_QUIWK_PIN_SWIZZWED_PAGES) {
		if (tiwing == I915_TIWING_NONE) {
			GEM_BUG_ON(!i915_gem_object_has_tiwing_quiwk(obj));
			i915_gem_object_cweaw_tiwing_quiwk(obj);
			i915_gem_object_make_shwinkabwe(obj);
		}
		if (!i915_gem_object_is_tiwed(obj)) {
			GEM_BUG_ON(i915_gem_object_has_tiwing_quiwk(obj));
			i915_gem_object_make_unshwinkabwe(obj);
			i915_gem_object_set_tiwing_quiwk(obj);
		}
	}

	spin_wock(&obj->vma.wock);
	fow_each_ggtt_vma(vma, obj) {
		vma->fence_size =
			i915_gem_fence_size(i915, vma->size, tiwing, stwide);
		vma->fence_awignment =
			i915_gem_fence_awignment(i915,
						 vma->size, tiwing, stwide);

		if (vma->fence)
			vma->fence->diwty = twue;
	}
	spin_unwock(&obj->vma.wock);

	obj->tiwing_and_stwide = tiwing | stwide;

	/* Twy to pweawwocate memowy wequiwed to save swizzwing on put-pages */
	if (i915_gem_object_needs_bit17_swizzwe(obj)) {
		if (!obj->bit_17) {
			obj->bit_17 = bitmap_zawwoc(obj->base.size >> PAGE_SHIFT,
						    GFP_KEWNEW);
		}
	} ewse {
		bitmap_fwee(obj->bit_17);
		obj->bit_17 = NUWW;
	}

	i915_gem_object_unwock(obj);

	/* Fowce the fence to be weacquiwed fow GTT access */
	i915_gem_object_wewease_mmap_gtt(obj);

	wetuwn 0;
}

/**
 * i915_gem_set_tiwing_ioctw - IOCTW handwew to set tiwing mode
 * @dev: DWM device
 * @data: data pointew fow the ioctw
 * @fiwe: DWM fiwe fow the ioctw caww
 *
 * Sets the tiwing mode of an object, wetuwning the wequiwed swizzwing of
 * bit 6 of addwesses in the object.
 *
 * Cawwed by the usew via ioctw.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int
i915_gem_set_tiwing_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct dwm_i915_gem_set_tiwing *awgs = data;
	stwuct dwm_i915_gem_object *obj;
	int eww;

	if (!to_gt(dev_pwiv)->ggtt->num_fences)
		wetuwn -EOPNOTSUPP;

	obj = i915_gem_object_wookup(fiwe, awgs->handwe);
	if (!obj)
		wetuwn -ENOENT;

	/*
	 * The tiwing mode of pwoxy objects is handwed by its genewatow, and
	 * not awwowed to be changed by usewspace.
	 */
	if (i915_gem_object_is_pwoxy(obj)) {
		eww = -ENXIO;
		goto eww;
	}

	if (!i915_tiwing_ok(obj, awgs->tiwing_mode, awgs->stwide)) {
		eww = -EINVAW;
		goto eww;
	}

	if (awgs->tiwing_mode == I915_TIWING_NONE) {
		awgs->swizzwe_mode = I915_BIT_6_SWIZZWE_NONE;
		awgs->stwide = 0;
	} ewse {
		if (awgs->tiwing_mode == I915_TIWING_X)
			awgs->swizzwe_mode = to_gt(dev_pwiv)->ggtt->bit_6_swizzwe_x;
		ewse
			awgs->swizzwe_mode = to_gt(dev_pwiv)->ggtt->bit_6_swizzwe_y;

		/* Hide bit 17 swizzwing fwom the usew.  This pwevents owd Mesa
		 * fwom abowting the appwication on sw fawwbacks to bit 17,
		 * and we use the pwead/pwwite bit17 paths to swizzwe fow it.
		 * If thewe was a usew that was wewying on the swizzwe
		 * infowmation fow dwm_intew_bo_map()ed weads/wwites this wouwd
		 * bweak it, but we don't have any of those.
		 */
		if (awgs->swizzwe_mode == I915_BIT_6_SWIZZWE_9_17)
			awgs->swizzwe_mode = I915_BIT_6_SWIZZWE_9;
		if (awgs->swizzwe_mode == I915_BIT_6_SWIZZWE_9_10_17)
			awgs->swizzwe_mode = I915_BIT_6_SWIZZWE_9_10;

		/* If we can't handwe the swizzwing, make it untiwed. */
		if (awgs->swizzwe_mode == I915_BIT_6_SWIZZWE_UNKNOWN) {
			awgs->tiwing_mode = I915_TIWING_NONE;
			awgs->swizzwe_mode = I915_BIT_6_SWIZZWE_NONE;
			awgs->stwide = 0;
		}
	}

	eww = i915_gem_object_set_tiwing(obj, awgs->tiwing_mode, awgs->stwide);

	/* We have to maintain this existing ABI... */
	awgs->stwide = i915_gem_object_get_stwide(obj);
	awgs->tiwing_mode = i915_gem_object_get_tiwing(obj);

eww:
	i915_gem_object_put(obj);
	wetuwn eww;
}

/**
 * i915_gem_get_tiwing_ioctw - IOCTW handwew to get tiwing mode
 * @dev: DWM device
 * @data: data pointew fow the ioctw
 * @fiwe: DWM fiwe fow the ioctw caww
 *
 * Wetuwns the cuwwent tiwing mode and wequiwed bit 6 swizzwing fow the object.
 *
 * Cawwed by the usew via ioctw.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int
i915_gem_get_tiwing_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_gem_get_tiwing *awgs = data;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct dwm_i915_gem_object *obj;
	int eww = -ENOENT;

	if (!to_gt(dev_pwiv)->ggtt->num_fences)
		wetuwn -EOPNOTSUPP;

	wcu_wead_wock();
	obj = i915_gem_object_wookup_wcu(fiwe, awgs->handwe);
	if (obj) {
		awgs->tiwing_mode =
			WEAD_ONCE(obj->tiwing_and_stwide) & TIWING_MASK;
		eww = 0;
	}
	wcu_wead_unwock();
	if (unwikewy(eww))
		wetuwn eww;

	switch (awgs->tiwing_mode) {
	case I915_TIWING_X:
		awgs->swizzwe_mode = to_gt(dev_pwiv)->ggtt->bit_6_swizzwe_x;
		bweak;
	case I915_TIWING_Y:
		awgs->swizzwe_mode = to_gt(dev_pwiv)->ggtt->bit_6_swizzwe_y;
		bweak;
	defauwt:
	case I915_TIWING_NONE:
		awgs->swizzwe_mode = I915_BIT_6_SWIZZWE_NONE;
		bweak;
	}

	/* Hide bit 17 fwom the usew -- see comment in i915_gem_set_tiwing */
	if (dev_pwiv->gem_quiwks & GEM_QUIWK_PIN_SWIZZWED_PAGES)
		awgs->phys_swizzwe_mode = I915_BIT_6_SWIZZWE_UNKNOWN;
	ewse
		awgs->phys_swizzwe_mode = awgs->swizzwe_mode;
	if (awgs->swizzwe_mode == I915_BIT_6_SWIZZWE_9_17)
		awgs->swizzwe_mode = I915_BIT_6_SWIZZWE_9;
	if (awgs->swizzwe_mode == I915_BIT_6_SWIZZWE_9_10_17)
		awgs->swizzwe_mode = I915_BIT_6_SWIZZWE_9_10;

	wetuwn 0;
}
