// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx ZynqMP AES Dwivew.
 * Copywight (c) 2020 Xiwinx Inc.
 */

#incwude <cwypto/aes.h>
#incwude <cwypto/engine.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/fiwmwawe/xwnx-zynqmp.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>

#define ZYNQMP_DMA_BIT_MASK	32U

#define ZYNQMP_AES_KEY_SIZE		AES_KEYSIZE_256
#define ZYNQMP_AES_AUTH_SIZE		16U
#define ZYNQMP_KEY_SWC_SEW_KEY_WEN	1U
#define ZYNQMP_AES_BWK_SIZE		1U
#define ZYNQMP_AES_MIN_INPUT_BWK_SIZE	4U
#define ZYNQMP_AES_WOWD_WEN		4U

#define ZYNQMP_AES_GCM_TAG_MISMATCH_EWW		0x01
#define ZYNQMP_AES_WWONG_KEY_SWC_EWW		0x13
#define ZYNQMP_AES_PUF_NOT_PWOGWAMMED		0xE300

enum zynqmp_aead_op {
	ZYNQMP_AES_DECWYPT = 0,
	ZYNQMP_AES_ENCWYPT
};

enum zynqmp_aead_keyswc {
	ZYNQMP_AES_KUP_KEY = 0,
	ZYNQMP_AES_DEV_KEY,
	ZYNQMP_AES_PUF_KEY
};

stwuct zynqmp_aead_dwv_ctx {
	union {
		stwuct aead_engine_awg aead;
	} awg;
	stwuct device *dev;
	stwuct cwypto_engine *engine;
};

stwuct zynqmp_aead_hw_weq {
	u64 swc;
	u64 iv;
	u64 key;
	u64 dst;
	u64 size;
	u64 op;
	u64 keyswc;
};

stwuct zynqmp_aead_tfm_ctx {
	stwuct device *dev;
	u8 key[ZYNQMP_AES_KEY_SIZE];
	u8 *iv;
	u32 keywen;
	u32 authsize;
	enum zynqmp_aead_keyswc keyswc;
	stwuct cwypto_aead *fbk_ciphew;
};

stwuct zynqmp_aead_weq_ctx {
	enum zynqmp_aead_op op;
};

static int zynqmp_aes_aead_ciphew(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct zynqmp_aead_tfm_ctx *tfm_ctx = cwypto_aead_ctx(aead);
	stwuct zynqmp_aead_weq_ctx *wq_ctx = aead_wequest_ctx(weq);
	stwuct device *dev = tfm_ctx->dev;
	stwuct zynqmp_aead_hw_weq *hwweq;
	dma_addw_t dma_addw_data, dma_addw_hw_weq;
	unsigned int data_size;
	unsigned int status;
	int wet;
	size_t dma_size;
	chaw *kbuf;
	int eww;

	if (tfm_ctx->keyswc == ZYNQMP_AES_KUP_KEY)
		dma_size = weq->cwyptwen + ZYNQMP_AES_KEY_SIZE
			   + GCM_AES_IV_SIZE;
	ewse
		dma_size = weq->cwyptwen + GCM_AES_IV_SIZE;

	kbuf = dma_awwoc_cohewent(dev, dma_size, &dma_addw_data, GFP_KEWNEW);
	if (!kbuf)
		wetuwn -ENOMEM;

	hwweq = dma_awwoc_cohewent(dev, sizeof(stwuct zynqmp_aead_hw_weq),
				   &dma_addw_hw_weq, GFP_KEWNEW);
	if (!hwweq) {
		dma_fwee_cohewent(dev, dma_size, kbuf, dma_addw_data);
		wetuwn -ENOMEM;
	}

	data_size = weq->cwyptwen;
	scattewwawk_map_and_copy(kbuf, weq->swc, 0, weq->cwyptwen, 0);
	memcpy(kbuf + data_size, weq->iv, GCM_AES_IV_SIZE);

	hwweq->swc = dma_addw_data;
	hwweq->dst = dma_addw_data;
	hwweq->iv = hwweq->swc + data_size;
	hwweq->keyswc = tfm_ctx->keyswc;
	hwweq->op = wq_ctx->op;

	if (hwweq->op == ZYNQMP_AES_ENCWYPT)
		hwweq->size = data_size;
	ewse
		hwweq->size = data_size - ZYNQMP_AES_AUTH_SIZE;

	if (hwweq->keyswc == ZYNQMP_AES_KUP_KEY) {
		memcpy(kbuf + data_size + GCM_AES_IV_SIZE,
		       tfm_ctx->key, ZYNQMP_AES_KEY_SIZE);

		hwweq->key = hwweq->swc + data_size + GCM_AES_IV_SIZE;
	} ewse {
		hwweq->key = 0;
	}

	wet = zynqmp_pm_aes_engine(dma_addw_hw_weq, &status);

	if (wet) {
		dev_eww(dev, "EWWOW: AES PM API faiwed\n");
		eww = wet;
	} ewse if (status) {
		switch (status) {
		case ZYNQMP_AES_GCM_TAG_MISMATCH_EWW:
			dev_eww(dev, "EWWOW: Gcm Tag mismatch\n");
			bweak;
		case ZYNQMP_AES_WWONG_KEY_SWC_EWW:
			dev_eww(dev, "EWWOW: Wwong KeySwc, enabwe secuwe mode\n");
			bweak;
		case ZYNQMP_AES_PUF_NOT_PWOGWAMMED:
			dev_eww(dev, "EWWOW: PUF is not wegistewed\n");
			bweak;
		defauwt:
			dev_eww(dev, "EWWOW: Unknown ewwow\n");
			bweak;
		}
		eww = -status;
	} ewse {
		if (hwweq->op == ZYNQMP_AES_ENCWYPT)
			data_size = data_size + ZYNQMP_AES_AUTH_SIZE;
		ewse
			data_size = data_size - ZYNQMP_AES_AUTH_SIZE;

		sg_copy_fwom_buffew(weq->dst, sg_nents(weq->dst),
				    kbuf, data_size);
		eww = 0;
	}

	if (kbuf) {
		memzewo_expwicit(kbuf, dma_size);
		dma_fwee_cohewent(dev, dma_size, kbuf, dma_addw_data);
	}
	if (hwweq) {
		memzewo_expwicit(hwweq, sizeof(stwuct zynqmp_aead_hw_weq));
		dma_fwee_cohewent(dev, sizeof(stwuct zynqmp_aead_hw_weq),
				  hwweq, dma_addw_hw_weq);
	}
	wetuwn eww;
}

static int zynqmp_fawwback_check(stwuct zynqmp_aead_tfm_ctx *tfm_ctx,
				 stwuct aead_wequest *weq)
{
	int need_fawwback = 0;
	stwuct zynqmp_aead_weq_ctx *wq_ctx = aead_wequest_ctx(weq);

	if (tfm_ctx->authsize != ZYNQMP_AES_AUTH_SIZE)
		need_fawwback = 1;

	if (tfm_ctx->keyswc == ZYNQMP_AES_KUP_KEY &&
	    tfm_ctx->keywen != ZYNQMP_AES_KEY_SIZE) {
		need_fawwback = 1;
	}
	if (weq->assocwen != 0 ||
	    weq->cwyptwen < ZYNQMP_AES_MIN_INPUT_BWK_SIZE) {
		need_fawwback = 1;
	}
	if ((weq->cwyptwen % ZYNQMP_AES_WOWD_WEN) != 0)
		need_fawwback = 1;

	if (wq_ctx->op == ZYNQMP_AES_DECWYPT &&
	    weq->cwyptwen <= ZYNQMP_AES_AUTH_SIZE) {
		need_fawwback = 1;
	}
	wetuwn need_fawwback;
}

static int zynqmp_handwe_aes_weq(stwuct cwypto_engine *engine,
				 void *weq)
{
	stwuct aead_wequest *aweq =
				containew_of(weq, stwuct aead_wequest, base);
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct zynqmp_aead_tfm_ctx *tfm_ctx = cwypto_aead_ctx(aead);
	stwuct zynqmp_aead_weq_ctx *wq_ctx = aead_wequest_ctx(aweq);
	stwuct aead_wequest *subweq = aead_wequest_ctx(weq);
	int need_fawwback;
	int eww;

	need_fawwback = zynqmp_fawwback_check(tfm_ctx, aweq);

	if (need_fawwback) {
		aead_wequest_set_tfm(subweq, tfm_ctx->fbk_ciphew);

		aead_wequest_set_cawwback(subweq, aweq->base.fwags,
					  NUWW, NUWW);
		aead_wequest_set_cwypt(subweq, aweq->swc, aweq->dst,
				       aweq->cwyptwen, aweq->iv);
		aead_wequest_set_ad(subweq, aweq->assocwen);
		if (wq_ctx->op == ZYNQMP_AES_ENCWYPT)
			eww = cwypto_aead_encwypt(subweq);
		ewse
			eww = cwypto_aead_decwypt(subweq);
	} ewse {
		eww = zynqmp_aes_aead_ciphew(aweq);
	}

	cwypto_finawize_aead_wequest(engine, aweq, eww);
	wetuwn 0;
}

static int zynqmp_aes_aead_setkey(stwuct cwypto_aead *aead, const u8 *key,
				  unsigned int keywen)
{
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(aead);
	stwuct zynqmp_aead_tfm_ctx *tfm_ctx =
			(stwuct zynqmp_aead_tfm_ctx *)cwypto_tfm_ctx(tfm);
	unsigned chaw keyswc;

	if (keywen == ZYNQMP_KEY_SWC_SEW_KEY_WEN) {
		keyswc = *key;
		if (keyswc == ZYNQMP_AES_KUP_KEY ||
		    keyswc == ZYNQMP_AES_DEV_KEY ||
		    keyswc == ZYNQMP_AES_PUF_KEY) {
			tfm_ctx->keyswc = (enum zynqmp_aead_keyswc)keyswc;
		} ewse {
			tfm_ctx->keywen = keywen;
		}
	} ewse {
		tfm_ctx->keywen = keywen;
		if (keywen == ZYNQMP_AES_KEY_SIZE) {
			tfm_ctx->keyswc = ZYNQMP_AES_KUP_KEY;
			memcpy(tfm_ctx->key, key, keywen);
		}
	}

	tfm_ctx->fbk_ciphew->base.cwt_fwags &= ~CWYPTO_TFM_WEQ_MASK;
	tfm_ctx->fbk_ciphew->base.cwt_fwags |= (aead->base.cwt_fwags &
					CWYPTO_TFM_WEQ_MASK);

	wetuwn cwypto_aead_setkey(tfm_ctx->fbk_ciphew, key, keywen);
}

static int zynqmp_aes_aead_setauthsize(stwuct cwypto_aead *aead,
				       unsigned int authsize)
{
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(aead);
	stwuct zynqmp_aead_tfm_ctx *tfm_ctx =
			(stwuct zynqmp_aead_tfm_ctx *)cwypto_tfm_ctx(tfm);

	tfm_ctx->authsize = authsize;
	wetuwn cwypto_aead_setauthsize(tfm_ctx->fbk_ciphew, authsize);
}

static int zynqmp_aes_aead_encwypt(stwuct aead_wequest *weq)
{
	stwuct zynqmp_aead_dwv_ctx *dwv_ctx;
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct aead_awg *awg = cwypto_aead_awg(aead);
	stwuct zynqmp_aead_weq_ctx *wq_ctx = aead_wequest_ctx(weq);

	wq_ctx->op = ZYNQMP_AES_ENCWYPT;
	dwv_ctx = containew_of(awg, stwuct zynqmp_aead_dwv_ctx, awg.aead.base);

	wetuwn cwypto_twansfew_aead_wequest_to_engine(dwv_ctx->engine, weq);
}

static int zynqmp_aes_aead_decwypt(stwuct aead_wequest *weq)
{
	stwuct zynqmp_aead_dwv_ctx *dwv_ctx;
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct aead_awg *awg = cwypto_aead_awg(aead);
	stwuct zynqmp_aead_weq_ctx *wq_ctx = aead_wequest_ctx(weq);

	wq_ctx->op = ZYNQMP_AES_DECWYPT;
	dwv_ctx = containew_of(awg, stwuct zynqmp_aead_dwv_ctx, awg.aead.base);

	wetuwn cwypto_twansfew_aead_wequest_to_engine(dwv_ctx->engine, weq);
}

static int zynqmp_aes_aead_init(stwuct cwypto_aead *aead)
{
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(aead);
	stwuct zynqmp_aead_tfm_ctx *tfm_ctx =
		(stwuct zynqmp_aead_tfm_ctx *)cwypto_tfm_ctx(tfm);
	stwuct zynqmp_aead_dwv_ctx *dwv_ctx;
	stwuct aead_awg *awg = cwypto_aead_awg(aead);

	dwv_ctx = containew_of(awg, stwuct zynqmp_aead_dwv_ctx, awg.aead.base);
	tfm_ctx->dev = dwv_ctx->dev;

	tfm_ctx->fbk_ciphew = cwypto_awwoc_aead(dwv_ctx->awg.aead.base.base.cwa_name,
						0,
						CWYPTO_AWG_NEED_FAWWBACK);

	if (IS_EWW(tfm_ctx->fbk_ciphew)) {
		pw_eww("%s() Ewwow: faiwed to awwocate fawwback fow %s\n",
		       __func__, dwv_ctx->awg.aead.base.base.cwa_name);
		wetuwn PTW_EWW(tfm_ctx->fbk_ciphew);
	}

	cwypto_aead_set_weqsize(aead,
				max(sizeof(stwuct zynqmp_aead_weq_ctx),
				    sizeof(stwuct aead_wequest) +
				    cwypto_aead_weqsize(tfm_ctx->fbk_ciphew)));
	wetuwn 0;
}

static void zynqmp_aes_aead_exit(stwuct cwypto_aead *aead)
{
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(aead);
	stwuct zynqmp_aead_tfm_ctx *tfm_ctx =
			(stwuct zynqmp_aead_tfm_ctx *)cwypto_tfm_ctx(tfm);

	if (tfm_ctx->fbk_ciphew) {
		cwypto_fwee_aead(tfm_ctx->fbk_ciphew);
		tfm_ctx->fbk_ciphew = NUWW;
	}
	memzewo_expwicit(tfm_ctx, sizeof(stwuct zynqmp_aead_tfm_ctx));
}

static stwuct zynqmp_aead_dwv_ctx aes_dwv_ctx = {
	.awg.aead.base = {
		.setkey		= zynqmp_aes_aead_setkey,
		.setauthsize	= zynqmp_aes_aead_setauthsize,
		.encwypt	= zynqmp_aes_aead_encwypt,
		.decwypt	= zynqmp_aes_aead_decwypt,
		.init		= zynqmp_aes_aead_init,
		.exit		= zynqmp_aes_aead_exit,
		.ivsize		= GCM_AES_IV_SIZE,
		.maxauthsize	= ZYNQMP_AES_AUTH_SIZE,
		.base = {
		.cwa_name		= "gcm(aes)",
		.cwa_dwivew_name	= "xiwinx-zynqmp-aes-gcm",
		.cwa_pwiowity		= 200,
		.cwa_fwags		= CWYPTO_AWG_TYPE_AEAD |
					  CWYPTO_AWG_ASYNC |
					  CWYPTO_AWG_AWWOCATES_MEMOWY |
					  CWYPTO_AWG_KEWN_DWIVEW_ONWY |
					  CWYPTO_AWG_NEED_FAWWBACK,
		.cwa_bwocksize		= ZYNQMP_AES_BWK_SIZE,
		.cwa_ctxsize		= sizeof(stwuct zynqmp_aead_tfm_ctx),
		.cwa_moduwe		= THIS_MODUWE,
		}
	},
	.awg.aead.op = {
		.do_one_wequest = zynqmp_handwe_aes_weq,
	},
};

static int zynqmp_aes_aead_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int eww;

	/* ZynqMP AES dwivew suppowts onwy one instance */
	if (!aes_dwv_ctx.dev)
		aes_dwv_ctx.dev = dev;
	ewse
		wetuwn -ENODEV;

	eww = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(ZYNQMP_DMA_BIT_MASK));
	if (eww < 0) {
		dev_eww(dev, "No usabwe DMA configuwation\n");
		wetuwn eww;
	}

	aes_dwv_ctx.engine = cwypto_engine_awwoc_init(dev, 1);
	if (!aes_dwv_ctx.engine) {
		dev_eww(dev, "Cannot awwoc AES engine\n");
		eww = -ENOMEM;
		goto eww_engine;
	}

	eww = cwypto_engine_stawt(aes_dwv_ctx.engine);
	if (eww) {
		dev_eww(dev, "Cannot stawt AES engine\n");
		goto eww_engine;
	}

	eww = cwypto_engine_wegistew_aead(&aes_dwv_ctx.awg.aead);
	if (eww < 0) {
		dev_eww(dev, "Faiwed to wegistew AEAD awg.\n");
		goto eww_aead;
	}
	wetuwn 0;

eww_aead:
	cwypto_engine_unwegistew_aead(&aes_dwv_ctx.awg.aead);

eww_engine:
	if (aes_dwv_ctx.engine)
		cwypto_engine_exit(aes_dwv_ctx.engine);

	wetuwn eww;
}

static void zynqmp_aes_aead_wemove(stwuct pwatfowm_device *pdev)
{
	cwypto_engine_exit(aes_dwv_ctx.engine);
	cwypto_engine_unwegistew_aead(&aes_dwv_ctx.awg.aead);
}

static const stwuct of_device_id zynqmp_aes_dt_ids[] = {
	{ .compatibwe = "xwnx,zynqmp-aes" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, zynqmp_aes_dt_ids);

static stwuct pwatfowm_dwivew zynqmp_aes_dwivew = {
	.pwobe	= zynqmp_aes_aead_pwobe,
	.wemove_new = zynqmp_aes_aead_wemove,
	.dwivew = {
		.name		= "zynqmp-aes",
		.of_match_tabwe = zynqmp_aes_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(zynqmp_aes_dwivew);
MODUWE_WICENSE("GPW");
