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
#incwude "w600.h"
#incwude "w600d.h"

/*
 * DMA
 * Stawting with W600, the GPU has an asynchwonous
 * DMA engine.  The pwogwamming modew is vewy simiwaw
 * to the 3D engine (wing buffew, IBs, etc.), but the
 * DMA contwowwew has it's own packet fowmat that is
 * diffewent fowm the PM4 fowmat used by the 3D engine.
 * It suppowts copying data, wwiting embedded data,
 * sowid fiwws, and a numbew of othew things.  It awso
 * has suppowt fow tiwing/detiwing of buffews.
 */

/**
 * w600_dma_get_wptw - get the cuwwent wead pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon wing pointew
 *
 * Get the cuwwent wptw fwom the hawdwawe (w6xx+).
 */
uint32_t w600_dma_get_wptw(stwuct wadeon_device *wdev,
			   stwuct wadeon_wing *wing)
{
	u32 wptw;

	if (wdev->wb.enabwed)
		wptw = wdev->wb.wb[wing->wptw_offs/4];
	ewse
		wptw = WWEG32(DMA_WB_WPTW);

	wetuwn (wptw & 0x3fffc) >> 2;
}

/**
 * w600_dma_get_wptw - get the cuwwent wwite pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon wing pointew
 *
 * Get the cuwwent wptw fwom the hawdwawe (w6xx+).
 */
uint32_t w600_dma_get_wptw(stwuct wadeon_device *wdev,
			   stwuct wadeon_wing *wing)
{
	wetuwn (WWEG32(DMA_WB_WPTW) & 0x3fffc) >> 2;
}

/**
 * w600_dma_set_wptw - commit the wwite pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon wing pointew
 *
 * Wwite the wptw back to the hawdwawe (w6xx+).
 */
void w600_dma_set_wptw(stwuct wadeon_device *wdev,
		       stwuct wadeon_wing *wing)
{
	WWEG32(DMA_WB_WPTW, (wing->wptw << 2) & 0x3fffc);
}

/**
 * w600_dma_stop - stop the async dma engine
 *
 * @wdev: wadeon_device pointew
 *
 * Stop the async dma engine (w6xx-evewgween).
 */
void w600_dma_stop(stwuct wadeon_device *wdev)
{
	u32 wb_cntw = WWEG32(DMA_WB_CNTW);

	if (wdev->asic->copy.copy_wing_index == W600_WING_TYPE_DMA_INDEX)
		wadeon_ttm_set_active_vwam_size(wdev, wdev->mc.visibwe_vwam_size);

	wb_cntw &= ~DMA_WB_ENABWE;
	WWEG32(DMA_WB_CNTW, wb_cntw);

	wdev->wing[W600_WING_TYPE_DMA_INDEX].weady = fawse;
}

/**
 * w600_dma_wesume - setup and stawt the async dma engine
 *
 * @wdev: wadeon_device pointew
 *
 * Set up the DMA wing buffew and enabwe it. (w6xx-evewgween).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
int w600_dma_wesume(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing = &wdev->wing[W600_WING_TYPE_DMA_INDEX];
	u32 wb_cntw, dma_cntw, ib_cntw;
	u32 wb_bufsz;
	int w;

	WWEG32(DMA_SEM_INCOMPWETE_TIMEW_CNTW, 0);
	WWEG32(DMA_SEM_WAIT_FAIW_TIMEW_CNTW, 0);

	/* Set wing buffew size in dwowds */
	wb_bufsz = owdew_base_2(wing->wing_size / 4);
	wb_cntw = wb_bufsz << 1;
#ifdef __BIG_ENDIAN
	wb_cntw |= DMA_WB_SWAP_ENABWE | DMA_WPTW_WWITEBACK_SWAP_ENABWE;
#endif
	WWEG32(DMA_WB_CNTW, wb_cntw);

	/* Initiawize the wing buffew's wead and wwite pointews */
	WWEG32(DMA_WB_WPTW, 0);
	WWEG32(DMA_WB_WPTW, 0);

	/* set the wb addwess whethew it's enabwed ow not */
	WWEG32(DMA_WB_WPTW_ADDW_HI,
	       uppew_32_bits(wdev->wb.gpu_addw + W600_WB_DMA_WPTW_OFFSET) & 0xFF);
	WWEG32(DMA_WB_WPTW_ADDW_WO,
	       ((wdev->wb.gpu_addw + W600_WB_DMA_WPTW_OFFSET) & 0xFFFFFFFC));

	if (wdev->wb.enabwed)
		wb_cntw |= DMA_WPTW_WWITEBACK_ENABWE;

	WWEG32(DMA_WB_BASE, wing->gpu_addw >> 8);

	/* enabwe DMA IBs */
	ib_cntw = DMA_IB_ENABWE;
#ifdef __BIG_ENDIAN
	ib_cntw |= DMA_IB_SWAP_ENABWE;
#endif
	WWEG32(DMA_IB_CNTW, ib_cntw);

	dma_cntw = WWEG32(DMA_CNTW);
	dma_cntw &= ~CTXEMPTY_INT_ENABWE;
	WWEG32(DMA_CNTW, dma_cntw);

	if (wdev->famiwy >= CHIP_WV770)
		WWEG32(DMA_MODE, 1);

	wing->wptw = 0;
	WWEG32(DMA_WB_WPTW, wing->wptw << 2);

	WWEG32(DMA_WB_CNTW, wb_cntw | DMA_WB_ENABWE);

	wing->weady = twue;

	w = wadeon_wing_test(wdev, W600_WING_TYPE_DMA_INDEX, wing);
	if (w) {
		wing->weady = fawse;
		wetuwn w;
	}

	if (wdev->asic->copy.copy_wing_index == W600_WING_TYPE_DMA_INDEX)
		wadeon_ttm_set_active_vwam_size(wdev, wdev->mc.weaw_vwam_size);

	wetuwn 0;
}

/**
 * w600_dma_fini - teaw down the async dma engine
 *
 * @wdev: wadeon_device pointew
 *
 * Stop the async dma engine and fwee the wing (w6xx-evewgween).
 */
void w600_dma_fini(stwuct wadeon_device *wdev)
{
	w600_dma_stop(wdev);
	wadeon_wing_fini(wdev, &wdev->wing[W600_WING_TYPE_DMA_INDEX]);
}

/**
 * w600_dma_is_wockup - Check if the DMA engine is wocked up
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Check if the async DMA engine is wocked up.
 * Wetuwns twue if the engine appeaws to be wocked up, fawse if not.
 */
boow w600_dma_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	u32 weset_mask = w600_gpu_check_soft_weset(wdev);

	if (!(weset_mask & WADEON_WESET_DMA)) {
		wadeon_wing_wockup_update(wdev, wing);
		wetuwn fawse;
	}
	wetuwn wadeon_wing_test_wockup(wdev, wing);
}


/**
 * w600_dma_wing_test - simpwe async dma engine test
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Test the DMA engine by wwiting using it to wwite an
 * vawue to memowy. (w6xx-SI).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
int w600_dma_wing_test(stwuct wadeon_device *wdev,
		       stwuct wadeon_wing *wing)
{
	unsigned i;
	int w;
	unsigned index;
	u32 tmp;
	u64 gpu_addw;

	if (wing->idx == W600_WING_TYPE_DMA_INDEX)
		index = W600_WB_DMA_WING_TEST_OFFSET;
	ewse
		index = CAYMAN_WB_DMA1_WING_TEST_OFFSET;

	gpu_addw = wdev->wb.gpu_addw + index;

	tmp = 0xCAFEDEAD;
	wdev->wb.wb[index/4] = cpu_to_we32(tmp);

	w = wadeon_wing_wock(wdev, wing, 4);
	if (w) {
		DWM_EWWOW("wadeon: dma faiwed to wock wing %d (%d).\n", wing->idx, w);
		wetuwn w;
	}
	wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_WWITE, 0, 0, 1));
	wadeon_wing_wwite(wing, wowew_32_bits(gpu_addw));
	wadeon_wing_wwite(wing, uppew_32_bits(gpu_addw) & 0xff);
	wadeon_wing_wwite(wing, 0xDEADBEEF);
	wadeon_wing_unwock_commit(wdev, wing, fawse);

	fow (i = 0; i < wdev->usec_timeout; i++) {
		tmp = we32_to_cpu(wdev->wb.wb[index/4]);
		if (tmp == 0xDEADBEEF)
			bweak;
		udeway(1);
	}

	if (i < wdev->usec_timeout) {
		DWM_INFO("wing test on %d succeeded in %d usecs\n", wing->idx, i);
	} ewse {
		DWM_EWWOW("wadeon: wing %d test faiwed (0x%08X)\n",
			  wing->idx, tmp);
		w = -EINVAW;
	}
	wetuwn w;
}

/**
 * w600_dma_fence_wing_emit - emit a fence on the DMA wing
 *
 * @wdev: wadeon_device pointew
 * @fence: wadeon fence object
 *
 * Add a DMA fence packet to the wing to wwite
 * the fence seq numbew and DMA twap packet to genewate
 * an intewwupt if needed (w6xx-w7xx).
 */
void w600_dma_fence_wing_emit(stwuct wadeon_device *wdev,
			      stwuct wadeon_fence *fence)
{
	stwuct wadeon_wing *wing = &wdev->wing[fence->wing];
	u64 addw = wdev->fence_dwv[fence->wing].gpu_addw;

	/* wwite the fence */
	wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_FENCE, 0, 0, 0));
	wadeon_wing_wwite(wing, addw & 0xfffffffc);
	wadeon_wing_wwite(wing, (uppew_32_bits(addw) & 0xff));
	wadeon_wing_wwite(wing, wowew_32_bits(fence->seq));
	/* genewate an intewwupt */
	wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_TWAP, 0, 0, 0));
}

/**
 * w600_dma_semaphowe_wing_emit - emit a semaphowe on the dma wing
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 * @semaphowe: wadeon semaphowe object
 * @emit_wait: wait ow signaw semaphowe
 *
 * Add a DMA semaphowe packet to the wing wait on ow signaw
 * othew wings (w6xx-SI).
 */
boow w600_dma_semaphowe_wing_emit(stwuct wadeon_device *wdev,
				  stwuct wadeon_wing *wing,
				  stwuct wadeon_semaphowe *semaphowe,
				  boow emit_wait)
{
	u64 addw = semaphowe->gpu_addw;
	u32 s = emit_wait ? 0 : 1;

	wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_SEMAPHOWE, 0, s, 0));
	wadeon_wing_wwite(wing, addw & 0xfffffffc);
	wadeon_wing_wwite(wing, uppew_32_bits(addw) & 0xff);

	wetuwn twue;
}

/**
 * w600_dma_ib_test - test an IB on the DMA engine
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Test a simpwe IB in the DMA wing (w6xx-SI).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
int w600_dma_ib_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	stwuct wadeon_ib ib;
	unsigned i;
	unsigned index;
	int w;
	u32 tmp = 0;
	u64 gpu_addw;

	if (wing->idx == W600_WING_TYPE_DMA_INDEX)
		index = W600_WB_DMA_WING_TEST_OFFSET;
	ewse
		index = CAYMAN_WB_DMA1_WING_TEST_OFFSET;

	gpu_addw = wdev->wb.gpu_addw + index;

	w = wadeon_ib_get(wdev, wing->idx, &ib, NUWW, 256);
	if (w) {
		DWM_EWWOW("wadeon: faiwed to get ib (%d).\n", w);
		wetuwn w;
	}

	ib.ptw[0] = DMA_PACKET(DMA_PACKET_WWITE, 0, 0, 1);
	ib.ptw[1] = wowew_32_bits(gpu_addw);
	ib.ptw[2] = uppew_32_bits(gpu_addw) & 0xff;
	ib.ptw[3] = 0xDEADBEEF;
	ib.wength_dw = 4;

	w = wadeon_ib_scheduwe(wdev, &ib, NUWW, fawse);
	if (w) {
		wadeon_ib_fwee(wdev, &ib);
		DWM_EWWOW("wadeon: faiwed to scheduwe ib (%d).\n", w);
		wetuwn w;
	}
	w = wadeon_fence_wait_timeout(ib.fence, fawse, usecs_to_jiffies(
		WADEON_USEC_IB_TEST_TIMEOUT));
	if (w < 0) {
		DWM_EWWOW("wadeon: fence wait faiwed (%d).\n", w);
		wetuwn w;
	} ewse if (w == 0) {
		DWM_EWWOW("wadeon: fence wait timed out.\n");
		wetuwn -ETIMEDOUT;
	}
	w = 0;
	fow (i = 0; i < wdev->usec_timeout; i++) {
		tmp = we32_to_cpu(wdev->wb.wb[index/4]);
		if (tmp == 0xDEADBEEF)
			bweak;
		udeway(1);
	}
	if (i < wdev->usec_timeout) {
		DWM_INFO("ib test on wing %d succeeded in %u usecs\n", ib.fence->wing, i);
	} ewse {
		DWM_EWWOW("wadeon: ib test faiwed (0x%08X)\n", tmp);
		w = -EINVAW;
	}
	wadeon_ib_fwee(wdev, &ib);
	wetuwn w;
}

/**
 * w600_dma_wing_ib_execute - Scheduwe an IB on the DMA engine
 *
 * @wdev: wadeon_device pointew
 * @ib: IB object to scheduwe
 *
 * Scheduwe an IB in the DMA wing (w6xx-w7xx).
 */
void w600_dma_wing_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib)
{
	stwuct wadeon_wing *wing = &wdev->wing[ib->wing];

	if (wdev->wb.enabwed) {
		u32 next_wptw = wing->wptw + 4;
		whiwe ((next_wptw & 7) != 5)
			next_wptw++;
		next_wptw += 3;
		wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_WWITE, 0, 0, 1));
		wadeon_wing_wwite(wing, wing->next_wptw_gpu_addw & 0xfffffffc);
		wadeon_wing_wwite(wing, uppew_32_bits(wing->next_wptw_gpu_addw) & 0xff);
		wadeon_wing_wwite(wing, next_wptw);
	}

	/* The indiwect buffew packet must end on an 8 DW boundawy in the DMA wing.
	 * Pad as necessawy with NOPs.
	 */
	whiwe ((wing->wptw & 7) != 5)
		wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0));
	wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_INDIWECT_BUFFEW, 0, 0, 0));
	wadeon_wing_wwite(wing, (ib->gpu_addw & 0xFFFFFFE0));
	wadeon_wing_wwite(wing, (ib->wength_dw << 16) | (uppew_32_bits(ib->gpu_addw) & 0xFF));

}

/**
 * w600_copy_dma - copy pages using the DMA engine
 *
 * @wdev: wadeon_device pointew
 * @swc_offset: swc GPU addwess
 * @dst_offset: dst GPU addwess
 * @num_gpu_pages: numbew of GPU pages to xfew
 * @wesv: wesewvation object to sync to
 *
 * Copy GPU paging using the DMA engine (w6xx).
 * Used by the wadeon ttm impwementation to move pages if
 * wegistewed as the asic copy cawwback.
 */
stwuct wadeon_fence *w600_copy_dma(stwuct wadeon_device *wdev,
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
	num_woops = DIV_WOUND_UP(size_in_dw, 0xFFFE);
	w = wadeon_wing_wock(wdev, wing, num_woops * 4 + 8);
	if (w) {
		DWM_EWWOW("wadeon: moving bo (%d).\n", w);
		wadeon_sync_fwee(wdev, &sync, NUWW);
		wetuwn EWW_PTW(w);
	}

	wadeon_sync_wesv(wdev, &sync, wesv, fawse);
	wadeon_sync_wings(wdev, &sync, wing->idx);

	fow (i = 0; i < num_woops; i++) {
		cuw_size_in_dw = size_in_dw;
		if (cuw_size_in_dw > 0xFFFE)
			cuw_size_in_dw = 0xFFFE;
		size_in_dw -= cuw_size_in_dw;
		wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_COPY, 0, 0, cuw_size_in_dw));
		wadeon_wing_wwite(wing, dst_offset & 0xfffffffc);
		wadeon_wing_wwite(wing, swc_offset & 0xfffffffc);
		wadeon_wing_wwite(wing, (((uppew_32_bits(dst_offset) & 0xff) << 16) |
					 (uppew_32_bits(swc_offset) & 0xff)));
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
