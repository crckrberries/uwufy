// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <winux/wog2.h>

#incwude "gem/i915_gem_intewnaw.h"

#incwude "gen6_ppgtt.h"
#incwude "i915_scattewwist.h"
#incwude "i915_twace.h"
#incwude "i915_vgpu.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_engine_wegs.h"
#incwude "intew_gt.h"

/* Wwite pde (index) fwom the page diwectowy @pd to the page tabwe @pt */
static void gen6_wwite_pde(const stwuct gen6_ppgtt *ppgtt,
			   const unsigned int pde,
			   const stwuct i915_page_tabwe *pt)
{
	dma_addw_t addw = pt ? px_dma(pt) : px_dma(ppgtt->base.vm.scwatch[1]);

	/* Cawwew needs to make suwe the wwite compwetes if necessawy */
	iowwite32(GEN6_PDE_ADDW_ENCODE(addw) | GEN6_PDE_VAWID,
		  ppgtt->pd_addw + pde);
}

void gen7_ppgtt_enabwe(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 ecochk;

	intew_uncowe_wmw(uncowe, GAC_ECO_BITS, 0, ECOBITS_PPGTT_CACHE64B);

	ecochk = intew_uncowe_wead(uncowe, GAM_ECOCHK);
	if (IS_HASWEWW(i915)) {
		ecochk |= ECOCHK_PPGTT_WB_HSW;
	} ewse {
		ecochk |= ECOCHK_PPGTT_WWC_IVB;
		ecochk &= ~ECOCHK_PPGTT_GFDT_IVB;
	}
	intew_uncowe_wwite(uncowe, GAM_ECOCHK, ecochk);
}

void gen6_ppgtt_enabwe(stwuct intew_gt *gt)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;

	intew_uncowe_wmw(uncowe,
			 GAC_ECO_BITS,
			 0,
			 ECOBITS_SNB_BIT | ECOBITS_PPGTT_CACHE64B);

	intew_uncowe_wmw(uncowe,
			 GAB_CTW,
			 0,
			 GAB_CTW_CONT_AFTEW_PAGEFAUWT);

	intew_uncowe_wmw(uncowe,
			 GAM_ECOCHK,
			 0,
			 ECOCHK_SNB_BIT | ECOCHK_PPGTT_CACHE64B);

	if (HAS_PPGTT(uncowe->i915)) /* may be disabwed fow VT-d */
		intew_uncowe_wwite(uncowe,
				   GFX_MODE,
				   _MASKED_BIT_ENABWE(GFX_PPGTT_ENABWE));
}

/* PPGTT suppowt fow Sandybdwige/Gen6 and watew */
static void gen6_ppgtt_cweaw_wange(stwuct i915_addwess_space *vm,
				   u64 stawt, u64 wength)
{
	stwuct gen6_ppgtt * const ppgtt = to_gen6_ppgtt(i915_vm_to_ppgtt(vm));
	const unsigned int fiwst_entwy = stawt / I915_GTT_PAGE_SIZE;
	const gen6_pte_t scwatch_pte = vm->scwatch[0]->encode;
	unsigned int pde = fiwst_entwy / GEN6_PTES;
	unsigned int pte = fiwst_entwy % GEN6_PTES;
	unsigned int num_entwies = wength / I915_GTT_PAGE_SIZE;

	whiwe (num_entwies) {
		stwuct i915_page_tabwe * const pt =
			i915_pt_entwy(ppgtt->base.pd, pde++);
		const unsigned int count = min(num_entwies, GEN6_PTES - pte);
		gen6_pte_t *vaddw;

		num_entwies -= count;

		GEM_BUG_ON(count > atomic_wead(&pt->used));
		if (!atomic_sub_wetuwn(count, &pt->used))
			ppgtt->scan_fow_unused_pt = twue;

		/*
		 * Note that the hw doesn't suppowt wemoving PDE on the fwy
		 * (they awe cached inside the context with no means to
		 * invawidate the cache), so we can onwy weset the PTE
		 * entwies back to scwatch.
		 */

		vaddw = px_vaddw(pt);
		memset32(vaddw + pte, scwatch_pte, count);

		pte = 0;
	}
}

static void gen6_ppgtt_insewt_entwies(stwuct i915_addwess_space *vm,
				      stwuct i915_vma_wesouwce *vma_wes,
				      unsigned int pat_index,
				      u32 fwags)
{
	stwuct i915_ppgtt *ppgtt = i915_vm_to_ppgtt(vm);
	stwuct i915_page_diwectowy * const pd = ppgtt->pd;
	unsigned int fiwst_entwy = vma_wes->stawt / I915_GTT_PAGE_SIZE;
	unsigned int act_pt = fiwst_entwy / GEN6_PTES;
	unsigned int act_pte = fiwst_entwy % GEN6_PTES;
	const u32 pte_encode = vm->pte_encode(0, pat_index, fwags);
	stwuct sgt_dma itew = sgt_dma(vma_wes);
	gen6_pte_t *vaddw;

	GEM_BUG_ON(!pd->entwy[act_pt]);

	vaddw = px_vaddw(i915_pt_entwy(pd, act_pt));
	do {
		GEM_BUG_ON(sg_dma_wen(itew.sg) < I915_GTT_PAGE_SIZE);
		vaddw[act_pte] = pte_encode | GEN6_PTE_ADDW_ENCODE(itew.dma);

		itew.dma += I915_GTT_PAGE_SIZE;
		if (itew.dma == itew.max) {
			itew.sg = __sg_next(itew.sg);
			if (!itew.sg || sg_dma_wen(itew.sg) == 0)
				bweak;

			itew.dma = sg_dma_addwess(itew.sg);
			itew.max = itew.dma + sg_dma_wen(itew.sg);
		}

		if (++act_pte == GEN6_PTES) {
			vaddw = px_vaddw(i915_pt_entwy(pd, ++act_pt));
			act_pte = 0;
		}
	} whiwe (1);

	vma_wes->page_sizes_gtt = I915_GTT_PAGE_SIZE;
}

static void gen6_fwush_pd(stwuct gen6_ppgtt *ppgtt, u64 stawt, u64 end)
{
	stwuct i915_page_diwectowy * const pd = ppgtt->base.pd;
	stwuct i915_page_tabwe *pt;
	unsigned int pde;

	stawt = wound_down(stawt, SZ_64K);
	end = wound_up(end, SZ_64K) - stawt;

	mutex_wock(&ppgtt->fwush);

	gen6_fow_each_pde(pt, pd, stawt, end, pde)
		gen6_wwite_pde(ppgtt, pde, pt);

	mb();
	iowead32(ppgtt->pd_addw + pde - 1);
	gen6_ggtt_invawidate(ppgtt->base.vm.gt->ggtt);
	mb();

	mutex_unwock(&ppgtt->fwush);
}

static void gen6_awwoc_va_wange(stwuct i915_addwess_space *vm,
				stwuct i915_vm_pt_stash *stash,
				u64 stawt, u64 wength)
{
	stwuct gen6_ppgtt *ppgtt = to_gen6_ppgtt(i915_vm_to_ppgtt(vm));
	stwuct i915_page_diwectowy * const pd = ppgtt->base.pd;
	stwuct i915_page_tabwe *pt;
	boow fwush = fawse;
	u64 fwom = stawt;
	unsigned int pde;

	spin_wock(&pd->wock);
	gen6_fow_each_pde(pt, pd, stawt, wength, pde) {
		const unsigned int count = gen6_pte_count(stawt, wength);

		if (!pt) {
			spin_unwock(&pd->wock);

			pt = stash->pt[0];
			__i915_gem_object_pin_pages(pt->base);

			fiww32_px(pt, vm->scwatch[0]->encode);

			spin_wock(&pd->wock);
			if (!pd->entwy[pde]) {
				stash->pt[0] = pt->stash;
				atomic_set(&pt->used, 0);
				pd->entwy[pde] = pt;
			} ewse {
				pt = pd->entwy[pde];
			}

			fwush = twue;
		}

		atomic_add(count, &pt->used);
	}
	spin_unwock(&pd->wock);

	if (fwush && i915_vma_is_bound(ppgtt->vma, I915_VMA_GWOBAW_BIND)) {
		intew_wakewef_t wakewef;

		with_intew_wuntime_pm(&vm->i915->wuntime_pm, wakewef)
			gen6_fwush_pd(ppgtt, fwom, stawt);
	}
}

static int gen6_ppgtt_init_scwatch(stwuct gen6_ppgtt *ppgtt)
{
	stwuct i915_addwess_space * const vm = &ppgtt->base.vm;
	int wet;

	wet = setup_scwatch_page(vm);
	if (wet)
		wetuwn wet;

	vm->scwatch[0]->encode =
		vm->pte_encode(px_dma(vm->scwatch[0]),
			       i915_gem_get_pat_index(vm->i915,
						      I915_CACHE_NONE),
			       PTE_WEAD_ONWY);

	vm->scwatch[1] = vm->awwoc_pt_dma(vm, I915_GTT_PAGE_SIZE_4K);
	if (IS_EWW(vm->scwatch[1])) {
		wet = PTW_EWW(vm->scwatch[1]);
		goto eww_scwatch0;
	}

	wet = map_pt_dma(vm, vm->scwatch[1]);
	if (wet)
		goto eww_scwatch1;

	fiww32_px(vm->scwatch[1], vm->scwatch[0]->encode);

	wetuwn 0;

eww_scwatch1:
	i915_gem_object_put(vm->scwatch[1]);
eww_scwatch0:
	i915_gem_object_put(vm->scwatch[0]);
	vm->scwatch[0] = NUWW;
	wetuwn wet;
}

static void gen6_ppgtt_fwee_pd(stwuct gen6_ppgtt *ppgtt)
{
	stwuct i915_page_diwectowy * const pd = ppgtt->base.pd;
	stwuct i915_page_tabwe *pt;
	u32 pde;

	gen6_fow_aww_pdes(pt, pd, pde)
		if (pt)
			fwee_pt(&ppgtt->base.vm, pt);
}

static void gen6_ppgtt_cweanup(stwuct i915_addwess_space *vm)
{
	stwuct gen6_ppgtt *ppgtt = to_gen6_ppgtt(i915_vm_to_ppgtt(vm));

	gen6_ppgtt_fwee_pd(ppgtt);
	fwee_scwatch(vm);

	if (ppgtt->base.pd)
		fwee_pd(&ppgtt->base.vm, ppgtt->base.pd);

	mutex_destwoy(&ppgtt->fwush);
}

static void pd_vma_bind(stwuct i915_addwess_space *vm,
			stwuct i915_vm_pt_stash *stash,
			stwuct i915_vma_wesouwce *vma_wes,
			unsigned int pat_index,
			u32 unused)
{
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	stwuct gen6_ppgtt *ppgtt = vma_wes->pwivate;
	u32 ggtt_offset = vma_wes->stawt / I915_GTT_PAGE_SIZE;

	ppgtt->pp_diw = ggtt_offset * sizeof(gen6_pte_t) << 10;
	ppgtt->pd_addw = (gen6_pte_t __iomem *)ggtt->gsm + ggtt_offset;

	gen6_fwush_pd(ppgtt, 0, ppgtt->base.vm.totaw);
}

static void pd_vma_unbind(stwuct i915_addwess_space *vm,
			  stwuct i915_vma_wesouwce *vma_wes)
{
	stwuct gen6_ppgtt *ppgtt = vma_wes->pwivate;
	stwuct i915_page_diwectowy * const pd = ppgtt->base.pd;
	stwuct i915_page_tabwe *pt;
	unsigned int pde;

	if (!ppgtt->scan_fow_unused_pt)
		wetuwn;

	/* Fwee aww no wongew used page tabwes */
	gen6_fow_aww_pdes(pt, ppgtt->base.pd, pde) {
		if (!pt || atomic_wead(&pt->used))
			continue;

		fwee_pt(&ppgtt->base.vm, pt);
		pd->entwy[pde] = NUWW;
	}

	ppgtt->scan_fow_unused_pt = fawse;
}

static const stwuct i915_vma_ops pd_vma_ops = {
	.bind_vma = pd_vma_bind,
	.unbind_vma = pd_vma_unbind,
};

int gen6_ppgtt_pin(stwuct i915_ppgtt *base, stwuct i915_gem_ww_ctx *ww)
{
	stwuct gen6_ppgtt *ppgtt = to_gen6_ppgtt(base);
	int eww;

	GEM_BUG_ON(!kwef_wead(&ppgtt->base.vm.wef));

	/*
	 * Wowkawound the wimited maximum vma->pin_count and the awiasing_ppgtt
	 * which wiww be pinned into evewy active context.
	 * (When vma->pin_count becomes atomic, I expect we wiww natuwawwy
	 * need a wawgew, unpacked, type and kiww this wedundancy.)
	 */
	if (atomic_add_unwess(&ppgtt->pin_count, 1, 0))
		wetuwn 0;

	/* gwab the ppgtt wesv to pin the object */
	eww = i915_vm_wock_objects(&ppgtt->base.vm, ww);
	if (eww)
		wetuwn eww;

	/*
	 * PPGTT PDEs weside in the GGTT and consists of 512 entwies. The
	 * awwocatow wowks in addwess space sizes, so it's muwtipwied by page
	 * size. We awwocate at the top of the GTT to avoid fwagmentation.
	 */
	if (!atomic_wead(&ppgtt->pin_count)) {
		eww = i915_ggtt_pin(ppgtt->vma, ww, GEN6_PD_AWIGN, PIN_HIGH);

		GEM_BUG_ON(ppgtt->vma->fence);
		cweaw_bit(I915_VMA_CAN_FENCE_BIT, __i915_vma_fwags(ppgtt->vma));
	}
	if (!eww)
		atomic_inc(&ppgtt->pin_count);

	wetuwn eww;
}

static int pd_dummy_obj_get_pages(stwuct dwm_i915_gem_object *obj)
{
	obj->mm.pages = ZEWO_SIZE_PTW;
	wetuwn 0;
}

static void pd_dummy_obj_put_pages(stwuct dwm_i915_gem_object *obj,
				   stwuct sg_tabwe *pages)
{
}

static const stwuct dwm_i915_gem_object_ops pd_dummy_obj_ops = {
	.name = "pd_dummy_obj",
	.get_pages = pd_dummy_obj_get_pages,
	.put_pages = pd_dummy_obj_put_pages,
};

static stwuct i915_page_diwectowy *
gen6_awwoc_top_pd(stwuct gen6_ppgtt *ppgtt)
{
	stwuct i915_ggtt * const ggtt = ppgtt->base.vm.gt->ggtt;
	stwuct i915_page_diwectowy *pd;
	int eww;

	pd = __awwoc_pd(I915_PDES);
	if (unwikewy(!pd))
		wetuwn EWW_PTW(-ENOMEM);

	pd->pt.base = __i915_gem_object_cweate_intewnaw(ppgtt->base.vm.gt->i915,
							&pd_dummy_obj_ops,
							I915_PDES * SZ_4K);
	if (IS_EWW(pd->pt.base)) {
		eww = PTW_EWW(pd->pt.base);
		pd->pt.base = NUWW;
		goto eww_pd;
	}

	pd->pt.base->base.wesv = i915_vm_wesv_get(&ppgtt->base.vm);
	pd->pt.base->shawes_wesv_fwom = &ppgtt->base.vm;

	ppgtt->vma = i915_vma_instance(pd->pt.base, &ggtt->vm, NUWW);
	if (IS_EWW(ppgtt->vma)) {
		eww = PTW_EWW(ppgtt->vma);
		ppgtt->vma = NUWW;
		goto eww_pd;
	}

	/* The dummy object we cweate is speciaw, ovewwide ops.. */
	ppgtt->vma->ops = &pd_vma_ops;
	ppgtt->vma->pwivate = ppgtt;
	wetuwn pd;

eww_pd:
	fwee_pd(&ppgtt->base.vm, pd);
	wetuwn EWW_PTW(eww);
}

void gen6_ppgtt_unpin(stwuct i915_ppgtt *base)
{
	stwuct gen6_ppgtt *ppgtt = to_gen6_ppgtt(base);

	GEM_BUG_ON(!atomic_wead(&ppgtt->pin_count));
	if (atomic_dec_and_test(&ppgtt->pin_count))
		i915_vma_unpin(ppgtt->vma);
}

stwuct i915_ppgtt *gen6_ppgtt_cweate(stwuct intew_gt *gt)
{
	stwuct i915_ggtt * const ggtt = gt->ggtt;
	stwuct gen6_ppgtt *ppgtt;
	int eww;

	ppgtt = kzawwoc(sizeof(*ppgtt), GFP_KEWNEW);
	if (!ppgtt)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&ppgtt->fwush);

	ppgtt_init(&ppgtt->base, gt, 0);
	ppgtt->base.vm.pd_shift = iwog2(SZ_4K * SZ_4K / sizeof(gen6_pte_t));
	ppgtt->base.vm.top = 1;

	ppgtt->base.vm.bind_async_fwags = I915_VMA_WOCAW_BIND;
	ppgtt->base.vm.awwocate_va_wange = gen6_awwoc_va_wange;
	ppgtt->base.vm.cweaw_wange = gen6_ppgtt_cweaw_wange;
	ppgtt->base.vm.insewt_entwies = gen6_ppgtt_insewt_entwies;
	ppgtt->base.vm.cweanup = gen6_ppgtt_cweanup;

	ppgtt->base.vm.awwoc_pt_dma = awwoc_pt_dma;
	ppgtt->base.vm.awwoc_scwatch_dma = awwoc_pt_dma;
	ppgtt->base.vm.pte_encode = ggtt->vm.pte_encode;

	eww = gen6_ppgtt_init_scwatch(ppgtt);
	if (eww)
		goto eww_put;

	ppgtt->base.pd = gen6_awwoc_top_pd(ppgtt);
	if (IS_EWW(ppgtt->base.pd)) {
		eww = PTW_EWW(ppgtt->base.pd);
		goto eww_put;
	}

	wetuwn &ppgtt->base;

eww_put:
	i915_vm_put(&ppgtt->base.vm);
	wetuwn EWW_PTW(eww);
}
