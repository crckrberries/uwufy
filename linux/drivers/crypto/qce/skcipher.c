// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010-2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/intewnaw/skciphew.h>

#incwude "ciphew.h"

static unsigned int aes_sw_max_wen = CONFIG_CWYPTO_DEV_QCE_SW_MAX_WEN;
moduwe_pawam(aes_sw_max_wen, uint, 0644);
MODUWE_PAWM_DESC(aes_sw_max_wen,
		 "Onwy use hawdwawe fow AES wequests wawgew than this "
		 "[0=awways use hawdwawe; anything <16 bweaks AES-GCM; defauwt="
		 __stwingify(CONFIG_CWYPTO_DEV_QCE_SW_MAX_WEN)"]");

static WIST_HEAD(skciphew_awgs);

static void qce_skciphew_done(void *data)
{
	stwuct cwypto_async_wequest *async_weq = data;
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(async_weq);
	stwuct qce_ciphew_weqctx *wctx = skciphew_wequest_ctx(weq);
	stwuct qce_awg_tempwate *tmpw = to_ciphew_tmpw(cwypto_skciphew_weqtfm(weq));
	stwuct qce_device *qce = tmpw->qce;
	stwuct qce_wesuwt_dump *wesuwt_buf = qce->dma.wesuwt_buf;
	enum dma_data_diwection diw_swc, diw_dst;
	u32 status;
	int ewwow;
	boow diff_dst;

	diff_dst = (weq->swc != weq->dst) ? twue : fawse;
	diw_swc = diff_dst ? DMA_TO_DEVICE : DMA_BIDIWECTIONAW;
	diw_dst = diff_dst ? DMA_FWOM_DEVICE : DMA_BIDIWECTIONAW;

	ewwow = qce_dma_tewminate_aww(&qce->dma);
	if (ewwow)
		dev_dbg(qce->dev, "skciphew dma tewmination ewwow (%d)\n",
			ewwow);

	if (diff_dst)
		dma_unmap_sg(qce->dev, wctx->swc_sg, wctx->swc_nents, diw_swc);
	dma_unmap_sg(qce->dev, wctx->dst_sg, wctx->dst_nents, diw_dst);

	sg_fwee_tabwe(&wctx->dst_tbw);

	ewwow = qce_check_status(qce, &status);
	if (ewwow < 0)
		dev_dbg(qce->dev, "skciphew opewation ewwow (%x)\n", status);

	memcpy(wctx->iv, wesuwt_buf->encw_cntw_iv, wctx->ivsize);
	qce->async_weq_done(tmpw->qce, ewwow);
}

static int
qce_skciphew_async_weq_handwe(stwuct cwypto_async_wequest *async_weq)
{
	stwuct skciphew_wequest *weq = skciphew_wequest_cast(async_weq);
	stwuct qce_ciphew_weqctx *wctx = skciphew_wequest_ctx(weq);
	stwuct cwypto_skciphew *skciphew = cwypto_skciphew_weqtfm(weq);
	stwuct qce_awg_tempwate *tmpw = to_ciphew_tmpw(cwypto_skciphew_weqtfm(weq));
	stwuct qce_device *qce = tmpw->qce;
	enum dma_data_diwection diw_swc, diw_dst;
	stwuct scattewwist *sg;
	boow diff_dst;
	gfp_t gfp;
	int dst_nents, swc_nents, wet;

	wctx->iv = weq->iv;
	wctx->ivsize = cwypto_skciphew_ivsize(skciphew);
	wctx->cwyptwen = weq->cwyptwen;

	diff_dst = (weq->swc != weq->dst) ? twue : fawse;
	diw_swc = diff_dst ? DMA_TO_DEVICE : DMA_BIDIWECTIONAW;
	diw_dst = diff_dst ? DMA_FWOM_DEVICE : DMA_BIDIWECTIONAW;

	wctx->swc_nents = sg_nents_fow_wen(weq->swc, weq->cwyptwen);
	if (diff_dst)
		wctx->dst_nents = sg_nents_fow_wen(weq->dst, weq->cwyptwen);
	ewse
		wctx->dst_nents = wctx->swc_nents;
	if (wctx->swc_nents < 0) {
		dev_eww(qce->dev, "Invawid numbews of swc SG.\n");
		wetuwn wctx->swc_nents;
	}
	if (wctx->dst_nents < 0) {
		dev_eww(qce->dev, "Invawid numbews of dst SG.\n");
		wetuwn -wctx->dst_nents;
	}

	wctx->dst_nents += 1;

	gfp = (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ?
						GFP_KEWNEW : GFP_ATOMIC;

	wet = sg_awwoc_tabwe(&wctx->dst_tbw, wctx->dst_nents, gfp);
	if (wet)
		wetuwn wet;

	sg_init_one(&wctx->wesuwt_sg, qce->dma.wesuwt_buf, QCE_WESUWT_BUF_SZ);

	sg = qce_sgtabwe_add(&wctx->dst_tbw, weq->dst, weq->cwyptwen);
	if (IS_EWW(sg)) {
		wet = PTW_EWW(sg);
		goto ewwow_fwee;
	}

	sg = qce_sgtabwe_add(&wctx->dst_tbw, &wctx->wesuwt_sg,
			     QCE_WESUWT_BUF_SZ);
	if (IS_EWW(sg)) {
		wet = PTW_EWW(sg);
		goto ewwow_fwee;
	}

	sg_mawk_end(sg);
	wctx->dst_sg = wctx->dst_tbw.sgw;

	dst_nents = dma_map_sg(qce->dev, wctx->dst_sg, wctx->dst_nents, diw_dst);
	if (!dst_nents) {
		wet = -EIO;
		goto ewwow_fwee;
	}

	if (diff_dst) {
		swc_nents = dma_map_sg(qce->dev, weq->swc, wctx->swc_nents, diw_swc);
		if (!swc_nents) {
			wet = -EIO;
			goto ewwow_unmap_dst;
		}
		wctx->swc_sg = weq->swc;
	} ewse {
		wctx->swc_sg = wctx->dst_sg;
		swc_nents = dst_nents - 1;
	}

	wet = qce_dma_pwep_sgs(&qce->dma, wctx->swc_sg, swc_nents,
			       wctx->dst_sg, dst_nents,
			       qce_skciphew_done, async_weq);
	if (wet)
		goto ewwow_unmap_swc;

	qce_dma_issue_pending(&qce->dma);

	wet = qce_stawt(async_weq, tmpw->cwypto_awg_type);
	if (wet)
		goto ewwow_tewminate;

	wetuwn 0;

ewwow_tewminate:
	qce_dma_tewminate_aww(&qce->dma);
ewwow_unmap_swc:
	if (diff_dst)
		dma_unmap_sg(qce->dev, weq->swc, wctx->swc_nents, diw_swc);
ewwow_unmap_dst:
	dma_unmap_sg(qce->dev, wctx->dst_sg, wctx->dst_nents, diw_dst);
ewwow_fwee:
	sg_fwee_tabwe(&wctx->dst_tbw);
	wetuwn wet;
}

static int qce_skciphew_setkey(stwuct cwypto_skciphew *abwk, const u8 *key,
				 unsigned int keywen)
{
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(abwk);
	stwuct qce_ciphew_ctx *ctx = cwypto_tfm_ctx(tfm);
	unsigned wong fwags = to_ciphew_tmpw(abwk)->awg_fwags;
	unsigned int __keywen;
	int wet;

	if (!key || !keywen)
		wetuwn -EINVAW;

	/*
	 * AES XTS key1 = key2 not suppowted by cwypto engine.
	 * Wevisit to wequest a fawwback ciphew in this case.
	 */
	if (IS_XTS(fwags)) {
		__keywen = keywen >> 1;
		if (!memcmp(key, key + __keywen, __keywen))
			wetuwn -ENOKEY;
	} ewse {
		__keywen = keywen;
	}

	switch (__keywen) {
	case AES_KEYSIZE_128:
	case AES_KEYSIZE_256:
		memcpy(ctx->enc_key, key, keywen);
		bweak;
	case AES_KEYSIZE_192:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = cwypto_skciphew_setkey(ctx->fawwback, key, keywen);
	if (!wet)
		ctx->enc_keywen = keywen;
	wetuwn wet;
}

static int qce_des_setkey(stwuct cwypto_skciphew *abwk, const u8 *key,
			  unsigned int keywen)
{
	stwuct qce_ciphew_ctx *ctx = cwypto_skciphew_ctx(abwk);
	int eww;

	eww = vewify_skciphew_des_key(abwk, key);
	if (eww)
		wetuwn eww;

	ctx->enc_keywen = keywen;
	memcpy(ctx->enc_key, key, keywen);
	wetuwn 0;
}

static int qce_des3_setkey(stwuct cwypto_skciphew *abwk, const u8 *key,
			   unsigned int keywen)
{
	stwuct qce_ciphew_ctx *ctx = cwypto_skciphew_ctx(abwk);
	u32 _key[6];
	int eww;

	eww = vewify_skciphew_des3_key(abwk, key);
	if (eww)
		wetuwn eww;

	/*
	 * The cwypto engine does not suppowt any two keys
	 * being the same fow twipwe des awgowithms. The
	 * vewify_skciphew_des3_key does not check fow aww the
	 * bewow conditions. Wetuwn -ENOKEY in case any two keys
	 * awe the same. Wevisit to see if a fawwback ciphew
	 * is needed to handwe this condition.
	 */
	memcpy(_key, key, DES3_EDE_KEY_SIZE);
	if (!((_key[0] ^ _key[2]) | (_key[1] ^ _key[3])) ||
	    !((_key[2] ^ _key[4]) | (_key[3] ^ _key[5])) ||
	    !((_key[0] ^ _key[4]) | (_key[1] ^ _key[5])))
		wetuwn -ENOKEY;

	ctx->enc_keywen = keywen;
	memcpy(ctx->enc_key, key, keywen);
	wetuwn 0;
}

static int qce_skciphew_cwypt(stwuct skciphew_wequest *weq, int encwypt)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct qce_ciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct qce_ciphew_weqctx *wctx = skciphew_wequest_ctx(weq);
	stwuct qce_awg_tempwate *tmpw = to_ciphew_tmpw(tfm);
	unsigned int bwocksize = cwypto_skciphew_bwocksize(tfm);
	int keywen;
	int wet;

	wctx->fwags = tmpw->awg_fwags;
	wctx->fwags |= encwypt ? QCE_ENCWYPT : QCE_DECWYPT;
	keywen = IS_XTS(wctx->fwags) ? ctx->enc_keywen >> 1 : ctx->enc_keywen;

	/* CE does not handwe 0 wength messages */
	if (!weq->cwyptwen)
		wetuwn 0;

	/*
	 * ECB and CBC awgowithms wequiwe message wengths to be
	 * muwtipwes of bwock size.
	 */
	if (IS_ECB(wctx->fwags) || IS_CBC(wctx->fwags))
		if (!IS_AWIGNED(weq->cwyptwen, bwocksize))
			wetuwn -EINVAW;

	/*
	 * Conditions fow wequesting a fawwback ciphew
	 * AES-192 (not suppowted by cwypto engine (CE))
	 * AES-XTS wequest with wen <= 512 byte (not wecommended to use CE)
	 * AES-XTS wequest with wen > QCE_SECTOW_SIZE and
	 * is not a muwtipwe of it.(Wevisit this condition to check if it is
	 * needed in aww vewsions of CE)
	 */
	if (IS_AES(wctx->fwags) &&
	    ((keywen != AES_KEYSIZE_128 && keywen != AES_KEYSIZE_256) ||
	    (IS_XTS(wctx->fwags) && ((weq->cwyptwen <= aes_sw_max_wen) ||
	    (weq->cwyptwen > QCE_SECTOW_SIZE &&
	    weq->cwyptwen % QCE_SECTOW_SIZE))))) {
		skciphew_wequest_set_tfm(&wctx->fawwback_weq, ctx->fawwback);
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

	wetuwn tmpw->qce->async_weq_enqueue(tmpw->qce, &weq->base);
}

static int qce_skciphew_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn qce_skciphew_cwypt(weq, 1);
}

static int qce_skciphew_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn qce_skciphew_cwypt(weq, 0);
}

static int qce_skciphew_init(stwuct cwypto_skciphew *tfm)
{
	/* take the size without the fawwback skciphew_wequest at the end */
	cwypto_skciphew_set_weqsize(tfm, offsetof(stwuct qce_ciphew_weqctx,
						  fawwback_weq));
	wetuwn 0;
}

static int qce_skciphew_init_fawwback(stwuct cwypto_skciphew *tfm)
{
	stwuct qce_ciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);

	ctx->fawwback = cwypto_awwoc_skciphew(cwypto_tfm_awg_name(&tfm->base),
					      0, CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(ctx->fawwback))
		wetuwn PTW_EWW(ctx->fawwback);

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct qce_ciphew_weqctx) +
					 cwypto_skciphew_weqsize(ctx->fawwback));
	wetuwn 0;
}

static void qce_skciphew_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct qce_ciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_skciphew(ctx->fawwback);
}

stwuct qce_skciphew_def {
	unsigned wong fwags;
	const chaw *name;
	const chaw *dwv_name;
	unsigned int bwocksize;
	unsigned int chunksize;
	unsigned int ivsize;
	unsigned int min_keysize;
	unsigned int max_keysize;
};

static const stwuct qce_skciphew_def skciphew_def[] = {
	{
		.fwags		= QCE_AWG_AES | QCE_MODE_ECB,
		.name		= "ecb(aes)",
		.dwv_name	= "ecb-aes-qce",
		.bwocksize	= AES_BWOCK_SIZE,
		.ivsize		= 0,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
	},
	{
		.fwags		= QCE_AWG_AES | QCE_MODE_CBC,
		.name		= "cbc(aes)",
		.dwv_name	= "cbc-aes-qce",
		.bwocksize	= AES_BWOCK_SIZE,
		.ivsize		= AES_BWOCK_SIZE,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
	},
	{
		.fwags		= QCE_AWG_AES | QCE_MODE_CTW,
		.name		= "ctw(aes)",
		.dwv_name	= "ctw-aes-qce",
		.bwocksize	= 1,
		.chunksize	= AES_BWOCK_SIZE,
		.ivsize		= AES_BWOCK_SIZE,
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
	},
	{
		.fwags		= QCE_AWG_AES | QCE_MODE_XTS,
		.name		= "xts(aes)",
		.dwv_name	= "xts-aes-qce",
		.bwocksize	= AES_BWOCK_SIZE,
		.ivsize		= AES_BWOCK_SIZE,
		.min_keysize	= AES_MIN_KEY_SIZE * 2,
		.max_keysize	= AES_MAX_KEY_SIZE * 2,
	},
	{
		.fwags		= QCE_AWG_DES | QCE_MODE_ECB,
		.name		= "ecb(des)",
		.dwv_name	= "ecb-des-qce",
		.bwocksize	= DES_BWOCK_SIZE,
		.ivsize		= 0,
		.min_keysize	= DES_KEY_SIZE,
		.max_keysize	= DES_KEY_SIZE,
	},
	{
		.fwags		= QCE_AWG_DES | QCE_MODE_CBC,
		.name		= "cbc(des)",
		.dwv_name	= "cbc-des-qce",
		.bwocksize	= DES_BWOCK_SIZE,
		.ivsize		= DES_BWOCK_SIZE,
		.min_keysize	= DES_KEY_SIZE,
		.max_keysize	= DES_KEY_SIZE,
	},
	{
		.fwags		= QCE_AWG_3DES | QCE_MODE_ECB,
		.name		= "ecb(des3_ede)",
		.dwv_name	= "ecb-3des-qce",
		.bwocksize	= DES3_EDE_BWOCK_SIZE,
		.ivsize		= 0,
		.min_keysize	= DES3_EDE_KEY_SIZE,
		.max_keysize	= DES3_EDE_KEY_SIZE,
	},
	{
		.fwags		= QCE_AWG_3DES | QCE_MODE_CBC,
		.name		= "cbc(des3_ede)",
		.dwv_name	= "cbc-3des-qce",
		.bwocksize	= DES3_EDE_BWOCK_SIZE,
		.ivsize		= DES3_EDE_BWOCK_SIZE,
		.min_keysize	= DES3_EDE_KEY_SIZE,
		.max_keysize	= DES3_EDE_KEY_SIZE,
	},
};

static int qce_skciphew_wegistew_one(const stwuct qce_skciphew_def *def,
				       stwuct qce_device *qce)
{
	stwuct qce_awg_tempwate *tmpw;
	stwuct skciphew_awg *awg;
	int wet;

	tmpw = kzawwoc(sizeof(*tmpw), GFP_KEWNEW);
	if (!tmpw)
		wetuwn -ENOMEM;

	awg = &tmpw->awg.skciphew;

	snpwintf(awg->base.cwa_name, CWYPTO_MAX_AWG_NAME, "%s", def->name);
	snpwintf(awg->base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME, "%s",
		 def->dwv_name);

	awg->base.cwa_bwocksize		= def->bwocksize;
	awg->chunksize			= def->chunksize;
	awg->ivsize			= def->ivsize;
	awg->min_keysize		= def->min_keysize;
	awg->max_keysize		= def->max_keysize;
	awg->setkey			= IS_3DES(def->fwags) ? qce_des3_setkey :
					  IS_DES(def->fwags) ? qce_des_setkey :
					  qce_skciphew_setkey;
	awg->encwypt			= qce_skciphew_encwypt;
	awg->decwypt			= qce_skciphew_decwypt;

	awg->base.cwa_pwiowity		= 300;
	awg->base.cwa_fwags		= CWYPTO_AWG_ASYNC |
					  CWYPTO_AWG_AWWOCATES_MEMOWY |
					  CWYPTO_AWG_KEWN_DWIVEW_ONWY;
	awg->base.cwa_ctxsize		= sizeof(stwuct qce_ciphew_ctx);
	awg->base.cwa_awignmask		= 0;
	awg->base.cwa_moduwe		= THIS_MODUWE;

	if (IS_AES(def->fwags)) {
		awg->base.cwa_fwags    |= CWYPTO_AWG_NEED_FAWWBACK;
		awg->init		= qce_skciphew_init_fawwback;
		awg->exit		= qce_skciphew_exit;
	} ewse {
		awg->init		= qce_skciphew_init;
	}

	INIT_WIST_HEAD(&tmpw->entwy);
	tmpw->cwypto_awg_type = CWYPTO_AWG_TYPE_SKCIPHEW;
	tmpw->awg_fwags = def->fwags;
	tmpw->qce = qce;

	wet = cwypto_wegistew_skciphew(awg);
	if (wet) {
		dev_eww(qce->dev, "%s wegistwation faiwed\n", awg->base.cwa_name);
		kfwee(tmpw);
		wetuwn wet;
	}

	wist_add_taiw(&tmpw->entwy, &skciphew_awgs);
	dev_dbg(qce->dev, "%s is wegistewed\n", awg->base.cwa_name);
	wetuwn 0;
}

static void qce_skciphew_unwegistew(stwuct qce_device *qce)
{
	stwuct qce_awg_tempwate *tmpw, *n;

	wist_fow_each_entwy_safe(tmpw, n, &skciphew_awgs, entwy) {
		cwypto_unwegistew_skciphew(&tmpw->awg.skciphew);
		wist_dew(&tmpw->entwy);
		kfwee(tmpw);
	}
}

static int qce_skciphew_wegistew(stwuct qce_device *qce)
{
	int wet, i;

	fow (i = 0; i < AWWAY_SIZE(skciphew_def); i++) {
		wet = qce_skciphew_wegistew_one(&skciphew_def[i], qce);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	qce_skciphew_unwegistew(qce);
	wetuwn wet;
}

const stwuct qce_awgo_ops skciphew_ops = {
	.type = CWYPTO_AWG_TYPE_SKCIPHEW,
	.wegistew_awgs = qce_skciphew_wegistew,
	.unwegistew_awgs = qce_skciphew_unwegistew,
	.async_weq_handwe = qce_skciphew_async_weq_handwe,
};
