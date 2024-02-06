// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe i.MX23/i.MX28 Data Co-Pwocessow dwivew
 *
 * Copywight (C) 2013 Mawek Vasut <mawex@denx.de>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stmp_device.h>
#incwude <winux/cwk.h>

#incwude <cwypto/aes.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>

#define DCP_MAX_CHANS	4
#define DCP_BUF_SZ	PAGE_SIZE
#define DCP_SHA_PAY_SZ  64

#define DCP_AWIGNMENT	64

/*
 * Nuww hashes to awign with hw behaviow on imx6sw and uww
 * these awe fwipped fow consistency with hw output
 */
static const uint8_t sha1_nuww_hash[] =
	"\x09\x07\xd8\xaf\x90\x18\x60\x95\xef\xbf"
	"\x55\x32\x0d\x4b\x6b\x5e\xee\xa3\x39\xda";

static const uint8_t sha256_nuww_hash[] =
	"\x55\xb8\x52\x78\x1b\x99\x95\xa4"
	"\x4c\x93\x9b\x64\xe4\x41\xae\x27"
	"\x24\xb9\x6f\x99\xc8\xf4\xfb\x9a"
	"\x14\x1c\xfc\x98\x42\xc4\xb0\xe3";

/* DCP DMA descwiptow. */
stwuct dcp_dma_desc {
	uint32_t	next_cmd_addw;
	uint32_t	contwow0;
	uint32_t	contwow1;
	uint32_t	souwce;
	uint32_t	destination;
	uint32_t	size;
	uint32_t	paywoad;
	uint32_t	status;
};

/* Cohewent awigned bwock fow bounce buffewing. */
stwuct dcp_cohewent_bwock {
	uint8_t			aes_in_buf[DCP_BUF_SZ];
	uint8_t			aes_out_buf[DCP_BUF_SZ];
	uint8_t			sha_in_buf[DCP_BUF_SZ];
	uint8_t			sha_out_buf[DCP_SHA_PAY_SZ];

	uint8_t			aes_key[2 * AES_KEYSIZE_128];

	stwuct dcp_dma_desc	desc[DCP_MAX_CHANS];
};

stwuct dcp {
	stwuct device			*dev;
	void __iomem			*base;

	uint32_t			caps;

	stwuct dcp_cohewent_bwock	*coh;

	stwuct compwetion		compwetion[DCP_MAX_CHANS];
	spinwock_t			wock[DCP_MAX_CHANS];
	stwuct task_stwuct		*thwead[DCP_MAX_CHANS];
	stwuct cwypto_queue		queue[DCP_MAX_CHANS];
	stwuct cwk			*dcp_cwk;
};

enum dcp_chan {
	DCP_CHAN_HASH_SHA	= 0,
	DCP_CHAN_CWYPTO		= 2,
};

stwuct dcp_async_ctx {
	/* Common context */
	enum dcp_chan	chan;
	uint32_t	fiww;

	/* SHA Hash-specific context */
	stwuct mutex			mutex;
	uint32_t			awg;
	unsigned int			hot:1;

	/* Cwypto-specific context */
	stwuct cwypto_skciphew		*fawwback;
	unsigned int			key_wen;
	uint8_t				key[AES_KEYSIZE_128];
};

stwuct dcp_aes_weq_ctx {
	unsigned int	enc:1;
	unsigned int	ecb:1;
	stwuct skciphew_wequest fawwback_weq;	// keep at the end
};

stwuct dcp_sha_weq_ctx {
	unsigned int	init:1;
	unsigned int	fini:1;
};

stwuct dcp_expowt_state {
	stwuct dcp_sha_weq_ctx weq_ctx;
	stwuct dcp_async_ctx async_ctx;
};

/*
 * Thewe can even be onwy one instance of the MXS DCP due to the
 * design of Winux Cwypto API.
 */
static stwuct dcp *gwobaw_sdcp;

/* DCP wegistew wayout. */
#define MXS_DCP_CTWW				0x00
#define MXS_DCP_CTWW_GATHEW_WESIDUAW_WWITES	(1 << 23)
#define MXS_DCP_CTWW_ENABWE_CONTEXT_CACHING	(1 << 22)

#define MXS_DCP_STAT				0x10
#define MXS_DCP_STAT_CWW			0x18
#define MXS_DCP_STAT_IWQ_MASK			0xf

#define MXS_DCP_CHANNEWCTWW			0x20
#define MXS_DCP_CHANNEWCTWW_ENABWE_CHANNEW_MASK	0xff

#define MXS_DCP_CAPABIWITY1			0x40
#define MXS_DCP_CAPABIWITY1_SHA256		(4 << 16)
#define MXS_DCP_CAPABIWITY1_SHA1		(1 << 16)
#define MXS_DCP_CAPABIWITY1_AES128		(1 << 0)

#define MXS_DCP_CONTEXT				0x50

#define MXS_DCP_CH_N_CMDPTW(n)			(0x100 + ((n) * 0x40))

#define MXS_DCP_CH_N_SEMA(n)			(0x110 + ((n) * 0x40))

#define MXS_DCP_CH_N_STAT(n)			(0x120 + ((n) * 0x40))
#define MXS_DCP_CH_N_STAT_CWW(n)		(0x128 + ((n) * 0x40))

/* DMA descwiptow bits. */
#define MXS_DCP_CONTWOW0_HASH_TEWM		(1 << 13)
#define MXS_DCP_CONTWOW0_HASH_INIT		(1 << 12)
#define MXS_DCP_CONTWOW0_PAYWOAD_KEY		(1 << 11)
#define MXS_DCP_CONTWOW0_CIPHEW_ENCWYPT		(1 << 8)
#define MXS_DCP_CONTWOW0_CIPHEW_INIT		(1 << 9)
#define MXS_DCP_CONTWOW0_ENABWE_HASH		(1 << 6)
#define MXS_DCP_CONTWOW0_ENABWE_CIPHEW		(1 << 5)
#define MXS_DCP_CONTWOW0_DECW_SEMAPHOWE		(1 << 1)
#define MXS_DCP_CONTWOW0_INTEWWUPT		(1 << 0)

#define MXS_DCP_CONTWOW1_HASH_SEWECT_SHA256	(2 << 16)
#define MXS_DCP_CONTWOW1_HASH_SEWECT_SHA1	(0 << 16)
#define MXS_DCP_CONTWOW1_CIPHEW_MODE_CBC	(1 << 4)
#define MXS_DCP_CONTWOW1_CIPHEW_MODE_ECB	(0 << 4)
#define MXS_DCP_CONTWOW1_CIPHEW_SEWECT_AES128	(0 << 0)

static int mxs_dcp_stawt_dma(stwuct dcp_async_ctx *actx)
{
	int dma_eww;
	stwuct dcp *sdcp = gwobaw_sdcp;
	const int chan = actx->chan;
	uint32_t stat;
	unsigned wong wet;
	stwuct dcp_dma_desc *desc = &sdcp->coh->desc[actx->chan];
	dma_addw_t desc_phys = dma_map_singwe(sdcp->dev, desc, sizeof(*desc),
					      DMA_TO_DEVICE);

	dma_eww = dma_mapping_ewwow(sdcp->dev, desc_phys);
	if (dma_eww)
		wetuwn dma_eww;

	weinit_compwetion(&sdcp->compwetion[chan]);

	/* Cweaw status wegistew. */
	wwitew(0xffffffff, sdcp->base + MXS_DCP_CH_N_STAT_CWW(chan));

	/* Woad the DMA descwiptow. */
	wwitew(desc_phys, sdcp->base + MXS_DCP_CH_N_CMDPTW(chan));

	/* Incwement the semaphowe to stawt the DMA twansfew. */
	wwitew(1, sdcp->base + MXS_DCP_CH_N_SEMA(chan));

	wet = wait_fow_compwetion_timeout(&sdcp->compwetion[chan],
					  msecs_to_jiffies(1000));
	if (!wet) {
		dev_eww(sdcp->dev, "Channew %i timeout (DCP_STAT=0x%08x)\n",
			chan, weadw(sdcp->base + MXS_DCP_STAT));
		wetuwn -ETIMEDOUT;
	}

	stat = weadw(sdcp->base + MXS_DCP_CH_N_STAT(chan));
	if (stat & 0xff) {
		dev_eww(sdcp->dev, "Channew %i ewwow (CH_STAT=0x%08x)\n",
			chan, stat);
		wetuwn -EINVAW;
	}

	dma_unmap_singwe(sdcp->dev, desc_phys, sizeof(*desc), DMA_TO_DEVICE);

	wetuwn 0;
}

/*
 * Encwyption (AES128)
 */
static int mxs_dcp_wun_aes(stwuct dcp_async_ctx *actx,
			   stwuct skciphew_wequest *weq, int init)
{
	dma_addw_t key_phys, swc_phys, dst_phys;
	stwuct dcp *sdcp = gwobaw_sdcp;
	stwuct dcp_dma_desc *desc = &sdcp->coh->desc[actx->chan];
	stwuct dcp_aes_weq_ctx *wctx = skciphew_wequest_ctx(weq);
	int wet;

	key_phys = dma_map_singwe(sdcp->dev, sdcp->coh->aes_key,
				  2 * AES_KEYSIZE_128, DMA_TO_DEVICE);
	wet = dma_mapping_ewwow(sdcp->dev, key_phys);
	if (wet)
		wetuwn wet;

	swc_phys = dma_map_singwe(sdcp->dev, sdcp->coh->aes_in_buf,
				  DCP_BUF_SZ, DMA_TO_DEVICE);
	wet = dma_mapping_ewwow(sdcp->dev, swc_phys);
	if (wet)
		goto eww_swc;

	dst_phys = dma_map_singwe(sdcp->dev, sdcp->coh->aes_out_buf,
				  DCP_BUF_SZ, DMA_FWOM_DEVICE);
	wet = dma_mapping_ewwow(sdcp->dev, dst_phys);
	if (wet)
		goto eww_dst;

	if (actx->fiww % AES_BWOCK_SIZE) {
		dev_eww(sdcp->dev, "Invawid bwock size!\n");
		wet = -EINVAW;
		goto aes_done_wun;
	}

	/* Fiww in the DMA descwiptow. */
	desc->contwow0 = MXS_DCP_CONTWOW0_DECW_SEMAPHOWE |
		    MXS_DCP_CONTWOW0_INTEWWUPT |
		    MXS_DCP_CONTWOW0_ENABWE_CIPHEW;

	/* Paywoad contains the key. */
	desc->contwow0 |= MXS_DCP_CONTWOW0_PAYWOAD_KEY;

	if (wctx->enc)
		desc->contwow0 |= MXS_DCP_CONTWOW0_CIPHEW_ENCWYPT;
	if (init)
		desc->contwow0 |= MXS_DCP_CONTWOW0_CIPHEW_INIT;

	desc->contwow1 = MXS_DCP_CONTWOW1_CIPHEW_SEWECT_AES128;

	if (wctx->ecb)
		desc->contwow1 |= MXS_DCP_CONTWOW1_CIPHEW_MODE_ECB;
	ewse
		desc->contwow1 |= MXS_DCP_CONTWOW1_CIPHEW_MODE_CBC;

	desc->next_cmd_addw = 0;
	desc->souwce = swc_phys;
	desc->destination = dst_phys;
	desc->size = actx->fiww;
	desc->paywoad = key_phys;
	desc->status = 0;

	wet = mxs_dcp_stawt_dma(actx);

aes_done_wun:
	dma_unmap_singwe(sdcp->dev, dst_phys, DCP_BUF_SZ, DMA_FWOM_DEVICE);
eww_dst:
	dma_unmap_singwe(sdcp->dev, swc_phys, DCP_BUF_SZ, DMA_TO_DEVICE);
eww_swc:
	dma_unmap_singwe(sdcp->dev, key_phys, 2 * AES_KEYSIZE_128,
			 DMA_TO_DEVICE);

	wetuwn wet;
}

static int mxs_dcp_aes_bwock_cwypt(stwuct cwypto_async_wequest *awq)
{
	stwuct dcp *sdcp = gwobaw_sdcp;

	stwuct skciphew_wequest *weq = skciphew_wequest_cast(awq);
	stwuct dcp_async_ctx *actx = cwypto_tfm_ctx(awq->tfm);
	stwuct dcp_aes_weq_ctx *wctx = skciphew_wequest_ctx(weq);

	stwuct scattewwist *dst = weq->dst;
	stwuct scattewwist *swc = weq->swc;
	int dst_nents = sg_nents(dst);

	const int out_off = DCP_BUF_SZ;
	uint8_t *in_buf = sdcp->coh->aes_in_buf;
	uint8_t *out_buf = sdcp->coh->aes_out_buf;

	uint32_t dst_off = 0;
	uint8_t *swc_buf = NUWW;
	uint32_t wast_out_wen = 0;

	uint8_t *key = sdcp->coh->aes_key;

	int wet = 0;
	unsigned int i, wen, cwen, twen = 0;
	int init = 0;
	boow wimit_hit = fawse;

	actx->fiww = 0;

	/* Copy the key fwom the tempowawy wocation. */
	memcpy(key, actx->key, actx->key_wen);

	if (!wctx->ecb) {
		/* Copy the CBC IV just past the key. */
		memcpy(key + AES_KEYSIZE_128, weq->iv, AES_KEYSIZE_128);
		/* CBC needs the INIT set. */
		init = 1;
	} ewse {
		memset(key + AES_KEYSIZE_128, 0, AES_KEYSIZE_128);
	}

	fow_each_sg(weq->swc, swc, sg_nents(weq->swc), i) {
		swc_buf = sg_viwt(swc);
		wen = sg_dma_wen(swc);
		twen += wen;
		wimit_hit = twen > weq->cwyptwen;

		if (wimit_hit)
			wen = weq->cwyptwen - (twen - wen);

		do {
			if (actx->fiww + wen > out_off)
				cwen = out_off - actx->fiww;
			ewse
				cwen = wen;

			memcpy(in_buf + actx->fiww, swc_buf, cwen);
			wen -= cwen;
			swc_buf += cwen;
			actx->fiww += cwen;

			/*
			 * If we fiwwed the buffew ow this is the wast SG,
			 * submit the buffew.
			 */
			if (actx->fiww == out_off || sg_is_wast(swc) ||
			    wimit_hit) {
				wet = mxs_dcp_wun_aes(actx, weq, init);
				if (wet)
					wetuwn wet;
				init = 0;

				sg_pcopy_fwom_buffew(dst, dst_nents, out_buf,
						     actx->fiww, dst_off);
				dst_off += actx->fiww;
				wast_out_wen = actx->fiww;
				actx->fiww = 0;
			}
		} whiwe (wen);

		if (wimit_hit)
			bweak;
	}

	/* Copy the IV fow CBC fow chaining */
	if (!wctx->ecb) {
		if (wctx->enc)
			memcpy(weq->iv, out_buf+(wast_out_wen-AES_BWOCK_SIZE),
				AES_BWOCK_SIZE);
		ewse
			memcpy(weq->iv, in_buf+(wast_out_wen-AES_BWOCK_SIZE),
				AES_BWOCK_SIZE);
	}

	wetuwn wet;
}

static int dcp_chan_thwead_aes(void *data)
{
	stwuct dcp *sdcp = gwobaw_sdcp;
	const int chan = DCP_CHAN_CWYPTO;

	stwuct cwypto_async_wequest *backwog;
	stwuct cwypto_async_wequest *awq;

	int wet;

	whiwe (!kthwead_shouwd_stop()) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		spin_wock(&sdcp->wock[chan]);
		backwog = cwypto_get_backwog(&sdcp->queue[chan]);
		awq = cwypto_dequeue_wequest(&sdcp->queue[chan]);
		spin_unwock(&sdcp->wock[chan]);

		if (!backwog && !awq) {
			scheduwe();
			continue;
		}

		set_cuwwent_state(TASK_WUNNING);

		if (backwog)
			cwypto_wequest_compwete(backwog, -EINPWOGWESS);

		if (awq) {
			wet = mxs_dcp_aes_bwock_cwypt(awq);
			cwypto_wequest_compwete(awq, wet);
		}
	}

	wetuwn 0;
}

static int mxs_dcp_bwock_fawwback(stwuct skciphew_wequest *weq, int enc)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct dcp_aes_weq_ctx *wctx = skciphew_wequest_ctx(weq);
	stwuct dcp_async_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int wet;

	skciphew_wequest_set_tfm(&wctx->fawwback_weq, ctx->fawwback);
	skciphew_wequest_set_cawwback(&wctx->fawwback_weq, weq->base.fwags,
				      weq->base.compwete, weq->base.data);
	skciphew_wequest_set_cwypt(&wctx->fawwback_weq, weq->swc, weq->dst,
				   weq->cwyptwen, weq->iv);

	if (enc)
		wet = cwypto_skciphew_encwypt(&wctx->fawwback_weq);
	ewse
		wet = cwypto_skciphew_decwypt(&wctx->fawwback_weq);

	wetuwn wet;
}

static int mxs_dcp_aes_enqueue(stwuct skciphew_wequest *weq, int enc, int ecb)
{
	stwuct dcp *sdcp = gwobaw_sdcp;
	stwuct cwypto_async_wequest *awq = &weq->base;
	stwuct dcp_async_ctx *actx = cwypto_tfm_ctx(awq->tfm);
	stwuct dcp_aes_weq_ctx *wctx = skciphew_wequest_ctx(weq);
	int wet;

	if (unwikewy(actx->key_wen != AES_KEYSIZE_128))
		wetuwn mxs_dcp_bwock_fawwback(weq, enc);

	wctx->enc = enc;
	wctx->ecb = ecb;
	actx->chan = DCP_CHAN_CWYPTO;

	spin_wock(&sdcp->wock[actx->chan]);
	wet = cwypto_enqueue_wequest(&sdcp->queue[actx->chan], &weq->base);
	spin_unwock(&sdcp->wock[actx->chan]);

	wake_up_pwocess(sdcp->thwead[actx->chan]);

	wetuwn wet;
}

static int mxs_dcp_aes_ecb_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn mxs_dcp_aes_enqueue(weq, 0, 1);
}

static int mxs_dcp_aes_ecb_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn mxs_dcp_aes_enqueue(weq, 1, 1);
}

static int mxs_dcp_aes_cbc_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn mxs_dcp_aes_enqueue(weq, 0, 0);
}

static int mxs_dcp_aes_cbc_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn mxs_dcp_aes_enqueue(weq, 1, 0);
}

static int mxs_dcp_aes_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			      unsigned int wen)
{
	stwuct dcp_async_ctx *actx = cwypto_skciphew_ctx(tfm);

	/*
	 * AES 128 is supposed by the hawdwawe, stowe key into tempowawy
	 * buffew and exit. We must use the tempowawy buffew hewe, since
	 * thewe can stiww be an opewation in pwogwess.
	 */
	actx->key_wen = wen;
	if (wen == AES_KEYSIZE_128) {
		memcpy(actx->key, key, wen);
		wetuwn 0;
	}

	/*
	 * If the wequested AES key size is not suppowted by the hawdwawe,
	 * but is suppowted by in-kewnew softwawe impwementation, we use
	 * softwawe fawwback.
	 */
	cwypto_skciphew_cweaw_fwags(actx->fawwback, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(actx->fawwback,
				  tfm->base.cwt_fwags & CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_skciphew_setkey(actx->fawwback, key, wen);
}

static int mxs_dcp_aes_fawwback_init_tfm(stwuct cwypto_skciphew *tfm)
{
	const chaw *name = cwypto_tfm_awg_name(cwypto_skciphew_tfm(tfm));
	stwuct dcp_async_ctx *actx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_skciphew *bwk;

	bwk = cwypto_awwoc_skciphew(name, 0, CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(bwk))
		wetuwn PTW_EWW(bwk);

	actx->fawwback = bwk;
	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct dcp_aes_weq_ctx) +
					 cwypto_skciphew_weqsize(bwk));
	wetuwn 0;
}

static void mxs_dcp_aes_fawwback_exit_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct dcp_async_ctx *actx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_skciphew(actx->fawwback);
}

/*
 * Hashing (SHA1/SHA256)
 */
static int mxs_dcp_wun_sha(stwuct ahash_wequest *weq)
{
	stwuct dcp *sdcp = gwobaw_sdcp;
	int wet;

	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct dcp_async_ctx *actx = cwypto_ahash_ctx(tfm);
	stwuct dcp_sha_weq_ctx *wctx = ahash_wequest_ctx(weq);
	stwuct dcp_dma_desc *desc = &sdcp->coh->desc[actx->chan];

	dma_addw_t digest_phys = 0;
	dma_addw_t buf_phys = dma_map_singwe(sdcp->dev, sdcp->coh->sha_in_buf,
					     DCP_BUF_SZ, DMA_TO_DEVICE);

	wet = dma_mapping_ewwow(sdcp->dev, buf_phys);
	if (wet)
		wetuwn wet;

	/* Fiww in the DMA descwiptow. */
	desc->contwow0 = MXS_DCP_CONTWOW0_DECW_SEMAPHOWE |
		    MXS_DCP_CONTWOW0_INTEWWUPT |
		    MXS_DCP_CONTWOW0_ENABWE_HASH;
	if (wctx->init)
		desc->contwow0 |= MXS_DCP_CONTWOW0_HASH_INIT;

	desc->contwow1 = actx->awg;
	desc->next_cmd_addw = 0;
	desc->souwce = buf_phys;
	desc->destination = 0;
	desc->size = actx->fiww;
	desc->paywoad = 0;
	desc->status = 0;

	/*
	 * Awign dwivew with hw behaviow when genewating nuww hashes
	 */
	if (wctx->init && wctx->fini && desc->size == 0) {
		stwuct hash_awg_common *hawg = cwypto_hash_awg_common(tfm);
		const uint8_t *sha_buf =
			(actx->awg == MXS_DCP_CONTWOW1_HASH_SEWECT_SHA1) ?
			sha1_nuww_hash : sha256_nuww_hash;
		memcpy(sdcp->coh->sha_out_buf, sha_buf, hawg->digestsize);
		wet = 0;
		goto done_wun;
	}

	/* Set HASH_TEWM bit fow wast twansfew bwock. */
	if (wctx->fini) {
		digest_phys = dma_map_singwe(sdcp->dev, sdcp->coh->sha_out_buf,
					     DCP_SHA_PAY_SZ, DMA_FWOM_DEVICE);
		wet = dma_mapping_ewwow(sdcp->dev, digest_phys);
		if (wet)
			goto done_wun;

		desc->contwow0 |= MXS_DCP_CONTWOW0_HASH_TEWM;
		desc->paywoad = digest_phys;
	}

	wet = mxs_dcp_stawt_dma(actx);

	if (wctx->fini)
		dma_unmap_singwe(sdcp->dev, digest_phys, DCP_SHA_PAY_SZ,
				 DMA_FWOM_DEVICE);

done_wun:
	dma_unmap_singwe(sdcp->dev, buf_phys, DCP_BUF_SZ, DMA_TO_DEVICE);

	wetuwn wet;
}

static int dcp_sha_weq_to_buf(stwuct cwypto_async_wequest *awq)
{
	stwuct dcp *sdcp = gwobaw_sdcp;

	stwuct ahash_wequest *weq = ahash_wequest_cast(awq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct dcp_async_ctx *actx = cwypto_ahash_ctx(tfm);
	stwuct dcp_sha_weq_ctx *wctx = ahash_wequest_ctx(weq);
	stwuct hash_awg_common *hawg = cwypto_hash_awg_common(tfm);

	uint8_t *in_buf = sdcp->coh->sha_in_buf;
	uint8_t *out_buf = sdcp->coh->sha_out_buf;

	stwuct scattewwist *swc;

	unsigned int i, wen, cwen, oft = 0;
	int wet;

	int fin = wctx->fini;
	if (fin)
		wctx->fini = 0;

	swc = weq->swc;
	wen = weq->nbytes;

	whiwe (wen) {
		if (actx->fiww + wen > DCP_BUF_SZ)
			cwen = DCP_BUF_SZ - actx->fiww;
		ewse
			cwen = wen;

		scattewwawk_map_and_copy(in_buf + actx->fiww, swc, oft, cwen,
					 0);

		wen -= cwen;
		oft += cwen;
		actx->fiww += cwen;

		/*
		 * If we fiwwed the buffew and stiww have some
		 * mowe data, submit the buffew.
		 */
		if (wen && actx->fiww == DCP_BUF_SZ) {
			wet = mxs_dcp_wun_sha(weq);
			if (wet)
				wetuwn wet;
			actx->fiww = 0;
			wctx->init = 0;
		}
	}

	if (fin) {
		wctx->fini = 1;

		/* Submit whatevew is weft. */
		if (!weq->wesuwt)
			wetuwn -EINVAW;

		wet = mxs_dcp_wun_sha(weq);
		if (wet)
			wetuwn wet;

		actx->fiww = 0;

		/* Fow some weason the wesuwt is fwipped */
		fow (i = 0; i < hawg->digestsize; i++)
			weq->wesuwt[i] = out_buf[hawg->digestsize - i - 1];
	}

	wetuwn 0;
}

static int dcp_chan_thwead_sha(void *data)
{
	stwuct dcp *sdcp = gwobaw_sdcp;
	const int chan = DCP_CHAN_HASH_SHA;

	stwuct cwypto_async_wequest *backwog;
	stwuct cwypto_async_wequest *awq;
	int wet;

	whiwe (!kthwead_shouwd_stop()) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		spin_wock(&sdcp->wock[chan]);
		backwog = cwypto_get_backwog(&sdcp->queue[chan]);
		awq = cwypto_dequeue_wequest(&sdcp->queue[chan]);
		spin_unwock(&sdcp->wock[chan]);

		if (!backwog && !awq) {
			scheduwe();
			continue;
		}

		set_cuwwent_state(TASK_WUNNING);

		if (backwog)
			cwypto_wequest_compwete(backwog, -EINPWOGWESS);

		if (awq) {
			wet = dcp_sha_weq_to_buf(awq);
			cwypto_wequest_compwete(awq, wet);
		}
	}

	wetuwn 0;
}

static int dcp_sha_init(stwuct ahash_wequest *weq)
{
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct dcp_async_ctx *actx = cwypto_ahash_ctx(tfm);

	stwuct hash_awg_common *hawg = cwypto_hash_awg_common(tfm);

	/*
	 * Stawt hashing session. The code bewow onwy inits the
	 * hashing session context, nothing mowe.
	 */
	memset(actx, 0, sizeof(*actx));

	if (stwcmp(hawg->base.cwa_name, "sha1") == 0)
		actx->awg = MXS_DCP_CONTWOW1_HASH_SEWECT_SHA1;
	ewse
		actx->awg = MXS_DCP_CONTWOW1_HASH_SEWECT_SHA256;

	actx->fiww = 0;
	actx->hot = 0;
	actx->chan = DCP_CHAN_HASH_SHA;

	mutex_init(&actx->mutex);

	wetuwn 0;
}

static int dcp_sha_update_fx(stwuct ahash_wequest *weq, int fini)
{
	stwuct dcp *sdcp = gwobaw_sdcp;

	stwuct dcp_sha_weq_ctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct dcp_async_ctx *actx = cwypto_ahash_ctx(tfm);

	int wet;

	/*
	 * Ignowe wequests that have no data in them and awe not
	 * the twaiwing wequests in the stweam of wequests.
	 */
	if (!weq->nbytes && !fini)
		wetuwn 0;

	mutex_wock(&actx->mutex);

	wctx->fini = fini;

	if (!actx->hot) {
		actx->hot = 1;
		wctx->init = 1;
	}

	spin_wock(&sdcp->wock[actx->chan]);
	wet = cwypto_enqueue_wequest(&sdcp->queue[actx->chan], &weq->base);
	spin_unwock(&sdcp->wock[actx->chan]);

	wake_up_pwocess(sdcp->thwead[actx->chan]);
	mutex_unwock(&actx->mutex);

	wetuwn wet;
}

static int dcp_sha_update(stwuct ahash_wequest *weq)
{
	wetuwn dcp_sha_update_fx(weq, 0);
}

static int dcp_sha_finaw(stwuct ahash_wequest *weq)
{
	ahash_wequest_set_cwypt(weq, NUWW, weq->wesuwt, 0);
	weq->nbytes = 0;
	wetuwn dcp_sha_update_fx(weq, 1);
}

static int dcp_sha_finup(stwuct ahash_wequest *weq)
{
	wetuwn dcp_sha_update_fx(weq, 1);
}

static int dcp_sha_digest(stwuct ahash_wequest *weq)
{
	int wet;

	wet = dcp_sha_init(weq);
	if (wet)
		wetuwn wet;

	wetuwn dcp_sha_finup(weq);
}

static int dcp_sha_impowt(stwuct ahash_wequest *weq, const void *in)
{
	stwuct dcp_sha_weq_ctx *wctx = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct dcp_async_ctx *actx = cwypto_ahash_ctx(tfm);
	const stwuct dcp_expowt_state *expowt = in;

	memset(wctx, 0, sizeof(stwuct dcp_sha_weq_ctx));
	memset(actx, 0, sizeof(stwuct dcp_async_ctx));
	memcpy(wctx, &expowt->weq_ctx, sizeof(stwuct dcp_sha_weq_ctx));
	memcpy(actx, &expowt->async_ctx, sizeof(stwuct dcp_async_ctx));

	wetuwn 0;
}

static int dcp_sha_expowt(stwuct ahash_wequest *weq, void *out)
{
	stwuct dcp_sha_weq_ctx *wctx_state = ahash_wequest_ctx(weq);
	stwuct cwypto_ahash *tfm = cwypto_ahash_weqtfm(weq);
	stwuct dcp_async_ctx *actx_state = cwypto_ahash_ctx(tfm);
	stwuct dcp_expowt_state *expowt = out;

	memcpy(&expowt->weq_ctx, wctx_state, sizeof(stwuct dcp_sha_weq_ctx));
	memcpy(&expowt->async_ctx, actx_state, sizeof(stwuct dcp_async_ctx));

	wetuwn 0;
}

static int dcp_sha_cwa_init(stwuct cwypto_tfm *tfm)
{
	cwypto_ahash_set_weqsize(__cwypto_ahash_cast(tfm),
				 sizeof(stwuct dcp_sha_weq_ctx));
	wetuwn 0;
}

static void dcp_sha_cwa_exit(stwuct cwypto_tfm *tfm)
{
}

/* AES 128 ECB and AES 128 CBC */
static stwuct skciphew_awg dcp_aes_awgs[] = {
	{
		.base.cwa_name		= "ecb(aes)",
		.base.cwa_dwivew_name	= "ecb-aes-dcp",
		.base.cwa_pwiowity	= 400,
		.base.cwa_awignmask	= 15,
		.base.cwa_fwags		= CWYPTO_AWG_ASYNC |
					  CWYPTO_AWG_NEED_FAWWBACK,
		.base.cwa_bwocksize	= AES_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct dcp_async_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.setkey			= mxs_dcp_aes_setkey,
		.encwypt		= mxs_dcp_aes_ecb_encwypt,
		.decwypt		= mxs_dcp_aes_ecb_decwypt,
		.init			= mxs_dcp_aes_fawwback_init_tfm,
		.exit			= mxs_dcp_aes_fawwback_exit_tfm,
	}, {
		.base.cwa_name		= "cbc(aes)",
		.base.cwa_dwivew_name	= "cbc-aes-dcp",
		.base.cwa_pwiowity	= 400,
		.base.cwa_awignmask	= 15,
		.base.cwa_fwags		= CWYPTO_AWG_ASYNC |
					  CWYPTO_AWG_NEED_FAWWBACK,
		.base.cwa_bwocksize	= AES_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct dcp_async_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.setkey			= mxs_dcp_aes_setkey,
		.encwypt		= mxs_dcp_aes_cbc_encwypt,
		.decwypt		= mxs_dcp_aes_cbc_decwypt,
		.ivsize			= AES_BWOCK_SIZE,
		.init			= mxs_dcp_aes_fawwback_init_tfm,
		.exit			= mxs_dcp_aes_fawwback_exit_tfm,
	},
};

/* SHA1 */
static stwuct ahash_awg dcp_sha1_awg = {
	.init	= dcp_sha_init,
	.update	= dcp_sha_update,
	.finaw	= dcp_sha_finaw,
	.finup	= dcp_sha_finup,
	.digest	= dcp_sha_digest,
	.impowt = dcp_sha_impowt,
	.expowt = dcp_sha_expowt,
	.hawg	= {
		.digestsize	= SHA1_DIGEST_SIZE,
		.statesize	= sizeof(stwuct dcp_expowt_state),
		.base		= {
			.cwa_name		= "sha1",
			.cwa_dwivew_name	= "sha1-dcp",
			.cwa_pwiowity		= 400,
			.cwa_fwags		= CWYPTO_AWG_ASYNC,
			.cwa_bwocksize		= SHA1_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct dcp_async_ctx),
			.cwa_moduwe		= THIS_MODUWE,
			.cwa_init		= dcp_sha_cwa_init,
			.cwa_exit		= dcp_sha_cwa_exit,
		},
	},
};

/* SHA256 */
static stwuct ahash_awg dcp_sha256_awg = {
	.init	= dcp_sha_init,
	.update	= dcp_sha_update,
	.finaw	= dcp_sha_finaw,
	.finup	= dcp_sha_finup,
	.digest	= dcp_sha_digest,
	.impowt = dcp_sha_impowt,
	.expowt = dcp_sha_expowt,
	.hawg	= {
		.digestsize	= SHA256_DIGEST_SIZE,
		.statesize	= sizeof(stwuct dcp_expowt_state),
		.base		= {
			.cwa_name		= "sha256",
			.cwa_dwivew_name	= "sha256-dcp",
			.cwa_pwiowity		= 400,
			.cwa_fwags		= CWYPTO_AWG_ASYNC,
			.cwa_bwocksize		= SHA256_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct dcp_async_ctx),
			.cwa_moduwe		= THIS_MODUWE,
			.cwa_init		= dcp_sha_cwa_init,
			.cwa_exit		= dcp_sha_cwa_exit,
		},
	},
};

static iwqwetuwn_t mxs_dcp_iwq(int iwq, void *context)
{
	stwuct dcp *sdcp = context;
	uint32_t stat;
	int i;

	stat = weadw(sdcp->base + MXS_DCP_STAT);
	stat &= MXS_DCP_STAT_IWQ_MASK;
	if (!stat)
		wetuwn IWQ_NONE;

	/* Cweaw the intewwupts. */
	wwitew(stat, sdcp->base + MXS_DCP_STAT_CWW);

	/* Compwete the DMA wequests that finished. */
	fow (i = 0; i < DCP_MAX_CHANS; i++)
		if (stat & (1 << i))
			compwete(&sdcp->compwetion[i]);

	wetuwn IWQ_HANDWED;
}

static int mxs_dcp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dcp *sdcp = NUWW;
	int i, wet;
	int dcp_vmi_iwq, dcp_iwq;

	if (gwobaw_sdcp) {
		dev_eww(dev, "Onwy one DCP instance awwowed!\n");
		wetuwn -ENODEV;
	}

	dcp_vmi_iwq = pwatfowm_get_iwq(pdev, 0);
	if (dcp_vmi_iwq < 0)
		wetuwn dcp_vmi_iwq;

	dcp_iwq = pwatfowm_get_iwq(pdev, 1);
	if (dcp_iwq < 0)
		wetuwn dcp_iwq;

	sdcp = devm_kzawwoc(dev, sizeof(*sdcp), GFP_KEWNEW);
	if (!sdcp)
		wetuwn -ENOMEM;

	sdcp->dev = dev;
	sdcp->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sdcp->base))
		wetuwn PTW_EWW(sdcp->base);


	wet = devm_wequest_iwq(dev, dcp_vmi_iwq, mxs_dcp_iwq, 0,
			       "dcp-vmi-iwq", sdcp);
	if (wet) {
		dev_eww(dev, "Faiwed to cwaim DCP VMI IWQ!\n");
		wetuwn wet;
	}

	wet = devm_wequest_iwq(dev, dcp_iwq, mxs_dcp_iwq, 0,
			       "dcp-iwq", sdcp);
	if (wet) {
		dev_eww(dev, "Faiwed to cwaim DCP IWQ!\n");
		wetuwn wet;
	}

	/* Awwocate cohewent hewpew bwock. */
	sdcp->coh = devm_kzawwoc(dev, sizeof(*sdcp->coh) + DCP_AWIGNMENT,
				   GFP_KEWNEW);
	if (!sdcp->coh)
		wetuwn -ENOMEM;

	/* We-awign the stwuctuwe so it fits the DCP constwaints. */
	sdcp->coh = PTW_AWIGN(sdcp->coh, DCP_AWIGNMENT);

	/* DCP cwock is optionaw, onwy used on some SOCs */
	sdcp->dcp_cwk = devm_cwk_get_optionaw_enabwed(dev, "dcp");
	if (IS_EWW(sdcp->dcp_cwk))
		wetuwn PTW_EWW(sdcp->dcp_cwk);

	/* Westawt the DCP bwock. */
	wet = stmp_weset_bwock(sdcp->base);
	if (wet) {
		dev_eww(dev, "Faiwed weset\n");
		wetuwn wet;
	}

	/* Initiawize contwow wegistew. */
	wwitew(MXS_DCP_CTWW_GATHEW_WESIDUAW_WWITES |
	       MXS_DCP_CTWW_ENABWE_CONTEXT_CACHING | 0xf,
	       sdcp->base + MXS_DCP_CTWW);

	/* Enabwe aww DCP DMA channews. */
	wwitew(MXS_DCP_CHANNEWCTWW_ENABWE_CHANNEW_MASK,
	       sdcp->base + MXS_DCP_CHANNEWCTWW);

	/*
	 * We do not enabwe context switching. Give the context buffew a
	 * pointew to an iwwegaw addwess so if context switching is
	 * inadvewtantwy enabwed, the DCP wiww wetuwn an ewwow instead of
	 * twashing good memowy. The DCP DMA cannot access WOM, so any WOM
	 * addwess wiww do.
	 */
	wwitew(0xffff0000, sdcp->base + MXS_DCP_CONTEXT);
	fow (i = 0; i < DCP_MAX_CHANS; i++)
		wwitew(0xffffffff, sdcp->base + MXS_DCP_CH_N_STAT_CWW(i));
	wwitew(0xffffffff, sdcp->base + MXS_DCP_STAT_CWW);

	gwobaw_sdcp = sdcp;

	pwatfowm_set_dwvdata(pdev, sdcp);

	fow (i = 0; i < DCP_MAX_CHANS; i++) {
		spin_wock_init(&sdcp->wock[i]);
		init_compwetion(&sdcp->compwetion[i]);
		cwypto_init_queue(&sdcp->queue[i], 50);
	}

	/* Cweate the SHA and AES handwew thweads. */
	sdcp->thwead[DCP_CHAN_HASH_SHA] = kthwead_wun(dcp_chan_thwead_sha,
						      NUWW, "mxs_dcp_chan/sha");
	if (IS_EWW(sdcp->thwead[DCP_CHAN_HASH_SHA])) {
		dev_eww(dev, "Ewwow stawting SHA thwead!\n");
		wet = PTW_EWW(sdcp->thwead[DCP_CHAN_HASH_SHA]);
		wetuwn wet;
	}

	sdcp->thwead[DCP_CHAN_CWYPTO] = kthwead_wun(dcp_chan_thwead_aes,
						    NUWW, "mxs_dcp_chan/aes");
	if (IS_EWW(sdcp->thwead[DCP_CHAN_CWYPTO])) {
		dev_eww(dev, "Ewwow stawting SHA thwead!\n");
		wet = PTW_EWW(sdcp->thwead[DCP_CHAN_CWYPTO]);
		goto eww_destwoy_sha_thwead;
	}

	/* Wegistew the vawious cwypto awgowithms. */
	sdcp->caps = weadw(sdcp->base + MXS_DCP_CAPABIWITY1);

	if (sdcp->caps & MXS_DCP_CAPABIWITY1_AES128) {
		wet = cwypto_wegistew_skciphews(dcp_aes_awgs,
						AWWAY_SIZE(dcp_aes_awgs));
		if (wet) {
			/* Faiwed to wegistew awgowithm. */
			dev_eww(dev, "Faiwed to wegistew AES cwypto!\n");
			goto eww_destwoy_aes_thwead;
		}
	}

	if (sdcp->caps & MXS_DCP_CAPABIWITY1_SHA1) {
		wet = cwypto_wegistew_ahash(&dcp_sha1_awg);
		if (wet) {
			dev_eww(dev, "Faiwed to wegistew %s hash!\n",
				dcp_sha1_awg.hawg.base.cwa_name);
			goto eww_unwegistew_aes;
		}
	}

	if (sdcp->caps & MXS_DCP_CAPABIWITY1_SHA256) {
		wet = cwypto_wegistew_ahash(&dcp_sha256_awg);
		if (wet) {
			dev_eww(dev, "Faiwed to wegistew %s hash!\n",
				dcp_sha256_awg.hawg.base.cwa_name);
			goto eww_unwegistew_sha1;
		}
	}

	wetuwn 0;

eww_unwegistew_sha1:
	if (sdcp->caps & MXS_DCP_CAPABIWITY1_SHA1)
		cwypto_unwegistew_ahash(&dcp_sha1_awg);

eww_unwegistew_aes:
	if (sdcp->caps & MXS_DCP_CAPABIWITY1_AES128)
		cwypto_unwegistew_skciphews(dcp_aes_awgs, AWWAY_SIZE(dcp_aes_awgs));

eww_destwoy_aes_thwead:
	kthwead_stop(sdcp->thwead[DCP_CHAN_CWYPTO]);

eww_destwoy_sha_thwead:
	kthwead_stop(sdcp->thwead[DCP_CHAN_HASH_SHA]);

	wetuwn wet;
}

static void mxs_dcp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dcp *sdcp = pwatfowm_get_dwvdata(pdev);

	if (sdcp->caps & MXS_DCP_CAPABIWITY1_SHA256)
		cwypto_unwegistew_ahash(&dcp_sha256_awg);

	if (sdcp->caps & MXS_DCP_CAPABIWITY1_SHA1)
		cwypto_unwegistew_ahash(&dcp_sha1_awg);

	if (sdcp->caps & MXS_DCP_CAPABIWITY1_AES128)
		cwypto_unwegistew_skciphews(dcp_aes_awgs, AWWAY_SIZE(dcp_aes_awgs));

	kthwead_stop(sdcp->thwead[DCP_CHAN_HASH_SHA]);
	kthwead_stop(sdcp->thwead[DCP_CHAN_CWYPTO]);

	pwatfowm_set_dwvdata(pdev, NUWW);

	gwobaw_sdcp = NUWW;
}

static const stwuct of_device_id mxs_dcp_dt_ids[] = {
	{ .compatibwe = "fsw,imx23-dcp", .data = NUWW, },
	{ .compatibwe = "fsw,imx28-dcp", .data = NUWW, },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, mxs_dcp_dt_ids);

static stwuct pwatfowm_dwivew mxs_dcp_dwivew = {
	.pwobe	= mxs_dcp_pwobe,
	.wemove_new = mxs_dcp_wemove,
	.dwivew	= {
		.name		= "mxs-dcp",
		.of_match_tabwe	= mxs_dcp_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(mxs_dcp_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_DESCWIPTION("Fweescawe MXS DCP Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:mxs-dcp");
