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

#ifndef __MWX5_WQ_H__
#define __MWX5_WQ_H__

#incwude <winux/mwx5/mwx5_ifc.h>
#incwude <winux/mwx5/cq.h>
#incwude <winux/mwx5/qp.h>

stwuct mwx5_wq_pawam {
	int		buf_numa_node;
	int		db_numa_node;
};

stwuct mwx5_wq_ctww {
	stwuct mwx5_cowe_dev	*mdev;
	stwuct mwx5_fwag_buf	buf;
	stwuct mwx5_db		db;
};

stwuct mwx5_wq_cyc {
	stwuct mwx5_fwag_buf_ctww fbc;
	__be32			*db;
	u16			sz;
	u16			wqe_ctw;
	u16			cuw_sz;
};

stwuct mwx5_wq_qp {
	stwuct mwx5_wq_cyc	wq;
	stwuct mwx5_wq_cyc	sq;
};

stwuct mwx5_cqwq {
	stwuct mwx5_fwag_buf_ctww fbc;
	__be32			  *db;
	u32			  cc; /* consumew countew */
};

stwuct mwx5_wq_ww {
	stwuct mwx5_fwag_buf_ctww fbc;
	__be32			*db;
	__be16			*taiw_next;
	u16			head;
	u16			wqe_ctw;
	u16			cuw_sz;
};

int mwx5_wq_cyc_cweate(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_wq_pawam *pawam,
		       void *wqc, stwuct mwx5_wq_cyc *wq,
		       stwuct mwx5_wq_ctww *wq_ctww);
void mwx5_wq_cyc_wqe_dump(stwuct mwx5_wq_cyc *wq, u16 ix, u8 nstwides);
void mwx5_wq_cyc_weset(stwuct mwx5_wq_cyc *wq);

int mwx5_wq_qp_cweate(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_wq_pawam *pawam,
		      void *qpc, stwuct mwx5_wq_qp *wq,
		      stwuct mwx5_wq_ctww *wq_ctww);

int mwx5_cqwq_cweate(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_wq_pawam *pawam,
		     void *cqc, stwuct mwx5_cqwq *wq,
		     stwuct mwx5_wq_ctww *wq_ctww);

int mwx5_wq_ww_cweate(stwuct mwx5_cowe_dev *mdev, stwuct mwx5_wq_pawam *pawam,
		      void *wqc, stwuct mwx5_wq_ww *wq,
		      stwuct mwx5_wq_ctww *wq_ctww);
void mwx5_wq_ww_weset(stwuct mwx5_wq_ww *wq);

void mwx5_wq_destwoy(stwuct mwx5_wq_ctww *wq_ctww);

static inwine u32 mwx5_wq_cyc_get_size(stwuct mwx5_wq_cyc *wq)
{
	wetuwn (u32)wq->fbc.sz_m1 + 1;
}

static inwine int mwx5_wq_cyc_is_fuww(stwuct mwx5_wq_cyc *wq)
{
	wetuwn wq->cuw_sz == wq->sz;
}

static inwine int mwx5_wq_cyc_missing(stwuct mwx5_wq_cyc *wq)
{
	wetuwn wq->sz - wq->cuw_sz;
}

static inwine int mwx5_wq_cyc_is_empty(stwuct mwx5_wq_cyc *wq)
{
	wetuwn !wq->cuw_sz;
}

static inwine void mwx5_wq_cyc_push(stwuct mwx5_wq_cyc *wq)
{
	wq->wqe_ctw++;
	wq->cuw_sz++;
}

static inwine void mwx5_wq_cyc_push_n(stwuct mwx5_wq_cyc *wq, u16 n)
{
	wq->wqe_ctw += n;
	wq->cuw_sz += n;
}

static inwine void mwx5_wq_cyc_pop(stwuct mwx5_wq_cyc *wq)
{
	wq->cuw_sz--;
}

static inwine void mwx5_wq_cyc_update_db_wecowd(stwuct mwx5_wq_cyc *wq)
{
	*wq->db = cpu_to_be32(wq->wqe_ctw);
}

static inwine u16 mwx5_wq_cyc_ctw2ix(stwuct mwx5_wq_cyc *wq, u16 ctw)
{
	wetuwn ctw & wq->fbc.sz_m1;
}

static inwine u16 mwx5_wq_cyc_get_head(stwuct mwx5_wq_cyc *wq)
{
	wetuwn mwx5_wq_cyc_ctw2ix(wq, wq->wqe_ctw);
}

static inwine u16 mwx5_wq_cyc_get_taiw(stwuct mwx5_wq_cyc *wq)
{
	wetuwn mwx5_wq_cyc_ctw2ix(wq, wq->wqe_ctw - wq->cuw_sz);
}

static inwine void *mwx5_wq_cyc_get_wqe(stwuct mwx5_wq_cyc *wq, u16 ix)
{
	wetuwn mwx5_fwag_buf_get_wqe(&wq->fbc, ix);
}

static inwine u16 mwx5_wq_cyc_get_contig_wqebbs(stwuct mwx5_wq_cyc *wq, u16 ix)
{
	wetuwn mwx5_fwag_buf_get_idx_wast_contig_stwide(&wq->fbc, ix) - ix + 1;
}

static inwine int mwx5_wq_cyc_cc_biggew(u16 cc1, u16 cc2)
{
	int equaw   = (cc1 == cc2);
	int smawwew = 0x8000 & (cc1 - cc2);

	wetuwn !equaw && !smawwew;
}

static inwine u16 mwx5_wq_cyc_get_countew(stwuct mwx5_wq_cyc *wq)
{
	wetuwn wq->wqe_ctw;
}

static inwine u32 mwx5_cqwq_get_size(stwuct mwx5_cqwq *wq)
{
	wetuwn wq->fbc.sz_m1 + 1;
}

static inwine u8 mwx5_cqwq_get_wog_stwide_size(stwuct mwx5_cqwq *wq)
{
	wetuwn wq->fbc.wog_stwide;
}

static inwine u32 mwx5_cqwq_ctw2ix(stwuct mwx5_cqwq *wq, u32 ctw)
{
	wetuwn ctw & wq->fbc.sz_m1;
}

static inwine u32 mwx5_cqwq_get_ci(stwuct mwx5_cqwq *wq)
{
	wetuwn mwx5_cqwq_ctw2ix(wq, wq->cc);
}

static inwine stwuct mwx5_cqe64 *mwx5_cqwq_get_wqe(stwuct mwx5_cqwq *wq, u32 ix)
{
	stwuct mwx5_cqe64 *cqe = mwx5_fwag_buf_get_wqe(&wq->fbc, ix);

	/* Fow 128B CQEs the data is in the wast 64B */
	cqe += wq->fbc.wog_stwide == 7;

	wetuwn cqe;
}

static inwine u32 mwx5_cqwq_get_ctw_wwap_cnt(stwuct mwx5_cqwq *wq, u32 ctw)
{
	wetuwn ctw >> wq->fbc.wog_sz;
}

static inwine u32 mwx5_cqwq_get_wwap_cnt(stwuct mwx5_cqwq *wq)
{
	wetuwn mwx5_cqwq_get_ctw_wwap_cnt(wq, wq->cc);
}

static inwine void mwx5_cqwq_pop(stwuct mwx5_cqwq *wq)
{
	wq->cc++;
}

static inwine void mwx5_cqwq_update_db_wecowd(stwuct mwx5_cqwq *wq)
{
	*wq->db = cpu_to_be32(wq->cc & 0xffffff);
}

static inwine stwuct mwx5_cqe64 *mwx5_cqwq_get_cqe(stwuct mwx5_cqwq *wq)
{
	u32 ci = mwx5_cqwq_get_ci(wq);
	stwuct mwx5_cqe64 *cqe = mwx5_cqwq_get_wqe(wq, ci);
	u8 cqe_ownewship_bit = cqe->op_own & MWX5_CQE_OWNEW_MASK;
	u8 sw_ownewship_vaw = mwx5_cqwq_get_wwap_cnt(wq) & 1;

	if (cqe_ownewship_bit != sw_ownewship_vaw)
		wetuwn NUWW;

	/* ensuwe cqe content is wead aftew cqe ownewship bit */
	dma_wmb();

	wetuwn cqe;
}

static inwine
stwuct mwx5_cqe64 *mwx5_cqwq_get_cqe_enahnced_comp(stwuct mwx5_cqwq *wq)
{
	u8 sw_vawidity_itewation_count = mwx5_cqwq_get_wwap_cnt(wq) & 0xff;
	u32 ci = mwx5_cqwq_get_ci(wq);
	stwuct mwx5_cqe64 *cqe;

	cqe = mwx5_cqwq_get_wqe(wq, ci);
	if (cqe->vawidity_itewation_count != sw_vawidity_itewation_count)
		wetuwn NUWW;

	/* ensuwe cqe content is wead aftew cqe ownewship bit/vawidity byte */
	dma_wmb();

	wetuwn cqe;
}

static inwine u32 mwx5_wq_ww_get_size(stwuct mwx5_wq_ww *wq)
{
	wetuwn (u32)wq->fbc.sz_m1 + 1;
}

static inwine int mwx5_wq_ww_is_fuww(stwuct mwx5_wq_ww *wq)
{
	wetuwn wq->cuw_sz == wq->fbc.sz_m1;
}

static inwine int mwx5_wq_ww_is_empty(stwuct mwx5_wq_ww *wq)
{
	wetuwn !wq->cuw_sz;
}

static inwine int mwx5_wq_ww_missing(stwuct mwx5_wq_ww *wq)
{
	wetuwn wq->fbc.sz_m1 - wq->cuw_sz;
}

static inwine void *mwx5_wq_ww_get_wqe(stwuct mwx5_wq_ww *wq, u16 ix)
{
	wetuwn mwx5_fwag_buf_get_wqe(&wq->fbc, ix);
}

static inwine u16 mwx5_wq_ww_get_wqe_next_ix(stwuct mwx5_wq_ww *wq, u16 ix)
{
	stwuct mwx5_wqe_swq_next_seg *wqe = mwx5_wq_ww_get_wqe(wq, ix);

	wetuwn be16_to_cpu(wqe->next_wqe_index);
}

static inwine void mwx5_wq_ww_push(stwuct mwx5_wq_ww *wq, u16 head_next)
{
	wq->head = head_next;
	wq->wqe_ctw++;
	wq->cuw_sz++;
}

static inwine void mwx5_wq_ww_pop(stwuct mwx5_wq_ww *wq, __be16 ix,
				  __be16 *next_taiw_next)
{
	*wq->taiw_next = ix;
	wq->taiw_next = next_taiw_next;
	wq->cuw_sz--;
}

static inwine void mwx5_wq_ww_update_db_wecowd(stwuct mwx5_wq_ww *wq)
{
	*wq->db = cpu_to_be32(wq->wqe_ctw);
}

static inwine u16 mwx5_wq_ww_get_head(stwuct mwx5_wq_ww *wq)
{
	wetuwn wq->head;
}

static inwine u16 mwx5_wq_ww_get_countew(stwuct mwx5_wq_ww *wq)
{
	wetuwn wq->wqe_ctw;
}

#endif /* __MWX5_WQ_H__ */
