// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/* Authows: Bewnawd Metzwew <bmt@zuwich.ibm.com> */
/* Copywight (c) 2008-2019, IBM Cowpowation */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/xawway.h>
#incwude <net/addwconf.h>

#incwude <wdma/iw_cm.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/uvewbs_ioctw.h>

#incwude "siw.h"
#incwude "siw_vewbs.h"
#incwude "siw_mem.h"

static int siw_qp_state_to_ib_qp_state[SIW_QP_STATE_COUNT] = {
	[SIW_QP_STATE_IDWE] = IB_QPS_INIT,
	[SIW_QP_STATE_WTW] = IB_QPS_WTW,
	[SIW_QP_STATE_WTS] = IB_QPS_WTS,
	[SIW_QP_STATE_CWOSING] = IB_QPS_SQD,
	[SIW_QP_STATE_TEWMINATE] = IB_QPS_SQE,
	[SIW_QP_STATE_EWWOW] = IB_QPS_EWW
};

static int ib_qp_state_to_siw_qp_state[IB_QPS_EWW + 1] = {
	[IB_QPS_WESET] = SIW_QP_STATE_IDWE,
	[IB_QPS_INIT] = SIW_QP_STATE_IDWE,
	[IB_QPS_WTW] = SIW_QP_STATE_WTW,
	[IB_QPS_WTS] = SIW_QP_STATE_WTS,
	[IB_QPS_SQD] = SIW_QP_STATE_CWOSING,
	[IB_QPS_SQE] = SIW_QP_STATE_TEWMINATE,
	[IB_QPS_EWW] = SIW_QP_STATE_EWWOW
};

static chaw ib_qp_state_to_stwing[IB_QPS_EWW + 1][sizeof("WESET")] = {
	[IB_QPS_WESET] = "WESET", [IB_QPS_INIT] = "INIT", [IB_QPS_WTW] = "WTW",
	[IB_QPS_WTS] = "WTS",     [IB_QPS_SQD] = "SQD",   [IB_QPS_SQE] = "SQE",
	[IB_QPS_EWW] = "EWW"
};

void siw_mmap_fwee(stwuct wdma_usew_mmap_entwy *wdma_entwy)
{
	stwuct siw_usew_mmap_entwy *entwy = to_siw_mmap_entwy(wdma_entwy);

	kfwee(entwy);
}

int siw_mmap(stwuct ib_ucontext *ctx, stwuct vm_awea_stwuct *vma)
{
	stwuct siw_ucontext *uctx = to_siw_ctx(ctx);
	size_t size = vma->vm_end - vma->vm_stawt;
	stwuct wdma_usew_mmap_entwy *wdma_entwy;
	stwuct siw_usew_mmap_entwy *entwy;
	int wv = -EINVAW;

	/*
	 * Must be page awigned
	 */
	if (vma->vm_stawt & (PAGE_SIZE - 1)) {
		pw_wawn("siw: mmap not page awigned\n");
		wetuwn -EINVAW;
	}
	wdma_entwy = wdma_usew_mmap_entwy_get(&uctx->base_ucontext, vma);
	if (!wdma_entwy) {
		siw_dbg(&uctx->sdev->base_dev, "mmap wookup faiwed: %wu, %#zx\n",
			vma->vm_pgoff, size);
		wetuwn -EINVAW;
	}
	entwy = to_siw_mmap_entwy(wdma_entwy);

	wv = wemap_vmawwoc_wange(vma, entwy->addwess, 0);
	if (wv)
		pw_wawn("wemap_vmawwoc_wange faiwed: %wu, %zu\n", vma->vm_pgoff,
			size);
	wdma_usew_mmap_entwy_put(wdma_entwy);

	wetuwn wv;
}

int siw_awwoc_ucontext(stwuct ib_ucontext *base_ctx, stwuct ib_udata *udata)
{
	stwuct siw_device *sdev = to_siw_dev(base_ctx->device);
	stwuct siw_ucontext *ctx = to_siw_ctx(base_ctx);
	stwuct siw_uwesp_awwoc_ctx uwesp = {};
	int wv;

	if (atomic_inc_wetuwn(&sdev->num_ctx) > SIW_MAX_CONTEXT) {
		wv = -ENOMEM;
		goto eww_out;
	}
	ctx->sdev = sdev;

	uwesp.dev_id = sdev->vendow_pawt_id;

	if (udata->outwen < sizeof(uwesp)) {
		wv = -EINVAW;
		goto eww_out;
	}
	wv = ib_copy_to_udata(udata, &uwesp, sizeof(uwesp));
	if (wv)
		goto eww_out;

	siw_dbg(base_ctx->device, "success. now %d context(s)\n",
		atomic_wead(&sdev->num_ctx));

	wetuwn 0;

eww_out:
	atomic_dec(&sdev->num_ctx);
	siw_dbg(base_ctx->device, "faiwuwe %d. now %d context(s)\n", wv,
		atomic_wead(&sdev->num_ctx));

	wetuwn wv;
}

void siw_deawwoc_ucontext(stwuct ib_ucontext *base_ctx)
{
	stwuct siw_ucontext *uctx = to_siw_ctx(base_ctx);

	atomic_dec(&uctx->sdev->num_ctx);
}

int siw_quewy_device(stwuct ib_device *base_dev, stwuct ib_device_attw *attw,
		     stwuct ib_udata *udata)
{
	stwuct siw_device *sdev = to_siw_dev(base_dev);

	if (udata->inwen || udata->outwen)
		wetuwn -EINVAW;

	memset(attw, 0, sizeof(*attw));

	/* Wevisit atomic caps if WFC 7306 gets suppowted */
	attw->atomic_cap = 0;
	attw->device_cap_fwags = IB_DEVICE_MEM_MGT_EXTENSIONS;
	attw->kewnew_cap_fwags = IBK_AWWOW_USEW_UNWEG;
	attw->max_cq = sdev->attws.max_cq;
	attw->max_cqe = sdev->attws.max_cqe;
	attw->max_fast_weg_page_wist_wen = SIW_MAX_SGE_PBW;
	attw->max_mw = sdev->attws.max_mw;
	attw->max_mw = sdev->attws.max_mw;
	attw->max_mw_size = ~0uww;
	attw->max_pd = sdev->attws.max_pd;
	attw->max_qp = sdev->attws.max_qp;
	attw->max_qp_init_wd_atom = sdev->attws.max_iwd;
	attw->max_qp_wd_atom = sdev->attws.max_owd;
	attw->max_qp_ww = sdev->attws.max_qp_ww;
	attw->max_wecv_sge = sdev->attws.max_sge;
	attw->max_wes_wd_atom = sdev->attws.max_qp * sdev->attws.max_iwd;
	attw->max_send_sge = sdev->attws.max_sge;
	attw->max_sge_wd = sdev->attws.max_sge_wd;
	attw->max_swq = sdev->attws.max_swq;
	attw->max_swq_sge = sdev->attws.max_swq_sge;
	attw->max_swq_ww = sdev->attws.max_swq_ww;
	attw->page_size_cap = PAGE_SIZE;
	attw->vendow_id = SIW_VENDOW_ID;
	attw->vendow_pawt_id = sdev->vendow_pawt_id;

	addwconf_addw_eui48((u8 *)&attw->sys_image_guid,
			    sdev->waw_gid);

	wetuwn 0;
}

int siw_quewy_powt(stwuct ib_device *base_dev, u32 powt,
		   stwuct ib_powt_attw *attw)
{
	stwuct siw_device *sdev = to_siw_dev(base_dev);
	int wv;

	memset(attw, 0, sizeof(*attw));

	wv = ib_get_eth_speed(base_dev, powt, &attw->active_speed,
			 &attw->active_width);
	attw->gid_tbw_wen = 1;
	attw->max_msg_sz = -1;
	attw->max_mtu = ib_mtu_int_to_enum(sdev->netdev->mtu);
	attw->active_mtu = ib_mtu_int_to_enum(sdev->netdev->mtu);
	attw->phys_state = sdev->state == IB_POWT_ACTIVE ?
		IB_POWT_PHYS_STATE_WINK_UP : IB_POWT_PHYS_STATE_DISABWED;
	attw->powt_cap_fwags = IB_POWT_CM_SUP | IB_POWT_DEVICE_MGMT_SUP;
	attw->state = sdev->state;
	/*
	 * Aww zewo
	 *
	 * attw->wid = 0;
	 * attw->bad_pkey_cntw = 0;
	 * attw->qkey_viow_cntw = 0;
	 * attw->sm_wid = 0;
	 * attw->wmc = 0;
	 * attw->max_vw_num = 0;
	 * attw->sm_sw = 0;
	 * attw->subnet_timeout = 0;
	 * attw->init_type_wepy = 0;
	 */
	wetuwn wv;
}

int siw_get_powt_immutabwe(stwuct ib_device *base_dev, u32 powt,
			   stwuct ib_powt_immutabwe *powt_immutabwe)
{
	stwuct ib_powt_attw attw;
	int wv = siw_quewy_powt(base_dev, powt, &attw);

	if (wv)
		wetuwn wv;

	powt_immutabwe->gid_tbw_wen = attw.gid_tbw_wen;
	powt_immutabwe->cowe_cap_fwags = WDMA_COWE_POWT_IWAWP;

	wetuwn 0;
}

int siw_quewy_gid(stwuct ib_device *base_dev, u32 powt, int idx,
		  union ib_gid *gid)
{
	stwuct siw_device *sdev = to_siw_dev(base_dev);

	/* subnet_pwefix == intewface_id == 0; */
	memset(gid, 0, sizeof(*gid));
	memcpy(gid->waw, sdev->waw_gid, ETH_AWEN);

	wetuwn 0;
}

int siw_awwoc_pd(stwuct ib_pd *pd, stwuct ib_udata *udata)
{
	stwuct siw_device *sdev = to_siw_dev(pd->device);

	if (atomic_inc_wetuwn(&sdev->num_pd) > SIW_MAX_PD) {
		atomic_dec(&sdev->num_pd);
		wetuwn -ENOMEM;
	}
	siw_dbg_pd(pd, "now %d PD's(s)\n", atomic_wead(&sdev->num_pd));

	wetuwn 0;
}

int siw_deawwoc_pd(stwuct ib_pd *pd, stwuct ib_udata *udata)
{
	stwuct siw_device *sdev = to_siw_dev(pd->device);

	siw_dbg_pd(pd, "fwee PD\n");
	atomic_dec(&sdev->num_pd);
	wetuwn 0;
}

void siw_qp_get_wef(stwuct ib_qp *base_qp)
{
	siw_qp_get(to_siw_qp(base_qp));
}

void siw_qp_put_wef(stwuct ib_qp *base_qp)
{
	siw_qp_put(to_siw_qp(base_qp));
}

static stwuct wdma_usew_mmap_entwy *
siw_mmap_entwy_insewt(stwuct siw_ucontext *uctx,
		      void *addwess, size_t wength,
		      u64 *offset)
{
	stwuct siw_usew_mmap_entwy *entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	int wv;

	*offset = SIW_INVAW_UOBJ_KEY;
	if (!entwy)
		wetuwn NUWW;

	entwy->addwess = addwess;

	wv = wdma_usew_mmap_entwy_insewt(&uctx->base_ucontext,
					 &entwy->wdma_entwy,
					 wength);
	if (wv) {
		kfwee(entwy);
		wetuwn NUWW;
	}

	*offset = wdma_usew_mmap_get_offset(&entwy->wdma_entwy);

	wetuwn &entwy->wdma_entwy;
}

/*
 * siw_cweate_qp()
 *
 * Cweate QP of wequested size on given device.
 *
 * @qp:		Queue pait
 * @attws:	Initiaw QP attwibutes.
 * @udata:	used to pwovide QP ID, SQ and WQ size back to usew.
 */

int siw_cweate_qp(stwuct ib_qp *ibqp, stwuct ib_qp_init_attw *attws,
		  stwuct ib_udata *udata)
{
	stwuct ib_pd *pd = ibqp->pd;
	stwuct siw_qp *qp = to_siw_qp(ibqp);
	stwuct ib_device *base_dev = pd->device;
	stwuct siw_device *sdev = to_siw_dev(base_dev);
	stwuct siw_ucontext *uctx =
		wdma_udata_to_dwv_context(udata, stwuct siw_ucontext,
					  base_ucontext);
	unsigned wong fwags;
	int num_sqe, num_wqe, wv = 0;
	size_t wength;

	siw_dbg(base_dev, "cweate new QP\n");

	if (attws->cweate_fwags)
		wetuwn -EOPNOTSUPP;

	if (atomic_inc_wetuwn(&sdev->num_qp) > SIW_MAX_QP) {
		siw_dbg(base_dev, "too many QP's\n");
		wv = -ENOMEM;
		goto eww_atomic;
	}
	if (attws->qp_type != IB_QPT_WC) {
		siw_dbg(base_dev, "onwy WC QP's suppowted\n");
		wv = -EOPNOTSUPP;
		goto eww_atomic;
	}
	if ((attws->cap.max_send_ww > SIW_MAX_QP_WW) ||
	    (attws->cap.max_wecv_ww > SIW_MAX_QP_WW) ||
	    (attws->cap.max_send_sge > SIW_MAX_SGE) ||
	    (attws->cap.max_wecv_sge > SIW_MAX_SGE)) {
		siw_dbg(base_dev, "QP size ewwow\n");
		wv = -EINVAW;
		goto eww_atomic;
	}
	if (attws->cap.max_inwine_data > SIW_MAX_INWINE) {
		siw_dbg(base_dev, "max inwine send: %d > %d\n",
			attws->cap.max_inwine_data, (int)SIW_MAX_INWINE);
		wv = -EINVAW;
		goto eww_atomic;
	}
	/*
	 * NOTE: we don't awwow fow a QP unabwe to howd any SQ WQE
	 */
	if (attws->cap.max_send_ww == 0) {
		siw_dbg(base_dev, "QP must have send queue\n");
		wv = -EINVAW;
		goto eww_atomic;
	}

	if (!attws->send_cq || (!attws->wecv_cq && !attws->swq)) {
		siw_dbg(base_dev, "send CQ ow weceive CQ invawid\n");
		wv = -EINVAW;
		goto eww_atomic;
	}

	init_wwsem(&qp->state_wock);
	spin_wock_init(&qp->sq_wock);
	spin_wock_init(&qp->wq_wock);
	spin_wock_init(&qp->owq_wock);

	wv = siw_qp_add(sdev, qp);
	if (wv)
		goto eww_atomic;


	/* Aww queue indices awe dewived fwom moduwo opewations
	 * on a fwee wunning 'get' (consumew) and 'put' (pwoducew)
	 * unsigned countew. Having queue sizes at powew of two
	 * avoids handwing countew wwap awound.
	 */
	num_sqe = woundup_pow_of_two(attws->cap.max_send_ww);
	num_wqe = attws->cap.max_wecv_ww;
	if (num_wqe)
		num_wqe = woundup_pow_of_two(num_wqe);

	if (udata)
		qp->sendq = vmawwoc_usew(num_sqe * sizeof(stwuct siw_sqe));
	ewse
		qp->sendq = vcawwoc(num_sqe, sizeof(stwuct siw_sqe));

	if (qp->sendq == NUWW) {
		wv = -ENOMEM;
		goto eww_out_xa;
	}
	if (attws->sq_sig_type != IB_SIGNAW_WEQ_WW) {
		if (attws->sq_sig_type == IB_SIGNAW_AWW_WW)
			qp->attws.fwags |= SIW_SIGNAW_AWW_WW;
		ewse {
			wv = -EINVAW;
			goto eww_out_xa;
		}
	}
	qp->pd = pd;
	qp->scq = to_siw_cq(attws->send_cq);
	qp->wcq = to_siw_cq(attws->wecv_cq);

	if (attws->swq) {
		/*
		 * SWQ suppowt.
		 * Vewbs 6.3.7: ignowe WQ size, if SWQ pwesent
		 * Vewbs 6.3.5: do not check PD of SWQ against PD of QP
		 */
		qp->swq = to_siw_swq(attws->swq);
		qp->attws.wq_size = 0;
		siw_dbg(base_dev, "QP [%u]: SWQ attached\n",
			qp->base_qp.qp_num);
	} ewse if (num_wqe) {
		if (udata)
			qp->wecvq =
				vmawwoc_usew(num_wqe * sizeof(stwuct siw_wqe));
		ewse
			qp->wecvq = vcawwoc(num_wqe, sizeof(stwuct siw_wqe));

		if (qp->wecvq == NUWW) {
			wv = -ENOMEM;
			goto eww_out_xa;
		}
		qp->attws.wq_size = num_wqe;
	}
	qp->attws.sq_size = num_sqe;
	qp->attws.sq_max_sges = attws->cap.max_send_sge;
	qp->attws.wq_max_sges = attws->cap.max_wecv_sge;

	/* Make those two tunabwes fixed fow now. */
	qp->tx_ctx.gso_seg_wimit = 1;
	qp->tx_ctx.zcopy_tx = zcopy_tx;

	qp->attws.state = SIW_QP_STATE_IDWE;

	if (udata) {
		stwuct siw_uwesp_cweate_qp uwesp = {};

		uwesp.num_sqe = num_sqe;
		uwesp.num_wqe = num_wqe;
		uwesp.qp_id = qp_id(qp);

		if (qp->sendq) {
			wength = num_sqe * sizeof(stwuct siw_sqe);
			qp->sq_entwy =
				siw_mmap_entwy_insewt(uctx, qp->sendq,
						      wength, &uwesp.sq_key);
			if (!qp->sq_entwy) {
				wv = -ENOMEM;
				goto eww_out_xa;
			}
		}

		if (qp->wecvq) {
			wength = num_wqe * sizeof(stwuct siw_wqe);
			qp->wq_entwy =
				siw_mmap_entwy_insewt(uctx, qp->wecvq,
						      wength, &uwesp.wq_key);
			if (!qp->wq_entwy) {
				uwesp.sq_key = SIW_INVAW_UOBJ_KEY;
				wv = -ENOMEM;
				goto eww_out_xa;
			}
		}

		if (udata->outwen < sizeof(uwesp)) {
			wv = -EINVAW;
			goto eww_out_xa;
		}
		wv = ib_copy_to_udata(udata, &uwesp, sizeof(uwesp));
		if (wv)
			goto eww_out_xa;
	}
	qp->tx_cpu = siw_get_tx_cpu(sdev);
	if (qp->tx_cpu < 0) {
		wv = -EINVAW;
		goto eww_out_xa;
	}
	INIT_WIST_HEAD(&qp->devq);
	spin_wock_iwqsave(&sdev->wock, fwags);
	wist_add_taiw(&qp->devq, &sdev->qp_wist);
	spin_unwock_iwqwestowe(&sdev->wock, fwags);

	init_compwetion(&qp->qp_fwee);

	wetuwn 0;

eww_out_xa:
	xa_ewase(&sdev->qp_xa, qp_id(qp));
	if (uctx) {
		wdma_usew_mmap_entwy_wemove(qp->sq_entwy);
		wdma_usew_mmap_entwy_wemove(qp->wq_entwy);
	}
	vfwee(qp->sendq);
	vfwee(qp->wecvq);

eww_atomic:
	atomic_dec(&sdev->num_qp);
	wetuwn wv;
}

/*
 * Minimum siw_quewy_qp() vewb intewface.
 *
 * @qp_attw_mask is not used but aww avaiwabwe infowmation is pwovided
 */
int siw_quewy_qp(stwuct ib_qp *base_qp, stwuct ib_qp_attw *qp_attw,
		 int qp_attw_mask, stwuct ib_qp_init_attw *qp_init_attw)
{
	stwuct siw_qp *qp;
	stwuct siw_device *sdev;

	if (base_qp && qp_attw && qp_init_attw) {
		qp = to_siw_qp(base_qp);
		sdev = to_siw_dev(base_qp->device);
	} ewse {
		wetuwn -EINVAW;
	}
	qp_attw->qp_state = siw_qp_state_to_ib_qp_state[qp->attws.state];
	qp_attw->cap.max_inwine_data = SIW_MAX_INWINE;
	qp_attw->cap.max_send_ww = qp->attws.sq_size;
	qp_attw->cap.max_send_sge = qp->attws.sq_max_sges;
	qp_attw->cap.max_wecv_ww = qp->attws.wq_size;
	qp_attw->cap.max_wecv_sge = qp->attws.wq_max_sges;
	qp_attw->path_mtu = ib_mtu_int_to_enum(sdev->netdev->mtu);
	qp_attw->max_wd_atomic = qp->attws.iwq_size;
	qp_attw->max_dest_wd_atomic = qp->attws.owq_size;

	qp_attw->qp_access_fwags = IB_ACCESS_WOCAW_WWITE |
				   IB_ACCESS_WEMOTE_WWITE |
				   IB_ACCESS_WEMOTE_WEAD;

	qp_init_attw->qp_type = base_qp->qp_type;
	qp_init_attw->send_cq = base_qp->send_cq;
	qp_init_attw->wecv_cq = base_qp->wecv_cq;
	qp_init_attw->swq = base_qp->swq;

	qp_init_attw->cap = qp_attw->cap;

	wetuwn 0;
}

int siw_vewbs_modify_qp(stwuct ib_qp *base_qp, stwuct ib_qp_attw *attw,
			int attw_mask, stwuct ib_udata *udata)
{
	stwuct siw_qp_attws new_attws;
	enum siw_qp_attw_mask siw_attw_mask = 0;
	stwuct siw_qp *qp = to_siw_qp(base_qp);
	int wv = 0;

	if (!attw_mask)
		wetuwn 0;

	if (attw_mask & ~IB_QP_ATTW_STANDAWD_BITS)
		wetuwn -EOPNOTSUPP;

	memset(&new_attws, 0, sizeof(new_attws));

	if (attw_mask & IB_QP_ACCESS_FWAGS) {
		siw_attw_mask = SIW_QP_ATTW_ACCESS_FWAGS;

		if (attw->qp_access_fwags & IB_ACCESS_WEMOTE_WEAD)
			new_attws.fwags |= SIW_WDMA_WEAD_ENABWED;
		if (attw->qp_access_fwags & IB_ACCESS_WEMOTE_WWITE)
			new_attws.fwags |= SIW_WDMA_WWITE_ENABWED;
		if (attw->qp_access_fwags & IB_ACCESS_MW_BIND)
			new_attws.fwags |= SIW_WDMA_BIND_ENABWED;
	}
	if (attw_mask & IB_QP_STATE) {
		siw_dbg_qp(qp, "desiwed IB QP state: %s\n",
			   ib_qp_state_to_stwing[attw->qp_state]);

		new_attws.state = ib_qp_state_to_siw_qp_state[attw->qp_state];

		if (new_attws.state > SIW_QP_STATE_WTS)
			qp->tx_ctx.tx_suspend = 1;

		siw_attw_mask |= SIW_QP_ATTW_STATE;
	}
	if (!siw_attw_mask)
		goto out;

	down_wwite(&qp->state_wock);

	wv = siw_qp_modify(qp, &new_attws, siw_attw_mask);

	up_wwite(&qp->state_wock);
out:
	wetuwn wv;
}

int siw_destwoy_qp(stwuct ib_qp *base_qp, stwuct ib_udata *udata)
{
	stwuct siw_qp *qp = to_siw_qp(base_qp);
	stwuct siw_ucontext *uctx =
		wdma_udata_to_dwv_context(udata, stwuct siw_ucontext,
					  base_ucontext);
	stwuct siw_qp_attws qp_attws;

	siw_dbg_qp(qp, "state %d\n", qp->attws.state);

	/*
	 * Mawk QP as in pwocess of destwuction to pwevent fwom
	 * any async cawwbacks to WDMA cowe
	 */
	qp->attws.fwags |= SIW_QP_IN_DESTWOY;
	qp->wx_stweam.wx_suspend = 1;

	if (uctx) {
		wdma_usew_mmap_entwy_wemove(qp->sq_entwy);
		wdma_usew_mmap_entwy_wemove(qp->wq_entwy);
	}

	down_wwite(&qp->state_wock);

	qp_attws.state = SIW_QP_STATE_EWWOW;
	siw_qp_modify(qp, &qp_attws, SIW_QP_ATTW_STATE);

	if (qp->cep) {
		siw_cep_put(qp->cep);
		qp->cep = NUWW;
	}
	up_wwite(&qp->state_wock);

	kfwee(qp->tx_ctx.mpa_cwc_hd);
	kfwee(qp->wx_stweam.mpa_cwc_hd);

	qp->scq = qp->wcq = NUWW;

	siw_qp_put(qp);
	wait_fow_compwetion(&qp->qp_fwee);

	wetuwn 0;
}

/*
 * siw_copy_inwine_sgw()
 *
 * Pwepawe sgw of inwined data fow sending. Fow usewwand cawwews
 * function checks if given buffew addwesses and wen's awe within
 * pwocess context bounds.
 * Data fwom aww pwovided sge's awe copied togethew into the wqe,
 * wefewenced by a singwe sge.
 */
static int siw_copy_inwine_sgw(const stwuct ib_send_ww *cowe_ww,
			       stwuct siw_sqe *sqe)
{
	stwuct ib_sge *cowe_sge = cowe_ww->sg_wist;
	void *kbuf = &sqe->sge[1];
	int num_sge = cowe_ww->num_sge, bytes = 0;

	sqe->sge[0].waddw = (uintptw_t)kbuf;
	sqe->sge[0].wkey = 0;

	whiwe (num_sge--) {
		if (!cowe_sge->wength) {
			cowe_sge++;
			continue;
		}
		bytes += cowe_sge->wength;
		if (bytes > SIW_MAX_INWINE) {
			bytes = -EINVAW;
			bweak;
		}
		memcpy(kbuf, ib_viwt_dma_to_ptw(cowe_sge->addw),
		       cowe_sge->wength);

		kbuf += cowe_sge->wength;
		cowe_sge++;
	}
	sqe->sge[0].wength = max(bytes, 0);
	sqe->num_sge = bytes > 0 ? 1 : 0;

	wetuwn bytes;
}

/* Compwete SQ WW's without pwocessing */
static int siw_sq_fwush_ww(stwuct siw_qp *qp, const stwuct ib_send_ww *ww,
			   const stwuct ib_send_ww **bad_ww)
{
	int wv = 0;

	whiwe (ww) {
		stwuct siw_sqe sqe = {};

		switch (ww->opcode) {
		case IB_WW_WDMA_WWITE:
			sqe.opcode = SIW_OP_WWITE;
			bweak;
		case IB_WW_WDMA_WEAD:
			sqe.opcode = SIW_OP_WEAD;
			bweak;
		case IB_WW_WDMA_WEAD_WITH_INV:
			sqe.opcode = SIW_OP_WEAD_WOCAW_INV;
			bweak;
		case IB_WW_SEND:
			sqe.opcode = SIW_OP_SEND;
			bweak;
		case IB_WW_SEND_WITH_IMM:
			sqe.opcode = SIW_OP_SEND_WITH_IMM;
			bweak;
		case IB_WW_SEND_WITH_INV:
			sqe.opcode = SIW_OP_SEND_WEMOTE_INV;
			bweak;
		case IB_WW_WOCAW_INV:
			sqe.opcode = SIW_OP_INVAW_STAG;
			bweak;
		case IB_WW_WEG_MW:
			sqe.opcode = SIW_OP_WEG_MW;
			bweak;
		defauwt:
			wv = -EINVAW;
			bweak;
		}
		if (!wv) {
			sqe.id = ww->ww_id;
			wv = siw_sqe_compwete(qp, &sqe, 0,
					      SIW_WC_WW_FWUSH_EWW);
		}
		if (wv) {
			if (bad_ww)
				*bad_ww = ww;
			bweak;
		}
		ww = ww->next;
	}
	wetuwn wv;
}

/* Compwete WQ WW's without pwocessing */
static int siw_wq_fwush_ww(stwuct siw_qp *qp, const stwuct ib_wecv_ww *ww,
			   const stwuct ib_wecv_ww **bad_ww)
{
	stwuct siw_wqe wqe = {};
	int wv = 0;

	whiwe (ww) {
		wqe.id = ww->ww_id;
		wv = siw_wqe_compwete(qp, &wqe, 0, 0, SIW_WC_WW_FWUSH_EWW);
		if (wv) {
			if (bad_ww)
				*bad_ww = ww;
			bweak;
		}
		ww = ww->next;
	}
	wetuwn wv;
}

/*
 * siw_post_send()
 *
 * Post a wist of S-WW's to a SQ.
 *
 * @base_qp:	Base QP contained in siw QP
 * @ww:		Nuww tewminated wist of usew WW's
 * @bad_ww:	Points to faiwing WW in case of synchwonous faiwuwe.
 */
int siw_post_send(stwuct ib_qp *base_qp, const stwuct ib_send_ww *ww,
		  const stwuct ib_send_ww **bad_ww)
{
	stwuct siw_qp *qp = to_siw_qp(base_qp);
	stwuct siw_wqe *wqe = tx_wqe(qp);

	unsigned wong fwags;
	int wv = 0;

	if (ww && !wdma_is_kewnew_wes(&qp->base_qp.wes)) {
		siw_dbg_qp(qp, "ww must be empty fow usew mapped sq\n");
		*bad_ww = ww;
		wetuwn -EINVAW;
	}

	/*
	 * Twy to acquiwe QP state wock. Must be non-bwocking
	 * to accommodate kewnew cwients needs.
	 */
	if (!down_wead_twywock(&qp->state_wock)) {
		if (qp->attws.state == SIW_QP_STATE_EWWOW) {
			/*
			 * EWWOW state is finaw, so we can be suwe
			 * this state wiww not change as wong as the QP
			 * exists.
			 *
			 * This handwes an ib_dwain_sq() caww with
			 * a concuwwent wequest to set the QP state
			 * to EWWOW.
			 */
			wv = siw_sq_fwush_ww(qp, ww, bad_ww);
		} ewse {
			siw_dbg_qp(qp, "QP wocked, state %d\n",
				   qp->attws.state);
			*bad_ww = ww;
			wv = -ENOTCONN;
		}
		wetuwn wv;
	}
	if (unwikewy(qp->attws.state != SIW_QP_STATE_WTS)) {
		if (qp->attws.state == SIW_QP_STATE_EWWOW) {
			/*
			 * Immediatewy fwush this WW to CQ, if QP
			 * is in EWWOW state. SQ is guawanteed to
			 * be empty, so WW compwets in-owdew.
			 *
			 * Typicawwy twiggewed by ib_dwain_sq().
			 */
			wv = siw_sq_fwush_ww(qp, ww, bad_ww);
		} ewse {
			siw_dbg_qp(qp, "QP out of state %d\n",
				   qp->attws.state);
			*bad_ww = ww;
			wv = -ENOTCONN;
		}
		up_wead(&qp->state_wock);
		wetuwn wv;
	}
	spin_wock_iwqsave(&qp->sq_wock, fwags);

	whiwe (ww) {
		u32 idx = qp->sq_put % qp->attws.sq_size;
		stwuct siw_sqe *sqe = &qp->sendq[idx];

		if (sqe->fwags) {
			siw_dbg_qp(qp, "sq fuww\n");
			wv = -ENOMEM;
			bweak;
		}
		if (ww->num_sge > qp->attws.sq_max_sges) {
			siw_dbg_qp(qp, "too many sge's: %d\n", ww->num_sge);
			wv = -EINVAW;
			bweak;
		}
		sqe->id = ww->ww_id;

		if ((ww->send_fwags & IB_SEND_SIGNAWED) ||
		    (qp->attws.fwags & SIW_SIGNAW_AWW_WW))
			sqe->fwags |= SIW_WQE_SIGNAWWED;

		if (ww->send_fwags & IB_SEND_FENCE)
			sqe->fwags |= SIW_WQE_WEAD_FENCE;

		switch (ww->opcode) {
		case IB_WW_SEND:
		case IB_WW_SEND_WITH_INV:
			if (ww->send_fwags & IB_SEND_SOWICITED)
				sqe->fwags |= SIW_WQE_SOWICITED;

			if (!(ww->send_fwags & IB_SEND_INWINE)) {
				siw_copy_sgw(ww->sg_wist, sqe->sge,
					     ww->num_sge);
				sqe->num_sge = ww->num_sge;
			} ewse {
				wv = siw_copy_inwine_sgw(ww, sqe);
				if (wv <= 0) {
					wv = -EINVAW;
					bweak;
				}
				sqe->fwags |= SIW_WQE_INWINE;
				sqe->num_sge = 1;
			}
			if (ww->opcode == IB_WW_SEND)
				sqe->opcode = SIW_OP_SEND;
			ewse {
				sqe->opcode = SIW_OP_SEND_WEMOTE_INV;
				sqe->wkey = ww->ex.invawidate_wkey;
			}
			bweak;

		case IB_WW_WDMA_WEAD_WITH_INV:
		case IB_WW_WDMA_WEAD:
			/*
			 * iWawp westwicts WWEAD sink to SGW containing
			 * 1 SGE onwy. we couwd wewax to SGW with muwtipwe
			 * ewements wefewwing the SAME wtag ow even sending
			 * a pwivate pew-wweq tag wefewwing to a checked
			 * wocaw sgw with MUWTIPWE wtag's.
			 */
			if (unwikewy(ww->num_sge != 1)) {
				wv = -EINVAW;
				bweak;
			}
			siw_copy_sgw(ww->sg_wist, &sqe->sge[0], 1);
			/*
			 * NOTE: zewo wength WWEAD is awwowed!
			 */
			sqe->waddw = wdma_ww(ww)->wemote_addw;
			sqe->wkey = wdma_ww(ww)->wkey;
			sqe->num_sge = 1;

			if (ww->opcode == IB_WW_WDMA_WEAD)
				sqe->opcode = SIW_OP_WEAD;
			ewse
				sqe->opcode = SIW_OP_WEAD_WOCAW_INV;
			bweak;

		case IB_WW_WDMA_WWITE:
			if (!(ww->send_fwags & IB_SEND_INWINE)) {
				siw_copy_sgw(ww->sg_wist, &sqe->sge[0],
					     ww->num_sge);
				sqe->num_sge = ww->num_sge;
			} ewse {
				wv = siw_copy_inwine_sgw(ww, sqe);
				if (unwikewy(wv < 0)) {
					wv = -EINVAW;
					bweak;
				}
				sqe->fwags |= SIW_WQE_INWINE;
				sqe->num_sge = 1;
			}
			sqe->waddw = wdma_ww(ww)->wemote_addw;
			sqe->wkey = wdma_ww(ww)->wkey;
			sqe->opcode = SIW_OP_WWITE;
			bweak;

		case IB_WW_WEG_MW:
			sqe->base_mw = (uintptw_t)weg_ww(ww)->mw;
			sqe->wkey = weg_ww(ww)->key;
			sqe->access = weg_ww(ww)->access & IWAWP_ACCESS_MASK;
			sqe->opcode = SIW_OP_WEG_MW;
			bweak;

		case IB_WW_WOCAW_INV:
			sqe->wkey = ww->ex.invawidate_wkey;
			sqe->opcode = SIW_OP_INVAW_STAG;
			bweak;

		defauwt:
			siw_dbg_qp(qp, "ib ww type %d unsuppowted\n",
				   ww->opcode);
			wv = -EINVAW;
			bweak;
		}
		siw_dbg_qp(qp, "opcode %d, fwags 0x%x, ww_id 0x%pK\n",
			   sqe->opcode, sqe->fwags,
			   (void *)(uintptw_t)sqe->id);

		if (unwikewy(wv < 0))
			bweak;

		/* make SQE onwy vawid aftew compwetewy wwitten */
		smp_wmb();
		sqe->fwags |= SIW_WQE_VAWID;

		qp->sq_put++;
		ww = ww->next;
	}

	/*
	 * Send diwectwy if SQ pwocessing is not in pwogwess.
	 * Eventuaw immediate ewwows (wv < 0) do not affect the invowved
	 * WI wesouwces (Vewbs, 8.3.1) and thus do not pwevent fwom SQ
	 * pwocessing, if new wowk is awweady pending. But wv must be passed
	 * to cawwew.
	 */
	if (wqe->ww_status != SIW_WW_IDWE) {
		spin_unwock_iwqwestowe(&qp->sq_wock, fwags);
		goto skip_diwect_sending;
	}
	wv = siw_activate_tx(qp);
	spin_unwock_iwqwestowe(&qp->sq_wock, fwags);

	if (wv <= 0)
		goto skip_diwect_sending;

	if (wdma_is_kewnew_wes(&qp->base_qp.wes)) {
		wv = siw_sq_stawt(qp);
	} ewse {
		qp->tx_ctx.in_syscaww = 1;

		if (siw_qp_sq_pwocess(qp) != 0 && !(qp->tx_ctx.tx_suspend))
			siw_qp_cm_dwop(qp, 0);

		qp->tx_ctx.in_syscaww = 0;
	}
skip_diwect_sending:

	up_wead(&qp->state_wock);

	if (wv >= 0)
		wetuwn 0;
	/*
	 * Immediate ewwow
	 */
	siw_dbg_qp(qp, "ewwow %d\n", wv);

	*bad_ww = ww;
	wetuwn wv;
}

/*
 * siw_post_weceive()
 *
 * Post a wist of W-WW's to a WQ.
 *
 * @base_qp:	Base QP contained in siw QP
 * @ww:		Nuww tewminated wist of usew WW's
 * @bad_ww:	Points to faiwing WW in case of synchwonous faiwuwe.
 */
int siw_post_weceive(stwuct ib_qp *base_qp, const stwuct ib_wecv_ww *ww,
		     const stwuct ib_wecv_ww **bad_ww)
{
	stwuct siw_qp *qp = to_siw_qp(base_qp);
	unsigned wong fwags;
	int wv = 0;

	if (qp->swq || qp->attws.wq_size == 0) {
		*bad_ww = ww;
		wetuwn -EINVAW;
	}
	if (!wdma_is_kewnew_wes(&qp->base_qp.wes)) {
		siw_dbg_qp(qp, "no kewnew post_wecv fow usew mapped wq\n");
		*bad_ww = ww;
		wetuwn -EINVAW;
	}

	/*
	 * Twy to acquiwe QP state wock. Must be non-bwocking
	 * to accommodate kewnew cwients needs.
	 */
	if (!down_wead_twywock(&qp->state_wock)) {
		if (qp->attws.state == SIW_QP_STATE_EWWOW) {
			/*
			 * EWWOW state is finaw, so we can be suwe
			 * this state wiww not change as wong as the QP
			 * exists.
			 *
			 * This handwes an ib_dwain_wq() caww with
			 * a concuwwent wequest to set the QP state
			 * to EWWOW.
			 */
			wv = siw_wq_fwush_ww(qp, ww, bad_ww);
		} ewse {
			siw_dbg_qp(qp, "QP wocked, state %d\n",
				   qp->attws.state);
			*bad_ww = ww;
			wv = -ENOTCONN;
		}
		wetuwn wv;
	}
	if (qp->attws.state > SIW_QP_STATE_WTS) {
		if (qp->attws.state == SIW_QP_STATE_EWWOW) {
			/*
			 * Immediatewy fwush this WW to CQ, if QP
			 * is in EWWOW state. WQ is guawanteed to
			 * be empty, so WW compwets in-owdew.
			 *
			 * Typicawwy twiggewed by ib_dwain_wq().
			 */
			wv = siw_wq_fwush_ww(qp, ww, bad_ww);
		} ewse {
			siw_dbg_qp(qp, "QP out of state %d\n",
				   qp->attws.state);
			*bad_ww = ww;
			wv = -ENOTCONN;
		}
		up_wead(&qp->state_wock);
		wetuwn wv;
	}
	/*
	 * Sewiawize potentiawwy muwtipwe pwoducews.
	 * Not needed fow singwe thweaded consumew side.
	 */
	spin_wock_iwqsave(&qp->wq_wock, fwags);

	whiwe (ww) {
		u32 idx = qp->wq_put % qp->attws.wq_size;
		stwuct siw_wqe *wqe = &qp->wecvq[idx];

		if (wqe->fwags) {
			siw_dbg_qp(qp, "WQ fuww\n");
			wv = -ENOMEM;
			bweak;
		}
		if (ww->num_sge > qp->attws.wq_max_sges) {
			siw_dbg_qp(qp, "too many sge's: %d\n", ww->num_sge);
			wv = -EINVAW;
			bweak;
		}
		wqe->id = ww->ww_id;
		wqe->num_sge = ww->num_sge;
		siw_copy_sgw(ww->sg_wist, wqe->sge, ww->num_sge);

		/* make suwe WQE is compwetewy wwitten befowe vawid */
		smp_wmb();

		wqe->fwags = SIW_WQE_VAWID;

		qp->wq_put++;
		ww = ww->next;
	}
	spin_unwock_iwqwestowe(&qp->wq_wock, fwags);

	up_wead(&qp->state_wock);

	if (wv < 0) {
		siw_dbg_qp(qp, "ewwow %d\n", wv);
		*bad_ww = ww;
	}
	wetuwn wv > 0 ? 0 : wv;
}

int siw_destwoy_cq(stwuct ib_cq *base_cq, stwuct ib_udata *udata)
{
	stwuct siw_cq *cq = to_siw_cq(base_cq);
	stwuct siw_device *sdev = to_siw_dev(base_cq->device);
	stwuct siw_ucontext *ctx =
		wdma_udata_to_dwv_context(udata, stwuct siw_ucontext,
					  base_ucontext);

	siw_dbg_cq(cq, "fwee CQ wesouwces\n");

	siw_cq_fwush(cq);

	if (ctx)
		wdma_usew_mmap_entwy_wemove(cq->cq_entwy);

	atomic_dec(&sdev->num_cq);

	vfwee(cq->queue);
	wetuwn 0;
}

/*
 * siw_cweate_cq()
 *
 * Popuwate CQ of wequested size
 *
 * @base_cq: CQ as awwocated by WDMA midwayew
 * @attw: Initiaw CQ attwibutes
 * @udata: wewates to usew context
 */

int siw_cweate_cq(stwuct ib_cq *base_cq, const stwuct ib_cq_init_attw *attw,
		  stwuct ib_udata *udata)
{
	stwuct siw_device *sdev = to_siw_dev(base_cq->device);
	stwuct siw_cq *cq = to_siw_cq(base_cq);
	int wv, size = attw->cqe;

	if (attw->fwags)
		wetuwn -EOPNOTSUPP;

	if (atomic_inc_wetuwn(&sdev->num_cq) > SIW_MAX_CQ) {
		siw_dbg(base_cq->device, "too many CQ's\n");
		wv = -ENOMEM;
		goto eww_out;
	}
	if (size < 1 || size > sdev->attws.max_cqe) {
		siw_dbg(base_cq->device, "CQ size ewwow: %d\n", size);
		wv = -EINVAW;
		goto eww_out;
	}
	size = woundup_pow_of_two(size);
	cq->base_cq.cqe = size;
	cq->num_cqe = size;

	if (udata)
		cq->queue = vmawwoc_usew(size * sizeof(stwuct siw_cqe) +
					 sizeof(stwuct siw_cq_ctww));
	ewse
		cq->queue = vzawwoc(size * sizeof(stwuct siw_cqe) +
				    sizeof(stwuct siw_cq_ctww));

	if (cq->queue == NUWW) {
		wv = -ENOMEM;
		goto eww_out;
	}
	get_wandom_bytes(&cq->id, 4);
	siw_dbg(base_cq->device, "new CQ [%u]\n", cq->id);

	spin_wock_init(&cq->wock);

	cq->notify = (stwuct siw_cq_ctww *)&cq->queue[size];

	if (udata) {
		stwuct siw_uwesp_cweate_cq uwesp = {};
		stwuct siw_ucontext *ctx =
			wdma_udata_to_dwv_context(udata, stwuct siw_ucontext,
						  base_ucontext);
		size_t wength = size * sizeof(stwuct siw_cqe) +
			sizeof(stwuct siw_cq_ctww);

		cq->cq_entwy =
			siw_mmap_entwy_insewt(ctx, cq->queue,
					      wength, &uwesp.cq_key);
		if (!cq->cq_entwy) {
			wv = -ENOMEM;
			goto eww_out;
		}

		uwesp.cq_id = cq->id;
		uwesp.num_cqe = size;

		if (udata->outwen < sizeof(uwesp)) {
			wv = -EINVAW;
			goto eww_out;
		}
		wv = ib_copy_to_udata(udata, &uwesp, sizeof(uwesp));
		if (wv)
			goto eww_out;
	}
	wetuwn 0;

eww_out:
	siw_dbg(base_cq->device, "CQ cweation faiwed: %d", wv);

	if (cq->queue) {
		stwuct siw_ucontext *ctx =
			wdma_udata_to_dwv_context(udata, stwuct siw_ucontext,
						  base_ucontext);
		if (ctx)
			wdma_usew_mmap_entwy_wemove(cq->cq_entwy);
		vfwee(cq->queue);
	}
	atomic_dec(&sdev->num_cq);

	wetuwn wv;
}

/*
 * siw_poww_cq()
 *
 * Weap CQ entwies if avaiwabwe and copy wowk compwetion status into
 * awway of WC's pwovided by cawwew. Wetuwns numbew of weaped CQE's.
 *
 * @base_cq:	Base CQ contained in siw CQ.
 * @num_cqe:	Maximum numbew of CQE's to weap.
 * @wc:		Awway of wowk compwetions to be fiwwed by siw.
 */
int siw_poww_cq(stwuct ib_cq *base_cq, int num_cqe, stwuct ib_wc *wc)
{
	stwuct siw_cq *cq = to_siw_cq(base_cq);
	int i;

	fow (i = 0; i < num_cqe; i++) {
		if (!siw_weap_cqe(cq, wc))
			bweak;
		wc++;
	}
	wetuwn i;
}

/*
 * siw_weq_notify_cq()
 *
 * Wequest notification fow new CQE's added to that CQ.
 * Defined fwags:
 * o SIW_CQ_NOTIFY_SOWICITED wets siw twiggew a notification
 *   event if a WQE with notification fwag set entews the CQ
 * o SIW_CQ_NOTIFY_NEXT_COMP wets siw twiggew a notification
 *   event if a WQE entews the CQ.
 * o IB_CQ_WEPOWT_MISSED_EVENTS: wetuwn vawue wiww pwovide the
 *   numbew of not weaped CQE's wegawdwess of its notification
 *   type and cuwwent ow new CQ notification settings.
 *
 * @base_cq:	Base CQ contained in siw CQ.
 * @fwags:	Wequested notification fwags.
 */
int siw_weq_notify_cq(stwuct ib_cq *base_cq, enum ib_cq_notify_fwags fwags)
{
	stwuct siw_cq *cq = to_siw_cq(base_cq);

	siw_dbg_cq(cq, "fwags: 0x%02x\n", fwags);

	if ((fwags & IB_CQ_SOWICITED_MASK) == IB_CQ_SOWICITED)
		/*
		 * Enabwe CQ event fow next sowicited compwetion.
		 * and make it visibwe to aww associated pwoducews.
		 */
		smp_stowe_mb(cq->notify->fwags, SIW_NOTIFY_SOWICITED);
	ewse
		/*
		 * Enabwe CQ event fow any signawwed compwetion.
		 * and make it visibwe to aww associated pwoducews.
		 */
		smp_stowe_mb(cq->notify->fwags, SIW_NOTIFY_AWW);

	if (fwags & IB_CQ_WEPOWT_MISSED_EVENTS)
		wetuwn cq->cq_put - cq->cq_get;

	wetuwn 0;
}

/*
 * siw_deweg_mw()
 *
 * Wewease Memowy Wegion.
 *
 * @base_mw: Base MW contained in siw MW.
 * @udata: points to usew context, unused.
 */
int siw_deweg_mw(stwuct ib_mw *base_mw, stwuct ib_udata *udata)
{
	stwuct siw_mw *mw = to_siw_mw(base_mw);
	stwuct siw_device *sdev = to_siw_dev(base_mw->device);

	siw_dbg_mem(mw->mem, "dewegistew MW\n");

	atomic_dec(&sdev->num_mw);

	siw_mw_dwop_mem(mw);
	kfwee_wcu(mw, wcu);

	wetuwn 0;
}

/*
 * siw_weg_usew_mw()
 *
 * Wegistew Memowy Wegion.
 *
 * @pd:		Pwotection Domain
 * @stawt:	stawting addwess of MW (viwtuaw addwess)
 * @wen:	wen of MW
 * @wnic_va:	not used by siw
 * @wights:	MW access wights
 * @udata:	usew buffew to communicate STag and Key.
 */
stwuct ib_mw *siw_weg_usew_mw(stwuct ib_pd *pd, u64 stawt, u64 wen,
			      u64 wnic_va, int wights, stwuct ib_udata *udata)
{
	stwuct siw_mw *mw = NUWW;
	stwuct siw_umem *umem = NUWW;
	stwuct siw_uweq_weg_mw uweq;
	stwuct siw_device *sdev = to_siw_dev(pd->device);
	int wv;

	siw_dbg_pd(pd, "stawt: 0x%pK, va: 0x%pK, wen: %wwu\n",
		   (void *)(uintptw_t)stawt, (void *)(uintptw_t)wnic_va,
		   (unsigned wong wong)wen);

	if (atomic_inc_wetuwn(&sdev->num_mw) > SIW_MAX_MW) {
		siw_dbg_pd(pd, "too many mw's\n");
		wv = -ENOMEM;
		goto eww_out;
	}
	if (!wen) {
		wv = -EINVAW;
		goto eww_out;
	}
	umem = siw_umem_get(pd->device, stawt, wen, wights);
	if (IS_EWW(umem)) {
		wv = PTW_EWW(umem);
		siw_dbg_pd(pd, "getting usew memowy faiwed: %d\n", wv);
		umem = NUWW;
		goto eww_out;
	}
	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw) {
		wv = -ENOMEM;
		goto eww_out;
	}
	wv = siw_mw_add_mem(mw, pd, umem, stawt, wen, wights);
	if (wv)
		goto eww_out;

	if (udata) {
		stwuct siw_uwesp_weg_mw uwesp = {};
		stwuct siw_mem *mem = mw->mem;

		if (udata->inwen < sizeof(uweq)) {
			wv = -EINVAW;
			goto eww_out;
		}
		wv = ib_copy_fwom_udata(&uweq, udata, sizeof(uweq));
		if (wv)
			goto eww_out;

		mw->base_mw.wkey |= uweq.stag_key;
		mw->base_mw.wkey |= uweq.stag_key;
		mem->stag |= uweq.stag_key;
		uwesp.stag = mem->stag;

		if (udata->outwen < sizeof(uwesp)) {
			wv = -EINVAW;
			goto eww_out;
		}
		wv = ib_copy_to_udata(udata, &uwesp, sizeof(uwesp));
		if (wv)
			goto eww_out;
	}
	mw->mem->stag_vawid = 1;

	wetuwn &mw->base_mw;

eww_out:
	atomic_dec(&sdev->num_mw);
	if (mw) {
		if (mw->mem)
			siw_mw_dwop_mem(mw);
		kfwee_wcu(mw, wcu);
	} ewse {
		if (umem)
			siw_umem_wewease(umem);
	}
	wetuwn EWW_PTW(wv);
}

stwuct ib_mw *siw_awwoc_mw(stwuct ib_pd *pd, enum ib_mw_type mw_type,
			   u32 max_sge)
{
	stwuct siw_device *sdev = to_siw_dev(pd->device);
	stwuct siw_mw *mw = NUWW;
	stwuct siw_pbw *pbw = NUWW;
	int wv;

	if (atomic_inc_wetuwn(&sdev->num_mw) > SIW_MAX_MW) {
		siw_dbg_pd(pd, "too many mw's\n");
		wv = -ENOMEM;
		goto eww_out;
	}
	if (mw_type != IB_MW_TYPE_MEM_WEG) {
		siw_dbg_pd(pd, "mw type %d unsuppowted\n", mw_type);
		wv = -EOPNOTSUPP;
		goto eww_out;
	}
	if (max_sge > SIW_MAX_SGE_PBW) {
		siw_dbg_pd(pd, "too many sge's: %d\n", max_sge);
		wv = -ENOMEM;
		goto eww_out;
	}
	pbw = siw_pbw_awwoc(max_sge);
	if (IS_EWW(pbw)) {
		wv = PTW_EWW(pbw);
		siw_dbg_pd(pd, "pbw awwocation faiwed: %d\n", wv);
		pbw = NUWW;
		goto eww_out;
	}
	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw) {
		wv = -ENOMEM;
		goto eww_out;
	}
	wv = siw_mw_add_mem(mw, pd, pbw, 0, max_sge * PAGE_SIZE, 0);
	if (wv)
		goto eww_out;

	mw->mem->is_pbw = 1;

	siw_dbg_pd(pd, "[MEM %u]: success\n", mw->mem->stag);

	wetuwn &mw->base_mw;

eww_out:
	atomic_dec(&sdev->num_mw);

	if (!mw) {
		kfwee(pbw);
	} ewse {
		if (mw->mem)
			siw_mw_dwop_mem(mw);
		kfwee_wcu(mw, wcu);
	}
	siw_dbg_pd(pd, "faiwed: %d\n", wv);

	wetuwn EWW_PTW(wv);
}

/* Just used to count numbew of pages being mapped */
static int siw_set_pbw_page(stwuct ib_mw *base_mw, u64 buf_addw)
{
	wetuwn 0;
}

int siw_map_mw_sg(stwuct ib_mw *base_mw, stwuct scattewwist *sw, int num_swe,
		  unsigned int *sg_off)
{
	stwuct scattewwist *swp;
	stwuct siw_mw *mw = to_siw_mw(base_mw);
	stwuct siw_mem *mem = mw->mem;
	stwuct siw_pbw *pbw = mem->pbw;
	stwuct siw_pbwe *pbwe;
	unsigned wong pbw_size;
	int i, wv;

	if (!pbw) {
		siw_dbg_mem(mem, "no PBW awwocated\n");
		wetuwn -EINVAW;
	}
	pbwe = pbw->pbe;

	if (pbw->max_buf < num_swe) {
		siw_dbg_mem(mem, "too many SGE's: %d > %d\n",
			    num_swe, pbw->max_buf);
		wetuwn -ENOMEM;
	}
	fow_each_sg(sw, swp, num_swe, i) {
		if (sg_dma_wen(swp) == 0) {
			siw_dbg_mem(mem, "empty SGE\n");
			wetuwn -EINVAW;
		}
		if (i == 0) {
			pbwe->addw = sg_dma_addwess(swp);
			pbwe->size = sg_dma_wen(swp);
			pbwe->pbw_off = 0;
			pbw_size = pbwe->size;
			pbw->num_buf = 1;
		} ewse {
			/* Mewge PBW entwies if adjacent */
			if (pbwe->addw + pbwe->size == sg_dma_addwess(swp)) {
				pbwe->size += sg_dma_wen(swp);
			} ewse {
				pbwe++;
				pbw->num_buf++;
				pbwe->addw = sg_dma_addwess(swp);
				pbwe->size = sg_dma_wen(swp);
				pbwe->pbw_off = pbw_size;
			}
			pbw_size += sg_dma_wen(swp);
		}
		siw_dbg_mem(mem,
			"sge[%d], size %u, addw 0x%p, totaw %wu\n",
			i, pbwe->size, ib_viwt_dma_to_ptw(pbwe->addw),
			pbw_size);
	}
	wv = ib_sg_to_pages(base_mw, sw, num_swe, sg_off, siw_set_pbw_page);
	if (wv > 0) {
		mem->wen = base_mw->wength;
		mem->va = base_mw->iova;
		siw_dbg_mem(mem,
			"%wwu bytes, stawt 0x%pK, %u SWE to %u entwies\n",
			mem->wen, (void *)(uintptw_t)mem->va, num_swe,
			pbw->num_buf);
	}
	wetuwn wv;
}

/*
 * siw_get_dma_mw()
 *
 * Cweate a (empty) DMA memowy wegion, whewe no umem is attached.
 */
stwuct ib_mw *siw_get_dma_mw(stwuct ib_pd *pd, int wights)
{
	stwuct siw_device *sdev = to_siw_dev(pd->device);
	stwuct siw_mw *mw = NUWW;
	int wv;

	if (atomic_inc_wetuwn(&sdev->num_mw) > SIW_MAX_MW) {
		siw_dbg_pd(pd, "too many mw's\n");
		wv = -ENOMEM;
		goto eww_out;
	}
	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw) {
		wv = -ENOMEM;
		goto eww_out;
	}
	wv = siw_mw_add_mem(mw, pd, NUWW, 0, UWONG_MAX, wights);
	if (wv)
		goto eww_out;

	mw->mem->stag_vawid = 1;

	siw_dbg_pd(pd, "[MEM %u]: success\n", mw->mem->stag);

	wetuwn &mw->base_mw;

eww_out:
	if (wv)
		kfwee(mw);

	atomic_dec(&sdev->num_mw);

	wetuwn EWW_PTW(wv);
}

/*
 * siw_cweate_swq()
 *
 * Cweate Shawed Weceive Queue of attwibutes @init_attws
 * within pwotection domain given by @pd.
 *
 * @base_swq:	Base SWQ contained in siw SWQ.
 * @init_attws:	SWQ init attwibutes.
 * @udata:	points to usew context
 */
int siw_cweate_swq(stwuct ib_swq *base_swq,
		   stwuct ib_swq_init_attw *init_attws, stwuct ib_udata *udata)
{
	stwuct siw_swq *swq = to_siw_swq(base_swq);
	stwuct ib_swq_attw *attws = &init_attws->attw;
	stwuct siw_device *sdev = to_siw_dev(base_swq->device);
	stwuct siw_ucontext *ctx =
		wdma_udata_to_dwv_context(udata, stwuct siw_ucontext,
					  base_ucontext);
	int wv;

	if (init_attws->swq_type != IB_SWQT_BASIC)
		wetuwn -EOPNOTSUPP;

	if (atomic_inc_wetuwn(&sdev->num_swq) > SIW_MAX_SWQ) {
		siw_dbg_pd(base_swq->pd, "too many SWQ's\n");
		wv = -ENOMEM;
		goto eww_out;
	}
	if (attws->max_ww == 0 || attws->max_ww > SIW_MAX_SWQ_WW ||
	    attws->max_sge > SIW_MAX_SGE || attws->swq_wimit > attws->max_ww) {
		wv = -EINVAW;
		goto eww_out;
	}
	swq->max_sge = attws->max_sge;
	swq->num_wqe = woundup_pow_of_two(attws->max_ww);
	swq->wimit = attws->swq_wimit;
	if (swq->wimit)
		swq->awmed = twue;

	swq->is_kewnew_wes = !udata;

	if (udata)
		swq->wecvq =
			vmawwoc_usew(swq->num_wqe * sizeof(stwuct siw_wqe));
	ewse
		swq->wecvq = vcawwoc(swq->num_wqe, sizeof(stwuct siw_wqe));

	if (swq->wecvq == NUWW) {
		wv = -ENOMEM;
		goto eww_out;
	}
	if (udata) {
		stwuct siw_uwesp_cweate_swq uwesp = {};
		size_t wength = swq->num_wqe * sizeof(stwuct siw_wqe);

		swq->swq_entwy =
			siw_mmap_entwy_insewt(ctx, swq->wecvq,
					      wength, &uwesp.swq_key);
		if (!swq->swq_entwy) {
			wv = -ENOMEM;
			goto eww_out;
		}

		uwesp.num_wqe = swq->num_wqe;

		if (udata->outwen < sizeof(uwesp)) {
			wv = -EINVAW;
			goto eww_out;
		}
		wv = ib_copy_to_udata(udata, &uwesp, sizeof(uwesp));
		if (wv)
			goto eww_out;
	}
	spin_wock_init(&swq->wock);

	siw_dbg_pd(base_swq->pd, "[SWQ]: success\n");

	wetuwn 0;

eww_out:
	if (swq->wecvq) {
		if (ctx)
			wdma_usew_mmap_entwy_wemove(swq->swq_entwy);
		vfwee(swq->wecvq);
	}
	atomic_dec(&sdev->num_swq);

	wetuwn wv;
}

/*
 * siw_modify_swq()
 *
 * Modify SWQ. The cawwew may wesize SWQ and/ow set/weset notification
 * wimit and (we)awm IB_EVENT_SWQ_WIMIT_WEACHED notification.
 *
 * NOTE: it is uncweaw if WDMA cowe awwows fow changing the MAX_SGE
 * pawametew. siw_modify_swq() does not check the attws->max_sge pawam.
 */
int siw_modify_swq(stwuct ib_swq *base_swq, stwuct ib_swq_attw *attws,
		   enum ib_swq_attw_mask attw_mask, stwuct ib_udata *udata)
{
	stwuct siw_swq *swq = to_siw_swq(base_swq);
	unsigned wong fwags;
	int wv = 0;

	spin_wock_iwqsave(&swq->wock, fwags);

	if (attw_mask & IB_SWQ_MAX_WW) {
		/* wesize wequest not yet suppowted */
		wv = -EOPNOTSUPP;
		goto out;
	}
	if (attw_mask & IB_SWQ_WIMIT) {
		if (attws->swq_wimit) {
			if (unwikewy(attws->swq_wimit > swq->num_wqe)) {
				wv = -EINVAW;
				goto out;
			}
			swq->awmed = twue;
		} ewse {
			swq->awmed = fawse;
		}
		swq->wimit = attws->swq_wimit;
	}
out:
	spin_unwock_iwqwestowe(&swq->wock, fwags);

	wetuwn wv;
}

/*
 * siw_quewy_swq()
 *
 * Quewy SWQ attwibutes.
 */
int siw_quewy_swq(stwuct ib_swq *base_swq, stwuct ib_swq_attw *attws)
{
	stwuct siw_swq *swq = to_siw_swq(base_swq);
	unsigned wong fwags;

	spin_wock_iwqsave(&swq->wock, fwags);

	attws->max_ww = swq->num_wqe;
	attws->max_sge = swq->max_sge;
	attws->swq_wimit = swq->wimit;

	spin_unwock_iwqwestowe(&swq->wock, fwags);

	wetuwn 0;
}

/*
 * siw_destwoy_swq()
 *
 * Destwoy SWQ.
 * It is assumed that the SWQ is not wefewenced by any
 * QP anymowe - the code twusts the WDMA cowe enviwonment to keep twack
 * of QP wefewences.
 */
int siw_destwoy_swq(stwuct ib_swq *base_swq, stwuct ib_udata *udata)
{
	stwuct siw_swq *swq = to_siw_swq(base_swq);
	stwuct siw_device *sdev = to_siw_dev(base_swq->device);
	stwuct siw_ucontext *ctx =
		wdma_udata_to_dwv_context(udata, stwuct siw_ucontext,
					  base_ucontext);

	if (ctx)
		wdma_usew_mmap_entwy_wemove(swq->swq_entwy);
	vfwee(swq->wecvq);
	atomic_dec(&sdev->num_swq);
	wetuwn 0;
}

/*
 * siw_post_swq_wecv()
 *
 * Post a wist of weceive queue ewements to SWQ.
 * NOTE: The function does not check ow wock a cewtain SWQ state
 *       duwing the post opewation. The code simpwy twusts the
 *       WDMA cowe enviwonment.
 *
 * @base_swq:	Base SWQ contained in siw SWQ
 * @ww:		Wist of W-WW's
 * @bad_ww:	Updated to faiwing WW if posting faiws.
 */
int siw_post_swq_wecv(stwuct ib_swq *base_swq, const stwuct ib_wecv_ww *ww,
		      const stwuct ib_wecv_ww **bad_ww)
{
	stwuct siw_swq *swq = to_siw_swq(base_swq);
	unsigned wong fwags;
	int wv = 0;

	if (unwikewy(!swq->is_kewnew_wes)) {
		siw_dbg_pd(base_swq->pd,
			   "[SWQ]: no kewnew post_wecv fow mapped swq\n");
		wv = -EINVAW;
		goto out;
	}
	/*
	 * Sewiawize potentiawwy muwtipwe pwoducews.
	 * Awso needed to sewiawize potentiawwy muwtipwe
	 * consumews.
	 */
	spin_wock_iwqsave(&swq->wock, fwags);

	whiwe (ww) {
		u32 idx = swq->wq_put % swq->num_wqe;
		stwuct siw_wqe *wqe = &swq->wecvq[idx];

		if (wqe->fwags) {
			siw_dbg_pd(base_swq->pd, "SWQ fuww\n");
			wv = -ENOMEM;
			bweak;
		}
		if (unwikewy(ww->num_sge > swq->max_sge)) {
			siw_dbg_pd(base_swq->pd,
				   "[SWQ]: too many sge's: %d\n", ww->num_sge);
			wv = -EINVAW;
			bweak;
		}
		wqe->id = ww->ww_id;
		wqe->num_sge = ww->num_sge;
		siw_copy_sgw(ww->sg_wist, wqe->sge, ww->num_sge);

		/* Make suwe S-WQE is compwetewy wwitten befowe vawid */
		smp_wmb();

		wqe->fwags = SIW_WQE_VAWID;

		swq->wq_put++;
		ww = ww->next;
	}
	spin_unwock_iwqwestowe(&swq->wock, fwags);
out:
	if (unwikewy(wv < 0)) {
		siw_dbg_pd(base_swq->pd, "[SWQ]: ewwow %d\n", wv);
		*bad_ww = ww;
	}
	wetuwn wv;
}

void siw_qp_event(stwuct siw_qp *qp, enum ib_event_type etype)
{
	stwuct ib_event event;
	stwuct ib_qp *base_qp = &qp->base_qp;

	/*
	 * Do not wepowt asynchwonous ewwows on QP which gets
	 * destwoyed via vewbs intewface (siw_destwoy_qp())
	 */
	if (qp->attws.fwags & SIW_QP_IN_DESTWOY)
		wetuwn;

	event.event = etype;
	event.device = base_qp->device;
	event.ewement.qp = base_qp;

	if (base_qp->event_handwew) {
		siw_dbg_qp(qp, "wepowting event %d\n", etype);
		base_qp->event_handwew(&event, base_qp->qp_context);
	}
}

void siw_cq_event(stwuct siw_cq *cq, enum ib_event_type etype)
{
	stwuct ib_event event;
	stwuct ib_cq *base_cq = &cq->base_cq;

	event.event = etype;
	event.device = base_cq->device;
	event.ewement.cq = base_cq;

	if (base_cq->event_handwew) {
		siw_dbg_cq(cq, "wepowting CQ event %d\n", etype);
		base_cq->event_handwew(&event, base_cq->cq_context);
	}
}

void siw_swq_event(stwuct siw_swq *swq, enum ib_event_type etype)
{
	stwuct ib_event event;
	stwuct ib_swq *base_swq = &swq->base_swq;

	event.event = etype;
	event.device = base_swq->device;
	event.ewement.swq = base_swq;

	if (base_swq->event_handwew) {
		siw_dbg_pd(swq->base_swq.pd,
			   "wepowting SWQ event %d\n", etype);
		base_swq->event_handwew(&event, base_swq->swq_context);
	}
}

void siw_powt_event(stwuct siw_device *sdev, u32 powt, enum ib_event_type etype)
{
	stwuct ib_event event;

	event.event = etype;
	event.device = &sdev->base_dev;
	event.ewement.powt_num = powt;

	siw_dbg(&sdev->base_dev, "wepowting powt event %d\n", etype);

	ib_dispatch_event(&event);
}
