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

#incwude "dcn31/dcn31_init.h"
#incwude "dcn314/dcn314_init.h"

#incwude "wesouwce.h"
#incwude "incwude/iwq_sewvice_intewface.h"
#incwude "dcn314_wesouwce.h"

#incwude "dcn20/dcn20_wesouwce.h"
#incwude "dcn30/dcn30_wesouwce.h"
#incwude "dcn31/dcn31_wesouwce.h"

#incwude "dcn10/dcn10_ipp.h"
#incwude "dcn30/dcn30_hubbub.h"
#incwude "dcn31/dcn31_hubbub.h"
#incwude "dcn30/dcn30_mpc.h"
#incwude "dcn31/dcn31_hubp.h"
#incwude "iwq/dcn31/iwq_sewvice_dcn31.h"
#incwude "iwq/dcn314/iwq_sewvice_dcn314.h"
#incwude "dcn30/dcn30_dpp.h"
#incwude "dcn314/dcn314_optc.h"
#incwude "dcn20/dcn20_hwseq.h"
#incwude "dcn30/dcn30_hwseq.h"
#incwude "dce110/dce110_hwseq.h"
#incwude "dcn30/dcn30_opp.h"
#incwude "dcn20/dcn20_dsc.h"
#incwude "dcn30/dcn30_vpg.h"
#incwude "dcn30/dcn30_afmt.h"
#incwude "dcn31/dcn31_dio_wink_encodew.h"
#incwude "dcn314/dcn314_dio_stweam_encodew.h"
#incwude "dcn31/dcn31_hpo_dp_stweam_encodew.h"
#incwude "dcn31/dcn31_hpo_dp_wink_encodew.h"
#incwude "dcn31/dcn31_apg.h"
#incwude "dcn31/dcn31_vpg.h"
#incwude "dcn31/dcn31_afmt.h"
#incwude "dce/dce_cwock_souwce.h"
#incwude "dce/dce_audio.h"
#incwude "dce/dce_hwseq.h"
#incwude "cwk_mgw.h"
#incwude "viwtuaw/viwtuaw_stweam_encodew.h"
#incwude "dce110/dce110_wesouwce.h"
#incwude "dmw/dispway_mode_vba.h"
#incwude "dmw/dcn31/dcn31_fpu.h"
#incwude "dmw/dcn314/dcn314_fpu.h"
#incwude "dcn314/dcn314_dccg.h"
#incwude "dcn10/dcn10_wesouwce.h"
#incwude "dcn31/dcn31_panew_cntw.h"
#incwude "dcn314/dcn314_hwseq.h"

#incwude "dcn30/dcn30_dwb.h"
#incwude "dcn30/dcn30_mmhubbub.h"

#incwude "dcn/dcn_3_1_4_offset.h"
#incwude "dcn/dcn_3_1_4_sh_mask.h"
#incwude "dpcs/dpcs_3_1_4_offset.h"
#incwude "dpcs/dpcs_3_1_4_sh_mask.h"

#define DCHUBBUB_DEBUG_CTWW_0__DET_DEPTH__SHIFT		0x10
#define DCHUBBUB_DEBUG_CTWW_0__DET_DEPTH_MASK		0x01FF0000W

#define DSCC0_DSCC_CONFIG0__ICH_WESET_AT_END_OF_WINE__SHIFT                   0x0
#define DSCC0_DSCC_CONFIG0__ICH_WESET_AT_END_OF_WINE_MASK                     0x0000000FW

#incwude "weg_hewpew.h"
#incwude "dce/dmub_abm.h"
#incwude "dce/dmub_psw.h"
#incwude "dce/dmub_wepway.h"
#incwude "dce/dce_aux.h"
#incwude "dce/dce_i2c.h"
#incwude "dmw/dcn314/dispway_mode_vba_314.h"
#incwude "vm_hewpew.h"
#incwude "dcn20/dcn20_vmid.h"

#incwude "wink_enc_cfg.h"

#define DCN_BASE__INST0_SEG1				0x000000C0
#define DCN_BASE__INST0_SEG2				0x000034C0
#define DCN_BASE__INST0_SEG3				0x00009000

#define NBIO_BASE__INST0_SEG1				0x00000014

#define MAX_INSTANCE					7
#define MAX_SEGMENT					8

#define wegBIF_BX2_BIOS_SCWATCH_2			0x003a
#define wegBIF_BX2_BIOS_SCWATCH_2_BASE_IDX		1
#define wegBIF_BX2_BIOS_SCWATCH_3			0x003b
#define wegBIF_BX2_BIOS_SCWATCH_3_BASE_IDX		1
#define wegBIF_BX2_BIOS_SCWATCH_6			0x003e
#define wegBIF_BX2_BIOS_SCWATCH_6_BASE_IDX		1

#define DC_WOGGEW \
	dc->ctx->woggew
#define DC_WOGGEW_INIT(woggew)

enum dcn31_cwk_swc_awway_id {
	DCN31_CWK_SWC_PWW0,
	DCN31_CWK_SWC_PWW1,
	DCN31_CWK_SWC_PWW2,
	DCN31_CWK_SWC_PWW3,
	DCN31_CWK_SWC_PWW4,
	DCN30_CWK_SWC_TOTAW
};

/* begin *********************
 * macwos to expend wegistew wist macwo defined in HW object headew fiwe
 */

/* DCN */
/* TODO awfuw hack. fixup dcn20_dwb.h */
#undef BASE_INNEW
#define BASE_INNEW(seg) DCN_BASE__INST0_SEG ## seg

#define BASE(seg) BASE_INNEW(seg)

#define SW(weg_name)\
		.weg_name = BASE(weg ## weg_name ## _BASE_IDX) +  \
					weg ## weg_name

#define SWI(weg_name, bwock, id)\
	.weg_name = BASE(weg ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					weg ## bwock ## id ## _ ## weg_name

#define SWI2(weg_name, bwock, id)\
	.weg_name = BASE(weg ## weg_name ## _BASE_IDX) + \
					weg ## weg_name

#define SWIW(vaw_name, weg_name, bwock, id)\
	.vaw_name = BASE(weg ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					weg ## bwock ## id ## _ ## weg_name

#define SWII(weg_name, bwock, id)\
	.weg_name[id] = BASE(weg ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					weg ## bwock ## id ## _ ## weg_name

#define SWII_MPC_WMU(weg_name, bwock, id)\
	.WMU##_##weg_name[id] = BASE(weg ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					weg ## bwock ## id ## _ ## weg_name

#define SWII_DWB(weg_name, temp_name, bwock, id)\
	.weg_name[id] = BASE(weg ## bwock ## id ## _ ## temp_name ## _BASE_IDX) + \
					weg ## bwock ## id ## _ ## temp_name

#define SF_DWB2(weg_name, bwock, id, fiewd_name, post_fix)	\
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix

#define DCCG_SWII(weg_name, bwock, id)\
	.bwock ## _ ## weg_name[id] = BASE(weg ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					weg ## bwock ## id ## _ ## weg_name

#define VUPDATE_SWII(weg_name, bwock, id)\
	.weg_name[id] = BASE(weg ## weg_name ## _ ## bwock ## id ## _BASE_IDX) + \
					weg ## weg_name ## _ ## bwock ## id

/* NBIO */
#define NBIO_BASE_INNEW(seg) \
	NBIO_BASE__INST0_SEG ## seg

#define NBIO_BASE(seg) \
	NBIO_BASE_INNEW(seg)

#define NBIO_SW(weg_name)\
		.weg_name = NBIO_BASE(wegBIF_BX2_ ## weg_name ## _BASE_IDX) + \
					wegBIF_BX2_ ## weg_name

/* MMHUB */
#define MMHUB_BASE_INNEW(seg) \
	MMHUB_BASE__INST0_SEG ## seg

#define MMHUB_BASE(seg) \
	MMHUB_BASE_INNEW(seg)

#define MMHUB_SW(weg_name)\
		.weg_name = MMHUB_BASE(weg ## weg_name ## _BASE_IDX) + \
					weg ## weg_name

/* CWOCK */
#define CWK_BASE_INNEW(seg) \
	CWK_BASE__INST0_SEG ## seg

#define CWK_BASE(seg) \
	CWK_BASE_INNEW(seg)

#define CWK_SWI(weg_name, bwock, inst)\
	.weg_name = CWK_BASE(weg ## bwock ## _ ## inst ## _ ## weg_name ## _BASE_IDX) + \
					weg ## bwock ## _ ## inst ## _ ## weg_name


static const stwuct bios_wegistews bios_wegs = {
		NBIO_SW(BIOS_SCWATCH_3),
		NBIO_SW(BIOS_SCWATCH_6)
};

#define cwk_swc_wegs(index, pwwid)\
[index] = {\
	CS_COMMON_WEG_WIST_DCN3_0(index, pwwid),\
}

static const stwuct dce110_cwk_swc_wegs cwk_swc_wegs[] = {
	cwk_swc_wegs(0, A),
	cwk_swc_wegs(1, B),
	cwk_swc_wegs(2, C),
	cwk_swc_wegs(3, D),
	cwk_swc_wegs(4, E)
};

static const stwuct dce110_cwk_swc_shift cs_shift = {
		CS_COMMON_MASK_SH_WIST_DCN3_1_4(__SHIFT)
};

static const stwuct dce110_cwk_swc_mask cs_mask = {
		CS_COMMON_MASK_SH_WIST_DCN3_1_4(_MASK)
};

#define abm_wegs(id)\
[id] = {\
		ABM_DCN302_WEG_WIST(id)\
}

static const stwuct dce_abm_wegistews abm_wegs[] = {
		abm_wegs(0),
		abm_wegs(1),
		abm_wegs(2),
		abm_wegs(3),
};

static const stwuct dce_abm_shift abm_shift = {
		ABM_MASK_SH_WIST_DCN30(__SHIFT)
};

static const stwuct dce_abm_mask abm_mask = {
		ABM_MASK_SH_WIST_DCN30(_MASK)
};

#define audio_wegs(id)\
[id] = {\
		AUD_COMMON_WEG_WIST(id)\
}

static const stwuct dce_audio_wegistews audio_wegs[] = {
	audio_wegs(0),
	audio_wegs(1),
	audio_wegs(2),
	audio_wegs(3),
	audio_wegs(4),
	audio_wegs(5),
	audio_wegs(6)
};

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

#define vpg_wegs(id)\
[id] = {\
	VPG_DCN31_WEG_WIST(id)\
}

static const stwuct dcn31_vpg_wegistews vpg_wegs[] = {
	vpg_wegs(0),
	vpg_wegs(1),
	vpg_wegs(2),
	vpg_wegs(3),
	vpg_wegs(4),
	vpg_wegs(5),
	vpg_wegs(6),
	vpg_wegs(7),
	vpg_wegs(8),
	vpg_wegs(9),
};

static const stwuct dcn31_vpg_shift vpg_shift = {
	DCN31_VPG_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn31_vpg_mask vpg_mask = {
	DCN31_VPG_MASK_SH_WIST(_MASK)
};

#define afmt_wegs(id)\
[id] = {\
	AFMT_DCN31_WEG_WIST(id)\
}

static const stwuct dcn31_afmt_wegistews afmt_wegs[] = {
	afmt_wegs(0),
	afmt_wegs(1),
	afmt_wegs(2),
	afmt_wegs(3),
	afmt_wegs(4),
	afmt_wegs(5)
};

static const stwuct dcn31_afmt_shift afmt_shift = {
	DCN31_AFMT_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn31_afmt_mask afmt_mask = {
	DCN31_AFMT_MASK_SH_WIST(_MASK)
};

#define apg_wegs(id)\
[id] = {\
	APG_DCN31_WEG_WIST(id)\
}

static const stwuct dcn31_apg_wegistews apg_wegs[] = {
	apg_wegs(0),
	apg_wegs(1),
	apg_wegs(2),
	apg_wegs(3)
};

static const stwuct dcn31_apg_shift apg_shift = {
	DCN31_APG_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn31_apg_mask apg_mask = {
		DCN31_APG_MASK_SH_WIST(_MASK)
};

#define stweam_enc_wegs(id)\
[id] = {\
		SE_DCN314_WEG_WIST(id)\
}

static const stwuct dcn10_stweam_enc_wegistews stweam_enc_wegs[] = {
	stweam_enc_wegs(0),
	stweam_enc_wegs(1),
	stweam_enc_wegs(2),
	stweam_enc_wegs(3),
	stweam_enc_wegs(4)
};

static const stwuct dcn10_stweam_encodew_shift se_shift = {
		SE_COMMON_MASK_SH_WIST_DCN314(__SHIFT)
};

static const stwuct dcn10_stweam_encodew_mask se_mask = {
		SE_COMMON_MASK_SH_WIST_DCN314(_MASK)
};


#define aux_wegs(id)\
[id] = {\
	DCN2_AUX_WEG_WIST(id)\
}

static const stwuct dcn10_wink_enc_aux_wegistews wink_enc_aux_wegs[] = {
		aux_wegs(0),
		aux_wegs(1),
		aux_wegs(2),
		aux_wegs(3),
		aux_wegs(4)
};

#define hpd_wegs(id)\
[id] = {\
	HPD_WEG_WIST(id)\
}

static const stwuct dcn10_wink_enc_hpd_wegistews wink_enc_hpd_wegs[] = {
		hpd_wegs(0),
		hpd_wegs(1),
		hpd_wegs(2),
		hpd_wegs(3),
		hpd_wegs(4)
};

#define wink_wegs(id, phyid)\
[id] = {\
	WE_DCN31_WEG_WIST(id), \
	UNIPHY_DCN2_WEG_WIST(phyid), \
}

static const stwuct dce110_aux_wegistews_shift aux_shift = {
	DCN_AUX_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce110_aux_wegistews_mask aux_mask = {
	DCN_AUX_MASK_SH_WIST(_MASK)
};

static const stwuct dcn10_wink_enc_wegistews wink_enc_wegs[] = {
	wink_wegs(0, A),
	wink_wegs(1, B),
	wink_wegs(2, C),
	wink_wegs(3, D),
	wink_wegs(4, E)
};

static const stwuct dcn10_wink_enc_shift we_shift = {
	WINK_ENCODEW_MASK_SH_WIST_DCN31(__SHIFT),
	DPCS_DCN31_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn10_wink_enc_mask we_mask = {
	WINK_ENCODEW_MASK_SH_WIST_DCN31(_MASK),
	DPCS_DCN31_MASK_SH_WIST(_MASK)
};

#define hpo_dp_stweam_encodew_weg_wist(id)\
[id] = {\
	DCN3_1_HPO_DP_STWEAM_ENC_WEG_WIST(id)\
}

static const stwuct dcn31_hpo_dp_stweam_encodew_wegistews hpo_dp_stweam_enc_wegs[] = {
	hpo_dp_stweam_encodew_weg_wist(0),
	hpo_dp_stweam_encodew_weg_wist(1),
	hpo_dp_stweam_encodew_weg_wist(2),
	hpo_dp_stweam_encodew_weg_wist(3)
};

static const stwuct dcn31_hpo_dp_stweam_encodew_shift hpo_dp_se_shift = {
	DCN3_1_HPO_DP_STWEAM_ENC_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn31_hpo_dp_stweam_encodew_mask hpo_dp_se_mask = {
	DCN3_1_HPO_DP_STWEAM_ENC_MASK_SH_WIST(_MASK)
};


#define hpo_dp_wink_encodew_weg_wist(id)\
[id] = {\
	DCN3_1_HPO_DP_WINK_ENC_WEG_WIST(id),\
	DCN3_1_WDPCSTX_WEG_WIST(0),\
	DCN3_1_WDPCSTX_WEG_WIST(1),\
	DCN3_1_WDPCSTX_WEG_WIST(2),\
}

static const stwuct dcn31_hpo_dp_wink_encodew_wegistews hpo_dp_wink_enc_wegs[] = {
	hpo_dp_wink_encodew_weg_wist(0),
	hpo_dp_wink_encodew_weg_wist(1),
};

static const stwuct dcn31_hpo_dp_wink_encodew_shift hpo_dp_we_shift = {
	DCN3_1_HPO_DP_WINK_ENC_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn31_hpo_dp_wink_encodew_mask hpo_dp_we_mask = {
	DCN3_1_HPO_DP_WINK_ENC_MASK_SH_WIST(_MASK)
};

#define dpp_wegs(id)\
[id] = {\
	DPP_WEG_WIST_DCN30(id),\
}

static const stwuct dcn3_dpp_wegistews dpp_wegs[] = {
	dpp_wegs(0),
	dpp_wegs(1),
	dpp_wegs(2),
	dpp_wegs(3)
};

static const stwuct dcn3_dpp_shift tf_shift = {
		DPP_WEG_WIST_SH_MASK_DCN30(__SHIFT)
};

static const stwuct dcn3_dpp_mask tf_mask = {
		DPP_WEG_WIST_SH_MASK_DCN30(_MASK)
};

#define opp_wegs(id)\
[id] = {\
	OPP_WEG_WIST_DCN30(id),\
}

static const stwuct dcn20_opp_wegistews opp_wegs[] = {
	opp_wegs(0),
	opp_wegs(1),
	opp_wegs(2),
	opp_wegs(3)
};

static const stwuct dcn20_opp_shift opp_shift = {
	OPP_MASK_SH_WIST_DCN20(__SHIFT)
};

static const stwuct dcn20_opp_mask opp_mask = {
	OPP_MASK_SH_WIST_DCN20(_MASK)
};

#define aux_engine_wegs(id)\
[id] = {\
	AUX_COMMON_WEG_WIST0(id), \
	.AUXN_IMPCAW = 0, \
	.AUXP_IMPCAW = 0, \
	.AUX_WESET_MASK = DP_AUX0_AUX_CONTWOW__AUX_WESET_MASK, \
}

static const stwuct dce110_aux_wegistews aux_engine_wegs[] = {
		aux_engine_wegs(0),
		aux_engine_wegs(1),
		aux_engine_wegs(2),
		aux_engine_wegs(3),
		aux_engine_wegs(4)
};

#define dwbc_wegs_dcn3(id)\
[id] = {\
	DWBC_COMMON_WEG_WIST_DCN30(id),\
}

static const stwuct dcn30_dwbc_wegistews dwbc30_wegs[] = {
	dwbc_wegs_dcn3(0),
};

static const stwuct dcn30_dwbc_shift dwbc30_shift = {
	DWBC_COMMON_MASK_SH_WIST_DCN30(__SHIFT)
};

static const stwuct dcn30_dwbc_mask dwbc30_mask = {
	DWBC_COMMON_MASK_SH_WIST_DCN30(_MASK)
};

#define mcif_wb_wegs_dcn3(id)\
[id] = {\
	MCIF_WB_COMMON_WEG_WIST_DCN30(id),\
}

static const stwuct dcn30_mmhubbub_wegistews mcif_wb30_wegs[] = {
	mcif_wb_wegs_dcn3(0)
};

static const stwuct dcn30_mmhubbub_shift mcif_wb30_shift = {
	MCIF_WB_COMMON_MASK_SH_WIST_DCN30(__SHIFT)
};

static const stwuct dcn30_mmhubbub_mask mcif_wb30_mask = {
	MCIF_WB_COMMON_MASK_SH_WIST_DCN30(_MASK)
};

#define dsc_wegsDCN314(id)\
[id] = {\
	DSC_WEG_WIST_DCN20(id)\
}

static const stwuct dcn20_dsc_wegistews dsc_wegs[] = {
	dsc_wegsDCN314(0),
	dsc_wegsDCN314(1),
	dsc_wegsDCN314(2),
	dsc_wegsDCN314(3)
};

static const stwuct dcn20_dsc_shift dsc_shift = {
	DSC_WEG_WIST_SH_MASK_DCN20(__SHIFT)
};

static const stwuct dcn20_dsc_mask dsc_mask = {
	DSC_WEG_WIST_SH_MASK_DCN20(_MASK)
};

static const stwuct dcn30_mpc_wegistews mpc_wegs = {
		MPC_WEG_WIST_DCN3_0(0),
		MPC_WEG_WIST_DCN3_0(1),
		MPC_WEG_WIST_DCN3_0(2),
		MPC_WEG_WIST_DCN3_0(3),
		MPC_OUT_MUX_WEG_WIST_DCN3_0(0),
		MPC_OUT_MUX_WEG_WIST_DCN3_0(1),
		MPC_OUT_MUX_WEG_WIST_DCN3_0(2),
		MPC_OUT_MUX_WEG_WIST_DCN3_0(3),
		MPC_WMU_GWOBAW_WEG_WIST_DCN3AG,
		MPC_WMU_WEG_WIST_DCN3AG(0),
		MPC_WMU_WEG_WIST_DCN3AG(1),
		//MPC_WMU_WEG_WIST_DCN3AG(2),
		MPC_DWB_MUX_WEG_WIST_DCN3_0(0),
};

static const stwuct dcn30_mpc_shift mpc_shift = {
	MPC_COMMON_MASK_SH_WIST_DCN30(__SHIFT)
};

static const stwuct dcn30_mpc_mask mpc_mask = {
	MPC_COMMON_MASK_SH_WIST_DCN30(_MASK)
};

#define optc_wegs(id)\
[id] = {OPTC_COMMON_WEG_WIST_DCN3_14(id)}

static const stwuct dcn_optc_wegistews optc_wegs[] = {
	optc_wegs(0),
	optc_wegs(1),
	optc_wegs(2),
	optc_wegs(3)
};

static const stwuct dcn_optc_shift optc_shift = {
	OPTC_COMMON_MASK_SH_WIST_DCN3_14(__SHIFT)
};

static const stwuct dcn_optc_mask optc_mask = {
	OPTC_COMMON_MASK_SH_WIST_DCN3_14(_MASK)
};

#define hubp_wegs(id)\
[id] = {\
	HUBP_WEG_WIST_DCN30(id)\
}

static const stwuct dcn_hubp2_wegistews hubp_wegs[] = {
		hubp_wegs(0),
		hubp_wegs(1),
		hubp_wegs(2),
		hubp_wegs(3)
};


static const stwuct dcn_hubp2_shift hubp_shift = {
		HUBP_MASK_SH_WIST_DCN31(__SHIFT)
};

static const stwuct dcn_hubp2_mask hubp_mask = {
		HUBP_MASK_SH_WIST_DCN31(_MASK)
};
static const stwuct dcn_hubbub_wegistews hubbub_weg = {
		HUBBUB_WEG_WIST_DCN31(0)
};

static const stwuct dcn_hubbub_shift hubbub_shift = {
		HUBBUB_MASK_SH_WIST_DCN31(__SHIFT)
};

static const stwuct dcn_hubbub_mask hubbub_mask = {
		HUBBUB_MASK_SH_WIST_DCN31(_MASK)
};

static const stwuct dccg_wegistews dccg_wegs = {
		DCCG_WEG_WIST_DCN314()
};

static const stwuct dccg_shift dccg_shift = {
		DCCG_MASK_SH_WIST_DCN314(__SHIFT)
};

static const stwuct dccg_mask dccg_mask = {
		DCCG_MASK_SH_WIST_DCN314(_MASK)
};


#define SWII2(weg_name_pwe, weg_name_post, id)\
	.weg_name_pwe ## _ ##  weg_name_post[id] = BASE(weg ## weg_name_pwe \
			## id ## _ ## weg_name_post ## _BASE_IDX) + \
			weg ## weg_name_pwe ## id ## _ ## weg_name_post


#define HWSEQ_DCN31_WEG_WIST()\
	SW(DCHUBBUB_GWOBAW_TIMEW_CNTW), \
	SW(DCHUBBUB_AWB_HOSTVM_CNTW), \
	SW(DIO_MEM_PWW_CTWW), \
	SW(ODM_MEM_PWW_CTWW3), \
	SW(DMU_MEM_PWW_CNTW), \
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
	SW(AZAWIA_CONTWOWWEW_CWOCK_GATING), \
	SW(HPO_TOP_HW_CONTWOW)

static const stwuct dce_hwseq_wegistews hwseq_weg = {
		HWSEQ_DCN31_WEG_WIST()
};

#define HWSEQ_DCN31_MASK_SH_WIST(mask_sh)\
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
	HWS_SF(, DMU_MEM_PWW_CNTW, DMCU_EWAM_MEM_PWW_FOWCE, mask_sh), \
	HWS_SF(, ODM_MEM_PWW_CTWW3, ODM_MEM_UNASSIGNED_PWW_MODE, mask_sh), \
	HWS_SF(, ODM_MEM_PWW_CTWW3, ODM_MEM_VBWANK_PWW_MODE, mask_sh), \
	HWS_SF(, MMHUBBUB_MEM_PWW_CNTW, VGA_MEM_PWW_FOWCE, mask_sh), \
	HWS_SF(, DIO_MEM_PWW_CTWW, I2C_WIGHT_SWEEP_FOWCE, mask_sh), \
	HWS_SF(, HPO_TOP_HW_CONTWOW, HPO_IO_EN, mask_sh)

static const stwuct dce_hwseq_shift hwseq_shift = {
		HWSEQ_DCN31_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce_hwseq_mask hwseq_mask = {
		HWSEQ_DCN31_MASK_SH_WIST(_MASK)
};
#define vmid_wegs(id)\
[id] = {\
		DCN20_VMID_WEG_WIST(id)\
}

static const stwuct dcn_vmid_wegistews vmid_wegs[] = {
	vmid_wegs(0),
	vmid_wegs(1),
	vmid_wegs(2),
	vmid_wegs(3),
	vmid_wegs(4),
	vmid_wegs(5),
	vmid_wegs(6),
	vmid_wegs(7),
	vmid_wegs(8),
	vmid_wegs(9),
	vmid_wegs(10),
	vmid_wegs(11),
	vmid_wegs(12),
	vmid_wegs(13),
	vmid_wegs(14),
	vmid_wegs(15)
};

static const stwuct dcn20_vmid_shift vmid_shifts = {
		DCN20_VMID_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn20_vmid_mask vmid_masks = {
		DCN20_VMID_MASK_SH_WIST(_MASK)
};

static const stwuct wesouwce_caps wes_cap_dcn314 = {
	.num_timing_genewatow = 4,
	.num_opp = 4,
	.num_video_pwane = 4,
	.num_audio = 5,
	.num_stweam_encodew = 5,
	.num_dig_wink_enc = 5,
	.num_hpo_dp_stweam_encodew = 4,
	.num_hpo_dp_wink_encodew = 2,
	.num_pww = 5,
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
	// 4:1 downscawing watio fow AWGB888 to pwevent undewfwow duwing P010 pwayback: 1000/4 = 250
	.max_downscawe_factow = {
			.awgb8888 = 250,
			.nv12 = 167,
			.fp16 = 167
	},
	64,
	64
};

static const stwuct dc_debug_options debug_defauwts_dwv = {
	.disabwe_z10 = fawse,
	.enabwe_z9_disabwe_intewface = twue,
	.minimum_z8_wesidency_time = 2100,
	.psw_skip_cwtc_disabwe = twue,
	.wepway_skip_cwtc_disabwed = twue,
	.disabwe_dmcu = twue,
	.fowce_abm_enabwe = fawse,
	.timing_twace = fawse,
	.cwock_twace = twue,
	.disabwe_dpp_powew_gate = fawse,
	.disabwe_hubp_powew_gate = fawse,
	.disabwe_ppwib_cwock_wequest = fawse,
	.pipe_spwit_powicy = MPC_SPWIT_DYNAMIC,
	.fowce_singwe_disp_pipe_spwit = fawse,
	.disabwe_dcc = DCC_ENABWE,
	.vsw_suppowt = twue,
	.pewfowmance_twace = fawse,
	.max_downscawe_swc_width = 4096,/*upto twue 4k*/
	.disabwe_ppwib_wm_wange = fawse,
	.scw_weset_wength10 = twue,
	.sanity_checks = twue,
	.undewfwow_assewt_deway_us = 0xFFFFFFFF,
	.dwb_fi_phase = -1, // -1 = disabwe,
	.dmub_command_tabwe = twue,
	.pstate_enabwed = twue,
	.use_max_wb = twue,
	.enabwe_mem_wow_powew = {
		.bits = {
			.vga = twue,
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
					.dsc = twue,
					.hdmistweam = twue,
					.hdmichaw = twue,
					.dpstweam = twue,
					.symcwk32_se = fawse,
					.symcwk32_we = twue,
					.symcwk_fe = twue,
					.physymcwk = twue,
					.dpiasymcwk = twue,
			}
	},

	.seamwess_boot_odm_combine = twue,
	.using_dmw2 = fawse,
};

static const stwuct dc_debug_options debug_defauwts_diags = {
	.disabwe_dmcu = twue,
	.fowce_abm_enabwe = fawse,
	.timing_twace = twue,
	.cwock_twace = twue,
	.disabwe_dpp_powew_gate = twue,
	.disabwe_hubp_powew_gate = twue,
	.disabwe_cwock_gate = twue,
	.disabwe_ppwib_cwock_wequest = twue,
	.disabwe_ppwib_wm_wange = twue,
	.disabwe_stuttew = fawse,
	.scw_weset_wength10 = twue,
	.dwb_fi_phase = -1, // -1 = disabwe
	.dmub_command_tabwe = twue,
	.enabwe_twi_buf = twue,
	.use_max_wb = twue
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

static void dcn31_dpp_destwoy(stwuct dpp **dpp)
{
	kfwee(TO_DCN20_DPP(*dpp));
	*dpp = NUWW;
}

static stwuct dpp *dcn31_dpp_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn3_dpp *dpp =
		kzawwoc(sizeof(stwuct dcn3_dpp), GFP_KEWNEW);

	if (!dpp)
		wetuwn NUWW;

	if (dpp3_constwuct(dpp, ctx, inst,
			&dpp_wegs[inst], &tf_shift, &tf_mask))
		wetuwn &dpp->base;

	BWEAK_TO_DEBUGGEW();
	kfwee(dpp);
	wetuwn NUWW;
}

static stwuct output_pixew_pwocessow *dcn31_opp_cweate(
	stwuct dc_context *ctx, uint32_t inst)
{
	stwuct dcn20_opp *opp =
		kzawwoc(sizeof(stwuct dcn20_opp), GFP_KEWNEW);

	if (!opp) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dcn20_opp_constwuct(opp, ctx, inst,
			&opp_wegs[inst], &opp_shift, &opp_mask);
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

	dce110_aux_engine_constwuct(aux_engine, ctx, inst,
				    SW_AUX_TIMEOUT_PEWIOD_MUWTIPWIEW * AUX_TIMEOUT_PEWIOD,
				    &aux_engine_wegs[inst],
					&aux_mask,
					&aux_shift,
					ctx->dc->caps.extended_aux_timeout_suppowt);

	wetuwn &aux_engine->base;
}
#define i2c_inst_wegs(id) { I2C_HW_ENGINE_COMMON_WEG_WIST_DCN30(id) }

static const stwuct dce_i2c_wegistews i2c_hw_wegs[] = {
		i2c_inst_wegs(1),
		i2c_inst_wegs(2),
		i2c_inst_wegs(3),
		i2c_inst_wegs(4),
		i2c_inst_wegs(5),
};

static const stwuct dce_i2c_shift i2c_shifts = {
		I2C_COMMON_MASK_SH_WIST_DCN30(__SHIFT)
};

static const stwuct dce_i2c_mask i2c_masks = {
		I2C_COMMON_MASK_SH_WIST_DCN30(_MASK)
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

static enum engine_id dcn314_get_pwefewwed_eng_id_dpia(unsigned int dpia_index)
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

	dcn2_i2c_hw_constwuct(dce_i2c_hw, ctx, inst,
				    &i2c_hw_wegs[inst], &i2c_shifts, &i2c_masks);

	wetuwn dce_i2c_hw;
}
static stwuct mpc *dcn31_mpc_cweate(
		stwuct dc_context *ctx,
		int num_mpcc,
		int num_wmu)
{
	stwuct dcn30_mpc *mpc30 = kzawwoc(sizeof(stwuct dcn30_mpc),
					  GFP_KEWNEW);

	if (!mpc30)
		wetuwn NUWW;

	dcn30_mpc_constwuct(mpc30, ctx,
			&mpc_wegs,
			&mpc_shift,
			&mpc_mask,
			num_mpcc,
			num_wmu);

	wetuwn &mpc30->base;
}

static stwuct hubbub *dcn31_hubbub_cweate(stwuct dc_context *ctx)
{
	int i;

	stwuct dcn20_hubbub *hubbub3 = kzawwoc(sizeof(stwuct dcn20_hubbub),
					  GFP_KEWNEW);

	if (!hubbub3)
		wetuwn NUWW;

	hubbub31_constwuct(hubbub3, ctx,
			&hubbub_weg,
			&hubbub_shift,
			&hubbub_mask,
			dcn3_14_ip.det_buffew_size_kbytes,
			dcn3_14_ip.pixew_chunk_size_kbytes,
			dcn3_14_ip.config_wetuwn_buffew_size_in_kbytes);


	fow (i = 0; i < wes_cap_dcn314.num_vmid; i++) {
		stwuct dcn20_vmid *vmid = &hubbub3->vmid[i];

		vmid->ctx = ctx;

		vmid->wegs = &vmid_wegs[i];
		vmid->shifts = &vmid_shifts;
		vmid->masks = &vmid_masks;
	}

	wetuwn &hubbub3->base;
}

static stwuct timing_genewatow *dcn31_timing_genewatow_cweate(
		stwuct dc_context *ctx,
		uint32_t instance)
{
	stwuct optc *tgn10 =
		kzawwoc(sizeof(stwuct optc), GFP_KEWNEW);

	if (!tgn10)
		wetuwn NUWW;

	tgn10->base.inst = instance;
	tgn10->base.ctx = ctx;

	tgn10->tg_wegs = &optc_wegs[instance];
	tgn10->tg_shift = &optc_shift;
	tgn10->tg_mask = &optc_mask;

	dcn314_timing_genewatow_init(tgn10);

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

static stwuct wink_encodew *dcn31_wink_encodew_cweate(
	stwuct dc_context *ctx,
	const stwuct encodew_init_data *enc_init_data)
{
	stwuct dcn20_wink_encodew *enc20 =
		kzawwoc(sizeof(stwuct dcn20_wink_encodew), GFP_KEWNEW);

	if (!enc20)
		wetuwn NUWW;

	dcn31_wink_encodew_constwuct(enc20,
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

	apg31_constwuct(apg31, ctx, inst,
			&apg_wegs[inst],
			&apg_shift,
			&apg_mask);

	wetuwn &apg31->base;
}

static stwuct stweam_encodew *dcn314_stweam_encodew_cweate(
	enum engine_id eng_id,
	stwuct dc_context *ctx)
{
	stwuct dcn10_stweam_encodew *enc1;
	stwuct vpg *vpg;
	stwuct afmt *afmt;
	int vpg_inst;
	int afmt_inst;

	/* Mapping of VPG, AFMT, DME wegistew bwocks to DIO bwock instance */
	if (eng_id < ENGINE_ID_DIGF) {
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

	dcn314_dio_stweam_encodew_constwuct(enc1, ctx, ctx->dc_bios,
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
	//Uses offset index 5-8, but actuawwy maps to vpg_inst 6-9
	vpg_inst = hpo_dp_inst + 5;

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

	hpo_dp_wink_encodew31_constwuct(hpo_dp_enc31, ctx, inst,
					&hpo_dp_wink_enc_wegs[inst],
					&hpo_dp_we_shift, &hpo_dp_we_mask);

	wetuwn &hpo_dp_enc31->base;
}

static stwuct dce_hwseq *dcn314_hwseq_cweate(
	stwuct dc_context *ctx)
{
	stwuct dce_hwseq *hws = kzawwoc(sizeof(stwuct dce_hwseq), GFP_KEWNEW);

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
	.cweate_stweam_encodew = dcn314_stweam_encodew_cweate,
	.cweate_hpo_dp_stweam_encodew = dcn31_hpo_dp_stweam_encodew_cweate,
	.cweate_hpo_dp_wink_encodew = dcn31_hpo_dp_wink_encodew_cweate,
	.cweate_hwseq = dcn314_hwseq_cweate,
};

static void dcn314_wesouwce_destwuct(stwuct dcn314_wesouwce_poow *poow)
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
			dcn31_dpp_destwoy(&poow->base.dpps[i]);

		if (poow->base.ipps[i] != NUWW)
			poow->base.ipps[i]->funcs->ipp_destwoy(&poow->base.ipps[i]);

		if (poow->base.hubps[i] != NUWW) {
			kfwee(TO_DCN20_HUBP(poow->base.hubps[i]));
			poow->base.hubps[i] = NUWW;
		}

		if (poow->base.iwqs != NUWW)
			daw_iwq_sewvice_destwoy(&poow->base.iwqs);
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

	if (poow->base.dccg != NUWW)
		dcn_dccg_destwoy(&poow->base.dccg);
}

static stwuct hubp *dcn31_hubp_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn20_hubp *hubp2 =
		kzawwoc(sizeof(stwuct dcn20_hubp), GFP_KEWNEW);

	if (!hubp2)
		wetuwn NUWW;

	if (hubp31_constwuct(hubp2, ctx, inst,
			&hubp_wegs[inst], &hubp_shift, &hubp_mask))
		wetuwn &hubp2->base;

	BWEAK_TO_DEBUGGEW();
	kfwee(hubp2);
	wetuwn NUWW;
}

static boow dcn31_dwbc_cweate(stwuct dc_context *ctx, stwuct wesouwce_poow *poow)
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

		dcn30_dwbc_constwuct(dwbc30, ctx,
				&dwbc30_wegs[i],
				&dwbc30_shift,
				&dwbc30_mask,
				i);

		poow->dwbc[i] = &dwbc30->base;
	}
	wetuwn twue;
}

static boow dcn31_mmhubbub_cweate(stwuct dc_context *ctx, stwuct wesouwce_poow *poow)
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

		dcn30_mmhubbub_constwuct(mcif_wb30, ctx,
				&mcif_wb30_wegs[i],
				&mcif_wb30_shift,
				&mcif_wb30_mask,
				i);

		poow->mcif_wb[i] = &mcif_wb30->base;
	}
	wetuwn twue;
}

static stwuct dispway_stweam_compwessow *dcn314_dsc_cweate(
	stwuct dc_context *ctx, uint32_t inst)
{
	stwuct dcn20_dsc *dsc =
		kzawwoc(sizeof(stwuct dcn20_dsc), GFP_KEWNEW);

	if (!dsc) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dsc2_constwuct(dsc, ctx, inst, &dsc_wegs[inst], &dsc_shift, &dsc_mask);
	wetuwn &dsc->base;
}

static void dcn314_destwoy_wesouwce_poow(stwuct wesouwce_poow **poow)
{
	stwuct dcn314_wesouwce_poow *dcn314_poow = TO_DCN314_WES_POOW(*poow);

	dcn314_wesouwce_destwuct(dcn314_poow);
	kfwee(dcn314_poow);
	*poow = NUWW;
}

static stwuct cwock_souwce *dcn31_cwock_souwce_cweate(
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
	kfwee(cwk_swc);
	wetuwn NUWW;
}

static int dcn314_popuwate_dmw_pipes_fwom_context(
	stwuct dc *dc, stwuct dc_state *context,
	dispway_e2e_pipe_pawams_st *pipes,
	boow fast_vawidate)
{
	int pipe_cnt;

	DC_FP_STAWT();
	pipe_cnt = dcn314_popuwate_dmw_pipes_fwom_context_fpu(dc, context, pipes, fast_vawidate);
	DC_FP_END();

	wetuwn pipe_cnt;
}

static stwuct dc_cap_funcs cap_funcs = {
	.get_dcc_compwession_cap = dcn20_get_dcc_compwession_cap
};

static void dcn314_update_bw_bounding_box(stwuct dc *dc, stwuct cwk_bw_pawams *bw_pawams)
{
	DC_FP_STAWT();
	dcn314_update_bw_bounding_box_fpu(dc, bw_pawams);
	DC_FP_END();
}

static void dcn314_get_panew_config_defauwts(stwuct dc_panew_config *panew_config)
{
	*panew_config = panew_config_defauwts;
}

static boow fiwtew_modes_fow_singwe_channew_wowkawound(stwuct dc *dc,
		stwuct dc_state *context)
{
	// Fiwtew 2K@240Hz+8K@24fps above combination timing if memowy onwy has singwe dimm WPDDW
	if (dc->cwk_mgw->bw_pawams->vwam_type == 34 &&
	    dc->cwk_mgw->bw_pawams->num_channews < 2 &&
	    context->stweam_count > 1) {
		int totaw_phy_pix_cwk = 0;

		fow (int i = 0; i < context->stweam_count; i++)
			if (context->wes_ctx.pipe_ctx[i].stweam)
				totaw_phy_pix_cwk += context->wes_ctx.pipe_ctx[i].stweam->phy_pix_cwk;

		if (totaw_phy_pix_cwk >= (1148928+826260)) //2K@240Hz+8K@24fps
			wetuwn twue;
	}
	wetuwn fawse;
}

boow dcn314_vawidate_bandwidth(stwuct dc *dc,
		stwuct dc_state *context,
		boow fast_vawidate)
{
	boow out = fawse;

	BW_VAW_TWACE_SETUP();

	int vwevew = 0;
	int pipe_cnt = 0;
	dispway_e2e_pipe_pawams_st *pipes = kzawwoc(dc->wes_poow->pipe_count * sizeof(dispway_e2e_pipe_pawams_st), GFP_KEWNEW);
	DC_WOGGEW_INIT(dc->ctx->woggew);

	BW_VAW_TWACE_COUNT();

	if (fiwtew_modes_fow_singwe_channew_wowkawound(dc, context))
		goto vawidate_faiw;

	DC_FP_STAWT();
	// do not suppowt sewf wefwesh onwy
	out = dcn30_intewnaw_vawidate_bw(dc, context, pipes, &pipe_cnt, &vwevew, fast_vawidate, fawse);
	DC_FP_END();

	// Disabwe fast_vawidate to set min dcfcwk in cawcuwate_wm_and_dwg
	if (pipe_cnt == 0)
		fast_vawidate = fawse;

	if (!out)
		goto vawidate_faiw;

	BW_VAW_TWACE_END_VOWTAGE_WEVEW();

	if (fast_vawidate) {
		BW_VAW_TWACE_SKIP(fast);
		goto vawidate_out;
	}
	if (dc->wes_poow->funcs->cawcuwate_wm_and_dwg)
		dc->wes_poow->funcs->cawcuwate_wm_and_dwg(dc, context, pipes, pipe_cnt, vwevew);

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

static stwuct wesouwce_funcs dcn314_wes_poow_funcs = {
	.destwoy = dcn314_destwoy_wesouwce_poow,
	.wink_enc_cweate = dcn31_wink_encodew_cweate,
	.wink_enc_cweate_minimaw = dcn31_wink_enc_cweate_minimaw,
	.wink_encs_assign = wink_enc_cfg_wink_encs_assign,
	.wink_enc_unassign = wink_enc_cfg_wink_enc_unassign,
	.panew_cntw_cweate = dcn31_panew_cntw_cweate,
	.vawidate_bandwidth = dcn314_vawidate_bandwidth,
	.cawcuwate_wm_and_dwg = dcn31_cawcuwate_wm_and_dwg,
	.update_soc_fow_wm_a = dcn31_update_soc_fow_wm_a,
	.popuwate_dmw_pipes = dcn314_popuwate_dmw_pipes_fwom_context,
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
	.update_bw_bounding_box = dcn314_update_bw_bounding_box,
	.patch_unknown_pwane_state = dcn20_patch_unknown_pwane_state,
	.get_panew_config_defauwts = dcn314_get_panew_config_defauwts,
	.get_pwefewwed_eng_id_dpia = dcn314_get_pwefewwed_eng_id_dpia,
};

static stwuct cwock_souwce *dcn30_cwock_souwce_cweate(
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
	kfwee(cwk_swc);
	wetuwn NUWW;
}

static boow dcn314_wesouwce_constwuct(
	uint8_t num_viwtuaw_winks,
	stwuct dc *dc,
	stwuct dcn314_wesouwce_poow *poow)
{
	int i;
	stwuct dc_context *ctx = dc->ctx;
	stwuct iwq_sewvice_init_data init_data;

	ctx->dc_bios->wegs = &bios_wegs;

	poow->base.wes_cap = &wes_cap_dcn314;
	poow->base.funcs = &dcn314_wes_poow_funcs;

	/*************************************************
	 *  Wesouwce + asic cap hawcoding                *
	 *************************************************/
	poow->base.undewway_pipe_index = NO_UNDEWWAY_PIPE;
	poow->base.pipe_count = poow->base.wes_cap->num_timing_genewatow;
	poow->base.mpcc_count = poow->base.wes_cap->num_timing_genewatow;
	dc->caps.max_downscawe_watio = 400;
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
	dc->caps.cowow.dpp.ogam_wam = 1;
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
	ewse
		dc->debug = debug_defauwts_diags;

	/* Disabwe pipe powew gating */
	dc->debug.disabwe_dpp_powew_gate = twue;
	dc->debug.disabwe_hubp_powew_gate = twue;

	/* Disabwe woot cwock optimization */
	dc->debug.woot_cwock_optimization.u32Aww = 0;

	// Init the vm_hewpew
	if (dc->vm_hewpew)
		vm_hewpew_init(dc->vm_hewpew, 16);

	/*************************************************
	 *  Cweate wesouwces                             *
	 *************************************************/

	/* Cwock Souwces fow Pixew Cwock*/
	poow->base.cwock_souwces[DCN31_CWK_SWC_PWW0] =
			dcn30_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW0,
				&cwk_swc_wegs[0], fawse);
	poow->base.cwock_souwces[DCN31_CWK_SWC_PWW1] =
			dcn30_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW1,
				&cwk_swc_wegs[1], fawse);
	poow->base.cwock_souwces[DCN31_CWK_SWC_PWW2] =
			dcn30_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW2,
				&cwk_swc_wegs[2], fawse);
	poow->base.cwock_souwces[DCN31_CWK_SWC_PWW3] =
			dcn30_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW3,
				&cwk_swc_wegs[3], fawse);
	poow->base.cwock_souwces[DCN31_CWK_SWC_PWW4] =
			dcn30_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW4,
				&cwk_swc_wegs[4], fawse);

	poow->base.cwk_swc_count = DCN30_CWK_SWC_TOTAW;

	/* todo: not weuse phy_pww wegistews */
	poow->base.dp_cwock_souwce =
			dcn31_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_ID_DP_DTO,
				&cwk_swc_wegs[0], twue);

	fow (i = 0; i < poow->base.cwk_swc_count; i++) {
		if (poow->base.cwock_souwces[i] == NUWW) {
			dm_ewwow("DC: faiwed to cweate cwock souwces!\n");
			BWEAK_TO_DEBUGGEW();
			goto cweate_faiw;
		}
	}

	poow->base.dccg = dccg314_cweate(ctx, &dccg_wegs, &dccg_shift, &dccg_mask);
	if (poow->base.dccg == NUWW) {
		dm_ewwow("DC: faiwed to cweate dccg!\n");
		BWEAK_TO_DEBUGGEW();
		goto cweate_faiw;
	}

	init_data.ctx = dc->ctx;
	poow->base.iwqs = daw_iwq_sewvice_dcn314_cweate(&init_data);
	if (!poow->base.iwqs)
		goto cweate_faiw;

	/* HUBBUB */
	poow->base.hubbub = dcn31_hubbub_cweate(ctx);
	if (poow->base.hubbub == NUWW) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate hubbub!\n");
		goto cweate_faiw;
	}

	/* HUBPs, DPPs, OPPs and TGs */
	fow (i = 0; i < poow->base.pipe_count; i++) {
		poow->base.hubps[i] = dcn31_hubp_cweate(ctx, i);
		if (poow->base.hubps[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate hubps!\n");
			goto cweate_faiw;
		}

		poow->base.dpps[i] = dcn31_dpp_cweate(ctx, i);
		if (poow->base.dpps[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate dpps!\n");
			goto cweate_faiw;
		}
	}

	fow (i = 0; i < poow->base.wes_cap->num_opp; i++) {
		poow->base.opps[i] = dcn31_opp_cweate(ctx, i);
		if (poow->base.opps[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate output pixew pwocessow!\n");
			goto cweate_faiw;
		}
	}

	fow (i = 0; i < poow->base.wes_cap->num_timing_genewatow; i++) {
		poow->base.timing_genewatows[i] = dcn31_timing_genewatow_cweate(
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
	poow->base.mpc = dcn31_mpc_cweate(ctx, poow->base.mpcc_count, poow->base.wes_cap->num_mpc_3dwut);
	if (poow->base.mpc == NUWW) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate mpc!\n");
		goto cweate_faiw;
	}

	fow (i = 0; i < poow->base.wes_cap->num_dsc; i++) {
		poow->base.dscs[i] = dcn314_dsc_cweate(ctx, i);
		if (poow->base.dscs[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow("DC: faiwed to cweate dispway stweam compwessow %d!\n", i);
			goto cweate_faiw;
		}
	}

	/* DWB and MMHUBBUB */
	if (!dcn31_dwbc_cweate(ctx, &poow->base)) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate dwbc!\n");
		goto cweate_faiw;
	}

	if (!dcn31_mmhubbub_cweate(ctx, &poow->base)) {
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

	/* DCN314 has 4 DPIA */
	poow->base.usb4_dpia_count = 4;

	/* Audio, Stweam Encodews incwuding HPO and viwtuaw, MPC 3D WUTs */
	if (!wesouwce_constwuct(num_viwtuaw_winks, dc, &poow->base,
			&wes_cweate_funcs))
		goto cweate_faiw;

	/* HW Sequencew and Pwane caps */
	dcn314_hw_sequencew_constwuct(dc);

	dc->caps.max_pwanes =  poow->base.pipe_count;

	fow (i = 0; i < dc->caps.max_pwanes; ++i)
		dc->caps.pwanes[i] = pwane_cap;

	dc->cap_funcs = cap_funcs;

	dc->dcn_ip->max_num_dpp = dcn3_14_ip.max_num_dpp;

	wetuwn twue;

cweate_faiw:

	dcn314_wesouwce_destwuct(poow);

	wetuwn fawse;
}

stwuct wesouwce_poow *dcn314_cweate_wesouwce_poow(
		const stwuct dc_init_data *init_data,
		stwuct dc *dc)
{
	stwuct dcn314_wesouwce_poow *poow =
		kzawwoc(sizeof(stwuct dcn314_wesouwce_poow), GFP_KEWNEW);

	if (!poow)
		wetuwn NUWW;

	if (dcn314_wesouwce_constwuct(init_data->num_viwtuaw_winks, dc, poow))
		wetuwn &poow->base;

	BWEAK_TO_DEBUGGEW();
	kfwee(poow);
	wetuwn NUWW;
}
