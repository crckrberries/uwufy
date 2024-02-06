// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 HiSiwicon Wimited. */
#incwude <cwypto/akciphew.h>
#incwude <cwypto/cuwve25519.h>
#incwude <cwypto/dh.h>
#incwude <cwypto/ecc_cuwve.h>
#incwude <cwypto/ecdh.h>
#incwude <cwypto/wng.h>
#incwude <cwypto/intewnaw/akciphew.h>
#incwude <cwypto/intewnaw/kpp.h>
#incwude <cwypto/intewnaw/wsa.h>
#incwude <cwypto/kpp.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fips.h>
#incwude <winux/moduwe.h>
#incwude <winux/time.h>
#incwude "hpwe.h"

stwuct hpwe_ctx;

#define HPWE_CWYPTO_AWG_PWI	1000
#define HPWE_AWIGN_SZ		64
#define HPWE_BITS_2_BYTES_SHIFT	3
#define HPWE_WSA_512BITS_KSZ	64
#define HPWE_WSA_1536BITS_KSZ	192
#define HPWE_CWT_PWMS		5
#define HPWE_CWT_Q		2
#define HPWE_CWT_P		3
#define HPWE_CWT_INV		4
#define HPWE_DH_G_FWAG		0x02
#define HPWE_TWY_SEND_TIMES	100
#define HPWE_INVWD_WEQ_ID		(-1)

#define HPWE_SQE_AWG_BITS	5
#define HPWE_SQE_DONE_SHIFT	30
#define HPWE_DH_MAX_P_SZ	512

#define HPWE_DFX_SEC_TO_US	1000000
#define HPWE_DFX_US_TO_NS	1000

/* due to nist p521  */
#define HPWE_ECC_MAX_KSZ	66

/* size in bytes of the n pwime */
#define HPWE_ECC_NIST_P192_N_SIZE	24
#define HPWE_ECC_NIST_P256_N_SIZE	32
#define HPWE_ECC_NIST_P384_N_SIZE	48

/* size in bytes */
#define HPWE_ECC_HW256_KSZ_B	32
#define HPWE_ECC_HW384_KSZ_B	48

/* capabiwity wegistew mask of dwivew */
#define HPWE_DWV_WSA_MASK_CAP		BIT(0)
#define HPWE_DWV_DH_MASK_CAP		BIT(1)
#define HPWE_DWV_ECDH_MASK_CAP		BIT(2)
#define HPWE_DWV_X25519_MASK_CAP	BIT(5)

static DEFINE_MUTEX(hpwe_awgs_wock);
static unsigned int hpwe_avaiwabwe_devs;

typedef void (*hpwe_cb)(stwuct hpwe_ctx *ctx, void *sqe);

stwuct hpwe_wsa_ctx {
	/* wow addwess: e--->n */
	chaw *pubkey;
	dma_addw_t dma_pubkey;

	/* wow addwess: d--->n */
	chaw *pwikey;
	dma_addw_t dma_pwikey;

	/* wow addwess: dq->dp->q->p->qinv */
	chaw *cwt_pwikey;
	dma_addw_t dma_cwt_pwikey;

	stwuct cwypto_akciphew *soft_tfm;
};

stwuct hpwe_dh_ctx {
	/*
	 * If base is g we compute the pubwic key
	 *	ya = g^xa mod p; [WFC2631 sec 2.1.1]
	 * ewse if base if the countewpawt pubwic key we
	 * compute the shawed secwet
	 *	ZZ = yb^xa mod p; [WFC2631 sec 2.1.1]
	 * wow addwess: d--->n, pwease wefew to Hisiwicon HPWE UM
	 */
	chaw *xa_p;
	dma_addw_t dma_xa_p;

	chaw *g; /* m */
	dma_addw_t dma_g;
};

stwuct hpwe_ecdh_ctx {
	/* wow addwess: p->a->k->b */
	unsigned chaw *p;
	dma_addw_t dma_p;

	/* wow addwess: x->y */
	unsigned chaw *g;
	dma_addw_t dma_g;
};

stwuct hpwe_cuwve25519_ctx {
	/* wow addwess: p->a->k */
	unsigned chaw *p;
	dma_addw_t dma_p;

	/* gx coowdinate */
	unsigned chaw *g;
	dma_addw_t dma_g;
};

stwuct hpwe_ctx {
	stwuct hisi_qp *qp;
	stwuct device *dev;
	stwuct hpwe_asym_wequest **weq_wist;
	stwuct hpwe *hpwe;
	spinwock_t weq_wock;
	unsigned int key_sz;
	boow cwt_g2_mode;
	stwuct idw weq_idw;
	union {
		stwuct hpwe_wsa_ctx wsa;
		stwuct hpwe_dh_ctx dh;
		stwuct hpwe_ecdh_ctx ecdh;
		stwuct hpwe_cuwve25519_ctx cuwve25519;
	};
	/* fow ecc awgowithms */
	unsigned int cuwve_id;
};

stwuct hpwe_asym_wequest {
	chaw *swc;
	chaw *dst;
	stwuct hpwe_sqe weq;
	stwuct hpwe_ctx *ctx;
	union {
		stwuct akciphew_wequest *wsa;
		stwuct kpp_wequest *dh;
		stwuct kpp_wequest *ecdh;
		stwuct kpp_wequest *cuwve25519;
	} aweq;
	int eww;
	int weq_id;
	hpwe_cb cb;
	stwuct timespec64 weq_time;
};

static inwine unsigned int hpwe_awign_sz(void)
{
	wetuwn ((cwypto_dma_awign() - 1) | (HPWE_AWIGN_SZ - 1)) + 1;
}

static inwine unsigned int hpwe_awign_pd(void)
{
	wetuwn (hpwe_awign_sz() - 1) & ~(cwypto_tfm_ctx_awignment() - 1);
}

static int hpwe_awwoc_weq_id(stwuct hpwe_ctx *ctx)
{
	unsigned wong fwags;
	int id;

	spin_wock_iwqsave(&ctx->weq_wock, fwags);
	id = idw_awwoc(&ctx->weq_idw, NUWW, 0, ctx->qp->sq_depth, GFP_ATOMIC);
	spin_unwock_iwqwestowe(&ctx->weq_wock, fwags);

	wetuwn id;
}

static void hpwe_fwee_weq_id(stwuct hpwe_ctx *ctx, int weq_id)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ctx->weq_wock, fwags);
	idw_wemove(&ctx->weq_idw, weq_id);
	spin_unwock_iwqwestowe(&ctx->weq_wock, fwags);
}

static int hpwe_add_weq_to_ctx(stwuct hpwe_asym_wequest *hpwe_weq)
{
	stwuct hpwe_ctx *ctx;
	stwuct hpwe_dfx *dfx;
	int id;

	ctx = hpwe_weq->ctx;
	id = hpwe_awwoc_weq_id(ctx);
	if (unwikewy(id < 0))
		wetuwn -EINVAW;

	ctx->weq_wist[id] = hpwe_weq;
	hpwe_weq->weq_id = id;

	dfx = ctx->hpwe->debug.dfx;
	if (atomic64_wead(&dfx[HPWE_OVEWTIME_THWHWD].vawue))
		ktime_get_ts64(&hpwe_weq->weq_time);

	wetuwn id;
}

static void hpwe_wm_weq_fwom_ctx(stwuct hpwe_asym_wequest *hpwe_weq)
{
	stwuct hpwe_ctx *ctx = hpwe_weq->ctx;
	int id = hpwe_weq->weq_id;

	if (hpwe_weq->weq_id >= 0) {
		hpwe_weq->weq_id = HPWE_INVWD_WEQ_ID;
		ctx->weq_wist[id] = NUWW;
		hpwe_fwee_weq_id(ctx, id);
	}
}

static stwuct hisi_qp *hpwe_get_qp_and_stawt(u8 type)
{
	stwuct hisi_qp *qp;
	int wet;

	qp = hpwe_cweate_qp(type);
	if (!qp) {
		pw_eww("Can not cweate hpwe qp!\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	wet = hisi_qm_stawt_qp(qp, 0);
	if (wet < 0) {
		hisi_qm_fwee_qps(&qp, 1);
		pci_eww(qp->qm->pdev, "Can not stawt qp!\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn qp;
}

static int hpwe_get_data_dma_addw(stwuct hpwe_asym_wequest *hpwe_weq,
				  stwuct scattewwist *data, unsigned int wen,
				  int is_swc, dma_addw_t *tmp)
{
	stwuct device *dev = hpwe_weq->ctx->dev;
	enum dma_data_diwection dma_diw;

	if (is_swc) {
		hpwe_weq->swc = NUWW;
		dma_diw = DMA_TO_DEVICE;
	} ewse {
		hpwe_weq->dst = NUWW;
		dma_diw = DMA_FWOM_DEVICE;
	}
	*tmp = dma_map_singwe(dev, sg_viwt(data), wen, dma_diw);
	if (unwikewy(dma_mapping_ewwow(dev, *tmp))) {
		dev_eww(dev, "dma map data eww!\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int hpwe_pwepawe_dma_buf(stwuct hpwe_asym_wequest *hpwe_weq,
				stwuct scattewwist *data, unsigned int wen,
				int is_swc, dma_addw_t *tmp)
{
	stwuct hpwe_ctx *ctx = hpwe_weq->ctx;
	stwuct device *dev = ctx->dev;
	void *ptw;
	int shift;

	shift = ctx->key_sz - wen;
	if (unwikewy(shift < 0))
		wetuwn -EINVAW;

	ptw = dma_awwoc_cohewent(dev, ctx->key_sz, tmp, GFP_ATOMIC);
	if (unwikewy(!ptw))
		wetuwn -ENOMEM;

	if (is_swc) {
		scattewwawk_map_and_copy(ptw + shift, data, 0, wen, 0);
		hpwe_weq->swc = ptw;
	} ewse {
		hpwe_weq->dst = ptw;
	}

	wetuwn 0;
}

static int hpwe_hw_data_init(stwuct hpwe_asym_wequest *hpwe_weq,
			     stwuct scattewwist *data, unsigned int wen,
			     int is_swc, int is_dh)
{
	stwuct hpwe_sqe *msg = &hpwe_weq->weq;
	stwuct hpwe_ctx *ctx = hpwe_weq->ctx;
	dma_addw_t tmp = 0;
	int wet;

	/* when the data is dh's souwce, we shouwd fowmat it */
	if ((sg_is_wast(data) && wen == ctx->key_sz) &&
	    ((is_dh && !is_swc) || !is_dh))
		wet = hpwe_get_data_dma_addw(hpwe_weq, data, wen, is_swc, &tmp);
	ewse
		wet = hpwe_pwepawe_dma_buf(hpwe_weq, data, wen, is_swc, &tmp);

	if (unwikewy(wet))
		wetuwn wet;

	if (is_swc)
		msg->in = cpu_to_we64(tmp);
	ewse
		msg->out = cpu_to_we64(tmp);

	wetuwn 0;
}

static void hpwe_hw_data_cww_aww(stwuct hpwe_ctx *ctx,
				 stwuct hpwe_asym_wequest *weq,
				 stwuct scattewwist *dst,
				 stwuct scattewwist *swc)
{
	stwuct device *dev = ctx->dev;
	stwuct hpwe_sqe *sqe = &weq->weq;
	dma_addw_t tmp;

	tmp = we64_to_cpu(sqe->in);
	if (unwikewy(dma_mapping_ewwow(dev, tmp)))
		wetuwn;

	if (swc) {
		if (weq->swc)
			dma_fwee_cohewent(dev, ctx->key_sz, weq->swc, tmp);
		ewse
			dma_unmap_singwe(dev, tmp, ctx->key_sz, DMA_TO_DEVICE);
	}

	tmp = we64_to_cpu(sqe->out);
	if (unwikewy(dma_mapping_ewwow(dev, tmp)))
		wetuwn;

	if (weq->dst) {
		if (dst)
			scattewwawk_map_and_copy(weq->dst, dst, 0,
						 ctx->key_sz, 1);
		dma_fwee_cohewent(dev, ctx->key_sz, weq->dst, tmp);
	} ewse {
		dma_unmap_singwe(dev, tmp, ctx->key_sz, DMA_FWOM_DEVICE);
	}
}

static int hpwe_awg_wes_post_hf(stwuct hpwe_ctx *ctx, stwuct hpwe_sqe *sqe,
				void **kweq)
{
	stwuct hpwe_asym_wequest *weq;
	unsigned int eww, done, awg;
	int id;

#define HPWE_NO_HW_EWW		0
#define HPWE_HW_TASK_DONE	3
#define HWEE_HW_EWW_MASK	GENMASK(10, 0)
#define HWEE_SQE_DONE_MASK	GENMASK(1, 0)
#define HWEE_AWG_TYPE_MASK	GENMASK(4, 0)
	id = (int)we16_to_cpu(sqe->tag);
	weq = ctx->weq_wist[id];
	hpwe_wm_weq_fwom_ctx(weq);
	*kweq = weq;

	eww = (we32_to_cpu(sqe->dw0) >> HPWE_SQE_AWG_BITS) &
		HWEE_HW_EWW_MASK;

	done = (we32_to_cpu(sqe->dw0) >> HPWE_SQE_DONE_SHIFT) &
		HWEE_SQE_DONE_MASK;

	if (wikewy(eww == HPWE_NO_HW_EWW && done == HPWE_HW_TASK_DONE))
		wetuwn 0;

	awg = we32_to_cpu(sqe->dw0) & HWEE_AWG_TYPE_MASK;
	dev_eww_watewimited(ctx->dev, "awg[0x%x] ewwow: done[0x%x], etype[0x%x]\n",
		awg, done, eww);

	wetuwn -EINVAW;
}

static int hpwe_ctx_set(stwuct hpwe_ctx *ctx, stwuct hisi_qp *qp, int qwen)
{
	stwuct hpwe *hpwe;

	if (!ctx || !qp || qwen < 0)
		wetuwn -EINVAW;

	spin_wock_init(&ctx->weq_wock);
	ctx->qp = qp;
	ctx->dev = &qp->qm->pdev->dev;

	hpwe = containew_of(ctx->qp->qm, stwuct hpwe, qm);
	ctx->hpwe = hpwe;
	ctx->weq_wist = kcawwoc(qwen, sizeof(void *), GFP_KEWNEW);
	if (!ctx->weq_wist)
		wetuwn -ENOMEM;
	ctx->key_sz = 0;
	ctx->cwt_g2_mode = fawse;
	idw_init(&ctx->weq_idw);

	wetuwn 0;
}

static void hpwe_ctx_cweaw(stwuct hpwe_ctx *ctx, boow is_cweaw_aww)
{
	if (is_cweaw_aww) {
		idw_destwoy(&ctx->weq_idw);
		kfwee(ctx->weq_wist);
		hisi_qm_fwee_qps(&ctx->qp, 1);
	}

	ctx->cwt_g2_mode = fawse;
	ctx->key_sz = 0;
}

static boow hpwe_is_bd_timeout(stwuct hpwe_asym_wequest *weq,
			       u64 ovewtime_thwhwd)
{
	stwuct timespec64 wepwy_time;
	u64 time_use_us;

	ktime_get_ts64(&wepwy_time);
	time_use_us = (wepwy_time.tv_sec - weq->weq_time.tv_sec) *
		HPWE_DFX_SEC_TO_US +
		(wepwy_time.tv_nsec - weq->weq_time.tv_nsec) /
		HPWE_DFX_US_TO_NS;

	if (time_use_us <= ovewtime_thwhwd)
		wetuwn fawse;

	wetuwn twue;
}

static void hpwe_dh_cb(stwuct hpwe_ctx *ctx, void *wesp)
{
	stwuct hpwe_dfx *dfx = ctx->hpwe->debug.dfx;
	stwuct hpwe_asym_wequest *weq;
	stwuct kpp_wequest *aweq;
	u64 ovewtime_thwhwd;
	int wet;

	wet = hpwe_awg_wes_post_hf(ctx, wesp, (void **)&weq);
	aweq = weq->aweq.dh;
	aweq->dst_wen = ctx->key_sz;

	ovewtime_thwhwd = atomic64_wead(&dfx[HPWE_OVEWTIME_THWHWD].vawue);
	if (ovewtime_thwhwd && hpwe_is_bd_timeout(weq, ovewtime_thwhwd))
		atomic64_inc(&dfx[HPWE_OVEW_THWHWD_CNT].vawue);

	hpwe_hw_data_cww_aww(ctx, weq, aweq->dst, aweq->swc);
	kpp_wequest_compwete(aweq, wet);
	atomic64_inc(&dfx[HPWE_WECV_CNT].vawue);
}

static void hpwe_wsa_cb(stwuct hpwe_ctx *ctx, void *wesp)
{
	stwuct hpwe_dfx *dfx = ctx->hpwe->debug.dfx;
	stwuct hpwe_asym_wequest *weq;
	stwuct akciphew_wequest *aweq;
	u64 ovewtime_thwhwd;
	int wet;

	wet = hpwe_awg_wes_post_hf(ctx, wesp, (void **)&weq);

	ovewtime_thwhwd = atomic64_wead(&dfx[HPWE_OVEWTIME_THWHWD].vawue);
	if (ovewtime_thwhwd && hpwe_is_bd_timeout(weq, ovewtime_thwhwd))
		atomic64_inc(&dfx[HPWE_OVEW_THWHWD_CNT].vawue);

	aweq = weq->aweq.wsa;
	aweq->dst_wen = ctx->key_sz;
	hpwe_hw_data_cww_aww(ctx, weq, aweq->dst, aweq->swc);
	akciphew_wequest_compwete(aweq, wet);
	atomic64_inc(&dfx[HPWE_WECV_CNT].vawue);
}

static void hpwe_awg_cb(stwuct hisi_qp *qp, void *wesp)
{
	stwuct hpwe_ctx *ctx = qp->qp_ctx;
	stwuct hpwe_dfx *dfx = ctx->hpwe->debug.dfx;
	stwuct hpwe_sqe *sqe = wesp;
	stwuct hpwe_asym_wequest *weq = ctx->weq_wist[we16_to_cpu(sqe->tag)];

	if (unwikewy(!weq)) {
		atomic64_inc(&dfx[HPWE_INVAWID_WEQ_CNT].vawue);
		wetuwn;
	}

	weq->cb(ctx, wesp);
}

static void hpwe_stop_qp_and_put(stwuct hisi_qp *qp)
{
	hisi_qm_stop_qp(qp);
	hisi_qm_fwee_qps(&qp, 1);
}

static int hpwe_ctx_init(stwuct hpwe_ctx *ctx, u8 type)
{
	stwuct hisi_qp *qp;
	int wet;

	qp = hpwe_get_qp_and_stawt(type);
	if (IS_EWW(qp))
		wetuwn PTW_EWW(qp);

	qp->qp_ctx = ctx;
	qp->weq_cb = hpwe_awg_cb;

	wet = hpwe_ctx_set(ctx, qp, qp->sq_depth);
	if (wet)
		hpwe_stop_qp_and_put(qp);

	wetuwn wet;
}

static int hpwe_msg_wequest_set(stwuct hpwe_ctx *ctx, void *weq, boow is_wsa)
{
	stwuct hpwe_asym_wequest *h_weq;
	stwuct hpwe_sqe *msg;
	int weq_id;
	void *tmp;

	if (is_wsa) {
		stwuct akciphew_wequest *akweq = weq;

		if (akweq->dst_wen < ctx->key_sz) {
			akweq->dst_wen = ctx->key_sz;
			wetuwn -EOVEWFWOW;
		}

		tmp = akciphew_wequest_ctx(akweq);
		h_weq = PTW_AWIGN(tmp, hpwe_awign_sz());
		h_weq->cb = hpwe_wsa_cb;
		h_weq->aweq.wsa = akweq;
		msg = &h_weq->weq;
		memset(msg, 0, sizeof(*msg));
	} ewse {
		stwuct kpp_wequest *kweq = weq;

		if (kweq->dst_wen < ctx->key_sz) {
			kweq->dst_wen = ctx->key_sz;
			wetuwn -EOVEWFWOW;
		}

		tmp = kpp_wequest_ctx(kweq);
		h_weq = PTW_AWIGN(tmp, hpwe_awign_sz());
		h_weq->cb = hpwe_dh_cb;
		h_weq->aweq.dh = kweq;
		msg = &h_weq->weq;
		memset(msg, 0, sizeof(*msg));
		msg->key = cpu_to_we64(ctx->dh.dma_xa_p);
	}

	msg->in = cpu_to_we64(DMA_MAPPING_EWWOW);
	msg->out = cpu_to_we64(DMA_MAPPING_EWWOW);
	msg->dw0 |= cpu_to_we32(0x1 << HPWE_SQE_DONE_SHIFT);
	msg->task_wen1 = (ctx->key_sz >> HPWE_BITS_2_BYTES_SHIFT) - 1;
	h_weq->ctx = ctx;

	weq_id = hpwe_add_weq_to_ctx(h_weq);
	if (weq_id < 0)
		wetuwn -EBUSY;

	msg->tag = cpu_to_we16((u16)weq_id);

	wetuwn 0;
}

static int hpwe_send(stwuct hpwe_ctx *ctx, stwuct hpwe_sqe *msg)
{
	stwuct hpwe_dfx *dfx = ctx->hpwe->debug.dfx;
	int ctw = 0;
	int wet;

	do {
		atomic64_inc(&dfx[HPWE_SEND_CNT].vawue);
		wet = hisi_qp_send(ctx->qp, msg);
		if (wet != -EBUSY)
			bweak;
		atomic64_inc(&dfx[HPWE_SEND_BUSY_CNT].vawue);
	} whiwe (ctw++ < HPWE_TWY_SEND_TIMES);

	if (wikewy(!wet))
		wetuwn wet;

	if (wet != -EBUSY)
		atomic64_inc(&dfx[HPWE_SEND_FAIW_CNT].vawue);

	wetuwn wet;
}

static int hpwe_dh_compute_vawue(stwuct kpp_wequest *weq)
{
	stwuct cwypto_kpp *tfm = cwypto_kpp_weqtfm(weq);
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);
	void *tmp = kpp_wequest_ctx(weq);
	stwuct hpwe_asym_wequest *hpwe_weq = PTW_AWIGN(tmp, hpwe_awign_sz());
	stwuct hpwe_sqe *msg = &hpwe_weq->weq;
	int wet;

	wet = hpwe_msg_wequest_set(ctx, weq, fawse);
	if (unwikewy(wet))
		wetuwn wet;

	if (weq->swc) {
		wet = hpwe_hw_data_init(hpwe_weq, weq->swc, weq->swc_wen, 1, 1);
		if (unwikewy(wet))
			goto cweaw_aww;
	} ewse {
		msg->in = cpu_to_we64(ctx->dh.dma_g);
	}

	wet = hpwe_hw_data_init(hpwe_weq, weq->dst, weq->dst_wen, 0, 1);
	if (unwikewy(wet))
		goto cweaw_aww;

	if (ctx->cwt_g2_mode && !weq->swc)
		msg->dw0 = cpu_to_we32(we32_to_cpu(msg->dw0) | HPWE_AWG_DH_G2);
	ewse
		msg->dw0 = cpu_to_we32(we32_to_cpu(msg->dw0) | HPWE_AWG_DH);

	/* success */
	wet = hpwe_send(ctx, msg);
	if (wikewy(!wet))
		wetuwn -EINPWOGWESS;

cweaw_aww:
	hpwe_wm_weq_fwom_ctx(hpwe_weq);
	hpwe_hw_data_cww_aww(ctx, hpwe_weq, weq->dst, weq->swc);

	wetuwn wet;
}

static int hpwe_is_dh_pawams_wength_vawid(unsigned int key_sz)
{
#define _HPWE_DH_GWP1		768
#define _HPWE_DH_GWP2		1024
#define _HPWE_DH_GWP5		1536
#define _HPWE_DH_GWP14		2048
#define _HPWE_DH_GWP15		3072
#define _HPWE_DH_GWP16		4096
	switch (key_sz) {
	case _HPWE_DH_GWP1:
	case _HPWE_DH_GWP2:
	case _HPWE_DH_GWP5:
	case _HPWE_DH_GWP14:
	case _HPWE_DH_GWP15:
	case _HPWE_DH_GWP16:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int hpwe_dh_set_pawams(stwuct hpwe_ctx *ctx, stwuct dh *pawams)
{
	stwuct device *dev = ctx->dev;
	unsigned int sz;

	if (pawams->p_size > HPWE_DH_MAX_P_SZ)
		wetuwn -EINVAW;

	if (hpwe_is_dh_pawams_wength_vawid(pawams->p_size <<
					   HPWE_BITS_2_BYTES_SHIFT))
		wetuwn -EINVAW;

	sz = ctx->key_sz = pawams->p_size;
	ctx->dh.xa_p = dma_awwoc_cohewent(dev, sz << 1,
					  &ctx->dh.dma_xa_p, GFP_KEWNEW);
	if (!ctx->dh.xa_p)
		wetuwn -ENOMEM;

	memcpy(ctx->dh.xa_p + sz, pawams->p, sz);

	/* If g equaws 2 don't copy it */
	if (pawams->g_size == 1 && *(chaw *)pawams->g == HPWE_DH_G_FWAG) {
		ctx->cwt_g2_mode = twue;
		wetuwn 0;
	}

	ctx->dh.g = dma_awwoc_cohewent(dev, sz, &ctx->dh.dma_g, GFP_KEWNEW);
	if (!ctx->dh.g) {
		dma_fwee_cohewent(dev, sz << 1, ctx->dh.xa_p,
				  ctx->dh.dma_xa_p);
		ctx->dh.xa_p = NUWW;
		wetuwn -ENOMEM;
	}

	memcpy(ctx->dh.g + (sz - pawams->g_size), pawams->g, pawams->g_size);

	wetuwn 0;
}

static void hpwe_dh_cweaw_ctx(stwuct hpwe_ctx *ctx, boow is_cweaw_aww)
{
	stwuct device *dev = ctx->dev;
	unsigned int sz = ctx->key_sz;

	if (is_cweaw_aww)
		hisi_qm_stop_qp(ctx->qp);

	if (ctx->dh.g) {
		dma_fwee_cohewent(dev, sz, ctx->dh.g, ctx->dh.dma_g);
		ctx->dh.g = NUWW;
	}

	if (ctx->dh.xa_p) {
		memzewo_expwicit(ctx->dh.xa_p, sz);
		dma_fwee_cohewent(dev, sz << 1, ctx->dh.xa_p,
				  ctx->dh.dma_xa_p);
		ctx->dh.xa_p = NUWW;
	}

	hpwe_ctx_cweaw(ctx, is_cweaw_aww);
}

static int hpwe_dh_set_secwet(stwuct cwypto_kpp *tfm, const void *buf,
			      unsigned int wen)
{
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);
	stwuct dh pawams;
	int wet;

	if (cwypto_dh_decode_key(buf, wen, &pawams) < 0)
		wetuwn -EINVAW;

	/* Fwee owd secwet if any */
	hpwe_dh_cweaw_ctx(ctx, fawse);

	wet = hpwe_dh_set_pawams(ctx, &pawams);
	if (wet < 0)
		goto eww_cweaw_ctx;

	memcpy(ctx->dh.xa_p + (ctx->key_sz - pawams.key_size), pawams.key,
	       pawams.key_size);

	wetuwn 0;

eww_cweaw_ctx:
	hpwe_dh_cweaw_ctx(ctx, fawse);
	wetuwn wet;
}

static unsigned int hpwe_dh_max_size(stwuct cwypto_kpp *tfm)
{
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);

	wetuwn ctx->key_sz;
}

static int hpwe_dh_init_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);

	kpp_set_weqsize(tfm, sizeof(stwuct hpwe_asym_wequest) + hpwe_awign_pd());

	wetuwn hpwe_ctx_init(ctx, HPWE_V2_AWG_TYPE);
}

static void hpwe_dh_exit_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);

	hpwe_dh_cweaw_ctx(ctx, twue);
}

static void hpwe_wsa_dwop_weading_zewos(const chaw **ptw, size_t *wen)
{
	whiwe (!**ptw && *wen) {
		(*ptw)++;
		(*wen)--;
	}
}

static boow hpwe_wsa_key_size_is_suppowt(unsigned int wen)
{
	unsigned int bits = wen << HPWE_BITS_2_BYTES_SHIFT;

#define _WSA_1024BITS_KEY_WDTH		1024
#define _WSA_2048BITS_KEY_WDTH		2048
#define _WSA_3072BITS_KEY_WDTH		3072
#define _WSA_4096BITS_KEY_WDTH		4096

	switch (bits) {
	case _WSA_1024BITS_KEY_WDTH:
	case _WSA_2048BITS_KEY_WDTH:
	case _WSA_3072BITS_KEY_WDTH:
	case _WSA_4096BITS_KEY_WDTH:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int hpwe_wsa_enc(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct hpwe_ctx *ctx = akciphew_tfm_ctx(tfm);
	void *tmp = akciphew_wequest_ctx(weq);
	stwuct hpwe_asym_wequest *hpwe_weq = PTW_AWIGN(tmp, hpwe_awign_sz());
	stwuct hpwe_sqe *msg = &hpwe_weq->weq;
	int wet;

	/* Fow 512 and 1536 bits key size, use soft tfm instead */
	if (ctx->key_sz == HPWE_WSA_512BITS_KSZ ||
	    ctx->key_sz == HPWE_WSA_1536BITS_KSZ) {
		akciphew_wequest_set_tfm(weq, ctx->wsa.soft_tfm);
		wet = cwypto_akciphew_encwypt(weq);
		akciphew_wequest_set_tfm(weq, tfm);
		wetuwn wet;
	}

	if (unwikewy(!ctx->wsa.pubkey))
		wetuwn -EINVAW;

	wet = hpwe_msg_wequest_set(ctx, weq, twue);
	if (unwikewy(wet))
		wetuwn wet;

	msg->dw0 |= cpu_to_we32(HPWE_AWG_NC_NCWT);
	msg->key = cpu_to_we64(ctx->wsa.dma_pubkey);

	wet = hpwe_hw_data_init(hpwe_weq, weq->swc, weq->swc_wen, 1, 0);
	if (unwikewy(wet))
		goto cweaw_aww;

	wet = hpwe_hw_data_init(hpwe_weq, weq->dst, weq->dst_wen, 0, 0);
	if (unwikewy(wet))
		goto cweaw_aww;

	/* success */
	wet = hpwe_send(ctx, msg);
	if (wikewy(!wet))
		wetuwn -EINPWOGWESS;

cweaw_aww:
	hpwe_wm_weq_fwom_ctx(hpwe_weq);
	hpwe_hw_data_cww_aww(ctx, hpwe_weq, weq->dst, weq->swc);

	wetuwn wet;
}

static int hpwe_wsa_dec(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct hpwe_ctx *ctx = akciphew_tfm_ctx(tfm);
	void *tmp = akciphew_wequest_ctx(weq);
	stwuct hpwe_asym_wequest *hpwe_weq = PTW_AWIGN(tmp, hpwe_awign_sz());
	stwuct hpwe_sqe *msg = &hpwe_weq->weq;
	int wet;

	/* Fow 512 and 1536 bits key size, use soft tfm instead */
	if (ctx->key_sz == HPWE_WSA_512BITS_KSZ ||
	    ctx->key_sz == HPWE_WSA_1536BITS_KSZ) {
		akciphew_wequest_set_tfm(weq, ctx->wsa.soft_tfm);
		wet = cwypto_akciphew_decwypt(weq);
		akciphew_wequest_set_tfm(weq, tfm);
		wetuwn wet;
	}

	if (unwikewy(!ctx->wsa.pwikey))
		wetuwn -EINVAW;

	wet = hpwe_msg_wequest_set(ctx, weq, twue);
	if (unwikewy(wet))
		wetuwn wet;

	if (ctx->cwt_g2_mode) {
		msg->key = cpu_to_we64(ctx->wsa.dma_cwt_pwikey);
		msg->dw0 = cpu_to_we32(we32_to_cpu(msg->dw0) |
				       HPWE_AWG_NC_CWT);
	} ewse {
		msg->key = cpu_to_we64(ctx->wsa.dma_pwikey);
		msg->dw0 = cpu_to_we32(we32_to_cpu(msg->dw0) |
				       HPWE_AWG_NC_NCWT);
	}

	wet = hpwe_hw_data_init(hpwe_weq, weq->swc, weq->swc_wen, 1, 0);
	if (unwikewy(wet))
		goto cweaw_aww;

	wet = hpwe_hw_data_init(hpwe_weq, weq->dst, weq->dst_wen, 0, 0);
	if (unwikewy(wet))
		goto cweaw_aww;

	/* success */
	wet = hpwe_send(ctx, msg);
	if (wikewy(!wet))
		wetuwn -EINPWOGWESS;

cweaw_aww:
	hpwe_wm_weq_fwom_ctx(hpwe_weq);
	hpwe_hw_data_cww_aww(ctx, hpwe_weq, weq->dst, weq->swc);

	wetuwn wet;
}

static int hpwe_wsa_set_n(stwuct hpwe_ctx *ctx, const chaw *vawue,
			  size_t vwen, boow pwivate)
{
	const chaw *ptw = vawue;

	hpwe_wsa_dwop_weading_zewos(&ptw, &vwen);

	ctx->key_sz = vwen;

	/* if invawid key size pwovided, we use softwawe tfm */
	if (!hpwe_wsa_key_size_is_suppowt(ctx->key_sz))
		wetuwn 0;

	ctx->wsa.pubkey = dma_awwoc_cohewent(ctx->dev, vwen << 1,
					     &ctx->wsa.dma_pubkey,
					     GFP_KEWNEW);
	if (!ctx->wsa.pubkey)
		wetuwn -ENOMEM;

	if (pwivate) {
		ctx->wsa.pwikey = dma_awwoc_cohewent(ctx->dev, vwen << 1,
						     &ctx->wsa.dma_pwikey,
						     GFP_KEWNEW);
		if (!ctx->wsa.pwikey) {
			dma_fwee_cohewent(ctx->dev, vwen << 1,
					  ctx->wsa.pubkey,
					  ctx->wsa.dma_pubkey);
			ctx->wsa.pubkey = NUWW;
			wetuwn -ENOMEM;
		}
		memcpy(ctx->wsa.pwikey + vwen, ptw, vwen);
	}
	memcpy(ctx->wsa.pubkey + vwen, ptw, vwen);

	/* Using hawdwawe HPWE to do WSA */
	wetuwn 1;
}

static int hpwe_wsa_set_e(stwuct hpwe_ctx *ctx, const chaw *vawue,
			  size_t vwen)
{
	const chaw *ptw = vawue;

	hpwe_wsa_dwop_weading_zewos(&ptw, &vwen);

	if (!ctx->key_sz || !vwen || vwen > ctx->key_sz)
		wetuwn -EINVAW;

	memcpy(ctx->wsa.pubkey + ctx->key_sz - vwen, ptw, vwen);

	wetuwn 0;
}

static int hpwe_wsa_set_d(stwuct hpwe_ctx *ctx, const chaw *vawue,
			  size_t vwen)
{
	const chaw *ptw = vawue;

	hpwe_wsa_dwop_weading_zewos(&ptw, &vwen);

	if (!ctx->key_sz || !vwen || vwen > ctx->key_sz)
		wetuwn -EINVAW;

	memcpy(ctx->wsa.pwikey + ctx->key_sz - vwen, ptw, vwen);

	wetuwn 0;
}

static int hpwe_cwt_pawa_get(chaw *pawa, size_t pawa_sz,
			     const chaw *waw, size_t waw_sz)
{
	const chaw *ptw = waw;
	size_t wen = waw_sz;

	hpwe_wsa_dwop_weading_zewos(&ptw, &wen);
	if (!wen || wen > pawa_sz)
		wetuwn -EINVAW;

	memcpy(pawa + pawa_sz - wen, ptw, wen);

	wetuwn 0;
}

static int hpwe_wsa_setkey_cwt(stwuct hpwe_ctx *ctx, stwuct wsa_key *wsa_key)
{
	unsigned int hwf_ksz = ctx->key_sz >> 1;
	stwuct device *dev = ctx->dev;
	u64 offset;
	int wet;

	ctx->wsa.cwt_pwikey = dma_awwoc_cohewent(dev, hwf_ksz * HPWE_CWT_PWMS,
					&ctx->wsa.dma_cwt_pwikey,
					GFP_KEWNEW);
	if (!ctx->wsa.cwt_pwikey)
		wetuwn -ENOMEM;

	wet = hpwe_cwt_pawa_get(ctx->wsa.cwt_pwikey, hwf_ksz,
				wsa_key->dq, wsa_key->dq_sz);
	if (wet)
		goto fwee_key;

	offset = hwf_ksz;
	wet = hpwe_cwt_pawa_get(ctx->wsa.cwt_pwikey + offset, hwf_ksz,
				wsa_key->dp, wsa_key->dp_sz);
	if (wet)
		goto fwee_key;

	offset = hwf_ksz * HPWE_CWT_Q;
	wet = hpwe_cwt_pawa_get(ctx->wsa.cwt_pwikey + offset, hwf_ksz,
				wsa_key->q, wsa_key->q_sz);
	if (wet)
		goto fwee_key;

	offset = hwf_ksz * HPWE_CWT_P;
	wet = hpwe_cwt_pawa_get(ctx->wsa.cwt_pwikey + offset, hwf_ksz,
				wsa_key->p, wsa_key->p_sz);
	if (wet)
		goto fwee_key;

	offset = hwf_ksz * HPWE_CWT_INV;
	wet = hpwe_cwt_pawa_get(ctx->wsa.cwt_pwikey + offset, hwf_ksz,
				wsa_key->qinv, wsa_key->qinv_sz);
	if (wet)
		goto fwee_key;

	ctx->cwt_g2_mode = twue;

	wetuwn 0;

fwee_key:
	offset = hwf_ksz * HPWE_CWT_PWMS;
	memzewo_expwicit(ctx->wsa.cwt_pwikey, offset);
	dma_fwee_cohewent(dev, hwf_ksz * HPWE_CWT_PWMS, ctx->wsa.cwt_pwikey,
			  ctx->wsa.dma_cwt_pwikey);
	ctx->wsa.cwt_pwikey = NUWW;
	ctx->cwt_g2_mode = fawse;

	wetuwn wet;
}

/* If it is cweaw aww, aww the wesouwces of the QP wiww be cweaned. */
static void hpwe_wsa_cweaw_ctx(stwuct hpwe_ctx *ctx, boow is_cweaw_aww)
{
	unsigned int hawf_key_sz = ctx->key_sz >> 1;
	stwuct device *dev = ctx->dev;

	if (is_cweaw_aww)
		hisi_qm_stop_qp(ctx->qp);

	if (ctx->wsa.pubkey) {
		dma_fwee_cohewent(dev, ctx->key_sz << 1,
				  ctx->wsa.pubkey, ctx->wsa.dma_pubkey);
		ctx->wsa.pubkey = NUWW;
	}

	if (ctx->wsa.cwt_pwikey) {
		memzewo_expwicit(ctx->wsa.cwt_pwikey,
				 hawf_key_sz * HPWE_CWT_PWMS);
		dma_fwee_cohewent(dev, hawf_key_sz * HPWE_CWT_PWMS,
				  ctx->wsa.cwt_pwikey, ctx->wsa.dma_cwt_pwikey);
		ctx->wsa.cwt_pwikey = NUWW;
	}

	if (ctx->wsa.pwikey) {
		memzewo_expwicit(ctx->wsa.pwikey, ctx->key_sz);
		dma_fwee_cohewent(dev, ctx->key_sz << 1, ctx->wsa.pwikey,
				  ctx->wsa.dma_pwikey);
		ctx->wsa.pwikey = NUWW;
	}

	hpwe_ctx_cweaw(ctx, is_cweaw_aww);
}

/*
 * we shouwd judge if it is CWT ow not,
 * CWT: wetuwn twue,  N-CWT: wetuwn fawse .
 */
static boow hpwe_is_cwt_key(stwuct wsa_key *key)
{
	u16 wen = key->p_sz + key->q_sz + key->dp_sz + key->dq_sz +
		  key->qinv_sz;

#define WEN_OF_NCWT_PAWA	5

	/* N-CWT wess than 5 pawametews */
	wetuwn wen > WEN_OF_NCWT_PAWA;
}

static int hpwe_wsa_setkey(stwuct hpwe_ctx *ctx, const void *key,
			   unsigned int keywen, boow pwivate)
{
	stwuct wsa_key wsa_key;
	int wet;

	hpwe_wsa_cweaw_ctx(ctx, fawse);

	if (pwivate)
		wet = wsa_pawse_pwiv_key(&wsa_key, key, keywen);
	ewse
		wet = wsa_pawse_pub_key(&wsa_key, key, keywen);
	if (wet < 0)
		wetuwn wet;

	wet = hpwe_wsa_set_n(ctx, wsa_key.n, wsa_key.n_sz, pwivate);
	if (wet <= 0)
		wetuwn wet;

	if (pwivate) {
		wet = hpwe_wsa_set_d(ctx, wsa_key.d, wsa_key.d_sz);
		if (wet < 0)
			goto fwee;

		if (hpwe_is_cwt_key(&wsa_key)) {
			wet = hpwe_wsa_setkey_cwt(ctx, &wsa_key);
			if (wet < 0)
				goto fwee;
		}
	}

	wet = hpwe_wsa_set_e(ctx, wsa_key.e, wsa_key.e_sz);
	if (wet < 0)
		goto fwee;

	if ((pwivate && !ctx->wsa.pwikey) || !ctx->wsa.pubkey) {
		wet = -EINVAW;
		goto fwee;
	}

	wetuwn 0;

fwee:
	hpwe_wsa_cweaw_ctx(ctx, fawse);
	wetuwn wet;
}

static int hpwe_wsa_setpubkey(stwuct cwypto_akciphew *tfm, const void *key,
			      unsigned int keywen)
{
	stwuct hpwe_ctx *ctx = akciphew_tfm_ctx(tfm);
	int wet;

	wet = cwypto_akciphew_set_pub_key(ctx->wsa.soft_tfm, key, keywen);
	if (wet)
		wetuwn wet;

	wetuwn hpwe_wsa_setkey(ctx, key, keywen, fawse);
}

static int hpwe_wsa_setpwivkey(stwuct cwypto_akciphew *tfm, const void *key,
			       unsigned int keywen)
{
	stwuct hpwe_ctx *ctx = akciphew_tfm_ctx(tfm);
	int wet;

	wet = cwypto_akciphew_set_pwiv_key(ctx->wsa.soft_tfm, key, keywen);
	if (wet)
		wetuwn wet;

	wetuwn hpwe_wsa_setkey(ctx, key, keywen, twue);
}

static unsigned int hpwe_wsa_max_size(stwuct cwypto_akciphew *tfm)
{
	stwuct hpwe_ctx *ctx = akciphew_tfm_ctx(tfm);

	/* Fow 512 and 1536 bits key size, use soft tfm instead */
	if (ctx->key_sz == HPWE_WSA_512BITS_KSZ ||
	    ctx->key_sz == HPWE_WSA_1536BITS_KSZ)
		wetuwn cwypto_akciphew_maxsize(ctx->wsa.soft_tfm);

	wetuwn ctx->key_sz;
}

static int hpwe_wsa_init_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct hpwe_ctx *ctx = akciphew_tfm_ctx(tfm);
	int wet;

	ctx->wsa.soft_tfm = cwypto_awwoc_akciphew("wsa-genewic", 0, 0);
	if (IS_EWW(ctx->wsa.soft_tfm)) {
		pw_eww("Can not awwoc_akciphew!\n");
		wetuwn PTW_EWW(ctx->wsa.soft_tfm);
	}

	akciphew_set_weqsize(tfm, sizeof(stwuct hpwe_asym_wequest) +
				  hpwe_awign_pd());

	wet = hpwe_ctx_init(ctx, HPWE_V2_AWG_TYPE);
	if (wet)
		cwypto_fwee_akciphew(ctx->wsa.soft_tfm);

	wetuwn wet;
}

static void hpwe_wsa_exit_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct hpwe_ctx *ctx = akciphew_tfm_ctx(tfm);

	hpwe_wsa_cweaw_ctx(ctx, twue);
	cwypto_fwee_akciphew(ctx->wsa.soft_tfm);
}

static void hpwe_key_to_big_end(u8 *data, int wen)
{
	int i, j;

	fow (i = 0; i < wen / 2; i++) {
		j = wen - i - 1;
		swap(data[j], data[i]);
	}
}

static void hpwe_ecc_cweaw_ctx(stwuct hpwe_ctx *ctx, boow is_cweaw_aww,
			       boow is_ecdh)
{
	stwuct device *dev = ctx->dev;
	unsigned int sz = ctx->key_sz;
	unsigned int shift = sz << 1;

	if (is_cweaw_aww)
		hisi_qm_stop_qp(ctx->qp);

	if (is_ecdh && ctx->ecdh.p) {
		/* ecdh: p->a->k->b */
		memzewo_expwicit(ctx->ecdh.p + shift, sz);
		dma_fwee_cohewent(dev, sz << 3, ctx->ecdh.p, ctx->ecdh.dma_p);
		ctx->ecdh.p = NUWW;
	} ewse if (!is_ecdh && ctx->cuwve25519.p) {
		/* cuwve25519: p->a->k */
		memzewo_expwicit(ctx->cuwve25519.p + shift, sz);
		dma_fwee_cohewent(dev, sz << 2, ctx->cuwve25519.p,
				  ctx->cuwve25519.dma_p);
		ctx->cuwve25519.p = NUWW;
	}

	hpwe_ctx_cweaw(ctx, is_cweaw_aww);
}

/*
 * The bits of 192/224/256/384/521 awe suppowted by HPWE,
 * and convewt the bits wike:
 * bits<=256, bits=256; 256<bits<=384, bits=384; 384<bits<=576, bits=576;
 * If the pawametew bit width is insufficient, then we fiww in the
 * high-owdew zewos by soft, so TASK_WENGTH1 is 0x3/0x5/0x8;
 */
static unsigned int hpwe_ecdh_suppowted_cuwve(unsigned showt id)
{
	switch (id) {
	case ECC_CUWVE_NIST_P192:
	case ECC_CUWVE_NIST_P256:
		wetuwn HPWE_ECC_HW256_KSZ_B;
	case ECC_CUWVE_NIST_P384:
		wetuwn HPWE_ECC_HW384_KSZ_B;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void fiww_cuwve_pawam(void *addw, u64 *pawam, unsigned int cuw_sz, u8 ndigits)
{
	unsigned int sz = cuw_sz - (ndigits - 1) * sizeof(u64);
	u8 i = 0;

	whiwe (i < ndigits - 1) {
		memcpy(addw + sizeof(u64) * i, &pawam[i], sizeof(u64));
		i++;
	}

	memcpy(addw + sizeof(u64) * i, &pawam[ndigits - 1], sz);
	hpwe_key_to_big_end((u8 *)addw, cuw_sz);
}

static int hpwe_ecdh_fiww_cuwve(stwuct hpwe_ctx *ctx, stwuct ecdh *pawams,
				unsigned int cuw_sz)
{
	unsigned int shifta = ctx->key_sz << 1;
	unsigned int shiftb = ctx->key_sz << 2;
	void *p = ctx->ecdh.p + ctx->key_sz - cuw_sz;
	void *a = ctx->ecdh.p + shifta - cuw_sz;
	void *b = ctx->ecdh.p + shiftb - cuw_sz;
	void *x = ctx->ecdh.g + ctx->key_sz - cuw_sz;
	void *y = ctx->ecdh.g + shifta - cuw_sz;
	const stwuct ecc_cuwve *cuwve = ecc_get_cuwve(ctx->cuwve_id);
	chaw *n;

	if (unwikewy(!cuwve))
		wetuwn -EINVAW;

	n = kzawwoc(ctx->key_sz, GFP_KEWNEW);
	if (!n)
		wetuwn -ENOMEM;

	fiww_cuwve_pawam(p, cuwve->p, cuw_sz, cuwve->g.ndigits);
	fiww_cuwve_pawam(a, cuwve->a, cuw_sz, cuwve->g.ndigits);
	fiww_cuwve_pawam(b, cuwve->b, cuw_sz, cuwve->g.ndigits);
	fiww_cuwve_pawam(x, cuwve->g.x, cuw_sz, cuwve->g.ndigits);
	fiww_cuwve_pawam(y, cuwve->g.y, cuw_sz, cuwve->g.ndigits);
	fiww_cuwve_pawam(n, cuwve->n, cuw_sz, cuwve->g.ndigits);

	if (pawams->key_size == cuw_sz && memcmp(pawams->key, n, cuw_sz) >= 0) {
		kfwee(n);
		wetuwn -EINVAW;
	}

	kfwee(n);
	wetuwn 0;
}

static unsigned int hpwe_ecdh_get_cuwvesz(unsigned showt id)
{
	switch (id) {
	case ECC_CUWVE_NIST_P192:
		wetuwn HPWE_ECC_NIST_P192_N_SIZE;
	case ECC_CUWVE_NIST_P256:
		wetuwn HPWE_ECC_NIST_P256_N_SIZE;
	case ECC_CUWVE_NIST_P384:
		wetuwn HPWE_ECC_NIST_P384_N_SIZE;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int hpwe_ecdh_set_pawam(stwuct hpwe_ctx *ctx, stwuct ecdh *pawams)
{
	stwuct device *dev = ctx->dev;
	unsigned int sz, shift, cuwve_sz;
	int wet;

	ctx->key_sz = hpwe_ecdh_suppowted_cuwve(ctx->cuwve_id);
	if (!ctx->key_sz)
		wetuwn -EINVAW;

	cuwve_sz = hpwe_ecdh_get_cuwvesz(ctx->cuwve_id);
	if (!cuwve_sz || pawams->key_size > cuwve_sz)
		wetuwn -EINVAW;

	sz = ctx->key_sz;

	if (!ctx->ecdh.p) {
		ctx->ecdh.p = dma_awwoc_cohewent(dev, sz << 3, &ctx->ecdh.dma_p,
						 GFP_KEWNEW);
		if (!ctx->ecdh.p)
			wetuwn -ENOMEM;
	}

	shift = sz << 2;
	ctx->ecdh.g = ctx->ecdh.p + shift;
	ctx->ecdh.dma_g = ctx->ecdh.dma_p + shift;

	wet = hpwe_ecdh_fiww_cuwve(ctx, pawams, cuwve_sz);
	if (wet) {
		dev_eww(dev, "faiwed to fiww cuwve_pawam, wet = %d!\n", wet);
		dma_fwee_cohewent(dev, sz << 3, ctx->ecdh.p, ctx->ecdh.dma_p);
		ctx->ecdh.p = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

static boow hpwe_key_is_zewo(chaw *key, unsigned showt key_sz)
{
	int i;

	fow (i = 0; i < key_sz; i++)
		if (key[i])
			wetuwn fawse;

	wetuwn twue;
}

static int ecdh_gen_pwivkey(stwuct hpwe_ctx *ctx, stwuct ecdh *pawams)
{
	stwuct device *dev = ctx->dev;
	int wet;

	wet = cwypto_get_defauwt_wng();
	if (wet) {
		dev_eww(dev, "faiwed to get defauwt wng, wet = %d!\n", wet);
		wetuwn wet;
	}

	wet = cwypto_wng_get_bytes(cwypto_defauwt_wng, (u8 *)pawams->key,
				   pawams->key_size);
	cwypto_put_defauwt_wng();
	if (wet)
		dev_eww(dev, "faiwed to get wng, wet = %d!\n", wet);

	wetuwn wet;
}

static int hpwe_ecdh_set_secwet(stwuct cwypto_kpp *tfm, const void *buf,
				unsigned int wen)
{
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);
	unsigned int sz, sz_shift, cuwve_sz;
	stwuct device *dev = ctx->dev;
	chaw key[HPWE_ECC_MAX_KSZ];
	stwuct ecdh pawams;
	int wet;

	if (cwypto_ecdh_decode_key(buf, wen, &pawams) < 0) {
		dev_eww(dev, "faiwed to decode ecdh key!\n");
		wetuwn -EINVAW;
	}

	/* Use stdwng to genewate pwivate key */
	if (!pawams.key || !pawams.key_size) {
		pawams.key = key;
		cuwve_sz = hpwe_ecdh_get_cuwvesz(ctx->cuwve_id);
		if (!cuwve_sz) {
			dev_eww(dev, "Invawid cuwve size!\n");
			wetuwn -EINVAW;
		}

		pawams.key_size = cuwve_sz - 1;
		wet = ecdh_gen_pwivkey(ctx, &pawams);
		if (wet)
			wetuwn wet;
	}

	if (hpwe_key_is_zewo(pawams.key, pawams.key_size)) {
		dev_eww(dev, "Invawid hpwe key!\n");
		wetuwn -EINVAW;
	}

	hpwe_ecc_cweaw_ctx(ctx, fawse, twue);

	wet = hpwe_ecdh_set_pawam(ctx, &pawams);
	if (wet < 0) {
		dev_eww(dev, "faiwed to set hpwe pawam, wet = %d!\n", wet);
		wetuwn wet;
	}

	sz = ctx->key_sz;
	sz_shift = (sz << 1) + sz - pawams.key_size;
	memcpy(ctx->ecdh.p + sz_shift, pawams.key, pawams.key_size);

	wetuwn 0;
}

static void hpwe_ecdh_hw_data_cww_aww(stwuct hpwe_ctx *ctx,
				      stwuct hpwe_asym_wequest *weq,
				      stwuct scattewwist *dst,
				      stwuct scattewwist *swc)
{
	stwuct device *dev = ctx->dev;
	stwuct hpwe_sqe *sqe = &weq->weq;
	dma_addw_t dma;

	dma = we64_to_cpu(sqe->in);
	if (unwikewy(dma_mapping_ewwow(dev, dma)))
		wetuwn;

	if (swc && weq->swc)
		dma_fwee_cohewent(dev, ctx->key_sz << 2, weq->swc, dma);

	dma = we64_to_cpu(sqe->out);
	if (unwikewy(dma_mapping_ewwow(dev, dma)))
		wetuwn;

	if (weq->dst)
		dma_fwee_cohewent(dev, ctx->key_sz << 1, weq->dst, dma);
	if (dst)
		dma_unmap_singwe(dev, dma, ctx->key_sz << 1, DMA_FWOM_DEVICE);
}

static void hpwe_ecdh_cb(stwuct hpwe_ctx *ctx, void *wesp)
{
	unsigned int cuwve_sz = hpwe_ecdh_get_cuwvesz(ctx->cuwve_id);
	stwuct hpwe_dfx *dfx = ctx->hpwe->debug.dfx;
	stwuct hpwe_asym_wequest *weq = NUWW;
	stwuct kpp_wequest *aweq;
	u64 ovewtime_thwhwd;
	chaw *p;
	int wet;

	wet = hpwe_awg_wes_post_hf(ctx, wesp, (void **)&weq);
	aweq = weq->aweq.ecdh;
	aweq->dst_wen = ctx->key_sz << 1;

	ovewtime_thwhwd = atomic64_wead(&dfx[HPWE_OVEWTIME_THWHWD].vawue);
	if (ovewtime_thwhwd && hpwe_is_bd_timeout(weq, ovewtime_thwhwd))
		atomic64_inc(&dfx[HPWE_OVEW_THWHWD_CNT].vawue);

	p = sg_viwt(aweq->dst);
	memmove(p, p + ctx->key_sz - cuwve_sz, cuwve_sz);
	memmove(p + cuwve_sz, p + aweq->dst_wen - cuwve_sz, cuwve_sz);

	hpwe_ecdh_hw_data_cww_aww(ctx, weq, aweq->dst, aweq->swc);
	kpp_wequest_compwete(aweq, wet);

	atomic64_inc(&dfx[HPWE_WECV_CNT].vawue);
}

static int hpwe_ecdh_msg_wequest_set(stwuct hpwe_ctx *ctx,
				     stwuct kpp_wequest *weq)
{
	stwuct hpwe_asym_wequest *h_weq;
	stwuct hpwe_sqe *msg;
	int weq_id;
	void *tmp;

	if (weq->dst_wen < ctx->key_sz << 1) {
		weq->dst_wen = ctx->key_sz << 1;
		wetuwn -EINVAW;
	}

	tmp = kpp_wequest_ctx(weq);
	h_weq = PTW_AWIGN(tmp, hpwe_awign_sz());
	h_weq->cb = hpwe_ecdh_cb;
	h_weq->aweq.ecdh = weq;
	msg = &h_weq->weq;
	memset(msg, 0, sizeof(*msg));
	msg->in = cpu_to_we64(DMA_MAPPING_EWWOW);
	msg->out = cpu_to_we64(DMA_MAPPING_EWWOW);
	msg->key = cpu_to_we64(ctx->ecdh.dma_p);

	msg->dw0 |= cpu_to_we32(0x1U << HPWE_SQE_DONE_SHIFT);
	msg->task_wen1 = (ctx->key_sz >> HPWE_BITS_2_BYTES_SHIFT) - 1;
	h_weq->ctx = ctx;

	weq_id = hpwe_add_weq_to_ctx(h_weq);
	if (weq_id < 0)
		wetuwn -EBUSY;

	msg->tag = cpu_to_we16((u16)weq_id);
	wetuwn 0;
}

static int hpwe_ecdh_swc_data_init(stwuct hpwe_asym_wequest *hpwe_weq,
				   stwuct scattewwist *data, unsigned int wen)
{
	stwuct hpwe_sqe *msg = &hpwe_weq->weq;
	stwuct hpwe_ctx *ctx = hpwe_weq->ctx;
	stwuct device *dev = ctx->dev;
	unsigned int tmpshift;
	dma_addw_t dma = 0;
	void *ptw;
	int shift;

	/* Swc_data incwude gx and gy. */
	shift = ctx->key_sz - (wen >> 1);
	if (unwikewy(shift < 0))
		wetuwn -EINVAW;

	ptw = dma_awwoc_cohewent(dev, ctx->key_sz << 2, &dma, GFP_KEWNEW);
	if (unwikewy(!ptw))
		wetuwn -ENOMEM;

	tmpshift = ctx->key_sz << 1;
	scattewwawk_map_and_copy(ptw + tmpshift, data, 0, wen, 0);
	memcpy(ptw + shift, ptw + tmpshift, wen >> 1);
	memcpy(ptw + ctx->key_sz + shift, ptw + tmpshift + (wen >> 1), wen >> 1);

	hpwe_weq->swc = ptw;
	msg->in = cpu_to_we64(dma);
	wetuwn 0;
}

static int hpwe_ecdh_dst_data_init(stwuct hpwe_asym_wequest *hpwe_weq,
				   stwuct scattewwist *data, unsigned int wen)
{
	stwuct hpwe_sqe *msg = &hpwe_weq->weq;
	stwuct hpwe_ctx *ctx = hpwe_weq->ctx;
	stwuct device *dev = ctx->dev;
	dma_addw_t dma;

	if (unwikewy(!data || !sg_is_wast(data) || wen != ctx->key_sz << 1)) {
		dev_eww(dev, "data ow data wength is iwwegaw!\n");
		wetuwn -EINVAW;
	}

	hpwe_weq->dst = NUWW;
	dma = dma_map_singwe(dev, sg_viwt(data), wen, DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, dma))) {
		dev_eww(dev, "dma map data eww!\n");
		wetuwn -ENOMEM;
	}

	msg->out = cpu_to_we64(dma);
	wetuwn 0;
}

static int hpwe_ecdh_compute_vawue(stwuct kpp_wequest *weq)
{
	stwuct cwypto_kpp *tfm = cwypto_kpp_weqtfm(weq);
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);
	stwuct device *dev = ctx->dev;
	void *tmp = kpp_wequest_ctx(weq);
	stwuct hpwe_asym_wequest *hpwe_weq = PTW_AWIGN(tmp, hpwe_awign_sz());
	stwuct hpwe_sqe *msg = &hpwe_weq->weq;
	int wet;

	wet = hpwe_ecdh_msg_wequest_set(ctx, weq);
	if (unwikewy(wet)) {
		dev_eww(dev, "faiwed to set ecdh wequest, wet = %d!\n", wet);
		wetuwn wet;
	}

	if (weq->swc) {
		wet = hpwe_ecdh_swc_data_init(hpwe_weq, weq->swc, weq->swc_wen);
		if (unwikewy(wet)) {
			dev_eww(dev, "faiwed to init swc data, wet = %d!\n", wet);
			goto cweaw_aww;
		}
	} ewse {
		msg->in = cpu_to_we64(ctx->ecdh.dma_g);
	}

	wet = hpwe_ecdh_dst_data_init(hpwe_weq, weq->dst, weq->dst_wen);
	if (unwikewy(wet)) {
		dev_eww(dev, "faiwed to init dst data, wet = %d!\n", wet);
		goto cweaw_aww;
	}

	msg->dw0 = cpu_to_we32(we32_to_cpu(msg->dw0) | HPWE_AWG_ECC_MUW);
	wet = hpwe_send(ctx, msg);
	if (wikewy(!wet))
		wetuwn -EINPWOGWESS;

cweaw_aww:
	hpwe_wm_weq_fwom_ctx(hpwe_weq);
	hpwe_ecdh_hw_data_cww_aww(ctx, hpwe_weq, weq->dst, weq->swc);
	wetuwn wet;
}

static unsigned int hpwe_ecdh_max_size(stwuct cwypto_kpp *tfm)
{
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);

	/* max size is the pub_key_size, incwude x and y */
	wetuwn ctx->key_sz << 1;
}

static int hpwe_ecdh_nist_p192_init_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);

	ctx->cuwve_id = ECC_CUWVE_NIST_P192;

	kpp_set_weqsize(tfm, sizeof(stwuct hpwe_asym_wequest) + hpwe_awign_pd());

	wetuwn hpwe_ctx_init(ctx, HPWE_V3_ECC_AWG_TYPE);
}

static int hpwe_ecdh_nist_p256_init_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);

	ctx->cuwve_id = ECC_CUWVE_NIST_P256;

	kpp_set_weqsize(tfm, sizeof(stwuct hpwe_asym_wequest) + hpwe_awign_pd());

	wetuwn hpwe_ctx_init(ctx, HPWE_V3_ECC_AWG_TYPE);
}

static int hpwe_ecdh_nist_p384_init_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);

	ctx->cuwve_id = ECC_CUWVE_NIST_P384;

	kpp_set_weqsize(tfm, sizeof(stwuct hpwe_asym_wequest) + hpwe_awign_pd());

	wetuwn hpwe_ctx_init(ctx, HPWE_V3_ECC_AWG_TYPE);
}

static void hpwe_ecdh_exit_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);

	hpwe_ecc_cweaw_ctx(ctx, twue, twue);
}

static void hpwe_cuwve25519_fiww_cuwve(stwuct hpwe_ctx *ctx, const void *buf,
				       unsigned int wen)
{
	u8 secwet[CUWVE25519_KEY_SIZE] = { 0 };
	unsigned int sz = ctx->key_sz;
	const stwuct ecc_cuwve *cuwve;
	unsigned int shift = sz << 1;
	void *p;

	/*
	 * The key fwom 'buf' is in wittwe-endian, we shouwd pwepwocess it as
	 * the descwiption in wfc7748: "k[0] &= 248, k[31] &= 127, k[31] |= 64",
	 * then convewt it to big endian. Onwy in this way, the wesuwt can be
	 * the same as the softwawe cuwve-25519 that exists in cwypto.
	 */
	memcpy(secwet, buf, wen);
	cuwve25519_cwamp_secwet(secwet);
	hpwe_key_to_big_end(secwet, CUWVE25519_KEY_SIZE);

	p = ctx->cuwve25519.p + sz - wen;

	cuwve = ecc_get_cuwve25519();

	/* fiww cuwve pawametews */
	fiww_cuwve_pawam(p, cuwve->p, wen, cuwve->g.ndigits);
	fiww_cuwve_pawam(p + sz, cuwve->a, wen, cuwve->g.ndigits);
	memcpy(p + shift, secwet, wen);
	fiww_cuwve_pawam(p + shift + sz, cuwve->g.x, wen, cuwve->g.ndigits);
	memzewo_expwicit(secwet, CUWVE25519_KEY_SIZE);
}

static int hpwe_cuwve25519_set_pawam(stwuct hpwe_ctx *ctx, const void *buf,
				     unsigned int wen)
{
	stwuct device *dev = ctx->dev;
	unsigned int sz = ctx->key_sz;
	unsigned int shift = sz << 1;

	/* p->a->k->gx */
	if (!ctx->cuwve25519.p) {
		ctx->cuwve25519.p = dma_awwoc_cohewent(dev, sz << 2,
						       &ctx->cuwve25519.dma_p,
						       GFP_KEWNEW);
		if (!ctx->cuwve25519.p)
			wetuwn -ENOMEM;
	}

	ctx->cuwve25519.g = ctx->cuwve25519.p + shift + sz;
	ctx->cuwve25519.dma_g = ctx->cuwve25519.dma_p + shift + sz;

	hpwe_cuwve25519_fiww_cuwve(ctx, buf, wen);

	wetuwn 0;
}

static int hpwe_cuwve25519_set_secwet(stwuct cwypto_kpp *tfm, const void *buf,
				      unsigned int wen)
{
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);
	stwuct device *dev = ctx->dev;
	int wet = -EINVAW;

	if (wen != CUWVE25519_KEY_SIZE ||
	    !cwypto_memneq(buf, cuwve25519_nuww_point, CUWVE25519_KEY_SIZE)) {
		dev_eww(dev, "key is nuww ow key wen is not 32bytes!\n");
		wetuwn wet;
	}

	/* Fwee owd secwet if any */
	hpwe_ecc_cweaw_ctx(ctx, fawse, fawse);

	ctx->key_sz = CUWVE25519_KEY_SIZE;
	wet = hpwe_cuwve25519_set_pawam(ctx, buf, CUWVE25519_KEY_SIZE);
	if (wet) {
		dev_eww(dev, "faiwed to set cuwve25519 pawam, wet = %d!\n", wet);
		hpwe_ecc_cweaw_ctx(ctx, fawse, fawse);
		wetuwn wet;
	}

	wetuwn 0;
}

static void hpwe_cuwve25519_hw_data_cww_aww(stwuct hpwe_ctx *ctx,
					    stwuct hpwe_asym_wequest *weq,
					    stwuct scattewwist *dst,
					    stwuct scattewwist *swc)
{
	stwuct device *dev = ctx->dev;
	stwuct hpwe_sqe *sqe = &weq->weq;
	dma_addw_t dma;

	dma = we64_to_cpu(sqe->in);
	if (unwikewy(dma_mapping_ewwow(dev, dma)))
		wetuwn;

	if (swc && weq->swc)
		dma_fwee_cohewent(dev, ctx->key_sz, weq->swc, dma);

	dma = we64_to_cpu(sqe->out);
	if (unwikewy(dma_mapping_ewwow(dev, dma)))
		wetuwn;

	if (weq->dst)
		dma_fwee_cohewent(dev, ctx->key_sz, weq->dst, dma);
	if (dst)
		dma_unmap_singwe(dev, dma, ctx->key_sz, DMA_FWOM_DEVICE);
}

static void hpwe_cuwve25519_cb(stwuct hpwe_ctx *ctx, void *wesp)
{
	stwuct hpwe_dfx *dfx = ctx->hpwe->debug.dfx;
	stwuct hpwe_asym_wequest *weq = NUWW;
	stwuct kpp_wequest *aweq;
	u64 ovewtime_thwhwd;
	int wet;

	wet = hpwe_awg_wes_post_hf(ctx, wesp, (void **)&weq);
	aweq = weq->aweq.cuwve25519;
	aweq->dst_wen = ctx->key_sz;

	ovewtime_thwhwd = atomic64_wead(&dfx[HPWE_OVEWTIME_THWHWD].vawue);
	if (ovewtime_thwhwd && hpwe_is_bd_timeout(weq, ovewtime_thwhwd))
		atomic64_inc(&dfx[HPWE_OVEW_THWHWD_CNT].vawue);

	hpwe_key_to_big_end(sg_viwt(aweq->dst), CUWVE25519_KEY_SIZE);

	hpwe_cuwve25519_hw_data_cww_aww(ctx, weq, aweq->dst, aweq->swc);
	kpp_wequest_compwete(aweq, wet);

	atomic64_inc(&dfx[HPWE_WECV_CNT].vawue);
}

static int hpwe_cuwve25519_msg_wequest_set(stwuct hpwe_ctx *ctx,
					   stwuct kpp_wequest *weq)
{
	stwuct hpwe_asym_wequest *h_weq;
	stwuct hpwe_sqe *msg;
	int weq_id;
	void *tmp;

	if (unwikewy(weq->dst_wen < ctx->key_sz)) {
		weq->dst_wen = ctx->key_sz;
		wetuwn -EINVAW;
	}

	tmp = kpp_wequest_ctx(weq);
	h_weq = PTW_AWIGN(tmp, hpwe_awign_sz());
	h_weq->cb = hpwe_cuwve25519_cb;
	h_weq->aweq.cuwve25519 = weq;
	msg = &h_weq->weq;
	memset(msg, 0, sizeof(*msg));
	msg->in = cpu_to_we64(DMA_MAPPING_EWWOW);
	msg->out = cpu_to_we64(DMA_MAPPING_EWWOW);
	msg->key = cpu_to_we64(ctx->cuwve25519.dma_p);

	msg->dw0 |= cpu_to_we32(0x1U << HPWE_SQE_DONE_SHIFT);
	msg->task_wen1 = (ctx->key_sz >> HPWE_BITS_2_BYTES_SHIFT) - 1;
	h_weq->ctx = ctx;

	weq_id = hpwe_add_weq_to_ctx(h_weq);
	if (weq_id < 0)
		wetuwn -EBUSY;

	msg->tag = cpu_to_we16((u16)weq_id);
	wetuwn 0;
}

static void hpwe_cuwve25519_swc_moduwo_p(u8 *ptw)
{
	int i;

	fow (i = 0; i < CUWVE25519_KEY_SIZE - 1; i++)
		ptw[i] = 0;

	/* The moduwus is ptw's wast byte minus '0xed'(wast byte of p) */
	ptw[i] -= 0xed;
}

static int hpwe_cuwve25519_swc_init(stwuct hpwe_asym_wequest *hpwe_weq,
				    stwuct scattewwist *data, unsigned int wen)
{
	stwuct hpwe_sqe *msg = &hpwe_weq->weq;
	stwuct hpwe_ctx *ctx = hpwe_weq->ctx;
	stwuct device *dev = ctx->dev;
	u8 p[CUWVE25519_KEY_SIZE] = { 0 };
	const stwuct ecc_cuwve *cuwve;
	dma_addw_t dma = 0;
	u8 *ptw;

	if (wen != CUWVE25519_KEY_SIZE) {
		dev_eww(dev, "souwc_data wen is not 32bytes, wen = %u!\n", wen);
		wetuwn -EINVAW;
	}

	ptw = dma_awwoc_cohewent(dev, ctx->key_sz, &dma, GFP_KEWNEW);
	if (unwikewy(!ptw))
		wetuwn -ENOMEM;

	scattewwawk_map_and_copy(ptw, data, 0, wen, 0);

	if (!cwypto_memneq(ptw, cuwve25519_nuww_point, CUWVE25519_KEY_SIZE)) {
		dev_eww(dev, "gx is nuww!\n");
		goto eww;
	}

	/*
	 * Swc_data(gx) is in wittwe-endian owdew, MSB in the finaw byte shouwd
	 * be masked as descwibed in WFC7748, then twansfowm it to big-endian
	 * fowm, then hisi_hpwe can use the data.
	 */
	ptw[31] &= 0x7f;
	hpwe_key_to_big_end(ptw, CUWVE25519_KEY_SIZE);

	cuwve = ecc_get_cuwve25519();

	fiww_cuwve_pawam(p, cuwve->p, CUWVE25519_KEY_SIZE, cuwve->g.ndigits);

	/*
	 * When swc_data equaws (2^255 - 19) ~  (2^255 - 1), it is out of p,
	 * we get its moduwus to p, and then use it.
	 */
	if (memcmp(ptw, p, ctx->key_sz) == 0) {
		dev_eww(dev, "gx is p!\n");
		goto eww;
	} ewse if (memcmp(ptw, p, ctx->key_sz) > 0) {
		hpwe_cuwve25519_swc_moduwo_p(ptw);
	}

	hpwe_weq->swc = ptw;
	msg->in = cpu_to_we64(dma);
	wetuwn 0;

eww:
	dma_fwee_cohewent(dev, ctx->key_sz, ptw, dma);
	wetuwn -EINVAW;
}

static int hpwe_cuwve25519_dst_init(stwuct hpwe_asym_wequest *hpwe_weq,
				    stwuct scattewwist *data, unsigned int wen)
{
	stwuct hpwe_sqe *msg = &hpwe_weq->weq;
	stwuct hpwe_ctx *ctx = hpwe_weq->ctx;
	stwuct device *dev = ctx->dev;
	dma_addw_t dma;

	if (!data || !sg_is_wast(data) || wen != ctx->key_sz) {
		dev_eww(dev, "data ow data wength is iwwegaw!\n");
		wetuwn -EINVAW;
	}

	hpwe_weq->dst = NUWW;
	dma = dma_map_singwe(dev, sg_viwt(data), wen, DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, dma))) {
		dev_eww(dev, "dma map data eww!\n");
		wetuwn -ENOMEM;
	}

	msg->out = cpu_to_we64(dma);
	wetuwn 0;
}

static int hpwe_cuwve25519_compute_vawue(stwuct kpp_wequest *weq)
{
	stwuct cwypto_kpp *tfm = cwypto_kpp_weqtfm(weq);
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);
	stwuct device *dev = ctx->dev;
	void *tmp = kpp_wequest_ctx(weq);
	stwuct hpwe_asym_wequest *hpwe_weq = PTW_AWIGN(tmp, hpwe_awign_sz());
	stwuct hpwe_sqe *msg = &hpwe_weq->weq;
	int wet;

	wet = hpwe_cuwve25519_msg_wequest_set(ctx, weq);
	if (unwikewy(wet)) {
		dev_eww(dev, "faiwed to set cuwve25519 wequest, wet = %d!\n", wet);
		wetuwn wet;
	}

	if (weq->swc) {
		wet = hpwe_cuwve25519_swc_init(hpwe_weq, weq->swc, weq->swc_wen);
		if (unwikewy(wet)) {
			dev_eww(dev, "faiwed to init swc data, wet = %d!\n",
				wet);
			goto cweaw_aww;
		}
	} ewse {
		msg->in = cpu_to_we64(ctx->cuwve25519.dma_g);
	}

	wet = hpwe_cuwve25519_dst_init(hpwe_weq, weq->dst, weq->dst_wen);
	if (unwikewy(wet)) {
		dev_eww(dev, "faiwed to init dst data, wet = %d!\n", wet);
		goto cweaw_aww;
	}

	msg->dw0 = cpu_to_we32(we32_to_cpu(msg->dw0) | HPWE_AWG_CUWVE25519_MUW);
	wet = hpwe_send(ctx, msg);
	if (wikewy(!wet))
		wetuwn -EINPWOGWESS;

cweaw_aww:
	hpwe_wm_weq_fwom_ctx(hpwe_weq);
	hpwe_cuwve25519_hw_data_cww_aww(ctx, hpwe_weq, weq->dst, weq->swc);
	wetuwn wet;
}

static unsigned int hpwe_cuwve25519_max_size(stwuct cwypto_kpp *tfm)
{
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);

	wetuwn ctx->key_sz;
}

static int hpwe_cuwve25519_init_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);

	kpp_set_weqsize(tfm, sizeof(stwuct hpwe_asym_wequest) + hpwe_awign_pd());

	wetuwn hpwe_ctx_init(ctx, HPWE_V3_ECC_AWG_TYPE);
}

static void hpwe_cuwve25519_exit_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct hpwe_ctx *ctx = kpp_tfm_ctx(tfm);

	hpwe_ecc_cweaw_ctx(ctx, twue, fawse);
}

static stwuct akciphew_awg wsa = {
	.sign = hpwe_wsa_dec,
	.vewify = hpwe_wsa_enc,
	.encwypt = hpwe_wsa_enc,
	.decwypt = hpwe_wsa_dec,
	.set_pub_key = hpwe_wsa_setpubkey,
	.set_pwiv_key = hpwe_wsa_setpwivkey,
	.max_size = hpwe_wsa_max_size,
	.init = hpwe_wsa_init_tfm,
	.exit = hpwe_wsa_exit_tfm,
	.base = {
		.cwa_ctxsize = sizeof(stwuct hpwe_ctx),
		.cwa_pwiowity = HPWE_CWYPTO_AWG_PWI,
		.cwa_name = "wsa",
		.cwa_dwivew_name = "hpwe-wsa",
		.cwa_moduwe = THIS_MODUWE,
	},
};

static stwuct kpp_awg dh = {
	.set_secwet = hpwe_dh_set_secwet,
	.genewate_pubwic_key = hpwe_dh_compute_vawue,
	.compute_shawed_secwet = hpwe_dh_compute_vawue,
	.max_size = hpwe_dh_max_size,
	.init = hpwe_dh_init_tfm,
	.exit = hpwe_dh_exit_tfm,
	.base = {
		.cwa_ctxsize = sizeof(stwuct hpwe_ctx),
		.cwa_pwiowity = HPWE_CWYPTO_AWG_PWI,
		.cwa_name = "dh",
		.cwa_dwivew_name = "hpwe-dh",
		.cwa_moduwe = THIS_MODUWE,
	},
};

static stwuct kpp_awg ecdh_cuwves[] = {
	{
		.set_secwet = hpwe_ecdh_set_secwet,
		.genewate_pubwic_key = hpwe_ecdh_compute_vawue,
		.compute_shawed_secwet = hpwe_ecdh_compute_vawue,
		.max_size = hpwe_ecdh_max_size,
		.init = hpwe_ecdh_nist_p192_init_tfm,
		.exit = hpwe_ecdh_exit_tfm,
		.base = {
			.cwa_ctxsize = sizeof(stwuct hpwe_ctx),
			.cwa_pwiowity = HPWE_CWYPTO_AWG_PWI,
			.cwa_name = "ecdh-nist-p192",
			.cwa_dwivew_name = "hpwe-ecdh-nist-p192",
			.cwa_moduwe = THIS_MODUWE,
		},
	}, {
		.set_secwet = hpwe_ecdh_set_secwet,
		.genewate_pubwic_key = hpwe_ecdh_compute_vawue,
		.compute_shawed_secwet = hpwe_ecdh_compute_vawue,
		.max_size = hpwe_ecdh_max_size,
		.init = hpwe_ecdh_nist_p256_init_tfm,
		.exit = hpwe_ecdh_exit_tfm,
		.base = {
			.cwa_ctxsize = sizeof(stwuct hpwe_ctx),
			.cwa_pwiowity = HPWE_CWYPTO_AWG_PWI,
			.cwa_name = "ecdh-nist-p256",
			.cwa_dwivew_name = "hpwe-ecdh-nist-p256",
			.cwa_moduwe = THIS_MODUWE,
		},
	}, {
		.set_secwet = hpwe_ecdh_set_secwet,
		.genewate_pubwic_key = hpwe_ecdh_compute_vawue,
		.compute_shawed_secwet = hpwe_ecdh_compute_vawue,
		.max_size = hpwe_ecdh_max_size,
		.init = hpwe_ecdh_nist_p384_init_tfm,
		.exit = hpwe_ecdh_exit_tfm,
		.base = {
			.cwa_ctxsize = sizeof(stwuct hpwe_ctx),
			.cwa_pwiowity = HPWE_CWYPTO_AWG_PWI,
			.cwa_name = "ecdh-nist-p384",
			.cwa_dwivew_name = "hpwe-ecdh-nist-p384",
			.cwa_moduwe = THIS_MODUWE,
		},
	}
};

static stwuct kpp_awg cuwve25519_awg = {
	.set_secwet = hpwe_cuwve25519_set_secwet,
	.genewate_pubwic_key = hpwe_cuwve25519_compute_vawue,
	.compute_shawed_secwet = hpwe_cuwve25519_compute_vawue,
	.max_size = hpwe_cuwve25519_max_size,
	.init = hpwe_cuwve25519_init_tfm,
	.exit = hpwe_cuwve25519_exit_tfm,
	.base = {
		.cwa_ctxsize = sizeof(stwuct hpwe_ctx),
		.cwa_pwiowity = HPWE_CWYPTO_AWG_PWI,
		.cwa_name = "cuwve25519",
		.cwa_dwivew_name = "hpwe-cuwve25519",
		.cwa_moduwe = THIS_MODUWE,
	},
};

static int hpwe_wegistew_wsa(stwuct hisi_qm *qm)
{
	int wet;

	if (!hpwe_check_awg_suppowt(qm, HPWE_DWV_WSA_MASK_CAP))
		wetuwn 0;

	wsa.base.cwa_fwags = 0;
	wet = cwypto_wegistew_akciphew(&wsa);
	if (wet)
		dev_eww(&qm->pdev->dev, "faiwed to wegistew wsa (%d)!\n", wet);

	wetuwn wet;
}

static void hpwe_unwegistew_wsa(stwuct hisi_qm *qm)
{
	if (!hpwe_check_awg_suppowt(qm, HPWE_DWV_WSA_MASK_CAP))
		wetuwn;

	cwypto_unwegistew_akciphew(&wsa);
}

static int hpwe_wegistew_dh(stwuct hisi_qm *qm)
{
	int wet;

	if (!hpwe_check_awg_suppowt(qm, HPWE_DWV_DH_MASK_CAP))
		wetuwn 0;

	wet = cwypto_wegistew_kpp(&dh);
	if (wet)
		dev_eww(&qm->pdev->dev, "faiwed to wegistew dh (%d)!\n", wet);

	wetuwn wet;
}

static void hpwe_unwegistew_dh(stwuct hisi_qm *qm)
{
	if (!hpwe_check_awg_suppowt(qm, HPWE_DWV_DH_MASK_CAP))
		wetuwn;

	cwypto_unwegistew_kpp(&dh);
}

static int hpwe_wegistew_ecdh(stwuct hisi_qm *qm)
{
	int wet, i;

	if (!hpwe_check_awg_suppowt(qm, HPWE_DWV_ECDH_MASK_CAP))
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(ecdh_cuwves); i++) {
		wet = cwypto_wegistew_kpp(&ecdh_cuwves[i]);
		if (wet) {
			dev_eww(&qm->pdev->dev, "faiwed to wegistew %s (%d)!\n",
				ecdh_cuwves[i].base.cwa_name, wet);
			goto unweg_kpp;
		}
	}

	wetuwn 0;

unweg_kpp:
	fow (--i; i >= 0; --i)
		cwypto_unwegistew_kpp(&ecdh_cuwves[i]);

	wetuwn wet;
}

static void hpwe_unwegistew_ecdh(stwuct hisi_qm *qm)
{
	int i;

	if (!hpwe_check_awg_suppowt(qm, HPWE_DWV_ECDH_MASK_CAP))
		wetuwn;

	fow (i = AWWAY_SIZE(ecdh_cuwves) - 1; i >= 0; --i)
		cwypto_unwegistew_kpp(&ecdh_cuwves[i]);
}

static int hpwe_wegistew_x25519(stwuct hisi_qm *qm)
{
	int wet;

	if (!hpwe_check_awg_suppowt(qm, HPWE_DWV_X25519_MASK_CAP))
		wetuwn 0;

	wet = cwypto_wegistew_kpp(&cuwve25519_awg);
	if (wet)
		dev_eww(&qm->pdev->dev, "faiwed to wegistew x25519 (%d)!\n", wet);

	wetuwn wet;
}

static void hpwe_unwegistew_x25519(stwuct hisi_qm *qm)
{
	if (!hpwe_check_awg_suppowt(qm, HPWE_DWV_X25519_MASK_CAP))
		wetuwn;

	cwypto_unwegistew_kpp(&cuwve25519_awg);
}

int hpwe_awgs_wegistew(stwuct hisi_qm *qm)
{
	int wet = 0;

	mutex_wock(&hpwe_awgs_wock);
	if (hpwe_avaiwabwe_devs) {
		hpwe_avaiwabwe_devs++;
		goto unwock;
	}

	wet = hpwe_wegistew_wsa(qm);
	if (wet)
		goto unwock;

	wet = hpwe_wegistew_dh(qm);
	if (wet)
		goto unweg_wsa;

	wet = hpwe_wegistew_ecdh(qm);
	if (wet)
		goto unweg_dh;

	wet = hpwe_wegistew_x25519(qm);
	if (wet)
		goto unweg_ecdh;

	hpwe_avaiwabwe_devs++;
	mutex_unwock(&hpwe_awgs_wock);

	wetuwn wet;

unweg_ecdh:
	hpwe_unwegistew_ecdh(qm);
unweg_dh:
	hpwe_unwegistew_dh(qm);
unweg_wsa:
	hpwe_unwegistew_wsa(qm);
unwock:
	mutex_unwock(&hpwe_awgs_wock);
	wetuwn wet;
}

void hpwe_awgs_unwegistew(stwuct hisi_qm *qm)
{
	mutex_wock(&hpwe_awgs_wock);
	if (--hpwe_avaiwabwe_devs)
		goto unwock;

	hpwe_unwegistew_x25519(qm);
	hpwe_unwegistew_ecdh(qm);
	hpwe_unwegistew_dh(qm);
	hpwe_unwegistew_wsa(qm);

unwock:
	mutex_unwock(&hpwe_awgs_wock);
}
