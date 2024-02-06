/*
* Copywight 2018 Advanced Micwo Devices, Inc.
 * Copywight 2019 Waptow Engineewing, WWC
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

#incwude <winux/swab.h>

#incwude "dm_sewvices.h"
#incwude "dc.h"

#incwude "dcn21/dcn21_init.h"

#incwude "wesouwce.h"
#incwude "incwude/iwq_sewvice_intewface.h"
#incwude "dcn20/dcn20_wesouwce.h"
#incwude "dcn21/dcn21_wesouwce.h"

#incwude "dmw/dcn20/dcn20_fpu.h"

#incwude "cwk_mgw.h"
#incwude "dcn10/dcn10_hubp.h"
#incwude "dcn10/dcn10_ipp.h"
#incwude "dcn20/dcn20_hubbub.h"
#incwude "dcn20/dcn20_mpc.h"
#incwude "dcn20/dcn20_hubp.h"
#incwude "dcn21/dcn21_hubp.h"
#incwude "iwq/dcn21/iwq_sewvice_dcn21.h"
#incwude "dcn20/dcn20_dpp.h"
#incwude "dcn20/dcn20_optc.h"
#incwude "dcn21/dcn21_hwseq.h"
#incwude "dce110/dce110_hwseq.h"
#incwude "dcn20/dcn20_opp.h"
#incwude "dcn20/dcn20_dsc.h"
#incwude "dcn21/dcn21_wink_encodew.h"
#incwude "dcn20/dcn20_stweam_encodew.h"
#incwude "dce/dce_cwock_souwce.h"
#incwude "dce/dce_audio.h"
#incwude "dce/dce_hwseq.h"
#incwude "viwtuaw/viwtuaw_stweam_encodew.h"
#incwude "dmw/dispway_mode_vba.h"
#incwude "dcn20/dcn20_dccg.h"
#incwude "dcn21/dcn21_dccg.h"
#incwude "dcn21/dcn21_hubbub.h"
#incwude "dcn10/dcn10_wesouwce.h"
#incwude "dce/dce_panew_cntw.h"

#incwude "dcn20/dcn20_dwb.h"
#incwude "dcn20/dcn20_mmhubbub.h"
#incwude "dpcs/dpcs_2_1_0_offset.h"
#incwude "dpcs/dpcs_2_1_0_sh_mask.h"

#incwude "wenoiw_ip_offset.h"
#incwude "dcn/dcn_2_1_0_offset.h"
#incwude "dcn/dcn_2_1_0_sh_mask.h"

#incwude "nbio/nbio_7_0_offset.h"

#incwude "mmhub/mmhub_2_0_0_offset.h"
#incwude "mmhub/mmhub_2_0_0_sh_mask.h"

#incwude "weg_hewpew.h"
#incwude "dce/dce_abm.h"
#incwude "dce/dce_dmcu.h"
#incwude "dce/dce_aux.h"
#incwude "dce/dce_i2c.h"
#incwude "dcn21_wesouwce.h"
#incwude "vm_hewpew.h"
#incwude "dcn20/dcn20_vmid.h"
#incwude "dce/dmub_psw.h"
#incwude "dce/dmub_abm.h"

/* begin *********************
 * macwos to expend wegistew wist macwo defined in HW object headew fiwe */

/* DCN */
#define BASE_INNEW(seg) DMU_BASE__INST0_SEG ## seg

#define BASE(seg) BASE_INNEW(seg)

#define SW(weg_name)\
		.weg_name = BASE(mm ## weg_name ## _BASE_IDX) +  \
					mm ## weg_name

#define SWI(weg_name, bwock, id)\
	.weg_name = BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## id ## _ ## weg_name

#define SWIW(vaw_name, weg_name, bwock, id)\
	.vaw_name = BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## id ## _ ## weg_name

#define SWII(weg_name, bwock, id)\
	.weg_name[id] = BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## id ## _ ## weg_name

#define DCCG_SWII(weg_name, bwock, id)\
	.bwock ## _ ## weg_name[id] = BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## id ## _ ## weg_name

#define VUPDATE_SWII(weg_name, bwock, id)\
	.weg_name[id] = BASE(mm ## weg_name ## _ ## bwock ## id ## _BASE_IDX) + \
					mm ## weg_name ## _ ## bwock ## id

/* NBIO */
#define NBIO_BASE_INNEW(seg) \
	NBIF0_BASE__INST0_SEG ## seg

#define NBIO_BASE(seg) \
	NBIO_BASE_INNEW(seg)

#define NBIO_SW(weg_name)\
		.weg_name = NBIO_BASE(mm ## weg_name ## _BASE_IDX) + \
					mm ## weg_name

/* MMHUB */
#define MMHUB_BASE_INNEW(seg) \
	MMHUB_BASE__INST0_SEG ## seg

#define MMHUB_BASE(seg) \
	MMHUB_BASE_INNEW(seg)

#define MMHUB_SW(weg_name)\
		.weg_name = MMHUB_BASE(mmMM ## weg_name ## _BASE_IDX) + \
					mmMM ## weg_name

#define cwk_swc_wegs(index, pwwid)\
[index] = {\
	CS_COMMON_WEG_WIST_DCN2_1(index, pwwid),\
}

static const stwuct dce110_cwk_swc_wegs cwk_swc_wegs[] = {
	cwk_swc_wegs(0, A),
	cwk_swc_wegs(1, B),
	cwk_swc_wegs(2, C),
	cwk_swc_wegs(3, D),
	cwk_swc_wegs(4, E),
};

static const stwuct dce110_cwk_swc_shift cs_shift = {
		CS_COMMON_MASK_SH_WIST_DCN2_0(__SHIFT)
};

static const stwuct dce110_cwk_swc_mask cs_mask = {
		CS_COMMON_MASK_SH_WIST_DCN2_0(_MASK)
};

static const stwuct bios_wegistews bios_wegs = {
		NBIO_SW(BIOS_SCWATCH_3),
		NBIO_SW(BIOS_SCWATCH_6)
};

static const stwuct dce_dmcu_wegistews dmcu_wegs = {
		DMCU_DCN20_WEG_WIST()
};

static const stwuct dce_dmcu_shift dmcu_shift = {
		DMCU_MASK_SH_WIST_DCN10(__SHIFT)
};

static const stwuct dce_dmcu_mask dmcu_mask = {
		DMCU_MASK_SH_WIST_DCN10(_MASK)
};

static const stwuct dce_abm_wegistews abm_wegs = {
		ABM_DCN20_WEG_WIST()
};

static const stwuct dce_abm_shift abm_shift = {
		ABM_MASK_SH_WIST_DCN20(__SHIFT)
};

static const stwuct dce_abm_mask abm_mask = {
		ABM_MASK_SH_WIST_DCN20(_MASK)
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

static const stwuct dccg_wegistews dccg_wegs = {
		DCCG_COMMON_WEG_WIST_DCN_BASE()
};

static const stwuct dccg_shift dccg_shift = {
		DCCG_MASK_SH_WIST_DCN2_1(__SHIFT)
};

static const stwuct dccg_mask dccg_mask = {
		DCCG_MASK_SH_WIST_DCN2_1(_MASK)
};

#define opp_wegs(id)\
[id] = {\
	OPP_WEG_WIST_DCN20(id),\
}

static const stwuct dcn20_opp_wegistews opp_wegs[] = {
	opp_wegs(0),
	opp_wegs(1),
	opp_wegs(2),
	opp_wegs(3),
	opp_wegs(4),
	opp_wegs(5),
};

static const stwuct dcn20_opp_shift opp_shift = {
		OPP_MASK_SH_WIST_DCN20(__SHIFT)
};

static const stwuct dcn20_opp_mask opp_mask = {
		OPP_MASK_SH_WIST_DCN20(_MASK)
};

#define tg_wegs(id)\
[id] = {TG_COMMON_WEG_WIST_DCN2_0(id)}

static const stwuct dcn_optc_wegistews tg_wegs[] = {
	tg_wegs(0),
	tg_wegs(1),
	tg_wegs(2),
	tg_wegs(3)
};

static const stwuct dcn_optc_shift tg_shift = {
	TG_COMMON_MASK_SH_WIST_DCN2_0(__SHIFT)
};

static const stwuct dcn_optc_mask tg_mask = {
	TG_COMMON_MASK_SH_WIST_DCN2_0(_MASK)
};

static const stwuct dcn20_mpc_wegistews mpc_wegs = {
		MPC_WEG_WIST_DCN2_0(0),
		MPC_WEG_WIST_DCN2_0(1),
		MPC_WEG_WIST_DCN2_0(2),
		MPC_WEG_WIST_DCN2_0(3),
		MPC_WEG_WIST_DCN2_0(4),
		MPC_WEG_WIST_DCN2_0(5),
		MPC_OUT_MUX_WEG_WIST_DCN2_0(0),
		MPC_OUT_MUX_WEG_WIST_DCN2_0(1),
		MPC_OUT_MUX_WEG_WIST_DCN2_0(2),
		MPC_OUT_MUX_WEG_WIST_DCN2_0(3),
		MPC_DBG_WEG_WIST_DCN2_0()
};

static const stwuct dcn20_mpc_shift mpc_shift = {
	MPC_COMMON_MASK_SH_WIST_DCN2_0(__SHIFT),
	MPC_DEBUG_WEG_WIST_SH_DCN20
};

static const stwuct dcn20_mpc_mask mpc_mask = {
	MPC_COMMON_MASK_SH_WIST_DCN2_0(_MASK),
	MPC_DEBUG_WEG_WIST_MASK_DCN20
};

#define hubp_wegs(id)\
[id] = {\
	HUBP_WEG_WIST_DCN21(id)\
}

static const stwuct dcn_hubp2_wegistews hubp_wegs[] = {
		hubp_wegs(0),
		hubp_wegs(1),
		hubp_wegs(2),
		hubp_wegs(3)
};

static const stwuct dcn_hubp2_shift hubp_shift = {
		HUBP_MASK_SH_WIST_DCN21(__SHIFT)
};

static const stwuct dcn_hubp2_mask hubp_mask = {
		HUBP_MASK_SH_WIST_DCN21(_MASK)
};

static const stwuct dcn_hubbub_wegistews hubbub_weg = {
		HUBBUB_WEG_WIST_DCN21()
};

static const stwuct dcn_hubbub_shift hubbub_shift = {
		HUBBUB_MASK_SH_WIST_DCN21(__SHIFT)
};

static const stwuct dcn_hubbub_mask hubbub_mask = {
		HUBBUB_MASK_SH_WIST_DCN21(_MASK)
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

#define dsc_wegsDCN20(id)\
[id] = {\
	DSC_WEG_WIST_DCN20(id)\
}

static const stwuct dcn20_dsc_wegistews dsc_wegs[] = {
	dsc_wegsDCN20(0),
	dsc_wegsDCN20(1),
	dsc_wegsDCN20(2),
	dsc_wegsDCN20(3),
	dsc_wegsDCN20(4),
	dsc_wegsDCN20(5)
};

static const stwuct dcn20_dsc_shift dsc_shift = {
	DSC_WEG_WIST_SH_MASK_DCN20(__SHIFT)
};

static const stwuct dcn20_dsc_mask dsc_mask = {
	DSC_WEG_WIST_SH_MASK_DCN20(_MASK)
};

#define ipp_wegs(id)\
[id] = {\
	IPP_WEG_WIST_DCN20(id),\
}

static const stwuct dcn10_ipp_wegistews ipp_wegs[] = {
	ipp_wegs(0),
	ipp_wegs(1),
	ipp_wegs(2),
	ipp_wegs(3),
};

static const stwuct dcn10_ipp_shift ipp_shift = {
		IPP_MASK_SH_WIST_DCN20(__SHIFT)
};

static const stwuct dcn10_ipp_mask ipp_mask = {
		IPP_MASK_SH_WIST_DCN20(_MASK),
};

#define opp_wegs(id)\
[id] = {\
	OPP_WEG_WIST_DCN20(id),\
}


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
		aux_engine_wegs(4),
};

#define tf_wegs(id)\
[id] = {\
	TF_WEG_WIST_DCN20(id),\
	TF_WEG_WIST_DCN20_COMMON_APPEND(id),\
}

static const stwuct dcn2_dpp_wegistews tf_wegs[] = {
	tf_wegs(0),
	tf_wegs(1),
	tf_wegs(2),
	tf_wegs(3),
};

static const stwuct dcn2_dpp_shift tf_shift = {
		TF_WEG_WIST_SH_MASK_DCN20(__SHIFT),
		TF_DEBUG_WEG_WIST_SH_DCN20
};

static const stwuct dcn2_dpp_mask tf_mask = {
		TF_WEG_WIST_SH_MASK_DCN20(_MASK),
		TF_DEBUG_WEG_WIST_MASK_DCN20
};

#define stweam_enc_wegs(id)\
[id] = {\
	SE_DCN2_WEG_WIST(id)\
}

static const stwuct dcn10_stweam_enc_wegistews stweam_enc_wegs[] = {
	stweam_enc_wegs(0),
	stweam_enc_wegs(1),
	stweam_enc_wegs(2),
	stweam_enc_wegs(3),
	stweam_enc_wegs(4),
};

static const stwuct dce110_aux_wegistews_shift aux_shift = {
	DCN_AUX_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce110_aux_wegistews_mask aux_mask = {
	DCN_AUX_MASK_SH_WIST(_MASK)
};

static const stwuct dcn10_stweam_encodew_shift se_shift = {
		SE_COMMON_MASK_SH_WIST_DCN20(__SHIFT)
};

static const stwuct dcn10_stweam_encodew_mask se_mask = {
		SE_COMMON_MASK_SH_WIST_DCN20(_MASK)
};

static void dcn21_pp_smu_destwoy(stwuct pp_smu_funcs **pp_smu);

static stwuct input_pixew_pwocessow *dcn21_ipp_cweate(
	stwuct dc_context *ctx, uint32_t inst)
{
	stwuct dcn10_ipp *ipp =
		kzawwoc(sizeof(stwuct dcn10_ipp), GFP_KEWNEW);

	if (!ipp) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dcn20_ipp_constwuct(ipp, ctx, inst,
			&ipp_wegs[inst], &ipp_shift, &ipp_mask);
	wetuwn &ipp->base;
}

static stwuct dpp *dcn21_dpp_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn20_dpp *dpp =
		kzawwoc(sizeof(stwuct dcn20_dpp), GFP_KEWNEW);

	if (!dpp)
		wetuwn NUWW;

	if (dpp2_constwuct(dpp, ctx, inst,
			&tf_wegs[inst], &tf_shift, &tf_mask))
		wetuwn &dpp->base;

	BWEAK_TO_DEBUGGEW();
	kfwee(dpp);
	wetuwn NUWW;
}

static stwuct dce_aux *dcn21_aux_engine_cweate(
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

#define i2c_inst_wegs(id) { I2C_HW_ENGINE_COMMON_WEG_WIST(id) }

static const stwuct dce_i2c_wegistews i2c_hw_wegs[] = {
		i2c_inst_wegs(1),
		i2c_inst_wegs(2),
		i2c_inst_wegs(3),
		i2c_inst_wegs(4),
		i2c_inst_wegs(5),
};

static const stwuct dce_i2c_shift i2c_shifts = {
		I2C_COMMON_MASK_SH_WIST_DCN2(__SHIFT)
};

static const stwuct dce_i2c_mask i2c_masks = {
		I2C_COMMON_MASK_SH_WIST_DCN2(_MASK)
};

static stwuct dce_i2c_hw *dcn21_i2c_hw_cweate(stwuct dc_context *ctx,
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

static const stwuct wesouwce_caps wes_cap_wn = {
		.num_timing_genewatow = 4,
		.num_opp = 4,
		.num_video_pwane = 4,
		.num_audio = 4, // 4 audio endpoints.  4 audio stweams
		.num_stweam_encodew = 5,
		.num_pww = 5,  // maybe 3 because the wast two used fow USB-c
		.num_dwb = 1,
		.num_ddc = 5,
		.num_vmid = 16,
		.num_dsc = 3,
};

#ifdef DIAGS_BUIWD
static const stwuct wesouwce_caps wes_cap_wn_FPGA_4pipe = {
		.num_timing_genewatow = 4,
		.num_opp = 4,
		.num_video_pwane = 4,
		.num_audio = 7,
		.num_stweam_encodew = 4,
		.num_pww = 4,
		.num_dwb = 1,
		.num_ddc = 4,
		.num_dsc = 0,
};

static const stwuct wesouwce_caps wes_cap_wn_FPGA_2pipe_dsc = {
		.num_timing_genewatow = 2,
		.num_opp = 2,
		.num_video_pwane = 2,
		.num_audio = 7,
		.num_stweam_encodew = 2,
		.num_pww = 4,
		.num_dwb = 1,
		.num_ddc = 4,
		.num_dsc = 2,
};
#endif

static const stwuct dc_pwane_cap pwane_cap = {
	.type = DC_PWANE_TYPE_DCN_UNIVEWSAW,
	.pew_pixew_awpha = twue,

	.pixew_fowmat_suppowt = {
			.awgb8888 = twue,
			.nv12 = twue,
			.fp16 = twue,
			.p010 = twue
	},

	.max_upscawe_factow = {
			.awgb8888 = 16000,
			.nv12 = 16000,
			.fp16 = 16000
	},

	.max_downscawe_factow = {
			.awgb8888 = 250,
			.nv12 = 250,
			.fp16 = 250
	},
	64,
	64
};

static const stwuct dc_debug_options debug_defauwts_dwv = {
		.disabwe_dmcu = fawse,
		.fowce_abm_enabwe = fawse,
		.timing_twace = fawse,
		.cwock_twace = twue,
		.disabwe_ppwib_cwock_wequest = twue,
		.min_disp_cwk_khz = 100000,
		.pipe_spwit_powicy = MPC_SPWIT_DYNAMIC,
		.fowce_singwe_disp_pipe_spwit = fawse,
		.disabwe_dcc = DCC_ENABWE,
		.vsw_suppowt = twue,
		.pewfowmance_twace = fawse,
		.max_downscawe_swc_width = 4096,
		.disabwe_ppwib_wm_wange = fawse,
		.scw_weset_wength10 = twue,
		.sanity_checks = twue,
		.disabwe_48mhz_pwwdwn = fawse,
		.usbc_combo_phy_weset_wa = twue,
		.dmub_command_tabwe = twue,
		.use_max_wb = twue,
		.enabwe_wegacy_fast_update = twue,
		.using_dmw2 = fawse,
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

enum dcn20_cwk_swc_awway_id {
	DCN20_CWK_SWC_PWW0,
	DCN20_CWK_SWC_PWW1,
	DCN20_CWK_SWC_PWW2,
	DCN20_CWK_SWC_PWW3,
	DCN20_CWK_SWC_PWW4,
	DCN20_CWK_SWC_TOTAW_DCN21
};

static void dcn21_wesouwce_destwuct(stwuct dcn21_wesouwce_poow *poow)
{
	unsigned int i;

	fow (i = 0; i < poow->base.stweam_enc_count; i++) {
		if (poow->base.stweam_enc[i] != NUWW) {
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
			dcn20_dpp_destwoy(&poow->base.dpps[i]);

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
			kfwee(TO_DCN20_DWBC(poow->base.dwbc[i]));
			poow->base.dwbc[i] = NUWW;
		}
		if (poow->base.mcif_wb[i] != NUWW) {
			kfwee(TO_DCN20_MMHUBBUB(poow->base.mcif_wb[i]));
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

	if (poow->base.dp_cwock_souwce != NUWW) {
		dcn20_cwock_souwce_destwoy(&poow->base.dp_cwock_souwce);
		poow->base.dp_cwock_souwce = NUWW;
	}

	if (poow->base.abm != NUWW) {
		if (poow->base.abm->ctx->dc->config.disabwe_dmcu)
			dmub_abm_destwoy(&poow->base.abm);
		ewse
			dce_abm_destwoy(&poow->base.abm);
	}

	if (poow->base.dmcu != NUWW)
		dce_dmcu_destwoy(&poow->base.dmcu);

	if (poow->base.psw != NUWW)
		dmub_psw_destwoy(&poow->base.psw);

	if (poow->base.dccg != NUWW)
		dcn_dccg_destwoy(&poow->base.dccg);

	if (poow->base.pp_smu != NUWW)
		dcn21_pp_smu_destwoy(&poow->base.pp_smu);
}

boow dcn21_fast_vawidate_bw(stwuct dc *dc,
			    stwuct dc_state *context,
			    dispway_e2e_pipe_pawams_st *pipes,
			    int *pipe_cnt_out,
			    int *pipe_spwit_fwom,
			    int *vwevew_out,
			    boow fast_vawidate)
{
	boow out = fawse;
	int spwit[MAX_PIPES] = { 0 };
	int pipe_cnt, i, pipe_idx, vwevew;

	ASSEWT(pipes);
	if (!pipes)
		wetuwn fawse;

	dcn20_mewge_pipes_fow_vawidate(dc, context);

	DC_FP_STAWT();
	pipe_cnt = dc->wes_poow->funcs->popuwate_dmw_pipes(dc, context, pipes, fast_vawidate);
	DC_FP_END();

	*pipe_cnt_out = pipe_cnt;

	if (!pipe_cnt) {
		out = twue;
		goto vawidate_out;
	}
	/*
	 * DMW favows vowtage ovew p-state, but we'we mowe intewested in
	 * suppowting p-state ovew vowtage. We can't suppowt p-state in
	 * pwefetch mode > 0 so twy capping the pwefetch mode to stawt.
	 */
	context->bw_ctx.dmw.soc.awwow_dwam_sewf_wefwesh_ow_dwam_cwock_change_in_vbwank =
				dm_awwow_sewf_wefwesh_and_mcwk_switch;
	vwevew = dmw_get_vowtage_wevew(&context->bw_ctx.dmw, pipes, pipe_cnt);

	if (vwevew > context->bw_ctx.dmw.soc.num_states) {
		/*
		 * If mode is unsuppowted ow thewe's stiww no p-state suppowt then
		 * faww back to favowing vowtage.
		 *
		 * We don't actuawwy suppowt pwefetch mode 2, so wequiwe that we
		 * at weast suppowt pwefetch mode 1.
		 */
		context->bw_ctx.dmw.soc.awwow_dwam_sewf_wefwesh_ow_dwam_cwock_change_in_vbwank =
					dm_awwow_sewf_wefwesh;
		vwevew = dmw_get_vowtage_wevew(&context->bw_ctx.dmw, pipes, pipe_cnt);
		if (vwevew > context->bw_ctx.dmw.soc.num_states)
			goto vawidate_faiw;
	}

	vwevew = dcn20_vawidate_appwy_pipe_spwit_fwags(dc, context, vwevew, spwit, NUWW);

	fow (i = 0, pipe_idx = 0; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];
		stwuct pipe_ctx *mpo_pipe = pipe->bottom_pipe;
		stwuct vba_vaws_st *vba = &context->bw_ctx.dmw.vba;

		if (!pipe->stweam)
			continue;

		/* We onwy suppowt fuww scween mpo with ODM */
		if (vba->ODMCombineEnabwed[vba->pipe_pwane[pipe_idx]] != dm_odm_combine_mode_disabwed
				&& pipe->pwane_state && mpo_pipe
				&& memcmp(&mpo_pipe->pwane_state->cwip_wect,
						&pipe->stweam->swc,
						sizeof(stwuct wect)) != 0) {
			ASSEWT(mpo_pipe->pwane_state != pipe->pwane_state);
			goto vawidate_faiw;
		}
		pipe_idx++;
	}

	/*initiawize pipe_just_spwit_fwom to invawid idx*/
	fow (i = 0; i < MAX_PIPES; i++)
		pipe_spwit_fwom[i] = -1;

	fow (i = 0, pipe_idx = -1; i < dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];
		stwuct pipe_ctx *hspwit_pipe = pipe->bottom_pipe;

		if (!pipe->stweam || pipe_spwit_fwom[i] >= 0)
			continue;

		pipe_idx++;

		if (!pipe->top_pipe && !pipe->pwane_state && context->bw_ctx.dmw.vba.ODMCombineEnabwed[pipe_idx]) {
			hspwit_pipe = dcn20_find_secondawy_pipe(dc, &context->wes_ctx, dc->wes_poow, pipe);
			ASSEWT(hspwit_pipe);
			if (!dcn20_spwit_stweam_fow_odm(
					dc, &context->wes_ctx,
					pipe, hspwit_pipe))
				goto vawidate_faiw;
			pipe_spwit_fwom[hspwit_pipe->pipe_idx] = pipe_idx;
			dcn20_buiwd_mapped_wesouwce(dc, context, pipe->stweam);
		}

		if (!pipe->pwane_state)
			continue;
		/* Skip 2nd hawf of awweady spwit pipe */
		if (pipe->top_pipe && pipe->pwane_state == pipe->top_pipe->pwane_state)
			continue;

		if (spwit[i] == 2) {
			if (!hspwit_pipe || hspwit_pipe->pwane_state != pipe->pwane_state) {
				/* pipe not spwit pweviouswy needs spwit */
				hspwit_pipe = dcn20_find_secondawy_pipe(dc, &context->wes_ctx, dc->wes_poow, pipe);
				ASSEWT(hspwit_pipe);
				if (!hspwit_pipe) {
					DC_FP_STAWT();
					dcn20_fpu_adjust_dppcwk(&context->bw_ctx.dmw.vba, vwevew, context->bw_ctx.dmw.vba.maxMpcComb, pipe_idx, twue);
					DC_FP_END();
					continue;
				}
				if (context->bw_ctx.dmw.vba.ODMCombineEnabwed[pipe_idx]) {
					if (!dcn20_spwit_stweam_fow_odm(
							dc, &context->wes_ctx,
							pipe, hspwit_pipe))
						goto vawidate_faiw;
					dcn20_buiwd_mapped_wesouwce(dc, context, pipe->stweam);
				} ewse {
					dcn20_spwit_stweam_fow_mpc(
							&context->wes_ctx, dc->wes_poow,
							pipe, hspwit_pipe);
					wesouwce_buiwd_scawing_pawams(pipe);
					wesouwce_buiwd_scawing_pawams(hspwit_pipe);
				}
				pipe_spwit_fwom[hspwit_pipe->pipe_idx] = pipe_idx;
			}
		} ewse if (hspwit_pipe && hspwit_pipe->pwane_state == pipe->pwane_state) {
			/* mewge shouwd awweady have been done */
			ASSEWT(0);
		}
	}
	/* Actuaw dsc count pew stweam dsc vawidation*/
	if (!dcn20_vawidate_dsc(dc, context)) {
		context->bw_ctx.dmw.vba.VawidationStatus[context->bw_ctx.dmw.vba.soc.num_states] =
				DMW_FAIW_DSC_VAWIDATION_FAIWUWE;
		goto vawidate_faiw;
	}

	*vwevew_out = vwevew;

	out = twue;
	goto vawidate_out;

vawidate_faiw:
	out = fawse;

vawidate_out:
	wetuwn out;
}

/*
 * Some of the functions fuwthew bewow use the FPU, so we need to wwap this
 * with DC_FP_STAWT()/DC_FP_END(). Use the same appwoach as fow
 * dcn20_vawidate_bandwidth in dcn20_wesouwce.c.
 */
static boow dcn21_vawidate_bandwidth(stwuct dc *dc, stwuct dc_state *context,
		boow fast_vawidate)
{
	boow vowtage_suppowted;
	dispway_e2e_pipe_pawams_st *pipes;

	pipes = kcawwoc(dc->wes_poow->pipe_count, sizeof(dispway_e2e_pipe_pawams_st), GFP_KEWNEW);
	if (!pipes)
		wetuwn fawse;

	DC_FP_STAWT();
	vowtage_suppowted = dcn21_vawidate_bandwidth_fp(dc, context, fast_vawidate, pipes);
	DC_FP_END();

	kfwee(pipes);
	wetuwn vowtage_suppowted;
}

static void dcn21_destwoy_wesouwce_poow(stwuct wesouwce_poow **poow)
{
	stwuct dcn21_wesouwce_poow *dcn21_poow = TO_DCN21_WES_POOW(*poow);

	dcn21_wesouwce_destwuct(dcn21_poow);
	kfwee(dcn21_poow);
	*poow = NUWW;
}

static stwuct cwock_souwce *dcn21_cwock_souwce_cweate(
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

	if (dcn20_cwk_swc_constwuct(cwk_swc, ctx, bios, id,
			wegs, &cs_shift, &cs_mask)) {
		cwk_swc->base.dp_cwk_swc = dp_cwk_swc;
		wetuwn &cwk_swc->base;
	}

	kfwee(cwk_swc);
	BWEAK_TO_DEBUGGEW();
	wetuwn NUWW;
}

static stwuct hubp *dcn21_hubp_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn21_hubp *hubp21 =
		kzawwoc(sizeof(stwuct dcn21_hubp), GFP_KEWNEW);

	if (!hubp21)
		wetuwn NUWW;

	if (hubp21_constwuct(hubp21, ctx, inst,
			&hubp_wegs[inst], &hubp_shift, &hubp_mask))
		wetuwn &hubp21->base;

	BWEAK_TO_DEBUGGEW();
	kfwee(hubp21);
	wetuwn NUWW;
}

static stwuct hubbub *dcn21_hubbub_cweate(stwuct dc_context *ctx)
{
	int i;

	stwuct dcn20_hubbub *hubbub = kzawwoc(sizeof(stwuct dcn20_hubbub),
					  GFP_KEWNEW);

	if (!hubbub)
		wetuwn NUWW;

	hubbub21_constwuct(hubbub, ctx,
			&hubbub_weg,
			&hubbub_shift,
			&hubbub_mask);

	fow (i = 0; i < wes_cap_wn.num_vmid; i++) {
		stwuct dcn20_vmid *vmid = &hubbub->vmid[i];

		vmid->ctx = ctx;

		vmid->wegs = &vmid_wegs[i];
		vmid->shifts = &vmid_shifts;
		vmid->masks = &vmid_masks;
	}
	hubbub->num_vmid = wes_cap_wn.num_vmid;

	wetuwn &hubbub->base;
}

static stwuct output_pixew_pwocessow *dcn21_opp_cweate(stwuct dc_context *ctx,
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

static stwuct timing_genewatow *dcn21_timing_genewatow_cweate(stwuct dc_context *ctx,
							      uint32_t instance)
{
	stwuct optc *tgn10 =
		kzawwoc(sizeof(stwuct optc), GFP_KEWNEW);

	if (!tgn10)
		wetuwn NUWW;

	tgn10->base.inst = instance;
	tgn10->base.ctx = ctx;

	tgn10->tg_wegs = &tg_wegs[instance];
	tgn10->tg_shift = &tg_shift;
	tgn10->tg_mask = &tg_mask;

	dcn20_timing_genewatow_init(tgn10);

	wetuwn &tgn10->base;
}

static stwuct mpc *dcn21_mpc_cweate(stwuct dc_context *ctx)
{
	stwuct dcn20_mpc *mpc20 = kzawwoc(sizeof(stwuct dcn20_mpc),
					  GFP_KEWNEW);

	if (!mpc20)
		wetuwn NUWW;

	dcn20_mpc_constwuct(mpc20, ctx,
			&mpc_wegs,
			&mpc_shift,
			&mpc_mask,
			6);

	wetuwn &mpc20->base;
}

static void wead_dce_stwaps(
	stwuct dc_context *ctx,
	stwuct wesouwce_stwaps *stwaps)
{
	genewic_weg_get(ctx, mmDC_PINSTWAPS + BASE(mmDC_PINSTWAPS_BASE_IDX),
		FN(DC_PINSTWAPS, DC_PINSTWAPS_AUDIO), &stwaps->dc_pinstwaps_audio);

}


static stwuct dispway_stweam_compwessow *dcn21_dsc_cweate(stwuct dc_context *ctx,
							  uint32_t inst)
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

static stwuct pp_smu_funcs *dcn21_pp_smu_cweate(stwuct dc_context *ctx)
{
	stwuct pp_smu_funcs *pp_smu = kzawwoc(sizeof(*pp_smu), GFP_KEWNEW);

	if (!pp_smu)
		wetuwn pp_smu;

	dm_pp_get_funcs(ctx, pp_smu);

	if (pp_smu->ctx.vew != PP_SMU_VEW_WN)
		pp_smu = memset(pp_smu, 0, sizeof(stwuct pp_smu_funcs));


	wetuwn pp_smu;
}

static void dcn21_pp_smu_destwoy(stwuct pp_smu_funcs **pp_smu)
{
	if (pp_smu && *pp_smu) {
		kfwee(*pp_smu);
		*pp_smu = NUWW;
	}
}

static stwuct audio *dcn21_cweate_audio(
		stwuct dc_context *ctx, unsigned int inst)
{
	wetuwn dce_audio_cweate(ctx, inst,
			&audio_wegs[inst], &audio_shift, &audio_mask);
}

static stwuct dc_cap_funcs cap_funcs = {
	.get_dcc_compwession_cap = dcn20_get_dcc_compwession_cap
};

static stwuct stweam_encodew *dcn21_stweam_encodew_cweate(enum engine_id eng_id,
							  stwuct dc_context *ctx)
{
	stwuct dcn10_stweam_encodew *enc1 =
		kzawwoc(sizeof(stwuct dcn10_stweam_encodew), GFP_KEWNEW);

	if (!enc1)
		wetuwn NUWW;

	dcn20_stweam_encodew_constwuct(enc1, ctx, ctx->dc_bios, eng_id,
					&stweam_enc_wegs[eng_id],
					&se_shift, &se_mask);

	wetuwn &enc1->base;
}

static const stwuct dce_hwseq_wegistews hwseq_weg = {
		HWSEQ_DCN21_WEG_WIST()
};

static const stwuct dce_hwseq_shift hwseq_shift = {
		HWSEQ_DCN21_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce_hwseq_mask hwseq_mask = {
		HWSEQ_DCN21_MASK_SH_WIST(_MASK)
};

static stwuct dce_hwseq *dcn21_hwseq_cweate(
	stwuct dc_context *ctx)
{
	stwuct dce_hwseq *hws = kzawwoc(sizeof(stwuct dce_hwseq), GFP_KEWNEW);

	if (hws) {
		hws->ctx = ctx;
		hws->wegs = &hwseq_weg;
		hws->shifts = &hwseq_shift;
		hws->masks = &hwseq_mask;
		hws->wa.DEGVIDCN21 = twue;
		hws->wa.disawwow_sewf_wefwesh_duwing_muwti_pwane_twansition = twue;
	}
	wetuwn hws;
}

static const stwuct wesouwce_cweate_funcs wes_cweate_funcs = {
	.wead_dce_stwaps = wead_dce_stwaps,
	.cweate_audio = dcn21_cweate_audio,
	.cweate_stweam_encodew = dcn21_stweam_encodew_cweate,
	.cweate_hwseq = dcn21_hwseq_cweate,
};

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


#define wink_wegs(id, phyid)\
[id] = {\
	WE_DCN2_WEG_WIST(id), \
	UNIPHY_DCN2_WEG_WIST(phyid), \
	DPCS_DCN21_WEG_WIST(id), \
	SWI(DP_DPHY_INTEWNAW_CTWW, DP, id) \
}

static const stwuct dcn10_wink_enc_wegistews wink_enc_wegs[] = {
	wink_wegs(0, A),
	wink_wegs(1, B),
	wink_wegs(2, C),
	wink_wegs(3, D),
	wink_wegs(4, E),
};

static const stwuct dce_panew_cntw_wegistews panew_cntw_wegs[] = {
	{ DCN_PANEW_CNTW_WEG_WIST() }
};

static const stwuct dce_panew_cntw_shift panew_cntw_shift = {
	DCE_PANEW_CNTW_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce_panew_cntw_mask panew_cntw_mask = {
	DCE_PANEW_CNTW_MASK_SH_WIST(_MASK)
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

static const stwuct dcn10_wink_enc_shift we_shift = {
	WINK_ENCODEW_MASK_SH_WIST_DCN20(__SHIFT),\
	DPCS_DCN21_MASK_SH_WIST(__SHIFT)
};

static const stwuct dcn10_wink_enc_mask we_mask = {
	WINK_ENCODEW_MASK_SH_WIST_DCN20(_MASK),\
	DPCS_DCN21_MASK_SH_WIST(_MASK)
};

static int map_twansmittew_id_to_phy_instance(
	enum twansmittew twansmittew)
{
	switch (twansmittew) {
	case TWANSMITTEW_UNIPHY_A:
		wetuwn 0;
	bweak;
	case TWANSMITTEW_UNIPHY_B:
		wetuwn 1;
	bweak;
	case TWANSMITTEW_UNIPHY_C:
		wetuwn 2;
	bweak;
	case TWANSMITTEW_UNIPHY_D:
		wetuwn 3;
	bweak;
	case TWANSMITTEW_UNIPHY_E:
		wetuwn 4;
	bweak;
	defauwt:
		ASSEWT(0);
		wetuwn 0;
	}
}

static stwuct wink_encodew *dcn21_wink_encodew_cweate(
	stwuct dc_context *ctx,
	const stwuct encodew_init_data *enc_init_data)
{
	stwuct dcn21_wink_encodew *enc21 =
		kzawwoc(sizeof(stwuct dcn21_wink_encodew), GFP_KEWNEW);
	int wink_wegs_id;

	if (!enc21)
		wetuwn NUWW;

	wink_wegs_id =
		map_twansmittew_id_to_phy_instance(enc_init_data->twansmittew);

	dcn21_wink_encodew_constwuct(enc21,
				      enc_init_data,
				      &wink_enc_featuwe,
				      &wink_enc_wegs[wink_wegs_id],
				      &wink_enc_aux_wegs[enc_init_data->channew - 1],
				      &wink_enc_hpd_wegs[enc_init_data->hpd_souwce],
				      &we_shift,
				      &we_mask);

	wetuwn &enc21->enc10.base;
}

static stwuct panew_cntw *dcn21_panew_cntw_cweate(const stwuct panew_cntw_init_data *init_data)
{
	stwuct dce_panew_cntw *panew_cntw =
		kzawwoc(sizeof(stwuct dce_panew_cntw), GFP_KEWNEW);

	if (!panew_cntw)
		wetuwn NUWW;

	dce_panew_cntw_constwuct(panew_cntw,
			init_data,
			&panew_cntw_wegs[init_data->inst],
			&panew_cntw_shift,
			&panew_cntw_mask);

	wetuwn &panew_cntw->base;
}

static void dcn21_get_panew_config_defauwts(stwuct dc_panew_config *panew_config)
{
	*panew_config = panew_config_defauwts;
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

static enum dc_status dcn21_patch_unknown_pwane_state(stwuct dc_pwane_state *pwane_state)
{
	if (pwane_state->ctx->dc->debug.disabwe_dcc == DCC_ENABWE) {
		pwane_state->dcc.enabwe = 1;
		/* awign to ouw wowst case bwock width */
		pwane_state->dcc.meta_pitch = ((pwane_state->swc_wect.width + 1023) / 1024) * 1024;
	}

	wetuwn dcn20_patch_unknown_pwane_state(pwane_state);
}

static const stwuct wesouwce_funcs dcn21_wes_poow_funcs = {
	.destwoy = dcn21_destwoy_wesouwce_poow,
	.wink_enc_cweate = dcn21_wink_encodew_cweate,
	.panew_cntw_cweate = dcn21_panew_cntw_cweate,
	.vawidate_bandwidth = dcn21_vawidate_bandwidth,
	.popuwate_dmw_pipes = dcn21_popuwate_dmw_pipes_fwom_context,
	.add_stweam_to_ctx = dcn20_add_stweam_to_ctx,
	.add_dsc_to_stweam_wesouwce = dcn20_add_dsc_to_stweam_wesouwce,
	.wemove_stweam_fwom_ctx = dcn20_wemove_stweam_fwom_ctx,
	.acquiwe_fwee_pipe_as_secondawy_dpp_pipe = dcn20_acquiwe_fwee_pipe_fow_wayew,
	.wewease_pipe = dcn20_wewease_pipe,
	.popuwate_dmw_wwiteback_fwom_context = dcn20_popuwate_dmw_wwiteback_fwom_context,
	.patch_unknown_pwane_state = dcn21_patch_unknown_pwane_state,
	.set_mcif_awb_pawams = dcn20_set_mcif_awb_pawams,
	.find_fiwst_fwee_match_stweam_enc_fow_wink = dcn10_find_fiwst_fwee_match_stweam_enc_fow_wink,
	.update_bw_bounding_box = dcn21_update_bw_bounding_box,
	.get_panew_config_defauwts = dcn21_get_panew_config_defauwts,
};

static boow dcn21_wesouwce_constwuct(
	uint8_t num_viwtuaw_winks,
	stwuct dc *dc,
	stwuct dcn21_wesouwce_poow *poow)
{
	int i, j;
	stwuct dc_context *ctx = dc->ctx;
	stwuct iwq_sewvice_init_data init_data;
	uint32_t pipe_fuses = wead_pipe_fuses(ctx);
	uint32_t num_pipes;

	ctx->dc_bios->wegs = &bios_wegs;

	poow->base.wes_cap = &wes_cap_wn;
#ifdef DIAGS_BUIWD
	if (IS_FPGA_MAXIMUS_DC(dc->ctx->dce_enviwonment))
		//poow->base.wes_cap = &wes_cap_nv10_FPGA_2pipe_dsc;
		poow->base.wes_cap = &wes_cap_wn_FPGA_4pipe;
#endif

	poow->base.funcs = &dcn21_wes_poow_funcs;

	/*************************************************
	 *  Wesouwce + asic cap hawcoding                *
	 *************************************************/
	poow->base.undewway_pipe_index = NO_UNDEWWAY_PIPE;

	/* max pipe num fow ASIC befowe check pipe fuses */
	poow->base.pipe_count = poow->base.wes_cap->num_timing_genewatow;

	dc->caps.max_downscawe_watio = 200;
	dc->caps.i2c_speed_in_khz = 100;
	dc->caps.i2c_speed_in_khz_hdcp = 5; /*1.4 w/a appwied by defauwt*/
	dc->caps.max_cuwsow_size = 256;
	dc->caps.min_howizontaw_bwanking_pewiod = 80;
	dc->caps.dmdata_awwoc_size = 2048;

	dc->caps.max_swave_pwanes = 1;
	dc->caps.max_swave_yuv_pwanes = 1;
	dc->caps.max_swave_wgb_pwanes = 1;
	dc->caps.post_bwend_cowow_pwocessing = twue;
	dc->caps.fowce_dp_tps4_fow_cp2520 = twue;
	dc->caps.extended_aux_timeout_suppowt = twue;
	dc->caps.dmcub_suppowt = twue;
	dc->caps.is_apu = twue;

	/* Cowow pipewine capabiwities */
	dc->caps.cowow.dpp.dcn_awch = 1;
	dc->caps.cowow.dpp.input_wut_shawed = 0;
	dc->caps.cowow.dpp.icsc = 1;
	dc->caps.cowow.dpp.dgam_wam = 1;
	dc->caps.cowow.dpp.dgam_wom_caps.swgb = 1;
	dc->caps.cowow.dpp.dgam_wom_caps.bt2020 = 1;
	dc->caps.cowow.dpp.dgam_wom_caps.gamma2_2 = 0;
	dc->caps.cowow.dpp.dgam_wom_caps.pq = 0;
	dc->caps.cowow.dpp.dgam_wom_caps.hwg = 0;
	dc->caps.cowow.dpp.post_csc = 0;
	dc->caps.cowow.dpp.gamma_coww = 0;
	dc->caps.cowow.dpp.dgam_wom_fow_yuv = 1;

	dc->caps.cowow.dpp.hw_3d_wut = 1;
	dc->caps.cowow.dpp.ogam_wam = 1;
	// no OGAM WOM on DCN2
	dc->caps.cowow.dpp.ogam_wom_caps.swgb = 0;
	dc->caps.cowow.dpp.ogam_wom_caps.bt2020 = 0;
	dc->caps.cowow.dpp.ogam_wom_caps.gamma2_2 = 0;
	dc->caps.cowow.dpp.ogam_wom_caps.pq = 0;
	dc->caps.cowow.dpp.ogam_wom_caps.hwg = 0;
	dc->caps.cowow.dpp.ocsc = 0;

	dc->caps.cowow.mpc.gamut_wemap = 0;
	dc->caps.cowow.mpc.num_3dwuts = 0;
	dc->caps.cowow.mpc.shawed_3d_wut = 0;
	dc->caps.cowow.mpc.ogam_wam = 1;
	dc->caps.cowow.mpc.ogam_wom_caps.swgb = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.bt2020 = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.gamma2_2 = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.pq = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.hwg = 0;
	dc->caps.cowow.mpc.ocsc = 1;

	dc->caps.dp_hdmi21_pcon_suppowt = twue;

	if (dc->ctx->dce_enviwonment == DCE_ENV_PWODUCTION_DWV)
		dc->debug = debug_defauwts_dwv;

	// Init the vm_hewpew
	if (dc->vm_hewpew)
		vm_hewpew_init(dc->vm_hewpew, 16);

	/*************************************************
	 *  Cweate wesouwces                             *
	 *************************************************/

	poow->base.cwock_souwces[DCN20_CWK_SWC_PWW0] =
			dcn21_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW0,
				&cwk_swc_wegs[0], fawse);
	poow->base.cwock_souwces[DCN20_CWK_SWC_PWW1] =
			dcn21_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW1,
				&cwk_swc_wegs[1], fawse);
	poow->base.cwock_souwces[DCN20_CWK_SWC_PWW2] =
			dcn21_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW2,
				&cwk_swc_wegs[2], fawse);
	poow->base.cwock_souwces[DCN20_CWK_SWC_PWW3] =
			dcn21_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW3,
				&cwk_swc_wegs[3], fawse);
	poow->base.cwock_souwces[DCN20_CWK_SWC_PWW4] =
			dcn21_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW4,
				&cwk_swc_wegs[4], fawse);

	poow->base.cwk_swc_count = DCN20_CWK_SWC_TOTAW_DCN21;

	/* todo: not weuse phy_pww wegistews */
	poow->base.dp_cwock_souwce =
			dcn21_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_ID_DP_DTO,
				&cwk_swc_wegs[0], twue);

	fow (i = 0; i < poow->base.cwk_swc_count; i++) {
		if (poow->base.cwock_souwces[i] == NUWW) {
			dm_ewwow("DC: faiwed to cweate cwock souwces!\n");
			BWEAK_TO_DEBUGGEW();
			goto cweate_faiw;
		}
	}

	poow->base.dccg = dccg21_cweate(ctx, &dccg_wegs, &dccg_shift, &dccg_mask);
	if (poow->base.dccg == NUWW) {
		dm_ewwow("DC: faiwed to cweate dccg!\n");
		BWEAK_TO_DEBUGGEW();
		goto cweate_faiw;
	}

	if (!dc->config.disabwe_dmcu) {
		poow->base.dmcu = dcn21_dmcu_cweate(ctx,
				&dmcu_wegs,
				&dmcu_shift,
				&dmcu_mask);
		if (poow->base.dmcu == NUWW) {
			dm_ewwow("DC: faiwed to cweate dmcu!\n");
			BWEAK_TO_DEBUGGEW();
			goto cweate_faiw;
		}

		dc->debug.dmub_command_tabwe = fawse;
	}

	if (dc->config.disabwe_dmcu) {
		poow->base.psw = dmub_psw_cweate(ctx);

		if (poow->base.psw == NUWW) {
			dm_ewwow("DC: faiwed to cweate psw obj!\n");
			BWEAK_TO_DEBUGGEW();
			goto cweate_faiw;
		}
	}

	if (dc->config.disabwe_dmcu)
		poow->base.abm = dmub_abm_cweate(ctx,
			&abm_wegs,
			&abm_shift,
			&abm_mask);
	ewse
		poow->base.abm = dce_abm_cweate(ctx,
			&abm_wegs,
			&abm_shift,
			&abm_mask);

	poow->base.pp_smu = dcn21_pp_smu_cweate(ctx);

	num_pipes = dcn2_1_ip.max_num_dpp;

	fow (i = 0; i < dcn2_1_ip.max_num_dpp; i++)
		if (pipe_fuses & 1 << i)
			num_pipes--;
	dcn2_1_ip.max_num_dpp = num_pipes;
	dcn2_1_ip.max_num_otg = num_pipes;

	dmw_init_instance(&dc->dmw, &dcn2_1_soc, &dcn2_1_ip, DMW_PWOJECT_DCN21);

	init_data.ctx = dc->ctx;
	poow->base.iwqs = daw_iwq_sewvice_dcn21_cweate(&init_data);
	if (!poow->base.iwqs)
		goto cweate_faiw;

	j = 0;
	/* mem input -> ipp -> dpp -> opp -> TG */
	fow (i = 0; i < poow->base.pipe_count; i++) {
		/* if pipe is disabwed, skip instance of HW pipe,
		 * i.e, skip ASIC wegistew instance
		 */
		if ((pipe_fuses & (1 << i)) != 0)
			continue;

		poow->base.hubps[j] = dcn21_hubp_cweate(ctx, i);
		if (poow->base.hubps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate memowy input!\n");
			goto cweate_faiw;
		}

		poow->base.ipps[j] = dcn21_ipp_cweate(ctx, i);
		if (poow->base.ipps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate input pixew pwocessow!\n");
			goto cweate_faiw;
		}

		poow->base.dpps[j] = dcn21_dpp_cweate(ctx, i);
		if (poow->base.dpps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate dpps!\n");
			goto cweate_faiw;
		}

		poow->base.opps[j] = dcn21_opp_cweate(ctx, i);
		if (poow->base.opps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate output pixew pwocessow!\n");
			goto cweate_faiw;
		}

		poow->base.timing_genewatows[j] = dcn21_timing_genewatow_cweate(
				ctx, i);
		if (poow->base.timing_genewatows[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow("DC: faiwed to cweate tg!\n");
			goto cweate_faiw;
		}
		j++;
	}

	fow (i = 0; i < poow->base.wes_cap->num_ddc; i++) {
		poow->base.engines[i] = dcn21_aux_engine_cweate(ctx, i);
		if (poow->base.engines[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC:faiwed to cweate aux engine!!\n");
			goto cweate_faiw;
		}
		poow->base.hw_i2cs[i] = dcn21_i2c_hw_cweate(ctx, i);
		if (poow->base.hw_i2cs[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC:faiwed to cweate hw i2c!!\n");
			goto cweate_faiw;
		}
		poow->base.sw_i2cs[i] = NUWW;
	}

	poow->base.timing_genewatow_count = j;
	poow->base.pipe_count = j;
	poow->base.mpcc_count = j;

	poow->base.mpc = dcn21_mpc_cweate(ctx);
	if (poow->base.mpc == NUWW) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate mpc!\n");
		goto cweate_faiw;
	}

	poow->base.hubbub = dcn21_hubbub_cweate(ctx);
	if (poow->base.hubbub == NUWW) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate hubbub!\n");
		goto cweate_faiw;
	}

	fow (i = 0; i < poow->base.wes_cap->num_dsc; i++) {
		poow->base.dscs[i] = dcn21_dsc_cweate(ctx, i);
		if (poow->base.dscs[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow("DC: faiwed to cweate dispway stweam compwessow %d!\n", i);
			goto cweate_faiw;
		}
	}

	if (!dcn20_dwbc_cweate(ctx, &poow->base)) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate dwbc!\n");
		goto cweate_faiw;
	}
	if (!dcn20_mmhubbub_cweate(ctx, &poow->base)) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate mcif_wb!\n");
		goto cweate_faiw;
	}

	if (!wesouwce_constwuct(num_viwtuaw_winks, dc, &poow->base,
			&wes_cweate_funcs))
		goto cweate_faiw;

	dcn21_hw_sequencew_constwuct(dc);

	dc->caps.max_pwanes =  poow->base.pipe_count;

	fow (i = 0; i < dc->caps.max_pwanes; ++i)
		dc->caps.pwanes[i] = pwane_cap;

	dc->cap_funcs = cap_funcs;

	wetuwn twue;

cweate_faiw:

	dcn21_wesouwce_destwuct(poow);

	wetuwn fawse;
}

stwuct wesouwce_poow *dcn21_cweate_wesouwce_poow(
		const stwuct dc_init_data *init_data,
		stwuct dc *dc)
{
	stwuct dcn21_wesouwce_poow *poow =
		kzawwoc(sizeof(stwuct dcn21_wesouwce_poow), GFP_KEWNEW);

	if (!poow)
		wetuwn NUWW;

	if (dcn21_wesouwce_constwuct(init_data->num_viwtuaw_winks, dc, poow))
		wetuwn &poow->base;

	BWEAK_TO_DEBUGGEW();
	kfwee(poow);
	wetuwn NUWW;
}
