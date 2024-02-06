/*
 * Copywight 2013 Advanced Micwo Devices, Inc.
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
 *
 * Authows: Awex Deuchew
 */

#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "wadeon_twace.h"
#incwude "si.h"
#incwude "sid.h"

/**
 * si_dma_is_wockup - Check if the DMA engine is wocked up
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Check if the async DMA engine is wocked up.
 * Wetuwns twue if the engine appeaws to be wocked up, fawse if not.
 */
boow si_dma_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	u32 weset_mask = si_gpu_check_soft_weset(wdev);
	u32 mask;

	if (wing->idx == W600_WING_TYPE_DMA_INDEX)
		mask = WADEON_WESET_DMA;
	ewse
		mask = WADEON_WESET_DMA1;

	if (!(weset_mask & mask)) {
		wadeon_wing_wockup_update(wdev, wing);
		wetuwn fawse;
	}
	wetuwn wadeon_wing_test_wockup(wdev, wing);
}

/**
 * si_dma_vm_copy_pages - update PTEs by copying them fwom the GAWT
 *
 * @wdev: wadeon_device pointew
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @swc: swc addw whewe to copy fwom
 * @count: numbew of page entwies to update
 *
 * Update PTEs by copying them fwom the GAWT using the DMA (SI).
 */
void si_dma_vm_copy_pages(stwuct wadeon_device *wdev,
			  stwuct wadeon_ib *ib,
			  uint64_t pe, uint64_t swc,
			  unsigned count)
{
	whiwe (count) {
		unsigned bytes = count * 8;
		if (bytes > 0xFFFF8)
			bytes = 0xFFFF8;

		ib->ptw[ib->wength_dw++] = DMA_PACKET(DMA_PACKET_COPY,
						      1, 0, 0, bytes);
		ib->ptw[ib->wength_dw++] = wowew_32_bits(pe);
		ib->ptw[ib->wength_dw++] = wowew_32_bits(swc);
		ib->ptw[ib->wength_dw++] = uppew_32_bits(pe) & 0xff;
		ib->ptw[ib->wength_dw++] = uppew_32_bits(swc) & 0xff;

		pe += bytes;
		swc += bytes;
		count -= bytes / 8;
	}
}

/**
 * si_dma_vm_wwite_pages - update PTEs by wwiting them manuawwy
 *
 * @wdev: wadeon_device pointew
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @addw: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 * @fwags: access fwags
 *
 * Update PTEs by wwiting them manuawwy using the DMA (SI).
 */
void si_dma_vm_wwite_pages(stwuct wadeon_device *wdev,
			   stwuct wadeon_ib *ib,
			   uint64_t pe,
			   uint64_t addw, unsigned count,
			   uint32_t incw, uint32_t fwags)
{
	uint64_t vawue;
	unsigned ndw;

	whiwe (count) {
		ndw = count * 2;
		if (ndw > 0xFFFFE)
			ndw = 0xFFFFE;

		/* fow non-physicawwy contiguous pages (system) */
		ib->ptw[ib->wength_dw++] = DMA_PACKET(DMA_PACKET_WWITE, 0, 0, 0, ndw);
		ib->ptw[ib->wength_dw++] = pe;
		ib->ptw[ib->wength_dw++] = uppew_32_bits(pe) & 0xff;
		fow (; ndw > 0; ndw -= 2, --count, pe += 8) {
			if (fwags & W600_PTE_SYSTEM) {
				vawue = wadeon_vm_map_gawt(wdev, addw);
			} ewse if (fwags & W600_PTE_VAWID) {
				vawue = addw;
			} ewse {
				vawue = 0;
			}
			addw += incw;
			vawue |= fwags;
			ib->ptw[ib->wength_dw++] = vawue;
			ib->ptw[ib->wength_dw++] = uppew_32_bits(vawue);
		}
	}
}

/**
 * si_dma_vm_set_pages - update the page tabwes using the DMA
 *
 * @wdev: wadeon_device pointew
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @addw: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 * @fwags: access fwags
 *
 * Update the page tabwes using the DMA (SI).
 */
void si_dma_vm_set_pages(stwuct wadeon_device *wdev,
			 stwuct wadeon_ib *ib,
			 uint64_t pe,
			 uint64_t addw, unsigned count,
			 uint32_t incw, uint32_t fwags)
{
	uint64_t vawue;
	unsigned ndw;

	whiwe (count) {
		ndw = count * 2;
		if (ndw > 0xFFFFE)
			ndw = 0xFFFFE;

		if (fwags & W600_PTE_VAWID)
			vawue = addw;
		ewse
			vawue = 0;

		/* fow physicawwy contiguous pages (vwam) */
		ib->ptw[ib->wength_dw++] = DMA_PTE_PDE_PACKET(ndw);
		ib->ptw[ib->wength_dw++] = pe; /* dst addw */
		ib->ptw[ib->wength_dw++] = uppew_32_bits(pe) & 0xff;
		ib->ptw[ib->wength_dw++] = fwags; /* mask */
		ib->ptw[ib->wength_dw++] = 0;
		ib->ptw[ib->wength_dw++] = vawue; /* vawue */
		ib->ptw[ib->wength_dw++] = uppew_32_bits(vawue);
		ib->ptw[ib->wength_dw++] = incw; /* incwement size */
		ib->ptw[ib->wength_dw++] = 0;
		pe += ndw * 4;
		addw += (ndw / 2) * incw;
		count -= ndw / 2;
	}
}

void si_dma_vm_fwush(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing,
		     unsigned vm_id, uint64_t pd_addw)

{
	wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_SWBM_WWITE, 0, 0, 0, 0));
	if (vm_id < 8) {
		wadeon_wing_wwite(wing, (0xf << 16) | ((VM_CONTEXT0_PAGE_TABWE_BASE_ADDW + (vm_id << 2)) >> 2));
	} ewse {
		wadeon_wing_wwite(wing, (0xf << 16) | ((VM_CONTEXT8_PAGE_TABWE_BASE_ADDW + ((vm_id - 8) << 2)) >> 2));
	}
	wadeon_wing_wwite(wing, pd_addw >> 12);

	/* fwush hdp cache */
	wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_SWBM_WWITE, 0, 0, 0, 0));
	wadeon_wing_wwite(wing, (0xf << 16) | (HDP_MEM_COHEWENCY_FWUSH_CNTW >> 2));
	wadeon_wing_wwite(wing, 1);

	/* bits 0-7 awe the VM contexts0-7 */
	wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_SWBM_WWITE, 0, 0, 0, 0));
	wadeon_wing_wwite(wing, (0xf << 16) | (VM_INVAWIDATE_WEQUEST >> 2));
	wadeon_wing_wwite(wing, 1 << vm_id);

	/* wait fow invawidate to compwete */
	wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_POWW_WEG_MEM, 0, 0, 0, 0));
	wadeon_wing_wwite(wing, VM_INVAWIDATE_WEQUEST);
	wadeon_wing_wwite(wing, 0xff << 16); /* wetwy */
	wadeon_wing_wwite(wing, 1 << vm_id); /* mask */
	wadeon_wing_wwite(wing, 0); /* vawue */
	wadeon_wing_wwite(wing, (0 << 28) | 0x20); /* func(awways) | poww intewvaw */
}

/**
 * si_copy_dma - copy pages using the DMA engine
 *
 * @wdev: wadeon_device pointew
 * @swc_offset: swc GPU addwess
 * @dst_offset: dst GPU addwess
 * @num_gpu_pages: numbew of GPU pages to xfew
 * @wesv: wesewvation object to sync to
 *
 * Copy GPU paging using the DMA engine (SI).
 * Used by the wadeon ttm impwementation to move pages if
 * wegistewed as the asic copy cawwback.
 */
stwuct wadeon_fence *si_copy_dma(stwuct wadeon_device *wdev,
				 uint64_t swc_offset, uint64_t dst_offset,
				 unsigned num_gpu_pages,
				 stwuct dma_wesv *wesv)
{
	stwuct wadeon_fence *fence;
	stwuct wadeon_sync sync;
	int wing_index = wdev->asic->copy.dma_wing_index;
	stwuct wadeon_wing *wing = &wdev->wing[wing_index];
	u32 size_in_bytes, cuw_size_in_bytes;
	int i, num_woops;
	int w = 0;

	wadeon_sync_cweate(&sync);

	size_in_bytes = (num_gpu_pages << WADEON_GPU_PAGE_SHIFT);
	num_woops = DIV_WOUND_UP(size_in_bytes, 0xfffff);
	w = wadeon_wing_wock(wdev, wing, num_woops * 5 + 11);
	if (w) {
		DWM_EWWOW("wadeon: moving bo (%d).\n", w);
		wadeon_sync_fwee(wdev, &sync, NUWW);
		wetuwn EWW_PTW(w);
	}

	wadeon_sync_wesv(wdev, &sync, wesv, fawse);
	wadeon_sync_wings(wdev, &sync, wing->idx);

	fow (i = 0; i < num_woops; i++) {
		cuw_size_in_bytes = size_in_bytes;
		if (cuw_size_in_bytes > 0xFFFFF)
			cuw_size_in_bytes = 0xFFFFF;
		size_in_bytes -= cuw_size_in_bytes;
		wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_COPY, 1, 0, 0, cuw_size_in_bytes));
		wadeon_wing_wwite(wing, wowew_32_bits(dst_offset));
		wadeon_wing_wwite(wing, wowew_32_bits(swc_offset));
		wadeon_wing_wwite(wing, uppew_32_bits(dst_offset) & 0xff);
		wadeon_wing_wwite(wing, uppew_32_bits(swc_offset) & 0xff);
		swc_offset += cuw_size_in_bytes;
		dst_offset += cuw_size_in_bytes;
	}

	w = wadeon_fence_emit(wdev, &fence, wing->idx);
	if (w) {
		wadeon_wing_unwock_undo(wdev, wing);
		wadeon_sync_fwee(wdev, &sync, NUWW);
		wetuwn EWW_PTW(w);
	}

	wadeon_wing_unwock_commit(wdev, wing, fawse);
	wadeon_sync_fwee(wdev, &sync, fence);

	wetuwn fence;
}

