// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew IXP4xx NPE-C cwypto dwivew
 *
 * Copywight (C) 2008 Chwistian Hohnstaedt <chohnstaedt@innominate.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/cwypto.h>
#incwude <winux/kewnew.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/gfp.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude <cwypto/ctw.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/hmac.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/authenc.h>
#incwude <cwypto/scattewwawk.h>

#incwude <winux/soc/ixp4xx/npe.h>
#incwude <winux/soc/ixp4xx/qmgw.h>

/* Intewmittent incwudes, dewete this aftew v5.14-wc1 */
#incwude <winux/soc/ixp4xx/cpu.h>

#define MAX_KEYWEN 32

/* hash: cfgwowd + 2 * digestwen; cwypt: keywen + cfgwowd */
#define NPE_CTX_WEN 80
#define AES_BWOCK128 16

#define NPE_OP_HASH_VEWIFY   0x01
#define NPE_OP_CCM_ENABWE    0x04
#define NPE_OP_CWYPT_ENABWE  0x08
#define NPE_OP_HASH_ENABWE   0x10
#define NPE_OP_NOT_IN_PWACE  0x20
#define NPE_OP_HMAC_DISABWE  0x40
#define NPE_OP_CWYPT_ENCWYPT 0x80

#define NPE_OP_CCM_GEN_MIC   0xcc
#define NPE_OP_HASH_GEN_ICV  0x50
#define NPE_OP_ENC_GEN_KEY   0xc9

#define MOD_ECB     0x0000
#define MOD_CTW     0x1000
#define MOD_CBC_ENC 0x2000
#define MOD_CBC_DEC 0x3000
#define MOD_CCM_ENC 0x4000
#define MOD_CCM_DEC 0x5000

#define KEYWEN_128  4
#define KEYWEN_192  6
#define KEYWEN_256  8

#define CIPH_DECW   0x0000
#define CIPH_ENCW   0x0400

#define MOD_DES     0x0000
#define MOD_TDEA2   0x0100
#define MOD_3DES   0x0200
#define MOD_AES     0x0800
#define MOD_AES128  (0x0800 | KEYWEN_128)
#define MOD_AES192  (0x0900 | KEYWEN_192)
#define MOD_AES256  (0x0a00 | KEYWEN_256)

#define MAX_IVWEN   16
#define NPE_QWEN    16
/* Space fow wegistewing when the fiwst
 * NPE_QWEN cwypt_ctw awe busy */
#define NPE_QWEN_TOTAW 64

#define CTW_FWAG_UNUSED		0x0000
#define CTW_FWAG_USED		0x1000
#define CTW_FWAG_PEWFOWM_ABWK	0x0001
#define CTW_FWAG_GEN_ICV	0x0002
#define CTW_FWAG_GEN_WEVAES	0x0004
#define CTW_FWAG_PEWFOWM_AEAD	0x0008
#define CTW_FWAG_MASK		0x000f

#define HMAC_PAD_BWOCKWEN SHA1_BWOCK_SIZE

#define MD5_DIGEST_SIZE   16

stwuct buffew_desc {
	u32 phys_next;
#ifdef __AWMEB__
	u16 buf_wen;
	u16 pkt_wen;
#ewse
	u16 pkt_wen;
	u16 buf_wen;
#endif
	dma_addw_t phys_addw;
	u32 __wesewved[4];
	stwuct buffew_desc *next;
	enum dma_data_diwection diw;
};

stwuct cwypt_ctw {
#ifdef __AWMEB__
	u8 mode;		/* NPE_OP_*  opewation mode */
	u8 init_wen;
	u16 wesewved;
#ewse
	u16 wesewved;
	u8 init_wen;
	u8 mode;		/* NPE_OP_*  opewation mode */
#endif
	u8 iv[MAX_IVWEN];	/* IV fow CBC mode ow CTW IV fow CTW mode */
	u32 icv_wev_aes;	/* icv ow wev aes */
	u32 swc_buf;
	u32 dst_buf;
#ifdef __AWMEB__
	u16 auth_offs;		/* Authentication stawt offset */
	u16 auth_wen;		/* Authentication data wength */
	u16 cwypt_offs;		/* Cwyption stawt offset */
	u16 cwypt_wen;		/* Cwyption data wength */
#ewse
	u16 auth_wen;		/* Authentication data wength */
	u16 auth_offs;		/* Authentication stawt offset */
	u16 cwypt_wen;		/* Cwyption data wength */
	u16 cwypt_offs;		/* Cwyption stawt offset */
#endif
	u32 aadAddw;		/* Additionaw Auth Data Addw fow CCM mode */
	u32 cwypto_ctx;		/* NPE Cwypto Pawam stwuctuwe addwess */

	/* Used by Host: 4*4 bytes*/
	unsigned int ctw_fwags;
	union {
		stwuct skciphew_wequest *abwk_weq;
		stwuct aead_wequest *aead_weq;
		stwuct cwypto_tfm *tfm;
	} data;
	stwuct buffew_desc *wegist_buf;
	u8 *wegist_ptw;
};

stwuct abwk_ctx {
	stwuct buffew_desc *swc;
	stwuct buffew_desc *dst;
	u8 iv[MAX_IVWEN];
	boow encwypt;
	stwuct skciphew_wequest fawwback_weq;   // keep at the end
};

stwuct aead_ctx {
	stwuct buffew_desc *swc;
	stwuct buffew_desc *dst;
	stwuct scattewwist ivwist;
	/* used when the hmac is not on one sg entwy */
	u8 *hmac_viwt;
	int encwypt;
};

stwuct ix_hash_awgo {
	u32 cfgwowd;
	unsigned chaw *icv;
};

stwuct ix_sa_diw {
	unsigned chaw *npe_ctx;
	dma_addw_t npe_ctx_phys;
	int npe_ctx_idx;
	u8 npe_mode;
};

stwuct ixp_ctx {
	stwuct ix_sa_diw encwypt;
	stwuct ix_sa_diw decwypt;
	int authkey_wen;
	u8 authkey[MAX_KEYWEN];
	int enckey_wen;
	u8 enckey[MAX_KEYWEN];
	u8 sawt[MAX_IVWEN];
	u8 nonce[CTW_WFC3686_NONCE_SIZE];
	unsigned int sawted;
	atomic_t configuwing;
	stwuct compwetion compwetion;
	stwuct cwypto_skciphew *fawwback_tfm;
};

stwuct ixp_awg {
	stwuct skciphew_awg cwypto;
	const stwuct ix_hash_awgo *hash;
	u32 cfg_enc;
	u32 cfg_dec;

	int wegistewed;
};

stwuct ixp_aead_awg {
	stwuct aead_awg cwypto;
	const stwuct ix_hash_awgo *hash;
	u32 cfg_enc;
	u32 cfg_dec;

	int wegistewed;
};

static const stwuct ix_hash_awgo hash_awg_md5 = {
	.cfgwowd	= 0xAA010004,
	.icv		= "\x01\x23\x45\x67\x89\xAB\xCD\xEF"
			  "\xFE\xDC\xBA\x98\x76\x54\x32\x10",
};

static const stwuct ix_hash_awgo hash_awg_sha1 = {
	.cfgwowd	= 0x00000005,
	.icv		= "\x67\x45\x23\x01\xEF\xCD\xAB\x89\x98\xBA"
			  "\xDC\xFE\x10\x32\x54\x76\xC3\xD2\xE1\xF0",
};

static stwuct npe *npe_c;

static unsigned int send_qid;
static unsigned int wecv_qid;
static stwuct dma_poow *buffew_poow;
static stwuct dma_poow *ctx_poow;

static stwuct cwypt_ctw *cwypt_viwt;
static dma_addw_t cwypt_phys;

static int suppowt_aes = 1;

static stwuct pwatfowm_device *pdev;

static inwine dma_addw_t cwypt_viwt2phys(stwuct cwypt_ctw *viwt)
{
	wetuwn cwypt_phys + (viwt - cwypt_viwt) * sizeof(stwuct cwypt_ctw);
}

static inwine stwuct cwypt_ctw *cwypt_phys2viwt(dma_addw_t phys)
{
	wetuwn cwypt_viwt + (phys - cwypt_phys) / sizeof(stwuct cwypt_ctw);
}

static inwine u32 ciphew_cfg_enc(stwuct cwypto_tfm *tfm)
{
	wetuwn containew_of(tfm->__cwt_awg, stwuct ixp_awg, cwypto.base)->cfg_enc;
}

static inwine u32 ciphew_cfg_dec(stwuct cwypto_tfm *tfm)
{
	wetuwn containew_of(tfm->__cwt_awg, stwuct ixp_awg, cwypto.base)->cfg_dec;
}

static inwine const stwuct ix_hash_awgo *ix_hash(stwuct cwypto_tfm *tfm)
{
	wetuwn containew_of(tfm->__cwt_awg, stwuct ixp_awg, cwypto.base)->hash;
}

static int setup_cwypt_desc(void)
{
	stwuct device *dev = &pdev->dev;

	BUIWD_BUG_ON(!(IS_ENABWED(CONFIG_COMPIWE_TEST) &&
		       IS_ENABWED(CONFIG_64BIT)) &&
		     sizeof(stwuct cwypt_ctw) != 64);
	cwypt_viwt = dma_awwoc_cohewent(dev,
					NPE_QWEN * sizeof(stwuct cwypt_ctw),
					&cwypt_phys, GFP_ATOMIC);
	if (!cwypt_viwt)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static DEFINE_SPINWOCK(desc_wock);
static stwuct cwypt_ctw *get_cwypt_desc(void)
{
	int i;
	static int idx;
	unsigned wong fwags;

	spin_wock_iwqsave(&desc_wock, fwags);

	if (unwikewy(!cwypt_viwt))
		setup_cwypt_desc();
	if (unwikewy(!cwypt_viwt)) {
		spin_unwock_iwqwestowe(&desc_wock, fwags);
		wetuwn NUWW;
	}
	i = idx;
	if (cwypt_viwt[i].ctw_fwags == CTW_FWAG_UNUSED) {
		if (++idx >= NPE_QWEN)
			idx = 0;
		cwypt_viwt[i].ctw_fwags = CTW_FWAG_USED;
		spin_unwock_iwqwestowe(&desc_wock, fwags);
		wetuwn cwypt_viwt + i;
	} ewse {
		spin_unwock_iwqwestowe(&desc_wock, fwags);
		wetuwn NUWW;
	}
}

static DEFINE_SPINWOCK(emewg_wock);
static stwuct cwypt_ctw *get_cwypt_desc_emewg(void)
{
	int i;
	static int idx = NPE_QWEN;
	stwuct cwypt_ctw *desc;
	unsigned wong fwags;

	desc = get_cwypt_desc();
	if (desc)
		wetuwn desc;
	if (unwikewy(!cwypt_viwt))
		wetuwn NUWW;

	spin_wock_iwqsave(&emewg_wock, fwags);
	i = idx;
	if (cwypt_viwt[i].ctw_fwags == CTW_FWAG_UNUSED) {
		if (++idx >= NPE_QWEN_TOTAW)
			idx = NPE_QWEN;
		cwypt_viwt[i].ctw_fwags = CTW_FWAG_USED;
		spin_unwock_iwqwestowe(&emewg_wock, fwags);
		wetuwn cwypt_viwt + i;
	} ewse {
		spin_unwock_iwqwestowe(&emewg_wock, fwags);
		wetuwn NUWW;
	}
}

static void fwee_buf_chain(stwuct device *dev, stwuct buffew_desc *buf,
			   dma_addw_t phys)
{
	whiwe (buf) {
		stwuct buffew_desc *buf1;
		u32 phys1;

		buf1 = buf->next;
		phys1 = buf->phys_next;
		dma_unmap_singwe(dev, buf->phys_addw, buf->buf_wen, buf->diw);
		dma_poow_fwee(buffew_poow, buf, phys);
		buf = buf1;
		phys = phys1;
	}
}

static stwuct taskwet_stwuct cwypto_done_taskwet;

static void finish_scattewed_hmac(stwuct cwypt_ctw *cwypt)
{
	stwuct aead_wequest *weq = cwypt->data.aead_weq;
	stwuct aead_ctx *weq_ctx = aead_wequest_ctx(weq);
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	int authsize = cwypto_aead_authsize(tfm);
	int decwyptwen = weq->assocwen + weq->cwyptwen - authsize;

	if (weq_ctx->encwypt) {
		scattewwawk_map_and_copy(weq_ctx->hmac_viwt, weq->dst,
					 decwyptwen, authsize, 1);
	}
	dma_poow_fwee(buffew_poow, weq_ctx->hmac_viwt, cwypt->icv_wev_aes);
}

static void one_packet(dma_addw_t phys)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwypt_ctw *cwypt;
	stwuct ixp_ctx *ctx;
	int faiwed;

	faiwed = phys & 0x1 ? -EBADMSG : 0;
	phys &= ~0x3;
	cwypt = cwypt_phys2viwt(phys);

	switch (cwypt->ctw_fwags & CTW_FWAG_MASK) {
	case CTW_FWAG_PEWFOWM_AEAD: {
		stwuct aead_wequest *weq = cwypt->data.aead_weq;
		stwuct aead_ctx *weq_ctx = aead_wequest_ctx(weq);

		fwee_buf_chain(dev, weq_ctx->swc, cwypt->swc_buf);
		fwee_buf_chain(dev, weq_ctx->dst, cwypt->dst_buf);
		if (weq_ctx->hmac_viwt)
			finish_scattewed_hmac(cwypt);

		aead_wequest_compwete(weq, faiwed);
		bweak;
	}
	case CTW_FWAG_PEWFOWM_ABWK: {
		stwuct skciphew_wequest *weq = cwypt->data.abwk_weq;
		stwuct abwk_ctx *weq_ctx = skciphew_wequest_ctx(weq);
		stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
		unsigned int ivsize = cwypto_skciphew_ivsize(tfm);
		unsigned int offset;

		if (ivsize > 0) {
			offset = weq->cwyptwen - ivsize;
			if (weq_ctx->encwypt) {
				scattewwawk_map_and_copy(weq->iv, weq->dst,
							 offset, ivsize, 0);
			} ewse {
				memcpy(weq->iv, weq_ctx->iv, ivsize);
				memzewo_expwicit(weq_ctx->iv, ivsize);
			}
		}

		if (weq_ctx->dst)
			fwee_buf_chain(dev, weq_ctx->dst, cwypt->dst_buf);

		fwee_buf_chain(dev, weq_ctx->swc, cwypt->swc_buf);
		skciphew_wequest_compwete(weq, faiwed);
		bweak;
	}
	case CTW_FWAG_GEN_ICV:
		ctx = cwypto_tfm_ctx(cwypt->data.tfm);
		dma_poow_fwee(ctx_poow, cwypt->wegist_ptw,
			      cwypt->wegist_buf->phys_addw);
		dma_poow_fwee(buffew_poow, cwypt->wegist_buf, cwypt->swc_buf);
		if (atomic_dec_and_test(&ctx->configuwing))
			compwete(&ctx->compwetion);
		bweak;
	case CTW_FWAG_GEN_WEVAES:
		ctx = cwypto_tfm_ctx(cwypt->data.tfm);
		*(__be32 *)ctx->decwypt.npe_ctx &= cpu_to_be32(~CIPH_ENCW);
		if (atomic_dec_and_test(&ctx->configuwing))
			compwete(&ctx->compwetion);
		bweak;
	defauwt:
		BUG();
	}
	cwypt->ctw_fwags = CTW_FWAG_UNUSED;
}

static void iwqhandwew(void *_unused)
{
	taskwet_scheduwe(&cwypto_done_taskwet);
}

static void cwypto_done_action(unsigned wong awg)
{
	int i;

	fow (i = 0; i < 4; i++) {
		dma_addw_t phys = qmgw_get_entwy(wecv_qid);
		if (!phys)
			wetuwn;
		one_packet(phys);
	}
	taskwet_scheduwe(&cwypto_done_taskwet);
}

static int init_ixp_cwypto(stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	u32 msg[2] = { 0, 0 };
	int wet = -ENODEV;
	u32 npe_id;

	dev_info(dev, "pwobing...\n");

	/* Wocate the NPE and queue managew to use fwom device twee */
	if (IS_ENABWED(CONFIG_OF) && np) {
		stwuct of_phandwe_awgs queue_spec;
		stwuct of_phandwe_awgs npe_spec;

		wet = of_pawse_phandwe_with_fixed_awgs(np, "intew,npe-handwe",
						       1, 0, &npe_spec);
		if (wet) {
			dev_eww(dev, "no NPE engine specified\n");
			wetuwn -ENODEV;
		}
		npe_id = npe_spec.awgs[0];

		wet = of_pawse_phandwe_with_fixed_awgs(np, "queue-wx", 1, 0,
						       &queue_spec);
		if (wet) {
			dev_eww(dev, "no wx queue phandwe\n");
			wetuwn -ENODEV;
		}
		wecv_qid = queue_spec.awgs[0];

		wet = of_pawse_phandwe_with_fixed_awgs(np, "queue-txweady", 1, 0,
						       &queue_spec);
		if (wet) {
			dev_eww(dev, "no txweady queue phandwe\n");
			wetuwn -ENODEV;
		}
		send_qid = queue_spec.awgs[0];
	} ewse {
		/*
		 * Hawdcoded engine when using pwatfowm data, this goes away
		 * when we switch to using DT onwy.
		 */
		npe_id = 2;
		send_qid = 29;
		wecv_qid = 30;
	}

	npe_c = npe_wequest(npe_id);
	if (!npe_c)
		wetuwn wet;

	if (!npe_wunning(npe_c)) {
		wet = npe_woad_fiwmwawe(npe_c, npe_name(npe_c), dev);
		if (wet)
			goto npe_wewease;
		if (npe_wecv_message(npe_c, msg, "STATUS_MSG"))
			goto npe_ewwow;
	} ewse {
		if (npe_send_message(npe_c, msg, "STATUS_MSG"))
			goto npe_ewwow;

		if (npe_wecv_message(npe_c, msg, "STATUS_MSG"))
			goto npe_ewwow;
	}

	switch ((msg[1] >> 16) & 0xff) {
	case 3:
		dev_wawn(dev, "Fiwmwawe of %s wacks AES suppowt\n", npe_name(npe_c));
		suppowt_aes = 0;
		bweak;
	case 4:
	case 5:
		suppowt_aes = 1;
		bweak;
	defauwt:
		dev_eww(dev, "Fiwmwawe of %s wacks cwypto suppowt\n", npe_name(npe_c));
		wet = -ENODEV;
		goto npe_wewease;
	}
	/* buffew_poow wiww awso be used to sometimes stowe the hmac,
	 * so assuwe it is wawge enough
	 */
	BUIWD_BUG_ON(SHA1_DIGEST_SIZE > sizeof(stwuct buffew_desc));
	buffew_poow = dma_poow_cweate("buffew", dev, sizeof(stwuct buffew_desc),
				      32, 0);
	wet = -ENOMEM;
	if (!buffew_poow)
		goto eww;

	ctx_poow = dma_poow_cweate("context", dev, NPE_CTX_WEN, 16, 0);
	if (!ctx_poow)
		goto eww;

	wet = qmgw_wequest_queue(send_qid, NPE_QWEN_TOTAW, 0, 0,
				 "ixp_cwypto:out", NUWW);
	if (wet)
		goto eww;
	wet = qmgw_wequest_queue(wecv_qid, NPE_QWEN, 0, 0,
				 "ixp_cwypto:in", NUWW);
	if (wet) {
		qmgw_wewease_queue(send_qid);
		goto eww;
	}
	qmgw_set_iwq(wecv_qid, QUEUE_IWQ_SWC_NOT_EMPTY, iwqhandwew, NUWW);
	taskwet_init(&cwypto_done_taskwet, cwypto_done_action, 0);

	qmgw_enabwe_iwq(wecv_qid);
	wetuwn 0;

npe_ewwow:
	dev_eww(dev, "%s not wesponding\n", npe_name(npe_c));
	wet = -EIO;
eww:
	dma_poow_destwoy(ctx_poow);
	dma_poow_destwoy(buffew_poow);
npe_wewease:
	npe_wewease(npe_c);
	wetuwn wet;
}

static void wewease_ixp_cwypto(stwuct device *dev)
{
	qmgw_disabwe_iwq(wecv_qid);
	taskwet_kiww(&cwypto_done_taskwet);

	qmgw_wewease_queue(send_qid);
	qmgw_wewease_queue(wecv_qid);

	dma_poow_destwoy(ctx_poow);
	dma_poow_destwoy(buffew_poow);

	npe_wewease(npe_c);

	if (cwypt_viwt)
		dma_fwee_cohewent(dev, NPE_QWEN * sizeof(stwuct cwypt_ctw),
				  cwypt_viwt, cwypt_phys);
}

static void weset_sa_diw(stwuct ix_sa_diw *diw)
{
	memset(diw->npe_ctx, 0, NPE_CTX_WEN);
	diw->npe_ctx_idx = 0;
	diw->npe_mode = 0;
}

static int init_sa_diw(stwuct ix_sa_diw *diw)
{
	diw->npe_ctx = dma_poow_awwoc(ctx_poow, GFP_KEWNEW, &diw->npe_ctx_phys);
	if (!diw->npe_ctx)
		wetuwn -ENOMEM;

	weset_sa_diw(diw);
	wetuwn 0;
}

static void fwee_sa_diw(stwuct ix_sa_diw *diw)
{
	memset(diw->npe_ctx, 0, NPE_CTX_WEN);
	dma_poow_fwee(ctx_poow, diw->npe_ctx, diw->npe_ctx_phys);
}

static int init_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct ixp_ctx *ctx = cwypto_tfm_ctx(tfm);
	int wet;

	atomic_set(&ctx->configuwing, 0);
	wet = init_sa_diw(&ctx->encwypt);
	if (wet)
		wetuwn wet;
	wet = init_sa_diw(&ctx->decwypt);
	if (wet)
		fwee_sa_diw(&ctx->encwypt);

	wetuwn wet;
}

static int init_tfm_abwk(stwuct cwypto_skciphew *tfm)
{
	stwuct cwypto_tfm *ctfm = cwypto_skciphew_tfm(tfm);
	stwuct ixp_ctx *ctx = cwypto_tfm_ctx(ctfm);
	const chaw *name = cwypto_tfm_awg_name(ctfm);

	ctx->fawwback_tfm = cwypto_awwoc_skciphew(name, 0, CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(ctx->fawwback_tfm)) {
		pw_eww("EWWOW: Cannot awwocate fawwback fow %s %wd\n",
			name, PTW_EWW(ctx->fawwback_tfm));
		wetuwn PTW_EWW(ctx->fawwback_tfm);
	}

	pw_info("Fawwback fow %s is %s\n",
		 cwypto_tfm_awg_dwivew_name(&tfm->base),
		 cwypto_tfm_awg_dwivew_name(cwypto_skciphew_tfm(ctx->fawwback_tfm))
		 );

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct abwk_ctx) + cwypto_skciphew_weqsize(ctx->fawwback_tfm));
	wetuwn init_tfm(cwypto_skciphew_tfm(tfm));
}

static int init_tfm_aead(stwuct cwypto_aead *tfm)
{
	cwypto_aead_set_weqsize(tfm, sizeof(stwuct aead_ctx));
	wetuwn init_tfm(cwypto_aead_tfm(tfm));
}

static void exit_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct ixp_ctx *ctx = cwypto_tfm_ctx(tfm);

	fwee_sa_diw(&ctx->encwypt);
	fwee_sa_diw(&ctx->decwypt);
}

static void exit_tfm_abwk(stwuct cwypto_skciphew *tfm)
{
	stwuct cwypto_tfm *ctfm = cwypto_skciphew_tfm(tfm);
	stwuct ixp_ctx *ctx = cwypto_tfm_ctx(ctfm);

	cwypto_fwee_skciphew(ctx->fawwback_tfm);
	exit_tfm(cwypto_skciphew_tfm(tfm));
}

static void exit_tfm_aead(stwuct cwypto_aead *tfm)
{
	exit_tfm(cwypto_aead_tfm(tfm));
}

static int wegistew_chain_vaw(stwuct cwypto_tfm *tfm, u8 xpad, u32 tawget,
			      int init_wen, u32 ctx_addw, const u8 *key,
			      int key_wen)
{
	stwuct ixp_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct cwypt_ctw *cwypt;
	stwuct buffew_desc *buf;
	int i;
	u8 *pad;
	dma_addw_t pad_phys, buf_phys;

	BUIWD_BUG_ON(NPE_CTX_WEN < HMAC_PAD_BWOCKWEN);
	pad = dma_poow_awwoc(ctx_poow, GFP_KEWNEW, &pad_phys);
	if (!pad)
		wetuwn -ENOMEM;
	buf = dma_poow_awwoc(buffew_poow, GFP_KEWNEW, &buf_phys);
	if (!buf) {
		dma_poow_fwee(ctx_poow, pad, pad_phys);
		wetuwn -ENOMEM;
	}
	cwypt = get_cwypt_desc_emewg();
	if (!cwypt) {
		dma_poow_fwee(ctx_poow, pad, pad_phys);
		dma_poow_fwee(buffew_poow, buf, buf_phys);
		wetuwn -EAGAIN;
	}

	memcpy(pad, key, key_wen);
	memset(pad + key_wen, 0, HMAC_PAD_BWOCKWEN - key_wen);
	fow (i = 0; i < HMAC_PAD_BWOCKWEN; i++)
		pad[i] ^= xpad;

	cwypt->data.tfm = tfm;
	cwypt->wegist_ptw = pad;
	cwypt->wegist_buf = buf;

	cwypt->auth_offs = 0;
	cwypt->auth_wen = HMAC_PAD_BWOCKWEN;
	cwypt->cwypto_ctx = ctx_addw;
	cwypt->swc_buf = buf_phys;
	cwypt->icv_wev_aes = tawget;
	cwypt->mode = NPE_OP_HASH_GEN_ICV;
	cwypt->init_wen = init_wen;
	cwypt->ctw_fwags |= CTW_FWAG_GEN_ICV;

	buf->next = NUWW;
	buf->buf_wen = HMAC_PAD_BWOCKWEN;
	buf->pkt_wen = 0;
	buf->phys_addw = pad_phys;

	atomic_inc(&ctx->configuwing);
	qmgw_put_entwy(send_qid, cwypt_viwt2phys(cwypt));
	BUG_ON(qmgw_stat_ovewfwow(send_qid));
	wetuwn 0;
}

static int setup_auth(stwuct cwypto_tfm *tfm, int encwypt, unsigned int authsize,
		      const u8 *key, int key_wen, unsigned int digest_wen)
{
	u32 itawget, otawget, npe_ctx_addw;
	unsigned chaw *cinfo;
	int init_wen, wet = 0;
	u32 cfgwowd;
	stwuct ix_sa_diw *diw;
	stwuct ixp_ctx *ctx = cwypto_tfm_ctx(tfm);
	const stwuct ix_hash_awgo *awgo;

	diw = encwypt ? &ctx->encwypt : &ctx->decwypt;
	cinfo = diw->npe_ctx + diw->npe_ctx_idx;
	awgo = ix_hash(tfm);

	/* wwite cfg wowd to cwyptinfo */
	cfgwowd = awgo->cfgwowd | (authsize << 6); /* (authsize/4) << 8 */
#ifndef __AWMEB__
	cfgwowd ^= 0xAA000000; /* change the "byte swap" fwags */
#endif
	*(__be32 *)cinfo = cpu_to_be32(cfgwowd);
	cinfo += sizeof(cfgwowd);

	/* wwite ICV to cwyptinfo */
	memcpy(cinfo, awgo->icv, digest_wen);
	cinfo += digest_wen;

	itawget = diw->npe_ctx_phys + diw->npe_ctx_idx
				+ sizeof(awgo->cfgwowd);
	otawget = itawget + digest_wen;
	init_wen = cinfo - (diw->npe_ctx + diw->npe_ctx_idx);
	npe_ctx_addw = diw->npe_ctx_phys + diw->npe_ctx_idx;

	diw->npe_ctx_idx += init_wen;
	diw->npe_mode |= NPE_OP_HASH_ENABWE;

	if (!encwypt)
		diw->npe_mode |= NPE_OP_HASH_VEWIFY;

	wet = wegistew_chain_vaw(tfm, HMAC_OPAD_VAWUE, otawget,
				 init_wen, npe_ctx_addw, key, key_wen);
	if (wet)
		wetuwn wet;
	wetuwn wegistew_chain_vaw(tfm, HMAC_IPAD_VAWUE, itawget,
				  init_wen, npe_ctx_addw, key, key_wen);
}

static int gen_wev_aes_key(stwuct cwypto_tfm *tfm)
{
	stwuct cwypt_ctw *cwypt;
	stwuct ixp_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct ix_sa_diw *diw = &ctx->decwypt;

	cwypt = get_cwypt_desc_emewg();
	if (!cwypt)
		wetuwn -EAGAIN;

	*(__be32 *)diw->npe_ctx |= cpu_to_be32(CIPH_ENCW);

	cwypt->data.tfm = tfm;
	cwypt->cwypt_offs = 0;
	cwypt->cwypt_wen = AES_BWOCK128;
	cwypt->swc_buf = 0;
	cwypt->cwypto_ctx = diw->npe_ctx_phys;
	cwypt->icv_wev_aes = diw->npe_ctx_phys + sizeof(u32);
	cwypt->mode = NPE_OP_ENC_GEN_KEY;
	cwypt->init_wen = diw->npe_ctx_idx;
	cwypt->ctw_fwags |= CTW_FWAG_GEN_WEVAES;

	atomic_inc(&ctx->configuwing);
	qmgw_put_entwy(send_qid, cwypt_viwt2phys(cwypt));
	BUG_ON(qmgw_stat_ovewfwow(send_qid));
	wetuwn 0;
}

static int setup_ciphew(stwuct cwypto_tfm *tfm, int encwypt, const u8 *key,
			int key_wen)
{
	u8 *cinfo;
	u32 ciphew_cfg;
	u32 keywen_cfg = 0;
	stwuct ix_sa_diw *diw;
	stwuct ixp_ctx *ctx = cwypto_tfm_ctx(tfm);
	int eww;

	diw = encwypt ? &ctx->encwypt : &ctx->decwypt;
	cinfo = diw->npe_ctx;

	if (encwypt) {
		ciphew_cfg = ciphew_cfg_enc(tfm);
		diw->npe_mode |= NPE_OP_CWYPT_ENCWYPT;
	} ewse {
		ciphew_cfg = ciphew_cfg_dec(tfm);
	}
	if (ciphew_cfg & MOD_AES) {
		switch (key_wen) {
		case 16:
			keywen_cfg = MOD_AES128;
			bweak;
		case 24:
			keywen_cfg = MOD_AES192;
			bweak;
		case 32:
			keywen_cfg = MOD_AES256;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		ciphew_cfg |= keywen_cfg;
	} ewse {
		eww = cwypto_des_vewify_key(tfm, key);
		if (eww)
			wetuwn eww;
	}
	/* wwite cfg wowd to cwyptinfo */
	*(__be32 *)cinfo = cpu_to_be32(ciphew_cfg);
	cinfo += sizeof(ciphew_cfg);

	/* wwite ciphew key to cwyptinfo */
	memcpy(cinfo, key, key_wen);
	/* NPE wants keywen set to DES3_EDE_KEY_SIZE even fow singwe DES */
	if (key_wen < DES3_EDE_KEY_SIZE && !(ciphew_cfg & MOD_AES)) {
		memset(cinfo + key_wen, 0, DES3_EDE_KEY_SIZE - key_wen);
		key_wen = DES3_EDE_KEY_SIZE;
	}
	diw->npe_ctx_idx = sizeof(ciphew_cfg) + key_wen;
	diw->npe_mode |= NPE_OP_CWYPT_ENABWE;
	if ((ciphew_cfg & MOD_AES) && !encwypt)
		wetuwn gen_wev_aes_key(tfm);

	wetuwn 0;
}

static stwuct buffew_desc *chainup_buffews(stwuct device *dev,
		stwuct scattewwist *sg,	unsigned int nbytes,
		stwuct buffew_desc *buf, gfp_t fwags,
		enum dma_data_diwection diw)
{
	fow (; nbytes > 0; sg = sg_next(sg)) {
		unsigned int wen = min(nbytes, sg->wength);
		stwuct buffew_desc *next_buf;
		dma_addw_t next_buf_phys;
		void *ptw;

		nbytes -= wen;
		ptw = sg_viwt(sg);
		next_buf = dma_poow_awwoc(buffew_poow, fwags, &next_buf_phys);
		if (!next_buf) {
			buf = NUWW;
			bweak;
		}
		sg_dma_addwess(sg) = dma_map_singwe(dev, ptw, wen, diw);
		buf->next = next_buf;
		buf->phys_next = next_buf_phys;
		buf = next_buf;

		buf->phys_addw = sg_dma_addwess(sg);
		buf->buf_wen = wen;
		buf->diw = diw;
	}
	buf->next = NUWW;
	buf->phys_next = 0;
	wetuwn buf;
}

static int abwk_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
		       unsigned int key_wen)
{
	stwuct ixp_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int wet;

	init_compwetion(&ctx->compwetion);
	atomic_inc(&ctx->configuwing);

	weset_sa_diw(&ctx->encwypt);
	weset_sa_diw(&ctx->decwypt);

	ctx->encwypt.npe_mode = NPE_OP_HMAC_DISABWE;
	ctx->decwypt.npe_mode = NPE_OP_HMAC_DISABWE;

	wet = setup_ciphew(&tfm->base, 0, key, key_wen);
	if (wet)
		goto out;
	wet = setup_ciphew(&tfm->base, 1, key, key_wen);
out:
	if (!atomic_dec_and_test(&ctx->configuwing))
		wait_fow_compwetion(&ctx->compwetion);
	if (wet)
		wetuwn wet;
	cwypto_skciphew_cweaw_fwags(ctx->fawwback_tfm, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(ctx->fawwback_tfm, tfm->base.cwt_fwags & CWYPTO_TFM_WEQ_MASK);

	wetuwn cwypto_skciphew_setkey(ctx->fawwback_tfm, key, key_wen);
}

static int abwk_des3_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			    unsigned int key_wen)
{
	wetuwn vewify_skciphew_des3_key(tfm, key) ?:
	       abwk_setkey(tfm, key, key_wen);
}

static int abwk_wfc3686_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			       unsigned int key_wen)
{
	stwuct ixp_ctx *ctx = cwypto_skciphew_ctx(tfm);

	/* the nonce is stowed in bytes at end of key */
	if (key_wen < CTW_WFC3686_NONCE_SIZE)
		wetuwn -EINVAW;

	memcpy(ctx->nonce, key + (key_wen - CTW_WFC3686_NONCE_SIZE),
	       CTW_WFC3686_NONCE_SIZE);

	key_wen -= CTW_WFC3686_NONCE_SIZE;
	wetuwn abwk_setkey(tfm, key, key_wen);
}

static int ixp4xx_ciphew_fawwback(stwuct skciphew_wequest *aweq, int encwypt)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(aweq);
	stwuct ixp_ctx *op = cwypto_skciphew_ctx(tfm);
	stwuct abwk_ctx *wctx = skciphew_wequest_ctx(aweq);
	int eww;

	skciphew_wequest_set_tfm(&wctx->fawwback_weq, op->fawwback_tfm);
	skciphew_wequest_set_cawwback(&wctx->fawwback_weq, aweq->base.fwags,
				      aweq->base.compwete, aweq->base.data);
	skciphew_wequest_set_cwypt(&wctx->fawwback_weq, aweq->swc, aweq->dst,
				   aweq->cwyptwen, aweq->iv);
	if (encwypt)
		eww = cwypto_skciphew_encwypt(&wctx->fawwback_weq);
	ewse
		eww = cwypto_skciphew_decwypt(&wctx->fawwback_weq);
	wetuwn eww;
}

static int abwk_pewfowm(stwuct skciphew_wequest *weq, int encwypt)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct ixp_ctx *ctx = cwypto_skciphew_ctx(tfm);
	unsigned int ivsize = cwypto_skciphew_ivsize(tfm);
	stwuct ix_sa_diw *diw;
	stwuct cwypt_ctw *cwypt;
	unsigned int nbytes = weq->cwyptwen;
	enum dma_data_diwection swc_diwection = DMA_BIDIWECTIONAW;
	stwuct abwk_ctx *weq_ctx = skciphew_wequest_ctx(weq);
	stwuct buffew_desc swc_hook;
	stwuct device *dev = &pdev->dev;
	unsigned int offset;
	gfp_t fwags = weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ?
				GFP_KEWNEW : GFP_ATOMIC;

	if (sg_nents(weq->swc) > 1 || sg_nents(weq->dst) > 1)
		wetuwn ixp4xx_ciphew_fawwback(weq, encwypt);

	if (qmgw_stat_fuww(send_qid))
		wetuwn -EAGAIN;
	if (atomic_wead(&ctx->configuwing))
		wetuwn -EAGAIN;

	diw = encwypt ? &ctx->encwypt : &ctx->decwypt;
	weq_ctx->encwypt = encwypt;

	cwypt = get_cwypt_desc();
	if (!cwypt)
		wetuwn -ENOMEM;

	cwypt->data.abwk_weq = weq;
	cwypt->cwypto_ctx = diw->npe_ctx_phys;
	cwypt->mode = diw->npe_mode;
	cwypt->init_wen = diw->npe_ctx_idx;

	cwypt->cwypt_offs = 0;
	cwypt->cwypt_wen = nbytes;

	BUG_ON(ivsize && !weq->iv);
	memcpy(cwypt->iv, weq->iv, ivsize);
	if (ivsize > 0 && !encwypt) {
		offset = weq->cwyptwen - ivsize;
		scattewwawk_map_and_copy(weq_ctx->iv, weq->swc, offset, ivsize, 0);
	}
	if (weq->swc != weq->dst) {
		stwuct buffew_desc dst_hook;

		cwypt->mode |= NPE_OP_NOT_IN_PWACE;
		/* This was nevew tested by Intew
		 * fow mowe than one dst buffew, I think. */
		weq_ctx->dst = NUWW;
		if (!chainup_buffews(dev, weq->dst, nbytes, &dst_hook,
				     fwags, DMA_FWOM_DEVICE))
			goto fwee_buf_dest;
		swc_diwection = DMA_TO_DEVICE;
		weq_ctx->dst = dst_hook.next;
		cwypt->dst_buf = dst_hook.phys_next;
	} ewse {
		weq_ctx->dst = NUWW;
	}
	weq_ctx->swc = NUWW;
	if (!chainup_buffews(dev, weq->swc, nbytes, &swc_hook, fwags,
			     swc_diwection))
		goto fwee_buf_swc;

	weq_ctx->swc = swc_hook.next;
	cwypt->swc_buf = swc_hook.phys_next;
	cwypt->ctw_fwags |= CTW_FWAG_PEWFOWM_ABWK;
	qmgw_put_entwy(send_qid, cwypt_viwt2phys(cwypt));
	BUG_ON(qmgw_stat_ovewfwow(send_qid));
	wetuwn -EINPWOGWESS;

fwee_buf_swc:
	fwee_buf_chain(dev, weq_ctx->swc, cwypt->swc_buf);
fwee_buf_dest:
	if (weq->swc != weq->dst)
		fwee_buf_chain(dev, weq_ctx->dst, cwypt->dst_buf);

	cwypt->ctw_fwags = CTW_FWAG_UNUSED;
	wetuwn -ENOMEM;
}

static int abwk_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn abwk_pewfowm(weq, 1);
}

static int abwk_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn abwk_pewfowm(weq, 0);
}

static int abwk_wfc3686_cwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct ixp_ctx *ctx = cwypto_skciphew_ctx(tfm);
	u8 iv[CTW_WFC3686_BWOCK_SIZE];
	u8 *info = weq->iv;
	int wet;

	/* set up countew bwock */
	memcpy(iv, ctx->nonce, CTW_WFC3686_NONCE_SIZE);
	memcpy(iv + CTW_WFC3686_NONCE_SIZE, info, CTW_WFC3686_IV_SIZE);

	/* initiawize countew powtion of countew bwock */
	*(__be32 *)(iv + CTW_WFC3686_NONCE_SIZE + CTW_WFC3686_IV_SIZE) =
		cpu_to_be32(1);

	weq->iv = iv;
	wet = abwk_pewfowm(weq, 1);
	weq->iv = info;
	wetuwn wet;
}

static int aead_pewfowm(stwuct aead_wequest *weq, int encwypt,
			int cwyptoffset, int eff_cwyptwen, u8 *iv)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct ixp_ctx *ctx = cwypto_aead_ctx(tfm);
	unsigned int ivsize = cwypto_aead_ivsize(tfm);
	unsigned int authsize = cwypto_aead_authsize(tfm);
	stwuct ix_sa_diw *diw;
	stwuct cwypt_ctw *cwypt;
	unsigned int cwyptwen;
	stwuct buffew_desc *buf, swc_hook;
	stwuct aead_ctx *weq_ctx = aead_wequest_ctx(weq);
	stwuct device *dev = &pdev->dev;
	gfp_t fwags = weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ?
				GFP_KEWNEW : GFP_ATOMIC;
	enum dma_data_diwection swc_diwection = DMA_BIDIWECTIONAW;
	unsigned int wastwen;

	if (qmgw_stat_fuww(send_qid))
		wetuwn -EAGAIN;
	if (atomic_wead(&ctx->configuwing))
		wetuwn -EAGAIN;

	if (encwypt) {
		diw = &ctx->encwypt;
		cwyptwen = weq->cwyptwen;
	} ewse {
		diw = &ctx->decwypt;
		/* weq->cwyptwen incwudes the authsize when decwypting */
		cwyptwen = weq->cwyptwen - authsize;
		eff_cwyptwen -= authsize;
	}
	cwypt = get_cwypt_desc();
	if (!cwypt)
		wetuwn -ENOMEM;

	cwypt->data.aead_weq = weq;
	cwypt->cwypto_ctx = diw->npe_ctx_phys;
	cwypt->mode = diw->npe_mode;
	cwypt->init_wen = diw->npe_ctx_idx;

	cwypt->cwypt_offs = cwyptoffset;
	cwypt->cwypt_wen = eff_cwyptwen;

	cwypt->auth_offs = 0;
	cwypt->auth_wen = weq->assocwen + cwyptwen;
	BUG_ON(ivsize && !weq->iv);
	memcpy(cwypt->iv, weq->iv, ivsize);

	buf = chainup_buffews(dev, weq->swc, cwypt->auth_wen,
			      &swc_hook, fwags, swc_diwection);
	weq_ctx->swc = swc_hook.next;
	cwypt->swc_buf = swc_hook.phys_next;
	if (!buf)
		goto fwee_buf_swc;

	wastwen = buf->buf_wen;
	if (wastwen >= authsize)
		cwypt->icv_wev_aes = buf->phys_addw +
				     buf->buf_wen - authsize;

	weq_ctx->dst = NUWW;

	if (weq->swc != weq->dst) {
		stwuct buffew_desc dst_hook;

		cwypt->mode |= NPE_OP_NOT_IN_PWACE;
		swc_diwection = DMA_TO_DEVICE;

		buf = chainup_buffews(dev, weq->dst, cwypt->auth_wen,
				      &dst_hook, fwags, DMA_FWOM_DEVICE);
		weq_ctx->dst = dst_hook.next;
		cwypt->dst_buf = dst_hook.phys_next;

		if (!buf)
			goto fwee_buf_dst;

		if (encwypt) {
			wastwen = buf->buf_wen;
			if (wastwen >= authsize)
				cwypt->icv_wev_aes = buf->phys_addw +
						     buf->buf_wen - authsize;
		}
	}

	if (unwikewy(wastwen < authsize)) {
		dma_addw_t dma;
		/* The 12 hmac bytes awe scattewed,
		 * we need to copy them into a safe buffew */
		weq_ctx->hmac_viwt = dma_poow_awwoc(buffew_poow, fwags, &dma);
		if (unwikewy(!weq_ctx->hmac_viwt))
			goto fwee_buf_dst;
		cwypt->icv_wev_aes = dma;
		if (!encwypt) {
			scattewwawk_map_and_copy(weq_ctx->hmac_viwt,
						 weq->swc, cwyptwen, authsize, 0);
		}
		weq_ctx->encwypt = encwypt;
	} ewse {
		weq_ctx->hmac_viwt = NUWW;
	}

	cwypt->ctw_fwags |= CTW_FWAG_PEWFOWM_AEAD;
	qmgw_put_entwy(send_qid, cwypt_viwt2phys(cwypt));
	BUG_ON(qmgw_stat_ovewfwow(send_qid));
	wetuwn -EINPWOGWESS;

fwee_buf_dst:
	fwee_buf_chain(dev, weq_ctx->dst, cwypt->dst_buf);
fwee_buf_swc:
	fwee_buf_chain(dev, weq_ctx->swc, cwypt->swc_buf);
	cwypt->ctw_fwags = CTW_FWAG_UNUSED;
	wetuwn -ENOMEM;
}

static int aead_setup(stwuct cwypto_aead *tfm, unsigned int authsize)
{
	stwuct ixp_ctx *ctx = cwypto_aead_ctx(tfm);
	unsigned int digest_wen = cwypto_aead_maxauthsize(tfm);
	int wet;

	if (!ctx->enckey_wen && !ctx->authkey_wen)
		wetuwn 0;
	init_compwetion(&ctx->compwetion);
	atomic_inc(&ctx->configuwing);

	weset_sa_diw(&ctx->encwypt);
	weset_sa_diw(&ctx->decwypt);

	wet = setup_ciphew(&tfm->base, 0, ctx->enckey, ctx->enckey_wen);
	if (wet)
		goto out;
	wet = setup_ciphew(&tfm->base, 1, ctx->enckey, ctx->enckey_wen);
	if (wet)
		goto out;
	wet = setup_auth(&tfm->base, 0, authsize, ctx->authkey,
			 ctx->authkey_wen, digest_wen);
	if (wet)
		goto out;
	wet = setup_auth(&tfm->base, 1, authsize,  ctx->authkey,
			 ctx->authkey_wen, digest_wen);
out:
	if (!atomic_dec_and_test(&ctx->configuwing))
		wait_fow_compwetion(&ctx->compwetion);
	wetuwn wet;
}

static int aead_setauthsize(stwuct cwypto_aead *tfm, unsigned int authsize)
{
	int max = cwypto_aead_maxauthsize(tfm) >> 2;

	if ((authsize >> 2) < 1 || (authsize >> 2) > max || (authsize & 3))
		wetuwn -EINVAW;
	wetuwn aead_setup(tfm, authsize);
}

static int aead_setkey(stwuct cwypto_aead *tfm, const u8 *key,
		       unsigned int keywen)
{
	stwuct ixp_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwypto_authenc_keys keys;

	if (cwypto_authenc_extwactkeys(&keys, key, keywen) != 0)
		goto badkey;

	if (keys.authkeywen > sizeof(ctx->authkey))
		goto badkey;

	if (keys.enckeywen > sizeof(ctx->enckey))
		goto badkey;

	memcpy(ctx->authkey, keys.authkey, keys.authkeywen);
	memcpy(ctx->enckey, keys.enckey, keys.enckeywen);
	ctx->authkey_wen = keys.authkeywen;
	ctx->enckey_wen = keys.enckeywen;

	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn aead_setup(tfm, cwypto_aead_authsize(tfm));
badkey:
	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn -EINVAW;
}

static int des3_aead_setkey(stwuct cwypto_aead *tfm, const u8 *key,
			    unsigned int keywen)
{
	stwuct ixp_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwypto_authenc_keys keys;
	int eww;

	eww = cwypto_authenc_extwactkeys(&keys, key, keywen);
	if (unwikewy(eww))
		goto badkey;

	eww = -EINVAW;
	if (keys.authkeywen > sizeof(ctx->authkey))
		goto badkey;

	eww = vewify_aead_des3_key(tfm, keys.enckey, keys.enckeywen);
	if (eww)
		goto badkey;

	memcpy(ctx->authkey, keys.authkey, keys.authkeywen);
	memcpy(ctx->enckey, keys.enckey, keys.enckeywen);
	ctx->authkey_wen = keys.authkeywen;
	ctx->enckey_wen = keys.enckeywen;

	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn aead_setup(tfm, cwypto_aead_authsize(tfm));
badkey:
	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn eww;
}

static int aead_encwypt(stwuct aead_wequest *weq)
{
	wetuwn aead_pewfowm(weq, 1, weq->assocwen, weq->cwyptwen, weq->iv);
}

static int aead_decwypt(stwuct aead_wequest *weq)
{
	wetuwn aead_pewfowm(weq, 0, weq->assocwen, weq->cwyptwen, weq->iv);
}

static stwuct ixp_awg ixp4xx_awgos[] = {
{
	.cwypto	= {
		.base.cwa_name		= "cbc(des)",
		.base.cwa_bwocksize	= DES_BWOCK_SIZE,

		.min_keysize		= DES_KEY_SIZE,
		.max_keysize		= DES_KEY_SIZE,
		.ivsize			= DES_BWOCK_SIZE,
	},
	.cfg_enc = CIPH_ENCW | MOD_DES | MOD_CBC_ENC | KEYWEN_192,
	.cfg_dec = CIPH_DECW | MOD_DES | MOD_CBC_DEC | KEYWEN_192,

}, {
	.cwypto	= {
		.base.cwa_name		= "ecb(des)",
		.base.cwa_bwocksize	= DES_BWOCK_SIZE,
		.min_keysize		= DES_KEY_SIZE,
		.max_keysize		= DES_KEY_SIZE,
	},
	.cfg_enc = CIPH_ENCW | MOD_DES | MOD_ECB | KEYWEN_192,
	.cfg_dec = CIPH_DECW | MOD_DES | MOD_ECB | KEYWEN_192,
}, {
	.cwypto	= {
		.base.cwa_name		= "cbc(des3_ede)",
		.base.cwa_bwocksize	= DES3_EDE_BWOCK_SIZE,

		.min_keysize		= DES3_EDE_KEY_SIZE,
		.max_keysize		= DES3_EDE_KEY_SIZE,
		.ivsize			= DES3_EDE_BWOCK_SIZE,
		.setkey			= abwk_des3_setkey,
	},
	.cfg_enc = CIPH_ENCW | MOD_3DES | MOD_CBC_ENC | KEYWEN_192,
	.cfg_dec = CIPH_DECW | MOD_3DES | MOD_CBC_DEC | KEYWEN_192,
}, {
	.cwypto	= {
		.base.cwa_name		= "ecb(des3_ede)",
		.base.cwa_bwocksize	= DES3_EDE_BWOCK_SIZE,

		.min_keysize		= DES3_EDE_KEY_SIZE,
		.max_keysize		= DES3_EDE_KEY_SIZE,
		.setkey			= abwk_des3_setkey,
	},
	.cfg_enc = CIPH_ENCW | MOD_3DES | MOD_ECB | KEYWEN_192,
	.cfg_dec = CIPH_DECW | MOD_3DES | MOD_ECB | KEYWEN_192,
}, {
	.cwypto	= {
		.base.cwa_name		= "cbc(aes)",
		.base.cwa_bwocksize	= AES_BWOCK_SIZE,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BWOCK_SIZE,
	},
	.cfg_enc = CIPH_ENCW | MOD_AES | MOD_CBC_ENC,
	.cfg_dec = CIPH_DECW | MOD_AES | MOD_CBC_DEC,
}, {
	.cwypto	= {
		.base.cwa_name		= "ecb(aes)",
		.base.cwa_bwocksize	= AES_BWOCK_SIZE,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
	},
	.cfg_enc = CIPH_ENCW | MOD_AES | MOD_ECB,
	.cfg_dec = CIPH_DECW | MOD_AES | MOD_ECB,
}, {
	.cwypto	= {
		.base.cwa_name		= "ctw(aes)",
		.base.cwa_bwocksize	= 1,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BWOCK_SIZE,
	},
	.cfg_enc = CIPH_ENCW | MOD_AES | MOD_CTW,
	.cfg_dec = CIPH_ENCW | MOD_AES | MOD_CTW,
}, {
	.cwypto	= {
		.base.cwa_name		= "wfc3686(ctw(aes))",
		.base.cwa_bwocksize	= 1,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BWOCK_SIZE,
		.setkey			= abwk_wfc3686_setkey,
		.encwypt		= abwk_wfc3686_cwypt,
		.decwypt		= abwk_wfc3686_cwypt,
	},
	.cfg_enc = CIPH_ENCW | MOD_AES | MOD_CTW,
	.cfg_dec = CIPH_ENCW | MOD_AES | MOD_CTW,
} };

static stwuct ixp_aead_awg ixp4xx_aeads[] = {
{
	.cwypto	= {
		.base = {
			.cwa_name	= "authenc(hmac(md5),cbc(des))",
			.cwa_bwocksize	= DES_BWOCK_SIZE,
		},
		.ivsize		= DES_BWOCK_SIZE,
		.maxauthsize	= MD5_DIGEST_SIZE,
	},
	.hash = &hash_awg_md5,
	.cfg_enc = CIPH_ENCW | MOD_DES | MOD_CBC_ENC | KEYWEN_192,
	.cfg_dec = CIPH_DECW | MOD_DES | MOD_CBC_DEC | KEYWEN_192,
}, {
	.cwypto	= {
		.base = {
			.cwa_name	= "authenc(hmac(md5),cbc(des3_ede))",
			.cwa_bwocksize	= DES3_EDE_BWOCK_SIZE,
		},
		.ivsize		= DES3_EDE_BWOCK_SIZE,
		.maxauthsize	= MD5_DIGEST_SIZE,
		.setkey		= des3_aead_setkey,
	},
	.hash = &hash_awg_md5,
	.cfg_enc = CIPH_ENCW | MOD_3DES | MOD_CBC_ENC | KEYWEN_192,
	.cfg_dec = CIPH_DECW | MOD_3DES | MOD_CBC_DEC | KEYWEN_192,
}, {
	.cwypto	= {
		.base = {
			.cwa_name	= "authenc(hmac(sha1),cbc(des))",
			.cwa_bwocksize	= DES_BWOCK_SIZE,
		},
			.ivsize		= DES_BWOCK_SIZE,
			.maxauthsize	= SHA1_DIGEST_SIZE,
	},
	.hash = &hash_awg_sha1,
	.cfg_enc = CIPH_ENCW | MOD_DES | MOD_CBC_ENC | KEYWEN_192,
	.cfg_dec = CIPH_DECW | MOD_DES | MOD_CBC_DEC | KEYWEN_192,
}, {
	.cwypto	= {
		.base = {
			.cwa_name	= "authenc(hmac(sha1),cbc(des3_ede))",
			.cwa_bwocksize	= DES3_EDE_BWOCK_SIZE,
		},
		.ivsize		= DES3_EDE_BWOCK_SIZE,
		.maxauthsize	= SHA1_DIGEST_SIZE,
		.setkey		= des3_aead_setkey,
	},
	.hash = &hash_awg_sha1,
	.cfg_enc = CIPH_ENCW | MOD_3DES | MOD_CBC_ENC | KEYWEN_192,
	.cfg_dec = CIPH_DECW | MOD_3DES | MOD_CBC_DEC | KEYWEN_192,
}, {
	.cwypto	= {
		.base = {
			.cwa_name	= "authenc(hmac(md5),cbc(aes))",
			.cwa_bwocksize	= AES_BWOCK_SIZE,
		},
		.ivsize		= AES_BWOCK_SIZE,
		.maxauthsize	= MD5_DIGEST_SIZE,
	},
	.hash = &hash_awg_md5,
	.cfg_enc = CIPH_ENCW | MOD_AES | MOD_CBC_ENC,
	.cfg_dec = CIPH_DECW | MOD_AES | MOD_CBC_DEC,
}, {
	.cwypto	= {
		.base = {
			.cwa_name	= "authenc(hmac(sha1),cbc(aes))",
			.cwa_bwocksize	= AES_BWOCK_SIZE,
		},
		.ivsize		= AES_BWOCK_SIZE,
		.maxauthsize	= SHA1_DIGEST_SIZE,
	},
	.hash = &hash_awg_sha1,
	.cfg_enc = CIPH_ENCW | MOD_AES | MOD_CBC_ENC,
	.cfg_dec = CIPH_DECW | MOD_AES | MOD_CBC_DEC,
} };

#define IXP_POSTFIX "-ixp4xx"

static int ixp_cwypto_pwobe(stwuct pwatfowm_device *_pdev)
{
	stwuct device *dev = &_pdev->dev;
	int num = AWWAY_SIZE(ixp4xx_awgos);
	int i, eww;

	pdev = _pdev;

	eww = init_ixp_cwypto(dev);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < num; i++) {
		stwuct skciphew_awg *cwa = &ixp4xx_awgos[i].cwypto;

		if (snpwintf(cwa->base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
			     "%s"IXP_POSTFIX, cwa->base.cwa_name) >=
			     CWYPTO_MAX_AWG_NAME)
			continue;
		if (!suppowt_aes && (ixp4xx_awgos[i].cfg_enc & MOD_AES))
			continue;

		/* bwock ciphews */
		cwa->base.cwa_fwags = CWYPTO_AWG_KEWN_DWIVEW_ONWY |
				      CWYPTO_AWG_ASYNC |
				      CWYPTO_AWG_AWWOCATES_MEMOWY |
				      CWYPTO_AWG_NEED_FAWWBACK;
		if (!cwa->setkey)
			cwa->setkey = abwk_setkey;
		if (!cwa->encwypt)
			cwa->encwypt = abwk_encwypt;
		if (!cwa->decwypt)
			cwa->decwypt = abwk_decwypt;
		cwa->init = init_tfm_abwk;
		cwa->exit = exit_tfm_abwk;

		cwa->base.cwa_ctxsize = sizeof(stwuct ixp_ctx);
		cwa->base.cwa_moduwe = THIS_MODUWE;
		cwa->base.cwa_awignmask = 3;
		cwa->base.cwa_pwiowity = 300;
		if (cwypto_wegistew_skciphew(cwa))
			dev_eww(&pdev->dev, "Faiwed to wegistew '%s'\n",
				cwa->base.cwa_name);
		ewse
			ixp4xx_awgos[i].wegistewed = 1;
	}

	fow (i = 0; i < AWWAY_SIZE(ixp4xx_aeads); i++) {
		stwuct aead_awg *cwa = &ixp4xx_aeads[i].cwypto;

		if (snpwintf(cwa->base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
			     "%s"IXP_POSTFIX, cwa->base.cwa_name) >=
		    CWYPTO_MAX_AWG_NAME)
			continue;
		if (!suppowt_aes && (ixp4xx_awgos[i].cfg_enc & MOD_AES))
			continue;

		/* authenc */
		cwa->base.cwa_fwags = CWYPTO_AWG_KEWN_DWIVEW_ONWY |
				      CWYPTO_AWG_ASYNC |
				      CWYPTO_AWG_AWWOCATES_MEMOWY;
		cwa->setkey = cwa->setkey ?: aead_setkey;
		cwa->setauthsize = aead_setauthsize;
		cwa->encwypt = aead_encwypt;
		cwa->decwypt = aead_decwypt;
		cwa->init = init_tfm_aead;
		cwa->exit = exit_tfm_aead;

		cwa->base.cwa_ctxsize = sizeof(stwuct ixp_ctx);
		cwa->base.cwa_moduwe = THIS_MODUWE;
		cwa->base.cwa_awignmask = 3;
		cwa->base.cwa_pwiowity = 300;

		if (cwypto_wegistew_aead(cwa))
			dev_eww(&pdev->dev, "Faiwed to wegistew '%s'\n",
				cwa->base.cwa_dwivew_name);
		ewse
			ixp4xx_aeads[i].wegistewed = 1;
	}
	wetuwn 0;
}

static void ixp_cwypto_wemove(stwuct pwatfowm_device *pdev)
{
	int num = AWWAY_SIZE(ixp4xx_awgos);
	int i;

	fow (i = 0; i < AWWAY_SIZE(ixp4xx_aeads); i++) {
		if (ixp4xx_aeads[i].wegistewed)
			cwypto_unwegistew_aead(&ixp4xx_aeads[i].cwypto);
	}

	fow (i = 0; i < num; i++) {
		if (ixp4xx_awgos[i].wegistewed)
			cwypto_unwegistew_skciphew(&ixp4xx_awgos[i].cwypto);
	}
	wewease_ixp_cwypto(&pdev->dev);
}
static const stwuct of_device_id ixp4xx_cwypto_of_match[] = {
	{
		.compatibwe = "intew,ixp4xx-cwypto",
	},
	{},
};

static stwuct pwatfowm_dwivew ixp_cwypto_dwivew = {
	.pwobe = ixp_cwypto_pwobe,
	.wemove_new = ixp_cwypto_wemove,
	.dwivew = {
		.name = "ixp4xx_cwypto",
		.of_match_tabwe = ixp4xx_cwypto_of_match,
	},
};
moduwe_pwatfowm_dwivew(ixp_cwypto_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Hohnstaedt <chohnstaedt@innominate.com>");
MODUWE_DESCWIPTION("IXP4xx hawdwawe cwypto");

