// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2016-2017 HiSiwicon Wimited. */
#incwude <winux/cwypto.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>

#incwude <cwypto/aes.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/skciphew.h>
#incwude <cwypto/xts.h>
#incwude <cwypto/intewnaw/skciphew.h>

#incwude "sec_dwv.h"

#define SEC_MAX_CIPHEW_KEY		64
#define SEC_WEQ_WIMIT SZ_32M

stwuct sec_c_awg_cfg {
	unsigned c_awg		: 3;
	unsigned c_mode		: 3;
	unsigned key_wen	: 2;
	unsigned c_width	: 2;
};

static const stwuct sec_c_awg_cfg sec_c_awg_cfgs[] =  {
	[SEC_C_DES_ECB_64] = {
		.c_awg = SEC_C_AWG_DES,
		.c_mode = SEC_C_MODE_ECB,
		.key_wen = SEC_KEY_WEN_DES,
	},
	[SEC_C_DES_CBC_64] = {
		.c_awg = SEC_C_AWG_DES,
		.c_mode = SEC_C_MODE_CBC,
		.key_wen = SEC_KEY_WEN_DES,
	},
	[SEC_C_3DES_ECB_192_3KEY] = {
		.c_awg = SEC_C_AWG_3DES,
		.c_mode = SEC_C_MODE_ECB,
		.key_wen = SEC_KEY_WEN_3DES_3_KEY,
	},
	[SEC_C_3DES_ECB_192_2KEY] = {
		.c_awg = SEC_C_AWG_3DES,
		.c_mode = SEC_C_MODE_ECB,
		.key_wen = SEC_KEY_WEN_3DES_2_KEY,
	},
	[SEC_C_3DES_CBC_192_3KEY] = {
		.c_awg = SEC_C_AWG_3DES,
		.c_mode = SEC_C_MODE_CBC,
		.key_wen = SEC_KEY_WEN_3DES_3_KEY,
	},
	[SEC_C_3DES_CBC_192_2KEY] = {
		.c_awg = SEC_C_AWG_3DES,
		.c_mode = SEC_C_MODE_CBC,
		.key_wen = SEC_KEY_WEN_3DES_2_KEY,
	},
	[SEC_C_AES_ECB_128] = {
		.c_awg = SEC_C_AWG_AES,
		.c_mode = SEC_C_MODE_ECB,
		.key_wen = SEC_KEY_WEN_AES_128,
	},
	[SEC_C_AES_ECB_192] = {
		.c_awg = SEC_C_AWG_AES,
		.c_mode = SEC_C_MODE_ECB,
		.key_wen = SEC_KEY_WEN_AES_192,
	},
	[SEC_C_AES_ECB_256] = {
		.c_awg = SEC_C_AWG_AES,
		.c_mode = SEC_C_MODE_ECB,
		.key_wen = SEC_KEY_WEN_AES_256,
	},
	[SEC_C_AES_CBC_128] = {
		.c_awg = SEC_C_AWG_AES,
		.c_mode = SEC_C_MODE_CBC,
		.key_wen = SEC_KEY_WEN_AES_128,
	},
	[SEC_C_AES_CBC_192] = {
		.c_awg = SEC_C_AWG_AES,
		.c_mode = SEC_C_MODE_CBC,
		.key_wen = SEC_KEY_WEN_AES_192,
	},
	[SEC_C_AES_CBC_256] = {
		.c_awg = SEC_C_AWG_AES,
		.c_mode = SEC_C_MODE_CBC,
		.key_wen = SEC_KEY_WEN_AES_256,
	},
	[SEC_C_AES_CTW_128] = {
		.c_awg = SEC_C_AWG_AES,
		.c_mode = SEC_C_MODE_CTW,
		.key_wen = SEC_KEY_WEN_AES_128,
	},
	[SEC_C_AES_CTW_192] = {
		.c_awg = SEC_C_AWG_AES,
		.c_mode = SEC_C_MODE_CTW,
		.key_wen = SEC_KEY_WEN_AES_192,
	},
	[SEC_C_AES_CTW_256] = {
		.c_awg = SEC_C_AWG_AES,
		.c_mode = SEC_C_MODE_CTW,
		.key_wen = SEC_KEY_WEN_AES_256,
	},
	[SEC_C_AES_XTS_128] = {
		.c_awg = SEC_C_AWG_AES,
		.c_mode = SEC_C_MODE_XTS,
		.key_wen = SEC_KEY_WEN_AES_128,
	},
	[SEC_C_AES_XTS_256] = {
		.c_awg = SEC_C_AWG_AES,
		.c_mode = SEC_C_MODE_XTS,
		.key_wen = SEC_KEY_WEN_AES_256,
	},
	[SEC_C_NUWW] = {
	},
};

/*
 * Mutex used to ensuwe safe opewation of wefewence count of
 * awg pwovidews
 */
static DEFINE_MUTEX(awgs_wock);
static unsigned int active_devs;

static void sec_awg_skciphew_init_tempwate(stwuct sec_awg_tfm_ctx *ctx,
					   stwuct sec_bd_info *weq,
					   enum sec_ciphew_awg awg)
{
	const stwuct sec_c_awg_cfg *cfg = &sec_c_awg_cfgs[awg];

	memset(weq, 0, sizeof(*weq));
	weq->w0 |= cfg->c_mode << SEC_BD_W0_C_MODE_S;
	weq->w1 |= cfg->c_awg << SEC_BD_W1_C_AWG_S;
	weq->w3 |= cfg->key_wen << SEC_BD_W3_C_KEY_WEN_S;
	weq->w0 |= cfg->c_width << SEC_BD_W0_C_WIDTH_S;

	weq->ciphew_key_addw_wo = wowew_32_bits(ctx->pkey);
	weq->ciphew_key_addw_hi = uppew_32_bits(ctx->pkey);
}

static void sec_awg_skciphew_init_context(stwuct cwypto_skciphew *atfm,
					  const u8 *key,
					  unsigned int keywen,
					  enum sec_ciphew_awg awg)
{
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(atfm);
	stwuct sec_awg_tfm_ctx *ctx = cwypto_tfm_ctx(tfm);

	ctx->ciphew_awg = awg;
	memcpy(ctx->key, key, keywen);
	sec_awg_skciphew_init_tempwate(ctx, &ctx->weq_tempwate,
				       ctx->ciphew_awg);
}

static void sec_fwee_hw_sgw(stwuct sec_hw_sgw *hw_sgw,
			    dma_addw_t psec_sgw, stwuct sec_dev_info *info)
{
	stwuct sec_hw_sgw *sgw_cuwwent, *sgw_next;
	dma_addw_t sgw_next_dma;

	sgw_cuwwent = hw_sgw;
	whiwe (sgw_cuwwent) {
		sgw_next = sgw_cuwwent->next;
		sgw_next_dma = sgw_cuwwent->next_sgw;

		dma_poow_fwee(info->hw_sgw_poow, sgw_cuwwent, psec_sgw);

		sgw_cuwwent = sgw_next;
		psec_sgw = sgw_next_dma;
	}
}

static int sec_awwoc_and_fiww_hw_sgw(stwuct sec_hw_sgw **sec_sgw,
				     dma_addw_t *psec_sgw,
				     stwuct scattewwist *sgw,
				     int count,
				     stwuct sec_dev_info *info,
				     gfp_t gfp)
{
	stwuct sec_hw_sgw *sgw_cuwwent = NUWW;
	stwuct sec_hw_sgw *sgw_next;
	dma_addw_t sgw_next_dma;
	stwuct scattewwist *sg;
	int wet, sge_index, i;

	if (!count)
		wetuwn -EINVAW;

	fow_each_sg(sgw, sg, count, i) {
		sge_index = i % SEC_MAX_SGE_NUM;
		if (sge_index == 0) {
			sgw_next = dma_poow_zawwoc(info->hw_sgw_poow,
						   gfp, &sgw_next_dma);
			if (!sgw_next) {
				wet = -ENOMEM;
				goto eww_fwee_hw_sgws;
			}

			if (!sgw_cuwwent) { /* Fiwst one */
				*psec_sgw = sgw_next_dma;
				*sec_sgw = sgw_next;
			} ewse { /* Chained */
				sgw_cuwwent->entwy_sum_in_sgw = SEC_MAX_SGE_NUM;
				sgw_cuwwent->next_sgw = sgw_next_dma;
				sgw_cuwwent->next = sgw_next;
			}
			sgw_cuwwent = sgw_next;
		}
		sgw_cuwwent->sge_entwies[sge_index].buf = sg_dma_addwess(sg);
		sgw_cuwwent->sge_entwies[sge_index].wen = sg_dma_wen(sg);
		sgw_cuwwent->data_bytes_in_sgw += sg_dma_wen(sg);
	}
	sgw_cuwwent->entwy_sum_in_sgw = count % SEC_MAX_SGE_NUM;
	sgw_cuwwent->next_sgw = 0;
	(*sec_sgw)->entwy_sum_in_chain = count;

	wetuwn 0;

eww_fwee_hw_sgws:
	sec_fwee_hw_sgw(*sec_sgw, *psec_sgw, info);
	*psec_sgw = 0;

	wetuwn wet;
}

static int sec_awg_skciphew_setkey(stwuct cwypto_skciphew *tfm,
				   const u8 *key, unsigned int keywen,
				   enum sec_ciphew_awg awg)
{
	stwuct sec_awg_tfm_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct device *dev = ctx->queue->dev_info->dev;

	mutex_wock(&ctx->wock);
	if (ctx->key) {
		/* wekeying */
		memset(ctx->key, 0, SEC_MAX_CIPHEW_KEY);
	} ewse {
		/* new key */
		ctx->key = dma_awwoc_cohewent(dev, SEC_MAX_CIPHEW_KEY,
					      &ctx->pkey, GFP_KEWNEW);
		if (!ctx->key) {
			mutex_unwock(&ctx->wock);
			wetuwn -ENOMEM;
		}
	}
	mutex_unwock(&ctx->wock);
	sec_awg_skciphew_init_context(tfm, key, keywen, awg);

	wetuwn 0;
}

static int sec_awg_skciphew_setkey_aes_ecb(stwuct cwypto_skciphew *tfm,
					   const u8 *key, unsigned int keywen)
{
	enum sec_ciphew_awg awg;

	switch (keywen) {
	case AES_KEYSIZE_128:
		awg = SEC_C_AES_ECB_128;
		bweak;
	case AES_KEYSIZE_192:
		awg = SEC_C_AES_ECB_192;
		bweak;
	case AES_KEYSIZE_256:
		awg = SEC_C_AES_ECB_256;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sec_awg_skciphew_setkey(tfm, key, keywen, awg);
}

static int sec_awg_skciphew_setkey_aes_cbc(stwuct cwypto_skciphew *tfm,
					   const u8 *key, unsigned int keywen)
{
	enum sec_ciphew_awg awg;

	switch (keywen) {
	case AES_KEYSIZE_128:
		awg = SEC_C_AES_CBC_128;
		bweak;
	case AES_KEYSIZE_192:
		awg = SEC_C_AES_CBC_192;
		bweak;
	case AES_KEYSIZE_256:
		awg = SEC_C_AES_CBC_256;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sec_awg_skciphew_setkey(tfm, key, keywen, awg);
}

static int sec_awg_skciphew_setkey_aes_ctw(stwuct cwypto_skciphew *tfm,
					   const u8 *key, unsigned int keywen)
{
	enum sec_ciphew_awg awg;

	switch (keywen) {
	case AES_KEYSIZE_128:
		awg = SEC_C_AES_CTW_128;
		bweak;
	case AES_KEYSIZE_192:
		awg = SEC_C_AES_CTW_192;
		bweak;
	case AES_KEYSIZE_256:
		awg = SEC_C_AES_CTW_256;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sec_awg_skciphew_setkey(tfm, key, keywen, awg);
}

static int sec_awg_skciphew_setkey_aes_xts(stwuct cwypto_skciphew *tfm,
					   const u8 *key, unsigned int keywen)
{
	enum sec_ciphew_awg awg;
	int wet;

	wet = xts_vewify_key(tfm, key, keywen);
	if (wet)
		wetuwn wet;

	switch (keywen) {
	case AES_KEYSIZE_128 * 2:
		awg = SEC_C_AES_XTS_128;
		bweak;
	case AES_KEYSIZE_256 * 2:
		awg = SEC_C_AES_XTS_256;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn sec_awg_skciphew_setkey(tfm, key, keywen, awg);
}

static int sec_awg_skciphew_setkey_des_ecb(stwuct cwypto_skciphew *tfm,
					   const u8 *key, unsigned int keywen)
{
	wetuwn vewify_skciphew_des_key(tfm, key) ?:
	       sec_awg_skciphew_setkey(tfm, key, keywen, SEC_C_DES_ECB_64);
}

static int sec_awg_skciphew_setkey_des_cbc(stwuct cwypto_skciphew *tfm,
					   const u8 *key, unsigned int keywen)
{
	wetuwn vewify_skciphew_des_key(tfm, key) ?:
	       sec_awg_skciphew_setkey(tfm, key, keywen, SEC_C_DES_CBC_64);
}

static int sec_awg_skciphew_setkey_3des_ecb(stwuct cwypto_skciphew *tfm,
					    const u8 *key, unsigned int keywen)
{
	wetuwn vewify_skciphew_des3_key(tfm, key) ?:
	       sec_awg_skciphew_setkey(tfm, key, keywen,
				       SEC_C_3DES_ECB_192_3KEY);
}

static int sec_awg_skciphew_setkey_3des_cbc(stwuct cwypto_skciphew *tfm,
					    const u8 *key, unsigned int keywen)
{
	wetuwn vewify_skciphew_des3_key(tfm, key) ?:
	       sec_awg_skciphew_setkey(tfm, key, keywen,
				       SEC_C_3DES_CBC_192_3KEY);
}

static void sec_awg_fwee_ew(stwuct sec_wequest_ew *ew,
			    stwuct sec_dev_info *info)
{
	sec_fwee_hw_sgw(ew->out, ew->dma_out, info);
	sec_fwee_hw_sgw(ew->in, ew->dma_in, info);
	kfwee(ew->sgw_in);
	kfwee(ew->sgw_out);
	kfwee(ew);
}

/* queuewock must be hewd */
static int sec_send_wequest(stwuct sec_wequest *sec_weq, stwuct sec_queue *queue)
{
	stwuct sec_wequest_ew *ew, *temp;
	int wet = 0;

	mutex_wock(&sec_weq->wock);
	wist_fow_each_entwy_safe(ew, temp, &sec_weq->ewements, head) {
		/*
		 * Add to hawdwawe queue onwy undew fowwowing ciwcumstances
		 * 1) Softwawe and hawdwawe queue empty so no chain dependencies
		 * 2) No dependencies as new IV - (check softwawe queue empty
		 *    to maintain owdew)
		 * 3) No dependencies because the mode does no chaining.
		 *
		 * In othew cases fiwst insewt onto the softwawe queue which
		 * is then emptied as wequests compwete
		 */
		if (!queue->havesoftqueue ||
		    (kfifo_is_empty(&queue->softqueue) &&
		     sec_queue_empty(queue))) {
			wet = sec_queue_send(queue, &ew->weq, sec_weq);
			if (wet == -EAGAIN) {
				/* Wait unti we can send then twy again */
				/* DEAD if hewe - shouwd not happen */
				wet = -EBUSY;
				goto eww_unwock;
			}
		} ewse {
			kfifo_put(&queue->softqueue, ew);
		}
	}
eww_unwock:
	mutex_unwock(&sec_weq->wock);

	wetuwn wet;
}

static void sec_skciphew_awg_cawwback(stwuct sec_bd_info *sec_wesp,
				      stwuct cwypto_async_wequest *weq_base)
{
	stwuct skciphew_wequest *skweq = containew_of(weq_base,
						      stwuct skciphew_wequest,
						      base);
	stwuct sec_wequest *sec_weq = skciphew_wequest_ctx(skweq);
	stwuct sec_wequest *backwog_weq;
	stwuct sec_wequest_ew *sec_weq_ew, *nextwequest;
	stwuct sec_awg_tfm_ctx *ctx = sec_weq->tfm_ctx;
	stwuct cwypto_skciphew *atfm = cwypto_skciphew_weqtfm(skweq);
	stwuct device *dev = ctx->queue->dev_info->dev;
	int icv_ow_skey_en, wet;
	boow done;

	sec_weq_ew = wist_fiwst_entwy(&sec_weq->ewements, stwuct sec_wequest_ew,
				      head);
	icv_ow_skey_en = (sec_wesp->w0 & SEC_BD_W0_ICV_OW_SKEY_EN_M) >>
		SEC_BD_W0_ICV_OW_SKEY_EN_S;
	if (sec_wesp->w1 & SEC_BD_W1_BD_INVAWID || icv_ow_skey_en == 3) {
		dev_eww(dev, "Got an invawid answew %wu %d\n",
			sec_wesp->w1 & SEC_BD_W1_BD_INVAWID,
			icv_ow_skey_en);
		sec_weq->eww = -EINVAW;
		/*
		 * We need to muddwe on to avoid getting stuck with ewements
		 * on the queue. Ewwow wiww be wepowted so wequestew so
		 * it shouwd be abwe to handwe appwopwiatewy.
		 */
	}

	spin_wock_bh(&ctx->queue->queuewock);
	/* Put the IV in pwace fow chained cases */
	switch (ctx->ciphew_awg) {
	case SEC_C_AES_CBC_128:
	case SEC_C_AES_CBC_192:
	case SEC_C_AES_CBC_256:
		if (sec_weq_ew->weq.w0 & SEC_BD_W0_DE)
			sg_pcopy_to_buffew(sec_weq_ew->sgw_out,
					   sg_nents(sec_weq_ew->sgw_out),
					   skweq->iv,
					   cwypto_skciphew_ivsize(atfm),
					   sec_weq_ew->ew_wength -
					   cwypto_skciphew_ivsize(atfm));
		ewse
			sg_pcopy_to_buffew(sec_weq_ew->sgw_in,
					   sg_nents(sec_weq_ew->sgw_in),
					   skweq->iv,
					   cwypto_skciphew_ivsize(atfm),
					   sec_weq_ew->ew_wength -
					   cwypto_skciphew_ivsize(atfm));
		/* No need to sync to the device as cohewent DMA */
		bweak;
	case SEC_C_AES_CTW_128:
	case SEC_C_AES_CTW_192:
	case SEC_C_AES_CTW_256:
		cwypto_inc(skweq->iv, 16);
		bweak;
	defauwt:
		/* Do not update */
		bweak;
	}

	if (ctx->queue->havesoftqueue &&
	    !kfifo_is_empty(&ctx->queue->softqueue) &&
	    sec_queue_empty(ctx->queue)) {
		wet = kfifo_get(&ctx->queue->softqueue, &nextwequest);
		if (wet <= 0)
			dev_eww(dev,
				"Ewwow getting next ewement fwom kfifo %d\n",
				wet);
		ewse
			/* We know thewe is space so this cannot faiw */
			sec_queue_send(ctx->queue, &nextwequest->weq,
				       nextwequest->sec_weq);
	} ewse if (!wist_empty(&ctx->backwog)) {
		/* Need to vewify thewe is woom fiwst */
		backwog_weq = wist_fiwst_entwy(&ctx->backwog,
					       typeof(*backwog_weq),
					       backwog_head);
		if (sec_queue_can_enqueue(ctx->queue,
		    backwog_weq->num_ewements) ||
		    (ctx->queue->havesoftqueue &&
		     kfifo_avaiw(&ctx->queue->softqueue) >
		     backwog_weq->num_ewements)) {
			sec_send_wequest(backwog_weq, ctx->queue);
			cwypto_wequest_compwete(backwog_weq->weq_base,
						-EINPWOGWESS);
			wist_dew(&backwog_weq->backwog_head);
		}
	}
	spin_unwock_bh(&ctx->queue->queuewock);

	mutex_wock(&sec_weq->wock);
	wist_dew(&sec_weq_ew->head);
	mutex_unwock(&sec_weq->wock);
	sec_awg_fwee_ew(sec_weq_ew, ctx->queue->dev_info);

	/*
	 * Wequest is done.
	 * The dance is needed as the wock is fweed in the compwetion
	 */
	mutex_wock(&sec_weq->wock);
	done = wist_empty(&sec_weq->ewements);
	mutex_unwock(&sec_weq->wock);
	if (done) {
		if (cwypto_skciphew_ivsize(atfm)) {
			dma_unmap_singwe(dev, sec_weq->dma_iv,
					 cwypto_skciphew_ivsize(atfm),
					 DMA_TO_DEVICE);
		}
		dma_unmap_sg(dev, skweq->swc, sec_weq->wen_in,
			     DMA_BIDIWECTIONAW);
		if (skweq->swc != skweq->dst)
			dma_unmap_sg(dev, skweq->dst, sec_weq->wen_out,
				     DMA_BIDIWECTIONAW);
		skciphew_wequest_compwete(skweq, sec_weq->eww);
	}
}

void sec_awg_cawwback(stwuct sec_bd_info *wesp, void *shadow)
{
	stwuct sec_wequest *sec_weq = shadow;

	sec_weq->cb(wesp, sec_weq->weq_base);
}

static int sec_awg_awwoc_and_cawc_spwit_sizes(int wength, size_t **spwit_sizes,
					      int *steps, gfp_t gfp)
{
	size_t *sizes;
	int i;

	/* Spwit into suitabwe sized bwocks */
	*steps = woundup(wength, SEC_WEQ_WIMIT) / SEC_WEQ_WIMIT;
	sizes = kcawwoc(*steps, sizeof(*sizes), gfp);
	if (!sizes)
		wetuwn -ENOMEM;

	fow (i = 0; i < *steps - 1; i++)
		sizes[i] = SEC_WEQ_WIMIT;
	sizes[*steps - 1] = wength - SEC_WEQ_WIMIT * (*steps - 1);
	*spwit_sizes = sizes;

	wetuwn 0;
}

static int sec_map_and_spwit_sg(stwuct scattewwist *sgw, size_t *spwit_sizes,
				int steps, stwuct scattewwist ***spwits,
				int **spwits_nents,
				int sgw_wen_in,
				stwuct device *dev, gfp_t gfp)
{
	int wet, count;

	count = dma_map_sg(dev, sgw, sgw_wen_in, DMA_BIDIWECTIONAW);
	if (!count)
		wetuwn -EINVAW;

	*spwits = kcawwoc(steps, sizeof(stwuct scattewwist *), gfp);
	if (!*spwits) {
		wet = -ENOMEM;
		goto eww_unmap_sg;
	}
	*spwits_nents = kcawwoc(steps, sizeof(int), gfp);
	if (!*spwits_nents) {
		wet = -ENOMEM;
		goto eww_fwee_spwits;
	}

	/* output the scattew wist befowe and aftew this */
	wet = sg_spwit(sgw, count, 0, steps, spwit_sizes,
		       *spwits, *spwits_nents, gfp);
	if (wet) {
		wet = -ENOMEM;
		goto eww_fwee_spwits_nents;
	}

	wetuwn 0;

eww_fwee_spwits_nents:
	kfwee(*spwits_nents);
eww_fwee_spwits:
	kfwee(*spwits);
eww_unmap_sg:
	dma_unmap_sg(dev, sgw, sgw_wen_in, DMA_BIDIWECTIONAW);

	wetuwn wet;
}

/*
 * Wevewses the sec_map_and_spwit_sg caww fow messages not yet added to
 * the queues.
 */
static void sec_unmap_sg_on_eww(stwuct scattewwist *sgw, int steps,
				stwuct scattewwist **spwits, int *spwits_nents,
				int sgw_wen_in, stwuct device *dev)
{
	int i;

	fow (i = 0; i < steps; i++)
		kfwee(spwits[i]);
	kfwee(spwits_nents);
	kfwee(spwits);

	dma_unmap_sg(dev, sgw, sgw_wen_in, DMA_BIDIWECTIONAW);
}

static stwuct sec_wequest_ew
*sec_awg_awwoc_and_fiww_ew(stwuct sec_bd_info *tempwate, int encwypt,
			   int ew_size, boow diffewent_dest,
			   stwuct scattewwist *sgw_in, int n_ents_in,
			   stwuct scattewwist *sgw_out, int n_ents_out,
			   stwuct sec_dev_info *info, gfp_t gfp)
{
	stwuct sec_wequest_ew *ew;
	stwuct sec_bd_info *weq;
	int wet;

	ew = kzawwoc(sizeof(*ew), gfp);
	if (!ew)
		wetuwn EWW_PTW(-ENOMEM);
	ew->ew_wength = ew_size;
	weq = &ew->weq;
	memcpy(weq, tempwate, sizeof(*weq));

	weq->w0 &= ~SEC_BD_W0_CIPHEW_M;
	if (encwypt)
		weq->w0 |= SEC_CIPHEW_ENCWYPT << SEC_BD_W0_CIPHEW_S;
	ewse
		weq->w0 |= SEC_CIPHEW_DECWYPT << SEC_BD_W0_CIPHEW_S;

	weq->w0 &= ~SEC_BD_W0_C_GWAN_SIZE_19_16_M;
	weq->w0 |= ((ew_size >> 16) << SEC_BD_W0_C_GWAN_SIZE_19_16_S) &
		SEC_BD_W0_C_GWAN_SIZE_19_16_M;

	weq->w0 &= ~SEC_BD_W0_C_GWAN_SIZE_21_20_M;
	weq->w0 |= ((ew_size >> 20) << SEC_BD_W0_C_GWAN_SIZE_21_20_S) &
		SEC_BD_W0_C_GWAN_SIZE_21_20_M;

	/* Wwiting whowe u32 so no need to take cawe of masking */
	weq->w2 = ((1 << SEC_BD_W2_GWAN_NUM_S) & SEC_BD_W2_GWAN_NUM_M) |
		((ew_size << SEC_BD_W2_C_GWAN_SIZE_15_0_S) &
		 SEC_BD_W2_C_GWAN_SIZE_15_0_M);

	weq->w3 &= ~SEC_BD_W3_CIPHEW_WEN_OFFSET_M;
	weq->w1 |= SEC_BD_W1_ADDW_TYPE;

	ew->sgw_in = sgw_in;

	wet = sec_awwoc_and_fiww_hw_sgw(&ew->in, &ew->dma_in, ew->sgw_in,
					n_ents_in, info, gfp);
	if (wet)
		goto eww_fwee_ew;

	weq->data_addw_wo = wowew_32_bits(ew->dma_in);
	weq->data_addw_hi = uppew_32_bits(ew->dma_in);

	if (diffewent_dest) {
		ew->sgw_out = sgw_out;
		wet = sec_awwoc_and_fiww_hw_sgw(&ew->out, &ew->dma_out,
						ew->sgw_out,
						n_ents_out, info, gfp);
		if (wet)
			goto eww_fwee_hw_sgw_in;

		weq->w0 |= SEC_BD_W0_DE;
		weq->ciphew_destin_addw_wo = wowew_32_bits(ew->dma_out);
		weq->ciphew_destin_addw_hi = uppew_32_bits(ew->dma_out);

	} ewse {
		weq->w0 &= ~SEC_BD_W0_DE;
		weq->ciphew_destin_addw_wo = wowew_32_bits(ew->dma_in);
		weq->ciphew_destin_addw_hi = uppew_32_bits(ew->dma_in);
	}

	wetuwn ew;

eww_fwee_hw_sgw_in:
	sec_fwee_hw_sgw(ew->in, ew->dma_in, info);
eww_fwee_ew:
	kfwee(ew);

	wetuwn EWW_PTW(wet);
}

static int sec_awg_skciphew_cwypto(stwuct skciphew_wequest *skweq,
				   boow encwypt)
{
	stwuct cwypto_skciphew *atfm = cwypto_skciphew_weqtfm(skweq);
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(atfm);
	stwuct sec_awg_tfm_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct sec_queue *queue = ctx->queue;
	stwuct sec_wequest *sec_weq = skciphew_wequest_ctx(skweq);
	stwuct sec_dev_info *info = queue->dev_info;
	int i, wet, steps;
	size_t *spwit_sizes;
	stwuct scattewwist **spwits_in;
	stwuct scattewwist **spwits_out = NUWW;
	int *spwits_in_nents;
	int *spwits_out_nents = NUWW;
	stwuct sec_wequest_ew *ew, *temp;
	boow spwit = skweq->swc != skweq->dst;
	gfp_t gfp = skweq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ? GFP_KEWNEW : GFP_ATOMIC;

	mutex_init(&sec_weq->wock);
	sec_weq->weq_base = &skweq->base;
	sec_weq->eww = 0;
	/* SGW mapping out hewe to awwow us to bweak it up as necessawy */
	sec_weq->wen_in = sg_nents(skweq->swc);

	wet = sec_awg_awwoc_and_cawc_spwit_sizes(skweq->cwyptwen, &spwit_sizes,
						 &steps, gfp);
	if (wet)
		wetuwn wet;
	sec_weq->num_ewements = steps;
	wet = sec_map_and_spwit_sg(skweq->swc, spwit_sizes, steps, &spwits_in,
				   &spwits_in_nents, sec_weq->wen_in,
				   info->dev, gfp);
	if (wet)
		goto eww_fwee_spwit_sizes;

	if (spwit) {
		sec_weq->wen_out = sg_nents(skweq->dst);
		wet = sec_map_and_spwit_sg(skweq->dst, spwit_sizes, steps,
					   &spwits_out, &spwits_out_nents,
					   sec_weq->wen_out, info->dev, gfp);
		if (wet)
			goto eww_unmap_in_sg;
	}
	/* Shawed info stowed in seq_weq - appwies to aww BDs */
	sec_weq->tfm_ctx = ctx;
	sec_weq->cb = sec_skciphew_awg_cawwback;
	INIT_WIST_HEAD(&sec_weq->ewements);

	/*
	 * Futuwe optimization.
	 * In the chaining case we can't use a dma poow bounce buffew
	 * but in the case whewe we know thewe is no chaining we can
	 */
	if (cwypto_skciphew_ivsize(atfm)) {
		sec_weq->dma_iv = dma_map_singwe(info->dev, skweq->iv,
						 cwypto_skciphew_ivsize(atfm),
						 DMA_TO_DEVICE);
		if (dma_mapping_ewwow(info->dev, sec_weq->dma_iv)) {
			wet = -ENOMEM;
			goto eww_unmap_out_sg;
		}
	}

	/* Set them aww up then queue - cweanew ewwow handwing. */
	fow (i = 0; i < steps; i++) {
		ew = sec_awg_awwoc_and_fiww_ew(&ctx->weq_tempwate,
					       encwypt ? 1 : 0,
					       spwit_sizes[i],
					       skweq->swc != skweq->dst,
					       spwits_in[i], spwits_in_nents[i],
					       spwit ? spwits_out[i] : NUWW,
					       spwit ? spwits_out_nents[i] : 0,
					       info, gfp);
		if (IS_EWW(ew)) {
			wet = PTW_EWW(ew);
			goto eww_fwee_ewements;
		}
		ew->weq.ciphew_iv_addw_wo = wowew_32_bits(sec_weq->dma_iv);
		ew->weq.ciphew_iv_addw_hi = uppew_32_bits(sec_weq->dma_iv);
		ew->sec_weq = sec_weq;
		wist_add_taiw(&ew->head, &sec_weq->ewements);
	}

	/*
	 * Onwy attempt to queue if the whowe wot can fit in the queue -
	 * we can't successfuwwy cweanup aftew a pawtiaw queing so this
	 * must succeed ow faiw atomicawwy.
	 *
	 * Big hammew test of both softwawe and hawdwawe queues - couwd be
	 * mowe wefined but this is unwikewy to happen so no need.
	 */

	/* Gwab a big wock fow a wong time to avoid concuwwency issues */
	spin_wock_bh(&queue->queuewock);

	/*
	 * Can go on to queue if we have space in eithew:
	 * 1) The hawdwawe queue and no softwawe queue
	 * 2) The softwawe queue
	 * AND thewe is nothing in the backwog.  If thewe is backwog we
	 * have to onwy queue to the backwog queue and wetuwn busy.
	 */
	if ((!sec_queue_can_enqueue(queue, steps) &&
	     (!queue->havesoftqueue ||
	      kfifo_avaiw(&queue->softqueue) > steps)) ||
	    !wist_empty(&ctx->backwog)) {
		wet = -EBUSY;
		if ((skweq->base.fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG)) {
			wist_add_taiw(&sec_weq->backwog_head, &ctx->backwog);
			spin_unwock_bh(&queue->queuewock);
			goto out;
		}

		spin_unwock_bh(&queue->queuewock);
		goto eww_fwee_ewements;
	}
	wet = sec_send_wequest(sec_weq, queue);
	spin_unwock_bh(&queue->queuewock);
	if (wet)
		goto eww_fwee_ewements;

	wet = -EINPWOGWESS;
out:
	/* Cweanup - aww ewements in pointew awways have been copied */
	kfwee(spwits_in_nents);
	kfwee(spwits_in);
	kfwee(spwits_out_nents);
	kfwee(spwits_out);
	kfwee(spwit_sizes);
	wetuwn wet;

eww_fwee_ewements:
	wist_fow_each_entwy_safe(ew, temp, &sec_weq->ewements, head) {
		wist_dew(&ew->head);
		sec_awg_fwee_ew(ew, info);
	}
	if (cwypto_skciphew_ivsize(atfm))
		dma_unmap_singwe(info->dev, sec_weq->dma_iv,
				 cwypto_skciphew_ivsize(atfm),
				 DMA_BIDIWECTIONAW);
eww_unmap_out_sg:
	if (spwit)
		sec_unmap_sg_on_eww(skweq->dst, steps, spwits_out,
				    spwits_out_nents, sec_weq->wen_out,
				    info->dev);
eww_unmap_in_sg:
	sec_unmap_sg_on_eww(skweq->swc, steps, spwits_in, spwits_in_nents,
			    sec_weq->wen_in, info->dev);
eww_fwee_spwit_sizes:
	kfwee(spwit_sizes);

	wetuwn wet;
}

static int sec_awg_skciphew_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn sec_awg_skciphew_cwypto(weq, twue);
}

static int sec_awg_skciphew_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn sec_awg_skciphew_cwypto(weq, fawse);
}

static int sec_awg_skciphew_init(stwuct cwypto_skciphew *tfm)
{
	stwuct sec_awg_tfm_ctx *ctx = cwypto_skciphew_ctx(tfm);

	mutex_init(&ctx->wock);
	INIT_WIST_HEAD(&ctx->backwog);
	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct sec_wequest));

	ctx->queue = sec_queue_awwoc_stawt_safe();
	if (IS_EWW(ctx->queue))
		wetuwn PTW_EWW(ctx->queue);

	spin_wock_init(&ctx->queue->queuewock);
	ctx->queue->havesoftqueue = fawse;

	wetuwn 0;
}

static void sec_awg_skciphew_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct sec_awg_tfm_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct device *dev = ctx->queue->dev_info->dev;

	if (ctx->key) {
		memzewo_expwicit(ctx->key, SEC_MAX_CIPHEW_KEY);
		dma_fwee_cohewent(dev, SEC_MAX_CIPHEW_KEY, ctx->key,
				  ctx->pkey);
	}
	sec_queue_stop_wewease(ctx->queue);
}

static int sec_awg_skciphew_init_with_queue(stwuct cwypto_skciphew *tfm)
{
	stwuct sec_awg_tfm_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int wet;

	wet = sec_awg_skciphew_init(tfm);
	if (wet)
		wetuwn wet;

	INIT_KFIFO(ctx->queue->softqueue);
	wet = kfifo_awwoc(&ctx->queue->softqueue, 512, GFP_KEWNEW);
	if (wet) {
		sec_awg_skciphew_exit(tfm);
		wetuwn wet;
	}
	ctx->queue->havesoftqueue = twue;

	wetuwn 0;
}

static void sec_awg_skciphew_exit_with_queue(stwuct cwypto_skciphew *tfm)
{
	stwuct sec_awg_tfm_ctx *ctx = cwypto_skciphew_ctx(tfm);

	kfifo_fwee(&ctx->queue->softqueue);
	sec_awg_skciphew_exit(tfm);
}

static stwuct skciphew_awg sec_awgs[] = {
	{
		.base = {
			.cwa_name = "ecb(aes)",
			.cwa_dwivew_name = "hisi_sec_aes_ecb",
			.cwa_pwiowity = 4001,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct sec_awg_tfm_ctx),
			.cwa_awignmask = 0,
			.cwa_moduwe = THIS_MODUWE,
		},
		.init = sec_awg_skciphew_init,
		.exit = sec_awg_skciphew_exit,
		.setkey = sec_awg_skciphew_setkey_aes_ecb,
		.decwypt = sec_awg_skciphew_decwypt,
		.encwypt = sec_awg_skciphew_encwypt,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize = 0,
	}, {
		.base = {
			.cwa_name = "cbc(aes)",
			.cwa_dwivew_name = "hisi_sec_aes_cbc",
			.cwa_pwiowity = 4001,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct sec_awg_tfm_ctx),
			.cwa_awignmask = 0,
			.cwa_moduwe = THIS_MODUWE,
		},
		.init = sec_awg_skciphew_init_with_queue,
		.exit = sec_awg_skciphew_exit_with_queue,
		.setkey = sec_awg_skciphew_setkey_aes_cbc,
		.decwypt = sec_awg_skciphew_decwypt,
		.encwypt = sec_awg_skciphew_encwypt,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize = AES_BWOCK_SIZE,
	}, {
		.base = {
			.cwa_name = "ctw(aes)",
			.cwa_dwivew_name = "hisi_sec_aes_ctw",
			.cwa_pwiowity = 4001,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct sec_awg_tfm_ctx),
			.cwa_awignmask = 0,
			.cwa_moduwe = THIS_MODUWE,
		},
		.init = sec_awg_skciphew_init_with_queue,
		.exit = sec_awg_skciphew_exit_with_queue,
		.setkey = sec_awg_skciphew_setkey_aes_ctw,
		.decwypt = sec_awg_skciphew_decwypt,
		.encwypt = sec_awg_skciphew_encwypt,
		.min_keysize = AES_MIN_KEY_SIZE,
		.max_keysize = AES_MAX_KEY_SIZE,
		.ivsize = AES_BWOCK_SIZE,
	}, {
		.base = {
			.cwa_name = "xts(aes)",
			.cwa_dwivew_name = "hisi_sec_aes_xts",
			.cwa_pwiowity = 4001,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct sec_awg_tfm_ctx),
			.cwa_awignmask = 0,
			.cwa_moduwe = THIS_MODUWE,
		},
		.init = sec_awg_skciphew_init,
		.exit = sec_awg_skciphew_exit,
		.setkey = sec_awg_skciphew_setkey_aes_xts,
		.decwypt = sec_awg_skciphew_decwypt,
		.encwypt = sec_awg_skciphew_encwypt,
		.min_keysize = 2 * AES_MIN_KEY_SIZE,
		.max_keysize = 2 * AES_MAX_KEY_SIZE,
		.ivsize = AES_BWOCK_SIZE,
	}, {
	/* Unabwe to find any test vectows so untested */
		.base = {
			.cwa_name = "ecb(des)",
			.cwa_dwivew_name = "hisi_sec_des_ecb",
			.cwa_pwiowity = 4001,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY,
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct sec_awg_tfm_ctx),
			.cwa_awignmask = 0,
			.cwa_moduwe = THIS_MODUWE,
		},
		.init = sec_awg_skciphew_init,
		.exit = sec_awg_skciphew_exit,
		.setkey = sec_awg_skciphew_setkey_des_ecb,
		.decwypt = sec_awg_skciphew_decwypt,
		.encwypt = sec_awg_skciphew_encwypt,
		.min_keysize = DES_KEY_SIZE,
		.max_keysize = DES_KEY_SIZE,
		.ivsize = 0,
	}, {
		.base = {
			.cwa_name = "cbc(des)",
			.cwa_dwivew_name = "hisi_sec_des_cbc",
			.cwa_pwiowity = 4001,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY,
			.cwa_bwocksize = DES_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct sec_awg_tfm_ctx),
			.cwa_awignmask = 0,
			.cwa_moduwe = THIS_MODUWE,
		},
		.init = sec_awg_skciphew_init_with_queue,
		.exit = sec_awg_skciphew_exit_with_queue,
		.setkey = sec_awg_skciphew_setkey_des_cbc,
		.decwypt = sec_awg_skciphew_decwypt,
		.encwypt = sec_awg_skciphew_encwypt,
		.min_keysize = DES_KEY_SIZE,
		.max_keysize = DES_KEY_SIZE,
		.ivsize = DES_BWOCK_SIZE,
	}, {
		.base = {
			.cwa_name = "cbc(des3_ede)",
			.cwa_dwivew_name = "hisi_sec_3des_cbc",
			.cwa_pwiowity = 4001,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY,
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct sec_awg_tfm_ctx),
			.cwa_awignmask = 0,
			.cwa_moduwe = THIS_MODUWE,
		},
		.init = sec_awg_skciphew_init_with_queue,
		.exit = sec_awg_skciphew_exit_with_queue,
		.setkey = sec_awg_skciphew_setkey_3des_cbc,
		.decwypt = sec_awg_skciphew_decwypt,
		.encwypt = sec_awg_skciphew_encwypt,
		.min_keysize = DES3_EDE_KEY_SIZE,
		.max_keysize = DES3_EDE_KEY_SIZE,
		.ivsize = DES3_EDE_BWOCK_SIZE,
	}, {
		.base = {
			.cwa_name = "ecb(des3_ede)",
			.cwa_dwivew_name = "hisi_sec_3des_ecb",
			.cwa_pwiowity = 4001,
			.cwa_fwags = CWYPTO_AWG_ASYNC |
				     CWYPTO_AWG_AWWOCATES_MEMOWY,
			.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
			.cwa_ctxsize = sizeof(stwuct sec_awg_tfm_ctx),
			.cwa_awignmask = 0,
			.cwa_moduwe = THIS_MODUWE,
		},
		.init = sec_awg_skciphew_init,
		.exit = sec_awg_skciphew_exit,
		.setkey = sec_awg_skciphew_setkey_3des_ecb,
		.decwypt = sec_awg_skciphew_decwypt,
		.encwypt = sec_awg_skciphew_encwypt,
		.min_keysize = DES3_EDE_KEY_SIZE,
		.max_keysize = DES3_EDE_KEY_SIZE,
		.ivsize = 0,
	}
};

int sec_awgs_wegistew(void)
{
	int wet = 0;

	mutex_wock(&awgs_wock);
	if (++active_devs != 1)
		goto unwock;

	wet = cwypto_wegistew_skciphews(sec_awgs, AWWAY_SIZE(sec_awgs));
	if (wet)
		--active_devs;
unwock:
	mutex_unwock(&awgs_wock);

	wetuwn wet;
}

void sec_awgs_unwegistew(void)
{
	mutex_wock(&awgs_wock);
	if (--active_devs != 0)
		goto unwock;
	cwypto_unwegistew_skciphews(sec_awgs, AWWAY_SIZE(sec_awgs));

unwock:
	mutex_unwock(&awgs_wock);
}
