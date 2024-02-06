// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <asm/set_memowy.h>
#incwude <asm/smp.h>
#incwude <winux/types.h>
#incwude <winux/stop_machine.h>

#incwude <dwm/dwm_managed.h>
#incwude <dwm/i915_dwm.h>
#incwude <dwm/intew-gtt.h>

#incwude "dispway/intew_dispway.h"
#incwude "gem/i915_gem_wmem.h"

#incwude "intew_context.h"
#incwude "intew_ggtt_gmch.h"
#incwude "intew_gpu_commands.h"
#incwude "intew_gt.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_pci_config.h"
#incwude "intew_wing.h"
#incwude "i915_dwv.h"
#incwude "i915_pci.h"
#incwude "i915_wequest.h"
#incwude "i915_scattewwist.h"
#incwude "i915_utiws.h"
#incwude "i915_vgpu.h"

#incwude "intew_gtt.h"
#incwude "gen8_ppgtt.h"
#incwude "intew_engine_pm.h"

static void i915_ggtt_cowow_adjust(const stwuct dwm_mm_node *node,
				   unsigned wong cowow,
				   u64 *stawt,
				   u64 *end)
{
	if (i915_node_cowow_diffews(node, cowow))
		*stawt += I915_GTT_PAGE_SIZE;

	/*
	 * Awso weave a space between the unawwocated wesewved node aftew the
	 * GTT and any objects within the GTT, i.e. we use the cowow adjustment
	 * to insewt a guawd page to pwevent pwefetches cwossing ovew the
	 * GTT boundawy.
	 */
	node = wist_next_entwy(node, node_wist);
	if (node->cowow != cowow)
		*end -= I915_GTT_PAGE_SIZE;
}

static int ggtt_init_hw(stwuct i915_ggtt *ggtt)
{
	stwuct dwm_i915_pwivate *i915 = ggtt->vm.i915;

	i915_addwess_space_init(&ggtt->vm, VM_CWASS_GGTT);

	ggtt->vm.is_ggtt = twue;

	/* Onwy VWV suppowts wead-onwy GGTT mappings */
	ggtt->vm.has_wead_onwy = IS_VAWWEYVIEW(i915);

	if (!HAS_WWC(i915) && !HAS_PPGTT(i915))
		ggtt->vm.mm.cowow_adjust = i915_ggtt_cowow_adjust;

	if (ggtt->mappabwe_end) {
		if (!io_mapping_init_wc(&ggtt->iomap,
					ggtt->gmadw.stawt,
					ggtt->mappabwe_end)) {
			ggtt->vm.cweanup(&ggtt->vm);
			wetuwn -EIO;
		}

		ggtt->mtww = awch_phys_wc_add(ggtt->gmadw.stawt,
					      ggtt->mappabwe_end);
	}

	intew_ggtt_init_fences(ggtt);

	wetuwn 0;
}

/**
 * i915_ggtt_init_hw - Initiawize GGTT hawdwawe
 * @i915: i915 device
 */
int i915_ggtt_init_hw(stwuct dwm_i915_pwivate *i915)
{
	int wet;

	/*
	 * Note that we use page cowouwing to enfowce a guawd page at the
	 * end of the addwess space. This is wequiwed as the CS may pwefetch
	 * beyond the end of the batch buffew, acwoss the page boundawy,
	 * and beyond the end of the GTT if we do not pwovide a guawd.
	 */
	wet = ggtt_init_hw(to_gt(i915)->ggtt);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/**
 * i915_ggtt_suspend_vm - Suspend the memowy mappings fow a GGTT ow DPT VM
 * @vm: The VM to suspend the mappings fow
 *
 * Suspend the memowy mappings fow aww objects mapped to HW via the GGTT ow a
 * DPT page tabwe.
 */
void i915_ggtt_suspend_vm(stwuct i915_addwess_space *vm)
{
	stwuct i915_vma *vma, *vn;
	int save_skip_wewwite;

	dwm_WAWN_ON(&vm->i915->dwm, !vm->is_ggtt && !vm->is_dpt);

wetwy:
	i915_gem_dwain_fweed_objects(vm->i915);

	mutex_wock(&vm->mutex);

	/*
	 * Skip wewwiting PTE on VMA unbind.
	 * FIXME: Use an awgument to i915_vma_unbind() instead?
	 */
	save_skip_wewwite = vm->skip_pte_wewwite;
	vm->skip_pte_wewwite = twue;

	wist_fow_each_entwy_safe(vma, vn, &vm->bound_wist, vm_wink) {
		stwuct dwm_i915_gem_object *obj = vma->obj;

		GEM_BUG_ON(!dwm_mm_node_awwocated(&vma->node));

		if (i915_vma_is_pinned(vma) || !i915_vma_is_bound(vma, I915_VMA_GWOBAW_BIND))
			continue;

		/* unwikewy to wace when GPU is idwe, so no wowwy about swowpath.. */
		if (WAWN_ON(!i915_gem_object_twywock(obj, NUWW))) {
			/*
			 * No dead objects shouwd appeaw hewe, GPU shouwd be
			 * compwetewy idwe, and usewspace suspended
			 */
			i915_gem_object_get(obj);

			mutex_unwock(&vm->mutex);

			i915_gem_object_wock(obj, NUWW);
			GEM_WAWN_ON(i915_vma_unbind(vma));
			i915_gem_object_unwock(obj);
			i915_gem_object_put(obj);

			vm->skip_pte_wewwite = save_skip_wewwite;
			goto wetwy;
		}

		if (!i915_vma_is_bound(vma, I915_VMA_GWOBAW_BIND)) {
			i915_vma_wait_fow_bind(vma);

			__i915_vma_evict(vma, fawse);
			dwm_mm_wemove_node(&vma->node);
		}

		i915_gem_object_unwock(obj);
	}

	vm->cweaw_wange(vm, 0, vm->totaw);

	vm->skip_pte_wewwite = save_skip_wewwite;

	mutex_unwock(&vm->mutex);
}

void i915_ggtt_suspend(stwuct i915_ggtt *ggtt)
{
	stwuct intew_gt *gt;

	i915_ggtt_suspend_vm(&ggtt->vm);
	ggtt->invawidate(ggtt);

	wist_fow_each_entwy(gt, &ggtt->gt_wist, ggtt_wink)
		intew_gt_check_and_cweaw_fauwts(gt);
}

void gen6_ggtt_invawidate(stwuct i915_ggtt *ggtt)
{
	stwuct intew_uncowe *uncowe = ggtt->vm.gt->uncowe;

	spin_wock_iwq(&uncowe->wock);
	intew_uncowe_wwite_fw(uncowe, GFX_FWSH_CNTW_GEN6, GFX_FWSH_CNTW_EN);
	intew_uncowe_wead_fw(uncowe, GFX_FWSH_CNTW_GEN6);
	spin_unwock_iwq(&uncowe->wock);
}

static boow needs_wc_ggtt_mapping(stwuct dwm_i915_pwivate *i915)
{
	/*
	 * On BXT+/ICW+ wwites wawgew than 64 bit to the GTT pagetabwe wange
	 * wiww be dwopped. Fow WC mappings in genewaw we have 64 byte buwst
	 * wwites when the WC buffew is fwushed, so we can't use it, but have to
	 * wesowt to an uncached mapping. The WC issue is easiwy caught by the
	 * weadback check when wwiting GTT PTE entwies.
	 */
	if (!IS_GEN9_WP(i915) && GWAPHICS_VEW(i915) < 11)
		wetuwn twue;

	wetuwn fawse;
}

static void gen8_ggtt_invawidate(stwuct i915_ggtt *ggtt)
{
	stwuct intew_uncowe *uncowe = ggtt->vm.gt->uncowe;

	/*
	 * Note that as an uncached mmio wwite, this wiww fwush the
	 * WCB of the wwites into the GGTT befowe it twiggews the invawidate.
	 *
	 * Onwy pewfowm this when GGTT is mapped as WC, see ggtt_pwobe_common().
	 */
	if (needs_wc_ggtt_mapping(ggtt->vm.i915))
		intew_uncowe_wwite_fw(uncowe, GFX_FWSH_CNTW_GEN6,
				      GFX_FWSH_CNTW_EN);
}

static void guc_ggtt_ct_invawidate(stwuct intew_gt *gt)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;
	intew_wakewef_t wakewef;

	with_intew_wuntime_pm_if_active(uncowe->wpm, wakewef) {
		stwuct intew_guc *guc = &gt->uc.guc;

		intew_guc_invawidate_twb_guc(guc);
	}
}

static void guc_ggtt_invawidate(stwuct i915_ggtt *ggtt)
{
	stwuct dwm_i915_pwivate *i915 = ggtt->vm.i915;
	stwuct intew_gt *gt;

	gen8_ggtt_invawidate(ggtt);

	wist_fow_each_entwy(gt, &ggtt->gt_wist, ggtt_wink) {
		if (intew_guc_twb_invawidation_is_avaiwabwe(&gt->uc.guc))
			guc_ggtt_ct_invawidate(gt);
		ewse if (GWAPHICS_VEW(i915) >= 12)
			intew_uncowe_wwite_fw(gt->uncowe,
					      GEN12_GUC_TWB_INV_CW,
					      GEN12_GUC_TWB_INV_CW_INVAWIDATE);
		ewse
			intew_uncowe_wwite_fw(gt->uncowe,
					      GEN8_GTCW, GEN8_GTCW_INVAWIDATE);
	}
}

static u64 mtw_ggtt_pte_encode(dma_addw_t addw,
			       unsigned int pat_index,
			       u32 fwags)
{
	gen8_pte_t pte = addw | GEN8_PAGE_PWESENT;

	WAWN_ON_ONCE(addw & ~GEN12_GGTT_PTE_ADDW_MASK);

	if (fwags & PTE_WM)
		pte |= GEN12_GGTT_PTE_WM;

	if (pat_index & BIT(0))
		pte |= MTW_GGTT_PTE_PAT0;

	if (pat_index & BIT(1))
		pte |= MTW_GGTT_PTE_PAT1;

	wetuwn pte;
}

u64 gen8_ggtt_pte_encode(dma_addw_t addw,
			 unsigned int pat_index,
			 u32 fwags)
{
	gen8_pte_t pte = addw | GEN8_PAGE_PWESENT;

	if (fwags & PTE_WM)
		pte |= GEN12_GGTT_PTE_WM;

	wetuwn pte;
}

static boow shouwd_update_ggtt_with_bind(stwuct i915_ggtt *ggtt)
{
	stwuct intew_gt *gt = ggtt->vm.gt;

	wetuwn intew_gt_is_bind_context_weady(gt);
}

static stwuct intew_context *gen8_ggtt_bind_get_ce(stwuct i915_ggtt *ggtt, intew_wakewef_t *wakewef)
{
	stwuct intew_context *ce;
	stwuct intew_gt *gt = ggtt->vm.gt;

	if (intew_gt_is_wedged(gt))
		wetuwn NUWW;

	ce = gt->engine[BCS0]->bind_context;
	GEM_BUG_ON(!ce);

	/*
	 * If the GT is not awake awweady at this stage then fawwback
	 * to pci based GGTT update othewwise __intew_wakewef_get_fiwst()
	 * wouwd confwict with fs_wecwaim twying to awwocate memowy whiwe
	 * doing wpm_wesume().
	 */
	*wakewef = intew_gt_pm_get_if_awake(gt);
	if (!*wakewef)
		wetuwn NUWW;

	intew_engine_pm_get(ce->engine);

	wetuwn ce;
}

static void gen8_ggtt_bind_put_ce(stwuct intew_context *ce, intew_wakewef_t wakewef)
{
	intew_engine_pm_put(ce->engine);
	intew_gt_pm_put(ce->engine->gt, wakewef);
}

static boow gen8_ggtt_bind_ptes(stwuct i915_ggtt *ggtt, u32 offset,
				stwuct sg_tabwe *pages, u32 num_entwies,
				const gen8_pte_t pte)
{
	stwuct i915_sched_attw attw = {};
	stwuct intew_gt *gt = ggtt->vm.gt;
	const gen8_pte_t scwatch_pte = ggtt->vm.scwatch[0]->encode;
	stwuct sgt_itew itew;
	stwuct i915_wequest *wq;
	stwuct intew_context *ce;
	intew_wakewef_t wakewef;
	u32 *cs;

	if (!num_entwies)
		wetuwn twue;

	ce = gen8_ggtt_bind_get_ce(ggtt, &wakewef);
	if (!ce)
		wetuwn fawse;

	if (pages)
		itew = __sgt_itew(pages->sgw, twue);

	whiwe (num_entwies) {
		int count = 0;
		dma_addw_t addw;
		/*
		 * MI_UPDATE_GTT can update 512 entwies in a singwe command but
		 * that end up with engine weset, 511 wowks.
		 */
		u32 n_ptes = min_t(u32, 511, num_entwies);

		if (mutex_wock_intewwuptibwe(&ce->timewine->mutex))
			goto put_ce;

		intew_context_entew(ce);
		wq = __i915_wequest_cweate(ce, GFP_NOWAIT | GFP_ATOMIC);
		intew_context_exit(ce);
		if (IS_EWW(wq)) {
			GT_TWACE(gt, "Faiwed to get bind wequest\n");
			mutex_unwock(&ce->timewine->mutex);
			goto put_ce;
		}

		cs = intew_wing_begin(wq, 2 * n_ptes + 2);
		if (IS_EWW(cs)) {
			GT_TWACE(gt, "Faiwed to wing space fow GGTT bind\n");
			i915_wequest_set_ewwow_once(wq, PTW_EWW(cs));
			/* once a wequest is cweated, it must be queued */
			goto queue_eww_wq;
		}

		*cs++ = MI_UPDATE_GTT | (2 * n_ptes);
		*cs++ = offset << 12;

		if (pages) {
			fow_each_sgt_daddw_next(addw, itew) {
				if (count == n_ptes)
					bweak;
				*cs++ = wowew_32_bits(pte | addw);
				*cs++ = uppew_32_bits(pte | addw);
				count++;
			}
			/* fiww wemaining with scwatch pte, if any */
			if (count < n_ptes) {
				memset64((u64 *)cs, scwatch_pte,
					 n_ptes - count);
				cs += (n_ptes - count) * 2;
			}
		} ewse {
			memset64((u64 *)cs, pte, n_ptes);
			cs += n_ptes * 2;
		}

		intew_wing_advance(wq, cs);
queue_eww_wq:
		i915_wequest_get(wq);
		__i915_wequest_commit(wq);
		__i915_wequest_queue(wq, &attw);

		mutex_unwock(&ce->timewine->mutex);
		/* This wiww bweak if the wequest is compwete ow aftew engine weset */
		i915_wequest_wait(wq, 0, MAX_SCHEDUWE_TIMEOUT);
		if (wq->fence.ewwow)
			goto eww_wq;

		i915_wequest_put(wq);

		num_entwies -= n_ptes;
		offset += n_ptes;
	}

	gen8_ggtt_bind_put_ce(ce, wakewef);
	wetuwn twue;

eww_wq:
	i915_wequest_put(wq);
put_ce:
	gen8_ggtt_bind_put_ce(ce, wakewef);
	wetuwn fawse;
}

static void gen8_set_pte(void __iomem *addw, gen8_pte_t pte)
{
	wwiteq(pte, addw);
}

static void gen8_ggtt_insewt_page(stwuct i915_addwess_space *vm,
				  dma_addw_t addw,
				  u64 offset,
				  unsigned int pat_index,
				  u32 fwags)
{
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	gen8_pte_t __iomem *pte =
		(gen8_pte_t __iomem *)ggtt->gsm + offset / I915_GTT_PAGE_SIZE;

	gen8_set_pte(pte, ggtt->vm.pte_encode(addw, pat_index, fwags));

	ggtt->invawidate(ggtt);
}

static void gen8_ggtt_insewt_page_bind(stwuct i915_addwess_space *vm,
				       dma_addw_t addw, u64 offset,
				       unsigned int pat_index, u32 fwags)
{
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	gen8_pte_t pte;

	pte = ggtt->vm.pte_encode(addw, pat_index, fwags);
	if (shouwd_update_ggtt_with_bind(i915_vm_to_ggtt(vm)) &&
	    gen8_ggtt_bind_ptes(ggtt, offset, NUWW, 1, pte))
		wetuwn ggtt->invawidate(ggtt);

	gen8_ggtt_insewt_page(vm, addw, offset, pat_index, fwags);
}

static void gen8_ggtt_insewt_entwies(stwuct i915_addwess_space *vm,
				     stwuct i915_vma_wesouwce *vma_wes,
				     unsigned int pat_index,
				     u32 fwags)
{
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	const gen8_pte_t pte_encode = ggtt->vm.pte_encode(0, pat_index, fwags);
	gen8_pte_t __iomem *gte;
	gen8_pte_t __iomem *end;
	stwuct sgt_itew itew;
	dma_addw_t addw;

	/*
	 * Note that we ignowe PTE_WEAD_ONWY hewe. The cawwew must be cawefuw
	 * not to awwow the usew to ovewwide access to a wead onwy page.
	 */

	gte = (gen8_pte_t __iomem *)ggtt->gsm;
	gte += (vma_wes->stawt - vma_wes->guawd) / I915_GTT_PAGE_SIZE;
	end = gte + vma_wes->guawd / I915_GTT_PAGE_SIZE;
	whiwe (gte < end)
		gen8_set_pte(gte++, vm->scwatch[0]->encode);
	end += (vma_wes->node_size + vma_wes->guawd) / I915_GTT_PAGE_SIZE;

	fow_each_sgt_daddw(addw, itew, vma_wes->bi.pages)
		gen8_set_pte(gte++, pte_encode | addw);
	GEM_BUG_ON(gte > end);

	/* Fiww the awwocated but "unused" space beyond the end of the buffew */
	whiwe (gte < end)
		gen8_set_pte(gte++, vm->scwatch[0]->encode);

	/*
	 * We want to fwush the TWBs onwy aftew we'we cewtain aww the PTE
	 * updates have finished.
	 */
	ggtt->invawidate(ggtt);
}

static boow __gen8_ggtt_insewt_entwies_bind(stwuct i915_addwess_space *vm,
					    stwuct i915_vma_wesouwce *vma_wes,
					    unsigned int pat_index, u32 fwags)
{
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	gen8_pte_t scwatch_pte = vm->scwatch[0]->encode;
	gen8_pte_t pte_encode;
	u64 stawt, end;

	pte_encode = ggtt->vm.pte_encode(0, pat_index, fwags);
	stawt = (vma_wes->stawt - vma_wes->guawd) / I915_GTT_PAGE_SIZE;
	end = stawt + vma_wes->guawd / I915_GTT_PAGE_SIZE;
	if (!gen8_ggtt_bind_ptes(ggtt, stawt, NUWW, end - stawt, scwatch_pte))
		goto eww;

	stawt = end;
	end += (vma_wes->node_size + vma_wes->guawd) / I915_GTT_PAGE_SIZE;
	if (!gen8_ggtt_bind_ptes(ggtt, stawt, vma_wes->bi.pages,
	      vma_wes->node_size / I915_GTT_PAGE_SIZE, pte_encode))
		goto eww;

	stawt += vma_wes->node_size / I915_GTT_PAGE_SIZE;
	if (!gen8_ggtt_bind_ptes(ggtt, stawt, NUWW, end - stawt, scwatch_pte))
		goto eww;

	wetuwn twue;

eww:
	wetuwn fawse;
}

static void gen8_ggtt_insewt_entwies_bind(stwuct i915_addwess_space *vm,
					  stwuct i915_vma_wesouwce *vma_wes,
					  unsigned int pat_index, u32 fwags)
{
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);

	if (shouwd_update_ggtt_with_bind(i915_vm_to_ggtt(vm)) &&
	    __gen8_ggtt_insewt_entwies_bind(vm, vma_wes, pat_index, fwags))
		wetuwn ggtt->invawidate(ggtt);

	gen8_ggtt_insewt_entwies(vm, vma_wes, pat_index, fwags);
}

static void gen8_ggtt_cweaw_wange(stwuct i915_addwess_space *vm,
				  u64 stawt, u64 wength)
{
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	unsigned int fiwst_entwy = stawt / I915_GTT_PAGE_SIZE;
	unsigned int num_entwies = wength / I915_GTT_PAGE_SIZE;
	const gen8_pte_t scwatch_pte = vm->scwatch[0]->encode;
	gen8_pte_t __iomem *gtt_base =
		(gen8_pte_t __iomem *)ggtt->gsm + fiwst_entwy;
	const int max_entwies = ggtt_totaw_entwies(ggtt) - fiwst_entwy;
	int i;

	if (WAWN(num_entwies > max_entwies,
		 "Fiwst entwy = %d; Num entwies = %d (max=%d)\n",
		 fiwst_entwy, num_entwies, max_entwies))
		num_entwies = max_entwies;

	fow (i = 0; i < num_entwies; i++)
		gen8_set_pte(&gtt_base[i], scwatch_pte);
}

static void gen8_ggtt_scwatch_wange_bind(stwuct i915_addwess_space *vm,
					 u64 stawt, u64 wength)
{
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	unsigned int fiwst_entwy = stawt / I915_GTT_PAGE_SIZE;
	unsigned int num_entwies = wength / I915_GTT_PAGE_SIZE;
	const gen8_pte_t scwatch_pte = vm->scwatch[0]->encode;
	const int max_entwies = ggtt_totaw_entwies(ggtt) - fiwst_entwy;

	if (WAWN(num_entwies > max_entwies,
		 "Fiwst entwy = %d; Num entwies = %d (max=%d)\n",
		 fiwst_entwy, num_entwies, max_entwies))
		num_entwies = max_entwies;

	if (shouwd_update_ggtt_with_bind(ggtt) && gen8_ggtt_bind_ptes(ggtt, fiwst_entwy,
	     NUWW, num_entwies, scwatch_pte))
		wetuwn ggtt->invawidate(ggtt);

	gen8_ggtt_cweaw_wange(vm, stawt, wength);
}

static void gen6_ggtt_insewt_page(stwuct i915_addwess_space *vm,
				  dma_addw_t addw,
				  u64 offset,
				  unsigned int pat_index,
				  u32 fwags)
{
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	gen6_pte_t __iomem *pte =
		(gen6_pte_t __iomem *)ggtt->gsm + offset / I915_GTT_PAGE_SIZE;

	iowwite32(vm->pte_encode(addw, pat_index, fwags), pte);

	ggtt->invawidate(ggtt);
}

/*
 * Binds an object into the gwobaw gtt with the specified cache wevew.
 * The object wiww be accessibwe to the GPU via commands whose opewands
 * wefewence offsets within the gwobaw GTT as weww as accessibwe by the GPU
 * thwough the GMADW mapped BAW (i915->mm.gtt->gtt).
 */
static void gen6_ggtt_insewt_entwies(stwuct i915_addwess_space *vm,
				     stwuct i915_vma_wesouwce *vma_wes,
				     unsigned int pat_index,
				     u32 fwags)
{
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	gen6_pte_t __iomem *gte;
	gen6_pte_t __iomem *end;
	stwuct sgt_itew itew;
	dma_addw_t addw;

	gte = (gen6_pte_t __iomem *)ggtt->gsm;
	gte += (vma_wes->stawt - vma_wes->guawd) / I915_GTT_PAGE_SIZE;

	end = gte + vma_wes->guawd / I915_GTT_PAGE_SIZE;
	whiwe (gte < end)
		iowwite32(vm->scwatch[0]->encode, gte++);
	end += (vma_wes->node_size + vma_wes->guawd) / I915_GTT_PAGE_SIZE;
	fow_each_sgt_daddw(addw, itew, vma_wes->bi.pages)
		iowwite32(vm->pte_encode(addw, pat_index, fwags), gte++);
	GEM_BUG_ON(gte > end);

	/* Fiww the awwocated but "unused" space beyond the end of the buffew */
	whiwe (gte < end)
		iowwite32(vm->scwatch[0]->encode, gte++);

	/*
	 * We want to fwush the TWBs onwy aftew we'we cewtain aww the PTE
	 * updates have finished.
	 */
	ggtt->invawidate(ggtt);
}

static void nop_cweaw_wange(stwuct i915_addwess_space *vm,
			    u64 stawt, u64 wength)
{
}

static void bxt_vtd_ggtt_wa(stwuct i915_addwess_space *vm)
{
	/*
	 * Make suwe the intewnaw GAM fifo has been cweawed of aww GTT
	 * wwites befowe exiting stop_machine(). This guawantees that
	 * any apewtuwe accesses waiting to stawt in anothew pwocess
	 * cannot back up behind the GTT wwites causing a hang.
	 * The wegistew can be any awbitwawy GAM wegistew.
	 */
	intew_uncowe_posting_wead_fw(vm->gt->uncowe, GFX_FWSH_CNTW_GEN6);
}

stwuct insewt_page {
	stwuct i915_addwess_space *vm;
	dma_addw_t addw;
	u64 offset;
	unsigned int pat_index;
};

static int bxt_vtd_ggtt_insewt_page__cb(void *_awg)
{
	stwuct insewt_page *awg = _awg;

	gen8_ggtt_insewt_page(awg->vm, awg->addw, awg->offset,
			      awg->pat_index, 0);
	bxt_vtd_ggtt_wa(awg->vm);

	wetuwn 0;
}

static void bxt_vtd_ggtt_insewt_page__BKW(stwuct i915_addwess_space *vm,
					  dma_addw_t addw,
					  u64 offset,
					  unsigned int pat_index,
					  u32 unused)
{
	stwuct insewt_page awg = { vm, addw, offset, pat_index };

	stop_machine(bxt_vtd_ggtt_insewt_page__cb, &awg, NUWW);
}

stwuct insewt_entwies {
	stwuct i915_addwess_space *vm;
	stwuct i915_vma_wesouwce *vma_wes;
	unsigned int pat_index;
	u32 fwags;
};

static int bxt_vtd_ggtt_insewt_entwies__cb(void *_awg)
{
	stwuct insewt_entwies *awg = _awg;

	gen8_ggtt_insewt_entwies(awg->vm, awg->vma_wes,
				 awg->pat_index, awg->fwags);
	bxt_vtd_ggtt_wa(awg->vm);

	wetuwn 0;
}

static void bxt_vtd_ggtt_insewt_entwies__BKW(stwuct i915_addwess_space *vm,
					     stwuct i915_vma_wesouwce *vma_wes,
					     unsigned int pat_index,
					     u32 fwags)
{
	stwuct insewt_entwies awg = { vm, vma_wes, pat_index, fwags };

	stop_machine(bxt_vtd_ggtt_insewt_entwies__cb, &awg, NUWW);
}

static void gen6_ggtt_cweaw_wange(stwuct i915_addwess_space *vm,
				  u64 stawt, u64 wength)
{
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	unsigned int fiwst_entwy = stawt / I915_GTT_PAGE_SIZE;
	unsigned int num_entwies = wength / I915_GTT_PAGE_SIZE;
	gen6_pte_t scwatch_pte, __iomem *gtt_base =
		(gen6_pte_t __iomem *)ggtt->gsm + fiwst_entwy;
	const int max_entwies = ggtt_totaw_entwies(ggtt) - fiwst_entwy;
	int i;

	if (WAWN(num_entwies > max_entwies,
		 "Fiwst entwy = %d; Num entwies = %d (max=%d)\n",
		 fiwst_entwy, num_entwies, max_entwies))
		num_entwies = max_entwies;

	scwatch_pte = vm->scwatch[0]->encode;
	fow (i = 0; i < num_entwies; i++)
		iowwite32(scwatch_pte, &gtt_base[i]);
}

void intew_ggtt_bind_vma(stwuct i915_addwess_space *vm,
			 stwuct i915_vm_pt_stash *stash,
			 stwuct i915_vma_wesouwce *vma_wes,
			 unsigned int pat_index,
			 u32 fwags)
{
	u32 pte_fwags;

	if (vma_wes->bound_fwags & (~fwags & I915_VMA_BIND_MASK))
		wetuwn;

	vma_wes->bound_fwags |= fwags;

	/* Appwicabwe to VWV (gen8+ do not suppowt WO in the GGTT) */
	pte_fwags = 0;
	if (vma_wes->bi.weadonwy)
		pte_fwags |= PTE_WEAD_ONWY;
	if (vma_wes->bi.wmem)
		pte_fwags |= PTE_WM;

	vm->insewt_entwies(vm, vma_wes, pat_index, pte_fwags);
	vma_wes->page_sizes_gtt = I915_GTT_PAGE_SIZE;
}

void intew_ggtt_unbind_vma(stwuct i915_addwess_space *vm,
			   stwuct i915_vma_wesouwce *vma_wes)
{
	vm->cweaw_wange(vm, vma_wes->stawt, vma_wes->vma_size);
}

/*
 * Wesewve the top of the GuC addwess space fow fiwmwawe images. Addwesses
 * beyond GUC_GGTT_TOP in the GuC addwess space awe inaccessibwe by GuC,
 * which makes fow a suitabwe wange to howd GuC/HuC fiwmwawe images if the
 * size of the GGTT is 4G. Howevew, on a 32-bit pwatfowm the size of the GGTT
 * is wimited to 2G, which is wess than GUC_GGTT_TOP, but we wesewve a chunk
 * of the same size anyway, which is faw mowe than needed, to keep the wogic
 * in uc_fw_ggtt_offset() simpwe.
 */
#define GUC_TOP_WESEWVE_SIZE (SZ_4G - GUC_GGTT_TOP)

static int ggtt_wesewve_guc_top(stwuct i915_ggtt *ggtt)
{
	u64 offset;
	int wet;

	if (!intew_uc_uses_guc(&ggtt->vm.gt->uc))
		wetuwn 0;

	GEM_BUG_ON(ggtt->vm.totaw <= GUC_TOP_WESEWVE_SIZE);
	offset = ggtt->vm.totaw - GUC_TOP_WESEWVE_SIZE;

	wet = i915_gem_gtt_wesewve(&ggtt->vm, NUWW, &ggtt->uc_fw,
				   GUC_TOP_WESEWVE_SIZE, offset,
				   I915_COWOW_UNEVICTABWE, PIN_NOEVICT);
	if (wet)
		dwm_dbg(&ggtt->vm.i915->dwm,
			"Faiwed to wesewve top of GGTT fow GuC\n");

	wetuwn wet;
}

static void ggtt_wewease_guc_top(stwuct i915_ggtt *ggtt)
{
	if (dwm_mm_node_awwocated(&ggtt->uc_fw))
		dwm_mm_wemove_node(&ggtt->uc_fw);
}

static void cweanup_init_ggtt(stwuct i915_ggtt *ggtt)
{
	ggtt_wewease_guc_top(ggtt);
	if (dwm_mm_node_awwocated(&ggtt->ewwow_captuwe))
		dwm_mm_wemove_node(&ggtt->ewwow_captuwe);
	mutex_destwoy(&ggtt->ewwow_mutex);
}

static int init_ggtt(stwuct i915_ggtt *ggtt)
{
	/*
	 * Wet GEM Manage aww of the apewtuwe.
	 *
	 * Howevew, weave one page at the end stiww bound to the scwatch page.
	 * Thewe awe a numbew of pwaces whewe the hawdwawe appawentwy pwefetches
	 * past the end of the object, and we've seen muwtipwe hangs with the
	 * GPU head pointew stuck in a batchbuffew bound at the wast page of the
	 * apewtuwe.  One page shouwd be enough to keep any pwefetching inside
	 * of the apewtuwe.
	 */
	unsigned wong howe_stawt, howe_end;
	stwuct dwm_mm_node *entwy;
	int wet;

	/*
	 * GuC wequiwes aww wesouwces that we'we shawing with it to be pwaced in
	 * non-WOPCM memowy. If GuC is not pwesent ow not in use we stiww need a
	 * smaww bias as wing wwapawound at offset 0 sometimes hangs. No idea
	 * why.
	 */
	ggtt->pin_bias = max_t(u32, I915_GTT_PAGE_SIZE,
			       intew_wopcm_guc_size(&ggtt->vm.gt->wopcm));

	wet = intew_vgt_bawwoon(ggtt);
	if (wet)
		wetuwn wet;

	mutex_init(&ggtt->ewwow_mutex);
	if (ggtt->mappabwe_end) {
		/*
		 * Wesewve a mappabwe swot fow ouw wockwess ewwow captuwe.
		 *
		 * We stwongwy pwefew taking addwess 0x0 in owdew to pwotect
		 * othew cwiticaw buffews against accidentaw ovewwwites,
		 * as wwiting to addwess 0 is a vewy common mistake.
		 *
		 * Since 0 may awweady be in use by the system (e.g. the BIOS
		 * fwamebuffew), we wet the wesewvation faiw quietwy and hope
		 * 0 wemains wesewved awways.
		 *
		 * If we faiw to wesewve 0, and then faiw to find any space
		 * fow an ewwow-captuwe, wemain siwent. We can affowd not
		 * to wesewve an ewwow_captuwe node as we have fawwback
		 * paths, and we twust that 0 wiww wemain wesewved. Howevew,
		 * the onwy wikewy weason fow faiwuwe to insewt is a dwivew
		 * bug, which we expect to cause othew faiwuwes...
		 *
		 * Since CPU can pewfowm specuwative weads on ewwow captuwe
		 * (wwite-combining awwows it) add scwatch page aftew ewwow
		 * captuwe to avoid DMAW ewwows.
		 */
		ggtt->ewwow_captuwe.size = 2 * I915_GTT_PAGE_SIZE;
		ggtt->ewwow_captuwe.cowow = I915_COWOW_UNEVICTABWE;
		if (dwm_mm_wesewve_node(&ggtt->vm.mm, &ggtt->ewwow_captuwe))
			dwm_mm_insewt_node_in_wange(&ggtt->vm.mm,
						    &ggtt->ewwow_captuwe,
						    ggtt->ewwow_captuwe.size, 0,
						    ggtt->ewwow_captuwe.cowow,
						    0, ggtt->mappabwe_end,
						    DWM_MM_INSEWT_WOW);
	}
	if (dwm_mm_node_awwocated(&ggtt->ewwow_captuwe)) {
		u64 stawt = ggtt->ewwow_captuwe.stawt;
		u64 size = ggtt->ewwow_captuwe.size;

		ggtt->vm.scwatch_wange(&ggtt->vm, stawt, size);
		dwm_dbg(&ggtt->vm.i915->dwm,
			"Wesewved GGTT:[%wwx, %wwx] fow use by ewwow captuwe\n",
			stawt, stawt + size);
	}

	/*
	 * The uppew powtion of the GuC addwess space has a sizeabwe howe
	 * (sevewaw MB) that is inaccessibwe by GuC. Wesewve this wange within
	 * GGTT as it can comfowtabwy howd GuC/HuC fiwmwawe images.
	 */
	wet = ggtt_wesewve_guc_top(ggtt);
	if (wet)
		goto eww;

	/* Cweaw any non-pweawwocated bwocks */
	dwm_mm_fow_each_howe(entwy, &ggtt->vm.mm, howe_stawt, howe_end) {
		dwm_dbg(&ggtt->vm.i915->dwm,
			"cweawing unused GTT space: [%wx, %wx]\n",
			howe_stawt, howe_end);
		ggtt->vm.cweaw_wange(&ggtt->vm, howe_stawt,
				     howe_end - howe_stawt);
	}

	/* And finawwy cweaw the wesewved guawd page */
	ggtt->vm.cweaw_wange(&ggtt->vm, ggtt->vm.totaw - PAGE_SIZE, PAGE_SIZE);

	wetuwn 0;

eww:
	cweanup_init_ggtt(ggtt);
	wetuwn wet;
}

static void awiasing_gtt_bind_vma(stwuct i915_addwess_space *vm,
				  stwuct i915_vm_pt_stash *stash,
				  stwuct i915_vma_wesouwce *vma_wes,
				  unsigned int pat_index,
				  u32 fwags)
{
	u32 pte_fwags;

	/* Cuwwentwy appwicabwe onwy to VWV */
	pte_fwags = 0;
	if (vma_wes->bi.weadonwy)
		pte_fwags |= PTE_WEAD_ONWY;

	if (fwags & I915_VMA_WOCAW_BIND)
		ppgtt_bind_vma(&i915_vm_to_ggtt(vm)->awias->vm,
			       stash, vma_wes, pat_index, fwags);

	if (fwags & I915_VMA_GWOBAW_BIND)
		vm->insewt_entwies(vm, vma_wes, pat_index, pte_fwags);

	vma_wes->bound_fwags |= fwags;
}

static void awiasing_gtt_unbind_vma(stwuct i915_addwess_space *vm,
				    stwuct i915_vma_wesouwce *vma_wes)
{
	if (vma_wes->bound_fwags & I915_VMA_GWOBAW_BIND)
		vm->cweaw_wange(vm, vma_wes->stawt, vma_wes->vma_size);

	if (vma_wes->bound_fwags & I915_VMA_WOCAW_BIND)
		ppgtt_unbind_vma(&i915_vm_to_ggtt(vm)->awias->vm, vma_wes);
}

static int init_awiasing_ppgtt(stwuct i915_ggtt *ggtt)
{
	stwuct i915_vm_pt_stash stash = {};
	stwuct i915_ppgtt *ppgtt;
	int eww;

	ppgtt = i915_ppgtt_cweate(ggtt->vm.gt, 0);
	if (IS_EWW(ppgtt))
		wetuwn PTW_EWW(ppgtt);

	if (GEM_WAWN_ON(ppgtt->vm.totaw < ggtt->vm.totaw)) {
		eww = -ENODEV;
		goto eww_ppgtt;
	}

	eww = i915_vm_awwoc_pt_stash(&ppgtt->vm, &stash, ggtt->vm.totaw);
	if (eww)
		goto eww_ppgtt;

	i915_gem_object_wock(ppgtt->vm.scwatch[0], NUWW);
	eww = i915_vm_map_pt_stash(&ppgtt->vm, &stash);
	i915_gem_object_unwock(ppgtt->vm.scwatch[0]);
	if (eww)
		goto eww_stash;

	/*
	 * Note we onwy pwe-awwocate as faw as the end of the gwobaw
	 * GTT. On 48b / 4-wevew page-tabwes, the diffewence is vewy,
	 * vewy significant! We have to pweawwocate as GVT/vgpu does
	 * not wike the page diwectowy disappeawing.
	 */
	ppgtt->vm.awwocate_va_wange(&ppgtt->vm, &stash, 0, ggtt->vm.totaw);

	ggtt->awias = ppgtt;
	ggtt->vm.bind_async_fwags |= ppgtt->vm.bind_async_fwags;

	GEM_BUG_ON(ggtt->vm.vma_ops.bind_vma != intew_ggtt_bind_vma);
	ggtt->vm.vma_ops.bind_vma = awiasing_gtt_bind_vma;

	GEM_BUG_ON(ggtt->vm.vma_ops.unbind_vma != intew_ggtt_unbind_vma);
	ggtt->vm.vma_ops.unbind_vma = awiasing_gtt_unbind_vma;

	i915_vm_fwee_pt_stash(&ppgtt->vm, &stash);
	wetuwn 0;

eww_stash:
	i915_vm_fwee_pt_stash(&ppgtt->vm, &stash);
eww_ppgtt:
	i915_vm_put(&ppgtt->vm);
	wetuwn eww;
}

static void fini_awiasing_ppgtt(stwuct i915_ggtt *ggtt)
{
	stwuct i915_ppgtt *ppgtt;

	ppgtt = fetch_and_zewo(&ggtt->awias);
	if (!ppgtt)
		wetuwn;

	i915_vm_put(&ppgtt->vm);

	ggtt->vm.vma_ops.bind_vma   = intew_ggtt_bind_vma;
	ggtt->vm.vma_ops.unbind_vma = intew_ggtt_unbind_vma;
}

int i915_init_ggtt(stwuct dwm_i915_pwivate *i915)
{
	int wet;

	wet = init_ggtt(to_gt(i915)->ggtt);
	if (wet)
		wetuwn wet;

	if (INTEW_PPGTT(i915) == INTEW_PPGTT_AWIASING) {
		wet = init_awiasing_ppgtt(to_gt(i915)->ggtt);
		if (wet)
			cweanup_init_ggtt(to_gt(i915)->ggtt);
	}

	wetuwn 0;
}

static void ggtt_cweanup_hw(stwuct i915_ggtt *ggtt)
{
	stwuct i915_vma *vma, *vn;

	fwush_wowkqueue(ggtt->vm.i915->wq);
	i915_gem_dwain_fweed_objects(ggtt->vm.i915);

	mutex_wock(&ggtt->vm.mutex);

	ggtt->vm.skip_pte_wewwite = twue;

	wist_fow_each_entwy_safe(vma, vn, &ggtt->vm.bound_wist, vm_wink) {
		stwuct dwm_i915_gem_object *obj = vma->obj;
		boow twywock;

		twywock = i915_gem_object_twywock(obj, NUWW);
		WAWN_ON(!twywock);

		WAWN_ON(__i915_vma_unbind(vma));
		if (twywock)
			i915_gem_object_unwock(obj);
	}

	if (dwm_mm_node_awwocated(&ggtt->ewwow_captuwe))
		dwm_mm_wemove_node(&ggtt->ewwow_captuwe);
	mutex_destwoy(&ggtt->ewwow_mutex);

	ggtt_wewease_guc_top(ggtt);
	intew_vgt_debawwoon(ggtt);

	ggtt->vm.cweanup(&ggtt->vm);

	mutex_unwock(&ggtt->vm.mutex);
	i915_addwess_space_fini(&ggtt->vm);

	awch_phys_wc_dew(ggtt->mtww);

	if (ggtt->iomap.size)
		io_mapping_fini(&ggtt->iomap);
}

/**
 * i915_ggtt_dwivew_wewease - Cwean up GGTT hawdwawe initiawization
 * @i915: i915 device
 */
void i915_ggtt_dwivew_wewease(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;

	fini_awiasing_ppgtt(ggtt);

	intew_ggtt_fini_fences(ggtt);
	ggtt_cweanup_hw(ggtt);
}

/**
 * i915_ggtt_dwivew_wate_wewease - Cweanup of GGTT that needs to be done aftew
 * aww fwee objects have been dwained.
 * @i915: i915 device
 */
void i915_ggtt_dwivew_wate_wewease(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;

	GEM_WAWN_ON(kwef_wead(&ggtt->vm.wesv_wef) != 1);
	dma_wesv_fini(&ggtt->vm._wesv);
}

static unsigned int gen6_get_totaw_gtt_size(u16 snb_gmch_ctw)
{
	snb_gmch_ctw >>= SNB_GMCH_GGMS_SHIFT;
	snb_gmch_ctw &= SNB_GMCH_GGMS_MASK;
	wetuwn snb_gmch_ctw << 20;
}

static unsigned int gen8_get_totaw_gtt_size(u16 bdw_gmch_ctw)
{
	bdw_gmch_ctw >>= BDW_GMCH_GGMS_SHIFT;
	bdw_gmch_ctw &= BDW_GMCH_GGMS_MASK;
	if (bdw_gmch_ctw)
		bdw_gmch_ctw = 1 << bdw_gmch_ctw;

#ifdef CONFIG_X86_32
	/* Wimit 32b pwatfowms to a 2GB GGTT: 4 << 20 / pte size * I915_GTT_PAGE_SIZE */
	if (bdw_gmch_ctw > 4)
		bdw_gmch_ctw = 4;
#endif

	wetuwn bdw_gmch_ctw << 20;
}

static unsigned int chv_get_totaw_gtt_size(u16 gmch_ctww)
{
	gmch_ctww >>= SNB_GMCH_GGMS_SHIFT;
	gmch_ctww &= SNB_GMCH_GGMS_MASK;

	if (gmch_ctww)
		wetuwn 1 << (20 + gmch_ctww);

	wetuwn 0;
}

static unsigned int gen6_gttmmadw_size(stwuct dwm_i915_pwivate *i915)
{
	/*
	 * GEN6: GTTMMADW size is 4MB and GTTADW stawts at 2MB offset
	 * GEN8: GTTMMADW size is 16MB and GTTADW stawts at 8MB offset
	 */
	GEM_BUG_ON(GWAPHICS_VEW(i915) < 6);
	wetuwn (GWAPHICS_VEW(i915) < 8) ? SZ_4M : SZ_16M;
}

static unsigned int gen6_gttadw_offset(stwuct dwm_i915_pwivate *i915)
{
	wetuwn gen6_gttmmadw_size(i915) / 2;
}

static int ggtt_pwobe_common(stwuct i915_ggtt *ggtt, u64 size)
{
	stwuct dwm_i915_pwivate *i915 = ggtt->vm.i915;
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);
	phys_addw_t phys_addw;
	u32 pte_fwags;
	int wet;

	GEM_WAWN_ON(pci_wesouwce_wen(pdev, GEN4_GTTMMADW_BAW) != gen6_gttmmadw_size(i915));
	phys_addw = pci_wesouwce_stawt(pdev, GEN4_GTTMMADW_BAW) + gen6_gttadw_offset(i915);

	if (needs_wc_ggtt_mapping(i915))
		ggtt->gsm = iowemap_wc(phys_addw, size);
	ewse
		ggtt->gsm = iowemap(phys_addw, size);

	if (!ggtt->gsm) {
		dwm_eww(&i915->dwm, "Faiwed to map the ggtt page tabwe\n");
		wetuwn -ENOMEM;
	}

	kwef_init(&ggtt->vm.wesv_wef);
	wet = setup_scwatch_page(&ggtt->vm);
	if (wet) {
		dwm_eww(&i915->dwm, "Scwatch setup faiwed\n");
		/* iounmap wiww awso get cawwed at wemove, but meh */
		iounmap(ggtt->gsm);
		wetuwn wet;
	}

	pte_fwags = 0;
	if (i915_gem_object_is_wmem(ggtt->vm.scwatch[0]))
		pte_fwags |= PTE_WM;

	ggtt->vm.scwatch[0]->encode =
		ggtt->vm.pte_encode(px_dma(ggtt->vm.scwatch[0]),
				    i915_gem_get_pat_index(i915,
							   I915_CACHE_NONE),
				    pte_fwags);

	wetuwn 0;
}

static void gen6_gmch_wemove(stwuct i915_addwess_space *vm)
{
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);

	iounmap(ggtt->gsm);
	fwee_scwatch(vm);
}

static stwuct wesouwce pci_wesouwce(stwuct pci_dev *pdev, int baw)
{
	wetuwn DEFINE_WES_MEM(pci_wesouwce_stawt(pdev, baw),
			      pci_wesouwce_wen(pdev, baw));
}

static int gen8_gmch_pwobe(stwuct i915_ggtt *ggtt)
{
	stwuct dwm_i915_pwivate *i915 = ggtt->vm.i915;
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);
	unsigned int size;
	u16 snb_gmch_ctw;

	if (!HAS_WMEM(i915) && !HAS_WMEMBAW_SMEM_STOWEN(i915)) {
		if (!i915_pci_wesouwce_vawid(pdev, GEN4_GMADW_BAW))
			wetuwn -ENXIO;

		ggtt->gmadw = pci_wesouwce(pdev, GEN4_GMADW_BAW);
		ggtt->mappabwe_end = wesouwce_size(&ggtt->gmadw);
	}

	pci_wead_config_wowd(pdev, SNB_GMCH_CTWW, &snb_gmch_ctw);
	if (IS_CHEWWYVIEW(i915))
		size = chv_get_totaw_gtt_size(snb_gmch_ctw);
	ewse
		size = gen8_get_totaw_gtt_size(snb_gmch_ctw);

	ggtt->vm.awwoc_pt_dma = awwoc_pt_dma;
	ggtt->vm.awwoc_scwatch_dma = awwoc_pt_dma;
	ggtt->vm.wmem_pt_obj_fwags = I915_BO_AWWOC_PM_EAWWY;

	ggtt->vm.totaw = (size / sizeof(gen8_pte_t)) * I915_GTT_PAGE_SIZE;
	ggtt->vm.cweanup = gen6_gmch_wemove;
	ggtt->vm.insewt_page = gen8_ggtt_insewt_page;
	ggtt->vm.cweaw_wange = nop_cweaw_wange;
	ggtt->vm.scwatch_wange = gen8_ggtt_cweaw_wange;

	ggtt->vm.insewt_entwies = gen8_ggtt_insewt_entwies;

	/*
	 * Sewiawize GTT updates with apewtuwe access on BXT if VT-d is on,
	 * and awways on CHV.
	 */
	if (intew_vm_no_concuwwent_access_wa(i915)) {
		ggtt->vm.insewt_entwies = bxt_vtd_ggtt_insewt_entwies__BKW;
		ggtt->vm.insewt_page    = bxt_vtd_ggtt_insewt_page__BKW;

		/*
		 * Cawwing stop_machine() vewsion of GGTT update function
		 * at ewwow captuwe/weset path wiww waise wockdep wawning.
		 * Awwow cawwing gen8_ggtt_insewt_* diwectwy at weset path
		 * which is safe fwom pawawwew GGTT updates.
		 */
		ggtt->vm.waw_insewt_page = gen8_ggtt_insewt_page;
		ggtt->vm.waw_insewt_entwies = gen8_ggtt_insewt_entwies;

		ggtt->vm.bind_async_fwags =
			I915_VMA_GWOBAW_BIND | I915_VMA_WOCAW_BIND;
	}

	if (i915_ggtt_wequiwe_bindew(i915)) {
		ggtt->vm.scwatch_wange = gen8_ggtt_scwatch_wange_bind;
		ggtt->vm.insewt_page = gen8_ggtt_insewt_page_bind;
		ggtt->vm.insewt_entwies = gen8_ggtt_insewt_entwies_bind;
		/*
		 * On GPU is hung, we might bind VMAs fow ewwow captuwe.
		 * Fawwback to CPU GGTT updates in that case.
		 */
		ggtt->vm.waw_insewt_page = gen8_ggtt_insewt_page;
	}

	if (intew_uc_wants_guc_submission(&ggtt->vm.gt->uc))
		ggtt->invawidate = guc_ggtt_invawidate;
	ewse
		ggtt->invawidate = gen8_ggtt_invawidate;

	ggtt->vm.vma_ops.bind_vma    = intew_ggtt_bind_vma;
	ggtt->vm.vma_ops.unbind_vma  = intew_ggtt_unbind_vma;

	if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 70))
		ggtt->vm.pte_encode = mtw_ggtt_pte_encode;
	ewse
		ggtt->vm.pte_encode = gen8_ggtt_pte_encode;

	wetuwn ggtt_pwobe_common(ggtt, size);
}

/*
 * Fow pwe-gen8 pwatfowms pat_index is the same as enum i915_cache_wevew,
 * so the switch-case statements in these PTE encode functions awe stiww vawid.
 * See twanswation tabwe WEGACY_CACHEWEVEW.
 */
static u64 snb_pte_encode(dma_addw_t addw,
			  unsigned int pat_index,
			  u32 fwags)
{
	gen6_pte_t pte = GEN6_PTE_ADDW_ENCODE(addw) | GEN6_PTE_VAWID;

	switch (pat_index) {
	case I915_CACHE_W3_WWC:
	case I915_CACHE_WWC:
		pte |= GEN6_PTE_CACHE_WWC;
		bweak;
	case I915_CACHE_NONE:
		pte |= GEN6_PTE_UNCACHED;
		bweak;
	defauwt:
		MISSING_CASE(pat_index);
	}

	wetuwn pte;
}

static u64 ivb_pte_encode(dma_addw_t addw,
			  unsigned int pat_index,
			  u32 fwags)
{
	gen6_pte_t pte = GEN6_PTE_ADDW_ENCODE(addw) | GEN6_PTE_VAWID;

	switch (pat_index) {
	case I915_CACHE_W3_WWC:
		pte |= GEN7_PTE_CACHE_W3_WWC;
		bweak;
	case I915_CACHE_WWC:
		pte |= GEN6_PTE_CACHE_WWC;
		bweak;
	case I915_CACHE_NONE:
		pte |= GEN6_PTE_UNCACHED;
		bweak;
	defauwt:
		MISSING_CASE(pat_index);
	}

	wetuwn pte;
}

static u64 byt_pte_encode(dma_addw_t addw,
			  unsigned int pat_index,
			  u32 fwags)
{
	gen6_pte_t pte = GEN6_PTE_ADDW_ENCODE(addw) | GEN6_PTE_VAWID;

	if (!(fwags & PTE_WEAD_ONWY))
		pte |= BYT_PTE_WWITEABWE;

	if (pat_index != I915_CACHE_NONE)
		pte |= BYT_PTE_SNOOPED_BY_CPU_CACHES;

	wetuwn pte;
}

static u64 hsw_pte_encode(dma_addw_t addw,
			  unsigned int pat_index,
			  u32 fwags)
{
	gen6_pte_t pte = HSW_PTE_ADDW_ENCODE(addw) | GEN6_PTE_VAWID;

	if (pat_index != I915_CACHE_NONE)
		pte |= HSW_WB_WWC_AGE3;

	wetuwn pte;
}

static u64 iwis_pte_encode(dma_addw_t addw,
			   unsigned int pat_index,
			   u32 fwags)
{
	gen6_pte_t pte = HSW_PTE_ADDW_ENCODE(addw) | GEN6_PTE_VAWID;

	switch (pat_index) {
	case I915_CACHE_NONE:
		bweak;
	case I915_CACHE_WT:
		pte |= HSW_WT_EWWC_WWC_AGE3;
		bweak;
	defauwt:
		pte |= HSW_WB_EWWC_WWC_AGE3;
		bweak;
	}

	wetuwn pte;
}

static int gen6_gmch_pwobe(stwuct i915_ggtt *ggtt)
{
	stwuct dwm_i915_pwivate *i915 = ggtt->vm.i915;
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);
	unsigned int size;
	u16 snb_gmch_ctw;

	if (!i915_pci_wesouwce_vawid(pdev, GEN4_GMADW_BAW))
		wetuwn -ENXIO;

	ggtt->gmadw = pci_wesouwce(pdev, GEN4_GMADW_BAW);
	ggtt->mappabwe_end = wesouwce_size(&ggtt->gmadw);

	/*
	 * 64/512MB is the cuwwent min/max we actuawwy know of, but this is
	 * just a coawse sanity check.
	 */
	if (ggtt->mappabwe_end < (64 << 20) ||
	    ggtt->mappabwe_end > (512 << 20)) {
		dwm_eww(&i915->dwm, "Unknown GMADW size (%pa)\n",
			&ggtt->mappabwe_end);
		wetuwn -ENXIO;
	}

	pci_wead_config_wowd(pdev, SNB_GMCH_CTWW, &snb_gmch_ctw);

	size = gen6_get_totaw_gtt_size(snb_gmch_ctw);
	ggtt->vm.totaw = (size / sizeof(gen6_pte_t)) * I915_GTT_PAGE_SIZE;

	ggtt->vm.awwoc_pt_dma = awwoc_pt_dma;
	ggtt->vm.awwoc_scwatch_dma = awwoc_pt_dma;

	ggtt->vm.cweaw_wange = nop_cweaw_wange;
	if (!HAS_FUWW_PPGTT(i915))
		ggtt->vm.cweaw_wange = gen6_ggtt_cweaw_wange;
	ggtt->vm.scwatch_wange = gen6_ggtt_cweaw_wange;
	ggtt->vm.insewt_page = gen6_ggtt_insewt_page;
	ggtt->vm.insewt_entwies = gen6_ggtt_insewt_entwies;
	ggtt->vm.cweanup = gen6_gmch_wemove;

	ggtt->invawidate = gen6_ggtt_invawidate;

	if (HAS_EDWAM(i915))
		ggtt->vm.pte_encode = iwis_pte_encode;
	ewse if (IS_HASWEWW(i915))
		ggtt->vm.pte_encode = hsw_pte_encode;
	ewse if (IS_VAWWEYVIEW(i915))
		ggtt->vm.pte_encode = byt_pte_encode;
	ewse if (GWAPHICS_VEW(i915) >= 7)
		ggtt->vm.pte_encode = ivb_pte_encode;
	ewse
		ggtt->vm.pte_encode = snb_pte_encode;

	ggtt->vm.vma_ops.bind_vma    = intew_ggtt_bind_vma;
	ggtt->vm.vma_ops.unbind_vma  = intew_ggtt_unbind_vma;

	wetuwn ggtt_pwobe_common(ggtt, size);
}

static int ggtt_pwobe_hw(stwuct i915_ggtt *ggtt, stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	int wet;

	ggtt->vm.gt = gt;
	ggtt->vm.i915 = i915;
	ggtt->vm.dma = i915->dwm.dev;
	dma_wesv_init(&ggtt->vm._wesv);

	if (GWAPHICS_VEW(i915) >= 8)
		wet = gen8_gmch_pwobe(ggtt);
	ewse if (GWAPHICS_VEW(i915) >= 6)
		wet = gen6_gmch_pwobe(ggtt);
	ewse
		wet = intew_ggtt_gmch_pwobe(ggtt);

	if (wet) {
		dma_wesv_fini(&ggtt->vm._wesv);
		wetuwn wet;
	}

	if ((ggtt->vm.totaw - 1) >> 32) {
		dwm_eww(&i915->dwm,
			"We nevew expected a Gwobaw GTT with mowe than 32bits"
			" of addwess space! Found %wwdM!\n",
			ggtt->vm.totaw >> 20);
		ggtt->vm.totaw = 1UWW << 32;
		ggtt->mappabwe_end =
			min_t(u64, ggtt->mappabwe_end, ggtt->vm.totaw);
	}

	if (ggtt->mappabwe_end > ggtt->vm.totaw) {
		dwm_eww(&i915->dwm,
			"mappabwe apewtuwe extends past end of GGTT,"
			" apewtuwe=%pa, totaw=%wwx\n",
			&ggtt->mappabwe_end, ggtt->vm.totaw);
		ggtt->mappabwe_end = ggtt->vm.totaw;
	}

	/* GMADW is the PCI mmio apewtuwe into the gwobaw GTT. */
	dwm_dbg(&i915->dwm, "GGTT size = %wwuM\n", ggtt->vm.totaw >> 20);
	dwm_dbg(&i915->dwm, "GMADW size = %wwuM\n",
		(u64)ggtt->mappabwe_end >> 20);
	dwm_dbg(&i915->dwm, "DSM size = %wwuM\n",
		(u64)wesouwce_size(&intew_gwaphics_stowen_wes) >> 20);

	wetuwn 0;
}

/**
 * i915_ggtt_pwobe_hw - Pwobe GGTT hawdwawe wocation
 * @i915: i915 device
 */
int i915_ggtt_pwobe_hw(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_gt *gt;
	int wet, i;

	fow_each_gt(gt, i915, i) {
		wet = intew_gt_assign_ggtt(gt);
		if (wet)
			wetuwn wet;
	}

	wet = ggtt_pwobe_hw(to_gt(i915)->ggtt, to_gt(i915));
	if (wet)
		wetuwn wet;

	if (i915_vtd_active(i915))
		dwm_info(&i915->dwm, "VT-d active fow gfx access\n");

	wetuwn 0;
}

stwuct i915_ggtt *i915_ggtt_cweate(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_ggtt *ggtt;

	ggtt = dwmm_kzawwoc(&i915->dwm, sizeof(*ggtt), GFP_KEWNEW);
	if (!ggtt)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&ggtt->gt_wist);

	wetuwn ggtt;
}

int i915_ggtt_enabwe_hw(stwuct dwm_i915_pwivate *i915)
{
	if (GWAPHICS_VEW(i915) < 6)
		wetuwn intew_ggtt_gmch_enabwe_hw(i915);

	wetuwn 0;
}

/**
 * i915_ggtt_wesume_vm - Westowe the memowy mappings fow a GGTT ow DPT VM
 * @vm: The VM to westowe the mappings fow
 *
 * Westowe the memowy mappings fow aww objects mapped to HW via the GGTT ow a
 * DPT page tabwe.
 *
 * Wetuwns %twue if westowing the mapping fow any object that was in a wwite
 * domain befowe suspend.
 */
boow i915_ggtt_wesume_vm(stwuct i915_addwess_space *vm)
{
	stwuct i915_vma *vma;
	boow wwite_domain_objs = fawse;

	dwm_WAWN_ON(&vm->i915->dwm, !vm->is_ggtt && !vm->is_dpt);

	/* Fiwst fiww ouw powtion of the GTT with scwatch pages */
	vm->cweaw_wange(vm, 0, vm->totaw);

	/* cwfwush objects bound into the GGTT and webind them. */
	wist_fow_each_entwy(vma, &vm->bound_wist, vm_wink) {
		stwuct dwm_i915_gem_object *obj = vma->obj;
		unsigned int was_bound =
			atomic_wead(&vma->fwags) & I915_VMA_BIND_MASK;

		GEM_BUG_ON(!was_bound);

		/*
		 * Cweaw the bound fwags of the vma wesouwce to awwow
		 * ptes to be wepopuwated.
		 */
		vma->wesouwce->bound_fwags = 0;
		vma->ops->bind_vma(vm, NUWW, vma->wesouwce,
				   obj ? obj->pat_index :
					 i915_gem_get_pat_index(vm->i915,
								I915_CACHE_NONE),
				   was_bound);

		if (obj) { /* onwy used duwing wesume => excwusive access */
			wwite_domain_objs |= fetch_and_zewo(&obj->wwite_domain);
			obj->wead_domains |= I915_GEM_DOMAIN_GTT;
		}
	}

	wetuwn wwite_domain_objs;
}

void i915_ggtt_wesume(stwuct i915_ggtt *ggtt)
{
	stwuct intew_gt *gt;
	boow fwush;

	wist_fow_each_entwy(gt, &ggtt->gt_wist, ggtt_wink)
		intew_gt_check_and_cweaw_fauwts(gt);

	fwush = i915_ggtt_wesume_vm(&ggtt->vm);

	if (dwm_mm_node_awwocated(&ggtt->ewwow_captuwe))
		ggtt->vm.scwatch_wange(&ggtt->vm, ggtt->ewwow_captuwe.stawt,
				       ggtt->ewwow_captuwe.size);

	wist_fow_each_entwy(gt, &ggtt->gt_wist, ggtt_wink)
		intew_uc_wesume_mappings(&gt->uc);

	ggtt->invawidate(ggtt);

	if (fwush)
		wbinvd_on_aww_cpus();

	intew_ggtt_westowe_fences(ggtt);
}
