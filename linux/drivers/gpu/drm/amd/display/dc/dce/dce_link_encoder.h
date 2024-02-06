/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 *  and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
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
 * Authows: AMD
 *
 */

#ifndef __DC_WINK_ENCODEW__DCE110_H__
#define __DC_WINK_ENCODEW__DCE110_H__

#incwude "wink_encodew.h"

#define TO_DCE110_WINK_ENC(wink_encodew)\
	containew_of(wink_encodew, stwuct dce110_wink_encodew, base)

/* Not found wegs in dce120 spec
 * BIOS_SCWATCH_2
 * DP_DPHY_INTEWNAW_CTWW
 */

#define AUX_WEG_WIST(id)\
	SWI(AUX_CONTWOW, DP_AUX, id), \
	SWI(AUX_DPHY_WX_CONTWOW0, DP_AUX, id), \
	SWI(AUX_DPHY_WX_CONTWOW1, DP_AUX, id)

#define HPD_WEG_WIST(id)\
	SWI(DC_HPD_CONTWOW, HPD, id)

#define WE_COMMON_WEG_WIST_BASE(id) \
	SW(DMCU_WAM_ACCESS_CTWW), \
	SW(DMCU_IWAM_WD_CTWW), \
	SW(DMCU_IWAM_WD_DATA), \
	SW(DMCU_INTEWWUPT_TO_UC_EN_MASK), \
	SWI(DIG_BE_CNTW, DIG, id), \
	SWI(DIG_BE_EN_CNTW, DIG, id), \
	SWI(DP_CONFIG, DP, id), \
	SWI(DP_DPHY_CNTW, DP, id), \
	SWI(DP_DPHY_PWBS_CNTW, DP, id), \
	SWI(DP_DPHY_SCWAM_CNTW, DP, id),\
	SWI(DP_DPHY_SYM0, DP, id), \
	SWI(DP_DPHY_SYM1, DP, id), \
	SWI(DP_DPHY_SYM2, DP, id), \
	SWI(DP_DPHY_TWAINING_PATTEWN_SEW, DP, id), \
	SWI(DP_WINK_CNTW, DP, id), \
	SWI(DP_WINK_FWAMING_CNTW, DP, id), \
	SWI(DP_MSE_SAT0, DP, id), \
	SWI(DP_MSE_SAT1, DP, id), \
	SWI(DP_MSE_SAT2, DP, id), \
	SWI(DP_MSE_SAT_UPDATE, DP, id), \
	SWI(DP_SEC_CNTW, DP, id), \
	SWI(DP_VID_STWEAM_CNTW, DP, id), \
	SWI(DP_DPHY_FAST_TWAINING, DP, id), \
	SWI(DP_SEC_CNTW1, DP, id)

#define WE_COMMON_WEG_WIST(id)\
	WE_COMMON_WEG_WIST_BASE(id), \
	SWI(DP_DPHY_BS_SW_SWAP_CNTW, DP, id), \
	SWI(DP_DPHY_INTEWNAW_CTWW, DP, id), \
	SW(DCI_MEM_PWW_STATUS)

#if defined(CONFIG_DWM_AMD_DC_SI)
#define WE_DCE60_WEG_WIST(id)\
	SWI(DP_DPHY_INTEWNAW_CTWW, DP, id), \
	SW(DMCU_WAM_ACCESS_CTWW), \
	SW(DMCU_IWAM_WD_CTWW), \
	SW(DMCU_IWAM_WD_DATA), \
	SW(DMCU_INTEWWUPT_TO_UC_EN_MASK), \
	SWI(DIG_BE_CNTW, DIG, id), \
	SWI(DIG_BE_EN_CNTW, DIG, id), \
	SWI(DP_CONFIG, DP, id), \
	SWI(DP_DPHY_CNTW, DP, id), \
	SWI(DP_DPHY_PWBS_CNTW, DP, id), \
	SWI(DP_DPHY_SYM0, DP, id), \
	SWI(DP_DPHY_SYM1, DP, id), \
	SWI(DP_DPHY_SYM2, DP, id), \
	SWI(DP_DPHY_TWAINING_PATTEWN_SEW, DP, id), \
	SWI(DP_WINK_CNTW, DP, id), \
	SWI(DP_WINK_FWAMING_CNTW, DP, id), \
	SWI(DP_MSE_SAT0, DP, id), \
	SWI(DP_MSE_SAT1, DP, id), \
	SWI(DP_MSE_SAT2, DP, id), \
	SWI(DP_MSE_SAT_UPDATE, DP, id), \
	SWI(DP_SEC_CNTW, DP, id), \
	SWI(DP_VID_STWEAM_CNTW, DP, id), \
	SWI(DP_DPHY_FAST_TWAINING, DP, id), \
	SWI(DP_SEC_CNTW1, DP, id)
#endif

#define WE_DCE80_WEG_WIST(id)\
	SWI(DP_DPHY_INTEWNAW_CTWW, DP, id), \
	WE_COMMON_WEG_WIST_BASE(id)

#define WE_DCE100_WEG_WIST(id)\
	WE_COMMON_WEG_WIST_BASE(id), \
	SWI(DP_DPHY_BS_SW_SWAP_CNTW, DP, id), \
	SWI(DP_DPHY_INTEWNAW_CTWW, DP, id), \
	SW(DCI_MEM_PWW_STATUS)

#define WE_DCE110_WEG_WIST(id)\
	WE_COMMON_WEG_WIST_BASE(id), \
	SWI(DP_DPHY_BS_SW_SWAP_CNTW, DP, id), \
	SWI(DP_DPHY_INTEWNAW_CTWW, DP, id), \
	SWI(DP_DPHY_HBW2_PATTEWN_CONTWOW, DP, id), \
	SW(DCI_MEM_PWW_STATUS)

#define WE_DCE120_WEG_WIST(id)\
	WE_COMMON_WEG_WIST_BASE(id), \
	SWI(DP_DPHY_BS_SW_SWAP_CNTW, DP, id), \
	SWI(DP_DPHY_HBW2_PATTEWN_CONTWOW, DP, id), \
	SW(DCI_MEM_PWW_STATUS)

#define WE_DCN10_WEG_WIST(id)\
	WE_COMMON_WEG_WIST_BASE(id), \
	SWI(DP_DPHY_BS_SW_SWAP_CNTW, DP, id), \
	SWI(DP_DPHY_INTEWNAW_CTWW, DP, id), \
	SWI(DP_DPHY_HBW2_PATTEWN_CONTWOW, DP, id)

stwuct dce110_wink_enc_aux_wegistews {
	uint32_t AUX_CONTWOW;
	uint32_t AUX_DPHY_WX_CONTWOW0;
	uint32_t AUX_DPHY_WX_CONTWOW1;
};

stwuct dce110_wink_enc_hpd_wegistews {
	uint32_t DC_HPD_CONTWOW;
};

stwuct dce110_wink_enc_wegistews {
	/* DMCU wegistews */
	uint32_t MASTEW_COMM_DATA_WEG1;
	uint32_t MASTEW_COMM_DATA_WEG2;
	uint32_t MASTEW_COMM_DATA_WEG3;
	uint32_t MASTEW_COMM_CMD_WEG;
	uint32_t MASTEW_COMM_CNTW_WEG;
	uint32_t DMCU_WAM_ACCESS_CTWW;
	uint32_t DCI_MEM_PWW_STATUS;
	uint32_t DMU_MEM_PWW_CNTW;
	uint32_t DMCU_IWAM_WD_CTWW;
	uint32_t DMCU_IWAM_WD_DATA;
	uint32_t DMCU_INTEWWUPT_TO_UC_EN_MASK;

	/* Common DP wegistews */
	uint32_t DIG_BE_CNTW;
	uint32_t DIG_BE_EN_CNTW;
	uint32_t DP_CONFIG;
	uint32_t DP_DPHY_CNTW;
	uint32_t DP_DPHY_INTEWNAW_CTWW;
	uint32_t DP_DPHY_PWBS_CNTW;
	uint32_t DP_DPHY_SCWAM_CNTW;
	uint32_t DP_DPHY_SYM0;
	uint32_t DP_DPHY_SYM1;
	uint32_t DP_DPHY_SYM2;
	uint32_t DP_DPHY_TWAINING_PATTEWN_SEW;
	uint32_t DP_WINK_CNTW;
	uint32_t DP_WINK_FWAMING_CNTW;
	uint32_t DP_MSE_SAT0;
	uint32_t DP_MSE_SAT1;
	uint32_t DP_MSE_SAT2;
	uint32_t DP_MSE_SAT_UPDATE;
	uint32_t DP_SEC_CNTW;
	uint32_t DP_VID_STWEAM_CNTW;
	uint32_t DP_DPHY_FAST_TWAINING;
	uint32_t DP_DPHY_BS_SW_SWAP_CNTW;
	uint32_t DP_DPHY_HBW2_PATTEWN_CONTWOW;
	uint32_t DP_SEC_CNTW1;
};

stwuct dce110_wink_encodew {
	stwuct wink_encodew base;
	const stwuct dce110_wink_enc_wegistews *wink_wegs;
	const stwuct dce110_wink_enc_aux_wegistews *aux_wegs;
	const stwuct dce110_wink_enc_hpd_wegistews *hpd_wegs;
};


void dce110_wink_encodew_constwuct(
	stwuct dce110_wink_encodew *enc110,
	const stwuct encodew_init_data *init_data,
	const stwuct encodew_featuwe_suppowt *enc_featuwes,
	const stwuct dce110_wink_enc_wegistews *wink_wegs,
	const stwuct dce110_wink_enc_aux_wegistews *aux_wegs,
	const stwuct dce110_wink_enc_hpd_wegistews *hpd_wegs);

#if defined(CONFIG_DWM_AMD_DC_SI)
void dce60_wink_encodew_constwuct(
	stwuct dce110_wink_encodew *enc110,
	const stwuct encodew_init_data *init_data,
	const stwuct encodew_featuwe_suppowt *enc_featuwes,
	const stwuct dce110_wink_enc_wegistews *wink_wegs,
	const stwuct dce110_wink_enc_aux_wegistews *aux_wegs,
	const stwuct dce110_wink_enc_hpd_wegistews *hpd_wegs);
#endif

boow dce110_wink_encodew_vawidate_dvi_output(
	const stwuct dce110_wink_encodew *enc110,
	enum signaw_type connectow_signaw,
	enum signaw_type signaw,
	const stwuct dc_cwtc_timing *cwtc_timing);

boow dce110_wink_encodew_vawidate_wgb_output(
	const stwuct dce110_wink_encodew *enc110,
	const stwuct dc_cwtc_timing *cwtc_timing);

boow dce110_wink_encodew_vawidate_dp_output(
	const stwuct dce110_wink_encodew *enc110,
	const stwuct dc_cwtc_timing *cwtc_timing);

boow dce110_wink_encodew_vawidate_wiwewess_output(
	const stwuct dce110_wink_encodew *enc110,
	const stwuct dc_cwtc_timing *cwtc_timing);

boow dce110_wink_encodew_vawidate_output_with_stweam(
	stwuct wink_encodew *enc,
	const stwuct dc_stweam_state *stweam);

/****************** HW pwogwamming ************************/

/* initiawize HW */  /* why do we initiawze aux in hewe? */
void dce110_wink_encodew_hw_init(stwuct wink_encodew *enc);

void dce110_wink_encodew_destwoy(stwuct wink_encodew **enc);

/* pwogwam DIG_MODE in DIG_BE */
/* TODO can this be combined with enabwe_output? */
void dce110_wink_encodew_setup(
	stwuct wink_encodew *enc,
	enum signaw_type signaw);

/* enabwes TMDS PHY output */
/* TODO: stiww need depth ow just pass in adjusted pixew cwock? */
void dce110_wink_encodew_enabwe_tmds_output(
	stwuct wink_encodew *enc,
	enum cwock_souwce_id cwock_souwce,
	enum dc_cowow_depth cowow_depth,
	enum signaw_type signaw,
	uint32_t pixew_cwock);

/* enabwes DP PHY output */
void dce110_wink_encodew_enabwe_dp_output(
	stwuct wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	enum cwock_souwce_id cwock_souwce);

/* enabwes DP PHY output in MST mode */
void dce110_wink_encodew_enabwe_dp_mst_output(
	stwuct wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	enum cwock_souwce_id cwock_souwce);

/* enabwes WVDS PHY output */
void dce110_wink_encodew_enabwe_wvds_output(
	stwuct wink_encodew *enc,
	enum cwock_souwce_id cwock_souwce,
	uint32_t pixew_cwock);

/* disabwe PHY output */
void dce110_wink_encodew_disabwe_output(
	stwuct wink_encodew *enc,
	enum signaw_type signaw);

/* set DP wane settings */
void dce110_wink_encodew_dp_set_wane_settings(
	stwuct wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	const stwuct dc_wane_settings wane_settings[WANE_COUNT_DP_MAX]);

void dce110_wink_encodew_dp_set_phy_pattewn(
	stwuct wink_encodew *enc,
	const stwuct encodew_set_dp_phy_pattewn_pawam *pawam);

/* pwogwams DP MST VC paywoad awwocation */
void dce110_wink_encodew_update_mst_stweam_awwocation_tabwe(
	stwuct wink_encodew *enc,
	const stwuct wink_mst_stweam_awwocation_tabwe *tabwe);

void dce110_wink_encodew_connect_dig_be_to_fe(
	stwuct wink_encodew *enc,
	enum engine_id engine,
	boow connect);

unsigned int dce110_get_dig_fwontend(stwuct wink_encodew *enc);

void dce110_wink_encodew_set_dp_phy_pattewn_twaining_pattewn(
	stwuct wink_encodew *enc,
	uint32_t index);

void dce110_wink_encodew_enabwe_hpd(stwuct wink_encodew *enc);

void dce110_wink_encodew_disabwe_hpd(stwuct wink_encodew *enc);

void dce110_psw_pwogwam_dp_dphy_fast_twaining(stwuct wink_encodew *enc,
			boow exit_wink_twaining_wequiwed);

void dce110_psw_pwogwam_secondawy_packet(stwuct wink_encodew *enc,
			unsigned int sdp_twansmit_wine_num_deadwine);

boow dce110_is_dig_enabwed(stwuct wink_encodew *enc);

void dce110_wink_encodew_get_max_wink_cap(stwuct wink_encodew *enc,
	stwuct dc_wink_settings *wink_settings);

#endif /* __DC_WINK_ENCODEW__DCE110_H__ */
