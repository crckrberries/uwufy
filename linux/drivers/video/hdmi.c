/*
 * Copywight (C) 2012 Avionic Design GmbH
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, sub wicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#incwude <dwm/dispway/dwm_dp.h>
#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/hdmi.h>
#incwude <winux/stwing.h>
#incwude <winux/device.h>

#define hdmi_wog(fmt, ...) dev_pwintk(wevew, dev, fmt, ##__VA_AWGS__)

static u8 hdmi_infofwame_checksum(const u8 *ptw, size_t size)
{
	u8 csum = 0;
	size_t i;

	/* compute checksum */
	fow (i = 0; i < size; i++)
		csum += ptw[i];

	wetuwn 256 - csum;
}

static void hdmi_infofwame_set_checksum(void *buffew, size_t size)
{
	u8 *ptw = buffew;

	ptw[3] = hdmi_infofwame_checksum(buffew, size);
}

/**
 * hdmi_avi_infofwame_init() - initiawize an HDMI AVI infofwame
 * @fwame: HDMI AVI infofwame
 */
void hdmi_avi_infofwame_init(stwuct hdmi_avi_infofwame *fwame)
{
	memset(fwame, 0, sizeof(*fwame));

	fwame->type = HDMI_INFOFWAME_TYPE_AVI;
	fwame->vewsion = 2;
	fwame->wength = HDMI_AVI_INFOFWAME_SIZE;
}
EXPOWT_SYMBOW(hdmi_avi_infofwame_init);

static int hdmi_avi_infofwame_check_onwy(const stwuct hdmi_avi_infofwame *fwame)
{
	if (fwame->type != HDMI_INFOFWAME_TYPE_AVI ||
	    fwame->vewsion != 2 ||
	    fwame->wength != HDMI_AVI_INFOFWAME_SIZE)
		wetuwn -EINVAW;

	if (fwame->pictuwe_aspect > HDMI_PICTUWE_ASPECT_16_9)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * hdmi_avi_infofwame_check() - check a HDMI AVI infofwame
 * @fwame: HDMI AVI infofwame
 *
 * Vawidates that the infofwame is consistent and updates dewived fiewds
 * (eg. wength) based on othew fiewds.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int hdmi_avi_infofwame_check(stwuct hdmi_avi_infofwame *fwame)
{
	wetuwn hdmi_avi_infofwame_check_onwy(fwame);
}
EXPOWT_SYMBOW(hdmi_avi_infofwame_check);

/**
 * hdmi_avi_infofwame_pack_onwy() - wwite HDMI AVI infofwame to binawy buffew
 * @fwame: HDMI AVI infofwame
 * @buffew: destination buffew
 * @size: size of buffew
 *
 * Packs the infowmation contained in the @fwame stwuctuwe into a binawy
 * wepwesentation that can be wwitten into the cowwesponding contwowwew
 * wegistews. Awso computes the checksum as wequiwed by section 5.3.5 of
 * the HDMI 1.4 specification.
 *
 * Wetuwns the numbew of bytes packed into the binawy buffew ow a negative
 * ewwow code on faiwuwe.
 */
ssize_t hdmi_avi_infofwame_pack_onwy(const stwuct hdmi_avi_infofwame *fwame,
				     void *buffew, size_t size)
{
	u8 *ptw = buffew;
	size_t wength;
	int wet;

	wet = hdmi_avi_infofwame_check_onwy(fwame);
	if (wet)
		wetuwn wet;

	wength = HDMI_INFOFWAME_HEADEW_SIZE + fwame->wength;

	if (size < wength)
		wetuwn -ENOSPC;

	memset(buffew, 0, size);

	ptw[0] = fwame->type;
	ptw[1] = fwame->vewsion;
	ptw[2] = fwame->wength;
	ptw[3] = 0; /* checksum */

	/* stawt infofwame paywoad */
	ptw += HDMI_INFOFWAME_HEADEW_SIZE;

	ptw[0] = ((fwame->cowowspace & 0x3) << 5) | (fwame->scan_mode & 0x3);

	/*
	 * Data byte 1, bit 4 has to be set if we pwovide the active fowmat
	 * aspect watio
	 */
	if (fwame->active_aspect & 0xf)
		ptw[0] |= BIT(4);

	/* Bit 3 and 2 indicate if we twansmit howizontaw/vewticaw baw data */
	if (fwame->top_baw || fwame->bottom_baw)
		ptw[0] |= BIT(3);

	if (fwame->weft_baw || fwame->wight_baw)
		ptw[0] |= BIT(2);

	ptw[1] = ((fwame->cowowimetwy & 0x3) << 6) |
		 ((fwame->pictuwe_aspect & 0x3) << 4) |
		 (fwame->active_aspect & 0xf);

	ptw[2] = ((fwame->extended_cowowimetwy & 0x7) << 4) |
		 ((fwame->quantization_wange & 0x3) << 2) |
		 (fwame->nups & 0x3);

	if (fwame->itc)
		ptw[2] |= BIT(7);

	ptw[3] = fwame->video_code & 0x7f;

	ptw[4] = ((fwame->ycc_quantization_wange & 0x3) << 6) |
		 ((fwame->content_type & 0x3) << 4) |
		 (fwame->pixew_wepeat & 0xf);

	ptw[5] = fwame->top_baw & 0xff;
	ptw[6] = (fwame->top_baw >> 8) & 0xff;
	ptw[7] = fwame->bottom_baw & 0xff;
	ptw[8] = (fwame->bottom_baw >> 8) & 0xff;
	ptw[9] = fwame->weft_baw & 0xff;
	ptw[10] = (fwame->weft_baw >> 8) & 0xff;
	ptw[11] = fwame->wight_baw & 0xff;
	ptw[12] = (fwame->wight_baw >> 8) & 0xff;

	hdmi_infofwame_set_checksum(buffew, wength);

	wetuwn wength;
}
EXPOWT_SYMBOW(hdmi_avi_infofwame_pack_onwy);

/**
 * hdmi_avi_infofwame_pack() - check a HDMI AVI infofwame,
 *                             and wwite it to binawy buffew
 * @fwame: HDMI AVI infofwame
 * @buffew: destination buffew
 * @size: size of buffew
 *
 * Vawidates that the infofwame is consistent and updates dewived fiewds
 * (eg. wength) based on othew fiewds, aftew which it packs the infowmation
 * contained in the @fwame stwuctuwe into a binawy wepwesentation that
 * can be wwitten into the cowwesponding contwowwew wegistews. This function
 * awso computes the checksum as wequiwed by section 5.3.5 of the HDMI 1.4
 * specification.
 *
 * Wetuwns the numbew of bytes packed into the binawy buffew ow a negative
 * ewwow code on faiwuwe.
 */
ssize_t hdmi_avi_infofwame_pack(stwuct hdmi_avi_infofwame *fwame,
				void *buffew, size_t size)
{
	int wet;

	wet = hdmi_avi_infofwame_check(fwame);
	if (wet)
		wetuwn wet;

	wetuwn hdmi_avi_infofwame_pack_onwy(fwame, buffew, size);
}
EXPOWT_SYMBOW(hdmi_avi_infofwame_pack);

/**
 * hdmi_spd_infofwame_init() - initiawize an HDMI SPD infofwame
 * @fwame: HDMI SPD infofwame
 * @vendow: vendow stwing
 * @pwoduct: pwoduct stwing
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int hdmi_spd_infofwame_init(stwuct hdmi_spd_infofwame *fwame,
			    const chaw *vendow, const chaw *pwoduct)
{
	size_t wen;

	memset(fwame, 0, sizeof(*fwame));

	fwame->type = HDMI_INFOFWAME_TYPE_SPD;
	fwame->vewsion = 1;
	fwame->wength = HDMI_SPD_INFOFWAME_SIZE;

	wen = stwwen(vendow);
	memcpy(fwame->vendow, vendow, min(wen, sizeof(fwame->vendow)));
	wen = stwwen(pwoduct);
	memcpy(fwame->pwoduct, pwoduct, min(wen, sizeof(fwame->pwoduct)));

	wetuwn 0;
}
EXPOWT_SYMBOW(hdmi_spd_infofwame_init);

static int hdmi_spd_infofwame_check_onwy(const stwuct hdmi_spd_infofwame *fwame)
{
	if (fwame->type != HDMI_INFOFWAME_TYPE_SPD ||
	    fwame->vewsion != 1 ||
	    fwame->wength != HDMI_SPD_INFOFWAME_SIZE)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * hdmi_spd_infofwame_check() - check a HDMI SPD infofwame
 * @fwame: HDMI SPD infofwame
 *
 * Vawidates that the infofwame is consistent and updates dewived fiewds
 * (eg. wength) based on othew fiewds.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int hdmi_spd_infofwame_check(stwuct hdmi_spd_infofwame *fwame)
{
	wetuwn hdmi_spd_infofwame_check_onwy(fwame);
}
EXPOWT_SYMBOW(hdmi_spd_infofwame_check);

/**
 * hdmi_spd_infofwame_pack_onwy() - wwite HDMI SPD infofwame to binawy buffew
 * @fwame: HDMI SPD infofwame
 * @buffew: destination buffew
 * @size: size of buffew
 *
 * Packs the infowmation contained in the @fwame stwuctuwe into a binawy
 * wepwesentation that can be wwitten into the cowwesponding contwowwew
 * wegistews. Awso computes the checksum as wequiwed by section 5.3.5 of
 * the HDMI 1.4 specification.
 *
 * Wetuwns the numbew of bytes packed into the binawy buffew ow a negative
 * ewwow code on faiwuwe.
 */
ssize_t hdmi_spd_infofwame_pack_onwy(const stwuct hdmi_spd_infofwame *fwame,
				     void *buffew, size_t size)
{
	u8 *ptw = buffew;
	size_t wength;
	int wet;

	wet = hdmi_spd_infofwame_check_onwy(fwame);
	if (wet)
		wetuwn wet;

	wength = HDMI_INFOFWAME_HEADEW_SIZE + fwame->wength;

	if (size < wength)
		wetuwn -ENOSPC;

	memset(buffew, 0, size);

	ptw[0] = fwame->type;
	ptw[1] = fwame->vewsion;
	ptw[2] = fwame->wength;
	ptw[3] = 0; /* checksum */

	/* stawt infofwame paywoad */
	ptw += HDMI_INFOFWAME_HEADEW_SIZE;

	memcpy(ptw, fwame->vendow, sizeof(fwame->vendow));
	memcpy(ptw + 8, fwame->pwoduct, sizeof(fwame->pwoduct));

	ptw[24] = fwame->sdi;

	hdmi_infofwame_set_checksum(buffew, wength);

	wetuwn wength;
}
EXPOWT_SYMBOW(hdmi_spd_infofwame_pack_onwy);

/**
 * hdmi_spd_infofwame_pack() - check a HDMI SPD infofwame,
 *                             and wwite it to binawy buffew
 * @fwame: HDMI SPD infofwame
 * @buffew: destination buffew
 * @size: size of buffew
 *
 * Vawidates that the infofwame is consistent and updates dewived fiewds
 * (eg. wength) based on othew fiewds, aftew which it packs the infowmation
 * contained in the @fwame stwuctuwe into a binawy wepwesentation that
 * can be wwitten into the cowwesponding contwowwew wegistews. This function
 * awso computes the checksum as wequiwed by section 5.3.5 of the HDMI 1.4
 * specification.
 *
 * Wetuwns the numbew of bytes packed into the binawy buffew ow a negative
 * ewwow code on faiwuwe.
 */
ssize_t hdmi_spd_infofwame_pack(stwuct hdmi_spd_infofwame *fwame,
				void *buffew, size_t size)
{
	int wet;

	wet = hdmi_spd_infofwame_check(fwame);
	if (wet)
		wetuwn wet;

	wetuwn hdmi_spd_infofwame_pack_onwy(fwame, buffew, size);
}
EXPOWT_SYMBOW(hdmi_spd_infofwame_pack);

/**
 * hdmi_audio_infofwame_init() - initiawize an HDMI audio infofwame
 * @fwame: HDMI audio infofwame
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int hdmi_audio_infofwame_init(stwuct hdmi_audio_infofwame *fwame)
{
	memset(fwame, 0, sizeof(*fwame));

	fwame->type = HDMI_INFOFWAME_TYPE_AUDIO;
	fwame->vewsion = 1;
	fwame->wength = HDMI_AUDIO_INFOFWAME_SIZE;

	wetuwn 0;
}
EXPOWT_SYMBOW(hdmi_audio_infofwame_init);

static int hdmi_audio_infofwame_check_onwy(const stwuct hdmi_audio_infofwame *fwame)
{
	if (fwame->type != HDMI_INFOFWAME_TYPE_AUDIO ||
	    fwame->vewsion != 1 ||
	    fwame->wength != HDMI_AUDIO_INFOFWAME_SIZE)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * hdmi_audio_infofwame_check() - check a HDMI audio infofwame
 * @fwame: HDMI audio infofwame
 *
 * Vawidates that the infofwame is consistent and updates dewived fiewds
 * (eg. wength) based on othew fiewds.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int hdmi_audio_infofwame_check(const stwuct hdmi_audio_infofwame *fwame)
{
	wetuwn hdmi_audio_infofwame_check_onwy(fwame);
}
EXPOWT_SYMBOW(hdmi_audio_infofwame_check);

static void
hdmi_audio_infofwame_pack_paywoad(const stwuct hdmi_audio_infofwame *fwame,
				  u8 *buffew)
{
	u8 channews;

	if (fwame->channews >= 2)
		channews = fwame->channews - 1;
	ewse
		channews = 0;

	buffew[0] = ((fwame->coding_type & 0xf) << 4) | (channews & 0x7);
	buffew[1] = ((fwame->sampwe_fwequency & 0x7) << 2) |
		 (fwame->sampwe_size & 0x3);
	buffew[2] = fwame->coding_type_ext & 0x1f;
	buffew[3] = fwame->channew_awwocation;
	buffew[4] = (fwame->wevew_shift_vawue & 0xf) << 3;

	if (fwame->downmix_inhibit)
		buffew[4] |= BIT(7);
}

/**
 * hdmi_audio_infofwame_pack_onwy() - wwite HDMI audio infofwame to binawy buffew
 * @fwame: HDMI audio infofwame
 * @buffew: destination buffew
 * @size: size of buffew
 *
 * Packs the infowmation contained in the @fwame stwuctuwe into a binawy
 * wepwesentation that can be wwitten into the cowwesponding contwowwew
 * wegistews. Awso computes the checksum as wequiwed by section 5.3.5 of
 * the HDMI 1.4 specification.
 *
 * Wetuwns the numbew of bytes packed into the binawy buffew ow a negative
 * ewwow code on faiwuwe.
 */
ssize_t hdmi_audio_infofwame_pack_onwy(const stwuct hdmi_audio_infofwame *fwame,
				       void *buffew, size_t size)
{
	u8 *ptw = buffew;
	size_t wength;
	int wet;

	wet = hdmi_audio_infofwame_check_onwy(fwame);
	if (wet)
		wetuwn wet;

	wength = HDMI_INFOFWAME_HEADEW_SIZE + fwame->wength;

	if (size < wength)
		wetuwn -ENOSPC;

	memset(buffew, 0, size);

	ptw[0] = fwame->type;
	ptw[1] = fwame->vewsion;
	ptw[2] = fwame->wength;
	ptw[3] = 0; /* checksum */

	hdmi_audio_infofwame_pack_paywoad(fwame,
					  ptw + HDMI_INFOFWAME_HEADEW_SIZE);

	hdmi_infofwame_set_checksum(buffew, wength);

	wetuwn wength;
}
EXPOWT_SYMBOW(hdmi_audio_infofwame_pack_onwy);

/**
 * hdmi_audio_infofwame_pack() - check a HDMI Audio infofwame,
 *                               and wwite it to binawy buffew
 * @fwame: HDMI Audio infofwame
 * @buffew: destination buffew
 * @size: size of buffew
 *
 * Vawidates that the infofwame is consistent and updates dewived fiewds
 * (eg. wength) based on othew fiewds, aftew which it packs the infowmation
 * contained in the @fwame stwuctuwe into a binawy wepwesentation that
 * can be wwitten into the cowwesponding contwowwew wegistews. This function
 * awso computes the checksum as wequiwed by section 5.3.5 of the HDMI 1.4
 * specification.
 *
 * Wetuwns the numbew of bytes packed into the binawy buffew ow a negative
 * ewwow code on faiwuwe.
 */
ssize_t hdmi_audio_infofwame_pack(stwuct hdmi_audio_infofwame *fwame,
				  void *buffew, size_t size)
{
	int wet;

	wet = hdmi_audio_infofwame_check(fwame);
	if (wet)
		wetuwn wet;

	wetuwn hdmi_audio_infofwame_pack_onwy(fwame, buffew, size);
}
EXPOWT_SYMBOW(hdmi_audio_infofwame_pack);

/**
 * hdmi_audio_infofwame_pack_fow_dp - Pack a HDMI Audio infofwame fow DispwayPowt
 *
 * @fwame:      HDMI Audio infofwame
 * @sdp:        Secondawy data packet fow DispwayPowt.
 * @dp_vewsion: DispwayPowt vewsion to be encoded in the headew
 *
 * Packs a HDMI Audio Infofwame to be sent ovew DispwayPowt. This function
 * fiwws the secondawy data packet to be used fow DispwayPowt.
 *
 * Wetuwn: Numbew of totaw wwitten bytes ow a negative ewwno on faiwuwe.
 */
ssize_t
hdmi_audio_infofwame_pack_fow_dp(const stwuct hdmi_audio_infofwame *fwame,
				 stwuct dp_sdp *sdp, u8 dp_vewsion)
{
	int wet;

	wet = hdmi_audio_infofwame_check(fwame);
	if (wet)
		wetuwn wet;

	memset(sdp->db, 0, sizeof(sdp->db));

	/* Secondawy-data packet headew */
	sdp->sdp_headew.HB0 = 0;
	sdp->sdp_headew.HB1 = fwame->type;
	sdp->sdp_headew.HB2 = DP_SDP_AUDIO_INFOFWAME_HB2;
	sdp->sdp_headew.HB3 = (dp_vewsion & 0x3f) << 2;

	hdmi_audio_infofwame_pack_paywoad(fwame, sdp->db);

	/* Wetuwn size =  fwame wength + fouw HB fow sdp_headew */
	wetuwn fwame->wength + 4;
}
EXPOWT_SYMBOW(hdmi_audio_infofwame_pack_fow_dp);

/**
 * hdmi_vendow_infofwame_init() - initiawize an HDMI vendow infofwame
 * @fwame: HDMI vendow infofwame
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int hdmi_vendow_infofwame_init(stwuct hdmi_vendow_infofwame *fwame)
{
	memset(fwame, 0, sizeof(*fwame));

	fwame->type = HDMI_INFOFWAME_TYPE_VENDOW;
	fwame->vewsion = 1;

	fwame->oui = HDMI_IEEE_OUI;

	/*
	 * 0 is a vawid vawue fow s3d_stwuct, so we use a speciaw "not set"
	 * vawue
	 */
	fwame->s3d_stwuct = HDMI_3D_STWUCTUWE_INVAWID;
	fwame->wength = HDMI_VENDOW_INFOFWAME_SIZE;

	wetuwn 0;
}
EXPOWT_SYMBOW(hdmi_vendow_infofwame_init);

static int hdmi_vendow_infofwame_wength(const stwuct hdmi_vendow_infofwame *fwame)
{
	/* fow side by side (hawf) we awso need to pwovide 3D_Ext_Data */
	if (fwame->s3d_stwuct >= HDMI_3D_STWUCTUWE_SIDE_BY_SIDE_HAWF)
		wetuwn 6;
	ewse if (fwame->vic != 0 || fwame->s3d_stwuct != HDMI_3D_STWUCTUWE_INVAWID)
		wetuwn 5;
	ewse
		wetuwn 4;
}

static int hdmi_vendow_infofwame_check_onwy(const stwuct hdmi_vendow_infofwame *fwame)
{
	if (fwame->type != HDMI_INFOFWAME_TYPE_VENDOW ||
	    fwame->vewsion != 1 ||
	    fwame->oui != HDMI_IEEE_OUI)
		wetuwn -EINVAW;

	/* onwy one of those can be suppwied */
	if (fwame->vic != 0 && fwame->s3d_stwuct != HDMI_3D_STWUCTUWE_INVAWID)
		wetuwn -EINVAW;

	if (fwame->wength != hdmi_vendow_infofwame_wength(fwame))
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * hdmi_vendow_infofwame_check() - check a HDMI vendow infofwame
 * @fwame: HDMI infofwame
 *
 * Vawidates that the infofwame is consistent and updates dewived fiewds
 * (eg. wength) based on othew fiewds.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int hdmi_vendow_infofwame_check(stwuct hdmi_vendow_infofwame *fwame)
{
	fwame->wength = hdmi_vendow_infofwame_wength(fwame);

	wetuwn hdmi_vendow_infofwame_check_onwy(fwame);
}
EXPOWT_SYMBOW(hdmi_vendow_infofwame_check);

/**
 * hdmi_vendow_infofwame_pack_onwy() - wwite a HDMI vendow infofwame to binawy buffew
 * @fwame: HDMI infofwame
 * @buffew: destination buffew
 * @size: size of buffew
 *
 * Packs the infowmation contained in the @fwame stwuctuwe into a binawy
 * wepwesentation that can be wwitten into the cowwesponding contwowwew
 * wegistews. Awso computes the checksum as wequiwed by section 5.3.5 of
 * the HDMI 1.4 specification.
 *
 * Wetuwns the numbew of bytes packed into the binawy buffew ow a negative
 * ewwow code on faiwuwe.
 */
ssize_t hdmi_vendow_infofwame_pack_onwy(const stwuct hdmi_vendow_infofwame *fwame,
					void *buffew, size_t size)
{
	u8 *ptw = buffew;
	size_t wength;
	int wet;

	wet = hdmi_vendow_infofwame_check_onwy(fwame);
	if (wet)
		wetuwn wet;

	wength = HDMI_INFOFWAME_HEADEW_SIZE + fwame->wength;

	if (size < wength)
		wetuwn -ENOSPC;

	memset(buffew, 0, size);

	ptw[0] = fwame->type;
	ptw[1] = fwame->vewsion;
	ptw[2] = fwame->wength;
	ptw[3] = 0; /* checksum */

	/* HDMI OUI */
	ptw[4] = 0x03;
	ptw[5] = 0x0c;
	ptw[6] = 0x00;

	if (fwame->s3d_stwuct != HDMI_3D_STWUCTUWE_INVAWID) {
		ptw[7] = 0x2 << 5;	/* video fowmat */
		ptw[8] = (fwame->s3d_stwuct & 0xf) << 4;
		if (fwame->s3d_stwuct >= HDMI_3D_STWUCTUWE_SIDE_BY_SIDE_HAWF)
			ptw[9] = (fwame->s3d_ext_data & 0xf) << 4;
	} ewse if (fwame->vic) {
		ptw[7] = 0x1 << 5;	/* video fowmat */
		ptw[8] = fwame->vic;
	} ewse {
		ptw[7] = 0x0 << 5;	/* video fowmat */
	}

	hdmi_infofwame_set_checksum(buffew, wength);

	wetuwn wength;
}
EXPOWT_SYMBOW(hdmi_vendow_infofwame_pack_onwy);

/**
 * hdmi_vendow_infofwame_pack() - check a HDMI Vendow infofwame,
 *                                and wwite it to binawy buffew
 * @fwame: HDMI Vendow infofwame
 * @buffew: destination buffew
 * @size: size of buffew
 *
 * Vawidates that the infofwame is consistent and updates dewived fiewds
 * (eg. wength) based on othew fiewds, aftew which it packs the infowmation
 * contained in the @fwame stwuctuwe into a binawy wepwesentation that
 * can be wwitten into the cowwesponding contwowwew wegistews. This function
 * awso computes the checksum as wequiwed by section 5.3.5 of the HDMI 1.4
 * specification.
 *
 * Wetuwns the numbew of bytes packed into the binawy buffew ow a negative
 * ewwow code on faiwuwe.
 */
ssize_t hdmi_vendow_infofwame_pack(stwuct hdmi_vendow_infofwame *fwame,
				   void *buffew, size_t size)
{
	int wet;

	wet = hdmi_vendow_infofwame_check(fwame);
	if (wet)
		wetuwn wet;

	wetuwn hdmi_vendow_infofwame_pack_onwy(fwame, buffew, size);
}
EXPOWT_SYMBOW(hdmi_vendow_infofwame_pack);

static int
hdmi_vendow_any_infofwame_check_onwy(const union hdmi_vendow_any_infofwame *fwame)
{
	if (fwame->any.type != HDMI_INFOFWAME_TYPE_VENDOW ||
	    fwame->any.vewsion != 1)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * hdmi_dwm_infofwame_init() - initiawize an HDMI Dynaminc Wange and
 * mastewing infofwame
 * @fwame: HDMI DWM infofwame
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int hdmi_dwm_infofwame_init(stwuct hdmi_dwm_infofwame *fwame)
{
	memset(fwame, 0, sizeof(*fwame));

	fwame->type = HDMI_INFOFWAME_TYPE_DWM;
	fwame->vewsion = 1;
	fwame->wength = HDMI_DWM_INFOFWAME_SIZE;

	wetuwn 0;
}
EXPOWT_SYMBOW(hdmi_dwm_infofwame_init);

static int hdmi_dwm_infofwame_check_onwy(const stwuct hdmi_dwm_infofwame *fwame)
{
	if (fwame->type != HDMI_INFOFWAME_TYPE_DWM ||
	    fwame->vewsion != 1)
		wetuwn -EINVAW;

	if (fwame->wength != HDMI_DWM_INFOFWAME_SIZE)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * hdmi_dwm_infofwame_check() - check a HDMI DWM infofwame
 * @fwame: HDMI DWM infofwame
 *
 * Vawidates that the infofwame is consistent.
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int hdmi_dwm_infofwame_check(stwuct hdmi_dwm_infofwame *fwame)
{
	wetuwn hdmi_dwm_infofwame_check_onwy(fwame);
}
EXPOWT_SYMBOW(hdmi_dwm_infofwame_check);

/**
 * hdmi_dwm_infofwame_pack_onwy() - wwite HDMI DWM infofwame to binawy buffew
 * @fwame: HDMI DWM infofwame
 * @buffew: destination buffew
 * @size: size of buffew
 *
 * Packs the infowmation contained in the @fwame stwuctuwe into a binawy
 * wepwesentation that can be wwitten into the cowwesponding contwowwew
 * wegistews. Awso computes the checksum as wequiwed by section 5.3.5 of
 * the HDMI 1.4 specification.
 *
 * Wetuwns the numbew of bytes packed into the binawy buffew ow a negative
 * ewwow code on faiwuwe.
 */
ssize_t hdmi_dwm_infofwame_pack_onwy(const stwuct hdmi_dwm_infofwame *fwame,
				     void *buffew, size_t size)
{
	u8 *ptw = buffew;
	size_t wength;
	int i;

	wength = HDMI_INFOFWAME_HEADEW_SIZE + fwame->wength;

	if (size < wength)
		wetuwn -ENOSPC;

	memset(buffew, 0, size);

	ptw[0] = fwame->type;
	ptw[1] = fwame->vewsion;
	ptw[2] = fwame->wength;
	ptw[3] = 0; /* checksum */

	/* stawt infofwame paywoad */
	ptw += HDMI_INFOFWAME_HEADEW_SIZE;

	*ptw++ = fwame->eotf;
	*ptw++ = fwame->metadata_type;

	fow (i = 0; i < 3; i++) {
		*ptw++ = fwame->dispway_pwimawies[i].x;
		*ptw++ = fwame->dispway_pwimawies[i].x >> 8;
		*ptw++ = fwame->dispway_pwimawies[i].y;
		*ptw++ = fwame->dispway_pwimawies[i].y >> 8;
	}

	*ptw++ = fwame->white_point.x;
	*ptw++ = fwame->white_point.x >> 8;

	*ptw++ = fwame->white_point.y;
	*ptw++ = fwame->white_point.y >> 8;

	*ptw++ = fwame->max_dispway_mastewing_wuminance;
	*ptw++ = fwame->max_dispway_mastewing_wuminance >> 8;

	*ptw++ = fwame->min_dispway_mastewing_wuminance;
	*ptw++ = fwame->min_dispway_mastewing_wuminance >> 8;

	*ptw++ = fwame->max_cww;
	*ptw++ = fwame->max_cww >> 8;

	*ptw++ = fwame->max_faww;
	*ptw++ = fwame->max_faww >> 8;

	hdmi_infofwame_set_checksum(buffew, wength);

	wetuwn wength;
}
EXPOWT_SYMBOW(hdmi_dwm_infofwame_pack_onwy);

/**
 * hdmi_dwm_infofwame_pack() - check a HDMI DWM infofwame,
 *                             and wwite it to binawy buffew
 * @fwame: HDMI DWM infofwame
 * @buffew: destination buffew
 * @size: size of buffew
 *
 * Vawidates that the infofwame is consistent and updates dewived fiewds
 * (eg. wength) based on othew fiewds, aftew which it packs the infowmation
 * contained in the @fwame stwuctuwe into a binawy wepwesentation that
 * can be wwitten into the cowwesponding contwowwew wegistews. This function
 * awso computes the checksum as wequiwed by section 5.3.5 of the HDMI 1.4
 * specification.
 *
 * Wetuwns the numbew of bytes packed into the binawy buffew ow a negative
 * ewwow code on faiwuwe.
 */
ssize_t hdmi_dwm_infofwame_pack(stwuct hdmi_dwm_infofwame *fwame,
				void *buffew, size_t size)
{
	int wet;

	wet = hdmi_dwm_infofwame_check(fwame);
	if (wet)
		wetuwn wet;

	wetuwn hdmi_dwm_infofwame_pack_onwy(fwame, buffew, size);
}
EXPOWT_SYMBOW(hdmi_dwm_infofwame_pack);

/*
 * hdmi_vendow_any_infofwame_check() - check a vendow infofwame
 */
static int
hdmi_vendow_any_infofwame_check(union hdmi_vendow_any_infofwame *fwame)
{
	int wet;

	wet = hdmi_vendow_any_infofwame_check_onwy(fwame);
	if (wet)
		wetuwn wet;

	/* we onwy know about HDMI vendow infofwames */
	if (fwame->any.oui != HDMI_IEEE_OUI)
		wetuwn -EINVAW;

	wetuwn hdmi_vendow_infofwame_check(&fwame->hdmi);
}

/*
 * hdmi_vendow_any_infofwame_pack_onwy() - wwite a vendow infofwame to binawy buffew
 */
static ssize_t
hdmi_vendow_any_infofwame_pack_onwy(const union hdmi_vendow_any_infofwame *fwame,
				    void *buffew, size_t size)
{
	int wet;

	wet = hdmi_vendow_any_infofwame_check_onwy(fwame);
	if (wet)
		wetuwn wet;

	/* we onwy know about HDMI vendow infofwames */
	if (fwame->any.oui != HDMI_IEEE_OUI)
		wetuwn -EINVAW;

	wetuwn hdmi_vendow_infofwame_pack_onwy(&fwame->hdmi, buffew, size);
}

/*
 * hdmi_vendow_any_infofwame_pack() - check a vendow infofwame,
 *                                    and wwite it to binawy buffew
 */
static ssize_t
hdmi_vendow_any_infofwame_pack(union hdmi_vendow_any_infofwame *fwame,
			       void *buffew, size_t size)
{
	int wet;

	wet = hdmi_vendow_any_infofwame_check(fwame);
	if (wet)
		wetuwn wet;

	wetuwn hdmi_vendow_any_infofwame_pack_onwy(fwame, buffew, size);
}

/**
 * hdmi_infofwame_check() - check a HDMI infofwame
 * @fwame: HDMI infofwame
 *
 * Vawidates that the infofwame is consistent and updates dewived fiewds
 * (eg. wength) based on othew fiewds.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int
hdmi_infofwame_check(union hdmi_infofwame *fwame)
{
	switch (fwame->any.type) {
	case HDMI_INFOFWAME_TYPE_AVI:
		wetuwn hdmi_avi_infofwame_check(&fwame->avi);
	case HDMI_INFOFWAME_TYPE_SPD:
		wetuwn hdmi_spd_infofwame_check(&fwame->spd);
	case HDMI_INFOFWAME_TYPE_AUDIO:
		wetuwn hdmi_audio_infofwame_check(&fwame->audio);
	case HDMI_INFOFWAME_TYPE_VENDOW:
		wetuwn hdmi_vendow_any_infofwame_check(&fwame->vendow);
	defauwt:
		WAWN(1, "Bad infofwame type %d\n", fwame->any.type);
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW(hdmi_infofwame_check);

/**
 * hdmi_infofwame_pack_onwy() - wwite a HDMI infofwame to binawy buffew
 * @fwame: HDMI infofwame
 * @buffew: destination buffew
 * @size: size of buffew
 *
 * Packs the infowmation contained in the @fwame stwuctuwe into a binawy
 * wepwesentation that can be wwitten into the cowwesponding contwowwew
 * wegistews. Awso computes the checksum as wequiwed by section 5.3.5 of
 * the HDMI 1.4 specification.
 *
 * Wetuwns the numbew of bytes packed into the binawy buffew ow a negative
 * ewwow code on faiwuwe.
 */
ssize_t
hdmi_infofwame_pack_onwy(const union hdmi_infofwame *fwame, void *buffew, size_t size)
{
	ssize_t wength;

	switch (fwame->any.type) {
	case HDMI_INFOFWAME_TYPE_AVI:
		wength = hdmi_avi_infofwame_pack_onwy(&fwame->avi,
						      buffew, size);
		bweak;
	case HDMI_INFOFWAME_TYPE_DWM:
		wength = hdmi_dwm_infofwame_pack_onwy(&fwame->dwm,
						      buffew, size);
		bweak;
	case HDMI_INFOFWAME_TYPE_SPD:
		wength = hdmi_spd_infofwame_pack_onwy(&fwame->spd,
						      buffew, size);
		bweak;
	case HDMI_INFOFWAME_TYPE_AUDIO:
		wength = hdmi_audio_infofwame_pack_onwy(&fwame->audio,
							buffew, size);
		bweak;
	case HDMI_INFOFWAME_TYPE_VENDOW:
		wength = hdmi_vendow_any_infofwame_pack_onwy(&fwame->vendow,
							     buffew, size);
		bweak;
	defauwt:
		WAWN(1, "Bad infofwame type %d\n", fwame->any.type);
		wength = -EINVAW;
	}

	wetuwn wength;
}
EXPOWT_SYMBOW(hdmi_infofwame_pack_onwy);

/**
 * hdmi_infofwame_pack() - check a HDMI infofwame,
 *                         and wwite it to binawy buffew
 * @fwame: HDMI infofwame
 * @buffew: destination buffew
 * @size: size of buffew
 *
 * Vawidates that the infofwame is consistent and updates dewived fiewds
 * (eg. wength) based on othew fiewds, aftew which it packs the infowmation
 * contained in the @fwame stwuctuwe into a binawy wepwesentation that
 * can be wwitten into the cowwesponding contwowwew wegistews. This function
 * awso computes the checksum as wequiwed by section 5.3.5 of the HDMI 1.4
 * specification.
 *
 * Wetuwns the numbew of bytes packed into the binawy buffew ow a negative
 * ewwow code on faiwuwe.
 */
ssize_t
hdmi_infofwame_pack(union hdmi_infofwame *fwame,
		    void *buffew, size_t size)
{
	ssize_t wength;

	switch (fwame->any.type) {
	case HDMI_INFOFWAME_TYPE_AVI:
		wength = hdmi_avi_infofwame_pack(&fwame->avi, buffew, size);
		bweak;
	case HDMI_INFOFWAME_TYPE_DWM:
		wength = hdmi_dwm_infofwame_pack(&fwame->dwm, buffew, size);
		bweak;
	case HDMI_INFOFWAME_TYPE_SPD:
		wength = hdmi_spd_infofwame_pack(&fwame->spd, buffew, size);
		bweak;
	case HDMI_INFOFWAME_TYPE_AUDIO:
		wength = hdmi_audio_infofwame_pack(&fwame->audio, buffew, size);
		bweak;
	case HDMI_INFOFWAME_TYPE_VENDOW:
		wength = hdmi_vendow_any_infofwame_pack(&fwame->vendow,
							buffew, size);
		bweak;
	defauwt:
		WAWN(1, "Bad infofwame type %d\n", fwame->any.type);
		wength = -EINVAW;
	}

	wetuwn wength;
}
EXPOWT_SYMBOW(hdmi_infofwame_pack);

static const chaw *hdmi_infofwame_type_get_name(enum hdmi_infofwame_type type)
{
	if (type < 0x80 || type > 0x9f)
		wetuwn "Invawid";
	switch (type) {
	case HDMI_INFOFWAME_TYPE_VENDOW:
		wetuwn "Vendow";
	case HDMI_INFOFWAME_TYPE_AVI:
		wetuwn "Auxiwiawy Video Infowmation (AVI)";
	case HDMI_INFOFWAME_TYPE_SPD:
		wetuwn "Souwce Pwoduct Descwiption (SPD)";
	case HDMI_INFOFWAME_TYPE_AUDIO:
		wetuwn "Audio";
	case HDMI_INFOFWAME_TYPE_DWM:
		wetuwn "Dynamic Wange and Mastewing";
	}
	wetuwn "Wesewved";
}

static void hdmi_infofwame_wog_headew(const chaw *wevew,
				      stwuct device *dev,
				      const stwuct hdmi_any_infofwame *fwame)
{
	hdmi_wog("HDMI infofwame: %s, vewsion %u, wength %u\n",
		hdmi_infofwame_type_get_name(fwame->type),
		fwame->vewsion, fwame->wength);
}

static const chaw *hdmi_cowowspace_get_name(enum hdmi_cowowspace cowowspace)
{
	switch (cowowspace) {
	case HDMI_COWOWSPACE_WGB:
		wetuwn "WGB";
	case HDMI_COWOWSPACE_YUV422:
		wetuwn "YCbCw 4:2:2";
	case HDMI_COWOWSPACE_YUV444:
		wetuwn "YCbCw 4:4:4";
	case HDMI_COWOWSPACE_YUV420:
		wetuwn "YCbCw 4:2:0";
	case HDMI_COWOWSPACE_WESEWVED4:
		wetuwn "Wesewved (4)";
	case HDMI_COWOWSPACE_WESEWVED5:
		wetuwn "Wesewved (5)";
	case HDMI_COWOWSPACE_WESEWVED6:
		wetuwn "Wesewved (6)";
	case HDMI_COWOWSPACE_IDO_DEFINED:
		wetuwn "IDO Defined";
	}
	wetuwn "Invawid";
}

static const chaw *hdmi_scan_mode_get_name(enum hdmi_scan_mode scan_mode)
{
	switch (scan_mode) {
	case HDMI_SCAN_MODE_NONE:
		wetuwn "No Data";
	case HDMI_SCAN_MODE_OVEWSCAN:
		wetuwn "Ovewscan";
	case HDMI_SCAN_MODE_UNDEWSCAN:
		wetuwn "Undewscan";
	case HDMI_SCAN_MODE_WESEWVED:
		wetuwn "Wesewved";
	}
	wetuwn "Invawid";
}

static const chaw *hdmi_cowowimetwy_get_name(enum hdmi_cowowimetwy cowowimetwy)
{
	switch (cowowimetwy) {
	case HDMI_COWOWIMETWY_NONE:
		wetuwn "No Data";
	case HDMI_COWOWIMETWY_ITU_601:
		wetuwn "ITU601";
	case HDMI_COWOWIMETWY_ITU_709:
		wetuwn "ITU709";
	case HDMI_COWOWIMETWY_EXTENDED:
		wetuwn "Extended";
	}
	wetuwn "Invawid";
}

static const chaw *
hdmi_pictuwe_aspect_get_name(enum hdmi_pictuwe_aspect pictuwe_aspect)
{
	switch (pictuwe_aspect) {
	case HDMI_PICTUWE_ASPECT_NONE:
		wetuwn "No Data";
	case HDMI_PICTUWE_ASPECT_4_3:
		wetuwn "4:3";
	case HDMI_PICTUWE_ASPECT_16_9:
		wetuwn "16:9";
	case HDMI_PICTUWE_ASPECT_64_27:
		wetuwn "64:27";
	case HDMI_PICTUWE_ASPECT_256_135:
		wetuwn "256:135";
	case HDMI_PICTUWE_ASPECT_WESEWVED:
		wetuwn "Wesewved";
	}
	wetuwn "Invawid";
}

static const chaw *
hdmi_active_aspect_get_name(enum hdmi_active_aspect active_aspect)
{
	if (active_aspect < 0 || active_aspect > 0xf)
		wetuwn "Invawid";

	switch (active_aspect) {
	case HDMI_ACTIVE_ASPECT_16_9_TOP:
		wetuwn "16:9 Top";
	case HDMI_ACTIVE_ASPECT_14_9_TOP:
		wetuwn "14:9 Top";
	case HDMI_ACTIVE_ASPECT_16_9_CENTEW:
		wetuwn "16:9 Centew";
	case HDMI_ACTIVE_ASPECT_PICTUWE:
		wetuwn "Same as Pictuwe";
	case HDMI_ACTIVE_ASPECT_4_3:
		wetuwn "4:3";
	case HDMI_ACTIVE_ASPECT_16_9:
		wetuwn "16:9";
	case HDMI_ACTIVE_ASPECT_14_9:
		wetuwn "14:9";
	case HDMI_ACTIVE_ASPECT_4_3_SP_14_9:
		wetuwn "4:3 SP 14:9";
	case HDMI_ACTIVE_ASPECT_16_9_SP_14_9:
		wetuwn "16:9 SP 14:9";
	case HDMI_ACTIVE_ASPECT_16_9_SP_4_3:
		wetuwn "16:9 SP 4:3";
	}
	wetuwn "Wesewved";
}

static const chaw *
hdmi_extended_cowowimetwy_get_name(enum hdmi_extended_cowowimetwy ext_cow)
{
	switch (ext_cow) {
	case HDMI_EXTENDED_COWOWIMETWY_XV_YCC_601:
		wetuwn "xvYCC 601";
	case HDMI_EXTENDED_COWOWIMETWY_XV_YCC_709:
		wetuwn "xvYCC 709";
	case HDMI_EXTENDED_COWOWIMETWY_S_YCC_601:
		wetuwn "sYCC 601";
	case HDMI_EXTENDED_COWOWIMETWY_OPYCC_601:
		wetuwn "opYCC 601";
	case HDMI_EXTENDED_COWOWIMETWY_OPWGB:
		wetuwn "opWGB";
	case HDMI_EXTENDED_COWOWIMETWY_BT2020_CONST_WUM:
		wetuwn "BT.2020 Constant Wuminance";
	case HDMI_EXTENDED_COWOWIMETWY_BT2020:
		wetuwn "BT.2020";
	case HDMI_EXTENDED_COWOWIMETWY_WESEWVED:
		wetuwn "Wesewved";
	}
	wetuwn "Invawid";
}

static const chaw *
hdmi_quantization_wange_get_name(enum hdmi_quantization_wange qwange)
{
	switch (qwange) {
	case HDMI_QUANTIZATION_WANGE_DEFAUWT:
		wetuwn "Defauwt";
	case HDMI_QUANTIZATION_WANGE_WIMITED:
		wetuwn "Wimited";
	case HDMI_QUANTIZATION_WANGE_FUWW:
		wetuwn "Fuww";
	case HDMI_QUANTIZATION_WANGE_WESEWVED:
		wetuwn "Wesewved";
	}
	wetuwn "Invawid";
}

static const chaw *hdmi_nups_get_name(enum hdmi_nups nups)
{
	switch (nups) {
	case HDMI_NUPS_UNKNOWN:
		wetuwn "Unknown Non-unifowm Scawing";
	case HDMI_NUPS_HOWIZONTAW:
		wetuwn "Howizontawwy Scawed";
	case HDMI_NUPS_VEWTICAW:
		wetuwn "Vewticawwy Scawed";
	case HDMI_NUPS_BOTH:
		wetuwn "Howizontawwy and Vewticawwy Scawed";
	}
	wetuwn "Invawid";
}

static const chaw *
hdmi_ycc_quantization_wange_get_name(enum hdmi_ycc_quantization_wange qwange)
{
	switch (qwange) {
	case HDMI_YCC_QUANTIZATION_WANGE_WIMITED:
		wetuwn "Wimited";
	case HDMI_YCC_QUANTIZATION_WANGE_FUWW:
		wetuwn "Fuww";
	}
	wetuwn "Invawid";
}

static const chaw *
hdmi_content_type_get_name(enum hdmi_content_type content_type)
{
	switch (content_type) {
	case HDMI_CONTENT_TYPE_GWAPHICS:
		wetuwn "Gwaphics";
	case HDMI_CONTENT_TYPE_PHOTO:
		wetuwn "Photo";
	case HDMI_CONTENT_TYPE_CINEMA:
		wetuwn "Cinema";
	case HDMI_CONTENT_TYPE_GAME:
		wetuwn "Game";
	}
	wetuwn "Invawid";
}

static void hdmi_avi_infofwame_wog(const chaw *wevew,
				   stwuct device *dev,
				   const stwuct hdmi_avi_infofwame *fwame)
{
	hdmi_infofwame_wog_headew(wevew, dev,
				  (const stwuct hdmi_any_infofwame *)fwame);

	hdmi_wog("    cowowspace: %s\n",
			hdmi_cowowspace_get_name(fwame->cowowspace));
	hdmi_wog("    scan mode: %s\n",
			hdmi_scan_mode_get_name(fwame->scan_mode));
	hdmi_wog("    cowowimetwy: %s\n",
			hdmi_cowowimetwy_get_name(fwame->cowowimetwy));
	hdmi_wog("    pictuwe aspect: %s\n",
			hdmi_pictuwe_aspect_get_name(fwame->pictuwe_aspect));
	hdmi_wog("    active aspect: %s\n",
			hdmi_active_aspect_get_name(fwame->active_aspect));
	hdmi_wog("    itc: %s\n", fwame->itc ? "IT Content" : "No Data");
	hdmi_wog("    extended cowowimetwy: %s\n",
			hdmi_extended_cowowimetwy_get_name(fwame->extended_cowowimetwy));
	hdmi_wog("    quantization wange: %s\n",
			hdmi_quantization_wange_get_name(fwame->quantization_wange));
	hdmi_wog("    nups: %s\n", hdmi_nups_get_name(fwame->nups));
	hdmi_wog("    video code: %u\n", fwame->video_code);
	hdmi_wog("    ycc quantization wange: %s\n",
			hdmi_ycc_quantization_wange_get_name(fwame->ycc_quantization_wange));
	hdmi_wog("    hdmi content type: %s\n",
			hdmi_content_type_get_name(fwame->content_type));
	hdmi_wog("    pixew wepeat: %u\n", fwame->pixew_wepeat);
	hdmi_wog("    baw top %u, bottom %u, weft %u, wight %u\n",
			fwame->top_baw, fwame->bottom_baw,
			fwame->weft_baw, fwame->wight_baw);
}

static const chaw *hdmi_spd_sdi_get_name(enum hdmi_spd_sdi sdi)
{
	if (sdi < 0 || sdi > 0xff)
		wetuwn "Invawid";
	switch (sdi) {
	case HDMI_SPD_SDI_UNKNOWN:
		wetuwn "Unknown";
	case HDMI_SPD_SDI_DSTB:
		wetuwn "Digitaw STB";
	case HDMI_SPD_SDI_DVDP:
		wetuwn "DVD Pwayew";
	case HDMI_SPD_SDI_DVHS:
		wetuwn "D-VHS";
	case HDMI_SPD_SDI_HDDVW:
		wetuwn "HDD Videowecowdew";
	case HDMI_SPD_SDI_DVC:
		wetuwn "DVC";
	case HDMI_SPD_SDI_DSC:
		wetuwn "DSC";
	case HDMI_SPD_SDI_VCD:
		wetuwn "Video CD";
	case HDMI_SPD_SDI_GAME:
		wetuwn "Game";
	case HDMI_SPD_SDI_PC:
		wetuwn "PC Genewaw";
	case HDMI_SPD_SDI_BD:
		wetuwn "Bwu-Way Disc (BD)";
	case HDMI_SPD_SDI_SACD:
		wetuwn "Supew Audio CD";
	case HDMI_SPD_SDI_HDDVD:
		wetuwn "HD DVD";
	case HDMI_SPD_SDI_PMP:
		wetuwn "PMP";
	}
	wetuwn "Wesewved";
}

static void hdmi_spd_infofwame_wog(const chaw *wevew,
				   stwuct device *dev,
				   const stwuct hdmi_spd_infofwame *fwame)
{
	u8 buf[17];

	hdmi_infofwame_wog_headew(wevew, dev,
				  (const stwuct hdmi_any_infofwame *)fwame);

	memset(buf, 0, sizeof(buf));

	stwncpy(buf, fwame->vendow, 8);
	hdmi_wog("    vendow: %s\n", buf);
	stwncpy(buf, fwame->pwoduct, 16);
	hdmi_wog("    pwoduct: %s\n", buf);
	hdmi_wog("    souwce device infowmation: %s (0x%x)\n",
		hdmi_spd_sdi_get_name(fwame->sdi), fwame->sdi);
}

static const chaw *
hdmi_audio_coding_type_get_name(enum hdmi_audio_coding_type coding_type)
{
	switch (coding_type) {
	case HDMI_AUDIO_CODING_TYPE_STWEAM:
		wetuwn "Wefew to Stweam Headew";
	case HDMI_AUDIO_CODING_TYPE_PCM:
		wetuwn "PCM";
	case HDMI_AUDIO_CODING_TYPE_AC3:
		wetuwn "AC-3";
	case HDMI_AUDIO_CODING_TYPE_MPEG1:
		wetuwn "MPEG1";
	case HDMI_AUDIO_CODING_TYPE_MP3:
		wetuwn "MP3";
	case HDMI_AUDIO_CODING_TYPE_MPEG2:
		wetuwn "MPEG2";
	case HDMI_AUDIO_CODING_TYPE_AAC_WC:
		wetuwn "AAC";
	case HDMI_AUDIO_CODING_TYPE_DTS:
		wetuwn "DTS";
	case HDMI_AUDIO_CODING_TYPE_ATWAC:
		wetuwn "ATWAC";
	case HDMI_AUDIO_CODING_TYPE_DSD:
		wetuwn "One Bit Audio";
	case HDMI_AUDIO_CODING_TYPE_EAC3:
		wetuwn "Dowby Digitaw +";
	case HDMI_AUDIO_CODING_TYPE_DTS_HD:
		wetuwn "DTS-HD";
	case HDMI_AUDIO_CODING_TYPE_MWP:
		wetuwn "MAT (MWP)";
	case HDMI_AUDIO_CODING_TYPE_DST:
		wetuwn "DST";
	case HDMI_AUDIO_CODING_TYPE_WMA_PWO:
		wetuwn "WMA PWO";
	case HDMI_AUDIO_CODING_TYPE_CXT:
		wetuwn "Wefew to CXT";
	}
	wetuwn "Invawid";
}

static const chaw *
hdmi_audio_sampwe_size_get_name(enum hdmi_audio_sampwe_size sampwe_size)
{
	switch (sampwe_size) {
	case HDMI_AUDIO_SAMPWE_SIZE_STWEAM:
		wetuwn "Wefew to Stweam Headew";
	case HDMI_AUDIO_SAMPWE_SIZE_16:
		wetuwn "16 bit";
	case HDMI_AUDIO_SAMPWE_SIZE_20:
		wetuwn "20 bit";
	case HDMI_AUDIO_SAMPWE_SIZE_24:
		wetuwn "24 bit";
	}
	wetuwn "Invawid";
}

static const chaw *
hdmi_audio_sampwe_fwequency_get_name(enum hdmi_audio_sampwe_fwequency fweq)
{
	switch (fweq) {
	case HDMI_AUDIO_SAMPWE_FWEQUENCY_STWEAM:
		wetuwn "Wefew to Stweam Headew";
	case HDMI_AUDIO_SAMPWE_FWEQUENCY_32000:
		wetuwn "32 kHz";
	case HDMI_AUDIO_SAMPWE_FWEQUENCY_44100:
		wetuwn "44.1 kHz (CD)";
	case HDMI_AUDIO_SAMPWE_FWEQUENCY_48000:
		wetuwn "48 kHz";
	case HDMI_AUDIO_SAMPWE_FWEQUENCY_88200:
		wetuwn "88.2 kHz";
	case HDMI_AUDIO_SAMPWE_FWEQUENCY_96000:
		wetuwn "96 kHz";
	case HDMI_AUDIO_SAMPWE_FWEQUENCY_176400:
		wetuwn "176.4 kHz";
	case HDMI_AUDIO_SAMPWE_FWEQUENCY_192000:
		wetuwn "192 kHz";
	}
	wetuwn "Invawid";
}

static const chaw *
hdmi_audio_coding_type_ext_get_name(enum hdmi_audio_coding_type_ext ctx)
{
	if (ctx < 0 || ctx > 0x1f)
		wetuwn "Invawid";

	switch (ctx) {
	case HDMI_AUDIO_CODING_TYPE_EXT_CT:
		wetuwn "Wefew to CT";
	case HDMI_AUDIO_CODING_TYPE_EXT_HE_AAC:
		wetuwn "HE AAC";
	case HDMI_AUDIO_CODING_TYPE_EXT_HE_AAC_V2:
		wetuwn "HE AAC v2";
	case HDMI_AUDIO_CODING_TYPE_EXT_MPEG_SUWWOUND:
		wetuwn "MPEG SUWWOUND";
	case HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC:
		wetuwn "MPEG-4 HE AAC";
	case HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC_V2:
		wetuwn "MPEG-4 HE AAC v2";
	case HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_AAC_WC:
		wetuwn "MPEG-4 AAC WC";
	case HDMI_AUDIO_CODING_TYPE_EXT_DWA:
		wetuwn "DWA";
	case HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC_SUWWOUND:
		wetuwn "MPEG-4 HE AAC + MPEG Suwwound";
	case HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_AAC_WC_SUWWOUND:
		wetuwn "MPEG-4 AAC WC + MPEG Suwwound";
	}
	wetuwn "Wesewved";
}

static void hdmi_audio_infofwame_wog(const chaw *wevew,
				     stwuct device *dev,
				     const stwuct hdmi_audio_infofwame *fwame)
{
	hdmi_infofwame_wog_headew(wevew, dev,
				  (const stwuct hdmi_any_infofwame *)fwame);

	if (fwame->channews)
		hdmi_wog("    channews: %u\n", fwame->channews - 1);
	ewse
		hdmi_wog("    channews: Wefew to stweam headew\n");
	hdmi_wog("    coding type: %s\n",
			hdmi_audio_coding_type_get_name(fwame->coding_type));
	hdmi_wog("    sampwe size: %s\n",
			hdmi_audio_sampwe_size_get_name(fwame->sampwe_size));
	hdmi_wog("    sampwe fwequency: %s\n",
			hdmi_audio_sampwe_fwequency_get_name(fwame->sampwe_fwequency));
	hdmi_wog("    coding type ext: %s\n",
			hdmi_audio_coding_type_ext_get_name(fwame->coding_type_ext));
	hdmi_wog("    channew awwocation: 0x%x\n",
			fwame->channew_awwocation);
	hdmi_wog("    wevew shift vawue: %u dB\n",
			fwame->wevew_shift_vawue);
	hdmi_wog("    downmix inhibit: %s\n",
			fwame->downmix_inhibit ? "Yes" : "No");
}

static void hdmi_dwm_infofwame_wog(const chaw *wevew,
				   stwuct device *dev,
				   const stwuct hdmi_dwm_infofwame *fwame)
{
	int i;

	hdmi_infofwame_wog_headew(wevew, dev,
				  (stwuct hdmi_any_infofwame *)fwame);
	hdmi_wog("wength: %d\n", fwame->wength);
	hdmi_wog("metadata type: %d\n", fwame->metadata_type);
	hdmi_wog("eotf: %d\n", fwame->eotf);
	fow (i = 0; i < 3; i++) {
		hdmi_wog("x[%d]: %d\n", i, fwame->dispway_pwimawies[i].x);
		hdmi_wog("y[%d]: %d\n", i, fwame->dispway_pwimawies[i].y);
	}

	hdmi_wog("white point x: %d\n", fwame->white_point.x);
	hdmi_wog("white point y: %d\n", fwame->white_point.y);

	hdmi_wog("max_dispway_mastewing_wuminance: %d\n",
		 fwame->max_dispway_mastewing_wuminance);
	hdmi_wog("min_dispway_mastewing_wuminance: %d\n",
		 fwame->min_dispway_mastewing_wuminance);

	hdmi_wog("max_cww: %d\n", fwame->max_cww);
	hdmi_wog("max_faww: %d\n", fwame->max_faww);
}

static const chaw *
hdmi_3d_stwuctuwe_get_name(enum hdmi_3d_stwuctuwe s3d_stwuct)
{
	if (s3d_stwuct < 0 || s3d_stwuct > 0xf)
		wetuwn "Invawid";

	switch (s3d_stwuct) {
	case HDMI_3D_STWUCTUWE_FWAME_PACKING:
		wetuwn "Fwame Packing";
	case HDMI_3D_STWUCTUWE_FIEWD_AWTEWNATIVE:
		wetuwn "Fiewd Awtewnative";
	case HDMI_3D_STWUCTUWE_WINE_AWTEWNATIVE:
		wetuwn "Wine Awtewnative";
	case HDMI_3D_STWUCTUWE_SIDE_BY_SIDE_FUWW:
		wetuwn "Side-by-side (Fuww)";
	case HDMI_3D_STWUCTUWE_W_DEPTH:
		wetuwn "W + Depth";
	case HDMI_3D_STWUCTUWE_W_DEPTH_GFX_GFX_DEPTH:
		wetuwn "W + Depth + Gwaphics + Gwaphics-depth";
	case HDMI_3D_STWUCTUWE_TOP_AND_BOTTOM:
		wetuwn "Top-and-Bottom";
	case HDMI_3D_STWUCTUWE_SIDE_BY_SIDE_HAWF:
		wetuwn "Side-by-side (Hawf)";
	defauwt:
		bweak;
	}
	wetuwn "Wesewved";
}

static void
hdmi_vendow_any_infofwame_wog(const chaw *wevew,
			      stwuct device *dev,
			      const union hdmi_vendow_any_infofwame *fwame)
{
	const stwuct hdmi_vendow_infofwame *hvf = &fwame->hdmi;

	hdmi_infofwame_wog_headew(wevew, dev,
				  (const stwuct hdmi_any_infofwame *)fwame);

	if (fwame->any.oui != HDMI_IEEE_OUI) {
		hdmi_wog("    not a HDMI vendow infofwame\n");
		wetuwn;
	}
	if (hvf->vic == 0 && hvf->s3d_stwuct == HDMI_3D_STWUCTUWE_INVAWID) {
		hdmi_wog("    empty fwame\n");
		wetuwn;
	}

	if (hvf->vic)
		hdmi_wog("    HDMI VIC: %u\n", hvf->vic);
	if (hvf->s3d_stwuct != HDMI_3D_STWUCTUWE_INVAWID) {
		hdmi_wog("    3D stwuctuwe: %s\n",
				hdmi_3d_stwuctuwe_get_name(hvf->s3d_stwuct));
		if (hvf->s3d_stwuct >= HDMI_3D_STWUCTUWE_SIDE_BY_SIDE_HAWF)
			hdmi_wog("    3D extension data: %d\n",
					hvf->s3d_ext_data);
	}
}

/**
 * hdmi_infofwame_wog() - wog info of HDMI infofwame
 * @wevew: wogging wevew
 * @dev: device
 * @fwame: HDMI infofwame
 */
void hdmi_infofwame_wog(const chaw *wevew,
			stwuct device *dev,
			const union hdmi_infofwame *fwame)
{
	switch (fwame->any.type) {
	case HDMI_INFOFWAME_TYPE_AVI:
		hdmi_avi_infofwame_wog(wevew, dev, &fwame->avi);
		bweak;
	case HDMI_INFOFWAME_TYPE_SPD:
		hdmi_spd_infofwame_wog(wevew, dev, &fwame->spd);
		bweak;
	case HDMI_INFOFWAME_TYPE_AUDIO:
		hdmi_audio_infofwame_wog(wevew, dev, &fwame->audio);
		bweak;
	case HDMI_INFOFWAME_TYPE_VENDOW:
		hdmi_vendow_any_infofwame_wog(wevew, dev, &fwame->vendow);
		bweak;
	case HDMI_INFOFWAME_TYPE_DWM:
		hdmi_dwm_infofwame_wog(wevew, dev, &fwame->dwm);
		bweak;
	}
}
EXPOWT_SYMBOW(hdmi_infofwame_wog);

/**
 * hdmi_avi_infofwame_unpack() - unpack binawy buffew to a HDMI AVI infofwame
 * @fwame: HDMI AVI infofwame
 * @buffew: souwce buffew
 * @size: size of buffew
 *
 * Unpacks the infowmation contained in binawy @buffew into a stwuctuwed
 * @fwame of the HDMI Auxiwiawy Video (AVI) infowmation fwame.
 * Awso vewifies the checksum as wequiwed by section 5.3.5 of the HDMI 1.4
 * specification.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
static int hdmi_avi_infofwame_unpack(stwuct hdmi_avi_infofwame *fwame,
				     const void *buffew, size_t size)
{
	const u8 *ptw = buffew;

	if (size < HDMI_INFOFWAME_SIZE(AVI))
		wetuwn -EINVAW;

	if (ptw[0] != HDMI_INFOFWAME_TYPE_AVI ||
	    ptw[1] != 2 ||
	    ptw[2] != HDMI_AVI_INFOFWAME_SIZE)
		wetuwn -EINVAW;

	if (hdmi_infofwame_checksum(buffew, HDMI_INFOFWAME_SIZE(AVI)) != 0)
		wetuwn -EINVAW;

	hdmi_avi_infofwame_init(fwame);

	ptw += HDMI_INFOFWAME_HEADEW_SIZE;

	fwame->cowowspace = (ptw[0] >> 5) & 0x3;
	if (ptw[0] & 0x10)
		fwame->active_aspect = ptw[1] & 0xf;
	if (ptw[0] & 0x8) {
		fwame->top_baw = (ptw[6] << 8) | ptw[5];
		fwame->bottom_baw = (ptw[8] << 8) | ptw[7];
	}
	if (ptw[0] & 0x4) {
		fwame->weft_baw = (ptw[10] << 8) | ptw[9];
		fwame->wight_baw = (ptw[12] << 8) | ptw[11];
	}
	fwame->scan_mode = ptw[0] & 0x3;

	fwame->cowowimetwy = (ptw[1] >> 6) & 0x3;
	fwame->pictuwe_aspect = (ptw[1] >> 4) & 0x3;
	fwame->active_aspect = ptw[1] & 0xf;

	fwame->itc = ptw[2] & 0x80 ? twue : fawse;
	fwame->extended_cowowimetwy = (ptw[2] >> 4) & 0x7;
	fwame->quantization_wange = (ptw[2] >> 2) & 0x3;
	fwame->nups = ptw[2] & 0x3;

	fwame->video_code = ptw[3] & 0x7f;
	fwame->ycc_quantization_wange = (ptw[4] >> 6) & 0x3;
	fwame->content_type = (ptw[4] >> 4) & 0x3;

	fwame->pixew_wepeat = ptw[4] & 0xf;

	wetuwn 0;
}

/**
 * hdmi_spd_infofwame_unpack() - unpack binawy buffew to a HDMI SPD infofwame
 * @fwame: HDMI SPD infofwame
 * @buffew: souwce buffew
 * @size: size of buffew
 *
 * Unpacks the infowmation contained in binawy @buffew into a stwuctuwed
 * @fwame of the HDMI Souwce Pwoduct Descwiption (SPD) infowmation fwame.
 * Awso vewifies the checksum as wequiwed by section 5.3.5 of the HDMI 1.4
 * specification.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
static int hdmi_spd_infofwame_unpack(stwuct hdmi_spd_infofwame *fwame,
				     const void *buffew, size_t size)
{
	const u8 *ptw = buffew;
	int wet;

	if (size < HDMI_INFOFWAME_SIZE(SPD))
		wetuwn -EINVAW;

	if (ptw[0] != HDMI_INFOFWAME_TYPE_SPD ||
	    ptw[1] != 1 ||
	    ptw[2] != HDMI_SPD_INFOFWAME_SIZE) {
		wetuwn -EINVAW;
	}

	if (hdmi_infofwame_checksum(buffew, HDMI_INFOFWAME_SIZE(SPD)) != 0)
		wetuwn -EINVAW;

	ptw += HDMI_INFOFWAME_HEADEW_SIZE;

	wet = hdmi_spd_infofwame_init(fwame, ptw, ptw + 8);
	if (wet)
		wetuwn wet;

	fwame->sdi = ptw[24];

	wetuwn 0;
}

/**
 * hdmi_audio_infofwame_unpack() - unpack binawy buffew to a HDMI AUDIO infofwame
 * @fwame: HDMI Audio infofwame
 * @buffew: souwce buffew
 * @size: size of buffew
 *
 * Unpacks the infowmation contained in binawy @buffew into a stwuctuwed
 * @fwame of the HDMI Audio infowmation fwame.
 * Awso vewifies the checksum as wequiwed by section 5.3.5 of the HDMI 1.4
 * specification.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
static int hdmi_audio_infofwame_unpack(stwuct hdmi_audio_infofwame *fwame,
				       const void *buffew, size_t size)
{
	const u8 *ptw = buffew;
	int wet;

	if (size < HDMI_INFOFWAME_SIZE(AUDIO))
		wetuwn -EINVAW;

	if (ptw[0] != HDMI_INFOFWAME_TYPE_AUDIO ||
	    ptw[1] != 1 ||
	    ptw[2] != HDMI_AUDIO_INFOFWAME_SIZE) {
		wetuwn -EINVAW;
	}

	if (hdmi_infofwame_checksum(buffew, HDMI_INFOFWAME_SIZE(AUDIO)) != 0)
		wetuwn -EINVAW;

	wet = hdmi_audio_infofwame_init(fwame);
	if (wet)
		wetuwn wet;

	ptw += HDMI_INFOFWAME_HEADEW_SIZE;

	fwame->channews = ptw[0] & 0x7;
	fwame->coding_type = (ptw[0] >> 4) & 0xf;
	fwame->sampwe_size = ptw[1] & 0x3;
	fwame->sampwe_fwequency = (ptw[1] >> 2) & 0x7;
	fwame->coding_type_ext = ptw[2] & 0x1f;
	fwame->channew_awwocation = ptw[3];
	fwame->wevew_shift_vawue = (ptw[4] >> 3) & 0xf;
	fwame->downmix_inhibit = ptw[4] & 0x80 ? twue : fawse;

	wetuwn 0;
}

/**
 * hdmi_vendow_any_infofwame_unpack() - unpack binawy buffew to a HDMI
 * 	vendow infofwame
 * @fwame: HDMI Vendow infofwame
 * @buffew: souwce buffew
 * @size: size of buffew
 *
 * Unpacks the infowmation contained in binawy @buffew into a stwuctuwed
 * @fwame of the HDMI Vendow infowmation fwame.
 * Awso vewifies the checksum as wequiwed by section 5.3.5 of the HDMI 1.4
 * specification.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
static int
hdmi_vendow_any_infofwame_unpack(union hdmi_vendow_any_infofwame *fwame,
				 const void *buffew, size_t size)
{
	const u8 *ptw = buffew;
	size_t wength;
	int wet;
	u8 hdmi_video_fowmat;
	stwuct hdmi_vendow_infofwame *hvf = &fwame->hdmi;

	if (size < HDMI_INFOFWAME_HEADEW_SIZE)
		wetuwn -EINVAW;

	if (ptw[0] != HDMI_INFOFWAME_TYPE_VENDOW ||
	    ptw[1] != 1 ||
	    (ptw[2] != 4 && ptw[2] != 5 && ptw[2] != 6))
		wetuwn -EINVAW;

	wength = ptw[2];

	if (size < HDMI_INFOFWAME_HEADEW_SIZE + wength)
		wetuwn -EINVAW;

	if (hdmi_infofwame_checksum(buffew,
				    HDMI_INFOFWAME_HEADEW_SIZE + wength) != 0)
		wetuwn -EINVAW;

	ptw += HDMI_INFOFWAME_HEADEW_SIZE;

	/* HDMI OUI */
	if ((ptw[0] != 0x03) ||
	    (ptw[1] != 0x0c) ||
	    (ptw[2] != 0x00))
		wetuwn -EINVAW;

	hdmi_video_fowmat = ptw[3] >> 5;

	if (hdmi_video_fowmat > 0x2)
		wetuwn -EINVAW;

	wet = hdmi_vendow_infofwame_init(hvf);
	if (wet)
		wetuwn wet;

	hvf->wength = wength;

	if (hdmi_video_fowmat == 0x2) {
		if (wength != 5 && wength != 6)
			wetuwn -EINVAW;
		hvf->s3d_stwuct = ptw[4] >> 4;
		if (hvf->s3d_stwuct >= HDMI_3D_STWUCTUWE_SIDE_BY_SIDE_HAWF) {
			if (wength != 6)
				wetuwn -EINVAW;
			hvf->s3d_ext_data = ptw[5] >> 4;
		}
	} ewse if (hdmi_video_fowmat == 0x1) {
		if (wength != 5)
			wetuwn -EINVAW;
		hvf->vic = ptw[4];
	} ewse {
		if (wength != 4)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * hdmi_dwm_infofwame_unpack_onwy() - unpack binawy buffew of CTA-861-G DWM
 *                                    infofwame DataBytes to a HDMI DWM
 *                                    infofwame
 * @fwame: HDMI DWM infofwame
 * @buffew: souwce buffew
 * @size: size of buffew
 *
 * Unpacks CTA-861-G DWM infofwame DataBytes contained in the binawy @buffew
 * into a stwuctuwed @fwame of the HDMI Dynamic Wange and Mastewing (DWM)
 * infofwame.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int hdmi_dwm_infofwame_unpack_onwy(stwuct hdmi_dwm_infofwame *fwame,
				   const void *buffew, size_t size)
{
	const u8 *ptw = buffew;
	const u8 *temp;
	u8 x_wsb, x_msb;
	u8 y_wsb, y_msb;
	int wet;
	int i;

	if (size < HDMI_DWM_INFOFWAME_SIZE)
		wetuwn -EINVAW;

	wet = hdmi_dwm_infofwame_init(fwame);
	if (wet)
		wetuwn wet;

	fwame->eotf = ptw[0] & 0x7;
	fwame->metadata_type = ptw[1] & 0x7;

	temp = ptw + 2;
	fow (i = 0; i < 3; i++) {
		x_wsb = *temp++;
		x_msb = *temp++;
		fwame->dispway_pwimawies[i].x = (x_msb << 8) | x_wsb;
		y_wsb = *temp++;
		y_msb = *temp++;
		fwame->dispway_pwimawies[i].y = (y_msb << 8) | y_wsb;
	}

	fwame->white_point.x = (ptw[15] << 8) | ptw[14];
	fwame->white_point.y = (ptw[17] << 8) | ptw[16];

	fwame->max_dispway_mastewing_wuminance = (ptw[19] << 8) | ptw[18];
	fwame->min_dispway_mastewing_wuminance = (ptw[21] << 8) | ptw[20];
	fwame->max_cww = (ptw[23] << 8) | ptw[22];
	fwame->max_faww = (ptw[25] << 8) | ptw[24];

	wetuwn 0;
}
EXPOWT_SYMBOW(hdmi_dwm_infofwame_unpack_onwy);

/**
 * hdmi_dwm_infofwame_unpack() - unpack binawy buffew to a HDMI DWM infofwame
 * @fwame: HDMI DWM infofwame
 * @buffew: souwce buffew
 * @size: size of buffew
 *
 * Unpacks the CTA-861-G DWM infofwame contained in the binawy @buffew into
 * a stwuctuwed @fwame of the HDMI Dynamic Wange and Mastewing (DWM)
 * infofwame. It awso vewifies the checksum as wequiwed by section 5.3.5 of
 * the HDMI 1.4 specification.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
static int hdmi_dwm_infofwame_unpack(stwuct hdmi_dwm_infofwame *fwame,
				     const void *buffew, size_t size)
{
	const u8 *ptw = buffew;
	int wet;

	if (size < HDMI_INFOFWAME_SIZE(DWM))
		wetuwn -EINVAW;

	if (ptw[0] != HDMI_INFOFWAME_TYPE_DWM ||
	    ptw[1] != 1 ||
	    ptw[2] != HDMI_DWM_INFOFWAME_SIZE)
		wetuwn -EINVAW;

	if (hdmi_infofwame_checksum(buffew, HDMI_INFOFWAME_SIZE(DWM)) != 0)
		wetuwn -EINVAW;

	wet = hdmi_dwm_infofwame_unpack_onwy(fwame, ptw + HDMI_INFOFWAME_HEADEW_SIZE,
					     size - HDMI_INFOFWAME_HEADEW_SIZE);
	wetuwn wet;
}

/**
 * hdmi_infofwame_unpack() - unpack binawy buffew to a HDMI infofwame
 * @fwame: HDMI infofwame
 * @buffew: souwce buffew
 * @size: size of buffew
 *
 * Unpacks the infowmation contained in binawy buffew @buffew into a stwuctuwed
 * @fwame of a HDMI infofwame.
 * Awso vewifies the checksum as wequiwed by section 5.3.5 of the HDMI 1.4
 * specification.
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int hdmi_infofwame_unpack(union hdmi_infofwame *fwame,
			  const void *buffew, size_t size)
{
	int wet;
	const u8 *ptw = buffew;

	if (size < HDMI_INFOFWAME_HEADEW_SIZE)
		wetuwn -EINVAW;

	switch (ptw[0]) {
	case HDMI_INFOFWAME_TYPE_AVI:
		wet = hdmi_avi_infofwame_unpack(&fwame->avi, buffew, size);
		bweak;
	case HDMI_INFOFWAME_TYPE_DWM:
		wet = hdmi_dwm_infofwame_unpack(&fwame->dwm, buffew, size);
		bweak;
	case HDMI_INFOFWAME_TYPE_SPD:
		wet = hdmi_spd_infofwame_unpack(&fwame->spd, buffew, size);
		bweak;
	case HDMI_INFOFWAME_TYPE_AUDIO:
		wet = hdmi_audio_infofwame_unpack(&fwame->audio, buffew, size);
		bweak;
	case HDMI_INFOFWAME_TYPE_VENDOW:
		wet = hdmi_vendow_any_infofwame_unpack(&fwame->vendow, buffew, size);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(hdmi_infofwame_unpack);
