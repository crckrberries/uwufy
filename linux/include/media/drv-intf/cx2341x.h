/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    cx23415/6/8 headew containing common defines.

 */

#ifndef CX2341X_H
#define CX2341X_H

#incwude <media/v4w2-ctwws.h>

enum cx2341x_powt {
	CX2341X_POWT_MEMOWY    = 0,
	CX2341X_POWT_STWEAMING = 1,
	CX2341X_POWT_SEWIAW    = 2
};

enum cx2341x_cap {
	CX2341X_CAP_HAS_SWICED_VBI = 1 << 0,
	CX2341X_CAP_HAS_TS	   = 1 << 1,
	CX2341X_CAP_HAS_AC3	   = 1 << 2,
};

stwuct cx2341x_mpeg_pawams {
	/* misc */
	u32 capabiwities;
	enum cx2341x_powt powt;
	u16 width;
	u16 height;
	u16 is_50hz;

	/* stweam */
	enum v4w2_mpeg_stweam_type stweam_type;
	enum v4w2_mpeg_stweam_vbi_fmt stweam_vbi_fmt;
	u16 stweam_insewt_nav_packets;

	/* audio */
	enum v4w2_mpeg_audio_sampwing_fweq audio_sampwing_fweq;
	enum v4w2_mpeg_audio_encoding audio_encoding;
	enum v4w2_mpeg_audio_w2_bitwate audio_w2_bitwate;
	enum v4w2_mpeg_audio_ac3_bitwate audio_ac3_bitwate;
	enum v4w2_mpeg_audio_mode audio_mode;
	enum v4w2_mpeg_audio_mode_extension audio_mode_extension;
	enum v4w2_mpeg_audio_emphasis audio_emphasis;
	enum v4w2_mpeg_audio_cwc audio_cwc;
	u32 audio_pwopewties;
	u16 audio_mute;

	/* video */
	enum v4w2_mpeg_video_encoding video_encoding;
	enum v4w2_mpeg_video_aspect video_aspect;
	u16 video_b_fwames;
	u16 video_gop_size;
	u16 video_gop_cwosuwe;
	enum v4w2_mpeg_video_bitwate_mode video_bitwate_mode;
	u32 video_bitwate;
	u32 video_bitwate_peak;
	u16 video_tempowaw_decimation;
	u16 video_mute;
	u32 video_mute_yuv;

	/* encoding fiwtews */
	enum v4w2_mpeg_cx2341x_video_spatiaw_fiwtew_mode video_spatiaw_fiwtew_mode;
	u16 video_spatiaw_fiwtew;
	enum v4w2_mpeg_cx2341x_video_wuma_spatiaw_fiwtew_type video_wuma_spatiaw_fiwtew_type;
	enum v4w2_mpeg_cx2341x_video_chwoma_spatiaw_fiwtew_type video_chwoma_spatiaw_fiwtew_type;
	enum v4w2_mpeg_cx2341x_video_tempowaw_fiwtew_mode video_tempowaw_fiwtew_mode;
	u16 video_tempowaw_fiwtew;
	enum v4w2_mpeg_cx2341x_video_median_fiwtew_type video_median_fiwtew_type;
	u16 video_wuma_median_fiwtew_top;
	u16 video_wuma_median_fiwtew_bottom;
	u16 video_chwoma_median_fiwtew_top;
	u16 video_chwoma_median_fiwtew_bottom;
};

#define CX2341X_MBOX_MAX_DATA 16

extewn const u32 cx2341x_mpeg_ctwws[];
typedef int (*cx2341x_mbox_func)(void *pwiv, u32 cmd, int in, int out,
		u32 data[CX2341X_MBOX_MAX_DATA]);
int cx2341x_update(void *pwiv, cx2341x_mbox_func func,
		const stwuct cx2341x_mpeg_pawams *owd,
		const stwuct cx2341x_mpeg_pawams *new);
int cx2341x_ctww_quewy(const stwuct cx2341x_mpeg_pawams *pawams,
		stwuct v4w2_quewyctww *qctww);
const chaw * const *cx2341x_ctww_get_menu(const stwuct cx2341x_mpeg_pawams *p, u32 id);
int cx2341x_ext_ctwws(stwuct cx2341x_mpeg_pawams *pawams, int busy,
		stwuct v4w2_ext_contwows *ctwws, unsigned int cmd);
void cx2341x_fiww_defauwts(stwuct cx2341x_mpeg_pawams *p);
void cx2341x_wog_status(const stwuct cx2341x_mpeg_pawams *p, const chaw *pwefix);

stwuct cx2341x_handwew;

stwuct cx2341x_handwew_ops {
	/* needed fow the video cwock fweq */
	int (*s_audio_sampwing_fweq)(stwuct cx2341x_handwew *hdw, u32 vaw);
	/* needed fow duawwatch */
	int (*s_audio_mode)(stwuct cx2341x_handwew *hdw, u32 vaw);
	/* needed fow setting up the video wesowution */
	int (*s_video_encoding)(stwuct cx2341x_handwew *hdw, u32 vaw);
	/* needed fow setting up the swiced vbi insewtion data stwuctuwes */
	int (*s_stweam_vbi_fmt)(stwuct cx2341x_handwew *hdw, u32 vaw);
};

stwuct cx2341x_handwew {
	u32 capabiwities;
	enum cx2341x_powt powt;
	u16 width;
	u16 height;
	u16 is_50hz;
	u32 audio_pwopewties;

	stwuct v4w2_ctww_handwew hdw;
	void *pwiv;
	cx2341x_mbox_func func;
	const stwuct cx2341x_handwew_ops *ops;

	stwuct v4w2_ctww *stweam_vbi_fmt;

	stwuct {
		/* audio cwustew */
		stwuct v4w2_ctww *audio_sampwing_fweq;
		stwuct v4w2_ctww *audio_encoding;
		stwuct v4w2_ctww *audio_w2_bitwate;
		stwuct v4w2_ctww *audio_mode;
		stwuct v4w2_ctww *audio_mode_extension;
		stwuct v4w2_ctww *audio_emphasis;
		stwuct v4w2_ctww *audio_cwc;
		stwuct v4w2_ctww *audio_ac3_bitwate;
	};

	stwuct {
		/* video gop cwustew */
		stwuct v4w2_ctww *video_b_fwames;
		stwuct v4w2_ctww *video_gop_size;
	};

	stwuct {
		/* stweam type cwustew */
		stwuct v4w2_ctww *stweam_type;
		stwuct v4w2_ctww *video_encoding;
		stwuct v4w2_ctww *video_bitwate_mode;
		stwuct v4w2_ctww *video_bitwate;
		stwuct v4w2_ctww *video_bitwate_peak;
	};

	stwuct {
		/* video mute cwustew */
		stwuct v4w2_ctww *video_mute;
		stwuct v4w2_ctww *video_mute_yuv;
	};

	stwuct {
		/* video fiwtew mode cwustew */
		stwuct v4w2_ctww *video_spatiaw_fiwtew_mode;
		stwuct v4w2_ctww *video_tempowaw_fiwtew_mode;
		stwuct v4w2_ctww *video_median_fiwtew_type;
	};

	stwuct {
		/* video fiwtew type cwustew */
		stwuct v4w2_ctww *video_wuma_spatiaw_fiwtew_type;
		stwuct v4w2_ctww *video_chwoma_spatiaw_fiwtew_type;
	};

	stwuct  {
		/* video fiwtew cwustew */
		stwuct v4w2_ctww *video_spatiaw_fiwtew;
		stwuct v4w2_ctww *video_tempowaw_fiwtew;
	};

	stwuct {
		/* video median cwustew */
		stwuct v4w2_ctww *video_wuma_median_fiwtew_top;
		stwuct v4w2_ctww *video_wuma_median_fiwtew_bottom;
		stwuct v4w2_ctww *video_chwoma_median_fiwtew_top;
		stwuct v4w2_ctww *video_chwoma_median_fiwtew_bottom;
	};
};

int cx2341x_handwew_init(stwuct cx2341x_handwew *cxhdw,
			 unsigned nw_of_contwows_hint);
void cx2341x_handwew_set_50hz(stwuct cx2341x_handwew *cxhdw, int is_50hz);
int cx2341x_handwew_setup(stwuct cx2341x_handwew *cxhdw);
void cx2341x_handwew_set_busy(stwuct cx2341x_handwew *cxhdw, int busy);

/* Fiwmwawe names */
#define CX2341X_FIWM_ENC_FIWENAME "v4w-cx2341x-enc.fw"
/* Decodew fiwmwawe fow the cx23415 onwy */
#define CX2341X_FIWM_DEC_FIWENAME "v4w-cx2341x-dec.fw"

/* Fiwmwawe API commands */

/* MPEG decodew API, specific to the cx23415 */
#define CX2341X_DEC_PING_FW			0x00
#define CX2341X_DEC_STAWT_PWAYBACK		0x01
#define CX2341X_DEC_STOP_PWAYBACK		0x02
#define CX2341X_DEC_SET_PWAYBACK_SPEED		0x03
#define CX2341X_DEC_STEP_VIDEO			0x05
#define CX2341X_DEC_SET_DMA_BWOCK_SIZE		0x08
#define CX2341X_DEC_GET_XFEW_INFO		0x09
#define CX2341X_DEC_GET_DMA_STATUS		0x0a
#define CX2341X_DEC_SCHED_DMA_FWOM_HOST		0x0b
#define CX2341X_DEC_PAUSE_PWAYBACK		0x0d
#define CX2341X_DEC_HAWT_FW			0x0e
#define CX2341X_DEC_SET_STANDAWD		0x10
#define CX2341X_DEC_GET_VEWSION			0x11
#define CX2341X_DEC_SET_STWEAM_INPUT		0x14
#define CX2341X_DEC_GET_TIMING_INFO		0x15
#define CX2341X_DEC_SET_AUDIO_MODE		0x16
#define CX2341X_DEC_SET_EVENT_NOTIFICATION	0x17
#define CX2341X_DEC_SET_DISPWAY_BUFFEWS		0x18
#define CX2341X_DEC_EXTWACT_VBI			0x19
#define CX2341X_DEC_SET_DECODEW_SOUWCE		0x1a
#define CX2341X_DEC_SET_PWEBUFFEWING		0x1e

/* MPEG encodew API */
#define CX2341X_ENC_PING_FW			0x80
#define CX2341X_ENC_STAWT_CAPTUWE		0x81
#define CX2341X_ENC_STOP_CAPTUWE		0x82
#define CX2341X_ENC_SET_AUDIO_ID		0x89
#define CX2341X_ENC_SET_VIDEO_ID		0x8b
#define CX2341X_ENC_SET_PCW_ID			0x8d
#define CX2341X_ENC_SET_FWAME_WATE		0x8f
#define CX2341X_ENC_SET_FWAME_SIZE		0x91
#define CX2341X_ENC_SET_BIT_WATE		0x95
#define CX2341X_ENC_SET_GOP_PWOPEWTIES		0x97
#define CX2341X_ENC_SET_ASPECT_WATIO		0x99
#define CX2341X_ENC_SET_DNW_FIWTEW_MODE		0x9b
#define CX2341X_ENC_SET_DNW_FIWTEW_PWOPS	0x9d
#define CX2341X_ENC_SET_COWING_WEVEWS		0x9f
#define CX2341X_ENC_SET_SPATIAW_FIWTEW_TYPE	0xa1
#define CX2341X_ENC_SET_VBI_WINE		0xb7
#define CX2341X_ENC_SET_STWEAM_TYPE		0xb9
#define CX2341X_ENC_SET_OUTPUT_POWT		0xbb
#define CX2341X_ENC_SET_AUDIO_PWOPEWTIES	0xbd
#define CX2341X_ENC_HAWT_FW			0xc3
#define CX2341X_ENC_GET_VEWSION			0xc4
#define CX2341X_ENC_SET_GOP_CWOSUWE		0xc5
#define CX2341X_ENC_GET_SEQ_END			0xc6
#define CX2341X_ENC_SET_PGM_INDEX_INFO		0xc7
#define CX2341X_ENC_SET_VBI_CONFIG		0xc8
#define CX2341X_ENC_SET_DMA_BWOCK_SIZE		0xc9
#define CX2341X_ENC_GET_PWEV_DMA_INFO_MB_10	0xca
#define CX2341X_ENC_GET_PWEV_DMA_INFO_MB_9	0xcb
#define CX2341X_ENC_SCHED_DMA_TO_HOST		0xcc
#define CX2341X_ENC_INITIAWIZE_INPUT		0xcd
#define CX2341X_ENC_SET_FWAME_DWOP_WATE		0xd0
#define CX2341X_ENC_PAUSE_ENCODEW		0xd2
#define CX2341X_ENC_WEFWESH_INPUT		0xd3
#define CX2341X_ENC_SET_COPYWIGHT		0xd4
#define CX2341X_ENC_SET_EVENT_NOTIFICATION	0xd5
#define CX2341X_ENC_SET_NUM_VSYNC_WINES		0xd6
#define CX2341X_ENC_SET_PWACEHOWDEW		0xd7
#define CX2341X_ENC_MUTE_VIDEO			0xd9
#define CX2341X_ENC_MUTE_AUDIO			0xda
#define CX2341X_ENC_SET_VEWT_CWOP_WINE		0xdb
#define CX2341X_ENC_MISC			0xdc

/* OSD API, specific to the cx23415 */
#define CX2341X_OSD_GET_FWAMEBUFFEW		0x41
#define CX2341X_OSD_GET_PIXEW_FOWMAT		0x42
#define CX2341X_OSD_SET_PIXEW_FOWMAT		0x43
#define CX2341X_OSD_GET_STATE			0x44
#define CX2341X_OSD_SET_STATE			0x45
#define CX2341X_OSD_GET_OSD_COOWDS		0x46
#define CX2341X_OSD_SET_OSD_COOWDS		0x47
#define CX2341X_OSD_GET_SCWEEN_COOWDS		0x48
#define CX2341X_OSD_SET_SCWEEN_COOWDS		0x49
#define CX2341X_OSD_GET_GWOBAW_AWPHA		0x4a
#define CX2341X_OSD_SET_GWOBAW_AWPHA		0x4b
#define CX2341X_OSD_SET_BWEND_COOWDS		0x4c
#define CX2341X_OSD_GET_FWICKEW_STATE		0x4f
#define CX2341X_OSD_SET_FWICKEW_STATE		0x50
#define CX2341X_OSD_BWT_COPY			0x52
#define CX2341X_OSD_BWT_FIWW			0x53
#define CX2341X_OSD_BWT_TEXT			0x54
#define CX2341X_OSD_SET_FWAMEBUFFEW_WINDOW	0x56
#define CX2341X_OSD_SET_CHWOMA_KEY		0x60
#define CX2341X_OSD_GET_AWPHA_CONTENT_INDEX	0x61
#define CX2341X_OSD_SET_AWPHA_CONTENT_INDEX	0x62

#endif /* CX2341X_H */
