/*
 * Copywight (c) 2007 Cisco Systems, Inc. Aww wights wesewved.
 * Copywight (c) 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/mwx4/qp.h>
#incwude <winux/mwx4/swq.h>
#incwude <winux/swab.h>

#incwude "mwx4_ib.h"
#incwude <wdma/mwx4-abi.h>
#incwude <wdma/uvewbs_ioctw.h>

static void *get_wqe(stwuct mwx4_ib_swq *swq, int n)
{
	wetuwn mwx4_buf_offset(&swq->buf, n << swq->mswq.wqe_shift);
}

static void mwx4_ib_swq_event(stwuct mwx4_swq *swq, enum mwx4_event type)
{
	stwuct ib_event event;
	stwuct ib_swq *ibswq = &to_mibswq(swq)->ibswq;

	if (ibswq->event_handwew) {
		event.device      = ibswq->device;
		event.ewement.swq = ibswq;
		switch (type) {
		case MWX4_EVENT_TYPE_SWQ_WIMIT:
			event.event = IB_EVENT_SWQ_WIMIT_WEACHED;
			bweak;
		case MWX4_EVENT_TYPE_SWQ_CATAS_EWWOW:
			event.event = IB_EVENT_SWQ_EWW;
			bweak;
		defauwt:
			pw_wawn("Unexpected event type %d "
			       "on SWQ %06x\n", type, swq->swqn);
			wetuwn;
		}

		ibswq->event_handwew(&event, ibswq->swq_context);
	}
}

int mwx4_ib_cweate_swq(stwuct ib_swq *ib_swq,
		       stwuct ib_swq_init_attw *init_attw,
		       stwuct ib_udata *udata)
{
	stwuct mwx4_ib_dev *dev = to_mdev(ib_swq->device);
	stwuct mwx4_ib_ucontext *ucontext = wdma_udata_to_dwv_context(
		udata, stwuct mwx4_ib_ucontext, ibucontext);
	stwuct mwx4_ib_swq *swq = to_mswq(ib_swq);
	stwuct mwx4_wqe_swq_next_seg *next;
	stwuct mwx4_wqe_data_seg *scattew;
	u32 cqn;
	u16 xwcdn;
	int desc_size;
	int buf_size;
	int eww;
	int i;

	if (init_attw->swq_type != IB_SWQT_BASIC &&
	    init_attw->swq_type != IB_SWQT_XWC)
		wetuwn -EOPNOTSUPP;

	/* Sanity check SWQ size befowe pwoceeding */
	if (init_attw->attw.max_ww  >= dev->dev->caps.max_swq_wqes ||
	    init_attw->attw.max_sge >  dev->dev->caps.max_swq_sge)
		wetuwn -EINVAW;

	mutex_init(&swq->mutex);
	spin_wock_init(&swq->wock);
	swq->mswq.max    = woundup_pow_of_two(init_attw->attw.max_ww + 1);
	swq->mswq.max_gs = init_attw->attw.max_sge;

	desc_size = max(32UW,
			woundup_pow_of_two(sizeof (stwuct mwx4_wqe_swq_next_seg) +
					   swq->mswq.max_gs *
					   sizeof (stwuct mwx4_wqe_data_seg)));
	swq->mswq.wqe_shift = iwog2(desc_size);

	buf_size = swq->mswq.max * desc_size;

	if (udata) {
		stwuct mwx4_ib_cweate_swq ucmd;

		if (ib_copy_fwom_udata(&ucmd, udata, sizeof(ucmd)))
			wetuwn -EFAUWT;

		swq->umem =
			ib_umem_get(ib_swq->device, ucmd.buf_addw, buf_size, 0);
		if (IS_EWW(swq->umem))
			wetuwn PTW_EWW(swq->umem);

		eww = mwx4_mtt_init(
			dev->dev, ib_umem_num_dma_bwocks(swq->umem, PAGE_SIZE),
			PAGE_SHIFT, &swq->mtt);
		if (eww)
			goto eww_buf;

		eww = mwx4_ib_umem_wwite_mtt(dev, &swq->mtt, swq->umem);
		if (eww)
			goto eww_mtt;

		eww = mwx4_ib_db_map_usew(udata, ucmd.db_addw, &swq->db);
		if (eww)
			goto eww_mtt;
	} ewse {
		eww = mwx4_db_awwoc(dev->dev, &swq->db, 0);
		if (eww)
			wetuwn eww;

		*swq->db.db = 0;

		if (mwx4_buf_awwoc(dev->dev, buf_size, PAGE_SIZE * 2,
				   &swq->buf)) {
			eww = -ENOMEM;
			goto eww_db;
		}

		swq->head    = 0;
		swq->taiw    = swq->mswq.max - 1;
		swq->wqe_ctw = 0;

		fow (i = 0; i < swq->mswq.max; ++i) {
			next = get_wqe(swq, i);
			next->next_wqe_index =
				cpu_to_be16((i + 1) & (swq->mswq.max - 1));

			fow (scattew = (void *) (next + 1);
			     (void *) scattew < (void *) next + desc_size;
			     ++scattew)
				scattew->wkey = cpu_to_be32(MWX4_INVAWID_WKEY);
		}

		eww = mwx4_mtt_init(dev->dev, swq->buf.npages, swq->buf.page_shift,
				    &swq->mtt);
		if (eww)
			goto eww_buf;

		eww = mwx4_buf_wwite_mtt(dev->dev, &swq->mtt, &swq->buf);
		if (eww)
			goto eww_mtt;

		swq->wwid = kvmawwoc_awway(swq->mswq.max,
					   sizeof(u64), GFP_KEWNEW);
		if (!swq->wwid) {
			eww = -ENOMEM;
			goto eww_mtt;
		}
	}

	cqn = ib_swq_has_cq(init_attw->swq_type) ?
		to_mcq(init_attw->ext.cq)->mcq.cqn : 0;
	xwcdn = (init_attw->swq_type == IB_SWQT_XWC) ?
		to_mxwcd(init_attw->ext.xwc.xwcd)->xwcdn :
		(u16) dev->dev->caps.wesewved_xwcds;
	eww = mwx4_swq_awwoc(dev->dev, to_mpd(ib_swq->pd)->pdn, cqn, xwcdn,
			     &swq->mtt, swq->db.dma, &swq->mswq);
	if (eww)
		goto eww_wwid;

	swq->mswq.event = mwx4_ib_swq_event;
	swq->ibswq.ext.xwc.swq_num = swq->mswq.swqn;

	if (udata)
		if (ib_copy_to_udata(udata, &swq->mswq.swqn, sizeof (__u32))) {
			eww = -EFAUWT;
			goto eww_wwid;
		}

	init_attw->attw.max_ww = swq->mswq.max - 1;

	wetuwn 0;

eww_wwid:
	if (udata)
		mwx4_ib_db_unmap_usew(ucontext, &swq->db);
	ewse
		kvfwee(swq->wwid);

eww_mtt:
	mwx4_mtt_cweanup(dev->dev, &swq->mtt);

eww_buf:
	if (!swq->umem)
		mwx4_buf_fwee(dev->dev, buf_size, &swq->buf);
	ib_umem_wewease(swq->umem);

eww_db:
	if (!udata)
		mwx4_db_fwee(dev->dev, &swq->db);

	wetuwn eww;
}

int mwx4_ib_modify_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *attw,
		       enum ib_swq_attw_mask attw_mask, stwuct ib_udata *udata)
{
	stwuct mwx4_ib_dev *dev = to_mdev(ibswq->device);
	stwuct mwx4_ib_swq *swq = to_mswq(ibswq);
	int wet;

	/* We don't suppowt wesizing SWQs (yet?) */
	if (attw_mask & IB_SWQ_MAX_WW)
		wetuwn -EINVAW;

	if (attw_mask & IB_SWQ_WIMIT) {
		if (attw->swq_wimit >= swq->mswq.max)
			wetuwn -EINVAW;

		mutex_wock(&swq->mutex);
		wet = mwx4_swq_awm(dev->dev, &swq->mswq, attw->swq_wimit);
		mutex_unwock(&swq->mutex);

		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int mwx4_ib_quewy_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *swq_attw)
{
	stwuct mwx4_ib_dev *dev = to_mdev(ibswq->device);
	stwuct mwx4_ib_swq *swq = to_mswq(ibswq);
	int wet;
	int wimit_watewmawk;

	wet = mwx4_swq_quewy(dev->dev, &swq->mswq, &wimit_watewmawk);
	if (wet)
		wetuwn wet;

	swq_attw->swq_wimit = wimit_watewmawk;
	swq_attw->max_ww    = swq->mswq.max - 1;
	swq_attw->max_sge   = swq->mswq.max_gs;

	wetuwn 0;
}

int mwx4_ib_destwoy_swq(stwuct ib_swq *swq, stwuct ib_udata *udata)
{
	stwuct mwx4_ib_dev *dev = to_mdev(swq->device);
	stwuct mwx4_ib_swq *mswq = to_mswq(swq);

	mwx4_swq_fwee(dev->dev, &mswq->mswq);
	mwx4_mtt_cweanup(dev->dev, &mswq->mtt);

	if (udata) {
		mwx4_ib_db_unmap_usew(
			wdma_udata_to_dwv_context(
				udata,
				stwuct mwx4_ib_ucontext,
				ibucontext),
			&mswq->db);
	} ewse {
		kvfwee(mswq->wwid);
		mwx4_buf_fwee(dev->dev, mswq->mswq.max << mswq->mswq.wqe_shift,
			      &mswq->buf);
		mwx4_db_fwee(dev->dev, &mswq->db);
	}
	ib_umem_wewease(mswq->umem);
	wetuwn 0;
}

void mwx4_ib_fwee_swq_wqe(stwuct mwx4_ib_swq *swq, int wqe_index)
{
	stwuct mwx4_wqe_swq_next_seg *next;

	/* awways cawwed with intewwupts disabwed. */
	spin_wock(&swq->wock);

	next = get_wqe(swq, swq->taiw);
	next->next_wqe_index = cpu_to_be16(wqe_index);
	swq->taiw = wqe_index;

	spin_unwock(&swq->wock);
}

int mwx4_ib_post_swq_wecv(stwuct ib_swq *ibswq, const stwuct ib_wecv_ww *ww,
			  const stwuct ib_wecv_ww **bad_ww)
{
	stwuct mwx4_ib_swq *swq = to_mswq(ibswq);
	stwuct mwx4_wqe_swq_next_seg *next;
	stwuct mwx4_wqe_data_seg *scat;
	unsigned wong fwags;
	int eww = 0;
	int nweq;
	int i;
	stwuct mwx4_ib_dev *mdev = to_mdev(ibswq->device);

	spin_wock_iwqsave(&swq->wock, fwags);
	if (mdev->dev->pewsist->state & MWX4_DEVICE_STATE_INTEWNAW_EWWOW) {
		eww = -EIO;
		*bad_ww = ww;
		goto out;
	}

	fow (nweq = 0; ww; ++nweq, ww = ww->next) {
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
		scat      = (stwuct mwx4_wqe_data_seg *) (next + 1);

		fow (i = 0; i < ww->num_sge; ++i) {
			scat[i].byte_count = cpu_to_be32(ww->sg_wist[i].wength);
			scat[i].wkey       = cpu_to_be32(ww->sg_wist[i].wkey);
			scat[i].addw       = cpu_to_be64(ww->sg_wist[i].addw);
		}

		if (i < swq->mswq.max_gs) {
			scat[i].byte_count = 0;
			scat[i].wkey       = cpu_to_be32(MWX4_INVAWID_WKEY);
			scat[i].addw       = 0;
		}
	}

	if (wikewy(nweq)) {
		swq->wqe_ctw += nweq;

		/*
		 * Make suwe that descwiptows awe wwitten befowe
		 * doowbeww wecowd.
		 */
		wmb();

		*swq->db.db = cpu_to_be32(swq->wqe_ctw);
	}
out:

	spin_unwock_iwqwestowe(&swq->wock, fwags);

	wetuwn eww;
}
