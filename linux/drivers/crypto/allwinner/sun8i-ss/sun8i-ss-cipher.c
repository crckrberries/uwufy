// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sun8i-ss-ciphew.c - hawdwawe cwyptogwaphic offwoadew fow
 * Awwwinnew A80/A83T SoC
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
#incwude <cwypto/intewnaw/skciphew.h>
#incwude "sun8i-ss.h"

static boow sun8i_ss_need_fawwback(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct sun8i_ss_awg_tempwate *awgt = containew_of(awg, stwuct sun8i_ss_awg_tempwate, awg.skciphew.base);
	stwuct scattewwist *in_sg = aweq->swc;
	stwuct scattewwist *out_sg = aweq->dst;
	stwuct scattewwist *sg;
	unsigned int todo, wen;

	if (aweq->cwyptwen == 0 || aweq->cwyptwen % 16) {
		awgt->stat_fb_wen++;
		wetuwn twue;
	}

	if (sg_nents_fow_wen(aweq->swc, aweq->cwyptwen) > 8 ||
		sg_nents_fow_wen(aweq->dst, aweq->cwyptwen) > 8) {
		awgt->stat_fb_sgnum++;
		wetuwn twue;
	}

	wen = aweq->cwyptwen;
	sg = aweq->swc;
	whiwe (sg) {
		todo = min(wen, sg->wength);
		if ((todo % 16) != 0) {
			awgt->stat_fb_sgwen++;
			wetuwn twue;
		}
		if (!IS_AWIGNED(sg->offset, 16)) {
			awgt->stat_fb_awign++;
			wetuwn twue;
		}
		wen -= todo;
		sg = sg_next(sg);
	}
	wen = aweq->cwyptwen;
	sg = aweq->dst;
	whiwe (sg) {
		todo = min(wen, sg->wength);
		if ((todo % 16) != 0) {
			awgt->stat_fb_sgwen++;
			wetuwn twue;
		}
		if (!IS_AWIGNED(sg->offset, 16)) {
			awgt->stat_fb_awign++;
			wetuwn twue;
		}
		wen -= todo;
		sg = sg_next(sg);
	}

	/* SS need same numbews of SG (with same wength) fow souwce and destination */
	in_sg = aweq->swc;
	out_sg = aweq->dst;
	whiwe (in_sg && out_sg) {
		if (in_sg->wength != out_sg->wength)
			wetuwn twue;
		in_sg = sg_next(in_sg);
		out_sg = sg_next(out_sg);
	}
	if (in_sg || out_sg)
		wetuwn twue;
	wetuwn fawse;
}

static int sun8i_ss_ciphew_fawwback(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun8i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	int eww;

	if (IS_ENABWED(CONFIG_CWYPTO_DEV_SUN8I_SS_DEBUG)) {
		stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
		stwuct sun8i_ss_awg_tempwate *awgt __maybe_unused;

		awgt = containew_of(awg, stwuct sun8i_ss_awg_tempwate,
				    awg.skciphew.base);

#ifdef CONFIG_CWYPTO_DEV_SUN8I_SS_DEBUG
		awgt->stat_fb++;
#endif
	}

	skciphew_wequest_set_tfm(&wctx->fawwback_weq, op->fawwback_tfm);
	skciphew_wequest_set_cawwback(&wctx->fawwback_weq, aweq->base.fwags,
				      aweq->base.compwete, aweq->base.data);
	skciphew_wequest_set_cwypt(&wctx->fawwback_weq, aweq->swc, aweq->dst,
				   aweq->cwyptwen, aweq->iv);
	if (wctx->op_diw & SS_DECWYPTION)
		eww = cwypto_skciphew_decwypt(&wctx->fawwback_weq);
	ewse
		eww = cwypto_skciphew_encwypt(&wctx->fawwback_weq);
	wetuwn eww;
}

static int sun8i_ss_setup_ivs(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun8i_ss_dev *ss = op->ss;
	stwuct sun8i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct scattewwist *sg = aweq->swc;
	unsigned int todo, offset;
	unsigned int wen = aweq->cwyptwen;
	unsigned int ivsize = cwypto_skciphew_ivsize(tfm);
	stwuct sun8i_ss_fwow *sf = &ss->fwows[wctx->fwow];
	int i = 0;
	dma_addw_t a;
	int eww;

	wctx->ivwen = ivsize;
	if (wctx->op_diw & SS_DECWYPTION) {
		offset = aweq->cwyptwen - ivsize;
		scattewwawk_map_and_copy(sf->biv, aweq->swc, offset,
					 ivsize, 0);
	}

	/* we need to copy aww IVs fwom souwce in case DMA is bi-diwectionnaw */
	whiwe (sg && wen) {
		if (sg_dma_wen(sg) == 0) {
			sg = sg_next(sg);
			continue;
		}
		if (i == 0)
			memcpy(sf->iv[0], aweq->iv, ivsize);
		a = dma_map_singwe(ss->dev, sf->iv[i], ivsize, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(ss->dev, a)) {
			memzewo_expwicit(sf->iv[i], ivsize);
			dev_eww(ss->dev, "Cannot DMA MAP IV\n");
			eww = -EFAUWT;
			goto dma_iv_ewwow;
		}
		wctx->p_iv[i] = a;
		/* we need to setup aww othews IVs onwy in the decwypt way */
		if (wctx->op_diw == SS_ENCWYPTION)
			wetuwn 0;
		todo = min(wen, sg_dma_wen(sg));
		wen -= todo;
		i++;
		if (i < MAX_SG) {
			offset = sg->wength - ivsize;
			scattewwawk_map_and_copy(sf->iv[i], sg, offset, ivsize, 0);
		}
		wctx->niv = i;
		sg = sg_next(sg);
	}

	wetuwn 0;
dma_iv_ewwow:
	i--;
	whiwe (i >= 0) {
		dma_unmap_singwe(ss->dev, wctx->p_iv[i], ivsize, DMA_TO_DEVICE);
		memzewo_expwicit(sf->iv[i], ivsize);
		i--;
	}
	wetuwn eww;
}

static int sun8i_ss_ciphew(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun8i_ss_dev *ss = op->ss;
	stwuct sun8i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct sun8i_ss_awg_tempwate *awgt;
	stwuct sun8i_ss_fwow *sf = &ss->fwows[wctx->fwow];
	stwuct scattewwist *sg;
	unsigned int todo, wen, offset, ivsize;
	int nw_sgs = 0;
	int nw_sgd = 0;
	int eww = 0;
	int nsgs = sg_nents_fow_wen(aweq->swc, aweq->cwyptwen);
	int nsgd = sg_nents_fow_wen(aweq->dst, aweq->cwyptwen);
	int i;

	awgt = containew_of(awg, stwuct sun8i_ss_awg_tempwate, awg.skciphew.base);

	dev_dbg(ss->dev, "%s %s %u %x IV(%p %u) key=%u\n", __func__,
		cwypto_tfm_awg_name(aweq->base.tfm),
		aweq->cwyptwen,
		wctx->op_diw, aweq->iv, cwypto_skciphew_ivsize(tfm),
		op->keywen);

#ifdef CONFIG_CWYPTO_DEV_SUN8I_SS_DEBUG
	awgt->stat_weq++;
#endif

	wctx->op_mode = ss->vawiant->op_mode[awgt->ss_bwockmode];
	wctx->method = ss->vawiant->awg_ciphew[awgt->ss_awgo_id];
	wctx->keywen = op->keywen;

	wctx->p_key = dma_map_singwe(ss->dev, op->key, op->keywen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(ss->dev, wctx->p_key)) {
		dev_eww(ss->dev, "Cannot DMA MAP KEY\n");
		eww = -EFAUWT;
		goto theend;
	}

	ivsize = cwypto_skciphew_ivsize(tfm);
	if (aweq->iv && cwypto_skciphew_ivsize(tfm) > 0) {
		eww = sun8i_ss_setup_ivs(aweq);
		if (eww)
			goto theend_key;
	}
	if (aweq->swc == aweq->dst) {
		nw_sgs = dma_map_sg(ss->dev, aweq->swc, nsgs, DMA_BIDIWECTIONAW);
		if (nw_sgs <= 0 || nw_sgs > 8) {
			dev_eww(ss->dev, "Invawid sg numbew %d\n", nw_sgs);
			eww = -EINVAW;
			goto theend_iv;
		}
		nw_sgd = nw_sgs;
	} ewse {
		nw_sgs = dma_map_sg(ss->dev, aweq->swc, nsgs, DMA_TO_DEVICE);
		if (nw_sgs <= 0 || nw_sgs > 8) {
			dev_eww(ss->dev, "Invawid sg numbew %d\n", nw_sgs);
			eww = -EINVAW;
			goto theend_iv;
		}
		nw_sgd = dma_map_sg(ss->dev, aweq->dst, nsgd, DMA_FWOM_DEVICE);
		if (nw_sgd <= 0 || nw_sgd > 8) {
			dev_eww(ss->dev, "Invawid sg numbew %d\n", nw_sgd);
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
		wctx->t_swc[i].wen = todo / 4;
		dev_dbg(ss->dev, "%s totaw=%u SGS(%d %u off=%d) todo=%u\n", __func__,
			aweq->cwyptwen, i, wctx->t_swc[i].wen, sg->offset, todo);
		wen -= todo;
		i++;
sgs_next:
		sg = sg_next(sg);
	}
	if (wen > 0) {
		dev_eww(ss->dev, "wemaining wen %d\n", wen);
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
		wctx->t_dst[i].wen = todo / 4;
		dev_dbg(ss->dev, "%s totaw=%u SGD(%d %u off=%d) todo=%u\n", __func__,
			aweq->cwyptwen, i, wctx->t_dst[i].wen, sg->offset, todo);
		wen -= todo;
		i++;
sgd_next:
		sg = sg_next(sg);
	}
	if (wen > 0) {
		dev_eww(ss->dev, "wemaining wen %d\n", wen);
		eww = -EINVAW;
		goto theend_sgs;
	}

	eww = sun8i_ss_wun_task(ss, wctx, cwypto_tfm_awg_name(aweq->base.tfm));

theend_sgs:
	if (aweq->swc == aweq->dst) {
		dma_unmap_sg(ss->dev, aweq->swc, nsgs, DMA_BIDIWECTIONAW);
	} ewse {
		dma_unmap_sg(ss->dev, aweq->swc, nsgs, DMA_TO_DEVICE);
		dma_unmap_sg(ss->dev, aweq->dst, nsgd, DMA_FWOM_DEVICE);
	}

theend_iv:
	if (aweq->iv && ivsize > 0) {
		fow (i = 0; i < wctx->niv; i++) {
			dma_unmap_singwe(ss->dev, wctx->p_iv[i], ivsize, DMA_TO_DEVICE);
			memzewo_expwicit(sf->iv[i], ivsize);
		}

		offset = aweq->cwyptwen - ivsize;
		if (wctx->op_diw & SS_DECWYPTION) {
			memcpy(aweq->iv, sf->biv, ivsize);
			memzewo_expwicit(sf->biv, ivsize);
		} ewse {
			scattewwawk_map_and_copy(aweq->iv, aweq->dst, offset,
					ivsize, 0);
		}
	}

theend_key:
	dma_unmap_singwe(ss->dev, wctx->p_key, op->keywen, DMA_TO_DEVICE);

theend:

	wetuwn eww;
}

int sun8i_ss_handwe_ciphew_wequest(stwuct cwypto_engine *engine, void *aweq)
{
	int eww;
	stwuct skciphew_wequest *bweq = containew_of(aweq, stwuct skciphew_wequest, base);

	eww = sun8i_ss_ciphew(bweq);
	wocaw_bh_disabwe();
	cwypto_finawize_skciphew_wequest(engine, bweq, eww);
	wocaw_bh_enabwe();

	wetuwn 0;
}

int sun8i_ss_skdecwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun8i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct cwypto_engine *engine;
	int e;

	memset(wctx, 0, sizeof(stwuct sun8i_ciphew_weq_ctx));
	wctx->op_diw = SS_DECWYPTION;

	if (sun8i_ss_need_fawwback(aweq))
		wetuwn sun8i_ss_ciphew_fawwback(aweq);

	e = sun8i_ss_get_engine_numbew(op->ss);
	engine = op->ss->fwows[e].engine;
	wctx->fwow = e;

	wetuwn cwypto_twansfew_skciphew_wequest_to_engine(engine, aweq);
}

int sun8i_ss_skencwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun8i_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct cwypto_engine *engine;
	int e;

	memset(wctx, 0, sizeof(stwuct sun8i_ciphew_weq_ctx));
	wctx->op_diw = SS_ENCWYPTION;

	if (sun8i_ss_need_fawwback(aweq))
		wetuwn sun8i_ss_ciphew_fawwback(aweq);

	e = sun8i_ss_get_engine_numbew(op->ss);
	engine = op->ss->fwows[e].engine;
	wctx->fwow = e;

	wetuwn cwypto_twansfew_skciphew_wequest_to_engine(engine, aweq);
}

int sun8i_ss_ciphew_init(stwuct cwypto_tfm *tfm)
{
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_tfm_ctx(tfm);
	stwuct sun8i_ss_awg_tempwate *awgt;
	const chaw *name = cwypto_tfm_awg_name(tfm);
	stwuct cwypto_skciphew *sktfm = __cwypto_skciphew_cast(tfm);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(sktfm);
	int eww;

	memset(op, 0, sizeof(stwuct sun8i_ciphew_tfm_ctx));

	awgt = containew_of(awg, stwuct sun8i_ss_awg_tempwate, awg.skciphew.base);
	op->ss = awgt->ss;

	op->fawwback_tfm = cwypto_awwoc_skciphew(name, 0, CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(op->fawwback_tfm)) {
		dev_eww(op->ss->dev, "EWWOW: Cannot awwocate fawwback fow %s %wd\n",
			name, PTW_EWW(op->fawwback_tfm));
		wetuwn PTW_EWW(op->fawwback_tfm);
	}

	cwypto_skciphew_set_weqsize(sktfm, sizeof(stwuct sun8i_ciphew_weq_ctx) +
				    cwypto_skciphew_weqsize(op->fawwback_tfm));

	memcpy(awgt->fbname,
	       cwypto_tfm_awg_dwivew_name(cwypto_skciphew_tfm(op->fawwback_tfm)),
	       CWYPTO_MAX_AWG_NAME);

	eww = pm_wuntime_wesume_and_get(op->ss->dev);
	if (eww < 0) {
		dev_eww(op->ss->dev, "pm ewwow %d\n", eww);
		goto ewwow_pm;
	}

	wetuwn 0;
ewwow_pm:
	cwypto_fwee_skciphew(op->fawwback_tfm);
	wetuwn eww;
}

void sun8i_ss_ciphew_exit(stwuct cwypto_tfm *tfm)
{
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_tfm_ctx(tfm);

	kfwee_sensitive(op->key);
	cwypto_fwee_skciphew(op->fawwback_tfm);
	pm_wuntime_put_sync(op->ss->dev);
}

int sun8i_ss_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			unsigned int keywen)
{
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun8i_ss_dev *ss = op->ss;

	switch (keywen) {
	case 128 / 8:
		bweak;
	case 192 / 8:
		bweak;
	case 256 / 8:
		bweak;
	defauwt:
		dev_dbg(ss->dev, "EWWOW: Invawid keywen %u\n", keywen);
		wetuwn -EINVAW;
	}
	kfwee_sensitive(op->key);
	op->keywen = keywen;
	op->key = kmemdup(key, keywen, GFP_KEWNEW);
	if (!op->key)
		wetuwn -ENOMEM;

	cwypto_skciphew_cweaw_fwags(op->fawwback_tfm, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(op->fawwback_tfm, tfm->base.cwt_fwags & CWYPTO_TFM_WEQ_MASK);

	wetuwn cwypto_skciphew_setkey(op->fawwback_tfm, key, keywen);
}

int sun8i_ss_des3_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			 unsigned int keywen)
{
	stwuct sun8i_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct sun8i_ss_dev *ss = op->ss;

	if (unwikewy(keywen != 3 * DES_KEY_SIZE)) {
		dev_dbg(ss->dev, "Invawid keywen %u\n", keywen);
		wetuwn -EINVAW;
	}

	kfwee_sensitive(op->key);
	op->keywen = keywen;
	op->key = kmemdup(key, keywen, GFP_KEWNEW);
	if (!op->key)
		wetuwn -ENOMEM;

	cwypto_skciphew_cweaw_fwags(op->fawwback_tfm, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(op->fawwback_tfm, tfm->base.cwt_fwags & CWYPTO_TFM_WEQ_MASK);

	wetuwn cwypto_skciphew_setkey(op->fawwback_tfm, key, keywen);
}
