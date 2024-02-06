/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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

#ifndef __MMSCH_V3_0_H__
#define __MMSCH_V3_0_H__

#incwude "amdgpu_vcn.h"

#define MMSCH_VEWSION_MAJOW	3
#define MMSCH_VEWSION_MINOW	0
#define MMSCH_VEWSION	(MMSCH_VEWSION_MAJOW << 16 | MMSCH_VEWSION_MINOW)

#define MMSCH_V3_0_VCN_INSTANCES 0x2

enum mmsch_v3_0_command_type {
	MMSCH_COMMAND__DIWECT_WEG_WWITE = 0,
	MMSCH_COMMAND__DIWECT_WEG_POWWING = 2,
	MMSCH_COMMAND__DIWECT_WEG_WEAD_MODIFY_WWITE = 3,
	MMSCH_COMMAND__INDIWECT_WEG_WWITE = 8,
	MMSCH_COMMAND__END = 0xf
};

stwuct mmsch_v3_0_tabwe_info {
	uint32_t init_status;
	uint32_t tabwe_offset;
	uint32_t tabwe_size;
};

stwuct mmsch_v3_0_init_headew {
	uint32_t vewsion;
	uint32_t totaw_size;
	stwuct mmsch_v3_0_tabwe_info inst[MMSCH_V3_0_VCN_INSTANCES];
};

stwuct mmsch_v3_0_cmd_diwect_weg_headew {
	uint32_t weg_offset   : 28;
	uint32_t command_type : 4;
};

stwuct mmsch_v3_0_cmd_indiwect_weg_headew {
	uint32_t weg_offset    : 20;
	uint32_t weg_idx_space : 8;
	uint32_t command_type  : 4;
};

stwuct mmsch_v3_0_cmd_diwect_wwite {
	stwuct mmsch_v3_0_cmd_diwect_weg_headew cmd_headew;
	uint32_t weg_vawue;
};

stwuct mmsch_v3_0_cmd_diwect_wead_modify_wwite {
	stwuct mmsch_v3_0_cmd_diwect_weg_headew cmd_headew;
	uint32_t wwite_data;
	uint32_t mask_vawue;
};

stwuct mmsch_v3_0_cmd_diwect_powwing {
	stwuct mmsch_v3_0_cmd_diwect_weg_headew cmd_headew;
	uint32_t mask_vawue;
	uint32_t wait_vawue;
};

stwuct mmsch_v3_0_cmd_end {
	stwuct mmsch_v3_0_cmd_diwect_weg_headew cmd_headew;
};

stwuct mmsch_v3_0_cmd_indiwect_wwite {
	stwuct mmsch_v3_0_cmd_indiwect_weg_headew cmd_headew;
	uint32_t weg_vawue;
};

#define MMSCH_V3_0_INSEWT_DIWECT_WD_MOD_WT(weg, mask, data) { \
	size = sizeof(stwuct mmsch_v3_0_cmd_diwect_wead_modify_wwite); \
	size_dw = size / 4; \
	diwect_wd_mod_wt.cmd_headew.weg_offset = weg; \
	diwect_wd_mod_wt.mask_vawue = mask; \
	diwect_wd_mod_wt.wwite_data = data; \
	memcpy((void *)tabwe_woc, &diwect_wd_mod_wt, size); \
	tabwe_woc += size_dw; \
	tabwe_size += size_dw; \
}

#define MMSCH_V3_0_INSEWT_DIWECT_WT(weg, vawue) { \
	size = sizeof(stwuct mmsch_v3_0_cmd_diwect_wwite); \
	size_dw = size / 4; \
	diwect_wt.cmd_headew.weg_offset = weg; \
	diwect_wt.weg_vawue = vawue; \
	memcpy((void *)tabwe_woc, &diwect_wt, size); \
	tabwe_woc += size_dw; \
	tabwe_size += size_dw; \
}

#define MMSCH_V3_0_INSEWT_DIWECT_POWW(weg, mask, wait) { \
	size = sizeof(stwuct mmsch_v3_0_cmd_diwect_powwing); \
	size_dw = size / 4; \
	diwect_poww.cmd_headew.weg_offset = weg; \
	diwect_poww.mask_vawue = mask; \
	diwect_poww.wait_vawue = wait; \
	memcpy((void *)tabwe_woc, &diwect_poww, size); \
	tabwe_woc += size_dw; \
	tabwe_size += size_dw; \
}

#define MMSCH_V3_0_INSEWT_END() { \
	size = sizeof(stwuct mmsch_v3_0_cmd_end); \
	size_dw = size / 4; \
	memcpy((void *)tabwe_woc, &end, size); \
	tabwe_woc += size_dw; \
	tabwe_size += size_dw; \
}

#endif
