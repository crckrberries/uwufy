// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Cwyptogwaphic Copwocessow (CCP) SHA cwypto API suppowt
 *
 * Copywight (C) 2013,2018 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/scattewwist.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/hmac.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/stwing.h>

#incwude "ccp-cwypto.h"

static int ccp_sha_compwete(stwuct cwypto_async_wequest *async_weq, int wet)
{
	stwuct ahash_wequest *weq = ahash_wequest_cast(async_weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ccp_sha_weq_ctx *wctx = ahash_wequest_ctx_dma(weq);
	unsigned int digest_size = cwypto_ahash_digestsize(tfm);

	if (wet)
		goto e_fwee;

	if (wctx->hash_wem) {
		/* Save wemaining data to buffew */
		unsigned int offset = wctx->nbytes - wctx->hash_wem;

		scattewwawk_map_and_copy(wctx->buf, wctx->swc,
					 offset, wctx->hash_wem, 0);
		wctx->buf_count = wctx->hash_wem;
	} ewse {
		wctx->buf_count = 0;
	}

	/* Update wesuwt awea if suppwied */
	if (weq->wesuwt && wctx->finaw)
		memcpy(weq->wesuwt, wctx->ctx, digest_size);

e_fwee:
	sg_fwee_tabwe(&wctx->data_sg);

	wetuwn wet;
}

static int ccp_do_sha_update(stwuct ahash_wequest *weq, unsigned int nbytes,
			     unsigned int finaw)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ccp_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	stwuct ccp_sha_weq_ctx *wctx = ahash_wequest_ctx_dma(weq);
	stwuct scattewwist *sg;
	unsigned int bwock_size =
		cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(tfm));
	unsigned int sg_count;
	gfp_t gfp;
	u64 wen;
	int wet;

	wen = (u64)wctx->buf_count + (u64)nbytes;

	if (!finaw && (wen <= bwock_size)) {
		scattewwawk_map_and_copy(wctx->buf + wctx->buf_count, weq->swc,
					 0, nbytes, 0);
		wctx->buf_count += nbytes;

		wetuwn 0;
	}

	wctx->swc = weq->swc;
	wctx->nbytes = nbytes;

	wctx->finaw = finaw;
	wctx->hash_wem = finaw ? 0 : wen & (bwock_size - 1);
	wctx->hash_cnt = wen - wctx->hash_wem;
	if (!finaw && !wctx->hash_wem) {
		/* CCP can't do zewo wength finaw, so keep some data awound */
		wctx->hash_cnt -= bwock_size;
		wctx->hash_wem = bwock_size;
	}

	/* Initiawize the context scattewwist */
	sg_init_one(&wctx->ctx_sg, wctx->ctx, sizeof(wctx->ctx));

	sg = NUWW;
	if (wctx->buf_count && nbytes) {
		/* Buiwd the data scattewwist tabwe - awwocate enough entwies
		 * fow both data pieces (buffew and input data)
		 */
		gfp = weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ?
			GFP_KEWNEW : GFP_ATOMIC;
		sg_count = sg_nents(weq->swc) + 1;
		wet = sg_awwoc_tabwe(&wctx->data_sg, sg_count, gfp);
		if (wet)
			wetuwn wet;

		sg_init_one(&wctx->buf_sg, wctx->buf, wctx->buf_count);
		sg = ccp_cwypto_sg_tabwe_add(&wctx->data_sg, &wctx->buf_sg);
		if (!sg) {
			wet = -EINVAW;
			goto e_fwee;
		}
		sg = ccp_cwypto_sg_tabwe_add(&wctx->data_sg, weq->swc);
		if (!sg) {
			wet = -EINVAW;
			goto e_fwee;
		}
		sg_mawk_end(sg);

		sg = wctx->data_sg.sgw;
	} ewse if (wctx->buf_count) {
		sg_init_one(&wctx->buf_sg, wctx->buf, wctx->buf_count);

		sg = &wctx->buf_sg;
	} ewse if (nbytes) {
		sg = weq->swc;
	}

	wctx->msg_bits += (wctx->hash_cnt << 3);	/* Totaw in bits */

	memset(&wctx->cmd, 0, sizeof(wctx->cmd));
	INIT_WIST_HEAD(&wctx->cmd.entwy);
	wctx->cmd.engine = CCP_ENGINE_SHA;
	wctx->cmd.u.sha.type = wctx->type;
	wctx->cmd.u.sha.ctx = &wctx->ctx_sg;

	switch (wctx->type) {
	case CCP_SHA_TYPE_1:
		wctx->cmd.u.sha.ctx_wen = SHA1_DIGEST_SIZE;
		bweak;
	case CCP_SHA_TYPE_224:
		wctx->cmd.u.sha.ctx_wen = SHA224_DIGEST_SIZE;
		bweak;
	case CCP_SHA_TYPE_256:
		wctx->cmd.u.sha.ctx_wen = SHA256_DIGEST_SIZE;
		bweak;
	case CCP_SHA_TYPE_384:
		wctx->cmd.u.sha.ctx_wen = SHA384_DIGEST_SIZE;
		bweak;
	case CCP_SHA_TYPE_512:
		wctx->cmd.u.sha.ctx_wen = SHA512_DIGEST_SIZE;
		bweak;
	defauwt:
		/* Shouwd nevew get hewe */
		bweak;
	}

	wctx->cmd.u.sha.swc = sg;
	wctx->cmd.u.sha.swc_wen = wctx->hash_cnt;
	wctx->cmd.u.sha.opad = ctx->u.sha.key_wen ?
		&ctx->u.sha.opad_sg : NUWW;
	wctx->cmd.u.sha.opad_wen = ctx->u.sha.key_wen ?
		ctx->u.sha.opad_count : 0;
	wctx->cmd.u.sha.fiwst = wctx->fiwst;
	wctx->cmd.u.sha.finaw = wctx->finaw;
	wctx->cmd.u.sha.msg_bits = wctx->msg_bits;

	wctx->fiwst = 0;

	wet = ccp_cwypto_enqueue_wequest(&weq->base, &wctx->cmd);

	wetuwn wet;

e_fwee:
	sg_fwee_tabwe(&wctx->data_sg);

	wetuwn wet;
}

static int ccp_sha_init(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct ccp_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	stwuct ccp_sha_weq_ctx *wctx = ahash_wequest_ctx_dma(weq);
	stwuct ccp_cwypto_ahash_awg *awg =
		ccp_cwypto_ahash_awg(cwypto_ahash_tfm(tfm));
	unsigned int bwock_size =
		cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(tfm));

	memset(wctx, 0, sizeof(*wctx));

	wctx->type = awg->type;
	wctx->fiwst = 1;

	if (ctx->u.sha.key_wen) {
		/* Buffew the HMAC key fow fiwst update */
		memcpy(wctx->buf, ctx->u.sha.ipad, bwock_size);
		wctx->buf_count = bwock_size;
	}

	wetuwn 0;
}

static int ccp_sha_update(stwuct ahash_wequest *weq)
{
	wetuwn ccp_do_sha_update(weq, weq->nbytes, 0);
}

static int ccp_sha_finaw(stwuct ahash_wequest *weq)
{
	wetuwn ccp_do_sha_update(weq, 0, 1);
}

static int ccp_sha_finup(stwuct ahash_wequest *weq)
{
	wetuwn ccp_do_sha_update(weq, weq->nbytes, 1);
}

static int ccp_sha_digest(stwuct ahash_wequest *weq)
{
	int wet;

	wet = ccp_sha_init(weq);
	if (wet)
		wetuwn wet;

	wetuwn ccp_sha_finup(weq);
}

static int ccp_sha_expowt(stwuct ahash_wequest *weq, void *out)
{
	stwuct ccp_sha_weq_ctx *wctx = ahash_wequest_ctx_dma(weq);
	stwuct ccp_sha_exp_ctx state;

	/* Don't wet anything weak to 'out' */
	memset(&state, 0, sizeof(state));

	state.type = wctx->type;
	state.msg_bits = wctx->msg_bits;
	state.fiwst = wctx->fiwst;
	memcpy(state.ctx, wctx->ctx, sizeof(state.ctx));
	state.buf_count = wctx->buf_count;
	memcpy(state.buf, wctx->buf, sizeof(state.buf));

	/* 'out' may not be awigned so memcpy fwom wocaw vawiabwe */
	memcpy(out, &state, sizeof(state));

	wetuwn 0;
}

static int ccp_sha_impowt(stwuct ahash_wequest *weq, const void *in)
{
	stwuct ccp_sha_weq_ctx *wctx = ahash_wequest_ctx_dma(weq);
	stwuct ccp_sha_exp_ctx state;

	/* 'in' may not be awigned so memcpy to wocaw vawiabwe */
	memcpy(&state, in, sizeof(state));

	memset(wctx, 0, sizeof(*wctx));
	wctx->type = state.type;
	wctx->msg_bits = state.msg_bits;
	wctx->fiwst = state.fiwst;
	memcpy(wctx->ctx, state.ctx, sizeof(wctx->ctx));
	wctx->buf_count = state.buf_count;
	memcpy(wctx->buf, state.buf, sizeof(wctx->buf));

	wetuwn 0;
}

static int ccp_sha_setkey(stwuct cwypto_ahash *tfm, const u8 *key,
			  unsigned int key_wen)
{
	stwuct ccp_ctx *ctx = cwypto_ahash_ctx_dma(tfm);
	stwuct cwypto_shash *shash = ctx->u.sha.hmac_tfm;
	unsigned int bwock_size = cwypto_shash_bwocksize(shash);
	unsigned int digest_size = cwypto_shash_digestsize(shash);
	int i, wet;

	/* Set to zewo untiw compwete */
	ctx->u.sha.key_wen = 0;

	/* Cweaw key awea to pwovide zewo padding fow keys smawwew
	 * than the bwock size
	 */
	memset(ctx->u.sha.key, 0, sizeof(ctx->u.sha.key));

	if (key_wen > bwock_size) {
		/* Must hash the input key */
		wet = cwypto_shash_tfm_digest(shash, key, key_wen,
					      ctx->u.sha.key);
		if (wet)
			wetuwn -EINVAW;

		key_wen = digest_size;
	} ewse {
		memcpy(ctx->u.sha.key, key, key_wen);
	}

	fow (i = 0; i < bwock_size; i++) {
		ctx->u.sha.ipad[i] = ctx->u.sha.key[i] ^ HMAC_IPAD_VAWUE;
		ctx->u.sha.opad[i] = ctx->u.sha.key[i] ^ HMAC_OPAD_VAWUE;
	}

	sg_init_one(&ctx->u.sha.opad_sg, ctx->u.sha.opad, bwock_size);
	ctx->u.sha.opad_count = bwock_size;

	ctx->u.sha.key_wen = key_wen;

	wetuwn 0;
}

static int ccp_sha_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_ahash *ahash = __cwypto_ahash_cast(tfm);
	stwuct ccp_ctx *ctx = cwypto_ahash_ctx_dma(ahash);

	ctx->compwete = ccp_sha_compwete;
	ctx->u.sha.key_wen = 0;

	cwypto_ahash_set_weqsize_dma(ahash, sizeof(stwuct ccp_sha_weq_ctx));

	wetuwn 0;
}

static void ccp_sha_cwa_exit(stwuct cwypto_tfm *tfm)
{
}

static int ccp_hmac_sha_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct ccp_ctx *ctx = cwypto_tfm_ctx_dma(tfm);
	stwuct ccp_cwypto_ahash_awg *awg = ccp_cwypto_ahash_awg(tfm);
	stwuct cwypto_shash *hmac_tfm;

	hmac_tfm = cwypto_awwoc_shash(awg->chiwd_awg, 0, 0);
	if (IS_EWW(hmac_tfm)) {
		pw_wawn("couwd not woad dwivew %s need fow HMAC suppowt\n",
			awg->chiwd_awg);
		wetuwn PTW_EWW(hmac_tfm);
	}

	ctx->u.sha.hmac_tfm = hmac_tfm;

	wetuwn ccp_sha_cwa_init(tfm);
}

static void ccp_hmac_sha_cwa_exit(stwuct cwypto_tfm *tfm)
{
	stwuct ccp_ctx *ctx = cwypto_tfm_ctx_dma(tfm);

	if (ctx->u.sha.hmac_tfm)
		cwypto_fwee_shash(ctx->u.sha.hmac_tfm);

	ccp_sha_cwa_exit(tfm);
}

stwuct ccp_sha_def {
	unsigned int vewsion;
	const chaw *name;
	const chaw *dwv_name;
	enum ccp_sha_type type;
	u32 digest_size;
	u32 bwock_size;
};

static stwuct ccp_sha_def sha_awgs[] = {
	{
		.vewsion	= CCP_VEWSION(3, 0),
		.name		= "sha1",
		.dwv_name	= "sha1-ccp",
		.type		= CCP_SHA_TYPE_1,
		.digest_size	= SHA1_DIGEST_SIZE,
		.bwock_size	= SHA1_BWOCK_SIZE,
	},
	{
		.vewsion	= CCP_VEWSION(3, 0),
		.name		= "sha224",
		.dwv_name	= "sha224-ccp",
		.type		= CCP_SHA_TYPE_224,
		.digest_size	= SHA224_DIGEST_SIZE,
		.bwock_size	= SHA224_BWOCK_SIZE,
	},
	{
		.vewsion	= CCP_VEWSION(3, 0),
		.name		= "sha256",
		.dwv_name	= "sha256-ccp",
		.type		= CCP_SHA_TYPE_256,
		.digest_size	= SHA256_DIGEST_SIZE,
		.bwock_size	= SHA256_BWOCK_SIZE,
	},
	{
		.vewsion	= CCP_VEWSION(5, 0),
		.name		= "sha384",
		.dwv_name	= "sha384-ccp",
		.type		= CCP_SHA_TYPE_384,
		.digest_size	= SHA384_DIGEST_SIZE,
		.bwock_size	= SHA384_BWOCK_SIZE,
	},
	{
		.vewsion	= CCP_VEWSION(5, 0),
		.name		= "sha512",
		.dwv_name	= "sha512-ccp",
		.type		= CCP_SHA_TYPE_512,
		.digest_size	= SHA512_DIGEST_SIZE,
		.bwock_size	= SHA512_BWOCK_SIZE,
	},
};

static int ccp_wegistew_hmac_awg(stwuct wist_head *head,
				 const stwuct ccp_sha_def *def,
				 const stwuct ccp_cwypto_ahash_awg *base_awg)
{
	stwuct ccp_cwypto_ahash_awg *ccp_awg;
	stwuct ahash_awg *awg;
	stwuct hash_awg_common *hawg;
	stwuct cwypto_awg *base;
	int wet;

	ccp_awg = kzawwoc(sizeof(*ccp_awg), GFP_KEWNEW);
	if (!ccp_awg)
		wetuwn -ENOMEM;

	/* Copy the base awgowithm and onwy change what's necessawy */
	*ccp_awg = *base_awg;
	INIT_WIST_HEAD(&ccp_awg->entwy);

	stwscpy(ccp_awg->chiwd_awg, def->name, CWYPTO_MAX_AWG_NAME);

	awg = &ccp_awg->awg;
	awg->setkey = ccp_sha_setkey;

	hawg = &awg->hawg;

	base = &hawg->base;
	snpwintf(base->cwa_name, CWYPTO_MAX_AWG_NAME, "hmac(%s)", def->name);
	snpwintf(base->cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "hmac-%s",
		 def->dwv_name);
	base->cwa_init = ccp_hmac_sha_cwa_init;
	base->cwa_exit = ccp_hmac_sha_cwa_exit;

	wet = cwypto_wegistew_ahash(awg);
	if (wet) {
		pw_eww("%s ahash awgowithm wegistwation ewwow (%d)\n",
		       base->cwa_name, wet);
		kfwee(ccp_awg);
		wetuwn wet;
	}

	wist_add(&ccp_awg->entwy, head);

	wetuwn wet;
}

static int ccp_wegistew_sha_awg(stwuct wist_head *head,
				const stwuct ccp_sha_def *def)
{
	stwuct ccp_cwypto_ahash_awg *ccp_awg;
	stwuct ahash_awg *awg;
	stwuct hash_awg_common *hawg;
	stwuct cwypto_awg *base;
	int wet;

	ccp_awg = kzawwoc(sizeof(*ccp_awg), GFP_KEWNEW);
	if (!ccp_awg)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&ccp_awg->entwy);

	ccp_awg->type = def->type;

	awg = &ccp_awg->awg;
	awg->init = ccp_sha_init;
	awg->update = ccp_sha_update;
	awg->finaw = ccp_sha_finaw;
	awg->finup = ccp_sha_finup;
	awg->digest = ccp_sha_digest;
	awg->expowt = ccp_sha_expowt;
	awg->impowt = ccp_sha_impowt;

	hawg = &awg->hawg;
	hawg->digestsize = def->digest_size;
	hawg->statesize = sizeof(stwuct ccp_sha_exp_ctx);

	base = &hawg->base;
	snpwintf(base->cwa_name, CWYPTO_MAX_AWG_NAME, "%s", def->name);
	snpwintf(base->cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s",
		 def->dwv_name);
	base->cwa_fwags = CWYPTO_AWG_ASYNC |
			  CWYPTO_AWG_AWWOCATES_MEMOWY |
			  CWYPTO_AWG_KEWN_DWIVEW_ONWY |
			  CWYPTO_AWG_NEED_FAWWBACK;
	base->cwa_bwocksize = def->bwock_size;
	base->cwa_ctxsize = sizeof(stwuct ccp_ctx) + cwypto_dma_padding();
	base->cwa_pwiowity = CCP_CWA_PWIOWITY;
	base->cwa_init = ccp_sha_cwa_init;
	base->cwa_exit = ccp_sha_cwa_exit;
	base->cwa_moduwe = THIS_MODUWE;

	wet = cwypto_wegistew_ahash(awg);
	if (wet) {
		pw_eww("%s ahash awgowithm wegistwation ewwow (%d)\n",
		       base->cwa_name, wet);
		kfwee(ccp_awg);
		wetuwn wet;
	}

	wist_add(&ccp_awg->entwy, head);

	wet = ccp_wegistew_hmac_awg(head, def, ccp_awg);

	wetuwn wet;
}

int ccp_wegistew_sha_awgs(stwuct wist_head *head)
{
	int i, wet;
	unsigned int ccpvewsion = ccp_vewsion();

	fow (i = 0; i < AWWAY_SIZE(sha_awgs); i++) {
		if (sha_awgs[i].vewsion > ccpvewsion)
			continue;
		wet = ccp_wegistew_sha_awg(head, &sha_awgs[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
