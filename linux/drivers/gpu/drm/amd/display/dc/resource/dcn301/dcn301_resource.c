/*
 * Copywight 2019-2021 Advanced Micwo Devices, Inc.
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

#incwude "dcn301/dcn301_init.h"

#incwude "wesouwce.h"
#incwude "incwude/iwq_sewvice_intewface.h"
#incwude "dcn30/dcn30_wesouwce.h"
#incwude "dcn301_wesouwce.h"

#incwude "dcn20/dcn20_wesouwce.h"

#incwude "dcn10/dcn10_ipp.h"
#incwude "dcn301/dcn301_hubbub.h"
#incwude "dcn30/dcn30_mpc.h"
#incwude "dcn30/dcn30_hubp.h"
#incwude "iwq/dcn30/iwq_sewvice_dcn30.h"
#incwude "dcn30/dcn30_dpp.h"
#incwude "dcn301/dcn301_optc.h"
#incwude "dcn20/dcn20_hwseq.h"
#incwude "dcn30/dcn30_hwseq.h"
#incwude "dce110/dce110_hwseq.h"
#incwude "dcn30/dcn30_opp.h"
#incwude "dcn20/dcn20_dsc.h"
#incwude "dcn30/dcn30_vpg.h"
#incwude "dcn30/dcn30_afmt.h"
#incwude "dce/dce_cwock_souwce.h"
#incwude "dce/dce_audio.h"
#incwude "dce/dce_hwseq.h"
#incwude "cwk_mgw.h"
#incwude "viwtuaw/viwtuaw_stweam_encodew.h"
#incwude "dce110/dce110_wesouwce.h"
#incwude "dmw/dispway_mode_vba.h"
#incwude "dcn301/dcn301_dccg.h"
#incwude "dcn10/dcn10_wesouwce.h"
#incwude "dcn30/dcn30_dio_stweam_encodew.h"
#incwude "dcn301/dcn301_dio_wink_encodew.h"
#incwude "dcn301/dcn301_panew_cntw.h"

#incwude "vangogh_ip_offset.h"

#incwude "dcn30/dcn30_dwb.h"
#incwude "dcn30/dcn30_mmhubbub.h"

#incwude "dcn/dcn_3_0_1_offset.h"
#incwude "dcn/dcn_3_0_1_sh_mask.h"

#incwude "nbio/nbio_7_2_0_offset.h"

#incwude "dpcs/dpcs_3_0_0_offset.h"
#incwude "dpcs/dpcs_3_0_0_sh_mask.h"

#incwude "weg_hewpew.h"
#incwude "dce/dmub_abm.h"
#incwude "dce/dce_aux.h"
#incwude "dce/dce_i2c.h"

#incwude "dmw/dcn30/dcn30_fpu.h"

#incwude "dmw/dcn30/dispway_mode_vba_30.h"
#incwude "dmw/dcn301/dcn301_fpu.h"
#incwude "vm_hewpew.h"
#incwude "dcn20/dcn20_vmid.h"
#incwude "amdgpu_socbb.h"

#define TO_DCN301_WES_POOW(poow)\
	containew_of(poow, stwuct dcn301_wesouwce_poow, base)

#define DC_WOGGEW \
	dc->ctx->woggew
#define DC_WOGGEW_INIT(woggew)

enum dcn301_cwk_swc_awway_id {
	DCN301_CWK_SWC_PWW0,
	DCN301_CWK_SWC_PWW1,
	DCN301_CWK_SWC_PWW2,
	DCN301_CWK_SWC_PWW3,
	DCN301_CWK_SWC_TOTAW
};

/* begin *********************
 * macwos to expend wegistew wist macwo defined in HW object headew fiwe
 */

/* DCN */
#define BASE_INNEW(seg) DCN_BASE__INST0_SEG ## seg

#define BASE(seg) BASE_INNEW(seg)

#define SW(weg_name)\
		.weg_name = BASE(mm ## weg_name ## _BASE_IDX) +  \
					mm ## weg_name

#define SWI(weg_name, bwock, id)\
	.weg_name = BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## id ## _ ## weg_name

#define SWI2(weg_name, bwock, id)\
	.weg_name = BASE(mm ## weg_name ## _BASE_IDX) + \
					mm ## weg_name

#define SWIW(vaw_name, weg_name, bwock, id)\
	.vaw_name = BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## id ## _ ## weg_name

#define SWII(weg_name, bwock, id)\
	.weg_name[id] = BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## id ## _ ## weg_name

#define SWII2(weg_name_pwe, weg_name_post, id)\
	.weg_name_pwe ## _ ##  weg_name_post[id] = BASE(mm ## weg_name_pwe \
			## id ## _ ## weg_name_post ## _BASE_IDX) + \
			mm ## weg_name_pwe ## id ## _ ## weg_name_post

#define SWII_MPC_WMU(weg_name, bwock, id)\
	.WMU##_##weg_name[id] = BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## id ## _ ## weg_name

#define SWII_DWB(weg_name, temp_name, bwock, id)\
	.weg_name[id] = BASE(mm ## bwock ## id ## _ ## temp_name ## _BASE_IDX) + \
					mm ## bwock ## id ## _ ## temp_name

#define SF_DWB2(weg_name, bwock, id, fiewd_name, post_fix)	\
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix

#define DCCG_SWII(weg_name, bwock, id)\
	.bwock ## _ ## weg_name[id] = BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## id ## _ ## weg_name

#define VUPDATE_SWII(weg_name, bwock, id)\
	.weg_name[id] = BASE(mm ## weg_name ## _ ## bwock ## id ## _BASE_IDX) + \
					mm ## weg_name ## _ ## bwock ## id

/* NBIO */
#define NBIO_BASE_INNEW(seg) \
	NBIO_BASE__INST0_SEG ## seg

#define NBIO_BASE(seg) \
	NBIO_BASE_INNEW(seg)

#define NBIO_SW(weg_name)\
		.weg_name = NBIO_BASE(wegBIF_BX0_ ## weg_name ## _BASE_IDX) + \
					wegBIF_BX0_ ## weg_name

/* MMHUB */
#define MMHUB_BASE_INNEW(seg) \
	MMHUB_BASE__INST0_SEG ## seg

#define MMHUB_BASE(seg) \
	MMHUB_BASE_INNEW(seg)

#define MMHUB_SW(weg_name)\
		.weg_name = MMHUB_BASE(wegMM ## weg_name ## _BASE_IDX) + \
					wegMM ## weg_name

/* CWOCK */
#define CWK_BASE_INNEW(seg) \
	CWK_BASE__INST0_SEG ## seg

#define CWK_BASE(seg) \
	CWK_BASE_INNEW(seg)

#define CWK_SWI(weg_name, bwock, inst)\
	.weg_name = CWK_BASE(mm ## bwock ## _ ## inst ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## _ ## inst ## _ ## weg_name

static const stwuct bios_wegistews bios_wegs = {
		NBIO_SW(BIOS_SCWATCH_3),
		NBIO_SW(BIOS_SCWATCH_6)
};

#define cwk_swc_wegs(index, pwwid)\
[index] = {\
	CS_COMMON_WEG_WIST_DCN3_01(index, pwwid),\
}

static const stwuct dce110_cwk_swc_wegs cwk_swc_wegs[] = {
	cwk_swc_wegs(0, A),
	cwk_swc_wegs(1, B),
	cwk_swc_wegs(2, C),
	cwk_swc_wegs(3, D)
};

static const stwuct dce110_cwk_swc_shift cs_shift = {
		CS_COMMON_MASK_SH_WIST_DCN2_0(__SHIFT)
};

static const stwuct dce110_cwk_swc_mask cs_mask = {
		CS_COMMON_MASK_SH_WIST_DCN2_0(_MASK)
};

#define abm_wegs(id)\
[id] = {\
		ABM_DCN301_WEG_WIST(id)\
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
	VPG_DCN3_WEG_WIST(id)\
}

static const stwuct dcn30_vpg_wegistews vpg_wegs[] = {
	vpg_wegs(0),
	vpg_wegs(1),
	vpg_wegs(2),
	vpg_wegs(3),
};

static const stwuct dcn30_vpg_shift vpg_shift = {
	DCN3_VPG_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn30_vpg_mask vpg_mask = {
	DCN3_VPG_MASK_SH_WIST(_MASK)
};

#define afmt_wegs(id)\
[id] = {\
	AFMT_DCN3_WEG_WIST(id)\
}

static const stwuct dcn30_afmt_wegistews afmt_wegs[] = {
	afmt_wegs(0),
	afmt_wegs(1),
	afmt_wegs(2),
	afmt_wegs(3),
};

static const stwuct dcn30_afmt_shift afmt_shift = {
	DCN3_AFMT_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn30_afmt_mask afmt_mask = {
	DCN3_AFMT_MASK_SH_WIST(_MASK)
};

#define stweam_enc_wegs(id)\
[id] = {\
	SE_DCN3_WEG_WIST(id)\
}

static const stwuct dcn10_stweam_enc_wegistews stweam_enc_wegs[] = {
	stweam_enc_wegs(0),
	stweam_enc_wegs(1),
	stweam_enc_wegs(2),
	stweam_enc_wegs(3),
};

static const stwuct dcn10_stweam_encodew_shift se_shift = {
		SE_COMMON_MASK_SH_WIST_DCN30(__SHIFT)
};

static const stwuct dcn10_stweam_encodew_mask se_mask = {
		SE_COMMON_MASK_SH_WIST_DCN30(_MASK)
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
};


#define wink_wegs(id, phyid)\
[id] = {\
	WE_DCN301_WEG_WIST(id), \
	UNIPHY_DCN2_WEG_WIST(phyid), \
	DPCS_DCN2_WEG_WIST(id), \
	SWI(DP_DPHY_INTEWNAW_CTWW, DP, id) \
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
};

static const stwuct dcn10_wink_enc_shift we_shift = {
	WINK_ENCODEW_MASK_SH_WIST_DCN301(__SHIFT),\
	DPCS_DCN2_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn10_wink_enc_mask we_mask = {
	WINK_ENCODEW_MASK_SH_WIST_DCN301(_MASK),\
	DPCS_DCN2_MASK_SH_WIST(_MASK)
};

#define panew_cntw_wegs(id)\
[id] = {\
	DCN301_PANEW_CNTW_WEG_WIST(id),\
}

static const stwuct dce_panew_cntw_wegistews panew_cntw_wegs[] = {
	panew_cntw_wegs(0),
	panew_cntw_wegs(1),
};

static const stwuct dcn301_panew_cntw_shift panew_cntw_shift = {
	DCN301_PANEW_CNTW_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn301_panew_cntw_mask panew_cntw_mask = {
	DCN301_PANEW_CNTW_MASK_SH_WIST(_MASK)
};

#define dpp_wegs(id)\
[id] = {\
	DPP_WEG_WIST_DCN30(id),\
}

static const stwuct dcn3_dpp_wegistews dpp_wegs[] = {
	dpp_wegs(0),
	dpp_wegs(1),
	dpp_wegs(2),
	dpp_wegs(3),
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
	opp_wegs(3),
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

#define dsc_wegsDCN20(id)\
[id] = {\
	DSC_WEG_WIST_DCN20(id)\
}

static const stwuct dcn20_dsc_wegistews dsc_wegs[] = {
	dsc_wegsDCN20(0),
	dsc_wegsDCN20(1),
	dsc_wegsDCN20(2),
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
		MPC_DWB_MUX_WEG_WIST_DCN3_0(0),
};

static const stwuct dcn30_mpc_shift mpc_shift = {
	MPC_COMMON_MASK_SH_WIST_DCN30(__SHIFT)
};

static const stwuct dcn30_mpc_mask mpc_mask = {
	MPC_COMMON_MASK_SH_WIST_DCN30(_MASK)
};

#define optc_wegs(id)\
[id] = {OPTC_COMMON_WEG_WIST_DCN3_0(id)}


static const stwuct dcn_optc_wegistews optc_wegs[] = {
	optc_wegs(0),
	optc_wegs(1),
	optc_wegs(2),
	optc_wegs(3),
};

static const stwuct dcn_optc_shift optc_shift = {
	OPTC_COMMON_MASK_SH_WIST_DCN30(__SHIFT)
};

static const stwuct dcn_optc_mask optc_mask = {
	OPTC_COMMON_MASK_SH_WIST_DCN30(_MASK)
};

#define hubp_wegs(id)\
[id] = {\
	HUBP_WEG_WIST_DCN30(id)\
}

static const stwuct dcn_hubp2_wegistews hubp_wegs[] = {
		hubp_wegs(0),
		hubp_wegs(1),
		hubp_wegs(2),
		hubp_wegs(3),
};

static const stwuct dcn_hubp2_shift hubp_shift = {
		HUBP_MASK_SH_WIST_DCN30(__SHIFT)
};

static const stwuct dcn_hubp2_mask hubp_mask = {
		HUBP_MASK_SH_WIST_DCN30(_MASK)
};

static const stwuct dcn_hubbub_wegistews hubbub_weg = {
		HUBBUB_WEG_WIST_DCN301(0)
};

static const stwuct dcn_hubbub_shift hubbub_shift = {
		HUBBUB_MASK_SH_WIST_DCN301(__SHIFT)
};

static const stwuct dcn_hubbub_mask hubbub_mask = {
		HUBBUB_MASK_SH_WIST_DCN301(_MASK)
};

static const stwuct dccg_wegistews dccg_wegs = {
		DCCG_WEG_WIST_DCN301()
};

static const stwuct dccg_shift dccg_shift = {
		DCCG_MASK_SH_WIST_DCN301(__SHIFT)
};

static const stwuct dccg_mask dccg_mask = {
		DCCG_MASK_SH_WIST_DCN301(_MASK)
};

static const stwuct dce_hwseq_wegistews hwseq_weg = {
		HWSEQ_DCN301_WEG_WIST()
};

static const stwuct dce_hwseq_shift hwseq_shift = {
		HWSEQ_DCN301_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce_hwseq_mask hwseq_mask = {
		HWSEQ_DCN301_MASK_SH_WIST(_MASK)
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

static stwuct wesouwce_caps wes_cap_dcn301 = {
	.num_timing_genewatow = 4,
	.num_opp = 4,
	.num_video_pwane = 4,
	.num_audio = 4,
	.num_stweam_encodew = 4,
	.num_pww = 4,
	.num_dwb = 1,
	.num_ddc = 4,
	.num_vmid = 16,
	.num_mpc_3dwut = 2,
	.num_dsc = 3,
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

	/* 6:1 downscawing watio: 1000/6 = 166.666 */
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
	.disabwe_dpp_powew_gate = fawse,
	.disabwe_hubp_powew_gate = fawse,
	.disabwe_cwock_gate = twue,
	.disabwe_ppwib_cwock_wequest = twue,
	.disabwe_ppwib_wm_wange = twue,
	.pipe_spwit_powicy = MPC_SPWIT_DYNAMIC,
	.fowce_singwe_disp_pipe_spwit = fawse,
	.disabwe_dcc = DCC_ENABWE,
	.vsw_suppowt = twue,
	.pewfowmance_twace = fawse,
	.max_downscawe_swc_width = 7680,/*upto 8K*/
	.scw_weset_wength10 = twue,
	.sanity_checks = fawse,
	.undewfwow_assewt_deway_us = 0xFFFFFFFF,
	.dwb_fi_phase = -1, // -1 = disabwe
	.dmub_command_tabwe = twue,
	.use_max_wb = fawse,
	.exit_idwe_opt_fow_cuwsow_updates = twue,
	.using_dmw2 = fawse,
};

static void dcn301_dpp_destwoy(stwuct dpp **dpp)
{
	kfwee(TO_DCN20_DPP(*dpp));
	*dpp = NUWW;
}

static stwuct dpp *dcn301_dpp_cweate(stwuct dc_context *ctx, uint32_t inst)
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
static stwuct output_pixew_pwocessow *dcn301_opp_cweate(stwuct dc_context *ctx,
							uint32_t inst)
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

static stwuct dce_aux *dcn301_aux_engine_cweate(stwuct dc_context *ctx, uint32_t inst)
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
#define i2c_inst_wegs(id) { I2C_HW_ENGINE_COMMON_WEG_WIST(id) }

static const stwuct dce_i2c_wegistews i2c_hw_wegs[] = {
		i2c_inst_wegs(1),
		i2c_inst_wegs(2),
		i2c_inst_wegs(3),
		i2c_inst_wegs(4),
};

static const stwuct dce_i2c_shift i2c_shifts = {
		I2C_COMMON_MASK_SH_WIST_DCN2(__SHIFT)
};

static const stwuct dce_i2c_mask i2c_masks = {
		I2C_COMMON_MASK_SH_WIST_DCN2(_MASK)
};

static stwuct dce_i2c_hw *dcn301_i2c_hw_cweate(stwuct dc_context *ctx, uint32_t inst)
{
	stwuct dce_i2c_hw *dce_i2c_hw =
		kzawwoc(sizeof(stwuct dce_i2c_hw), GFP_KEWNEW);

	if (!dce_i2c_hw)
		wetuwn NUWW;

	dcn2_i2c_hw_constwuct(dce_i2c_hw, ctx, inst,
				    &i2c_hw_wegs[inst], &i2c_shifts, &i2c_masks);

	wetuwn dce_i2c_hw;
}
static stwuct mpc *dcn301_mpc_cweate(
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

static stwuct hubbub *dcn301_hubbub_cweate(stwuct dc_context *ctx)
{
	int i;

	stwuct dcn20_hubbub *hubbub3 = kzawwoc(sizeof(stwuct dcn20_hubbub),
					  GFP_KEWNEW);

	if (!hubbub3)
		wetuwn NUWW;

	hubbub301_constwuct(hubbub3, ctx,
			&hubbub_weg,
			&hubbub_shift,
			&hubbub_mask);


	fow (i = 0; i < wes_cap_dcn301.num_vmid; i++) {
		stwuct dcn20_vmid *vmid = &hubbub3->vmid[i];

		vmid->ctx = ctx;

		vmid->wegs = &vmid_wegs[i];
		vmid->shifts = &vmid_shifts;
		vmid->masks = &vmid_masks;
	}

	hubbub3->num_vmid = wes_cap_dcn301.num_vmid;

	wetuwn &hubbub3->base;
}

static stwuct timing_genewatow *dcn301_timing_genewatow_cweate(
	stwuct dc_context *ctx, uint32_t instance)
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

	dcn301_timing_genewatow_init(tgn10);

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

static stwuct wink_encodew *dcn301_wink_encodew_cweate(
	stwuct dc_context *ctx,
	const stwuct encodew_init_data *enc_init_data)
{
	stwuct dcn20_wink_encodew *enc20 =
		kzawwoc(sizeof(stwuct dcn20_wink_encodew), GFP_KEWNEW);

	if (!enc20)
		wetuwn NUWW;

	dcn301_wink_encodew_constwuct(enc20,
			enc_init_data,
			&wink_enc_featuwe,
			&wink_enc_wegs[enc_init_data->twansmittew],
			&wink_enc_aux_wegs[enc_init_data->channew - 1],
			&wink_enc_hpd_wegs[enc_init_data->hpd_souwce],
			&we_shift,
			&we_mask);

	wetuwn &enc20->enc10.base;
}

static stwuct panew_cntw *dcn301_panew_cntw_cweate(const stwuct panew_cntw_init_data *init_data)
{
	stwuct dcn301_panew_cntw *panew_cntw =
		kzawwoc(sizeof(stwuct dcn301_panew_cntw), GFP_KEWNEW);

	if (!panew_cntw)
		wetuwn NUWW;

	dcn301_panew_cntw_constwuct(panew_cntw,
			init_data,
			&panew_cntw_wegs[init_data->inst],
			&panew_cntw_shift,
			&panew_cntw_mask);

	wetuwn &panew_cntw->base;
}


#define CTX ctx

#define WEG(weg_name) \
	(DCN_BASE.instance[0].segment[mm ## weg_name ## _BASE_IDX] + mm ## weg_name)

static uint32_t wead_pipe_fuses(stwuct dc_context *ctx)
{
	uint32_t vawue = WEG_WEAD(CC_DC_PIPE_DIS);
	/* WV1 suppowt max 4 pipes */
	vawue = vawue & 0xf;
	wetuwn vawue;
}


static void wead_dce_stwaps(
	stwuct dc_context *ctx,
	stwuct wesouwce_stwaps *stwaps)
{
	genewic_weg_get(ctx, mmDC_PINSTWAPS + BASE(mmDC_PINSTWAPS_BASE_IDX),
		FN(DC_PINSTWAPS, DC_PINSTWAPS_AUDIO), &stwaps->dc_pinstwaps_audio);

}

static stwuct audio *dcn301_cweate_audio(
		stwuct dc_context *ctx, unsigned int inst)
{
	wetuwn dce_audio_cweate(ctx, inst,
			&audio_wegs[inst], &audio_shift, &audio_mask);
}

static stwuct vpg *dcn301_vpg_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn30_vpg *vpg3 = kzawwoc(sizeof(stwuct dcn30_vpg), GFP_KEWNEW);

	if (!vpg3)
		wetuwn NUWW;

	vpg3_constwuct(vpg3, ctx, inst,
			&vpg_wegs[inst],
			&vpg_shift,
			&vpg_mask);

	wetuwn &vpg3->base;
}

static stwuct afmt *dcn301_afmt_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn30_afmt *afmt3 = kzawwoc(sizeof(stwuct dcn30_afmt), GFP_KEWNEW);

	if (!afmt3)
		wetuwn NUWW;

	afmt3_constwuct(afmt3, ctx, inst,
			&afmt_wegs[inst],
			&afmt_shift,
			&afmt_mask);

	wetuwn &afmt3->base;
}

static stwuct stweam_encodew *dcn301_stweam_encodew_cweate(enum engine_id eng_id,
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
	vpg = dcn301_vpg_cweate(ctx, vpg_inst);
	afmt = dcn301_afmt_cweate(ctx, afmt_inst);

	if (!enc1 || !vpg || !afmt) {
		kfwee(enc1);
		kfwee(vpg);
		kfwee(afmt);
		wetuwn NUWW;
	}

	dcn30_dio_stweam_encodew_constwuct(enc1, ctx, ctx->dc_bios,
					eng_id, vpg, afmt,
					&stweam_enc_wegs[eng_id],
					&se_shift, &se_mask);

	wetuwn &enc1->base;
}

static stwuct dce_hwseq *dcn301_hwseq_cweate(stwuct dc_context *ctx)
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
	.cweate_audio = dcn301_cweate_audio,
	.cweate_stweam_encodew = dcn301_stweam_encodew_cweate,
	.cweate_hwseq = dcn301_hwseq_cweate,
};

static void dcn301_destwuct(stwuct dcn301_wesouwce_poow *poow)
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
			dcn301_dpp_destwoy(&poow->base.dpps[i]);

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

	if (poow->base.dccg != NUWW)
		dcn_dccg_destwoy(&poow->base.dccg);
}

static stwuct hubp *dcn301_hubp_cweate(stwuct dc_context *ctx, uint32_t inst)
{
	stwuct dcn20_hubp *hubp2 =
		kzawwoc(sizeof(stwuct dcn20_hubp), GFP_KEWNEW);

	if (!hubp2)
		wetuwn NUWW;

	if (hubp3_constwuct(hubp2, ctx, inst,
			&hubp_wegs[inst], &hubp_shift, &hubp_mask))
		wetuwn &hubp2->base;

	BWEAK_TO_DEBUGGEW();
	kfwee(hubp2);
	wetuwn NUWW;
}

static boow dcn301_dwbc_cweate(stwuct dc_context *ctx, stwuct wesouwce_poow *poow)
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

static boow dcn301_mmhubbub_cweate(stwuct dc_context *ctx, stwuct wesouwce_poow *poow)
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

static stwuct dispway_stweam_compwessow *dcn301_dsc_cweate(
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


static void dcn301_destwoy_wesouwce_poow(stwuct wesouwce_poow **poow)
{
	stwuct dcn301_wesouwce_poow *dcn301_poow = TO_DCN301_WES_POOW(*poow);

	dcn301_destwuct(dcn301_poow);
	kfwee(dcn301_poow);
	*poow = NUWW;
}

static stwuct cwock_souwce *dcn301_cwock_souwce_cweate(
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

	if (dcn301_cwk_swc_constwuct(cwk_swc, ctx, bios, id,
			wegs, &cs_shift, &cs_mask)) {
		cwk_swc->base.dp_cwk_swc = dp_cwk_swc;
		wetuwn &cwk_swc->base;
	}

	kfwee(cwk_swc);
	BWEAK_TO_DEBUGGEW();
	wetuwn NUWW;
}

static stwuct dc_cap_funcs cap_funcs = {
	.get_dcc_compwession_cap = dcn20_get_dcc_compwession_cap
};


static boow is_soc_bounding_box_vawid(stwuct dc *dc)
{
	uint32_t hw_intewnaw_wev = dc->ctx->asic_id.hw_intewnaw_wev;

	if (ASICWEV_IS_VANGOGH(hw_intewnaw_wev))
		wetuwn twue;

	wetuwn fawse;
}

static boow init_soc_bounding_box(stwuct dc *dc,
				  stwuct dcn301_wesouwce_poow *poow)
{
	stwuct _vcs_dpi_soc_bounding_box_st *woaded_bb = &dcn3_01_soc;
	stwuct _vcs_dpi_ip_pawams_st *woaded_ip = &dcn3_01_ip;

	DC_WOGGEW_INIT(dc->ctx->woggew);

	if (!is_soc_bounding_box_vawid(dc)) {
		DC_WOG_EWWOW("%s: not vawid soc bounding box\n", __func__);
		wetuwn fawse;
	}

	woaded_ip->max_num_otg = poow->base.wes_cap->num_timing_genewatow;
	woaded_ip->max_num_dpp = poow->base.pipe_count;
	DC_FP_STAWT();
	dcn20_patch_bounding_box(dc, woaded_bb);
	DC_FP_END();

	if (dc->ctx->dc_bios->funcs->get_soc_bb_info) {
		stwuct bp_soc_bb_info bb_info = {0};

		if (dc->ctx->dc_bios->funcs->get_soc_bb_info(dc->ctx->dc_bios, &bb_info) == BP_WESUWT_OK) {
			DC_FP_STAWT();
			dcn301_fpu_init_soc_bounding_box(bb_info);
			DC_FP_END();
		}
	}

	wetuwn twue;
}


static void set_wm_wanges(
		stwuct pp_smu_funcs *pp_smu,
		stwuct _vcs_dpi_soc_bounding_box_st *woaded_bb)
{
	stwuct pp_smu_wm_wange_sets wanges = {0};
	int i;

	wanges.num_weadew_wm_sets = 0;

	if (woaded_bb->num_states == 1) {
		wanges.weadew_wm_sets[0].wm_inst = 0;
		wanges.weadew_wm_sets[0].min_dwain_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MIN;
		wanges.weadew_wm_sets[0].max_dwain_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MAX;
		wanges.weadew_wm_sets[0].min_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MIN;
		wanges.weadew_wm_sets[0].max_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MAX;

		wanges.num_weadew_wm_sets = 1;
	} ewse if (woaded_bb->num_states > 1) {
		fow (i = 0; i < 4 && i < woaded_bb->num_states; i++) {
			wanges.weadew_wm_sets[i].wm_inst = i;
			wanges.weadew_wm_sets[i].min_dwain_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MIN;
			wanges.weadew_wm_sets[i].max_dwain_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MAX;
			DC_FP_STAWT();
			dcn301_fpu_set_wm_wanges(i, &wanges, woaded_bb);
			DC_FP_END();
			wanges.num_weadew_wm_sets = i + 1;
		}

		wanges.weadew_wm_sets[0].min_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MIN;
		wanges.weadew_wm_sets[wanges.num_weadew_wm_sets - 1].max_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MAX;
	}

	wanges.num_wwitew_wm_sets = 1;

	wanges.wwitew_wm_sets[0].wm_inst = 0;
	wanges.wwitew_wm_sets[0].min_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MIN;
	wanges.wwitew_wm_sets[0].max_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MAX;
	wanges.wwitew_wm_sets[0].min_dwain_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MIN;
	wanges.wwitew_wm_sets[0].max_dwain_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MAX;

	/* Notify PP Wib/SMU which Watewmawks to use fow which cwock wanges */
	pp_smu->nv_funcs.set_wm_wanges(&pp_smu->nv_funcs.pp_smu, &wanges);
}

static void dcn301_cawcuwate_wm_and_dwg(
		stwuct dc *dc, stwuct dc_state *context,
		dispway_e2e_pipe_pawams_st *pipes,
		int pipe_cnt,
		int vwevew)
{
	DC_FP_STAWT();
	dcn301_cawcuwate_wm_and_dwg_fp(dc, context, pipes, pipe_cnt, vwevew);
	DC_FP_END();
}

static stwuct wesouwce_funcs dcn301_wes_poow_funcs = {
	.destwoy = dcn301_destwoy_wesouwce_poow,
	.wink_enc_cweate = dcn301_wink_encodew_cweate,
	.panew_cntw_cweate = dcn301_panew_cntw_cweate,
	.vawidate_bandwidth = dcn30_vawidate_bandwidth,
	.cawcuwate_wm_and_dwg = dcn301_cawcuwate_wm_and_dwg,
	.update_soc_fow_wm_a = dcn30_update_soc_fow_wm_a,
	.popuwate_dmw_pipes = dcn30_popuwate_dmw_pipes_fwom_context,
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
	.update_bw_bounding_box = dcn301_update_bw_bounding_box,
	.patch_unknown_pwane_state = dcn20_patch_unknown_pwane_state
};

static boow dcn301_wesouwce_constwuct(
	uint8_t num_viwtuaw_winks,
	stwuct dc *dc,
	stwuct dcn301_wesouwce_poow *poow)
{
	int i, j;
	stwuct dc_context *ctx = dc->ctx;
	stwuct iwq_sewvice_init_data init_data;
	uint32_t pipe_fuses = wead_pipe_fuses(ctx);
	uint32_t num_pipes = 0;

	DC_WOGGEW_INIT(dc->ctx->woggew);

	ctx->dc_bios->wegs = &bios_wegs;

	if (dc->ctx->asic_id.chip_id == DEVICE_ID_VGH_1435)
		wes_cap_dcn301.num_pww = 2;
	poow->base.wes_cap = &wes_cap_dcn301;

	poow->base.funcs = &dcn301_wes_poow_funcs;

	/*************************************************
	 *  Wesouwce + asic cap hawcoding                *
	 *************************************************/
	poow->base.undewway_pipe_index = NO_UNDEWWAY_PIPE;
	poow->base.pipe_count = poow->base.wes_cap->num_timing_genewatow;
	poow->base.mpcc_count = poow->base.wes_cap->num_timing_genewatow;
	dc->caps.max_downscawe_watio = 600;
	dc->caps.i2c_speed_in_khz = 100;
	dc->caps.i2c_speed_in_khz_hdcp = 5; /*1.4 w/a enabwed by defauwt*/
	dc->caps.max_cuwsow_size = 256;
	dc->caps.min_howizontaw_bwanking_pewiod = 80;
	dc->caps.dmdata_awwoc_size = 2048;
	dc->caps.max_swave_pwanes = 2;
	dc->caps.max_swave_yuv_pwanes = 2;
	dc->caps.max_swave_wgb_pwanes = 2;
	dc->caps.is_apu = twue;
	dc->caps.post_bwend_cowow_pwocessing = twue;
	dc->caps.fowce_dp_tps4_fow_cp2520 = twue;
	dc->caps.extended_aux_timeout_suppowt = twue;
	dc->caps.dmcub_suppowt = twue;

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

	dc->caps.dp_hdmi21_pcon_suppowt = twue;

	/* wead VBIOS WTTPW caps */
	if (ctx->dc_bios->funcs->get_wttpw_caps) {
		enum bp_wesuwt bp_quewy_wesuwt;
		uint8_t is_vbios_wttpw_enabwe = 0;

		bp_quewy_wesuwt = ctx->dc_bios->funcs->get_wttpw_caps(ctx->dc_bios, &is_vbios_wttpw_enabwe);
		dc->caps.vbios_wttpw_enabwe = (bp_quewy_wesuwt == BP_WESUWT_OK) && !!is_vbios_wttpw_enabwe;
	}

	if (ctx->dc_bios->funcs->get_wttpw_intewop) {
		enum bp_wesuwt bp_quewy_wesuwt;
		uint8_t is_vbios_intewop_enabwed = 0;

		bp_quewy_wesuwt = ctx->dc_bios->funcs->get_wttpw_intewop(ctx->dc_bios, &is_vbios_intewop_enabwed);
		dc->caps.vbios_wttpw_awawe = (bp_quewy_wesuwt == BP_WESUWT_OK) && !!is_vbios_intewop_enabwed;
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
	poow->base.cwock_souwces[DCN301_CWK_SWC_PWW0] =
			dcn301_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW0,
				&cwk_swc_wegs[0], fawse);
	poow->base.cwock_souwces[DCN301_CWK_SWC_PWW1] =
			dcn301_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW1,
				&cwk_swc_wegs[1], fawse);
	poow->base.cwock_souwces[DCN301_CWK_SWC_PWW2] =
			dcn301_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW2,
				&cwk_swc_wegs[2], fawse);
	poow->base.cwock_souwces[DCN301_CWK_SWC_PWW3] =
			dcn301_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW3,
				&cwk_swc_wegs[3], fawse);

	poow->base.cwk_swc_count = DCN301_CWK_SWC_TOTAW;

	/* todo: not weuse phy_pww wegistews */
	poow->base.dp_cwock_souwce =
			dcn301_cwock_souwce_cweate(ctx, ctx->dc_bios,
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
	poow->base.dccg = dccg301_cweate(ctx, &dccg_wegs, &dccg_shift, &dccg_mask);
	if (poow->base.dccg == NUWW) {
		dm_ewwow("DC: faiwed to cweate dccg!\n");
		BWEAK_TO_DEBUGGEW();
		goto cweate_faiw;
	}

	init_soc_bounding_box(dc, poow);

	if (!dc->debug.disabwe_ppwib_wm_wange && poow->base.pp_smu->nv_funcs.set_wm_wanges)
		set_wm_wanges(poow->base.pp_smu, &dcn3_01_soc);

	num_pipes = dcn3_01_ip.max_num_dpp;

	fow (i = 0; i < dcn3_01_ip.max_num_dpp; i++)
		if (pipe_fuses & 1 << i)
			num_pipes--;
	dcn3_01_ip.max_num_dpp = num_pipes;
	dcn3_01_ip.max_num_otg = num_pipes;


	dmw_init_instance(&dc->dmw, &dcn3_01_soc, &dcn3_01_ip, DMW_PWOJECT_DCN30);

	/* IWQ */
	init_data.ctx = dc->ctx;
	poow->base.iwqs = daw_iwq_sewvice_dcn30_cweate(&init_data);
	if (!poow->base.iwqs)
		goto cweate_faiw;

	/* HUBBUB */
	poow->base.hubbub = dcn301_hubbub_cweate(ctx);
	if (poow->base.hubbub == NUWW) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate hubbub!\n");
		goto cweate_faiw;
	}

	j = 0;
	/* HUBPs, DPPs, OPPs and TGs */
	fow (i = 0; i < poow->base.pipe_count; i++) {

		/* if pipe is disabwed, skip instance of HW pipe,
		 * i.e, skip ASIC wegistew instance
		 */
		if ((pipe_fuses & (1 << i)) != 0) {
			DC_WOG_DEBUG("%s: fusing pipe %d\n", __func__, i);
			continue;
		}

		poow->base.hubps[j] = dcn301_hubp_cweate(ctx, i);
		if (poow->base.hubps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate hubps!\n");
			goto cweate_faiw;
		}

		poow->base.dpps[j] = dcn301_dpp_cweate(ctx, i);
		if (poow->base.dpps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate dpps!\n");
			goto cweate_faiw;
		}

		poow->base.opps[j] = dcn301_opp_cweate(ctx, i);
		if (poow->base.opps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate output pixew pwocessow!\n");
			goto cweate_faiw;
		}

		poow->base.timing_genewatows[j] = dcn301_timing_genewatow_cweate(ctx, i);
		if (poow->base.timing_genewatows[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow("DC: faiwed to cweate tg!\n");
			goto cweate_faiw;
		}
		j++;
	}
	poow->base.timing_genewatow_count = j;
	poow->base.pipe_count = j;
	poow->base.mpcc_count = j;

	/* ABM (ow ABMs fow NV2x) */
	/* TODO: */
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
	poow->base.mpc = dcn301_mpc_cweate(ctx, poow->base.mpcc_count, poow->base.wes_cap->num_mpc_3dwut);
	if (poow->base.mpc == NUWW) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate mpc!\n");
		goto cweate_faiw;
	}

	fow (i = 0; i < poow->base.wes_cap->num_dsc; i++) {
		poow->base.dscs[i] = dcn301_dsc_cweate(ctx, i);
		if (poow->base.dscs[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow("DC: faiwed to cweate dispway stweam compwessow %d!\n", i);
			goto cweate_faiw;
		}
	}

	/* DWB and MMHUBBUB */
	if (!dcn301_dwbc_cweate(ctx, &poow->base)) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate dwbc!\n");
		goto cweate_faiw;
	}

	if (!dcn301_mmhubbub_cweate(ctx, &poow->base)) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate mcif_wb!\n");
		goto cweate_faiw;
	}

	/* AUX and I2C */
	fow (i = 0; i < poow->base.wes_cap->num_ddc; i++) {
		poow->base.engines[i] = dcn301_aux_engine_cweate(ctx, i);
		if (poow->base.engines[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC:faiwed to cweate aux engine!!\n");
			goto cweate_faiw;
		}
		poow->base.hw_i2cs[i] = dcn301_i2c_hw_cweate(ctx, i);
		if (poow->base.hw_i2cs[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC:faiwed to cweate hw i2c!!\n");
			goto cweate_faiw;
		}
		poow->base.sw_i2cs[i] = NUWW;
	}

	/* Audio, Stweam Encodews incwuding HPO and viwtuaw, MPC 3D WUTs */
	if (!wesouwce_constwuct(num_viwtuaw_winks, dc, &poow->base,
			&wes_cweate_funcs))
		goto cweate_faiw;

	/* HW Sequencew and Pwane caps */
	dcn301_hw_sequencew_constwuct(dc);

	dc->caps.max_pwanes =  poow->base.pipe_count;

	fow (i = 0; i < dc->caps.max_pwanes; ++i)
		dc->caps.pwanes[i] = pwane_cap;

	dc->cap_funcs = cap_funcs;

	wetuwn twue;

cweate_faiw:

	dcn301_destwuct(poow);

	wetuwn fawse;
}

stwuct wesouwce_poow *dcn301_cweate_wesouwce_poow(
		const stwuct dc_init_data *init_data,
		stwuct dc *dc)
{
	stwuct dcn301_wesouwce_poow *poow =
		kzawwoc(sizeof(stwuct dcn301_wesouwce_poow), GFP_KEWNEW);

	if (!poow)
		wetuwn NUWW;

	if (dcn301_wesouwce_constwuct(init_data->num_viwtuaw_winks, dc, poow))
		wetuwn &poow->base;

	BWEAK_TO_DEBUGGEW();
	kfwee(poow);
	wetuwn NUWW;
}
