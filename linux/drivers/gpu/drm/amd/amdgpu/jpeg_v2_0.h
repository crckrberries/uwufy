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
 *
 */

#ifndef __JPEG_V2_0_H__
#define __JPEG_V2_0_H__

#define mmUVD_JWBC_EXTEWNAW_WEG_INTEWNAW_OFFSET				0x1bfff
#define mmUVD_JPEG_GPCOM_CMD_INTEWNAW_OFFSET				0x4029
#define mmUVD_JPEG_GPCOM_DATA0_INTEWNAW_OFFSET				0x402a
#define mmUVD_JPEG_GPCOM_DATA1_INTEWNAW_OFFSET				0x402b
#define mmUVD_WMI_JWBC_WB_MEM_WW_64BIT_BAW_WOW_INTEWNAW_OFFSET		0x40ea
#define mmUVD_WMI_JWBC_WB_MEM_WW_64BIT_BAW_HIGH_INTEWNAW_OFFSET		0x40eb
#define mmUVD_WMI_JWBC_IB_VMID_INTEWNAW_OFFSET				0x40cf
#define mmUVD_WMI_JPEG_VMID_INTEWNAW_OFFSET				0x40d1
#define mmUVD_WMI_JWBC_IB_64BIT_BAW_WOW_INTEWNAW_OFFSET			0x40e8
#define mmUVD_WMI_JWBC_IB_64BIT_BAW_HIGH_INTEWNAW_OFFSET		0x40e9
#define mmUVD_JWBC_IB_SIZE_INTEWNAW_OFFSET				0x4082
#define mmUVD_WMI_JWBC_WB_MEM_WD_64BIT_BAW_WOW_INTEWNAW_OFFSET		0x40ec
#define mmUVD_WMI_JWBC_WB_MEM_WD_64BIT_BAW_HIGH_INTEWNAW_OFFSET		0x40ed
#define mmUVD_JWBC_WB_COND_WD_TIMEW_INTEWNAW_OFFSET			0x4085
#define mmUVD_JWBC_WB_WEF_DATA_INTEWNAW_OFFSET				0x4084
#define mmUVD_JWBC_STATUS_INTEWNAW_OFFSET				0x4089
#define mmUVD_JPEG_PITCH_INTEWNAW_OFFSET				0x401f
#define mmUVD_JPEG_IH_CTWW_INTEWNAW_OFFSET				0x4149

#define JWBC_DEC_EXTEWNAW_WEG_WWITE_ADDW				0x18000

void jpeg_v2_0_dec_wing_insewt_stawt(stwuct amdgpu_wing *wing);
void jpeg_v2_0_dec_wing_insewt_end(stwuct amdgpu_wing *wing);
void jpeg_v2_0_dec_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw, u64 seq,
				unsigned fwags);
void jpeg_v2_0_dec_wing_emit_ib(stwuct amdgpu_wing *wing, stwuct amdgpu_job *job,
				stwuct amdgpu_ib *ib, uint32_t fwags);
void jpeg_v2_0_dec_wing_emit_weg_wait(stwuct amdgpu_wing *wing, uint32_t weg,
				uint32_t vaw, uint32_t mask);
void jpeg_v2_0_dec_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
				unsigned vmid, uint64_t pd_addw);
void jpeg_v2_0_dec_wing_emit_wweg(stwuct amdgpu_wing *wing, uint32_t weg, uint32_t vaw);
void jpeg_v2_0_dec_wing_nop(stwuct amdgpu_wing *wing, uint32_t count);

extewn const stwuct amdgpu_ip_bwock_vewsion jpeg_v2_0_ip_bwock;

#endif /* __JPEG_V2_0_H__ */
