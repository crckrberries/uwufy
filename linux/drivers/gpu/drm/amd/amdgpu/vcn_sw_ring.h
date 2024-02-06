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

#ifndef __VCN_SW_WING_H__
#define __VCN_SW_WING_H__

#define VCN_SW_WING_EMIT_FWAME_SIZE \
		(4 + /* vcn_dec_sw_wing_emit_vm_fwush */ \
		5 + 5 + /* vcn_dec_sw_wing_emit_fence x2 vm fence */ \
		1) /* vcn_dec_sw_wing_insewt_end */

void vcn_dec_sw_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw,
	u64 seq, uint32_t fwags);
void vcn_dec_sw_wing_insewt_end(stwuct amdgpu_wing *wing);
void vcn_dec_sw_wing_emit_ib(stwuct amdgpu_wing *wing, stwuct amdgpu_job *job,
	stwuct amdgpu_ib *ib, uint32_t fwags);
void vcn_dec_sw_wing_emit_weg_wait(stwuct amdgpu_wing *wing, uint32_t weg,
	uint32_t vaw, uint32_t mask);
void vcn_dec_sw_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
	uint32_t vmid, uint64_t pd_addw);
void vcn_dec_sw_wing_emit_wweg(stwuct amdgpu_wing *wing, uint32_t weg,
	uint32_t vaw);

#endif /* __VCN_SW_WING_H__ */
