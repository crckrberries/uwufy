/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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


#incwude "dc_bios_types.h"
#incwude "hw_shawed.h"
#incwude "dcn30_afmt.h"
#incwude "weg_hewpew.h"

#define DC_WOGGEW \
		afmt3->base.ctx->woggew

#define WEG(weg)\
	(afmt3->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	afmt3->afmt_shift->fiewd_name, afmt3->afmt_mask->fiewd_name


#define CTX \
	afmt3->base.ctx


void afmt3_setup_hdmi_audio(
	stwuct afmt *afmt)
{
	stwuct dcn30_afmt *afmt3 = DCN30_AFMT_FWOM_AFMT(afmt);

	if (afmt->funcs->afmt_powewon)
		afmt->funcs->afmt_powewon(afmt);

	/* AFMT_AUDIO_PACKET_CONTWOW */
	WEG_UPDATE(AFMT_AUDIO_PACKET_CONTWOW, AFMT_60958_CS_UPDATE, 1);

	/* AFMT_AUDIO_PACKET_CONTWOW2 */
	WEG_UPDATE_2(AFMT_AUDIO_PACKET_CONTWOW2,
			AFMT_AUDIO_WAYOUT_OVWD, 0,
			AFMT_60958_OSF_OVWD, 0);

	/* AFMT_60958_0__AFMT_60958_CS_CHANNEW_NUMBEW_W_MASK &
	 * AFMT_60958_0__AFMT_60958_CS_CWOCK_ACCUWACY_MASK
	 */
	WEG_UPDATE_2(AFMT_60958_0,
			AFMT_60958_CS_CHANNEW_NUMBEW_W, 1,
			AFMT_60958_CS_CWOCK_ACCUWACY, 0);

	/* AFMT_60958_1 AFMT_60958_CS_CHAWNNEW_NUMBEW_W */
	WEG_UPDATE(AFMT_60958_1, AFMT_60958_CS_CHANNEW_NUMBEW_W, 2);

	/* AFMT_60958_2 now keep this settings untiw
	 * Pwogwamming guide comes out
	 */
	WEG_UPDATE_6(AFMT_60958_2,
			AFMT_60958_CS_CHANNEW_NUMBEW_2, 3,
			AFMT_60958_CS_CHANNEW_NUMBEW_3, 4,
			AFMT_60958_CS_CHANNEW_NUMBEW_4, 5,
			AFMT_60958_CS_CHANNEW_NUMBEW_5, 6,
			AFMT_60958_CS_CHANNEW_NUMBEW_6, 7,
			AFMT_60958_CS_CHANNEW_NUMBEW_7, 8);
}

static union audio_cea_channews speakews_to_channews(
	stwuct audio_speakew_fwags speakew_fwags)
{
	union audio_cea_channews cea_channews = {0};

	/* these awe one to one */
	cea_channews.channews.FW = speakew_fwags.FW_FW;
	cea_channews.channews.FW = speakew_fwags.FW_FW;
	cea_channews.channews.WFE = speakew_fwags.WFE;
	cea_channews.channews.FC = speakew_fwags.FC;

	/* if Weaw Weft and Wight exist move WC speakew to channew 7
	 * othewwise to channew 5
	 */
	if (speakew_fwags.WW_WW) {
		cea_channews.channews.WW_WC = speakew_fwags.WW_WW;
		cea_channews.channews.WW = speakew_fwags.WW_WW;
		cea_channews.channews.WC_WWC_FWC = speakew_fwags.WC;
	} ewse {
		cea_channews.channews.WW_WC = speakew_fwags.WC;
	}

	/* FWONT Weft Wight Centew and WEAW Weft Wight Centew awe excwusive */
	if (speakew_fwags.FWC_FWC) {
		cea_channews.channews.WC_WWC_FWC = speakew_fwags.FWC_FWC;
		cea_channews.channews.WWC_FWC = speakew_fwags.FWC_FWC;
	} ewse {
		cea_channews.channews.WC_WWC_FWC = speakew_fwags.WWC_WWC;
		cea_channews.channews.WWC_FWC = speakew_fwags.WWC_WWC;
	}

	wetuwn cea_channews;
}

void afmt3_se_audio_setup(
	stwuct afmt *afmt,
	unsigned int az_inst,
	stwuct audio_info *audio_info)
{
	stwuct dcn30_afmt *afmt3 = DCN30_AFMT_FWOM_AFMT(afmt);

	uint32_t channews = 0;

	ASSEWT(audio_info);
	/* This shouwd not happen.it does so we don't get BSOD*/
	if (audio_info == NUWW)
		wetuwn;

	channews = speakews_to_channews(audio_info->fwags.speakew_fwags).aww;

	/* setup the audio stweam souwce sewect (audio -> dig mapping) */
	WEG_SET(AFMT_AUDIO_SWC_CONTWOW, 0, AFMT_AUDIO_SWC_SEWECT, az_inst);

	/* Channew awwocation */
	WEG_UPDATE(AFMT_AUDIO_PACKET_CONTWOW2, AFMT_AUDIO_CHANNEW_ENABWE, channews);

	/* Disabwe fowced mem powew off */
	if (afmt->funcs->afmt_powewon == NUWW)
		WEG_UPDATE(AFMT_MEM_PWW, AFMT_MEM_PWW_FOWCE, 0);
}

void afmt3_audio_mute_contwow(
	stwuct afmt *afmt,
	boow mute)
{
	stwuct dcn30_afmt *afmt3 = DCN30_AFMT_FWOM_AFMT(afmt);
	if (mute && afmt->funcs->afmt_powewdown)
		afmt->funcs->afmt_powewdown(afmt);
	if (!mute && afmt->funcs->afmt_powewon)
		afmt->funcs->afmt_powewon(afmt);
	/* enabwe/disabwe twansmission of audio packets */
	WEG_UPDATE(AFMT_AUDIO_PACKET_CONTWOW, AFMT_AUDIO_SAMPWE_SEND, !mute);
}

void afmt3_audio_info_immediate_update(
	stwuct afmt *afmt)
{
	stwuct dcn30_afmt *afmt3 = DCN30_AFMT_FWOM_AFMT(afmt);

	/* update doubwe-buffewed AUDIO_INFO wegistews immediatewy */
	WEG_UPDATE(AFMT_INFOFWAME_CONTWOW0, AFMT_AUDIO_INFO_UPDATE, 1);
}

void afmt3_setup_dp_audio(
		stwuct afmt *afmt)
{
	stwuct dcn30_afmt *afmt3 = DCN30_AFMT_FWOM_AFMT(afmt);

	if (afmt->funcs->afmt_powewon)
		afmt->funcs->afmt_powewon(afmt);

	/* AFMT_AUDIO_PACKET_CONTWOW */
	WEG_UPDATE(AFMT_AUDIO_PACKET_CONTWOW, AFMT_60958_CS_UPDATE, 1);

	/* AFMT_AUDIO_PACKET_CONTWOW2 */
	/* Pwogwam the ATP and AIP next */
	WEG_UPDATE_2(AFMT_AUDIO_PACKET_CONTWOW2,
			AFMT_AUDIO_WAYOUT_OVWD, 0,
			AFMT_60958_OSF_OVWD, 0);

	/* AFMT_INFOFWAME_CONTWOW0 */
	WEG_UPDATE(AFMT_INFOFWAME_CONTWOW0, AFMT_AUDIO_INFO_UPDATE, 1);

	/* AFMT_60958_0__AFMT_60958_CS_CWOCK_ACCUWACY_MASK */
	WEG_UPDATE(AFMT_60958_0, AFMT_60958_CS_CWOCK_ACCUWACY, 0);
}

static stwuct afmt_funcs dcn30_afmt_funcs = {
	.setup_hdmi_audio		= afmt3_setup_hdmi_audio,
	.se_audio_setup			= afmt3_se_audio_setup,
	.audio_mute_contwow		= afmt3_audio_mute_contwow,
	.audio_info_immediate_update	= afmt3_audio_info_immediate_update,
	.setup_dp_audio			= afmt3_setup_dp_audio,
};

void afmt3_constwuct(stwuct dcn30_afmt *afmt3,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn30_afmt_wegistews *afmt_wegs,
	const stwuct dcn30_afmt_shift *afmt_shift,
	const stwuct dcn30_afmt_mask *afmt_mask)
{
	afmt3->base.ctx = ctx;

	afmt3->base.inst = inst;
	afmt3->base.funcs = &dcn30_afmt_funcs;

	afmt3->wegs = afmt_wegs;
	afmt3->afmt_shift = afmt_shift;
	afmt3->afmt_mask = afmt_mask;
}
