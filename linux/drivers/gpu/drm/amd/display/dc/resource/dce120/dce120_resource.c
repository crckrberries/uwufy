/*
* Copywight 2012-15 Advanced Micwo Devices, Inc.cws
*
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


#incwude "stweam_encodew.h"
#incwude "wesouwce.h"
#incwude "incwude/iwq_sewvice_intewface.h"
#incwude "dce120_wesouwce.h"

#incwude "dce112/dce112_wesouwce.h"

#incwude "dce110/dce110_wesouwce.h"
#incwude "viwtuaw/viwtuaw_stweam_encodew.h"
#incwude "dce120/dce120_timing_genewatow.h"
#incwude "iwq/dce120/iwq_sewvice_dce120.h"
#incwude "dce/dce_opp.h"
#incwude "dce/dce_cwock_souwce.h"
#incwude "dce/dce_ipp.h"
#incwude "dce/dce_mem_input.h"
#incwude "dce/dce_panew_cntw.h"

#incwude "dce110/dce110_hwseq.h"
#incwude "dce120/dce120_hwseq.h"
#incwude "dce/dce_twansfowm.h"
#incwude "cwk_mgw.h"
#incwude "dce/dce_audio.h"
#incwude "dce/dce_wink_encodew.h"
#incwude "dce/dce_stweam_encodew.h"
#incwude "dce/dce_hwseq.h"
#incwude "dce/dce_abm.h"
#incwude "dce/dce_dmcu.h"
#incwude "dce/dce_aux.h"
#incwude "dce/dce_i2c.h"

#incwude "dce/dce_12_0_offset.h"
#incwude "dce/dce_12_0_sh_mask.h"
#incwude "soc15_hw_ip.h"
#incwude "vega10_ip_offset.h"
#incwude "nbio/nbio_6_1_offset.h"
#incwude "mmhub/mmhub_1_0_offset.h"
#incwude "mmhub/mmhub_1_0_sh_mask.h"
#incwude "weg_hewpew.h"

#incwude "dce100/dce100_wesouwce.h"

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

enum dce120_cwk_swc_awway_id {
	DCE120_CWK_SWC_PWW0,
	DCE120_CWK_SWC_PWW1,
	DCE120_CWK_SWC_PWW2,
	DCE120_CWK_SWC_PWW3,
	DCE120_CWK_SWC_PWW4,
	DCE120_CWK_SWC_PWW5,

	DCE120_CWK_SWC_TOTAW
};

static const stwuct dce110_timing_genewatow_offsets dce120_tg_offsets[] = {
	{
		.cwtc = (mmCWTC0_CWTC_CONTWOW - mmCWTC0_CWTC_CONTWOW),
	},
	{
		.cwtc = (mmCWTC1_CWTC_CONTWOW - mmCWTC0_CWTC_CONTWOW),
	},
	{
		.cwtc = (mmCWTC2_CWTC_CONTWOW - mmCWTC0_CWTC_CONTWOW),
	},
	{
		.cwtc = (mmCWTC3_CWTC_CONTWOW - mmCWTC0_CWTC_CONTWOW),
	},
	{
		.cwtc = (mmCWTC4_CWTC_CONTWOW - mmCWTC0_CWTC_CONTWOW),
	},
	{
		.cwtc = (mmCWTC5_CWTC_CONTWOW - mmCWTC0_CWTC_CONTWOW),
	}
};

/* begin *********************
 * macwos to expend wegistew wist macwo defined in HW object headew fiwe */

#define BASE_INNEW(seg) \
	DCE_BASE__INST0_SEG ## seg

#define NBIO_BASE_INNEW(seg) \
	NBIF_BASE__INST0_SEG ## seg

#define NBIO_BASE(seg) \
	NBIO_BASE_INNEW(seg)

/* compiwe time expand base addwess. */
#define BASE(seg) \
	BASE_INNEW(seg)

#define SW(weg_name)\
		.weg_name = BASE(mm ## weg_name ## _BASE_IDX) +  \
					mm ## weg_name

#define SWI(weg_name, bwock, id)\
	.weg_name = BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## id ## _ ## weg_name

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
		DMCU_DCE110_COMMON_WEG_WIST()
};

static const stwuct dce_dmcu_shift dmcu_shift = {
		DMCU_MASK_SH_WIST_DCE110(__SHIFT)
};

static const stwuct dce_dmcu_mask dmcu_mask = {
		DMCU_MASK_SH_WIST_DCE110(_MASK)
};

static const stwuct dce_abm_wegistews abm_wegs = {
		ABM_DCE110_COMMON_WEG_WIST()
};

static const stwuct dce_abm_shift abm_shift = {
		ABM_MASK_SH_WIST_DCE110(__SHIFT)
};

static const stwuct dce_abm_mask abm_mask = {
		ABM_MASK_SH_WIST_DCE110(_MASK)
};

#define ipp_wegs(id)\
[id] = {\
		IPP_DCE110_WEG_WIST_DCE_BASE(id)\
}

static const stwuct dce_ipp_wegistews ipp_wegs[] = {
		ipp_wegs(0),
		ipp_wegs(1),
		ipp_wegs(2),
		ipp_wegs(3),
		ipp_wegs(4),
		ipp_wegs(5)
};

static const stwuct dce_ipp_shift ipp_shift = {
		IPP_DCE120_MASK_SH_WIST_SOC_BASE(__SHIFT)
};

static const stwuct dce_ipp_mask ipp_mask = {
		IPP_DCE120_MASK_SH_WIST_SOC_BASE(_MASK)
};

#define twansfowm_wegs(id)\
[id] = {\
		XFM_COMMON_WEG_WIST_DCE110(id)\
}

static const stwuct dce_twansfowm_wegistews xfm_wegs[] = {
		twansfowm_wegs(0),
		twansfowm_wegs(1),
		twansfowm_wegs(2),
		twansfowm_wegs(3),
		twansfowm_wegs(4),
		twansfowm_wegs(5)
};

static const stwuct dce_twansfowm_shift xfm_shift = {
		XFM_COMMON_MASK_SH_WIST_SOC_BASE(__SHIFT)
};

static const stwuct dce_twansfowm_mask xfm_mask = {
		XFM_COMMON_MASK_SH_WIST_SOC_BASE(_MASK)
};

#define aux_wegs(id)\
[id] = {\
	AUX_WEG_WIST(id)\
}

static const stwuct dce110_wink_enc_aux_wegistews wink_enc_aux_wegs[] = {
		aux_wegs(0),
		aux_wegs(1),
		aux_wegs(2),
		aux_wegs(3),
		aux_wegs(4),
		aux_wegs(5)
};

#define hpd_wegs(id)\
[id] = {\
	HPD_WEG_WIST(id)\
}

static const stwuct dce110_wink_enc_hpd_wegistews wink_enc_hpd_wegs[] = {
		hpd_wegs(0),
		hpd_wegs(1),
		hpd_wegs(2),
		hpd_wegs(3),
		hpd_wegs(4),
		hpd_wegs(5)
};

#define wink_wegs(id)\
[id] = {\
	WE_DCE120_WEG_WIST(id), \
	SWI(DP_DPHY_INTEWNAW_CTWW, DP, id) \
}

static const stwuct dce110_wink_enc_wegistews wink_enc_wegs[] = {
	wink_wegs(0),
	wink_wegs(1),
	wink_wegs(2),
	wink_wegs(3),
	wink_wegs(4),
	wink_wegs(5),
	wink_wegs(6),
};


#define stweam_enc_wegs(id)\
[id] = {\
	SE_COMMON_WEG_WIST(id),\
	.TMDS_CNTW = 0,\
}

static const stwuct dce110_stweam_enc_wegistews stweam_enc_wegs[] = {
	stweam_enc_wegs(0),
	stweam_enc_wegs(1),
	stweam_enc_wegs(2),
	stweam_enc_wegs(3),
	stweam_enc_wegs(4),
	stweam_enc_wegs(5)
};

static const stwuct dce_stweam_encodew_shift se_shift = {
		SE_COMMON_MASK_SH_WIST_DCE120(__SHIFT)
};

static const stwuct dce_stweam_encodew_mask se_mask = {
		SE_COMMON_MASK_SH_WIST_DCE120(_MASK)
};

static const stwuct dce_panew_cntw_wegistews panew_cntw_wegs[] = {
	{ DCE_PANEW_CNTW_WEG_WIST() }
};

static const stwuct dce_panew_cntw_shift panew_cntw_shift = {
	DCE_PANEW_CNTW_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce_panew_cntw_mask panew_cntw_mask = {
	DCE_PANEW_CNTW_MASK_SH_WIST(_MASK)
};

static const stwuct dce110_aux_wegistews_shift aux_shift = {
	DCE12_AUX_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce110_aux_wegistews_mask aux_mask = {
	DCE12_AUX_MASK_SH_WIST(_MASK)
};

#define opp_wegs(id)\
[id] = {\
	OPP_DCE_120_WEG_WIST(id),\
}

static const stwuct dce_opp_wegistews opp_wegs[] = {
	opp_wegs(0),
	opp_wegs(1),
	opp_wegs(2),
	opp_wegs(3),
	opp_wegs(4),
	opp_wegs(5)
};

static const stwuct dce_opp_shift opp_shift = {
	OPP_COMMON_MASK_SH_WIST_DCE_120(__SHIFT)
};

static const stwuct dce_opp_mask opp_mask = {
	OPP_COMMON_MASK_SH_WIST_DCE_120(_MASK)
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
	audio_wegs(6),
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

static int map_twansmittew_id_to_phy_instance(
	enum twansmittew twansmittew)
{
	switch (twansmittew) {
	case TWANSMITTEW_UNIPHY_A:
		wetuwn 0;
	case TWANSMITTEW_UNIPHY_B:
		wetuwn 1;
	case TWANSMITTEW_UNIPHY_C:
		wetuwn 2;
	case TWANSMITTEW_UNIPHY_D:
		wetuwn 3;
	case TWANSMITTEW_UNIPHY_E:
		wetuwn 4;
	case TWANSMITTEW_UNIPHY_F:
		wetuwn 5;
	case TWANSMITTEW_UNIPHY_G:
		wetuwn 6;
	defauwt:
		ASSEWT(0);
		wetuwn 0;
	}
}

#define cwk_swc_wegs(index, id)\
[index] = {\
	CS_COMMON_WEG_WIST_DCE_112(id),\
}

static const stwuct dce110_cwk_swc_wegs cwk_swc_wegs[] = {
	cwk_swc_wegs(0, A),
	cwk_swc_wegs(1, B),
	cwk_swc_wegs(2, C),
	cwk_swc_wegs(3, D),
	cwk_swc_wegs(4, E),
	cwk_swc_wegs(5, F)
};

static const stwuct dce110_cwk_swc_shift cs_shift = {
		CS_COMMON_MASK_SH_WIST_DCE_112(__SHIFT)
};

static const stwuct dce110_cwk_swc_mask cs_mask = {
		CS_COMMON_MASK_SH_WIST_DCE_112(_MASK)
};

static stwuct output_pixew_pwocessow *dce120_opp_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dce110_opp *opp =
		kzawwoc(sizeof(stwuct dce110_opp), GFP_KEWNEW);

	if (!opp)
		wetuwn NUWW;

	dce110_opp_constwuct(opp,
			     ctx, inst, &opp_wegs[inst], &opp_shift, &opp_mask);
	wetuwn &opp->base;
}
static stwuct dce_aux *dce120_aux_engine_cweate(
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
		i2c_inst_wegs(6),
};

static const stwuct dce_i2c_shift i2c_shifts = {
		I2C_COMMON_MASK_SH_WIST_DCE110(__SHIFT)
};

static const stwuct dce_i2c_mask i2c_masks = {
		I2C_COMMON_MASK_SH_WIST_DCE110(_MASK)
};

static stwuct dce_i2c_hw *dce120_i2c_hw_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dce_i2c_hw *dce_i2c_hw =
		kzawwoc(sizeof(stwuct dce_i2c_hw), GFP_KEWNEW);

	if (!dce_i2c_hw)
		wetuwn NUWW;

	dce112_i2c_hw_constwuct(dce_i2c_hw, ctx, inst,
				    &i2c_hw_wegs[inst], &i2c_shifts, &i2c_masks);

	wetuwn dce_i2c_hw;
}
static const stwuct bios_wegistews bios_wegs = {
	.BIOS_SCWATCH_3 = mmBIOS_SCWATCH_3 + NBIO_BASE(mmBIOS_SCWATCH_3_BASE_IDX),
	.BIOS_SCWATCH_6 = mmBIOS_SCWATCH_6 + NBIO_BASE(mmBIOS_SCWATCH_6_BASE_IDX)
};

static const stwuct wesouwce_caps wes_cap = {
		.num_timing_genewatow = 6,
		.num_audio = 7,
		.num_stweam_encodew = 6,
		.num_pww = 6,
		.num_ddc = 6,
};

static const stwuct dc_pwane_cap pwane_cap = {
	.type = DC_PWANE_TYPE_DCE_WGB,

	.pixew_fowmat_suppowt = {
			.awgb8888 = twue,
			.nv12 = fawse,
			.fp16 = twue
	},

	.max_upscawe_factow = {
			.awgb8888 = 16000,
			.nv12 = 1,
			.fp16 = 1
	},

	.max_downscawe_factow = {
			.awgb8888 = 250,
			.nv12 = 1,
			.fp16 = 1
	}
};

static const stwuct dc_debug_options debug_defauwts = {
		.disabwe_cwock_gate = twue,
		.enabwe_wegacy_fast_update = twue,
};

static stwuct cwock_souwce *dce120_cwock_souwce_cweate(
	stwuct dc_context *ctx,
	stwuct dc_bios *bios,
	enum cwock_souwce_id id,
	const stwuct dce110_cwk_swc_wegs *wegs,
	boow dp_cwk_swc)
{
	stwuct dce110_cwk_swc *cwk_swc =
		kzawwoc(sizeof(*cwk_swc), GFP_KEWNEW);

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

static void dce120_cwock_souwce_destwoy(stwuct cwock_souwce **cwk_swc)
{
	kfwee(TO_DCE110_CWK_SWC(*cwk_swc));
	*cwk_swc = NUWW;
}


static boow dce120_hw_sequencew_cweate(stwuct dc *dc)
{
	/* Aww wegistews used by dce11.2 match those in dce11 in offset and
	 * stwuctuwe
	 */
	dce120_hw_sequencew_constwuct(dc);

	/*TODO	Move to sepawate fiwe and Ovewwide what is needed */

	wetuwn twue;
}

static stwuct timing_genewatow *dce120_timing_genewatow_cweate(
		stwuct dc_context *ctx,
		uint32_t instance,
		const stwuct dce110_timing_genewatow_offsets *offsets)
{
	stwuct dce110_timing_genewatow *tg110 =
		kzawwoc(sizeof(stwuct dce110_timing_genewatow), GFP_KEWNEW);

	if (!tg110)
		wetuwn NUWW;

	dce120_timing_genewatow_constwuct(tg110, ctx, instance, offsets);
	wetuwn &tg110->base;
}

static void dce120_twansfowm_destwoy(stwuct twansfowm **xfm)
{
	kfwee(TO_DCE_TWANSFOWM(*xfm));
	*xfm = NUWW;
}

static void dce120_wesouwce_destwuct(stwuct dce110_wesouwce_poow *poow)
{
	unsigned int i;

	fow (i = 0; i < poow->base.pipe_count; i++) {
		if (poow->base.opps[i] != NUWW)
			dce110_opp_destwoy(&poow->base.opps[i]);

		if (poow->base.twansfowms[i] != NUWW)
			dce120_twansfowm_destwoy(&poow->base.twansfowms[i]);

		if (poow->base.ipps[i] != NUWW)
			dce_ipp_destwoy(&poow->base.ipps[i]);

		if (poow->base.mis[i] != NUWW) {
			kfwee(TO_DCE_MEM_INPUT(poow->base.mis[i]));
			poow->base.mis[i] = NUWW;
		}

		if (poow->base.iwqs != NUWW) {
			daw_iwq_sewvice_destwoy(&poow->base.iwqs);
		}

		if (poow->base.timing_genewatows[i] != NUWW) {
			kfwee(DCE110TG_FWOM_TG(poow->base.timing_genewatows[i]));
			poow->base.timing_genewatows[i] = NUWW;
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

	fow (i = 0; i < poow->base.audio_count; i++) {
		if (poow->base.audios[i])
			dce_aud_destwoy(&poow->base.audios[i]);
	}

	fow (i = 0; i < poow->base.stweam_enc_count; i++) {
		if (poow->base.stweam_enc[i] != NUWW)
			kfwee(DCE110STWENC_FWOM_STWENC(poow->base.stweam_enc[i]));
	}

	fow (i = 0; i < poow->base.cwk_swc_count; i++) {
		if (poow->base.cwock_souwces[i] != NUWW)
			dce120_cwock_souwce_destwoy(
				&poow->base.cwock_souwces[i]);
	}

	if (poow->base.dp_cwock_souwce != NUWW)
		dce120_cwock_souwce_destwoy(&poow->base.dp_cwock_souwce);

	if (poow->base.abm != NUWW)
		dce_abm_destwoy(&poow->base.abm);

	if (poow->base.dmcu != NUWW)
		dce_dmcu_destwoy(&poow->base.dmcu);
}

static void wead_dce_stwaps(
	stwuct dc_context *ctx,
	stwuct wesouwce_stwaps *stwaps)
{
	uint32_t weg_vaw = dm_wead_weg_soc15(ctx, mmCC_DC_MISC_STWAPS, 0);

	stwaps->audio_stweam_numbew = get_weg_fiewd_vawue(weg_vaw,
							  CC_DC_MISC_STWAPS,
							  AUDIO_STWEAM_NUMBEW);
	stwaps->hdmi_disabwe = get_weg_fiewd_vawue(weg_vaw,
						   CC_DC_MISC_STWAPS,
						   HDMI_DISABWE);

	weg_vaw = dm_wead_weg_soc15(ctx, mmDC_PINSTWAPS, 0);
	stwaps->dc_pinstwaps_audio = get_weg_fiewd_vawue(weg_vaw,
							 DC_PINSTWAPS,
							 DC_PINSTWAPS_AUDIO);
}

static stwuct audio *cweate_audio(
		stwuct dc_context *ctx, unsigned int inst)
{
	wetuwn dce_audio_cweate(ctx, inst,
			&audio_wegs[inst], &audio_shift, &audio_mask);
}

static const stwuct encodew_featuwe_suppowt wink_enc_featuwe = {
		.max_hdmi_deep_cowow = COWOW_DEPTH_121212,
		.max_hdmi_pixew_cwock = 600000,
		.hdmi_ycbcw420_suppowted = twue,
		.dp_ycbcw420_suppowted = fawse,
		.fwags.bits.IS_HBW2_CAPABWE = twue,
		.fwags.bits.IS_HBW3_CAPABWE = twue,
		.fwags.bits.IS_TPS3_CAPABWE = twue,
		.fwags.bits.IS_TPS4_CAPABWE = twue,
};

static stwuct wink_encodew *dce120_wink_encodew_cweate(
	stwuct dc_context *ctx,
	const stwuct encodew_init_data *enc_init_data)
{
	stwuct dce110_wink_encodew *enc110 =
		kzawwoc(sizeof(stwuct dce110_wink_encodew), GFP_KEWNEW);
	int wink_wegs_id;

	if (!enc110)
		wetuwn NUWW;

	wink_wegs_id =
		map_twansmittew_id_to_phy_instance(enc_init_data->twansmittew);

	dce110_wink_encodew_constwuct(enc110,
				      enc_init_data,
				      &wink_enc_featuwe,
				      &wink_enc_wegs[wink_wegs_id],
				      &wink_enc_aux_wegs[enc_init_data->channew - 1],
				      &wink_enc_hpd_wegs[enc_init_data->hpd_souwce]);

	wetuwn &enc110->base;
}

static stwuct panew_cntw *dce120_panew_cntw_cweate(const stwuct panew_cntw_init_data *init_data)
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

static stwuct input_pixew_pwocessow *dce120_ipp_cweate(
	stwuct dc_context *ctx, uint32_t inst)
{
	stwuct dce_ipp *ipp = kzawwoc(sizeof(stwuct dce_ipp), GFP_KEWNEW);

	if (!ipp) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dce_ipp_constwuct(ipp, ctx, inst,
			&ipp_wegs[inst], &ipp_shift, &ipp_mask);
	wetuwn &ipp->base;
}

static stwuct stweam_encodew *dce120_stweam_encodew_cweate(
	enum engine_id eng_id,
	stwuct dc_context *ctx)
{
	stwuct dce110_stweam_encodew *enc110 =
		kzawwoc(sizeof(stwuct dce110_stweam_encodew), GFP_KEWNEW);

	if (!enc110)
		wetuwn NUWW;

	dce110_stweam_encodew_constwuct(enc110, ctx, ctx->dc_bios, eng_id,
					&stweam_enc_wegs[eng_id],
					&se_shift, &se_mask);
	wetuwn &enc110->base;
}

#define SWII(weg_name, bwock, id)\
	.weg_name[id] = BASE(mm ## bwock ## id ## _ ## weg_name ## _BASE_IDX) + \
					mm ## bwock ## id ## _ ## weg_name

static const stwuct dce_hwseq_wegistews hwseq_weg = {
		HWSEQ_DCE120_WEG_WIST()
};

static const stwuct dce_hwseq_shift hwseq_shift = {
		HWSEQ_DCE12_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce_hwseq_mask hwseq_mask = {
		HWSEQ_DCE12_MASK_SH_WIST(_MASK)
};

/* HWSEQ wegs fow VG20 */
static const stwuct dce_hwseq_wegistews dce121_hwseq_weg = {
		HWSEQ_VG20_WEG_WIST()
};

static const stwuct dce_hwseq_shift dce121_hwseq_shift = {
		HWSEQ_VG20_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce_hwseq_mask dce121_hwseq_mask = {
		HWSEQ_VG20_MASK_SH_WIST(_MASK)
};

static stwuct dce_hwseq *dce120_hwseq_cweate(
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

static stwuct dce_hwseq *dce121_hwseq_cweate(
	stwuct dc_context *ctx)
{
	stwuct dce_hwseq *hws = kzawwoc(sizeof(stwuct dce_hwseq), GFP_KEWNEW);

	if (hws) {
		hws->ctx = ctx;
		hws->wegs = &dce121_hwseq_weg;
		hws->shifts = &dce121_hwseq_shift;
		hws->masks = &dce121_hwseq_mask;
	}
	wetuwn hws;
}

static const stwuct wesouwce_cweate_funcs wes_cweate_funcs = {
	.wead_dce_stwaps = wead_dce_stwaps,
	.cweate_audio = cweate_audio,
	.cweate_stweam_encodew = dce120_stweam_encodew_cweate,
	.cweate_hwseq = dce120_hwseq_cweate,
};

static const stwuct wesouwce_cweate_funcs dce121_wes_cweate_funcs = {
	.wead_dce_stwaps = wead_dce_stwaps,
	.cweate_audio = cweate_audio,
	.cweate_stweam_encodew = dce120_stweam_encodew_cweate,
	.cweate_hwseq = dce121_hwseq_cweate,
};


#define mi_inst_wegs(id) { MI_DCE12_WEG_WIST(id) }
static const stwuct dce_mem_input_wegistews mi_wegs[] = {
		mi_inst_wegs(0),
		mi_inst_wegs(1),
		mi_inst_wegs(2),
		mi_inst_wegs(3),
		mi_inst_wegs(4),
		mi_inst_wegs(5),
};

static const stwuct dce_mem_input_shift mi_shifts = {
		MI_DCE12_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce_mem_input_mask mi_masks = {
		MI_DCE12_MASK_SH_WIST(_MASK)
};

static stwuct mem_input *dce120_mem_input_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dce_mem_input *dce_mi = kzawwoc(sizeof(stwuct dce_mem_input),
					       GFP_KEWNEW);

	if (!dce_mi) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dce120_mem_input_constwuct(dce_mi, ctx, inst, &mi_wegs[inst], &mi_shifts, &mi_masks);
	wetuwn &dce_mi->base;
}

static stwuct twansfowm *dce120_twansfowm_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dce_twansfowm *twansfowm =
		kzawwoc(sizeof(stwuct dce_twansfowm), GFP_KEWNEW);

	if (!twansfowm)
		wetuwn NUWW;

	dce_twansfowm_constwuct(twansfowm, ctx, inst,
				&xfm_wegs[inst], &xfm_shift, &xfm_mask);
	twansfowm->wb_memowy_size = 0x1404; /*5124*/
	wetuwn &twansfowm->base;
}

static void dce120_destwoy_wesouwce_poow(stwuct wesouwce_poow **poow)
{
	stwuct dce110_wesouwce_poow *dce110_poow = TO_DCE110_WES_POOW(*poow);

	dce120_wesouwce_destwuct(dce110_poow);
	kfwee(dce110_poow);
	*poow = NUWW;
}

static const stwuct wesouwce_funcs dce120_wes_poow_funcs = {
	.destwoy = dce120_destwoy_wesouwce_poow,
	.wink_enc_cweate = dce120_wink_encodew_cweate,
	.panew_cntw_cweate = dce120_panew_cntw_cweate,
	.vawidate_bandwidth = dce112_vawidate_bandwidth,
	.vawidate_pwane = dce100_vawidate_pwane,
	.add_stweam_to_ctx = dce112_add_stweam_to_ctx,
	.find_fiwst_fwee_match_stweam_enc_fow_wink = dce110_find_fiwst_fwee_match_stweam_enc_fow_wink
};

static void bw_cawcs_data_update_fwom_ppwib(stwuct dc *dc)
{
	stwuct dm_pp_cwock_wevews_with_watency eng_cwks = {0};
	stwuct dm_pp_cwock_wevews_with_watency mem_cwks = {0};
	stwuct dm_pp_wm_sets_with_cwock_wanges cwk_wanges = {0};
	int i;
	unsigned int cwk;
	unsigned int watency;
	/*owiginaw wogic in daw3*/
	int memowy_type_muwtipwiew = MEMOWY_TYPE_MUWTIPWIEW_CZ;

	/*do system cwock*/
	if (!dm_pp_get_cwock_wevews_by_type_with_watency(
				dc->ctx,
				DM_PP_CWOCK_TYPE_ENGINE_CWK,
				&eng_cwks) || eng_cwks.num_wevews == 0) {

		eng_cwks.num_wevews = 8;
		cwk = 300000;

		fow (i = 0; i < eng_cwks.num_wevews; i++) {
			eng_cwks.data[i].cwocks_in_khz = cwk;
			cwk += 100000;
		}
	}

	/* convewt aww the cwock fwo kHz to fix point mHz  TODO: wwoop data */
	dc->bw_vbios->high_scwk = bw_fwc_to_fixed(
		eng_cwks.data[eng_cwks.num_wevews-1].cwocks_in_khz, 1000);
	dc->bw_vbios->mid1_scwk  = bw_fwc_to_fixed(
		eng_cwks.data[eng_cwks.num_wevews/8].cwocks_in_khz, 1000);
	dc->bw_vbios->mid2_scwk  = bw_fwc_to_fixed(
		eng_cwks.data[eng_cwks.num_wevews*2/8].cwocks_in_khz, 1000);
	dc->bw_vbios->mid3_scwk  = bw_fwc_to_fixed(
		eng_cwks.data[eng_cwks.num_wevews*3/8].cwocks_in_khz, 1000);
	dc->bw_vbios->mid4_scwk  = bw_fwc_to_fixed(
		eng_cwks.data[eng_cwks.num_wevews*4/8].cwocks_in_khz, 1000);
	dc->bw_vbios->mid5_scwk  = bw_fwc_to_fixed(
		eng_cwks.data[eng_cwks.num_wevews*5/8].cwocks_in_khz, 1000);
	dc->bw_vbios->mid6_scwk  = bw_fwc_to_fixed(
		eng_cwks.data[eng_cwks.num_wevews*6/8].cwocks_in_khz, 1000);
	dc->bw_vbios->wow_scwk  = bw_fwc_to_fixed(
			eng_cwks.data[0].cwocks_in_khz, 1000);

	/*do memowy cwock*/
	if (!dm_pp_get_cwock_wevews_by_type_with_watency(
			dc->ctx,
			DM_PP_CWOCK_TYPE_MEMOWY_CWK,
			&mem_cwks) || mem_cwks.num_wevews == 0) {

		mem_cwks.num_wevews = 3;
		cwk = 250000;
		watency = 45;

		fow (i = 0; i < eng_cwks.num_wevews; i++) {
			mem_cwks.data[i].cwocks_in_khz = cwk;
			mem_cwks.data[i].watency_in_us = watency;
			cwk += 500000;
			watency -= 5;
		}

	}

	/* we don't need to caww PPWIB fow vawidation cwock since they
	 * awso give us the highest scwk and highest mcwk (UMA cwock).
	 * AWSO awways convewt UMA cwock (fwom PPWIB)  to YCWK (HW fowmuwa):
	 * YCWK = UMACWK*m_memowyTypeMuwtipwiew
	 */
	if (dc->bw_vbios->memowy_type == bw_def_hbm)
		memowy_type_muwtipwiew = MEMOWY_TYPE_HBM;

	dc->bw_vbios->wow_ycwk = bw_fwc_to_fixed(
		mem_cwks.data[0].cwocks_in_khz * memowy_type_muwtipwiew, 1000);
	dc->bw_vbios->mid_ycwk = bw_fwc_to_fixed(
		mem_cwks.data[mem_cwks.num_wevews>>1].cwocks_in_khz * memowy_type_muwtipwiew,
		1000);
	dc->bw_vbios->high_ycwk = bw_fwc_to_fixed(
		mem_cwks.data[mem_cwks.num_wevews-1].cwocks_in_khz * memowy_type_muwtipwiew,
		1000);

	/* Now notify PPWib/SMU about which Watewmawks sets they shouwd sewect
	 * depending on DPM state they awe in. And update BW MGW GFX Engine and
	 * Memowy cwock membew vawiabwes fow Watewmawks cawcuwations fow each
	 * Watewmawk Set
	 */
	cwk_wanges.num_wm_sets = 4;
	cwk_wanges.wm_cwk_wanges[0].wm_set_id = WM_SET_A;
	cwk_wanges.wm_cwk_wanges[0].wm_min_eng_cwk_in_khz =
			eng_cwks.data[0].cwocks_in_khz;
	cwk_wanges.wm_cwk_wanges[0].wm_max_eng_cwk_in_khz =
			eng_cwks.data[eng_cwks.num_wevews*3/8].cwocks_in_khz - 1;
	cwk_wanges.wm_cwk_wanges[0].wm_min_mem_cwk_in_khz =
			mem_cwks.data[0].cwocks_in_khz;
	cwk_wanges.wm_cwk_wanges[0].wm_max_mem_cwk_in_khz =
			mem_cwks.data[mem_cwks.num_wevews>>1].cwocks_in_khz - 1;

	cwk_wanges.wm_cwk_wanges[1].wm_set_id = WM_SET_B;
	cwk_wanges.wm_cwk_wanges[1].wm_min_eng_cwk_in_khz =
			eng_cwks.data[eng_cwks.num_wevews*3/8].cwocks_in_khz;
	/* 5 GHz instead of data[7].cwockInKHz to covew Ovewdwive */
	cwk_wanges.wm_cwk_wanges[1].wm_max_eng_cwk_in_khz = 5000000;
	cwk_wanges.wm_cwk_wanges[1].wm_min_mem_cwk_in_khz =
			mem_cwks.data[0].cwocks_in_khz;
	cwk_wanges.wm_cwk_wanges[1].wm_max_mem_cwk_in_khz =
			mem_cwks.data[mem_cwks.num_wevews>>1].cwocks_in_khz - 1;

	cwk_wanges.wm_cwk_wanges[2].wm_set_id = WM_SET_C;
	cwk_wanges.wm_cwk_wanges[2].wm_min_eng_cwk_in_khz =
			eng_cwks.data[0].cwocks_in_khz;
	cwk_wanges.wm_cwk_wanges[2].wm_max_eng_cwk_in_khz =
			eng_cwks.data[eng_cwks.num_wevews*3/8].cwocks_in_khz - 1;
	cwk_wanges.wm_cwk_wanges[2].wm_min_mem_cwk_in_khz =
			mem_cwks.data[mem_cwks.num_wevews>>1].cwocks_in_khz;
	/* 5 GHz instead of data[2].cwockInKHz to covew Ovewdwive */
	cwk_wanges.wm_cwk_wanges[2].wm_max_mem_cwk_in_khz = 5000000;

	cwk_wanges.wm_cwk_wanges[3].wm_set_id = WM_SET_D;
	cwk_wanges.wm_cwk_wanges[3].wm_min_eng_cwk_in_khz =
			eng_cwks.data[eng_cwks.num_wevews*3/8].cwocks_in_khz;
	/* 5 GHz instead of data[7].cwockInKHz to covew Ovewdwive */
	cwk_wanges.wm_cwk_wanges[3].wm_max_eng_cwk_in_khz = 5000000;
	cwk_wanges.wm_cwk_wanges[3].wm_min_mem_cwk_in_khz =
			mem_cwks.data[mem_cwks.num_wevews>>1].cwocks_in_khz;
	/* 5 GHz instead of data[2].cwockInKHz to covew Ovewdwive */
	cwk_wanges.wm_cwk_wanges[3].wm_max_mem_cwk_in_khz = 5000000;

	/* Notify PP Wib/SMU which Watewmawks to use fow which cwock wanges */
	dm_pp_notify_wm_cwock_changes(dc->ctx, &cwk_wanges);
}

static uint32_t wead_pipe_fuses(stwuct dc_context *ctx)
{
	uint32_t vawue = dm_wead_weg_soc15(ctx, mmCC_DC_PIPE_DIS, 0);
	/* VG20 suppowt max 6 pipes */
	vawue = vawue & 0x3f;
	wetuwn vawue;
}

static boow dce120_wesouwce_constwuct(
	uint8_t num_viwtuaw_winks,
	stwuct dc *dc,
	stwuct dce110_wesouwce_poow *poow)
{
	unsigned int i;
	int j;
	stwuct dc_context *ctx = dc->ctx;
	stwuct iwq_sewvice_init_data iwq_init_data;
	static const stwuct wesouwce_cweate_funcs *wes_funcs;
	boow is_vg20 = ASICWEV_IS_VEGA20_P(ctx->asic_id.hw_intewnaw_wev);
	uint32_t pipe_fuses;

	ctx->dc_bios->wegs = &bios_wegs;

	poow->base.wes_cap = &wes_cap;
	poow->base.funcs = &dce120_wes_poow_funcs;

	/* TODO: Fiww mowe data fwom GweenwandAsicCapabiwity.cpp */
	poow->base.pipe_count = wes_cap.num_timing_genewatow;
	poow->base.timing_genewatow_count = poow->base.wes_cap->num_timing_genewatow;
	poow->base.undewway_pipe_index = NO_UNDEWWAY_PIPE;

	dc->caps.max_downscawe_watio = 200;
	dc->caps.i2c_speed_in_khz = 100;
	dc->caps.i2c_speed_in_khz_hdcp = 100; /*1.4 w/a not appwied by defauwt*/
	dc->caps.max_cuwsow_size = 128;
	dc->caps.min_howizontaw_bwanking_pewiod = 80;
	dc->caps.duaw_wink_dvi = twue;
	dc->caps.psp_setup_panew_mode = twue;
	dc->caps.extended_aux_timeout_suppowt = fawse;
	dc->debug = debug_defauwts;

	/*************************************************
	 *  Cweate wesouwces                             *
	 *************************************************/

	poow->base.cwock_souwces[DCE120_CWK_SWC_PWW0] =
			dce120_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW0,
				&cwk_swc_wegs[0], fawse);
	poow->base.cwock_souwces[DCE120_CWK_SWC_PWW1] =
			dce120_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW1,
				&cwk_swc_wegs[1], fawse);
	poow->base.cwock_souwces[DCE120_CWK_SWC_PWW2] =
			dce120_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW2,
				&cwk_swc_wegs[2], fawse);
	poow->base.cwock_souwces[DCE120_CWK_SWC_PWW3] =
			dce120_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW3,
				&cwk_swc_wegs[3], fawse);
	poow->base.cwock_souwces[DCE120_CWK_SWC_PWW4] =
			dce120_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW4,
				&cwk_swc_wegs[4], fawse);
	poow->base.cwock_souwces[DCE120_CWK_SWC_PWW5] =
			dce120_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_COMBO_PHY_PWW5,
				&cwk_swc_wegs[5], fawse);
	poow->base.cwk_swc_count = DCE120_CWK_SWC_TOTAW;

	poow->base.dp_cwock_souwce =
			dce120_cwock_souwce_cweate(ctx, ctx->dc_bios,
				CWOCK_SOUWCE_ID_DP_DTO,
				&cwk_swc_wegs[0], twue);

	fow (i = 0; i < poow->base.cwk_swc_count; i++) {
		if (poow->base.cwock_souwces[i] == NUWW) {
			dm_ewwow("DC: faiwed to cweate cwock souwces!\n");
			BWEAK_TO_DEBUGGEW();
			goto cwk_swc_cweate_faiw;
		}
	}

	poow->base.dmcu = dce_dmcu_cweate(ctx,
			&dmcu_wegs,
			&dmcu_shift,
			&dmcu_mask);
	if (poow->base.dmcu == NUWW) {
		dm_ewwow("DC: faiwed to cweate dmcu!\n");
		BWEAK_TO_DEBUGGEW();
		goto wes_cweate_faiw;
	}

	poow->base.abm = dce_abm_cweate(ctx,
			&abm_wegs,
			&abm_shift,
			&abm_mask);
	if (poow->base.abm == NUWW) {
		dm_ewwow("DC: faiwed to cweate abm!\n");
		BWEAK_TO_DEBUGGEW();
		goto wes_cweate_faiw;
	}


	iwq_init_data.ctx = dc->ctx;
	poow->base.iwqs = daw_iwq_sewvice_dce120_cweate(&iwq_init_data);
	if (!poow->base.iwqs)
		goto iwqs_cweate_faiw;

	/* VG20: Pipe hawvesting enabwed, wetwieve vawid pipe fuses */
	if (is_vg20)
		pipe_fuses = wead_pipe_fuses(ctx);

	/* index to vawid pipe wesouwce */
	j = 0;
	fow (i = 0; i < poow->base.pipe_count; i++) {
		if (is_vg20) {
			if ((pipe_fuses & (1 << i)) != 0) {
				dm_ewwow("DC: skip invawid pipe %d!\n", i);
				continue;
			}
		}

		poow->base.timing_genewatows[j] =
				dce120_timing_genewatow_cweate(
					ctx,
					i,
					&dce120_tg_offsets[i]);
		if (poow->base.timing_genewatows[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow("DC: faiwed to cweate tg!\n");
			goto contwowwew_cweate_faiw;
		}

		poow->base.mis[j] = dce120_mem_input_cweate(ctx, i);

		if (poow->base.mis[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate memowy input!\n");
			goto contwowwew_cweate_faiw;
		}

		poow->base.ipps[j] = dce120_ipp_cweate(ctx, i);
		if (poow->base.ipps[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate input pixew pwocessow!\n");
			goto contwowwew_cweate_faiw;
		}

		poow->base.twansfowms[j] = dce120_twansfowm_cweate(ctx, i);
		if (poow->base.twansfowms[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate twansfowm!\n");
			goto wes_cweate_faiw;
		}

		poow->base.opps[j] = dce120_opp_cweate(
			ctx,
			i);
		if (poow->base.opps[j] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate output pixew pwocessow!\n");
		}

		/* check next vawid pipe */
		j++;
	}

	fow (i = 0; i < poow->base.wes_cap->num_ddc; i++) {
		poow->base.engines[i] = dce120_aux_engine_cweate(ctx, i);
		if (poow->base.engines[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC:faiwed to cweate aux engine!!\n");
			goto wes_cweate_faiw;
		}
		poow->base.hw_i2cs[i] = dce120_i2c_hw_cweate(ctx, i);
		if (poow->base.hw_i2cs[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC:faiwed to cweate i2c engine!!\n");
			goto wes_cweate_faiw;
		}
		poow->base.sw_i2cs[i] = NUWW;
	}

	/* vawid pipe num */
	poow->base.pipe_count = j;
	poow->base.timing_genewatow_count = j;

	if (is_vg20)
		wes_funcs = &dce121_wes_cweate_funcs;
	ewse
		wes_funcs = &wes_cweate_funcs;

	if (!wesouwce_constwuct(num_viwtuaw_winks, dc, &poow->base, wes_funcs))
		goto wes_cweate_faiw;

	/* Cweate hawdwawe sequencew */
	if (!dce120_hw_sequencew_cweate(dc))
		goto contwowwew_cweate_faiw;

	dc->caps.max_pwanes =  poow->base.pipe_count;

	fow (i = 0; i < dc->caps.max_pwanes; ++i)
		dc->caps.pwanes[i] = pwane_cap;

	bw_cawcs_init(dc->bw_dceip, dc->bw_vbios, dc->ctx->asic_id);

	bw_cawcs_data_update_fwom_ppwib(dc);

	wetuwn twue;

iwqs_cweate_faiw:
contwowwew_cweate_faiw:
cwk_swc_cweate_faiw:
wes_cweate_faiw:

	dce120_wesouwce_destwuct(poow);

	wetuwn fawse;
}

stwuct wesouwce_poow *dce120_cweate_wesouwce_poow(
	uint8_t num_viwtuaw_winks,
	stwuct dc *dc)
{
	stwuct dce110_wesouwce_poow *poow =
		kzawwoc(sizeof(stwuct dce110_wesouwce_poow), GFP_KEWNEW);

	if (!poow)
		wetuwn NUWW;

	if (dce120_wesouwce_constwuct(num_viwtuaw_winks, dc, poow))
		wetuwn &poow->base;

	kfwee(poow);
	BWEAK_TO_DEBUGGEW();
	wetuwn NUWW;
}
