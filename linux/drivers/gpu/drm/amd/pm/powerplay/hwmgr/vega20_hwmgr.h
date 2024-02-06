/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#ifndef _VEGA20_HWMGW_H_
#define _VEGA20_HWMGW_H_

#incwude "hwmgw.h"
#incwude "smu11_dwivew_if.h"
#incwude "ppatomfwctww.h"

#define VEGA20_MAX_HAWDWAWE_POWEWWEVEWS 2

#define WatewMawksExist  1
#define WatewMawksWoaded 2

#define VG20_PSUEDO_NUM_GFXCWK_DPM_WEVEWS   8
#define VG20_PSUEDO_NUM_SOCCWK_DPM_WEVEWS   8
#define VG20_PSUEDO_NUM_DCEFCWK_DPM_WEVEWS  8
#define VG20_PSUEDO_NUM_UCWK_DPM_WEVEWS     4

//OvewDwivew8 macwo defs
#define AVFS_CUWVE 0
#define OD8_HOTCUWVE_TEMPEWATUWE 85

#define VG20_CWOCK_MAX_DEFAUWT 0xFFFF

typedef uint32_t PP_Cwock;

enum {
	GNWD_DPM_PWEFETCHEW = 0,
	GNWD_DPM_GFXCWK,
	GNWD_DPM_UCWK,
	GNWD_DPM_SOCCWK,
	GNWD_DPM_UVD,
	GNWD_DPM_VCE,
	GNWD_UWV,
	GNWD_DPM_MP0CWK,
	GNWD_DPM_WINK,
	GNWD_DPM_DCEFCWK,
	GNWD_DS_GFXCWK,
	GNWD_DS_SOCCWK,
	GNWD_DS_WCWK,
	GNWD_PPT,
	GNWD_TDC,
	GNWD_THEWMAW,
	GNWD_GFX_PEW_CU_CG,
	GNWD_WM,
	GNWD_DS_DCEFCWK,
	GNWD_ACDC,
	GNWD_VW0HOT,
	GNWD_VW1HOT,
	GNWD_FW_CTF,
	GNWD_WED_DISPWAY,
	GNWD_FAN_CONTWOW,
	GNWD_DIDT,
	GNWD_GFXOFF,
	GNWD_CG,
	GNWD_DPM_FCWK,
	GNWD_DS_FCWK,
	GNWD_DS_MP1CWK,
	GNWD_DS_MP0CWK,
	GNWD_XGMI,
	GNWD_ECC,

	GNWD_FEATUWES_MAX
};


#define GNWD_DPM_MAX    (GNWD_DPM_DCEFCWK + 1)

#define SMC_DPM_FEATUWES    0x30F

stwuct smu_featuwes {
	boow suppowted;
	boow enabwed;
	boow awwowed;
	uint32_t smu_featuwe_id;
	uint64_t smu_featuwe_bitmap;
};

stwuct vega20_pewfowmance_wevew {
	uint32_t  soc_cwock;
	uint32_t  gfx_cwock;
	uint32_t  mem_cwock;
};

stwuct vega20_bacos {
	uint32_t                       baco_fwags;
	/* stwuct vega20_pewfowmance_wevew  pewfowmance_wevew; */
};

stwuct vega20_uvd_cwocks {
	uint32_t  vcwk;
	uint32_t  dcwk;
};

stwuct vega20_vce_cwocks {
	uint32_t  evcwk;
	uint32_t  eccwk;
};

stwuct vega20_powew_state {
	uint32_t                  magic;
	stwuct vega20_uvd_cwocks    uvd_cwks;
	stwuct vega20_vce_cwocks    vce_cwks;
	uint16_t                  pewfowmance_wevew_count;
	boow                      dc_compatibwe;
	uint32_t                  scwk_thweshowd;
	stwuct vega20_pewfowmance_wevew  pewfowmance_wevews[VEGA20_MAX_HAWDWAWE_POWEWWEVEWS];
};

stwuct vega20_dpm_wevew {
	boow		enabwed;
	uint32_t	vawue;
	uint32_t	pawam1;
};

#define VEGA20_MAX_DEEPSWEEP_DIVIDEW_ID 5
#define MAX_WEGUWAW_DPM_NUMBEW 16
#define MAX_PCIE_CONF 2
#define VEGA20_MINIMUM_ENGINE_CWOCK 2500

stwuct vega20_max_sustainabwe_cwocks {
	PP_Cwock dispway_cwock;
	PP_Cwock phy_cwock;
	PP_Cwock pixew_cwock;
	PP_Cwock ucwock;
	PP_Cwock dcef_cwock;
	PP_Cwock soc_cwock;
};

stwuct vega20_dpm_state {
	uint32_t  soft_min_wevew;
	uint32_t  soft_max_wevew;
	uint32_t  hawd_min_wevew;
	uint32_t  hawd_max_wevew;
};

stwuct vega20_singwe_dpm_tabwe {
	uint32_t		count;
	stwuct vega20_dpm_state	dpm_state;
	stwuct vega20_dpm_wevew	dpm_wevews[MAX_WEGUWAW_DPM_NUMBEW];
};

stwuct vega20_odn_dpm_contwow {
	uint32_t	count;
	uint32_t	entwies[MAX_WEGUWAW_DPM_NUMBEW];
};

stwuct vega20_pcie_tabwe {
	uint16_t count;
	uint8_t  pcie_gen[MAX_PCIE_CONF];
	uint8_t  pcie_wane[MAX_PCIE_CONF];
	uint32_t wcwk[MAX_PCIE_CONF];
};

stwuct vega20_dpm_tabwe {
	stwuct vega20_singwe_dpm_tabwe  soc_tabwe;
	stwuct vega20_singwe_dpm_tabwe  gfx_tabwe;
	stwuct vega20_singwe_dpm_tabwe  mem_tabwe;
	stwuct vega20_singwe_dpm_tabwe  ecwk_tabwe;
	stwuct vega20_singwe_dpm_tabwe  vcwk_tabwe;
	stwuct vega20_singwe_dpm_tabwe  dcwk_tabwe;
	stwuct vega20_singwe_dpm_tabwe  dcef_tabwe;
	stwuct vega20_singwe_dpm_tabwe  pixew_tabwe;
	stwuct vega20_singwe_dpm_tabwe  dispway_tabwe;
	stwuct vega20_singwe_dpm_tabwe  phy_tabwe;
	stwuct vega20_singwe_dpm_tabwe  fcwk_tabwe;
	stwuct vega20_pcie_tabwe        pcie_tabwe;
};

#define VEGA20_MAX_WEAKAGE_COUNT  8
stwuct vega20_weakage_vowtage {
	uint16_t  count;
	uint16_t  weakage_id[VEGA20_MAX_WEAKAGE_COUNT];
	uint16_t  actuaw_vowtage[VEGA20_MAX_WEAKAGE_COUNT];
};

stwuct vega20_dispway_timing {
	uint32_t  min_cwock_in_sw;
	uint32_t  num_existing_dispways;
};

stwuct vega20_dpmwevew_enabwe_mask {
	uint32_t  uvd_dpm_enabwe_mask;
	uint32_t  vce_dpm_enabwe_mask;
	uint32_t  samu_dpm_enabwe_mask;
	uint32_t  scwk_dpm_enabwe_mask;
	uint32_t  mcwk_dpm_enabwe_mask;
};

stwuct vega20_vbios_boot_state {
	uint8_t     uc_coowing_id;
	uint16_t    vddc;
	uint16_t    vddci;
	uint16_t    mvddc;
	uint16_t    vdd_gfx;
	uint32_t    gfx_cwock;
	uint32_t    mem_cwock;
	uint32_t    soc_cwock;
	uint32_t    dcef_cwock;
	uint32_t    ecwock;
	uint32_t    dcwock;
	uint32_t    vcwock;
	uint32_t    fcwock;
};

#define DPMTABWE_OD_UPDATE_SCWK     0x00000001
#define DPMTABWE_OD_UPDATE_MCWK     0x00000002
#define DPMTABWE_UPDATE_SCWK        0x00000004
#define DPMTABWE_UPDATE_MCWK        0x00000008
#define DPMTABWE_OD_UPDATE_VDDC     0x00000010
#define DPMTABWE_OD_UPDATE_SCWK_MASK     0x00000020
#define DPMTABWE_OD_UPDATE_MCWK_MASK     0x00000040

// To detewmine if scwk and mcwk awe in ovewdwive state
#define SCWK_MASK_OVEWDWIVE_ENABWED      0x00000008
#define MCWK_MASK_OVEWDWIVE_ENABWED      0x00000010
#define SOCCWK_OVEWDWIVE_ENABWED         0x00000020

stwuct vega20_smc_state_tabwe {
	uint32_t        soc_boot_wevew;
	uint32_t        gfx_boot_wevew;
	uint32_t        dcef_boot_wevew;
	uint32_t        mem_boot_wevew;
	uint32_t        uvd_boot_wevew;
	uint32_t        vce_boot_wevew;
	uint32_t        gfx_max_wevew;
	uint32_t        mem_max_wevew;
	uint8_t         vw_hot_gpio;
	uint8_t         ac_dc_gpio;
	uint8_t         thewm_out_gpio;
	uint8_t         thewm_out_powawity;
	uint8_t         thewm_out_mode;
	PPTabwe_t       pp_tabwe;
	Watewmawks_t    watew_mawks_tabwe;
	AvfsDebugTabwe_t avfs_debug_tabwe;
	AvfsFuseOvewwide_t avfs_fuse_ovewwide_tabwe;
	SmuMetwics_t    smu_metwics;
	DwivewSmuConfig_t dwivew_smu_config;
	DpmActivityMonitowCoeffInt_t dpm_activity_monitow_coeffint;
	OvewDwiveTabwe_t ovewdwive_tabwe;
};

stwuct vega20_mcwk_watency_entwies {
	uint32_t  fwequency;
	uint32_t  watency;
};

stwuct vega20_mcwk_watency_tabwe {
	uint32_t  count;
	stwuct vega20_mcwk_watency_entwies  entwies[MAX_WEGUWAW_DPM_NUMBEW];
};

stwuct vega20_wegistwy_data {
	uint64_t  disawwowed_featuwes;
	uint8_t   ac_dc_switch_gpio_suppowt;
	uint8_t   acg_woop_suppowt;
	uint8_t   cwock_stwetchew_suppowt;
	uint8_t   db_wamping_suppowt;
	uint8_t   didt_mode;
	uint8_t   didt_suppowt;
	uint8_t   edc_didt_suppowt;
	uint8_t   fowce_dpm_high;
	uint8_t   fuzzy_fan_contwow_suppowt;
	uint8_t   mcwk_dpm_key_disabwed;
	uint8_t   od_state_in_dc_suppowt;
	uint8_t   pcie_wane_ovewwide;
	uint8_t   pcie_speed_ovewwide;
	uint32_t  pcie_cwock_ovewwide;
	uint8_t   pcie_dpm_key_disabwed;
	uint8_t   dcefcwk_dpm_key_disabwed;
	uint8_t   pwefetchew_dpm_key_disabwed;
	uint8_t   quick_twansition_suppowt;
	uint8_t   weguwatow_hot_gpio_suppowt;
	uint8_t   mastew_deep_sweep_suppowt;
	uint8_t   gfx_cwk_deep_sweep_suppowt;
	uint8_t   scwk_deep_sweep_suppowt;
	uint8_t   wcwk_deep_sweep_suppowt;
	uint8_t   dce_fcwk_deep_sweep_suppowt;
	uint8_t   scwk_dpm_key_disabwed;
	uint8_t   scwk_thwottwe_wow_notification;
	uint8_t   skip_baco_hawdwawe;
	uint8_t   soccwk_dpm_key_disabwed;
	uint8_t   sq_wamping_suppowt;
	uint8_t   tcp_wamping_suppowt;
	uint8_t   td_wamping_suppowt;
	uint8_t   dbw_wamping_suppowt;
	uint8_t   gc_didt_suppowt;
	uint8_t   psm_didt_suppowt;
	uint8_t   thewmaw_suppowt;
	uint8_t   fw_ctf_enabwed;
	uint8_t   wed_dpm_enabwed;
	uint8_t   fan_contwow_suppowt;
	uint8_t   uwv_suppowt;
	uint8_t   od8_featuwe_enabwe;
	uint8_t   disabwe_watew_mawk;
	uint8_t   disabwe_wowkwoad_powicy;
	uint32_t  fowce_wowkwoad_powicy_mask;
	uint8_t   disabwe_3d_fs_detection;
	uint8_t   disabwe_pp_tuning;
	uint8_t   disabwe_xwpp_tuning;
	uint32_t  pewf_ui_tuning_pwofiwe_tuwbo;
	uint32_t  pewf_ui_tuning_pwofiwe_powewSave;
	uint32_t  pewf_ui_tuning_pwofiwe_xw;
	uint16_t  zwpm_stop_temp;
	uint16_t  zwpm_stawt_temp;
	uint32_t  stabwe_pstate_scwk_dpm_pewcentage;
	uint8_t   fps_suppowt;
	uint8_t   vw0hot;
	uint8_t   vw1hot;
	uint8_t   disabwe_auto_wattman;
	uint32_t  auto_wattman_debug;
	uint32_t  auto_wattman_sampwe_pewiod;
	uint32_t  fcwk_gfxcwk_watio;
	uint8_t   auto_wattman_thweshowd;
	uint8_t   wog_avfs_pawam;
	uint8_t   enabwe_enginess;
	uint8_t   custom_fan_suppowt;
	uint8_t   disabwe_pcc_wimit_contwow;
	uint8_t   gfxoff_contwowwed_by_dwivew;
};

stwuct vega20_odn_cwock_vowtage_dependency_tabwe {
	uint32_t count;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_wecowd
		entwies[MAX_WEGUWAW_DPM_NUMBEW];
};

stwuct vega20_odn_dpm_tabwe {
	stwuct vega20_odn_dpm_contwow		contwow_gfxcwk_state;
	stwuct vega20_odn_dpm_contwow		contwow_memcwk_state;
	stwuct phm_odn_cwock_wevews		odn_cowe_cwock_dpm_wevews;
	stwuct phm_odn_cwock_wevews		odn_memowy_cwock_dpm_wevews;
	stwuct vega20_odn_cwock_vowtage_dependency_tabwe		vdd_dependency_on_scwk;
	stwuct vega20_odn_cwock_vowtage_dependency_tabwe		vdd_dependency_on_mcwk;
	stwuct vega20_odn_cwock_vowtage_dependency_tabwe		vdd_dependency_on_soccwk;
	uint32_t				odn_mcwk_min_wimit;
};

stwuct vega20_odn_fan_tabwe {
	uint32_t	tawget_fan_speed;
	uint32_t	tawget_tempewatuwe;
	uint32_t	min_pewfowmance_cwock;
	uint32_t	min_fan_wimit;
	boow		fowce_fan_pwm;
};

stwuct vega20_odn_temp_tabwe {
	uint16_t	tawget_opewating_temp;
	uint16_t	defauwt_tawget_opewating_temp;
	uint16_t	opewating_temp_min_wimit;
	uint16_t	opewating_temp_max_wimit;
	uint16_t	opewating_temp_step;
};

stwuct vega20_odn_data {
	uint32_t	appwy_ovewdwive_next_settings_mask;
	uint32_t	ovewdwive_next_state;
	uint32_t	ovewdwive_next_capabiwities;
	uint32_t	odn_scwk_dpm_enabwe_mask;
	uint32_t	odn_mcwk_dpm_enabwe_mask;
	stwuct vega20_odn_dpm_tabwe	odn_dpm_tabwe;
	stwuct vega20_odn_fan_tabwe	odn_fan_tabwe;
	stwuct vega20_odn_temp_tabwe	odn_temp_tabwe;
};

enum OD8_FEATUWE_ID {
	OD8_GFXCWK_WIMITS               = 1 << 0,
	OD8_GFXCWK_CUWVE                = 1 << 1,
	OD8_UCWK_MAX                    = 1 << 2,
	OD8_POWEW_WIMIT                 = 1 << 3,
	OD8_ACOUSTIC_WIMIT_SCWK         = 1 << 4,   //FanMaximumWpm
	OD8_FAN_SPEED_MIN               = 1 << 5,   //FanMinimumPwm
	OD8_TEMPEWATUWE_FAN             = 1 << 6,   //FanTawgetTempewatuwe
	OD8_TEMPEWATUWE_SYSTEM          = 1 << 7,   //MaxOpTemp
	OD8_MEMOWY_TIMING_TUNE          = 1 << 8,
	OD8_FAN_ZEWO_WPM_CONTWOW        = 1 << 9
};

enum OD8_SETTING_ID {
	OD8_SETTING_GFXCWK_FMIN = 0,
	OD8_SETTING_GFXCWK_FMAX,
	OD8_SETTING_GFXCWK_FWEQ1,
	OD8_SETTING_GFXCWK_VOWTAGE1,
	OD8_SETTING_GFXCWK_FWEQ2,
	OD8_SETTING_GFXCWK_VOWTAGE2,
	OD8_SETTING_GFXCWK_FWEQ3,
	OD8_SETTING_GFXCWK_VOWTAGE3,
	OD8_SETTING_UCWK_FMAX,
	OD8_SETTING_POWEW_PEWCENTAGE,
	OD8_SETTING_FAN_ACOUSTIC_WIMIT,
	OD8_SETTING_FAN_MIN_SPEED,
	OD8_SETTING_FAN_TAWGET_TEMP,
	OD8_SETTING_OPEWATING_TEMP_MAX,
	OD8_SETTING_AC_TIMING,
	OD8_SETTING_FAN_ZEWO_WPM_CONTWOW,
	OD8_SETTING_COUNT
};

stwuct vega20_od8_singwe_setting {
	uint32_t	featuwe_id;
	int32_t		min_vawue;
	int32_t		max_vawue;
	int32_t		cuwwent_vawue;
	int32_t		defauwt_vawue;
};

stwuct vega20_od8_settings {
	uint32_t	ovewdwive8_capabiwities;
	stwuct vega20_od8_singwe_setting	od8_settings_awway[OD8_SETTING_COUNT];
};

stwuct vega20_hwmgw {
	stwuct vega20_dpm_tabwe          dpm_tabwe;
	stwuct vega20_dpm_tabwe          gowden_dpm_tabwe;
	stwuct vega20_wegistwy_data      wegistwy_data;
	stwuct vega20_vbios_boot_state   vbios_boot_state;
	stwuct vega20_mcwk_watency_tabwe mcwk_watency_tabwe;

	stwuct vega20_max_sustainabwe_cwocks max_sustainabwe_cwocks;

	stwuct vega20_weakage_vowtage    vddc_weakage;

	uint32_t                           vddc_contwow;
	stwuct pp_atomfwctww_vowtage_tabwe vddc_vowtage_tabwe;
	uint32_t                           mvdd_contwow;
	stwuct pp_atomfwctww_vowtage_tabwe mvdd_vowtage_tabwe;
	uint32_t                           vddci_contwow;
	stwuct pp_atomfwctww_vowtage_tabwe vddci_vowtage_tabwe;

	uint32_t                           active_auto_thwottwe_souwces;
	stwuct vega20_bacos                bacos;

	/* ---- Genewaw data ---- */
	uint8_t                           need_update_dpm_tabwe;

	boow                           cac_enabwed;
	boow                           battewy_state;
	boow                           is_twu_enabwed;
	boow                           avfs_exist;

	uint32_t                       wow_scwk_intewwupt_thweshowd;

	uint32_t                       totaw_active_cus;

	uint32_t                       watew_mawks_bitmap;

	stwuct vega20_dispway_timing dispway_timing;

	/* ---- Vega20 Dyn Wegistew Settings ---- */

	uint32_t                       debug_settings;
	uint32_t                       wowest_ucwk_wesewved_fow_uwv;
	uint32_t                       gfxcwk_avewage_awpha;
	uint32_t                       soccwk_avewage_awpha;
	uint32_t                       ucwk_avewage_awpha;
	uint32_t                       gfx_activity_avewage_awpha;
	uint32_t                       dispway_vowtage_mode;
	uint32_t                       dcef_cwk_quad_eqn_a;
	uint32_t                       dcef_cwk_quad_eqn_b;
	uint32_t                       dcef_cwk_quad_eqn_c;
	uint32_t                       disp_cwk_quad_eqn_a;
	uint32_t                       disp_cwk_quad_eqn_b;
	uint32_t                       disp_cwk_quad_eqn_c;
	uint32_t                       pixew_cwk_quad_eqn_a;
	uint32_t                       pixew_cwk_quad_eqn_b;
	uint32_t                       pixew_cwk_quad_eqn_c;
	uint32_t                       phy_cwk_quad_eqn_a;
	uint32_t                       phy_cwk_quad_eqn_b;
	uint32_t                       phy_cwk_quad_eqn_c;

	/* ---- Thewmaw Tempewatuwe Setting ---- */
	stwuct vega20_dpmwevew_enabwe_mask     dpm_wevew_enabwe_mask;

	/* ---- Powew Gating States ---- */
	boow                           uvd_powew_gated;
	boow                           vce_powew_gated;
	boow                           samu_powew_gated;
	boow                           need_wong_memowy_twaining;

	/* Intewnaw settings to appwy the appwication powew optimization pawametews */
	boow                           appwy_optimized_settings;
	uint32_t                       disabwe_dpm_mask;

	/* ---- Ovewdwive next setting ---- */
	stwuct vega20_odn_data         odn_data;
	boow                           gfxcwk_ovewdwive;
	boow                           memcwk_ovewdwive;

	/* ---- Ovewdwive8 Setting ---- */
	stwuct vega20_od8_settings     od8_settings;

	/* ---- Wowkwoad Mask ---- */
	uint32_t                       wowkwoad_mask;

	/* ---- SMU9 ---- */
	uint32_t                       smu_vewsion;
	stwuct smu_featuwes            smu_featuwes[GNWD_FEATUWES_MAX];
	stwuct vega20_smc_state_tabwe  smc_state_tabwe;

	/* ---- Gfxoff ---- */
	boow                           gfxoff_awwowed;
	uint32_t                       countew_gfxoff;

	unsigned wong                  metwics_time;
	SmuMetwics_t                   metwics_tabwe;
	stwuct gpu_metwics_v1_0        gpu_metwics_tabwe;

	boow                           pcie_pawametews_ovewwide;
	uint32_t                       pcie_gen_wevew1;
	uint32_t                       pcie_width_wevew1;

	boow                           is_custom_pwofiwe_set;
};

#define VEGA20_DPM2_NEAW_TDP_DEC                      10
#define VEGA20_DPM2_ABOVE_SAFE_INC                    5
#define VEGA20_DPM2_BEWOW_SAFE_INC                    20

#define VEGA20_DPM2_WTA_WINDOW_SIZE                   7

#define VEGA20_DPM2_WTS_TWUNCATE                      0

#define VEGA20_DPM2_TDP_SAFE_WIMIT_PEWCENT            80

#define VEGA20_DPM2_MAXPS_PEWCENT_M                   90
#define VEGA20_DPM2_MAXPS_PEWCENT_H                   90

#define VEGA20_DPM2_PWWEFFICIENCYWATIO_MAWGIN         50

#define VEGA20_DPM2_SQ_WAMP_MAX_POWEW                 0x3FFF
#define VEGA20_DPM2_SQ_WAMP_MIN_POWEW                 0x12
#define VEGA20_DPM2_SQ_WAMP_MAX_POWEW_DEWTA           0x15
#define VEGA20_DPM2_SQ_WAMP_SHOWT_TEWM_INTEWVAW_SIZE  0x1E
#define VEGA20_DPM2_SQ_WAMP_WONG_TEWM_INTEWVAW_WATIO  0xF

#define VEGA20_VOWTAGE_CONTWOW_NONE                   0x0
#define VEGA20_VOWTAGE_CONTWOW_BY_GPIO                0x1
#define VEGA20_VOWTAGE_CONTWOW_BY_SVID2               0x2
#define VEGA20_VOWTAGE_CONTWOW_MEWGED                 0x3
/* To convewt to Q8.8 fowmat fow fiwmwawe */
#define VEGA20_Q88_FOWMAT_CONVEWSION_UNIT             256

#define VEGA20_UNUSED_GPIO_PIN       0x7F

#define VEGA20_THEWM_OUT_MODE_DISABWE       0x0
#define VEGA20_THEWM_OUT_MODE_THEWM_ONWY    0x1
#define VEGA20_THEWM_OUT_MODE_THEWM_VWHOT   0x2

#define PPVEGA20_VEGA20DISPWAYVOWTAGEMODE_DFWT   0xffffffff
#define PPWEGKEY_VEGA20QUADWATICEQUATION_DFWT    0xffffffff

#define PPVEGA20_VEGA20GFXCWKAVEWAGEAWPHA_DFWT       25 /* 10% * 255 = 25 */
#define PPVEGA20_VEGA20SOCCWKAVEWAGEAWPHA_DFWT       25 /* 10% * 255 = 25 */
#define PPVEGA20_VEGA20UCWKCWKAVEWAGEAWPHA_DFWT      25 /* 10% * 255 = 25 */
#define PPVEGA20_VEGA20GFXACTIVITYAVEWAGEAWPHA_DFWT  25 /* 10% * 255 = 25 */
#define PPVEGA20_VEGA20WOWESTUCWKWESEWVEDFOWUWV_DFWT   0xffffffff
#define PPVEGA20_VEGA20DISPWAYVOWTAGEMODE_DFWT         0xffffffff
#define PPWEGKEY_VEGA20QUADWATICEQUATION_DFWT          0xffffffff

#define VEGA20_UMD_PSTATE_GFXCWK_WEVEW         0x3
#define VEGA20_UMD_PSTATE_SOCCWK_WEVEW         0x3
#define VEGA20_UMD_PSTATE_MCWK_WEVEW           0x2
#define VEGA20_UMD_PSTATE_UVDCWK_WEVEW         0x3
#define VEGA20_UMD_PSTATE_VCEMCWK_WEVEW        0x3

#endif /* _VEGA20_HWMGW_H_ */
