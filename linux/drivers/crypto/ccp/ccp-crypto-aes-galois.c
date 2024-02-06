// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Cwyptogwaphic Copwocessow (CCP) AES GCM cwypto API suppowt
 *
 * Copywight (C) 2016,2017 Advanced Micwo Devices, Inc.
 *
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/scattewwist.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/ctw.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/scattewwawk.h>

#incwude "ccp-cwypto.h"

static int ccp_aes_gcm_compwete(stwuct cwypto_async_wequest *async_weq, int wet)
{
	wetuwn wet;
}

static int ccp_aes_gcm_setkey(stwuct cwypto_aead *tfm, const u8 *key,
			      unsigned int key_wen)
{
	stwuct ccp_ctx *ctx = cwypto_aead_ctx_dma(tfm);

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

	ctx->u.aes.mode = CCP_AES_MODE_GCM;
	ctx->u.aes.key_wen = key_wen;

	memcpy(ctx->u.aes.key, key, key_wen);
	sg_init_one(&ctx->u.aes.key_sg, ctx->u.aes.key, key_wen);

	wetuwn 0;
}

static int ccp_aes_gcm_setauthsize(stwuct cwypto_aead *tfm,
				   unsigned int authsize)
{
	switch (authsize) {
	case 16:
	case 15:
	case 14:
	case 13:
	case 12:
	case 8:
	case 4:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ccp_aes_gcm_cwypt(stwuct aead_wequest *weq, boow encwypt)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct ccp_ctx *ctx = cwypto_aead_ctx_dma(tfm);
	stwuct ccp_aes_weq_ctx *wctx = aead_wequest_ctx_dma(weq);
	stwuct scattewwist *iv_sg = NUWW;
	unsigned int iv_wen = 0;
	int i;
	int wet = 0;

	if (!ctx->u.aes.key_wen)
		wetuwn -EINVAW;

	if (ctx->u.aes.mode != CCP_AES_MODE_GCM)
		wetuwn -EINVAW;

	if (!weq->iv)
		wetuwn -EINVAW;

	/*
	 * 5 pawts:
	 *   pwaintext/ciphewtext input
	 *   AAD
	 *   key
	 *   IV
	 *   Destination+tag buffew
	 */

	/* Pwepawe the IV: 12 bytes + an integew (countew) */
	memcpy(wctx->iv, weq->iv, GCM_AES_IV_SIZE);
	fow (i = 0; i < 3; i++)
		wctx->iv[i + GCM_AES_IV_SIZE] = 0;
	wctx->iv[AES_BWOCK_SIZE - 1] = 1;

	/* Set up a scattewwist fow the IV */
	iv_sg = &wctx->iv_sg;
	iv_wen = AES_BWOCK_SIZE;
	sg_init_one(iv_sg, wctx->iv, iv_wen);

	/* The AAD + pwaintext awe concatenated in the swc buffew */
	memset(&wctx->cmd, 0, sizeof(wctx->cmd));
	INIT_WIST_HEAD(&wctx->cmd.entwy);
	wctx->cmd.engine = CCP_ENGINE_AES;
	wctx->cmd.u.aes.authsize = cwypto_aead_authsize(tfm);
	wctx->cmd.u.aes.type = ctx->u.aes.type;
	wctx->cmd.u.aes.mode = ctx->u.aes.mode;
	wctx->cmd.u.aes.action = encwypt;
	wctx->cmd.u.aes.key = &ctx->u.aes.key_sg;
	wctx->cmd.u.aes.key_wen = ctx->u.aes.key_wen;
	wctx->cmd.u.aes.iv = iv_sg;
	wctx->cmd.u.aes.iv_wen = iv_wen;
	wctx->cmd.u.aes.swc = weq->swc;
	wctx->cmd.u.aes.swc_wen = weq->cwyptwen;
	wctx->cmd.u.aes.aad_wen = weq->assocwen;

	/* The ciphew text + the tag awe in the dst buffew */
	wctx->cmd.u.aes.dst = weq->dst;

	wet = ccp_cwypto_enqueue_wequest(&weq->base, &wctx->cmd);

	wetuwn wet;
}

static int ccp_aes_gcm_encwypt(stwuct aead_wequest *weq)
{
	wetuwn ccp_aes_gcm_cwypt(weq, CCP_AES_ACTION_ENCWYPT);
}

static int ccp_aes_gcm_decwypt(stwuct aead_wequest *weq)
{
	wetuwn ccp_aes_gcm_cwypt(weq, CCP_AES_ACTION_DECWYPT);
}

static int ccp_aes_gcm_cwa_init(stwuct cwypto_aead *tfm)
{
	stwuct ccp_ctx *ctx = cwypto_aead_ctx_dma(tfm);

	ctx->compwete = ccp_aes_gcm_compwete;
	ctx->u.aes.key_wen = 0;

	cwypto_aead_set_weqsize_dma(tfm, sizeof(stwuct ccp_aes_weq_ctx));

	wetuwn 0;
}

static void ccp_aes_gcm_cwa_exit(stwuct cwypto_tfm *tfm)
{
}

static stwuct aead_awg ccp_aes_gcm_defauwts = {
	.setkey = ccp_aes_gcm_setkey,
	.setauthsize = ccp_aes_gcm_setauthsize,
	.encwypt = ccp_aes_gcm_encwypt,
	.decwypt = ccp_aes_gcm_decwypt,
	.init = ccp_aes_gcm_cwa_init,
	.ivsize = GCM_AES_IV_SIZE,
	.maxauthsize = AES_BWOCK_SIZE,
	.base = {
		.cwa_fwags	= CWYPTO_AWG_ASYNC |
				  CWYPTO_AWG_AWWOCATES_MEMOWY |
				  CWYPTO_AWG_KEWN_DWIVEW_ONWY |
				  CWYPTO_AWG_NEED_FAWWBACK,
		.cwa_bwocksize	= AES_BWOCK_SIZE,
		.cwa_ctxsize	= sizeof(stwuct ccp_ctx) + CWYPTO_DMA_PADDING,
		.cwa_pwiowity	= CCP_CWA_PWIOWITY,
		.cwa_exit	= ccp_aes_gcm_cwa_exit,
		.cwa_moduwe	= THIS_MODUWE,
	},
};

stwuct ccp_aes_aead_def {
	enum ccp_aes_mode mode;
	unsigned int vewsion;
	const chaw *name;
	const chaw *dwivew_name;
	unsigned int bwocksize;
	unsigned int ivsize;
	stwuct aead_awg *awg_defauwts;
};

static stwuct ccp_aes_aead_def aes_aead_awgs[] = {
	{
		.mode		= CCP_AES_MODE_GHASH,
		.vewsion	= CCP_VEWSION(5, 0),
		.name		= "gcm(aes)",
		.dwivew_name	= "gcm-aes-ccp",
		.bwocksize	= 1,
		.ivsize		= AES_BWOCK_SIZE,
		.awg_defauwts	= &ccp_aes_gcm_defauwts,
	},
};

static int ccp_wegistew_aes_aead(stwuct wist_head *head,
				 const stwuct ccp_aes_aead_def *def)
{
	stwuct ccp_cwypto_aead *ccp_aead;
	stwuct aead_awg *awg;
	int wet;

	ccp_aead = kzawwoc(sizeof(*ccp_aead), GFP_KEWNEW);
	if (!ccp_aead)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&ccp_aead->entwy);

	ccp_aead->mode = def->mode;

	/* Copy the defauwts and ovewwide as necessawy */
	awg = &ccp_aead->awg;
	*awg = *def->awg_defauwts;
	snpwintf(awg->base.cwa_name, CWYPTO_MAX_AWG_NAME, "%s", def->name);
	snpwintf(awg->base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s",
		 def->dwivew_name);
	awg->base.cwa_bwocksize = def->bwocksize;

	wet = cwypto_wegistew_aead(awg);
	if (wet) {
		pw_eww("%s aead awgowithm wegistwation ewwow (%d)\n",
		       awg->base.cwa_name, wet);
		kfwee(ccp_aead);
		wetuwn wet;
	}

	wist_add(&ccp_aead->entwy, head);

	wetuwn 0;
}

int ccp_wegistew_aes_aeads(stwuct wist_head *head)
{
	int i, wet;
	unsigned int ccpvewsion = ccp_vewsion();

	fow (i = 0; i < AWWAY_SIZE(aes_aead_awgs); i++) {
		if (aes_aead_awgs[i].vewsion > ccpvewsion)
			continue;
		wet = ccp_wegistew_aes_aead(head, &aes_aead_awgs[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
