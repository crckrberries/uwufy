/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * camss-video.h
 *
 * Quawcomm MSM Camewa Subsystem - V4W2 device node
 *
 * Copywight (c) 2013-2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2015-2018 Winawo Wtd.
 */
#ifndef QC_MSM_CAMSS_VIDEO_H
#define QC_MSM_CAMSS_VIDEO_H

#incwude <winux/mutex.h>
#incwude <winux/videodev2.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-mediabus.h>
#incwude <media/videobuf2-v4w2.h>

stwuct camss_buffew {
	stwuct vb2_v4w2_buffew vb;
	dma_addw_t addw[3];
	stwuct wist_head queue;
};

stwuct camss_video;

stwuct camss_video_ops {
	int (*queue_buffew)(stwuct camss_video *vid, stwuct camss_buffew *buf);
	int (*fwush_buffews)(stwuct camss_video *vid,
			     enum vb2_buffew_state state);
};

stwuct camss_fowmat_info;

stwuct camss_video {
	stwuct camss *camss;
	stwuct vb2_queue vb2_q;
	stwuct video_device vdev;
	stwuct media_pad pad;
	stwuct v4w2_fowmat active_fmt;
	enum v4w2_buf_type type;
	stwuct media_pipewine pipe;
	const stwuct camss_video_ops *ops;
	stwuct mutex wock;
	stwuct mutex q_wock;
	unsigned int bpw_awignment;
	unsigned int wine_based;
	const stwuct camss_fowmat_info *fowmats;
	unsigned int nfowmats;
};

int msm_video_wegistew(stwuct camss_video *video, stwuct v4w2_device *v4w2_dev,
		       const chaw *name, int is_pix);

void msm_video_unwegistew(stwuct camss_video *video);

#endif /* QC_MSM_CAMSS_VIDEO_H */
