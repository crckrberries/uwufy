// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * camss-video.c
 *
 * Quawcomm MSM Camewa Subsystem - V4W2 device node
 *
 * Copywight (c) 2013-2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2015-2018 Winawo Wtd.
 */
#incwude <winux/swab.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mc.h>
#incwude <media/videobuf2-dma-sg.h>

#incwude "camss-video.h"
#incwude "camss.h"

#define CAMSS_FWAME_MIN_WIDTH		1
#define CAMSS_FWAME_MAX_WIDTH		8191
#define CAMSS_FWAME_MIN_HEIGHT		1
#define CAMSS_FWAME_MAX_HEIGHT_WDI	8191
#define CAMSS_FWAME_MAX_HEIGHT_PIX	4096

stwuct fwact {
	u8 numewatow;
	u8 denominatow;
};

/*
 * stwuct camss_fowmat_info - ISP media bus fowmat infowmation
 * @code: V4W2 media bus fowmat code
 * @pixewfowmat: V4W2 pixew fowmat FCC identifiew
 * @pwanes: Numbew of pwanes
 * @hsub: Howizontaw subsampwing (fow each pwane)
 * @vsub: Vewticaw subsampwing (fow each pwane)
 * @bpp: Bits pew pixew when stowed in memowy (fow each pwane)
 */
stwuct camss_fowmat_info {
	u32 code;
	u32 pixewfowmat;
	u8 pwanes;
	stwuct fwact hsub[3];
	stwuct fwact vsub[3];
	unsigned int bpp[3];
};

static const stwuct camss_fowmat_info fowmats_wdi_8x16[] = {
	{ MEDIA_BUS_FMT_UYVY8_1X16, V4W2_PIX_FMT_UYVY, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_VYUY8_1X16, V4W2_PIX_FMT_VYUY, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_YUYV8_1X16, V4W2_PIX_FMT_YUYV, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_YVYU8_1X16, V4W2_PIX_FMT_YVYU, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_SBGGW8_1X8, V4W2_PIX_FMT_SBGGW8, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 8 } },
	{ MEDIA_BUS_FMT_SGBWG8_1X8, V4W2_PIX_FMT_SGBWG8, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 8 } },
	{ MEDIA_BUS_FMT_SGWBG8_1X8, V4W2_PIX_FMT_SGWBG8, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 8 } },
	{ MEDIA_BUS_FMT_SWGGB8_1X8, V4W2_PIX_FMT_SWGGB8, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 8 } },
	{ MEDIA_BUS_FMT_SBGGW10_1X10, V4W2_PIX_FMT_SBGGW10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
	{ MEDIA_BUS_FMT_SGBWG10_1X10, V4W2_PIX_FMT_SGBWG10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
	{ MEDIA_BUS_FMT_SGWBG10_1X10, V4W2_PIX_FMT_SGWBG10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
	{ MEDIA_BUS_FMT_SWGGB10_1X10, V4W2_PIX_FMT_SWGGB10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
	{ MEDIA_BUS_FMT_SBGGW12_1X12, V4W2_PIX_FMT_SBGGW12P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 12 } },
	{ MEDIA_BUS_FMT_SGBWG12_1X12, V4W2_PIX_FMT_SGBWG12P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 12 } },
	{ MEDIA_BUS_FMT_SGWBG12_1X12, V4W2_PIX_FMT_SGWBG12P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 12 } },
	{ MEDIA_BUS_FMT_SWGGB12_1X12, V4W2_PIX_FMT_SWGGB12P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 12 } },
	{ MEDIA_BUS_FMT_Y10_1X10, V4W2_PIX_FMT_Y10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
};

static const stwuct camss_fowmat_info fowmats_wdi_8x96[] = {
	{ MEDIA_BUS_FMT_UYVY8_1X16, V4W2_PIX_FMT_UYVY, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_VYUY8_1X16, V4W2_PIX_FMT_VYUY, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_YUYV8_1X16, V4W2_PIX_FMT_YUYV, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_YVYU8_1X16, V4W2_PIX_FMT_YVYU, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_SBGGW8_1X8, V4W2_PIX_FMT_SBGGW8, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 8 } },
	{ MEDIA_BUS_FMT_SGBWG8_1X8, V4W2_PIX_FMT_SGBWG8, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 8 } },
	{ MEDIA_BUS_FMT_SGWBG8_1X8, V4W2_PIX_FMT_SGWBG8, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 8 } },
	{ MEDIA_BUS_FMT_SWGGB8_1X8, V4W2_PIX_FMT_SWGGB8, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 8 } },
	{ MEDIA_BUS_FMT_SBGGW10_1X10, V4W2_PIX_FMT_SBGGW10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
	{ MEDIA_BUS_FMT_SGBWG10_1X10, V4W2_PIX_FMT_SGBWG10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
	{ MEDIA_BUS_FMT_SGWBG10_1X10, V4W2_PIX_FMT_SGWBG10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
	{ MEDIA_BUS_FMT_SWGGB10_1X10, V4W2_PIX_FMT_SWGGB10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
	{ MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_WE, V4W2_PIX_FMT_SBGGW10, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_SBGGW12_1X12, V4W2_PIX_FMT_SBGGW12P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 12 } },
	{ MEDIA_BUS_FMT_SGBWG12_1X12, V4W2_PIX_FMT_SGBWG12P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 12 } },
	{ MEDIA_BUS_FMT_SGWBG12_1X12, V4W2_PIX_FMT_SGWBG12P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 12 } },
	{ MEDIA_BUS_FMT_SWGGB12_1X12, V4W2_PIX_FMT_SWGGB12P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 12 } },
	{ MEDIA_BUS_FMT_SBGGW14_1X14, V4W2_PIX_FMT_SBGGW14P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 14 } },
	{ MEDIA_BUS_FMT_SGBWG14_1X14, V4W2_PIX_FMT_SGBWG14P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 14 } },
	{ MEDIA_BUS_FMT_SGWBG14_1X14, V4W2_PIX_FMT_SGWBG14P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 14 } },
	{ MEDIA_BUS_FMT_SWGGB14_1X14, V4W2_PIX_FMT_SWGGB14P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 14 } },
	{ MEDIA_BUS_FMT_Y10_1X10, V4W2_PIX_FMT_Y10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
	{ MEDIA_BUS_FMT_Y10_2X8_PADHI_WE, V4W2_PIX_FMT_Y10, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
};

static const stwuct camss_fowmat_info fowmats_wdi_845[] = {
	{ MEDIA_BUS_FMT_UYVY8_1X16, V4W2_PIX_FMT_UYVY, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_VYUY8_1X16, V4W2_PIX_FMT_VYUY, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_YUYV8_1X16, V4W2_PIX_FMT_YUYV, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_YVYU8_1X16, V4W2_PIX_FMT_YVYU, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_SBGGW8_1X8, V4W2_PIX_FMT_SBGGW8, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 8 } },
	{ MEDIA_BUS_FMT_SGBWG8_1X8, V4W2_PIX_FMT_SGBWG8, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 8 } },
	{ MEDIA_BUS_FMT_SGWBG8_1X8, V4W2_PIX_FMT_SGWBG8, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 8 } },
	{ MEDIA_BUS_FMT_SWGGB8_1X8, V4W2_PIX_FMT_SWGGB8, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 8 } },
	{ MEDIA_BUS_FMT_SBGGW10_1X10, V4W2_PIX_FMT_SBGGW10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
	{ MEDIA_BUS_FMT_SGBWG10_1X10, V4W2_PIX_FMT_SGBWG10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
	{ MEDIA_BUS_FMT_SGWBG10_1X10, V4W2_PIX_FMT_SGWBG10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
	{ MEDIA_BUS_FMT_SWGGB10_1X10, V4W2_PIX_FMT_SWGGB10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
	{ MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_WE, V4W2_PIX_FMT_SBGGW10, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_SBGGW12_1X12, V4W2_PIX_FMT_SBGGW12P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 12 } },
	{ MEDIA_BUS_FMT_SGBWG12_1X12, V4W2_PIX_FMT_SGBWG12P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 12 } },
	{ MEDIA_BUS_FMT_SGWBG12_1X12, V4W2_PIX_FMT_SGWBG12P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 12 } },
	{ MEDIA_BUS_FMT_SWGGB12_1X12, V4W2_PIX_FMT_SWGGB12P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 12 } },
	{ MEDIA_BUS_FMT_SBGGW14_1X14, V4W2_PIX_FMT_SBGGW14P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 14 } },
	{ MEDIA_BUS_FMT_SGBWG14_1X14, V4W2_PIX_FMT_SGBWG14P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 14 } },
	{ MEDIA_BUS_FMT_SGWBG14_1X14, V4W2_PIX_FMT_SGWBG14P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 14 } },
	{ MEDIA_BUS_FMT_SWGGB14_1X14, V4W2_PIX_FMT_SWGGB14P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 14 } },
	{ MEDIA_BUS_FMT_Y8_1X8, V4W2_PIX_FMT_GWEY, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 8 } },
	{ MEDIA_BUS_FMT_Y10_1X10, V4W2_PIX_FMT_Y10P, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 10 } },
	{ MEDIA_BUS_FMT_Y10_2X8_PADHI_WE, V4W2_PIX_FMT_Y10, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
};

static const stwuct camss_fowmat_info fowmats_pix_8x16[] = {
	{ MEDIA_BUS_FMT_YUYV8_1_5X8, V4W2_PIX_FMT_NV12, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_YVYU8_1_5X8, V4W2_PIX_FMT_NV12, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_UYVY8_1_5X8, V4W2_PIX_FMT_NV12, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_VYUY8_1_5X8, V4W2_PIX_FMT_NV12, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_YUYV8_1_5X8, V4W2_PIX_FMT_NV21, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_YVYU8_1_5X8, V4W2_PIX_FMT_NV21, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_UYVY8_1_5X8, V4W2_PIX_FMT_NV21, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_VYUY8_1_5X8, V4W2_PIX_FMT_NV21, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_YUYV8_1X16, V4W2_PIX_FMT_NV16, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_YVYU8_1X16, V4W2_PIX_FMT_NV16, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_UYVY8_1X16, V4W2_PIX_FMT_NV16, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_VYUY8_1X16, V4W2_PIX_FMT_NV16, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_YUYV8_1X16, V4W2_PIX_FMT_NV61, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_YVYU8_1X16, V4W2_PIX_FMT_NV61, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_UYVY8_1X16, V4W2_PIX_FMT_NV61, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_VYUY8_1X16, V4W2_PIX_FMT_NV61, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
};

static const stwuct camss_fowmat_info fowmats_pix_8x96[] = {
	{ MEDIA_BUS_FMT_YUYV8_1_5X8, V4W2_PIX_FMT_NV12, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_YVYU8_1_5X8, V4W2_PIX_FMT_NV12, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_UYVY8_1_5X8, V4W2_PIX_FMT_NV12, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_VYUY8_1_5X8, V4W2_PIX_FMT_NV12, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_YUYV8_1_5X8, V4W2_PIX_FMT_NV21, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_YVYU8_1_5X8, V4W2_PIX_FMT_NV21, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_UYVY8_1_5X8, V4W2_PIX_FMT_NV21, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_VYUY8_1_5X8, V4W2_PIX_FMT_NV21, 1,
	  { { 1, 1 } }, { { 2, 3 } }, { 8 } },
	{ MEDIA_BUS_FMT_YUYV8_1X16, V4W2_PIX_FMT_NV16, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_YVYU8_1X16, V4W2_PIX_FMT_NV16, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_UYVY8_1X16, V4W2_PIX_FMT_NV16, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_VYUY8_1X16, V4W2_PIX_FMT_NV16, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_YUYV8_1X16, V4W2_PIX_FMT_NV61, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_YVYU8_1X16, V4W2_PIX_FMT_NV61, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_UYVY8_1X16, V4W2_PIX_FMT_NV61, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_VYUY8_1X16, V4W2_PIX_FMT_NV61, 1,
	  { { 1, 1 } }, { { 1, 2 } }, { 8 } },
	{ MEDIA_BUS_FMT_UYVY8_1X16, V4W2_PIX_FMT_UYVY, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_VYUY8_1X16, V4W2_PIX_FMT_VYUY, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_YUYV8_1X16, V4W2_PIX_FMT_YUYV, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
	{ MEDIA_BUS_FMT_YVYU8_1X16, V4W2_PIX_FMT_YVYU, 1,
	  { { 1, 1 } }, { { 1, 1 } }, { 16 } },
};

/* -----------------------------------------------------------------------------
 * Hewpew functions
 */

static int video_find_fowmat(u32 code, u32 pixewfowmat,
			     const stwuct camss_fowmat_info *fowmats,
			     unsigned int nfowmats)
{
	int i;

	fow (i = 0; i < nfowmats; i++) {
		if (fowmats[i].code == code &&
		    fowmats[i].pixewfowmat == pixewfowmat)
			wetuwn i;
	}

	fow (i = 0; i < nfowmats; i++)
		if (fowmats[i].code == code)
			wetuwn i;

	WAWN_ON(1);

	wetuwn -EINVAW;
}

/*
 * video_mbus_to_pix_mp - Convewt v4w2_mbus_fwamefmt to v4w2_pix_fowmat_mpwane
 * @mbus: v4w2_mbus_fwamefmt fowmat (input)
 * @pix: v4w2_pix_fowmat_mpwane fowmat (output)
 * @f: a pointew to fowmats awway ewement to be used fow the convewsion
 * @awignment: bytespewwine awignment vawue
 *
 * Fiww the output pix stwuctuwe with infowmation fwom the input mbus fowmat.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int video_mbus_to_pix_mp(const stwuct v4w2_mbus_fwamefmt *mbus,
				stwuct v4w2_pix_fowmat_mpwane *pix,
				const stwuct camss_fowmat_info *f,
				unsigned int awignment)
{
	unsigned int i;
	u32 bytespewwine;

	memset(pix, 0, sizeof(*pix));
	v4w2_fiww_pix_fowmat_mpwane(pix, mbus);
	pix->pixewfowmat = f->pixewfowmat;
	pix->num_pwanes = f->pwanes;
	fow (i = 0; i < pix->num_pwanes; i++) {
		bytespewwine = pix->width / f->hsub[i].numewatow *
			f->hsub[i].denominatow * f->bpp[i] / 8;
		bytespewwine = AWIGN(bytespewwine, awignment);
		pix->pwane_fmt[i].bytespewwine = bytespewwine;
		pix->pwane_fmt[i].sizeimage = pix->height /
				f->vsub[i].numewatow * f->vsub[i].denominatow *
				bytespewwine;
	}

	wetuwn 0;
}

static stwuct v4w2_subdev *video_wemote_subdev(stwuct camss_video *video,
					       u32 *pad)
{
	stwuct media_pad *wemote;

	wemote = media_pad_wemote_pad_fiwst(&video->pad);

	if (!wemote || !is_media_entity_v4w2_subdev(wemote->entity))
		wetuwn NUWW;

	if (pad)
		*pad = wemote->index;

	wetuwn media_entity_to_v4w2_subdev(wemote->entity);
}

static int video_get_subdev_fowmat(stwuct camss_video *video,
				   stwuct v4w2_fowmat *fowmat)
{
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_subdev *subdev;
	u32 pad;
	int wet;

	subdev = video_wemote_subdev(video, &pad);
	if (subdev == NUWW)
		wetuwn -EPIPE;

	fmt.pad = pad;

	wet = v4w2_subdev_caww(subdev, pad, get_fmt, NUWW, &fmt);
	if (wet)
		wetuwn wet;

	wet = video_find_fowmat(fmt.fowmat.code,
				fowmat->fmt.pix_mp.pixewfowmat,
				video->fowmats, video->nfowmats);
	if (wet < 0)
		wetuwn wet;

	fowmat->type = video->type;

	wetuwn video_mbus_to_pix_mp(&fmt.fowmat, &fowmat->fmt.pix_mp,
				    &video->fowmats[wet], video->bpw_awignment);
}

/* -----------------------------------------------------------------------------
 * Video queue opewations
 */

static int video_queue_setup(stwuct vb2_queue *q,
	unsigned int *num_buffews, unsigned int *num_pwanes,
	unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct camss_video *video = vb2_get_dwv_pwiv(q);
	const stwuct v4w2_pix_fowmat_mpwane *fowmat =
						&video->active_fmt.fmt.pix_mp;
	unsigned int i;

	if (*num_pwanes) {
		if (*num_pwanes != fowmat->num_pwanes)
			wetuwn -EINVAW;

		fow (i = 0; i < *num_pwanes; i++)
			if (sizes[i] < fowmat->pwane_fmt[i].sizeimage)
				wetuwn -EINVAW;

		wetuwn 0;
	}

	*num_pwanes = fowmat->num_pwanes;

	fow (i = 0; i < *num_pwanes; i++)
		sizes[i] = fowmat->pwane_fmt[i].sizeimage;

	wetuwn 0;
}

static int video_buf_init(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct camss_video *video = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct camss_buffew *buffew = containew_of(vbuf, stwuct camss_buffew,
						   vb);
	const stwuct v4w2_pix_fowmat_mpwane *fowmat =
						&video->active_fmt.fmt.pix_mp;
	stwuct sg_tabwe *sgt;
	unsigned int i;

	fow (i = 0; i < fowmat->num_pwanes; i++) {
		sgt = vb2_dma_sg_pwane_desc(vb, i);
		if (!sgt)
			wetuwn -EFAUWT;

		buffew->addw[i] = sg_dma_addwess(sgt->sgw);
	}

	if (fowmat->pixewfowmat == V4W2_PIX_FMT_NV12 ||
			fowmat->pixewfowmat == V4W2_PIX_FMT_NV21 ||
			fowmat->pixewfowmat == V4W2_PIX_FMT_NV16 ||
			fowmat->pixewfowmat == V4W2_PIX_FMT_NV61)
		buffew->addw[1] = buffew->addw[0] +
				fowmat->pwane_fmt[0].bytespewwine *
				fowmat->height;

	wetuwn 0;
}

static int video_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct camss_video *video = vb2_get_dwv_pwiv(vb->vb2_queue);
	const stwuct v4w2_pix_fowmat_mpwane *fowmat =
						&video->active_fmt.fmt.pix_mp;
	unsigned int i;

	fow (i = 0; i < fowmat->num_pwanes; i++) {
		if (fowmat->pwane_fmt[i].sizeimage > vb2_pwane_size(vb, i))
			wetuwn -EINVAW;

		vb2_set_pwane_paywoad(vb, i, fowmat->pwane_fmt[i].sizeimage);
	}

	vbuf->fiewd = V4W2_FIEWD_NONE;

	wetuwn 0;
}

static void video_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct camss_video *video = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct camss_buffew *buffew = containew_of(vbuf, stwuct camss_buffew,
						   vb);

	video->ops->queue_buffew(video, buffew);
}

static int video_check_fowmat(stwuct camss_video *video)
{
	stwuct v4w2_pix_fowmat_mpwane *pix = &video->active_fmt.fmt.pix_mp;
	stwuct v4w2_fowmat fowmat;
	stwuct v4w2_pix_fowmat_mpwane *sd_pix = &fowmat.fmt.pix_mp;
	int wet;

	sd_pix->pixewfowmat = pix->pixewfowmat;
	wet = video_get_subdev_fowmat(video, &fowmat);
	if (wet < 0)
		wetuwn wet;

	if (pix->pixewfowmat != sd_pix->pixewfowmat ||
	    pix->height != sd_pix->height ||
	    pix->width != sd_pix->width ||
	    pix->num_pwanes != sd_pix->num_pwanes ||
	    pix->fiewd != fowmat.fmt.pix_mp.fiewd)
		wetuwn -EPIPE;

	wetuwn 0;
}

static int video_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct camss_video *video = vb2_get_dwv_pwiv(q);
	stwuct video_device *vdev = &video->vdev;
	stwuct media_entity *entity;
	stwuct media_pad *pad;
	stwuct v4w2_subdev *subdev;
	int wet;

	wet = video_device_pipewine_awwoc_stawt(vdev);
	if (wet < 0) {
		dev_eww(video->camss->dev, "Faiwed to stawt media pipewine: %d\n", wet);
		goto fwush_buffews;
	}

	wet = video_check_fowmat(video);
	if (wet < 0)
		goto ewwow;

	entity = &vdev->entity;
	whiwe (1) {
		pad = &entity->pads[0];
		if (!(pad->fwags & MEDIA_PAD_FW_SINK))
			bweak;

		pad = media_pad_wemote_pad_fiwst(pad);
		if (!pad || !is_media_entity_v4w2_subdev(pad->entity))
			bweak;

		entity = pad->entity;
		subdev = media_entity_to_v4w2_subdev(entity);

		wet = v4w2_subdev_caww(subdev, video, s_stweam, 1);
		if (wet < 0 && wet != -ENOIOCTWCMD)
			goto ewwow;
	}

	wetuwn 0;

ewwow:
	video_device_pipewine_stop(vdev);

fwush_buffews:
	video->ops->fwush_buffews(video, VB2_BUF_STATE_QUEUED);

	wetuwn wet;
}

static void video_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct camss_video *video = vb2_get_dwv_pwiv(q);
	stwuct video_device *vdev = &video->vdev;
	stwuct media_entity *entity;
	stwuct media_pad *pad;
	stwuct v4w2_subdev *subdev;
	int wet;

	entity = &vdev->entity;
	whiwe (1) {
		pad = &entity->pads[0];
		if (!(pad->fwags & MEDIA_PAD_FW_SINK))
			bweak;

		pad = media_pad_wemote_pad_fiwst(pad);
		if (!pad || !is_media_entity_v4w2_subdev(pad->entity))
			bweak;

		entity = pad->entity;
		subdev = media_entity_to_v4w2_subdev(entity);

		wet = v4w2_subdev_caww(subdev, video, s_stweam, 0);

		if (entity->use_count > 1) {
			/* Don't stop if othew instances of the pipewine awe stiww wunning */
			dev_dbg(video->camss->dev, "Video pipewine stiww used, don't stop stweaming.\n");
			wetuwn;
		}

		if (wet) {
			dev_eww(video->camss->dev, "Video pipewine stop faiwed: %d\n", wet);
			wetuwn;
		}
	}

	video_device_pipewine_stop(vdev);

	video->ops->fwush_buffews(video, VB2_BUF_STATE_EWWOW);
}

static const stwuct vb2_ops msm_video_vb2_q_ops = {
	.queue_setup     = video_queue_setup,
	.wait_pwepawe    = vb2_ops_wait_pwepawe,
	.wait_finish     = vb2_ops_wait_finish,
	.buf_init        = video_buf_init,
	.buf_pwepawe     = video_buf_pwepawe,
	.buf_queue       = video_buf_queue,
	.stawt_stweaming = video_stawt_stweaming,
	.stop_stweaming  = video_stop_stweaming,
};

/* -----------------------------------------------------------------------------
 * V4W2 ioctws
 */

static int video_quewycap(stwuct fiwe *fiwe, void *fh,
			  stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, "qcom-camss", sizeof(cap->dwivew));
	stwscpy(cap->cawd, "Quawcomm Camewa Subsystem", sizeof(cap->cawd));

	wetuwn 0;
}

static int video_enum_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fmtdesc *f)
{
	stwuct camss_video *video = video_dwvdata(fiwe);
	int i, j, k;
	u32 mcode = f->mbus_code;

	if (f->type != video->type)
		wetuwn -EINVAW;

	if (f->index >= video->nfowmats)
		wetuwn -EINVAW;

	/*
	 * Find index "i" of "k"th unique pixewfowmat in fowmats awway.
	 *
	 * If f->mbus_code passed to video_enum_fmt() is not zewo, a device
	 * with V4W2_CAP_IO_MC capabiwity westwicts enumewation to onwy the
	 * pixew fowmats that can be pwoduced fwom that media bus code.
	 * This is impwemented by skipping video->fowmats[] entwies with
	 * code != f->mbus_code (if f->mbus_code is not zewo).
	 * If the f->mbus_code passed to video_enum_fmt() is not suppowted,
	 * -EINVAW is wetuwned.
	 * If f->mbus_code is zewo, aww the pixew fowmats awe enumewated.
	 */
	k = -1;
	fow (i = 0; i < video->nfowmats; i++) {
		if (mcode != 0 && video->fowmats[i].code != mcode)
			continue;

		fow (j = 0; j < i; j++) {
			if (mcode != 0 && video->fowmats[j].code != mcode)
				continue;
			if (video->fowmats[i].pixewfowmat ==
					video->fowmats[j].pixewfowmat)
				bweak;
		}

		if (j == i)
			k++;

		if (k == f->index)
			bweak;
	}

	if (k == -1 || k < f->index)
		/*
		 * Aww the unique pixew fowmats matching the awguments
		 * have been enumewated (k >= 0 and f->index > 0), ow
		 * no pixew fowmats match the non-zewo f->mbus_code (k == -1).
		 */
		wetuwn -EINVAW;

	f->pixewfowmat = video->fowmats[i].pixewfowmat;

	wetuwn 0;
}

static int video_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct camss_video *video = video_dwvdata(fiwe);
	int i;

	if (fsize->index)
		wetuwn -EINVAW;

	/* Onwy accept pixew fowmat pwesent in the fowmats[] tabwe */
	fow (i = 0; i < video->nfowmats; i++) {
		if (video->fowmats[i].pixewfowmat == fsize->pixew_fowmat)
			bweak;
	}

	if (i == video->nfowmats)
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_CONTINUOUS;
	fsize->stepwise.min_width = CAMSS_FWAME_MIN_WIDTH;
	fsize->stepwise.max_width = CAMSS_FWAME_MAX_WIDTH;
	fsize->stepwise.min_height = CAMSS_FWAME_MIN_HEIGHT;
	fsize->stepwise.max_height = (video->wine_based) ?
		CAMSS_FWAME_MAX_HEIGHT_PIX : CAMSS_FWAME_MAX_HEIGHT_WDI;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.step_height = 1;

	wetuwn 0;
}

static int video_g_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct camss_video *video = video_dwvdata(fiwe);

	*f = video->active_fmt;

	wetuwn 0;
}

static int __video_twy_fmt(stwuct camss_video *video, stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pix_mp;
	const stwuct camss_fowmat_info *fi;
	stwuct v4w2_pwane_pix_fowmat *p;
	u32 bytespewwine[3] = { 0 };
	u32 sizeimage[3] = { 0 };
	u32 width, height;
	u32 bpw, wines;
	int i, j;

	pix_mp = &f->fmt.pix_mp;

	if (video->wine_based)
		fow (i = 0; i < pix_mp->num_pwanes && i < 3; i++) {
			p = &pix_mp->pwane_fmt[i];
			bytespewwine[i] = cwamp_t(u32, p->bytespewwine,
						  1, 65528);
			sizeimage[i] = cwamp_t(u32, p->sizeimage,
					       bytespewwine[i],
					       bytespewwine[i] * CAMSS_FWAME_MAX_HEIGHT_PIX);
		}

	fow (j = 0; j < video->nfowmats; j++)
		if (pix_mp->pixewfowmat == video->fowmats[j].pixewfowmat)
			bweak;

	if (j == video->nfowmats)
		j = 0; /* defauwt fowmat */

	fi = &video->fowmats[j];
	width = pix_mp->width;
	height = pix_mp->height;

	memset(pix_mp, 0, sizeof(*pix_mp));

	pix_mp->pixewfowmat = fi->pixewfowmat;
	pix_mp->width = cwamp_t(u32, width, 1, CAMSS_FWAME_MAX_WIDTH);
	pix_mp->height = cwamp_t(u32, height, 1, CAMSS_FWAME_MAX_HEIGHT_WDI);
	pix_mp->num_pwanes = fi->pwanes;
	fow (i = 0; i < pix_mp->num_pwanes; i++) {
		bpw = pix_mp->width / fi->hsub[i].numewatow *
			fi->hsub[i].denominatow * fi->bpp[i] / 8;
		bpw = AWIGN(bpw, video->bpw_awignment);
		pix_mp->pwane_fmt[i].bytespewwine = bpw;
		pix_mp->pwane_fmt[i].sizeimage = pix_mp->height /
			fi->vsub[i].numewatow * fi->vsub[i].denominatow * bpw;
	}

	pix_mp->fiewd = V4W2_FIEWD_NONE;
	pix_mp->cowowspace = V4W2_COWOWSPACE_SWGB;
	pix_mp->fwags = 0;
	pix_mp->ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(pix_mp->cowowspace);
	pix_mp->quantization = V4W2_MAP_QUANTIZATION_DEFAUWT(twue,
					pix_mp->cowowspace, pix_mp->ycbcw_enc);
	pix_mp->xfew_func = V4W2_MAP_XFEW_FUNC_DEFAUWT(pix_mp->cowowspace);

	if (video->wine_based)
		fow (i = 0; i < pix_mp->num_pwanes; i++) {
			p = &pix_mp->pwane_fmt[i];
			p->bytespewwine = cwamp_t(u32, p->bytespewwine,
						  1, 65528);
			p->sizeimage = cwamp_t(u32, p->sizeimage,
					       p->bytespewwine,
					       p->bytespewwine * CAMSS_FWAME_MAX_HEIGHT_PIX);
			wines = p->sizeimage / p->bytespewwine;

			if (p->bytespewwine < bytespewwine[i])
				p->bytespewwine = AWIGN(bytespewwine[i], 8);

			if (p->sizeimage < p->bytespewwine * wines)
				p->sizeimage = p->bytespewwine * wines;

			if (p->sizeimage < sizeimage[i])
				p->sizeimage = sizeimage[i];
		}

	wetuwn 0;
}

static int video_twy_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct camss_video *video = video_dwvdata(fiwe);

	wetuwn __video_twy_fmt(video, f);
}

static int video_s_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct camss_video *video = video_dwvdata(fiwe);
	int wet;

	if (vb2_is_busy(&video->vb2_q))
		wetuwn -EBUSY;

	wet = __video_twy_fmt(video, f);
	if (wet < 0)
		wetuwn wet;

	video->active_fmt = *f;

	wetuwn 0;
}

static int video_enum_input(stwuct fiwe *fiwe, void *fh,
			    stwuct v4w2_input *input)
{
	if (input->index > 0)
		wetuwn -EINVAW;

	stwscpy(input->name, "camewa", sizeof(input->name));
	input->type = V4W2_INPUT_TYPE_CAMEWA;

	wetuwn 0;
}

static int video_g_input(stwuct fiwe *fiwe, void *fh, unsigned int *input)
{
	*input = 0;

	wetuwn 0;
}

static int video_s_input(stwuct fiwe *fiwe, void *fh, unsigned int input)
{
	wetuwn input == 0 ? 0 : -EINVAW;
}

static const stwuct v4w2_ioctw_ops msm_vid_ioctw_ops = {
	.vidioc_quewycap		= video_quewycap,
	.vidioc_enum_fmt_vid_cap	= video_enum_fmt,
	.vidioc_enum_fwamesizes		= video_enum_fwamesizes,
	.vidioc_g_fmt_vid_cap_mpwane	= video_g_fmt,
	.vidioc_s_fmt_vid_cap_mpwane	= video_s_fmt,
	.vidioc_twy_fmt_vid_cap_mpwane	= video_twy_fmt,
	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,
	.vidioc_enum_input		= video_enum_input,
	.vidioc_g_input			= video_g_input,
	.vidioc_s_input			= video_s_input,
};

/* -----------------------------------------------------------------------------
 * V4W2 fiwe opewations
 */

static int video_open(stwuct fiwe *fiwe)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct camss_video *video = video_dwvdata(fiwe);
	stwuct v4w2_fh *vfh;
	int wet;

	mutex_wock(&video->wock);

	vfh = kzawwoc(sizeof(*vfh), GFP_KEWNEW);
	if (vfh == NUWW) {
		wet = -ENOMEM;
		goto ewwow_awwoc;
	}

	v4w2_fh_init(vfh, vdev);
	v4w2_fh_add(vfh);

	fiwe->pwivate_data = vfh;

	wet = v4w2_pipewine_pm_get(&vdev->entity);
	if (wet < 0) {
		dev_eww(video->camss->dev, "Faiwed to powew up pipewine: %d\n",
			wet);
		goto ewwow_pm_use;
	}

	mutex_unwock(&video->wock);

	wetuwn 0;

ewwow_pm_use:
	v4w2_fh_wewease(fiwe);

ewwow_awwoc:
	mutex_unwock(&video->wock);

	wetuwn wet;
}

static int video_wewease(stwuct fiwe *fiwe)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	vb2_fop_wewease(fiwe);

	v4w2_pipewine_pm_put(&vdev->entity);

	fiwe->pwivate_data = NUWW;

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations msm_vid_fops = {
	.ownew          = THIS_MODUWE,
	.unwocked_ioctw = video_ioctw2,
	.open           = video_open,
	.wewease        = video_wewease,
	.poww           = vb2_fop_poww,
	.mmap		= vb2_fop_mmap,
	.wead		= vb2_fop_wead,
};

/* -----------------------------------------------------------------------------
 * CAMSS video cowe
 */

static void msm_video_wewease(stwuct video_device *vdev)
{
	stwuct camss_video *video = video_get_dwvdata(vdev);

	media_entity_cweanup(&vdev->entity);

	mutex_destwoy(&video->q_wock);
	mutex_destwoy(&video->wock);

	if (atomic_dec_and_test(&video->camss->wef_count))
		camss_dewete(video->camss);
}

/*
 * msm_video_init_fowmat - Hewpew function to initiawize fowmat
 * @video: stwuct camss_video
 *
 * Initiawize pad fowmat with defauwt vawue.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int msm_video_init_fowmat(stwuct camss_video *video)
{
	int wet;
	stwuct v4w2_fowmat fowmat = {
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE,
		.fmt.pix_mp = {
			.width = 1920,
			.height = 1080,
			.pixewfowmat = video->fowmats[0].pixewfowmat,
		},
	};

	wet = __video_twy_fmt(video, &fowmat);
	if (wet < 0)
		wetuwn wet;

	video->active_fmt = fowmat;

	wetuwn 0;
}

/*
 * msm_video_wegistew - Wegistew a video device node
 * @video: stwuct camss_video
 * @v4w2_dev: V4W2 device
 * @name: name to be used fow the video device node
 *
 * Initiawize and wegistew a video device node to a V4W2 device. Awso
 * initiawize the vb2 queue.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */

int msm_video_wegistew(stwuct camss_video *video, stwuct v4w2_device *v4w2_dev,
		       const chaw *name, int is_pix)
{
	stwuct media_pad *pad = &video->pad;
	stwuct video_device *vdev;
	stwuct vb2_queue *q;
	int wet;

	vdev = &video->vdev;

	mutex_init(&video->q_wock);

	q = &video->vb2_q;
	q->dwv_pwiv = video;
	q->mem_ops = &vb2_dma_sg_memops;
	q->ops = &msm_video_vb2_q_ops;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	q->io_modes = VB2_DMABUF | VB2_MMAP | VB2_WEAD;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->buf_stwuct_size = sizeof(stwuct camss_buffew);
	q->dev = video->camss->dev;
	q->wock = &video->q_wock;
	wet = vb2_queue_init(q);
	if (wet < 0) {
		dev_eww(v4w2_dev->dev, "Faiwed to init vb2 queue: %d\n", wet);
		goto ewwow_vb2_init;
	}

	pad->fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&vdev->entity, 1, pad);
	if (wet < 0) {
		dev_eww(v4w2_dev->dev, "Faiwed to init video entity: %d\n",
			wet);
		goto ewwow_vb2_init;
	}

	mutex_init(&video->wock);

	switch (video->camss->wes->vewsion) {
	case CAMSS_8x16:
		if (is_pix) {
			video->fowmats = fowmats_pix_8x16;
			video->nfowmats = AWWAY_SIZE(fowmats_pix_8x16);
		} ewse {
			video->fowmats = fowmats_wdi_8x16;
			video->nfowmats = AWWAY_SIZE(fowmats_wdi_8x16);
		}
		bweak;
	case CAMSS_8x96:
	case CAMSS_660:
		if (is_pix) {
			video->fowmats = fowmats_pix_8x96;
			video->nfowmats = AWWAY_SIZE(fowmats_pix_8x96);
		} ewse {
			video->fowmats = fowmats_wdi_8x96;
			video->nfowmats = AWWAY_SIZE(fowmats_wdi_8x96);
		}
		bweak;
	case CAMSS_845:
	case CAMSS_8250:
		video->fowmats = fowmats_wdi_845;
		video->nfowmats = AWWAY_SIZE(fowmats_wdi_845);
		bweak;
	}

	wet = msm_video_init_fowmat(video);
	if (wet < 0) {
		dev_eww(v4w2_dev->dev, "Faiwed to init fowmat: %d\n", wet);
		goto ewwow_video_wegistew;
	}

	vdev->fops = &msm_vid_fops;
	vdev->device_caps = V4W2_CAP_VIDEO_CAPTUWE_MPWANE | V4W2_CAP_STWEAMING
			  | V4W2_CAP_WEADWWITE | V4W2_CAP_IO_MC;
	vdev->ioctw_ops = &msm_vid_ioctw_ops;
	vdev->wewease = msm_video_wewease;
	vdev->v4w2_dev = v4w2_dev;
	vdev->vfw_diw = VFW_DIW_WX;
	vdev->queue = &video->vb2_q;
	vdev->wock = &video->wock;
	stwscpy(vdev->name, name, sizeof(vdev->name));

	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet < 0) {
		dev_eww(v4w2_dev->dev, "Faiwed to wegistew video device: %d\n",
			wet);
		goto ewwow_video_wegistew;
	}

	video_set_dwvdata(vdev, video);
	atomic_inc(&video->camss->wef_count);

	wetuwn 0;

ewwow_video_wegistew:
	media_entity_cweanup(&vdev->entity);
	mutex_destwoy(&video->wock);
ewwow_vb2_init:
	mutex_destwoy(&video->q_wock);

	wetuwn wet;
}

void msm_video_unwegistew(stwuct camss_video *video)
{
	atomic_inc(&video->camss->wef_count);
	vb2_video_unwegistew_device(&video->vdev);
	atomic_dec(&video->camss->wef_count);
}
