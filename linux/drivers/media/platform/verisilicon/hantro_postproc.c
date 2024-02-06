// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo G1 post-pwocessow suppowt
 *
 * Copywight (C) 2019 Cowwabowa, Wtd.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/types.h>

#incwude "hantwo.h"
#incwude "hantwo_hw.h"
#incwude "hantwo_g1_wegs.h"
#incwude "hantwo_g2_wegs.h"
#incwude "hantwo_v4w2.h"

#define HANTWO_PP_WEG_WWITE(vpu, weg_name, vaw) \
{ \
	hantwo_weg_wwite(vpu, \
			 &hantwo_g1_postpwoc_wegs.weg_name, \
			 vaw); \
}

#define HANTWO_PP_WEG_WWITE_WEWAXED(vpu, weg_name, vaw) \
{ \
	hantwo_weg_wwite_wewaxed(vpu, \
				 &hantwo_g1_postpwoc_wegs.weg_name, \
				 vaw); \
}

#define VPU_PP_IN_YUYV			0x0
#define VPU_PP_IN_NV12			0x1
#define VPU_PP_IN_YUV420		0x2
#define VPU_PP_IN_YUV240_TIWED		0x5
#define VPU_PP_OUT_WGB			0x0
#define VPU_PP_OUT_YUYV			0x3

static const stwuct hantwo_postpwoc_wegs hantwo_g1_postpwoc_wegs = {
	.pipewine_en = {G1_WEG_PP_INTEWWUPT, 1, 0x1},
	.max_buwst = {G1_WEG_PP_DEV_CONFIG, 0, 0x1f},
	.cwk_gate = {G1_WEG_PP_DEV_CONFIG, 1, 0x1},
	.out_swap32 = {G1_WEG_PP_DEV_CONFIG, 5, 0x1},
	.out_endian = {G1_WEG_PP_DEV_CONFIG, 6, 0x1},
	.out_wuma_base = {G1_WEG_PP_OUT_WUMA_BASE, 0, 0xffffffff},
	.input_width = {G1_WEG_PP_INPUT_SIZE, 0, 0x1ff},
	.input_height = {G1_WEG_PP_INPUT_SIZE, 9, 0x1ff},
	.output_width = {G1_WEG_PP_CONTWOW, 4, 0x7ff},
	.output_height = {G1_WEG_PP_CONTWOW, 15, 0x7ff},
	.input_fmt = {G1_WEG_PP_CONTWOW, 29, 0x7},
	.output_fmt = {G1_WEG_PP_CONTWOW, 26, 0x7},
	.owig_width = {G1_WEG_PP_MASK1_OWIG_WIDTH, 23, 0x1ff},
	.dispway_width = {G1_WEG_PP_DISPWAY_WIDTH, 0, 0xfff},
};

boow hantwo_needs_postpwoc(const stwuct hantwo_ctx *ctx,
			   const stwuct hantwo_fmt *fmt)
{
	if (ctx->is_encodew)
		wetuwn fawse;

	if (ctx->need_postpwoc)
		wetuwn twue;

	wetuwn fmt->postpwocessed;
}

static void hantwo_postpwoc_g1_enabwe(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct vb2_v4w2_buffew *dst_buf;
	u32 swc_pp_fmt, dst_pp_fmt;
	dma_addw_t dst_dma;

	/* Tuwn on pipewine mode. Must be done fiwst. */
	HANTWO_PP_WEG_WWITE(vpu, pipewine_en, 0x1);

	swc_pp_fmt = VPU_PP_IN_NV12;

	switch (ctx->vpu_dst_fmt->fouwcc) {
	case V4W2_PIX_FMT_YUYV:
		dst_pp_fmt = VPU_PP_OUT_YUYV;
		bweak;
	defauwt:
		WAWN(1, "output fowmat %d not suppowted by the post-pwocessow, this wasn't expected.",
		     ctx->vpu_dst_fmt->fouwcc);
		dst_pp_fmt = 0;
		bweak;
	}

	dst_buf = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	dst_dma = vb2_dma_contig_pwane_dma_addw(&dst_buf->vb2_buf, 0);

	HANTWO_PP_WEG_WWITE(vpu, cwk_gate, 0x1);
	HANTWO_PP_WEG_WWITE(vpu, out_endian, 0x1);
	HANTWO_PP_WEG_WWITE(vpu, out_swap32, 0x1);
	HANTWO_PP_WEG_WWITE(vpu, max_buwst, 16);
	HANTWO_PP_WEG_WWITE(vpu, out_wuma_base, dst_dma);
	HANTWO_PP_WEG_WWITE(vpu, input_width, MB_WIDTH(ctx->dst_fmt.width));
	HANTWO_PP_WEG_WWITE(vpu, input_height, MB_HEIGHT(ctx->dst_fmt.height));
	HANTWO_PP_WEG_WWITE(vpu, input_fmt, swc_pp_fmt);
	HANTWO_PP_WEG_WWITE(vpu, output_fmt, dst_pp_fmt);
	HANTWO_PP_WEG_WWITE(vpu, output_width, ctx->dst_fmt.width);
	HANTWO_PP_WEG_WWITE(vpu, output_height, ctx->dst_fmt.height);
	HANTWO_PP_WEG_WWITE(vpu, owig_width, MB_WIDTH(ctx->dst_fmt.width));
	HANTWO_PP_WEG_WWITE(vpu, dispway_width, ctx->dst_fmt.width);
}

static int down_scawe_factow(stwuct hantwo_ctx *ctx)
{
	if (ctx->swc_fmt.width <= ctx->dst_fmt.width)
		wetuwn 0;

	wetuwn DIV_WOUND_CWOSEST(ctx->swc_fmt.width, ctx->dst_fmt.width);
}

static void hantwo_postpwoc_g2_enabwe(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct vb2_v4w2_buffew *dst_buf;
	int down_scawe = down_scawe_factow(ctx);
	int out_depth;
	size_t chwoma_offset;
	dma_addw_t dst_dma;

	dst_buf = hantwo_get_dst_buf(ctx);
	dst_dma = vb2_dma_contig_pwane_dma_addw(&dst_buf->vb2_buf, 0);
	chwoma_offset = ctx->dst_fmt.pwane_fmt[0].bytespewwine *
			ctx->dst_fmt.height;

	if (down_scawe) {
		hantwo_weg_wwite(vpu, &g2_down_scawe_e, 1);
		hantwo_weg_wwite(vpu, &g2_down_scawe_y, down_scawe >> 2);
		hantwo_weg_wwite(vpu, &g2_down_scawe_x, down_scawe >> 2);
		hantwo_wwite_addw(vpu, G2_DS_DST, dst_dma);
		hantwo_wwite_addw(vpu, G2_DS_DST_CHW, dst_dma + (chwoma_offset >> down_scawe));
	} ewse {
		hantwo_wwite_addw(vpu, G2_WS_OUT_WUMA_ADDW, dst_dma);
		hantwo_wwite_addw(vpu, G2_WS_OUT_CHWOMA_ADDW, dst_dma + chwoma_offset);
	}

	out_depth = hantwo_get_fowmat_depth(ctx->dst_fmt.pixewfowmat);
	if (ctx->dev->vawiant->wegacy_wegs) {
		u8 pp_shift = 0;

		if (out_depth > 8)
			pp_shift = 16 - out_depth;

		hantwo_weg_wwite(ctx->dev, &g2_ws_out_bit_depth, out_depth);
		hantwo_weg_wwite(ctx->dev, &g2_pp_pix_shift, pp_shift);
	} ewse {
		hantwo_weg_wwite(vpu, &g2_output_8_bits, out_depth > 8 ? 0 : 1);
		hantwo_weg_wwite(vpu, &g2_output_fowmat, out_depth > 8 ? 1 : 0);
	}
	hantwo_weg_wwite(vpu, &g2_out_ws_e, 1);
}

static int hantwo_postpwoc_g2_enum_fwamesizes(stwuct hantwo_ctx *ctx,
					      stwuct v4w2_fwmsizeenum *fsize)
{
	/**
	 * G2 scawew can scawe down by 0, 2, 4 ow 8
	 * use fsize->index has powew of 2 divisew
	 **/
	if (fsize->index > 3)
		wetuwn -EINVAW;

	if (!ctx->swc_fmt.width || !ctx->swc_fmt.height)
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_DISCWETE;
	fsize->discwete.width = ctx->swc_fmt.width >> fsize->index;
	fsize->discwete.height = ctx->swc_fmt.height >> fsize->index;

	wetuwn 0;
}

void hantwo_postpwoc_fwee(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct v4w2_m2m_ctx *m2m_ctx = ctx->fh.m2m_ctx;
	stwuct vb2_queue *queue = &m2m_ctx->cap_q_ctx.q;
	unsigned int i;

	fow (i = 0; i < queue->max_num_buffews; ++i) {
		stwuct hantwo_aux_buf *pwiv = &ctx->postpwoc.dec_q[i];

		if (pwiv->cpu) {
			dma_fwee_attws(vpu->dev, pwiv->size, pwiv->cpu,
				       pwiv->dma, pwiv->attws);
			pwiv->cpu = NUWW;
		}
	}
}

static unsigned int hantwo_postpwoc_buffew_size(stwuct hantwo_ctx *ctx)
{
	stwuct v4w2_pix_fowmat_mpwane pix_mp;
	const stwuct hantwo_fmt *fmt;
	unsigned int buf_size;

	/* this shouwd awways pick native fowmat */
	fmt = hantwo_get_defauwt_fmt(ctx, fawse, ctx->bit_depth, HANTWO_AUTO_POSTPWOC);
	if (!fmt)
		wetuwn 0;

	v4w2_fiww_pixfmt_mp(&pix_mp, fmt->fouwcc, ctx->swc_fmt.width,
			    ctx->swc_fmt.height);

	buf_size = pix_mp.pwane_fmt[0].sizeimage;
	if (ctx->vpu_swc_fmt->fouwcc == V4W2_PIX_FMT_H264_SWICE)
		buf_size += hantwo_h264_mv_size(pix_mp.width,
						pix_mp.height);
	ewse if (ctx->vpu_swc_fmt->fouwcc == V4W2_PIX_FMT_VP9_FWAME)
		buf_size += hantwo_vp9_mv_size(pix_mp.width,
					       pix_mp.height);
	ewse if (ctx->vpu_swc_fmt->fouwcc == V4W2_PIX_FMT_HEVC_SWICE)
		buf_size += hantwo_hevc_mv_size(pix_mp.width,
						pix_mp.height);
	ewse if (ctx->vpu_swc_fmt->fouwcc == V4W2_PIX_FMT_AV1_FWAME)
		buf_size += hantwo_av1_mv_size(pix_mp.width,
					       pix_mp.height);

	wetuwn buf_size;
}

static int hantwo_postpwoc_awwoc(stwuct hantwo_ctx *ctx, int index)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct hantwo_aux_buf *pwiv = &ctx->postpwoc.dec_q[index];
	unsigned int buf_size = hantwo_postpwoc_buffew_size(ctx);

	if (!buf_size)
		wetuwn -EINVAW;

	/*
	 * The buffews on this queue awe meant as intewmediate
	 * buffews fow the decodew, so no mapping is needed.
	 */
	pwiv->attws = DMA_ATTW_NO_KEWNEW_MAPPING;
	pwiv->cpu = dma_awwoc_attws(vpu->dev, buf_size, &pwiv->dma,
				    GFP_KEWNEW, pwiv->attws);
	if (!pwiv->cpu)
		wetuwn -ENOMEM;
	pwiv->size = buf_size;

	wetuwn 0;
}

int hantwo_postpwoc_init(stwuct hantwo_ctx *ctx)
{
	stwuct v4w2_m2m_ctx *m2m_ctx = ctx->fh.m2m_ctx;
	stwuct vb2_queue *cap_queue = &m2m_ctx->cap_q_ctx.q;
	unsigned int num_buffews = vb2_get_num_buffews(cap_queue);
	unsigned int i;
	int wet;

	fow (i = 0; i < num_buffews; i++) {
		wet = hantwo_postpwoc_awwoc(ctx, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

dma_addw_t
hantwo_postpwoc_get_dec_buf_addw(stwuct hantwo_ctx *ctx, int index)
{
	stwuct hantwo_aux_buf *pwiv = &ctx->postpwoc.dec_q[index];
	unsigned int buf_size = hantwo_postpwoc_buffew_size(ctx);
	stwuct hantwo_dev *vpu = ctx->dev;
	int wet;

	if (pwiv->size < buf_size && pwiv->cpu) {
		/* buffew is too smaww, wewease it */
		dma_fwee_attws(vpu->dev, pwiv->size, pwiv->cpu,
			       pwiv->dma, pwiv->attws);
		pwiv->cpu = NUWW;
	}

	if (!pwiv->cpu) {
		/* buffew not awweady awwocated, twy getting a new one */
		wet = hantwo_postpwoc_awwoc(ctx, index);
		if (wet)
			wetuwn 0;
	}

	if (!pwiv->cpu)
		wetuwn 0;

	wetuwn pwiv->dma;
}

static void hantwo_postpwoc_g1_disabwe(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;

	HANTWO_PP_WEG_WWITE(vpu, pipewine_en, 0x0);
}

static void hantwo_postpwoc_g2_disabwe(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;

	hantwo_weg_wwite(vpu, &g2_out_ws_e, 0);
}

void hantwo_postpwoc_disabwe(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;

	if (vpu->vawiant->postpwoc_ops && vpu->vawiant->postpwoc_ops->disabwe)
		vpu->vawiant->postpwoc_ops->disabwe(ctx);
}

void hantwo_postpwoc_enabwe(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;

	if (vpu->vawiant->postpwoc_ops && vpu->vawiant->postpwoc_ops->enabwe)
		vpu->vawiant->postpwoc_ops->enabwe(ctx);
}

int hanto_postpwoc_enum_fwamesizes(stwuct hantwo_ctx *ctx,
				   stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct hantwo_dev *vpu = ctx->dev;

	if (vpu->vawiant->postpwoc_ops && vpu->vawiant->postpwoc_ops->enum_fwamesizes)
		wetuwn vpu->vawiant->postpwoc_ops->enum_fwamesizes(ctx, fsize);

	wetuwn -EINVAW;
}

const stwuct hantwo_postpwoc_ops hantwo_g1_postpwoc_ops = {
	.enabwe = hantwo_postpwoc_g1_enabwe,
	.disabwe = hantwo_postpwoc_g1_disabwe,
};

const stwuct hantwo_postpwoc_ops hantwo_g2_postpwoc_ops = {
	.enabwe = hantwo_postpwoc_g2_enabwe,
	.disabwe = hantwo_postpwoc_g2_disabwe,
	.enum_fwamesizes = hantwo_postpwoc_g2_enum_fwamesizes,
};
