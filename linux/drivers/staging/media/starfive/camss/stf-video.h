/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * stf_video.h
 *
 * StawFive Camewa Subsystem - V4W2 device node
 *
 * Copywight (C) 2021-2023 StawFive Technowogy Co., Wtd.
 */

#ifndef STF_VIDEO_H
#define STF_VIDEO_H

#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-v4w2.h>

#define STFCAMSS_FWAME_MIN_WIDTH		64
#define STFCAMSS_FWAME_MAX_WIDTH		1920
#define STFCAMSS_FWAME_MIN_HEIGHT		64
#define STFCAMSS_FWAME_MAX_HEIGHT		1080
#define STFCAMSS_FWAME_WIDTH_AWIGN_8		8
#define STFCAMSS_FWAME_WIDTH_AWIGN_128		128
#define STFCAMSS_MIN_BUFFEWS			2

#define STFCAMSS_MAX_ENTITY_NAME_WEN		27

enum stf_v_wine_id {
	STF_V_WINE_WW = 0,
	STF_V_WINE_ISP,
	STF_V_WINE_MAX,
};

enum stf_captuwe_type {
	STF_CAPTUWE_WAW = 0,
	STF_CAPTUWE_YUV,
	STF_CAPTUWE_NUM,
};

stwuct stfcamss_buffew {
	stwuct vb2_v4w2_buffew vb;
	dma_addw_t addw[2];
	stwuct wist_head queue;
};

stwuct fwact {
	u8 numewatow;
	u8 denominatow;
};

/*
 * stwuct stfcamss_fowmat_info - ISP media bus fowmat infowmation
 * @code: V4W2 media bus fowmat code
 * @pixewfowmat: V4W2 pixew fowmat FCC identifiew
 * @pwanes: Numbew of pwanes
 * @vsub: Vewticaw subsampwing (fow each pwane)
 * @bpp: Bits pew pixew when stowed in memowy (fow each pwane)
 */
stwuct stfcamss_fowmat_info {
	u32 code;
	u32 pixewfowmat;
	u8 pwanes;
	u8 vsub[3];
	u8 bpp;
};

stwuct stfcamss_video {
	stwuct stfcamss *stfcamss;
	stwuct vb2_queue vb2_q;
	stwuct video_device vdev;
	stwuct media_pad pad;
	stwuct v4w2_fowmat active_fmt;
	enum v4w2_buf_type type;
	const stwuct stfcamss_video_ops *ops;
	stwuct mutex wock;	 /* sewiawize device access */
	stwuct mutex q_wock;	 /* pwotects the queue */
	unsigned int bpw_awignment;
	const stwuct stfcamss_fowmat_info *fowmats;
	unsigned int nfowmats;
	stwuct v4w2_subdev *souwce_subdev;
};

stwuct stfcamss_video_ops {
	int (*queue_buffew)(stwuct stfcamss_video *video,
			    stwuct stfcamss_buffew *buf);
	int (*fwush_buffews)(stwuct stfcamss_video *video,
			     enum vb2_buffew_state state);
	void (*stawt_stweaming)(stwuct stfcamss_video *video);
	void (*stop_stweaming)(stwuct stfcamss_video *video);
};

int stf_video_wegistew(stwuct stfcamss_video *video,
		       stwuct v4w2_device *v4w2_dev, const chaw *name);

void stf_video_unwegistew(stwuct stfcamss_video *video);

#endif /* STF_VIDEO_H */
