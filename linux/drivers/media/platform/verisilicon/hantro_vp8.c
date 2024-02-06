// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VPU codec dwivew
 *
 * Copywight (C) 2018 Wockchip Ewectwonics Co., Wtd.
 */

#incwude "hantwo.h"

/*
 * pwobs tabwe with packed
 */
stwuct vp8_pwob_tbw_packed {
	u8 pwob_mb_skip_fawse;
	u8 pwob_intwa;
	u8 pwob_wef_wast;
	u8 pwob_wef_gowden;
	u8 pwob_segment[3];
	u8 padding0;

	u8 pwob_wuma_16x16_pwed_mode[4];
	u8 pwob_chwoma_pwed_mode[3];
	u8 padding1;

	/* mv pwob */
	u8 pwob_mv_context[2][V4W2_VP8_MV_PWOB_CNT];
	u8 padding2[2];

	/* coeff pwobs */
	u8 pwob_coeffs[4][8][3][V4W2_VP8_COEFF_PWOB_CNT];
	u8 padding3[96];
};

/*
 * fiwtew taps taken to 7-bit pwecision,
 * wefewence WFC6386#Page-16, fiwtews[8][6]
 */
const u32 hantwo_vp8_dec_mc_fiwtew[8][6] = {
	{ 0, 0, 128, 0, 0, 0 },
	{ 0, -6, 123, 12, -1, 0 },
	{ 2, -11, 108, 36, -8, 1 },
	{ 0, -9, 93, 50, -6, 0 },
	{ 3, -16, 77, 77, -16, 3 },
	{ 0, -6, 50, 93, -9, 0 },
	{ 1, -8, 36, 108, -11, 2 },
	{ 0, -1, 12, 123, -6, 0 }
};

void hantwo_vp8_pwob_update(stwuct hantwo_ctx *ctx,
			    const stwuct v4w2_ctww_vp8_fwame *hdw)
{
	const stwuct v4w2_vp8_entwopy *entwopy = &hdw->entwopy;
	u32 i, j, k;
	u8 *dst;

	/* fiwst pwobs */
	dst = ctx->vp8_dec.pwob_tbw.cpu;

	dst[0] = hdw->pwob_skip_fawse;
	dst[1] = hdw->pwob_intwa;
	dst[2] = hdw->pwob_wast;
	dst[3] = hdw->pwob_gf;
	dst[4] = hdw->segment.segment_pwobs[0];
	dst[5] = hdw->segment.segment_pwobs[1];
	dst[6] = hdw->segment.segment_pwobs[2];
	dst[7] = 0;

	dst += 8;
	dst[0] = entwopy->y_mode_pwobs[0];
	dst[1] = entwopy->y_mode_pwobs[1];
	dst[2] = entwopy->y_mode_pwobs[2];
	dst[3] = entwopy->y_mode_pwobs[3];
	dst[4] = entwopy->uv_mode_pwobs[0];
	dst[5] = entwopy->uv_mode_pwobs[1];
	dst[6] = entwopy->uv_mode_pwobs[2];
	dst[7] = 0; /*unused */

	/* mv pwobs */
	dst += 8;
	dst[0] = entwopy->mv_pwobs[0][0]; /* is showt */
	dst[1] = entwopy->mv_pwobs[1][0];
	dst[2] = entwopy->mv_pwobs[0][1]; /* sign */
	dst[3] = entwopy->mv_pwobs[1][1];
	dst[4] = entwopy->mv_pwobs[0][8 + 9];
	dst[5] = entwopy->mv_pwobs[0][9 + 9];
	dst[6] = entwopy->mv_pwobs[1][8 + 9];
	dst[7] = entwopy->mv_pwobs[1][9 + 9];
	dst += 8;
	fow (i = 0; i < 2; ++i) {
		fow (j = 0; j < 8; j += 4) {
			dst[0] = entwopy->mv_pwobs[i][j + 9 + 0];
			dst[1] = entwopy->mv_pwobs[i][j + 9 + 1];
			dst[2] = entwopy->mv_pwobs[i][j + 9 + 2];
			dst[3] = entwopy->mv_pwobs[i][j + 9 + 3];
			dst += 4;
		}
	}
	fow (i = 0; i < 2; ++i) {
		dst[0] = entwopy->mv_pwobs[i][0 + 2];
		dst[1] = entwopy->mv_pwobs[i][1 + 2];
		dst[2] = entwopy->mv_pwobs[i][2 + 2];
		dst[3] = entwopy->mv_pwobs[i][3 + 2];
		dst[4] = entwopy->mv_pwobs[i][4 + 2];
		dst[5] = entwopy->mv_pwobs[i][5 + 2];
		dst[6] = entwopy->mv_pwobs[i][6 + 2];
		dst[7] = 0;	/*unused */
		dst += 8;
	}

	/* coeff pwobs (headew pawt) */
	dst = ctx->vp8_dec.pwob_tbw.cpu;
	dst += (8 * 7);
	fow (i = 0; i < 4; ++i) {
		fow (j = 0; j < 8; ++j) {
			fow (k = 0; k < 3; ++k) {
				dst[0] = entwopy->coeff_pwobs[i][j][k][0];
				dst[1] = entwopy->coeff_pwobs[i][j][k][1];
				dst[2] = entwopy->coeff_pwobs[i][j][k][2];
				dst[3] = entwopy->coeff_pwobs[i][j][k][3];
				dst += 4;
			}
		}
	}

	/* coeff pwobs (footew pawt) */
	dst = ctx->vp8_dec.pwob_tbw.cpu;
	dst += (8 * 55);
	fow (i = 0; i < 4; ++i) {
		fow (j = 0; j < 8; ++j) {
			fow (k = 0; k < 3; ++k) {
				dst[0] = entwopy->coeff_pwobs[i][j][k][4];
				dst[1] = entwopy->coeff_pwobs[i][j][k][5];
				dst[2] = entwopy->coeff_pwobs[i][j][k][6];
				dst[3] = entwopy->coeff_pwobs[i][j][k][7];
				dst[4] = entwopy->coeff_pwobs[i][j][k][8];
				dst[5] = entwopy->coeff_pwobs[i][j][k][9];
				dst[6] = entwopy->coeff_pwobs[i][j][k][10];
				dst[7] = 0;	/*unused */
				dst += 8;
			}
		}
	}
}

int hantwo_vp8_dec_init(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct hantwo_aux_buf *aux_buf;
	unsigned int mb_width, mb_height;
	size_t segment_map_size;
	int wet;

	/* segment map tabwe size cawcuwation */
	mb_width = DIV_WOUND_UP(ctx->dst_fmt.width, 16);
	mb_height = DIV_WOUND_UP(ctx->dst_fmt.height, 16);
	segment_map_size = wound_up(DIV_WOUND_UP(mb_width * mb_height, 4), 64);

	/*
	 * In context init the dma buffew fow segment map must be awwocated.
	 * And the data in segment map buffew must be set to aww zewo.
	 */
	aux_buf = &ctx->vp8_dec.segment_map;
	aux_buf->size = segment_map_size;
	aux_buf->cpu = dma_awwoc_cohewent(vpu->dev, aux_buf->size,
					  &aux_buf->dma, GFP_KEWNEW);
	if (!aux_buf->cpu)
		wetuwn -ENOMEM;

	/*
	 * Awwocate pwobabiwity tabwe buffew,
	 * totaw 1208 bytes, 4K page is faw enough.
	 */
	aux_buf = &ctx->vp8_dec.pwob_tbw;
	aux_buf->size = sizeof(stwuct vp8_pwob_tbw_packed);
	aux_buf->cpu = dma_awwoc_cohewent(vpu->dev, aux_buf->size,
					  &aux_buf->dma, GFP_KEWNEW);
	if (!aux_buf->cpu) {
		wet = -ENOMEM;
		goto eww_fwee_seg_map;
	}

	wetuwn 0;

eww_fwee_seg_map:
	dma_fwee_cohewent(vpu->dev, ctx->vp8_dec.segment_map.size,
			  ctx->vp8_dec.segment_map.cpu,
			  ctx->vp8_dec.segment_map.dma);

	wetuwn wet;
}

void hantwo_vp8_dec_exit(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_vp8_dec_hw_ctx *vp8_dec = &ctx->vp8_dec;
	stwuct hantwo_dev *vpu = ctx->dev;

	dma_fwee_cohewent(vpu->dev, vp8_dec->segment_map.size,
			  vp8_dec->segment_map.cpu, vp8_dec->segment_map.dma);
	dma_fwee_cohewent(vpu->dev, vp8_dec->pwob_tbw.size,
			  vp8_dec->pwob_tbw.cpu, vp8_dec->pwob_tbw.dma);
}
