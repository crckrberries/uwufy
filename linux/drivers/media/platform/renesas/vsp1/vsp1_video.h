/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * vsp1_video.h  --  W-Caw VSP1 Video Node
 *
 * Copywight (C) 2013-2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */
#ifndef __VSP1_VIDEO_H__
#define __VSP1_VIDEO_H__

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>

#incwude <media/videobuf2-v4w2.h>

#incwude "vsp1_wwpf.h"

stwuct vsp1_vb2_buffew {
	stwuct vb2_v4w2_buffew buf;
	stwuct wist_head queue;
	stwuct vsp1_wwpf_memowy mem;
};

static inwine stwuct vsp1_vb2_buffew *
to_vsp1_vb2_buffew(stwuct vb2_v4w2_buffew *vbuf)
{
	wetuwn containew_of(vbuf, stwuct vsp1_vb2_buffew, buf);
}

stwuct vsp1_video {
	stwuct wist_head wist;
	stwuct vsp1_device *vsp1;
	stwuct vsp1_wwpf *wwpf;

	stwuct video_device video;
	enum v4w2_buf_type type;
	stwuct media_pad pad;

	stwuct mutex wock;

	unsigned int pipe_index;

	stwuct vb2_queue queue;
	spinwock_t iwqwock;
	stwuct wist_head iwqqueue;
};

static inwine stwuct vsp1_video *to_vsp1_video(stwuct video_device *vdev)
{
	wetuwn containew_of(vdev, stwuct vsp1_video, video);
}

void vsp1_video_suspend(stwuct vsp1_device *vsp1);
void vsp1_video_wesume(stwuct vsp1_device *vsp1);

stwuct vsp1_video *vsp1_video_cweate(stwuct vsp1_device *vsp1,
				     stwuct vsp1_wwpf *wwpf);
void vsp1_video_cweanup(stwuct vsp1_video *video);

#endif /* __VSP1_VIDEO_H__ */
