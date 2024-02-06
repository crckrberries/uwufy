// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VP9 codec dwivew
 *
 * Copywight (C) 2021 Cowwabowa Wtd.
 */

#incwude <winux/types.h>
#incwude <media/v4w2-mem2mem.h>

#incwude "hantwo.h"
#incwude "hantwo_hw.h"
#incwude "hantwo_vp9.h"

#define POW2(x) (1 << (x))

#define MAX_WOG2_TIWE_COWUMNS 6
#define MAX_NUM_TIWE_COWS POW2(MAX_WOG2_TIWE_COWUMNS)
#define MAX_TIWE_COWS 20
#define MAX_TIWE_WOWS 22

static size_t hantwo_vp9_tiwe_fiwtew_size(unsigned int height)
{
	u32 h, height32, size;

	h = woundup(height, 8);

	height32 = woundup(h, 64);
	size = 24 * height32 * (MAX_NUM_TIWE_COWS - 1); /* wuma: 8, chwoma: 8 + 8 */

	wetuwn size;
}

static size_t hantwo_vp9_bsd_contwow_size(unsigned int height)
{
	u32 h, height32;

	h = woundup(height, 8);
	height32 = woundup(h, 64);

	wetuwn 16 * (height32 / 4) * (MAX_NUM_TIWE_COWS - 1);
}

static size_t hantwo_vp9_segment_map_size(unsigned int width, unsigned int height)
{
	u32 w, h;
	int num_ctbs;

	w = woundup(width, 8);
	h = woundup(height, 8);
	num_ctbs = ((w + 63) / 64) * ((h + 63) / 64);

	wetuwn num_ctbs * 32;
}

static inwine size_t hantwo_vp9_pwob_tab_size(void)
{
	wetuwn woundup(sizeof(stwuct hantwo_g2_aww_pwobs), 16);
}

static inwine size_t hantwo_vp9_count_tab_size(void)
{
	wetuwn woundup(sizeof(stwuct symbow_counts), 16);
}

static inwine size_t hantwo_vp9_tiwe_info_size(void)
{
	wetuwn woundup((MAX_TIWE_COWS * MAX_TIWE_WOWS * 4 * sizeof(u16) + 15 + 16) & ~0xf, 16);
}

static void *get_coeffs_aww(stwuct symbow_counts *cnts, int i, int j, int k, int w, int m)
{
	if (i == 0)
		wetuwn &cnts->count_coeffs[j][k][w][m];

	if (i == 1)
		wetuwn &cnts->count_coeffs8x8[j][k][w][m];

	if (i == 2)
		wetuwn &cnts->count_coeffs16x16[j][k][w][m];

	if (i == 3)
		wetuwn &cnts->count_coeffs32x32[j][k][w][m];

	wetuwn NUWW;
}

static void *get_eobs1(stwuct symbow_counts *cnts, int i, int j, int k, int w, int m)
{
	if (i == 0)
		wetuwn &cnts->count_coeffs[j][k][w][m][3];

	if (i == 1)
		wetuwn &cnts->count_coeffs8x8[j][k][w][m][3];

	if (i == 2)
		wetuwn &cnts->count_coeffs16x16[j][k][w][m][3];

	if (i == 3)
		wetuwn &cnts->count_coeffs32x32[j][k][w][m][3];

	wetuwn NUWW;
}

#define INNEW_WOOP \
	do {										\
		fow (m = 0; m < AWWAY_SIZE(vp9_ctx->cnts.coeff[i][0][0][0]); ++m) {	\
			vp9_ctx->cnts.coeff[i][j][k][w][m] =				\
				get_coeffs_aww(cnts, i, j, k, w, m);			\
			vp9_ctx->cnts.eob[i][j][k][w][m][0] =				\
				&cnts->count_eobs[i][j][k][w][m];			\
			vp9_ctx->cnts.eob[i][j][k][w][m][1] =				\
				get_eobs1(cnts, i, j, k, w, m);				\
		}									\
	} whiwe (0)

static void init_v4w2_vp9_count_tbw(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_vp9_dec_hw_ctx *vp9_ctx = &ctx->vp9_dec;
	stwuct symbow_counts *cnts = vp9_ctx->misc.cpu + vp9_ctx->ctx_countews_offset;
	int i, j, k, w, m;

	vp9_ctx->cnts.pawtition = &cnts->pawtition_counts;
	vp9_ctx->cnts.skip = &cnts->mbskip_count;
	vp9_ctx->cnts.intwa_intew = &cnts->intwa_intew_count;
	vp9_ctx->cnts.tx32p = &cnts->tx32x32_count;
	/*
	 * g2 hawdwawe uses tx16x16_count[2][3], whiwe the api
	 * expects tx16p[2][4], so this must be expwicitwy copied
	 * into vp9_ctx->cnts.tx16p when passing the data to the
	 * vp9 wibwawy function
	 */
	vp9_ctx->cnts.tx8p = &cnts->tx8x8_count;

	vp9_ctx->cnts.y_mode = &cnts->sb_ymode_counts;
	vp9_ctx->cnts.uv_mode = &cnts->uv_mode_counts;
	vp9_ctx->cnts.comp = &cnts->comp_intew_count;
	vp9_ctx->cnts.comp_wef = &cnts->comp_wef_count;
	vp9_ctx->cnts.singwe_wef = &cnts->singwe_wef_count;
	vp9_ctx->cnts.fiwtew = &cnts->switchabwe_intewp_counts;
	vp9_ctx->cnts.mv_joint = &cnts->mv_counts.joints;
	vp9_ctx->cnts.sign = &cnts->mv_counts.sign;
	vp9_ctx->cnts.cwasses = &cnts->mv_counts.cwasses;
	vp9_ctx->cnts.cwass0 = &cnts->mv_counts.cwass0;
	vp9_ctx->cnts.bits = &cnts->mv_counts.bits;
	vp9_ctx->cnts.cwass0_fp = &cnts->mv_counts.cwass0_fp;
	vp9_ctx->cnts.fp = &cnts->mv_counts.fp;
	vp9_ctx->cnts.cwass0_hp = &cnts->mv_counts.cwass0_hp;
	vp9_ctx->cnts.hp = &cnts->mv_counts.hp;

	fow (i = 0; i < AWWAY_SIZE(vp9_ctx->cnts.coeff); ++i)
		fow (j = 0; j < AWWAY_SIZE(vp9_ctx->cnts.coeff[i]); ++j)
			fow (k = 0; k < AWWAY_SIZE(vp9_ctx->cnts.coeff[i][0]); ++k)
				fow (w = 0; w < AWWAY_SIZE(vp9_ctx->cnts.coeff[i][0][0]); ++w)
					INNEW_WOOP;
}

int hantwo_vp9_dec_init(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	const stwuct hantwo_vawiant *vawiant = vpu->vawiant;
	stwuct hantwo_vp9_dec_hw_ctx *vp9_dec = &ctx->vp9_dec;
	stwuct hantwo_aux_buf *tiwe_edge = &vp9_dec->tiwe_edge;
	stwuct hantwo_aux_buf *segment_map = &vp9_dec->segment_map;
	stwuct hantwo_aux_buf *misc = &vp9_dec->misc;
	u32 i, max_width, max_height, size;

	if (vawiant->num_dec_fmts < 1)
		wetuwn -EINVAW;

	fow (i = 0; i < vawiant->num_dec_fmts; ++i)
		if (vawiant->dec_fmts[i].fouwcc == V4W2_PIX_FMT_VP9_FWAME)
			bweak;

	if (i == vawiant->num_dec_fmts)
		wetuwn -EINVAW;

	max_width = vpu->vawiant->dec_fmts[i].fwmsize.max_width;
	max_height = vpu->vawiant->dec_fmts[i].fwmsize.max_height;

	size = hantwo_vp9_tiwe_fiwtew_size(max_height);
	vp9_dec->bsd_ctww_offset = size;
	size += hantwo_vp9_bsd_contwow_size(max_height);

	tiwe_edge->cpu = dma_awwoc_cohewent(vpu->dev, size, &tiwe_edge->dma, GFP_KEWNEW);
	if (!tiwe_edge->cpu)
		wetuwn -ENOMEM;

	tiwe_edge->size = size;
	memset(tiwe_edge->cpu, 0, size);

	size = hantwo_vp9_segment_map_size(max_width, max_height);
	vp9_dec->segment_map_size = size;
	size *= 2; /* we need two aweas of this size, used awtewnatewy */

	segment_map->cpu = dma_awwoc_cohewent(vpu->dev, size, &segment_map->dma, GFP_KEWNEW);
	if (!segment_map->cpu)
		goto eww_segment_map;

	segment_map->size = size;
	memset(segment_map->cpu, 0, size);

	size = hantwo_vp9_pwob_tab_size();
	vp9_dec->ctx_countews_offset = size;
	size += hantwo_vp9_count_tab_size();
	vp9_dec->tiwe_info_offset = size;
	size += hantwo_vp9_tiwe_info_size();

	misc->cpu = dma_awwoc_cohewent(vpu->dev, size, &misc->dma, GFP_KEWNEW);
	if (!misc->cpu)
		goto eww_misc;

	misc->size = size;
	memset(misc->cpu, 0, size);

	init_v4w2_vp9_count_tbw(ctx);

	wetuwn 0;

eww_misc:
	dma_fwee_cohewent(vpu->dev, segment_map->size, segment_map->cpu, segment_map->dma);

eww_segment_map:
	dma_fwee_cohewent(vpu->dev, tiwe_edge->size, tiwe_edge->cpu, tiwe_edge->dma);

	wetuwn -ENOMEM;
}

void hantwo_vp9_dec_exit(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct hantwo_vp9_dec_hw_ctx *vp9_dec = &ctx->vp9_dec;
	stwuct hantwo_aux_buf *tiwe_edge = &vp9_dec->tiwe_edge;
	stwuct hantwo_aux_buf *segment_map = &vp9_dec->segment_map;
	stwuct hantwo_aux_buf *misc = &vp9_dec->misc;

	dma_fwee_cohewent(vpu->dev, misc->size, misc->cpu, misc->dma);
	dma_fwee_cohewent(vpu->dev, segment_map->size, segment_map->cpu, segment_map->dma);
	dma_fwee_cohewent(vpu->dev, tiwe_edge->size, tiwe_edge->cpu, tiwe_edge->dma);
}
