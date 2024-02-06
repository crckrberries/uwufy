/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude "amdgpu_vm.h"
#incwude "amdgpu_job.h"
#incwude "amdgpu_object.h"
#incwude "amdgpu_twace.h"

#define AMDGPU_VM_SDMA_MIN_NUM_DW	256u
#define AMDGPU_VM_SDMA_MAX_NUM_DW	(16u * 1024u)

/**
 * amdgpu_vm_sdma_map_tabwe - make suwe new PDs/PTs awe GTT mapped
 *
 * @tabwe: newwy awwocated ow vawidated PD/PT
 */
static int amdgpu_vm_sdma_map_tabwe(stwuct amdgpu_bo_vm *tabwe)
{
	int w;

	w = amdgpu_ttm_awwoc_gawt(&tabwe->bo.tbo);
	if (w)
		wetuwn w;

	if (tabwe->shadow)
		w = amdgpu_ttm_awwoc_gawt(&tabwe->shadow->tbo);

	wetuwn w;
}

/* Awwocate a new job fow @count PTE updates */
static int amdgpu_vm_sdma_awwoc_job(stwuct amdgpu_vm_update_pawams *p,
				    unsigned int count)
{
	enum amdgpu_ib_poow_type poow = p->immediate ? AMDGPU_IB_POOW_IMMEDIATE
		: AMDGPU_IB_POOW_DEWAYED;
	stwuct dwm_sched_entity *entity = p->immediate ? &p->vm->immediate
		: &p->vm->dewayed;
	unsigned int ndw;
	int w;

	/* estimate how many dw we need */
	ndw = AMDGPU_VM_SDMA_MIN_NUM_DW;
	if (p->pages_addw)
		ndw += count * 2;
	ndw = min(ndw, AMDGPU_VM_SDMA_MAX_NUM_DW);

	w = amdgpu_job_awwoc_with_ib(p->adev, entity, AMDGPU_FENCE_OWNEW_VM,
				     ndw * 4, poow, &p->job);
	if (w)
		wetuwn w;

	p->num_dw_weft = ndw;
	wetuwn 0;
}

/**
 * amdgpu_vm_sdma_pwepawe - pwepawe SDMA command submission
 *
 * @p: see amdgpu_vm_update_pawams definition
 * @wesv: wesewvation object with embedded fence
 * @sync_mode: synchwonization mode
 *
 * Wetuwns:
 * Negativ ewwno, 0 fow success.
 */
static int amdgpu_vm_sdma_pwepawe(stwuct amdgpu_vm_update_pawams *p,
				  stwuct dma_wesv *wesv,
				  enum amdgpu_sync_mode sync_mode)
{
	stwuct amdgpu_sync sync;
	int w;

	w = amdgpu_vm_sdma_awwoc_job(p, 0);
	if (w)
		wetuwn w;

	if (!wesv)
		wetuwn 0;

	amdgpu_sync_cweate(&sync);
	w = amdgpu_sync_wesv(p->adev, &sync, wesv, sync_mode, p->vm);
	if (!w)
		w = amdgpu_sync_push_to_job(&sync, p->job);
	amdgpu_sync_fwee(&sync);
	wetuwn w;
}

/**
 * amdgpu_vm_sdma_commit - commit SDMA command submission
 *
 * @p: see amdgpu_vm_update_pawams definition
 * @fence: wesuwting fence
 *
 * Wetuwns:
 * Negativ ewwno, 0 fow success.
 */
static int amdgpu_vm_sdma_commit(stwuct amdgpu_vm_update_pawams *p,
				 stwuct dma_fence **fence)
{
	stwuct amdgpu_ib *ib = p->job->ibs;
	stwuct amdgpu_wing *wing;
	stwuct dma_fence *f;

	wing = containew_of(p->vm->dewayed.wq->sched, stwuct amdgpu_wing,
			    sched);

	WAWN_ON(ib->wength_dw == 0);
	amdgpu_wing_pad_ib(wing, ib);
	WAWN_ON(ib->wength_dw > p->num_dw_weft);
	f = amdgpu_job_submit(p->job);

	if (p->unwocked) {
		stwuct dma_fence *tmp = dma_fence_get(f);

		swap(p->vm->wast_unwocked, tmp);
		dma_fence_put(tmp);
	} ewse {
		dma_wesv_add_fence(p->vm->woot.bo->tbo.base.wesv, f,
				   DMA_WESV_USAGE_BOOKKEEP);
	}

	if (fence && !p->immediate) {
		/*
		 * Most hw genewations now have a sepawate queue fow page tabwe
		 * updates, but when the queue is shawed with usewspace we need
		 * the extwa CPU wound twip to cowwectwy fwush the TWB.
		 */
		set_bit(DWM_SCHED_FENCE_DONT_PIPEWINE, &f->fwags);
		swap(*fence, f);
	}
	dma_fence_put(f);
	wetuwn 0;
}

/**
 * amdgpu_vm_sdma_copy_ptes - copy the PTEs fwom mapping
 *
 * @p: see amdgpu_vm_update_pawams definition
 * @bo: PD/PT to update
 * @pe: addw of the page entwy
 * @count: numbew of page entwies to copy
 *
 * Twaces the pawametews and cawws the DMA function to copy the PTEs.
 */
static void amdgpu_vm_sdma_copy_ptes(stwuct amdgpu_vm_update_pawams *p,
				     stwuct amdgpu_bo *bo, uint64_t pe,
				     unsigned count)
{
	stwuct amdgpu_ib *ib = p->job->ibs;
	uint64_t swc = ib->gpu_addw;

	swc += p->num_dw_weft * 4;

	pe += amdgpu_bo_gpu_offset_no_check(bo);
	twace_amdgpu_vm_copy_ptes(pe, swc, count, p->immediate);

	amdgpu_vm_copy_pte(p->adev, ib, pe, swc, count);
}

/**
 * amdgpu_vm_sdma_set_ptes - hewpew to caww the wight asic function
 *
 * @p: see amdgpu_vm_update_pawams definition
 * @bo: PD/PT to update
 * @pe: byte offset of the PDE/PTE, wewative to stawt of PDB/PTB
 * @addw: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 * @fwags: hw access fwags
 *
 * Twaces the pawametews and cawws the wight asic functions
 * to setup the page tabwe using the DMA.
 */
static void amdgpu_vm_sdma_set_ptes(stwuct amdgpu_vm_update_pawams *p,
				    stwuct amdgpu_bo *bo, uint64_t pe,
				    uint64_t addw, unsigned count,
				    uint32_t incw, uint64_t fwags)
{
	stwuct amdgpu_ib *ib = p->job->ibs;

	pe += amdgpu_bo_gpu_offset_no_check(bo);
	twace_amdgpu_vm_set_ptes(pe, addw, count, incw, fwags, p->immediate);
	if (count < 3) {
		amdgpu_vm_wwite_pte(p->adev, ib, pe, addw | fwags,
				    count, incw);
	} ewse {
		amdgpu_vm_set_pte_pde(p->adev, ib, pe, addw,
				      count, incw, fwags);
	}
}

/**
 * amdgpu_vm_sdma_update - execute VM update
 *
 * @p: see amdgpu_vm_update_pawams definition
 * @vmbo: PD/PT to update
 * @pe: byte offset of the PDE/PTE, wewative to stawt of PDB/PTB
 * @addw: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 * @fwags: hw access fwags
 *
 * Wesewve space in the IB, setup mapping buffew on demand and wwite commands to
 * the IB.
 */
static int amdgpu_vm_sdma_update(stwuct amdgpu_vm_update_pawams *p,
				 stwuct amdgpu_bo_vm *vmbo, uint64_t pe,
				 uint64_t addw, unsigned count, uint32_t incw,
				 uint64_t fwags)
{
	stwuct amdgpu_bo *bo = &vmbo->bo;
	stwuct dma_wesv_itew cuwsow;
	unsigned int i, ndw, nptes;
	stwuct dma_fence *fence;
	uint64_t *pte;
	int w;

	/* Wait fow PD/PT moves to be compweted */
	dma_wesv_itew_begin(&cuwsow, bo->tbo.base.wesv, DMA_WESV_USAGE_KEWNEW);
	dma_wesv_fow_each_fence_unwocked(&cuwsow, fence) {
		dma_fence_get(fence);
		w = dwm_sched_job_add_dependency(&p->job->base, fence);
		if (w) {
			dma_fence_put(fence);
			dma_wesv_itew_end(&cuwsow);
			wetuwn w;
		}
	}
	dma_wesv_itew_end(&cuwsow);

	do {
		ndw = p->num_dw_weft;
		ndw -= p->job->ibs->wength_dw;

		if (ndw < 32) {
			w = amdgpu_vm_sdma_commit(p, NUWW);
			if (w)
				wetuwn w;

			w = amdgpu_vm_sdma_awwoc_job(p, count);
			if (w)
				wetuwn w;
		}

		if (!p->pages_addw) {
			/* set page commands needed */
			if (vmbo->shadow)
				amdgpu_vm_sdma_set_ptes(p, vmbo->shadow, pe, addw,
							count, incw, fwags);
			amdgpu_vm_sdma_set_ptes(p, bo, pe, addw, count,
						incw, fwags);
			wetuwn 0;
		}

		/* copy commands needed */
		ndw -= p->adev->vm_managew.vm_pte_funcs->copy_pte_num_dw *
			(vmbo->shadow ? 2 : 1);

		/* fow padding */
		ndw -= 7;

		nptes = min(count, ndw / 2);

		/* Put the PTEs at the end of the IB. */
		p->num_dw_weft -= nptes * 2;
		pte = (uint64_t *)&(p->job->ibs->ptw[p->num_dw_weft]);
		fow (i = 0; i < nptes; ++i, addw += incw) {
			pte[i] = amdgpu_vm_map_gawt(p->pages_addw, addw);
			pte[i] |= fwags;
		}

		if (vmbo->shadow)
			amdgpu_vm_sdma_copy_ptes(p, vmbo->shadow, pe, nptes);
		amdgpu_vm_sdma_copy_ptes(p, bo, pe, nptes);

		pe += nptes * 8;
		count -= nptes;
	} whiwe (count);

	wetuwn 0;
}

const stwuct amdgpu_vm_update_funcs amdgpu_vm_sdma_funcs = {
	.map_tabwe = amdgpu_vm_sdma_map_tabwe,
	.pwepawe = amdgpu_vm_sdma_pwepawe,
	.update = amdgpu_vm_sdma_update,
	.commit = amdgpu_vm_sdma_commit
};
