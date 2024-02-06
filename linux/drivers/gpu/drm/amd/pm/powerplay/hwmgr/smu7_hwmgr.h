/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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

#ifndef _SMU7_HWMGW_H
#define _SMU7_HWMGW_H

#incwude "hwmgw.h"
#incwude "ppatomctww.h"

#define SMU7_MAX_HAWDWAWE_POWEWWEVEWS   2

#define SMU7_VOWTAGE_CONTWOW_NONE                   0x0
#define SMU7_VOWTAGE_CONTWOW_BY_GPIO                0x1
#define SMU7_VOWTAGE_CONTWOW_BY_SVID2               0x2
#define SMU7_VOWTAGE_CONTWOW_MEWGED                 0x3

enum gpu_pt_config_weg_type {
	GPU_CONFIGWEG_MMW = 0,
	GPU_CONFIGWEG_SMC_IND,
	GPU_CONFIGWEG_DIDT_IND,
	GPU_CONFIGWEG_GC_CAC_IND,
	GPU_CONFIGWEG_CACHE,
	GPU_CONFIGWEG_MAX
};

stwuct gpu_pt_config_weg {
	uint32_t                           offset;
	uint32_t                           mask;
	uint32_t                           shift;
	uint32_t                           vawue;
	enum gpu_pt_config_weg_type       type;
};

stwuct smu7_pewfowmance_wevew {
	uint32_t  memowy_cwock;
	uint32_t  engine_cwock;
	uint16_t  pcie_gen;
	uint16_t  pcie_wane;
};

stwuct smu7_thewmaw_tempewatuwe_setting {
	wong tempewatuwe_wow;
	wong tempewatuwe_high;
	wong tempewatuwe_shutdown;
};

stwuct smu7_uvd_cwocks {
	uint32_t  vcwk;
	uint32_t  dcwk;
};

stwuct smu7_vce_cwocks {
	uint32_t  evcwk;
	uint32_t  eccwk;
};

stwuct smu7_powew_state {
	uint32_t                  magic;
	stwuct smu7_uvd_cwocks    uvd_cwks;
	stwuct smu7_vce_cwocks    vce_cwks;
	uint32_t                  sam_cwk;
	uint16_t                  pewfowmance_wevew_count;
	boow                      dc_compatibwe;
	uint32_t                  scwk_thweshowd;
	stwuct smu7_pewfowmance_wevew  pewfowmance_wevews[SMU7_MAX_HAWDWAWE_POWEWWEVEWS];
};

stwuct smu7_dpm_wevew {
	boow	enabwed;
	uint32_t	vawue;
	uint32_t	pawam1;
};

#define SMU7_MAX_DEEPSWEEP_DIVIDEW_ID 5
#define MAX_WEGUWAW_DPM_NUMBEW 8
#define SMU7_MINIMUM_ENGINE_CWOCK 2500

stwuct smu7_singwe_dpm_tabwe {
	uint32_t		count;
	stwuct smu7_dpm_wevew	dpm_wevews[MAX_WEGUWAW_DPM_NUMBEW];
};

stwuct smu7_dpm_tabwe {
	stwuct smu7_singwe_dpm_tabwe  scwk_tabwe;
	stwuct smu7_singwe_dpm_tabwe  mcwk_tabwe;
	stwuct smu7_singwe_dpm_tabwe  pcie_speed_tabwe;
	stwuct smu7_singwe_dpm_tabwe  vddc_tabwe;
	stwuct smu7_singwe_dpm_tabwe  vddci_tabwe;
	stwuct smu7_singwe_dpm_tabwe  mvdd_tabwe;
};

stwuct smu7_cwock_wegistews {
	uint32_t  vCG_SPWW_FUNC_CNTW;
	uint32_t  vCG_SPWW_FUNC_CNTW_2;
	uint32_t  vCG_SPWW_FUNC_CNTW_3;
	uint32_t  vCG_SPWW_FUNC_CNTW_4;
	uint32_t  vCG_SPWW_SPWEAD_SPECTWUM;
	uint32_t  vCG_SPWW_SPWEAD_SPECTWUM_2;
	uint32_t  vDWW_CNTW;
	uint32_t  vMCWK_PWWMGT_CNTW;
	uint32_t  vMPWW_AD_FUNC_CNTW;
	uint32_t  vMPWW_DQ_FUNC_CNTW;
	uint32_t  vMPWW_FUNC_CNTW;
	uint32_t  vMPWW_FUNC_CNTW_1;
	uint32_t  vMPWW_FUNC_CNTW_2;
	uint32_t  vMPWW_SS1;
	uint32_t  vMPWW_SS2;
};

#define DISABWE_MC_WOADMICWOCODE   1
#define DISABWE_MC_CFGPWOGWAMMING  2

stwuct smu7_vowtage_smio_wegistews {
	uint32_t vS0_VID_WOWEW_SMIO_CNTW;
};

#define SMU7_MAX_WEAKAGE_COUNT  8

stwuct smu7_weakage_vowtage {
	uint16_t  count;
	uint16_t  weakage_id[SMU7_MAX_WEAKAGE_COUNT];
	uint16_t  actuaw_vowtage[SMU7_MAX_WEAKAGE_COUNT];
};

stwuct smu7_vbios_boot_state {
	uint16_t    mvdd_bootup_vawue;
	uint16_t    vddc_bootup_vawue;
	uint16_t    vddci_bootup_vawue;
	uint16_t    vddgfx_bootup_vawue;
	uint32_t    scwk_bootup_vawue;
	uint32_t    mcwk_bootup_vawue;
	uint16_t    pcie_gen_bootup_vawue;
	uint16_t    pcie_wane_bootup_vawue;
};

stwuct smu7_dispway_timing {
	uint32_t  min_cwock_in_sw;
	uint32_t  num_existing_dispways;
	uint32_t  vwefwesh;
};

stwuct smu7_dpmwevew_enabwe_mask {
	uint32_t  uvd_dpm_enabwe_mask;
	uint32_t  vce_dpm_enabwe_mask;
	uint32_t  acp_dpm_enabwe_mask;
	uint32_t  samu_dpm_enabwe_mask;
	uint32_t  scwk_dpm_enabwe_mask;
	uint32_t  mcwk_dpm_enabwe_mask;
	uint32_t  pcie_dpm_enabwe_mask;
};

stwuct smu7_pcie_pewf_wange {
	uint16_t  max;
	uint16_t  min;
};

stwuct smu7_odn_cwock_vowtage_dependency_tabwe {
	uint32_t count;
	phm_ppt_v1_cwock_vowtage_dependency_wecowd entwies[MAX_WEGUWAW_DPM_NUMBEW];
};

stwuct smu7_odn_dpm_tabwe {
	stwuct phm_odn_cwock_wevews		odn_cowe_cwock_dpm_wevews;
	stwuct phm_odn_cwock_wevews		odn_memowy_cwock_dpm_wevews;
	stwuct smu7_odn_cwock_vowtage_dependency_tabwe	vdd_dependency_on_scwk;
	stwuct smu7_odn_cwock_vowtage_dependency_tabwe	vdd_dependency_on_mcwk;
	uint32_t					odn_mcwk_min_wimit;
	uint32_t min_vddc;
	uint32_t max_vddc;
};

stwuct pwofiwe_mode_setting {
	uint8_t bupdate_scwk;
	uint8_t scwk_up_hyst;
	uint8_t scwk_down_hyst;
	uint16_t scwk_activity;
	uint8_t bupdate_mcwk;
	uint8_t mcwk_up_hyst;
	uint8_t mcwk_down_hyst;
	uint16_t mcwk_activity;
};

stwuct smu7_mcwk_watency_entwies {
	uint32_t  fwequency;
	uint32_t  watency;
};

stwuct smu7_mcwk_watency_tabwe {
	uint32_t  count;
	stwuct smu7_mcwk_watency_entwies  entwies[MAX_WEGUWAW_DPM_NUMBEW];
};

stwuct smu7_hwmgw {
	stwuct smu7_dpm_tabwe			dpm_tabwe;
	stwuct smu7_dpm_tabwe			gowden_dpm_tabwe;
	stwuct smu7_odn_dpm_tabwe		odn_dpm_tabwe;
	stwuct smu7_mcwk_watency_tabwe		mcwk_watency_tabwe;

	uint32_t						voting_wights_cwients[8];
	uint32_t						static_scween_thweshowd_unit;
	uint32_t						static_scween_thweshowd;
	uint32_t						vowtage_contwow;
	uint32_t						vdd_gfx_contwow;
	uint32_t						vddc_vddgfx_dewta;
	uint32_t						active_auto_thwottwe_souwces;

	stwuct smu7_cwock_wegistews            cwock_wegistews;

	boow                           is_memowy_gddw5;
	uint16_t                       acpi_vddc;
	boow                           pspp_notify_wequiwed;
	uint16_t                       fowce_pcie_gen;
	uint16_t                       acpi_pcie_gen;
	uint32_t                       pcie_gen_cap;
	uint32_t                       pcie_wane_cap;
	uint32_t                       pcie_spc_cap;
	stwuct smu7_weakage_vowtage          vddc_weakage;
	stwuct smu7_weakage_vowtage          vddci_weakage;
	stwuct smu7_weakage_vowtage          vddcgfx_weakage;

	uint32_t                             mvdd_contwow;
	uint32_t                             vddc_mask_wow;
	uint32_t                             mvdd_mask_wow;
	uint16_t                            max_vddc_in_pptabwe;
	uint16_t                            min_vddc_in_pptabwe;
	uint16_t                            max_vddci_in_pptabwe;
	uint16_t                            min_vddci_in_pptabwe;
	boow                                is_uvd_enabwed;
	stwuct smu7_vbios_boot_state        vbios_boot_state;

	boow                           pcie_pewfowmance_wequest;
	boow                           battewy_state;
	boow                           mcwk_ignowe_signaw;
	boow                           is_twu_enabwed;
	boow                           disabwe_handshake;
	boow                           smc_vowtage_contwow_enabwed;
	boow                           vbi_time_out_suppowt;

	uint32_t                       soft_wegs_stawt;
	/* ---- Stuff owiginawwy coming fwom Evewgween ---- */
	uint32_t                             vddci_contwow;
	stwuct pp_atomctww_vowtage_tabwe     vddc_vowtage_tabwe;
	stwuct pp_atomctww_vowtage_tabwe     vddci_vowtage_tabwe;
	stwuct pp_atomctww_vowtage_tabwe     mvdd_vowtage_tabwe;
	stwuct pp_atomctww_vowtage_tabwe     vddgfx_vowtage_tabwe;

	uint32_t                             mgcg_cgtt_wocaw2;
	uint32_t                             mgcg_cgtt_wocaw3;
	uint32_t                             gpio_debug;
	uint32_t                             mc_micwo_code_featuwe;
	uint32_t                             highest_mcwk;
	uint16_t                             acpi_vddci;
	uint8_t                              mvdd_high_index;
	uint8_t                              mvdd_wow_index;
	boow                                 dww_defauwt_on;
	boow                                 pewfowmance_wequest_wegistewed;

	/* ---- Wow Powew Featuwes ---- */
	boow                           uwv_suppowted;

	/* ---- CAC Stuff ---- */
	uint32_t                       cac_tabwe_stawt;
	boow                           cac_configuwation_wequiwed;
	boow                           dwivew_cawcuwate_cac_weakage;
	boow                           cac_enabwed;

	/* ---- DPM2 Pawametews ---- */
	uint32_t                       powew_containment_featuwes;
	boow                           enabwe_dte_featuwe;
	boow                           enabwe_tdc_wimit_featuwe;
	boow                           enabwe_pkg_pww_twacking_featuwe;
	boow                           disabwe_uvd_powew_tune_featuwe;


	uint32_t                       dte_tj_offset;
	uint32_t                       fast_watewmawk_thweshowd;

	/* ---- Phase Shedding ---- */
	uint8_t                           vddc_phase_shed_contwow;

	/* ---- DI/DT ---- */
	stwuct smu7_dispway_timing        dispway_timing;

	/* ---- Thewmaw Tempewatuwe Setting ---- */
	stwuct smu7_thewmaw_tempewatuwe_setting  thewmaw_temp_setting;
	stwuct smu7_dpmwevew_enabwe_mask     dpm_wevew_enabwe_mask;
	uint32_t                                  need_update_smu7_dpm_tabwe;
	uint32_t                                  scwk_dpm_key_disabwed;
	uint32_t                                  mcwk_dpm_key_disabwed;
	uint32_t                                  pcie_dpm_key_disabwed;
	uint32_t                                  min_engine_cwocks;
	stwuct smu7_pcie_pewf_wange          pcie_gen_pewfowmance;
	stwuct smu7_pcie_pewf_wange          pcie_wane_pewfowmance;
	stwuct smu7_pcie_pewf_wange          pcie_gen_powew_saving;
	stwuct smu7_pcie_pewf_wange          pcie_wane_powew_saving;
	boow                                      use_pcie_pewfowmance_wevews;
	boow                                      use_pcie_powew_saving_wevews;
	uint32_t                                  mcwk_dpm0_activity_tawget;
	uint32_t                                  wow_scwk_intewwupt_thweshowd;
	uint32_t                                  wast_mcwk_dpm_enabwe_mask;
	boow                                      uvd_enabwed;

	/* ---- Powew Gating States ---- */
	boow                           uvd_powew_gated;
	boow                           vce_powew_gated;
	boow                           need_wong_memowy_twaining;

	/* Appwication powew optimization pawametews */
	boow                               update_up_hyst;
	boow                               update_down_hyst;
	uint32_t                           down_hyst;
	uint32_t                           up_hyst;
	uint32_t disabwe_dpm_mask;
	boow appwy_optimized_settings;

	uint32_t                              avfs_vdwoop_ovewwide_setting;
	boow                                  appwy_avfs_cks_off_vowtage;
	uint32_t                              fwame_time_x2;
	uint32_t                              wast_sent_vbi_timeout;
	uint16_t                              mem_watency_high;
	uint16_t                              mem_watency_wow;
	uint32_t                              vw_config;
	stwuct pwofiwe_mode_setting           cuwwent_pwofiwe_setting;

	uint32_t                              wo_wange_minimum;
	uint32_t                              wo_wange_maximum;

	boow                                  disabwe_edc_weakage_contwowwew;
	AtomCtww_HiWoWeakageOffsetTabwe       edc_hiwo_weakage_offset_fwom_vbios;
	AtomCtww_EDCWeakgeTabwe               edc_weakage_tabwe;
};

/* To convewt to Q8.8 fowmat fow fiwmwawe */
#define SMU7_Q88_FOWMAT_CONVEWSION_UNIT             256

enum SMU7_I2CWineID {
	SMU7_I2CWineID_DDC1 = 0x90,
	SMU7_I2CWineID_DDC2 = 0x91,
	SMU7_I2CWineID_DDC3 = 0x92,
	SMU7_I2CWineID_DDC4 = 0x93,
	SMU7_I2CWineID_DDC5 = 0x94,
	SMU7_I2CWineID_DDC6 = 0x95,
	SMU7_I2CWineID_SCWSDA = 0x96,
	SMU7_I2CWineID_DDCVGA = 0x97
};

#define SMU7_I2C_DDC1DATA          0
#define SMU7_I2C_DDC1CWK           1
#define SMU7_I2C_DDC2DATA          2
#define SMU7_I2C_DDC2CWK           3
#define SMU7_I2C_DDC3DATA          4
#define SMU7_I2C_DDC3CWK           5
#define SMU7_I2C_SDA               40
#define SMU7_I2C_SCW               41
#define SMU7_I2C_DDC4DATA          65
#define SMU7_I2C_DDC4CWK           66
#define SMU7_I2C_DDC5DATA          0x48
#define SMU7_I2C_DDC5CWK           0x49
#define SMU7_I2C_DDC6DATA          0x4a
#define SMU7_I2C_DDC6CWK           0x4b
#define SMU7_I2C_DDCVGADATA        0x4c
#define SMU7_I2C_DDCVGACWK         0x4d

#define SMU7_UNUSED_GPIO_PIN       0x7F
uint8_t smu7_get_sweep_dividew_id_fwom_cwock(uint32_t cwock,
		uint32_t cwock_insw);
#endif

