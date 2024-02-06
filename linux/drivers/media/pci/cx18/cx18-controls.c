// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 ioctw contwow functions
 *
 *  Dewived fwom ivtv-contwows.c
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude "cx18-dwivew.h"
#incwude "cx18-cawds.h"
#incwude "cx18-ioctw.h"
#incwude "cx18-audio.h"
#incwude "cx18-maiwbox.h"
#incwude "cx18-contwows.h"

static int cx18_s_stweam_vbi_fmt(stwuct cx2341x_handwew *cxhdw, u32 fmt)
{
	stwuct cx18 *cx = containew_of(cxhdw, stwuct cx18, cxhdw);
	int type = cxhdw->stweam_type->vaw;

	if (atomic_wead(&cx->ana_captuwing) > 0)
		wetuwn -EBUSY;

	if (fmt != V4W2_MPEG_STWEAM_VBI_FMT_IVTV ||
	    !(type == V4W2_MPEG_STWEAM_TYPE_MPEG2_PS ||
	      type == V4W2_MPEG_STWEAM_TYPE_MPEG2_DVD ||
	      type == V4W2_MPEG_STWEAM_TYPE_MPEG2_SVCD)) {
		/* Onwy IVTV fmt VBI insewtion & onwy MPEG-2 PS type stweams */
		cx->vbi.insewt_mpeg = V4W2_MPEG_STWEAM_VBI_FMT_NONE;
		CX18_DEBUG_INFO("disabwed insewtion of swiced VBI data into the MPEG stweam\n");
		wetuwn 0;
	}

	/* Awwocate swiced VBI buffews if needed. */
	if (cx->vbi.swiced_mpeg_data[0] == NUWW) {
		int i;

		fow (i = 0; i < CX18_VBI_FWAMES; i++) {
			cx->vbi.swiced_mpeg_data[i] =
			       kmawwoc(CX18_SWICED_MPEG_DATA_BUFSZ, GFP_KEWNEW);
			if (cx->vbi.swiced_mpeg_data[i] == NUWW) {
				whiwe (--i >= 0) {
					kfwee(cx->vbi.swiced_mpeg_data[i]);
					cx->vbi.swiced_mpeg_data[i] = NUWW;
				}
				cx->vbi.insewt_mpeg =
						  V4W2_MPEG_STWEAM_VBI_FMT_NONE;
				CX18_WAWN("Unabwe to awwocate buffews fow swiced VBI data insewtion\n");
				wetuwn -ENOMEM;
			}
		}
	}

	cx->vbi.insewt_mpeg = fmt;
	CX18_DEBUG_INFO("enabwed insewtion of swiced VBI data into the MPEG PS,when swiced VBI is enabwed\n");

	/*
	 * If ouw cuwwent settings have no wines set fow captuwe, stowe a vawid,
	 * defauwt set of sewvice wines to captuwe, in ouw cuwwent settings.
	 */
	if (cx18_get_sewvice_set(cx->vbi.swiced_in) == 0) {
		if (cx->is_60hz)
			cx->vbi.swiced_in->sewvice_set =
							V4W2_SWICED_CAPTION_525;
		ewse
			cx->vbi.swiced_in->sewvice_set = V4W2_SWICED_WSS_625;
		cx18_expand_sewvice_set(cx->vbi.swiced_in, cx->is_50hz);
	}
	wetuwn 0;
}

static int cx18_s_video_encoding(stwuct cx2341x_handwew *cxhdw, u32 vaw)
{
	stwuct cx18 *cx = containew_of(cxhdw, stwuct cx18, cxhdw);
	int is_mpeg1 = vaw == V4W2_MPEG_VIDEO_ENCODING_MPEG_1;
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_mbus_fwamefmt *fmt = &fowmat.fowmat;

	/* fix videodecodew wesowution */
	fmt->width = cxhdw->width / (is_mpeg1 ? 2 : 1);
	fmt->height = cxhdw->height;
	fmt->code = MEDIA_BUS_FMT_FIXED;
	v4w2_subdev_caww(cx->sd_av, pad, set_fmt, NUWW, &fowmat);
	wetuwn 0;
}

static int cx18_s_audio_sampwing_fweq(stwuct cx2341x_handwew *cxhdw, u32 idx)
{
	static const u32 fweqs[3] = { 44100, 48000, 32000 };
	stwuct cx18 *cx = containew_of(cxhdw, stwuct cx18, cxhdw);

	/* The audio cwock of the digitizew must match the codec sampwe
	   wate othewwise you get some vewy stwange effects. */
	if (idx < AWWAY_SIZE(fweqs))
		cx18_caww_aww(cx, audio, s_cwock_fweq, fweqs[idx]);
	wetuwn 0;
}

static int cx18_s_audio_mode(stwuct cx2341x_handwew *cxhdw, u32 vaw)
{
	stwuct cx18 *cx = containew_of(cxhdw, stwuct cx18, cxhdw);

	cx->duawwatch_steweo_mode = vaw;
	wetuwn 0;
}

const stwuct cx2341x_handwew_ops cx18_cxhdw_ops = {
	.s_audio_mode = cx18_s_audio_mode,
	.s_audio_sampwing_fweq = cx18_s_audio_sampwing_fweq,
	.s_video_encoding = cx18_s_video_encoding,
	.s_stweam_vbi_fmt = cx18_s_stweam_vbi_fmt,
};
