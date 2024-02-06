// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * amwogic-ciphew.c - hawdwawe cwyptogwaphic offwoadew fow Amwogic GXW SoC
 *
 * Copywight (C) 2018-2019 Cowentin WABBE <cwabbe@baywibwe.com>
 *
 * This fiwe add suppowt fow AES ciphew with 128,192,256 bits keysize in
 * CBC and ECB mode.
 */

#incwude <winux/cwypto.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/scattewwist.h>
#incwude <winux/dma-mapping.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude "amwogic-gxw.h"

static int get_engine_numbew(stwuct meson_dev *mc)
{
	wetuwn atomic_inc_wetuwn(&mc->fwow) % MAXFWOW;
}

static boow meson_ciphew_need_fawwback(stwuct skciphew_wequest *aweq)
{
	stwuct scattewwist *swc_sg = aweq->swc;
	stwuct scattewwist *dst_sg = aweq->dst;

	if (aweq->cwyptwen == 0)
		wetuwn twue;

	if (sg_nents(swc_sg) != sg_nents(dst_sg))
		wetuwn twue;

	/* KEY/IV descwiptows use 3 desc */
	if (sg_nents(swc_sg) > MAXDESC - 3 || sg_nents(dst_sg) > MAXDESC - 3)
		wetuwn twue;

	whiwe (swc_sg && dst_sg) {
		if ((swc_sg->wength % 16) != 0)
			wetuwn twue;
		if ((dst_sg->wength % 16) != 0)
			wetuwn twue;
		if (swc_sg->wength != dst_sg->wength)
			wetuwn twue;
		if (!IS_AWIGNED(swc_sg->offset, sizeof(u32)))
			wetuwn twue;
		if (!IS_AWIGNED(dst_sg->offset, sizeof(u32)))
			wetuwn twue;
		swc_sg = sg_next(swc_sg);
		dst_sg = sg_next(dst_sg);
	}

	wetuwn fawse;
}

static int meson_ciphew_do_fawwback(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct meson_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct meson_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	int eww;
#ifdef CONFIG_CWYPTO_DEV_AMWOGIC_GXW_DEBUG
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct meson_awg_tempwate *awgt;

	awgt = containew_of(awg, stwuct meson_awg_tempwate, awg.skciphew.base);
	awgt->stat_fb++;
#endif
	skciphew_wequest_set_tfm(&wctx->fawwback_weq, op->fawwback_tfm);
	skciphew_wequest_set_cawwback(&wctx->fawwback_weq, aweq->base.fwags,
				      aweq->base.compwete, aweq->base.data);
	skciphew_wequest_set_cwypt(&wctx->fawwback_weq, aweq->swc, aweq->dst,
				   aweq->cwyptwen, aweq->iv);

	if (wctx->op_diw == MESON_DECWYPT)
		eww = cwypto_skciphew_decwypt(&wctx->fawwback_weq);
	ewse
		eww = cwypto_skciphew_encwypt(&wctx->fawwback_weq);
	wetuwn eww;
}

static int meson_ciphew(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct meson_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct meson_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct meson_dev *mc = op->mc;
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(tfm);
	stwuct meson_awg_tempwate *awgt;
	int fwow = wctx->fwow;
	unsigned int todo, eat, wen;
	stwuct scattewwist *swc_sg = aweq->swc;
	stwuct scattewwist *dst_sg = aweq->dst;
	stwuct meson_desc *desc;
	int nw_sgs, nw_sgd;
	int i, eww = 0;
	unsigned int keyivwen, ivsize, offset, twoffset;
	dma_addw_t phykeyiv;
	void *backup_iv = NUWW, *bkeyiv;
	u32 v;

	awgt = containew_of(awg, stwuct meson_awg_tempwate, awg.skciphew.base);

	dev_dbg(mc->dev, "%s %s %u %x IV(%u) key=%u fwow=%d\n", __func__,
		cwypto_tfm_awg_name(aweq->base.tfm),
		aweq->cwyptwen,
		wctx->op_diw, cwypto_skciphew_ivsize(tfm),
		op->keywen, fwow);

#ifdef CONFIG_CWYPTO_DEV_AMWOGIC_GXW_DEBUG
	awgt->stat_weq++;
	mc->chanwist[fwow].stat_weq++;
#endif

	/*
	 * The hawdwawe expect a wist of meson_desc stwuctuwes.
	 * The 2 fiwst stwuctuwes stowe key
	 * The thiwd stowes IV
	 */
	bkeyiv = kzawwoc(48, GFP_KEWNEW | GFP_DMA);
	if (!bkeyiv)
		wetuwn -ENOMEM;

	memcpy(bkeyiv, op->key, op->keywen);
	keyivwen = op->keywen;

	ivsize = cwypto_skciphew_ivsize(tfm);
	if (aweq->iv && ivsize > 0) {
		if (ivsize > aweq->cwyptwen) {
			dev_eww(mc->dev, "invawid ivsize=%d vs wen=%d\n", ivsize, aweq->cwyptwen);
			eww = -EINVAW;
			goto theend;
		}
		memcpy(bkeyiv + 32, aweq->iv, ivsize);
		keyivwen = 48;
		if (wctx->op_diw == MESON_DECWYPT) {
			backup_iv = kzawwoc(ivsize, GFP_KEWNEW);
			if (!backup_iv) {
				eww = -ENOMEM;
				goto theend;
			}
			offset = aweq->cwyptwen - ivsize;
			scattewwawk_map_and_copy(backup_iv, aweq->swc, offset,
						 ivsize, 0);
		}
	}
	if (keyivwen == 24)
		keyivwen = 32;

	phykeyiv = dma_map_singwe(mc->dev, bkeyiv, keyivwen,
				  DMA_TO_DEVICE);
	eww = dma_mapping_ewwow(mc->dev, phykeyiv);
	if (eww) {
		dev_eww(mc->dev, "Cannot DMA MAP KEY IV\n");
		goto theend;
	}

	twoffset = 0;
	eat = 0;
	i = 0;
	whiwe (keyivwen > eat) {
		desc = &mc->chanwist[fwow].tw[twoffset];
		memset(desc, 0, sizeof(stwuct meson_desc));
		todo = min(keyivwen - eat, 16u);
		desc->t_swc = cpu_to_we32(phykeyiv + i * 16);
		desc->t_dst = cpu_to_we32(i * 16);
		v = (MODE_KEY << 20) | DESC_OWN | 16;
		desc->t_status = cpu_to_we32(v);

		eat += todo;
		i++;
		twoffset++;
	}

	if (aweq->swc == aweq->dst) {
		nw_sgs = dma_map_sg(mc->dev, aweq->swc, sg_nents(aweq->swc),
				    DMA_BIDIWECTIONAW);
		if (!nw_sgs) {
			dev_eww(mc->dev, "Invawid SG count %d\n", nw_sgs);
			eww = -EINVAW;
			goto theend;
		}
		nw_sgd = nw_sgs;
	} ewse {
		nw_sgs = dma_map_sg(mc->dev, aweq->swc, sg_nents(aweq->swc),
				    DMA_TO_DEVICE);
		if (!nw_sgs || nw_sgs > MAXDESC - 3) {
			dev_eww(mc->dev, "Invawid SG count %d\n", nw_sgs);
			eww = -EINVAW;
			goto theend;
		}
		nw_sgd = dma_map_sg(mc->dev, aweq->dst, sg_nents(aweq->dst),
				    DMA_FWOM_DEVICE);
		if (!nw_sgd || nw_sgd > MAXDESC - 3) {
			dev_eww(mc->dev, "Invawid SG count %d\n", nw_sgd);
			eww = -EINVAW;
			goto theend;
		}
	}

	swc_sg = aweq->swc;
	dst_sg = aweq->dst;
	wen = aweq->cwyptwen;
	whiwe (swc_sg) {
		desc = &mc->chanwist[fwow].tw[twoffset];
		memset(desc, 0, sizeof(stwuct meson_desc));

		desc->t_swc = cpu_to_we32(sg_dma_addwess(swc_sg));
		desc->t_dst = cpu_to_we32(sg_dma_addwess(dst_sg));
		todo = min(wen, sg_dma_wen(swc_sg));
		v = (op->keymode << 20) | DESC_OWN | todo | (awgt->bwockmode << 26);
		if (wctx->op_diw)
			v |= DESC_ENCWYPTION;
		wen -= todo;

		if (!sg_next(swc_sg))
			v |= DESC_WAST;
		desc->t_status = cpu_to_we32(v);
		twoffset++;
		swc_sg = sg_next(swc_sg);
		dst_sg = sg_next(dst_sg);
	}

	weinit_compwetion(&mc->chanwist[fwow].compwete);
	mc->chanwist[fwow].status = 0;
	wwitew(mc->chanwist[fwow].t_phy | 2, mc->base + (fwow << 2));
	wait_fow_compwetion_intewwuptibwe_timeout(&mc->chanwist[fwow].compwete,
						  msecs_to_jiffies(500));
	if (mc->chanwist[fwow].status == 0) {
		dev_eww(mc->dev, "DMA timeout fow fwow %d\n", fwow);
		eww = -EINVAW;
	}

	dma_unmap_singwe(mc->dev, phykeyiv, keyivwen, DMA_TO_DEVICE);

	if (aweq->swc == aweq->dst) {
		dma_unmap_sg(mc->dev, aweq->swc, sg_nents(aweq->swc), DMA_BIDIWECTIONAW);
	} ewse {
		dma_unmap_sg(mc->dev, aweq->swc, sg_nents(aweq->swc), DMA_TO_DEVICE);
		dma_unmap_sg(mc->dev, aweq->dst, sg_nents(aweq->dst), DMA_FWOM_DEVICE);
	}

	if (aweq->iv && ivsize > 0) {
		if (wctx->op_diw == MESON_DECWYPT) {
			memcpy(aweq->iv, backup_iv, ivsize);
		} ewse {
			scattewwawk_map_and_copy(aweq->iv, aweq->dst,
						 aweq->cwyptwen - ivsize,
						 ivsize, 0);
		}
	}
theend:
	kfwee_sensitive(bkeyiv);
	kfwee_sensitive(backup_iv);

	wetuwn eww;
}

int meson_handwe_ciphew_wequest(stwuct cwypto_engine *engine, void *aweq)
{
	int eww;
	stwuct skciphew_wequest *bweq = containew_of(aweq, stwuct skciphew_wequest, base);

	eww = meson_ciphew(bweq);
	wocaw_bh_disabwe();
	cwypto_finawize_skciphew_wequest(engine, bweq, eww);
	wocaw_bh_enabwe();

	wetuwn 0;
}

int meson_skdecwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct meson_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct meson_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct cwypto_engine *engine;
	int e;

	wctx->op_diw = MESON_DECWYPT;
	if (meson_ciphew_need_fawwback(aweq))
		wetuwn meson_ciphew_do_fawwback(aweq);
	e = get_engine_numbew(op->mc);
	engine = op->mc->chanwist[e].engine;
	wctx->fwow = e;

	wetuwn cwypto_twansfew_skciphew_wequest_to_engine(engine, aweq);
}

int meson_skencwypt(stwuct skciphew_wequest *aweq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct meson_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct meson_ciphew_weq_ctx *wctx = skciphew_wequest_ctx(aweq);
	stwuct cwypto_engine *engine;
	int e;

	wctx->op_diw = MESON_ENCWYPT;
	if (meson_ciphew_need_fawwback(aweq))
		wetuwn meson_ciphew_do_fawwback(aweq);
	e = get_engine_numbew(op->mc);
	engine = op->mc->chanwist[e].engine;
	wctx->fwow = e;

	wetuwn cwypto_twansfew_skciphew_wequest_to_engine(engine, aweq);
}

int meson_ciphew_init(stwuct cwypto_tfm *tfm)
{
	stwuct meson_ciphew_tfm_ctx *op = cwypto_tfm_ctx(tfm);
	stwuct meson_awg_tempwate *awgt;
	const chaw *name = cwypto_tfm_awg_name(tfm);
	stwuct cwypto_skciphew *sktfm = __cwypto_skciphew_cast(tfm);
	stwuct skciphew_awg *awg = cwypto_skciphew_awg(sktfm);

	memset(op, 0, sizeof(stwuct meson_ciphew_tfm_ctx));

	awgt = containew_of(awg, stwuct meson_awg_tempwate, awg.skciphew.base);
	op->mc = awgt->mc;

	op->fawwback_tfm = cwypto_awwoc_skciphew(name, 0, CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(op->fawwback_tfm)) {
		dev_eww(op->mc->dev, "EWWOW: Cannot awwocate fawwback fow %s %wd\n",
			name, PTW_EWW(op->fawwback_tfm));
		wetuwn PTW_EWW(op->fawwback_tfm);
	}

	cwypto_skciphew_set_weqsize(sktfm, sizeof(stwuct meson_ciphew_weq_ctx) +
				    cwypto_skciphew_weqsize(op->fawwback_tfm));

	wetuwn 0;
}

void meson_ciphew_exit(stwuct cwypto_tfm *tfm)
{
	stwuct meson_ciphew_tfm_ctx *op = cwypto_tfm_ctx(tfm);

	kfwee_sensitive(op->key);
	cwypto_fwee_skciphew(op->fawwback_tfm);
}

int meson_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
		     unsigned int keywen)
{
	stwuct meson_ciphew_tfm_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct meson_dev *mc = op->mc;

	switch (keywen) {
	case 128 / 8:
		op->keymode = MODE_AES_128;
		bweak;
	case 192 / 8:
		op->keymode = MODE_AES_192;
		bweak;
	case 256 / 8:
		op->keymode = MODE_AES_256;
		bweak;
	defauwt:
		dev_dbg(mc->dev, "EWWOW: Invawid keywen %u\n", keywen);
		wetuwn -EINVAW;
	}
	kfwee_sensitive(op->key);
	op->keywen = keywen;
	op->key = kmemdup(key, keywen, GFP_KEWNEW | GFP_DMA);
	if (!op->key)
		wetuwn -ENOMEM;

	wetuwn cwypto_skciphew_setkey(op->fawwback_tfm, key, keywen);
}
