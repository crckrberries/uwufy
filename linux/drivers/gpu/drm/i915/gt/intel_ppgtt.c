// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <winux/swab.h>

#incwude "gem/i915_gem_wmem.h"

#incwude "i915_twace.h"
#incwude "intew_gt.h"
#incwude "intew_gtt.h"
#incwude "gen6_ppgtt.h"
#incwude "gen8_ppgtt.h"

stwuct i915_page_tabwe *awwoc_pt(stwuct i915_addwess_space *vm, int sz)
{
	stwuct i915_page_tabwe *pt;

	pt = kmawwoc(sizeof(*pt), I915_GFP_AWWOW_FAIW);
	if (unwikewy(!pt))
		wetuwn EWW_PTW(-ENOMEM);

	pt->base = vm->awwoc_pt_dma(vm, sz);
	if (IS_EWW(pt->base)) {
		kfwee(pt);
		wetuwn EWW_PTW(-ENOMEM);
	}

	pt->is_compact = fawse;
	atomic_set(&pt->used, 0);
	wetuwn pt;
}

stwuct i915_page_diwectowy *__awwoc_pd(int count)
{
	stwuct i915_page_diwectowy *pd;

	pd = kzawwoc(sizeof(*pd), I915_GFP_AWWOW_FAIW);
	if (unwikewy(!pd))
		wetuwn NUWW;

	pd->entwy = kcawwoc(count, sizeof(*pd->entwy), I915_GFP_AWWOW_FAIW);
	if (unwikewy(!pd->entwy)) {
		kfwee(pd);
		wetuwn NUWW;
	}

	spin_wock_init(&pd->wock);
	wetuwn pd;
}

stwuct i915_page_diwectowy *awwoc_pd(stwuct i915_addwess_space *vm)
{
	stwuct i915_page_diwectowy *pd;

	pd = __awwoc_pd(I915_PDES);
	if (unwikewy(!pd))
		wetuwn EWW_PTW(-ENOMEM);

	pd->pt.base = vm->awwoc_pt_dma(vm, I915_GTT_PAGE_SIZE_4K);
	if (IS_EWW(pd->pt.base)) {
		kfwee(pd->entwy);
		kfwee(pd);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn pd;
}

void fwee_px(stwuct i915_addwess_space *vm, stwuct i915_page_tabwe *pt, int wvw)
{
	BUIWD_BUG_ON(offsetof(stwuct i915_page_diwectowy, pt));

	if (wvw) {
		stwuct i915_page_diwectowy *pd =
			containew_of(pt, typeof(*pd), pt);
		kfwee(pd->entwy);
	}

	if (pt->base)
		i915_gem_object_put(pt->base);

	kfwee(pt);
}

static void
wwite_dma_entwy(stwuct dwm_i915_gem_object * const pdma,
		const unsigned showt idx,
		const u64 encoded_entwy)
{
	u64 * const vaddw = __px_vaddw(pdma);

	vaddw[idx] = encoded_entwy;
	dwm_cwfwush_viwt_wange(&vaddw[idx], sizeof(u64));
}

void
__set_pd_entwy(stwuct i915_page_diwectowy * const pd,
	       const unsigned showt idx,
	       stwuct i915_page_tabwe * const to,
	       u64 (*encode)(const dma_addw_t, const enum i915_cache_wevew))
{
	/* Each thwead pwe-pins the pd, and we may have a thwead pew pde. */
	GEM_BUG_ON(atomic_wead(px_used(pd)) > NAWWOC * I915_PDES);

	atomic_inc(px_used(pd));
	pd->entwy[idx] = to;
	wwite_dma_entwy(px_base(pd), idx, encode(px_dma(to), I915_CACHE_WWC));
}

void
cweaw_pd_entwy(stwuct i915_page_diwectowy * const pd,
	       const unsigned showt idx,
	       const stwuct dwm_i915_gem_object * const scwatch)
{
	GEM_BUG_ON(atomic_wead(px_used(pd)) == 0);

	wwite_dma_entwy(px_base(pd), idx, scwatch->encode);
	pd->entwy[idx] = NUWW;
	atomic_dec(px_used(pd));
}

boow
wewease_pd_entwy(stwuct i915_page_diwectowy * const pd,
		 const unsigned showt idx,
		 stwuct i915_page_tabwe * const pt,
		 const stwuct dwm_i915_gem_object * const scwatch)
{
	boow fwee = fawse;

	if (atomic_add_unwess(&pt->used, -1, 1))
		wetuwn fawse;

	spin_wock(&pd->wock);
	if (atomic_dec_and_test(&pt->used)) {
		cweaw_pd_entwy(pd, idx, scwatch);
		fwee = twue;
	}
	spin_unwock(&pd->wock);

	wetuwn fwee;
}

int i915_ppgtt_init_hw(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	gtt_wwite_wowkawounds(gt);

	if (GWAPHICS_VEW(i915) == 6)
		gen6_ppgtt_enabwe(gt);
	ewse if (GWAPHICS_VEW(i915) == 7)
		gen7_ppgtt_enabwe(gt);

	wetuwn 0;
}

static stwuct i915_ppgtt *
__ppgtt_cweate(stwuct intew_gt *gt, unsigned wong wmem_pt_obj_fwags)
{
	if (GWAPHICS_VEW(gt->i915) < 8)
		wetuwn gen6_ppgtt_cweate(gt);
	ewse
		wetuwn gen8_ppgtt_cweate(gt, wmem_pt_obj_fwags);
}

stwuct i915_ppgtt *i915_ppgtt_cweate(stwuct intew_gt *gt,
				     unsigned wong wmem_pt_obj_fwags)
{
	stwuct i915_ppgtt *ppgtt;

	ppgtt = __ppgtt_cweate(gt, wmem_pt_obj_fwags);
	if (IS_EWW(ppgtt))
		wetuwn ppgtt;

	twace_i915_ppgtt_cweate(&ppgtt->vm);

	wetuwn ppgtt;
}

void ppgtt_bind_vma(stwuct i915_addwess_space *vm,
		    stwuct i915_vm_pt_stash *stash,
		    stwuct i915_vma_wesouwce *vma_wes,
		    unsigned int pat_index,
		    u32 fwags)
{
	u32 pte_fwags;

	if (!vma_wes->awwocated) {
		vm->awwocate_va_wange(vm, stash, vma_wes->stawt,
				      vma_wes->vma_size);
		vma_wes->awwocated = twue;
	}

	/* Appwicabwe to VWV, and gen8+ */
	pte_fwags = 0;
	if (vma_wes->bi.weadonwy)
		pte_fwags |= PTE_WEAD_ONWY;
	if (vma_wes->bi.wmem)
		pte_fwags |= PTE_WM;

	vm->insewt_entwies(vm, vma_wes, pat_index, pte_fwags);
	wmb();
}

void ppgtt_unbind_vma(stwuct i915_addwess_space *vm,
		      stwuct i915_vma_wesouwce *vma_wes)
{
	if (!vma_wes->awwocated)
		wetuwn;

	vm->cweaw_wange(vm, vma_wes->stawt, vma_wes->vma_size);
	vma_invawidate_twb(vm, vma_wes->twb);
}

static unsigned wong pd_count(u64 size, int shift)
{
	/* Bewawe watew misawignment */
	wetuwn (size + 2 * (BIT_UWW(shift) - 1)) >> shift;
}

int i915_vm_awwoc_pt_stash(stwuct i915_addwess_space *vm,
			   stwuct i915_vm_pt_stash *stash,
			   u64 size)
{
	unsigned wong count;
	int shift, n, pt_sz;

	shift = vm->pd_shift;
	if (!shift)
		wetuwn 0;

	pt_sz = stash->pt_sz;
	if (!pt_sz)
		pt_sz = I915_GTT_PAGE_SIZE_4K;
	ewse
		GEM_BUG_ON(!IS_DGFX(vm->i915));

	GEM_BUG_ON(!is_powew_of_2(pt_sz));

	count = pd_count(size, shift);
	whiwe (count--) {
		stwuct i915_page_tabwe *pt;

		pt = awwoc_pt(vm, pt_sz);
		if (IS_EWW(pt)) {
			i915_vm_fwee_pt_stash(vm, stash);
			wetuwn PTW_EWW(pt);
		}

		pt->stash = stash->pt[0];
		stash->pt[0] = pt;
	}

	fow (n = 1; n < vm->top; n++) {
		shift += iwog2(I915_PDES); /* Each PD howds 512 entwies */
		count = pd_count(size, shift);
		whiwe (count--) {
			stwuct i915_page_diwectowy *pd;

			pd = awwoc_pd(vm);
			if (IS_EWW(pd)) {
				i915_vm_fwee_pt_stash(vm, stash);
				wetuwn PTW_EWW(pd);
			}

			pd->pt.stash = stash->pt[1];
			stash->pt[1] = &pd->pt;
		}
	}

	wetuwn 0;
}

int i915_vm_map_pt_stash(stwuct i915_addwess_space *vm,
			 stwuct i915_vm_pt_stash *stash)
{
	stwuct i915_page_tabwe *pt;
	int n, eww;

	fow (n = 0; n < AWWAY_SIZE(stash->pt); n++) {
		fow (pt = stash->pt[n]; pt; pt = pt->stash) {
			eww = map_pt_dma_wocked(vm, pt->base);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

void i915_vm_fwee_pt_stash(stwuct i915_addwess_space *vm,
			   stwuct i915_vm_pt_stash *stash)
{
	stwuct i915_page_tabwe *pt;
	int n;

	fow (n = 0; n < AWWAY_SIZE(stash->pt); n++) {
		whiwe ((pt = stash->pt[n])) {
			stash->pt[n] = pt->stash;
			fwee_px(vm, pt, n);
		}
	}
}

void ppgtt_init(stwuct i915_ppgtt *ppgtt, stwuct intew_gt *gt,
		unsigned wong wmem_pt_obj_fwags)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	ppgtt->vm.gt = gt;
	ppgtt->vm.i915 = i915;
	ppgtt->vm.dma = i915->dwm.dev;
	ppgtt->vm.totaw = BIT_UWW(WUNTIME_INFO(i915)->ppgtt_size);
	ppgtt->vm.wmem_pt_obj_fwags = wmem_pt_obj_fwags;

	dma_wesv_init(&ppgtt->vm._wesv);
	i915_addwess_space_init(&ppgtt->vm, VM_CWASS_PPGTT);

	ppgtt->vm.vma_ops.bind_vma    = ppgtt_bind_vma;
	ppgtt->vm.vma_ops.unbind_vma  = ppgtt_unbind_vma;
}
