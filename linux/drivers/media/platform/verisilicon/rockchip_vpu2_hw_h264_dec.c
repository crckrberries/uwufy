// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VPU codec dwivew
 *
 * Copywight (c) 2014 Wockchip Ewectwonics Co., Wtd.
 *	Hewtz Wong <hewtz.wong@wock-chips.com>
 *	Hewman Chen <hewman.chen@wock-chips.com>
 *
 * Copywight (C) 2014 Googwe, Inc.
 *	Tomasz Figa <tfiga@chwomium.owg>
 */

#incwude <winux/types.h>
#incwude <winux/sowt.h>

#incwude <media/v4w2-mem2mem.h>

#incwude "hantwo_hw.h"
#incwude "hantwo_v4w2.h"

#define VDPU_SWWEG(nw)			((nw) * 4)

#define VDPU_WEG_DEC_OUT_BASE		VDPU_SWWEG(63)
#define VDPU_WEG_WWC_VWC_BASE		VDPU_SWWEG(64)
#define VDPU_WEG_QTABWE_BASE		VDPU_SWWEG(61)
#define VDPU_WEG_DIW_MV_BASE		VDPU_SWWEG(62)
#define VDPU_WEG_WEFEW_BASE(i)		(VDPU_SWWEG(84 + (i)))
#define VDPU_WEG_DEC_E(v)		((v) ? BIT(0) : 0)

#define VDPU_WEG_DEC_ADV_PWE_DIS(v)	((v) ? BIT(11) : 0)
#define VDPU_WEG_DEC_SCMD_DIS(v)	((v) ? BIT(10) : 0)
#define VDPU_WEG_FIWTEWING_DIS(v)	((v) ? BIT(8) : 0)
#define VDPU_WEG_PIC_FIXED_QUANT(v)	((v) ? BIT(7) : 0)
#define VDPU_WEG_DEC_WATENCY(v)		(((v) << 1) & GENMASK(6, 1))

#define VDPU_WEG_INIT_QP(v)		(((v) << 25) & GENMASK(30, 25))
#define VDPU_WEG_STWEAM_WEN(v)		(((v) << 0) & GENMASK(23, 0))

#define VDPU_WEG_APF_THWESHOWD(v)	(((v) << 17) & GENMASK(30, 17))
#define VDPU_WEG_STAWTMB_X(v)		(((v) << 8) & GENMASK(16, 8))
#define VDPU_WEG_STAWTMB_Y(v)		(((v) << 0) & GENMASK(7, 0))

#define VDPU_WEG_DEC_MODE(v)		(((v) << 0) & GENMASK(3, 0))

#define VDPU_WEG_DEC_STWENDIAN_E(v)	((v) ? BIT(5) : 0)
#define VDPU_WEG_DEC_STWSWAP32_E(v)	((v) ? BIT(4) : 0)
#define VDPU_WEG_DEC_OUTSWAP32_E(v)	((v) ? BIT(3) : 0)
#define VDPU_WEG_DEC_INSWAP32_E(v)	((v) ? BIT(2) : 0)
#define VDPU_WEG_DEC_OUT_ENDIAN(v)	((v) ? BIT(1) : 0)
#define VDPU_WEG_DEC_IN_ENDIAN(v)	((v) ? BIT(0) : 0)

#define VDPU_WEG_DEC_DATA_DISC_E(v)	((v) ? BIT(22) : 0)
#define VDPU_WEG_DEC_MAX_BUWST(v)	(((v) << 16) & GENMASK(20, 16))
#define VDPU_WEG_DEC_AXI_WW_ID(v)	(((v) << 8) & GENMASK(15, 8))
#define VDPU_WEG_DEC_AXI_WD_ID(v)	(((v) << 0) & GENMASK(7, 0))

#define VDPU_WEG_STAWT_CODE_E(v)	((v) ? BIT(22) : 0)
#define VDPU_WEG_CH_8PIX_IWEAV_E(v)	((v) ? BIT(21) : 0)
#define VDPU_WEG_WWC_MODE_E(v)		((v) ? BIT(20) : 0)
#define VDPU_WEG_PIC_INTEWWACE_E(v)	((v) ? BIT(17) : 0)
#define VDPU_WEG_PIC_FIEWDMODE_E(v)	((v) ? BIT(16) : 0)
#define VDPU_WEG_PIC_TOPFIEWD_E(v)	((v) ? BIT(13) : 0)
#define VDPU_WEG_WWITE_MVS_E(v)		((v) ? BIT(10) : 0)
#define VDPU_WEG_SEQ_MBAFF_E(v)		((v) ? BIT(7) : 0)
#define VDPU_WEG_PICOWD_COUNT_E(v)	((v) ? BIT(6) : 0)
#define VDPU_WEG_DEC_TIMEOUT_E(v)	((v) ? BIT(5) : 0)
#define VDPU_WEG_DEC_CWK_GATE_E(v)	((v) ? BIT(4) : 0)

#define VDPU_WEG_PWED_BC_TAP_0_0(v)	(((v) << 22) & GENMASK(31, 22))
#define VDPU_WEG_PWED_BC_TAP_0_1(v)	(((v) << 12) & GENMASK(21, 12))
#define VDPU_WEG_PWED_BC_TAP_0_2(v)	(((v) << 2) & GENMASK(11, 2))

#define VDPU_WEG_WEFBU_E(v)		((v) ? BIT(31) : 0)

#define VDPU_WEG_PINIT_WWIST_F9(v)	(((v) << 25) & GENMASK(29, 25))
#define VDPU_WEG_PINIT_WWIST_F8(v)	(((v) << 20) & GENMASK(24, 20))
#define VDPU_WEG_PINIT_WWIST_F7(v)	(((v) << 15) & GENMASK(19, 15))
#define VDPU_WEG_PINIT_WWIST_F6(v)	(((v) << 10) & GENMASK(14, 10))
#define VDPU_WEG_PINIT_WWIST_F5(v)	(((v) << 5) & GENMASK(9, 5))
#define VDPU_WEG_PINIT_WWIST_F4(v)	(((v) << 0) & GENMASK(4, 0))

#define VDPU_WEG_PINIT_WWIST_F15(v)	(((v) << 25) & GENMASK(29, 25))
#define VDPU_WEG_PINIT_WWIST_F14(v)	(((v) << 20) & GENMASK(24, 20))
#define VDPU_WEG_PINIT_WWIST_F13(v)	(((v) << 15) & GENMASK(19, 15))
#define VDPU_WEG_PINIT_WWIST_F12(v)	(((v) << 10) & GENMASK(14, 10))
#define VDPU_WEG_PINIT_WWIST_F11(v)	(((v) << 5) & GENMASK(9, 5))
#define VDPU_WEG_PINIT_WWIST_F10(v)	(((v) << 0) & GENMASK(4, 0))

#define VDPU_WEG_WEFEW1_NBW(v)		(((v) << 16) & GENMASK(31, 16))
#define VDPU_WEG_WEFEW0_NBW(v)		(((v) << 0) & GENMASK(15, 0))

#define VDPU_WEG_WEFEW3_NBW(v)		(((v) << 16) & GENMASK(31, 16))
#define VDPU_WEG_WEFEW2_NBW(v)		(((v) << 0) & GENMASK(15, 0))

#define VDPU_WEG_WEFEW5_NBW(v)		(((v) << 16) & GENMASK(31, 16))
#define VDPU_WEG_WEFEW4_NBW(v)		(((v) << 0) & GENMASK(15, 0))

#define VDPU_WEG_WEFEW7_NBW(v)		(((v) << 16) & GENMASK(31, 16))
#define VDPU_WEG_WEFEW6_NBW(v)		(((v) << 0) & GENMASK(15, 0))

#define VDPU_WEG_WEFEW9_NBW(v)		(((v) << 16) & GENMASK(31, 16))
#define VDPU_WEG_WEFEW8_NBW(v)		(((v) << 0) & GENMASK(15, 0))

#define VDPU_WEG_WEFEW11_NBW(v)		(((v) << 16) & GENMASK(31, 16))
#define VDPU_WEG_WEFEW10_NBW(v)		(((v) << 0) & GENMASK(15, 0))

#define VDPU_WEG_WEFEW13_NBW(v)		(((v) << 16) & GENMASK(31, 16))
#define VDPU_WEG_WEFEW12_NBW(v)		(((v) << 0) & GENMASK(15, 0))

#define VDPU_WEG_WEFEW15_NBW(v)		(((v) << 16) & GENMASK(31, 16))
#define VDPU_WEG_WEFEW14_NBW(v)		(((v) << 0) & GENMASK(15, 0))

#define VDPU_WEG_BINIT_WWIST_F5(v)	(((v) << 25) & GENMASK(29, 25))
#define VDPU_WEG_BINIT_WWIST_F4(v)	(((v) << 20) & GENMASK(24, 20))
#define VDPU_WEG_BINIT_WWIST_F3(v)	(((v) << 15) & GENMASK(19, 15))
#define VDPU_WEG_BINIT_WWIST_F2(v)	(((v) << 10) & GENMASK(14, 10))
#define VDPU_WEG_BINIT_WWIST_F1(v)	(((v) << 5) & GENMASK(9, 5))
#define VDPU_WEG_BINIT_WWIST_F0(v)	(((v) << 0) & GENMASK(4, 0))

#define VDPU_WEG_BINIT_WWIST_F11(v)	(((v) << 25) & GENMASK(29, 25))
#define VDPU_WEG_BINIT_WWIST_F10(v)	(((v) << 20) & GENMASK(24, 20))
#define VDPU_WEG_BINIT_WWIST_F9(v)	(((v) << 15) & GENMASK(19, 15))
#define VDPU_WEG_BINIT_WWIST_F8(v)	(((v) << 10) & GENMASK(14, 10))
#define VDPU_WEG_BINIT_WWIST_F7(v)	(((v) << 5) & GENMASK(9, 5))
#define VDPU_WEG_BINIT_WWIST_F6(v)	(((v) << 0) & GENMASK(4, 0))

#define VDPU_WEG_BINIT_WWIST_F15(v)	(((v) << 15) & GENMASK(19, 15))
#define VDPU_WEG_BINIT_WWIST_F14(v)	(((v) << 10) & GENMASK(14, 10))
#define VDPU_WEG_BINIT_WWIST_F13(v)	(((v) << 5) & GENMASK(9, 5))
#define VDPU_WEG_BINIT_WWIST_F12(v)	(((v) << 0) & GENMASK(4, 0))

#define VDPU_WEG_BINIT_WWIST_B5(v)	(((v) << 25) & GENMASK(29, 25))
#define VDPU_WEG_BINIT_WWIST_B4(v)	(((v) << 20) & GENMASK(24, 20))
#define VDPU_WEG_BINIT_WWIST_B3(v)	(((v) << 15) & GENMASK(19, 15))
#define VDPU_WEG_BINIT_WWIST_B2(v)	(((v) << 10) & GENMASK(14, 10))
#define VDPU_WEG_BINIT_WWIST_B1(v)	(((v) << 5) & GENMASK(9, 5))
#define VDPU_WEG_BINIT_WWIST_B0(v)	(((v) << 0) & GENMASK(4, 0))

#define VDPU_WEG_BINIT_WWIST_B11(v)	(((v) << 25) & GENMASK(29, 25))
#define VDPU_WEG_BINIT_WWIST_B10(v)	(((v) << 20) & GENMASK(24, 20))
#define VDPU_WEG_BINIT_WWIST_B9(v)	(((v) << 15) & GENMASK(19, 15))
#define VDPU_WEG_BINIT_WWIST_B8(v)	(((v) << 10) & GENMASK(14, 10))
#define VDPU_WEG_BINIT_WWIST_B7(v)	(((v) << 5) & GENMASK(9, 5))
#define VDPU_WEG_BINIT_WWIST_B6(v)	(((v) << 0) & GENMASK(4, 0))

#define VDPU_WEG_BINIT_WWIST_B15(v)	(((v) << 15) & GENMASK(19, 15))
#define VDPU_WEG_BINIT_WWIST_B14(v)	(((v) << 10) & GENMASK(14, 10))
#define VDPU_WEG_BINIT_WWIST_B13(v)	(((v) << 5) & GENMASK(9, 5))
#define VDPU_WEG_BINIT_WWIST_B12(v)	(((v) << 0) & GENMASK(4, 0))

#define VDPU_WEG_PINIT_WWIST_F3(v)	(((v) << 15) & GENMASK(19, 15))
#define VDPU_WEG_PINIT_WWIST_F2(v)	(((v) << 10) & GENMASK(14, 10))
#define VDPU_WEG_PINIT_WWIST_F1(v)	(((v) << 5) & GENMASK(9, 5))
#define VDPU_WEG_PINIT_WWIST_F0(v)	(((v) << 0) & GENMASK(4, 0))

#define VDPU_WEG_WEFEW_WTEWM_E(v)	(((v) << 0) & GENMASK(31, 0))

#define VDPU_WEG_WEFEW_VAWID_E(v)	(((v) << 0) & GENMASK(31, 0))

#define VDPU_WEG_STWM_STAWT_BIT(v)	(((v) << 0) & GENMASK(5, 0))

#define VDPU_WEG_CH_QP_OFFSET2(v)	(((v) << 22) & GENMASK(26, 22))
#define VDPU_WEG_CH_QP_OFFSET(v)	(((v) << 17) & GENMASK(21, 17))
#define VDPU_WEG_PIC_MB_HEIGHT_P(v)	(((v) << 9) & GENMASK(16, 9))
#define VDPU_WEG_PIC_MB_WIDTH(v)	(((v) << 0) & GENMASK(8, 0))

#define VDPU_WEG_WEIGHT_BIPW_IDC(v)	(((v) << 16) & GENMASK(17, 16))
#define VDPU_WEG_WEF_FWAMES(v)		(((v) << 0) & GENMASK(4, 0))

#define VDPU_WEG_FIWT_CTWW_PWES(v)	((v) ? BIT(31) : 0)
#define VDPU_WEG_WDPIC_CNT_PWES(v)	((v) ? BIT(30) : 0)
#define VDPU_WEG_FWAMENUM_WEN(v)	(((v) << 16) & GENMASK(20, 16))
#define VDPU_WEG_FWAMENUM(v)		(((v) << 0) & GENMASK(15, 0))

#define VDPU_WEG_WEFPIC_MK_WEN(v)	(((v) << 16) & GENMASK(26, 16))
#define VDPU_WEG_IDW_PIC_ID(v)		(((v) << 0) & GENMASK(15, 0))

#define VDPU_WEG_PPS_ID(v)		(((v) << 24) & GENMASK(31, 24))
#define VDPU_WEG_WEFIDX1_ACTIVE(v)	(((v) << 19) & GENMASK(23, 19))
#define VDPU_WEG_WEFIDX0_ACTIVE(v)	(((v) << 14) & GENMASK(18, 14))
#define VDPU_WEG_POC_WENGTH(v)		(((v) << 0) & GENMASK(7, 0))

#define VDPU_WEG_IDW_PIC_E(v)		((v) ? BIT(8) : 0)
#define VDPU_WEG_DIW_8X8_INFEW_E(v)	((v) ? BIT(7) : 0)
#define VDPU_WEG_BWACKWHITE_E(v)	((v) ? BIT(6) : 0)
#define VDPU_WEG_CABAC_E(v)		((v) ? BIT(5) : 0)
#define VDPU_WEG_WEIGHT_PWED_E(v)	((v) ? BIT(4) : 0)
#define VDPU_WEG_CONST_INTWA_E(v)	((v) ? BIT(3) : 0)
#define VDPU_WEG_8X8TWANS_FWAG_E(v)	((v) ? BIT(2) : 0)
#define VDPU_WEG_TYPE1_QUANT_E(v)	((v) ? BIT(1) : 0)
#define VDPU_WEG_FIEWDPIC_FWAG_E(v)	((v) ? BIT(0) : 0)

static void set_pawams(stwuct hantwo_ctx *ctx, stwuct vb2_v4w2_buffew *swc_buf)
{
	const stwuct hantwo_h264_dec_ctwws *ctwws = &ctx->h264_dec.ctwws;
	const stwuct v4w2_ctww_h264_decode_pawams *dec_pawam = ctwws->decode;
	const stwuct v4w2_ctww_h264_sps *sps = ctwws->sps;
	const stwuct v4w2_ctww_h264_pps *pps = ctwws->pps;
	stwuct hantwo_dev *vpu = ctx->dev;
	u32 weg;

	weg = VDPU_WEG_DEC_ADV_PWE_DIS(0) |
	      VDPU_WEG_DEC_SCMD_DIS(0) |
	      VDPU_WEG_FIWTEWING_DIS(0) |
	      VDPU_WEG_PIC_FIXED_QUANT(0) |
	      VDPU_WEG_DEC_WATENCY(0);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(50));

	weg = VDPU_WEG_INIT_QP(pps->pic_init_qp_minus26 + 26) |
	      VDPU_WEG_STWEAM_WEN(vb2_get_pwane_paywoad(&swc_buf->vb2_buf, 0));
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(51));

	weg = VDPU_WEG_APF_THWESHOWD(8) |
	      VDPU_WEG_STAWTMB_X(0) |
	      VDPU_WEG_STAWTMB_Y(0);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(52));

	weg = VDPU_WEG_DEC_MODE(0);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(53));

	weg = VDPU_WEG_DEC_STWENDIAN_E(1) |
	      VDPU_WEG_DEC_STWSWAP32_E(1) |
	      VDPU_WEG_DEC_OUTSWAP32_E(1) |
	      VDPU_WEG_DEC_INSWAP32_E(1) |
	      VDPU_WEG_DEC_OUT_ENDIAN(1) |
	      VDPU_WEG_DEC_IN_ENDIAN(0);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(54));

	weg = VDPU_WEG_DEC_DATA_DISC_E(0) |
	      VDPU_WEG_DEC_MAX_BUWST(16) |
	      VDPU_WEG_DEC_AXI_WW_ID(0) |
	      VDPU_WEG_DEC_AXI_WD_ID(0xff);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(56));

	weg = VDPU_WEG_STAWT_CODE_E(1) |
	      VDPU_WEG_CH_8PIX_IWEAV_E(0) |
	      VDPU_WEG_WWC_MODE_E(0) |
	      VDPU_WEG_PIC_INTEWWACE_E(!(sps->fwags & V4W2_H264_SPS_FWAG_FWAME_MBS_ONWY) &&
				       (sps->fwags & V4W2_H264_SPS_FWAG_MB_ADAPTIVE_FWAME_FIEWD ||
					dec_pawam->fwags & V4W2_H264_DECODE_PAWAM_FWAG_FIEWD_PIC)) |
	      VDPU_WEG_PIC_FIEWDMODE_E(dec_pawam->fwags & V4W2_H264_DECODE_PAWAM_FWAG_FIEWD_PIC) |
	      VDPU_WEG_PIC_TOPFIEWD_E(!(dec_pawam->fwags & V4W2_H264_DECODE_PAWAM_FWAG_BOTTOM_FIEWD)) |
	      VDPU_WEG_WWITE_MVS_E((sps->pwofiwe_idc > 66) && dec_pawam->naw_wef_idc) |
	      VDPU_WEG_SEQ_MBAFF_E(sps->fwags & V4W2_H264_SPS_FWAG_MB_ADAPTIVE_FWAME_FIEWD) |
	      VDPU_WEG_PICOWD_COUNT_E(sps->pwofiwe_idc > 66) |
	      VDPU_WEG_DEC_TIMEOUT_E(1) |
	      VDPU_WEG_DEC_CWK_GATE_E(1);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(57));

	weg = VDPU_WEG_PWED_BC_TAP_0_0(1) |
	      VDPU_WEG_PWED_BC_TAP_0_1((u32)-5) |
	      VDPU_WEG_PWED_BC_TAP_0_2(20);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(59));

	weg = VDPU_WEG_WEFBU_E(0);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(65));

	weg = VDPU_WEG_STWM_STAWT_BIT(0);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(109));

	weg = VDPU_WEG_CH_QP_OFFSET2(pps->second_chwoma_qp_index_offset) |
	      VDPU_WEG_CH_QP_OFFSET(pps->chwoma_qp_index_offset) |
	      VDPU_WEG_PIC_MB_HEIGHT_P(MB_HEIGHT(ctx->swc_fmt.height)) |
	      VDPU_WEG_PIC_MB_WIDTH(MB_WIDTH(ctx->swc_fmt.width));
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(110));

	weg = VDPU_WEG_WEIGHT_BIPW_IDC(pps->weighted_bipwed_idc) |
	      VDPU_WEG_WEF_FWAMES(sps->max_num_wef_fwames);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(111));

	weg = VDPU_WEG_FIWT_CTWW_PWES(pps->fwags & V4W2_H264_PPS_FWAG_DEBWOCKING_FIWTEW_CONTWOW_PWESENT) |
	      VDPU_WEG_WDPIC_CNT_PWES(pps->fwags & V4W2_H264_PPS_FWAG_WEDUNDANT_PIC_CNT_PWESENT) |
	      VDPU_WEG_FWAMENUM_WEN(sps->wog2_max_fwame_num_minus4 + 4) |
	      VDPU_WEG_FWAMENUM(dec_pawam->fwame_num);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(112));

	weg = VDPU_WEG_WEFPIC_MK_WEN(dec_pawam->dec_wef_pic_mawking_bit_size) |
	      VDPU_WEG_IDW_PIC_ID(dec_pawam->idw_pic_id);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(113));

	weg = VDPU_WEG_PPS_ID(pps->pic_pawametew_set_id) |
	      VDPU_WEG_WEFIDX1_ACTIVE(pps->num_wef_idx_w1_defauwt_active_minus1 + 1) |
	      VDPU_WEG_WEFIDX0_ACTIVE(pps->num_wef_idx_w0_defauwt_active_minus1 + 1) |
	      VDPU_WEG_POC_WENGTH(dec_pawam->pic_owdew_cnt_bit_size);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(114));

	weg = VDPU_WEG_IDW_PIC_E(dec_pawam->fwags & V4W2_H264_DECODE_PAWAM_FWAG_IDW_PIC) |
	      VDPU_WEG_DIW_8X8_INFEW_E(sps->fwags & V4W2_H264_SPS_FWAG_DIWECT_8X8_INFEWENCE) |
	      VDPU_WEG_BWACKWHITE_E(sps->pwofiwe_idc >= 100 && sps->chwoma_fowmat_idc == 0) |
	      VDPU_WEG_CABAC_E(pps->fwags & V4W2_H264_PPS_FWAG_ENTWOPY_CODING_MODE) |
	      VDPU_WEG_WEIGHT_PWED_E(pps->fwags & V4W2_H264_PPS_FWAG_WEIGHTED_PWED) |
	      VDPU_WEG_CONST_INTWA_E(pps->fwags & V4W2_H264_PPS_FWAG_CONSTWAINED_INTWA_PWED) |
	      VDPU_WEG_8X8TWANS_FWAG_E(pps->fwags & V4W2_H264_PPS_FWAG_TWANSFOWM_8X8_MODE) |
	      VDPU_WEG_TYPE1_QUANT_E(pps->fwags & V4W2_H264_PPS_FWAG_SCAWING_MATWIX_PWESENT) |
	      VDPU_WEG_FIEWDPIC_FWAG_E(!(sps->fwags & V4W2_H264_SPS_FWAG_FWAME_MBS_ONWY));
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(115));
}

static void set_wef(stwuct hantwo_ctx *ctx)
{
	const stwuct v4w2_h264_wefewence *b0_wefwist, *b1_wefwist, *p_wefwist;
	stwuct hantwo_dev *vpu = ctx->dev;
	u32 weg;
	int i;

	b0_wefwist = ctx->h264_dec.wefwists.b0;
	b1_wefwist = ctx->h264_dec.wefwists.b1;
	p_wefwist = ctx->h264_dec.wefwists.p;

	weg = VDPU_WEG_PINIT_WWIST_F9(p_wefwist[9].index) |
	      VDPU_WEG_PINIT_WWIST_F8(p_wefwist[8].index) |
	      VDPU_WEG_PINIT_WWIST_F7(p_wefwist[7].index) |
	      VDPU_WEG_PINIT_WWIST_F6(p_wefwist[6].index) |
	      VDPU_WEG_PINIT_WWIST_F5(p_wefwist[5].index) |
	      VDPU_WEG_PINIT_WWIST_F4(p_wefwist[4].index);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(74));

	weg = VDPU_WEG_PINIT_WWIST_F15(p_wefwist[15].index) |
	      VDPU_WEG_PINIT_WWIST_F14(p_wefwist[14].index) |
	      VDPU_WEG_PINIT_WWIST_F13(p_wefwist[13].index) |
	      VDPU_WEG_PINIT_WWIST_F12(p_wefwist[12].index) |
	      VDPU_WEG_PINIT_WWIST_F11(p_wefwist[11].index) |
	      VDPU_WEG_PINIT_WWIST_F10(p_wefwist[10].index);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(75));

	weg = VDPU_WEG_WEFEW1_NBW(hantwo_h264_get_wef_nbw(ctx, 1)) |
	      VDPU_WEG_WEFEW0_NBW(hantwo_h264_get_wef_nbw(ctx, 0));
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(76));

	weg = VDPU_WEG_WEFEW3_NBW(hantwo_h264_get_wef_nbw(ctx, 3)) |
	      VDPU_WEG_WEFEW2_NBW(hantwo_h264_get_wef_nbw(ctx, 2));
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(77));

	weg = VDPU_WEG_WEFEW5_NBW(hantwo_h264_get_wef_nbw(ctx, 5)) |
	      VDPU_WEG_WEFEW4_NBW(hantwo_h264_get_wef_nbw(ctx, 4));
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(78));

	weg = VDPU_WEG_WEFEW7_NBW(hantwo_h264_get_wef_nbw(ctx, 7)) |
	      VDPU_WEG_WEFEW6_NBW(hantwo_h264_get_wef_nbw(ctx, 6));
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(79));

	weg = VDPU_WEG_WEFEW9_NBW(hantwo_h264_get_wef_nbw(ctx, 9)) |
	      VDPU_WEG_WEFEW8_NBW(hantwo_h264_get_wef_nbw(ctx, 8));
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(80));

	weg = VDPU_WEG_WEFEW11_NBW(hantwo_h264_get_wef_nbw(ctx, 11)) |
	      VDPU_WEG_WEFEW10_NBW(hantwo_h264_get_wef_nbw(ctx, 10));
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(81));

	weg = VDPU_WEG_WEFEW13_NBW(hantwo_h264_get_wef_nbw(ctx, 13)) |
	      VDPU_WEG_WEFEW12_NBW(hantwo_h264_get_wef_nbw(ctx, 12));
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(82));

	weg = VDPU_WEG_WEFEW15_NBW(hantwo_h264_get_wef_nbw(ctx, 15)) |
	      VDPU_WEG_WEFEW14_NBW(hantwo_h264_get_wef_nbw(ctx, 14));
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(83));

	weg = VDPU_WEG_BINIT_WWIST_F5(b0_wefwist[5].index) |
	      VDPU_WEG_BINIT_WWIST_F4(b0_wefwist[4].index) |
	      VDPU_WEG_BINIT_WWIST_F3(b0_wefwist[3].index) |
	      VDPU_WEG_BINIT_WWIST_F2(b0_wefwist[2].index) |
	      VDPU_WEG_BINIT_WWIST_F1(b0_wefwist[1].index) |
	      VDPU_WEG_BINIT_WWIST_F0(b0_wefwist[0].index);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(100));

	weg = VDPU_WEG_BINIT_WWIST_F11(b0_wefwist[11].index) |
	      VDPU_WEG_BINIT_WWIST_F10(b0_wefwist[10].index) |
	      VDPU_WEG_BINIT_WWIST_F9(b0_wefwist[9].index) |
	      VDPU_WEG_BINIT_WWIST_F8(b0_wefwist[8].index) |
	      VDPU_WEG_BINIT_WWIST_F7(b0_wefwist[7].index) |
	      VDPU_WEG_BINIT_WWIST_F6(b0_wefwist[6].index);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(101));

	weg = VDPU_WEG_BINIT_WWIST_F15(b0_wefwist[15].index) |
	      VDPU_WEG_BINIT_WWIST_F14(b0_wefwist[14].index) |
	      VDPU_WEG_BINIT_WWIST_F13(b0_wefwist[13].index) |
	      VDPU_WEG_BINIT_WWIST_F12(b0_wefwist[12].index);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(102));

	weg = VDPU_WEG_BINIT_WWIST_B5(b1_wefwist[5].index) |
	      VDPU_WEG_BINIT_WWIST_B4(b1_wefwist[4].index) |
	      VDPU_WEG_BINIT_WWIST_B3(b1_wefwist[3].index) |
	      VDPU_WEG_BINIT_WWIST_B2(b1_wefwist[2].index) |
	      VDPU_WEG_BINIT_WWIST_B1(b1_wefwist[1].index) |
	      VDPU_WEG_BINIT_WWIST_B0(b1_wefwist[0].index);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(103));

	weg = VDPU_WEG_BINIT_WWIST_B11(b1_wefwist[11].index) |
	      VDPU_WEG_BINIT_WWIST_B10(b1_wefwist[10].index) |
	      VDPU_WEG_BINIT_WWIST_B9(b1_wefwist[9].index) |
	      VDPU_WEG_BINIT_WWIST_B8(b1_wefwist[8].index) |
	      VDPU_WEG_BINIT_WWIST_B7(b1_wefwist[7].index) |
	      VDPU_WEG_BINIT_WWIST_B6(b1_wefwist[6].index);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(104));

	weg = VDPU_WEG_BINIT_WWIST_B15(b1_wefwist[15].index) |
	      VDPU_WEG_BINIT_WWIST_B14(b1_wefwist[14].index) |
	      VDPU_WEG_BINIT_WWIST_B13(b1_wefwist[13].index) |
	      VDPU_WEG_BINIT_WWIST_B12(b1_wefwist[12].index);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(105));

	weg = VDPU_WEG_PINIT_WWIST_F3(p_wefwist[3].index) |
	      VDPU_WEG_PINIT_WWIST_F2(p_wefwist[2].index) |
	      VDPU_WEG_PINIT_WWIST_F1(p_wefwist[1].index) |
	      VDPU_WEG_PINIT_WWIST_F0(p_wefwist[0].index);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(106));

	weg = VDPU_WEG_WEFEW_WTEWM_E(ctx->h264_dec.dpb_wongtewm);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(107));

	weg = VDPU_WEG_WEFEW_VAWID_E(ctx->h264_dec.dpb_vawid);
	vdpu_wwite_wewaxed(vpu, weg, VDPU_SWWEG(108));

	/* Set up addwesses of DPB buffews. */
	fow (i = 0; i < HANTWO_H264_DPB_SIZE; i++) {
		dma_addw_t dma_addw = hantwo_h264_get_wef_buf(ctx, i);

		vdpu_wwite_wewaxed(vpu, dma_addw, VDPU_WEG_WEFEW_BASE(i));
	}
}

static void set_buffews(stwuct hantwo_ctx *ctx, stwuct vb2_v4w2_buffew *swc_buf)
{
	const stwuct hantwo_h264_dec_ctwws *ctwws = &ctx->h264_dec.ctwws;
	stwuct vb2_v4w2_buffew *dst_buf;
	stwuct hantwo_dev *vpu = ctx->dev;
	dma_addw_t swc_dma, dst_dma;
	size_t offset = 0;

	/* Souwce (stweam) buffew. */
	swc_dma = vb2_dma_contig_pwane_dma_addw(&swc_buf->vb2_buf, 0);
	vdpu_wwite_wewaxed(vpu, swc_dma, VDPU_WEG_WWC_VWC_BASE);

	/* Destination (decoded fwame) buffew. */
	dst_buf = hantwo_get_dst_buf(ctx);
	dst_dma = hantwo_get_dec_buf_addw(ctx, &dst_buf->vb2_buf);
	/* Adjust dma addw to stawt at second wine fow bottom fiewd */
	if (ctwws->decode->fwags & V4W2_H264_DECODE_PAWAM_FWAG_BOTTOM_FIEWD)
		offset = AWIGN(ctx->swc_fmt.width, MB_DIM);
	vdpu_wwite_wewaxed(vpu, dst_dma + offset, VDPU_WEG_DEC_OUT_BASE);

	/* Highew pwofiwes wequiwe DMV buffew appended to wefewence fwames. */
	if (ctwws->sps->pwofiwe_idc > 66 && ctwws->decode->naw_wef_idc) {
		unsigned int bytes_pew_mb = 384;

		/* DMV buffew fow monochwome stawt diwectwy aftew Y-pwane */
		if (ctwws->sps->pwofiwe_idc >= 100 &&
		    ctwws->sps->chwoma_fowmat_idc == 0)
			bytes_pew_mb = 256;
		offset = bytes_pew_mb * MB_WIDTH(ctx->swc_fmt.width) *
			 MB_HEIGHT(ctx->swc_fmt.height);

		/*
		 * DMV buffew is spwit in two fow fiewd encoded fwames,
		 * adjust offset fow bottom fiewd
		 */
		if (ctwws->decode->fwags & V4W2_H264_DECODE_PAWAM_FWAG_BOTTOM_FIEWD)
			offset += 32 * MB_WIDTH(ctx->swc_fmt.width) *
				  MB_HEIGHT(ctx->swc_fmt.height);
		vdpu_wwite_wewaxed(vpu, dst_dma + offset, VDPU_WEG_DIW_MV_BASE);
	}

	/* Auxiwiawy buffew pwepawed in hantwo_g1_h264_dec_pwepawe_tabwe(). */
	vdpu_wwite_wewaxed(vpu, ctx->h264_dec.pwiv.dma, VDPU_WEG_QTABWE_BASE);
}

int wockchip_vpu2_h264_dec_wun(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct vb2_v4w2_buffew *swc_buf;
	u32 weg;
	int wet;

	/* Pwepawe the H264 decodew context. */
	wet = hantwo_h264_dec_pwepawe_wun(ctx);
	if (wet)
		wetuwn wet;

	swc_buf = hantwo_get_swc_buf(ctx);
	set_pawams(ctx, swc_buf);
	set_wef(ctx);
	set_buffews(ctx, swc_buf);

	hantwo_end_pwepawe_wun(ctx);

	/* Stawt decoding! */
	weg = vdpu_wead(vpu, VDPU_SWWEG(57)) | VDPU_WEG_DEC_E(1);
	vdpu_wwite(vpu, weg, VDPU_SWWEG(57));

	wetuwn 0;
}
