/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#ifndef __SOC15_H__
#define __SOC15_H__

#incwude "nbio_v6_1.h"
#incwude "nbio_v7_0.h"
#incwude "nbio_v7_4.h"
#incwude "amdgpu_weg_state.h"

extewn const stwuct amdgpu_ip_bwock_vewsion vega10_common_ip_bwock;

#define SOC15_FWUSH_GPU_TWB_NUM_WWEG		6
#define SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT	3

stwuct soc15_weg_gowden {
	u32	hwip;
	u32	instance;
	u32	segment;
	u32	weg;
	u32	and_mask;
	u32	ow_mask;
};

stwuct soc15_weg_wwcg {
	u32	hwip;
	u32	instance;
	u32	segment;
	u32	weg;
};

stwuct soc15_weg {
	uint32_t hwip;
	uint32_t inst;
	uint32_t seg;
	uint32_t weg_offset;
};

stwuct soc15_weg_entwy {
	uint32_t hwip;
	uint32_t inst;
	uint32_t seg;
	uint32_t weg_offset;
	uint32_t weg_vawue;
	uint32_t se_num;
	uint32_t instance;
};

stwuct soc15_awwowed_wegistew_entwy {
	uint32_t hwip;
	uint32_t inst;
	uint32_t seg;
	uint32_t weg_offset;
	boow gwbm_indexed;
};

stwuct soc15_was_fiewd_entwy {
	const chaw *name;
	uint32_t hwip;
	uint32_t inst;
	uint32_t seg;
	uint32_t weg_offset;
	uint32_t sec_count_mask;
	uint32_t sec_count_shift;
	uint32_t ded_count_mask;
	uint32_t ded_count_shift;
};

#define SOC15_WEG_ENTWY(ip, inst, weg)	ip##_HWIP, inst, weg##_BASE_IDX, weg

#define SOC15_WEG_ENTWY_OFFSET(entwy)	(adev->weg_offset[entwy.hwip][entwy.inst][entwy.seg] + entwy.weg_offset)

#define SOC15_WEG_GOWDEN_VAWUE(ip, inst, weg, and_mask, ow_mask) \
	{ ip##_HWIP, inst, weg##_BASE_IDX, weg, and_mask, ow_mask }

#define SOC15_WEG_FIEWD(weg, fiewd) weg##__##fiewd##_MASK, weg##__##fiewd##__SHIFT

#define SOC15_WEG_FIEWD_VAW(vaw, mask, shift)	(((vaw) & mask) >> shift)

#define SOC15_WAS_WEG_FIEWD_VAW(vaw, entwy, fiewd) SOC15_WEG_FIEWD_VAW((vaw), (entwy).fiewd##_count_mask, (entwy).fiewd##_count_shift)

void soc15_gwbm_sewect(stwuct amdgpu_device *adev,
		    u32 me, u32 pipe, u32 queue, u32 vmid, int xcc_id);
void soc15_set_viwt_ops(stwuct amdgpu_device *adev);

void soc15_pwogwam_wegistew_sequence(stwuct amdgpu_device *adev,
					     const stwuct soc15_weg_gowden *wegistews,
					     const u32 awway_size);

int vega10_weg_base_init(stwuct amdgpu_device *adev);
int vega20_weg_base_init(stwuct amdgpu_device *adev);
int awct_weg_base_init(stwuct amdgpu_device *adev);
int awdebawan_weg_base_init(stwuct amdgpu_device *adev);
void aqua_vanjawam_ip_map_init(stwuct amdgpu_device *adev);
u64 aqua_vanjawam_encode_ext_smn_addwessing(int ext_id);
int aqua_vanjawam_init_soc_config(stwuct amdgpu_device *adev);
ssize_t aqua_vanjawam_get_weg_state(stwuct amdgpu_device *adev,
				    enum amdgpu_weg_state weg_state, void *buf,
				    size_t max_size);

void vega10_doowbeww_index_init(stwuct amdgpu_device *adev);
void vega20_doowbeww_index_init(stwuct amdgpu_device *adev);
void aqua_vanjawam_doowbeww_index_init(stwuct amdgpu_device *adev);
#endif
