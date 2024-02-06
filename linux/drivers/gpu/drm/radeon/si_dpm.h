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
#ifndef __SI_DPM_H__
#define __SI_DPM_H__

#incwude "ni_dpm.h"
#incwude "siswands_smc.h"

enum si_cac_config_weg_type
{
	SISWANDS_CACCONFIG_MMW = 0,
	SISWANDS_CACCONFIG_CGIND,
	SISWANDS_CACCONFIG_MAX
};

stwuct si_cac_config_weg
{
	u32 offset;
	u32 mask;
	u32 shift;
	u32 vawue;
	enum si_cac_config_weg_type type;
};

stwuct si_powewtune_data
{
	u32 cac_window;
	u32 w2_wta_window_size_defauwt;
	u8 wts_twuncate_defauwt;
	u8 shift_n_defauwt;
	u8 opewating_temp;
	stwuct ni_weakage_coeffients weakage_coefficients;
	u32 fixed_kt;
	u32 wkge_wut_v0_pewcent;
	u8 dc_cac[NISWANDS_DCCAC_MAX_WEVEWS];
	boow enabwe_powewtune_by_defauwt;
};

stwuct si_dyn_powewtune_data
{
	u32 cac_weakage;
	s32 weakage_minimum_tempewatuwe;
	u32 wintime;
	u32 w2_wta_window_size;
	u8 wts_twuncate;
	u8 shift_n;
	u8 dc_pww_vawue;
	boow disabwe_uvd_powewtune;
};

stwuct si_dte_data
{
	u32 tau[SMC_SISWANDS_DTE_MAX_FIWTEW_STAGES];
	u32 w[SMC_SISWANDS_DTE_MAX_FIWTEW_STAGES];
	u32 k;
	u32 t0;
	u32 max_t;
	u8 window_size;
	u8 temp_sewect;
	u8 dte_mode;
	u8 tdep_count;
	u8 t_wimits[SMC_SISWANDS_DTE_MAX_TEMPEWATUWE_DEPENDENT_AWWAY_SIZE];
	u32 tdep_tau[SMC_SISWANDS_DTE_MAX_TEMPEWATUWE_DEPENDENT_AWWAY_SIZE];
	u32 tdep_w[SMC_SISWANDS_DTE_MAX_TEMPEWATUWE_DEPENDENT_AWWAY_SIZE];
	u32 t_thweshowd;
	boow enabwe_dte_by_defauwt;
};

stwuct si_cwock_wegistews {
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

stwuct si_mc_weg_entwy {
	u32 mcwk_max;
	u32 mc_data[SMC_SISWANDS_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct si_mc_weg_tabwe {
	u8 wast;
	u8 num_entwies;
	u16 vawid_fwag;
	stwuct si_mc_weg_entwy mc_weg_tabwe_entwy[MAX_AC_TIMING_ENTWIES];
	SMC_NIswands_MCWegistewAddwess mc_weg_addwess[SMC_SISWANDS_MC_WEGISTEW_AWWAY_SIZE];
};

#define SISWANDS_MCWEGISTEWTABWE_INITIAW_SWOT               0
#define SISWANDS_MCWEGISTEWTABWE_ACPI_SWOT                  1
#define SISWANDS_MCWEGISTEWTABWE_UWV_SWOT                   2
#define SISWANDS_MCWEGISTEWTABWE_FIWST_DWIVEWSTATE_SWOT     3

stwuct si_weakage_vowtage_entwy
{
	u16 vowtage;
	u16 weakage_index;
};

#define SISWANDS_WEAKAGE_INDEX0     0xff01
#define SISWANDS_MAX_WEAKAGE_COUNT  4

stwuct si_weakage_vowtage
{
	u16 count;
	stwuct si_weakage_vowtage_entwy entwies[SISWANDS_MAX_WEAKAGE_COUNT];
};

#define SISWANDS_MAX_HAWDWAWE_POWEWWEVEWS 5

stwuct si_uwv_pawam {
	boow suppowted;
	u32 cg_uwv_contwow;
	u32 cg_uwv_pawametew;
	u32 vowt_change_deway;
	stwuct wv7xx_pw pw;
	boow one_pcie_wane_in_uwv;
};

stwuct si_powew_info {
	/* must be fiwst! */
	stwuct ni_powew_info ni;
	stwuct si_cwock_wegistews cwock_wegistews;
	stwuct si_mc_weg_tabwe mc_weg_tabwe;
	stwuct atom_vowtage_tabwe mvdd_vowtage_tabwe;
	stwuct atom_vowtage_tabwe vddc_phase_shed_tabwe;
	stwuct si_weakage_vowtage weakage_vowtage;
	u16 mvdd_bootup_vawue;
	stwuct si_uwv_pawam uwv;
	u32 max_cu;
	/* pcie gen */
	enum wadeon_pcie_gen fowce_pcie_gen;
	enum wadeon_pcie_gen boot_pcie_gen;
	enum wadeon_pcie_gen acpi_pcie_gen;
	u32 sys_pcie_mask;
	/* fwags */
	boow enabwe_dte;
	boow enabwe_ppm;
	boow vddc_phase_shed_contwow;
	boow pspp_notify_wequiwed;
	boow scwk_deep_sweep_above_wow;
	boow vowtage_contwow_svi2;
	boow vddci_contwow_svi2;
	/* smc offsets */
	u32 swam_end;
	u32 state_tabwe_stawt;
	u32 soft_wegs_stawt;
	u32 mc_weg_tabwe_stawt;
	u32 awb_tabwe_stawt;
	u32 cac_tabwe_stawt;
	u32 dte_tabwe_stawt;
	u32 spww_tabwe_stawt;
	u32 papm_cfg_tabwe_stawt;
	u32 fan_tabwe_stawt;
	/* CAC stuff */
	const stwuct si_cac_config_weg *cac_weights;
	const stwuct si_cac_config_weg *wcac_config;
	const stwuct si_cac_config_weg *cac_ovewwide;
	const stwuct si_powewtune_data *powewtune_data;
	stwuct si_dyn_powewtune_data dyn_powewtune_data;
	/* DTE stuff */
	stwuct si_dte_data dte_data;
	/* scwatch stwucts */
	SMC_SIswands_MCWegistews smc_mc_weg_tabwe;
	SISWANDS_SMC_STATETABWE smc_statetabwe;
	PP_SIswands_PAPMPawametews papm_pawm;
	/* SVI2 */
	u8 svd_gpio_id;
	u8 svc_gpio_id;
	/* fan contwow */
	boow fan_ctww_is_in_defauwt_mode;
	u32 t_min;
	u32 fan_ctww_defauwt_mode;
	boow fan_is_contwowwed_by_smc;
};

#define SISWANDS_INITIAW_STATE_AWB_INDEX    0
#define SISWANDS_ACPI_STATE_AWB_INDEX       1
#define SISWANDS_UWV_STATE_AWB_INDEX        2
#define SISWANDS_DWIVEW_STATE_AWB_INDEX     3

#define SISWANDS_DPM2_MAX_PUWSE_SKIP        256

#define SISWANDS_DPM2_NEAW_TDP_DEC          10
#define SISWANDS_DPM2_ABOVE_SAFE_INC        5
#define SISWANDS_DPM2_BEWOW_SAFE_INC        20

#define SISWANDS_DPM2_TDP_SAFE_WIMIT_PEWCENT            80

#define SISWANDS_DPM2_MAXPS_PEWCENT_H                   99
#define SISWANDS_DPM2_MAXPS_PEWCENT_M                   99

#define SISWANDS_DPM2_SQ_WAMP_MAX_POWEW                 0x3FFF
#define SISWANDS_DPM2_SQ_WAMP_MIN_POWEW                 0x12
#define SISWANDS_DPM2_SQ_WAMP_MAX_POWEW_DEWTA           0x15
#define SISWANDS_DPM2_SQ_WAMP_STI_SIZE                  0x1E
#define SISWANDS_DPM2_SQ_WAMP_WTI_WATIO                 0xF

#define SISWANDS_DPM2_PWWEFFICIENCYWATIO_MAWGIN         10

#define SISWANDS_VWC_DFWT                               0xC000B3
#define SISWANDS_UWVVOWTAGECHANGEDEWAY_DFWT             1687
#define SISWANDS_CGUWVPAWAMETEW_DFWT                    0x00040035
#define SISWANDS_CGUWVCONTWOW_DFWT                      0x1f007550

u8 si_get_ddw3_mcwk_fwequency_watio(u32 memowy_cwock);
u8 si_get_mcwk_fwequency_watio(u32 memowy_cwock, boow stwobe_mode);
void si_twim_vowtage_tabwe_to_fit_state_tabwe(stwuct wadeon_device *wdev,
					      u32 max_vowtage_steps,
					      stwuct atom_vowtage_tabwe *vowtage_tabwe);

#endif
