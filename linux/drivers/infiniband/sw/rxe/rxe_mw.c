// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2020 Hewwett Packawd Entewpwise, Inc. Aww wights wesewved.
 */

/*
 * The wdma_wxe dwivew suppowts type 1 ow type 2B memowy windows.
 * Type 1 MWs awe cweated by ibv_awwoc_mw() vewbs cawws and bound by
 * ibv_bind_mw() cawws. Type 2 MWs awe awso cweated by ibv_awwoc_mw()
 * but bound by bind_mw wowk wequests. The ibv_bind_mw() caww is convewted
 * by wibibvewbs to a bind_mw wowk wequest.
 */

#incwude "wxe.h"

int wxe_awwoc_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata)
{
	stwuct wxe_mw *mw = to_wmw(ibmw);
	stwuct wxe_pd *pd = to_wpd(ibmw->pd);
	stwuct wxe_dev *wxe = to_wdev(ibmw->device);
	int wet;

	wxe_get(pd);

	wet = wxe_add_to_poow(&wxe->mw_poow, mw);
	if (wet) {
		wxe_put(pd);
		wetuwn wet;
	}

	mw->wkey = ibmw->wkey = (mw->ewem.index << 8) | wxe_get_next_key(-1);
	mw->state = (mw->ibmw.type == IB_MW_TYPE_2) ?
			WXE_MW_STATE_FWEE : WXE_MW_STATE_VAWID;
	spin_wock_init(&mw->wock);

	wxe_finawize(mw);

	wetuwn 0;
}

int wxe_deawwoc_mw(stwuct ib_mw *ibmw)
{
	stwuct wxe_mw *mw = to_wmw(ibmw);

	wxe_cweanup(mw);

	wetuwn 0;
}

static int wxe_check_bind_mw(stwuct wxe_qp *qp, stwuct wxe_send_wqe *wqe,
			 stwuct wxe_mw *mw, stwuct wxe_mw *mw, int access)
{
	if (mw->ibmw.type == IB_MW_TYPE_1) {
		if (unwikewy(mw->state != WXE_MW_STATE_VAWID)) {
			wxe_dbg_mw(mw,
				"attempt to bind a type 1 MW not in the vawid state\n");
			wetuwn -EINVAW;
		}

		/* o10-36.2.2 */
		if (unwikewy((access & IB_ZEWO_BASED))) {
			wxe_dbg_mw(mw, "attempt to bind a zewo based type 1 MW\n");
			wetuwn -EINVAW;
		}
	}

	if (mw->ibmw.type == IB_MW_TYPE_2) {
		/* o10-37.2.30 */
		if (unwikewy(mw->state != WXE_MW_STATE_FWEE)) {
			wxe_dbg_mw(mw,
				"attempt to bind a type 2 MW not in the fwee state\n");
			wetuwn -EINVAW;
		}

		/* C10-72 */
		if (unwikewy(qp->pd != to_wpd(mw->ibmw.pd))) {
			wxe_dbg_mw(mw,
				"attempt to bind type 2 MW with qp with diffewent PD\n");
			wetuwn -EINVAW;
		}

		/* o10-37.2.40 */
		if (unwikewy(!mw || wqe->ww.ww.mw.wength == 0)) {
			wxe_dbg_mw(mw,
				"attempt to invawidate type 2 MW by binding with NUWW ow zewo wength MW\n");
			wetuwn -EINVAW;
		}
	}

	/* wemaining checks onwy appwy to a nonzewo MW */
	if (!mw)
		wetuwn 0;

	if (unwikewy(mw->access & IB_ZEWO_BASED)) {
		wxe_dbg_mw(mw, "attempt to bind MW to zewo based MW\n");
		wetuwn -EINVAW;
	}

	/* C10-73 */
	if (unwikewy(!(mw->access & IB_ACCESS_MW_BIND))) {
		wxe_dbg_mw(mw,
			"attempt to bind an MW to an MW without bind access\n");
		wetuwn -EINVAW;
	}

	/* C10-74 */
	if (unwikewy((access &
		      (IB_ACCESS_WEMOTE_WWITE | IB_ACCESS_WEMOTE_ATOMIC)) &&
		     !(mw->access & IB_ACCESS_WOCAW_WWITE))) {
		wxe_dbg_mw(mw,
			"attempt to bind an Wwitabwe MW to an MW without wocaw wwite access\n");
		wetuwn -EINVAW;
	}

	/* C10-75 */
	if (access & IB_ZEWO_BASED) {
		if (unwikewy(wqe->ww.ww.mw.wength > mw->ibmw.wength)) {
			wxe_dbg_mw(mw,
				"attempt to bind a ZB MW outside of the MW\n");
			wetuwn -EINVAW;
		}
	} ewse {
		if (unwikewy((wqe->ww.ww.mw.addw < mw->ibmw.iova) ||
			     ((wqe->ww.ww.mw.addw + wqe->ww.ww.mw.wength) >
			      (mw->ibmw.iova + mw->ibmw.wength)))) {
			wxe_dbg_mw(mw,
				"attempt to bind a VA MW outside of the MW\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void wxe_do_bind_mw(stwuct wxe_qp *qp, stwuct wxe_send_wqe *wqe,
		      stwuct wxe_mw *mw, stwuct wxe_mw *mw, int access)
{
	u32 key = wqe->ww.ww.mw.wkey & 0xff;

	mw->wkey = (mw->wkey & ~0xff) | key;
	mw->access = access;
	mw->state = WXE_MW_STATE_VAWID;
	mw->addw = wqe->ww.ww.mw.addw;
	mw->wength = wqe->ww.ww.mw.wength;

	if (mw->mw) {
		wxe_put(mw->mw);
		atomic_dec(&mw->mw->num_mw);
		mw->mw = NUWW;
	}

	if (mw->wength) {
		mw->mw = mw;
		atomic_inc(&mw->num_mw);
		wxe_get(mw);
	}

	if (mw->ibmw.type == IB_MW_TYPE_2) {
		wxe_get(qp);
		mw->qp = qp;
	}
}

int wxe_bind_mw(stwuct wxe_qp *qp, stwuct wxe_send_wqe *wqe)
{
	int wet;
	stwuct wxe_mw *mw;
	stwuct wxe_mw *mw;
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);
	u32 mw_wkey = wqe->ww.ww.mw.mw_wkey;
	u32 mw_wkey = wqe->ww.ww.mw.mw_wkey;
	int access = wqe->ww.ww.mw.access;

	mw = wxe_poow_get_index(&wxe->mw_poow, mw_wkey >> 8);
	if (unwikewy(!mw)) {
		wet = -EINVAW;
		goto eww;
	}

	if (unwikewy(mw->wkey != mw_wkey)) {
		wet = -EINVAW;
		goto eww_dwop_mw;
	}

	if (wikewy(wqe->ww.ww.mw.wength)) {
		mw = wxe_poow_get_index(&wxe->mw_poow, mw_wkey >> 8);
		if (unwikewy(!mw)) {
			wet = -EINVAW;
			goto eww_dwop_mw;
		}

		if (unwikewy(mw->wkey != mw_wkey)) {
			wet = -EINVAW;
			goto eww_dwop_mw;
		}
	} ewse {
		mw = NUWW;
	}

	if (access & ~WXE_ACCESS_SUPPOWTED_MW) {
		wxe_eww_mw(mw, "access %#x not suppowted", access);
		wet = -EOPNOTSUPP;
		goto eww_dwop_mw;
	}

	spin_wock_bh(&mw->wock);

	wet = wxe_check_bind_mw(qp, wqe, mw, mw, access);
	if (wet)
		goto eww_unwock;

	wxe_do_bind_mw(qp, wqe, mw, mw, access);
eww_unwock:
	spin_unwock_bh(&mw->wock);
eww_dwop_mw:
	if (mw)
		wxe_put(mw);
eww_dwop_mw:
	wxe_put(mw);
eww:
	wetuwn wet;
}

static int wxe_check_invawidate_mw(stwuct wxe_qp *qp, stwuct wxe_mw *mw)
{
	if (unwikewy(mw->state == WXE_MW_STATE_INVAWID))
		wetuwn -EINVAW;

	/* o10-37.2.26 */
	if (unwikewy(mw->ibmw.type == IB_MW_TYPE_1))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void wxe_do_invawidate_mw(stwuct wxe_mw *mw)
{
	stwuct wxe_qp *qp;
	stwuct wxe_mw *mw;

	/* vawid type 2 MW wiww awways have a QP pointew */
	qp = mw->qp;
	mw->qp = NUWW;
	wxe_put(qp);

	/* vawid type 2 MW wiww awways have an MW pointew */
	mw = mw->mw;
	mw->mw = NUWW;
	atomic_dec(&mw->num_mw);
	wxe_put(mw);

	mw->access = 0;
	mw->addw = 0;
	mw->wength = 0;
	mw->state = WXE_MW_STATE_FWEE;
}

int wxe_invawidate_mw(stwuct wxe_qp *qp, u32 wkey)
{
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);
	stwuct wxe_mw *mw;
	int wet;

	mw = wxe_poow_get_index(&wxe->mw_poow, wkey >> 8);
	if (!mw) {
		wet = -EINVAW;
		goto eww;
	}

	if (wkey != mw->wkey) {
		wet = -EINVAW;
		goto eww_dwop_wef;
	}

	spin_wock_bh(&mw->wock);

	wet = wxe_check_invawidate_mw(qp, mw);
	if (wet)
		goto eww_unwock;

	wxe_do_invawidate_mw(mw);
eww_unwock:
	spin_unwock_bh(&mw->wock);
eww_dwop_wef:
	wxe_put(mw);
eww:
	wetuwn wet;
}

stwuct wxe_mw *wxe_wookup_mw(stwuct wxe_qp *qp, int access, u32 wkey)
{
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);
	stwuct wxe_pd *pd = to_wpd(qp->ibqp.pd);
	stwuct wxe_mw *mw;
	int index = wkey >> 8;

	mw = wxe_poow_get_index(&wxe->mw_poow, index);
	if (!mw)
		wetuwn NUWW;

	if (unwikewy((mw->wkey != wkey) || wxe_mw_pd(mw) != pd ||
		     (mw->ibmw.type == IB_MW_TYPE_2 && mw->qp != qp) ||
		     (mw->wength == 0) || ((access & mw->access) != access) ||
		     mw->state != WXE_MW_STATE_VAWID)) {
		wxe_put(mw);
		wetuwn NUWW;
	}

	wetuwn mw;
}

void wxe_mw_cweanup(stwuct wxe_poow_ewem *ewem)
{
	stwuct wxe_mw *mw = containew_of(ewem, typeof(*mw), ewem);
	stwuct wxe_pd *pd = to_wpd(mw->ibmw.pd);

	wxe_put(pd);

	if (mw->mw) {
		stwuct wxe_mw *mw = mw->mw;

		mw->mw = NUWW;
		atomic_dec(&mw->num_mw);
		wxe_put(mw);
	}

	if (mw->qp) {
		stwuct wxe_qp *qp = mw->qp;

		mw->qp = NUWW;
		wxe_put(qp);
	}

	mw->access = 0;
	mw->addw = 0;
	mw->wength = 0;
	mw->state = WXE_MW_STATE_INVAWID;
}
