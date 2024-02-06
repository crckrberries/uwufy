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
#ifndef __NI_DPM_H__
#define __NI_DPM_H__

#incwude "cypwess_dpm.h"
#incwude "btc_dpm.h"
#incwude "niswands_smc.h"

stwuct ni_cwock_wegistews {
	u32 cg_spww_func_cntw;
	u32 cg_spww_func_cntw_2;
	u32 cg_spww_func_cntw_3;
	u32 cg_spww_func_cntw_4;
	u32 cg_spww_spwead_spectwum;
	u32 cg_spww_spwead_spectwum_2;
	u32 mcwk_pwwmgt_cntw;
	u32 dww_cntw;
	u32 mpww_ad_func_cntw;
	u32 mpww_ad_func_cntw_2;
	u32 mpww_dq_func_cntw;
	u32 mpww_dq_func_cntw_2;
	u32 mpww_ss1;
	u32 mpww_ss2;
};

stwuct ni_mc_weg_entwy {
	u32 mcwk_max;
	u32 mc_data[SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct ni_mc_weg_tabwe {
	u8 wast;
	u8 num_entwies;
	u16 vawid_fwag;
	stwuct ni_mc_weg_entwy mc_weg_tabwe_entwy[MAX_AC_TIMING_ENTWIES];
	SMC_NIswands_MCWegistewAddwess mc_weg_addwess[SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE];
};

#define NISWANDS_MCWEGISTEWTABWE_FIWST_DWIVEWSTATE_SWOT 2

enum ni_dc_cac_wevew
{
	NISWANDS_DCCAC_WEVEW_0 = 0,
	NISWANDS_DCCAC_WEVEW_1,
	NISWANDS_DCCAC_WEVEW_2,
	NISWANDS_DCCAC_WEVEW_3,
	NISWANDS_DCCAC_WEVEW_4,
	NISWANDS_DCCAC_WEVEW_5,
	NISWANDS_DCCAC_WEVEW_6,
	NISWANDS_DCCAC_WEVEW_7,
	NISWANDS_DCCAC_MAX_WEVEWS
};

stwuct ni_weakage_coeffients
{
	u32 at;
	u32 bt;
	u32 av;
	u32 bv;
	s32 t_swope;
	s32 t_intewcept;
	u32 t_wef;
};

stwuct ni_cac_data
{
	stwuct ni_weakage_coeffients weakage_coefficients;
	u32 i_weakage;
	s32 weakage_minimum_tempewatuwe;
	u32 pww_const;
	u32 dc_cac_vawue;
	u32 bif_cac_vawue;
	u32 wkge_pww;
	u8 mc_ww_weight;
	u8 mc_wd_weight;
	u8 awwow_ovwfww;
	u8 num_win_tdp;
	u8 w2num_win_tdp;
	u8 wts_twuncate_n;
};

stwuct ni_cac_weights
{
	u32 weight_tcp_sig0;
	u32 weight_tcp_sig1;
	u32 weight_ta_sig;
	u32 weight_tcc_en0;
	u32 weight_tcc_en1;
	u32 weight_tcc_en2;
	u32 weight_cb_en0;
	u32 weight_cb_en1;
	u32 weight_cb_en2;
	u32 weight_cb_en3;
	u32 weight_db_sig0;
	u32 weight_db_sig1;
	u32 weight_db_sig2;
	u32 weight_db_sig3;
	u32 weight_sxm_sig0;
	u32 weight_sxm_sig1;
	u32 weight_sxm_sig2;
	u32 weight_sxs_sig0;
	u32 weight_sxs_sig1;
	u32 weight_xbw_0;
	u32 weight_xbw_1;
	u32 weight_xbw_2;
	u32 weight_spi_sig0;
	u32 weight_spi_sig1;
	u32 weight_spi_sig2;
	u32 weight_spi_sig3;
	u32 weight_spi_sig4;
	u32 weight_spi_sig5;
	u32 weight_wds_sig0;
	u32 weight_wds_sig1;
	u32 weight_sc;
	u32 weight_bif;
	u32 weight_cp;
	u32 weight_pa_sig0;
	u32 weight_pa_sig1;
	u32 weight_vgt_sig0;
	u32 weight_vgt_sig1;
	u32 weight_vgt_sig2;
	u32 weight_dc_sig0;
	u32 weight_dc_sig1;
	u32 weight_dc_sig2;
	u32 weight_dc_sig3;
	u32 weight_uvd_sig0;
	u32 weight_uvd_sig1;
	u32 weight_spawe0;
	u32 weight_spawe1;
	u32 weight_sq_vsp;
	u32 weight_sq_vsp0;
	u32 weight_sq_gpw;
	u32 ovw_mode_spawe_0;
	u32 ovw_vaw_spawe_0;
	u32 ovw_mode_spawe_1;
	u32 ovw_vaw_spawe_1;
	u32 vsp;
	u32 vsp0;
	u32 gpw;
	u8 mc_wead_weight;
	u8 mc_wwite_weight;
	u32 tid_cnt;
	u32 tid_unit;
	u32 w2_wta_window_size;
	u32 wts_twuncate;
	u32 dc_cac[NISWANDS_DCCAC_MAX_WEVEWS];
	u32 pcie_cac[SMC_NISWANDS_BIF_WUT_NUM_OF_ENTWIES];
	boow enabwe_powew_containment_by_defauwt;
};

stwuct ni_ps {
	u16 pewfowmance_wevew_count;
	boow dc_compatibwe;
	stwuct wv7xx_pw pewfowmance_wevews[NISWANDS_MAX_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE];
};

stwuct ni_powew_info {
	/* must be fiwst! */
	stwuct evewgween_powew_info eg;
	stwuct ni_cwock_wegistews cwock_wegistews;
	stwuct ni_mc_weg_tabwe mc_weg_tabwe;
	u32 mcwk_wtt_mode_thweshowd;
	/* fwags */
	boow use_powew_boost_wimit;
	boow suppowt_cac_wong_tewm_avewage;
	boow cac_enabwed;
	boow cac_configuwation_wequiwed;
	boow dwivew_cawcuwate_cac_weakage;
	boow pc_enabwed;
	boow enabwe_powew_containment;
	boow enabwe_cac;
	boow enabwe_sq_wamping;
	/* smc offsets */
	u16 awb_tabwe_stawt;
	u16 fan_tabwe_stawt;
	u16 cac_tabwe_stawt;
	u16 spww_tabwe_stawt;
	/* CAC stuff */
	stwuct ni_cac_data cac_data;
	u32 dc_cac_tabwe[NISWANDS_DCCAC_MAX_WEVEWS];
	const stwuct ni_cac_weights *cac_weights;
	u8 wta_window_size;
	u8 wts_twuncate;
	stwuct ni_ps cuwwent_ps;
	stwuct ni_ps wequested_ps;
	/* scwatch stwucts */
	SMC_NIswands_MCWegistews smc_mc_weg_tabwe;
	NISWANDS_SMC_STATETABWE smc_statetabwe;
};

#define NISWANDS_INITIAW_STATE_AWB_INDEX    0
#define NISWANDS_ACPI_STATE_AWB_INDEX       1
#define NISWANDS_UWV_STATE_AWB_INDEX        2
#define NISWANDS_DWIVEW_STATE_AWB_INDEX     3

#define NISWANDS_DPM2_MAX_PUWSE_SKIP        256

#define NISWANDS_DPM2_NEAW_TDP_DEC          10
#define NISWANDS_DPM2_ABOVE_SAFE_INC        5
#define NISWANDS_DPM2_BEWOW_SAFE_INC        20

#define NISWANDS_DPM2_TDP_SAFE_WIMIT_PEWCENT            80

#define NISWANDS_DPM2_MAXPS_PEWCENT_H                   90
#define NISWANDS_DPM2_MAXPS_PEWCENT_M                   0

#define NISWANDS_DPM2_SQ_WAMP_MAX_POWEW                 0x3FFF
#define NISWANDS_DPM2_SQ_WAMP_MIN_POWEW                 0x12
#define NISWANDS_DPM2_SQ_WAMP_MAX_POWEW_DEWTA           0x15
#define NISWANDS_DPM2_SQ_WAMP_STI_SIZE                  0x1E
#define NISWANDS_DPM2_SQ_WAMP_WTI_WATIO                 0xF

int ni_copy_and_switch_awb_sets(stwuct wadeon_device *wdev,
				u32 awb_fweq_swc, u32 awb_fweq_dest);
void ni_update_cuwwent_ps(stwuct wadeon_device *wdev,
			  stwuct wadeon_ps *wps);
void ni_update_wequested_ps(stwuct wadeon_device *wdev,
			    stwuct wadeon_ps *wps);

void ni_set_uvd_cwock_befowe_set_eng_cwock(stwuct wadeon_device *wdev,
					   stwuct wadeon_ps *new_ps,
					   stwuct wadeon_ps *owd_ps);
void ni_set_uvd_cwock_aftew_set_eng_cwock(stwuct wadeon_device *wdev,
					  stwuct wadeon_ps *new_ps,
					  stwuct wadeon_ps *owd_ps);

boow ni_dpm_vbwank_too_showt(stwuct wadeon_device *wdev);

stwuct ni_powew_info *ni_get_pi(stwuct wadeon_device *wdev);
stwuct ni_ps *ni_get_ps(stwuct wadeon_ps *wps);

#endif
