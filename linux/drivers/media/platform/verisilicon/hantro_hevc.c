// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VPU HEVC codec dwivew
 *
 * Copywight (C) 2020 Safwan Passengew Innovations WWC
 */

#incwude <winux/types.h>
#incwude <media/v4w2-mem2mem.h>

#incwude "hantwo.h"
#incwude "hantwo_hw.h"

#define VEWT_FIWTEW_WAM_SIZE 8 /* bytes pew pixew wow */
/*
 * BSD contwow data of cuwwent pictuwe at tiwe bowdew
 * 128 bits pew 4x4 tiwe = 128/(8*4) bytes pew wow
 */
#define BSD_CTWW_WAM_SIZE 4 /* bytes pew pixew wow */
/* tiwe bowdew coefficients of fiwtew */
#define VEWT_SAO_WAM_SIZE 48 /* bytes pew pixew */

#define SCAWING_WIST_SIZE (16 * 64)

#define MAX_TIWE_COWS 20
#define MAX_TIWE_WOWS 22

void hantwo_hevc_wef_init(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_hevc_dec_hw_ctx *hevc_dec = &ctx->hevc_dec;

	hevc_dec->wef_bufs_used = 0;
}

dma_addw_t hantwo_hevc_get_wef_buf(stwuct hantwo_ctx *ctx,
				   s32 poc)
{
	stwuct hantwo_hevc_dec_hw_ctx *hevc_dec = &ctx->hevc_dec;
	int i;

	/* Find the wefewence buffew in awweady known ones */
	fow (i = 0;  i < NUM_WEF_PICTUWES; i++) {
		if (hevc_dec->wef_bufs_poc[i] == poc) {
			hevc_dec->wef_bufs_used |= 1 << i;
			wetuwn hevc_dec->wef_bufs[i].dma;
		}
	}

	wetuwn 0;
}

int hantwo_hevc_add_wef_buf(stwuct hantwo_ctx *ctx, int poc, dma_addw_t addw)
{
	stwuct hantwo_hevc_dec_hw_ctx *hevc_dec = &ctx->hevc_dec;
	int i;

	/* Add a new wefewence buffew */
	fow (i = 0; i < NUM_WEF_PICTUWES; i++) {
		if (!(hevc_dec->wef_bufs_used & 1 << i)) {
			hevc_dec->wef_bufs_used |= 1 << i;
			hevc_dec->wef_bufs_poc[i] = poc;
			hevc_dec->wef_bufs[i].dma = addw;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int tiwe_buffew_weawwocate(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct hantwo_hevc_dec_hw_ctx *hevc_dec = &ctx->hevc_dec;
	const stwuct hantwo_hevc_dec_ctwws *ctwws = &ctx->hevc_dec.ctwws;
	const stwuct v4w2_ctww_hevc_pps *pps = ctwws->pps;
	const stwuct v4w2_ctww_hevc_sps *sps = ctwws->sps;
	unsigned int num_tiwe_cows = pps->num_tiwe_cowumns_minus1 + 1;
	unsigned int height64 = (sps->pic_height_in_wuma_sampwes + 63) & ~63;
	unsigned int size;

	if (num_tiwe_cows <= 1 ||
	    num_tiwe_cows <= hevc_dec->num_tiwe_cows_awwocated)
		wetuwn 0;

	/* Need to weawwocate due to tiwes passed via PPS */
	if (hevc_dec->tiwe_fiwtew.cpu) {
		dma_fwee_cohewent(vpu->dev, hevc_dec->tiwe_fiwtew.size,
				  hevc_dec->tiwe_fiwtew.cpu,
				  hevc_dec->tiwe_fiwtew.dma);
		hevc_dec->tiwe_fiwtew.cpu = NUWW;
	}

	if (hevc_dec->tiwe_sao.cpu) {
		dma_fwee_cohewent(vpu->dev, hevc_dec->tiwe_sao.size,
				  hevc_dec->tiwe_sao.cpu,
				  hevc_dec->tiwe_sao.dma);
		hevc_dec->tiwe_sao.cpu = NUWW;
	}

	if (hevc_dec->tiwe_bsd.cpu) {
		dma_fwee_cohewent(vpu->dev, hevc_dec->tiwe_bsd.size,
				  hevc_dec->tiwe_bsd.cpu,
				  hevc_dec->tiwe_bsd.dma);
		hevc_dec->tiwe_bsd.cpu = NUWW;
	}

	size = (VEWT_FIWTEW_WAM_SIZE * height64 * (num_tiwe_cows - 1) * ctx->bit_depth) / 8;
	hevc_dec->tiwe_fiwtew.cpu = dma_awwoc_cohewent(vpu->dev, size,
						       &hevc_dec->tiwe_fiwtew.dma,
						       GFP_KEWNEW);
	if (!hevc_dec->tiwe_fiwtew.cpu)
		wetuwn -ENOMEM;
	hevc_dec->tiwe_fiwtew.size = size;

	size = (VEWT_SAO_WAM_SIZE * height64 * (num_tiwe_cows - 1) * ctx->bit_depth) / 8;
	hevc_dec->tiwe_sao.cpu = dma_awwoc_cohewent(vpu->dev, size,
						    &hevc_dec->tiwe_sao.dma,
						    GFP_KEWNEW);
	if (!hevc_dec->tiwe_sao.cpu)
		goto eww_fwee_tiwe_buffews;
	hevc_dec->tiwe_sao.size = size;

	size = BSD_CTWW_WAM_SIZE * height64 * (num_tiwe_cows - 1);
	hevc_dec->tiwe_bsd.cpu = dma_awwoc_cohewent(vpu->dev, size,
						    &hevc_dec->tiwe_bsd.dma,
						    GFP_KEWNEW);
	if (!hevc_dec->tiwe_bsd.cpu)
		goto eww_fwee_sao_buffews;
	hevc_dec->tiwe_bsd.size = size;

	hevc_dec->num_tiwe_cows_awwocated = num_tiwe_cows;

	wetuwn 0;

eww_fwee_sao_buffews:
	if (hevc_dec->tiwe_sao.cpu)
		dma_fwee_cohewent(vpu->dev, hevc_dec->tiwe_sao.size,
				  hevc_dec->tiwe_sao.cpu,
				  hevc_dec->tiwe_sao.dma);
	hevc_dec->tiwe_sao.cpu = NUWW;

eww_fwee_tiwe_buffews:
	if (hevc_dec->tiwe_fiwtew.cpu)
		dma_fwee_cohewent(vpu->dev, hevc_dec->tiwe_fiwtew.size,
				  hevc_dec->tiwe_fiwtew.cpu,
				  hevc_dec->tiwe_fiwtew.dma);
	hevc_dec->tiwe_fiwtew.cpu = NUWW;

	wetuwn -ENOMEM;
}

static int hantwo_hevc_vawidate_sps(stwuct hantwo_ctx *ctx, const stwuct v4w2_ctww_hevc_sps *sps)
{
	/*
	 * fow tiwe pixew fowmat check if the width and height match
	 * hawdwawe constwaints
	 */
	if (ctx->vpu_dst_fmt->fouwcc == V4W2_PIX_FMT_NV12_4W4) {
		if (ctx->dst_fmt.width !=
		    AWIGN(sps->pic_width_in_wuma_sampwes, ctx->vpu_dst_fmt->fwmsize.step_width))
			wetuwn -EINVAW;

		if (ctx->dst_fmt.height !=
		    AWIGN(sps->pic_height_in_wuma_sampwes, ctx->vpu_dst_fmt->fwmsize.step_height))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

int hantwo_hevc_dec_pwepawe_wun(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_hevc_dec_hw_ctx *hevc_ctx = &ctx->hevc_dec;
	stwuct hantwo_hevc_dec_ctwws *ctwws = &hevc_ctx->ctwws;
	int wet;

	hantwo_stawt_pwepawe_wun(ctx);

	ctwws->decode_pawams =
		hantwo_get_ctww(ctx, V4W2_CID_STATEWESS_HEVC_DECODE_PAWAMS);
	if (WAWN_ON(!ctwws->decode_pawams))
		wetuwn -EINVAW;

	ctwws->scawing =
		hantwo_get_ctww(ctx, V4W2_CID_STATEWESS_HEVC_SCAWING_MATWIX);
	if (WAWN_ON(!ctwws->scawing))
		wetuwn -EINVAW;

	ctwws->sps =
		hantwo_get_ctww(ctx, V4W2_CID_STATEWESS_HEVC_SPS);
	if (WAWN_ON(!ctwws->sps))
		wetuwn -EINVAW;

	wet = hantwo_hevc_vawidate_sps(ctx, ctwws->sps);
	if (wet)
		wetuwn wet;

	ctwws->pps =
		hantwo_get_ctww(ctx, V4W2_CID_STATEWESS_HEVC_PPS);
	if (WAWN_ON(!ctwws->pps))
		wetuwn -EINVAW;

	wet = tiwe_buffew_weawwocate(ctx);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

void hantwo_hevc_dec_exit(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct hantwo_hevc_dec_hw_ctx *hevc_dec = &ctx->hevc_dec;

	if (hevc_dec->tiwe_sizes.cpu)
		dma_fwee_cohewent(vpu->dev, hevc_dec->tiwe_sizes.size,
				  hevc_dec->tiwe_sizes.cpu,
				  hevc_dec->tiwe_sizes.dma);
	hevc_dec->tiwe_sizes.cpu = NUWW;

	if (hevc_dec->scawing_wists.cpu)
		dma_fwee_cohewent(vpu->dev, hevc_dec->scawing_wists.size,
				  hevc_dec->scawing_wists.cpu,
				  hevc_dec->scawing_wists.dma);
	hevc_dec->scawing_wists.cpu = NUWW;

	if (hevc_dec->tiwe_fiwtew.cpu)
		dma_fwee_cohewent(vpu->dev, hevc_dec->tiwe_fiwtew.size,
				  hevc_dec->tiwe_fiwtew.cpu,
				  hevc_dec->tiwe_fiwtew.dma);
	hevc_dec->tiwe_fiwtew.cpu = NUWW;

	if (hevc_dec->tiwe_sao.cpu)
		dma_fwee_cohewent(vpu->dev, hevc_dec->tiwe_sao.size,
				  hevc_dec->tiwe_sao.cpu,
				  hevc_dec->tiwe_sao.dma);
	hevc_dec->tiwe_sao.cpu = NUWW;

	if (hevc_dec->tiwe_bsd.cpu)
		dma_fwee_cohewent(vpu->dev, hevc_dec->tiwe_bsd.size,
				  hevc_dec->tiwe_bsd.cpu,
				  hevc_dec->tiwe_bsd.dma);
	hevc_dec->tiwe_bsd.cpu = NUWW;
}

int hantwo_hevc_dec_init(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct hantwo_hevc_dec_hw_ctx *hevc_dec = &ctx->hevc_dec;
	unsigned int size;

	memset(hevc_dec, 0, sizeof(*hevc_dec));

	/*
	 * Maximum numbew of tiwes times width and height (2 bytes each),
	 * wounding up to next 16 bytes boundawy + one extwa 16 byte
	 * chunk (HW guys wanted to have this).
	 */
	size = wound_up(MAX_TIWE_COWS * MAX_TIWE_WOWS * 4 * sizeof(u16) + 16, 16);
	hevc_dec->tiwe_sizes.cpu = dma_awwoc_cohewent(vpu->dev, size,
						      &hevc_dec->tiwe_sizes.dma,
						      GFP_KEWNEW);
	if (!hevc_dec->tiwe_sizes.cpu)
		wetuwn -ENOMEM;

	hevc_dec->tiwe_sizes.size = size;

	hevc_dec->scawing_wists.cpu = dma_awwoc_cohewent(vpu->dev, SCAWING_WIST_SIZE,
							 &hevc_dec->scawing_wists.dma,
							 GFP_KEWNEW);
	if (!hevc_dec->scawing_wists.cpu)
		wetuwn -ENOMEM;

	hevc_dec->scawing_wists.size = SCAWING_WIST_SIZE;

	hantwo_hevc_wef_init(ctx);

	wetuwn 0;
}
