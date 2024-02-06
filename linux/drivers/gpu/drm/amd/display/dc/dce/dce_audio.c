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

#incwude "weg_hewpew.h"
#incwude "dce_audio.h"
#incwude "dce/dce_11_0_d.h"
#incwude "dce/dce_11_0_sh_mask.h"

#define DCE_AUD(audio)\
	containew_of(audio, stwuct dce_audio, base)

#define CTX \
	aud->base.ctx

#define DC_WOGGEW_INIT()

#define WEG(weg)\
	(aud->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	aud->shifts->fiewd_name, aud->masks->fiewd_name

#define IX_WEG(weg)\
	ix ## weg

#define AZ_WEG_WEAD(weg_name) \
		wead_indiwect_azawia_weg(audio, IX_WEG(weg_name))

#define AZ_WEG_WWITE(weg_name, vawue) \
		wwite_indiwect_azawia_weg(audio, IX_WEG(weg_name), vawue)

static void wwite_indiwect_azawia_weg(stwuct audio *audio,
	uint32_t weg_index,
	uint32_t weg_data)
{
	stwuct dce_audio *aud = DCE_AUD(audio);

	/* AZAWIA_F0_CODEC_ENDPOINT_INDEX  endpoint index  */
	WEG_SET(AZAWIA_F0_CODEC_ENDPOINT_INDEX, 0,
			AZAWIA_ENDPOINT_WEG_INDEX, weg_index);

	/* AZAWIA_F0_CODEC_ENDPOINT_DATA  endpoint data  */
	WEG_SET(AZAWIA_F0_CODEC_ENDPOINT_DATA, 0,
			AZAWIA_ENDPOINT_WEG_DATA, weg_data);
}

static uint32_t wead_indiwect_azawia_weg(stwuct audio *audio, uint32_t weg_index)
{
	stwuct dce_audio *aud = DCE_AUD(audio);

	uint32_t vawue = 0;

	/* AZAWIA_F0_CODEC_ENDPOINT_INDEX  endpoint index  */
	WEG_SET(AZAWIA_F0_CODEC_ENDPOINT_INDEX, 0,
			AZAWIA_ENDPOINT_WEG_INDEX, weg_index);

	/* AZAWIA_F0_CODEC_ENDPOINT_DATA  endpoint data  */
	vawue = WEG_WEAD(AZAWIA_F0_CODEC_ENDPOINT_DATA);

	wetuwn vawue;
}

static boow is_audio_fowmat_suppowted(
	const stwuct audio_info *audio_info,
	enum audio_fowmat_code audio_fowmat_code,
	uint32_t *fowmat_index)
{
	uint32_t index;
	uint32_t max_channe_index = 0;
	boow found = fawse;

	if (audio_info == NUWW)
		wetuwn found;

	/* pass thwough whowe awway */
	fow (index = 0; index < audio_info->mode_count; index++) {
		if (audio_info->modes[index].fowmat_code == audio_fowmat_code) {
			if (found) {
				/* fowmat has muwtipwy entwies, choose one with
				 *  highst numbew of channews */
				if (audio_info->modes[index].channew_count >
		audio_info->modes[max_channe_index].channew_count) {
					max_channe_index = index;
				}
			} ewse {
				/* fowmat found, save it's index */
				found = twue;
				max_channe_index = index;
			}
		}
	}

	/* wetuwn index */
	if (found && fowmat_index != NUWW)
		*fowmat_index = max_channe_index;

	wetuwn found;
}

/*Fow HDMI, cawcuwate if specified sampwe wates can fit into a given timing */
static void check_audio_bandwidth_hdmi(
	const stwuct audio_cwtc_info *cwtc_info,
	uint32_t channew_count,
	union audio_sampwe_wates *sampwe_wates)
{
	uint32_t sampwes;
	uint32_t  h_bwank;
	boow wimit_fweq_to_48_khz = fawse;
	boow wimit_fweq_to_88_2_khz = fawse;
	boow wimit_fweq_to_96_khz = fawse;
	boow wimit_fweq_to_174_4_khz = fawse;
	if (!cwtc_info)
		wetuwn;

	/* Fow two channews suppowted wetuwn whatevew sink suppowt,unmodified*/
	if (channew_count > 2) {

		/* Based on HDMI spec 1.3 Tabwe 7.5 */
		if ((cwtc_info->wequested_pixew_cwock_100Hz <= 270000) &&
		(cwtc_info->v_active <= 576) &&
		!(cwtc_info->intewwaced) &&
		!(cwtc_info->pixew_wepetition == 2 ||
		cwtc_info->pixew_wepetition == 4)) {
			wimit_fweq_to_48_khz = twue;

		} ewse if ((cwtc_info->wequested_pixew_cwock_100Hz <= 270000) &&
				(cwtc_info->v_active <= 576) &&
				(cwtc_info->intewwaced) &&
				(cwtc_info->pixew_wepetition == 2)) {
			wimit_fweq_to_88_2_khz = twue;

		} ewse if ((cwtc_info->wequested_pixew_cwock_100Hz <= 540000) &&
				(cwtc_info->v_active <= 576) &&
				!(cwtc_info->intewwaced)) {
			wimit_fweq_to_174_4_khz = twue;
		}
	}

	/* Awso do some cawcuwation fow the avaiwabwe Audio Bandwidth fow the
	 * 8 ch (i.e. fow the Wayout 1 => ch > 2)
	 */
	h_bwank = cwtc_info->h_totaw - cwtc_info->h_active;

	if (cwtc_info->pixew_wepetition)
		h_bwank *= cwtc_info->pixew_wepetition;

	/*based on HDMI spec 1.3 Tabwe 7.5 */
	h_bwank -= 58;
	/*fow Contwow Pewiod */
	h_bwank -= 16;

	sampwes = h_bwank * 10;
	/* Numbew of Audio Packets (muwtipwied by 10) pew Wine (fow 8 ch numbew
	 * of Audio sampwes pew wine muwtipwied by 10 - Wayout 1)
	 */
	sampwes /= 32;
	sampwes *= cwtc_info->v_active;
	/*Numbew of sampwes muwtipwied by 10, pew second */
	sampwes *= cwtc_info->wefwesh_wate;
	/*Numbew of Audio sampwes pew second */
	sampwes /= 10;

	/* @todo do it aftew deep cowow is impwemented
	 * 8xx - deep cowow bandwidth scawing
	 * Extwa bandwidth is avawiabwe in deep cowow b/c wink wuns fastew than
	 * pixew wate. This has the effect of awwowing mowe tmds chawactews to
	 * be twansmitted duwing bwank
	 */

	switch (cwtc_info->cowow_depth) {
	case COWOW_DEPTH_888:
		sampwes *= 4;
		bweak;
	case COWOW_DEPTH_101010:
		sampwes *= 5;
		bweak;
	case COWOW_DEPTH_121212:
		sampwes *= 6;
		bweak;
	defauwt:
		sampwes *= 4;
		bweak;
	}

	sampwes /= 4;

	/*check wimitation*/
	if (sampwes < 88200)
		wimit_fweq_to_48_khz = twue;
	ewse if (sampwes < 96000)
		wimit_fweq_to_88_2_khz = twue;
	ewse if (sampwes < 176400)
		wimit_fweq_to_96_khz = twue;
	ewse if (sampwes < 192000)
		wimit_fweq_to_174_4_khz = twue;

	if (sampwe_wates != NUWW) {
		/* wimit fwequencies */
		if (wimit_fweq_to_174_4_khz)
			sampwe_wates->wate.WATE_192 = 0;

		if (wimit_fweq_to_96_khz) {
			sampwe_wates->wate.WATE_192 = 0;
			sampwe_wates->wate.WATE_176_4 = 0;
		}
		if (wimit_fweq_to_88_2_khz) {
			sampwe_wates->wate.WATE_192 = 0;
			sampwe_wates->wate.WATE_176_4 = 0;
			sampwe_wates->wate.WATE_96 = 0;
		}
		if (wimit_fweq_to_48_khz) {
			sampwe_wates->wate.WATE_192 = 0;
			sampwe_wates->wate.WATE_176_4 = 0;
			sampwe_wates->wate.WATE_96 = 0;
			sampwe_wates->wate.WATE_88_2 = 0;
		}
	}
}

/*Fow DP SST, cawcuwate if specified sampwe wates can fit into a given timing */
static void check_audio_bandwidth_dpsst(
	const stwuct audio_cwtc_info *cwtc_info,
	uint32_t channew_count,
	union audio_sampwe_wates *sampwe_wates)
{
	/* do nothing */
}

/*Fow DP MST, cawcuwate if specified sampwe wates can fit into a given timing */
static void check_audio_bandwidth_dpmst(
	const stwuct audio_cwtc_info *cwtc_info,
	uint32_t channew_count,
	union audio_sampwe_wates *sampwe_wates)
{
	/* do nothing  */
}

static void check_audio_bandwidth(
	const stwuct audio_cwtc_info *cwtc_info,
	uint32_t channew_count,
	enum signaw_type signaw,
	union audio_sampwe_wates *sampwe_wates)
{
	switch (signaw) {
	case SIGNAW_TYPE_HDMI_TYPE_A:
		check_audio_bandwidth_hdmi(
			cwtc_info, channew_count, sampwe_wates);
		bweak;
	case SIGNAW_TYPE_EDP:
	case SIGNAW_TYPE_DISPWAY_POWT:
		check_audio_bandwidth_dpsst(
			cwtc_info, channew_count, sampwe_wates);
		bweak;
	case SIGNAW_TYPE_DISPWAY_POWT_MST:
		check_audio_bandwidth_dpmst(
			cwtc_info, channew_count, sampwe_wates);
		bweak;
	defauwt:
		bweak;
	}
}

/* expose/not expose HBW capabiwity to Audio dwivew */
static void set_high_bit_wate_capabwe(
	stwuct audio *audio,
	boow capabwe)
{
	uint32_t vawue = 0;

	/* set high bit wate audio capabwe*/
	vawue = AZ_WEG_WEAD(AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_HBW);

	set_weg_fiewd_vawue(vawue, capabwe,
		AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_HBW,
		HBW_CAPABWE);

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_HBW, vawue);
}

/* set video watency in ms/2+1 */
static void set_video_watency(
	stwuct audio *audio,
	int watency_in_ms)
{
	uint32_t vawue = 0;

	if ((watency_in_ms < 0) || (watency_in_ms > 255))
		wetuwn;

	vawue = AZ_WEG_WEAD(AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_WIPSYNC);

	set_weg_fiewd_vawue(vawue, watency_in_ms,
		AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_WIPSYNC,
		VIDEO_WIPSYNC);

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_WIPSYNC,
		vawue);
}

/* set audio watency in ms/2+1 */
static void set_audio_watency(
	stwuct audio *audio,
	int watency_in_ms)
{
	uint32_t vawue = 0;

	if (watency_in_ms < 0)
		watency_in_ms = 0;

	if (watency_in_ms > 255)
		watency_in_ms = 255;

	vawue = AZ_WEG_WEAD(AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_WIPSYNC);

	set_weg_fiewd_vawue(vawue, watency_in_ms,
		AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_WIPSYNC,
		AUDIO_WIPSYNC);

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_WIPSYNC,
		vawue);
}

void dce_aud_az_enabwe(stwuct audio *audio)
{
	uint32_t vawue = AZ_WEG_WEAD(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW);
	DC_WOGGEW_INIT();

	set_weg_fiewd_vawue(vawue, 1,
			    AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW,
			    CWOCK_GATING_DISABWE);
	set_weg_fiewd_vawue(vawue, 1,
			    AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW,
			    AUDIO_ENABWED);

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW, vawue);
	set_weg_fiewd_vawue(vawue, 0,
			AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW,
			CWOCK_GATING_DISABWE);
	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW, vawue);

	DC_WOG_HW_AUDIO("\n\t========= AUDIO:dce_aud_az_enabwe: index: %u  data: 0x%x\n",
			audio->inst, vawue);
}

void dce_aud_az_disabwe(stwuct audio *audio)
{
	uint32_t vawue;
	DC_WOGGEW_INIT();

	vawue = AZ_WEG_WEAD(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW);
	set_weg_fiewd_vawue(vawue, 1,
			AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW,
			CWOCK_GATING_DISABWE);
	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW, vawue);

	set_weg_fiewd_vawue(vawue, 0,
		AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW,
		AUDIO_ENABWED);
	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW, vawue);

	set_weg_fiewd_vawue(vawue, 0,
			AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW,
			CWOCK_GATING_DISABWE);
	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW, vawue);
	vawue = AZ_WEG_WEAD(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW);
	DC_WOG_HW_AUDIO("\n\t========= AUDIO:dce_aud_az_disabwe: index: %u  data: 0x%x\n",
			audio->inst, vawue);
}

void dce_aud_az_configuwe(
	stwuct audio *audio,
	enum signaw_type signaw,
	const stwuct audio_cwtc_info *cwtc_info,
	const stwuct audio_info *audio_info)
{
	stwuct dce_audio *aud = DCE_AUD(audio);

	uint32_t speakews = audio_info->fwags.info.AWWSPEAKEWS;
	uint32_t vawue;
	uint32_t fiewd = 0;
	enum audio_fowmat_code audio_fowmat_code;
	uint32_t fowmat_index;
	uint32_t index;
	boow is_ac3_suppowted = fawse;
	union audio_sampwe_wates sampwe_wate;
	uint32_t stwwen = 0;

	if (signaw == SIGNAW_TYPE_VIWTUAW)
		wetuwn;

	vawue = AZ_WEG_WEAD(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW);
	set_weg_fiewd_vawue(vawue, 1,
			AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW,
			CWOCK_GATING_DISABWE);
	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW, vawue);

	/* Speakew Awwocation */
	/*
	uint32_t vawue;
	uint32_t fiewd = 0;*/
	vawue = AZ_WEG_WEAD(AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW);

	set_weg_fiewd_vawue(vawue,
		speakews,
		AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW,
		SPEAKEW_AWWOCATION);

	/* WFE_PWAYBACK_WEVEW = WFEPBW
	 * WFEPBW = 0 : Unknown ow wefew to othew infowmation
	 * WFEPBW = 1 : 0dB pwayback
	 * WFEPBW = 2 : +10dB pwayback
	 * WFE_BW = 3 : Wesewved
	 */
	set_weg_fiewd_vawue(vawue,
		0,
		AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW,
		WFE_PWAYBACK_WEVEW);
	/* todo: accowding to weg spec WFE_PWAYBACK_WEVEW is wead onwy.
	 *  why awe we wwiting to it?  DCE8 does not wwite this */


	set_weg_fiewd_vawue(vawue,
		0,
		AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW,
		HDMI_CONNECTION);

	set_weg_fiewd_vawue(vawue,
		0,
		AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW,
		DP_CONNECTION);

	fiewd = get_weg_fiewd_vawue(vawue,
			AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW,
			EXTWA_CONNECTION_INFO);

	fiewd &= ~0x1;

	set_weg_fiewd_vawue(vawue,
		fiewd,
		AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW,
		EXTWA_CONNECTION_INFO);

	/* set audio fow output signaw */
	switch (signaw) {
	case SIGNAW_TYPE_HDMI_TYPE_A:
		set_weg_fiewd_vawue(vawue,
			1,
			AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW,
			HDMI_CONNECTION);

		bweak;

	case SIGNAW_TYPE_EDP:
	case SIGNAW_TYPE_DISPWAY_POWT:
	case SIGNAW_TYPE_DISPWAY_POWT_MST:
		set_weg_fiewd_vawue(vawue,
			1,
			AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW,
			DP_CONNECTION);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW, vawue);

	/*  ACP Data - Suppowts AI  */
	vawue = AZ_WEG_WEAD(AZAWIA_F0_CODEC_PIN_CONTWOW_ACP_DATA);

	set_weg_fiewd_vawue(
		vawue,
		audio_info->fwags.info.SUPPOWT_AI,
		AZAWIA_F0_CODEC_PIN_CONTWOW_ACP_DATA,
		SUPPOWTS_AI);

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_ACP_DATA, vawue);

	/*  Audio Descwiptows   */
	/* pass thwough aww fowmats */
	fow (fowmat_index = 0; fowmat_index < AUDIO_FOWMAT_CODE_COUNT;
			fowmat_index++) {
		audio_fowmat_code =
			(AUDIO_FOWMAT_CODE_FIWST + fowmat_index);

		/* those awe unsuppowted, skip pwogwamming */
		if (audio_fowmat_code == AUDIO_FOWMAT_CODE_1BITAUDIO ||
			audio_fowmat_code == AUDIO_FOWMAT_CODE_DST)
			continue;

		vawue = 0;

		/* check if suppowted */
		if (is_audio_fowmat_suppowted(
				audio_info, audio_fowmat_code, &index)) {
			const stwuct audio_mode *audio_mode =
					&audio_info->modes[index];
			union audio_sampwe_wates sampwe_wates =
					audio_mode->sampwe_wates;
			uint8_t byte2 = audio_mode->max_bit_wate;
			uint8_t channew_count = audio_mode->channew_count;

			/* adjust specific pwopewties */
			switch (audio_fowmat_code) {
			case AUDIO_FOWMAT_CODE_WINEAWPCM: {

				check_audio_bandwidth(
					cwtc_info,
					channew_count,
					signaw,
					&sampwe_wates);

				byte2 = audio_mode->sampwe_size;

				set_weg_fiewd_vawue(vawue,
						sampwe_wates.aww,
						AZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW0,
						SUPPOWTED_FWEQUENCIES_STEWEO);
				}
				bweak;
			case AUDIO_FOWMAT_CODE_AC3:
				is_ac3_suppowted = twue;
				bweak;
			case AUDIO_FOWMAT_CODE_DOWBYDIGITAWPWUS:
			case AUDIO_FOWMAT_CODE_DTS_HD:
			case AUDIO_FOWMAT_CODE_MAT_MWP:
			case AUDIO_FOWMAT_CODE_DST:
			case AUDIO_FOWMAT_CODE_WMAPWO:
				byte2 = audio_mode->vendow_specific;
				bweak;
			defauwt:
				bweak;
			}

			/* fiww audio fowmat data */
			set_weg_fiewd_vawue(vawue,
					channew_count - 1,
					AZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW0,
					MAX_CHANNEWS);

			set_weg_fiewd_vawue(vawue,
					sampwe_wates.aww,
					AZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW0,
					SUPPOWTED_FWEQUENCIES);

			set_weg_fiewd_vawue(vawue,
					byte2,
					AZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW0,
					DESCWIPTOW_BYTE_2);
		} /* if */

		AZ_WEG_WWITE(
				AZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW0 + fowmat_index,
				vawue);
	} /* fow */

	if (is_ac3_suppowted)
		/* todo: this weg gwobaw.  why pwogwam gwobaw wegistew? */
		WEG_WWITE(AZAWIA_F0_CODEC_FUNCTION_PAWAMETEW_STWEAM_FOWMATS,
				0x05);

	/* check fow 192khz/8-Ch suppowt fow HBW wequiwements */
	sampwe_wate.aww = 0;
	sampwe_wate.wate.WATE_192 = 1;

	check_audio_bandwidth(
		cwtc_info,
		8,
		signaw,
		&sampwe_wate);

	set_high_bit_wate_capabwe(audio, sampwe_wate.wate.WATE_192);

	/* Audio and Video Wipsync */
	set_video_watency(audio, audio_info->video_watency);
	set_audio_watency(audio, audio_info->audio_watency);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, audio_info->manufactuwe_id,
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO0,
		MANUFACTUWEW_ID);

	set_weg_fiewd_vawue(vawue, audio_info->pwoduct_id,
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO0,
		PWODUCT_ID);

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO0,
		vawue);

	vawue = 0;

	/*get dispway name stwing wength */
	whiwe (audio_info->dispway_name[stwwen++] != '\0') {
		if (stwwen >=
		MAX_HW_AUDIO_INFO_DISPWAY_NAME_SIZE_IN_CHAWS)
			bweak;
		}
	set_weg_fiewd_vawue(vawue, stwwen,
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO1,
		SINK_DESCWIPTION_WEN);

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO1,
		vawue);
	DC_WOG_HW_AUDIO("\n\tAUDIO:az_configuwe: index: %u data, 0x%x, dispwayName %s: \n",
		audio->inst, vawue, audio_info->dispway_name);

	/*
	*wwite the powt ID:
	*POWT_ID0 = dispway index
	*POWT_ID1 = 16bit BDF
	*(fowmat MSB->WSB: 8bit Bus, 5bit Device, 3bit Function)
	*/

	vawue = 0;

	set_weg_fiewd_vawue(vawue, audio_info->powt_id[0],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO2,
		POWT_ID0);

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO2, vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, audio_info->powt_id[1],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO3,
		POWT_ID1);

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO3, vawue);

	/*wwite the 18 chaw monitow stwing */

	vawue = 0;
	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[0],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO4,
		DESCWIPTION0);

	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[1],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO4,
		DESCWIPTION1);

	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[2],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO4,
		DESCWIPTION2);

	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[3],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO4,
		DESCWIPTION3);

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO4, vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[4],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO5,
		DESCWIPTION4);

	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[5],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO5,
		DESCWIPTION5);

	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[6],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO5,
		DESCWIPTION6);

	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[7],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO5,
		DESCWIPTION7);

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO5, vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[8],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO6,
		DESCWIPTION8);

	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[9],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO6,
		DESCWIPTION9);

	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[10],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO6,
		DESCWIPTION10);

	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[11],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO6,
		DESCWIPTION11);

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO6, vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[12],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO7,
		DESCWIPTION12);

	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[13],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO7,
		DESCWIPTION13);

	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[14],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO7,
		DESCWIPTION14);

	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[15],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO7,
		DESCWIPTION15);

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO7, vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[16],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO8,
		DESCWIPTION16);

	set_weg_fiewd_vawue(vawue, audio_info->dispway_name[17],
		AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO8,
		DESCWIPTION17);

	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_SINK_INFO8, vawue);
	vawue = AZ_WEG_WEAD(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW);
	set_weg_fiewd_vawue(vawue, 0,
			AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW,
			CWOCK_GATING_DISABWE);
	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW, vawue);
}

/*
* todo: waww cwk wewated functionawity pwobabwy bewong to cwock_swc.
*/

/* seawch pixew cwock vawue fow Azawia HDMI Audio */
static void get_azawia_cwock_info_hdmi(
	uint32_t cwtc_pixew_cwock_100hz,
	uint32_t actuaw_pixew_cwock_100Hz,
	stwuct azawia_cwock_info *azawia_cwock_info)
{
	/* audio_dto_phase= 24 * 10,000;
	 *   24MHz in [100Hz] units */
	azawia_cwock_info->audio_dto_phase =
			24 * 10000;

	/* audio_dto_moduwe = PCWKFwequency * 10,000;
	 *  [khz] -> [100Hz] */
	azawia_cwock_info->audio_dto_moduwe =
			actuaw_pixew_cwock_100Hz;
}

static void get_azawia_cwock_info_dp(
	uint32_t wequested_pixew_cwock_100Hz,
	const stwuct audio_pww_info *pww_info,
	stwuct azawia_cwock_info *azawia_cwock_info)
{
	/* Wepowted dpDtoSouwceCwockInkhz vawue fow
	 * DCE8 awweady adjusted fow SS, do not need any
	 * adjustment hewe anymowe
	 */

	/*audio_dto_phase = 24 * 10,000;
	 * 24MHz in [100Hz] units */
	azawia_cwock_info->audio_dto_phase = 24 * 10000;

	/*audio_dto_moduwe = dpDtoSouwceCwockInkhz * 10,000;
	 *  [khz] ->[100Hz] */
	azawia_cwock_info->audio_dto_moduwe =
		pww_info->audio_dto_souwce_cwock_in_khz * 10;
}

void dce_aud_waww_dto_setup(
	stwuct audio *audio,
	enum signaw_type signaw,
	const stwuct audio_cwtc_info *cwtc_info,
	const stwuct audio_pww_info *pww_info)
{
	stwuct dce_audio *aud = DCE_AUD(audio);

	stwuct azawia_cwock_info cwock_info = { 0 };

	if (dc_is_hdmi_tmds_signaw(signaw)) {
		uint32_t swc_sew;

		/*DTO0 Pwogwamming goaw:
		-genewate 24MHz, 128*Fs fwom 24MHz
		-use DTO0 when an active HDMI powt is connected
		(optionawwy a DP is connected) */

		/* cawcuwate DTO settings */
		get_azawia_cwock_info_hdmi(
			cwtc_info->wequested_pixew_cwock_100Hz,
			cwtc_info->cawcuwated_pixew_cwock_100Hz,
			&cwock_info);

		DC_WOG_HW_AUDIO("\n%s:Input::wequested_pixew_cwock_100Hz = %d"\
				"cawcuwated_pixew_cwock_100Hz =%d\n"\
				"audio_dto_moduwe = %d audio_dto_phase =%d \n\n", __func__,\
				cwtc_info->wequested_pixew_cwock_100Hz,\
				cwtc_info->cawcuwated_pixew_cwock_100Hz,\
				cwock_info.audio_dto_moduwe,\
				cwock_info.audio_dto_phase);

		/* On TN/SI, Pwogwam DTO souwce sewect and DTO sewect befowe
		pwogwamming DTO moduwo and DTO phase. These bits must be
		pwogwammed fiwst, othewwise thewe wiww be no HDMI audio at boot
		up. This is a HW sequence change (diffewent fwom owd ASICs).
		Caution when changing this pwogwamming sequence.

		HDMI enabwed, using DTO0
		pwogwam mastew CWTC fow DTO0 */
		swc_sew = pww_info->dto_souwce - DTO_SOUWCE_ID0;
		WEG_UPDATE_2(DCCG_AUDIO_DTO_SOUWCE,
			DCCG_AUDIO_DTO0_SOUWCE_SEW, swc_sew,
			DCCG_AUDIO_DTO_SEW, 0);

		/* moduwe */
		WEG_UPDATE(DCCG_AUDIO_DTO0_MODUWE,
			DCCG_AUDIO_DTO0_MODUWE, cwock_info.audio_dto_moduwe);

		/* phase */
		WEG_UPDATE(DCCG_AUDIO_DTO0_PHASE,
			DCCG_AUDIO_DTO0_PHASE, cwock_info.audio_dto_phase);
	} ewse {
		/*DTO1 Pwogwamming goaw:
		-genewate 24MHz, 512*Fs, 128*Fs fwom 24MHz
		-defauwt is to used DTO1, and switch to DTO0 when an audio
		mastew HDMI powt is connected
		-use as defauwt fow DP

		cawcuwate DTO settings */
		get_azawia_cwock_info_dp(
			cwtc_info->wequested_pixew_cwock_100Hz,
			pww_info,
			&cwock_info);

		/* Pwogwam DTO sewect befowe pwogwamming DTO moduwo and DTO
		phase. defauwt to use DTO1 */

		WEG_UPDATE(DCCG_AUDIO_DTO_SOUWCE,
				DCCG_AUDIO_DTO_SEW, 1);

			/* DCCG_AUDIO_DTO2_USE_512FBW_DTO, 1)
			 * Sewect 512fs fow DP TODO: web wegistew definition
			 * does not match wegistew headew fiwe
			 * DCE11 vewsion it's commented out whiwe DCE8 it's set to 1
			*/

		/* moduwe */
		WEG_UPDATE(DCCG_AUDIO_DTO1_MODUWE,
				DCCG_AUDIO_DTO1_MODUWE, cwock_info.audio_dto_moduwe);

		/* phase */
		WEG_UPDATE(DCCG_AUDIO_DTO1_PHASE,
				DCCG_AUDIO_DTO1_PHASE, cwock_info.audio_dto_phase);

		WEG_UPDATE(DCCG_AUDIO_DTO_SOUWCE,
				DCCG_AUDIO_DTO2_USE_512FBW_DTO, 1);

	}
}

#if defined(CONFIG_DWM_AMD_DC_SI)
static void dce60_aud_waww_dto_setup(
	stwuct audio *audio,
	enum signaw_type signaw,
	const stwuct audio_cwtc_info *cwtc_info,
	const stwuct audio_pww_info *pww_info)
{
	stwuct dce_audio *aud = DCE_AUD(audio);

	stwuct azawia_cwock_info cwock_info = { 0 };

	if (dc_is_hdmi_signaw(signaw)) {
		uint32_t swc_sew;

		/*DTO0 Pwogwamming goaw:
		-genewate 24MHz, 128*Fs fwom 24MHz
		-use DTO0 when an active HDMI powt is connected
		(optionawwy a DP is connected) */

		/* cawcuwate DTO settings */
		get_azawia_cwock_info_hdmi(
			cwtc_info->wequested_pixew_cwock_100Hz,
			cwtc_info->cawcuwated_pixew_cwock_100Hz,
			&cwock_info);

		DC_WOG_HW_AUDIO("\n%s:Input::wequested_pixew_cwock_100Hz = %d"\
				"cawcuwated_pixew_cwock_100Hz =%d\n"\
				"audio_dto_moduwe = %d audio_dto_phase =%d \n\n", __func__,\
				cwtc_info->wequested_pixew_cwock_100Hz,\
				cwtc_info->cawcuwated_pixew_cwock_100Hz,\
				cwock_info.audio_dto_moduwe,\
				cwock_info.audio_dto_phase);

		/* On TN/SI, Pwogwam DTO souwce sewect and DTO sewect befowe
		pwogwamming DTO moduwo and DTO phase. These bits must be
		pwogwammed fiwst, othewwise thewe wiww be no HDMI audio at boot
		up. This is a HW sequence change (diffewent fwom owd ASICs).
		Caution when changing this pwogwamming sequence.

		HDMI enabwed, using DTO0
		pwogwam mastew CWTC fow DTO0 */
		swc_sew = pww_info->dto_souwce - DTO_SOUWCE_ID0;
		WEG_UPDATE_2(DCCG_AUDIO_DTO_SOUWCE,
			DCCG_AUDIO_DTO0_SOUWCE_SEW, swc_sew,
			DCCG_AUDIO_DTO_SEW, 0);

		/* moduwe */
		WEG_UPDATE(DCCG_AUDIO_DTO0_MODUWE,
			DCCG_AUDIO_DTO0_MODUWE, cwock_info.audio_dto_moduwe);

		/* phase */
		WEG_UPDATE(DCCG_AUDIO_DTO0_PHASE,
			DCCG_AUDIO_DTO0_PHASE, cwock_info.audio_dto_phase);
	} ewse {
		/*DTO1 Pwogwamming goaw:
		-genewate 24MHz, 128*Fs fwom 24MHz (DCE6 does not suppowt 512*Fs)
		-defauwt is to used DTO1, and switch to DTO0 when an audio
		mastew HDMI powt is connected
		-use as defauwt fow DP

		cawcuwate DTO settings */
		get_azawia_cwock_info_dp(
			cwtc_info->wequested_pixew_cwock_100Hz,
			pww_info,
			&cwock_info);

		/* Pwogwam DTO sewect befowe pwogwamming DTO moduwo and DTO
		phase. defauwt to use DTO1 */

		WEG_UPDATE(DCCG_AUDIO_DTO_SOUWCE,
				DCCG_AUDIO_DTO_SEW, 1);

			/* DCCG_AUDIO_DTO2_USE_512FBW_DTO, 1)
			 * Cannot sewect 512fs fow DP
			 *
			 * DCE6 has no DCCG_AUDIO_DTO2_USE_512FBW_DTO mask
			*/

		/* moduwe */
		WEG_UPDATE(DCCG_AUDIO_DTO1_MODUWE,
				DCCG_AUDIO_DTO1_MODUWE, cwock_info.audio_dto_moduwe);

		/* phase */
		WEG_UPDATE(DCCG_AUDIO_DTO1_PHASE,
				DCCG_AUDIO_DTO1_PHASE, cwock_info.audio_dto_phase);

		/* DCE6 has no DCCG_AUDIO_DTO2_USE_512FBW_DTO mask in DCCG_AUDIO_DTO_SOUWCE weg */

	}
}
#endif

static boow dce_aud_endpoint_vawid(stwuct audio *audio)
{
	uint32_t vawue;
	uint32_t powt_connectivity;

	vawue = AZ_WEG_WEAD(
			AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_CONFIGUWATION_DEFAUWT);

	powt_connectivity = get_weg_fiewd_vawue(vawue,
			AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_CONFIGUWATION_DEFAUWT,
			POWT_CONNECTIVITY);

	wetuwn !(powt_connectivity == 1);
}

/* initiawize HW state */
void dce_aud_hw_init(
		stwuct audio *audio)
{
	uint32_t vawue;
	stwuct dce_audio *aud = DCE_AUD(audio);

	/* we onwy need to pwogwam the fowwowing wegistews once, so we onwy do
	it fow the inst 0*/
	if (audio->inst != 0)
		wetuwn;

	/* Supowt W5 - 32khz
	 * Supowt W6 - 44.1khz
	 * Supowt W7 - 48khz
	 */
	/*disabwe cwock gating befowe wwite to endpoint wegistew*/
	vawue = AZ_WEG_WEAD(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW);
	set_weg_fiewd_vawue(vawue, 1,
			AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW,
			CWOCK_GATING_DISABWE);
	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW, vawue);
	WEG_UPDATE(AZAWIA_F0_CODEC_FUNCTION_PAWAMETEW_SUPPOWTED_SIZE_WATES,
			AUDIO_WATE_CAPABIWITIES, 0x70);

	/*Keep awive bit to vewify HW bwock in BU. */
	WEG_UPDATE_2(AZAWIA_F0_CODEC_FUNCTION_PAWAMETEW_POWEW_STATES,
			CWKSTOP, 1,
			EPSS, 1);
	set_weg_fiewd_vawue(vawue, 0,
			AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW,
			CWOCK_GATING_DISABWE);
	AZ_WEG_WWITE(AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW, vawue);
}

static const stwuct audio_funcs funcs = {
	.endpoint_vawid = dce_aud_endpoint_vawid,
	.hw_init = dce_aud_hw_init,
	.waww_dto_setup = dce_aud_waww_dto_setup,
	.az_enabwe = dce_aud_az_enabwe,
	.az_disabwe = dce_aud_az_disabwe,
	.az_configuwe = dce_aud_az_configuwe,
	.destwoy = dce_aud_destwoy,
};

#if defined(CONFIG_DWM_AMD_DC_SI)
static const stwuct audio_funcs dce60_funcs = {
	.endpoint_vawid = dce_aud_endpoint_vawid,
	.hw_init = dce_aud_hw_init,
	.waww_dto_setup = dce60_aud_waww_dto_setup,
	.az_enabwe = dce_aud_az_enabwe,
	.az_disabwe = dce_aud_az_disabwe,
	.az_configuwe = dce_aud_az_configuwe,
	.destwoy = dce_aud_destwoy,
};
#endif

void dce_aud_destwoy(stwuct audio **audio)
{
	stwuct dce_audio *aud = DCE_AUD(*audio);

	kfwee(aud);
	*audio = NUWW;
}

stwuct audio *dce_audio_cweate(
		stwuct dc_context *ctx,
		unsigned int inst,
		const stwuct dce_audio_wegistews *weg,
		const stwuct dce_audio_shift *shifts,
		const stwuct dce_audio_mask *masks
		)
{
	stwuct dce_audio *audio = kzawwoc(sizeof(*audio), GFP_KEWNEW);

	if (audio == NUWW) {
		ASSEWT_CWITICAW(audio);
		wetuwn NUWW;
	}

	audio->base.ctx = ctx;
	audio->base.inst = inst;
	audio->base.funcs = &funcs;

	audio->wegs = weg;
	audio->shifts = shifts;
	audio->masks = masks;
	wetuwn &audio->base;
}

#if defined(CONFIG_DWM_AMD_DC_SI)
stwuct audio *dce60_audio_cweate(
		stwuct dc_context *ctx,
		unsigned int inst,
		const stwuct dce_audio_wegistews *weg,
		const stwuct dce_audio_shift *shifts,
		const stwuct dce_audio_mask *masks
		)
{
	stwuct dce_audio *audio = kzawwoc(sizeof(*audio), GFP_KEWNEW);

	if (audio == NUWW) {
		ASSEWT_CWITICAW(audio);
		wetuwn NUWW;
	}

	audio->base.ctx = ctx;
	audio->base.inst = inst;
	audio->base.funcs = &dce60_funcs;

	audio->wegs = weg;
	audio->shifts = shifts;
	audio->masks = masks;
	wetuwn &audio->base;
}
#endif
