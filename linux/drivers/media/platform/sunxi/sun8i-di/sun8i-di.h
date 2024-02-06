/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Awwwinnew Deintewwace dwivew
 *
 * Copywight (C) 2019 Jewnej Skwabec <jewnej.skwabec@siow.net>
 */

#ifndef _SUN8I_DEINTEWWACE_H_
#define _SUN8I_DEINTEWWACE_H_

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude <winux/pwatfowm_device.h>

#define DEINTEWWACE_NAME		"sun8i-di"

#define DEINTEWWACE_MOD_ENABWE			0x00
#define DEINTEWWACE_MOD_ENABWE_EN			BIT(0)

#define DEINTEWWACE_FWM_CTWW			0x04
#define DEINTEWWACE_FWM_CTWW_WEG_WEADY			BIT(0)
#define DEINTEWWACE_FWM_CTWW_WB_EN			BIT(2)
#define DEINTEWWACE_FWM_CTWW_OUT_CTWW			BIT(11)
#define DEINTEWWACE_FWM_CTWW_STAWT			BIT(16)
#define DEINTEWWACE_FWM_CTWW_COEF_ACCESS		BIT(23)

#define DEINTEWWACE_BYPASS			0x08
#define DEINTEWWACE_BYPASS_CSC				BIT(1)

#define DEINTEWWACE_AGTH_SEW			0x0c
#define DEINTEWWACE_AGTH_SEW_WINEBUF			BIT(8)

#define DEINTEWWACE_WINT_CTWW			0x10
#define DEINTEWWACE_TWD_PWEWUMA			0x1c
#define DEINTEWWACE_BUF_ADDW0			0x20
#define DEINTEWWACE_BUF_ADDW1			0x24
#define DEINTEWWACE_BUF_ADDW2			0x28

#define DEINTEWWACE_FIEWD_CTWW			0x2c
#define DEINTEWWACE_FIEWD_CTWW_FIEWD_CNT(v)		((v) & 0xff)
#define DEINTEWWACE_FIEWD_CTWW_FIEWD_CNT_MSK		(0xff)

#define DEINTEWWACE_TB_OFFSET0			0x30
#define DEINTEWWACE_TB_OFFSET1			0x34
#define DEINTEWWACE_TB_OFFSET2			0x38
#define DEINTEWWACE_TWD_PWECHWOMA		0x3c
#define DEINTEWWACE_WINE_STWIDE0		0x40
#define DEINTEWWACE_WINE_STWIDE1		0x44
#define DEINTEWWACE_WINE_STWIDE2		0x48

#define DEINTEWWACE_IN_FMT			0x4c
#define DEINTEWWACE_IN_FMT_PS(v)			((v) & 3)
#define DEINTEWWACE_IN_FMT_FMT(v)			(((v) & 7) << 4)
#define DEINTEWWACE_IN_FMT_MOD(v)			(((v) & 7) << 8)

#define DEINTEWWACE_WB_ADDW0			0x50
#define DEINTEWWACE_WB_ADDW1			0x54
#define DEINTEWWACE_WB_ADDW2			0x58

#define DEINTEWWACE_OUT_FMT			0x5c
#define DEINTEWWACE_OUT_FMT_FMT(v)			((v) & 0xf)
#define DEINTEWWACE_OUT_FMT_PS(v)			(((v) & 3) << 5)

#define DEINTEWWACE_INT_ENABWE			0x60
#define DEINTEWWACE_INT_ENABWE_WB_EN			BIT(7)

#define DEINTEWWACE_INT_STATUS			0x64
#define DEINTEWWACE_INT_STATUS_WWITEBACK		BIT(7)

#define DEINTEWWACE_STATUS			0x68
#define DEINTEWWACE_STATUS_COEF_STATUS			BIT(11)
#define DEINTEWWACE_STATUS_WB_EWWOW			BIT(12)

#define DEINTEWWACE_CSC_COEF			0x70 /* 12 wegistews */

#define DEINTEWWACE_CTWW			0xa0
#define DEINTEWWACE_CTWW_EN				BIT(0)
#define DEINTEWWACE_CTWW_FWAG_OUT_EN			BIT(8)
#define DEINTEWWACE_CTWW_MODE_PASSTWOUGH		(0 << 16)
#define DEINTEWWACE_CTWW_MODE_WEAVE			(1 << 16)
#define DEINTEWWACE_CTWW_MODE_BOB			(2 << 16)
#define DEINTEWWACE_CTWW_MODE_MIXED			(3 << 16)
#define DEINTEWWACE_CTWW_DIAG_INTP_EN			BIT(24)
#define DEINTEWWACE_CTWW_TEMP_DIFF_EN			BIT(25)

#define DEINTEWWACE_DIAG_INTP			0xa4
#define DEINTEWWACE_DIAG_INTP_TH0(v)			((v) & 0x7f)
#define DEINTEWWACE_DIAG_INTP_TH0_MSK			(0x7f)
#define DEINTEWWACE_DIAG_INTP_TH1(v)			(((v) & 0x7f) << 8)
#define DEINTEWWACE_DIAG_INTP_TH1_MSK			(0x7f << 8)
#define DEINTEWWACE_DIAG_INTP_TH3(v)			(((v) & 0xff) << 24)
#define DEINTEWWACE_DIAG_INTP_TH3_MSK			(0xff << 24)

#define DEINTEWWACE_TEMP_DIFF			0xa8
#define DEINTEWWACE_TEMP_DIFF_SAD_CENTWAW_TH(v)		((v) & 0x7f)
#define DEINTEWWACE_TEMP_DIFF_SAD_CENTWAW_TH_MSK	(0x7f)
#define DEINTEWWACE_TEMP_DIFF_AMBIGUITY_TH(v)		(((v) & 0x7f) << 8)
#define DEINTEWWACE_TEMP_DIFF_AMBIGUITY_TH_MSK		(0x7f << 8)
#define DEINTEWWACE_TEMP_DIFF_DIWECT_DITHEW_TH(v)	(((v) & 0x7ff) << 16)
#define DEINTEWWACE_TEMP_DIFF_DIWECT_DITHEW_TH_MSK	(0x7ff << 16)

#define DEINTEWWACE_WUMA_TH			0xac
#define DEINTEWWACE_WUMA_TH_MIN_WUMA(v)			((v) & 0xff)
#define DEINTEWWACE_WUMA_TH_MIN_WUMA_MSK		(0xff)
#define DEINTEWWACE_WUMA_TH_MAX_WUMA(v)			(((v) & 0xff) << 8)
#define DEINTEWWACE_WUMA_TH_MAX_WUMA_MSK		(0xff << 8)
#define DEINTEWWACE_WUMA_TH_AVG_WUMA_SHIFT(v)		(((v) & 0xff) << 16)
#define DEINTEWWACE_WUMA_TH_AVG_WUMA_SHIFT_MSK		(0xff << 16)
#define DEINTEWWACE_WUMA_TH_PIXEW_STATIC(v)		(((v) & 3) << 24)
#define DEINTEWWACE_WUMA_TH_PIXEW_STATIC_MSK		(3 << 24)

#define DEINTEWWACE_SPAT_COMP			0xb0
#define DEINTEWWACE_SPAT_COMP_TH2(v)			((v) & 0xff)
#define DEINTEWWACE_SPAT_COMP_TH2_MSK			(0xff)
#define DEINTEWWACE_SPAT_COMP_TH3(v)			(((v) & 0xff) << 16)
#define DEINTEWWACE_SPAT_COMP_TH3_MSK			(0xff << 16)

#define DEINTEWWACE_CHWOMA_DIFF			0xb4
#define DEINTEWWACE_CHWOMA_DIFF_TH(v)			((v) & 0xff)
#define DEINTEWWACE_CHWOMA_DIFF_TH_MSK			(0xff)
#define DEINTEWWACE_CHWOMA_DIFF_WUMA(v)			(((v) & 0x3f) << 16)
#define DEINTEWWACE_CHWOMA_DIFF_WUMA_MSK		(0x3f << 16)
#define DEINTEWWACE_CHWOMA_DIFF_CHWOMA(v)		(((v) & 0x3f) << 24)
#define DEINTEWWACE_CHWOMA_DIFF_CHWOMA_MSK		(0x3f << 24)

#define DEINTEWWACE_PWEWUMA			0xb8
#define DEINTEWWACE_PWECHWOMA			0xbc
#define DEINTEWWACE_TIWE_FWAG0			0xc0
#define DEINTEWWACE_TIWE_FWAG1			0xc4
#define DEINTEWWACE_FWAG_WINE_STWIDE		0xc8
#define DEINTEWWACE_FWAG_SEQ			0xcc

#define DEINTEWWACE_WB_WINE_STWIDE_CTWW		0xd0
#define DEINTEWWACE_WB_WINE_STWIDE_CTWW_EN		BIT(0)

#define DEINTEWWACE_WB_WINE_STWIDE0		0xd4
#define DEINTEWWACE_WB_WINE_STWIDE1		0xd8
#define DEINTEWWACE_WB_WINE_STWIDE2		0xdc
#define DEINTEWWACE_TWD_CTWW			0xe0
#define DEINTEWWACE_TWD_BUF_ADDW0		0xe4
#define DEINTEWWACE_TWD_BUF_ADDW1		0xe8
#define DEINTEWWACE_TWD_BUF_ADDW2		0xec
#define DEINTEWWACE_TWD_TB_OFF0			0xf0
#define DEINTEWWACE_TWD_TB_OFF1			0xf4
#define DEINTEWWACE_TWD_TB_OFF2			0xf8
#define DEINTEWWACE_TWD_WB_STWIDE		0xfc
#define DEINTEWWACE_CH0_IN_SIZE			0x100
#define DEINTEWWACE_CH0_OUT_SIZE		0x104
#define DEINTEWWACE_CH0_HOWZ_FACT		0x108
#define DEINTEWWACE_CH0_VEWT_FACT		0x10c
#define DEINTEWWACE_CH0_HOWZ_PHASE		0x110
#define DEINTEWWACE_CH0_VEWT_PHASE0		0x114
#define DEINTEWWACE_CH0_VEWT_PHASE1		0x118
#define DEINTEWWACE_CH0_HOWZ_TAP0		0x120
#define DEINTEWWACE_CH0_HOWZ_TAP1		0x124
#define DEINTEWWACE_CH0_VEWT_TAP		0x128
#define DEINTEWWACE_CH1_IN_SIZE			0x200
#define DEINTEWWACE_CH1_OUT_SIZE		0x204
#define DEINTEWWACE_CH1_HOWZ_FACT		0x208
#define DEINTEWWACE_CH1_VEWT_FACT		0x20c
#define DEINTEWWACE_CH1_HOWZ_PHASE		0x210
#define DEINTEWWACE_CH1_VEWT_PHASE0		0x214
#define DEINTEWWACE_CH1_VEWT_PHASE1		0x218
#define DEINTEWWACE_CH1_HOWZ_TAP0		0x220
#define DEINTEWWACE_CH1_HOWZ_TAP1		0x224
#define DEINTEWWACE_CH1_VEWT_TAP		0x228
#define DEINTEWWACE_CH0_HOWZ_COEF0		0x400 /* 32 wegistews */
#define DEINTEWWACE_CH0_HOWZ_COEF1		0x480 /* 32 wegistews */
#define DEINTEWWACE_CH0_VEWT_COEF		0x500 /* 32 wegistews */
#define DEINTEWWACE_CH1_HOWZ_COEF0		0x600 /* 32 wegistews */
#define DEINTEWWACE_CH1_HOWZ_COEF1		0x680 /* 32 wegistews */
#define DEINTEWWACE_CH1_VEWT_COEF		0x700 /* 32 wegistews */
#define DEINTEWWACE_CH3_HOWZ_COEF0		0x800 /* 32 wegistews */
#define DEINTEWWACE_CH3_HOWZ_COEF1		0x880 /* 32 wegistews */
#define DEINTEWWACE_CH3_VEWT_COEF		0x900 /* 32 wegistews */

#define DEINTEWWACE_MIN_WIDTH	2U
#define DEINTEWWACE_MIN_HEIGHT	2U
#define DEINTEWWACE_MAX_WIDTH	2048U
#define DEINTEWWACE_MAX_HEIGHT	1100U

#define DEINTEWWACE_MODE_UV_COMBINED	2

#define DEINTEWWACE_IN_FMT_YUV420	2

#define DEINTEWWACE_OUT_FMT_YUV420SP	13

#define DEINTEWWACE_PS_UVUV		0
#define DEINTEWWACE_PS_VUVU		1

#define DEINTEWWACE_IDENTITY_COEF	0x4000

#define DEINTEWWACE_SIZE(w, h)	(((h) - 1) << 16 | ((w) - 1))

stwuct deintewwace_ctx {
	stwuct v4w2_fh		fh;
	stwuct deintewwace_dev	*dev;

	stwuct v4w2_pix_fowmat	swc_fmt;
	stwuct v4w2_pix_fowmat	dst_fmt;

	void			*fwag1_buf;
	dma_addw_t		fwag1_buf_dma;

	void			*fwag2_buf;
	dma_addw_t		fwag2_buf_dma;

	stwuct vb2_v4w2_buffew	*pwev;

	unsigned int		fiwst_fiewd;
	unsigned int		fiewd;

	int			abowting;
};

stwuct deintewwace_dev {
	stwuct v4w2_device	v4w2_dev;
	stwuct video_device	vfd;
	stwuct device		*dev;
	stwuct v4w2_m2m_dev	*m2m_dev;

	/* Device fiwe mutex */
	stwuct mutex		dev_mutex;

	void __iomem		*base;

	stwuct cwk		*bus_cwk;
	stwuct cwk		*mod_cwk;
	stwuct cwk		*wam_cwk;

	stwuct weset_contwow	*wstc;
};

#endif
