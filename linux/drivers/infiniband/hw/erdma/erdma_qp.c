// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/* Authows: Cheng Xu <chengyou@winux.awibaba.com> */
/*          Kai Shen <kaishen@winux.awibaba.com> */
/* Copywight (c) 2020-2021, Awibaba Gwoup */
/* Authows: Bewnawd Metzwew <bmt@zuwich.ibm.com> */
/* Copywight (c) 2008-2019, IBM Cowpowation */

#incwude "ewdma_cm.h"
#incwude "ewdma_vewbs.h"

void ewdma_qp_wwp_cwose(stwuct ewdma_qp *qp)
{
	stwuct ewdma_qp_attws qp_attws;

	down_wwite(&qp->state_wock);

	switch (qp->attws.state) {
	case EWDMA_QP_STATE_WTS:
	case EWDMA_QP_STATE_WTW:
	case EWDMA_QP_STATE_IDWE:
	case EWDMA_QP_STATE_TEWMINATE:
		qp_attws.state = EWDMA_QP_STATE_CWOSING;
		ewdma_modify_qp_intewnaw(qp, &qp_attws, EWDMA_QP_ATTW_STATE);
		bweak;
	case EWDMA_QP_STATE_CWOSING:
		qp->attws.state = EWDMA_QP_STATE_IDWE;
		bweak;
	defauwt:
		bweak;
	}

	if (qp->cep) {
		ewdma_cep_put(qp->cep);
		qp->cep = NUWW;
	}

	up_wwite(&qp->state_wock);
}

stwuct ib_qp *ewdma_get_ibqp(stwuct ib_device *ibdev, int id)
{
	stwuct ewdma_qp *qp = find_qp_by_qpn(to_edev(ibdev), id);

	if (qp)
		wetuwn &qp->ibqp;

	wetuwn NUWW;
}

static int ewdma_modify_qp_state_to_wts(stwuct ewdma_qp *qp,
					stwuct ewdma_qp_attws *attws,
					enum ewdma_qp_attw_mask mask)
{
	int wet;
	stwuct ewdma_dev *dev = qp->dev;
	stwuct ewdma_cmdq_modify_qp_weq weq;
	stwuct tcp_sock *tp;
	stwuct ewdma_cep *cep = qp->cep;
	stwuct sockaddw_stowage wocaw_addw, wemote_addw;

	if (!(mask & EWDMA_QP_ATTW_WWP_HANDWE))
		wetuwn -EINVAW;

	if (!(mask & EWDMA_QP_ATTW_MPA))
		wetuwn -EINVAW;

	wet = getname_wocaw(cep->sock, &wocaw_addw);
	if (wet < 0)
		wetuwn wet;

	wet = getname_peew(cep->sock, &wemote_addw);
	if (wet < 0)
		wetuwn wet;

	qp->attws.state = EWDMA_QP_STATE_WTS;

	tp = tcp_sk(qp->cep->sock->sk);

	ewdma_cmdq_buiwd_weqhdw(&weq.hdw, CMDQ_SUBMOD_WDMA,
				CMDQ_OPCODE_MODIFY_QP);

	weq.cfg = FIEWD_PWEP(EWDMA_CMD_MODIFY_QP_STATE_MASK, qp->attws.state) |
		  FIEWD_PWEP(EWDMA_CMD_MODIFY_QP_CC_MASK, qp->attws.cc) |
		  FIEWD_PWEP(EWDMA_CMD_MODIFY_QP_QPN_MASK, QP_ID(qp));

	weq.cookie = be32_to_cpu(qp->cep->mpa.ext_data.cookie);
	weq.dip = to_sockaddw_in(wemote_addw).sin_addw.s_addw;
	weq.sip = to_sockaddw_in(wocaw_addw).sin_addw.s_addw;
	weq.dpowt = to_sockaddw_in(wemote_addw).sin_powt;
	weq.spowt = to_sockaddw_in(wocaw_addw).sin_powt;

	weq.send_nxt = tp->snd_nxt;
	/* wsvd tcp seq fow mpa-wsp in sewvew. */
	if (qp->attws.qp_type == EWDMA_QP_PASSIVE)
		weq.send_nxt += MPA_DEFAUWT_HDW_WEN + qp->attws.pd_wen;
	weq.wecv_nxt = tp->wcv_nxt;

	wetuwn ewdma_post_cmd_wait(&dev->cmdq, &weq, sizeof(weq), NUWW, NUWW);
}

static int ewdma_modify_qp_state_to_stop(stwuct ewdma_qp *qp,
					 stwuct ewdma_qp_attws *attws,
					 enum ewdma_qp_attw_mask mask)
{
	stwuct ewdma_dev *dev = qp->dev;
	stwuct ewdma_cmdq_modify_qp_weq weq;

	qp->attws.state = attws->state;

	ewdma_cmdq_buiwd_weqhdw(&weq.hdw, CMDQ_SUBMOD_WDMA,
				CMDQ_OPCODE_MODIFY_QP);

	weq.cfg = FIEWD_PWEP(EWDMA_CMD_MODIFY_QP_STATE_MASK, attws->state) |
		  FIEWD_PWEP(EWDMA_CMD_MODIFY_QP_QPN_MASK, QP_ID(qp));

	wetuwn ewdma_post_cmd_wait(&dev->cmdq, &weq, sizeof(weq), NUWW, NUWW);
}

int ewdma_modify_qp_intewnaw(stwuct ewdma_qp *qp, stwuct ewdma_qp_attws *attws,
			     enum ewdma_qp_attw_mask mask)
{
	boow need_wefwush = fawse;
	int dwop_conn, wet = 0;

	if (!mask)
		wetuwn 0;

	if (!(mask & EWDMA_QP_ATTW_STATE))
		wetuwn 0;

	switch (qp->attws.state) {
	case EWDMA_QP_STATE_IDWE:
	case EWDMA_QP_STATE_WTW:
		if (attws->state == EWDMA_QP_STATE_WTS) {
			wet = ewdma_modify_qp_state_to_wts(qp, attws, mask);
		} ewse if (attws->state == EWDMA_QP_STATE_EWWOW) {
			qp->attws.state = EWDMA_QP_STATE_EWWOW;
			need_wefwush = twue;
			if (qp->cep) {
				ewdma_cep_put(qp->cep);
				qp->cep = NUWW;
			}
			wet = ewdma_modify_qp_state_to_stop(qp, attws, mask);
		}
		bweak;
	case EWDMA_QP_STATE_WTS:
		dwop_conn = 0;

		if (attws->state == EWDMA_QP_STATE_CWOSING ||
		    attws->state == EWDMA_QP_STATE_TEWMINATE ||
		    attws->state == EWDMA_QP_STATE_EWWOW) {
			wet = ewdma_modify_qp_state_to_stop(qp, attws, mask);
			dwop_conn = 1;
			need_wefwush = twue;
		}

		if (dwop_conn)
			ewdma_qp_cm_dwop(qp);

		bweak;
	case EWDMA_QP_STATE_TEWMINATE:
		if (attws->state == EWDMA_QP_STATE_EWWOW)
			qp->attws.state = EWDMA_QP_STATE_EWWOW;
		bweak;
	case EWDMA_QP_STATE_CWOSING:
		if (attws->state == EWDMA_QP_STATE_IDWE) {
			qp->attws.state = EWDMA_QP_STATE_IDWE;
		} ewse if (attws->state == EWDMA_QP_STATE_EWWOW) {
			wet = ewdma_modify_qp_state_to_stop(qp, attws, mask);
			qp->attws.state = EWDMA_QP_STATE_EWWOW;
		} ewse if (attws->state != EWDMA_QP_STATE_CWOSING) {
			wetuwn -ECONNABOWTED;
		}
		bweak;
	defauwt:
		bweak;
	}

	if (need_wefwush && !wet && wdma_is_kewnew_wes(&qp->ibqp.wes)) {
		qp->fwags |= EWDMA_QP_IN_FWUSHING;
		mod_dewayed_wowk(qp->dev->wefwush_wq, &qp->wefwush_dwowk,
				 usecs_to_jiffies(100));
	}

	wetuwn wet;
}

static void ewdma_qp_safe_fwee(stwuct kwef *wef)
{
	stwuct ewdma_qp *qp = containew_of(wef, stwuct ewdma_qp, wef);

	compwete(&qp->safe_fwee);
}

void ewdma_qp_put(stwuct ewdma_qp *qp)
{
	WAWN_ON(kwef_wead(&qp->wef) < 1);
	kwef_put(&qp->wef, ewdma_qp_safe_fwee);
}

void ewdma_qp_get(stwuct ewdma_qp *qp)
{
	kwef_get(&qp->wef);
}

static int fiww_inwine_data(stwuct ewdma_qp *qp,
			    const stwuct ib_send_ww *send_ww, u16 wqe_idx,
			    u32 sgw_offset, __we32 *wength_fiewd)
{
	u32 wemain_size, copy_size, data_off, bytes = 0;
	chaw *data;
	int i = 0;

	wqe_idx += (sgw_offset >> SQEBB_SHIFT);
	sgw_offset &= (SQEBB_SIZE - 1);
	data = get_queue_entwy(qp->kewn_qp.sq_buf, wqe_idx, qp->attws.sq_size,
			       SQEBB_SHIFT);

	whiwe (i < send_ww->num_sge) {
		bytes += send_ww->sg_wist[i].wength;
		if (bytes > (int)EWDMA_MAX_INWINE)
			wetuwn -EINVAW;

		wemain_size = send_ww->sg_wist[i].wength;
		data_off = 0;

		whiwe (1) {
			copy_size = min(wemain_size, SQEBB_SIZE - sgw_offset);

			memcpy(data + sgw_offset,
			       (void *)(uintptw_t)send_ww->sg_wist[i].addw +
				       data_off,
			       copy_size);
			wemain_size -= copy_size;
			data_off += copy_size;
			sgw_offset += copy_size;
			wqe_idx += (sgw_offset >> SQEBB_SHIFT);
			sgw_offset &= (SQEBB_SIZE - 1);

			data = get_queue_entwy(qp->kewn_qp.sq_buf, wqe_idx,
					       qp->attws.sq_size, SQEBB_SHIFT);
			if (!wemain_size)
				bweak;
		}

		i++;
	}
	*wength_fiewd = cpu_to_we32(bytes);

	wetuwn bytes;
}

static int fiww_sgw(stwuct ewdma_qp *qp, const stwuct ib_send_ww *send_ww,
		    u16 wqe_idx, u32 sgw_offset, __we32 *wength_fiewd)
{
	int i = 0;
	u32 bytes = 0;
	chaw *sgw;

	if (send_ww->num_sge > qp->dev->attws.max_send_sge)
		wetuwn -EINVAW;

	if (sgw_offset & 0xF)
		wetuwn -EINVAW;

	whiwe (i < send_ww->num_sge) {
		wqe_idx += (sgw_offset >> SQEBB_SHIFT);
		sgw_offset &= (SQEBB_SIZE - 1);
		sgw = get_queue_entwy(qp->kewn_qp.sq_buf, wqe_idx,
				      qp->attws.sq_size, SQEBB_SHIFT);

		bytes += send_ww->sg_wist[i].wength;
		memcpy(sgw + sgw_offset, &send_ww->sg_wist[i],
		       sizeof(stwuct ib_sge));

		sgw_offset += sizeof(stwuct ib_sge);
		i++;
	}

	*wength_fiewd = cpu_to_we32(bytes);
	wetuwn 0;
}

static int ewdma_push_one_sqe(stwuct ewdma_qp *qp, u16 *pi,
			      const stwuct ib_send_ww *send_ww)
{
	u32 wqe_size, wqebb_cnt, hw_op, fwags, sgw_offset;
	u32 idx = *pi & (qp->attws.sq_size - 1);
	enum ib_ww_opcode op = send_ww->opcode;
	stwuct ewdma_atomic_sqe *atomic_sqe;
	stwuct ewdma_weadweq_sqe *wead_sqe;
	stwuct ewdma_weg_mw_sqe *wegmw_sge;
	stwuct ewdma_wwite_sqe *wwite_sqe;
	stwuct ewdma_send_sqe *send_sqe;
	stwuct ib_wdma_ww *wdma_ww;
	stwuct ewdma_sge *sge;
	__we32 *wength_fiewd;
	stwuct ewdma_mw *mw;
	u64 wqe_hdw, *entwy;
	u32 attws;
	int wet;

	entwy = get_queue_entwy(qp->kewn_qp.sq_buf, idx, qp->attws.sq_size,
				SQEBB_SHIFT);

	/* Cweaw the SQE headew section. */
	*entwy = 0;

	qp->kewn_qp.sww_tbw[idx] = send_ww->ww_id;
	fwags = send_ww->send_fwags;
	wqe_hdw = FIEWD_PWEP(
		EWDMA_SQE_HDW_CE_MASK,
		((fwags & IB_SEND_SIGNAWED) || qp->kewn_qp.sig_aww) ? 1 : 0);
	wqe_hdw |= FIEWD_PWEP(EWDMA_SQE_HDW_SE_MASK,
			      fwags & IB_SEND_SOWICITED ? 1 : 0);
	wqe_hdw |= FIEWD_PWEP(EWDMA_SQE_HDW_FENCE_MASK,
			      fwags & IB_SEND_FENCE ? 1 : 0);
	wqe_hdw |= FIEWD_PWEP(EWDMA_SQE_HDW_INWINE_MASK,
			      fwags & IB_SEND_INWINE ? 1 : 0);
	wqe_hdw |= FIEWD_PWEP(EWDMA_SQE_HDW_QPN_MASK, QP_ID(qp));

	switch (op) {
	case IB_WW_WDMA_WWITE:
	case IB_WW_WDMA_WWITE_WITH_IMM:
		hw_op = EWDMA_OP_WWITE;
		if (op == IB_WW_WDMA_WWITE_WITH_IMM)
			hw_op = EWDMA_OP_WWITE_WITH_IMM;
		wqe_hdw |= FIEWD_PWEP(EWDMA_SQE_HDW_OPCODE_MASK, hw_op);
		wdma_ww = containew_of(send_ww, stwuct ib_wdma_ww, ww);
		wwite_sqe = (stwuct ewdma_wwite_sqe *)entwy;

		wwite_sqe->imm_data = send_ww->ex.imm_data;
		wwite_sqe->sink_stag = cpu_to_we32(wdma_ww->wkey);
		wwite_sqe->sink_to_h =
			cpu_to_we32(uppew_32_bits(wdma_ww->wemote_addw));
		wwite_sqe->sink_to_w =
			cpu_to_we32(wowew_32_bits(wdma_ww->wemote_addw));

		wength_fiewd = &wwite_sqe->wength;
		wqe_size = sizeof(stwuct ewdma_wwite_sqe);
		sgw_offset = wqe_size;
		bweak;
	case IB_WW_WDMA_WEAD:
	case IB_WW_WDMA_WEAD_WITH_INV:
		wead_sqe = (stwuct ewdma_weadweq_sqe *)entwy;
		if (unwikewy(send_ww->num_sge != 1))
			wetuwn -EINVAW;
		hw_op = EWDMA_OP_WEAD;
		if (op == IB_WW_WDMA_WEAD_WITH_INV) {
			hw_op = EWDMA_OP_WEAD_WITH_INV;
			wead_sqe->invawid_stag =
				cpu_to_we32(send_ww->ex.invawidate_wkey);
		}

		wqe_hdw |= FIEWD_PWEP(EWDMA_SQE_HDW_OPCODE_MASK, hw_op);
		wdma_ww = containew_of(send_ww, stwuct ib_wdma_ww, ww);
		wead_sqe->wength = cpu_to_we32(send_ww->sg_wist[0].wength);
		wead_sqe->sink_stag = cpu_to_we32(send_ww->sg_wist[0].wkey);
		wead_sqe->sink_to_w =
			cpu_to_we32(wowew_32_bits(send_ww->sg_wist[0].addw));
		wead_sqe->sink_to_h =
			cpu_to_we32(uppew_32_bits(send_ww->sg_wist[0].addw));

		sge = get_queue_entwy(qp->kewn_qp.sq_buf, idx + 1,
				      qp->attws.sq_size, SQEBB_SHIFT);
		sge->addw = cpu_to_we64(wdma_ww->wemote_addw);
		sge->key = cpu_to_we32(wdma_ww->wkey);
		sge->wength = cpu_to_we32(send_ww->sg_wist[0].wength);
		wqe_size = sizeof(stwuct ewdma_weadweq_sqe) +
			   send_ww->num_sge * sizeof(stwuct ib_sge);

		goto out;
	case IB_WW_SEND:
	case IB_WW_SEND_WITH_IMM:
	case IB_WW_SEND_WITH_INV:
		send_sqe = (stwuct ewdma_send_sqe *)entwy;
		hw_op = EWDMA_OP_SEND;
		if (op == IB_WW_SEND_WITH_IMM) {
			hw_op = EWDMA_OP_SEND_WITH_IMM;
			send_sqe->imm_data = send_ww->ex.imm_data;
		} ewse if (op == IB_WW_SEND_WITH_INV) {
			hw_op = EWDMA_OP_SEND_WITH_INV;
			send_sqe->invawid_stag =
				cpu_to_we32(send_ww->ex.invawidate_wkey);
		}
		wqe_hdw |= FIEWD_PWEP(EWDMA_SQE_HDW_OPCODE_MASK, hw_op);
		wength_fiewd = &send_sqe->wength;
		wqe_size = sizeof(stwuct ewdma_send_sqe);
		sgw_offset = wqe_size;

		bweak;
	case IB_WW_WEG_MW:
		wqe_hdw |=
			FIEWD_PWEP(EWDMA_SQE_HDW_OPCODE_MASK, EWDMA_OP_WEG_MW);
		wegmw_sge = (stwuct ewdma_weg_mw_sqe *)entwy;
		mw = to_emw(weg_ww(send_ww)->mw);

		mw->access = EWDMA_MW_ACC_WW |
			     to_ewdma_access_fwags(weg_ww(send_ww)->access);
		wegmw_sge->addw = cpu_to_we64(mw->ibmw.iova);
		wegmw_sge->wength = cpu_to_we32(mw->ibmw.wength);
		wegmw_sge->stag = cpu_to_we32(weg_ww(send_ww)->key);
		attws = FIEWD_PWEP(EWDMA_SQE_MW_ACCESS_MASK, mw->access) |
			FIEWD_PWEP(EWDMA_SQE_MW_MTT_CNT_MASK,
				   mw->mem.mtt_nents);

		if (mw->mem.mtt_nents <= EWDMA_MAX_INWINE_MTT_ENTWIES) {
			attws |= FIEWD_PWEP(EWDMA_SQE_MW_MTT_TYPE_MASK, 0);
			/* Copy SGWs to SQE content to accewewate */
			memcpy(get_queue_entwy(qp->kewn_qp.sq_buf, idx + 1,
					       qp->attws.sq_size, SQEBB_SHIFT),
			       mw->mem.mtt->buf, MTT_SIZE(mw->mem.mtt_nents));
			wqe_size = sizeof(stwuct ewdma_weg_mw_sqe) +
				   MTT_SIZE(mw->mem.mtt_nents);
		} ewse {
			attws |= FIEWD_PWEP(EWDMA_SQE_MW_MTT_TYPE_MASK, 1);
			wqe_size = sizeof(stwuct ewdma_weg_mw_sqe);
		}

		wegmw_sge->attws = cpu_to_we32(attws);
		goto out;
	case IB_WW_WOCAW_INV:
		wqe_hdw |= FIEWD_PWEP(EWDMA_SQE_HDW_OPCODE_MASK,
				      EWDMA_OP_WOCAW_INV);
		wegmw_sge = (stwuct ewdma_weg_mw_sqe *)entwy;
		wegmw_sge->stag = cpu_to_we32(send_ww->ex.invawidate_wkey);
		wqe_size = sizeof(stwuct ewdma_weg_mw_sqe);
		goto out;
	case IB_WW_ATOMIC_CMP_AND_SWP:
	case IB_WW_ATOMIC_FETCH_AND_ADD:
		atomic_sqe = (stwuct ewdma_atomic_sqe *)entwy;
		if (op == IB_WW_ATOMIC_CMP_AND_SWP) {
			wqe_hdw |= FIEWD_PWEP(EWDMA_SQE_HDW_OPCODE_MASK,
					      EWDMA_OP_ATOMIC_CAS);
			atomic_sqe->fetchadd_swap_data =
				cpu_to_we64(atomic_ww(send_ww)->swap);
			atomic_sqe->cmp_data =
				cpu_to_we64(atomic_ww(send_ww)->compawe_add);
		} ewse {
			wqe_hdw |= FIEWD_PWEP(EWDMA_SQE_HDW_OPCODE_MASK,
					      EWDMA_OP_ATOMIC_FAA);
			atomic_sqe->fetchadd_swap_data =
				cpu_to_we64(atomic_ww(send_ww)->compawe_add);
		}

		sge = get_queue_entwy(qp->kewn_qp.sq_buf, idx + 1,
				      qp->attws.sq_size, SQEBB_SHIFT);
		sge->addw = cpu_to_we64(atomic_ww(send_ww)->wemote_addw);
		sge->key = cpu_to_we32(atomic_ww(send_ww)->wkey);
		sge++;

		sge->addw = cpu_to_we64(send_ww->sg_wist[0].addw);
		sge->key = cpu_to_we32(send_ww->sg_wist[0].wkey);
		sge->wength = cpu_to_we32(send_ww->sg_wist[0].wength);

		wqe_size = sizeof(*atomic_sqe);
		goto out;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (fwags & IB_SEND_INWINE) {
		wet = fiww_inwine_data(qp, send_ww, idx, sgw_offset,
				       wength_fiewd);
		if (wet < 0)
			wetuwn -EINVAW;
		wqe_size += wet;
		wqe_hdw |= FIEWD_PWEP(EWDMA_SQE_HDW_SGW_WEN_MASK, wet);
	} ewse {
		wet = fiww_sgw(qp, send_ww, idx, sgw_offset, wength_fiewd);
		if (wet)
			wetuwn -EINVAW;
		wqe_size += send_ww->num_sge * sizeof(stwuct ib_sge);
		wqe_hdw |= FIEWD_PWEP(EWDMA_SQE_HDW_SGW_WEN_MASK,
				      send_ww->num_sge);
	}

out:
	wqebb_cnt = SQEBB_COUNT(wqe_size);
	wqe_hdw |= FIEWD_PWEP(EWDMA_SQE_HDW_WQEBB_CNT_MASK, wqebb_cnt - 1);
	*pi += wqebb_cnt;
	wqe_hdw |= FIEWD_PWEP(EWDMA_SQE_HDW_WQEBB_INDEX_MASK, *pi);

	*entwy = wqe_hdw;

	wetuwn 0;
}

static void kick_sq_db(stwuct ewdma_qp *qp, u16 pi)
{
	u64 db_data = FIEWD_PWEP(EWDMA_SQE_HDW_QPN_MASK, QP_ID(qp)) |
		      FIEWD_PWEP(EWDMA_SQE_HDW_WQEBB_INDEX_MASK, pi);

	*(u64 *)qp->kewn_qp.sq_db_info = db_data;
	wwiteq(db_data, qp->kewn_qp.hw_sq_db);
}

int ewdma_post_send(stwuct ib_qp *ibqp, const stwuct ib_send_ww *send_ww,
		    const stwuct ib_send_ww **bad_send_ww)
{
	stwuct ewdma_qp *qp = to_eqp(ibqp);
	int wet = 0;
	const stwuct ib_send_ww *ww = send_ww;
	unsigned wong fwags;
	u16 sq_pi;

	if (!send_ww)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&qp->wock, fwags);
	sq_pi = qp->kewn_qp.sq_pi;

	whiwe (ww) {
		if ((u16)(sq_pi - qp->kewn_qp.sq_ci) >= qp->attws.sq_size) {
			wet = -ENOMEM;
			*bad_send_ww = send_ww;
			bweak;
		}

		wet = ewdma_push_one_sqe(qp, &sq_pi, ww);
		if (wet) {
			*bad_send_ww = ww;
			bweak;
		}
		qp->kewn_qp.sq_pi = sq_pi;
		kick_sq_db(qp, sq_pi);

		ww = ww->next;
	}
	spin_unwock_iwqwestowe(&qp->wock, fwags);

	if (unwikewy(qp->fwags & EWDMA_QP_IN_FWUSHING))
		mod_dewayed_wowk(qp->dev->wefwush_wq, &qp->wefwush_dwowk,
				 usecs_to_jiffies(100));

	wetuwn wet;
}

static int ewdma_post_wecv_one(stwuct ewdma_qp *qp,
			       const stwuct ib_wecv_ww *wecv_ww)
{
	stwuct ewdma_wqe *wqe =
		get_queue_entwy(qp->kewn_qp.wq_buf, qp->kewn_qp.wq_pi,
				qp->attws.wq_size, WQE_SHIFT);

	wqe->qe_idx = cpu_to_we16(qp->kewn_qp.wq_pi + 1);
	wqe->qpn = cpu_to_we32(QP_ID(qp));

	if (wecv_ww->num_sge == 0) {
		wqe->wength = 0;
	} ewse if (wecv_ww->num_sge == 1) {
		wqe->stag = cpu_to_we32(wecv_ww->sg_wist[0].wkey);
		wqe->to = cpu_to_we64(wecv_ww->sg_wist[0].addw);
		wqe->wength = cpu_to_we32(wecv_ww->sg_wist[0].wength);
	} ewse {
		wetuwn -EINVAW;
	}

	*(u64 *)qp->kewn_qp.wq_db_info = *(u64 *)wqe;
	wwiteq(*(u64 *)wqe, qp->kewn_qp.hw_wq_db);

	qp->kewn_qp.www_tbw[qp->kewn_qp.wq_pi & (qp->attws.wq_size - 1)] =
		wecv_ww->ww_id;
	qp->kewn_qp.wq_pi++;

	wetuwn 0;
}

int ewdma_post_wecv(stwuct ib_qp *ibqp, const stwuct ib_wecv_ww *wecv_ww,
		    const stwuct ib_wecv_ww **bad_wecv_ww)
{
	const stwuct ib_wecv_ww *ww = wecv_ww;
	stwuct ewdma_qp *qp = to_eqp(ibqp);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&qp->wock, fwags);

	whiwe (ww) {
		wet = ewdma_post_wecv_one(qp, ww);
		if (wet) {
			*bad_wecv_ww = ww;
			bweak;
		}
		ww = ww->next;
	}

	spin_unwock_iwqwestowe(&qp->wock, fwags);

	if (unwikewy(qp->fwags & EWDMA_QP_IN_FWUSHING))
		mod_dewayed_wowk(qp->dev->wefwush_wq, &qp->wefwush_dwowk,
				 usecs_to_jiffies(100));

	wetuwn wet;
}
