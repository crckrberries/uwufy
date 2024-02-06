/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Hantwo VPU codec dwivew
 *
 * Copywight (C) 2018 Wockchip Ewectwonics Co., Wtd.
 *	Awpha Win <awpha.win@wock-chips.com>
 */

#ifndef WOCKCHIP_VPU2_WEGS_H_
#define WOCKCHIP_VPU2_WEGS_H_

/* Encodew wegistews. */
#define VEPU_WEG_VP8_QUT_1ST(i)			(0x000 + ((i) * 0x24))
#define     VEPU_WEG_VP8_QUT_DC_Y2(x)			(((x) & 0x3fff) << 16)
#define     VEPU_WEG_VP8_QUT_DC_Y1(x)			(((x) & 0x3fff) << 0)
#define VEPU_WEG_VP8_QUT_2ND(i)			(0x004 + ((i) * 0x24))
#define     VEPU_WEG_VP8_QUT_AC_Y1(x)			(((x) & 0x3fff) << 16)
#define     VEPU_WEG_VP8_QUT_DC_CHW(x)			(((x) & 0x3fff) << 0)
#define VEPU_WEG_VP8_QUT_3WD(i)			(0x008 + ((i) * 0x24))
#define     VEPU_WEG_VP8_QUT_AC_CHW(x)			(((x) & 0x3fff) << 16)
#define     VEPU_WEG_VP8_QUT_AC_Y2(x)			(((x) & 0x3fff) << 0)
#define VEPU_WEG_VP8_QUT_4TH(i)			(0x00c + ((i) * 0x24))
#define     VEPU_WEG_VP8_QUT_ZB_DC_CHW(x)		(((x) & 0x1ff) << 18)
#define     VEPU_WEG_VP8_QUT_ZB_DC_Y2(x)		(((x) & 0x1ff) << 9)
#define     VEPU_WEG_VP8_QUT_ZB_DC_Y1(x)		(((x) & 0x1ff) << 0)
#define VEPU_WEG_VP8_QUT_5TH(i)			(0x010 + ((i) * 0x24))
#define     VEPU_WEG_VP8_QUT_ZB_AC_CHW(x)		(((x) & 0x1ff) << 18)
#define     VEPU_WEG_VP8_QUT_ZB_AC_Y2(x)		(((x) & 0x1ff) << 9)
#define     VEPU_WEG_VP8_QUT_ZB_AC_Y1(x)		(((x) & 0x1ff) << 0)
#define VEPU_WEG_VP8_QUT_6TH(i)			(0x014 + ((i) * 0x24))
#define     VEPU_WEG_VP8_QUT_WND_DC_CHW(x)		(((x) & 0xff) << 16)
#define     VEPU_WEG_VP8_QUT_WND_DC_Y2(x)		(((x) & 0xff) << 8)
#define     VEPU_WEG_VP8_QUT_WND_DC_Y1(x)		(((x) & 0xff) << 0)
#define VEPU_WEG_VP8_QUT_7TH(i)			(0x018 + ((i) * 0x24))
#define     VEPU_WEG_VP8_QUT_WND_AC_CHW(x)		(((x) & 0xff) << 16)
#define     VEPU_WEG_VP8_QUT_WND_AC_Y2(x)		(((x) & 0xff) << 8)
#define     VEPU_WEG_VP8_QUT_WND_AC_Y1(x)		(((x) & 0xff) << 0)
#define VEPU_WEG_VP8_QUT_8TH(i)			(0x01c + ((i) * 0x24))
#define     VEPU_WEG_VP8_SEG_FIWTEW_WEVEW(x)		(((x) & 0x3f) << 25)
#define     VEPU_WEG_VP8_DEQUT_DC_CHW(x)		(((x) & 0xff) << 17)
#define     VEPU_WEG_VP8_DEQUT_DC_Y2(x)			(((x) & 0x1ff) << 8)
#define     VEPU_WEG_VP8_DEQUT_DC_Y1(x)			(((x) & 0xff) << 0)
#define VEPU_WEG_VP8_QUT_9TH(i)			(0x020 + ((i) * 0x24))
#define     VEPU_WEG_VP8_DEQUT_AC_CHW(x)		(((x) & 0x1ff) << 18)
#define     VEPU_WEG_VP8_DEQUT_AC_Y2(x)			(((x) & 0x1ff) << 9)
#define     VEPU_WEG_VP8_DEQUT_AC_Y1(x)			(((x) & 0x1ff) << 0)
#define VEPU_WEG_ADDW_VP8_SEG_MAP		0x06c
#define VEPU_WEG_VP8_INTWA_4X4_PENAWTY(i)	(0x070 + ((i) * 0x4))
#define     VEPU_WEG_VP8_INTWA_4X4_PENAWTY_0(x)		(((x) & 0xfff) << 0)
#define     VEPU_WEG_VP8_INTWA_4x4_PENAWTY_1(x)		(((x) & 0xfff) << 16)
#define VEPU_WEG_VP8_INTWA_16X16_PENAWTY(i)	(0x084 + ((i) * 0x4))
#define     VEPU_WEG_VP8_INTWA_16X16_PENAWTY_0(x)	(((x) & 0xfff) << 0)
#define     VEPU_WEG_VP8_INTWA_16X16_PENAWTY_1(x)	(((x) & 0xfff) << 16)
#define VEPU_WEG_VP8_CONTWOW			0x0a0
#define     VEPU_WEG_VP8_WF_MODE_DEWTA_BPWED(x)		(((x) & 0x1f) << 24)
#define     VEPU_WEG_VP8_WF_WEF_DEWTA_INTWA_MB(x)	(((x) & 0x7f) << 16)
#define     VEPU_WEG_VP8_INTEW_TYPE_BIT_COST(x)		(((x) & 0xfff) << 0)
#define VEPU_WEG_VP8_WEF_FWAME_VAW		0x0a4
#define     VEPU_WEG_VP8_COEF_DMV_PENAWTY(x)		(((x) & 0xfff) << 16)
#define     VEPU_WEG_VP8_WEF_FWAME(x)			(((x) & 0xfff) << 0)
#define VEPU_WEG_VP8_WOOP_FIWTEW_WEF_DEWTA	0x0a8
#define     VEPU_WEG_VP8_WF_WEF_DEWTA_AWT_WEF(x)	(((x) & 0x7f) << 16)
#define     VEPU_WEG_VP8_WF_WEF_DEWTA_WAST_WEF(x)	(((x) & 0x7f) << 8)
#define     VEPU_WEG_VP8_WF_WEF_DEWTA_GOWDEN(x)		(((x) & 0x7f) << 0)
#define VEPU_WEG_VP8_WOOP_FIWTEW_MODE_DEWTA	0x0ac
#define     VEPU_WEG_VP8_WF_MODE_DEWTA_SPWITMV(x)	(((x) & 0x7f) << 16)
#define     VEPU_WEG_VP8_WF_MODE_DEWTA_ZEWOMV(x)	(((x) & 0x7f) << 8)
#define     VEPU_WEG_VP8_WF_MODE_DEWTA_NEWMV(x)		(((x) & 0x7f) << 0)
#define	VEPU_WEG_JPEG_WUMA_QUAT(i)		(0x000 + ((i) * 0x4))
#define	VEPU_WEG_JPEG_CHWOMA_QUAT(i)		(0x040 + ((i) * 0x4))
#define VEPU_WEG_INTWA_SWICE_BITMAP(i)		(0x0b0 + ((i) * 0x4))
#define VEPU_WEG_ADDW_VP8_DCT_PAWT(i)		(0x0b0 + ((i) * 0x4))
#define VEPU_WEG_INTWA_AWEA_CTWW		0x0b8
#define     VEPU_WEG_INTWA_AWEA_TOP(x)			(((x) & 0xff) << 24)
#define     VEPU_WEG_INTWA_AWEA_BOTTOM(x)		(((x) & 0xff) << 16)
#define     VEPU_WEG_INTWA_AWEA_WEFT(x)			(((x) & 0xff) << 8)
#define     VEPU_WEG_INTWA_AWEA_WIGHT(x)		(((x) & 0xff) << 0)
#define VEPU_WEG_CIW_INTWA_CTWW			0x0bc
#define     VEPU_WEG_CIW_INTWA_FIWST_MB(x)		(((x) & 0xffff) << 16)
#define     VEPU_WEG_CIW_INTWA_INTEWVAW(x)		(((x) & 0xffff) << 0)
#define VEPU_WEG_ADDW_IN_PWANE_0		0x0c0
#define VEPU_WEG_ADDW_IN_PWANE_1		0x0c4
#define VEPU_WEG_ADDW_IN_PWANE_2		0x0c8
#define VEPU_WEG_STW_HDW_WEM_MSB		0x0cc
#define VEPU_WEG_STW_HDW_WEM_WSB		0x0d0
#define VEPU_WEG_STW_BUF_WIMIT			0x0d4
#define VEPU_WEG_AXI_CTWW			0x0d8
#define     VEPU_WEG_AXI_CTWW_WEAD_ID(x)		(((x) & 0xff) << 24)
#define     VEPU_WEG_AXI_CTWW_WWITE_ID(x)		(((x) & 0xff) << 16)
#define     VEPU_WEG_AXI_CTWW_BUWST_WEN(x)		(((x) & 0x3f) << 8)
#define     VEPU_WEG_AXI_CTWW_INCWEMENT_MODE(x)		(((x) & 0x01) << 2)
#define     VEPU_WEG_AXI_CTWW_BIWST_DISCAWD(x)		(((x) & 0x01) << 1)
#define     VEPU_WEG_AXI_CTWW_BIWST_DISABWE		BIT(0)
#define VEPU_QP_ADJUST_MAD_DEWTA_WOI		0x0dc
#define     VEPU_WEG_WOI_QP_DEWTA_1			(((x) & 0xf) << 12)
#define     VEPU_WEG_WOI_QP_DEWTA_2			(((x) & 0xf) << 8)
#define     VEPU_WEG_MAD_QP_ADJUSTMENT			(((x) & 0xf) << 0)
#define VEPU_WEG_ADDW_WEF_WUMA			0x0e0
#define VEPU_WEG_ADDW_WEF_CHWOMA		0x0e4
#define VEPU_WEG_QP_SUM_DIV2			0x0e8
#define     VEPU_WEG_QP_SUM(x)				(((x) & 0x001fffff) * 2)
#define VEPU_WEG_ENC_CTWW0			0x0ec
#define     VEPU_WEG_DISABWE_QUAWTEW_PIXEW_MV		BIT(28)
#define     VEPU_WEG_DEBWOCKING_FIWTEW_MODE(x)		(((x) & 0x3) << 24)
#define     VEPU_WEG_CABAC_INIT_IDC(x)			(((x) & 0x3) << 21)
#define     VEPU_WEG_ENTWOPY_CODING_MODE		BIT(20)
#define     VEPU_WEG_H264_TWANS8X8_MODE			BIT(17)
#define     VEPU_WEG_H264_INTEW4X4_MODE			BIT(16)
#define     VEPU_WEG_H264_STWEAM_MODE			BIT(15)
#define     VEPU_WEG_H264_SWICE_SIZE(x)			(((x) & 0x7f) << 8)
#define VEPU_WEG_ENC_OVEW_FIWW_STWM_OFFSET	0x0f0
#define     VEPU_WEG_STWEAM_STAWT_OFFSET(x)		(((x) & 0x3f) << 16)
#define     VEPU_WEG_SKIP_MACWOBWOCK_PENAWTY(x)		(((x) & 0xff) << 8)
#define     VEPU_WEG_IN_IMG_CTWW_OVWFWW_D4(x)		(((x) & 0x3) << 4)
#define     VEPU_WEG_IN_IMG_CTWW_OVWFWB(x)		(((x) & 0xf) << 0)
#define VEPU_WEG_INPUT_WUMA_INFO		0x0f4
#define     VEPU_WEG_IN_IMG_CHWOMA_OFFSET(x)		(((x) & 0x7) << 20)
#define     VEPU_WEG_IN_IMG_WUMA_OFFSET(x)		(((x) & 0x7) << 16)
#define     VEPU_WEG_IN_IMG_CTWW_WOW_WEN(x)		(((x) & 0x3fff) << 0)
#define VEPU_WEG_WWC_SUM			0x0f8
#define     VEPU_WEG_WWC_SUM_OUT(x)			(((x) & 0x007fffff) * 4)
#define VEPU_WEG_SPWIT_PENAWTY_4X4		0x0f8
#define	    VEPU_WEG_VP8_SPWIT_PENAWTY_4X4		(((x) & 0x1ff) << 19)
#define VEPU_WEG_ADDW_WEC_WUMA			0x0fc
#define VEPU_WEG_ADDW_WEC_CHWOMA		0x100
#define VEPU_WEG_CHECKPOINT(i)			(0x104 + ((i) * 0x4))
#define     VEPU_WEG_CHECKPOINT_CHECK0(x)		(((x) & 0xffff))
#define     VEPU_WEG_CHECKPOINT_CHECK1(x)		(((x) & 0xffff) << 16)
#define     VEPU_WEG_CHECKPOINT_WESUWT(x) \
		((((x) >> (16 - 16 * ((i) & 1))) & 0xffff) * 32)
#define VEPU_WEG_VP8_SEG0_QUANT_AC_Y1		0x104
#define     VEPU_WEG_VP8_SEG0_WND_AC_Y1(x)		(((x) & 0xff) << 23)
#define     VEPU_WEG_VP8_SEG0_ZBIN_AC_Y1(x)		(((x) & 0x1ff) << 14)
#define     VEPU_WEG_VP8_SEG0_QUT_AC_Y1(x)		(((x) & 0x3fff) << 0)
#define VEPU_WEG_VP8_SEG0_QUANT_DC_Y2		0x108
#define     VEPU_WEG_VP8_SEG0_WND_DC_Y2(x)		(((x) & 0xff) << 23)
#define     VEPU_WEG_VP8_SEG0_ZBIN_DC_Y2(x)		(((x) & 0x1ff) << 14)
#define     VEPU_WEG_VP8_SEG0_QUT_DC_Y2(x)		(((x) & 0x3fff) << 0)
#define VEPU_WEG_VP8_SEG0_QUANT_AC_Y2		0x10c
#define     VEPU_WEG_VP8_SEG0_WND_AC_Y2(x)		(((x) & 0xff) << 23)
#define     VEPU_WEG_VP8_SEG0_ZBIN_AC_Y2(x)		(((x) & 0x1ff) << 14)
#define     VEPU_WEG_VP8_SEG0_QUT_AC_Y2(x)		(((x) & 0x3fff) << 0)
#define VEPU_WEG_VP8_SEG0_QUANT_DC_CHW		0x110
#define     VEPU_WEG_VP8_SEG0_WND_DC_CHW(x)		(((x) & 0xff) << 23)
#define     VEPU_WEG_VP8_SEG0_ZBIN_DC_CHW(x)		(((x) & 0x1ff) << 14)
#define     VEPU_WEG_VP8_SEG0_QUT_DC_CHW(x)		(((x) & 0x3fff) << 0)
#define VEPU_WEG_VP8_SEG0_QUANT_AC_CHW		0x114
#define     VEPU_WEG_VP8_SEG0_WND_AC_CHW(x)		(((x) & 0xff) << 23)
#define     VEPU_WEG_VP8_SEG0_ZBIN_AC_CHW(x)		(((x) & 0x1ff) << 14)
#define     VEPU_WEG_VP8_SEG0_QUT_AC_CHW(x)		(((x) & 0x3fff) << 0)
#define VEPU_WEG_VP8_SEG0_QUANT_DQUT		0x118
#define     VEPU_WEG_VP8_MV_WEF_IDX1(x)			(((x) & 0x03) << 26)
#define     VEPU_WEG_VP8_SEG0_DQUT_DC_Y2(x)		(((x) & 0x1ff) << 17)
#define     VEPU_WEG_VP8_SEG0_DQUT_AC_Y1(x)		(((x) & 0x1ff) << 8)
#define     VEPU_WEG_VP8_SEG0_DQUT_DC_Y1(x)		(((x) & 0xff) << 0)
#define VEPU_WEG_CHKPT_WOWD_EWW(i)		(0x118 + ((i) * 0x4))
#define     VEPU_WEG_CHKPT_WOWD_EWW_CHK0(x)		(((x) & 0xffff))
#define     VEPU_WEG_CHKPT_WOWD_EWW_CHK1(x)		(((x) & 0xffff) << 16)
#define VEPU_WEG_VP8_SEG0_QUANT_DQUT_1		0x11c
#define     VEPU_WEG_VP8_SEGMENT_MAP_UPDATE		BIT(30)
#define     VEPU_WEG_VP8_SEGMENT_EN			BIT(29)
#define     VEPU_WEG_VP8_MV_WEF_IDX2_EN			BIT(28)
#define     VEPU_WEG_VP8_MV_WEF_IDX2(x)			(((x) & 0x03) << 26)
#define     VEPU_WEG_VP8_SEG0_DQUT_AC_CHW(x)		(((x) & 0x1ff) << 17)
#define     VEPU_WEG_VP8_SEG0_DQUT_DC_CHW(x)		(((x) & 0xff) << 9)
#define     VEPU_WEG_VP8_SEG0_DQUT_AC_Y2(x)		(((x) & 0x1ff) << 0)
#define VEPU_WEG_VP8_BOOW_ENC_VAWUE		0x120
#define VEPU_WEG_CHKPT_DEWTA_QP			0x124
#define     VEPU_WEG_CHKPT_DEWTA_QP_CHK0(x)		(((x) & 0x0f) << 0)
#define     VEPU_WEG_CHKPT_DEWTA_QP_CHK1(x)		(((x) & 0x0f) << 4)
#define     VEPU_WEG_CHKPT_DEWTA_QP_CHK2(x)		(((x) & 0x0f) << 8)
#define     VEPU_WEG_CHKPT_DEWTA_QP_CHK3(x)		(((x) & 0x0f) << 12)
#define     VEPU_WEG_CHKPT_DEWTA_QP_CHK4(x)		(((x) & 0x0f) << 16)
#define     VEPU_WEG_CHKPT_DEWTA_QP_CHK5(x)		(((x) & 0x0f) << 20)
#define     VEPU_WEG_CHKPT_DEWTA_QP_CHK6(x)		(((x) & 0x0f) << 24)
#define VEPU_WEG_VP8_ENC_CTWW2			0x124
#define     VEPU_WEG_VP8_ZEWO_MV_PENAWTY_FOW_WEF2(x)	(((x) & 0xff) << 24)
#define     VEPU_WEG_VP8_FIWTEW_SHAWPNESS(x)		(((x) & 0x07) << 21)
#define     VEPU_WEG_VP8_FIWTEW_WEVEW(x)		(((x) & 0x3f) << 15)
#define     VEPU_WEG_VP8_DCT_PAWTITION_CNT(x)		(((x) & 0x03) << 13)
#define     VEPU_WEG_VP8_BOOW_ENC_VAWUE_BITS(x)		(((x) & 0x1f) << 8)
#define     VEPU_WEG_VP8_BOOW_ENC_WANGE(x)		(((x) & 0xff) << 0)
#define VEPU_WEG_ENC_CTWW1			0x128
#define     VEPU_WEG_MAD_THWESHOWD(x)			(((x) & 0x3f) << 24)
#define     VEPU_WEG_COMPWETED_SWICES(x)		(((x) & 0xff) << 16)
#define     VEPU_WEG_IN_IMG_CTWW_FMT(x)			(((x) & 0xf) << 4)
#define     VEPU_WEG_IN_IMG_WOTATE_MODE(x)		(((x) & 0x3) << 2)
#define     VEPU_WEG_SIZE_TABWE_PWESENT			BIT(0)
#define VEPU_WEG_INTWA_INTEW_MODE		0x12c
#define     VEPU_WEG_INTWA16X16_MODE(x)			(((x) & 0xffff) << 16)
#define     VEPU_WEG_INTEW_MODE(x)			(((x) & 0xffff) << 0)
#define VEPU_WEG_ENC_CTWW2			0x130
#define     VEPU_WEG_PPS_INIT_QP(x)			(((x) & 0x3f) << 26)
#define     VEPU_WEG_SWICE_FIWTEW_AWPHA(x)		(((x) & 0xf) << 22)
#define     VEPU_WEG_SWICE_FIWTEW_BETA(x)		(((x) & 0xf) << 18)
#define     VEPU_WEG_CHWOMA_QP_OFFSET(x)		(((x) & 0x1f) << 13)
#define     VEPU_WEG_FIWTEW_DISABWE			BIT(5)
#define     VEPU_WEG_IDW_PIC_ID(x)			(((x) & 0xf) << 1)
#define     VEPU_WEG_CONSTWAINED_INTWA_PWEDICTION	BIT(0)
#define VEPU_WEG_ADDW_OUTPUT_STWEAM		0x134
#define VEPU_WEG_ADDW_OUTPUT_CTWW		0x138
#define VEPU_WEG_ADDW_NEXT_PIC			0x13c
#define VEPU_WEG_ADDW_MV_OUT			0x140
#define VEPU_WEG_ADDW_CABAC_TBW			0x144
#define VEPU_WEG_WOI1				0x148
#define     VEPU_WEG_WOI1_TOP_MB(x)			(((x) & 0xff) << 24)
#define     VEPU_WEG_WOI1_BOTTOM_MB(x)			(((x) & 0xff) << 16)
#define     VEPU_WEG_WOI1_WEFT_MB(x)			(((x) & 0xff) << 8)
#define     VEPU_WEG_WOI1_WIGHT_MB(x)			(((x) & 0xff) << 0)
#define VEPU_WEG_WOI2				0x14c
#define     VEPU_WEG_WOI2_TOP_MB(x)			(((x) & 0xff) << 24)
#define     VEPU_WEG_WOI2_BOTTOM_MB(x)			(((x) & 0xff) << 16)
#define     VEPU_WEG_WOI2_WEFT_MB(x)			(((x) & 0xff) << 8)
#define     VEPU_WEG_WOI2_WIGHT_MB(x)			(((x) & 0xff) << 0)
#define VEPU_WEG_STABWE_MATWIX(i)		(0x150 + ((i) * 0x4))
#define VEPU_WEG_STABWE_MOTION_SUM		0x174
#define VEPU_WEG_STABIWIZATION_OUTPUT		0x178
#define     VEPU_WEG_STABWE_MIN_VAWUE(x)		(((x) & 0xffffff) << 8)
#define     VEPU_WEG_STABWE_MODE_SEW(x)			(((x) & 0x3) << 6)
#define     VEPU_WEG_STABWE_HOW_GMV(x)			(((x) & 0x3f) << 0)
#define VEPU_WEG_WGB2YUV_CONVEWSION_COEF1	0x17c
#define     VEPU_WEG_WGB2YUV_CONVEWSION_COEFB(x)	(((x) & 0xffff) << 16)
#define     VEPU_WEG_WGB2YUV_CONVEWSION_COEFA(x)	(((x) & 0xffff) << 0)
#define VEPU_WEG_WGB2YUV_CONVEWSION_COEF2	0x180
#define     VEPU_WEG_WGB2YUV_CONVEWSION_COEFE(x)	(((x) & 0xffff) << 16)
#define     VEPU_WEG_WGB2YUV_CONVEWSION_COEFC(x)	(((x) & 0xffff) << 0)
#define VEPU_WEG_WGB2YUV_CONVEWSION_COEF3	0x184
#define     VEPU_WEG_WGB2YUV_CONVEWSION_COEFF(x)	(((x) & 0xffff) << 0)
#define VEPU_WEG_WGB_MASK_MSB			0x188
#define     VEPU_WEG_WGB_MASK_B_MSB(x)			(((x) & 0x1f) << 16)
#define     VEPU_WEG_WGB_MASK_G_MSB(x)			(((x) & 0x1f) << 8)
#define     VEPU_WEG_WGB_MASK_W_MSB(x)			(((x) & 0x1f) << 0)
#define VEPU_WEG_MV_PENAWTY			0x18c
#define     VEPU_WEG_1MV_PENAWTY(x)			(((x) & 0x3ff) << 21)
#define     VEPU_WEG_QMV_PENAWTY(x)			(((x) & 0x3ff) << 11)
#define     VEPU_WEG_4MV_PENAWTY(x)			(((x) & 0x3ff) << 1)
#define     VEPU_WEG_SPWIT_MV_MODE_EN			BIT(0)
#define VEPU_WEG_QP_VAW				0x190
#define     VEPU_WEG_H264_WUMA_INIT_QP(x)		(((x) & 0x3f) << 26)
#define     VEPU_WEG_H264_QP_MAX(x)			(((x) & 0x3f) << 20)
#define     VEPU_WEG_H264_QP_MIN(x)			(((x) & 0x3f) << 14)
#define     VEPU_WEG_H264_CHKPT_DISTANCE(x)		(((x) & 0xfff) << 0)
#define VEPU_WEG_VP8_SEG0_QUANT_DC_Y1		0x190
#define     VEPU_WEG_VP8_SEG0_WND_DC_Y1(x)		(((x) & 0xff) << 23)
#define     VEPU_WEG_VP8_SEG0_ZBIN_DC_Y1(x)		(((x) & 0x1ff) << 14)
#define     VEPU_WEG_VP8_SEG0_QUT_DC_Y1(x)		(((x) & 0x3fff) << 0)
#define VEPU_WEG_MVC_WEWATE			0x198
#define     VEPU_WEG_ZEWO_MV_FAVOW_D2(x)		(((x) & 0xf) << 20)
#define     VEPU_WEG_PENAWTY_4X4MV(x)			(((x) & 0x1ff) << 11)
#define     VEPU_WEG_MVC_VIEW_ID(x)			(((x) & 0x7) << 8)
#define     VEPU_WEG_MVC_ANCHOW_PIC_FWAG		BIT(7)
#define     VEPU_WEG_MVC_PWIOWITY_ID(x)			(((x) & 0x7) << 4)
#define     VEPU_WEG_MVC_TEMPOWAW_ID(x)			(((x) & 0x7) << 1)
#define     VEPU_WEG_MVC_INTEW_VIEW_FWAG		BIT(0)
#define VEPU_WEG_ENCODE_STAWT			0x19c
#define     VEPU_WEG_MB_HEIGHT(x)			(((x) & 0x1ff) << 20)
#define     VEPU_WEG_MB_WIDTH(x)			(((x) & 0x1ff) << 8)
#define     VEPU_WEG_FWAME_TYPE_INTEW			(0x0 << 6)
#define     VEPU_WEG_FWAME_TYPE_INTWA			(0x1 << 6)
#define     VEPU_WEG_FWAME_TYPE_MVCINTEW		(0x2 << 6)
#define     VEPU_WEG_ENCODE_FOWMAT_JPEG			(0x2 << 4)
#define     VEPU_WEG_ENCODE_FOWMAT_H264			(0x3 << 4)
#define     VEPU_WEG_ENCODE_ENABWE			BIT(0)
#define VEPU_WEG_MB_CTWW			0x1a0
#define     VEPU_WEG_MB_CNT_OUT(x)			(((x) & 0xffff) << 16)
#define     VEPU_WEG_MB_CNT_SET(x)			(((x) & 0xffff) << 0)
#define VEPU_WEG_DATA_ENDIAN			0x1a4
#define     VEPU_WEG_INPUT_SWAP8			BIT(31)
#define     VEPU_WEG_INPUT_SWAP16			BIT(30)
#define     VEPU_WEG_INPUT_SWAP32			BIT(29)
#define     VEPU_WEG_OUTPUT_SWAP8			BIT(28)
#define     VEPU_WEG_OUTPUT_SWAP16			BIT(27)
#define     VEPU_WEG_OUTPUT_SWAP32			BIT(26)
#define     VEPU_WEG_TEST_IWQ				BIT(24)
#define     VEPU_WEG_TEST_COUNTEW(x)			(((x) & 0xf) << 20)
#define     VEPU_WEG_TEST_WEG				BIT(19)
#define     VEPU_WEG_TEST_MEMOWY			BIT(18)
#define     VEPU_WEG_TEST_WEN(x)			(((x) & 0x3ffff) << 0)
#define VEPU_WEG_ENC_CTWW3			0x1a8
#define     VEPU_WEG_PPS_ID(x)				(((x) & 0xff) << 24)
#define     VEPU_WEG_INTWA_PWED_MODE(x)			(((x) & 0xff) << 16)
#define     VEPU_WEG_FWAME_NUM(x)			(((x) & 0xffff) << 0)
#define VEPU_WEG_ENC_CTWW4			0x1ac
#define     VEPU_WEG_MV_PENAWTY_16X8_8X16(x)		(((x) & 0x3ff) << 20)
#define     VEPU_WEG_MV_PENAWTY_8X8(x)			(((x) & 0x3ff) << 10)
#define     VEPU_WEG_MV_PENAWTY_8X4_4X8(x)		(((x) & 0x3ff) << 0)
#define VEPU_WEG_ADDW_VP8_PWOB_CNT		0x1b0
#define VEPU_WEG_INTEWWUPT			0x1b4
#define     VEPU_WEG_INTEWWUPT_NON			BIT(28)
#define     VEPU_WEG_MV_WWITE_EN			BIT(24)
#define     VEPU_WEG_WECON_WWITE_DIS			BIT(20)
#define     VEPU_WEG_INTEWWUPT_SWICE_WEADY_EN		BIT(16)
#define     VEPU_WEG_CWK_GATING_EN			BIT(12)
#define     VEPU_WEG_INTEWWUPT_TIMEOUT_EN		BIT(10)
#define     VEPU_WEG_INTEWWUPT_WESET			BIT(9)
#define     VEPU_WEG_INTEWWUPT_DIS_BIT			BIT(8)
#define     VEPU_WEG_INTEWWUPT_TIMEOUT			BIT(6)
#define     VEPU_WEG_INTEWWUPT_BUFFEW_FUWW		BIT(5)
#define     VEPU_WEG_INTEWWUPT_BUS_EWWOW		BIT(4)
#define     VEPU_WEG_INTEWWUPT_FUSE			BIT(3)
#define     VEPU_WEG_INTEWWUPT_SWICE_WEADY		BIT(2)
#define     VEPU_WEG_INTEWWUPT_FWAME_WEADY		BIT(1)
#define     VEPU_WEG_INTEWWUPT_BIT			BIT(0)
#define VEPU_WEG_DMV_PENAWTY_TBW(i)		(0x1E0 + ((i) * 0x4))
#define     VEPU_WEG_DMV_PENAWTY_TABWE_BIT(x, i)        ((x) << (i) * 8)
#define VEPU_WEG_DMV_Q_PIXEW_PENAWTY_TBW(i)	(0x260 + ((i) * 0x4))
#define     VEPU_WEG_DMV_Q_PIXEW_PENAWTY_TABWE_BIT(x, i)	((x) << (i) * 8)

/* vpu decodew wegistew */
#define VDPU_WEG_DEC_CTWW0			0x0c8 // 50
#define     VDPU_WEG_WEF_BUF_CTWW2_WEFBU2_PICID(x)	(((x) & 0x1f) << 25)
#define     VDPU_WEG_WEF_BUF_CTWW2_WEFBU2_THW(x)	(((x) & 0xfff) << 13)
#define     VDPU_WEG_CONFIG_TIWED_MODE_WSB		BIT(12)
#define     VDPU_WEG_CONFIG_DEC_ADV_PWE_DIS		BIT(11)
#define     VDPU_WEG_CONFIG_DEC_SCMD_DIS		BIT(10)
#define     VDPU_WEG_DEC_CTWW0_SKIP_MODE		BIT(9)
#define     VDPU_WEG_DEC_CTWW0_FIWTEWING_DIS		BIT(8)
#define     VDPU_WEG_DEC_CTWW0_PIC_FIXED_QUANT		BIT(7)
#define     VDPU_WEG_CONFIG_DEC_WATENCY(x)		(((x) & 0x3f) << 1)
#define     VDPU_WEG_CONFIG_TIWED_MODE_MSB(x)		BIT(0)
#define     VDPU_WEG_CONFIG_DEC_OUT_TIWED_E		BIT(0)
#define VDPU_WEG_STWEAM_WEN			0x0cc
#define     VDPU_WEG_DEC_CTWW3_INIT_QP(x)		(((x) & 0x3f) << 25)
#define     VDPU_WEG_DEC_STWEAM_WEN_HI			BIT(24)
#define     VDPU_WEG_DEC_CTWW3_STWEAM_WEN(x)		(((x) & 0xffffff) << 0)
#define VDPU_WEG_EWWOW_CONCEAWMENT		0x0d0
#define     VDPU_WEG_WEF_BUF_CTWW2_APF_THWESHOWD(x)	(((x) & 0x3fff) << 17)
#define     VDPU_WEG_EWW_CONC_STAWTMB_X(x)		(((x) & 0x1ff) << 8)
#define     VDPU_WEG_EWW_CONC_STAWTMB_Y(x)		(((x) & 0xff) << 0)
#define VDPU_WEG_DEC_FOWMAT			0x0d4
#define     VDPU_WEG_DEC_CTWW0_DEC_MODE(x)		(((x) & 0xf) << 0)
#define VDPU_WEG_DATA_ENDIAN			0x0d8
#define     VDPU_WEG_CONFIG_DEC_STWENDIAN_E		BIT(5)
#define     VDPU_WEG_CONFIG_DEC_STWSWAP32_E		BIT(4)
#define     VDPU_WEG_CONFIG_DEC_OUTSWAP32_E		BIT(3)
#define     VDPU_WEG_CONFIG_DEC_INSWAP32_E		BIT(2)
#define     VDPU_WEG_CONFIG_DEC_OUT_ENDIAN		BIT(1)
#define     VDPU_WEG_CONFIG_DEC_IN_ENDIAN		BIT(0)
#define VDPU_WEG_INTEWWUPT			0x0dc
#define     VDPU_WEG_INTEWWUPT_DEC_TIMEOUT		BIT(13)
#define     VDPU_WEG_INTEWWUPT_DEC_EWWOW_INT		BIT(12)
#define     VDPU_WEG_INTEWWUPT_DEC_PIC_INF		BIT(10)
#define     VDPU_WEG_INTEWWUPT_DEC_SWICE_INT		BIT(9)
#define     VDPU_WEG_INTEWWUPT_DEC_ASO_INT		BIT(8)
#define     VDPU_WEG_INTEWWUPT_DEC_BUFFEW_INT		BIT(6)
#define     VDPU_WEG_INTEWWUPT_DEC_BUS_INT		BIT(5)
#define     VDPU_WEG_INTEWWUPT_DEC_WDY_INT		BIT(4)
#define     VDPU_WEG_INTEWWUPT_DEC_IWQ_DIS		BIT(1)
#define     VDPU_WEG_INTEWWUPT_DEC_IWQ			BIT(0)
#define VDPU_WEG_AXI_CTWW			0x0e0
#define     VDPU_WEG_AXI_DEC_SEW			BIT(23)
#define     VDPU_WEG_CONFIG_DEC_DATA_DISC_E		BIT(22)
#define     VDPU_WEG_PAWAW_BUS_E(x)			BIT(21)
#define     VDPU_WEG_CONFIG_DEC_MAX_BUWST(x)		(((x) & 0x1f) << 16)
#define     VDPU_WEG_DEC_CTWW0_DEC_AXI_WW_ID(x)		(((x) & 0xff) << 8)
#define     VDPU_WEG_CONFIG_DEC_AXI_WD_ID(x)		(((x) & 0xff) << 0)
#define VDPU_WEG_EN_FWAGS			0x0e4
#define     VDPU_WEG_AHB_HWOCK_E			BIT(31)
#define     VDPU_WEG_CACHE_E				BIT(29)
#define     VDPU_WEG_PWEFETCH_SINGWE_CHANNEW_E		BIT(28)
#define     VDPU_WEG_INTWA_3_CYCWE_ENHANCE		BIT(27)
#define     VDPU_WEG_INTWA_DOUBWE_SPEED			BIT(26)
#define     VDPU_WEG_INTEW_DOUBWE_SPEED			BIT(25)
#define     VDPU_WEG_DEC_CTWW3_STAWT_CODE_E		BIT(22)
#define     VDPU_WEG_DEC_CTWW3_CH_8PIX_IWEAV_E		BIT(21)
#define     VDPU_WEG_DEC_CTWW0_WWC_MODE_E		BIT(20)
#define     VDPU_WEG_DEC_CTWW0_DIVX3_E			BIT(19)
#define     VDPU_WEG_DEC_CTWW0_PJPEG_E			BIT(18)
#define     VDPU_WEG_DEC_CTWW0_PIC_INTEWWACE_E		BIT(17)
#define     VDPU_WEG_DEC_CTWW0_PIC_FIEWDMODE_E		BIT(16)
#define     VDPU_WEG_DEC_CTWW0_PIC_B_E			BIT(15)
#define     VDPU_WEG_DEC_CTWW0_PIC_INTEW_E		BIT(14)
#define     VDPU_WEG_DEC_CTWW0_PIC_TOPFIEWD_E		BIT(13)
#define     VDPU_WEG_DEC_CTWW0_FWD_INTEWWACE_E		BIT(12)
#define     VDPU_WEG_DEC_CTWW0_SOWENSON_E		BIT(11)
#define     VDPU_WEG_DEC_CTWW0_WWITE_MVS_E		BIT(10)
#define     VDPU_WEG_DEC_CTWW0_WEF_TOPFIEWD_E		BIT(9)
#define     VDPU_WEG_DEC_CTWW0_WEFTOPFIWST_E		BIT(8)
#define     VDPU_WEG_DEC_CTWW0_SEQ_MBAFF_E		BIT(7)
#define     VDPU_WEG_DEC_CTWW0_PICOWD_COUNT_E		BIT(6)
#define     VDPU_WEG_CONFIG_DEC_TIMEOUT_E		BIT(5)
#define     VDPU_WEG_CONFIG_DEC_CWK_GATE_E		BIT(4)
#define     VDPU_WEG_DEC_CTWW0_DEC_OUT_DIS		BIT(2)
#define     VDPU_WEG_WEF_BUF_CTWW2_WEFBU2_BUF_E		BIT(1)
#define     VDPU_WEG_INTEWWUPT_DEC_E			BIT(0)
#define VDPU_WEG_SOFT_WESET			0x0e8
#define VDPU_WEG_PWED_FWT			0x0ec
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_0_0(x)	(((x) & 0x3ff) << 22)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_0_1(x)	(((x) & 0x3ff) << 12)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_0_2(x)	(((x) & 0x3ff) << 2)
#define VDPU_WEG_ADDITIONAW_CHWOMA_ADDWESS	0x0f0
#define VDPU_WEG_ADDW_QTABWE			0x0f4
#define VDPU_WEG_DIWECT_MV_ADDW			0x0f8
#define VDPU_WEG_ADDW_DST			0x0fc
#define VDPU_WEG_ADDW_STW			0x100
#define VDPU_WEG_WEFBUF_WEWATED			0x104
#define VDPU_WEG_FWD_PIC(i)			(0x128 + ((i) * 0x4))
#define     VDPU_WEG_FWD_PIC_PINIT_WWIST_F5(x)		(((x) & 0x1f) << 25)
#define     VDPU_WEG_FWD_PIC_PINIT_WWIST_F4(x)		(((x) & 0x1f) << 20)
#define     VDPU_WEG_FWD_PIC_PINIT_WWIST_F3(x)		(((x) & 0x1f) << 15)
#define     VDPU_WEG_FWD_PIC_PINIT_WWIST_F2(x)		(((x) & 0x1f) << 10)
#define     VDPU_WEG_FWD_PIC_PINIT_WWIST_F1(x)		(((x) & 0x1f) << 5)
#define     VDPU_WEG_FWD_PIC_PINIT_WWIST_F0(x)		(((x) & 0x1f) << 0)
#define VDPU_WEG_WEF_PIC(i)			(0x130 + ((i) * 0x4))
#define     VDPU_WEG_WEF_PIC_WEFEW1_NBW(x)		(((x) & 0xffff) << 16)
#define     VDPU_WEG_WEF_PIC_WEFEW0_NBW(x)		(((x) & 0xffff) << 0)
#define VDPU_WEG_H264_ADDW_WEF(i)			(0x150 + ((i) * 0x4))
#define     VDPU_WEG_ADDW_WEF_FIEWD_E			BIT(1)
#define     VDPU_WEG_ADDW_WEF_TOPC_E			BIT(0)
#define VDPU_WEG_INITIAW_WEF_PIC_WIST0		0x190
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F5(x)	(((x) & 0x1f) << 25)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F4(x)	(((x) & 0x1f) << 20)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F3(x)	(((x) & 0x1f) << 15)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F2(x)	(((x) & 0x1f) << 10)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F1(x)	(((x) & 0x1f) << 5)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F0(x)	(((x) & 0x1f) << 0)
#define VDPU_WEG_INITIAW_WEF_PIC_WIST1		0x194
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F11(x)	(((x) & 0x1f) << 25)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F10(x)	(((x) & 0x1f) << 20)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F9(x)	(((x) & 0x1f) << 15)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F8(x)	(((x) & 0x1f) << 10)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F7(x)	(((x) & 0x1f) << 5)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F6(x)	(((x) & 0x1f) << 0)
#define VDPU_WEG_INITIAW_WEF_PIC_WIST2		0x198
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F15(x)	(((x) & 0x1f) << 15)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F14(x)	(((x) & 0x1f) << 10)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F13(x)	(((x) & 0x1f) << 5)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_F12(x)	(((x) & 0x1f) << 0)
#define VDPU_WEG_INITIAW_WEF_PIC_WIST3		0x19c
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B5(x)	(((x) & 0x1f) << 25)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B4(x)	(((x) & 0x1f) << 20)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B3(x)	(((x) & 0x1f) << 15)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B2(x)	(((x) & 0x1f) << 10)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B1(x)	(((x) & 0x1f) << 5)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B0(x)	(((x) & 0x1f) << 0)
#define VDPU_WEG_INITIAW_WEF_PIC_WIST4		0x1a0
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B11(x)	(((x) & 0x1f) << 25)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B10(x)	(((x) & 0x1f) << 20)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B9(x)	(((x) & 0x1f) << 15)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B8(x)	(((x) & 0x1f) << 10)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B7(x)	(((x) & 0x1f) << 5)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B6(x)	(((x) & 0x1f) << 0)
#define VDPU_WEG_INITIAW_WEF_PIC_WIST5		0x1a4
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B15(x)	(((x) & 0x1f) << 15)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B14(x)	(((x) & 0x1f) << 10)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B13(x)	(((x) & 0x1f) << 5)
#define     VDPU_WEG_BD_WEF_PIC_BINIT_WWIST_B12(x)	(((x) & 0x1f) << 0)
#define VDPU_WEG_INITIAW_WEF_PIC_WIST6		0x1a8
#define     VDPU_WEG_BD_P_WEF_PIC_PINIT_WWIST_F3(x)	(((x) & 0x1f) << 15)
#define     VDPU_WEG_BD_P_WEF_PIC_PINIT_WWIST_F2(x)	(((x) & 0x1f) << 10)
#define     VDPU_WEG_BD_P_WEF_PIC_PINIT_WWIST_F1(x)	(((x) & 0x1f) << 5)
#define     VDPU_WEG_BD_P_WEF_PIC_PINIT_WWIST_F0(x)	(((x) & 0x1f) << 0)
#define VDPU_WEG_WT_WEF				0x1ac
#define VDPU_WEG_VAWID_WEF			0x1b0
#define VDPU_WEG_H264_PIC_MB_SIZE		0x1b8
#define     VDPU_WEG_DEC_CTWW2_CH_QP_OFFSET2(x)		(((x) & 0x1f) << 22)
#define     VDPU_WEG_DEC_CTWW2_CH_QP_OFFSET(x)		(((x) & 0x1f) << 17)
#define     VDPU_WEG_DEC_CTWW1_PIC_MB_HEIGHT_P(x)	(((x) & 0xff) << 9)
#define     VDPU_WEG_DEC_CTWW1_PIC_MB_WIDTH(x)		(((x) & 0x1ff) << 0)
#define VDPU_WEG_H264_CTWW			0x1bc
#define     VDPU_WEG_DEC_CTWW4_WEIGHT_BIPW_IDC(x)	(((x) & 0x3) << 16)
#define     VDPU_WEG_DEC_CTWW1_WEF_FWAMES(x)		(((x) & 0x1f) << 0)
#define VDPU_WEG_CUWWENT_FWAME			0x1c0
#define     VDPU_WEG_DEC_CTWW5_FIWT_CTWW_PWES		BIT(31)
#define     VDPU_WEG_DEC_CTWW5_WDPIC_CNT_PWES		BIT(30)
#define     VDPU_WEG_DEC_CTWW4_FWAMENUM_WEN(x)		(((x) & 0x1f) << 16)
#define     VDPU_WEG_DEC_CTWW4_FWAMENUM(x)		(((x) & 0xffff) << 0)
#define VDPU_WEG_WEF_FWAME			0x1c4
#define     VDPU_WEG_DEC_CTWW5_WEFPIC_MK_WEN(x)		(((x) & 0x7ff) << 16)
#define     VDPU_WEG_DEC_CTWW5_IDW_PIC_ID(x)		(((x) & 0xffff) << 0)
#define VDPU_WEG_DEC_CTWW6			0x1c8
#define     VDPU_WEG_DEC_CTWW6_PPS_ID(x)		(((x) & 0xff) << 24)
#define     VDPU_WEG_DEC_CTWW6_WEFIDX1_ACTIVE(x)	(((x) & 0x1f) << 19)
#define     VDPU_WEG_DEC_CTWW6_WEFIDX0_ACTIVE(x)	(((x) & 0x1f) << 14)
#define     VDPU_WEG_DEC_CTWW6_POC_WENGTH(x)		(((x) & 0xff) << 0)
#define VDPU_WEG_ENABWE_FWAG			0x1cc
#define     VDPU_WEG_DEC_CTWW5_IDW_PIC_E		BIT(8)
#define     VDPU_WEG_DEC_CTWW4_DIW_8X8_INFEW_E		BIT(7)
#define     VDPU_WEG_DEC_CTWW4_BWACKWHITE_E		BIT(6)
#define     VDPU_WEG_DEC_CTWW4_CABAC_E			BIT(5)
#define     VDPU_WEG_DEC_CTWW4_WEIGHT_PWED_E		BIT(4)
#define     VDPU_WEG_DEC_CTWW5_CONST_INTWA_E		BIT(3)
#define     VDPU_WEG_DEC_CTWW5_8X8TWANS_FWAG_E		BIT(2)
#define     VDPU_WEG_DEC_CTWW2_TYPE1_QUANT_E		BIT(1)
#define     VDPU_WEG_DEC_CTWW2_FIEWDPIC_FWAG_E		BIT(0)
#define VDPU_WEG_VP8_PIC_MB_SIZE		0x1e0
#define     VDPU_WEG_DEC_PIC_MB_WIDTH(x)		(((x) & 0x1ff) << 23)
#define	    VDPU_WEG_DEC_MB_WIDTH_OFF(x)		(((x) & 0xf) << 19)
#define	    VDPU_WEG_DEC_PIC_MB_HEIGHT_P(x)		(((x) & 0xff) << 11)
#define     VDPU_WEG_DEC_MB_HEIGHT_OFF(x)		(((x) & 0xf) << 7)
#define     VDPU_WEG_DEC_CTWW1_PIC_MB_W_EXT(x)		(((x) & 0x7) << 3)
#define     VDPU_WEG_DEC_CTWW1_PIC_MB_H_EXT(x)		(((x) & 0x7) << 0)
#define VDPU_WEG_VP8_DCT_STAWT_BIT		0x1e4
#define     VDPU_WEG_DEC_CTWW4_DCT1_STAWT_BIT(x)	(((x) & 0x3f) << 26)
#define     VDPU_WEG_DEC_CTWW4_DCT2_STAWT_BIT(x)	(((x) & 0x3f) << 20)
#define     VDPU_WEG_DEC_CTWW4_VC1_HEIGHT_EXT		BIT(13)
#define     VDPU_WEG_DEC_CTWW4_BIWIN_MC_E		BIT(12)
#define VDPU_WEG_VP8_CTWW0			0x1e8
#define     VDPU_WEG_DEC_CTWW2_STWM_STAWT_BIT(x)	(((x) & 0x3f) << 26)
#define     VDPU_WEG_DEC_CTWW2_STWM1_STAWT_BIT(x)	(((x) & 0x3f) << 18)
#define     VDPU_WEG_DEC_CTWW2_BOOWEAN_VAWUE(x)		(((x) & 0xff) << 8)
#define     VDPU_WEG_DEC_CTWW2_BOOWEAN_WANGE(x)		(((x) & 0xff) << 0)
#define VDPU_WEG_VP8_DATA_VAW			0x1f0
#define     VDPU_WEG_DEC_CTWW6_COEFFS_PAWT_AM(x)	(((x) & 0xf) << 24)
#define     VDPU_WEG_DEC_CTWW6_STWEAM1_WEN(x)		(((x) & 0xffffff) << 0)
#define VDPU_WEG_PWED_FWT7			0x1f4
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_5_1(x)	(((x) & 0x3ff) << 22)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_5_2(x)	(((x) & 0x3ff) << 12)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_5_3(x)	(((x) & 0x3ff) << 2)
#define VDPU_WEG_PWED_FWT8			0x1f8
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_6_0(x)	(((x) & 0x3ff) << 22)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_6_1(x)	(((x) & 0x3ff) << 12)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_6_2(x)	(((x) & 0x3ff) << 2)
#define VDPU_WEG_PWED_FWT9			0x1fc
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_6_3(x)	(((x) & 0x3ff) << 22)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_7_0(x)	(((x) & 0x3ff) << 12)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_7_1(x)	(((x) & 0x3ff) << 2)
#define VDPU_WEG_PWED_FWT10			0x200
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_7_2(x)	(((x) & 0x3ff) << 22)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_7_3(x)	(((x) & 0x3ff) << 12)
#define     VDPU_WEG_BD_WEF_PIC_PWED_TAP_2_M1(x)	(((x) & 0x3) << 10)
#define     VDPU_WEG_BD_WEF_PIC_PWED_TAP_2_4(x)		(((x) & 0x3) << 8)
#define     VDPU_WEG_BD_WEF_PIC_PWED_TAP_4_M1(x)	(((x) & 0x3) << 6)
#define     VDPU_WEG_BD_WEF_PIC_PWED_TAP_4_4(x)		(((x) & 0x3) << 4)
#define     VDPU_WEG_BD_WEF_PIC_PWED_TAP_6_M1(x)	(((x) & 0x3) << 2)
#define     VDPU_WEG_BD_WEF_PIC_PWED_TAP_6_4(x)		(((x) & 0x3) << 0)
#define VDPU_WEG_FIWTEW_WEVEW			0x204
#define     VDPU_WEG_WEF_PIC_WF_WEVEW_0(x)		(((x) & 0x3f) << 18)
#define     VDPU_WEG_WEF_PIC_WF_WEVEW_1(x)		(((x) & 0x3f) << 12)
#define     VDPU_WEG_WEF_PIC_WF_WEVEW_2(x)		(((x) & 0x3f) << 6)
#define     VDPU_WEG_WEF_PIC_WF_WEVEW_3(x)		(((x) & 0x3f) << 0)
#define VDPU_WEG_VP8_QUANTEW0			0x208
#define     VDPU_WEG_WEF_PIC_QUANT_DEWTA_0(x)		(((x) & 0x1f) << 27)
#define     VDPU_WEG_WEF_PIC_QUANT_DEWTA_1(x)		(((x) & 0x1f) << 22)
#define     VDPU_WEG_WEF_PIC_QUANT_0(x)			(((x) & 0x7ff) << 11)
#define     VDPU_WEG_WEF_PIC_QUANT_1(x)			(((x) & 0x7ff) << 0)
#define VDPU_WEG_VP8_ADDW_WEF0			0x20c
#define VDPU_WEG_FIWTEW_MB_ADJ			0x210
#define     VDPU_WEG_WEF_PIC_FIWT_TYPE_E		BIT(31)
#define     VDPU_WEG_WEF_PIC_FIWT_SHAWPNESS(x)		(((x) & 0x7) << 28)
#define     VDPU_WEG_FIWT_MB_ADJ_0(x)			(((x) & 0x7f) << 21)
#define     VDPU_WEG_FIWT_MB_ADJ_1(x)			(((x) & 0x7f) << 14)
#define     VDPU_WEG_FIWT_MB_ADJ_2(x)			(((x) & 0x7f) << 7)
#define     VDPU_WEG_FIWT_MB_ADJ_3(x)			(((x) & 0x7f) << 0)
#define VDPU_WEG_FIWTEW_WEF_ADJ			0x214
#define     VDPU_WEG_WEF_PIC_ADJ_0(x)			(((x) & 0x7f) << 21)
#define     VDPU_WEG_WEF_PIC_ADJ_1(x)			(((x) & 0x7f) << 14)
#define     VDPU_WEG_WEF_PIC_ADJ_2(x)			(((x) & 0x7f) << 7)
#define     VDPU_WEG_WEF_PIC_ADJ_3(x)			(((x) & 0x7f) << 0)
#define VDPU_WEG_VP8_ADDW_WEF2_5(i)		(0x218 + ((i) * 0x4))
#define     VDPU_WEG_VP8_GWEF_SIGN_BIAS			BIT(0)
#define     VDPU_WEG_VP8_AWEF_SIGN_BIAS			BIT(0)
#define VDPU_WEG_VP8_DCT_BASE(i)		(0x230 + ((i) * 0x4))
#define VDPU_WEG_VP8_ADDW_CTWW_PAWT		0x244
#define VDPU_WEG_VP8_ADDW_WEF1			0x250
#define VDPU_WEG_VP8_SEGMENT_VAW		0x254
#define     VDPU_WEG_FWD_PIC1_SEGMENT_BASE(x)		((x) << 0)
#define     VDPU_WEG_FWD_PIC1_SEGMENT_UPD_E		BIT(1)
#define     VDPU_WEG_FWD_PIC1_SEGMENT_E			BIT(0)
#define VDPU_WEG_VP8_DCT_STAWT_BIT2		0x258
#define     VDPU_WEG_DEC_CTWW7_DCT3_STAWT_BIT(x)	(((x) & 0x3f) << 24)
#define     VDPU_WEG_DEC_CTWW7_DCT4_STAWT_BIT(x)	(((x) & 0x3f) << 18)
#define     VDPU_WEG_DEC_CTWW7_DCT5_STAWT_BIT(x)	(((x) & 0x3f) << 12)
#define     VDPU_WEG_DEC_CTWW7_DCT6_STAWT_BIT(x)	(((x) & 0x3f) << 6)
#define     VDPU_WEG_DEC_CTWW7_DCT7_STAWT_BIT(x)	(((x) & 0x3f) << 0)
#define VDPU_WEG_VP8_QUANTEW1			0x25c
#define     VDPU_WEG_WEF_PIC_QUANT_DEWTA_2(x)		(((x) & 0x1f) << 27)
#define     VDPU_WEG_WEF_PIC_QUANT_DEWTA_3(x)		(((x) & 0x1f) << 22)
#define     VDPU_WEG_WEF_PIC_QUANT_2(x)			(((x) & 0x7ff) << 11)
#define     VDPU_WEG_WEF_PIC_QUANT_3(x)			(((x) & 0x7ff) << 0)
#define VDPU_WEG_VP8_QUANTEW2			0x260
#define     VDPU_WEG_WEF_PIC_QUANT_DEWTA_4(x)		(((x) & 0x1f) << 27)
#define     VDPU_WEG_WEF_PIC_QUANT_4(x)			(((x) & 0x7ff) << 11)
#define     VDPU_WEG_WEF_PIC_QUANT_5(x)			(((x) & 0x7ff) << 0)
#define VDPU_WEG_PWED_FWT1			0x264
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_0_3(x)	(((x) & 0x3ff) << 22)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_1_0(x)	(((x) & 0x3ff) << 12)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_1_1(x)	(((x) & 0x3ff) << 2)
#define VDPU_WEG_PWED_FWT2			0x268
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_1_2(x)	(((x) & 0x3ff) << 22)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_1_3(x)	(((x) & 0x3ff) << 12)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_2_0(x)	(((x) & 0x3ff) << 2)
#define VDPU_WEG_PWED_FWT3			0x26c
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_2_1(x)	(((x) & 0x3ff) << 22)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_2_2(x)	(((x) & 0x3ff) << 12)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_2_3(x)	(((x) & 0x3ff) << 2)
#define VDPU_WEG_PWED_FWT4			0x270
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_3_0(x)	(((x) & 0x3ff) << 22)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_3_1(x)	(((x) & 0x3ff) << 12)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_3_2(x)	(((x) & 0x3ff) << 2)
#define VDPU_WEG_PWED_FWT5			0x274
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_3_3(x)	(((x) & 0x3ff) << 22)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_4_0(x)	(((x) & 0x3ff) << 12)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_4_1(x)	(((x) & 0x3ff) << 2)
#define VDPU_WEG_PWED_FWT6			0x278
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_4_2(x)	(((x) & 0x3ff) << 22)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_4_3(x)	(((x) & 0x3ff) << 12)
#define     VDPU_WEG_PWED_FWT_PWED_BC_TAP_5_0(x)	(((x) & 0x3ff) << 2)

#endif /* WOCKCHIP_VPU2_WEGS_H_ */
