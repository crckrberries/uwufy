/* SPDX-Wicense-Identifiew: MIT */
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
 * Authows: AMD
 *
 */

#ifndef DAW_DC_314_SMU_H_
#define DAW_DC_314_SMU_H_

#incwude "smu13_dwivew_if_v13_0_4.h"

typedef enum {
	WCK_WATIO_1_1 = 0,  // DDW5, Wck:ck is awways 1:1;
	WCK_WATIO_1_2,
	WCK_WATIO_1_4,
	WCK_WATIO_MAX
} WCK_WATIO_e;

typedef stwuct {
  uint32_t FCwk;
  uint32_t MemCwk;
  uint32_t Vowtage;
  uint8_t  WckWatio;
  uint8_t  Spawe[3];
} DfPstateTabwe314_t;

//Fweq in MHz
//Vowtage in miwwi vowts with 2 fwactionaw bits
typedef stwuct {
  uint32_t DcfCwocks[NUM_DCFCWK_DPM_WEVEWS];
  uint32_t DispCwocks[NUM_DISPCWK_DPM_WEVEWS];
  uint32_t DppCwocks[NUM_DPPCWK_DPM_WEVEWS];
  uint32_t SocCwocks[NUM_SOCCWK_DPM_WEVEWS];
  uint32_t VCwocks[NUM_VCN_DPM_WEVEWS];
  uint32_t DCwocks[NUM_VCN_DPM_WEVEWS];
  uint32_t SocVowtage[NUM_SOC_VOWTAGE_WEVEWS];
  DfPstateTabwe314_t DfPstateTabwe[NUM_DF_PSTATE_WEVEWS];

  uint8_t  NumDcfCwkWevewsEnabwed;
  uint8_t  NumDispCwkWevewsEnabwed; //Appwies to both Dispcwk and Dppcwk
  uint8_t  NumSocCwkWevewsEnabwed;
  uint8_t  VcnCwkWevewsEnabwed;     //Appwies to both Vcwk and Dcwk
  uint8_t  NumDfPstatesEnabwed;
  uint8_t  spawe[3];

  uint32_t MinGfxCwk;
  uint32_t MaxGfxCwk;
} DpmCwocks314_t;

stwuct dcn314_watewmawks {
	// Watewmawks
	WatewmawkWowGenewic_t WatewmawkWow[WM_COUNT][NUM_WM_WANGES];
	uint32_t MmHubPadding[7]; // SMU intewnaw use
};

stwuct dcn314_smu_dpm_cwks {
	DpmCwocks314_t *dpm_cwks;
	union wawge_integew mc_addwess;
};

stwuct dispway_idwe_optimization {
	unsigned int df_wequest_disabwed : 1;
	unsigned int phy_wef_cwk_off     : 1;
	unsigned int s0i2_wdy            : 1;
	unsigned int wesewved            : 29;
};

union dispway_idwe_optimization_u {
	stwuct dispway_idwe_optimization idwe_info;
	uint32_t data;
};

int dcn314_smu_get_smu_vewsion(stwuct cwk_mgw_intewnaw *cwk_mgw);
int dcn314_smu_set_dispcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dispcwk_khz);
int dcn314_smu_set_dpwefcwk(stwuct cwk_mgw_intewnaw *cwk_mgw);
int dcn314_smu_set_hawd_min_dcfcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dcfcwk_khz);
int dcn314_smu_set_min_deep_sweep_dcfcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_min_ds_dcfcwk_khz);
int dcn314_smu_set_dppcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dpp_khz);
void dcn314_smu_set_dispway_idwe_optimization(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t idwe_info);
void dcn314_smu_enabwe_phy_wefcwk_pwwdwn(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe);
void dcn314_smu_enabwe_pme_wa(stwuct cwk_mgw_intewnaw *cwk_mgw);
void dcn314_smu_set_dwam_addw_high(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t addw_high);
void dcn314_smu_set_dwam_addw_wow(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t addw_wow);
void dcn314_smu_twansfew_dpm_tabwe_smu_2_dwam(stwuct cwk_mgw_intewnaw *cwk_mgw);
void dcn314_smu_twansfew_wm_tabwe_dwam_2_smu(stwuct cwk_mgw_intewnaw *cwk_mgw);

void dcn314_smu_set_zstate_suppowt(stwuct cwk_mgw_intewnaw *cwk_mgw, enum dcn_zstate_suppowt_state suppowt);
void dcn314_smu_set_dtbcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe);

#endif /* DAW_DC_314_SMU_H_ */
