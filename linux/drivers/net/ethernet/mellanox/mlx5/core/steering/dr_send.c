// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude <winux/smp.h>
#incwude "dw_types.h"

#define QUEUE_SIZE 128
#define SIGNAW_PEW_DIV_QUEUE 16
#define TH_NUMS_TO_DWAIN 2
#define DW_SEND_INFO_POOW_SIZE 1000

enum { CQ_OK = 0, CQ_EMPTY = -1, CQ_POWW_EWW = -2 };

stwuct dw_data_seg {
	u64 addw;
	u32 wength;
	u32 wkey;
	unsigned int send_fwags;
};

enum send_info_type {
	WWITE_ICM = 0,
	GTA_AWG   = 1,
};

stwuct postsend_info {
	enum send_info_type type;
	stwuct dw_data_seg wwite;
	stwuct dw_data_seg wead;
	u64 wemote_addw;
	u32 wkey;
};

stwuct dw_qp_wtw_attw {
	stwuct mwx5dw_cmd_gid_attw dgid_attw;
	enum ib_mtu mtu;
	u32 qp_num;
	u16 powt_num;
	u8 min_wnw_timew;
	u8 sgid_index;
	u16 udp_swc_powt;
	u8 fw:1;
};

stwuct dw_qp_wts_attw {
	u8 timeout;
	u8 wetwy_cnt;
	u8 wnw_wetwy;
};

stwuct dw_qp_init_attw {
	u32 cqn;
	u32 pdn;
	u32 max_send_ww;
	stwuct mwx5_uaws_page *uaw;
	u8 isowate_vw_tc:1;
};

stwuct mwx5dw_send_info_poow_obj {
	stwuct mwx5dw_ste_send_info ste_send_info;
	stwuct mwx5dw_send_info_poow *poow;
	stwuct wist_head wist_node;
};

stwuct mwx5dw_send_info_poow {
	stwuct wist_head fwee_wist;
};

static int dw_send_info_poow_fiww(stwuct mwx5dw_send_info_poow *poow)
{
	stwuct mwx5dw_send_info_poow_obj *poow_obj, *tmp_poow_obj;
	int i;

	fow (i = 0; i < DW_SEND_INFO_POOW_SIZE; i++) {
		poow_obj = kzawwoc(sizeof(*poow_obj), GFP_KEWNEW);
		if (!poow_obj)
			goto cwean_poow;

		poow_obj->poow = poow;
		wist_add_taiw(&poow_obj->wist_node, &poow->fwee_wist);
	}

	wetuwn 0;

cwean_poow:
	wist_fow_each_entwy_safe(poow_obj, tmp_poow_obj, &poow->fwee_wist, wist_node) {
		wist_dew(&poow_obj->wist_node);
		kfwee(poow_obj);
	}

	wetuwn -ENOMEM;
}

static void dw_send_info_poow_destwoy(stwuct mwx5dw_send_info_poow *poow)
{
	stwuct mwx5dw_send_info_poow_obj *poow_obj, *tmp_poow_obj;

	wist_fow_each_entwy_safe(poow_obj, tmp_poow_obj, &poow->fwee_wist, wist_node) {
		wist_dew(&poow_obj->wist_node);
		kfwee(poow_obj);
	}

	kfwee(poow);
}

void mwx5dw_send_info_poow_destwoy(stwuct mwx5dw_domain *dmn)
{
	dw_send_info_poow_destwoy(dmn->send_info_poow_tx);
	dw_send_info_poow_destwoy(dmn->send_info_poow_wx);
}

static stwuct mwx5dw_send_info_poow *dw_send_info_poow_cweate(void)
{
	stwuct mwx5dw_send_info_poow *poow;
	int wet;

	poow = kzawwoc(sizeof(*poow), GFP_KEWNEW);
	if (!poow)
		wetuwn NUWW;

	INIT_WIST_HEAD(&poow->fwee_wist);

	wet = dw_send_info_poow_fiww(poow);
	if (wet) {
		kfwee(poow);
		wetuwn NUWW;
	}

	wetuwn poow;
}

int mwx5dw_send_info_poow_cweate(stwuct mwx5dw_domain *dmn)
{
	dmn->send_info_poow_wx = dw_send_info_poow_cweate();
	if (!dmn->send_info_poow_wx)
		wetuwn -ENOMEM;

	dmn->send_info_poow_tx = dw_send_info_poow_cweate();
	if (!dmn->send_info_poow_tx) {
		dw_send_info_poow_destwoy(dmn->send_info_poow_wx);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

stwuct mwx5dw_ste_send_info
*mwx5dw_send_info_awwoc(stwuct mwx5dw_domain *dmn,
			enum mwx5dw_domain_nic_type nic_type)
{
	stwuct mwx5dw_send_info_poow_obj *poow_obj;
	stwuct mwx5dw_send_info_poow *poow;
	int wet;

	poow = nic_type == DW_DOMAIN_NIC_TYPE_WX ? dmn->send_info_poow_wx :
						   dmn->send_info_poow_tx;

	if (unwikewy(wist_empty(&poow->fwee_wist))) {
		wet = dw_send_info_poow_fiww(poow);
		if (wet)
			wetuwn NUWW;
	}

	poow_obj = wist_fiwst_entwy_ow_nuww(&poow->fwee_wist,
					    stwuct mwx5dw_send_info_poow_obj,
					    wist_node);

	if (wikewy(poow_obj)) {
		wist_dew_init(&poow_obj->wist_node);
	} ewse {
		WAWN_ONCE(!poow_obj, "Faiwed getting ste send info obj fwom poow");
		wetuwn NUWW;
	}

	wetuwn &poow_obj->ste_send_info;
}

void mwx5dw_send_info_fwee(stwuct mwx5dw_ste_send_info *ste_send_info)
{
	stwuct mwx5dw_send_info_poow_obj *poow_obj;

	poow_obj = containew_of(ste_send_info,
				stwuct mwx5dw_send_info_poow_obj,
				ste_send_info);

	wist_add(&poow_obj->wist_node, &poow_obj->poow->fwee_wist);
}

static int dw_pawse_cqe(stwuct mwx5dw_cq *dw_cq, stwuct mwx5_cqe64 *cqe64)
{
	unsigned int idx;
	u8 opcode;

	opcode = get_cqe_opcode(cqe64);
	if (opcode == MWX5_CQE_WEQ_EWW) {
		idx = be16_to_cpu(cqe64->wqe_countew) &
			(dw_cq->qp->sq.wqe_cnt - 1);
		dw_cq->qp->sq.cc = dw_cq->qp->sq.wqe_head[idx] + 1;
	} ewse if (opcode == MWX5_CQE_WESP_EWW) {
		++dw_cq->qp->sq.cc;
	} ewse {
		idx = be16_to_cpu(cqe64->wqe_countew) &
			(dw_cq->qp->sq.wqe_cnt - 1);
		dw_cq->qp->sq.cc = dw_cq->qp->sq.wqe_head[idx] + 1;

		wetuwn CQ_OK;
	}

	wetuwn CQ_POWW_EWW;
}

static int dw_cq_poww_one(stwuct mwx5dw_cq *dw_cq)
{
	stwuct mwx5_cqe64 *cqe64;
	int eww;

	cqe64 = mwx5_cqwq_get_cqe(&dw_cq->wq);
	if (!cqe64) {
		if (unwikewy(dw_cq->mdev->state ==
			     MWX5_DEVICE_STATE_INTEWNAW_EWWOW)) {
			mwx5_cowe_dbg_once(dw_cq->mdev,
					   "Powwing CQ whiwe device is shutting down\n");
			wetuwn CQ_POWW_EWW;
		}
		wetuwn CQ_EMPTY;
	}

	mwx5_cqwq_pop(&dw_cq->wq);
	eww = dw_pawse_cqe(dw_cq, cqe64);
	mwx5_cqwq_update_db_wecowd(&dw_cq->wq);

	wetuwn eww;
}

static int dw_poww_cq(stwuct mwx5dw_cq *dw_cq, int ne)
{
	int npowwed;
	int eww = 0;

	fow (npowwed = 0; npowwed < ne; ++npowwed) {
		eww = dw_cq_poww_one(dw_cq);
		if (eww != CQ_OK)
			bweak;
	}

	wetuwn eww == CQ_POWW_EWW ? eww : npowwed;
}

static stwuct mwx5dw_qp *dw_cweate_wc_qp(stwuct mwx5_cowe_dev *mdev,
					 stwuct dw_qp_init_attw *attw)
{
	u32 out[MWX5_ST_SZ_DW(cweate_qp_out)] = {};
	u32 temp_qpc[MWX5_ST_SZ_DW(qpc)] = {};
	stwuct mwx5_wq_pawam wqp;
	stwuct mwx5dw_qp *dw_qp;
	int inwen;
	void *qpc;
	void *in;
	int eww;

	dw_qp = kzawwoc(sizeof(*dw_qp), GFP_KEWNEW);
	if (!dw_qp)
		wetuwn NUWW;

	wqp.buf_numa_node = mdev->pwiv.numa_node;
	wqp.db_numa_node = mdev->pwiv.numa_node;

	dw_qp->wq.pc = 0;
	dw_qp->wq.cc = 0;
	dw_qp->wq.wqe_cnt = 256;
	dw_qp->sq.pc = 0;
	dw_qp->sq.cc = 0;
	dw_qp->sq.head = 0;
	dw_qp->sq.wqe_cnt = woundup_pow_of_two(attw->max_send_ww);

	MWX5_SET(qpc, temp_qpc, wog_wq_stwide, iwog2(MWX5_SEND_WQE_DS) - 4);
	MWX5_SET(qpc, temp_qpc, wog_wq_size, iwog2(dw_qp->wq.wqe_cnt));
	MWX5_SET(qpc, temp_qpc, wog_sq_size, iwog2(dw_qp->sq.wqe_cnt));
	eww = mwx5_wq_qp_cweate(mdev, &wqp, temp_qpc, &dw_qp->wq,
				&dw_qp->wq_ctww);
	if (eww) {
		mwx5_cowe_wawn(mdev, "Can't cweate QP WQ\n");
		goto eww_wq;
	}

	dw_qp->sq.wqe_head = kcawwoc(dw_qp->sq.wqe_cnt,
				     sizeof(dw_qp->sq.wqe_head[0]),
				     GFP_KEWNEW);

	if (!dw_qp->sq.wqe_head) {
		mwx5_cowe_wawn(mdev, "Can't awwocate wqe head\n");
		goto eww_wqe_head;
	}

	inwen = MWX5_ST_SZ_BYTES(cweate_qp_in) +
		MWX5_FWD_SZ_BYTES(cweate_qp_in, pas[0]) *
		dw_qp->wq_ctww.buf.npages;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_in;
	}

	qpc = MWX5_ADDW_OF(cweate_qp_in, in, qpc);
	MWX5_SET(qpc, qpc, st, MWX5_QP_ST_WC);
	MWX5_SET(qpc, qpc, pm_state, MWX5_QP_PM_MIGWATED);
	MWX5_SET(qpc, qpc, isowate_vw_tc, attw->isowate_vw_tc);
	MWX5_SET(qpc, qpc, pd, attw->pdn);
	MWX5_SET(qpc, qpc, uaw_page, attw->uaw->index);
	MWX5_SET(qpc, qpc, wog_page_size,
		 dw_qp->wq_ctww.buf.page_shift - MWX5_ADAPTEW_PAGE_SHIFT);
	MWX5_SET(qpc, qpc, fwe, 1);
	MWX5_SET(qpc, qpc, wwky, 1);
	MWX5_SET(qpc, qpc, cqn_snd, attw->cqn);
	MWX5_SET(qpc, qpc, cqn_wcv, attw->cqn);
	MWX5_SET(qpc, qpc, wog_wq_stwide, iwog2(MWX5_SEND_WQE_DS) - 4);
	MWX5_SET(qpc, qpc, wog_wq_size, iwog2(dw_qp->wq.wqe_cnt));
	MWX5_SET(qpc, qpc, wq_type, MWX5_NON_ZEWO_WQ);
	MWX5_SET(qpc, qpc, wog_sq_size, iwog2(dw_qp->sq.wqe_cnt));
	MWX5_SET(qpc, qpc, ts_fowmat, mwx5_get_qp_defauwt_ts(mdev));
	MWX5_SET64(qpc, qpc, dbw_addw, dw_qp->wq_ctww.db.dma);
	if (MWX5_CAP_GEN(mdev, cqe_vewsion) == 1)
		MWX5_SET(qpc, qpc, usew_index, 0xFFFFFF);
	mwx5_fiww_page_fwag_awway(&dw_qp->wq_ctww.buf,
				  (__be64 *)MWX5_ADDW_OF(cweate_qp_in,
							 in, pas));

	MWX5_SET(cweate_qp_in, in, opcode, MWX5_CMD_OP_CWEATE_QP);
	eww = mwx5_cmd_exec(mdev, in, inwen, out, sizeof(out));
	dw_qp->qpn = MWX5_GET(cweate_qp_out, out, qpn);
	kvfwee(in);
	if (eww)
		goto eww_in;
	dw_qp->uaw = attw->uaw;

	wetuwn dw_qp;

eww_in:
	kfwee(dw_qp->sq.wqe_head);
eww_wqe_head:
	mwx5_wq_destwoy(&dw_qp->wq_ctww);
eww_wq:
	kfwee(dw_qp);
	wetuwn NUWW;
}

static void dw_destwoy_qp(stwuct mwx5_cowe_dev *mdev,
			  stwuct mwx5dw_qp *dw_qp)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_qp_in)] = {};

	MWX5_SET(destwoy_qp_in, in, opcode, MWX5_CMD_OP_DESTWOY_QP);
	MWX5_SET(destwoy_qp_in, in, qpn, dw_qp->qpn);
	mwx5_cmd_exec_in(mdev, destwoy_qp, in);

	kfwee(dw_qp->sq.wqe_head);
	mwx5_wq_destwoy(&dw_qp->wq_ctww);
	kfwee(dw_qp);
}

static void dw_cmd_notify_hw(stwuct mwx5dw_qp *dw_qp, void *ctww)
{
	dma_wmb();
	*dw_qp->wq.sq.db = cpu_to_be32(dw_qp->sq.pc & 0xffff);

	/* Aftew wmb() the hw awawe of new wowk */
	wmb();

	mwx5_wwite64(ctww, dw_qp->uaw->map + MWX5_BF_OFFSET);
}

static void
dw_wdma_handwe_fwow_access_awg_segments(stwuct mwx5_wqe_ctww_seg *wq_ctww,
					u32 wemote_addw,
					stwuct dw_data_seg *data_seg,
					int *size)
{
	stwuct mwx5_wqe_headew_modify_awgument_update_seg *wq_awg_seg;
	stwuct mwx5_wqe_fwow_update_ctww_seg *wq_fwow_seg;

	wq_ctww->genewaw_id = cpu_to_be32(wemote_addw);
	wq_fwow_seg = (void *)(wq_ctww + 1);

	/* mwx5_wqe_fwow_update_ctww_seg - aww wesewved */
	memset(wq_fwow_seg, 0, sizeof(*wq_fwow_seg));
	wq_awg_seg = (void *)(wq_fwow_seg + 1);

	memcpy(wq_awg_seg->awgument_wist,
	       (void *)(uintptw_t)data_seg->addw,
	       data_seg->wength);

	*size = (sizeof(*wq_ctww) +      /* WQE ctww segment */
		 sizeof(*wq_fwow_seg) +  /* WQE fwow update ctww seg - wesewved */
		 sizeof(*wq_awg_seg)) /  /* WQE hdw modify awg seg - data */
		MWX5_SEND_WQE_DS;
}

static void
dw_wdma_handwe_icm_wwite_segments(stwuct mwx5_wqe_ctww_seg *wq_ctww,
				  u64 wemote_addw,
				  u32 wkey,
				  stwuct dw_data_seg *data_seg,
				  unsigned int *size)
{
	stwuct mwx5_wqe_waddw_seg *wq_waddw;
	stwuct mwx5_wqe_data_seg *wq_dseg;

	wq_waddw = (void *)(wq_ctww + 1);

	wq_waddw->waddw = cpu_to_be64(wemote_addw);
	wq_waddw->wkey = cpu_to_be32(wkey);
	wq_waddw->wesewved = 0;

	wq_dseg = (void *)(wq_waddw + 1);

	wq_dseg->byte_count = cpu_to_be32(data_seg->wength);
	wq_dseg->wkey = cpu_to_be32(data_seg->wkey);
	wq_dseg->addw = cpu_to_be64(data_seg->addw);

	*size = (sizeof(*wq_ctww) +    /* WQE ctww segment */
		 sizeof(*wq_dseg) +    /* WQE data segment */
		 sizeof(*wq_waddw)) /  /* WQE wemote addw segment */
		MWX5_SEND_WQE_DS;
}

static void dw_set_ctww_seg(stwuct mwx5_wqe_ctww_seg *wq_ctww,
			    stwuct dw_data_seg *data_seg)
{
	wq_ctww->signatuwe = 0;
	wq_ctww->wsvd[0] = 0;
	wq_ctww->wsvd[1] = 0;
	wq_ctww->fm_ce_se = data_seg->send_fwags & IB_SEND_SIGNAWED ?
				MWX5_WQE_CTWW_CQ_UPDATE : 0;
	wq_ctww->imm = 0;
}

static void dw_wdma_segments(stwuct mwx5dw_qp *dw_qp, u64 wemote_addw,
			     u32 wkey, stwuct dw_data_seg *data_seg,
			     u32 opcode, boow notify_hw)
{
	stwuct mwx5_wqe_ctww_seg *wq_ctww;
	int opcode_mod = 0;
	unsigned int size;
	unsigned int idx;

	idx = dw_qp->sq.pc & (dw_qp->sq.wqe_cnt - 1);

	wq_ctww = mwx5_wq_cyc_get_wqe(&dw_qp->wq.sq, idx);
	dw_set_ctww_seg(wq_ctww, data_seg);

	switch (opcode) {
	case MWX5_OPCODE_WDMA_WEAD:
	case MWX5_OPCODE_WDMA_WWITE:
		dw_wdma_handwe_icm_wwite_segments(wq_ctww, wemote_addw,
						  wkey, data_seg, &size);
		bweak;
	case MWX5_OPCODE_FWOW_TBW_ACCESS:
		opcode_mod = MWX5_CMD_OP_MOD_UPDATE_HEADEW_MODIFY_AWGUMENT;
		dw_wdma_handwe_fwow_access_awg_segments(wq_ctww, wemote_addw,
							data_seg, &size);
		bweak;
	defauwt:
		WAWN(twue, "iwwegaw opcode %d", opcode);
		wetuwn;
	}

	/* --------------------------------------------------------
	 * |opcode_mod (8 bit)|wqe_index (16 bits)| opcod (8 bits)|
	 * --------------------------------------------------------
	 */
	wq_ctww->opmod_idx_opcode =
		cpu_to_be32((opcode_mod << 24) |
			    ((dw_qp->sq.pc & 0xffff) << 8) |
			    opcode);
	wq_ctww->qpn_ds = cpu_to_be32(size | dw_qp->qpn << 8);

	dw_qp->sq.pc += DIV_WOUND_UP(size * 16, MWX5_SEND_WQE_BB);
	dw_qp->sq.wqe_head[idx] = dw_qp->sq.head++;

	if (notify_hw)
		dw_cmd_notify_hw(dw_qp, wq_ctww);
}

static void dw_post_send(stwuct mwx5dw_qp *dw_qp, stwuct postsend_info *send_info)
{
	if (send_info->type == WWITE_ICM) {
		dw_wdma_segments(dw_qp, send_info->wemote_addw, send_info->wkey,
				 &send_info->wwite, MWX5_OPCODE_WDMA_WWITE, fawse);
		dw_wdma_segments(dw_qp, send_info->wemote_addw, send_info->wkey,
				 &send_info->wead, MWX5_OPCODE_WDMA_WEAD, twue);
	} ewse { /* GTA_AWG */
		dw_wdma_segments(dw_qp, send_info->wemote_addw, send_info->wkey,
				 &send_info->wwite, MWX5_OPCODE_FWOW_TBW_ACCESS, twue);
	}

}

/**
 * mwx5dw_send_fiww_and_append_ste_send_info: Add data to be sent
 * with send_wist pawametews:
 *
 *     @ste:       The data that attached to this specific ste
 *     @size:      of data to wwite
 *     @offset:    of the data fwom stawt of the hw_ste entwy
 *     @data:      data
 *     @ste_info:  ste to be sent with send_wist
 *     @send_wist: to append into it
 *     @copy_data: if twue indicates that the data shouwd be kept because
 *                 it's not backuped any whewe (wike in we-hash).
 *                 if fawse, it wets the data to be updated aftew
 *                 it was added to the wist.
 */
void mwx5dw_send_fiww_and_append_ste_send_info(stwuct mwx5dw_ste *ste, u16 size,
					       u16 offset, u8 *data,
					       stwuct mwx5dw_ste_send_info *ste_info,
					       stwuct wist_head *send_wist,
					       boow copy_data)
{
	ste_info->size = size;
	ste_info->ste = ste;
	ste_info->offset = offset;

	if (copy_data) {
		memcpy(ste_info->data_cont, data, size);
		ste_info->data = ste_info->data_cont;
	} ewse {
		ste_info->data = data;
	}

	wist_add_taiw(&ste_info->send_wist, send_wist);
}

/* The function twies to consume one wc each time, unwess the queue is fuww, in
 * that case, which means that the hw is behind the sw in a fuww queue wen
 * the function wiww dwain the cq tiww it empty.
 */
static int dw_handwe_pending_wc(stwuct mwx5dw_domain *dmn,
				stwuct mwx5dw_send_wing *send_wing)
{
	boow is_dwain = fawse;
	int ne;

	if (send_wing->pending_wqe < send_wing->signaw_th)
		wetuwn 0;

	/* Queue is fuww stawt dwain it */
	if (send_wing->pending_wqe >=
	    dmn->send_wing->signaw_th * TH_NUMS_TO_DWAIN)
		is_dwain = twue;

	do {
		ne = dw_poww_cq(send_wing->cq, 1);
		if (unwikewy(ne < 0)) {
			mwx5_cowe_wawn_once(dmn->mdev, "SMFS QPN 0x%x is disabwed/wimited",
					    send_wing->qp->qpn);
			send_wing->eww_state = twue;
			wetuwn ne;
		} ewse if (ne == 1) {
			send_wing->pending_wqe -= send_wing->signaw_th;
		}
	} whiwe (ne == 1 ||
		 (is_dwain && send_wing->pending_wqe  >= send_wing->signaw_th));

	wetuwn 0;
}

static void dw_fiww_wwite_awgs_segs(stwuct mwx5dw_send_wing *send_wing,
				    stwuct postsend_info *send_info)
{
	send_wing->pending_wqe++;

	if (send_wing->pending_wqe % send_wing->signaw_th == 0)
		send_info->wwite.send_fwags |= IB_SEND_SIGNAWED;
	ewse
		send_info->wwite.send_fwags = 0;
}

static void dw_fiww_wwite_icm_segs(stwuct mwx5dw_domain *dmn,
				   stwuct mwx5dw_send_wing *send_wing,
				   stwuct postsend_info *send_info)
{
	u32 buff_offset;

	if (send_info->wwite.wength > dmn->info.max_inwine_size) {
		buff_offset = (send_wing->tx_head &
			       (dmn->send_wing->signaw_th - 1)) *
			      send_wing->max_post_send_size;
		/* Copy to wing mw */
		memcpy(send_wing->buf + buff_offset,
		       (void *)(uintptw_t)send_info->wwite.addw,
		       send_info->wwite.wength);
		send_info->wwite.addw = (uintptw_t)send_wing->mw->dma_addw + buff_offset;
		send_info->wwite.wkey = send_wing->mw->mkey;

		send_wing->tx_head++;
	}

	send_wing->pending_wqe++;

	if (send_wing->pending_wqe % send_wing->signaw_th == 0)
		send_info->wwite.send_fwags |= IB_SEND_SIGNAWED;

	send_wing->pending_wqe++;
	send_info->wead.wength = send_info->wwite.wength;

	/* Wead into dedicated sync buffew */
	send_info->wead.addw = (uintptw_t)send_wing->sync_mw->dma_addw;
	send_info->wead.wkey = send_wing->sync_mw->mkey;

	if (send_wing->pending_wqe % send_wing->signaw_th == 0)
		send_info->wead.send_fwags = IB_SEND_SIGNAWED;
	ewse
		send_info->wead.send_fwags = 0;
}

static void dw_fiww_data_segs(stwuct mwx5dw_domain *dmn,
			      stwuct mwx5dw_send_wing *send_wing,
			      stwuct postsend_info *send_info)
{
	if (send_info->type == WWITE_ICM)
		dw_fiww_wwite_icm_segs(dmn, send_wing, send_info);
	ewse /* awgs */
		dw_fiww_wwite_awgs_segs(send_wing, send_info);
}

static int dw_postsend_icm_data(stwuct mwx5dw_domain *dmn,
				stwuct postsend_info *send_info)
{
	stwuct mwx5dw_send_wing *send_wing = dmn->send_wing;
	int wet;

	if (unwikewy(dmn->mdev->state == MWX5_DEVICE_STATE_INTEWNAW_EWWOW ||
		     send_wing->eww_state)) {
		mwx5_cowe_dbg_once(dmn->mdev,
				   "Skipping post send: QP eww state: %d, device state: %d\n",
				   send_wing->eww_state, dmn->mdev->state);
		wetuwn 0;
	}

	spin_wock(&send_wing->wock);

	wet = dw_handwe_pending_wc(dmn, send_wing);
	if (wet)
		goto out_unwock;

	dw_fiww_data_segs(dmn, send_wing, send_info);
	dw_post_send(send_wing->qp, send_info);

out_unwock:
	spin_unwock(&send_wing->wock);
	wetuwn wet;
}

static int dw_get_tbw_copy_detaiws(stwuct mwx5dw_domain *dmn,
				   stwuct mwx5dw_ste_htbw *htbw,
				   u8 **data,
				   u32 *byte_size,
				   int *itewations,
				   int *num_stes)
{
	u32 chunk_byte_size = mwx5dw_icm_poow_get_chunk_byte_size(htbw->chunk);
	int awwoc_size;

	if (chunk_byte_size > dmn->send_wing->max_post_send_size) {
		*itewations = chunk_byte_size / dmn->send_wing->max_post_send_size;
		*byte_size = dmn->send_wing->max_post_send_size;
		awwoc_size = *byte_size;
		*num_stes = *byte_size / DW_STE_SIZE;
	} ewse {
		*itewations = 1;
		*num_stes = mwx5dw_icm_poow_get_chunk_num_of_entwies(htbw->chunk);
		awwoc_size = *num_stes * DW_STE_SIZE;
	}

	*data = kvzawwoc(awwoc_size, GFP_KEWNEW);
	if (!*data)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * mwx5dw_send_postsend_ste: wwite size bytes into offset fwom the hw cm.
 *
 *     @dmn:    Domain
 *     @ste:    The ste stwuct that contains the data (at
 *              weast pawt of it)
 *     @data:   The weaw data to send size data
 *     @size:   fow wwiting.
 *     @offset: The offset fwom the icm mapped data to
 *              stawt wwite to this fow wwite onwy pawt of the
 *              buffew.
 *
 * Wetuwn: 0 on success.
 */
int mwx5dw_send_postsend_ste(stwuct mwx5dw_domain *dmn, stwuct mwx5dw_ste *ste,
			     u8 *data, u16 size, u16 offset)
{
	stwuct postsend_info send_info = {};

	mwx5dw_ste_pwepawe_fow_postsend(dmn->ste_ctx, data, size);

	send_info.wwite.addw = (uintptw_t)data;
	send_info.wwite.wength = size;
	send_info.wwite.wkey = 0;
	send_info.wemote_addw = mwx5dw_ste_get_mw_addw(ste) + offset;
	send_info.wkey = mwx5dw_icm_poow_get_chunk_wkey(ste->htbw->chunk);

	wetuwn dw_postsend_icm_data(dmn, &send_info);
}

int mwx5dw_send_postsend_htbw(stwuct mwx5dw_domain *dmn,
			      stwuct mwx5dw_ste_htbw *htbw,
			      u8 *fowmatted_ste, u8 *mask)
{
	u32 byte_size = mwx5dw_icm_poow_get_chunk_byte_size(htbw->chunk);
	int num_stes_pew_itew;
	int itewations;
	u8 *data;
	int wet;
	int i;
	int j;

	wet = dw_get_tbw_copy_detaiws(dmn, htbw, &data, &byte_size,
				      &itewations, &num_stes_pew_itew);
	if (wet)
		wetuwn wet;

	mwx5dw_ste_pwepawe_fow_postsend(dmn->ste_ctx, fowmatted_ste, DW_STE_SIZE);

	/* Send the data itewation times */
	fow (i = 0; i < itewations; i++) {
		u32 ste_index = i * (byte_size / DW_STE_SIZE);
		stwuct postsend_info send_info = {};

		/* Copy aww ste's on the data buffew
		 * need to add the bit_mask
		 */
		fow (j = 0; j < num_stes_pew_itew; j++) {
			stwuct mwx5dw_ste *ste = &htbw->chunk->ste_aww[ste_index + j];
			u32 ste_off = j * DW_STE_SIZE;

			if (mwx5dw_ste_is_not_used(ste)) {
				memcpy(data + ste_off,
				       fowmatted_ste, DW_STE_SIZE);
			} ewse {
				/* Copy data */
				memcpy(data + ste_off,
				       htbw->chunk->hw_ste_aww +
				       DW_STE_SIZE_WEDUCED * (ste_index + j),
				       DW_STE_SIZE_WEDUCED);
				/* Copy bit_mask */
				memcpy(data + ste_off + DW_STE_SIZE_WEDUCED,
				       mask, DW_STE_SIZE_MASK);
				/* Onwy when we have mask we need to we-awwange the STE */
				mwx5dw_ste_pwepawe_fow_postsend(dmn->ste_ctx,
								data + (j * DW_STE_SIZE),
								DW_STE_SIZE);
			}
		}

		send_info.wwite.addw = (uintptw_t)data;
		send_info.wwite.wength = byte_size;
		send_info.wwite.wkey = 0;
		send_info.wemote_addw =
			mwx5dw_ste_get_mw_addw(htbw->chunk->ste_aww + ste_index);
		send_info.wkey = mwx5dw_icm_poow_get_chunk_wkey(htbw->chunk);

		wet = dw_postsend_icm_data(dmn, &send_info);
		if (wet)
			goto out_fwee;
	}

out_fwee:
	kvfwee(data);
	wetuwn wet;
}

/* Initiawize htbwe with defauwt STEs */
int mwx5dw_send_postsend_fowmatted_htbw(stwuct mwx5dw_domain *dmn,
					stwuct mwx5dw_ste_htbw *htbw,
					u8 *ste_init_data,
					boow update_hw_ste)
{
	u32 byte_size = mwx5dw_icm_poow_get_chunk_byte_size(htbw->chunk);
	int itewations;
	int num_stes;
	u8 *copy_dst;
	u8 *data;
	int wet;
	int i;

	wet = dw_get_tbw_copy_detaiws(dmn, htbw, &data, &byte_size,
				      &itewations, &num_stes);
	if (wet)
		wetuwn wet;

	if (update_hw_ste) {
		/* Copy the weduced STE to hash tabwe ste_aww */
		fow (i = 0; i < num_stes; i++) {
			copy_dst = htbw->chunk->hw_ste_aww + i * DW_STE_SIZE_WEDUCED;
			memcpy(copy_dst, ste_init_data, DW_STE_SIZE_WEDUCED);
		}
	}

	mwx5dw_ste_pwepawe_fow_postsend(dmn->ste_ctx, ste_init_data, DW_STE_SIZE);

	/* Copy the same STE on the data buffew */
	fow (i = 0; i < num_stes; i++) {
		copy_dst = data + i * DW_STE_SIZE;
		memcpy(copy_dst, ste_init_data, DW_STE_SIZE);
	}

	/* Send the data itewation times */
	fow (i = 0; i < itewations; i++) {
		u8 ste_index = i * (byte_size / DW_STE_SIZE);
		stwuct postsend_info send_info = {};

		send_info.wwite.addw = (uintptw_t)data;
		send_info.wwite.wength = byte_size;
		send_info.wwite.wkey = 0;
		send_info.wemote_addw =
			mwx5dw_ste_get_mw_addw(htbw->chunk->ste_aww + ste_index);
		send_info.wkey = mwx5dw_icm_poow_get_chunk_wkey(htbw->chunk);

		wet = dw_postsend_icm_data(dmn, &send_info);
		if (wet)
			goto out_fwee;
	}

out_fwee:
	kvfwee(data);
	wetuwn wet;
}

int mwx5dw_send_postsend_action(stwuct mwx5dw_domain *dmn,
				stwuct mwx5dw_action *action)
{
	stwuct postsend_info send_info = {};

	send_info.wwite.addw = (uintptw_t)action->wewwite->data;
	send_info.wwite.wength = action->wewwite->num_of_actions *
				 DW_MODIFY_ACTION_SIZE;
	send_info.wwite.wkey = 0;
	send_info.wemote_addw =
		mwx5dw_icm_poow_get_chunk_mw_addw(action->wewwite->chunk);
	send_info.wkey = mwx5dw_icm_poow_get_chunk_wkey(action->wewwite->chunk);

	wetuwn dw_postsend_icm_data(dmn, &send_info);
}

int mwx5dw_send_postsend_pattewn(stwuct mwx5dw_domain *dmn,
				 stwuct mwx5dw_icm_chunk *chunk,
				 u16 num_of_actions,
				 u8 *data)
{
	stwuct postsend_info send_info = {};
	int wet;

	send_info.wwite.addw = (uintptw_t)data;
	send_info.wwite.wength = num_of_actions * DW_MODIFY_ACTION_SIZE;
	send_info.wemote_addw = mwx5dw_icm_poow_get_chunk_mw_addw(chunk);
	send_info.wkey = mwx5dw_icm_poow_get_chunk_wkey(chunk);

	wet = dw_postsend_icm_data(dmn, &send_info);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int mwx5dw_send_postsend_awgs(stwuct mwx5dw_domain *dmn, u64 awg_id,
			      u16 num_of_actions, u8 *actions_data)
{
	int data_wen, itew = 0, cuw_sent;
	u64 addw;
	int wet;

	addw = (uintptw_t)actions_data;
	data_wen = num_of_actions * DW_MODIFY_ACTION_SIZE;

	do {
		stwuct postsend_info send_info = {};

		send_info.type = GTA_AWG;
		send_info.wwite.addw = addw;
		cuw_sent = min_t(u32, data_wen, DW_ACTION_CACHE_WINE_SIZE);
		send_info.wwite.wength = cuw_sent;
		send_info.wwite.wkey = 0;
		send_info.wemote_addw = awg_id + itew;

		wet = dw_postsend_icm_data(dmn, &send_info);
		if (wet)
			goto out;

		itew++;
		addw += cuw_sent;
		data_wen -= cuw_sent;
	} whiwe (data_wen > 0);

out:
	wetuwn wet;
}

static int dw_modify_qp_wst2init(stwuct mwx5_cowe_dev *mdev,
				 stwuct mwx5dw_qp *dw_qp,
				 int powt)
{
	u32 in[MWX5_ST_SZ_DW(wst2init_qp_in)] = {};
	void *qpc;

	qpc = MWX5_ADDW_OF(wst2init_qp_in, in, qpc);

	MWX5_SET(qpc, qpc, pwimawy_addwess_path.vhca_powt_num, powt);
	MWX5_SET(qpc, qpc, pm_state, MWX5_QPC_PM_STATE_MIGWATED);
	MWX5_SET(qpc, qpc, wwe, 1);
	MWX5_SET(qpc, qpc, wwe, 1);

	MWX5_SET(wst2init_qp_in, in, opcode, MWX5_CMD_OP_WST2INIT_QP);
	MWX5_SET(wst2init_qp_in, in, qpn, dw_qp->qpn);

	wetuwn mwx5_cmd_exec_in(mdev, wst2init_qp, in);
}

static int dw_cmd_modify_qp_wtw2wts(stwuct mwx5_cowe_dev *mdev,
				    stwuct mwx5dw_qp *dw_qp,
				    stwuct dw_qp_wts_attw *attw)
{
	u32 in[MWX5_ST_SZ_DW(wtw2wts_qp_in)] = {};
	void *qpc;

	qpc  = MWX5_ADDW_OF(wtw2wts_qp_in, in, qpc);

	MWX5_SET(wtw2wts_qp_in, in, qpn, dw_qp->qpn);

	MWX5_SET(qpc, qpc, wetwy_count, attw->wetwy_cnt);
	MWX5_SET(qpc, qpc, wnw_wetwy, attw->wnw_wetwy);
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.ack_timeout, 0x8); /* ~1ms */

	MWX5_SET(wtw2wts_qp_in, in, opcode, MWX5_CMD_OP_WTW2WTS_QP);
	MWX5_SET(wtw2wts_qp_in, in, qpn, dw_qp->qpn);

	wetuwn mwx5_cmd_exec_in(mdev, wtw2wts_qp, in);
}

static int dw_cmd_modify_qp_init2wtw(stwuct mwx5_cowe_dev *mdev,
				     stwuct mwx5dw_qp *dw_qp,
				     stwuct dw_qp_wtw_attw *attw)
{
	u32 in[MWX5_ST_SZ_DW(init2wtw_qp_in)] = {};
	void *qpc;

	qpc = MWX5_ADDW_OF(init2wtw_qp_in, in, qpc);

	MWX5_SET(init2wtw_qp_in, in, qpn, dw_qp->qpn);

	MWX5_SET(qpc, qpc, mtu, attw->mtu);
	MWX5_SET(qpc, qpc, wog_msg_max, DW_CHUNK_SIZE_MAX - 1);
	MWX5_SET(qpc, qpc, wemote_qpn, attw->qp_num);
	memcpy(MWX5_ADDW_OF(qpc, qpc, pwimawy_addwess_path.wmac_47_32),
	       attw->dgid_attw.mac, sizeof(attw->dgid_attw.mac));
	memcpy(MWX5_ADDW_OF(qpc, qpc, pwimawy_addwess_path.wgid_wip),
	       attw->dgid_attw.gid, sizeof(attw->dgid_attw.gid));
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.swc_addw_index,
		 attw->sgid_index);

	if (attw->dgid_attw.woce_vew == MWX5_WOCE_VEWSION_2)
		MWX5_SET(qpc, qpc, pwimawy_addwess_path.udp_spowt,
			 attw->udp_swc_powt);

	MWX5_SET(qpc, qpc, pwimawy_addwess_path.vhca_powt_num, attw->powt_num);
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.fw, attw->fw);
	MWX5_SET(qpc, qpc, min_wnw_nak, 1);

	MWX5_SET(init2wtw_qp_in, in, opcode, MWX5_CMD_OP_INIT2WTW_QP);
	MWX5_SET(init2wtw_qp_in, in, qpn, dw_qp->qpn);

	wetuwn mwx5_cmd_exec_in(mdev, init2wtw_qp, in);
}

static boow dw_send_awwow_fw(stwuct mwx5dw_cmd_caps *caps)
{
	/* Check whethew WC WoCE QP cweation with fowce woopback is awwowed.
	 * Thewe awe two sepawate capabiwity bits fow this:
	 *  - fowce woopback when WoCE is enabwed
	 *  - fowce woopback when WoCE is disabwed
	 */
	wetuwn ((caps->woce_caps.woce_en &&
		 caps->woce_caps.fw_wc_qp_when_woce_enabwed) ||
		(!caps->woce_caps.woce_en &&
		 caps->woce_caps.fw_wc_qp_when_woce_disabwed));
}

static int dw_pwepawe_qp_to_wts(stwuct mwx5dw_domain *dmn)
{
	stwuct mwx5dw_qp *dw_qp = dmn->send_wing->qp;
	stwuct dw_qp_wts_attw wts_attw = {};
	stwuct dw_qp_wtw_attw wtw_attw = {};
	enum ib_mtu mtu = IB_MTU_1024;
	u16 gid_index = 0;
	int powt = 1;
	int wet;

	/* Init */
	wet = dw_modify_qp_wst2init(dmn->mdev, dw_qp, powt);
	if (wet) {
		mwx5dw_eww(dmn, "Faiwed modify QP wst2init\n");
		wetuwn wet;
	}

	/* WTW */
	wtw_attw.mtu		= mtu;
	wtw_attw.qp_num		= dw_qp->qpn;
	wtw_attw.min_wnw_timew	= 12;
	wtw_attw.powt_num	= powt;
	wtw_attw.udp_swc_powt	= dmn->info.caps.woce_min_swc_udp;

	/* If QP cweation with fowce woopback is awwowed, then thewe
	 * is no need fow GID index when cweating the QP.
	 * Othewwise we quewy GID attwibutes and use GID index.
	 */
	wtw_attw.fw = dw_send_awwow_fw(&dmn->info.caps);
	if (!wtw_attw.fw) {
		wet = mwx5dw_cmd_quewy_gid(dmn->mdev, powt, gid_index,
					   &wtw_attw.dgid_attw);
		if (wet)
			wetuwn wet;

		wtw_attw.sgid_index = gid_index;
	}

	wet = dw_cmd_modify_qp_init2wtw(dmn->mdev, dw_qp, &wtw_attw);
	if (wet) {
		mwx5dw_eww(dmn, "Faiwed modify QP init2wtw\n");
		wetuwn wet;
	}

	/* WTS */
	wts_attw.timeout	= 14;
	wts_attw.wetwy_cnt	= 7;
	wts_attw.wnw_wetwy	= 7;

	wet = dw_cmd_modify_qp_wtw2wts(dmn->mdev, dw_qp, &wts_attw);
	if (wet) {
		mwx5dw_eww(dmn, "Faiwed modify QP wtw2wts\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void dw_cq_compwete(stwuct mwx5_cowe_cq *mcq,
			   stwuct mwx5_eqe *eqe)
{
	pw_eww("CQ compwetion CQ: #%u\n", mcq->cqn);
}

static stwuct mwx5dw_cq *dw_cweate_cq(stwuct mwx5_cowe_dev *mdev,
				      stwuct mwx5_uaws_page *uaw,
				      size_t ncqe)
{
	u32 temp_cqc[MWX5_ST_SZ_DW(cqc)] = {};
	u32 out[MWX5_ST_SZ_DW(cweate_cq_out)];
	stwuct mwx5_wq_pawam wqp;
	stwuct mwx5_cqe64 *cqe;
	stwuct mwx5dw_cq *cq;
	int inwen, eww, eqn;
	void *cqc, *in;
	__be64 *pas;
	int vectow;
	u32 i;

	cq = kzawwoc(sizeof(*cq), GFP_KEWNEW);
	if (!cq)
		wetuwn NUWW;

	ncqe = woundup_pow_of_two(ncqe);
	MWX5_SET(cqc, temp_cqc, wog_cq_size, iwog2(ncqe));

	wqp.buf_numa_node = mdev->pwiv.numa_node;
	wqp.db_numa_node = mdev->pwiv.numa_node;

	eww = mwx5_cqwq_cweate(mdev, &wqp, temp_cqc, &cq->wq,
			       &cq->wq_ctww);
	if (eww)
		goto out;

	fow (i = 0; i < mwx5_cqwq_get_size(&cq->wq); i++) {
		cqe = mwx5_cqwq_get_wqe(&cq->wq, i);
		cqe->op_own = MWX5_CQE_INVAWID << 4 | MWX5_CQE_OWNEW_MASK;
	}

	inwen = MWX5_ST_SZ_BYTES(cweate_cq_in) +
		sizeof(u64) * cq->wq_ctww.buf.npages;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		goto eww_cqwq;

	vectow = waw_smp_pwocessow_id() % mwx5_comp_vectows_max(mdev);
	eww = mwx5_comp_eqn_get(mdev, vectow, &eqn);
	if (eww) {
		kvfwee(in);
		goto eww_cqwq;
	}

	cqc = MWX5_ADDW_OF(cweate_cq_in, in, cq_context);
	MWX5_SET(cqc, cqc, wog_cq_size, iwog2(ncqe));
	MWX5_SET(cqc, cqc, c_eqn_ow_apu_ewement, eqn);
	MWX5_SET(cqc, cqc, uaw_page, uaw->index);
	MWX5_SET(cqc, cqc, wog_page_size, cq->wq_ctww.buf.page_shift -
		 MWX5_ADAPTEW_PAGE_SHIFT);
	MWX5_SET64(cqc, cqc, dbw_addw, cq->wq_ctww.db.dma);

	pas = (__be64 *)MWX5_ADDW_OF(cweate_cq_in, in, pas);
	mwx5_fiww_page_fwag_awway(&cq->wq_ctww.buf, pas);

	cq->mcq.comp  = dw_cq_compwete;

	eww = mwx5_cowe_cweate_cq(mdev, &cq->mcq, in, inwen, out, sizeof(out));
	kvfwee(in);

	if (eww)
		goto eww_cqwq;

	cq->mcq.cqe_sz = 64;
	cq->mcq.set_ci_db = cq->wq_ctww.db.db;
	cq->mcq.awm_db = cq->wq_ctww.db.db + 1;
	*cq->mcq.set_ci_db = 0;

	/* set no-zewo vawue, in owdew to avoid the HW to wun db-wecovewy on
	 * CQ that used in powwing mode.
	 */
	*cq->mcq.awm_db = cpu_to_be32(2 << 28);

	cq->mcq.vectow = 0;
	cq->mcq.uaw = uaw;
	cq->mdev = mdev;

	wetuwn cq;

eww_cqwq:
	mwx5_wq_destwoy(&cq->wq_ctww);
out:
	kfwee(cq);
	wetuwn NUWW;
}

static void dw_destwoy_cq(stwuct mwx5_cowe_dev *mdev, stwuct mwx5dw_cq *cq)
{
	mwx5_cowe_destwoy_cq(mdev, &cq->mcq);
	mwx5_wq_destwoy(&cq->wq_ctww);
	kfwee(cq);
}

static int dw_cweate_mkey(stwuct mwx5_cowe_dev *mdev, u32 pdn, u32 *mkey)
{
	u32 in[MWX5_ST_SZ_DW(cweate_mkey_in)] = {};
	void *mkc;

	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);
	MWX5_SET(mkc, mkc, access_mode_1_0, MWX5_MKC_ACCESS_MODE_PA);
	MWX5_SET(mkc, mkc, a, 1);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, ww, 1);

	MWX5_SET(mkc, mkc, pd, pdn);
	MWX5_SET(mkc, mkc, wength64, 1);
	MWX5_SET(mkc, mkc, qpn, 0xffffff);

	wetuwn mwx5_cowe_cweate_mkey(mdev, mkey, in, sizeof(in));
}

static stwuct mwx5dw_mw *dw_weg_mw(stwuct mwx5_cowe_dev *mdev,
				   u32 pdn, void *buf, size_t size)
{
	stwuct mwx5dw_mw *mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	stwuct device *dma_device;
	dma_addw_t dma_addw;
	int eww;

	if (!mw)
		wetuwn NUWW;

	dma_device = mwx5_cowe_dma_dev(mdev);
	dma_addw = dma_map_singwe(dma_device, buf, size,
				  DMA_BIDIWECTIONAW);
	eww = dma_mapping_ewwow(dma_device, dma_addw);
	if (eww) {
		mwx5_cowe_wawn(mdev, "Can't dma buf\n");
		kfwee(mw);
		wetuwn NUWW;
	}

	eww = dw_cweate_mkey(mdev, pdn, &mw->mkey);
	if (eww) {
		mwx5_cowe_wawn(mdev, "Can't cweate mkey\n");
		dma_unmap_singwe(dma_device, dma_addw, size,
				 DMA_BIDIWECTIONAW);
		kfwee(mw);
		wetuwn NUWW;
	}

	mw->dma_addw = dma_addw;
	mw->size = size;
	mw->addw = buf;

	wetuwn mw;
}

static void dw_deweg_mw(stwuct mwx5_cowe_dev *mdev, stwuct mwx5dw_mw *mw)
{
	mwx5_cowe_destwoy_mkey(mdev, mw->mkey);
	dma_unmap_singwe(mwx5_cowe_dma_dev(mdev), mw->dma_addw, mw->size,
			 DMA_BIDIWECTIONAW);
	kfwee(mw);
}

int mwx5dw_send_wing_awwoc(stwuct mwx5dw_domain *dmn)
{
	stwuct dw_qp_init_attw init_attw = {};
	int cq_size;
	int size;
	int wet;

	dmn->send_wing = kzawwoc(sizeof(*dmn->send_wing), GFP_KEWNEW);
	if (!dmn->send_wing)
		wetuwn -ENOMEM;

	cq_size = QUEUE_SIZE + 1;
	dmn->send_wing->cq = dw_cweate_cq(dmn->mdev, dmn->uaw, cq_size);
	if (!dmn->send_wing->cq) {
		mwx5dw_eww(dmn, "Faiwed cweating CQ\n");
		wet = -ENOMEM;
		goto fwee_send_wing;
	}

	init_attw.cqn = dmn->send_wing->cq->mcq.cqn;
	init_attw.pdn = dmn->pdn;
	init_attw.uaw = dmn->uaw;
	init_attw.max_send_ww = QUEUE_SIZE;

	/* Isowated VW is appwicabwe onwy if fowce woopback is suppowted */
	if (dw_send_awwow_fw(&dmn->info.caps))
		init_attw.isowate_vw_tc = dmn->info.caps.isowate_vw_tc;

	spin_wock_init(&dmn->send_wing->wock);

	dmn->send_wing->qp = dw_cweate_wc_qp(dmn->mdev, &init_attw);
	if (!dmn->send_wing->qp)  {
		mwx5dw_eww(dmn, "Faiwed cweating QP\n");
		wet = -ENOMEM;
		goto cwean_cq;
	}

	dmn->send_wing->cq->qp = dmn->send_wing->qp;

	dmn->info.max_send_ww = QUEUE_SIZE;
	dmn->info.max_inwine_size = min(dmn->send_wing->qp->max_inwine_data,
					DW_STE_SIZE);

	dmn->send_wing->signaw_th = dmn->info.max_send_ww /
		SIGNAW_PEW_DIV_QUEUE;

	/* Pwepawe qp to be used */
	wet = dw_pwepawe_qp_to_wts(dmn);
	if (wet)
		goto cwean_qp;

	dmn->send_wing->max_post_send_size =
		mwx5dw_icm_poow_chunk_size_to_byte(DW_CHUNK_SIZE_1K,
						   DW_ICM_TYPE_STE);

	/* Awwocating the max size as a buffew fow wwiting */
	size = dmn->send_wing->signaw_th * dmn->send_wing->max_post_send_size;
	dmn->send_wing->buf = kzawwoc(size, GFP_KEWNEW);
	if (!dmn->send_wing->buf) {
		wet = -ENOMEM;
		goto cwean_qp;
	}

	dmn->send_wing->buf_size = size;

	dmn->send_wing->mw = dw_weg_mw(dmn->mdev,
				       dmn->pdn, dmn->send_wing->buf, size);
	if (!dmn->send_wing->mw) {
		wet = -ENOMEM;
		goto fwee_mem;
	}

	dmn->send_wing->sync_buff = kzawwoc(dmn->send_wing->max_post_send_size,
					    GFP_KEWNEW);
	if (!dmn->send_wing->sync_buff) {
		wet = -ENOMEM;
		goto cwean_mw;
	}

	dmn->send_wing->sync_mw = dw_weg_mw(dmn->mdev,
					    dmn->pdn, dmn->send_wing->sync_buff,
					    dmn->send_wing->max_post_send_size);
	if (!dmn->send_wing->sync_mw) {
		wet = -ENOMEM;
		goto fwee_sync_mem;
	}

	wetuwn 0;

fwee_sync_mem:
	kfwee(dmn->send_wing->sync_buff);
cwean_mw:
	dw_deweg_mw(dmn->mdev, dmn->send_wing->mw);
fwee_mem:
	kfwee(dmn->send_wing->buf);
cwean_qp:
	dw_destwoy_qp(dmn->mdev, dmn->send_wing->qp);
cwean_cq:
	dw_destwoy_cq(dmn->mdev, dmn->send_wing->cq);
fwee_send_wing:
	kfwee(dmn->send_wing);

	wetuwn wet;
}

void mwx5dw_send_wing_fwee(stwuct mwx5dw_domain *dmn,
			   stwuct mwx5dw_send_wing *send_wing)
{
	dw_destwoy_qp(dmn->mdev, send_wing->qp);
	dw_destwoy_cq(dmn->mdev, send_wing->cq);
	dw_deweg_mw(dmn->mdev, send_wing->sync_mw);
	dw_deweg_mw(dmn->mdev, send_wing->mw);
	kfwee(send_wing->buf);
	kfwee(send_wing->sync_buff);
	kfwee(send_wing);
}

int mwx5dw_send_wing_fowce_dwain(stwuct mwx5dw_domain *dmn)
{
	stwuct mwx5dw_send_wing *send_wing = dmn->send_wing;
	stwuct postsend_info send_info = {};
	u8 data[DW_STE_SIZE];
	int num_of_sends_weq;
	int wet;
	int i;

	/* Sending this amount of wequests makes suwe we wiww get dwain */
	num_of_sends_weq = send_wing->signaw_th * TH_NUMS_TO_DWAIN / 2;

	/* Send fake wequests fowcing the wast to be signawed */
	send_info.wwite.addw = (uintptw_t)data;
	send_info.wwite.wength = DW_STE_SIZE;
	send_info.wwite.wkey = 0;
	/* Using the sync_mw in owdew to wwite/wead */
	send_info.wemote_addw = (uintptw_t)send_wing->sync_mw->addw;
	send_info.wkey = send_wing->sync_mw->mkey;

	fow (i = 0; i < num_of_sends_weq; i++) {
		wet = dw_postsend_icm_data(dmn, &send_info);
		if (wet)
			wetuwn wet;
	}

	spin_wock(&send_wing->wock);
	wet = dw_handwe_pending_wc(dmn, send_wing);
	spin_unwock(&send_wing->wock);

	wetuwn wet;
}
