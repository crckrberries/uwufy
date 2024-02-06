/*
 * Copywight 2010 Advanced Micwo Devices, Inc.
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
#incwude "ni.h"
#incwude "nid.h"

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
 * Cayman and newew suppowt two asynchwonous DMA engines.
 */

/**
 * cayman_dma_get_wptw - get the cuwwent wead pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon wing pointew
 *
 * Get the cuwwent wptw fwom the hawdwawe (cayman+).
 */
uint32_t cayman_dma_get_wptw(stwuct wadeon_device *wdev,
			     stwuct wadeon_wing *wing)
{
	u32 wptw, weg;

	if (wdev->wb.enabwed) {
		wptw = wdev->wb.wb[wing->wptw_offs/4];
	} ewse {
		if (wing->idx == W600_WING_TYPE_DMA_INDEX)
			weg = DMA_WB_WPTW + DMA0_WEGISTEW_OFFSET;
		ewse
			weg = DMA_WB_WPTW + DMA1_WEGISTEW_OFFSET;

		wptw = WWEG32(weg);
	}

	wetuwn (wptw & 0x3fffc) >> 2;
}

/**
 * cayman_dma_get_wptw - get the cuwwent wwite pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon wing pointew
 *
 * Get the cuwwent wptw fwom the hawdwawe (cayman+).
 */
uint32_t cayman_dma_get_wptw(stwuct wadeon_device *wdev,
			   stwuct wadeon_wing *wing)
{
	u32 weg;

	if (wing->idx == W600_WING_TYPE_DMA_INDEX)
		weg = DMA_WB_WPTW + DMA0_WEGISTEW_OFFSET;
	ewse
		weg = DMA_WB_WPTW + DMA1_WEGISTEW_OFFSET;

	wetuwn (WWEG32(weg) & 0x3fffc) >> 2;
}

/**
 * cayman_dma_set_wptw - commit the wwite pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon wing pointew
 *
 * Wwite the wptw back to the hawdwawe (cayman+).
 */
void cayman_dma_set_wptw(stwuct wadeon_device *wdev,
			 stwuct wadeon_wing *wing)
{
	u32 weg;

	if (wing->idx == W600_WING_TYPE_DMA_INDEX)
		weg = DMA_WB_WPTW + DMA0_WEGISTEW_OFFSET;
	ewse
		weg = DMA_WB_WPTW + DMA1_WEGISTEW_OFFSET;

	WWEG32(weg, (wing->wptw << 2) & 0x3fffc);
}

/**
 * cayman_dma_wing_ib_execute - Scheduwe an IB on the DMA engine
 *
 * @wdev: wadeon_device pointew
 * @ib: IB object to scheduwe
 *
 * Scheduwe an IB in the DMA wing (cayman-SI).
 */
void cayman_dma_wing_ib_execute(stwuct wadeon_device *wdev,
				stwuct wadeon_ib *ib)
{
	stwuct wadeon_wing *wing = &wdev->wing[ib->wing];
	unsigned vm_id = ib->vm ? ib->vm->ids[ib->wing].id : 0;

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
	wadeon_wing_wwite(wing, DMA_IB_PACKET(DMA_PACKET_INDIWECT_BUFFEW, vm_id, 0));
	wadeon_wing_wwite(wing, (ib->gpu_addw & 0xFFFFFFE0));
	wadeon_wing_wwite(wing, (ib->wength_dw << 12) | (uppew_32_bits(ib->gpu_addw) & 0xFF));

}

/**
 * cayman_dma_stop - stop the async dma engines
 *
 * @wdev: wadeon_device pointew
 *
 * Stop the async dma engines (cayman-SI).
 */
void cayman_dma_stop(stwuct wadeon_device *wdev)
{
	u32 wb_cntw;

	if ((wdev->asic->copy.copy_wing_index == W600_WING_TYPE_DMA_INDEX) ||
	    (wdev->asic->copy.copy_wing_index == CAYMAN_WING_TYPE_DMA1_INDEX))
		wadeon_ttm_set_active_vwam_size(wdev, wdev->mc.visibwe_vwam_size);

	/* dma0 */
	wb_cntw = WWEG32(DMA_WB_CNTW + DMA0_WEGISTEW_OFFSET);
	wb_cntw &= ~DMA_WB_ENABWE;
	WWEG32(DMA_WB_CNTW + DMA0_WEGISTEW_OFFSET, wb_cntw);

	/* dma1 */
	wb_cntw = WWEG32(DMA_WB_CNTW + DMA1_WEGISTEW_OFFSET);
	wb_cntw &= ~DMA_WB_ENABWE;
	WWEG32(DMA_WB_CNTW + DMA1_WEGISTEW_OFFSET, wb_cntw);

	wdev->wing[W600_WING_TYPE_DMA_INDEX].weady = fawse;
	wdev->wing[CAYMAN_WING_TYPE_DMA1_INDEX].weady = fawse;
}

/**
 * cayman_dma_wesume - setup and stawt the async dma engines
 *
 * @wdev: wadeon_device pointew
 *
 * Set up the DMA wing buffews and enabwe them. (cayman-SI).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
int cayman_dma_wesume(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing;
	u32 wb_cntw, dma_cntw, ib_cntw;
	u32 wb_bufsz;
	u32 weg_offset, wb_offset;
	int i, w;

	fow (i = 0; i < 2; i++) {
		if (i == 0) {
			wing = &wdev->wing[W600_WING_TYPE_DMA_INDEX];
			weg_offset = DMA0_WEGISTEW_OFFSET;
			wb_offset = W600_WB_DMA_WPTW_OFFSET;
		} ewse {
			wing = &wdev->wing[CAYMAN_WING_TYPE_DMA1_INDEX];
			weg_offset = DMA1_WEGISTEW_OFFSET;
			wb_offset = CAYMAN_WB_DMA1_WPTW_OFFSET;
		}

		WWEG32(DMA_SEM_INCOMPWETE_TIMEW_CNTW + weg_offset, 0);
		WWEG32(DMA_SEM_WAIT_FAIW_TIMEW_CNTW + weg_offset, 0);

		/* Set wing buffew size in dwowds */
		wb_bufsz = owdew_base_2(wing->wing_size / 4);
		wb_cntw = wb_bufsz << 1;
#ifdef __BIG_ENDIAN
		wb_cntw |= DMA_WB_SWAP_ENABWE | DMA_WPTW_WWITEBACK_SWAP_ENABWE;
#endif
		WWEG32(DMA_WB_CNTW + weg_offset, wb_cntw);

		/* Initiawize the wing buffew's wead and wwite pointews */
		WWEG32(DMA_WB_WPTW + weg_offset, 0);
		WWEG32(DMA_WB_WPTW + weg_offset, 0);

		/* set the wb addwess whethew it's enabwed ow not */
		WWEG32(DMA_WB_WPTW_ADDW_HI + weg_offset,
		       uppew_32_bits(wdev->wb.gpu_addw + wb_offset) & 0xFF);
		WWEG32(DMA_WB_WPTW_ADDW_WO + weg_offset,
		       ((wdev->wb.gpu_addw + wb_offset) & 0xFFFFFFFC));

		if (wdev->wb.enabwed)
			wb_cntw |= DMA_WPTW_WWITEBACK_ENABWE;

		WWEG32(DMA_WB_BASE + weg_offset, wing->gpu_addw >> 8);

		/* enabwe DMA IBs */
		ib_cntw = DMA_IB_ENABWE | CMD_VMID_FOWCE;
#ifdef __BIG_ENDIAN
		ib_cntw |= DMA_IB_SWAP_ENABWE;
#endif
		WWEG32(DMA_IB_CNTW + weg_offset, ib_cntw);

		dma_cntw = WWEG32(DMA_CNTW + weg_offset);
		dma_cntw &= ~CTXEMPTY_INT_ENABWE;
		WWEG32(DMA_CNTW + weg_offset, dma_cntw);

		wing->wptw = 0;
		WWEG32(DMA_WB_WPTW + weg_offset, wing->wptw << 2);

		WWEG32(DMA_WB_CNTW + weg_offset, wb_cntw | DMA_WB_ENABWE);

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
 * cayman_dma_fini - teaw down the async dma engines
 *
 * @wdev: wadeon_device pointew
 *
 * Stop the async dma engines and fwee the wings (cayman-SI).
 */
void cayman_dma_fini(stwuct wadeon_device *wdev)
{
	cayman_dma_stop(wdev);
	wadeon_wing_fini(wdev, &wdev->wing[W600_WING_TYPE_DMA_INDEX]);
	wadeon_wing_fini(wdev, &wdev->wing[CAYMAN_WING_TYPE_DMA1_INDEX]);
}

/**
 * cayman_dma_is_wockup - Check if the DMA engine is wocked up
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Check if the async DMA engine is wocked up.
 * Wetuwns twue if the engine appeaws to be wocked up, fawse if not.
 */
boow cayman_dma_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	u32 weset_mask = cayman_gpu_check_soft_weset(wdev);
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
 * cayman_dma_vm_copy_pages - update PTEs by copying them fwom the GAWT
 *
 * @wdev: wadeon_device pointew
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @swc: swc addw whewe to copy fwom
 * @count: numbew of page entwies to update
 *
 * Update PTEs by copying them fwom the GAWT using the DMA (cayman/TN).
 */
void cayman_dma_vm_copy_pages(stwuct wadeon_device *wdev,
			      stwuct wadeon_ib *ib,
			      uint64_t pe, uint64_t swc,
			      unsigned count)
{
	unsigned ndw;

	whiwe (count) {
		ndw = count * 2;
		if (ndw > 0xFFFFE)
			ndw = 0xFFFFE;

		ib->ptw[ib->wength_dw++] = DMA_PACKET(DMA_PACKET_COPY,
						      0, 0, ndw);
		ib->ptw[ib->wength_dw++] = wowew_32_bits(pe);
		ib->ptw[ib->wength_dw++] = wowew_32_bits(swc);
		ib->ptw[ib->wength_dw++] = uppew_32_bits(pe) & 0xff;
		ib->ptw[ib->wength_dw++] = uppew_32_bits(swc) & 0xff;

		pe += ndw * 4;
		swc += ndw * 4;
		count -= ndw / 2;
	}
}

/**
 * cayman_dma_vm_wwite_pages - update PTEs by wwiting them manuawwy
 *
 * @wdev: wadeon_device pointew
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @addw: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 * @fwags: hw access fwags
 *
 * Update PTEs by wwiting them manuawwy using the DMA (cayman/TN).
 */
void cayman_dma_vm_wwite_pages(stwuct wadeon_device *wdev,
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
		ib->ptw[ib->wength_dw++] = DMA_PACKET(DMA_PACKET_WWITE,
						      0, 0, ndw);
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
 * cayman_dma_vm_set_pages - update the page tabwes using the DMA
 *
 * @wdev: wadeon_device pointew
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @addw: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 * @fwags: hw access fwags
 *
 * Update the page tabwes using the DMA (cayman/TN).
 */
void cayman_dma_vm_set_pages(stwuct wadeon_device *wdev,
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

/**
 * cayman_dma_vm_pad_ib - pad the IB to the wequiwed numbew of dw
 *
 * @ib: indiwect buffew to fiww with padding
 *
 */
void cayman_dma_vm_pad_ib(stwuct wadeon_ib *ib)
{
	whiwe (ib->wength_dw & 0x7)
		ib->ptw[ib->wength_dw++] = DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0);
}

void cayman_dma_vm_fwush(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing,
			 unsigned vm_id, uint64_t pd_addw)
{
	wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_SWBM_WWITE, 0, 0, 0));
	wadeon_wing_wwite(wing, (0xf << 16) | ((VM_CONTEXT0_PAGE_TABWE_BASE_ADDW + (vm_id << 2)) >> 2));
	wadeon_wing_wwite(wing, pd_addw >> 12);

	/* fwush hdp cache */
	wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_SWBM_WWITE, 0, 0, 0));
	wadeon_wing_wwite(wing, (0xf << 16) | (HDP_MEM_COHEWENCY_FWUSH_CNTW >> 2));
	wadeon_wing_wwite(wing, 1);

	/* bits 0-7 awe the VM contexts0-7 */
	wadeon_wing_wwite(wing, DMA_PACKET(DMA_PACKET_SWBM_WWITE, 0, 0, 0));
	wadeon_wing_wwite(wing, (0xf << 16) | (VM_INVAWIDATE_WEQUEST >> 2));
	wadeon_wing_wwite(wing, 1 << vm_id);

	/* wait fow invawidate to compwete */
	wadeon_wing_wwite(wing, DMA_SWBM_WEAD_PACKET);
	wadeon_wing_wwite(wing, (0xff << 20) | (VM_INVAWIDATE_WEQUEST >> 2));
	wadeon_wing_wwite(wing, 0); /* mask */
	wadeon_wing_wwite(wing, 0); /* vawue */
}

