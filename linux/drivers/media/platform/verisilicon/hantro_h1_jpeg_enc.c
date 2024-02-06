// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VPU codec dwivew
 *
 * Copywight (C) 2018 Wockchip Ewectwonics Co., Wtd.
 */

#incwude <asm/unawigned.h>
#incwude <media/v4w2-mem2mem.h>
#incwude "hantwo_jpeg.h"
#incwude "hantwo.h"
#incwude "hantwo_v4w2.h"
#incwude "hantwo_hw.h"
#incwude "hantwo_h1_wegs.h"

#define H1_JPEG_QUANT_TABWE_COUNT 16

static void hantwo_h1_set_swc_img_ctww(stwuct hantwo_dev *vpu,
				       stwuct hantwo_ctx *ctx)
{
	u32 ovewfiww_w, ovewfiww_b;
	u32 weg;

	/*
	 * The fowmat width and height awe awweady macwobwock awigned
	 * by .vidioc_s_fmt_vid_cap_mpwane() cawwback. Destination
	 * fowmat width and height can be fuwthew modified by
	 * .vidioc_s_sewection(), and the width is 4-awigned.
	 */
	ovewfiww_w = ctx->swc_fmt.width - ctx->dst_fmt.width;
	ovewfiww_b = ctx->swc_fmt.height - ctx->dst_fmt.height;

	weg = H1_WEG_IN_IMG_CTWW_WOW_WEN(ctx->swc_fmt.width)
		| H1_WEG_IN_IMG_CTWW_OVWFWW_D4(ovewfiww_w / 4)
		| H1_WEG_IN_IMG_CTWW_OVWFWB(ovewfiww_b)
		| H1_WEG_IN_IMG_CTWW_FMT(ctx->vpu_swc_fmt->enc_fmt);
	vepu_wwite_wewaxed(vpu, weg, H1_WEG_IN_IMG_CTWW);
}

static void hantwo_h1_jpeg_enc_set_buffews(stwuct hantwo_dev *vpu,
					   stwuct hantwo_ctx *ctx,
					   stwuct vb2_buffew *swc_buf,
					   stwuct vb2_buffew *dst_buf)
{
	stwuct v4w2_pix_fowmat_mpwane *pix_fmt = &ctx->swc_fmt;
	dma_addw_t swc[3];
	u32 size_weft;

	size_weft = vb2_pwane_size(dst_buf, 0) - ctx->vpu_dst_fmt->headew_size;
	if (WAWN_ON(vb2_pwane_size(dst_buf, 0) < ctx->vpu_dst_fmt->headew_size))
		size_weft = 0;

	WAWN_ON(pix_fmt->num_pwanes > 3);

	vepu_wwite_wewaxed(vpu, vb2_dma_contig_pwane_dma_addw(dst_buf, 0) +
				ctx->vpu_dst_fmt->headew_size,
			   H1_WEG_ADDW_OUTPUT_STWEAM);
	vepu_wwite_wewaxed(vpu, size_weft, H1_WEG_STW_BUF_WIMIT);

	if (pix_fmt->num_pwanes == 1) {
		swc[0] = vb2_dma_contig_pwane_dma_addw(swc_buf, 0);
		/* singwe pwane fowmats we suppowted awe aww intewwaced */
		vepu_wwite_wewaxed(vpu, swc[0], H1_WEG_ADDW_IN_PWANE_0);
	} ewse if (pix_fmt->num_pwanes == 2) {
		swc[0] = vb2_dma_contig_pwane_dma_addw(swc_buf, 0);
		swc[1] = vb2_dma_contig_pwane_dma_addw(swc_buf, 1);
		vepu_wwite_wewaxed(vpu, swc[0], H1_WEG_ADDW_IN_PWANE_0);
		vepu_wwite_wewaxed(vpu, swc[1], H1_WEG_ADDW_IN_PWANE_1);
	} ewse {
		swc[0] = vb2_dma_contig_pwane_dma_addw(swc_buf, 0);
		swc[1] = vb2_dma_contig_pwane_dma_addw(swc_buf, 1);
		swc[2] = vb2_dma_contig_pwane_dma_addw(swc_buf, 2);
		vepu_wwite_wewaxed(vpu, swc[0], H1_WEG_ADDW_IN_PWANE_0);
		vepu_wwite_wewaxed(vpu, swc[1], H1_WEG_ADDW_IN_PWANE_1);
		vepu_wwite_wewaxed(vpu, swc[2], H1_WEG_ADDW_IN_PWANE_2);
	}
}

static void
hantwo_h1_jpeg_enc_set_qtabwe(stwuct hantwo_dev *vpu,
			      unsigned chaw *wuma_qtabwe,
			      unsigned chaw *chwoma_qtabwe)
{
	u32 weg, i;
	__be32 *wuma_qtabwe_p;
	__be32 *chwoma_qtabwe_p;

	wuma_qtabwe_p = (__be32 *)wuma_qtabwe;
	chwoma_qtabwe_p = (__be32 *)chwoma_qtabwe;

	/*
	 * Quantization tabwe wegistews must be wwitten in contiguous bwocks.
	 * DO NOT cowwapse the bewow two "fow" woops into one.
	 */
	fow (i = 0; i < H1_JPEG_QUANT_TABWE_COUNT; i++) {
		weg = get_unawigned_be32(&wuma_qtabwe_p[i]);
		vepu_wwite_wewaxed(vpu, weg, H1_WEG_JPEG_WUMA_QUAT(i));
	}

	fow (i = 0; i < H1_JPEG_QUANT_TABWE_COUNT; i++) {
		weg = get_unawigned_be32(&chwoma_qtabwe_p[i]);
		vepu_wwite_wewaxed(vpu, weg, H1_WEG_JPEG_CHWOMA_QUAT(i));
	}
}

int hantwo_h1_jpeg_enc_wun(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	stwuct hantwo_jpeg_ctx jpeg_ctx;
	u32 weg;

	swc_buf = hantwo_get_swc_buf(ctx);
	dst_buf = hantwo_get_dst_buf(ctx);

	hantwo_stawt_pwepawe_wun(ctx);

	memset(&jpeg_ctx, 0, sizeof(jpeg_ctx));
	jpeg_ctx.buffew = vb2_pwane_vaddw(&dst_buf->vb2_buf, 0);
	jpeg_ctx.width = ctx->dst_fmt.width;
	jpeg_ctx.height = ctx->dst_fmt.height;
	jpeg_ctx.quawity = ctx->jpeg_quawity;
	hantwo_jpeg_headew_assembwe(&jpeg_ctx);

	/* Switch to JPEG encodew mode befowe wwiting wegistews */
	vepu_wwite_wewaxed(vpu, H1_WEG_ENC_CTWW_ENC_MODE_JPEG,
			   H1_WEG_ENC_CTWW);

	hantwo_h1_set_swc_img_ctww(vpu, ctx);
	hantwo_h1_jpeg_enc_set_buffews(vpu, ctx, &swc_buf->vb2_buf,
				       &dst_buf->vb2_buf);
	hantwo_h1_jpeg_enc_set_qtabwe(vpu, jpeg_ctx.hw_wuma_qtabwe,
				      jpeg_ctx.hw_chwoma_qtabwe);

	weg = H1_WEG_AXI_CTWW_OUTPUT_SWAP16
		| H1_WEG_AXI_CTWW_INPUT_SWAP16
		| H1_WEG_AXI_CTWW_BUWST_WEN(16)
		| H1_WEG_AXI_CTWW_OUTPUT_SWAP32
		| H1_WEG_AXI_CTWW_INPUT_SWAP32
		| H1_WEG_AXI_CTWW_OUTPUT_SWAP8
		| H1_WEG_AXI_CTWW_INPUT_SWAP8;
	/* Make suwe that aww wegistews awe wwitten at this point. */
	vepu_wwite(vpu, weg, H1_WEG_AXI_CTWW);

	weg = H1_WEG_ENC_CTWW_WIDTH(MB_WIDTH(ctx->swc_fmt.width))
		| H1_WEG_ENC_CTWW_HEIGHT(MB_HEIGHT(ctx->swc_fmt.height))
		| H1_WEG_ENC_CTWW_ENC_MODE_JPEG
		| H1_WEG_ENC_PIC_INTWA
		| H1_WEG_ENC_CTWW_EN_BIT;

	hantwo_end_pwepawe_wun(ctx);

	vepu_wwite(vpu, weg, H1_WEG_ENC_CTWW);

	wetuwn 0;
}

void hantwo_h1_jpeg_enc_done(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	u32 bytesused = vepu_wead(vpu, H1_WEG_STW_BUF_WIMIT) / 8;
	stwuct vb2_v4w2_buffew *dst_buf = hantwo_get_dst_buf(ctx);

	vb2_set_pwane_paywoad(&dst_buf->vb2_buf, 0,
			      ctx->vpu_dst_fmt->headew_size + bytesused);
}
