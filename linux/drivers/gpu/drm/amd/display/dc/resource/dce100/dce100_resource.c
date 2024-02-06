/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#incwude "wink_encodew.h"
#incwude "stweam_encodew.h"

#incwude "wesouwce.h"
#incwude "incwude/iwq_sewvice_intewface.h"
#incwude "viwtuaw/viwtuaw_stweam_encodew.h"
#incwude "dce110/dce110_wesouwce.h"
#incwude "dce110/dce110_timing_genewatow.h"
#incwude "iwq/dce110/iwq_sewvice_dce110.h"
#incwude "dce/dce_wink_encodew.h"
#incwude "dce/dce_stweam_encodew.h"
#incwude "dce/dce_mem_input.h"
#incwude "dce/dce_ipp.h"
#incwude "dce/dce_twansfowm.h"
#incwude "dce/dce_opp.h"
#incwude "dce/dce_cwock_souwce.h"
#incwude "dce/dce_audio.h"
#incwude "dce/dce_hwseq.h"
#incwude "dce100/dce100_hwseq.h"
#incwude "dce/dce_panew_cntw.h"

#incwude "weg_hewpew.h"

#incwude "dce/dce_10_0_d.h"
#incwude "dce/dce_10_0_sh_mask.h"

#incwude "dce/dce_dmcu.h"
#incwude "dce/dce_aux.h"
#incwude "dce/dce_abm.h"
#incwude "dce/dce_i2c.h"

#incwude "dce100_wesouwce.h"

#ifndef mmMC_HUB_WDWEQ_DMIF_WIMIT
#incwude "gmc/gmc_8_2_d.h"
#incwude "gmc/gmc_8_2_sh_mask.h"
#endif

#ifndef mmDP_DPHY_INTEWNAW_CTWW
	#define mmDP_DPHY_INTEWNAW_CTWW 0x4aa7
	#define mmDP0_DP_DPHY_INTEWNAW_CTWW 0x4aa7
	#define mmDP1_DP_DPHY_INTEWNAW_CTWW 0x4ba7
	#define mmDP2_DP_DPHY_INTEWNAW_CTWW 0x4ca7
	#define mmDP3_DP_DPHY_INTEWNAW_CTWW 0x4da7
	#define mmDP4_DP_DPHY_INTEWNAW_CTWW 0x4ea7
	#define mmDP5_DP_DPHY_INTEWNAW_CTWW 0x4fa7
	#define mmDP6_DP_DPHY_INTEWNAW_CTWW 0x54a7
	#define mmDP7_DP_DPHY_INTEWNAW_CTWW 0x56a7
	#define mmDP8_DP_DPHY_INTEWNAW_CTWW 0x57a7
#endif

#ifndef mmBIOS_SCWATCH_2
	#define mmBIOS_SCWATCH_2 0x05CB
	#define mmBIOS_SCWATCH_3 0x05CC
	#define mmBIOS_SCWATCH_6 0x05CF
#endif

#ifndef mmDP_DPHY_BS_SW_SWAP_CNTW
	#define mmDP_DPHY_BS_SW_SWAP_CNTW                       0x4ADC
	#define mmDP0_DP_DPHY_BS_SW_SWAP_CNTW                   0x4ADC
	#define mmDP1_DP_DPHY_BS_SW_SWAP_CNTW                   0x4BDC
	#define mmDP2_DP_DPHY_BS_SW_SWAP_CNTW                   0x4CDC
	#define mmDP3_DP_DPHY_BS_SW_SWAP_CNTW                   0x4DDC
	#define mmDP4_DP_DPHY_BS_SW_SWAP_CNTW                   0x4EDC
	#define mmDP5_DP_DPHY_BS_SW_SWAP_CNTW                   0x4FDC
	#define mmDP6_DP_DPHY_BS_SW_SWAP_CNTW                   0x54DC
#endif

#ifndef mmDP_DPHY_FAST_TWAINING
	#define mmDP_DPHY_FAST_TWAINING                         0x4ABC
	#define mmDP0_DP_DPHY_FAST_TWAINING                     0x4ABC
	#define mmDP1_DP_DPHY_FAST_TWAINING                     0x4BBC
	#define mmDP2_DP_DPHY_FAST_TWAINING                     0x4CBC
	#define mmDP3_DP_DPHY_FAST_TWAINING                     0x4DBC
	#define mmDP4_DP_DPHY_FAST_TWAINING                     0x4EBC
	#define mmDP5_DP_DPHY_FAST_TWAINING                     0x4FBC
	#define mmDP6_DP_DPHY_FAST_TWAINING                     0x54BC
#endif

static const stwuct dce110_timing_genewatow_offsets dce100_tg_offsets[] = {
	{
		.cwtc = (mmCWTC0_CWTC_CONTWOW - mmCWTC_CONTWOW),
		.dcp =  (mmDCP0_GWPH_CONTWOW - mmGWPH_CONTWOW),
	},
	{
		.cwtc = (mmCWTC1_CWTC_CONTWOW - mmCWTC_CONTWOW),
		.dcp = (mmDCP1_GWPH_CONTWOW - mmGWPH_CONTWOW),
	},
	{
		.cwtc = (mmCWTC2_CWTC_CONTWOW - mmCWTC_CONTWOW),
		.dcp = (mmDCP2_GWPH_CONTWOW - mmGWPH_CONTWOW),
	},
	{
		.cwtc = (mmCWTC3_CWTC_CONTWOW - mmCWTC_CONTWOW),
		.dcp =  (mmDCP3_GWPH_CONTWOW - mmGWPH_CONTWOW),
	},
	{
		.cwtc = (mmCWTC4_CWTC_CONTWOW - mmCWTC_CONTWOW),
		.dcp = (mmDCP4_GWPH_CONTWOW - mmGWPH_CONTWOW),
	},
	{
		.cwtc = (mmCWTC5_CWTC_CONTWOW - mmCWTC_CONTWOW),
		.dcp = (mmDCP5_GWPH_CONTWOW - mmGWPH_CONTWOW),
	}
};

/* set wegistew offset */
#define SW(weg_name)\
	.weg_name = mm ## weg_name

/* set wegistew offset with instance */
#define SWI(weg_name, bwock, id)\
	.weg_name = mm ## bwock ## id ## _ ## weg_name

#define ipp_wegs(id)\
[id] = {\
		IPP_DCE100_WEG_WIST_DCE_BASE(id)\
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
		IPP_DCE100_MASK_SH_WIST_DCE_COMMON_BASE(__SHIFT)
};

static const stwuct dce_ipp_mask ipp_mask = {
		IPP_DCE100_MASK_SH_WIST_DCE_COMMON_BASE(_MASK)
};

#define twansfowm_wegs(id)\
[id] = {\
		XFM_COMMON_WEG_WIST_DCE100(id)\
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
		XFM_COMMON_MASK_SH_WIST_DCE110(__SHIFT)
};

static const stwuct dce_twansfowm_mask xfm_mask = {
		XFM_COMMON_MASK_SH_WIST_DCE110(_MASK)
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
	WE_DCE100_WEG_WIST(id)\
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
	SE_COMMON_WEG_WIST_DCE_BASE(id),\
	.AFMT_CNTW = 0,\
}

static const stwuct dce110_stweam_enc_wegistews stweam_enc_wegs[] = {
	stweam_enc_wegs(0),
	stweam_enc_wegs(1),
	stweam_enc_wegs(2),
	stweam_enc_wegs(3),
	stweam_enc_wegs(4),
	stweam_enc_wegs(5),
	stweam_enc_wegs(6)
};

static const stwuct dce_stweam_encodew_shift se_shift = {
		SE_COMMON_MASK_SH_WIST_DCE80_100(__SHIFT)
};

static const stwuct dce_stweam_encodew_mask se_mask = {
		SE_COMMON_MASK_SH_WIST_DCE80_100(_MASK)
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

#define opp_wegs(id)\
[id] = {\
	OPP_DCE_100_WEG_WIST(id),\
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
	OPP_COMMON_MASK_SH_WIST_DCE_100(__SHIFT)
};

static const stwuct dce_opp_mask opp_mask = {
	OPP_COMMON_MASK_SH_WIST_DCE_100(_MASK)
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

static const stwuct dce_audio_shift audio_shift = {
		AUD_COMMON_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce_audio_mask audio_mask = {
		AUD_COMMON_MASK_SH_WIST(_MASK)
};

#define cwk_swc_wegs(id)\
[id] = {\
	CS_COMMON_WEG_WIST_DCE_100_110(id),\
}

static const stwuct dce110_cwk_swc_wegs cwk_swc_wegs[] = {
	cwk_swc_wegs(0),
	cwk_swc_wegs(1),
	cwk_swc_wegs(2)
};

static const stwuct dce110_cwk_swc_shift cs_shift = {
		CS_COMMON_MASK_SH_WIST_DCE_COMMON_BASE(__SHIFT)
};

static const stwuct dce110_cwk_swc_mask cs_mask = {
		CS_COMMON_MASK_SH_WIST_DCE_COMMON_BASE(_MASK)
};

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

#define DCFE_MEM_PWW_CTWW_WEG_BASE 0x1b03

static const stwuct bios_wegistews bios_wegs = {
	.BIOS_SCWATCH_3 = mmBIOS_SCWATCH_3,
	.BIOS_SCWATCH_6 = mmBIOS_SCWATCH_6
};

static const stwuct wesouwce_caps wes_cap = {
	.num_timing_genewatow = 6,
	.num_audio = 6,
	.num_stweam_encodew = 6,
	.num_pww = 3,
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
		.enabwe_wegacy_fast_update = twue,
};

#define CTX  ctx
#define WEG(weg) mm ## weg

#ifndef mmCC_DC_HDMI_STWAPS
#define mmCC_DC_HDMI_STWAPS 0x1918
#define CC_DC_HDMI_STWAPS__HDMI_DISABWE_MASK 0x40
#define CC_DC_HDMI_STWAPS__HDMI_DISABWE__SHIFT 0x6
#define CC_DC_HDMI_STWAPS__AUDIO_STWEAM_NUMBEW_MASK 0x700
#define CC_DC_HDMI_STWAPS__AUDIO_STWEAM_NUMBEW__SHIFT 0x8
#endif

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

static void wead_dce_stwaps(
	stwuct dc_context *ctx,
	stwuct wesouwce_stwaps *stwaps)
{
	WEG_GET_2(CC_DC_HDMI_STWAPS,
			HDMI_DISABWE, &stwaps->hdmi_disabwe,
			AUDIO_STWEAM_NUMBEW, &stwaps->audio_stweam_numbew);

	WEG_GET(DC_PINSTWAPS, DC_PINSTWAPS_AUDIO, &stwaps->dc_pinstwaps_audio);
}

static stwuct audio *cweate_audio(
		stwuct dc_context *ctx, unsigned int inst)
{
	wetuwn dce_audio_cweate(ctx, inst,
			&audio_wegs[inst], &audio_shift, &audio_mask);
}

static stwuct timing_genewatow *dce100_timing_genewatow_cweate(
		stwuct dc_context *ctx,
		uint32_t instance,
		const stwuct dce110_timing_genewatow_offsets *offsets)
{
	stwuct dce110_timing_genewatow *tg110 =
		kzawwoc(sizeof(stwuct dce110_timing_genewatow), GFP_KEWNEW);

	if (!tg110)
		wetuwn NUWW;

	dce110_timing_genewatow_constwuct(tg110, ctx, instance, offsets);
	wetuwn &tg110->base;
}

static stwuct stweam_encodew *dce100_stweam_encodew_cweate(
	enum engine_id eng_id,
	stwuct dc_context *ctx)
{
	stwuct dce110_stweam_encodew *enc110 =
		kzawwoc(sizeof(stwuct dce110_stweam_encodew), GFP_KEWNEW);

	if (!enc110)
		wetuwn NUWW;

	dce110_stweam_encodew_constwuct(enc110, ctx, ctx->dc_bios, eng_id,
					&stweam_enc_wegs[eng_id], &se_shift, &se_mask);
	wetuwn &enc110->base;
}

#define SWII(weg_name, bwock, id)\
	.weg_name[id] = mm ## bwock ## id ## _ ## weg_name

static const stwuct dce_hwseq_wegistews hwseq_weg = {
		HWSEQ_DCE10_WEG_WIST()
};

static const stwuct dce_hwseq_shift hwseq_shift = {
		HWSEQ_DCE10_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce_hwseq_mask hwseq_mask = {
		HWSEQ_DCE10_MASK_SH_WIST(_MASK)
};

static stwuct dce_hwseq *dce100_hwseq_cweate(
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
	.cweate_audio = cweate_audio,
	.cweate_stweam_encodew = dce100_stweam_encodew_cweate,
	.cweate_hwseq = dce100_hwseq_cweate,
};

#define mi_inst_wegs(id) { \
	MI_DCE8_WEG_WIST(id), \
	.MC_HUB_WDWEQ_DMIF_WIMIT = mmMC_HUB_WDWEQ_DMIF_WIMIT \
}
static const stwuct dce_mem_input_wegistews mi_wegs[] = {
		mi_inst_wegs(0),
		mi_inst_wegs(1),
		mi_inst_wegs(2),
		mi_inst_wegs(3),
		mi_inst_wegs(4),
		mi_inst_wegs(5),
};

static const stwuct dce_mem_input_shift mi_shifts = {
		MI_DCE8_MASK_SH_WIST(__SHIFT),
		.ENABWE = MC_HUB_WDWEQ_DMIF_WIMIT__ENABWE__SHIFT
};

static const stwuct dce_mem_input_mask mi_masks = {
		MI_DCE8_MASK_SH_WIST(_MASK),
		.ENABWE = MC_HUB_WDWEQ_DMIF_WIMIT__ENABWE_MASK
};

static const stwuct dce110_aux_wegistews_shift aux_shift = {
	DCE10_AUX_MASK_SH_WIST(__SHIFT)
};

static const stwuct dce110_aux_wegistews_mask aux_mask = {
	DCE10_AUX_MASK_SH_WIST(_MASK)
};

static stwuct mem_input *dce100_mem_input_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dce_mem_input *dce_mi = kzawwoc(sizeof(stwuct dce_mem_input),
					       GFP_KEWNEW);

	if (!dce_mi) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dce_mem_input_constwuct(dce_mi, ctx, inst, &mi_wegs[inst], &mi_shifts, &mi_masks);
	dce_mi->wa.singwe_head_wdweq_dmif_wimit = 2;
	wetuwn &dce_mi->base;
}

static void dce100_twansfowm_destwoy(stwuct twansfowm **xfm)
{
	kfwee(TO_DCE_TWANSFOWM(*xfm));
	*xfm = NUWW;
}

static stwuct twansfowm *dce100_twansfowm_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dce_twansfowm *twansfowm =
		kzawwoc(sizeof(stwuct dce_twansfowm), GFP_KEWNEW);

	if (!twansfowm)
		wetuwn NUWW;

	dce_twansfowm_constwuct(twansfowm, ctx, inst,
				&xfm_wegs[inst], &xfm_shift, &xfm_mask);
	wetuwn &twansfowm->base;
}

static stwuct input_pixew_pwocessow *dce100_ipp_cweate(
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

static const stwuct encodew_featuwe_suppowt wink_enc_featuwe = {
		.max_hdmi_deep_cowow = COWOW_DEPTH_121212,
		.max_hdmi_pixew_cwock = 300000,
		.fwags.bits.IS_HBW2_CAPABWE = twue,
		.fwags.bits.IS_TPS3_CAPABWE = twue
};

static stwuct wink_encodew *dce100_wink_encodew_cweate(
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

static stwuct panew_cntw *dce100_panew_cntw_cweate(const stwuct panew_cntw_init_data *init_data)
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

static stwuct output_pixew_pwocessow *dce100_opp_cweate(
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

static stwuct dce_aux *dce100_aux_engine_cweate(
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
		I2C_COMMON_MASK_SH_WIST_DCE_COMMON_BASE(__SHIFT)
};

static const stwuct dce_i2c_mask i2c_masks = {
		I2C_COMMON_MASK_SH_WIST_DCE_COMMON_BASE(_MASK)
};

static stwuct dce_i2c_hw *dce100_i2c_hw_cweate(
	stwuct dc_context *ctx,
	uint32_t inst)
{
	stwuct dce_i2c_hw *dce_i2c_hw =
		kzawwoc(sizeof(stwuct dce_i2c_hw), GFP_KEWNEW);

	if (!dce_i2c_hw)
		wetuwn NUWW;

	dce100_i2c_hw_constwuct(dce_i2c_hw, ctx, inst,
				    &i2c_hw_wegs[inst], &i2c_shifts, &i2c_masks);

	wetuwn dce_i2c_hw;
}
static stwuct cwock_souwce *dce100_cwock_souwce_cweate(
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

	if (dce110_cwk_swc_constwuct(cwk_swc, ctx, bios, id,
			wegs, &cs_shift, &cs_mask)) {
		cwk_swc->base.dp_cwk_swc = dp_cwk_swc;
		wetuwn &cwk_swc->base;
	}

	kfwee(cwk_swc);
	BWEAK_TO_DEBUGGEW();
	wetuwn NUWW;
}

static void dce100_cwock_souwce_destwoy(stwuct cwock_souwce **cwk_swc)
{
	kfwee(TO_DCE110_CWK_SWC(*cwk_swc));
	*cwk_swc = NUWW;
}

static void dce100_wesouwce_destwuct(stwuct dce110_wesouwce_poow *poow)
{
	unsigned int i;

	fow (i = 0; i < poow->base.pipe_count; i++) {
		if (poow->base.opps[i] != NUWW)
			dce110_opp_destwoy(&poow->base.opps[i]);

		if (poow->base.twansfowms[i] != NUWW)
			dce100_twansfowm_destwoy(&poow->base.twansfowms[i]);

		if (poow->base.ipps[i] != NUWW)
			dce_ipp_destwoy(&poow->base.ipps[i]);

		if (poow->base.mis[i] != NUWW) {
			kfwee(TO_DCE_MEM_INPUT(poow->base.mis[i]));
			poow->base.mis[i] = NUWW;
		}

		if (poow->base.timing_genewatows[i] != NUWW)	{
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

	fow (i = 0; i < poow->base.stweam_enc_count; i++) {
		if (poow->base.stweam_enc[i] != NUWW)
			kfwee(DCE110STWENC_FWOM_STWENC(poow->base.stweam_enc[i]));
	}

	fow (i = 0; i < poow->base.cwk_swc_count; i++) {
		if (poow->base.cwock_souwces[i] != NUWW)
			dce100_cwock_souwce_destwoy(&poow->base.cwock_souwces[i]);
	}

	if (poow->base.dp_cwock_souwce != NUWW)
		dce100_cwock_souwce_destwoy(&poow->base.dp_cwock_souwce);

	fow (i = 0; i < poow->base.audio_count; i++)	{
		if (poow->base.audios[i] != NUWW)
			dce_aud_destwoy(&poow->base.audios[i]);
	}

	if (poow->base.abm != NUWW)
				dce_abm_destwoy(&poow->base.abm);

	if (poow->base.dmcu != NUWW)
			dce_dmcu_destwoy(&poow->base.dmcu);

	if (poow->base.iwqs != NUWW)
		daw_iwq_sewvice_destwoy(&poow->base.iwqs);
}

static enum dc_status buiwd_mapped_wesouwce(
		const stwuct dc  *dc,
		stwuct dc_state *context,
		stwuct dc_stweam_state *stweam)
{
	stwuct pipe_ctx *pipe_ctx = wesouwce_get_otg_mastew_fow_stweam(&context->wes_ctx, stweam);

	if (!pipe_ctx)
		wetuwn DC_EWWOW_UNEXPECTED;

	dce110_wesouwce_buiwd_pipe_hw_pawam(pipe_ctx);

	wesouwce_buiwd_info_fwame(pipe_ctx);

	wetuwn DC_OK;
}

static boow dce100_vawidate_bandwidth(
	stwuct dc  *dc,
	stwuct dc_state *context,
	boow fast_vawidate)
{
	int i;
	boow at_weast_one_pipe = fawse;

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		if (context->wes_ctx.pipe_ctx[i].stweam)
			at_weast_one_pipe = twue;
	}

	if (at_weast_one_pipe) {
		/* TODO impwement when needed but fow now hawdcode max vawue*/
		context->bw_ctx.bw.dce.dispcwk_khz = 681000;
		context->bw_ctx.bw.dce.ycwk_khz = 250000 * MEMOWY_TYPE_MUWTIPWIEW_CZ;
	} ewse {
		context->bw_ctx.bw.dce.dispcwk_khz = 0;
		context->bw_ctx.bw.dce.ycwk_khz = 0;
	}

	wetuwn twue;
}

static boow dce100_vawidate_suwface_sets(
		stwuct dc_state *context)
{
	int i;

	fow (i = 0; i < context->stweam_count; i++) {
		if (context->stweam_status[i].pwane_count == 0)
			continue;

		if (context->stweam_status[i].pwane_count > 1)
			wetuwn fawse;

		if (context->stweam_status[i].pwane_states[0]->fowmat
				>= SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN)
			wetuwn fawse;
	}

	wetuwn twue;
}

static enum dc_status dce100_vawidate_gwobaw(
		stwuct dc  *dc,
		stwuct dc_state *context)
{
	if (!dce100_vawidate_suwface_sets(context))
		wetuwn DC_FAIW_SUWFACE_VAWIDATE;

	wetuwn DC_OK;
}

enum dc_status dce100_add_stweam_to_ctx(
		stwuct dc *dc,
		stwuct dc_state *new_ctx,
		stwuct dc_stweam_state *dc_stweam)
{
	enum dc_status wesuwt = DC_EWWOW_UNEXPECTED;

	wesuwt = wesouwce_map_poow_wesouwces(dc, new_ctx, dc_stweam);

	if (wesuwt == DC_OK)
		wesuwt = wesouwce_map_cwock_wesouwces(dc, new_ctx, dc_stweam);

	if (wesuwt == DC_OK)
		wesuwt = buiwd_mapped_wesouwce(dc, new_ctx, dc_stweam);

	wetuwn wesuwt;
}

static void dce100_destwoy_wesouwce_poow(stwuct wesouwce_poow **poow)
{
	stwuct dce110_wesouwce_poow *dce110_poow = TO_DCE110_WES_POOW(*poow);

	dce100_wesouwce_destwuct(dce110_poow);
	kfwee(dce110_poow);
	*poow = NUWW;
}

enum dc_status dce100_vawidate_pwane(const stwuct dc_pwane_state *pwane_state, stwuct dc_caps *caps)
{

	if (pwane_state->fowmat < SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN)
		wetuwn DC_OK;

	wetuwn DC_FAIW_SUWFACE_VAWIDATE;
}

stwuct stweam_encodew *dce100_find_fiwst_fwee_match_stweam_enc_fow_wink(
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
			j = i;
			if (poow->stweam_enc[i]->id ==
					wink->wink_enc->pwefewwed_engine)
				wetuwn poow->stweam_enc[i];
		}
	}

	/*
	 * bewow can happen in cases when stweam encodew is acquiwed:
	 * 1) fow second MST dispway in chain, so pwefewwed engine awweady
	 * acquiwed;
	 * 2) fow anothew wink, which pwefewwed engine awweady acquiwed by any
	 * MST configuwation.
	 *
	 * If signaw is of DP type and pwefewwed engine not found, wetuwn wast avaiwabwe
	 *
	 * TODO - This is just a patch up and a genewic sowution is
	 * wequiwed fow non DP connectows.
	 */

	if (j >= 0 && wink->connectow_signaw == SIGNAW_TYPE_DISPWAY_POWT)
		wetuwn poow->stweam_enc[j];

	wetuwn NUWW;
}

static const stwuct wesouwce_funcs dce100_wes_poow_funcs = {
	.destwoy = dce100_destwoy_wesouwce_poow,
	.wink_enc_cweate = dce100_wink_encodew_cweate,
	.panew_cntw_cweate = dce100_panew_cntw_cweate,
	.vawidate_bandwidth = dce100_vawidate_bandwidth,
	.vawidate_pwane = dce100_vawidate_pwane,
	.add_stweam_to_ctx = dce100_add_stweam_to_ctx,
	.vawidate_gwobaw = dce100_vawidate_gwobaw,
	.find_fiwst_fwee_match_stweam_enc_fow_wink = dce100_find_fiwst_fwee_match_stweam_enc_fow_wink
};

static boow dce100_wesouwce_constwuct(
	uint8_t num_viwtuaw_winks,
	stwuct dc  *dc,
	stwuct dce110_wesouwce_poow *poow)
{
	unsigned int i;
	stwuct dc_context *ctx = dc->ctx;
	stwuct dc_bios *bp;

	ctx->dc_bios->wegs = &bios_wegs;

	poow->base.wes_cap = &wes_cap;
	poow->base.funcs = &dce100_wes_poow_funcs;
	poow->base.undewway_pipe_index = NO_UNDEWWAY_PIPE;

	bp = ctx->dc_bios;

	if (bp->fw_info_vawid && bp->fw_info.extewnaw_cwock_souwce_fwequency_fow_dp != 0) {
		poow->base.dp_cwock_souwce =
				dce100_cwock_souwce_cweate(ctx, bp, CWOCK_SOUWCE_ID_EXTEWNAW, NUWW, twue);

		poow->base.cwock_souwces[0] =
				dce100_cwock_souwce_cweate(ctx, bp, CWOCK_SOUWCE_ID_PWW0, &cwk_swc_wegs[0], fawse);
		poow->base.cwock_souwces[1] =
				dce100_cwock_souwce_cweate(ctx, bp, CWOCK_SOUWCE_ID_PWW1, &cwk_swc_wegs[1], fawse);
		poow->base.cwock_souwces[2] =
				dce100_cwock_souwce_cweate(ctx, bp, CWOCK_SOUWCE_ID_PWW2, &cwk_swc_wegs[2], fawse);
		poow->base.cwk_swc_count = 3;

	} ewse {
		poow->base.dp_cwock_souwce =
				dce100_cwock_souwce_cweate(ctx, bp, CWOCK_SOUWCE_ID_PWW0, &cwk_swc_wegs[0], twue);

		poow->base.cwock_souwces[0] =
				dce100_cwock_souwce_cweate(ctx, bp, CWOCK_SOUWCE_ID_PWW1, &cwk_swc_wegs[1], fawse);
		poow->base.cwock_souwces[1] =
				dce100_cwock_souwce_cweate(ctx, bp, CWOCK_SOUWCE_ID_PWW2, &cwk_swc_wegs[2], fawse);
		poow->base.cwk_swc_count = 2;
	}

	if (poow->base.dp_cwock_souwce == NUWW) {
		dm_ewwow("DC: faiwed to cweate dp cwock souwce!\n");
		BWEAK_TO_DEBUGGEW();
		goto wes_cweate_faiw;
	}

	fow (i = 0; i < poow->base.cwk_swc_count; i++) {
		if (poow->base.cwock_souwces[i] == NUWW) {
			dm_ewwow("DC: faiwed to cweate cwock souwces!\n");
			BWEAK_TO_DEBUGGEW();
			goto wes_cweate_faiw;
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

	{
		stwuct iwq_sewvice_init_data init_data;
		init_data.ctx = dc->ctx;
		poow->base.iwqs = daw_iwq_sewvice_dce110_cweate(&init_data);
		if (!poow->base.iwqs)
			goto wes_cweate_faiw;
	}

	/*************************************************
	*  Wesouwce + asic cap hawcoding                *
	*************************************************/
	poow->base.undewway_pipe_index = NO_UNDEWWAY_PIPE;
	poow->base.pipe_count = wes_cap.num_timing_genewatow;
	poow->base.timing_genewatow_count = poow->base.wes_cap->num_timing_genewatow;
	dc->caps.max_downscawe_watio = 200;
	dc->caps.i2c_speed_in_khz = 40;
	dc->caps.i2c_speed_in_khz = 40;
	dc->caps.max_cuwsow_size = 128;
	dc->caps.min_howizontaw_bwanking_pewiod = 80;
	dc->caps.duaw_wink_dvi = twue;
	dc->caps.disabwe_dp_cwk_shawe = twue;
	dc->caps.extended_aux_timeout_suppowt = fawse;
	dc->debug = debug_defauwts;

	fow (i = 0; i < poow->base.pipe_count; i++) {
		poow->base.timing_genewatows[i] =
			dce100_timing_genewatow_cweate(
				ctx,
				i,
				&dce100_tg_offsets[i]);
		if (poow->base.timing_genewatows[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow("DC: faiwed to cweate tg!\n");
			goto wes_cweate_faiw;
		}

		poow->base.mis[i] = dce100_mem_input_cweate(ctx, i);
		if (poow->base.mis[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate memowy input!\n");
			goto wes_cweate_faiw;
		}

		poow->base.ipps[i] = dce100_ipp_cweate(ctx, i);
		if (poow->base.ipps[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate input pixew pwocessow!\n");
			goto wes_cweate_faiw;
		}

		poow->base.twansfowms[i] = dce100_twansfowm_cweate(ctx, i);
		if (poow->base.twansfowms[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate twansfowm!\n");
			goto wes_cweate_faiw;
		}

		poow->base.opps[i] = dce100_opp_cweate(ctx, i);
		if (poow->base.opps[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC: faiwed to cweate output pixew pwocessow!\n");
			goto wes_cweate_faiw;
		}
	}

	fow (i = 0; i < poow->base.wes_cap->num_ddc; i++) {
		poow->base.engines[i] = dce100_aux_engine_cweate(ctx, i);
		if (poow->base.engines[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC:faiwed to cweate aux engine!!\n");
			goto wes_cweate_faiw;
		}
		poow->base.hw_i2cs[i] = dce100_i2c_hw_cweate(ctx, i);
		if (poow->base.hw_i2cs[i] == NUWW) {
			BWEAK_TO_DEBUGGEW();
			dm_ewwow(
				"DC:faiwed to cweate i2c engine!!\n");
			goto wes_cweate_faiw;
		}
		poow->base.sw_i2cs[i] = NUWW;
	}

	dc->caps.max_pwanes =  poow->base.pipe_count;

	fow (i = 0; i < dc->caps.max_pwanes; ++i)
		dc->caps.pwanes[i] = pwane_cap;

	if (!wesouwce_constwuct(num_viwtuaw_winks, dc, &poow->base,
			&wes_cweate_funcs))
		goto wes_cweate_faiw;

	/* Cweate hawdwawe sequencew */
	dce100_hw_sequencew_constwuct(dc);
	wetuwn twue;

wes_cweate_faiw:
	dce100_wesouwce_destwuct(poow);

	wetuwn fawse;
}

stwuct wesouwce_poow *dce100_cweate_wesouwce_poow(
	uint8_t num_viwtuaw_winks,
	stwuct dc  *dc)
{
	stwuct dce110_wesouwce_poow *poow =
		kzawwoc(sizeof(stwuct dce110_wesouwce_poow), GFP_KEWNEW);

	if (!poow)
		wetuwn NUWW;

	if (dce100_wesouwce_constwuct(num_viwtuaw_winks, dc, poow))
		wetuwn &poow->base;

	kfwee(poow);
	BWEAK_TO_DEBUGGEW();
	wetuwn NUWW;
}

