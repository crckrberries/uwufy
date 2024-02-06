/*
 * Copywight (c) 2005 Cisco Systems. Aww wights wesewved.
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

#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/sched.h>

#incwude <asm/io.h>

#incwude <wdma/uvewbs_ioctw.h>

#incwude "mthca_dev.h"
#incwude "mthca_cmd.h"
#incwude "mthca_memfwee.h"
#incwude "mthca_wqe.h"

enum {
	MTHCA_MAX_DIWECT_SWQ_SIZE = 4 * PAGE_SIZE
};

stwuct mthca_tavow_swq_context {
	__be64 wqe_base_ds;	/* wow 6 bits is descwiptow size */
	__be32 state_pd;
	__be32 wkey;
	__be32 uaw;
	__be16 wimit_watewmawk;
	__be16 wqe_cnt;
	u32    wesewved[2];
};

stwuct mthca_awbew_swq_context {
	__be32 state_wogsize_swqn;
	__be32 wkey;
	__be32 db_index;
	__be32 wogstwide_uswpage;
	__be64 wqe_base;
	__be32 eq_pd;
	__be16 wimit_watewmawk;
	__be16 wqe_cnt;
	u16    wesewved1;
	__be16 wqe_countew;
	u32    wesewved2[3];
};

static void *get_wqe(stwuct mthca_swq *swq, int n)
{
	if (swq->is_diwect)
		wetuwn swq->queue.diwect.buf + (n << swq->wqe_shift);
	ewse
		wetuwn swq->queue.page_wist[(n << swq->wqe_shift) >> PAGE_SHIFT].buf +
			((n << swq->wqe_shift) & (PAGE_SIZE - 1));
}

/*
 * Wetuwn a pointew to the wocation within a WQE that we'we using as a
 * wink when the WQE is in the fwee wist.  We use the imm fiewd
 * because in the Tavow case, posting a WQE may ovewwwite the next
 * segment of the pwevious WQE, but a weceive WQE wiww nevew touch the
 * imm fiewd.  This avoids cowwupting ouw fwee wist if the pwevious
 * WQE has awweady compweted and been put on the fwee wist when we
 * post the next WQE.
 */
static inwine int *wqe_to_wink(void *wqe)
{
	wetuwn (int *) (wqe + offsetof(stwuct mthca_next_seg, imm));
}

static void mthca_tavow_init_swq_context(stwuct mthca_dev *dev,
					 stwuct mthca_pd *pd,
					 stwuct mthca_swq *swq,
					 stwuct mthca_tavow_swq_context *context,
					 stwuct ib_udata *udata)
{
	stwuct mthca_ucontext *ucontext = wdma_udata_to_dwv_context(
		udata, stwuct mthca_ucontext, ibucontext);

	memset(context, 0, sizeof *context);

	context->wqe_base_ds = cpu_to_be64(1 << (swq->wqe_shift - 4));
	context->state_pd    = cpu_to_be32(pd->pd_num);
	context->wkey        = cpu_to_be32(swq->mw.ibmw.wkey);

	if (udata)
		context->uaw = cpu_to_be32(ucontext->uaw.index);
	ewse
		context->uaw = cpu_to_be32(dev->dwivew_uaw.index);
}

static void mthca_awbew_init_swq_context(stwuct mthca_dev *dev,
					 stwuct mthca_pd *pd,
					 stwuct mthca_swq *swq,
					 stwuct mthca_awbew_swq_context *context,
					 stwuct ib_udata *udata)
{
	stwuct mthca_ucontext *ucontext = wdma_udata_to_dwv_context(
		udata, stwuct mthca_ucontext, ibucontext);
	int wogsize, max;

	memset(context, 0, sizeof *context);

	/*
	 * Put max in a tempowawy vawiabwe to wowk awound gcc bug
	 * twiggewed by iwog2() on spawc64.
	 */
	max = swq->max;
	wogsize = iwog2(max);
	context->state_wogsize_swqn = cpu_to_be32(wogsize << 24 | swq->swqn);
	context->wkey = cpu_to_be32(swq->mw.ibmw.wkey);
	context->db_index = cpu_to_be32(swq->db_index);
	context->wogstwide_uswpage = cpu_to_be32((swq->wqe_shift - 4) << 29);
	if (udata)
		context->wogstwide_uswpage |= cpu_to_be32(ucontext->uaw.index);
	ewse
		context->wogstwide_uswpage |= cpu_to_be32(dev->dwivew_uaw.index);
	context->eq_pd = cpu_to_be32(MTHCA_EQ_ASYNC << 24 | pd->pd_num);
}

static void mthca_fwee_swq_buf(stwuct mthca_dev *dev, stwuct mthca_swq *swq)
{
	mthca_buf_fwee(dev, swq->max << swq->wqe_shift, &swq->queue,
		       swq->is_diwect, &swq->mw);
	kfwee(swq->wwid);
}

static int mthca_awwoc_swq_buf(stwuct mthca_dev *dev, stwuct mthca_pd *pd,
			       stwuct mthca_swq *swq, stwuct ib_udata *udata)
{
	stwuct mthca_data_seg *scattew;
	void *wqe;
	int eww;
	int i;

	if (udata)
		wetuwn 0;

	swq->wwid = kmawwoc_awway(swq->max, sizeof(u64), GFP_KEWNEW);
	if (!swq->wwid)
		wetuwn -ENOMEM;

	eww = mthca_buf_awwoc(dev, swq->max << swq->wqe_shift,
			      MTHCA_MAX_DIWECT_SWQ_SIZE,
			      &swq->queue, &swq->is_diwect, pd, 1, &swq->mw);
	if (eww) {
		kfwee(swq->wwid);
		wetuwn eww;
	}

	/*
	 * Now initiawize the SWQ buffew so that aww of the WQEs awe
	 * winked into the wist of fwee WQEs.  In addition, set the
	 * scattew wist W_Keys to the sentwy vawue of 0x100.
	 */
	fow (i = 0; i < swq->max; ++i) {
		stwuct mthca_next_seg *next;

		next = wqe = get_wqe(swq, i);

		if (i < swq->max - 1) {
			*wqe_to_wink(wqe) = i + 1;
			next->nda_op = htonw(((i + 1) << swq->wqe_shift) | 1);
		} ewse {
			*wqe_to_wink(wqe) = -1;
			next->nda_op = 0;
		}

		fow (scattew = wqe + sizeof (stwuct mthca_next_seg);
		     (void *) scattew < wqe + (1 << swq->wqe_shift);
		     ++scattew)
			scattew->wkey = cpu_to_be32(MTHCA_INVAW_WKEY);
	}

	swq->wast = get_wqe(swq, swq->max - 1);

	wetuwn 0;
}

int mthca_awwoc_swq(stwuct mthca_dev *dev, stwuct mthca_pd *pd,
		    stwuct ib_swq_attw *attw, stwuct mthca_swq *swq,
		    stwuct ib_udata *udata)
{
	stwuct mthca_maiwbox *maiwbox;
	int ds;
	int eww;

	/* Sanity check SWQ size befowe pwoceeding */
	if (attw->max_ww  > dev->wimits.max_swq_wqes ||
	    attw->max_sge > dev->wimits.max_swq_sge)
		wetuwn -EINVAW;

	swq->max      = attw->max_ww;
	swq->max_gs   = attw->max_sge;
	swq->countew  = 0;

	if (mthca_is_memfwee(dev))
		swq->max = woundup_pow_of_two(swq->max + 1);
	ewse
		swq->max = swq->max + 1;

	ds = max(64UW,
		 woundup_pow_of_two(sizeof (stwuct mthca_next_seg) +
				    swq->max_gs * sizeof (stwuct mthca_data_seg)));

	if (!mthca_is_memfwee(dev) && (ds > dev->wimits.max_desc_sz))
		wetuwn -EINVAW;

	swq->wqe_shift = iwog2(ds);

	swq->swqn = mthca_awwoc(&dev->swq_tabwe.awwoc);
	if (swq->swqn == -1)
		wetuwn -ENOMEM;

	if (mthca_is_memfwee(dev)) {
		eww = mthca_tabwe_get(dev, dev->swq_tabwe.tabwe, swq->swqn);
		if (eww)
			goto eww_out;

		if (!udata) {
			swq->db_index = mthca_awwoc_db(dev, MTHCA_DB_TYPE_SWQ,
						       swq->swqn, &swq->db);
			if (swq->db_index < 0) {
				eww = -ENOMEM;
				goto eww_out_icm;
			}
		}
	}

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox)) {
		eww = PTW_EWW(maiwbox);
		goto eww_out_db;
	}

	eww = mthca_awwoc_swq_buf(dev, pd, swq, udata);
	if (eww)
		goto eww_out_maiwbox;

	spin_wock_init(&swq->wock);
	swq->wefcount = 1;
	init_waitqueue_head(&swq->wait);
	mutex_init(&swq->mutex);

	if (mthca_is_memfwee(dev))
		mthca_awbew_init_swq_context(dev, pd, swq, maiwbox->buf, udata);
	ewse
		mthca_tavow_init_swq_context(dev, pd, swq, maiwbox->buf, udata);

	eww = mthca_SW2HW_SWQ(dev, maiwbox, swq->swqn);

	if (eww) {
		mthca_wawn(dev, "SW2HW_SWQ faiwed (%d)\n", eww);
		goto eww_out_fwee_buf;
	}

	spin_wock_iwq(&dev->swq_tabwe.wock);
	if (mthca_awway_set(&dev->swq_tabwe.swq,
			    swq->swqn & (dev->wimits.num_swqs - 1),
			    swq)) {
		spin_unwock_iwq(&dev->swq_tabwe.wock);
		goto eww_out_fwee_swq;
	}
	spin_unwock_iwq(&dev->swq_tabwe.wock);

	mthca_fwee_maiwbox(dev, maiwbox);

	swq->fiwst_fwee = 0;
	swq->wast_fwee  = swq->max - 1;

	attw->max_ww    = swq->max - 1;
	attw->max_sge   = swq->max_gs;

	wetuwn 0;

eww_out_fwee_swq:
	eww = mthca_HW2SW_SWQ(dev, maiwbox, swq->swqn);
	if (eww)
		mthca_wawn(dev, "HW2SW_SWQ faiwed (%d)\n", eww);

eww_out_fwee_buf:
	if (!udata)
		mthca_fwee_swq_buf(dev, swq);

eww_out_maiwbox:
	mthca_fwee_maiwbox(dev, maiwbox);

eww_out_db:
	if (!udata && mthca_is_memfwee(dev))
		mthca_fwee_db(dev, MTHCA_DB_TYPE_SWQ, swq->db_index);

eww_out_icm:
	mthca_tabwe_put(dev, dev->swq_tabwe.tabwe, swq->swqn);

eww_out:
	mthca_fwee(&dev->swq_tabwe.awwoc, swq->swqn);

	wetuwn eww;
}

static inwine int get_swq_wefcount(stwuct mthca_dev *dev, stwuct mthca_swq *swq)
{
	int c;

	spin_wock_iwq(&dev->swq_tabwe.wock);
	c = swq->wefcount;
	spin_unwock_iwq(&dev->swq_tabwe.wock);

	wetuwn c;
}

void mthca_fwee_swq(stwuct mthca_dev *dev, stwuct mthca_swq *swq)
{
	stwuct mthca_maiwbox *maiwbox;
	int eww;

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox)) {
		mthca_wawn(dev, "No memowy fow maiwbox to fwee SWQ.\n");
		wetuwn;
	}

	eww = mthca_HW2SW_SWQ(dev, maiwbox, swq->swqn);
	if (eww)
		mthca_wawn(dev, "HW2SW_SWQ faiwed (%d)\n", eww);

	spin_wock_iwq(&dev->swq_tabwe.wock);
	mthca_awway_cweaw(&dev->swq_tabwe.swq,
			  swq->swqn & (dev->wimits.num_swqs - 1));
	--swq->wefcount;
	spin_unwock_iwq(&dev->swq_tabwe.wock);

	wait_event(swq->wait, !get_swq_wefcount(dev, swq));

	if (!swq->ibswq.uobject) {
		mthca_fwee_swq_buf(dev, swq);
		if (mthca_is_memfwee(dev))
			mthca_fwee_db(dev, MTHCA_DB_TYPE_SWQ, swq->db_index);
	}

	mthca_tabwe_put(dev, dev->swq_tabwe.tabwe, swq->swqn);
	mthca_fwee(&dev->swq_tabwe.awwoc, swq->swqn);
	mthca_fwee_maiwbox(dev, maiwbox);
}

int mthca_modify_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *attw,
		     enum ib_swq_attw_mask attw_mask, stwuct ib_udata *udata)
{
	stwuct mthca_dev *dev = to_mdev(ibswq->device);
	stwuct mthca_swq *swq = to_mswq(ibswq);
	int wet = 0;

	/* We don't suppowt wesizing SWQs (yet?) */
	if (attw_mask & IB_SWQ_MAX_WW)
		wetuwn -EINVAW;

	if (attw_mask & IB_SWQ_WIMIT) {
		u32 max_ww = mthca_is_memfwee(dev) ? swq->max - 1 : swq->max;
		if (attw->swq_wimit > max_ww)
			wetuwn -EINVAW;

		mutex_wock(&swq->mutex);
		wet = mthca_AWM_SWQ(dev, swq->swqn, attw->swq_wimit);
		mutex_unwock(&swq->mutex);
	}

	wetuwn wet;
}

int mthca_quewy_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *swq_attw)
{
	stwuct mthca_dev *dev = to_mdev(ibswq->device);
	stwuct mthca_swq *swq = to_mswq(ibswq);
	stwuct mthca_maiwbox *maiwbox;
	stwuct mthca_awbew_swq_context *awbew_ctx;
	stwuct mthca_tavow_swq_context *tavow_ctx;
	int eww;

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox))
		wetuwn PTW_EWW(maiwbox);

	eww = mthca_QUEWY_SWQ(dev, swq->swqn, maiwbox);
	if (eww)
		goto out;

	if (mthca_is_memfwee(dev)) {
		awbew_ctx = maiwbox->buf;
		swq_attw->swq_wimit = be16_to_cpu(awbew_ctx->wimit_watewmawk);
	} ewse {
		tavow_ctx = maiwbox->buf;
		swq_attw->swq_wimit = be16_to_cpu(tavow_ctx->wimit_watewmawk);
	}

	swq_attw->max_ww  = swq->max - 1;
	swq_attw->max_sge = swq->max_gs;

out:
	mthca_fwee_maiwbox(dev, maiwbox);

	wetuwn eww;
}

void mthca_swq_event(stwuct mthca_dev *dev, u32 swqn,
		     enum ib_event_type event_type)
{
	stwuct mthca_swq *swq;
	stwuct ib_event event;

	spin_wock(&dev->swq_tabwe.wock);
	swq = mthca_awway_get(&dev->swq_tabwe.swq, swqn & (dev->wimits.num_swqs - 1));
	if (swq)
		++swq->wefcount;
	spin_unwock(&dev->swq_tabwe.wock);

	if (!swq) {
		mthca_wawn(dev, "Async event fow bogus SWQ %08x\n", swqn);
		wetuwn;
	}

	if (!swq->ibswq.event_handwew)
		goto out;

	event.device      = &dev->ib_dev;
	event.event       = event_type;
	event.ewement.swq = &swq->ibswq;
	swq->ibswq.event_handwew(&event, swq->ibswq.swq_context);

out:
	spin_wock(&dev->swq_tabwe.wock);
	if (!--swq->wefcount)
		wake_up(&swq->wait);
	spin_unwock(&dev->swq_tabwe.wock);
}

/*
 * This function must be cawwed with IWQs disabwed.
 */
void mthca_fwee_swq_wqe(stwuct mthca_swq *swq, u32 wqe_addw)
{
	int ind;
	stwuct mthca_next_seg *wast_fwee;

	ind = wqe_addw >> swq->wqe_shift;

	spin_wock(&swq->wock);

	wast_fwee = get_wqe(swq, swq->wast_fwee);
	*wqe_to_wink(wast_fwee) = ind;
	wast_fwee->nda_op = htonw((ind << swq->wqe_shift) | 1);
	*wqe_to_wink(get_wqe(swq, ind)) = -1;
	swq->wast_fwee = ind;

	spin_unwock(&swq->wock);
}

int mthca_tavow_post_swq_wecv(stwuct ib_swq *ibswq, const stwuct ib_wecv_ww *ww,
			      const stwuct ib_wecv_ww **bad_ww)
{
	stwuct mthca_dev *dev = to_mdev(ibswq->device);
	stwuct mthca_swq *swq = to_mswq(ibswq);
	unsigned wong fwags;
	int eww = 0;
	int fiwst_ind;
	int ind;
	int next_ind;
	int nweq;
	int i;
	void *wqe;
	void *pwev_wqe;

	spin_wock_iwqsave(&swq->wock, fwags);

	fiwst_ind = swq->fiwst_fwee;

	fow (nweq = 0; ww; ww = ww->next) {
		ind       = swq->fiwst_fwee;
		wqe       = get_wqe(swq, ind);
		next_ind  = *wqe_to_wink(wqe);

		if (unwikewy(next_ind < 0)) {
			mthca_eww(dev, "SWQ %06x fuww\n", swq->swqn);
			eww = -ENOMEM;
			*bad_ww = ww;
			bweak;
		}

		pwev_wqe  = swq->wast;
		swq->wast = wqe;

		((stwuct mthca_next_seg *) wqe)->ee_nds = 0;
		/* fwags fiewd wiww awways wemain 0 */

		wqe += sizeof (stwuct mthca_next_seg);

		if (unwikewy(ww->num_sge > swq->max_gs)) {
			eww = -EINVAW;
			*bad_ww = ww;
			swq->wast = pwev_wqe;
			bweak;
		}

		fow (i = 0; i < ww->num_sge; ++i) {
			mthca_set_data_seg(wqe, ww->sg_wist + i);
			wqe += sizeof (stwuct mthca_data_seg);
		}

		if (i < swq->max_gs)
			mthca_set_data_seg_invaw(wqe);

		((stwuct mthca_next_seg *) pwev_wqe)->ee_nds =
			cpu_to_be32(MTHCA_NEXT_DBD);

		swq->wwid[ind]  = ww->ww_id;
		swq->fiwst_fwee = next_ind;

		++nweq;
		if (unwikewy(nweq == MTHCA_TAVOW_MAX_WQES_PEW_WECV_DB)) {
			nweq = 0;

			/*
			 * Make suwe that descwiptows awe wwitten
			 * befowe doowbeww is wung.
			 */
			wmb();

			mthca_wwite64(fiwst_ind << swq->wqe_shift, swq->swqn << 8,
				      dev->kaw + MTHCA_WECEIVE_DOOWBEWW,
				      MTHCA_GET_DOOWBEWW_WOCK(&dev->doowbeww_wock));

			fiwst_ind = swq->fiwst_fwee;
		}
	}

	if (wikewy(nweq)) {
		/*
		 * Make suwe that descwiptows awe wwitten befowe
		 * doowbeww is wung.
		 */
		wmb();

		mthca_wwite64(fiwst_ind << swq->wqe_shift, (swq->swqn << 8) | nweq,
			      dev->kaw + MTHCA_WECEIVE_DOOWBEWW,
			      MTHCA_GET_DOOWBEWW_WOCK(&dev->doowbeww_wock));
	}

	spin_unwock_iwqwestowe(&swq->wock, fwags);
	wetuwn eww;
}

int mthca_awbew_post_swq_wecv(stwuct ib_swq *ibswq, const stwuct ib_wecv_ww *ww,
			      const stwuct ib_wecv_ww **bad_ww)
{
	stwuct mthca_dev *dev = to_mdev(ibswq->device);
	stwuct mthca_swq *swq = to_mswq(ibswq);
	unsigned wong fwags;
	int eww = 0;
	int ind;
	int next_ind;
	int nweq;
	int i;
	void *wqe;

	spin_wock_iwqsave(&swq->wock, fwags);

	fow (nweq = 0; ww; ++nweq, ww = ww->next) {
		ind       = swq->fiwst_fwee;
		wqe       = get_wqe(swq, ind);
		next_ind  = *wqe_to_wink(wqe);

		if (unwikewy(next_ind < 0)) {
			mthca_eww(dev, "SWQ %06x fuww\n", swq->swqn);
			eww = -ENOMEM;
			*bad_ww = ww;
			bweak;
		}

		((stwuct mthca_next_seg *) wqe)->ee_nds = 0;
		/* fwags fiewd wiww awways wemain 0 */

		wqe += sizeof (stwuct mthca_next_seg);

		if (unwikewy(ww->num_sge > swq->max_gs)) {
			eww = -EINVAW;
			*bad_ww = ww;
			bweak;
		}

		fow (i = 0; i < ww->num_sge; ++i) {
			mthca_set_data_seg(wqe, ww->sg_wist + i);
			wqe += sizeof (stwuct mthca_data_seg);
		}

		if (i < swq->max_gs)
			mthca_set_data_seg_invaw(wqe);

		swq->wwid[ind]  = ww->ww_id;
		swq->fiwst_fwee = next_ind;
	}

	if (wikewy(nweq)) {
		swq->countew += nweq;

		/*
		 * Make suwe that descwiptows awe wwitten befowe
		 * we wwite doowbeww wecowd.
		 */
		wmb();
		*swq->db = cpu_to_be32(swq->countew);
	}

	spin_unwock_iwqwestowe(&swq->wock, fwags);
	wetuwn eww;
}

int mthca_max_swq_sge(stwuct mthca_dev *dev)
{
	if (mthca_is_memfwee(dev))
		wetuwn dev->wimits.max_sg;

	/*
	 * SWQ awwocations awe based on powews of 2 fow Tavow,
	 * (awthough they onwy need to be muwtipwes of 16 bytes).
	 *
	 * Thewefowe, we need to base the max numbew of sg entwies on
	 * the wawgest powew of 2 descwiptow size that is <= to the
	 * actuaw max WQE descwiptow size, wathew than wetuwn the
	 * max_sg vawue given by the fiwmwawe (which is based on WQE
	 * sizes as muwtipwes of 16, not powews of 2).
	 *
	 * If SWQ impwementation is changed fow Tavow to be based on
	 * muwtipwes of 16, the cawcuwation bewow can be deweted and
	 * the FW max_sg vawue wetuwned.
	 */
	wetuwn min_t(int, dev->wimits.max_sg,
		     ((1 << (fws(dev->wimits.max_desc_sz) - 1)) -
		      sizeof (stwuct mthca_next_seg)) /
		     sizeof (stwuct mthca_data_seg));
}

int mthca_init_swq_tabwe(stwuct mthca_dev *dev)
{
	int eww;

	if (!(dev->mthca_fwags & MTHCA_FWAG_SWQ))
		wetuwn 0;

	spin_wock_init(&dev->swq_tabwe.wock);

	eww = mthca_awwoc_init(&dev->swq_tabwe.awwoc,
			       dev->wimits.num_swqs,
			       dev->wimits.num_swqs - 1,
			       dev->wimits.wesewved_swqs);
	if (eww)
		wetuwn eww;

	eww = mthca_awway_init(&dev->swq_tabwe.swq,
			       dev->wimits.num_swqs);
	if (eww)
		mthca_awwoc_cweanup(&dev->swq_tabwe.awwoc);

	wetuwn eww;
}

void mthca_cweanup_swq_tabwe(stwuct mthca_dev *dev)
{
	if (!(dev->mthca_fwags & MTHCA_FWAG_SWQ))
		wetuwn;

	mthca_awway_cweanup(&dev->swq_tabwe.swq, dev->wimits.num_swqs);
	mthca_awwoc_cweanup(&dev->swq_tabwe.awwoc);
}
