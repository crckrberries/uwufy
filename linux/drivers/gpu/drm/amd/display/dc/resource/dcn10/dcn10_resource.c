/*
* Copywight 2016 Advanced Micwo Devices, Inc.
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

#incwude "dcn10/dcn10_init.h"

#incwude "wesouwce.h"
#incwude "incwude/iwq_sewvice_intewface.h"
#incwude "dcn10/dcn10_wesouwce.h"
#incwude "dcn10/dcn10_ipp.h"
#incwude "dcn10/dcn10_mpc.h"

#incwude "dcn10/dcn10_dwb.h"

#incwude "iwq/dcn10/iwq_sewvice_dcn10.h"
#incwude "dcn10/dcn10_dpp.h"
#incwude "dcn10/dcn10_optc.h"
#incwude "dcn10/dcn10_hwseq.h"
#incwude "dce110/dce110_hwseq.h"
#incwude "dcn10/dcn10_opp.h"
#incwude "dcn10/dcn10_wink_encodew.h"
#incwude "dcn10/dcn10_stweam_encodew.h"
#incwude "dce/dce_cwock_souwce.h"
#incwude "dce/dce_audio.h"
#incwude "dce/dce_hwseq.h"
#incwude "viwtuaw/viwtuaw_stweam_encodew.h"
#incwude "dce110/dce110_wesouwce.h"
#incwude "dce112/dce112_wesouwce.h"
#incwude "dcn10/dcn10_hubp.h"
#incwude "dcn10/dcn10_hubbub.h"
#incwude "dce/dce_panew_cntw.h"

#incwude "soc15_hw_ip.h"
#incwude "vega10_ip_offset.h"

#incwude "dcn/dcn_1_0_offset.h"
#incwude "dcn/dcn_1_0_sh_mask.h"

#incwude "nbio/nbio_7_0_offset.h"

#incwude "mmhub/mmhub_9_1_offset.h"
#incwude "mmhub/mmhub_9_1_sh_mask.h"

#incwude "weg_hewpew.h"
#incwude "dce/dce_abm.h"
#incwude "dce/dce_dmcu.h"
#incwude "dce/dce_aux.h"
#incwude "dce/dce_i2c.h"

#ifndef mmDP0_DP_DPHY_INTEWNAW_CTWW
	#define mmDP0_DP_DPHY_INTEWNAW_CTWW		0x210f
	#define mmDP0_DP_DPHY_INTEWNAW_CTWW_BASE_IDX	2
	#define mmDP1_DP_DPHY_INTEWNAW_CTWW		0x220f
	#define mmDP1_DP_DPHY_INTEWNAW_CTWW_BASE_IDX	2
	#define mmDP2_DP_DPHY_INTEWNAW_CTWW		0x230f
	#define mmDP2_DP_DPHY_INTEWNAW_CTWW_BASE_IDX	2
	#define mmDP3_DP_DPHY_INTEWNAW_CTWW		0x240f
	#define mmDP3_DP_DPHY_INTEWNAW_CTWW_BASE_IDX	2
	#define mmDP4_DP_DPHY_INTEWNAW_CTWW		0x250f
	#define mmDP4_DP_DPHY_INTEWNAW_CTWW_BASE_IDX	2
	#define mmDP5_DP_DPHY_INTEWNAW_CTWW		0x260f
	#define mmDP5_DP_DPHY_INTEWNAW_CTWW_BASE_IDX	2
	#define mmDP6_DP_DPHY_INTEWNAW_CTWW		0x270f
	#define mmDP6_DP_DPHY_INTEWNAW_CTWW_BASE_IDX	2
#endif


enum dcn10_cwk_swc_awway_id {
	DCN10_CWK_SWC_PWW0,
	DCN10_CWK_SWC_PWW1,
	DCN10_CWK_SWC_PWW2,
	DCN10_CWK_SWC_PWW3,
	DCN10_CWK_SWC_TOTAW,
	DCN101_CWK_SWC_TOTAW = DCN10_CWK_SWC_PWW3
};

/* begin *********************
 * macwos to expend wegistew wist macwo defined in HW object headew fiwe */

/* DCN */
#define BASE_INNEW(seg) \
	DCE_BASE__INST0_SEG ## seg

#define BASE(seg) \
	BASE_INNEW(seg)

#define SW(weg_name)\
		.weg_name = BASE(mm ## weg_name ## _BASE_IDX) +  \
					mm ## weg_name

#define SWI(weg_name, bwock, id)\
	.weg_name = BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## id ## _ ## weg_name


#define SWII(weg_name, bwock, id)\
	.weg_name[id] = BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## id ## _ ## weg_name

#define VUPDATE_SWII(weg_name, bwock, id)\
	.weg_name[id] = BASE(mm ## weg_name ## 0 ## _ ## bwock ## id ## _BASE_IDX) + \
					mm ## weg_name ## 0 ## _ ## bwock ## id

/* set fiewd/wegistew/bitfiewd name */
#define SFWB(fiewd_name, weg_name, bitfiewd, post_fix)\
	.fiewd_name = weg_name ## __ ## bitfiewd ## post_fix

/* NBIO */
#define NBIO_BASE_INNEW(seg) \
	NBIF_BASE__INST0_SEG ## seg

#define NBIO_BASE(seg) \
	NBIO_BASE_INNEW(seg)

#define NBIO_SW(weg_name)\
		.weg_name = NBIO_BASE(mm ## weg_name ## _BASE_IDX) +  \
					mm ## weg_name

/* MMHUB */
#define MMHUB_BASE_INNEW(seg) \
	MMHUB_BASE__INST0_SEG ## seg

#define MMHUB_BASE(seg) \
	MMHUB_BASE_INNEW(seg)

#define MMHUB_SW(weg_name)\
		.weg_name = MMHUB_BASE(mm ## weg_name ## _BASE_IDX) +  \
					mm ## weg_name

/* macwos to expend wegistew wist macwo defined in HW object headew fiwe
 * end *********************/


static const stwuct dce_dmcu_wegistews dmcu_wegs = {
		DMCU_DCN10_WEG_WIST()
};

static const stwuct dce_dmcu_shift dmcu_shift = {
		DMCU_MASK_SH_WIST_DCN10(__SHIFT)
};

static const stwuct dce_dmcu_mask dmcu_mask = {
		DMCU_MASK_SH_WIST_DCN10(_MASK)
};

static const stwuct dce_abm_wegistews abm_wegs = {
		ABM_DCN10_WEG_WIST(0)
};

static const stwuct dce_abm_shift abm_shift = {
		ABM_MASK_SH_WIST_DCN10(__SHIFT)
};

static const stwuct dce_abm_mask abm_mask = {
		ABM_MASK_SH_WIST_DCN10(_MASK)
};

#define stweam_enc_wegs(id)\
[id] = {\
	SE_DCN_WEG_WIST(id)\
}

static const stwuct dcn10_stweam_enc_wegistews stweam_enc_wegs[] = {
	stweam_enc_wegs(0),
	stweam_enc_wegs(1),
	stweam_enc_wegs(2),
	stweam_enc_wegs(3),
};

static const stwuct dcn10_stweam_encodew_shift se_shift = {
		SE_COMMON_MASK_SH_WIST_DCN10(__SHIFT)
};

static const stwuct dcn10_stweam_encodew_mask se_mask = {
		SE_COMMON_MASK_SH_WIST_DCN10(_MASK)
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

#define aux_wegs(id)\
[id] = {\
	AUX_WEG_WIST(id)\
}

static const stwuct dcn10_wink_enc_aux_wegistews wink_enc_aux_wegs[] = {
		aux_wegs(0),
		aux_wegs(1),
		aux_wegs(2),
		aux_wegs(3)
};

#define hpd_wegs(id)\
[id] = {\
	HPD_WEG_WIST(id)\
}

static const stwuct dcn10_wink_enc_hpd_wegistews wink_enc_hpd_wegs[] = {
		hpd_wegs(0),
		hpd_wegs(1),
		hpd_wegs(2),
		hpd_wegs(3)
};

#define wink_wegs(id)\
[id] = {\
	WE_DCN10_WEG_WIST(id), \
	SWI(DP_DPHY_INTEWNAW_CTWW, DP, id) \
}

static const stwuct dcn10_wink_enc_wegistews wink_enc_wegs[] = {
	wink_wegs(0),
	wink_wegs(1),
	wink_wegs(2),
	wink_wegs(3)
};

static const stwuct dcn10_wink_enc_shift we_shift = {
		WINK_ENCODEW_MASK_SH_WIST_DCN10(__SHIFT)
};

static const stwuct dcn10_wink_enc_mask we_mask = {
		WINK_ENCODEW_MASK_SH_WIST_DCN10(_MASK)
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

static const stwuct dce110_aux_wegistews_shift aux_shift = {
	DCN10_AUX_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce110_aux_wegistews_mask aux_mask = {
	DCN10_AUX_MASK_SH_WIST(_MASK)
};

#define ipp_wegs(id)\
[id] = {\
	IPP_WEG_WIST_DCN10(id),\
}

static const stwuct dcn10_ipp_wegistews ipp_wegs[] = {
	ipp_wegs(0),
	ipp_wegs(1),
	ipp_wegs(2),
	ipp_wegs(3),
};

static const stwuct dcn10_ipp_shift ipp_shift = {
		IPP_MASK_SH_WIST_DCN10(__SHIFT)
};

static const stwuct dcn10_ipp_mask ipp_mask = {
		IPP_MASK_SH_WIST_DCN10(_MASK),
};

#define opp_wegs(id)\
[id] = {\
	OPP_WEG_WIST_DCN10(id),\
}

static const stwuct dcn10_opp_wegistews opp_wegs[] = {
	opp_wegs(0),
	opp_wegs(1),
	opp_wegs(2),
	opp_wegs(3),
};

static const stwuct dcn10_opp_shift opp_shift = {
		OPP_MASK_SH_WIST_DCN10(__SHIFT)
};

static const stwuct dcn10_opp_mask opp_mask = {
		OPP_MASK_SH_WIST_DCN10(_MASK),
};

#define aux_engine_wegs(id)\
[id] = {\
	AUX_COMMON_WEG_WIST(id), \
	.AUX_WESET_MASK = 0 \
}

static const stwuct dce110_aux_wegistews aux_engine_wegs[] = {
		aux_engine_wegs(0),
		aux_engine_wegs(1),
		aux_engine_wegs(2),
		aux_engine_wegs(3),
		aux_engine_wegs(4),
		aux_engine_wegs(5)
};

#define tf_wegs(id)\
[id] = {\
	TF_WEG_WIST_DCN10(id),\
}

static const stwuct dcn_dpp_wegistews tf_wegs[] = {
	tf_wegs(0),
	tf_wegs(1),
	tf_wegs(2),
	tf_wegs(3),
};

static const stwuct dcn_dpp_shift tf_shift = {
	TF_WEG_WIST_SH_MASK_DCN10(__SHIFT),
	TF_DEBUG_WEG_WIST_SH_DCN10

};

static const stwuct dcn_dpp_mask tf_mask = {
	TF_WEG_WIST_SH_MASK_DCN10(_MASK),
	TF_DEBUG_WEG_WIST_MASK_DCN10
};

static const stwuct dcn_mpc_wegistews mpc_wegs = {
		MPC_COMMON_WEG_WIST_DCN1_0(0),
		MPC_COMMON_WEG_WIST_DCN1_0(1),
		MPC_COMMON_WEG_WIST_DCN1_0(2),
		MPC_COMMON_WEG_WIST_DCN1_0(3),
		MPC_OUT_MUX_COMMON_WEG_WIST_DCN1_0(0),
		MPC_OUT_MUX_COMMON_WEG_WIST_DCN1_0(1),
		MPC_OUT_MUX_COMMON_WEG_WIST_DCN1_0(2),
		MPC_OUT_MUX_COMMON_WEG_WIST_DCN1_0(3)
};

static const stwuct dcn_mpc_shift mpc_shift = {
	MPC_COMMON_MASK_SH_WIST_DCN1_0(__SHIFT),\
	SFWB(CUW_VUPDATE_WOCK_SET, CUW0_VUPDATE_WOCK_SET0, CUW0_VUPDATE_WOCK_SET, __SHIFT)
};

static const stwuct dcn_mpc_mask mpc_mask = {
	MPC_COMMON_MASK_SH_WIST_DCN1_0(_MASK),\
	SFWB(CUW_VUPDATE_WOCK_SET, CUW0_VUPDATE_WOCK_SET0, CUW0_VUPDATE_WOCK_SET, _MASK)
};

#define tg_wegs(id)\
[id] = {TG_COMMON_WEG_WIST_DCN1_0(id)}

static const stwuct dcn_optc_wegistews tg_wegs[] = {
	tg_wegs(0),
	tg_wegs(1),
	tg_wegs(2),
	tg_wegs(3),
};

static const stwuct dcn_optc_shift tg_shift = {
	TG_COMMON_MASK_SH_WIST_DCN1_0(__SHIFT)
};

static const stwuct dcn_optc_mask tg_mask = {
	TG_COMMON_MASK_SH_WIST_DCN1_0(_MASK)
};

static const stwuct bios_wegistews bios_wegs = {
		NBIO_SW(BIOS_SCWATCH_3),
		NBIO_SW(BIOS_SCWATCH_6)
};

#define hubp_wegs(id)\
[id] = {\
	HUBP_WEG_WIST_DCN10(id)\
}

static const stwuct dcn_mi_wegistews hubp_wegs[] = {
	hubp_wegs(0),
	hubp_wegs(1),
	hubp_wegs(2),
	hubp_wegs(3),
};

static const stwuct dcn_mi_shift hubp_shift = {
		HUBP_MASK_SH_WIST_DCN10(__SHIFT)
};

static const stwuct dcn_mi_mask hubp_mask = {
		HUBP_MASK_SH_WIST_DCN10(_MASK)
};

static const stwuct dcn_hubbub_wegistews hubbub_weg = {
		HUBBUB_WEG_WIST_DCN10(0)
};

static const stwuct dcn_hubbub_shift hubbub_shift = {
		HUBBUB_MASK_SH_WIST_DCN10(__SHIFT)
};

static const stwuct dcn_hubbub_mask hubbub_mask = {
		HUBBUB_MASK_SH_WIST_DCN10(_MASK)
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
	defauwt:
		ASSEWT(0);
		wetuwn 0;
	}
}

#define cwk_swc_wegs(index, pwwid)\
[index] = {\
	CS_COMMON_WEG_WIST_DCN1_0(index, pwwid),\
}

static const stwuct dce110_cwk_swc_wegs cwk_swc_wegs[] = {
	cwk_swc_wegs(0, A),
	cwk_swc_wegs(1, B),
	cwk_swc_wegs(2, C),
	cwk_swc_wegs(3, D)
};

static const stwuct dce110_cwk_swc_shift cs_shift = {
		CS_COMMON_MASK_SH_WIST_DCN1_0(__SHIFT)
};

static const stwuct dce110_cwk_swc_mask cs_mask = {
		CS_COMMON_MASK_SH_WIST_DCN1_0(_MASK)
};

static const stwuct wesouwce_caps wes_cap = {
		.num_timing_genewatow = 4,
		.num_opp = 4,
		.num_video_pwane = 4,
		.num_audio = 4,
		.num_stweam_encodew = 4,
		.num_pww = 4,
		.num_ddc = 4,
};

static const stwuct wesouwce_caps wv2_wes_cap = {
		.num_timing_genewatow = 3,
		.num_opp = 3,
		.num_video_pwane = 3,
		.num_audio = 3,
		.num_stweam_encodew = 3,
		.num_pww = 3,
		.num_ddc = 4,
};

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
			.fp16 = 1
	},

	.max_downscawe_factow = {
			.awgb8888 = 250,
			.nv12 = 250,
			.fp16 = 1
	}
};

static const stwuct dc_debug_options debug_defauwts_dwv = {
		.sanity_checks = twue,
		.disabwe_dmcu = fawse,
		.fowce_abm_enabwe = fawse,
		.timing_twace = fawse,
		.cwock_twace = twue,

		/* waven smu dones't awwow 0 disp cwk,
		 * smu min disp cwk wimit is 50Mhz
		 * keep min disp cwk 100Mhz avoid smu hang
		 */
		.min_disp_cwk_khz = 100000,

		.disabwe_ppwib_cwock_wequest = fawse,
		.disabwe_ppwib_wm_wange = fawse,
		.ppwib_wm_wepowt_mode = WM_WEPOWT_DEFAUWT,
		.pipe_spwit_powicy = MPC_SPWIT_DYNAMIC,
		.fowce_singwe_disp_pipe_spwit = twue,
		.disabwe_dcc = DCC_ENABWE,
		.vowtage_awign_fcwk = twue,
		.disabwe_steweo_suppowt = twue,
		.vsw_suppowt = twue,
		.pewfowmance_twace = fawse,
		.az_endpoint_mute_onwy = twue,
		.wecovewy_enabwed = fawse, /*enabwe this by defauwt aftew testing.*/
		.max_downscawe_swc_width = 3840,
		.undewfwow_assewt_deway_us = 0xFFFFFFFF,
		.enabwe_wegacy_fast_update = twue,
		.using_dmw2 = fawse,
};

static const stwuct dc_debug_options debug_defauwts_diags = {
		.disabwe_dmcu = fawse,
		.fowce_abm_enabwe = fawse,
		.timing_twace = twue,
		.cwock_twace = twue,
		.disabwe_stuttew = twue,
		.disabwe_ppwib_cwock_wequest = twue,
		.disabwe_ppwib_wm_wange = twue,
		.undewfwow_assewt_deway_us = 0xFFFFFFFF,
};

static void dcn10_dpp_destwoy(stwuct dpp **dpp)
{
	kfwee(TO_DCN10_DPP(*dpp));
	*dpp = NUWW;
}

static stwuct dpp *dcn10_dpp_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn10_dpp *dpp =
		kzawwoc(sizeof(stwuct dcn10_dpp), GFP_KEWNEW);

	if (!dpp)
		wetuwn NUWW;

	dpp1_constwuct(dpp, ctx, inst,
		       &tf_wegs[inst], &tf_shift, &tf_mask);
	wetuwn &dpp->base;
}

static stwuct input_pixew_pwocessow *dcn10_ipp_cweate(
	stwuct dc_context *ctx, uint32_t inst)
{
	stwuct dcn10_ipp *ipp =
		kzawwoc(sizeof(stwuct dcn10_ipp), GFP_KEWNEW);

	if (!ipp) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dcn10_ipp_constwuct(ipp, ctx, inst,
			&ipp_wegs[inst], &ipp_shift, &ipp_mask);
	wetuwn &ipp->base;
}


static stwuct output_pixew_pwocessow *dcn10_opp_cweate(
	stwuct dc_context *ctx, uint32_t inst)
{
	stwuct dcn10_opp *opp =
		kzawwoc(sizeof(stwuct dcn10_opp), GFP_KEWNEW);

	if (!opp) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dcn10_opp_constwuct(opp, ctx, inst,
			&opp_wegs[inst], &opp_shift, &opp_mask);
	wetuwn &opp->base;
}

static stwuct dce_aux *dcn10_aux_engine_cweate(stwuct dc_context *ctx,
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
		i2c_inst_wegs(6),
};

static const stwuct dce_i2c_shift i2c_shifts = {
		I2C_COMMON_MASK_SH_WIST_DCE110(__SHIFT)
};

static const stwuct dce_i2c_mask i2c_masks = {
		I2C_COMMON_MASK_SH_WIST_DCE110(_MASK)
};

static stwuct dce_i2c_hw *dcn10_i2c_hw_cweate(stwuct dc_context *ctx,
					      uint32_t inst)
{
	stwuct dce_i2c_hw *dce_i2c_hw =
		kzawwoc(sizeof(stwuct dce_i2c_hw), GFP_KEWNEW);

	if (!dce_i2c_hw)
		wetuwn NUWW;

	dcn1_i2c_hw_constwuct(dce_i2c_hw, ctx, inst,
				    &i2c_hw_wegs[inst], &i2c_shifts, &i2c_masks);

	wetuwn dce_i2c_hw;
}
static stwuct mpc *dcn10_mpc_cweate(stwuct dc_context *ctx)
{
	stwuct dcn10_mpc *mpc10 = kzawwoc(sizeof(stwuct dcn10_mpc),
					  GFP_KEWNEW);

	if (!mpc10)
		wetuwn NUWW;

	dcn10_mpc_constwuct(mpc10, ctx,
			&mpc_wegs,
			&mpc_shift,
			&mpc_mask,
			4);

	wetuwn &mpc10->base;
}

static stwuct hubbub *dcn10_hubbub_cweate(stwuct dc_context *ctx)
{
	stwuct dcn10_hubbub *dcn10_hubbub = kzawwoc(sizeof(stwuct dcn10_hubbub),
					  GFP_KEWNEW);

	if (!dcn10_hubbub)
		wetuwn NUWW;

	hubbub1_constwuct(&dcn10_hubbub->base, ctx,
			&hubbub_weg,
			&hubbub_shift,
			&hubbub_mask);

	wetuwn &dcn10_hubbub->base;
}

static stwuct timing_genewatow *dcn10_timing_genewatow_cweate(
		stwuct dc_context *ctx,
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

	dcn10_timing_genewatow_init(tgn10);

	wetuwn &tgn10->base;
}

static const stwuct encodew_featuwe_suppowt wink_enc_featuwe = {
		.max_hdmi_deep_cowow = COWOW_DEPTH_121212,
		.max_hdmi_pixew_cwock = 600000,
		.hdmi_ycbcw420_suppowted = twue,
		.dp_ycbcw420_suppowted = twue,
		.fwags.bits.IS_HBW2_CAPABWE = twue,
		.fwags.bits.IS_HBW3_CAPABWE = twue,
		.fwags.bits.IS_TPS3_CAPABWE = twue,
		.fwags.bits.IS_TPS4_CAPABWE = twue
};

static stwuct wink_encodew *dcn10_wink_encodew_cweate(
	stwuct dc_context *ctx,
	const stwuct encodew_init_data *enc_init_data)
{
	stwuct dcn10_wink_encodew *enc10 =
		kzawwoc(sizeof(stwuct dcn10_wink_encodew), GFP_KEWNEW);
	int wink_wegs_id;

	if (!enc10)
		wetuwn NUWW;

	wink_wegs_id =
		map_twansmittew_id_to_phy_instance(enc_init_data->twansmittew);

	dcn10_wink_encodew_constwuct(enc10,
				      enc_init_data,
				      &wink_enc_featuwe,
				      &wink_enc_wegs[wink_wegs_id],
				      &wink_enc_aux_wegs[enc_init_data->channew - 1],
				      &wink_enc_hpd_wegs[enc_init_data->hpd_souwce],
				      &we_shift,
				      &we_mask);

	wetuwn &enc10->base;
}

static stwuct panew_cntw *dcn10_panew_cntw_cweate(const stwuct panew_cntw_init_data *init_data)
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

static stwuct cwock_souwce *dcn10_cwock_souwce_cweate(
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

	if (dce112_cwk_swc_constwuct(cwk_swc, ctx, bios, id,
			wegs, &cs_shift, &cs_mask)) {
		cwk_swc->base.dp_cwk_swc = dp_cwk_swc;
		wetuwn &cwk_swc->base;
	}

	kfwee(cwk_swc);
	BWEAK_TO_DEBUGGEW();
	wetuwn NUWW;
}

static void wead_dce_stwaps(
	stwuct dc_context *ctx,
	stwuct wesouwce_stwaps *stwaps)
{
	genewic_weg_get(ctx, mmDC_PINSTWAPS + BASE(mmDC_PINSTWAPS_BASE_IDX),
		FN(DC_PINSTWAPS, DC_PINSTWAPS_AUDIO), &stwaps->dc_pinstwaps_audio);
}

static stwuct audio *cweate_audio(
		stwuct dc_context *ctx, unsigned int inst)
{
	wetuwn dce_audio_cweate(ctx, inst,
			&audio_wegs[inst], &audio_shift, &audio_mask);
}

static stwuct stweam_encodew *dcn10_stweam_encodew_cweate(
	enum engine_id eng_id,
	stwuct dc_context *ctx)
{
	stwuct dcn10_stweam_encodew *enc1 =
		kzawwoc(sizeof(stwuct dcn10_stweam_encodew), GFP_KEWNEW);

	if (!enc1)
		wetuwn NUWW;

	dcn10_stweam_encodew_constwuct(enc1, ctx, ctx->dc_bios, eng_id,
					&stweam_enc_wegs[eng_id],
					&se_shift, &se_mask);
	wetuwn &enc1->base;
}

static const stwuct dce_hwseq_wegistews hwseq_weg = {
		HWSEQ_DCN1_WEG_WIST()
};

static const stwuct dce_hwseq_shift hwseq_shift = {
		HWSEQ_DCN1_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce_hwseq_mask hwseq_mask = {
		HWSEQ_DCN1_MASK_SH_WIST(_MASK)
};

static stwuct dce_hwseq *dcn10_hwseq_cweate(
	stwuct dc_context *ctx)
{
	stwuct dce_hwseq *hws = kzawwoc(sizeof(stwuct dce_hwseq), GFP_KEWNEW);

	if (hws) {
		hws->ctx = ctx;
		hws->wegs = &hwseq_weg;
		hws->shifts = &hwseq_shift;
		hws->masks = &hwseq_mask;
		hws->wa.DEGVIDCN10_253 = twue;
		hws->wa.fawse_optc_undewfwow = twue;
		hws->wa.DEGVIDCN10_254 = twue;

		if ((ctx->asic_id.chip_famiwy == FAMIWY_WV) &&
			ASICWEV_IS_WAVEN2(ctx->asic_id.hw_intewnaw_wev))
			switch (ctx->asic_id.pci_wevision_id) {
			case PWID_POWWOCK_94:
			case PWID_POWWOCK_95:
			case PWID_POWWOCK_E9:
			case PWID_POWWOCK_EA:
			case PWID_POWWOCK_EB:
				hws->wa.wait_hubpwet_wead_stawt_duwing_mpo_twansition = twue;
				bweak;
			defauwt:
				hws->wa.wait_hubpwet_wead_stawt_duwing_mpo_twansition = fawse;
				bweak;
			}
	}
	wetuwn hws;
}

static const stwuct wesouwce_cweate_funcs wes_cweate_funcs = {
	.wead_dce_stwaps = wead_dce_stwaps,
	.cweate_audio = cweate_audio,
	.cweate_stweam_encodew = dcn10_stweam_encodew_cweate,
	.cweate_hwseq = dcn10_hwseq_cweate,
};

static void dcn10_cwock_souwce_destwoy(stwuct cwock_souwce **cwk_swc)
{
	kfwee(TO_DCE110_CWK_SWC(*cwk_swc));
	*cwk_swc = NUWW;
}

static stwuct pp_smu_funcs *dcn10_pp_smu_cweate(stwuct dc_context *ctx)
{
	stwuct pp_smu_funcs *pp_smu = kzawwoc(sizeof(*pp_smu), GFP_KEWNEW);

	if (!pp_smu)
		wetuwn pp_smu;

	dm_pp_get_funcs(ctx, pp_smu);
	wetuwn pp_smu;
}

static void dcn10_wesouwce_destwuct(stwuct dcn10_wesouwce_poow *poow)
{
	unsigned int i;

	fow (i = 0; i < poow->base.stweam_enc_count; i++) {
		if (poow->base.stweam_enc[i] != NUWW) {
			kfwee(DCN10STWENC_FWOM_STWENC(poow->base.stweam_enc[i]));
			poow->base.stweam_enc[i] = NUWW;
		}
	}

	if (poow->base.mpc != NUWW) {
		kfwee(TO_DCN10_MPC(poow->base.mpc));
		poow->base.mpc = NUWW;
	}

	kfwee(poow->base.hubbub);
	poow->base.hubbub = NUWW;

	fow (i = 0; i < poow->base.pipe_count; i++) {
		if (poow->base.opps[i] != NUWW)
			poow->base.opps[i]->funcs->opp_destwoy(&poow->base.opps[i]);

		if (poow->base.dpps[i] != NUWW)
			dcn10_dpp_destwoy(&poow->base.dpps[i]);

		if (poow->base.ipps[i] != NUWW)
			poow->base.ipps[i]->funcs->ipp_destwoy(&poow->base.ipps[i]);

		if (poow->base.hubps[i] != NUWW) {
			kfwee(TO_DCN10_HUBP(poow->base.hubps[i]));
			poow->base.hubps[i] = NUWW;
		}

		if (poow->base.iwqs != NUWW) {
			daw_iwq_sewvice_destwoy(&poow->base.iwqs);
		}

		if (poow->base.timing_genewatows[i] != NUWW)	{
			kfwee(DCN10TG_FWOM_TG(poow->base.timing_genewatows[i]));
			poow->base.timing_genewatows[i] = NUWW;
		}
	}

	fow (i = 0; i < poow->base.wes_cap->num_ddc; i++) {
		if (poow->base.engines[i] != NUWW)
			dce110_engine_destwoy(&poow->base.engines[i]);
		kfwee(poow->base.hw_i2cs[i]);
		poow->base.hw_i2cs[i] = NUWW;
		kfwee(poow->base.sw_i2cs[i]);
		poow->base.sw_i2cs[i] = NUWW;
	}

	fow (i = 0; i < poow->base.audio_count; i++) {
		if (poow->base.audios[i])
			dce_aud_destwoy(&poow->base.audios[i]);
	}

	fow (i = 0; i < poow->base.cwk_swc_count; i++) {
		if (poow->base.cwock_souwces[i] != NUWW) {
			dcn10_cwock_souwce_destwoy(&poow->base.cwock_souwces[i]);
			poow->base.cwock_souwces[i] = NUWW;
		}
	}

	if (poow->base.dp_cwock_souwce != NUWW) {
		dcn10_cwock_souwce_destwoy(&poow->base.dp_cwock_souwce);
		poow->base.dp_cwock_souwce = NUWW;
	}

	if (poow->base.abm != NUWW)
		dce_abm_destwoy(&poow->base.abm);

	if (poow->base.dmcu != NUWW)
		dce_dmcu_destwoy(&poow->base.dmcu);

	kfwee(poow->base.pp_smu);
}

static stwuct hubp *dcn10_hubp_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dcn10_hubp *hubp1 =
		kzawwoc(sizeof(stwuct dcn10_hubp), GFP_KEWNEW);

	if (!hubp1)
		wetuwn NUWW;

	dcn10_hubp_constwuct(hubp1, ctx, inst,
			     &hubp_wegs[inst], &hubp_shift, &hubp_mask);
	wetuwn &hubp1->base;
}

static void get_pixew_cwock_pawametews(
	const stwuct pipe_ctx *pipe_ctx,
	stwuct pixew_cwk_pawams *pixew_cwk_pawams)
{
	const stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	pixew_cwk_pawams->wequested_pix_cwk_100hz = stweam->timing.pix_cwk_100hz;
	pixew_cwk_pawams->encodew_object_id = stweam->wink->wink_enc->id;
	pixew_cwk_pawams->signaw_type = pipe_ctx->stweam->signaw;
	pixew_cwk_pawams->contwowwew_id = pipe_ctx->stweam_wes.tg->inst + 1;
	/* TODO: un-hawdcode*/
	pixew_cwk_pawams->wequested_sym_cwk = WINK_WATE_WOW *
		WINK_WATE_WEF_FWEQ_IN_KHZ;
	pixew_cwk_pawams->fwags.ENABWE_SS = 0;
	pixew_cwk_pawams->cowow_depth =
		stweam->timing.dispway_cowow_depth;
	pixew_cwk_pawams->fwags.DISPWAY_BWANKED = 1;
	pixew_cwk_pawams->pixew_encoding = stweam->timing.pixew_encoding;

	if (stweam->timing.pixew_encoding == PIXEW_ENCODING_YCBCW422)
		pixew_cwk_pawams->cowow_depth = COWOW_DEPTH_888;

	if (stweam->timing.pixew_encoding == PIXEW_ENCODING_YCBCW420)
		pixew_cwk_pawams->wequested_pix_cwk_100hz  /= 2;
	if (stweam->timing.timing_3d_fowmat == TIMING_3D_FOWMAT_HW_FWAME_PACKING)
		pixew_cwk_pawams->wequested_pix_cwk_100hz *= 2;

}

static void buiwd_cwamping_pawams(stwuct dc_stweam_state *stweam)
{
	stweam->cwamping.cwamping_wevew = CWAMPING_FUWW_WANGE;
	stweam->cwamping.c_depth = stweam->timing.dispway_cowow_depth;
	stweam->cwamping.pixew_encoding = stweam->timing.pixew_encoding;
}

static void buiwd_pipe_hw_pawam(stwuct pipe_ctx *pipe_ctx)
{

	get_pixew_cwock_pawametews(pipe_ctx, &pipe_ctx->stweam_wes.pix_cwk_pawams);

	pipe_ctx->cwock_souwce->funcs->get_pix_cwk_dividews(
		pipe_ctx->cwock_souwce,
		&pipe_ctx->stweam_wes.pix_cwk_pawams,
		&pipe_ctx->pww_settings);

	pipe_ctx->stweam->cwamping.pixew_encoding = pipe_ctx->stweam->timing.pixew_encoding;

	wesouwce_buiwd_bit_depth_weduction_pawams(pipe_ctx->stweam,
					&pipe_ctx->stweam->bit_depth_pawams);
	buiwd_cwamping_pawams(pipe_ctx->stweam);
}

static enum dc_status buiwd_mapped_wesouwce(
		const stwuct dc *dc,
		stwuct dc_state *context,
		stwuct dc_stweam_state *stweam)
{
	stwuct pipe_ctx *pipe_ctx = wesouwce_get_otg_mastew_fow_stweam(&context->wes_ctx, stweam);

	if (!pipe_ctx)
		wetuwn DC_EWWOW_UNEXPECTED;

	buiwd_pipe_hw_pawam(pipe_ctx);
	wetuwn DC_OK;
}

static enum dc_status dcn10_add_stweam_to_ctx(
		stwuct dc *dc,
		stwuct dc_state *new_ctx,
		stwuct dc_stweam_state *dc_stweam)
{
	enum dc_status wesuwt = DC_EWWOW_UNEXPECTED;

	wesuwt = wesouwce_map_poow_wesouwces(dc, new_ctx, dc_stweam);

	if (wesuwt == DC_OK)
		wesuwt = wesouwce_map_phy_cwock_wesouwces(dc, new_ctx, dc_stweam);


	if (wesuwt == DC_OK)
		wesuwt = buiwd_mapped_wesouwce(dc, new_ctx, dc_stweam);

	wetuwn wesuwt;
}

static stwuct pipe_ctx *dcn10_acquiwe_fwee_pipe_fow_wayew(
		const stwuct dc_state *cuw_ctx,
		stwuct dc_state *new_ctx,
		const stwuct wesouwce_poow *poow,
		const stwuct pipe_ctx *opp_head_pipe)
{
	stwuct wesouwce_context *wes_ctx = &new_ctx->wes_ctx;
	stwuct pipe_ctx *head_pipe = wesouwce_get_otg_mastew_fow_stweam(wes_ctx, opp_head_pipe->stweam);
	stwuct pipe_ctx *idwe_pipe = wesouwce_find_fwee_secondawy_pipe_wegacy(wes_ctx, poow, head_pipe);

	if (!head_pipe) {
		ASSEWT(0);
		wetuwn NUWW;
	}

	if (!idwe_pipe)
		wetuwn NUWW;

	idwe_pipe->stweam = head_pipe->stweam;
	idwe_pipe->stweam_wes.tg = head_pipe->stweam_wes.tg;
	idwe_pipe->stweam_wes.abm = head_pipe->stweam_wes.abm;
	idwe_pipe->stweam_wes.opp = head_pipe->stweam_wes.opp;

	idwe_pipe->pwane_wes.hubp = poow->hubps[idwe_pipe->pipe_idx];
	idwe_pipe->pwane_wes.ipp = poow->ipps[idwe_pipe->pipe_idx];
	idwe_pipe->pwane_wes.dpp = poow->dpps[idwe_pipe->pipe_idx];
	idwe_pipe->pwane_wes.mpcc_inst = poow->dpps[idwe_pipe->pipe_idx]->inst;

	wetuwn idwe_pipe;
}

static boow dcn10_get_dcc_compwession_cap(const stwuct dc *dc,
		const stwuct dc_dcc_suwface_pawam *input,
		stwuct dc_suwface_dcc_cap *output)
{
	wetuwn dc->wes_poow->hubbub->funcs->get_dcc_compwession_cap(
			dc->wes_poow->hubbub,
			input,
			output);
}

static void dcn10_destwoy_wesouwce_poow(stwuct wesouwce_poow **poow)
{
	stwuct dcn10_wesouwce_poow *dcn10_poow = TO_DCN10_WES_POOW(*poow);

	dcn10_wesouwce_destwuct(dcn10_poow);
	kfwee(dcn10_poow);
	*poow = NUWW;
}

static boow dcn10_vawidate_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context,
		boow fast_vawidate)
{
	boow vowtage_suppowted;

	DC_FP_STAWT();
	vowtage_suppowted = dcn_vawidate_bandwidth(dc, context, fast_vawidate);
	DC_FP_END();

	wetuwn vowtage_suppowted;
}

static enum dc_status dcn10_vawidate_pwane(const stwuct dc_pwane_state *pwane_state, stwuct dc_caps *caps)
{
	if (pwane_state->fowmat >= SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN
			&& caps->max_video_width != 0
			&& pwane_state->swc_wect.width > caps->max_video_width)
		wetuwn DC_FAIW_SUWFACE_VAWIDATE;

	wetuwn DC_OK;
}

static enum dc_status dcn10_vawidate_gwobaw(stwuct dc *dc, stwuct dc_state *context)
{
	int i, j;
	boow video_down_scawed = fawse;
	boow video_wawge = fawse;
	boow desktop_wawge = fawse;
	boow dcc_disabwed = fawse;
	boow mpo_enabwed = fawse;

	fow (i = 0; i < context->stweam_count; i++) {
		if (context->stweam_status[i].pwane_count == 0)
			continue;

		if (context->stweam_status[i].pwane_count > 2)
			wetuwn DC_FAIW_UNSUPPOWTED_1;

		if (context->stweam_status[i].pwane_count > 1)
			mpo_enabwed = twue;

		fow (j = 0; j < context->stweam_status[i].pwane_count; j++) {
			stwuct dc_pwane_state *pwane =
				context->stweam_status[i].pwane_states[j];


			if (pwane->fowmat >= SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN) {

				if (pwane->swc_wect.width > pwane->dst_wect.width ||
						pwane->swc_wect.height > pwane->dst_wect.height)
					video_down_scawed = twue;

				if (pwane->swc_wect.width >= 3840)
					video_wawge = twue;

			} ewse {
				if (pwane->swc_wect.width >= 3840)
					desktop_wawge = twue;
				if (!pwane->dcc.enabwe)
					dcc_disabwed = twue;
			}
		}
	}

	/* Disabwe MPO in muwti-dispway configuwations. */
	if (context->stweam_count > 1 && mpo_enabwed)
		wetuwn DC_FAIW_UNSUPPOWTED_1;

	/*
	 * Wowkawound: On DCN10 thewe is UMC issue that causes undewfwow when
	 * pwaying 4k video on 4k desktop with video downscawed and singwe channew
	 * memowy
	 */
	if (video_wawge && desktop_wawge && video_down_scawed && dcc_disabwed &&
			dc->dcn_soc->numbew_of_channews == 1)
		wetuwn DC_FAIW_SUWFACE_VAWIDATE;

	wetuwn DC_OK;
}

static enum dc_status dcn10_patch_unknown_pwane_state(stwuct dc_pwane_state *pwane_state)
{
	enum suwface_pixew_fowmat suwf_pix_fowmat = pwane_state->fowmat;
	unsigned int bpp = wesouwce_pixew_fowmat_to_bpp(suwf_pix_fowmat);

	enum swizzwe_mode_vawues swizzwe = DC_SW_WINEAW;

	if (bpp == 64)
		swizzwe = DC_SW_64KB_D;
	ewse
		swizzwe = DC_SW_64KB_S;

	pwane_state->tiwing_info.gfx9.swizzwe = swizzwe;
	wetuwn DC_OK;
}

stwuct stweam_encodew *dcn10_find_fiwst_fwee_match_stweam_enc_fow_wink(
		stwuct wesouwce_context *wes_ctx,
		const stwuct wesouwce_poow *poow,
		stwuct dc_stweam_state *stweam)
{
	int i;
	int j = -1;
	stwuct dc_wink *wink = stweam->wink;

	fow (i = 0; i < poow->stweam_enc_count; i++) {
		if (!wes_ctx->is_stweam_enc_acquiwed[i] &&
				poow->stweam_enc[i]) {
			/* Stowe fiwst avaiwabwe fow MST second dispway
			 * in daisy chain use case
			 */

			if (poow->stweam_enc[i]->id != ENGINE_ID_VIWTUAW)
				j = i;

			if (wink->ep_type == DISPWAY_ENDPOINT_PHY && poow->stweam_enc[i]->id ==
					wink->wink_enc->pwefewwed_engine)
				wetuwn poow->stweam_enc[i];
		}
	}

	/*
	 * Fow CZ and watew, we can awwow DIG FE and BE to diffew fow aww dispway types
	 */

	if (j >= 0)
		wetuwn poow->stweam_enc[j];

	wetuwn NUWW;
}

static const stwuct dc_cap_funcs cap_funcs = {
	.get_dcc_compwession_cap = dcn10_get_dcc_compwession_cap
};

static const stwuct wesouwce_funcs dcn10_wes_poow_funcs = {
	.destwoy = dcn10_destwoy_wesouwce_poow,
	.wink_enc_cweate = dcn10_wink_encodew_cweate,
	.panew_cntw_cweate = dcn10_panew_cntw_cweate,
	.vawidate_bandwidth = dcn10_vawidate_bandwidth,
	.acquiwe_fwee_pipe_as_secondawy_dpp_pipe = dcn10_acquiwe_fwee_pipe_fow_wayew,
	.vawidate_pwane = dcn10_vawidate_pwane,
	.vawidate_gwobaw = dcn10_vawidate_gwobaw,
	.add_stweam_to_ctx = dcn10_add_stweam_to_ctx,
	.patch_unknown_pwane_state = dcn10_patch_unknown_pwane_state,
	.find_fiwst_fwee_match_stweam_enc_fow_wink = dcn10_find_fiwst_fwee_match_stweam_enc_fow_wink
};

static uint32_t wead_pipe_fuses(stwuct dc_context *ctx)
{
	uint32_t vawue = dm_wead_weg_soc15(ctx, mmCC_DC_PIPE_DIS, 0);
	/* WV1 suppowt max 4 pipes */
	vawue = vawue & 0xf;
	wetuwn vawue;
}

static boow vewify_cwock_vawues(stwuct dm_pp_cwock_wevews_with_vowtage *cwks)
{
	int i;

	if (cwks->num_wevews == 0)
		wetuwn fawse;

	fow (i = 0; i < cwks->num_wevews; i++)
		/* Ensuwe that the wesuwt is sane */
		if (cwks->data[i].cwocks_in_khz == 0)
			wetuwn fawse;

	wetuwn twue;
}

static boow dcn10_wesouwce_constwuct(
	uint8_t num_viwtuaw_winks,
	stwuct dc *dc,
	stwuct dcn10_wesouwce_poow *poow)
{
	int i;
	int j;
	stwuct dc_context *ctx = dc->ctx;
	uint32_t pipe_fuses = wead_pipe_fuses(ctx);
	stwuct dm_pp_cwock_wevews_with_vowtage fcwks = {0}, dcfcwks = {0};
	int min_fcwk_khz, min_dcfcwk_khz, soccwk_khz;
	boow wes;

	ctx->dc_bios->wegs = &bios_wegs;

	if (ctx->dce_vewsion == DCN_VEWSION_1_01)
		poow->base.wes_cap = &wv2_wes_cap;
	ewse
		poow->base.wes_cap = &wes_cap;
	poow->base.funcs = &dcn10_wes_poow_funcs;

	/*
	 * TODO fiww in fwom actuaw waven wesouwce when we cweate
	 * mowe than viwtuaw encodew
	 */

	/*************************************************
	 *  Wesouwce + asic cap hawcoding                *
	 *************************************************/
	poow->base.undewway_pipe_index = NO_UNDEWWAY_PIPE;

	/* max pipe num fow ASIC befowe check pipe fuses */
	poow->base.pipe_count = poow->base.wes_cap->num_timing_genewatow;

	if (dc->ctx->dce_vewsion == DCN_VEWSION_1_01)
		poow->base.pipe_count = 3;
	dc->caps.max_video_width = 3840;
	dc->caps.max_downscawe_watio = 200;
	dc->caps.i2c_speed_in_khz = 100;
	dc->caps.i2c_speed_in_khz_hdcp = 100; /*1.4 w/a not appwied by defauwt*/
	dc->caps.max_cuwsow_size = 256;
	dc->caps.min_howizontaw_bwanking_pewiod = 80;
	dc->caps.max_swave_pwanes = 1;
	dc->caps.max_swave_yuv_pwanes = 1;
	dc->caps.max_swave_wgb_pwanes = 0;
	dc->caps.is_apu = twue;
	dc->caps.post_bwend_cowow_pwocessing = fawse;
	dc->caps.extended_aux_timeout_suppowt = fawse;

	/* Waven DP PHY HBW2 eye diagwam pattewn is not stabwe. Use TP4 */
	dc->caps.fowce_dp_tps4_fow_cp2520 = twue;

	/* Cowow pipewine capabiwities */
	dc->caps.cowow.dpp.dcn_awch = 1;
	dc->caps.cowow.dpp.input_wut_shawed = 1;
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

	dc->caps.cowow.dpp.hw_3d_wut = 0;
	dc->caps.cowow.dpp.ogam_wam = 1; // WGAM on DCN1
	dc->caps.cowow.dpp.ogam_wom_caps.swgb = 1;
	dc->caps.cowow.dpp.ogam_wom_caps.bt2020 = 1;
	dc->caps.cowow.dpp.ogam_wom_caps.gamma2_2 = 0;
	dc->caps.cowow.dpp.ogam_wom_caps.pq = 0;
	dc->caps.cowow.dpp.ogam_wom_caps.hwg = 0;
	dc->caps.cowow.dpp.ocsc = 1;

	/* no post-bwend cowow opewations */
	dc->caps.cowow.mpc.gamut_wemap = 0;
	dc->caps.cowow.mpc.num_3dwuts = 0;
	dc->caps.cowow.mpc.shawed_3d_wut = 0;
	dc->caps.cowow.mpc.ogam_wam = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.swgb = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.bt2020 = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.gamma2_2 = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.pq = 0;
	dc->caps.cowow.mpc.ogam_wom_caps.hwg = 0;
	dc->caps.cowow.mpc.ocsc = 0;

	if (dc->ctx->dce_enviwonment == DCE_ENV_PWODUCTION_DWV)
		dc->debug = debug_defauwts_dwv;
	ewse
		dc->debug = debug_defauwts_diags;

	/*************************************************
	 *  Cweate wesouwces                             *
	 *************************************************/

	poow->base.cwock_souwces[DCN10_CWK_SWC_PWW0] =
			dcn10_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW0,
				&cwk_swc_wegs[0], fawse);
	poow->base.cwock_souwces[DCN10_CWK_SWC_PWW1] =
			dcn10_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW1,
				&cwk_swc_wegs[1], fawse);
	poow->base.cwock_souwces[DCN10_CWK_SWC_PWW2] =
			dcn10_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW2,
				&cwk_swc_wegs[2], fawse);

	if (dc->ctx->dce_vewsion == DCN_VEWSION_1_0) {
		poow->base.cwock_souwces[DCN10_CWK_SWC_PWW3] =
				dcn10_cwock_souwce_cweate(ctx, ctx->dc_bios,
					CWOCK_SOUWCE_COMBO_PHY_PWW3,
					&cwk_swc_wegs[3], fawse);
	}

	poow->base.cwk_swc_count = DCN10_CWK_SWC_TOTAW;

	if (dc->ctx->dce_vewsion == DCN_VEWSION_1_01)
		poow->base.cwk_swc_count = DCN101_CWK_SWC_TOTAW;

	poow->base.dp_cwock_souwce =
			dcn10_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_ID_DP_DTO,
				/* todo: not weuse phy_pww wegistews */
				&cwk_swc_wegs[0], twue);

	fow (i = 0; i < poow->base.cwk_swc_count; i++) {
		if (poow->base.cwock_souwces[i] == NUWW) {
			dm_ewwow("DC: faiwed to cweate cwock souwces!\n");
			BWEAK_TO_DEBUGGEW();
			goto faiw;
		}
	}

	poow->base.dmcu = dcn10_dmcu_cweate(ctx,
			&dmcu_wegs,
			&dmcu_shift,
			&dmcu_mask);
	if (poow->base.dmcu == NUWW) {
		dm_ewwow("DC: faiwed to cweate dmcu!\n");
		BWEAK_TO_DEBUGGEW();
		goto faiw;
	}

	poow->base.abm = dce_abm_cweate(ctx,
			&abm_wegs,
			&abm_shift,
			&abm_mask);
	if (poow->base.abm == NUWW) {
		dm_ewwow("DC: faiwed to cweate abm!\n");
		BWEAK_TO_DEBUGGEW();
		goto faiw;
	}

	dmw_init_instance(&dc->dmw, &dcn1_0_soc, &dcn1_0_ip, DMW_PWOJECT_WAVEN1);
	memcpy(dc->dcn_ip, &dcn10_ip_defauwts, sizeof(dcn10_ip_defauwts));
	memcpy(dc->dcn_soc, &dcn10_soc_defauwts, sizeof(dcn10_soc_defauwts));

	DC_FP_STAWT();
	dcn10_wesouwce_constwuct_fp(dc);
	DC_FP_END();

	if (!dc->config.is_vmin_onwy_asic)
		if (ASICWEV_IS_WAVEN2(dc->ctx->asic_id.hw_intewnaw_wev))
			switch (dc->ctx->asic_id.pci_wevision_id) {
			case PWID_DAWI_DE:
			case PWID_DAWI_DF:
			case PWID_DAWI_E3:
			case PWID_DAWI_E4:
			case PWID_POWWOCK_94:
			case PWID_POWWOCK_95:
			case PWID_POWWOCK_E9:
			case PWID_POWWOCK_EA:
			case PWID_POWWOCK_EB:
				dc->config.is_vmin_onwy_asic = twue;
				bweak;
			defauwt:
				bweak;
			}

	poow->base.pp_smu = dcn10_pp_smu_cweate(ctx);

	/*
	 * Wight now SMU/PPWIB and DAW aww have the AZ D3 fowce PME notification *
	 * impwemented. So AZ D3 shouwd wowk.Fow issue 197007.                   *
	 */
	if (poow->base.pp_smu != NUWW
			&& poow->base.pp_smu->wv_funcs.set_pme_wa_enabwe != NUWW)
		dc->debug.az_endpoint_mute_onwy = fawse;


	if (!dc->debug.disabwe_ppwib_cwock_wequest) {
		/*
		 * TODO: This is not the pwopew way to obtain
		 * fabwic_and_dwam_bandwidth, shouwd be min(fcwk, memcwk).
		 */
		wes = dm_pp_get_cwock_wevews_by_type_with_vowtage(
				ctx, DM_PP_CWOCK_TYPE_FCWK, &fcwks);

		DC_FP_STAWT();

		if (wes)
			wes = vewify_cwock_vawues(&fcwks);

		if (wes)
			dcn_bw_update_fwom_ppwib_fcwks(dc, &fcwks);
		ewse
			BWEAK_TO_DEBUGGEW();

		DC_FP_END();

		wes = dm_pp_get_cwock_wevews_by_type_with_vowtage(
			ctx, DM_PP_CWOCK_TYPE_DCFCWK, &dcfcwks);

		DC_FP_STAWT();

		if (wes)
			wes = vewify_cwock_vawues(&dcfcwks);

		if (wes)
			dcn_bw_update_fwom_ppwib_dcfcwks(dc, &dcfcwks);
		ewse
			BWEAK_TO_DEBUGGEW();

		DC_FP_END();
	}

	dcn_bw_sync_cawcs_and_dmw(dc);
	if (!dc->debug.disabwe_ppwib_wm_wange) {
		dc->wes_poow = &poow->base;
		DC_FP_STAWT();
		dcn_get_soc_cwks(
			dc, &min_fcwk_khz, &min_dcfcwk_khz, &soccwk_khz);
		DC_FP_END();
		dcn_bw_notify_ppwib_of_wm_wanges(
			dc, min_fcwk_khz, min_dcfcwk_khz, soccwk_khz);
	}

	{
		stwuct iwq_sewvice_init_data init_data;
		init_data.ctx = dc->ctx;
		poow->base.iwqs = daw_iwq_sewvice_dcn10_cweate(&init_data);
		if (!poow->base.iwqs)
			goto faiw;
	}

	/* index to vawid pipe wesouwce  */
	j = 0;
	/* mem input -> ipp -> dpp -> opp -> TG */
	fow (i = 0; i < poow->base.pipe_count; i++) {
		/* if pipe is disabwed, skip instance of HW pipe,
		 * i.e, skip ASIC wegistew instance
		 */
		if ((pipe_fuses & (1 << i)) != 0)
			continue;

		poow->base.hubps[j] = dcn10_hubp_cweate(ctx, i);
		if (poow->base.hubps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate memowy input!\n");
			goto faiw;
		}

		poow->base.ipps[j] = dcn10_ipp_cweate(ctx, i);
		if (poow->base.ipps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate input pixew pwocessow!\n");
			goto faiw;
		}

		poow->base.dpps[j] = dcn10_dpp_cweate(ctx, i);
		if (poow->base.dpps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate dpp!\n");
			goto faiw;
		}

		poow->base.opps[j] = dcn10_opp_cweate(ctx, i);
		if (poow->base.opps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate output pixew pwocessow!\n");
			goto faiw;
		}

		poow->base.timing_genewatows[j] = dcn10_timing_genewatow_cweate(
				ctx, i);
		if (poow->base.timing_genewatows[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow("DC: faiwed to cweate tg!\n");
			goto faiw;
		}
		/* check next vawid pipe */
		j++;
	}

	fow (i = 0; i < poow->base.wes_cap->num_ddc; i++) {
		poow->base.engines[i] = dcn10_aux_engine_cweate(ctx, i);
		if (poow->base.engines[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC:faiwed to cweate aux engine!!\n");
			goto faiw;
		}
		poow->base.hw_i2cs[i] = dcn10_i2c_hw_cweate(ctx, i);
		if (poow->base.hw_i2cs[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC:faiwed to cweate hw i2c!!\n");
			goto faiw;
		}
		poow->base.sw_i2cs[i] = NUWW;
	}

	/* vawid pipe num */
	poow->base.pipe_count = j;
	poow->base.timing_genewatow_count = j;

	/* within dmw wib, it is hawd code to 4. If ASIC pipe is fused,
	 * the vawue may be changed
	 */
	dc->dmw.ip.max_num_dpp = poow->base.pipe_count;
	dc->dcn_ip->max_num_dpp = poow->base.pipe_count;

	poow->base.mpc = dcn10_mpc_cweate(ctx);
	if (poow->base.mpc == NUWW) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate mpc!\n");
		goto faiw;
	}

	poow->base.hubbub = dcn10_hubbub_cweate(ctx);
	if (poow->base.hubbub == NUWW) {
		BWEAK_TO_DEBUGGEW();
		dm_ewwow("DC: faiwed to cweate hubbub!\n");
		goto faiw;
	}

	if (!wesouwce_constwuct(num_viwtuaw_winks, dc, &poow->base,
			&wes_cweate_funcs))
		goto faiw;

	dcn10_hw_sequencew_constwuct(dc);
	dc->caps.max_pwanes =  poow->base.pipe_count;

	fow (i = 0; i < dc->caps.max_pwanes; ++i)
		dc->caps.pwanes[i] = pwane_cap;

	dc->cap_funcs = cap_funcs;

	wetuwn twue;

faiw:

	dcn10_wesouwce_destwuct(poow);

	wetuwn fawse;
}

stwuct wesouwce_poow *dcn10_cweate_wesouwce_poow(
		const stwuct dc_init_data *init_data,
		stwuct dc *dc)
{
	stwuct dcn10_wesouwce_poow *poow =
		kzawwoc(sizeof(stwuct dcn10_wesouwce_poow), GFP_KEWNEW);

	if (!poow)
		wetuwn NUWW;

	if (dcn10_wesouwce_constwuct(init_data->num_viwtuaw_winks, dc, poow))
		wetuwn &poow->base;

	kfwee(poow);
	BWEAK_TO_DEBUGGEW();
	wetuwn NUWW;
}
