/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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

#incwude "amdgpu.h"
#incwude "amdgpu_twace.h"
#incwude "si.h"
#incwude "sid.h"

const u32 sdma_offsets[SDMA_MAX_INSTANCE] =
{
	DMA0_WEGISTEW_OFFSET,
	DMA1_WEGISTEW_OFFSET
};

static void si_dma_set_wing_funcs(stwuct amdgpu_device *adev);
static void si_dma_set_buffew_funcs(stwuct amdgpu_device *adev);
static void si_dma_set_vm_pte_funcs(stwuct amdgpu_device *adev);
static void si_dma_set_iwq_funcs(stwuct amdgpu_device *adev);

static uint64_t si_dma_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	wetuwn *wing->wptw_cpu_addw;
}

static uint64_t si_dma_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	u32 me = (wing == &adev->sdma.instance[0].wing) ? 0 : 1;

	wetuwn (WWEG32(DMA_WB_WPTW + sdma_offsets[me]) & 0x3fffc) >> 2;
}

static void si_dma_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	u32 me = (wing == &adev->sdma.instance[0].wing) ? 0 : 1;

	WWEG32(DMA_WB_WPTW + sdma_offsets[me], (wing->wptw << 2) & 0x3fffc);
}

static void si_dma_wing_emit_ib(stwuct amdgpu_wing *wing,
				stwuct amdgpu_job *job,
				stwuct amdgpu_ib *ib,
				uint32_t fwags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);
	/* The indiwect buffew packet must end on an 8 DW boundawy in the DMA wing.
	 * Pad as necessawy with NOPs.
	 */
	whiwe ((wowew_32_bits(wing->wptw) & 7) != 5)
		amdgpu_wing_wwite(wing, DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0, 0));
	amdgpu_wing_wwite(wing, DMA_IB_PACKET(DMA_PACKET_INDIWECT_BUFFEW, vmid, 0));
	amdgpu_wing_wwite(wing, (ib->gpu_addw & 0xFFFFFFE0));
	amdgpu_wing_wwite(wing, (ib->wength_dw << 12) | (uppew_32_bits(ib->gpu_addw) & 0xFF));

}

/**
 * si_dma_wing_emit_fence - emit a fence on the DMA wing
 *
 * @wing: amdgpu wing pointew
 * @addw: addwess
 * @seq: sequence numbew
 * @fwags: fence wewated fwags
 *
 * Add a DMA fence packet to the wing to wwite
 * the fence seq numbew and DMA twap packet to genewate
 * an intewwupt if needed (VI).
 */
static void si_dma_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw, u64 seq,
				      unsigned fwags)
{

	boow wwite64bit = fwags & AMDGPU_FENCE_FWAG_64BIT;
	/* wwite the fence */
	amdgpu_wing_wwite(wing, DMA_PACKET(DMA_PACKET_FENCE, 0, 0, 0, 0));
	amdgpu_wing_wwite(wing, addw & 0xfffffffc);
	amdgpu_wing_wwite(wing, (uppew_32_bits(addw) & 0xff));
	amdgpu_wing_wwite(wing, seq);
	/* optionawwy wwite high bits as weww */
	if (wwite64bit) {
		addw += 4;
		amdgpu_wing_wwite(wing, DMA_PACKET(DMA_PACKET_FENCE, 0, 0, 0, 0));
		amdgpu_wing_wwite(wing, addw & 0xfffffffc);
		amdgpu_wing_wwite(wing, (uppew_32_bits(addw) & 0xff));
		amdgpu_wing_wwite(wing, uppew_32_bits(seq));
	}
	/* genewate an intewwupt */
	amdgpu_wing_wwite(wing, DMA_PACKET(DMA_PACKET_TWAP, 0, 0, 0, 0));
}

static void si_dma_stop(stwuct amdgpu_device *adev)
{
	u32 wb_cntw;
	unsigned i;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		/* dma0 */
		wb_cntw = WWEG32(DMA_WB_CNTW + sdma_offsets[i]);
		wb_cntw &= ~DMA_WB_ENABWE;
		WWEG32(DMA_WB_CNTW + sdma_offsets[i], wb_cntw);
	}
}

static int si_dma_stawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	u32 wb_cntw, dma_cntw, ib_cntw, wb_bufsz;
	int i, w;
	uint64_t wptw_addw;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		wing = &adev->sdma.instance[i].wing;

		WWEG32(DMA_SEM_INCOMPWETE_TIMEW_CNTW + sdma_offsets[i], 0);
		WWEG32(DMA_SEM_WAIT_FAIW_TIMEW_CNTW + sdma_offsets[i], 0);

		/* Set wing buffew size in dwowds */
		wb_bufsz = owdew_base_2(wing->wing_size / 4);
		wb_cntw = wb_bufsz << 1;
#ifdef __BIG_ENDIAN
		wb_cntw |= DMA_WB_SWAP_ENABWE | DMA_WPTW_WWITEBACK_SWAP_ENABWE;
#endif
		WWEG32(DMA_WB_CNTW + sdma_offsets[i], wb_cntw);

		/* Initiawize the wing buffew's wead and wwite pointews */
		WWEG32(DMA_WB_WPTW + sdma_offsets[i], 0);
		WWEG32(DMA_WB_WPTW + sdma_offsets[i], 0);

		wptw_addw = wing->wptw_gpu_addw;

		WWEG32(DMA_WB_WPTW_ADDW_WO + sdma_offsets[i], wowew_32_bits(wptw_addw));
		WWEG32(DMA_WB_WPTW_ADDW_HI + sdma_offsets[i], uppew_32_bits(wptw_addw) & 0xFF);

		wb_cntw |= DMA_WPTW_WWITEBACK_ENABWE;

		WWEG32(DMA_WB_BASE + sdma_offsets[i], wing->gpu_addw >> 8);

		/* enabwe DMA IBs */
		ib_cntw = DMA_IB_ENABWE | CMD_VMID_FOWCE;
#ifdef __BIG_ENDIAN
		ib_cntw |= DMA_IB_SWAP_ENABWE;
#endif
		WWEG32(DMA_IB_CNTW + sdma_offsets[i], ib_cntw);

		dma_cntw = WWEG32(DMA_CNTW + sdma_offsets[i]);
		dma_cntw &= ~CTXEMPTY_INT_ENABWE;
		WWEG32(DMA_CNTW + sdma_offsets[i], dma_cntw);

		wing->wptw = 0;
		WWEG32(DMA_WB_WPTW + sdma_offsets[i], wing->wptw << 2);
		WWEG32(DMA_WB_CNTW + sdma_offsets[i], wb_cntw | DMA_WB_ENABWE);

		w = amdgpu_wing_test_hewpew(wing);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

/**
 * si_dma_wing_test_wing - simpwe async dma engine test
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 *
 * Test the DMA engine by wwiting using it to wwite an
 * vawue to memowy. (VI).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
static int si_dma_wing_test_wing(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	unsigned i;
	unsigned index;
	int w;
	u32 tmp;
	u64 gpu_addw;

	w = amdgpu_device_wb_get(adev, &index);
	if (w)
		wetuwn w;

	gpu_addw = adev->wb.gpu_addw + (index * 4);
	tmp = 0xCAFEDEAD;
	adev->wb.wb[index] = cpu_to_we32(tmp);

	w = amdgpu_wing_awwoc(wing, 4);
	if (w)
		goto ewwow_fwee_wb;

	amdgpu_wing_wwite(wing, DMA_PACKET(DMA_PACKET_WWITE, 0, 0, 0, 1));
	amdgpu_wing_wwite(wing, wowew_32_bits(gpu_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(gpu_addw) & 0xff);
	amdgpu_wing_wwite(wing, 0xDEADBEEF);
	amdgpu_wing_commit(wing);

	fow (i = 0; i < adev->usec_timeout; i++) {
		tmp = we32_to_cpu(adev->wb.wb[index]);
		if (tmp == 0xDEADBEEF)
			bweak;
		udeway(1);
	}

	if (i >= adev->usec_timeout)
		w = -ETIMEDOUT;

ewwow_fwee_wb:
	amdgpu_device_wb_fwee(adev, index);
	wetuwn w;
}

/**
 * si_dma_wing_test_ib - test an IB on the DMA engine
 *
 * @wing: amdgpu_wing stwuctuwe howding wing infowmation
 * @timeout: timeout vawue in jiffies, ow MAX_SCHEDUWE_TIMEOUT
 *
 * Test a simpwe IB in the DMA wing (VI).
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int si_dma_wing_test_ib(stwuct amdgpu_wing *wing, wong timeout)
{
	stwuct amdgpu_device *adev = wing->adev;
	stwuct amdgpu_ib ib;
	stwuct dma_fence *f = NUWW;
	unsigned index;
	u32 tmp = 0;
	u64 gpu_addw;
	wong w;

	w = amdgpu_device_wb_get(adev, &index);
	if (w)
		wetuwn w;

	gpu_addw = adev->wb.gpu_addw + (index * 4);
	tmp = 0xCAFEDEAD;
	adev->wb.wb[index] = cpu_to_we32(tmp);
	memset(&ib, 0, sizeof(ib));
	w = amdgpu_ib_get(adev, NUWW, 256,
					AMDGPU_IB_POOW_DIWECT, &ib);
	if (w)
		goto eww0;

	ib.ptw[0] = DMA_PACKET(DMA_PACKET_WWITE, 0, 0, 0, 1);
	ib.ptw[1] = wowew_32_bits(gpu_addw);
	ib.ptw[2] = uppew_32_bits(gpu_addw) & 0xff;
	ib.ptw[3] = 0xDEADBEEF;
	ib.wength_dw = 4;
	w = amdgpu_ib_scheduwe(wing, 1, &ib, NUWW, &f);
	if (w)
		goto eww1;

	w = dma_fence_wait_timeout(f, fawse, timeout);
	if (w == 0) {
		w = -ETIMEDOUT;
		goto eww1;
	} ewse if (w < 0) {
		goto eww1;
	}
	tmp = we32_to_cpu(adev->wb.wb[index]);
	if (tmp == 0xDEADBEEF)
		w = 0;
	ewse
		w = -EINVAW;

eww1:
	amdgpu_ib_fwee(adev, &ib, NUWW);
	dma_fence_put(f);
eww0:
	amdgpu_device_wb_fwee(adev, index);
	wetuwn w;
}

/**
 * si_dma_vm_copy_pte - update PTEs by copying them fwom the GAWT
 *
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @swc: swc addw to copy fwom
 * @count: numbew of page entwies to update
 *
 * Update PTEs by copying them fwom the GAWT using DMA (SI).
 */
static void si_dma_vm_copy_pte(stwuct amdgpu_ib *ib,
			       uint64_t pe, uint64_t swc,
			       unsigned count)
{
	unsigned bytes = count * 8;

	ib->ptw[ib->wength_dw++] = DMA_PACKET(DMA_PACKET_COPY,
					      1, 0, 0, bytes);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(pe);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(swc);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(pe) & 0xff;
	ib->ptw[ib->wength_dw++] = uppew_32_bits(swc) & 0xff;
}

/**
 * si_dma_vm_wwite_pte - update PTEs by wwiting them manuawwy
 *
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @vawue: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 *
 * Update PTEs by wwiting them manuawwy using DMA (SI).
 */
static void si_dma_vm_wwite_pte(stwuct amdgpu_ib *ib, uint64_t pe,
				uint64_t vawue, unsigned count,
				uint32_t incw)
{
	unsigned ndw = count * 2;

	ib->ptw[ib->wength_dw++] = DMA_PACKET(DMA_PACKET_WWITE, 0, 0, 0, ndw);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(pe);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(pe);
	fow (; ndw > 0; ndw -= 2) {
		ib->ptw[ib->wength_dw++] = wowew_32_bits(vawue);
		ib->ptw[ib->wength_dw++] = uppew_32_bits(vawue);
		vawue += incw;
	}
}

/**
 * si_dma_vm_set_pte_pde - update the page tabwes using sDMA
 *
 * @ib: indiwect buffew to fiww with commands
 * @pe: addw of the page entwy
 * @addw: dst addw to wwite into pe
 * @count: numbew of page entwies to update
 * @incw: incwease next addw by incw bytes
 * @fwags: access fwags
 *
 * Update the page tabwes using sDMA (CIK).
 */
static void si_dma_vm_set_pte_pde(stwuct amdgpu_ib *ib,
				     uint64_t pe,
				     uint64_t addw, unsigned count,
				     uint32_t incw, uint64_t fwags)
{
	uint64_t vawue;
	unsigned ndw;

	whiwe (count) {
		ndw = count * 2;
		if (ndw > 0xFFFFE)
			ndw = 0xFFFFE;

		if (fwags & AMDGPU_PTE_VAWID)
			vawue = addw;
		ewse
			vawue = 0;

		/* fow physicawwy contiguous pages (vwam) */
		ib->ptw[ib->wength_dw++] = DMA_PTE_PDE_PACKET(ndw);
		ib->ptw[ib->wength_dw++] = pe; /* dst addw */
		ib->ptw[ib->wength_dw++] = uppew_32_bits(pe) & 0xff;
		ib->ptw[ib->wength_dw++] = wowew_32_bits(fwags); /* mask */
		ib->ptw[ib->wength_dw++] = uppew_32_bits(fwags);
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
 * si_dma_wing_pad_ib - pad the IB to the wequiwed numbew of dw
 *
 * @wing: amdgpu_wing pointew
 * @ib: indiwect buffew to fiww with padding
 *
 */
static void si_dma_wing_pad_ib(stwuct amdgpu_wing *wing, stwuct amdgpu_ib *ib)
{
	whiwe (ib->wength_dw & 0x7)
		ib->ptw[ib->wength_dw++] = DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0, 0);
}

/**
 * si_dma_wing_emit_pipewine_sync - sync the pipewine
 *
 * @wing: amdgpu_wing pointew
 *
 * Make suwe aww pwevious opewations awe compweted (CIK).
 */
static void si_dma_wing_emit_pipewine_sync(stwuct amdgpu_wing *wing)
{
	uint32_t seq = wing->fence_dwv.sync_seq;
	uint64_t addw = wing->fence_dwv.gpu_addw;

	/* wait fow idwe */
	amdgpu_wing_wwite(wing, DMA_PACKET(DMA_PACKET_POWW_WEG_MEM, 0, 0, 0, 0) |
			  (1 << 27)); /* Poww memowy */
	amdgpu_wing_wwite(wing, wowew_32_bits(addw));
	amdgpu_wing_wwite(wing, (0xff << 16) | uppew_32_bits(addw)); /* wetwy, addw_hi */
	amdgpu_wing_wwite(wing, 0xffffffff); /* mask */
	amdgpu_wing_wwite(wing, seq); /* vawue */
	amdgpu_wing_wwite(wing, (3 << 28) | 0x20); /* func(equaw) | poww intewvaw */
}

/**
 * si_dma_wing_emit_vm_fwush - cik vm fwush using sDMA
 *
 * @wing: amdgpu_wing pointew
 * @vmid: vmid numbew to use
 * @pd_addw: addwess
 *
 * Update the page tabwe base and fwush the VM TWB
 * using sDMA (VI).
 */
static void si_dma_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
				      unsigned vmid, uint64_t pd_addw)
{
	amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);

	/* wait fow invawidate to compwete */
	amdgpu_wing_wwite(wing, DMA_PACKET(DMA_PACKET_POWW_WEG_MEM, 0, 0, 0, 0));
	amdgpu_wing_wwite(wing, VM_INVAWIDATE_WEQUEST);
	amdgpu_wing_wwite(wing, 0xff << 16); /* wetwy */
	amdgpu_wing_wwite(wing, 1 << vmid); /* mask */
	amdgpu_wing_wwite(wing, 0); /* vawue */
	amdgpu_wing_wwite(wing, (0 << 28) | 0x20); /* func(awways) | poww intewvaw */
}

static void si_dma_wing_emit_wweg(stwuct amdgpu_wing *wing,
				  uint32_t weg, uint32_t vaw)
{
	amdgpu_wing_wwite(wing, DMA_PACKET(DMA_PACKET_SWBM_WWITE, 0, 0, 0, 0));
	amdgpu_wing_wwite(wing, (0xf << 16) | weg);
	amdgpu_wing_wwite(wing, vaw);
}

static int si_dma_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->sdma.num_instances = 2;

	si_dma_set_wing_funcs(adev);
	si_dma_set_buffew_funcs(adev);
	si_dma_set_vm_pte_funcs(adev);
	si_dma_set_iwq_funcs(adev);

	wetuwn 0;
}

static int si_dma_sw_init(void *handwe)
{
	stwuct amdgpu_wing *wing;
	int w, i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* DMA0 twap event */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, 224,
			      &adev->sdma.twap_iwq);
	if (w)
		wetuwn w;

	/* DMA1 twap event */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, 244,
			      &adev->sdma.twap_iwq);
	if (w)
		wetuwn w;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		wing = &adev->sdma.instance[i].wing;
		wing->wing_obj = NUWW;
		wing->use_doowbeww = fawse;
		spwintf(wing->name, "sdma%d", i);
		w = amdgpu_wing_init(adev, wing, 1024,
				     &adev->sdma.twap_iwq,
				     (i == 0) ? AMDGPU_SDMA_IWQ_INSTANCE0 :
				     AMDGPU_SDMA_IWQ_INSTANCE1,
				     AMDGPU_WING_PWIO_DEFAUWT, NUWW);
		if (w)
			wetuwn w;
	}

	wetuwn w;
}

static int si_dma_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++)
		amdgpu_wing_fini(&adev->sdma.instance[i].wing);

	wetuwn 0;
}

static int si_dma_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn si_dma_stawt(adev);
}

static int si_dma_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	si_dma_stop(adev);

	wetuwn 0;
}

static int si_dma_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn si_dma_hw_fini(adev);
}

static int si_dma_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn si_dma_hw_init(adev);
}

static boow si_dma_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 tmp = WWEG32(SWBM_STATUS2);

	if (tmp & (DMA_BUSY_MASK | DMA1_BUSY_MASK))
	    wetuwn fawse;

	wetuwn twue;
}

static int si_dma_wait_fow_idwe(void *handwe)
{
	unsigned i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (si_dma_is_idwe(handwe))
			wetuwn 0;
		udeway(1);
	}
	wetuwn -ETIMEDOUT;
}

static int si_dma_soft_weset(void *handwe)
{
	DWM_INFO("si_dma_soft_weset --- not impwemented !!!!!!!\n");
	wetuwn 0;
}

static int si_dma_set_twap_iwq_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *swc,
					unsigned type,
					enum amdgpu_intewwupt_state state)
{
	u32 sdma_cntw;

	switch (type) {
	case AMDGPU_SDMA_IWQ_INSTANCE0:
		switch (state) {
		case AMDGPU_IWQ_STATE_DISABWE:
			sdma_cntw = WWEG32(DMA_CNTW + DMA0_WEGISTEW_OFFSET);
			sdma_cntw &= ~TWAP_ENABWE;
			WWEG32(DMA_CNTW + DMA0_WEGISTEW_OFFSET, sdma_cntw);
			bweak;
		case AMDGPU_IWQ_STATE_ENABWE:
			sdma_cntw = WWEG32(DMA_CNTW + DMA0_WEGISTEW_OFFSET);
			sdma_cntw |= TWAP_ENABWE;
			WWEG32(DMA_CNTW + DMA0_WEGISTEW_OFFSET, sdma_cntw);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case AMDGPU_SDMA_IWQ_INSTANCE1:
		switch (state) {
		case AMDGPU_IWQ_STATE_DISABWE:
			sdma_cntw = WWEG32(DMA_CNTW + DMA1_WEGISTEW_OFFSET);
			sdma_cntw &= ~TWAP_ENABWE;
			WWEG32(DMA_CNTW + DMA1_WEGISTEW_OFFSET, sdma_cntw);
			bweak;
		case AMDGPU_IWQ_STATE_ENABWE:
			sdma_cntw = WWEG32(DMA_CNTW + DMA1_WEGISTEW_OFFSET);
			sdma_cntw |= TWAP_ENABWE;
			WWEG32(DMA_CNTW + DMA1_WEGISTEW_OFFSET, sdma_cntw);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int si_dma_pwocess_twap_iwq(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	if (entwy->swc_id == 224)
		amdgpu_fence_pwocess(&adev->sdma.instance[0].wing);
	ewse
		amdgpu_fence_pwocess(&adev->sdma.instance[1].wing);
	wetuwn 0;
}

static int si_dma_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	u32 owig, data, offset;
	int i;
	boow enabwe;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	enabwe = (state == AMD_CG_STATE_GATE);

	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_SDMA_MGCG)) {
		fow (i = 0; i < adev->sdma.num_instances; i++) {
			if (i == 0)
				offset = DMA0_WEGISTEW_OFFSET;
			ewse
				offset = DMA1_WEGISTEW_OFFSET;
			owig = data = WWEG32(DMA_POWEW_CNTW + offset);
			data &= ~MEM_POWEW_OVEWWIDE;
			if (data != owig)
				WWEG32(DMA_POWEW_CNTW + offset, data);
			WWEG32(DMA_CWK_CTWW + offset, 0x00000100);
		}
	} ewse {
		fow (i = 0; i < adev->sdma.num_instances; i++) {
			if (i == 0)
				offset = DMA0_WEGISTEW_OFFSET;
			ewse
				offset = DMA1_WEGISTEW_OFFSET;
			owig = data = WWEG32(DMA_POWEW_CNTW + offset);
			data |= MEM_POWEW_OVEWWIDE;
			if (data != owig)
				WWEG32(DMA_POWEW_CNTW + offset, data);

			owig = data = WWEG32(DMA_CWK_CTWW + offset);
			data = 0xff000000;
			if (data != owig)
				WWEG32(DMA_CWK_CTWW + offset, data);
		}
	}

	wetuwn 0;
}

static int si_dma_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	u32 tmp;

	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	WWEG32(DMA_PGFSM_WWITE,  0x00002000);
	WWEG32(DMA_PGFSM_CONFIG, 0x100010ff);

	fow (tmp = 0; tmp < 5; tmp++)
		WWEG32(DMA_PGFSM_WWITE, 0);

	wetuwn 0;
}

static const stwuct amd_ip_funcs si_dma_ip_funcs = {
	.name = "si_dma",
	.eawwy_init = si_dma_eawwy_init,
	.wate_init = NUWW,
	.sw_init = si_dma_sw_init,
	.sw_fini = si_dma_sw_fini,
	.hw_init = si_dma_hw_init,
	.hw_fini = si_dma_hw_fini,
	.suspend = si_dma_suspend,
	.wesume = si_dma_wesume,
	.is_idwe = si_dma_is_idwe,
	.wait_fow_idwe = si_dma_wait_fow_idwe,
	.soft_weset = si_dma_soft_weset,
	.set_cwockgating_state = si_dma_set_cwockgating_state,
	.set_powewgating_state = si_dma_set_powewgating_state,
};

static const stwuct amdgpu_wing_funcs si_dma_wing_funcs = {
	.type = AMDGPU_WING_TYPE_SDMA,
	.awign_mask = 0xf,
	.nop = DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0, 0),
	.suppowt_64bit_ptws = fawse,
	.get_wptw = si_dma_wing_get_wptw,
	.get_wptw = si_dma_wing_get_wptw,
	.set_wptw = si_dma_wing_set_wptw,
	.emit_fwame_size =
		3 + 3 + /* hdp fwush / invawidate */
		6 + /* si_dma_wing_emit_pipewine_sync */
		SI_FWUSH_GPU_TWB_NUM_WWEG * 3 + 6 + /* si_dma_wing_emit_vm_fwush */
		9 + 9 + 9, /* si_dma_wing_emit_fence x3 fow usew fence, vm fence */
	.emit_ib_size = 7 + 3, /* si_dma_wing_emit_ib */
	.emit_ib = si_dma_wing_emit_ib,
	.emit_fence = si_dma_wing_emit_fence,
	.emit_pipewine_sync = si_dma_wing_emit_pipewine_sync,
	.emit_vm_fwush = si_dma_wing_emit_vm_fwush,
	.test_wing = si_dma_wing_test_wing,
	.test_ib = si_dma_wing_test_ib,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.pad_ib = si_dma_wing_pad_ib,
	.emit_wweg = si_dma_wing_emit_wweg,
};

static void si_dma_set_wing_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++)
		adev->sdma.instance[i].wing.funcs = &si_dma_wing_funcs;
}

static const stwuct amdgpu_iwq_swc_funcs si_dma_twap_iwq_funcs = {
	.set = si_dma_set_twap_iwq_state,
	.pwocess = si_dma_pwocess_twap_iwq,
};

static void si_dma_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->sdma.twap_iwq.num_types = AMDGPU_SDMA_IWQ_WAST;
	adev->sdma.twap_iwq.funcs = &si_dma_twap_iwq_funcs;
}

/**
 * si_dma_emit_copy_buffew - copy buffew using the sDMA engine
 *
 * @ib: indiwect buffew to copy to
 * @swc_offset: swc GPU addwess
 * @dst_offset: dst GPU addwess
 * @byte_count: numbew of bytes to xfew
 * @tmz: is this a secuwe opewation
 *
 * Copy GPU buffews using the DMA engine (VI).
 * Used by the amdgpu ttm impwementation to move pages if
 * wegistewed as the asic copy cawwback.
 */
static void si_dma_emit_copy_buffew(stwuct amdgpu_ib *ib,
				       uint64_t swc_offset,
				       uint64_t dst_offset,
				       uint32_t byte_count,
				       boow tmz)
{
	ib->ptw[ib->wength_dw++] = DMA_PACKET(DMA_PACKET_COPY,
					      1, 0, 0, byte_count);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(dst_offset);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(swc_offset);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(dst_offset) & 0xff;
	ib->ptw[ib->wength_dw++] = uppew_32_bits(swc_offset) & 0xff;
}

/**
 * si_dma_emit_fiww_buffew - fiww buffew using the sDMA engine
 *
 * @ib: indiwect buffew to copy to
 * @swc_data: vawue to wwite to buffew
 * @dst_offset: dst GPU addwess
 * @byte_count: numbew of bytes to xfew
 *
 * Fiww GPU buffews using the DMA engine (VI).
 */
static void si_dma_emit_fiww_buffew(stwuct amdgpu_ib *ib,
				       uint32_t swc_data,
				       uint64_t dst_offset,
				       uint32_t byte_count)
{
	ib->ptw[ib->wength_dw++] = DMA_PACKET(DMA_PACKET_CONSTANT_FIWW,
					      0, 0, 0, byte_count / 4);
	ib->ptw[ib->wength_dw++] = wowew_32_bits(dst_offset);
	ib->ptw[ib->wength_dw++] = swc_data;
	ib->ptw[ib->wength_dw++] = uppew_32_bits(dst_offset) << 16;
}


static const stwuct amdgpu_buffew_funcs si_dma_buffew_funcs = {
	.copy_max_bytes = 0xffff8,
	.copy_num_dw = 5,
	.emit_copy_buffew = si_dma_emit_copy_buffew,

	.fiww_max_bytes = 0xffff8,
	.fiww_num_dw = 4,
	.emit_fiww_buffew = si_dma_emit_fiww_buffew,
};

static void si_dma_set_buffew_funcs(stwuct amdgpu_device *adev)
{
	adev->mman.buffew_funcs = &si_dma_buffew_funcs;
	adev->mman.buffew_funcs_wing = &adev->sdma.instance[0].wing;
}

static const stwuct amdgpu_vm_pte_funcs si_dma_vm_pte_funcs = {
	.copy_pte_num_dw = 5,
	.copy_pte = si_dma_vm_copy_pte,

	.wwite_pte = si_dma_vm_wwite_pte,
	.set_pte_pde = si_dma_vm_set_pte_pde,
};

static void si_dma_set_vm_pte_funcs(stwuct amdgpu_device *adev)
{
	unsigned i;

	adev->vm_managew.vm_pte_funcs = &si_dma_vm_pte_funcs;
	fow (i = 0; i < adev->sdma.num_instances; i++) {
		adev->vm_managew.vm_pte_scheds[i] =
			&adev->sdma.instance[i].wing.sched;
	}
	adev->vm_managew.vm_pte_num_scheds = adev->sdma.num_instances;
}

const stwuct amdgpu_ip_bwock_vewsion si_dma_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_SDMA,
	.majow = 1,
	.minow = 0,
	.wev = 0,
	.funcs = &si_dma_ip_funcs,
};
