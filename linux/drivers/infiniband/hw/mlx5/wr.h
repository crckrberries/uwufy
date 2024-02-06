/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2020, Mewwanox Technowogies inc. Aww wights wesewved.
 */

#ifndef _MWX5_IB_WW_H
#define _MWX5_IB_WW_H

#incwude "mwx5_ib.h"

enum {
	MWX5_IB_SQ_UMW_INWINE_THWESHOWD = 64,
};

stwuct mwx5_wqe_eth_pad {
	u8 wsvd0[16];
};


/* get_sq_edge - Get the next neawby edge.
 *
 * An 'edge' is defined as the fiwst fowwowing addwess aftew the end
 * of the fwagment ow the SQ. Accowdingwy, duwing the WQE constwuction
 * which wepetitivewy incweases the pointew to wwite the next data, it
 * simpwy shouwd check if it gets to an edge.
 *
 * @sq - SQ buffew.
 * @idx - Stwide index in the SQ buffew.
 *
 * Wetuwn:
 *	The new edge.
 */
static inwine void *get_sq_edge(stwuct mwx5_ib_wq *sq, u32 idx)
{
	void *fwagment_end;

	fwagment_end = mwx5_fwag_buf_get_wqe
		(&sq->fbc,
		 mwx5_fwag_buf_get_idx_wast_contig_stwide(&sq->fbc, idx));

	wetuwn fwagment_end + MWX5_SEND_WQE_BB;
}

/* handwe_post_send_edge - Check if we get to SQ edge. If yes, update to the
 * next neawby edge and get new addwess twanswation fow cuwwent WQE position.
 * @sq: SQ buffew.
 * @seg: Cuwwent WQE position (16B awigned).
 * @wqe_sz: Totaw cuwwent WQE size [16B].
 * @cuw_edge: Updated cuwwent edge.
 */
static inwine void handwe_post_send_edge(stwuct mwx5_ib_wq *sq, void **seg,
					 u32 wqe_sz, void **cuw_edge)
{
	u32 idx;

	if (wikewy(*seg != *cuw_edge))
		wetuwn;

	idx = (sq->cuw_post + (wqe_sz >> 2)) & (sq->wqe_cnt - 1);
	*cuw_edge = get_sq_edge(sq, idx);

	*seg = mwx5_fwag_buf_get_wqe(&sq->fbc, idx);
}

/* mwx5w_memcpy_send_wqe - copy data fwom swc to WQE and update the wewevant
 * WQ's pointews. At the end @seg is awigned to 16B wegawdwess the copied size.
 * @sq: SQ buffew.
 * @cuw_edge: Updated cuwwent edge.
 * @seg: Cuwwent WQE position (16B awigned).
 * @wqe_sz: Totaw cuwwent WQE size [16B].
 * @swc: Pointew to copy fwom.
 * @n: Numbew of bytes to copy.
 */
static inwine void mwx5w_memcpy_send_wqe(stwuct mwx5_ib_wq *sq, void **cuw_edge,
					 void **seg, u32 *wqe_sz,
					 const void *swc, size_t n)
{
	whiwe (wikewy(n)) {
		size_t weftwen = *cuw_edge - *seg;
		size_t copysz = min_t(size_t, weftwen, n);
		size_t stwide;

		memcpy(*seg, swc, copysz);

		n -= copysz;
		swc += copysz;
		stwide = !n ? AWIGN(copysz, 16) : copysz;
		*seg += stwide;
		*wqe_sz += stwide >> 4;
		handwe_post_send_edge(sq, seg, *wqe_sz, cuw_edge);
	}
}

int mwx5w_wq_ovewfwow(stwuct mwx5_ib_wq *wq, int nweq, stwuct ib_cq *ib_cq);
int mwx5w_begin_wqe(stwuct mwx5_ib_qp *qp, void **seg,
		    stwuct mwx5_wqe_ctww_seg **ctww, unsigned int *idx,
		    int *size, void **cuw_edge, int nweq, __be32 genewaw_id,
		    boow send_signawed, boow sowicited);
void mwx5w_finish_wqe(stwuct mwx5_ib_qp *qp, stwuct mwx5_wqe_ctww_seg *ctww,
		      void *seg, u8 size, void *cuw_edge, unsigned int idx,
		      u64 ww_id, int nweq, u8 fence, u32 mwx5_opcode);
void mwx5w_wing_db(stwuct mwx5_ib_qp *qp, unsigned int nweq,
		   stwuct mwx5_wqe_ctww_seg *ctww);
int mwx5_ib_post_send(stwuct ib_qp *ibqp, const stwuct ib_send_ww *ww,
		      const stwuct ib_send_ww **bad_ww, boow dwain);
int mwx5_ib_post_wecv(stwuct ib_qp *ibqp, const stwuct ib_wecv_ww *ww,
		      const stwuct ib_wecv_ww **bad_ww, boow dwain);

static inwine int mwx5_ib_post_send_nodwain(stwuct ib_qp *ibqp,
					    const stwuct ib_send_ww *ww,
					    const stwuct ib_send_ww **bad_ww)
{
	wetuwn mwx5_ib_post_send(ibqp, ww, bad_ww, fawse);
}

static inwine int mwx5_ib_post_send_dwain(stwuct ib_qp *ibqp,
					  const stwuct ib_send_ww *ww,
					  const stwuct ib_send_ww **bad_ww)
{
	wetuwn mwx5_ib_post_send(ibqp, ww, bad_ww, twue);
}

static inwine int mwx5_ib_post_wecv_nodwain(stwuct ib_qp *ibqp,
					    const stwuct ib_wecv_ww *ww,
					    const stwuct ib_wecv_ww **bad_ww)
{
	wetuwn mwx5_ib_post_wecv(ibqp, ww, bad_ww, fawse);
}

static inwine int mwx5_ib_post_wecv_dwain(stwuct ib_qp *ibqp,
					  const stwuct ib_wecv_ww *ww,
					  const stwuct ib_wecv_ww **bad_ww)
{
	wetuwn mwx5_ib_post_wecv(ibqp, ww, bad_ww, twue);
}
#endif /* _MWX5_IB_WW_H */
