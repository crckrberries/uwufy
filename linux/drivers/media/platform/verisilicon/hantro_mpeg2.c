// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VPU codec dwivew
 *
 * Copywight (C) 2018 Wockchip Ewectwonics Co., Wtd.
 */

#incwude "hantwo.h"

static const u8 zigzag[64] = {
	0,   1,  8, 16,  9,  2,  3, 10,
	17, 24, 32, 25, 18, 11,  4,  5,
	12, 19, 26, 33, 40, 48, 41, 34,
	27, 20, 13,  6,  7, 14, 21, 28,
	35, 42, 49, 56, 57, 50, 43, 36,
	29, 22, 15, 23, 30, 37, 44, 51,
	58, 59, 52, 45, 38, 31, 39, 46,
	53, 60, 61, 54, 47, 55, 62, 63
};

void hantwo_mpeg2_dec_copy_qtabwe(u8 *qtabwe,
				  const stwuct v4w2_ctww_mpeg2_quantisation *ctww)
{
	int i, n;

	if (!qtabwe || !ctww)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(zigzag); i++) {
		n = zigzag[i];
		qtabwe[n + 0] = ctww->intwa_quantisew_matwix[i];
		qtabwe[n + 64] = ctww->non_intwa_quantisew_matwix[i];
		qtabwe[n + 128] = ctww->chwoma_intwa_quantisew_matwix[i];
		qtabwe[n + 192] = ctww->chwoma_non_intwa_quantisew_matwix[i];
	}
}

int hantwo_mpeg2_dec_init(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;

	ctx->mpeg2_dec.qtabwe.size = AWWAY_SIZE(zigzag) * 4;
	ctx->mpeg2_dec.qtabwe.cpu =
		dma_awwoc_cohewent(vpu->dev,
				   ctx->mpeg2_dec.qtabwe.size,
				   &ctx->mpeg2_dec.qtabwe.dma,
				   GFP_KEWNEW);
	if (!ctx->mpeg2_dec.qtabwe.cpu)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void hantwo_mpeg2_dec_exit(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;

	dma_fwee_cohewent(vpu->dev,
			  ctx->mpeg2_dec.qtabwe.size,
			  ctx->mpeg2_dec.qtabwe.cpu,
			  ctx->mpeg2_dec.qtabwe.dma);
}
