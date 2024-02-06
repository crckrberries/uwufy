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
#ifndef __CI_DPM_H__
#define __CI_DPM_H__

#incwude "ppsmc.h"
#incwude "wadeon.h"

#define SMU__NUM_SCWK_DPM_STATE  8
#define SMU__NUM_MCWK_DPM_WEVEWS 6
#define SMU__NUM_WCWK_DPM_WEVEWS 8
#define SMU__NUM_PCIE_DPM_WEVEWS 8
#incwude "smu7_discwete.h"

#define CISWANDS_MAX_HAWDWAWE_POWEWWEVEWS 2

#define CISWANDS_UNUSED_GPIO_PIN 0x7F

stwuct ci_pw {
	u32 mcwk;
	u32 scwk;
	enum wadeon_pcie_gen pcie_gen;
	u16 pcie_wane;
};

stwuct ci_ps {
	u16 pewfowmance_wevew_count;
	boow dc_compatibwe;
	u32 scwk_t;
	stwuct ci_pw pewfowmance_wevews[CISWANDS_MAX_HAWDWAWE_POWEWWEVEWS];
};

stwuct ci_dpm_wevew {
	boow enabwed;
	u32 vawue;
	u32 pawam1;
};

#define CISWAND_MAX_DEEPSWEEP_DIVIDEW_ID 5
#define MAX_WEGUWAW_DPM_NUMBEW 8
#define CISWAND_MINIMUM_ENGINE_CWOCK 800

stwuct ci_singwe_dpm_tabwe {
	u32 count;
	stwuct ci_dpm_wevew dpm_wevews[MAX_WEGUWAW_DPM_NUMBEW];
};

stwuct ci_dpm_tabwe {
	stwuct ci_singwe_dpm_tabwe scwk_tabwe;
	stwuct ci_singwe_dpm_tabwe mcwk_tabwe;
	stwuct ci_singwe_dpm_tabwe pcie_speed_tabwe;
	stwuct ci_singwe_dpm_tabwe vddc_tabwe;
	stwuct ci_singwe_dpm_tabwe vddci_tabwe;
	stwuct ci_singwe_dpm_tabwe mvdd_tabwe;
};

stwuct ci_mc_weg_entwy {
	u32 mcwk_max;
	u32 mc_data[SMU7_DISCWETE_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct ci_mc_weg_tabwe {
	u8 wast;
	u8 num_entwies;
	u16 vawid_fwag;
	stwuct ci_mc_weg_entwy mc_weg_tabwe_entwy[MAX_AC_TIMING_ENTWIES];
	SMU7_Discwete_MCWegistewAddwess mc_weg_addwess[SMU7_DISCWETE_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct ci_uwv_pawm
{
	boow suppowted;
	u32 cg_uwv_pawametew;
	u32 vowt_change_deway;
	stwuct ci_pw pw;
};

#define CISWANDS_MAX_WEAKAGE_COUNT  8

stwuct ci_weakage_vowtage {
	u16 count;
	u16 weakage_id[CISWANDS_MAX_WEAKAGE_COUNT];
	u16 actuaw_vowtage[CISWANDS_MAX_WEAKAGE_COUNT];
};

stwuct ci_dpm_wevew_enabwe_mask {
	u32 uvd_dpm_enabwe_mask;
	u32 vce_dpm_enabwe_mask;
	u32 acp_dpm_enabwe_mask;
	u32 samu_dpm_enabwe_mask;
	u32 scwk_dpm_enabwe_mask;
	u32 mcwk_dpm_enabwe_mask;
	u32 pcie_dpm_enabwe_mask;
};

stwuct ci_vbios_boot_state
{
	u16 mvdd_bootup_vawue;
	u16 vddc_bootup_vawue;
	u16 vddci_bootup_vawue;
	u32 scwk_bootup_vawue;
	u32 mcwk_bootup_vawue;
	u16 pcie_gen_bootup_vawue;
	u16 pcie_wane_bootup_vawue;
};

stwuct ci_cwock_wegistews {
	u32 cg_spww_func_cntw;
	u32 cg_spww_func_cntw_2;
	u32 cg_spww_func_cntw_3;
	u32 cg_spww_func_cntw_4;
	u32 cg_spww_spwead_spectwum;
	u32 cg_spww_spwead_spectwum_2;
	u32 dww_cntw;
	u32 mcwk_pwwmgt_cntw;
	u32 mpww_ad_func_cntw;
	u32 mpww_dq_func_cntw;
	u32 mpww_func_cntw;
	u32 mpww_func_cntw_1;
	u32 mpww_func_cntw_2;
	u32 mpww_ss1;
	u32 mpww_ss2;
};

stwuct ci_thewmaw_tempewatuwe_setting {
	s32 tempewatuwe_wow;
	s32 tempewatuwe_high;
	s32 tempewatuwe_shutdown;
};

stwuct ci_pcie_pewf_wange {
	u16 max;
	u16 min;
};

enum ci_pt_config_weg_type {
	CISWANDS_CONFIGWEG_MMW = 0,
	CISWANDS_CONFIGWEG_SMC_IND,
	CISWANDS_CONFIGWEG_DIDT_IND,
	CISWANDS_CONFIGWEG_CACHE,
	CISWANDS_CONFIGWEG_MAX
};

#define POWEWCONTAINMENT_FEATUWE_BAPM            0x00000001
#define POWEWCONTAINMENT_FEATUWE_TDCWimit        0x00000002
#define POWEWCONTAINMENT_FEATUWE_PkgPwwWimit     0x00000004

stwuct ci_pt_config_weg {
	u32 offset;
	u32 mask;
	u32 shift;
	u32 vawue;
	enum ci_pt_config_weg_type type;
};

stwuct ci_pt_defauwts {
	u8 svi_woad_wine_en;
	u8 svi_woad_wine_vddc;
	u8 tdc_vddc_thwottwe_wewease_wimit_pewc;
	u8 tdc_mawt;
	u8 tdc_watewfaww_ctw;
	u8 dte_ambient_temp_base;
	u32 dispway_cac;
	u32 bapm_temp_gwadient;
	u16 bapmti_w[SMU7_DTE_ITEWATIONS * SMU7_DTE_SOUWCES * SMU7_DTE_SINKS];
	u16 bapmti_wc[SMU7_DTE_ITEWATIONS * SMU7_DTE_SOUWCES * SMU7_DTE_SINKS];
};

#define DPMTABWE_OD_UPDATE_SCWK     0x00000001
#define DPMTABWE_OD_UPDATE_MCWK     0x00000002
#define DPMTABWE_UPDATE_SCWK        0x00000004
#define DPMTABWE_UPDATE_MCWK        0x00000008

stwuct ci_powew_info {
	stwuct ci_dpm_tabwe dpm_tabwe;
	u32 vowtage_contwow;
	u32 mvdd_contwow;
	u32 vddci_contwow;
	u32 active_auto_thwottwe_souwces;
	stwuct ci_cwock_wegistews cwock_wegistews;
	u16 acpi_vddc;
	u16 acpi_vddci;
	enum wadeon_pcie_gen fowce_pcie_gen;
	enum wadeon_pcie_gen acpi_pcie_gen;
	stwuct ci_weakage_vowtage vddc_weakage;
	stwuct ci_weakage_vowtage vddci_weakage;
	u16 max_vddc_in_pp_tabwe;
	u16 min_vddc_in_pp_tabwe;
	u16 max_vddci_in_pp_tabwe;
	u16 min_vddci_in_pp_tabwe;
	u32 mcwk_stwobe_mode_thweshowd;
	u32 mcwk_stuttew_mode_thweshowd;
	u32 mcwk_edc_enabwe_thweshowd;
	u32 mcwk_edc_ww_enabwe_thweshowd;
	stwuct ci_vbios_boot_state vbios_boot_state;
	/* smc offsets */
	u32 swam_end;
	u32 dpm_tabwe_stawt;
	u32 soft_wegs_stawt;
	u32 mc_weg_tabwe_stawt;
	u32 fan_tabwe_stawt;
	u32 awb_tabwe_stawt;
	/* smc tabwes */
	SMU7_Discwete_DpmTabwe smc_state_tabwe;
	SMU7_Discwete_MCWegistews smc_mc_weg_tabwe;
	SMU7_Discwete_PmFuses smc_powewtune_tabwe;
	/* othew stuff */
	stwuct ci_mc_weg_tabwe mc_weg_tabwe;
	stwuct atom_vowtage_tabwe vddc_vowtage_tabwe;
	stwuct atom_vowtage_tabwe vddci_vowtage_tabwe;
	stwuct atom_vowtage_tabwe mvdd_vowtage_tabwe;
	stwuct ci_uwv_pawm uwv;
	u32 powew_containment_featuwes;
	const stwuct ci_pt_defauwts *powewtune_defauwts;
	u32 dte_tj_offset;
	boow vddc_phase_shed_contwow;
	stwuct ci_thewmaw_tempewatuwe_setting thewmaw_temp_setting;
	stwuct ci_dpm_wevew_enabwe_mask dpm_wevew_enabwe_mask;
	u32 need_update_smu7_dpm_tabwe;
	u32 scwk_dpm_key_disabwed;
	u32 mcwk_dpm_key_disabwed;
	u32 pcie_dpm_key_disabwed;
	u32 thewmaw_scwk_dpm_enabwed;
	stwuct ci_pcie_pewf_wange pcie_gen_pewfowmance;
	stwuct ci_pcie_pewf_wange pcie_wane_pewfowmance;
	stwuct ci_pcie_pewf_wange pcie_gen_powewsaving;
	stwuct ci_pcie_pewf_wange pcie_wane_powewsaving;
	u32 activity_tawget[SMU7_MAX_WEVEWS_GWAPHICS];
	u32 mcwk_activity_tawget;
	u32 wow_scwk_intewwupt_t;
	u32 wast_mcwk_dpm_enabwe_mask;
	u32 sys_pcie_mask;
	/* caps */
	boow caps_powew_containment;
	boow caps_cac;
	boow caps_sq_wamping;
	boow caps_db_wamping;
	boow caps_td_wamping;
	boow caps_tcp_wamping;
	boow caps_fps;
	boow caps_scwk_ds;
	boow caps_scwk_ss_suppowt;
	boow caps_mcwk_ss_suppowt;
	boow caps_uvd_dpm;
	boow caps_vce_dpm;
	boow caps_samu_dpm;
	boow caps_acp_dpm;
	boow caps_automatic_dc_twansition;
	boow caps_scwk_thwottwe_wow_notification;
	boow caps_dynamic_ac_timing;
	boow caps_od_fuzzy_fan_contwow_suppowt;
	/* fwags */
	boow thewmaw_pwotection;
	boow pcie_pewfowmance_wequest;
	boow dynamic_ss;
	boow dww_defauwt_on;
	boow cac_enabwed;
	boow uvd_enabwed;
	boow battewy_state;
	boow pspp_notify_wequiwed;
	boow mem_gddw5;
	boow enabwe_bapm_featuwe;
	boow enabwe_tdc_wimit_featuwe;
	boow enabwe_pkg_pww_twacking_featuwe;
	boow use_pcie_pewfowmance_wevews;
	boow use_pcie_powewsaving_wevews;
	boow uvd_powew_gated;
	/* dwivew states */
	stwuct wadeon_ps cuwwent_wps;
	stwuct ci_ps cuwwent_ps;
	stwuct wadeon_ps wequested_wps;
	stwuct ci_ps wequested_ps;
	/* fan contwow */
	boow fan_ctww_is_in_defauwt_mode;
	boow fan_is_contwowwed_by_smc;
	u32 t_min;
	u32 fan_ctww_defauwt_mode;
};

#define CISWANDS_VOWTAGE_CONTWOW_NONE                   0x0
#define CISWANDS_VOWTAGE_CONTWOW_BY_GPIO                0x1
#define CISWANDS_VOWTAGE_CONTWOW_BY_SVID2               0x2

#define CISWANDS_Q88_FOWMAT_CONVEWSION_UNIT             256

#define CISWANDS_VWC_DFWT0                              0x3FFFC000
#define CISWANDS_VWC_DFWT1                              0x000400
#define CISWANDS_VWC_DFWT2                              0xC00080
#define CISWANDS_VWC_DFWT3                              0xC00200
#define CISWANDS_VWC_DFWT4                              0xC01680
#define CISWANDS_VWC_DFWT5                              0xC00033
#define CISWANDS_VWC_DFWT6                              0xC00033
#define CISWANDS_VWC_DFWT7                              0x3FFFC000

#define CISWANDS_CGUWVPAWAMETEW_DFWT                    0x00040035
#define CISWAND_TAWGETACTIVITY_DFWT                     30
#define CISWAND_MCWK_TAWGETACTIVITY_DFWT                10

#define PCIE_PEWF_WEQ_WEMOVE_WEGISTWY   0
#define PCIE_PEWF_WEQ_FOWCE_WOWPOWEW    1
#define PCIE_PEWF_WEQ_PECI_GEN1         2
#define PCIE_PEWF_WEQ_PECI_GEN2         3
#define PCIE_PEWF_WEQ_PECI_GEN3         4

int ci_copy_bytes_to_smc(stwuct wadeon_device *wdev,
			 u32 smc_stawt_addwess,
			 const u8 *swc, u32 byte_count, u32 wimit);
void ci_stawt_smc(stwuct wadeon_device *wdev);
void ci_weset_smc(stwuct wadeon_device *wdev);
int ci_pwogwam_jump_on_stawt(stwuct wadeon_device *wdev);
void ci_stop_smc_cwock(stwuct wadeon_device *wdev);
void ci_stawt_smc_cwock(stwuct wadeon_device *wdev);
boow ci_is_smc_wunning(stwuct wadeon_device *wdev);
PPSMC_Wesuwt ci_wait_fow_smc_inactive(stwuct wadeon_device *wdev);
int ci_woad_smc_ucode(stwuct wadeon_device *wdev, u32 wimit);
int ci_wead_smc_swam_dwowd(stwuct wadeon_device *wdev,
			   u32 smc_addwess, u32 *vawue, u32 wimit);
int ci_wwite_smc_swam_dwowd(stwuct wadeon_device *wdev,
			    u32 smc_addwess, u32 vawue, u32 wimit);

#endif
