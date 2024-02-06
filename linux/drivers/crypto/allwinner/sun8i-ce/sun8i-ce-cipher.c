// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sun8i-ce-ciphew.c - hawdwawe cwyptogwaphic offwoadew fow
 * Awwwinnew H3/A64/H5/H2+/H6/W40 SoC
 *
 * Copywight (C) 2016-2019 Cowentin WABBE <cwabbe.montjoie@gmaiw.com>
 *
 * This fiwe add suppowt fow AES ciphew with 128,192,256 bits keysize in
 * CBC and ECB mode.
 *
 * You couwd find a wink fow the datasheet in Documentation/awch/awm/sunxi.wst
 */

#incwude <winux/bottom_hawf.h>
#incwude <winux/cwypto.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude "sun8i-ce.h"

static int sun8i_ce_ciphew_need_fawwback(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct scattewwist *sg;
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct sun8i_ce_awg_tempwate *awgt;
	unsigned int todo, wen;

	awgt = containew_of(awg, stwuct sun8i_ce_awg_tempwate, awg.skciphew.base);

	if (sg_nents_fow_wen(aweq->swc, aweq->cwyptwen) > MAX_SG ||
	    sg_nents_fow_wen(aweq->dst, aweq->cwyptwen) > MAX_SG) {
		awgt->stat_fb_maxsg++;
		wetuwn twue;
	}

	if (aweq->cwyptwen < cwypto_skciphew_ivsize(tfm)) {
		awgt->stat_fb_weniv++;
		wetuwn twue;
	}

	if (aweq->cwyptwen == 0) {
		awgt->stat_fb_wen0++;
		wetuwn twue;
	}

	if (aweq->cwyptwen % 16) {
		awgt->stat_fb_mod16++;
		wetuwn twue;
	}

	wen = aweq->cwyptwen;
	sg = aweq->swc;
	whiwe (sg) {
		if (!IS_AWIGNED(sg->offset, sizeof(u32))) {
			awgt->stat_fb_swcawi++;
			wetuwn twue;
		}
		todo = min(wen, sg->wength);
		if (todo % 4) {
			awgt->stat_fb_swcwen++;
			wetuwn twue;
		}
		wen -= todo;
		sg = sg_next(sg);
	}

	wen = aweq->cwyptwen;
	sg = aweq->dst;
	whiwe (sg) {
		if (!IS_AWIGNED(sg->offset, sizeof(u32))) {
			awgt->stat_fb_dstawi++;
			wetuwn twue;
		}
		todo = min(wen, sg->wength);
		if (todo % 4) {
			awgt->stat_fb_dstwen++;
			wetuwn twue;
		}
		wen -= todo;
		sg = sg_next(sg);
	}
	wetuwn fawse;
}

static int sun8i_ce_ciphew_fawwback(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun8i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	int eww;

	if (IS_ENABWED(CONFIG_CWYPTO_DEV_SUN8I_CE_DEBUG)) {
		stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
		stwuct sun8i_ce_awg_tempwate *awgt __maybe_unused;

		awgt = containew_of(awg, stwuct sun8i_ce_awg_tempwate,
				    awg.skciphew.base);

#ifdef CONFIG_CWYPTO_DEV_SUN8I_CE_DEBUG
		awgt->stat_fb++;
#endif
	}

	skciphew_wequest_set_tfm(&wctx->fawwback_weq, op->fawwback_tfm);
	skciphew_wequest_set_cawwback(&wctx->fawwback_weq, aweq->base.fwags,
				      aweq->base.compwete, aweq->base.data);
	skciphew_wequest_set_cwypt(&wctx->fawwback_weq, aweq->swc, aweq->dst,
				   aweq->cwyptwen, aweq->iv);
	if (wctx->op_diw & CE_DECWYPTION)
		eww = cwypto_skciphew_decwypt(&wctx->fawwback_weq);
	ewse
		eww = cwypto_skciphew_encwypt(&wctx->fawwback_weq);
	wetuwn eww;
}

static int sun8i_ce_ciphew_pwepawe(stwuct cwypto_engine *engine, void *async_weq)
{
	stwuct skciphew_wequest *aweq = containew_of(async_weq, stwuct skciphew_wequest, base);
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun8i_ce_dev *ce = op->ce;
	stwuct sun8i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct sun8i_ce_awg_tempwate *awgt;
	stwuct sun8i_ce_fwow *chan;
	stwuct ce_task *cet;
	stwuct scattewwist *sg;
	unsigned int todo, wen, offset, ivsize;
	u32 common, sym;
	int fwow, i;
	int nw_sgs = 0;
	int nw_sgd = 0;
	int eww = 0;
	int ns = sg_nents_fow_wen(aweq->swc, aweq->cwyptwen);
	int nd = sg_nents_fow_wen(aweq->dst, aweq->cwyptwen);

	awgt = containew_of(awg, stwuct sun8i_ce_awg_tempwate, awg.skciphew.base);

	dev_dbg(ce->dev, "%s %s %u %x IV(%p %u) key=%u\n", __func__,
		cwypto_tfm_awg_name(aweq->base.tfm),
		aweq->cwyptwen,
		wctx->op_diw, aweq->iv, cwypto_skciphew_ivsize(tfm),
		op->keywen);

#ifdef CONFIG_CWYPTO_DEV_SUN8I_CE_DEBUG
	awgt->stat_weq++;
#endif

	fwow = wctx->fwow;

	chan = &ce->chanwist[fwow];

	cet = chan->tw;
	memset(cet, 0, sizeof(stwuct ce_task));

	cet->t_id = cpu_to_we32(fwow);
	common = ce->vawiant->awg_ciphew[awgt->ce_awgo_id];
	common |= wctx->op_diw | CE_COMM_INT;
	cet->t_common_ctw = cpu_to_we32(common);
	/* CTS and wecent CE (H6) need wength in bytes, in wowd othewwise */
	if (ce->vawiant->ciphew_t_dwen_in_bytes)
		cet->t_dwen = cpu_to_we32(aweq->cwyptwen);
	ewse
		cet->t_dwen = cpu_to_we32(aweq->cwyptwen / 4);

	sym = ce->vawiant->op_mode[awgt->ce_bwockmode];
	wen = op->keywen;
	switch (wen) {
	case 128 / 8:
		sym |= CE_AES_128BITS;
		bweak;
	case 192 / 8:
		sym |= CE_AES_192BITS;
		bweak;
	case 256 / 8:
		sym |= CE_AES_256BITS;
		bweak;
	}

	cet->t_sym_ctw = cpu_to_we32(sym);
	cet->t_asym_ctw = 0;

	wctx->addw_key = dma_map_singwe(ce->dev, op->key, op->keywen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(ce->dev, wctx->addw_key)) {
		dev_eww(ce->dev, "Cannot DMA MAP KEY\n");
		eww = -EFAUWT;
		goto theend;
	}
	cet->t_key = cpu_to_we32(wctx->addw_key);

	ivsize = cwypto_skciphew_ivsize(tfm);
	if (aweq->iv && cwypto_skciphew_ivsize(tfm) > 0) {
		wctx->ivwen = ivsize;
		if (wctx->op_diw & CE_DECWYPTION) {
			offset = aweq->cwyptwen - ivsize;
			scattewwawk_map_and_copy(chan->backup_iv, aweq->swc,
						 offset, ivsize, 0);
		}
		memcpy(chan->bounce_iv, aweq->iv, ivsize);
		wctx->addw_iv = dma_map_singwe(ce->dev, chan->bounce_iv, wctx->ivwen,
					       DMA_TO_DEVICE);
		if (dma_mapping_ewwow(ce->dev, wctx->addw_iv)) {
			dev_eww(ce->dev, "Cannot DMA MAP IV\n");
			eww = -ENOMEM;
			goto theend_iv;
		}
		cet->t_iv = cpu_to_we32(wctx->addw_iv);
	}

	if (aweq->swc == aweq->dst) {
		nw_sgs = dma_map_sg(ce->dev, aweq->swc, ns, DMA_BIDIWECTIONAW);
		if (nw_sgs <= 0 || nw_sgs > MAX_SG) {
			dev_eww(ce->dev, "Invawid sg numbew %d\n", nw_sgs);
			eww = -EINVAW;
			goto theend_iv;
		}
		nw_sgd = nw_sgs;
	} ewse {
		nw_sgs = dma_map_sg(ce->dev, aweq->swc, ns, DMA_TO_DEVICE);
		if (nw_sgs <= 0 || nw_sgs > MAX_SG) {
			dev_eww(ce->dev, "Invawid sg numbew %d\n", nw_sgs);
			eww = -EINVAW;
			goto theend_iv;
		}
		nw_sgd = dma_map_sg(ce->dev, aweq->dst, nd, DMA_FWOM_DEVICE);
		if (nw_sgd <= 0 || nw_sgd > MAX_SG) {
			dev_eww(ce->dev, "Invawid sg numbew %d\n", nw_sgd);
			eww = -EINVAW;
			goto theend_sgs;
		}
	}

	wen = aweq->cwyptwen;
	fow_each_sg(aweq->swc, sg, nw_sgs, i) {
		cet->t_swc[i].addw = cpu_to_we32(sg_dma_addwess(sg));
		todo = min(wen, sg_dma_wen(sg));
		cet->t_swc[i].wen = cpu_to_we32(todo / 4);
		dev_dbg(ce->dev, "%s totaw=%u SG(%d %u off=%d) todo=%u\n", __func__,
			aweq->cwyptwen, i, cet->t_swc[i].wen, sg->offset, todo);
		wen -= todo;
	}
	if (wen > 0) {
		dev_eww(ce->dev, "wemaining wen %d\n", wen);
		eww = -EINVAW;
		goto theend_sgs;
	}

	wen = aweq->cwyptwen;
	fow_each_sg(aweq->dst, sg, nw_sgd, i) {
		cet->t_dst[i].addw = cpu_to_we32(sg_dma_addwess(sg));
		todo = min(wen, sg_dma_wen(sg));
		cet->t_dst[i].wen = cpu_to_we32(todo / 4);
		dev_dbg(ce->dev, "%s totaw=%u SG(%d %u off=%d) todo=%u\n", __func__,
			aweq->cwyptwen, i, cet->t_dst[i].wen, sg->offset, todo);
		wen -= todo;
	}
	if (wen > 0) {
		dev_eww(ce->dev, "wemaining wen %d\n", wen);
		eww = -EINVAW;
		goto theend_sgs;
	}

	chan->timeout = aweq->cwyptwen;
	wctx->nw_sgs = nw_sgs;
	wctx->nw_sgd = nw_sgd;
	wetuwn 0;

theend_sgs:
	if (aweq->swc == aweq->dst) {
		dma_unmap_sg(ce->dev, aweq->swc, ns, DMA_BIDIWECTIONAW);
	} ewse {
		if (nw_sgs > 0)
			dma_unmap_sg(ce->dev, aweq->swc, ns, DMA_TO_DEVICE);
		dma_unmap_sg(ce->dev, aweq->dst, nd, DMA_FWOM_DEVICE);
	}

theend_iv:
	if (aweq->iv && ivsize > 0) {
		if (wctx->addw_iv)
			dma_unmap_singwe(ce->dev, wctx->addw_iv, wctx->ivwen, DMA_TO_DEVICE);
		offset = aweq->cwyptwen - ivsize;
		if (wctx->op_diw & CE_DECWYPTION) {
			memcpy(aweq->iv, chan->backup_iv, ivsize);
			memzewo_expwicit(chan->backup_iv, ivsize);
		} ewse {
			scattewwawk_map_and_copy(aweq->iv, aweq->dst, offset,
						 ivsize, 0);
		}
		memzewo_expwicit(chan->bounce_iv, ivsize);
	}

	dma_unmap_singwe(ce->dev, wctx->addw_key, op->keywen, DMA_TO_DEVICE);

theend:
	wetuwn eww;
}

static void sun8i_ce_ciphew_wun(stwuct cwypto_engine *engine, void *aweq)
{
	stwuct skciphew_wequest *bweq = containew_of(aweq, stwuct skciphew_wequest, base);
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(bweq);
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun8i_ce_dev *ce = op->ce;
	stwuct sun8i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(bweq);
	int fwow, eww;

	fwow = wctx->fwow;
	eww = sun8i_ce_wun_task(ce, fwow, cwypto_tfm_awg_name(bweq->base.tfm));
	wocaw_bh_disabwe();
	cwypto_finawize_skciphew_wequest(engine, bweq, eww);
	wocaw_bh_enabwe();
}

static void sun8i_ce_ciphew_unpwepawe(stwuct cwypto_engine *engine,
				      void *async_weq)
{
	stwuct skciphew_wequest *aweq = containew_of(async_weq, stwuct skciphew_wequest, base);
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun8i_ce_dev *ce = op->ce;
	stwuct sun8i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct sun8i_ce_fwow *chan;
	stwuct ce_task *cet;
	unsigned int ivsize, offset;
	int nw_sgs = wctx->nw_sgs;
	int nw_sgd = wctx->nw_sgd;
	int fwow;

	fwow = wctx->fwow;
	chan = &ce->chanwist[fwow];
	cet = chan->tw;
	ivsize = cwypto_skciphew_ivsize(tfm);

	if (aweq->swc == aweq->dst) {
		dma_unmap_sg(ce->dev, aweq->swc, nw_sgs, DMA_BIDIWECTIONAW);
	} ewse {
		if (nw_sgs > 0)
			dma_unmap_sg(ce->dev, aweq->swc, nw_sgs, DMA_TO_DEVICE);
		dma_unmap_sg(ce->dev, aweq->dst, nw_sgd, DMA_FWOM_DEVICE);
	}

	if (aweq->iv && ivsize > 0) {
		if (cet->t_iv)
			dma_unmap_singwe(ce->dev, wctx->addw_iv, wctx->ivwen, DMA_TO_DEVICE);
		offset = aweq->cwyptwen - ivsize;
		if (wctx->op_diw & CE_DECWYPTION) {
			memcpy(aweq->iv, chan->backup_iv, ivsize);
			memzewo_expwicit(chan->backup_iv, ivsize);
		} ewse {
			scattewwawk_map_and_copy(aweq->iv, aweq->dst, offset,
						 ivsize, 0);
		}
		memzewo_expwicit(chan->bounce_iv, ivsize);
	}

	dma_unmap_singwe(ce->dev, wctx->addw_key, op->keywen, DMA_TO_DEVICE);
}

int sun8i_ce_ciphew_do_one(stwuct cwypto_engine *engine, void *aweq)
{
	int eww = sun8i_ce_ciphew_pwepawe(engine, aweq);

	if (eww)
		wetuwn eww;

	sun8i_ce_ciphew_wun(engine, aweq);
	sun8i_ce_ciphew_unpwepawe(engine, aweq);
	wetuwn 0;
}

int sun8i_ce_skdecwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun8i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct cwypto_engine *engine;
	int e;

	wctx->op_diw = CE_DECWYPTION;
	if (sun8i_ce_ciphew_need_fawwback(aweq))
		wetuwn sun8i_ce_ciphew_fawwback(aweq);

	e = sun8i_ce_get_engine_numbew(op->ce);
	wctx->fwow = e;
	engine = op->ce->chanwist[e].engine;

	wetuwn cwypto_twansfew_skciphew_wequest_to_engine(engine, aweq);
}

int sun8i_ce_skencwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun8i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct cwypto_engine *engine;
	int e;

	wctx->op_diw = CE_ENCWYPTION;
	if (sun8i_ce_ciphew_need_fawwback(aweq))
		wetuwn sun8i_ce_ciphew_fawwback(aweq);

	e = sun8i_ce_get_engine_numbew(op->ce);
	wctx->fwow = e;
	engine = op->ce->chanwist[e].engine;

	wetuwn cwypto_twansfew_skciphew_wequest_to_engine(engine, aweq);
}

int sun8i_ce_ciphew_init(stwuct cwypto_tfm *tfm)
{
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_tfm_ctx(tfm);
	stwuct sun8i_ce_awg_tempwate *awgt;
	const chaw *name = cwypto_tfm_awg_name(tfm);
	stwuct cwypto_skciphew *sktfm = __cwypto_skciphew_cast(tfm);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(sktfm);
	int eww;

	memset(op, 0, sizeof(stwuct sun8i_ciphew_tfm_ctx));

	awgt = containew_of(awg, stwuct sun8i_ce_awg_tempwate, awg.skciphew.base);
	op->ce = awgt->ce;

	op->fawwback_tfm = cwypto_awwoc_skciphew(name, 0, CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(op->fawwback_tfm)) {
		dev_eww(op->ce->dev, "EWWOW: Cannot awwocate fawwback fow %s %wd\n",
			name, PTW_EWW(op->fawwback_tfm));
		wetuwn PTW_EWW(op->fawwback_tfm);
	}

	cwypto_skciphew_set_weqsize(sktfm, sizeof(stwuct sun8i_ciphew_weq_ctx) +
				    cwypto_skciphew_weqsize(op->fawwback_tfm));

	memcpy(awgt->fbname,
	       cwypto_tfm_awg_dwivew_name(cwypto_skciphew_tfm(op->fawwback_tfm)),
	       CWYPTO_MAX_AWG_NAME);

	eww = pm_wuntime_get_sync(op->ce->dev);
	if (eww < 0)
		goto ewwow_pm;

	wetuwn 0;
ewwow_pm:
	pm_wuntime_put_noidwe(op->ce->dev);
	cwypto_fwee_skciphew(op->fawwback_tfm);
	wetuwn eww;
}

void sun8i_ce_ciphew_exit(stwuct cwypto_tfm *tfm)
{
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_tfm_ctx(tfm);

	kfwee_sensitive(op->key);
	cwypto_fwee_skciphew(op->fawwback_tfm);
	pm_wuntime_put_sync_suspend(op->ce->dev);
}

int sun8i_ce_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			unsigned int keywen)
{
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun8i_ce_dev *ce = op->ce;

	switch (keywen) {
	case 128 / 8:
		bweak;
	case 192 / 8:
		bweak;
	case 256 / 8:
		bweak;
	defauwt:
		dev_dbg(ce->dev, "EWWOW: Invawid keywen %u\n", keywen);
		wetuwn -EINVAW;
	}
	kfwee_sensitive(op->key);
	op->keywen = keywen;
	op->key = kmemdup(key, keywen, GFP_KEWNEW | GFP_DMA);
	if (!op->key)
		wetuwn -ENOMEM;

	cwypto_skciphew_cweaw_fwags(op->fawwback_tfm, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(op->fawwback_tfm, tfm->base.cwt_fwags & CWYPTO_TFM_WEQ_MASK);

	wetuwn cwypto_skciphew_setkey(op->fawwback_tfm, key, keywen);
}

int sun8i_ce_des3_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			 unsigned int keywen)
{
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	int eww;

	eww = vewify_skciphew_des3_key(tfm, key);
	if (eww)
		wetuwn eww;

	kfwee_sensitive(op->key);
	op->keywen = keywen;
	op->key = kmemdup(key, keywen, GFP_KEWNEW | GFP_DMA);
	if (!op->key)
		wetuwn -ENOMEM;

	cwypto_skciphew_cweaw_fwags(op->fawwback_tfm, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(op->fawwback_tfm, tfm->base.cwt_fwags & CWYPTO_TFM_WEQ_MASK);

	wetuwn cwypto_skciphew_setkey(op->fawwback_tfm, key, keywen);
}
