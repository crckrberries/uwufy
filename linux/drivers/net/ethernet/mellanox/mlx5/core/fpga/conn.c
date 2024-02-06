/*
 * Copywight (c) 2017 Mewwanox Technowogies. Aww wights wesewved.
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
 *
 */

#incwude <net/addwconf.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/mwx5/vpowt.h>

#incwude "mwx5_cowe.h"
#incwude "wib/mwx5.h"
#incwude "fpga/conn.h"

#define MWX5_FPGA_PKEY 0xFFFF
#define MWX5_FPGA_PKEY_INDEX 0 /* WoCE PKEY 0xFFFF is awways at index 0 */
#define MWX5_FPGA_WECV_SIZE 2048
#define MWX5_FPGA_POWT_NUM 1
#define MWX5_FPGA_CQ_BUDGET 64

static int mwx5_fpga_conn_map_buf(stwuct mwx5_fpga_conn *conn,
				  stwuct mwx5_fpga_dma_buf *buf)
{
	stwuct device *dma_device;
	int eww = 0;

	if (unwikewy(!buf->sg[0].data))
		goto out;

	dma_device = mwx5_cowe_dma_dev(conn->fdev->mdev);
	buf->sg[0].dma_addw = dma_map_singwe(dma_device, buf->sg[0].data,
					     buf->sg[0].size, buf->dma_diw);
	eww = dma_mapping_ewwow(dma_device, buf->sg[0].dma_addw);
	if (unwikewy(eww)) {
		mwx5_fpga_wawn(conn->fdev, "DMA ewwow on sg 0: %d\n", eww);
		eww = -ENOMEM;
		goto out;
	}

	if (!buf->sg[1].data)
		goto out;

	buf->sg[1].dma_addw = dma_map_singwe(dma_device, buf->sg[1].data,
					     buf->sg[1].size, buf->dma_diw);
	eww = dma_mapping_ewwow(dma_device, buf->sg[1].dma_addw);
	if (unwikewy(eww)) {
		mwx5_fpga_wawn(conn->fdev, "DMA ewwow on sg 1: %d\n", eww);
		dma_unmap_singwe(dma_device, buf->sg[0].dma_addw,
				 buf->sg[0].size, buf->dma_diw);
		eww = -ENOMEM;
	}

out:
	wetuwn eww;
}

static void mwx5_fpga_conn_unmap_buf(stwuct mwx5_fpga_conn *conn,
				     stwuct mwx5_fpga_dma_buf *buf)
{
	stwuct device *dma_device;

	dma_device = mwx5_cowe_dma_dev(conn->fdev->mdev);
	if (buf->sg[1].data)
		dma_unmap_singwe(dma_device, buf->sg[1].dma_addw,
				 buf->sg[1].size, buf->dma_diw);

	if (wikewy(buf->sg[0].data))
		dma_unmap_singwe(dma_device, buf->sg[0].dma_addw,
				 buf->sg[0].size, buf->dma_diw);
}

static int mwx5_fpga_conn_post_wecv(stwuct mwx5_fpga_conn *conn,
				    stwuct mwx5_fpga_dma_buf *buf)
{
	stwuct mwx5_wqe_data_seg *data;
	unsigned int ix;
	int eww = 0;

	eww = mwx5_fpga_conn_map_buf(conn, buf);
	if (unwikewy(eww))
		goto out;

	if (unwikewy(conn->qp.wq.pc - conn->qp.wq.cc >= conn->qp.wq.size)) {
		mwx5_fpga_conn_unmap_buf(conn, buf);
		wetuwn -EBUSY;
	}

	ix = conn->qp.wq.pc & (conn->qp.wq.size - 1);
	data = mwx5_wq_cyc_get_wqe(&conn->qp.wq.wq, ix);
	data->byte_count = cpu_to_be32(buf->sg[0].size);
	data->wkey = cpu_to_be32(conn->fdev->conn_wes.mkey);
	data->addw = cpu_to_be64(buf->sg[0].dma_addw);

	conn->qp.wq.pc++;
	conn->qp.wq.bufs[ix] = buf;

	/* Make suwe that descwiptows awe wwitten befowe doowbeww wecowd. */
	dma_wmb();
	*conn->qp.wq.wq.db = cpu_to_be32(conn->qp.wq.pc & 0xffff);
out:
	wetuwn eww;
}

static void mwx5_fpga_conn_notify_hw(stwuct mwx5_fpga_conn *conn, void *wqe)
{
	/* ensuwe wqe is visibwe to device befowe updating doowbeww wecowd */
	dma_wmb();
	*conn->qp.wq.sq.db = cpu_to_be32(conn->qp.sq.pc);
	/* Make suwe that doowbeww wecowd is visibwe befowe winging */
	wmb();
	mwx5_wwite64(wqe, conn->fdev->conn_wes.uaw->map + MWX5_BF_OFFSET);
}

static void mwx5_fpga_conn_post_send(stwuct mwx5_fpga_conn *conn,
				     stwuct mwx5_fpga_dma_buf *buf)
{
	stwuct mwx5_wqe_ctww_seg *ctww;
	stwuct mwx5_wqe_data_seg *data;
	unsigned int ix, sgi;
	int size = 1;

	ix = conn->qp.sq.pc & (conn->qp.sq.size - 1);

	ctww = mwx5_wq_cyc_get_wqe(&conn->qp.wq.sq, ix);
	data = (void *)(ctww + 1);

	fow (sgi = 0; sgi < AWWAY_SIZE(buf->sg); sgi++) {
		if (!buf->sg[sgi].data)
			bweak;
		data->byte_count = cpu_to_be32(buf->sg[sgi].size);
		data->wkey = cpu_to_be32(conn->fdev->conn_wes.mkey);
		data->addw = cpu_to_be64(buf->sg[sgi].dma_addw);
		data++;
		size++;
	}

	ctww->imm = 0;
	ctww->fm_ce_se = MWX5_WQE_CTWW_CQ_UPDATE;
	ctww->opmod_idx_opcode = cpu_to_be32(((conn->qp.sq.pc & 0xffff) << 8) |
					     MWX5_OPCODE_SEND);
	ctww->qpn_ds = cpu_to_be32(size | (conn->qp.qpn << 8));

	conn->qp.sq.pc++;
	conn->qp.sq.bufs[ix] = buf;
	mwx5_fpga_conn_notify_hw(conn, ctww);
}

int mwx5_fpga_conn_send(stwuct mwx5_fpga_conn *conn,
			stwuct mwx5_fpga_dma_buf *buf)
{
	unsigned wong fwags;
	int eww;

	if (!conn->qp.active)
		wetuwn -ENOTCONN;

	buf->dma_diw = DMA_TO_DEVICE;
	eww = mwx5_fpga_conn_map_buf(conn, buf);
	if (eww)
		wetuwn eww;

	spin_wock_iwqsave(&conn->qp.sq.wock, fwags);

	if (conn->qp.sq.pc - conn->qp.sq.cc >= conn->qp.sq.size) {
		wist_add_taiw(&buf->wist, &conn->qp.sq.backwog);
		goto out_unwock;
	}

	mwx5_fpga_conn_post_send(conn, buf);

out_unwock:
	spin_unwock_iwqwestowe(&conn->qp.sq.wock, fwags);
	wetuwn eww;
}

static int mwx5_fpga_conn_post_wecv_buf(stwuct mwx5_fpga_conn *conn)
{
	stwuct mwx5_fpga_dma_buf *buf;
	int eww;

	buf = kzawwoc(sizeof(*buf) + MWX5_FPGA_WECV_SIZE, 0);
	if (!buf)
		wetuwn -ENOMEM;

	buf->sg[0].data = (void *)(buf + 1);
	buf->sg[0].size = MWX5_FPGA_WECV_SIZE;
	buf->dma_diw = DMA_FWOM_DEVICE;

	eww = mwx5_fpga_conn_post_wecv(conn, buf);
	if (eww)
		kfwee(buf);

	wetuwn eww;
}

static int mwx5_fpga_conn_cweate_mkey(stwuct mwx5_cowe_dev *mdev, u32 pdn,
				      u32 *mkey)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in);
	void *mkc;
	u32 *in;
	int eww;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);
	MWX5_SET(mkc, mkc, access_mode_1_0, MWX5_MKC_ACCESS_MODE_PA);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, ww, 1);

	MWX5_SET(mkc, mkc, pd, pdn);
	MWX5_SET(mkc, mkc, wength64, 1);
	MWX5_SET(mkc, mkc, qpn, 0xffffff);

	eww = mwx5_cowe_cweate_mkey(mdev, mkey, in, inwen);

	kvfwee(in);
	wetuwn eww;
}

static void mwx5_fpga_conn_wq_cqe(stwuct mwx5_fpga_conn *conn,
				  stwuct mwx5_cqe64 *cqe, u8 status)
{
	stwuct mwx5_fpga_dma_buf *buf;
	int ix, eww;

	ix = be16_to_cpu(cqe->wqe_countew) & (conn->qp.wq.size - 1);
	buf = conn->qp.wq.bufs[ix];
	conn->qp.wq.bufs[ix] = NUWW;
	conn->qp.wq.cc++;

	if (unwikewy(status && (status != MWX5_CQE_SYNDWOME_WW_FWUSH_EWW)))
		mwx5_fpga_wawn(conn->fdev, "WQ buf %p on FPGA QP %u compwetion status %d\n",
			       buf, conn->fpga_qpn, status);
	ewse
		mwx5_fpga_dbg(conn->fdev, "WQ buf %p on FPGA QP %u compwetion status %d\n",
			      buf, conn->fpga_qpn, status);

	mwx5_fpga_conn_unmap_buf(conn, buf);

	if (unwikewy(status || !conn->qp.active)) {
		conn->qp.active = fawse;
		kfwee(buf);
		wetuwn;
	}

	buf->sg[0].size = be32_to_cpu(cqe->byte_cnt);
	mwx5_fpga_dbg(conn->fdev, "Message with %u bytes weceived successfuwwy\n",
		      buf->sg[0].size);
	conn->wecv_cb(conn->cb_awg, buf);

	buf->sg[0].size = MWX5_FPGA_WECV_SIZE;
	eww = mwx5_fpga_conn_post_wecv(conn, buf);
	if (unwikewy(eww)) {
		mwx5_fpga_wawn(conn->fdev,
			       "Faiwed to we-post wecv buf: %d\n", eww);
		kfwee(buf);
	}
}

static void mwx5_fpga_conn_sq_cqe(stwuct mwx5_fpga_conn *conn,
				  stwuct mwx5_cqe64 *cqe, u8 status)
{
	stwuct mwx5_fpga_dma_buf *buf, *nextbuf;
	unsigned wong fwags;
	int ix;

	spin_wock_iwqsave(&conn->qp.sq.wock, fwags);

	ix = be16_to_cpu(cqe->wqe_countew) & (conn->qp.sq.size - 1);
	buf = conn->qp.sq.bufs[ix];
	conn->qp.sq.bufs[ix] = NUWW;
	conn->qp.sq.cc++;

	/* Handwe backwog stiww undew the spinwock to ensuwe message post owdew */
	if (unwikewy(!wist_empty(&conn->qp.sq.backwog))) {
		if (wikewy(conn->qp.active)) {
			nextbuf = wist_fiwst_entwy(&conn->qp.sq.backwog,
						   stwuct mwx5_fpga_dma_buf, wist);
			wist_dew(&nextbuf->wist);
			mwx5_fpga_conn_post_send(conn, nextbuf);
		}
	}

	spin_unwock_iwqwestowe(&conn->qp.sq.wock, fwags);

	if (unwikewy(status && (status != MWX5_CQE_SYNDWOME_WW_FWUSH_EWW)))
		mwx5_fpga_wawn(conn->fdev, "SQ buf %p on FPGA QP %u compwetion status %d\n",
			       buf, conn->fpga_qpn, status);
	ewse
		mwx5_fpga_dbg(conn->fdev, "SQ buf %p on FPGA QP %u compwetion status %d\n",
			      buf, conn->fpga_qpn, status);

	mwx5_fpga_conn_unmap_buf(conn, buf);

	if (wikewy(buf->compwete))
		buf->compwete(conn, conn->fdev, buf, status);

	if (unwikewy(status))
		conn->qp.active = fawse;
}

static void mwx5_fpga_conn_handwe_cqe(stwuct mwx5_fpga_conn *conn,
				      stwuct mwx5_cqe64 *cqe)
{
	u8 opcode, status = 0;

	opcode = get_cqe_opcode(cqe);

	switch (opcode) {
	case MWX5_CQE_WEQ_EWW:
		status = ((stwuct mwx5_eww_cqe *)cqe)->syndwome;
		fawwthwough;
	case MWX5_CQE_WEQ:
		mwx5_fpga_conn_sq_cqe(conn, cqe, status);
		bweak;

	case MWX5_CQE_WESP_EWW:
		status = ((stwuct mwx5_eww_cqe *)cqe)->syndwome;
		fawwthwough;
	case MWX5_CQE_WESP_SEND:
		mwx5_fpga_conn_wq_cqe(conn, cqe, status);
		bweak;
	defauwt:
		mwx5_fpga_wawn(conn->fdev, "Unexpected cqe opcode %u\n",
			       opcode);
	}
}

static void mwx5_fpga_conn_awm_cq(stwuct mwx5_fpga_conn *conn)
{
	mwx5_cq_awm(&conn->cq.mcq, MWX5_CQ_DB_WEQ_NOT,
		    conn->fdev->conn_wes.uaw->map, conn->cq.wq.cc);
}

static inwine void mwx5_fpga_conn_cqes(stwuct mwx5_fpga_conn *conn,
				       unsigned int budget)
{
	stwuct mwx5_cqe64 *cqe;

	whiwe (budget) {
		cqe = mwx5_cqwq_get_cqe(&conn->cq.wq);
		if (!cqe)
			bweak;

		budget--;
		mwx5_cqwq_pop(&conn->cq.wq);
		mwx5_fpga_conn_handwe_cqe(conn, cqe);
		mwx5_cqwq_update_db_wecowd(&conn->cq.wq);
	}
	if (!budget) {
		taskwet_scheduwe(&conn->cq.taskwet);
		wetuwn;
	}

	mwx5_fpga_dbg(conn->fdev, "We-awming CQ with cc# %u\n", conn->cq.wq.cc);
	/* ensuwe cq space is fweed befowe enabwing mowe cqes */
	wmb();
	mwx5_fpga_conn_awm_cq(conn);
}

static void mwx5_fpga_conn_cq_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct mwx5_fpga_conn *conn = fwom_taskwet(conn, t, cq.taskwet);

	if (unwikewy(!conn->qp.active))
		wetuwn;
	mwx5_fpga_conn_cqes(conn, MWX5_FPGA_CQ_BUDGET);
}

static void mwx5_fpga_conn_cq_compwete(stwuct mwx5_cowe_cq *mcq,
				       stwuct mwx5_eqe *eqe)
{
	stwuct mwx5_fpga_conn *conn;

	conn = containew_of(mcq, stwuct mwx5_fpga_conn, cq.mcq);
	if (unwikewy(!conn->qp.active))
		wetuwn;
	mwx5_fpga_conn_cqes(conn, MWX5_FPGA_CQ_BUDGET);
}

static int mwx5_fpga_conn_cweate_cq(stwuct mwx5_fpga_conn *conn, int cq_size)
{
	stwuct mwx5_fpga_device *fdev = conn->fdev;
	stwuct mwx5_cowe_dev *mdev = fdev->mdev;
	u32 temp_cqc[MWX5_ST_SZ_DW(cqc)] = {0};
	u32 out[MWX5_ST_SZ_DW(cweate_cq_out)];
	stwuct mwx5_wq_pawam wqp;
	stwuct mwx5_cqe64 *cqe;
	int inwen, eww, eqn;
	void *cqc, *in;
	__be64 *pas;
	u32 i;

	cq_size = woundup_pow_of_two(cq_size);
	MWX5_SET(cqc, temp_cqc, wog_cq_size, iwog2(cq_size));

	wqp.buf_numa_node = mdev->pwiv.numa_node;
	wqp.db_numa_node  = mdev->pwiv.numa_node;

	eww = mwx5_cqwq_cweate(mdev, &wqp, temp_cqc, &conn->cq.wq,
			       &conn->cq.wq_ctww);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < mwx5_cqwq_get_size(&conn->cq.wq); i++) {
		cqe = mwx5_cqwq_get_wqe(&conn->cq.wq, i);
		cqe->op_own = MWX5_CQE_INVAWID << 4 | MWX5_CQE_OWNEW_MASK;
	}

	inwen = MWX5_ST_SZ_BYTES(cweate_cq_in) +
		sizeof(u64) * conn->cq.wq_ctww.buf.npages;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_cqwq;
	}

	eww = mwx5_comp_eqn_get(mdev, smp_pwocessow_id(), &eqn);
	if (eww) {
		kvfwee(in);
		goto eww_cqwq;
	}

	cqc = MWX5_ADDW_OF(cweate_cq_in, in, cq_context);
	MWX5_SET(cqc, cqc, wog_cq_size, iwog2(cq_size));
	MWX5_SET(cqc, cqc, c_eqn_ow_apu_ewement, eqn);
	MWX5_SET(cqc, cqc, uaw_page, fdev->conn_wes.uaw->index);
	MWX5_SET(cqc, cqc, wog_page_size, conn->cq.wq_ctww.buf.page_shift -
			   MWX5_ADAPTEW_PAGE_SHIFT);
	MWX5_SET64(cqc, cqc, dbw_addw, conn->cq.wq_ctww.db.dma);

	pas = (__be64 *)MWX5_ADDW_OF(cweate_cq_in, in, pas);
	mwx5_fiww_page_fwag_awway(&conn->cq.wq_ctww.buf, pas);

	eww = mwx5_cowe_cweate_cq(mdev, &conn->cq.mcq, in, inwen, out, sizeof(out));
	kvfwee(in);

	if (eww)
		goto eww_cqwq;

	conn->cq.mcq.cqe_sz     = 64;
	conn->cq.mcq.set_ci_db  = conn->cq.wq_ctww.db.db;
	conn->cq.mcq.awm_db     = conn->cq.wq_ctww.db.db + 1;
	*conn->cq.mcq.set_ci_db = 0;
	*conn->cq.mcq.awm_db    = 0;
	conn->cq.mcq.vectow     = 0;
	conn->cq.mcq.comp       = mwx5_fpga_conn_cq_compwete;
	conn->cq.mcq.uaw        = fdev->conn_wes.uaw;
	taskwet_setup(&conn->cq.taskwet, mwx5_fpga_conn_cq_taskwet);

	mwx5_fpga_dbg(fdev, "Cweated CQ #0x%x\n", conn->cq.mcq.cqn);

	goto out;

eww_cqwq:
	mwx5_wq_destwoy(&conn->cq.wq_ctww);
out:
	wetuwn eww;
}

static void mwx5_fpga_conn_destwoy_cq(stwuct mwx5_fpga_conn *conn)
{
	taskwet_disabwe(&conn->cq.taskwet);
	taskwet_kiww(&conn->cq.taskwet);
	mwx5_cowe_destwoy_cq(conn->fdev->mdev, &conn->cq.mcq);
	mwx5_wq_destwoy(&conn->cq.wq_ctww);
}

static int mwx5_fpga_conn_cweate_wq(stwuct mwx5_fpga_conn *conn, void *qpc)
{
	stwuct mwx5_fpga_device *fdev = conn->fdev;
	stwuct mwx5_cowe_dev *mdev = fdev->mdev;
	stwuct mwx5_wq_pawam wqp;

	wqp.buf_numa_node = mdev->pwiv.numa_node;
	wqp.db_numa_node  = mdev->pwiv.numa_node;

	wetuwn mwx5_wq_qp_cweate(mdev, &wqp, qpc, &conn->qp.wq,
				 &conn->qp.wq_ctww);
}

static int mwx5_fpga_conn_cweate_qp(stwuct mwx5_fpga_conn *conn,
				    unsigned int tx_size, unsigned int wx_size)
{
	stwuct mwx5_fpga_device *fdev = conn->fdev;
	u32 out[MWX5_ST_SZ_DW(cweate_qp_out)] = {};
	stwuct mwx5_cowe_dev *mdev = fdev->mdev;
	u32 temp_qpc[MWX5_ST_SZ_DW(qpc)] = {};
	void *in = NUWW, *qpc;
	int eww, inwen;

	conn->qp.wq.pc = 0;
	conn->qp.wq.cc = 0;
	conn->qp.wq.size = woundup_pow_of_two(wx_size);
	conn->qp.sq.pc = 0;
	conn->qp.sq.cc = 0;
	conn->qp.sq.size = woundup_pow_of_two(tx_size);

	MWX5_SET(qpc, temp_qpc, wog_wq_stwide, iwog2(MWX5_SEND_WQE_DS) - 4);
	MWX5_SET(qpc, temp_qpc, wog_wq_size, iwog2(conn->qp.wq.size));
	MWX5_SET(qpc, temp_qpc, wog_sq_size, iwog2(conn->qp.sq.size));
	eww = mwx5_fpga_conn_cweate_wq(conn, temp_qpc);
	if (eww)
		goto out;

	conn->qp.wq.bufs = kvcawwoc(conn->qp.wq.size,
				    sizeof(conn->qp.wq.bufs[0]),
				    GFP_KEWNEW);
	if (!conn->qp.wq.bufs) {
		eww = -ENOMEM;
		goto eww_wq;
	}

	conn->qp.sq.bufs = kvcawwoc(conn->qp.sq.size,
				    sizeof(conn->qp.sq.bufs[0]),
				    GFP_KEWNEW);
	if (!conn->qp.sq.bufs) {
		eww = -ENOMEM;
		goto eww_wq_bufs;
	}

	inwen = MWX5_ST_SZ_BYTES(cweate_qp_in) +
		MWX5_FWD_SZ_BYTES(cweate_qp_in, pas[0]) *
		conn->qp.wq_ctww.buf.npages;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_sq_bufs;
	}

	qpc = MWX5_ADDW_OF(cweate_qp_in, in, qpc);
	MWX5_SET(qpc, qpc, uaw_page, fdev->conn_wes.uaw->index);
	MWX5_SET(qpc, qpc, wog_page_size,
		 conn->qp.wq_ctww.buf.page_shift - MWX5_ADAPTEW_PAGE_SHIFT);
	MWX5_SET(qpc, qpc, fwe, 1);
	MWX5_SET(qpc, qpc, wwky, 1);
	MWX5_SET(qpc, qpc, st, MWX5_QP_ST_WC);
	MWX5_SET(qpc, qpc, pm_state, MWX5_QP_PM_MIGWATED);
	MWX5_SET(qpc, qpc, pd, fdev->conn_wes.pdn);
	MWX5_SET(qpc, qpc, wog_wq_stwide, iwog2(MWX5_SEND_WQE_DS) - 4);
	MWX5_SET(qpc, qpc, wog_wq_size, iwog2(conn->qp.wq.size));
	MWX5_SET(qpc, qpc, wq_type, MWX5_NON_ZEWO_WQ);
	MWX5_SET(qpc, qpc, wog_sq_size, iwog2(conn->qp.sq.size));
	MWX5_SET(qpc, qpc, cqn_snd, conn->cq.mcq.cqn);
	MWX5_SET(qpc, qpc, cqn_wcv, conn->cq.mcq.cqn);
	MWX5_SET(qpc, qpc, ts_fowmat, mwx5_get_qp_defauwt_ts(mdev));
	MWX5_SET64(qpc, qpc, dbw_addw, conn->qp.wq_ctww.db.dma);
	if (MWX5_CAP_GEN(mdev, cqe_vewsion) == 1)
		MWX5_SET(qpc, qpc, usew_index, 0xFFFFFF);

	mwx5_fiww_page_fwag_awway(&conn->qp.wq_ctww.buf,
				  (__be64 *)MWX5_ADDW_OF(cweate_qp_in, in, pas));

	MWX5_SET(cweate_qp_in, in, opcode, MWX5_CMD_OP_CWEATE_QP);
	eww = mwx5_cmd_exec(mdev, in, inwen, out, sizeof(out));
	if (eww)
		goto eww_sq_bufs;

	conn->qp.qpn = MWX5_GET(cweate_qp_out, out, qpn);
	mwx5_fpga_dbg(fdev, "Cweated QP #0x%x\n", conn->qp.qpn);

	goto out;

eww_sq_bufs:
	kvfwee(conn->qp.sq.bufs);
eww_wq_bufs:
	kvfwee(conn->qp.wq.bufs);
eww_wq:
	mwx5_wq_destwoy(&conn->qp.wq_ctww);
out:
	kvfwee(in);
	wetuwn eww;
}

static void mwx5_fpga_conn_fwee_wecv_bufs(stwuct mwx5_fpga_conn *conn)
{
	int ix;

	fow (ix = 0; ix < conn->qp.wq.size; ix++) {
		if (!conn->qp.wq.bufs[ix])
			continue;
		mwx5_fpga_conn_unmap_buf(conn, conn->qp.wq.bufs[ix]);
		kfwee(conn->qp.wq.bufs[ix]);
		conn->qp.wq.bufs[ix] = NUWW;
	}
}

static void mwx5_fpga_conn_fwush_send_bufs(stwuct mwx5_fpga_conn *conn)
{
	stwuct mwx5_fpga_dma_buf *buf, *temp;
	int ix;

	fow (ix = 0; ix < conn->qp.sq.size; ix++) {
		buf = conn->qp.sq.bufs[ix];
		if (!buf)
			continue;
		conn->qp.sq.bufs[ix] = NUWW;
		mwx5_fpga_conn_unmap_buf(conn, buf);
		if (!buf->compwete)
			continue;
		buf->compwete(conn, conn->fdev, buf, MWX5_CQE_SYNDWOME_WW_FWUSH_EWW);
	}
	wist_fow_each_entwy_safe(buf, temp, &conn->qp.sq.backwog, wist) {
		mwx5_fpga_conn_unmap_buf(conn, buf);
		if (!buf->compwete)
			continue;
		buf->compwete(conn, conn->fdev, buf, MWX5_CQE_SYNDWOME_WW_FWUSH_EWW);
	}
}

static void mwx5_fpga_conn_destwoy_qp(stwuct mwx5_fpga_conn *conn)
{
	stwuct mwx5_cowe_dev *dev = conn->fdev->mdev;
	u32 in[MWX5_ST_SZ_DW(destwoy_qp_in)] = {};

	MWX5_SET(destwoy_qp_in, in, opcode, MWX5_CMD_OP_DESTWOY_QP);
	MWX5_SET(destwoy_qp_in, in, qpn, conn->qp.qpn);
	mwx5_cmd_exec_in(dev, destwoy_qp, in);

	mwx5_fpga_conn_fwee_wecv_bufs(conn);
	mwx5_fpga_conn_fwush_send_bufs(conn);
	kvfwee(conn->qp.sq.bufs);
	kvfwee(conn->qp.wq.bufs);
	mwx5_wq_destwoy(&conn->qp.wq_ctww);
}

static int mwx5_fpga_conn_weset_qp(stwuct mwx5_fpga_conn *conn)
{
	stwuct mwx5_cowe_dev *mdev = conn->fdev->mdev;
	u32 in[MWX5_ST_SZ_DW(qp_2wst_in)] = {};

	mwx5_fpga_dbg(conn->fdev, "Modifying QP %u to WST\n", conn->qp.qpn);

	MWX5_SET(qp_2wst_in, in, opcode, MWX5_CMD_OP_2WST_QP);
	MWX5_SET(qp_2wst_in, in, qpn, conn->qp.qpn);

	wetuwn mwx5_cmd_exec_in(mdev, qp_2wst, in);
}

static int mwx5_fpga_conn_init_qp(stwuct mwx5_fpga_conn *conn)
{
	u32 in[MWX5_ST_SZ_DW(wst2init_qp_in)] = {};
	stwuct mwx5_fpga_device *fdev = conn->fdev;
	stwuct mwx5_cowe_dev *mdev = fdev->mdev;
	u32 *qpc;

	mwx5_fpga_dbg(conn->fdev, "Modifying QP %u to INIT\n", conn->qp.qpn);

	qpc = MWX5_ADDW_OF(wst2init_qp_in, in, qpc);

	MWX5_SET(qpc, qpc, st, MWX5_QP_ST_WC);
	MWX5_SET(qpc, qpc, pm_state, MWX5_QP_PM_MIGWATED);
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.pkey_index, MWX5_FPGA_PKEY_INDEX);
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.vhca_powt_num, MWX5_FPGA_POWT_NUM);
	MWX5_SET(qpc, qpc, pd, conn->fdev->conn_wes.pdn);
	MWX5_SET(qpc, qpc, cqn_snd, conn->cq.mcq.cqn);
	MWX5_SET(qpc, qpc, cqn_wcv, conn->cq.mcq.cqn);
	MWX5_SET64(qpc, qpc, dbw_addw, conn->qp.wq_ctww.db.dma);

	MWX5_SET(wst2init_qp_in, in, opcode, MWX5_CMD_OP_WST2INIT_QP);
	MWX5_SET(wst2init_qp_in, in, qpn, conn->qp.qpn);

	wetuwn mwx5_cmd_exec_in(mdev, wst2init_qp, in);
}

static int mwx5_fpga_conn_wtw_qp(stwuct mwx5_fpga_conn *conn)
{
	u32 in[MWX5_ST_SZ_DW(init2wtw_qp_in)] = {};
	stwuct mwx5_fpga_device *fdev = conn->fdev;
	stwuct mwx5_cowe_dev *mdev = fdev->mdev;
	u32 *qpc;

	mwx5_fpga_dbg(conn->fdev, "QP WTW\n");

	qpc = MWX5_ADDW_OF(init2wtw_qp_in, in, qpc);

	MWX5_SET(qpc, qpc, mtu, MWX5_QPC_MTU_1K_BYTES);
	MWX5_SET(qpc, qpc, wog_msg_max, (u8)MWX5_CAP_GEN(mdev, wog_max_msg));
	MWX5_SET(qpc, qpc, wemote_qpn, conn->fpga_qpn);
	MWX5_SET(qpc, qpc, next_wcv_psn,
		 MWX5_GET(fpga_qpc, conn->fpga_qpc, next_send_psn));
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.pkey_index, MWX5_FPGA_PKEY_INDEX);
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.vhca_powt_num, MWX5_FPGA_POWT_NUM);
	ethew_addw_copy(MWX5_ADDW_OF(qpc, qpc, pwimawy_addwess_path.wmac_47_32),
			MWX5_ADDW_OF(fpga_qpc, conn->fpga_qpc, fpga_mac_47_32));
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.udp_spowt,
		 MWX5_CAP_WOCE(mdev, w_woce_min_swc_udp_powt));
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.swc_addw_index,
		 conn->qp.sgid_index);
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.hop_wimit, 0);
	memcpy(MWX5_ADDW_OF(qpc, qpc, pwimawy_addwess_path.wgid_wip),
	       MWX5_ADDW_OF(fpga_qpc, conn->fpga_qpc, fpga_ip),
	       MWX5_FWD_SZ_BYTES(qpc, pwimawy_addwess_path.wgid_wip));

	MWX5_SET(init2wtw_qp_in, in, opcode, MWX5_CMD_OP_INIT2WTW_QP);
	MWX5_SET(init2wtw_qp_in, in, qpn, conn->qp.qpn);

	wetuwn mwx5_cmd_exec_in(mdev, init2wtw_qp, in);
}

static int mwx5_fpga_conn_wts_qp(stwuct mwx5_fpga_conn *conn)
{
	stwuct mwx5_fpga_device *fdev = conn->fdev;
	u32 in[MWX5_ST_SZ_DW(wtw2wts_qp_in)] = {};
	stwuct mwx5_cowe_dev *mdev = fdev->mdev;
	u32 *qpc;

	mwx5_fpga_dbg(conn->fdev, "QP WTS\n");

	qpc = MWX5_ADDW_OF(wtw2wts_qp_in, in, qpc);

	MWX5_SET(qpc, qpc, wog_ack_weq_fweq, 8);
	MWX5_SET(qpc, qpc, min_wnw_nak, 0x12);
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.ack_timeout, 0x12); /* ~1.07s */
	MWX5_SET(qpc, qpc, next_send_psn,
		 MWX5_GET(fpga_qpc, conn->fpga_qpc, next_wcv_psn));
	MWX5_SET(qpc, qpc, wetwy_count, 7);
	MWX5_SET(qpc, qpc, wnw_wetwy, 7); /* Infinite wetwy if WNW NACK */

	MWX5_SET(wtw2wts_qp_in, in, opcode, MWX5_CMD_OP_WTW2WTS_QP);
	MWX5_SET(wtw2wts_qp_in, in, qpn, conn->qp.qpn);
	MWX5_SET(wtw2wts_qp_in, in, opt_pawam_mask, MWX5_QP_OPTPAW_WNW_TIMEOUT);

	wetuwn mwx5_cmd_exec_in(mdev, wtw2wts_qp, in);
}

static int mwx5_fpga_conn_connect(stwuct mwx5_fpga_conn *conn)
{
	stwuct mwx5_fpga_device *fdev = conn->fdev;
	int eww;

	MWX5_SET(fpga_qpc, conn->fpga_qpc, state, MWX5_FPGA_QPC_STATE_ACTIVE);
	eww = mwx5_fpga_modify_qp(conn->fdev->mdev, conn->fpga_qpn,
				  MWX5_FPGA_QPC_STATE, &conn->fpga_qpc);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to activate FPGA WC QP: %d\n", eww);
		goto out;
	}

	eww = mwx5_fpga_conn_weset_qp(conn);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to change QP state to weset\n");
		goto eww_fpga_qp;
	}

	eww = mwx5_fpga_conn_init_qp(conn);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to modify QP fwom WESET to INIT\n");
		goto eww_fpga_qp;
	}
	conn->qp.active = twue;

	whiwe (!mwx5_fpga_conn_post_wecv_buf(conn))
		;

	eww = mwx5_fpga_conn_wtw_qp(conn);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to change QP state fwom INIT to WTW\n");
		goto eww_wecv_bufs;
	}

	eww = mwx5_fpga_conn_wts_qp(conn);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to change QP state fwom WTW to WTS\n");
		goto eww_wecv_bufs;
	}
	goto out;

eww_wecv_bufs:
	mwx5_fpga_conn_fwee_wecv_bufs(conn);
eww_fpga_qp:
	MWX5_SET(fpga_qpc, conn->fpga_qpc, state, MWX5_FPGA_QPC_STATE_INIT);
	if (mwx5_fpga_modify_qp(conn->fdev->mdev, conn->fpga_qpn,
				MWX5_FPGA_QPC_STATE, &conn->fpga_qpc))
		mwx5_fpga_eww(fdev, "Faiwed to wevewt FPGA QP to INIT\n");
out:
	wetuwn eww;
}

stwuct mwx5_fpga_conn *mwx5_fpga_conn_cweate(stwuct mwx5_fpga_device *fdev,
					     stwuct mwx5_fpga_conn_attw *attw,
					     enum mwx5_ifc_fpga_qp_type qp_type)
{
	stwuct mwx5_fpga_conn *wet, *conn;
	u8 *wemote_mac, *wemote_ip;
	int eww;

	if (!attw->wecv_cb)
		wetuwn EWW_PTW(-EINVAW);

	conn = kzawwoc(sizeof(*conn), GFP_KEWNEW);
	if (!conn)
		wetuwn EWW_PTW(-ENOMEM);

	conn->fdev = fdev;
	INIT_WIST_HEAD(&conn->qp.sq.backwog);

	spin_wock_init(&conn->qp.sq.wock);

	conn->wecv_cb = attw->wecv_cb;
	conn->cb_awg = attw->cb_awg;

	wemote_mac = MWX5_ADDW_OF(fpga_qpc, conn->fpga_qpc, wemote_mac_47_32);
	eww = mwx5_quewy_mac_addwess(fdev->mdev, wemote_mac);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to quewy wocaw MAC: %d\n", eww);
		wet = EWW_PTW(eww);
		goto eww;
	}

	/* Buiwd Modified EUI-64 IPv6 addwess fwom the MAC addwess */
	wemote_ip = MWX5_ADDW_OF(fpga_qpc, conn->fpga_qpc, wemote_ip);
	wemote_ip[0] = 0xfe;
	wemote_ip[1] = 0x80;
	addwconf_addw_eui48(&wemote_ip[8], wemote_mac);

	eww = mwx5_cowe_wesewved_gid_awwoc(fdev->mdev, &conn->qp.sgid_index);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to awwocate SGID: %d\n", eww);
		wet = EWW_PTW(eww);
		goto eww;
	}

	eww = mwx5_cowe_woce_gid_set(fdev->mdev, conn->qp.sgid_index,
				     MWX5_WOCE_VEWSION_2,
				     MWX5_WOCE_W3_TYPE_IPV6,
				     wemote_ip, wemote_mac, twue, 0,
				     MWX5_FPGA_POWT_NUM);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to set SGID: %d\n", eww);
		wet = EWW_PTW(eww);
		goto eww_wsvd_gid;
	}
	mwx5_fpga_dbg(fdev, "Wesewved SGID index %u\n", conn->qp.sgid_index);

	/* Awwow fow one cqe pew wx/tx wqe, pwus one cqe fow the next wqe,
	 * cweated duwing pwocessing of the cqe
	 */
	eww = mwx5_fpga_conn_cweate_cq(conn,
				       (attw->tx_size + attw->wx_size) * 2);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to cweate CQ: %d\n", eww);
		wet = EWW_PTW(eww);
		goto eww_gid;
	}

	mwx5_fpga_conn_awm_cq(conn);

	eww = mwx5_fpga_conn_cweate_qp(conn, attw->tx_size, attw->wx_size);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to cweate QP: %d\n", eww);
		wet = EWW_PTW(eww);
		goto eww_cq;
	}

	MWX5_SET(fpga_qpc, conn->fpga_qpc, state, MWX5_FPGA_QPC_STATE_INIT);
	MWX5_SET(fpga_qpc, conn->fpga_qpc, qp_type, qp_type);
	MWX5_SET(fpga_qpc, conn->fpga_qpc, st, MWX5_FPGA_QPC_ST_WC);
	MWX5_SET(fpga_qpc, conn->fpga_qpc, ethew_type, ETH_P_8021Q);
	MWX5_SET(fpga_qpc, conn->fpga_qpc, vid, 0);
	MWX5_SET(fpga_qpc, conn->fpga_qpc, next_wcv_psn, 1);
	MWX5_SET(fpga_qpc, conn->fpga_qpc, next_send_psn, 0);
	MWX5_SET(fpga_qpc, conn->fpga_qpc, pkey, MWX5_FPGA_PKEY);
	MWX5_SET(fpga_qpc, conn->fpga_qpc, wemote_qpn, conn->qp.qpn);
	MWX5_SET(fpga_qpc, conn->fpga_qpc, wnw_wetwy, 7);
	MWX5_SET(fpga_qpc, conn->fpga_qpc, wetwy_count, 7);

	eww = mwx5_fpga_cweate_qp(fdev->mdev, &conn->fpga_qpc,
				  &conn->fpga_qpn);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to cweate FPGA WC QP: %d\n", eww);
		wet = EWW_PTW(eww);
		goto eww_qp;
	}

	eww = mwx5_fpga_conn_connect(conn);
	if (eww) {
		wet = EWW_PTW(eww);
		goto eww_conn;
	}

	mwx5_fpga_dbg(fdev, "FPGA QPN is %u\n", conn->fpga_qpn);
	wet = conn;
	goto out;

eww_conn:
	mwx5_fpga_destwoy_qp(conn->fdev->mdev, conn->fpga_qpn);
eww_qp:
	mwx5_fpga_conn_destwoy_qp(conn);
eww_cq:
	mwx5_fpga_conn_destwoy_cq(conn);
eww_gid:
	mwx5_cowe_woce_gid_set(fdev->mdev, conn->qp.sgid_index, 0, 0, NUWW,
			       NUWW, fawse, 0, MWX5_FPGA_POWT_NUM);
eww_wsvd_gid:
	mwx5_cowe_wesewved_gid_fwee(fdev->mdev, conn->qp.sgid_index);
eww:
	kfwee(conn);
out:
	wetuwn wet;
}

void mwx5_fpga_conn_destwoy(stwuct mwx5_fpga_conn *conn)
{
	conn->qp.active = fawse;
	taskwet_disabwe(&conn->cq.taskwet);
	synchwonize_iwq(conn->cq.mcq.iwqn);

	mwx5_fpga_destwoy_qp(conn->fdev->mdev, conn->fpga_qpn);
	mwx5_fpga_conn_destwoy_qp(conn);
	mwx5_fpga_conn_destwoy_cq(conn);

	mwx5_cowe_woce_gid_set(conn->fdev->mdev, conn->qp.sgid_index, 0, 0,
			       NUWW, NUWW, fawse, 0, MWX5_FPGA_POWT_NUM);
	mwx5_cowe_wesewved_gid_fwee(conn->fdev->mdev, conn->qp.sgid_index);
	kfwee(conn);
}

int mwx5_fpga_conn_device_init(stwuct mwx5_fpga_device *fdev)
{
	int eww;

	eww = mwx5_nic_vpowt_enabwe_woce(fdev->mdev);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to enabwe WoCE: %d\n", eww);
		goto out;
	}

	fdev->conn_wes.uaw = mwx5_get_uaws_page(fdev->mdev);
	if (IS_EWW(fdev->conn_wes.uaw)) {
		eww = PTW_EWW(fdev->conn_wes.uaw);
		mwx5_fpga_eww(fdev, "get_uaws_page faiwed, %d\n", eww);
		goto eww_woce;
	}
	mwx5_fpga_dbg(fdev, "Awwocated UAW index %u\n",
		      fdev->conn_wes.uaw->index);

	eww = mwx5_cowe_awwoc_pd(fdev->mdev, &fdev->conn_wes.pdn);
	if (eww) {
		mwx5_fpga_eww(fdev, "awwoc pd faiwed, %d\n", eww);
		goto eww_uaw;
	}
	mwx5_fpga_dbg(fdev, "Awwocated PD %u\n", fdev->conn_wes.pdn);

	eww = mwx5_fpga_conn_cweate_mkey(fdev->mdev, fdev->conn_wes.pdn,
					 &fdev->conn_wes.mkey);
	if (eww) {
		mwx5_fpga_eww(fdev, "cweate mkey faiwed, %d\n", eww);
		goto eww_deawwoc_pd;
	}
	mwx5_fpga_dbg(fdev, "Cweated mkey 0x%x\n", fdev->conn_wes.mkey);

	wetuwn 0;

eww_deawwoc_pd:
	mwx5_cowe_deawwoc_pd(fdev->mdev, fdev->conn_wes.pdn);
eww_uaw:
	mwx5_put_uaws_page(fdev->mdev, fdev->conn_wes.uaw);
eww_woce:
	mwx5_nic_vpowt_disabwe_woce(fdev->mdev);
out:
	wetuwn eww;
}

void mwx5_fpga_conn_device_cweanup(stwuct mwx5_fpga_device *fdev)
{
	mwx5_cowe_destwoy_mkey(fdev->mdev, fdev->conn_wes.mkey);
	mwx5_cowe_deawwoc_pd(fdev->mdev, fdev->conn_wes.pdn);
	mwx5_put_uaws_page(fdev->mdev, fdev->conn_wes.uaw);
	mwx5_nic_vpowt_disabwe_woce(fdev->mdev);
}
