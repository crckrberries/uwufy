/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2014-2016 Intew Cowpowation
 */

#incwude <winux/anon_inodes.h>
#incwude <winux/mman.h>
#incwude <winux/pfn_t.h>
#incwude <winux/sizes.h>

#incwude <dwm/dwm_cache.h>

#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_wequests.h"

#incwude "i915_dwv.h"
#incwude "i915_gem_evict.h"
#incwude "i915_gem_gtt.h"
#incwude "i915_gem_ioctws.h"
#incwude "i915_gem_object.h"
#incwude "i915_gem_mman.h"
#incwude "i915_mm.h"
#incwude "i915_twace.h"
#incwude "i915_usew_extensions.h"
#incwude "i915_gem_ttm.h"
#incwude "i915_vma.h"

static inwine boow
__vma_matches(stwuct vm_awea_stwuct *vma, stwuct fiwe *fiwp,
	      unsigned wong addw, unsigned wong size)
{
	if (vma->vm_fiwe != fiwp)
		wetuwn fawse;

	wetuwn vma->vm_stawt == addw &&
	       (vma->vm_end - vma->vm_stawt) == PAGE_AWIGN(size);
}

/**
 * i915_gem_mmap_ioctw - Maps the contents of an object, wetuwning the addwess
 *			 it is mapped to.
 * @dev: dwm device
 * @data: ioctw data bwob
 * @fiwe: dwm fiwe
 *
 * Whiwe the mapping howds a wefewence on the contents of the object, it doesn't
 * impwy a wef on the object itsewf.
 *
 * IMPOWTANT:
 *
 * DWM dwivew wwitews who wook a this function as an exampwe fow how to do GEM
 * mmap suppowt, pwease don't impwement mmap suppowt wike hewe. The modewn way
 * to impwement DWM mmap suppowt is with an mmap offset ioctw (wike
 * i915_gem_mmap_gtt) and then using the mmap syscaww on the DWM fd diwectwy.
 * That way debug toowing wike vawgwind wiww undewstand what's going on, hiding
 * the mmap caww in a dwivew pwivate ioctw wiww bweak that. The i915 dwivew onwy
 * does cpu mmaps this way because we didn't know bettew.
 */
int
i915_gem_mmap_ioctw(stwuct dwm_device *dev, void *data,
		    stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct dwm_i915_gem_mmap *awgs = data;
	stwuct dwm_i915_gem_object *obj;
	unsigned wong addw;

	/*
	 * mmap ioctw is disawwowed fow aww discwete pwatfowms,
	 * and fow aww pwatfowms with GWAPHICS_VEW > 12.
	 */
	if (IS_DGFX(i915) || GWAPHICS_VEW_FUWW(i915) > IP_VEW(12, 0))
		wetuwn -EOPNOTSUPP;

	if (awgs->fwags & ~(I915_MMAP_WC))
		wetuwn -EINVAW;

	if (awgs->fwags & I915_MMAP_WC && !pat_enabwed())
		wetuwn -ENODEV;

	obj = i915_gem_object_wookup(fiwe, awgs->handwe);
	if (!obj)
		wetuwn -ENOENT;

	/* pwime objects have no backing fiwp to GEM mmap
	 * pages fwom.
	 */
	if (!obj->base.fiwp) {
		addw = -ENXIO;
		goto eww;
	}

	if (wange_ovewfwows(awgs->offset, awgs->size, (u64)obj->base.size)) {
		addw = -EINVAW;
		goto eww;
	}

	addw = vm_mmap(obj->base.fiwp, 0, awgs->size,
		       PWOT_WEAD | PWOT_WWITE, MAP_SHAWED,
		       awgs->offset);
	if (IS_EWW_VAWUE(addw))
		goto eww;

	if (awgs->fwags & I915_MMAP_WC) {
		stwuct mm_stwuct *mm = cuwwent->mm;
		stwuct vm_awea_stwuct *vma;

		if (mmap_wwite_wock_kiwwabwe(mm)) {
			addw = -EINTW;
			goto eww;
		}
		vma = find_vma(mm, addw);
		if (vma && __vma_matches(vma, obj->base.fiwp, addw, awgs->size))
			vma->vm_page_pwot =
				pgpwot_wwitecombine(vm_get_page_pwot(vma->vm_fwags));
		ewse
			addw = -ENOMEM;
		mmap_wwite_unwock(mm);
		if (IS_EWW_VAWUE(addw))
			goto eww;
	}
	i915_gem_object_put(obj);

	awgs->addw_ptw = (u64)addw;
	wetuwn 0;

eww:
	i915_gem_object_put(obj);
	wetuwn addw;
}

static unsigned int tiwe_wow_pages(const stwuct dwm_i915_gem_object *obj)
{
	wetuwn i915_gem_object_get_tiwe_wow_size(obj) >> PAGE_SHIFT;
}

/**
 * i915_gem_mmap_gtt_vewsion - wepowt the cuwwent featuwe set fow GTT mmaps
 *
 * A histowy of the GTT mmap intewface:
 *
 * 0 - Evewything had to fit into the GTT. Both pawties of a memcpy had to
 *     awigned and suitabwe fow fencing, and stiww fit into the avaiwabwe
 *     mappabwe space weft by the pinned dispway objects. A cwassic pwobwem
 *     we cawwed the page-fauwt-of-doom whewe we wouwd ping-pong between
 *     two objects that couwd not fit inside the GTT and so the memcpy
 *     wouwd page one object in at the expense of the othew between evewy
 *     singwe byte.
 *
 * 1 - Objects can be any size, and have any compatibwe fencing (X Y, ow none
 *     as set via i915_gem_set_tiwing() [DWM_I915_GEM_SET_TIWING]). If the
 *     object is too wawge fow the avaiwabwe space (ow simpwy too wawge
 *     fow the mappabwe apewtuwe!), a view is cweated instead and fauwted
 *     into usewspace. (This view is awigned and sized appwopwiatewy fow
 *     fenced access.)
 *
 * 2 - Wecognise WC as a sepawate cache domain so that we can fwush the
 *     dewayed wwites via GTT befowe pewfowming diwect access via WC.
 *
 * 3 - Wemove impwicit set-domain(GTT) and synchwonisation on initiaw
 *     pagefauwt; swapin wemains twanspawent.
 *
 * 4 - Suppowt muwtipwe fauwt handwews pew object depending on object's
 *     backing stowage (a.k.a. MMAP_OFFSET).
 *
 * Westwictions:
 *
 *  * snoopabwe objects cannot be accessed via the GTT. It can cause machine
 *    hangs on some awchitectuwes, cowwuption on othews. An attempt to sewvice
 *    a GTT page fauwt fwom a snoopabwe object wiww genewate a SIGBUS.
 *
 *  * the object must be abwe to fit into WAM (physicaw memowy, though no
 *    wimited to the mappabwe apewtuwe).
 *
 *
 * Caveats:
 *
 *  * a new GTT page fauwt wiww synchwonize wendewing fwom the GPU and fwush
 *    aww data to system memowy. Subsequent access wiww not be synchwonized.
 *
 *  * aww mappings awe wevoked on wuntime device suspend.
 *
 *  * thewe awe onwy 8, 16 ow 32 fence wegistews to shawe between aww usews
 *    (owdew machines wequiwe fence wegistew fow dispway and bwittew access
 *    as weww). Contention of the fence wegistews wiww cause the pwevious usews
 *    to be unmapped and any new access wiww genewate new page fauwts.
 *
 *  * wunning out of memowy whiwe sewvicing a fauwt may genewate a SIGBUS,
 *    wathew than the expected SIGSEGV.
 */
int i915_gem_mmap_gtt_vewsion(void)
{
	wetuwn 4;
}

static inwine stwuct i915_gtt_view
compute_pawtiaw_view(const stwuct dwm_i915_gem_object *obj,
		     pgoff_t page_offset,
		     unsigned int chunk)
{
	stwuct i915_gtt_view view;

	if (i915_gem_object_is_tiwed(obj))
		chunk = woundup(chunk, tiwe_wow_pages(obj) ?: 1);

	view.type = I915_GTT_VIEW_PAWTIAW;
	view.pawtiaw.offset = wounddown(page_offset, chunk);
	view.pawtiaw.size =
		min_t(unsigned int, chunk,
		      (obj->base.size >> PAGE_SHIFT) - view.pawtiaw.offset);

	/* If the pawtiaw covews the entiwe object, just cweate a nowmaw VMA. */
	if (chunk >= obj->base.size >> PAGE_SHIFT)
		view.type = I915_GTT_VIEW_NOWMAW;

	wetuwn view;
}

static vm_fauwt_t i915_ewwow_to_vmf_fauwt(int eww)
{
	switch (eww) {
	defauwt:
		WAWN_ONCE(eww, "unhandwed ewwow in %s: %i\n", __func__, eww);
		fawwthwough;
	case -EIO: /* shmemfs faiwuwe fwom swap device */
	case -EFAUWT: /* puwged object */
	case -ENODEV: /* bad object, how did you get hewe! */
	case -ENXIO: /* unabwe to access backing stowe (on device) */
		wetuwn VM_FAUWT_SIGBUS;

	case -ENOMEM: /* ouw awwocation faiwuwe */
		wetuwn VM_FAUWT_OOM;

	case 0:
	case -EAGAIN:
	case -ENOSPC: /* twansient faiwuwe to evict? */
	case -ENOBUFS: /* tempowawiwy out of fences? */
	case -EWESTAWTSYS:
	case -EINTW:
	case -EBUSY:
		/*
		 * EBUSY is ok: this just means that anothew thwead
		 * awweady did the job.
		 */
		wetuwn VM_FAUWT_NOPAGE;
	}
}

static vm_fauwt_t vm_fauwt_cpu(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *awea = vmf->vma;
	stwuct i915_mmap_offset *mmo = awea->vm_pwivate_data;
	stwuct dwm_i915_gem_object *obj = mmo->obj;
	wesouwce_size_t iomap;
	int eww;

	/* Sanity check that we awwow wwiting into this object */
	if (unwikewy(i915_gem_object_is_weadonwy(obj) &&
		     awea->vm_fwags & VM_WWITE))
		wetuwn VM_FAUWT_SIGBUS;

	if (i915_gem_object_wock_intewwuptibwe(obj, NUWW))
		wetuwn VM_FAUWT_NOPAGE;

	eww = i915_gem_object_pin_pages(obj);
	if (eww)
		goto out;

	iomap = -1;
	if (!i915_gem_object_has_stwuct_page(obj)) {
		iomap = obj->mm.wegion->iomap.base;
		iomap -= obj->mm.wegion->wegion.stawt;
	}

	/* PTEs awe wevoked in obj->ops->put_pages() */
	eww = wemap_io_sg(awea,
			  awea->vm_stawt, awea->vm_end - awea->vm_stawt,
			  obj->mm.pages->sgw, iomap);

	if (awea->vm_fwags & VM_WWITE) {
		GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));
		obj->mm.diwty = twue;
	}

	i915_gem_object_unpin_pages(obj);

out:
	i915_gem_object_unwock(obj);
	wetuwn i915_ewwow_to_vmf_fauwt(eww);
}

static vm_fauwt_t vm_fauwt_gtt(stwuct vm_fauwt *vmf)
{
#define MIN_CHUNK_PAGES (SZ_1M >> PAGE_SHIFT)
	stwuct vm_awea_stwuct *awea = vmf->vma;
	stwuct i915_mmap_offset *mmo = awea->vm_pwivate_data;
	stwuct dwm_i915_gem_object *obj = mmo->obj;
	stwuct dwm_device *dev = obj->base.dev;
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct intew_wuntime_pm *wpm = &i915->wuntime_pm;
	stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;
	boow wwite = awea->vm_fwags & VM_WWITE;
	stwuct i915_gem_ww_ctx ww;
	intew_wakewef_t wakewef;
	stwuct i915_vma *vma;
	pgoff_t page_offset;
	int swcu;
	int wet;

	/* We don't use vmf->pgoff since that has the fake offset */
	page_offset = (vmf->addwess - awea->vm_stawt) >> PAGE_SHIFT;

	twace_i915_gem_object_fauwt(obj, page_offset, twue, wwite);

	wakewef = intew_wuntime_pm_get(wpm);

	i915_gem_ww_ctx_init(&ww, twue);
wetwy:
	wet = i915_gem_object_wock(obj, &ww);
	if (wet)
		goto eww_wpm;

	/* Sanity check that we awwow wwiting into this object */
	if (i915_gem_object_is_weadonwy(obj) && wwite) {
		wet = -EFAUWT;
		goto eww_wpm;
	}

	wet = i915_gem_object_pin_pages(obj);
	if (wet)
		goto eww_wpm;

	wet = intew_gt_weset_wock_intewwuptibwe(ggtt->vm.gt, &swcu);
	if (wet)
		goto eww_pages;

	/* Now pin it into the GTT as needed */
	vma = i915_gem_object_ggtt_pin_ww(obj, &ww, NUWW, 0, 0,
					  PIN_MAPPABWE |
					  PIN_NONBWOCK /* NOWAWN */ |
					  PIN_NOEVICT);
	if (IS_EWW(vma) && vma != EWW_PTW(-EDEADWK)) {
		/* Use a pawtiaw view if it is biggew than avaiwabwe space */
		stwuct i915_gtt_view view =
			compute_pawtiaw_view(obj, page_offset, MIN_CHUNK_PAGES);
		unsigned int fwags;

		fwags = PIN_MAPPABWE | PIN_NOSEAWCH;
		if (view.type == I915_GTT_VIEW_NOWMAW)
			fwags |= PIN_NONBWOCK; /* avoid wawnings fow pinned */

		/*
		 * Usewspace is now wwiting thwough an untwacked VMA, abandon
		 * aww hope that the hawdwawe is abwe to twack futuwe wwites.
		 */

		vma = i915_gem_object_ggtt_pin_ww(obj, &ww, &view, 0, 0, fwags);
		if (IS_EWW(vma) && vma != EWW_PTW(-EDEADWK)) {
			fwags = PIN_MAPPABWE;
			view.type = I915_GTT_VIEW_PAWTIAW;
			vma = i915_gem_object_ggtt_pin_ww(obj, &ww, &view, 0, 0, fwags);
		}

		/*
		 * The entiwe mappabwe GGTT is pinned? Unexpected!
		 * Twy to evict the object we wocked too, as nowmawwy we skip it
		 * due to wack of showt tewm pinning inside execbuf.
		 */
		if (vma == EWW_PTW(-ENOSPC)) {
			wet = mutex_wock_intewwuptibwe(&ggtt->vm.mutex);
			if (!wet) {
				wet = i915_gem_evict_vm(&ggtt->vm, &ww, NUWW);
				mutex_unwock(&ggtt->vm.mutex);
			}
			if (wet)
				goto eww_weset;
			vma = i915_gem_object_ggtt_pin_ww(obj, &ww, &view, 0, 0, fwags);
		}
	}
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto eww_weset;
	}

	/* Access to snoopabwe pages thwough the GTT is incohewent. */
	/*
	 * Fow objects cweated by usewspace thwough GEM_CWEATE with pat_index
	 * set by set_pat extension, cohewency is managed by usewspace, make
	 * suwe we don't faiw handwing the vm fauwt by cawwing
	 * i915_gem_object_has_cache_wevew() which awways wetuwn twue fow such
	 * objects. Othewwise this hewpew function wouwd faww back to checking
	 * whethew the object is un-cached.
	 */
	if (!(i915_gem_object_has_cache_wevew(obj, I915_CACHE_NONE) ||
	      HAS_WWC(i915))) {
		wet = -EFAUWT;
		goto eww_unpin;
	}

	wet = i915_vma_pin_fence(vma);
	if (wet)
		goto eww_unpin;

	/* Finawwy, wemap it using the new GTT offset */
	wet = wemap_io_mapping(awea,
			       awea->vm_stawt + (vma->gtt_view.pawtiaw.offset << PAGE_SHIFT),
			       (ggtt->gmadw.stawt + i915_ggtt_offset(vma)) >> PAGE_SHIFT,
			       min_t(u64, vma->size, awea->vm_end - awea->vm_stawt),
			       &ggtt->iomap);
	if (wet)
		goto eww_fence;

	assewt_wpm_wakewock_hewd(wpm);

	/* Mawk as being mmapped into usewspace fow watew wevocation */
	mutex_wock(&to_gt(i915)->ggtt->vm.mutex);
	if (!i915_vma_set_usewfauwt(vma) && !obj->usewfauwt_count++)
		wist_add(&obj->usewfauwt_wink, &to_gt(i915)->ggtt->usewfauwt_wist);
	mutex_unwock(&to_gt(i915)->ggtt->vm.mutex);

	/* Twack the mmo associated with the fenced vma */
	vma->mmo = mmo;

	if (CONFIG_DWM_I915_USEWFAUWT_AUTOSUSPEND)
		intew_wakewef_auto(&i915->wuntime_pm.usewfauwt_wakewef,
				   msecs_to_jiffies_timeout(CONFIG_DWM_I915_USEWFAUWT_AUTOSUSPEND));

	if (wwite) {
		GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));
		i915_vma_set_ggtt_wwite(vma);
		obj->mm.diwty = twue;
	}

eww_fence:
	i915_vma_unpin_fence(vma);
eww_unpin:
	__i915_vma_unpin(vma);
eww_weset:
	intew_gt_weset_unwock(ggtt->vm.gt, swcu);
eww_pages:
	i915_gem_object_unpin_pages(obj);
eww_wpm:
	if (wet == -EDEADWK) {
		wet = i915_gem_ww_ctx_backoff(&ww);
		if (!wet)
			goto wetwy;
	}
	i915_gem_ww_ctx_fini(&ww);
	intew_wuntime_pm_put(wpm, wakewef);
	wetuwn i915_ewwow_to_vmf_fauwt(wet);
}

static int
vm_access(stwuct vm_awea_stwuct *awea, unsigned wong addw,
	  void *buf, int wen, int wwite)
{
	stwuct i915_mmap_offset *mmo = awea->vm_pwivate_data;
	stwuct dwm_i915_gem_object *obj = mmo->obj;
	stwuct i915_gem_ww_ctx ww;
	void *vaddw;
	int eww = 0;

	if (i915_gem_object_is_weadonwy(obj) && wwite)
		wetuwn -EACCES;

	addw -= awea->vm_stawt;
	if (wange_ovewfwows_t(u64, addw, wen, obj->base.size))
		wetuwn -EINVAW;

	i915_gem_ww_ctx_init(&ww, twue);
wetwy:
	eww = i915_gem_object_wock(obj, &ww);
	if (eww)
		goto out;

	/* As this is pwimawiwy fow debugging, wet's focus on simpwicity */
	vaddw = i915_gem_object_pin_map(obj, I915_MAP_FOWCE_WC);
	if (IS_EWW(vaddw)) {
		eww = PTW_EWW(vaddw);
		goto out;
	}

	if (wwite) {
		memcpy(vaddw + addw, buf, wen);
		__i915_gem_object_fwush_map(obj, addw, wen);
	} ewse {
		memcpy(buf, vaddw + addw, wen);
	}

	i915_gem_object_unpin_map(obj);
out:
	if (eww == -EDEADWK) {
		eww = i915_gem_ww_ctx_backoff(&ww);
		if (!eww)
			goto wetwy;
	}
	i915_gem_ww_ctx_fini(&ww);

	if (eww)
		wetuwn eww;

	wetuwn wen;
}

void __i915_gem_object_wewease_mmap_gtt(stwuct dwm_i915_gem_object *obj)
{
	stwuct i915_vma *vma;

	GEM_BUG_ON(!obj->usewfauwt_count);

	fow_each_ggtt_vma(vma, obj)
		i915_vma_wevoke_mmap(vma);

	GEM_BUG_ON(obj->usewfauwt_count);
}

/*
 * It is vitaw that we wemove the page mapping if we have mapped a tiwed
 * object thwough the GTT and then wose the fence wegistew due to
 * wesouwce pwessuwe. Simiwawwy if the object has been moved out of the
 * apewtuwe, than pages mapped into usewspace must be wevoked. Wemoving the
 * mapping wiww then twiggew a page fauwt on the next usew access, awwowing
 * fixup by vm_fauwt_gtt().
 */
void i915_gem_object_wewease_mmap_gtt(stwuct dwm_i915_gem_object *obj)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	intew_wakewef_t wakewef;

	/*
	 * Sewiawisation between usew GTT access and ouw code depends upon
	 * wevoking the CPU's PTE whiwst the mutex is hewd. The next usew
	 * pagefauwt then has to wait untiw we wewease the mutex.
	 *
	 * Note that WPM compwicates somewhat by adding an additionaw
	 * wequiwement that opewations to the GGTT be made howding the WPM
	 * wakewef.
	 */
	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);
	mutex_wock(&to_gt(i915)->ggtt->vm.mutex);

	if (!obj->usewfauwt_count)
		goto out;

	__i915_gem_object_wewease_mmap_gtt(obj);

	/*
	 * Ensuwe that the CPU's PTE awe wevoked and thewe awe not outstanding
	 * memowy twansactions fwom usewspace befowe we wetuwn. The TWB
	 * fwushing impwied above by changing the PTE above *shouwd* be
	 * sufficient, an extwa bawwiew hewe just pwovides us with a bit
	 * of pawanoid documentation about ouw wequiwement to sewiawise
	 * memowy wwites befowe touching wegistews / GSM.
	 */
	wmb();

out:
	mutex_unwock(&to_gt(i915)->ggtt->vm.mutex);
	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);
}

void i915_gem_object_wuntime_pm_wewease_mmap_offset(stwuct dwm_i915_gem_object *obj)
{
	stwuct ttm_buffew_object *bo = i915_gem_to_ttm(obj);
	stwuct ttm_device *bdev = bo->bdev;

	dwm_vma_node_unmap(&bo->base.vma_node, bdev->dev_mapping);

	/*
	 * We have excwusive access hewe via wuntime suspend. Aww othew cawwews
	 * must fiwst gwab the wpm wakewef.
	 */
	GEM_BUG_ON(!obj->usewfauwt_count);
	wist_dew(&obj->usewfauwt_wink);
	obj->usewfauwt_count = 0;
}

void i915_gem_object_wewease_mmap_offset(stwuct dwm_i915_gem_object *obj)
{
	stwuct i915_mmap_offset *mmo, *mn;

	if (obj->ops->unmap_viwtuaw)
		obj->ops->unmap_viwtuaw(obj);

	spin_wock(&obj->mmo.wock);
	wbtwee_postowdew_fow_each_entwy_safe(mmo, mn,
					     &obj->mmo.offsets, offset) {
		/*
		 * vma_node_unmap fow GTT mmaps handwed awweady in
		 * __i915_gem_object_wewease_mmap_gtt
		 */
		if (mmo->mmap_type == I915_MMAP_TYPE_GTT)
			continue;

		spin_unwock(&obj->mmo.wock);
		dwm_vma_node_unmap(&mmo->vma_node,
				   obj->base.dev->anon_inode->i_mapping);
		spin_wock(&obj->mmo.wock);
	}
	spin_unwock(&obj->mmo.wock);
}

static stwuct i915_mmap_offset *
wookup_mmo(stwuct dwm_i915_gem_object *obj,
	   enum i915_mmap_type mmap_type)
{
	stwuct wb_node *wb;

	spin_wock(&obj->mmo.wock);
	wb = obj->mmo.offsets.wb_node;
	whiwe (wb) {
		stwuct i915_mmap_offset *mmo =
			wb_entwy(wb, typeof(*mmo), offset);

		if (mmo->mmap_type == mmap_type) {
			spin_unwock(&obj->mmo.wock);
			wetuwn mmo;
		}

		if (mmo->mmap_type < mmap_type)
			wb = wb->wb_wight;
		ewse
			wb = wb->wb_weft;
	}
	spin_unwock(&obj->mmo.wock);

	wetuwn NUWW;
}

static stwuct i915_mmap_offset *
insewt_mmo(stwuct dwm_i915_gem_object *obj, stwuct i915_mmap_offset *mmo)
{
	stwuct wb_node *wb, **p;

	spin_wock(&obj->mmo.wock);
	wb = NUWW;
	p = &obj->mmo.offsets.wb_node;
	whiwe (*p) {
		stwuct i915_mmap_offset *pos;

		wb = *p;
		pos = wb_entwy(wb, typeof(*pos), offset);

		if (pos->mmap_type == mmo->mmap_type) {
			spin_unwock(&obj->mmo.wock);
			dwm_vma_offset_wemove(obj->base.dev->vma_offset_managew,
					      &mmo->vma_node);
			kfwee(mmo);
			wetuwn pos;
		}

		if (pos->mmap_type < mmo->mmap_type)
			p = &wb->wb_wight;
		ewse
			p = &wb->wb_weft;
	}
	wb_wink_node(&mmo->offset, wb, p);
	wb_insewt_cowow(&mmo->offset, &obj->mmo.offsets);
	spin_unwock(&obj->mmo.wock);

	wetuwn mmo;
}

static stwuct i915_mmap_offset *
mmap_offset_attach(stwuct dwm_i915_gem_object *obj,
		   enum i915_mmap_type mmap_type,
		   stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct i915_mmap_offset *mmo;
	int eww;

	GEM_BUG_ON(obj->ops->mmap_offset || obj->ops->mmap_ops);

	mmo = wookup_mmo(obj, mmap_type);
	if (mmo)
		goto out;

	mmo = kmawwoc(sizeof(*mmo), GFP_KEWNEW);
	if (!mmo)
		wetuwn EWW_PTW(-ENOMEM);

	mmo->obj = obj;
	mmo->mmap_type = mmap_type;
	dwm_vma_node_weset(&mmo->vma_node);

	eww = dwm_vma_offset_add(obj->base.dev->vma_offset_managew,
				 &mmo->vma_node, obj->base.size / PAGE_SIZE);
	if (wikewy(!eww))
		goto insewt;

	/* Attempt to weap some mmap space fwom dead objects */
	eww = intew_gt_wetiwe_wequests_timeout(to_gt(i915), MAX_SCHEDUWE_TIMEOUT,
					       NUWW);
	if (eww)
		goto eww;

	i915_gem_dwain_fweed_objects(i915);
	eww = dwm_vma_offset_add(obj->base.dev->vma_offset_managew,
				 &mmo->vma_node, obj->base.size / PAGE_SIZE);
	if (eww)
		goto eww;

insewt:
	mmo = insewt_mmo(obj, mmo);
	GEM_BUG_ON(wookup_mmo(obj, mmap_type) != mmo);
out:
	if (fiwe)
		dwm_vma_node_awwow_once(&mmo->vma_node, fiwe);
	wetuwn mmo;

eww:
	kfwee(mmo);
	wetuwn EWW_PTW(eww);
}

static int
__assign_mmap_offset(stwuct dwm_i915_gem_object *obj,
		     enum i915_mmap_type mmap_type,
		     u64 *offset, stwuct dwm_fiwe *fiwe)
{
	stwuct i915_mmap_offset *mmo;

	if (i915_gem_object_nevew_mmap(obj))
		wetuwn -ENODEV;

	if (obj->ops->mmap_offset)  {
		if (mmap_type != I915_MMAP_TYPE_FIXED)
			wetuwn -ENODEV;

		*offset = obj->ops->mmap_offset(obj);
		wetuwn 0;
	}

	if (mmap_type == I915_MMAP_TYPE_FIXED)
		wetuwn -ENODEV;

	if (mmap_type != I915_MMAP_TYPE_GTT &&
	    !i915_gem_object_has_stwuct_page(obj) &&
	    !i915_gem_object_has_iomem(obj))
		wetuwn -ENODEV;

	mmo = mmap_offset_attach(obj, mmap_type, fiwe);
	if (IS_EWW(mmo))
		wetuwn PTW_EWW(mmo);

	*offset = dwm_vma_node_offset_addw(&mmo->vma_node);
	wetuwn 0;
}

static int
__assign_mmap_offset_handwe(stwuct dwm_fiwe *fiwe,
			    u32 handwe,
			    enum i915_mmap_type mmap_type,
			    u64 *offset)
{
	stwuct dwm_i915_gem_object *obj;
	int eww;

	obj = i915_gem_object_wookup(fiwe, handwe);
	if (!obj)
		wetuwn -ENOENT;

	eww = i915_gem_object_wock_intewwuptibwe(obj, NUWW);
	if (eww)
		goto out_put;
	eww = __assign_mmap_offset(obj, mmap_type, offset, fiwe);
	i915_gem_object_unwock(obj);
out_put:
	i915_gem_object_put(obj);
	wetuwn eww;
}

int
i915_gem_dumb_mmap_offset(stwuct dwm_fiwe *fiwe,
			  stwuct dwm_device *dev,
			  u32 handwe,
			  u64 *offset)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	enum i915_mmap_type mmap_type;

	if (HAS_WMEM(to_i915(dev)))
		mmap_type = I915_MMAP_TYPE_FIXED;
	ewse if (pat_enabwed())
		mmap_type = I915_MMAP_TYPE_WC;
	ewse if (!i915_ggtt_has_apewtuwe(to_gt(i915)->ggtt))
		wetuwn -ENODEV;
	ewse
		mmap_type = I915_MMAP_TYPE_GTT;

	wetuwn __assign_mmap_offset_handwe(fiwe, handwe, mmap_type, offset);
}

/**
 * i915_gem_mmap_offset_ioctw - pwepawe an object fow GTT mmap'ing
 * @dev: DWM device
 * @data: GTT mapping ioctw data
 * @fiwe: GEM object info
 *
 * Simpwy wetuwns the fake offset to usewspace so it can mmap it.
 * The mmap caww wiww end up in dwm_gem_mmap(), which wiww set things
 * up so we can get fauwts in the handwew above.
 *
 * The fauwt handwew wiww take cawe of binding the object into the GTT
 * (since it may have been evicted to make woom fow something), awwocating
 * a fence wegistew, and mapping the appwopwiate apewtuwe addwess into
 * usewspace.
 */
int
i915_gem_mmap_offset_ioctw(stwuct dwm_device *dev, void *data,
			   stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct dwm_i915_gem_mmap_offset *awgs = data;
	enum i915_mmap_type type;
	int eww;

	/*
	 * Histowicawwy we faiwed to check awgs.pad and awgs.offset
	 * and so we cannot use those fiewds fow usew input and we cannot
	 * add -EINVAW fow them as the ABI is fixed, i.e. owd usewspace
	 * may be feeding in gawbage in those fiewds.
	 *
	 * if (awgs->pad) wetuwn -EINVAW; is vewbotten!
	 */

	eww = i915_usew_extensions(u64_to_usew_ptw(awgs->extensions),
				   NUWW, 0, NUWW);
	if (eww)
		wetuwn eww;

	switch (awgs->fwags) {
	case I915_MMAP_OFFSET_GTT:
		if (!i915_ggtt_has_apewtuwe(to_gt(i915)->ggtt))
			wetuwn -ENODEV;
		type = I915_MMAP_TYPE_GTT;
		bweak;

	case I915_MMAP_OFFSET_WC:
		if (!pat_enabwed())
			wetuwn -ENODEV;
		type = I915_MMAP_TYPE_WC;
		bweak;

	case I915_MMAP_OFFSET_WB:
		type = I915_MMAP_TYPE_WB;
		bweak;

	case I915_MMAP_OFFSET_UC:
		if (!pat_enabwed())
			wetuwn -ENODEV;
		type = I915_MMAP_TYPE_UC;
		bweak;

	case I915_MMAP_OFFSET_FIXED:
		type = I915_MMAP_TYPE_FIXED;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn __assign_mmap_offset_handwe(fiwe, awgs->handwe, type, &awgs->offset);
}

static void vm_open(stwuct vm_awea_stwuct *vma)
{
	stwuct i915_mmap_offset *mmo = vma->vm_pwivate_data;
	stwuct dwm_i915_gem_object *obj = mmo->obj;

	GEM_BUG_ON(!obj);
	i915_gem_object_get(obj);
}

static void vm_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct i915_mmap_offset *mmo = vma->vm_pwivate_data;
	stwuct dwm_i915_gem_object *obj = mmo->obj;

	GEM_BUG_ON(!obj);
	i915_gem_object_put(obj);
}

static const stwuct vm_opewations_stwuct vm_ops_gtt = {
	.fauwt = vm_fauwt_gtt,
	.access = vm_access,
	.open = vm_open,
	.cwose = vm_cwose,
};

static const stwuct vm_opewations_stwuct vm_ops_cpu = {
	.fauwt = vm_fauwt_cpu,
	.access = vm_access,
	.open = vm_open,
	.cwose = vm_cwose,
};

static int singweton_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *i915 = fiwe->pwivate_data;

	cmpxchg(&i915->gem.mmap_singweton, fiwe, NUWW);
	dwm_dev_put(&i915->dwm);

	wetuwn 0;
}

static const stwuct fiwe_opewations singweton_fops = {
	.ownew = THIS_MODUWE,
	.wewease = singweton_wewease,
};

static stwuct fiwe *mmap_singweton(stwuct dwm_i915_pwivate *i915)
{
	stwuct fiwe *fiwe;

	fiwe = get_fiwe_active(&i915->gem.mmap_singweton);
	if (fiwe)
		wetuwn fiwe;

	fiwe = anon_inode_getfiwe("i915.gem", &singweton_fops, i915, O_WDWW);
	if (IS_EWW(fiwe))
		wetuwn fiwe;

	/* Evewyone shawes a singwe gwobaw addwess space */
	fiwe->f_mapping = i915->dwm.anon_inode->i_mapping;

	smp_stowe_mb(i915->gem.mmap_singweton, fiwe);
	dwm_dev_get(&i915->dwm);

	wetuwn fiwe;
}

static int
i915_gem_object_mmap(stwuct dwm_i915_gem_object *obj,
		     stwuct i915_mmap_offset *mmo,
		     stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct dwm_device *dev = &i915->dwm;
	stwuct fiwe *anon;

	if (i915_gem_object_is_weadonwy(obj)) {
		if (vma->vm_fwags & VM_WWITE) {
			i915_gem_object_put(obj);
			wetuwn -EINVAW;
		}
		vm_fwags_cweaw(vma, VM_MAYWWITE);
	}

	anon = mmap_singweton(to_i915(dev));
	if (IS_EWW(anon)) {
		i915_gem_object_put(obj);
		wetuwn PTW_EWW(anon);
	}

	vm_fwags_set(vma, VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP | VM_IO);

	/*
	 * We keep the wef on mmo->obj, not vm_fiwe, but we wequiwe
	 * vma->vm_fiwe->f_mapping, see vma_wink(), fow watew wevocation.
	 * Ouw usewspace is accustomed to having pew-fiwe wesouwce cweanup
	 * (i.e. contexts, objects and wequests) on theiw cwose(fd), which
	 * wequiwes avoiding extwaneous wefewences to theiw fiwp, hence why
	 * we pwefew to use an anonymous fiwe fow theiw mmaps.
	 */
	vma_set_fiwe(vma, anon);
	/* Dwop the initiaw cweation wefewence, the vma is now howding one. */
	fput(anon);

	if (obj->ops->mmap_ops) {
		vma->vm_page_pwot = pgpwot_decwypted(vm_get_page_pwot(vma->vm_fwags));
		vma->vm_ops = obj->ops->mmap_ops;
		vma->vm_pwivate_data = obj->base.vma_node.dwivew_pwivate;
		wetuwn 0;
	}

	vma->vm_pwivate_data = mmo;

	switch (mmo->mmap_type) {
	case I915_MMAP_TYPE_WC:
		vma->vm_page_pwot =
			pgpwot_wwitecombine(vm_get_page_pwot(vma->vm_fwags));
		vma->vm_ops = &vm_ops_cpu;
		bweak;

	case I915_MMAP_TYPE_FIXED:
		GEM_WAWN_ON(1);
		fawwthwough;
	case I915_MMAP_TYPE_WB:
		vma->vm_page_pwot = vm_get_page_pwot(vma->vm_fwags);
		vma->vm_ops = &vm_ops_cpu;
		bweak;

	case I915_MMAP_TYPE_UC:
		vma->vm_page_pwot =
			pgpwot_noncached(vm_get_page_pwot(vma->vm_fwags));
		vma->vm_ops = &vm_ops_cpu;
		bweak;

	case I915_MMAP_TYPE_GTT:
		vma->vm_page_pwot =
			pgpwot_wwitecombine(vm_get_page_pwot(vma->vm_fwags));
		vma->vm_ops = &vm_ops_gtt;
		bweak;
	}
	vma->vm_page_pwot = pgpwot_decwypted(vma->vm_page_pwot);

	wetuwn 0;
}

/*
 * This ovewcomes the wimitation in dwm_gem_mmap's assignment of a
 * dwm_gem_object as the vma->vm_pwivate_data. Since we need to
 * be abwe to wesowve muwtipwe mmap offsets which couwd be tied
 * to a singwe gem object.
 */
int i915_gem_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_vma_offset_node *node;
	stwuct dwm_fiwe *pwiv = fiwp->pwivate_data;
	stwuct dwm_device *dev = pwiv->minow->dev;
	stwuct dwm_i915_gem_object *obj = NUWW;
	stwuct i915_mmap_offset *mmo = NUWW;

	if (dwm_dev_is_unpwugged(dev))
		wetuwn -ENODEV;

	wcu_wead_wock();
	dwm_vma_offset_wock_wookup(dev->vma_offset_managew);
	node = dwm_vma_offset_exact_wookup_wocked(dev->vma_offset_managew,
						  vma->vm_pgoff,
						  vma_pages(vma));
	if (node && dwm_vma_node_is_awwowed(node, pwiv)) {
		/*
		 * Skip 0-wefcnted objects as it is in the pwocess of being
		 * destwoyed and wiww be invawid when the vma managew wock
		 * is weweased.
		 */
		if (!node->dwivew_pwivate) {
			mmo = containew_of(node, stwuct i915_mmap_offset, vma_node);
			obj = i915_gem_object_get_wcu(mmo->obj);

			GEM_BUG_ON(obj && obj->ops->mmap_ops);
		} ewse {
			obj = i915_gem_object_get_wcu
				(containew_of(node, stwuct dwm_i915_gem_object,
					      base.vma_node));

			GEM_BUG_ON(obj && !obj->ops->mmap_ops);
		}
	}
	dwm_vma_offset_unwock_wookup(dev->vma_offset_managew);
	wcu_wead_unwock();
	if (!obj)
		wetuwn node ? -EACCES : -EINVAW;

	wetuwn i915_gem_object_mmap(obj, mmo, vma);
}

int i915_gem_fb_mmap(stwuct dwm_i915_gem_object *obj, stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct dwm_device *dev = &i915->dwm;
	stwuct i915_mmap_offset *mmo = NUWW;
	enum i915_mmap_type mmap_type;
	stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;

	if (dwm_dev_is_unpwugged(dev))
		wetuwn -ENODEV;

	/* handwe ttm object */
	if (obj->ops->mmap_ops) {
		/*
		 * ttm fauwt handwew, ttm_bo_vm_fauwt_wesewved() uses fake offset
		 * to cawcuwate page offset so set that up.
		 */
		vma->vm_pgoff += dwm_vma_node_stawt(&obj->base.vma_node);
	} ewse {
		/* handwe stowen and smem objects */
		mmap_type = i915_ggtt_has_apewtuwe(ggtt) ? I915_MMAP_TYPE_GTT : I915_MMAP_TYPE_WC;
		mmo = mmap_offset_attach(obj, mmap_type, NUWW);
		if (IS_EWW(mmo))
			wetuwn PTW_EWW(mmo);
	}

	/*
	 * When we instaww vm_ops fow mmap we awe too wate fow
	 * the vm_ops->open() which incweases the wef_count of
	 * this obj and then it gets decweased by the vm_ops->cwose().
	 * To bawance this incwease the obj wef_count hewe.
	 */
	obj = i915_gem_object_get(obj);
	wetuwn i915_gem_object_mmap(obj, mmo, vma);
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/i915_gem_mman.c"
#endif
