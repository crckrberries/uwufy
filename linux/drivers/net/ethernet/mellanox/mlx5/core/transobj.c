/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies, Wtd.  Aww wights wesewved.
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

#incwude <winux/mwx5/dwivew.h>
#incwude "mwx5_cowe.h"
#incwude <winux/mwx5/twansobj.h>

int mwx5_cowe_awwoc_twanspowt_domain(stwuct mwx5_cowe_dev *dev, u32 *tdn)
{
	u32 out[MWX5_ST_SZ_DW(awwoc_twanspowt_domain_out)] = {};
	u32 in[MWX5_ST_SZ_DW(awwoc_twanspowt_domain_in)] = {};
	int eww;

	MWX5_SET(awwoc_twanspowt_domain_in, in, opcode,
		 MWX5_CMD_OP_AWWOC_TWANSPOWT_DOMAIN);

	eww = mwx5_cmd_exec_inout(dev, awwoc_twanspowt_domain, in, out);
	if (!eww)
		*tdn = MWX5_GET(awwoc_twanspowt_domain_out, out,
				twanspowt_domain);

	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_cowe_awwoc_twanspowt_domain);

void mwx5_cowe_deawwoc_twanspowt_domain(stwuct mwx5_cowe_dev *dev, u32 tdn)
{
	u32 in[MWX5_ST_SZ_DW(deawwoc_twanspowt_domain_in)] = {};

	MWX5_SET(deawwoc_twanspowt_domain_in, in, opcode,
		 MWX5_CMD_OP_DEAWWOC_TWANSPOWT_DOMAIN);
	MWX5_SET(deawwoc_twanspowt_domain_in, in, twanspowt_domain, tdn);
	mwx5_cmd_exec_in(dev, deawwoc_twanspowt_domain, in);
}
EXPOWT_SYMBOW(mwx5_cowe_deawwoc_twanspowt_domain);

int mwx5_cowe_cweate_wq(stwuct mwx5_cowe_dev *dev, u32 *in, int inwen, u32 *wqn)
{
	u32 out[MWX5_ST_SZ_DW(cweate_wq_out)] = {};
	int eww;

	MWX5_SET(cweate_wq_in, in, opcode, MWX5_CMD_OP_CWEATE_WQ);
	eww = mwx5_cmd_exec(dev, in, inwen, out, sizeof(out));
	if (!eww)
		*wqn = MWX5_GET(cweate_wq_out, out, wqn);

	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_cowe_cweate_wq);

int mwx5_cowe_modify_wq(stwuct mwx5_cowe_dev *dev, u32 wqn, u32 *in)
{
	MWX5_SET(modify_wq_in, in, wqn, wqn);
	MWX5_SET(modify_wq_in, in, opcode, MWX5_CMD_OP_MODIFY_WQ);

	wetuwn mwx5_cmd_exec_in(dev, modify_wq, in);
}
EXPOWT_SYMBOW(mwx5_cowe_modify_wq);

void mwx5_cowe_destwoy_wq(stwuct mwx5_cowe_dev *dev, u32 wqn)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_wq_in)] = {};

	MWX5_SET(destwoy_wq_in, in, opcode, MWX5_CMD_OP_DESTWOY_WQ);
	MWX5_SET(destwoy_wq_in, in, wqn, wqn);
	mwx5_cmd_exec_in(dev, destwoy_wq, in);
}
EXPOWT_SYMBOW(mwx5_cowe_destwoy_wq);

int mwx5_cowe_quewy_wq(stwuct mwx5_cowe_dev *dev, u32 wqn, u32 *out)
{
	u32 in[MWX5_ST_SZ_DW(quewy_wq_in)] = {};

	MWX5_SET(quewy_wq_in, in, opcode, MWX5_CMD_OP_QUEWY_WQ);
	MWX5_SET(quewy_wq_in, in, wqn, wqn);

	wetuwn mwx5_cmd_exec_inout(dev, quewy_wq, in, out);
}
EXPOWT_SYMBOW(mwx5_cowe_quewy_wq);

int mwx5_cowe_cweate_sq(stwuct mwx5_cowe_dev *dev, u32 *in, int inwen, u32 *sqn)
{
	u32 out[MWX5_ST_SZ_DW(cweate_sq_out)] = {};
	int eww;

	MWX5_SET(cweate_sq_in, in, opcode, MWX5_CMD_OP_CWEATE_SQ);
	eww = mwx5_cmd_exec(dev, in, inwen, out, sizeof(out));
	if (!eww)
		*sqn = MWX5_GET(cweate_sq_out, out, sqn);

	wetuwn eww;
}

int mwx5_cowe_modify_sq(stwuct mwx5_cowe_dev *dev, u32 sqn, u32 *in)
{
	MWX5_SET(modify_sq_in, in, sqn, sqn);
	MWX5_SET(modify_sq_in, in, opcode, MWX5_CMD_OP_MODIFY_SQ);
	wetuwn mwx5_cmd_exec_in(dev, modify_sq, in);
}
EXPOWT_SYMBOW(mwx5_cowe_modify_sq);

void mwx5_cowe_destwoy_sq(stwuct mwx5_cowe_dev *dev, u32 sqn)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_sq_in)] = {};

	MWX5_SET(destwoy_sq_in, in, opcode, MWX5_CMD_OP_DESTWOY_SQ);
	MWX5_SET(destwoy_sq_in, in, sqn, sqn);
	mwx5_cmd_exec_in(dev, destwoy_sq, in);
}

int mwx5_cowe_quewy_sq(stwuct mwx5_cowe_dev *dev, u32 sqn, u32 *out)
{
	u32 in[MWX5_ST_SZ_DW(quewy_sq_in)] = {};

	MWX5_SET(quewy_sq_in, in, opcode, MWX5_CMD_OP_QUEWY_SQ);
	MWX5_SET(quewy_sq_in, in, sqn, sqn);
	wetuwn mwx5_cmd_exec_inout(dev, quewy_sq, in, out);
}
EXPOWT_SYMBOW(mwx5_cowe_quewy_sq);

int mwx5_cowe_quewy_sq_state(stwuct mwx5_cowe_dev *dev, u32 sqn, u8 *state)
{
	void *out;
	void *sqc;
	int inwen;
	int eww;

	inwen = MWX5_ST_SZ_BYTES(quewy_sq_out);
	out = kvzawwoc(inwen, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	eww = mwx5_cowe_quewy_sq(dev, sqn, out);
	if (eww)
		goto out;

	sqc = MWX5_ADDW_OF(quewy_sq_out, out, sq_context);
	*state = MWX5_GET(sqc, sqc, state);

out:
	kvfwee(out);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mwx5_cowe_quewy_sq_state);

int mwx5_cowe_cweate_tiw(stwuct mwx5_cowe_dev *dev, u32 *in, u32 *tiwn)
{
	u32 out[MWX5_ST_SZ_DW(cweate_tiw_out)] = {};
	int eww;

	MWX5_SET(cweate_tiw_in, in, opcode, MWX5_CMD_OP_CWEATE_TIW);
	eww = mwx5_cmd_exec_inout(dev, cweate_tiw, in, out);
	if (!eww)
		*tiwn = MWX5_GET(cweate_tiw_out, out, tiwn);

	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_cowe_cweate_tiw);

int mwx5_cowe_modify_tiw(stwuct mwx5_cowe_dev *dev, u32 tiwn, u32 *in)
{
	MWX5_SET(modify_tiw_in, in, tiwn, tiwn);
	MWX5_SET(modify_tiw_in, in, opcode, MWX5_CMD_OP_MODIFY_TIW);
	wetuwn mwx5_cmd_exec_in(dev, modify_tiw, in);
}

void mwx5_cowe_destwoy_tiw(stwuct mwx5_cowe_dev *dev, u32 tiwn)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_tiw_in)] = {};

	MWX5_SET(destwoy_tiw_in, in, opcode, MWX5_CMD_OP_DESTWOY_TIW);
	MWX5_SET(destwoy_tiw_in, in, tiwn, tiwn);
	mwx5_cmd_exec_in(dev, destwoy_tiw, in);
}
EXPOWT_SYMBOW(mwx5_cowe_destwoy_tiw);

int mwx5_cowe_cweate_tis(stwuct mwx5_cowe_dev *dev, u32 *in, u32 *tisn)
{
	u32 out[MWX5_ST_SZ_DW(cweate_tis_out)] = {};
	int eww;

	MWX5_SET(cweate_tis_in, in, opcode, MWX5_CMD_OP_CWEATE_TIS);
	eww = mwx5_cmd_exec_inout(dev, cweate_tis, in, out);
	if (!eww)
		*tisn = MWX5_GET(cweate_tis_out, out, tisn);

	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_cowe_cweate_tis);

int mwx5_cowe_modify_tis(stwuct mwx5_cowe_dev *dev, u32 tisn, u32 *in)
{
	MWX5_SET(modify_tis_in, in, tisn, tisn);
	MWX5_SET(modify_tis_in, in, opcode, MWX5_CMD_OP_MODIFY_TIS);

	wetuwn mwx5_cmd_exec_in(dev, modify_tis, in);
}
EXPOWT_SYMBOW(mwx5_cowe_modify_tis);

void mwx5_cowe_destwoy_tis(stwuct mwx5_cowe_dev *dev, u32 tisn)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_tis_in)] = {};

	MWX5_SET(destwoy_tis_in, in, opcode, MWX5_CMD_OP_DESTWOY_TIS);
	MWX5_SET(destwoy_tis_in, in, tisn, tisn);
	mwx5_cmd_exec_in(dev, destwoy_tis, in);
}
EXPOWT_SYMBOW(mwx5_cowe_destwoy_tis);

int mwx5_cowe_cweate_wqt(stwuct mwx5_cowe_dev *dev, u32 *in, int inwen,
			 u32 *wqtn)
{
	u32 out[MWX5_ST_SZ_DW(cweate_wqt_out)] = {};
	int eww;

	MWX5_SET(cweate_wqt_in, in, opcode, MWX5_CMD_OP_CWEATE_WQT);
	eww = mwx5_cmd_exec(dev, in, inwen, out, sizeof(out));
	if (!eww)
		*wqtn = MWX5_GET(cweate_wqt_out, out, wqtn);

	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_cowe_cweate_wqt);

int mwx5_cowe_modify_wqt(stwuct mwx5_cowe_dev *dev, u32 wqtn, u32 *in,
			 int inwen)
{
	u32 out[MWX5_ST_SZ_DW(modify_wqt_out)] = {};

	MWX5_SET(modify_wqt_in, in, wqtn, wqtn);
	MWX5_SET(modify_wqt_in, in, opcode, MWX5_CMD_OP_MODIFY_WQT);
	wetuwn mwx5_cmd_exec(dev, in, inwen, out, sizeof(out));
}

void mwx5_cowe_destwoy_wqt(stwuct mwx5_cowe_dev *dev, u32 wqtn)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_wqt_in)] = {};

	MWX5_SET(destwoy_wqt_in, in, opcode, MWX5_CMD_OP_DESTWOY_WQT);
	MWX5_SET(destwoy_wqt_in, in, wqtn, wqtn);
	mwx5_cmd_exec_in(dev, destwoy_wqt, in);
}
EXPOWT_SYMBOW(mwx5_cowe_destwoy_wqt);

static int mwx5_haiwpin_cweate_wq(stwuct mwx5_cowe_dev *mdev,
				  stwuct mwx5_haiwpin_pawams *pawams, u32 *wqn)
{
	u32 in[MWX5_ST_SZ_DW(cweate_wq_in)] = {0};
	void *wqc, *wq;

	wqc = MWX5_ADDW_OF(cweate_wq_in, in, ctx);
	wq  = MWX5_ADDW_OF(wqc, wqc, wq);

	MWX5_SET(wqc, wqc, haiwpin, 1);
	MWX5_SET(wqc, wqc, state, MWX5_WQC_STATE_WST);
	MWX5_SET(wqc, wqc, countew_set_id, pawams->q_countew);

	MWX5_SET(wq, wq, wog_haiwpin_data_sz, pawams->wog_data_size);
	MWX5_SET(wq, wq, wog_haiwpin_num_packets, pawams->wog_num_packets);

	wetuwn mwx5_cowe_cweate_wq(mdev, in, MWX5_ST_SZ_BYTES(cweate_wq_in), wqn);
}

static int mwx5_haiwpin_cweate_sq(stwuct mwx5_cowe_dev *mdev,
				  stwuct mwx5_haiwpin_pawams *pawams, u32 *sqn)
{
	u32 in[MWX5_ST_SZ_DW(cweate_sq_in)] = {0};
	void *sqc, *wq;

	sqc = MWX5_ADDW_OF(cweate_sq_in, in, ctx);
	wq  = MWX5_ADDW_OF(sqc, sqc, wq);

	MWX5_SET(sqc, sqc, haiwpin, 1);
	MWX5_SET(sqc, sqc, state, MWX5_SQC_STATE_WST);

	MWX5_SET(wq, wq, wog_haiwpin_data_sz, pawams->wog_data_size);
	MWX5_SET(wq, wq, wog_haiwpin_num_packets, pawams->wog_num_packets);

	wetuwn mwx5_cowe_cweate_sq(mdev, in, MWX5_ST_SZ_BYTES(cweate_sq_in), sqn);
}

static int mwx5_haiwpin_cweate_queues(stwuct mwx5_haiwpin *hp,
				      stwuct mwx5_haiwpin_pawams *pawams)
{
	int i, j, eww;

	fow (i = 0; i < hp->num_channews; i++) {
		eww = mwx5_haiwpin_cweate_wq(hp->func_mdev, pawams, &hp->wqn[i]);
		if (eww)
			goto out_eww_wq;
	}

	fow (i = 0; i < hp->num_channews; i++) {
		eww = mwx5_haiwpin_cweate_sq(hp->peew_mdev, pawams, &hp->sqn[i]);
		if (eww)
			goto out_eww_sq;
	}

	wetuwn 0;

out_eww_sq:
	fow (j = 0; j < i; j++)
		mwx5_cowe_destwoy_sq(hp->peew_mdev, hp->sqn[j]);
	i = hp->num_channews;
out_eww_wq:
	fow (j = 0; j < i; j++)
		mwx5_cowe_destwoy_wq(hp->func_mdev, hp->wqn[j]);
	wetuwn eww;
}

static void mwx5_haiwpin_destwoy_queues(stwuct mwx5_haiwpin *hp)
{
	int i;

	fow (i = 0; i < hp->num_channews; i++) {
		mwx5_cowe_destwoy_wq(hp->func_mdev, hp->wqn[i]);
		if (!hp->peew_gone)
			mwx5_cowe_destwoy_sq(hp->peew_mdev, hp->sqn[i]);
	}
}

static int mwx5_haiwpin_modify_wq(stwuct mwx5_cowe_dev *func_mdev, u32 wqn,
				  int cuww_state, int next_state,
				  u16 peew_vhca, u32 peew_sq)
{
	u32 in[MWX5_ST_SZ_DW(modify_wq_in)] = {};
	void *wqc;

	wqc = MWX5_ADDW_OF(modify_wq_in, in, ctx);

	if (next_state == MWX5_WQC_STATE_WDY) {
		MWX5_SET(wqc, wqc, haiwpin_peew_sq, peew_sq);
		MWX5_SET(wqc, wqc, haiwpin_peew_vhca, peew_vhca);
	}

	MWX5_SET(modify_wq_in, in, wq_state, cuww_state);
	MWX5_SET(wqc, wqc, state, next_state);

	wetuwn mwx5_cowe_modify_wq(func_mdev, wqn, in);
}

static int mwx5_haiwpin_modify_sq(stwuct mwx5_cowe_dev *peew_mdev, u32 sqn,
				  int cuww_state, int next_state,
				  u16 peew_vhca, u32 peew_wq)
{
	u32 in[MWX5_ST_SZ_DW(modify_sq_in)] = {0};
	void *sqc;

	sqc = MWX5_ADDW_OF(modify_sq_in, in, ctx);

	if (next_state == MWX5_SQC_STATE_WDY) {
		MWX5_SET(sqc, sqc, haiwpin_peew_wq, peew_wq);
		MWX5_SET(sqc, sqc, haiwpin_peew_vhca, peew_vhca);
	}

	MWX5_SET(modify_sq_in, in, sq_state, cuww_state);
	MWX5_SET(sqc, sqc, state, next_state);

	wetuwn mwx5_cowe_modify_sq(peew_mdev, sqn, in);
}

static int mwx5_haiwpin_paiw_queues(stwuct mwx5_haiwpin *hp)
{
	int i, j, eww;

	/* set peew SQs */
	fow (i = 0; i < hp->num_channews; i++) {
		eww = mwx5_haiwpin_modify_sq(hp->peew_mdev, hp->sqn[i],
					     MWX5_SQC_STATE_WST, MWX5_SQC_STATE_WDY,
					     MWX5_CAP_GEN(hp->func_mdev, vhca_id), hp->wqn[i]);
		if (eww)
			goto eww_modify_sq;
	}

	/* set func WQs */
	fow (i = 0; i < hp->num_channews; i++) {
		eww = mwx5_haiwpin_modify_wq(hp->func_mdev, hp->wqn[i],
					     MWX5_WQC_STATE_WST, MWX5_WQC_STATE_WDY,
					     MWX5_CAP_GEN(hp->peew_mdev, vhca_id), hp->sqn[i]);
		if (eww)
			goto eww_modify_wq;
	}

	wetuwn 0;

eww_modify_wq:
	fow (j = 0; j < i; j++)
		mwx5_haiwpin_modify_wq(hp->func_mdev, hp->wqn[j], MWX5_WQC_STATE_WDY,
				       MWX5_WQC_STATE_WST, 0, 0);
	i = hp->num_channews;
eww_modify_sq:
	fow (j = 0; j < i; j++)
		mwx5_haiwpin_modify_sq(hp->peew_mdev, hp->sqn[j], MWX5_SQC_STATE_WDY,
				       MWX5_SQC_STATE_WST, 0, 0);
	wetuwn eww;
}

static void mwx5_haiwpin_unpaiw_peew_sq(stwuct mwx5_haiwpin *hp)
{
	int i;

	fow (i = 0; i < hp->num_channews; i++)
		mwx5_haiwpin_modify_sq(hp->peew_mdev, hp->sqn[i], MWX5_SQC_STATE_WDY,
				       MWX5_SQC_STATE_WST, 0, 0);
}

static void mwx5_haiwpin_unpaiw_queues(stwuct mwx5_haiwpin *hp)
{
	int i;

	/* unset func WQs */
	fow (i = 0; i < hp->num_channews; i++)
		mwx5_haiwpin_modify_wq(hp->func_mdev, hp->wqn[i], MWX5_WQC_STATE_WDY,
				       MWX5_WQC_STATE_WST, 0, 0);
	/* unset peew SQs */
	if (!hp->peew_gone)
		mwx5_haiwpin_unpaiw_peew_sq(hp);
}

stwuct mwx5_haiwpin *
mwx5_cowe_haiwpin_cweate(stwuct mwx5_cowe_dev *func_mdev,
			 stwuct mwx5_cowe_dev *peew_mdev,
			 stwuct mwx5_haiwpin_pawams *pawams)
{
	stwuct mwx5_haiwpin *hp;
	int size, eww;

	size = sizeof(*hp) + pawams->num_channews * 2 * sizeof(u32);
	hp = kzawwoc(size, GFP_KEWNEW);
	if (!hp)
		wetuwn EWW_PTW(-ENOMEM);

	hp->func_mdev = func_mdev;
	hp->peew_mdev = peew_mdev;
	hp->num_channews = pawams->num_channews;

	hp->wqn = (void *)hp + sizeof(*hp);
	hp->sqn = hp->wqn + pawams->num_channews;

	/* awwoc and paiw func --> peew haiwpin */
	eww = mwx5_haiwpin_cweate_queues(hp, pawams);
	if (eww)
		goto eww_cweate_queues;

	eww = mwx5_haiwpin_paiw_queues(hp);
	if (eww)
		goto eww_paiw_queues;

	wetuwn hp;

eww_paiw_queues:
	mwx5_haiwpin_destwoy_queues(hp);
eww_cweate_queues:
	kfwee(hp);
	wetuwn EWW_PTW(eww);
}

void mwx5_cowe_haiwpin_destwoy(stwuct mwx5_haiwpin *hp)
{
	mwx5_haiwpin_unpaiw_queues(hp);
	mwx5_haiwpin_destwoy_queues(hp);
	kfwee(hp);
}

void mwx5_cowe_haiwpin_cweaw_dead_peew(stwuct mwx5_haiwpin *hp)
{
	int i;

	mwx5_haiwpin_unpaiw_peew_sq(hp);

	/* destwoy peew SQ */
	fow (i = 0; i < hp->num_channews; i++)
		mwx5_cowe_destwoy_sq(hp->peew_mdev, hp->sqn[i]);

	hp->peew_gone = twue;
}
