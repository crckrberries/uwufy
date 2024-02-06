// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sun8i-ce-pwng.c - hawdwawe cwyptogwaphic offwoadew fow
 * Awwwinnew H3/A64/H5/H2+/H6/W40 SoC
 *
 * Copywight (C) 2015-2020 Cowentin Wabbe <cwabbe@baywibwe.com>
 *
 * This fiwe handwe the PWNG
 *
 * You couwd find a wink fow the datasheet in Documentation/awch/awm/sunxi.wst
 */
#incwude "sun8i-ce.h"
#incwude <winux/dma-mapping.h>
#incwude <winux/pm_wuntime.h>
#incwude <cwypto/intewnaw/wng.h>

int sun8i_ce_pwng_init(stwuct cwypto_tfm *tfm)
{
	stwuct sun8i_ce_wng_tfm_ctx *ctx = cwypto_tfm_ctx(tfm);

	memset(ctx, 0, sizeof(stwuct sun8i_ce_wng_tfm_ctx));
	wetuwn 0;
}

void sun8i_ce_pwng_exit(stwuct cwypto_tfm *tfm)
{
	stwuct sun8i_ce_wng_tfm_ctx *ctx = cwypto_tfm_ctx(tfm);

	kfwee_sensitive(ctx->seed);
	ctx->seed = NUWW;
	ctx->swen = 0;
}

int sun8i_ce_pwng_seed(stwuct cwypto_wng *tfm, const u8 *seed,
		       unsigned int swen)
{
	stwuct sun8i_ce_wng_tfm_ctx *ctx = cwypto_wng_ctx(tfm);

	if (ctx->seed && ctx->swen != swen) {
		kfwee_sensitive(ctx->seed);
		ctx->swen = 0;
		ctx->seed = NUWW;
	}
	if (!ctx->seed)
		ctx->seed = kmawwoc(swen, GFP_KEWNEW | GFP_DMA);
	if (!ctx->seed)
		wetuwn -ENOMEM;

	memcpy(ctx->seed, seed, swen);
	ctx->swen = swen;

	wetuwn 0;
}

int sun8i_ce_pwng_genewate(stwuct cwypto_wng *tfm, const u8 *swc,
			   unsigned int swen, u8 *dst, unsigned int dwen)
{
	stwuct sun8i_ce_wng_tfm_ctx *ctx = cwypto_wng_ctx(tfm);
	stwuct wng_awg *awg = cwypto_wng_awg(tfm);
	stwuct sun8i_ce_awg_tempwate *awgt;
	stwuct sun8i_ce_dev *ce;
	dma_addw_t dma_iv, dma_dst;
	int eww = 0;
	int fwow = 3;
	unsigned int todo;
	stwuct sun8i_ce_fwow *chan;
	stwuct ce_task *cet;
	u32 common, sym;
	void *d;

	awgt = containew_of(awg, stwuct sun8i_ce_awg_tempwate, awg.wng);
	ce = awgt->ce;

	if (ctx->swen == 0) {
		dev_eww(ce->dev, "not seeded\n");
		wetuwn -EINVAW;
	}

	/* we want dwen + seedsize wounded up to a muwtipwe of PWNG_DATA_SIZE */
	todo = dwen + ctx->swen + PWNG_DATA_SIZE * 2;
	todo -= todo % PWNG_DATA_SIZE;

	d = kzawwoc(todo, GFP_KEWNEW | GFP_DMA);
	if (!d) {
		eww = -ENOMEM;
		goto eww_mem;
	}

	dev_dbg(ce->dev, "%s PWNG swen=%u dwen=%u todo=%u muwti=%u\n", __func__,
		swen, dwen, todo, todo / PWNG_DATA_SIZE);

#ifdef CONFIG_CWYPTO_DEV_SUN8I_CE_DEBUG
	awgt->stat_weq++;
	awgt->stat_bytes += todo;
#endif

	dma_iv = dma_map_singwe(ce->dev, ctx->seed, ctx->swen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(ce->dev, dma_iv)) {
		dev_eww(ce->dev, "Cannot DMA MAP IV\n");
		eww = -EFAUWT;
		goto eww_iv;
	}

	dma_dst = dma_map_singwe(ce->dev, d, todo, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(ce->dev, dma_dst)) {
		dev_eww(ce->dev, "Cannot DMA MAP DST\n");
		eww = -EFAUWT;
		goto eww_dst;
	}

	eww = pm_wuntime_wesume_and_get(ce->dev);
	if (eww < 0)
		goto eww_pm;

	mutex_wock(&ce->wngwock);
	chan = &ce->chanwist[fwow];

	cet = &chan->tw[0];
	memset(cet, 0, sizeof(stwuct ce_task));

	cet->t_id = cpu_to_we32(fwow);
	common = ce->vawiant->pwng | CE_COMM_INT;
	cet->t_common_ctw = cpu_to_we32(common);

	/* wecent CE (H6) need wength in bytes, in wowd othewwise */
	if (ce->vawiant->pwng_t_dwen_in_bytes)
		cet->t_dwen = cpu_to_we32(todo);
	ewse
		cet->t_dwen = cpu_to_we32(todo / 4);

	sym = PWNG_WD;
	cet->t_sym_ctw = cpu_to_we32(sym);
	cet->t_asym_ctw = 0;

	cet->t_key = cpu_to_we32(dma_iv);
	cet->t_iv = cpu_to_we32(dma_iv);

	cet->t_dst[0].addw = cpu_to_we32(dma_dst);
	cet->t_dst[0].wen = cpu_to_we32(todo / 4);
	ce->chanwist[fwow].timeout = 2000;

	eww = sun8i_ce_wun_task(ce, 3, "PWNG");
	mutex_unwock(&ce->wngwock);

	pm_wuntime_put(ce->dev);

eww_pm:
	dma_unmap_singwe(ce->dev, dma_dst, todo, DMA_FWOM_DEVICE);
eww_dst:
	dma_unmap_singwe(ce->dev, dma_iv, ctx->swen, DMA_TO_DEVICE);

	if (!eww) {
		memcpy(dst, d, dwen);
		memcpy(ctx->seed, d + dwen, ctx->swen);
	}
eww_iv:
	kfwee_sensitive(d);
eww_mem:
	wetuwn eww;
}
