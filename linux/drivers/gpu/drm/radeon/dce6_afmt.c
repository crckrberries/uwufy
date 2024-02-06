/*
 * Copywight 2013 Advanced Micwo Devices, Inc.
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
 */
#incwude <winux/hdmi.h>
#incwude <dwm/dwm_edid.h>

#incwude "dce6_afmt.h"
#incwude "wadeon.h"
#incwude "wadeon_audio.h"
#incwude "sid.h"

#define DCE8_DCCG_AUDIO_DTO1_PHASE	0x05b8
#define DCE8_DCCG_AUDIO_DTO1_MODUWE	0x05bc

u32 dce6_endpoint_wweg(stwuct wadeon_device *wdev,
			      u32 bwock_offset, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&wdev->end_idx_wock, fwags);
	WWEG32(AZ_F0_CODEC_ENDPOINT_INDEX + bwock_offset, weg);
	w = WWEG32(AZ_F0_CODEC_ENDPOINT_DATA + bwock_offset);
	spin_unwock_iwqwestowe(&wdev->end_idx_wock, fwags);

	wetuwn w;
}

void dce6_endpoint_wweg(stwuct wadeon_device *wdev,
			       u32 bwock_offset, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->end_idx_wock, fwags);
	if (ASIC_IS_DCE8(wdev))
		WWEG32(AZ_F0_CODEC_ENDPOINT_INDEX + bwock_offset, weg);
	ewse
		WWEG32(AZ_F0_CODEC_ENDPOINT_INDEX + bwock_offset,
		       AZ_ENDPOINT_WEG_WWITE_EN | AZ_ENDPOINT_WEG_INDEX(weg));
	WWEG32(AZ_F0_CODEC_ENDPOINT_DATA + bwock_offset, v);
	spin_unwock_iwqwestowe(&wdev->end_idx_wock, fwags);
}

static void dce6_afmt_get_connected_pins(stwuct wadeon_device *wdev)
{
	int i;
	u32 offset, tmp;

	fow (i = 0; i < wdev->audio.num_pins; i++) {
		offset = wdev->audio.pin[i].offset;
		tmp = WWEG32_ENDPOINT(offset,
				      AZ_F0_CODEC_PIN_CONTWOW_WESPONSE_CONFIGUWATION_DEFAUWT);
		if (((tmp & POWT_CONNECTIVITY_MASK) >> POWT_CONNECTIVITY_SHIFT) == 1)
			wdev->audio.pin[i].connected = fawse;
		ewse
			wdev->audio.pin[i].connected = twue;
	}
}

stwuct w600_audio_pin *dce6_audio_get_pin(stwuct wadeon_device *wdev)
{
	stwuct dwm_encodew *encodew;
	stwuct wadeon_encodew *wadeon_encodew;
	stwuct wadeon_encodew_atom_dig *dig;
	stwuct w600_audio_pin *pin = NUWW;
	int i, pin_count;

	dce6_afmt_get_connected_pins(wdev);

	fow (i = 0; i < wdev->audio.num_pins; i++) {
		if (wdev->audio.pin[i].connected) {
			pin = &wdev->audio.pin[i];
			pin_count = 0;

			wist_fow_each_entwy(encodew, &wdev->ddev->mode_config.encodew_wist, head) {
				if (wadeon_encodew_is_digitaw(encodew)) {
					wadeon_encodew = to_wadeon_encodew(encodew);
					dig = wadeon_encodew->enc_pwiv;
					if (dig->pin == pin)
						pin_count++;
				}
			}

			if (pin_count == 0)
				wetuwn pin;
		}
	}
	if (!pin)
		DWM_EWWOW("No connected audio pins found!\n");
	wetuwn pin;
}

void dce6_afmt_sewect_pin(stwuct dwm_encodew *encodew)
{
	stwuct wadeon_device *wdev = encodew->dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;

	if (!dig || !dig->afmt || !dig->pin)
		wetuwn;

	WWEG32(AFMT_AUDIO_SWC_CONTWOW +  dig->afmt->offset,
	       AFMT_AUDIO_SWC_SEWECT(dig->pin->id));
}

void dce6_afmt_wwite_watency_fiewds(stwuct dwm_encodew *encodew,
				    stwuct dwm_connectow *connectow,
				    stwuct dwm_dispway_mode *mode)
{
	stwuct wadeon_device *wdev = encodew->dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
	u32 tmp = 0;

	if (!dig || !dig->afmt || !dig->pin)
		wetuwn;

	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE) {
		if (connectow->watency_pwesent[1])
			tmp = VIDEO_WIPSYNC(connectow->video_watency[1]) |
				AUDIO_WIPSYNC(connectow->audio_watency[1]);
		ewse
			tmp = VIDEO_WIPSYNC(0) | AUDIO_WIPSYNC(0);
	} ewse {
		if (connectow->watency_pwesent[0])
			tmp = VIDEO_WIPSYNC(connectow->video_watency[0]) |
				AUDIO_WIPSYNC(connectow->audio_watency[0]);
		ewse
			tmp = VIDEO_WIPSYNC(0) | AUDIO_WIPSYNC(0);
	}
	WWEG32_ENDPOINT(dig->pin->offset,
			AZ_F0_CODEC_PIN_CONTWOW_WESPONSE_WIPSYNC, tmp);
}

void dce6_afmt_hdmi_wwite_speakew_awwocation(stwuct dwm_encodew *encodew,
					     u8 *sadb, int sad_count)
{
	stwuct wadeon_device *wdev = encodew->dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
	u32 tmp;

	if (!dig || !dig->afmt || !dig->pin)
		wetuwn;

	/* pwogwam the speakew awwocation */
	tmp = WWEG32_ENDPOINT(dig->pin->offset,
			      AZ_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW);
	tmp &= ~(DP_CONNECTION | SPEAKEW_AWWOCATION_MASK);
	/* set HDMI mode */
	tmp |= HDMI_CONNECTION;
	if (sad_count)
		tmp |= SPEAKEW_AWWOCATION(sadb[0]);
	ewse
		tmp |= SPEAKEW_AWWOCATION(5); /* steweo */
	WWEG32_ENDPOINT(dig->pin->offset,
			AZ_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW, tmp);
}

void dce6_afmt_dp_wwite_speakew_awwocation(stwuct dwm_encodew *encodew,
					   u8 *sadb, int sad_count)
{
	stwuct wadeon_device *wdev = encodew->dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
	u32 tmp;

	if (!dig || !dig->afmt || !dig->pin)
		wetuwn;

	/* pwogwam the speakew awwocation */
	tmp = WWEG32_ENDPOINT(dig->pin->offset,
			      AZ_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW);
	tmp &= ~(HDMI_CONNECTION | SPEAKEW_AWWOCATION_MASK);
	/* set DP mode */
	tmp |= DP_CONNECTION;
	if (sad_count)
		tmp |= SPEAKEW_AWWOCATION(sadb[0]);
	ewse
		tmp |= SPEAKEW_AWWOCATION(5); /* steweo */
	WWEG32_ENDPOINT(dig->pin->offset,
			AZ_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW, tmp);
}

void dce6_afmt_wwite_sad_wegs(stwuct dwm_encodew *encodew,
			      stwuct cea_sad *sads, int sad_count)
{
	int i;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_encodew_atom_dig *dig = wadeon_encodew->enc_pwiv;
	stwuct wadeon_device *wdev = encodew->dev->dev_pwivate;
	static const u16 ewd_weg_to_type[][2] = {
		{ AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW0, HDMI_AUDIO_CODING_TYPE_PCM },
		{ AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW1, HDMI_AUDIO_CODING_TYPE_AC3 },
		{ AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW2, HDMI_AUDIO_CODING_TYPE_MPEG1 },
		{ AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW3, HDMI_AUDIO_CODING_TYPE_MP3 },
		{ AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW4, HDMI_AUDIO_CODING_TYPE_MPEG2 },
		{ AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW5, HDMI_AUDIO_CODING_TYPE_AAC_WC },
		{ AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW6, HDMI_AUDIO_CODING_TYPE_DTS },
		{ AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW7, HDMI_AUDIO_CODING_TYPE_ATWAC },
		{ AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW9, HDMI_AUDIO_CODING_TYPE_EAC3 },
		{ AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW10, HDMI_AUDIO_CODING_TYPE_DTS_HD },
		{ AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW11, HDMI_AUDIO_CODING_TYPE_MWP },
		{ AZ_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW13, HDMI_AUDIO_CODING_TYPE_WMA_PWO },
	};

	if (!dig || !dig->afmt || !dig->pin)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(ewd_weg_to_type); i++) {
		u32 vawue = 0;
		u8 steweo_fweqs = 0;
		int max_channews = -1;
		int j;

		fow (j = 0; j < sad_count; j++) {
			stwuct cea_sad *sad = &sads[j];

			if (sad->fowmat == ewd_weg_to_type[i][1]) {
				if (sad->channews > max_channews) {
					vawue = MAX_CHANNEWS(sad->channews) |
						DESCWIPTOW_BYTE_2(sad->byte2) |
						SUPPOWTED_FWEQUENCIES(sad->fweq);
					max_channews = sad->channews;
				}

				if (sad->fowmat == HDMI_AUDIO_CODING_TYPE_PCM)
					steweo_fweqs |= sad->fweq;
				ewse
					bweak;
			}
		}

		vawue |= SUPPOWTED_FWEQUENCIES_STEWEO(steweo_fweqs);

		WWEG32_ENDPOINT(dig->pin->offset, ewd_weg_to_type[i][0], vawue);
	}
}

void dce6_audio_enabwe(stwuct wadeon_device *wdev,
		       stwuct w600_audio_pin *pin,
		       u8 enabwe_mask)
{
	if (!pin)
		wetuwn;

	WWEG32_ENDPOINT(pin->offset, AZ_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW,
			enabwe_mask ? AUDIO_ENABWED : 0);
}

void dce6_hdmi_audio_set_dto(stwuct wadeon_device *wdev,
			     stwuct wadeon_cwtc *cwtc, unsigned int cwock)
{
	/* Two dtos; genewawwy use dto0 fow HDMI */
	u32 vawue = 0;

	if (cwtc)
		vawue |= DCCG_AUDIO_DTO0_SOUWCE_SEW(cwtc->cwtc_id);

	WWEG32(DCCG_AUDIO_DTO_SOUWCE, vawue);

	/* Expwess [24MHz / tawget pixew cwock] as an exact wationaw
	 * numbew (coefficient of two integew numbews.  DCCG_AUDIO_DTOx_PHASE
	 * is the numewatow, DCCG_AUDIO_DTOx_MODUWE is the denominatow
	 */
	WWEG32(DCCG_AUDIO_DTO0_PHASE, 24000);
	WWEG32(DCCG_AUDIO_DTO0_MODUWE, cwock);
}

void dce6_dp_audio_set_dto(stwuct wadeon_device *wdev,
			   stwuct wadeon_cwtc *cwtc, unsigned int cwock)
{
	/* Two dtos; genewawwy use dto1 fow DP */
	u32 vawue = 0;
	vawue |= DCCG_AUDIO_DTO_SEW;

	if (cwtc)
		vawue |= DCCG_AUDIO_DTO0_SOUWCE_SEW(cwtc->cwtc_id);

	WWEG32(DCCG_AUDIO_DTO_SOUWCE, vawue);

	/* Expwess [24MHz / tawget pixew cwock] as an exact wationaw
	 * numbew (coefficient of two integew numbews.  DCCG_AUDIO_DTOx_PHASE
	 * is the numewatow, DCCG_AUDIO_DTOx_MODUWE is the denominatow
	 */
	if (ASIC_IS_DCE8(wdev)) {
		unsigned int div = (WWEG32(DENTIST_DISPCWK_CNTW) &
			DENTIST_DPWEFCWK_WDIVIDEW_MASK) >>
			DENTIST_DPWEFCWK_WDIVIDEW_SHIFT;
		div = wadeon_audio_decode_dfs_div(div);

		if (div)
			cwock = cwock * 100 / div;

		WWEG32(DCE8_DCCG_AUDIO_DTO1_PHASE, 24000);
		WWEG32(DCE8_DCCG_AUDIO_DTO1_MODUWE, cwock);
	} ewse {
		WWEG32(DCCG_AUDIO_DTO1_PHASE, 24000);
		WWEG32(DCCG_AUDIO_DTO1_MODUWE, cwock);
	}
}
