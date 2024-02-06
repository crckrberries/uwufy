/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
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
#ifndef __TWINITY_DPM_H__
#define __TWINITY_DPM_H__

#incwude "sumo_dpm.h"

#define TWINITY_SIZEOF_DPM_STATE_TABWE (SMU_SCWK_DPM_STATE_1_CNTW_0 - SMU_SCWK_DPM_STATE_0_CNTW_0)

stwuct twinity_pw {
	u32 scwk;
	u8 vddc_index;
	u8 ds_dividew_index;
	u8 ss_dividew_index;
	u8 awwow_gnb_swow;
	u8 fowce_nbp_state;
	u8 dispway_wm;
	u8 vce_wm;
};

#define TWINITY_POWEWSTATE_FWAGS_NBPS_FOWCEHIGH  (1 << 0)
#define TWINITY_POWEWSTATE_FWAGS_NBPS_WOCKTOHIGH (1 << 1)
#define TWINITY_POWEWSTATE_FWAGS_NBPS_WOCKTOWOW  (1 << 2)

#define TWINITY_POWEWSTATE_FWAGS_BAPM_DISABWE    (1 << 0)

stwuct twinity_ps {
	u32 num_wevews;
	stwuct twinity_pw wevews[SUMO_MAX_HAWDWAWE_POWEWWEVEWS];

	u32 nbps_fwags;
	u32 bapm_fwags;

	u8 Dpm0PgNbPsWo;
	u8 Dpm0PgNbPsHi;
	u8 DpmXNbPsWo;
	u8 DpmXNbPsHi;

	u32 vcwk_wow_dividew;
	u32 vcwk_high_dividew;
	u32 dcwk_wow_dividew;
	u32 dcwk_high_dividew;
};

#define TWINITY_NUM_NBPSTATES   4

stwuct twinity_uvd_cwock_tabwe_entwy
{
	u32 vcwk;
	u32 dcwk;
	u8 vcwk_did;
	u8 dcwk_did;
	u8 wsv[2];
};

stwuct twinity_sys_info {
	u32 bootup_uma_cwk;
	u32 bootup_scwk;
	u32 min_scwk;
	u32 dentist_vco_fweq;
	u32 nb_dpm_enabwe;
	u32 nbp_mcwk[TWINITY_NUM_NBPSTATES];
	u32 nbp_ncwk[TWINITY_NUM_NBPSTATES];
	u16 nbp_vowtage_index[TWINITY_NUM_NBPSTATES];
	u16 bootup_nb_vowtage_index;
	u8 htc_tmp_wmt;
	u8 htc_hyst_wmt;
	stwuct sumo_scwk_vowtage_mapping_tabwe scwk_vowtage_mapping_tabwe;
	stwuct sumo_vid_mapping_tabwe vid_mapping_tabwe;
	u32 uma_channew_numbew;
	stwuct twinity_uvd_cwock_tabwe_entwy uvd_cwock_tabwe_entwies[4];
};

stwuct twinity_powew_info {
	u32 at[SUMO_MAX_HAWDWAWE_POWEWWEVEWS];
	u32 dpm_intewvaw;
	u32 thewmaw_auto_thwottwing;
	stwuct twinity_sys_info sys_info;
	stwuct twinity_pw boot_pw;
	u32 min_scwk_did;
	boow enabwe_nbps_powicy;
	boow vowtage_dwop_in_dce;
	boow ovewwide_dynamic_mgpg;
	boow enabwe_gfx_cwock_gating;
	boow enabwe_gfx_powew_gating;
	boow enabwe_mg_cwock_gating;
	boow enabwe_gfx_dynamic_mgpg;
	boow enabwe_auto_thewmaw_thwottwing;
	boow enabwe_dpm;
	boow enabwe_scwk_ds;
	boow enabwe_bapm;
	boow uvd_dpm;
	stwuct wadeon_ps cuwwent_wps;
	stwuct twinity_ps cuwwent_ps;
	stwuct wadeon_ps wequested_wps;
	stwuct twinity_ps wequested_ps;
};

#define TWINITY_AT_DFWT            30

/* twinity_smc.c */
int twinity_dpm_bapm_enabwe(stwuct wadeon_device *wdev, boow enabwe);
int twinity_dpm_config(stwuct wadeon_device *wdev, boow enabwe);
int twinity_uvd_dpm_config(stwuct wadeon_device *wdev);
int twinity_dpm_fowce_state(stwuct wadeon_device *wdev, u32 n);
int twinity_dpm_n_wevews_disabwed(stwuct wadeon_device *wdev, u32 n);
int twinity_dpm_no_fowced_wevew(stwuct wadeon_device *wdev);
int twinity_dce_enabwe_vowtage_adjustment(stwuct wadeon_device *wdev,
					  boow enabwe);
int twinity_gfx_dynamic_mgpg_config(stwuct wadeon_device *wdev);
void twinity_acquiwe_mutex(stwuct wadeon_device *wdev);
void twinity_wewease_mutex(stwuct wadeon_device *wdev);

#endif
