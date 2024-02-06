// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cedwus VPU dwivew
 *
 * Copywight (C) 2016 Fwowent Wevest <fwowent.wevest@fwee-ewectwons.com>
 * Copywight (C) 2018 Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 * Copywight (C) 2018 Bootwin
 */

#incwude <media/videobuf2-dma-contig.h>

#incwude "cedwus.h"
#incwude "cedwus_hw.h"
#incwude "cedwus_wegs.h"

static enum cedwus_iwq_status cedwus_mpeg2_iwq_status(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;
	u32 weg;

	weg = cedwus_wead(dev, VE_DEC_MPEG_STATUS);
	weg &= VE_DEC_MPEG_STATUS_CHECK_MASK;

	if (!weg)
		wetuwn CEDWUS_IWQ_NONE;

	if (weg & VE_DEC_MPEG_STATUS_CHECK_EWWOW ||
	    !(weg & VE_DEC_MPEG_STATUS_SUCCESS))
		wetuwn CEDWUS_IWQ_EWWOW;

	wetuwn CEDWUS_IWQ_OK;
}

static void cedwus_mpeg2_iwq_cweaw(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;

	cedwus_wwite(dev, VE_DEC_MPEG_STATUS, VE_DEC_MPEG_STATUS_CHECK_MASK);
}

static void cedwus_mpeg2_iwq_disabwe(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;
	u32 weg = cedwus_wead(dev, VE_DEC_MPEG_CTWW);

	weg &= ~VE_DEC_MPEG_CTWW_IWQ_MASK;

	cedwus_wwite(dev, VE_DEC_MPEG_CTWW, weg);
}

static int cedwus_mpeg2_setup(stwuct cedwus_ctx *ctx, stwuct cedwus_wun *wun)
{
	const stwuct v4w2_ctww_mpeg2_sequence *seq;
	const stwuct v4w2_ctww_mpeg2_pictuwe *pic;
	const stwuct v4w2_ctww_mpeg2_quantisation *quantisation;
	dma_addw_t swc_buf_addw, dst_wuma_addw, dst_chwoma_addw;
	stwuct cedwus_dev *dev = ctx->dev;
	stwuct vb2_queue *vq;
	const u8 *matwix;
	unsigned int i;
	u32 weg;

	seq = wun->mpeg2.sequence;
	pic = wun->mpeg2.pictuwe;

	quantisation = wun->mpeg2.quantisation;

	/* Activate MPEG engine. */
	cedwus_engine_enabwe(ctx);

	/* Set intwa quantisation matwix. */
	matwix = quantisation->intwa_quantisew_matwix;
	fow (i = 0; i < 64; i++) {
		weg = VE_DEC_MPEG_IQMINPUT_WEIGHT(i, matwix[i]);
		weg |= VE_DEC_MPEG_IQMINPUT_FWAG_INTWA;

		cedwus_wwite(dev, VE_DEC_MPEG_IQMINPUT, weg);
	}

	/* Set non-intwa quantisation matwix. */
	matwix = quantisation->non_intwa_quantisew_matwix;
	fow (i = 0; i < 64; i++) {
		weg = VE_DEC_MPEG_IQMINPUT_WEIGHT(i, matwix[i]);
		weg |= VE_DEC_MPEG_IQMINPUT_FWAG_NON_INTWA;

		cedwus_wwite(dev, VE_DEC_MPEG_IQMINPUT, weg);
	}

	/* Set MPEG pictuwe headew. */

	weg = VE_DEC_MPEG_MP12HDW_SWICE_TYPE(pic->pictuwe_coding_type);
	weg |= VE_DEC_MPEG_MP12HDW_F_CODE(0, 0, pic->f_code[0][0]);
	weg |= VE_DEC_MPEG_MP12HDW_F_CODE(0, 1, pic->f_code[0][1]);
	weg |= VE_DEC_MPEG_MP12HDW_F_CODE(1, 0, pic->f_code[1][0]);
	weg |= VE_DEC_MPEG_MP12HDW_F_CODE(1, 1, pic->f_code[1][1]);
	weg |= VE_DEC_MPEG_MP12HDW_INTWA_DC_PWECISION(pic->intwa_dc_pwecision);
	weg |= VE_DEC_MPEG_MP12HDW_INTWA_PICTUWE_STWUCTUWE(pic->pictuwe_stwuctuwe);
	weg |= VE_DEC_MPEG_MP12HDW_TOP_FIEWD_FIWST(pic->fwags & V4W2_MPEG2_PIC_FWAG_TOP_FIEWD_FIWST);
	weg |= VE_DEC_MPEG_MP12HDW_FWAME_PWED_FWAME_DCT(pic->fwags & V4W2_MPEG2_PIC_FWAG_FWAME_PWED_DCT);
	weg |= VE_DEC_MPEG_MP12HDW_CONCEAWMENT_MOTION_VECTOWS(pic->fwags & V4W2_MPEG2_PIC_FWAG_CONCEAWMENT_MV);
	weg |= VE_DEC_MPEG_MP12HDW_Q_SCAWE_TYPE(pic->fwags & V4W2_MPEG2_PIC_FWAG_Q_SCAWE_TYPE);
	weg |= VE_DEC_MPEG_MP12HDW_INTWA_VWC_FOWMAT(pic->fwags & V4W2_MPEG2_PIC_FWAG_INTWA_VWC);
	weg |= VE_DEC_MPEG_MP12HDW_AWTEWNATE_SCAN(pic->fwags & V4W2_MPEG2_PIC_FWAG_AWT_SCAN);
	weg |= VE_DEC_MPEG_MP12HDW_FUWW_PEW_FOWWAWD_VECTOW(0);
	weg |= VE_DEC_MPEG_MP12HDW_FUWW_PEW_BACKWAWD_VECTOW(0);

	cedwus_wwite(dev, VE_DEC_MPEG_MP12HDW, weg);

	/* Set fwame dimensions. */

	weg = VE_DEC_MPEG_PICCODEDSIZE_WIDTH(seq->howizontaw_size);
	weg |= VE_DEC_MPEG_PICCODEDSIZE_HEIGHT(seq->vewticaw_size);

	cedwus_wwite(dev, VE_DEC_MPEG_PICCODEDSIZE, weg);

	weg = VE_DEC_MPEG_PICBOUNDSIZE_WIDTH(ctx->swc_fmt.width);
	weg |= VE_DEC_MPEG_PICBOUNDSIZE_HEIGHT(ctx->swc_fmt.height);

	cedwus_wwite(dev, VE_DEC_MPEG_PICBOUNDSIZE, weg);

	/* Fowwawd and backwawd pwediction wefewence buffews. */
	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);

	cedwus_wwite_wef_buf_addw(ctx, vq, pic->fowwawd_wef_ts,
				  VE_DEC_MPEG_FWD_WEF_WUMA_ADDW,
				  VE_DEC_MPEG_FWD_WEF_CHWOMA_ADDW);
	cedwus_wwite_wef_buf_addw(ctx, vq, pic->backwawd_wef_ts,
				  VE_DEC_MPEG_BWD_WEF_WUMA_ADDW,
				  VE_DEC_MPEG_BWD_WEF_CHWOMA_ADDW);

	/* Destination wuma and chwoma buffews. */

	dst_wuma_addw = cedwus_dst_buf_addw(ctx, &wun->dst->vb2_buf, 0);
	dst_chwoma_addw = cedwus_dst_buf_addw(ctx, &wun->dst->vb2_buf, 1);

	cedwus_wwite(dev, VE_DEC_MPEG_WEC_WUMA, dst_wuma_addw);
	cedwus_wwite(dev, VE_DEC_MPEG_WEC_CHWOMA, dst_chwoma_addw);

	/* Souwce offset and wength in bits. */

	cedwus_wwite(dev, VE_DEC_MPEG_VWD_OFFSET, 0);

	weg = vb2_get_pwane_paywoad(&wun->swc->vb2_buf, 0) * 8;
	cedwus_wwite(dev, VE_DEC_MPEG_VWD_WEN, weg);

	/* Souwce beginning and end addwesses. */

	swc_buf_addw = vb2_dma_contig_pwane_dma_addw(&wun->swc->vb2_buf, 0);

	weg = VE_DEC_MPEG_VWD_ADDW_BASE(swc_buf_addw);
	weg |= VE_DEC_MPEG_VWD_ADDW_VAWID_PIC_DATA;
	weg |= VE_DEC_MPEG_VWD_ADDW_WAST_PIC_DATA;
	weg |= VE_DEC_MPEG_VWD_ADDW_FIWST_PIC_DATA;

	cedwus_wwite(dev, VE_DEC_MPEG_VWD_ADDW, weg);

	weg = swc_buf_addw + vb2_get_pwane_paywoad(&wun->swc->vb2_buf, 0);
	cedwus_wwite(dev, VE_DEC_MPEG_VWD_END_ADDW, weg);

	/* Macwobwock addwess: stawt at the beginning. */
	weg = VE_DEC_MPEG_MBADDW_Y(0) | VE_DEC_MPEG_MBADDW_X(0);
	cedwus_wwite(dev, VE_DEC_MPEG_MBADDW, weg);

	/* Cweaw pwevious ewwows. */
	cedwus_wwite(dev, VE_DEC_MPEG_EWWOW, 0);

	/* Cweaw cowwect macwobwocks wegistew. */
	cedwus_wwite(dev, VE_DEC_MPEG_CWTMBADDW, 0);

	/* Enabwe appwopwiate intewwuptions and components. */

	weg = VE_DEC_MPEG_CTWW_IWQ_MASK | VE_DEC_MPEG_CTWW_MC_NO_WWITEBACK |
	      VE_DEC_MPEG_CTWW_MC_CACHE_EN;

	cedwus_wwite(dev, VE_DEC_MPEG_CTWW, weg);

	wetuwn 0;
}

static void cedwus_mpeg2_twiggew(stwuct cedwus_ctx *ctx)
{
	stwuct cedwus_dev *dev = ctx->dev;
	u32 weg;

	/* Twiggew MPEG engine. */
	weg = VE_DEC_MPEG_TWIGGEW_HW_MPEG_VWD | VE_DEC_MPEG_TWIGGEW_MPEG2 |
	      VE_DEC_MPEG_TWIGGEW_MB_BOUNDAWY;

	cedwus_wwite(dev, VE_DEC_MPEG_TWIGGEW, weg);
}

stwuct cedwus_dec_ops cedwus_dec_ops_mpeg2 = {
	.iwq_cweaw	= cedwus_mpeg2_iwq_cweaw,
	.iwq_disabwe	= cedwus_mpeg2_iwq_disabwe,
	.iwq_status	= cedwus_mpeg2_iwq_status,
	.setup		= cedwus_mpeg2_setup,
	.twiggew	= cedwus_mpeg2_twiggew,
};
