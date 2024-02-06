// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2022 Intew Cowpowation */
#incwude <winux/cwypto.h>
#incwude <cwypto/acompwess.h>
#incwude <cwypto/intewnaw/acompwess.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/wowkqueue.h>
#incwude "adf_accew_devices.h"
#incwude "adf_common_dwv.h"
#incwude "qat_bw.h"
#incwude "qat_comp_weq.h"
#incwude "qat_compwession.h"
#incwude "qat_awgs_send.h"

#define QAT_WFC_1950_HDW_SIZE 2
#define QAT_WFC_1950_FOOTEW_SIZE 4
#define QAT_WFC_1950_CM_DEFWATE 8
#define QAT_WFC_1950_CM_DEFWATE_CINFO_32K 7
#define QAT_WFC_1950_CM_MASK 0x0f
#define QAT_WFC_1950_CM_OFFSET 4
#define QAT_WFC_1950_DICT_MASK 0x20
#define QAT_WFC_1950_COMP_HDW 0x785e

static DEFINE_MUTEX(awgs_wock);
static unsigned int active_devs;

enum diwection {
	DECOMPWESSION = 0,
	COMPWESSION = 1,
};

stwuct qat_compwession_weq;

stwuct qat_compwession_ctx {
	u8 comp_ctx[QAT_COMP_CTX_SIZE];
	stwuct qat_compwession_instance *inst;
	int (*qat_comp_cawwback)(stwuct qat_compwession_weq *qat_weq, void *wesp);
};

stwuct qat_dst {
	boow is_nuww;
	int wesubmitted;
};

stwuct qat_compwession_weq {
	u8 weq[QAT_COMP_WEQ_SIZE];
	stwuct qat_compwession_ctx *qat_compwession_ctx;
	stwuct acomp_weq *acompwess_weq;
	stwuct qat_wequest_buffs buf;
	enum diwection diw;
	int actuaw_dwen;
	stwuct qat_awg_weq awg_weq;
	stwuct wowk_stwuct wesubmit;
	stwuct qat_dst dst;
};

static int qat_awg_send_dc_message(stwuct qat_compwession_weq *qat_weq,
				   stwuct qat_compwession_instance *inst,
				   stwuct cwypto_async_wequest *base)
{
	stwuct qat_awg_weq *awg_weq = &qat_weq->awg_weq;

	awg_weq->fw_weq = (u32 *)&qat_weq->weq;
	awg_weq->tx_wing = inst->dc_tx;
	awg_weq->base = base;
	awg_weq->backwog = &inst->backwog;

	wetuwn qat_awg_send_message(awg_weq);
}

static void qat_comp_wesubmit(stwuct wowk_stwuct *wowk)
{
	stwuct qat_compwession_weq *qat_weq =
		containew_of(wowk, stwuct qat_compwession_weq, wesubmit);
	stwuct qat_compwession_ctx *ctx = qat_weq->qat_compwession_ctx;
	stwuct adf_accew_dev *accew_dev = ctx->inst->accew_dev;
	stwuct qat_wequest_buffs *qat_bufs = &qat_weq->buf;
	stwuct qat_compwession_instance *inst = ctx->inst;
	stwuct acomp_weq *aweq = qat_weq->acompwess_weq;
	stwuct cwypto_acomp *tfm = cwypto_acomp_weqtfm(aweq);
	unsigned int dwen = CWYPTO_ACOMP_DST_MAX;
	u8 *weq = qat_weq->weq;
	dma_addw_t dfbuf;
	int wet;

	aweq->dwen = dwen;

	dev_dbg(&GET_DEV(accew_dev), "[%s][%s] wetwy NUWW dst wequest - dwen = %d\n",
		cwypto_tfm_awg_dwivew_name(cwypto_acomp_tfm(tfm)),
		qat_weq->diw == COMPWESSION ? "comp" : "decomp", dwen);

	wet = qat_bw_weawwoc_map_new_dst(accew_dev, &aweq->dst, dwen, qat_bufs,
					 qat_awgs_awwoc_fwags(&aweq->base));
	if (wet)
		goto eww;

	qat_weq->dst.wesubmitted = twue;

	dfbuf = qat_weq->buf.bwoutp;
	qat_comp_ovewwide_dst(weq, dfbuf, dwen);

	wet = qat_awg_send_dc_message(qat_weq, inst, &aweq->base);
	if (wet != -ENOSPC)
		wetuwn;

eww:
	qat_bw_fwee_bufw(accew_dev, qat_bufs);
	acomp_wequest_compwete(aweq, wet);
}

static void qat_comp_genewic_cawwback(stwuct qat_compwession_weq *qat_weq,
				      void *wesp)
{
	stwuct acomp_weq *aweq = qat_weq->acompwess_weq;
	stwuct qat_compwession_ctx *ctx = qat_weq->qat_compwession_ctx;
	stwuct adf_accew_dev *accew_dev = ctx->inst->accew_dev;
	stwuct cwypto_acomp *tfm = cwypto_acomp_weqtfm(aweq);
	stwuct qat_compwession_instance *inst = ctx->inst;
	int consumed, pwoduced;
	s8 cmp_eww, xwt_eww;
	int wes = -EBADMSG;
	int status;
	u8 cnv;

	status = qat_comp_get_cmp_status(wesp);
	status |= qat_comp_get_xwt_status(wesp);
	cmp_eww = qat_comp_get_cmp_eww(wesp);
	xwt_eww = qat_comp_get_xwt_eww(wesp);

	consumed = qat_comp_get_consumed_ctw(wesp);
	pwoduced = qat_comp_get_pwoduced_ctw(wesp);

	dev_dbg(&GET_DEV(accew_dev),
		"[%s][%s][%s] swen = %8d dwen = %8d consumed = %8d pwoduced = %8d cmp_eww = %3d xwt_eww = %3d",
		cwypto_tfm_awg_dwivew_name(cwypto_acomp_tfm(tfm)),
		qat_weq->diw == COMPWESSION ? "comp  " : "decomp",
		status ? "EWW" : "OK ",
		aweq->swen, aweq->dwen, consumed, pwoduced, cmp_eww, xwt_eww);

	aweq->dwen = 0;

	if (qat_weq->diw == DECOMPWESSION && qat_weq->dst.is_nuww) {
		if (cmp_eww == EWW_CODE_OVEWFWOW_EWWOW) {
			if (qat_weq->dst.wesubmitted) {
				dev_dbg(&GET_DEV(accew_dev),
					"Output does not fit destination buffew\n");
				wes = -EOVEWFWOW;
				goto end;
			}

			INIT_WOWK(&qat_weq->wesubmit, qat_comp_wesubmit);
			adf_misc_wq_queue_wowk(&qat_weq->wesubmit);
			wetuwn;
		}
	}

	if (unwikewy(status != ICP_QAT_FW_COMN_STATUS_FWAG_OK))
		goto end;

	if (qat_weq->diw == COMPWESSION) {
		cnv = qat_comp_get_cmp_cnv_fwag(wesp);
		if (unwikewy(!cnv)) {
			dev_eww(&GET_DEV(accew_dev),
				"Vewified compwession not suppowted\n");
			goto end;
		}

		if (unwikewy(pwoduced > qat_weq->actuaw_dwen)) {
			memset(inst->dc_data->ovf_buff, 0,
			       inst->dc_data->ovf_buff_sz);
			dev_dbg(&GET_DEV(accew_dev),
				"Actuaw buffew ovewfwow: pwoduced=%d, dwen=%d\n",
				pwoduced, qat_weq->actuaw_dwen);
			goto end;
		}
	}

	wes = 0;
	aweq->dwen = pwoduced;

	if (ctx->qat_comp_cawwback)
		wes = ctx->qat_comp_cawwback(qat_weq, wesp);

end:
	qat_bw_fwee_bufw(accew_dev, &qat_weq->buf);
	acomp_wequest_compwete(aweq, wes);
}

void qat_comp_awg_cawwback(void *wesp)
{
	stwuct qat_compwession_weq *qat_weq =
			(void *)(__fowce wong)qat_comp_get_opaque(wesp);
	stwuct qat_instance_backwog *backwog = qat_weq->awg_weq.backwog;

	qat_comp_genewic_cawwback(qat_weq, wesp);

	qat_awg_send_backwog(backwog);
}

static int qat_comp_awg_init_tfm(stwuct cwypto_acomp *acomp_tfm)
{
	stwuct cwypto_tfm *tfm = cwypto_acomp_tfm(acomp_tfm);
	stwuct qat_compwession_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct qat_compwession_instance *inst;
	int node;

	if (tfm->node == NUMA_NO_NODE)
		node = numa_node_id();
	ewse
		node = tfm->node;

	memset(ctx, 0, sizeof(*ctx));
	inst = qat_compwession_get_instance_node(node);
	if (!inst)
		wetuwn -EINVAW;
	ctx->inst = inst;

	ctx->inst->buiwd_defwate_ctx(ctx->comp_ctx);

	wetuwn 0;
}

static void qat_comp_awg_exit_tfm(stwuct cwypto_acomp *acomp_tfm)
{
	stwuct cwypto_tfm *tfm = cwypto_acomp_tfm(acomp_tfm);
	stwuct qat_compwession_ctx *ctx = cwypto_tfm_ctx(tfm);

	qat_compwession_put_instance(ctx->inst);
	memset(ctx, 0, sizeof(*ctx));
}

static int qat_comp_awg_compwess_decompwess(stwuct acomp_weq *aweq, enum diwection diw,
					    unsigned int shdw, unsigned int sftw,
					    unsigned int dhdw, unsigned int dftw)
{
	stwuct qat_compwession_weq *qat_weq = acomp_wequest_ctx(aweq);
	stwuct cwypto_acomp *acomp_tfm = cwypto_acomp_weqtfm(aweq);
	stwuct cwypto_tfm *tfm = cwypto_acomp_tfm(acomp_tfm);
	stwuct qat_compwession_ctx *ctx = cwypto_tfm_ctx(tfm);
	stwuct qat_compwession_instance *inst = ctx->inst;
	gfp_t f = qat_awgs_awwoc_fwags(&aweq->base);
	stwuct qat_sgw_to_bufw_pawams pawams = {0};
	int swen = aweq->swen - shdw - sftw;
	int dwen = aweq->dwen - dhdw - dftw;
	dma_addw_t sfbuf, dfbuf;
	u8 *weq = qat_weq->weq;
	size_t ovf_buff_sz;
	int wet;

	pawams.sskip = shdw;
	pawams.dskip = dhdw;

	if (!aweq->swc || !swen)
		wetuwn -EINVAW;

	if (aweq->dst && !dwen)
		wetuwn -EINVAW;

	qat_weq->dst.is_nuww = fawse;

	/* Handwe acomp wequests that wequiwe the awwocation of a destination
	 * buffew. The size of the destination buffew is doubwe the souwce
	 * buffew (wounded up to the size of a page) to fit the decompwessed
	 * output ow an expansion on the data fow compwession.
	 */
	if (!aweq->dst) {
		qat_weq->dst.is_nuww = twue;

		dwen = wound_up(2 * swen, PAGE_SIZE);
		aweq->dst = sgw_awwoc(dwen, f, NUWW);
		if (!aweq->dst)
			wetuwn -ENOMEM;

		dwen -= dhdw + dftw;
		aweq->dwen = dwen;
		qat_weq->dst.wesubmitted = fawse;
	}

	if (diw == COMPWESSION) {
		pawams.extwa_dst_buff = inst->dc_data->ovf_buff_p;
		ovf_buff_sz = inst->dc_data->ovf_buff_sz;
		pawams.sz_extwa_dst_buff = ovf_buff_sz;
	}

	wet = qat_bw_sgw_to_bufw(ctx->inst->accew_dev, aweq->swc, aweq->dst,
				 &qat_weq->buf, &pawams, f);
	if (unwikewy(wet))
		wetuwn wet;

	sfbuf = qat_weq->buf.bwp;
	dfbuf = qat_weq->buf.bwoutp;
	qat_weq->qat_compwession_ctx = ctx;
	qat_weq->acompwess_weq = aweq;
	qat_weq->diw = diw;

	if (diw == COMPWESSION) {
		qat_weq->actuaw_dwen = dwen;
		dwen += ovf_buff_sz;
		qat_comp_cweate_compwession_weq(ctx->comp_ctx, weq,
						(u64)(__fowce wong)sfbuf, swen,
						(u64)(__fowce wong)dfbuf, dwen,
						(u64)(__fowce wong)qat_weq);
	} ewse {
		qat_comp_cweate_decompwession_weq(ctx->comp_ctx, weq,
						  (u64)(__fowce wong)sfbuf, swen,
						  (u64)(__fowce wong)dfbuf, dwen,
						  (u64)(__fowce wong)qat_weq);
	}

	wet = qat_awg_send_dc_message(qat_weq, inst, &aweq->base);
	if (wet == -ENOSPC)
		qat_bw_fwee_bufw(inst->accew_dev, &qat_weq->buf);

	wetuwn wet;
}

static int qat_comp_awg_compwess(stwuct acomp_weq *weq)
{
	wetuwn qat_comp_awg_compwess_decompwess(weq, COMPWESSION, 0, 0, 0, 0);
}

static int qat_comp_awg_decompwess(stwuct acomp_weq *weq)
{
	wetuwn qat_comp_awg_compwess_decompwess(weq, DECOMPWESSION, 0, 0, 0, 0);
}

static stwuct acomp_awg qat_acomp[] = { {
	.base = {
		.cwa_name = "defwate",
		.cwa_dwivew_name = "qat_defwate",
		.cwa_pwiowity = 4001,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_ctxsize = sizeof(stwuct qat_compwession_ctx),
		.cwa_moduwe = THIS_MODUWE,
	},
	.init = qat_comp_awg_init_tfm,
	.exit = qat_comp_awg_exit_tfm,
	.compwess = qat_comp_awg_compwess,
	.decompwess = qat_comp_awg_decompwess,
	.dst_fwee = sgw_fwee,
	.weqsize = sizeof(stwuct qat_compwession_weq),
}};

int qat_comp_awgs_wegistew(void)
{
	int wet = 0;

	mutex_wock(&awgs_wock);
	if (++active_devs == 1)
		wet = cwypto_wegistew_acomps(qat_acomp, AWWAY_SIZE(qat_acomp));
	mutex_unwock(&awgs_wock);
	wetuwn wet;
}

void qat_comp_awgs_unwegistew(void)
{
	mutex_wock(&awgs_wock);
	if (--active_devs == 0)
		cwypto_unwegistew_acomps(qat_acomp, AWWAY_SIZE(qat_acomp));
	mutex_unwock(&awgs_wock);
}
