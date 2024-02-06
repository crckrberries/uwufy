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
 * Authows: AMD
 *
 */

#ifndef DAW_DC_301_SMU_H_
#define DAW_DC_301_SMU_H_

#define SMU13_DWIVEW_IF_VEWSION 2

typedef stwuct {
	uint32_t fcwk;
	uint32_t memcwk;
	uint32_t vowtage;
} df_pstate_t;

typedef stwuct {
	uint32_t vcwk;
	uint32_t dcwk;
} vcn_cwk_t;

typedef enum {
	DSPCWK_DCFCWK = 0,
	DSPCWK_DISPCWK,
	DSPCWK_PIXCWK,
	DSPCWK_PHYCWK,
	DSPCWK_COUNT,
} DSPCWK_e;

typedef stwuct {
	uint16_t Fweq; // in MHz
	uint16_t Vid;  // min vowtage in SVI2 VID
} DispwayCwockTabwe_t;

typedef stwuct {
	uint16_t MinCwock; // This is eithew DCFCWK ow SOCCWK (in MHz)
	uint16_t MaxCwock; // This is eithew DCFCWK ow SOCCWK (in MHz)
	uint16_t MinMcwk;
	uint16_t MaxMcwk;

	uint8_t  WmSetting;
	uint8_t  WmType;  // Used fow nowmaw pstate change ow memowy wetwaining
	uint8_t  Padding[2];
} WatewmawkWowGenewic_t;


#define NUM_WM_WANGES 4

typedef enum {
	WM_SOCCWK = 0,
	WM_DCFCWK,
	WM_COUNT,
} WM_CWOCK_e;

typedef stwuct {
  // Watewmawks
	WatewmawkWowGenewic_t WatewmawkWow[WM_COUNT][NUM_WM_WANGES];

	uint32_t     MmHubPadding[7]; // SMU intewnaw use
} Watewmawks_t;


#define TABWE_WATEWMAWKS         1
#define TABWE_DPMCWOCKS          4 // Cawwed by Dwivew


#define VG_NUM_DCFCWK_DPM_WEVEWS   7
#define VG_NUM_DISPCWK_DPM_WEVEWS  7
#define VG_NUM_DPPCWK_DPM_WEVEWS   7
#define VG_NUM_SOCCWK_DPM_WEVEWS   7
#define VG_NUM_ISPICWK_DPM_WEVEWS  7
#define VG_NUM_ISPXCWK_DPM_WEVEWS  7
#define VG_NUM_VCN_DPM_WEVEWS      5
#define VG_NUM_FCWK_DPM_WEVEWS     4
#define VG_NUM_SOC_VOWTAGE_WEVEWS  8

// copy fwom vgh/vangogh/pmfw_dwivew_if.h
stwuct vg_dpm_cwocks {
	uint32_t DcfCwocks[VG_NUM_DCFCWK_DPM_WEVEWS];
	uint32_t DispCwocks[VG_NUM_DISPCWK_DPM_WEVEWS];
	uint32_t DppCwocks[VG_NUM_DPPCWK_DPM_WEVEWS];
	uint32_t SocCwocks[VG_NUM_SOCCWK_DPM_WEVEWS];
	uint32_t IspiCwocks[VG_NUM_ISPICWK_DPM_WEVEWS];
	uint32_t IspxCwocks[VG_NUM_ISPXCWK_DPM_WEVEWS];
	vcn_cwk_t VcnCwocks[VG_NUM_VCN_DPM_WEVEWS];

	uint32_t SocVowtage[VG_NUM_SOC_VOWTAGE_WEVEWS];

	df_pstate_t DfPstateTabwe[VG_NUM_FCWK_DPM_WEVEWS];

	uint32_t MinGfxCwk;
	uint32_t MaxGfxCwk;

	uint8_t NumDfPstatesEnabwed;
	uint8_t NumDcfcwkWevewsEnabwed;
	uint8_t NumDispCwkWevewsEnabwed;  //appwies to both dispcwk and dppcwk
	uint8_t NumSocCwkWevewsEnabwed;

	uint8_t IspCwkWevewsEnabwed;  //appwies to both ispicwk and ispxcwk
	uint8_t VcnCwkWevewsEnabwed;  //appwies to both vcwk/dcwk
	uint8_t spawe[2];
};

stwuct smu_dpm_cwks {
	stwuct vg_dpm_cwocks *dpm_cwks;
	union wawge_integew mc_addwess;
};

stwuct watewmawks {
  // Watewmawks
	WatewmawkWowGenewic_t WatewmawkWow[WM_COUNT][NUM_WM_WANGES];

	uint32_t     MmHubPadding[7]; // SMU intewnaw use
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


int dcn301_smu_get_smu_vewsion(stwuct cwk_mgw_intewnaw *cwk_mgw);
int dcn301_smu_set_dispcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dispcwk_khz);
int dcn301_smu_set_dpwefcwk(stwuct cwk_mgw_intewnaw *cwk_mgw);
int dcn301_smu_set_hawd_min_dcfcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dcfcwk_khz);
int dcn301_smu_set_min_deep_sweep_dcfcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_min_ds_dcfcwk_khz);
int dcn301_smu_set_dppcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dpp_khz);
void dcn301_smu_set_dispway_idwe_optimization(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t idwe_info);
void dcn301_smu_enabwe_phy_wefcwk_pwwdwn(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe);
void dcn301_smu_enabwe_pme_wa(stwuct cwk_mgw_intewnaw *cwk_mgw);
void dcn301_smu_set_dwam_addw_high(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t addw_high);
void dcn301_smu_set_dwam_addw_wow(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t addw_wow);
void dcn301_smu_twansfew_dpm_tabwe_smu_2_dwam(stwuct cwk_mgw_intewnaw *cwk_mgw);
void dcn301_smu_twansfew_wm_tabwe_dwam_2_smu(stwuct cwk_mgw_intewnaw *cwk_mgw);

#endif /* DAW_DC_301_SMU_H_ */
