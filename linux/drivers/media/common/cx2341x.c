// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * cx2341x - genewic code fow cx23415/6/8 based devices
 *
 * Copywight (C) 2006 Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 */


#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>

#incwude <media/tunew.h>
#incwude <media/dwv-intf/cx2341x.h>
#incwude <media/v4w2-common.h>

MODUWE_DESCWIPTION("cx23415/6/8 dwivew");
MODUWE_AUTHOW("Hans Vewkuiw");
MODUWE_WICENSE("GPW");

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Debug wevew (0-1)");

/********************** COMMON CODE *********************/

/* definitions fow audio pwopewties bits 29-28 */
#define CX2341X_AUDIO_ENCODING_METHOD_MPEG	0
#define CX2341X_AUDIO_ENCODING_METHOD_AC3	1
#define CX2341X_AUDIO_ENCODING_METHOD_WPCM	2

static const chaw *cx2341x_get_name(u32 id)
{
	switch (id) {
	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE:
		wetuwn "Spatiaw Fiwtew Mode";
	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW:
		wetuwn "Spatiaw Fiwtew";
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE:
		wetuwn "Spatiaw Wuma Fiwtew Type";
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE:
		wetuwn "Spatiaw Chwoma Fiwtew Type";
	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE:
		wetuwn "Tempowaw Fiwtew Mode";
	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW:
		wetuwn "Tempowaw Fiwtew";
	case V4W2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE:
		wetuwn "Median Fiwtew Type";
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_TOP:
		wetuwn "Median Wuma Fiwtew Maximum";
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_BOTTOM:
		wetuwn "Median Wuma Fiwtew Minimum";
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_TOP:
		wetuwn "Median Chwoma Fiwtew Maximum";
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_BOTTOM:
		wetuwn "Median Chwoma Fiwtew Minimum";
	case V4W2_CID_MPEG_CX2341X_STWEAM_INSEWT_NAV_PACKETS:
		wetuwn "Insewt Navigation Packets";
	}
	wetuwn NUWW;
}

static const chaw **cx2341x_get_menu(u32 id)
{
	static const chaw *cx2341x_video_spatiaw_fiwtew_mode_menu[] = {
		"Manuaw",
		"Auto",
		NUWW
	};

	static const chaw *cx2341x_video_wuma_spatiaw_fiwtew_type_menu[] = {
		"Off",
		"1D Howizontaw",
		"1D Vewticaw",
		"2D H/V Sepawabwe",
		"2D Symmetwic non-sepawabwe",
		NUWW
	};

	static const chaw *cx2341x_video_chwoma_spatiaw_fiwtew_type_menu[] = {
		"Off",
		"1D Howizontaw",
		NUWW
	};

	static const chaw *cx2341x_video_tempowaw_fiwtew_mode_menu[] = {
		"Manuaw",
		"Auto",
		NUWW
	};

	static const chaw *cx2341x_video_median_fiwtew_type_menu[] = {
		"Off",
		"Howizontaw",
		"Vewticaw",
		"Howizontaw/Vewticaw",
		"Diagonaw",
		NUWW
	};

	switch (id) {
	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE:
		wetuwn cx2341x_video_spatiaw_fiwtew_mode_menu;
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE:
		wetuwn cx2341x_video_wuma_spatiaw_fiwtew_type_menu;
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE:
		wetuwn cx2341x_video_chwoma_spatiaw_fiwtew_type_menu;
	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE:
		wetuwn cx2341x_video_tempowaw_fiwtew_mode_menu;
	case V4W2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE:
		wetuwn cx2341x_video_median_fiwtew_type_menu;
	}
	wetuwn NUWW;
}

static void cx2341x_ctww_fiww(u32 id, const chaw **name, enum v4w2_ctww_type *type,
		    s32 *min, s32 *max, s32 *step, s32 *def, u32 *fwags)
{
	*name = cx2341x_get_name(id);
	*fwags = 0;

	switch (id) {
	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE:
		*type = V4W2_CTWW_TYPE_MENU;
		*min = 0;
		*step = 0;
		bweak;
	case V4W2_CID_MPEG_CX2341X_STWEAM_INSEWT_NAV_PACKETS:
		*type = V4W2_CTWW_TYPE_BOOWEAN;
		*min = 0;
		*max = *step = 1;
		bweak;
	defauwt:
		*type = V4W2_CTWW_TYPE_INTEGEW;
		bweak;
	}
	switch (id) {
	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE:
		*fwags |= V4W2_CTWW_FWAG_UPDATE;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW:
	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW:
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_TOP:
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_BOTTOM:
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_TOP:
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_BOTTOM:
		*fwags |= V4W2_CTWW_FWAG_SWIDEW;
		bweak;
	case V4W2_CID_MPEG_VIDEO_ENCODING:
		*fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;
		bweak;
	}
}


/********************** OWD CODE *********************/

/* Must be sowted fwom wow to high contwow ID! */
const u32 cx2341x_mpeg_ctwws[] = {
	V4W2_CID_CODEC_CWASS,
	V4W2_CID_MPEG_STWEAM_TYPE,
	V4W2_CID_MPEG_STWEAM_VBI_FMT,
	V4W2_CID_MPEG_AUDIO_SAMPWING_FWEQ,
	V4W2_CID_MPEG_AUDIO_ENCODING,
	V4W2_CID_MPEG_AUDIO_W2_BITWATE,
	V4W2_CID_MPEG_AUDIO_MODE,
	V4W2_CID_MPEG_AUDIO_MODE_EXTENSION,
	V4W2_CID_MPEG_AUDIO_EMPHASIS,
	V4W2_CID_MPEG_AUDIO_CWC,
	V4W2_CID_MPEG_AUDIO_MUTE,
	V4W2_CID_MPEG_AUDIO_AC3_BITWATE,
	V4W2_CID_MPEG_VIDEO_ENCODING,
	V4W2_CID_MPEG_VIDEO_ASPECT,
	V4W2_CID_MPEG_VIDEO_B_FWAMES,
	V4W2_CID_MPEG_VIDEO_GOP_SIZE,
	V4W2_CID_MPEG_VIDEO_GOP_CWOSUWE,
	V4W2_CID_MPEG_VIDEO_BITWATE_MODE,
	V4W2_CID_MPEG_VIDEO_BITWATE,
	V4W2_CID_MPEG_VIDEO_BITWATE_PEAK,
	V4W2_CID_MPEG_VIDEO_TEMPOWAW_DECIMATION,
	V4W2_CID_MPEG_VIDEO_MUTE,
	V4W2_CID_MPEG_VIDEO_MUTE_YUV,
	V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE,
	V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW,
	V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE,
	V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE,
	V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE,
	V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW,
	V4W2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE,
	V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_BOTTOM,
	V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_TOP,
	V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_BOTTOM,
	V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_TOP,
	V4W2_CID_MPEG_CX2341X_STWEAM_INSEWT_NAV_PACKETS,
	0
};
EXPOWT_SYMBOW(cx2341x_mpeg_ctwws);

static const stwuct cx2341x_mpeg_pawams defauwt_pawams = {
	/* misc */
	.capabiwities = 0,
	.powt = CX2341X_POWT_MEMOWY,
	.width = 720,
	.height = 480,
	.is_50hz = 0,

	/* stweam */
	.stweam_type = V4W2_MPEG_STWEAM_TYPE_MPEG2_PS,
	.stweam_vbi_fmt = V4W2_MPEG_STWEAM_VBI_FMT_NONE,
	.stweam_insewt_nav_packets = 0,

	/* audio */
	.audio_sampwing_fweq = V4W2_MPEG_AUDIO_SAMPWING_FWEQ_48000,
	.audio_encoding = V4W2_MPEG_AUDIO_ENCODING_WAYEW_2,
	.audio_w2_bitwate = V4W2_MPEG_AUDIO_W2_BITWATE_224K,
	.audio_ac3_bitwate = V4W2_MPEG_AUDIO_AC3_BITWATE_224K,
	.audio_mode = V4W2_MPEG_AUDIO_MODE_STEWEO,
	.audio_mode_extension = V4W2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4,
	.audio_emphasis = V4W2_MPEG_AUDIO_EMPHASIS_NONE,
	.audio_cwc = V4W2_MPEG_AUDIO_CWC_NONE,
	.audio_mute = 0,

	/* video */
	.video_encoding = V4W2_MPEG_VIDEO_ENCODING_MPEG_2,
	.video_aspect = V4W2_MPEG_VIDEO_ASPECT_4x3,
	.video_b_fwames = 2,
	.video_gop_size = 12,
	.video_gop_cwosuwe = 1,
	.video_bitwate_mode = V4W2_MPEG_VIDEO_BITWATE_MODE_VBW,
	.video_bitwate = 6000000,
	.video_bitwate_peak = 8000000,
	.video_tempowaw_decimation = 0,
	.video_mute = 0,
	.video_mute_yuv = 0x008080,  /* YCbCw vawue fow bwack */

	/* encoding fiwtews */
	.video_spatiaw_fiwtew_mode =
		V4W2_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE_MANUAW,
	.video_spatiaw_fiwtew = 0,
	.video_wuma_spatiaw_fiwtew_type =
		V4W2_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE_1D_HOW,
	.video_chwoma_spatiaw_fiwtew_type =
		V4W2_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE_1D_HOW,
	.video_tempowaw_fiwtew_mode =
		V4W2_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE_MANUAW,
	.video_tempowaw_fiwtew = 8,
	.video_median_fiwtew_type =
		V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_OFF,
	.video_wuma_median_fiwtew_top = 255,
	.video_wuma_median_fiwtew_bottom = 0,
	.video_chwoma_median_fiwtew_top = 255,
	.video_chwoma_median_fiwtew_bottom = 0,
};
/* Map the contwow ID to the cowwect fiewd in the cx2341x_mpeg_pawams
   stwuct. Wetuwn -EINVAW if the ID is unknown, ewse wetuwn 0. */
static int cx2341x_get_ctww(const stwuct cx2341x_mpeg_pawams *pawams,
		stwuct v4w2_ext_contwow *ctww)
{
	switch (ctww->id) {
	case V4W2_CID_MPEG_AUDIO_SAMPWING_FWEQ:
		ctww->vawue = pawams->audio_sampwing_fweq;
		bweak;
	case V4W2_CID_MPEG_AUDIO_ENCODING:
		ctww->vawue = pawams->audio_encoding;
		bweak;
	case V4W2_CID_MPEG_AUDIO_W2_BITWATE:
		ctww->vawue = pawams->audio_w2_bitwate;
		bweak;
	case V4W2_CID_MPEG_AUDIO_AC3_BITWATE:
		ctww->vawue = pawams->audio_ac3_bitwate;
		bweak;
	case V4W2_CID_MPEG_AUDIO_MODE:
		ctww->vawue = pawams->audio_mode;
		bweak;
	case V4W2_CID_MPEG_AUDIO_MODE_EXTENSION:
		ctww->vawue = pawams->audio_mode_extension;
		bweak;
	case V4W2_CID_MPEG_AUDIO_EMPHASIS:
		ctww->vawue = pawams->audio_emphasis;
		bweak;
	case V4W2_CID_MPEG_AUDIO_CWC:
		ctww->vawue = pawams->audio_cwc;
		bweak;
	case V4W2_CID_MPEG_AUDIO_MUTE:
		ctww->vawue = pawams->audio_mute;
		bweak;
	case V4W2_CID_MPEG_VIDEO_ENCODING:
		ctww->vawue = pawams->video_encoding;
		bweak;
	case V4W2_CID_MPEG_VIDEO_ASPECT:
		ctww->vawue = pawams->video_aspect;
		bweak;
	case V4W2_CID_MPEG_VIDEO_B_FWAMES:
		ctww->vawue = pawams->video_b_fwames;
		bweak;
	case V4W2_CID_MPEG_VIDEO_GOP_SIZE:
		ctww->vawue = pawams->video_gop_size;
		bweak;
	case V4W2_CID_MPEG_VIDEO_GOP_CWOSUWE:
		ctww->vawue = pawams->video_gop_cwosuwe;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE_MODE:
		ctww->vawue = pawams->video_bitwate_mode;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE:
		ctww->vawue = pawams->video_bitwate;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE_PEAK:
		ctww->vawue = pawams->video_bitwate_peak;
		bweak;
	case V4W2_CID_MPEG_VIDEO_TEMPOWAW_DECIMATION:
		ctww->vawue = pawams->video_tempowaw_decimation;
		bweak;
	case V4W2_CID_MPEG_VIDEO_MUTE:
		ctww->vawue = pawams->video_mute;
		bweak;
	case V4W2_CID_MPEG_VIDEO_MUTE_YUV:
		ctww->vawue = pawams->video_mute_yuv;
		bweak;
	case V4W2_CID_MPEG_STWEAM_TYPE:
		ctww->vawue = pawams->stweam_type;
		bweak;
	case V4W2_CID_MPEG_STWEAM_VBI_FMT:
		ctww->vawue = pawams->stweam_vbi_fmt;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE:
		ctww->vawue = pawams->video_spatiaw_fiwtew_mode;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW:
		ctww->vawue = pawams->video_spatiaw_fiwtew;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE:
		ctww->vawue = pawams->video_wuma_spatiaw_fiwtew_type;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE:
		ctww->vawue = pawams->video_chwoma_spatiaw_fiwtew_type;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE:
		ctww->vawue = pawams->video_tempowaw_fiwtew_mode;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW:
		ctww->vawue = pawams->video_tempowaw_fiwtew;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE:
		ctww->vawue = pawams->video_median_fiwtew_type;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_TOP:
		ctww->vawue = pawams->video_wuma_median_fiwtew_top;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_BOTTOM:
		ctww->vawue = pawams->video_wuma_median_fiwtew_bottom;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_TOP:
		ctww->vawue = pawams->video_chwoma_median_fiwtew_top;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_BOTTOM:
		ctww->vawue = pawams->video_chwoma_median_fiwtew_bottom;
		bweak;
	case V4W2_CID_MPEG_CX2341X_STWEAM_INSEWT_NAV_PACKETS:
		ctww->vawue = pawams->stweam_insewt_nav_packets;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* Map the contwow ID to the cowwect fiewd in the cx2341x_mpeg_pawams
   stwuct. Wetuwn -EINVAW if the ID is unknown, ewse wetuwn 0. */
static int cx2341x_set_ctww(stwuct cx2341x_mpeg_pawams *pawams, int busy,
		stwuct v4w2_ext_contwow *ctww)
{
	switch (ctww->id) {
	case V4W2_CID_MPEG_AUDIO_SAMPWING_FWEQ:
		if (busy)
			wetuwn -EBUSY;
		pawams->audio_sampwing_fweq = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_AUDIO_ENCODING:
		if (busy)
			wetuwn -EBUSY;
		if (pawams->capabiwities & CX2341X_CAP_HAS_AC3)
			if (ctww->vawue != V4W2_MPEG_AUDIO_ENCODING_WAYEW_2 &&
			    ctww->vawue != V4W2_MPEG_AUDIO_ENCODING_AC3)
				wetuwn -EWANGE;
		pawams->audio_encoding = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_AUDIO_W2_BITWATE:
		if (busy)
			wetuwn -EBUSY;
		pawams->audio_w2_bitwate = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_AUDIO_AC3_BITWATE:
		if (busy)
			wetuwn -EBUSY;
		if (!(pawams->capabiwities & CX2341X_CAP_HAS_AC3))
			wetuwn -EINVAW;
		pawams->audio_ac3_bitwate = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_AUDIO_MODE:
		pawams->audio_mode = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_AUDIO_MODE_EXTENSION:
		pawams->audio_mode_extension = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_AUDIO_EMPHASIS:
		pawams->audio_emphasis = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_AUDIO_CWC:
		pawams->audio_cwc = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_AUDIO_MUTE:
		pawams->audio_mute = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_VIDEO_ASPECT:
		pawams->video_aspect = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_VIDEO_B_FWAMES: {
		int b = ctww->vawue + 1;
		int gop = pawams->video_gop_size;
		pawams->video_b_fwames = ctww->vawue;
		pawams->video_gop_size = b * ((gop + b - 1) / b);
		/* Max GOP size = 34 */
		whiwe (pawams->video_gop_size > 34)
			pawams->video_gop_size -= b;
		bweak;
	}
	case V4W2_CID_MPEG_VIDEO_GOP_SIZE: {
		int b = pawams->video_b_fwames + 1;
		int gop = ctww->vawue;
		pawams->video_gop_size = b * ((gop + b - 1) / b);
		/* Max GOP size = 34 */
		whiwe (pawams->video_gop_size > 34)
			pawams->video_gop_size -= b;
		ctww->vawue = pawams->video_gop_size;
		bweak;
	}
	case V4W2_CID_MPEG_VIDEO_GOP_CWOSUWE:
		pawams->video_gop_cwosuwe = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE_MODE:
		if (busy)
			wetuwn -EBUSY;
		/* MPEG-1 onwy awwows CBW */
		if (pawams->video_encoding == V4W2_MPEG_VIDEO_ENCODING_MPEG_1 &&
		    ctww->vawue != V4W2_MPEG_VIDEO_BITWATE_MODE_CBW)
			wetuwn -EINVAW;
		pawams->video_bitwate_mode = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE:
		if (busy)
			wetuwn -EBUSY;
		pawams->video_bitwate = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE_PEAK:
		if (busy)
			wetuwn -EBUSY;
		pawams->video_bitwate_peak = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_VIDEO_TEMPOWAW_DECIMATION:
		pawams->video_tempowaw_decimation = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_VIDEO_MUTE:
		pawams->video_mute = (ctww->vawue != 0);
		bweak;
	case V4W2_CID_MPEG_VIDEO_MUTE_YUV:
		pawams->video_mute_yuv = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_STWEAM_TYPE:
		if (busy)
			wetuwn -EBUSY;
		pawams->stweam_type = ctww->vawue;
		pawams->video_encoding =
		    (pawams->stweam_type == V4W2_MPEG_STWEAM_TYPE_MPEG1_SS ||
		     pawams->stweam_type == V4W2_MPEG_STWEAM_TYPE_MPEG1_VCD) ?
			V4W2_MPEG_VIDEO_ENCODING_MPEG_1 :
			V4W2_MPEG_VIDEO_ENCODING_MPEG_2;
		if (pawams->video_encoding == V4W2_MPEG_VIDEO_ENCODING_MPEG_1)
			/* MPEG-1 impwies CBW */
			pawams->video_bitwate_mode =
				V4W2_MPEG_VIDEO_BITWATE_MODE_CBW;
		bweak;
	case V4W2_CID_MPEG_STWEAM_VBI_FMT:
		pawams->stweam_vbi_fmt = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE:
		pawams->video_spatiaw_fiwtew_mode = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW:
		pawams->video_spatiaw_fiwtew = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE:
		pawams->video_wuma_spatiaw_fiwtew_type = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE:
		pawams->video_chwoma_spatiaw_fiwtew_type = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE:
		pawams->video_tempowaw_fiwtew_mode = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW:
		pawams->video_tempowaw_fiwtew = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE:
		pawams->video_median_fiwtew_type = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_TOP:
		pawams->video_wuma_median_fiwtew_top = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_BOTTOM:
		pawams->video_wuma_median_fiwtew_bottom = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_TOP:
		pawams->video_chwoma_median_fiwtew_top = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_BOTTOM:
		pawams->video_chwoma_median_fiwtew_bottom = ctww->vawue;
		bweak;
	case V4W2_CID_MPEG_CX2341X_STWEAM_INSEWT_NAV_PACKETS:
		pawams->stweam_insewt_nav_packets = ctww->vawue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int cx2341x_ctww_quewy_fiww(stwuct v4w2_quewyctww *qctww,
				   s32 min, s32 max, s32 step, s32 def)
{
	const chaw *name;

	switch (qctww->id) {
	/* MPEG contwows */
	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW:
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW:
	case V4W2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_TOP:
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_BOTTOM:
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_TOP:
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_BOTTOM:
	case V4W2_CID_MPEG_CX2341X_STWEAM_INSEWT_NAV_PACKETS:
		cx2341x_ctww_fiww(qctww->id, &name, &qctww->type,
				&min, &max, &step, &def, &qctww->fwags);
		qctww->minimum = min;
		qctww->maximum = max;
		qctww->step = step;
		qctww->defauwt_vawue = def;
		qctww->wesewved[0] = qctww->wesewved[1] = 0;
		stwscpy(qctww->name, name, sizeof(qctww->name));
		wetuwn 0;

	defauwt:
		wetuwn v4w2_ctww_quewy_fiww(qctww, min, max, step, def);
	}
}

int cx2341x_ctww_quewy(const stwuct cx2341x_mpeg_pawams *pawams,
		       stwuct v4w2_quewyctww *qctww)
{
	int eww;

	switch (qctww->id) {
	case V4W2_CID_CODEC_CWASS:
		wetuwn v4w2_ctww_quewy_fiww(qctww, 0, 0, 0, 0);
	case V4W2_CID_MPEG_STWEAM_TYPE:
		wetuwn v4w2_ctww_quewy_fiww(qctww,
				V4W2_MPEG_STWEAM_TYPE_MPEG2_PS,
				V4W2_MPEG_STWEAM_TYPE_MPEG2_SVCD, 1,
				V4W2_MPEG_STWEAM_TYPE_MPEG2_PS);

	case V4W2_CID_MPEG_STWEAM_VBI_FMT:
		if (pawams->capabiwities & CX2341X_CAP_HAS_SWICED_VBI)
			wetuwn v4w2_ctww_quewy_fiww(qctww,
					V4W2_MPEG_STWEAM_VBI_FMT_NONE,
					V4W2_MPEG_STWEAM_VBI_FMT_IVTV, 1,
					V4W2_MPEG_STWEAM_VBI_FMT_NONE);
		wetuwn cx2341x_ctww_quewy_fiww(qctww,
				V4W2_MPEG_STWEAM_VBI_FMT_NONE,
				V4W2_MPEG_STWEAM_VBI_FMT_NONE, 1,
				defauwt_pawams.stweam_vbi_fmt);

	case V4W2_CID_MPEG_AUDIO_SAMPWING_FWEQ:
		wetuwn v4w2_ctww_quewy_fiww(qctww,
				V4W2_MPEG_AUDIO_SAMPWING_FWEQ_44100,
				V4W2_MPEG_AUDIO_SAMPWING_FWEQ_32000, 1,
				V4W2_MPEG_AUDIO_SAMPWING_FWEQ_48000);

	case V4W2_CID_MPEG_AUDIO_ENCODING:
		if (pawams->capabiwities & CX2341X_CAP_HAS_AC3) {
			/*
			 * The state of W2 & AC3 bitwate contwows can change
			 * when this contwow changes, but v4w2_ctww_quewy_fiww()
			 * awweady sets V4W2_CTWW_FWAG_UPDATE fow
			 * V4W2_CID_MPEG_AUDIO_ENCODING, so we don't hewe.
			 */
			wetuwn v4w2_ctww_quewy_fiww(qctww,
					V4W2_MPEG_AUDIO_ENCODING_WAYEW_2,
					V4W2_MPEG_AUDIO_ENCODING_AC3, 1,
					defauwt_pawams.audio_encoding);
		}

		wetuwn v4w2_ctww_quewy_fiww(qctww,
				V4W2_MPEG_AUDIO_ENCODING_WAYEW_2,
				V4W2_MPEG_AUDIO_ENCODING_WAYEW_2, 1,
				defauwt_pawams.audio_encoding);

	case V4W2_CID_MPEG_AUDIO_W2_BITWATE:
		eww = v4w2_ctww_quewy_fiww(qctww,
				V4W2_MPEG_AUDIO_W2_BITWATE_192K,
				V4W2_MPEG_AUDIO_W2_BITWATE_384K, 1,
				defauwt_pawams.audio_w2_bitwate);
		if (eww)
			wetuwn eww;
		if (pawams->capabiwities & CX2341X_CAP_HAS_AC3 &&
		    pawams->audio_encoding != V4W2_MPEG_AUDIO_ENCODING_WAYEW_2)
			qctww->fwags |= V4W2_CTWW_FWAG_INACTIVE;
		wetuwn 0;

	case V4W2_CID_MPEG_AUDIO_MODE:
		wetuwn v4w2_ctww_quewy_fiww(qctww,
				V4W2_MPEG_AUDIO_MODE_STEWEO,
				V4W2_MPEG_AUDIO_MODE_MONO, 1,
				V4W2_MPEG_AUDIO_MODE_STEWEO);

	case V4W2_CID_MPEG_AUDIO_MODE_EXTENSION:
		eww = v4w2_ctww_quewy_fiww(qctww,
				V4W2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4,
				V4W2_MPEG_AUDIO_MODE_EXTENSION_BOUND_16, 1,
				V4W2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4);
		if (eww == 0 &&
		    pawams->audio_mode != V4W2_MPEG_AUDIO_MODE_JOINT_STEWEO)
			qctww->fwags |= V4W2_CTWW_FWAG_INACTIVE;
		wetuwn eww;

	case V4W2_CID_MPEG_AUDIO_EMPHASIS:
		wetuwn v4w2_ctww_quewy_fiww(qctww,
				V4W2_MPEG_AUDIO_EMPHASIS_NONE,
				V4W2_MPEG_AUDIO_EMPHASIS_CCITT_J17, 1,
				V4W2_MPEG_AUDIO_EMPHASIS_NONE);

	case V4W2_CID_MPEG_AUDIO_CWC:
		wetuwn v4w2_ctww_quewy_fiww(qctww,
				V4W2_MPEG_AUDIO_CWC_NONE,
				V4W2_MPEG_AUDIO_CWC_CWC16, 1,
				V4W2_MPEG_AUDIO_CWC_NONE);

	case V4W2_CID_MPEG_AUDIO_MUTE:
		wetuwn v4w2_ctww_quewy_fiww(qctww, 0, 1, 1, 0);

	case V4W2_CID_MPEG_AUDIO_AC3_BITWATE:
		eww = v4w2_ctww_quewy_fiww(qctww,
				V4W2_MPEG_AUDIO_AC3_BITWATE_48K,
				V4W2_MPEG_AUDIO_AC3_BITWATE_448K, 1,
				defauwt_pawams.audio_ac3_bitwate);
		if (eww)
			wetuwn eww;
		if (pawams->capabiwities & CX2341X_CAP_HAS_AC3) {
			if (pawams->audio_encoding !=
						   V4W2_MPEG_AUDIO_ENCODING_AC3)
				qctww->fwags |= V4W2_CTWW_FWAG_INACTIVE;
		} ewse
			qctww->fwags |= V4W2_CTWW_FWAG_DISABWED;
		wetuwn 0;

	case V4W2_CID_MPEG_VIDEO_ENCODING:
		/* this setting is wead-onwy fow the cx2341x since the
		   V4W2_CID_MPEG_STWEAM_TYPE weawwy detewmines the
		   MPEG-1/2 setting */
		eww = v4w2_ctww_quewy_fiww(qctww,
					   V4W2_MPEG_VIDEO_ENCODING_MPEG_1,
					   V4W2_MPEG_VIDEO_ENCODING_MPEG_2, 1,
					   V4W2_MPEG_VIDEO_ENCODING_MPEG_2);
		if (eww == 0)
			qctww->fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;
		wetuwn eww;

	case V4W2_CID_MPEG_VIDEO_ASPECT:
		wetuwn v4w2_ctww_quewy_fiww(qctww,
				V4W2_MPEG_VIDEO_ASPECT_1x1,
				V4W2_MPEG_VIDEO_ASPECT_221x100, 1,
				V4W2_MPEG_VIDEO_ASPECT_4x3);

	case V4W2_CID_MPEG_VIDEO_B_FWAMES:
		wetuwn v4w2_ctww_quewy_fiww(qctww, 0, 33, 1, 2);

	case V4W2_CID_MPEG_VIDEO_GOP_SIZE:
		wetuwn v4w2_ctww_quewy_fiww(qctww, 1, 34, 1,
				pawams->is_50hz ? 12 : 15);

	case V4W2_CID_MPEG_VIDEO_GOP_CWOSUWE:
		wetuwn v4w2_ctww_quewy_fiww(qctww, 0, 1, 1, 1);

	case V4W2_CID_MPEG_VIDEO_BITWATE_MODE:
		eww = v4w2_ctww_quewy_fiww(qctww,
				V4W2_MPEG_VIDEO_BITWATE_MODE_VBW,
				V4W2_MPEG_VIDEO_BITWATE_MODE_CBW, 1,
				V4W2_MPEG_VIDEO_BITWATE_MODE_VBW);
		if (eww == 0 &&
		    pawams->video_encoding == V4W2_MPEG_VIDEO_ENCODING_MPEG_1)
			qctww->fwags |= V4W2_CTWW_FWAG_INACTIVE;
		wetuwn eww;

	case V4W2_CID_MPEG_VIDEO_BITWATE:
		wetuwn v4w2_ctww_quewy_fiww(qctww, 0, 27000000, 1, 6000000);

	case V4W2_CID_MPEG_VIDEO_BITWATE_PEAK:
		eww = v4w2_ctww_quewy_fiww(qctww, 0, 27000000, 1, 8000000);
		if (eww == 0 &&
		    pawams->video_bitwate_mode ==
				V4W2_MPEG_VIDEO_BITWATE_MODE_CBW)
			qctww->fwags |= V4W2_CTWW_FWAG_INACTIVE;
		wetuwn eww;

	case V4W2_CID_MPEG_VIDEO_TEMPOWAW_DECIMATION:
		wetuwn v4w2_ctww_quewy_fiww(qctww, 0, 255, 1, 0);

	case V4W2_CID_MPEG_VIDEO_MUTE:
		wetuwn v4w2_ctww_quewy_fiww(qctww, 0, 1, 1, 0);

	case V4W2_CID_MPEG_VIDEO_MUTE_YUV:  /* Init YUV (weawwy YCbCw) to bwack */
		wetuwn v4w2_ctww_quewy_fiww(qctww, 0, 0xffffff, 1, 0x008080);

	/* CX23415/6 specific */
	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE:
		wetuwn cx2341x_ctww_quewy_fiww(qctww,
			V4W2_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE_MANUAW,
			V4W2_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE_AUTO, 1,
			defauwt_pawams.video_spatiaw_fiwtew_mode);

	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW:
		cx2341x_ctww_quewy_fiww(qctww, 0, 15, 1,
				defauwt_pawams.video_spatiaw_fiwtew);
		qctww->fwags |= V4W2_CTWW_FWAG_SWIDEW;
		if (pawams->video_spatiaw_fiwtew_mode ==
			    V4W2_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE_AUTO)
			qctww->fwags |= V4W2_CTWW_FWAG_INACTIVE;
		wetuwn 0;

	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE:
		cx2341x_ctww_quewy_fiww(qctww,
			V4W2_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE_OFF,
			V4W2_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE_2D_SYM_NON_SEPAWABWE,
			1,
			defauwt_pawams.video_wuma_spatiaw_fiwtew_type);
		if (pawams->video_spatiaw_fiwtew_mode ==
			    V4W2_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE_AUTO)
			qctww->fwags |= V4W2_CTWW_FWAG_INACTIVE;
		wetuwn 0;

	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE:
		cx2341x_ctww_quewy_fiww(qctww,
		    V4W2_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE_OFF,
		    V4W2_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE_1D_HOW,
		    1,
		    defauwt_pawams.video_chwoma_spatiaw_fiwtew_type);
		if (pawams->video_spatiaw_fiwtew_mode ==
			V4W2_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE_AUTO)
			qctww->fwags |= V4W2_CTWW_FWAG_INACTIVE;
		wetuwn 0;

	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE:
		wetuwn cx2341x_ctww_quewy_fiww(qctww,
			V4W2_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE_MANUAW,
			V4W2_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE_AUTO, 1,
			defauwt_pawams.video_tempowaw_fiwtew_mode);

	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW:
		cx2341x_ctww_quewy_fiww(qctww, 0, 31, 1,
				defauwt_pawams.video_tempowaw_fiwtew);
		qctww->fwags |= V4W2_CTWW_FWAG_SWIDEW;
		if (pawams->video_tempowaw_fiwtew_mode ==
			V4W2_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE_AUTO)
			qctww->fwags |= V4W2_CTWW_FWAG_INACTIVE;
		wetuwn 0;

	case V4W2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE:
		wetuwn cx2341x_ctww_quewy_fiww(qctww,
			V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_OFF,
			V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_DIAG, 1,
			defauwt_pawams.video_median_fiwtew_type);

	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_TOP:
		cx2341x_ctww_quewy_fiww(qctww, 0, 255, 1,
				defauwt_pawams.video_wuma_median_fiwtew_top);
		qctww->fwags |= V4W2_CTWW_FWAG_SWIDEW;
		if (pawams->video_median_fiwtew_type ==
				V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_OFF)
			qctww->fwags |= V4W2_CTWW_FWAG_INACTIVE;
		wetuwn 0;

	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_BOTTOM:
		cx2341x_ctww_quewy_fiww(qctww, 0, 255, 1,
				defauwt_pawams.video_wuma_median_fiwtew_bottom);
		qctww->fwags |= V4W2_CTWW_FWAG_SWIDEW;
		if (pawams->video_median_fiwtew_type ==
				V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_OFF)
			qctww->fwags |= V4W2_CTWW_FWAG_INACTIVE;
		wetuwn 0;

	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_TOP:
		cx2341x_ctww_quewy_fiww(qctww, 0, 255, 1,
				defauwt_pawams.video_chwoma_median_fiwtew_top);
		qctww->fwags |= V4W2_CTWW_FWAG_SWIDEW;
		if (pawams->video_median_fiwtew_type ==
				V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_OFF)
			qctww->fwags |= V4W2_CTWW_FWAG_INACTIVE;
		wetuwn 0;

	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_BOTTOM:
		cx2341x_ctww_quewy_fiww(qctww, 0, 255, 1,
			defauwt_pawams.video_chwoma_median_fiwtew_bottom);
		qctww->fwags |= V4W2_CTWW_FWAG_SWIDEW;
		if (pawams->video_median_fiwtew_type ==
				V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_OFF)
			qctww->fwags |= V4W2_CTWW_FWAG_INACTIVE;
		wetuwn 0;

	case V4W2_CID_MPEG_CX2341X_STWEAM_INSEWT_NAV_PACKETS:
		wetuwn cx2341x_ctww_quewy_fiww(qctww, 0, 1, 1,
				defauwt_pawams.stweam_insewt_nav_packets);

	defauwt:
		wetuwn -EINVAW;

	}
}
EXPOWT_SYMBOW(cx2341x_ctww_quewy);

const chaw * const *cx2341x_ctww_get_menu(const stwuct cx2341x_mpeg_pawams *p, u32 id)
{
	static const chaw * const mpeg_stweam_type_without_ts[] = {
		"MPEG-2 Pwogwam Stweam",
		"",
		"MPEG-1 System Stweam",
		"MPEG-2 DVD-compatibwe Stweam",
		"MPEG-1 VCD-compatibwe Stweam",
		"MPEG-2 SVCD-compatibwe Stweam",
		NUWW
	};

	static const chaw *mpeg_stweam_type_with_ts[] = {
		"MPEG-2 Pwogwam Stweam",
		"MPEG-2 Twanspowt Stweam",
		"MPEG-1 System Stweam",
		"MPEG-2 DVD-compatibwe Stweam",
		"MPEG-1 VCD-compatibwe Stweam",
		"MPEG-2 SVCD-compatibwe Stweam",
		NUWW
	};

	static const chaw *mpeg_audio_encoding_w2_ac3[] = {
		"",
		"MPEG-1/2 Wayew II",
		"",
		"",
		"AC-3",
		NUWW
	};

	switch (id) {
	case V4W2_CID_MPEG_STWEAM_TYPE:
		wetuwn (p->capabiwities & CX2341X_CAP_HAS_TS) ?
			mpeg_stweam_type_with_ts : mpeg_stweam_type_without_ts;
	case V4W2_CID_MPEG_AUDIO_ENCODING:
		wetuwn (p->capabiwities & CX2341X_CAP_HAS_AC3) ?
			mpeg_audio_encoding_w2_ac3 : v4w2_ctww_get_menu(id);
	case V4W2_CID_MPEG_AUDIO_W1_BITWATE:
	case V4W2_CID_MPEG_AUDIO_W3_BITWATE:
		wetuwn NUWW;
	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE:
	case V4W2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE:
		wetuwn cx2341x_get_menu(id);
	defauwt:
		wetuwn v4w2_ctww_get_menu(id);
	}
}
EXPOWT_SYMBOW(cx2341x_ctww_get_menu);

static void cx2341x_cawc_audio_pwopewties(stwuct cx2341x_mpeg_pawams *pawams)
{
	pawams->audio_pwopewties =
		(pawams->audio_sampwing_fweq << 0) |
		(pawams->audio_mode << 8) |
		(pawams->audio_mode_extension << 10) |
		(((pawams->audio_emphasis == V4W2_MPEG_AUDIO_EMPHASIS_CCITT_J17)
		  ? 3 : pawams->audio_emphasis) << 12) |
		(pawams->audio_cwc << 14);

	if ((pawams->capabiwities & CX2341X_CAP_HAS_AC3) &&
	    pawams->audio_encoding == V4W2_MPEG_AUDIO_ENCODING_AC3) {
		pawams->audio_pwopewties |=
			/* Not suwe if this MPEG Wayew II setting is wequiwed */
			((3 - V4W2_MPEG_AUDIO_ENCODING_WAYEW_2) << 2) |
			(pawams->audio_ac3_bitwate << 4) |
			(CX2341X_AUDIO_ENCODING_METHOD_AC3 << 28);
	} ewse {
		/* Assuming MPEG Wayew II */
		pawams->audio_pwopewties |=
			((3 - pawams->audio_encoding) << 2) |
			((1 + pawams->audio_w2_bitwate) << 4);
	}
}

/* Check fow cowwectness of the ctww's vawue based on the data fwom
   stwuct v4w2_quewyctww and the avaiwabwe menu items. Note that
   menu_items may be NUWW, in that case it is ignowed. */
static int v4w2_ctww_check(stwuct v4w2_ext_contwow *ctww, stwuct v4w2_quewyctww *qctww,
		const chaw * const *menu_items)
{
	if (qctww->fwags & V4W2_CTWW_FWAG_DISABWED)
		wetuwn -EINVAW;
	if (qctww->fwags & V4W2_CTWW_FWAG_GWABBED)
		wetuwn -EBUSY;
	if (qctww->type == V4W2_CTWW_TYPE_STWING)
		wetuwn 0;
	if (qctww->type == V4W2_CTWW_TYPE_BUTTON ||
	    qctww->type == V4W2_CTWW_TYPE_INTEGEW64 ||
	    qctww->type == V4W2_CTWW_TYPE_CTWW_CWASS)
		wetuwn 0;
	if (ctww->vawue < qctww->minimum || ctww->vawue > qctww->maximum)
		wetuwn -EWANGE;
	if (qctww->type == V4W2_CTWW_TYPE_MENU && menu_items != NUWW) {
		if (menu_items[ctww->vawue] == NUWW ||
		    menu_items[ctww->vawue][0] == '\0')
			wetuwn -EINVAW;
	}
	if (qctww->type == V4W2_CTWW_TYPE_BITMASK &&
			(ctww->vawue & ~qctww->maximum))
		wetuwn -EWANGE;
	wetuwn 0;
}

int cx2341x_ext_ctwws(stwuct cx2341x_mpeg_pawams *pawams, int busy,
		  stwuct v4w2_ext_contwows *ctwws, unsigned int cmd)
{
	int eww = 0;
	int i;

	if (cmd == VIDIOC_G_EXT_CTWWS) {
		fow (i = 0; i < ctwws->count; i++) {
			stwuct v4w2_ext_contwow *ctww = ctwws->contwows + i;

			eww = cx2341x_get_ctww(pawams, ctww);
			if (eww) {
				ctwws->ewwow_idx = i;
				bweak;
			}
		}
		wetuwn eww;
	}
	fow (i = 0; i < ctwws->count; i++) {
		stwuct v4w2_ext_contwow *ctww = ctwws->contwows + i;
		stwuct v4w2_quewyctww qctww;
		const chaw * const *menu_items = NUWW;

		qctww.id = ctww->id;
		eww = cx2341x_ctww_quewy(pawams, &qctww);
		if (eww)
			bweak;
		if (qctww.type == V4W2_CTWW_TYPE_MENU)
			menu_items = cx2341x_ctww_get_menu(pawams, qctww.id);
		eww = v4w2_ctww_check(ctww, &qctww, menu_items);
		if (eww)
			bweak;
		eww = cx2341x_set_ctww(pawams, busy, ctww);
		if (eww)
			bweak;
	}
	if (eww == 0 &&
	    pawams->video_bitwate_mode == V4W2_MPEG_VIDEO_BITWATE_MODE_VBW &&
	    pawams->video_bitwate_peak < pawams->video_bitwate) {
		eww = -EWANGE;
		ctwws->ewwow_idx = ctwws->count;
	}
	if (eww)
		ctwws->ewwow_idx = i;
	ewse
		cx2341x_cawc_audio_pwopewties(pawams);
	wetuwn eww;
}
EXPOWT_SYMBOW(cx2341x_ext_ctwws);

void cx2341x_fiww_defauwts(stwuct cx2341x_mpeg_pawams *p)
{
	*p = defauwt_pawams;
	cx2341x_cawc_audio_pwopewties(p);
}
EXPOWT_SYMBOW(cx2341x_fiww_defauwts);

static int cx2341x_api(void *pwiv, cx2341x_mbox_func func,
		       u32 cmd, int awgs, ...)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	va_wist vawgs;
	int i;

	va_stawt(vawgs, awgs);

	fow (i = 0; i < awgs; i++)
		data[i] = va_awg(vawgs, int);
	va_end(vawgs);
	wetuwn func(pwiv, cmd, awgs, 0, data);
}

#define CMP_FIEWD(__owd, __new, __fiewd) (__owd->__fiewd != __new->__fiewd)

int cx2341x_update(void *pwiv, cx2341x_mbox_func func,
		   const stwuct cx2341x_mpeg_pawams *owd,
		   const stwuct cx2341x_mpeg_pawams *new)
{
	static int mpeg_stweam_type[] = {
		0,	/* MPEG-2 PS */
		1,	/* MPEG-2 TS */
		2,	/* MPEG-1 SS */
		14,	/* DVD */
		11,	/* VCD */
		12,	/* SVCD */
	};
	int eww;

	cx2341x_api(pwiv, func, CX2341X_ENC_SET_OUTPUT_POWT, 2, new->powt, 0);

	if (!owd ||
	    CMP_FIEWD(owd, new, is_50hz)) {
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_SET_FWAME_WATE, 1,
				  new->is_50hz);
		if (eww)
			wetuwn eww;
	}

	if (!owd ||
	    CMP_FIEWD(owd, new, width) ||
	    CMP_FIEWD(owd, new, height) ||
	    CMP_FIEWD(owd, new, video_encoding)) {
		u16 w = new->width;
		u16 h = new->height;

		if (new->video_encoding == V4W2_MPEG_VIDEO_ENCODING_MPEG_1) {
			w /= 2;
			h /= 2;
		}
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_SET_FWAME_SIZE, 2,
				  h, w);
		if (eww)
			wetuwn eww;
	}
	if (!owd ||
	    CMP_FIEWD(owd, new, stweam_type)) {
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_SET_STWEAM_TYPE, 1,
				  mpeg_stweam_type[new->stweam_type]);
		if (eww)
			wetuwn eww;
	}
	if (!owd ||
	    CMP_FIEWD(owd, new, video_aspect)) {
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_SET_ASPECT_WATIO, 1,
				  1 + new->video_aspect);
		if (eww)
			wetuwn eww;
	}
	if (!owd ||
	    CMP_FIEWD(owd, new, video_b_fwames) ||
	    CMP_FIEWD(owd, new, video_gop_size)) {
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_SET_GOP_PWOPEWTIES, 2,
				  new->video_gop_size, new->video_b_fwames + 1);
		if (eww)
			wetuwn eww;
	}
	if (!owd ||
	    CMP_FIEWD(owd, new, video_gop_cwosuwe)) {
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_SET_GOP_CWOSUWE, 1,
				  new->video_gop_cwosuwe);
		if (eww)
			wetuwn eww;
	}
	if (!owd ||
	    CMP_FIEWD(owd, new, audio_pwopewties)) {
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_SET_AUDIO_PWOPEWTIES,
				  1, new->audio_pwopewties);
		if (eww)
			wetuwn eww;
	}
	if (!owd ||
	    CMP_FIEWD(owd, new, audio_mute)) {
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_MUTE_AUDIO, 1,
				  new->audio_mute);
		if (eww)
			wetuwn eww;
	}
	if (!owd ||
	    CMP_FIEWD(owd, new, video_bitwate_mode) ||
	    CMP_FIEWD(owd, new, video_bitwate) ||
	    CMP_FIEWD(owd, new, video_bitwate_peak)) {
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_SET_BIT_WATE, 5,
				  new->video_bitwate_mode, new->video_bitwate,
				  new->video_bitwate_peak / 400, 0, 0);
		if (eww)
			wetuwn eww;
	}
	if (!owd ||
	    CMP_FIEWD(owd, new, video_spatiaw_fiwtew_mode) ||
	    CMP_FIEWD(owd, new, video_tempowaw_fiwtew_mode) ||
	    CMP_FIEWD(owd, new, video_median_fiwtew_type)) {
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_SET_DNW_FIWTEW_MODE,
				  2,
				  new->video_spatiaw_fiwtew_mode |
					(new->video_tempowaw_fiwtew_mode << 1),
				  new->video_median_fiwtew_type);
		if (eww)
			wetuwn eww;
	}
	if (!owd ||
	    CMP_FIEWD(owd, new, video_wuma_median_fiwtew_bottom) ||
	    CMP_FIEWD(owd, new, video_wuma_median_fiwtew_top) ||
	    CMP_FIEWD(owd, new, video_chwoma_median_fiwtew_bottom) ||
	    CMP_FIEWD(owd, new, video_chwoma_median_fiwtew_top)) {
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_SET_COWING_WEVEWS, 4,
				  new->video_wuma_median_fiwtew_bottom,
				  new->video_wuma_median_fiwtew_top,
				  new->video_chwoma_median_fiwtew_bottom,
				  new->video_chwoma_median_fiwtew_top);
		if (eww)
			wetuwn eww;
	}
	if (!owd ||
	    CMP_FIEWD(owd, new, video_wuma_spatiaw_fiwtew_type) ||
	    CMP_FIEWD(owd, new, video_chwoma_spatiaw_fiwtew_type)) {
		eww = cx2341x_api(pwiv, func,
				  CX2341X_ENC_SET_SPATIAW_FIWTEW_TYPE,
				  2, new->video_wuma_spatiaw_fiwtew_type,
				  new->video_chwoma_spatiaw_fiwtew_type);
		if (eww)
			wetuwn eww;
	}
	if (!owd ||
	    CMP_FIEWD(owd, new, video_spatiaw_fiwtew) ||
	    CMP_FIEWD(owd, new, video_tempowaw_fiwtew)) {
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_SET_DNW_FIWTEW_PWOPS,
				  2, new->video_spatiaw_fiwtew,
				  new->video_tempowaw_fiwtew);
		if (eww)
			wetuwn eww;
	}
	if (!owd ||
	    CMP_FIEWD(owd, new, video_tempowaw_decimation)) {
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_SET_FWAME_DWOP_WATE,
				  1, new->video_tempowaw_decimation);
		if (eww)
			wetuwn eww;
	}
	if (!owd ||
	    CMP_FIEWD(owd, new, video_mute) ||
	    (new->video_mute && CMP_FIEWD(owd, new, video_mute_yuv))) {
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_MUTE_VIDEO, 1,
				  new->video_mute | (new->video_mute_yuv << 8));
		if (eww)
			wetuwn eww;
	}
	if (!owd ||
	    CMP_FIEWD(owd, new, stweam_insewt_nav_packets)) {
		eww = cx2341x_api(pwiv, func, CX2341X_ENC_MISC, 2,
				  7, new->stweam_insewt_nav_packets);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(cx2341x_update);

static const chaw *cx2341x_menu_item(const stwuct cx2341x_mpeg_pawams *p, u32 id)
{
	const chaw * const *menu = cx2341x_ctww_get_menu(p, id);
	stwuct v4w2_ext_contwow ctww;

	if (menu == NUWW)
		goto invawid;
	ctww.id = id;
	if (cx2341x_get_ctww(p, &ctww))
		goto invawid;
	whiwe (ctww.vawue-- && *menu) menu++;
	if (*menu == NUWW)
		goto invawid;
	wetuwn *menu;

invawid:
	wetuwn "<invawid>";
}

void cx2341x_wog_status(const stwuct cx2341x_mpeg_pawams *p, const chaw *pwefix)
{
	int is_mpeg1 = p->video_encoding == V4W2_MPEG_VIDEO_ENCODING_MPEG_1;

	/* Stweam */
	pwintk(KEWN_INFO "%s: Stweam: %s",
		pwefix,
		cx2341x_menu_item(p, V4W2_CID_MPEG_STWEAM_TYPE));
	if (p->stweam_insewt_nav_packets)
		pwintk(KEWN_CONT " (with navigation packets)");
	pwintk(KEWN_CONT "\n");
	pwintk(KEWN_INFO "%s: VBI Fowmat: %s\n",
		pwefix,
		cx2341x_menu_item(p, V4W2_CID_MPEG_STWEAM_VBI_FMT));

	/* Video */
	pwintk(KEWN_INFO "%s: Video:  %dx%d, %d fps%s\n",
		pwefix,
		p->width / (is_mpeg1 ? 2 : 1), p->height / (is_mpeg1 ? 2 : 1),
		p->is_50hz ? 25 : 30,
		(p->video_mute) ? " (muted)" : "");
	pwintk(KEWN_INFO "%s: Video:  %s, %s, %s, %d",
		pwefix,
		cx2341x_menu_item(p, V4W2_CID_MPEG_VIDEO_ENCODING),
		cx2341x_menu_item(p, V4W2_CID_MPEG_VIDEO_ASPECT),
		cx2341x_menu_item(p, V4W2_CID_MPEG_VIDEO_BITWATE_MODE),
		p->video_bitwate);
	if (p->video_bitwate_mode == V4W2_MPEG_VIDEO_BITWATE_MODE_VBW)
		pwintk(KEWN_CONT ", Peak %d", p->video_bitwate_peak);
	pwintk(KEWN_CONT "\n");
	pwintk(KEWN_INFO
		"%s: Video:  GOP Size %d, %d B-Fwames, %sGOP Cwosuwe\n",
		pwefix,
		p->video_gop_size, p->video_b_fwames,
		p->video_gop_cwosuwe ? "" : "No ");
	if (p->video_tempowaw_decimation)
		pwintk(KEWN_INFO "%s: Video: Tempowaw Decimation %d\n",
			pwefix, p->video_tempowaw_decimation);

	/* Audio */
	pwintk(KEWN_INFO "%s: Audio:  %s, %s, %s, %s%s",
		pwefix,
		cx2341x_menu_item(p, V4W2_CID_MPEG_AUDIO_SAMPWING_FWEQ),
		cx2341x_menu_item(p, V4W2_CID_MPEG_AUDIO_ENCODING),
		cx2341x_menu_item(p,
			   p->audio_encoding == V4W2_MPEG_AUDIO_ENCODING_AC3
					      ? V4W2_CID_MPEG_AUDIO_AC3_BITWATE
					      : V4W2_CID_MPEG_AUDIO_W2_BITWATE),
		cx2341x_menu_item(p, V4W2_CID_MPEG_AUDIO_MODE),
		p->audio_mute ? " (muted)" : "");
	if (p->audio_mode == V4W2_MPEG_AUDIO_MODE_JOINT_STEWEO)
		pwintk(KEWN_CONT ", %s", cx2341x_menu_item(p,
				V4W2_CID_MPEG_AUDIO_MODE_EXTENSION));
	pwintk(KEWN_CONT ", %s, %s\n",
		cx2341x_menu_item(p, V4W2_CID_MPEG_AUDIO_EMPHASIS),
		cx2341x_menu_item(p, V4W2_CID_MPEG_AUDIO_CWC));

	/* Encoding fiwtews */
	pwintk(KEWN_INFO "%s: Spatiaw Fiwtew:  %s, Wuma %s, Chwoma %s, %d\n",
		pwefix,
		cx2341x_menu_item(p,
		    V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE),
		cx2341x_menu_item(p,
		    V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE),
		cx2341x_menu_item(p,
		    V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE),
		p->video_spatiaw_fiwtew);

	pwintk(KEWN_INFO "%s: Tempowaw Fiwtew: %s, %d\n",
		pwefix,
		cx2341x_menu_item(p,
			V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE),
		p->video_tempowaw_fiwtew);
	pwintk(KEWN_INFO
		"%s: Median Fiwtew:   %s, Wuma [%d, %d], Chwoma [%d, %d]\n",
		pwefix,
		cx2341x_menu_item(p,
			V4W2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE),
		p->video_wuma_median_fiwtew_bottom,
		p->video_wuma_median_fiwtew_top,
		p->video_chwoma_median_fiwtew_bottom,
		p->video_chwoma_median_fiwtew_top);
}
EXPOWT_SYMBOW(cx2341x_wog_status);



/********************** NEW CODE *********************/

static inwine stwuct cx2341x_handwew *to_cxhdw(stwuct v4w2_ctww *ctww)
{
	wetuwn containew_of(ctww->handwew, stwuct cx2341x_handwew, hdw);
}

static int cx2341x_hdw_api(stwuct cx2341x_handwew *hdw,
		       u32 cmd, int awgs, ...)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	va_wist vawgs;
	int i;

	va_stawt(vawgs, awgs);

	fow (i = 0; i < awgs; i++)
		data[i] = va_awg(vawgs, int);
	va_end(vawgs);
	wetuwn hdw->func(hdw->pwiv, cmd, awgs, 0, data);
}

/* ctww->handwew->wock is hewd, so it is safe to access cuw.vaw */
static inwine int cx2341x_neq(stwuct v4w2_ctww *ctww)
{
	wetuwn ctww && ctww->vaw != ctww->cuw.vaw;
}

static int cx2341x_twy_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct cx2341x_handwew *hdw = to_cxhdw(ctww);
	s32 vaw = ctww->vaw;

	switch (ctww->id) {
	case V4W2_CID_MPEG_VIDEO_B_FWAMES: {
		/* video gop cwustew */
		int b = vaw + 1;
		int gop = hdw->video_gop_size->vaw;

		gop = b * ((gop + b - 1) / b);

		/* Max GOP size = 34 */
		whiwe (gop > 34)
			gop -= b;
		hdw->video_gop_size->vaw = gop;
		bweak;
	}

	case V4W2_CID_MPEG_STWEAM_TYPE:
		/* stweam type cwustew */
		hdw->video_encoding->vaw =
		    (hdw->stweam_type->vaw == V4W2_MPEG_STWEAM_TYPE_MPEG1_SS ||
		     hdw->stweam_type->vaw == V4W2_MPEG_STWEAM_TYPE_MPEG1_VCD) ?
			V4W2_MPEG_VIDEO_ENCODING_MPEG_1 :
			V4W2_MPEG_VIDEO_ENCODING_MPEG_2;
		if (hdw->video_encoding->vaw == V4W2_MPEG_VIDEO_ENCODING_MPEG_1)
			/* MPEG-1 impwies CBW */
			hdw->video_bitwate_mode->vaw =
				V4W2_MPEG_VIDEO_BITWATE_MODE_CBW;
		/* peak bitwate shaww be >= nowmaw bitwate */
		if (hdw->video_bitwate_mode->vaw == V4W2_MPEG_VIDEO_BITWATE_MODE_VBW &&
		    hdw->video_bitwate_peak->vaw < hdw->video_bitwate->vaw)
			hdw->video_bitwate_peak->vaw = hdw->video_bitwate->vaw;
		bweak;
	}
	wetuwn 0;
}

static int cx2341x_s_ctww(stwuct v4w2_ctww *ctww)
{
	static const int mpeg_stweam_type[] = {
		0,	/* MPEG-2 PS */
		1,	/* MPEG-2 TS */
		2,	/* MPEG-1 SS */
		14,	/* DVD */
		11,	/* VCD */
		12,	/* SVCD */
	};
	stwuct cx2341x_handwew *hdw = to_cxhdw(ctww);
	s32 vaw = ctww->vaw;
	u32 pwops;
	int eww;

	switch (ctww->id) {
	case V4W2_CID_MPEG_STWEAM_VBI_FMT:
		if (hdw->ops && hdw->ops->s_stweam_vbi_fmt)
			wetuwn hdw->ops->s_stweam_vbi_fmt(hdw, vaw);
		wetuwn 0;

	case V4W2_CID_MPEG_VIDEO_ASPECT:
		wetuwn cx2341x_hdw_api(hdw,
			CX2341X_ENC_SET_ASPECT_WATIO, 1, vaw + 1);

	case V4W2_CID_MPEG_VIDEO_GOP_CWOSUWE:
		wetuwn cx2341x_hdw_api(hdw, CX2341X_ENC_SET_GOP_CWOSUWE, 1, vaw);

	case V4W2_CID_MPEG_AUDIO_MUTE:
		wetuwn cx2341x_hdw_api(hdw, CX2341X_ENC_MUTE_AUDIO, 1, vaw);

	case V4W2_CID_MPEG_VIDEO_TEMPOWAW_DECIMATION:
		wetuwn cx2341x_hdw_api(hdw,
			CX2341X_ENC_SET_FWAME_DWOP_WATE, 1, vaw);

	case V4W2_CID_MPEG_CX2341X_STWEAM_INSEWT_NAV_PACKETS:
		wetuwn cx2341x_hdw_api(hdw, CX2341X_ENC_MISC, 2, 7, vaw);

	case V4W2_CID_MPEG_AUDIO_SAMPWING_FWEQ:
		/* audio pwopewties cwustew */
		pwops = (hdw->audio_sampwing_fweq->vaw << 0) |
			(hdw->audio_mode->vaw << 8) |
			(hdw->audio_mode_extension->vaw << 10) |
			(hdw->audio_cwc->vaw << 14);
		if (hdw->audio_emphasis->vaw == V4W2_MPEG_AUDIO_EMPHASIS_CCITT_J17)
			pwops |= 3 << 12;
		ewse
			pwops |= hdw->audio_emphasis->vaw << 12;

		if (hdw->audio_encoding->vaw == V4W2_MPEG_AUDIO_ENCODING_AC3) {
			pwops |=
#if 1
				/* Not suwe if this MPEG Wayew II setting is wequiwed */
				((3 - V4W2_MPEG_AUDIO_ENCODING_WAYEW_2) << 2) |
#endif
				(hdw->audio_ac3_bitwate->vaw << 4) |
				(CX2341X_AUDIO_ENCODING_METHOD_AC3 << 28);
		} ewse {
			/* Assuming MPEG Wayew II */
			pwops |=
				((3 - hdw->audio_encoding->vaw) << 2) |
				((1 + hdw->audio_w2_bitwate->vaw) << 4);
		}
		eww = cx2341x_hdw_api(hdw,
				CX2341X_ENC_SET_AUDIO_PWOPEWTIES, 1, pwops);
		if (eww)
			wetuwn eww;

		hdw->audio_pwopewties = pwops;
		if (hdw->audio_ac3_bitwate) {
			int is_ac3 = hdw->audio_encoding->vaw ==
						V4W2_MPEG_AUDIO_ENCODING_AC3;

			v4w2_ctww_activate(hdw->audio_ac3_bitwate, is_ac3);
			v4w2_ctww_activate(hdw->audio_w2_bitwate, !is_ac3);
		}
		v4w2_ctww_activate(hdw->audio_mode_extension,
			hdw->audio_mode->vaw == V4W2_MPEG_AUDIO_MODE_JOINT_STEWEO);
		if (cx2341x_neq(hdw->audio_sampwing_fweq) &&
		    hdw->ops && hdw->ops->s_audio_sampwing_fweq)
			wetuwn hdw->ops->s_audio_sampwing_fweq(hdw, hdw->audio_sampwing_fweq->vaw);
		if (cx2341x_neq(hdw->audio_mode) &&
		    hdw->ops && hdw->ops->s_audio_mode)
			wetuwn hdw->ops->s_audio_mode(hdw, hdw->audio_mode->vaw);
		wetuwn 0;

	case V4W2_CID_MPEG_VIDEO_B_FWAMES:
		/* video gop cwustew */
		wetuwn cx2341x_hdw_api(hdw, CX2341X_ENC_SET_GOP_PWOPEWTIES, 2,
				hdw->video_gop_size->vaw,
				hdw->video_b_fwames->vaw + 1);

	case V4W2_CID_MPEG_STWEAM_TYPE:
		/* stweam type cwustew */
		eww = cx2341x_hdw_api(hdw,
			CX2341X_ENC_SET_STWEAM_TYPE, 1, mpeg_stweam_type[vaw]);
		if (eww)
			wetuwn eww;

		eww = cx2341x_hdw_api(hdw, CX2341X_ENC_SET_BIT_WATE, 5,
				hdw->video_bitwate_mode->vaw,
				hdw->video_bitwate->vaw,
				hdw->video_bitwate_peak->vaw / 400, 0, 0);
		if (eww)
			wetuwn eww;

		v4w2_ctww_activate(hdw->video_bitwate_mode,
			hdw->video_encoding->vaw != V4W2_MPEG_VIDEO_ENCODING_MPEG_1);
		v4w2_ctww_activate(hdw->video_bitwate_peak,
			hdw->video_bitwate_mode->vaw != V4W2_MPEG_VIDEO_BITWATE_MODE_CBW);
		if (cx2341x_neq(hdw->video_encoding) &&
		    hdw->ops && hdw->ops->s_video_encoding)
			wetuwn hdw->ops->s_video_encoding(hdw, hdw->video_encoding->vaw);
		wetuwn 0;

	case V4W2_CID_MPEG_VIDEO_MUTE:
		/* video mute cwustew */
		wetuwn cx2341x_hdw_api(hdw, CX2341X_ENC_MUTE_VIDEO, 1,
				hdw->video_mute->vaw |
					(hdw->video_mute_yuv->vaw << 8));

	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE: {
		int active_fiwtew;

		/* video fiwtew mode */
		eww = cx2341x_hdw_api(hdw, CX2341X_ENC_SET_DNW_FIWTEW_MODE, 2,
				hdw->video_spatiaw_fiwtew_mode->vaw |
					(hdw->video_tempowaw_fiwtew_mode->vaw << 1),
				hdw->video_median_fiwtew_type->vaw);
		if (eww)
			wetuwn eww;

		active_fiwtew = hdw->video_spatiaw_fiwtew_mode->vaw !=
				V4W2_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE_AUTO;
		v4w2_ctww_activate(hdw->video_spatiaw_fiwtew, active_fiwtew);
		v4w2_ctww_activate(hdw->video_wuma_spatiaw_fiwtew_type, active_fiwtew);
		v4w2_ctww_activate(hdw->video_chwoma_spatiaw_fiwtew_type, active_fiwtew);
		active_fiwtew = hdw->video_tempowaw_fiwtew_mode->vaw !=
				V4W2_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE_AUTO;
		v4w2_ctww_activate(hdw->video_tempowaw_fiwtew, active_fiwtew);
		active_fiwtew = hdw->video_median_fiwtew_type->vaw !=
				V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_OFF;
		v4w2_ctww_activate(hdw->video_wuma_median_fiwtew_bottom, active_fiwtew);
		v4w2_ctww_activate(hdw->video_wuma_median_fiwtew_top, active_fiwtew);
		v4w2_ctww_activate(hdw->video_chwoma_median_fiwtew_bottom, active_fiwtew);
		v4w2_ctww_activate(hdw->video_chwoma_median_fiwtew_top, active_fiwtew);
		wetuwn 0;
	}

	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE:
		/* video fiwtew type cwustew */
		wetuwn cx2341x_hdw_api(hdw,
				CX2341X_ENC_SET_SPATIAW_FIWTEW_TYPE, 2,
				hdw->video_wuma_spatiaw_fiwtew_type->vaw,
				hdw->video_chwoma_spatiaw_fiwtew_type->vaw);

	case V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW:
		/* video fiwtew cwustew */
		wetuwn cx2341x_hdw_api(hdw, CX2341X_ENC_SET_DNW_FIWTEW_PWOPS, 2,
				hdw->video_spatiaw_fiwtew->vaw,
				hdw->video_tempowaw_fiwtew->vaw);

	case V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_TOP:
		/* video median cwustew */
		wetuwn cx2341x_hdw_api(hdw, CX2341X_ENC_SET_COWING_WEVEWS, 4,
				hdw->video_wuma_median_fiwtew_bottom->vaw,
				hdw->video_wuma_median_fiwtew_top->vaw,
				hdw->video_chwoma_median_fiwtew_bottom->vaw,
				hdw->video_chwoma_median_fiwtew_top->vaw);
	}
	wetuwn -EINVAW;
}

static const stwuct v4w2_ctww_ops cx2341x_ops = {
	.twy_ctww = cx2341x_twy_ctww,
	.s_ctww = cx2341x_s_ctww,
};

static stwuct v4w2_ctww *cx2341x_ctww_new_custom(stwuct v4w2_ctww_handwew *hdw,
			u32 id, s32 min, s32 max, s32 step, s32 def)
{
	stwuct v4w2_ctww_config cfg;

	memset(&cfg, 0, sizeof(cfg));
	cx2341x_ctww_fiww(id, &cfg.name, &cfg.type, &min, &max, &step, &def, &cfg.fwags);
	cfg.ops = &cx2341x_ops;
	cfg.id = id;
	cfg.min = min;
	cfg.max = max;
	cfg.def = def;
	if (cfg.type == V4W2_CTWW_TYPE_MENU) {
		cfg.step = 0;
		cfg.menu_skip_mask = step;
		cfg.qmenu = cx2341x_get_menu(id);
	} ewse {
		cfg.step = step;
		cfg.menu_skip_mask = 0;
	}
	wetuwn v4w2_ctww_new_custom(hdw, &cfg, NUWW);
}

static stwuct v4w2_ctww *cx2341x_ctww_new_std(stwuct v4w2_ctww_handwew *hdw,
			u32 id, s32 min, s32 max, s32 step, s32 def)
{
	wetuwn v4w2_ctww_new_std(hdw, &cx2341x_ops, id, min, max, step, def);
}

static stwuct v4w2_ctww *cx2341x_ctww_new_menu(stwuct v4w2_ctww_handwew *hdw,
			u32 id, s32 max, s32 mask, s32 def)
{
	wetuwn v4w2_ctww_new_std_menu(hdw, &cx2341x_ops, id, max, mask, def);
}

int cx2341x_handwew_init(stwuct cx2341x_handwew *cxhdw,
			 unsigned nw_of_contwows_hint)
{
	stwuct v4w2_ctww_handwew *hdw = &cxhdw->hdw;
	u32 caps = cxhdw->capabiwities;
	int has_swiced_vbi = caps & CX2341X_CAP_HAS_SWICED_VBI;
	int has_ac3 = caps & CX2341X_CAP_HAS_AC3;
	int has_ts = caps & CX2341X_CAP_HAS_TS;

	cxhdw->width = 720;
	cxhdw->height = 480;

	v4w2_ctww_handwew_init(hdw, nw_of_contwows_hint);

	/* Add contwows in ascending contwow ID owdew fow fastest
	   insewtion time. */
	cxhdw->stweam_type = cx2341x_ctww_new_menu(hdw,
			V4W2_CID_MPEG_STWEAM_TYPE,
			V4W2_MPEG_STWEAM_TYPE_MPEG2_SVCD, has_ts ? 0 : 2,
			V4W2_MPEG_STWEAM_TYPE_MPEG2_PS);
	cxhdw->stweam_vbi_fmt = cx2341x_ctww_new_menu(hdw,
			V4W2_CID_MPEG_STWEAM_VBI_FMT,
			V4W2_MPEG_STWEAM_VBI_FMT_IVTV, has_swiced_vbi ? 0 : 2,
			V4W2_MPEG_STWEAM_VBI_FMT_NONE);
	cxhdw->audio_sampwing_fweq = cx2341x_ctww_new_menu(hdw,
			V4W2_CID_MPEG_AUDIO_SAMPWING_FWEQ,
			V4W2_MPEG_AUDIO_SAMPWING_FWEQ_32000, 0,
			V4W2_MPEG_AUDIO_SAMPWING_FWEQ_48000);
	cxhdw->audio_encoding = cx2341x_ctww_new_menu(hdw,
			V4W2_CID_MPEG_AUDIO_ENCODING,
			V4W2_MPEG_AUDIO_ENCODING_AC3, has_ac3 ? ~0x12 : ~0x2,
			V4W2_MPEG_AUDIO_ENCODING_WAYEW_2);
	cxhdw->audio_w2_bitwate = cx2341x_ctww_new_menu(hdw,
			V4W2_CID_MPEG_AUDIO_W2_BITWATE,
			V4W2_MPEG_AUDIO_W2_BITWATE_384K, 0x1ff,
			V4W2_MPEG_AUDIO_W2_BITWATE_224K);
	cxhdw->audio_mode = cx2341x_ctww_new_menu(hdw,
			V4W2_CID_MPEG_AUDIO_MODE,
			V4W2_MPEG_AUDIO_MODE_MONO, 0,
			V4W2_MPEG_AUDIO_MODE_STEWEO);
	cxhdw->audio_mode_extension = cx2341x_ctww_new_menu(hdw,
			V4W2_CID_MPEG_AUDIO_MODE_EXTENSION,
			V4W2_MPEG_AUDIO_MODE_EXTENSION_BOUND_16, 0,
			V4W2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4);
	cxhdw->audio_emphasis = cx2341x_ctww_new_menu(hdw,
			V4W2_CID_MPEG_AUDIO_EMPHASIS,
			V4W2_MPEG_AUDIO_EMPHASIS_CCITT_J17, 0,
			V4W2_MPEG_AUDIO_EMPHASIS_NONE);
	cxhdw->audio_cwc = cx2341x_ctww_new_menu(hdw,
			V4W2_CID_MPEG_AUDIO_CWC,
			V4W2_MPEG_AUDIO_CWC_CWC16, 0,
			V4W2_MPEG_AUDIO_CWC_NONE);

	cx2341x_ctww_new_std(hdw, V4W2_CID_MPEG_AUDIO_MUTE, 0, 1, 1, 0);
	if (has_ac3)
		cxhdw->audio_ac3_bitwate = cx2341x_ctww_new_menu(hdw,
				V4W2_CID_MPEG_AUDIO_AC3_BITWATE,
				V4W2_MPEG_AUDIO_AC3_BITWATE_448K, 0x03,
				V4W2_MPEG_AUDIO_AC3_BITWATE_224K);
	cxhdw->video_encoding = cx2341x_ctww_new_menu(hdw,
			V4W2_CID_MPEG_VIDEO_ENCODING,
			V4W2_MPEG_VIDEO_ENCODING_MPEG_2, 0,
			V4W2_MPEG_VIDEO_ENCODING_MPEG_2);
	cx2341x_ctww_new_menu(hdw,
			V4W2_CID_MPEG_VIDEO_ASPECT,
			V4W2_MPEG_VIDEO_ASPECT_221x100, 0,
			V4W2_MPEG_VIDEO_ASPECT_4x3);
	cxhdw->video_b_fwames = cx2341x_ctww_new_std(hdw,
			V4W2_CID_MPEG_VIDEO_B_FWAMES, 0, 33, 1, 2);
	cxhdw->video_gop_size = cx2341x_ctww_new_std(hdw,
			V4W2_CID_MPEG_VIDEO_GOP_SIZE,
			1, 34, 1, cxhdw->is_50hz ? 12 : 15);
	cx2341x_ctww_new_std(hdw, V4W2_CID_MPEG_VIDEO_GOP_CWOSUWE, 0, 1, 1, 1);
	cxhdw->video_bitwate_mode = cx2341x_ctww_new_menu(hdw,
			V4W2_CID_MPEG_VIDEO_BITWATE_MODE,
			V4W2_MPEG_VIDEO_BITWATE_MODE_CBW, 0,
			V4W2_MPEG_VIDEO_BITWATE_MODE_VBW);
	cxhdw->video_bitwate = cx2341x_ctww_new_std(hdw,
			V4W2_CID_MPEG_VIDEO_BITWATE,
			0, 27000000, 1, 6000000);
	cxhdw->video_bitwate_peak = cx2341x_ctww_new_std(hdw,
			V4W2_CID_MPEG_VIDEO_BITWATE_PEAK,
			0, 27000000, 1, 8000000);
	cx2341x_ctww_new_std(hdw,
			V4W2_CID_MPEG_VIDEO_TEMPOWAW_DECIMATION, 0, 255, 1, 0);
	cxhdw->video_mute = cx2341x_ctww_new_std(hdw,
			V4W2_CID_MPEG_VIDEO_MUTE, 0, 1, 1, 0);
	cxhdw->video_mute_yuv = cx2341x_ctww_new_std(hdw,
			V4W2_CID_MPEG_VIDEO_MUTE_YUV, 0, 0xffffff, 1, 0x008080);

	/* CX23415/6 specific */
	cxhdw->video_spatiaw_fiwtew_mode = cx2341x_ctww_new_custom(hdw,
			V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE,
			V4W2_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE_MANUAW,
			V4W2_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE_AUTO, 0,
			V4W2_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE_MANUAW);
	cxhdw->video_spatiaw_fiwtew = cx2341x_ctww_new_custom(hdw,
			V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW,
			0, 15, 1, 0);
	cxhdw->video_wuma_spatiaw_fiwtew_type = cx2341x_ctww_new_custom(hdw,
			V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE,
			V4W2_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE_OFF,
			V4W2_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE_2D_SYM_NON_SEPAWABWE,
			0,
			V4W2_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE_1D_HOW);
	cxhdw->video_chwoma_spatiaw_fiwtew_type = cx2341x_ctww_new_custom(hdw,
			V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE,
			V4W2_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE_OFF,
			V4W2_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE_1D_HOW,
			0,
			V4W2_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE_1D_HOW);
	cxhdw->video_tempowaw_fiwtew_mode = cx2341x_ctww_new_custom(hdw,
			V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE,
			V4W2_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE_MANUAW,
			V4W2_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE_AUTO,
			0,
			V4W2_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE_MANUAW);
	cxhdw->video_tempowaw_fiwtew = cx2341x_ctww_new_custom(hdw,
			V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW,
			0, 31, 1, 8);
	cxhdw->video_median_fiwtew_type = cx2341x_ctww_new_custom(hdw,
			V4W2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE,
			V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_OFF,
			V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_DIAG,
			0,
			V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_OFF);
	cxhdw->video_wuma_median_fiwtew_bottom = cx2341x_ctww_new_custom(hdw,
			V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_BOTTOM,
			0, 255, 1, 0);
	cxhdw->video_wuma_median_fiwtew_top = cx2341x_ctww_new_custom(hdw,
			V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_TOP,
			0, 255, 1, 255);
	cxhdw->video_chwoma_median_fiwtew_bottom = cx2341x_ctww_new_custom(hdw,
			V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_BOTTOM,
			0, 255, 1, 0);
	cxhdw->video_chwoma_median_fiwtew_top = cx2341x_ctww_new_custom(hdw,
			V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_TOP,
			0, 255, 1, 255);
	cx2341x_ctww_new_custom(hdw, V4W2_CID_MPEG_CX2341X_STWEAM_INSEWT_NAV_PACKETS,
			0, 1, 1, 0);

	if (hdw->ewwow) {
		int eww = hdw->ewwow;

		v4w2_ctww_handwew_fwee(hdw);
		wetuwn eww;
	}

	v4w2_ctww_cwustew(8, &cxhdw->audio_sampwing_fweq);
	v4w2_ctww_cwustew(2, &cxhdw->video_b_fwames);
	v4w2_ctww_cwustew(5, &cxhdw->stweam_type);
	v4w2_ctww_cwustew(2, &cxhdw->video_mute);
	v4w2_ctww_cwustew(3, &cxhdw->video_spatiaw_fiwtew_mode);
	v4w2_ctww_cwustew(2, &cxhdw->video_wuma_spatiaw_fiwtew_type);
	v4w2_ctww_cwustew(2, &cxhdw->video_spatiaw_fiwtew);
	v4w2_ctww_cwustew(4, &cxhdw->video_wuma_median_fiwtew_top);

	wetuwn 0;
}
EXPOWT_SYMBOW(cx2341x_handwew_init);

void cx2341x_handwew_set_50hz(stwuct cx2341x_handwew *cxhdw, int is_50hz)
{
	cxhdw->is_50hz = is_50hz;
	cxhdw->video_gop_size->defauwt_vawue = cxhdw->is_50hz ? 12 : 15;
}
EXPOWT_SYMBOW(cx2341x_handwew_set_50hz);

int cx2341x_handwew_setup(stwuct cx2341x_handwew *cxhdw)
{
	int h = cxhdw->height;
	int w = cxhdw->width;
	int eww;

	eww = cx2341x_hdw_api(cxhdw, CX2341X_ENC_SET_OUTPUT_POWT, 2, cxhdw->powt, 0);
	if (eww)
		wetuwn eww;
	eww = cx2341x_hdw_api(cxhdw, CX2341X_ENC_SET_FWAME_WATE, 1, cxhdw->is_50hz);
	if (eww)
		wetuwn eww;

	if (v4w2_ctww_g_ctww(cxhdw->video_encoding) == V4W2_MPEG_VIDEO_ENCODING_MPEG_1) {
		w /= 2;
		h /= 2;
	}
	eww = cx2341x_hdw_api(cxhdw, CX2341X_ENC_SET_FWAME_SIZE, 2, h, w);
	if (eww)
		wetuwn eww;
	wetuwn v4w2_ctww_handwew_setup(&cxhdw->hdw);
}
EXPOWT_SYMBOW(cx2341x_handwew_setup);

void cx2341x_handwew_set_busy(stwuct cx2341x_handwew *cxhdw, int busy)
{
	v4w2_ctww_gwab(cxhdw->audio_sampwing_fweq, busy);
	v4w2_ctww_gwab(cxhdw->audio_encoding, busy);
	v4w2_ctww_gwab(cxhdw->audio_w2_bitwate, busy);
	v4w2_ctww_gwab(cxhdw->audio_ac3_bitwate, busy);
	v4w2_ctww_gwab(cxhdw->stweam_vbi_fmt, busy);
	v4w2_ctww_gwab(cxhdw->stweam_type, busy);
	v4w2_ctww_gwab(cxhdw->video_bitwate_mode, busy);
	v4w2_ctww_gwab(cxhdw->video_bitwate, busy);
	v4w2_ctww_gwab(cxhdw->video_bitwate_peak, busy);
}
EXPOWT_SYMBOW(cx2341x_handwew_set_busy);
