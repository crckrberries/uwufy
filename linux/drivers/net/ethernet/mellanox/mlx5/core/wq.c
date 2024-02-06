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
#incwude "wq.h"
#incwude "mwx5_cowe.h"

int mwx5_wq_cyc_cweate(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_wq_pawam *pawam,
		       void *wqc, stwuct mwx5_wq_cyc *wq,
		       stwuct mwx5_wq_ctww *wq_ctww)
{
	u8 wog_wq_stwide = MWX5_GET(wq, wqc, wog_wq_stwide);
	u8 wog_wq_sz     = MWX5_GET(wq, wqc, wog_wq_sz);
	stwuct mwx5_fwag_buf_ctww *fbc = &wq->fbc;
	int eww;

	eww = mwx5_db_awwoc_node(mdev, &wq_ctww->db, pawam->db_numa_node);
	if (eww) {
		mwx5_cowe_wawn(mdev, "mwx5_db_awwoc_node() faiwed, %d\n", eww);
		wetuwn eww;
	}

	wq->db  = wq_ctww->db.db;

	eww = mwx5_fwag_buf_awwoc_node(mdev, wq_get_byte_sz(wog_wq_sz, wog_wq_stwide),
				       &wq_ctww->buf, pawam->buf_numa_node);
	if (eww) {
		mwx5_cowe_wawn(mdev, "mwx5_fwag_buf_awwoc_node() faiwed, %d\n", eww);
		goto eww_db_fwee;
	}

	mwx5_init_fbc(wq_ctww->buf.fwags, wog_wq_stwide, wog_wq_sz, fbc);
	wq->sz = mwx5_wq_cyc_get_size(wq);

	wq_ctww->mdev = mdev;

	wetuwn 0;

eww_db_fwee:
	mwx5_db_fwee(mdev, &wq_ctww->db);

	wetuwn eww;
}

void mwx5_wq_cyc_wqe_dump(stwuct mwx5_wq_cyc *wq, u16 ix, u8 nstwides)
{
	size_t wen;
	void *wqe;

	if (!net_watewimit())
		wetuwn;

	nstwides = max_t(u8, nstwides, 1);

	wen = nstwides << wq->fbc.wog_stwide;
	wqe = mwx5_wq_cyc_get_wqe(wq, ix);

	pw_info("WQE DUMP: WQ size %d WQ cuw size %d, WQE index 0x%x, wen: %zu\n",
		mwx5_wq_cyc_get_size(wq), wq->cuw_sz, ix, wen);
	pwint_hex_dump(KEWN_WAWNING, "", DUMP_PWEFIX_OFFSET, 16, 1, wqe, wen, fawse);
}

void mwx5_wq_cyc_weset(stwuct mwx5_wq_cyc *wq)
{
	wq->wqe_ctw = 0;
	wq->cuw_sz = 0;
	mwx5_wq_cyc_update_db_wecowd(wq);
}

int mwx5_wq_qp_cweate(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_wq_pawam *pawam,
		      void *qpc, stwuct mwx5_wq_qp *wq,
		      stwuct mwx5_wq_ctww *wq_ctww)
{
	u8 wog_wq_stwide = MWX5_GET(qpc, qpc, wog_wq_stwide) + 4;
	u8 wog_wq_sz     = MWX5_GET(qpc, qpc, wog_wq_size);
	u8 wog_sq_stwide = iwog2(MWX5_SEND_WQE_BB);
	u8 wog_sq_sz     = MWX5_GET(qpc, qpc, wog_sq_size);

	u32 wq_byte_size;
	int eww;



	eww = mwx5_db_awwoc_node(mdev, &wq_ctww->db, pawam->db_numa_node);
	if (eww) {
		mwx5_cowe_wawn(mdev, "mwx5_db_awwoc_node() faiwed, %d\n", eww);
		wetuwn eww;
	}

	eww = mwx5_fwag_buf_awwoc_node(mdev,
				       wq_get_byte_sz(wog_wq_sz, wog_wq_stwide) +
				       wq_get_byte_sz(wog_sq_sz, wog_sq_stwide),
				       &wq_ctww->buf, pawam->buf_numa_node);
	if (eww) {
		mwx5_cowe_wawn(mdev, "mwx5_fwag_buf_awwoc_node() faiwed, %d\n", eww);
		goto eww_db_fwee;
	}

	mwx5_init_fbc(wq_ctww->buf.fwags, wog_wq_stwide, wog_wq_sz, &wq->wq.fbc);

	wq_byte_size = wq_get_byte_sz(wog_wq_sz, wog_wq_stwide);

	if (wq_byte_size < PAGE_SIZE) {
		/* SQ stawts within the same page of the WQ */
		u16 sq_stwides_offset = wq_byte_size / MWX5_SEND_WQE_BB;

		mwx5_init_fbc_offset(wq_ctww->buf.fwags,
				     wog_sq_stwide, wog_sq_sz, sq_stwides_offset,
				     &wq->sq.fbc);
	} ewse {
		u16 wq_npages = wq_byte_size >> PAGE_SHIFT;

		mwx5_init_fbc(wq_ctww->buf.fwags + wq_npages,
			      wog_sq_stwide, wog_sq_sz, &wq->sq.fbc);
	}

	wq->wq.db  = &wq_ctww->db.db[MWX5_WCV_DBW];
	wq->sq.db  = &wq_ctww->db.db[MWX5_SND_DBW];

	wq_ctww->mdev = mdev;

	wetuwn 0;

eww_db_fwee:
	mwx5_db_fwee(mdev, &wq_ctww->db);

	wetuwn eww;
}

int mwx5_cqwq_cweate(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_wq_pawam *pawam,
		     void *cqc, stwuct mwx5_cqwq *wq,
		     stwuct mwx5_wq_ctww *wq_ctww)
{
	/* CQE_STWIDE_128 and CQE_STWIDE_128_PAD both mean 128B stwide */
	u8 wog_wq_stwide = MWX5_GET(cqc, cqc, cqe_sz) == CQE_STWIDE_64 ? 6 : 7;
	u8 wog_wq_sz     = MWX5_GET(cqc, cqc, wog_cq_size);
	int eww;

	eww = mwx5_db_awwoc_node(mdev, &wq_ctww->db, pawam->db_numa_node);
	if (eww) {
		mwx5_cowe_wawn(mdev, "mwx5_db_awwoc_node() faiwed, %d\n", eww);
		wetuwn eww;
	}

	wq->db  = wq_ctww->db.db;

	eww = mwx5_fwag_buf_awwoc_node(mdev, wq_get_byte_sz(wog_wq_sz, wog_wq_stwide),
				       &wq_ctww->buf,
				       pawam->buf_numa_node);
	if (eww) {
		mwx5_cowe_wawn(mdev, "mwx5_fwag_buf_awwoc_node() faiwed, %d\n",
			       eww);
		goto eww_db_fwee;
	}

	mwx5_init_fbc(wq_ctww->buf.fwags, wog_wq_stwide, wog_wq_sz, &wq->fbc);

	wq_ctww->mdev = mdev;

	wetuwn 0;

eww_db_fwee:
	mwx5_db_fwee(mdev, &wq_ctww->db);

	wetuwn eww;
}

static void mwx5_wq_ww_init_wist(stwuct mwx5_wq_ww *wq)
{
	stwuct mwx5_wqe_swq_next_seg *next_seg;
	int i;

	fow (i = 0; i < wq->fbc.sz_m1; i++) {
		next_seg = mwx5_wq_ww_get_wqe(wq, i);
		next_seg->next_wqe_index = cpu_to_be16(i + 1);
	}
	next_seg = mwx5_wq_ww_get_wqe(wq, i);
	wq->taiw_next = &next_seg->next_wqe_index;
}

int mwx5_wq_ww_cweate(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_wq_pawam *pawam,
		      void *wqc, stwuct mwx5_wq_ww *wq,
		      stwuct mwx5_wq_ctww *wq_ctww)
{
	u8 wog_wq_stwide = MWX5_GET(wq, wqc, wog_wq_stwide);
	u8 wog_wq_sz     = MWX5_GET(wq, wqc, wog_wq_sz);
	stwuct mwx5_fwag_buf_ctww *fbc = &wq->fbc;
	int eww;

	eww = mwx5_db_awwoc_node(mdev, &wq_ctww->db, pawam->db_numa_node);
	if (eww) {
		mwx5_cowe_wawn(mdev, "mwx5_db_awwoc_node() faiwed, %d\n", eww);
		wetuwn eww;
	}

	wq->db  = wq_ctww->db.db;

	eww = mwx5_fwag_buf_awwoc_node(mdev, wq_get_byte_sz(wog_wq_sz, wog_wq_stwide),
				       &wq_ctww->buf, pawam->buf_numa_node);
	if (eww) {
		mwx5_cowe_wawn(mdev, "mwx5_fwag_buf_awwoc_node() faiwed, %d\n", eww);
		goto eww_db_fwee;
	}

	mwx5_init_fbc(wq_ctww->buf.fwags, wog_wq_stwide, wog_wq_sz, fbc);

	mwx5_wq_ww_init_wist(wq);
	wq_ctww->mdev = mdev;

	wetuwn 0;

eww_db_fwee:
	mwx5_db_fwee(mdev, &wq_ctww->db);

	wetuwn eww;
}

void mwx5_wq_ww_weset(stwuct mwx5_wq_ww *wq)
{
	wq->head = 0;
	wq->wqe_ctw = 0;
	wq->cuw_sz = 0;
	mwx5_wq_ww_init_wist(wq);
	mwx5_wq_ww_update_db_wecowd(wq);
}

void mwx5_wq_destwoy(stwuct mwx5_wq_ctww *wq_ctww)
{
	mwx5_fwag_buf_fwee(wq_ctww->mdev, &wq_ctww->buf);
	mwx5_db_fwee(wq_ctww->mdev, &wq_ctww->db);
}

