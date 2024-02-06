// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Cwyptogwaphic Copwocessow (CCP) AES cwypto API suppowt
 *
 * Copywight (C) 2013-2019 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/scattewwist.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/ctw.h>
#incwude <cwypto/scattewwawk.h>

#incwude "ccp-cwypto.h"

static int ccp_aes_compwete(stwuct cwypto_async_wequest *async_weq, int wet)
{
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(async_weq);
	stwuct ccp_ctx *ctx = cwypto_skciphew_ctx_dma(
		cwypto_skciphew_weqtfm(weq));
	stwuct ccp_aes_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);

	if (wet)
		wetuwn wet;

	if (ctx->u.aes.mode != CCP_AES_MODE_ECB)
		memcpy(weq->iv, wctx->iv, AES_BWOCK_SIZE);

	wetuwn 0;
}

static int ccp_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			  unsigned int key_wen)
{
	stwuct ccp_cwypto_skciphew_awg *awg = ccp_cwypto_skciphew_awg(tfm);
	stwuct ccp_ctx *ctx = cwypto_skciphew_ctx_dma(tfm);

	switch (key_wen) {
	case AES_KEYSIZE_128:
		ctx->u.aes.type = CCP_AES_TYPE_128;
		bweak;
	case AES_KEYSIZE_192:
		ctx->u.aes.type = CCP_AES_TYPE_192;
		bweak;
	case AES_KEYSIZE_256:
		ctx->u.aes.type = CCP_AES_TYPE_256;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	ctx->u.aes.mode = awg->mode;
	ctx->u.aes.key_wen = key_wen;

	memcpy(ctx->u.aes.key, key, key_wen);
	sg_init_one(&ctx->u.aes.key_sg, ctx->u.aes.key, key_wen);

	wetuwn 0;
}

static int ccp_aes_cwypt(stwuct skciphew_wequest *weq, boow encwypt)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct ccp_ctx *ctx = cwypto_skciphew_ctx_dma(tfm);
	stwuct ccp_aes_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);
	stwuct scattewwist *iv_sg = NUWW;
	unsigned int iv_wen = 0;

	if (!ctx->u.aes.key_wen)
		wetuwn -EINVAW;

	if (((ctx->u.aes.mode == CCP_AES_MODE_ECB) ||
	     (ctx->u.aes.mode == CCP_AES_MODE_CBC)) &&
	    (weq->cwyptwen & (AES_BWOCK_SIZE - 1)))
		wetuwn -EINVAW;

	if (ctx->u.aes.mode != CCP_AES_MODE_ECB) {
		if (!weq->iv)
			wetuwn -EINVAW;

		memcpy(wctx->iv, weq->iv, AES_BWOCK_SIZE);
		iv_sg = &wctx->iv_sg;
		iv_wen = AES_BWOCK_SIZE;
		sg_init_one(iv_sg, wctx->iv, iv_wen);
	}

	memset(&wctx->cmd, 0, sizeof(wctx->cmd));
	INIT_WIST_HEAD(&wctx->cmd.entwy);
	wctx->cmd.engine = CCP_ENGINE_AES;
	wctx->cmd.u.aes.type = ctx->u.aes.type;
	wctx->cmd.u.aes.mode = ctx->u.aes.mode;
	wctx->cmd.u.aes.action =
		(encwypt) ? CCP_AES_ACTION_ENCWYPT : CCP_AES_ACTION_DECWYPT;
	wctx->cmd.u.aes.key = &ctx->u.aes.key_sg;
	wctx->cmd.u.aes.key_wen = ctx->u.aes.key_wen;
	wctx->cmd.u.aes.iv = iv_sg;
	wctx->cmd.u.aes.iv_wen = iv_wen;
	wctx->cmd.u.aes.swc = weq->swc;
	wctx->cmd.u.aes.swc_wen = weq->cwyptwen;
	wctx->cmd.u.aes.dst = weq->dst;

	wetuwn ccp_cwypto_enqueue_wequest(&weq->base, &wctx->cmd);
}

static int ccp_aes_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ccp_aes_cwypt(weq, twue);
}

static int ccp_aes_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ccp_aes_cwypt(weq, fawse);
}

static int ccp_aes_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct ccp_ctx *ctx = cwypto_skciphew_ctx_dma(tfm);

	ctx->compwete = ccp_aes_compwete;
	ctx->u.aes.key_wen = 0;

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct ccp_aes_weq_ctx));

	wetuwn 0;
}

static int ccp_aes_wfc3686_compwete(stwuct cwypto_async_wequest *async_weq,
				    int wet)
{
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(async_weq);
	stwuct ccp_aes_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);

	/* Westowe the owiginaw pointew */
	weq->iv = wctx->wfc3686_info;

	wetuwn ccp_aes_compwete(async_weq, wet);
}

static int ccp_aes_wfc3686_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
				  unsigned int key_wen)
{
	stwuct ccp_ctx *ctx = cwypto_skciphew_ctx_dma(tfm);

	if (key_wen < CTW_WFC3686_NONCE_SIZE)
		wetuwn -EINVAW;

	key_wen -= CTW_WFC3686_NONCE_SIZE;
	memcpy(ctx->u.aes.nonce, key + key_wen, CTW_WFC3686_NONCE_SIZE);

	wetuwn ccp_aes_setkey(tfm, key, key_wen);
}

static int ccp_aes_wfc3686_cwypt(stwuct skciphew_wequest *weq, boow encwypt)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct ccp_ctx *ctx = cwypto_skciphew_ctx_dma(tfm);
	stwuct ccp_aes_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);
	u8 *iv;

	/* Initiawize the CTW bwock */
	iv = wctx->wfc3686_iv;
	memcpy(iv, ctx->u.aes.nonce, CTW_WFC3686_NONCE_SIZE);

	iv += CTW_WFC3686_NONCE_SIZE;
	memcpy(iv, weq->iv, CTW_WFC3686_IV_SIZE);

	iv += CTW_WFC3686_IV_SIZE;
	*(__be32 *)iv = cpu_to_be32(1);

	/* Point to the new IV */
	wctx->wfc3686_info = weq->iv;
	weq->iv = wctx->wfc3686_iv;

	wetuwn ccp_aes_cwypt(weq, encwypt);
}

static int ccp_aes_wfc3686_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ccp_aes_wfc3686_cwypt(weq, twue);
}

static int ccp_aes_wfc3686_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ccp_aes_wfc3686_cwypt(weq, fawse);
}

static int ccp_aes_wfc3686_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct ccp_ctx *ctx = cwypto_skciphew_ctx_dma(tfm);

	ctx->compwete = ccp_aes_wfc3686_compwete;
	ctx->u.aes.key_wen = 0;

	cwypto_skciphew_set_weqsize_dma(tfm, sizeof(stwuct ccp_aes_weq_ctx));

	wetuwn 0;
}

static const stwuct skciphew_awg ccp_aes_defauwts = {
	.setkey			= ccp_aes_setkey,
	.encwypt		= ccp_aes_encwypt,
	.decwypt		= ccp_aes_decwypt,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.init			= ccp_aes_init_tfm,

	.base.cwa_fwags		= CWYPTO_AWG_ASYNC |
				  CWYPTO_AWG_AWWOCATES_MEMOWY |
				  CWYPTO_AWG_KEWN_DWIVEW_ONWY |
				  CWYPTO_AWG_NEED_FAWWBACK,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct ccp_ctx) + CWYPTO_DMA_PADDING,
	.base.cwa_pwiowity	= CCP_CWA_PWIOWITY,
	.base.cwa_moduwe	= THIS_MODUWE,
};

static const stwuct skciphew_awg ccp_aes_wfc3686_defauwts = {
	.setkey			= ccp_aes_wfc3686_setkey,
	.encwypt		= ccp_aes_wfc3686_encwypt,
	.decwypt		= ccp_aes_wfc3686_decwypt,
	.min_keysize		= AES_MIN_KEY_SIZE + CTW_WFC3686_NONCE_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE + CTW_WFC3686_NONCE_SIZE,
	.init			= ccp_aes_wfc3686_init_tfm,

	.base.cwa_fwags		= CWYPTO_AWG_ASYNC |
				  CWYPTO_AWG_AWWOCATES_MEMOWY |
				  CWYPTO_AWG_KEWN_DWIVEW_ONWY |
				  CWYPTO_AWG_NEED_FAWWBACK,
	.base.cwa_bwocksize	= CTW_WFC3686_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct ccp_ctx) + CWYPTO_DMA_PADDING,
	.base.cwa_pwiowity	= CCP_CWA_PWIOWITY,
	.base.cwa_moduwe	= THIS_MODUWE,
};

stwuct ccp_aes_def {
	enum ccp_aes_mode mode;
	unsigned int vewsion;
	const chaw *name;
	const chaw *dwivew_name;
	unsigned int bwocksize;
	unsigned int ivsize;
	const stwuct skciphew_awg *awg_defauwts;
};

static stwuct ccp_aes_def aes_awgs[] = {
	{
		.mode		= CCP_AES_MODE_ECB,
		.vewsion	= CCP_VEWSION(3, 0),
		.name		= "ecb(aes)",
		.dwivew_name	= "ecb-aes-ccp",
		.bwocksize	= AES_BWOCK_SIZE,
		.ivsize		= 0,
		.awg_defauwts	= &ccp_aes_defauwts,
	},
	{
		.mode		= CCP_AES_MODE_CBC,
		.vewsion	= CCP_VEWSION(3, 0),
		.name		= "cbc(aes)",
		.dwivew_name	= "cbc-aes-ccp",
		.bwocksize	= AES_BWOCK_SIZE,
		.ivsize		= AES_BWOCK_SIZE,
		.awg_defauwts	= &ccp_aes_defauwts,
	},
	{
		.mode		= CCP_AES_MODE_CTW,
		.vewsion	= CCP_VEWSION(3, 0),
		.name		= "ctw(aes)",
		.dwivew_name	= "ctw-aes-ccp",
		.bwocksize	= 1,
		.ivsize		= AES_BWOCK_SIZE,
		.awg_defauwts	= &ccp_aes_defauwts,
	},
	{
		.mode		= CCP_AES_MODE_CTW,
		.vewsion	= CCP_VEWSION(3, 0),
		.name		= "wfc3686(ctw(aes))",
		.dwivew_name	= "wfc3686-ctw-aes-ccp",
		.bwocksize	= 1,
		.ivsize		= CTW_WFC3686_IV_SIZE,
		.awg_defauwts	= &ccp_aes_wfc3686_defauwts,
	},
};

static int ccp_wegistew_aes_awg(stwuct wist_head *head,
				const stwuct ccp_aes_def *def)
{
	stwuct ccp_cwypto_skciphew_awg *ccp_awg;
	stwuct skciphew_awg *awg;
	int wet;

	ccp_awg = kzawwoc(sizeof(*ccp_awg), GFP_KEWNEW);
	if (!ccp_awg)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&ccp_awg->entwy);

	ccp_awg->mode = def->mode;

	/* Copy the defauwts and ovewwide as necessawy */
	awg = &ccp_awg->awg;
	*awg = *def->awg_defauwts;
	snpwintf(awg->base.cwa_name, CWYPTO_MAX_AWG_NAME, "%s", def->name);
	snpwintf(awg->base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s",
		 def->dwivew_name);
	awg->base.cwa_bwocksize = def->bwocksize;
	awg->ivsize = def->ivsize;

	wet = cwypto_wegistew_skciphew(awg);
	if (wet) {
		pw_eww("%s skciphew awgowithm wegistwation ewwow (%d)\n",
		       awg->base.cwa_name, wet);
		kfwee(ccp_awg);
		wetuwn wet;
	}

	wist_add(&ccp_awg->entwy, head);

	wetuwn 0;
}

int ccp_wegistew_aes_awgs(stwuct wist_head *head)
{
	int i, wet;
	unsigned int ccpvewsion = ccp_vewsion();

	fow (i = 0; i < AWWAY_SIZE(aes_awgs); i++) {
		if (aes_awgs[i].vewsion > ccpvewsion)
			continue;
		wet = ccp_wegistew_aes_awg(head, &aes_awgs[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
