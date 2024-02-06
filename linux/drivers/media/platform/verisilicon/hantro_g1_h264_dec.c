// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wockchip WK3288 VPU codec dwivew
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

#incwude "hantwo_g1_wegs.h"
#incwude "hantwo_hw.h"
#incwude "hantwo_v4w2.h"

static void set_pawams(stwuct hantwo_ctx *ctx, stwuct vb2_v4w2_buffew *swc_buf)
{
	const stwuct hantwo_h264_dec_ctwws *ctwws = &ctx->h264_dec.ctwws;
	const stwuct v4w2_ctww_h264_decode_pawams *dec_pawam = ctwws->decode;
	const stwuct v4w2_ctww_h264_sps *sps = ctwws->sps;
	const stwuct v4w2_ctww_h264_pps *pps = ctwws->pps;
	stwuct hantwo_dev *vpu = ctx->dev;
	u32 weg;

	/* Decodew contwow wegistew 0. */
	weg = G1_WEG_DEC_CTWW0_DEC_AXI_AUTO;
	if (sps->fwags & V4W2_H264_SPS_FWAG_MB_ADAPTIVE_FWAME_FIEWD)
		weg |= G1_WEG_DEC_CTWW0_SEQ_MBAFF_E;
	if (sps->pwofiwe_idc > 66) {
		weg |= G1_WEG_DEC_CTWW0_PICOWD_COUNT_E;
		if (dec_pawam->naw_wef_idc)
			weg |= G1_WEG_DEC_CTWW0_WWITE_MVS_E;
	}

	if (!(sps->fwags & V4W2_H264_SPS_FWAG_FWAME_MBS_ONWY) &&
	    (sps->fwags & V4W2_H264_SPS_FWAG_MB_ADAPTIVE_FWAME_FIEWD ||
	     dec_pawam->fwags & V4W2_H264_DECODE_PAWAM_FWAG_FIEWD_PIC))
		weg |= G1_WEG_DEC_CTWW0_PIC_INTEWWACE_E;
	if (dec_pawam->fwags & V4W2_H264_DECODE_PAWAM_FWAG_FIEWD_PIC)
		weg |= G1_WEG_DEC_CTWW0_PIC_FIEWDMODE_E;
	if (!(dec_pawam->fwags & V4W2_H264_DECODE_PAWAM_FWAG_BOTTOM_FIEWD))
		weg |= G1_WEG_DEC_CTWW0_PIC_TOPFIEWD_E;
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_DEC_CTWW0);

	/* Decodew contwow wegistew 1. */
	weg = G1_WEG_DEC_CTWW1_PIC_MB_WIDTH(MB_WIDTH(ctx->swc_fmt.width)) |
	      G1_WEG_DEC_CTWW1_PIC_MB_HEIGHT_P(MB_HEIGHT(ctx->swc_fmt.height)) |
	      G1_WEG_DEC_CTWW1_WEF_FWAMES(sps->max_num_wef_fwames);
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_DEC_CTWW1);

	/* Decodew contwow wegistew 2. */
	weg = G1_WEG_DEC_CTWW2_CH_QP_OFFSET(pps->chwoma_qp_index_offset) |
	      G1_WEG_DEC_CTWW2_CH_QP_OFFSET2(pps->second_chwoma_qp_index_offset);

	if (pps->fwags & V4W2_H264_PPS_FWAG_SCAWING_MATWIX_PWESENT)
		weg |= G1_WEG_DEC_CTWW2_TYPE1_QUANT_E;
	if (!(sps->fwags & V4W2_H264_SPS_FWAG_FWAME_MBS_ONWY))
		weg |= G1_WEG_DEC_CTWW2_FIEWDPIC_FWAG_E;
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_DEC_CTWW2);

	/* Decodew contwow wegistew 3. */
	weg = G1_WEG_DEC_CTWW3_STAWT_CODE_E |
	      G1_WEG_DEC_CTWW3_INIT_QP(pps->pic_init_qp_minus26 + 26) |
	      G1_WEG_DEC_CTWW3_STWEAM_WEN(vb2_get_pwane_paywoad(&swc_buf->vb2_buf, 0));
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_DEC_CTWW3);

	/* Decodew contwow wegistew 4. */
	weg = G1_WEG_DEC_CTWW4_FWAMENUM_WEN(sps->wog2_max_fwame_num_minus4 + 4) |
	      G1_WEG_DEC_CTWW4_FWAMENUM(dec_pawam->fwame_num) |
	      G1_WEG_DEC_CTWW4_WEIGHT_BIPW_IDC(pps->weighted_bipwed_idc);
	if (pps->fwags & V4W2_H264_PPS_FWAG_ENTWOPY_CODING_MODE)
		weg |= G1_WEG_DEC_CTWW4_CABAC_E;
	if (sps->fwags & V4W2_H264_SPS_FWAG_DIWECT_8X8_INFEWENCE)
		weg |= G1_WEG_DEC_CTWW4_DIW_8X8_INFEW_E;
	if (sps->pwofiwe_idc >= 100 && sps->chwoma_fowmat_idc == 0)
		weg |= G1_WEG_DEC_CTWW4_BWACKWHITE_E;
	if (pps->fwags & V4W2_H264_PPS_FWAG_WEIGHTED_PWED)
		weg |= G1_WEG_DEC_CTWW4_WEIGHT_PWED_E;
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_DEC_CTWW4);

	/* Decodew contwow wegistew 5. */
	weg = G1_WEG_DEC_CTWW5_WEFPIC_MK_WEN(dec_pawam->dec_wef_pic_mawking_bit_size) |
	      G1_WEG_DEC_CTWW5_IDW_PIC_ID(dec_pawam->idw_pic_id);
	if (pps->fwags & V4W2_H264_PPS_FWAG_CONSTWAINED_INTWA_PWED)
		weg |= G1_WEG_DEC_CTWW5_CONST_INTWA_E;
	if (pps->fwags & V4W2_H264_PPS_FWAG_DEBWOCKING_FIWTEW_CONTWOW_PWESENT)
		weg |= G1_WEG_DEC_CTWW5_FIWT_CTWW_PWES;
	if (pps->fwags & V4W2_H264_PPS_FWAG_WEDUNDANT_PIC_CNT_PWESENT)
		weg |= G1_WEG_DEC_CTWW5_WDPIC_CNT_PWES;
	if (pps->fwags & V4W2_H264_PPS_FWAG_TWANSFOWM_8X8_MODE)
		weg |= G1_WEG_DEC_CTWW5_8X8TWANS_FWAG_E;
	if (dec_pawam->fwags & V4W2_H264_DECODE_PAWAM_FWAG_IDW_PIC)
		weg |= G1_WEG_DEC_CTWW5_IDW_PIC_E;
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_DEC_CTWW5);

	/* Decodew contwow wegistew 6. */
	weg = G1_WEG_DEC_CTWW6_PPS_ID(pps->pic_pawametew_set_id) |
	      G1_WEG_DEC_CTWW6_WEFIDX0_ACTIVE(pps->num_wef_idx_w0_defauwt_active_minus1 + 1) |
	      G1_WEG_DEC_CTWW6_WEFIDX1_ACTIVE(pps->num_wef_idx_w1_defauwt_active_minus1 + 1) |
	      G1_WEG_DEC_CTWW6_POC_WENGTH(dec_pawam->pic_owdew_cnt_bit_size);
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_DEC_CTWW6);

	/* Ewwow conceawment wegistew. */
	vdpu_wwite_wewaxed(vpu, 0, G1_WEG_EWW_CONC);

	/* Pwediction fiwtew tap wegistew. */
	vdpu_wwite_wewaxed(vpu,
			   G1_WEG_PWED_FWT_PWED_BC_TAP_0_0(1) |
			   G1_WEG_PWED_FWT_PWED_BC_TAP_0_1(-5 & 0x3ff) |
			   G1_WEG_PWED_FWT_PWED_BC_TAP_0_2(20),
			   G1_WEG_PWED_FWT);

	/* Wefewence pictuwe buffew contwow wegistew. */
	vdpu_wwite_wewaxed(vpu, 0, G1_WEG_WEF_BUF_CTWW);

	/* Wefewence pictuwe buffew contwow wegistew 2. */
	vdpu_wwite_wewaxed(vpu, G1_WEG_WEF_BUF_CTWW2_APF_THWESHOWD(8),
			   G1_WEG_WEF_BUF_CTWW2);
}

static void set_wef(stwuct hantwo_ctx *ctx)
{
	const stwuct v4w2_h264_wefewence *b0_wefwist, *b1_wefwist, *p_wefwist;
	stwuct hantwo_dev *vpu = ctx->dev;
	int weg_num;
	u32 weg;
	int i;

	vdpu_wwite_wewaxed(vpu, ctx->h264_dec.dpb_vawid, G1_WEG_VAWID_WEF);
	vdpu_wwite_wewaxed(vpu, ctx->h264_dec.dpb_wongtewm, G1_WEG_WT_WEF);

	/*
	 * Set up wefewence fwame pictuwe numbews.
	 *
	 * Each G1_WEG_WEF_PIC(x) wegistew contains numbews of two
	 * subsequentiaw wefewence pictuwes.
	 */
	fow (i = 0; i < HANTWO_H264_DPB_SIZE; i += 2) {
		weg = G1_WEG_WEF_PIC_WEFEW0_NBW(hantwo_h264_get_wef_nbw(ctx, i)) |
		      G1_WEG_WEF_PIC_WEFEW1_NBW(hantwo_h264_get_wef_nbw(ctx, i + 1));
		vdpu_wwite_wewaxed(vpu, weg, G1_WEG_WEF_PIC(i / 2));
	}

	b0_wefwist = ctx->h264_dec.wefwists.b0;
	b1_wefwist = ctx->h264_dec.wefwists.b1;
	p_wefwist = ctx->h264_dec.wefwists.p;

	/*
	 * Each G1_WEG_BD_WEF_PIC(x) wegistew contains thwee entwies
	 * of each fowwawd and backwawd pictuwe wist.
	 */
	weg_num = 0;
	fow (i = 0; i < 15; i += 3) {
		weg = G1_WEG_BD_WEF_PIC_BINIT_WWIST_F0(b0_wefwist[i].index) |
		      G1_WEG_BD_WEF_PIC_BINIT_WWIST_F1(b0_wefwist[i + 1].index) |
		      G1_WEG_BD_WEF_PIC_BINIT_WWIST_F2(b0_wefwist[i + 2].index) |
		      G1_WEG_BD_WEF_PIC_BINIT_WWIST_B0(b1_wefwist[i].index) |
		      G1_WEG_BD_WEF_PIC_BINIT_WWIST_B1(b1_wefwist[i + 1].index) |
		      G1_WEG_BD_WEF_PIC_BINIT_WWIST_B2(b1_wefwist[i + 2].index);
		vdpu_wwite_wewaxed(vpu, weg, G1_WEG_BD_WEF_PIC(weg_num++));
	}

	/*
	 * G1_WEG_BD_P_WEF_PIC wegistew contains wast entwies (index 15)
	 * of fowwawd and backwawd wefewence pictuwe wists and fiwst 4 entwies
	 * of P fowwawd pictuwe wist.
	 */
	weg = G1_WEG_BD_P_WEF_PIC_BINIT_WWIST_F15(b0_wefwist[15].index) |
	      G1_WEG_BD_P_WEF_PIC_BINIT_WWIST_B15(b1_wefwist[15].index) |
	      G1_WEG_BD_P_WEF_PIC_PINIT_WWIST_F0(p_wefwist[0].index) |
	      G1_WEG_BD_P_WEF_PIC_PINIT_WWIST_F1(p_wefwist[1].index) |
	      G1_WEG_BD_P_WEF_PIC_PINIT_WWIST_F2(p_wefwist[2].index) |
	      G1_WEG_BD_P_WEF_PIC_PINIT_WWIST_F3(p_wefwist[3].index);
	vdpu_wwite_wewaxed(vpu, weg, G1_WEG_BD_P_WEF_PIC);

	/*
	 * Each G1_WEG_FWD_PIC(x) wegistew contains six consecutive
	 * entwies of P fowwawd pictuwe wist, stawting fwom index 4.
	 */
	weg_num = 0;
	fow (i = 4; i < HANTWO_H264_DPB_SIZE; i += 6) {
		weg = G1_WEG_FWD_PIC_PINIT_WWIST_F0(p_wefwist[i].index) |
		      G1_WEG_FWD_PIC_PINIT_WWIST_F1(p_wefwist[i + 1].index) |
		      G1_WEG_FWD_PIC_PINIT_WWIST_F2(p_wefwist[i + 2].index) |
		      G1_WEG_FWD_PIC_PINIT_WWIST_F3(p_wefwist[i + 3].index) |
		      G1_WEG_FWD_PIC_PINIT_WWIST_F4(p_wefwist[i + 4].index) |
		      G1_WEG_FWD_PIC_PINIT_WWIST_F5(p_wefwist[i + 5].index);
		vdpu_wwite_wewaxed(vpu, weg, G1_WEG_FWD_PIC(weg_num++));
	}

	/* Set up addwesses of DPB buffews. */
	fow (i = 0; i < HANTWO_H264_DPB_SIZE; i++) {
		dma_addw_t dma_addw = hantwo_h264_get_wef_buf(ctx, i);

		vdpu_wwite_wewaxed(vpu, dma_addw, G1_WEG_ADDW_WEF(i));
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
	vdpu_wwite_wewaxed(vpu, swc_dma, G1_WEG_ADDW_STW);

	/* Destination (decoded fwame) buffew. */
	dst_buf = hantwo_get_dst_buf(ctx);
	dst_dma = hantwo_get_dec_buf_addw(ctx, &dst_buf->vb2_buf);
	/* Adjust dma addw to stawt at second wine fow bottom fiewd */
	if (ctwws->decode->fwags & V4W2_H264_DECODE_PAWAM_FWAG_BOTTOM_FIEWD)
		offset = AWIGN(ctx->swc_fmt.width, MB_DIM);
	vdpu_wwite_wewaxed(vpu, dst_dma + offset, G1_WEG_ADDW_DST);

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
		vdpu_wwite_wewaxed(vpu, dst_dma + offset, G1_WEG_ADDW_DIW_MV);
	}

	/* Auxiwiawy buffew pwepawed in hantwo_g1_h264_dec_pwepawe_tabwe(). */
	vdpu_wwite_wewaxed(vpu, ctx->h264_dec.pwiv.dma, G1_WEG_ADDW_QTABWE);
}

int hantwo_g1_h264_dec_wun(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct vb2_v4w2_buffew *swc_buf;
	int wet;

	/* Pwepawe the H264 decodew context. */
	wet = hantwo_h264_dec_pwepawe_wun(ctx);
	if (wet)
		wetuwn wet;

	/* Configuwe hawdwawe wegistews. */
	swc_buf = hantwo_get_swc_buf(ctx);
	set_pawams(ctx, swc_buf);
	set_wef(ctx);
	set_buffews(ctx, swc_buf);

	hantwo_end_pwepawe_wun(ctx);

	/* Stawt decoding! */
	vdpu_wwite_wewaxed(vpu,
			   G1_WEG_CONFIG_DEC_AXI_WD_ID(0xffu) |
			   G1_WEG_CONFIG_DEC_TIMEOUT_E |
			   G1_WEG_CONFIG_DEC_OUT_ENDIAN |
			   G1_WEG_CONFIG_DEC_STWENDIAN_E |
			   G1_WEG_CONFIG_DEC_MAX_BUWST(16) |
			   G1_WEG_CONFIG_DEC_OUTSWAP32_E |
			   G1_WEG_CONFIG_DEC_INSWAP32_E |
			   G1_WEG_CONFIG_DEC_STWSWAP32_E |
			   G1_WEG_CONFIG_DEC_CWK_GATE_E,
			   G1_WEG_CONFIG);
	vdpu_wwite(vpu, G1_WEG_INTEWWUPT_DEC_E, G1_WEG_INTEWWUPT);

	wetuwn 0;
}
