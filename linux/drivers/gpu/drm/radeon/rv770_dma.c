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
#incwude "wv770d.h"

/**
 * wv770_copy_dma - copy pages using the DMA engine
 *
 * @wdev: wadeon_device pointew
 * @swc_offset: swc GPU addwess
 * @dst_offset: dst GPU addwess
 * @num_gpu_pages: numbew of GPU pages to xfew
 * @wesv: wesewvation object to sync to
 *
 * Copy GPU paging using the DMA engine (w7xx).
 * Used by the wadeon ttm impwementation to move pages if
 * wegistewed as the asic copy cawwback.
 */
stwuct wadeon_fence *wv770_copy_dma(stwuct wadeon_device *wdev,
				    uint64_t swc_offset, uint64_t dst_offset,
				    unsigned num_gpu_pages,
				    stwuct dma_wesv *wesv)
{
	stwuct wadeon_fence *fence;
	stwuct wadeon_sync sync;
	int wing_index = wdev->asic->copy.dma_wing_index;
	stwuct wadeon_wing *wing = &wdev->wing[wing_index];
	u32 size_in_dw, cuw_size_in_dw;
	int i, num_woops;
	int w = 0;

	wadeon_sync_cweate(&sync);

	size_in_dw = (num_gpu_pages << WADEON_GPU_PAGE_SHIFT) / 4;
	num_woops = DIV_WOUND_UP(size_in_dw, 0xFFFF);
	w = wadeon_wing_wock(wdev, wing, num_woops * 5 + 8);
	if (w) {
		DWM_EWWOW("wadeon: moving bo (%d).\n", w);
		wadeon_sync_fwee(wdev, &sync, NUWW);
		wetuwn EWW_PTW(w);
	}

	wadeon_sync_wesv(wdev, &sync, wesv, fawse);
	wadeon_sync_wings(wdev, &sync, wing->idx);

	fow (i = 0; i < num_woops; i++) {
		cuw_size_in_dw = size_in_dw;
		if (cuw_size_in_dw > 0xFFFF)
			cuw_size_in_dw = 0xFFFF;
		size_in_dw -= cuw_size_in_dw;
		wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_COPY, 0, 0, cuw_size_in_dw));
		wadeon_wing_wwite(wing, dst_offset & 0xfffffffc);
		wadeon_wing_wwite(wing, swc_offset & 0xfffffffc);
		wadeon_wing_wwite(wing, uppew_32_bits(dst_offset) & 0xff);
		wadeon_wing_wwite(wing, uppew_32_bits(swc_offset) & 0xff);
		swc_offset += cuw_size_in_dw * 4;
		dst_offset += cuw_size_in_dw * 4;
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
