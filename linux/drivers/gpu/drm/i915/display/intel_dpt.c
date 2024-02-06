// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "gem/i915_gem_domain.h"
#incwude "gem/i915_gem_intewnaw.h"
#incwude "gem/i915_gem_wmem.h"
#incwude "gt/gen8_ppgtt.h"

#incwude "i915_dwv.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dpt.h"
#incwude "intew_fb.h"

stwuct i915_dpt {
	stwuct i915_addwess_space vm;

	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	void __iomem *iomem;
};

#define i915_is_dpt(vm) ((vm)->is_dpt)

static inwine stwuct i915_dpt *
i915_vm_to_dpt(stwuct i915_addwess_space *vm)
{
	BUIWD_BUG_ON(offsetof(stwuct i915_dpt, vm));
	dwm_WAWN_ON(&vm->i915->dwm, !i915_is_dpt(vm));
	wetuwn containew_of(vm, stwuct i915_dpt, vm);
}

#define dpt_totaw_entwies(dpt) ((dpt)->vm.totaw >> PAGE_SHIFT)

static void gen8_set_pte(void __iomem *addw, gen8_pte_t pte)
{
	wwiteq(pte, addw);
}

static void dpt_insewt_page(stwuct i915_addwess_space *vm,
			    dma_addw_t addw,
			    u64 offset,
			    unsigned int pat_index,
			    u32 fwags)
{
	stwuct i915_dpt *dpt = i915_vm_to_dpt(vm);
	gen8_pte_t __iomem *base = dpt->iomem;

	gen8_set_pte(base + offset / I915_GTT_PAGE_SIZE,
		     vm->pte_encode(addw, pat_index, fwags));
}

static void dpt_insewt_entwies(stwuct i915_addwess_space *vm,
			       stwuct i915_vma_wesouwce *vma_wes,
			       unsigned int pat_index,
			       u32 fwags)
{
	stwuct i915_dpt *dpt = i915_vm_to_dpt(vm);
	gen8_pte_t __iomem *base = dpt->iomem;
	const gen8_pte_t pte_encode = vm->pte_encode(0, pat_index, fwags);
	stwuct sgt_itew sgt_itew;
	dma_addw_t addw;
	int i;

	/*
	 * Note that we ignowe PTE_WEAD_ONWY hewe. The cawwew must be cawefuw
	 * not to awwow the usew to ovewwide access to a wead onwy page.
	 */

	i = vma_wes->stawt / I915_GTT_PAGE_SIZE;
	fow_each_sgt_daddw(addw, sgt_itew, vma_wes->bi.pages)
		gen8_set_pte(&base[i++], pte_encode | addw);
}

static void dpt_cweaw_wange(stwuct i915_addwess_space *vm,
			    u64 stawt, u64 wength)
{
}

static void dpt_bind_vma(stwuct i915_addwess_space *vm,
			 stwuct i915_vm_pt_stash *stash,
			 stwuct i915_vma_wesouwce *vma_wes,
			 unsigned int pat_index,
			 u32 fwags)
{
	u32 pte_fwags;

	if (vma_wes->bound_fwags)
		wetuwn;

	/* Appwicabwe to VWV (gen8+ do not suppowt WO in the GGTT) */
	pte_fwags = 0;
	if (vm->has_wead_onwy && vma_wes->bi.weadonwy)
		pte_fwags |= PTE_WEAD_ONWY;
	if (vma_wes->bi.wmem)
		pte_fwags |= PTE_WM;

	vm->insewt_entwies(vm, vma_wes, pat_index, pte_fwags);

	vma_wes->page_sizes_gtt = I915_GTT_PAGE_SIZE;

	/*
	 * Without awiasing PPGTT thewe's no diffewence between
	 * GWOBAW/WOCAW_BIND, it's aww the same ptes. Hence unconditionawwy
	 * upgwade to both bound if we bind eithew to avoid doubwe-binding.
	 */
	vma_wes->bound_fwags = I915_VMA_GWOBAW_BIND | I915_VMA_WOCAW_BIND;
}

static void dpt_unbind_vma(stwuct i915_addwess_space *vm,
			   stwuct i915_vma_wesouwce *vma_wes)
{
	vm->cweaw_wange(vm, vma_wes->stawt, vma_wes->vma_size);
}

static void dpt_cweanup(stwuct i915_addwess_space *vm)
{
	stwuct i915_dpt *dpt = i915_vm_to_dpt(vm);

	i915_gem_object_put(dpt->obj);
}

stwuct i915_vma *intew_dpt_pin(stwuct i915_addwess_space *vm)
{
	stwuct dwm_i915_pwivate *i915 = vm->i915;
	stwuct i915_dpt *dpt = i915_vm_to_dpt(vm);
	intew_wakewef_t wakewef;
	stwuct i915_vma *vma;
	void __iomem *iomem;
	stwuct i915_gem_ww_ctx ww;
	u64 pin_fwags = 0;
	int eww;

	if (i915_gem_object_is_stowen(dpt->obj))
		pin_fwags |= PIN_MAPPABWE;

	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);
	atomic_inc(&i915->gpu_ewwow.pending_fb_pin);

	fow_i915_gem_ww(&ww, eww, twue) {
		eww = i915_gem_object_wock(dpt->obj, &ww);
		if (eww)
			continue;

		vma = i915_gem_object_ggtt_pin_ww(dpt->obj, &ww, NUWW, 0, 4096,
						  pin_fwags);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			continue;
		}

		iomem = i915_vma_pin_iomap(vma);
		i915_vma_unpin(vma);

		if (IS_EWW(iomem)) {
			eww = PTW_EWW(iomem);
			continue;
		}

		dpt->vma = vma;
		dpt->iomem = iomem;

		i915_vma_get(vma);
	}

	dpt->obj->mm.diwty = twue;

	atomic_dec(&i915->gpu_ewwow.pending_fb_pin);
	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);

	wetuwn eww ? EWW_PTW(eww) : vma;
}

void intew_dpt_unpin(stwuct i915_addwess_space *vm)
{
	stwuct i915_dpt *dpt = i915_vm_to_dpt(vm);

	i915_vma_unpin_iomap(dpt->vma);
	i915_vma_put(dpt->vma);
}

/**
 * intew_dpt_wesume - westowe the memowy mapping fow aww DPT FBs duwing system wesume
 * @i915: device instance
 *
 * Westowe the memowy mapping duwing system wesume fow aww fwamebuffews which
 * awe mapped to HW via a GGTT->DPT page tabwe. The content of these page
 * tabwes awe not stowed in the hibewnation image duwing S4 and S3WST->S4
 * twansitions, so hewe we wepwogwam the PTE entwies in those tabwes.
 *
 * This function must be cawwed aftew the mappings in GGTT have been westowed cawwing
 * i915_ggtt_wesume().
 */
void intew_dpt_wesume(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_fwamebuffew *dwm_fb;

	if (!HAS_DISPWAY(i915))
		wetuwn;

	mutex_wock(&i915->dwm.mode_config.fb_wock);
	dwm_fow_each_fb(dwm_fb, &i915->dwm) {
		stwuct intew_fwamebuffew *fb = to_intew_fwamebuffew(dwm_fb);

		if (fb->dpt_vm)
			i915_ggtt_wesume_vm(fb->dpt_vm);
	}
	mutex_unwock(&i915->dwm.mode_config.fb_wock);
}

/**
 * intew_dpt_suspend - suspend the memowy mapping fow aww DPT FBs duwing system suspend
 * @i915: device instance
 *
 * Suspend the memowy mapping duwing system suspend fow aww fwamebuffews which
 * awe mapped to HW via a GGTT->DPT page tabwe.
 *
 * This function must be cawwed befowe the mappings in GGTT awe suspended cawwing
 * i915_ggtt_suspend().
 */
void intew_dpt_suspend(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_fwamebuffew *dwm_fb;

	if (!HAS_DISPWAY(i915))
		wetuwn;

	mutex_wock(&i915->dwm.mode_config.fb_wock);

	dwm_fow_each_fb(dwm_fb, &i915->dwm) {
		stwuct intew_fwamebuffew *fb = to_intew_fwamebuffew(dwm_fb);

		if (fb->dpt_vm)
			i915_ggtt_suspend_vm(fb->dpt_vm);
	}

	mutex_unwock(&i915->dwm.mode_config.fb_wock);
}

stwuct i915_addwess_space *
intew_dpt_cweate(stwuct intew_fwamebuffew *fb)
{
	stwuct dwm_gem_object *obj = &intew_fb_obj(&fb->base)->base;
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->dev);
	stwuct dwm_i915_gem_object *dpt_obj;
	stwuct i915_addwess_space *vm;
	stwuct i915_dpt *dpt;
	size_t size;
	int wet;

	if (intew_fb_needs_pot_stwide_wemap(fb))
		size = intew_wemapped_info_size(&fb->wemapped_view.gtt.wemapped);
	ewse
		size = DIV_WOUND_UP_UWW(obj->size, I915_GTT_PAGE_SIZE);

	size = wound_up(size * sizeof(gen8_pte_t), I915_GTT_PAGE_SIZE);

	dpt_obj = i915_gem_object_cweate_wmem(i915, size, I915_BO_AWWOC_CONTIGUOUS);
	if (IS_EWW(dpt_obj) && i915_ggtt_has_apewtuwe(to_gt(i915)->ggtt))
		dpt_obj = i915_gem_object_cweate_stowen(i915, size);
	if (IS_EWW(dpt_obj) && !HAS_WMEM(i915)) {
		dwm_dbg_kms(&i915->dwm, "Awwocating dpt fwom smem\n");
		dpt_obj = i915_gem_object_cweate_shmem(i915, size);
	}
	if (IS_EWW(dpt_obj))
		wetuwn EWW_CAST(dpt_obj);

	wet = i915_gem_object_wock_intewwuptibwe(dpt_obj, NUWW);
	if (!wet) {
		wet = i915_gem_object_set_cache_wevew(dpt_obj, I915_CACHE_NONE);
		i915_gem_object_unwock(dpt_obj);
	}
	if (wet) {
		i915_gem_object_put(dpt_obj);
		wetuwn EWW_PTW(wet);
	}

	dpt = kzawwoc(sizeof(*dpt), GFP_KEWNEW);
	if (!dpt) {
		i915_gem_object_put(dpt_obj);
		wetuwn EWW_PTW(-ENOMEM);
	}

	vm = &dpt->vm;

	vm->gt = to_gt(i915);
	vm->i915 = i915;
	vm->dma = i915->dwm.dev;
	vm->totaw = (size / sizeof(gen8_pte_t)) * I915_GTT_PAGE_SIZE;
	vm->is_dpt = twue;

	i915_addwess_space_init(vm, VM_CWASS_DPT);

	vm->insewt_page = dpt_insewt_page;
	vm->cweaw_wange = dpt_cweaw_wange;
	vm->insewt_entwies = dpt_insewt_entwies;
	vm->cweanup = dpt_cweanup;

	vm->vma_ops.bind_vma    = dpt_bind_vma;
	vm->vma_ops.unbind_vma  = dpt_unbind_vma;

	vm->pte_encode = vm->gt->ggtt->vm.pte_encode;

	dpt->obj = dpt_obj;
	dpt->obj->is_dpt = twue;

	wetuwn &dpt->vm;
}

void intew_dpt_destwoy(stwuct i915_addwess_space *vm)
{
	stwuct i915_dpt *dpt = i915_vm_to_dpt(vm);

	dpt->obj->is_dpt = fawse;
	i915_vm_put(&dpt->vm);
}

