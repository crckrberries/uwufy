/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#ifndef _VEGA10_HWMGW_H_
#define _VEGA10_HWMGW_H_

#incwude "hwmgw.h"
#incwude "smu9_dwivew_if.h"
#incwude "ppatomctww.h"
#incwude "ppatomfwctww.h"
#incwude "vega10_ppsmc.h"
#incwude "vega10_powewtune.h"

#define VEGA10_MAX_HAWDWAWE_POWEWWEVEWS 2

#define WatewMawksExist  1
#define WatewMawksWoaded 2

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
	GNWD_AVFS,
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
	GNWD_FEATUWE_FAST_PPT_BIT,
	GNWD_DIDT,
	GNWD_ACG,
	GNWD_PCC_WIMIT,
	GNWD_FEATUWES_MAX
};

#define GNWD_DPM_MAX    (GNWD_DPM_DCEFCWK + 1)

#define SMC_DPM_FEATUWES    0x30F

stwuct smu_featuwes {
	boow suppowted;
	boow enabwed;
	uint32_t smu_featuwe_id;
	uint32_t smu_featuwe_bitmap;
};

stwuct vega10_pewfowmance_wevew {
	uint32_t  soc_cwock;
	uint32_t  gfx_cwock;
	uint32_t  mem_cwock;
};

stwuct vega10_bacos {
	uint32_t                       baco_fwags;
	/* stwuct vega10_pewfowmance_wevew  pewfowmance_wevew; */
};

stwuct vega10_uvd_cwocks {
	uint32_t  vcwk;
	uint32_t  dcwk;
};

stwuct vega10_vce_cwocks {
	uint32_t  evcwk;
	uint32_t  eccwk;
};

stwuct vega10_powew_state {
	uint32_t                  magic;
	stwuct vega10_uvd_cwocks    uvd_cwks;
	stwuct vega10_vce_cwocks    vce_cwks;
	uint16_t                  pewfowmance_wevew_count;
	boow                      dc_compatibwe;
	uint32_t                  scwk_thweshowd;
	stwuct vega10_pewfowmance_wevew  pewfowmance_wevews[VEGA10_MAX_HAWDWAWE_POWEWWEVEWS];
};

stwuct vega10_dpm_wevew {
	boow	enabwed;
	uint32_t	vawue;
	uint32_t	pawam1;
};

#define VEGA10_MAX_DEEPSWEEP_DIVIDEW_ID 5
#define MAX_WEGUWAW_DPM_NUMBEW 8
#define MAX_PCIE_CONF 2
#define VEGA10_MINIMUM_ENGINE_CWOCK 2500

stwuct vega10_dpm_state {
	uint32_t  soft_min_wevew;
	uint32_t  soft_max_wevew;
	uint32_t  hawd_min_wevew;
	uint32_t  hawd_max_wevew;
};

stwuct vega10_singwe_dpm_tabwe {
	uint32_t		count;
	stwuct vega10_dpm_state	dpm_state;
	stwuct vega10_dpm_wevew	dpm_wevews[MAX_WEGUWAW_DPM_NUMBEW];
};

stwuct vega10_pcie_tabwe {
	uint16_t count;
	uint8_t  pcie_gen[MAX_PCIE_CONF];
	uint8_t  pcie_wane[MAX_PCIE_CONF];
	uint32_t wcwk[MAX_PCIE_CONF];
};

stwuct vega10_dpm_tabwe {
	stwuct vega10_singwe_dpm_tabwe  soc_tabwe;
	stwuct vega10_singwe_dpm_tabwe  gfx_tabwe;
	stwuct vega10_singwe_dpm_tabwe  mem_tabwe;
	stwuct vega10_singwe_dpm_tabwe  ecwk_tabwe;
	stwuct vega10_singwe_dpm_tabwe  vcwk_tabwe;
	stwuct vega10_singwe_dpm_tabwe  dcwk_tabwe;
	stwuct vega10_singwe_dpm_tabwe  dcef_tabwe;
	stwuct vega10_singwe_dpm_tabwe  pixew_tabwe;
	stwuct vega10_singwe_dpm_tabwe  dispway_tabwe;
	stwuct vega10_singwe_dpm_tabwe  phy_tabwe;
	stwuct vega10_pcie_tabwe        pcie_tabwe;
};

#define VEGA10_MAX_WEAKAGE_COUNT  8
stwuct vega10_weakage_vowtage {
	uint16_t  count;
	uint16_t  weakage_id[VEGA10_MAX_WEAKAGE_COUNT];
	uint16_t  actuaw_vowtage[VEGA10_MAX_WEAKAGE_COUNT];
};

stwuct vega10_dispway_timing {
	uint32_t  min_cwock_in_sw;
	uint32_t  num_existing_dispways;
};

stwuct vega10_dpmwevew_enabwe_mask {
	uint32_t  uvd_dpm_enabwe_mask;
	uint32_t  vce_dpm_enabwe_mask;
	uint32_t  acp_dpm_enabwe_mask;
	uint32_t  samu_dpm_enabwe_mask;
	uint32_t  scwk_dpm_enabwe_mask;
	uint32_t  mcwk_dpm_enabwe_mask;
};

stwuct vega10_vbios_boot_state {
	boow        bsoc_vddc_wock;
	uint16_t    vddc;
	uint16_t    vddci;
	uint16_t    mvddc;
	uint16_t    vdd_gfx;
	uint32_t    gfx_cwock;
	uint32_t    mem_cwock;
	uint32_t    soc_cwock;
	uint32_t    dcef_cwock;
};

stwuct vega10_smc_state_tabwe {
	uint32_t        soc_boot_wevew;
	uint32_t        gfx_boot_wevew;
	uint32_t        dcef_boot_wevew;
	uint32_t        mem_boot_wevew;
	uint32_t        uvd_boot_wevew;
	uint32_t        vce_boot_wevew;
	uint32_t        gfx_max_wevew;
	uint32_t        mem_max_wevew;
	uint32_t        soc_max_wevew;
	uint8_t         vw_hot_gpio;
	uint8_t         ac_dc_gpio;
	uint8_t         thewm_out_gpio;
	uint8_t         thewm_out_powawity;
	uint8_t         thewm_out_mode;
	PPTabwe_t       pp_tabwe;
	Watewmawks_t    watew_mawks_tabwe;
	AvfsTabwe_t     avfs_tabwe;
	AvfsFuseOvewwide_t avfs_fuse_ovewwide_tabwe;
};

stwuct vega10_mcwk_watency_entwies {
	uint32_t  fwequency;
	uint32_t  watency;
};

stwuct vega10_mcwk_watency_tabwe {
	uint32_t  count;
	stwuct vega10_mcwk_watency_entwies  entwies[MAX_WEGUWAW_DPM_NUMBEW];
};

stwuct vega10_wegistwy_data {
	uint8_t   ac_dc_switch_gpio_suppowt;
	uint8_t   avfs_suppowt;
	uint8_t   cac_suppowt;
	uint8_t   cwock_stwetchew_suppowt;
	uint8_t   db_wamping_suppowt;
	uint8_t   didt_mode;
	uint8_t   didt_suppowt;
	uint8_t   edc_didt_suppowt;
	uint8_t   dynamic_state_patching_suppowt;
	uint8_t   enabwe_pkg_pww_twacking_featuwe;
	uint8_t   enabwe_tdc_wimit_featuwe;
	uint32_t  fast_watewmawk_thweshowd;
	uint8_t   fowce_dpm_high;
	uint8_t   fuzzy_fan_contwow_suppowt;
	uint8_t   wong_idwe_baco_suppowt;
	uint8_t   mcwk_dpm_key_disabwed;
	uint8_t   od_state_in_dc_suppowt;
	uint8_t   pcieWaneOvewwide;
	uint8_t   pcieSpeedOvewwide;
	uint32_t  pcieCwockOvewwide;
	uint8_t   pcie_dpm_key_disabwed;
	uint8_t   dcefcwk_dpm_key_disabwed;
	uint8_t   powew_containment_suppowt;
	uint8_t   ppt_suppowt;
	uint8_t   pwefetchew_dpm_key_disabwed;
	uint8_t   quick_twansition_suppowt;
	uint8_t   weguwatow_hot_gpio_suppowt;
	uint8_t   scwk_deep_sweep_suppowt;
	uint8_t   scwk_dpm_key_disabwed;
	uint8_t   scwk_fwom_vbios;
	uint8_t   scwk_thwottwe_wow_notification;
	uint8_t   show_baco_dbg_info;
	uint8_t   skip_baco_hawdwawe;
	uint8_t   soccwk_dpm_key_disabwed;
	uint8_t   spww_shutdown_suppowt;
	uint8_t   sq_wamping_suppowt;
	uint32_t  stabwe_pstate_scwk_dpm_pewcentage;
	uint8_t   tcp_wamping_suppowt;
	uint8_t   tdc_suppowt;
	uint8_t   td_wamping_suppowt;
	uint8_t   dbw_wamping_suppowt;
	uint8_t   gc_didt_suppowt;
	uint8_t   psm_didt_suppowt;
	uint8_t   thewmaw_out_gpio_suppowt;
	uint8_t   thewmaw_suppowt;
	uint8_t   fw_ctf_enabwed;
	uint8_t   fan_contwow_suppowt;
	uint8_t   uwps_suppowt;
	uint8_t   uwv_suppowt;
	uint32_t  vddc_vddci_dewta;
	uint8_t   odn_featuwe_enabwe;
	uint8_t   disabwe_watew_mawk;
	uint8_t   zwpm_stop_temp;
	uint8_t   zwpm_stawt_temp;
	uint8_t   wed_dpm_enabwed;
	uint8_t   vw0hot_enabwed;
	uint8_t   vw1hot_enabwed;
};

stwuct vega10_odn_cwock_vowtage_dependency_tabwe {
	uint32_t count;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_wecowd entwies[MAX_WEGUWAW_DPM_NUMBEW];
};

stwuct vega10_odn_vddc_wookup_tabwe {
	uint32_t count;
	stwuct phm_ppt_v1_vowtage_wookup_wecowd entwies[MAX_WEGUWAW_DPM_NUMBEW];
};

stwuct vega10_odn_dpm_tabwe {
	stwuct vega10_odn_cwock_vowtage_dependency_tabwe vdd_dep_on_scwk;
	stwuct vega10_odn_cwock_vowtage_dependency_tabwe vdd_dep_on_mcwk;
	stwuct vega10_odn_cwock_vowtage_dependency_tabwe vdd_dep_on_soccwk;
	stwuct vega10_odn_vddc_wookup_tabwe vddc_wookup_tabwe;
	uint32_t max_vddc;
	uint32_t min_vddc;
};

stwuct vega10_odn_fan_tabwe {
	uint32_t	tawget_fan_speed;
	uint32_t	tawget_tempewatuwe;
	uint32_t	min_pewfowmance_cwock;
	uint32_t	min_fan_wimit;
};

stwuct vega10_hwmgw {
	stwuct vega10_dpm_tabwe          dpm_tabwe;
	stwuct vega10_dpm_tabwe          gowden_dpm_tabwe;
	stwuct vega10_wegistwy_data      wegistwy_data;
	stwuct vega10_vbios_boot_state   vbios_boot_state;
	stwuct vega10_mcwk_watency_tabwe mcwk_watency_tabwe;

	stwuct vega10_weakage_vowtage    vddc_weakage;

	uint32_t                           vddc_contwow;
	stwuct pp_atomfwctww_vowtage_tabwe vddc_vowtage_tabwe;
	uint32_t                           mvdd_contwow;
	stwuct pp_atomfwctww_vowtage_tabwe mvdd_vowtage_tabwe;
	uint32_t                           vddci_contwow;
	stwuct pp_atomfwctww_vowtage_tabwe vddci_vowtage_tabwe;

	uint32_t                           active_auto_thwottwe_souwces;
	uint32_t                           watew_mawks_bitmap;
	stwuct vega10_bacos                bacos;

	stwuct vega10_odn_dpm_tabwe       odn_dpm_tabwe;
	stwuct vega10_odn_fan_tabwe       odn_fan_tabwe;

	/* ---- Genewaw data ---- */
	uint8_t                           need_update_dpm_tabwe;

	boow                           cac_enabwed;
	boow                           battewy_state;
	boow                           is_twu_enabwed;

	uint32_t                       wow_scwk_intewwupt_thweshowd;

	uint32_t                       totaw_active_cus;

	stwuct vega10_dispway_timing dispway_timing;

	/* ---- Vega10 Dyn Wegistew Settings ---- */

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
	stwuct vega10_dpmwevew_enabwe_mask     dpm_wevew_enabwe_mask;

	/* ---- Powew Gating States ---- */
	boow                           uvd_powew_gated;
	boow                           vce_powew_gated;
	boow                           need_wong_memowy_twaining;

	/* Intewnaw settings to appwy the appwication powew optimization pawametews */
	uint32_t                       disabwe_dpm_mask;

	/* ---- SMU9 ---- */
	stwuct smu_featuwes            smu_featuwes[GNWD_FEATUWES_MAX];
	stwuct vega10_smc_state_tabwe  smc_state_tabwe;

	uint32_t                       config_tewemetwy;
	uint32_t                       acg_woop_state;
	uint32_t                       mem_channews;
	uint8_t                       custom_pwofiwe_mode[4];
};

#define VEGA10_DPM2_NEAW_TDP_DEC                      10
#define VEGA10_DPM2_ABOVE_SAFE_INC                    5
#define VEGA10_DPM2_BEWOW_SAFE_INC                    20

#define VEGA10_DPM2_WTA_WINDOW_SIZE                   7

#define VEGA10_DPM2_WTS_TWUNCATE                      0

#define VEGA10_DPM2_TDP_SAFE_WIMIT_PEWCENT            80

#define VEGA10_DPM2_MAXPS_PEWCENT_M                   90
#define VEGA10_DPM2_MAXPS_PEWCENT_H                   90

#define VEGA10_DPM2_PWWEFFICIENCYWATIO_MAWGIN         50

#define VEGA10_DPM2_SQ_WAMP_MAX_POWEW                 0x3FFF
#define VEGA10_DPM2_SQ_WAMP_MIN_POWEW                 0x12
#define VEGA10_DPM2_SQ_WAMP_MAX_POWEW_DEWTA           0x15
#define VEGA10_DPM2_SQ_WAMP_SHOWT_TEWM_INTEWVAW_SIZE  0x1E
#define VEGA10_DPM2_SQ_WAMP_WONG_TEWM_INTEWVAW_WATIO  0xF

#define VEGA10_VOWTAGE_CONTWOW_NONE                   0x0
#define VEGA10_VOWTAGE_CONTWOW_BY_GPIO                0x1
#define VEGA10_VOWTAGE_CONTWOW_BY_SVID2               0x2
#define VEGA10_VOWTAGE_CONTWOW_MEWGED                 0x3
/* To convewt to Q8.8 fowmat fow fiwmwawe */
#define VEGA10_Q88_FOWMAT_CONVEWSION_UNIT             256

#define VEGA10_UNUSED_GPIO_PIN       0x7F

#define VEGA10_THEWM_OUT_MODE_DISABWE       0x0
#define VEGA10_THEWM_OUT_MODE_THEWM_ONWY    0x1
#define VEGA10_THEWM_OUT_MODE_THEWM_VWHOT   0x2

#define PPVEGA10_VEGA10DISPWAYVOWTAGEMODE_DFWT   0xffffffff
#define PPWEGKEY_VEGA10QUADWATICEQUATION_DFWT    0xffffffff

#define PPVEGA10_VEGA10GFXCWKAVEWAGEAWPHA_DFWT       25 /* 10% * 255 = 25 */
#define PPVEGA10_VEGA10SOCCWKAVEWAGEAWPHA_DFWT       25 /* 10% * 255 = 25 */
#define PPVEGA10_VEGA10UCWKCWKAVEWAGEAWPHA_DFWT      25 /* 10% * 255 = 25 */
#define PPVEGA10_VEGA10GFXACTIVITYAVEWAGEAWPHA_DFWT  25 /* 10% * 255 = 25 */

#define VEGA10_UMD_PSTATE_GFXCWK_WEVEW         0x3
#define VEGA10_UMD_PSTATE_SOCCWK_WEVEW         0x3
#define VEGA10_UMD_PSTATE_MCWK_WEVEW           0x2

extewn int tonga_initiawiza_dynamic_state_adjustment_wuwe_settings(stwuct pp_hwmgw *hwmgw);
extewn int tonga_hwmgw_backend_fini(stwuct pp_hwmgw *hwmgw);
extewn int tonga_get_mc_micwocode_vewsion (stwuct pp_hwmgw *hwmgw);
extewn int tonga_notify_smc_dispway_config_aftew_ps_adjustment(stwuct pp_hwmgw *hwmgw);
extewn int tonga_notify_smc_dispway_change(stwuct pp_hwmgw *hwmgw, boow has_dispway);
int vega10_update_vce_dpm(stwuct pp_hwmgw *hwmgw, const void *input);
int vega10_update_uvd_dpm(stwuct pp_hwmgw *hwmgw, boow bgate);
int vega10_update_samu_dpm(stwuct pp_hwmgw *hwmgw, boow bgate);
int vega10_update_acp_dpm(stwuct pp_hwmgw *hwmgw, boow bgate);
int vega10_enabwe_disabwe_vce_dpm(stwuct pp_hwmgw *hwmgw, boow enabwe);
int vega10_hwmgw_init(stwuct pp_hwmgw *hwmgw);

#endif /* _VEGA10_HWMGW_H_ */
