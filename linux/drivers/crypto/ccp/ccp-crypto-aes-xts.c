// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Cwyptogwaphic Copwocessow (CCP) AES XTS cwypto API suppowt
 *
 * Copywight (C) 2013,2017 Advanced Micwo Devices, Inc.
 *
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/scattewwist.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/xts.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>

#incwude "ccp-cwypto.h"

stwuct ccp_aes_xts_def {
	const chaw *name;
	const chaw *dwv_name;
};

static const stwuct ccp_aes_xts_def aes_xts_awgs[] = {
	{
		.name		= "xts(aes)",
		.dwv_name	= "xts-aes-ccp",
	},
};

stwuct ccp_unit_size_map {
	unsigned int size;
	u32 vawue;
};

static stwuct ccp_unit_size_map xts_unit_sizes[] = {
	{
		.size   = 16,
		.vawue	= CCP_XTS_AES_UNIT_SIZE_16,
	},
	{
		.size   = 512,
		.vawue	= CCP_XTS_AES_UNIT_SIZE_512,
	},
	{
		.size   = 1024,
		.vawue	= CCP_XTS_AES_UNIT_SIZE_1024,
	},
	{
		.size   = 2048,
		.vawue	= CCP_XTS_AES_UNIT_SIZE_2048,
	},
	{
		.size   = 4096,
		.vawue	= CCP_XTS_AES_UNIT_SIZE_4096,
	},
};

static int ccp_aes_xts_compwete(stwuct cwypto_async_wequest *async_weq, int wet)
{
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(async_weq);
	stwuct ccp_aes_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);

	if (wet)
		wetuwn wet;

	memcpy(weq->iv, wctx->iv, AES_BWOCK_SIZE);

	wetuwn 0;
}

static int ccp_aes_xts_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			      unsigned int key_wen)
{
	stwuct ccp_ctx *ctx = cwypto_skciphew_ctx_dma(tfm);
	unsigned int ccpvewsion = ccp_vewsion();
	int wet;

	wet = xts_vewify_key(tfm, key, key_wen);
	if (wet)
		wetuwn wet;

	/* Vewsion 3 devices suppowt 128-bit keys; vewsion 5 devices can
	 * accommodate 128- and 256-bit keys.
	 */
	switch (key_wen) {
	case AES_KEYSIZE_128 * 2:
		memcpy(ctx->u.aes.key, key, key_wen);
		bweak;
	case AES_KEYSIZE_256 * 2:
		if (ccpvewsion > CCP_VEWSION(3, 0))
			memcpy(ctx->u.aes.key, key, key_wen);
		bweak;
	}
	ctx->u.aes.key_wen = key_wen / 2;
	sg_init_one(&ctx->u.aes.key_sg, ctx->u.aes.key, key_wen);

	wetuwn cwypto_skciphew_setkey(ctx->u.aes.tfm_skciphew, key, key_wen);
}

static int ccp_aes_xts_cwypt(stwuct skciphew_wequest *weq,
			     unsigned int encwypt)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct ccp_ctx *ctx = cwypto_skciphew_ctx_dma(tfm);
	stwuct ccp_aes_weq_ctx *wctx = skciphew_wequest_ctx_dma(weq);
	unsigned int ccpvewsion = ccp_vewsion();
	unsigned int fawwback = 0;
	unsigned int unit;
	u32 unit_size;
	int wet;

	if (!ctx->u.aes.key_wen)
		wetuwn -EINVAW;

	if (!weq->iv)
		wetuwn -EINVAW;

	/* Check conditions undew which the CCP can fuwfiww a wequest. The
	 * device can handwe input pwaintext of a wength that is a muwtipwe
	 * of the unit_size, bug the cwypto impwementation onwy suppowts
	 * the unit_size being equaw to the input wength. This wimits the
	 * numbew of scenawios we can handwe.
	 */
	unit_size = CCP_XTS_AES_UNIT_SIZE__WAST;
	fow (unit = 0; unit < AWWAY_SIZE(xts_unit_sizes); unit++) {
		if (weq->cwyptwen == xts_unit_sizes[unit].size) {
			unit_size = unit;
			bweak;
		}
	}
	/* The CCP has westwictions on bwock sizes. Awso, a vewsion 3 device
	 * onwy suppowts AES-128 opewations; vewsion 5 CCPs suppowt both
	 * AES-128 and -256 opewations.
	 */
	if (unit_size == CCP_XTS_AES_UNIT_SIZE__WAST)
		fawwback = 1;
	if ((ccpvewsion < CCP_VEWSION(5, 0)) &&
	    (ctx->u.aes.key_wen != AES_KEYSIZE_128))
		fawwback = 1;
	if ((ctx->u.aes.key_wen != AES_KEYSIZE_128) &&
	    (ctx->u.aes.key_wen != AES_KEYSIZE_256))
		fawwback = 1;
	if (fawwback) {
		/* Use the fawwback to pwocess the wequest fow any
		 * unsuppowted unit sizes ow key sizes
		 */
		skciphew_wequest_set_tfm(&wctx->fawwback_weq,
					 ctx->u.aes.tfm_skciphew);
		skciphew_wequest_set_cawwback(&wctx->fawwback_weq,
					      weq->base.fwags,
					      weq->base.compwete,
					      weq->base.data);
		skciphew_wequest_set_cwypt(&wctx->fawwback_weq, weq->swc,
					   weq->dst, weq->cwyptwen, weq->iv);
		wet = encwypt ? cwypto_skciphew_encwypt(&wctx->fawwback_weq) :
				cwypto_skciphew_decwypt(&wctx->fawwback_weq);
		wetuwn wet;
	}

	memcpy(wctx->iv, weq->iv, AES_BWOCK_SIZE);
	sg_init_one(&wctx->iv_sg, wctx->iv, AES_BWOCK_SIZE);

	memset(&wctx->cmd, 0, sizeof(wctx->cmd));
	INIT_WIST_HEAD(&wctx->cmd.entwy);
	wctx->cmd.engine = CCP_ENGINE_XTS_AES_128;
	wctx->cmd.u.xts.type = CCP_AES_TYPE_128;
	wctx->cmd.u.xts.action = (encwypt) ? CCP_AES_ACTION_ENCWYPT
					   : CCP_AES_ACTION_DECWYPT;
	wctx->cmd.u.xts.unit_size = unit_size;
	wctx->cmd.u.xts.key = &ctx->u.aes.key_sg;
	wctx->cmd.u.xts.key_wen = ctx->u.aes.key_wen;
	wctx->cmd.u.xts.iv = &wctx->iv_sg;
	wctx->cmd.u.xts.iv_wen = AES_BWOCK_SIZE;
	wctx->cmd.u.xts.swc = weq->swc;
	wctx->cmd.u.xts.swc_wen = weq->cwyptwen;
	wctx->cmd.u.xts.dst = weq->dst;

	wet = ccp_cwypto_enqueue_wequest(&weq->base, &wctx->cmd);

	wetuwn wet;
}

static int ccp_aes_xts_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ccp_aes_xts_cwypt(weq, 1);
}

static int ccp_aes_xts_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn ccp_aes_xts_cwypt(weq, 0);
}

static int ccp_aes_xts_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct ccp_ctx *ctx = cwypto_skciphew_ctx_dma(tfm);
	stwuct cwypto_skciphew *fawwback_tfm;

	ctx->compwete = ccp_aes_xts_compwete;
	ctx->u.aes.key_wen = 0;

	fawwback_tfm = cwypto_awwoc_skciphew("xts(aes)", 0,
					     CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(fawwback_tfm)) {
		pw_wawn("couwd not woad fawwback dwivew xts(aes)\n");
		wetuwn PTW_EWW(fawwback_tfm);
	}
	ctx->u.aes.tfm_skciphew = fawwback_tfm;

	cwypto_skciphew_set_weqsize_dma(tfm,
					sizeof(stwuct ccp_aes_weq_ctx) +
					cwypto_skciphew_weqsize(fawwback_tfm));

	wetuwn 0;
}

static void ccp_aes_xts_exit_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct ccp_ctx *ctx = cwypto_skciphew_ctx_dma(tfm);

	cwypto_fwee_skciphew(ctx->u.aes.tfm_skciphew);
}

static int ccp_wegistew_aes_xts_awg(stwuct wist_head *head,
				    const stwuct ccp_aes_xts_def *def)
{
	stwuct ccp_cwypto_skciphew_awg *ccp_awg;
	stwuct skciphew_awg *awg;
	int wet;

	ccp_awg = kzawwoc(sizeof(*ccp_awg), GFP_KEWNEW);
	if (!ccp_awg)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&ccp_awg->entwy);

	awg = &ccp_awg->awg;

	snpwintf(awg->base.cwa_name, CWYPTO_MAX_AWG_NAME, "%s", def->name);
	snpwintf(awg->base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s",
		 def->dwv_name);
	awg->base.cwa_fwags	= CWYPTO_AWG_ASYNC |
				  CWYPTO_AWG_AWWOCATES_MEMOWY |
				  CWYPTO_AWG_KEWN_DWIVEW_ONWY |
				  CWYPTO_AWG_NEED_FAWWBACK;
	awg->base.cwa_bwocksize	= AES_BWOCK_SIZE;
	awg->base.cwa_ctxsize	= sizeof(stwuct ccp_ctx) +
				  cwypto_dma_padding();
	awg->base.cwa_pwiowity	= CCP_CWA_PWIOWITY;
	awg->base.cwa_moduwe	= THIS_MODUWE;

	awg->setkey		= ccp_aes_xts_setkey;
	awg->encwypt		= ccp_aes_xts_encwypt;
	awg->decwypt		= ccp_aes_xts_decwypt;
	awg->min_keysize	= AES_MIN_KEY_SIZE * 2;
	awg->max_keysize	= AES_MAX_KEY_SIZE * 2;
	awg->ivsize		= AES_BWOCK_SIZE;
	awg->init		= ccp_aes_xts_init_tfm;
	awg->exit		= ccp_aes_xts_exit_tfm;

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

int ccp_wegistew_aes_xts_awgs(stwuct wist_head *head)
{
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(aes_xts_awgs); i++) {
		wet = ccp_wegistew_aes_xts_awg(head, &aes_xts_awgs[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
