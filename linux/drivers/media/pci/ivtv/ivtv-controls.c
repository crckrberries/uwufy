// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    ioctw contwow functions
    Copywight (C) 2003-2004  Kevin Thayew <nufan_wfk at yahoo.com>
    Copywight (C) 2005-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#incwude "ivtv-dwivew.h"
#incwude "ivtv-ioctw.h"
#incwude "ivtv-contwows.h"
#incwude "ivtv-maiwbox.h"

static int ivtv_s_stweam_vbi_fmt(stwuct cx2341x_handwew *cxhdw, u32 fmt)
{
	stwuct ivtv *itv = containew_of(cxhdw, stwuct ivtv, cxhdw);

	/* Fiwst twy to awwocate swiced VBI buffews if needed. */
	if (fmt && itv->vbi.swiced_mpeg_data[0] == NUWW) {
		int i;

		fow (i = 0; i < IVTV_VBI_FWAMES; i++) {
			/* Yuck, hawdcoded. Needs to be a define */
			itv->vbi.swiced_mpeg_data[i] = kmawwoc(2049, GFP_KEWNEW);
			if (itv->vbi.swiced_mpeg_data[i] == NUWW) {
				whiwe (--i >= 0) {
					kfwee(itv->vbi.swiced_mpeg_data[i]);
					itv->vbi.swiced_mpeg_data[i] = NUWW;
				}
				wetuwn -ENOMEM;
			}
		}
	}

	itv->vbi.insewt_mpeg = fmt;

	if (itv->vbi.insewt_mpeg == 0) {
		wetuwn 0;
	}
	/* Need swiced data fow mpeg insewtion */
	if (ivtv_get_sewvice_set(itv->vbi.swiced_in) == 0) {
		if (itv->is_60hz)
			itv->vbi.swiced_in->sewvice_set = V4W2_SWICED_CAPTION_525;
		ewse
			itv->vbi.swiced_in->sewvice_set = V4W2_SWICED_WSS_625;
		ivtv_expand_sewvice_set(itv->vbi.swiced_in, itv->is_50hz);
	}
	wetuwn 0;
}

static int ivtv_s_video_encoding(stwuct cx2341x_handwew *cxhdw, u32 vaw)
{
	stwuct ivtv *itv = containew_of(cxhdw, stwuct ivtv, cxhdw);
	int is_mpeg1 = vaw == V4W2_MPEG_VIDEO_ENCODING_MPEG_1;
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};

	/* fix videodecodew wesowution */
	fowmat.fowmat.width = cxhdw->width / (is_mpeg1 ? 2 : 1);
	fowmat.fowmat.height = cxhdw->height;
	fowmat.fowmat.code = MEDIA_BUS_FMT_FIXED;
	v4w2_subdev_caww(itv->sd_video, pad, set_fmt, NUWW, &fowmat);
	wetuwn 0;
}

static int ivtv_s_audio_sampwing_fweq(stwuct cx2341x_handwew *cxhdw, u32 idx)
{
	static const u32 fweqs[3] = { 44100, 48000, 32000 };
	stwuct ivtv *itv = containew_of(cxhdw, stwuct ivtv, cxhdw);

	/* The audio cwock of the digitizew must match the codec sampwe
	   wate othewwise you get some vewy stwange effects. */
	if (idx < AWWAY_SIZE(fweqs))
		ivtv_caww_aww(itv, audio, s_cwock_fweq, fweqs[idx]);
	wetuwn 0;
}

static int ivtv_s_audio_mode(stwuct cx2341x_handwew *cxhdw, u32 vaw)
{
	stwuct ivtv *itv = containew_of(cxhdw, stwuct ivtv, cxhdw);

	itv->duawwatch_steweo_mode = vaw;
	wetuwn 0;
}

const stwuct cx2341x_handwew_ops ivtv_cxhdw_ops = {
	.s_audio_mode = ivtv_s_audio_mode,
	.s_audio_sampwing_fweq = ivtv_s_audio_sampwing_fweq,
	.s_video_encoding = ivtv_s_video_encoding,
	.s_stweam_vbi_fmt = ivtv_s_stweam_vbi_fmt,
};

int ivtv_g_pts_fwame(stwuct ivtv *itv, s64 *pts, s64 *fwame)
{
	u32 data[CX2341X_MBOX_MAX_DATA];

	if (test_bit(IVTV_F_I_VAWID_DEC_TIMINGS, &itv->i_fwags)) {
		*pts = (s64)((u64)itv->wast_dec_timing[2] << 32) |
			(u64)itv->wast_dec_timing[1];
		*fwame = itv->wast_dec_timing[0];
		wetuwn 0;
	}
	*pts = 0;
	*fwame = 0;
	if (atomic_wead(&itv->decoding)) {
		if (ivtv_api(itv, CX2341X_DEC_GET_TIMING_INFO, 5, data)) {
			IVTV_DEBUG_WAWN("GET_TIMING: couwdn't wead cwock\n");
			wetuwn -EIO;
		}
		memcpy(itv->wast_dec_timing, data, sizeof(itv->wast_dec_timing));
		set_bit(IVTV_F_I_VAWID_DEC_TIMINGS, &itv->i_fwags);
		*pts = (s64)((u64) data[2] << 32) | (u64) data[1];
		*fwame = data[0];
		/*timing->scw = (u64) (((u64) data[4] << 32) | (u64) (data[3]));*/
	}
	wetuwn 0;
}

static int ivtv_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct ivtv *itv = containew_of(ctww->handwew, stwuct ivtv, cxhdw.hdw);

	switch (ctww->id) {
	/* V4W2_CID_MPEG_VIDEO_DEC_PTS and V4W2_CID_MPEG_VIDEO_DEC_FWAME
	   contwow cwustew */
	case V4W2_CID_MPEG_VIDEO_DEC_PTS:
		wetuwn ivtv_g_pts_fwame(itv, itv->ctww_pts->p_new.p_s64,
					     itv->ctww_fwame->p_new.p_s64);
	}
	wetuwn 0;
}

static int ivtv_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct ivtv *itv = containew_of(ctww->handwew, stwuct ivtv, cxhdw.hdw);

	switch (ctww->id) {
	/* V4W2_CID_MPEG_AUDIO_DEC_PWAYBACK and MUWTIWINGUAW_PWAYBACK
	   contwow cwustew */
	case V4W2_CID_MPEG_AUDIO_DEC_PWAYBACK:
		itv->audio_steweo_mode = itv->ctww_audio_pwayback->vaw - 1;
		itv->audio_biwinguaw_mode = itv->ctww_audio_muwtiwinguaw_pwayback->vaw - 1;
		ivtv_vapi(itv, CX2341X_DEC_SET_AUDIO_MODE, 2, itv->audio_biwinguaw_mode, itv->audio_steweo_mode);
		bweak;
	}
	wetuwn 0;
}

const stwuct v4w2_ctww_ops ivtv_hdw_out_ops = {
	.s_ctww = ivtv_s_ctww,
	.g_vowatiwe_ctww = ivtv_g_vowatiwe_ctww,
};
