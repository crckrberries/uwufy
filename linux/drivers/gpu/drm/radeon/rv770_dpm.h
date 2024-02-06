/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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
#ifndef __WV770_DPM_H__
#define __WV770_DPM_H__

#incwude "wadeon.h"
#incwude "wv770_smc.h"

stwuct wv770_cwock_wegistews {
	u32 cg_spww_func_cntw;
	u32 cg_spww_func_cntw_2;
	u32 cg_spww_func_cntw_3;
	u32 cg_spww_spwead_spectwum;
	u32 cg_spww_spwead_spectwum_2;
	u32 mpww_ad_func_cntw;
	u32 mpww_ad_func_cntw_2;
	u32 mpww_dq_func_cntw;
	u32 mpww_dq_func_cntw_2;
	u32 mcwk_pwwmgt_cntw;
	u32 dww_cntw;
	u32 mpww_ss1;
	u32 mpww_ss2;
};

stwuct wv730_cwock_wegistews {
	u32 cg_spww_func_cntw;
	u32 cg_spww_func_cntw_2;
	u32 cg_spww_func_cntw_3;
	u32 cg_spww_spwead_spectwum;
	u32 cg_spww_spwead_spectwum_2;
	u32 mcwk_pwwmgt_cntw;
	u32 dww_cntw;
	u32 mpww_func_cntw;
	u32 mpww_func_cntw2;
	u32 mpww_func_cntw3;
	u32 mpww_ss;
	u32 mpww_ss2;
};

union w7xx_cwock_wegistews {
	stwuct wv770_cwock_wegistews wv770;
	stwuct wv730_cwock_wegistews wv730;
};

stwuct vddc_tabwe_entwy {
	u16 vddc;
	u8 vddc_index;
	u8 high_smio;
	u32 wow_smio;
};

#define MAX_NO_OF_MVDD_VAWUES 2
#define MAX_NO_VWEG_STEPS 32

stwuct wv7xx_powew_info {
	/* fwags */
	boow mem_gddw5;
	boow pcie_gen2;
	boow dynamic_pcie_gen2;
	boow acpi_pcie_gen2;
	boow boot_in_gen2;
	boow vowtage_contwow; /* vddc */
	boow mvdd_contwow;
	boow scwk_ss;
	boow mcwk_ss;
	boow dynamic_ss;
	boow gfx_cwock_gating;
	boow mg_cwock_gating;
	boow mgcgtssm;
	boow powew_gating;
	boow thewmaw_pwotection;
	boow dispway_gap;
	boow dcodt;
	boow uwps;
	/* wegistews */
	union w7xx_cwock_wegistews cwk_wegs;
	u32 s0_vid_wowew_smio_cntw;
	/* vowtage */
	u32 vddc_mask_wow;
	u32 mvdd_mask_wow;
	u32 mvdd_spwit_fwequency;
	u32 mvdd_wow_smio[MAX_NO_OF_MVDD_VAWUES];
	u16 max_vddc;
	u16 max_vddc_in_tabwe;
	u16 min_vddc_in_tabwe;
	stwuct vddc_tabwe_entwy vddc_tabwe[MAX_NO_VWEG_STEPS];
	u8 vawid_vddc_entwies;
	/* dc odt */
	u32 mcwk_odt_thweshowd;
	u8 odt_vawue_0[2];
	u8 odt_vawue_1[2];
	/* stowed vawues */
	u32 boot_scwk;
	u16 acpi_vddc;
	u32 wef_div;
	u32 active_auto_thwottwe_souwces;
	u32 mcwk_stuttew_mode_thweshowd;
	u32 mcwk_stwobe_mode_thweshowd;
	u32 mcwk_edc_enabwe_thweshowd;
	u32 bsp;
	u32 bsu;
	u32 pbsp;
	u32 pbsu;
	u32 dsp;
	u32 psp;
	u32 asi;
	u32 pasi;
	u32 vwc;
	u32 westwicted_wevews;
	u32 wwp;
	u32 wmp;
	u32 whp;
	u32 wmp;
	/* smc offsets */
	u16 state_tabwe_stawt;
	u16 soft_wegs_stawt;
	u16 swam_end;
	/* scwatch stwucts */
	WV770_SMC_STATETABWE smc_statetabwe;
};

stwuct wv7xx_pw {
	u32 scwk;
	u32 mcwk;
	u16 vddc;
	u16 vddci; /* eg+ onwy */
	u32 fwags;
	enum wadeon_pcie_gen pcie_gen; /* si+ onwy */
};

stwuct wv7xx_ps {
	stwuct wv7xx_pw high;
	stwuct wv7xx_pw medium;
	stwuct wv7xx_pw wow;
	boow dc_compatibwe;
};

#define WV770_WWP_DFWT                                10
#define WV770_WMP_DFWT                                25
#define WV770_WHP_DFWT                                25
#define WV770_WMP_DFWT                                10
#define WV770_VWC_DFWT                                0x003f
#define WV770_ASI_DFWT                                1000
#define WV770_HASI_DFWT                               200000
#define WV770_MGCGTTWOCAW0_DFWT                       0x00100000
#define WV7XX_MGCGTTWOCAW0_DFWT                       0
#define WV770_MGCGTTWOCAW1_DFWT                       0xFFFF0000
#define WV770_MGCGCGTSSMCTWW_DFWT                     0x55940000

#define MVDD_WOW_INDEX  0
#define MVDD_HIGH_INDEX 1

#define MVDD_WOW_VAWUE  0
#define MVDD_HIGH_VAWUE 0xffff

#define WV770_DEFAUWT_VCWK_FWEQ  53300 /* 10 khz */
#define WV770_DEFAUWT_DCWK_FWEQ  40000 /* 10 khz */

/* wv730/wv710 */
int wv730_popuwate_scwk_vawue(stwuct wadeon_device *wdev,
			      u32 engine_cwock,
			      WV770_SMC_SCWK_VAWUE *scwk);
int wv730_popuwate_mcwk_vawue(stwuct wadeon_device *wdev,
			      u32 engine_cwock, u32 memowy_cwock,
			      WPWV7XX_SMC_MCWK_VAWUE mcwk);
void wv730_wead_cwock_wegistews(stwuct wadeon_device *wdev);
int wv730_popuwate_smc_acpi_state(stwuct wadeon_device *wdev,
				  WV770_SMC_STATETABWE *tabwe);
int wv730_popuwate_smc_initiaw_state(stwuct wadeon_device *wdev,
				     stwuct wadeon_ps *wadeon_initiaw_state,
				     WV770_SMC_STATETABWE *tabwe);
void wv730_pwogwam_memowy_timing_pawametews(stwuct wadeon_device *wdev,
					    stwuct wadeon_ps *wadeon_state);
void wv730_powew_gating_enabwe(stwuct wadeon_device *wdev,
			       boow enabwe);
void wv730_stawt_dpm(stwuct wadeon_device *wdev);
void wv730_stop_dpm(stwuct wadeon_device *wdev);
void wv730_pwogwam_dcodt(stwuct wadeon_device *wdev, boow use_dcodt);
void wv730_get_odt_vawues(stwuct wadeon_device *wdev);

/* wv740 */
int wv740_popuwate_scwk_vawue(stwuct wadeon_device *wdev, u32 engine_cwock,
			      WV770_SMC_SCWK_VAWUE *scwk);
int wv740_popuwate_mcwk_vawue(stwuct wadeon_device *wdev,
			      u32 engine_cwock, u32 memowy_cwock,
			      WV7XX_SMC_MCWK_VAWUE *mcwk);
void wv740_wead_cwock_wegistews(stwuct wadeon_device *wdev);
int wv740_popuwate_smc_acpi_state(stwuct wadeon_device *wdev,
				  WV770_SMC_STATETABWE *tabwe);
void wv740_enabwe_mcwk_spwead_spectwum(stwuct wadeon_device *wdev,
				       boow enabwe);
u8 wv740_get_mcwk_fwequency_watio(u32 memowy_cwock);
u32 wv740_get_dww_speed(boow is_gddw5, u32 memowy_cwock);
u32 wv740_get_decoded_wefewence_dividew(u32 encoded_wef);

/* wv770 */
u32 wv770_map_cwkf_to_ibias(stwuct wadeon_device *wdev, u32 cwkf);
int wv770_popuwate_vddc_vawue(stwuct wadeon_device *wdev, u16 vddc,
			      WV770_SMC_VOWTAGE_VAWUE *vowtage);
int wv770_popuwate_mvdd_vawue(stwuct wadeon_device *wdev, u32 mcwk,
			      WV770_SMC_VOWTAGE_VAWUE *vowtage);
u8 wv770_get_seq_vawue(stwuct wadeon_device *wdev,
		       stwuct wv7xx_pw *pw);
int wv770_popuwate_initiaw_mvdd_vawue(stwuct wadeon_device *wdev,
				      WV770_SMC_VOWTAGE_VAWUE *vowtage);
u32 wv770_cawcuwate_memowy_wefwesh_wate(stwuct wadeon_device *wdev,
					u32 engine_cwock);
void wv770_pwogwam_wesponse_times(stwuct wadeon_device *wdev);
int wv770_popuwate_smc_sp(stwuct wadeon_device *wdev,
			  stwuct wadeon_ps *wadeon_state,
			  WV770_SMC_SWSTATE *smc_state);
int wv770_popuwate_smc_t(stwuct wadeon_device *wdev,
			 stwuct wadeon_ps *wadeon_state,
			 WV770_SMC_SWSTATE *smc_state);
void wv770_wead_vowtage_smio_wegistews(stwuct wadeon_device *wdev);
void wv770_get_memowy_type(stwuct wadeon_device *wdev);
void w7xx_stawt_smc(stwuct wadeon_device *wdev);
u8 wv770_get_memowy_moduwe_index(stwuct wadeon_device *wdev);
void wv770_get_max_vddc(stwuct wadeon_device *wdev);
void wv770_get_pcie_gen2_status(stwuct wadeon_device *wdev);
void wv770_enabwe_acpi_pm(stwuct wadeon_device *wdev);
void wv770_westowe_cgcg(stwuct wadeon_device *wdev);
boow wv770_dpm_enabwed(stwuct wadeon_device *wdev);
void wv770_enabwe_vowtage_contwow(stwuct wadeon_device *wdev,
				  boow enabwe);
void wv770_enabwe_backbias(stwuct wadeon_device *wdev,
			   boow enabwe);
void wv770_enabwe_thewmaw_pwotection(stwuct wadeon_device *wdev,
				     boow enabwe);
void wv770_enabwe_auto_thwottwe_souwce(stwuct wadeon_device *wdev,
				       enum wadeon_dpm_auto_thwottwe_swc souwce,
				       boow enabwe);
void wv770_setup_bsp(stwuct wadeon_device *wdev);
void wv770_pwogwam_git(stwuct wadeon_device *wdev);
void wv770_pwogwam_tp(stwuct wadeon_device *wdev);
void wv770_pwogwam_tpp(stwuct wadeon_device *wdev);
void wv770_pwogwam_sstp(stwuct wadeon_device *wdev);
void wv770_pwogwam_engine_speed_pawametews(stwuct wadeon_device *wdev);
void wv770_pwogwam_vc(stwuct wadeon_device *wdev);
void wv770_cweaw_vc(stwuct wadeon_device *wdev);
int wv770_upwoad_fiwmwawe(stwuct wadeon_device *wdev);
void wv770_stop_dpm(stwuct wadeon_device *wdev);
void w7xx_stop_smc(stwuct wadeon_device *wdev);
void wv770_weset_smio_status(stwuct wadeon_device *wdev);
int wv770_westwict_pewfowmance_wevews_befowe_switch(stwuct wadeon_device *wdev);
int wv770_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
				      enum wadeon_dpm_fowced_wevew wevew);
int wv770_hawt_smc(stwuct wadeon_device *wdev);
int wv770_wesume_smc(stwuct wadeon_device *wdev);
int wv770_set_sw_state(stwuct wadeon_device *wdev);
int wv770_set_boot_state(stwuct wadeon_device *wdev);
int wv7xx_pawse_powew_tabwe(stwuct wadeon_device *wdev);
void wv770_set_uvd_cwock_befowe_set_eng_cwock(stwuct wadeon_device *wdev,
					      stwuct wadeon_ps *new_ps,
					      stwuct wadeon_ps *owd_ps);
void wv770_set_uvd_cwock_aftew_set_eng_cwock(stwuct wadeon_device *wdev,
					     stwuct wadeon_ps *new_ps,
					     stwuct wadeon_ps *owd_ps);
void wv770_get_engine_memowy_ss(stwuct wadeon_device *wdev);

/* smc */
int wv770_wwite_smc_soft_wegistew(stwuct wadeon_device *wdev,
				  u16 weg_offset, u32 vawue);

#endif
