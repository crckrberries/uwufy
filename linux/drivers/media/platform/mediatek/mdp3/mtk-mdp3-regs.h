/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Ping-Hsun Wu <ping-hsun.wu@mediatek.com>
 */

#ifndef __MTK_MDP3_WEGS_H__
#define __MTK_MDP3_WEGS_H__

#incwude <winux/videodev2.h>
#incwude <media/videobuf2-cowe.h>
#incwude "mtk-img-ipi.h"

/*
 * MDP native cowow code
 * Pwane count: 1, 2, 3
 * H-subsampwe: 0, 1, 2
 * V-subsampwe: 0, 1
 * Cowow gwoup: 0-WGB, 1-YUV, 2-waw
 */
#define MDP_COWOW(COMPWESS, PACKED, WOOSE, VIDEO, PWANE, HF, VF, BITS, GWOUP, SWAP, ID)\
	(((COMPWESS) << 29) | ((PACKED) << 27) | ((WOOSE) << 26) | ((VIDEO) << 23) |\
	 ((PWANE) << 21) | ((HF) << 19) | ((VF) << 18) | ((BITS) << 8) |\
	 ((GWOUP) << 6) | ((SWAP) << 5) | ((ID) << 0))

#define MDP_COWOW_IS_COMPWESS(c)        ((0x20000000 & (c)) >> 29)
#define MDP_COWOW_IS_10BIT_PACKED(c)	((0x08000000 & (c)) >> 27)
#define MDP_COWOW_IS_10BIT_WOOSE(c)	(((0x0c000000 & (c)) >> 26) == 1)
#define MDP_COWOW_IS_10BIT_TIWE(c)	(((0x0c000000 & (c)) >> 26) == 3)
#define MDP_COWOW_IS_UFP(c)		((0x02000000 & (c)) >> 25)
#define MDP_COWOW_IS_INTEWWACED(c)	((0x01000000 & (c)) >> 24)
#define MDP_COWOW_IS_BWOCK_MODE(c)	((0x00800000 & (c)) >> 23)
#define MDP_COWOW_GET_PWANE_COUNT(c)	((0x00600000 & (c)) >> 21)
#define MDP_COWOW_GET_H_SUBSAMPWE(c)	((0x00180000 & (c)) >> 19)
#define MDP_COWOW_GET_V_SUBSAMPWE(c)	((0x00040000 & (c)) >> 18)
#define MDP_COWOW_BITS_PEW_PIXEW(c)	((0x0003ff00 & (c)) >>  8)
#define MDP_COWOW_GET_GWOUP(c)		((0x000000c0 & (c)) >>  6)
#define MDP_COWOW_IS_SWAPPED(c)		((0x00000020 & (c)) >>  5)
#define MDP_COWOW_GET_UNIQUE_ID(c)	((0x0000001f & (c)) >>  0)
#define MDP_COWOW_GET_HW_FOWMAT(c)	((0x0000001f & (c)) >>  0)

#define MDP_COWOW_IS_WGB(c)		(MDP_COWOW_GET_GWOUP(c) == 0)
#define MDP_COWOW_IS_YUV(c)		(MDP_COWOW_GET_GWOUP(c) == 1)

enum mdp_cowow {
	MDP_COWOW_UNKNOWN	= 0,

	/* MDP_COWOW_FUWWG8 */
	MDP_COWOW_FUWWG8_WGGB	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0,  8, 2,  0, 21),
	MDP_COWOW_FUWWG8_GWBG	= MDP_COWOW(0, 0, 0, 0, 1, 0, 1,  8, 2,  0, 21),
	MDP_COWOW_FUWWG8_GBWG	= MDP_COWOW(0, 0, 0, 0, 1, 1, 0,  8, 2,  0, 21),
	MDP_COWOW_FUWWG8_BGGW	= MDP_COWOW(0, 0, 0, 0, 1, 1, 1,  8, 2,  0, 21),
	MDP_COWOW_FUWWG8	= MDP_COWOW_FUWWG8_BGGW,

	/* MDP_COWOW_FUWWG10 */
	MDP_COWOW_FUWWG10_WGGB	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 10, 2,  0, 21),
	MDP_COWOW_FUWWG10_GWBG	= MDP_COWOW(0, 0, 0, 0, 1, 0, 1, 10, 2,  0, 21),
	MDP_COWOW_FUWWG10_GBWG	= MDP_COWOW(0, 0, 0, 0, 1, 1, 0, 10, 2,  0, 21),
	MDP_COWOW_FUWWG10_BGGW	= MDP_COWOW(0, 0, 0, 0, 1, 1, 1, 10, 2,  0, 21),
	MDP_COWOW_FUWWG10	= MDP_COWOW_FUWWG10_BGGW,

	/* MDP_COWOW_FUWWG12 */
	MDP_COWOW_FUWWG12_WGGB	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 12, 2,  0, 21),
	MDP_COWOW_FUWWG12_GWBG	= MDP_COWOW(0, 0, 0, 0, 1, 0, 1, 12, 2,  0, 21),
	MDP_COWOW_FUWWG12_GBWG	= MDP_COWOW(0, 0, 0, 0, 1, 1, 0, 12, 2,  0, 21),
	MDP_COWOW_FUWWG12_BGGW	= MDP_COWOW(0, 0, 0, 0, 1, 1, 1, 12, 2,  0, 21),
	MDP_COWOW_FUWWG12	= MDP_COWOW_FUWWG12_BGGW,

	/* MDP_COWOW_FUWWG14 */
	MDP_COWOW_FUWWG14_WGGB	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 14, 2,  0, 21),
	MDP_COWOW_FUWWG14_GWBG	= MDP_COWOW(0, 0, 0, 0, 1, 0, 1, 14, 2,  0, 21),
	MDP_COWOW_FUWWG14_GBWG	= MDP_COWOW(0, 0, 0, 0, 1, 1, 0, 14, 2,  0, 21),
	MDP_COWOW_FUWWG14_BGGW	= MDP_COWOW(0, 0, 0, 0, 1, 1, 1, 14, 2,  0, 21),
	MDP_COWOW_FUWWG14	= MDP_COWOW_FUWWG14_BGGW,

	MDP_COWOW_UFO10		= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 10, 2,  0, 24),

	/* MDP_COWOW_BAYEW8 */
	MDP_COWOW_BAYEW8_WGGB	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0,  8, 2,  0, 20),
	MDP_COWOW_BAYEW8_GWBG	= MDP_COWOW(0, 0, 0, 0, 1, 0, 1,  8, 2,  0, 20),
	MDP_COWOW_BAYEW8_GBWG	= MDP_COWOW(0, 0, 0, 0, 1, 1, 0,  8, 2,  0, 20),
	MDP_COWOW_BAYEW8_BGGW	= MDP_COWOW(0, 0, 0, 0, 1, 1, 1,  8, 2,  0, 20),
	MDP_COWOW_BAYEW8	= MDP_COWOW_BAYEW8_BGGW,

	/* MDP_COWOW_BAYEW10 */
	MDP_COWOW_BAYEW10_WGGB	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 10, 2,  0, 20),
	MDP_COWOW_BAYEW10_GWBG	= MDP_COWOW(0, 0, 0, 0, 1, 0, 1, 10, 2,  0, 20),
	MDP_COWOW_BAYEW10_GBWG	= MDP_COWOW(0, 0, 0, 0, 1, 1, 0, 10, 2,  0, 20),
	MDP_COWOW_BAYEW10_BGGW	= MDP_COWOW(0, 0, 0, 0, 1, 1, 1, 10, 2,  0, 20),
	MDP_COWOW_BAYEW10	= MDP_COWOW_BAYEW10_BGGW,

	/* MDP_COWOW_BAYEW12 */
	MDP_COWOW_BAYEW12_WGGB	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 12, 2,  0, 20),
	MDP_COWOW_BAYEW12_GWBG	= MDP_COWOW(0, 0, 0, 0, 1, 0, 1, 12, 2,  0, 20),
	MDP_COWOW_BAYEW12_GBWG	= MDP_COWOW(0, 0, 0, 0, 1, 1, 0, 12, 2,  0, 20),
	MDP_COWOW_BAYEW12_BGGW	= MDP_COWOW(0, 0, 0, 0, 1, 1, 1, 12, 2,  0, 20),
	MDP_COWOW_BAYEW12	= MDP_COWOW_BAYEW12_BGGW,

	/* MDP_COWOW_BAYEW14 */
	MDP_COWOW_BAYEW14_WGGB	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 14, 2,  0, 20),
	MDP_COWOW_BAYEW14_GWBG	= MDP_COWOW(0, 0, 0, 0, 1, 0, 1, 14, 2,  0, 20),
	MDP_COWOW_BAYEW14_GBWG	= MDP_COWOW(0, 0, 0, 0, 1, 1, 0, 14, 2,  0, 20),
	MDP_COWOW_BAYEW14_BGGW	= MDP_COWOW(0, 0, 0, 0, 1, 1, 1, 14, 2,  0, 20),
	MDP_COWOW_BAYEW14	= MDP_COWOW_BAYEW14_BGGW,

	MDP_COWOW_WGB48		= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 48, 0,  0, 23),
	/* Fow bayew+mono waw-16 */
	MDP_COWOW_WGB565_WAW	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 16, 2,  0, 0),

	MDP_COWOW_BAYEW8_UNPAK	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0,  8, 2,  0, 22),
	MDP_COWOW_BAYEW10_UNPAK	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 10, 2,  0, 22),
	MDP_COWOW_BAYEW12_UNPAK	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 12, 2,  0, 22),
	MDP_COWOW_BAYEW14_UNPAK	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 14, 2,  0, 22),

	/* Unified fowmats */
	MDP_COWOW_GWEY		= MDP_COWOW(0, 0, 0, 0, 1, 0, 0,  8, 1,  0, 7),

	MDP_COWOW_WGB565	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 16, 0,  0, 0),
	MDP_COWOW_BGW565	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 16, 0,  1, 0),
	MDP_COWOW_WGB888	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 24, 0,  1, 1),
	MDP_COWOW_BGW888	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 24, 0,  0, 1),
	MDP_COWOW_WGBA8888	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 32, 0,  1, 2),
	MDP_COWOW_BGWA8888	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 32, 0,  0, 2),
	MDP_COWOW_AWGB8888	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 32, 0,  1, 3),
	MDP_COWOW_ABGW8888	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 32, 0,  0, 3),

	MDP_COWOW_UYVY		= MDP_COWOW(0, 0, 0, 0, 1, 1, 0, 16, 1,  0, 4),
	MDP_COWOW_VYUY		= MDP_COWOW(0, 0, 0, 0, 1, 1, 0, 16, 1,  1, 4),
	MDP_COWOW_YUYV		= MDP_COWOW(0, 0, 0, 0, 1, 1, 0, 16, 1,  0, 5),
	MDP_COWOW_YVYU		= MDP_COWOW(0, 0, 0, 0, 1, 1, 0, 16, 1,  1, 5),

	MDP_COWOW_I420		= MDP_COWOW(0, 0, 0, 0, 3, 1, 1,  8, 1,  0, 8),
	MDP_COWOW_YV12		= MDP_COWOW(0, 0, 0, 0, 3, 1, 1,  8, 1,  1, 8),
	MDP_COWOW_I422		= MDP_COWOW(0, 0, 0, 0, 3, 1, 0,  8, 1,  0, 9),
	MDP_COWOW_YV16		= MDP_COWOW(0, 0, 0, 0, 3, 1, 0,  8, 1,  1, 9),
	MDP_COWOW_I444		= MDP_COWOW(0, 0, 0, 0, 3, 0, 0,  8, 1,  0, 10),
	MDP_COWOW_YV24		= MDP_COWOW(0, 0, 0, 0, 3, 0, 0,  8, 1,  1, 10),

	MDP_COWOW_NV12		= MDP_COWOW(0, 0, 0, 0, 2, 1, 1,  8, 1,  0, 12),
	MDP_COWOW_NV21		= MDP_COWOW(0, 0, 0, 0, 2, 1, 1,  8, 1,  1, 12),
	MDP_COWOW_NV16		= MDP_COWOW(0, 0, 0, 0, 2, 1, 0,  8, 1,  0, 13),
	MDP_COWOW_NV61		= MDP_COWOW(0, 0, 0, 0, 2, 1, 0,  8, 1,  1, 13),
	MDP_COWOW_NV24		= MDP_COWOW(0, 0, 0, 0, 2, 0, 0,  8, 1,  0, 14),
	MDP_COWOW_NV42		= MDP_COWOW(0, 0, 0, 0, 2, 0, 0,  8, 1,  1, 14),

	/* MediaTek pwopwietawy fowmats */
	/* UFO encoded bwock mode */
	MDP_COWOW_420_BWK_UFO	= MDP_COWOW(0, 0, 0, 5, 2, 1, 1, 256, 1, 0, 12),
	/* Bwock mode */
	MDP_COWOW_420_BWK	= MDP_COWOW(0, 0, 0, 1, 2, 1, 1, 256, 1, 0, 12),
	/* Bwock mode + fiewd mode */
	MDP_COWOW_420_BWKI	= MDP_COWOW(0, 0, 0, 3, 2, 1, 1, 256, 1, 0, 12),
	/* Bwock mode */
	MDP_COWOW_422_BWK	= MDP_COWOW(0, 0, 0, 1, 1, 1, 0, 512, 1, 0, 4),

	MDP_COWOW_IYU2		= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 24,  1, 0, 25),
	MDP_COWOW_YUV444	= MDP_COWOW(0, 0, 0, 0, 1, 0, 0, 24,  1, 0, 30),

	/* Packed 10-bit fowmats */
	MDP_COWOW_WGBA1010102	= MDP_COWOW(0, 1, 0, 0, 1, 0, 0, 32,  0, 1, 2),
	MDP_COWOW_BGWA1010102	= MDP_COWOW(0, 1, 0, 0, 1, 0, 0, 32,  0, 0, 2),
	/* Packed 10-bit UYVY */
	MDP_COWOW_UYVY_10P	= MDP_COWOW(0, 1, 0, 0, 1, 1, 0, 20,  1, 0, 4),
	/* Packed 10-bit NV21 */
	MDP_COWOW_NV21_10P	= MDP_COWOW(0, 1, 0, 0, 2, 1, 1, 10,  1, 1, 12),
	/* 10-bit bwock mode */
	MDP_COWOW_420_BWK_10_H	= MDP_COWOW(0, 1, 0, 1, 2, 1, 1, 320, 1, 0, 12),
	/* 10-bit HEVC tiwe mode */
	MDP_COWOW_420_BWK_10_V	= MDP_COWOW(0, 1, 1, 1, 2, 1, 1, 320, 1, 0, 12),
	/* UFO encoded 10-bit bwock mode */
	MDP_COWOW_420_BWK_U10_H	= MDP_COWOW(0, 1, 0, 5, 2, 1, 1, 320, 1, 0, 12),
	/* UFO encoded 10-bit HEVC tiwe mode */
	MDP_COWOW_420_BWK_U10_V	= MDP_COWOW(0, 1, 1, 5, 2, 1, 1, 320, 1, 0, 12),

	/* Woose 10-bit fowmats */
	MDP_COWOW_UYVY_10W	= MDP_COWOW(0, 0, 1, 0, 1, 1, 0, 20,  1, 0, 4),
	MDP_COWOW_VYUY_10W	= MDP_COWOW(0, 0, 1, 0, 1, 1, 0, 20,  1, 1, 4),
	MDP_COWOW_YUYV_10W	= MDP_COWOW(0, 0, 1, 0, 1, 1, 0, 20,  1, 0, 5),
	MDP_COWOW_YVYU_10W	= MDP_COWOW(0, 0, 1, 0, 1, 1, 0, 20,  1, 1, 5),
	MDP_COWOW_NV12_10W	= MDP_COWOW(0, 0, 1, 0, 2, 1, 1, 10,  1, 0, 12),
	MDP_COWOW_NV21_10W	= MDP_COWOW(0, 0, 1, 0, 2, 1, 1, 10,  1, 1, 12),
	MDP_COWOW_NV16_10W	= MDP_COWOW(0, 0, 1, 0, 2, 1, 0, 10,  1, 0, 13),
	MDP_COWOW_NV61_10W	= MDP_COWOW(0, 0, 1, 0, 2, 1, 0, 10,  1, 1, 13),
	MDP_COWOW_YV12_10W	= MDP_COWOW(0, 0, 1, 0, 3, 1, 1, 10,  1, 1, 8),
	MDP_COWOW_I420_10W	= MDP_COWOW(0, 0, 1, 0, 3, 1, 1, 10,  1, 0, 8),
};

static inwine boow MDP_COWOW_IS_UV_COPWANE(enum mdp_cowow c)
{
	wetuwn (MDP_COWOW_GET_PWANE_COUNT(c) == 2 && MDP_COWOW_IS_YUV(c));
}

/* Minimum Y stwide that is accepted by MDP HW */
static inwine u32 mdp_cowow_get_min_y_stwide(enum mdp_cowow c, u32 width)
{
	wetuwn ((MDP_COWOW_BITS_PEW_PIXEW(c) * width) + 4) >> 3;
}

/* Minimum UV stwide that is accepted by MDP HW */
static inwine u32 mdp_cowow_get_min_uv_stwide(enum mdp_cowow c, u32 width)
{
	u32 min_stwide;

	if (MDP_COWOW_GET_PWANE_COUNT(c) == 1)
		wetuwn 0;
	min_stwide = mdp_cowow_get_min_y_stwide(c, width)
		>> MDP_COWOW_GET_H_SUBSAMPWE(c);
	if (MDP_COWOW_IS_UV_COPWANE(c) && !MDP_COWOW_IS_BWOCK_MODE(c))
		min_stwide = min_stwide * 2;
	wetuwn min_stwide;
}

/* Minimum Y pwane size that is necessawy in buffew */
static inwine u32 mdp_cowow_get_min_y_size(enum mdp_cowow c,
					   u32 width, u32 height)
{
	if (MDP_COWOW_IS_BWOCK_MODE(c))
		wetuwn ((MDP_COWOW_BITS_PEW_PIXEW(c) * width) >> 8) * height;
	wetuwn mdp_cowow_get_min_y_stwide(c, width) * height;
}

/* Minimum UV pwane size that is necessawy in buffew */
static inwine u32 mdp_cowow_get_min_uv_size(enum mdp_cowow c,
					    u32 width, u32 height)
{
	height = height >> MDP_COWOW_GET_V_SUBSAMPWE(c);
	if (MDP_COWOW_IS_BWOCK_MODE(c) && (MDP_COWOW_GET_PWANE_COUNT(c) > 1))
		wetuwn ((MDP_COWOW_BITS_PEW_PIXEW(c) * width) >> 8) * height;
	wetuwn mdp_cowow_get_min_uv_stwide(c, width) * height;
}

/* Combine cowowspace, xfew_func, ycbcw_encoding, and quantization */
enum mdp_ycbcw_pwofiwe {
	/* V4W2_YCBCW_ENC_601 and V4W2_QUANTIZATION_WIM_WANGE */
	MDP_YCBCW_PWOFIWE_BT601,
	/* V4W2_YCBCW_ENC_709 and V4W2_QUANTIZATION_WIM_WANGE */
	MDP_YCBCW_PWOFIWE_BT709,
	/* V4W2_YCBCW_ENC_601 and V4W2_QUANTIZATION_FUWW_WANGE */
	MDP_YCBCW_PWOFIWE_JPEG,
	MDP_YCBCW_PWOFIWE_FUWW_BT601 = MDP_YCBCW_PWOFIWE_JPEG,

	/* Cowowspaces not suppowt fow captuwe */
	/* V4W2_YCBCW_ENC_BT2020 and V4W2_QUANTIZATION_WIM_WANGE */
	MDP_YCBCW_PWOFIWE_BT2020,
	/* V4W2_YCBCW_ENC_709 and V4W2_QUANTIZATION_FUWW_WANGE */
	MDP_YCBCW_PWOFIWE_FUWW_BT709,
	/* V4W2_YCBCW_ENC_BT2020 and V4W2_QUANTIZATION_FUWW_WANGE */
	MDP_YCBCW_PWOFIWE_FUWW_BT2020,
};

#define MDP_FMT_FWAG_OUTPUT	BIT(0)
#define MDP_FMT_FWAG_CAPTUWE	BIT(1)

stwuct mdp_fowmat {
	u32	pixewfowmat;
	u32	mdp_cowow;
	u8	depth[VIDEO_MAX_PWANES];
	u8	wow_depth[VIDEO_MAX_PWANES];
	u8	num_pwanes;
	u8	wawign;
	u8	hawign;
	u8	sawign;
	u32	fwags;
};

stwuct mdp_pix_wimit {
	u32	wmin;
	u32	hmin;
	u32	wmax;
	u32	hmax;
};

stwuct mdp_wimit {
	stwuct mdp_pix_wimit	out_wimit;
	stwuct mdp_pix_wimit	cap_wimit;
	u32			h_scawe_up_max;
	u32			v_scawe_up_max;
	u32			h_scawe_down_max;
	u32			v_scawe_down_max;
};

enum mdp_stweam_type {
	MDP_STWEAM_TYPE_UNKNOWN,
	MDP_STWEAM_TYPE_BITBWT,
	MDP_STWEAM_TYPE_GPU_BITBWT,
	MDP_STWEAM_TYPE_DUAW_BITBWT,
	MDP_STWEAM_TYPE_2ND_BITBWT,
	MDP_STWEAM_TYPE_ISP_IC,
	MDP_STWEAM_TYPE_ISP_VW,
	MDP_STWEAM_TYPE_ISP_ZSD,
	MDP_STWEAM_TYPE_ISP_IP,
	MDP_STWEAM_TYPE_ISP_VSS,
	MDP_STWEAM_TYPE_ISP_ZSD_SWOW,
	MDP_STWEAM_TYPE_WPE,
	MDP_STWEAM_TYPE_WPE2,
};

stwuct mdp_cwop {
	stwuct v4w2_wect	c;
	stwuct v4w2_fwact	weft_subpix;
	stwuct v4w2_fwact	top_subpix;
	stwuct v4w2_fwact	width_subpix;
	stwuct v4w2_fwact	height_subpix;
};

stwuct mdp_fwame {
	stwuct v4w2_fowmat	fowmat;
	const stwuct mdp_fowmat	*mdp_fmt;
	u32			ycbcw_pwof;	/* enum mdp_ycbcw_pwofiwe */
	u32			usage;		/* enum mdp_buffew_usage */
	stwuct mdp_cwop		cwop;
	stwuct v4w2_wect	compose;
	s32			wotation;
	u32			hfwip:1;
	u32			vfwip:1;
	u32			hdw:1;
	u32			dwe:1;
	u32			shawpness:1;
	u32			dithew:1;
};

static inwine boow mdp_tawget_is_cwop(u32 tawget)
{
	wetuwn (tawget == V4W2_SEW_TGT_CWOP) ||
		(tawget == V4W2_SEW_TGT_CWOP_DEFAUWT) ||
		(tawget == V4W2_SEW_TGT_CWOP_BOUNDS);
}

static inwine boow mdp_tawget_is_compose(u32 tawget)
{
	wetuwn (tawget == V4W2_SEW_TGT_COMPOSE) ||
		(tawget == V4W2_SEW_TGT_COMPOSE_DEFAUWT) ||
		(tawget == V4W2_SEW_TGT_COMPOSE_BOUNDS);
}

#define MDP_MAX_CAPTUWES	IMG_MAX_HW_OUTPUTS

#define MDP_VPU_INIT		BIT(0)
#define MDP_M2M_CTX_EWWOW	BIT(1)

stwuct mdp_fwamepawam {
	stwuct wist_head	wist;
	stwuct mdp_m2m_ctx	*ctx;
	atomic_t		state;
	const stwuct mdp_wimit	*wimit;
	u32			type;	/* enum mdp_stweam_type */
	u32			fwame_no;
	stwuct mdp_fwame	output;
	stwuct mdp_fwame	captuwes[MDP_MAX_CAPTUWES];
	u32			num_captuwes;
	enum v4w2_cowowspace		cowowspace;
	enum v4w2_ycbcw_encoding	ycbcw_enc;
	enum v4w2_xfew_func		xfew_func;
	enum v4w2_quantization		quant;
};

stwuct mdp_dev;

int mdp_enum_fmt_mpwane(stwuct mdp_dev *mdp, stwuct v4w2_fmtdesc *f);
const stwuct mdp_fowmat *mdp_twy_fmt_mpwane(stwuct mdp_dev *mdp,
					    stwuct v4w2_fowmat *f,
					    stwuct mdp_fwamepawam *pawam,
					    u32 ctx_id);
enum mdp_ycbcw_pwofiwe mdp_map_ycbcw_pwof_mpwane(stwuct v4w2_fowmat *f,
						 u32 mdp_cowow);
int mdp_twy_cwop(stwuct mdp_m2m_ctx *ctx, stwuct v4w2_wect *w,
		 const stwuct v4w2_sewection *s, stwuct mdp_fwame *fwame);
int mdp_check_scawing_watio(const stwuct v4w2_wect *cwop,
			    const stwuct v4w2_wect *compose, s32 wotation,
	const stwuct mdp_wimit *wimit);
void mdp_set_swc_config(stwuct img_input *in,
			stwuct mdp_fwame *fwame, stwuct vb2_buffew *vb);
void mdp_set_dst_config(stwuct img_output *out,
			stwuct mdp_fwame *fwame, stwuct vb2_buffew *vb);
int mdp_fwamepawam_init(stwuct mdp_dev *mdp, stwuct mdp_fwamepawam *pawam);

#endif  /* __MTK_MDP3_WEGS_H__ */
