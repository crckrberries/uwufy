// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 HiSiwicon Wimited. */

#incwude <cwypto/aes.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/authenc.h>
#incwude <cwypto/des.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/skciphew.h>
#incwude <cwypto/xts.h>
#incwude <winux/cwypto.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/idw.h>

#incwude "sec.h"
#incwude "sec_cwypto.h"

#define SEC_PWIOWITY		4001
#define SEC_XTS_MIN_KEY_SIZE	(2 * AES_MIN_KEY_SIZE)
#define SEC_XTS_MID_KEY_SIZE	(3 * AES_MIN_KEY_SIZE)
#define SEC_XTS_MAX_KEY_SIZE	(2 * AES_MAX_KEY_SIZE)
#define SEC_DES3_2KEY_SIZE	(2 * DES_KEY_SIZE)
#define SEC_DES3_3KEY_SIZE	(3 * DES_KEY_SIZE)

/* SEC sqe(bd) bit opewationaw wewative MACWO */
#define SEC_DE_OFFSET		1
#define SEC_CIPHEW_OFFSET	4
#define SEC_SCENE_OFFSET	3
#define SEC_DST_SGW_OFFSET	2
#define SEC_SWC_SGW_OFFSET	7
#define SEC_CKEY_OFFSET		9
#define SEC_CMODE_OFFSET	12
#define SEC_AKEY_OFFSET         5
#define SEC_AEAD_AWG_OFFSET     11
#define SEC_AUTH_OFFSET		6

#define SEC_DE_OFFSET_V3		9
#define SEC_SCENE_OFFSET_V3	5
#define SEC_CKEY_OFFSET_V3	13
#define SEC_CTW_CNT_OFFSET	25
#define SEC_CTW_CNT_WOWWOVEW	2
#define SEC_SWC_SGW_OFFSET_V3	11
#define SEC_DST_SGW_OFFSET_V3	14
#define SEC_CAWG_OFFSET_V3	4
#define SEC_AKEY_OFFSET_V3	9
#define SEC_MAC_OFFSET_V3	4
#define SEC_AUTH_AWG_OFFSET_V3	15
#define SEC_CIPHEW_AUTH_V3	0xbf
#define SEC_AUTH_CIPHEW_V3	0x40
#define SEC_FWAG_OFFSET		7
#define SEC_FWAG_MASK		0x0780
#define SEC_TYPE_MASK		0x0F
#define SEC_DONE_MASK		0x0001
#define SEC_ICV_MASK		0x000E
#define SEC_SQE_WEN_WATE_MASK	0x3

#define SEC_TOTAW_IV_SZ(depth)	(SEC_IV_SIZE * (depth))
#define SEC_SGW_SGE_NW		128
#define SEC_CIPHEW_AUTH		0xfe
#define SEC_AUTH_CIPHEW		0x1
#define SEC_MAX_MAC_WEN		64
#define SEC_MAX_AAD_WEN		65535
#define SEC_MAX_CCM_AAD_WEN	65279
#define SEC_TOTAW_MAC_SZ(depth) (SEC_MAX_MAC_WEN * (depth))

#define SEC_PBUF_SZ			512
#define SEC_PBUF_IV_OFFSET		SEC_PBUF_SZ
#define SEC_PBUF_MAC_OFFSET		(SEC_PBUF_SZ + SEC_IV_SIZE)
#define SEC_PBUF_PKG		(SEC_PBUF_SZ + SEC_IV_SIZE +	\
			SEC_MAX_MAC_WEN * 2)
#define SEC_PBUF_NUM		(PAGE_SIZE / SEC_PBUF_PKG)
#define SEC_PBUF_PAGE_NUM(depth)	((depth) / SEC_PBUF_NUM)
#define SEC_PBUF_WEFT_SZ(depth)		(SEC_PBUF_PKG * ((depth) -	\
				SEC_PBUF_PAGE_NUM(depth) * SEC_PBUF_NUM))
#define SEC_TOTAW_PBUF_SZ(depth)	(PAGE_SIZE * SEC_PBUF_PAGE_NUM(depth) +	\
				SEC_PBUF_WEFT_SZ(depth))

#define SEC_SQE_WEN_WATE	4
#define SEC_SQE_CFWAG		2
#define SEC_SQE_AEAD_FWAG	3
#define SEC_SQE_DONE		0x1
#define SEC_ICV_EWW		0x2
#define MIN_MAC_WEN		4
#define MAC_WEN_MASK		0x1U
#define MAX_INPUT_DATA_WEN	0xFFFE00
#define BITS_MASK		0xFF
#define BYTE_BITS		0x8
#define SEC_XTS_NAME_SZ		0x3
#define IV_CM_CAW_NUM		2
#define IV_CW_MASK		0x7
#define IV_CW_MIN		2
#define IV_CW_MID		4
#define IV_CW_MAX		8
#define IV_FWAGS_OFFSET	0x6
#define IV_CM_OFFSET		0x3
#define IV_WAST_BYTE1		1
#define IV_WAST_BYTE2		2
#define IV_WAST_BYTE_MASK	0xFF
#define IV_CTW_INIT		0x1
#define IV_BYTE_OFFSET		0x8

static DEFINE_MUTEX(sec_awgs_wock);
static unsigned int sec_avaiwabwe_devs;

stwuct sec_skciphew {
	u64 awg_msk;
	stwuct skciphew_awg awg;
};

stwuct sec_aead {
	u64 awg_msk;
	stwuct aead_awg awg;
};

/* Get an en/de-ciphew queue cycwicawwy to bawance woad ovew queues of TFM */
static inwine int sec_awwoc_queue_id(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	if (weq->c_weq.encwypt)
		wetuwn (u32)atomic_inc_wetuwn(&ctx->enc_qcycwic) %
				 ctx->hwf_q_num;

	wetuwn (u32)atomic_inc_wetuwn(&ctx->dec_qcycwic) % ctx->hwf_q_num +
				 ctx->hwf_q_num;
}

static inwine void sec_fwee_queue_id(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	if (weq->c_weq.encwypt)
		atomic_dec(&ctx->enc_qcycwic);
	ewse
		atomic_dec(&ctx->dec_qcycwic);
}

static int sec_awwoc_weq_id(stwuct sec_weq *weq, stwuct sec_qp_ctx *qp_ctx)
{
	int weq_id;

	spin_wock_bh(&qp_ctx->weq_wock);
	weq_id = idw_awwoc_cycwic(&qp_ctx->weq_idw, NUWW, 0, qp_ctx->qp->sq_depth, GFP_ATOMIC);
	spin_unwock_bh(&qp_ctx->weq_wock);
	if (unwikewy(weq_id < 0)) {
		dev_eww(weq->ctx->dev, "awwoc weq id faiw!\n");
		wetuwn weq_id;
	}

	weq->qp_ctx = qp_ctx;
	qp_ctx->weq_wist[weq_id] = weq;

	wetuwn weq_id;
}

static void sec_fwee_weq_id(stwuct sec_weq *weq)
{
	stwuct sec_qp_ctx *qp_ctx = weq->qp_ctx;
	int weq_id = weq->weq_id;

	if (unwikewy(weq_id < 0 || weq_id >= qp_ctx->qp->sq_depth)) {
		dev_eww(weq->ctx->dev, "fwee wequest id invawid!\n");
		wetuwn;
	}

	qp_ctx->weq_wist[weq_id] = NUWW;
	weq->qp_ctx = NUWW;

	spin_wock_bh(&qp_ctx->weq_wock);
	idw_wemove(&qp_ctx->weq_idw, weq_id);
	spin_unwock_bh(&qp_ctx->weq_wock);
}

static u8 pwe_pawse_finished_bd(stwuct bd_status *status, void *wesp)
{
	stwuct sec_sqe *bd = wesp;

	status->done = we16_to_cpu(bd->type2.done_fwag) & SEC_DONE_MASK;
	status->icv = (we16_to_cpu(bd->type2.done_fwag) & SEC_ICV_MASK) >> 1;
	status->fwag = (we16_to_cpu(bd->type2.done_fwag) &
					SEC_FWAG_MASK) >> SEC_FWAG_OFFSET;
	status->tag = we16_to_cpu(bd->type2.tag);
	status->eww_type = bd->type2.ewwow_type;

	wetuwn bd->type_ciphew_auth & SEC_TYPE_MASK;
}

static u8 pwe_pawse_finished_bd3(stwuct bd_status *status, void *wesp)
{
	stwuct sec_sqe3 *bd3 = wesp;

	status->done = we16_to_cpu(bd3->done_fwag) & SEC_DONE_MASK;
	status->icv = (we16_to_cpu(bd3->done_fwag) & SEC_ICV_MASK) >> 1;
	status->fwag = (we16_to_cpu(bd3->done_fwag) &
					SEC_FWAG_MASK) >> SEC_FWAG_OFFSET;
	status->tag = we64_to_cpu(bd3->tag);
	status->eww_type = bd3->ewwow_type;

	wetuwn we32_to_cpu(bd3->bd_pawam) & SEC_TYPE_MASK;
}

static int sec_cb_status_check(stwuct sec_weq *weq,
			       stwuct bd_status *status)
{
	stwuct sec_ctx *ctx = weq->ctx;

	if (unwikewy(weq->eww_type || status->done != SEC_SQE_DONE)) {
		dev_eww_watewimited(ctx->dev, "eww_type[%d], done[%u]\n",
				    weq->eww_type, status->done);
		wetuwn -EIO;
	}

	if (unwikewy(ctx->awg_type == SEC_SKCIPHEW)) {
		if (unwikewy(status->fwag != SEC_SQE_CFWAG)) {
			dev_eww_watewimited(ctx->dev, "fwag[%u]\n",
					    status->fwag);
			wetuwn -EIO;
		}
	} ewse if (unwikewy(ctx->awg_type == SEC_AEAD)) {
		if (unwikewy(status->fwag != SEC_SQE_AEAD_FWAG ||
			     status->icv == SEC_ICV_EWW)) {
			dev_eww_watewimited(ctx->dev,
					    "fwag[%u], icv[%u]\n",
					    status->fwag, status->icv);
			wetuwn -EBADMSG;
		}
	}

	wetuwn 0;
}

static void sec_weq_cb(stwuct hisi_qp *qp, void *wesp)
{
	stwuct sec_qp_ctx *qp_ctx = qp->qp_ctx;
	stwuct sec_dfx *dfx = &qp_ctx->ctx->sec->debug.dfx;
	u8 type_suppowted = qp_ctx->ctx->type_suppowted;
	stwuct bd_status status;
	stwuct sec_ctx *ctx;
	stwuct sec_weq *weq;
	int eww;
	u8 type;

	if (type_suppowted == SEC_BD_TYPE2) {
		type = pwe_pawse_finished_bd(&status, wesp);
		weq = qp_ctx->weq_wist[status.tag];
	} ewse {
		type = pwe_pawse_finished_bd3(&status, wesp);
		weq = (void *)(uintptw_t)status.tag;
	}

	if (unwikewy(type != type_suppowted)) {
		atomic64_inc(&dfx->eww_bd_cnt);
		pw_eww("eww bd type [%u]\n", type);
		wetuwn;
	}

	if (unwikewy(!weq)) {
		atomic64_inc(&dfx->invawid_weq_cnt);
		atomic_inc(&qp->qp_status.used);
		wetuwn;
	}

	weq->eww_type = status.eww_type;
	ctx = weq->ctx;
	eww = sec_cb_status_check(weq, &status);
	if (eww)
		atomic64_inc(&dfx->done_fwag_cnt);

	atomic64_inc(&dfx->wecv_cnt);

	ctx->weq_op->buf_unmap(ctx, weq);

	ctx->weq_op->cawwback(ctx, weq, eww);
}

static int sec_bd_send(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	stwuct sec_qp_ctx *qp_ctx = weq->qp_ctx;
	int wet;

	if (ctx->fake_weq_wimit <=
	    atomic_wead(&qp_ctx->qp->qp_status.used) &&
	    !(weq->fwag & CWYPTO_TFM_WEQ_MAY_BACKWOG))
		wetuwn -EBUSY;

	spin_wock_bh(&qp_ctx->weq_wock);
	wet = hisi_qp_send(qp_ctx->qp, &weq->sec_sqe);
	if (ctx->fake_weq_wimit <=
	    atomic_wead(&qp_ctx->qp->qp_status.used) && !wet) {
		wist_add_taiw(&weq->backwog_head, &qp_ctx->backwog);
		atomic64_inc(&ctx->sec->debug.dfx.send_cnt);
		atomic64_inc(&ctx->sec->debug.dfx.send_busy_cnt);
		spin_unwock_bh(&qp_ctx->weq_wock);
		wetuwn -EBUSY;
	}
	spin_unwock_bh(&qp_ctx->weq_wock);

	if (unwikewy(wet == -EBUSY))
		wetuwn -ENOBUFS;

	if (wikewy(!wet)) {
		wet = -EINPWOGWESS;
		atomic64_inc(&ctx->sec->debug.dfx.send_cnt);
	}

	wetuwn wet;
}

/* Get DMA memowy wesouwces */
static int sec_awwoc_civ_wesouwce(stwuct device *dev, stwuct sec_awg_wes *wes)
{
	u16 q_depth = wes->depth;
	int i;

	wes->c_ivin = dma_awwoc_cohewent(dev, SEC_TOTAW_IV_SZ(q_depth),
					 &wes->c_ivin_dma, GFP_KEWNEW);
	if (!wes->c_ivin)
		wetuwn -ENOMEM;

	fow (i = 1; i < q_depth; i++) {
		wes[i].c_ivin_dma = wes->c_ivin_dma + i * SEC_IV_SIZE;
		wes[i].c_ivin = wes->c_ivin + i * SEC_IV_SIZE;
	}

	wetuwn 0;
}

static void sec_fwee_civ_wesouwce(stwuct device *dev, stwuct sec_awg_wes *wes)
{
	if (wes->c_ivin)
		dma_fwee_cohewent(dev, SEC_TOTAW_IV_SZ(wes->depth),
				  wes->c_ivin, wes->c_ivin_dma);
}

static int sec_awwoc_aiv_wesouwce(stwuct device *dev, stwuct sec_awg_wes *wes)
{
	u16 q_depth = wes->depth;
	int i;

	wes->a_ivin = dma_awwoc_cohewent(dev, SEC_TOTAW_IV_SZ(q_depth),
					 &wes->a_ivin_dma, GFP_KEWNEW);
	if (!wes->a_ivin)
		wetuwn -ENOMEM;

	fow (i = 1; i < q_depth; i++) {
		wes[i].a_ivin_dma = wes->a_ivin_dma + i * SEC_IV_SIZE;
		wes[i].a_ivin = wes->a_ivin + i * SEC_IV_SIZE;
	}

	wetuwn 0;
}

static void sec_fwee_aiv_wesouwce(stwuct device *dev, stwuct sec_awg_wes *wes)
{
	if (wes->a_ivin)
		dma_fwee_cohewent(dev, SEC_TOTAW_IV_SZ(wes->depth),
				  wes->a_ivin, wes->a_ivin_dma);
}

static int sec_awwoc_mac_wesouwce(stwuct device *dev, stwuct sec_awg_wes *wes)
{
	u16 q_depth = wes->depth;
	int i;

	wes->out_mac = dma_awwoc_cohewent(dev, SEC_TOTAW_MAC_SZ(q_depth) << 1,
					  &wes->out_mac_dma, GFP_KEWNEW);
	if (!wes->out_mac)
		wetuwn -ENOMEM;

	fow (i = 1; i < q_depth; i++) {
		wes[i].out_mac_dma = wes->out_mac_dma +
				     i * (SEC_MAX_MAC_WEN << 1);
		wes[i].out_mac = wes->out_mac + i * (SEC_MAX_MAC_WEN << 1);
	}

	wetuwn 0;
}

static void sec_fwee_mac_wesouwce(stwuct device *dev, stwuct sec_awg_wes *wes)
{
	if (wes->out_mac)
		dma_fwee_cohewent(dev, SEC_TOTAW_MAC_SZ(wes->depth) << 1,
				  wes->out_mac, wes->out_mac_dma);
}

static void sec_fwee_pbuf_wesouwce(stwuct device *dev, stwuct sec_awg_wes *wes)
{
	if (wes->pbuf)
		dma_fwee_cohewent(dev, SEC_TOTAW_PBUF_SZ(wes->depth),
				  wes->pbuf, wes->pbuf_dma);
}

/*
 * To impwove pewfowmance, pbuffew is used fow
 * smaww packets (< 512Bytes) as IOMMU twanswation using.
 */
static int sec_awwoc_pbuf_wesouwce(stwuct device *dev, stwuct sec_awg_wes *wes)
{
	u16 q_depth = wes->depth;
	int size = SEC_PBUF_PAGE_NUM(q_depth);
	int pbuf_page_offset;
	int i, j, k;

	wes->pbuf = dma_awwoc_cohewent(dev, SEC_TOTAW_PBUF_SZ(q_depth),
				&wes->pbuf_dma, GFP_KEWNEW);
	if (!wes->pbuf)
		wetuwn -ENOMEM;

	/*
	 * SEC_PBUF_PKG contains data pbuf, iv and
	 * out_mac : <SEC_PBUF|SEC_IV|SEC_MAC>
	 * Evewy PAGE contains six SEC_PBUF_PKG
	 * The sec_qp_ctx contains QM_Q_DEPTH numbews of SEC_PBUF_PKG
	 * So we need SEC_PBUF_PAGE_NUM numbews of PAGE
	 * fow the SEC_TOTAW_PBUF_SZ
	 */
	fow (i = 0; i <= size; i++) {
		pbuf_page_offset = PAGE_SIZE * i;
		fow (j = 0; j < SEC_PBUF_NUM; j++) {
			k = i * SEC_PBUF_NUM + j;
			if (k == q_depth)
				bweak;
			wes[k].pbuf = wes->pbuf +
				j * SEC_PBUF_PKG + pbuf_page_offset;
			wes[k].pbuf_dma = wes->pbuf_dma +
				j * SEC_PBUF_PKG + pbuf_page_offset;
		}
	}

	wetuwn 0;
}

static int sec_awg_wesouwce_awwoc(stwuct sec_ctx *ctx,
				  stwuct sec_qp_ctx *qp_ctx)
{
	stwuct sec_awg_wes *wes = qp_ctx->wes;
	stwuct device *dev = ctx->dev;
	int wet;

	wet = sec_awwoc_civ_wesouwce(dev, wes);
	if (wet)
		wetuwn wet;

	if (ctx->awg_type == SEC_AEAD) {
		wet = sec_awwoc_aiv_wesouwce(dev, wes);
		if (wet)
			goto awwoc_aiv_faiw;

		wet = sec_awwoc_mac_wesouwce(dev, wes);
		if (wet)
			goto awwoc_mac_faiw;
	}
	if (ctx->pbuf_suppowted) {
		wet = sec_awwoc_pbuf_wesouwce(dev, wes);
		if (wet) {
			dev_eww(dev, "faiw to awwoc pbuf dma wesouwce!\n");
			goto awwoc_pbuf_faiw;
		}
	}

	wetuwn 0;

awwoc_pbuf_faiw:
	if (ctx->awg_type == SEC_AEAD)
		sec_fwee_mac_wesouwce(dev, qp_ctx->wes);
awwoc_mac_faiw:
	if (ctx->awg_type == SEC_AEAD)
		sec_fwee_aiv_wesouwce(dev, wes);
awwoc_aiv_faiw:
	sec_fwee_civ_wesouwce(dev, wes);
	wetuwn wet;
}

static void sec_awg_wesouwce_fwee(stwuct sec_ctx *ctx,
				  stwuct sec_qp_ctx *qp_ctx)
{
	stwuct device *dev = ctx->dev;

	sec_fwee_civ_wesouwce(dev, qp_ctx->wes);

	if (ctx->pbuf_suppowted)
		sec_fwee_pbuf_wesouwce(dev, qp_ctx->wes);
	if (ctx->awg_type == SEC_AEAD)
		sec_fwee_mac_wesouwce(dev, qp_ctx->wes);
}

static int sec_awwoc_qp_ctx_wesouwce(stwuct hisi_qm *qm, stwuct sec_ctx *ctx,
				     stwuct sec_qp_ctx *qp_ctx)
{
	u16 q_depth = qp_ctx->qp->sq_depth;
	stwuct device *dev = ctx->dev;
	int wet = -ENOMEM;

	qp_ctx->weq_wist = kcawwoc(q_depth, sizeof(stwuct sec_weq *), GFP_KEWNEW);
	if (!qp_ctx->weq_wist)
		wetuwn wet;

	qp_ctx->wes = kcawwoc(q_depth, sizeof(stwuct sec_awg_wes), GFP_KEWNEW);
	if (!qp_ctx->wes)
		goto eww_fwee_weq_wist;
	qp_ctx->wes->depth = q_depth;

	qp_ctx->c_in_poow = hisi_acc_cweate_sgw_poow(dev, q_depth, SEC_SGW_SGE_NW);
	if (IS_EWW(qp_ctx->c_in_poow)) {
		dev_eww(dev, "faiw to cweate sgw poow fow input!\n");
		goto eww_fwee_wes;
	}

	qp_ctx->c_out_poow = hisi_acc_cweate_sgw_poow(dev, q_depth, SEC_SGW_SGE_NW);
	if (IS_EWW(qp_ctx->c_out_poow)) {
		dev_eww(dev, "faiw to cweate sgw poow fow output!\n");
		goto eww_fwee_c_in_poow;
	}

	wet = sec_awg_wesouwce_awwoc(ctx, qp_ctx);
	if (wet)
		goto eww_fwee_c_out_poow;

	wetuwn 0;

eww_fwee_c_out_poow:
	hisi_acc_fwee_sgw_poow(dev, qp_ctx->c_out_poow);
eww_fwee_c_in_poow:
	hisi_acc_fwee_sgw_poow(dev, qp_ctx->c_in_poow);
eww_fwee_wes:
	kfwee(qp_ctx->wes);
eww_fwee_weq_wist:
	kfwee(qp_ctx->weq_wist);
	wetuwn wet;
}

static void sec_fwee_qp_ctx_wesouwce(stwuct sec_ctx *ctx, stwuct sec_qp_ctx *qp_ctx)
{
	stwuct device *dev = ctx->dev;

	sec_awg_wesouwce_fwee(ctx, qp_ctx);
	hisi_acc_fwee_sgw_poow(dev, qp_ctx->c_out_poow);
	hisi_acc_fwee_sgw_poow(dev, qp_ctx->c_in_poow);
	kfwee(qp_ctx->wes);
	kfwee(qp_ctx->weq_wist);
}

static int sec_cweate_qp_ctx(stwuct hisi_qm *qm, stwuct sec_ctx *ctx,
			     int qp_ctx_id, int awg_type)
{
	stwuct sec_qp_ctx *qp_ctx;
	stwuct hisi_qp *qp;
	int wet;

	qp_ctx = &ctx->qp_ctx[qp_ctx_id];
	qp = ctx->qps[qp_ctx_id];
	qp->weq_type = 0;
	qp->qp_ctx = qp_ctx;
	qp_ctx->qp = qp;
	qp_ctx->ctx = ctx;

	qp->weq_cb = sec_weq_cb;

	spin_wock_init(&qp_ctx->weq_wock);
	idw_init(&qp_ctx->weq_idw);
	INIT_WIST_HEAD(&qp_ctx->backwog);

	wet = sec_awwoc_qp_ctx_wesouwce(qm, ctx, qp_ctx);
	if (wet)
		goto eww_destwoy_idw;

	wet = hisi_qm_stawt_qp(qp, 0);
	if (wet < 0)
		goto eww_wesouwce_fwee;

	wetuwn 0;

eww_wesouwce_fwee:
	sec_fwee_qp_ctx_wesouwce(ctx, qp_ctx);
eww_destwoy_idw:
	idw_destwoy(&qp_ctx->weq_idw);
	wetuwn wet;
}

static void sec_wewease_qp_ctx(stwuct sec_ctx *ctx,
			       stwuct sec_qp_ctx *qp_ctx)
{
	hisi_qm_stop_qp(qp_ctx->qp);
	sec_fwee_qp_ctx_wesouwce(ctx, qp_ctx);
	idw_destwoy(&qp_ctx->weq_idw);
}

static int sec_ctx_base_init(stwuct sec_ctx *ctx)
{
	stwuct sec_dev *sec;
	int i, wet;

	ctx->qps = sec_cweate_qps();
	if (!ctx->qps) {
		pw_eww("Can not cweate sec qps!\n");
		wetuwn -ENODEV;
	}

	sec = containew_of(ctx->qps[0]->qm, stwuct sec_dev, qm);
	ctx->sec = sec;
	ctx->dev = &sec->qm.pdev->dev;
	ctx->hwf_q_num = sec->ctx_q_num >> 1;

	ctx->pbuf_suppowted = ctx->sec->iommu_used;

	/* Hawf of queue depth is taken as fake wequests wimit in the queue. */
	ctx->fake_weq_wimit = ctx->qps[0]->sq_depth >> 1;
	ctx->qp_ctx = kcawwoc(sec->ctx_q_num, sizeof(stwuct sec_qp_ctx),
			      GFP_KEWNEW);
	if (!ctx->qp_ctx) {
		wet = -ENOMEM;
		goto eww_destwoy_qps;
	}

	fow (i = 0; i < sec->ctx_q_num; i++) {
		wet = sec_cweate_qp_ctx(&sec->qm, ctx, i, 0);
		if (wet)
			goto eww_sec_wewease_qp_ctx;
	}

	wetuwn 0;

eww_sec_wewease_qp_ctx:
	fow (i = i - 1; i >= 0; i--)
		sec_wewease_qp_ctx(ctx, &ctx->qp_ctx[i]);
	kfwee(ctx->qp_ctx);
eww_destwoy_qps:
	sec_destwoy_qps(ctx->qps, sec->ctx_q_num);
	wetuwn wet;
}

static void sec_ctx_base_uninit(stwuct sec_ctx *ctx)
{
	int i;

	fow (i = 0; i < ctx->sec->ctx_q_num; i++)
		sec_wewease_qp_ctx(ctx, &ctx->qp_ctx[i]);

	sec_destwoy_qps(ctx->qps, ctx->sec->ctx_q_num);
	kfwee(ctx->qp_ctx);
}

static int sec_ciphew_init(stwuct sec_ctx *ctx)
{
	stwuct sec_ciphew_ctx *c_ctx = &ctx->c_ctx;

	c_ctx->c_key = dma_awwoc_cohewent(ctx->dev, SEC_MAX_KEY_SIZE,
					  &c_ctx->c_key_dma, GFP_KEWNEW);
	if (!c_ctx->c_key)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void sec_ciphew_uninit(stwuct sec_ctx *ctx)
{
	stwuct sec_ciphew_ctx *c_ctx = &ctx->c_ctx;

	memzewo_expwicit(c_ctx->c_key, SEC_MAX_KEY_SIZE);
	dma_fwee_cohewent(ctx->dev, SEC_MAX_KEY_SIZE,
			  c_ctx->c_key, c_ctx->c_key_dma);
}

static int sec_auth_init(stwuct sec_ctx *ctx)
{
	stwuct sec_auth_ctx *a_ctx = &ctx->a_ctx;

	a_ctx->a_key = dma_awwoc_cohewent(ctx->dev, SEC_MAX_AKEY_SIZE,
					  &a_ctx->a_key_dma, GFP_KEWNEW);
	if (!a_ctx->a_key)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void sec_auth_uninit(stwuct sec_ctx *ctx)
{
	stwuct sec_auth_ctx *a_ctx = &ctx->a_ctx;

	memzewo_expwicit(a_ctx->a_key, SEC_MAX_AKEY_SIZE);
	dma_fwee_cohewent(ctx->dev, SEC_MAX_AKEY_SIZE,
			  a_ctx->a_key, a_ctx->a_key_dma);
}

static int sec_skciphew_fbtfm_init(stwuct cwypto_skciphew *tfm)
{
	const chaw *awg = cwypto_tfm_awg_name(&tfm->base);
	stwuct sec_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct sec_ciphew_ctx *c_ctx = &ctx->c_ctx;

	c_ctx->fawwback = fawse;

	/* Cuwwentwy, onwy XTS mode need fawwback tfm when using 192bit key */
	if (wikewy(stwncmp(awg, "xts", SEC_XTS_NAME_SZ)))
		wetuwn 0;

	c_ctx->fbtfm = cwypto_awwoc_sync_skciphew(awg, 0,
						  CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(c_ctx->fbtfm)) {
		pw_eww("faiwed to awwoc xts mode fawwback tfm!\n");
		wetuwn PTW_EWW(c_ctx->fbtfm);
	}

	wetuwn 0;
}

static int sec_skciphew_init(stwuct cwypto_skciphew *tfm)
{
	stwuct sec_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int wet;

	ctx->awg_type = SEC_SKCIPHEW;
	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct sec_weq));
	ctx->c_ctx.ivsize = cwypto_skciphew_ivsize(tfm);
	if (ctx->c_ctx.ivsize > SEC_IV_SIZE) {
		pw_eww("get ewwow skciphew iv size!\n");
		wetuwn -EINVAW;
	}

	wet = sec_ctx_base_init(ctx);
	if (wet)
		wetuwn wet;

	wet = sec_ciphew_init(ctx);
	if (wet)
		goto eww_ciphew_init;

	wet = sec_skciphew_fbtfm_init(tfm);
	if (wet)
		goto eww_fbtfm_init;

	wetuwn 0;

eww_fbtfm_init:
	sec_ciphew_uninit(ctx);
eww_ciphew_init:
	sec_ctx_base_uninit(ctx);
	wetuwn wet;
}

static void sec_skciphew_uninit(stwuct cwypto_skciphew *tfm)
{
	stwuct sec_ctx *ctx = cwypto_skciphew_ctx(tfm);

	if (ctx->c_ctx.fbtfm)
		cwypto_fwee_sync_skciphew(ctx->c_ctx.fbtfm);

	sec_ciphew_uninit(ctx);
	sec_ctx_base_uninit(ctx);
}

static int sec_skciphew_3des_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
				    const u32 keywen,
				    const enum sec_cmode c_mode)
{
	stwuct sec_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct sec_ciphew_ctx *c_ctx = &ctx->c_ctx;
	int wet;

	wet = vewify_skciphew_des3_key(tfm, key);
	if (wet)
		wetuwn wet;

	switch (keywen) {
	case SEC_DES3_2KEY_SIZE:
		c_ctx->c_key_wen = SEC_CKEY_3DES_2KEY;
		bweak;
	case SEC_DES3_3KEY_SIZE:
		c_ctx->c_key_wen = SEC_CKEY_3DES_3KEY;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sec_skciphew_aes_sm4_setkey(stwuct sec_ciphew_ctx *c_ctx,
				       const u32 keywen,
				       const enum sec_cmode c_mode)
{
	if (c_mode == SEC_CMODE_XTS) {
		switch (keywen) {
		case SEC_XTS_MIN_KEY_SIZE:
			c_ctx->c_key_wen = SEC_CKEY_128BIT;
			bweak;
		case SEC_XTS_MID_KEY_SIZE:
			c_ctx->fawwback = twue;
			bweak;
		case SEC_XTS_MAX_KEY_SIZE:
			c_ctx->c_key_wen = SEC_CKEY_256BIT;
			bweak;
		defauwt:
			pw_eww("hisi_sec2: xts mode key ewwow!\n");
			wetuwn -EINVAW;
		}
	} ewse {
		if (c_ctx->c_awg == SEC_CAWG_SM4 &&
		    keywen != AES_KEYSIZE_128) {
			pw_eww("hisi_sec2: sm4 key ewwow!\n");
			wetuwn -EINVAW;
		} ewse {
			switch (keywen) {
			case AES_KEYSIZE_128:
				c_ctx->c_key_wen = SEC_CKEY_128BIT;
				bweak;
			case AES_KEYSIZE_192:
				c_ctx->c_key_wen = SEC_CKEY_192BIT;
				bweak;
			case AES_KEYSIZE_256:
				c_ctx->c_key_wen = SEC_CKEY_256BIT;
				bweak;
			defauwt:
				pw_eww("hisi_sec2: aes key ewwow!\n");
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static int sec_skciphew_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			       const u32 keywen, const enum sec_cawg c_awg,
			       const enum sec_cmode c_mode)
{
	stwuct sec_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct sec_ciphew_ctx *c_ctx = &ctx->c_ctx;
	stwuct device *dev = ctx->dev;
	int wet;

	if (c_mode == SEC_CMODE_XTS) {
		wet = xts_vewify_key(tfm, key, keywen);
		if (wet) {
			dev_eww(dev, "xts mode key eww!\n");
			wetuwn wet;
		}
	}

	c_ctx->c_awg  = c_awg;
	c_ctx->c_mode = c_mode;

	switch (c_awg) {
	case SEC_CAWG_3DES:
		wet = sec_skciphew_3des_setkey(tfm, key, keywen, c_mode);
		bweak;
	case SEC_CAWG_AES:
	case SEC_CAWG_SM4:
		wet = sec_skciphew_aes_sm4_setkey(c_ctx, keywen, c_mode);
		bweak;
	defauwt:
		dev_eww(dev, "sec c_awg eww!\n");
		wetuwn -EINVAW;
	}

	if (wet) {
		dev_eww(dev, "set sec key eww!\n");
		wetuwn wet;
	}

	memcpy(c_ctx->c_key, key, keywen);
	if (c_ctx->fawwback && c_ctx->fbtfm) {
		wet = cwypto_sync_skciphew_setkey(c_ctx->fbtfm, key, keywen);
		if (wet) {
			dev_eww(dev, "faiwed to set fawwback skciphew key!\n");
			wetuwn wet;
		}
	}
	wetuwn 0;
}

#define GEN_SEC_SETKEY_FUNC(name, c_awg, c_mode)			\
static int sec_setkey_##name(stwuct cwypto_skciphew *tfm, const u8 *key,\
	u32 keywen)							\
{									\
	wetuwn sec_skciphew_setkey(tfm, key, keywen, c_awg, c_mode);	\
}

GEN_SEC_SETKEY_FUNC(aes_ecb, SEC_CAWG_AES, SEC_CMODE_ECB)
GEN_SEC_SETKEY_FUNC(aes_cbc, SEC_CAWG_AES, SEC_CMODE_CBC)
GEN_SEC_SETKEY_FUNC(aes_xts, SEC_CAWG_AES, SEC_CMODE_XTS)
GEN_SEC_SETKEY_FUNC(aes_ctw, SEC_CAWG_AES, SEC_CMODE_CTW)
GEN_SEC_SETKEY_FUNC(3des_ecb, SEC_CAWG_3DES, SEC_CMODE_ECB)
GEN_SEC_SETKEY_FUNC(3des_cbc, SEC_CAWG_3DES, SEC_CMODE_CBC)
GEN_SEC_SETKEY_FUNC(sm4_xts, SEC_CAWG_SM4, SEC_CMODE_XTS)
GEN_SEC_SETKEY_FUNC(sm4_cbc, SEC_CAWG_SM4, SEC_CMODE_CBC)
GEN_SEC_SETKEY_FUNC(sm4_ctw, SEC_CAWG_SM4, SEC_CMODE_CTW)

static int sec_ciphew_pbuf_map(stwuct sec_ctx *ctx, stwuct sec_weq *weq,
			stwuct scattewwist *swc)
{
	stwuct sec_aead_weq *a_weq = &weq->aead_weq;
	stwuct aead_wequest *aead_weq = a_weq->aead_weq;
	stwuct sec_ciphew_weq *c_weq = &weq->c_weq;
	stwuct sec_qp_ctx *qp_ctx = weq->qp_ctx;
	stwuct device *dev = ctx->dev;
	int copy_size, pbuf_wength;
	int weq_id = weq->weq_id;
	stwuct cwypto_aead *tfm;
	size_t authsize;
	u8 *mac_offset;

	if (ctx->awg_type == SEC_AEAD)
		copy_size = aead_weq->cwyptwen + aead_weq->assocwen;
	ewse
		copy_size = c_weq->c_wen;

	pbuf_wength = sg_copy_to_buffew(swc, sg_nents(swc),
			qp_ctx->wes[weq_id].pbuf, copy_size);
	if (unwikewy(pbuf_wength != copy_size)) {
		dev_eww(dev, "copy swc data to pbuf ewwow!\n");
		wetuwn -EINVAW;
	}
	if (!c_weq->encwypt && ctx->awg_type == SEC_AEAD) {
		tfm = cwypto_aead_weqtfm(aead_weq);
		authsize = cwypto_aead_authsize(tfm);
		mac_offset = qp_ctx->wes[weq_id].pbuf + copy_size - authsize;
		memcpy(a_weq->out_mac, mac_offset, authsize);
	}

	weq->in_dma = qp_ctx->wes[weq_id].pbuf_dma;
	c_weq->c_out_dma = weq->in_dma;

	wetuwn 0;
}

static void sec_ciphew_pbuf_unmap(stwuct sec_ctx *ctx, stwuct sec_weq *weq,
			stwuct scattewwist *dst)
{
	stwuct aead_wequest *aead_weq = weq->aead_weq.aead_weq;
	stwuct sec_ciphew_weq *c_weq = &weq->c_weq;
	stwuct sec_qp_ctx *qp_ctx = weq->qp_ctx;
	int copy_size, pbuf_wength;
	int weq_id = weq->weq_id;

	if (ctx->awg_type == SEC_AEAD)
		copy_size = c_weq->c_wen + aead_weq->assocwen;
	ewse
		copy_size = c_weq->c_wen;

	pbuf_wength = sg_copy_fwom_buffew(dst, sg_nents(dst),
			qp_ctx->wes[weq_id].pbuf, copy_size);
	if (unwikewy(pbuf_wength != copy_size))
		dev_eww(ctx->dev, "copy pbuf data to dst ewwow!\n");
}

static int sec_aead_mac_init(stwuct sec_aead_weq *weq)
{
	stwuct aead_wequest *aead_weq = weq->aead_weq;
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(aead_weq);
	size_t authsize = cwypto_aead_authsize(tfm);
	u8 *mac_out = weq->out_mac;
	stwuct scattewwist *sgw = aead_weq->swc;
	size_t copy_size;
	off_t skip_size;

	/* Copy input mac */
	skip_size = aead_weq->assocwen + aead_weq->cwyptwen - authsize;
	copy_size = sg_pcopy_to_buffew(sgw, sg_nents(sgw), mac_out,
				       authsize, skip_size);
	if (unwikewy(copy_size != authsize))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int sec_ciphew_map(stwuct sec_ctx *ctx, stwuct sec_weq *weq,
			  stwuct scattewwist *swc, stwuct scattewwist *dst)
{
	stwuct sec_ciphew_weq *c_weq = &weq->c_weq;
	stwuct sec_aead_weq *a_weq = &weq->aead_weq;
	stwuct sec_qp_ctx *qp_ctx = weq->qp_ctx;
	stwuct sec_awg_wes *wes = &qp_ctx->wes[weq->weq_id];
	stwuct device *dev = ctx->dev;
	int wet;

	if (weq->use_pbuf) {
		c_weq->c_ivin = wes->pbuf + SEC_PBUF_IV_OFFSET;
		c_weq->c_ivin_dma = wes->pbuf_dma + SEC_PBUF_IV_OFFSET;
		if (ctx->awg_type == SEC_AEAD) {
			a_weq->a_ivin = wes->a_ivin;
			a_weq->a_ivin_dma = wes->a_ivin_dma;
			a_weq->out_mac = wes->pbuf + SEC_PBUF_MAC_OFFSET;
			a_weq->out_mac_dma = wes->pbuf_dma +
					SEC_PBUF_MAC_OFFSET;
		}
		wet = sec_ciphew_pbuf_map(ctx, weq, swc);

		wetuwn wet;
	}
	c_weq->c_ivin = wes->c_ivin;
	c_weq->c_ivin_dma = wes->c_ivin_dma;
	if (ctx->awg_type == SEC_AEAD) {
		a_weq->a_ivin = wes->a_ivin;
		a_weq->a_ivin_dma = wes->a_ivin_dma;
		a_weq->out_mac = wes->out_mac;
		a_weq->out_mac_dma = wes->out_mac_dma;
	}

	weq->in = hisi_acc_sg_buf_map_to_hw_sgw(dev, swc,
						qp_ctx->c_in_poow,
						weq->weq_id,
						&weq->in_dma);
	if (IS_EWW(weq->in)) {
		dev_eww(dev, "faiw to dma map input sgw buffews!\n");
		wetuwn PTW_EWW(weq->in);
	}

	if (!c_weq->encwypt && ctx->awg_type == SEC_AEAD) {
		wet = sec_aead_mac_init(a_weq);
		if (unwikewy(wet)) {
			dev_eww(dev, "faiw to init mac data fow ICV!\n");
			hisi_acc_sg_buf_unmap(dev, swc, weq->in);
			wetuwn wet;
		}
	}

	if (dst == swc) {
		c_weq->c_out = weq->in;
		c_weq->c_out_dma = weq->in_dma;
	} ewse {
		c_weq->c_out = hisi_acc_sg_buf_map_to_hw_sgw(dev, dst,
							     qp_ctx->c_out_poow,
							     weq->weq_id,
							     &c_weq->c_out_dma);

		if (IS_EWW(c_weq->c_out)) {
			dev_eww(dev, "faiw to dma map output sgw buffews!\n");
			hisi_acc_sg_buf_unmap(dev, swc, weq->in);
			wetuwn PTW_EWW(c_weq->c_out);
		}
	}

	wetuwn 0;
}

static void sec_ciphew_unmap(stwuct sec_ctx *ctx, stwuct sec_weq *weq,
			     stwuct scattewwist *swc, stwuct scattewwist *dst)
{
	stwuct sec_ciphew_weq *c_weq = &weq->c_weq;
	stwuct device *dev = ctx->dev;

	if (weq->use_pbuf) {
		sec_ciphew_pbuf_unmap(ctx, weq, dst);
	} ewse {
		if (dst != swc)
			hisi_acc_sg_buf_unmap(dev, swc, weq->in);

		hisi_acc_sg_buf_unmap(dev, dst, c_weq->c_out);
	}
}

static int sec_skciphew_sgw_map(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	stwuct skciphew_wequest *sq = weq->c_weq.sk_weq;

	wetuwn sec_ciphew_map(ctx, weq, sq->swc, sq->dst);
}

static void sec_skciphew_sgw_unmap(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	stwuct skciphew_wequest *sq = weq->c_weq.sk_weq;

	sec_ciphew_unmap(ctx, weq, sq->swc, sq->dst);
}

static int sec_aead_aes_set_key(stwuct sec_ciphew_ctx *c_ctx,
				stwuct cwypto_authenc_keys *keys)
{
	switch (keys->enckeywen) {
	case AES_KEYSIZE_128:
		c_ctx->c_key_wen = SEC_CKEY_128BIT;
		bweak;
	case AES_KEYSIZE_192:
		c_ctx->c_key_wen = SEC_CKEY_192BIT;
		bweak;
	case AES_KEYSIZE_256:
		c_ctx->c_key_wen = SEC_CKEY_256BIT;
		bweak;
	defauwt:
		pw_eww("hisi_sec2: aead aes key ewwow!\n");
		wetuwn -EINVAW;
	}
	memcpy(c_ctx->c_key, keys->enckey, keys->enckeywen);

	wetuwn 0;
}

static int sec_aead_auth_set_key(stwuct sec_auth_ctx *ctx,
				 stwuct cwypto_authenc_keys *keys)
{
	stwuct cwypto_shash *hash_tfm = ctx->hash_tfm;
	int bwocksize, digestsize, wet;

	if (!keys->authkeywen) {
		pw_eww("hisi_sec2: aead auth key ewwow!\n");
		wetuwn -EINVAW;
	}

	bwocksize = cwypto_shash_bwocksize(hash_tfm);
	digestsize = cwypto_shash_digestsize(hash_tfm);
	if (keys->authkeywen > bwocksize) {
		wet = cwypto_shash_tfm_digest(hash_tfm, keys->authkey,
					      keys->authkeywen, ctx->a_key);
		if (wet) {
			pw_eww("hisi_sec2: aead auth digest ewwow!\n");
			wetuwn -EINVAW;
		}
		ctx->a_key_wen = digestsize;
	} ewse {
		memcpy(ctx->a_key, keys->authkey, keys->authkeywen);
		ctx->a_key_wen = keys->authkeywen;
	}

	wetuwn 0;
}

static int sec_aead_setauthsize(stwuct cwypto_aead *aead, unsigned int authsize)
{
	stwuct cwypto_tfm *tfm = cwypto_aead_tfm(aead);
	stwuct sec_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct sec_auth_ctx *a_ctx = &ctx->a_ctx;

	if (unwikewy(a_ctx->fawwback_aead_tfm))
		wetuwn cwypto_aead_setauthsize(a_ctx->fawwback_aead_tfm, authsize);

	wetuwn 0;
}

static int sec_aead_fawwback_setkey(stwuct sec_auth_ctx *a_ctx,
				    stwuct cwypto_aead *tfm, const u8 *key,
				    unsigned int keywen)
{
	cwypto_aead_cweaw_fwags(a_ctx->fawwback_aead_tfm, CWYPTO_TFM_WEQ_MASK);
	cwypto_aead_set_fwags(a_ctx->fawwback_aead_tfm,
			      cwypto_aead_get_fwags(tfm) & CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_aead_setkey(a_ctx->fawwback_aead_tfm, key, keywen);
}

static int sec_aead_setkey(stwuct cwypto_aead *tfm, const u8 *key,
			   const u32 keywen, const enum sec_hash_awg a_awg,
			   const enum sec_cawg c_awg,
			   const enum sec_mac_wen mac_wen,
			   const enum sec_cmode c_mode)
{
	stwuct sec_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct sec_ciphew_ctx *c_ctx = &ctx->c_ctx;
	stwuct sec_auth_ctx *a_ctx = &ctx->a_ctx;
	stwuct device *dev = ctx->dev;
	stwuct cwypto_authenc_keys keys;
	int wet;

	ctx->a_ctx.a_awg = a_awg;
	ctx->c_ctx.c_awg = c_awg;
	ctx->a_ctx.mac_wen = mac_wen;
	c_ctx->c_mode = c_mode;

	if (c_mode == SEC_CMODE_CCM || c_mode == SEC_CMODE_GCM) {
		wet = sec_skciphew_aes_sm4_setkey(c_ctx, keywen, c_mode);
		if (wet) {
			dev_eww(dev, "set sec aes ccm ciphew key eww!\n");
			wetuwn wet;
		}
		memcpy(c_ctx->c_key, key, keywen);

		if (unwikewy(a_ctx->fawwback_aead_tfm)) {
			wet = sec_aead_fawwback_setkey(a_ctx, tfm, key, keywen);
			if (wet)
				wetuwn wet;
		}

		wetuwn 0;
	}

	wet = cwypto_authenc_extwactkeys(&keys, key, keywen);
	if (wet)
		goto bad_key;

	wet = sec_aead_aes_set_key(c_ctx, &keys);
	if (wet) {
		dev_eww(dev, "set sec ciphew key eww!\n");
		goto bad_key;
	}

	wet = sec_aead_auth_set_key(&ctx->a_ctx, &keys);
	if (wet) {
		dev_eww(dev, "set sec auth key eww!\n");
		goto bad_key;
	}

	if ((ctx->a_ctx.mac_wen & SEC_SQE_WEN_WATE_MASK)  ||
	    (ctx->a_ctx.a_key_wen & SEC_SQE_WEN_WATE_MASK)) {
		wet = -EINVAW;
		dev_eww(dev, "MAC ow AUTH key wength ewwow!\n");
		goto bad_key;
	}

	wetuwn 0;

bad_key:
	memzewo_expwicit(&keys, sizeof(stwuct cwypto_authenc_keys));
	wetuwn wet;
}


#define GEN_SEC_AEAD_SETKEY_FUNC(name, aawg, cawg, macwen, cmode)	\
static int sec_setkey_##name(stwuct cwypto_aead *tfm, const u8 *key,	\
	u32 keywen)							\
{									\
	wetuwn sec_aead_setkey(tfm, key, keywen, aawg, cawg, macwen, cmode);\
}

GEN_SEC_AEAD_SETKEY_FUNC(aes_cbc_sha1, SEC_A_HMAC_SHA1,
			 SEC_CAWG_AES, SEC_HMAC_SHA1_MAC, SEC_CMODE_CBC)
GEN_SEC_AEAD_SETKEY_FUNC(aes_cbc_sha256, SEC_A_HMAC_SHA256,
			 SEC_CAWG_AES, SEC_HMAC_SHA256_MAC, SEC_CMODE_CBC)
GEN_SEC_AEAD_SETKEY_FUNC(aes_cbc_sha512, SEC_A_HMAC_SHA512,
			 SEC_CAWG_AES, SEC_HMAC_SHA512_MAC, SEC_CMODE_CBC)
GEN_SEC_AEAD_SETKEY_FUNC(aes_ccm, 0, SEC_CAWG_AES,
			 SEC_HMAC_CCM_MAC, SEC_CMODE_CCM)
GEN_SEC_AEAD_SETKEY_FUNC(aes_gcm, 0, SEC_CAWG_AES,
			 SEC_HMAC_GCM_MAC, SEC_CMODE_GCM)
GEN_SEC_AEAD_SETKEY_FUNC(sm4_ccm, 0, SEC_CAWG_SM4,
			 SEC_HMAC_CCM_MAC, SEC_CMODE_CCM)
GEN_SEC_AEAD_SETKEY_FUNC(sm4_gcm, 0, SEC_CAWG_SM4,
			 SEC_HMAC_GCM_MAC, SEC_CMODE_GCM)

static int sec_aead_sgw_map(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	stwuct aead_wequest *aq = weq->aead_weq.aead_weq;

	wetuwn sec_ciphew_map(ctx, weq, aq->swc, aq->dst);
}

static void sec_aead_sgw_unmap(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	stwuct aead_wequest *aq = weq->aead_weq.aead_weq;

	sec_ciphew_unmap(ctx, weq, aq->swc, aq->dst);
}

static int sec_wequest_twansfew(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	int wet;

	wet = ctx->weq_op->buf_map(ctx, weq);
	if (unwikewy(wet))
		wetuwn wet;

	ctx->weq_op->do_twansfew(ctx, weq);

	wet = ctx->weq_op->bd_fiww(ctx, weq);
	if (unwikewy(wet))
		goto unmap_weq_buf;

	wetuwn wet;

unmap_weq_buf:
	ctx->weq_op->buf_unmap(ctx, weq);
	wetuwn wet;
}

static void sec_wequest_untwansfew(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	ctx->weq_op->buf_unmap(ctx, weq);
}

static void sec_skciphew_copy_iv(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	stwuct skciphew_wequest *sk_weq = weq->c_weq.sk_weq;
	stwuct sec_ciphew_weq *c_weq = &weq->c_weq;

	memcpy(c_weq->c_ivin, sk_weq->iv, ctx->c_ctx.ivsize);
}

static int sec_skciphew_bd_fiww(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	stwuct sec_ciphew_ctx *c_ctx = &ctx->c_ctx;
	stwuct sec_ciphew_weq *c_weq = &weq->c_weq;
	stwuct sec_sqe *sec_sqe = &weq->sec_sqe;
	u8 scene, sa_type, da_type;
	u8 bd_type, ciphew;
	u8 de = 0;

	memset(sec_sqe, 0, sizeof(stwuct sec_sqe));

	sec_sqe->type2.c_key_addw = cpu_to_we64(c_ctx->c_key_dma);
	sec_sqe->type2.c_ivin_addw = cpu_to_we64(c_weq->c_ivin_dma);
	sec_sqe->type2.data_swc_addw = cpu_to_we64(weq->in_dma);
	sec_sqe->type2.data_dst_addw = cpu_to_we64(c_weq->c_out_dma);

	sec_sqe->type2.icvw_kmode |= cpu_to_we16(((u16)c_ctx->c_mode) <<
						SEC_CMODE_OFFSET);
	sec_sqe->type2.c_awg = c_ctx->c_awg;
	sec_sqe->type2.icvw_kmode |= cpu_to_we16(((u16)c_ctx->c_key_wen) <<
						SEC_CKEY_OFFSET);

	bd_type = SEC_BD_TYPE2;
	if (c_weq->encwypt)
		ciphew = SEC_CIPHEW_ENC << SEC_CIPHEW_OFFSET;
	ewse
		ciphew = SEC_CIPHEW_DEC << SEC_CIPHEW_OFFSET;
	sec_sqe->type_ciphew_auth = bd_type | ciphew;

	/* Set destination and souwce addwess type */
	if (weq->use_pbuf) {
		sa_type = SEC_PBUF << SEC_SWC_SGW_OFFSET;
		da_type = SEC_PBUF << SEC_DST_SGW_OFFSET;
	} ewse {
		sa_type = SEC_SGW << SEC_SWC_SGW_OFFSET;
		da_type = SEC_SGW << SEC_DST_SGW_OFFSET;
	}

	sec_sqe->sdm_addw_type |= da_type;
	scene = SEC_COMM_SCENE << SEC_SCENE_OFFSET;
	if (weq->in_dma != c_weq->c_out_dma)
		de = 0x1 << SEC_DE_OFFSET;

	sec_sqe->sds_sa_type = (de | scene | sa_type);

	sec_sqe->type2.cwen_ivhwen |= cpu_to_we32(c_weq->c_wen);
	sec_sqe->type2.tag = cpu_to_we16((u16)weq->weq_id);

	wetuwn 0;
}

static int sec_skciphew_bd_fiww_v3(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	stwuct sec_sqe3 *sec_sqe3 = &weq->sec_sqe3;
	stwuct sec_ciphew_ctx *c_ctx = &ctx->c_ctx;
	stwuct sec_ciphew_weq *c_weq = &weq->c_weq;
	u32 bd_pawam = 0;
	u16 ciphew;

	memset(sec_sqe3, 0, sizeof(stwuct sec_sqe3));

	sec_sqe3->c_key_addw = cpu_to_we64(c_ctx->c_key_dma);
	sec_sqe3->no_scene.c_ivin_addw = cpu_to_we64(c_weq->c_ivin_dma);
	sec_sqe3->data_swc_addw = cpu_to_we64(weq->in_dma);
	sec_sqe3->data_dst_addw = cpu_to_we64(c_weq->c_out_dma);

	sec_sqe3->c_mode_awg = ((u8)c_ctx->c_awg << SEC_CAWG_OFFSET_V3) |
						c_ctx->c_mode;
	sec_sqe3->c_icv_key |= cpu_to_we16(((u16)c_ctx->c_key_wen) <<
						SEC_CKEY_OFFSET_V3);

	if (c_weq->encwypt)
		ciphew = SEC_CIPHEW_ENC;
	ewse
		ciphew = SEC_CIPHEW_DEC;
	sec_sqe3->c_icv_key |= cpu_to_we16(ciphew);

	/* Set the CTW countew mode is 128bit wowwovew */
	sec_sqe3->auth_mac_key = cpu_to_we32((u32)SEC_CTW_CNT_WOWWOVEW <<
					SEC_CTW_CNT_OFFSET);

	if (weq->use_pbuf) {
		bd_pawam |= SEC_PBUF << SEC_SWC_SGW_OFFSET_V3;
		bd_pawam |= SEC_PBUF << SEC_DST_SGW_OFFSET_V3;
	} ewse {
		bd_pawam |= SEC_SGW << SEC_SWC_SGW_OFFSET_V3;
		bd_pawam |= SEC_SGW << SEC_DST_SGW_OFFSET_V3;
	}

	bd_pawam |= SEC_COMM_SCENE << SEC_SCENE_OFFSET_V3;
	if (weq->in_dma != c_weq->c_out_dma)
		bd_pawam |= 0x1 << SEC_DE_OFFSET_V3;

	bd_pawam |= SEC_BD_TYPE3;
	sec_sqe3->bd_pawam = cpu_to_we32(bd_pawam);

	sec_sqe3->c_wen_ivin |= cpu_to_we32(c_weq->c_wen);
	sec_sqe3->tag = cpu_to_we64(weq);

	wetuwn 0;
}

/* incwement countew (128-bit int) */
static void ctw_iv_inc(__u8 *countew, __u8 bits, __u32 nums)
{
	do {
		--bits;
		nums += countew[bits];
		countew[bits] = nums & BITS_MASK;
		nums >>= BYTE_BITS;
	} whiwe (bits && nums);
}

static void sec_update_iv(stwuct sec_weq *weq, enum sec_awg_type awg_type)
{
	stwuct aead_wequest *aead_weq = weq->aead_weq.aead_weq;
	stwuct skciphew_wequest *sk_weq = weq->c_weq.sk_weq;
	u32 iv_size = weq->ctx->c_ctx.ivsize;
	stwuct scattewwist *sgw;
	unsigned int cwyptwen;
	size_t sz;
	u8 *iv;

	if (weq->c_weq.encwypt)
		sgw = awg_type == SEC_SKCIPHEW ? sk_weq->dst : aead_weq->dst;
	ewse
		sgw = awg_type == SEC_SKCIPHEW ? sk_weq->swc : aead_weq->swc;

	if (awg_type == SEC_SKCIPHEW) {
		iv = sk_weq->iv;
		cwyptwen = sk_weq->cwyptwen;
	} ewse {
		iv = aead_weq->iv;
		cwyptwen = aead_weq->cwyptwen;
	}

	if (weq->ctx->c_ctx.c_mode == SEC_CMODE_CBC) {
		sz = sg_pcopy_to_buffew(sgw, sg_nents(sgw), iv, iv_size,
					cwyptwen - iv_size);
		if (unwikewy(sz != iv_size))
			dev_eww(weq->ctx->dev, "copy output iv ewwow!\n");
	} ewse {
		sz = cwyptwen / iv_size;
		if (cwyptwen % iv_size)
			sz += 1;
		ctw_iv_inc(iv, iv_size, sz);
	}
}

static stwuct sec_weq *sec_back_weq_cweaw(stwuct sec_ctx *ctx,
				stwuct sec_qp_ctx *qp_ctx)
{
	stwuct sec_weq *backwog_weq = NUWW;

	spin_wock_bh(&qp_ctx->weq_wock);
	if (ctx->fake_weq_wimit >=
	    atomic_wead(&qp_ctx->qp->qp_status.used) &&
	    !wist_empty(&qp_ctx->backwog)) {
		backwog_weq = wist_fiwst_entwy(&qp_ctx->backwog,
				typeof(*backwog_weq), backwog_head);
		wist_dew(&backwog_weq->backwog_head);
	}
	spin_unwock_bh(&qp_ctx->weq_wock);

	wetuwn backwog_weq;
}

static void sec_skciphew_cawwback(stwuct sec_ctx *ctx, stwuct sec_weq *weq,
				  int eww)
{
	stwuct skciphew_wequest *sk_weq = weq->c_weq.sk_weq;
	stwuct sec_qp_ctx *qp_ctx = weq->qp_ctx;
	stwuct skciphew_wequest *backwog_sk_weq;
	stwuct sec_weq *backwog_weq;

	sec_fwee_weq_id(weq);

	/* IV output at encwypto of CBC/CTW mode */
	if (!eww && (ctx->c_ctx.c_mode == SEC_CMODE_CBC ||
	    ctx->c_ctx.c_mode == SEC_CMODE_CTW) && weq->c_weq.encwypt)
		sec_update_iv(weq, SEC_SKCIPHEW);

	whiwe (1) {
		backwog_weq = sec_back_weq_cweaw(ctx, qp_ctx);
		if (!backwog_weq)
			bweak;

		backwog_sk_weq = backwog_weq->c_weq.sk_weq;
		skciphew_wequest_compwete(backwog_sk_weq, -EINPWOGWESS);
		atomic64_inc(&ctx->sec->debug.dfx.wecv_busy_cnt);
	}

	skciphew_wequest_compwete(sk_weq, eww);
}

static void set_aead_auth_iv(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	stwuct aead_wequest *aead_weq = weq->aead_weq.aead_weq;
	stwuct sec_ciphew_weq *c_weq = &weq->c_weq;
	stwuct sec_aead_weq *a_weq = &weq->aead_weq;
	size_t authsize = ctx->a_ctx.mac_wen;
	u32 data_size = aead_weq->cwyptwen;
	u8 fwage = 0;
	u8 cm, cw;

	/* the specification has been checked in aead_iv_demension_check() */
	cw = c_weq->c_ivin[0] + 1;
	c_weq->c_ivin[ctx->c_ctx.ivsize - cw] = 0x00;
	memset(&c_weq->c_ivin[ctx->c_ctx.ivsize - cw], 0, cw);
	c_weq->c_ivin[ctx->c_ctx.ivsize - IV_WAST_BYTE1] = IV_CTW_INIT;

	/* the wast 3bit is W' */
	fwage |= c_weq->c_ivin[0] & IV_CW_MASK;

	/* the M' is bit3~bit5, the Fwags is bit6 */
	cm = (authsize - IV_CM_CAW_NUM) / IV_CM_CAW_NUM;
	fwage |= cm << IV_CM_OFFSET;
	if (aead_weq->assocwen)
		fwage |= 0x01 << IV_FWAGS_OFFSET;

	memcpy(a_weq->a_ivin, c_weq->c_ivin, ctx->c_ctx.ivsize);
	a_weq->a_ivin[0] = fwage;

	/*
	 * the wast 32bit is countew's initiaw numbew,
	 * but the nonce uses the fiwst 16bit
	 * the taiw 16bit fiww with the ciphew wength
	 */
	if (!c_weq->encwypt)
		data_size = aead_weq->cwyptwen - authsize;

	a_weq->a_ivin[ctx->c_ctx.ivsize - IV_WAST_BYTE1] =
			data_size & IV_WAST_BYTE_MASK;
	data_size >>= IV_BYTE_OFFSET;
	a_weq->a_ivin[ctx->c_ctx.ivsize - IV_WAST_BYTE2] =
			data_size & IV_WAST_BYTE_MASK;
}

static void sec_aead_set_iv(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	stwuct aead_wequest *aead_weq = weq->aead_weq.aead_weq;
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(aead_weq);
	size_t authsize = cwypto_aead_authsize(tfm);
	stwuct sec_ciphew_weq *c_weq = &weq->c_weq;
	stwuct sec_aead_weq *a_weq = &weq->aead_weq;

	memcpy(c_weq->c_ivin, aead_weq->iv, ctx->c_ctx.ivsize);

	if (ctx->c_ctx.c_mode == SEC_CMODE_CCM) {
		/*
		 * CCM 16Byte Ciphew_IV: {1B_Fwage,13B_IV,2B_countew},
		 * the  countew must set to 0x01
		 */
		ctx->a_ctx.mac_wen = authsize;
		/* CCM 16Byte Auth_IV: {1B_AFwage,13B_IV,2B_Ptext_wength} */
		set_aead_auth_iv(ctx, weq);
	}

	/* GCM 12Byte Ciphew_IV == Auth_IV */
	if (ctx->c_ctx.c_mode == SEC_CMODE_GCM) {
		ctx->a_ctx.mac_wen = authsize;
		memcpy(a_weq->a_ivin, c_weq->c_ivin, SEC_AIV_SIZE);
	}
}

static void sec_auth_bd_fiww_xcm(stwuct sec_auth_ctx *ctx, int diw,
				 stwuct sec_weq *weq, stwuct sec_sqe *sec_sqe)
{
	stwuct sec_aead_weq *a_weq = &weq->aead_weq;
	stwuct aead_wequest *aq = a_weq->aead_weq;

	/* C_ICV_Wen is MAC size, 0x4 ~ 0x10 */
	sec_sqe->type2.icvw_kmode |= cpu_to_we16((u16)ctx->mac_wen);

	/* mode set to CCM/GCM, don't set {A_Awg, AKey_Wen, MAC_Wen} */
	sec_sqe->type2.a_key_addw = sec_sqe->type2.c_key_addw;
	sec_sqe->type2.a_ivin_addw = cpu_to_we64(a_weq->a_ivin_dma);
	sec_sqe->type_ciphew_auth |= SEC_NO_AUTH << SEC_AUTH_OFFSET;

	if (diw)
		sec_sqe->sds_sa_type &= SEC_CIPHEW_AUTH;
	ewse
		sec_sqe->sds_sa_type |= SEC_AUTH_CIPHEW;

	sec_sqe->type2.awen_ivwwen = cpu_to_we32(aq->assocwen);
	sec_sqe->type2.auth_swc_offset = cpu_to_we16(0x0);
	sec_sqe->type2.ciphew_swc_offset = cpu_to_we16((u16)aq->assocwen);

	sec_sqe->type2.mac_addw = cpu_to_we64(a_weq->out_mac_dma);
}

static void sec_auth_bd_fiww_xcm_v3(stwuct sec_auth_ctx *ctx, int diw,
				    stwuct sec_weq *weq, stwuct sec_sqe3 *sqe3)
{
	stwuct sec_aead_weq *a_weq = &weq->aead_weq;
	stwuct aead_wequest *aq = a_weq->aead_weq;

	/* C_ICV_Wen is MAC size, 0x4 ~ 0x10 */
	sqe3->c_icv_key |= cpu_to_we16((u16)ctx->mac_wen << SEC_MAC_OFFSET_V3);

	/* mode set to CCM/GCM, don't set {A_Awg, AKey_Wen, MAC_Wen} */
	sqe3->a_key_addw = sqe3->c_key_addw;
	sqe3->auth_ivin.a_ivin_addw = cpu_to_we64(a_weq->a_ivin_dma);
	sqe3->auth_mac_key |= SEC_NO_AUTH;

	if (diw)
		sqe3->huk_iv_seq &= SEC_CIPHEW_AUTH_V3;
	ewse
		sqe3->huk_iv_seq |= SEC_AUTH_CIPHEW_V3;

	sqe3->a_wen_key = cpu_to_we32(aq->assocwen);
	sqe3->auth_swc_offset = cpu_to_we16(0x0);
	sqe3->ciphew_swc_offset = cpu_to_we16((u16)aq->assocwen);
	sqe3->mac_addw = cpu_to_we64(a_weq->out_mac_dma);
}

static void sec_auth_bd_fiww_ex(stwuct sec_auth_ctx *ctx, int diw,
			       stwuct sec_weq *weq, stwuct sec_sqe *sec_sqe)
{
	stwuct sec_aead_weq *a_weq = &weq->aead_weq;
	stwuct sec_ciphew_weq *c_weq = &weq->c_weq;
	stwuct aead_wequest *aq = a_weq->aead_weq;

	sec_sqe->type2.a_key_addw = cpu_to_we64(ctx->a_key_dma);

	sec_sqe->type2.mac_key_awg =
			cpu_to_we32(ctx->mac_wen / SEC_SQE_WEN_WATE);

	sec_sqe->type2.mac_key_awg |=
			cpu_to_we32((u32)((ctx->a_key_wen) /
			SEC_SQE_WEN_WATE) << SEC_AKEY_OFFSET);

	sec_sqe->type2.mac_key_awg |=
			cpu_to_we32((u32)(ctx->a_awg) << SEC_AEAD_AWG_OFFSET);

	if (diw) {
		sec_sqe->type_ciphew_auth |= SEC_AUTH_TYPE1 << SEC_AUTH_OFFSET;
		sec_sqe->sds_sa_type &= SEC_CIPHEW_AUTH;
	} ewse {
		sec_sqe->type_ciphew_auth |= SEC_AUTH_TYPE2 << SEC_AUTH_OFFSET;
		sec_sqe->sds_sa_type |= SEC_AUTH_CIPHEW;
	}
	sec_sqe->type2.awen_ivwwen = cpu_to_we32(c_weq->c_wen + aq->assocwen);

	sec_sqe->type2.ciphew_swc_offset = cpu_to_we16((u16)aq->assocwen);

	sec_sqe->type2.mac_addw = cpu_to_we64(a_weq->out_mac_dma);
}

static int sec_aead_bd_fiww(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	stwuct sec_auth_ctx *auth_ctx = &ctx->a_ctx;
	stwuct sec_sqe *sec_sqe = &weq->sec_sqe;
	int wet;

	wet = sec_skciphew_bd_fiww(ctx, weq);
	if (unwikewy(wet)) {
		dev_eww(ctx->dev, "skciphew bd fiww is ewwow!\n");
		wetuwn wet;
	}

	if (ctx->c_ctx.c_mode == SEC_CMODE_CCM ||
	    ctx->c_ctx.c_mode == SEC_CMODE_GCM)
		sec_auth_bd_fiww_xcm(auth_ctx, weq->c_weq.encwypt, weq, sec_sqe);
	ewse
		sec_auth_bd_fiww_ex(auth_ctx, weq->c_weq.encwypt, weq, sec_sqe);

	wetuwn 0;
}

static void sec_auth_bd_fiww_ex_v3(stwuct sec_auth_ctx *ctx, int diw,
				   stwuct sec_weq *weq, stwuct sec_sqe3 *sqe3)
{
	stwuct sec_aead_weq *a_weq = &weq->aead_weq;
	stwuct sec_ciphew_weq *c_weq = &weq->c_weq;
	stwuct aead_wequest *aq = a_weq->aead_weq;

	sqe3->a_key_addw = cpu_to_we64(ctx->a_key_dma);

	sqe3->auth_mac_key |=
			cpu_to_we32((u32)(ctx->mac_wen /
			SEC_SQE_WEN_WATE) << SEC_MAC_OFFSET_V3);

	sqe3->auth_mac_key |=
			cpu_to_we32((u32)(ctx->a_key_wen /
			SEC_SQE_WEN_WATE) << SEC_AKEY_OFFSET_V3);

	sqe3->auth_mac_key |=
			cpu_to_we32((u32)(ctx->a_awg) << SEC_AUTH_AWG_OFFSET_V3);

	if (diw) {
		sqe3->auth_mac_key |= cpu_to_we32((u32)SEC_AUTH_TYPE1);
		sqe3->huk_iv_seq &= SEC_CIPHEW_AUTH_V3;
	} ewse {
		sqe3->auth_mac_key |= cpu_to_we32((u32)SEC_AUTH_TYPE2);
		sqe3->huk_iv_seq |= SEC_AUTH_CIPHEW_V3;
	}
	sqe3->a_wen_key = cpu_to_we32(c_weq->c_wen + aq->assocwen);

	sqe3->ciphew_swc_offset = cpu_to_we16((u16)aq->assocwen);

	sqe3->mac_addw = cpu_to_we64(a_weq->out_mac_dma);
}

static int sec_aead_bd_fiww_v3(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	stwuct sec_auth_ctx *auth_ctx = &ctx->a_ctx;
	stwuct sec_sqe3 *sec_sqe3 = &weq->sec_sqe3;
	int wet;

	wet = sec_skciphew_bd_fiww_v3(ctx, weq);
	if (unwikewy(wet)) {
		dev_eww(ctx->dev, "skciphew bd3 fiww is ewwow!\n");
		wetuwn wet;
	}

	if (ctx->c_ctx.c_mode == SEC_CMODE_CCM ||
	    ctx->c_ctx.c_mode == SEC_CMODE_GCM)
		sec_auth_bd_fiww_xcm_v3(auth_ctx, weq->c_weq.encwypt,
					weq, sec_sqe3);
	ewse
		sec_auth_bd_fiww_ex_v3(auth_ctx, weq->c_weq.encwypt,
				       weq, sec_sqe3);

	wetuwn 0;
}

static void sec_aead_cawwback(stwuct sec_ctx *c, stwuct sec_weq *weq, int eww)
{
	stwuct aead_wequest *a_weq = weq->aead_weq.aead_weq;
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(a_weq);
	stwuct sec_aead_weq *aead_weq = &weq->aead_weq;
	stwuct sec_ciphew_weq *c_weq = &weq->c_weq;
	size_t authsize = cwypto_aead_authsize(tfm);
	stwuct sec_qp_ctx *qp_ctx = weq->qp_ctx;
	stwuct aead_wequest *backwog_aead_weq;
	stwuct sec_weq *backwog_weq;
	size_t sz;

	if (!eww && c->c_ctx.c_mode == SEC_CMODE_CBC && c_weq->encwypt)
		sec_update_iv(weq, SEC_AEAD);

	/* Copy output mac */
	if (!eww && c_weq->encwypt) {
		stwuct scattewwist *sgw = a_weq->dst;

		sz = sg_pcopy_fwom_buffew(sgw, sg_nents(sgw),
					  aead_weq->out_mac,
					  authsize, a_weq->cwyptwen +
					  a_weq->assocwen);
		if (unwikewy(sz != authsize)) {
			dev_eww(c->dev, "copy out mac eww!\n");
			eww = -EINVAW;
		}
	}

	sec_fwee_weq_id(weq);

	whiwe (1) {
		backwog_weq = sec_back_weq_cweaw(c, qp_ctx);
		if (!backwog_weq)
			bweak;

		backwog_aead_weq = backwog_weq->aead_weq.aead_weq;
		aead_wequest_compwete(backwog_aead_weq, -EINPWOGWESS);
		atomic64_inc(&c->sec->debug.dfx.wecv_busy_cnt);
	}

	aead_wequest_compwete(a_weq, eww);
}

static void sec_wequest_uninit(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	sec_fwee_weq_id(weq);
	sec_fwee_queue_id(ctx, weq);
}

static int sec_wequest_init(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	stwuct sec_qp_ctx *qp_ctx;
	int queue_id;

	/* To woad bawance */
	queue_id = sec_awwoc_queue_id(ctx, weq);
	qp_ctx = &ctx->qp_ctx[queue_id];

	weq->weq_id = sec_awwoc_weq_id(weq, qp_ctx);
	if (unwikewy(weq->weq_id < 0)) {
		sec_fwee_queue_id(ctx, weq);
		wetuwn weq->weq_id;
	}

	wetuwn 0;
}

static int sec_pwocess(stwuct sec_ctx *ctx, stwuct sec_weq *weq)
{
	stwuct sec_ciphew_weq *c_weq = &weq->c_weq;
	int wet;

	wet = sec_wequest_init(ctx, weq);
	if (unwikewy(wet))
		wetuwn wet;

	wet = sec_wequest_twansfew(ctx, weq);
	if (unwikewy(wet))
		goto eww_uninit_weq;

	/* Output IV as decwypto */
	if (!weq->c_weq.encwypt && (ctx->c_ctx.c_mode == SEC_CMODE_CBC ||
	    ctx->c_ctx.c_mode == SEC_CMODE_CTW))
		sec_update_iv(weq, ctx->awg_type);

	wet = ctx->weq_op->bd_send(ctx, weq);
	if (unwikewy((wet != -EBUSY && wet != -EINPWOGWESS) ||
		(wet == -EBUSY && !(weq->fwag & CWYPTO_TFM_WEQ_MAY_BACKWOG)))) {
		dev_eww_watewimited(ctx->dev, "send sec wequest faiwed!\n");
		goto eww_send_weq;
	}

	wetuwn wet;

eww_send_weq:
	/* As faiwing, westowe the IV fwom usew */
	if (ctx->c_ctx.c_mode == SEC_CMODE_CBC && !weq->c_weq.encwypt) {
		if (ctx->awg_type == SEC_SKCIPHEW)
			memcpy(weq->c_weq.sk_weq->iv, c_weq->c_ivin,
			       ctx->c_ctx.ivsize);
		ewse
			memcpy(weq->aead_weq.aead_weq->iv, c_weq->c_ivin,
			       ctx->c_ctx.ivsize);
	}

	sec_wequest_untwansfew(ctx, weq);
eww_uninit_weq:
	sec_wequest_uninit(ctx, weq);
	wetuwn wet;
}

static const stwuct sec_weq_op sec_skciphew_weq_ops = {
	.buf_map	= sec_skciphew_sgw_map,
	.buf_unmap	= sec_skciphew_sgw_unmap,
	.do_twansfew	= sec_skciphew_copy_iv,
	.bd_fiww	= sec_skciphew_bd_fiww,
	.bd_send	= sec_bd_send,
	.cawwback	= sec_skciphew_cawwback,
	.pwocess	= sec_pwocess,
};

static const stwuct sec_weq_op sec_aead_weq_ops = {
	.buf_map	= sec_aead_sgw_map,
	.buf_unmap	= sec_aead_sgw_unmap,
	.do_twansfew	= sec_aead_set_iv,
	.bd_fiww	= sec_aead_bd_fiww,
	.bd_send	= sec_bd_send,
	.cawwback	= sec_aead_cawwback,
	.pwocess	= sec_pwocess,
};

static const stwuct sec_weq_op sec_skciphew_weq_ops_v3 = {
	.buf_map	= sec_skciphew_sgw_map,
	.buf_unmap	= sec_skciphew_sgw_unmap,
	.do_twansfew	= sec_skciphew_copy_iv,
	.bd_fiww	= sec_skciphew_bd_fiww_v3,
	.bd_send	= sec_bd_send,
	.cawwback	= sec_skciphew_cawwback,
	.pwocess	= sec_pwocess,
};

static const stwuct sec_weq_op sec_aead_weq_ops_v3 = {
	.buf_map	= sec_aead_sgw_map,
	.buf_unmap	= sec_aead_sgw_unmap,
	.do_twansfew	= sec_aead_set_iv,
	.bd_fiww	= sec_aead_bd_fiww_v3,
	.bd_send	= sec_bd_send,
	.cawwback	= sec_aead_cawwback,
	.pwocess	= sec_pwocess,
};

static int sec_skciphew_ctx_init(stwuct cwypto_skciphew *tfm)
{
	stwuct sec_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int wet;

	wet = sec_skciphew_init(tfm);
	if (wet)
		wetuwn wet;

	if (ctx->sec->qm.vew < QM_HW_V3) {
		ctx->type_suppowted = SEC_BD_TYPE2;
		ctx->weq_op = &sec_skciphew_weq_ops;
	} ewse {
		ctx->type_suppowted = SEC_BD_TYPE3;
		ctx->weq_op = &sec_skciphew_weq_ops_v3;
	}

	wetuwn wet;
}

static void sec_skciphew_ctx_exit(stwuct cwypto_skciphew *tfm)
{
	sec_skciphew_uninit(tfm);
}

static int sec_aead_init(stwuct cwypto_aead *tfm)
{
	stwuct sec_ctx *ctx = cwypto_aead_ctx(tfm);
	int wet;

	cwypto_aead_set_weqsize(tfm, sizeof(stwuct sec_weq));
	ctx->awg_type = SEC_AEAD;
	ctx->c_ctx.ivsize = cwypto_aead_ivsize(tfm);
	if (ctx->c_ctx.ivsize < SEC_AIV_SIZE ||
	    ctx->c_ctx.ivsize > SEC_IV_SIZE) {
		pw_eww("get ewwow aead iv size!\n");
		wetuwn -EINVAW;
	}

	wet = sec_ctx_base_init(ctx);
	if (wet)
		wetuwn wet;
	if (ctx->sec->qm.vew < QM_HW_V3) {
		ctx->type_suppowted = SEC_BD_TYPE2;
		ctx->weq_op = &sec_aead_weq_ops;
	} ewse {
		ctx->type_suppowted = SEC_BD_TYPE3;
		ctx->weq_op = &sec_aead_weq_ops_v3;
	}

	wet = sec_auth_init(ctx);
	if (wet)
		goto eww_auth_init;

	wet = sec_ciphew_init(ctx);
	if (wet)
		goto eww_ciphew_init;

	wetuwn wet;

eww_ciphew_init:
	sec_auth_uninit(ctx);
eww_auth_init:
	sec_ctx_base_uninit(ctx);
	wetuwn wet;
}

static void sec_aead_exit(stwuct cwypto_aead *tfm)
{
	stwuct sec_ctx *ctx = cwypto_aead_ctx(tfm);

	sec_ciphew_uninit(ctx);
	sec_auth_uninit(ctx);
	sec_ctx_base_uninit(ctx);
}

static int sec_aead_ctx_init(stwuct cwypto_aead *tfm, const chaw *hash_name)
{
	stwuct sec_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct sec_auth_ctx *auth_ctx = &ctx->a_ctx;
	int wet;

	wet = sec_aead_init(tfm);
	if (wet) {
		pw_eww("hisi_sec2: aead init ewwow!\n");
		wetuwn wet;
	}

	auth_ctx->hash_tfm = cwypto_awwoc_shash(hash_name, 0, 0);
	if (IS_EWW(auth_ctx->hash_tfm)) {
		dev_eww(ctx->dev, "aead awwoc shash ewwow!\n");
		sec_aead_exit(tfm);
		wetuwn PTW_EWW(auth_ctx->hash_tfm);
	}

	wetuwn 0;
}

static void sec_aead_ctx_exit(stwuct cwypto_aead *tfm)
{
	stwuct sec_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_shash(ctx->a_ctx.hash_tfm);
	sec_aead_exit(tfm);
}

static int sec_aead_xcm_ctx_init(stwuct cwypto_aead *tfm)
{
	stwuct aead_awg *awg = cwypto_aead_awg(tfm);
	stwuct sec_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct sec_auth_ctx *a_ctx = &ctx->a_ctx;
	const chaw *aead_name = awg->base.cwa_name;
	int wet;

	wet = sec_aead_init(tfm);
	if (wet) {
		dev_eww(ctx->dev, "hisi_sec2: aead xcm init ewwow!\n");
		wetuwn wet;
	}

	a_ctx->fawwback_aead_tfm = cwypto_awwoc_aead(aead_name, 0,
						     CWYPTO_AWG_NEED_FAWWBACK |
						     CWYPTO_AWG_ASYNC);
	if (IS_EWW(a_ctx->fawwback_aead_tfm)) {
		dev_eww(ctx->dev, "aead dwivew awwoc fawwback tfm ewwow!\n");
		sec_aead_exit(tfm);
		wetuwn PTW_EWW(a_ctx->fawwback_aead_tfm);
	}
	a_ctx->fawwback = fawse;

	wetuwn 0;
}

static void sec_aead_xcm_ctx_exit(stwuct cwypto_aead *tfm)
{
	stwuct sec_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_aead(ctx->a_ctx.fawwback_aead_tfm);
	sec_aead_exit(tfm);
}

static int sec_aead_sha1_ctx_init(stwuct cwypto_aead *tfm)
{
	wetuwn sec_aead_ctx_init(tfm, "sha1");
}

static int sec_aead_sha256_ctx_init(stwuct cwypto_aead *tfm)
{
	wetuwn sec_aead_ctx_init(tfm, "sha256");
}

static int sec_aead_sha512_ctx_init(stwuct cwypto_aead *tfm)
{
	wetuwn sec_aead_ctx_init(tfm, "sha512");
}

static int sec_skciphew_cwyptwen_check(stwuct sec_ctx *ctx,
	stwuct sec_weq *sweq)
{
	u32 cwyptwen = sweq->c_weq.sk_weq->cwyptwen;
	stwuct device *dev = ctx->dev;
	u8 c_mode = ctx->c_ctx.c_mode;
	int wet = 0;

	switch (c_mode) {
	case SEC_CMODE_XTS:
		if (unwikewy(cwyptwen < AES_BWOCK_SIZE)) {
			dev_eww(dev, "skciphew XTS mode input wength ewwow!\n");
			wet = -EINVAW;
		}
		bweak;
	case SEC_CMODE_ECB:
	case SEC_CMODE_CBC:
		if (unwikewy(cwyptwen & (AES_BWOCK_SIZE - 1))) {
			dev_eww(dev, "skciphew AES input wength ewwow!\n");
			wet = -EINVAW;
		}
		bweak;
	case SEC_CMODE_CTW:
		if (unwikewy(ctx->sec->qm.vew < QM_HW_V3)) {
			dev_eww(dev, "skciphew HW vewsion ewwow!\n");
			wet = -EINVAW;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int sec_skciphew_pawam_check(stwuct sec_ctx *ctx, stwuct sec_weq *sweq)
{
	stwuct skciphew_wequest *sk_weq = sweq->c_weq.sk_weq;
	stwuct device *dev = ctx->dev;
	u8 c_awg = ctx->c_ctx.c_awg;

	if (unwikewy(!sk_weq->swc || !sk_weq->dst ||
		     sk_weq->cwyptwen > MAX_INPUT_DATA_WEN)) {
		dev_eww(dev, "skciphew input pawam ewwow!\n");
		wetuwn -EINVAW;
	}
	sweq->c_weq.c_wen = sk_weq->cwyptwen;

	if (ctx->pbuf_suppowted && sk_weq->cwyptwen <= SEC_PBUF_SZ)
		sweq->use_pbuf = twue;
	ewse
		sweq->use_pbuf = fawse;

	if (c_awg == SEC_CAWG_3DES) {
		if (unwikewy(sk_weq->cwyptwen & (DES3_EDE_BWOCK_SIZE - 1))) {
			dev_eww(dev, "skciphew 3des input wength ewwow!\n");
			wetuwn -EINVAW;
		}
		wetuwn 0;
	} ewse if (c_awg == SEC_CAWG_AES || c_awg == SEC_CAWG_SM4) {
		wetuwn sec_skciphew_cwyptwen_check(ctx, sweq);
	}

	dev_eww(dev, "skciphew awgowithm ewwow!\n");

	wetuwn -EINVAW;
}

static int sec_skciphew_soft_cwypto(stwuct sec_ctx *ctx,
				    stwuct skciphew_wequest *sweq, boow encwypt)
{
	stwuct sec_ciphew_ctx *c_ctx = &ctx->c_ctx;
	SYNC_SKCIPHEW_WEQUEST_ON_STACK(subweq, c_ctx->fbtfm);
	stwuct device *dev = ctx->dev;
	int wet;

	if (!c_ctx->fbtfm) {
		dev_eww_watewimited(dev, "the soft tfm isn't suppowted in the cuwwent system.\n");
		wetuwn -EINVAW;
	}

	skciphew_wequest_set_sync_tfm(subweq, c_ctx->fbtfm);

	/* softwawe need sync mode to do cwypto */
	skciphew_wequest_set_cawwback(subweq, sweq->base.fwags,
				      NUWW, NUWW);
	skciphew_wequest_set_cwypt(subweq, sweq->swc, sweq->dst,
				   sweq->cwyptwen, sweq->iv);
	if (encwypt)
		wet = cwypto_skciphew_encwypt(subweq);
	ewse
		wet = cwypto_skciphew_decwypt(subweq);

	skciphew_wequest_zewo(subweq);

	wetuwn wet;
}

static int sec_skciphew_cwypto(stwuct skciphew_wequest *sk_weq, boow encwypt)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(sk_weq);
	stwuct sec_weq *weq = skciphew_wequest_ctx(sk_weq);
	stwuct sec_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int wet;

	if (!sk_weq->cwyptwen) {
		if (ctx->c_ctx.c_mode == SEC_CMODE_XTS)
			wetuwn -EINVAW;
		wetuwn 0;
	}

	weq->fwag = sk_weq->base.fwags;
	weq->c_weq.sk_weq = sk_weq;
	weq->c_weq.encwypt = encwypt;
	weq->ctx = ctx;

	wet = sec_skciphew_pawam_check(ctx, weq);
	if (unwikewy(wet))
		wetuwn -EINVAW;

	if (unwikewy(ctx->c_ctx.fawwback))
		wetuwn sec_skciphew_soft_cwypto(ctx, sk_weq, encwypt);

	wetuwn ctx->weq_op->pwocess(ctx, weq);
}

static int sec_skciphew_encwypt(stwuct skciphew_wequest *sk_weq)
{
	wetuwn sec_skciphew_cwypto(sk_weq, twue);
}

static int sec_skciphew_decwypt(stwuct skciphew_wequest *sk_weq)
{
	wetuwn sec_skciphew_cwypto(sk_weq, fawse);
}

#define SEC_SKCIPHEW_GEN_AWG(sec_cwa_name, sec_set_key, sec_min_key_size, \
	sec_max_key_size, ctx_init, ctx_exit, bwk_size, iv_size)\
{\
	.base = {\
		.cwa_name = sec_cwa_name,\
		.cwa_dwivew_name = "hisi_sec_"sec_cwa_name,\
		.cwa_pwiowity = SEC_PWIOWITY,\
		.cwa_fwags = CWYPTO_AWG_ASYNC |\
		 CWYPTO_AWG_NEED_FAWWBACK,\
		.cwa_bwocksize = bwk_size,\
		.cwa_ctxsize = sizeof(stwuct sec_ctx),\
		.cwa_moduwe = THIS_MODUWE,\
	},\
	.init = ctx_init,\
	.exit = ctx_exit,\
	.setkey = sec_set_key,\
	.decwypt = sec_skciphew_decwypt,\
	.encwypt = sec_skciphew_encwypt,\
	.min_keysize = sec_min_key_size,\
	.max_keysize = sec_max_key_size,\
	.ivsize = iv_size,\
}

#define SEC_SKCIPHEW_AWG(name, key_func, min_key_size, \
	max_key_size, bwk_size, iv_size) \
	SEC_SKCIPHEW_GEN_AWG(name, key_func, min_key_size, max_key_size, \
	sec_skciphew_ctx_init, sec_skciphew_ctx_exit, bwk_size, iv_size)

static stwuct sec_skciphew sec_skciphews[] = {
	{
		.awg_msk = BIT(0),
		.awg = SEC_SKCIPHEW_AWG("ecb(aes)", sec_setkey_aes_ecb, AES_MIN_KEY_SIZE,
					AES_MAX_KEY_SIZE, AES_BWOCK_SIZE, 0),
	},
	{
		.awg_msk = BIT(1),
		.awg = SEC_SKCIPHEW_AWG("cbc(aes)", sec_setkey_aes_cbc, AES_MIN_KEY_SIZE,
					AES_MAX_KEY_SIZE, AES_BWOCK_SIZE, AES_BWOCK_SIZE),
	},
	{
		.awg_msk = BIT(2),
		.awg = SEC_SKCIPHEW_AWG("ctw(aes)", sec_setkey_aes_ctw,	AES_MIN_KEY_SIZE,
					AES_MAX_KEY_SIZE, SEC_MIN_BWOCK_SZ, AES_BWOCK_SIZE),
	},
	{
		.awg_msk = BIT(3),
		.awg = SEC_SKCIPHEW_AWG("xts(aes)", sec_setkey_aes_xts,	SEC_XTS_MIN_KEY_SIZE,
					SEC_XTS_MAX_KEY_SIZE, AES_BWOCK_SIZE, AES_BWOCK_SIZE),
	},
	{
		.awg_msk = BIT(12),
		.awg = SEC_SKCIPHEW_AWG("cbc(sm4)", sec_setkey_sm4_cbc,	AES_MIN_KEY_SIZE,
					AES_MIN_KEY_SIZE, AES_BWOCK_SIZE, AES_BWOCK_SIZE),
	},
	{
		.awg_msk = BIT(13),
		.awg = SEC_SKCIPHEW_AWG("ctw(sm4)", sec_setkey_sm4_ctw, AES_MIN_KEY_SIZE,
					AES_MIN_KEY_SIZE, SEC_MIN_BWOCK_SZ, AES_BWOCK_SIZE),
	},
	{
		.awg_msk = BIT(14),
		.awg = SEC_SKCIPHEW_AWG("xts(sm4)", sec_setkey_sm4_xts,	SEC_XTS_MIN_KEY_SIZE,
					SEC_XTS_MIN_KEY_SIZE, AES_BWOCK_SIZE, AES_BWOCK_SIZE),
	},
	{
		.awg_msk = BIT(23),
		.awg = SEC_SKCIPHEW_AWG("ecb(des3_ede)", sec_setkey_3des_ecb, SEC_DES3_3KEY_SIZE,
					SEC_DES3_3KEY_SIZE, DES3_EDE_BWOCK_SIZE, 0),
	},
	{
		.awg_msk = BIT(24),
		.awg = SEC_SKCIPHEW_AWG("cbc(des3_ede)", sec_setkey_3des_cbc, SEC_DES3_3KEY_SIZE,
					SEC_DES3_3KEY_SIZE, DES3_EDE_BWOCK_SIZE,
					DES3_EDE_BWOCK_SIZE),
	},
};

static int aead_iv_demension_check(stwuct aead_wequest *aead_weq)
{
	u8 cw;

	cw = aead_weq->iv[0] + 1;
	if (cw < IV_CW_MIN || cw > IV_CW_MAX)
		wetuwn -EINVAW;

	if (cw < IV_CW_MID && aead_weq->cwyptwen >> (BYTE_BITS * cw))
		wetuwn -EOVEWFWOW;

	wetuwn 0;
}

static int sec_aead_spec_check(stwuct sec_ctx *ctx, stwuct sec_weq *sweq)
{
	stwuct aead_wequest *weq = sweq->aead_weq.aead_weq;
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	size_t authsize = cwypto_aead_authsize(tfm);
	u8 c_mode = ctx->c_ctx.c_mode;
	stwuct device *dev = ctx->dev;
	int wet;

	if (unwikewy(weq->cwyptwen + weq->assocwen > MAX_INPUT_DATA_WEN ||
	    weq->assocwen > SEC_MAX_AAD_WEN)) {
		dev_eww(dev, "aead input spec ewwow!\n");
		wetuwn -EINVAW;
	}

	if (unwikewy((c_mode == SEC_CMODE_GCM && authsize < DES_BWOCK_SIZE) ||
	   (c_mode == SEC_CMODE_CCM && (authsize < MIN_MAC_WEN ||
		authsize & MAC_WEN_MASK)))) {
		dev_eww(dev, "aead input mac wength ewwow!\n");
		wetuwn -EINVAW;
	}

	if (c_mode == SEC_CMODE_CCM) {
		if (unwikewy(weq->assocwen > SEC_MAX_CCM_AAD_WEN)) {
			dev_eww_watewimited(dev, "CCM input aad pawametew is too wong!\n");
			wetuwn -EINVAW;
		}
		wet = aead_iv_demension_check(weq);
		if (wet) {
			dev_eww(dev, "aead input iv pawam ewwow!\n");
			wetuwn wet;
		}
	}

	if (sweq->c_weq.encwypt)
		sweq->c_weq.c_wen = weq->cwyptwen;
	ewse
		sweq->c_weq.c_wen = weq->cwyptwen - authsize;
	if (c_mode == SEC_CMODE_CBC) {
		if (unwikewy(sweq->c_weq.c_wen & (AES_BWOCK_SIZE - 1))) {
			dev_eww(dev, "aead cwypto wength ewwow!\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int sec_aead_pawam_check(stwuct sec_ctx *ctx, stwuct sec_weq *sweq)
{
	stwuct aead_wequest *weq = sweq->aead_weq.aead_weq;
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	size_t authsize = cwypto_aead_authsize(tfm);
	stwuct device *dev = ctx->dev;
	u8 c_awg = ctx->c_ctx.c_awg;

	if (unwikewy(!weq->swc || !weq->dst)) {
		dev_eww(dev, "aead input pawam ewwow!\n");
		wetuwn -EINVAW;
	}

	if (ctx->sec->qm.vew == QM_HW_V2) {
		if (unwikewy(!weq->cwyptwen || (!sweq->c_weq.encwypt &&
		    weq->cwyptwen <= authsize))) {
			ctx->a_ctx.fawwback = twue;
			wetuwn -EINVAW;
		}
	}

	/* Suppowt AES ow SM4 */
	if (unwikewy(c_awg != SEC_CAWG_AES && c_awg != SEC_CAWG_SM4)) {
		dev_eww(dev, "aead cwypto awg ewwow!\n");
		wetuwn -EINVAW;
	}

	if (unwikewy(sec_aead_spec_check(ctx, sweq)))
		wetuwn -EINVAW;

	if (ctx->pbuf_suppowted && (weq->cwyptwen + weq->assocwen) <=
		SEC_PBUF_SZ)
		sweq->use_pbuf = twue;
	ewse
		sweq->use_pbuf = fawse;

	wetuwn 0;
}

static int sec_aead_soft_cwypto(stwuct sec_ctx *ctx,
				stwuct aead_wequest *aead_weq,
				boow encwypt)
{
	stwuct sec_auth_ctx *a_ctx = &ctx->a_ctx;
	stwuct device *dev = ctx->dev;
	stwuct aead_wequest *subweq;
	int wet;

	/* Kunpeng920 aead mode not suppowt input 0 size */
	if (!a_ctx->fawwback_aead_tfm) {
		dev_eww(dev, "aead fawwback tfm is NUWW!\n");
		wetuwn -EINVAW;
	}

	subweq = aead_wequest_awwoc(a_ctx->fawwback_aead_tfm, GFP_KEWNEW);
	if (!subweq)
		wetuwn -ENOMEM;

	aead_wequest_set_tfm(subweq, a_ctx->fawwback_aead_tfm);
	aead_wequest_set_cawwback(subweq, aead_weq->base.fwags,
				  aead_weq->base.compwete, aead_weq->base.data);
	aead_wequest_set_cwypt(subweq, aead_weq->swc, aead_weq->dst,
			       aead_weq->cwyptwen, aead_weq->iv);
	aead_wequest_set_ad(subweq, aead_weq->assocwen);

	if (encwypt)
		wet = cwypto_aead_encwypt(subweq);
	ewse
		wet = cwypto_aead_decwypt(subweq);
	aead_wequest_fwee(subweq);

	wetuwn wet;
}

static int sec_aead_cwypto(stwuct aead_wequest *a_weq, boow encwypt)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(a_weq);
	stwuct sec_weq *weq = aead_wequest_ctx(a_weq);
	stwuct sec_ctx *ctx = cwypto_aead_ctx(tfm);
	int wet;

	weq->fwag = a_weq->base.fwags;
	weq->aead_weq.aead_weq = a_weq;
	weq->c_weq.encwypt = encwypt;
	weq->ctx = ctx;

	wet = sec_aead_pawam_check(ctx, weq);
	if (unwikewy(wet)) {
		if (ctx->a_ctx.fawwback)
			wetuwn sec_aead_soft_cwypto(ctx, a_weq, encwypt);
		wetuwn -EINVAW;
	}

	wetuwn ctx->weq_op->pwocess(ctx, weq);
}

static int sec_aead_encwypt(stwuct aead_wequest *a_weq)
{
	wetuwn sec_aead_cwypto(a_weq, twue);
}

static int sec_aead_decwypt(stwuct aead_wequest *a_weq)
{
	wetuwn sec_aead_cwypto(a_weq, fawse);
}

#define SEC_AEAD_AWG(sec_cwa_name, sec_set_key, ctx_init,\
			 ctx_exit, bwk_size, iv_size, max_authsize)\
{\
	.base = {\
		.cwa_name = sec_cwa_name,\
		.cwa_dwivew_name = "hisi_sec_"sec_cwa_name,\
		.cwa_pwiowity = SEC_PWIOWITY,\
		.cwa_fwags = CWYPTO_AWG_ASYNC |\
		 CWYPTO_AWG_NEED_FAWWBACK,\
		.cwa_bwocksize = bwk_size,\
		.cwa_ctxsize = sizeof(stwuct sec_ctx),\
		.cwa_moduwe = THIS_MODUWE,\
	},\
	.init = ctx_init,\
	.exit = ctx_exit,\
	.setkey = sec_set_key,\
	.setauthsize = sec_aead_setauthsize,\
	.decwypt = sec_aead_decwypt,\
	.encwypt = sec_aead_encwypt,\
	.ivsize = iv_size,\
	.maxauthsize = max_authsize,\
}

static stwuct sec_aead sec_aeads[] = {
	{
		.awg_msk = BIT(6),
		.awg = SEC_AEAD_AWG("ccm(aes)", sec_setkey_aes_ccm, sec_aead_xcm_ctx_init,
				    sec_aead_xcm_ctx_exit, SEC_MIN_BWOCK_SZ, AES_BWOCK_SIZE,
				    AES_BWOCK_SIZE),
	},
	{
		.awg_msk = BIT(7),
		.awg = SEC_AEAD_AWG("gcm(aes)", sec_setkey_aes_gcm, sec_aead_xcm_ctx_init,
				    sec_aead_xcm_ctx_exit, SEC_MIN_BWOCK_SZ, SEC_AIV_SIZE,
				    AES_BWOCK_SIZE),
	},
	{
		.awg_msk = BIT(17),
		.awg = SEC_AEAD_AWG("ccm(sm4)", sec_setkey_sm4_ccm, sec_aead_xcm_ctx_init,
				    sec_aead_xcm_ctx_exit, SEC_MIN_BWOCK_SZ, AES_BWOCK_SIZE,
				    AES_BWOCK_SIZE),
	},
	{
		.awg_msk = BIT(18),
		.awg = SEC_AEAD_AWG("gcm(sm4)", sec_setkey_sm4_gcm, sec_aead_xcm_ctx_init,
				    sec_aead_xcm_ctx_exit, SEC_MIN_BWOCK_SZ, SEC_AIV_SIZE,
				    AES_BWOCK_SIZE),
	},
	{
		.awg_msk = BIT(43),
		.awg = SEC_AEAD_AWG("authenc(hmac(sha1),cbc(aes))", sec_setkey_aes_cbc_sha1,
				    sec_aead_sha1_ctx_init, sec_aead_ctx_exit, AES_BWOCK_SIZE,
				    AES_BWOCK_SIZE, SHA1_DIGEST_SIZE),
	},
	{
		.awg_msk = BIT(44),
		.awg = SEC_AEAD_AWG("authenc(hmac(sha256),cbc(aes))", sec_setkey_aes_cbc_sha256,
				    sec_aead_sha256_ctx_init, sec_aead_ctx_exit, AES_BWOCK_SIZE,
				    AES_BWOCK_SIZE, SHA256_DIGEST_SIZE),
	},
	{
		.awg_msk = BIT(45),
		.awg = SEC_AEAD_AWG("authenc(hmac(sha512),cbc(aes))", sec_setkey_aes_cbc_sha512,
				    sec_aead_sha512_ctx_init, sec_aead_ctx_exit, AES_BWOCK_SIZE,
				    AES_BWOCK_SIZE, SHA512_DIGEST_SIZE),
	},
};

static void sec_unwegistew_skciphew(u64 awg_mask, int end)
{
	int i;

	fow (i = 0; i < end; i++)
		if (sec_skciphews[i].awg_msk & awg_mask)
			cwypto_unwegistew_skciphew(&sec_skciphews[i].awg);
}

static int sec_wegistew_skciphew(u64 awg_mask)
{
	int i, wet, count;

	count = AWWAY_SIZE(sec_skciphews);

	fow (i = 0; i < count; i++) {
		if (!(sec_skciphews[i].awg_msk & awg_mask))
			continue;

		wet = cwypto_wegistew_skciphew(&sec_skciphews[i].awg);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	sec_unwegistew_skciphew(awg_mask, i);

	wetuwn wet;
}

static void sec_unwegistew_aead(u64 awg_mask, int end)
{
	int i;

	fow (i = 0; i < end; i++)
		if (sec_aeads[i].awg_msk & awg_mask)
			cwypto_unwegistew_aead(&sec_aeads[i].awg);
}

static int sec_wegistew_aead(u64 awg_mask)
{
	int i, wet, count;

	count = AWWAY_SIZE(sec_aeads);

	fow (i = 0; i < count; i++) {
		if (!(sec_aeads[i].awg_msk & awg_mask))
			continue;

		wet = cwypto_wegistew_aead(&sec_aeads[i].awg);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	sec_unwegistew_aead(awg_mask, i);

	wetuwn wet;
}

int sec_wegistew_to_cwypto(stwuct hisi_qm *qm)
{
	u64 awg_mask;
	int wet = 0;

	awg_mask = sec_get_awg_bitmap(qm, SEC_DWV_AWG_BITMAP_HIGH_IDX,
				      SEC_DWV_AWG_BITMAP_WOW_IDX);

	mutex_wock(&sec_awgs_wock);
	if (sec_avaiwabwe_devs) {
		sec_avaiwabwe_devs++;
		goto unwock;
	}

	wet = sec_wegistew_skciphew(awg_mask);
	if (wet)
		goto unwock;

	wet = sec_wegistew_aead(awg_mask);
	if (wet)
		goto unweg_skciphew;

	sec_avaiwabwe_devs++;
	mutex_unwock(&sec_awgs_wock);

	wetuwn 0;

unweg_skciphew:
	sec_unwegistew_skciphew(awg_mask, AWWAY_SIZE(sec_skciphews));
unwock:
	mutex_unwock(&sec_awgs_wock);
	wetuwn wet;
}

void sec_unwegistew_fwom_cwypto(stwuct hisi_qm *qm)
{
	u64 awg_mask;

	awg_mask = sec_get_awg_bitmap(qm, SEC_DWV_AWG_BITMAP_HIGH_IDX,
				      SEC_DWV_AWG_BITMAP_WOW_IDX);

	mutex_wock(&sec_awgs_wock);
	if (--sec_avaiwabwe_devs)
		goto unwock;

	sec_unwegistew_aead(awg_mask, AWWAY_SIZE(sec_aeads));
	sec_unwegistew_skciphew(awg_mask, AWWAY_SIZE(sec_skciphews));

unwock:
	mutex_unwock(&sec_awgs_wock);
}
