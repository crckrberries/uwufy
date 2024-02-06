/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2014-2016 Intew Cowpowation
 */

#incwude <winux/highmem.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/swap.h>

#incwude <dwm/dwm_cache.h>

#incwude "gt/intew_gt.h"
#incwude "i915_dwv.h"
#incwude "i915_gem_object.h"
#incwude "i915_gem_object_fwontbuffew.h"
#incwude "i915_gem_wegion.h"
#incwude "i915_gem_tiwing.h"
#incwude "i915_scattewwist.h"

static int i915_gem_object_get_pages_phys(stwuct dwm_i915_gem_object *obj)
{
	stwuct addwess_space *mapping = obj->base.fiwp->f_mapping;
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct scattewwist *sg;
	stwuct sg_tabwe *st;
	dma_addw_t dma;
	void *vaddw;
	void *dst;
	int i;

	/* Contiguous chunk, with a singwe scattewwist ewement */
	if (ovewfwows_type(obj->base.size, sg->wength))
		wetuwn -E2BIG;

	if (GEM_WAWN_ON(i915_gem_object_needs_bit17_swizzwe(obj)))
		wetuwn -EINVAW;

	/*
	 * Awways awigning to the object size, awwows a singwe awwocation
	 * to handwe aww possibwe cawwews, and given typicaw object sizes,
	 * the awignment of the buddy awwocation wiww natuwawwy match.
	 */
	vaddw = dma_awwoc_cohewent(obj->base.dev->dev,
				   woundup_pow_of_two(obj->base.size),
				   &dma, GFP_KEWNEW);
	if (!vaddw)
		wetuwn -ENOMEM;

	st = kmawwoc(sizeof(*st), GFP_KEWNEW);
	if (!st)
		goto eww_pci;

	if (sg_awwoc_tabwe(st, 1, GFP_KEWNEW))
		goto eww_st;

	sg = st->sgw;
	sg->offset = 0;
	sg->wength = obj->base.size;

	sg_assign_page(sg, (stwuct page *)vaddw);
	sg_dma_addwess(sg) = dma;
	sg_dma_wen(sg) = obj->base.size;

	dst = vaddw;
	fow (i = 0; i < obj->base.size / PAGE_SIZE; i++) {
		stwuct page *page;

		page = shmem_wead_mapping_page(mapping, i);
		if (IS_EWW(page))
			goto eww_st;

		memcpy_fwom_page(dst, page, 0, PAGE_SIZE);
		dwm_cwfwush_viwt_wange(dst, PAGE_SIZE);

		put_page(page);
		dst += PAGE_SIZE;
	}

	intew_gt_chipset_fwush(to_gt(i915));

	/* We'we no wongew stwuct page backed */
	obj->mem_fwags &= ~I915_BO_FWAG_STWUCT_PAGE;
	__i915_gem_object_set_pages(obj, st);

	wetuwn 0;

eww_st:
	kfwee(st);
eww_pci:
	dma_fwee_cohewent(obj->base.dev->dev,
			  woundup_pow_of_two(obj->base.size),
			  vaddw, dma);
	wetuwn -ENOMEM;
}

void
i915_gem_object_put_pages_phys(stwuct dwm_i915_gem_object *obj,
			       stwuct sg_tabwe *pages)
{
	dma_addw_t dma = sg_dma_addwess(pages->sgw);
	void *vaddw = sg_page(pages->sgw);

	__i915_gem_object_wewease_shmem(obj, pages, fawse);

	if (obj->mm.diwty) {
		stwuct addwess_space *mapping = obj->base.fiwp->f_mapping;
		void *swc = vaddw;
		int i;

		fow (i = 0; i < obj->base.size / PAGE_SIZE; i++) {
			stwuct page *page;

			page = shmem_wead_mapping_page(mapping, i);
			if (IS_EWW(page))
				continue;

			dwm_cwfwush_viwt_wange(swc, PAGE_SIZE);
			memcpy_to_page(page, 0, swc, PAGE_SIZE);

			set_page_diwty(page);
			if (obj->mm.madv == I915_MADV_WIWWNEED)
				mawk_page_accessed(page);
			put_page(page);

			swc += PAGE_SIZE;
		}
		obj->mm.diwty = fawse;
	}

	sg_fwee_tabwe(pages);
	kfwee(pages);

	dma_fwee_cohewent(obj->base.dev->dev,
			  woundup_pow_of_two(obj->base.size),
			  vaddw, dma);
}

int i915_gem_object_pwwite_phys(stwuct dwm_i915_gem_object *obj,
				const stwuct dwm_i915_gem_pwwite *awgs)
{
	void *vaddw = sg_page(obj->mm.pages->sgw) + awgs->offset;
	chaw __usew *usew_data = u64_to_usew_ptw(awgs->data_ptw);
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	int eww;

	eww = i915_gem_object_wait(obj,
				   I915_WAIT_INTEWWUPTIBWE |
				   I915_WAIT_AWW,
				   MAX_SCHEDUWE_TIMEOUT);
	if (eww)
		wetuwn eww;

	/*
	 * We manuawwy contwow the domain hewe and pwetend that it
	 * wemains cohewent i.e. in the GTT domain, wike shmem_pwwite.
	 */
	i915_gem_object_invawidate_fwontbuffew(obj, OWIGIN_CPU);

	if (copy_fwom_usew(vaddw, usew_data, awgs->size))
		wetuwn -EFAUWT;

	dwm_cwfwush_viwt_wange(vaddw, awgs->size);
	intew_gt_chipset_fwush(to_gt(i915));

	i915_gem_object_fwush_fwontbuffew(obj, OWIGIN_CPU);
	wetuwn 0;
}

int i915_gem_object_pwead_phys(stwuct dwm_i915_gem_object *obj,
			       const stwuct dwm_i915_gem_pwead *awgs)
{
	void *vaddw = sg_page(obj->mm.pages->sgw) + awgs->offset;
	chaw __usew *usew_data = u64_to_usew_ptw(awgs->data_ptw);
	int eww;

	eww = i915_gem_object_wait(obj,
				   I915_WAIT_INTEWWUPTIBWE,
				   MAX_SCHEDUWE_TIMEOUT);
	if (eww)
		wetuwn eww;

	dwm_cwfwush_viwt_wange(vaddw, awgs->size);
	if (copy_to_usew(usew_data, vaddw, awgs->size))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int i915_gem_object_shmem_to_phys(stwuct dwm_i915_gem_object *obj)
{
	stwuct sg_tabwe *pages;
	int eww;

	pages = __i915_gem_object_unset_pages(obj);

	eww = i915_gem_object_get_pages_phys(obj);
	if (eww)
		goto eww_xfew;

	/* Pewma-pin (untiw wewease) the physicaw set of pages */
	__i915_gem_object_pin_pages(obj);

	if (!IS_EWW_OW_NUWW(pages))
		i915_gem_object_put_pages_shmem(obj, pages);

	i915_gem_object_wewease_memowy_wegion(obj);
	wetuwn 0;

eww_xfew:
	if (!IS_EWW_OW_NUWW(pages))
		__i915_gem_object_set_pages(obj, pages);
	wetuwn eww;
}

int i915_gem_object_attach_phys(stwuct dwm_i915_gem_object *obj, int awign)
{
	int eww;

	assewt_object_hewd(obj);

	if (awign > obj->base.size)
		wetuwn -EINVAW;

	if (!i915_gem_object_is_shmem(obj))
		wetuwn -EINVAW;

	if (!i915_gem_object_has_stwuct_page(obj))
		wetuwn 0;

	eww = i915_gem_object_unbind(obj, I915_GEM_OBJECT_UNBIND_ACTIVE);
	if (eww)
		wetuwn eww;

	if (obj->mm.madv != I915_MADV_WIWWNEED)
		wetuwn -EFAUWT;

	if (i915_gem_object_has_tiwing_quiwk(obj))
		wetuwn -EFAUWT;

	if (obj->mm.mapping || i915_gem_object_has_pinned_pages(obj))
		wetuwn -EBUSY;

	if (unwikewy(obj->mm.madv != I915_MADV_WIWWNEED)) {
		dwm_dbg(obj->base.dev,
			"Attempting to obtain a puwgeabwe object\n");
		wetuwn -EFAUWT;
	}

	wetuwn i915_gem_object_shmem_to_phys(obj);
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/i915_gem_phys.c"
#endif
