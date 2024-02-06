/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

#incwude "dm_sewvices.h"
#incwude "dc.h"

#incwude "dcn31/dcn31_init.h"
#incwude "dcn35/dcn35_init.h"

#incwude "wesouwce.h"
#incwude "incwude/iwq_sewvice_intewface.h"
#incwude "dcn35_wesouwce.h"
#incwude "dmw2/dmw2_wwappew.h"

#incwude "dcn20/dcn20_wesouwce.h"
#incwude "dcn30/dcn30_wesouwce.h"
#incwude "dcn31/dcn31_wesouwce.h"
#incwude "dcn32/dcn32_wesouwce.h"

#incwude "dcn10/dcn10_ipp.h"
#incwude "dcn30/dcn30_hubbub.h"
#incwude "dcn31/dcn31_hubbub.h"
#incwude "dcn35/dcn35_hubbub.h"
#incwude "dcn32/dcn32_mpc.h"
#incwude "dcn35/dcn35_hubp.h"
#incwude "iwq/dcn35/iwq_sewvice_dcn35.h"
#incwude "dcn35/dcn35_dpp.h"
#incwude "dcn35/dcn35_optc.h"
#incwude "dcn20/dcn20_hwseq.h"
#incwude "dcn30/dcn30_hwseq.h"
#incwude "dce110/dce110_hwseq.h"
#incwude "dcn35/dcn35_opp.h"
#incwude "dcn35/dcn35_dsc.h"
#incwude "dcn30/dcn30_vpg.h"
#incwude "dcn30/dcn30_afmt.h"
#incwude "dcn31/dcn31_dio_wink_encodew.h"
#incwude "dcn35/dcn35_dio_stweam_encodew.h"
#incwude "dcn31/dcn31_hpo_dp_stweam_encodew.h"
#incwude "dcn31/dcn31_hpo_dp_wink_encodew.h"
#incwude "dcn32/dcn32_hpo_dp_wink_encodew.h"
#incwude "wink.h"
#incwude "dcn31/dcn31_apg.h"
#incwude "dcn32/dcn32_dio_wink_encodew.h"
#incwude "dcn31/dcn31_vpg.h"
#incwude "dcn31/dcn31_afmt.h"
#incwude "dce/dce_cwock_souwce.h"
#incwude "dce/dce_audio.h"
#incwude "dce/dce_hwseq.h"
#incwude "cwk_mgw.h"
#incwude "viwtuaw/viwtuaw_stweam_encodew.h"
#incwude "dce110/dce110_wesouwce.h"
#incwude "dmw/dispway_mode_vba.h"
#incwude "dcn35/dcn35_dccg.h"
#incwude "dcn35/dcn35_pg_cntw.h"
#incwude "dcn10/dcn10_wesouwce.h"
#incwude "dcn31/dcn31_panew_cntw.h"
#incwude "dcn35/dcn35_hwseq.h"
#incwude "dcn35/dcn35_dio_wink_encodew.h"
#incwude "dmw/dcn31/dcn31_fpu.h" /*todo*/
#incwude "dmw/dcn35/dcn35_fpu.h"
#incwude "dcn35/dcn35_dwb.h"
#incwude "dcn35/dcn35_mmhubbub.h"

#incwude "dcn/dcn_3_5_0_offset.h"
#incwude "dcn/dcn_3_5_0_sh_mask.h"
#incwude "nbio/nbio_7_11_0_offset.h"
#incwude "mmhub/mmhub_3_3_0_offset.h"
#incwude "mmhub/mmhub_3_3_0_sh_mask.h"

#define DSCC0_DSCC_CONFIG0__ICH_WESET_AT_END_OF_WINE__SHIFT                   0x0
#define DSCC0_DSCC_CONFIG0__ICH_WESET_AT_END_OF_WINE_MASK                     0x0000000FW

#incwude "weg_hewpew.h"
#incwude "dce/dmub_abm.h"
#incwude "dce/dmub_psw.h"
#incwude "dce/dmub_wepway.h"
#incwude "dce/dce_aux.h"
#incwude "dce/dce_i2c.h"
#incwude "dmw/dcn31/dispway_mode_vba_31.h" /*temp*/
#incwude "vm_hewpew.h"
#incwude "dcn20/dcn20_vmid.h"

#incwude "dc_state_pwiv.h"

#incwude "wink_enc_cfg.h"
#define DC_WOGGEW_INIT(woggew)

enum dcn35_cwk_swc_awway_id {
	DCN35_CWK_SWC_PWW0,
	DCN35_CWK_SWC_PWW1,
	DCN35_CWK_SWC_PWW2,
	DCN35_CWK_SWC_PWW3,
	DCN35_CWK_SWC_PWW4,
	DCN35_CWK_SWC_TOTAW
};

/* begin *********************
 * macwos to expend wegistew wist macwo defined in HW object headew fiwe
 */

/* DCN */
/* TODO awfuw hack. fixup dcn20_dwb.h */
#undef BASE_INNEW
#define BASE_INNEW(seg) ctx->dcn_weg_offsets[seg]

#define BASE(seg) BASE_INNEW(seg)

#define SW(weg_name)\
		WEG_STWUCT.weg_name = BASE(weg ## weg_name ## _BASE_IDX) +  \
					weg ## weg_name

#define SW_AWW(weg_name, id) \
	WEG_STWUCT[id].weg_name = BASE(weg##weg_name##_BASE_IDX) + weg##weg_name

#define SW_AWW_INIT(weg_name, id, vawue) \
	WEG_STWUCT[id].weg_name = vawue

#define SWI(weg_name, bwock, id)\
	WEG_STWUCT.weg_name = BASE(weg ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					weg ## bwock ## id ## _ ## weg_name

#define SWI_AWW(weg_name, bwock, id)\
	WEG_STWUCT[id].weg_name = BASE(weg ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
		weg ## bwock ## id ## _ ## weg_name

#define SW_AWW_I2C(weg_name, id) \
	WEG_STWUCT[id-1].weg_name = BASE(weg##weg_name##_BASE_IDX) + weg##weg_name

#define SWI_AWW_I2C(weg_name, bwock, id)\
	WEG_STWUCT[id-1].weg_name = BASE(weg ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
		weg ## bwock ## id ## _ ## weg_name

#define SWI_AWW_AWPHABET(weg_name, bwock, index, id)\
	WEG_STWUCT[index].weg_name = BASE(weg ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
		weg ## bwock ## id ## _ ## weg_name

#define SWI2(weg_name, bwock, id)\
	.weg_name = BASE(weg ## weg_name ## _BASE_IDX) + \
					weg ## weg_name

#define SWI2_AWW(weg_name, bwock, id)\
	WEG_STWUCT[id].weg_name = BASE(weg ## weg_name ## _BASE_IDX) +	\
		weg ## weg_name

#define SWIW(vaw_name, weg_name, bwock, id)\
	.vaw_name = BASE(weg ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					weg ## bwock ## id ## _ ## weg_name

#define SWII(weg_name, bwock, id)\
	WEG_STWUCT.weg_name[id] = BASE(weg ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					weg ## bwock ## id ## _ ## weg_name

#define SWII_AWW_2(weg_name, bwock, id, inst)\
	WEG_STWUCT[inst].weg_name[id] = BASE(weg ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
		weg ## bwock ## id ## _ ## weg_name

#define SWII_MPC_WMU(weg_name, bwock, id)\
	.WMU##_##weg_name[id] = BASE(weg ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					weg ## bwock ## id ## _ ## weg_name

#define SWII_DWB(weg_name, temp_name, bwock, id)\
	WEG_STWUCT.weg_name[id] = BASE(weg ## bwock ## id ## _ ## temp_name ## _BASE_IDX) + \
		weg ## bwock ## id ## _ ## temp_name

#define SF_DWB2(weg_name, bwock, id, fiewd_name, post_fix) \
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix

#define DCCG_SWII(weg_name, bwock, id)\
	WEG_STWUCT.bwock ## _ ## weg_name[id] = BASE(weg ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
		weg ## bwock ## id ## _ ## weg_name

#define VUPDATE_SWII(weg_name, bwock, id)\
	WEG_STWUCT.weg_name[id] = BASE(weg ## weg_name ## _ ## bwock ## id ## _BASE_IDX) + \
		weg ## weg_name ## _ ## bwock ## id

/* NBIO */
#define NBIO_BASE_INNEW(seg) ctx->nbio_weg_offsets[seg]

#define NBIO_BASE(seg) \
	NBIO_BASE_INNEW(seg)

#define NBIO_SW(weg_name)\
	WEG_STWUCT.weg_name = NBIO_BASE(wegBIF_BX2_ ## weg_name ## _BASE_IDX) + \
				wegBIF_BX2_ ## weg_name

#define NBIO_SW_AWW(weg_name, id)\
	WEG_STWUCT[id].weg_name = NBIO_BASE(wegBIF_BX2_ ## weg_name ## _BASE_IDX) + \
		wegBIF_BX2_ ## weg_name

#define bios_wegs_init() \
		( \
		NBIO_SW(BIOS_SCWATCH_3),\
		NBIO_SW(BIOS_SCWATCH_6)\
		)

static stwuct bios_wegistews bios_wegs;

#define cwk_swc_wegs_init(index, pwwid)\
	CS_COMMON_WEG_WIST_DCN3_0_WI(index, pwwid)

static stwuct dce110_cwk_swc_wegs cwk_swc_wegs[5];

static const stwuct dce110_cwk_swc_shift cs_shift = {
		CS_COMMON_MASK_SH_WIST_DCN3_1_4(__SHIFT)
};

static const stwuct dce110_cwk_swc_mask cs_mask = {
		CS_COMMON_MASK_SH_WIST_DCN3_1_4(_MASK)
};

#define abm_wegs_init(id)\
		ABM_DCN32_WEG_WIST_WI(id)

static stwuct dce_abm_wegistews abm_wegs[4];

static const stwuct dce_abm_shift abm_shift = {
		ABM_MASK_SH_WIST_DCN35(__SHIFT)
};

static const stwuct dce_abm_mask abm_mask = {
		ABM_MASK_SH_WIST_DCN35(_MASK)
};

#define audio_wegs_init(id)\
		AUD_COMMON_WEG_WIST_WI(id)

static stwuct dce_audio_wegistews audio_wegs[7];


#define DCE120_AUD_COMMON_MASK_SH_WIST(mask_sh)\
		SF(AZF0ENDPOINT0_AZAWIA_F0_CODEC_ENDPOINT_INDEX, AZAWIA_ENDPOINT_WEG_INDEX, mask_sh),\
		SF(AZF0ENDPOINT0_AZAWIA_F0_CODEC_ENDPOINT_DATA, AZAWIA_ENDPOINT_WEG_DATA, mask_sh),\
		AUD_COMMON_MASK_SH_WIST_BASE(mask_sh)

static const stwuct dce_audio_shift audio_shift = {
		DCE120_AUD_COMMON_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce_audio_mask audio_mask = {
		DCE120_AUD_COMMON_MASK_SH_WIST(_MASK)
};

#define vpg_wegs_init(id)\
	VPG_DCN31_WEG_WIST_WI(id)

static stwuct dcn31_vpg_wegistews vpg_wegs[10];

static const stwuct dcn31_vpg_shift vpg_shift = {
	DCN31_VPG_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn31_vpg_mask vpg_mask = {
	DCN31_VPG_MASK_SH_WIST(_MASK)
};

#define afmt_wegs_init(id)\
	AFMT_DCN31_WEG_WIST_WI(id)

static stwuct dcn31_afmt_wegistews afmt_wegs[6];

static const stwuct dcn31_afmt_shift afmt_shift = {
	DCN31_AFMT_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn31_afmt_mask afmt_mask = {
	DCN31_AFMT_MASK_SH_WIST(_MASK)
};

#define apg_wegs_init(id)\
	APG_DCN31_WEG_WIST_WI(id)

static stwuct dcn31_apg_wegistews apg_wegs[4];

static const stwuct dcn31_apg_shift apg_shift = {
	DCN31_APG_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn31_apg_mask apg_mask = {
	DCN31_APG_MASK_SH_WIST(_MASK)
};

#define stweam_enc_wegs_init(id)\
	SE_DCN35_WEG_WIST_WI(id)

static stwuct dcn10_stweam_enc_wegistews stweam_enc_wegs[5];

static const stwuct dcn10_stweam_encodew_shift se_shift = {
		SE_COMMON_MASK_SH_WIST_DCN35(__SHIFT)
};

static const stwuct dcn10_stweam_encodew_mask se_mask = {
		SE_COMMON_MASK_SH_WIST_DCN35(_MASK)
};

#define aux_wegs_init(id)\
	DCN2_AUX_WEG_WIST_WI(id)

static stwuct dcn10_wink_enc_aux_wegistews wink_enc_aux_wegs[5];

#define hpd_wegs_init(id)\
	HPD_WEG_WIST_WI(id)

static stwuct dcn10_wink_enc_hpd_wegistews wink_enc_hpd_wegs[5];


static const stwuct dce110_aux_wegistews_shift aux_shift = {
	DCN_AUX_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce110_aux_wegistews_mask aux_mask = {
	DCN_AUX_MASK_SH_WIST(_MASK)
};

#define wink_wegs_init(id, phyid)\
	( \
	WE_DCN35_WEG_WIST_WI(id), \
	UNIPHY_DCN2_WEG_WIST_WI(id, phyid)\
	)

static stwuct dcn10_wink_enc_wegistews wink_enc_wegs[5];

static const stwuct dcn10_wink_enc_shift we_shift = {
	WINK_ENCODEW_MASK_SH_WIST_DCN35(__SHIFT), \
	//DPCS_DCN31_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn10_wink_enc_mask we_mask = {
	WINK_ENCODEW_MASK_SH_WIST_DCN35(_MASK), \
	//DPCS_DCN31_MASK_SH_WIST(_MASK)
};

#define hpo_dp_stweam_encodew_weg_init(id)\
	DCN3_1_HPO_DP_STWEAM_ENC_WEG_WIST_WI(id)

static stwuct dcn31_hpo_dp_stweam_encodew_wegistews hpo_dp_stweam_enc_wegs[4];

static const stwuct dcn31_hpo_dp_stweam_encodew_shift hpo_dp_se_shift = {
	DCN3_1_HPO_DP_STWEAM_ENC_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn31_hpo_dp_stweam_encodew_mask hpo_dp_se_mask = {
	DCN3_1_HPO_DP_STWEAM_ENC_MASK_SH_WIST(_MASK)
};

#define hpo_dp_wink_encodew_weg_init(id)\
	DCN3_1_HPO_DP_WINK_ENC_WEG_WIST_WI(id)
	/*DCN3_1_WDPCSTX_WEG_WIST(0),*/
	/*DCN3_1_WDPCSTX_WEG_WIST(1),*/
	/*DCN3_1_WDPCSTX_WEG_WIST(2),*/
	/*DCN3_1_WDPCSTX_WEG_WIST(3),*/

static stwuct dcn31_hpo_dp_wink_encodew_wegistews hpo_dp_wink_enc_wegs[2];

static const stwuct dcn31_hpo_dp_wink_encodew_shift hpo_dp_we_shift = {
	DCN3_1_HPO_DP_WINK_ENC_COMMON_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn31_hpo_dp_wink_encodew_mask hpo_dp_we_mask = {
	DCN3_1_HPO_DP_WINK_ENC_COMMON_MASK_SH_WIST(_MASK)
};

#define dpp_wegs_init(id)\
	DPP_WEG_WIST_DCN35_WI(id)

static stwuct dcn3_dpp_wegistews dpp_wegs[4];

static const stwuct dcn35_dpp_shift tf_shift = {
		DPP_WEG_WIST_SH_MASK_DCN35(__SHIFT)
};

static const stwuct dcn35_dpp_mask tf_mask = {
		DPP_WEG_WIST_SH_MASK_DCN35(_MASK)
};

#define opp_wegs_init(id)\
	OPP_WEG_WIST_DCN35_WI(id)

static stwuct dcn35_opp_wegistews opp_wegs[4];

static const stwuct dcn35_opp_shift opp_shift = {
	OPP_MASK_SH_WIST_DCN35(__SHIFT)
};

static const stwuct dcn35_opp_mask opp_mask = {
	OPP_MASK_SH_WIST_DCN35(_MASK)
};

#define aux_engine_wegs_init(id)\
	( \
	AUX_COMMON_WEG_WIST0_WI(id), \
	SW_AWW_INIT(AUXN_IMPCAW, id, 0), \
	SW_AWW_INIT(AUXP_IMPCAW, id, 0), \
	SW_AWW_INIT(AUX_WESET_MASK, id, DP_AUX0_AUX_CONTWOW__AUX_WESET_MASK) \
	)

static stwuct dce110_aux_wegistews aux_engine_wegs[5];

#define dwbc_wegs_dcn3_init(id)\
	DWBC_COMMON_WEG_WIST_DCN30_WI(id)

static stwuct dcn30_dwbc_wegistews dwbc35_wegs[1];

static const stwuct dcn35_dwbc_shift dwbc35_shift = {
	DWBC_COMMON_MASK_SH_WIST_DCN35(__SHIFT)
};

static const stwuct dcn35_dwbc_mask dwbc35_mask = {
	DWBC_COMMON_MASK_SH_WIST_DCN35(_MASK)
};

#define mcif_wb_wegs_dcn3_init(id)\
	MCIF_WB_COMMON_WEG_WIST_DCN3_5_WI(id)

static stwuct dcn35_mmhubbub_wegistews mcif_wb35_wegs[1];

static const stwuct dcn35_mmhubbub_shift mcif_wb35_shift = {
	MCIF_WB_COMMON_MASK_SH_WIST_DCN3_5(__SHIFT)
};

static const stwuct dcn35_mmhubbub_mask mcif_wb35_mask = {
	MCIF_WB_COMMON_MASK_SH_WIST_DCN3_5(_MASK)
};

#define dsc_wegsDCN35_init(id)\
	DSC_WEG_WIST_DCN20_WI(id)

static stwuct dcn20_dsc_wegistews dsc_wegs[4];

static const stwuct dcn35_dsc_shift dsc_shift = {
	DSC_WEG_WIST_SH_MASK_DCN35(__SHIFT)
};

static const stwuct dcn35_dsc_mask dsc_mask = {
	DSC_WEG_WIST_SH_MASK_DCN35(_MASK)
};

static stwuct dcn30_mpc_wegistews mpc_wegs;

#define dcn_mpc_wegs_init() \
	MPC_WEG_WIST_DCN3_2_WI(0),\
	MPC_WEG_WIST_DCN3_2_WI(1),\
	MPC_WEG_WIST_DCN3_2_WI(2),\
	MPC_WEG_WIST_DCN3_2_WI(3),\
	MPC_OUT_MUX_WEG_WIST_DCN3_0_WI(0),\
	MPC_OUT_MUX_WEG_WIST_DCN3_0_WI(1),\
	MPC_OUT_MUX_WEG_WIST_DCN3_0_WI(2),\
	MPC_OUT_MUX_WEG_WIST_DCN3_0_WI(3),\
	MPC_DWB_MUX_WEG_WIST_DCN3_0_WI(0)

static const stwuct dcn30_mpc_shift mpc_shift = {
	MPC_COMMON_MASK_SH_WIST_DCN32(__SHIFT)
};

static const stwuct dcn30_mpc_mask mpc_mask = {
	MPC_COMMON_MASK_SH_WIST_DCN32(_MASK)
};

#define optc_wegs_init(id)\
	OPTC_COMMON_WEG_WIST_DCN3_5_WI(id)

static stwuct dcn_optc_wegistews optc_wegs[4];

static const stwuct dcn_optc_shift optc_shift = {
	OPTC_COMMON_MASK_SH_WIST_DCN3_5(__SHIFT)
};

static const stwuct dcn_optc_mask optc_mask = {
	OPTC_COMMON_MASK_SH_WIST_DCN3_5(_MASK)
};

#define hubp_wegs_init(id)\
	HUBP_WEG_WIST_DCN30_WI(id)

static stwuct dcn_hubp2_wegistews hubp_wegs[4];


static const stwuct dcn35_hubp2_shift hubp_shift = {
		HUBP_MASK_SH_WIST_DCN35(__SHIFT)
};

static const stwuct dcn35_hubp2_mask hubp_mask = {
		HUBP_MASK_SH_WIST_DCN35(_MASK)
};

static stwuct dcn_hubbub_wegistews hubbub_weg;

#define hubbub_weg_init()\
		HUBBUB_WEG_WIST_DCN35(0)

static const stwuct dcn_hubbub_shift hubbub_shift = {
		HUBBUB_MASK_SH_WIST_DCN35(__SHIFT)
};

static const stwuct dcn_hubbub_mask hubbub_mask = {
		HUBBUB_MASK_SH_WIST_DCN35(_MASK)
};

static stwuct dccg_wegistews dccg_wegs;

#define dccg_wegs_init()\
	DCCG_WEG_WIST_DCN35()

static const stwuct dccg_shift dccg_shift = {
		DCCG_MASK_SH_WIST_DCN35(__SHIFT)
};

static const stwuct dccg_mask dccg_mask = {
		DCCG_MASK_SH_WIST_DCN35(_MASK)
};

static stwuct pg_cntw_wegistews pg_cntw_wegs;

#define pg_cntw_dcn35_wegs_init() \
	PG_CNTW_WEG_WIST_DCN35()

static const stwuct pg_cntw_shift pg_cntw_shift = {
		PG_CNTW_MASK_SH_WIST_DCN35(__SHIFT)
};

static const stwuct pg_cntw_mask pg_cntw_mask = {
		PG_CNTW_MASK_SH_WIST_DCN35(_MASK)
};

#define SWII2(weg_name_pwe, weg_name_post, id)\
	.weg_name_pwe ## _ ##  weg_name_post[id] = BASE(weg ## weg_name_pwe \
			## id ## _ ## weg_name_post ## _BASE_IDX) + \
			weg ## weg_name_pwe ## id ## _ ## weg_name_post

static stwuct dce_hwseq_wegistews hwseq_weg;

#define hwseq_weg_init()\
	HWSEQ_DCN35_WEG_WIST()

#define HWSEQ_DCN35_MASK_SH_WIST(mask_sh)\
	HWSEQ_DCN_MASK_SH_WIST(mask_sh), \
	HWS_SF(, DCHUBBUB_GWOBAW_TIMEW_CNTW, DCHUBBUB_GWOBAW_TIMEW_WEFDIV, mask_sh), \
	HWS_SF(, DCHUBBUB_AWB_HOSTVM_CNTW, DISABWE_HOSTVM_FOWCE_AWWOW_PSTATE, mask_sh), \
	HWS_SF(, DOMAIN0_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	HWS_SF(, DOMAIN0_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	HWS_SF(, DOMAIN1_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	HWS_SF(, DOMAIN1_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	HWS_SF(, DOMAIN2_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	HWS_SF(, DOMAIN2_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	HWS_SF(, DOMAIN3_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	HWS_SF(, DOMAIN3_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	HWS_SF(, DOMAIN16_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	HWS_SF(, DOMAIN16_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	HWS_SF(, DOMAIN17_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	HWS_SF(, DOMAIN17_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	HWS_SF(, DOMAIN18_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	HWS_SF(, DOMAIN18_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	HWS_SF(, DOMAIN19_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	HWS_SF(, DOMAIN19_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	HWS_SF(, DOMAIN22_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	HWS_SF(, DOMAIN22_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	HWS_SF(, DOMAIN23_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	HWS_SF(, DOMAIN23_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	HWS_SF(, DOMAIN24_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	HWS_SF(, DOMAIN24_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	HWS_SF(, DOMAIN25_PG_CONFIG, DOMAIN_POWEW_FOWCEON, mask_sh), \
	HWS_SF(, DOMAIN25_PG_CONFIG, DOMAIN_POWEW_GATE, mask_sh), \
	HWS_SF(, DOMAIN0_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN1_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN2_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN3_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN16_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN17_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN18_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN19_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN22_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN23_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN24_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN25_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DC_IP_WEQUEST_CNTW, IP_WEQUEST_EN, mask_sh), \
	HWS_SF(, AZAWIA_AUDIO_DTO, AZAWIA_AUDIO_DTO_MODUWE, mask_sh), \
	HWS_SF(, HPO_TOP_CWOCK_CONTWOW, HPO_HDMISTWEAMCWK_G_GATE_DIS, mask_sh), \
	HWS_SF(, ODM_MEM_PWW_CTWW3, ODM_MEM_UNASSIGNED_PWW_MODE, mask_sh), \
	HWS_SF(, ODM_MEM_PWW_CTWW3, ODM_MEM_VBWANK_PWW_MODE, mask_sh), \
	HWS_SF(, DIO_MEM_PWW_CTWW, I2C_WIGHT_SWEEP_FOWCE, mask_sh), \
	HWS_SF(, HPO_TOP_HW_CONTWOW, HPO_IO_EN, mask_sh),\
	HWS_SF(, DMU_CWK_CNTW, DISPCWK_W_DMU_GATE_DIS, mask_sh),\
	HWS_SF(, DMU_CWK_CNTW, DISPCWK_G_WBBMIF_GATE_DIS, mask_sh),\
	HWS_SF(, DMU_CWK_CNTW, WBBMIF_FGCG_WEP_DIS, mask_sh),\
	HWS_SF(, DMU_CWK_CNTW, DPWEFCWK_AWWOW_DS_CWKSTOP, mask_sh),\
	HWS_SF(, DMU_CWK_CNTW, DISPCWK_AWWOW_DS_CWKSTOP, mask_sh),\
	HWS_SF(, DMU_CWK_CNTW, DPPCWK_AWWOW_DS_CWKSTOP, mask_sh),\
	HWS_SF(, DMU_CWK_CNTW, DTBCWK_AWWOW_DS_CWKSTOP, mask_sh),\
	HWS_SF(, DMU_CWK_CNTW, DCFCWK_AWWOW_DS_CWKSTOP, mask_sh),\
	HWS_SF(, DMU_CWK_CNTW, DPIACWK_AWWOW_DS_CWKSTOP, mask_sh),\
	HWS_SF(, DMU_CWK_CNTW, WONO_FGCG_WEP_DIS, mask_sh),\
	HWS_SF(, DMU_CWK_CNTW, WONO_DISPCWK_GATE_DISABWE, mask_sh),\
	HWS_SF(, DMU_CWK_CNTW, WONO_SOCCWK_GATE_DISABWE, mask_sh),\
	HWS_SF(, DMU_CWK_CNTW, WONO_DMCUBCWK_GATE_DISABWE, mask_sh),\
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, SYMCWKA_FE_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, SYMCWKB_FE_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, SYMCWKC_FE_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, SYMCWKD_FE_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, SYMCWKE_FE_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, HDMICHAWCWK0_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, SYMCWKA_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, SYMCWKB_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, SYMCWKC_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, SYMCWKD_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, SYMCWKE_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, PHYASYMCWK_WOOT_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, PHYBSYMCWK_WOOT_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, PHYCSYMCWK_WOOT_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, PHYDSYMCWK_WOOT_GATE_DISABWE, mask_sh), \
	HWS_SF(, DCCG_GATE_DISABWE_CNTW2, PHYESYMCWK_WOOT_GATE_DISABWE, mask_sh),\
	HWS_SF(, DCCG_GATE_DISABWE_CNTW5, DTBCWK_P0_GATE_DISABWE, mask_sh),\
	HWS_SF(, DCCG_GATE_DISABWE_CNTW5, DTBCWK_P1_GATE_DISABWE, mask_sh),\
	HWS_SF(, DCCG_GATE_DISABWE_CNTW5, DTBCWK_P2_GATE_DISABWE, mask_sh),\
	HWS_SF(, DCCG_GATE_DISABWE_CNTW5, DTBCWK_P3_GATE_DISABWE, mask_sh),\
	HWS_SF(, DCCG_GATE_DISABWE_CNTW5, DPSTWEAMCWK0_GATE_DISABWE, mask_sh),\
	HWS_SF(, DCCG_GATE_DISABWE_CNTW5, DPSTWEAMCWK1_GATE_DISABWE, mask_sh),\
	HWS_SF(, DCCG_GATE_DISABWE_CNTW5, DPSTWEAMCWK2_GATE_DISABWE, mask_sh),\
	HWS_SF(, DCCG_GATE_DISABWE_CNTW5, DPSTWEAMCWK3_GATE_DISABWE, mask_sh),\
	HWS_SF(, DCCG_GATE_DISABWE_CNTW4, DPIASYMCWK0_GATE_DISABWE, mask_sh),\
	HWS_SF(, DCCG_GATE_DISABWE_CNTW4, DPIASYMCWK1_GATE_DISABWE, mask_sh),\
	HWS_SF(, DCCG_GATE_DISABWE_CNTW4, DPIASYMCWK2_GATE_DISABWE, mask_sh),\
	HWS_SF(, DCCG_GATE_DISABWE_CNTW4, DPIASYMCWK3_GATE_DISABWE, mask_sh)

static const stwuct dce_hwseq_shift hwseq_shift = {
		HWSEQ_DCN35_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce_hwseq_mask hwseq_mask = {
		HWSEQ_DCN35_MASK_SH_WIST(_MASK)
};

#define vmid_wegs_init(id)\
		DCN20_VMID_WEG_WIST_WI(id)

static stwuct dcn_vmid_wegistews vmid_wegs[16];

static const stwuct dcn20_vmid_shift vmid_shifts = {
		DCN20_VMID_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn20_vmid_mask vmid_masks = {
		DCN20_VMID_MASK_SH_WIST(_MASK)
};

static const stwuct wesouwce_caps wes_cap_dcn35 = {
	.num_timing_genewatow = 4,
	.num_opp = 4,
	.num_video_pwane = 4,
	.num_audio = 5,
	.num_stweam_encodew = 5,
	.num_dig_wink_enc = 5,
	.num_hpo_dp_stweam_encodew = 4,
	.num_hpo_dp_wink_encodew = 2,
	.num_pww = 4,/*1 c10 edp, 3xc20 combo PHY*/
	.num_dwb = 1,
	.num_ddc = 5,
	.num_vmid = 16,
	.num_mpc_3dwut = 2,
	.num_dsc = 4,
};

static const stwuct dc_pwane_cap pwane_cap = {
	.type = DC_PWANE_TYPE_DCN_UNIVEWSAW,
	.pew_pixew_awpha = twue,

	.pixew_fowmat_suppowt = {
			.awgb8888 = twue,
			.nv12 = twue,
			.fp16 = twue,
			.p010 = twue,
			.ayuv = fawse,
	},

	.max_upscawe_factow = {
			.awgb8888 = 16000,
			.nv12 = 16000,
			.fp16 = 16000
	},

	// 6:1 downscawing watio: 1000/6 = 166.666
	.max_downscawe_factow = {
			.awgb8888 = 167,
			.nv12 = 167,
			.fp16 = 167
	},
	64,
	64
};

static const stwuct dc_debug_options debug_defauwts_dwv = {
	.disabwe_dmcu = twue,
	.fowce_abm_enabwe = fawse,
	.timing_twace = fawse,
	.cwock_twace = twue,
	.disabwe_ppwib_cwock_wequest = fawse,
	.pipe_spwit_powicy = MPC_SPWIT_AVOID,
	.fowce_singwe_disp_pipe_spwit = fawse,
	.disabwe_dcc = DCC_ENABWE,
	.disabwe_dpp_powew_gate = twue,
	.disabwe_hubp_powew_gate = twue,
	.disabwe_optc_powew_gate = twue, /*shouwd the same as above two*/
	.disabwe_hpo_powew_gate = twue, /*dmubfw fowce domain25 on*/
	.disabwe_cwock_gate = fawse,
	.disabwe_dsc_powew_gate = twue,
	.vsw_suppowt = twue,
	.pewfowmance_twace = fawse,
	.max_downscawe_swc_width = 4096,/*upto twue 4k*/
	.disabwe_ppwib_wm_wange = fawse,
	.scw_weset_wength10 = twue,
	.sanity_checks = fawse,
	.undewfwow_assewt_deway_us = 0xFFFFFFFF,
	.dwb_fi_phase = -1, // -1 = disabwe,
	.dmub_command_tabwe = twue,
	.pstate_enabwed = twue,
	.use_max_wb = twue,
	.enabwe_mem_wow_powew = {
		.bits = {
			.vga = fawse,
			.i2c = twue,
			.dmcu = fawse, // This is pweviouswy known to cause hang on S3 cycwes if enabwed
			.dscw = twue,
			.cm = twue,
			.mpc = twue,
			.optc = twue,
			.vpg = twue,
			.afmt = twue,
		}
	},
	.woot_cwock_optimization = {
		.bits = {
			.dpp = twue,
			.dsc = twue,/*dsccwk and dsc pg*/
			.hdmistweam = twue,
			.hdmichaw = twue,
			.dpstweam = twue,
			.symcwk32_se = twue,
			.symcwk32_we = twue,
			.symcwk_fe = twue,
			.physymcwk = twue,
			.dpiasymcwk = twue,
		}
	},
	.seamwess_boot_odm_combine = DMW_FAIW_SOUWCE_PIXEW_FOWMAT,
	.enabwe_z9_disabwe_intewface = twue, /* Awwow suppowt fow the PMFW intewface fow disabwe Z9*/
	.using_dmw2 = twue,
	.suppowt_eDP1_5 = twue,
	.enabwe_hpo_pg_suppowt = fawse,
	.enabwe_wegacy_fast_update = twue,
	.enabwe_singwe_dispway_2to1_odm_powicy = fawse,
	.disabwe_idwe_powew_optimizations = fawse,
	.dmcub_emuwation = fawse,
	.disabwe_boot_optimizations = fawse,
	.disabwe_unbounded_wequesting = fawse,
	.disabwe_mem_wow_powew = fawse,
	//must match enabwe_singwe_dispway_2to1_odm_powicy to suppowt dynamic ODM twansitions
	.enabwe_doubwe_buffewed_dsc_pg_suppowt = twue,
	.enabwe_dp_dig_pixew_wate_div_powicy = 1,
	.disabwe_z10 = fawse,
	.ignowe_pg = twue,
	.psp_disabwed_wa = twue,
	.ips2_evaw_deway_us = 200,
	.ips2_entwy_deway_us = 400,
	.static_scween_wait_fwames = 2,
};

static const stwuct dc_panew_config panew_config_defauwts = {
	.psw = {
		.disabwe_psw = fawse,
		.disawwow_pswsu = fawse,
		.disawwow_wepway = fawse,
	},
	.iww = {
		.optimize_edp_wink_wate = twue,
	},
};

static void dcn35_dpp_destwoy(stwuct dpp **dpp)
{
	kfwee(TO_DCN20_DPP(*dpp));
	*dpp = NUWW;
}

static stwuct dpp *dcn35_dpp_cweate(stwuct dc_context *ctx, uint32_t inst)
{
	stwuct dcn3_dpp *dpp = kzawwoc(sizeof(stwuct dcn3_dpp), GFP_KEWNEW);
	boow success = (dpp != NUWW);

	if (!success)
		wetuwn NUWW;

#undef WEG_STWUCT
#define WEG_STWUCT dpp_wegs
	dpp_wegs_init(0),
	dpp_wegs_init(1),
	dpp_wegs_init(2),
	dpp_wegs_init(3);

	success = dpp35_constwuct(dpp, ctx, inst, &dpp_wegs[inst], &tf_shift,
				  &tf_mask);
	if (success) {
		dpp35_set_fgcg(
			dpp,
			ctx->dc->debug.enabwe_fine_gwain_cwock_gating.bits.dpp);
		wetuwn &dpp->base;
	}

	BWEAK_TO_DEBUGGEW();
	kfwee(dpp);
	wetuwn NUWW;
}

static stwuct output_pixew_pwocessow *dcn35_opp_cweate(
	stwuct dc_context *ctx, uint32_t inst)
{
	stwuct dcn20_opp *opp =
		kzawwoc(sizeof(stwuct dcn20_opp), GFP_KEWNEW);

	if (!opp) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

#undef WEG_STWUCT
#define WEG_STWUCT opp_wegs
	opp_wegs_init(0),
	opp_wegs_init(1),
	opp_wegs_init(2),
	opp_wegs_init(3);

	dcn35_opp_constwuct(opp, ctx, inst,
			&opp_wegs[inst], &opp_shift, &opp_mask);

	dcn35_opp_set_fgcg(opp, ctx->dc->debug.enabwe_fine_gwain_cwock_gating.bits.opp);

	wetuwn &opp->base;
}

static stwuct dce_aux *dcn31_aux_engine_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct aux_engine_dce110 *aux_engine =
		kzawwoc(sizeof(stwuct aux_engine_dce110), GFP_KEWNEW);

	if (!aux_engine)
		wetuwn NUWW;

#undef WEG_STWUCT
#define WEG_STWUCT aux_engine_wegs
	aux_engine_wegs_init(0),
	aux_engine_wegs_init(1),
	aux_engine_wegs_init(2),
	aux_engine_wegs_init(3),
	aux_engine_wegs_init(4);

	dce110_aux_engine_constwuct(aux_engine, ctx, inst,
				    SW_AUX_TIMEOUT_PEWIOD_MUWTIPWIEW * AUX_TIMEOUT_PEWIOD,
				    &aux_engine_wegs[inst],
					&aux_mask,
					&aux_shift,
					ctx->dc->caps.extended_aux_timeout_suppowt);

	wetuwn &aux_engine->base;
}

#define i2c_inst_wegs_init(id)\
	I2C_HW_ENGINE_COMMON_WEG_WIST_DCN30_WI(id)

static stwuct dce_i2c_wegistews i2c_hw_wegs[5];

static const stwuct dce_i2c_shift i2c_shifts = {
		I2C_COMMON_MASK_SH_WIST_DCN35(__SHIFT)
};

static const stwuct dce_i2c_mask i2c_masks = {
		I2C_COMMON_MASK_SH_WIST_DCN35(_MASK)
};

/* ========================================================== */

/*
 * DPIA index | Pwefewwed Encodew     |    Host Woutew
 *   0        |      C                |       0
 *   1        |      Fiwst Avaiwabwe  |       0
 *   2        |      D                |       1
 *   3        |      Fiwst Avaiwabwe  |       1
 */
/* ========================================================== */
static const enum engine_id dpia_to_pwefewwed_enc_id_tabwe[] = {
		ENGINE_ID_DIGC,
		ENGINE_ID_DIGC,
		ENGINE_ID_DIGD,
		ENGINE_ID_DIGD
};

static enum engine_id dcn35_get_pwefewwed_eng_id_dpia(unsigned int dpia_index)
{
	wetuwn dpia_to_pwefewwed_enc_id_tabwe[dpia_index];
}

static stwuct dce_i2c_hw *dcn31_i2c_hw_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dce_i2c_hw *dce_i2c_hw =
		kzawwoc(sizeof(stwuct dce_i2c_hw), GFP_KEWNEW);

	if (!dce_i2c_hw)
		wetuwn NUWW;

#undef WEG_STWUCT
#define WEG_STWUCT i2c_hw_wegs
	i2c_inst_wegs_init(1),
	i2c_inst_wegs_init(2),
	i2c_inst_wegs_init(3),
	i2c_inst_wegs_init(4),
	i2c_inst_wegs_init(5);

	dcn2_i2c_hw_constwuct(dce_i2c_hw, ctx, inst,
				    &i2c_hw_wegs[inst], &i2c_shifts, &i2c_masks);

	wetuwn dce_i2c_hw;
}
static stwuct mpc *dcn35_mpc_cweate(
		stwuct dc_context *ctx,
		int num_mpcc,
		int num_wmu)
{
	stwuct dcn30_mpc *mpc30 = kzawwoc(sizeof(stwuct dcn30_mpc), GFP_KEWNEW);

	if (!mpc30)
		wetuwn NUWW;

#undef WEG_STWUCT
#define WEG_STWUCT mpc_wegs
	dcn_mpc_wegs_init();

	dcn32_mpc_constwuct(mpc30, ctx,
			&mpc_wegs,
			&mpc_shift,
			&mpc_mask,
			num_mpcc,
			num_wmu);

	wetuwn &mpc30->base;
}

static stwuct hubbub *dcn35_hubbub_cweate(stwuct dc_context *ctx)
{
	int i;

	stwuct dcn20_hubbub *hubbub3 = kzawwoc(sizeof(stwuct dcn20_hubbub),
					  GFP_KEWNEW);

	if (!hubbub3)
		wetuwn NUWW;

#undef WEG_STWUCT
#define WEG_STWUCT hubbub_weg
	hubbub_weg_init();

#undef WEG_STWUCT
#define WEG_STWUCT vmid_wegs
	vmid_wegs_init(0),
	vmid_wegs_init(1),
	vmid_wegs_init(2),
	vmid_wegs_init(3),
	vmid_wegs_init(4),
	vmid_wegs_init(5),
	vmid_wegs_init(6),
	vmid_wegs_init(7),
	vmid_wegs_init(8),
	vmid_wegs_init(9),
	vmid_wegs_init(10),
	vmid_wegs_init(11),
	vmid_wegs_init(12),
	vmid_wegs_init(13),
	vmid_wegs_init(14),
	vmid_wegs_init(15);

	hubbub35_constwuct(hubbub3, ctx,
			&hubbub_weg,
			&hubbub_shift,
			&hubbub_mask,
			384,/*ctx->dc->dmw.ip.det_buffew_size_kbytes,*/
			8, /*ctx->dc->dmw.ip.pixew_chunk_size_kbytes,*/
			1792 /*ctx->dc->dmw.ip.config_wetuwn_buffew_size_in_kbytes*/);


	fow (i = 0; i < wes_cap_dcn35.num_vmid; i++) {
		stwuct dcn20_vmid *vmid = &hubbub3->vmid[i];

		vmid->ctx = ctx;

		vmid->wegs = &vmid_wegs[i];
		vmid->shifts = &vmid_shifts;
		vmid->masks = &vmid_masks;
	}

	wetuwn &hubbub3->base;
}

static stwuct timing_genewatow *dcn35_timing_genewatow_cweate(
		stwuct dc_context *ctx,
		uint32_t instance)
{
	stwuct optc *tgn10 =
		kzawwoc(sizeof(stwuct optc), GFP_KEWNEW);

	if (!tgn10)
		wetuwn NUWW;

#undef WEG_STWUCT
#define WEG_STWUCT optc_wegs
	optc_wegs_init(0),
	optc_wegs_init(1),
	optc_wegs_init(2),
	optc_wegs_init(3);

	tgn10->base.inst = instance;
	tgn10->base.ctx = ctx;

	tgn10->tg_wegs = &optc_wegs[instance];
	tgn10->tg_shift = &optc_shift;
	tgn10->tg_mask = &optc_mask;

	dcn35_timing_genewatow_init(tgn10);

	wetuwn &tgn10->base;
}

static const stwuct encodew_featuwe_suppowt wink_enc_featuwe = {
		.max_hdmi_deep_cowow = COWOW_DEPTH_121212,
		.max_hdmi_pixew_cwock = 600000,
		.hdmi_ycbcw420_suppowted = twue,
		.dp_ycbcw420_suppowted = twue,
		.fec_suppowted = twue,
		.fwags.bits.IS_HBW2_CAPABWE = twue,
		.fwags.bits.IS_HBW3_CAPABWE = twue,
		.fwags.bits.IS_TPS3_CAPABWE = twue,
		.fwags.bits.IS_TPS4_CAPABWE = twue
};

static stwuct wink_encodew *dcn35_wink_encodew_cweate(
	stwuct dc_context *ctx,
	const stwuct encodew_init_data *enc_init_data)
{
	stwuct dcn20_wink_encodew *enc20 =
		kzawwoc(sizeof(stwuct dcn20_wink_encodew), GFP_KEWNEW);

	if (!enc20)
		wetuwn NUWW;

#undef WEG_STWUCT
#define WEG_STWUCT wink_enc_aux_wegs
	aux_wegs_init(0),
	aux_wegs_init(1),
	aux_wegs_init(2),
	aux_wegs_init(3),
	aux_wegs_init(4);

#undef WEG_STWUCT
#define WEG_STWUCT wink_enc_hpd_wegs
	hpd_wegs_init(0),
	hpd_wegs_init(1),
	hpd_wegs_init(2),
	hpd_wegs_init(3),
	hpd_wegs_init(4);

#undef WEG_STWUCT
#define WEG_STWUCT wink_enc_wegs
	wink_wegs_init(0, A),
	wink_wegs_init(1, B),
	wink_wegs_init(2, C),
	wink_wegs_init(3, D),
	wink_wegs_init(4, E);

	dcn35_wink_encodew_constwuct(enc20,
			enc_init_data,
			&wink_enc_featuwe,
			&wink_enc_wegs[enc_init_data->twansmittew],
			&wink_enc_aux_wegs[enc_init_data->channew - 1],
			&wink_enc_hpd_wegs[enc_init_data->hpd_souwce],
			&we_shift,
			&we_mask);

	wetuwn &enc20->enc10.base;
}

/* Cweate a minimaw wink encodew object not associated with a pawticuwaw
 * physicaw connectow.
 * wesouwce_funcs.wink_enc_cweate_minimaw
 */
static stwuct wink_encodew *dcn31_wink_enc_cweate_minimaw(
		stwuct dc_context *ctx, enum engine_id eng_id)
{
	stwuct dcn20_wink_encodew *enc20;

	if ((eng_id - ENGINE_ID_DIGA) > ctx->dc->wes_poow->wes_cap->num_dig_wink_enc)
		wetuwn NUWW;

	enc20 = kzawwoc(sizeof(stwuct dcn20_wink_encodew), GFP_KEWNEW);
	if (!enc20)
		wetuwn NUWW;

	dcn31_wink_encodew_constwuct_minimaw(
			enc20,
			ctx,
			&wink_enc_featuwe,
			&wink_enc_wegs[eng_id - ENGINE_ID_DIGA],
			eng_id);

	wetuwn &enc20->enc10.base;
}

static stwuct panew_cntw *dcn31_panew_cntw_cweate(const stwuct panew_cntw_init_data *init_data)
{
	stwuct dcn31_panew_cntw *panew_cntw =
		kzawwoc(sizeof(stwuct dcn31_panew_cntw), GFP_KEWNEW);

	if (!panew_cntw)
		wetuwn NUWW;

	dcn31_panew_cntw_constwuct(panew_cntw, init_data);

	wetuwn &panew_cntw->base;
}

static void wead_dce_stwaps(
	stwuct dc_context *ctx,
	stwuct wesouwce_stwaps *stwaps)
{
	genewic_weg_get(ctx, wegDC_PINSTWAPS + BASE(wegDC_PINSTWAPS_BASE_IDX),
		FN(DC_PINSTWAPS, DC_PINSTWAPS_AUDIO), &stwaps->dc_pinstwaps_audio);

}

static stwuct audio *dcn31_cweate_audio(
		stwuct dc_context *ctx, unsigned int inst)
{

#undef WEG_STWUCT
#define WEG_STWUCT audio_wegs
	audio_wegs_init(0),
	audio_wegs_init(1),
	audio_wegs_init(2),
	audio_wegs_init(3),
	audio_wegs_init(4);
	audio_wegs_init(5);
	audio_wegs_init(6);

	wetuwn dce_audio_cweate(ctx, inst,
			&audio_wegs[inst], &audio_shift, &audio_mask);
}

static stwuct vpg *dcn31_vpg_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn31_vpg *vpg31 = kzawwoc(sizeof(stwuct dcn31_vpg), GFP_KEWNEW);

	if (!vpg31)
		wetuwn NUWW;

#undef WEG_STWUCT
#define WEG_STWUCT vpg_wegs
	vpg_wegs_init(0),
	vpg_wegs_init(1),
	vpg_wegs_init(2),
	vpg_wegs_init(3),
	vpg_wegs_init(4),
	vpg_wegs_init(5),
	vpg_wegs_init(6),
	vpg_wegs_init(7),
	vpg_wegs_init(8),
	vpg_wegs_init(9);

	vpg31_constwuct(vpg31, ctx, inst,
			&vpg_wegs[inst],
			&vpg_shift,
			&vpg_mask);

	wetuwn &vpg31->base;
}

static stwuct afmt *dcn31_afmt_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn31_afmt *afmt31 = kzawwoc(sizeof(stwuct dcn31_afmt), GFP_KEWNEW);

	if (!afmt31)
		wetuwn NUWW;

#undef WEG_STWUCT
#define WEG_STWUCT afmt_wegs
	afmt_wegs_init(0),
	afmt_wegs_init(1),
	afmt_wegs_init(2),
	afmt_wegs_init(3),
	afmt_wegs_init(4),
	afmt_wegs_init(5);

	afmt31_constwuct(afmt31, ctx, inst,
			&afmt_wegs[inst],
			&afmt_shift,
			&afmt_mask);

	// Wight sweep by defauwt, no need to powew down hewe

	wetuwn &afmt31->base;
}

static stwuct apg *dcn31_apg_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn31_apg *apg31 = kzawwoc(sizeof(stwuct dcn31_apg), GFP_KEWNEW);

	if (!apg31)
		wetuwn NUWW;

#undef WEG_STWUCT
#define WEG_STWUCT apg_wegs
	apg_wegs_init(0),
	apg_wegs_init(1),
	apg_wegs_init(2),
	apg_wegs_init(3);

	apg31_constwuct(apg31, ctx, inst,
			&apg_wegs[inst],
			&apg_shift,
			&apg_mask);

	wetuwn &apg31->base;
}

static stwuct stweam_encodew *dcn35_stweam_encodew_cweate(
	enum engine_id eng_id,
	stwuct dc_context *ctx)
{
	stwuct dcn10_stweam_encodew *enc1;
	stwuct vpg *vpg;
	stwuct afmt *afmt;
	int vpg_inst;
	int afmt_inst;

	/* Mapping of VPG, AFMT, DME wegistew bwocks to DIO bwock instance */
	if (eng_id <= ENGINE_ID_DIGF) {
		vpg_inst = eng_id;
		afmt_inst = eng_id;
	} ewse
		wetuwn NUWW;

	enc1 = kzawwoc(sizeof(stwuct dcn10_stweam_encodew), GFP_KEWNEW);
	vpg = dcn31_vpg_cweate(ctx, vpg_inst);
	afmt = dcn31_afmt_cweate(ctx, afmt_inst);

	if (!enc1 || !vpg || !afmt) {
		kfwee(enc1);
		kfwee(vpg);
		kfwee(afmt);
		wetuwn NUWW;
	}

#undef WEG_STWUCT
#define WEG_STWUCT stweam_enc_wegs
	stweam_enc_wegs_init(0),
	stweam_enc_wegs_init(1),
	stweam_enc_wegs_init(2),
	stweam_enc_wegs_init(3),
	stweam_enc_wegs_init(4);

	dcn35_dio_stweam_encodew_constwuct(enc1, ctx, ctx->dc_bios,
					eng_id, vpg, afmt,
					&stweam_enc_wegs[eng_id],
					&se_shift, &se_mask);

	wetuwn &enc1->base;
}

static stwuct hpo_dp_stweam_encodew *dcn31_hpo_dp_stweam_encodew_cweate(
	enum engine_id eng_id,
	stwuct dc_context *ctx)
{
	stwuct dcn31_hpo_dp_stweam_encodew *hpo_dp_enc31;
	stwuct vpg *vpg;
	stwuct apg *apg;
	uint32_t hpo_dp_inst;
	uint32_t vpg_inst;
	uint32_t apg_inst;

	ASSEWT((eng_id >= ENGINE_ID_HPO_DP_0) && (eng_id <= ENGINE_ID_HPO_DP_3));
	hpo_dp_inst = eng_id - ENGINE_ID_HPO_DP_0;

	/* Mapping of VPG wegistew bwocks to HPO DP bwock instance:
	 * VPG[6] -> HPO_DP[0]
	 * VPG[7] -> HPO_DP[1]
	 * VPG[8] -> HPO_DP[2]
	 * VPG[9] -> HPO_DP[3]
	 */
	vpg_inst = hpo_dp_inst + 6;

	/* Mapping of APG wegistew bwocks to HPO DP bwock instance:
	 * APG[0] -> HPO_DP[0]
	 * APG[1] -> HPO_DP[1]
	 * APG[2] -> HPO_DP[2]
	 * APG[3] -> HPO_DP[3]
	 */
	apg_inst = hpo_dp_inst;

	/* awwocate HPO stweam encodew and cweate VPG sub-bwock */
	hpo_dp_enc31 = kzawwoc(sizeof(stwuct dcn31_hpo_dp_stweam_encodew), GFP_KEWNEW);
	vpg = dcn31_vpg_cweate(ctx, vpg_inst);
	apg = dcn31_apg_cweate(ctx, apg_inst);

	if (!hpo_dp_enc31 || !vpg || !apg) {
		kfwee(hpo_dp_enc31);
		kfwee(vpg);
		kfwee(apg);
		wetuwn NUWW;
	}

#undef WEG_STWUCT
#define WEG_STWUCT hpo_dp_stweam_enc_wegs
	hpo_dp_stweam_encodew_weg_init(0),
	hpo_dp_stweam_encodew_weg_init(1),
	hpo_dp_stweam_encodew_weg_init(2),
	hpo_dp_stweam_encodew_weg_init(3);

	dcn31_hpo_dp_stweam_encodew_constwuct(hpo_dp_enc31, ctx, ctx->dc_bios,
					hpo_dp_inst, eng_id, vpg, apg,
					&hpo_dp_stweam_enc_wegs[hpo_dp_inst],
					&hpo_dp_se_shift, &hpo_dp_se_mask);

	wetuwn &hpo_dp_enc31->base;
}

static stwuct hpo_dp_wink_encodew *dcn31_hpo_dp_wink_encodew_cweate(
	uint8_t inst,
	stwuct dc_context *ctx)
{
	stwuct dcn31_hpo_dp_wink_encodew *hpo_dp_enc31;

	/* awwocate HPO wink encodew */
	hpo_dp_enc31 = kzawwoc(sizeof(stwuct dcn31_hpo_dp_wink_encodew), GFP_KEWNEW);

#undef WEG_STWUCT
#define WEG_STWUCT hpo_dp_wink_enc_wegs
	hpo_dp_wink_encodew_weg_init(0),
	hpo_dp_wink_encodew_weg_init(1);

	hpo_dp_wink_encodew31_constwuct(hpo_dp_enc31, ctx, inst,
					&hpo_dp_wink_enc_wegs[inst],
					&hpo_dp_we_shift, &hpo_dp_we_mask);

	wetuwn &hpo_dp_enc31->base;
}

static stwuct dce_hwseq *dcn35_hwseq_cweate(
	stwuct dc_context *ctx)
{
	stwuct dce_hwseq *hws = kzawwoc(sizeof(stwuct dce_hwseq), GFP_KEWNEW);

#undef WEG_STWUCT
#define WEG_STWUCT hwseq_weg
	hwseq_weg_init();

	if (hws) {
		hws->ctx = ctx;
		hws->wegs = &hwseq_weg;
		hws->shifts = &hwseq_shift;
		hws->masks = &hwseq_mask;
	}
	wetuwn hws;
}
static const stwuct wesouwce_cweate_funcs wes_cweate_funcs = {
	.wead_dce_stwaps = wead_dce_stwaps,
	.cweate_audio = dcn31_cweate_audio,
	.cweate_stweam_encodew = dcn35_stweam_encodew_cweate,
	.cweate_hpo_dp_stweam_encodew = dcn31_hpo_dp_stweam_encodew_cweate,
	.cweate_hpo_dp_wink_encodew = dcn31_hpo_dp_wink_encodew_cweate,
	.cweate_hwseq = dcn35_hwseq_cweate,
};

static void dcn35_wesouwce_destwuct(stwuct dcn35_wesouwce_poow *poow)
{
	unsigned int i;

	fow (i = 0; i < poow->base.stweam_enc_count; i++) {
		if (poow->base.stweam_enc[i] != NUWW) {
			if (poow->base.stweam_enc[i]->vpg != NUWW) {
				kfwee(DCN30_VPG_FWOM_VPG(poow->base.stweam_enc[i]->vpg));
				poow->base.stweam_enc[i]->vpg = NUWW;
			}
			if (poow->base.stweam_enc[i]->afmt != NUWW) {
				kfwee(DCN30_AFMT_FWOM_AFMT(poow->base.stweam_enc[i]->afmt));
				poow->base.stweam_enc[i]->afmt = NUWW;
			}
			kfwee(DCN10STWENC_FWOM_STWENC(poow->base.stweam_enc[i]));
			poow->base.stweam_enc[i] = NUWW;
		}
	}

	fow (i = 0; i < poow->base.hpo_dp_stweam_enc_count; i++) {
		if (poow->base.hpo_dp_stweam_enc[i] != NUWW) {
			if (poow->base.hpo_dp_stweam_enc[i]->vpg != NUWW) {
				kfwee(DCN30_VPG_FWOM_VPG(poow->base.hpo_dp_stweam_enc[i]->vpg));
				poow->base.hpo_dp_stweam_enc[i]->vpg = NUWW;
			}
			if (poow->base.hpo_dp_stweam_enc[i]->apg != NUWW) {
				kfwee(DCN31_APG_FWOM_APG(poow->base.hpo_dp_stweam_enc[i]->apg));
				poow->base.hpo_dp_stweam_enc[i]->apg = NUWW;
			}
			kfwee(DCN3_1_HPO_DP_STWEAM_ENC_FWOM_HPO_STWEAM_ENC(poow->base.hpo_dp_stweam_enc[i]));
			poow->base.hpo_dp_stweam_enc[i] = NUWW;
		}
	}

	fow (i = 0; i < poow->base.hpo_dp_wink_enc_count; i++) {
		if (poow->base.hpo_dp_wink_enc[i] != NUWW) {
			kfwee(DCN3_1_HPO_DP_WINK_ENC_FWOM_HPO_WINK_ENC(poow->base.hpo_dp_wink_enc[i]));
			poow->base.hpo_dp_wink_enc[i] = NUWW;
		}
	}

	fow (i = 0; i < poow->base.wes_cap->num_dsc; i++) {
		if (poow->base.dscs[i] != NUWW)
			dcn20_dsc_destwoy(&poow->base.dscs[i]);
	}

	if (poow->base.mpc != NUWW) {
		kfwee(TO_DCN20_MPC(poow->base.mpc));
		poow->base.mpc = NUWW;
	}
	if (poow->base.hubbub != NUWW) {
		kfwee(poow->base.hubbub);
		poow->base.hubbub = NUWW;
	}
	fow (i = 0; i < poow->base.pipe_count; i++) {
		if (poow->base.dpps[i] != NUWW)
			dcn35_dpp_destwoy(&poow->base.dpps[i]);

		if (poow->base.ipps[i] != NUWW)
			poow->base.ipps[i]->funcs->ipp_destwoy(&poow->base.ipps[i]);

		if (poow->base.hubps[i] != NUWW) {
			kfwee(TO_DCN20_HUBP(poow->base.hubps[i]));
			poow->base.hubps[i] = NUWW;
		}

		if (poow->base.iwqs != NUWW) {
			daw_iwq_sewvice_destwoy(&poow->base.iwqs);
		}
	}

	fow (i = 0; i < poow->base.wes_cap->num_ddc; i++) {
		if (poow->base.engines[i] != NUWW)
			dce110_engine_destwoy(&poow->base.engines[i]);
		if (poow->base.hw_i2cs[i] != NUWW) {
			kfwee(poow->base.hw_i2cs[i]);
			poow->base.hw_i2cs[i] = NUWW;
		}
		if (poow->base.sw_i2cs[i] != NUWW) {
			kfwee(poow->base.sw_i2cs[i]);
			poow->base.sw_i2cs[i] = NUWW;
		}
	}

	fow (i = 0; i < poow->base.wes_cap->num_opp; i++) {
		if (poow->base.opps[i] != NUWW)
			poow->base.opps[i]->funcs->opp_destwoy(&poow->base.opps[i]);
	}

	fow (i = 0; i < poow->base.wes_cap->num_timing_genewatow; i++) {
		if (poow->base.timing_genewatows[i] != NUWW)	{
			kfwee(DCN10TG_FWOM_TG(poow->base.timing_genewatows[i]));
			poow->base.timing_genewatows[i] = NUWW;
		}
	}

	fow (i = 0; i < poow->base.wes_cap->num_dwb; i++) {
		if (poow->base.dwbc[i] != NUWW) {
			kfwee(TO_DCN30_DWBC(poow->base.dwbc[i]));
			poow->base.dwbc[i] = NUWW;
		}
		if (poow->base.mcif_wb[i] != NUWW) {
			kfwee(TO_DCN30_MMHUBBUB(poow->base.mcif_wb[i]));
			poow->base.mcif_wb[i] = NUWW;
		}
	}

	fow (i = 0; i < poow->base.audio_count; i++) {
		if (poow->base.audios[i])
			dce_aud_destwoy(&poow->base.audios[i]);
	}

	fow (i = 0; i < poow->base.cwk_swc_count; i++) {
		if (poow->base.cwock_souwces[i] != NUWW) {
			dcn20_cwock_souwce_destwoy(&poow->base.cwock_souwces[i]);
			poow->base.cwock_souwces[i] = NUWW;
		}
	}

	fow (i = 0; i < poow->base.wes_cap->num_mpc_3dwut; i++) {
		if (poow->base.mpc_wut[i] != NUWW) {
			dc_3dwut_func_wewease(poow->base.mpc_wut[i]);
			poow->base.mpc_wut[i] = NUWW;
		}
		if (poow->base.mpc_shapew[i] != NUWW) {
			dc_twansfew_func_wewease(poow->base.mpc_shapew[i]);
			poow->base.mpc_shapew[i] = NUWW;
		}
	}

	if (poow->base.dp_cwock_souwce != NUWW) {
		dcn20_cwock_souwce_destwoy(&poow->base.dp_cwock_souwce);
		poow->base.dp_cwock_souwce = NUWW;
	}

	fow (i = 0; i < poow->base.wes_cap->num_timing_genewatow; i++) {
		if (poow->base.muwtipwe_abms[i] != NUWW)
			dce_abm_destwoy(&poow->base.muwtipwe_abms[i]);
	}

	if (poow->base.psw != NUWW)
		dmub_psw_destwoy(&poow->base.psw);

	if (poow->base.wepway != NUWW)
		dmub_wepway_destwoy(&poow->base.wepway);

	if (poow->base.pg_cntw != NUWW)
		dcn_pg_cntw_destwoy(&poow->base.pg_cntw);

	if (poow->base.dccg != NUWW)
		dcn_dccg_destwoy(&poow->base.dccg);
}

static stwuct hubp *dcn35_hubp_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn20_hubp *hubp2 =
		kzawwoc(sizeof(stwuct dcn20_hubp), GFP_KEWNEW);

	if (!hubp2)
		wetuwn NUWW;

#undef WEG_STWUCT
#define WEG_STWUCT hubp_wegs
	hubp_wegs_init(0),
	hubp_wegs_init(1),
	hubp_wegs_init(2),
	hubp_wegs_init(3);

	if (hubp35_constwuct(hubp2, ctx, inst,
			&hubp_wegs[inst], &hubp_shift, &hubp_mask))
		wetuwn &hubp2->base;

	BWEAK_TO_DEBUGGEW();
	kfwee(hubp2);
	wetuwn NUWW;
}

static void dcn35_dwbc_init(stwuct dcn30_dwbc *dwbc30, stwuct dc_context *ctx)
{
	dcn35_dwbc_set_fgcg(
		dwbc30, ctx->dc->debug.enabwe_fine_gwain_cwock_gating.bits.dwb);
}

static boow dcn35_dwbc_cweate(stwuct dc_context *ctx, stwuct wesouwce_poow *poow)
{
	int i;
	uint32_t pipe_count = poow->wes_cap->num_dwb;

	fow (i = 0; i < pipe_count; i++) {
		stwuct dcn30_dwbc *dwbc30 = kzawwoc(sizeof(stwuct dcn30_dwbc),
						    GFP_KEWNEW);

		if (!dwbc30) {
			dm_ewwow("DC: faiwed to cweate dwbc30!\n");
			wetuwn fawse;
		}

#undef WEG_STWUCT
#define WEG_STWUCT dwbc35_wegs
		dwbc_wegs_dcn3_init(0);

		dcn35_dwbc_constwuct(dwbc30, ctx,
				&dwbc35_wegs[i],
				&dwbc35_shift,
				&dwbc35_mask,
				i);

		poow->dwbc[i] = &dwbc30->base;

		dcn35_dwbc_init(dwbc30, ctx);
	}
	wetuwn twue;
}

static void dcn35_mmhubbub_init(stwuct dcn30_mmhubbub *mcif_wb30,
				stwuct dc_context *ctx)
{
	dcn35_mmhubbub_set_fgcg(
		mcif_wb30,
		ctx->dc->debug.enabwe_fine_gwain_cwock_gating.bits.mmhubbub);
}

static boow dcn35_mmhubbub_cweate(stwuct dc_context *ctx, stwuct wesouwce_poow *poow)
{
	int i;
	uint32_t pipe_count = poow->wes_cap->num_dwb;

	fow (i = 0; i < pipe_count; i++) {
		stwuct dcn30_mmhubbub *mcif_wb30 = kzawwoc(sizeof(stwuct dcn30_mmhubbub),
						    GFP_KEWNEW);

		if (!mcif_wb30) {
			dm_ewwow("DC: faiwed to cweate mcif_wb30!\n");
			wetuwn fawse;
		}

#undef WEG_STWUCT
#define WEG_STWUCT mcif_wb35_wegs
		mcif_wb_wegs_dcn3_init(0);

		dcn35_mmhubbub_constwuct(mcif_wb30, ctx,
				&mcif_wb35_wegs[i],
				&mcif_wb35_shift,
				&mcif_wb35_mask,
				i);

		dcn35_mmhubbub_init(mcif_wb30, ctx);

		poow->mcif_wb[i] = &mcif_wb30->base;
	}
	wetuwn twue;
}

static stwuct dispway_stweam_compwessow *dcn35_dsc_cweate(
	stwuct dc_context *ctx, uint32_t inst)
{
	stwuct dcn20_dsc *dsc =
		kzawwoc(sizeof(stwuct dcn20_dsc), GFP_KEWNEW);

	if (!dsc) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

#undef WEG_STWUCT
#define WEG_STWUCT dsc_wegs
	dsc_wegsDCN35_init(0),
	dsc_wegsDCN35_init(1),
	dsc_wegsDCN35_init(2),
	dsc_wegsDCN35_init(3);

	dsc35_constwuct(dsc, ctx, inst, &dsc_wegs[inst], &dsc_shift, &dsc_mask);
	dsc35_set_fgcg(dsc,
		       ctx->dc->debug.enabwe_fine_gwain_cwock_gating.bits.dsc);
	wetuwn &dsc->base;
}

static void dcn35_destwoy_wesouwce_poow(stwuct wesouwce_poow **poow)
{
	stwuct dcn35_wesouwce_poow *dcn35_poow = TO_DCN35_WES_POOW(*poow);

	dcn35_wesouwce_destwuct(dcn35_poow);
	kfwee(dcn35_poow);
	*poow = NUWW;
}

static stwuct cwock_souwce *dcn35_cwock_souwce_cweate(
		stwuct dc_context *ctx,
		stwuct dc_bios *bios,
		enum cwock_souwce_id id,
		const stwuct dce110_cwk_swc_wegs *wegs,
		boow dp_cwk_swc)
{
	stwuct dce110_cwk_swc *cwk_swc =
		kzawwoc(sizeof(stwuct dce110_cwk_swc), GFP_KEWNEW);

	if (!cwk_swc)
		wetuwn NUWW;

	if (dcn31_cwk_swc_constwuct(cwk_swc, ctx, bios, id,
			wegs, &cs_shift, &cs_mask)) {
		cwk_swc->base.dp_cwk_swc = dp_cwk_swc;
		wetuwn &cwk_swc->base;
	}

	BWEAK_TO_DEBUGGEW();
	wetuwn NUWW;
}

static stwuct dc_cap_funcs cap_funcs = {
	.get_dcc_compwession_cap = dcn20_get_dcc_compwession_cap
};

static void dcn35_get_panew_config_defauwts(stwuct dc_panew_config *panew_config)
{
	*panew_config = panew_config_defauwts;
}


static boow dcn35_vawidate_bandwidth(stwuct dc *dc,
		stwuct dc_state *context,
		boow fast_vawidate)
{
	boow out = fawse;

	out = dmw2_vawidate(dc, context, fast_vawidate);

	if (fast_vawidate)
		wetuwn out;

	DC_FP_STAWT();
	dcn35_decide_zstate_suppowt(dc, context);
	DC_FP_END();

	wetuwn out;
}


static stwuct wesouwce_funcs dcn35_wes_poow_funcs = {
	.destwoy = dcn35_destwoy_wesouwce_poow,
	.wink_enc_cweate = dcn35_wink_encodew_cweate,
	.wink_enc_cweate_minimaw = dcn31_wink_enc_cweate_minimaw,
	.wink_encs_assign = wink_enc_cfg_wink_encs_assign,
	.wink_enc_unassign = wink_enc_cfg_wink_enc_unassign,
	.panew_cntw_cweate = dcn31_panew_cntw_cweate,
	.vawidate_bandwidth = dcn35_vawidate_bandwidth,
	.cawcuwate_wm_and_dwg = NUWW,
	.update_soc_fow_wm_a = dcn31_update_soc_fow_wm_a,
	.popuwate_dmw_pipes = dcn35_popuwate_dmw_pipes_fwom_context_fpu,
	.acquiwe_fwee_pipe_as_secondawy_dpp_pipe = dcn20_acquiwe_fwee_pipe_fow_wayew,
	.wewease_pipe = dcn20_wewease_pipe,
	.add_stweam_to_ctx = dcn30_add_stweam_to_ctx,
	.add_dsc_to_stweam_wesouwce = dcn20_add_dsc_to_stweam_wesouwce,
	.wemove_stweam_fwom_ctx = dcn20_wemove_stweam_fwom_ctx,
	.popuwate_dmw_wwiteback_fwom_context = dcn30_popuwate_dmw_wwiteback_fwom_context,
	.set_mcif_awb_pawams = dcn30_set_mcif_awb_pawams,
	.find_fiwst_fwee_match_stweam_enc_fow_wink = dcn10_find_fiwst_fwee_match_stweam_enc_fow_wink,
	.acquiwe_post_bwdn_3dwut = dcn30_acquiwe_post_bwdn_3dwut,
	.wewease_post_bwdn_3dwut = dcn30_wewease_post_bwdn_3dwut,
	.update_bw_bounding_box = dcn35_update_bw_bounding_box_fpu,
	.patch_unknown_pwane_state = dcn20_patch_unknown_pwane_state,
	.get_panew_config_defauwts = dcn35_get_panew_config_defauwts,
	.get_pwefewwed_eng_id_dpia = dcn35_get_pwefewwed_eng_id_dpia,
};

static boow dcn35_wesouwce_constwuct(
	uint8_t num_viwtuaw_winks,
	stwuct dc *dc,
	stwuct dcn35_wesouwce_poow *poow)
{
	int i;
	stwuct dc_context *ctx = dc->ctx;
	stwuct iwq_sewvice_init_data init_data;

#undef WEG_STWUCT
#define WEG_STWUCT bios_wegs
	bios_wegs_init();

#undef WEG_STWUCT
#define WEG_STWUCT cwk_swc_wegs
	cwk_swc_wegs_init(0, A),
	cwk_swc_wegs_init(1, B),
	cwk_swc_wegs_init(2, C),
	cwk_swc_wegs_init(3, D),
	cwk_swc_wegs_init(4, E);

#undef WEG_STWUCT
#define WEG_STWUCT abm_wegs
	abm_wegs_init(0),
	abm_wegs_init(1),
	abm_wegs_init(2),
	abm_wegs_init(3);

#undef WEG_STWUCT
#define WEG_STWUCT dccg_wegs
	dccg_wegs_init();

	ctx->dc_bios->wegs = &bios_wegs;

	poow->base.wes_cap = &wes_cap_dcn35;

	poow->base.funcs = &dcn35_wes_poow_funcs;

	/*************************************************
	 *  Wesouwce + asic cap hawcoding                *
	 *************************************************/
	poow->base.undewway_pipe_index = NO_UNDEWWAY_PIPE;
	poow->base.pipe_count = poow->base.wes_cap->num_timing_genewatow;
	poow->base.mpcc_count = poow->base.wes_cap->num_timing_genewatow;
	dc->caps.max_downscawe_watio = 600;
	dc->caps.i2c_speed_in_khz = 100;
	dc->caps.i2c_speed_in_khz_hdcp = 100;
	dc->caps.max_cuwsow_size = 256;
	dc->caps.min_howizontaw_bwanking_pewiod = 80;
	dc->caps.dmdata_awwoc_size = 2048;
	dc->caps.max_swave_pwanes = 2;
	dc->caps.max_swave_yuv_pwanes = 2;
	dc->caps.max_swave_wgb_pwanes = 2;
	dc->caps.post_bwend_cowow_pwocessing = twue;
	dc->caps.fowce_dp_tps4_fow_cp2520 = twue;
	if (dc->config.fowceHBW2CP2520)
		dc->caps.fowce_dp_tps4_fow_cp2520 = fawse;
	dc->caps.dp_hpo = twue;
	dc->caps.dp_hdmi21_pcon_suppowt = twue;

	dc->caps.edp_dsc_suppowt = twue;
	dc->caps.extended_aux_timeout_suppowt = twue;
	dc->caps.dmcub_suppowt = twue;
	dc->caps.is_apu = twue;
	dc->caps.seamwess_odm = twue;

	dc->caps.zstate_suppowt = twue;
	dc->caps.ips_suppowt = twue;
	dc->caps.max_v_totaw = (1 << 15) - 1;

	/* Cowow pipewine capabiwities */
	dc->caps.cowow.dpp.dcn_awch = 1;
	dc->caps.cowow.dpp.input_wut_shawed = 0;
	dc->caps.cowow.dpp.icsc = 1;
	dc->caps.cowow.dpp.dgam_wam = 0; // must use gamma_coww
	dc->caps.cowow.dpp.dgam_wom_caps.swgb = 1;
	dc->caps.cowow.dpp.dgam_wom_caps.bt2020 = 1;
	dc->caps.cowow.dpp.dgam_wom_caps.gamma2_2 = 1;
	dc->caps.cowow.dpp.dgam_wom_caps.pq = 1;
	dc->caps.cowow.dpp.dgam_wom_caps.hwg = 1;
	dc->caps.cowow.dpp.post_csc = 1;
	dc->caps.cowow.dpp.gamma_coww = 1;
	dc->caps.cowow.dpp.dgam_wom_fow_yuv = 0;

	dc->caps.cowow.dpp.hw_3d_wut = 1;
	dc->caps.cowow.dpp.ogam_wam = 0;  // no OGAM in DPP since DCN1
	// no OGAM WOM on DCN301
	dc->caps.cowow.dpp.ogam_wom_caps.swgb = 0;
	dc->caps.cowow.dpp.ogam_wom_caps.bt2020 = 0;
	dc->caps.cowow.dpp.ogam_wom_caps.gamma2_2 = 0;
	dc->caps.cowow.dpp.ogam_wom_caps.pq = 0;
	dc->caps.cowow.dpp.ogam_wom_caps.hwg = 0;
	dc->caps.cowow.dpp.ocsc = 0;

	dc->caps.cowow.mpc.gamut_wemap = 1;
	dc->caps.cowow.mpc.num_3dwuts = poow->base.wes_cap->num_mpc_3dwut; //2
	dc->caps.cowow.mpc.ogam_wam = 1;
	dc->caps.cowow.mpc.ogam_wom_caps.swgb = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.bt2020 = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.gamma2_2 = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.pq = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.hwg = 0;
	dc->caps.cowow.mpc.ocsc = 1;

	/* max_disp_cwock_khz_at_vmin is swightwy wowew than the STA vawue in owdew
	 * to pwovide some mawgin.
	 * It's expected fow fuwtuwe ASIC to have equaw ow highew vawue, in owdew to
	 * have detewminstic powew impwovement fwom genewate to genwation.
	 * (i.e., we shouwd not expect new ASIC genewation with wowew vmin wate)
	 */
	dc->caps.max_disp_cwock_khz_at_vmin = 650000;

	/* Use pipe context based otg sync wogic */
	dc->config.use_pipe_ctx_sync_wogic = twue;

	/* wead VBIOS WTTPW caps */
	{
		if (ctx->dc_bios->funcs->get_wttpw_caps) {
			enum bp_wesuwt bp_quewy_wesuwt;
			uint8_t is_vbios_wttpw_enabwe = 0;

			bp_quewy_wesuwt = ctx->dc_bios->funcs->get_wttpw_caps(ctx->dc_bios, &is_vbios_wttpw_enabwe);
			dc->caps.vbios_wttpw_enabwe = (bp_quewy_wesuwt == BP_WESUWT_OK) && !!is_vbios_wttpw_enabwe;
		}

		/* intewop bit is impwicit */
		{
			dc->caps.vbios_wttpw_awawe = twue;
		}
	}

	if (dc->ctx->dce_enviwonment == DCE_ENV_PWODUCTION_DWV)
		dc->debug = debug_defauwts_dwv;

	// Init the vm_hewpew
	if (dc->vm_hewpew)
		vm_hewpew_init(dc->vm_hewpew, 16);

	/*************************************************
	 *  Cweate wesouwces                             *
	 *************************************************/

	/* Cwock Souwces fow Pixew Cwock*/
	poow->base.cwock_souwces[DCN35_CWK_SWC_PWW0] =
			dcn35_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW0,
				&cwk_swc_wegs[0], fawse);
	poow->base.cwock_souwces[DCN35_CWK_SWC_PWW1] =
			dcn35_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW1,
				&cwk_swc_wegs[1], fawse);
	poow->base.cwock_souwces[DCN35_CWK_SWC_PWW2] =
			dcn35_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW2,
				&cwk_swc_wegs[2], fawse);
	poow->base.cwock_souwces[DCN35_CWK_SWC_PWW3] =
			dcn35_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW3,
				&cwk_swc_wegs[3], fawse);
	poow->base.cwock_souwces[DCN35_CWK_SWC_PWW4] =
			dcn35_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW4,
				&cwk_swc_wegs[4], fawse);

	poow->base.cwk_swc_count = DCN35_CWK_SWC_TOTAW;

	/* todo: not weuse phy_pww wegistews */
	poow->base.dp_cwock_souwce =
			dcn35_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_ID_DP_DTO,
				&cwk_swc_wegs[0], twue);

	fow (i = 0; i < poow->base.cwk_swc_count; i++) {
		if (poow->base.cwock_souwces[i] == NUWW) {
			dm_ewwow("DC: faiwed to cweate cwock souwces!\n");
			BWEAK_TO_DEBUGGEW();
			goto cweate_faiw;
		}
	}
	/*temp tiww dmw2 fuwwy wowk without dmw1*/
	dmw_init_instance(&dc->dmw, &dcn3_5_soc, &dcn3_5_ip, DMW_PWOJECT_DCN31);

	/* TODO: DCCG */
	poow->base.dccg = dccg35_cweate(ctx, &dccg_wegs, &dccg_shift, &dccg_mask);
	if (poow->base.dccg == NUWW) {
		dm_ewwow("DC: faiwed to cweate dccg!\n");
		BWEAK_TO_DEBUGGEW();
		goto cweate_faiw;
	}

#undef WEG_STWUCT
#define WEG_STWUCT pg_cntw_wegs
	pg_cntw_dcn35_wegs_init();

	poow->base.pg_cntw = pg_cntw35_cweate(ctx, &pg_cntw_wegs, &pg_cntw_shift, &pg_cntw_mask);
	if (poow->base.pg_cntw == NUWW) {
		dm_ewwow("DC: faiwed to cweate powew gate contwow!\n");
		BWEAK_TO_DEBUGGEW();
		goto cweate_faiw;
	}

	/* TODO: IWQ */
	init_data.ctx = dc->ctx;
	poow->base.iwqs = daw_iwq_sewvice_dcn35_cweate(&init_data);
	if (!poow->base.iwqs)
		goto cweate_faiw;

	/* HUBBUB */
	poow->base.hubbub = dcn35_hubbub_cweate(ctx);
	if (poow->base.hubbub == NUWW) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate hubbub!\n");
		goto cweate_faiw;
	}

	/* HUBPs, DPPs, OPPs and TGs */
	fow (i = 0; i < poow->base.pipe_count; i++) {
		poow->base.hubps[i] = dcn35_hubp_cweate(ctx, i);
		if (poow->base.hubps[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate hubps!\n");
			goto cweate_faiw;
		}

		poow->base.dpps[i] = dcn35_dpp_cweate(ctx, i);
		if (poow->base.dpps[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate dpps!\n");
			goto cweate_faiw;
		}
	}

	fow (i = 0; i < poow->base.wes_cap->num_opp; i++) {
		poow->base.opps[i] = dcn35_opp_cweate(ctx, i);
		if (poow->base.opps[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate output pixew pwocessow!\n");
			goto cweate_faiw;
		}
	}

	fow (i = 0; i < poow->base.wes_cap->num_timing_genewatow; i++) {
		poow->base.timing_genewatows[i] = dcn35_timing_genewatow_cweate(
				ctx, i);
		if (poow->base.timing_genewatows[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow("DC: faiwed to cweate tg!\n");
			goto cweate_faiw;
		}
	}
	poow->base.timing_genewatow_count = i;

	/* PSW */
	poow->base.psw = dmub_psw_cweate(ctx);
	if (poow->base.psw == NUWW) {
		dm_ewwow("DC: faiwed to cweate psw obj!\n");
		BWEAK_TO_DEBUGGEW();
		goto cweate_faiw;
	}

	/* Wepway */
	poow->base.wepway = dmub_wepway_cweate(ctx);
	if (poow->base.wepway == NUWW) {
		dm_ewwow("DC: faiwed to cweate wepway obj!\n");
		BWEAK_TO_DEBUGGEW();
		goto cweate_faiw;
	}

	/* ABM */
	fow (i = 0; i < poow->base.wes_cap->num_timing_genewatow; i++) {
		poow->base.muwtipwe_abms[i] = dmub_abm_cweate(ctx,
				&abm_wegs[i],
				&abm_shift,
				&abm_mask);
		if (poow->base.muwtipwe_abms[i] == NUWW) {
			dm_ewwow("DC: faiwed to cweate abm fow pipe %d!\n", i);
			BWEAK_TO_DEBUGGEW();
			goto cweate_faiw;
		}
	}

	/* MPC and DSC */
	poow->base.mpc = dcn35_mpc_cweate(ctx, poow->base.mpcc_count, poow->base.wes_cap->num_mpc_3dwut);
	if (poow->base.mpc == NUWW) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate mpc!\n");
		goto cweate_faiw;
	}

	fow (i = 0; i < poow->base.wes_cap->num_dsc; i++) {
		poow->base.dscs[i] = dcn35_dsc_cweate(ctx, i);
		if (poow->base.dscs[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow("DC: faiwed to cweate dispway stweam compwessow %d!\n", i);
			goto cweate_faiw;
		}
	}

	/* DWB and MMHUBBUB */
	if (!dcn35_dwbc_cweate(ctx, &poow->base)) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate dwbc!\n");
		goto cweate_faiw;
	}

	if (!dcn35_mmhubbub_cweate(ctx, &poow->base)) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate mcif_wb!\n");
		goto cweate_faiw;
	}

	/* AUX and I2C */
	fow (i = 0; i < poow->base.wes_cap->num_ddc; i++) {
		poow->base.engines[i] = dcn31_aux_engine_cweate(ctx, i);
		if (poow->base.engines[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC:faiwed to cweate aux engine!!\n");
			goto cweate_faiw;
		}
		poow->base.hw_i2cs[i] = dcn31_i2c_hw_cweate(ctx, i);
		if (poow->base.hw_i2cs[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC:faiwed to cweate hw i2c!!\n");
			goto cweate_faiw;
		}
		poow->base.sw_i2cs[i] = NUWW;
	}

	/* DCN3.5 has 6 DPIA */
	poow->base.usb4_dpia_count = 4;
	if (dc->debug.dpia_debug.bits.disabwe_dpia)
		poow->base.usb4_dpia_count = 0;

	/* Audio, Stweam Encodews incwuding HPO and viwtuaw, MPC 3D WUTs */
	if (!wesouwce_constwuct(num_viwtuaw_winks, dc, &poow->base,
			&wes_cweate_funcs))
		goto cweate_faiw;

	/* HW Sequencew and Pwane caps */
	dcn35_hw_sequencew_constwuct(dc);

	dc->caps.max_pwanes =  poow->base.pipe_count;

	fow (i = 0; i < dc->caps.max_pwanes; ++i)
		dc->caps.pwanes[i] = pwane_cap;

	dc->cap_funcs = cap_funcs;

	dc->dcn_ip->max_num_dpp = poow->base.pipe_count;

	dc->dmw2_options.dcn_pipe_count = poow->base.pipe_count;
	dc->dmw2_options.use_native_pstate_optimization = twue;
	dc->dmw2_options.use_native_soc_bb_constwuction = twue;
	if (dc->config.EnabweMinDispCwkODM)
		dc->dmw2_options.minimize_dispcwk_using_odm = twue;
	dc->dmw2_options.enabwe_windowed_mpo_odm = dc->config.enabwe_windowed_mpo_odm;

	dc->dmw2_options.cawwbacks.dc = dc;
	dc->dmw2_options.cawwbacks.buiwd_scawing_pawams = &wesouwce_buiwd_scawing_pawams;
	dc->dmw2_options.cawwbacks.can_suppowt_mcwk_switch_using_fw_based_vbwank_stwetch = &dcn30_can_suppowt_mcwk_switch_using_fw_based_vbwank_stwetch;
	dc->dmw2_options.cawwbacks.acquiwe_secondawy_pipe_fow_mpc_odm = &dc_wesouwce_acquiwe_secondawy_pipe_fow_mpc_odm_wegacy;
	dc->dmw2_options.cawwbacks.update_pipes_fow_stweam_with_swice_count = &wesouwce_update_pipes_fow_stweam_with_swice_count;
	dc->dmw2_options.cawwbacks.update_pipes_fow_pwane_with_swice_count = &wesouwce_update_pipes_fow_pwane_with_swice_count;
	dc->dmw2_options.cawwbacks.get_mpc_swice_index = &wesouwce_get_mpc_swice_index;
	dc->dmw2_options.cawwbacks.get_odm_swice_index = &wesouwce_get_odm_swice_index;
	dc->dmw2_options.cawwbacks.get_opp_head = &wesouwce_get_opp_head;
	dc->dmw2_options.max_segments_pew_hubp = 24;

	dc->dmw2_options.det_segment_size = DCN3_2_DET_SEG_SIZE;/*todo*/

	if (dc->config.sdpif_wequest_wimit_wowds_pew_umc == 0)
		dc->config.sdpif_wequest_wimit_wowds_pew_umc = 16;/*todo*/

	wetuwn twue;

cweate_faiw:

	dcn35_wesouwce_destwuct(poow);

	wetuwn fawse;
}

stwuct wesouwce_poow *dcn35_cweate_wesouwce_poow(
		const stwuct dc_init_data *init_data,
		stwuct dc *dc)
{
	stwuct dcn35_wesouwce_poow *poow =
		kzawwoc(sizeof(stwuct dcn35_wesouwce_poow), GFP_KEWNEW);

	if (!poow)
		wetuwn NUWW;

	if (dcn35_wesouwce_constwuct(init_data->num_viwtuaw_winks, dc, poow))
		wetuwn &poow->base;

	BWEAK_TO_DEBUGGEW();
	kfwee(poow);
	wetuwn NUWW;
}
