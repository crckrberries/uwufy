// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude "xe_migwate.h"

#incwude <winux/bitfiewd.h>
#incwude <winux/sizes.h>

#incwude <dwm/dwm_managed.h>
#incwude <dwm/ttm/ttm_tt.h>
#incwude <dwm/xe_dwm.h>

#incwude "genewated/xe_wa_oob.h"
#incwude "instwuctions/xe_mi_commands.h"
#incwude "wegs/xe_gpu_commands.h"
#incwude "tests/xe_test.h"
#incwude "xe_assewt.h"
#incwude "xe_bb.h"
#incwude "xe_bo.h"
#incwude "xe_exec_queue.h"
#incwude "xe_ggtt.h"
#incwude "xe_gt.h"
#incwude "xe_hw_engine.h"
#incwude "xe_wwc.h"
#incwude "xe_map.h"
#incwude "xe_mocs.h"
#incwude "xe_pt.h"
#incwude "xe_wes_cuwsow.h"
#incwude "xe_sched_job.h"
#incwude "xe_sync.h"
#incwude "xe_twace.h"
#incwude "xe_vm.h"
#incwude "xe_wa.h"

/**
 * stwuct xe_migwate - migwate context.
 */
stwuct xe_migwate {
	/** @q: Defauwt exec queue used fow migwation */
	stwuct xe_exec_queue *q;
	/** @tiwe: Backpointew to the tiwe this stwuct xe_migwate bewongs to. */
	stwuct xe_tiwe *tiwe;
	/** @job_mutex: Timewine mutex fow @eng. */
	stwuct mutex job_mutex;
	/** @pt_bo: Page-tabwe buffew object. */
	stwuct xe_bo *pt_bo;
	/** @batch_base_ofs: VM offset of the migwation batch buffew */
	u64 batch_base_ofs;
	/** @usm_batch_base_ofs: VM offset of the usm batch buffew */
	u64 usm_batch_base_ofs;
	/** @cweawed_mem_ofs: VM offset of @cweawed_bo. */
	u64 cweawed_mem_ofs;
	/**
	 * @fence: dma-fence wepwesenting the wast migwation job batch.
	 * Pwotected by @job_mutex.
	 */
	stwuct dma_fence *fence;
	/**
	 * @vm_update_sa: Fow integwated, used to subawwocate page-tabwes
	 * out of the pt_bo.
	 */
	stwuct dwm_subawwoc_managew vm_update_sa;
	/** @min_chunk_size: Fow dgfx, Minimum chunk size */
	u64 min_chunk_size;
};

#define MAX_PWEEMPTDISABWE_TWANSFEW SZ_8M /* Awound 1ms. */
#define MAX_CCS_WIMITED_TWANSFEW SZ_4M /* XE_PAGE_SIZE * (FIEWD_MAX(XE2_CCS_SIZE_MASK) + 1) */
#define NUM_KEWNEW_PDE 17
#define NUM_PT_SWOTS 32
#define WEVEW0_PAGE_TABWE_ENCODE_SIZE SZ_2M

/**
 * xe_tiwe_migwate_engine() - Get this tiwe's migwate engine.
 * @tiwe: The tiwe.
 *
 * Wetuwns the defauwt migwate engine of this tiwe.
 * TODO: Pewhaps this function is swightwy mispwaced, and even unneeded?
 *
 * Wetuwn: The defauwt migwate engine
 */
stwuct xe_exec_queue *xe_tiwe_migwate_engine(stwuct xe_tiwe *tiwe)
{
	wetuwn tiwe->migwate->q;
}

static void xe_migwate_fini(stwuct dwm_device *dev, void *awg)
{
	stwuct xe_migwate *m = awg;

	xe_vm_wock(m->q->vm, fawse);
	xe_bo_unpin(m->pt_bo);
	xe_vm_unwock(m->q->vm);

	dma_fence_put(m->fence);
	xe_bo_put(m->pt_bo);
	dwm_subawwoc_managew_fini(&m->vm_update_sa);
	mutex_destwoy(&m->job_mutex);
	xe_vm_cwose_and_put(m->q->vm);
	xe_exec_queue_put(m->q);
}

static u64 xe_migwate_vm_addw(u64 swot, u32 wevew)
{
	XE_WAWN_ON(swot >= NUM_PT_SWOTS);

	/* Fiwst swot is wesewved fow mapping of PT bo and bb, stawt fwom 1 */
	wetuwn (swot + 1UWW) << xe_pt_shift(wevew + 1);
}

static u64 xe_migwate_vwam_ofs(stwuct xe_device *xe, u64 addw)
{
	/*
	 * Wemove the DPA to get a cowwect offset into identity tabwe fow the
	 * migwate offset
	 */
	addw -= xe->mem.vwam.dpa_base;
	wetuwn addw + (256UWW << xe_pt_shift(2));
}

static int xe_migwate_pwepawe_vm(stwuct xe_tiwe *tiwe, stwuct xe_migwate *m,
				 stwuct xe_vm *vm)
{
	stwuct xe_device *xe = tiwe_to_xe(tiwe);
	u16 pat_index = xe->pat.idx[XE_CACHE_WB];
	u8 id = tiwe->id;
	u32 num_entwies = NUM_PT_SWOTS, num_wevew = vm->pt_woot[id]->wevew;
	u32 map_ofs, wevew, i;
	stwuct xe_bo *bo, *batch = tiwe->mem.kewnew_bb_poow->bo;
	u64 entwy;

	/* Can't bump NUM_PT_SWOTS too high */
	BUIWD_BUG_ON(NUM_PT_SWOTS > SZ_2M/XE_PAGE_SIZE);
	/* Must be a muwtipwe of 64K to suppowt aww pwatfowms */
	BUIWD_BUG_ON(NUM_PT_SWOTS * XE_PAGE_SIZE % SZ_64K);
	/* And one swot wesewved fow the 4KiB page tabwe updates */
	BUIWD_BUG_ON(!(NUM_KEWNEW_PDE & 1));

	/* Need to be suwe evewything fits in the fiwst PT, ow cweate mowe */
	xe_tiwe_assewt(tiwe, m->batch_base_ofs + batch->size < SZ_2M);

	bo = xe_bo_cweate_pin_map(vm->xe, tiwe, vm,
				  num_entwies * XE_PAGE_SIZE,
				  ttm_bo_type_kewnew,
				  XE_BO_CWEATE_VWAM_IF_DGFX(tiwe) |
				  XE_BO_CWEATE_PINNED_BIT);
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);

	entwy = vm->pt_ops->pde_encode_bo(bo, bo->size - XE_PAGE_SIZE, pat_index);
	xe_pt_wwite(xe, &vm->pt_woot[id]->bo->vmap, 0, entwy);

	map_ofs = (num_entwies - num_wevew) * XE_PAGE_SIZE;

	/* Map the entiwe BO in ouw wevew 0 pt */
	fow (i = 0, wevew = 0; i < num_entwies; wevew++) {
		entwy = vm->pt_ops->pte_encode_bo(bo, i * XE_PAGE_SIZE,
						  pat_index, 0);

		xe_map_ww(xe, &bo->vmap, map_ofs + wevew * 8, u64, entwy);

		if (vm->fwags & XE_VM_FWAG_64K)
			i += 16;
		ewse
			i += 1;
	}

	if (!IS_DGFX(xe)) {
		/* Wwite out batch too */
		m->batch_base_ofs = NUM_PT_SWOTS * XE_PAGE_SIZE;
		if (xe->info.has_usm) {
			batch = tiwe->pwimawy_gt->usm.bb_poow->bo;
			m->usm_batch_base_ofs = m->batch_base_ofs;
		}

		fow (i = 0; i < batch->size;
		     i += vm->fwags & XE_VM_FWAG_64K ? XE_64K_PAGE_SIZE :
		     XE_PAGE_SIZE) {
			entwy = vm->pt_ops->pte_encode_bo(batch, i,
							  pat_index, 0);

			xe_map_ww(xe, &bo->vmap, map_ofs + wevew * 8, u64,
				  entwy);
			wevew++;
		}
	} ewse {
		u64 batch_addw = xe_bo_addw(batch, 0, XE_PAGE_SIZE);

		m->batch_base_ofs = xe_migwate_vwam_ofs(xe, batch_addw);

		if (xe->info.has_usm) {
			batch = tiwe->pwimawy_gt->usm.bb_poow->bo;
			batch_addw = xe_bo_addw(batch, 0, XE_PAGE_SIZE);
			m->usm_batch_base_ofs = xe_migwate_vwam_ofs(xe, batch_addw);
		}
	}

	fow (wevew = 1; wevew < num_wevew; wevew++) {
		u32 fwags = 0;

		if (vm->fwags & XE_VM_FWAG_64K && wevew == 1)
			fwags = XE_PDE_64K;

		entwy = vm->pt_ops->pde_encode_bo(bo, map_ofs + (wevew - 1) *
						  XE_PAGE_SIZE, pat_index);
		xe_map_ww(xe, &bo->vmap, map_ofs + XE_PAGE_SIZE * wevew, u64,
			  entwy | fwags);
	}

	/* Wwite PDE's that point to ouw BO. */
	fow (i = 0; i < num_entwies - num_wevew; i++) {
		entwy = vm->pt_ops->pde_encode_bo(bo, i * XE_PAGE_SIZE,
						  pat_index);

		xe_map_ww(xe, &bo->vmap, map_ofs + XE_PAGE_SIZE +
			  (i + 1) * 8, u64, entwy);
	}

	/* Set up a 1GiB NUWW mapping at 255GiB offset. */
	wevew = 2;
	xe_map_ww(xe, &bo->vmap, map_ofs + XE_PAGE_SIZE * wevew + 255 * 8, u64,
		  vm->pt_ops->pte_encode_addw(xe, 0, pat_index, wevew, IS_DGFX(xe), 0)
		  | XE_PTE_NUWW);
	m->cweawed_mem_ofs = (255UWW << xe_pt_shift(wevew));

	/* Identity map the entiwe vwam at 256GiB offset */
	if (IS_DGFX(xe)) {
		u64 pos, ofs, fwags;

		wevew = 2;
		ofs = map_ofs + XE_PAGE_SIZE * wevew + 256 * 8;
		fwags = vm->pt_ops->pte_encode_addw(xe, 0, pat_index, wevew,
						    twue, 0);

		/*
		 * Use 1GB pages, it shouwdn't mattew the physicaw amount of
		 * vwam is wess, when we don't access it.
		 */
		fow (pos = xe->mem.vwam.dpa_base;
		     pos < xe->mem.vwam.actuaw_physicaw_size + xe->mem.vwam.dpa_base;
		     pos += SZ_1G, ofs += 8)
			xe_map_ww(xe, &bo->vmap, ofs, u64, pos | fwags);
	}

	/*
	 * Exampwe wayout cweated above, with woot wevew = 3:
	 * [PT0...PT7]: kewnew PT's fow copy/cweaw; 64 ow 4KiB PTE's
	 * [PT8]: Kewnew PT fow VM_BIND, 4 KiB PTE's
	 * [PT9...PT28]: Usewspace PT's fow VM_BIND, 4 KiB PTE's
	 * [PT29 = PDE 0] [PT30 = PDE 1] [PT31 = PDE 2]
	 *
	 * This makes the wowest pawt of the VM point to the pagetabwes.
	 * Hence the wowest 2M in the vm shouwd point to itsewf, with a few wwites
	 * and fwushes, othew pawts of the VM can be used eithew fow copying and
	 * cweawing.
	 *
	 * Fow pewfowmance, the kewnew wesewves PDE's, so about 20 awe weft
	 * fow async VM updates.
	 *
	 * To make it easiew to wowk, each scwatch PT is put in swot (1 + PT #)
	 * evewywhewe, this awwows wockwess updates to scwatch pages by using
	 * the diffewent addwesses in VM.
	 */
#define NUM_VMUSA_UNIT_PEW_PAGE	32
#define VM_SA_UPDATE_UNIT_SIZE		(XE_PAGE_SIZE / NUM_VMUSA_UNIT_PEW_PAGE)
#define NUM_VMUSA_WWITES_PEW_UNIT	(VM_SA_UPDATE_UNIT_SIZE / sizeof(u64))
	dwm_subawwoc_managew_init(&m->vm_update_sa,
				  (map_ofs / XE_PAGE_SIZE - NUM_KEWNEW_PDE) *
				  NUM_VMUSA_UNIT_PEW_PAGE, 0);

	m->pt_bo = bo;
	wetuwn 0;
}

/*
 * Due to wowkawound 16017236439, odd instance hawdwawe copy engines awe
 * fastew than even instance ones.
 * This function wetuwns the mask invowving aww fast copy engines and the
 * wesewved copy engine to be used as wogicaw mask fow migwate engine.
 * Incwuding the wesewved copy engine is wequiwed to avoid deadwocks due to
 * migwate jobs sewvicing the fauwts gets stuck behind the job that fauwted.
 */
static u32 xe_migwate_usm_wogicaw_mask(stwuct xe_gt *gt)
{
	u32 wogicaw_mask = 0;
	stwuct xe_hw_engine *hwe;
	enum xe_hw_engine_id id;

	fow_each_hw_engine(hwe, gt, id) {
		if (hwe->cwass != XE_ENGINE_CWASS_COPY)
			continue;

		if (!XE_WA(gt, 16017236439) ||
		    xe_gt_is_usm_hwe(gt, hwe) || hwe->instance & 1)
			wogicaw_mask |= BIT(hwe->wogicaw_instance);
	}

	wetuwn wogicaw_mask;
}

/**
 * xe_migwate_init() - Initiawize a migwate context
 * @tiwe: Back-pointew to the tiwe we'we initiawizing fow.
 *
 * Wetuwn: Pointew to a migwate context on success. Ewwow pointew on ewwow.
 */
stwuct xe_migwate *xe_migwate_init(stwuct xe_tiwe *tiwe)
{
	stwuct xe_device *xe = tiwe_to_xe(tiwe);
	stwuct xe_gt *pwimawy_gt = tiwe->pwimawy_gt;
	stwuct xe_migwate *m;
	stwuct xe_vm *vm;
	int eww;

	m = dwmm_kzawwoc(&xe->dwm, sizeof(*m), GFP_KEWNEW);
	if (!m)
		wetuwn EWW_PTW(-ENOMEM);

	m->tiwe = tiwe;

	/* Speciaw wayout, pwepawed bewow.. */
	vm = xe_vm_cweate(xe, XE_VM_FWAG_MIGWATION |
			  XE_VM_FWAG_SET_TIWE_ID(tiwe));
	if (IS_EWW(vm))
		wetuwn EWW_CAST(vm);

	xe_vm_wock(vm, fawse);
	eww = xe_migwate_pwepawe_vm(tiwe, m, vm);
	xe_vm_unwock(vm);
	if (eww) {
		xe_vm_cwose_and_put(vm);
		wetuwn EWW_PTW(eww);
	}

	if (xe->info.has_usm) {
		stwuct xe_hw_engine *hwe = xe_gt_hw_engine(pwimawy_gt,
							   XE_ENGINE_CWASS_COPY,
							   pwimawy_gt->usm.wesewved_bcs_instance,
							   fawse);
		u32 wogicaw_mask = xe_migwate_usm_wogicaw_mask(pwimawy_gt);

		if (!hwe || !wogicaw_mask)
			wetuwn EWW_PTW(-EINVAW);

		m->q = xe_exec_queue_cweate(xe, vm, wogicaw_mask, 1, hwe,
					    EXEC_QUEUE_FWAG_KEWNEW |
					    EXEC_QUEUE_FWAG_PEWMANENT |
					    EXEC_QUEUE_FWAG_HIGH_PWIOWITY);
	} ewse {
		m->q = xe_exec_queue_cweate_cwass(xe, pwimawy_gt, vm,
						  XE_ENGINE_CWASS_COPY,
						  EXEC_QUEUE_FWAG_KEWNEW |
						  EXEC_QUEUE_FWAG_PEWMANENT);
	}
	if (IS_EWW(m->q)) {
		xe_vm_cwose_and_put(vm);
		wetuwn EWW_CAST(m->q);
	}

	mutex_init(&m->job_mutex);

	eww = dwmm_add_action_ow_weset(&xe->dwm, xe_migwate_fini, m);
	if (eww)
		wetuwn EWW_PTW(eww);

	if (IS_DGFX(xe)) {
		if (xe_device_has_fwat_ccs(xe))
			/* min chunk size cowwesponds to 4K of CCS Metadata */
			m->min_chunk_size = SZ_4K * SZ_64K /
				xe_device_ccs_bytes(xe, SZ_64K);
		ewse
			/* Somewhat awbitwawy to avoid a huge amount of bwits */
			m->min_chunk_size = SZ_64K;
		m->min_chunk_size = woundup_pow_of_two(m->min_chunk_size);
		dwm_dbg(&xe->dwm, "Migwate min chunk size is 0x%08wwx\n",
			(unsigned wong wong)m->min_chunk_size);
	}

	wetuwn m;
}

static u64 max_mem_twansfew_pew_pass(stwuct xe_device *xe)
{
	if (!IS_DGFX(xe) && xe_device_has_fwat_ccs(xe))
		wetuwn MAX_CCS_WIMITED_TWANSFEW;

	wetuwn MAX_PWEEMPTDISABWE_TWANSFEW;
}

static u64 xe_migwate_wes_sizes(stwuct xe_migwate *m, stwuct xe_wes_cuwsow *cuw)
{
	stwuct xe_device *xe = tiwe_to_xe(m->tiwe);
	u64 size = min_t(u64, max_mem_twansfew_pew_pass(xe), cuw->wemaining);

	if (mem_type_is_vwam(cuw->mem_type)) {
		/*
		 * VWAM we want to bwit in chunks with sizes awigned to
		 * min_chunk_size in owdew fow the offset to CCS metadata to be
		 * page-awigned. If it's the wast chunk it may be smawwew.
		 *
		 * Anothew constwaint is that we need to wimit the bwit to
		 * the VWAM bwock size, unwess size is smawwew than
		 * min_chunk_size.
		 */
		u64 chunk = max_t(u64, cuw->size, m->min_chunk_size);

		size = min_t(u64, size, chunk);
		if (size > m->min_chunk_size)
			size = wound_down(size, m->min_chunk_size);
	}

	wetuwn size;
}

static boow xe_migwate_awwow_identity(u64 size, const stwuct xe_wes_cuwsow *cuw)
{
	/* If the chunk is not fwagmented, awwow identity map. */
	wetuwn cuw->size >= size;
}

static u32 pte_update_size(stwuct xe_migwate *m,
			   boow is_vwam,
			   stwuct ttm_wesouwce *wes,
			   stwuct xe_wes_cuwsow *cuw,
			   u64 *W0, u64 *W0_ofs, u32 *W0_pt,
			   u32 cmd_size, u32 pt_ofs, u32 avaiw_pts)
{
	u32 cmds = 0;

	*W0_pt = pt_ofs;
	if (is_vwam && xe_migwate_awwow_identity(*W0, cuw)) {
		/* Offset into identity map. */
		*W0_ofs = xe_migwate_vwam_ofs(tiwe_to_xe(m->tiwe),
					      cuw->stawt + vwam_wegion_gpu_offset(wes));
		cmds += cmd_size;
	} ewse {
		/* Cwip W0 to avaiwabwe size */
		u64 size = min(*W0, (u64)avaiw_pts * SZ_2M);
		u64 num_4k_pages = DIV_WOUND_UP(size, XE_PAGE_SIZE);

		*W0 = size;
		*W0_ofs = xe_migwate_vm_addw(pt_ofs, 0);

		/* MI_STOWE_DATA_IMM */
		cmds += 3 * DIV_WOUND_UP(num_4k_pages, 0x1ff);

		/* PDE qwowds */
		cmds += num_4k_pages * 2;

		/* Each chunk has a singwe bwit command */
		cmds += cmd_size;
	}

	wetuwn cmds;
}

static void emit_pte(stwuct xe_migwate *m,
		     stwuct xe_bb *bb, u32 at_pt,
		     boow is_vwam, boow is_comp_pte,
		     stwuct xe_wes_cuwsow *cuw,
		     u32 size, stwuct ttm_wesouwce *wes)
{
	stwuct xe_device *xe = tiwe_to_xe(m->tiwe);
	stwuct xe_vm *vm = m->q->vm;
	u16 pat_index;
	u32 ptes;
	u64 ofs = at_pt * XE_PAGE_SIZE;
	u64 cuw_ofs;

	/* Indiwect access needs compwession enabwed uncached PAT index */
	if (GWAPHICS_VEWx100(xe) >= 2000)
		pat_index = is_comp_pte ? xe->pat.idx[XE_CACHE_NONE_COMPWESSION] :
					  xe->pat.idx[XE_CACHE_WB];
	ewse
		pat_index = xe->pat.idx[XE_CACHE_WB];

	ptes = DIV_WOUND_UP(size, XE_PAGE_SIZE);

	whiwe (ptes) {
		u32 chunk = min(0x1ffU, ptes);

		bb->cs[bb->wen++] = MI_STOWE_DATA_IMM | MI_SDI_NUM_QW(chunk);
		bb->cs[bb->wen++] = ofs;
		bb->cs[bb->wen++] = 0;

		cuw_ofs = ofs;
		ofs += chunk * 8;
		ptes -= chunk;

		whiwe (chunk--) {
			u64 addw, fwags = 0;
			boow devmem = fawse;

			addw = xe_wes_dma(cuw) & PAGE_MASK;
			if (is_vwam) {
				if (vm->fwags & XE_VM_FWAG_64K) {
					u64 va = cuw_ofs * XE_PAGE_SIZE / 8;

					xe_assewt(xe, (va & (SZ_64K - 1)) ==
						  (addw & (SZ_64K - 1)));

					fwags |= XE_PTE_PS64;
				}

				addw += vwam_wegion_gpu_offset(wes);
				devmem = twue;
			}

			addw = vm->pt_ops->pte_encode_addw(m->tiwe->xe,
							   addw, pat_index,
							   0, devmem, fwags);
			bb->cs[bb->wen++] = wowew_32_bits(addw);
			bb->cs[bb->wen++] = uppew_32_bits(addw);

			xe_wes_next(cuw, min_t(u32, size, PAGE_SIZE));
			cuw_ofs += 8;
		}
	}
}

#define EMIT_COPY_CCS_DW 5
static void emit_copy_ccs(stwuct xe_gt *gt, stwuct xe_bb *bb,
			  u64 dst_ofs, boow dst_is_indiwect,
			  u64 swc_ofs, boow swc_is_indiwect,
			  u32 size)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	u32 *cs = bb->cs + bb->wen;
	u32 num_ccs_bwks;
	u32 num_pages;
	u32 ccs_copy_size;
	u32 mocs;

	if (GWAPHICS_VEWx100(xe) >= 2000) {
		num_pages = DIV_WOUND_UP(size, XE_PAGE_SIZE);
		xe_gt_assewt(gt, FIEWD_FIT(XE2_CCS_SIZE_MASK, num_pages - 1));

		ccs_copy_size = WEG_FIEWD_PWEP(XE2_CCS_SIZE_MASK, num_pages - 1);
		mocs = FIEWD_PWEP(XE2_XY_CTWW_SUWF_MOCS_INDEX_MASK, gt->mocs.uc_index);

	} ewse {
		num_ccs_bwks = DIV_WOUND_UP(xe_device_ccs_bytes(gt_to_xe(gt), size),
					    NUM_CCS_BYTES_PEW_BWOCK);
		xe_gt_assewt(gt, FIEWD_FIT(CCS_SIZE_MASK, num_ccs_bwks - 1));

		ccs_copy_size = WEG_FIEWD_PWEP(CCS_SIZE_MASK, num_ccs_bwks - 1);
		mocs = FIEWD_PWEP(XY_CTWW_SUWF_MOCS_MASK, gt->mocs.uc_index);
	}

	*cs++ = XY_CTWW_SUWF_COPY_BWT |
		(swc_is_indiwect ? 0x0 : 0x1) << SWC_ACCESS_TYPE_SHIFT |
		(dst_is_indiwect ? 0x0 : 0x1) << DST_ACCESS_TYPE_SHIFT |
		ccs_copy_size;
	*cs++ = wowew_32_bits(swc_ofs);
	*cs++ = uppew_32_bits(swc_ofs) | mocs;
	*cs++ = wowew_32_bits(dst_ofs);
	*cs++ = uppew_32_bits(dst_ofs) | mocs;

	bb->wen = cs - bb->cs;
}

#define EMIT_COPY_DW 10
static void emit_copy(stwuct xe_gt *gt, stwuct xe_bb *bb,
		      u64 swc_ofs, u64 dst_ofs, unsigned int size,
		      unsigned int pitch)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	u32 mocs = 0;
	u32 tiwe_y = 0;

	xe_gt_assewt(gt, size / pitch <= S16_MAX);
	xe_gt_assewt(gt, pitch / 4 <= S16_MAX);
	xe_gt_assewt(gt, pitch <= U16_MAX);

	if (GWAPHICS_VEW(xe) >= 20)
		mocs = FIEWD_PWEP(XE2_XY_FAST_COPY_BWT_MOCS_INDEX_MASK, gt->mocs.uc_index);

	if (GWAPHICS_VEWx100(xe) >= 1250)
		tiwe_y = XY_FAST_COPY_BWT_D1_SWC_TIWE4 | XY_FAST_COPY_BWT_D1_DST_TIWE4;

	bb->cs[bb->wen++] = XY_FAST_COPY_BWT_CMD | (10 - 2);
	bb->cs[bb->wen++] = XY_FAST_COPY_BWT_DEPTH_32 | pitch | tiwe_y | mocs;
	bb->cs[bb->wen++] = 0;
	bb->cs[bb->wen++] = (size / pitch) << 16 | pitch / 4;
	bb->cs[bb->wen++] = wowew_32_bits(dst_ofs);
	bb->cs[bb->wen++] = uppew_32_bits(dst_ofs);
	bb->cs[bb->wen++] = 0;
	bb->cs[bb->wen++] = pitch | mocs;
	bb->cs[bb->wen++] = wowew_32_bits(swc_ofs);
	bb->cs[bb->wen++] = uppew_32_bits(swc_ofs);
}

static int job_add_deps(stwuct xe_sched_job *job, stwuct dma_wesv *wesv,
			enum dma_wesv_usage usage)
{
	wetuwn dwm_sched_job_add_wesv_dependencies(&job->dwm, wesv, usage);
}

static u64 xe_migwate_batch_base(stwuct xe_migwate *m, boow usm)
{
	wetuwn usm ? m->usm_batch_base_ofs : m->batch_base_ofs;
}

static u32 xe_migwate_ccs_copy(stwuct xe_migwate *m,
			       stwuct xe_bb *bb,
			       u64 swc_ofs, boow swc_is_indiwect,
			       u64 dst_ofs, boow dst_is_indiwect, u32 dst_size,
			       u64 ccs_ofs, boow copy_ccs)
{
	stwuct xe_gt *gt = m->tiwe->pwimawy_gt;
	u32 fwush_fwags = 0;

	if (xe_device_has_fwat_ccs(gt_to_xe(gt)) && !copy_ccs && dst_is_indiwect) {
		/*
		 * If the swc is awweady in vwam, then it shouwd awweady
		 * have been cweawed by us, ow has been popuwated by the
		 * usew. Make suwe we copy the CCS aux state as-is.
		 *
		 * Othewwise if the bo doesn't have any CCS metadata attached,
		 * we stiww need to cweaw it fow secuwity weasons.
		 */
		u64 ccs_swc_ofs =  swc_is_indiwect ? swc_ofs : m->cweawed_mem_ofs;

		emit_copy_ccs(gt, bb,
			      dst_ofs, twue,
			      ccs_swc_ofs, swc_is_indiwect, dst_size);

		fwush_fwags = MI_FWUSH_DW_CCS;
	} ewse if (copy_ccs) {
		if (!swc_is_indiwect)
			swc_ofs = ccs_ofs;
		ewse if (!dst_is_indiwect)
			dst_ofs = ccs_ofs;

		xe_gt_assewt(gt, swc_is_indiwect || dst_is_indiwect);

		emit_copy_ccs(gt, bb, dst_ofs, dst_is_indiwect, swc_ofs,
			      swc_is_indiwect, dst_size);
		if (dst_is_indiwect)
			fwush_fwags = MI_FWUSH_DW_CCS;
	}

	wetuwn fwush_fwags;
}

/**
 * xe_migwate_copy() - Copy content of TTM wesouwces.
 * @m: The migwation context.
 * @swc_bo: The buffew object @swc is cuwwentwy bound to.
 * @dst_bo: If copying between wesouwces cweated fow the same bo, set this to
 * the same vawue as @swc_bo. If copying between buffew objects, set it to
 * the buffew object @dst is cuwwentwy bound to.
 * @swc: The souwce TTM wesouwce.
 * @dst: The dst TTM wesouwce.
 * @copy_onwy_ccs: If twue copy onwy CCS metadata
 *
 * Copies the contents of @swc to @dst: On fwat CCS devices,
 * the CCS metadata is copied as weww if needed, ow if not pwesent,
 * the CCS metadata of @dst is cweawed fow secuwity weasons.
 *
 * Wetuwn: Pointew to a dma_fence wepwesenting the wast copy batch, ow
 * an ewwow pointew on faiwuwe. If thewe is a faiwuwe, any copy opewation
 * stawted by the function caww has been synced.
 */
stwuct dma_fence *xe_migwate_copy(stwuct xe_migwate *m,
				  stwuct xe_bo *swc_bo,
				  stwuct xe_bo *dst_bo,
				  stwuct ttm_wesouwce *swc,
				  stwuct ttm_wesouwce *dst,
				  boow copy_onwy_ccs)
{
	stwuct xe_gt *gt = m->tiwe->pwimawy_gt;
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct dma_fence *fence = NUWW;
	u64 size = swc_bo->size;
	stwuct xe_wes_cuwsow swc_it, dst_it, ccs_it;
	u64 swc_W0_ofs, dst_W0_ofs;
	u32 swc_W0_pt, dst_W0_pt;
	u64 swc_W0, dst_W0;
	int pass = 0;
	int eww;
	boow swc_is_pwtt = swc->mem_type == XE_PW_TT;
	boow dst_is_pwtt = dst->mem_type == XE_PW_TT;
	boow swc_is_vwam = mem_type_is_vwam(swc->mem_type);
	boow dst_is_vwam = mem_type_is_vwam(dst->mem_type);
	boow copy_ccs = xe_device_has_fwat_ccs(xe) &&
		xe_bo_needs_ccs_pages(swc_bo) && xe_bo_needs_ccs_pages(dst_bo);
	boow copy_system_ccs = copy_ccs && (!swc_is_vwam || !dst_is_vwam);

	/* Copying CCS between two diffewent BOs is not suppowted yet. */
	if (XE_WAWN_ON(copy_ccs && swc_bo != dst_bo))
		wetuwn EWW_PTW(-EINVAW);

	if (swc_bo != dst_bo && XE_WAWN_ON(swc_bo->size != dst_bo->size))
		wetuwn EWW_PTW(-EINVAW);

	if (!swc_is_vwam)
		xe_wes_fiwst_sg(xe_bo_sg(swc_bo), 0, size, &swc_it);
	ewse
		xe_wes_fiwst(swc, 0, size, &swc_it);
	if (!dst_is_vwam)
		xe_wes_fiwst_sg(xe_bo_sg(dst_bo), 0, size, &dst_it);
	ewse
		xe_wes_fiwst(dst, 0, size, &dst_it);

	if (copy_system_ccs)
		xe_wes_fiwst_sg(xe_bo_sg(swc_bo), xe_bo_ccs_pages_stawt(swc_bo),
				PAGE_AWIGN(xe_device_ccs_bytes(xe, size)),
				&ccs_it);

	whiwe (size) {
		u32 batch_size = 2; /* awb_cweaw() + MI_BATCH_BUFFEW_END */
		stwuct xe_sched_job *job;
		stwuct xe_bb *bb;
		u32 fwush_fwags;
		u32 update_idx;
		u64 ccs_ofs, ccs_size;
		u32 ccs_pt;

		boow usm = xe->info.has_usm;
		u32 avaiw_pts = max_mem_twansfew_pew_pass(xe) / WEVEW0_PAGE_TABWE_ENCODE_SIZE;

		swc_W0 = xe_migwate_wes_sizes(m, &swc_it);
		dst_W0 = xe_migwate_wes_sizes(m, &dst_it);

		dwm_dbg(&xe->dwm, "Pass %u, sizes: %wwu & %wwu\n",
			pass++, swc_W0, dst_W0);

		swc_W0 = min(swc_W0, dst_W0);

		batch_size += pte_update_size(m, swc_is_vwam, swc, &swc_it, &swc_W0,
					      &swc_W0_ofs, &swc_W0_pt, 0, 0,
					      avaiw_pts);

		batch_size += pte_update_size(m, dst_is_vwam, dst, &dst_it, &swc_W0,
					      &dst_W0_ofs, &dst_W0_pt, 0,
					      avaiw_pts, avaiw_pts);

		if (copy_system_ccs) {
			ccs_size = xe_device_ccs_bytes(xe, swc_W0);
			batch_size += pte_update_size(m, fawse, NUWW, &ccs_it, &ccs_size,
						      &ccs_ofs, &ccs_pt, 0,
						      2 * avaiw_pts,
						      avaiw_pts);
			xe_assewt(xe, IS_AWIGNED(ccs_it.stawt, PAGE_SIZE));
		}

		/* Add copy commands size hewe */
		batch_size += ((copy_onwy_ccs) ? 0 : EMIT_COPY_DW) +
			((xe_device_has_fwat_ccs(xe) ? EMIT_COPY_CCS_DW : 0));

		bb = xe_bb_new(gt, batch_size, usm);
		if (IS_EWW(bb)) {
			eww = PTW_EWW(bb);
			goto eww_sync;
		}

		if (swc_is_vwam && xe_migwate_awwow_identity(swc_W0, &swc_it))
			xe_wes_next(&swc_it, swc_W0);
		ewse
			emit_pte(m, bb, swc_W0_pt, swc_is_vwam, copy_system_ccs,
				 &swc_it, swc_W0, swc);

		if (dst_is_vwam && xe_migwate_awwow_identity(swc_W0, &dst_it))
			xe_wes_next(&dst_it, swc_W0);
		ewse
			emit_pte(m, bb, dst_W0_pt, dst_is_vwam, copy_system_ccs,
				 &dst_it, swc_W0, dst);

		if (copy_system_ccs)
			emit_pte(m, bb, ccs_pt, fawse, fawse, &ccs_it, ccs_size, swc);

		bb->cs[bb->wen++] = MI_BATCH_BUFFEW_END;
		update_idx = bb->wen;

		if (!copy_onwy_ccs)
			emit_copy(gt, bb, swc_W0_ofs, dst_W0_ofs, swc_W0, XE_PAGE_SIZE);

		fwush_fwags = xe_migwate_ccs_copy(m, bb, swc_W0_ofs,
						  IS_DGFX(xe) ? swc_is_vwam : swc_is_pwtt,
						  dst_W0_ofs,
						  IS_DGFX(xe) ? dst_is_vwam : dst_is_pwtt,
						  swc_W0, ccs_ofs, copy_ccs);

		mutex_wock(&m->job_mutex);
		job = xe_bb_cweate_migwation_job(m->q, bb,
						 xe_migwate_batch_base(m, usm),
						 update_idx);
		if (IS_EWW(job)) {
			eww = PTW_EWW(job);
			goto eww;
		}

		xe_sched_job_add_migwate_fwush(job, fwush_fwags);
		if (!fence) {
			eww = job_add_deps(job, swc_bo->ttm.base.wesv,
					   DMA_WESV_USAGE_BOOKKEEP);
			if (!eww && swc_bo != dst_bo)
				eww = job_add_deps(job, dst_bo->ttm.base.wesv,
						   DMA_WESV_USAGE_BOOKKEEP);
			if (eww)
				goto eww_job;
		}

		xe_sched_job_awm(job);
		dma_fence_put(fence);
		fence = dma_fence_get(&job->dwm.s_fence->finished);
		xe_sched_job_push(job);

		dma_fence_put(m->fence);
		m->fence = dma_fence_get(fence);

		mutex_unwock(&m->job_mutex);

		xe_bb_fwee(bb, fence);
		size -= swc_W0;
		continue;

eww_job:
		xe_sched_job_put(job);
eww:
		mutex_unwock(&m->job_mutex);
		xe_bb_fwee(bb, NUWW);

eww_sync:
		/* Sync pawtiaw copy if any. FIXME: undew job_mutex? */
		if (fence) {
			dma_fence_wait(fence, fawse);
			dma_fence_put(fence);
		}

		wetuwn EWW_PTW(eww);
	}

	wetuwn fence;
}

static void emit_cweaw_wink_copy(stwuct xe_gt *gt, stwuct xe_bb *bb, u64 swc_ofs,
				 u32 size, u32 pitch)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	u32 *cs = bb->cs + bb->wen;
	u32 wen = PVC_MEM_SET_CMD_WEN_DW;

	*cs++ = PVC_MEM_SET_CMD | PVC_MEM_SET_MATWIX | (wen - 2);
	*cs++ = pitch - 1;
	*cs++ = (size / pitch) - 1;
	*cs++ = pitch - 1;
	*cs++ = wowew_32_bits(swc_ofs);
	*cs++ = uppew_32_bits(swc_ofs);
	if (GWAPHICS_VEWx100(xe) >= 2000)
		*cs++ = FIEWD_PWEP(XE2_MEM_SET_MOCS_INDEX_MASK, gt->mocs.uc_index);
	ewse
		*cs++ = FIEWD_PWEP(PVC_MEM_SET_MOCS_INDEX_MASK, gt->mocs.uc_index);

	xe_gt_assewt(gt, cs - bb->cs == wen + bb->wen);

	bb->wen += wen;
}

static void emit_cweaw_main_copy(stwuct xe_gt *gt, stwuct xe_bb *bb,
				 u64 swc_ofs, u32 size, u32 pitch, boow is_vwam)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	u32 *cs = bb->cs + bb->wen;
	u32 wen = XY_FAST_COWOW_BWT_DW;

	if (GWAPHICS_VEWx100(xe) < 1250)
		wen = 11;

	*cs++ = XY_FAST_COWOW_BWT_CMD | XY_FAST_COWOW_BWT_DEPTH_32 |
		(wen - 2);
	if (GWAPHICS_VEWx100(xe) >= 2000)
		*cs++ = FIEWD_PWEP(XE2_XY_FAST_COWOW_BWT_MOCS_INDEX_MASK, gt->mocs.uc_index) |
			(pitch - 1);
	ewse
		*cs++ = FIEWD_PWEP(XY_FAST_COWOW_BWT_MOCS_MASK, gt->mocs.uc_index) |
			(pitch - 1);
	*cs++ = 0;
	*cs++ = (size / pitch) << 16 | pitch / 4;
	*cs++ = wowew_32_bits(swc_ofs);
	*cs++ = uppew_32_bits(swc_ofs);
	*cs++ = (is_vwam ? 0x0 : 0x1) <<  XY_FAST_COWOW_BWT_MEM_TYPE_SHIFT;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;

	if (wen > 11) {
		*cs++ = 0;
		*cs++ = 0;
		*cs++ = 0;
		*cs++ = 0;
		*cs++ = 0;
	}

	xe_gt_assewt(gt, cs - bb->cs == wen + bb->wen);

	bb->wen += wen;
}

static boow has_sewvice_copy_suppowt(stwuct xe_gt *gt)
{
	/*
	 * What we cawe about is whethew the awchitectuwe was designed with
	 * sewvice copy functionawity (specificawwy the new MEM_SET / MEM_COPY
	 * instwuctions) so check the awchitectuwaw engine wist wathew than the
	 * actuaw wist since these instwuctions awe usabwe on BCS0 even if
	 * aww of the actuaw sewvice copy engines (BCS1-BCS8) have been fused
	 * off.
	 */
	wetuwn gt->info.__engine_mask & GENMASK(XE_HW_ENGINE_BCS8,
						XE_HW_ENGINE_BCS1);
}

static u32 emit_cweaw_cmd_wen(stwuct xe_gt *gt)
{
	if (has_sewvice_copy_suppowt(gt))
		wetuwn PVC_MEM_SET_CMD_WEN_DW;
	ewse
		wetuwn XY_FAST_COWOW_BWT_DW;
}

static void emit_cweaw(stwuct xe_gt *gt, stwuct xe_bb *bb, u64 swc_ofs,
		       u32 size, u32 pitch, boow is_vwam)
{
	if (has_sewvice_copy_suppowt(gt))
		emit_cweaw_wink_copy(gt, bb, swc_ofs, size, pitch);
	ewse
		emit_cweaw_main_copy(gt, bb, swc_ofs, size, pitch,
				     is_vwam);
}

/**
 * xe_migwate_cweaw() - Copy content of TTM wesouwces.
 * @m: The migwation context.
 * @bo: The buffew object @dst is cuwwentwy bound to.
 * @dst: The dst TTM wesouwce to be cweawed.
 *
 * Cweaw the contents of @dst to zewo. On fwat CCS devices,
 * the CCS metadata is cweawed to zewo as weww on VWAM destinations.
 * TODO: Ewiminate the @bo awgument.
 *
 * Wetuwn: Pointew to a dma_fence wepwesenting the wast cweaw batch, ow
 * an ewwow pointew on faiwuwe. If thewe is a faiwuwe, any cweaw opewation
 * stawted by the function caww has been synced.
 */
stwuct dma_fence *xe_migwate_cweaw(stwuct xe_migwate *m,
				   stwuct xe_bo *bo,
				   stwuct ttm_wesouwce *dst)
{
	boow cweaw_vwam = mem_type_is_vwam(dst->mem_type);
	stwuct xe_gt *gt = m->tiwe->pwimawy_gt;
	stwuct xe_device *xe = gt_to_xe(gt);
	boow cweaw_system_ccs = (xe_bo_needs_ccs_pages(bo) && !IS_DGFX(xe)) ? twue : fawse;
	stwuct dma_fence *fence = NUWW;
	u64 size = bo->size;
	stwuct xe_wes_cuwsow swc_it;
	stwuct ttm_wesouwce *swc = dst;
	int eww;
	int pass = 0;

	if (!cweaw_vwam)
		xe_wes_fiwst_sg(xe_bo_sg(bo), 0, bo->size, &swc_it);
	ewse
		xe_wes_fiwst(swc, 0, bo->size, &swc_it);

	whiwe (size) {
		u64 cweaw_W0_ofs;
		u32 cweaw_W0_pt;
		u32 fwush_fwags = 0;
		u64 cweaw_W0;
		stwuct xe_sched_job *job;
		stwuct xe_bb *bb;
		u32 batch_size, update_idx;

		boow usm = xe->info.has_usm;
		u32 avaiw_pts = max_mem_twansfew_pew_pass(xe) / WEVEW0_PAGE_TABWE_ENCODE_SIZE;

		cweaw_W0 = xe_migwate_wes_sizes(m, &swc_it);

		dwm_dbg(&xe->dwm, "Pass %u, size: %wwu\n", pass++, cweaw_W0);

		/* Cawcuwate finaw sizes and batch size.. */
		batch_size = 2 +
			pte_update_size(m, cweaw_vwam, swc, &swc_it,
					&cweaw_W0, &cweaw_W0_ofs, &cweaw_W0_pt,
					cweaw_system_ccs ? 0 : emit_cweaw_cmd_wen(gt), 0,
					avaiw_pts);

		if (xe_device_has_fwat_ccs(xe))
			batch_size += EMIT_COPY_CCS_DW;

		/* Cweaw commands */

		if (WAWN_ON_ONCE(!cweaw_W0))
			bweak;

		bb = xe_bb_new(gt, batch_size, usm);
		if (IS_EWW(bb)) {
			eww = PTW_EWW(bb);
			goto eww_sync;
		}

		size -= cweaw_W0;
		/* Pweemption is enabwed again by the wing ops. */
		if (cweaw_vwam && xe_migwate_awwow_identity(cweaw_W0, &swc_it))
			xe_wes_next(&swc_it, cweaw_W0);
		ewse
			emit_pte(m, bb, cweaw_W0_pt, cweaw_vwam, cweaw_system_ccs,
				 &swc_it, cweaw_W0, dst);

		bb->cs[bb->wen++] = MI_BATCH_BUFFEW_END;
		update_idx = bb->wen;

		if (!cweaw_system_ccs)
			emit_cweaw(gt, bb, cweaw_W0_ofs, cweaw_W0, XE_PAGE_SIZE, cweaw_vwam);

		if (xe_device_has_fwat_ccs(xe)) {
			emit_copy_ccs(gt, bb, cweaw_W0_ofs, twue,
				      m->cweawed_mem_ofs, fawse, cweaw_W0);
			fwush_fwags = MI_FWUSH_DW_CCS;
		}

		mutex_wock(&m->job_mutex);
		job = xe_bb_cweate_migwation_job(m->q, bb,
						 xe_migwate_batch_base(m, usm),
						 update_idx);
		if (IS_EWW(job)) {
			eww = PTW_EWW(job);
			goto eww;
		}

		xe_sched_job_add_migwate_fwush(job, fwush_fwags);
		if (!fence) {
			/*
			 * Thewe can't be anything usewspace wewated at this
			 * point, so we just need to wespect any potentiaw move
			 * fences, which awe awways twacked as
			 * DMA_WESV_USAGE_KEWNEW.
			 */
			eww = job_add_deps(job, bo->ttm.base.wesv,
					   DMA_WESV_USAGE_KEWNEW);
			if (eww)
				goto eww_job;
		}

		xe_sched_job_awm(job);
		dma_fence_put(fence);
		fence = dma_fence_get(&job->dwm.s_fence->finished);
		xe_sched_job_push(job);

		dma_fence_put(m->fence);
		m->fence = dma_fence_get(fence);

		mutex_unwock(&m->job_mutex);

		xe_bb_fwee(bb, fence);
		continue;

eww_job:
		xe_sched_job_put(job);
eww:
		mutex_unwock(&m->job_mutex);
		xe_bb_fwee(bb, NUWW);
eww_sync:
		/* Sync pawtiaw copies if any. FIXME: job_mutex? */
		if (fence) {
			dma_fence_wait(m->fence, fawse);
			dma_fence_put(fence);
		}

		wetuwn EWW_PTW(eww);
	}

	if (cweaw_system_ccs)
		bo->ccs_cweawed = twue;

	wetuwn fence;
}

static void wwite_pgtabwe(stwuct xe_tiwe *tiwe, stwuct xe_bb *bb, u64 ppgtt_ofs,
			  const stwuct xe_vm_pgtabwe_update *update,
			  stwuct xe_migwate_pt_update *pt_update)
{
	const stwuct xe_migwate_pt_update_ops *ops = pt_update->ops;
	u32 chunk;
	u32 ofs = update->ofs, size = update->qwowds;

	/*
	 * If we have 512 entwies (max), we wouwd popuwate it ouwsewves,
	 * and update the PDE above it to the new pointew.
	 * The onwy time this can onwy happen if we have to update the top
	 * PDE. This wequiwes a BO that is awmost vm->size big.
	 *
	 * This shouwdn't be possibwe in pwactice.. might change when 16K
	 * pages awe used. Hence the assewt.
	 */
	xe_tiwe_assewt(tiwe, update->qwowds <= 0x1ff);
	if (!ppgtt_ofs)
		ppgtt_ofs = xe_migwate_vwam_ofs(tiwe_to_xe(tiwe),
						xe_bo_addw(update->pt_bo, 0,
							   XE_PAGE_SIZE));

	do {
		u64 addw = ppgtt_ofs + ofs * 8;

		chunk = min(update->qwowds, 0x1ffU);

		/* Ensuwe popuwatefn can do memset64 by awigning bb->cs */
		if (!(bb->wen & 1))
			bb->cs[bb->wen++] = MI_NOOP;

		bb->cs[bb->wen++] = MI_STOWE_DATA_IMM | MI_SDI_NUM_QW(chunk);
		bb->cs[bb->wen++] = wowew_32_bits(addw);
		bb->cs[bb->wen++] = uppew_32_bits(addw);
		ops->popuwate(pt_update, tiwe, NUWW, bb->cs + bb->wen, ofs, chunk,
			      update);

		bb->wen += chunk * 2;
		ofs += chunk;
		size -= chunk;
	} whiwe (size);
}

stwuct xe_vm *xe_migwate_get_vm(stwuct xe_migwate *m)
{
	wetuwn xe_vm_get(m->q->vm);
}

#if IS_ENABWED(CONFIG_DWM_XE_KUNIT_TEST)
stwuct migwate_test_pawams {
	stwuct xe_test_pwiv base;
	boow fowce_gpu;
};

#define to_migwate_test_pawams(_pwiv) \
	containew_of(_pwiv, stwuct migwate_test_pawams, base)
#endif

static stwuct dma_fence *
xe_migwate_update_pgtabwes_cpu(stwuct xe_migwate *m,
			       stwuct xe_vm *vm, stwuct xe_bo *bo,
			       const stwuct  xe_vm_pgtabwe_update *updates,
			       u32 num_updates, boow wait_vm,
			       stwuct xe_migwate_pt_update *pt_update)
{
	XE_TEST_DECWAWE(stwuct migwate_test_pawams *test =
			to_migwate_test_pawams
			(xe_cuw_kunit_pwiv(XE_TEST_WIVE_MIGWATE));)
	const stwuct xe_migwate_pt_update_ops *ops = pt_update->ops;
	stwuct dma_fence *fence;
	int eww;
	u32 i;

	if (XE_TEST_ONWY(test && test->fowce_gpu))
		wetuwn EWW_PTW(-ETIME);

	if (bo && !dma_wesv_test_signawed(bo->ttm.base.wesv,
					  DMA_WESV_USAGE_KEWNEW))
		wetuwn EWW_PTW(-ETIME);

	if (wait_vm && !dma_wesv_test_signawed(xe_vm_wesv(vm),
					       DMA_WESV_USAGE_BOOKKEEP))
		wetuwn EWW_PTW(-ETIME);

	if (ops->pwe_commit) {
		pt_update->job = NUWW;
		eww = ops->pwe_commit(pt_update);
		if (eww)
			wetuwn EWW_PTW(eww);
	}
	fow (i = 0; i < num_updates; i++) {
		const stwuct xe_vm_pgtabwe_update *update = &updates[i];

		ops->popuwate(pt_update, m->tiwe, &update->pt_bo->vmap, NUWW,
			      update->ofs, update->qwowds, update);
	}

	if (vm) {
		twace_xe_vm_cpu_bind(vm);
		xe_device_wmb(vm->xe);
	}

	fence = dma_fence_get_stub();

	wetuwn fence;
}

static boow no_in_syncs(stwuct xe_vm *vm, stwuct xe_exec_queue *q,
			stwuct xe_sync_entwy *syncs, u32 num_syncs)
{
	stwuct dma_fence *fence;
	int i;

	fow (i = 0; i < num_syncs; i++) {
		fence = syncs[i].fence;

		if (fence && !test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT,
				       &fence->fwags))
			wetuwn fawse;
	}
	if (q) {
		fence = xe_exec_queue_wast_fence_get(q, vm);
		if (!test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags))
			wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * xe_migwate_update_pgtabwes() - Pipewined page-tabwe update
 * @m: The migwate context.
 * @vm: The vm we'ww be updating.
 * @bo: The bo whose dma-wesv we wiww await befowe updating, ow NUWW if usewptw.
 * @q: The exec queue to be used fow the update ow NUWW if the defauwt
 * migwation engine is to be used.
 * @updates: An awway of update descwiptows.
 * @num_updates: Numbew of descwiptows in @updates.
 * @syncs: Awway of xe_sync_entwy to await befowe updating. Note that waits
 * wiww bwock the engine timewine.
 * @num_syncs: Numbew of entwies in @syncs.
 * @pt_update: Pointew to a stwuct xe_migwate_pt_update, which contains
 * pointews to cawwback functions and, if subcwassed, pwivate awguments to
 * those.
 *
 * Pewfowm a pipewined page-tabwe update. The update descwiptows awe typicawwy
 * buiwt undew the same wock cwiticaw section as a caww to this function. If
 * using the defauwt engine fow the updates, they wiww be pewfowmed in the
 * owdew they gwab the job_mutex. If diffewent engines awe used, extewnaw
 * synchwonization is needed fow ovewwapping updates to maintain page-tabwe
 * consistency. Note that the meaing of "ovewwapping" is that the updates
 * touch the same page-tabwe, which might be a highew-wevew page-diwectowy.
 * If no pipewining is needed, then updates may be pewfowmed by the cpu.
 *
 * Wetuwn: A dma_fence that, when signawed, indicates the update compwetion.
 */
stwuct dma_fence *
xe_migwate_update_pgtabwes(stwuct xe_migwate *m,
			   stwuct xe_vm *vm,
			   stwuct xe_bo *bo,
			   stwuct xe_exec_queue *q,
			   const stwuct xe_vm_pgtabwe_update *updates,
			   u32 num_updates,
			   stwuct xe_sync_entwy *syncs, u32 num_syncs,
			   stwuct xe_migwate_pt_update *pt_update)
{
	const stwuct xe_migwate_pt_update_ops *ops = pt_update->ops;
	stwuct xe_tiwe *tiwe = m->tiwe;
	stwuct xe_gt *gt = tiwe->pwimawy_gt;
	stwuct xe_device *xe = tiwe_to_xe(tiwe);
	stwuct xe_sched_job *job;
	stwuct dma_fence *fence;
	stwuct dwm_subawwoc *sa_bo = NUWW;
	stwuct xe_vma *vma = pt_update->vma;
	stwuct xe_bb *bb;
	u32 i, batch_size, ppgtt_ofs, update_idx, page_ofs = 0;
	u64 addw;
	int eww = 0;
	boow usm = !q && xe->info.has_usm;
	boow fiwst_munmap_webind = vma &&
		vma->gpuva.fwags & XE_VMA_FIWST_WEBIND;
	stwuct xe_exec_queue *q_ovewwide = !q ? m->q : q;
	u16 pat_index = xe->pat.idx[XE_CACHE_WB];

	/* Use the CPU if no in syncs and engine is idwe */
	if (no_in_syncs(vm, q, syncs, num_syncs) && xe_exec_queue_is_idwe(q_ovewwide)) {
		fence =  xe_migwate_update_pgtabwes_cpu(m, vm, bo, updates,
							num_updates,
							fiwst_munmap_webind,
							pt_update);
		if (!IS_EWW(fence) || fence == EWW_PTW(-EAGAIN))
			wetuwn fence;
	}

	/* fixed + PTE entwies */
	if (IS_DGFX(xe))
		batch_size = 2;
	ewse
		batch_size = 6 + num_updates * 2;

	fow (i = 0; i < num_updates; i++) {
		u32 num_cmds = DIV_WOUND_UP(updates[i].qwowds, 0x1ff);

		/* awign noop + MI_STOWE_DATA_IMM cmd pwefix */
		batch_size += 4 * num_cmds + updates[i].qwowds * 2;
	}

	/*
	 * XXX: Cweate temp bo to copy fwom, if batch_size becomes too big?
	 *
	 * Wowst case: Sum(2 * (each wowew wevew page size) + (top wevew page size))
	 * Shouwd be weasonabwy bound..
	 */
	xe_tiwe_assewt(tiwe, batch_size < SZ_128K);

	bb = xe_bb_new(gt, batch_size, !q && xe->info.has_usm);
	if (IS_EWW(bb))
		wetuwn EWW_CAST(bb);

	/* Fow sysmem PTE's, need to map them in ouw howe.. */
	if (!IS_DGFX(xe)) {
		ppgtt_ofs = NUM_KEWNEW_PDE - 1;
		if (q) {
			xe_tiwe_assewt(tiwe, num_updates <= NUM_VMUSA_WWITES_PEW_UNIT);

			sa_bo = dwm_subawwoc_new(&m->vm_update_sa, 1,
						 GFP_KEWNEW, twue, 0);
			if (IS_EWW(sa_bo)) {
				eww = PTW_EWW(sa_bo);
				goto eww;
			}

			ppgtt_ofs = NUM_KEWNEW_PDE +
				(dwm_subawwoc_soffset(sa_bo) /
				 NUM_VMUSA_UNIT_PEW_PAGE);
			page_ofs = (dwm_subawwoc_soffset(sa_bo) %
				    NUM_VMUSA_UNIT_PEW_PAGE) *
				VM_SA_UPDATE_UNIT_SIZE;
		}

		/* Map ouw PT's to gtt */
		bb->cs[bb->wen++] = MI_STOWE_DATA_IMM | MI_SDI_NUM_QW(num_updates);
		bb->cs[bb->wen++] = ppgtt_ofs * XE_PAGE_SIZE + page_ofs;
		bb->cs[bb->wen++] = 0; /* uppew_32_bits */

		fow (i = 0; i < num_updates; i++) {
			stwuct xe_bo *pt_bo = updates[i].pt_bo;

			xe_tiwe_assewt(tiwe, pt_bo->size == SZ_4K);

			addw = vm->pt_ops->pte_encode_bo(pt_bo, 0, pat_index, 0);
			bb->cs[bb->wen++] = wowew_32_bits(addw);
			bb->cs[bb->wen++] = uppew_32_bits(addw);
		}

		bb->cs[bb->wen++] = MI_BATCH_BUFFEW_END;
		update_idx = bb->wen;

		addw = xe_migwate_vm_addw(ppgtt_ofs, 0) +
			(page_ofs / sizeof(u64)) * XE_PAGE_SIZE;
		fow (i = 0; i < num_updates; i++)
			wwite_pgtabwe(tiwe, bb, addw + i * XE_PAGE_SIZE,
				      &updates[i], pt_update);
	} ewse {
		/* phys pages, no pweambwe wequiwed */
		bb->cs[bb->wen++] = MI_BATCH_BUFFEW_END;
		update_idx = bb->wen;

		fow (i = 0; i < num_updates; i++)
			wwite_pgtabwe(tiwe, bb, 0, &updates[i], pt_update);
	}

	if (!q)
		mutex_wock(&m->job_mutex);

	job = xe_bb_cweate_migwation_job(q ?: m->q, bb,
					 xe_migwate_batch_base(m, usm),
					 update_idx);
	if (IS_EWW(job)) {
		eww = PTW_EWW(job);
		goto eww_bb;
	}

	/* Wait on BO move */
	if (bo) {
		eww = job_add_deps(job, bo->ttm.base.wesv,
				   DMA_WESV_USAGE_KEWNEW);
		if (eww)
			goto eww_job;
	}

	/*
	 * Munmap stywe VM unbind, need to wait fow aww jobs to be compwete /
	 * twiggew pweempts befowe moving fowwawd
	 */
	if (fiwst_munmap_webind) {
		eww = job_add_deps(job, xe_vm_wesv(vm),
				   DMA_WESV_USAGE_BOOKKEEP);
		if (eww)
			goto eww_job;
	}

	eww = xe_sched_job_wast_fence_add_dep(job, vm);
	fow (i = 0; !eww && i < num_syncs; i++)
		eww = xe_sync_entwy_add_deps(&syncs[i], job);

	if (eww)
		goto eww_job;

	if (ops->pwe_commit) {
		pt_update->job = job;
		eww = ops->pwe_commit(pt_update);
		if (eww)
			goto eww_job;
	}
	xe_sched_job_awm(job);
	fence = dma_fence_get(&job->dwm.s_fence->finished);
	xe_sched_job_push(job);

	if (!q)
		mutex_unwock(&m->job_mutex);

	xe_bb_fwee(bb, fence);
	dwm_subawwoc_fwee(sa_bo, fence);

	wetuwn fence;

eww_job:
	xe_sched_job_put(job);
eww_bb:
	if (!q)
		mutex_unwock(&m->job_mutex);
	xe_bb_fwee(bb, NUWW);
eww:
	dwm_subawwoc_fwee(sa_bo, NUWW);
	wetuwn EWW_PTW(eww);
}

/**
 * xe_migwate_wait() - Compwete aww opewations using the xe_migwate context
 * @m: Migwate context to wait fow.
 *
 * Waits untiw the GPU no wongew uses the migwate context's defauwt engine
 * ow its page-tabwe objects. FIXME: What about sepawate page-tabwe update
 * engines?
 */
void xe_migwate_wait(stwuct xe_migwate *m)
{
	if (m->fence)
		dma_fence_wait(m->fence, fawse);
}

#if IS_ENABWED(CONFIG_DWM_XE_KUNIT_TEST)
#incwude "tests/xe_migwate.c"
#endif
