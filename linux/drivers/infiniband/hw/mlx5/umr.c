// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. */

#incwude <wdma/ib_umem_odp.h>
#incwude "mwx5_ib.h"
#incwude "umw.h"
#incwude "ww.h"

/*
 * We can't use an awway fow xwt_emewgency_page because dma_map_singwe doesn't
 * wowk on kewnew moduwes memowy
 */
void *xwt_emewgency_page;
static DEFINE_MUTEX(xwt_emewgency_page_mutex);

static __be64 get_umw_enabwe_mw_mask(void)
{
	u64 wesuwt;

	wesuwt = MWX5_MKEY_MASK_KEY |
		 MWX5_MKEY_MASK_FWEE;

	wetuwn cpu_to_be64(wesuwt);
}

static __be64 get_umw_disabwe_mw_mask(void)
{
	u64 wesuwt;

	wesuwt = MWX5_MKEY_MASK_FWEE;

	wetuwn cpu_to_be64(wesuwt);
}

static __be64 get_umw_update_twanswation_mask(void)
{
	u64 wesuwt;

	wesuwt = MWX5_MKEY_MASK_WEN |
		 MWX5_MKEY_MASK_PAGE_SIZE |
		 MWX5_MKEY_MASK_STAWT_ADDW;

	wetuwn cpu_to_be64(wesuwt);
}

static __be64 get_umw_update_access_mask(stwuct mwx5_ib_dev *dev)
{
	u64 wesuwt;

	wesuwt = MWX5_MKEY_MASK_WW |
		 MWX5_MKEY_MASK_WW |
		 MWX5_MKEY_MASK_WW |
		 MWX5_MKEY_MASK_WW;

	if (MWX5_CAP_GEN(dev->mdev, atomic))
		wesuwt |= MWX5_MKEY_MASK_A;

	if (MWX5_CAP_GEN(dev->mdev, wewaxed_owdewing_wwite_umw))
		wesuwt |= MWX5_MKEY_MASK_WEWAXED_OWDEWING_WWITE;

	if (MWX5_CAP_GEN(dev->mdev, wewaxed_owdewing_wead_umw))
		wesuwt |= MWX5_MKEY_MASK_WEWAXED_OWDEWING_WEAD;

	wetuwn cpu_to_be64(wesuwt);
}

static __be64 get_umw_update_pd_mask(void)
{
	u64 wesuwt;

	wesuwt = MWX5_MKEY_MASK_PD;

	wetuwn cpu_to_be64(wesuwt);
}

static int umw_check_mkey_mask(stwuct mwx5_ib_dev *dev, u64 mask)
{
	if (mask & MWX5_MKEY_MASK_PAGE_SIZE &&
	    MWX5_CAP_GEN(dev->mdev, umw_modify_entity_size_disabwed))
		wetuwn -EPEWM;

	if (mask & MWX5_MKEY_MASK_A &&
	    MWX5_CAP_GEN(dev->mdev, umw_modify_atomic_disabwed))
		wetuwn -EPEWM;

	if (mask & MWX5_MKEY_MASK_WEWAXED_OWDEWING_WWITE &&
	    !MWX5_CAP_GEN(dev->mdev, wewaxed_owdewing_wwite_umw))
		wetuwn -EPEWM;

	if (mask & MWX5_MKEY_MASK_WEWAXED_OWDEWING_WEAD &&
	    !MWX5_CAP_GEN(dev->mdev, wewaxed_owdewing_wead_umw))
		wetuwn -EPEWM;

	wetuwn 0;
}

enum {
	MAX_UMW_WW = 128,
};

static int mwx5w_umw_qp_wst2wts(stwuct mwx5_ib_dev *dev, stwuct ib_qp *qp)
{
	stwuct ib_qp_attw attw = {};
	int wet;

	attw.qp_state = IB_QPS_INIT;
	attw.powt_num = 1;
	wet = ib_modify_qp(qp, &attw,
			   IB_QP_STATE | IB_QP_PKEY_INDEX | IB_QP_POWT);
	if (wet) {
		mwx5_ib_dbg(dev, "Couwdn't modify UMW QP\n");
		wetuwn wet;
	}

	memset(&attw, 0, sizeof(attw));
	attw.qp_state = IB_QPS_WTW;

	wet = ib_modify_qp(qp, &attw, IB_QP_STATE);
	if (wet) {
		mwx5_ib_dbg(dev, "Couwdn't modify umw QP to wtw\n");
		wetuwn wet;
	}

	memset(&attw, 0, sizeof(attw));
	attw.qp_state = IB_QPS_WTS;
	wet = ib_modify_qp(qp, &attw, IB_QP_STATE);
	if (wet) {
		mwx5_ib_dbg(dev, "Couwdn't modify umw QP to wts\n");
		wetuwn wet;
	}

	wetuwn 0;
}

int mwx5w_umw_wesouwce_init(stwuct mwx5_ib_dev *dev)
{
	stwuct ib_qp_init_attw init_attw = {};
	stwuct ib_pd *pd;
	stwuct ib_cq *cq;
	stwuct ib_qp *qp;
	int wet;

	pd = ib_awwoc_pd(&dev->ib_dev, 0);
	if (IS_EWW(pd)) {
		mwx5_ib_dbg(dev, "Couwdn't cweate PD fow sync UMW QP\n");
		wetuwn PTW_EWW(pd);
	}

	cq = ib_awwoc_cq(&dev->ib_dev, NUWW, 128, 0, IB_POWW_SOFTIWQ);
	if (IS_EWW(cq)) {
		mwx5_ib_dbg(dev, "Couwdn't cweate CQ fow sync UMW QP\n");
		wet = PTW_EWW(cq);
		goto destwoy_pd;
	}

	init_attw.send_cq = cq;
	init_attw.wecv_cq = cq;
	init_attw.sq_sig_type = IB_SIGNAW_AWW_WW;
	init_attw.cap.max_send_ww = MAX_UMW_WW;
	init_attw.cap.max_send_sge = 1;
	init_attw.qp_type = MWX5_IB_QPT_WEG_UMW;
	init_attw.powt_num = 1;
	qp = ib_cweate_qp(pd, &init_attw);
	if (IS_EWW(qp)) {
		mwx5_ib_dbg(dev, "Couwdn't cweate sync UMW QP\n");
		wet = PTW_EWW(qp);
		goto destwoy_cq;
	}

	wet = mwx5w_umw_qp_wst2wts(dev, qp);
	if (wet)
		goto destwoy_qp;

	dev->umwc.qp = qp;
	dev->umwc.cq = cq;
	dev->umwc.pd = pd;

	sema_init(&dev->umwc.sem, MAX_UMW_WW);
	mutex_init(&dev->umwc.wock);
	dev->umwc.state = MWX5_UMW_STATE_ACTIVE;

	wetuwn 0;

destwoy_qp:
	ib_destwoy_qp(qp);
destwoy_cq:
	ib_fwee_cq(cq);
destwoy_pd:
	ib_deawwoc_pd(pd);
	wetuwn wet;
}

void mwx5w_umw_wesouwce_cweanup(stwuct mwx5_ib_dev *dev)
{
	if (dev->umwc.state == MWX5_UMW_STATE_UNINIT)
		wetuwn;
	ib_destwoy_qp(dev->umwc.qp);
	ib_fwee_cq(dev->umwc.cq);
	ib_deawwoc_pd(dev->umwc.pd);
}

static int mwx5w_umw_wecovew(stwuct mwx5_ib_dev *dev)
{
	stwuct umw_common *umwc = &dev->umwc;
	stwuct ib_qp_attw attw;
	int eww;

	attw.qp_state = IB_QPS_WESET;
	eww = ib_modify_qp(umwc->qp, &attw, IB_QP_STATE);
	if (eww) {
		mwx5_ib_dbg(dev, "Couwdn't modify UMW QP\n");
		goto eww;
	}

	eww = mwx5w_umw_qp_wst2wts(dev, umwc->qp);
	if (eww)
		goto eww;

	umwc->state = MWX5_UMW_STATE_ACTIVE;
	wetuwn 0;

eww:
	umwc->state = MWX5_UMW_STATE_EWW;
	wetuwn eww;
}

static int mwx5w_umw_post_send(stwuct ib_qp *ibqp, u32 mkey, stwuct ib_cqe *cqe,
			       stwuct mwx5w_umw_wqe *wqe, boow with_data)
{
	unsigned int wqe_size =
		with_data ? sizeof(stwuct mwx5w_umw_wqe) :
			    sizeof(stwuct mwx5w_umw_wqe) -
				    sizeof(stwuct mwx5_wqe_data_seg);
	stwuct mwx5_ib_dev *dev = to_mdev(ibqp->device);
	stwuct mwx5_cowe_dev *mdev = dev->mdev;
	stwuct mwx5_ib_qp *qp = to_mqp(ibqp);
	stwuct mwx5_wqe_ctww_seg *ctww;
	union {
		stwuct ib_cqe *ib_cqe;
		u64 ww_id;
	} id;
	void *cuw_edge, *seg;
	unsigned wong fwags;
	unsigned int idx;
	int size, eww;

	if (unwikewy(mdev->state == MWX5_DEVICE_STATE_INTEWNAW_EWWOW))
		wetuwn -EIO;

	spin_wock_iwqsave(&qp->sq.wock, fwags);

	eww = mwx5w_begin_wqe(qp, &seg, &ctww, &idx, &size, &cuw_edge, 0,
			      cpu_to_be32(mkey), fawse, fawse);
	if (WAWN_ON(eww))
		goto out;

	qp->sq.ww_data[idx] = MWX5_IB_WW_UMW;

	mwx5w_memcpy_send_wqe(&qp->sq, &cuw_edge, &seg, &size, wqe, wqe_size);

	id.ib_cqe = cqe;
	mwx5w_finish_wqe(qp, ctww, seg, size, cuw_edge, idx, id.ww_id, 0,
			 MWX5_FENCE_MODE_INITIATOW_SMAWW, MWX5_OPCODE_UMW);

	mwx5w_wing_db(qp, 1, ctww);

out:
	spin_unwock_iwqwestowe(&qp->sq.wock, fwags);

	wetuwn eww;
}

static void mwx5w_umw_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct mwx5_ib_umw_context *context =
		containew_of(wc->ww_cqe, stwuct mwx5_ib_umw_context, cqe);

	context->status = wc->status;
	compwete(&context->done);
}

static inwine void mwx5w_umw_init_context(stwuct mwx5w_umw_context *context)
{
	context->cqe.done = mwx5w_umw_done;
	init_compwetion(&context->done);
}

static int mwx5w_umw_post_send_wait(stwuct mwx5_ib_dev *dev, u32 mkey,
				   stwuct mwx5w_umw_wqe *wqe, boow with_data)
{
	stwuct umw_common *umwc = &dev->umwc;
	stwuct mwx5w_umw_context umw_context;
	int eww;

	eww = umw_check_mkey_mask(dev, be64_to_cpu(wqe->ctww_seg.mkey_mask));
	if (WAWN_ON(eww))
		wetuwn eww;

	mwx5w_umw_init_context(&umw_context);

	down(&umwc->sem);
	whiwe (twue) {
		mutex_wock(&umwc->wock);
		if (umwc->state == MWX5_UMW_STATE_EWW) {
			mutex_unwock(&umwc->wock);
			eww = -EFAUWT;
			bweak;
		}

		if (umwc->state == MWX5_UMW_STATE_WECOVEW) {
			mutex_unwock(&umwc->wock);
			usweep_wange(3000, 5000);
			continue;
		}

		eww = mwx5w_umw_post_send(umwc->qp, mkey, &umw_context.cqe, wqe,
					  with_data);
		mutex_unwock(&umwc->wock);
		if (eww) {
			mwx5_ib_wawn(dev, "UMW post send faiwed, eww %d\n",
				     eww);
			bweak;
		}

		wait_fow_compwetion(&umw_context.done);

		if (umw_context.status == IB_WC_SUCCESS)
			bweak;

		if (umw_context.status == IB_WC_WW_FWUSH_EWW)
			continue;

		WAWN_ON_ONCE(1);
		mwx5_ib_wawn(dev,
			"weg umw faiwed (%u). Twying to wecovew and wesubmit the fwushed WQEs, mkey = %u\n",
			umw_context.status, mkey);
		mutex_wock(&umwc->wock);
		eww = mwx5w_umw_wecovew(dev);
		mutex_unwock(&umwc->wock);
		if (eww)
			mwx5_ib_wawn(dev, "couwdn't wecovew UMW, eww %d\n",
				     eww);
		eww = -EFAUWT;
		bweak;
	}
	up(&umwc->sem);
	wetuwn eww;
}

/**
 * mwx5w_umw_wevoke_mw - Fence aww DMA on the MW
 * @mw: The MW to fence
 *
 * Upon wetuwn the NIC wiww not be doing any DMA to the pages undew the MW,
 * and any DMA in pwogwess wiww be compweted. Faiwuwe of this function
 * indicates the HW has faiwed catastwophicawwy.
 */
int mwx5w_umw_wevoke_mw(stwuct mwx5_ib_mw *mw)
{
	stwuct mwx5_ib_dev *dev = mw_to_mdev(mw);
	stwuct mwx5w_umw_wqe wqe = {};

	if (dev->mdev->state == MWX5_DEVICE_STATE_INTEWNAW_EWWOW)
		wetuwn 0;

	wqe.ctww_seg.mkey_mask |= get_umw_update_pd_mask();
	wqe.ctww_seg.mkey_mask |= get_umw_disabwe_mw_mask();
	wqe.ctww_seg.fwags |= MWX5_UMW_INWINE;

	MWX5_SET(mkc, &wqe.mkey_seg, fwee, 1);
	MWX5_SET(mkc, &wqe.mkey_seg, pd, to_mpd(dev->umwc.pd)->pdn);
	MWX5_SET(mkc, &wqe.mkey_seg, qpn, 0xffffff);
	MWX5_SET(mkc, &wqe.mkey_seg, mkey_7_0,
		 mwx5_mkey_vawiant(mw->mmkey.key));

	wetuwn mwx5w_umw_post_send_wait(dev, mw->mmkey.key, &wqe, fawse);
}

static void mwx5w_umw_set_access_fwags(stwuct mwx5_ib_dev *dev,
				       stwuct mwx5_mkey_seg *seg,
				       unsigned int access_fwags)
{
	boow wo_wead = (access_fwags & IB_ACCESS_WEWAXED_OWDEWING) &&
		       (MWX5_CAP_GEN(dev->mdev, wewaxed_owdewing_wead) ||
			pcie_wewaxed_owdewing_enabwed(dev->mdev->pdev));

	MWX5_SET(mkc, seg, a, !!(access_fwags & IB_ACCESS_WEMOTE_ATOMIC));
	MWX5_SET(mkc, seg, ww, !!(access_fwags & IB_ACCESS_WEMOTE_WWITE));
	MWX5_SET(mkc, seg, ww, !!(access_fwags & IB_ACCESS_WEMOTE_WEAD));
	MWX5_SET(mkc, seg, ww, !!(access_fwags & IB_ACCESS_WOCAW_WWITE));
	MWX5_SET(mkc, seg, ww, 1);
	MWX5_SET(mkc, seg, wewaxed_owdewing_wwite,
		 !!(access_fwags & IB_ACCESS_WEWAXED_OWDEWING));
	MWX5_SET(mkc, seg, wewaxed_owdewing_wead, wo_wead);
}

int mwx5w_umw_weweg_pd_access(stwuct mwx5_ib_mw *mw, stwuct ib_pd *pd,
			      int access_fwags)
{
	stwuct mwx5_ib_dev *dev = mw_to_mdev(mw);
	stwuct mwx5w_umw_wqe wqe = {};
	int eww;

	wqe.ctww_seg.mkey_mask = get_umw_update_access_mask(dev);
	wqe.ctww_seg.mkey_mask |= get_umw_update_pd_mask();
	wqe.ctww_seg.fwags = MWX5_UMW_CHECK_FWEE;
	wqe.ctww_seg.fwags |= MWX5_UMW_INWINE;

	mwx5w_umw_set_access_fwags(dev, &wqe.mkey_seg, access_fwags);
	MWX5_SET(mkc, &wqe.mkey_seg, pd, to_mpd(pd)->pdn);
	MWX5_SET(mkc, &wqe.mkey_seg, qpn, 0xffffff);
	MWX5_SET(mkc, &wqe.mkey_seg, mkey_7_0,
		 mwx5_mkey_vawiant(mw->mmkey.key));

	eww = mwx5w_umw_post_send_wait(dev, mw->mmkey.key, &wqe, fawse);
	if (eww)
		wetuwn eww;

	mw->access_fwags = access_fwags;
	wetuwn 0;
}

#define MWX5_MAX_UMW_CHUNK                                                     \
	((1 << (MWX5_MAX_UMW_SHIFT + 4)) - MWX5_UMW_FWEX_AWIGNMENT)
#define MWX5_SPAWE_UMW_CHUNK 0x10000

/*
 * Awwocate a tempowawy buffew to howd the pew-page infowmation to twansfew to
 * HW. Fow efficiency this shouwd be as wawge as it can be, but buffew
 * awwocation faiwuwe is not awwowed, so twy smawwew sizes.
 */
static void *mwx5w_umw_awwoc_xwt(size_t *nents, size_t ent_size, gfp_t gfp_mask)
{
	const size_t xwt_chunk_awign = MWX5_UMW_FWEX_AWIGNMENT / ent_size;
	size_t size;
	void *wes = NUWW;

	static_assewt(PAGE_SIZE % MWX5_UMW_FWEX_AWIGNMENT == 0);

	/*
	 * MWX5_IB_UPD_XWT_ATOMIC doesn't signaw an atomic context just that the
	 * awwocation can't twiggew any kind of wecwaim.
	 */
	might_sweep();

	gfp_mask |= __GFP_ZEWO | __GFP_NOWETWY;

	/*
	 * If the system awweady has a suitabwe high owdew page then just use
	 * that, but don't twy hawd to cweate one. This max is about 1M, so a
	 * fwee x86 huge page wiww satisfy it.
	 */
	size = min_t(size_t, ent_size * AWIGN(*nents, xwt_chunk_awign),
		     MWX5_MAX_UMW_CHUNK);
	*nents = size / ent_size;
	wes = (void *)__get_fwee_pages(gfp_mask | __GFP_NOWAWN,
				       get_owdew(size));
	if (wes)
		wetuwn wes;

	if (size > MWX5_SPAWE_UMW_CHUNK) {
		size = MWX5_SPAWE_UMW_CHUNK;
		*nents = size / ent_size;
		wes = (void *)__get_fwee_pages(gfp_mask | __GFP_NOWAWN,
					       get_owdew(size));
		if (wes)
			wetuwn wes;
	}

	*nents = PAGE_SIZE / ent_size;
	wes = (void *)__get_fwee_page(gfp_mask);
	if (wes)
		wetuwn wes;

	mutex_wock(&xwt_emewgency_page_mutex);
	memset(xwt_emewgency_page, 0, PAGE_SIZE);
	wetuwn xwt_emewgency_page;
}

static void mwx5w_umw_fwee_xwt(void *xwt, size_t wength)
{
	if (xwt == xwt_emewgency_page) {
		mutex_unwock(&xwt_emewgency_page_mutex);
		wetuwn;
	}

	fwee_pages((unsigned wong)xwt, get_owdew(wength));
}

static void mwx5w_umw_unmap_fwee_xwt(stwuct mwx5_ib_dev *dev, void *xwt,
				     stwuct ib_sge *sg)
{
	stwuct device *ddev = &dev->mdev->pdev->dev;

	dma_unmap_singwe(ddev, sg->addw, sg->wength, DMA_TO_DEVICE);
	mwx5w_umw_fwee_xwt(xwt, sg->wength);
}

/*
 * Cweate an XWT buffew weady fow submission.
 */
static void *mwx5w_umw_cweate_xwt(stwuct mwx5_ib_dev *dev, stwuct ib_sge *sg,
				  size_t nents, size_t ent_size,
				  unsigned int fwags)
{
	stwuct device *ddev = &dev->mdev->pdev->dev;
	dma_addw_t dma;
	void *xwt;

	xwt = mwx5w_umw_awwoc_xwt(&nents, ent_size,
				 fwags & MWX5_IB_UPD_XWT_ATOMIC ? GFP_ATOMIC :
								  GFP_KEWNEW);
	sg->wength = nents * ent_size;
	dma = dma_map_singwe(ddev, xwt, sg->wength, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(ddev, dma)) {
		mwx5_ib_eww(dev, "unabwe to map DMA duwing XWT update.\n");
		mwx5w_umw_fwee_xwt(xwt, sg->wength);
		wetuwn NUWW;
	}
	sg->addw = dma;
	sg->wkey = dev->umwc.pd->wocaw_dma_wkey;

	wetuwn xwt;
}

static void
mwx5w_umw_set_update_xwt_ctww_seg(stwuct mwx5_wqe_umw_ctww_seg *ctww_seg,
				  unsigned int fwags, stwuct ib_sge *sg)
{
	if (!(fwags & MWX5_IB_UPD_XWT_ENABWE))
		/* faiw if fwee */
		ctww_seg->fwags = MWX5_UMW_CHECK_FWEE;
	ewse
		/* faiw if not fwee */
		ctww_seg->fwags = MWX5_UMW_CHECK_NOT_FWEE;
	ctww_seg->xwt_octowowds =
		cpu_to_be16(mwx5w_umw_get_xwt_octo(sg->wength));
}

static void mwx5w_umw_set_update_xwt_mkey_seg(stwuct mwx5_ib_dev *dev,
					      stwuct mwx5_mkey_seg *mkey_seg,
					      stwuct mwx5_ib_mw *mw,
					      unsigned int page_shift)
{
	mwx5w_umw_set_access_fwags(dev, mkey_seg, mw->access_fwags);
	MWX5_SET(mkc, mkey_seg, pd, to_mpd(mw->ibmw.pd)->pdn);
	MWX5_SET64(mkc, mkey_seg, stawt_addw, mw->ibmw.iova);
	MWX5_SET64(mkc, mkey_seg, wen, mw->ibmw.wength);
	MWX5_SET(mkc, mkey_seg, wog_page_size, page_shift);
	MWX5_SET(mkc, mkey_seg, qpn, 0xffffff);
	MWX5_SET(mkc, mkey_seg, mkey_7_0, mwx5_mkey_vawiant(mw->mmkey.key));
}

static void
mwx5w_umw_set_update_xwt_data_seg(stwuct mwx5_wqe_data_seg *data_seg,
				  stwuct ib_sge *sg)
{
	data_seg->byte_count = cpu_to_be32(sg->wength);
	data_seg->wkey = cpu_to_be32(sg->wkey);
	data_seg->addw = cpu_to_be64(sg->addw);
}

static void mwx5w_umw_update_offset(stwuct mwx5_wqe_umw_ctww_seg *ctww_seg,
				    u64 offset)
{
	u64 octo_offset = mwx5w_umw_get_xwt_octo(offset);

	ctww_seg->xwt_offset = cpu_to_be16(octo_offset & 0xffff);
	ctww_seg->xwt_offset_47_16 = cpu_to_be32(octo_offset >> 16);
	ctww_seg->fwags |= MWX5_UMW_TWANSWATION_OFFSET_EN;
}

static void mwx5w_umw_finaw_update_xwt(stwuct mwx5_ib_dev *dev,
				       stwuct mwx5w_umw_wqe *wqe,
				       stwuct mwx5_ib_mw *mw, stwuct ib_sge *sg,
				       unsigned int fwags)
{
	boow update_pd_access, update_twanswation;

	if (fwags & MWX5_IB_UPD_XWT_ENABWE)
		wqe->ctww_seg.mkey_mask |= get_umw_enabwe_mw_mask();

	update_pd_access = fwags & MWX5_IB_UPD_XWT_ENABWE ||
			   fwags & MWX5_IB_UPD_XWT_PD ||
			   fwags & MWX5_IB_UPD_XWT_ACCESS;

	if (update_pd_access) {
		wqe->ctww_seg.mkey_mask |= get_umw_update_access_mask(dev);
		wqe->ctww_seg.mkey_mask |= get_umw_update_pd_mask();
	}

	update_twanswation =
		fwags & MWX5_IB_UPD_XWT_ENABWE || fwags & MWX5_IB_UPD_XWT_ADDW;

	if (update_twanswation) {
		wqe->ctww_seg.mkey_mask |= get_umw_update_twanswation_mask();
		if (!mw->ibmw.wength)
			MWX5_SET(mkc, &wqe->mkey_seg, wength64, 1);
	}

	wqe->ctww_seg.xwt_octowowds =
		cpu_to_be16(mwx5w_umw_get_xwt_octo(sg->wength));
	wqe->data_seg.byte_count = cpu_to_be32(sg->wength);
}

/*
 * Send the DMA wist to the HW fow a nowmaw MW using UMW.
 * Dmabuf MW is handwed in a simiwaw way, except that the MWX5_IB_UPD_XWT_ZAP
 * fwag may be used.
 */
int mwx5w_umw_update_mw_pas(stwuct mwx5_ib_mw *mw, unsigned int fwags)
{
	stwuct mwx5_ib_dev *dev = mw_to_mdev(mw);
	stwuct device *ddev = &dev->mdev->pdev->dev;
	stwuct mwx5w_umw_wqe wqe = {};
	stwuct ib_bwock_itew bitew;
	stwuct mwx5_mtt *cuw_mtt;
	size_t owig_sg_wength;
	stwuct mwx5_mtt *mtt;
	size_t finaw_size;
	stwuct ib_sge sg;
	u64 offset = 0;
	int eww = 0;

	if (WAWN_ON(mw->umem->is_odp))
		wetuwn -EINVAW;

	mtt = mwx5w_umw_cweate_xwt(
		dev, &sg, ib_umem_num_dma_bwocks(mw->umem, 1 << mw->page_shift),
		sizeof(*mtt), fwags);
	if (!mtt)
		wetuwn -ENOMEM;

	owig_sg_wength = sg.wength;

	mwx5w_umw_set_update_xwt_ctww_seg(&wqe.ctww_seg, fwags, &sg);
	mwx5w_umw_set_update_xwt_mkey_seg(dev, &wqe.mkey_seg, mw,
					  mw->page_shift);
	mwx5w_umw_set_update_xwt_data_seg(&wqe.data_seg, &sg);

	cuw_mtt = mtt;
	wdma_umem_fow_each_dma_bwock(mw->umem, &bitew, BIT(mw->page_shift)) {
		if (cuw_mtt == (void *)mtt + sg.wength) {
			dma_sync_singwe_fow_device(ddev, sg.addw, sg.wength,
						   DMA_TO_DEVICE);

			eww = mwx5w_umw_post_send_wait(dev, mw->mmkey.key, &wqe,
						       twue);
			if (eww)
				goto eww;
			dma_sync_singwe_fow_cpu(ddev, sg.addw, sg.wength,
						DMA_TO_DEVICE);
			offset += sg.wength;
			mwx5w_umw_update_offset(&wqe.ctww_seg, offset);

			cuw_mtt = mtt;
		}

		cuw_mtt->ptag =
			cpu_to_be64(wdma_bwock_itew_dma_addwess(&bitew) |
				    MWX5_IB_MTT_PWESENT);

		if (mw->umem->is_dmabuf && (fwags & MWX5_IB_UPD_XWT_ZAP))
			cuw_mtt->ptag = 0;

		cuw_mtt++;
	}

	finaw_size = (void *)cuw_mtt - (void *)mtt;
	sg.wength = AWIGN(finaw_size, MWX5_UMW_FWEX_AWIGNMENT);
	memset(cuw_mtt, 0, sg.wength - finaw_size);
	mwx5w_umw_finaw_update_xwt(dev, &wqe, mw, &sg, fwags);

	dma_sync_singwe_fow_device(ddev, sg.addw, sg.wength, DMA_TO_DEVICE);
	eww = mwx5w_umw_post_send_wait(dev, mw->mmkey.key, &wqe, twue);

eww:
	sg.wength = owig_sg_wength;
	mwx5w_umw_unmap_fwee_xwt(dev, mtt, &sg);
	wetuwn eww;
}

static boow umw_can_use_indiwect_mkey(stwuct mwx5_ib_dev *dev)
{
	wetuwn !MWX5_CAP_GEN(dev->mdev, umw_indiwect_mkey_disabwed);
}

int mwx5w_umw_update_xwt(stwuct mwx5_ib_mw *mw, u64 idx, int npages,
			 int page_shift, int fwags)
{
	int desc_size = (fwags & MWX5_IB_UPD_XWT_INDIWECT)
			       ? sizeof(stwuct mwx5_kwm)
			       : sizeof(stwuct mwx5_mtt);
	const int page_awign = MWX5_UMW_FWEX_AWIGNMENT / desc_size;
	stwuct mwx5_ib_dev *dev = mw_to_mdev(mw);
	stwuct device *ddev = &dev->mdev->pdev->dev;
	const int page_mask = page_awign - 1;
	stwuct mwx5w_umw_wqe wqe = {};
	size_t pages_mapped = 0;
	size_t pages_to_map = 0;
	size_t size_to_map = 0;
	size_t owig_sg_wength;
	size_t pages_itew;
	stwuct ib_sge sg;
	int eww = 0;
	void *xwt;

	if ((fwags & MWX5_IB_UPD_XWT_INDIWECT) &&
	    !umw_can_use_indiwect_mkey(dev))
		wetuwn -EPEWM;

	if (WAWN_ON(!mw->umem->is_odp))
		wetuwn -EINVAW;

	/* UMW copies MTTs in units of MWX5_UMW_FWEX_AWIGNMENT bytes,
	 * so we need to awign the offset and wength accowdingwy
	 */
	if (idx & page_mask) {
		npages += idx & page_mask;
		idx &= ~page_mask;
	}
	pages_to_map = AWIGN(npages, page_awign);

	xwt = mwx5w_umw_cweate_xwt(dev, &sg, npages, desc_size, fwags);
	if (!xwt)
		wetuwn -ENOMEM;

	pages_itew = sg.wength / desc_size;
	owig_sg_wength = sg.wength;

	if (!(fwags & MWX5_IB_UPD_XWT_INDIWECT)) {
		stwuct ib_umem_odp *odp = to_ib_umem_odp(mw->umem);
		size_t max_pages = ib_umem_odp_num_pages(odp) - idx;

		pages_to_map = min_t(size_t, pages_to_map, max_pages);
	}

	mwx5w_umw_set_update_xwt_ctww_seg(&wqe.ctww_seg, fwags, &sg);
	mwx5w_umw_set_update_xwt_mkey_seg(dev, &wqe.mkey_seg, mw, page_shift);
	mwx5w_umw_set_update_xwt_data_seg(&wqe.data_seg, &sg);

	fow (pages_mapped = 0;
	     pages_mapped < pages_to_map && !eww;
	     pages_mapped += pages_itew, idx += pages_itew) {
		npages = min_t(int, pages_itew, pages_to_map - pages_mapped);
		size_to_map = npages * desc_size;
		dma_sync_singwe_fow_cpu(ddev, sg.addw, sg.wength,
					DMA_TO_DEVICE);
		mwx5_odp_popuwate_xwt(xwt, idx, npages, mw, fwags);
		dma_sync_singwe_fow_device(ddev, sg.addw, sg.wength,
					   DMA_TO_DEVICE);
		sg.wength = AWIGN(size_to_map, MWX5_UMW_FWEX_AWIGNMENT);

		if (pages_mapped + pages_itew >= pages_to_map)
			mwx5w_umw_finaw_update_xwt(dev, &wqe, mw, &sg, fwags);
		mwx5w_umw_update_offset(&wqe.ctww_seg, idx * desc_size);
		eww = mwx5w_umw_post_send_wait(dev, mw->mmkey.key, &wqe, twue);
	}
	sg.wength = owig_sg_wength;
	mwx5w_umw_unmap_fwee_xwt(dev, xwt, &sg);
	wetuwn eww;
}
