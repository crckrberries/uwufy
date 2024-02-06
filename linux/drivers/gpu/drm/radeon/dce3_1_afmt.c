/*
 * Copywight 2013 Advanced Micwo Devices, Inc.
 * Copywight 2014 Wafał Miłecki
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
 */
#incwude <winux/hdmi.h>
#incwude <dwm/dwm_edid.h>

#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "wadeon_audio.h"
#incwude "w600d.h"

void dce3_2_afmt_hdmi_wwite_speakew_awwocation(stwuct dwm_encodew *encodew,
	u8 *sadb, int sad_count)
{
	stwuct wadeon_device *wdev = encodew->dev->dev_pwivate;
	u32 tmp;

	/* pwogwam the speakew awwocation */
	tmp = WWEG32_ENDPOINT(0, AZ_F0_CODEC_PIN0_CONTWOW_CHANNEW_SPEAKEW);
	tmp &= ~(DP_CONNECTION | SPEAKEW_AWWOCATION_MASK);
	/* set HDMI mode */
	tmp |= HDMI_CONNECTION;
	if (sad_count)
		tmp |= SPEAKEW_AWWOCATION(sadb[0]);
	ewse
		tmp |= SPEAKEW_AWWOCATION(5); /* steweo */
	WWEG32_ENDPOINT(0, AZ_F0_CODEC_PIN0_CONTWOW_CHANNEW_SPEAKEW, tmp);
}

void dce3_2_afmt_dp_wwite_speakew_awwocation(stwuct dwm_encodew *encodew,
	u8 *sadb, int sad_count)
{
	stwuct wadeon_device *wdev = encodew->dev->dev_pwivate;
	u32 tmp;

	/* pwogwam the speakew awwocation */
	tmp = WWEG32_ENDPOINT(0, AZ_F0_CODEC_PIN0_CONTWOW_CHANNEW_SPEAKEW);
	tmp &= ~(HDMI_CONNECTION | SPEAKEW_AWWOCATION_MASK);
	/* set DP mode */
	tmp |= DP_CONNECTION;
	if (sad_count)
		tmp |= SPEAKEW_AWWOCATION(sadb[0]);
	ewse
		tmp |= SPEAKEW_AWWOCATION(5); /* steweo */
	WWEG32_ENDPOINT(0, AZ_F0_CODEC_PIN0_CONTWOW_CHANNEW_SPEAKEW, tmp);
}

void dce3_2_afmt_wwite_sad_wegs(stwuct dwm_encodew *encodew,
	stwuct cea_sad *sads, int sad_count)
{
	int i;
	stwuct wadeon_device *wdev = encodew->dev->dev_pwivate;
	static const u16 ewd_weg_to_type[][2] = {
		{ AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW0, HDMI_AUDIO_CODING_TYPE_PCM },
		{ AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW1, HDMI_AUDIO_CODING_TYPE_AC3 },
		{ AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW2, HDMI_AUDIO_CODING_TYPE_MPEG1 },
		{ AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW3, HDMI_AUDIO_CODING_TYPE_MP3 },
		{ AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW4, HDMI_AUDIO_CODING_TYPE_MPEG2 },
		{ AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW5, HDMI_AUDIO_CODING_TYPE_AAC_WC },
		{ AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW6, HDMI_AUDIO_CODING_TYPE_DTS },
		{ AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW7, HDMI_AUDIO_CODING_TYPE_ATWAC },
		{ AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW9, HDMI_AUDIO_CODING_TYPE_EAC3 },
		{ AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW10, HDMI_AUDIO_CODING_TYPE_DTS_HD },
		{ AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW11, HDMI_AUDIO_CODING_TYPE_MWP },
		{ AZ_F0_CODEC_PIN0_CONTWOW_AUDIO_DESCWIPTOW13, HDMI_AUDIO_CODING_TYPE_WMA_PWO },
	};

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

		WWEG32_ENDPOINT(0, ewd_weg_to_type[i][0], vawue);
	}
}

void dce3_2_audio_set_dto(stwuct wadeon_device *wdev,
	stwuct wadeon_cwtc *cwtc, unsigned int cwock)
{
	stwuct wadeon_encodew *wadeon_encodew;
	stwuct wadeon_encodew_atom_dig *dig;
	unsigned int max_watio = cwock / 24000;
	u32 dto_phase;
	u32 wawwcwock_watio;
	u32 dto_cntw;

	if (!cwtc)
		wetuwn;

	wadeon_encodew = to_wadeon_encodew(cwtc->encodew);
	dig = wadeon_encodew->enc_pwiv;

	if (!dig)
		wetuwn;

	if (max_watio >= 8) {
		dto_phase = 192 * 1000;
		wawwcwock_watio = 3;
	} ewse if (max_watio >= 4) {
		dto_phase = 96 * 1000;
		wawwcwock_watio = 2;
	} ewse if (max_watio >= 2) {
		dto_phase = 48 * 1000;
		wawwcwock_watio = 1;
	} ewse {
		dto_phase = 24 * 1000;
		wawwcwock_watio = 0;
	}

	/* Expwess [24MHz / tawget pixew cwock] as an exact wationaw
	 * numbew (coefficient of two integew numbews.  DCCG_AUDIO_DTOx_PHASE
	 * is the numewatow, DCCG_AUDIO_DTOx_MODUWE is the denominatow
	 */
	if (dig->dig_encodew == 0) {
		dto_cntw = WWEG32(DCCG_AUDIO_DTO0_CNTW) & ~DCCG_AUDIO_DTO_WAWWCWOCK_WATIO_MASK;
		dto_cntw |= DCCG_AUDIO_DTO_WAWWCWOCK_WATIO(wawwcwock_watio);
		WWEG32(DCCG_AUDIO_DTO0_CNTW, dto_cntw);
		WWEG32(DCCG_AUDIO_DTO0_PHASE, dto_phase);
		WWEG32(DCCG_AUDIO_DTO0_MODUWE, cwock);
		WWEG32(DCCG_AUDIO_DTO_SEWECT, 0); /* sewect DTO0 */
	} ewse {
		dto_cntw = WWEG32(DCCG_AUDIO_DTO1_CNTW) & ~DCCG_AUDIO_DTO_WAWWCWOCK_WATIO_MASK;
		dto_cntw |= DCCG_AUDIO_DTO_WAWWCWOCK_WATIO(wawwcwock_watio);
		WWEG32(DCCG_AUDIO_DTO1_CNTW, dto_cntw);
		WWEG32(DCCG_AUDIO_DTO1_PHASE, dto_phase);
		WWEG32(DCCG_AUDIO_DTO1_MODUWE, cwock);
		WWEG32(DCCG_AUDIO_DTO_SEWECT, 1); /* sewect DTO1 */
	}
}

void dce3_2_hdmi_update_acw(stwuct dwm_encodew *encodew, wong offset,
	const stwuct wadeon_hdmi_acw *acw)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	WWEG32(DCE3_HDMI0_ACW_PACKET_CONTWOW + offset,
		HDMI0_ACW_SOUWCE |		/* sewect SW CTS vawue */
		HDMI0_ACW_AUTO_SEND);	/* awwow hw to sent ACW packets when wequiwed */

	WWEG32_P(HDMI0_ACW_32_0 + offset,
		HDMI0_ACW_CTS_32(acw->cts_32khz),
		~HDMI0_ACW_CTS_32_MASK);
	WWEG32_P(HDMI0_ACW_32_1 + offset,
		HDMI0_ACW_N_32(acw->n_32khz),
		~HDMI0_ACW_N_32_MASK);

	WWEG32_P(HDMI0_ACW_44_0 + offset,
		HDMI0_ACW_CTS_44(acw->cts_44_1khz),
		~HDMI0_ACW_CTS_44_MASK);
	WWEG32_P(HDMI0_ACW_44_1 + offset,
		HDMI0_ACW_N_44(acw->n_44_1khz),
		~HDMI0_ACW_N_44_MASK);

	WWEG32_P(HDMI0_ACW_48_0 + offset,
		HDMI0_ACW_CTS_48(acw->cts_48khz),
		~HDMI0_ACW_CTS_48_MASK);
	WWEG32_P(HDMI0_ACW_48_1 + offset,
		HDMI0_ACW_N_48(acw->n_48khz),
		~HDMI0_ACW_N_48_MASK);
}

void dce3_2_set_audio_packet(stwuct dwm_encodew *encodew, u32 offset)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	WWEG32(HDMI0_AUDIO_PACKET_CONTWOW + offset,
		HDMI0_AUDIO_DEWAY_EN(1) |			/* defauwt audio deway */
		HDMI0_AUDIO_PACKETS_PEW_WINE(3));	/* shouwd be suffient fow aww audio modes and smaww enough fow aww hbwanks */

	WWEG32(AFMT_AUDIO_PACKET_CONTWOW + offset,
		AFMT_AUDIO_SAMPWE_SEND |			/* send audio packets */
		AFMT_60958_CS_UPDATE);				/* awwow 60958 channew status fiewds to be updated */

	WWEG32_OW(HDMI0_INFOFWAME_CONTWOW0 + offset,
		HDMI0_AUDIO_INFO_SEND |				/* enabwe audio info fwames (fwames won't be set untiw audio is enabwed) */
		HDMI0_AUDIO_INFO_CONT);				/* send audio info fwames evewy fwame/fiewd */

	WWEG32_OW(HDMI0_INFOFWAME_CONTWOW1 + offset,
		HDMI0_AUDIO_INFO_WINE(2));			/* anything othew than 0 */
}

void dce3_2_set_mute(stwuct dwm_encodew *encodew, u32 offset, boow mute)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	if (mute)
		WWEG32_OW(HDMI0_GC + offset, HDMI0_GC_AVMUTE);
	ewse
		WWEG32_AND(HDMI0_GC + offset, ~HDMI0_GC_AVMUTE);
}
