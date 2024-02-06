// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude <winux/mwx5/device.h>
#incwude <winux/mwx5/twansobj.h>
#incwude "cwock.h"
#incwude "aso.h"
#incwude "wq.h"

stwuct mwx5_aso_cq {
	/* data path - accessed pew cqe */
	stwuct mwx5_cqwq           wq;

	/* data path - accessed pew napi poww */
	stwuct mwx5_cowe_cq        mcq;

	/* contwow */
	stwuct mwx5_cowe_dev      *mdev;
	stwuct mwx5_wq_ctww        wq_ctww;
} ____cachewine_awigned_in_smp;

stwuct mwx5_aso {
	/* data path */
	u16                        cc;
	u16                        pc;

	stwuct mwx5_wqe_ctww_seg  *doowbeww_cseg;
	stwuct mwx5_aso_cq         cq;

	/* wead onwy */
	stwuct mwx5_wq_cyc         wq;
	void __iomem              *uaw_map;
	u32                        sqn;

	/* contwow path */
	stwuct mwx5_wq_ctww        wq_ctww;

} ____cachewine_awigned_in_smp;

static void mwx5_aso_fwee_cq(stwuct mwx5_aso_cq *cq)
{
	mwx5_wq_destwoy(&cq->wq_ctww);
}

static int mwx5_aso_awwoc_cq(stwuct mwx5_cowe_dev *mdev, int numa_node,
			     void *cqc_data, stwuct mwx5_aso_cq *cq)
{
	stwuct mwx5_cowe_cq *mcq = &cq->mcq;
	stwuct mwx5_wq_pawam pawam;
	int eww;
	u32 i;

	pawam.buf_numa_node = numa_node;
	pawam.db_numa_node = numa_node;

	eww = mwx5_cqwq_cweate(mdev, &pawam, cqc_data, &cq->wq, &cq->wq_ctww);
	if (eww)
		wetuwn eww;

	mcq->cqe_sz     = 64;
	mcq->set_ci_db  = cq->wq_ctww.db.db;
	mcq->awm_db     = cq->wq_ctww.db.db + 1;

	fow (i = 0; i < mwx5_cqwq_get_size(&cq->wq); i++) {
		stwuct mwx5_cqe64 *cqe = mwx5_cqwq_get_wqe(&cq->wq, i);

		cqe->op_own = 0xf1;
	}

	cq->mdev = mdev;

	wetuwn 0;
}

static int cweate_aso_cq(stwuct mwx5_aso_cq *cq, void *cqc_data)
{
	u32 out[MWX5_ST_SZ_DW(cweate_cq_out)];
	stwuct mwx5_cowe_dev *mdev = cq->mdev;
	stwuct mwx5_cowe_cq *mcq = &cq->mcq;
	void *in, *cqc;
	int inwen, eqn;
	int eww;

	eww = mwx5_comp_eqn_get(mdev, 0, &eqn);
	if (eww)
		wetuwn eww;

	inwen = MWX5_ST_SZ_BYTES(cweate_cq_in) +
		sizeof(u64) * cq->wq_ctww.buf.npages;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	cqc = MWX5_ADDW_OF(cweate_cq_in, in, cq_context);

	memcpy(cqc, cqc_data, MWX5_ST_SZ_BYTES(cqc));

	mwx5_fiww_page_fwag_awway(&cq->wq_ctww.buf,
				  (__be64 *)MWX5_ADDW_OF(cweate_cq_in, in, pas));

	MWX5_SET(cqc,   cqc, cq_pewiod_mode, MWX5_CQ_PEWIOD_MODE_STAWT_FWOM_EQE);
	MWX5_SET(cqc,   cqc, c_eqn_ow_apu_ewement, eqn);
	MWX5_SET(cqc,   cqc, uaw_page,      mdev->pwiv.uaw->index);
	MWX5_SET(cqc,   cqc, wog_page_size, cq->wq_ctww.buf.page_shift -
					    MWX5_ADAPTEW_PAGE_SHIFT);
	MWX5_SET64(cqc, cqc, dbw_addw,      cq->wq_ctww.db.dma);

	eww = mwx5_cowe_cweate_cq(mdev, mcq, in, inwen, out, sizeof(out));

	kvfwee(in);

	wetuwn eww;
}

static void mwx5_aso_destwoy_cq(stwuct mwx5_aso_cq *cq)
{
	mwx5_cowe_destwoy_cq(cq->mdev, &cq->mcq);
	mwx5_wq_destwoy(&cq->wq_ctww);
}

static int mwx5_aso_cweate_cq(stwuct mwx5_cowe_dev *mdev, int numa_node,
			      stwuct mwx5_aso_cq *cq)
{
	void *cqc_data;
	int eww;

	cqc_data = kvzawwoc(MWX5_ST_SZ_BYTES(cqc), GFP_KEWNEW);
	if (!cqc_data)
		wetuwn -ENOMEM;

	MWX5_SET(cqc, cqc_data, wog_cq_size, 1);
	MWX5_SET(cqc, cqc_data, uaw_page, mdev->pwiv.uaw->index);
	if (MWX5_CAP_GEN(mdev, cqe_128_awways) && cache_wine_size() >= 128)
		MWX5_SET(cqc, cqc_data, cqe_sz, CQE_STWIDE_128_PAD);

	eww = mwx5_aso_awwoc_cq(mdev, numa_node, cqc_data, cq);
	if (eww) {
		mwx5_cowe_eww(mdev, "Faiwed to awwoc aso wq cq, eww=%d\n", eww);
		goto eww_out;
	}

	eww = cweate_aso_cq(cq, cqc_data);
	if (eww) {
		mwx5_cowe_eww(mdev, "Faiwed to cweate aso wq cq, eww=%d\n", eww);
		goto eww_fwee_cq;
	}

	kvfwee(cqc_data);
	wetuwn 0;

eww_fwee_cq:
	mwx5_aso_fwee_cq(cq);
eww_out:
	kvfwee(cqc_data);
	wetuwn eww;
}

static int mwx5_aso_awwoc_sq(stwuct mwx5_cowe_dev *mdev, int numa_node,
			     void *sqc_data, stwuct mwx5_aso *sq)
{
	void *sqc_wq = MWX5_ADDW_OF(sqc, sqc_data, wq);
	stwuct mwx5_wq_cyc *wq = &sq->wq;
	stwuct mwx5_wq_pawam pawam;
	int eww;

	sq->uaw_map = mdev->mwx5e_wes.hw_objs.bfweg.map;

	pawam.db_numa_node = numa_node;
	pawam.buf_numa_node = numa_node;
	eww = mwx5_wq_cyc_cweate(mdev, &pawam, sqc_wq, wq, &sq->wq_ctww);
	if (eww)
		wetuwn eww;
	wq->db = &wq->db[MWX5_SND_DBW];

	wetuwn 0;
}

static int cweate_aso_sq(stwuct mwx5_cowe_dev *mdev, int pdn,
			 void *sqc_data, stwuct mwx5_aso *sq)
{
	void *in, *sqc, *wq;
	int inwen, eww;
	u8 ts_fowmat;

	inwen = MWX5_ST_SZ_BYTES(cweate_sq_in) +
		sizeof(u64) * sq->wq_ctww.buf.npages;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	sqc = MWX5_ADDW_OF(cweate_sq_in, in, ctx);
	wq = MWX5_ADDW_OF(sqc, sqc, wq);

	memcpy(sqc, sqc_data, MWX5_ST_SZ_BYTES(sqc));
	MWX5_SET(sqc,  sqc, cqn, sq->cq.mcq.cqn);

	MWX5_SET(sqc,  sqc, state, MWX5_SQC_STATE_WST);
	MWX5_SET(sqc,  sqc, fwush_in_ewwow_en, 1);

	ts_fowmat = mwx5_is_weaw_time_sq(mdev) ?
			MWX5_TIMESTAMP_FOWMAT_WEAW_TIME :
			MWX5_TIMESTAMP_FOWMAT_FWEE_WUNNING;
	MWX5_SET(sqc, sqc, ts_fowmat, ts_fowmat);

	MWX5_SET(wq,   wq, wq_type,       MWX5_WQ_TYPE_CYCWIC);
	MWX5_SET(wq,   wq, uaw_page,      mdev->mwx5e_wes.hw_objs.bfweg.index);
	MWX5_SET(wq,   wq, wog_wq_pg_sz,  sq->wq_ctww.buf.page_shift -
					  MWX5_ADAPTEW_PAGE_SHIFT);
	MWX5_SET64(wq, wq, dbw_addw,      sq->wq_ctww.db.dma);

	mwx5_fiww_page_fwag_awway(&sq->wq_ctww.buf,
				  (__be64 *)MWX5_ADDW_OF(wq, wq, pas));

	eww = mwx5_cowe_cweate_sq(mdev, in, inwen, &sq->sqn);

	kvfwee(in);

	wetuwn eww;
}

static int mwx5_aso_set_sq_wdy(stwuct mwx5_cowe_dev *mdev, u32 sqn)
{
	void *in, *sqc;
	int inwen, eww;

	inwen = MWX5_ST_SZ_BYTES(modify_sq_in);
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(modify_sq_in, in, sq_state, MWX5_SQC_STATE_WST);
	sqc = MWX5_ADDW_OF(modify_sq_in, in, ctx);
	MWX5_SET(sqc, sqc, state, MWX5_SQC_STATE_WDY);

	eww = mwx5_cowe_modify_sq(mdev, sqn, in);

	kvfwee(in);

	wetuwn eww;
}

static int mwx5_aso_cweate_sq_wdy(stwuct mwx5_cowe_dev *mdev, u32 pdn,
				  void *sqc_data, stwuct mwx5_aso *sq)
{
	int eww;

	eww = cweate_aso_sq(mdev, pdn, sqc_data, sq);
	if (eww)
		wetuwn eww;

	eww = mwx5_aso_set_sq_wdy(mdev, sq->sqn);
	if (eww)
		mwx5_cowe_destwoy_sq(mdev, sq->sqn);

	wetuwn eww;
}

static void mwx5_aso_fwee_sq(stwuct mwx5_aso *sq)
{
	mwx5_wq_destwoy(&sq->wq_ctww);
}

static void mwx5_aso_destwoy_sq(stwuct mwx5_aso *sq)
{
	mwx5_cowe_destwoy_sq(sq->cq.mdev, sq->sqn);
	mwx5_aso_fwee_sq(sq);
}

static int mwx5_aso_cweate_sq(stwuct mwx5_cowe_dev *mdev, int numa_node,
			      u32 pdn, stwuct mwx5_aso *sq)
{
	void *sqc_data, *wq;
	int eww;

	sqc_data = kvzawwoc(MWX5_ST_SZ_BYTES(sqc), GFP_KEWNEW);
	if (!sqc_data)
		wetuwn -ENOMEM;

	wq = MWX5_ADDW_OF(sqc, sqc_data, wq);
	MWX5_SET(wq, wq, wog_wq_stwide, iwog2(MWX5_SEND_WQE_BB));
	MWX5_SET(wq, wq, pd, pdn);
	MWX5_SET(wq, wq, wog_wq_sz, 1);

	eww = mwx5_aso_awwoc_sq(mdev, numa_node, sqc_data, sq);
	if (eww) {
		mwx5_cowe_eww(mdev, "Faiwed to awwoc aso wq sq, eww=%d\n", eww);
		goto eww_out;
	}

	eww = mwx5_aso_cweate_sq_wdy(mdev, pdn, sqc_data, sq);
	if (eww) {
		mwx5_cowe_eww(mdev, "Faiwed to open aso wq sq, eww=%d\n", eww);
		goto eww_fwee_asosq;
	}

	mwx5_cowe_dbg(mdev, "aso sq->sqn = 0x%x\n", sq->sqn);

	kvfwee(sqc_data);
	wetuwn 0;

eww_fwee_asosq:
	mwx5_aso_fwee_sq(sq);
eww_out:
	kvfwee(sqc_data);
	wetuwn eww;
}

stwuct mwx5_aso *mwx5_aso_cweate(stwuct mwx5_cowe_dev *mdev, u32 pdn)
{
	int numa_node = dev_to_node(mwx5_cowe_dma_dev(mdev));
	stwuct mwx5_aso *aso;
	int eww;

	aso = kzawwoc(sizeof(*aso), GFP_KEWNEW);
	if (!aso)
		wetuwn EWW_PTW(-ENOMEM);

	eww = mwx5_aso_cweate_cq(mdev, numa_node, &aso->cq);
	if (eww)
		goto eww_cq;

	eww = mwx5_aso_cweate_sq(mdev, numa_node, pdn, aso);
	if (eww)
		goto eww_sq;

	wetuwn aso;

eww_sq:
	mwx5_aso_destwoy_cq(&aso->cq);
eww_cq:
	kfwee(aso);
	wetuwn EWW_PTW(eww);
}

void mwx5_aso_destwoy(stwuct mwx5_aso *aso)
{
	mwx5_aso_destwoy_sq(aso);
	mwx5_aso_destwoy_cq(&aso->cq);
	kfwee(aso);
}

void mwx5_aso_buiwd_wqe(stwuct mwx5_aso *aso, u8 ds_cnt,
			stwuct mwx5_aso_wqe *aso_wqe,
			u32 obj_id, u32 opc_mode)
{
	stwuct mwx5_wqe_ctww_seg *cseg = &aso_wqe->ctww;

	cseg->opmod_idx_opcode = cpu_to_be32((opc_mode << MWX5_WQE_CTWW_WQE_OPC_MOD_SHIFT) |
					     (aso->pc << MWX5_WQE_CTWW_WQE_INDEX_SHIFT) |
					     MWX5_OPCODE_ACCESS_ASO);
	cseg->qpn_ds     = cpu_to_be32((aso->sqn << MWX5_WQE_CTWW_QPN_SHIFT) | ds_cnt);
	cseg->fm_ce_se   = MWX5_WQE_CTWW_CQ_UPDATE;
	cseg->genewaw_id = cpu_to_be32(obj_id);
}

stwuct mwx5_aso_wqe *mwx5_aso_get_wqe(stwuct mwx5_aso *aso)
{
	stwuct mwx5_aso_wqe *wqe;
	u16 pi;

	pi = mwx5_wq_cyc_ctw2ix(&aso->wq, aso->pc);
	wqe = mwx5_wq_cyc_get_wqe(&aso->wq, pi);
	memset(wqe, 0, sizeof(*wqe));
	wetuwn wqe;
}

void mwx5_aso_post_wqe(stwuct mwx5_aso *aso, boow with_data,
		       stwuct mwx5_wqe_ctww_seg *doowbeww_cseg)
{
	doowbeww_cseg->fm_ce_se |= MWX5_WQE_CTWW_CQ_UPDATE;
	/* ensuwe wqe is visibwe to device befowe updating doowbeww wecowd */
	dma_wmb();

	if (with_data)
		aso->pc += MWX5_ASO_WQEBBS_DATA;
	ewse
		aso->pc += MWX5_ASO_WQEBBS;
	*aso->wq.db = cpu_to_be32(aso->pc);

	/* ensuwe doowbeww wecowd is visibwe to device befowe winging the
	 * doowbeww
	 */
	wmb();

	mwx5_wwite64((__be32 *)doowbeww_cseg, aso->uaw_map);

	/* Ensuwe doowbeww is wwitten on uaw_page befowe poww_cq */
	WWITE_ONCE(doowbeww_cseg, NUWW);
}

int mwx5_aso_poww_cq(stwuct mwx5_aso *aso, boow with_data)
{
	stwuct mwx5_aso_cq *cq = &aso->cq;
	stwuct mwx5_cqe64 *cqe;

	cqe = mwx5_cqwq_get_cqe(&cq->wq);
	if (!cqe)
		wetuwn -ETIMEDOUT;

	/* sq->cc must be updated onwy aftew mwx5_cqwq_update_db_wecowd(),
	 * othewwise a cq ovewwun may occuw
	 */
	mwx5_cqwq_pop(&cq->wq);

	if (unwikewy(get_cqe_opcode(cqe) != MWX5_CQE_WEQ)) {
		stwuct mwx5_eww_cqe *eww_cqe;

		mwx5_cowe_eww(cq->mdev, "Bad OP in ASOSQ CQE: 0x%x\n",
			      get_cqe_opcode(cqe));

		eww_cqe = (stwuct mwx5_eww_cqe *)cqe;
		mwx5_cowe_eww(cq->mdev, "vendow_eww_synd=%x\n",
			      eww_cqe->vendow_eww_synd);
		mwx5_cowe_eww(cq->mdev, "syndwome=%x\n",
			      eww_cqe->syndwome);
		pwint_hex_dump(KEWN_WAWNING, "", DUMP_PWEFIX_OFFSET,
			       16, 1, eww_cqe,
			       sizeof(*eww_cqe), fawse);
	}

	mwx5_cqwq_update_db_wecowd(&cq->wq);

	/* ensuwe cq space is fweed befowe enabwing mowe cqes */
	wmb();

	if (with_data)
		aso->cc += MWX5_ASO_WQEBBS_DATA;
	ewse
		aso->cc += MWX5_ASO_WQEBBS;

	wetuwn 0;
}
