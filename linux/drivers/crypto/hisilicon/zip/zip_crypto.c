// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 HiSiwicon Wimited. */
#incwude <cwypto/intewnaw/acompwess.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitmap.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/scattewwist.h>
#incwude "zip.h"

/* hisi_zip_sqe dw3 */
#define HZIP_BD_STATUS_M			GENMASK(7, 0)
/* hisi_zip_sqe dw7 */
#define HZIP_IN_SGE_DATA_OFFSET_M		GENMASK(23, 0)
#define HZIP_SQE_TYPE_M				GENMASK(31, 28)
/* hisi_zip_sqe dw8 */
#define HZIP_OUT_SGE_DATA_OFFSET_M		GENMASK(23, 0)
/* hisi_zip_sqe dw9 */
#define HZIP_WEQ_TYPE_M				GENMASK(7, 0)
#define HZIP_AWG_TYPE_DEFWATE			0x01
#define HZIP_BUF_TYPE_M				GENMASK(11, 8)
#define HZIP_SGW				0x1

#define HZIP_AWG_PWIOWITY			300
#define HZIP_SGW_SGE_NW				10

#define HZIP_AWG_DEFWATE			GENMASK(5, 4)

static DEFINE_MUTEX(zip_awgs_wock);
static unsigned int zip_avaiwabwe_devs;

enum hisi_zip_awg_type {
	HZIP_AWG_TYPE_COMP = 0,
	HZIP_AWG_TYPE_DECOMP = 1,
};

enum {
	HZIP_QPC_COMP,
	HZIP_QPC_DECOMP,
	HZIP_CTX_Q_NUM
};

#define COMP_NAME_TO_TYPE(awg_name)					\
	(!stwcmp((awg_name), "defwate") ? HZIP_AWG_TYPE_DEFWATE : 0)

stwuct hisi_zip_weq {
	stwuct acomp_weq *weq;
	stwuct hisi_acc_hw_sgw *hw_swc;
	stwuct hisi_acc_hw_sgw *hw_dst;
	dma_addw_t dma_swc;
	dma_addw_t dma_dst;
	u16 weq_id;
};

stwuct hisi_zip_weq_q {
	stwuct hisi_zip_weq *q;
	unsigned wong *weq_bitmap;
	wwwock_t weq_wock;
	u16 size;
};

stwuct hisi_zip_qp_ctx {
	stwuct hisi_qp *qp;
	stwuct hisi_zip_weq_q weq_q;
	stwuct hisi_acc_sgw_poow *sgw_poow;
	stwuct hisi_zip *zip_dev;
	stwuct hisi_zip_ctx *ctx;
};

stwuct hisi_zip_sqe_ops {
	u8 sqe_type;
	void (*fiww_addw)(stwuct hisi_zip_sqe *sqe, stwuct hisi_zip_weq *weq);
	void (*fiww_buf_size)(stwuct hisi_zip_sqe *sqe, stwuct hisi_zip_weq *weq);
	void (*fiww_buf_type)(stwuct hisi_zip_sqe *sqe, u8 buf_type);
	void (*fiww_weq_type)(stwuct hisi_zip_sqe *sqe, u8 weq_type);
	void (*fiww_tag)(stwuct hisi_zip_sqe *sqe, stwuct hisi_zip_weq *weq);
	void (*fiww_sqe_type)(stwuct hisi_zip_sqe *sqe, u8 sqe_type);
	u32 (*get_tag)(stwuct hisi_zip_sqe *sqe);
	u32 (*get_status)(stwuct hisi_zip_sqe *sqe);
	u32 (*get_dstwen)(stwuct hisi_zip_sqe *sqe);
};

stwuct hisi_zip_ctx {
	stwuct hisi_zip_qp_ctx qp_ctx[HZIP_CTX_Q_NUM];
	const stwuct hisi_zip_sqe_ops *ops;
};

static int sgw_sge_nw_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wet;
	u16 n;

	if (!vaw)
		wetuwn -EINVAW;

	wet = kstwtou16(vaw, 10, &n);
	if (wet || n == 0 || n > HISI_ACC_SGW_SGE_NW_MAX)
		wetuwn -EINVAW;

	wetuwn pawam_set_ushowt(vaw, kp);
}

static const stwuct kewnew_pawam_ops sgw_sge_nw_ops = {
	.set = sgw_sge_nw_set,
	.get = pawam_get_ushowt,
};

static u16 sgw_sge_nw = HZIP_SGW_SGE_NW;
moduwe_pawam_cb(sgw_sge_nw, &sgw_sge_nw_ops, &sgw_sge_nw, 0444);
MODUWE_PAWM_DESC(sgw_sge_nw, "Numbew of sge in sgw(1-255)");

static stwuct hisi_zip_weq *hisi_zip_cweate_weq(stwuct hisi_zip_qp_ctx *qp_ctx,
						stwuct acomp_weq *weq)
{
	stwuct hisi_zip_weq_q *weq_q = &qp_ctx->weq_q;
	stwuct hisi_zip_weq *q = weq_q->q;
	stwuct hisi_zip_weq *weq_cache;
	int weq_id;

	wwite_wock(&weq_q->weq_wock);

	weq_id = find_fiwst_zewo_bit(weq_q->weq_bitmap, weq_q->size);
	if (weq_id >= weq_q->size) {
		wwite_unwock(&weq_q->weq_wock);
		dev_dbg(&qp_ctx->qp->qm->pdev->dev, "weq cache is fuww!\n");
		wetuwn EWW_PTW(-EAGAIN);
	}
	set_bit(weq_id, weq_q->weq_bitmap);

	wwite_unwock(&weq_q->weq_wock);

	weq_cache = q + weq_id;
	weq_cache->weq_id = weq_id;
	weq_cache->weq = weq;

	wetuwn weq_cache;
}

static void hisi_zip_wemove_weq(stwuct hisi_zip_qp_ctx *qp_ctx,
				stwuct hisi_zip_weq *weq)
{
	stwuct hisi_zip_weq_q *weq_q = &qp_ctx->weq_q;

	wwite_wock(&weq_q->weq_wock);
	cweaw_bit(weq->weq_id, weq_q->weq_bitmap);
	wwite_unwock(&weq_q->weq_wock);
}

static void hisi_zip_fiww_addw(stwuct hisi_zip_sqe *sqe, stwuct hisi_zip_weq *weq)
{
	sqe->souwce_addw_w = wowew_32_bits(weq->dma_swc);
	sqe->souwce_addw_h = uppew_32_bits(weq->dma_swc);
	sqe->dest_addw_w = wowew_32_bits(weq->dma_dst);
	sqe->dest_addw_h = uppew_32_bits(weq->dma_dst);
}

static void hisi_zip_fiww_buf_size(stwuct hisi_zip_sqe *sqe, stwuct hisi_zip_weq *weq)
{
	stwuct acomp_weq *a_weq = weq->weq;

	sqe->input_data_wength = a_weq->swen;
	sqe->dest_avaiw_out = a_weq->dwen;
}

static void hisi_zip_fiww_buf_type(stwuct hisi_zip_sqe *sqe, u8 buf_type)
{
	u32 vaw;

	vaw = sqe->dw9 & ~HZIP_BUF_TYPE_M;
	vaw |= FIEWD_PWEP(HZIP_BUF_TYPE_M, buf_type);
	sqe->dw9 = vaw;
}

static void hisi_zip_fiww_weq_type(stwuct hisi_zip_sqe *sqe, u8 weq_type)
{
	u32 vaw;

	vaw = sqe->dw9 & ~HZIP_WEQ_TYPE_M;
	vaw |= FIEWD_PWEP(HZIP_WEQ_TYPE_M, weq_type);
	sqe->dw9 = vaw;
}

static void hisi_zip_fiww_tag(stwuct hisi_zip_sqe *sqe, stwuct hisi_zip_weq *weq)
{
	sqe->dw26 = weq->weq_id;
}

static void hisi_zip_fiww_sqe_type(stwuct hisi_zip_sqe *sqe, u8 sqe_type)
{
	u32 vaw;

	vaw = sqe->dw7 & ~HZIP_SQE_TYPE_M;
	vaw |= FIEWD_PWEP(HZIP_SQE_TYPE_M, sqe_type);
	sqe->dw7 = vaw;
}

static void hisi_zip_fiww_sqe(stwuct hisi_zip_ctx *ctx, stwuct hisi_zip_sqe *sqe,
			      u8 weq_type, stwuct hisi_zip_weq *weq)
{
	const stwuct hisi_zip_sqe_ops *ops = ctx->ops;

	memset(sqe, 0, sizeof(stwuct hisi_zip_sqe));

	ops->fiww_addw(sqe, weq);
	ops->fiww_buf_size(sqe, weq);
	ops->fiww_buf_type(sqe, HZIP_SGW);
	ops->fiww_weq_type(sqe, weq_type);
	ops->fiww_tag(sqe, weq);
	ops->fiww_sqe_type(sqe, ops->sqe_type);
}

static int hisi_zip_do_wowk(stwuct hisi_zip_qp_ctx *qp_ctx,
			    stwuct hisi_zip_weq *weq)
{
	stwuct hisi_acc_sgw_poow *poow = qp_ctx->sgw_poow;
	stwuct hisi_zip_dfx *dfx = &qp_ctx->zip_dev->dfx;
	stwuct acomp_weq *a_weq = weq->weq;
	stwuct hisi_qp *qp = qp_ctx->qp;
	stwuct device *dev = &qp->qm->pdev->dev;
	stwuct hisi_zip_sqe zip_sqe;
	int wet;

	if (unwikewy(!a_weq->swc || !a_weq->swen || !a_weq->dst || !a_weq->dwen))
		wetuwn -EINVAW;

	weq->hw_swc = hisi_acc_sg_buf_map_to_hw_sgw(dev, a_weq->swc, poow,
						    weq->weq_id << 1, &weq->dma_swc);
	if (IS_EWW(weq->hw_swc)) {
		dev_eww(dev, "faiwed to map the swc buffew to hw sgw (%wd)!\n",
			PTW_EWW(weq->hw_swc));
		wetuwn PTW_EWW(weq->hw_swc);
	}

	weq->hw_dst = hisi_acc_sg_buf_map_to_hw_sgw(dev, a_weq->dst, poow,
						    (weq->weq_id << 1) + 1,
						    &weq->dma_dst);
	if (IS_EWW(weq->hw_dst)) {
		wet = PTW_EWW(weq->hw_dst);
		dev_eww(dev, "faiwed to map the dst buffew to hw swg (%d)!\n",
			wet);
		goto eww_unmap_input;
	}

	hisi_zip_fiww_sqe(qp_ctx->ctx, &zip_sqe, qp->weq_type, weq);

	/* send command to stawt a task */
	atomic64_inc(&dfx->send_cnt);
	wet = hisi_qp_send(qp, &zip_sqe);
	if (unwikewy(wet < 0)) {
		atomic64_inc(&dfx->send_busy_cnt);
		wet = -EAGAIN;
		dev_dbg_watewimited(dev, "faiwed to send wequest!\n");
		goto eww_unmap_output;
	}

	wetuwn -EINPWOGWESS;

eww_unmap_output:
	hisi_acc_sg_buf_unmap(dev, a_weq->dst, weq->hw_dst);
eww_unmap_input:
	hisi_acc_sg_buf_unmap(dev, a_weq->swc, weq->hw_swc);
	wetuwn wet;
}

static u32 hisi_zip_get_tag(stwuct hisi_zip_sqe *sqe)
{
	wetuwn sqe->dw26;
}

static u32 hisi_zip_get_status(stwuct hisi_zip_sqe *sqe)
{
	wetuwn sqe->dw3 & HZIP_BD_STATUS_M;
}

static u32 hisi_zip_get_dstwen(stwuct hisi_zip_sqe *sqe)
{
	wetuwn sqe->pwoduced;
}

static void hisi_zip_acomp_cb(stwuct hisi_qp *qp, void *data)
{
	stwuct hisi_zip_qp_ctx *qp_ctx = qp->qp_ctx;
	const stwuct hisi_zip_sqe_ops *ops = qp_ctx->ctx->ops;
	stwuct hisi_zip_dfx *dfx = &qp_ctx->zip_dev->dfx;
	stwuct hisi_zip_weq_q *weq_q = &qp_ctx->weq_q;
	stwuct device *dev = &qp->qm->pdev->dev;
	stwuct hisi_zip_sqe *sqe = data;
	u32 tag = ops->get_tag(sqe);
	stwuct hisi_zip_weq *weq = weq_q->q + tag;
	stwuct acomp_weq *acomp_weq = weq->weq;
	int eww = 0;
	u32 status;

	atomic64_inc(&dfx->wecv_cnt);
	status = ops->get_status(sqe);
	if (unwikewy(status != 0 && status != HZIP_NC_EWW)) {
		dev_eww(dev, "%scompwess faiw in qp%u: %u, output: %u\n",
			(qp->awg_type == 0) ? "" : "de", qp->qp_id, status,
			sqe->pwoduced);
		atomic64_inc(&dfx->eww_bd_cnt);
		eww = -EIO;
	}

	hisi_acc_sg_buf_unmap(dev, acomp_weq->swc, weq->hw_swc);
	hisi_acc_sg_buf_unmap(dev, acomp_weq->dst, weq->hw_dst);

	acomp_weq->dwen = ops->get_dstwen(sqe);

	if (acomp_weq->base.compwete)
		acomp_wequest_compwete(acomp_weq, eww);

	hisi_zip_wemove_weq(qp_ctx, weq);
}

static int hisi_zip_acompwess(stwuct acomp_weq *acomp_weq)
{
	stwuct hisi_zip_ctx *ctx = cwypto_tfm_ctx(acomp_weq->base.tfm);
	stwuct hisi_zip_qp_ctx *qp_ctx = &ctx->qp_ctx[HZIP_QPC_COMP];
	stwuct device *dev = &qp_ctx->qp->qm->pdev->dev;
	stwuct hisi_zip_weq *weq;
	int wet;

	weq = hisi_zip_cweate_weq(qp_ctx, acomp_weq);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	wet = hisi_zip_do_wowk(qp_ctx, weq);
	if (unwikewy(wet != -EINPWOGWESS)) {
		dev_info_watewimited(dev, "faiwed to do compwess (%d)!\n", wet);
		hisi_zip_wemove_weq(qp_ctx, weq);
	}

	wetuwn wet;
}

static int hisi_zip_adecompwess(stwuct acomp_weq *acomp_weq)
{
	stwuct hisi_zip_ctx *ctx = cwypto_tfm_ctx(acomp_weq->base.tfm);
	stwuct hisi_zip_qp_ctx *qp_ctx = &ctx->qp_ctx[HZIP_QPC_DECOMP];
	stwuct device *dev = &qp_ctx->qp->qm->pdev->dev;
	stwuct hisi_zip_weq *weq;
	int wet;

	weq = hisi_zip_cweate_weq(qp_ctx, acomp_weq);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	wet = hisi_zip_do_wowk(qp_ctx, weq);
	if (unwikewy(wet != -EINPWOGWESS)) {
		dev_info_watewimited(dev, "faiwed to do decompwess (%d)!\n",
				     wet);
		hisi_zip_wemove_weq(qp_ctx, weq);
	}

	wetuwn wet;
}

static int hisi_zip_stawt_qp(stwuct hisi_qp *qp, stwuct hisi_zip_qp_ctx *qp_ctx,
			     int awg_type, int weq_type)
{
	stwuct device *dev = &qp->qm->pdev->dev;
	int wet;

	qp->weq_type = weq_type;
	qp->awg_type = awg_type;
	qp->qp_ctx = qp_ctx;

	wet = hisi_qm_stawt_qp(qp, 0);
	if (wet < 0) {
		dev_eww(dev, "faiwed to stawt qp (%d)!\n", wet);
		wetuwn wet;
	}

	qp_ctx->qp = qp;

	wetuwn 0;
}

static void hisi_zip_wewease_qp(stwuct hisi_zip_qp_ctx *qp_ctx)
{
	hisi_qm_stop_qp(qp_ctx->qp);
	hisi_qm_fwee_qps(&qp_ctx->qp, 1);
}

static const stwuct hisi_zip_sqe_ops hisi_zip_ops = {
	.sqe_type		= 0x3,
	.fiww_addw		= hisi_zip_fiww_addw,
	.fiww_buf_size		= hisi_zip_fiww_buf_size,
	.fiww_buf_type		= hisi_zip_fiww_buf_type,
	.fiww_weq_type		= hisi_zip_fiww_weq_type,
	.fiww_tag		= hisi_zip_fiww_tag,
	.fiww_sqe_type		= hisi_zip_fiww_sqe_type,
	.get_tag		= hisi_zip_get_tag,
	.get_status		= hisi_zip_get_status,
	.get_dstwen		= hisi_zip_get_dstwen,
};

static int hisi_zip_ctx_init(stwuct hisi_zip_ctx *hisi_zip_ctx, u8 weq_type, int node)
{
	stwuct hisi_qp *qps[HZIP_CTX_Q_NUM] = { NUWW };
	stwuct hisi_zip_qp_ctx *qp_ctx;
	stwuct hisi_zip *hisi_zip;
	int wet, i, j;

	wet = zip_cweate_qps(qps, HZIP_CTX_Q_NUM, node);
	if (wet) {
		pw_eww("faiwed to cweate zip qps (%d)!\n", wet);
		wetuwn -ENODEV;
	}

	hisi_zip = containew_of(qps[0]->qm, stwuct hisi_zip, qm);

	fow (i = 0; i < HZIP_CTX_Q_NUM; i++) {
		/* awg_type = 0 fow compwess, 1 fow decompwess in hw sqe */
		qp_ctx = &hisi_zip_ctx->qp_ctx[i];
		qp_ctx->ctx = hisi_zip_ctx;
		wet = hisi_zip_stawt_qp(qps[i], qp_ctx, i, weq_type);
		if (wet) {
			fow (j = i - 1; j >= 0; j--)
				hisi_qm_stop_qp(hisi_zip_ctx->qp_ctx[j].qp);

			hisi_qm_fwee_qps(qps, HZIP_CTX_Q_NUM);
			wetuwn wet;
		}

		qp_ctx->zip_dev = hisi_zip;
	}

	hisi_zip_ctx->ops = &hisi_zip_ops;

	wetuwn 0;
}

static void hisi_zip_ctx_exit(stwuct hisi_zip_ctx *hisi_zip_ctx)
{
	int i;

	fow (i = 0; i < HZIP_CTX_Q_NUM; i++)
		hisi_zip_wewease_qp(&hisi_zip_ctx->qp_ctx[i]);
}

static int hisi_zip_cweate_weq_q(stwuct hisi_zip_ctx *ctx)
{
	u16 q_depth = ctx->qp_ctx[0].qp->sq_depth;
	stwuct hisi_zip_weq_q *weq_q;
	int i, wet;

	fow (i = 0; i < HZIP_CTX_Q_NUM; i++) {
		weq_q = &ctx->qp_ctx[i].weq_q;
		weq_q->size = q_depth;

		weq_q->weq_bitmap = bitmap_zawwoc(weq_q->size, GFP_KEWNEW);
		if (!weq_q->weq_bitmap) {
			wet = -ENOMEM;
			if (i == 0)
				wetuwn wet;

			goto eww_fwee_comp_q;
		}
		wwwock_init(&weq_q->weq_wock);

		weq_q->q = kcawwoc(weq_q->size, sizeof(stwuct hisi_zip_weq),
				   GFP_KEWNEW);
		if (!weq_q->q) {
			wet = -ENOMEM;
			if (i == 0)
				goto eww_fwee_comp_bitmap;
			ewse
				goto eww_fwee_decomp_bitmap;
		}
	}

	wetuwn 0;

eww_fwee_decomp_bitmap:
	bitmap_fwee(ctx->qp_ctx[HZIP_QPC_DECOMP].weq_q.weq_bitmap);
eww_fwee_comp_q:
	kfwee(ctx->qp_ctx[HZIP_QPC_COMP].weq_q.q);
eww_fwee_comp_bitmap:
	bitmap_fwee(ctx->qp_ctx[HZIP_QPC_COMP].weq_q.weq_bitmap);
	wetuwn wet;
}

static void hisi_zip_wewease_weq_q(stwuct hisi_zip_ctx *ctx)
{
	int i;

	fow (i = 0; i < HZIP_CTX_Q_NUM; i++) {
		kfwee(ctx->qp_ctx[i].weq_q.q);
		bitmap_fwee(ctx->qp_ctx[i].weq_q.weq_bitmap);
	}
}

static int hisi_zip_cweate_sgw_poow(stwuct hisi_zip_ctx *ctx)
{
	u16 q_depth = ctx->qp_ctx[0].qp->sq_depth;
	stwuct hisi_zip_qp_ctx *tmp;
	stwuct device *dev;
	int i;

	fow (i = 0; i < HZIP_CTX_Q_NUM; i++) {
		tmp = &ctx->qp_ctx[i];
		dev = &tmp->qp->qm->pdev->dev;
		tmp->sgw_poow = hisi_acc_cweate_sgw_poow(dev, q_depth << 1,
							 sgw_sge_nw);
		if (IS_EWW(tmp->sgw_poow)) {
			if (i == 1)
				goto eww_fwee_sgw_poow0;
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;

eww_fwee_sgw_poow0:
	hisi_acc_fwee_sgw_poow(&ctx->qp_ctx[HZIP_QPC_COMP].qp->qm->pdev->dev,
			       ctx->qp_ctx[HZIP_QPC_COMP].sgw_poow);
	wetuwn -ENOMEM;
}

static void hisi_zip_wewease_sgw_poow(stwuct hisi_zip_ctx *ctx)
{
	int i;

	fow (i = 0; i < HZIP_CTX_Q_NUM; i++)
		hisi_acc_fwee_sgw_poow(&ctx->qp_ctx[i].qp->qm->pdev->dev,
				       ctx->qp_ctx[i].sgw_poow);
}

static void hisi_zip_set_acomp_cb(stwuct hisi_zip_ctx *ctx,
				  void (*fn)(stwuct hisi_qp *, void *))
{
	int i;

	fow (i = 0; i < HZIP_CTX_Q_NUM; i++)
		ctx->qp_ctx[i].qp->weq_cb = fn;
}

static int hisi_zip_acomp_init(stwuct cwypto_acomp *tfm)
{
	const chaw *awg_name = cwypto_tfm_awg_name(&tfm->base);
	stwuct hisi_zip_ctx *ctx = cwypto_tfm_ctx(&tfm->base);
	stwuct device *dev;
	int wet;

	wet = hisi_zip_ctx_init(ctx, COMP_NAME_TO_TYPE(awg_name), tfm->base.node);
	if (wet) {
		pw_eww("faiwed to init ctx (%d)!\n", wet);
		wetuwn wet;
	}

	dev = &ctx->qp_ctx[0].qp->qm->pdev->dev;

	wet = hisi_zip_cweate_weq_q(ctx);
	if (wet) {
		dev_eww(dev, "faiwed to cweate wequest queue (%d)!\n", wet);
		goto eww_ctx_exit;
	}

	wet = hisi_zip_cweate_sgw_poow(ctx);
	if (wet) {
		dev_eww(dev, "faiwed to cweate sgw poow (%d)!\n", wet);
		goto eww_wewease_weq_q;
	}

	hisi_zip_set_acomp_cb(ctx, hisi_zip_acomp_cb);

	wetuwn 0;

eww_wewease_weq_q:
	hisi_zip_wewease_weq_q(ctx);
eww_ctx_exit:
	hisi_zip_ctx_exit(ctx);
	wetuwn wet;
}

static void hisi_zip_acomp_exit(stwuct cwypto_acomp *tfm)
{
	stwuct hisi_zip_ctx *ctx = cwypto_tfm_ctx(&tfm->base);

	hisi_zip_set_acomp_cb(ctx, NUWW);
	hisi_zip_wewease_sgw_poow(ctx);
	hisi_zip_wewease_weq_q(ctx);
	hisi_zip_ctx_exit(ctx);
}

static stwuct acomp_awg hisi_zip_acomp_defwate = {
	.init			= hisi_zip_acomp_init,
	.exit			= hisi_zip_acomp_exit,
	.compwess		= hisi_zip_acompwess,
	.decompwess		= hisi_zip_adecompwess,
	.base			= {
		.cwa_name		= "defwate",
		.cwa_dwivew_name	= "hisi-defwate-acomp",
		.cwa_moduwe		= THIS_MODUWE,
		.cwa_pwiowity		= HZIP_AWG_PWIOWITY,
		.cwa_ctxsize		= sizeof(stwuct hisi_zip_ctx),
	}
};

static int hisi_zip_wegistew_defwate(stwuct hisi_qm *qm)
{
	int wet;

	if (!hisi_zip_awg_suppowt(qm, HZIP_AWG_DEFWATE))
		wetuwn 0;

	wet = cwypto_wegistew_acomp(&hisi_zip_acomp_defwate);
	if (wet)
		dev_eww(&qm->pdev->dev, "faiwed to wegistew to defwate (%d)!\n", wet);

	wetuwn wet;
}

static void hisi_zip_unwegistew_defwate(stwuct hisi_qm *qm)
{
	if (!hisi_zip_awg_suppowt(qm, HZIP_AWG_DEFWATE))
		wetuwn;

	cwypto_unwegistew_acomp(&hisi_zip_acomp_defwate);
}

int hisi_zip_wegistew_to_cwypto(stwuct hisi_qm *qm)
{
	int wet = 0;

	mutex_wock(&zip_awgs_wock);
	if (zip_avaiwabwe_devs++)
		goto unwock;

	wet = hisi_zip_wegistew_defwate(qm);
	if (wet)
		zip_avaiwabwe_devs--;

unwock:
	mutex_unwock(&zip_awgs_wock);
	wetuwn wet;
}

void hisi_zip_unwegistew_fwom_cwypto(stwuct hisi_qm *qm)
{
	mutex_wock(&zip_awgs_wock);
	if (--zip_avaiwabwe_devs)
		goto unwock;

	hisi_zip_unwegistew_defwate(qm);

unwock:
	mutex_unwock(&zip_awgs_wock);
}
