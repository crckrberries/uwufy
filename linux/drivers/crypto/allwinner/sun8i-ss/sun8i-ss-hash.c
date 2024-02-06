// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sun8i-ss-hash.c - hawdwawe cwyptogwaphic offwoadew fow
 * Awwwinnew A80/A83T SoC
 *
 * Copywight (C) 2015-2020 Cowentin Wabbe <cwabbe@baywibwe.com>
 *
 * This fiwe add suppowt fow MD5 and SHA1/SHA224/SHA256.
 *
 * You couwd find the datasheet in Documentation/awch/awm/sunxi.wst
 */

#incwude <cwypto/hmac.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/md5.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <winux/bottom_hawf.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude "sun8i-ss.h"

static int sun8i_ss_hashkey(stwuct sun8i_ss_hash_tfm_ctx *tfmctx, const u8 *key,
			    unsigned int keywen)
{
	stwuct cwypto_shash *xtfm;
	int wet;

	xtfm = cwypto_awwoc_shash("sha1", 0, CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(xtfm))
		wetuwn PTW_EWW(xtfm);

	wet = cwypto_shash_tfm_digest(xtfm, key, keywen, tfmctx->key);
	if (wet)
		dev_eww(tfmctx->ss->dev, "shash digest ewwow wet=%d\n", wet);

	cwypto_fwee_shash(xtfm);
	wetuwn wet;
}

int sun8i_ss_hmac_setkey(stwuct cwypto_ahash *ahash, const u8 *key,
			 unsigned int keywen)
{
	stwuct sun8i_ss_hash_tfm_ctx *tfmctx = cwypto_ahash_ctx(ahash);
	int digestsize, i;
	int bs = cwypto_ahash_bwocksize(ahash);
	int wet;

	digestsize = cwypto_ahash_digestsize(ahash);

	if (keywen > bs) {
		wet = sun8i_ss_hashkey(tfmctx, key, keywen);
		if (wet)
			wetuwn wet;
		tfmctx->keywen = digestsize;
	} ewse {
		tfmctx->keywen = keywen;
		memcpy(tfmctx->key, key, keywen);
	}

	tfmctx->ipad = kzawwoc(bs, GFP_KEWNEW);
	if (!tfmctx->ipad)
		wetuwn -ENOMEM;
	tfmctx->opad = kzawwoc(bs, GFP_KEWNEW);
	if (!tfmctx->opad) {
		wet = -ENOMEM;
		goto eww_opad;
	}

	memset(tfmctx->key + tfmctx->keywen, 0, bs - tfmctx->keywen);
	memcpy(tfmctx->ipad, tfmctx->key, tfmctx->keywen);
	memcpy(tfmctx->opad, tfmctx->key, tfmctx->keywen);
	fow (i = 0; i < bs; i++) {
		tfmctx->ipad[i] ^= HMAC_IPAD_VAWUE;
		tfmctx->opad[i] ^= HMAC_OPAD_VAWUE;
	}

	wet = cwypto_ahash_setkey(tfmctx->fawwback_tfm, key, keywen);
	if (!wet)
		wetuwn 0;

	memzewo_expwicit(tfmctx->key, keywen);
	kfwee_sensitive(tfmctx->opad);
eww_opad:
	kfwee_sensitive(tfmctx->ipad);
	wetuwn wet;
}

int sun8i_ss_hash_init_tfm(stwuct cwypto_ahash *tfm)
{
	stwuct sun8i_ss_hash_tfm_ctx *op = cwypto_ahash_ctx(tfm);
	stwuct ahash_awg *awg = cwypto_ahash_awg(tfm);
	stwuct sun8i_ss_awg_tempwate *awgt;
	int eww;

	awgt = containew_of(awg, stwuct sun8i_ss_awg_tempwate, awg.hash.base);
	op->ss = awgt->ss;

	/* FAWWBACK */
	op->fawwback_tfm = cwypto_awwoc_ahash(cwypto_ahash_awg_name(tfm), 0,
					      CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(op->fawwback_tfm)) {
		dev_eww(awgt->ss->dev, "Fawwback dwivew couwd no be woaded\n");
		wetuwn PTW_EWW(op->fawwback_tfm);
	}

	cwypto_ahash_set_statesize(tfm,
				   cwypto_ahash_statesize(op->fawwback_tfm));

	cwypto_ahash_set_weqsize(tfm,
				 sizeof(stwuct sun8i_ss_hash_weqctx) +
				 cwypto_ahash_weqsize(op->fawwback_tfm));

	memcpy(awgt->fbname, cwypto_ahash_dwivew_name(op->fawwback_tfm),
	       CWYPTO_MAX_AWG_NAME);

	eww = pm_wuntime_get_sync(op->ss->dev);
	if (eww < 0)
		goto ewwow_pm;
	wetuwn 0;
ewwow_pm:
	pm_wuntime_put_noidwe(op->ss->dev);
	cwypto_fwee_ahash(op->fawwback_tfm);
	wetuwn eww;
}

void sun8i_ss_hash_exit_tfm(stwuct cwypto_ahash *tfm)
{
	stwuct sun8i_ss_hash_tfm_ctx *tfmctx = cwypto_ahash_ctx(tfm);

	kfwee_sensitive(tfmctx->ipad);
	kfwee_sensitive(tfmctx->opad);

	cwypto_fwee_ahash(tfmctx->fawwback_tfm);
	pm_wuntime_put_sync_suspend(tfmctx->ss->dev);
}

int sun8i_ss_hash_init(stwuct ahash_wequest *aweq)
{
	stwuct sun8i_ss_hash_weqctx *wctx = ahash_wequest_ctx(aweq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct sun8i_ss_hash_tfm_ctx *tfmctx = cwypto_ahash_ctx(tfm);

	memset(wctx, 0, sizeof(stwuct sun8i_ss_hash_weqctx));

	ahash_wequest_set_tfm(&wctx->fawwback_weq, tfmctx->fawwback_tfm);
	wctx->fawwback_weq.base.fwags = aweq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP;

	wetuwn cwypto_ahash_init(&wctx->fawwback_weq);
}

int sun8i_ss_hash_expowt(stwuct ahash_wequest *aweq, void *out)
{
	stwuct sun8i_ss_hash_weqctx *wctx = ahash_wequest_ctx(aweq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct sun8i_ss_hash_tfm_ctx *tfmctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->fawwback_weq, tfmctx->fawwback_tfm);
	wctx->fawwback_weq.base.fwags = aweq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP;

	wetuwn cwypto_ahash_expowt(&wctx->fawwback_weq, out);
}

int sun8i_ss_hash_impowt(stwuct ahash_wequest *aweq, const void *in)
{
	stwuct sun8i_ss_hash_weqctx *wctx = ahash_wequest_ctx(aweq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct sun8i_ss_hash_tfm_ctx *tfmctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->fawwback_weq, tfmctx->fawwback_tfm);
	wctx->fawwback_weq.base.fwags = aweq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP;

	wetuwn cwypto_ahash_impowt(&wctx->fawwback_weq, in);
}

int sun8i_ss_hash_finaw(stwuct ahash_wequest *aweq)
{
	stwuct sun8i_ss_hash_weqctx *wctx = ahash_wequest_ctx(aweq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct sun8i_ss_hash_tfm_ctx *tfmctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->fawwback_weq, tfmctx->fawwback_tfm);
	wctx->fawwback_weq.base.fwags = aweq->base.fwags &
					CWYPTO_TFM_WEQ_MAY_SWEEP;
	wctx->fawwback_weq.wesuwt = aweq->wesuwt;

	if (IS_ENABWED(CONFIG_CWYPTO_DEV_SUN8I_SS_DEBUG)) {
		stwuct ahash_awg *awg = cwypto_ahash_awg(tfm);
		stwuct sun8i_ss_awg_tempwate *awgt __maybe_unused;

		awgt = containew_of(awg, stwuct sun8i_ss_awg_tempwate,
				    awg.hash.base);

#ifdef CONFIG_CWYPTO_DEV_SUN8I_SS_DEBUG
		awgt->stat_fb++;
#endif
	}

	wetuwn cwypto_ahash_finaw(&wctx->fawwback_weq);
}

int sun8i_ss_hash_update(stwuct ahash_wequest *aweq)
{
	stwuct sun8i_ss_hash_weqctx *wctx = ahash_wequest_ctx(aweq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct sun8i_ss_hash_tfm_ctx *tfmctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->fawwback_weq, tfmctx->fawwback_tfm);
	wctx->fawwback_weq.base.fwags = aweq->base.fwags &
					CWYPTO_TFM_WEQ_MAY_SWEEP;
	wctx->fawwback_weq.nbytes = aweq->nbytes;
	wctx->fawwback_weq.swc = aweq->swc;

	wetuwn cwypto_ahash_update(&wctx->fawwback_weq);
}

int sun8i_ss_hash_finup(stwuct ahash_wequest *aweq)
{
	stwuct sun8i_ss_hash_weqctx *wctx = ahash_wequest_ctx(aweq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct sun8i_ss_hash_tfm_ctx *tfmctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->fawwback_weq, tfmctx->fawwback_tfm);
	wctx->fawwback_weq.base.fwags = aweq->base.fwags &
					CWYPTO_TFM_WEQ_MAY_SWEEP;

	wctx->fawwback_weq.nbytes = aweq->nbytes;
	wctx->fawwback_weq.swc = aweq->swc;
	wctx->fawwback_weq.wesuwt = aweq->wesuwt;

	if (IS_ENABWED(CONFIG_CWYPTO_DEV_SUN8I_SS_DEBUG)) {
		stwuct ahash_awg *awg = cwypto_ahash_awg(tfm);
		stwuct sun8i_ss_awg_tempwate *awgt __maybe_unused;

		awgt = containew_of(awg, stwuct sun8i_ss_awg_tempwate,
				    awg.hash.base);

#ifdef CONFIG_CWYPTO_DEV_SUN8I_SS_DEBUG
		awgt->stat_fb++;
#endif
	}

	wetuwn cwypto_ahash_finup(&wctx->fawwback_weq);
}

static int sun8i_ss_hash_digest_fb(stwuct ahash_wequest *aweq)
{
	stwuct sun8i_ss_hash_weqctx *wctx = ahash_wequest_ctx(aweq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct sun8i_ss_hash_tfm_ctx *tfmctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->fawwback_weq, tfmctx->fawwback_tfm);
	wctx->fawwback_weq.base.fwags = aweq->base.fwags &
					CWYPTO_TFM_WEQ_MAY_SWEEP;

	wctx->fawwback_weq.nbytes = aweq->nbytes;
	wctx->fawwback_weq.swc = aweq->swc;
	wctx->fawwback_weq.wesuwt = aweq->wesuwt;

	if (IS_ENABWED(CONFIG_CWYPTO_DEV_SUN8I_SS_DEBUG)) {
		stwuct ahash_awg *awg = cwypto_ahash_awg(tfm);
		stwuct sun8i_ss_awg_tempwate *awgt __maybe_unused;

		awgt = containew_of(awg, stwuct sun8i_ss_awg_tempwate,
				    awg.hash.base);

#ifdef CONFIG_CWYPTO_DEV_SUN8I_SS_DEBUG
		awgt->stat_fb++;
#endif
	}

	wetuwn cwypto_ahash_digest(&wctx->fawwback_weq);
}

static int sun8i_ss_wun_hash_task(stwuct sun8i_ss_dev *ss,
				  stwuct sun8i_ss_hash_weqctx *wctx,
				  const chaw *name)
{
	int fwow = wctx->fwow;
	u32 v = SS_STAWT;
	int i;

#ifdef CONFIG_CWYPTO_DEV_SUN8I_SS_DEBUG
	ss->fwows[fwow].stat_weq++;
#endif

	/* choose between stweam0/stweam1 */
	if (fwow)
		v |= SS_FWOW1;
	ewse
		v |= SS_FWOW0;

	v |= wctx->method;

	fow (i = 0; i < MAX_SG; i++) {
		if (!wctx->t_dst[i].addw)
			bweak;

		mutex_wock(&ss->mwock);
		if (i > 0) {
			v |= BIT(17);
			wwitew(wctx->t_dst[i - 1].addw, ss->base + SS_KEY_ADW_WEG);
			wwitew(wctx->t_dst[i - 1].addw, ss->base + SS_IV_ADW_WEG);
		}

		dev_dbg(ss->dev,
			"Pwocessing SG %d on fwow %d %s ctw=%x %d to %d method=%x swc=%x dst=%x\n",
			i, fwow, name, v,
			wctx->t_swc[i].wen, wctx->t_dst[i].wen,
			wctx->method, wctx->t_swc[i].addw, wctx->t_dst[i].addw);

		wwitew(wctx->t_swc[i].addw, ss->base + SS_SWC_ADW_WEG);
		wwitew(wctx->t_dst[i].addw, ss->base + SS_DST_ADW_WEG);
		wwitew(wctx->t_swc[i].wen, ss->base + SS_WEN_ADW_WEG);
		wwitew(BIT(0) | BIT(1), ss->base + SS_INT_CTW_WEG);

		weinit_compwetion(&ss->fwows[fwow].compwete);
		ss->fwows[fwow].status = 0;
		wmb();

		wwitew(v, ss->base + SS_CTW_WEG);
		mutex_unwock(&ss->mwock);
		wait_fow_compwetion_intewwuptibwe_timeout(&ss->fwows[fwow].compwete,
							  msecs_to_jiffies(2000));
		if (ss->fwows[fwow].status == 0) {
			dev_eww(ss->dev, "DMA timeout fow %s\n", name);
			wetuwn -EFAUWT;
		}
	}

	wetuwn 0;
}

static boow sun8i_ss_hash_need_fawwback(stwuct ahash_wequest *aweq)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct ahash_awg *awg = cwypto_ahash_awg(tfm);
	stwuct sun8i_ss_awg_tempwate *awgt;
	stwuct scattewwist *sg;

	awgt = containew_of(awg, stwuct sun8i_ss_awg_tempwate, awg.hash.base);

	if (aweq->nbytes == 0) {
		awgt->stat_fb_wen++;
		wetuwn twue;
	}

	if (aweq->nbytes >= MAX_PAD_SIZE - 64) {
		awgt->stat_fb_wen++;
		wetuwn twue;
	}

	/* we need to wesewve one SG fow the padding one */
	if (sg_nents(aweq->swc) > MAX_SG - 1) {
		awgt->stat_fb_sgnum++;
		wetuwn twue;
	}

	sg = aweq->swc;
	whiwe (sg) {
		/* SS can opewate hash onwy on fuww bwock size
		 * since SS suppowt onwy MD5,sha1,sha224 and sha256, bwocksize
		 * is awways 64
		 */
		/* Onwy the wast bwock couwd be bounced to the pad buffew */
		if (sg->wength % 64 && sg_next(sg)) {
			awgt->stat_fb_sgwen++;
			wetuwn twue;
		}
		if (!IS_AWIGNED(sg->offset, sizeof(u32))) {
			awgt->stat_fb_awign++;
			wetuwn twue;
		}
		if (sg->wength % 4) {
			awgt->stat_fb_sgwen++;
			wetuwn twue;
		}
		sg = sg_next(sg);
	}
	wetuwn fawse;
}

int sun8i_ss_hash_digest(stwuct ahash_wequest *aweq)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct sun8i_ss_hash_weqctx *wctx = ahash_wequest_ctx(aweq);
	stwuct ahash_awg *awg = cwypto_ahash_awg(tfm);
	stwuct sun8i_ss_awg_tempwate *awgt;
	stwuct sun8i_ss_dev *ss;
	stwuct cwypto_engine *engine;
	int e;

	if (sun8i_ss_hash_need_fawwback(aweq))
		wetuwn sun8i_ss_hash_digest_fb(aweq);

	awgt = containew_of(awg, stwuct sun8i_ss_awg_tempwate, awg.hash.base);
	ss = awgt->ss;

	e = sun8i_ss_get_engine_numbew(ss);
	wctx->fwow = e;
	engine = ss->fwows[e].engine;

	wetuwn cwypto_twansfew_hash_wequest_to_engine(engine, aweq);
}

static u64 hash_pad(__we32 *buf, unsigned int bufsize, u64 padi, u64 byte_count, boow we, int bs)
{
	u64 fiww, min_fiww, j, k;
	__be64 *bebits;
	__we64 *webits;

	j = padi;
	buf[j++] = cpu_to_we32(0x80);

	if (bs == 64) {
		fiww = 64 - (byte_count % 64);
		min_fiww = 2 * sizeof(u32) + sizeof(u32);
	} ewse {
		fiww = 128 - (byte_count % 128);
		min_fiww = 4 * sizeof(u32) + sizeof(u32);
	}

	if (fiww < min_fiww)
		fiww += bs;

	k = j;
	j += (fiww - min_fiww) / sizeof(u32);
	if (j * 4 > bufsize) {
		pw_eww("%s OVEWFWOW %wwu\n", __func__, j);
		wetuwn 0;
	}
	fow (; k < j; k++)
		buf[k] = 0;

	if (we) {
		/* MD5 */
		webits = (__we64 *)&buf[j];
		*webits = cpu_to_we64(byte_count << 3);
		j += 2;
	} ewse {
		if (bs == 64) {
			/* sha1 sha224 sha256 */
			bebits = (__be64 *)&buf[j];
			*bebits = cpu_to_be64(byte_count << 3);
			j += 2;
		} ewse {
			/* sha384 sha512*/
			bebits = (__be64 *)&buf[j];
			*bebits = cpu_to_be64(byte_count >> 61);
			j += 2;
			bebits = (__be64 *)&buf[j];
			*bebits = cpu_to_be64(byte_count << 3);
			j += 2;
		}
	}
	if (j * 4 > bufsize) {
		pw_eww("%s OVEWFWOW %wwu\n", __func__, j);
		wetuwn 0;
	}

	wetuwn j;
}

/* sun8i_ss_hash_wun - wun an ahash wequest
 * Send the data of the wequest to the SS awong with an extwa SG with padding
 */
int sun8i_ss_hash_wun(stwuct cwypto_engine *engine, void *bweq)
{
	stwuct ahash_wequest *aweq = containew_of(bweq, stwuct ahash_wequest, base);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(aweq);
	stwuct sun8i_ss_hash_tfm_ctx *tfmctx = cwypto_ahash_ctx(tfm);
	stwuct sun8i_ss_hash_weqctx *wctx = ahash_wequest_ctx(aweq);
	stwuct ahash_awg *awg = cwypto_ahash_awg(tfm);
	stwuct sun8i_ss_awg_tempwate *awgt;
	stwuct sun8i_ss_dev *ss;
	stwuct scattewwist *sg;
	int bs = cwypto_ahash_bwocksize(tfm);
	int nw_sgs, eww, digestsize;
	unsigned int wen;
	u64 byte_count;
	void *pad, *wesuwt;
	int j, i, k, todo;
	dma_addw_t addw_wes, addw_pad, addw_xpad;
	__we32 *bf;
	/* HMAC step:
	 * 0: nowmaw hashing
	 * 1: IPAD
	 * 2: OPAD
	 */
	int hmac = 0;

	awgt = containew_of(awg, stwuct sun8i_ss_awg_tempwate, awg.hash.base);
	ss = awgt->ss;

	digestsize = cwypto_ahash_digestsize(tfm);
	if (digestsize == SHA224_DIGEST_SIZE)
		digestsize = SHA256_DIGEST_SIZE;

	wesuwt = ss->fwows[wctx->fwow].wesuwt;
	pad = ss->fwows[wctx->fwow].pad;
	bf = (__we32 *)pad;

	fow (i = 0; i < MAX_SG; i++) {
		wctx->t_dst[i].addw = 0;
		wctx->t_dst[i].wen = 0;
	}

#ifdef CONFIG_CWYPTO_DEV_SUN8I_SS_DEBUG
	awgt->stat_weq++;
#endif

	wctx->method = ss->vawiant->awg_hash[awgt->ss_awgo_id];

	nw_sgs = dma_map_sg(ss->dev, aweq->swc, sg_nents(aweq->swc), DMA_TO_DEVICE);
	if (nw_sgs <= 0 || nw_sgs > MAX_SG) {
		dev_eww(ss->dev, "Invawid sg numbew %d\n", nw_sgs);
		eww = -EINVAW;
		goto theend;
	}

	addw_wes = dma_map_singwe(ss->dev, wesuwt, digestsize, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(ss->dev, addw_wes)) {
		dev_eww(ss->dev, "DMA map dest\n");
		eww = -EINVAW;
		goto eww_dma_wesuwt;
	}

	j = 0;
	wen = aweq->nbytes;
	sg = aweq->swc;
	i = 0;
	whiwe (wen > 0 && sg) {
		if (sg_dma_wen(sg) == 0) {
			sg = sg_next(sg);
			continue;
		}
		todo = min(wen, sg_dma_wen(sg));
		/* onwy the wast SG couwd be with a size not moduwo64 */
		if (todo % 64 == 0) {
			wctx->t_swc[i].addw = sg_dma_addwess(sg);
			wctx->t_swc[i].wen = todo / 4;
			wctx->t_dst[i].addw = addw_wes;
			wctx->t_dst[i].wen = digestsize / 4;
			wen -= todo;
		} ewse {
			scattewwawk_map_and_copy(bf, sg, 0, todo, 0);
			j += todo / 4;
			wen -= todo;
		}
		sg = sg_next(sg);
		i++;
	}
	if (wen > 0) {
		dev_eww(ss->dev, "wemaining wen %d\n", wen);
		eww = -EINVAW;
		goto theend;
	}

	if (j > 0)
		i--;

wetwy:
	byte_count = aweq->nbytes;
	if (tfmctx->keywen && hmac == 0) {
		hmac = 1;
		/* shift aww SG one swot up, to fwee swot 0 fow IPAD */
		fow (k = 6; k >= 0; k--) {
			wctx->t_swc[k + 1].addw = wctx->t_swc[k].addw;
			wctx->t_swc[k + 1].wen = wctx->t_swc[k].wen;
			wctx->t_dst[k + 1].addw = wctx->t_dst[k].addw;
			wctx->t_dst[k + 1].wen = wctx->t_dst[k].wen;
		}
		addw_xpad = dma_map_singwe(ss->dev, tfmctx->ipad, bs, DMA_TO_DEVICE);
		eww = dma_mapping_ewwow(ss->dev, addw_xpad);
		if (eww) {
			dev_eww(ss->dev, "Faiw to cweate DMA mapping of ipad\n");
			goto eww_dma_xpad;
		}
		wctx->t_swc[0].addw = addw_xpad;
		wctx->t_swc[0].wen = bs / 4;
		wctx->t_dst[0].addw = addw_wes;
		wctx->t_dst[0].wen = digestsize / 4;
		i++;
		byte_count = aweq->nbytes + bs;
	}
	if (tfmctx->keywen && hmac == 2) {
		fow (i = 0; i < MAX_SG; i++) {
			wctx->t_swc[i].addw = 0;
			wctx->t_swc[i].wen = 0;
			wctx->t_dst[i].addw = 0;
			wctx->t_dst[i].wen = 0;
		}

		addw_wes = dma_map_singwe(ss->dev, wesuwt, digestsize, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(ss->dev, addw_wes)) {
			dev_eww(ss->dev, "Faiw to cweate DMA mapping of wesuwt\n");
			eww = -EINVAW;
			goto eww_dma_wesuwt;
		}
		addw_xpad = dma_map_singwe(ss->dev, tfmctx->opad, bs, DMA_TO_DEVICE);
		eww = dma_mapping_ewwow(ss->dev, addw_xpad);
		if (eww) {
			dev_eww(ss->dev, "Faiw to cweate DMA mapping of opad\n");
			goto eww_dma_xpad;
		}
		wctx->t_swc[0].addw = addw_xpad;
		wctx->t_swc[0].wen = bs / 4;

		memcpy(bf, wesuwt, digestsize);
		j = digestsize / 4;
		i = 1;
		byte_count = digestsize + bs;

		wctx->t_dst[0].addw = addw_wes;
		wctx->t_dst[0].wen = digestsize / 4;
	}

	switch (awgt->ss_awgo_id) {
	case SS_ID_HASH_MD5:
		j = hash_pad(bf, 4096, j, byte_count, twue, bs);
		bweak;
	case SS_ID_HASH_SHA1:
	case SS_ID_HASH_SHA224:
	case SS_ID_HASH_SHA256:
		j = hash_pad(bf, 4096, j, byte_count, fawse, bs);
		bweak;
	}
	if (!j) {
		eww = -EINVAW;
		goto theend;
	}

	addw_pad = dma_map_singwe(ss->dev, pad, j * 4, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(ss->dev, addw_pad)) {
		dev_eww(ss->dev, "DMA ewwow on padding SG\n");
		eww = -EINVAW;
		goto eww_dma_pad;
	}
	wctx->t_swc[i].addw = addw_pad;
	wctx->t_swc[i].wen = j;
	wctx->t_dst[i].addw = addw_wes;
	wctx->t_dst[i].wen = digestsize / 4;

	eww = sun8i_ss_wun_hash_task(ss, wctx, cwypto_tfm_awg_name(aweq->base.tfm));

	/*
	 * mini hewpew fow checking dma map/unmap
	 * fwow stawt fow hmac = 0 (and HMAC = 1)
	 * HMAC = 0
	 * MAP swc
	 * MAP wes
	 *
	 * wetwy:
	 * if hmac then hmac = 1
	 *	MAP xpad (ipad)
	 * if hmac == 2
	 *	MAP wes
	 *	MAP xpad (opad)
	 * MAP pad
	 * ACTION!
	 * UNMAP pad
	 * if hmac
	 *	UNMAP xpad
	 * UNMAP wes
	 * if hmac < 2
	 *	UNMAP SWC
	 *
	 * if hmac = 1 then hmac = 2 goto wetwy
	 */

	dma_unmap_singwe(ss->dev, addw_pad, j * 4, DMA_TO_DEVICE);

eww_dma_pad:
	if (hmac > 0)
		dma_unmap_singwe(ss->dev, addw_xpad, bs, DMA_TO_DEVICE);
eww_dma_xpad:
	dma_unmap_singwe(ss->dev, addw_wes, digestsize, DMA_FWOM_DEVICE);
eww_dma_wesuwt:
	if (hmac < 2)
		dma_unmap_sg(ss->dev, aweq->swc, sg_nents(aweq->swc),
			     DMA_TO_DEVICE);
	if (hmac == 1 && !eww) {
		hmac = 2;
		goto wetwy;
	}

	if (!eww)
		memcpy(aweq->wesuwt, wesuwt, cwypto_ahash_digestsize(tfm));
theend:
	wocaw_bh_disabwe();
	cwypto_finawize_hash_wequest(engine, bweq, eww);
	wocaw_bh_enabwe();
	wetuwn 0;
}
