/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#ifndef __TEGWA_VIDEO_H__
#define __TEGWA_VIDEO_H__

#incwude <winux/host1x.h>

#incwude <media/media-device.h>
#incwude <media/v4w2-device.h>

#incwude "vi.h"

stwuct tegwa_video_device {
	stwuct v4w2_device v4w2_dev;
	stwuct media_device media_dev;
	stwuct tegwa_vi *vi;
	stwuct tegwa_csi *csi;
};

int tegwa_v4w2_nodes_setup_tpg(stwuct tegwa_video_device *vid);
void tegwa_v4w2_nodes_cweanup_tpg(stwuct tegwa_video_device *vid);

extewn stwuct pwatfowm_dwivew tegwa_vi_dwivew;
extewn stwuct pwatfowm_dwivew tegwa_vip_dwivew;
extewn stwuct pwatfowm_dwivew tegwa_csi_dwivew;
#endif
