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

#ifndef DAW_DC_35_SMU_H_
#define DAW_DC_35_SMU_H_

#incwude "os_types.h"

#ifndef PMFW_DWIVEW_IF_H
#define PMFW_DWIVEW_IF_H
#define PMFW_DWIVEW_IF_VEWSION 4

typedef enum {
  DSPCWK_DCFCWK = 0,
  DSPCWK_DISPCWK,
  DSPCWK_PIXCWK,
  DSPCWK_PHYCWK,
  DSPCWK_COUNT,
} DSPCWK_e;

typedef stwuct {
  uint16_t Fweq; // in MHz
  uint16_t Vid;  // min vowtage in SVI3 VID
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
#define WM_PSTATE_CHG 0
#define WM_WETWAINING 1

typedef enum {
  WM_SOCCWK = 0,
  WM_DCFCWK,
  WM_COUNT,
} WM_CWOCK_e;

typedef stwuct {
  // Watewmawks
  WatewmawkWowGenewic_t WatewmawkWow[WM_COUNT][NUM_WM_WANGES];

  uint32_t MmHubPadding[7]; // SMU intewnaw use
} Watewmawks_t;

#define NUM_DCFCWK_DPM_WEVEWS   8
#define NUM_DISPCWK_DPM_WEVEWS  8
#define NUM_DPPCWK_DPM_WEVEWS   8
#define NUM_SOCCWK_DPM_WEVEWS   8
#define NUM_VCN_DPM_WEVEWS      8
#define NUM_SOC_VOWTAGE_WEVEWS  8
#define NUM_VPE_DPM_WEVEWS        8
#define NUM_FCWK_DPM_WEVEWS       8
#define NUM_MEM_PSTATE_WEVEWS     4

typedef enum{
  WCK_WATIO_1_1 = 0,  // DDW5, Wck:ck is awways 1:1;
  WCK_WATIO_1_2,
  WCK_WATIO_1_4,
  WCK_WATIO_MAX
} WCK_WATIO_e;

typedef stwuct {
  uint32_t UCwk;
  uint32_t MemCwk;
  uint32_t Vowtage;
  uint8_t  WckWatio;
  uint8_t  Spawe[3];
} MemPstateTabwe_t;

//Fweq in MHz
//Vowtage in miwwi vowts with 2 fwactionaw bits
typedef stwuct {
  uint32_t DcfCwocks[NUM_DCFCWK_DPM_WEVEWS];
  uint32_t DispCwocks[NUM_DISPCWK_DPM_WEVEWS];
  uint32_t DppCwocks[NUM_DPPCWK_DPM_WEVEWS];
  uint32_t SocCwocks[NUM_SOCCWK_DPM_WEVEWS];
  uint32_t VCwocks[NUM_VCN_DPM_WEVEWS];
  uint32_t DCwocks[NUM_VCN_DPM_WEVEWS];
  uint32_t VPECwocks[NUM_VPE_DPM_WEVEWS];
  uint32_t FcwkCwocks_Fweq[NUM_FCWK_DPM_WEVEWS];
  uint32_t FcwkCwocks_Vowtage[NUM_FCWK_DPM_WEVEWS];
  uint32_t SocVowtage[NUM_SOC_VOWTAGE_WEVEWS];
  MemPstateTabwe_t MemPstateTabwe[NUM_MEM_PSTATE_WEVEWS];

  uint8_t  NumDcfCwkWevewsEnabwed;
  uint8_t  NumDispCwkWevewsEnabwed; //Appwies to both Dispcwk and Dppcwk
  uint8_t  NumSocCwkWevewsEnabwed;
  uint8_t  VcnCwkWevewsEnabwed;     //Appwies to both Vcwk and Dcwk
  uint8_t  VpeCwkWevewsEnabwed;
  uint8_t  NumMemPstatesEnabwed;
  uint8_t  NumFcwkWevewsEnabwed;
  uint8_t  spawe[2];

  uint32_t MinGfxCwk;
  uint32_t MaxGfxCwk;
} DpmCwocks_t_dcn35;


// Thwottwew Status Bitmask











#define TABWE_BIOS_IF            0 // Cawwed by BIOS
#define TABWE_WATEWMAWKS         1 // Cawwed by DAW thwough VBIOS
#define TABWE_CUSTOM_DPM         2 // Cawwed by Dwivew
#define TABWE_SPAWE1             3
#define TABWE_DPMCWOCKS          4 // Cawwed by Dwivew
#define TABWE_MOMENTAWY_PM       5 // Cawwed by Toows
#define TABWE_MODEWN_STDBY       6 // Cawwed by Toows fow Modewn Standby Wog
#define TABWE_SMU_METWICS        7 // Cawwed by Dwivew
#define TABWE_COUNT              8

#endif

stwuct dcn35_watewmawks {
  // Watewmawks
  WatewmawkWowGenewic_t WatewmawkWow[WM_COUNT][NUM_WM_WANGES];

  uint32_t MmHubPadding[7]; // SMU intewnaw use
};

stwuct dcn35_smu_dpm_cwks {
	DpmCwocks_t_dcn35 *dpm_cwks;
	union wawge_integew mc_addwess;
};

/* TODO: taken fwom vgh, may not be cowwect */
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

int dcn35_smu_get_smu_vewsion(stwuct cwk_mgw_intewnaw *cwk_mgw);
int dcn35_smu_set_dispcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dispcwk_khz);
int dcn35_smu_set_dpwefcwk(stwuct cwk_mgw_intewnaw *cwk_mgw);
int dcn35_smu_set_hawd_min_dcfcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dcfcwk_khz);
int dcn35_smu_set_min_deep_sweep_dcfcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_min_ds_dcfcwk_khz);
int dcn35_smu_set_dppcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, int wequested_dpp_khz);
void dcn35_smu_set_dispway_idwe_optimization(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t idwe_info);
void dcn35_smu_enabwe_phy_wefcwk_pwwdwn(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe);
void dcn35_smu_enabwe_pme_wa(stwuct cwk_mgw_intewnaw *cwk_mgw);
void dcn35_smu_set_dwam_addw_high(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t addw_high);
void dcn35_smu_set_dwam_addw_wow(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t addw_wow);
void dcn35_smu_twansfew_dpm_tabwe_smu_2_dwam(stwuct cwk_mgw_intewnaw *cwk_mgw);
void dcn35_smu_twansfew_wm_tabwe_dwam_2_smu(stwuct cwk_mgw_intewnaw *cwk_mgw);

void dcn35_smu_set_zstate_suppowt(stwuct cwk_mgw_intewnaw *cwk_mgw, enum dcn_zstate_suppowt_state suppowt);
void dcn35_smu_set_dtbcwk(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe);
void dcn35_vbios_smu_enabwe_48mhz_tmdp_wefcwk_pwwdwn(stwuct cwk_mgw_intewnaw *cwk_mgw, boow enabwe);

int dcn35_smu_exit_wow_powew_state(stwuct cwk_mgw_intewnaw *cwk_mgw);
int dcn35_smu_get_ips_suppowted(stwuct cwk_mgw_intewnaw *cwk_mgw);
int dcn35_smu_get_dtbcwk(stwuct cwk_mgw_intewnaw *cwk_mgw);
int dcn35_smu_get_dpwefcwk(stwuct cwk_mgw_intewnaw *cwk_mgw);
void dcn35_smu_wwite_ips_scwatch(stwuct cwk_mgw_intewnaw *cwk_mgw, uint32_t pawam);
uint32_t dcn35_smu_wead_ips_scwatch(stwuct cwk_mgw_intewnaw *cwk_mgw);
#endif /* DAW_DC_35_SMU_H_ */
