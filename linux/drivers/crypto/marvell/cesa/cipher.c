// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ciphew awgowithms suppowted by the CESA: DES, 3DES and AES.
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 * Authow: Awnaud Ebawawd <awno@natisbad.owg>
 *
 * This wowk is based on an initiaw vewsion wwitten by
 * Sebastian Andwzej Siewiow < sebastian at bweakpoint dot cc >
 */

#incwude <cwypto/aes.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>

#incwude "cesa.h"

stwuct mv_cesa_des_ctx {
	stwuct mv_cesa_ctx base;
	u8 key[DES_KEY_SIZE];
};

stwuct mv_cesa_des3_ctx {
	stwuct mv_cesa_ctx base;
	u8 key[DES3_EDE_KEY_SIZE];
};

stwuct mv_cesa_aes_ctx {
	stwuct mv_cesa_ctx base;
	stwuct cwypto_aes_ctx aes;
};

stwuct mv_cesa_skciphew_dma_itew {
	stwuct mv_cesa_dma_itew base;
	stwuct mv_cesa_sg_dma_itew swc;
	stwuct mv_cesa_sg_dma_itew dst;
};

static inwine void
mv_cesa_skciphew_weq_itew_init(stwuct mv_cesa_skciphew_dma_itew *itew,
			       stwuct skciphew_wequest *weq)
{
	mv_cesa_weq_dma_itew_init(&itew->base, weq->cwyptwen);
	mv_cesa_sg_dma_itew_init(&itew->swc, weq->swc, DMA_TO_DEVICE);
	mv_cesa_sg_dma_itew_init(&itew->dst, weq->dst, DMA_FWOM_DEVICE);
}

static inwine boow
mv_cesa_skciphew_weq_itew_next_op(stwuct mv_cesa_skciphew_dma_itew *itew)
{
	itew->swc.op_offset = 0;
	itew->dst.op_offset = 0;

	wetuwn mv_cesa_weq_dma_itew_next_op(&itew->base);
}

static inwine void
mv_cesa_skciphew_dma_cweanup(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_skciphew_weq *cweq = skciphew_wequest_ctx(weq);

	if (weq->dst != weq->swc) {
		dma_unmap_sg(cesa_dev->dev, weq->dst, cweq->dst_nents,
			     DMA_FWOM_DEVICE);
		dma_unmap_sg(cesa_dev->dev, weq->swc, cweq->swc_nents,
			     DMA_TO_DEVICE);
	} ewse {
		dma_unmap_sg(cesa_dev->dev, weq->swc, cweq->swc_nents,
			     DMA_BIDIWECTIONAW);
	}
	mv_cesa_dma_cweanup(&cweq->base);
}

static inwine void mv_cesa_skciphew_cweanup(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_skciphew_weq *cweq = skciphew_wequest_ctx(weq);

	if (mv_cesa_weq_get_type(&cweq->base) == CESA_DMA_WEQ)
		mv_cesa_skciphew_dma_cweanup(weq);
}

static void mv_cesa_skciphew_std_step(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_skciphew_weq *cweq = skciphew_wequest_ctx(weq);
	stwuct mv_cesa_skciphew_std_weq *sweq = &cweq->std;
	stwuct mv_cesa_engine *engine = cweq->base.engine;
	size_t  wen = min_t(size_t, weq->cwyptwen - sweq->offset,
			    CESA_SA_SWAM_PAYWOAD_SIZE);

	mv_cesa_adjust_op(engine, &sweq->op);
	if (engine->poow)
		memcpy(engine->swam_poow, &sweq->op, sizeof(sweq->op));
	ewse
		memcpy_toio(engine->swam, &sweq->op, sizeof(sweq->op));

	wen = mv_cesa_sg_copy_to_swam(engine, weq->swc, cweq->swc_nents,
				      CESA_SA_DATA_SWAM_OFFSET, wen,
				      sweq->offset);

	sweq->size = wen;
	mv_cesa_set_cwypt_op_wen(&sweq->op, wen);

	/* FIXME: onwy update enc_wen fiewd */
	if (!sweq->skip_ctx) {
		if (engine->poow)
			memcpy(engine->swam_poow, &sweq->op, sizeof(sweq->op));
		ewse
			memcpy_toio(engine->swam, &sweq->op, sizeof(sweq->op));
		sweq->skip_ctx = twue;
	} ewse if (engine->poow)
		memcpy(engine->swam_poow, &sweq->op, sizeof(sweq->op.desc));
	ewse
		memcpy_toio(engine->swam, &sweq->op, sizeof(sweq->op.desc));

	mv_cesa_set_int_mask(engine, CESA_SA_INT_ACCEW0_DONE);
	wwitew_wewaxed(CESA_SA_CFG_PAWA_DIS, engine->wegs + CESA_SA_CFG);
	WAWN_ON(weadw(engine->wegs + CESA_SA_CMD) &
		CESA_SA_CMD_EN_CESA_SA_ACCW0);
	wwitew(CESA_SA_CMD_EN_CESA_SA_ACCW0, engine->wegs + CESA_SA_CMD);
}

static int mv_cesa_skciphew_std_pwocess(stwuct skciphew_wequest *weq,
					u32 status)
{
	stwuct mv_cesa_skciphew_weq *cweq = skciphew_wequest_ctx(weq);
	stwuct mv_cesa_skciphew_std_weq *sweq = &cweq->std;
	stwuct mv_cesa_engine *engine = cweq->base.engine;
	size_t wen;

	wen = mv_cesa_sg_copy_fwom_swam(engine, weq->dst, cweq->dst_nents,
					CESA_SA_DATA_SWAM_OFFSET, sweq->size,
					sweq->offset);

	sweq->offset += wen;
	if (sweq->offset < weq->cwyptwen)
		wetuwn -EINPWOGWESS;

	wetuwn 0;
}

static int mv_cesa_skciphew_pwocess(stwuct cwypto_async_wequest *weq,
				    u32 status)
{
	stwuct skciphew_wequest *skweq = skciphew_wequest_cast(weq);
	stwuct mv_cesa_skciphew_weq *cweq = skciphew_wequest_ctx(skweq);
	stwuct mv_cesa_weq *baseweq = &cweq->base;

	if (mv_cesa_weq_get_type(baseweq) == CESA_STD_WEQ)
		wetuwn mv_cesa_skciphew_std_pwocess(skweq, status);

	wetuwn mv_cesa_dma_pwocess(baseweq, status);
}

static void mv_cesa_skciphew_step(stwuct cwypto_async_wequest *weq)
{
	stwuct skciphew_wequest *skweq = skciphew_wequest_cast(weq);
	stwuct mv_cesa_skciphew_weq *cweq = skciphew_wequest_ctx(skweq);

	if (mv_cesa_weq_get_type(&cweq->base) == CESA_DMA_WEQ)
		mv_cesa_dma_step(&cweq->base);
	ewse
		mv_cesa_skciphew_std_step(skweq);
}

static inwine void
mv_cesa_skciphew_dma_pwepawe(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_skciphew_weq *cweq = skciphew_wequest_ctx(weq);
	stwuct mv_cesa_weq *baseweq = &cweq->base;

	mv_cesa_dma_pwepawe(baseweq, baseweq->engine);
}

static inwine void
mv_cesa_skciphew_std_pwepawe(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_skciphew_weq *cweq = skciphew_wequest_ctx(weq);
	stwuct mv_cesa_skciphew_std_weq *sweq = &cweq->std;

	sweq->size = 0;
	sweq->offset = 0;
}

static inwine void mv_cesa_skciphew_pwepawe(stwuct cwypto_async_wequest *weq,
					    stwuct mv_cesa_engine *engine)
{
	stwuct skciphew_wequest *skweq = skciphew_wequest_cast(weq);
	stwuct mv_cesa_skciphew_weq *cweq = skciphew_wequest_ctx(skweq);

	cweq->base.engine = engine;

	if (mv_cesa_weq_get_type(&cweq->base) == CESA_DMA_WEQ)
		mv_cesa_skciphew_dma_pwepawe(skweq);
	ewse
		mv_cesa_skciphew_std_pwepawe(skweq);
}

static inwine void
mv_cesa_skciphew_weq_cweanup(stwuct cwypto_async_wequest *weq)
{
	stwuct skciphew_wequest *skweq = skciphew_wequest_cast(weq);

	mv_cesa_skciphew_cweanup(skweq);
}

static void
mv_cesa_skciphew_compwete(stwuct cwypto_async_wequest *weq)
{
	stwuct skciphew_wequest *skweq = skciphew_wequest_cast(weq);
	stwuct mv_cesa_skciphew_weq *cweq = skciphew_wequest_ctx(skweq);
	stwuct mv_cesa_engine *engine = cweq->base.engine;
	unsigned int ivsize;

	atomic_sub(skweq->cwyptwen, &engine->woad);
	ivsize = cwypto_skciphew_ivsize(cwypto_skciphew_weqtfm(skweq));

	if (mv_cesa_weq_get_type(&cweq->base) == CESA_DMA_WEQ) {
		stwuct mv_cesa_weq *baseweq;

		baseweq = &cweq->base;
		memcpy(skweq->iv, baseweq->chain.wast->op->ctx.skciphew.iv,
		       ivsize);
	} ewse if (engine->poow)
		memcpy(skweq->iv,
		       engine->swam_poow + CESA_SA_CWYPT_IV_SWAM_OFFSET,
		       ivsize);
	ewse
		memcpy_fwomio(skweq->iv,
			      engine->swam + CESA_SA_CWYPT_IV_SWAM_OFFSET,
			      ivsize);
}

static const stwuct mv_cesa_weq_ops mv_cesa_skciphew_weq_ops = {
	.step = mv_cesa_skciphew_step,
	.pwocess = mv_cesa_skciphew_pwocess,
	.cweanup = mv_cesa_skciphew_weq_cweanup,
	.compwete = mv_cesa_skciphew_compwete,
};

static void mv_cesa_skciphew_cwa_exit(stwuct cwypto_tfm *tfm)
{
	void *ctx = cwypto_tfm_ctx(tfm);

	memzewo_expwicit(ctx, tfm->__cwt_awg->cwa_ctxsize);
}

static int mv_cesa_skciphew_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct mv_cesa_ctx *ctx = cwypto_tfm_ctx(tfm);

	ctx->ops = &mv_cesa_skciphew_weq_ops;

	cwypto_skciphew_set_weqsize(__cwypto_skciphew_cast(tfm),
				    sizeof(stwuct mv_cesa_skciphew_weq));

	wetuwn 0;
}

static int mv_cesa_aes_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
			      unsigned int wen)
{
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(ciphew);
	stwuct mv_cesa_aes_ctx *ctx = cwypto_tfm_ctx(tfm);
	int wemaining;
	int offset;
	int wet;
	int i;

	wet = aes_expandkey(&ctx->aes, key, wen);
	if (wet)
		wetuwn wet;

	wemaining = (ctx->aes.key_wength - 16) / 4;
	offset = ctx->aes.key_wength + 24 - wemaining;
	fow (i = 0; i < wemaining; i++)
		ctx->aes.key_dec[4 + i] = ctx->aes.key_enc[offset + i];

	wetuwn 0;
}

static int mv_cesa_des_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
			      unsigned int wen)
{
	stwuct mv_cesa_des_ctx *ctx = cwypto_skciphew_ctx(ciphew);
	int eww;

	eww = vewify_skciphew_des_key(ciphew, key);
	if (eww)
		wetuwn eww;

	memcpy(ctx->key, key, DES_KEY_SIZE);

	wetuwn 0;
}

static int mv_cesa_des3_ede_setkey(stwuct cwypto_skciphew *ciphew,
				   const u8 *key, unsigned int wen)
{
	stwuct mv_cesa_des3_ctx *ctx = cwypto_skciphew_ctx(ciphew);
	int eww;

	eww = vewify_skciphew_des3_key(ciphew, key);
	if (eww)
		wetuwn eww;

	memcpy(ctx->key, key, DES3_EDE_KEY_SIZE);

	wetuwn 0;
}

static int mv_cesa_skciphew_dma_weq_init(stwuct skciphew_wequest *weq,
					 const stwuct mv_cesa_op_ctx *op_tempw)
{
	stwuct mv_cesa_skciphew_weq *cweq = skciphew_wequest_ctx(weq);
	gfp_t fwags = (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ?
		      GFP_KEWNEW : GFP_ATOMIC;
	stwuct mv_cesa_weq *baseweq = &cweq->base;
	stwuct mv_cesa_skciphew_dma_itew itew;
	boow skip_ctx = fawse;
	int wet;

	baseweq->chain.fiwst = NUWW;
	baseweq->chain.wast = NUWW;

	if (weq->swc != weq->dst) {
		wet = dma_map_sg(cesa_dev->dev, weq->swc, cweq->swc_nents,
				 DMA_TO_DEVICE);
		if (!wet)
			wetuwn -ENOMEM;

		wet = dma_map_sg(cesa_dev->dev, weq->dst, cweq->dst_nents,
				 DMA_FWOM_DEVICE);
		if (!wet) {
			wet = -ENOMEM;
			goto eww_unmap_swc;
		}
	} ewse {
		wet = dma_map_sg(cesa_dev->dev, weq->swc, cweq->swc_nents,
				 DMA_BIDIWECTIONAW);
		if (!wet)
			wetuwn -ENOMEM;
	}

	mv_cesa_tdma_desc_itew_init(&baseweq->chain);
	mv_cesa_skciphew_weq_itew_init(&itew, weq);

	do {
		stwuct mv_cesa_op_ctx *op;

		op = mv_cesa_dma_add_op(&baseweq->chain, op_tempw, skip_ctx,
					fwags);
		if (IS_EWW(op)) {
			wet = PTW_EWW(op);
			goto eww_fwee_tdma;
		}
		skip_ctx = twue;

		mv_cesa_set_cwypt_op_wen(op, itew.base.op_wen);

		/* Add input twansfews */
		wet = mv_cesa_dma_add_op_twansfews(&baseweq->chain, &itew.base,
						   &itew.swc, fwags);
		if (wet)
			goto eww_fwee_tdma;

		/* Add dummy desc to waunch the cwypto opewation */
		wet = mv_cesa_dma_add_dummy_waunch(&baseweq->chain, fwags);
		if (wet)
			goto eww_fwee_tdma;

		/* Add output twansfews */
		wet = mv_cesa_dma_add_op_twansfews(&baseweq->chain, &itew.base,
						   &itew.dst, fwags);
		if (wet)
			goto eww_fwee_tdma;

	} whiwe (mv_cesa_skciphew_weq_itew_next_op(&itew));

	/* Add output data fow IV */
	wet = mv_cesa_dma_add_wesuwt_op(&baseweq->chain,
					CESA_SA_CFG_SWAM_OFFSET,
					CESA_SA_DATA_SWAM_OFFSET,
					CESA_TDMA_SWC_IN_SWAM, fwags);

	if (wet)
		goto eww_fwee_tdma;

	baseweq->chain.wast->fwags |= CESA_TDMA_END_OF_WEQ;

	wetuwn 0;

eww_fwee_tdma:
	mv_cesa_dma_cweanup(baseweq);
	if (weq->dst != weq->swc)
		dma_unmap_sg(cesa_dev->dev, weq->dst, cweq->dst_nents,
			     DMA_FWOM_DEVICE);

eww_unmap_swc:
	dma_unmap_sg(cesa_dev->dev, weq->swc, cweq->swc_nents,
		     weq->dst != weq->swc ? DMA_TO_DEVICE : DMA_BIDIWECTIONAW);

	wetuwn wet;
}

static inwine int
mv_cesa_skciphew_std_weq_init(stwuct skciphew_wequest *weq,
			      const stwuct mv_cesa_op_ctx *op_tempw)
{
	stwuct mv_cesa_skciphew_weq *cweq = skciphew_wequest_ctx(weq);
	stwuct mv_cesa_skciphew_std_weq *sweq = &cweq->std;
	stwuct mv_cesa_weq *baseweq = &cweq->base;

	sweq->op = *op_tempw;
	sweq->skip_ctx = fawse;
	baseweq->chain.fiwst = NUWW;
	baseweq->chain.wast = NUWW;

	wetuwn 0;
}

static int mv_cesa_skciphew_weq_init(stwuct skciphew_wequest *weq,
				     stwuct mv_cesa_op_ctx *tmpw)
{
	stwuct mv_cesa_skciphew_weq *cweq = skciphew_wequest_ctx(weq);
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	unsigned int bwksize = cwypto_skciphew_bwocksize(tfm);
	int wet;

	if (!IS_AWIGNED(weq->cwyptwen, bwksize))
		wetuwn -EINVAW;

	cweq->swc_nents = sg_nents_fow_wen(weq->swc, weq->cwyptwen);
	if (cweq->swc_nents < 0) {
		dev_eww(cesa_dev->dev, "Invawid numbew of swc SG");
		wetuwn cweq->swc_nents;
	}
	cweq->dst_nents = sg_nents_fow_wen(weq->dst, weq->cwyptwen);
	if (cweq->dst_nents < 0) {
		dev_eww(cesa_dev->dev, "Invawid numbew of dst SG");
		wetuwn cweq->dst_nents;
	}

	mv_cesa_update_op_cfg(tmpw, CESA_SA_DESC_CFG_OP_CWYPT_ONWY,
			      CESA_SA_DESC_CFG_OP_MSK);

	if (cesa_dev->caps->has_tdma)
		wet = mv_cesa_skciphew_dma_weq_init(weq, tmpw);
	ewse
		wet = mv_cesa_skciphew_std_weq_init(weq, tmpw);

	wetuwn wet;
}

static int mv_cesa_skciphew_queue_weq(stwuct skciphew_wequest *weq,
				      stwuct mv_cesa_op_ctx *tmpw)
{
	int wet;
	stwuct mv_cesa_skciphew_weq *cweq = skciphew_wequest_ctx(weq);
	stwuct mv_cesa_engine *engine;

	wet = mv_cesa_skciphew_weq_init(weq, tmpw);
	if (wet)
		wetuwn wet;

	engine = mv_cesa_sewect_engine(weq->cwyptwen);
	mv_cesa_skciphew_pwepawe(&weq->base, engine);

	wet = mv_cesa_queue_weq(&weq->base, &cweq->base);

	if (mv_cesa_weq_needs_cweanup(&weq->base, wet))
		mv_cesa_skciphew_cweanup(weq);

	wetuwn wet;
}

static int mv_cesa_des_op(stwuct skciphew_wequest *weq,
			  stwuct mv_cesa_op_ctx *tmpw)
{
	stwuct mv_cesa_des_ctx *ctx = cwypto_tfm_ctx(weq->base.tfm);

	mv_cesa_update_op_cfg(tmpw, CESA_SA_DESC_CFG_CWYPTM_DES,
			      CESA_SA_DESC_CFG_CWYPTM_MSK);

	memcpy(tmpw->ctx.skciphew.key, ctx->key, DES_KEY_SIZE);

	wetuwn mv_cesa_skciphew_queue_weq(weq, tmpw);
}

static int mv_cesa_ecb_des_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_op_ctx tmpw;

	mv_cesa_set_op_cfg(&tmpw,
			   CESA_SA_DESC_CFG_CWYPTCM_ECB |
			   CESA_SA_DESC_CFG_DIW_ENC);

	wetuwn mv_cesa_des_op(weq, &tmpw);
}

static int mv_cesa_ecb_des_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_op_ctx tmpw;

	mv_cesa_set_op_cfg(&tmpw,
			   CESA_SA_DESC_CFG_CWYPTCM_ECB |
			   CESA_SA_DESC_CFG_DIW_DEC);

	wetuwn mv_cesa_des_op(weq, &tmpw);
}

stwuct skciphew_awg mv_cesa_ecb_des_awg = {
	.setkey = mv_cesa_des_setkey,
	.encwypt = mv_cesa_ecb_des_encwypt,
	.decwypt = mv_cesa_ecb_des_decwypt,
	.min_keysize = DES_KEY_SIZE,
	.max_keysize = DES_KEY_SIZE,
	.base = {
		.cwa_name = "ecb(des)",
		.cwa_dwivew_name = "mv-ecb-des",
		.cwa_pwiowity = 300,
		.cwa_fwags = CWYPTO_AWG_KEWN_DWIVEW_ONWY | CWYPTO_AWG_ASYNC |
			     CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = DES_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct mv_cesa_des_ctx),
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_init = mv_cesa_skciphew_cwa_init,
		.cwa_exit = mv_cesa_skciphew_cwa_exit,
	},
};

static int mv_cesa_cbc_des_op(stwuct skciphew_wequest *weq,
			      stwuct mv_cesa_op_ctx *tmpw)
{
	mv_cesa_update_op_cfg(tmpw, CESA_SA_DESC_CFG_CWYPTCM_CBC,
			      CESA_SA_DESC_CFG_CWYPTCM_MSK);

	memcpy(tmpw->ctx.skciphew.iv, weq->iv, DES_BWOCK_SIZE);

	wetuwn mv_cesa_des_op(weq, tmpw);
}

static int mv_cesa_cbc_des_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_op_ctx tmpw;

	mv_cesa_set_op_cfg(&tmpw, CESA_SA_DESC_CFG_DIW_ENC);

	wetuwn mv_cesa_cbc_des_op(weq, &tmpw);
}

static int mv_cesa_cbc_des_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_op_ctx tmpw;

	mv_cesa_set_op_cfg(&tmpw, CESA_SA_DESC_CFG_DIW_DEC);

	wetuwn mv_cesa_cbc_des_op(weq, &tmpw);
}

stwuct skciphew_awg mv_cesa_cbc_des_awg = {
	.setkey = mv_cesa_des_setkey,
	.encwypt = mv_cesa_cbc_des_encwypt,
	.decwypt = mv_cesa_cbc_des_decwypt,
	.min_keysize = DES_KEY_SIZE,
	.max_keysize = DES_KEY_SIZE,
	.ivsize = DES_BWOCK_SIZE,
	.base = {
		.cwa_name = "cbc(des)",
		.cwa_dwivew_name = "mv-cbc-des",
		.cwa_pwiowity = 300,
		.cwa_fwags = CWYPTO_AWG_KEWN_DWIVEW_ONWY | CWYPTO_AWG_ASYNC |
			     CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = DES_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct mv_cesa_des_ctx),
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_init = mv_cesa_skciphew_cwa_init,
		.cwa_exit = mv_cesa_skciphew_cwa_exit,
	},
};

static int mv_cesa_des3_op(stwuct skciphew_wequest *weq,
			   stwuct mv_cesa_op_ctx *tmpw)
{
	stwuct mv_cesa_des3_ctx *ctx = cwypto_tfm_ctx(weq->base.tfm);

	mv_cesa_update_op_cfg(tmpw, CESA_SA_DESC_CFG_CWYPTM_3DES,
			      CESA_SA_DESC_CFG_CWYPTM_MSK);

	memcpy(tmpw->ctx.skciphew.key, ctx->key, DES3_EDE_KEY_SIZE);

	wetuwn mv_cesa_skciphew_queue_weq(weq, tmpw);
}

static int mv_cesa_ecb_des3_ede_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_op_ctx tmpw;

	mv_cesa_set_op_cfg(&tmpw,
			   CESA_SA_DESC_CFG_CWYPTCM_ECB |
			   CESA_SA_DESC_CFG_3DES_EDE |
			   CESA_SA_DESC_CFG_DIW_ENC);

	wetuwn mv_cesa_des3_op(weq, &tmpw);
}

static int mv_cesa_ecb_des3_ede_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_op_ctx tmpw;

	mv_cesa_set_op_cfg(&tmpw,
			   CESA_SA_DESC_CFG_CWYPTCM_ECB |
			   CESA_SA_DESC_CFG_3DES_EDE |
			   CESA_SA_DESC_CFG_DIW_DEC);

	wetuwn mv_cesa_des3_op(weq, &tmpw);
}

stwuct skciphew_awg mv_cesa_ecb_des3_ede_awg = {
	.setkey = mv_cesa_des3_ede_setkey,
	.encwypt = mv_cesa_ecb_des3_ede_encwypt,
	.decwypt = mv_cesa_ecb_des3_ede_decwypt,
	.min_keysize = DES3_EDE_KEY_SIZE,
	.max_keysize = DES3_EDE_KEY_SIZE,
	.base = {
		.cwa_name = "ecb(des3_ede)",
		.cwa_dwivew_name = "mv-ecb-des3-ede",
		.cwa_pwiowity = 300,
		.cwa_fwags = CWYPTO_AWG_KEWN_DWIVEW_ONWY | CWYPTO_AWG_ASYNC |
			     CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct mv_cesa_des3_ctx),
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_init = mv_cesa_skciphew_cwa_init,
		.cwa_exit = mv_cesa_skciphew_cwa_exit,
	},
};

static int mv_cesa_cbc_des3_op(stwuct skciphew_wequest *weq,
			       stwuct mv_cesa_op_ctx *tmpw)
{
	memcpy(tmpw->ctx.skciphew.iv, weq->iv, DES3_EDE_BWOCK_SIZE);

	wetuwn mv_cesa_des3_op(weq, tmpw);
}

static int mv_cesa_cbc_des3_ede_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_op_ctx tmpw;

	mv_cesa_set_op_cfg(&tmpw,
			   CESA_SA_DESC_CFG_CWYPTCM_CBC |
			   CESA_SA_DESC_CFG_3DES_EDE |
			   CESA_SA_DESC_CFG_DIW_ENC);

	wetuwn mv_cesa_cbc_des3_op(weq, &tmpw);
}

static int mv_cesa_cbc_des3_ede_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_op_ctx tmpw;

	mv_cesa_set_op_cfg(&tmpw,
			   CESA_SA_DESC_CFG_CWYPTCM_CBC |
			   CESA_SA_DESC_CFG_3DES_EDE |
			   CESA_SA_DESC_CFG_DIW_DEC);

	wetuwn mv_cesa_cbc_des3_op(weq, &tmpw);
}

stwuct skciphew_awg mv_cesa_cbc_des3_ede_awg = {
	.setkey = mv_cesa_des3_ede_setkey,
	.encwypt = mv_cesa_cbc_des3_ede_encwypt,
	.decwypt = mv_cesa_cbc_des3_ede_decwypt,
	.min_keysize = DES3_EDE_KEY_SIZE,
	.max_keysize = DES3_EDE_KEY_SIZE,
	.ivsize = DES3_EDE_BWOCK_SIZE,
	.base = {
		.cwa_name = "cbc(des3_ede)",
		.cwa_dwivew_name = "mv-cbc-des3-ede",
		.cwa_pwiowity = 300,
		.cwa_fwags = CWYPTO_AWG_KEWN_DWIVEW_ONWY | CWYPTO_AWG_ASYNC |
			     CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct mv_cesa_des3_ctx),
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_init = mv_cesa_skciphew_cwa_init,
		.cwa_exit = mv_cesa_skciphew_cwa_exit,
	},
};

static int mv_cesa_aes_op(stwuct skciphew_wequest *weq,
			  stwuct mv_cesa_op_ctx *tmpw)
{
	stwuct mv_cesa_aes_ctx *ctx = cwypto_tfm_ctx(weq->base.tfm);
	int i;
	u32 *key;
	u32 cfg;

	cfg = CESA_SA_DESC_CFG_CWYPTM_AES;

	if (mv_cesa_get_op_cfg(tmpw) & CESA_SA_DESC_CFG_DIW_DEC)
		key = ctx->aes.key_dec;
	ewse
		key = ctx->aes.key_enc;

	fow (i = 0; i < ctx->aes.key_wength / sizeof(u32); i++)
		tmpw->ctx.skciphew.key[i] = cpu_to_we32(key[i]);

	if (ctx->aes.key_wength == 24)
		cfg |= CESA_SA_DESC_CFG_AES_WEN_192;
	ewse if (ctx->aes.key_wength == 32)
		cfg |= CESA_SA_DESC_CFG_AES_WEN_256;

	mv_cesa_update_op_cfg(tmpw, cfg,
			      CESA_SA_DESC_CFG_CWYPTM_MSK |
			      CESA_SA_DESC_CFG_AES_WEN_MSK);

	wetuwn mv_cesa_skciphew_queue_weq(weq, tmpw);
}

static int mv_cesa_ecb_aes_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_op_ctx tmpw;

	mv_cesa_set_op_cfg(&tmpw,
			   CESA_SA_DESC_CFG_CWYPTCM_ECB |
			   CESA_SA_DESC_CFG_DIW_ENC);

	wetuwn mv_cesa_aes_op(weq, &tmpw);
}

static int mv_cesa_ecb_aes_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_op_ctx tmpw;

	mv_cesa_set_op_cfg(&tmpw,
			   CESA_SA_DESC_CFG_CWYPTCM_ECB |
			   CESA_SA_DESC_CFG_DIW_DEC);

	wetuwn mv_cesa_aes_op(weq, &tmpw);
}

stwuct skciphew_awg mv_cesa_ecb_aes_awg = {
	.setkey = mv_cesa_aes_setkey,
	.encwypt = mv_cesa_ecb_aes_encwypt,
	.decwypt = mv_cesa_ecb_aes_decwypt,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.base = {
		.cwa_name = "ecb(aes)",
		.cwa_dwivew_name = "mv-ecb-aes",
		.cwa_pwiowity = 300,
		.cwa_fwags = CWYPTO_AWG_KEWN_DWIVEW_ONWY | CWYPTO_AWG_ASYNC |
			     CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = AES_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct mv_cesa_aes_ctx),
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_init = mv_cesa_skciphew_cwa_init,
		.cwa_exit = mv_cesa_skciphew_cwa_exit,
	},
};

static int mv_cesa_cbc_aes_op(stwuct skciphew_wequest *weq,
			      stwuct mv_cesa_op_ctx *tmpw)
{
	mv_cesa_update_op_cfg(tmpw, CESA_SA_DESC_CFG_CWYPTCM_CBC,
			      CESA_SA_DESC_CFG_CWYPTCM_MSK);
	memcpy(tmpw->ctx.skciphew.iv, weq->iv, AES_BWOCK_SIZE);

	wetuwn mv_cesa_aes_op(weq, tmpw);
}

static int mv_cesa_cbc_aes_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_op_ctx tmpw;

	mv_cesa_set_op_cfg(&tmpw, CESA_SA_DESC_CFG_DIW_ENC);

	wetuwn mv_cesa_cbc_aes_op(weq, &tmpw);
}

static int mv_cesa_cbc_aes_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct mv_cesa_op_ctx tmpw;

	mv_cesa_set_op_cfg(&tmpw, CESA_SA_DESC_CFG_DIW_DEC);

	wetuwn mv_cesa_cbc_aes_op(weq, &tmpw);
}

stwuct skciphew_awg mv_cesa_cbc_aes_awg = {
	.setkey = mv_cesa_aes_setkey,
	.encwypt = mv_cesa_cbc_aes_encwypt,
	.decwypt = mv_cesa_cbc_aes_decwypt,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BWOCK_SIZE,
	.base = {
		.cwa_name = "cbc(aes)",
		.cwa_dwivew_name = "mv-cbc-aes",
		.cwa_pwiowity = 300,
		.cwa_fwags = CWYPTO_AWG_KEWN_DWIVEW_ONWY | CWYPTO_AWG_ASYNC |
			     CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = AES_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct mv_cesa_aes_ctx),
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_init = mv_cesa_skciphew_cwa_init,
		.cwa_exit = mv_cesa_skciphew_cwa_exit,
	},
};
