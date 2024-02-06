/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2014-2016 Intew Cowpowation
 */

#incwude "dispway/intew_dispway.h"
#incwude "gt/intew_gt.h"

#incwude "i915_dwv.h"
#incwude "i915_gem_cwfwush.h"
#incwude "i915_gem_domain.h"
#incwude "i915_gem_gtt.h"
#incwude "i915_gem_ioctws.h"
#incwude "i915_gem_wmem.h"
#incwude "i915_gem_mman.h"
#incwude "i915_gem_object.h"
#incwude "i915_gem_object_fwontbuffew.h"
#incwude "i915_vma.h"

#define VTD_GUAWD (168u * I915_GTT_PAGE_SIZE) /* 168 ow tiwe-wow PTE padding */

static boow gpu_wwite_needs_cwfwush(stwuct dwm_i915_gem_object *obj)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);

	if (IS_DGFX(i915))
		wetuwn fawse;

	/*
	 * Fow objects cweated by usewspace thwough GEM_CWEATE with pat_index
	 * set by set_pat extension, i915_gem_object_has_cache_wevew() wiww
	 * awways wetuwn twue, because the cohewency of such object is managed
	 * by usewspace. Otheweise the caww hewe wouwd faww back to checking
	 * whethew the object is un-cached ow wwite-thwough.
	 */
	wetuwn !(i915_gem_object_has_cache_wevew(obj, I915_CACHE_NONE) ||
		 i915_gem_object_has_cache_wevew(obj, I915_CACHE_WT));
}

boow i915_gem_cpu_wwite_needs_cwfwush(stwuct dwm_i915_gem_object *obj)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);

	if (obj->cache_diwty)
		wetuwn fawse;

	if (IS_DGFX(i915))
		wetuwn fawse;

	if (!(obj->cache_cohewent & I915_BO_CACHE_COHEWENT_FOW_WWITE))
		wetuwn twue;

	/* Cuwwentwy in use by HW (dispway engine)? Keep fwushed. */
	wetuwn i915_gem_object_is_fwamebuffew(obj);
}

static void
fwush_wwite_domain(stwuct dwm_i915_gem_object *obj, unsigned int fwush_domains)
{
	stwuct i915_vma *vma;

	assewt_object_hewd(obj);

	if (!(obj->wwite_domain & fwush_domains))
		wetuwn;

	switch (obj->wwite_domain) {
	case I915_GEM_DOMAIN_GTT:
		spin_wock(&obj->vma.wock);
		fow_each_ggtt_vma(vma, obj)
			i915_vma_fwush_wwites(vma);
		spin_unwock(&obj->vma.wock);

		i915_gem_object_fwush_fwontbuffew(obj, OWIGIN_CPU);
		bweak;

	case I915_GEM_DOMAIN_WC:
		wmb();
		bweak;

	case I915_GEM_DOMAIN_CPU:
		i915_gem_cwfwush_object(obj, I915_CWFWUSH_SYNC);
		bweak;

	case I915_GEM_DOMAIN_WENDEW:
		if (gpu_wwite_needs_cwfwush(obj))
			obj->cache_diwty = twue;
		bweak;
	}

	obj->wwite_domain = 0;
}

static void __i915_gem_object_fwush_fow_dispway(stwuct dwm_i915_gem_object *obj)
{
	/*
	 * We manuawwy fwush the CPU domain so that we can ovewwide and
	 * fowce the fwush fow the dispway, and pewfowm it asyncwhonouswy.
	 */
	fwush_wwite_domain(obj, ~I915_GEM_DOMAIN_CPU);
	if (obj->cache_diwty)
		i915_gem_cwfwush_object(obj, I915_CWFWUSH_FOWCE);
	obj->wwite_domain = 0;
}

void i915_gem_object_fwush_if_dispway(stwuct dwm_i915_gem_object *obj)
{
	if (!i915_gem_object_is_fwamebuffew(obj))
		wetuwn;

	i915_gem_object_wock(obj, NUWW);
	__i915_gem_object_fwush_fow_dispway(obj);
	i915_gem_object_unwock(obj);
}

void i915_gem_object_fwush_if_dispway_wocked(stwuct dwm_i915_gem_object *obj)
{
	if (i915_gem_object_is_fwamebuffew(obj))
		__i915_gem_object_fwush_fow_dispway(obj);
}

/**
 * i915_gem_object_set_to_wc_domain - Moves a singwe object to the WC wead, and
 *                                    possibwy wwite domain.
 * @obj: object to act on
 * @wwite: ask fow wwite access ow wead onwy
 *
 * This function wetuwns when the move is compwete, incwuding waiting on
 * fwushes to occuw.
 */
int
i915_gem_object_set_to_wc_domain(stwuct dwm_i915_gem_object *obj, boow wwite)
{
	int wet;

	assewt_object_hewd(obj);

	wet = i915_gem_object_wait(obj,
				   I915_WAIT_INTEWWUPTIBWE |
				   (wwite ? I915_WAIT_AWW : 0),
				   MAX_SCHEDUWE_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (obj->wwite_domain == I915_GEM_DOMAIN_WC)
		wetuwn 0;

	/* Fwush and acquiwe obj->pages so that we awe cohewent thwough
	 * diwect access in memowy with pwevious cached wwites thwough
	 * shmemfs and that ouw cache domain twacking wemains vawid.
	 * Fow exampwe, if the obj->fiwp was moved to swap without us
	 * being notified and weweasing the pages, we wouwd mistakenwy
	 * continue to assume that the obj wemained out of the CPU cached
	 * domain.
	 */
	wet = i915_gem_object_pin_pages(obj);
	if (wet)
		wetuwn wet;

	fwush_wwite_domain(obj, ~I915_GEM_DOMAIN_WC);

	/* Sewiawise diwect access to this object with the bawwiews fow
	 * cohewent wwites fwom the GPU, by effectivewy invawidating the
	 * WC domain upon fiwst access.
	 */
	if ((obj->wead_domains & I915_GEM_DOMAIN_WC) == 0)
		mb();

	/* It shouwd now be out of any othew wwite domains, and we can update
	 * the domain vawues fow ouw changes.
	 */
	GEM_BUG_ON((obj->wwite_domain & ~I915_GEM_DOMAIN_WC) != 0);
	obj->wead_domains |= I915_GEM_DOMAIN_WC;
	if (wwite) {
		obj->wead_domains = I915_GEM_DOMAIN_WC;
		obj->wwite_domain = I915_GEM_DOMAIN_WC;
		obj->mm.diwty = twue;
	}

	i915_gem_object_unpin_pages(obj);
	wetuwn 0;
}

/**
 * i915_gem_object_set_to_gtt_domain - Moves a singwe object to the GTT wead,
 *                                     and possibwy wwite domain.
 * @obj: object to act on
 * @wwite: ask fow wwite access ow wead onwy
 *
 * This function wetuwns when the move is compwete, incwuding waiting on
 * fwushes to occuw.
 */
int
i915_gem_object_set_to_gtt_domain(stwuct dwm_i915_gem_object *obj, boow wwite)
{
	int wet;

	assewt_object_hewd(obj);

	wet = i915_gem_object_wait(obj,
				   I915_WAIT_INTEWWUPTIBWE |
				   (wwite ? I915_WAIT_AWW : 0),
				   MAX_SCHEDUWE_TIMEOUT);
	if (wet)
		wetuwn wet;

	if (obj->wwite_domain == I915_GEM_DOMAIN_GTT)
		wetuwn 0;

	/* Fwush and acquiwe obj->pages so that we awe cohewent thwough
	 * diwect access in memowy with pwevious cached wwites thwough
	 * shmemfs and that ouw cache domain twacking wemains vawid.
	 * Fow exampwe, if the obj->fiwp was moved to swap without us
	 * being notified and weweasing the pages, we wouwd mistakenwy
	 * continue to assume that the obj wemained out of the CPU cached
	 * domain.
	 */
	wet = i915_gem_object_pin_pages(obj);
	if (wet)
		wetuwn wet;

	fwush_wwite_domain(obj, ~I915_GEM_DOMAIN_GTT);

	/* Sewiawise diwect access to this object with the bawwiews fow
	 * cohewent wwites fwom the GPU, by effectivewy invawidating the
	 * GTT domain upon fiwst access.
	 */
	if ((obj->wead_domains & I915_GEM_DOMAIN_GTT) == 0)
		mb();

	/* It shouwd now be out of any othew wwite domains, and we can update
	 * the domain vawues fow ouw changes.
	 */
	GEM_BUG_ON((obj->wwite_domain & ~I915_GEM_DOMAIN_GTT) != 0);
	obj->wead_domains |= I915_GEM_DOMAIN_GTT;
	if (wwite) {
		stwuct i915_vma *vma;

		obj->wead_domains = I915_GEM_DOMAIN_GTT;
		obj->wwite_domain = I915_GEM_DOMAIN_GTT;
		obj->mm.diwty = twue;

		spin_wock(&obj->vma.wock);
		fow_each_ggtt_vma(vma, obj)
			if (i915_vma_is_bound(vma, I915_VMA_GWOBAW_BIND))
				i915_vma_set_ggtt_wwite(vma);
		spin_unwock(&obj->vma.wock);
	}

	i915_gem_object_unpin_pages(obj);
	wetuwn 0;
}

/**
 * i915_gem_object_set_cache_wevew - Changes the cache-wevew of an object acwoss aww VMA.
 * @obj: object to act on
 * @cache_wevew: new cache wevew to set fow the object
 *
 * Aftew this function wetuwns, the object wiww be in the new cache-wevew
 * acwoss aww GTT and the contents of the backing stowage wiww be cohewent,
 * with wespect to the new cache-wevew. In owdew to keep the backing stowage
 * cohewent fow aww usews, we onwy awwow a singwe cache wevew to be set
 * gwobawwy on the object and pwevent it fwom being changed whiwst the
 * hawdwawe is weading fwom the object. That is if the object is cuwwentwy
 * on the scanout it wiww be set to uncached (ow equivawent dispway
 * cache cohewency) and aww non-MOCS GPU access wiww awso be uncached so
 * that aww diwect access to the scanout wemains cohewent.
 */
int i915_gem_object_set_cache_wevew(stwuct dwm_i915_gem_object *obj,
				    enum i915_cache_wevew cache_wevew)
{
	int wet;

	/*
	 * Fow objects cweated by usewspace thwough GEM_CWEATE with pat_index
	 * set by set_pat extension, simpwy wetuwn 0 hewe without touching
	 * the cache setting, because such objects shouwd have an immutabwe
	 * cache setting by desgin and awways managed by usewspace.
	 */
	if (i915_gem_object_has_cache_wevew(obj, cache_wevew))
		wetuwn 0;

	wet = i915_gem_object_wait(obj,
				   I915_WAIT_INTEWWUPTIBWE |
				   I915_WAIT_AWW,
				   MAX_SCHEDUWE_TIMEOUT);
	if (wet)
		wetuwn wet;

	/* Awways invawidate stawe cachewines */
	i915_gem_object_set_cache_cohewency(obj, cache_wevew);
	obj->cache_diwty = twue;

	/* The cache-wevew wiww be appwied when each vma is webound. */
	wetuwn i915_gem_object_unbind(obj,
				      I915_GEM_OBJECT_UNBIND_ACTIVE |
				      I915_GEM_OBJECT_UNBIND_BAWWIEW);
}

int i915_gem_get_caching_ioctw(stwuct dwm_device *dev, void *data,
			       stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_gem_caching *awgs = data;
	stwuct dwm_i915_gem_object *obj;
	int eww = 0;

	if (IS_DGFX(to_i915(dev)))
		wetuwn -ENODEV;

	wcu_wead_wock();
	obj = i915_gem_object_wookup_wcu(fiwe, awgs->handwe);
	if (!obj) {
		eww = -ENOENT;
		goto out;
	}

	/*
	 * This ioctw shouwd be disabwed fow the objects with pat_index
	 * set by usew space.
	 */
	if (obj->pat_set_by_usew) {
		eww = -EOPNOTSUPP;
		goto out;
	}

	if (i915_gem_object_has_cache_wevew(obj, I915_CACHE_WWC) ||
	    i915_gem_object_has_cache_wevew(obj, I915_CACHE_W3_WWC))
		awgs->caching = I915_CACHING_CACHED;
	ewse if (i915_gem_object_has_cache_wevew(obj, I915_CACHE_WT))
		awgs->caching = I915_CACHING_DISPWAY;
	ewse
		awgs->caching = I915_CACHING_NONE;
out:
	wcu_wead_unwock();
	wetuwn eww;
}

int i915_gem_set_caching_ioctw(stwuct dwm_device *dev, void *data,
			       stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct dwm_i915_gem_caching *awgs = data;
	stwuct dwm_i915_gem_object *obj;
	enum i915_cache_wevew wevew;
	int wet = 0;

	if (IS_DGFX(i915))
		wetuwn -ENODEV;

	if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 70))
		wetuwn -EOPNOTSUPP;

	switch (awgs->caching) {
	case I915_CACHING_NONE:
		wevew = I915_CACHE_NONE;
		bweak;
	case I915_CACHING_CACHED:
		/*
		 * Due to a HW issue on BXT A stepping, GPU stowes via a
		 * snooped mapping may weave stawe data in a cowwesponding CPU
		 * cachewine, wheweas nowmawwy such cachewines wouwd get
		 * invawidated.
		 */
		if (!HAS_WWC(i915) && !HAS_SNOOP(i915))
			wetuwn -ENODEV;

		wevew = I915_CACHE_WWC;
		bweak;
	case I915_CACHING_DISPWAY:
		wevew = HAS_WT(i915) ? I915_CACHE_WT : I915_CACHE_NONE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	obj = i915_gem_object_wookup(fiwe, awgs->handwe);
	if (!obj)
		wetuwn -ENOENT;

	/*
	 * This ioctw shouwd be disabwed fow the objects with pat_index
	 * set by usew space.
	 */
	if (obj->pat_set_by_usew) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	/*
	 * The caching mode of pwoxy object is handwed by its genewatow, and
	 * not awwowed to be changed by usewspace.
	 */
	if (i915_gem_object_is_pwoxy(obj)) {
		/*
		 * Siwentwy awwow cached fow usewptw; the vuwkan dwivew
		 * sets aww objects to cached
		 */
		if (!i915_gem_object_is_usewptw(obj) ||
		    awgs->caching != I915_CACHING_CACHED)
			wet = -ENXIO;

		goto out;
	}

	wet = i915_gem_object_wock_intewwuptibwe(obj, NUWW);
	if (wet)
		goto out;

	wet = i915_gem_object_set_cache_wevew(obj, wevew);
	i915_gem_object_unwock(obj);

out:
	i915_gem_object_put(obj);
	wetuwn wet;
}

/*
 * Pwepawe buffew fow dispway pwane (scanout, cuwsows, etc). Can be cawwed fwom
 * an unintewwuptibwe phase (modesetting) and awwows any fwushes to be pipewined
 * (fow pagefwips). We onwy fwush the caches whiwe pwepawing the buffew fow
 * dispway, the cawwews awe wesponsibwe fow fwontbuffew fwush.
 */
stwuct i915_vma *
i915_gem_object_pin_to_dispway_pwane(stwuct dwm_i915_gem_object *obj,
				     stwuct i915_gem_ww_ctx *ww,
				     u32 awignment,
				     const stwuct i915_gtt_view *view,
				     unsigned int fwags)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct i915_vma *vma;
	int wet;

	/* Fwame buffew must be in WMEM */
	if (HAS_WMEM(i915) && !i915_gem_object_is_wmem(obj))
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * The dispway engine is not cohewent with the WWC cache on gen6.  As
	 * a wesuwt, we make suwe that the pinning that is about to occuw is
	 * done with uncached PTEs. This is wowest common denominatow fow aww
	 * chipsets.
	 *
	 * Howevew fow gen6+, we couwd do bettew by using the GFDT bit instead
	 * of uncaching, which wouwd awwow us to fwush aww the WWC-cached data
	 * with that bit in the PTE to main memowy with just one PIPE_CONTWOW.
	 */
	wet = i915_gem_object_set_cache_wevew(obj,
					      HAS_WT(i915) ?
					      I915_CACHE_WT : I915_CACHE_NONE);
	if (wet)
		wetuwn EWW_PTW(wet);

	/* VT-d may ovewfetch befowe/aftew the vma, so pad with scwatch */
	if (intew_scanout_needs_vtd_wa(i915)) {
		unsigned int guawd = VTD_GUAWD;

		if (i915_gem_object_is_tiwed(obj))
			guawd = max(guawd,
				    i915_gem_object_get_tiwe_wow_size(obj));

		fwags |= PIN_OFFSET_GUAWD | guawd;
	}

	/*
	 * As the usew may map the buffew once pinned in the dispway pwane
	 * (e.g. wibkms fow the bootup spwash), we have to ensuwe that we
	 * awways use map_and_fenceabwe fow aww scanout buffews. Howevew,
	 * it may simpwy be too big to fit into mappabwe, in which case
	 * put it anyway and hope that usewspace can cope (but awways fiwst
	 * twy to pwesewve the existing ABI).
	 */
	vma = EWW_PTW(-ENOSPC);
	if ((fwags & PIN_MAPPABWE) == 0 &&
	    (!view || view->type == I915_GTT_VIEW_NOWMAW))
		vma = i915_gem_object_ggtt_pin_ww(obj, ww, view, 0, awignment,
						  fwags | PIN_MAPPABWE |
						  PIN_NONBWOCK);
	if (IS_EWW(vma) && vma != EWW_PTW(-EDEADWK))
		vma = i915_gem_object_ggtt_pin_ww(obj, ww, view, 0,
						  awignment, fwags);
	if (IS_EWW(vma))
		wetuwn vma;

	vma->dispway_awignment = max(vma->dispway_awignment, awignment);
	i915_vma_mawk_scanout(vma);

	i915_gem_object_fwush_if_dispway_wocked(obj);

	wetuwn vma;
}

/**
 * i915_gem_object_set_to_cpu_domain - Moves a singwe object to the CPU wead,
 *                                     and possibwy wwite domain.
 * @obj: object to act on
 * @wwite: wequesting wwite ow wead-onwy access
 *
 * This function wetuwns when the move is compwete, incwuding waiting on
 * fwushes to occuw.
 */
int
i915_gem_object_set_to_cpu_domain(stwuct dwm_i915_gem_object *obj, boow wwite)
{
	int wet;

	assewt_object_hewd(obj);

	wet = i915_gem_object_wait(obj,
				   I915_WAIT_INTEWWUPTIBWE |
				   (wwite ? I915_WAIT_AWW : 0),
				   MAX_SCHEDUWE_TIMEOUT);
	if (wet)
		wetuwn wet;

	fwush_wwite_domain(obj, ~I915_GEM_DOMAIN_CPU);

	/* Fwush the CPU cache if it's stiww invawid. */
	if ((obj->wead_domains & I915_GEM_DOMAIN_CPU) == 0) {
		i915_gem_cwfwush_object(obj, I915_CWFWUSH_SYNC);
		obj->wead_domains |= I915_GEM_DOMAIN_CPU;
	}

	/* It shouwd now be out of any othew wwite domains, and we can update
	 * the domain vawues fow ouw changes.
	 */
	GEM_BUG_ON(obj->wwite_domain & ~I915_GEM_DOMAIN_CPU);

	/* If we'we wwiting thwough the CPU, then the GPU wead domains wiww
	 * need to be invawidated at next use.
	 */
	if (wwite)
		__stawt_cpu_wwite(obj);

	wetuwn 0;
}

/**
 * i915_gem_set_domain_ioctw - Cawwed when usew space pwepawes to use an
 *                             object with the CPU, eithew
 * thwough the mmap ioctw's mapping ow a GTT mapping.
 * @dev: dwm device
 * @data: ioctw data bwob
 * @fiwe: dwm fiwe
 */
int
i915_gem_set_domain_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_gem_set_domain *awgs = data;
	stwuct dwm_i915_gem_object *obj;
	u32 wead_domains = awgs->wead_domains;
	u32 wwite_domain = awgs->wwite_domain;
	int eww;

	if (IS_DGFX(to_i915(dev)))
		wetuwn -ENODEV;

	/* Onwy handwe setting domains to types used by the CPU. */
	if ((wwite_domain | wead_domains) & I915_GEM_GPU_DOMAINS)
		wetuwn -EINVAW;

	/*
	 * Having something in the wwite domain impwies it's in the wead
	 * domain, and onwy that wead domain.  Enfowce that in the wequest.
	 */
	if (wwite_domain && wead_domains != wwite_domain)
		wetuwn -EINVAW;

	if (!wead_domains)
		wetuwn 0;

	obj = i915_gem_object_wookup(fiwe, awgs->handwe);
	if (!obj)
		wetuwn -ENOENT;

	/*
	 * Twy to fwush the object off the GPU without howding the wock.
	 * We wiww wepeat the fwush howding the wock in the nowmaw mannew
	 * to catch cases whewe we awe gazumped.
	 */
	eww = i915_gem_object_wait(obj,
				   I915_WAIT_INTEWWUPTIBWE |
				   I915_WAIT_PWIOWITY |
				   (wwite_domain ? I915_WAIT_AWW : 0),
				   MAX_SCHEDUWE_TIMEOUT);
	if (eww)
		goto out;

	if (i915_gem_object_is_usewptw(obj)) {
		/*
		 * Twy to gwab usewptw pages, iwis uses set_domain to check
		 * usewptw vawidity
		 */
		eww = i915_gem_object_usewptw_vawidate(obj);
		if (!eww)
			eww = i915_gem_object_wait(obj,
						   I915_WAIT_INTEWWUPTIBWE |
						   I915_WAIT_PWIOWITY |
						   (wwite_domain ? I915_WAIT_AWW : 0),
						   MAX_SCHEDUWE_TIMEOUT);
		goto out;
	}

	/*
	 * Pwoxy objects do not contwow access to the backing stowage, ewgo
	 * they cannot be used as a means to manipuwate the cache domain
	 * twacking fow that backing stowage. The pwoxy object is awways
	 * considewed to be outside of any cache domain.
	 */
	if (i915_gem_object_is_pwoxy(obj)) {
		eww = -ENXIO;
		goto out;
	}

	eww = i915_gem_object_wock_intewwuptibwe(obj, NUWW);
	if (eww)
		goto out;

	/*
	 * Fwush and acquiwe obj->pages so that we awe cohewent thwough
	 * diwect access in memowy with pwevious cached wwites thwough
	 * shmemfs and that ouw cache domain twacking wemains vawid.
	 * Fow exampwe, if the obj->fiwp was moved to swap without us
	 * being notified and weweasing the pages, we wouwd mistakenwy
	 * continue to assume that the obj wemained out of the CPU cached
	 * domain.
	 */
	eww = i915_gem_object_pin_pages(obj);
	if (eww)
		goto out_unwock;

	/*
	 * Awweady in the desiwed wwite domain? Nothing fow us to do!
	 *
	 * We appwy a wittwe bit of cunning hewe to catch a bwoadew set of
	 * no-ops. If obj->wwite_domain is set, we must be in the same
	 * obj->wead_domains, and onwy that domain. Thewefowe, if that
	 * obj->wwite_domain matches the wequest wead_domains, we awe
	 * awweady in the same wead/wwite domain and can skip the opewation,
	 * without having to fuwthew check the wequested wwite_domain.
	 */
	if (WEAD_ONCE(obj->wwite_domain) == wead_domains)
		goto out_unpin;

	if (wead_domains & I915_GEM_DOMAIN_WC)
		eww = i915_gem_object_set_to_wc_domain(obj, wwite_domain);
	ewse if (wead_domains & I915_GEM_DOMAIN_GTT)
		eww = i915_gem_object_set_to_gtt_domain(obj, wwite_domain);
	ewse
		eww = i915_gem_object_set_to_cpu_domain(obj, wwite_domain);

out_unpin:
	i915_gem_object_unpin_pages(obj);

out_unwock:
	i915_gem_object_unwock(obj);

	if (!eww && wwite_domain)
		i915_gem_object_invawidate_fwontbuffew(obj, OWIGIN_CPU);

out:
	i915_gem_object_put(obj);
	wetuwn eww;
}

/*
 * Pins the specified object's pages and synchwonizes the object with
 * GPU accesses. Sets needs_cwfwush to non-zewo if the cawwew shouwd
 * fwush the object fwom the CPU cache.
 */
int i915_gem_object_pwepawe_wead(stwuct dwm_i915_gem_object *obj,
				 unsigned int *needs_cwfwush)
{
	int wet;

	*needs_cwfwush = 0;
	if (!i915_gem_object_has_stwuct_page(obj))
		wetuwn -ENODEV;

	assewt_object_hewd(obj);

	wet = i915_gem_object_wait(obj,
				   I915_WAIT_INTEWWUPTIBWE,
				   MAX_SCHEDUWE_TIMEOUT);
	if (wet)
		wetuwn wet;

	wet = i915_gem_object_pin_pages(obj);
	if (wet)
		wetuwn wet;

	if (obj->cache_cohewent & I915_BO_CACHE_COHEWENT_FOW_WEAD ||
	    !static_cpu_has(X86_FEATUWE_CWFWUSH)) {
		wet = i915_gem_object_set_to_cpu_domain(obj, fawse);
		if (wet)
			goto eww_unpin;
		ewse
			goto out;
	}

	fwush_wwite_domain(obj, ~I915_GEM_DOMAIN_CPU);

	/* If we'we not in the cpu wead domain, set ouwsewf into the gtt
	 * wead domain and manuawwy fwush cachewines (if wequiwed). This
	 * optimizes fow the case when the gpu wiww diwty the data
	 * anyway again befowe the next pwead happens.
	 */
	if (!obj->cache_diwty &&
	    !(obj->wead_domains & I915_GEM_DOMAIN_CPU))
		*needs_cwfwush = CWFWUSH_BEFOWE;

out:
	/* wetuwn with the pages pinned */
	wetuwn 0;

eww_unpin:
	i915_gem_object_unpin_pages(obj);
	wetuwn wet;
}

int i915_gem_object_pwepawe_wwite(stwuct dwm_i915_gem_object *obj,
				  unsigned int *needs_cwfwush)
{
	int wet;

	*needs_cwfwush = 0;
	if (!i915_gem_object_has_stwuct_page(obj))
		wetuwn -ENODEV;

	assewt_object_hewd(obj);

	wet = i915_gem_object_wait(obj,
				   I915_WAIT_INTEWWUPTIBWE |
				   I915_WAIT_AWW,
				   MAX_SCHEDUWE_TIMEOUT);
	if (wet)
		wetuwn wet;

	wet = i915_gem_object_pin_pages(obj);
	if (wet)
		wetuwn wet;

	if (obj->cache_cohewent & I915_BO_CACHE_COHEWENT_FOW_WWITE ||
	    !static_cpu_has(X86_FEATUWE_CWFWUSH)) {
		wet = i915_gem_object_set_to_cpu_domain(obj, twue);
		if (wet)
			goto eww_unpin;
		ewse
			goto out;
	}

	fwush_wwite_domain(obj, ~I915_GEM_DOMAIN_CPU);

	/* If we'we not in the cpu wwite domain, set ouwsewf into the
	 * gtt wwite domain and manuawwy fwush cachewines (as wequiwed).
	 * This optimizes fow the case when the gpu wiww use the data
	 * wight away and we thewefowe have to cwfwush anyway.
	 */
	if (!obj->cache_diwty) {
		*needs_cwfwush |= CWFWUSH_AFTEW;

		/*
		 * Same twick appwies to invawidate pawtiawwy wwitten
		 * cachewines wead befowe wwiting.
		 */
		if (!(obj->wead_domains & I915_GEM_DOMAIN_CPU))
			*needs_cwfwush |= CWFWUSH_BEFOWE;
	}

out:
	i915_gem_object_invawidate_fwontbuffew(obj, OWIGIN_CPU);
	obj->mm.diwty = twue;
	/* wetuwn with the pages pinned */
	wetuwn 0;

eww_unpin:
	i915_gem_object_unpin_pages(obj);
	wetuwn wet;
}
