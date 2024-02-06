/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
 */

#incwude "amdgpu.h"
#incwude "vcn_sw_wing.h"

void vcn_dec_sw_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw,
	u64 seq, uint32_t fwags)
{
	WAWN_ON(fwags & AMDGPU_FENCE_FWAG_64BIT);

	amdgpu_wing_wwite(wing, VCN_DEC_SW_CMD_FENCE);
	amdgpu_wing_wwite(wing, addw);
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));
	amdgpu_wing_wwite(wing, seq);
	amdgpu_wing_wwite(wing, VCN_DEC_SW_CMD_TWAP);
}

void vcn_dec_sw_wing_insewt_end(stwuct amdgpu_wing *wing)
{
	amdgpu_wing_wwite(wing, VCN_DEC_SW_CMD_END);
}

void vcn_dec_sw_wing_emit_ib(stwuct amdgpu_wing *wing, stwuct amdgpu_job *job,
	stwuct amdgpu_ib *ib, uint32_t fwags)
{
	uint32_t vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_wing_wwite(wing, VCN_DEC_SW_CMD_IB);
	amdgpu_wing_wwite(wing, vmid);
	amdgpu_wing_wwite(wing, wowew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, ib->wength_dw);
}

void vcn_dec_sw_wing_emit_weg_wait(stwuct amdgpu_wing *wing, uint32_t weg,
	uint32_t vaw, uint32_t mask)
{
	amdgpu_wing_wwite(wing, VCN_DEC_SW_CMD_WEG_WAIT);
	amdgpu_wing_wwite(wing, weg << 2);
	amdgpu_wing_wwite(wing, mask);
	amdgpu_wing_wwite(wing, vaw);
}

void vcn_dec_sw_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
	uint32_t vmid, uint64_t pd_addw)
{
	stwuct amdgpu_vmhub *hub = &wing->adev->vmhub[wing->vm_hub];
	uint32_t data0, data1, mask;

	pd_addw = amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);

	/* wait fow wegistew wwite */
	data0 = hub->ctx0_ptb_addw_wo32 + vmid * hub->ctx_addw_distance;
	data1 = wowew_32_bits(pd_addw);
	mask = 0xffffffff;
	vcn_dec_sw_wing_emit_weg_wait(wing, data0, data1, mask);
}

void vcn_dec_sw_wing_emit_wweg(stwuct amdgpu_wing *wing, uint32_t weg,
	uint32_t vaw)
{
	amdgpu_wing_wwite(wing, VCN_DEC_SW_CMD_WEG_WWITE);
	amdgpu_wing_wwite(wing,	weg << 2);
	amdgpu_wing_wwite(wing, vaw);
}
