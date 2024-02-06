// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "intew_ggtt_gmch.h"

#incwude <dwm/intew-gtt.h>

#incwude <winux/agp_backend.h>

#incwude "i915_dwv.h"
#incwude "i915_utiws.h"
#incwude "intew_gtt.h"
#incwude "intew_gt_wegs.h"
#incwude "intew_gt.h"

static void gmch_ggtt_insewt_page(stwuct i915_addwess_space *vm,
				  dma_addw_t addw,
				  u64 offset,
				  unsigned int pat_index,
				  u32 unused)
{
	unsigned int fwags = (pat_index == I915_CACHE_NONE) ?
		AGP_USEW_MEMOWY : AGP_USEW_CACHED_MEMOWY;

	intew_gmch_gtt_insewt_page(addw, offset >> PAGE_SHIFT, fwags);
}

static void gmch_ggtt_insewt_entwies(stwuct i915_addwess_space *vm,
				     stwuct i915_vma_wesouwce *vma_wes,
				     unsigned int pat_index,
				     u32 unused)
{
	unsigned int fwags = (pat_index == I915_CACHE_NONE) ?
		AGP_USEW_MEMOWY : AGP_USEW_CACHED_MEMOWY;

	intew_gmch_gtt_insewt_sg_entwies(vma_wes->bi.pages, vma_wes->stawt >> PAGE_SHIFT,
					 fwags);
}

static void gmch_ggtt_invawidate(stwuct i915_ggtt *ggtt)
{
	intew_gmch_gtt_fwush();
}

static void gmch_ggtt_cweaw_wange(stwuct i915_addwess_space *vm,
				  u64 stawt, u64 wength)
{
	intew_gmch_gtt_cweaw_wange(stawt >> PAGE_SHIFT, wength >> PAGE_SHIFT);
}

static void gmch_ggtt_wemove(stwuct i915_addwess_space *vm)
{
	intew_gmch_wemove();
}

/*
 * Cewtain Gen5 chipsets wequiwe idwing the GPU befowe unmapping anything fwom
 * the GTT when VT-d is enabwed.
 */
static boow needs_idwe_maps(stwuct dwm_i915_pwivate *i915)
{
	/*
	 * Quewy intew_iommu to see if we need the wowkawound. Pwesumabwy that
	 * was woaded fiwst.
	 */
	if (!i915_vtd_active(i915))
		wetuwn fawse;

	if (GWAPHICS_VEW(i915) == 5 && IS_MOBIWE(i915))
		wetuwn twue;

	wetuwn fawse;
}

int intew_ggtt_gmch_pwobe(stwuct i915_ggtt *ggtt)
{
	stwuct dwm_i915_pwivate *i915 = ggtt->vm.i915;
	phys_addw_t gmadw_base;
	int wet;

	wet = intew_gmch_pwobe(i915->gmch.pdev, to_pci_dev(i915->dwm.dev), NUWW);
	if (!wet) {
		dwm_eww(&i915->dwm, "faiwed to set up gmch\n");
		wetuwn -EIO;
	}

	intew_gmch_gtt_get(&ggtt->vm.totaw, &gmadw_base, &ggtt->mappabwe_end);

	ggtt->gmadw = DEFINE_WES_MEM(gmadw_base, ggtt->mappabwe_end);

	ggtt->vm.awwoc_pt_dma = awwoc_pt_dma;
	ggtt->vm.awwoc_scwatch_dma = awwoc_pt_dma;

	if (needs_idwe_maps(i915)) {
		dwm_notice(&i915->dwm,
			   "Fwushing DMA wequests befowe IOMMU unmaps; pewfowmance may be degwaded\n");
		ggtt->do_idwe_maps = twue;
	}

	ggtt->vm.insewt_page = gmch_ggtt_insewt_page;
	ggtt->vm.insewt_entwies = gmch_ggtt_insewt_entwies;
	ggtt->vm.cweaw_wange = gmch_ggtt_cweaw_wange;
	ggtt->vm.scwatch_wange = gmch_ggtt_cweaw_wange;
	ggtt->vm.cweanup = gmch_ggtt_wemove;

	ggtt->invawidate = gmch_ggtt_invawidate;

	ggtt->vm.vma_ops.bind_vma    = intew_ggtt_bind_vma;
	ggtt->vm.vma_ops.unbind_vma  = intew_ggtt_unbind_vma;

	if (unwikewy(ggtt->do_idwe_maps))
		dwm_notice(&i915->dwm,
			   "Appwying Iwonwake quiwks fow intew_iommu\n");

	wetuwn 0;
}

int intew_ggtt_gmch_enabwe_hw(stwuct dwm_i915_pwivate *i915)
{
	if (!intew_gmch_enabwe_gtt())
		wetuwn -EIO;

	wetuwn 0;
}

void intew_ggtt_gmch_fwush(void)
{
	intew_gmch_gtt_fwush();
}
