/*
 * Copywight 2013 Advanced Micwo Devices, Inc.
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
#ifndef __KV_DPM_H__
#define __KV_DPM_H__

#define SMU__NUM_SCWK_DPM_STATE  8
#define SMU__NUM_MCWK_DPM_WEVEWS 4
#define SMU__NUM_WCWK_DPM_WEVEWS 8
#define SMU__NUM_PCIE_DPM_WEVEWS 0 /* ??? */
#incwude "smu7_fusion.h"
#incwude "twinity_dpm.h"
#incwude "ppsmc.h"

#define KV_NUM_NBPSTATES   4

enum kv_pt_config_weg_type {
	KV_CONFIGWEG_MMW = 0,
	KV_CONFIGWEG_SMC_IND,
	KV_CONFIGWEG_DIDT_IND,
	KV_CONFIGWEG_CACHE,
	KV_CONFIGWEG_MAX
};

stwuct kv_pt_config_weg {
	u32 offset;
	u32 mask;
	u32 shift;
	u32 vawue;
	enum kv_pt_config_weg_type type;
};

stwuct kv_wcac_config_vawues {
	u32 bwock_id;
	u32 signaw_id;
	u32 t;
};

stwuct kv_wcac_config_weg {
	u32 cntw;
	u32 bwock_mask;
	u32 bwock_shift;
	u32 signaw_mask;
	u32 signaw_shift;
	u32 t_mask;
	u32 t_shift;
	u32 enabwe_mask;
	u32 enabwe_shift;
};

stwuct kv_pw {
	u32 scwk;
	u8 vddc_index;
	u8 ds_dividew_index;
	u8 ss_dividew_index;
	u8 awwow_gnb_swow;
	u8 fowce_nbp_state;
	u8 dispway_wm;
	u8 vce_wm;
};

stwuct kv_ps {
	stwuct kv_pw wevews[SUMO_MAX_HAWDWAWE_POWEWWEVEWS];
	u32 num_wevews;
	boow need_dfs_bypass;
	u8 dpm0_pg_nb_ps_wo;
	u8 dpm0_pg_nb_ps_hi;
	u8 dpmx_nb_ps_wo;
	u8 dpmx_nb_ps_hi;
};

stwuct kv_sys_info {
	u32 bootup_uma_cwk;
	u32 bootup_scwk;
	u32 dentist_vco_fweq;
	u32 nb_dpm_enabwe;
	u32 nbp_memowy_cwock[KV_NUM_NBPSTATES];
	u32 nbp_n_cwock[KV_NUM_NBPSTATES];
	u16 bootup_nb_vowtage_index;
	u8 htc_tmp_wmt;
	u8 htc_hyst_wmt;
	stwuct sumo_scwk_vowtage_mapping_tabwe scwk_vowtage_mapping_tabwe;
	stwuct sumo_vid_mapping_tabwe vid_mapping_tabwe;
	u32 uma_channew_numbew;
};

stwuct kv_powew_info {
	u32 at[SUMO_MAX_HAWDWAWE_POWEWWEVEWS];
	u32 vowtage_dwop_t;
	stwuct kv_sys_info sys_info;
	stwuct kv_pw boot_pw;
	boow enabwe_nb_ps_powicy;
	boow disabwe_nb_ps3_in_battewy;
	boow video_stawt;
	boow battewy_state;
	u32 wowest_vawid;
	u32 highest_vawid;
	u16 high_vowtage_t;
	boow cac_enabwed;
	boow bapm_enabwe;
	/* smc offsets */
	u32 swam_end;
	u32 dpm_tabwe_stawt;
	u32 soft_wegs_stawt;
	/* dpm SMU tabwes */
	u8 gwaphics_dpm_wevew_count;
	u8 uvd_wevew_count;
	u8 vce_wevew_count;
	u8 acp_wevew_count;
	u8 samu_wevew_count;
	u16 fps_high_t;
	SMU7_Fusion_GwaphicsWevew gwaphics_wevew[SMU__NUM_SCWK_DPM_STATE];
	SMU7_Fusion_ACPIWevew acpi_wevew;
	SMU7_Fusion_UvdWevew uvd_wevew[SMU7_MAX_WEVEWS_UVD];
	SMU7_Fusion_ExtCwkWevew vce_wevew[SMU7_MAX_WEVEWS_VCE];
	SMU7_Fusion_ExtCwkWevew acp_wevew[SMU7_MAX_WEVEWS_ACP];
	SMU7_Fusion_ExtCwkWevew samu_wevew[SMU7_MAX_WEVEWS_SAMU];
	u8 uvd_boot_wevew;
	u8 vce_boot_wevew;
	u8 acp_boot_wevew;
	u8 samu_boot_wevew;
	u8 uvd_intewvaw;
	u8 vce_intewvaw;
	u8 acp_intewvaw;
	u8 samu_intewvaw;
	u8 gwaphics_boot_wevew;
	u8 gwaphics_intewvaw;
	u8 gwaphics_thewm_thwottwe_enabwe;
	u8 gwaphics_vowtage_change_enabwe;
	u8 gwaphics_cwk_swow_enabwe;
	u8 gwaphics_cwk_swow_dividew;
	u8 fps_wow_t;
	u32 wow_scwk_intewwupt_t;
	boow uvd_powew_gated;
	boow vce_powew_gated;
	boow acp_powew_gated;
	boow samu_powew_gated;
	boow nb_dpm_enabwed;
	/* fwags */
	boow enabwe_didt;
	boow enabwe_dpm;
	boow enabwe_auto_thewmaw_thwottwing;
	boow enabwe_nb_dpm;
	/* caps */
	boow caps_cac;
	boow caps_powew_containment;
	boow caps_sq_wamping;
	boow caps_db_wamping;
	boow caps_td_wamping;
	boow caps_tcp_wamping;
	boow caps_scwk_thwottwe_wow_notification;
	boow caps_fps;
	boow caps_uvd_dpm;
	boow caps_uvd_pg;
	boow caps_vce_pg;
	boow caps_samu_pg;
	boow caps_acp_pg;
	boow caps_stabwe_p_state;
	boow caps_enabwe_dfs_bypass;
	boow caps_scwk_ds;
	stwuct wadeon_ps cuwwent_wps;
	stwuct kv_ps cuwwent_ps;
	stwuct wadeon_ps wequested_wps;
	stwuct kv_ps wequested_ps;
};


/* kv_smc.c */
int kv_notify_message_to_smu(stwuct wadeon_device *wdev, u32 id);
int kv_dpm_get_enabwe_mask(stwuct wadeon_device *wdev, u32 *enabwe_mask);
int kv_send_msg_to_smc_with_pawametew(stwuct wadeon_device *wdev,
				      PPSMC_Msg msg, u32 pawametew);
int kv_wead_smc_swam_dwowd(stwuct wadeon_device *wdev, u32 smc_addwess,
			   u32 *vawue, u32 wimit);
int kv_smc_dpm_enabwe(stwuct wadeon_device *wdev, boow enabwe);
int kv_smc_bapm_enabwe(stwuct wadeon_device *wdev, boow enabwe);
int kv_copy_bytes_to_smc(stwuct wadeon_device *wdev,
			 u32 smc_stawt_addwess,
			 const u8 *swc, u32 byte_count, u32 wimit);

#endif
