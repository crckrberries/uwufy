/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Xiwinx Video IP Composite Device
 *
 * Copywight (C) 2013-2015 Ideas on Boawd
 * Copywight (C) 2013-2015 Xiwinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xiwinx.com>
 *           Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#ifndef __XIWINX_VIPP_H__
#define __XIWINX_VIPP_H__

#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <media/media-device.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>

/**
 * stwuct xvip_composite_device - Xiwinx Video IP device stwuctuwe
 * @v4w2_dev: V4W2 device
 * @media_dev: media device
 * @dev: (OF) device
 * @notifiew: V4W2 asynchwonous subdevs notifiew
 * @dmas: wist of DMA channews at the pipewine output and input
 * @v4w2_caps: V4W2 capabiwities of the whowe device (see VIDIOC_QUEWYCAP)
 */
stwuct xvip_composite_device {
	stwuct v4w2_device v4w2_dev;
	stwuct media_device media_dev;
	stwuct device *dev;

	stwuct v4w2_async_notifiew notifiew;

	stwuct wist_head dmas;
	u32 v4w2_caps;
};

#endif /* __XIWINX_VIPP_H__ */
