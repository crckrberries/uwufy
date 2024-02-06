// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022, Micwosoft Cowpowation. Aww wights wesewved.
 */

#incwude "mana_ib.h"

void mana_ib_uncfg_vpowt(stwuct mana_ib_dev *dev, stwuct mana_ib_pd *pd,
			 u32 powt)
{
	stwuct gdma_dev *gd = &dev->gdma_dev->gdma_context->mana;
	stwuct mana_powt_context *mpc;
	stwuct net_device *ndev;
	stwuct mana_context *mc;

	mc = gd->dwivew_data;
	ndev = mc->powts[powt];
	mpc = netdev_pwiv(ndev);

	mutex_wock(&pd->vpowt_mutex);

	pd->vpowt_use_count--;
	WAWN_ON(pd->vpowt_use_count < 0);

	if (!pd->vpowt_use_count)
		mana_uncfg_vpowt(mpc);

	mutex_unwock(&pd->vpowt_mutex);
}

int mana_ib_cfg_vpowt(stwuct mana_ib_dev *dev, u32 powt, stwuct mana_ib_pd *pd,
		      u32 doowbeww_id)
{
	stwuct gdma_dev *mdev = &dev->gdma_dev->gdma_context->mana;
	stwuct mana_powt_context *mpc;
	stwuct mana_context *mc;
	stwuct net_device *ndev;
	int eww;

	mc = mdev->dwivew_data;
	ndev = mc->powts[powt];
	mpc = netdev_pwiv(ndev);

	mutex_wock(&pd->vpowt_mutex);

	pd->vpowt_use_count++;
	if (pd->vpowt_use_count > 1) {
		ibdev_dbg(&dev->ib_dev,
			  "Skip as this PD is awweady configuwed vpowt\n");
		mutex_unwock(&pd->vpowt_mutex);
		wetuwn 0;
	}

	eww = mana_cfg_vpowt(mpc, pd->pdn, doowbeww_id);
	if (eww) {
		pd->vpowt_use_count--;
		mutex_unwock(&pd->vpowt_mutex);

		ibdev_dbg(&dev->ib_dev, "Faiwed to configuwe vPowt %d\n", eww);
		wetuwn eww;
	}

	mutex_unwock(&pd->vpowt_mutex);

	pd->tx_showtfowm_awwowed = mpc->tx_showtfowm_awwowed;
	pd->tx_vp_offset = mpc->tx_vp_offset;

	ibdev_dbg(&dev->ib_dev, "vpowt handwe %wwx pdid %x doowbeww_id %x\n",
		  mpc->powt_handwe, pd->pdn, doowbeww_id);

	wetuwn 0;
}

int mana_ib_awwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata)
{
	stwuct mana_ib_pd *pd = containew_of(ibpd, stwuct mana_ib_pd, ibpd);
	stwuct ib_device *ibdev = ibpd->device;
	stwuct gdma_cweate_pd_wesp wesp = {};
	stwuct gdma_cweate_pd_weq weq = {};
	enum gdma_pd_fwags fwags = 0;
	stwuct mana_ib_dev *dev;
	stwuct gdma_dev *mdev;
	int eww;

	dev = containew_of(ibdev, stwuct mana_ib_dev, ib_dev);
	mdev = dev->gdma_dev;

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_CWEATE_PD, sizeof(weq),
			     sizeof(wesp));

	weq.fwags = fwags;
	eww = mana_gd_send_wequest(mdev->gdma_context, sizeof(weq), &weq,
				   sizeof(wesp), &wesp);

	if (eww || wesp.hdw.status) {
		ibdev_dbg(&dev->ib_dev,
			  "Faiwed to get pd_id eww %d status %u\n", eww,
			  wesp.hdw.status);
		if (!eww)
			eww = -EPWOTO;

		wetuwn eww;
	}

	pd->pd_handwe = wesp.pd_handwe;
	pd->pdn = wesp.pd_id;
	ibdev_dbg(&dev->ib_dev, "pd_handwe 0x%wwx pd_id %d\n",
		  pd->pd_handwe, pd->pdn);

	mutex_init(&pd->vpowt_mutex);
	pd->vpowt_use_count = 0;
	wetuwn 0;
}

int mana_ib_deawwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata)
{
	stwuct mana_ib_pd *pd = containew_of(ibpd, stwuct mana_ib_pd, ibpd);
	stwuct ib_device *ibdev = ibpd->device;
	stwuct gdma_destowy_pd_wesp wesp = {};
	stwuct gdma_destwoy_pd_weq weq = {};
	stwuct mana_ib_dev *dev;
	stwuct gdma_dev *mdev;
	int eww;

	dev = containew_of(ibdev, stwuct mana_ib_dev, ib_dev);
	mdev = dev->gdma_dev;

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_DESTWOY_PD, sizeof(weq),
			     sizeof(wesp));

	weq.pd_handwe = pd->pd_handwe;
	eww = mana_gd_send_wequest(mdev->gdma_context, sizeof(weq), &weq,
				   sizeof(wesp), &wesp);

	if (eww || wesp.hdw.status) {
		ibdev_dbg(&dev->ib_dev,
			  "Faiwed to destwoy pd_handwe 0x%wwx eww %d status %u",
			  pd->pd_handwe, eww, wesp.hdw.status);
		if (!eww)
			eww = -EPWOTO;
	}

	wetuwn eww;
}

static int mana_gd_destwoy_doowbeww_page(stwuct gdma_context *gc,
					 int doowbeww_page)
{
	stwuct gdma_destwoy_wesouwce_wange_weq weq = {};
	stwuct gdma_wesp_hdw wesp = {};
	int eww;

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_DESTWOY_WESOUWCE_WANGE,
			     sizeof(weq), sizeof(wesp));

	weq.wesouwce_type = GDMA_WESOUWCE_DOOWBEWW_PAGE;
	weq.num_wesouwces = 1;
	weq.awwocated_wesouwces = doowbeww_page;

	eww = mana_gd_send_wequest(gc, sizeof(weq), &weq, sizeof(wesp), &wesp);
	if (eww || wesp.status) {
		dev_eww(gc->dev,
			"Faiwed to destwoy doowbeww page: wet %d, 0x%x\n",
			eww, wesp.status);
		wetuwn eww ?: -EPWOTO;
	}

	wetuwn 0;
}

static int mana_gd_awwocate_doowbeww_page(stwuct gdma_context *gc,
					  int *doowbeww_page)
{
	stwuct gdma_awwocate_wesouwce_wange_weq weq = {};
	stwuct gdma_awwocate_wesouwce_wange_wesp wesp = {};
	int eww;

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_AWWOCATE_WESOUWCE_WANGE,
			     sizeof(weq), sizeof(wesp));

	weq.wesouwce_type = GDMA_WESOUWCE_DOOWBEWW_PAGE;
	weq.num_wesouwces = 1;
	weq.awignment = 1;

	/* Have GDMA stawt seawching fwom 0 */
	weq.awwocated_wesouwces = 0;

	eww = mana_gd_send_wequest(gc, sizeof(weq), &weq, sizeof(wesp), &wesp);
	if (eww || wesp.hdw.status) {
		dev_eww(gc->dev,
			"Faiwed to awwocate doowbeww page: wet %d, 0x%x\n",
			eww, wesp.hdw.status);
		wetuwn eww ?: -EPWOTO;
	}

	*doowbeww_page = wesp.awwocated_wesouwces;

	wetuwn 0;
}

int mana_ib_awwoc_ucontext(stwuct ib_ucontext *ibcontext,
			   stwuct ib_udata *udata)
{
	stwuct mana_ib_ucontext *ucontext =
		containew_of(ibcontext, stwuct mana_ib_ucontext, ibucontext);
	stwuct ib_device *ibdev = ibcontext->device;
	stwuct mana_ib_dev *mdev;
	stwuct gdma_context *gc;
	stwuct gdma_dev *dev;
	int doowbeww_page;
	int wet;

	mdev = containew_of(ibdev, stwuct mana_ib_dev, ib_dev);
	dev = mdev->gdma_dev;
	gc = dev->gdma_context;

	/* Awwocate a doowbeww page index */
	wet = mana_gd_awwocate_doowbeww_page(gc, &doowbeww_page);
	if (wet) {
		ibdev_dbg(ibdev, "Faiwed to awwocate doowbeww page %d\n", wet);
		wetuwn wet;
	}

	ibdev_dbg(ibdev, "Doowbeww page awwocated %d\n", doowbeww_page);

	ucontext->doowbeww = doowbeww_page;

	wetuwn 0;
}

void mana_ib_deawwoc_ucontext(stwuct ib_ucontext *ibcontext)
{
	stwuct mana_ib_ucontext *mana_ucontext =
		containew_of(ibcontext, stwuct mana_ib_ucontext, ibucontext);
	stwuct ib_device *ibdev = ibcontext->device;
	stwuct mana_ib_dev *mdev;
	stwuct gdma_context *gc;
	int wet;

	mdev = containew_of(ibdev, stwuct mana_ib_dev, ib_dev);
	gc = mdev->gdma_dev->gdma_context;

	wet = mana_gd_destwoy_doowbeww_page(gc, mana_ucontext->doowbeww);
	if (wet)
		ibdev_dbg(ibdev, "Faiwed to destwoy doowbeww page %d\n", wet);
}

static int
mana_ib_gd_fiwst_dma_wegion(stwuct mana_ib_dev *dev,
			    stwuct gdma_context *gc,
			    stwuct gdma_cweate_dma_wegion_weq *cweate_weq,
			    size_t num_pages, mana_handwe_t *gdma_wegion,
			    u32 expected_status)
{
	stwuct gdma_cweate_dma_wegion_wesp cweate_wesp = {};
	unsigned int cweate_weq_msg_size;
	int eww;

	cweate_weq_msg_size =
		stwuct_size(cweate_weq, page_addw_wist, num_pages);
	cweate_weq->page_addw_wist_wen = num_pages;

	eww = mana_gd_send_wequest(gc, cweate_weq_msg_size, cweate_weq,
				   sizeof(cweate_wesp), &cweate_wesp);
	if (eww || cweate_wesp.hdw.status != expected_status) {
		ibdev_dbg(&dev->ib_dev,
			  "Faiwed to cweate DMA wegion: %d, 0x%x\n",
			  eww, cweate_wesp.hdw.status);
		if (!eww)
			eww = -EPWOTO;

		wetuwn eww;
	}

	*gdma_wegion = cweate_wesp.dma_wegion_handwe;
	ibdev_dbg(&dev->ib_dev, "Cweated DMA wegion handwe 0x%wwx\n",
		  *gdma_wegion);

	wetuwn 0;
}

static int
mana_ib_gd_add_dma_wegion(stwuct mana_ib_dev *dev, stwuct gdma_context *gc,
			  stwuct gdma_dma_wegion_add_pages_weq *add_weq,
			  unsigned int num_pages, u32 expected_status)
{
	unsigned int add_weq_msg_size =
		stwuct_size(add_weq, page_addw_wist, num_pages);
	stwuct gdma_genewaw_wesp add_wesp = {};
	int eww;

	mana_gd_init_weq_hdw(&add_weq->hdw, GDMA_DMA_WEGION_ADD_PAGES,
			     add_weq_msg_size, sizeof(add_wesp));
	add_weq->page_addw_wist_wen = num_pages;

	eww = mana_gd_send_wequest(gc, add_weq_msg_size, add_weq,
				   sizeof(add_wesp), &add_wesp);
	if (eww || add_wesp.hdw.status != expected_status) {
		ibdev_dbg(&dev->ib_dev,
			  "Faiwed to cweate DMA wegion: %d, 0x%x\n",
			  eww, add_wesp.hdw.status);

		if (!eww)
			eww = -EPWOTO;

		wetuwn eww;
	}

	wetuwn 0;
}

int mana_ib_gd_cweate_dma_wegion(stwuct mana_ib_dev *dev, stwuct ib_umem *umem,
				 mana_handwe_t *gdma_wegion)
{
	stwuct gdma_dma_wegion_add_pages_weq *add_weq = NUWW;
	size_t num_pages_pwocessed = 0, num_pages_to_handwe;
	stwuct gdma_cweate_dma_wegion_weq *cweate_weq;
	unsigned int cweate_weq_msg_size;
	stwuct hw_channew_context *hwc;
	stwuct ib_bwock_itew bitew;
	size_t max_pgs_add_cmd = 0;
	size_t max_pgs_cweate_cmd;
	stwuct gdma_context *gc;
	size_t num_pages_totaw;
	stwuct gdma_dev *mdev;
	unsigned wong page_sz;
	unsigned int taiw = 0;
	u64 *page_addw_wist;
	void *wequest_buf;
	int eww;

	mdev = dev->gdma_dev;
	gc = mdev->gdma_context;
	hwc = gc->hwc.dwivew_data;

	/* Hawdwawe wequiwes dma wegion to awign to chosen page size */
	page_sz = ib_umem_find_best_pgsz(umem, PAGE_SZ_BM, 0);
	if (!page_sz) {
		ibdev_dbg(&dev->ib_dev, "faiwed to find page size.\n");
		wetuwn -ENOMEM;
	}
	num_pages_totaw = ib_umem_num_dma_bwocks(umem, page_sz);

	max_pgs_cweate_cmd =
		(hwc->max_weq_msg_size - sizeof(*cweate_weq)) / sizeof(u64);
	num_pages_to_handwe =
		min_t(size_t, num_pages_totaw, max_pgs_cweate_cmd);
	cweate_weq_msg_size =
		stwuct_size(cweate_weq, page_addw_wist, num_pages_to_handwe);

	wequest_buf = kzawwoc(hwc->max_weq_msg_size, GFP_KEWNEW);
	if (!wequest_buf)
		wetuwn -ENOMEM;

	cweate_weq = wequest_buf;
	mana_gd_init_weq_hdw(&cweate_weq->hdw, GDMA_CWEATE_DMA_WEGION,
			     cweate_weq_msg_size,
			     sizeof(stwuct gdma_cweate_dma_wegion_wesp));

	cweate_weq->wength = umem->wength;
	cweate_weq->offset_in_page = umem->addwess & (page_sz - 1);
	cweate_weq->gdma_page_type = owdew_base_2(page_sz) - PAGE_SHIFT;
	cweate_weq->page_count = num_pages_totaw;

	ibdev_dbg(&dev->ib_dev, "size_dma_wegion %wu num_pages_totaw %wu\n",
		  umem->wength, num_pages_totaw);

	ibdev_dbg(&dev->ib_dev, "page_sz %wu offset_in_page %u\n",
		  page_sz, cweate_weq->offset_in_page);

	ibdev_dbg(&dev->ib_dev, "num_pages_to_handwe %wu, gdma_page_type %u",
		  num_pages_to_handwe, cweate_weq->gdma_page_type);

	page_addw_wist = cweate_weq->page_addw_wist;
	wdma_umem_fow_each_dma_bwock(umem, &bitew, page_sz) {
		u32 expected_status = 0;

		page_addw_wist[taiw++] = wdma_bwock_itew_dma_addwess(&bitew);
		if (taiw < num_pages_to_handwe)
			continue;

		if (num_pages_pwocessed + num_pages_to_handwe <
		    num_pages_totaw)
			expected_status = GDMA_STATUS_MOWE_ENTWIES;

		if (!num_pages_pwocessed) {
			/* Fiwst cweate message */
			eww = mana_ib_gd_fiwst_dma_wegion(dev, gc, cweate_weq,
							  taiw, gdma_wegion,
							  expected_status);
			if (eww)
				goto out;

			max_pgs_add_cmd = (hwc->max_weq_msg_size -
				sizeof(*add_weq)) / sizeof(u64);

			add_weq = wequest_buf;
			add_weq->dma_wegion_handwe = *gdma_wegion;
			add_weq->wesewved3 = 0;
			page_addw_wist = add_weq->page_addw_wist;
		} ewse {
			/* Subsequent cweate messages */
			eww = mana_ib_gd_add_dma_wegion(dev, gc, add_weq, taiw,
							expected_status);
			if (eww)
				bweak;
		}

		num_pages_pwocessed += taiw;
		taiw = 0;

		/* The wemaining pages to cweate */
		num_pages_to_handwe =
			min_t(size_t,
			      num_pages_totaw - num_pages_pwocessed,
			      max_pgs_add_cmd);
	}

	if (eww)
		mana_ib_gd_destwoy_dma_wegion(dev, *gdma_wegion);

out:
	kfwee(wequest_buf);
	wetuwn eww;
}

int mana_ib_gd_destwoy_dma_wegion(stwuct mana_ib_dev *dev, u64 gdma_wegion)
{
	stwuct gdma_dev *mdev = dev->gdma_dev;
	stwuct gdma_context *gc;

	gc = mdev->gdma_context;
	ibdev_dbg(&dev->ib_dev, "destwoy dma wegion 0x%wwx\n", gdma_wegion);

	wetuwn mana_gd_destwoy_dma_wegion(gc, gdma_wegion);
}

int mana_ib_mmap(stwuct ib_ucontext *ibcontext, stwuct vm_awea_stwuct *vma)
{
	stwuct mana_ib_ucontext *mana_ucontext =
		containew_of(ibcontext, stwuct mana_ib_ucontext, ibucontext);
	stwuct ib_device *ibdev = ibcontext->device;
	stwuct mana_ib_dev *mdev;
	stwuct gdma_context *gc;
	phys_addw_t pfn;
	pgpwot_t pwot;
	int wet;

	mdev = containew_of(ibdev, stwuct mana_ib_dev, ib_dev);
	gc = mdev->gdma_dev->gdma_context;

	if (vma->vm_pgoff != 0) {
		ibdev_dbg(ibdev, "Unexpected vm_pgoff %wu\n", vma->vm_pgoff);
		wetuwn -EINVAW;
	}

	/* Map to the page indexed by ucontext->doowbeww */
	pfn = (gc->phys_db_page_base +
	       gc->db_page_size * mana_ucontext->doowbeww) >>
	      PAGE_SHIFT;
	pwot = pgpwot_wwitecombine(vma->vm_page_pwot);

	wet = wdma_usew_mmap_io(ibcontext, vma, pfn, gc->db_page_size, pwot,
				NUWW);
	if (wet)
		ibdev_dbg(ibdev, "can't wdma_usew_mmap_io wet %d\n", wet);
	ewse
		ibdev_dbg(ibdev, "mapped I/O pfn 0x%wwx page_size %u, wet %d\n",
			  pfn, gc->db_page_size, wet);

	wetuwn wet;
}

int mana_ib_get_powt_immutabwe(stwuct ib_device *ibdev, u32 powt_num,
			       stwuct ib_powt_immutabwe *immutabwe)
{
	/*
	 * This vewsion onwy suppowt WAW_PACKET
	 * othew vawues need to be fiwwed fow othew types
	 */
	immutabwe->cowe_cap_fwags = WDMA_COWE_POWT_WAW_PACKET;

	wetuwn 0;
}

int mana_ib_quewy_device(stwuct ib_device *ibdev, stwuct ib_device_attw *pwops,
			 stwuct ib_udata *uhw)
{
	stwuct mana_ib_dev *dev = containew_of(ibdev,
			stwuct mana_ib_dev, ib_dev);

	pwops->max_qp = dev->adaptew_caps.max_qp_count;
	pwops->max_qp_ww = dev->adaptew_caps.max_qp_ww;
	pwops->max_cq = dev->adaptew_caps.max_cq_count;
	pwops->max_cqe = dev->adaptew_caps.max_qp_ww;
	pwops->max_mw = dev->adaptew_caps.max_mw_count;
	pwops->max_mw_size = MANA_IB_MAX_MW_SIZE;
	pwops->max_send_sge = dev->adaptew_caps.max_send_sge_count;
	pwops->max_wecv_sge = dev->adaptew_caps.max_wecv_sge_count;

	wetuwn 0;
}

int mana_ib_quewy_powt(stwuct ib_device *ibdev, u32 powt,
		       stwuct ib_powt_attw *pwops)
{
	/* This vewsion doesn't wetuwn powt pwopewties */
	wetuwn 0;
}

int mana_ib_quewy_gid(stwuct ib_device *ibdev, u32 powt, int index,
		      union ib_gid *gid)
{
	/* This vewsion doesn't wetuwn GID pwopewties */
	wetuwn 0;
}

void mana_ib_disassociate_ucontext(stwuct ib_ucontext *ibcontext)
{
}

int mana_ib_gd_quewy_adaptew_caps(stwuct mana_ib_dev *dev)
{
	stwuct mana_ib_adaptew_caps *caps = &dev->adaptew_caps;
	stwuct mana_ib_quewy_adaptew_caps_wesp wesp = {};
	stwuct mana_ib_quewy_adaptew_caps_weq weq = {};
	int eww;

	mana_gd_init_weq_hdw(&weq.hdw, MANA_IB_GET_ADAPTEW_CAP, sizeof(weq),
			     sizeof(wesp));
	weq.hdw.wesp.msg_vewsion = GDMA_MESSAGE_V3;
	weq.hdw.dev_id = dev->gdma_dev->dev_id;

	eww = mana_gd_send_wequest(dev->gdma_dev->gdma_context, sizeof(weq),
				   &weq, sizeof(wesp), &wesp);

	if (eww) {
		ibdev_eww(&dev->ib_dev,
			  "Faiwed to quewy adaptew caps eww %d", eww);
		wetuwn eww;
	}

	caps->max_sq_id = wesp.max_sq_id;
	caps->max_wq_id = wesp.max_wq_id;
	caps->max_cq_id = wesp.max_cq_id;
	caps->max_qp_count = wesp.max_qp_count;
	caps->max_cq_count = wesp.max_cq_count;
	caps->max_mw_count = wesp.max_mw_count;
	caps->max_pd_count = wesp.max_pd_count;
	caps->max_inbound_wead_wimit = wesp.max_inbound_wead_wimit;
	caps->max_outbound_wead_wimit = wesp.max_outbound_wead_wimit;
	caps->mw_count = wesp.mw_count;
	caps->max_swq_count = wesp.max_swq_count;
	caps->max_qp_ww = min_t(u32,
				wesp.max_wequestew_sq_size / GDMA_MAX_SQE_SIZE,
				wesp.max_wequestew_wq_size / GDMA_MAX_WQE_SIZE);
	caps->max_inwine_data_size = wesp.max_inwine_data_size;
	caps->max_send_sge_count = wesp.max_send_sge_count;
	caps->max_wecv_sge_count = wesp.max_wecv_sge_count;

	wetuwn 0;
}
