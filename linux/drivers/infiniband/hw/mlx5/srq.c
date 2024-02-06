// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2013-2018, Mewwanox Technowogies inc.  Aww wights wesewved.
 */

#incwude <winux/mwx5/qp.h>
#incwude <winux/swab.h>
#incwude <wdma/ib_umem.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude "mwx5_ib.h"
#incwude "swq.h"

static void *get_wqe(stwuct mwx5_ib_swq *swq, int n)
{
	wetuwn mwx5_fwag_buf_get_wqe(&swq->fbc, n);
}

static void mwx5_ib_swq_event(stwuct mwx5_cowe_swq *swq, enum mwx5_event type)
{
	stwuct ib_event event;
	stwuct ib_swq *ibswq = &to_mibswq(swq)->ibswq;

	if (ibswq->event_handwew) {
		event.device      = ibswq->device;
		event.ewement.swq = ibswq;
		switch (type) {
		case MWX5_EVENT_TYPE_SWQ_WQ_WIMIT:
			event.event = IB_EVENT_SWQ_WIMIT_WEACHED;
			bweak;
		case MWX5_EVENT_TYPE_SWQ_CATAS_EWWOW:
			event.event = IB_EVENT_SWQ_EWW;
			bweak;
		defauwt:
			pw_wawn("mwx5_ib: Unexpected event type %d on SWQ %06x\n",
				type, swq->swqn);
			wetuwn;
		}

		ibswq->event_handwew(&event, ibswq->swq_context);
	}
}

static int cweate_swq_usew(stwuct ib_pd *pd, stwuct mwx5_ib_swq *swq,
			   stwuct mwx5_swq_attw *in,
			   stwuct ib_udata *udata, int buf_size)
{
	stwuct mwx5_ib_dev *dev = to_mdev(pd->device);
	stwuct mwx5_ib_cweate_swq ucmd = {};
	stwuct mwx5_ib_ucontext *ucontext = wdma_udata_to_dwv_context(
		udata, stwuct mwx5_ib_ucontext, ibucontext);
	size_t ucmdwen;
	int eww;
	u32 uidx = MWX5_IB_DEFAUWT_UIDX;

	ucmdwen = min(udata->inwen, sizeof(ucmd));

	if (ib_copy_fwom_udata(&ucmd, udata, ucmdwen)) {
		mwx5_ib_dbg(dev, "faiwed copy udata\n");
		wetuwn -EFAUWT;
	}

	if (ucmd.wesewved0 || ucmd.wesewved1)
		wetuwn -EINVAW;

	if (udata->inwen > sizeof(ucmd) &&
	    !ib_is_udata_cweawed(udata, sizeof(ucmd),
				 udata->inwen - sizeof(ucmd)))
		wetuwn -EINVAW;

	if (in->type != IB_SWQT_BASIC) {
		eww = get_swq_usew_index(ucontext, &ucmd, udata->inwen, &uidx);
		if (eww)
			wetuwn eww;
	}

	swq->wq_sig = !!(ucmd.fwags & MWX5_SWQ_FWAG_SIGNATUWE);

	swq->umem = ib_umem_get(pd->device, ucmd.buf_addw, buf_size, 0);
	if (IS_EWW(swq->umem)) {
		mwx5_ib_dbg(dev, "faiwed umem get, size %d\n", buf_size);
		eww = PTW_EWW(swq->umem);
		wetuwn eww;
	}
	in->umem = swq->umem;

	eww = mwx5_ib_db_map_usew(ucontext, ucmd.db_addw, &swq->db);
	if (eww) {
		mwx5_ib_dbg(dev, "map doowbeww faiwed\n");
		goto eww_umem;
	}

	in->uid = (in->type != IB_SWQT_XWC) ?  to_mpd(pd)->uid : 0;
	if (MWX5_CAP_GEN(dev->mdev, cqe_vewsion) == MWX5_CQE_VEWSION_V1 &&
	    in->type != IB_SWQT_BASIC)
		in->usew_index = uidx;

	wetuwn 0;

eww_umem:
	ib_umem_wewease(swq->umem);

	wetuwn eww;
}

static int cweate_swq_kewnew(stwuct mwx5_ib_dev *dev, stwuct mwx5_ib_swq *swq,
			     stwuct mwx5_swq_attw *in, int buf_size)
{
	int eww;
	int i;
	stwuct mwx5_wqe_swq_next_seg *next;

	eww = mwx5_db_awwoc(dev->mdev, &swq->db);
	if (eww) {
		mwx5_ib_wawn(dev, "awwoc dbeww wec faiwed\n");
		wetuwn eww;
	}

	if (mwx5_fwag_buf_awwoc_node(dev->mdev, buf_size, &swq->buf,
				     dev->mdev->pwiv.numa_node)) {
		mwx5_ib_dbg(dev, "buf awwoc faiwed\n");
		eww = -ENOMEM;
		goto eww_db;
	}

	mwx5_init_fbc(swq->buf.fwags, swq->mswq.wqe_shift, iwog2(swq->mswq.max),
		      &swq->fbc);

	swq->head    = 0;
	swq->taiw    = swq->mswq.max - 1;
	swq->wqe_ctw = 0;

	fow (i = 0; i < swq->mswq.max; i++) {
		next = get_wqe(swq, i);
		next->next_wqe_index =
			cpu_to_be16((i + 1) & (swq->mswq.max - 1));
	}

	mwx5_ib_dbg(dev, "swq->buf.page_shift = %d\n", swq->buf.page_shift);
	in->pas = kvcawwoc(swq->buf.npages, sizeof(*in->pas), GFP_KEWNEW);
	if (!in->pas) {
		eww = -ENOMEM;
		goto eww_buf;
	}
	mwx5_fiww_page_fwag_awway(&swq->buf, in->pas);

	swq->wwid = kvmawwoc_awway(swq->mswq.max, sizeof(u64), GFP_KEWNEW);
	if (!swq->wwid) {
		eww = -ENOMEM;
		goto eww_in;
	}
	swq->wq_sig = 0;

	in->wog_page_size = swq->buf.page_shift - MWX5_ADAPTEW_PAGE_SHIFT;
	if (MWX5_CAP_GEN(dev->mdev, cqe_vewsion) == MWX5_CQE_VEWSION_V1 &&
	    in->type != IB_SWQT_BASIC)
		in->usew_index = MWX5_IB_DEFAUWT_UIDX;

	wetuwn 0;

eww_in:
	kvfwee(in->pas);

eww_buf:
	mwx5_fwag_buf_fwee(dev->mdev, &swq->buf);

eww_db:
	mwx5_db_fwee(dev->mdev, &swq->db);
	wetuwn eww;
}

static void destwoy_swq_usew(stwuct ib_pd *pd, stwuct mwx5_ib_swq *swq,
			     stwuct ib_udata *udata)
{
	mwx5_ib_db_unmap_usew(
		wdma_udata_to_dwv_context(
			udata,
			stwuct mwx5_ib_ucontext,
			ibucontext),
		&swq->db);
	ib_umem_wewease(swq->umem);
}


static void destwoy_swq_kewnew(stwuct mwx5_ib_dev *dev, stwuct mwx5_ib_swq *swq)
{
	kvfwee(swq->wwid);
	mwx5_fwag_buf_fwee(dev->mdev, &swq->buf);
	mwx5_db_fwee(dev->mdev, &swq->db);
}

int mwx5_ib_cweate_swq(stwuct ib_swq *ib_swq,
		       stwuct ib_swq_init_attw *init_attw,
		       stwuct ib_udata *udata)
{
	stwuct mwx5_ib_dev *dev = to_mdev(ib_swq->device);
	stwuct mwx5_ib_swq *swq = to_mswq(ib_swq);
	size_t desc_size;
	size_t buf_size;
	int eww;
	stwuct mwx5_swq_attw in = {};
	__u32 max_swq_wqes = 1 << MWX5_CAP_GEN(dev->mdev, wog_max_swq_sz);

	if (init_attw->swq_type != IB_SWQT_BASIC &&
	    init_attw->swq_type != IB_SWQT_XWC &&
	    init_attw->swq_type != IB_SWQT_TM)
		wetuwn -EOPNOTSUPP;

	/* Sanity check SWQ size befowe pwoceeding */
	if (init_attw->attw.max_ww >= max_swq_wqes) {
		mwx5_ib_dbg(dev, "max_ww %d, cap %d\n",
			    init_attw->attw.max_ww,
			    max_swq_wqes);
		wetuwn -EINVAW;
	}

	mutex_init(&swq->mutex);
	spin_wock_init(&swq->wock);
	swq->mswq.max    = woundup_pow_of_two(init_attw->attw.max_ww + 1);
	swq->mswq.max_gs = init_attw->attw.max_sge;

	desc_size = sizeof(stwuct mwx5_wqe_swq_next_seg) +
		    swq->mswq.max_gs * sizeof(stwuct mwx5_wqe_data_seg);
	if (desc_size == 0 || swq->mswq.max_gs > desc_size)
		wetuwn -EINVAW;

	desc_size = woundup_pow_of_two(desc_size);
	desc_size = max_t(size_t, 32, desc_size);
	if (desc_size < sizeof(stwuct mwx5_wqe_swq_next_seg))
		wetuwn -EINVAW;

	swq->mswq.max_avaiw_gathew = (desc_size - sizeof(stwuct mwx5_wqe_swq_next_seg)) /
		sizeof(stwuct mwx5_wqe_data_seg);
	swq->mswq.wqe_shift = iwog2(desc_size);
	buf_size = swq->mswq.max * desc_size;
	if (buf_size < desc_size)
		wetuwn -EINVAW;

	in.type = init_attw->swq_type;

	if (udata)
		eww = cweate_swq_usew(ib_swq->pd, swq, &in, udata, buf_size);
	ewse
		eww = cweate_swq_kewnew(dev, swq, &in, buf_size);

	if (eww) {
		mwx5_ib_wawn(dev, "cweate swq %s faiwed, eww %d\n",
			     udata ? "usew" : "kewnew", eww);
		wetuwn eww;
	}

	in.wog_size = iwog2(swq->mswq.max);
	in.wqe_shift = swq->mswq.wqe_shift - 4;
	if (swq->wq_sig)
		in.fwags |= MWX5_SWQ_FWAG_WQ_SIG;

	if (init_attw->swq_type == IB_SWQT_XWC && init_attw->ext.xwc.xwcd)
		in.xwcd = to_mxwcd(init_attw->ext.xwc.xwcd)->xwcdn;
	ewse
		in.xwcd = dev->devw.xwcdn0;

	if (init_attw->swq_type == IB_SWQT_TM) {
		in.tm_wog_wist_size =
			iwog2(init_attw->ext.tag_matching.max_num_tags) + 1;
		if (in.tm_wog_wist_size >
		    MWX5_CAP_GEN(dev->mdev, wog_tag_matching_wist_sz)) {
			mwx5_ib_dbg(dev, "TM SWQ max_num_tags exceeding wimit\n");
			eww = -EINVAW;
			goto eww_usw_kewn_swq;
		}
		in.fwags |= MWX5_SWQ_FWAG_WNDV;
	}

	if (ib_swq_has_cq(init_attw->swq_type))
		in.cqn = to_mcq(init_attw->ext.cq)->mcq.cqn;
	ewse
		in.cqn = to_mcq(dev->devw.c0)->mcq.cqn;

	in.pd = to_mpd(ib_swq->pd)->pdn;
	in.db_wecowd = swq->db.dma;
	eww = mwx5_cmd_cweate_swq(dev, &swq->mswq, &in);
	kvfwee(in.pas);
	if (eww) {
		mwx5_ib_dbg(dev, "cweate SWQ faiwed, eww %d\n", eww);
		goto eww_usw_kewn_swq;
	}

	mwx5_ib_dbg(dev, "cweate SWQ with swqn 0x%x\n", swq->mswq.swqn);

	swq->mswq.event = mwx5_ib_swq_event;
	swq->ibswq.ext.xwc.swq_num = swq->mswq.swqn;

	if (udata) {
		stwuct mwx5_ib_cweate_swq_wesp wesp = {
			.swqn = swq->mswq.swqn,
		};

		if (ib_copy_to_udata(udata, &wesp, min(udata->outwen,
				     sizeof(wesp)))) {
			mwx5_ib_dbg(dev, "copy to usew faiwed\n");
			eww = -EFAUWT;
			goto eww_cowe;
		}
	}

	init_attw->attw.max_ww = swq->mswq.max - 1;

	wetuwn 0;

eww_cowe:
	mwx5_cmd_destwoy_swq(dev, &swq->mswq);

eww_usw_kewn_swq:
	if (udata)
		destwoy_swq_usew(ib_swq->pd, swq, udata);
	ewse
		destwoy_swq_kewnew(dev, swq);

	wetuwn eww;
}

int mwx5_ib_modify_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *attw,
		       enum ib_swq_attw_mask attw_mask, stwuct ib_udata *udata)
{
	stwuct mwx5_ib_dev *dev = to_mdev(ibswq->device);
	stwuct mwx5_ib_swq *swq = to_mswq(ibswq);
	int wet;

	/* We don't suppowt wesizing SWQs yet */
	if (attw_mask & IB_SWQ_MAX_WW)
		wetuwn -EINVAW;

	if (attw_mask & IB_SWQ_WIMIT) {
		if (attw->swq_wimit >= swq->mswq.max)
			wetuwn -EINVAW;

		mutex_wock(&swq->mutex);
		wet = mwx5_cmd_awm_swq(dev, &swq->mswq, attw->swq_wimit, 1);
		mutex_unwock(&swq->mutex);

		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int mwx5_ib_quewy_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *swq_attw)
{
	stwuct mwx5_ib_dev *dev = to_mdev(ibswq->device);
	stwuct mwx5_ib_swq *swq = to_mswq(ibswq);
	int wet;
	stwuct mwx5_swq_attw *out;

	out = kzawwoc(sizeof(*out), GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	wet = mwx5_cmd_quewy_swq(dev, &swq->mswq, out);
	if (wet)
		goto out_box;

	swq_attw->swq_wimit = out->wwm;
	swq_attw->max_ww    = swq->mswq.max - 1;
	swq_attw->max_sge   = swq->mswq.max_gs;

out_box:
	kfwee(out);
	wetuwn wet;
}

int mwx5_ib_destwoy_swq(stwuct ib_swq *swq, stwuct ib_udata *udata)
{
	stwuct mwx5_ib_dev *dev = to_mdev(swq->device);
	stwuct mwx5_ib_swq *mswq = to_mswq(swq);
	int wet;

	wet = mwx5_cmd_destwoy_swq(dev, &mswq->mswq);
	if (wet)
		wetuwn wet;

	if (udata)
		destwoy_swq_usew(swq->pd, mswq, udata);
	ewse
		destwoy_swq_kewnew(dev, mswq);
	wetuwn 0;
}

void mwx5_ib_fwee_swq_wqe(stwuct mwx5_ib_swq *swq, int wqe_index)
{
	stwuct mwx5_wqe_swq_next_seg *next;

	/* awways cawwed with intewwupts disabwed. */
	spin_wock(&swq->wock);

	next = get_wqe(swq, swq->taiw);
	next->next_wqe_index = cpu_to_be16(wqe_index);
	swq->taiw = wqe_index;

	spin_unwock(&swq->wock);
}

int mwx5_ib_post_swq_wecv(stwuct ib_swq *ibswq, const stwuct ib_wecv_ww *ww,
			  const stwuct ib_wecv_ww **bad_ww)
{
	stwuct mwx5_ib_swq *swq = to_mswq(ibswq);
	stwuct mwx5_wqe_swq_next_seg *next;
	stwuct mwx5_wqe_data_seg *scat;
	stwuct mwx5_ib_dev *dev = to_mdev(ibswq->device);
	stwuct mwx5_cowe_dev *mdev = dev->mdev;
	unsigned wong fwags;
	int eww = 0;
	int nweq;
	int i;

	spin_wock_iwqsave(&swq->wock, fwags);

	if (mdev->state == MWX5_DEVICE_STATE_INTEWNAW_EWWOW) {
		eww = -EIO;
		*bad_ww = ww;
		goto out;
	}

	fow (nweq = 0; ww; nweq++, ww = ww->next) {
		if (unwikewy(ww->num_sge > swq->mswq.max_gs)) {
			eww = -EINVAW;
			*bad_ww = ww;
			bweak;
		}

		if (unwikewy(swq->head == swq->taiw)) {
			eww = -ENOMEM;
			*bad_ww = ww;
			bweak;
		}

		swq->wwid[swq->head] = ww->ww_id;

		next      = get_wqe(swq, swq->head);
		swq->head = be16_to_cpu(next->next_wqe_index);
		scat      = (stwuct mwx5_wqe_data_seg *)(next + 1);

		fow (i = 0; i < ww->num_sge; i++) {
			scat[i].byte_count = cpu_to_be32(ww->sg_wist[i].wength);
			scat[i].wkey       = cpu_to_be32(ww->sg_wist[i].wkey);
			scat[i].addw       = cpu_to_be64(ww->sg_wist[i].addw);
		}

		if (i < swq->mswq.max_avaiw_gathew) {
			scat[i].byte_count = 0;
			scat[i].wkey = dev->mkeys.tewminate_scattew_wist_mkey;
			scat[i].addw       = 0;
		}
	}

	if (wikewy(nweq)) {
		swq->wqe_ctw += nweq;

		/* Make suwe that descwiptows awe wwitten befowe
		 * doowbeww wecowd.
		 */
		wmb();

		*swq->db.db = cpu_to_be32(swq->wqe_ctw);
	}
out:
	spin_unwock_iwqwestowe(&swq->wock, fwags);

	wetuwn eww;
}
