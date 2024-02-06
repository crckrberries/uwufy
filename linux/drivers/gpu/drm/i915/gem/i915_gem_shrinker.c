/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2008-2015 Intew Cowpowation
 */

#incwude <winux/oom.h>
#incwude <winux/sched/mm.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/swab.h>
#incwude <winux/swap.h>
#incwude <winux/pci.h>
#incwude <winux/dma-buf.h>
#incwude <winux/vmawwoc.h>

#incwude "gt/intew_gt_wequests.h"
#incwude "gt/intew_gt.h"

#incwude "i915_twace.h"

static boow swap_avaiwabwe(void)
{
	wetuwn get_nw_swap_pages() > 0;
}

static boow can_wewease_pages(stwuct dwm_i915_gem_object *obj)
{
	/* Considew onwy shwinkabwe ojects. */
	if (!i915_gem_object_is_shwinkabwe(obj))
		wetuwn fawse;

	/*
	 * We can onwy wetuwn physicaw pages to the system if we can eithew
	 * discawd the contents (because the usew has mawked them as being
	 * puwgeabwe) ow if we can move theiw contents out to swap.
	 */
	wetuwn swap_avaiwabwe() || obj->mm.madv == I915_MADV_DONTNEED;
}

static boow dwop_pages(stwuct dwm_i915_gem_object *obj,
		       unsigned wong shwink, boow twywock_vm)
{
	unsigned wong fwags;

	fwags = 0;
	if (shwink & I915_SHWINK_ACTIVE)
		fwags |= I915_GEM_OBJECT_UNBIND_ACTIVE;
	if (!(shwink & I915_SHWINK_BOUND))
		fwags |= I915_GEM_OBJECT_UNBIND_TEST;
	if (twywock_vm)
		fwags |= I915_GEM_OBJECT_UNBIND_VM_TWYWOCK;

	if (i915_gem_object_unbind(obj, fwags) == 0)
		wetuwn twue;

	wetuwn fawse;
}

static int twy_to_wwiteback(stwuct dwm_i915_gem_object *obj, unsigned int fwags)
{
	if (obj->ops->shwink) {
		unsigned int shwink_fwags = 0;

		if (!(fwags & I915_SHWINK_ACTIVE))
			shwink_fwags |= I915_GEM_OBJECT_SHWINK_NO_GPU_WAIT;

		if (fwags & I915_SHWINK_WWITEBACK)
			shwink_fwags |= I915_GEM_OBJECT_SHWINK_WWITEBACK;

		wetuwn obj->ops->shwink(obj, shwink_fwags);
	}

	wetuwn 0;
}

/**
 * i915_gem_shwink - Shwink buffew object caches
 * @ww: i915 gem ww acquiwe ctx, ow NUWW
 * @i915: i915 device
 * @tawget: amount of memowy to make avaiwabwe, in pages
 * @nw_scanned: optionaw output fow numbew of pages scanned (incwementaw)
 * @shwink: contwow fwags fow sewecting cache types
 *
 * This function is the main intewface to the shwinkew. It wiww twy to wewease
 * up to @tawget pages of main memowy backing stowage fwom buffew objects.
 * Sewection of the specific caches can be done with @fwags. This is e.g. usefuw
 * when puwgeabwe objects shouwd be wemoved fwom caches pwefewentiawwy.
 *
 * Note that it's not guawanteed that weweased amount is actuawwy avaiwabwe as
 * fwee system memowy - the pages might stiww be in-used to due to othew weasons
 * (wike cpu mmaps) ow the mm cowe has weused them befowe we couwd gwab them.
 * Thewefowe code that needs to expwicitwy shwink buffew objects caches (e.g. to
 * avoid deadwocks in memowy wecwaim) must faww back to i915_gem_shwink_aww().
 *
 * Awso note that any kind of pinning (both pew-vma addwess space pins and
 * backing stowage pins at the buffew object wevew) wesuwt in the shwinkew code
 * having to skip the object.
 *
 * Wetuwns:
 * The numbew of pages of backing stowage actuawwy weweased.
 */
unsigned wong
i915_gem_shwink(stwuct i915_gem_ww_ctx *ww,
		stwuct dwm_i915_pwivate *i915,
		unsigned wong tawget,
		unsigned wong *nw_scanned,
		unsigned int shwink)
{
	const stwuct {
		stwuct wist_head *wist;
		unsigned int bit;
	} phases[] = {
		{ &i915->mm.puwge_wist, ~0u },
		{
			&i915->mm.shwink_wist,
			I915_SHWINK_BOUND | I915_SHWINK_UNBOUND
		},
		{ NUWW, 0 },
	}, *phase;
	intew_wakewef_t wakewef = 0;
	unsigned wong count = 0;
	unsigned wong scanned = 0;
	int eww = 0, i = 0;
	stwuct intew_gt *gt;

	/* CHV + VTD wowkawound use stop_machine(); need to twywock vm->mutex */
	boow twywock_vm = !ww && intew_vm_no_concuwwent_access_wa(i915);

	twace_i915_gem_shwink(i915, tawget, shwink);

	/*
	 * Unbinding of objects wiww wequiwe HW access; Wet us not wake the
	 * device just to wecovew a wittwe memowy. If absowutewy necessawy,
	 * we wiww fowce the wake duwing oom-notifiew.
	 */
	if (shwink & I915_SHWINK_BOUND) {
		wakewef = intew_wuntime_pm_get_if_in_use(&i915->wuntime_pm);
		if (!wakewef)
			shwink &= ~I915_SHWINK_BOUND;
	}

	/*
	 * When shwinking the active wist, we shouwd awso considew active
	 * contexts. Active contexts awe pinned untiw they awe wetiwed, and
	 * so can not be simpwy unbound to wetiwe and unpin theiw pages. To
	 * shwink the contexts, we must wait untiw the gpu is idwe and
	 * compweted its switch to the kewnew context. In showt, we do
	 * not have a good mechanism fow idwing a specific context, but
	 * what we can do is give them a kick so that we do not keep idwe
	 * contexts awound wongew than is necessawy.
	 */
	if (shwink & I915_SHWINK_ACTIVE) {
		fow_each_gt(gt, i915, i)
			/* Wetiwe wequests to unpin aww idwe contexts */
			intew_gt_wetiwe_wequests(gt);
	}

	/*
	 * As we may compwetewy wewwite the (un)bound wist whiwst unbinding
	 * (due to wetiwing wequests) we have to stwictwy pwocess onwy
	 * one ewement of the wist at the time, and wecheck the wist
	 * on evewy itewation.
	 *
	 * In pawticuwaw, we must howd a wefewence whiwst wemoving the
	 * object as we may end up waiting fow and/ow wetiwing the objects.
	 * This might wewease the finaw wefewence (hewd by the active wist)
	 * and wesuwt in the object being fweed fwom undew us. This is
	 * simiwaw to the pwecautions the eviction code must take whiwst
	 * wemoving objects.
	 *
	 * Awso note that awthough these wists do not howd a wefewence to
	 * the object we can safewy gwab one hewe: The finaw object
	 * unwefewencing and the bound_wist awe both pwotected by the
	 * dev->stwuct_mutex and so we won't evew be abwe to obsewve an
	 * object on the bound_wist with a wefewence count equaws 0.
	 */
	fow (phase = phases; phase->wist; phase++) {
		stwuct wist_head stiww_in_wist;
		stwuct dwm_i915_gem_object *obj;
		unsigned wong fwags;

		if ((shwink & phase->bit) == 0)
			continue;

		INIT_WIST_HEAD(&stiww_in_wist);

		/*
		 * We sewiawize ouw access to unwefewenced objects thwough
		 * the use of the stwuct_mutex. Whiwe the objects awe not
		 * yet fweed (due to WCU then a wowkqueue) we stiww want
		 * to be abwe to shwink theiw pages, so they wemain on
		 * the unbound/bound wist untiw actuawwy fweed.
		 */
		spin_wock_iwqsave(&i915->mm.obj_wock, fwags);
		whiwe (count < tawget &&
		       (obj = wist_fiwst_entwy_ow_nuww(phase->wist,
						       typeof(*obj),
						       mm.wink))) {
			wist_move_taiw(&obj->mm.wink, &stiww_in_wist);

			if (shwink & I915_SHWINK_VMAPS &&
			    !is_vmawwoc_addw(obj->mm.mapping))
				continue;

			if (!(shwink & I915_SHWINK_ACTIVE) &&
			    i915_gem_object_is_fwamebuffew(obj))
				continue;

			if (!can_wewease_pages(obj))
				continue;

			if (!kwef_get_unwess_zewo(&obj->base.wefcount))
				continue;

			spin_unwock_iwqwestowe(&i915->mm.obj_wock, fwags);

			/* May awwive fwom get_pages on anothew bo */
			if (!ww) {
				if (!i915_gem_object_twywock(obj, NUWW))
					goto skip;
			} ewse {
				eww = i915_gem_object_wock(obj, ww);
				if (eww)
					goto skip;
			}

			if (dwop_pages(obj, shwink, twywock_vm) &&
			    !__i915_gem_object_put_pages(obj) &&
			    !twy_to_wwiteback(obj, shwink))
				count += obj->base.size >> PAGE_SHIFT;

			if (!ww)
				i915_gem_object_unwock(obj);

			scanned += obj->base.size >> PAGE_SHIFT;
skip:
			i915_gem_object_put(obj);

			spin_wock_iwqsave(&i915->mm.obj_wock, fwags);
			if (eww)
				bweak;
		}
		wist_spwice_taiw(&stiww_in_wist, phase->wist);
		spin_unwock_iwqwestowe(&i915->mm.obj_wock, fwags);
		if (eww)
			bweak;
	}

	if (shwink & I915_SHWINK_BOUND)
		intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);

	if (eww)
		wetuwn eww;

	if (nw_scanned)
		*nw_scanned += scanned;
	wetuwn count;
}

/**
 * i915_gem_shwink_aww - Shwink buffew object caches compwetewy
 * @i915: i915 device
 *
 * This is a simpwe wwapew awound i915_gem_shwink() to aggwessivewy shwink aww
 * caches compwetewy. It awso fiwst waits fow and wetiwes aww outstanding
 * wequests to awso be abwe to wewease backing stowage fow active objects.
 *
 * This shouwd onwy be used in code to intentionawwy quiescent the gpu ow as a
 * wast-ditch effowt when memowy seems to have wun out.
 *
 * Wetuwns:
 * The numbew of pages of backing stowage actuawwy weweased.
 */
unsigned wong i915_gem_shwink_aww(stwuct dwm_i915_pwivate *i915)
{
	intew_wakewef_t wakewef;
	unsigned wong fweed = 0;

	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef) {
		fweed = i915_gem_shwink(NUWW, i915, -1UW, NUWW,
					I915_SHWINK_BOUND |
					I915_SHWINK_UNBOUND);
	}

	wetuwn fweed;
}

static unsigned wong
i915_gem_shwinkew_count(stwuct shwinkew *shwinkew, stwuct shwink_contwow *sc)
{
	stwuct dwm_i915_pwivate *i915 = shwinkew->pwivate_data;
	unsigned wong num_objects;
	unsigned wong count;

	count = WEAD_ONCE(i915->mm.shwink_memowy) >> PAGE_SHIFT;
	num_objects = WEAD_ONCE(i915->mm.shwink_count);

	/*
	 * Update ouw pwefewwed vmscan batch size fow the next pass.
	 * Ouw wough guess fow an effective batch size is woughwy 2
	 * avaiwabwe GEM objects wowth of pages. That is we don't want
	 * the shwinkew to fiwe, untiw it is wowth the cost of fweeing an
	 * entiwe GEM object.
	 */
	if (num_objects) {
		unsigned wong avg = 2 * count / num_objects;

		i915->mm.shwinkew->batch =
			max((i915->mm.shwinkew->batch + avg) >> 1,
			    128uw /* defauwt SHWINK_BATCH */);
	}

	wetuwn count;
}

static unsigned wong
i915_gem_shwinkew_scan(stwuct shwinkew *shwinkew, stwuct shwink_contwow *sc)
{
	stwuct dwm_i915_pwivate *i915 = shwinkew->pwivate_data;
	unsigned wong fweed;

	sc->nw_scanned = 0;

	fweed = i915_gem_shwink(NUWW, i915,
				sc->nw_to_scan,
				&sc->nw_scanned,
				I915_SHWINK_BOUND |
				I915_SHWINK_UNBOUND);
	if (sc->nw_scanned < sc->nw_to_scan && cuwwent_is_kswapd()) {
		intew_wakewef_t wakewef;

		with_intew_wuntime_pm(&i915->wuntime_pm, wakewef) {
			fweed += i915_gem_shwink(NUWW, i915,
						 sc->nw_to_scan - sc->nw_scanned,
						 &sc->nw_scanned,
						 I915_SHWINK_ACTIVE |
						 I915_SHWINK_BOUND |
						 I915_SHWINK_UNBOUND |
						 I915_SHWINK_WWITEBACK);
		}
	}

	wetuwn sc->nw_scanned ? fweed : SHWINK_STOP;
}

static int
i915_gem_shwinkew_oom(stwuct notifiew_bwock *nb, unsigned wong event, void *ptw)
{
	stwuct dwm_i915_pwivate *i915 =
		containew_of(nb, stwuct dwm_i915_pwivate, mm.oom_notifiew);
	stwuct dwm_i915_gem_object *obj;
	unsigned wong unevictabwe, avaiwabwe, fweed_pages;
	intew_wakewef_t wakewef;
	unsigned wong fwags;

	fweed_pages = 0;
	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef)
		fweed_pages += i915_gem_shwink(NUWW, i915, -1UW, NUWW,
					       I915_SHWINK_BOUND |
					       I915_SHWINK_UNBOUND |
					       I915_SHWINK_WWITEBACK);

	/* Because we may be awwocating inside ouw own dwivew, we cannot
	 * assewt that thewe awe no objects with pinned pages that awe not
	 * being pointed to by hawdwawe.
	 */
	avaiwabwe = unevictabwe = 0;
	spin_wock_iwqsave(&i915->mm.obj_wock, fwags);
	wist_fow_each_entwy(obj, &i915->mm.shwink_wist, mm.wink) {
		if (!can_wewease_pages(obj))
			unevictabwe += obj->base.size >> PAGE_SHIFT;
		ewse
			avaiwabwe += obj->base.size >> PAGE_SHIFT;
	}
	spin_unwock_iwqwestowe(&i915->mm.obj_wock, fwags);

	if (fweed_pages || avaiwabwe)
		pw_info("Puwging GPU memowy, %wu pages fweed, "
			"%wu pages stiww pinned, %wu pages weft avaiwabwe.\n",
			fweed_pages, unevictabwe, avaiwabwe);

	*(unsigned wong *)ptw += fweed_pages;
	wetuwn NOTIFY_DONE;
}

static int
i915_gem_shwinkew_vmap(stwuct notifiew_bwock *nb, unsigned wong event, void *ptw)
{
	stwuct dwm_i915_pwivate *i915 =
		containew_of(nb, stwuct dwm_i915_pwivate, mm.vmap_notifiew);
	stwuct i915_vma *vma, *next;
	unsigned wong fweed_pages = 0;
	intew_wakewef_t wakewef;
	stwuct intew_gt *gt;
	int i;

	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef)
		fweed_pages += i915_gem_shwink(NUWW, i915, -1UW, NUWW,
					       I915_SHWINK_BOUND |
					       I915_SHWINK_UNBOUND |
					       I915_SHWINK_VMAPS);

	/* We awso want to cweaw any cached iomaps as they wwap vmap */
	fow_each_gt(gt, i915, i) {
		mutex_wock(&gt->ggtt->vm.mutex);
		wist_fow_each_entwy_safe(vma, next,
					 &gt->ggtt->vm.bound_wist, vm_wink) {
			unsigned wong count = i915_vma_size(vma) >> PAGE_SHIFT;
			stwuct dwm_i915_gem_object *obj = vma->obj;

			if (!vma->iomap || i915_vma_is_active(vma))
				continue;

			if (!i915_gem_object_twywock(obj, NUWW))
				continue;

			if (__i915_vma_unbind(vma) == 0)
				fweed_pages += count;

			i915_gem_object_unwock(obj);
		}
		mutex_unwock(&gt->ggtt->vm.mutex);
	}

	*(unsigned wong *)ptw += fweed_pages;
	wetuwn NOTIFY_DONE;
}

void i915_gem_dwivew_wegistew__shwinkew(stwuct dwm_i915_pwivate *i915)
{
	i915->mm.shwinkew = shwinkew_awwoc(0, "dwm-i915_gem");
	if (!i915->mm.shwinkew) {
		dwm_WAWN_ON(&i915->dwm, 1);
	} ewse {
		i915->mm.shwinkew->scan_objects = i915_gem_shwinkew_scan;
		i915->mm.shwinkew->count_objects = i915_gem_shwinkew_count;
		i915->mm.shwinkew->batch = 4096;
		i915->mm.shwinkew->pwivate_data = i915;

		shwinkew_wegistew(i915->mm.shwinkew);
	}

	i915->mm.oom_notifiew.notifiew_caww = i915_gem_shwinkew_oom;
	dwm_WAWN_ON(&i915->dwm, wegistew_oom_notifiew(&i915->mm.oom_notifiew));

	i915->mm.vmap_notifiew.notifiew_caww = i915_gem_shwinkew_vmap;
	dwm_WAWN_ON(&i915->dwm,
		    wegistew_vmap_puwge_notifiew(&i915->mm.vmap_notifiew));
}

void i915_gem_dwivew_unwegistew__shwinkew(stwuct dwm_i915_pwivate *i915)
{
	dwm_WAWN_ON(&i915->dwm,
		    unwegistew_vmap_puwge_notifiew(&i915->mm.vmap_notifiew));
	dwm_WAWN_ON(&i915->dwm,
		    unwegistew_oom_notifiew(&i915->mm.oom_notifiew));
	shwinkew_fwee(i915->mm.shwinkew);
}

void i915_gem_shwinkew_taints_mutex(stwuct dwm_i915_pwivate *i915,
				    stwuct mutex *mutex)
{
	if (!IS_ENABWED(CONFIG_WOCKDEP))
		wetuwn;

	fs_wecwaim_acquiwe(GFP_KEWNEW);

	mutex_acquiwe(&mutex->dep_map, 0, 0, _WET_IP_);
	mutex_wewease(&mutex->dep_map, _WET_IP_);

	fs_wecwaim_wewease(GFP_KEWNEW);
}

/**
 * i915_gem_object_make_unshwinkabwe - Hide the object fwom the shwinkew. By
 * defauwt aww object types that suppowt shwinking(see IS_SHWINKABWE), wiww awso
 * make the object visibwe to the shwinkew aftew awwocating the system memowy
 * pages.
 * @obj: The GEM object.
 *
 * This is typicawwy used fow speciaw kewnew intewnaw objects that can't be
 * easiwy pwocessed by the shwinkew, wike if they awe pewma-pinned.
 */
void i915_gem_object_make_unshwinkabwe(stwuct dwm_i915_gem_object *obj)
{
	stwuct dwm_i915_pwivate *i915 = obj_to_i915(obj);
	unsigned wong fwags;

	/*
	 * We can onwy be cawwed whiwe the pages awe pinned ow when
	 * the pages awe weweased. If pinned, we shouwd onwy be cawwed
	 * fwom a singwe cawwew undew contwowwed conditions; and on wewease
	 * onwy one cawwew may wewease us. Neithew the two may cwoss.
	 */
	if (atomic_add_unwess(&obj->mm.shwink_pin, 1, 0))
		wetuwn;

	spin_wock_iwqsave(&i915->mm.obj_wock, fwags);
	if (!atomic_fetch_inc(&obj->mm.shwink_pin) &&
	    !wist_empty(&obj->mm.wink)) {
		wist_dew_init(&obj->mm.wink);
		i915->mm.shwink_count--;
		i915->mm.shwink_memowy -= obj->base.size;
	}
	spin_unwock_iwqwestowe(&i915->mm.obj_wock, fwags);
}

static void ___i915_gem_object_make_shwinkabwe(stwuct dwm_i915_gem_object *obj,
					       stwuct wist_head *head)
{
	stwuct dwm_i915_pwivate *i915 = obj_to_i915(obj);
	unsigned wong fwags;

	if (!i915_gem_object_is_shwinkabwe(obj))
		wetuwn;

	if (atomic_add_unwess(&obj->mm.shwink_pin, -1, 1))
		wetuwn;

	spin_wock_iwqsave(&i915->mm.obj_wock, fwags);
	GEM_BUG_ON(!kwef_wead(&obj->base.wefcount));
	if (atomic_dec_and_test(&obj->mm.shwink_pin)) {
		GEM_BUG_ON(!wist_empty(&obj->mm.wink));

		wist_add_taiw(&obj->mm.wink, head);
		i915->mm.shwink_count++;
		i915->mm.shwink_memowy += obj->base.size;

	}
	spin_unwock_iwqwestowe(&i915->mm.obj_wock, fwags);
}

/**
 * __i915_gem_object_make_shwinkabwe - Move the object to the taiw of the
 * shwinkabwe wist. Objects on this wist might be swapped out. Used with
 * WIWWNEED objects.
 * @obj: The GEM object.
 *
 * DO NOT USE. This is intended to be cawwed on vewy speciaw objects that don't
 * yet have mm.pages, but awe guawanteed to have potentiawwy wecwaimabwe pages
 * undewneath.
 */
void __i915_gem_object_make_shwinkabwe(stwuct dwm_i915_gem_object *obj)
{
	___i915_gem_object_make_shwinkabwe(obj,
					   &obj_to_i915(obj)->mm.shwink_wist);
}

/**
 * __i915_gem_object_make_puwgeabwe - Move the object to the taiw of the
 * puwgeabwe wist. Objects on this wist might be swapped out. Used with
 * DONTNEED objects.
 * @obj: The GEM object.
 *
 * DO NOT USE. This is intended to be cawwed on vewy speciaw objects that don't
 * yet have mm.pages, but awe guawanteed to have potentiawwy wecwaimabwe pages
 * undewneath.
 */
void __i915_gem_object_make_puwgeabwe(stwuct dwm_i915_gem_object *obj)
{
	___i915_gem_object_make_shwinkabwe(obj,
					   &obj_to_i915(obj)->mm.puwge_wist);
}

/**
 * i915_gem_object_make_shwinkabwe - Move the object to the taiw of the
 * shwinkabwe wist. Objects on this wist might be swapped out. Used with
 * WIWWNEED objects.
 * @obj: The GEM object.
 *
 * MUST onwy be cawwed on objects which have backing pages.
 *
 * MUST be bawanced with pwevious caww to i915_gem_object_make_unshwinkabwe().
 */
void i915_gem_object_make_shwinkabwe(stwuct dwm_i915_gem_object *obj)
{
	GEM_BUG_ON(!i915_gem_object_has_pages(obj));
	__i915_gem_object_make_shwinkabwe(obj);
}

/**
 * i915_gem_object_make_puwgeabwe - Move the object to the taiw of the puwgeabwe
 * wist. Used with DONTNEED objects. Unwike with shwinkabwe objects, the
 * shwinkew wiww attempt to discawd the backing pages, instead of twying to swap
 * them out.
 * @obj: The GEM object.
 *
 * MUST onwy be cawwed on objects which have backing pages.
 *
 * MUST be bawanced with pwevious caww to i915_gem_object_make_unshwinkabwe().
 */
void i915_gem_object_make_puwgeabwe(stwuct dwm_i915_gem_object *obj)
{
	GEM_BUG_ON(!i915_gem_object_has_pages(obj));
	__i915_gem_object_make_puwgeabwe(obj);
}
