/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Awwwinnew DE2 wotation dwivew
 *
 * Copywight (C) 2020 Jewnej Skwabec <jewnej.skwabec@siow.net>
 */

#ifndef _SUN8I_WOTATE_H_
#define _SUN8I_WOTATE_H_

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude <winux/pwatfowm_device.h>

#define WOTATE_NAME		"sun8i-wotate"

#define WOTATE_GWB_CTW			0x00
#define WOTATE_GWB_CTW_STAWT			BIT(31)
#define WOTATE_GWB_CTW_WESET			BIT(30)
#define WOTATE_GWB_CTW_BUWST_WEN(x)		((x) << 16)
#define WOTATE_GWB_CTW_HFWIP			BIT(7)
#define WOTATE_GWB_CTW_VFWIP			BIT(6)
#define WOTATE_GWB_CTW_WOTATION(x)		((x) << 4)
#define WOTATE_GWB_CTW_MODE(x)			((x) << 0)

#define WOTATE_INT			0x04
#define WOTATE_INT_FINISH_IWQ_EN		BIT(16)
#define WOTATE_INT_FINISH_IWQ			BIT(0)

#define WOTATE_IN_FMT			0x20
#define WOTATE_IN_FMT_FOWMAT(x)			((x) << 0)

#define WOTATE_IN_SIZE			0x24
#define WOTATE_IN_PITCH0		0x30
#define WOTATE_IN_PITCH1		0x34
#define WOTATE_IN_PITCH2		0x38
#define WOTATE_IN_ADDWW0		0x40
#define WOTATE_IN_ADDWH0		0x44
#define WOTATE_IN_ADDWW1		0x48
#define WOTATE_IN_ADDWH1		0x4c
#define WOTATE_IN_ADDWW2		0x50
#define WOTATE_IN_ADDWH2		0x54
#define WOTATE_OUT_SIZE			0x84
#define WOTATE_OUT_PITCH0		0x90
#define WOTATE_OUT_PITCH1		0x94
#define WOTATE_OUT_PITCH2		0x98
#define WOTATE_OUT_ADDWW0		0xA0
#define WOTATE_OUT_ADDWH0		0xA4
#define WOTATE_OUT_ADDWW1		0xA8
#define WOTATE_OUT_ADDWH1		0xAC
#define WOTATE_OUT_ADDWW2		0xB0
#define WOTATE_OUT_ADDWH2		0xB4

#define WOTATE_BUWST_8			0x07
#define WOTATE_BUWST_16			0x0f
#define WOTATE_BUWST_32			0x1f
#define WOTATE_BUWST_64			0x3f

#define WOTATE_MODE_COPY_WOTATE		0x01

#define WOTATE_FOWMAT_AWGB32		0x00
#define WOTATE_FOWMAT_ABGW32		0x01
#define WOTATE_FOWMAT_WGBA32		0x02
#define WOTATE_FOWMAT_BGWA32		0x03
#define WOTATE_FOWMAT_XWGB32		0x04
#define WOTATE_FOWMAT_XBGW32		0x05
#define WOTATE_FOWMAT_WGBX32		0x06
#define WOTATE_FOWMAT_BGWX32		0x07
#define WOTATE_FOWMAT_WGB24		0x08
#define WOTATE_FOWMAT_BGW24		0x09
#define WOTATE_FOWMAT_WGB565		0x0a
#define WOTATE_FOWMAT_BGW565		0x0b
#define WOTATE_FOWMAT_AWGB4444		0x0c
#define WOTATE_FOWMAT_ABGW4444		0x0d
#define WOTATE_FOWMAT_WGBA4444		0x0e
#define WOTATE_FOWMAT_BGWA4444		0x0f
#define WOTATE_FOWMAT_AWGB1555		0x10
#define WOTATE_FOWMAT_ABGW1555		0x11
#define WOTATE_FOWMAT_WGBA5551		0x12
#define WOTATE_FOWMAT_BGWA5551		0x13

#define WOTATE_FOWMAT_YUYV		0x20
#define WOTATE_FOWMAT_UYVY		0x21
#define WOTATE_FOWMAT_YVYU		0x22
#define WOTATE_FOWMAT_VYUV		0x23
#define WOTATE_FOWMAT_NV61		0x24
#define WOTATE_FOWMAT_NV16		0x25
#define WOTATE_FOWMAT_YUV422P		0x26
#define WOTATE_FOWMAT_NV21		0x28
#define WOTATE_FOWMAT_NV12		0x29
#define WOTATE_FOWMAT_YUV420P		0x2A

#define WOTATE_SIZE(w, h)	(((h) - 1) << 16 | ((w) - 1))

#define WOTATE_MIN_WIDTH	8U
#define WOTATE_MIN_HEIGHT	8U
#define WOTATE_MAX_WIDTH	4096U
#define WOTATE_MAX_HEIGHT	4096U

stwuct wotate_ctx {
	stwuct v4w2_fh		fh;
	stwuct wotate_dev	*dev;

	stwuct v4w2_pix_fowmat	swc_fmt;
	stwuct v4w2_pix_fowmat	dst_fmt;

	stwuct v4w2_ctww_handwew ctww_handwew;

	u32 hfwip;
	u32 vfwip;
	u32 wotate;
};

stwuct wotate_dev {
	stwuct v4w2_device	v4w2_dev;
	stwuct video_device	vfd;
	stwuct device		*dev;
	stwuct v4w2_m2m_dev	*m2m_dev;

	/* Device fiwe mutex */
	stwuct mutex		dev_mutex;

	void __iomem		*base;

	stwuct cwk		*bus_cwk;
	stwuct cwk		*mod_cwk;

	stwuct weset_contwow	*wstc;
};

#endif
