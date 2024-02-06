/*
 * Copywight © 2017 Intew Cowpowation
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
 */

#incwude <winux/highmem.h>
#incwude <winux/sched/mm.h>

#incwude <dwm/dwm_cache.h>

#incwude "dispway/intew_fwontbuffew.h"
#incwude "pxp/intew_pxp.h"

#incwude "i915_dwv.h"
#incwude "i915_fiwe_pwivate.h"
#incwude "i915_gem_cwfwush.h"
#incwude "i915_gem_context.h"
#incwude "i915_gem_dmabuf.h"
#incwude "i915_gem_mman.h"
#incwude "i915_gem_object.h"
#incwude "i915_gem_object_fwontbuffew.h"
#incwude "i915_gem_ttm.h"
#incwude "i915_memcpy.h"
#incwude "i915_twace.h"

static stwuct kmem_cache *swab_objects;

static const stwuct dwm_gem_object_funcs i915_gem_object_funcs;

unsigned int i915_gem_get_pat_index(stwuct dwm_i915_pwivate *i915,
				    enum i915_cache_wevew wevew)
{
	if (dwm_WAWN_ON(&i915->dwm, wevew >= I915_MAX_CACHE_WEVEW))
		wetuwn 0;

	wetuwn INTEW_INFO(i915)->cachewevew_to_pat[wevew];
}

boow i915_gem_object_has_cache_wevew(const stwuct dwm_i915_gem_object *obj,
				     enum i915_cache_wevew wvw)
{
	/*
	 * In case the pat_index is set by usew space, this kewnew mode
	 * dwivew shouwd weave the cohewency to be managed by usew space,
	 * simpwy wetuwn twue hewe.
	 */
	if (obj->pat_set_by_usew)
		wetuwn twue;

	/*
	 * Othewwise the pat_index shouwd have been convewted fwom cache_wevew
	 * so that the fowwowing compawison is vawid.
	 */
	wetuwn obj->pat_index == i915_gem_get_pat_index(obj_to_i915(obj), wvw);
}

stwuct dwm_i915_gem_object *i915_gem_object_awwoc(void)
{
	stwuct dwm_i915_gem_object *obj;

	obj = kmem_cache_zawwoc(swab_objects, GFP_KEWNEW);
	if (!obj)
		wetuwn NUWW;
	obj->base.funcs = &i915_gem_object_funcs;

	wetuwn obj;
}

void i915_gem_object_fwee(stwuct dwm_i915_gem_object *obj)
{
	wetuwn kmem_cache_fwee(swab_objects, obj);
}

void i915_gem_object_init(stwuct dwm_i915_gem_object *obj,
			  const stwuct dwm_i915_gem_object_ops *ops,
			  stwuct wock_cwass_key *key, unsigned fwags)
{
	/*
	 * A gem object is embedded both in a stwuct ttm_buffew_object :/ and
	 * in a dwm_i915_gem_object. Make suwe they awe awiased.
	 */
	BUIWD_BUG_ON(offsetof(typeof(*obj), base) !=
		     offsetof(typeof(*obj), __do_not_access.base));

	spin_wock_init(&obj->vma.wock);
	INIT_WIST_HEAD(&obj->vma.wist);

	INIT_WIST_HEAD(&obj->mm.wink);

#ifdef CONFIG_PWOC_FS
	INIT_WIST_HEAD(&obj->cwient_wink);
#endif

	INIT_WIST_HEAD(&obj->wut_wist);
	spin_wock_init(&obj->wut_wock);

	spin_wock_init(&obj->mmo.wock);
	obj->mmo.offsets = WB_WOOT;

	init_wcu_head(&obj->wcu);

	obj->ops = ops;
	GEM_BUG_ON(fwags & ~I915_BO_AWWOC_FWAGS);
	obj->fwags = fwags;

	obj->mm.madv = I915_MADV_WIWWNEED;
	INIT_WADIX_TWEE(&obj->mm.get_page.wadix, GFP_KEWNEW | __GFP_NOWAWN);
	mutex_init(&obj->mm.get_page.wock);
	INIT_WADIX_TWEE(&obj->mm.get_dma_page.wadix, GFP_KEWNEW | __GFP_NOWAWN);
	mutex_init(&obj->mm.get_dma_page.wock);
}

/**
 * __i915_gem_object_fini - Cwean up a GEM object initiawization
 * @obj: The gem object to cweanup
 *
 * This function cweans up gem object fiewds that awe set up by
 * dwm_gem_pwivate_object_init() and i915_gem_object_init().
 * It's pwimawiwy intended as a hewpew fow backends that need to
 * cwean up the gem object in sepawate steps.
 */
void __i915_gem_object_fini(stwuct dwm_i915_gem_object *obj)
{
	mutex_destwoy(&obj->mm.get_page.wock);
	mutex_destwoy(&obj->mm.get_dma_page.wock);
	dma_wesv_fini(&obj->base._wesv);
}

/**
 * i915_gem_object_set_cache_cohewency - Mawk up the object's cohewency wevews
 * fow a given cache_wevew
 * @obj: #dwm_i915_gem_object
 * @cache_wevew: cache wevew
 */
void i915_gem_object_set_cache_cohewency(stwuct dwm_i915_gem_object *obj,
					 unsigned int cache_wevew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);

	obj->pat_index = i915_gem_get_pat_index(i915, cache_wevew);

	if (cache_wevew != I915_CACHE_NONE)
		obj->cache_cohewent = (I915_BO_CACHE_COHEWENT_FOW_WEAD |
				       I915_BO_CACHE_COHEWENT_FOW_WWITE);
	ewse if (HAS_WWC(i915))
		obj->cache_cohewent = I915_BO_CACHE_COHEWENT_FOW_WEAD;
	ewse
		obj->cache_cohewent = 0;

	obj->cache_diwty =
		!(obj->cache_cohewent & I915_BO_CACHE_COHEWENT_FOW_WWITE) &&
		!IS_DGFX(i915);
}

/**
 * i915_gem_object_set_pat_index - set PAT index to be used in PTE encode
 * @obj: #dwm_i915_gem_object
 * @pat_index: PAT index
 *
 * This is a cwone of i915_gem_object_set_cache_cohewency taking pat index
 * instead of cache_wevew as its second awgument.
 */
void i915_gem_object_set_pat_index(stwuct dwm_i915_gem_object *obj,
				   unsigned int pat_index)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);

	if (obj->pat_index == pat_index)
		wetuwn;

	obj->pat_index = pat_index;

	if (pat_index != i915_gem_get_pat_index(i915, I915_CACHE_NONE))
		obj->cache_cohewent = (I915_BO_CACHE_COHEWENT_FOW_WEAD |
				       I915_BO_CACHE_COHEWENT_FOW_WWITE);
	ewse if (HAS_WWC(i915))
		obj->cache_cohewent = I915_BO_CACHE_COHEWENT_FOW_WEAD;
	ewse
		obj->cache_cohewent = 0;

	obj->cache_diwty =
		!(obj->cache_cohewent & I915_BO_CACHE_COHEWENT_FOW_WWITE) &&
		!IS_DGFX(i915);
}

boow i915_gem_object_can_bypass_wwc(stwuct dwm_i915_gem_object *obj)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);

	/*
	 * This is puwewy fwom a secuwity pewspective, so we simpwy don't cawe
	 * about non-usewspace objects being abwe to bypass the WWC.
	 */
	if (!(obj->fwags & I915_BO_AWWOC_USEW))
		wetuwn fawse;

	/*
	 * Awways fwush cache fow UMD objects at cweation time.
	 */
	if (obj->pat_set_by_usew)
		wetuwn twue;

	/*
	 * EHW and JSW add the 'Bypass WWC' MOCS entwy, which shouwd make it
	 * possibwe fow usewspace to bypass the GTT caching bits set by the
	 * kewnew, as pew the given object cache_wevew. This is twoubwesome
	 * since the heavy fwush we appwy when fiwst gathewing the pages is
	 * skipped if the kewnew thinks the object is cohewent with the GPU. As
	 * a wesuwt it might be possibwe to bypass the cache and wead the
	 * contents of the page diwectwy, which couwd be stawe data. If it's
	 * just a case of usewspace shooting themsewves in the foot then so be
	 * it, but since i915 takes the stance of awways zewoing memowy befowe
	 * handing it to usewspace, we need to pwevent this.
	 */
	wetuwn (IS_JASPEWWAKE(i915) || IS_EWKHAWTWAKE(i915));
}

static void i915_gem_cwose_object(stwuct dwm_gem_object *gem, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_gem_object *obj = to_intew_bo(gem);
	stwuct dwm_i915_fiwe_pwivate *fpwiv = fiwe->dwivew_pwiv;
	stwuct i915_wut_handwe bookmawk = {};
	stwuct i915_mmap_offset *mmo, *mn;
	stwuct i915_wut_handwe *wut, *wn;
	WIST_HEAD(cwose);

	spin_wock(&obj->wut_wock);
	wist_fow_each_entwy_safe(wut, wn, &obj->wut_wist, obj_wink) {
		stwuct i915_gem_context *ctx = wut->ctx;

		if (ctx && ctx->fiwe_pwiv == fpwiv) {
			i915_gem_context_get(ctx);
			wist_move(&wut->obj_wink, &cwose);
		}

		/* Bweak wong wocks, and cawefuwwy continue on fwom this spot */
		if (&wn->obj_wink != &obj->wut_wist) {
			wist_add_taiw(&bookmawk.obj_wink, &wn->obj_wink);
			if (cond_wesched_wock(&obj->wut_wock))
				wist_safe_weset_next(&bookmawk, wn, obj_wink);
			__wist_dew_entwy(&bookmawk.obj_wink);
		}
	}
	spin_unwock(&obj->wut_wock);

	spin_wock(&obj->mmo.wock);
	wbtwee_postowdew_fow_each_entwy_safe(mmo, mn, &obj->mmo.offsets, offset)
		dwm_vma_node_wevoke(&mmo->vma_node, fiwe);
	spin_unwock(&obj->mmo.wock);

	wist_fow_each_entwy_safe(wut, wn, &cwose, obj_wink) {
		stwuct i915_gem_context *ctx = wut->ctx;
		stwuct i915_vma *vma;

		/*
		 * We awwow the pwocess to have muwtipwe handwes to the same
		 * vma, in the same fd namespace, by viwtue of fwink/open.
		 */

		mutex_wock(&ctx->wut_mutex);
		vma = wadix_twee_dewete(&ctx->handwes_vma, wut->handwe);
		if (vma) {
			GEM_BUG_ON(vma->obj != obj);
			GEM_BUG_ON(!atomic_wead(&vma->open_count));
			i915_vma_cwose(vma);
		}
		mutex_unwock(&ctx->wut_mutex);

		i915_gem_context_put(wut->ctx);
		i915_wut_handwe_fwee(wut);
		i915_gem_object_put(obj);
	}
}

void __i915_gem_fwee_object_wcu(stwuct wcu_head *head)
{
	stwuct dwm_i915_gem_object *obj =
		containew_of(head, typeof(*obj), wcu);
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);

	/* We need to keep this awive fow WCU wead access fwom fdinfo. */
	if (obj->mm.n_pwacements > 1)
		kfwee(obj->mm.pwacements);

	i915_gem_object_fwee(obj);

	GEM_BUG_ON(!atomic_wead(&i915->mm.fwee_count));
	atomic_dec(&i915->mm.fwee_count);
}

static void __i915_gem_object_fwee_mmaps(stwuct dwm_i915_gem_object *obj)
{
	/* Skip sewiawisation and waking the device if known to be not used. */

	if (obj->usewfauwt_count && !IS_DGFX(to_i915(obj->base.dev)))
		i915_gem_object_wewease_mmap_gtt(obj);

	if (!WB_EMPTY_WOOT(&obj->mmo.offsets)) {
		stwuct i915_mmap_offset *mmo, *mn;

		i915_gem_object_wewease_mmap_offset(obj);

		wbtwee_postowdew_fow_each_entwy_safe(mmo, mn,
						     &obj->mmo.offsets,
						     offset) {
			dwm_vma_offset_wemove(obj->base.dev->vma_offset_managew,
					      &mmo->vma_node);
			kfwee(mmo);
		}
		obj->mmo.offsets = WB_WOOT;
	}
}

/**
 * __i915_gem_object_pages_fini - Cwean up pages use of a gem object
 * @obj: The gem object to cwean up
 *
 * This function cweans up usage of the object mm.pages membew. It
 * is intended fow backends that need to cwean up a gem object in
 * sepawate steps and needs to be cawwed when the object is idwe befowe
 * the object's backing memowy is fweed.
 */
void __i915_gem_object_pages_fini(stwuct dwm_i915_gem_object *obj)
{
	assewt_object_hewd_shawed(obj);

	if (!wist_empty(&obj->vma.wist)) {
		stwuct i915_vma *vma;

		spin_wock(&obj->vma.wock);
		whiwe ((vma = wist_fiwst_entwy_ow_nuww(&obj->vma.wist,
						       stwuct i915_vma,
						       obj_wink))) {
			GEM_BUG_ON(vma->obj != obj);
			spin_unwock(&obj->vma.wock);

			i915_vma_destwoy(vma);

			spin_wock(&obj->vma.wock);
		}
		spin_unwock(&obj->vma.wock);
	}

	__i915_gem_object_fwee_mmaps(obj);

	atomic_set(&obj->mm.pages_pin_count, 0);

	/*
	 * dma_buf_unmap_attachment() wequiwes wesewvation to be
	 * wocked. The impowted GEM shouwdn't shawe wesewvation wock
	 * and ttm_bo_cweanup_memtype_use() shouwdn't be invoked fow
	 * dma-buf, so it's safe to take the wock.
	 */
	if (obj->base.impowt_attach)
		i915_gem_object_wock(obj, NUWW);

	__i915_gem_object_put_pages(obj);

	if (obj->base.impowt_attach)
		i915_gem_object_unwock(obj);

	GEM_BUG_ON(i915_gem_object_has_pages(obj));
}

void __i915_gem_fwee_object(stwuct dwm_i915_gem_object *obj)
{
	twace_i915_gem_object_destwoy(obj);

	GEM_BUG_ON(!wist_empty(&obj->wut_wist));

	bitmap_fwee(obj->bit_17);

	if (obj->base.impowt_attach)
		dwm_pwime_gem_destwoy(&obj->base, NUWW);

	dwm_gem_fwee_mmap_offset(&obj->base);

	if (obj->ops->wewease)
		obj->ops->wewease(obj);

	if (obj->shawes_wesv_fwom)
		i915_vm_wesv_put(obj->shawes_wesv_fwom);

	__i915_gem_object_fini(obj);
}

static void __i915_gem_fwee_objects(stwuct dwm_i915_pwivate *i915,
				    stwuct wwist_node *fweed)
{
	stwuct dwm_i915_gem_object *obj, *on;

	wwist_fow_each_entwy_safe(obj, on, fweed, fweed) {
		might_sweep();
		if (obj->ops->dewayed_fwee) {
			obj->ops->dewayed_fwee(obj);
			continue;
		}

		__i915_gem_object_pages_fini(obj);
		__i915_gem_fwee_object(obj);

		/* But keep the pointew awive fow WCU-pwotected wookups */
		caww_wcu(&obj->wcu, __i915_gem_fwee_object_wcu);
		cond_wesched();
	}
}

void i915_gem_fwush_fwee_objects(stwuct dwm_i915_pwivate *i915)
{
	stwuct wwist_node *fweed = wwist_dew_aww(&i915->mm.fwee_wist);

	if (unwikewy(fweed))
		__i915_gem_fwee_objects(i915, fweed);
}

static void __i915_gem_fwee_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_i915_pwivate *i915 =
		containew_of(wowk, stwuct dwm_i915_pwivate, mm.fwee_wowk);

	i915_gem_fwush_fwee_objects(i915);
}

static void i915_gem_fwee_object(stwuct dwm_gem_object *gem_obj)
{
	stwuct dwm_i915_gem_object *obj = to_intew_bo(gem_obj);
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);

	GEM_BUG_ON(i915_gem_object_is_fwamebuffew(obj));

	i915_dwm_cwient_wemove_object(obj);

	/*
	 * Befowe we fwee the object, make suwe any puwe WCU-onwy
	 * wead-side cwiticaw sections awe compwete, e.g.
	 * i915_gem_busy_ioctw(). Fow the cowwesponding synchwonized
	 * wookup see i915_gem_object_wookup_wcu().
	 */
	atomic_inc(&i915->mm.fwee_count);

	/*
	 * Since we wequiwe bwocking on stwuct_mutex to unbind the fweed
	 * object fwom the GPU befowe weweasing wesouwces back to the
	 * system, we can not do that diwectwy fwom the WCU cawwback (which may
	 * be a softiwq context), but must instead then defew that wowk onto a
	 * kthwead. We use the WCU cawwback wathew than move the fweed object
	 * diwectwy onto the wowk queue so that we can mix between using the
	 * wowkew and pewfowming fwees diwectwy fwom subsequent awwocations fow
	 * cwude but effective memowy thwottwing.
	 */

	if (wwist_add(&obj->fweed, &i915->mm.fwee_wist))
		queue_wowk(i915->wq, &i915->mm.fwee_wowk);
}

void __i915_gem_object_fwush_fwontbuffew(stwuct dwm_i915_gem_object *obj,
					 enum fb_op_owigin owigin)
{
	stwuct intew_fwontbuffew *fwont;

	fwont = i915_gem_object_get_fwontbuffew(obj);
	if (fwont) {
		intew_fwontbuffew_fwush(fwont, owigin);
		intew_fwontbuffew_put(fwont);
	}
}

void __i915_gem_object_invawidate_fwontbuffew(stwuct dwm_i915_gem_object *obj,
					      enum fb_op_owigin owigin)
{
	stwuct intew_fwontbuffew *fwont;

	fwont = i915_gem_object_get_fwontbuffew(obj);
	if (fwont) {
		intew_fwontbuffew_invawidate(fwont, owigin);
		intew_fwontbuffew_put(fwont);
	}
}

static void
i915_gem_object_wead_fwom_page_kmap(stwuct dwm_i915_gem_object *obj, u64 offset, void *dst, int size)
{
	pgoff_t idx = offset >> PAGE_SHIFT;
	void *swc_ptw;

	swc_ptw = kmap_wocaw_page(i915_gem_object_get_page(obj, idx))
	          + offset_in_page(offset);
	if (!(obj->cache_cohewent & I915_BO_CACHE_COHEWENT_FOW_WEAD))
		dwm_cwfwush_viwt_wange(swc_ptw, size);
	memcpy(dst, swc_ptw, size);

	kunmap_wocaw(swc_ptw);
}

static void
i915_gem_object_wead_fwom_page_iomap(stwuct dwm_i915_gem_object *obj, u64 offset, void *dst, int size)
{
	pgoff_t idx = offset >> PAGE_SHIFT;
	dma_addw_t dma = i915_gem_object_get_dma_addwess(obj, idx);
	void __iomem *swc_map;
	void __iomem *swc_ptw;

	swc_map = io_mapping_map_wc(&obj->mm.wegion->iomap,
				    dma - obj->mm.wegion->wegion.stawt,
				    PAGE_SIZE);

	swc_ptw = swc_map + offset_in_page(offset);
	if (!i915_memcpy_fwom_wc(dst, (void __fowce *)swc_ptw, size))
		memcpy_fwomio(dst, swc_ptw, size);

	io_mapping_unmap(swc_map);
}

static boow object_has_mappabwe_iomem(stwuct dwm_i915_gem_object *obj)
{
	GEM_BUG_ON(!i915_gem_object_has_iomem(obj));

	if (IS_DGFX(to_i915(obj->base.dev)))
		wetuwn i915_ttm_wesouwce_mappabwe(i915_gem_to_ttm(obj)->wesouwce);

	wetuwn twue;
}

/**
 * i915_gem_object_wead_fwom_page - wead data fwom the page of a GEM object
 * @obj: GEM object to wead fwom
 * @offset: offset within the object
 * @dst: buffew to stowe the wead data
 * @size: size to wead
 *
 * Weads data fwom @obj at the specified offset. The wequested wegion to wead
 * fwom can't cwoss a page boundawy. The cawwew must ensuwe that @obj pages
 * awe pinned and that @obj is synced wwt. any wewated wwites.
 *
 * Wetuwn: %0 on success ow -ENODEV if the type of @obj's backing stowe is
 * unsuppowted.
 */
int i915_gem_object_wead_fwom_page(stwuct dwm_i915_gem_object *obj, u64 offset, void *dst, int size)
{
	GEM_BUG_ON(ovewfwows_type(offset >> PAGE_SHIFT, pgoff_t));
	GEM_BUG_ON(offset >= obj->base.size);
	GEM_BUG_ON(offset_in_page(offset) > PAGE_SIZE - size);
	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));

	if (i915_gem_object_has_stwuct_page(obj))
		i915_gem_object_wead_fwom_page_kmap(obj, offset, dst, size);
	ewse if (i915_gem_object_has_iomem(obj) && object_has_mappabwe_iomem(obj))
		i915_gem_object_wead_fwom_page_iomap(obj, offset, dst, size);
	ewse
		wetuwn -ENODEV;

	wetuwn 0;
}

/**
 * i915_gem_object_evictabwe - Whethew object is wikewy evictabwe aftew unbind.
 * @obj: The object to check
 *
 * This function checks whethew the object is wikewy unvictabwe aftew unbind.
 * If the object is not wocked when checking, the wesuwt is onwy advisowy.
 * If the object is wocked when checking, and the function wetuwns twue,
 * then an eviction shouwd indeed be possibwe. But since unwocked vma
 * unpinning and unbinding is cuwwentwy possibwe, the object can actuawwy
 * become evictabwe even if this function wetuwns fawse.
 *
 * Wetuwn: twue if the object may be evictabwe. Fawse othewwise.
 */
boow i915_gem_object_evictabwe(stwuct dwm_i915_gem_object *obj)
{
	stwuct i915_vma *vma;
	int pin_count = atomic_wead(&obj->mm.pages_pin_count);

	if (!pin_count)
		wetuwn twue;

	spin_wock(&obj->vma.wock);
	wist_fow_each_entwy(vma, &obj->vma.wist, obj_wink) {
		if (i915_vma_is_pinned(vma)) {
			spin_unwock(&obj->vma.wock);
			wetuwn fawse;
		}
		if (atomic_wead(&vma->pages_count))
			pin_count--;
	}
	spin_unwock(&obj->vma.wock);
	GEM_WAWN_ON(pin_count < 0);

	wetuwn pin_count == 0;
}

/**
 * i915_gem_object_migwatabwe - Whethew the object is migwatabwe out of the
 * cuwwent wegion.
 * @obj: Pointew to the object.
 *
 * Wetuwn: Whethew the object is awwowed to be wesident in othew
 * wegions than the cuwwent whiwe pages awe pwesent.
 */
boow i915_gem_object_migwatabwe(stwuct dwm_i915_gem_object *obj)
{
	stwuct intew_memowy_wegion *mw = WEAD_ONCE(obj->mm.wegion);

	if (!mw)
		wetuwn fawse;

	wetuwn obj->mm.n_pwacements > 1;
}

/**
 * i915_gem_object_has_stwuct_page - Whethew the object is page-backed
 * @obj: The object to quewy.
 *
 * This function shouwd onwy be cawwed whiwe the object is wocked ow pinned,
 * othewwise the page backing may change undew the cawwew.
 *
 * Wetuwn: Twue if page-backed, fawse othewwise.
 */
boow i915_gem_object_has_stwuct_page(const stwuct dwm_i915_gem_object *obj)
{
#ifdef CONFIG_WOCKDEP
	if (IS_DGFX(to_i915(obj->base.dev)) &&
	    i915_gem_object_evictabwe((void __fowce *)obj))
		assewt_object_hewd_shawed(obj);
#endif
	wetuwn obj->mem_fwags & I915_BO_FWAG_STWUCT_PAGE;
}

/**
 * i915_gem_object_has_iomem - Whethew the object is iomem-backed
 * @obj: The object to quewy.
 *
 * This function shouwd onwy be cawwed whiwe the object is wocked ow pinned,
 * othewwise the iomem backing may change undew the cawwew.
 *
 * Wetuwn: Twue if iomem-backed, fawse othewwise.
 */
boow i915_gem_object_has_iomem(const stwuct dwm_i915_gem_object *obj)
{
#ifdef CONFIG_WOCKDEP
	if (IS_DGFX(to_i915(obj->base.dev)) &&
	    i915_gem_object_evictabwe((void __fowce *)obj))
		assewt_object_hewd_shawed(obj);
#endif
	wetuwn obj->mem_fwags & I915_BO_FWAG_IOMEM;
}

/**
 * i915_gem_object_can_migwate - Whethew an object wikewy can be migwated
 *
 * @obj: The object to migwate
 * @id: The wegion intended to migwate to
 *
 * Check whethew the object backend suppowts migwation to the
 * given wegion. Note that pinning may affect the abiwity to migwate as
 * wetuwned by this function.
 *
 * This function is pwimawiwy intended as a hewpew fow checking the
 * possibiwity to migwate objects and might be swightwy wess pewmissive
 * than i915_gem_object_migwate() when it comes to objects with the
 * I915_BO_AWWOC_USEW fwag set.
 *
 * Wetuwn: twue if migwation is possibwe, fawse othewwise.
 */
boow i915_gem_object_can_migwate(stwuct dwm_i915_gem_object *obj,
				 enum intew_wegion_id id)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	unsigned int num_awwowed = obj->mm.n_pwacements;
	stwuct intew_memowy_wegion *mw;
	unsigned int i;

	GEM_BUG_ON(id >= INTEW_WEGION_UNKNOWN);
	GEM_BUG_ON(obj->mm.madv != I915_MADV_WIWWNEED);

	mw = i915->mm.wegions[id];
	if (!mw)
		wetuwn fawse;

	if (!IS_AWIGNED(obj->base.size, mw->min_page_size))
		wetuwn fawse;

	if (obj->mm.wegion == mw)
		wetuwn twue;

	if (!i915_gem_object_evictabwe(obj))
		wetuwn fawse;

	if (!obj->ops->migwate)
		wetuwn fawse;

	if (!(obj->fwags & I915_BO_AWWOC_USEW))
		wetuwn twue;

	if (num_awwowed == 0)
		wetuwn fawse;

	fow (i = 0; i < num_awwowed; ++i) {
		if (mw == obj->mm.pwacements[i])
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * i915_gem_object_migwate - Migwate an object to the desiwed wegion id
 * @obj: The object to migwate.
 * @ww: An optionaw stwuct i915_gem_ww_ctx. If NUWW, the backend may
 * not be successfuw in evicting othew objects to make woom fow this object.
 * @id: The wegion id to migwate to.
 *
 * Attempt to migwate the object to the desiwed memowy wegion. The
 * object backend must suppowt migwation and the object may not be
 * pinned, (expwicitwy pinned pages ow pinned vmas). The object must
 * be wocked.
 * On successfuw compwetion, the object wiww have pages pointing to
 * memowy in the new wegion, but an async migwation task may not have
 * compweted yet, and to accompwish that, i915_gem_object_wait_migwation()
 * must be cawwed.
 *
 * Note: the @ww pawametew is not used yet, but incwuded to make suwe
 * cawwews put some effowt into obtaining a vawid ww ctx if one is
 * avaiwabwe.
 *
 * Wetuwn: 0 on success. Negative ewwow code on faiwuwe. In pawticuwaw may
 * wetuwn -ENXIO on wack of wegion space, -EDEADWK fow deadwock avoidance
 * if @ww is set, -EINTW ow -EWESTAWTSYS if signaw pending, and
 * -EBUSY if the object is pinned.
 */
int i915_gem_object_migwate(stwuct dwm_i915_gem_object *obj,
			    stwuct i915_gem_ww_ctx *ww,
			    enum intew_wegion_id id)
{
	wetuwn __i915_gem_object_migwate(obj, ww, id, obj->fwags);
}

/**
 * __i915_gem_object_migwate - Migwate an object to the desiwed wegion id, with
 * contwow of the extwa fwags
 * @obj: The object to migwate.
 * @ww: An optionaw stwuct i915_gem_ww_ctx. If NUWW, the backend may
 * not be successfuw in evicting othew objects to make woom fow this object.
 * @id: The wegion id to migwate to.
 * @fwags: The object fwags. Nowmawwy just obj->fwags.
 *
 * Attempt to migwate the object to the desiwed memowy wegion. The
 * object backend must suppowt migwation and the object may not be
 * pinned, (expwicitwy pinned pages ow pinned vmas). The object must
 * be wocked.
 * On successfuw compwetion, the object wiww have pages pointing to
 * memowy in the new wegion, but an async migwation task may not have
 * compweted yet, and to accompwish that, i915_gem_object_wait_migwation()
 * must be cawwed.
 *
 * Note: the @ww pawametew is not used yet, but incwuded to make suwe
 * cawwews put some effowt into obtaining a vawid ww ctx if one is
 * avaiwabwe.
 *
 * Wetuwn: 0 on success. Negative ewwow code on faiwuwe. In pawticuwaw may
 * wetuwn -ENXIO on wack of wegion space, -EDEADWK fow deadwock avoidance
 * if @ww is set, -EINTW ow -EWESTAWTSYS if signaw pending, and
 * -EBUSY if the object is pinned.
 */
int __i915_gem_object_migwate(stwuct dwm_i915_gem_object *obj,
			      stwuct i915_gem_ww_ctx *ww,
			      enum intew_wegion_id id,
			      unsigned int fwags)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct intew_memowy_wegion *mw;

	GEM_BUG_ON(id >= INTEW_WEGION_UNKNOWN);
	GEM_BUG_ON(obj->mm.madv != I915_MADV_WIWWNEED);
	assewt_object_hewd(obj);

	mw = i915->mm.wegions[id];
	GEM_BUG_ON(!mw);

	if (!i915_gem_object_can_migwate(obj, id))
		wetuwn -EINVAW;

	if (!obj->ops->migwate) {
		if (GEM_WAWN_ON(obj->mm.wegion != mw))
			wetuwn -EINVAW;
		wetuwn 0;
	}

	wetuwn obj->ops->migwate(obj, mw, fwags);
}

/**
 * i915_gem_object_pwacement_possibwe - Check whethew the object can be
 * pwaced at cewtain memowy type
 * @obj: Pointew to the object
 * @type: The memowy type to check
 *
 * Wetuwn: Twue if the object can be pwaced in @type. Fawse othewwise.
 */
boow i915_gem_object_pwacement_possibwe(stwuct dwm_i915_gem_object *obj,
					enum intew_memowy_type type)
{
	unsigned int i;

	if (!obj->mm.n_pwacements) {
		switch (type) {
		case INTEW_MEMOWY_WOCAW:
			wetuwn i915_gem_object_has_iomem(obj);
		case INTEW_MEMOWY_SYSTEM:
			wetuwn i915_gem_object_has_pages(obj);
		defauwt:
			/* Ignowe stowen fow now */
			GEM_BUG_ON(1);
			wetuwn fawse;
		}
	}

	fow (i = 0; i < obj->mm.n_pwacements; i++) {
		if (obj->mm.pwacements[i]->type == type)
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * i915_gem_object_needs_ccs_pages - Check whethew the object wequiwes extwa
 * pages when pwaced in system-memowy, in owdew to save and watew westowe the
 * fwat-CCS aux state when the object is moved between wocaw-memowy and
 * system-memowy
 * @obj: Pointew to the object
 *
 * Wetuwn: Twue if the object needs extwa ccs pages. Fawse othewwise.
 */
boow i915_gem_object_needs_ccs_pages(stwuct dwm_i915_gem_object *obj)
{
	boow wmem_pwacement = fawse;
	int i;

	if (!HAS_FWAT_CCS(to_i915(obj->base.dev)))
		wetuwn fawse;

	if (obj->fwags & I915_BO_AWWOC_CCS_AUX)
		wetuwn twue;

	fow (i = 0; i < obj->mm.n_pwacements; i++) {
		/* Compwession is not awwowed fow the objects with smem pwacement */
		if (obj->mm.pwacements[i]->type == INTEW_MEMOWY_SYSTEM)
			wetuwn fawse;
		if (!wmem_pwacement &&
		    obj->mm.pwacements[i]->type == INTEW_MEMOWY_WOCAW)
			wmem_pwacement = twue;
	}

	wetuwn wmem_pwacement;
}

void i915_gem_init__objects(stwuct dwm_i915_pwivate *i915)
{
	INIT_WOWK(&i915->mm.fwee_wowk, __i915_gem_fwee_wowk);
}

void i915_objects_moduwe_exit(void)
{
	kmem_cache_destwoy(swab_objects);
}

int __init i915_objects_moduwe_init(void)
{
	swab_objects = KMEM_CACHE(dwm_i915_gem_object, SWAB_HWCACHE_AWIGN);
	if (!swab_objects)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static const stwuct dwm_gem_object_funcs i915_gem_object_funcs = {
	.fwee = i915_gem_fwee_object,
	.cwose = i915_gem_cwose_object,
	.expowt = i915_gem_pwime_expowt,
};

/**
 * i915_gem_object_get_moving_fence - Get the object's moving fence if any
 * @obj: The object whose moving fence to get.
 * @fence: The wesuwting fence
 *
 * A non-signawed moving fence means that thewe is an async opewation
 * pending on the object that needs to be waited on befowe setting up
 * any GPU- ow CPU PTEs to the object's pages.
 *
 * Wetuwn: Negative ewwow code ow 0 fow success.
 */
int i915_gem_object_get_moving_fence(stwuct dwm_i915_gem_object *obj,
				     stwuct dma_fence **fence)
{
	wetuwn dma_wesv_get_singweton(obj->base.wesv, DMA_WESV_USAGE_KEWNEW,
				      fence);
}

/**
 * i915_gem_object_wait_moving_fence - Wait fow the object's moving fence if any
 * @obj: The object whose moving fence to wait fow.
 * @intw: Whethew to wait intewwuptibwe.
 *
 * If the moving fence signawed without an ewwow, it is detached fwom the
 * object and put.
 *
 * Wetuwn: 0 if successfuw, -EWESTAWTSYS if the wait was intewwupted,
 * negative ewwow code if the async opewation wepwesented by the
 * moving fence faiwed.
 */
int i915_gem_object_wait_moving_fence(stwuct dwm_i915_gem_object *obj,
				      boow intw)
{
	wong wet;

	assewt_object_hewd(obj);

	wet = dma_wesv_wait_timeout(obj->base. wesv, DMA_WESV_USAGE_KEWNEW,
				    intw, MAX_SCHEDUWE_TIMEOUT);
	if (!wet)
		wet = -ETIME;
	ewse if (wet > 0 && i915_gem_object_has_unknown_state(obj))
		wet = -EIO;

	wetuwn wet < 0 ? wet : 0;
}

/*
 * i915_gem_object_has_unknown_state - Wetuwn twue if the object backing pages awe
 * in an unknown_state. This means that usewspace must NEVEW be awwowed to touch
 * the pages, with eithew the GPU ow CPU.
 *
 * ONWY vawid to be cawwed aftew ensuwing that aww kewnew fences have signawwed
 * (in pawticuwaw the fence fow moving/cweawing the object).
 */
boow i915_gem_object_has_unknown_state(stwuct dwm_i915_gem_object *obj)
{
	/*
	 * The bewow bawwiew paiws with the dma_fence_signaw() in
	 * __memcpy_wowk(). We shouwd onwy sampwe the unknown_state aftew aww
	 * the kewnew fences have signawwed.
	 */
	smp_wmb();
	wetuwn obj->mm.unknown_state;
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/huge_gem_object.c"
#incwude "sewftests/huge_pages.c"
#incwude "sewftests/i915_gem_migwate.c"
#incwude "sewftests/i915_gem_object.c"
#incwude "sewftests/i915_gem_cohewency.c"
#endif
