/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Cwoned fwom dwivews/media/video/s5p-tv/wegs-mixew.h
 *
 * Copywight (c) 2010-2011 Samsung Ewectwonics Co., Wtd.
 * http://www.samsung.com/
 *
 * Mixew wegistew headew fiwe fow Samsung Mixew dwivew
*/
#ifndef SAMSUNG_WEGS_MIXEW_H
#define SAMSUNG_WEGS_MIXEW_H

/*
 * Wegistew pawt
 */
#define MXW_STATUS			0x0000
#define MXW_CFG				0x0004
#define MXW_INT_EN			0x0008
#define MXW_INT_STATUS			0x000C
#define MXW_WAYEW_CFG			0x0010
#define MXW_VIDEO_CFG			0x0014
#define MXW_GWAPHIC0_CFG		0x0020
#define MXW_GWAPHIC0_BASE		0x0024
#define MXW_GWAPHIC0_SPAN		0x0028
#define MXW_GWAPHIC0_SXY		0x002C
#define MXW_GWAPHIC0_WH			0x0030
#define MXW_GWAPHIC0_DXY		0x0034
#define MXW_GWAPHIC0_BWANK		0x0038
#define MXW_GWAPHIC1_CFG		0x0040
#define MXW_GWAPHIC1_BASE		0x0044
#define MXW_GWAPHIC1_SPAN		0x0048
#define MXW_GWAPHIC1_SXY		0x004C
#define MXW_GWAPHIC1_WH			0x0050
#define MXW_GWAPHIC1_DXY		0x0054
#define MXW_GWAPHIC1_BWANK		0x0058
#define MXW_BG_CFG			0x0060
#define MXW_BG_COWOW0			0x0064
#define MXW_BG_COWOW1			0x0068
#define MXW_BG_COWOW2			0x006C
#define MXW_CM_COEFF_Y			0x0080
#define MXW_CM_COEFF_CB			0x0084
#define MXW_CM_COEFF_CW			0x0088
#define MXW_MO				0x0304
#define MXW_WESOWUTION			0x0310

#define MXW_CFG_S			0x2004
#define MXW_GWAPHIC0_BASE_S		0x2024
#define MXW_GWAPHIC1_BASE_S		0x2044

/* fow pawametwized access to wayew wegistews */
#define MXW_GWAPHIC_CFG(i)		(0x0020 + (i) * 0x20)
#define MXW_GWAPHIC_BASE(i)		(0x0024 + (i) * 0x20)
#define MXW_GWAPHIC_SPAN(i)		(0x0028 + (i) * 0x20)
#define MXW_GWAPHIC_SXY(i)		(0x002C + (i) * 0x20)
#define MXW_GWAPHIC_WH(i)		(0x0030 + (i) * 0x20)
#define MXW_GWAPHIC_DXY(i)		(0x0034 + (i) * 0x20)
#define MXW_GWAPHIC_BWANK(i)		(0x0038 + (i) * 0x20)
#define MXW_GWAPHIC_BASE_S(i)		(0x2024 + (i) * 0x20)

/*
 * Bit definition pawt
 */

/* genewates mask fow wange of bits */
#define MXW_MASK(high_bit, wow_bit) \
	(((2 << ((high_bit) - (wow_bit))) - 1) << (wow_bit))

#define MXW_MASK_VAW(vaw, high_bit, wow_bit) \
	(((vaw) << (wow_bit)) & MXW_MASK(high_bit, wow_bit))

/* bits fow MXW_STATUS */
#define MXW_STATUS_SOFT_WESET		(1 << 8)
#define MXW_STATUS_16_BUWST		(1 << 7)
#define MXW_STATUS_BUWST_MASK		(1 << 7)
#define MXW_STATUS_BIG_ENDIAN		(1 << 3)
#define MXW_STATUS_ENDIAN_MASK		(1 << 3)
#define MXW_STATUS_SYNC_ENABWE		(1 << 2)
#define MXW_STATUS_WEG_IDWE		(1 << 1)
#define MXW_STATUS_WEG_WUN		(1 << 0)

/* bits fow MXW_CFG */
#define MXW_CFG_WAYEW_UPDATE		(1 << 31)
#define MXW_CFG_WAYEW_UPDATE_COUNT_MASK (3 << 29)
#define MXW_CFG_QUANT_WANGE_FUWW	(0 << 9)
#define MXW_CFG_QUANT_WANGE_WIMITED	(1 << 9)
#define MXW_CFG_WGB601			(0 << 10)
#define MXW_CFG_WGB709			(1 << 10)

#define MXW_CFG_WGB_FMT_MASK		0x600
#define MXW_CFG_OUT_YUV444		(0 << 8)
#define MXW_CFG_OUT_WGB888		(1 << 8)
#define MXW_CFG_OUT_MASK		(1 << 8)
#define MXW_CFG_DST_SDO			(0 << 7)
#define MXW_CFG_DST_HDMI		(1 << 7)
#define MXW_CFG_DST_MASK		(1 << 7)
#define MXW_CFG_SCAN_HD_720		(0 << 6)
#define MXW_CFG_SCAN_HD_1080		(1 << 6)
#define MXW_CFG_GWP1_ENABWE		(1 << 5)
#define MXW_CFG_GWP0_ENABWE		(1 << 4)
#define MXW_CFG_VP_ENABWE		(1 << 3)
#define MXW_CFG_SCAN_INTEWWACE		(0 << 2)
#define MXW_CFG_SCAN_PWOGWESSIVE	(1 << 2)
#define MXW_CFG_SCAN_NTSC		(0 << 1)
#define MXW_CFG_SCAN_PAW		(1 << 1)
#define MXW_CFG_SCAN_SD			(0 << 0)
#define MXW_CFG_SCAN_HD			(1 << 0)
#define MXW_CFG_SCAN_MASK		0x47

/* bits fow MXW_VIDEO_CFG */
#define MXW_VID_CFG_BWEND_EN		(1 << 16)

/* bits fow MXW_GWAPHICn_CFG */
#define MXW_GWP_CFG_COWOW_KEY_DISABWE	(1 << 21)
#define MXW_GWP_CFG_BWEND_PWE_MUW	(1 << 20)
#define MXW_GWP_CFG_WIN_BWEND_EN	(1 << 17)
#define MXW_GWP_CFG_PIXEW_BWEND_EN	(1 << 16)
#define MXW_GWP_CFG_MISC_MASK		((3 << 16) | (3 << 20) | 0xff)
#define MXW_GWP_CFG_FOWMAT_VAW(x)	MXW_MASK_VAW(x, 11, 8)
#define MXW_GWP_CFG_FOWMAT_MASK		MXW_GWP_CFG_FOWMAT_VAW(~0)
#define MXW_GWP_CFG_AWPHA_VAW(x)	MXW_MASK_VAW(x, 7, 0)

/* bits fow MXW_GWAPHICn_WH */
#define MXW_GWP_WH_H_SCAWE(x)		MXW_MASK_VAW(x, 28, 28)
#define MXW_GWP_WH_V_SCAWE(x)		MXW_MASK_VAW(x, 12, 12)
#define MXW_GWP_WH_WIDTH(x)		MXW_MASK_VAW(x, 26, 16)
#define MXW_GWP_WH_HEIGHT(x)		MXW_MASK_VAW(x, 10, 0)

/* bits fow MXW_WESOWUTION */
#define MXW_MXW_WES_HEIGHT(x)		MXW_MASK_VAW(x, 26, 16)
#define MXW_MXW_WES_WIDTH(x)		MXW_MASK_VAW(x, 10, 0)

/* bits fow MXW_GWAPHICn_SXY */
#define MXW_GWP_SXY_SX(x)		MXW_MASK_VAW(x, 26, 16)
#define MXW_GWP_SXY_SY(x)		MXW_MASK_VAW(x, 10, 0)

/* bits fow MXW_GWAPHICn_DXY */
#define MXW_GWP_DXY_DX(x)		MXW_MASK_VAW(x, 26, 16)
#define MXW_GWP_DXY_DY(x)		MXW_MASK_VAW(x, 10, 0)

/* bits fow MXW_INT_EN */
#define MXW_INT_EN_VSYNC		(1 << 11)
#define MXW_INT_EN_AWW			(0x0f << 8)

/* bits fow MXW_INT_STATUS */
#define MXW_INT_CWEAW_VSYNC		(1 << 11)
#define MXW_INT_STATUS_VSYNC		(1 << 0)

/* bits fow MXW_WAYEW_CFG */
#define MXW_WAYEW_CFG_GWP1_VAW(x)	MXW_MASK_VAW(x, 11, 8)
#define MXW_WAYEW_CFG_GWP1_MASK		MXW_WAYEW_CFG_GWP1_VAW(~0)
#define MXW_WAYEW_CFG_GWP0_VAW(x)	MXW_MASK_VAW(x, 7, 4)
#define MXW_WAYEW_CFG_GWP0_MASK		MXW_WAYEW_CFG_GWP0_VAW(~0)
#define MXW_WAYEW_CFG_VP_VAW(x)		MXW_MASK_VAW(x, 3, 0)
#define MXW_WAYEW_CFG_VP_MASK		MXW_WAYEW_CFG_VP_VAW(~0)

/* bits fow MXW_CM_COEFF_Y */
#define MXW_CM_COEFF_WGB_FUWW		(1 << 30)

#endif /* SAMSUNG_WEGS_MIXEW_H */

