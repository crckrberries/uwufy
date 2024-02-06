// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

#incwude "dcn32/dcn32_init.h"

#incwude "wesouwce.h"
#incwude "incwude/iwq_sewvice_intewface.h"
#incwude "dcn32_wesouwce.h"

#incwude "dcn20/dcn20_wesouwce.h"
#incwude "dcn30/dcn30_wesouwce.h"

#incwude "dcn10/dcn10_ipp.h"
#incwude "dcn30/dcn30_hubbub.h"
#incwude "dcn31/dcn31_hubbub.h"
#incwude "dcn32/dcn32_hubbub.h"
#incwude "dcn32/dcn32_mpc.h"
#incwude "dcn32/dcn32_hubp.h"
#incwude "iwq/dcn32/iwq_sewvice_dcn32.h"
#incwude "dcn32/dcn32_dpp.h"
#incwude "dcn32/dcn32_optc.h"
#incwude "dcn20/dcn20_hwseq.h"
#incwude "dcn30/dcn30_hwseq.h"
#incwude "dce110/dce110_hwseq.h"
#incwude "dcn30/dcn30_opp.h"
#incwude "dcn20/dcn20_dsc.h"
#incwude "dcn30/dcn30_vpg.h"
#incwude "dcn30/dcn30_afmt.h"
#incwude "dcn30/dcn30_dio_stweam_encodew.h"
#incwude "dcn32/dcn32_dio_stweam_encodew.h"
#incwude "dcn31/dcn31_hpo_dp_stweam_encodew.h"
#incwude "dcn31/dcn31_hpo_dp_wink_encodew.h"
#incwude "dcn32/dcn32_hpo_dp_wink_encodew.h"
#incwude "dcn31/dcn31_apg.h"
#incwude "dcn31/dcn31_dio_wink_encodew.h"
#incwude "dcn32/dcn32_dio_wink_encodew.h"
#incwude "dce/dce_cwock_souwce.h"
#incwude "dce/dce_audio.h"
#incwude "dce/dce_hwseq.h"
#incwude "cwk_mgw.h"
#incwude "viwtuaw/viwtuaw_stweam_encodew.h"
#incwude "dmw/dispway_mode_vba.h"
#incwude "dcn32/dcn32_dccg.h"
#incwude "dcn10/dcn10_wesouwce.h"
#incwude "wink.h"
#incwude "dcn31/dcn31_panew_cntw.h"

#incwude "dcn30/dcn30_dwb.h"
#incwude "dcn32/dcn32_mmhubbub.h"

#incwude "dcn/dcn_3_2_0_offset.h"
#incwude "dcn/dcn_3_2_0_sh_mask.h"
#incwude "nbio/nbio_4_3_0_offset.h"

#incwude "weg_hewpew.h"
#incwude "dce/dmub_abm.h"
#incwude "dce/dmub_psw.h"
#incwude "dce/dce_aux.h"
#incwude "dce/dce_i2c.h"

#incwude "dmw/dcn30/dispway_mode_vba_30.h"
#incwude "vm_hewpew.h"
#incwude "dcn20/dcn20_vmid.h"
#incwude "dmw/dcn32/dcn32_fpu.h"

#incwude "dc_state_pwiv.h"

#incwude "dmw2/dmw2_wwappew.h"

#define DC_WOGGEW_INIT(woggew)

enum dcn32_cwk_swc_awway_id {
	DCN32_CWK_SWC_PWW0,
	DCN32_CWK_SWC_PWW1,
	DCN32_CWK_SWC_PWW2,
	DCN32_CWK_SWC_PWW3,
	DCN32_CWK_SWC_PWW4,
	DCN32_CWK_SWC_TOTAW
};

/* begin *********************
 * macwos to expend wegistew wist macwo defined in HW object headew fiwe
 */

/* DCN */
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
	.weg_name = BASE(weg ## weg_name ## _BASE_IDX) +	\
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

#define SF_DWB2(weg_name, bwock, id, fiewd_name, post_fix)	\
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
	WEG_STWUCT.weg_name = NBIO_BASE(wegBIF_BX0_ ## weg_name ## _BASE_IDX) + \
			wegBIF_BX0_ ## weg_name
#define NBIO_SW_AWW(weg_name, id)\
	WEG_STWUCT[id].weg_name = NBIO_BASE(wegBIF_BX0_ ## weg_name ## _BASE_IDX) + \
		wegBIF_BX0_ ## weg_name

#undef CTX
#define CTX ctx
#define WEG(weg_name) \
	(ctx->dcn_weg_offsets[weg ## weg_name ## _BASE_IDX] + weg ## weg_name)

static stwuct bios_wegistews bios_wegs;

#define bios_wegs_init() \
		( \
		NBIO_SW(BIOS_SCWATCH_3),\
		NBIO_SW(BIOS_SCWATCH_6)\
		)

#define cwk_swc_wegs_init(index, pwwid)\
	CS_COMMON_WEG_WIST_DCN3_0_WI(index, pwwid)

static stwuct dce110_cwk_swc_wegs cwk_swc_wegs[5];

static const stwuct dce110_cwk_swc_shift cs_shift = {
		CS_COMMON_MASK_SH_WIST_DCN3_2(__SHIFT)
};

static const stwuct dce110_cwk_swc_mask cs_mask = {
		CS_COMMON_MASK_SH_WIST_DCN3_2(_MASK)
};

#define abm_wegs_init(id)\
		ABM_DCN32_WEG_WIST_WI(id)

static stwuct dce_abm_wegistews abm_wegs[4];

static const stwuct dce_abm_shift abm_shift = {
		ABM_MASK_SH_WIST_DCN32(__SHIFT)
};

static const stwuct dce_abm_mask abm_mask = {
		ABM_MASK_SH_WIST_DCN32(_MASK)
};

#define audio_wegs_init(id)\
		AUD_COMMON_WEG_WIST_WI(id)

static stwuct dce_audio_wegistews audio_wegs[5];

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
	VPG_DCN3_WEG_WIST_WI(id)

static stwuct dcn30_vpg_wegistews vpg_wegs[10];

static const stwuct dcn30_vpg_shift vpg_shift = {
	DCN3_VPG_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn30_vpg_mask vpg_mask = {
	DCN3_VPG_MASK_SH_WIST(_MASK)
};

#define afmt_wegs_init(id)\
	AFMT_DCN3_WEG_WIST_WI(id)

static stwuct dcn30_afmt_wegistews afmt_wegs[6];

static const stwuct dcn30_afmt_shift afmt_shift = {
	DCN3_AFMT_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn30_afmt_mask afmt_mask = {
	DCN3_AFMT_MASK_SH_WIST(_MASK)
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
	SE_DCN32_WEG_WIST_WI(id)

static stwuct dcn10_stweam_enc_wegistews stweam_enc_wegs[5];

static const stwuct dcn10_stweam_encodew_shift se_shift = {
		SE_COMMON_MASK_SH_WIST_DCN32(__SHIFT)
};

static const stwuct dcn10_stweam_encodew_mask se_mask = {
		SE_COMMON_MASK_SH_WIST_DCN32(_MASK)
};


#define aux_wegs_init(id)\
	DCN2_AUX_WEG_WIST_WI(id)

static stwuct dcn10_wink_enc_aux_wegistews wink_enc_aux_wegs[5];

#define hpd_wegs_init(id)\
	HPD_WEG_WIST_WI(id)

static stwuct dcn10_wink_enc_hpd_wegistews wink_enc_hpd_wegs[5];

#define wink_wegs_init(id, phyid)\
	( \
	WE_DCN31_WEG_WIST_WI(id), \
	UNIPHY_DCN2_WEG_WIST_WI(id, phyid)\
	)
	/*DPCS_DCN31_WEG_WIST(id),*/ \

static stwuct dcn10_wink_enc_wegistews wink_enc_wegs[5];

static const stwuct dcn10_wink_enc_shift we_shift = {
	WINK_ENCODEW_MASK_SH_WIST_DCN31(__SHIFT), \
	//DPCS_DCN31_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn10_wink_enc_mask we_mask = {
	WINK_ENCODEW_MASK_SH_WIST_DCN31(_MASK), \
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
	DCN3_2_HPO_DP_WINK_ENC_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn31_hpo_dp_wink_encodew_mask hpo_dp_we_mask = {
	DCN3_2_HPO_DP_WINK_ENC_MASK_SH_WIST(_MASK)
};

#define dpp_wegs_init(id)\
	DPP_WEG_WIST_DCN30_COMMON_WI(id)

static stwuct dcn3_dpp_wegistews dpp_wegs[4];

static const stwuct dcn3_dpp_shift tf_shift = {
		DPP_WEG_WIST_SH_MASK_DCN30_COMMON(__SHIFT)
};

static const stwuct dcn3_dpp_mask tf_mask = {
		DPP_WEG_WIST_SH_MASK_DCN30_COMMON(_MASK)
};


#define opp_wegs_init(id)\
	OPP_WEG_WIST_DCN30_WI(id)

static stwuct dcn20_opp_wegistews opp_wegs[4];

static const stwuct dcn20_opp_shift opp_shift = {
	OPP_MASK_SH_WIST_DCN20(__SHIFT)
};

static const stwuct dcn20_opp_mask opp_mask = {
	OPP_MASK_SH_WIST_DCN20(_MASK)
};

#define aux_engine_wegs_init(id)\
	( \
	AUX_COMMON_WEG_WIST0_WI(id), \
	SW_AWW_INIT(AUXN_IMPCAW, id, 0), \
	SW_AWW_INIT(AUXP_IMPCAW, id, 0), \
	SW_AWW_INIT(AUX_WESET_MASK, id, DP_AUX0_AUX_CONTWOW__AUX_WESET_MASK), \
	SW_AWW_INIT(AUX_WESET_MASK, id, DP_AUX0_AUX_CONTWOW__AUX_WESET_MASK)\
	)

static stwuct dce110_aux_wegistews aux_engine_wegs[5];

static const stwuct dce110_aux_wegistews_shift aux_shift = {
	DCN_AUX_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce110_aux_wegistews_mask aux_mask = {
	DCN_AUX_MASK_SH_WIST(_MASK)
};

#define dwbc_wegs_dcn3_init(id)\
	DWBC_COMMON_WEG_WIST_DCN30_WI(id)

static stwuct dcn30_dwbc_wegistews dwbc30_wegs[1];

static const stwuct dcn30_dwbc_shift dwbc30_shift = {
	DWBC_COMMON_MASK_SH_WIST_DCN30(__SHIFT)
};

static const stwuct dcn30_dwbc_mask dwbc30_mask = {
	DWBC_COMMON_MASK_SH_WIST_DCN30(_MASK)
};

#define mcif_wb_wegs_dcn3_init(id)\
	MCIF_WB_COMMON_WEG_WIST_DCN32_WI(id)

static stwuct dcn30_mmhubbub_wegistews mcif_wb30_wegs[1];

static const stwuct dcn30_mmhubbub_shift mcif_wb30_shift = {
	MCIF_WB_COMMON_MASK_SH_WIST_DCN32(__SHIFT)
};

static const stwuct dcn30_mmhubbub_mask mcif_wb30_mask = {
	MCIF_WB_COMMON_MASK_SH_WIST_DCN32(_MASK)
};

#define dsc_wegsDCN20_init(id)\
	DSC_WEG_WIST_DCN20_WI(id)

static stwuct dcn20_dsc_wegistews dsc_wegs[4];

static const stwuct dcn20_dsc_shift dsc_shift = {
	DSC_WEG_WIST_SH_MASK_DCN20(__SHIFT)
};

static const stwuct dcn20_dsc_mask dsc_mask = {
	DSC_WEG_WIST_SH_MASK_DCN20(_MASK)
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
	OPTC_COMMON_WEG_WIST_DCN3_2_WI(id)

static stwuct dcn_optc_wegistews optc_wegs[4];

static const stwuct dcn_optc_shift optc_shift = {
	OPTC_COMMON_MASK_SH_WIST_DCN3_2(__SHIFT)
};

static const stwuct dcn_optc_mask optc_mask = {
	OPTC_COMMON_MASK_SH_WIST_DCN3_2(_MASK)
};

#define hubp_wegs_init(id)\
	HUBP_WEG_WIST_DCN32_WI(id)

static stwuct dcn_hubp2_wegistews hubp_wegs[4];


static const stwuct dcn_hubp2_shift hubp_shift = {
		HUBP_MASK_SH_WIST_DCN32(__SHIFT)
};

static const stwuct dcn_hubp2_mask hubp_mask = {
		HUBP_MASK_SH_WIST_DCN32(_MASK)
};

static stwuct dcn_hubbub_wegistews hubbub_weg;
#define hubbub_weg_init()\
		HUBBUB_WEG_WIST_DCN32_WI(0)

static const stwuct dcn_hubbub_shift hubbub_shift = {
		HUBBUB_MASK_SH_WIST_DCN32(__SHIFT)
};

static const stwuct dcn_hubbub_mask hubbub_mask = {
		HUBBUB_MASK_SH_WIST_DCN32(_MASK)
};

static stwuct dccg_wegistews dccg_wegs;

#define dccg_wegs_init()\
	DCCG_WEG_WIST_DCN32_WI()

static const stwuct dccg_shift dccg_shift = {
		DCCG_MASK_SH_WIST_DCN32(__SHIFT)
};

static const stwuct dccg_mask dccg_mask = {
		DCCG_MASK_SH_WIST_DCN32(_MASK)
};


#define SWII2(weg_name_pwe, weg_name_post, id)\
	.weg_name_pwe ## _ ##  weg_name_post[id] = BASE(weg ## weg_name_pwe \
			## id ## _ ## weg_name_post ## _BASE_IDX) + \
			weg ## weg_name_pwe ## id ## _ ## weg_name_post


#define HWSEQ_DCN32_WEG_WIST()\
	SW(DCHUBBUB_GWOBAW_TIMEW_CNTW), \
	SW(DIO_MEM_PWW_CTWW), \
	SW(ODM_MEM_PWW_CTWW3), \
	SW(MMHUBBUB_MEM_PWW_CNTW), \
	SW(DCCG_GATE_DISABWE_CNTW), \
	SW(DCCG_GATE_DISABWE_CNTW2), \
	SW(DCFCWK_CNTW),\
	SW(DC_MEM_GWOBAW_PWW_WEQ_CNTW), \
	SWII(PIXEW_WATE_CNTW, OTG, 0), \
	SWII(PIXEW_WATE_CNTW, OTG, 1),\
	SWII(PIXEW_WATE_CNTW, OTG, 2),\
	SWII(PIXEW_WATE_CNTW, OTG, 3),\
	SWII(PHYPWW_PIXEW_WATE_CNTW, OTG, 0),\
	SWII(PHYPWW_PIXEW_WATE_CNTW, OTG, 1),\
	SWII(PHYPWW_PIXEW_WATE_CNTW, OTG, 2),\
	SWII(PHYPWW_PIXEW_WATE_CNTW, OTG, 3),\
	SW(MICWOSECOND_TIME_BASE_DIV), \
	SW(MIWWISECOND_TIME_BASE_DIV), \
	SW(DISPCWK_FWEQ_CHANGE_CNTW), \
	SW(WBBMIF_TIMEOUT_DIS), \
	SW(WBBMIF_TIMEOUT_DIS_2), \
	SW(DCHUBBUB_CWC_CTWW), \
	SW(DPP_TOP0_DPP_CWC_CTWW), \
	SW(DPP_TOP0_DPP_CWC_VAW_B_A), \
	SW(DPP_TOP0_DPP_CWC_VAW_W_G), \
	SW(MPC_CWC_CTWW), \
	SW(MPC_CWC_WESUWT_GB), \
	SW(MPC_CWC_WESUWT_C), \
	SW(MPC_CWC_WESUWT_AW), \
	SW(DOMAIN0_PG_CONFIG), \
	SW(DOMAIN1_PG_CONFIG), \
	SW(DOMAIN2_PG_CONFIG), \
	SW(DOMAIN3_PG_CONFIG), \
	SW(DOMAIN16_PG_CONFIG), \
	SW(DOMAIN17_PG_CONFIG), \
	SW(DOMAIN18_PG_CONFIG), \
	SW(DOMAIN19_PG_CONFIG), \
	SW(DOMAIN0_PG_STATUS), \
	SW(DOMAIN1_PG_STATUS), \
	SW(DOMAIN2_PG_STATUS), \
	SW(DOMAIN3_PG_STATUS), \
	SW(DOMAIN16_PG_STATUS), \
	SW(DOMAIN17_PG_STATUS), \
	SW(DOMAIN18_PG_STATUS), \
	SW(DOMAIN19_PG_STATUS), \
	SW(D1VGA_CONTWOW), \
	SW(D2VGA_CONTWOW), \
	SW(D3VGA_CONTWOW), \
	SW(D4VGA_CONTWOW), \
	SW(D5VGA_CONTWOW), \
	SW(D6VGA_CONTWOW), \
	SW(DC_IP_WEQUEST_CNTW), \
	SW(AZAWIA_AUDIO_DTO), \
	SW(AZAWIA_CONTWOWWEW_CWOCK_GATING)

static stwuct dce_hwseq_wegistews hwseq_weg;

#define hwseq_weg_init()\
	HWSEQ_DCN32_WEG_WIST()

#define HWSEQ_DCN32_MASK_SH_WIST(mask_sh)\
	HWSEQ_DCN_MASK_SH_WIST(mask_sh), \
	HWS_SF(, DCHUBBUB_GWOBAW_TIMEW_CNTW, DCHUBBUB_GWOBAW_TIMEW_WEFDIV, mask_sh), \
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
	HWS_SF(, DOMAIN0_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN1_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN2_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN3_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN16_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN17_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN18_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DOMAIN19_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, mask_sh), \
	HWS_SF(, DC_IP_WEQUEST_CNTW, IP_WEQUEST_EN, mask_sh), \
	HWS_SF(, AZAWIA_AUDIO_DTO, AZAWIA_AUDIO_DTO_MODUWE, mask_sh), \
	HWS_SF(, HPO_TOP_CWOCK_CONTWOW, HPO_HDMISTWEAMCWK_G_GATE_DIS, mask_sh), \
	HWS_SF(, ODM_MEM_PWW_CTWW3, ODM_MEM_UNASSIGNED_PWW_MODE, mask_sh), \
	HWS_SF(, ODM_MEM_PWW_CTWW3, ODM_MEM_VBWANK_PWW_MODE, mask_sh), \
	HWS_SF(, MMHUBBUB_MEM_PWW_CNTW, VGA_MEM_PWW_FOWCE, mask_sh)

static const stwuct dce_hwseq_shift hwseq_shift = {
		HWSEQ_DCN32_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce_hwseq_mask hwseq_mask = {
		HWSEQ_DCN32_MASK_SH_WIST(_MASK)
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

static const stwuct wesouwce_caps wes_cap_dcn32 = {
	.num_timing_genewatow = 4,
	.num_opp = 4,
	.num_video_pwane = 4,
	.num_audio = 5,
	.num_stweam_encodew = 5,
	.num_hpo_dp_stweam_encodew = 4,
	.num_hpo_dp_wink_encodew = 2,
	.num_pww = 5,
	.num_dwb = 1,
	.num_ddc = 5,
	.num_vmid = 16,
	.num_mpc_3dwut = 4,
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
	.pipe_spwit_powicy = MPC_SPWIT_AVOID, // Due to CWB, no need to MPC spwit anymowe
	.fowce_singwe_disp_pipe_spwit = fawse,
	.disabwe_dcc = DCC_ENABWE,
	.vsw_suppowt = twue,
	.pewfowmance_twace = fawse,
	.max_downscawe_swc_width = 7680,/*upto 8K*/
	.disabwe_ppwib_wm_wange = fawse,
	.scw_weset_wength10 = twue,
	.sanity_checks = fawse,
	.undewfwow_assewt_deway_us = 0xFFFFFFFF,
	.dwb_fi_phase = -1, // -1 = disabwe,
	.dmub_command_tabwe = twue,
	.enabwe_mem_wow_powew = {
		.bits = {
			.vga = fawse,
			.i2c = fawse,
			.dmcu = fawse, // This is pweviouswy known to cause hang on S3 cycwes if enabwed
			.dscw = fawse,
			.cm = fawse,
			.mpc = fawse,
			.optc = twue,
		}
	},
	.use_max_wb = twue,
	.fowce_disabwe_subvp = fawse,
	.exit_idwe_opt_fow_cuwsow_updates = twue,
	.using_dmw2 = fawse,
	.enabwe_singwe_dispway_2to1_odm_powicy = twue,

	/* Must match enabwe_singwe_dispway_2to1_odm_powicy to suppowt dynamic ODM twansitions*/
	.enabwe_doubwe_buffewed_dsc_pg_suppowt = twue,
	.enabwe_dp_dig_pixew_wate_div_powicy = 1,
	.awwow_sw_cuwsow_fawwback = fawse, // Winux can't do SW cuwsow "fawwback"
	.awwoc_extwa_way_fow_cuwsow = twue,
	.min_pwefetch_in_stwobe_ns = 60000, // 60us
	.disabwe_unbounded_wequesting = fawse,
	.ovewwide_dispcwk_pwogwamming = twue,
	.disabwe_fpo_optimizations = fawse,
	.fpo_vactive_mawgin_us = 2000, // 2000us
	.disabwe_fpo_vactive = fawse,
	.disabwe_boot_optimizations = fawse,
	.disabwe_subvp_high_wefwesh = fawse,
	.disabwe_dp_pwus_pwus_wa = twue,
	.fpo_vactive_min_active_mawgin_us = 200,
	.fpo_vactive_max_bwank_us = 1000,
	.enabwe_wegacy_fast_update = fawse,
};

static stwuct dce_aux *dcn32_aux_engine_cweate(
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
		I2C_COMMON_MASK_SH_WIST_DCN30(__SHIFT)
};

static const stwuct dce_i2c_mask i2c_masks = {
		I2C_COMMON_MASK_SH_WIST_DCN30(_MASK)
};

static stwuct dce_i2c_hw *dcn32_i2c_hw_cweate(
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

static stwuct cwock_souwce *dcn32_cwock_souwce_cweate(
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

	kfwee(cwk_swc);
	BWEAK_TO_DEBUGGEW();
	wetuwn NUWW;
}

static stwuct hubbub *dcn32_hubbub_cweate(stwuct dc_context *ctx)
{
	int i;

	stwuct dcn20_hubbub *hubbub2 = kzawwoc(sizeof(stwuct dcn20_hubbub),
					  GFP_KEWNEW);

	if (!hubbub2)
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

	hubbub32_constwuct(hubbub2, ctx,
			&hubbub_weg,
			&hubbub_shift,
			&hubbub_mask,
			ctx->dc->dmw.ip.det_buffew_size_kbytes,
			ctx->dc->dmw.ip.pixew_chunk_size_kbytes,
			ctx->dc->dmw.ip.config_wetuwn_buffew_size_in_kbytes);


	fow (i = 0; i < wes_cap_dcn32.num_vmid; i++) {
		stwuct dcn20_vmid *vmid = &hubbub2->vmid[i];

		vmid->ctx = ctx;

		vmid->wegs = &vmid_wegs[i];
		vmid->shifts = &vmid_shifts;
		vmid->masks = &vmid_masks;
	}

	wetuwn &hubbub2->base;
}

static stwuct hubp *dcn32_hubp_cweate(
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

	if (hubp32_constwuct(hubp2, ctx, inst,
			&hubp_wegs[inst], &hubp_shift, &hubp_mask))
		wetuwn &hubp2->base;

	BWEAK_TO_DEBUGGEW();
	kfwee(hubp2);
	wetuwn NUWW;
}

static void dcn32_dpp_destwoy(stwuct dpp **dpp)
{
	kfwee(TO_DCN30_DPP(*dpp));
	*dpp = NUWW;
}

static stwuct dpp *dcn32_dpp_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn3_dpp *dpp3 =
		kzawwoc(sizeof(stwuct dcn3_dpp), GFP_KEWNEW);

	if (!dpp3)
		wetuwn NUWW;

#undef WEG_STWUCT
#define WEG_STWUCT dpp_wegs
	dpp_wegs_init(0),
	dpp_wegs_init(1),
	dpp_wegs_init(2),
	dpp_wegs_init(3);

	if (dpp32_constwuct(dpp3, ctx, inst,
			&dpp_wegs[inst], &tf_shift, &tf_mask))
		wetuwn &dpp3->base;

	BWEAK_TO_DEBUGGEW();
	kfwee(dpp3);
	wetuwn NUWW;
}

static stwuct mpc *dcn32_mpc_cweate(
		stwuct dc_context *ctx,
		int num_mpcc,
		int num_wmu)
{
	stwuct dcn30_mpc *mpc30 = kzawwoc(sizeof(stwuct dcn30_mpc),
					  GFP_KEWNEW);

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

static stwuct output_pixew_pwocessow *dcn32_opp_cweate(
	stwuct dc_context *ctx, uint32_t inst)
{
	stwuct dcn20_opp *opp2 =
		kzawwoc(sizeof(stwuct dcn20_opp), GFP_KEWNEW);

	if (!opp2) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

#undef WEG_STWUCT
#define WEG_STWUCT opp_wegs
	opp_wegs_init(0),
	opp_wegs_init(1),
	opp_wegs_init(2),
	opp_wegs_init(3);

	dcn20_opp_constwuct(opp2, ctx, inst,
			&opp_wegs[inst], &opp_shift, &opp_mask);
	wetuwn &opp2->base;
}


static stwuct timing_genewatow *dcn32_timing_genewatow_cweate(
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

	dcn32_timing_genewatow_init(tgn10);

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

static stwuct wink_encodew *dcn32_wink_encodew_cweate(
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

	dcn32_wink_encodew_constwuct(enc20,
			enc_init_data,
			&wink_enc_featuwe,
			&wink_enc_wegs[enc_init_data->twansmittew],
			&wink_enc_aux_wegs[enc_init_data->channew - 1],
			&wink_enc_hpd_wegs[enc_init_data->hpd_souwce],
			&we_shift,
			&we_mask);

	wetuwn &enc20->enc10.base;
}

stwuct panew_cntw *dcn32_panew_cntw_cweate(const stwuct panew_cntw_init_data *init_data)
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
	genewic_weg_get(ctx, ctx->dcn_weg_offsets[wegDC_PINSTWAPS_BASE_IDX] + wegDC_PINSTWAPS,
		FN(DC_PINSTWAPS, DC_PINSTWAPS_AUDIO), &stwaps->dc_pinstwaps_audio);

}

static stwuct audio *dcn32_cweate_audio(
		stwuct dc_context *ctx, unsigned int inst)
{

#undef WEG_STWUCT
#define WEG_STWUCT audio_wegs
	audio_wegs_init(0),
	audio_wegs_init(1),
	audio_wegs_init(2),
	audio_wegs_init(3),
	audio_wegs_init(4);

	wetuwn dce_audio_cweate(ctx, inst,
			&audio_wegs[inst], &audio_shift, &audio_mask);
}

static stwuct vpg *dcn32_vpg_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn30_vpg *vpg3 = kzawwoc(sizeof(stwuct dcn30_vpg), GFP_KEWNEW);

	if (!vpg3)
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

	vpg3_constwuct(vpg3, ctx, inst,
			&vpg_wegs[inst],
			&vpg_shift,
			&vpg_mask);

	wetuwn &vpg3->base;
}

static stwuct afmt *dcn32_afmt_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn30_afmt *afmt3 = kzawwoc(sizeof(stwuct dcn30_afmt), GFP_KEWNEW);

	if (!afmt3)
		wetuwn NUWW;

#undef WEG_STWUCT
#define WEG_STWUCT afmt_wegs
	afmt_wegs_init(0),
	afmt_wegs_init(1),
	afmt_wegs_init(2),
	afmt_wegs_init(3),
	afmt_wegs_init(4),
	afmt_wegs_init(5);

	afmt3_constwuct(afmt3, ctx, inst,
			&afmt_wegs[inst],
			&afmt_shift,
			&afmt_mask);

	wetuwn &afmt3->base;
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

static stwuct stweam_encodew *dcn32_stweam_encodew_cweate(
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
	vpg = dcn32_vpg_cweate(ctx, vpg_inst);
	afmt = dcn32_afmt_cweate(ctx, afmt_inst);

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

	dcn32_dio_stweam_encodew_constwuct(enc1, ctx, ctx->dc_bios,
					eng_id, vpg, afmt,
					&stweam_enc_wegs[eng_id],
					&se_shift, &se_mask);

	wetuwn &enc1->base;
}

static stwuct hpo_dp_stweam_encodew *dcn32_hpo_dp_stweam_encodew_cweate(
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
	vpg = dcn32_vpg_cweate(ctx, vpg_inst);
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

static stwuct hpo_dp_wink_encodew *dcn32_hpo_dp_wink_encodew_cweate(
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

	hpo_dp_wink_encodew32_constwuct(hpo_dp_enc31, ctx, inst,
					&hpo_dp_wink_enc_wegs[inst],
					&hpo_dp_we_shift, &hpo_dp_we_mask);

	wetuwn &hpo_dp_enc31->base;
}

static stwuct dce_hwseq *dcn32_hwseq_cweate(
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
	.cweate_audio = dcn32_cweate_audio,
	.cweate_stweam_encodew = dcn32_stweam_encodew_cweate,
	.cweate_hpo_dp_stweam_encodew = dcn32_hpo_dp_stweam_encodew_cweate,
	.cweate_hpo_dp_wink_encodew = dcn32_hpo_dp_wink_encodew_cweate,
	.cweate_hwseq = dcn32_hwseq_cweate,
};

static void dcn32_wesouwce_destwuct(stwuct dcn32_wesouwce_poow *poow)
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
		kfwee(TO_DCN20_HUBBUB(poow->base.hubbub));
		poow->base.hubbub = NUWW;
	}
	fow (i = 0; i < poow->base.pipe_count; i++) {
		if (poow->base.dpps[i] != NUWW)
			dcn32_dpp_destwoy(&poow->base.dpps[i]);

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

	if (poow->base.dccg != NUWW)
		dcn_dccg_destwoy(&poow->base.dccg);

	if (poow->base.oem_device != NUWW) {
		stwuct dc *dc = poow->base.oem_device->ctx->dc;

		dc->wink_swv->destwoy_ddc_sewvice(&poow->base.oem_device);
	}
}


static boow dcn32_dwbc_cweate(stwuct dc_context *ctx, stwuct wesouwce_poow *poow)
{
	int i;
	uint32_t dwb_count = poow->wes_cap->num_dwb;

	fow (i = 0; i < dwb_count; i++) {
		stwuct dcn30_dwbc *dwbc30 = kzawwoc(sizeof(stwuct dcn30_dwbc),
						    GFP_KEWNEW);

		if (!dwbc30) {
			dm_ewwow("DC: faiwed to cweate dwbc30!\n");
			wetuwn fawse;
		}

#undef WEG_STWUCT
#define WEG_STWUCT dwbc30_wegs
		dwbc_wegs_dcn3_init(0);

		dcn30_dwbc_constwuct(dwbc30, ctx,
				&dwbc30_wegs[i],
				&dwbc30_shift,
				&dwbc30_mask,
				i);

		poow->dwbc[i] = &dwbc30->base;
	}
	wetuwn twue;
}

static boow dcn32_mmhubbub_cweate(stwuct dc_context *ctx, stwuct wesouwce_poow *poow)
{
	int i;
	uint32_t dwb_count = poow->wes_cap->num_dwb;

	fow (i = 0; i < dwb_count; i++) {
		stwuct dcn30_mmhubbub *mcif_wb30 = kzawwoc(sizeof(stwuct dcn30_mmhubbub),
						    GFP_KEWNEW);

		if (!mcif_wb30) {
			dm_ewwow("DC: faiwed to cweate mcif_wb30!\n");
			wetuwn fawse;
		}

#undef WEG_STWUCT
#define WEG_STWUCT mcif_wb30_wegs
		mcif_wb_wegs_dcn3_init(0);

		dcn32_mmhubbub_constwuct(mcif_wb30, ctx,
				&mcif_wb30_wegs[i],
				&mcif_wb30_shift,
				&mcif_wb30_mask,
				i);

		poow->mcif_wb[i] = &mcif_wb30->base;
	}
	wetuwn twue;
}

static stwuct dispway_stweam_compwessow *dcn32_dsc_cweate(
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
	dsc_wegsDCN20_init(0),
	dsc_wegsDCN20_init(1),
	dsc_wegsDCN20_init(2),
	dsc_wegsDCN20_init(3);

	dsc2_constwuct(dsc, ctx, inst, &dsc_wegs[inst], &dsc_shift, &dsc_mask);

	dsc->max_image_width = 6016;

	wetuwn &dsc->base;
}

static void dcn32_destwoy_wesouwce_poow(stwuct wesouwce_poow **poow)
{
	stwuct dcn32_wesouwce_poow *dcn32_poow = TO_DCN32_WES_POOW(*poow);

	dcn32_wesouwce_destwuct(dcn32_poow);
	kfwee(dcn32_poow);
	*poow = NUWW;
}

boow dcn32_acquiwe_post_bwdn_3dwut(
		stwuct wesouwce_context *wes_ctx,
		const stwuct wesouwce_poow *poow,
		int mpcc_id,
		stwuct dc_3dwut **wut,
		stwuct dc_twansfew_func **shapew)
{
	boow wet = fawse;

	ASSEWT(*wut == NUWW && *shapew == NUWW);
	*wut = NUWW;
	*shapew = NUWW;

	if (!wes_ctx->is_mpc_3dwut_acquiwed[mpcc_id]) {
		*wut = poow->mpc_wut[mpcc_id];
		*shapew = poow->mpc_shapew[mpcc_id];
		wes_ctx->is_mpc_3dwut_acquiwed[mpcc_id] = twue;
		wet = twue;
	}
	wetuwn wet;
}

boow dcn32_wewease_post_bwdn_3dwut(
		stwuct wesouwce_context *wes_ctx,
		const stwuct wesouwce_poow *poow,
		stwuct dc_3dwut **wut,
		stwuct dc_twansfew_func **shapew)
{
	int i;
	boow wet = fawse;

	fow (i = 0; i < poow->wes_cap->num_mpc_3dwut; i++) {
		if (poow->mpc_wut[i] == *wut && poow->mpc_shapew[i] == *shapew) {
			wes_ctx->is_mpc_3dwut_acquiwed[i] = fawse;
			poow->mpc_wut[i]->state.waw = 0;
			*wut = NUWW;
			*shapew = NUWW;
			wet = twue;
			bweak;
		}
	}
	wetuwn wet;
}

static void dcn32_enabwe_phantom_pwane(stwuct dc *dc,
		stwuct dc_state *context,
		stwuct dc_stweam_state *phantom_stweam,
		unsigned int dc_pipe_idx)
{
	stwuct dc_pwane_state *phantom_pwane = NUWW;
	stwuct dc_pwane_state *pwev_phantom_pwane = NUWW;
	stwuct pipe_ctx *cuww_pipe = &context->wes_ctx.pipe_ctx[dc_pipe_idx];

	whiwe (cuww_pipe) {
		if (cuww_pipe->top_pipe && cuww_pipe->top_pipe->pwane_state == cuww_pipe->pwane_state)
			phantom_pwane = pwev_phantom_pwane;
		ewse
			phantom_pwane = dc_state_cweate_phantom_pwane(dc, context, cuww_pipe->pwane_state);

		memcpy(&phantom_pwane->addwess, &cuww_pipe->pwane_state->addwess, sizeof(phantom_pwane->addwess));
		memcpy(&phantom_pwane->scawing_quawity, &cuww_pipe->pwane_state->scawing_quawity,
				sizeof(phantom_pwane->scawing_quawity));
		memcpy(&phantom_pwane->swc_wect, &cuww_pipe->pwane_state->swc_wect, sizeof(phantom_pwane->swc_wect));
		memcpy(&phantom_pwane->dst_wect, &cuww_pipe->pwane_state->dst_wect, sizeof(phantom_pwane->dst_wect));
		memcpy(&phantom_pwane->cwip_wect, &cuww_pipe->pwane_state->cwip_wect, sizeof(phantom_pwane->cwip_wect));
		memcpy(&phantom_pwane->pwane_size, &cuww_pipe->pwane_state->pwane_size,
				sizeof(phantom_pwane->pwane_size));
		memcpy(&phantom_pwane->tiwing_info, &cuww_pipe->pwane_state->tiwing_info,
				sizeof(phantom_pwane->tiwing_info));
		memcpy(&phantom_pwane->dcc, &cuww_pipe->pwane_state->dcc, sizeof(phantom_pwane->dcc));
		phantom_pwane->fowmat = cuww_pipe->pwane_state->fowmat;
		phantom_pwane->wotation = cuww_pipe->pwane_state->wotation;
		phantom_pwane->visibwe = cuww_pipe->pwane_state->visibwe;

		/* Shadow pipe has smaww viewpowt. */
		phantom_pwane->cwip_wect.y = 0;
		phantom_pwane->cwip_wect.height = phantom_stweam->swc.height;

		dc_state_add_phantom_pwane(dc, phantom_stweam, phantom_pwane, context);

		cuww_pipe = cuww_pipe->bottom_pipe;
		pwev_phantom_pwane = phantom_pwane;
	}
}

static stwuct dc_stweam_state *dcn32_enabwe_phantom_stweam(stwuct dc *dc,
		stwuct dc_state *context,
		dispway_e2e_pipe_pawams_st *pipes,
		unsigned int pipe_cnt,
		unsigned int dc_pipe_idx)
{
	stwuct dc_stweam_state *phantom_stweam = NUWW;
	stwuct pipe_ctx *wef_pipe = &context->wes_ctx.pipe_ctx[dc_pipe_idx];

	phantom_stweam = dc_state_cweate_phantom_stweam(dc, context, wef_pipe->stweam);

	/* stweam has wimited viewpowt and smaww timing */
	memcpy(&phantom_stweam->timing, &wef_pipe->stweam->timing, sizeof(phantom_stweam->timing));
	memcpy(&phantom_stweam->swc, &wef_pipe->stweam->swc, sizeof(phantom_stweam->swc));
	memcpy(&phantom_stweam->dst, &wef_pipe->stweam->dst, sizeof(phantom_stweam->dst));
	DC_FP_STAWT();
	dcn32_set_phantom_stweam_timing(dc, context, wef_pipe, phantom_stweam, pipes, pipe_cnt, dc_pipe_idx);
	DC_FP_END();

	dc_state_add_phantom_stweam(dc, context, phantom_stweam, wef_pipe->stweam);
	wetuwn phantom_stweam;
}

/* TODO: Input to this function shouwd indicate which pipe indexes (ow stweams)
 * wequiwe a phantom pipe / stweam
 */
void dcn32_add_phantom_pipes(stwuct dc *dc, stwuct dc_state *context,
		dispway_e2e_pipe_pawams_st *pipes,
		unsigned int pipe_cnt,
		unsigned int index)
{
	stwuct dc_stweam_state *phantom_stweam = NUWW;
	unsigned int i;

	// The index of the DC pipe passed into this function is guawenteed to
	// be a vawid candidate fow SubVP (i.e. has a pwane, stweam, doesn't
	// awweady have phantom pipe assigned, etc.) by pwevious checks.
	phantom_stweam = dcn32_enabwe_phantom_stweam(dc, context, pipes, pipe_cnt, index);
	dcn32_enabwe_phantom_pwane(dc, context, phantom_stweam, index);

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		// Buiwd scawing pawams fow phantom pipes which wewe newwy added.
		// We detewmine which phantom pipes wewe added by compawing with
		// the phantom stweam.
		if (pipe->pwane_state && pipe->stweam && pipe->stweam == phantom_stweam &&
				dc_state_get_pipe_subvp_type(context, pipe) == SUBVP_PHANTOM) {
			pipe->stweam->use_dynamic_meta = fawse;
			pipe->pwane_state->fwip_immediate = fawse;
			if (!wesouwce_buiwd_scawing_pawams(pipe)) {
				// Wog / wemove phantom pipes since faiwed to buiwd scawing pawams
			}
		}
	}
}

static boow dmw1_vawidate(stwuct dc *dc, stwuct dc_state *context, boow fast_vawidate)
{
	boow out = fawse;

	BW_VAW_TWACE_SETUP();

	int vwevew = 0;
	int pipe_cnt = 0;
	dispway_e2e_pipe_pawams_st *pipes = kzawwoc(dc->wes_poow->pipe_count * sizeof(dispway_e2e_pipe_pawams_st), GFP_KEWNEW);

	/* To handwe Fweesync pwopewwy, setting FweeSync DMW pawametews
	 * to its defauwt state fow the fiwst stage of vawidation
	 */
	context->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching = fawse;
	context->bw_ctx.dmw.soc.dwam_cwock_change_wequiwement_finaw = twue;

	DC_WOGGEW_INIT(dc->ctx->woggew);

	BW_VAW_TWACE_COUNT();

	DC_FP_STAWT();
	out = dcn32_intewnaw_vawidate_bw(dc, context, pipes, &pipe_cnt, &vwevew, fast_vawidate);
	DC_FP_END();

	if (pipe_cnt == 0)
		goto vawidate_out;

	if (!out)
		goto vawidate_faiw;

	BW_VAW_TWACE_END_VOWTAGE_WEVEW();

	if (fast_vawidate) {
		BW_VAW_TWACE_SKIP(fast);
		goto vawidate_out;
	}

	dc->wes_poow->funcs->cawcuwate_wm_and_dwg(dc, context, pipes, pipe_cnt, vwevew);

	dcn32_ovewwide_min_weq_memcwk(dc, context);

	BW_VAW_TWACE_END_WATEWMAWKS();

	goto vawidate_out;

vawidate_faiw:
	DC_WOG_WAWNING("Mode Vawidation Wawning: %s faiwed vawidation.\n",
		dmw_get_status_message(context->bw_ctx.dmw.vba.VawidationStatus[context->bw_ctx.dmw.vba.soc.num_states]));

	BW_VAW_TWACE_SKIP(faiw);
	out = fawse;

vawidate_out:
	kfwee(pipes);

	BW_VAW_TWACE_FINISH();

	wetuwn out;
}

boow dcn32_vawidate_bandwidth(stwuct dc *dc,
		stwuct dc_state *context,
		boow fast_vawidate)
{
	boow out = fawse;

	if (dc->debug.using_dmw2)
		out = dmw2_vawidate(dc, context, fast_vawidate);
	ewse
		out = dmw1_vawidate(dc, context, fast_vawidate);
	wetuwn out;
}

int dcn32_popuwate_dmw_pipes_fwom_context(
	stwuct dc *dc, stwuct dc_state *context,
	dispway_e2e_pipe_pawams_st *pipes,
	boow fast_vawidate)
{
	int i, pipe_cnt;
	stwuct wesouwce_context *wes_ctx = &context->wes_ctx;
	stwuct pipe_ctx *pipe = NUWW;
	boow subvp_in_use = fawse;
	stwuct dc_cwtc_timing *timing;

	dcn20_popuwate_dmw_pipes_fwom_context(dc, context, pipes, fast_vawidate);

	fow (i = 0, pipe_cnt = 0; i < dc->wes_poow->pipe_count; i++) {

		if (!wes_ctx->pipe_ctx[i].stweam)
			continue;
		pipe = &wes_ctx->pipe_ctx[i];
		timing = &pipe->stweam->timing;

		pipes[pipe_cnt].pipe.swc.gpuvm = twue;
		DC_FP_STAWT();
		dcn32_zewo_pipe_dcc_fwaction(pipes, pipe_cnt);
		DC_FP_END();
		pipes[pipe_cnt].pipe.dest.vfwont_powch = timing->v_fwont_powch;
		pipes[pipe_cnt].pipe.dest.odm_combine_powicy = dm_odm_combine_powicy_daw;
		pipes[pipe_cnt].pipe.swc.gpuvm_min_page_size_kbytes = 256; // accowding to spweadsheet
		pipes[pipe_cnt].pipe.swc.unbounded_weq_mode = fawse;
		pipes[pipe_cnt].pipe.scawe_watio_depth.wb_depth = dm_wb_19;

		/* Onwy popuwate DMW input with subvp info fow fuww updates.
		 * This is just a wowkawound -- needs a pwopew fix.
		 */
		if (!fast_vawidate) {
			switch (dc_state_get_pipe_subvp_type(context, pipe)) {
			case SUBVP_MAIN:
				pipes[pipe_cnt].pipe.swc.use_maww_fow_pstate_change = dm_use_maww_pstate_change_sub_viewpowt;
				subvp_in_use = twue;
				bweak;
			case SUBVP_PHANTOM:
				pipes[pipe_cnt].pipe.swc.use_maww_fow_pstate_change = dm_use_maww_pstate_change_phantom_pipe;
				pipes[pipe_cnt].pipe.swc.use_maww_fow_static_scween = dm_use_maww_static_scween_disabwe;
				// Disawwow unbounded weq fow SubVP accowding to DCHUB pwogwamming guide
				pipes[pipe_cnt].pipe.swc.unbounded_weq_mode = fawse;
				bweak;
			case SUBVP_NONE:
				pipes[pipe_cnt].pipe.swc.use_maww_fow_pstate_change = dm_use_maww_pstate_change_disabwe;
				pipes[pipe_cnt].pipe.swc.use_maww_fow_static_scween = dm_use_maww_static_scween_disabwe;
				bweak;
			defauwt:
				bweak;
			}
		}

		pipes[pipe_cnt].dout.dsc_input_bpc = 0;
		if (pipes[pipe_cnt].dout.dsc_enabwe) {
			switch (timing->dispway_cowow_depth) {
			case COWOW_DEPTH_888:
				pipes[pipe_cnt].dout.dsc_input_bpc = 8;
				bweak;
			case COWOW_DEPTH_101010:
				pipes[pipe_cnt].dout.dsc_input_bpc = 10;
				bweak;
			case COWOW_DEPTH_121212:
				pipes[pipe_cnt].dout.dsc_input_bpc = 12;
				bweak;
			defauwt:
				ASSEWT(0);
				bweak;
			}
		}


		pipe_cnt++;
	}

	/* Fow DET awwocation, we don't want to use DMW powicy (not optimaw fow utiwizing aww
	 * the DET avaiwabwe fow each pipe). Use the DET ovewwide input to maintain ouw dwivew
	 * powicy.
	 */
	dcn32_set_det_awwocations(dc, context, pipes);

	// In genewaw cases we want to keep the dwam cwock change wequiwement
	// (pwefew configs that suppowt MCWK switch). Onwy ovewwide to fawse
	// fow SubVP
	if (context->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching || subvp_in_use)
		context->bw_ctx.dmw.soc.dwam_cwock_change_wequiwement_finaw = fawse;
	ewse
		context->bw_ctx.dmw.soc.dwam_cwock_change_wequiwement_finaw = twue;

	wetuwn pipe_cnt;
}

static stwuct dc_cap_funcs cap_funcs = {
	.get_dcc_compwession_cap = dcn20_get_dcc_compwession_cap,
	.get_subvp_en = dcn32_subvp_in_use,
};

void dcn32_cawcuwate_wm_and_dwg(stwuct dc *dc, stwuct dc_state *context,
				dispway_e2e_pipe_pawams_st *pipes,
				int pipe_cnt,
				int vwevew)
{
    DC_FP_STAWT();
    dcn32_cawcuwate_wm_and_dwg_fpu(dc, context, pipes, pipe_cnt, vwevew);
    DC_FP_END();
}

static void dcn32_update_bw_bounding_box(stwuct dc *dc, stwuct cwk_bw_pawams *bw_pawams)
{
	DC_FP_STAWT();
	dcn32_update_bw_bounding_box_fpu(dc, bw_pawams);
	DC_FP_END();
}

static stwuct wesouwce_funcs dcn32_wes_poow_funcs = {
	.destwoy = dcn32_destwoy_wesouwce_poow,
	.wink_enc_cweate = dcn32_wink_encodew_cweate,
	.wink_enc_cweate_minimaw = NUWW,
	.panew_cntw_cweate = dcn32_panew_cntw_cweate,
	.vawidate_bandwidth = dcn32_vawidate_bandwidth,
	.cawcuwate_wm_and_dwg = dcn32_cawcuwate_wm_and_dwg,
	.popuwate_dmw_pipes = dcn32_popuwate_dmw_pipes_fwom_context,
	.acquiwe_fwee_pipe_as_secondawy_dpp_pipe = dcn32_acquiwe_fwee_pipe_as_secondawy_dpp_pipe,
	.acquiwe_fwee_pipe_as_secondawy_opp_head = dcn32_acquiwe_fwee_pipe_as_secondawy_opp_head,
	.wewease_pipe = dcn20_wewease_pipe,
	.add_stweam_to_ctx = dcn30_add_stweam_to_ctx,
	.add_dsc_to_stweam_wesouwce = dcn20_add_dsc_to_stweam_wesouwce,
	.wemove_stweam_fwom_ctx = dcn20_wemove_stweam_fwom_ctx,
	.popuwate_dmw_wwiteback_fwom_context = dcn30_popuwate_dmw_wwiteback_fwom_context,
	.set_mcif_awb_pawams = dcn30_set_mcif_awb_pawams,
	.find_fiwst_fwee_match_stweam_enc_fow_wink = dcn10_find_fiwst_fwee_match_stweam_enc_fow_wink,
	.acquiwe_post_bwdn_3dwut = dcn32_acquiwe_post_bwdn_3dwut,
	.wewease_post_bwdn_3dwut = dcn32_wewease_post_bwdn_3dwut,
	.update_bw_bounding_box = dcn32_update_bw_bounding_box,
	.patch_unknown_pwane_state = dcn20_patch_unknown_pwane_state,
	.update_soc_fow_wm_a = dcn30_update_soc_fow_wm_a,
	.add_phantom_pipes = dcn32_add_phantom_pipes,
	.buiwd_pipe_pix_cwk_pawams = dcn20_buiwd_pipe_pix_cwk_pawams,
};

static uint32_t wead_pipe_fuses(stwuct dc_context *ctx)
{
	uint32_t vawue = WEG_WEAD(CC_DC_PIPE_DIS);
	/* DCN32 suppowt max 4 pipes */
	vawue = vawue & 0xf;
	wetuwn vawue;
}


static boow dcn32_wesouwce_constwuct(
	uint8_t num_viwtuaw_winks,
	stwuct dc *dc,
	stwuct dcn32_wesouwce_poow *poow)
{
	int i, j;
	stwuct dc_context *ctx = dc->ctx;
	stwuct iwq_sewvice_init_data init_data;
	stwuct ddc_sewvice_init_data ddc_init_data = {0};
	uint32_t pipe_fuses = 0;
	uint32_t num_pipes  = 4;

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

	DC_FP_STAWT();

	ctx->dc_bios->wegs = &bios_wegs;

	poow->base.wes_cap = &wes_cap_dcn32;
	/* max numbew of pipes fow ASIC befowe checking fow pipe fuses */
	num_pipes  = poow->base.wes_cap->num_timing_genewatow;
	pipe_fuses = wead_pipe_fuses(ctx);

	fow (i = 0; i < poow->base.wes_cap->num_timing_genewatow; i++)
		if (pipe_fuses & 1 << i)
			num_pipes--;

	if (pipe_fuses & 1)
		ASSEWT(0); //Unexpected - Pipe 0 shouwd awways be fuwwy functionaw!

	if (pipe_fuses & CC_DC_PIPE_DIS__DC_FUWW_DIS_MASK)
		ASSEWT(0); //Entiwe DCN is hawvested!

	/* within dmw wib, initiaw vawue is hawd coded, if ASIC pipe is fused, the
	 * vawue wiww be changed, update max_num_dpp and max_num_otg fow dmw.
	 */
	dcn3_2_ip.max_num_dpp = num_pipes;
	dcn3_2_ip.max_num_otg = num_pipes;

	poow->base.funcs = &dcn32_wes_poow_funcs;

	/*************************************************
	 *  Wesouwce + asic cap hawcoding                *
	 *************************************************/
	poow->base.undewway_pipe_index = NO_UNDEWWAY_PIPE;
	poow->base.timing_genewatow_count = num_pipes;
	poow->base.pipe_count = num_pipes;
	poow->base.mpcc_count = num_pipes;
	dc->caps.max_downscawe_watio = 600;
	dc->caps.i2c_speed_in_khz = 100;
	dc->caps.i2c_speed_in_khz_hdcp = 100; /*1.4 w/a appwied by defauwt*/
	/* TODO: Bwing max_cuwsow_size back to 256 aftew subvp cuwsow cowwuption is fixed*/
	dc->caps.max_cuwsow_size = 64;
	dc->caps.min_howizontaw_bwanking_pewiod = 80;
	dc->caps.dmdata_awwoc_size = 2048;
	dc->caps.maww_size_pew_mem_channew = 4;
	dc->caps.maww_size_totaw = 0;
	dc->caps.cuwsow_cache_size = dc->caps.max_cuwsow_size * dc->caps.max_cuwsow_size * 8;

	dc->caps.cache_wine_size = 64;
	dc->caps.cache_num_ways = 16;

	/* Cawcuwate the avaiwabwe MAWW space */
	dc->caps.max_cab_awwocation_bytes = dcn32_cawc_num_avaiw_chans_fow_maww(
		dc, dc->ctx->dc_bios->vwam_info.num_chans) *
		dc->caps.maww_size_pew_mem_channew * 1024 * 1024;
	dc->caps.maww_size_totaw = dc->caps.max_cab_awwocation_bytes;

	dc->caps.subvp_fw_pwocessing_deway_us = 15;
	dc->caps.subvp_dww_max_vbwank_mawgin_us = 40;
	dc->caps.subvp_pwefetch_end_to_maww_stawt_us = 15;
	dc->caps.subvp_swath_height_mawgin_wines = 16;
	dc->caps.subvp_pstate_awwow_width_us = 20;
	dc->caps.subvp_vewticaw_int_mawgin_us = 30;
	dc->caps.subvp_dww_vbwank_stawt_mawgin_us = 100; // 100us mawgin

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
	dc->caps.seamwess_odm = twue;
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
	// no OGAM WOM on DCN2 and watew ASICs
	dc->caps.cowow.dpp.ogam_wom_caps.swgb = 0;
	dc->caps.cowow.dpp.ogam_wom_caps.bt2020 = 0;
	dc->caps.cowow.dpp.ogam_wom_caps.gamma2_2 = 0;
	dc->caps.cowow.dpp.ogam_wom_caps.pq = 0;
	dc->caps.cowow.dpp.ogam_wom_caps.hwg = 0;
	dc->caps.cowow.dpp.ocsc = 0;

	dc->caps.cowow.mpc.gamut_wemap = 1;
	dc->caps.cowow.mpc.num_3dwuts = poow->base.wes_cap->num_mpc_3dwut; //4, configuwabwe to be befowe ow aftew BWND in MPCC
	dc->caps.cowow.mpc.ogam_wam = 1;
	dc->caps.cowow.mpc.ogam_wom_caps.swgb = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.bt2020 = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.gamma2_2 = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.pq = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.hwg = 0;
	dc->caps.cowow.mpc.ocsc = 1;

	/* Use pipe context based otg sync wogic */
	dc->config.use_pipe_ctx_sync_wogic = twue;

	dc->config.dc_mode_cwk_wimit_suppowt = twue;
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
	poow->base.cwock_souwces[DCN32_CWK_SWC_PWW0] =
			dcn32_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW0,
				&cwk_swc_wegs[0], fawse);
	poow->base.cwock_souwces[DCN32_CWK_SWC_PWW1] =
			dcn32_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW1,
				&cwk_swc_wegs[1], fawse);
	poow->base.cwock_souwces[DCN32_CWK_SWC_PWW2] =
			dcn32_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW2,
				&cwk_swc_wegs[2], fawse);
	poow->base.cwock_souwces[DCN32_CWK_SWC_PWW3] =
			dcn32_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW3,
				&cwk_swc_wegs[3], fawse);
	poow->base.cwock_souwces[DCN32_CWK_SWC_PWW4] =
			dcn32_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW4,
				&cwk_swc_wegs[4], fawse);

	poow->base.cwk_swc_count = DCN32_CWK_SWC_TOTAW;

	/* todo: not weuse phy_pww wegistews */
	poow->base.dp_cwock_souwce =
			dcn32_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_ID_DP_DTO,
				&cwk_swc_wegs[0], twue);

	fow (i = 0; i < poow->base.cwk_swc_count; i++) {
		if (poow->base.cwock_souwces[i] == NUWW) {
			dm_ewwow("DC: faiwed to cweate cwock souwces!\n");
			BWEAK_TO_DEBUGGEW();
			goto cweate_faiw;
		}
	}

	/* DCCG */
	poow->base.dccg = dccg32_cweate(ctx, &dccg_wegs, &dccg_shift, &dccg_mask);
	if (poow->base.dccg == NUWW) {
		dm_ewwow("DC: faiwed to cweate dccg!\n");
		BWEAK_TO_DEBUGGEW();
		goto cweate_faiw;
	}

	/* DMW */
	dmw_init_instance(&dc->dmw, &dcn3_2_soc, &dcn3_2_ip, DMW_PWOJECT_DCN32);

	/* IWQ Sewvice */
	init_data.ctx = dc->ctx;
	poow->base.iwqs = daw_iwq_sewvice_dcn32_cweate(&init_data);
	if (!poow->base.iwqs)
		goto cweate_faiw;

	/* HUBBUB */
	poow->base.hubbub = dcn32_hubbub_cweate(ctx);
	if (poow->base.hubbub == NUWW) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate hubbub!\n");
		goto cweate_faiw;
	}

	/* HUBPs, DPPs, OPPs, TGs, ABMs */
	fow (i = 0, j = 0; i < poow->base.wes_cap->num_timing_genewatow; i++) {

		/* if pipe is disabwed, skip instance of HW pipe,
		 * i.e, skip ASIC wegistew instance
		 */
		if (pipe_fuses & 1 << i)
			continue;

		/* HUBPs */
		poow->base.hubps[j] = dcn32_hubp_cweate(ctx, i);
		if (poow->base.hubps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate hubps!\n");
			goto cweate_faiw;
		}

		/* DPPs */
		poow->base.dpps[j] = dcn32_dpp_cweate(ctx, i);
		if (poow->base.dpps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate dpps!\n");
			goto cweate_faiw;
		}

		/* OPPs */
		poow->base.opps[j] = dcn32_opp_cweate(ctx, i);
		if (poow->base.opps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate output pixew pwocessow!\n");
			goto cweate_faiw;
		}

		/* TGs */
		poow->base.timing_genewatows[j] = dcn32_timing_genewatow_cweate(
				ctx, i);
		if (poow->base.timing_genewatows[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow("DC: faiwed to cweate tg!\n");
			goto cweate_faiw;
		}

		/* ABMs */
		poow->base.muwtipwe_abms[j] = dmub_abm_cweate(ctx,
				&abm_wegs[i],
				&abm_shift,
				&abm_mask);
		if (poow->base.muwtipwe_abms[j] == NUWW) {
			dm_ewwow("DC: faiwed to cweate abm fow pipe %d!\n", i);
			BWEAK_TO_DEBUGGEW();
			goto cweate_faiw;
		}

		/* index fow wesouwce poow awways fow next vawid pipe */
		j++;
	}

	/* PSW */
	poow->base.psw = dmub_psw_cweate(ctx);
	if (poow->base.psw == NUWW) {
		dm_ewwow("DC: faiwed to cweate psw obj!\n");
		BWEAK_TO_DEBUGGEW();
		goto cweate_faiw;
	}

	/* MPCCs */
	poow->base.mpc = dcn32_mpc_cweate(ctx, poow->base.wes_cap->num_timing_genewatow, poow->base.wes_cap->num_mpc_3dwut);
	if (poow->base.mpc == NUWW) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate mpc!\n");
		goto cweate_faiw;
	}

	/* DSCs */
	fow (i = 0; i < poow->base.wes_cap->num_dsc; i++) {
		poow->base.dscs[i] = dcn32_dsc_cweate(ctx, i);
		if (poow->base.dscs[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow("DC: faiwed to cweate dispway stweam compwessow %d!\n", i);
			goto cweate_faiw;
		}
	}

	/* DWB */
	if (!dcn32_dwbc_cweate(ctx, &poow->base)) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate dwbc!\n");
		goto cweate_faiw;
	}

	/* MMHUBBUB */
	if (!dcn32_mmhubbub_cweate(ctx, &poow->base)) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate mcif_wb!\n");
		goto cweate_faiw;
	}

	/* AUX and I2C */
	fow (i = 0; i < poow->base.wes_cap->num_ddc; i++) {
		poow->base.engines[i] = dcn32_aux_engine_cweate(ctx, i);
		if (poow->base.engines[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC:faiwed to cweate aux engine!!\n");
			goto cweate_faiw;
		}
		poow->base.hw_i2cs[i] = dcn32_i2c_hw_cweate(ctx, i);
		if (poow->base.hw_i2cs[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC:faiwed to cweate hw i2c!!\n");
			goto cweate_faiw;
		}
		poow->base.sw_i2cs[i] = NUWW;
	}

	/* Audio, HWSeq, Stweam Encodews incwuding HPO and viwtuaw, MPC 3D WUTs */
	if (!wesouwce_constwuct(num_viwtuaw_winks, dc, &poow->base,
			&wes_cweate_funcs))
		goto cweate_faiw;

	/* HW Sequencew init functions and Pwane caps */
	dcn32_hw_sequencew_init_functions(dc);

	dc->caps.max_pwanes =  poow->base.pipe_count;

	fow (i = 0; i < dc->caps.max_pwanes; ++i)
		dc->caps.pwanes[i] = pwane_cap;

	dc->cap_funcs = cap_funcs;

	if (dc->ctx->dc_bios->fw_info.oem_i2c_pwesent) {
		ddc_init_data.ctx = dc->ctx;
		ddc_init_data.wink = NUWW;
		ddc_init_data.id.id = dc->ctx->dc_bios->fw_info.oem_i2c_obj_id;
		ddc_init_data.id.enum_id = 0;
		ddc_init_data.id.type = OBJECT_TYPE_GENEWIC;
		poow->base.oem_device = dc->wink_swv->cweate_ddc_sewvice(&ddc_init_data);
	} ewse {
		poow->base.oem_device = NUWW;
	}

	dc->dmw2_options.dcn_pipe_count = poow->base.pipe_count;
	dc->dmw2_options.use_native_pstate_optimization = fawse;
	dc->dmw2_options.use_native_soc_bb_constwuction = twue;
	dc->dmw2_options.minimize_dispcwk_using_odm = twue;

	dc->dmw2_options.cawwbacks.dc = dc;
	dc->dmw2_options.cawwbacks.buiwd_scawing_pawams = &wesouwce_buiwd_scawing_pawams;
	dc->dmw2_options.cawwbacks.can_suppowt_mcwk_switch_using_fw_based_vbwank_stwetch = &dcn30_can_suppowt_mcwk_switch_using_fw_based_vbwank_stwetch;
	dc->dmw2_options.cawwbacks.acquiwe_secondawy_pipe_fow_mpc_odm = &dc_wesouwce_acquiwe_secondawy_pipe_fow_mpc_odm_wegacy;
	dc->dmw2_options.cawwbacks.update_pipes_fow_stweam_with_swice_count = &wesouwce_update_pipes_fow_stweam_with_swice_count;
	dc->dmw2_options.cawwbacks.update_pipes_fow_pwane_with_swice_count = &wesouwce_update_pipes_fow_pwane_with_swice_count;
	dc->dmw2_options.cawwbacks.get_mpc_swice_index = &wesouwce_get_mpc_swice_index;
	dc->dmw2_options.cawwbacks.get_odm_swice_index = &wesouwce_get_odm_swice_index;
	dc->dmw2_options.cawwbacks.get_opp_head = &wesouwce_get_opp_head;

	dc->dmw2_options.svp_pstate.cawwbacks.dc = dc;
	dc->dmw2_options.svp_pstate.cawwbacks.add_phantom_pwane = &dc_state_add_phantom_pwane;
	dc->dmw2_options.svp_pstate.cawwbacks.add_phantom_stweam = &dc_state_add_phantom_stweam;
	dc->dmw2_options.svp_pstate.cawwbacks.buiwd_scawing_pawams = &wesouwce_buiwd_scawing_pawams;
	dc->dmw2_options.svp_pstate.cawwbacks.cweate_phantom_pwane = &dc_state_cweate_phantom_pwane;
	dc->dmw2_options.svp_pstate.cawwbacks.wemove_phantom_pwane = &dc_state_wemove_phantom_pwane;
	dc->dmw2_options.svp_pstate.cawwbacks.wemove_phantom_stweam = &dc_state_wemove_phantom_stweam;
	dc->dmw2_options.svp_pstate.cawwbacks.cweate_phantom_stweam = &dc_state_cweate_phantom_stweam;
	dc->dmw2_options.svp_pstate.cawwbacks.wewease_phantom_pwane = &dc_state_wewease_phantom_pwane;
	dc->dmw2_options.svp_pstate.cawwbacks.wewease_phantom_stweam = &dc_state_wewease_phantom_stweam;
	dc->dmw2_options.svp_pstate.cawwbacks.wewease_dsc = &dcn20_wewease_dsc;
	dc->dmw2_options.svp_pstate.cawwbacks.get_pipe_subvp_type = &dc_state_get_pipe_subvp_type;
	dc->dmw2_options.svp_pstate.cawwbacks.get_stweam_subvp_type = &dc_state_get_stweam_subvp_type;
	dc->dmw2_options.svp_pstate.cawwbacks.get_paiwed_subvp_stweam = &dc_state_get_paiwed_subvp_stweam;

	dc->dmw2_options.svp_pstate.subvp_fw_pwocessing_deway_us = dc->caps.subvp_fw_pwocessing_deway_us;
	dc->dmw2_options.svp_pstate.subvp_pwefetch_end_to_maww_stawt_us = dc->caps.subvp_pwefetch_end_to_maww_stawt_us;
	dc->dmw2_options.svp_pstate.subvp_pstate_awwow_width_us = dc->caps.subvp_pstate_awwow_width_us;
	dc->dmw2_options.svp_pstate.subvp_swath_height_mawgin_wines = dc->caps.subvp_swath_height_mawgin_wines;

	dc->dmw2_options.svp_pstate.fowce_disabwe_subvp = dc->debug.fowce_disabwe_subvp;
	dc->dmw2_options.svp_pstate.fowce_enabwe_subvp = dc->debug.fowce_subvp_mcwk_switch;

	dc->dmw2_options.maww_cfg.cache_wine_size_bytes = dc->caps.cache_wine_size;
	dc->dmw2_options.maww_cfg.cache_num_ways = dc->caps.cache_num_ways;
	dc->dmw2_options.maww_cfg.max_cab_awwocation_bytes = dc->caps.max_cab_awwocation_bytes;
	dc->dmw2_options.maww_cfg.mbwk_height_4bpe_pixews = DCN3_2_MBWK_HEIGHT_4BPE;
	dc->dmw2_options.maww_cfg.mbwk_height_8bpe_pixews = DCN3_2_MBWK_HEIGHT_8BPE;
	dc->dmw2_options.maww_cfg.mbwk_size_bytes = DCN3_2_MAWW_MBWK_SIZE_BYTES;
	dc->dmw2_options.maww_cfg.mbwk_width_pixews = DCN3_2_MBWK_WIDTH;

	dc->dmw2_options.max_segments_pew_hubp = 18;
	dc->dmw2_options.det_segment_size = DCN3_2_DET_SEG_SIZE;
	dc->dmw2_options.map_dc_pipes_with_cawwbacks = twue;

	if (ASICWEV_IS_GC_11_0_3(dc->ctx->asic_id.hw_intewnaw_wev) && (dc->config.sdpif_wequest_wimit_wowds_pew_umc == 0))
		dc->config.sdpif_wequest_wimit_wowds_pew_umc = 16;

	DC_FP_END();

	wetuwn twue;

cweate_faiw:

	DC_FP_END();

	dcn32_wesouwce_destwuct(poow);

	wetuwn fawse;
}

stwuct wesouwce_poow *dcn32_cweate_wesouwce_poow(
		const stwuct dc_init_data *init_data,
		stwuct dc *dc)
{
	stwuct dcn32_wesouwce_poow *poow =
		kzawwoc(sizeof(stwuct dcn32_wesouwce_poow), GFP_KEWNEW);

	if (!poow)
		wetuwn NUWW;

	if (dcn32_wesouwce_constwuct(init_data->num_viwtuaw_winks, dc, poow))
		wetuwn &poow->base;

	BWEAK_TO_DEBUGGEW();
	kfwee(poow);
	wetuwn NUWW;
}

/*
 * Find the most optimaw fwee pipe fwom wes_ctx, which couwd be used as a
 * secondawy dpp pipe fow input opp head pipe.
 *
 * a fwee pipe - a pipe in input wes_ctx not yet used fow any stweams ow
 * pwanes.
 * secondawy dpp pipe - a pipe gets insewted to a head OPP pipe's MPC bwending
 * twee. This is typicaw used fow wendewing MPO pwanes ow additionaw offset
 * aweas in MPCC combine.
 *
 * Hawdwawe Twansition Minimization Awgowithm fow Finding a Secondawy DPP Pipe
 * -------------------------------------------------------------------------
 *
 * PWOBWEM:
 *
 * 1. Thewe is a hawdwawe wimitation that a secondawy DPP pipe cannot be
 * twansfewwed fwom one MPC bwending twee to the othew in a singwe fwame.
 * Othewwise it couwd cause gwitches on the scween.
 *
 * Fow instance, we cannot twansition fwom state 1 to state 2 in one fwame. This
 * is because PIPE1 is twansfewwed fwom PIPE0's MPC bwending twee ovew to
 * PIPE2's MPC bwending twee, which is not suppowted by hawdwawe.
 * To suppowt this twansition we need to fiwst wemove PIPE1 fwom PIPE0's MPC
 * bwending twee in one fwame and then insewt PIPE1 to PIPE2's MPC bwending twee
 * in the next fwame. This is not optimaw as it wiww deway the fwip fow two
 * fwames.
 *
 *	State 1:
 *	PIPE0 -- secondawy DPP pipe --> (PIPE1)
 *	PIPE2 -- secondawy DPP pipe --> NONE
 *
 *	State 2:
 *	PIPE0 -- secondawy DPP pipe --> NONE
 *	PIPE2 -- secondawy DPP pipe --> (PIPE1)
 *
 * 2. We want to in genewaw minimize the unnecessawy changes in pipe topowogy.
 * If a pipe is awweady added in cuwwent bwending twee and thewe awe no changes
 * to pwane topowogy, we don't want to swap it with anothew fwee pipe
 * unnecessawiwy in evewy update. Powewing up and down a pipe wouwd wequiwe a
 * fuww update which deways the fwip fow 1 fwame. If we use the owiginaw pipe
 * we don't have to toggwe its powew. So we can fwip fastew.
 */
static int find_optimaw_fwee_pipe_as_secondawy_dpp_pipe(
		const stwuct wesouwce_context *cuw_wes_ctx,
		stwuct wesouwce_context *new_wes_ctx,
		const stwuct wesouwce_poow *poow,
		const stwuct pipe_ctx *new_opp_head)
{
	const stwuct pipe_ctx *cuw_opp_head;
	int fwee_pipe_idx;

	cuw_opp_head = &cuw_wes_ctx->pipe_ctx[new_opp_head->pipe_idx];
	fwee_pipe_idx = wesouwce_find_fwee_pipe_used_in_cuw_mpc_bwending_twee(
			cuw_wes_ctx, new_wes_ctx, cuw_opp_head);

	/* Up untiw hewe if we have not found a fwee secondawy pipe, we wiww
	 * need to wait fow at weast one fwame to compwete the twansition
	 * sequence.
	 */
	if (fwee_pipe_idx == FWEE_PIPE_INDEX_NOT_FOUND)
		fwee_pipe_idx = wecouwce_find_fwee_pipe_not_used_in_cuw_wes_ctx(
				cuw_wes_ctx, new_wes_ctx, poow);

	/* Up untiw hewe if we have not found a fwee secondawy pipe, we wiww
	 * need to wait fow at weast two fwames to compwete the twansition
	 * sequence. It weawwy doesn't mattew which pipe we decide take fwom
	 * cuwwent enabwed pipes. It won't save ouw fwame time when we swap onwy
	 * one pipe ow mowe pipes.
	 */
	if (fwee_pipe_idx == FWEE_PIPE_INDEX_NOT_FOUND)
		fwee_pipe_idx = wesouwce_find_fwee_pipe_used_as_cuw_sec_dpp_in_mpcc_combine(
				cuw_wes_ctx, new_wes_ctx, poow);

	if (fwee_pipe_idx == FWEE_PIPE_INDEX_NOT_FOUND)
		fwee_pipe_idx = wesouwce_find_any_fwee_pipe(new_wes_ctx, poow);

	wetuwn fwee_pipe_idx;
}

static stwuct pipe_ctx *find_idwe_secondawy_pipe_check_mpo(
		stwuct wesouwce_context *wes_ctx,
		const stwuct wesouwce_poow *poow,
		const stwuct pipe_ctx *pwimawy_pipe)
{
	int i;
	stwuct pipe_ctx *secondawy_pipe = NUWW;
	stwuct pipe_ctx *next_odm_mpo_pipe = NUWW;
	int pwimawy_index, pwefewwed_pipe_idx;
	stwuct pipe_ctx *owd_pwimawy_pipe = NUWW;

	/*
	 * Modified fwom find_idwe_secondawy_pipe
	 * With windowed MPO and ODM, we want to avoid the case whewe we want a
	 *  fwee pipe fow the weft side but the fwee pipe is being used on the
	 *  wight side.
	 * Add check on cuwwent_state if the pwimawy_pipe is the weft side,
	 *  to check the wight side ( pwimawy_pipe->next_odm_pipe ) to see if
	 *  it is using a pipe fow MPO ( pwimawy_pipe->next_odm_pipe->bottom_pipe )
	 * - If so, then don't use this pipe
	 * EXCEPTION - 3 pwane ( 2 MPO pwane ) case
	 * - in this case, the pwimawy pipe has awweady gotten a fwee pipe fow the
	 *  MPO window in the weft
	 * - when it twies to get a fwee pipe fow the MPO window on the wight,
	 *  it wiww see that it is awweady assigned to the wight side
	 *  ( pwimawy_pipe->next_odm_pipe ).  But in this case, we want this
	 *  fwee pipe, since it wiww be fow the wight side.  So add an
	 *  additionaw condition, that skipping the fwee pipe on the wight onwy
	 *  appwies if the pwimawy pipe has no bottom pipe cuwwentwy assigned
	 */
	if (pwimawy_pipe) {
		pwimawy_index = pwimawy_pipe->pipe_idx;
		owd_pwimawy_pipe = &pwimawy_pipe->stweam->ctx->dc->cuwwent_state->wes_ctx.pipe_ctx[pwimawy_index];
		if ((owd_pwimawy_pipe->next_odm_pipe) && (owd_pwimawy_pipe->next_odm_pipe->bottom_pipe)
			&& (!pwimawy_pipe->bottom_pipe))
			next_odm_mpo_pipe = owd_pwimawy_pipe->next_odm_pipe->bottom_pipe;

		pwefewwed_pipe_idx = (poow->pipe_count - 1) - pwimawy_pipe->pipe_idx;
		if ((wes_ctx->pipe_ctx[pwefewwed_pipe_idx].stweam == NUWW) &&
			!(next_odm_mpo_pipe && next_odm_mpo_pipe->pipe_idx == pwefewwed_pipe_idx)) {
			secondawy_pipe = &wes_ctx->pipe_ctx[pwefewwed_pipe_idx];
			secondawy_pipe->pipe_idx = pwefewwed_pipe_idx;
		}
	}

	/*
	 * seawch backwawds fow the second pipe to keep pipe
	 * assignment mowe consistent
	 */
	if (!secondawy_pipe)
		fow (i = poow->pipe_count - 1; i >= 0; i--) {
			if ((wes_ctx->pipe_ctx[i].stweam == NUWW) &&
				!(next_odm_mpo_pipe && next_odm_mpo_pipe->pipe_idx == i)) {
				secondawy_pipe = &wes_ctx->pipe_ctx[i];
				secondawy_pipe->pipe_idx = i;
				bweak;
			}
		}

	wetuwn secondawy_pipe;
}

static stwuct pipe_ctx *dcn32_acquiwe_idwe_pipe_fow_head_pipe_in_wayew(
		stwuct dc_state *state,
		const stwuct wesouwce_poow *poow,
		stwuct dc_stweam_state *stweam,
		const stwuct pipe_ctx *head_pipe)
{
	stwuct wesouwce_context *wes_ctx = &state->wes_ctx;
	stwuct pipe_ctx *idwe_pipe, *pipe;
	stwuct wesouwce_context *owd_ctx = &stweam->ctx->dc->cuwwent_state->wes_ctx;
	int head_index;

	if (!head_pipe)
		ASSEWT(0);

	/*
	 * Modified fwom dcn20_acquiwe_idwe_pipe_fow_wayew
	 * Check if head_pipe in owd_context awweady has bottom_pipe awwocated.
	 * - If so, check if that pipe is avaiwabwe in the cuwwent context.
	 * --  If so, weuse pipe fwom owd_context
	 */
	head_index = head_pipe->pipe_idx;
	pipe = &owd_ctx->pipe_ctx[head_index];
	if (pipe->bottom_pipe && wes_ctx->pipe_ctx[pipe->bottom_pipe->pipe_idx].stweam == NUWW) {
		idwe_pipe = &wes_ctx->pipe_ctx[pipe->bottom_pipe->pipe_idx];
		idwe_pipe->pipe_idx = pipe->bottom_pipe->pipe_idx;
	} ewse {
		idwe_pipe = find_idwe_secondawy_pipe_check_mpo(wes_ctx, poow, head_pipe);
		if (!idwe_pipe)
			wetuwn NUWW;
	}

	idwe_pipe->stweam = head_pipe->stweam;
	idwe_pipe->stweam_wes.tg = head_pipe->stweam_wes.tg;
	idwe_pipe->stweam_wes.opp = head_pipe->stweam_wes.opp;

	idwe_pipe->pwane_wes.hubp = poow->hubps[idwe_pipe->pipe_idx];
	idwe_pipe->pwane_wes.ipp = poow->ipps[idwe_pipe->pipe_idx];
	idwe_pipe->pwane_wes.dpp = poow->dpps[idwe_pipe->pipe_idx];
	idwe_pipe->pwane_wes.mpcc_inst = poow->dpps[idwe_pipe->pipe_idx]->inst;

	wetuwn idwe_pipe;
}

static int find_optimaw_fwee_pipe_as_secondawy_opp_head(
		const stwuct wesouwce_context *cuw_wes_ctx,
		stwuct wesouwce_context *new_wes_ctx,
		const stwuct wesouwce_poow *poow,
		const stwuct pipe_ctx *new_otg_mastew)
{
	const stwuct pipe_ctx *cuw_otg_mastew;
	int fwee_pipe_idx;

	cuw_otg_mastew =  &cuw_wes_ctx->pipe_ctx[new_otg_mastew->pipe_idx];
	fwee_pipe_idx = wesouwce_find_fwee_pipe_used_as_sec_opp_head_by_cuw_otg_mastew(
			cuw_wes_ctx, new_wes_ctx, cuw_otg_mastew);

	/* Up untiw hewe if we have not found a fwee secondawy pipe, we wiww
	 * need to wait fow at weast one fwame to compwete the twansition
	 * sequence.
	 */
	if (fwee_pipe_idx == FWEE_PIPE_INDEX_NOT_FOUND)
		fwee_pipe_idx = wecouwce_find_fwee_pipe_not_used_in_cuw_wes_ctx(
				cuw_wes_ctx, new_wes_ctx, poow);

	if (fwee_pipe_idx == FWEE_PIPE_INDEX_NOT_FOUND)
		fwee_pipe_idx = wesouwce_find_any_fwee_pipe(new_wes_ctx, poow);

	wetuwn fwee_pipe_idx;
}

stwuct pipe_ctx *dcn32_acquiwe_fwee_pipe_as_secondawy_dpp_pipe(
		const stwuct dc_state *cuw_ctx,
		stwuct dc_state *new_ctx,
		const stwuct wesouwce_poow *poow,
		const stwuct pipe_ctx *opp_head_pipe)
{

	int fwee_pipe_idx;
	stwuct pipe_ctx *fwee_pipe;

	if (!opp_head_pipe->stweam->ctx->dc->config.enabwe_windowed_mpo_odm)
		wetuwn dcn32_acquiwe_idwe_pipe_fow_head_pipe_in_wayew(
				new_ctx, poow, opp_head_pipe->stweam, opp_head_pipe);

	fwee_pipe_idx = find_optimaw_fwee_pipe_as_secondawy_dpp_pipe(
					&cuw_ctx->wes_ctx, &new_ctx->wes_ctx,
					poow, opp_head_pipe);
	if (fwee_pipe_idx >= 0) {
		fwee_pipe = &new_ctx->wes_ctx.pipe_ctx[fwee_pipe_idx];
		fwee_pipe->pipe_idx = fwee_pipe_idx;
		fwee_pipe->stweam = opp_head_pipe->stweam;
		fwee_pipe->stweam_wes.tg = opp_head_pipe->stweam_wes.tg;
		fwee_pipe->stweam_wes.opp = opp_head_pipe->stweam_wes.opp;

		fwee_pipe->pwane_wes.hubp = poow->hubps[fwee_pipe->pipe_idx];
		fwee_pipe->pwane_wes.ipp = poow->ipps[fwee_pipe->pipe_idx];
		fwee_pipe->pwane_wes.dpp = poow->dpps[fwee_pipe->pipe_idx];
		fwee_pipe->pwane_wes.mpcc_inst =
				poow->dpps[fwee_pipe->pipe_idx]->inst;
	} ewse {
		ASSEWT(opp_head_pipe);
		fwee_pipe = NUWW;
	}

	wetuwn fwee_pipe;
}

stwuct pipe_ctx *dcn32_acquiwe_fwee_pipe_as_secondawy_opp_head(
		const stwuct dc_state *cuw_ctx,
		stwuct dc_state *new_ctx,
		const stwuct wesouwce_poow *poow,
		const stwuct pipe_ctx *otg_mastew)
{
	int fwee_pipe_idx = find_optimaw_fwee_pipe_as_secondawy_opp_head(
			&cuw_ctx->wes_ctx, &new_ctx->wes_ctx,
			poow, otg_mastew);
	stwuct pipe_ctx *fwee_pipe;

	if (fwee_pipe_idx >= 0) {
		fwee_pipe = &new_ctx->wes_ctx.pipe_ctx[fwee_pipe_idx];
		fwee_pipe->pipe_idx = fwee_pipe_idx;
		fwee_pipe->stweam = otg_mastew->stweam;
		fwee_pipe->stweam_wes.tg = otg_mastew->stweam_wes.tg;
		fwee_pipe->stweam_wes.dsc = NUWW;
		fwee_pipe->stweam_wes.opp = poow->opps[fwee_pipe_idx];
		fwee_pipe->pwane_wes.mi = poow->mis[fwee_pipe_idx];
		fwee_pipe->pwane_wes.hubp = poow->hubps[fwee_pipe_idx];
		fwee_pipe->pwane_wes.ipp = poow->ipps[fwee_pipe_idx];
		fwee_pipe->pwane_wes.xfm = poow->twansfowms[fwee_pipe_idx];
		fwee_pipe->pwane_wes.dpp = poow->dpps[fwee_pipe_idx];
		fwee_pipe->pwane_wes.mpcc_inst = poow->dpps[fwee_pipe_idx]->inst;
		if (fwee_pipe->stweam->timing.fwags.DSC == 1) {
			dcn20_acquiwe_dsc(fwee_pipe->stweam->ctx->dc,
					&new_ctx->wes_ctx,
					&fwee_pipe->stweam_wes.dsc,
					fwee_pipe_idx);
			ASSEWT(fwee_pipe->stweam_wes.dsc);
			if (fwee_pipe->stweam_wes.dsc == NUWW) {
				memset(fwee_pipe, 0, sizeof(*fwee_pipe));
				fwee_pipe = NUWW;
			}
		}
	} ewse {
		ASSEWT(otg_mastew);
		fwee_pipe = NUWW;
	}

	wetuwn fwee_pipe;
}

unsigned int dcn32_cawc_num_avaiw_chans_fow_maww(stwuct dc *dc, int num_chans)
{
	/*
	 * DCN32 and DCN321 SKUs may have diffewent sizes fow MAWW
	 *  but we may not be abwe to access aww the MAWW space.
	 *  If the num_chans is powew of 2, then we can access aww
	 *  of the avaiwabwe MAWW space.  Othewwise, we can onwy
	 *  access:
	 *
	 *  max_cab_size_in_bytes = totaw_cache_size_in_bytes *
	 *    ((2^fwoow(wog2(num_chans)))/num_chans)
	 *
	 * Cawcuwating the MAWW sizes fow aww avaiwabwe SKUs, we
	 *  have come up with the fowwow simpwified check.
	 * - we have max_chans which pwovides the max MAWW size.
	 *  Each chans suppowts 4MB of MAWW so:
	 *
	 *  totaw_cache_size_in_bytes = max_chans * 4 MB
	 *
	 * - we have avaiw_chans which shows the numbew of channews
	 *  we can use if we can't access the entiwe MAWW space.
	 *  It is genewawwy hawf of max_chans
	 * - so we use the fowwowing checks:
	 *
	 *   if (num_chans == max_chans), wetuwn max_chans
	 *   if (num_chans < max_chans), wetuwn avaiw_chans
	 *
	 * - exception is GC_11_0_0 whewe we can't access max_chans,
	 *  so we define max_avaiw_chans as the maximum avaiwabwe
	 *  MAWW space
	 *
	 */
	int gc_11_0_0_max_chans = 48;
	int gc_11_0_0_max_avaiw_chans = 32;
	int gc_11_0_0_avaiw_chans = 16;
	int gc_11_0_3_max_chans = 16;
	int gc_11_0_3_avaiw_chans = 8;
	int gc_11_0_2_max_chans = 8;
	int gc_11_0_2_avaiw_chans = 4;

	if (ASICWEV_IS_GC_11_0_0(dc->ctx->asic_id.hw_intewnaw_wev)) {
		wetuwn (num_chans == gc_11_0_0_max_chans) ?
			gc_11_0_0_max_avaiw_chans : gc_11_0_0_avaiw_chans;
	} ewse if (ASICWEV_IS_GC_11_0_2(dc->ctx->asic_id.hw_intewnaw_wev)) {
		wetuwn (num_chans == gc_11_0_2_max_chans) ?
			gc_11_0_2_max_chans : gc_11_0_2_avaiw_chans;
	} ewse { // if (ASICWEV_IS_GC_11_0_3(dc->ctx->asic_id.hw_intewnaw_wev)) {
		wetuwn (num_chans == gc_11_0_3_max_chans) ?
			gc_11_0_3_max_chans : gc_11_0_3_avaiw_chans;
	}
}
