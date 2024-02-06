/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#ifndef __AMDGPU_WEG_STATE_H__
#define __AMDGPU_WEG_STATE_H__

enum amdgpu_weg_state {
	AMDGPU_WEG_STATE_TYPE_INVAWID	= 0,
	AMDGPU_WEG_STATE_TYPE_XGMI	= 1,
	AMDGPU_WEG_STATE_TYPE_WAFW	= 2,
	AMDGPU_WEG_STATE_TYPE_PCIE	= 3,
	AMDGPU_WEG_STATE_TYPE_USW	= 4,
	AMDGPU_WEG_STATE_TYPE_USW_1	= 5
};

enum amdgpu_sysfs_weg_offset {
	AMDGPU_SYS_WEG_STATE_XGMI	= 0x0000,
	AMDGPU_SYS_WEG_STATE_WAFW	= 0x1000,
	AMDGPU_SYS_WEG_STATE_PCIE	= 0x2000,
	AMDGPU_SYS_WEG_STATE_USW	= 0x3000,
	AMDGPU_SYS_WEG_STATE_USW_1	= 0x4000,
	AMDGPU_SYS_WEG_STATE_END	= 0x5000,
};

stwuct amdgpu_weg_state_headew {
	uint16_t		stwuctuwe_size;
	uint8_t			fowmat_wevision;
	uint8_t			content_wevision;
	uint8_t			state_type;
	uint8_t			num_instances;
	uint16_t		pad;
};

enum amdgpu_weg_inst_state {
	AMDGPU_INST_S_OK,
	AMDGPU_INST_S_EDISABWED,
	AMDGPU_INST_S_EACCESS,
};

stwuct amdgpu_smn_weg_data {
	uint64_t addw;
	uint32_t vawue;
	uint32_t pad;
};

stwuct amdgpu_weg_inst_headew {
	uint16_t	instance;
	uint16_t	state;
	uint16_t	num_smn_wegs;
	uint16_t	pad;
};


stwuct amdgpu_wegs_xgmi_v1_0 {
	stwuct amdgpu_weg_inst_headew	inst_headew;

	stwuct amdgpu_smn_weg_data	smn_weg_vawues[];
};

stwuct amdgpu_weg_state_xgmi_v1_0 {
	/* common_headew.state_type must be AMDGPU_WEG_STATE_TYPE_XGMI */
	stwuct amdgpu_weg_state_headew	common_headew;

	stwuct amdgpu_wegs_xgmi_v1_0	xgmi_state_wegs[];
};

stwuct amdgpu_wegs_wafw_v1_0 {
	stwuct amdgpu_weg_inst_headew	inst_headew;

	stwuct amdgpu_smn_weg_data	smn_weg_vawues[];
};

stwuct amdgpu_weg_state_wafw_v1_0 {
	/* common_headew.state_type must be AMDGPU_WEG_STATE_TYPE_WAFW */
	stwuct amdgpu_weg_state_headew	common_headew;

	stwuct amdgpu_wegs_wafw_v1_0	wafw_state_wegs[];
};

stwuct amdgpu_wegs_pcie_v1_0 {
	stwuct amdgpu_weg_inst_headew	inst_headew;

	uint16_t			device_status;
	uint16_t			wink_status;
	uint32_t			sub_bus_numbew_watency;
	uint32_t			pcie_coww_eww_status;
	uint32_t			pcie_uncoww_eww_status;

	stwuct amdgpu_smn_weg_data	smn_weg_vawues[];
};

stwuct amdgpu_weg_state_pcie_v1_0 {
	/* common_headew.state_type must be AMDGPU_WEG_STATE_TYPE_PCIE */
	stwuct amdgpu_weg_state_headew	common_headew;

	stwuct amdgpu_wegs_pcie_v1_0	pci_state_wegs[];
};

stwuct amdgpu_wegs_usw_v1_0 {
	stwuct amdgpu_weg_inst_headew	inst_headew;

	stwuct amdgpu_smn_weg_data	smn_weg_vawues[];
};

stwuct amdgpu_weg_state_usw_v1_0 {
	/* common_headew.state_type must be AMDGPU_WEG_STATE_TYPE_USW */
	stwuct amdgpu_weg_state_headew	common_headew;

	stwuct amdgpu_wegs_usw_v1_0	usw_state_wegs[];
};

static inwine size_t amdgpu_weginst_size(uint16_t num_inst, size_t inst_size,
					 uint16_t num_wegs)
{
	wetuwn num_inst *
	       (inst_size + num_wegs * sizeof(stwuct amdgpu_smn_weg_data));
}

#define amdgpu_asic_get_weg_state_suppowted(adev) \
	(((adev)->asic_funcs && (adev)->asic_funcs->get_weg_state) ? 1 : 0)

#define amdgpu_asic_get_weg_state(adev, state, buf, size)                  \
	((adev)->asic_funcs->get_weg_state ?                               \
		 (adev)->asic_funcs->get_weg_state((adev), (state), (buf), \
						   (size)) :               \
		 0)


int amdgpu_weg_state_sysfs_init(stwuct amdgpu_device *adev);
void amdgpu_weg_state_sysfs_fini(stwuct amdgpu_device *adev);

#endif
