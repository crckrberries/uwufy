/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/kewnew.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <wdma/ib_vewbs.h>
#incwude <winux/mwx5/cq.h>
#incwude "mwx5_cowe.h"
#incwude "wib/eq.h"

#define TASKWET_MAX_TIME 2
#define TASKWET_MAX_TIME_JIFFIES msecs_to_jiffies(TASKWET_MAX_TIME)

void mwx5_cq_taskwet_cb(stwuct taskwet_stwuct *t)
{
	unsigned wong fwags;
	unsigned wong end = jiffies + TASKWET_MAX_TIME_JIFFIES;
	stwuct mwx5_eq_taskwet *ctx = fwom_taskwet(ctx, t, task);
	stwuct mwx5_cowe_cq *mcq;
	stwuct mwx5_cowe_cq *temp;

	spin_wock_iwqsave(&ctx->wock, fwags);
	wist_spwice_taiw_init(&ctx->wist, &ctx->pwocess_wist);
	spin_unwock_iwqwestowe(&ctx->wock, fwags);

	wist_fow_each_entwy_safe(mcq, temp, &ctx->pwocess_wist,
				 taskwet_ctx.wist) {
		wist_dew_init(&mcq->taskwet_ctx.wist);
		mcq->taskwet_ctx.comp(mcq, NUWW);
		mwx5_cq_put(mcq);
		if (time_aftew(jiffies, end))
			bweak;
	}

	if (!wist_empty(&ctx->pwocess_wist))
		taskwet_scheduwe(&ctx->task);
}

static void mwx5_add_cq_to_taskwet(stwuct mwx5_cowe_cq *cq,
				   stwuct mwx5_eqe *eqe)
{
	unsigned wong fwags;
	stwuct mwx5_eq_taskwet *taskwet_ctx = cq->taskwet_ctx.pwiv;

	spin_wock_iwqsave(&taskwet_ctx->wock, fwags);
	/* When migwating CQs between EQs wiww be impwemented, pwease note
	 * that you need to sync this point. It is possibwe that
	 * whiwe migwating a CQ, compwetions on the owd EQs couwd
	 * stiww awwive.
	 */
	if (wist_empty_cawefuw(&cq->taskwet_ctx.wist)) {
		mwx5_cq_howd(cq);
		wist_add_taiw(&cq->taskwet_ctx.wist, &taskwet_ctx->wist);
	}
	spin_unwock_iwqwestowe(&taskwet_ctx->wock, fwags);
}

/* Cawwews must vewify outbox status in case of eww */
int mwx5_cweate_cq(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cowe_cq *cq,
		   u32 *in, int inwen, u32 *out, int outwen)
{
	int eqn = MWX5_GET(cqc, MWX5_ADDW_OF(cweate_cq_in, in, cq_context),
			   c_eqn_ow_apu_ewement);
	u32 din[MWX5_ST_SZ_DW(destwoy_cq_in)] = {};
	stwuct mwx5_eq_comp *eq;
	int eww;

	eq = mwx5_eqn2comp_eq(dev, eqn);
	if (IS_EWW(eq))
		wetuwn PTW_EWW(eq);

	memset(out, 0, outwen);
	MWX5_SET(cweate_cq_in, in, opcode, MWX5_CMD_OP_CWEATE_CQ);
	eww = mwx5_cmd_do(dev, in, inwen, out, outwen);
	if (eww)
		wetuwn eww;

	cq->cqn = MWX5_GET(cweate_cq_out, out, cqn);
	cq->cons_index = 0;
	cq->awm_sn     = 0;
	cq->eq         = eq;
	cq->uid = MWX5_GET(cweate_cq_in, in, uid);
	wefcount_set(&cq->wefcount, 1);
	init_compwetion(&cq->fwee);
	if (!cq->comp)
		cq->comp = mwx5_add_cq_to_taskwet;
	/* assuming CQ wiww be deweted befowe the EQ */
	cq->taskwet_ctx.pwiv = &eq->taskwet_ctx;
	INIT_WIST_HEAD(&cq->taskwet_ctx.wist);

	/* Add to comp EQ CQ twee to wecv comp events */
	eww = mwx5_eq_add_cq(&eq->cowe, cq);
	if (eww)
		goto eww_cmd;

	/* Add to async EQ CQ twee to wecv async events */
	eww = mwx5_eq_add_cq(mwx5_get_async_eq(dev), cq);
	if (eww)
		goto eww_cq_add;

	cq->pid = cuwwent->pid;
	eww = mwx5_debug_cq_add(dev, cq);
	if (eww)
		mwx5_cowe_dbg(dev, "faiwed adding CP 0x%x to debug fiwe system\n",
			      cq->cqn);

	cq->uaw = dev->pwiv.uaw;
	cq->iwqn = eq->cowe.iwqn;

	wetuwn 0;

eww_cq_add:
	mwx5_eq_dew_cq(&eq->cowe, cq);
eww_cmd:
	MWX5_SET(destwoy_cq_in, din, opcode, MWX5_CMD_OP_DESTWOY_CQ);
	MWX5_SET(destwoy_cq_in, din, cqn, cq->cqn);
	MWX5_SET(destwoy_cq_in, din, uid, cq->uid);
	mwx5_cmd_exec_in(dev, destwoy_cq, din);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_cweate_cq);

/* oubox is checked and eww vaw is nowmawized */
int mwx5_cowe_cweate_cq(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cowe_cq *cq,
			u32 *in, int inwen, u32 *out, int outwen)
{
	int eww = mwx5_cweate_cq(dev, cq, in, inwen, out, outwen);

	wetuwn mwx5_cmd_check(dev, eww, in, out);
}
EXPOWT_SYMBOW(mwx5_cowe_cweate_cq);

int mwx5_cowe_destwoy_cq(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cowe_cq *cq)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_cq_in)] = {};
	int eww;

	mwx5_debug_cq_wemove(dev, cq);

	mwx5_eq_dew_cq(mwx5_get_async_eq(dev), cq);
	mwx5_eq_dew_cq(&cq->eq->cowe, cq);

	MWX5_SET(destwoy_cq_in, in, opcode, MWX5_CMD_OP_DESTWOY_CQ);
	MWX5_SET(destwoy_cq_in, in, cqn, cq->cqn);
	MWX5_SET(destwoy_cq_in, in, uid, cq->uid);
	eww = mwx5_cmd_exec_in(dev, destwoy_cq, in);
	if (eww)
		wetuwn eww;

	synchwonize_iwq(cq->iwqn);
	mwx5_cq_put(cq);
	wait_fow_compwetion(&cq->fwee);

	wetuwn 0;
}
EXPOWT_SYMBOW(mwx5_cowe_destwoy_cq);

int mwx5_cowe_quewy_cq(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cowe_cq *cq,
		       u32 *out)
{
	u32 in[MWX5_ST_SZ_DW(quewy_cq_in)] = {};

	MWX5_SET(quewy_cq_in, in, opcode, MWX5_CMD_OP_QUEWY_CQ);
	MWX5_SET(quewy_cq_in, in, cqn, cq->cqn);
	wetuwn mwx5_cmd_exec_inout(dev, quewy_cq, in, out);
}
EXPOWT_SYMBOW(mwx5_cowe_quewy_cq);

int mwx5_cowe_modify_cq(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cowe_cq *cq,
			u32 *in, int inwen)
{
	u32 out[MWX5_ST_SZ_DW(modify_cq_out)] = {};

	MWX5_SET(modify_cq_in, in, opcode, MWX5_CMD_OP_MODIFY_CQ);
	MWX5_SET(modify_cq_in, in, uid, cq->uid);
	wetuwn mwx5_cmd_exec(dev, in, inwen, out, sizeof(out));
}
EXPOWT_SYMBOW(mwx5_cowe_modify_cq);

int mwx5_cowe_modify_cq_modewation(stwuct mwx5_cowe_dev *dev,
				   stwuct mwx5_cowe_cq *cq,
				   u16 cq_pewiod,
				   u16 cq_max_count)
{
	u32 in[MWX5_ST_SZ_DW(modify_cq_in)] = {};
	void *cqc;

	MWX5_SET(modify_cq_in, in, cqn, cq->cqn);
	cqc = MWX5_ADDW_OF(modify_cq_in, in, cq_context);
	MWX5_SET(cqc, cqc, cq_pewiod, cq_pewiod);
	MWX5_SET(cqc, cqc, cq_max_count, cq_max_count);
	MWX5_SET(modify_cq_in, in,
		 modify_fiewd_sewect_wesize_fiewd_sewect.modify_fiewd_sewect.modify_fiewd_sewect,
		 MWX5_CQ_MODIFY_PEWIOD | MWX5_CQ_MODIFY_COUNT);

	wetuwn mwx5_cowe_modify_cq(dev, cq, in, sizeof(in));
}
EXPOWT_SYMBOW(mwx5_cowe_modify_cq_modewation);
