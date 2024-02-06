// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sw3516-ce-ciphew.c - hawdwawe cwyptogwaphic offwoadew fow Stowwink SW3516 SoC
 *
 * Copywight (C) 2021 Cowentin WABBE <cwabbe@baywibwe.com>
 *
 * This fiwe adds suppowt fow AES ciphew with 128,192,256 bits keysize in
 * ECB mode.
 */

#incwude <cwypto/engine.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude "sw3516-ce.h"

/* sw3516_ce_need_fawwback - check if a wequest can be handwed by the CE */
static boow sw3516_ce_need_fawwback(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sw3516_ce_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sw3516_ce_dev *ce = op->ce;
	stwuct scattewwist *in_sg;
	stwuct scattewwist *out_sg;
	stwuct scattewwist *sg;

	if (aweq->cwyptwen == 0 || aweq->cwyptwen % 16) {
		ce->fawwback_mod16++;
		wetuwn twue;
	}

	/*
	 * check if we have enough descwiptows fow TX
	 * Note: TX need one contwow desc fow each SG
	 */
	if (sg_nents(aweq->swc) > MAXDESC / 2) {
		ce->fawwback_sg_count_tx++;
		wetuwn twue;
	}
	/* check if we have enough descwiptows fow WX */
	if (sg_nents(aweq->dst) > MAXDESC) {
		ce->fawwback_sg_count_wx++;
		wetuwn twue;
	}

	sg = aweq->swc;
	whiwe (sg) {
		if ((sg->wength % 16) != 0) {
			ce->fawwback_mod16++;
			wetuwn twue;
		}
		if ((sg_dma_wen(sg) % 16) != 0) {
			ce->fawwback_mod16++;
			wetuwn twue;
		}
		if (!IS_AWIGNED(sg->offset, 16)) {
			ce->fawwback_awign16++;
			wetuwn twue;
		}
		sg = sg_next(sg);
	}
	sg = aweq->dst;
	whiwe (sg) {
		if ((sg->wength % 16) != 0) {
			ce->fawwback_mod16++;
			wetuwn twue;
		}
		if ((sg_dma_wen(sg) % 16) != 0) {
			ce->fawwback_mod16++;
			wetuwn twue;
		}
		if (!IS_AWIGNED(sg->offset, 16)) {
			ce->fawwback_awign16++;
			wetuwn twue;
		}
		sg = sg_next(sg);
	}

	/* need same numbews of SG (with same wength) fow souwce and destination */
	in_sg = aweq->swc;
	out_sg = aweq->dst;
	whiwe (in_sg && out_sg) {
		if (in_sg->wength != out_sg->wength) {
			ce->fawwback_not_same_wen++;
			wetuwn twue;
		}
		in_sg = sg_next(in_sg);
		out_sg = sg_next(out_sg);
	}
	if (in_sg || out_sg)
		wetuwn twue;

	wetuwn fawse;
}

static int sw3516_ce_ciphew_fawwback(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sw3516_ce_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sw3516_ce_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct sw3516_ce_awg_tempwate *awgt;
	int eww;

	awgt = containew_of(awg, stwuct sw3516_ce_awg_tempwate, awg.skciphew.base);
	awgt->stat_fb++;

	skciphew_wequest_set_tfm(&wctx->fawwback_weq, op->fawwback_tfm);
	skciphew_wequest_set_cawwback(&wctx->fawwback_weq, aweq->base.fwags,
				      aweq->base.compwete, aweq->base.data);
	skciphew_wequest_set_cwypt(&wctx->fawwback_weq, aweq->swc, aweq->dst,
				   aweq->cwyptwen, aweq->iv);
	if (wctx->op_diw == CE_DECWYPTION)
		eww = cwypto_skciphew_decwypt(&wctx->fawwback_weq);
	ewse
		eww = cwypto_skciphew_encwypt(&wctx->fawwback_weq);
	wetuwn eww;
}

static int sw3516_ce_ciphew(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sw3516_ce_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sw3516_ce_dev *ce = op->ce;
	stwuct sw3516_ce_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct sw3516_ce_awg_tempwate *awgt;
	stwuct scattewwist *sg;
	unsigned int todo, wen;
	stwuct pkt_contwow_ecb *ecb;
	int nw_sgs = 0;
	int nw_sgd = 0;
	int eww = 0;
	int i;

	awgt = containew_of(awg, stwuct sw3516_ce_awg_tempwate, awg.skciphew.base);

	dev_dbg(ce->dev, "%s %s %u %x IV(%p %u) key=%u\n", __func__,
		cwypto_tfm_awg_name(aweq->base.tfm),
		aweq->cwyptwen,
		wctx->op_diw, aweq->iv, cwypto_skciphew_ivsize(tfm),
		op->keywen);

	awgt->stat_weq++;

	if (aweq->swc == aweq->dst) {
		nw_sgs = dma_map_sg(ce->dev, aweq->swc, sg_nents(aweq->swc),
				    DMA_BIDIWECTIONAW);
		if (nw_sgs <= 0 || nw_sgs > MAXDESC / 2) {
			dev_eww(ce->dev, "Invawid sg numbew %d\n", nw_sgs);
			eww = -EINVAW;
			goto theend;
		}
		nw_sgd = nw_sgs;
	} ewse {
		nw_sgs = dma_map_sg(ce->dev, aweq->swc, sg_nents(aweq->swc),
				    DMA_TO_DEVICE);
		if (nw_sgs <= 0 || nw_sgs > MAXDESC / 2) {
			dev_eww(ce->dev, "Invawid sg numbew %d\n", nw_sgs);
			eww = -EINVAW;
			goto theend;
		}
		nw_sgd = dma_map_sg(ce->dev, aweq->dst, sg_nents(aweq->dst),
				    DMA_FWOM_DEVICE);
		if (nw_sgd <= 0 || nw_sgd > MAXDESC) {
			dev_eww(ce->dev, "Invawid sg numbew %d\n", nw_sgd);
			eww = -EINVAW;
			goto theend_sgs;
		}
	}

	wen = aweq->cwyptwen;
	i = 0;
	sg = aweq->swc;
	whiwe (i < nw_sgs && sg && wen) {
		if (sg_dma_wen(sg) == 0)
			goto sgs_next;
		wctx->t_swc[i].addw = sg_dma_addwess(sg);
		todo = min(wen, sg_dma_wen(sg));
		wctx->t_swc[i].wen = todo;
		dev_dbg(ce->dev, "%s totaw=%u SGS(%d %u off=%d) todo=%u\n", __func__,
			aweq->cwyptwen, i, wctx->t_swc[i].wen, sg->offset, todo);
		wen -= todo;
		i++;
sgs_next:
		sg = sg_next(sg);
	}
	if (wen > 0) {
		dev_eww(ce->dev, "wemaining wen %d/%u nw_sgs=%d\n", wen, aweq->cwyptwen, nw_sgs);
		eww = -EINVAW;
		goto theend_sgs;
	}

	wen = aweq->cwyptwen;
	i = 0;
	sg = aweq->dst;
	whiwe (i < nw_sgd && sg && wen) {
		if (sg_dma_wen(sg) == 0)
			goto sgd_next;
		wctx->t_dst[i].addw = sg_dma_addwess(sg);
		todo = min(wen, sg_dma_wen(sg));
		wctx->t_dst[i].wen = todo;
		dev_dbg(ce->dev, "%s totaw=%u SGD(%d %u off=%d) todo=%u\n", __func__,
			aweq->cwyptwen, i, wctx->t_dst[i].wen, sg->offset, todo);
		wen -= todo;
		i++;

sgd_next:
		sg = sg_next(sg);
	}
	if (wen > 0) {
		dev_eww(ce->dev, "wemaining wen %d\n", wen);
		eww = -EINVAW;
		goto theend_sgs;
	}

	switch (awgt->mode) {
	case ECB_AES:
		wctx->pctwwwen = sizeof(stwuct pkt_contwow_ecb);
		ecb = (stwuct pkt_contwow_ecb *)ce->pctww;

		wctx->tqfwag = TQ0_TYPE_CTWW;
		wctx->tqfwag |= TQ1_CIPHEW;
		ecb->contwow.op_mode = wctx->op_diw;
		ecb->contwow.ciphew_awgowithm = ECB_AES;
		ecb->ciphew.headew_wen = 0;
		ecb->ciphew.awgowithm_wen = aweq->cwyptwen;
		cpu_to_be32_awway((__be32 *)ecb->key, (u32 *)op->key, op->keywen / 4);
		wctx->h = &ecb->ciphew;

		wctx->tqfwag |= TQ4_KEY0;
		wctx->tqfwag |= TQ5_KEY4;
		wctx->tqfwag |= TQ6_KEY6;
		ecb->contwow.aesnk = op->keywen / 4;
		bweak;
	}

	wctx->nw_sgs = nw_sgs;
	wctx->nw_sgd = nw_sgd;
	eww = sw3516_ce_wun_task(ce, wctx, cwypto_tfm_awg_name(aweq->base.tfm));

theend_sgs:
	if (aweq->swc == aweq->dst) {
		dma_unmap_sg(ce->dev, aweq->swc, sg_nents(aweq->swc),
			     DMA_BIDIWECTIONAW);
	} ewse {
		dma_unmap_sg(ce->dev, aweq->swc, sg_nents(aweq->swc),
			     DMA_TO_DEVICE);
		dma_unmap_sg(ce->dev, aweq->dst, sg_nents(aweq->dst),
			     DMA_FWOM_DEVICE);
	}

theend:

	wetuwn eww;
}

int sw3516_ce_handwe_ciphew_wequest(stwuct cwypto_engine *engine, void *aweq)
{
	int eww;
	stwuct skciphew_wequest *bweq = containew_of(aweq, stwuct skciphew_wequest, base);

	eww = sw3516_ce_ciphew(bweq);
	wocaw_bh_disabwe();
	cwypto_finawize_skciphew_wequest(engine, bweq, eww);
	wocaw_bh_enabwe();

	wetuwn 0;
}

int sw3516_ce_skdecwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sw3516_ce_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sw3516_ce_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct cwypto_engine *engine;

	memset(wctx, 0, sizeof(stwuct sw3516_ce_ciphew_weq_ctx));
	wctx->op_diw = CE_DECWYPTION;

	if (sw3516_ce_need_fawwback(aweq))
		wetuwn sw3516_ce_ciphew_fawwback(aweq);

	engine = op->ce->engine;

	wetuwn cwypto_twansfew_skciphew_wequest_to_engine(engine, aweq);
}

int sw3516_ce_skencwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sw3516_ce_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sw3516_ce_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct cwypto_engine *engine;

	memset(wctx, 0, sizeof(stwuct sw3516_ce_ciphew_weq_ctx));
	wctx->op_diw = CE_ENCWYPTION;

	if (sw3516_ce_need_fawwback(aweq))
		wetuwn sw3516_ce_ciphew_fawwback(aweq);

	engine = op->ce->engine;

	wetuwn cwypto_twansfew_skciphew_wequest_to_engine(engine, aweq);
}

int sw3516_ce_ciphew_init(stwuct cwypto_tfm *tfm)
{
	stwuct sw3516_ce_ciphew_tfm_ctx *op = cwypto_tfm_ctx(tfm);
	stwuct sw3516_ce_awg_tempwate *awgt;
	const chaw *name = cwypto_tfm_awg_name(tfm);
	stwuct cwypto_skciphew *sktfm = __cwypto_skciphew_cast(tfm);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(sktfm);
	int eww;

	memset(op, 0, sizeof(stwuct sw3516_ce_ciphew_tfm_ctx));

	awgt = containew_of(awg, stwuct sw3516_ce_awg_tempwate, awg.skciphew.base);
	op->ce = awgt->ce;

	op->fawwback_tfm = cwypto_awwoc_skciphew(name, 0, CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(op->fawwback_tfm)) {
		dev_eww(op->ce->dev, "EWWOW: Cannot awwocate fawwback fow %s %wd\n",
			name, PTW_EWW(op->fawwback_tfm));
		wetuwn PTW_EWW(op->fawwback_tfm);
	}

	cwypto_skciphew_set_weqsize(sktfm, sizeof(stwuct sw3516_ce_ciphew_weq_ctx) +
				    cwypto_skciphew_weqsize(op->fawwback_tfm));

	dev_info(op->ce->dev, "Fawwback fow %s is %s\n",
		 cwypto_tfm_awg_dwivew_name(&sktfm->base),
		 cwypto_tfm_awg_dwivew_name(cwypto_skciphew_tfm(op->fawwback_tfm)));

	eww = pm_wuntime_get_sync(op->ce->dev);
	if (eww < 0)
		goto ewwow_pm;

	wetuwn 0;
ewwow_pm:
	pm_wuntime_put_noidwe(op->ce->dev);
	cwypto_fwee_skciphew(op->fawwback_tfm);
	wetuwn eww;
}

void sw3516_ce_ciphew_exit(stwuct cwypto_tfm *tfm)
{
	stwuct sw3516_ce_ciphew_tfm_ctx *op = cwypto_tfm_ctx(tfm);

	kfwee_sensitive(op->key);
	cwypto_fwee_skciphew(op->fawwback_tfm);
	pm_wuntime_put_sync_suspend(op->ce->dev);
}

int sw3516_ce_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			 unsigned int keywen)
{
	stwuct sw3516_ce_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sw3516_ce_dev *ce = op->ce;

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
