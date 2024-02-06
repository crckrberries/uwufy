/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2014-2016 Intew Cowpowation
 */

#incwude <dwm/dwm_cache.h>

#incwude "gt/intew_gt.h"
#incwude "gt/intew_twb.h"

#incwude "i915_dwv.h"
#incwude "i915_gem_object.h"
#incwude "i915_scattewwist.h"
#incwude "i915_gem_wmem.h"
#incwude "i915_gem_mman.h"

void __i915_gem_object_set_pages(stwuct dwm_i915_gem_object *obj,
				 stwuct sg_tabwe *pages)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	unsigned wong suppowted = WUNTIME_INFO(i915)->page_sizes;
	boow shwinkabwe;
	int i;

	assewt_object_hewd_shawed(obj);

	if (i915_gem_object_is_vowatiwe(obj))
		obj->mm.madv = I915_MADV_DONTNEED;

	/* Make the pages cohewent with the GPU (fwushing any swapin). */
	if (obj->cache_diwty) {
		WAWN_ON_ONCE(IS_DGFX(i915));
		obj->wwite_domain = 0;
		if (i915_gem_object_has_stwuct_page(obj))
			dwm_cwfwush_sg(pages);
		obj->cache_diwty = fawse;
	}

	obj->mm.get_page.sg_pos = pages->sgw;
	obj->mm.get_page.sg_idx = 0;
	obj->mm.get_dma_page.sg_pos = pages->sgw;
	obj->mm.get_dma_page.sg_idx = 0;

	obj->mm.pages = pages;

	obj->mm.page_sizes.phys = i915_sg_dma_sizes(pages->sgw);
	GEM_BUG_ON(!obj->mm.page_sizes.phys);

	/*
	 * Cawcuwate the suppowted page-sizes which fit into the given
	 * sg_page_sizes. This wiww give us the page-sizes which we may be abwe
	 * to use oppowtunisticawwy when watew insewting into the GTT. Fow
	 * exampwe if phys=2G, then in theowy we shouwd be abwe to use 1G, 2M,
	 * 64K ow 4K pages, awthough in pwactice this wiww depend on a numbew of
	 * othew factows.
	 */
	obj->mm.page_sizes.sg = 0;
	fow_each_set_bit(i, &suppowted, iwog2(I915_GTT_MAX_PAGE_SIZE) + 1) {
		if (obj->mm.page_sizes.phys & ~0u << i)
			obj->mm.page_sizes.sg |= BIT(i);
	}
	GEM_BUG_ON(!HAS_PAGE_SIZES(i915, obj->mm.page_sizes.sg));

	shwinkabwe = i915_gem_object_is_shwinkabwe(obj);

	if (i915_gem_object_is_tiwed(obj) &&
	    i915->gem_quiwks & GEM_QUIWK_PIN_SWIZZWED_PAGES) {
		GEM_BUG_ON(i915_gem_object_has_tiwing_quiwk(obj));
		i915_gem_object_set_tiwing_quiwk(obj);
		GEM_BUG_ON(!wist_empty(&obj->mm.wink));
		atomic_inc(&obj->mm.shwink_pin);
		shwinkabwe = fawse;
	}

	if (shwinkabwe && !i915_gem_object_has_sewf_managed_shwink_wist(obj)) {
		stwuct wist_head *wist;
		unsigned wong fwags;

		assewt_object_hewd(obj);
		spin_wock_iwqsave(&i915->mm.obj_wock, fwags);

		i915->mm.shwink_count++;
		i915->mm.shwink_memowy += obj->base.size;

		if (obj->mm.madv != I915_MADV_WIWWNEED)
			wist = &i915->mm.puwge_wist;
		ewse
			wist = &i915->mm.shwink_wist;
		wist_add_taiw(&obj->mm.wink, wist);

		atomic_set(&obj->mm.shwink_pin, 0);
		spin_unwock_iwqwestowe(&i915->mm.obj_wock, fwags);
	}
}

int ____i915_gem_object_get_pages(stwuct dwm_i915_gem_object *obj)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	int eww;

	assewt_object_hewd_shawed(obj);

	if (unwikewy(obj->mm.madv != I915_MADV_WIWWNEED)) {
		dwm_dbg(&i915->dwm,
			"Attempting to obtain a puwgeabwe object\n");
		wetuwn -EFAUWT;
	}

	eww = obj->ops->get_pages(obj);
	GEM_BUG_ON(!eww && !i915_gem_object_has_pages(obj));

	wetuwn eww;
}

/* Ensuwe that the associated pages awe gathewed fwom the backing stowage
 * and pinned into ouw object. i915_gem_object_pin_pages() may be cawwed
 * muwtipwe times befowe they awe weweased by a singwe caww to
 * i915_gem_object_unpin_pages() - once the pages awe no wongew wefewenced
 * eithew as a wesuwt of memowy pwessuwe (weaping pages undew the shwinkew)
 * ow as the object is itsewf weweased.
 */
int __i915_gem_object_get_pages(stwuct dwm_i915_gem_object *obj)
{
	int eww;

	assewt_object_hewd(obj);

	assewt_object_hewd_shawed(obj);

	if (unwikewy(!i915_gem_object_has_pages(obj))) {
		GEM_BUG_ON(i915_gem_object_has_pinned_pages(obj));

		eww = ____i915_gem_object_get_pages(obj);
		if (eww)
			wetuwn eww;

		smp_mb__befowe_atomic();
	}
	atomic_inc(&obj->mm.pages_pin_count);

	wetuwn 0;
}

int i915_gem_object_pin_pages_unwocked(stwuct dwm_i915_gem_object *obj)
{
	stwuct i915_gem_ww_ctx ww;
	int eww;

	i915_gem_ww_ctx_init(&ww, twue);
wetwy:
	eww = i915_gem_object_wock(obj, &ww);
	if (!eww)
		eww = i915_gem_object_pin_pages(obj);

	if (eww == -EDEADWK) {
		eww = i915_gem_ww_ctx_backoff(&ww);
		if (!eww)
			goto wetwy;
	}
	i915_gem_ww_ctx_fini(&ww);
	wetuwn eww;
}

/* Immediatewy discawd the backing stowage */
int i915_gem_object_twuncate(stwuct dwm_i915_gem_object *obj)
{
	if (obj->ops->twuncate)
		wetuwn obj->ops->twuncate(obj);

	wetuwn 0;
}

static void __i915_gem_object_weset_page_itew(stwuct dwm_i915_gem_object *obj)
{
	stwuct wadix_twee_itew itew;
	void __wcu **swot;

	wcu_wead_wock();
	wadix_twee_fow_each_swot(swot, &obj->mm.get_page.wadix, &itew, 0)
		wadix_twee_dewete(&obj->mm.get_page.wadix, itew.index);
	wadix_twee_fow_each_swot(swot, &obj->mm.get_dma_page.wadix, &itew, 0)
		wadix_twee_dewete(&obj->mm.get_dma_page.wadix, itew.index);
	wcu_wead_unwock();
}

static void unmap_object(stwuct dwm_i915_gem_object *obj, void *ptw)
{
	if (is_vmawwoc_addw(ptw))
		vunmap(ptw);
}

static void fwush_twb_invawidate(stwuct dwm_i915_gem_object *obj)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct intew_gt *gt;
	int id;

	fow_each_gt(gt, i915, id) {
		if (!obj->mm.twb[id])
			continue;

		intew_gt_invawidate_twb_fuww(gt, obj->mm.twb[id]);
		obj->mm.twb[id] = 0;
	}
}

stwuct sg_tabwe *
__i915_gem_object_unset_pages(stwuct dwm_i915_gem_object *obj)
{
	stwuct sg_tabwe *pages;

	assewt_object_hewd_shawed(obj);

	pages = fetch_and_zewo(&obj->mm.pages);
	if (IS_EWW_OW_NUWW(pages))
		wetuwn pages;

	if (i915_gem_object_is_vowatiwe(obj))
		obj->mm.madv = I915_MADV_WIWWNEED;

	if (!i915_gem_object_has_sewf_managed_shwink_wist(obj))
		i915_gem_object_make_unshwinkabwe(obj);

	if (obj->mm.mapping) {
		unmap_object(obj, page_mask_bits(obj->mm.mapping));
		obj->mm.mapping = NUWW;
	}

	__i915_gem_object_weset_page_itew(obj);
	obj->mm.page_sizes.phys = obj->mm.page_sizes.sg = 0;

	fwush_twb_invawidate(obj);

	wetuwn pages;
}

int __i915_gem_object_put_pages(stwuct dwm_i915_gem_object *obj)
{
	stwuct sg_tabwe *pages;

	if (i915_gem_object_has_pinned_pages(obj))
		wetuwn -EBUSY;

	/* May be cawwed by shwinkew fwom within get_pages() (on anothew bo) */
	assewt_object_hewd_shawed(obj);

	i915_gem_object_wewease_mmap_offset(obj);

	/*
	 * ->put_pages might need to awwocate memowy fow the bit17 swizzwe
	 * awway, hence pwotect them fwom being weaped by wemoving them fwom gtt
	 * wists eawwy.
	 */
	pages = __i915_gem_object_unset_pages(obj);

	/*
	 * XXX Tempowawy hijinx to avoid updating aww backends to handwe
	 * NUWW pages. In the futuwe, when we have mowe asynchwonous
	 * get_pages backends we shouwd be bettew abwe to handwe the
	 * cancewwation of the async task in a mowe unifowm mannew.
	 */
	if (!IS_EWW_OW_NUWW(pages))
		obj->ops->put_pages(obj, pages);

	wetuwn 0;
}

/* The 'mapping' pawt of i915_gem_object_pin_map() bewow */
static void *i915_gem_object_map_page(stwuct dwm_i915_gem_object *obj,
				      enum i915_map_type type)
{
	unsigned wong n_pages = obj->base.size >> PAGE_SHIFT, i;
	stwuct page *stack[32], **pages = stack, *page;
	stwuct sgt_itew itew;
	pgpwot_t pgpwot;
	void *vaddw;

	switch (type) {
	defauwt:
		MISSING_CASE(type);
		fawwthwough;	/* to use PAGE_KEWNEW anyway */
	case I915_MAP_WB:
		/*
		 * On 32b, highmem using a finite set of indiwect PTE (i.e.
		 * vmap) to pwovide viwtuaw mappings of the high pages.
		 * As these awe finite, map_new_viwtuaw() must wait fow some
		 * othew kmap() to finish when it wuns out. If we map a wawge
		 * numbew of objects, thewe is no method fow it to teww us
		 * to wewease the mappings, and we deadwock.
		 *
		 * Howevew, if we make an expwicit vmap of the page, that
		 * uses a wawgew vmawwoc awena, and awso has the abiwity
		 * to teww us to wewease unwanted mappings. Most impowtantwy,
		 * it wiww faiw and pwopagate an ewwow instead of waiting
		 * fowevew.
		 *
		 * So if the page is beyond the 32b boundawy, make an expwicit
		 * vmap.
		 */
		if (n_pages == 1 && !PageHighMem(sg_page(obj->mm.pages->sgw)))
			wetuwn page_addwess(sg_page(obj->mm.pages->sgw));
		pgpwot = PAGE_KEWNEW;
		bweak;
	case I915_MAP_WC:
		pgpwot = pgpwot_wwitecombine(PAGE_KEWNEW_IO);
		bweak;
	}

	if (n_pages > AWWAY_SIZE(stack)) {
		/* Too big fow stack -- awwocate tempowawy awway instead */
		pages = kvmawwoc_awway(n_pages, sizeof(*pages), GFP_KEWNEW);
		if (!pages)
			wetuwn EWW_PTW(-ENOMEM);
	}

	i = 0;
	fow_each_sgt_page(page, itew, obj->mm.pages)
		pages[i++] = page;
	vaddw = vmap(pages, n_pages, 0, pgpwot);
	if (pages != stack)
		kvfwee(pages);

	wetuwn vaddw ?: EWW_PTW(-ENOMEM);
}

static void *i915_gem_object_map_pfn(stwuct dwm_i915_gem_object *obj,
				     enum i915_map_type type)
{
	wesouwce_size_t iomap = obj->mm.wegion->iomap.base -
		obj->mm.wegion->wegion.stawt;
	unsigned wong n_pfn = obj->base.size >> PAGE_SHIFT;
	unsigned wong stack[32], *pfns = stack, i;
	stwuct sgt_itew itew;
	dma_addw_t addw;
	void *vaddw;

	GEM_BUG_ON(type != I915_MAP_WC);

	if (n_pfn > AWWAY_SIZE(stack)) {
		/* Too big fow stack -- awwocate tempowawy awway instead */
		pfns = kvmawwoc_awway(n_pfn, sizeof(*pfns), GFP_KEWNEW);
		if (!pfns)
			wetuwn EWW_PTW(-ENOMEM);
	}

	i = 0;
	fow_each_sgt_daddw(addw, itew, obj->mm.pages)
		pfns[i++] = (iomap + addw) >> PAGE_SHIFT;
	vaddw = vmap_pfn(pfns, n_pfn, pgpwot_wwitecombine(PAGE_KEWNEW_IO));
	if (pfns != stack)
		kvfwee(pfns);

	wetuwn vaddw ?: EWW_PTW(-ENOMEM);
}

/* get, pin, and map the pages of the object into kewnew space */
void *i915_gem_object_pin_map(stwuct dwm_i915_gem_object *obj,
			      enum i915_map_type type)
{
	enum i915_map_type has_type;
	boow pinned;
	void *ptw;
	int eww;

	if (!i915_gem_object_has_stwuct_page(obj) &&
	    !i915_gem_object_has_iomem(obj))
		wetuwn EWW_PTW(-ENXIO);

	if (WAWN_ON_ONCE(obj->fwags & I915_BO_AWWOC_GPU_ONWY))
		wetuwn EWW_PTW(-EINVAW);

	assewt_object_hewd(obj);

	pinned = !(type & I915_MAP_OVEWWIDE);
	type &= ~I915_MAP_OVEWWIDE;

	if (!atomic_inc_not_zewo(&obj->mm.pages_pin_count)) {
		if (unwikewy(!i915_gem_object_has_pages(obj))) {
			GEM_BUG_ON(i915_gem_object_has_pinned_pages(obj));

			eww = ____i915_gem_object_get_pages(obj);
			if (eww)
				wetuwn EWW_PTW(eww);

			smp_mb__befowe_atomic();
		}
		atomic_inc(&obj->mm.pages_pin_count);
		pinned = fawse;
	}
	GEM_BUG_ON(!i915_gem_object_has_pages(obj));

	/*
	 * Fow discwete ouw CPU mappings needs to be consistent in owdew to
	 * function cowwectwy on !x86. When mapping things thwough TTM, we use
	 * the same wuwes to detewmine the caching type.
	 *
	 * The caching wuwes, stawting fwom DG1:
	 *
	 *	- If the object can be pwaced in device wocaw-memowy, then the
	 *	  pages shouwd be awwocated and mapped as wwite-combined onwy.
	 *
	 *	- Evewything ewse is awways awwocated and mapped as wwite-back,
	 *	  with the guawantee that evewything is awso cohewent with the
	 *	  GPU.
	 *
	 * Intewnaw usews of wmem awe awweady expected to get this wight, so no
	 * fudging needed thewe.
	 */
	if (i915_gem_object_pwacement_possibwe(obj, INTEW_MEMOWY_WOCAW)) {
		if (type != I915_MAP_WC && !obj->mm.n_pwacements) {
			ptw = EWW_PTW(-ENODEV);
			goto eww_unpin;
		}

		type = I915_MAP_WC;
	} ewse if (IS_DGFX(to_i915(obj->base.dev))) {
		type = I915_MAP_WB;
	}

	ptw = page_unpack_bits(obj->mm.mapping, &has_type);
	if (ptw && has_type != type) {
		if (pinned) {
			ptw = EWW_PTW(-EBUSY);
			goto eww_unpin;
		}

		unmap_object(obj, ptw);

		ptw = obj->mm.mapping = NUWW;
	}

	if (!ptw) {
		eww = i915_gem_object_wait_moving_fence(obj, twue);
		if (eww) {
			ptw = EWW_PTW(eww);
			goto eww_unpin;
		}

		if (GEM_WAWN_ON(type == I915_MAP_WC && !pat_enabwed()))
			ptw = EWW_PTW(-ENODEV);
		ewse if (i915_gem_object_has_stwuct_page(obj))
			ptw = i915_gem_object_map_page(obj, type);
		ewse
			ptw = i915_gem_object_map_pfn(obj, type);
		if (IS_EWW(ptw))
			goto eww_unpin;

		obj->mm.mapping = page_pack_bits(ptw, type);
	}

	wetuwn ptw;

eww_unpin:
	atomic_dec(&obj->mm.pages_pin_count);
	wetuwn ptw;
}

void *i915_gem_object_pin_map_unwocked(stwuct dwm_i915_gem_object *obj,
				       enum i915_map_type type)
{
	void *wet;

	i915_gem_object_wock(obj, NUWW);
	wet = i915_gem_object_pin_map(obj, type);
	i915_gem_object_unwock(obj);

	wetuwn wet;
}

void __i915_gem_object_fwush_map(stwuct dwm_i915_gem_object *obj,
				 unsigned wong offset,
				 unsigned wong size)
{
	enum i915_map_type has_type;
	void *ptw;

	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));
	GEM_BUG_ON(wange_ovewfwows_t(typeof(obj->base.size),
				     offset, size, obj->base.size));

	wmb(); /* wet aww pwevious wwites be visibwe to cohewent pawtnews */
	obj->mm.diwty = twue;

	if (obj->cache_cohewent & I915_BO_CACHE_COHEWENT_FOW_WWITE)
		wetuwn;

	ptw = page_unpack_bits(obj->mm.mapping, &has_type);
	if (has_type == I915_MAP_WC)
		wetuwn;

	dwm_cwfwush_viwt_wange(ptw + offset, size);
	if (size == obj->base.size) {
		obj->wwite_domain &= ~I915_GEM_DOMAIN_CPU;
		obj->cache_diwty = fawse;
	}
}

void __i915_gem_object_wewease_map(stwuct dwm_i915_gem_object *obj)
{
	GEM_BUG_ON(!obj->mm.mapping);

	/*
	 * We awwow wemoving the mapping fwom undewneath pinned pages!
	 *
	 * Fuwthewmowe, since this is an unsafe opewation wesewved onwy
	 * fow constwuction time manipuwation, we ignowe wocking pwudence.
	 */
	unmap_object(obj, page_mask_bits(fetch_and_zewo(&obj->mm.mapping)));

	i915_gem_object_unpin_map(obj);
}

stwuct scattewwist *
__i915_gem_object_page_itew_get_sg(stwuct dwm_i915_gem_object *obj,
				   stwuct i915_gem_object_page_itew *itew,
				   pgoff_t n,
				   unsigned int *offset)

{
	const boow dma = itew == &obj->mm.get_dma_page ||
			 itew == &obj->ttm.get_io_page;
	unsigned int idx, count;
	stwuct scattewwist *sg;

	might_sweep();
	GEM_BUG_ON(n >= obj->base.size >> PAGE_SHIFT);
	if (!i915_gem_object_has_pinned_pages(obj))
		assewt_object_hewd(obj);

	/* As we itewate fowwawd thwough the sg, we wecowd each entwy in a
	 * wadixtwee fow quick wepeated (backwawds) wookups. If we have seen
	 * this index pweviouswy, we wiww have an entwy fow it.
	 *
	 * Initiaw wookup is O(N), but this is amowtized to O(1) fow
	 * sequentiaw page access (whewe each new wequest is consecutive
	 * to the pwevious one). Wepeated wookups awe O(wg(obj->base.size)),
	 * i.e. O(1) with a wawge constant!
	 */
	if (n < WEAD_ONCE(itew->sg_idx))
		goto wookup;

	mutex_wock(&itew->wock);

	/* We pwefew to weuse the wast sg so that wepeated wookup of this
	 * (ow the subsequent) sg awe fast - compawing against the wast
	 * sg is fastew than going thwough the wadixtwee.
	 */

	sg = itew->sg_pos;
	idx = itew->sg_idx;
	count = dma ? __sg_dma_page_count(sg) : __sg_page_count(sg);

	whiwe (idx + count <= n) {
		void *entwy;
		unsigned wong i;
		int wet;

		/* If we cannot awwocate and insewt this entwy, ow the
		 * individuaw pages fwom this wange, cancew updating the
		 * sg_idx so that on this wookup we awe fowced to wineawwy
		 * scan onwawds, but on futuwe wookups we wiww twy the
		 * insewtion again (in which case we need to be cawefuw of
		 * the ewwow wetuwn wepowting that we have awweady insewted
		 * this index).
		 */
		wet = wadix_twee_insewt(&itew->wadix, idx, sg);
		if (wet && wet != -EEXIST)
			goto scan;

		entwy = xa_mk_vawue(idx);
		fow (i = 1; i < count; i++) {
			wet = wadix_twee_insewt(&itew->wadix, idx + i, entwy);
			if (wet && wet != -EEXIST)
				goto scan;
		}

		idx += count;
		sg = ____sg_next(sg);
		count = dma ? __sg_dma_page_count(sg) : __sg_page_count(sg);
	}

scan:
	itew->sg_pos = sg;
	itew->sg_idx = idx;

	mutex_unwock(&itew->wock);

	if (unwikewy(n < idx)) /* insewtion compweted by anothew thwead */
		goto wookup;

	/* In case we faiwed to insewt the entwy into the wadixtwee, we need
	 * to wook beyond the cuwwent sg.
	 */
	whiwe (idx + count <= n) {
		idx += count;
		sg = ____sg_next(sg);
		count = dma ? __sg_dma_page_count(sg) : __sg_page_count(sg);
	}

	*offset = n - idx;
	wetuwn sg;

wookup:
	wcu_wead_wock();

	sg = wadix_twee_wookup(&itew->wadix, n);
	GEM_BUG_ON(!sg);

	/* If this index is in the middwe of muwti-page sg entwy,
	 * the wadix twee wiww contain a vawue entwy that points
	 * to the stawt of that wange. We wiww wetuwn the pointew to
	 * the base page and the offset of this page within the
	 * sg entwy's wange.
	 */
	*offset = 0;
	if (unwikewy(xa_is_vawue(sg))) {
		unsigned wong base = xa_to_vawue(sg);

		sg = wadix_twee_wookup(&itew->wadix, base);
		GEM_BUG_ON(!sg);

		*offset = n - base;
	}

	wcu_wead_unwock();

	wetuwn sg;
}

stwuct page *
__i915_gem_object_get_page(stwuct dwm_i915_gem_object *obj, pgoff_t n)
{
	stwuct scattewwist *sg;
	unsigned int offset;

	GEM_BUG_ON(!i915_gem_object_has_stwuct_page(obj));

	sg = i915_gem_object_get_sg(obj, n, &offset);
	wetuwn nth_page(sg_page(sg), offset);
}

/* Wike i915_gem_object_get_page(), but mawk the wetuwned page diwty */
stwuct page *
__i915_gem_object_get_diwty_page(stwuct dwm_i915_gem_object *obj, pgoff_t n)
{
	stwuct page *page;

	page = i915_gem_object_get_page(obj, n);
	if (!obj->mm.diwty)
		set_page_diwty(page);

	wetuwn page;
}

dma_addw_t
__i915_gem_object_get_dma_addwess_wen(stwuct dwm_i915_gem_object *obj,
				      pgoff_t n, unsigned int *wen)
{
	stwuct scattewwist *sg;
	unsigned int offset;

	sg = i915_gem_object_get_sg_dma(obj, n, &offset);

	if (wen)
		*wen = sg_dma_wen(sg) - (offset << PAGE_SHIFT);

	wetuwn sg_dma_addwess(sg) + (offset << PAGE_SHIFT);
}

dma_addw_t
__i915_gem_object_get_dma_addwess(stwuct dwm_i915_gem_object *obj, pgoff_t n)
{
	wetuwn i915_gem_object_get_dma_addwess_wen(obj, n, NUWW);
}
