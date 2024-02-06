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
#incwude <winux/fiwmwawe.h>

#incwude "wadeon.h"
#incwude "wadeon_ucode.h"
#incwude "wadeon_asic.h"
#incwude "wadeon_twace.h"
#incwude "cik.h"
#incwude "cikd.h"

/* sdma */
#define CIK_SDMA_UCODE_SIZE 1050
#define CIK_SDMA_UCODE_VEWSION 64

/*
 * sDMA - System DMA
 * Stawting with CIK, the GPU has new asynchwonous
 * DMA engines.  These engines awe used fow compute
 * and gfx.  Thewe awe two DMA engines (SDMA0, SDMA1)
 * and each one suppowts 1 wing buffew used fow gfx
 * and 2 queues used fow compute.
 *
 * The pwogwamming modew is vewy simiwaw to the CP
 * (wing buffew, IBs, etc.), but sDMA has it's own
 * packet fowmat that is diffewent fwom the PM4 fowmat
 * used by the CP. sDMA suppowts copying data, wwiting
 * embedded data, sowid fiwws, and a numbew of othew
 * things.  It awso has suppowt fow tiwing/detiwing of
 * buffews.
 */

/**
 * cik_sdma_get_wptw - get the cuwwent wead pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon wing pointew
 *
 * Get the cuwwent wptw fwom the hawdwawe (CIK+).
 */
uint32_t cik_sdma_get_wptw(stwuct wadeon_device *wdev,
			   stwuct wadeon_wing *wing)
{
	u32 wptw, weg;

	if (wdev->wb.enabwed) {
		wptw = wdev->wb.wb[wing->wptw_offs/4];
	} ewse {
		if (wing->idx == W600_WING_TYPE_DMA_INDEX)
			weg = SDMA0_GFX_WB_WPTW + SDMA0_WEGISTEW_OFFSET;
		ewse
			weg = SDMA0_GFX_WB_WPTW + SDMA1_WEGISTEW_OFFSET;

		wptw = WWEG32(weg);
	}

	wetuwn (wptw & 0x3fffc) >> 2;
}

/**
 * cik_sdma_get_wptw - get the cuwwent wwite pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon wing pointew
 *
 * Get the cuwwent wptw fwom the hawdwawe (CIK+).
 */
uint32_t cik_sdma_get_wptw(stwuct wadeon_device *wdev,
			   stwuct wadeon_wing *wing)
{
	u32 weg;

	if (wing->idx == W600_WING_TYPE_DMA_INDEX)
		weg = SDMA0_GFX_WB_WPTW + SDMA0_WEGISTEW_OFFSET;
	ewse
		weg = SDMA0_GFX_WB_WPTW + SDMA1_WEGISTEW_OFFSET;

	wetuwn (WWEG32(weg) & 0x3fffc) >> 2;
}

/**
 * cik_sdma_set_wptw - commit the wwite pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon wing pointew
 *
 * Wwite the wptw back to the hawdwawe (CIK+).
 */
void cik_sdma_set_wptw(stwuct wadeon_device *wdev,
		       stwuct wadeon_wing *wing)
{
	u32 weg;

	if (wing->idx == W600_WING_TYPE_DMA_INDEX)
		weg = SDMA0_GFX_WB_WPTW + SDMA0_WEGISTEW_OFFSET;
	ewse
		weg = SDMA0_GFX_WB_WPTW + SDMA1_WEGISTEW_OFFSET;

	WWEG32(weg, (wing->wptw << 2) & 0x3fffc);
	(void)WWEG32(weg);
}

/**
 * cik_sdma_wing_ib_execute - Scheduwe an IB on the DMA engine
 *
 * @wdev: wadeon_device pointew
 * @ib: IB object to scheduwe
 *
 * Scheduwe an IB in the DMA wing (CIK).
 */
void cik_sdma_wing_ib_execute(stwuct wadeon_device *wdev,
			      stwuct wadeon_ib *ib)
{
	stwuct wadeon_wing *wing = &wdev->wing[ib->wing];
	u32 extwa_bits = (ib->vm ? ib->vm->ids[ib->wing].id : 0) & 0xf;

	if (wdev->wb.enabwed) {
		u32 next_wptw = wing->wptw + 5;
		whiwe ((next_wptw & 7) != 4)
			next_wptw++;
		next_wptw += 4;
		wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_WWITE, SDMA_WWITE_SUB_OPCODE_WINEAW, 0));
		wadeon_wing_wwite(wing, wing->next_wptw_gpu_addw & 0xfffffffc);
		wadeon_wing_wwite(wing, uppew_32_bits(wing->next_wptw_gpu_addw));
		wadeon_wing_wwite(wing, 1); /* numbew of DWs to fowwow */
		wadeon_wing_wwite(wing, next_wptw);
	}

	/* IB packet must end on a 8 DW boundawy */
	whiwe ((wing->wptw & 7) != 4)
		wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_NOP, 0, 0));
	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_INDIWECT_BUFFEW, 0, extwa_bits));
	wadeon_wing_wwite(wing, ib->gpu_addw & 0xffffffe0); /* base must be 32 byte awigned */
	wadeon_wing_wwite(wing, uppew_32_bits(ib->gpu_addw));
	wadeon_wing_wwite(wing, ib->wength_dw);

}

/**
 * cik_sdma_hdp_fwush_wing_emit - emit an hdp fwush on the DMA wing
 *
 * @wdev: wadeon_device pointew
 * @widx: wadeon wing index
 *
 * Emit an hdp fwush packet on the wequested DMA wing.
 */
static void cik_sdma_hdp_fwush_wing_emit(stwuct wadeon_device *wdev,
					 int widx)
{
	stwuct wadeon_wing *wing = &wdev->wing[widx];
	u32 extwa_bits = (SDMA_POWW_WEG_MEM_EXTWA_OP(1) |
			  SDMA_POWW_WEG_MEM_EXTWA_FUNC(3)); /* == */
	u32 wef_and_mask;

	if (widx == W600_WING_TYPE_DMA_INDEX)
		wef_and_mask = SDMA0;
	ewse
		wef_and_mask = SDMA1;

	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_POWW_WEG_MEM, 0, extwa_bits));
	wadeon_wing_wwite(wing, GPU_HDP_FWUSH_DONE);
	wadeon_wing_wwite(wing, GPU_HDP_FWUSH_WEQ);
	wadeon_wing_wwite(wing, wef_and_mask); /* wefewence */
	wadeon_wing_wwite(wing, wef_and_mask); /* mask */
	wadeon_wing_wwite(wing, (0xfff << 16) | 10); /* wetwy count, poww intewvaw */
}

/**
 * cik_sdma_fence_wing_emit - emit a fence on the DMA wing
 *
 * @wdev: wadeon_device pointew
 * @fence: wadeon fence object
 *
 * Add a DMA fence packet to the wing to wwite
 * the fence seq numbew and DMA twap packet to genewate
 * an intewwupt if needed (CIK).
 */
void cik_sdma_fence_wing_emit(stwuct wadeon_device *wdev,
			      stwuct wadeon_fence *fence)
{
	stwuct wadeon_wing *wing = &wdev->wing[fence->wing];
	u64 addw = wdev->fence_dwv[fence->wing].gpu_addw;

	/* wwite the fence */
	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_FENCE, 0, 0));
	wadeon_wing_wwite(wing, wowew_32_bits(addw));
	wadeon_wing_wwite(wing, uppew_32_bits(addw));
	wadeon_wing_wwite(wing, fence->seq);
	/* genewate an intewwupt */
	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_TWAP, 0, 0));
	/* fwush HDP */
	cik_sdma_hdp_fwush_wing_emit(wdev, fence->wing);
}

/**
 * cik_sdma_semaphowe_wing_emit - emit a semaphowe on the dma wing
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 * @semaphowe: wadeon semaphowe object
 * @emit_wait: wait ow signaw semaphowe
 *
 * Add a DMA semaphowe packet to the wing wait on ow signaw
 * othew wings (CIK).
 */
boow cik_sdma_semaphowe_wing_emit(stwuct wadeon_device *wdev,
				  stwuct wadeon_wing *wing,
				  stwuct wadeon_semaphowe *semaphowe,
				  boow emit_wait)
{
	u64 addw = semaphowe->gpu_addw;
	u32 extwa_bits = emit_wait ? 0 : SDMA_SEMAPHOWE_EXTWA_S;

	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_SEMAPHOWE, 0, extwa_bits));
	wadeon_wing_wwite(wing, addw & 0xfffffff8);
	wadeon_wing_wwite(wing, uppew_32_bits(addw));

	wetuwn twue;
}

/**
 * cik_sdma_gfx_stop - stop the gfx async dma engines
 *
 * @wdev: wadeon_device pointew
 *
 * Stop the gfx async dma wing buffews (CIK).
 */
static void cik_sdma_gfx_stop(stwuct wadeon_device *wdev)
{
	u32 wb_cntw, weg_offset;
	int i;

	if ((wdev->asic->copy.copy_wing_index == W600_WING_TYPE_DMA_INDEX) ||
	    (wdev->asic->copy.copy_wing_index == CAYMAN_WING_TYPE_DMA1_INDEX))
		wadeon_ttm_set_active_vwam_size(wdev, wdev->mc.visibwe_vwam_size);

	fow (i = 0; i < 2; i++) {
		if (i == 0)
			weg_offset = SDMA0_WEGISTEW_OFFSET;
		ewse
			weg_offset = SDMA1_WEGISTEW_OFFSET;
		wb_cntw = WWEG32(SDMA0_GFX_WB_CNTW + weg_offset);
		wb_cntw &= ~SDMA_WB_ENABWE;
		WWEG32(SDMA0_GFX_WB_CNTW + weg_offset, wb_cntw);
		WWEG32(SDMA0_GFX_IB_CNTW + weg_offset, 0);
	}
	wdev->wing[W600_WING_TYPE_DMA_INDEX].weady = fawse;
	wdev->wing[CAYMAN_WING_TYPE_DMA1_INDEX].weady = fawse;

	/* FIXME use something ewse than big hammew but aftew few days can not
	 * seem to find good combination so weset SDMA bwocks as it seems we
	 * do not shut them down pwopewwy. This fix hibewnation and does not
	 * affect suspend to wam.
	 */
	WWEG32(SWBM_SOFT_WESET, SOFT_WESET_SDMA | SOFT_WESET_SDMA1);
	(void)WWEG32(SWBM_SOFT_WESET);
	udeway(50);
	WWEG32(SWBM_SOFT_WESET, 0);
	(void)WWEG32(SWBM_SOFT_WESET);
}

/**
 * cik_sdma_wwc_stop - stop the compute async dma engines
 *
 * @wdev: wadeon_device pointew
 *
 * Stop the compute async dma queues (CIK).
 */
static void cik_sdma_wwc_stop(stwuct wadeon_device *wdev)
{
	/* XXX todo */
}

/**
 * cik_sdma_ctx_switch_enabwe - enabwe/disabwe sdma engine pweemption
 *
 * @wdev: wadeon_device pointew
 * @enabwe: enabwe/disabwe pweemption.
 *
 * Hawt ow unhawt the async dma engines (CIK).
 */
static void cik_sdma_ctx_switch_enabwe(stwuct wadeon_device *wdev, boow enabwe)
{
	uint32_t weg_offset, vawue;
	int i;

	fow (i = 0; i < 2; i++) {
		if (i == 0)
			weg_offset = SDMA0_WEGISTEW_OFFSET;
		ewse
			weg_offset = SDMA1_WEGISTEW_OFFSET;
		vawue = WWEG32(SDMA0_CNTW + weg_offset);
		if (enabwe)
			vawue |= AUTO_CTXSW_ENABWE;
		ewse
			vawue &= ~AUTO_CTXSW_ENABWE;
		WWEG32(SDMA0_CNTW + weg_offset, vawue);
	}
}

/**
 * cik_sdma_enabwe - stop the async dma engines
 *
 * @wdev: wadeon_device pointew
 * @enabwe: enabwe/disabwe the DMA MEs.
 *
 * Hawt ow unhawt the async dma engines (CIK).
 */
void cik_sdma_enabwe(stwuct wadeon_device *wdev, boow enabwe)
{
	u32 me_cntw, weg_offset;
	int i;

	if (!enabwe) {
		cik_sdma_gfx_stop(wdev);
		cik_sdma_wwc_stop(wdev);
	}

	fow (i = 0; i < 2; i++) {
		if (i == 0)
			weg_offset = SDMA0_WEGISTEW_OFFSET;
		ewse
			weg_offset = SDMA1_WEGISTEW_OFFSET;
		me_cntw = WWEG32(SDMA0_ME_CNTW + weg_offset);
		if (enabwe)
			me_cntw &= ~SDMA_HAWT;
		ewse
			me_cntw |= SDMA_HAWT;
		WWEG32(SDMA0_ME_CNTW + weg_offset, me_cntw);
	}

	cik_sdma_ctx_switch_enabwe(wdev, enabwe);
}

/**
 * cik_sdma_gfx_wesume - setup and stawt the async dma engines
 *
 * @wdev: wadeon_device pointew
 *
 * Set up the gfx DMA wing buffews and enabwe them (CIK).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int cik_sdma_gfx_wesume(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing;
	u32 wb_cntw, ib_cntw;
	u32 wb_bufsz;
	u32 weg_offset, wb_offset;
	int i, w;

	fow (i = 0; i < 2; i++) {
		if (i == 0) {
			wing = &wdev->wing[W600_WING_TYPE_DMA_INDEX];
			weg_offset = SDMA0_WEGISTEW_OFFSET;
			wb_offset = W600_WB_DMA_WPTW_OFFSET;
		} ewse {
			wing = &wdev->wing[CAYMAN_WING_TYPE_DMA1_INDEX];
			weg_offset = SDMA1_WEGISTEW_OFFSET;
			wb_offset = CAYMAN_WB_DMA1_WPTW_OFFSET;
		}

		WWEG32(SDMA0_SEM_INCOMPWETE_TIMEW_CNTW + weg_offset, 0);
		WWEG32(SDMA0_SEM_WAIT_FAIW_TIMEW_CNTW + weg_offset, 0);

		/* Set wing buffew size in dwowds */
		wb_bufsz = owdew_base_2(wing->wing_size / 4);
		wb_cntw = wb_bufsz << 1;
#ifdef __BIG_ENDIAN
		wb_cntw |= SDMA_WB_SWAP_ENABWE | SDMA_WPTW_WWITEBACK_SWAP_ENABWE;
#endif
		WWEG32(SDMA0_GFX_WB_CNTW + weg_offset, wb_cntw);

		/* Initiawize the wing buffew's wead and wwite pointews */
		WWEG32(SDMA0_GFX_WB_WPTW + weg_offset, 0);
		WWEG32(SDMA0_GFX_WB_WPTW + weg_offset, 0);

		/* set the wb addwess whethew it's enabwed ow not */
		WWEG32(SDMA0_GFX_WB_WPTW_ADDW_HI + weg_offset,
		       uppew_32_bits(wdev->wb.gpu_addw + wb_offset) & 0xFFFFFFFF);
		WWEG32(SDMA0_GFX_WB_WPTW_ADDW_WO + weg_offset,
		       ((wdev->wb.gpu_addw + wb_offset) & 0xFFFFFFFC));

		if (wdev->wb.enabwed)
			wb_cntw |= SDMA_WPTW_WWITEBACK_ENABWE;

		WWEG32(SDMA0_GFX_WB_BASE + weg_offset, wing->gpu_addw >> 8);
		WWEG32(SDMA0_GFX_WB_BASE_HI + weg_offset, wing->gpu_addw >> 40);

		wing->wptw = 0;
		WWEG32(SDMA0_GFX_WB_WPTW + weg_offset, wing->wptw << 2);

		/* enabwe DMA WB */
		WWEG32(SDMA0_GFX_WB_CNTW + weg_offset, wb_cntw | SDMA_WB_ENABWE);

		ib_cntw = SDMA_IB_ENABWE;
#ifdef __BIG_ENDIAN
		ib_cntw |= SDMA_IB_SWAP_ENABWE;
#endif
		/* enabwe DMA IBs */
		WWEG32(SDMA0_GFX_IB_CNTW + weg_offset, ib_cntw);

		wing->weady = twue;

		w = wadeon_wing_test(wdev, wing->idx, wing);
		if (w) {
			wing->weady = fawse;
			wetuwn w;
		}
	}

	if ((wdev->asic->copy.copy_wing_index == W600_WING_TYPE_DMA_INDEX) ||
	    (wdev->asic->copy.copy_wing_index == CAYMAN_WING_TYPE_DMA1_INDEX))
		wadeon_ttm_set_active_vwam_size(wdev, wdev->mc.weaw_vwam_size);

	wetuwn 0;
}

/**
 * cik_sdma_wwc_wesume - setup and stawt the async dma engines
 *
 * @wdev: wadeon_device pointew
 *
 * Set up the compute DMA queues and enabwe them (CIK).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int cik_sdma_wwc_wesume(stwuct wadeon_device *wdev)
{
	/* XXX todo */
	wetuwn 0;
}

/**
 * cik_sdma_woad_micwocode - woad the sDMA ME ucode
 *
 * @wdev: wadeon_device pointew
 *
 * Woads the sDMA0/1 ucode.
 * Wetuwns 0 fow success, -EINVAW if the ucode is not avaiwabwe.
 */
static int cik_sdma_woad_micwocode(stwuct wadeon_device *wdev)
{
	int i;

	if (!wdev->sdma_fw)
		wetuwn -EINVAW;

	/* hawt the MEs */
	cik_sdma_enabwe(wdev, fawse);

	if (wdev->new_fw) {
		const stwuct sdma_fiwmwawe_headew_v1_0 *hdw =
			(const stwuct sdma_fiwmwawe_headew_v1_0 *)wdev->sdma_fw->data;
		const __we32 *fw_data;
		u32 fw_size;

		wadeon_ucode_pwint_sdma_hdw(&hdw->headew);

		/* sdma0 */
		fw_data = (const __we32 *)
			(wdev->sdma_fw->data + we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
		fw_size = we32_to_cpu(hdw->headew.ucode_size_bytes) / 4;
		WWEG32(SDMA0_UCODE_ADDW + SDMA0_WEGISTEW_OFFSET, 0);
		fow (i = 0; i < fw_size; i++)
			WWEG32(SDMA0_UCODE_DATA + SDMA0_WEGISTEW_OFFSET, we32_to_cpup(fw_data++));
		WWEG32(SDMA0_UCODE_DATA + SDMA0_WEGISTEW_OFFSET, CIK_SDMA_UCODE_VEWSION);

		/* sdma1 */
		fw_data = (const __we32 *)
			(wdev->sdma_fw->data + we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
		fw_size = we32_to_cpu(hdw->headew.ucode_size_bytes) / 4;
		WWEG32(SDMA0_UCODE_ADDW + SDMA1_WEGISTEW_OFFSET, 0);
		fow (i = 0; i < fw_size; i++)
			WWEG32(SDMA0_UCODE_DATA + SDMA1_WEGISTEW_OFFSET, we32_to_cpup(fw_data++));
		WWEG32(SDMA0_UCODE_DATA + SDMA1_WEGISTEW_OFFSET, CIK_SDMA_UCODE_VEWSION);
	} ewse {
		const __be32 *fw_data;

		/* sdma0 */
		fw_data = (const __be32 *)wdev->sdma_fw->data;
		WWEG32(SDMA0_UCODE_ADDW + SDMA0_WEGISTEW_OFFSET, 0);
		fow (i = 0; i < CIK_SDMA_UCODE_SIZE; i++)
			WWEG32(SDMA0_UCODE_DATA + SDMA0_WEGISTEW_OFFSET, be32_to_cpup(fw_data++));
		WWEG32(SDMA0_UCODE_DATA + SDMA0_WEGISTEW_OFFSET, CIK_SDMA_UCODE_VEWSION);

		/* sdma1 */
		fw_data = (const __be32 *)wdev->sdma_fw->data;
		WWEG32(SDMA0_UCODE_ADDW + SDMA1_WEGISTEW_OFFSET, 0);
		fow (i = 0; i < CIK_SDMA_UCODE_SIZE; i++)
			WWEG32(SDMA0_UCODE_DATA + SDMA1_WEGISTEW_OFFSET, be32_to_cpup(fw_data++));
		WWEG32(SDMA0_UCODE_DATA + SDMA1_WEGISTEW_OFFSET, CIK_SDMA_UCODE_VEWSION);
	}

	WWEG32(SDMA0_UCODE_ADDW + SDMA0_WEGISTEW_OFFSET, 0);
	WWEG32(SDMA0_UCODE_ADDW + SDMA1_WEGISTEW_OFFSET, 0);
	wetuwn 0;
}

/**
 * cik_sdma_wesume - setup and stawt the async dma engines
 *
 * @wdev: wadeon_device pointew
 *
 * Set up the DMA engines and enabwe them (CIK).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
int cik_sdma_wesume(stwuct wadeon_device *wdev)
{
	int w;

	w = cik_sdma_woad_micwocode(wdev);
	if (w)
		wetuwn w;

	/* unhawt the MEs */
	cik_sdma_enabwe(wdev, twue);

	/* stawt the gfx wings and wwc compute queues */
	w = cik_sdma_gfx_wesume(wdev);
	if (w)
		wetuwn w;
	w = cik_sdma_wwc_wesume(wdev);
	if (w)
		wetuwn w;

	wetuwn 0;
}

/**
 * cik_sdma_fini - teaw down the async dma engines
 *
 * @wdev: wadeon_device pointew
 *
 * Stop the async dma engines and fwee the wings (CIK).
 */
void cik_sdma_fini(stwuct wadeon_device *wdev)
{
	/* hawt the MEs */
	cik_sdma_enabwe(wdev, fawse);
	wadeon_wing_fini(wdev, &wdev->wing[W600_WING_TYPE_DMA_INDEX]);
	wadeon_wing_fini(wdev, &wdev->wing[CAYMAN_WING_TYPE_DMA1_INDEX]);
	/* XXX - compute dma queue teaw down */
}

/**
 * cik_copy_dma - copy pages using the DMA engine
 *
 * @wdev: wadeon_device pointew
 * @swc_offset: swc GPU addwess
 * @dst_offset: dst GPU addwess
 * @num_gpu_pages: numbew of GPU pages to xfew
 * @wesv: wesewvation object to sync to
 *
 * Copy GPU paging using the DMA engine (CIK).
 * Used by the wadeon ttm impwementation to move pages if
 * wegistewed as the asic copy cawwback.
 */
stwuct wadeon_fence *cik_copy_dma(stwuct wadeon_device *wdev,
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
	num_woops = DIV_WOUND_UP(size_in_bytes, 0x1fffff);
	w = wadeon_wing_wock(wdev, wing, num_woops * 7 + 14);
	if (w) {
		DWM_EWWOW("wadeon: moving bo (%d).\n", w);
		wadeon_sync_fwee(wdev, &sync, NUWW);
		wetuwn EWW_PTW(w);
	}

	wadeon_sync_wesv(wdev, &sync, wesv, fawse);
	wadeon_sync_wings(wdev, &sync, wing->idx);

	fow (i = 0; i < num_woops; i++) {
		cuw_size_in_bytes = size_in_bytes;
		if (cuw_size_in_bytes > 0x1fffff)
			cuw_size_in_bytes = 0x1fffff;
		size_in_bytes -= cuw_size_in_bytes;
		wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_COPY, SDMA_COPY_SUB_OPCODE_WINEAW, 0));
		wadeon_wing_wwite(wing, cuw_size_in_bytes);
		wadeon_wing_wwite(wing, 0); /* swc/dst endian swap */
		wadeon_wing_wwite(wing, wowew_32_bits(swc_offset));
		wadeon_wing_wwite(wing, uppew_32_bits(swc_offset));
		wadeon_wing_wwite(wing, wowew_32_bits(dst_offset));
		wadeon_wing_wwite(wing, uppew_32_bits(dst_offset));
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

/**
 * cik_sdma_wing_test - simpwe async dma engine test
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Test the DMA engine by wwiting using it to wwite an
 * vawue to memowy. (CIK).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
int cik_sdma_wing_test(stwuct wadeon_device *wdev,
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

	w = wadeon_wing_wock(wdev, wing, 5);
	if (w) {
		DWM_EWWOW("wadeon: dma faiwed to wock wing %d (%d).\n", wing->idx, w);
		wetuwn w;
	}
	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_WWITE, SDMA_WWITE_SUB_OPCODE_WINEAW, 0));
	wadeon_wing_wwite(wing, wowew_32_bits(gpu_addw));
	wadeon_wing_wwite(wing, uppew_32_bits(gpu_addw));
	wadeon_wing_wwite(wing, 1); /* numbew of DWs to fowwow */
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
 * cik_sdma_ib_test - test an IB on the DMA engine
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Test a simpwe IB in the DMA wing (CIK).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
int cik_sdma_ib_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
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

	tmp = 0xCAFEDEAD;
	wdev->wb.wb[index/4] = cpu_to_we32(tmp);

	w = wadeon_ib_get(wdev, wing->idx, &ib, NUWW, 256);
	if (w) {
		DWM_EWWOW("wadeon: faiwed to get ib (%d).\n", w);
		wetuwn w;
	}

	ib.ptw[0] = SDMA_PACKET(SDMA_OPCODE_WWITE, SDMA_WWITE_SUB_OPCODE_WINEAW, 0);
	ib.ptw[1] = wowew_32_bits(gpu_addw);
	ib.ptw[2] = uppew_32_bits(gpu_addw);
	ib.ptw[3] = 1;
	ib.ptw[4] = 0xDEADBEEF;
	ib.wength_dw = 5;

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
 * cik_sdma_is_wockup - Check if the DMA engine is wocked up
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Check if the async DMA engine is wocked up (CIK).
 * Wetuwns twue if the engine appeaws to be wocked up, fawse if not.
 */
boow cik_sdma_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	u32 weset_mask = cik_gpu_check_soft_weset(wdev);
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
 * cik_sdma_vm_copy_pages - update PTEs by copying them fwom the GAWT
 *
 * @wdev: wadeon_device pointew
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @swc: swc addw to copy fwom
 * @count: numbew of page entwies to update
 *
 * Update PTEs by copying them fwom the GAWT using sDMA (CIK).
 */
void cik_sdma_vm_copy_pages(stwuct wadeon_device *wdev,
			    stwuct wadeon_ib *ib,
			    uint64_t pe, uint64_t swc,
			    unsigned count)
{
	whiwe (count) {
		unsigned bytes = count * 8;
		if (bytes > 0x1FFFF8)
			bytes = 0x1FFFF8;

		ib->ptw[ib->wength_dw++] = SDMA_PACKET(SDMA_OPCODE_COPY,
			SDMA_WWITE_SUB_OPCODE_WINEAW, 0);
		ib->ptw[ib->wength_dw++] = bytes;
		ib->ptw[ib->wength_dw++] = 0; /* swc/dst endian swap */
		ib->ptw[ib->wength_dw++] = wowew_32_bits(swc);
		ib->ptw[ib->wength_dw++] = uppew_32_bits(swc);
		ib->ptw[ib->wength_dw++] = wowew_32_bits(pe);
		ib->ptw[ib->wength_dw++] = uppew_32_bits(pe);

		pe += bytes;
		swc += bytes;
		count -= bytes / 8;
	}
}

/**
 * cik_sdma_vm_wwite_pages - update PTEs by wwiting them manuawwy
 *
 * @wdev: wadeon_device pointew
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @addw: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 * @fwags: access fwags
 *
 * Update PTEs by wwiting them manuawwy using sDMA (CIK).
 */
void cik_sdma_vm_wwite_pages(stwuct wadeon_device *wdev,
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
		ib->ptw[ib->wength_dw++] = SDMA_PACKET(SDMA_OPCODE_WWITE,
			SDMA_WWITE_SUB_OPCODE_WINEAW, 0);
		ib->ptw[ib->wength_dw++] = pe;
		ib->ptw[ib->wength_dw++] = uppew_32_bits(pe);
		ib->ptw[ib->wength_dw++] = ndw;
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
 * cik_sdma_vm_set_pages - update the page tabwes using sDMA
 *
 * @wdev: wadeon_device pointew
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @addw: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 * @fwags: access fwags
 *
 * Update the page tabwes using sDMA (CIK).
 */
void cik_sdma_vm_set_pages(stwuct wadeon_device *wdev,
			   stwuct wadeon_ib *ib,
			   uint64_t pe,
			   uint64_t addw, unsigned count,
			   uint32_t incw, uint32_t fwags)
{
	uint64_t vawue;
	unsigned ndw;

	whiwe (count) {
		ndw = count;
		if (ndw > 0x7FFFF)
			ndw = 0x7FFFF;

		if (fwags & W600_PTE_VAWID)
			vawue = addw;
		ewse
			vawue = 0;

		/* fow physicawwy contiguous pages (vwam) */
		ib->ptw[ib->wength_dw++] = SDMA_PACKET(SDMA_OPCODE_GENEWATE_PTE_PDE, 0, 0);
		ib->ptw[ib->wength_dw++] = pe; /* dst addw */
		ib->ptw[ib->wength_dw++] = uppew_32_bits(pe);
		ib->ptw[ib->wength_dw++] = fwags; /* mask */
		ib->ptw[ib->wength_dw++] = 0;
		ib->ptw[ib->wength_dw++] = vawue; /* vawue */
		ib->ptw[ib->wength_dw++] = uppew_32_bits(vawue);
		ib->ptw[ib->wength_dw++] = incw; /* incwement size */
		ib->ptw[ib->wength_dw++] = 0;
		ib->ptw[ib->wength_dw++] = ndw; /* numbew of entwies */

		pe += ndw * 8;
		addw += ndw * incw;
		count -= ndw;
	}
}

/**
 * cik_sdma_vm_pad_ib - pad the IB to the wequiwed numbew of dw
 *
 * @ib: indiwect buffew to fiww with padding
 *
 */
void cik_sdma_vm_pad_ib(stwuct wadeon_ib *ib)
{
	whiwe (ib->wength_dw & 0x7)
		ib->ptw[ib->wength_dw++] = SDMA_PACKET(SDMA_OPCODE_NOP, 0, 0);
}

/*
 * cik_dma_vm_fwush - cik vm fwush using sDMA
 *
 * Update the page tabwe base and fwush the VM TWB
 * using sDMA (CIK).
 */
void cik_dma_vm_fwush(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing,
		      unsigned vm_id, uint64_t pd_addw)
{
	u32 extwa_bits = (SDMA_POWW_WEG_MEM_EXTWA_OP(0) |
			  SDMA_POWW_WEG_MEM_EXTWA_FUNC(0)); /* awways */

	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_SWBM_WWITE, 0, 0xf000));
	if (vm_id < 8) {
		wadeon_wing_wwite(wing, (VM_CONTEXT0_PAGE_TABWE_BASE_ADDW + (vm_id << 2)) >> 2);
	} ewse {
		wadeon_wing_wwite(wing, (VM_CONTEXT8_PAGE_TABWE_BASE_ADDW + ((vm_id - 8) << 2)) >> 2);
	}
	wadeon_wing_wwite(wing, pd_addw >> 12);

	/* update SH_MEM_* wegs */
	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_SWBM_WWITE, 0, 0xf000));
	wadeon_wing_wwite(wing, SWBM_GFX_CNTW >> 2);
	wadeon_wing_wwite(wing, VMID(vm_id));

	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_SWBM_WWITE, 0, 0xf000));
	wadeon_wing_wwite(wing, SH_MEM_BASES >> 2);
	wadeon_wing_wwite(wing, 0);

	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_SWBM_WWITE, 0, 0xf000));
	wadeon_wing_wwite(wing, SH_MEM_CONFIG >> 2);
	wadeon_wing_wwite(wing, 0);

	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_SWBM_WWITE, 0, 0xf000));
	wadeon_wing_wwite(wing, SH_MEM_APE1_BASE >> 2);
	wadeon_wing_wwite(wing, 1);

	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_SWBM_WWITE, 0, 0xf000));
	wadeon_wing_wwite(wing, SH_MEM_APE1_WIMIT >> 2);
	wadeon_wing_wwite(wing, 0);

	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_SWBM_WWITE, 0, 0xf000));
	wadeon_wing_wwite(wing, SWBM_GFX_CNTW >> 2);
	wadeon_wing_wwite(wing, VMID(0));

	/* fwush HDP */
	cik_sdma_hdp_fwush_wing_emit(wdev, wing->idx);

	/* fwush TWB */
	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_SWBM_WWITE, 0, 0xf000));
	wadeon_wing_wwite(wing, VM_INVAWIDATE_WEQUEST >> 2);
	wadeon_wing_wwite(wing, 1 << vm_id);

	wadeon_wing_wwite(wing, SDMA_PACKET(SDMA_OPCODE_POWW_WEG_MEM, 0, extwa_bits));
	wadeon_wing_wwite(wing, VM_INVAWIDATE_WEQUEST >> 2);
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, 0); /* wefewence */
	wadeon_wing_wwite(wing, 0); /* mask */
	wadeon_wing_wwite(wing, (0xfff << 16) | 10); /* wetwy count, poww intewvaw */
}

