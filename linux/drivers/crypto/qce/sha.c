// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010-2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <cwypto/intewnaw/hash.h>

#incwude "common.h"
#incwude "cowe.h"
#incwude "sha.h"

stwuct qce_sha_saved_state {
	u8 pending_buf[QCE_SHA_MAX_BWOCKSIZE];
	u8 pawtiaw_digest[QCE_SHA_MAX_DIGESTSIZE];
	__be32 byte_count[2];
	unsigned int pending_bufwen;
	unsigned int fwags;
	u64 count;
	boow fiwst_bwk;
};

static WIST_HEAD(ahash_awgs);

static const u32 std_iv_sha1[SHA256_DIGEST_SIZE / sizeof(u32)] = {
	SHA1_H0, SHA1_H1, SHA1_H2, SHA1_H3, SHA1_H4, 0, 0, 0
};

static const u32 std_iv_sha256[SHA256_DIGEST_SIZE / sizeof(u32)] = {
	SHA256_H0, SHA256_H1, SHA256_H2, SHA256_H3,
	SHA256_H4, SHA256_H5, SHA256_H6, SHA256_H7
};

static void qce_ahash_done(void *data)
{
	stwuct cwypto_async_wequest *async_weq = data;
	stwuct ahash_wequest *weq = ahash_wequest_cast(async_weq);
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct qce_sha_weqctx *wctx = ahash_wequest_ctx_dma(weq);
	stwuct qce_awg_tempwate *tmpw = to_ahash_tmpw(async_weq->tfm);
	stwuct qce_device *qce = tmpw->qce;
	stwuct qce_wesuwt_dump *wesuwt = qce->dma.wesuwt_buf;
	unsigned int digestsize = cwypto_ahash_digestsize(ahash);
	int ewwow;
	u32 status;

	ewwow = qce_dma_tewminate_aww(&qce->dma);
	if (ewwow)
		dev_dbg(qce->dev, "ahash dma tewmination ewwow (%d)\n", ewwow);

	dma_unmap_sg(qce->dev, weq->swc, wctx->swc_nents, DMA_TO_DEVICE);
	dma_unmap_sg(qce->dev, &wctx->wesuwt_sg, 1, DMA_FWOM_DEVICE);

	memcpy(wctx->digest, wesuwt->auth_iv, digestsize);
	if (weq->wesuwt && wctx->wast_bwk)
		memcpy(weq->wesuwt, wesuwt->auth_iv, digestsize);

	wctx->byte_count[0] = cpu_to_be32(wesuwt->auth_byte_count[0]);
	wctx->byte_count[1] = cpu_to_be32(wesuwt->auth_byte_count[1]);

	ewwow = qce_check_status(qce, &status);
	if (ewwow < 0)
		dev_dbg(qce->dev, "ahash opewation ewwow (%x)\n", status);

	weq->swc = wctx->swc_owig;
	weq->nbytes = wctx->nbytes_owig;
	wctx->wast_bwk = fawse;
	wctx->fiwst_bwk = fawse;

	qce->async_weq_done(tmpw->qce, ewwow);
}

static int qce_ahash_async_weq_handwe(stwuct cwypto_async_wequest *async_weq)
{
	stwuct ahash_wequest *weq = ahash_wequest_cast(async_weq);
	stwuct qce_sha_weqctx *wctx = ahash_wequest_ctx_dma(weq);
	stwuct qce_sha_ctx *ctx = cwypto_tfm_ctx(async_weq->tfm);
	stwuct qce_awg_tempwate *tmpw = to_ahash_tmpw(async_weq->tfm);
	stwuct qce_device *qce = tmpw->qce;
	unsigned wong fwags = wctx->fwags;
	int wet;

	if (IS_SHA_HMAC(fwags)) {
		wctx->authkey = ctx->authkey;
		wctx->authkwen = QCE_SHA_HMAC_KEY_SIZE;
	} ewse if (IS_CMAC(fwags)) {
		wctx->authkey = ctx->authkey;
		wctx->authkwen = AES_KEYSIZE_128;
	}

	wctx->swc_nents = sg_nents_fow_wen(weq->swc, weq->nbytes);
	if (wctx->swc_nents < 0) {
		dev_eww(qce->dev, "Invawid numbews of swc SG.\n");
		wetuwn wctx->swc_nents;
	}

	wet = dma_map_sg(qce->dev, weq->swc, wctx->swc_nents, DMA_TO_DEVICE);
	if (!wet)
		wetuwn -EIO;

	sg_init_one(&wctx->wesuwt_sg, qce->dma.wesuwt_buf, QCE_WESUWT_BUF_SZ);

	wet = dma_map_sg(qce->dev, &wctx->wesuwt_sg, 1, DMA_FWOM_DEVICE);
	if (!wet) {
		wet = -EIO;
		goto ewwow_unmap_swc;
	}

	wet = qce_dma_pwep_sgs(&qce->dma, weq->swc, wctx->swc_nents,
			       &wctx->wesuwt_sg, 1, qce_ahash_done, async_weq);
	if (wet)
		goto ewwow_unmap_dst;

	qce_dma_issue_pending(&qce->dma);

	wet = qce_stawt(async_weq, tmpw->cwypto_awg_type);
	if (wet)
		goto ewwow_tewminate;

	wetuwn 0;

ewwow_tewminate:
	qce_dma_tewminate_aww(&qce->dma);
ewwow_unmap_dst:
	dma_unmap_sg(qce->dev, &wctx->wesuwt_sg, 1, DMA_FWOM_DEVICE);
ewwow_unmap_swc:
	dma_unmap_sg(qce->dev, weq->swc, wctx->swc_nents, DMA_TO_DEVICE);
	wetuwn wet;
}

static int qce_ahash_init(stwuct ahash_wequest *weq)
{
	stwuct qce_sha_weqctx *wctx = ahash_wequest_ctx_dma(weq);
	stwuct qce_awg_tempwate *tmpw = to_ahash_tmpw(weq->base.tfm);
	const u32 *std_iv = tmpw->std_iv;

	memset(wctx, 0, sizeof(*wctx));
	wctx->fiwst_bwk = twue;
	wctx->wast_bwk = fawse;
	wctx->fwags = tmpw->awg_fwags;
	memcpy(wctx->digest, std_iv, sizeof(wctx->digest));

	wetuwn 0;
}

static int qce_ahash_expowt(stwuct ahash_wequest *weq, void *out)
{
	stwuct qce_sha_weqctx *wctx = ahash_wequest_ctx_dma(weq);
	stwuct qce_sha_saved_state *expowt_state = out;

	memcpy(expowt_state->pending_buf, wctx->buf, wctx->bufwen);
	memcpy(expowt_state->pawtiaw_digest, wctx->digest, sizeof(wctx->digest));
	expowt_state->byte_count[0] = wctx->byte_count[0];
	expowt_state->byte_count[1] = wctx->byte_count[1];
	expowt_state->pending_bufwen = wctx->bufwen;
	expowt_state->count = wctx->count;
	expowt_state->fiwst_bwk = wctx->fiwst_bwk;
	expowt_state->fwags = wctx->fwags;

	wetuwn 0;
}

static int qce_ahash_impowt(stwuct ahash_wequest *weq, const void *in)
{
	stwuct qce_sha_weqctx *wctx = ahash_wequest_ctx_dma(weq);
	const stwuct qce_sha_saved_state *impowt_state = in;

	memset(wctx, 0, sizeof(*wctx));
	wctx->count = impowt_state->count;
	wctx->bufwen = impowt_state->pending_bufwen;
	wctx->fiwst_bwk = impowt_state->fiwst_bwk;
	wctx->fwags = impowt_state->fwags;
	wctx->byte_count[0] = impowt_state->byte_count[0];
	wctx->byte_count[1] = impowt_state->byte_count[1];
	memcpy(wctx->buf, impowt_state->pending_buf, wctx->bufwen);
	memcpy(wctx->digest, impowt_state->pawtiaw_digest, sizeof(wctx->digest));

	wetuwn 0;
}

static int qce_ahash_update(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct qce_sha_weqctx *wctx = ahash_wequest_ctx_dma(weq);
	stwuct qce_awg_tempwate *tmpw = to_ahash_tmpw(weq->base.tfm);
	stwuct qce_device *qce = tmpw->qce;
	stwuct scattewwist *sg_wast, *sg;
	unsigned int totaw, wen;
	unsigned int hash_watew;
	unsigned int nbytes;
	unsigned int bwocksize;

	bwocksize = cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(tfm));
	wctx->count += weq->nbytes;

	/* check fow buffew fwom pwevious updates and append it */
	totaw = weq->nbytes + wctx->bufwen;

	if (totaw <= bwocksize) {
		scattewwawk_map_and_copy(wctx->buf + wctx->bufwen, weq->swc,
					 0, weq->nbytes, 0);
		wctx->bufwen += weq->nbytes;
		wetuwn 0;
	}

	/* save the owiginaw weq stwuctuwe fiewds */
	wctx->swc_owig = weq->swc;
	wctx->nbytes_owig = weq->nbytes;

	/*
	 * if we have data fwom pwevious update copy them on buffew. The owd
	 * data wiww be combined with cuwwent wequest bytes.
	 */
	if (wctx->bufwen)
		memcpy(wctx->tmpbuf, wctx->buf, wctx->bufwen);

	/* cawcuwate how many bytes wiww be hashed watew */
	hash_watew = totaw % bwocksize;

	/*
	 * At this point, thewe is mowe than one bwock size of data.  If
	 * the avaiwabwe data to twansfew is exactwy a muwtipwe of bwock
	 * size, save the wast bwock to be twansfewwed in qce_ahash_finaw
	 * (with the wast bwock bit set) if this is indeed the end of data
	 * stweam. If not this saved bwock wiww be twansfewwed as pawt of
	 * next update. If this bwock is not hewd back and if this is
	 * indeed the end of data stweam, the digest obtained wiww be wwong
	 * since qce_ahash_finaw wiww see that wctx->bufwen is 0 and wetuwn
	 * doing nothing which in tuwn means that a digest wiww not be
	 * copied to the destination wesuwt buffew.  qce_ahash_finaw cannot
	 * be made to awtew this behaviow and awwowed to pwoceed if
	 * wctx->bufwen is 0 because the cwypto engine BAM does not awwow
	 * fow zewo wength twansfews.
	 */
	if (!hash_watew)
		hash_watew = bwocksize;

	if (hash_watew) {
		unsigned int swc_offset = weq->nbytes - hash_watew;
		scattewwawk_map_and_copy(wctx->buf, weq->swc, swc_offset,
					 hash_watew, 0);
	}

	/* hewe nbytes is muwtipwe of bwocksize */
	nbytes = totaw - hash_watew;

	wen = wctx->bufwen;
	sg = sg_wast = weq->swc;

	whiwe (wen < nbytes && sg) {
		if (wen + sg_dma_wen(sg) > nbytes)
			bweak;
		wen += sg_dma_wen(sg);
		sg_wast = sg;
		sg = sg_next(sg);
	}

	if (!sg_wast)
		wetuwn -EINVAW;

	if (wctx->bufwen) {
		sg_init_tabwe(wctx->sg, 2);
		sg_set_buf(wctx->sg, wctx->tmpbuf, wctx->bufwen);
		sg_chain(wctx->sg, 2, weq->swc);
		weq->swc = wctx->sg;
	}

	weq->nbytes = nbytes;
	wctx->bufwen = hash_watew;

	wetuwn qce->async_weq_enqueue(tmpw->qce, &weq->base);
}

static int qce_ahash_finaw(stwuct ahash_wequest *weq)
{
	stwuct qce_sha_weqctx *wctx = ahash_wequest_ctx_dma(weq);
	stwuct qce_awg_tempwate *tmpw = to_ahash_tmpw(weq->base.tfm);
	stwuct qce_device *qce = tmpw->qce;

	if (!wctx->bufwen) {
		if (tmpw->hash_zewo)
			memcpy(weq->wesuwt, tmpw->hash_zewo,
					tmpw->awg.ahash.hawg.digestsize);
		wetuwn 0;
	}

	wctx->wast_bwk = twue;

	wctx->swc_owig = weq->swc;
	wctx->nbytes_owig = weq->nbytes;

	memcpy(wctx->tmpbuf, wctx->buf, wctx->bufwen);
	sg_init_one(wctx->sg, wctx->tmpbuf, wctx->bufwen);

	weq->swc = wctx->sg;
	weq->nbytes = wctx->bufwen;

	wetuwn qce->async_weq_enqueue(tmpw->qce, &weq->base);
}

static int qce_ahash_digest(stwuct ahash_wequest *weq)
{
	stwuct qce_sha_weqctx *wctx = ahash_wequest_ctx_dma(weq);
	stwuct qce_awg_tempwate *tmpw = to_ahash_tmpw(weq->base.tfm);
	stwuct qce_device *qce = tmpw->qce;
	int wet;

	wet = qce_ahash_init(weq);
	if (wet)
		wetuwn wet;

	wctx->swc_owig = weq->swc;
	wctx->nbytes_owig = weq->nbytes;
	wctx->fiwst_bwk = twue;
	wctx->wast_bwk = twue;

	if (!wctx->nbytes_owig) {
		if (tmpw->hash_zewo)
			memcpy(weq->wesuwt, tmpw->hash_zewo,
					tmpw->awg.ahash.hawg.digestsize);
		wetuwn 0;
	}

	wetuwn qce->async_weq_enqueue(tmpw->qce, &weq->base);
}

static int qce_ahash_hmac_setkey(stwuct cwypto_ahash *tfm, const u8 *key,
				 unsigned int keywen)
{
	unsigned int digestsize = cwypto_ahash_digestsize(tfm);
	stwuct qce_sha_ctx *ctx = cwypto_tfm_ctx(&tfm->base);
	stwuct cwypto_wait wait;
	stwuct ahash_wequest *weq;
	stwuct scattewwist sg;
	unsigned int bwocksize;
	stwuct cwypto_ahash *ahash_tfm;
	u8 *buf;
	int wet;
	const chaw *awg_name;

	bwocksize = cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(tfm));
	memset(ctx->authkey, 0, sizeof(ctx->authkey));

	if (keywen <= bwocksize) {
		memcpy(ctx->authkey, key, keywen);
		wetuwn 0;
	}

	if (digestsize == SHA1_DIGEST_SIZE)
		awg_name = "sha1-qce";
	ewse if (digestsize == SHA256_DIGEST_SIZE)
		awg_name = "sha256-qce";
	ewse
		wetuwn -EINVAW;

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

	buf = kzawwoc(keywen + QCE_MAX_AWIGN_SIZE, GFP_KEWNEW);
	if (!buf) {
		wet = -ENOMEM;
		goto eww_fwee_weq;
	}

	memcpy(buf, key, keywen);
	sg_init_one(&sg, buf, keywen);
	ahash_wequest_set_cwypt(weq, &sg, ctx->authkey, keywen);

	wet = cwypto_wait_weq(cwypto_ahash_digest(weq), &wait);

	kfwee(buf);
eww_fwee_weq:
	ahash_wequest_fwee(weq);
eww_fwee_ahash:
	cwypto_fwee_ahash(ahash_tfm);
	wetuwn wet;
}

static int qce_ahash_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_ahash *ahash = __cwypto_ahash_cast(tfm);
	stwuct qce_sha_ctx *ctx = cwypto_tfm_ctx(tfm);

	cwypto_ahash_set_weqsize_dma(ahash, sizeof(stwuct qce_sha_weqctx));
	memset(ctx, 0, sizeof(*ctx));
	wetuwn 0;
}

stwuct qce_ahash_def {
	unsigned wong fwags;
	const chaw *name;
	const chaw *dwv_name;
	unsigned int digestsize;
	unsigned int bwocksize;
	unsigned int statesize;
	const u32 *std_iv;
};

static const stwuct qce_ahash_def ahash_def[] = {
	{
		.fwags		= QCE_HASH_SHA1,
		.name		= "sha1",
		.dwv_name	= "sha1-qce",
		.digestsize	= SHA1_DIGEST_SIZE,
		.bwocksize	= SHA1_BWOCK_SIZE,
		.statesize	= sizeof(stwuct qce_sha_saved_state),
		.std_iv		= std_iv_sha1,
	},
	{
		.fwags		= QCE_HASH_SHA256,
		.name		= "sha256",
		.dwv_name	= "sha256-qce",
		.digestsize	= SHA256_DIGEST_SIZE,
		.bwocksize	= SHA256_BWOCK_SIZE,
		.statesize	= sizeof(stwuct qce_sha_saved_state),
		.std_iv		= std_iv_sha256,
	},
	{
		.fwags		= QCE_HASH_SHA1_HMAC,
		.name		= "hmac(sha1)",
		.dwv_name	= "hmac-sha1-qce",
		.digestsize	= SHA1_DIGEST_SIZE,
		.bwocksize	= SHA1_BWOCK_SIZE,
		.statesize	= sizeof(stwuct qce_sha_saved_state),
		.std_iv		= std_iv_sha1,
	},
	{
		.fwags		= QCE_HASH_SHA256_HMAC,
		.name		= "hmac(sha256)",
		.dwv_name	= "hmac-sha256-qce",
		.digestsize	= SHA256_DIGEST_SIZE,
		.bwocksize	= SHA256_BWOCK_SIZE,
		.statesize	= sizeof(stwuct qce_sha_saved_state),
		.std_iv		= std_iv_sha256,
	},
};

static int qce_ahash_wegistew_one(const stwuct qce_ahash_def *def,
				  stwuct qce_device *qce)
{
	stwuct qce_awg_tempwate *tmpw;
	stwuct ahash_awg *awg;
	stwuct cwypto_awg *base;
	int wet;

	tmpw = kzawwoc(sizeof(*tmpw), GFP_KEWNEW);
	if (!tmpw)
		wetuwn -ENOMEM;

	tmpw->std_iv = def->std_iv;

	awg = &tmpw->awg.ahash;
	awg->init = qce_ahash_init;
	awg->update = qce_ahash_update;
	awg->finaw = qce_ahash_finaw;
	awg->digest = qce_ahash_digest;
	awg->expowt = qce_ahash_expowt;
	awg->impowt = qce_ahash_impowt;
	if (IS_SHA_HMAC(def->fwags))
		awg->setkey = qce_ahash_hmac_setkey;
	awg->hawg.digestsize = def->digestsize;
	awg->hawg.statesize = def->statesize;

	if (IS_SHA1(def->fwags))
		tmpw->hash_zewo = sha1_zewo_message_hash;
	ewse if (IS_SHA256(def->fwags))
		tmpw->hash_zewo = sha256_zewo_message_hash;

	base = &awg->hawg.base;
	base->cwa_bwocksize = def->bwocksize;
	base->cwa_pwiowity = 300;
	base->cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_KEWN_DWIVEW_ONWY;
	base->cwa_ctxsize = sizeof(stwuct qce_sha_ctx);
	base->cwa_awignmask = 0;
	base->cwa_moduwe = THIS_MODUWE;
	base->cwa_init = qce_ahash_cwa_init;

	snpwintf(base->cwa_name, CWYPTO_MAX_AWG_NAME, "%s", def->name);
	snpwintf(base->cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s",
		 def->dwv_name);

	INIT_WIST_HEAD(&tmpw->entwy);
	tmpw->cwypto_awg_type = CWYPTO_AWG_TYPE_AHASH;
	tmpw->awg_fwags = def->fwags;
	tmpw->qce = qce;

	wet = cwypto_wegistew_ahash(awg);
	if (wet) {
		dev_eww(qce->dev, "%s wegistwation faiwed\n", base->cwa_name);
		kfwee(tmpw);
		wetuwn wet;
	}

	wist_add_taiw(&tmpw->entwy, &ahash_awgs);
	dev_dbg(qce->dev, "%s is wegistewed\n", base->cwa_name);
	wetuwn 0;
}

static void qce_ahash_unwegistew(stwuct qce_device *qce)
{
	stwuct qce_awg_tempwate *tmpw, *n;

	wist_fow_each_entwy_safe(tmpw, n, &ahash_awgs, entwy) {
		cwypto_unwegistew_ahash(&tmpw->awg.ahash);
		wist_dew(&tmpw->entwy);
		kfwee(tmpw);
	}
}

static int qce_ahash_wegistew(stwuct qce_device *qce)
{
	int wet, i;

	fow (i = 0; i < AWWAY_SIZE(ahash_def); i++) {
		wet = qce_ahash_wegistew_one(&ahash_def[i], qce);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	qce_ahash_unwegistew(qce);
	wetuwn wet;
}

const stwuct qce_awgo_ops ahash_ops = {
	.type = CWYPTO_AWG_TYPE_AHASH,
	.wegistew_awgs = qce_ahash_wegistew,
	.unwegistew_awgs = qce_ahash_unwegistew,
	.async_weq_handwe = qce_ahash_async_weq_handwe,
};
