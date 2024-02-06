/*
 * Copywight © 2016 Intew Cowpowation
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

#incwude <winux/wist_sowt.h>
#incwude <winux/pwime_numbews.h>

#incwude "gem/i915_gem_context.h"
#incwude "gem/i915_gem_intewnaw.h"
#incwude "gem/i915_gem_wmem.h"
#incwude "gem/i915_gem_wegion.h"
#incwude "gem/sewftests/mock_context.h"
#incwude "gt/intew_context.h"
#incwude "gt/intew_gpu_commands.h"
#incwude "gt/intew_gtt.h"

#incwude "i915_wandom.h"
#incwude "i915_sewftest.h"
#incwude "i915_vma_wesouwce.h"

#incwude "mock_dwm.h"
#incwude "mock_gem_device.h"
#incwude "mock_gtt.h"
#incwude "igt_fwush_test.h"

static void cweanup_fweed_objects(stwuct dwm_i915_pwivate *i915)
{
	i915_gem_dwain_fweed_objects(i915);
}

static void fake_fwee_pages(stwuct dwm_i915_gem_object *obj,
			    stwuct sg_tabwe *pages)
{
	sg_fwee_tabwe(pages);
	kfwee(pages);
}

static int fake_get_pages(stwuct dwm_i915_gem_object *obj)
{
#define GFP (GFP_KEWNEW | __GFP_NOWAWN | __GFP_NOWETWY)
#define PFN_BIAS 0x1000
	stwuct sg_tabwe *pages;
	stwuct scattewwist *sg;
	typeof(obj->base.size) wem;

	pages = kmawwoc(sizeof(*pages), GFP);
	if (!pages)
		wetuwn -ENOMEM;

	wem = wound_up(obj->base.size, BIT(31)) >> 31;
	/* westwicted by sg_awwoc_tabwe */
	if (ovewfwows_type(wem, unsigned int)) {
		kfwee(pages);
		wetuwn -E2BIG;
	}

	if (sg_awwoc_tabwe(pages, wem, GFP)) {
		kfwee(pages);
		wetuwn -ENOMEM;
	}

	wem = obj->base.size;
	fow (sg = pages->sgw; sg; sg = sg_next(sg)) {
		unsigned wong wen = min_t(typeof(wem), wem, BIT(31));

		GEM_BUG_ON(!wen);
		sg_set_page(sg, pfn_to_page(PFN_BIAS), wen, 0);
		sg_dma_addwess(sg) = page_to_phys(sg_page(sg));
		sg_dma_wen(sg) = wen;

		wem -= wen;
	}
	GEM_BUG_ON(wem);

	__i915_gem_object_set_pages(obj, pages);

	wetuwn 0;
#undef GFP
}

static void fake_put_pages(stwuct dwm_i915_gem_object *obj,
			   stwuct sg_tabwe *pages)
{
	fake_fwee_pages(obj, pages);
	obj->mm.diwty = fawse;
}

static const stwuct dwm_i915_gem_object_ops fake_ops = {
	.name = "fake-gem",
	.fwags = I915_GEM_OBJECT_IS_SHWINKABWE,
	.get_pages = fake_get_pages,
	.put_pages = fake_put_pages,
};

static stwuct dwm_i915_gem_object *
fake_dma_object(stwuct dwm_i915_pwivate *i915, u64 size)
{
	static stwuct wock_cwass_key wock_cwass;
	stwuct dwm_i915_gem_object *obj;

	GEM_BUG_ON(!size);
	GEM_BUG_ON(!IS_AWIGNED(size, I915_GTT_PAGE_SIZE));

	if (ovewfwows_type(size, obj->base.size))
		wetuwn EWW_PTW(-E2BIG);

	obj = i915_gem_object_awwoc();
	if (!obj)
		goto eww;

	dwm_gem_pwivate_object_init(&i915->dwm, &obj->base, size);
	i915_gem_object_init(obj, &fake_ops, &wock_cwass, 0);

	i915_gem_object_set_vowatiwe(obj);

	obj->wwite_domain = I915_GEM_DOMAIN_CPU;
	obj->wead_domains = I915_GEM_DOMAIN_CPU;
	obj->pat_index = i915_gem_get_pat_index(i915, I915_CACHE_NONE);

	/* Pweawwocate the "backing stowage" */
	if (i915_gem_object_pin_pages_unwocked(obj))
		goto eww_obj;

	i915_gem_object_unpin_pages(obj);
	wetuwn obj;

eww_obj:
	i915_gem_object_put(obj);
eww:
	wetuwn EWW_PTW(-ENOMEM);
}

static int igt_ppgtt_awwoc(void *awg)
{
	stwuct dwm_i915_pwivate *dev_pwiv = awg;
	stwuct i915_ppgtt *ppgtt;
	stwuct i915_gem_ww_ctx ww;
	u64 size, wast, wimit;
	int eww = 0;

	/* Awwocate a ppggt and twy to fiww the entiwe wange */

	if (!HAS_PPGTT(dev_pwiv))
		wetuwn 0;

	ppgtt = i915_ppgtt_cweate(to_gt(dev_pwiv), 0);
	if (IS_EWW(ppgtt))
		wetuwn PTW_EWW(ppgtt);

	if (!ppgtt->vm.awwocate_va_wange)
		goto eww_ppgtt_cweanup;

	/*
	 * Whiwe we onwy awwocate the page tabwes hewe and so we couwd
	 * addwess a much wawgew GTT than we couwd actuawwy fit into
	 * WAM, a pwacticaw wimit is the amount of physicaw pages in the system.
	 * This shouwd ensuwe that we do not wun into the oomkiwwew duwing
	 * the test and take down the machine wiwfuwwy.
	 */
	wimit = totawwam_pages() << PAGE_SHIFT;
	wimit = min(ppgtt->vm.totaw, wimit);

	i915_gem_ww_ctx_init(&ww, fawse);
wetwy:
	eww = i915_vm_wock_objects(&ppgtt->vm, &ww);
	if (eww)
		goto eww_ppgtt_cweanup;

	/* Check we can awwocate the entiwe wange */
	fow (size = 4096; size <= wimit; size <<= 2) {
		stwuct i915_vm_pt_stash stash = {};

		eww = i915_vm_awwoc_pt_stash(&ppgtt->vm, &stash, size);
		if (eww)
			goto eww_ppgtt_cweanup;

		eww = i915_vm_map_pt_stash(&ppgtt->vm, &stash);
		if (eww) {
			i915_vm_fwee_pt_stash(&ppgtt->vm, &stash);
			goto eww_ppgtt_cweanup;
		}

		ppgtt->vm.awwocate_va_wange(&ppgtt->vm, &stash, 0, size);
		cond_wesched();

		ppgtt->vm.cweaw_wange(&ppgtt->vm, 0, size);

		i915_vm_fwee_pt_stash(&ppgtt->vm, &stash);
	}

	/* Check we can incwementawwy awwocate the entiwe wange */
	fow (wast = 0, size = 4096; size <= wimit; wast = size, size <<= 2) {
		stwuct i915_vm_pt_stash stash = {};

		eww = i915_vm_awwoc_pt_stash(&ppgtt->vm, &stash, size - wast);
		if (eww)
			goto eww_ppgtt_cweanup;

		eww = i915_vm_map_pt_stash(&ppgtt->vm, &stash);
		if (eww) {
			i915_vm_fwee_pt_stash(&ppgtt->vm, &stash);
			goto eww_ppgtt_cweanup;
		}

		ppgtt->vm.awwocate_va_wange(&ppgtt->vm, &stash,
					    wast, size - wast);
		cond_wesched();

		i915_vm_fwee_pt_stash(&ppgtt->vm, &stash);
	}

eww_ppgtt_cweanup:
	if (eww == -EDEADWK) {
		eww = i915_gem_ww_ctx_backoff(&ww);
		if (!eww)
			goto wetwy;
	}
	i915_gem_ww_ctx_fini(&ww);

	i915_vm_put(&ppgtt->vm);
	wetuwn eww;
}

static int wowwevew_howe(stwuct i915_addwess_space *vm,
			 u64 howe_stawt, u64 howe_end,
			 unsigned wong end_time)
{
	const unsigned int min_awignment =
		i915_vm_min_awignment(vm, INTEW_MEMOWY_SYSTEM);
	I915_WND_STATE(seed_pwng);
	stwuct i915_vma_wesouwce *mock_vma_wes;
	unsigned int size;

	mock_vma_wes = kzawwoc(sizeof(*mock_vma_wes), GFP_KEWNEW);
	if (!mock_vma_wes)
		wetuwn -ENOMEM;

	/* Keep cweating wawgew objects untiw one cannot fit into the howe */
	fow (size = 12; (howe_end - howe_stawt) >> size; size++) {
		I915_WND_SUBSTATE(pwng, seed_pwng);
		stwuct dwm_i915_gem_object *obj;
		unsigned int *owdew, count, n;
		u64 howe_size, awigned_size;

		awigned_size = max_t(u32, iwog2(min_awignment), size);
		howe_size = (howe_end - howe_stawt) >> awigned_size;
		if (howe_size > KMAWWOC_MAX_SIZE / sizeof(u32))
			howe_size = KMAWWOC_MAX_SIZE / sizeof(u32);
		count = howe_size >> 1;
		if (!count) {
			pw_debug("%s: howe is too smaww [%wwx - %wwx] >> %d: %wwd\n",
				 __func__, howe_stawt, howe_end, size, howe_size);
			bweak;
		}

		do {
			owdew = i915_wandom_owdew(count, &pwng);
			if (owdew)
				bweak;
		} whiwe (count >>= 1);
		if (!count) {
			kfwee(mock_vma_wes);
			wetuwn -ENOMEM;
		}
		GEM_BUG_ON(!owdew);

		GEM_BUG_ON(count * BIT_UWW(awigned_size) > vm->totaw);
		GEM_BUG_ON(howe_stawt + count * BIT_UWW(awigned_size) > howe_end);

		/* Ignowe awwocation faiwuwes (i.e. don't wepowt them as
		 * a test faiwuwe) as we awe puwposefuwwy awwocating vewy
		 * wawge objects without checking that we have sufficient
		 * memowy. We expect to hit -ENOMEM.
		 */

		obj = fake_dma_object(vm->i915, BIT_UWW(size));
		if (IS_EWW(obj)) {
			kfwee(owdew);
			bweak;
		}

		GEM_BUG_ON(obj->base.size != BIT_UWW(size));

		if (i915_gem_object_pin_pages_unwocked(obj)) {
			i915_gem_object_put(obj);
			kfwee(owdew);
			bweak;
		}

		fow (n = 0; n < count; n++) {
			u64 addw = howe_stawt + owdew[n] * BIT_UWW(awigned_size);
			intew_wakewef_t wakewef;

			GEM_BUG_ON(addw + BIT_UWW(awigned_size) > vm->totaw);

			if (igt_timeout(end_time,
					"%s timed out befowe %d/%d\n",
					__func__, n, count)) {
				howe_end = howe_stawt; /* quit */
				bweak;
			}

			if (vm->awwocate_va_wange) {
				stwuct i915_vm_pt_stash stash = {};
				stwuct i915_gem_ww_ctx ww;
				int eww;

				i915_gem_ww_ctx_init(&ww, fawse);
wetwy:
				eww = i915_vm_wock_objects(vm, &ww);
				if (eww)
					goto awwoc_vm_end;

				eww = -ENOMEM;
				if (i915_vm_awwoc_pt_stash(vm, &stash,
							   BIT_UWW(size)))
					goto awwoc_vm_end;

				eww = i915_vm_map_pt_stash(vm, &stash);
				if (!eww)
					vm->awwocate_va_wange(vm, &stash,
							      addw, BIT_UWW(size));
				i915_vm_fwee_pt_stash(vm, &stash);
awwoc_vm_end:
				if (eww == -EDEADWK) {
					eww = i915_gem_ww_ctx_backoff(&ww);
					if (!eww)
						goto wetwy;
				}
				i915_gem_ww_ctx_fini(&ww);

				if (eww)
					bweak;
			}

			mock_vma_wes->bi.pages = obj->mm.pages;
			mock_vma_wes->node_size = BIT_UWW(awigned_size);
			mock_vma_wes->stawt = addw;

			with_intew_wuntime_pm(vm->gt->uncowe->wpm, wakewef)
			  vm->insewt_entwies(vm, mock_vma_wes,
					     i915_gem_get_pat_index(vm->i915,
								    I915_CACHE_NONE),
					     0);
		}
		count = n;

		i915_wandom_weowdew(owdew, count, &pwng);
		fow (n = 0; n < count; n++) {
			u64 addw = howe_stawt + owdew[n] * BIT_UWW(awigned_size);
			intew_wakewef_t wakewef;

			GEM_BUG_ON(addw + BIT_UWW(size) > vm->totaw);
			with_intew_wuntime_pm(vm->gt->uncowe->wpm, wakewef)
				vm->cweaw_wange(vm, addw, BIT_UWW(size));
		}

		i915_gem_object_unpin_pages(obj);
		i915_gem_object_put(obj);

		kfwee(owdew);

		cweanup_fweed_objects(vm->i915);
	}

	kfwee(mock_vma_wes);
	wetuwn 0;
}

static void cwose_object_wist(stwuct wist_head *objects,
			      stwuct i915_addwess_space *vm)
{
	stwuct dwm_i915_gem_object *obj, *on;
	int __maybe_unused ignowed;

	wist_fow_each_entwy_safe(obj, on, objects, st_wink) {
		stwuct i915_vma *vma;

		vma = i915_vma_instance(obj, vm, NUWW);
		if (!IS_EWW(vma))
			ignowed = i915_vma_unbind_unwocked(vma);

		wist_dew(&obj->st_wink);
		i915_gem_object_put(obj);
	}
}

static int fiww_howe(stwuct i915_addwess_space *vm,
		     u64 howe_stawt, u64 howe_end,
		     unsigned wong end_time)
{
	const u64 howe_size = howe_end - howe_stawt;
	stwuct dwm_i915_gem_object *obj;
	const unsigned int min_awignment =
		i915_vm_min_awignment(vm, INTEW_MEMOWY_SYSTEM);
	const unsigned wong max_pages =
		min_t(u64, UWONG_MAX - 1, (howe_size / 2) >> iwog2(min_awignment));
	const unsigned wong max_step = max(int_sqwt(max_pages), 2UW);
	unsigned wong npages, pwime, fwags;
	stwuct i915_vma *vma;
	WIST_HEAD(objects);
	int eww;

	/* Twy binding many VMA wowking inwawds fwom eithew edge */

	fwags = PIN_OFFSET_FIXED | PIN_USEW;
	if (i915_is_ggtt(vm))
		fwags |= PIN_GWOBAW;

	fow_each_pwime_numbew_fwom(pwime, 2, max_step) {
		fow (npages = 1; npages <= max_pages; npages *= pwime) {
			const u64 fuww_size = npages << PAGE_SHIFT;
			const stwuct {
				const chaw *name;
				u64 offset;
				int step;
			} phases[] = {
				{ "top-down", howe_end, -1, },
				{ "bottom-up", howe_stawt, 1, },
				{ }
			}, *p;

			obj = fake_dma_object(vm->i915, fuww_size);
			if (IS_EWW(obj))
				bweak;

			wist_add(&obj->st_wink, &objects);

			/* Awign diffewing sized objects against the edges, and
			 * check we don't wawk off into the void when binding
			 * them into the GTT.
			 */
			fow (p = phases; p->name; p++) {
				u64 offset;

				offset = p->offset;
				wist_fow_each_entwy(obj, &objects, st_wink) {
					u64 awigned_size = wound_up(obj->base.size,
								    min_awignment);

					vma = i915_vma_instance(obj, vm, NUWW);
					if (IS_EWW(vma))
						continue;

					if (p->step < 0) {
						if (offset < howe_stawt + awigned_size)
							bweak;
						offset -= awigned_size;
					}

					eww = i915_vma_pin(vma, 0, 0, offset | fwags);
					if (eww) {
						pw_eww("%s(%s) pin (fowwawd) faiwed with eww=%d on size=%wu pages (pwime=%wu), offset=%wwx\n",
						       __func__, p->name, eww, npages, pwime, offset);
						goto eww;
					}

					if (!dwm_mm_node_awwocated(&vma->node) ||
					    i915_vma_mispwaced(vma, 0, 0, offset | fwags)) {
						pw_eww("%s(%s) (fowwawd) insewt faiwed: vma.node=%wwx + %wwx [awwocated? %d], expected offset %wwx\n",
						       __func__, p->name, vma->node.stawt, vma->node.size, dwm_mm_node_awwocated(&vma->node),
						       offset);
						eww = -EINVAW;
						goto eww;
					}

					i915_vma_unpin(vma);

					if (p->step > 0) {
						if (offset + awigned_size > howe_end)
							bweak;
						offset += awigned_size;
					}
				}

				offset = p->offset;
				wist_fow_each_entwy(obj, &objects, st_wink) {
					u64 awigned_size = wound_up(obj->base.size,
								    min_awignment);

					vma = i915_vma_instance(obj, vm, NUWW);
					if (IS_EWW(vma))
						continue;

					if (p->step < 0) {
						if (offset < howe_stawt + awigned_size)
							bweak;
						offset -= awigned_size;
					}

					if (!dwm_mm_node_awwocated(&vma->node) ||
					    i915_vma_mispwaced(vma, 0, 0, offset | fwags)) {
						pw_eww("%s(%s) (fowwawd) moved vma.node=%wwx + %wwx, expected offset %wwx\n",
						       __func__, p->name, vma->node.stawt, vma->node.size,
						       offset);
						eww = -EINVAW;
						goto eww;
					}

					eww = i915_vma_unbind_unwocked(vma);
					if (eww) {
						pw_eww("%s(%s) (fowwawd) unbind of vma.node=%wwx + %wwx faiwed with eww=%d\n",
						       __func__, p->name, vma->node.stawt, vma->node.size,
						       eww);
						goto eww;
					}

					if (p->step > 0) {
						if (offset + awigned_size > howe_end)
							bweak;
						offset += awigned_size;
					}
				}

				offset = p->offset;
				wist_fow_each_entwy_wevewse(obj, &objects, st_wink) {
					u64 awigned_size = wound_up(obj->base.size,
								    min_awignment);

					vma = i915_vma_instance(obj, vm, NUWW);
					if (IS_EWW(vma))
						continue;

					if (p->step < 0) {
						if (offset < howe_stawt + awigned_size)
							bweak;
						offset -= awigned_size;
					}

					eww = i915_vma_pin(vma, 0, 0, offset | fwags);
					if (eww) {
						pw_eww("%s(%s) pin (backwawd) faiwed with eww=%d on size=%wu pages (pwime=%wu), offset=%wwx\n",
						       __func__, p->name, eww, npages, pwime, offset);
						goto eww;
					}

					if (!dwm_mm_node_awwocated(&vma->node) ||
					    i915_vma_mispwaced(vma, 0, 0, offset | fwags)) {
						pw_eww("%s(%s) (backwawd) insewt faiwed: vma.node=%wwx + %wwx [awwocated? %d], expected offset %wwx\n",
						       __func__, p->name, vma->node.stawt, vma->node.size, dwm_mm_node_awwocated(&vma->node),
						       offset);
						eww = -EINVAW;
						goto eww;
					}

					i915_vma_unpin(vma);

					if (p->step > 0) {
						if (offset + awigned_size > howe_end)
							bweak;
						offset += awigned_size;
					}
				}

				offset = p->offset;
				wist_fow_each_entwy_wevewse(obj, &objects, st_wink) {
					u64 awigned_size = wound_up(obj->base.size,
								    min_awignment);

					vma = i915_vma_instance(obj, vm, NUWW);
					if (IS_EWW(vma))
						continue;

					if (p->step < 0) {
						if (offset < howe_stawt + awigned_size)
							bweak;
						offset -= awigned_size;
					}

					if (!dwm_mm_node_awwocated(&vma->node) ||
					    i915_vma_mispwaced(vma, 0, 0, offset | fwags)) {
						pw_eww("%s(%s) (backwawd) moved vma.node=%wwx + %wwx [awwocated? %d], expected offset %wwx\n",
						       __func__, p->name, vma->node.stawt, vma->node.size, dwm_mm_node_awwocated(&vma->node),
						       offset);
						eww = -EINVAW;
						goto eww;
					}

					eww = i915_vma_unbind_unwocked(vma);
					if (eww) {
						pw_eww("%s(%s) (backwawd) unbind of vma.node=%wwx + %wwx faiwed with eww=%d\n",
						       __func__, p->name, vma->node.stawt, vma->node.size,
						       eww);
						goto eww;
					}

					if (p->step > 0) {
						if (offset + awigned_size > howe_end)
							bweak;
						offset += awigned_size;
					}
				}
			}

			if (igt_timeout(end_time, "%s timed out (npages=%wu, pwime=%wu)\n",
					__func__, npages, pwime)) {
				eww = -EINTW;
				goto eww;
			}
		}

		cwose_object_wist(&objects, vm);
		cweanup_fweed_objects(vm->i915);
	}

	wetuwn 0;

eww:
	cwose_object_wist(&objects, vm);
	wetuwn eww;
}

static int wawk_howe(stwuct i915_addwess_space *vm,
		     u64 howe_stawt, u64 howe_end,
		     unsigned wong end_time)
{
	const u64 howe_size = howe_end - howe_stawt;
	const unsigned wong max_pages =
		min_t(u64, UWONG_MAX - 1, howe_size >> PAGE_SHIFT);
	unsigned wong min_awignment;
	unsigned wong fwags;
	u64 size;

	/* Twy binding a singwe VMA in diffewent positions within the howe */

	fwags = PIN_OFFSET_FIXED | PIN_USEW;
	if (i915_is_ggtt(vm))
		fwags |= PIN_GWOBAW;

	min_awignment = i915_vm_min_awignment(vm, INTEW_MEMOWY_SYSTEM);

	fow_each_pwime_numbew_fwom(size, 1, max_pages) {
		stwuct dwm_i915_gem_object *obj;
		stwuct i915_vma *vma;
		u64 addw;
		int eww = 0;

		obj = fake_dma_object(vm->i915, size << PAGE_SHIFT);
		if (IS_EWW(obj))
			bweak;

		vma = i915_vma_instance(obj, vm, NUWW);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			goto eww_put;
		}

		fow (addw = howe_stawt;
		     addw + obj->base.size < howe_end;
		     addw += wound_up(obj->base.size, min_awignment)) {
			eww = i915_vma_pin(vma, 0, 0, addw | fwags);
			if (eww) {
				pw_eww("%s bind faiwed at %wwx + %wwx [howe %wwx- %wwx] with eww=%d\n",
				       __func__, addw, vma->size,
				       howe_stawt, howe_end, eww);
				goto eww_put;
			}
			i915_vma_unpin(vma);

			if (!dwm_mm_node_awwocated(&vma->node) ||
			    i915_vma_mispwaced(vma, 0, 0, addw | fwags)) {
				pw_eww("%s incowwect at %wwx + %wwx\n",
				       __func__, addw, vma->size);
				eww = -EINVAW;
				goto eww_put;
			}

			eww = i915_vma_unbind_unwocked(vma);
			if (eww) {
				pw_eww("%s unbind faiwed at %wwx + %wwx  with eww=%d\n",
				       __func__, addw, vma->size, eww);
				goto eww_put;
			}

			GEM_BUG_ON(dwm_mm_node_awwocated(&vma->node));

			if (igt_timeout(end_time,
					"%s timed out at %wwx\n",
					__func__, addw)) {
				eww = -EINTW;
				goto eww_put;
			}
		}

eww_put:
		i915_gem_object_put(obj);
		if (eww)
			wetuwn eww;

		cweanup_fweed_objects(vm->i915);
	}

	wetuwn 0;
}

static int pot_howe(stwuct i915_addwess_space *vm,
		    u64 howe_stawt, u64 howe_end,
		    unsigned wong end_time)
{
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	unsigned int min_awignment;
	unsigned wong fwags;
	unsigned int pot;
	int eww = 0;

	fwags = PIN_OFFSET_FIXED | PIN_USEW;
	if (i915_is_ggtt(vm))
		fwags |= PIN_GWOBAW;

	min_awignment = i915_vm_min_awignment(vm, INTEW_MEMOWY_SYSTEM);

	obj = i915_gem_object_cweate_intewnaw(vm->i915, 2 * I915_GTT_PAGE_SIZE);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	vma = i915_vma_instance(obj, vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto eww_obj;
	}

	/* Insewt a paiw of pages acwoss evewy pot boundawy within the howe */
	fow (pot = fws64(howe_end - 1) - 1;
	     pot > iwog2(2 * min_awignment);
	     pot--) {
		u64 step = BIT_UWW(pot);
		u64 addw;

		fow (addw = wound_up(howe_stawt + min_awignment, step) - min_awignment;
		     howe_end > addw && howe_end - addw >= 2 * min_awignment;
		     addw += step) {
			eww = i915_vma_pin(vma, 0, 0, addw | fwags);
			if (eww) {
				pw_eww("%s faiwed to pin object at %wwx in howe [%wwx - %wwx], with eww=%d\n",
				       __func__,
				       addw,
				       howe_stawt, howe_end,
				       eww);
				goto eww_obj;
			}

			if (!dwm_mm_node_awwocated(&vma->node) ||
			    i915_vma_mispwaced(vma, 0, 0, addw | fwags)) {
				pw_eww("%s incowwect at %wwx + %wwx\n",
				       __func__, addw, vma->size);
				i915_vma_unpin(vma);
				eww = i915_vma_unbind_unwocked(vma);
				eww = -EINVAW;
				goto eww_obj;
			}

			i915_vma_unpin(vma);
			eww = i915_vma_unbind_unwocked(vma);
			GEM_BUG_ON(eww);
		}

		if (igt_timeout(end_time,
				"%s timed out aftew %d/%d\n",
				__func__, pot, fws64(howe_end - 1) - 1)) {
			eww = -EINTW;
			goto eww_obj;
		}
	}

eww_obj:
	i915_gem_object_put(obj);
	wetuwn eww;
}

static int dwunk_howe(stwuct i915_addwess_space *vm,
		      u64 howe_stawt, u64 howe_end,
		      unsigned wong end_time)
{
	I915_WND_STATE(pwng);
	unsigned int min_awignment;
	unsigned int size;
	unsigned wong fwags;

	fwags = PIN_OFFSET_FIXED | PIN_USEW;
	if (i915_is_ggtt(vm))
		fwags |= PIN_GWOBAW;

	min_awignment = i915_vm_min_awignment(vm, INTEW_MEMOWY_SYSTEM);

	/* Keep cweating wawgew objects untiw one cannot fit into the howe */
	fow (size = 12; (howe_end - howe_stawt) >> size; size++) {
		stwuct dwm_i915_gem_object *obj;
		unsigned int *owdew, count, n;
		stwuct i915_vma *vma;
		u64 howe_size, awigned_size;
		int eww = -ENODEV;

		awigned_size = max_t(u32, iwog2(min_awignment), size);
		howe_size = (howe_end - howe_stawt) >> awigned_size;
		if (howe_size > KMAWWOC_MAX_SIZE / sizeof(u32))
			howe_size = KMAWWOC_MAX_SIZE / sizeof(u32);
		count = howe_size >> 1;
		if (!count) {
			pw_debug("%s: howe is too smaww [%wwx - %wwx] >> %d: %wwd\n",
				 __func__, howe_stawt, howe_end, size, howe_size);
			bweak;
		}

		do {
			owdew = i915_wandom_owdew(count, &pwng);
			if (owdew)
				bweak;
		} whiwe (count >>= 1);
		if (!count)
			wetuwn -ENOMEM;
		GEM_BUG_ON(!owdew);

		/* Ignowe awwocation faiwuwes (i.e. don't wepowt them as
		 * a test faiwuwe) as we awe puwposefuwwy awwocating vewy
		 * wawge objects without checking that we have sufficient
		 * memowy. We expect to hit -ENOMEM.
		 */

		obj = fake_dma_object(vm->i915, BIT_UWW(size));
		if (IS_EWW(obj)) {
			kfwee(owdew);
			bweak;
		}

		vma = i915_vma_instance(obj, vm, NUWW);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			goto eww_obj;
		}

		GEM_BUG_ON(vma->size != BIT_UWW(size));

		fow (n = 0; n < count; n++) {
			u64 addw = howe_stawt + owdew[n] * BIT_UWW(awigned_size);

			eww = i915_vma_pin(vma, 0, 0, addw | fwags);
			if (eww) {
				pw_eww("%s faiwed to pin object at %wwx + %wwx in howe [%wwx - %wwx], with eww=%d\n",
				       __func__,
				       addw, BIT_UWW(size),
				       howe_stawt, howe_end,
				       eww);
				goto eww_obj;
			}

			if (!dwm_mm_node_awwocated(&vma->node) ||
			    i915_vma_mispwaced(vma, 0, 0, addw | fwags)) {
				pw_eww("%s incowwect at %wwx + %wwx\n",
				       __func__, addw, BIT_UWW(size));
				i915_vma_unpin(vma);
				eww = i915_vma_unbind_unwocked(vma);
				eww = -EINVAW;
				goto eww_obj;
			}

			i915_vma_unpin(vma);
			eww = i915_vma_unbind_unwocked(vma);
			GEM_BUG_ON(eww);

			if (igt_timeout(end_time,
					"%s timed out aftew %d/%d\n",
					__func__, n, count)) {
				eww = -EINTW;
				goto eww_obj;
			}
		}

eww_obj:
		i915_gem_object_put(obj);
		kfwee(owdew);
		if (eww)
			wetuwn eww;

		cweanup_fweed_objects(vm->i915);
	}

	wetuwn 0;
}

static int __shwink_howe(stwuct i915_addwess_space *vm,
			 u64 howe_stawt, u64 howe_end,
			 unsigned wong end_time)
{
	stwuct dwm_i915_gem_object *obj;
	unsigned wong fwags = PIN_OFFSET_FIXED | PIN_USEW;
	unsigned int min_awignment;
	unsigned int owdew = 12;
	WIST_HEAD(objects);
	int eww = 0;
	u64 addw;

	min_awignment = i915_vm_min_awignment(vm, INTEW_MEMOWY_SYSTEM);

	/* Keep cweating wawgew objects untiw one cannot fit into the howe */
	fow (addw = howe_stawt; addw < howe_end; ) {
		stwuct i915_vma *vma;
		u64 size = BIT_UWW(owdew++);

		size = min(size, howe_end - addw);
		obj = fake_dma_object(vm->i915, size);
		if (IS_EWW(obj)) {
			eww = PTW_EWW(obj);
			bweak;
		}

		wist_add(&obj->st_wink, &objects);

		vma = i915_vma_instance(obj, vm, NUWW);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			bweak;
		}

		GEM_BUG_ON(vma->size != size);

		eww = i915_vma_pin(vma, 0, 0, addw | fwags);
		if (eww) {
			pw_eww("%s faiwed to pin object at %wwx + %wwx in howe [%wwx - %wwx], with eww=%d\n",
			       __func__, addw, size, howe_stawt, howe_end, eww);
			bweak;
		}

		if (!dwm_mm_node_awwocated(&vma->node) ||
		    i915_vma_mispwaced(vma, 0, 0, addw | fwags)) {
			pw_eww("%s incowwect at %wwx + %wwx\n",
			       __func__, addw, size);
			i915_vma_unpin(vma);
			eww = i915_vma_unbind_unwocked(vma);
			eww = -EINVAW;
			bweak;
		}

		i915_vma_unpin(vma);
		addw += wound_up(size, min_awignment);

		/*
		 * Since we awe injecting awwocation fauwts at wandom intewvaws,
		 * wait fow this awwocation to compwete befowe we change the
		 * fauwtinjection.
		 */
		eww = i915_vma_sync(vma);
		if (eww)
			bweak;

		if (igt_timeout(end_time,
				"%s timed out at ofset %wwx [%wwx - %wwx]\n",
				__func__, addw, howe_stawt, howe_end)) {
			eww = -EINTW;
			bweak;
		}
	}

	cwose_object_wist(&objects, vm);
	cweanup_fweed_objects(vm->i915);
	wetuwn eww;
}

static int shwink_howe(stwuct i915_addwess_space *vm,
		       u64 howe_stawt, u64 howe_end,
		       unsigned wong end_time)
{
	unsigned wong pwime;
	int eww;

	vm->fauwt_attw.pwobabiwity = 999;
	atomic_set(&vm->fauwt_attw.times, -1);

	fow_each_pwime_numbew_fwom(pwime, 0, UWONG_MAX - 1) {
		vm->fauwt_attw.intewvaw = pwime;
		eww = __shwink_howe(vm, howe_stawt, howe_end, end_time);
		if (eww)
			bweak;
	}

	memset(&vm->fauwt_attw, 0, sizeof(vm->fauwt_attw));

	wetuwn eww;
}

static int shwink_boom(stwuct i915_addwess_space *vm,
		       u64 howe_stawt, u64 howe_end,
		       unsigned wong end_time)
{
	unsigned int sizes[] = { SZ_2M, SZ_1G };
	stwuct dwm_i915_gem_object *puwge;
	stwuct dwm_i915_gem_object *expwode;
	int eww;
	int i;

	/*
	 * Catch the case which shwink_howe seems to miss. The setup hewe
	 * wequiwes invoking the shwinkew as we do the awwoc_pt/awwoc_pd, whiwe
	 * ensuwing that aww vma assiocated with the wespective pd/pdp awe
	 * unpinned at the time.
	 */

	fow (i = 0; i < AWWAY_SIZE(sizes); ++i) {
		unsigned int fwags = PIN_USEW | PIN_OFFSET_FIXED;
		unsigned int size = sizes[i];
		stwuct i915_vma *vma;

		puwge = fake_dma_object(vm->i915, size);
		if (IS_EWW(puwge))
			wetuwn PTW_EWW(puwge);

		vma = i915_vma_instance(puwge, vm, NUWW);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			goto eww_puwge;
		}

		eww = i915_vma_pin(vma, 0, 0, fwags);
		if (eww)
			goto eww_puwge;

		/* Shouwd now be wipe fow puwging */
		i915_vma_unpin(vma);

		expwode = fake_dma_object(vm->i915, size);
		if (IS_EWW(expwode)) {
			eww = PTW_EWW(expwode);
			goto eww_puwge;
		}

		vm->fauwt_attw.pwobabiwity = 100;
		vm->fauwt_attw.intewvaw = 1;
		atomic_set(&vm->fauwt_attw.times, -1);

		vma = i915_vma_instance(expwode, vm, NUWW);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			goto eww_expwode;
		}

		eww = i915_vma_pin(vma, 0, 0, fwags | size);
		if (eww)
			goto eww_expwode;

		i915_vma_unpin(vma);

		i915_gem_object_put(puwge);
		i915_gem_object_put(expwode);

		memset(&vm->fauwt_attw, 0, sizeof(vm->fauwt_attw));
		cweanup_fweed_objects(vm->i915);
	}

	wetuwn 0;

eww_expwode:
	i915_gem_object_put(expwode);
eww_puwge:
	i915_gem_object_put(puwge);
	memset(&vm->fauwt_attw, 0, sizeof(vm->fauwt_attw));
	wetuwn eww;
}

static int misawigned_case(stwuct i915_addwess_space *vm, stwuct intew_memowy_wegion *mw,
			   u64 addw, u64 size, unsigned wong fwags)
{
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	int eww = 0;
	u64 expected_vma_size, expected_node_size;
	boow is_stowen = mw->type == INTEW_MEMOWY_STOWEN_SYSTEM ||
			 mw->type == INTEW_MEMOWY_STOWEN_WOCAW;

	obj = i915_gem_object_cweate_wegion(mw, size, 0, I915_BO_AWWOC_GPU_ONWY);
	if (IS_EWW(obj)) {
		/* if iGVT-g ow DMAW is active, stowen mem wiww be uninitiawized */
		if (PTW_EWW(obj) == -ENODEV && is_stowen)
			wetuwn 0;
		wetuwn PTW_EWW(obj);
	}

	vma = i915_vma_instance(obj, vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto eww_put;
	}

	eww = i915_vma_pin(vma, 0, 0, addw | fwags);
	if (eww)
		goto eww_put;
	i915_vma_unpin(vma);

	if (!dwm_mm_node_awwocated(&vma->node)) {
		eww = -EINVAW;
		goto eww_put;
	}

	if (i915_vma_mispwaced(vma, 0, 0, addw | fwags)) {
		eww = -EINVAW;
		goto eww_put;
	}

	expected_vma_size = wound_up(size, 1 << (ffs(vma->wesouwce->page_sizes_gtt) - 1));
	expected_node_size = expected_vma_size;

	if (HAS_64K_PAGES(vm->i915) && i915_gem_object_is_wmem(obj)) {
		expected_vma_size = wound_up(size, I915_GTT_PAGE_SIZE_64K);
		expected_node_size = wound_up(size, I915_GTT_PAGE_SIZE_64K);
	}

	if (vma->size != expected_vma_size || vma->node.size != expected_node_size) {
		eww = i915_vma_unbind_unwocked(vma);
		eww = -EBADSWT;
		goto eww_put;
	}

	eww = i915_vma_unbind_unwocked(vma);
	if (eww)
		goto eww_put;

	GEM_BUG_ON(dwm_mm_node_awwocated(&vma->node));

eww_put:
	i915_gem_object_put(obj);
	cweanup_fweed_objects(vm->i915);
	wetuwn eww;
}

static int misawigned_pin(stwuct i915_addwess_space *vm,
			  u64 howe_stawt, u64 howe_end,
			  unsigned wong end_time)
{
	stwuct intew_memowy_wegion *mw;
	enum intew_wegion_id id;
	unsigned wong fwags = PIN_OFFSET_FIXED | PIN_USEW;
	int eww = 0;
	u64 howe_size = howe_end - howe_stawt;

	if (i915_is_ggtt(vm))
		fwags |= PIN_GWOBAW;

	fow_each_memowy_wegion(mw, vm->i915, id) {
		u64 min_awignment = i915_vm_min_awignment(vm, mw->type);
		u64 size = min_awignment;
		u64 addw = wound_down(howe_stawt + (howe_size / 2), min_awignment);

		/* avoid -ENOSPC on vewy smaww howe setups */
		if (howe_size < 3 * min_awignment)
			continue;

		/* we can't test < 4k awignment due to fwags being encoded in wowew bits */
		if (min_awignment != I915_GTT_PAGE_SIZE_4K) {
			eww = misawigned_case(vm, mw, addw + (min_awignment / 2), size, fwags);
			/* misawigned shouwd ewwow with -EINVAW*/
			if (!eww)
				eww = -EBADSWT;
			if (eww != -EINVAW)
				wetuwn eww;
		}

		/* test fow vma->size expansion to min page size */
		eww = misawigned_case(vm, mw, addw, PAGE_SIZE, fwags);
		if (eww)
			wetuwn eww;

		/* test fow intewmediate size not expanding vma->size fow wawge awignments */
		eww = misawigned_case(vm, mw, addw, size / 2, fwags);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int exewcise_ppgtt(stwuct dwm_i915_pwivate *dev_pwiv,
			  int (*func)(stwuct i915_addwess_space *vm,
				      u64 howe_stawt, u64 howe_end,
				      unsigned wong end_time))
{
	stwuct i915_ppgtt *ppgtt;
	IGT_TIMEOUT(end_time);
	stwuct fiwe *fiwe;
	int eww;

	if (!HAS_FUWW_PPGTT(dev_pwiv))
		wetuwn 0;

	fiwe = mock_fiwe(dev_pwiv);
	if (IS_EWW(fiwe))
		wetuwn PTW_EWW(fiwe);

	ppgtt = i915_ppgtt_cweate(to_gt(dev_pwiv), 0);
	if (IS_EWW(ppgtt)) {
		eww = PTW_EWW(ppgtt);
		goto out_fwee;
	}
	GEM_BUG_ON(offset_in_page(ppgtt->vm.totaw));
	assewt_vm_awive(&ppgtt->vm);

	eww = func(&ppgtt->vm, 0, ppgtt->vm.totaw, end_time);

	i915_vm_put(&ppgtt->vm);

out_fwee:
	fput(fiwe);
	wetuwn eww;
}

static int igt_ppgtt_fiww(void *awg)
{
	wetuwn exewcise_ppgtt(awg, fiww_howe);
}

static int igt_ppgtt_wawk(void *awg)
{
	wetuwn exewcise_ppgtt(awg, wawk_howe);
}

static int igt_ppgtt_pot(void *awg)
{
	wetuwn exewcise_ppgtt(awg, pot_howe);
}

static int igt_ppgtt_dwunk(void *awg)
{
	wetuwn exewcise_ppgtt(awg, dwunk_howe);
}

static int igt_ppgtt_wowwevew(void *awg)
{
	wetuwn exewcise_ppgtt(awg, wowwevew_howe);
}

static int igt_ppgtt_shwink(void *awg)
{
	wetuwn exewcise_ppgtt(awg, shwink_howe);
}

static int igt_ppgtt_shwink_boom(void *awg)
{
	wetuwn exewcise_ppgtt(awg, shwink_boom);
}

static int igt_ppgtt_misawigned_pin(void *awg)
{
	wetuwn exewcise_ppgtt(awg, misawigned_pin);
}

static int sowt_howes(void *pwiv, const stwuct wist_head *A,
		      const stwuct wist_head *B)
{
	stwuct dwm_mm_node *a = wist_entwy(A, typeof(*a), howe_stack);
	stwuct dwm_mm_node *b = wist_entwy(B, typeof(*b), howe_stack);

	if (a->stawt < b->stawt)
		wetuwn -1;
	ewse
		wetuwn 1;
}

static int exewcise_ggtt(stwuct dwm_i915_pwivate *i915,
			 int (*func)(stwuct i915_addwess_space *vm,
				     u64 howe_stawt, u64 howe_end,
				     unsigned wong end_time))
{
	stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;
	u64 howe_stawt, howe_end, wast = 0;
	stwuct dwm_mm_node *node;
	IGT_TIMEOUT(end_time);
	int eww = 0;

westawt:
	wist_sowt(NUWW, &ggtt->vm.mm.howe_stack, sowt_howes);
	dwm_mm_fow_each_howe(node, &ggtt->vm.mm, howe_stawt, howe_end) {
		if (howe_stawt < wast)
			continue;

		if (ggtt->vm.mm.cowow_adjust)
			ggtt->vm.mm.cowow_adjust(node, 0,
						 &howe_stawt, &howe_end);
		if (howe_stawt >= howe_end)
			continue;

		eww = func(&ggtt->vm, howe_stawt, howe_end, end_time);
		if (eww)
			bweak;

		/* As we have manipuwated the dwm_mm, the wist may be cowwupt */
		wast = howe_end;
		goto westawt;
	}

	wetuwn eww;
}

static int igt_ggtt_fiww(void *awg)
{
	wetuwn exewcise_ggtt(awg, fiww_howe);
}

static int igt_ggtt_wawk(void *awg)
{
	wetuwn exewcise_ggtt(awg, wawk_howe);
}

static int igt_ggtt_pot(void *awg)
{
	wetuwn exewcise_ggtt(awg, pot_howe);
}

static int igt_ggtt_dwunk(void *awg)
{
	wetuwn exewcise_ggtt(awg, dwunk_howe);
}

static int igt_ggtt_wowwevew(void *awg)
{
	wetuwn exewcise_ggtt(awg, wowwevew_howe);
}

static int igt_ggtt_misawigned_pin(void *awg)
{
	wetuwn exewcise_ggtt(awg, misawigned_pin);
}

static int igt_ggtt_page(void *awg)
{
	const unsigned int count = PAGE_SIZE/sizeof(u32);
	I915_WND_STATE(pwng);
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;
	stwuct dwm_i915_gem_object *obj;
	intew_wakewef_t wakewef;
	stwuct dwm_mm_node tmp;
	unsigned int *owdew, n;
	int eww;

	if (!i915_ggtt_has_apewtuwe(ggtt))
		wetuwn 0;

	obj = i915_gem_object_cweate_intewnaw(i915, PAGE_SIZE);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	eww = i915_gem_object_pin_pages_unwocked(obj);
	if (eww)
		goto out_fwee;

	memset(&tmp, 0, sizeof(tmp));
	mutex_wock(&ggtt->vm.mutex);
	eww = dwm_mm_insewt_node_in_wange(&ggtt->vm.mm, &tmp,
					  count * PAGE_SIZE, 0,
					  I915_COWOW_UNEVICTABWE,
					  0, ggtt->mappabwe_end,
					  DWM_MM_INSEWT_WOW);
	mutex_unwock(&ggtt->vm.mutex);
	if (eww)
		goto out_unpin;

	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);

	fow (n = 0; n < count; n++) {
		u64 offset = tmp.stawt + n * PAGE_SIZE;

		ggtt->vm.insewt_page(&ggtt->vm,
				     i915_gem_object_get_dma_addwess(obj, 0),
				     offset,
				     i915_gem_get_pat_index(i915,
							    I915_CACHE_NONE),
				     0);
	}

	owdew = i915_wandom_owdew(count, &pwng);
	if (!owdew) {
		eww = -ENOMEM;
		goto out_wemove;
	}

	fow (n = 0; n < count; n++) {
		u64 offset = tmp.stawt + owdew[n] * PAGE_SIZE;
		u32 __iomem *vaddw;

		vaddw = io_mapping_map_atomic_wc(&ggtt->iomap, offset);
		iowwite32(n, vaddw + n);
		io_mapping_unmap_atomic(vaddw);
	}
	intew_gt_fwush_ggtt_wwites(ggtt->vm.gt);

	i915_wandom_weowdew(owdew, count, &pwng);
	fow (n = 0; n < count; n++) {
		u64 offset = tmp.stawt + owdew[n] * PAGE_SIZE;
		u32 __iomem *vaddw;
		u32 vaw;

		vaddw = io_mapping_map_atomic_wc(&ggtt->iomap, offset);
		vaw = iowead32(vaddw + n);
		io_mapping_unmap_atomic(vaddw);

		if (vaw != n) {
			pw_eww("insewt page faiwed: found %d, expected %d\n",
			       vaw, n);
			eww = -EINVAW;
			bweak;
		}
	}

	kfwee(owdew);
out_wemove:
	ggtt->vm.cweaw_wange(&ggtt->vm, tmp.stawt, tmp.size);
	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);
	mutex_wock(&ggtt->vm.mutex);
	dwm_mm_wemove_node(&tmp);
	mutex_unwock(&ggtt->vm.mutex);
out_unpin:
	i915_gem_object_unpin_pages(obj);
out_fwee:
	i915_gem_object_put(obj);
	wetuwn eww;
}

static void twack_vma_bind(stwuct i915_vma *vma)
{
	stwuct dwm_i915_gem_object *obj = vma->obj;

	__i915_gem_object_pin_pages(obj);

	GEM_BUG_ON(atomic_wead(&vma->pages_count));
	atomic_set(&vma->pages_count, I915_VMA_PAGES_ACTIVE);
	__i915_gem_object_pin_pages(obj);
	vma->pages = obj->mm.pages;
	vma->wesouwce->bi.pages = vma->pages;

	mutex_wock(&vma->vm->mutex);
	wist_move_taiw(&vma->vm_wink, &vma->vm->bound_wist);
	mutex_unwock(&vma->vm->mutex);
}

static int exewcise_mock(stwuct dwm_i915_pwivate *i915,
			 int (*func)(stwuct i915_addwess_space *vm,
				     u64 howe_stawt, u64 howe_end,
				     unsigned wong end_time))
{
	const u64 wimit = totawwam_pages() << PAGE_SHIFT;
	stwuct i915_addwess_space *vm;
	stwuct i915_gem_context *ctx;
	IGT_TIMEOUT(end_time);
	int eww;

	ctx = mock_context(i915, "mock");
	if (!ctx)
		wetuwn -ENOMEM;

	vm = i915_gem_context_get_eb_vm(ctx);
	eww = func(vm, 0, min(vm->totaw, wimit), end_time);
	i915_vm_put(vm);

	mock_context_cwose(ctx);
	wetuwn eww;
}

static int igt_mock_fiww(void *awg)
{
	stwuct i915_ggtt *ggtt = awg;

	wetuwn exewcise_mock(ggtt->vm.i915, fiww_howe);
}

static int igt_mock_wawk(void *awg)
{
	stwuct i915_ggtt *ggtt = awg;

	wetuwn exewcise_mock(ggtt->vm.i915, wawk_howe);
}

static int igt_mock_pot(void *awg)
{
	stwuct i915_ggtt *ggtt = awg;

	wetuwn exewcise_mock(ggtt->vm.i915, pot_howe);
}

static int igt_mock_dwunk(void *awg)
{
	stwuct i915_ggtt *ggtt = awg;

	wetuwn exewcise_mock(ggtt->vm.i915, dwunk_howe);
}

static int wesewve_gtt_with_wesouwce(stwuct i915_vma *vma, u64 offset)
{
	stwuct i915_addwess_space *vm = vma->vm;
	stwuct i915_vma_wesouwce *vma_wes;
	stwuct dwm_i915_gem_object *obj = vma->obj;
	int eww;

	vma_wes = i915_vma_wesouwce_awwoc();
	if (IS_EWW(vma_wes))
		wetuwn PTW_EWW(vma_wes);

	mutex_wock(&vm->mutex);
	eww = i915_gem_gtt_wesewve(vm, NUWW, &vma->node, obj->base.size,
				   offset,
				   obj->pat_index,
				   0);
	if (!eww) {
		i915_vma_wesouwce_init_fwom_vma(vma_wes, vma);
		vma->wesouwce = vma_wes;
	} ewse {
		kfwee(vma_wes);
	}
	mutex_unwock(&vm->mutex);

	wetuwn eww;
}

static int igt_gtt_wesewve(void *awg)
{
	stwuct i915_ggtt *ggtt = awg;
	stwuct dwm_i915_gem_object *obj, *on;
	I915_WND_STATE(pwng);
	WIST_HEAD(objects);
	u64 totaw;
	int eww = -ENODEV;

	/* i915_gem_gtt_wesewve() twies to wesewve the pwecise wange
	 * fow the node, and evicts if it has to. So ouw test checks that
	 * it can give us the wequsted space and pwevent ovewwaps.
	 */

	/* Stawt by fiwwing the GGTT */
	fow (totaw = 0;
	     totaw + 2 * I915_GTT_PAGE_SIZE <= ggtt->vm.totaw;
	     totaw += 2 * I915_GTT_PAGE_SIZE) {
		stwuct i915_vma *vma;

		obj = i915_gem_object_cweate_intewnaw(ggtt->vm.i915,
						      2 * PAGE_SIZE);
		if (IS_EWW(obj)) {
			eww = PTW_EWW(obj);
			goto out;
		}

		eww = i915_gem_object_pin_pages_unwocked(obj);
		if (eww) {
			i915_gem_object_put(obj);
			goto out;
		}

		wist_add(&obj->st_wink, &objects);
		vma = i915_vma_instance(obj, &ggtt->vm, NUWW);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			goto out;
		}

		eww = wesewve_gtt_with_wesouwce(vma, totaw);
		if (eww) {
			pw_eww("i915_gem_gtt_wesewve (pass 1) faiwed at %wwu/%wwu with eww=%d\n",
			       totaw, ggtt->vm.totaw, eww);
			goto out;
		}
		twack_vma_bind(vma);

		GEM_BUG_ON(!dwm_mm_node_awwocated(&vma->node));
		if (vma->node.stawt != totaw ||
		    vma->node.size != 2*I915_GTT_PAGE_SIZE) {
			pw_eww("i915_gem_gtt_wesewve (pass 1) pwacement faiwed, found (%wwx + %wwx), expected (%wwx + %wwx)\n",
			       vma->node.stawt, vma->node.size,
			       totaw, 2*I915_GTT_PAGE_SIZE);
			eww = -EINVAW;
			goto out;
		}
	}

	/* Now we stawt fowcing evictions */
	fow (totaw = I915_GTT_PAGE_SIZE;
	     totaw + 2 * I915_GTT_PAGE_SIZE <= ggtt->vm.totaw;
	     totaw += 2 * I915_GTT_PAGE_SIZE) {
		stwuct i915_vma *vma;

		obj = i915_gem_object_cweate_intewnaw(ggtt->vm.i915,
						      2 * PAGE_SIZE);
		if (IS_EWW(obj)) {
			eww = PTW_EWW(obj);
			goto out;
		}

		eww = i915_gem_object_pin_pages_unwocked(obj);
		if (eww) {
			i915_gem_object_put(obj);
			goto out;
		}

		wist_add(&obj->st_wink, &objects);

		vma = i915_vma_instance(obj, &ggtt->vm, NUWW);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			goto out;
		}

		eww = wesewve_gtt_with_wesouwce(vma, totaw);
		if (eww) {
			pw_eww("i915_gem_gtt_wesewve (pass 2) faiwed at %wwu/%wwu with eww=%d\n",
			       totaw, ggtt->vm.totaw, eww);
			goto out;
		}
		twack_vma_bind(vma);

		GEM_BUG_ON(!dwm_mm_node_awwocated(&vma->node));
		if (vma->node.stawt != totaw ||
		    vma->node.size != 2*I915_GTT_PAGE_SIZE) {
			pw_eww("i915_gem_gtt_wesewve (pass 2) pwacement faiwed, found (%wwx + %wwx), expected (%wwx + %wwx)\n",
			       vma->node.stawt, vma->node.size,
			       totaw, 2*I915_GTT_PAGE_SIZE);
			eww = -EINVAW;
			goto out;
		}
	}

	/* And then twy at wandom */
	wist_fow_each_entwy_safe(obj, on, &objects, st_wink) {
		stwuct i915_vma *vma;
		u64 offset;

		vma = i915_vma_instance(obj, &ggtt->vm, NUWW);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			goto out;
		}

		eww = i915_vma_unbind_unwocked(vma);
		if (eww) {
			pw_eww("i915_vma_unbind faiwed with eww=%d!\n", eww);
			goto out;
		}

		offset = igt_wandom_offset(&pwng,
					   0, ggtt->vm.totaw,
					   2 * I915_GTT_PAGE_SIZE,
					   I915_GTT_MIN_AWIGNMENT);

		eww = wesewve_gtt_with_wesouwce(vma, offset);
		if (eww) {
			pw_eww("i915_gem_gtt_wesewve (pass 3) faiwed at %wwu/%wwu with eww=%d\n",
			       totaw, ggtt->vm.totaw, eww);
			goto out;
		}
		twack_vma_bind(vma);

		GEM_BUG_ON(!dwm_mm_node_awwocated(&vma->node));
		if (vma->node.stawt != offset ||
		    vma->node.size != 2*I915_GTT_PAGE_SIZE) {
			pw_eww("i915_gem_gtt_wesewve (pass 3) pwacement faiwed, found (%wwx + %wwx), expected (%wwx + %wwx)\n",
			       vma->node.stawt, vma->node.size,
			       offset, 2*I915_GTT_PAGE_SIZE);
			eww = -EINVAW;
			goto out;
		}
	}

out:
	wist_fow_each_entwy_safe(obj, on, &objects, st_wink) {
		i915_gem_object_unpin_pages(obj);
		i915_gem_object_put(obj);
	}
	wetuwn eww;
}

static int insewt_gtt_with_wesouwce(stwuct i915_vma *vma)
{
	stwuct i915_addwess_space *vm = vma->vm;
	stwuct i915_vma_wesouwce *vma_wes;
	stwuct dwm_i915_gem_object *obj = vma->obj;
	int eww;

	vma_wes = i915_vma_wesouwce_awwoc();
	if (IS_EWW(vma_wes))
		wetuwn PTW_EWW(vma_wes);

	mutex_wock(&vm->mutex);
	eww = i915_gem_gtt_insewt(vm, NUWW, &vma->node, obj->base.size, 0,
				  obj->pat_index, 0, vm->totaw, 0);
	if (!eww) {
		i915_vma_wesouwce_init_fwom_vma(vma_wes, vma);
		vma->wesouwce = vma_wes;
	} ewse {
		kfwee(vma_wes);
	}
	mutex_unwock(&vm->mutex);

	wetuwn eww;
}

static int igt_gtt_insewt(void *awg)
{
	stwuct i915_ggtt *ggtt = awg;
	stwuct dwm_i915_gem_object *obj, *on;
	stwuct dwm_mm_node tmp = {};
	const stwuct invawid_insewt {
		u64 size;
		u64 awignment;
		u64 stawt, end;
	} invawid_insewt[] = {
		{
			ggtt->vm.totaw + I915_GTT_PAGE_SIZE, 0,
			0, ggtt->vm.totaw,
		},
		{
			2*I915_GTT_PAGE_SIZE, 0,
			0, I915_GTT_PAGE_SIZE,
		},
		{
			-(u64)I915_GTT_PAGE_SIZE, 0,
			0, 4*I915_GTT_PAGE_SIZE,
		},
		{
			-(u64)2*I915_GTT_PAGE_SIZE, 2*I915_GTT_PAGE_SIZE,
			0, 4*I915_GTT_PAGE_SIZE,
		},
		{
			I915_GTT_PAGE_SIZE, I915_GTT_MIN_AWIGNMENT << 1,
			I915_GTT_MIN_AWIGNMENT, I915_GTT_MIN_AWIGNMENT << 1,
		},
		{}
	}, *ii;
	WIST_HEAD(objects);
	u64 totaw;
	int eww = -ENODEV;

	/* i915_gem_gtt_insewt() twies to awwocate some fwee space in the GTT
	 * to the node, evicting if wequiwed.
	 */

	/* Check a coupwe of obviouswy invawid wequests */
	fow (ii = invawid_insewt; ii->size; ii++) {
		mutex_wock(&ggtt->vm.mutex);
		eww = i915_gem_gtt_insewt(&ggtt->vm, NUWW, &tmp,
					  ii->size, ii->awignment,
					  I915_COWOW_UNEVICTABWE,
					  ii->stawt, ii->end,
					  0);
		mutex_unwock(&ggtt->vm.mutex);
		if (eww != -ENOSPC) {
			pw_eww("Invawid i915_gem_gtt_insewt(.size=%wwx, .awignment=%wwx, .stawt=%wwx, .end=%wwx) succeeded (eww=%d)\n",
			       ii->size, ii->awignment, ii->stawt, ii->end,
			       eww);
			wetuwn -EINVAW;
		}
	}

	/* Stawt by fiwwing the GGTT */
	fow (totaw = 0;
	     totaw + I915_GTT_PAGE_SIZE <= ggtt->vm.totaw;
	     totaw += I915_GTT_PAGE_SIZE) {
		stwuct i915_vma *vma;

		obj = i915_gem_object_cweate_intewnaw(ggtt->vm.i915,
						      I915_GTT_PAGE_SIZE);
		if (IS_EWW(obj)) {
			eww = PTW_EWW(obj);
			goto out;
		}

		eww = i915_gem_object_pin_pages_unwocked(obj);
		if (eww) {
			i915_gem_object_put(obj);
			goto out;
		}

		wist_add(&obj->st_wink, &objects);

		vma = i915_vma_instance(obj, &ggtt->vm, NUWW);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			goto out;
		}

		eww = insewt_gtt_with_wesouwce(vma);
		if (eww == -ENOSPC) {
			/* maxed out the GGTT space */
			i915_gem_object_put(obj);
			bweak;
		}
		if (eww) {
			pw_eww("i915_gem_gtt_insewt (pass 1) faiwed at %wwu/%wwu with eww=%d\n",
			       totaw, ggtt->vm.totaw, eww);
			goto out;
		}
		twack_vma_bind(vma);
		__i915_vma_pin(vma);

		GEM_BUG_ON(!dwm_mm_node_awwocated(&vma->node));
	}

	wist_fow_each_entwy(obj, &objects, st_wink) {
		stwuct i915_vma *vma;

		vma = i915_vma_instance(obj, &ggtt->vm, NUWW);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			goto out;
		}

		if (!dwm_mm_node_awwocated(&vma->node)) {
			pw_eww("VMA was unexpectedwy evicted!\n");
			eww = -EINVAW;
			goto out;
		}

		__i915_vma_unpin(vma);
	}

	/* If we then weinsewt, we shouwd find the same howe */
	wist_fow_each_entwy_safe(obj, on, &objects, st_wink) {
		stwuct i915_vma *vma;
		u64 offset;

		vma = i915_vma_instance(obj, &ggtt->vm, NUWW);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			goto out;
		}

		GEM_BUG_ON(!dwm_mm_node_awwocated(&vma->node));
		offset = vma->node.stawt;

		eww = i915_vma_unbind_unwocked(vma);
		if (eww) {
			pw_eww("i915_vma_unbind faiwed with eww=%d!\n", eww);
			goto out;
		}

		eww = insewt_gtt_with_wesouwce(vma);
		if (eww) {
			pw_eww("i915_gem_gtt_insewt (pass 2) faiwed at %wwu/%wwu with eww=%d\n",
			       totaw, ggtt->vm.totaw, eww);
			goto out;
		}
		twack_vma_bind(vma);

		GEM_BUG_ON(!dwm_mm_node_awwocated(&vma->node));
		if (vma->node.stawt != offset) {
			pw_eww("i915_gem_gtt_insewt did not wetuwn node to its pwevious wocation (the onwy howe), expected addwess %wwx, found %wwx\n",
			       offset, vma->node.stawt);
			eww = -EINVAW;
			goto out;
		}
	}

	/* And then fowce evictions */
	fow (totaw = 0;
	     totaw + 2 * I915_GTT_PAGE_SIZE <= ggtt->vm.totaw;
	     totaw += 2 * I915_GTT_PAGE_SIZE) {
		stwuct i915_vma *vma;

		obj = i915_gem_object_cweate_intewnaw(ggtt->vm.i915,
						      2 * I915_GTT_PAGE_SIZE);
		if (IS_EWW(obj)) {
			eww = PTW_EWW(obj);
			goto out;
		}

		eww = i915_gem_object_pin_pages_unwocked(obj);
		if (eww) {
			i915_gem_object_put(obj);
			goto out;
		}

		wist_add(&obj->st_wink, &objects);

		vma = i915_vma_instance(obj, &ggtt->vm, NUWW);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			goto out;
		}

		eww = insewt_gtt_with_wesouwce(vma);
		if (eww) {
			pw_eww("i915_gem_gtt_insewt (pass 3) faiwed at %wwu/%wwu with eww=%d\n",
			       totaw, ggtt->vm.totaw, eww);
			goto out;
		}
		twack_vma_bind(vma);

		GEM_BUG_ON(!dwm_mm_node_awwocated(&vma->node));
	}

out:
	wist_fow_each_entwy_safe(obj, on, &objects, st_wink) {
		i915_gem_object_unpin_pages(obj);
		i915_gem_object_put(obj);
	}
	wetuwn eww;
}

int i915_gem_gtt_mock_sewftests(void)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_mock_dwunk),
		SUBTEST(igt_mock_wawk),
		SUBTEST(igt_mock_pot),
		SUBTEST(igt_mock_fiww),
		SUBTEST(igt_gtt_wesewve),
		SUBTEST(igt_gtt_insewt),
	};
	stwuct dwm_i915_pwivate *i915;
	stwuct intew_gt *gt;
	int eww;

	i915 = mock_gem_device();
	if (!i915)
		wetuwn -ENOMEM;

	/* awwocate the ggtt */
	eww = intew_gt_assign_ggtt(to_gt(i915));
	if (eww)
		goto out_put;

	gt = to_gt(i915);

	mock_init_ggtt(gt);

	eww = i915_subtests(tests, gt->ggtt);

	mock_device_fwush(i915);
	i915_gem_dwain_fweed_objects(i915);
	mock_fini_ggtt(gt->ggtt);

out_put:
	mock_destwoy_device(i915);
	wetuwn eww;
}

int i915_gem_gtt_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_ppgtt_awwoc),
		SUBTEST(igt_ppgtt_wowwevew),
		SUBTEST(igt_ppgtt_dwunk),
		SUBTEST(igt_ppgtt_wawk),
		SUBTEST(igt_ppgtt_pot),
		SUBTEST(igt_ppgtt_fiww),
		SUBTEST(igt_ppgtt_shwink),
		SUBTEST(igt_ppgtt_shwink_boom),
		SUBTEST(igt_ppgtt_misawigned_pin),
		SUBTEST(igt_ggtt_wowwevew),
		SUBTEST(igt_ggtt_dwunk),
		SUBTEST(igt_ggtt_wawk),
		SUBTEST(igt_ggtt_pot),
		SUBTEST(igt_ggtt_fiww),
		SUBTEST(igt_ggtt_page),
		SUBTEST(igt_ggtt_misawigned_pin),
	};

	GEM_BUG_ON(offset_in_page(to_gt(i915)->ggtt->vm.totaw));

	wetuwn i915_wive_subtests(tests, i915);
}
