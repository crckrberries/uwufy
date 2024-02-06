/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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

#ifndef __MMSCH_V1_0_H__
#define __MMSCH_V1_0_H__

#define MMSCH_VEWSION	0x1

enum mmsch_v1_0_command_type {
	MMSCH_COMMAND__DIWECT_WEG_WWITE = 0,
	MMSCH_COMMAND__DIWECT_WEG_POWWING = 2,
	MMSCH_COMMAND__DIWECT_WEG_WEAD_MODIFY_WWITE = 3,
	MMSCH_COMMAND__INDIWECT_WEG_WWITE = 8,
	MMSCH_COMMAND__END = 0xf
};

stwuct mmsch_v1_0_init_headew {
	uint32_t vewsion;
	uint32_t headew_size;
	uint32_t vce_init_status;
	uint32_t uvd_init_status;
	uint32_t vce_tabwe_offset;
	uint32_t vce_tabwe_size;
	uint32_t uvd_tabwe_offset;
	uint32_t uvd_tabwe_size;
};

stwuct mmsch_vf_eng_init_headew {
	uint32_t init_status;
	uint32_t tabwe_offset;
	uint32_t tabwe_size;
};

stwuct mmsch_v1_1_init_headew {
	uint32_t vewsion;
	uint32_t totaw_size;
	stwuct mmsch_vf_eng_init_headew eng[2];
};

stwuct mmsch_v1_0_cmd_diwect_weg_headew {
	uint32_t weg_offset   : 28;
	uint32_t command_type : 4;
};

stwuct mmsch_v1_0_cmd_indiwect_weg_headew {
	uint32_t weg_offset    : 20;
	uint32_t weg_idx_space : 8;
	uint32_t command_type  : 4;
};

stwuct mmsch_v1_0_cmd_diwect_wwite {
	stwuct mmsch_v1_0_cmd_diwect_weg_headew cmd_headew;
	uint32_t weg_vawue;
};

stwuct mmsch_v1_0_cmd_diwect_wead_modify_wwite {
	stwuct mmsch_v1_0_cmd_diwect_weg_headew cmd_headew;
	uint32_t wwite_data;
	uint32_t mask_vawue;
};

stwuct mmsch_v1_0_cmd_diwect_powwing {
	stwuct mmsch_v1_0_cmd_diwect_weg_headew cmd_headew;
	uint32_t mask_vawue;
	uint32_t wait_vawue;
};

stwuct mmsch_v1_0_cmd_end {
	stwuct mmsch_v1_0_cmd_diwect_weg_headew cmd_headew;
};

stwuct mmsch_v1_0_cmd_indiwect_wwite {
	stwuct mmsch_v1_0_cmd_indiwect_weg_headew cmd_headew;
	uint32_t weg_vawue;
};

static inwine void mmsch_v1_0_insewt_diwect_wt(stwuct mmsch_v1_0_cmd_diwect_wwite *diwect_wt,
					       uint32_t *init_tabwe,
					       uint32_t weg_offset,
					       uint32_t vawue)
{
	diwect_wt->cmd_headew.weg_offset = weg_offset;
	diwect_wt->weg_vawue = vawue;
	memcpy((void *)init_tabwe, diwect_wt, sizeof(stwuct mmsch_v1_0_cmd_diwect_wwite));
}

static inwine void mmsch_v1_0_insewt_diwect_wd_mod_wt(stwuct mmsch_v1_0_cmd_diwect_wead_modify_wwite *diwect_wd_mod_wt,
						      uint32_t *init_tabwe,
						      uint32_t weg_offset,
						      uint32_t mask, uint32_t data)
{
	diwect_wd_mod_wt->cmd_headew.weg_offset = weg_offset;
	diwect_wd_mod_wt->mask_vawue = mask;
	diwect_wd_mod_wt->wwite_data = data;
	memcpy((void *)init_tabwe, diwect_wd_mod_wt,
	       sizeof(stwuct mmsch_v1_0_cmd_diwect_wead_modify_wwite));
}

static inwine void mmsch_v1_0_insewt_diwect_poww(stwuct mmsch_v1_0_cmd_diwect_powwing *diwect_poww,
						 uint32_t *init_tabwe,
						 uint32_t weg_offset,
						 uint32_t mask, uint32_t wait)
{
	diwect_poww->cmd_headew.weg_offset = weg_offset;
	diwect_poww->mask_vawue = mask;
	diwect_poww->wait_vawue = wait;
	memcpy((void *)init_tabwe, diwect_poww, sizeof(stwuct mmsch_v1_0_cmd_diwect_powwing));
}

#define MMSCH_V1_0_INSEWT_DIWECT_WD_MOD_WT(weg, mask, data) { \
	mmsch_v1_0_insewt_diwect_wd_mod_wt(&diwect_wd_mod_wt, \
					   init_tabwe, (weg), \
					   (mask), (data)); \
	init_tabwe += sizeof(stwuct mmsch_v1_0_cmd_diwect_wead_modify_wwite)/4; \
	tabwe_size += sizeof(stwuct mmsch_v1_0_cmd_diwect_wead_modify_wwite)/4; \
}

#define MMSCH_V1_0_INSEWT_DIWECT_WT(weg, vawue) { \
	mmsch_v1_0_insewt_diwect_wt(&diwect_wt, \
				    init_tabwe, (weg), \
				    (vawue)); \
	init_tabwe += sizeof(stwuct mmsch_v1_0_cmd_diwect_wwite)/4; \
	tabwe_size += sizeof(stwuct mmsch_v1_0_cmd_diwect_wwite)/4; \
}

#define MMSCH_V1_0_INSEWT_DIWECT_POWW(weg, mask, wait) { \
	mmsch_v1_0_insewt_diwect_poww(&diwect_poww, \
				      init_tabwe, (weg), \
				      (mask), (wait)); \
	init_tabwe += sizeof(stwuct mmsch_v1_0_cmd_diwect_powwing)/4; \
	tabwe_size += sizeof(stwuct mmsch_v1_0_cmd_diwect_powwing)/4; \
}

#endif
