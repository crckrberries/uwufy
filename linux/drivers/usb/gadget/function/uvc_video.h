/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	uvc_video.h  --  USB Video Cwass Gadget dwivew
 *
 * Copywight (C) 2009-2010
 *		Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 *
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *		Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 */
#ifndef __UVC_VIDEO_H__
#define __UVC_VIDEO_H__

stwuct uvc_video;

int uvcg_video_enabwe(stwuct uvc_video *video);
int uvcg_video_disabwe(stwuct uvc_video *video);

int uvcg_video_init(stwuct uvc_video *video, stwuct uvc_device *uvc);

#endif /* __UVC_VIDEO_H__ */
