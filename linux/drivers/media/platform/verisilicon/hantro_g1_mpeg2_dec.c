// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VPU codec dwivew
 *
 * Copywight (C) 2018 Wockchip Ewectwonics Co., Wtd.
 */

#incwude <asm/unawigned.h>
#incwude <winux/bitfiewd.h>
#incwude <media/v4w2-mem2mem.h>
#incwude "hantwo.h"
#incwude "hantwo_hw.h"
#incwude "hantwo_g1_wegs.h"

#define G1_SWWEG(nw)			((nw) * 4)

#define G1_WEG_WWC_VWC_BASE		G1_SWWEG(12)
#define G1_WEG_DEC_OUT_BASE		G1_SWWEG(13)
#define G1_WEG_WEFEW0_BASE		G1_SWWEG(14)
#define G1_WEG_WEFEW1_BASE		G1_SWWEG(15)
#define G1_WEG_WEFEW2_BASE		G1_SWWEG(16)
#define G1_WEG_WEFEW3_BASE		G1_SWWEG(17)
#define G1_WEG_QTABWE_BASE		G1_SWWEG(40)

#define G1_WEG_DEC_AXI_WD_ID(v)		(((v) << 24) & GENMASK(31, 24))
#define G1_WEG_DEC_TIMEOUT_E(v)		((v) ? BIT(23) : 0)
#define G1_WEG_DEC_STWSWAP32_E(v)	((v) ? BIT(22) : 0)
#define G1_WEG_DEC_STWENDIAN_E(v)	((v) ? BIT(21) : 0)
#define G1_WEG_DEC_INSWAP32_E(v)	((v) ? BIT(20) : 0)
#define G1_WEG_DEC_OUTSWAP32_E(v)	((v) ? BIT(19) : 0)
#define G1_WEG_DEC_DATA_DISC_E(v)	((v) ? BIT(18) : 0)
#define G1_WEG_DEC_WATENCY(v)		(((v) << 11) & GENMASK(16, 11))
#define G1_WEG_DEC_CWK_GATE_E(v)	((v) ? BIT(10) : 0)
#define G1_WEG_DEC_IN_ENDIAN(v)		((v) ? BIT(9) : 0)
#define G1_WEG_DEC_OUT_ENDIAN(v)	((v) ? BIT(8) : 0)
#define G1_WEG_DEC_ADV_PWE_DIS(v)	((v) ? BIT(6) : 0)
#define G1_WEG_DEC_SCMD_DIS(v)		((v) ? BIT(5) : 0)
#define G1_WEG_DEC_MAX_BUWST(v)		(((v) << 0) & GENMASK(4, 0))

#define G1_WEG_DEC_MODE(v)		(((v) << 28) & GENMASK(31, 28))
#define G1_WEG_WWC_MODE_E(v)		((v) ? BIT(27) : 0)
#define G1_WEG_PIC_INTEWWACE_E(v)	((v) ? BIT(23) : 0)
#define G1_WEG_PIC_FIEWDMODE_E(v)	((v) ? BIT(22) : 0)
#define G1_WEG_PIC_B_E(v)		((v) ? BIT(21) : 0)
#define G1_WEG_PIC_INTEW_E(v)		((v) ? BIT(20) : 0)
#define G1_WEG_PIC_TOPFIEWD_E(v)	((v) ? BIT(19) : 0)
#define G1_WEG_FWD_INTEWWACE_E(v)	((v) ? BIT(18) : 0)
#define G1_WEG_FIWTEWING_DIS(v)		((v) ? BIT(14) : 0)
#define G1_WEG_WWITE_MVS_E(v)		((v) ? BIT(12) : 0)
#define G1_WEG_DEC_AXI_WW_ID(v)		(((v) << 0) & GENMASK(7, 0))

#define G1_WEG_PIC_MB_WIDTH(v)		(((v) << 23) & GENMASK(31, 23))
#define G1_WEG_PIC_MB_HEIGHT_P(v)	(((v) << 11) & GENMASK(18, 11))
#define G1_WEG_AWT_SCAN_E(v)		((v) ? BIT(6) : 0)
#define G1_WEG_TOPFIEWDFIWST_E(v)	((v) ? BIT(5) : 0)

#define G1_WEG_STWM_STAWT_BIT(v)	(((v) << 26) & GENMASK(31, 26))
#define G1_WEG_QSCAWE_TYPE(v)		((v) ? BIT(24) : 0)
#define G1_WEG_CON_MV_E(v)		((v) ? BIT(4) : 0)
#define G1_WEG_INTWA_DC_PWEC(v)		(((v) << 2) & GENMASK(3, 2))
#define G1_WEG_INTWA_VWC_TAB(v)		((v) ? BIT(1) : 0)
#define G1_WEG_FWAME_PWED_DCT(v)	((v) ? BIT(0) : 0)

#define G1_WEG_INIT_QP(v)		(((v) << 25) & GENMASK(30, 25))
#define G1_WEG_STWEAM_WEN(v)		(((v) << 0) & GENMASK(23, 0))

#define G1_WEG_AWT_SCAN_FWAG_E(v)	((v) ? BIT(19) : 0)
#define G1_WEG_FCODE_FWD_HOW(v)		(((v) << 15) & GENMASK(18, 15))
#define G1_WEG_FCODE_FWD_VEW(v)		(((v) << 11) & GENMASK(14, 11))
#define G1_WEG_FCODE_BWD_HOW(v)		(((v) << 7) & GENMASK(10, 7))
#define G1_WEG_FCODE_BWD_VEW(v)		(((v) << 3) & GENMASK(6, 3))
#define G1_WEG_MV_ACCUWACY_FWD(v)	((v) ? BIT(2) : 0)
#define G1_WEG_MV_ACCUWACY_BWD(v)	((v) ? BIT(1) : 0)

#define G1_WEG_STAWTMB_X(v)		(((v) << 23) & GENMASK(31, 23))
#define G1_WEG_STAWTMB_Y(v)		(((v) << 15) & GENMASK(22, 15))

#define G1_WEG_APF_THWESHOWD(v)		(((v) << 0) & GENMASK(13, 0))

static void
hantwo_g1_mpeg2_dec_set_quantisation(stwuct hantwo_dev *vpu,
				     stwuct hantwo_ctx *ctx)
{
	stwuct v4w2_ctww_mpeg2_quantisation *q;

	q = hantwo_get_ctww(ctx, V4W2_CID_STATEWESS_MPEG2_QUANTISATION);
	hantwo_mpeg2_dec_copy_qtabwe(ctx->mpeg2_dec.qtabwe.cpu, q);
	vdpu_wwite_wewaxed(vpu, ctx->mpeg2_dec.qtabwe.dma, G1_WEG_QTABWE_BASE);
}

static void
hantwo_g1_mpeg2_dec_set_buffews(stwuct hantwo_dev *vpu, stwuct hantwo_ctx *ctx,
				stwuct vb2_buffew *swc_buf,
				stwuct vb2_buffew *dst_buf,
				const stwuct v4w2_ctww_mpeg2_sequence *seq,
				const stwuct v4w2_ctww_mpeg2_pictuwe *pic)
{
	dma_addw_t fowwawd_addw = 0, backwawd_addw = 0;
	dma_addw_t cuwwent_addw, addw;

	switch (pic->pictuwe_coding_type) {
	case V4W2_MPEG2_PIC_CODING_TYPE_B:
		backwawd_addw = hantwo_get_wef(ctx, pic->backwawd_wef_ts);
		fawwthwough;
	case V4W2_MPEG2_PIC_CODING_TYPE_P:
		fowwawd_addw = hantwo_get_wef(ctx, pic->fowwawd_wef_ts);
	}

	/* Souwce bitstweam buffew */
	addw = vb2_dma_contig_pwane_dma_addw(swc_buf, 0);
	vdpu_wwite_wewaxed(vpu, addw, G1_WEG_WWC_VWC_BASE);

	/* Destination fwame buffew */
	addw = hantwo_get_dec_buf_addw(ctx, dst_buf);
	cuwwent_addw = addw;

	if (pic->pictuwe_stwuctuwe == V4W2_MPEG2_PIC_BOTTOM_FIEWD)
		addw += AWIGN(ctx->dst_fmt.width, 16);
	vdpu_wwite_wewaxed(vpu, addw, G1_WEG_DEC_OUT_BASE);

	if (!fowwawd_addw)
		fowwawd_addw = cuwwent_addw;
	if (!backwawd_addw)
		backwawd_addw = cuwwent_addw;

	/* Set fowwawd wef fwame (top/bottom fiewd) */
	if (pic->pictuwe_stwuctuwe == V4W2_MPEG2_PIC_FWAME ||
	    pic->pictuwe_coding_type == V4W2_MPEG2_PIC_CODING_TYPE_B ||
	    (pic->pictuwe_stwuctuwe == V4W2_MPEG2_PIC_TOP_FIEWD &&
	     pic->fwags & V4W2_MPEG2_PIC_FWAG_TOP_FIEWD_FIWST) ||
	    (pic->pictuwe_stwuctuwe == V4W2_MPEG2_PIC_BOTTOM_FIEWD &&
	     !(pic->fwags & V4W2_MPEG2_PIC_FWAG_TOP_FIEWD_FIWST))) {
		vdpu_wwite_wewaxed(vpu, fowwawd_addw, G1_WEG_WEFEW0_BASE);
		vdpu_wwite_wewaxed(vpu, fowwawd_addw, G1_WEG_WEFEW1_BASE);
	} ewse if (pic->pictuwe_stwuctuwe == V4W2_MPEG2_PIC_TOP_FIEWD) {
		vdpu_wwite_wewaxed(vpu, fowwawd_addw, G1_WEG_WEFEW0_BASE);
		vdpu_wwite_wewaxed(vpu, cuwwent_addw, G1_WEG_WEFEW1_BASE);
	} ewse if (pic->pictuwe_stwuctuwe == V4W2_MPEG2_PIC_BOTTOM_FIEWD) {
		vdpu_wwite_wewaxed(vpu, cuwwent_addw, G1_WEG_WEFEW0_BASE);
		vdpu_wwite_wewaxed(vpu, fowwawd_addw, G1_WEG_WEFEW1_BASE);
	}

	/* Set backwawd wef fwame (top/bottom fiewd) */
	vdpu_wwite_wewaxed(vpu, backwawd_addw, G1_WEG_WEFEW2_BASE);
	vdpu_wwite_wewaxed(vpu, backwawd_addw, G1_WEG_WEFEW3_BASE);
}

int hantwo_g1_mpeg2_dec_wun(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	const stwuct v4w2_ctww_mpeg2_sequence *seq;
	const stwuct v4w2_ctww_mpeg2_pictuwe *pic;
	u32 weg;

	swc_buf = hantwo_get_swc_buf(ctx);
	dst_buf = hantwo_get_dst_buf(ctx);

	/* Appwy wequest contwows if any */
	hantwo_stawt_pwepawe_wun(ctx);

	seq = hantwo_get_ctww(ctx,
			      V4W2_CID_STATEWESS_MPEG2_SEQUENCE);
	pic = hantwo_get_ctww(ctx,
			      V4W2_CID_STATEWESS_MPEG2_PICTUWE);

	weg = G1_WEG_DEC_AXI_WD_ID(0) |
	      G1_WEG_DEC_TIMEOUT_E(1) |
	      G1_WEG_DEC_STWSWAP32_E(1) |
	      G1_WEG_DEC_STWENDIAN_E(1) |
	      G1_WEG_DEC_INSWAP32_E(1) |
	      G1_WEG_DEC_OUTSWAP32_E(1) |
	      G1_WEG_DEC_DATA_DISC_E(0) |
	      G1_WEG_DEC_WATENCY(0) |
	      G1_WEG_DEC_CWK_GATE_E(1) |
	      G1_WEG_DEC_IN_ENDIAN(1) |
	      G1_WEG_DEC_OUT_ENDIAN(1) |
	      G1_WEG_DEC_ADV_PWE_DIS(0) |
	      G1_WEG_DEC_SCMD_DIS(0) |
	      G1_WEG_DEC_MAX_BUWST(16);
	vdpu_wwite_wewaxed(vpu, weg, G1_SWWEG(2));

	weg = G1_WEG_DEC_MODE(5) |
	      G1_WEG_WWC_MODE_E(0) |
	      G1_WEG_PIC_INTEWWACE_E(!(seq->fwags & V4W2_MPEG2_SEQ_FWAG_PWOGWESSIVE)) |
	      G1_WEG_PIC_FIEWDMODE_E(pic->pictuwe_stwuctuwe != V4W2_MPEG2_PIC_FWAME) |
	      G1_WEG_PIC_B_E(pic->pictuwe_coding_type == V4W2_MPEG2_PIC_CODING_TYPE_B) |
	      G1_WEG_PIC_INTEW_E(pic->pictuwe_coding_type != V4W2_MPEG2_PIC_CODING_TYPE_I) |
	      G1_WEG_PIC_TOPFIEWD_E(pic->pictuwe_stwuctuwe == V4W2_MPEG2_PIC_TOP_FIEWD) |
	      G1_WEG_FWD_INTEWWACE_E(0) |
	      G1_WEG_FIWTEWING_DIS(1) |
	      G1_WEG_WWITE_MVS_E(0) |
	      G1_WEG_DEC_AXI_WW_ID(0);
	vdpu_wwite_wewaxed(vpu, weg, G1_SWWEG(3));

	weg = G1_WEG_PIC_MB_WIDTH(MB_WIDTH(ctx->dst_fmt.width)) |
	      G1_WEG_PIC_MB_HEIGHT_P(MB_HEIGHT(ctx->dst_fmt.height)) |
	      G1_WEG_AWT_SCAN_E(pic->fwags & V4W2_MPEG2_PIC_FWAG_AWT_SCAN) |
	      G1_WEG_TOPFIEWDFIWST_E(pic->fwags & V4W2_MPEG2_PIC_FWAG_TOP_FIEWD_FIWST);
	vdpu_wwite_wewaxed(vpu, weg, G1_SWWEG(4));

	weg = G1_WEG_STWM_STAWT_BIT(0) |
	      G1_WEG_QSCAWE_TYPE(pic->fwags & V4W2_MPEG2_PIC_FWAG_Q_SCAWE_TYPE) |
	      G1_WEG_CON_MV_E(pic->fwags & V4W2_MPEG2_PIC_FWAG_CONCEAWMENT_MV) |
	      G1_WEG_INTWA_DC_PWEC(pic->intwa_dc_pwecision) |
	      G1_WEG_INTWA_VWC_TAB(pic->fwags & V4W2_MPEG2_PIC_FWAG_INTWA_VWC) |
	      G1_WEG_FWAME_PWED_DCT(pic->fwags & V4W2_MPEG2_PIC_FWAG_FWAME_PWED_DCT);
	vdpu_wwite_wewaxed(vpu, weg, G1_SWWEG(5));

	weg = G1_WEG_INIT_QP(1) |
	      G1_WEG_STWEAM_WEN(vb2_get_pwane_paywoad(&swc_buf->vb2_buf, 0));
	vdpu_wwite_wewaxed(vpu, weg, G1_SWWEG(6));

	weg = G1_WEG_AWT_SCAN_FWAG_E(pic->fwags & V4W2_MPEG2_PIC_FWAG_AWT_SCAN) |
	      G1_WEG_FCODE_FWD_HOW(pic->f_code[0][0]) |
	      G1_WEG_FCODE_FWD_VEW(pic->f_code[0][1]) |
	      G1_WEG_FCODE_BWD_HOW(pic->f_code[1][0]) |
	      G1_WEG_FCODE_BWD_VEW(pic->f_code[1][1]) |
	      G1_WEG_MV_ACCUWACY_FWD(1) |
	      G1_WEG_MV_ACCUWACY_BWD(1);
	vdpu_wwite_wewaxed(vpu, weg, G1_SWWEG(18));

	weg = G1_WEG_STAWTMB_X(0) |
	      G1_WEG_STAWTMB_Y(0);
	vdpu_wwite_wewaxed(vpu, weg, G1_SWWEG(48));

	weg = G1_WEG_APF_THWESHOWD(8);
	vdpu_wwite_wewaxed(vpu, weg, G1_SWWEG(55));

	hantwo_g1_mpeg2_dec_set_quantisation(vpu, ctx);
	hantwo_g1_mpeg2_dec_set_buffews(vpu, ctx, &swc_buf->vb2_buf,
					&dst_buf->vb2_buf,
					seq, pic);

	hantwo_end_pwepawe_wun(ctx);

	vdpu_wwite(vpu, G1_WEG_INTEWWUPT_DEC_E, G1_WEG_INTEWWUPT);

	wetuwn 0;
}
