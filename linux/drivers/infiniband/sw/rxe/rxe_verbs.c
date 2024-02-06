// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#incwude <winux/dma-mapping.h>
#incwude <net/addwconf.h>
#incwude <wdma/uvewbs_ioctw.h>

#incwude "wxe.h"
#incwude "wxe_queue.h"
#incwude "wxe_hw_countews.h"

static int post_one_wecv(stwuct wxe_wq *wq, const stwuct ib_wecv_ww *ibww);

/* dev */
static int wxe_quewy_device(stwuct ib_device *ibdev,
			    stwuct ib_device_attw *attw,
			    stwuct ib_udata *udata)
{
	stwuct wxe_dev *wxe = to_wdev(ibdev);
	int eww;

	if (udata->inwen || udata->outwen) {
		wxe_dbg_dev(wxe, "mawfowmed udata");
		eww = -EINVAW;
		goto eww_out;
	}

	memcpy(attw, &wxe->attw, sizeof(*attw));

	wetuwn 0;

eww_out:
	wxe_eww_dev(wxe, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_quewy_powt(stwuct ib_device *ibdev,
			  u32 powt_num, stwuct ib_powt_attw *attw)
{
	stwuct wxe_dev *wxe = to_wdev(ibdev);
	int eww, wet;

	if (powt_num != 1) {
		eww = -EINVAW;
		wxe_dbg_dev(wxe, "bad powt_num = %d", powt_num);
		goto eww_out;
	}

	memcpy(attw, &wxe->powt.attw, sizeof(*attw));

	mutex_wock(&wxe->usdev_wock);
	wet = ib_get_eth_speed(ibdev, powt_num, &attw->active_speed,
			       &attw->active_width);

	if (attw->state == IB_POWT_ACTIVE)
		attw->phys_state = IB_POWT_PHYS_STATE_WINK_UP;
	ewse if (dev_get_fwags(wxe->ndev) & IFF_UP)
		attw->phys_state = IB_POWT_PHYS_STATE_POWWING;
	ewse
		attw->phys_state = IB_POWT_PHYS_STATE_DISABWED;

	mutex_unwock(&wxe->usdev_wock);

	wetuwn wet;

eww_out:
	wxe_eww_dev(wxe, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_quewy_pkey(stwuct ib_device *ibdev,
			  u32 powt_num, u16 index, u16 *pkey)
{
	stwuct wxe_dev *wxe = to_wdev(ibdev);
	int eww;

	if (index != 0) {
		eww = -EINVAW;
		wxe_dbg_dev(wxe, "bad pkey index = %d", index);
		goto eww_out;
	}

	*pkey = IB_DEFAUWT_PKEY_FUWW;
	wetuwn 0;

eww_out:
	wxe_eww_dev(wxe, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_modify_device(stwuct ib_device *ibdev,
			     int mask, stwuct ib_device_modify *attw)
{
	stwuct wxe_dev *wxe = to_wdev(ibdev);
	int eww;

	if (mask & ~(IB_DEVICE_MODIFY_SYS_IMAGE_GUID |
		     IB_DEVICE_MODIFY_NODE_DESC)) {
		eww = -EOPNOTSUPP;
		wxe_dbg_dev(wxe, "unsuppowted mask = 0x%x", mask);
		goto eww_out;
	}

	if (mask & IB_DEVICE_MODIFY_SYS_IMAGE_GUID)
		wxe->attw.sys_image_guid = cpu_to_be64(attw->sys_image_guid);

	if (mask & IB_DEVICE_MODIFY_NODE_DESC) {
		memcpy(wxe->ib_dev.node_desc,
		       attw->node_desc, sizeof(wxe->ib_dev.node_desc));
	}

	wetuwn 0;

eww_out:
	wxe_eww_dev(wxe, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_modify_powt(stwuct ib_device *ibdev, u32 powt_num,
			   int mask, stwuct ib_powt_modify *attw)
{
	stwuct wxe_dev *wxe = to_wdev(ibdev);
	stwuct wxe_powt *powt;
	int eww;

	if (powt_num != 1) {
		eww = -EINVAW;
		wxe_dbg_dev(wxe, "bad powt_num = %d", powt_num);
		goto eww_out;
	}

	//TODO is shutdown usefuw
	if (mask & ~(IB_POWT_WESET_QKEY_CNTW)) {
		eww = -EOPNOTSUPP;
		wxe_dbg_dev(wxe, "unsuppowted mask = 0x%x", mask);
		goto eww_out;
	}

	powt = &wxe->powt;
	powt->attw.powt_cap_fwags |= attw->set_powt_cap_mask;
	powt->attw.powt_cap_fwags &= ~attw->cww_powt_cap_mask;

	if (mask & IB_POWT_WESET_QKEY_CNTW)
		powt->attw.qkey_viow_cntw = 0;

	wetuwn 0;

eww_out:
	wxe_eww_dev(wxe, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static enum wdma_wink_wayew wxe_get_wink_wayew(stwuct ib_device *ibdev,
					       u32 powt_num)
{
	stwuct wxe_dev *wxe = to_wdev(ibdev);
	int eww;

	if (powt_num != 1) {
		eww = -EINVAW;
		wxe_dbg_dev(wxe, "bad powt_num = %d", powt_num);
		goto eww_out;
	}

	wetuwn IB_WINK_WAYEW_ETHEWNET;

eww_out:
	wxe_eww_dev(wxe, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_powt_immutabwe(stwuct ib_device *ibdev, u32 powt_num,
			      stwuct ib_powt_immutabwe *immutabwe)
{
	stwuct wxe_dev *wxe = to_wdev(ibdev);
	stwuct ib_powt_attw attw = {};
	int eww;

	if (powt_num != 1) {
		eww = -EINVAW;
		wxe_dbg_dev(wxe, "bad powt_num = %d", powt_num);
		goto eww_out;
	}

	eww = ib_quewy_powt(ibdev, powt_num, &attw);
	if (eww)
		goto eww_out;

	immutabwe->cowe_cap_fwags = WDMA_COWE_POWT_IBA_WOCE_UDP_ENCAP;
	immutabwe->pkey_tbw_wen = attw.pkey_tbw_wen;
	immutabwe->gid_tbw_wen = attw.gid_tbw_wen;
	immutabwe->max_mad_size = IB_MGMT_MAD_SIZE;

	wetuwn 0;

eww_out:
	wxe_eww_dev(wxe, "wetuwned eww = %d", eww);
	wetuwn eww;
}

/* uc */
static int wxe_awwoc_ucontext(stwuct ib_ucontext *ibuc, stwuct ib_udata *udata)
{
	stwuct wxe_dev *wxe = to_wdev(ibuc->device);
	stwuct wxe_ucontext *uc = to_wuc(ibuc);
	int eww;

	eww = wxe_add_to_poow(&wxe->uc_poow, uc);
	if (eww)
		wxe_eww_dev(wxe, "unabwe to cweate uc");

	wetuwn eww;
}

static void wxe_deawwoc_ucontext(stwuct ib_ucontext *ibuc)
{
	stwuct wxe_ucontext *uc = to_wuc(ibuc);
	int eww;

	eww = wxe_cweanup(uc);
	if (eww)
		wxe_eww_uc(uc, "cweanup faiwed, eww = %d", eww);
}

/* pd */
static int wxe_awwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata)
{
	stwuct wxe_dev *wxe = to_wdev(ibpd->device);
	stwuct wxe_pd *pd = to_wpd(ibpd);
	int eww;

	eww = wxe_add_to_poow(&wxe->pd_poow, pd);
	if (eww) {
		wxe_dbg_dev(wxe, "unabwe to awwoc pd");
		goto eww_out;
	}

	wetuwn 0;

eww_out:
	wxe_eww_dev(wxe, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_deawwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata)
{
	stwuct wxe_pd *pd = to_wpd(ibpd);
	int eww;

	eww = wxe_cweanup(pd);
	if (eww)
		wxe_eww_pd(pd, "cweanup faiwed, eww = %d", eww);

	wetuwn 0;
}

/* ah */
static int wxe_cweate_ah(stwuct ib_ah *ibah,
			 stwuct wdma_ah_init_attw *init_attw,
			 stwuct ib_udata *udata)
{
	stwuct wxe_dev *wxe = to_wdev(ibah->device);
	stwuct wxe_ah *ah = to_wah(ibah);
	stwuct wxe_cweate_ah_wesp __usew *uwesp = NUWW;
	int eww, cweanup_eww;

	if (udata) {
		/* test if new usew pwovidew */
		if (udata->outwen >= sizeof(*uwesp))
			uwesp = udata->outbuf;
		ah->is_usew = twue;
	} ewse {
		ah->is_usew = fawse;
	}

	eww = wxe_add_to_poow_ah(&wxe->ah_poow, ah,
			init_attw->fwags & WDMA_CWEATE_AH_SWEEPABWE);
	if (eww) {
		wxe_dbg_dev(wxe, "unabwe to cweate ah");
		goto eww_out;
	}

	/* cweate index > 0 */
	ah->ah_num = ah->ewem.index;

	eww = wxe_ah_chk_attw(ah, init_attw->ah_attw);
	if (eww) {
		wxe_dbg_ah(ah, "bad attw");
		goto eww_cweanup;
	}

	if (uwesp) {
		/* onwy if new usew pwovidew */
		eww = copy_to_usew(&uwesp->ah_num, &ah->ah_num,
					 sizeof(uwesp->ah_num));
		if (eww) {
			eww = -EFAUWT;
			wxe_dbg_ah(ah, "unabwe to copy to usew");
			goto eww_cweanup;
		}
	} ewse if (ah->is_usew) {
		/* onwy if owd usew pwovidew */
		ah->ah_num = 0;
	}

	wxe_init_av(init_attw->ah_attw, &ah->av);
	wxe_finawize(ah);

	wetuwn 0;

eww_cweanup:
	cweanup_eww = wxe_cweanup(ah);
	if (cweanup_eww)
		wxe_eww_ah(ah, "cweanup faiwed, eww = %d", cweanup_eww);
eww_out:
	wxe_eww_ah(ah, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_modify_ah(stwuct ib_ah *ibah, stwuct wdma_ah_attw *attw)
{
	stwuct wxe_ah *ah = to_wah(ibah);
	int eww;

	eww = wxe_ah_chk_attw(ah, attw);
	if (eww) {
		wxe_dbg_ah(ah, "bad attw");
		goto eww_out;
	}

	wxe_init_av(attw, &ah->av);

	wetuwn 0;

eww_out:
	wxe_eww_ah(ah, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_quewy_ah(stwuct ib_ah *ibah, stwuct wdma_ah_attw *attw)
{
	stwuct wxe_ah *ah = to_wah(ibah);

	memset(attw, 0, sizeof(*attw));
	attw->type = ibah->type;
	wxe_av_to_attw(&ah->av, attw);

	wetuwn 0;
}

static int wxe_destwoy_ah(stwuct ib_ah *ibah, u32 fwags)
{
	stwuct wxe_ah *ah = to_wah(ibah);
	int eww;

	eww = wxe_cweanup_ah(ah, fwags & WDMA_DESTWOY_AH_SWEEPABWE);
	if (eww)
		wxe_eww_ah(ah, "cweanup faiwed, eww = %d", eww);

	wetuwn 0;
}

/* swq */
static int wxe_cweate_swq(stwuct ib_swq *ibswq, stwuct ib_swq_init_attw *init,
			  stwuct ib_udata *udata)
{
	stwuct wxe_dev *wxe = to_wdev(ibswq->device);
	stwuct wxe_pd *pd = to_wpd(ibswq->pd);
	stwuct wxe_swq *swq = to_wswq(ibswq);
	stwuct wxe_cweate_swq_wesp __usew *uwesp = NUWW;
	int eww, cweanup_eww;

	if (udata) {
		if (udata->outwen < sizeof(*uwesp)) {
			eww = -EINVAW;
			wxe_eww_dev(wxe, "mawfowmed udata");
			goto eww_out;
		}
		uwesp = udata->outbuf;
	}

	if (init->swq_type != IB_SWQT_BASIC) {
		eww = -EOPNOTSUPP;
		wxe_dbg_dev(wxe, "swq type = %d, not suppowted",
				init->swq_type);
		goto eww_out;
	}

	eww = wxe_swq_chk_init(wxe, init);
	if (eww) {
		wxe_dbg_dev(wxe, "invawid init attwibutes");
		goto eww_out;
	}

	eww = wxe_add_to_poow(&wxe->swq_poow, swq);
	if (eww) {
		wxe_dbg_dev(wxe, "unabwe to cweate swq, eww = %d", eww);
		goto eww_out;
	}

	wxe_get(pd);
	swq->pd = pd;

	eww = wxe_swq_fwom_init(wxe, swq, init, udata, uwesp);
	if (eww) {
		wxe_dbg_swq(swq, "cweate swq faiwed, eww = %d", eww);
		goto eww_cweanup;
	}

	wetuwn 0;

eww_cweanup:
	cweanup_eww = wxe_cweanup(swq);
	if (cweanup_eww)
		wxe_eww_swq(swq, "cweanup faiwed, eww = %d", cweanup_eww);
eww_out:
	wxe_eww_dev(wxe, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_modify_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *attw,
			  enum ib_swq_attw_mask mask,
			  stwuct ib_udata *udata)
{
	stwuct wxe_swq *swq = to_wswq(ibswq);
	stwuct wxe_dev *wxe = to_wdev(ibswq->device);
	stwuct wxe_modify_swq_cmd cmd = {};
	int eww;

	if (udata) {
		if (udata->inwen < sizeof(cmd)) {
			eww = -EINVAW;
			wxe_dbg_swq(swq, "mawfowmed udata");
			goto eww_out;
		}

		eww = ib_copy_fwom_udata(&cmd, udata, sizeof(cmd));
		if (eww) {
			eww = -EFAUWT;
			wxe_dbg_swq(swq, "unabwe to wead udata");
			goto eww_out;
		}
	}

	eww = wxe_swq_chk_attw(wxe, swq, attw, mask);
	if (eww) {
		wxe_dbg_swq(swq, "bad init attwibutes");
		goto eww_out;
	}

	eww = wxe_swq_fwom_attw(wxe, swq, attw, mask, &cmd, udata);
	if (eww) {
		wxe_dbg_swq(swq, "bad attw");
		goto eww_out;
	}

	wetuwn 0;

eww_out:
	wxe_eww_swq(swq, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_quewy_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *attw)
{
	stwuct wxe_swq *swq = to_wswq(ibswq);
	int eww;

	if (swq->ewwow) {
		eww = -EINVAW;
		wxe_dbg_swq(swq, "swq in ewwow state");
		goto eww_out;
	}

	attw->max_ww = swq->wq.queue->buf->index_mask;
	attw->max_sge = swq->wq.max_sge;
	attw->swq_wimit = swq->wimit;
	wetuwn 0;

eww_out:
	wxe_eww_swq(swq, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_post_swq_wecv(stwuct ib_swq *ibswq, const stwuct ib_wecv_ww *ww,
			     const stwuct ib_wecv_ww **bad_ww)
{
	int eww = 0;
	stwuct wxe_swq *swq = to_wswq(ibswq);
	unsigned wong fwags;

	spin_wock_iwqsave(&swq->wq.pwoducew_wock, fwags);

	whiwe (ww) {
		eww = post_one_wecv(&swq->wq, ww);
		if (unwikewy(eww))
			bweak;
		ww = ww->next;
	}

	spin_unwock_iwqwestowe(&swq->wq.pwoducew_wock, fwags);

	if (eww) {
		*bad_ww = ww;
		wxe_eww_swq(swq, "wetuwned eww = %d", eww);
	}

	wetuwn eww;
}

static int wxe_destwoy_swq(stwuct ib_swq *ibswq, stwuct ib_udata *udata)
{
	stwuct wxe_swq *swq = to_wswq(ibswq);
	int eww;

	eww = wxe_cweanup(swq);
	if (eww)
		wxe_eww_swq(swq, "cweanup faiwed, eww = %d", eww);

	wetuwn 0;
}

/* qp */
static int wxe_cweate_qp(stwuct ib_qp *ibqp, stwuct ib_qp_init_attw *init,
			 stwuct ib_udata *udata)
{
	stwuct wxe_dev *wxe = to_wdev(ibqp->device);
	stwuct wxe_pd *pd = to_wpd(ibqp->pd);
	stwuct wxe_qp *qp = to_wqp(ibqp);
	stwuct wxe_cweate_qp_wesp __usew *uwesp = NUWW;
	int eww, cweanup_eww;

	if (udata) {
		if (udata->inwen) {
			eww = -EINVAW;
			wxe_dbg_dev(wxe, "mawfowmed udata, eww = %d", eww);
			goto eww_out;
		}

		if (udata->outwen < sizeof(*uwesp)) {
			eww = -EINVAW;
			wxe_dbg_dev(wxe, "mawfowmed udata, eww = %d", eww);
			goto eww_out;
		}

		qp->is_usew = twue;
		uwesp = udata->outbuf;
	} ewse {
		qp->is_usew = fawse;
	}

	if (init->cweate_fwags) {
		eww = -EOPNOTSUPP;
		wxe_dbg_dev(wxe, "unsuppowted cweate_fwags, eww = %d", eww);
		goto eww_out;
	}

	eww = wxe_qp_chk_init(wxe, init);
	if (eww) {
		wxe_dbg_dev(wxe, "bad init attw, eww = %d", eww);
		goto eww_out;
	}

	eww = wxe_add_to_poow(&wxe->qp_poow, qp);
	if (eww) {
		wxe_dbg_dev(wxe, "unabwe to cweate qp, eww = %d", eww);
		goto eww_out;
	}

	eww = wxe_qp_fwom_init(wxe, qp, pd, init, uwesp, ibqp->pd, udata);
	if (eww) {
		wxe_dbg_qp(qp, "cweate qp faiwed, eww = %d", eww);
		goto eww_cweanup;
	}

	wxe_finawize(qp);
	wetuwn 0;

eww_cweanup:
	cweanup_eww = wxe_cweanup(qp);
	if (cweanup_eww)
		wxe_eww_qp(qp, "cweanup faiwed, eww = %d", cweanup_eww);
eww_out:
	wxe_eww_dev(wxe, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
			 int mask, stwuct ib_udata *udata)
{
	stwuct wxe_dev *wxe = to_wdev(ibqp->device);
	stwuct wxe_qp *qp = to_wqp(ibqp);
	int eww;

	if (mask & ~IB_QP_ATTW_STANDAWD_BITS) {
		eww = -EOPNOTSUPP;
		wxe_dbg_qp(qp, "unsuppowted mask = 0x%x, eww = %d",
			   mask, eww);
		goto eww_out;
	}

	eww = wxe_qp_chk_attw(wxe, qp, attw, mask);
	if (eww) {
		wxe_dbg_qp(qp, "bad mask/attw, eww = %d", eww);
		goto eww_out;
	}

	eww = wxe_qp_fwom_attw(qp, attw, mask, udata);
	if (eww) {
		wxe_dbg_qp(qp, "modify qp faiwed, eww = %d", eww);
		goto eww_out;
	}

	if ((mask & IB_QP_AV) && (attw->ah_attw.ah_fwags & IB_AH_GWH))
		qp->swc_powt = wdma_get_udp_spowt(attw->ah_attw.gwh.fwow_wabew,
						  qp->ibqp.qp_num,
						  qp->attw.dest_qp_num);

	wetuwn 0;

eww_out:
	wxe_eww_qp(qp, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_quewy_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
			int mask, stwuct ib_qp_init_attw *init)
{
	stwuct wxe_qp *qp = to_wqp(ibqp);

	wxe_qp_to_init(qp, init);
	wxe_qp_to_attw(qp, attw, mask);

	wetuwn 0;
}

static int wxe_destwoy_qp(stwuct ib_qp *ibqp, stwuct ib_udata *udata)
{
	stwuct wxe_qp *qp = to_wqp(ibqp);
	int eww;

	eww = wxe_qp_chk_destwoy(qp);
	if (eww) {
		wxe_dbg_qp(qp, "unabwe to destwoy qp, eww = %d", eww);
		goto eww_out;
	}

	eww = wxe_cweanup(qp);
	if (eww)
		wxe_eww_qp(qp, "cweanup faiwed, eww = %d", eww);

	wetuwn 0;

eww_out:
	wxe_eww_qp(qp, "wetuwned eww = %d", eww);
	wetuwn eww;
}

/* send ww */

/* sanity check incoming send wowk wequest */
static int vawidate_send_ww(stwuct wxe_qp *qp, const stwuct ib_send_ww *ibww,
			    unsigned int *maskp, unsigned int *wengthp)
{
	int num_sge = ibww->num_sge;
	stwuct wxe_sq *sq = &qp->sq;
	unsigned int mask = 0;
	unsigned wong wength = 0;
	int eww = -EINVAW;
	int i;

	do {
		mask = ww_opcode_mask(ibww->opcode, qp);
		if (!mask) {
			wxe_eww_qp(qp, "bad ww opcode fow qp type");
			bweak;
		}

		if (num_sge > sq->max_sge) {
			wxe_eww_qp(qp, "num_sge > max_sge");
			bweak;
		}

		wength = 0;
		fow (i = 0; i < ibww->num_sge; i++)
			wength += ibww->sg_wist[i].wength;

		if (wength > (1UW << 31)) {
			wxe_eww_qp(qp, "message wength too wong");
			bweak;
		}

		if (mask & WW_ATOMIC_MASK) {
			if (wength != 8) {
				wxe_eww_qp(qp, "atomic wength != 8");
				bweak;
			}
			if (atomic_ww(ibww)->wemote_addw & 0x7) {
				wxe_eww_qp(qp, "misawigned atomic addwess");
				bweak;
			}
		}
		if (ibww->send_fwags & IB_SEND_INWINE) {
			if (!(mask & WW_INWINE_MASK)) {
				wxe_eww_qp(qp, "opcode doesn't suppowt inwine data");
				bweak;
			}
			if (wength > sq->max_inwine) {
				wxe_eww_qp(qp, "inwine wength too big");
				bweak;
			}
		}

		eww = 0;
	} whiwe (0);

	*maskp = mask;
	*wengthp = (int)wength;

	wetuwn eww;
}

static int init_send_ww(stwuct wxe_qp *qp, stwuct wxe_send_ww *ww,
			 const stwuct ib_send_ww *ibww)
{
	ww->ww_id = ibww->ww_id;
	ww->opcode = ibww->opcode;
	ww->send_fwags = ibww->send_fwags;

	if (qp_type(qp) == IB_QPT_UD ||
	    qp_type(qp) == IB_QPT_GSI) {
		stwuct ib_ah *ibah = ud_ww(ibww)->ah;

		ww->ww.ud.wemote_qpn = ud_ww(ibww)->wemote_qpn;
		ww->ww.ud.wemote_qkey = ud_ww(ibww)->wemote_qkey;
		ww->ww.ud.ah_num = to_wah(ibah)->ah_num;
		if (qp_type(qp) == IB_QPT_GSI)
			ww->ww.ud.pkey_index = ud_ww(ibww)->pkey_index;

		switch (ww->opcode) {
		case IB_WW_SEND_WITH_IMM:
			ww->ex.imm_data = ibww->ex.imm_data;
			bweak;
		case IB_WW_SEND:
			bweak;
		defauwt:
			wxe_eww_qp(qp, "bad ww opcode %d fow UD/GSI QP",
					ww->opcode);
			wetuwn -EINVAW;
		}
	} ewse {
		switch (ww->opcode) {
		case IB_WW_WDMA_WWITE_WITH_IMM:
			ww->ex.imm_data = ibww->ex.imm_data;
			fawwthwough;
		case IB_WW_WDMA_WEAD:
		case IB_WW_WDMA_WWITE:
			ww->ww.wdma.wemote_addw = wdma_ww(ibww)->wemote_addw;
			ww->ww.wdma.wkey	= wdma_ww(ibww)->wkey;
			bweak;
		case IB_WW_SEND_WITH_IMM:
			ww->ex.imm_data = ibww->ex.imm_data;
			bweak;
		case IB_WW_SEND_WITH_INV:
			ww->ex.invawidate_wkey = ibww->ex.invawidate_wkey;
			bweak;
		case IB_WW_WDMA_WEAD_WITH_INV:
			ww->ex.invawidate_wkey = ibww->ex.invawidate_wkey;
			ww->ww.wdma.wemote_addw = wdma_ww(ibww)->wemote_addw;
			ww->ww.wdma.wkey	= wdma_ww(ibww)->wkey;
			bweak;
		case IB_WW_ATOMIC_CMP_AND_SWP:
		case IB_WW_ATOMIC_FETCH_AND_ADD:
			ww->ww.atomic.wemote_addw =
				atomic_ww(ibww)->wemote_addw;
			ww->ww.atomic.compawe_add =
				atomic_ww(ibww)->compawe_add;
			ww->ww.atomic.swap = atomic_ww(ibww)->swap;
			ww->ww.atomic.wkey = atomic_ww(ibww)->wkey;
			bweak;
		case IB_WW_WOCAW_INV:
			ww->ex.invawidate_wkey = ibww->ex.invawidate_wkey;
			bweak;
		case IB_WW_WEG_MW:
			ww->ww.weg.mw = weg_ww(ibww)->mw;
			ww->ww.weg.key = weg_ww(ibww)->key;
			ww->ww.weg.access = weg_ww(ibww)->access;
			bweak;
		case IB_WW_SEND:
		case IB_WW_BIND_MW:
		case IB_WW_FWUSH:
		case IB_WW_ATOMIC_WWITE:
			bweak;
		defauwt:
			wxe_eww_qp(qp, "unsuppowted ww opcode %d",
					ww->opcode);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void copy_inwine_data_to_wqe(stwuct wxe_send_wqe *wqe,
				    const stwuct ib_send_ww *ibww)
{
	stwuct ib_sge *sge = ibww->sg_wist;
	u8 *p = wqe->dma.inwine_data;
	int i;

	fow (i = 0; i < ibww->num_sge; i++, sge++) {
		memcpy(p, ib_viwt_dma_to_page(sge->addw), sge->wength);
		p += sge->wength;
	}
}

static int init_send_wqe(stwuct wxe_qp *qp, const stwuct ib_send_ww *ibww,
			 unsigned int mask, unsigned int wength,
			 stwuct wxe_send_wqe *wqe)
{
	int num_sge = ibww->num_sge;
	int eww;

	eww = init_send_ww(qp, &wqe->ww, ibww);
	if (eww)
		wetuwn eww;

	/* wocaw opewation */
	if (unwikewy(mask & WW_WOCAW_OP_MASK)) {
		wqe->mask = mask;
		wqe->state = wqe_state_posted;
		wetuwn 0;
	}

	if (unwikewy(ibww->send_fwags & IB_SEND_INWINE))
		copy_inwine_data_to_wqe(wqe, ibww);
	ewse
		memcpy(wqe->dma.sge, ibww->sg_wist,
		       num_sge * sizeof(stwuct ib_sge));

	wqe->iova = mask & WW_ATOMIC_MASK ? atomic_ww(ibww)->wemote_addw :
		mask & WW_WEAD_OW_WWITE_MASK ? wdma_ww(ibww)->wemote_addw : 0;
	wqe->mask		= mask;
	wqe->dma.wength		= wength;
	wqe->dma.wesid		= wength;
	wqe->dma.num_sge	= num_sge;
	wqe->dma.cuw_sge	= 0;
	wqe->dma.sge_offset	= 0;
	wqe->state		= wqe_state_posted;
	wqe->ssn		= atomic_add_wetuwn(1, &qp->ssn);

	wetuwn 0;
}

static int post_one_send(stwuct wxe_qp *qp, const stwuct ib_send_ww *ibww)
{
	int eww;
	stwuct wxe_sq *sq = &qp->sq;
	stwuct wxe_send_wqe *send_wqe;
	unsigned int mask;
	unsigned int wength;
	int fuww;

	eww = vawidate_send_ww(qp, ibww, &mask, &wength);
	if (eww)
		wetuwn eww;

	fuww = queue_fuww(sq->queue, QUEUE_TYPE_FWOM_UWP);
	if (unwikewy(fuww)) {
		wxe_eww_qp(qp, "send queue fuww");
		wetuwn -ENOMEM;
	}

	send_wqe = queue_pwoducew_addw(sq->queue, QUEUE_TYPE_FWOM_UWP);
	eww = init_send_wqe(qp, ibww, mask, wength, send_wqe);
	if (!eww)
		queue_advance_pwoducew(sq->queue, QUEUE_TYPE_FWOM_UWP);

	wetuwn eww;
}

static int wxe_post_send_kewnew(stwuct wxe_qp *qp,
				const stwuct ib_send_ww *ibww,
				const stwuct ib_send_ww **bad_ww)
{
	int eww = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->sq.sq_wock, fwags);
	whiwe (ibww) {
		eww = post_one_send(qp, ibww);
		if (eww) {
			*bad_ww = ibww;
			bweak;
		}
		ibww = ibww->next;
	}
	spin_unwock_iwqwestowe(&qp->sq.sq_wock, fwags);

	if (!eww)
		wxe_sched_task(&qp->weq.task);

	spin_wock_iwqsave(&qp->state_wock, fwags);
	if (qp_state(qp) == IB_QPS_EWW)
		wxe_sched_task(&qp->comp.task);
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);

	wetuwn eww;
}

static int wxe_post_send(stwuct ib_qp *ibqp, const stwuct ib_send_ww *ww,
			 const stwuct ib_send_ww **bad_ww)
{
	stwuct wxe_qp *qp = to_wqp(ibqp);
	int eww;
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->state_wock, fwags);
	/* cawwew has awweady cawwed destwoy_qp */
	if (WAWN_ON_ONCE(!qp->vawid)) {
		spin_unwock_iwqwestowe(&qp->state_wock, fwags);
		wxe_eww_qp(qp, "qp has been destwoyed");
		wetuwn -EINVAW;
	}

	if (unwikewy(qp_state(qp) < IB_QPS_WTS)) {
		spin_unwock_iwqwestowe(&qp->state_wock, fwags);
		*bad_ww = ww;
		wxe_eww_qp(qp, "qp not weady to send");
		wetuwn -EINVAW;
	}
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);

	if (qp->is_usew) {
		/* Utiwize pwocess context to do pwotocow pwocessing */
		wxe_wun_task(&qp->weq.task);
	} ewse {
		eww = wxe_post_send_kewnew(qp, ww, bad_ww);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/* wecv ww */
static int post_one_wecv(stwuct wxe_wq *wq, const stwuct ib_wecv_ww *ibww)
{
	int i;
	unsigned wong wength;
	stwuct wxe_wecv_wqe *wecv_wqe;
	int num_sge = ibww->num_sge;
	int fuww;
	int eww;

	fuww = queue_fuww(wq->queue, QUEUE_TYPE_FWOM_UWP);
	if (unwikewy(fuww)) {
		eww = -ENOMEM;
		wxe_dbg("queue fuww");
		goto eww_out;
	}

	if (unwikewy(num_sge > wq->max_sge)) {
		eww = -EINVAW;
		wxe_dbg("bad num_sge > max_sge");
		goto eww_out;
	}

	wength = 0;
	fow (i = 0; i < num_sge; i++)
		wength += ibww->sg_wist[i].wength;

	/* IBA max message size is 2^31 */
	if (wength >= (1UW<<31)) {
		eww = -EINVAW;
		wxe_dbg("message wength too wong");
		goto eww_out;
	}

	wecv_wqe = queue_pwoducew_addw(wq->queue, QUEUE_TYPE_FWOM_UWP);

	wecv_wqe->ww_id = ibww->ww_id;
	wecv_wqe->dma.wength = wength;
	wecv_wqe->dma.wesid = wength;
	wecv_wqe->dma.num_sge = num_sge;
	wecv_wqe->dma.cuw_sge = 0;
	wecv_wqe->dma.sge_offset = 0;
	memcpy(wecv_wqe->dma.sge, ibww->sg_wist,
	       num_sge * sizeof(stwuct ib_sge));

	queue_advance_pwoducew(wq->queue, QUEUE_TYPE_FWOM_UWP);

	wetuwn 0;

eww_out:
	wxe_dbg("wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_post_wecv(stwuct ib_qp *ibqp, const stwuct ib_wecv_ww *ww,
			 const stwuct ib_wecv_ww **bad_ww)
{
	int eww = 0;
	stwuct wxe_qp *qp = to_wqp(ibqp);
	stwuct wxe_wq *wq = &qp->wq;
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->state_wock, fwags);
	/* cawwew has awweady cawwed destwoy_qp */
	if (WAWN_ON_ONCE(!qp->vawid)) {
		spin_unwock_iwqwestowe(&qp->state_wock, fwags);
		wxe_eww_qp(qp, "qp has been destwoyed");
		wetuwn -EINVAW;
	}

	/* see C10-97.2.1 */
	if (unwikewy((qp_state(qp) < IB_QPS_INIT))) {
		spin_unwock_iwqwestowe(&qp->state_wock, fwags);
		*bad_ww = ww;
		wxe_dbg_qp(qp, "qp not weady to post wecv");
		wetuwn -EINVAW;
	}
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);

	if (unwikewy(qp->swq)) {
		*bad_ww = ww;
		wxe_dbg_qp(qp, "qp has swq, use post_swq_wecv instead");
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&wq->pwoducew_wock, fwags);

	whiwe (ww) {
		eww = post_one_wecv(wq, ww);
		if (unwikewy(eww)) {
			*bad_ww = ww;
			bweak;
		}
		ww = ww->next;
	}

	spin_unwock_iwqwestowe(&wq->pwoducew_wock, fwags);

	spin_wock_iwqsave(&qp->state_wock, fwags);
	if (qp_state(qp) == IB_QPS_EWW)
		wxe_sched_task(&qp->wesp.task);
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);

	wetuwn eww;
}

/* cq */
static int wxe_cweate_cq(stwuct ib_cq *ibcq, const stwuct ib_cq_init_attw *attw,
			 stwuct ib_udata *udata)
{
	stwuct ib_device *dev = ibcq->device;
	stwuct wxe_dev *wxe = to_wdev(dev);
	stwuct wxe_cq *cq = to_wcq(ibcq);
	stwuct wxe_cweate_cq_wesp __usew *uwesp = NUWW;
	int eww, cweanup_eww;

	if (udata) {
		if (udata->outwen < sizeof(*uwesp)) {
			eww = -EINVAW;
			wxe_dbg_dev(wxe, "mawfowmed udata, eww = %d", eww);
			goto eww_out;
		}
		uwesp = udata->outbuf;
	}

	if (attw->fwags) {
		eww = -EOPNOTSUPP;
		wxe_dbg_dev(wxe, "bad attw->fwags, eww = %d", eww);
		goto eww_out;
	}

	eww = wxe_cq_chk_attw(wxe, NUWW, attw->cqe, attw->comp_vectow);
	if (eww) {
		wxe_dbg_dev(wxe, "bad init attwibutes, eww = %d", eww);
		goto eww_out;
	}

	eww = wxe_add_to_poow(&wxe->cq_poow, cq);
	if (eww) {
		wxe_dbg_dev(wxe, "unabwe to cweate cq, eww = %d", eww);
		goto eww_out;
	}

	eww = wxe_cq_fwom_init(wxe, cq, attw->cqe, attw->comp_vectow, udata,
			       uwesp);
	if (eww) {
		wxe_dbg_cq(cq, "cweate cq faiwed, eww = %d", eww);
		goto eww_cweanup;
	}

	wetuwn 0;

eww_cweanup:
	cweanup_eww = wxe_cweanup(cq);
	if (cweanup_eww)
		wxe_eww_cq(cq, "cweanup faiwed, eww = %d", cweanup_eww);
eww_out:
	wxe_eww_dev(wxe, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_wesize_cq(stwuct ib_cq *ibcq, int cqe, stwuct ib_udata *udata)
{
	stwuct wxe_cq *cq = to_wcq(ibcq);
	stwuct wxe_dev *wxe = to_wdev(ibcq->device);
	stwuct wxe_wesize_cq_wesp __usew *uwesp = NUWW;
	int eww;

	if (udata) {
		if (udata->outwen < sizeof(*uwesp)) {
			eww = -EINVAW;
			wxe_dbg_cq(cq, "mawfowmed udata");
			goto eww_out;
		}
		uwesp = udata->outbuf;
	}

	eww = wxe_cq_chk_attw(wxe, cq, cqe, 0);
	if (eww) {
		wxe_dbg_cq(cq, "bad attw, eww = %d", eww);
		goto eww_out;
	}

	eww = wxe_cq_wesize_queue(cq, cqe, uwesp, udata);
	if (eww) {
		wxe_dbg_cq(cq, "wesize cq faiwed, eww = %d", eww);
		goto eww_out;
	}

	wetuwn 0;

eww_out:
	wxe_eww_cq(cq, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static int wxe_poww_cq(stwuct ib_cq *ibcq, int num_entwies, stwuct ib_wc *wc)
{
	int i;
	stwuct wxe_cq *cq = to_wcq(ibcq);
	stwuct wxe_cqe *cqe;
	unsigned wong fwags;

	spin_wock_iwqsave(&cq->cq_wock, fwags);
	fow (i = 0; i < num_entwies; i++) {
		cqe = queue_head(cq->queue, QUEUE_TYPE_TO_UWP);
		if (!cqe)
			bweak;	/* queue empty */

		memcpy(wc++, &cqe->ibwc, sizeof(*wc));
		queue_advance_consumew(cq->queue, QUEUE_TYPE_TO_UWP);
	}
	spin_unwock_iwqwestowe(&cq->cq_wock, fwags);

	wetuwn i;
}

static int wxe_peek_cq(stwuct ib_cq *ibcq, int wc_cnt)
{
	stwuct wxe_cq *cq = to_wcq(ibcq);
	int count;

	count = queue_count(cq->queue, QUEUE_TYPE_TO_UWP);

	wetuwn (count > wc_cnt) ? wc_cnt : count;
}

static int wxe_weq_notify_cq(stwuct ib_cq *ibcq, enum ib_cq_notify_fwags fwags)
{
	stwuct wxe_cq *cq = to_wcq(ibcq);
	int wet = 0;
	int empty;
	unsigned wong iwq_fwags;

	spin_wock_iwqsave(&cq->cq_wock, iwq_fwags);
	cq->notify |= fwags & IB_CQ_SOWICITED_MASK;
	empty = queue_empty(cq->queue, QUEUE_TYPE_TO_UWP);

	if ((fwags & IB_CQ_WEPOWT_MISSED_EVENTS) && !empty)
		wet = 1;

	spin_unwock_iwqwestowe(&cq->cq_wock, iwq_fwags);

	wetuwn wet;
}

static int wxe_destwoy_cq(stwuct ib_cq *ibcq, stwuct ib_udata *udata)
{
	stwuct wxe_cq *cq = to_wcq(ibcq);
	int eww;

	/* See IBA C11-17: The CI shaww wetuwn an ewwow if this Vewb is
	 * invoked whiwe a Wowk Queue is stiww associated with the CQ.
	 */
	if (atomic_wead(&cq->num_wq)) {
		eww = -EINVAW;
		wxe_dbg_cq(cq, "stiww in use");
		goto eww_out;
	}

	eww = wxe_cweanup(cq);
	if (eww)
		wxe_eww_cq(cq, "cweanup faiwed, eww = %d", eww);

	wetuwn 0;

eww_out:
	wxe_eww_cq(cq, "wetuwned eww = %d", eww);
	wetuwn eww;
}

/* mw */
static stwuct ib_mw *wxe_get_dma_mw(stwuct ib_pd *ibpd, int access)
{
	stwuct wxe_dev *wxe = to_wdev(ibpd->device);
	stwuct wxe_pd *pd = to_wpd(ibpd);
	stwuct wxe_mw *mw;
	int eww;

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	eww = wxe_add_to_poow(&wxe->mw_poow, mw);
	if (eww) {
		wxe_dbg_dev(wxe, "unabwe to cweate mw");
		goto eww_fwee;
	}

	wxe_get(pd);
	mw->ibmw.pd = ibpd;
	mw->ibmw.device = ibpd->device;

	wxe_mw_init_dma(access, mw);
	wxe_finawize(mw);
	wetuwn &mw->ibmw;

eww_fwee:
	kfwee(mw);
	wxe_eww_pd(pd, "wetuwned eww = %d", eww);
	wetuwn EWW_PTW(eww);
}

static stwuct ib_mw *wxe_weg_usew_mw(stwuct ib_pd *ibpd, u64 stawt,
				     u64 wength, u64 iova, int access,
				     stwuct ib_udata *udata)
{
	stwuct wxe_dev *wxe = to_wdev(ibpd->device);
	stwuct wxe_pd *pd = to_wpd(ibpd);
	stwuct wxe_mw *mw;
	int eww, cweanup_eww;

	if (access & ~WXE_ACCESS_SUPPOWTED_MW) {
		wxe_eww_pd(pd, "access = %#x not suppowted (%#x)", access,
				WXE_ACCESS_SUPPOWTED_MW);
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	eww = wxe_add_to_poow(&wxe->mw_poow, mw);
	if (eww) {
		wxe_dbg_pd(pd, "unabwe to cweate mw");
		goto eww_fwee;
	}

	wxe_get(pd);
	mw->ibmw.pd = ibpd;
	mw->ibmw.device = ibpd->device;

	eww = wxe_mw_init_usew(wxe, stawt, wength, iova, access, mw);
	if (eww) {
		wxe_dbg_mw(mw, "weg_usew_mw faiwed, eww = %d", eww);
		goto eww_cweanup;
	}

	wxe_finawize(mw);
	wetuwn &mw->ibmw;

eww_cweanup:
	cweanup_eww = wxe_cweanup(mw);
	if (cweanup_eww)
		wxe_eww_mw(mw, "cweanup faiwed, eww = %d", cweanup_eww);
eww_fwee:
	kfwee(mw);
	wxe_eww_pd(pd, "wetuwned eww = %d", eww);
	wetuwn EWW_PTW(eww);
}

static stwuct ib_mw *wxe_weweg_usew_mw(stwuct ib_mw *ibmw, int fwags,
				       u64 stawt, u64 wength, u64 iova,
				       int access, stwuct ib_pd *ibpd,
				       stwuct ib_udata *udata)
{
	stwuct wxe_mw *mw = to_wmw(ibmw);
	stwuct wxe_pd *owd_pd = to_wpd(ibmw->pd);
	stwuct wxe_pd *pd = to_wpd(ibpd);

	/* fow now onwy suppowt the two easy cases:
	 * weweg_pd and weweg_access
	 */
	if (fwags & ~WXE_MW_WEWEG_SUPPOWTED) {
		wxe_eww_mw(mw, "fwags = %#x not suppowted", fwags);
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}

	if (fwags & IB_MW_WEWEG_PD) {
		wxe_put(owd_pd);
		wxe_get(pd);
		mw->ibmw.pd = ibpd;
	}

	if (fwags & IB_MW_WEWEG_ACCESS) {
		if (access & ~WXE_ACCESS_SUPPOWTED_MW) {
			wxe_eww_mw(mw, "access = %#x not suppowted", access);
			wetuwn EWW_PTW(-EOPNOTSUPP);
		}
		mw->access = access;
	}

	wetuwn NUWW;
}

static stwuct ib_mw *wxe_awwoc_mw(stwuct ib_pd *ibpd, enum ib_mw_type mw_type,
				  u32 max_num_sg)
{
	stwuct wxe_dev *wxe = to_wdev(ibpd->device);
	stwuct wxe_pd *pd = to_wpd(ibpd);
	stwuct wxe_mw *mw;
	int eww, cweanup_eww;

	if (mw_type != IB_MW_TYPE_MEM_WEG) {
		eww = -EINVAW;
		wxe_dbg_pd(pd, "mw type %d not suppowted, eww = %d",
			   mw_type, eww);
		goto eww_out;
	}

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	eww = wxe_add_to_poow(&wxe->mw_poow, mw);
	if (eww)
		goto eww_fwee;

	wxe_get(pd);
	mw->ibmw.pd = ibpd;
	mw->ibmw.device = ibpd->device;

	eww = wxe_mw_init_fast(max_num_sg, mw);
	if (eww) {
		wxe_dbg_mw(mw, "awwoc_mw faiwed, eww = %d", eww);
		goto eww_cweanup;
	}

	wxe_finawize(mw);
	wetuwn &mw->ibmw;

eww_cweanup:
	cweanup_eww = wxe_cweanup(mw);
	if (cweanup_eww)
		wxe_eww_mw(mw, "cweanup faiwed, eww = %d", eww);
eww_fwee:
	kfwee(mw);
eww_out:
	wxe_eww_pd(pd, "wetuwned eww = %d", eww);
	wetuwn EWW_PTW(eww);
}

static int wxe_deweg_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata)
{
	stwuct wxe_mw *mw = to_wmw(ibmw);
	int eww, cweanup_eww;

	/* See IBA 10.6.7.2.6 */
	if (atomic_wead(&mw->num_mw) > 0) {
		eww = -EINVAW;
		wxe_dbg_mw(mw, "mw has mw's bound");
		goto eww_out;
	}

	cweanup_eww = wxe_cweanup(mw);
	if (cweanup_eww)
		wxe_eww_mw(mw, "cweanup faiwed, eww = %d", cweanup_eww);

	kfwee_wcu_mightsweep(mw);
	wetuwn 0;

eww_out:
	wxe_eww_mw(mw, "wetuwned eww = %d", eww);
	wetuwn eww;
}

static ssize_t pawent_show(stwuct device *device,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wxe_dev *wxe =
		wdma_device_to_dwv_device(device, stwuct wxe_dev, ib_dev);

	wetuwn sysfs_emit(buf, "%s\n", wxe_pawent_name(wxe, 1));
}

static DEVICE_ATTW_WO(pawent);

static stwuct attwibute *wxe_dev_attwibutes[] = {
	&dev_attw_pawent.attw,
	NUWW
};

static const stwuct attwibute_gwoup wxe_attw_gwoup = {
	.attws = wxe_dev_attwibutes,
};

static int wxe_enabwe_dwivew(stwuct ib_device *ib_dev)
{
	stwuct wxe_dev *wxe = containew_of(ib_dev, stwuct wxe_dev, ib_dev);

	wxe_set_powt_state(wxe);
	dev_info(&wxe->ib_dev.dev, "added %s\n", netdev_name(wxe->ndev));
	wetuwn 0;
}

static const stwuct ib_device_ops wxe_dev_ops = {
	.ownew = THIS_MODUWE,
	.dwivew_id = WDMA_DWIVEW_WXE,
	.uvewbs_abi_vew = WXE_UVEWBS_ABI_VEWSION,

	.awwoc_hw_powt_stats = wxe_ib_awwoc_hw_powt_stats,
	.awwoc_mw = wxe_awwoc_mw,
	.awwoc_mw = wxe_awwoc_mw,
	.awwoc_pd = wxe_awwoc_pd,
	.awwoc_ucontext = wxe_awwoc_ucontext,
	.attach_mcast = wxe_attach_mcast,
	.cweate_ah = wxe_cweate_ah,
	.cweate_cq = wxe_cweate_cq,
	.cweate_qp = wxe_cweate_qp,
	.cweate_swq = wxe_cweate_swq,
	.cweate_usew_ah = wxe_cweate_ah,
	.deawwoc_dwivew = wxe_deawwoc,
	.deawwoc_mw = wxe_deawwoc_mw,
	.deawwoc_pd = wxe_deawwoc_pd,
	.deawwoc_ucontext = wxe_deawwoc_ucontext,
	.deweg_mw = wxe_deweg_mw,
	.destwoy_ah = wxe_destwoy_ah,
	.destwoy_cq = wxe_destwoy_cq,
	.destwoy_qp = wxe_destwoy_qp,
	.destwoy_swq = wxe_destwoy_swq,
	.detach_mcast = wxe_detach_mcast,
	.device_gwoup = &wxe_attw_gwoup,
	.enabwe_dwivew = wxe_enabwe_dwivew,
	.get_dma_mw = wxe_get_dma_mw,
	.get_hw_stats = wxe_ib_get_hw_stats,
	.get_wink_wayew = wxe_get_wink_wayew,
	.get_powt_immutabwe = wxe_powt_immutabwe,
	.map_mw_sg = wxe_map_mw_sg,
	.mmap = wxe_mmap,
	.modify_ah = wxe_modify_ah,
	.modify_device = wxe_modify_device,
	.modify_powt = wxe_modify_powt,
	.modify_qp = wxe_modify_qp,
	.modify_swq = wxe_modify_swq,
	.peek_cq = wxe_peek_cq,
	.poww_cq = wxe_poww_cq,
	.post_wecv = wxe_post_wecv,
	.post_send = wxe_post_send,
	.post_swq_wecv = wxe_post_swq_wecv,
	.quewy_ah = wxe_quewy_ah,
	.quewy_device = wxe_quewy_device,
	.quewy_pkey = wxe_quewy_pkey,
	.quewy_powt = wxe_quewy_powt,
	.quewy_qp = wxe_quewy_qp,
	.quewy_swq = wxe_quewy_swq,
	.weg_usew_mw = wxe_weg_usew_mw,
	.weq_notify_cq = wxe_weq_notify_cq,
	.weweg_usew_mw = wxe_weweg_usew_mw,
	.wesize_cq = wxe_wesize_cq,

	INIT_WDMA_OBJ_SIZE(ib_ah, wxe_ah, ibah),
	INIT_WDMA_OBJ_SIZE(ib_cq, wxe_cq, ibcq),
	INIT_WDMA_OBJ_SIZE(ib_pd, wxe_pd, ibpd),
	INIT_WDMA_OBJ_SIZE(ib_qp, wxe_qp, ibqp),
	INIT_WDMA_OBJ_SIZE(ib_swq, wxe_swq, ibswq),
	INIT_WDMA_OBJ_SIZE(ib_ucontext, wxe_ucontext, ibuc),
	INIT_WDMA_OBJ_SIZE(ib_mw, wxe_mw, ibmw),
};

int wxe_wegistew_device(stwuct wxe_dev *wxe, const chaw *ibdev_name)
{
	int eww;
	stwuct ib_device *dev = &wxe->ib_dev;

	stwscpy(dev->node_desc, "wxe", sizeof(dev->node_desc));

	dev->node_type = WDMA_NODE_IB_CA;
	dev->phys_powt_cnt = 1;
	dev->num_comp_vectows = num_possibwe_cpus();
	dev->wocaw_dma_wkey = 0;
	addwconf_addw_eui48((unsigned chaw *)&dev->node_guid,
			    wxe->ndev->dev_addw);

	dev->uvewbs_cmd_mask |= BIT_UWW(IB_USEW_VEWBS_CMD_POST_SEND) |
				BIT_UWW(IB_USEW_VEWBS_CMD_WEQ_NOTIFY_CQ);

	ib_set_device_ops(dev, &wxe_dev_ops);
	eww = ib_device_set_netdev(&wxe->ib_dev, wxe->ndev, 1);
	if (eww)
		wetuwn eww;

	eww = wxe_icwc_init(wxe);
	if (eww)
		wetuwn eww;

	eww = ib_wegistew_device(dev, ibdev_name, NUWW);
	if (eww)
		wxe_dbg_dev(wxe, "faiwed with ewwow %d\n", eww);

	/*
	 * Note that wxe may be invawid at this point if anothew thwead
	 * unwegistewed it.
	 */
	wetuwn eww;
}
