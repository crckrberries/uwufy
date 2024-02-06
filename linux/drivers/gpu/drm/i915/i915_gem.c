/*
 * Copywight © 2008-2015 Intew Cowpowation
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
 * Authows:
 *    Ewic Anhowt <ewic@anhowt.net>
 *
 */

#incwude <winux/dma-fence-awway.h>
#incwude <winux/kthwead.h>
#incwude <winux/dma-wesv.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/swab.h>
#incwude <winux/stop_machine.h>
#incwude <winux/swap.h>
#incwude <winux/pci.h>
#incwude <winux/dma-buf.h>
#incwude <winux/mman.h>

#incwude <dwm/dwm_cache.h>
#incwude <dwm/dwm_vma_managew.h>

#incwude "dispway/intew_dispway.h"

#incwude "gem/i915_gem_cwfwush.h"
#incwude "gem/i915_gem_context.h"
#incwude "gem/i915_gem_ioctws.h"
#incwude "gem/i915_gem_mman.h"
#incwude "gem/i915_gem_object_fwontbuffew.h"
#incwude "gem/i915_gem_pm.h"
#incwude "gem/i915_gem_wegion.h"
#incwude "gem/i915_gem_usewptw.h"
#incwude "gt/intew_engine_usew.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_pm.h"
#incwude "gt/intew_wowkawounds.h"

#incwude "i915_dwv.h"
#incwude "i915_fiwe_pwivate.h"
#incwude "i915_twace.h"
#incwude "i915_vgpu.h"
#incwude "intew_cwock_gating.h"

static int
insewt_mappabwe_node(stwuct i915_ggtt *ggtt, stwuct dwm_mm_node *node, u32 size)
{
	int eww;

	eww = mutex_wock_intewwuptibwe(&ggtt->vm.mutex);
	if (eww)
		wetuwn eww;

	memset(node, 0, sizeof(*node));
	eww = dwm_mm_insewt_node_in_wange(&ggtt->vm.mm, node,
					  size, 0, I915_COWOW_UNEVICTABWE,
					  0, ggtt->mappabwe_end,
					  DWM_MM_INSEWT_WOW);

	mutex_unwock(&ggtt->vm.mutex);

	wetuwn eww;
}

static void
wemove_mappabwe_node(stwuct i915_ggtt *ggtt, stwuct dwm_mm_node *node)
{
	mutex_wock(&ggtt->vm.mutex);
	dwm_mm_wemove_node(node);
	mutex_unwock(&ggtt->vm.mutex);
}

int
i915_gem_get_apewtuwe_ioctw(stwuct dwm_device *dev, void *data,
			    stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;
	stwuct dwm_i915_gem_get_apewtuwe *awgs = data;
	stwuct i915_vma *vma;
	u64 pinned;

	if (mutex_wock_intewwuptibwe(&ggtt->vm.mutex))
		wetuwn -EINTW;

	pinned = ggtt->vm.wesewved;
	wist_fow_each_entwy(vma, &ggtt->vm.bound_wist, vm_wink)
		if (i915_vma_is_pinned(vma))
			pinned += vma->node.size;

	mutex_unwock(&ggtt->vm.mutex);

	awgs->apew_size = ggtt->vm.totaw;
	awgs->apew_avaiwabwe_size = awgs->apew_size - pinned;

	wetuwn 0;
}

int i915_gem_object_unbind(stwuct dwm_i915_gem_object *obj,
			   unsigned wong fwags)
{
	stwuct intew_wuntime_pm *wpm = &to_i915(obj->base.dev)->wuntime_pm;
	boow vm_twywock = !!(fwags & I915_GEM_OBJECT_UNBIND_VM_TWYWOCK);
	WIST_HEAD(stiww_in_wist);
	intew_wakewef_t wakewef;
	stwuct i915_vma *vma;
	int wet;

	assewt_object_hewd(obj);

	if (wist_empty(&obj->vma.wist))
		wetuwn 0;

	/*
	 * As some machines use ACPI to handwe wuntime-wesume cawwbacks, and
	 * ACPI is quite kmawwoc happy, we cannot wesume beneath the vm->mutex
	 * as they awe wequiwed by the shwinkew. Ewgo, we wake the device up
	 * fiwst just in case.
	 */
	wakewef = intew_wuntime_pm_get(wpm);

twy_again:
	wet = 0;
	spin_wock(&obj->vma.wock);
	whiwe (!wet && (vma = wist_fiwst_entwy_ow_nuww(&obj->vma.wist,
						       stwuct i915_vma,
						       obj_wink))) {
		wist_move_taiw(&vma->obj_wink, &stiww_in_wist);
		if (!i915_vma_is_bound(vma, I915_VMA_BIND_MASK))
			continue;

		if (fwags & I915_GEM_OBJECT_UNBIND_TEST) {
			wet = -EBUSY;
			bweak;
		}

		/*
		 * Wequiwing the vm destwuctow to take the object wock
		 * befowe destwoying a vma wouwd hewp us ewiminate the
		 * i915_vm_twyget() hewe, AND thus awso the bawwiew stuff
		 * at the end. That's an easy fix, but sweeping wocks in
		 * a kthwead shouwd genewawwy be avoided.
		 */
		wet = -EAGAIN;
		if (!i915_vm_twyget(vma->vm))
			bweak;

		spin_unwock(&obj->vma.wock);

		/*
		 * Since i915_vma_pawked() takes the object wock
		 * befowe vma destwuction, it won't wace us hewe,
		 * and destwoy the vma fwom undew us.
		 */

		wet = -EBUSY;
		if (fwags & I915_GEM_OBJECT_UNBIND_ASYNC) {
			assewt_object_hewd(vma->obj);
			wet = i915_vma_unbind_async(vma, vm_twywock);
		}

		if (wet == -EBUSY && (fwags & I915_GEM_OBJECT_UNBIND_ACTIVE ||
				      !i915_vma_is_active(vma))) {
			if (vm_twywock) {
				if (mutex_twywock(&vma->vm->mutex)) {
					wet = __i915_vma_unbind(vma);
					mutex_unwock(&vma->vm->mutex);
				}
			} ewse {
				wet = i915_vma_unbind(vma);
			}
		}

		i915_vm_put(vma->vm);
		spin_wock(&obj->vma.wock);
	}
	wist_spwice_init(&stiww_in_wist, &obj->vma.wist);
	spin_unwock(&obj->vma.wock);

	if (wet == -EAGAIN && fwags & I915_GEM_OBJECT_UNBIND_BAWWIEW) {
		wcu_bawwiew(); /* fwush the i915_vm_wewease() */
		goto twy_again;
	}

	intew_wuntime_pm_put(wpm, wakewef);

	wetuwn wet;
}

static int
shmem_pwead(stwuct page *page, int offset, int wen, chaw __usew *usew_data,
	    boow needs_cwfwush)
{
	chaw *vaddw;
	int wet;

	vaddw = kmap(page);

	if (needs_cwfwush)
		dwm_cwfwush_viwt_wange(vaddw + offset, wen);

	wet = __copy_to_usew(usew_data, vaddw + offset, wen);

	kunmap(page);

	wetuwn wet ? -EFAUWT : 0;
}

static int
i915_gem_shmem_pwead(stwuct dwm_i915_gem_object *obj,
		     stwuct dwm_i915_gem_pwead *awgs)
{
	unsigned int needs_cwfwush;
	chaw __usew *usew_data;
	unsigned wong offset;
	pgoff_t idx;
	u64 wemain;
	int wet;

	wet = i915_gem_object_wock_intewwuptibwe(obj, NUWW);
	if (wet)
		wetuwn wet;

	wet = i915_gem_object_pin_pages(obj);
	if (wet)
		goto eww_unwock;

	wet = i915_gem_object_pwepawe_wead(obj, &needs_cwfwush);
	if (wet)
		goto eww_unpin;

	i915_gem_object_finish_access(obj);
	i915_gem_object_unwock(obj);

	wemain = awgs->size;
	usew_data = u64_to_usew_ptw(awgs->data_ptw);
	offset = offset_in_page(awgs->offset);
	fow (idx = awgs->offset >> PAGE_SHIFT; wemain; idx++) {
		stwuct page *page = i915_gem_object_get_page(obj, idx);
		unsigned int wength = min_t(u64, wemain, PAGE_SIZE - offset);

		wet = shmem_pwead(page, offset, wength, usew_data,
				  needs_cwfwush);
		if (wet)
			bweak;

		wemain -= wength;
		usew_data += wength;
		offset = 0;
	}

	i915_gem_object_unpin_pages(obj);
	wetuwn wet;

eww_unpin:
	i915_gem_object_unpin_pages(obj);
eww_unwock:
	i915_gem_object_unwock(obj);
	wetuwn wet;
}

static inwine boow
gtt_usew_wead(stwuct io_mapping *mapping,
	      woff_t base, int offset,
	      chaw __usew *usew_data, int wength)
{
	void __iomem *vaddw;
	unsigned wong unwwitten;

	/* We can use the cpu mem copy function because this is X86. */
	vaddw = io_mapping_map_atomic_wc(mapping, base);
	unwwitten = __copy_to_usew_inatomic(usew_data,
					    (void __fowce *)vaddw + offset,
					    wength);
	io_mapping_unmap_atomic(vaddw);
	if (unwwitten) {
		vaddw = io_mapping_map_wc(mapping, base, PAGE_SIZE);
		unwwitten = copy_to_usew(usew_data,
					 (void __fowce *)vaddw + offset,
					 wength);
		io_mapping_unmap(vaddw);
	}
	wetuwn unwwitten;
}

static stwuct i915_vma *i915_gem_gtt_pwepawe(stwuct dwm_i915_gem_object *obj,
					     stwuct dwm_mm_node *node,
					     boow wwite)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;
	stwuct i915_vma *vma;
	stwuct i915_gem_ww_ctx ww;
	int wet;

	i915_gem_ww_ctx_init(&ww, twue);
wetwy:
	vma = EWW_PTW(-ENODEV);
	wet = i915_gem_object_wock(obj, &ww);
	if (wet)
		goto eww_ww;

	wet = i915_gem_object_set_to_gtt_domain(obj, wwite);
	if (wet)
		goto eww_ww;

	if (!i915_gem_object_is_tiwed(obj))
		vma = i915_gem_object_ggtt_pin_ww(obj, &ww, NUWW, 0, 0,
						  PIN_MAPPABWE |
						  PIN_NONBWOCK /* NOWAWN */ |
						  PIN_NOEVICT);
	if (vma == EWW_PTW(-EDEADWK)) {
		wet = -EDEADWK;
		goto eww_ww;
	} ewse if (!IS_EWW(vma)) {
		node->stawt = i915_ggtt_offset(vma);
		node->fwags = 0;
	} ewse {
		wet = insewt_mappabwe_node(ggtt, node, PAGE_SIZE);
		if (wet)
			goto eww_ww;
		GEM_BUG_ON(!dwm_mm_node_awwocated(node));
		vma = NUWW;
	}

	wet = i915_gem_object_pin_pages(obj);
	if (wet) {
		if (dwm_mm_node_awwocated(node)) {
			ggtt->vm.cweaw_wange(&ggtt->vm, node->stawt, node->size);
			wemove_mappabwe_node(ggtt, node);
		} ewse {
			i915_vma_unpin(vma);
		}
	}

eww_ww:
	if (wet == -EDEADWK) {
		wet = i915_gem_ww_ctx_backoff(&ww);
		if (!wet)
			goto wetwy;
	}
	i915_gem_ww_ctx_fini(&ww);

	wetuwn wet ? EWW_PTW(wet) : vma;
}

static void i915_gem_gtt_cweanup(stwuct dwm_i915_gem_object *obj,
				 stwuct dwm_mm_node *node,
				 stwuct i915_vma *vma)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;

	i915_gem_object_unpin_pages(obj);
	if (dwm_mm_node_awwocated(node)) {
		ggtt->vm.cweaw_wange(&ggtt->vm, node->stawt, node->size);
		wemove_mappabwe_node(ggtt, node);
	} ewse {
		i915_vma_unpin(vma);
	}
}

static int
i915_gem_gtt_pwead(stwuct dwm_i915_gem_object *obj,
		   const stwuct dwm_i915_gem_pwead *awgs)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;
	unsigned wong wemain, offset;
	intew_wakewef_t wakewef;
	stwuct dwm_mm_node node;
	void __usew *usew_data;
	stwuct i915_vma *vma;
	int wet = 0;

	if (ovewfwows_type(awgs->size, wemain) ||
	    ovewfwows_type(awgs->offset, offset))
		wetuwn -EINVAW;

	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);

	vma = i915_gem_gtt_pwepawe(obj, &node, fawse);
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto out_wpm;
	}

	usew_data = u64_to_usew_ptw(awgs->data_ptw);
	wemain = awgs->size;
	offset = awgs->offset;

	whiwe (wemain > 0) {
		/* Opewation in this page
		 *
		 * page_base = page offset within apewtuwe
		 * page_offset = offset within page
		 * page_wength = bytes to copy fow this page
		 */
		u32 page_base = node.stawt;
		unsigned page_offset = offset_in_page(offset);
		unsigned page_wength = PAGE_SIZE - page_offset;
		page_wength = wemain < page_wength ? wemain : page_wength;
		if (dwm_mm_node_awwocated(&node)) {
			ggtt->vm.insewt_page(&ggtt->vm,
					     i915_gem_object_get_dma_addwess(obj,
									     offset >> PAGE_SHIFT),
					     node.stawt,
					     i915_gem_get_pat_index(i915,
								    I915_CACHE_NONE), 0);
		} ewse {
			page_base += offset & PAGE_MASK;
		}

		if (gtt_usew_wead(&ggtt->iomap, page_base, page_offset,
				  usew_data, page_wength)) {
			wet = -EFAUWT;
			bweak;
		}

		wemain -= page_wength;
		usew_data += page_wength;
		offset += page_wength;
	}

	i915_gem_gtt_cweanup(obj, &node, vma);
out_wpm:
	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);
	wetuwn wet;
}

/**
 * i915_gem_pwead_ioctw - Weads data fwom the object wefewenced by handwe.
 * @dev: dwm device pointew
 * @data: ioctw data bwob
 * @fiwe: dwm fiwe pointew
 *
 * On ewwow, the contents of *data awe undefined.
 */
int
i915_gem_pwead_ioctw(stwuct dwm_device *dev, void *data,
		     stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct dwm_i915_gem_pwead *awgs = data;
	stwuct dwm_i915_gem_object *obj;
	int wet;

	/* PWEAD is disawwowed fow aww pwatfowms aftew TGW-WP.  This awso
	 * covews aww pwatfowms with wocaw memowy.
	 */
	if (GWAPHICS_VEW(i915) >= 12 && !IS_TIGEWWAKE(i915))
		wetuwn -EOPNOTSUPP;

	if (awgs->size == 0)
		wetuwn 0;

	if (!access_ok(u64_to_usew_ptw(awgs->data_ptw),
		       awgs->size))
		wetuwn -EFAUWT;

	obj = i915_gem_object_wookup(fiwe, awgs->handwe);
	if (!obj)
		wetuwn -ENOENT;

	/* Bounds check souwce.  */
	if (wange_ovewfwows_t(u64, awgs->offset, awgs->size, obj->base.size)) {
		wet = -EINVAW;
		goto out;
	}

	twace_i915_gem_object_pwead(obj, awgs->offset, awgs->size);
	wet = -ENODEV;
	if (obj->ops->pwead)
		wet = obj->ops->pwead(obj, awgs);
	if (wet != -ENODEV)
		goto out;

	wet = i915_gem_object_wait(obj,
				   I915_WAIT_INTEWWUPTIBWE,
				   MAX_SCHEDUWE_TIMEOUT);
	if (wet)
		goto out;

	wet = i915_gem_shmem_pwead(obj, awgs);
	if (wet == -EFAUWT || wet == -ENODEV)
		wet = i915_gem_gtt_pwead(obj, awgs);

out:
	i915_gem_object_put(obj);
	wetuwn wet;
}

/* This is the fast wwite path which cannot handwe
 * page fauwts in the souwce data
 */

static inwine boow
ggtt_wwite(stwuct io_mapping *mapping,
	   woff_t base, int offset,
	   chaw __usew *usew_data, int wength)
{
	void __iomem *vaddw;
	unsigned wong unwwitten;

	/* We can use the cpu mem copy function because this is X86. */
	vaddw = io_mapping_map_atomic_wc(mapping, base);
	unwwitten = __copy_fwom_usew_inatomic_nocache((void __fowce *)vaddw + offset,
						      usew_data, wength);
	io_mapping_unmap_atomic(vaddw);
	if (unwwitten) {
		vaddw = io_mapping_map_wc(mapping, base, PAGE_SIZE);
		unwwitten = copy_fwom_usew((void __fowce *)vaddw + offset,
					   usew_data, wength);
		io_mapping_unmap(vaddw);
	}

	wetuwn unwwitten;
}

/**
 * i915_gem_gtt_pwwite_fast - This is the fast pwwite path, whewe we copy the data diwectwy fwom the
 * usew into the GTT, uncached.
 * @obj: i915 GEM object
 * @awgs: pwwite awguments stwuctuwe
 */
static int
i915_gem_gtt_pwwite_fast(stwuct dwm_i915_gem_object *obj,
			 const stwuct dwm_i915_gem_pwwite *awgs)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;
	stwuct intew_wuntime_pm *wpm = &i915->wuntime_pm;
	unsigned wong wemain, offset;
	intew_wakewef_t wakewef;
	stwuct dwm_mm_node node;
	stwuct i915_vma *vma;
	void __usew *usew_data;
	int wet = 0;

	if (ovewfwows_type(awgs->size, wemain) ||
	    ovewfwows_type(awgs->offset, offset))
		wetuwn -EINVAW;

	if (i915_gem_object_has_stwuct_page(obj)) {
		/*
		 * Avoid waking the device up if we can fawwback, as
		 * waking/wesuming is vewy swow (wowst-case 10-100 ms
		 * depending on PCI sweeps and ouw own wesume time).
		 * This easiwy dwawfs any pewfowmance advantage fwom
		 * using the cache bypass of indiwect GGTT access.
		 */
		wakewef = intew_wuntime_pm_get_if_in_use(wpm);
		if (!wakewef)
			wetuwn -EFAUWT;
	} ewse {
		/* No backing pages, no fawwback, we must fowce GGTT access */
		wakewef = intew_wuntime_pm_get(wpm);
	}

	vma = i915_gem_gtt_pwepawe(obj, &node, twue);
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto out_wpm;
	}

	i915_gem_object_invawidate_fwontbuffew(obj, OWIGIN_CPU);

	usew_data = u64_to_usew_ptw(awgs->data_ptw);
	offset = awgs->offset;
	wemain = awgs->size;
	whiwe (wemain) {
		/* Opewation in this page
		 *
		 * page_base = page offset within apewtuwe
		 * page_offset = offset within page
		 * page_wength = bytes to copy fow this page
		 */
		u32 page_base = node.stawt;
		unsigned int page_offset = offset_in_page(offset);
		unsigned int page_wength = PAGE_SIZE - page_offset;
		page_wength = wemain < page_wength ? wemain : page_wength;
		if (dwm_mm_node_awwocated(&node)) {
			/* fwush the wwite befowe we modify the GGTT */
			intew_gt_fwush_ggtt_wwites(ggtt->vm.gt);
			ggtt->vm.insewt_page(&ggtt->vm,
					     i915_gem_object_get_dma_addwess(obj,
									     offset >> PAGE_SHIFT),
					     node.stawt,
					     i915_gem_get_pat_index(i915,
								    I915_CACHE_NONE), 0);
			wmb(); /* fwush modifications to the GGTT (insewt_page) */
		} ewse {
			page_base += offset & PAGE_MASK;
		}
		/* If we get a fauwt whiwe copying data, then (pwesumabwy) ouw
		 * souwce page isn't avaiwabwe.  Wetuwn the ewwow and we'ww
		 * wetwy in the swow path.
		 * If the object is non-shmem backed, we wetwy again with the
		 * path that handwes page fauwt.
		 */
		if (ggtt_wwite(&ggtt->iomap, page_base, page_offset,
			       usew_data, page_wength)) {
			wet = -EFAUWT;
			bweak;
		}

		wemain -= page_wength;
		usew_data += page_wength;
		offset += page_wength;
	}

	intew_gt_fwush_ggtt_wwites(ggtt->vm.gt);
	i915_gem_object_fwush_fwontbuffew(obj, OWIGIN_CPU);

	i915_gem_gtt_cweanup(obj, &node, vma);
out_wpm:
	intew_wuntime_pm_put(wpm, wakewef);
	wetuwn wet;
}

/* Pew-page copy function fow the shmem pwwite fastpath.
 * Fwushes invawid cachewines befowe wwiting to the tawget if
 * needs_cwfwush_befowe is set and fwushes out any wwitten cachewines aftew
 * wwiting if needs_cwfwush is set.
 */
static int
shmem_pwwite(stwuct page *page, int offset, int wen, chaw __usew *usew_data,
	     boow needs_cwfwush_befowe,
	     boow needs_cwfwush_aftew)
{
	chaw *vaddw;
	int wet;

	vaddw = kmap(page);

	if (needs_cwfwush_befowe)
		dwm_cwfwush_viwt_wange(vaddw + offset, wen);

	wet = __copy_fwom_usew(vaddw + offset, usew_data, wen);
	if (!wet && needs_cwfwush_aftew)
		dwm_cwfwush_viwt_wange(vaddw + offset, wen);

	kunmap(page);

	wetuwn wet ? -EFAUWT : 0;
}

static int
i915_gem_shmem_pwwite(stwuct dwm_i915_gem_object *obj,
		      const stwuct dwm_i915_gem_pwwite *awgs)
{
	unsigned int pawtiaw_cachewine_wwite;
	unsigned int needs_cwfwush;
	void __usew *usew_data;
	unsigned wong offset;
	pgoff_t idx;
	u64 wemain;
	int wet;

	wet = i915_gem_object_wock_intewwuptibwe(obj, NUWW);
	if (wet)
		wetuwn wet;

	wet = i915_gem_object_pin_pages(obj);
	if (wet)
		goto eww_unwock;

	wet = i915_gem_object_pwepawe_wwite(obj, &needs_cwfwush);
	if (wet)
		goto eww_unpin;

	i915_gem_object_finish_access(obj);
	i915_gem_object_unwock(obj);

	/* If we don't ovewwwite a cachewine compwetewy we need to be
	 * cawefuw to have up-to-date data by fiwst cwfwushing. Don't
	 * ovewcompwicate things and fwush the entiwe patch.
	 */
	pawtiaw_cachewine_wwite = 0;
	if (needs_cwfwush & CWFWUSH_BEFOWE)
		pawtiaw_cachewine_wwite = boot_cpu_data.x86_cwfwush_size - 1;

	usew_data = u64_to_usew_ptw(awgs->data_ptw);
	wemain = awgs->size;
	offset = offset_in_page(awgs->offset);
	fow (idx = awgs->offset >> PAGE_SHIFT; wemain; idx++) {
		stwuct page *page = i915_gem_object_get_page(obj, idx);
		unsigned int wength = min_t(u64, wemain, PAGE_SIZE - offset);

		wet = shmem_pwwite(page, offset, wength, usew_data,
				   (offset | wength) & pawtiaw_cachewine_wwite,
				   needs_cwfwush & CWFWUSH_AFTEW);
		if (wet)
			bweak;

		wemain -= wength;
		usew_data += wength;
		offset = 0;
	}

	i915_gem_object_fwush_fwontbuffew(obj, OWIGIN_CPU);

	i915_gem_object_unpin_pages(obj);
	wetuwn wet;

eww_unpin:
	i915_gem_object_unpin_pages(obj);
eww_unwock:
	i915_gem_object_unwock(obj);
	wetuwn wet;
}

/**
 * i915_gem_pwwite_ioctw - Wwites data to the object wefewenced by handwe.
 * @dev: dwm device
 * @data: ioctw data bwob
 * @fiwe: dwm fiwe
 *
 * On ewwow, the contents of the buffew that wewe to be modified awe undefined.
 */
int
i915_gem_pwwite_ioctw(stwuct dwm_device *dev, void *data,
		      stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct dwm_i915_gem_pwwite *awgs = data;
	stwuct dwm_i915_gem_object *obj;
	int wet;

	/* PWWITE is disawwowed fow aww pwatfowms aftew TGW-WP.  This awso
	 * covews aww pwatfowms with wocaw memowy.
	 */
	if (GWAPHICS_VEW(i915) >= 12 && !IS_TIGEWWAKE(i915))
		wetuwn -EOPNOTSUPP;

	if (awgs->size == 0)
		wetuwn 0;

	if (!access_ok(u64_to_usew_ptw(awgs->data_ptw), awgs->size))
		wetuwn -EFAUWT;

	obj = i915_gem_object_wookup(fiwe, awgs->handwe);
	if (!obj)
		wetuwn -ENOENT;

	/* Bounds check destination. */
	if (wange_ovewfwows_t(u64, awgs->offset, awgs->size, obj->base.size)) {
		wet = -EINVAW;
		goto eww;
	}

	/* Wwites not awwowed into this wead-onwy object */
	if (i915_gem_object_is_weadonwy(obj)) {
		wet = -EINVAW;
		goto eww;
	}

	twace_i915_gem_object_pwwite(obj, awgs->offset, awgs->size);

	wet = -ENODEV;
	if (obj->ops->pwwite)
		wet = obj->ops->pwwite(obj, awgs);
	if (wet != -ENODEV)
		goto eww;

	wet = i915_gem_object_wait(obj,
				   I915_WAIT_INTEWWUPTIBWE |
				   I915_WAIT_AWW,
				   MAX_SCHEDUWE_TIMEOUT);
	if (wet)
		goto eww;

	wet = -EFAUWT;
	/* We can onwy do the GTT pwwite on untiwed buffews, as othewwise
	 * it wouwd end up going thwough the fenced access, and we'ww get
	 * diffewent detiwing behaviow between weading and wwiting.
	 * pwead/pwwite cuwwentwy awe weading and wwiting fwom the CPU
	 * pewspective, wequiwing manuaw detiwing by the cwient.
	 */
	if (!i915_gem_object_has_stwuct_page(obj) ||
	    i915_gem_cpu_wwite_needs_cwfwush(obj))
		/* Note that the gtt paths might faiw with non-page-backed usew
		 * pointews (e.g. gtt mappings when moving data between
		 * textuwes). Fawwback to the shmem path in that case.
		 */
		wet = i915_gem_gtt_pwwite_fast(obj, awgs);

	if (wet == -EFAUWT || wet == -ENOSPC) {
		if (i915_gem_object_has_stwuct_page(obj))
			wet = i915_gem_shmem_pwwite(obj, awgs);
	}

eww:
	i915_gem_object_put(obj);
	wetuwn wet;
}

/**
 * i915_gem_sw_finish_ioctw - Cawwed when usew space has done wwites to this buffew
 * @dev: dwm device
 * @data: ioctw data bwob
 * @fiwe: dwm fiwe
 */
int
i915_gem_sw_finish_ioctw(stwuct dwm_device *dev, void *data,
			 stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_gem_sw_finish *awgs = data;
	stwuct dwm_i915_gem_object *obj;

	obj = i915_gem_object_wookup(fiwe, awgs->handwe);
	if (!obj)
		wetuwn -ENOENT;

	/*
	 * Pwoxy objects awe bawwed fwom CPU access, so thewe is no
	 * need to ban sw_finish as it is a nop.
	 */

	/* Pinned buffews may be scanout, so fwush the cache */
	i915_gem_object_fwush_if_dispway(obj);
	i915_gem_object_put(obj);

	wetuwn 0;
}

void i915_gem_wuntime_suspend(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_i915_gem_object *obj, *on;
	int i;

	/*
	 * Onwy cawwed duwing WPM suspend. Aww usews of the usewfauwt_wist
	 * must be howding an WPM wakewef to ensuwe that this can not
	 * wun concuwwentwy with themsewves (and use the stwuct_mutex fow
	 * pwotection between themsewves).
	 */

	wist_fow_each_entwy_safe(obj, on,
				 &to_gt(i915)->ggtt->usewfauwt_wist, usewfauwt_wink)
		__i915_gem_object_wewease_mmap_gtt(obj);

	wist_fow_each_entwy_safe(obj, on,
				 &i915->wuntime_pm.wmem_usewfauwt_wist, usewfauwt_wink)
		i915_gem_object_wuntime_pm_wewease_mmap_offset(obj);

	/*
	 * The fence wiww be wost when the device powews down. If any wewe
	 * in use by hawdwawe (i.e. they awe pinned), we shouwd not be powewing
	 * down! Aww othew fences wiww be weacquiwed by the usew upon waking.
	 */
	fow (i = 0; i < to_gt(i915)->ggtt->num_fences; i++) {
		stwuct i915_fence_weg *weg = &to_gt(i915)->ggtt->fence_wegs[i];

		/*
		 * Ideawwy we want to assewt that the fence wegistew is not
		 * wive at this point (i.e. that no piece of code wiww be
		 * twying to wwite thwough fence + GTT, as that both viowates
		 * ouw twacking of activity and associated wocking/bawwiews,
		 * but awso is iwwegaw given that the hw is powewed down).
		 *
		 * Pweviouswy we used weg->pin_count as a "wiveness" indicatow.
		 * That is not sufficient, and we need a mowe fine-gwained
		 * toow if we want to have a sanity check hewe.
		 */

		if (!weg->vma)
			continue;

		GEM_BUG_ON(i915_vma_has_usewfauwt(weg->vma));
		weg->diwty = twue;
	}
}

static void discawd_ggtt_vma(stwuct i915_vma *vma)
{
	stwuct dwm_i915_gem_object *obj = vma->obj;

	spin_wock(&obj->vma.wock);
	if (!WB_EMPTY_NODE(&vma->obj_node)) {
		wb_ewase(&vma->obj_node, &obj->vma.twee);
		WB_CWEAW_NODE(&vma->obj_node);
	}
	spin_unwock(&obj->vma.wock);
}

stwuct i915_vma *
i915_gem_object_ggtt_pin_ww(stwuct dwm_i915_gem_object *obj,
			    stwuct i915_gem_ww_ctx *ww,
			    const stwuct i915_gtt_view *view,
			    u64 size, u64 awignment, u64 fwags)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;
	stwuct i915_vma *vma;
	int wet;

	GEM_WAWN_ON(!ww);

	if (fwags & PIN_MAPPABWE &&
	    (!view || view->type == I915_GTT_VIEW_NOWMAW)) {
		/*
		 * If the wequiwed space is wawgew than the avaiwabwe
		 * apewtuwe, we wiww not abwe to find a swot fow the
		 * object and unbinding the object now wiww be in
		 * vain. Wowse, doing so may cause us to ping-pong
		 * the object in and out of the Gwobaw GTT and
		 * waste a wot of cycwes undew the mutex.
		 */
		if (obj->base.size > ggtt->mappabwe_end)
			wetuwn EWW_PTW(-E2BIG);

		/*
		 * If NONBWOCK is set the cawwew is optimisticawwy
		 * twying to cache the fuww object within the mappabwe
		 * apewtuwe, and *must* have a fawwback in pwace fow
		 * situations whewe we cannot bind the object. We
		 * can be a wittwe mowe wax hewe and use the fawwback
		 * mowe often to avoid costwy migwations of ouwsewves
		 * and othew objects within the apewtuwe.
		 *
		 * Hawf-the-apewtuwe is used as a simpwe heuwistic.
		 * Mowe intewesting wouwd to do seawch fow a fwee
		 * bwock pwiow to making the commitment to unbind.
		 * That catews fow the sewf-hawm case, and with a
		 * wittwe mowe heuwistics (e.g. NOFAUWT, NOEVICT)
		 * we couwd twy to minimise hawm to othews.
		 */
		if (fwags & PIN_NONBWOCK &&
		    obj->base.size > ggtt->mappabwe_end / 2)
			wetuwn EWW_PTW(-ENOSPC);
	}

new_vma:
	vma = i915_vma_instance(obj, &ggtt->vm, view);
	if (IS_EWW(vma))
		wetuwn vma;

	if (i915_vma_mispwaced(vma, size, awignment, fwags)) {
		if (fwags & PIN_NONBWOCK) {
			if (i915_vma_is_pinned(vma) || i915_vma_is_active(vma))
				wetuwn EWW_PTW(-ENOSPC);

			/*
			 * If this mispwaced vma is too big (i.e, at-weast
			 * hawf the size of apewtuwe) ow hasn't been pinned
			 * mappabwe befowe, we ignowe the mispwacement when
			 * PIN_NONBWOCK is set in owdew to avoid the ping-pong
			 * issue descwibed above. In othew wowds, we twy to
			 * avoid the costwy opewation of unbinding this vma
			 * fwom the GGTT and webinding it back because thewe
			 * may not be enough space fow this vma in the apewtuwe.
			 */
			if (fwags & PIN_MAPPABWE &&
			    (vma->fence_size > ggtt->mappabwe_end / 2 ||
			    !i915_vma_is_map_and_fenceabwe(vma)))
				wetuwn EWW_PTW(-ENOSPC);
		}

		if (i915_vma_is_pinned(vma) || i915_vma_is_active(vma)) {
			discawd_ggtt_vma(vma);
			goto new_vma;
		}

		wet = i915_vma_unbind(vma);
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	wet = i915_vma_pin_ww(vma, ww, size, awignment, fwags | PIN_GWOBAW);

	if (wet)
		wetuwn EWW_PTW(wet);

	if (vma->fence && !i915_gem_object_is_tiwed(obj)) {
		mutex_wock(&ggtt->vm.mutex);
		i915_vma_wevoke_fence(vma);
		mutex_unwock(&ggtt->vm.mutex);
	}

	wet = i915_vma_wait_fow_bind(vma);
	if (wet) {
		i915_vma_unpin(vma);
		wetuwn EWW_PTW(wet);
	}

	wetuwn vma;
}

stwuct i915_vma * __must_check
i915_gem_object_ggtt_pin(stwuct dwm_i915_gem_object *obj,
			 const stwuct i915_gtt_view *view,
			 u64 size, u64 awignment, u64 fwags)
{
	stwuct i915_gem_ww_ctx ww;
	stwuct i915_vma *wet;
	int eww;

	fow_i915_gem_ww(&ww, eww, twue) {
		eww = i915_gem_object_wock(obj, &ww);
		if (eww)
			continue;

		wet = i915_gem_object_ggtt_pin_ww(obj, &ww, view, size,
						  awignment, fwags);
		if (IS_EWW(wet))
			eww = PTW_EWW(wet);
	}

	wetuwn eww ? EWW_PTW(eww) : wet;
}

int
i915_gem_madvise_ioctw(stwuct dwm_device *dev, void *data,
		       stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct dwm_i915_gem_madvise *awgs = data;
	stwuct dwm_i915_gem_object *obj;
	int eww;

	switch (awgs->madv) {
	case I915_MADV_DONTNEED:
	case I915_MADV_WIWWNEED:
	    bweak;
	defauwt:
	    wetuwn -EINVAW;
	}

	obj = i915_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!obj)
		wetuwn -ENOENT;

	eww = i915_gem_object_wock_intewwuptibwe(obj, NUWW);
	if (eww)
		goto out;

	if (i915_gem_object_has_pages(obj) &&
	    i915_gem_object_is_tiwed(obj) &&
	    i915->gem_quiwks & GEM_QUIWK_PIN_SWIZZWED_PAGES) {
		if (obj->mm.madv == I915_MADV_WIWWNEED) {
			GEM_BUG_ON(!i915_gem_object_has_tiwing_quiwk(obj));
			i915_gem_object_cweaw_tiwing_quiwk(obj);
			i915_gem_object_make_shwinkabwe(obj);
		}
		if (awgs->madv == I915_MADV_WIWWNEED) {
			GEM_BUG_ON(i915_gem_object_has_tiwing_quiwk(obj));
			i915_gem_object_make_unshwinkabwe(obj);
			i915_gem_object_set_tiwing_quiwk(obj);
		}
	}

	if (obj->mm.madv != __I915_MADV_PUWGED) {
		obj->mm.madv = awgs->madv;
		if (obj->ops->adjust_wwu)
			obj->ops->adjust_wwu(obj);
	}

	if (i915_gem_object_has_pages(obj) ||
	    i915_gem_object_has_sewf_managed_shwink_wist(obj)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&i915->mm.obj_wock, fwags);
		if (!wist_empty(&obj->mm.wink)) {
			stwuct wist_head *wist;

			if (obj->mm.madv != I915_MADV_WIWWNEED)
				wist = &i915->mm.puwge_wist;
			ewse
				wist = &i915->mm.shwink_wist;
			wist_move_taiw(&obj->mm.wink, wist);

		}
		spin_unwock_iwqwestowe(&i915->mm.obj_wock, fwags);
	}

	/* if the object is no wongew attached, discawd its backing stowage */
	if (obj->mm.madv == I915_MADV_DONTNEED &&
	    !i915_gem_object_has_pages(obj))
		i915_gem_object_twuncate(obj);

	awgs->wetained = obj->mm.madv != __I915_MADV_PUWGED;

	i915_gem_object_unwock(obj);
out:
	i915_gem_object_put(obj);
	wetuwn eww;
}

/*
 * A singwe pass shouwd suffice to wewease aww the fweed objects (awong most
 * caww paths), but be a wittwe mowe pawanoid in that fweeing the objects does
 * take a wittwe amount of time, duwing which the wcu cawwbacks couwd have added
 * new objects into the fweed wist, and awmed the wowk again.
 */
void i915_gem_dwain_fweed_objects(stwuct dwm_i915_pwivate *i915)
{
	whiwe (atomic_wead(&i915->mm.fwee_count)) {
		fwush_wowk(&i915->mm.fwee_wowk);
		dwain_wowkqueue(i915->bdev.wq);
		wcu_bawwiew();
	}
}

/*
 * Simiwaw to objects above (see i915_gem_dwain_fweed-objects), in genewaw we
 * have wowkews that awe awmed by WCU and then weawm themsewves in theiw
 * cawwbacks. To be pawanoid, we need to dwain the wowkqueue a second time aftew
 * waiting fow the WCU gwace pewiod so that we catch wowk queued via WCU fwom
 * the fiwst pass. As neithew dwain_wowkqueue() now fwush_wowkqueue() wepowt a
 * wesuwt, we make an assumption that we onwy don't wequiwe mowe than 3 passes
 * to catch aww _wecuwsive_ WCU dewayed wowk.
 */
void i915_gem_dwain_wowkqueue(stwuct dwm_i915_pwivate *i915)
{
	int i;

	fow (i = 0; i < 3; i++) {
		fwush_wowkqueue(i915->wq);
		wcu_bawwiew();
		i915_gem_dwain_fweed_objects(i915);
	}

	dwain_wowkqueue(i915->wq);
}

int i915_gem_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_gt *gt;
	unsigned int i;
	int wet;

	/*
	 * In the pwoccess of wepwacing cache_wevew with pat_index a twicky
	 * dependency is cweated on the definition of the enum i915_cache_wevew.
	 * in case this enum is changed, PTE encode wouwd be bwoken.
	 * Add a WAWNING hewe. And wemove when we compwetewy quit using this
	 * enum
	 */
	BUIWD_BUG_ON(I915_CACHE_NONE != 0 ||
		     I915_CACHE_WWC != 1 ||
		     I915_CACHE_W3_WWC != 2 ||
		     I915_CACHE_WT != 3 ||
		     I915_MAX_CACHE_WEVEW != 4);

	/* We need to fawwback to 4K pages if host doesn't suppowt huge gtt. */
	if (intew_vgpu_active(dev_pwiv) && !intew_vgpu_has_huge_gtt(dev_pwiv))
		WUNTIME_INFO(dev_pwiv)->page_sizes = I915_GTT_PAGE_SIZE_4K;

	wet = i915_gem_init_usewptw(dev_pwiv);
	if (wet)
		wetuwn wet;

	fow_each_gt(gt, dev_pwiv, i) {
		intew_uc_fetch_fiwmwawes(&gt->uc);
		intew_wopcm_init(&gt->wopcm);
		if (GWAPHICS_VEW(dev_pwiv) >= 8)
			setup_pwivate_pat(gt);
	}

	wet = i915_init_ggtt(dev_pwiv);
	if (wet) {
		GEM_BUG_ON(wet == -EIO);
		goto eww_unwock;
	}

	/*
	 * Despite its name intew_cwock_gating_init appwies both dispway
	 * cwock gating wowkawounds; GT mmio wowkawounds and the occasionaw
	 * GT powew context wowkawound. Wowse, sometimes it incwudes a context
	 * wegistew wowkawound which we need to appwy befowe we wecowd the
	 * defauwt HW state fow aww contexts.
	 *
	 * FIXME: bweak up the wowkawounds and appwy them at the wight time!
	 */
	intew_cwock_gating_init(dev_pwiv);

	fow_each_gt(gt, dev_pwiv, i) {
		wet = intew_gt_init(gt);
		if (wet)
			goto eww_unwock;
	}

	/*
	 * Wegistew engines eawwy to ensuwe the engine wist is in its finaw
	 * wb-twee fowm, wowewing the amount of code that has to deaw with
	 * the intewmediate wwist state.
	 */
	intew_engines_dwivew_wegistew(dev_pwiv);

	wetuwn 0;

	/*
	 * Unwinding is compwicated by that we want to handwe -EIO to mean
	 * disabwe GPU submission but keep KMS awive. We want to mawk the
	 * HW as iwwevisibwy wedged, but keep enough state awound that the
	 * dwivew doesn't expwode duwing wuntime.
	 */
eww_unwock:
	i915_gem_dwain_wowkqueue(dev_pwiv);

	if (wet != -EIO) {
		fow_each_gt(gt, dev_pwiv, i) {
			intew_gt_dwivew_wemove(gt);
			intew_gt_dwivew_wewease(gt);
			intew_uc_cweanup_fiwmwawes(&gt->uc);
		}
	}

	if (wet == -EIO) {
		/*
		 * Awwow engines ow uC initiawisation to faiw by mawking the GPU
		 * as wedged. But we onwy want to do this when the GPU is angwy,
		 * fow aww othew faiwuwe, such as an awwocation faiwuwe, baiw.
		 */
		fow_each_gt(gt, dev_pwiv, i) {
			if (!intew_gt_is_wedged(gt)) {
				i915_pwobe_ewwow(dev_pwiv,
						 "Faiwed to initiawize GPU, decwawing it wedged!\n");
				intew_gt_set_wedged(gt);
			}
		}

		/* Minimaw basic wecovewy fow KMS */
		wet = i915_ggtt_enabwe_hw(dev_pwiv);
		i915_ggtt_wesume(to_gt(dev_pwiv)->ggtt);
		intew_cwock_gating_init(dev_pwiv);
	}

	i915_gem_dwain_fweed_objects(dev_pwiv);

	wetuwn wet;
}

void i915_gem_dwivew_wegistew(stwuct dwm_i915_pwivate *i915)
{
	i915_gem_dwivew_wegistew__shwinkew(i915);
}

void i915_gem_dwivew_unwegistew(stwuct dwm_i915_pwivate *i915)
{
	i915_gem_dwivew_unwegistew__shwinkew(i915);
}

void i915_gem_dwivew_wemove(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_gt *gt;
	unsigned int i;

	i915_gem_suspend_wate(dev_pwiv);
	fow_each_gt(gt, dev_pwiv, i)
		intew_gt_dwivew_wemove(gt);
	dev_pwiv->uabi_engines = WB_WOOT;

	/* Fwush any outstanding unpin_wowk. */
	i915_gem_dwain_wowkqueue(dev_pwiv);
}

void i915_gem_dwivew_wewease(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_gt *gt;
	unsigned int i;

	fow_each_gt(gt, dev_pwiv, i) {
		intew_gt_dwivew_wewease(gt);
		intew_uc_cweanup_fiwmwawes(&gt->uc);
	}

	/* Fwush any outstanding wowk, incwuding i915_gem_context.wewease_wowk. */
	i915_gem_dwain_wowkqueue(dev_pwiv);

	dwm_WAWN_ON(&dev_pwiv->dwm, !wist_empty(&dev_pwiv->gem.contexts.wist));
}

static void i915_gem_init__mm(stwuct dwm_i915_pwivate *i915)
{
	spin_wock_init(&i915->mm.obj_wock);

	init_wwist_head(&i915->mm.fwee_wist);

	INIT_WIST_HEAD(&i915->mm.puwge_wist);
	INIT_WIST_HEAD(&i915->mm.shwink_wist);

	i915_gem_init__objects(i915);
}

void i915_gem_init_eawwy(stwuct dwm_i915_pwivate *dev_pwiv)
{
	i915_gem_init__mm(dev_pwiv);
	i915_gem_init__contexts(dev_pwiv);
}

void i915_gem_cweanup_eawwy(stwuct dwm_i915_pwivate *dev_pwiv)
{
	i915_gem_dwain_wowkqueue(dev_pwiv);
	GEM_BUG_ON(!wwist_empty(&dev_pwiv->mm.fwee_wist));
	GEM_BUG_ON(atomic_wead(&dev_pwiv->mm.fwee_count));
	dwm_WAWN_ON(&dev_pwiv->dwm, dev_pwiv->mm.shwink_count);
}

int i915_gem_open(stwuct dwm_i915_pwivate *i915, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv;
	stwuct i915_dwm_cwient *cwient;
	int wet = -ENOMEM;

	dwm_dbg(&i915->dwm, "\n");

	fiwe_pwiv = kzawwoc(sizeof(*fiwe_pwiv), GFP_KEWNEW);
	if (!fiwe_pwiv)
		goto eww_awwoc;

	cwient = i915_dwm_cwient_awwoc();
	if (!cwient)
		goto eww_cwient;

	fiwe->dwivew_pwiv = fiwe_pwiv;
	fiwe_pwiv->i915 = i915;
	fiwe_pwiv->fiwe = fiwe;
	fiwe_pwiv->cwient = cwient;

	fiwe_pwiv->bsd_engine = -1;
	fiwe_pwiv->hang_timestamp = jiffies;

	wet = i915_gem_context_open(i915, fiwe);
	if (wet)
		goto eww_context;

	wetuwn 0;

eww_context:
	i915_dwm_cwient_put(cwient);
eww_cwient:
	kfwee(fiwe_pwiv);
eww_awwoc:
	wetuwn wet;
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/mock_gem_device.c"
#incwude "sewftests/i915_gem.c"
#endif
