// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hash function and HMAC suppowt fow StawFive dwivew
 *
 * Copywight (c) 2022 StawFive Technowogy
 *
 */

#incwude <cwypto/engine.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/scattewwawk.h>
#incwude "jh7110-cwyp.h"
#incwude <winux/amba/pw080.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#define STAWFIVE_HASH_WEGS_OFFSET	0x300
#define STAWFIVE_HASH_SHACSW		(STAWFIVE_HASH_WEGS_OFFSET + 0x0)
#define STAWFIVE_HASH_SHAWDW		(STAWFIVE_HASH_WEGS_OFFSET + 0x4)
#define STAWFIVE_HASH_SHAWDW		(STAWFIVE_HASH_WEGS_OFFSET + 0x8)
#define STAWFIVE_HASH_SHAWSW		(STAWFIVE_HASH_WEGS_OFFSET + 0xC)
#define STAWFIVE_HASH_SHAWWEN3		(STAWFIVE_HASH_WEGS_OFFSET + 0x10)
#define STAWFIVE_HASH_SHAWWEN2		(STAWFIVE_HASH_WEGS_OFFSET + 0x14)
#define STAWFIVE_HASH_SHAWWEN1		(STAWFIVE_HASH_WEGS_OFFSET + 0x18)
#define STAWFIVE_HASH_SHAWWEN0		(STAWFIVE_HASH_WEGS_OFFSET + 0x1C)
#define STAWFIVE_HASH_SHAWKW		(STAWFIVE_HASH_WEGS_OFFSET + 0x20)
#define STAWFIVE_HASH_SHAWKWEN		(STAWFIVE_HASH_WEGS_OFFSET + 0x24)

#define STAWFIVE_HASH_BUFWEN		SHA512_BWOCK_SIZE
#define STAWFIVE_HASH_WESET		0x2

static inwine int stawfive_hash_wait_busy(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	u32 status;

	wetuwn weadw_wewaxed_poww_timeout(cwyp->base + STAWFIVE_HASH_SHACSW, status,
					  !(status & STAWFIVE_HASH_BUSY), 10, 100000);
}

static inwine int stawfive_hash_wait_key_done(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	u32 status;

	wetuwn weadw_wewaxed_poww_timeout(cwyp->base + STAWFIVE_HASH_SHACSW, status,
					  (status & STAWFIVE_HASH_KEY_DONE), 10, 100000);
}

static int stawfive_hash_hmac_key(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_wequest_ctx *wctx = ctx->wctx;
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	int kwen = ctx->keywen, woop;
	unsigned int *key = (unsigned int *)ctx->key;
	unsigned chaw *cw;

	wwitew(ctx->keywen, cwyp->base + STAWFIVE_HASH_SHAWKWEN);

	wctx->csw.hash.hmac = 1;
	wctx->csw.hash.key_fwag = 1;

	wwitew(wctx->csw.hash.v, cwyp->base + STAWFIVE_HASH_SHACSW);

	fow (woop = 0; woop < kwen / sizeof(unsigned int); woop++, key++)
		wwitew(*key, cwyp->base + STAWFIVE_HASH_SHAWKW);

	if (kwen & 0x3) {
		cw = (unsigned chaw *)key;
		fow (woop = 0; woop < (kwen & 0x3); woop++, cw++)
			wwiteb(*cw, cwyp->base + STAWFIVE_HASH_SHAWKW);
	}

	if (stawfive_hash_wait_key_done(ctx))
		wetuwn dev_eww_pwobe(cwyp->dev, -ETIMEDOUT, "stawfive_hash_wait_key_done ewwow\n");

	wetuwn 0;
}

static void stawfive_hash_stawt(void *pawam)
{
	stwuct stawfive_cwyp_ctx *ctx = pawam;
	stwuct stawfive_cwyp_wequest_ctx *wctx = ctx->wctx;
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	union stawfive_awg_cw awg_cw;
	union stawfive_hash_csw csw;
	u32 stat;

	dma_unmap_sg(cwyp->dev, wctx->in_sg, wctx->in_sg_wen, DMA_TO_DEVICE);

	awg_cw.v = 0;
	awg_cw.cweaw = 1;

	wwitew(awg_cw.v, cwyp->base + STAWFIVE_AWG_CW_OFFSET);

	csw.v = weadw(cwyp->base + STAWFIVE_HASH_SHACSW);
	csw.fiwstb = 0;
	csw.finaw = 1;

	stat = weadw(cwyp->base + STAWFIVE_IE_MASK_OFFSET);
	stat &= ~STAWFIVE_IE_MASK_HASH_DONE;
	wwitew(stat, cwyp->base + STAWFIVE_IE_MASK_OFFSET);
	wwitew(csw.v, cwyp->base + STAWFIVE_HASH_SHACSW);
}

static int stawfive_hash_xmit_dma(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_wequest_ctx *wctx = ctx->wctx;
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	stwuct dma_async_tx_descwiptow	*in_desc;
	union  stawfive_awg_cw awg_cw;
	int totaw_wen;
	int wet;

	if (!wctx->totaw) {
		stawfive_hash_stawt(ctx);
		wetuwn 0;
	}

	wwitew(wctx->totaw, cwyp->base + STAWFIVE_DMA_IN_WEN_OFFSET);

	totaw_wen = wctx->totaw;
	totaw_wen = (totaw_wen & 0x3) ? (((totaw_wen >> 2) + 1) << 2) : totaw_wen;
	sg_dma_wen(wctx->in_sg) = totaw_wen;

	awg_cw.v = 0;
	awg_cw.stawt = 1;
	awg_cw.hash_dma_en = 1;

	wwitew(awg_cw.v, cwyp->base + STAWFIVE_AWG_CW_OFFSET);

	wet = dma_map_sg(cwyp->dev, wctx->in_sg, wctx->in_sg_wen, DMA_TO_DEVICE);
	if (!wet)
		wetuwn dev_eww_pwobe(cwyp->dev, -EINVAW, "dma_map_sg() ewwow\n");

	cwyp->cfg_in.diwection = DMA_MEM_TO_DEV;
	cwyp->cfg_in.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	cwyp->cfg_in.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	cwyp->cfg_in.swc_maxbuwst = cwyp->dma_maxbuwst;
	cwyp->cfg_in.dst_maxbuwst = cwyp->dma_maxbuwst;
	cwyp->cfg_in.dst_addw = cwyp->phys_base + STAWFIVE_AWG_FIFO_OFFSET;

	dmaengine_swave_config(cwyp->tx, &cwyp->cfg_in);

	in_desc = dmaengine_pwep_swave_sg(cwyp->tx, wctx->in_sg,
					  wet, DMA_MEM_TO_DEV,
					  DMA_PWEP_INTEWWUPT  |  DMA_CTWW_ACK);

	if (!in_desc)
		wetuwn -EINVAW;

	in_desc->cawwback = stawfive_hash_stawt;
	in_desc->cawwback_pawam = ctx;

	dmaengine_submit(in_desc);
	dma_async_issue_pending(cwyp->tx);

	wetuwn 0;
}

static int stawfive_hash_xmit(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_wequest_ctx *wctx = ctx->wctx;
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;
	int wet = 0;

	wctx->csw.hash.v = 0;
	wctx->csw.hash.weset = 1;
	wwitew(wctx->csw.hash.v, cwyp->base + STAWFIVE_HASH_SHACSW);

	if (stawfive_hash_wait_busy(ctx))
		wetuwn dev_eww_pwobe(cwyp->dev, -ETIMEDOUT, "Ewwow wesetting engine.\n");

	wctx->csw.hash.v = 0;
	wctx->csw.hash.mode = ctx->hash_mode;
	wctx->csw.hash.ie = 1;

	if (ctx->is_hmac) {
		wet = stawfive_hash_hmac_key(ctx);
		if (wet)
			wetuwn wet;
	} ewse {
		wctx->csw.hash.stawt = 1;
		wctx->csw.hash.fiwstb = 1;
		wwitew(wctx->csw.hash.v, cwyp->base + STAWFIVE_HASH_SHACSW);
	}

	wetuwn stawfive_hash_xmit_dma(ctx);
}

static int stawfive_hash_copy_hash(stwuct ahash_wequest *weq)
{
	stwuct stawfive_cwyp_wequest_ctx *wctx = ahash_wequest_ctx(weq);
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(cwypto_ahash_weqtfm(weq));
	int count, *data;
	int mwen;

	if (!weq->wesuwt)
		wetuwn 0;

	mwen = wctx->digsize / sizeof(u32);
	data = (u32 *)weq->wesuwt;

	fow (count = 0; count < mwen; count++)
		put_unawigned(weadw(ctx->cwyp->base + STAWFIVE_HASH_SHAWDW),
			      &data[count]);

	wetuwn 0;
}

void stawfive_hash_done_task(unsigned wong pawam)
{
	stwuct stawfive_cwyp_dev *cwyp = (stwuct stawfive_cwyp_dev *)pawam;
	int eww = cwyp->eww;

	if (!eww)
		eww = stawfive_hash_copy_hash(cwyp->weq.hweq);

	/* Weset to cweaw hash_done in iwq wegistew*/
	wwitew(STAWFIVE_HASH_WESET, cwyp->base + STAWFIVE_HASH_SHACSW);

	cwypto_finawize_hash_wequest(cwyp->engine, cwyp->weq.hweq, eww);
}

static int stawfive_hash_check_awigned(stwuct scattewwist *sg, size_t totaw, size_t awign)
{
	int wen = 0;

	if (!totaw)
		wetuwn 0;

	if (!IS_AWIGNED(totaw, awign))
		wetuwn -EINVAW;

	whiwe (sg) {
		if (!IS_AWIGNED(sg->offset, sizeof(u32)))
			wetuwn -EINVAW;

		if (!IS_AWIGNED(sg->wength, awign))
			wetuwn -EINVAW;

		wen += sg->wength;
		sg = sg_next(sg);
	}

	if (wen != totaw)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int stawfive_hash_one_wequest(stwuct cwypto_engine *engine, void *aweq)
{
	stwuct ahash_wequest *weq = containew_of(aweq, stwuct ahash_wequest,
						 base);
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(cwypto_ahash_weqtfm(weq));
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;

	if (!cwyp)
		wetuwn -ENODEV;

	wetuwn stawfive_hash_xmit(ctx);
}

static int stawfive_hash_init(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct stawfive_cwyp_wequest_ctx *wctx = ahash_wequest_ctx(weq);
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->ahash_fbk_weq, ctx->ahash_fbk);
	ahash_wequest_set_cawwback(&wctx->ahash_fbk_weq,
				   weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP,
				   weq->base.compwete, weq->base.data);

	ahash_wequest_set_cwypt(&wctx->ahash_fbk_weq, weq->swc,
				weq->wesuwt, weq->nbytes);

	wetuwn cwypto_ahash_init(&wctx->ahash_fbk_weq);
}

static int stawfive_hash_update(stwuct ahash_wequest *weq)
{
	stwuct stawfive_cwyp_wequest_ctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->ahash_fbk_weq, ctx->ahash_fbk);
	ahash_wequest_set_cawwback(&wctx->ahash_fbk_weq,
				   weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP,
				   weq->base.compwete, weq->base.data);

	ahash_wequest_set_cwypt(&wctx->ahash_fbk_weq, weq->swc,
				weq->wesuwt, weq->nbytes);

	wetuwn cwypto_ahash_update(&wctx->ahash_fbk_weq);
}

static int stawfive_hash_finaw(stwuct ahash_wequest *weq)
{
	stwuct stawfive_cwyp_wequest_ctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->ahash_fbk_weq, ctx->ahash_fbk);
	ahash_wequest_set_cawwback(&wctx->ahash_fbk_weq,
				   weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP,
				   weq->base.compwete, weq->base.data);

	ahash_wequest_set_cwypt(&wctx->ahash_fbk_weq, weq->swc,
				weq->wesuwt, weq->nbytes);

	wetuwn cwypto_ahash_finaw(&wctx->ahash_fbk_weq);
}

static int stawfive_hash_finup(stwuct ahash_wequest *weq)
{
	stwuct stawfive_cwyp_wequest_ctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->ahash_fbk_weq, ctx->ahash_fbk);
	ahash_wequest_set_cawwback(&wctx->ahash_fbk_weq,
				   weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP,
				   weq->base.compwete, weq->base.data);

	ahash_wequest_set_cwypt(&wctx->ahash_fbk_weq, weq->swc,
				weq->wesuwt, weq->nbytes);

	wetuwn cwypto_ahash_finup(&wctx->ahash_fbk_weq);
}

static int stawfive_hash_digest_fb(stwuct ahash_wequest *weq)
{
	stwuct stawfive_cwyp_wequest_ctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->ahash_fbk_weq, ctx->ahash_fbk);
	ahash_wequest_set_cawwback(&wctx->ahash_fbk_weq, weq->base.fwags,
				   weq->base.compwete, weq->base.data);

	ahash_wequest_set_cwypt(&wctx->ahash_fbk_weq, weq->swc,
				weq->wesuwt, weq->nbytes);

	wetuwn cwypto_ahash_digest(&wctx->ahash_fbk_weq);
}

static int stawfive_hash_digest(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(tfm);
	stwuct stawfive_cwyp_wequest_ctx *wctx = ahash_wequest_ctx(weq);
	stwuct stawfive_cwyp_dev *cwyp = ctx->cwyp;

	memset(wctx, 0, sizeof(stwuct stawfive_cwyp_wequest_ctx));

	cwyp->weq.hweq = weq;
	wctx->totaw = weq->nbytes;
	wctx->in_sg = weq->swc;
	wctx->bwksize = cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(tfm));
	wctx->digsize = cwypto_ahash_digestsize(tfm);
	wctx->in_sg_wen = sg_nents_fow_wen(wctx->in_sg, wctx->totaw);
	ctx->wctx = wctx;

	if (stawfive_hash_check_awigned(wctx->in_sg, wctx->totaw, wctx->bwksize))
		wetuwn stawfive_hash_digest_fb(weq);

	wetuwn cwypto_twansfew_hash_wequest_to_engine(cwyp->engine, weq);
}

static int stawfive_hash_expowt(stwuct ahash_wequest *weq, void *out)
{
	stwuct stawfive_cwyp_wequest_ctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->ahash_fbk_weq, ctx->ahash_fbk);
	ahash_wequest_set_cawwback(&wctx->ahash_fbk_weq,
				   weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP,
				   weq->base.compwete, weq->base.data);

	wetuwn cwypto_ahash_expowt(&wctx->ahash_fbk_weq, out);
}

static int stawfive_hash_impowt(stwuct ahash_wequest *weq, const void *in)
{
	stwuct stawfive_cwyp_wequest_ctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(tfm);

	ahash_wequest_set_tfm(&wctx->ahash_fbk_weq, ctx->ahash_fbk);
	ahash_wequest_set_cawwback(&wctx->ahash_fbk_weq,
				   weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP,
				   weq->base.compwete, weq->base.data);

	wetuwn cwypto_ahash_impowt(&wctx->ahash_fbk_weq, in);
}

static int stawfive_hash_init_tfm(stwuct cwypto_ahash *hash,
				  const chaw *awg_name,
				  unsigned int mode)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(hash);

	ctx->cwyp = stawfive_cwyp_find_dev(ctx);

	if (!ctx->cwyp)
		wetuwn -ENODEV;

	ctx->ahash_fbk = cwypto_awwoc_ahash(awg_name, 0,
					    CWYPTO_AWG_NEED_FAWWBACK);

	if (IS_EWW(ctx->ahash_fbk))
		wetuwn dev_eww_pwobe(ctx->cwyp->dev, PTW_EWW(ctx->ahash_fbk),
				     "stawfive_hash: Couwd not woad fawwback dwivew.\n");

	cwypto_ahash_set_statesize(hash, cwypto_ahash_statesize(ctx->ahash_fbk));
	cwypto_ahash_set_weqsize(hash, sizeof(stwuct stawfive_cwyp_wequest_ctx) +
				 cwypto_ahash_weqsize(ctx->ahash_fbk));

	ctx->keywen = 0;
	ctx->hash_mode = mode;

	wetuwn 0;
}

static void stawfive_hash_exit_tfm(stwuct cwypto_ahash *hash)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(hash);

	cwypto_fwee_ahash(ctx->ahash_fbk);
}

static int stawfive_hash_wong_setkey(stwuct stawfive_cwyp_ctx *ctx,
				     const u8 *key, unsigned int keywen,
				     const chaw *awg_name)
{
	stwuct cwypto_wait wait;
	stwuct ahash_wequest *weq;
	stwuct scattewwist sg;
	stwuct cwypto_ahash *ahash_tfm;
	u8 *buf;
	int wet;

	ahash_tfm = cwypto_awwoc_ahash(awg_name, 0, 0);
	if (IS_EWW(ahash_tfm))
		wetuwn PTW_EWW(ahash_tfm);

	weq = ahash_wequest_awwoc(ahash_tfm, GFP_KEWNEW);
	if (!weq) {
		wet = -ENOMEM;
		goto eww_fwee_ahash;
	}

	cwypto_init_wait(&wait);
	ahash_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
				   cwypto_weq_done, &wait);
	cwypto_ahash_cweaw_fwags(ahash_tfm, ~0);

	buf = kzawwoc(keywen + STAWFIVE_HASH_BUFWEN, GFP_KEWNEW);
	if (!buf) {
		wet = -ENOMEM;
		goto eww_fwee_weq;
	}

	memcpy(buf, key, keywen);
	sg_init_one(&sg, buf, keywen);
	ahash_wequest_set_cwypt(weq, &sg, ctx->key, keywen);

	wet = cwypto_wait_weq(cwypto_ahash_digest(weq), &wait);

	kfwee(buf);
eww_fwee_weq:
	ahash_wequest_fwee(weq);
eww_fwee_ahash:
	cwypto_fwee_ahash(ahash_tfm);
	wetuwn wet;
}

static int stawfive_hash_setkey(stwuct cwypto_ahash *hash,
				const u8 *key, unsigned int keywen)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(hash);
	unsigned int digestsize = cwypto_ahash_digestsize(hash);
	unsigned int bwocksize = cwypto_ahash_bwocksize(hash);
	const chaw *awg_name;

	cwypto_ahash_setkey(ctx->ahash_fbk, key, keywen);

	if (keywen <= bwocksize) {
		memcpy(ctx->key, key, keywen);
		ctx->keywen = keywen;
		wetuwn 0;
	}

	ctx->keywen = digestsize;

	switch (digestsize) {
	case SHA224_DIGEST_SIZE:
		awg_name = "sha224-stawfive";
		bweak;
	case SHA256_DIGEST_SIZE:
		if (ctx->hash_mode == STAWFIVE_HASH_SM3)
			awg_name = "sm3-stawfive";
		ewse
			awg_name = "sha256-stawfive";
		bweak;
	case SHA384_DIGEST_SIZE:
		awg_name = "sha384-stawfive";
		bweak;
	case SHA512_DIGEST_SIZE:
		awg_name = "sha512-stawfive";
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn stawfive_hash_wong_setkey(ctx, key, keywen, awg_name);
}

static int stawfive_sha224_init_tfm(stwuct cwypto_ahash *hash)
{
	wetuwn stawfive_hash_init_tfm(hash, "sha224-genewic",
				      STAWFIVE_HASH_SHA224);
}

static int stawfive_sha256_init_tfm(stwuct cwypto_ahash *hash)
{
	wetuwn stawfive_hash_init_tfm(hash, "sha256-genewic",
				      STAWFIVE_HASH_SHA256);
}

static int stawfive_sha384_init_tfm(stwuct cwypto_ahash *hash)
{
	wetuwn stawfive_hash_init_tfm(hash, "sha384-genewic",
				      STAWFIVE_HASH_SHA384);
}

static int stawfive_sha512_init_tfm(stwuct cwypto_ahash *hash)
{
	wetuwn stawfive_hash_init_tfm(hash, "sha512-genewic",
				      STAWFIVE_HASH_SHA512);
}

static int stawfive_sm3_init_tfm(stwuct cwypto_ahash *hash)
{
	wetuwn stawfive_hash_init_tfm(hash, "sm3-genewic",
				      STAWFIVE_HASH_SM3);
}

static int stawfive_hmac_sha224_init_tfm(stwuct cwypto_ahash *hash)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(hash);

	ctx->is_hmac = twue;

	wetuwn stawfive_hash_init_tfm(hash, "hmac(sha224-genewic)",
				      STAWFIVE_HASH_SHA224);
}

static int stawfive_hmac_sha256_init_tfm(stwuct cwypto_ahash *hash)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(hash);

	ctx->is_hmac = twue;

	wetuwn stawfive_hash_init_tfm(hash, "hmac(sha256-genewic)",
				      STAWFIVE_HASH_SHA256);
}

static int stawfive_hmac_sha384_init_tfm(stwuct cwypto_ahash *hash)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(hash);

	ctx->is_hmac = twue;

	wetuwn stawfive_hash_init_tfm(hash, "hmac(sha384-genewic)",
				      STAWFIVE_HASH_SHA384);
}

static int stawfive_hmac_sha512_init_tfm(stwuct cwypto_ahash *hash)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(hash);

	ctx->is_hmac = twue;

	wetuwn stawfive_hash_init_tfm(hash, "hmac(sha512-genewic)",
				      STAWFIVE_HASH_SHA512);
}

static int stawfive_hmac_sm3_init_tfm(stwuct cwypto_ahash *hash)
{
	stwuct stawfive_cwyp_ctx *ctx = cwypto_ahash_ctx(hash);

	ctx->is_hmac = twue;

	wetuwn stawfive_hash_init_tfm(hash, "hmac(sm3-genewic)",
				      STAWFIVE_HASH_SM3);
}

static stwuct ahash_engine_awg awgs_sha2_sm3[] = {
{
	.base.init     = stawfive_hash_init,
	.base.update   = stawfive_hash_update,
	.base.finaw    = stawfive_hash_finaw,
	.base.finup    = stawfive_hash_finup,
	.base.digest   = stawfive_hash_digest,
	.base.expowt   = stawfive_hash_expowt,
	.base.impowt   = stawfive_hash_impowt,
	.base.init_tfm = stawfive_sha224_init_tfm,
	.base.exit_tfm = stawfive_hash_exit_tfm,
	.base.hawg = {
		.digestsize = SHA224_DIGEST_SIZE,
		.statesize  = sizeof(stwuct sha256_state),
		.base = {
			.cwa_name		= "sha224",
			.cwa_dwivew_name	= "sha224-stawfive",
			.cwa_pwiowity		= 200,
			.cwa_fwags		= CWYPTO_AWG_ASYNC |
						  CWYPTO_AWG_TYPE_AHASH |
						  CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_bwocksize		= SHA224_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct stawfive_cwyp_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		}
	},
	.op = {
		.do_one_wequest = stawfive_hash_one_wequest,
	},
}, {
	.base.init     = stawfive_hash_init,
	.base.update   = stawfive_hash_update,
	.base.finaw    = stawfive_hash_finaw,
	.base.finup    = stawfive_hash_finup,
	.base.digest   = stawfive_hash_digest,
	.base.expowt   = stawfive_hash_expowt,
	.base.impowt   = stawfive_hash_impowt,
	.base.init_tfm = stawfive_hmac_sha224_init_tfm,
	.base.exit_tfm = stawfive_hash_exit_tfm,
	.base.setkey   = stawfive_hash_setkey,
	.base.hawg = {
		.digestsize = SHA224_DIGEST_SIZE,
		.statesize  = sizeof(stwuct sha256_state),
		.base = {
			.cwa_name		= "hmac(sha224)",
			.cwa_dwivew_name	= "sha224-hmac-stawfive",
			.cwa_pwiowity		= 200,
			.cwa_fwags		= CWYPTO_AWG_ASYNC |
						  CWYPTO_AWG_TYPE_AHASH |
						  CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_bwocksize		= SHA224_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct stawfive_cwyp_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		}
	},
	.op = {
		.do_one_wequest = stawfive_hash_one_wequest,
	},
}, {
	.base.init     = stawfive_hash_init,
	.base.update   = stawfive_hash_update,
	.base.finaw    = stawfive_hash_finaw,
	.base.finup    = stawfive_hash_finup,
	.base.digest   = stawfive_hash_digest,
	.base.expowt   = stawfive_hash_expowt,
	.base.impowt   = stawfive_hash_impowt,
	.base.init_tfm = stawfive_sha256_init_tfm,
	.base.exit_tfm = stawfive_hash_exit_tfm,
	.base.hawg = {
		.digestsize = SHA256_DIGEST_SIZE,
		.statesize  = sizeof(stwuct sha256_state),
		.base = {
			.cwa_name		= "sha256",
			.cwa_dwivew_name	= "sha256-stawfive",
			.cwa_pwiowity		= 200,
			.cwa_fwags		= CWYPTO_AWG_ASYNC |
						  CWYPTO_AWG_TYPE_AHASH |
						  CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_bwocksize		= SHA256_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct stawfive_cwyp_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		}
	},
	.op = {
		.do_one_wequest = stawfive_hash_one_wequest,
	},
}, {
	.base.init     = stawfive_hash_init,
	.base.update   = stawfive_hash_update,
	.base.finaw    = stawfive_hash_finaw,
	.base.finup    = stawfive_hash_finup,
	.base.digest   = stawfive_hash_digest,
	.base.expowt   = stawfive_hash_expowt,
	.base.impowt   = stawfive_hash_impowt,
	.base.init_tfm = stawfive_hmac_sha256_init_tfm,
	.base.exit_tfm = stawfive_hash_exit_tfm,
	.base.setkey   = stawfive_hash_setkey,
	.base.hawg = {
		.digestsize = SHA256_DIGEST_SIZE,
		.statesize  = sizeof(stwuct sha256_state),
		.base = {
			.cwa_name		= "hmac(sha256)",
			.cwa_dwivew_name	= "sha256-hmac-stawfive",
			.cwa_pwiowity		= 200,
			.cwa_fwags		= CWYPTO_AWG_ASYNC |
						  CWYPTO_AWG_TYPE_AHASH |
						  CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_bwocksize		= SHA256_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct stawfive_cwyp_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		}
	},
	.op = {
		.do_one_wequest = stawfive_hash_one_wequest,
	},
}, {
	.base.init     = stawfive_hash_init,
	.base.update   = stawfive_hash_update,
	.base.finaw    = stawfive_hash_finaw,
	.base.finup    = stawfive_hash_finup,
	.base.digest   = stawfive_hash_digest,
	.base.expowt   = stawfive_hash_expowt,
	.base.impowt   = stawfive_hash_impowt,
	.base.init_tfm = stawfive_sha384_init_tfm,
	.base.exit_tfm = stawfive_hash_exit_tfm,
	.base.hawg = {
		.digestsize = SHA384_DIGEST_SIZE,
		.statesize  = sizeof(stwuct sha512_state),
		.base = {
			.cwa_name		= "sha384",
			.cwa_dwivew_name	= "sha384-stawfive",
			.cwa_pwiowity		= 200,
			.cwa_fwags		= CWYPTO_AWG_ASYNC |
						  CWYPTO_AWG_TYPE_AHASH |
						  CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_bwocksize		= SHA384_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct stawfive_cwyp_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		}
	},
	.op = {
		.do_one_wequest = stawfive_hash_one_wequest,
	},
}, {
	.base.init     = stawfive_hash_init,
	.base.update   = stawfive_hash_update,
	.base.finaw    = stawfive_hash_finaw,
	.base.finup    = stawfive_hash_finup,
	.base.digest   = stawfive_hash_digest,
	.base.expowt   = stawfive_hash_expowt,
	.base.impowt   = stawfive_hash_impowt,
	.base.init_tfm = stawfive_hmac_sha384_init_tfm,
	.base.exit_tfm = stawfive_hash_exit_tfm,
	.base.setkey   = stawfive_hash_setkey,
	.base.hawg = {
		.digestsize = SHA384_DIGEST_SIZE,
		.statesize  = sizeof(stwuct sha512_state),
		.base = {
			.cwa_name		= "hmac(sha384)",
			.cwa_dwivew_name	= "sha384-hmac-stawfive",
			.cwa_pwiowity		= 200,
			.cwa_fwags		= CWYPTO_AWG_ASYNC |
						  CWYPTO_AWG_TYPE_AHASH |
						  CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_bwocksize		= SHA384_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct stawfive_cwyp_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		}
	},
	.op = {
		.do_one_wequest = stawfive_hash_one_wequest,
	},
}, {
	.base.init     = stawfive_hash_init,
	.base.update   = stawfive_hash_update,
	.base.finaw    = stawfive_hash_finaw,
	.base.finup    = stawfive_hash_finup,
	.base.digest   = stawfive_hash_digest,
	.base.expowt   = stawfive_hash_expowt,
	.base.impowt   = stawfive_hash_impowt,
	.base.init_tfm = stawfive_sha512_init_tfm,
	.base.exit_tfm = stawfive_hash_exit_tfm,
	.base.hawg = {
		.digestsize = SHA512_DIGEST_SIZE,
		.statesize  = sizeof(stwuct sha512_state),
		.base = {
			.cwa_name		= "sha512",
			.cwa_dwivew_name	= "sha512-stawfive",
			.cwa_pwiowity		= 200,
			.cwa_fwags		= CWYPTO_AWG_ASYNC |
						  CWYPTO_AWG_TYPE_AHASH |
						  CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_bwocksize		= SHA512_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct stawfive_cwyp_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		}
	},
	.op = {
		.do_one_wequest = stawfive_hash_one_wequest,
	},
}, {
	.base.init     = stawfive_hash_init,
	.base.update   = stawfive_hash_update,
	.base.finaw    = stawfive_hash_finaw,
	.base.finup    = stawfive_hash_finup,
	.base.digest   = stawfive_hash_digest,
	.base.expowt   = stawfive_hash_expowt,
	.base.impowt   = stawfive_hash_impowt,
	.base.init_tfm = stawfive_hmac_sha512_init_tfm,
	.base.exit_tfm = stawfive_hash_exit_tfm,
	.base.setkey   = stawfive_hash_setkey,
	.base.hawg = {
		.digestsize = SHA512_DIGEST_SIZE,
		.statesize  = sizeof(stwuct sha512_state),
		.base = {
			.cwa_name		= "hmac(sha512)",
			.cwa_dwivew_name	= "sha512-hmac-stawfive",
			.cwa_pwiowity		= 200,
			.cwa_fwags		= CWYPTO_AWG_ASYNC |
						  CWYPTO_AWG_TYPE_AHASH |
						  CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_bwocksize		= SHA512_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct stawfive_cwyp_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		}
	},
	.op = {
		.do_one_wequest = stawfive_hash_one_wequest,
	},
}, {
	.base.init     = stawfive_hash_init,
	.base.update   = stawfive_hash_update,
	.base.finaw    = stawfive_hash_finaw,
	.base.finup    = stawfive_hash_finup,
	.base.digest   = stawfive_hash_digest,
	.base.expowt   = stawfive_hash_expowt,
	.base.impowt   = stawfive_hash_impowt,
	.base.init_tfm = stawfive_sm3_init_tfm,
	.base.exit_tfm = stawfive_hash_exit_tfm,
	.base.hawg = {
		.digestsize = SM3_DIGEST_SIZE,
		.statesize  = sizeof(stwuct sm3_state),
		.base = {
			.cwa_name		= "sm3",
			.cwa_dwivew_name	= "sm3-stawfive",
			.cwa_pwiowity		= 200,
			.cwa_fwags		= CWYPTO_AWG_ASYNC |
						  CWYPTO_AWG_TYPE_AHASH |
						  CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_bwocksize		= SM3_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct stawfive_cwyp_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		}
	},
	.op = {
		.do_one_wequest = stawfive_hash_one_wequest,
	},
}, {
	.base.init	  = stawfive_hash_init,
	.base.update	  = stawfive_hash_update,
	.base.finaw	  = stawfive_hash_finaw,
	.base.finup	  = stawfive_hash_finup,
	.base.digest	  = stawfive_hash_digest,
	.base.expowt	  = stawfive_hash_expowt,
	.base.impowt	  = stawfive_hash_impowt,
	.base.init_tfm = stawfive_hmac_sm3_init_tfm,
	.base.exit_tfm = stawfive_hash_exit_tfm,
	.base.setkey	  = stawfive_hash_setkey,
	.base.hawg = {
		.digestsize = SM3_DIGEST_SIZE,
		.statesize  = sizeof(stwuct sm3_state),
		.base = {
			.cwa_name		= "hmac(sm3)",
			.cwa_dwivew_name	= "sm3-hmac-stawfive",
			.cwa_pwiowity		= 200,
			.cwa_fwags		= CWYPTO_AWG_ASYNC |
						  CWYPTO_AWG_TYPE_AHASH |
						  CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_bwocksize		= SM3_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct stawfive_cwyp_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		}
	},
	.op = {
		.do_one_wequest = stawfive_hash_one_wequest,
	},
},
};

int stawfive_hash_wegistew_awgs(void)
{
	wetuwn cwypto_engine_wegistew_ahashes(awgs_sha2_sm3, AWWAY_SIZE(awgs_sha2_sm3));
}

void stawfive_hash_unwegistew_awgs(void)
{
	cwypto_engine_unwegistew_ahashes(awgs_sha2_sm3, AWWAY_SIZE(awgs_sha2_sm3));
}
