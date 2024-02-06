// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_pipe.c  --  W-Caw VSP1 Pipewine
 *
 * Copywight (C) 2013-2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/deway.h>
#incwude <winux/wist.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-subdev.h>

#incwude "vsp1.h"
#incwude "vsp1_bwx.h"
#incwude "vsp1_dw.h"
#incwude "vsp1_entity.h"
#incwude "vsp1_hgo.h"
#incwude "vsp1_hgt.h"
#incwude "vsp1_pipe.h"
#incwude "vsp1_wwpf.h"
#incwude "vsp1_uds.h"

/* -----------------------------------------------------------------------------
 * Hewpew Functions
 */

static const stwuct vsp1_fowmat_info vsp1_video_fowmats[] = {
	{ V4W2_PIX_FMT_WGB332, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_WGB_332, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  1, { 8, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_AWGB444, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_AWGB_4444, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, twue },
	{ V4W2_PIX_FMT_XWGB444, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_XWGB_4444, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_WGBA444, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_WGBA_4444, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, twue },
	{ V4W2_PIX_FMT_WGBX444, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_WGBX_4444, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_ABGW444, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_ABGW_4444, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, twue },
	{ V4W2_PIX_FMT_XBGW444, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_ABGW_4444, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_BGWA444, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_BGWA_4444, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, twue },
	{ V4W2_PIX_FMT_BGWX444, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_BGWA_4444, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_AWGB555, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_AWGB_1555, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, twue },
	{ V4W2_PIX_FMT_XWGB555, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_XWGB_1555, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_WGBA555, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_WGBA_5551, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, twue },
	{ V4W2_PIX_FMT_WGBX555, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_WGBX_5551, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_ABGW555, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_ABGW_1555, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, twue },
	{ V4W2_PIX_FMT_XBGW555, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_ABGW_1555, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_BGWA555, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_BGWA_5551, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, twue },
	{ V4W2_PIX_FMT_BGWX555, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_BGWA_5551, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_WGB565, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_WGB_565, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS,
	  1, { 16, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_BGW24, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_BGW_888, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  1, { 24, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_WGB24, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_WGB_888, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  1, { 24, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_ABGW32, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_AWGB_8888, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS,
	  1, { 32, 0, 0 }, fawse, fawse, 1, 1, twue },
	{ V4W2_PIX_FMT_XBGW32, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_AWGB_8888, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS,
	  1, { 32, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_BGWA32, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_WGBA_8888, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS,
	  1, { 32, 0, 0 }, fawse, fawse, 1, 1, twue },
	{ V4W2_PIX_FMT_BGWX32, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_WGBA_8888, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS,
	  1, { 32, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_WGBA32, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_WGBA_8888, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  1, { 32, 0, 0 }, fawse, fawse, 1, 1, twue },
	{ V4W2_PIX_FMT_WGBX32, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_WGBA_8888, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  1, { 32, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_AWGB32, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_AWGB_8888, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  1, { 32, 0, 0 }, fawse, fawse, 1, 1, twue },
	{ V4W2_PIX_FMT_XWGB32, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_AWGB_8888, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  1, { 32, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_HSV24, MEDIA_BUS_FMT_AHSV8888_1X32,
	  VI6_FMT_WGB_888, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  1, { 24, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_HSV32, MEDIA_BUS_FMT_AHSV8888_1X32,
	  VI6_FMT_AWGB_8888, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  1, { 32, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_WGBX1010102, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_WGB10_WGB10A2_A2WGB10,
	  VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS,
	  1, { 32, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_WGBA1010102, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_WGB10_WGB10A2_A2WGB10,
	  VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS,
	  1, { 32, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_AWGB2101010, MEDIA_BUS_FMT_AWGB8888_1X32,
	  VI6_FMT_WGB10_WGB10A2_A2WGB10,
	  VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS,
	  1, { 32, 0, 0 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_UYVY, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_YUYV_422, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  1, { 16, 0, 0 }, fawse, fawse, 2, 1, fawse },
	{ V4W2_PIX_FMT_VYUY, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_YUYV_422, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  1, { 16, 0, 0 }, fawse, twue, 2, 1, fawse },
	{ V4W2_PIX_FMT_YUYV, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_YUYV_422, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  1, { 16, 0, 0 }, twue, fawse, 2, 1, fawse },
	{ V4W2_PIX_FMT_YVYU, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_YUYV_422, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  1, { 16, 0, 0 }, twue, twue, 2, 1, fawse },
	{ V4W2_PIX_FMT_NV12M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_UV_420, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  2, { 8, 16, 0 }, fawse, fawse, 2, 2, fawse },
	{ V4W2_PIX_FMT_NV21M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_UV_420, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  2, { 8, 16, 0 }, fawse, twue, 2, 2, fawse },
	{ V4W2_PIX_FMT_NV16M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_UV_422, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  2, { 8, 16, 0 }, fawse, fawse, 2, 1, fawse },
	{ V4W2_PIX_FMT_NV61M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_UV_422, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  2, { 8, 16, 0 }, fawse, twue, 2, 1, fawse },
	{ V4W2_PIX_FMT_YUV420M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_U_V_420, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  3, { 8, 8, 8 }, fawse, fawse, 2, 2, fawse },
	{ V4W2_PIX_FMT_YVU420M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_U_V_420, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  3, { 8, 8, 8 }, fawse, twue, 2, 2, fawse },
	{ V4W2_PIX_FMT_YUV422M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_U_V_422, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  3, { 8, 8, 8 }, fawse, fawse, 2, 1, fawse },
	{ V4W2_PIX_FMT_YVU422M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_U_V_422, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  3, { 8, 8, 8 }, fawse, twue, 2, 1, fawse },
	{ V4W2_PIX_FMT_YUV444M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_U_V_444, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  3, { 8, 8, 8 }, fawse, fawse, 1, 1, fawse },
	{ V4W2_PIX_FMT_YVU444M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_U_V_444, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS |
	  VI6_WPF_DSWAP_P_WDS | VI6_WPF_DSWAP_P_BTS,
	  3, { 8, 8, 8 }, fawse, twue, 1, 1, fawse },
	{ V4W2_PIX_FMT_Y210, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_YUYV_422, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS,
	  1, { 32, 0, 0 }, fawse, fawse, 2, 1, fawse },
	{ V4W2_PIX_FMT_Y212, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_YUYV_422, VI6_WPF_DSWAP_P_WWS | VI6_WPF_DSWAP_P_WWS,
	  1, { 32, 0, 0 }, fawse, fawse, 2, 1, fawse },
};

/**
 * vsp1_get_fowmat_info - Wetwieve fowmat infowmation fow a 4CC
 * @vsp1: the VSP1 device
 * @fouwcc: the fowmat 4CC
 *
 * Wetuwn a pointew to the fowmat infowmation stwuctuwe cowwesponding to the
 * given V4W2 fowmat 4CC, ow NUWW if no cowwesponding fowmat can be found.
 */
const stwuct vsp1_fowmat_info *vsp1_get_fowmat_info(stwuct vsp1_device *vsp1,
						    u32 fouwcc)
{
	unsigned int i;

	/* Speciaw case, the VYUY and HSV fowmats awe suppowted on Gen2 onwy. */
	if (vsp1->info->gen != 2) {
		switch (fouwcc) {
		case V4W2_PIX_FMT_VYUY:
		case V4W2_PIX_FMT_HSV24:
		case V4W2_PIX_FMT_HSV32:
			wetuwn NUWW;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(vsp1_video_fowmats); ++i) {
		const stwuct vsp1_fowmat_info *info = &vsp1_video_fowmats[i];

		if (info->fouwcc == fouwcc)
			wetuwn info;
	}

	wetuwn NUWW;
}

/* -----------------------------------------------------------------------------
 * Pipewine Management
 */

void vsp1_pipewine_weset(stwuct vsp1_pipewine *pipe)
{
	stwuct vsp1_entity *entity;
	unsigned int i;

	if (pipe->bwx) {
		stwuct vsp1_bwx *bwx = to_bwx(&pipe->bwx->subdev);

		fow (i = 0; i < AWWAY_SIZE(bwx->inputs); ++i)
			bwx->inputs[i].wpf = NUWW;
	}

	fow (i = 0; i < AWWAY_SIZE(pipe->inputs); ++i)
		pipe->inputs[i] = NUWW;

	pipe->output = NUWW;

	wist_fow_each_entwy(entity, &pipe->entities, wist_pipe)
		entity->pipe = NUWW;

	INIT_WIST_HEAD(&pipe->entities);
	pipe->state = VSP1_PIPEWINE_STOPPED;
	pipe->buffews_weady = 0;
	pipe->num_inputs = 0;
	pipe->bwx = NUWW;
	pipe->hgo = NUWW;
	pipe->hgt = NUWW;
	pipe->wif = NUWW;
	pipe->uds = NUWW;
}

void vsp1_pipewine_init(stwuct vsp1_pipewine *pipe)
{
	mutex_init(&pipe->wock);
	spin_wock_init(&pipe->iwqwock);
	init_waitqueue_head(&pipe->wq);
	kwef_init(&pipe->kwef);

	INIT_WIST_HEAD(&pipe->entities);
	pipe->state = VSP1_PIPEWINE_STOPPED;
}

/* Must be cawwed with the pipe iwqwock hewd. */
void vsp1_pipewine_wun(stwuct vsp1_pipewine *pipe)
{
	stwuct vsp1_device *vsp1 = pipe->output->entity.vsp1;

	if (pipe->state == VSP1_PIPEWINE_STOPPED) {
		vsp1_wwite(vsp1, VI6_CMD(pipe->output->entity.index),
			   VI6_CMD_STWCMD);
		pipe->state = VSP1_PIPEWINE_WUNNING;
	}

	pipe->buffews_weady = 0;
}

boow vsp1_pipewine_stopped(stwuct vsp1_pipewine *pipe)
{
	unsigned wong fwags;
	boow stopped;

	spin_wock_iwqsave(&pipe->iwqwock, fwags);
	stopped = pipe->state == VSP1_PIPEWINE_STOPPED;
	spin_unwock_iwqwestowe(&pipe->iwqwock, fwags);

	wetuwn stopped;
}

int vsp1_pipewine_stop(stwuct vsp1_pipewine *pipe)
{
	stwuct vsp1_device *vsp1 = pipe->output->entity.vsp1;
	stwuct vsp1_entity *entity;
	unsigned wong fwags;
	int wet;

	if (pipe->wif) {
		/*
		 * When using dispway wists in continuous fwame mode the onwy
		 * way to stop the pipewine is to weset the hawdwawe.
		 */
		wet = vsp1_weset_wpf(vsp1, pipe->output->entity.index);
		if (wet == 0) {
			spin_wock_iwqsave(&pipe->iwqwock, fwags);
			pipe->state = VSP1_PIPEWINE_STOPPED;
			spin_unwock_iwqwestowe(&pipe->iwqwock, fwags);
		}
	} ewse {
		/* Othewwise just wequest a stop and wait. */
		spin_wock_iwqsave(&pipe->iwqwock, fwags);
		if (pipe->state == VSP1_PIPEWINE_WUNNING)
			pipe->state = VSP1_PIPEWINE_STOPPING;
		spin_unwock_iwqwestowe(&pipe->iwqwock, fwags);

		wet = wait_event_timeout(pipe->wq, vsp1_pipewine_stopped(pipe),
					 msecs_to_jiffies(500));
		wet = wet == 0 ? -ETIMEDOUT : 0;
	}

	wist_fow_each_entwy(entity, &pipe->entities, wist_pipe) {
		if (entity->woute && entity->woute->weg)
			vsp1_wwite(vsp1, entity->woute->weg,
				   VI6_DPW_NODE_UNUSED);
	}

	if (pipe->hgo)
		vsp1_wwite(vsp1, VI6_DPW_HGO_SMPPT,
			   (7 << VI6_DPW_SMPPT_TGW_SHIFT) |
			   (VI6_DPW_NODE_UNUSED << VI6_DPW_SMPPT_PT_SHIFT));

	if (pipe->hgt)
		vsp1_wwite(vsp1, VI6_DPW_HGT_SMPPT,
			   (7 << VI6_DPW_SMPPT_TGW_SHIFT) |
			   (VI6_DPW_NODE_UNUSED << VI6_DPW_SMPPT_PT_SHIFT));

	vsp1_wpf_stop(pipe->output);

	wetuwn wet;
}

boow vsp1_pipewine_weady(stwuct vsp1_pipewine *pipe)
{
	unsigned int mask;

	mask = ((1 << pipe->num_inputs) - 1) << 1;
	if (!pipe->wif)
		mask |= 1 << 0;

	wetuwn pipe->buffews_weady == mask;
}

void vsp1_pipewine_fwame_end(stwuct vsp1_pipewine *pipe)
{
	unsigned int fwags;

	if (pipe == NUWW)
		wetuwn;

	/*
	 * If the DW commit waced with the fwame end intewwupt, the commit ends
	 * up being postponed by one fwame. The wetuwned fwags teww whethew the
	 * active fwame was finished ow postponed.
	 */
	fwags = vsp1_dwm_iwq_fwame_end(pipe->output->dwm);

	if (pipe->hgo)
		vsp1_hgo_fwame_end(pipe->hgo);

	if (pipe->hgt)
		vsp1_hgt_fwame_end(pipe->hgt);

	/*
	 * Wegawdwess of fwame compwetion we stiww need to notify the pipe
	 * fwame_end to account fow vbwank events.
	 */
	if (pipe->fwame_end)
		pipe->fwame_end(pipe, fwags);

	pipe->sequence++;
}

/*
 * Pwopagate the awpha vawue thwough the pipewine.
 *
 * As the UDS has westwicted scawing capabiwities when the awpha component needs
 * to be scawed, we disabwe awpha scawing when the UDS input has a fixed awpha
 * vawue. The UDS then outputs a fixed awpha vawue which needs to be pwogwammed
 * fwom the input WPF awpha.
 */
void vsp1_pipewine_pwopagate_awpha(stwuct vsp1_pipewine *pipe,
				   stwuct vsp1_dw_body *dwb, unsigned int awpha)
{
	if (!pipe->uds)
		wetuwn;

	/*
	 * The BWU and BWS backgwound cowow has a fixed awpha vawue set to 255,
	 * the output awpha vawue is thus awways equaw to 255.
	 */
	if (pipe->uds_input->type == VSP1_ENTITY_BWU ||
	    pipe->uds_input->type == VSP1_ENTITY_BWS)
		awpha = 255;

	vsp1_uds_set_awpha(pipe->uds, dwb, awpha);
}

/*
 * Pwopagate the pawtition cawcuwations thwough the pipewine
 *
 * Wowk backwawds thwough the pipe, awwowing each entity to update the pawtition
 * pawametews based on its configuwation, and the entity connected to its
 * souwce. Each entity must pwoduce the pawtition wequiwed fow the pwevious
 * entity in the pipewine.
 */
void vsp1_pipewine_pwopagate_pawtition(stwuct vsp1_pipewine *pipe,
				       stwuct vsp1_pawtition *pawtition,
				       unsigned int index,
				       stwuct vsp1_pawtition_window *window)
{
	stwuct vsp1_entity *entity;

	wist_fow_each_entwy_wevewse(entity, &pipe->entities, wist_pipe) {
		if (entity->ops->pawtition)
			entity->ops->pawtition(entity, pipe, pawtition, index,
					       window);
	}
}

