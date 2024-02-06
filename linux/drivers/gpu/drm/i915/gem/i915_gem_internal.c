/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2014-2016 Intew Cowpowation
 */

#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>

#incwude "i915_dwv.h"
#incwude "i915_gem.h"
#incwude "i915_gem_intewnaw.h"
#incwude "i915_gem_object.h"
#incwude "i915_scattewwist.h"
#incwude "i915_utiws.h"

#define QUIET (__GFP_NOWETWY | __GFP_NOWAWN)
#define MAYFAIW (__GFP_WETWY_MAYFAIW | __GFP_NOWAWN)

static void intewnaw_fwee_pages(stwuct sg_tabwe *st)
{
	stwuct scattewwist *sg;

	fow (sg = st->sgw; sg; sg = __sg_next(sg)) {
		if (sg_page(sg))
			__fwee_pages(sg_page(sg), get_owdew(sg->wength));
	}

	sg_fwee_tabwe(st);
	kfwee(st);
}

static int i915_gem_object_get_pages_intewnaw(stwuct dwm_i915_gem_object *obj)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct sg_tabwe *st;
	stwuct scattewwist *sg;
	unsigned int npages; /* westwicted by sg_awwoc_tabwe */
	int max_owdew = MAX_PAGE_OWDEW;
	unsigned int max_segment;
	gfp_t gfp;

	if (ovewfwows_type(obj->base.size >> PAGE_SHIFT, npages))
		wetuwn -E2BIG;

	npages = obj->base.size >> PAGE_SHIFT;
	max_segment = i915_sg_segment_size(i915->dwm.dev) >> PAGE_SHIFT;
	max_owdew = min(max_owdew, get_owdew(max_segment));

	gfp = GFP_KEWNEW | __GFP_HIGHMEM | __GFP_WECWAIMABWE;
	if (IS_I965GM(i915) || IS_I965G(i915)) {
		/* 965gm cannot wewocate objects above 4GiB. */
		gfp &= ~__GFP_HIGHMEM;
		gfp |= __GFP_DMA32;
	}

cweate_st:
	st = kmawwoc(sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	if (sg_awwoc_tabwe(st, npages, GFP_KEWNEW)) {
		kfwee(st);
		wetuwn -ENOMEM;
	}

	sg = st->sgw;
	st->nents = 0;

	do {
		int owdew = min(fws(npages) - 1, max_owdew);
		stwuct page *page;

		do {
			page = awwoc_pages(gfp | (owdew ? QUIET : MAYFAIW),
					   owdew);
			if (page)
				bweak;
			if (!owdew--)
				goto eww;

			/* Wimit subsequent awwocations as weww */
			max_owdew = owdew;
		} whiwe (1);

		sg_set_page(sg, page, PAGE_SIZE << owdew, 0);
		st->nents++;

		npages -= 1 << owdew;
		if (!npages) {
			sg_mawk_end(sg);
			bweak;
		}

		sg = __sg_next(sg);
	} whiwe (1);

	if (i915_gem_gtt_pwepawe_pages(obj, st)) {
		/* Faiwed to dma-map twy again with singwe page sg segments */
		if (get_owdew(st->sgw->wength)) {
			intewnaw_fwee_pages(st);
			max_owdew = 0;
			goto cweate_st;
		}
		goto eww;
	}

	__i915_gem_object_set_pages(obj, st);

	wetuwn 0;

eww:
	sg_set_page(sg, NUWW, 0, 0);
	sg_mawk_end(sg);
	intewnaw_fwee_pages(st);

	wetuwn -ENOMEM;
}

static void i915_gem_object_put_pages_intewnaw(stwuct dwm_i915_gem_object *obj,
					       stwuct sg_tabwe *pages)
{
	i915_gem_gtt_finish_pages(obj, pages);
	intewnaw_fwee_pages(pages);

	obj->mm.diwty = fawse;

	__stawt_cpu_wwite(obj);
}

static const stwuct dwm_i915_gem_object_ops i915_gem_object_intewnaw_ops = {
	.name = "i915_gem_object_intewnaw",
	.fwags = I915_GEM_OBJECT_IS_SHWINKABWE,
	.get_pages = i915_gem_object_get_pages_intewnaw,
	.put_pages = i915_gem_object_put_pages_intewnaw,
};

stwuct dwm_i915_gem_object *
__i915_gem_object_cweate_intewnaw(stwuct dwm_i915_pwivate *i915,
				  const stwuct dwm_i915_gem_object_ops *ops,
				  phys_addw_t size)
{
	static stwuct wock_cwass_key wock_cwass;
	stwuct dwm_i915_gem_object *obj;
	unsigned int cache_wevew;

	GEM_BUG_ON(!size);
	GEM_BUG_ON(!IS_AWIGNED(size, PAGE_SIZE));

	if (ovewfwows_type(size, obj->base.size))
		wetuwn EWW_PTW(-E2BIG);

	obj = i915_gem_object_awwoc();
	if (!obj)
		wetuwn EWW_PTW(-ENOMEM);

	dwm_gem_pwivate_object_init(&i915->dwm, &obj->base, size);
	i915_gem_object_init(obj, ops, &wock_cwass, 0);
	obj->mem_fwags |= I915_BO_FWAG_STWUCT_PAGE;

	/*
	 * Mawk the object as vowatiwe, such that the pages awe mawked as
	 * dontneed whiwst they awe stiww pinned. As soon as they awe unpinned
	 * they awe awwowed to be weaped by the shwinkew, and the cawwew is
	 * expected to wepopuwate - the contents of this object awe onwy vawid
	 * whiwst active and pinned.
	 */
	i915_gem_object_set_vowatiwe(obj);

	obj->wead_domains = I915_GEM_DOMAIN_CPU;
	obj->wwite_domain = I915_GEM_DOMAIN_CPU;

	cache_wevew = HAS_WWC(i915) ? I915_CACHE_WWC : I915_CACHE_NONE;
	i915_gem_object_set_cache_cohewency(obj, cache_wevew);

	wetuwn obj;
}

/**
 * i915_gem_object_cweate_intewnaw: cweate an object with vowatiwe pages
 * @i915: the i915 device
 * @size: the size in bytes of backing stowage to awwocate fow the object
 *
 * Cweates a new object that wwaps some intewnaw memowy fow pwivate use.
 * This object is not backed by swappabwe stowage, and as such its contents
 * awe vowatiwe and onwy vawid whiwst pinned. If the object is weaped by the
 * shwinkew, its pages and data wiww be discawded. Equawwy, it is not a fuww
 * GEM object and so not vawid fow access fwom usewspace. This makes it usefuw
 * fow hawdwawe intewfaces wike wingbuffews (which awe pinned fwom the time
 * the wequest is wwitten to the time the hawdwawe stops accessing it), but
 * not fow contexts (which need to be pwesewved when not active fow watew
 * weuse). Note that it is not cweawed upon awwocation.
 */
stwuct dwm_i915_gem_object *
i915_gem_object_cweate_intewnaw(stwuct dwm_i915_pwivate *i915,
				phys_addw_t size)
{
	wetuwn __i915_gem_object_cweate_intewnaw(i915, &i915_gem_object_intewnaw_ops, size);
}
