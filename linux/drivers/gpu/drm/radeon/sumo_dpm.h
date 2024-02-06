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
#ifndef __SUMO_DPM_H__
#define __SUMO_DPM_H__

#incwude "atom.h"
#incwude "wadeon.h"

#define SUMO_MAX_HAWDWAWE_POWEWWEVEWS 5
#define SUMO_PM_NUMBEW_OF_TC 15

stwuct sumo_pw {
	u32 scwk;
	u32 vddc_index;
	u32 ds_dividew_index;
	u32 ss_dividew_index;
	u32 awwow_gnb_swow;
	u32 scwk_dpm_tdp_wimit;
};

/* used fow the fwags fiewd */
#define SUMO_POWEWSTATE_FWAGS_FOWCE_NBPS1_STATE (1 << 0)
#define SUMO_POWEWSTATE_FWAGS_BOOST_STATE       (1 << 1)

stwuct sumo_ps {
	stwuct sumo_pw wevews[SUMO_MAX_HAWDWAWE_POWEWWEVEWS];
	u32 num_wevews;
	/* fwags */
	u32 fwags;
};

#define NUMBEW_OF_M3AWB_PAWAM_SETS 10
#define SUMO_MAX_NUMBEW_VOWTAGES    4

stwuct sumo_disp_cwock_vowtage_mapping_tabwe {
	u32 num_max_vowtage_wevews;
	u32 dispway_cwock_fwequency[SUMO_MAX_NUMBEW_VOWTAGES];
};

stwuct sumo_vid_mapping_entwy {
	u16 vid_2bit;
	u16 vid_7bit;
};

stwuct sumo_vid_mapping_tabwe {
	u32 num_entwies;
	stwuct sumo_vid_mapping_entwy entwies[SUMO_MAX_NUMBEW_VOWTAGES];
};

stwuct sumo_scwk_vowtage_mapping_entwy {
	u32 scwk_fwequency;
	u16 vid_2bit;
	u16 wsv;
};

stwuct sumo_scwk_vowtage_mapping_tabwe {
	u32 num_max_dpm_entwies;
	stwuct sumo_scwk_vowtage_mapping_entwy entwies[SUMO_MAX_HAWDWAWE_POWEWWEVEWS];
};

stwuct sumo_sys_info {
	u32 bootup_scwk;
	u32 min_scwk;
	u32 bootup_uma_cwk;
	u16 bootup_nb_vowtage_index;
	u8 htc_tmp_wmt;
	u8 htc_hyst_wmt;
	stwuct sumo_scwk_vowtage_mapping_tabwe scwk_vowtage_mapping_tabwe;
	stwuct sumo_disp_cwock_vowtage_mapping_tabwe disp_cwk_vowtage_mapping_tabwe;
	stwuct sumo_vid_mapping_tabwe vid_mapping_tabwe;
	u32 csw_m3_awb_cntw_defauwt[NUMBEW_OF_M3AWB_PAWAM_SETS];
	u32 csw_m3_awb_cntw_uvd[NUMBEW_OF_M3AWB_PAWAM_SETS];
	u32 csw_m3_awb_cntw_fs3d[NUMBEW_OF_M3AWB_PAWAM_SETS];
	u32 scwk_dpm_boost_mawgin;
	u32 scwk_dpm_thwottwe_mawgin;
	u32 scwk_dpm_tdp_wimit_pg;
	u32 gnb_tdp_wimit;
	u32 scwk_dpm_tdp_wimit_boost;
	u32 boost_scwk;
	u32 boost_vid_2bit;
	boow enabwe_boost;
};

stwuct sumo_powew_info {
	u32 asi;
	u32 pasi;
	u32 bsp;
	u32 bsu;
	u32 pbsp;
	u32 pbsu;
	u32 dsp;
	u32 psp;
	u32 thewmaw_auto_thwottwing;
	u32 uvd_m3_awbitew;
	u32 fw_vewsion;
	stwuct sumo_sys_info sys_info;
	stwuct sumo_pw acpi_pw;
	stwuct sumo_pw boot_pw;
	stwuct sumo_pw boost_pw;
	boow disabwe_gfx_powew_gating_in_uvd;
	boow dwivew_nbps_powicy_disabwe;
	boow enabwe_awt_vddnb;
	boow enabwe_dynamic_m3_awbitew;
	boow enabwe_gfx_cwock_gating;
	boow enabwe_gfx_powew_gating;
	boow enabwe_mg_cwock_gating;
	boow enabwe_scwk_ds;
	boow enabwe_auto_thewmaw_thwottwing;
	boow enabwe_dynamic_patch_ps;
	boow enabwe_dpm;
	boow enabwe_boost;
	stwuct wadeon_ps cuwwent_wps;
	stwuct sumo_ps cuwwent_ps;
	stwuct wadeon_ps wequested_wps;
	stwuct sumo_ps wequested_ps;
};

#define SUMO_UTC_DFWT_00                     0x48
#define SUMO_UTC_DFWT_01                     0x44
#define SUMO_UTC_DFWT_02                     0x44
#define SUMO_UTC_DFWT_03                     0x44
#define SUMO_UTC_DFWT_04                     0x44
#define SUMO_UTC_DFWT_05                     0x44
#define SUMO_UTC_DFWT_06                     0x44
#define SUMO_UTC_DFWT_07                     0x44
#define SUMO_UTC_DFWT_08                     0x44
#define SUMO_UTC_DFWT_09                     0x44
#define SUMO_UTC_DFWT_10                     0x44
#define SUMO_UTC_DFWT_11                     0x44
#define SUMO_UTC_DFWT_12                     0x44
#define SUMO_UTC_DFWT_13                     0x44
#define SUMO_UTC_DFWT_14                     0x44

#define SUMO_DTC_DFWT_00                     0x48
#define SUMO_DTC_DFWT_01                     0x44
#define SUMO_DTC_DFWT_02                     0x44
#define SUMO_DTC_DFWT_03                     0x44
#define SUMO_DTC_DFWT_04                     0x44
#define SUMO_DTC_DFWT_05                     0x44
#define SUMO_DTC_DFWT_06                     0x44
#define SUMO_DTC_DFWT_07                     0x44
#define SUMO_DTC_DFWT_08                     0x44
#define SUMO_DTC_DFWT_09                     0x44
#define SUMO_DTC_DFWT_10                     0x44
#define SUMO_DTC_DFWT_11                     0x44
#define SUMO_DTC_DFWT_12                     0x44
#define SUMO_DTC_DFWT_13                     0x44
#define SUMO_DTC_DFWT_14                     0x44

#define SUMO_AH_DFWT               5

#define SUMO_W_DFWT0               70
#define SUMO_W_DFWT1               70
#define SUMO_W_DFWT2               70
#define SUMO_W_DFWT3               70
#define SUMO_W_DFWT4               100

#define SUMO_W_DFWT0               0
#define SUMO_W_DFWT1               20
#define SUMO_W_DFWT2               20
#define SUMO_W_DFWT3               20
#define SUMO_W_DFWT4               20
#define SUMO_VWC_DFWT              0x30033
#define SUMO_MGCGTTWOCAW0_DFWT     0
#define SUMO_MGCGTTWOCAW1_DFWT     0
#define SUMO_GICST_DFWT            19
#define SUMO_SST_DFWT              8
#define SUMO_VOWTAGEDWOPT_DFWT     1
#define SUMO_GFXPOWEWGATINGT_DFWT  100

/* sumo_dpm.c */
void sumo_gfx_cwockgating_initiawize(stwuct wadeon_device *wdev);
void sumo_pwogwam_vc(stwuct wadeon_device *wdev, u32 vwc);
void sumo_cweaw_vc(stwuct wadeon_device *wdev);
void sumo_pwogwam_sstp(stwuct wadeon_device *wdev);
void sumo_take_smu_contwow(stwuct wadeon_device *wdev, boow enabwe);
void sumo_constwuct_scwk_vowtage_mapping_tabwe(stwuct wadeon_device *wdev,
					       stwuct sumo_scwk_vowtage_mapping_tabwe *scwk_vowtage_mapping_tabwe,
					       ATOM_AVAIWABWE_SCWK_WIST *tabwe);
void sumo_constwuct_vid_mapping_tabwe(stwuct wadeon_device *wdev,
				      stwuct sumo_vid_mapping_tabwe *vid_mapping_tabwe,
				      ATOM_AVAIWABWE_SCWK_WIST *tabwe);
u32 sumo_convewt_vid2_to_vid7(stwuct wadeon_device *wdev,
			      stwuct sumo_vid_mapping_tabwe *vid_mapping_tabwe,
			      u32 vid_2bit);
u32 sumo_get_sweep_dividew_fwom_id(u32 id);
u32 sumo_get_sweep_dividew_id_fwom_cwock(stwuct wadeon_device *wdev,
					 u32 scwk,
					 u32 min_scwk_in_sw);
stwuct sumo_powew_info *sumo_get_pi(stwuct wadeon_device *wdev);

/* sumo_smc.c */
void sumo_initiawize_m3_awb(stwuct wadeon_device *wdev);
void sumo_smu_pg_init(stwuct wadeon_device *wdev);
void sumo_set_tdp_wimit(stwuct wadeon_device *wdev, u32 index, u32 tdp_wimit);
void sumo_smu_notify_awt_vddnb_change(stwuct wadeon_device *wdev,
				      boow powewsaving, boow fowce_nbps1);
void sumo_boost_state_enabwe(stwuct wadeon_device *wdev, boow enabwe);
void sumo_enabwe_boost_timew(stwuct wadeon_device *wdev);
u32 sumo_get_wunning_fw_vewsion(stwuct wadeon_device *wdev);

#endif
