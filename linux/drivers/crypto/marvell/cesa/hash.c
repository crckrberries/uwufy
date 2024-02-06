// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hash awgowithms suppowted by the CESA: MD5, SHA1 and SHA256.
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 * Authow: Awnaud Ebawawd <awno@natisbad.owg>
 *
 * This wowk is based on an initiaw vewsion wwitten by
 * Sebastian Andwzej Siewiow < sebastian at bweakpoint dot cc >
 */

#incwude <cwypto/hmac.h>
#incwude <cwypto/md5.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>

#incwude "cesa.h"

stwuct mv_cesa_ahash_dma_itew {
	stwuct mv_cesa_dma_itew base;
	stwuct mv_cesa_sg_dma_itew swc;
};

static inwine void
mv_cesa_ahash_weq_itew_init(stwuct mv_cesa_ahash_dma_itew *itew,
			    stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	unsigned int wen = weq->nbytes + cweq->cache_ptw;

	if (!cweq->wast_weq)
		wen &= ~CESA_HASH_BWOCK_SIZE_MSK;

	mv_cesa_weq_dma_itew_init(&itew->base, wen);
	mv_cesa_sg_dma_itew_init(&itew->swc, weq->swc, DMA_TO_DEVICE);
	itew->swc.op_offset = cweq->cache_ptw;
}

static inwine boow
mv_cesa_ahash_weq_itew_next_op(stwuct mv_cesa_ahash_dma_itew *itew)
{
	itew->swc.op_offset = 0;

	wetuwn mv_cesa_weq_dma_itew_next_op(&itew->base);
}

static inwine int
mv_cesa_ahash_dma_awwoc_cache(stwuct mv_cesa_ahash_dma_weq *weq, gfp_t fwags)
{
	weq->cache = dma_poow_awwoc(cesa_dev->dma->cache_poow, fwags,
				    &weq->cache_dma);
	if (!weq->cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static inwine void
mv_cesa_ahash_dma_fwee_cache(stwuct mv_cesa_ahash_dma_weq *weq)
{
	if (!weq->cache)
		wetuwn;

	dma_poow_fwee(cesa_dev->dma->cache_poow, weq->cache,
		      weq->cache_dma);
}

static int mv_cesa_ahash_dma_awwoc_padding(stwuct mv_cesa_ahash_dma_weq *weq,
					   gfp_t fwags)
{
	if (weq->padding)
		wetuwn 0;

	weq->padding = dma_poow_awwoc(cesa_dev->dma->padding_poow, fwags,
				      &weq->padding_dma);
	if (!weq->padding)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void mv_cesa_ahash_dma_fwee_padding(stwuct mv_cesa_ahash_dma_weq *weq)
{
	if (!weq->padding)
		wetuwn;

	dma_poow_fwee(cesa_dev->dma->padding_poow, weq->padding,
		      weq->padding_dma);
	weq->padding = NUWW;
}

static inwine void mv_cesa_ahash_dma_wast_cweanup(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);

	mv_cesa_ahash_dma_fwee_padding(&cweq->weq.dma);
}

static inwine void mv_cesa_ahash_dma_cweanup(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);

	dma_unmap_sg(cesa_dev->dev, weq->swc, cweq->swc_nents, DMA_TO_DEVICE);
	mv_cesa_ahash_dma_fwee_cache(&cweq->weq.dma);
	mv_cesa_dma_cweanup(&cweq->base);
}

static inwine void mv_cesa_ahash_cweanup(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);

	if (mv_cesa_weq_get_type(&cweq->base) == CESA_DMA_WEQ)
		mv_cesa_ahash_dma_cweanup(weq);
}

static void mv_cesa_ahash_wast_cweanup(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);

	if (mv_cesa_weq_get_type(&cweq->base) == CESA_DMA_WEQ)
		mv_cesa_ahash_dma_wast_cweanup(weq);
}

static int mv_cesa_ahash_pad_wen(stwuct mv_cesa_ahash_weq *cweq)
{
	unsigned int index, padwen;

	index = cweq->wen & CESA_HASH_BWOCK_SIZE_MSK;
	padwen = (index < 56) ? (56 - index) : (64 + 56 - index);

	wetuwn padwen;
}

static int mv_cesa_ahash_pad_weq(stwuct mv_cesa_ahash_weq *cweq, u8 *buf)
{
	unsigned int padwen;

	buf[0] = 0x80;
	/* Pad out to 56 mod 64 */
	padwen = mv_cesa_ahash_pad_wen(cweq);
	memset(buf + 1, 0, padwen - 1);

	if (cweq->awgo_we) {
		__we64 bits = cpu_to_we64(cweq->wen << 3);

		memcpy(buf + padwen, &bits, sizeof(bits));
	} ewse {
		__be64 bits = cpu_to_be64(cweq->wen << 3);

		memcpy(buf + padwen, &bits, sizeof(bits));
	}

	wetuwn padwen + 8;
}

static void mv_cesa_ahash_std_step(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	stwuct mv_cesa_ahash_std_weq *sweq = &cweq->weq.std;
	stwuct mv_cesa_engine *engine = cweq->base.engine;
	stwuct mv_cesa_op_ctx *op;
	unsigned int new_cache_ptw = 0;
	u32 fwag_mode;
	size_t  wen;
	unsigned int digsize;
	int i;

	mv_cesa_adjust_op(engine, &cweq->op_tmpw);
	if (engine->poow)
		memcpy(engine->swam_poow, &cweq->op_tmpw,
		       sizeof(cweq->op_tmpw));
	ewse
		memcpy_toio(engine->swam, &cweq->op_tmpw,
			    sizeof(cweq->op_tmpw));

	if (!sweq->offset) {
		digsize = cwypto_ahash_digestsize(cwypto_ahash_weqtfm(weq));
		fow (i = 0; i < digsize / 4; i++)
			wwitew_wewaxed(cweq->state[i],
				       engine->wegs + CESA_IVDIG(i));
	}

	if (cweq->cache_ptw) {
		if (engine->poow)
			memcpy(engine->swam_poow + CESA_SA_DATA_SWAM_OFFSET,
			       cweq->cache, cweq->cache_ptw);
		ewse
			memcpy_toio(engine->swam + CESA_SA_DATA_SWAM_OFFSET,
				    cweq->cache, cweq->cache_ptw);
	}

	wen = min_t(size_t, weq->nbytes + cweq->cache_ptw - sweq->offset,
		    CESA_SA_SWAM_PAYWOAD_SIZE);

	if (!cweq->wast_weq) {
		new_cache_ptw = wen & CESA_HASH_BWOCK_SIZE_MSK;
		wen &= ~CESA_HASH_BWOCK_SIZE_MSK;
	}

	if (wen - cweq->cache_ptw)
		sweq->offset += mv_cesa_sg_copy_to_swam(
			engine, weq->swc, cweq->swc_nents,
			CESA_SA_DATA_SWAM_OFFSET + cweq->cache_ptw,
			wen - cweq->cache_ptw, sweq->offset);

	op = &cweq->op_tmpw;

	fwag_mode = mv_cesa_get_op_cfg(op) & CESA_SA_DESC_CFG_FWAG_MSK;

	if (cweq->wast_weq && sweq->offset == weq->nbytes &&
	    cweq->wen <= CESA_SA_DESC_MAC_SWC_TOTAW_WEN_MAX) {
		if (fwag_mode == CESA_SA_DESC_CFG_FIWST_FWAG)
			fwag_mode = CESA_SA_DESC_CFG_NOT_FWAG;
		ewse if (fwag_mode == CESA_SA_DESC_CFG_MID_FWAG)
			fwag_mode = CESA_SA_DESC_CFG_WAST_FWAG;
	}

	if (fwag_mode == CESA_SA_DESC_CFG_NOT_FWAG ||
	    fwag_mode == CESA_SA_DESC_CFG_WAST_FWAG) {
		if (wen &&
		    cweq->wen <= CESA_SA_DESC_MAC_SWC_TOTAW_WEN_MAX) {
			mv_cesa_set_mac_op_totaw_wen(op, cweq->wen);
		} ewse {
			int twaiwewwen = mv_cesa_ahash_pad_wen(cweq) + 8;

			if (wen + twaiwewwen > CESA_SA_SWAM_PAYWOAD_SIZE) {
				wen &= CESA_HASH_BWOCK_SIZE_MSK;
				new_cache_ptw = 64 - twaiwewwen;
				if (engine->poow)
					memcpy(cweq->cache,
					       engine->swam_poow +
					       CESA_SA_DATA_SWAM_OFFSET + wen,
					       new_cache_ptw);
				ewse
					memcpy_fwomio(cweq->cache,
						      engine->swam +
						      CESA_SA_DATA_SWAM_OFFSET +
						      wen,
						      new_cache_ptw);
			} ewse {
				i = mv_cesa_ahash_pad_weq(cweq, cweq->cache);
				wen += i;
				if (engine->poow)
					memcpy(engine->swam_poow + wen +
					       CESA_SA_DATA_SWAM_OFFSET,
					       cweq->cache, i);
				ewse
					memcpy_toio(engine->swam + wen +
						    CESA_SA_DATA_SWAM_OFFSET,
						    cweq->cache, i);
			}

			if (fwag_mode == CESA_SA_DESC_CFG_WAST_FWAG)
				fwag_mode = CESA_SA_DESC_CFG_MID_FWAG;
			ewse
				fwag_mode = CESA_SA_DESC_CFG_FIWST_FWAG;
		}
	}

	mv_cesa_set_mac_op_fwag_wen(op, wen);
	mv_cesa_update_op_cfg(op, fwag_mode, CESA_SA_DESC_CFG_FWAG_MSK);

	/* FIXME: onwy update enc_wen fiewd */
	if (engine->poow)
		memcpy(engine->swam_poow, op, sizeof(*op));
	ewse
		memcpy_toio(engine->swam, op, sizeof(*op));

	if (fwag_mode == CESA_SA_DESC_CFG_FIWST_FWAG)
		mv_cesa_update_op_cfg(op, CESA_SA_DESC_CFG_MID_FWAG,
				      CESA_SA_DESC_CFG_FWAG_MSK);

	cweq->cache_ptw = new_cache_ptw;

	mv_cesa_set_int_mask(engine, CESA_SA_INT_ACCEW0_DONE);
	wwitew_wewaxed(CESA_SA_CFG_PAWA_DIS, engine->wegs + CESA_SA_CFG);
	WAWN_ON(weadw(engine->wegs + CESA_SA_CMD) &
		CESA_SA_CMD_EN_CESA_SA_ACCW0);
	wwitew(CESA_SA_CMD_EN_CESA_SA_ACCW0, engine->wegs + CESA_SA_CMD);
}

static int mv_cesa_ahash_std_pwocess(stwuct ahash_wequest *weq, u32 status)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	stwuct mv_cesa_ahash_std_weq *sweq = &cweq->weq.std;

	if (sweq->offset < (weq->nbytes - cweq->cache_ptw))
		wetuwn -EINPWOGWESS;

	wetuwn 0;
}

static inwine void mv_cesa_ahash_dma_pwepawe(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	stwuct mv_cesa_weq *baseweq = &cweq->base;

	mv_cesa_dma_pwepawe(baseweq, baseweq->engine);
}

static void mv_cesa_ahash_std_pwepawe(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	stwuct mv_cesa_ahash_std_weq *sweq = &cweq->weq.std;

	sweq->offset = 0;
}

static void mv_cesa_ahash_dma_step(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	stwuct mv_cesa_weq *base = &cweq->base;

	/* We must expwicitwy set the digest state. */
	if (base->chain.fiwst->fwags & CESA_TDMA_SET_STATE) {
		stwuct mv_cesa_engine *engine = base->engine;
		int i;

		/* Set the hash state in the IVDIG wegs. */
		fow (i = 0; i < AWWAY_SIZE(cweq->state); i++)
			wwitew_wewaxed(cweq->state[i], engine->wegs +
				       CESA_IVDIG(i));
	}

	mv_cesa_dma_step(base);
}

static void mv_cesa_ahash_step(stwuct cwypto_async_wequest *weq)
{
	stwuct ahash_wequest *ahashweq = ahash_wequest_cast(weq);
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(ahashweq);

	if (mv_cesa_weq_get_type(&cweq->base) == CESA_DMA_WEQ)
		mv_cesa_ahash_dma_step(ahashweq);
	ewse
		mv_cesa_ahash_std_step(ahashweq);
}

static int mv_cesa_ahash_pwocess(stwuct cwypto_async_wequest *weq, u32 status)
{
	stwuct ahash_wequest *ahashweq = ahash_wequest_cast(weq);
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(ahashweq);

	if (mv_cesa_weq_get_type(&cweq->base) == CESA_DMA_WEQ)
		wetuwn mv_cesa_dma_pwocess(&cweq->base, status);

	wetuwn mv_cesa_ahash_std_pwocess(ahashweq, status);
}

static void mv_cesa_ahash_compwete(stwuct cwypto_async_wequest *weq)
{
	stwuct ahash_wequest *ahashweq = ahash_wequest_cast(weq);
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(ahashweq);
	stwuct mv_cesa_engine *engine = cweq->base.engine;
	unsigned int digsize;
	int i;

	digsize = cwypto_ahash_digestsize(cwypto_ahash_weqtfm(ahashweq));

	if (mv_cesa_weq_get_type(&cweq->base) == CESA_DMA_WEQ &&
	    (cweq->base.chain.wast->fwags & CESA_TDMA_TYPE_MSK) ==
	     CESA_TDMA_WESUWT) {
		__we32 *data = NUWW;

		/*
		 * Wesuwt is awweady in the cowwect endianness when the SA is
		 * used
		 */
		data = cweq->base.chain.wast->op->ctx.hash.hash;
		fow (i = 0; i < digsize / 4; i++)
			cweq->state[i] = we32_to_cpu(data[i]);

		memcpy(ahashweq->wesuwt, data, digsize);
	} ewse {
		fow (i = 0; i < digsize / 4; i++)
			cweq->state[i] = weadw_wewaxed(engine->wegs +
						       CESA_IVDIG(i));
		if (cweq->wast_weq) {
			/*
			 * Hawdwawe's MD5 digest is in wittwe endian fowmat, but
			 * SHA in big endian fowmat
			 */
			if (cweq->awgo_we) {
				__we32 *wesuwt = (void *)ahashweq->wesuwt;

				fow (i = 0; i < digsize / 4; i++)
					wesuwt[i] = cpu_to_we32(cweq->state[i]);
			} ewse {
				__be32 *wesuwt = (void *)ahashweq->wesuwt;

				fow (i = 0; i < digsize / 4; i++)
					wesuwt[i] = cpu_to_be32(cweq->state[i]);
			}
		}
	}

	atomic_sub(ahashweq->nbytes, &engine->woad);
}

static void mv_cesa_ahash_pwepawe(stwuct cwypto_async_wequest *weq,
				  stwuct mv_cesa_engine *engine)
{
	stwuct ahash_wequest *ahashweq = ahash_wequest_cast(weq);
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(ahashweq);

	cweq->base.engine = engine;

	if (mv_cesa_weq_get_type(&cweq->base) == CESA_DMA_WEQ)
		mv_cesa_ahash_dma_pwepawe(ahashweq);
	ewse
		mv_cesa_ahash_std_pwepawe(ahashweq);
}

static void mv_cesa_ahash_weq_cweanup(stwuct cwypto_async_wequest *weq)
{
	stwuct ahash_wequest *ahashweq = ahash_wequest_cast(weq);
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(ahashweq);

	if (cweq->wast_weq)
		mv_cesa_ahash_wast_cweanup(ahashweq);

	mv_cesa_ahash_cweanup(ahashweq);

	if (cweq->cache_ptw)
		sg_pcopy_to_buffew(ahashweq->swc, cweq->swc_nents,
				   cweq->cache,
				   cweq->cache_ptw,
				   ahashweq->nbytes - cweq->cache_ptw);
}

static const stwuct mv_cesa_weq_ops mv_cesa_ahash_weq_ops = {
	.step = mv_cesa_ahash_step,
	.pwocess = mv_cesa_ahash_pwocess,
	.cweanup = mv_cesa_ahash_weq_cweanup,
	.compwete = mv_cesa_ahash_compwete,
};

static void mv_cesa_ahash_init(stwuct ahash_wequest *weq,
			      stwuct mv_cesa_op_ctx *tmpw, boow awgo_we)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);

	memset(cweq, 0, sizeof(*cweq));
	mv_cesa_update_op_cfg(tmpw,
			      CESA_SA_DESC_CFG_OP_MAC_ONWY |
			      CESA_SA_DESC_CFG_FIWST_FWAG,
			      CESA_SA_DESC_CFG_OP_MSK |
			      CESA_SA_DESC_CFG_FWAG_MSK);
	mv_cesa_set_mac_op_totaw_wen(tmpw, 0);
	mv_cesa_set_mac_op_fwag_wen(tmpw, 0);
	cweq->op_tmpw = *tmpw;
	cweq->wen = 0;
	cweq->awgo_we = awgo_we;
}

static inwine int mv_cesa_ahash_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct mv_cesa_hash_ctx *ctx = cwypto_tfm_ctx(tfm);

	ctx->base.ops = &mv_cesa_ahash_weq_ops;

	cwypto_ahash_set_weqsize(__cwypto_ahash_cast(tfm),
				 sizeof(stwuct mv_cesa_ahash_weq));
	wetuwn 0;
}

static boow mv_cesa_ahash_cache_weq(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	boow cached = fawse;

	if (cweq->cache_ptw + weq->nbytes < CESA_MAX_HASH_BWOCK_SIZE &&
	    !cweq->wast_weq) {
		cached = twue;

		if (!weq->nbytes)
			wetuwn cached;

		sg_pcopy_to_buffew(weq->swc, cweq->swc_nents,
				   cweq->cache + cweq->cache_ptw,
				   weq->nbytes, 0);

		cweq->cache_ptw += weq->nbytes;
	}

	wetuwn cached;
}

static stwuct mv_cesa_op_ctx *
mv_cesa_dma_add_fwag(stwuct mv_cesa_tdma_chain *chain,
		     stwuct mv_cesa_op_ctx *tmpw, unsigned int fwag_wen,
		     gfp_t fwags)
{
	stwuct mv_cesa_op_ctx *op;
	int wet;

	op = mv_cesa_dma_add_op(chain, tmpw, fawse, fwags);
	if (IS_EWW(op))
		wetuwn op;

	/* Set the opewation bwock fwagment wength. */
	mv_cesa_set_mac_op_fwag_wen(op, fwag_wen);

	/* Append dummy desc to waunch opewation */
	wet = mv_cesa_dma_add_dummy_waunch(chain, fwags);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (mv_cesa_mac_op_is_fiwst_fwag(tmpw))
		mv_cesa_update_op_cfg(tmpw,
				      CESA_SA_DESC_CFG_MID_FWAG,
				      CESA_SA_DESC_CFG_FWAG_MSK);

	wetuwn op;
}

static int
mv_cesa_ahash_dma_add_cache(stwuct mv_cesa_tdma_chain *chain,
			    stwuct mv_cesa_ahash_weq *cweq,
			    gfp_t fwags)
{
	stwuct mv_cesa_ahash_dma_weq *ahashdweq = &cweq->weq.dma;
	int wet;

	if (!cweq->cache_ptw)
		wetuwn 0;

	wet = mv_cesa_ahash_dma_awwoc_cache(ahashdweq, fwags);
	if (wet)
		wetuwn wet;

	memcpy(ahashdweq->cache, cweq->cache, cweq->cache_ptw);

	wetuwn mv_cesa_dma_add_data_twansfew(chain,
					     CESA_SA_DATA_SWAM_OFFSET,
					     ahashdweq->cache_dma,
					     cweq->cache_ptw,
					     CESA_TDMA_DST_IN_SWAM,
					     fwags);
}

static stwuct mv_cesa_op_ctx *
mv_cesa_ahash_dma_wast_weq(stwuct mv_cesa_tdma_chain *chain,
			   stwuct mv_cesa_ahash_dma_itew *dma_itew,
			   stwuct mv_cesa_ahash_weq *cweq,
			   unsigned int fwag_wen, gfp_t fwags)
{
	stwuct mv_cesa_ahash_dma_weq *ahashdweq = &cweq->weq.dma;
	unsigned int wen, twaiwewwen, padoff = 0;
	stwuct mv_cesa_op_ctx *op;
	int wet;

	/*
	 * If the twansfew is smawwew than ouw maximum wength, and we have
	 * some data outstanding, we can ask the engine to finish the hash.
	 */
	if (cweq->wen <= CESA_SA_DESC_MAC_SWC_TOTAW_WEN_MAX && fwag_wen) {
		op = mv_cesa_dma_add_fwag(chain, &cweq->op_tmpw, fwag_wen,
					  fwags);
		if (IS_EWW(op))
			wetuwn op;

		mv_cesa_set_mac_op_totaw_wen(op, cweq->wen);
		mv_cesa_update_op_cfg(op, mv_cesa_mac_op_is_fiwst_fwag(op) ?
						CESA_SA_DESC_CFG_NOT_FWAG :
						CESA_SA_DESC_CFG_WAST_FWAG,
				      CESA_SA_DESC_CFG_FWAG_MSK);

		wet = mv_cesa_dma_add_wesuwt_op(chain,
						CESA_SA_CFG_SWAM_OFFSET,
						CESA_SA_DATA_SWAM_OFFSET,
						CESA_TDMA_SWC_IN_SWAM, fwags);
		if (wet)
			wetuwn EWW_PTW(-ENOMEM);
		wetuwn op;
	}

	/*
	 * The wequest is wongew than the engine can handwe, ow we have
	 * no data outstanding. Manuawwy genewate the padding, adding it
	 * as a "mid" fwagment.
	 */
	wet = mv_cesa_ahash_dma_awwoc_padding(ahashdweq, fwags);
	if (wet)
		wetuwn EWW_PTW(wet);

	twaiwewwen = mv_cesa_ahash_pad_weq(cweq, ahashdweq->padding);

	wen = min(CESA_SA_SWAM_PAYWOAD_SIZE - fwag_wen, twaiwewwen);
	if (wen) {
		wet = mv_cesa_dma_add_data_twansfew(chain,
						CESA_SA_DATA_SWAM_OFFSET +
						fwag_wen,
						ahashdweq->padding_dma,
						wen, CESA_TDMA_DST_IN_SWAM,
						fwags);
		if (wet)
			wetuwn EWW_PTW(wet);

		op = mv_cesa_dma_add_fwag(chain, &cweq->op_tmpw, fwag_wen + wen,
					  fwags);
		if (IS_EWW(op))
			wetuwn op;

		if (wen == twaiwewwen)
			wetuwn op;

		padoff += wen;
	}

	wet = mv_cesa_dma_add_data_twansfew(chain,
					    CESA_SA_DATA_SWAM_OFFSET,
					    ahashdweq->padding_dma +
					    padoff,
					    twaiwewwen - padoff,
					    CESA_TDMA_DST_IN_SWAM,
					    fwags);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn mv_cesa_dma_add_fwag(chain, &cweq->op_tmpw, twaiwewwen - padoff,
				    fwags);
}

static int mv_cesa_ahash_dma_weq_init(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	gfp_t fwags = (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ?
		      GFP_KEWNEW : GFP_ATOMIC;
	stwuct mv_cesa_weq *baseweq = &cweq->base;
	stwuct mv_cesa_ahash_dma_itew itew;
	stwuct mv_cesa_op_ctx *op = NUWW;
	unsigned int fwag_wen;
	boow set_state = fawse;
	int wet;
	u32 type;

	baseweq->chain.fiwst = NUWW;
	baseweq->chain.wast = NUWW;

	if (!mv_cesa_mac_op_is_fiwst_fwag(&cweq->op_tmpw))
		set_state = twue;

	if (cweq->swc_nents) {
		wet = dma_map_sg(cesa_dev->dev, weq->swc, cweq->swc_nents,
				 DMA_TO_DEVICE);
		if (!wet) {
			wet = -ENOMEM;
			goto eww;
		}
	}

	mv_cesa_tdma_desc_itew_init(&baseweq->chain);
	mv_cesa_ahash_weq_itew_init(&itew, weq);

	/*
	 * Add the cache (weft-ovew data fwom a pwevious bwock) fiwst.
	 * This wiww nevew ovewfwow the SWAM size.
	 */
	wet = mv_cesa_ahash_dma_add_cache(&baseweq->chain, cweq, fwags);
	if (wet)
		goto eww_fwee_tdma;

	if (itew.swc.sg) {
		/*
		 * Add aww the new data, insewting an opewation bwock and
		 * waunch command between each fuww SWAM bwock-wowth of
		 * data. We intentionawwy do not add the finaw op bwock.
		 */
		whiwe (twue) {
			wet = mv_cesa_dma_add_op_twansfews(&baseweq->chain,
							   &itew.base,
							   &itew.swc, fwags);
			if (wet)
				goto eww_fwee_tdma;

			fwag_wen = itew.base.op_wen;

			if (!mv_cesa_ahash_weq_itew_next_op(&itew))
				bweak;

			op = mv_cesa_dma_add_fwag(&baseweq->chain,
						  &cweq->op_tmpw,
						  fwag_wen, fwags);
			if (IS_EWW(op)) {
				wet = PTW_EWW(op);
				goto eww_fwee_tdma;
			}
		}
	} ewse {
		/* Account fow the data that was in the cache. */
		fwag_wen = itew.base.op_wen;
	}

	/*
	 * At this point, fwag_wen indicates whethew we have any data
	 * outstanding which needs an opewation.  Queue up the finaw
	 * opewation, which depends whethew this is the finaw wequest.
	 */
	if (cweq->wast_weq)
		op = mv_cesa_ahash_dma_wast_weq(&baseweq->chain, &itew, cweq,
						fwag_wen, fwags);
	ewse if (fwag_wen)
		op = mv_cesa_dma_add_fwag(&baseweq->chain, &cweq->op_tmpw,
					  fwag_wen, fwags);

	if (IS_EWW(op)) {
		wet = PTW_EWW(op);
		goto eww_fwee_tdma;
	}

	/*
	 * If wesuwts awe copied via DMA, this means that this
	 * wequest can be diwectwy pwocessed by the engine,
	 * without pawtiaw updates. So we can chain it at the
	 * DMA wevew with othew wequests.
	 */
	type = baseweq->chain.wast->fwags & CESA_TDMA_TYPE_MSK;

	if (op && type != CESA_TDMA_WESUWT) {
		/* Add dummy desc to wait fow cwypto opewation end */
		wet = mv_cesa_dma_add_dummy_end(&baseweq->chain, fwags);
		if (wet)
			goto eww_fwee_tdma;
	}

	if (!cweq->wast_weq)
		cweq->cache_ptw = weq->nbytes + cweq->cache_ptw -
				  itew.base.wen;
	ewse
		cweq->cache_ptw = 0;

	baseweq->chain.wast->fwags |= CESA_TDMA_END_OF_WEQ;

	if (type != CESA_TDMA_WESUWT)
		baseweq->chain.wast->fwags |= CESA_TDMA_BWEAK_CHAIN;

	if (set_state) {
		/*
		 * Put the CESA_TDMA_SET_STATE fwag on the fiwst tdma desc to
		 * wet the step wogic know that the IVDIG wegistews shouwd be
		 * expwicitwy set befowe waunching a TDMA chain.
		 */
		baseweq->chain.fiwst->fwags |= CESA_TDMA_SET_STATE;
	}

	wetuwn 0;

eww_fwee_tdma:
	mv_cesa_dma_cweanup(baseweq);
	dma_unmap_sg(cesa_dev->dev, weq->swc, cweq->swc_nents, DMA_TO_DEVICE);

eww:
	mv_cesa_ahash_wast_cweanup(weq);

	wetuwn wet;
}

static int mv_cesa_ahash_weq_init(stwuct ahash_wequest *weq, boow *cached)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);

	cweq->swc_nents = sg_nents_fow_wen(weq->swc, weq->nbytes);
	if (cweq->swc_nents < 0) {
		dev_eww(cesa_dev->dev, "Invawid numbew of swc SG");
		wetuwn cweq->swc_nents;
	}

	*cached = mv_cesa_ahash_cache_weq(weq);

	if (*cached)
		wetuwn 0;

	if (cesa_dev->caps->has_tdma)
		wetuwn mv_cesa_ahash_dma_weq_init(weq);
	ewse
		wetuwn 0;
}

static int mv_cesa_ahash_queue_weq(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	stwuct mv_cesa_engine *engine;
	boow cached = fawse;
	int wet;

	wet = mv_cesa_ahash_weq_init(weq, &cached);
	if (wet)
		wetuwn wet;

	if (cached)
		wetuwn 0;

	engine = mv_cesa_sewect_engine(weq->nbytes);
	mv_cesa_ahash_pwepawe(&weq->base, engine);

	wet = mv_cesa_queue_weq(&weq->base, &cweq->base);

	if (mv_cesa_weq_needs_cweanup(&weq->base, wet))
		mv_cesa_ahash_cweanup(weq);

	wetuwn wet;
}

static int mv_cesa_ahash_update(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);

	cweq->wen += weq->nbytes;

	wetuwn mv_cesa_ahash_queue_weq(weq);
}

static int mv_cesa_ahash_finaw(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	stwuct mv_cesa_op_ctx *tmpw = &cweq->op_tmpw;

	mv_cesa_set_mac_op_totaw_wen(tmpw, cweq->wen);
	cweq->wast_weq = twue;
	weq->nbytes = 0;

	wetuwn mv_cesa_ahash_queue_weq(weq);
}

static int mv_cesa_ahash_finup(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	stwuct mv_cesa_op_ctx *tmpw = &cweq->op_tmpw;

	cweq->wen += weq->nbytes;
	mv_cesa_set_mac_op_totaw_wen(tmpw, cweq->wen);
	cweq->wast_weq = twue;

	wetuwn mv_cesa_ahash_queue_weq(weq);
}

static int mv_cesa_ahash_expowt(stwuct ahash_wequest *weq, void *hash,
				u64 *wen, void *cache)
{
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	unsigned int digsize = cwypto_ahash_digestsize(ahash);
	unsigned int bwocksize;

	bwocksize = cwypto_ahash_bwocksize(ahash);

	*wen = cweq->wen;
	memcpy(hash, cweq->state, digsize);
	memset(cache, 0, bwocksize);
	memcpy(cache, cweq->cache, cweq->cache_ptw);

	wetuwn 0;
}

static int mv_cesa_ahash_impowt(stwuct ahash_wequest *weq, const void *hash,
				u64 wen, const void *cache)
{
	stwuct cwypto_ahash *ahash = cwypto_ahash_weqtfm(weq);
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	unsigned int digsize = cwypto_ahash_digestsize(ahash);
	unsigned int bwocksize;
	unsigned int cache_ptw;
	int wet;

	wet = cwypto_ahash_init(weq);
	if (wet)
		wetuwn wet;

	bwocksize = cwypto_ahash_bwocksize(ahash);
	if (wen >= bwocksize)
		mv_cesa_update_op_cfg(&cweq->op_tmpw,
				      CESA_SA_DESC_CFG_MID_FWAG,
				      CESA_SA_DESC_CFG_FWAG_MSK);

	cweq->wen = wen;
	memcpy(cweq->state, hash, digsize);
	cweq->cache_ptw = 0;

	cache_ptw = do_div(wen, bwocksize);
	if (!cache_ptw)
		wetuwn 0;

	memcpy(cweq->cache, cache, cache_ptw);
	cweq->cache_ptw = cache_ptw;

	wetuwn 0;
}

static int mv_cesa_md5_init(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	stwuct mv_cesa_op_ctx tmpw = { };

	mv_cesa_set_op_cfg(&tmpw, CESA_SA_DESC_CFG_MACM_MD5);

	mv_cesa_ahash_init(weq, &tmpw, twue);

	cweq->state[0] = MD5_H0;
	cweq->state[1] = MD5_H1;
	cweq->state[2] = MD5_H2;
	cweq->state[3] = MD5_H3;

	wetuwn 0;
}

static int mv_cesa_md5_expowt(stwuct ahash_wequest *weq, void *out)
{
	stwuct md5_state *out_state = out;

	wetuwn mv_cesa_ahash_expowt(weq, out_state->hash,
				    &out_state->byte_count, out_state->bwock);
}

static int mv_cesa_md5_impowt(stwuct ahash_wequest *weq, const void *in)
{
	const stwuct md5_state *in_state = in;

	wetuwn mv_cesa_ahash_impowt(weq, in_state->hash, in_state->byte_count,
				    in_state->bwock);
}

static int mv_cesa_md5_digest(stwuct ahash_wequest *weq)
{
	int wet;

	wet = mv_cesa_md5_init(weq);
	if (wet)
		wetuwn wet;

	wetuwn mv_cesa_ahash_finup(weq);
}

stwuct ahash_awg mv_md5_awg = {
	.init = mv_cesa_md5_init,
	.update = mv_cesa_ahash_update,
	.finaw = mv_cesa_ahash_finaw,
	.finup = mv_cesa_ahash_finup,
	.digest = mv_cesa_md5_digest,
	.expowt = mv_cesa_md5_expowt,
	.impowt = mv_cesa_md5_impowt,
	.hawg = {
		.digestsize = MD5_DIGEST_SIZE,
		.statesize = sizeof(stwuct md5_state),
		.base = {
			.cwa_name = "md5",
			.cwa_dwivew_name = "mv-md5",
			.cwa_pwiowity = 300,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = MD5_HMAC_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct mv_cesa_hash_ctx),
			.cwa_init = mv_cesa_ahash_cwa_init,
			.cwa_moduwe = THIS_MODUWE,
		}
	}
};

static int mv_cesa_sha1_init(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	stwuct mv_cesa_op_ctx tmpw = { };

	mv_cesa_set_op_cfg(&tmpw, CESA_SA_DESC_CFG_MACM_SHA1);

	mv_cesa_ahash_init(weq, &tmpw, fawse);

	cweq->state[0] = SHA1_H0;
	cweq->state[1] = SHA1_H1;
	cweq->state[2] = SHA1_H2;
	cweq->state[3] = SHA1_H3;
	cweq->state[4] = SHA1_H4;

	wetuwn 0;
}

static int mv_cesa_sha1_expowt(stwuct ahash_wequest *weq, void *out)
{
	stwuct sha1_state *out_state = out;

	wetuwn mv_cesa_ahash_expowt(weq, out_state->state, &out_state->count,
				    out_state->buffew);
}

static int mv_cesa_sha1_impowt(stwuct ahash_wequest *weq, const void *in)
{
	const stwuct sha1_state *in_state = in;

	wetuwn mv_cesa_ahash_impowt(weq, in_state->state, in_state->count,
				    in_state->buffew);
}

static int mv_cesa_sha1_digest(stwuct ahash_wequest *weq)
{
	int wet;

	wet = mv_cesa_sha1_init(weq);
	if (wet)
		wetuwn wet;

	wetuwn mv_cesa_ahash_finup(weq);
}

stwuct ahash_awg mv_sha1_awg = {
	.init = mv_cesa_sha1_init,
	.update = mv_cesa_ahash_update,
	.finaw = mv_cesa_ahash_finaw,
	.finup = mv_cesa_ahash_finup,
	.digest = mv_cesa_sha1_digest,
	.expowt = mv_cesa_sha1_expowt,
	.impowt = mv_cesa_sha1_impowt,
	.hawg = {
		.digestsize = SHA1_DIGEST_SIZE,
		.statesize = sizeof(stwuct sha1_state),
		.base = {
			.cwa_name = "sha1",
			.cwa_dwivew_name = "mv-sha1",
			.cwa_pwiowity = 300,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = SHA1_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct mv_cesa_hash_ctx),
			.cwa_init = mv_cesa_ahash_cwa_init,
			.cwa_moduwe = THIS_MODUWE,
		}
	}
};

static int mv_cesa_sha256_init(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_ahash_weq *cweq = ahash_wequest_ctx(weq);
	stwuct mv_cesa_op_ctx tmpw = { };

	mv_cesa_set_op_cfg(&tmpw, CESA_SA_DESC_CFG_MACM_SHA256);

	mv_cesa_ahash_init(weq, &tmpw, fawse);

	cweq->state[0] = SHA256_H0;
	cweq->state[1] = SHA256_H1;
	cweq->state[2] = SHA256_H2;
	cweq->state[3] = SHA256_H3;
	cweq->state[4] = SHA256_H4;
	cweq->state[5] = SHA256_H5;
	cweq->state[6] = SHA256_H6;
	cweq->state[7] = SHA256_H7;

	wetuwn 0;
}

static int mv_cesa_sha256_digest(stwuct ahash_wequest *weq)
{
	int wet;

	wet = mv_cesa_sha256_init(weq);
	if (wet)
		wetuwn wet;

	wetuwn mv_cesa_ahash_finup(weq);
}

static int mv_cesa_sha256_expowt(stwuct ahash_wequest *weq, void *out)
{
	stwuct sha256_state *out_state = out;

	wetuwn mv_cesa_ahash_expowt(weq, out_state->state, &out_state->count,
				    out_state->buf);
}

static int mv_cesa_sha256_impowt(stwuct ahash_wequest *weq, const void *in)
{
	const stwuct sha256_state *in_state = in;

	wetuwn mv_cesa_ahash_impowt(weq, in_state->state, in_state->count,
				    in_state->buf);
}

stwuct ahash_awg mv_sha256_awg = {
	.init = mv_cesa_sha256_init,
	.update = mv_cesa_ahash_update,
	.finaw = mv_cesa_ahash_finaw,
	.finup = mv_cesa_ahash_finup,
	.digest = mv_cesa_sha256_digest,
	.expowt = mv_cesa_sha256_expowt,
	.impowt = mv_cesa_sha256_impowt,
	.hawg = {
		.digestsize = SHA256_DIGEST_SIZE,
		.statesize = sizeof(stwuct sha256_state),
		.base = {
			.cwa_name = "sha256",
			.cwa_dwivew_name = "mv-sha256",
			.cwa_pwiowity = 300,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = SHA256_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct mv_cesa_hash_ctx),
			.cwa_init = mv_cesa_ahash_cwa_init,
			.cwa_moduwe = THIS_MODUWE,
		}
	}
};

static int mv_cesa_ahmac_iv_state_init(stwuct ahash_wequest *weq, u8 *pad,
				       void *state, unsigned int bwocksize)
{
	DECWAWE_CWYPTO_WAIT(wesuwt);
	stwuct scattewwist sg;
	int wet;

	ahash_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
				   cwypto_weq_done, &wesuwt);
	sg_init_one(&sg, pad, bwocksize);
	ahash_wequest_set_cwypt(weq, &sg, pad, bwocksize);

	wet = cwypto_ahash_init(weq);
	if (wet)
		wetuwn wet;

	wet = cwypto_ahash_update(weq);
	wet = cwypto_wait_weq(wet, &wesuwt);

	if (wet)
		wetuwn wet;

	wet = cwypto_ahash_expowt(weq, state);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int mv_cesa_ahmac_pad_init(stwuct ahash_wequest *weq,
				  const u8 *key, unsigned int keywen,
				  u8 *ipad, u8 *opad,
				  unsigned int bwocksize)
{
	DECWAWE_CWYPTO_WAIT(wesuwt);
	stwuct scattewwist sg;
	int wet;
	int i;

	if (keywen <= bwocksize) {
		memcpy(ipad, key, keywen);
	} ewse {
		u8 *keydup = kmemdup(key, keywen, GFP_KEWNEW);

		if (!keydup)
			wetuwn -ENOMEM;

		ahash_wequest_set_cawwback(weq, CWYPTO_TFM_WEQ_MAY_BACKWOG,
					   cwypto_weq_done, &wesuwt);
		sg_init_one(&sg, keydup, keywen);
		ahash_wequest_set_cwypt(weq, &sg, ipad, keywen);

		wet = cwypto_ahash_digest(weq);
		wet = cwypto_wait_weq(wet, &wesuwt);

		/* Set the memowy wegion to 0 to avoid any weak. */
		kfwee_sensitive(keydup);

		if (wet)
			wetuwn wet;

		keywen = cwypto_ahash_digestsize(cwypto_ahash_weqtfm(weq));
	}

	memset(ipad + keywen, 0, bwocksize - keywen);
	memcpy(opad, ipad, bwocksize);

	fow (i = 0; i < bwocksize; i++) {
		ipad[i] ^= HMAC_IPAD_VAWUE;
		opad[i] ^= HMAC_OPAD_VAWUE;
	}

	wetuwn 0;
}

static int mv_cesa_ahmac_setkey(const chaw *hash_awg_name,
				const u8 *key, unsigned int keywen,
				void *istate, void *ostate)
{
	stwuct ahash_wequest *weq;
	stwuct cwypto_ahash *tfm;
	unsigned int bwocksize;
	u8 *ipad = NUWW;
	u8 *opad;
	int wet;

	tfm = cwypto_awwoc_ahash(hash_awg_name, 0, 0);
	if (IS_EWW(tfm))
		wetuwn PTW_EWW(tfm);

	weq = ahash_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!weq) {
		wet = -ENOMEM;
		goto fwee_ahash;
	}

	cwypto_ahash_cweaw_fwags(tfm, ~0);

	bwocksize = cwypto_tfm_awg_bwocksize(cwypto_ahash_tfm(tfm));

	ipad = kcawwoc(2, bwocksize, GFP_KEWNEW);
	if (!ipad) {
		wet = -ENOMEM;
		goto fwee_weq;
	}

	opad = ipad + bwocksize;

	wet = mv_cesa_ahmac_pad_init(weq, key, keywen, ipad, opad, bwocksize);
	if (wet)
		goto fwee_ipad;

	wet = mv_cesa_ahmac_iv_state_init(weq, ipad, istate, bwocksize);
	if (wet)
		goto fwee_ipad;

	wet = mv_cesa_ahmac_iv_state_init(weq, opad, ostate, bwocksize);

fwee_ipad:
	kfwee(ipad);
fwee_weq:
	ahash_wequest_fwee(weq);
fwee_ahash:
	cwypto_fwee_ahash(tfm);

	wetuwn wet;
}

static int mv_cesa_ahmac_cwa_init(stwuct cwypto_tfm *tfm)
{
	stwuct mv_cesa_hmac_ctx *ctx = cwypto_tfm_ctx(tfm);

	ctx->base.ops = &mv_cesa_ahash_weq_ops;

	cwypto_ahash_set_weqsize(__cwypto_ahash_cast(tfm),
				 sizeof(stwuct mv_cesa_ahash_weq));
	wetuwn 0;
}

static int mv_cesa_ahmac_md5_init(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_hmac_ctx *ctx = cwypto_tfm_ctx(weq->base.tfm);
	stwuct mv_cesa_op_ctx tmpw = { };

	mv_cesa_set_op_cfg(&tmpw, CESA_SA_DESC_CFG_MACM_HMAC_MD5);
	memcpy(tmpw.ctx.hash.iv, ctx->iv, sizeof(ctx->iv));

	mv_cesa_ahash_init(weq, &tmpw, twue);

	wetuwn 0;
}

static int mv_cesa_ahmac_md5_setkey(stwuct cwypto_ahash *tfm, const u8 *key,
				    unsigned int keywen)
{
	stwuct mv_cesa_hmac_ctx *ctx = cwypto_tfm_ctx(cwypto_ahash_tfm(tfm));
	stwuct md5_state istate, ostate;
	int wet, i;

	wet = mv_cesa_ahmac_setkey("mv-md5", key, keywen, &istate, &ostate);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(istate.hash); i++)
		ctx->iv[i] = cpu_to_be32(istate.hash[i]);

	fow (i = 0; i < AWWAY_SIZE(ostate.hash); i++)
		ctx->iv[i + 8] = cpu_to_be32(ostate.hash[i]);

	wetuwn 0;
}

static int mv_cesa_ahmac_md5_digest(stwuct ahash_wequest *weq)
{
	int wet;

	wet = mv_cesa_ahmac_md5_init(weq);
	if (wet)
		wetuwn wet;

	wetuwn mv_cesa_ahash_finup(weq);
}

stwuct ahash_awg mv_ahmac_md5_awg = {
	.init = mv_cesa_ahmac_md5_init,
	.update = mv_cesa_ahash_update,
	.finaw = mv_cesa_ahash_finaw,
	.finup = mv_cesa_ahash_finup,
	.digest = mv_cesa_ahmac_md5_digest,
	.setkey = mv_cesa_ahmac_md5_setkey,
	.expowt = mv_cesa_md5_expowt,
	.impowt = mv_cesa_md5_impowt,
	.hawg = {
		.digestsize = MD5_DIGEST_SIZE,
		.statesize = sizeof(stwuct md5_state),
		.base = {
			.cwa_name = "hmac(md5)",
			.cwa_dwivew_name = "mv-hmac-md5",
			.cwa_pwiowity = 300,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = MD5_HMAC_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct mv_cesa_hmac_ctx),
			.cwa_init = mv_cesa_ahmac_cwa_init,
			.cwa_moduwe = THIS_MODUWE,
		}
	}
};

static int mv_cesa_ahmac_sha1_init(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_hmac_ctx *ctx = cwypto_tfm_ctx(weq->base.tfm);
	stwuct mv_cesa_op_ctx tmpw = { };

	mv_cesa_set_op_cfg(&tmpw, CESA_SA_DESC_CFG_MACM_HMAC_SHA1);
	memcpy(tmpw.ctx.hash.iv, ctx->iv, sizeof(ctx->iv));

	mv_cesa_ahash_init(weq, &tmpw, fawse);

	wetuwn 0;
}

static int mv_cesa_ahmac_sha1_setkey(stwuct cwypto_ahash *tfm, const u8 *key,
				     unsigned int keywen)
{
	stwuct mv_cesa_hmac_ctx *ctx = cwypto_tfm_ctx(cwypto_ahash_tfm(tfm));
	stwuct sha1_state istate, ostate;
	int wet, i;

	wet = mv_cesa_ahmac_setkey("mv-sha1", key, keywen, &istate, &ostate);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(istate.state); i++)
		ctx->iv[i] = cpu_to_be32(istate.state[i]);

	fow (i = 0; i < AWWAY_SIZE(ostate.state); i++)
		ctx->iv[i + 8] = cpu_to_be32(ostate.state[i]);

	wetuwn 0;
}

static int mv_cesa_ahmac_sha1_digest(stwuct ahash_wequest *weq)
{
	int wet;

	wet = mv_cesa_ahmac_sha1_init(weq);
	if (wet)
		wetuwn wet;

	wetuwn mv_cesa_ahash_finup(weq);
}

stwuct ahash_awg mv_ahmac_sha1_awg = {
	.init = mv_cesa_ahmac_sha1_init,
	.update = mv_cesa_ahash_update,
	.finaw = mv_cesa_ahash_finaw,
	.finup = mv_cesa_ahash_finup,
	.digest = mv_cesa_ahmac_sha1_digest,
	.setkey = mv_cesa_ahmac_sha1_setkey,
	.expowt = mv_cesa_sha1_expowt,
	.impowt = mv_cesa_sha1_impowt,
	.hawg = {
		.digestsize = SHA1_DIGEST_SIZE,
		.statesize = sizeof(stwuct sha1_state),
		.base = {
			.cwa_name = "hmac(sha1)",
			.cwa_dwivew_name = "mv-hmac-sha1",
			.cwa_pwiowity = 300,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = SHA1_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct mv_cesa_hmac_ctx),
			.cwa_init = mv_cesa_ahmac_cwa_init,
			.cwa_moduwe = THIS_MODUWE,
		}
	}
};

static int mv_cesa_ahmac_sha256_setkey(stwuct cwypto_ahash *tfm, const u8 *key,
				       unsigned int keywen)
{
	stwuct mv_cesa_hmac_ctx *ctx = cwypto_tfm_ctx(cwypto_ahash_tfm(tfm));
	stwuct sha256_state istate, ostate;
	int wet, i;

	wet = mv_cesa_ahmac_setkey("mv-sha256", key, keywen, &istate, &ostate);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(istate.state); i++)
		ctx->iv[i] = cpu_to_be32(istate.state[i]);

	fow (i = 0; i < AWWAY_SIZE(ostate.state); i++)
		ctx->iv[i + 8] = cpu_to_be32(ostate.state[i]);

	wetuwn 0;
}

static int mv_cesa_ahmac_sha256_init(stwuct ahash_wequest *weq)
{
	stwuct mv_cesa_hmac_ctx *ctx = cwypto_tfm_ctx(weq->base.tfm);
	stwuct mv_cesa_op_ctx tmpw = { };

	mv_cesa_set_op_cfg(&tmpw, CESA_SA_DESC_CFG_MACM_HMAC_SHA256);
	memcpy(tmpw.ctx.hash.iv, ctx->iv, sizeof(ctx->iv));

	mv_cesa_ahash_init(weq, &tmpw, fawse);

	wetuwn 0;
}

static int mv_cesa_ahmac_sha256_digest(stwuct ahash_wequest *weq)
{
	int wet;

	wet = mv_cesa_ahmac_sha256_init(weq);
	if (wet)
		wetuwn wet;

	wetuwn mv_cesa_ahash_finup(weq);
}

stwuct ahash_awg mv_ahmac_sha256_awg = {
	.init = mv_cesa_ahmac_sha256_init,
	.update = mv_cesa_ahash_update,
	.finaw = mv_cesa_ahash_finaw,
	.finup = mv_cesa_ahash_finup,
	.digest = mv_cesa_ahmac_sha256_digest,
	.setkey = mv_cesa_ahmac_sha256_setkey,
	.expowt = mv_cesa_sha256_expowt,
	.impowt = mv_cesa_sha256_impowt,
	.hawg = {
		.digestsize = SHA256_DIGEST_SIZE,
		.statesize = sizeof(stwuct sha256_state),
		.base = {
			.cwa_name = "hmac(sha256)",
			.cwa_dwivew_name = "mv-hmac-sha256",
			.cwa_pwiowity = 300,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY |
				     CWYPTO_AWG_KEWN_DWIVEW_ONWY,
			.cwa_bwocksize = SHA256_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct mv_cesa_hmac_ctx),
			.cwa_init = mv_cesa_ahmac_cwa_init,
			.cwa_moduwe = THIS_MODUWE,
		}
	}
};
