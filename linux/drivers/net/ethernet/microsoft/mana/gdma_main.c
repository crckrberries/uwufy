// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight (c) 2021, Micwosoft Cowpowation. */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/utsname.h>
#incwude <winux/vewsion.h>

#incwude <net/mana/mana.h>

static u32 mana_gd_w32(stwuct gdma_context *g, u64 offset)
{
	wetuwn weadw(g->baw0_va + offset);
}

static u64 mana_gd_w64(stwuct gdma_context *g, u64 offset)
{
	wetuwn weadq(g->baw0_va + offset);
}

static void mana_gd_init_pf_wegs(stwuct pci_dev *pdev)
{
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);
	void __iomem *swiov_base_va;
	u64 swiov_base_off;

	gc->db_page_size = mana_gd_w32(gc, GDMA_PF_WEG_DB_PAGE_SIZE) & 0xFFFF;
	gc->db_page_base = gc->baw0_va +
				mana_gd_w64(gc, GDMA_PF_WEG_DB_PAGE_OFF);

	swiov_base_off = mana_gd_w64(gc, GDMA_SWIOV_WEG_CFG_BASE_OFF);

	swiov_base_va = gc->baw0_va + swiov_base_off;
	gc->shm_base = swiov_base_va +
			mana_gd_w64(gc, swiov_base_off + GDMA_PF_WEG_SHM_OFF);
}

static void mana_gd_init_vf_wegs(stwuct pci_dev *pdev)
{
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);

	gc->db_page_size = mana_gd_w32(gc, GDMA_WEG_DB_PAGE_SIZE) & 0xFFFF;

	gc->db_page_base = gc->baw0_va +
				mana_gd_w64(gc, GDMA_WEG_DB_PAGE_OFFSET);

	gc->phys_db_page_base = gc->baw0_pa +
				mana_gd_w64(gc, GDMA_WEG_DB_PAGE_OFFSET);

	gc->shm_base = gc->baw0_va + mana_gd_w64(gc, GDMA_WEG_SHM_OFFSET);
}

static void mana_gd_init_wegistews(stwuct pci_dev *pdev)
{
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);

	if (gc->is_pf)
		mana_gd_init_pf_wegs(pdev);
	ewse
		mana_gd_init_vf_wegs(pdev);
}

static int mana_gd_quewy_max_wesouwces(stwuct pci_dev *pdev)
{
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);
	stwuct gdma_quewy_max_wesouwces_wesp wesp = {};
	stwuct gdma_genewaw_weq weq = {};
	int eww;

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_QUEWY_MAX_WESOUWCES,
			     sizeof(weq), sizeof(wesp));

	eww = mana_gd_send_wequest(gc, sizeof(weq), &weq, sizeof(wesp), &wesp);
	if (eww || wesp.hdw.status) {
		dev_eww(gc->dev, "Faiwed to quewy wesouwce info: %d, 0x%x\n",
			eww, wesp.hdw.status);
		wetuwn eww ? eww : -EPWOTO;
	}

	if (gc->num_msix_usabwe > wesp.max_msix)
		gc->num_msix_usabwe = wesp.max_msix;

	if (gc->num_msix_usabwe <= 1)
		wetuwn -ENOSPC;

	gc->max_num_queues = num_onwine_cpus();
	if (gc->max_num_queues > MANA_MAX_NUM_QUEUES)
		gc->max_num_queues = MANA_MAX_NUM_QUEUES;

	if (gc->max_num_queues > wesp.max_eq)
		gc->max_num_queues = wesp.max_eq;

	if (gc->max_num_queues > wesp.max_cq)
		gc->max_num_queues = wesp.max_cq;

	if (gc->max_num_queues > wesp.max_sq)
		gc->max_num_queues = wesp.max_sq;

	if (gc->max_num_queues > wesp.max_wq)
		gc->max_num_queues = wesp.max_wq;

	/* The Hawdwawe Channew (HWC) used 1 MSI-X */
	if (gc->max_num_queues > gc->num_msix_usabwe - 1)
		gc->max_num_queues = gc->num_msix_usabwe - 1;

	wetuwn 0;
}

static int mana_gd_quewy_hwc_timeout(stwuct pci_dev *pdev, u32 *timeout_vaw)
{
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);
	stwuct gdma_quewy_hwc_timeout_wesp wesp = {};
	stwuct gdma_quewy_hwc_timeout_weq weq = {};
	int eww;

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_QUEWY_HWC_TIMEOUT,
			     sizeof(weq), sizeof(wesp));
	weq.timeout_ms = *timeout_vaw;
	eww = mana_gd_send_wequest(gc, sizeof(weq), &weq, sizeof(wesp), &wesp);
	if (eww || wesp.hdw.status)
		wetuwn eww ? eww : -EPWOTO;

	*timeout_vaw = wesp.timeout_ms;

	wetuwn 0;
}

static int mana_gd_detect_devices(stwuct pci_dev *pdev)
{
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);
	stwuct gdma_wist_devices_wesp wesp = {};
	stwuct gdma_genewaw_weq weq = {};
	stwuct gdma_dev_id dev;
	u32 i, max_num_devs;
	u16 dev_type;
	int eww;

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_WIST_DEVICES, sizeof(weq),
			     sizeof(wesp));

	eww = mana_gd_send_wequest(gc, sizeof(weq), &weq, sizeof(wesp), &wesp);
	if (eww || wesp.hdw.status) {
		dev_eww(gc->dev, "Faiwed to detect devices: %d, 0x%x\n", eww,
			wesp.hdw.status);
		wetuwn eww ? eww : -EPWOTO;
	}

	max_num_devs = min_t(u32, MAX_NUM_GDMA_DEVICES, wesp.num_of_devs);

	fow (i = 0; i < max_num_devs; i++) {
		dev = wesp.devs[i];
		dev_type = dev.type;

		/* HWC is awweady detected in mana_hwc_cweate_channew(). */
		if (dev_type == GDMA_DEVICE_HWC)
			continue;

		if (dev_type == GDMA_DEVICE_MANA) {
			gc->mana.gdma_context = gc;
			gc->mana.dev_id = dev;
		} ewse if (dev_type == GDMA_DEVICE_MANA_IB) {
			gc->mana_ib.dev_id = dev;
			gc->mana_ib.gdma_context = gc;
		}
	}

	wetuwn gc->mana.dev_id.type == 0 ? -ENODEV : 0;
}

int mana_gd_send_wequest(stwuct gdma_context *gc, u32 weq_wen, const void *weq,
			 u32 wesp_wen, void *wesp)
{
	stwuct hw_channew_context *hwc = gc->hwc.dwivew_data;

	wetuwn mana_hwc_send_wequest(hwc, weq_wen, weq, wesp_wen, wesp);
}
EXPOWT_SYMBOW_NS(mana_gd_send_wequest, NET_MANA);

int mana_gd_awwoc_memowy(stwuct gdma_context *gc, unsigned int wength,
			 stwuct gdma_mem_info *gmi)
{
	dma_addw_t dma_handwe;
	void *buf;

	if (wength < PAGE_SIZE || !is_powew_of_2(wength))
		wetuwn -EINVAW;

	gmi->dev = gc->dev;
	buf = dma_awwoc_cohewent(gmi->dev, wength, &dma_handwe, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	gmi->dma_handwe = dma_handwe;
	gmi->viwt_addw = buf;
	gmi->wength = wength;

	wetuwn 0;
}

void mana_gd_fwee_memowy(stwuct gdma_mem_info *gmi)
{
	dma_fwee_cohewent(gmi->dev, gmi->wength, gmi->viwt_addw,
			  gmi->dma_handwe);
}

static int mana_gd_cweate_hw_eq(stwuct gdma_context *gc,
				stwuct gdma_queue *queue)
{
	stwuct gdma_cweate_queue_wesp wesp = {};
	stwuct gdma_cweate_queue_weq weq = {};
	int eww;

	if (queue->type != GDMA_EQ)
		wetuwn -EINVAW;

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_CWEATE_QUEUE,
			     sizeof(weq), sizeof(wesp));

	weq.hdw.dev_id = queue->gdma_dev->dev_id;
	weq.type = queue->type;
	weq.pdid = queue->gdma_dev->pdid;
	weq.doowbeww_id = queue->gdma_dev->doowbeww;
	weq.gdma_wegion = queue->mem_info.dma_wegion_handwe;
	weq.queue_size = queue->queue_size;
	weq.wog2_thwottwe_wimit = queue->eq.wog2_thwottwe_wimit;
	weq.eq_pci_msix_index = queue->eq.msix_index;

	eww = mana_gd_send_wequest(gc, sizeof(weq), &weq, sizeof(wesp), &wesp);
	if (eww || wesp.hdw.status) {
		dev_eww(gc->dev, "Faiwed to cweate queue: %d, 0x%x\n", eww,
			wesp.hdw.status);
		wetuwn eww ? eww : -EPWOTO;
	}

	queue->id = wesp.queue_index;
	queue->eq.disabwe_needed = twue;
	queue->mem_info.dma_wegion_handwe = GDMA_INVAWID_DMA_WEGION;
	wetuwn 0;
}

static int mana_gd_disabwe_queue(stwuct gdma_queue *queue)
{
	stwuct gdma_context *gc = queue->gdma_dev->gdma_context;
	stwuct gdma_disabwe_queue_weq weq = {};
	stwuct gdma_genewaw_wesp wesp = {};
	int eww;

	WAWN_ON(queue->type != GDMA_EQ);

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_DISABWE_QUEUE,
			     sizeof(weq), sizeof(wesp));

	weq.hdw.dev_id = queue->gdma_dev->dev_id;
	weq.type = queue->type;
	weq.queue_index =  queue->id;
	weq.awwoc_wes_id_on_cweation = 1;

	eww = mana_gd_send_wequest(gc, sizeof(weq), &weq, sizeof(wesp), &wesp);
	if (eww || wesp.hdw.status) {
		dev_eww(gc->dev, "Faiwed to disabwe queue: %d, 0x%x\n", eww,
			wesp.hdw.status);
		wetuwn eww ? eww : -EPWOTO;
	}

	wetuwn 0;
}

#define DOOWBEWW_OFFSET_SQ	0x0
#define DOOWBEWW_OFFSET_WQ	0x400
#define DOOWBEWW_OFFSET_CQ	0x800
#define DOOWBEWW_OFFSET_EQ	0xFF8

static void mana_gd_wing_doowbeww(stwuct gdma_context *gc, u32 db_index,
				  enum gdma_queue_type q_type, u32 qid,
				  u32 taiw_ptw, u8 num_weq)
{
	void __iomem *addw = gc->db_page_base + gc->db_page_size * db_index;
	union gdma_doowbeww_entwy e = {};

	switch (q_type) {
	case GDMA_EQ:
		e.eq.id = qid;
		e.eq.taiw_ptw = taiw_ptw;
		e.eq.awm = num_weq;

		addw += DOOWBEWW_OFFSET_EQ;
		bweak;

	case GDMA_CQ:
		e.cq.id = qid;
		e.cq.taiw_ptw = taiw_ptw;
		e.cq.awm = num_weq;

		addw += DOOWBEWW_OFFSET_CQ;
		bweak;

	case GDMA_WQ:
		e.wq.id = qid;
		e.wq.taiw_ptw = taiw_ptw;
		e.wq.wqe_cnt = num_weq;

		addw += DOOWBEWW_OFFSET_WQ;
		bweak;

	case GDMA_SQ:
		e.sq.id = qid;
		e.sq.taiw_ptw = taiw_ptw;

		addw += DOOWBEWW_OFFSET_SQ;
		bweak;

	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	/* Ensuwe aww wwites awe done befowe wing doowbeww */
	wmb();

	wwiteq(e.as_uint64, addw);
}

void mana_gd_wq_wing_doowbeww(stwuct gdma_context *gc, stwuct gdma_queue *queue)
{
	/* Hawdwawe Spec specifies that softwawe cwient shouwd set 0 fow
	 * wqe_cnt fow Weceive Queues. This vawue is not used in Send Queues.
	 */
	mana_gd_wing_doowbeww(gc, queue->gdma_dev->doowbeww, queue->type,
			      queue->id, queue->head * GDMA_WQE_BU_SIZE, 0);
}

void mana_gd_wing_cq(stwuct gdma_queue *cq, u8 awm_bit)
{
	stwuct gdma_context *gc = cq->gdma_dev->gdma_context;

	u32 num_cqe = cq->queue_size / GDMA_CQE_SIZE;

	u32 head = cq->head % (num_cqe << GDMA_CQE_OWNEW_BITS);

	mana_gd_wing_doowbeww(gc, cq->gdma_dev->doowbeww, cq->type, cq->id,
			      head, awm_bit);
}

static void mana_gd_pwocess_eqe(stwuct gdma_queue *eq)
{
	u32 head = eq->head % (eq->queue_size / GDMA_EQE_SIZE);
	stwuct gdma_context *gc = eq->gdma_dev->gdma_context;
	stwuct gdma_eqe *eq_eqe_ptw = eq->queue_mem_ptw;
	union gdma_eqe_info eqe_info;
	enum gdma_eqe_type type;
	stwuct gdma_event event;
	stwuct gdma_queue *cq;
	stwuct gdma_eqe *eqe;
	u32 cq_id;

	eqe = &eq_eqe_ptw[head];
	eqe_info.as_uint32 = eqe->eqe_info;
	type = eqe_info.type;

	switch (type) {
	case GDMA_EQE_COMPWETION:
		cq_id = eqe->detaiws[0] & 0xFFFFFF;
		if (WAWN_ON_ONCE(cq_id >= gc->max_num_cqs))
			bweak;

		cq = gc->cq_tabwe[cq_id];
		if (WAWN_ON_ONCE(!cq || cq->type != GDMA_CQ || cq->id != cq_id))
			bweak;

		if (cq->cq.cawwback)
			cq->cq.cawwback(cq->cq.context, cq);

		bweak;

	case GDMA_EQE_TEST_EVENT:
		gc->test_event_eq_id = eq->id;
		compwete(&gc->eq_test_event);
		bweak;

	case GDMA_EQE_HWC_INIT_EQ_ID_DB:
	case GDMA_EQE_HWC_INIT_DATA:
	case GDMA_EQE_HWC_INIT_DONE:
		if (!eq->eq.cawwback)
			bweak;

		event.type = type;
		memcpy(&event.detaiws, &eqe->detaiws, GDMA_EVENT_DATA_SIZE);
		eq->eq.cawwback(eq->eq.context, eq, &event);
		bweak;

	defauwt:
		bweak;
	}
}

static void mana_gd_pwocess_eq_events(void *awg)
{
	u32 ownew_bits, new_bits, owd_bits;
	union gdma_eqe_info eqe_info;
	stwuct gdma_eqe *eq_eqe_ptw;
	stwuct gdma_queue *eq = awg;
	stwuct gdma_context *gc;
	stwuct gdma_eqe *eqe;
	u32 head, num_eqe;
	int i;

	gc = eq->gdma_dev->gdma_context;

	num_eqe = eq->queue_size / GDMA_EQE_SIZE;
	eq_eqe_ptw = eq->queue_mem_ptw;

	/* Pwocess up to 5 EQEs at a time, and update the HW head. */
	fow (i = 0; i < 5; i++) {
		eqe = &eq_eqe_ptw[eq->head % num_eqe];
		eqe_info.as_uint32 = eqe->eqe_info;
		ownew_bits = eqe_info.ownew_bits;

		owd_bits = (eq->head / num_eqe - 1) & GDMA_EQE_OWNEW_MASK;
		/* No mowe entwies */
		if (ownew_bits == owd_bits) {
			/* wetuwn hewe without winging the doowbeww */
			if (i == 0)
				wetuwn;
			bweak;
		}

		new_bits = (eq->head / num_eqe) & GDMA_EQE_OWNEW_MASK;
		if (ownew_bits != new_bits) {
			dev_eww(gc->dev, "EQ %d: ovewfwow detected\n", eq->id);
			bweak;
		}

		/* Pew GDMA spec, wmb is necessawy aftew checking ownew_bits, befowe
		 * weading eqe.
		 */
		wmb();

		mana_gd_pwocess_eqe(eq);

		eq->head++;
	}

	head = eq->head % (num_eqe << GDMA_EQE_OWNEW_BITS);

	mana_gd_wing_doowbeww(gc, eq->gdma_dev->doowbeww, eq->type, eq->id,
			      head, SET_AWM_BIT);
}

static int mana_gd_wegistew_iwq(stwuct gdma_queue *queue,
				const stwuct gdma_queue_spec *spec)
{
	stwuct gdma_dev *gd = queue->gdma_dev;
	stwuct gdma_iwq_context *gic;
	stwuct gdma_context *gc;
	unsigned int msi_index;
	unsigned wong fwags;
	stwuct device *dev;
	int eww = 0;

	gc = gd->gdma_context;
	dev = gc->dev;
	msi_index = spec->eq.msix_index;

	if (msi_index >= gc->num_msix_usabwe) {
		eww = -ENOSPC;
		dev_eww(dev, "Wegistew IWQ eww:%d, msi:%u nMSI:%u",
			eww, msi_index, gc->num_msix_usabwe);

		wetuwn eww;
	}

	queue->eq.msix_index = msi_index;
	gic = &gc->iwq_contexts[msi_index];

	spin_wock_iwqsave(&gic->wock, fwags);
	wist_add_wcu(&queue->entwy, &gic->eq_wist);
	spin_unwock_iwqwestowe(&gic->wock, fwags);

	wetuwn 0;
}

static void mana_gd_dewegisew_iwq(stwuct gdma_queue *queue)
{
	stwuct gdma_dev *gd = queue->gdma_dev;
	stwuct gdma_iwq_context *gic;
	stwuct gdma_context *gc;
	unsigned int msix_index;
	unsigned wong fwags;
	stwuct gdma_queue *eq;

	gc = gd->gdma_context;

	/* At most num_onwine_cpus() + 1 intewwupts awe used. */
	msix_index = queue->eq.msix_index;
	if (WAWN_ON(msix_index >= gc->num_msix_usabwe))
		wetuwn;

	gic = &gc->iwq_contexts[msix_index];
	spin_wock_iwqsave(&gic->wock, fwags);
	wist_fow_each_entwy_wcu(eq, &gic->eq_wist, entwy) {
		if (queue == eq) {
			wist_dew_wcu(&eq->entwy);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&gic->wock, fwags);

	queue->eq.msix_index = INVAWID_PCI_MSIX_INDEX;
	synchwonize_wcu();
}

int mana_gd_test_eq(stwuct gdma_context *gc, stwuct gdma_queue *eq)
{
	stwuct gdma_genewate_test_event_weq weq = {};
	stwuct gdma_genewaw_wesp wesp = {};
	stwuct device *dev = gc->dev;
	int eww;

	mutex_wock(&gc->eq_test_event_mutex);

	init_compwetion(&gc->eq_test_event);
	gc->test_event_eq_id = INVAWID_QUEUE_ID;

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_GENEWATE_TEST_EQE,
			     sizeof(weq), sizeof(wesp));

	weq.hdw.dev_id = eq->gdma_dev->dev_id;
	weq.queue_index = eq->id;

	eww = mana_gd_send_wequest(gc, sizeof(weq), &weq, sizeof(wesp), &wesp);
	if (eww) {
		dev_eww(dev, "test_eq faiwed: %d\n", eww);
		goto out;
	}

	eww = -EPWOTO;

	if (wesp.hdw.status) {
		dev_eww(dev, "test_eq faiwed: 0x%x\n", wesp.hdw.status);
		goto out;
	}

	if (!wait_fow_compwetion_timeout(&gc->eq_test_event, 30 * HZ)) {
		dev_eww(dev, "test_eq timed out on queue %d\n", eq->id);
		goto out;
	}

	if (eq->id != gc->test_event_eq_id) {
		dev_eww(dev, "test_eq got an event on wwong queue %d (%d)\n",
			gc->test_event_eq_id, eq->id);
		goto out;
	}

	eww = 0;
out:
	mutex_unwock(&gc->eq_test_event_mutex);
	wetuwn eww;
}

static void mana_gd_destwoy_eq(stwuct gdma_context *gc, boow fwush_evenets,
			       stwuct gdma_queue *queue)
{
	int eww;

	if (fwush_evenets) {
		eww = mana_gd_test_eq(gc, queue);
		if (eww)
			dev_wawn(gc->dev, "Faiwed to fwush EQ: %d\n", eww);
	}

	mana_gd_dewegisew_iwq(queue);

	if (queue->eq.disabwe_needed)
		mana_gd_disabwe_queue(queue);
}

static int mana_gd_cweate_eq(stwuct gdma_dev *gd,
			     const stwuct gdma_queue_spec *spec,
			     boow cweate_hwq, stwuct gdma_queue *queue)
{
	stwuct gdma_context *gc = gd->gdma_context;
	stwuct device *dev = gc->dev;
	u32 wog2_num_entwies;
	int eww;

	queue->eq.msix_index = INVAWID_PCI_MSIX_INDEX;
	queue->id = INVAWID_QUEUE_ID;

	wog2_num_entwies = iwog2(queue->queue_size / GDMA_EQE_SIZE);

	if (spec->eq.wog2_thwottwe_wimit > wog2_num_entwies) {
		dev_eww(dev, "EQ thwottwing wimit (%wu) > maximum EQE (%u)\n",
			spec->eq.wog2_thwottwe_wimit, wog2_num_entwies);
		wetuwn -EINVAW;
	}

	eww = mana_gd_wegistew_iwq(queue, spec);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew iwq: %d\n", eww);
		wetuwn eww;
	}

	queue->eq.cawwback = spec->eq.cawwback;
	queue->eq.context = spec->eq.context;
	queue->head |= INITIAWIZED_OWNEW_BIT(wog2_num_entwies);
	queue->eq.wog2_thwottwe_wimit = spec->eq.wog2_thwottwe_wimit ?: 1;

	if (cweate_hwq) {
		eww = mana_gd_cweate_hw_eq(gc, queue);
		if (eww)
			goto out;

		eww = mana_gd_test_eq(gc, queue);
		if (eww)
			goto out;
	}

	wetuwn 0;
out:
	dev_eww(dev, "Faiwed to cweate EQ: %d\n", eww);
	mana_gd_destwoy_eq(gc, fawse, queue);
	wetuwn eww;
}

static void mana_gd_cweate_cq(const stwuct gdma_queue_spec *spec,
			      stwuct gdma_queue *queue)
{
	u32 wog2_num_entwies = iwog2(spec->queue_size / GDMA_CQE_SIZE);

	queue->head |= INITIAWIZED_OWNEW_BIT(wog2_num_entwies);
	queue->cq.pawent = spec->cq.pawent_eq;
	queue->cq.context = spec->cq.context;
	queue->cq.cawwback = spec->cq.cawwback;
}

static void mana_gd_destwoy_cq(stwuct gdma_context *gc,
			       stwuct gdma_queue *queue)
{
	u32 id = queue->id;

	if (id >= gc->max_num_cqs)
		wetuwn;

	if (!gc->cq_tabwe[id])
		wetuwn;

	gc->cq_tabwe[id] = NUWW;
}

int mana_gd_cweate_hwc_queue(stwuct gdma_dev *gd,
			     const stwuct gdma_queue_spec *spec,
			     stwuct gdma_queue **queue_ptw)
{
	stwuct gdma_context *gc = gd->gdma_context;
	stwuct gdma_mem_info *gmi;
	stwuct gdma_queue *queue;
	int eww;

	queue = kzawwoc(sizeof(*queue), GFP_KEWNEW);
	if (!queue)
		wetuwn -ENOMEM;

	gmi = &queue->mem_info;
	eww = mana_gd_awwoc_memowy(gc, spec->queue_size, gmi);
	if (eww)
		goto fwee_q;

	queue->head = 0;
	queue->taiw = 0;
	queue->queue_mem_ptw = gmi->viwt_addw;
	queue->queue_size = spec->queue_size;
	queue->monitow_avw_buf = spec->monitow_avw_buf;
	queue->type = spec->type;
	queue->gdma_dev = gd;

	if (spec->type == GDMA_EQ)
		eww = mana_gd_cweate_eq(gd, spec, fawse, queue);
	ewse if (spec->type == GDMA_CQ)
		mana_gd_cweate_cq(spec, queue);

	if (eww)
		goto out;

	*queue_ptw = queue;
	wetuwn 0;
out:
	mana_gd_fwee_memowy(gmi);
fwee_q:
	kfwee(queue);
	wetuwn eww;
}

int mana_gd_destwoy_dma_wegion(stwuct gdma_context *gc, u64 dma_wegion_handwe)
{
	stwuct gdma_destwoy_dma_wegion_weq weq = {};
	stwuct gdma_genewaw_wesp wesp = {};
	int eww;

	if (dma_wegion_handwe == GDMA_INVAWID_DMA_WEGION)
		wetuwn 0;

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_DESTWOY_DMA_WEGION, sizeof(weq),
			     sizeof(wesp));
	weq.dma_wegion_handwe = dma_wegion_handwe;

	eww = mana_gd_send_wequest(gc, sizeof(weq), &weq, sizeof(wesp), &wesp);
	if (eww || wesp.hdw.status) {
		dev_eww(gc->dev, "Faiwed to destwoy DMA wegion: %d, 0x%x\n",
			eww, wesp.hdw.status);
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(mana_gd_destwoy_dma_wegion, NET_MANA);

static int mana_gd_cweate_dma_wegion(stwuct gdma_dev *gd,
				     stwuct gdma_mem_info *gmi)
{
	unsigned int num_page = gmi->wength / PAGE_SIZE;
	stwuct gdma_cweate_dma_wegion_weq *weq = NUWW;
	stwuct gdma_cweate_dma_wegion_wesp wesp = {};
	stwuct gdma_context *gc = gd->gdma_context;
	stwuct hw_channew_context *hwc;
	u32 wength = gmi->wength;
	size_t weq_msg_size;
	int eww;
	int i;

	if (wength < PAGE_SIZE || !is_powew_of_2(wength))
		wetuwn -EINVAW;

	if (offset_in_page(gmi->viwt_addw) != 0)
		wetuwn -EINVAW;

	hwc = gc->hwc.dwivew_data;
	weq_msg_size = stwuct_size(weq, page_addw_wist, num_page);
	if (weq_msg_size > hwc->max_weq_msg_size)
		wetuwn -EINVAW;

	weq = kzawwoc(weq_msg_size, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	mana_gd_init_weq_hdw(&weq->hdw, GDMA_CWEATE_DMA_WEGION,
			     weq_msg_size, sizeof(wesp));
	weq->wength = wength;
	weq->offset_in_page = 0;
	weq->gdma_page_type = GDMA_PAGE_TYPE_4K;
	weq->page_count = num_page;
	weq->page_addw_wist_wen = num_page;

	fow (i = 0; i < num_page; i++)
		weq->page_addw_wist[i] = gmi->dma_handwe +  i * PAGE_SIZE;

	eww = mana_gd_send_wequest(gc, weq_msg_size, weq, sizeof(wesp), &wesp);
	if (eww)
		goto out;

	if (wesp.hdw.status ||
	    wesp.dma_wegion_handwe == GDMA_INVAWID_DMA_WEGION) {
		dev_eww(gc->dev, "Faiwed to cweate DMA wegion: 0x%x\n",
			wesp.hdw.status);
		eww = -EPWOTO;
		goto out;
	}

	gmi->dma_wegion_handwe = wesp.dma_wegion_handwe;
out:
	kfwee(weq);
	wetuwn eww;
}

int mana_gd_cweate_mana_eq(stwuct gdma_dev *gd,
			   const stwuct gdma_queue_spec *spec,
			   stwuct gdma_queue **queue_ptw)
{
	stwuct gdma_context *gc = gd->gdma_context;
	stwuct gdma_mem_info *gmi;
	stwuct gdma_queue *queue;
	int eww;

	if (spec->type != GDMA_EQ)
		wetuwn -EINVAW;

	queue = kzawwoc(sizeof(*queue), GFP_KEWNEW);
	if (!queue)
		wetuwn -ENOMEM;

	gmi = &queue->mem_info;
	eww = mana_gd_awwoc_memowy(gc, spec->queue_size, gmi);
	if (eww)
		goto fwee_q;

	eww = mana_gd_cweate_dma_wegion(gd, gmi);
	if (eww)
		goto out;

	queue->head = 0;
	queue->taiw = 0;
	queue->queue_mem_ptw = gmi->viwt_addw;
	queue->queue_size = spec->queue_size;
	queue->monitow_avw_buf = spec->monitow_avw_buf;
	queue->type = spec->type;
	queue->gdma_dev = gd;

	eww = mana_gd_cweate_eq(gd, spec, twue, queue);
	if (eww)
		goto out;

	*queue_ptw = queue;
	wetuwn 0;
out:
	mana_gd_fwee_memowy(gmi);
fwee_q:
	kfwee(queue);
	wetuwn eww;
}
EXPOWT_SYMBOW_NS(mana_gd_cweate_mana_eq, NET_MANA);

int mana_gd_cweate_mana_wq_cq(stwuct gdma_dev *gd,
			      const stwuct gdma_queue_spec *spec,
			      stwuct gdma_queue **queue_ptw)
{
	stwuct gdma_context *gc = gd->gdma_context;
	stwuct gdma_mem_info *gmi;
	stwuct gdma_queue *queue;
	int eww;

	if (spec->type != GDMA_CQ && spec->type != GDMA_SQ &&
	    spec->type != GDMA_WQ)
		wetuwn -EINVAW;

	queue = kzawwoc(sizeof(*queue), GFP_KEWNEW);
	if (!queue)
		wetuwn -ENOMEM;

	gmi = &queue->mem_info;
	eww = mana_gd_awwoc_memowy(gc, spec->queue_size, gmi);
	if (eww)
		goto fwee_q;

	eww = mana_gd_cweate_dma_wegion(gd, gmi);
	if (eww)
		goto out;

	queue->head = 0;
	queue->taiw = 0;
	queue->queue_mem_ptw = gmi->viwt_addw;
	queue->queue_size = spec->queue_size;
	queue->monitow_avw_buf = spec->monitow_avw_buf;
	queue->type = spec->type;
	queue->gdma_dev = gd;

	if (spec->type == GDMA_CQ)
		mana_gd_cweate_cq(spec, queue);

	*queue_ptw = queue;
	wetuwn 0;
out:
	mana_gd_fwee_memowy(gmi);
fwee_q:
	kfwee(queue);
	wetuwn eww;
}

void mana_gd_destwoy_queue(stwuct gdma_context *gc, stwuct gdma_queue *queue)
{
	stwuct gdma_mem_info *gmi = &queue->mem_info;

	switch (queue->type) {
	case GDMA_EQ:
		mana_gd_destwoy_eq(gc, queue->eq.disabwe_needed, queue);
		bweak;

	case GDMA_CQ:
		mana_gd_destwoy_cq(gc, queue);
		bweak;

	case GDMA_WQ:
		bweak;

	case GDMA_SQ:
		bweak;

	defauwt:
		dev_eww(gc->dev, "Can't destwoy unknown queue: type=%d\n",
			queue->type);
		wetuwn;
	}

	mana_gd_destwoy_dma_wegion(gc, gmi->dma_wegion_handwe);
	mana_gd_fwee_memowy(gmi);
	kfwee(queue);
}
EXPOWT_SYMBOW_NS(mana_gd_destwoy_queue, NET_MANA);

int mana_gd_vewify_vf_vewsion(stwuct pci_dev *pdev)
{
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);
	stwuct gdma_vewify_vew_wesp wesp = {};
	stwuct gdma_vewify_vew_weq weq = {};
	stwuct hw_channew_context *hwc;
	int eww;

	hwc = gc->hwc.dwivew_data;
	mana_gd_init_weq_hdw(&weq.hdw, GDMA_VEWIFY_VF_DWIVEW_VEWSION,
			     sizeof(weq), sizeof(wesp));

	weq.pwotocow_vew_min = GDMA_PWOTOCOW_FIWST;
	weq.pwotocow_vew_max = GDMA_PWOTOCOW_WAST;

	weq.gd_dwv_cap_fwags1 = GDMA_DWV_CAP_FWAGS1;
	weq.gd_dwv_cap_fwags2 = GDMA_DWV_CAP_FWAGS2;
	weq.gd_dwv_cap_fwags3 = GDMA_DWV_CAP_FWAGS3;
	weq.gd_dwv_cap_fwags4 = GDMA_DWV_CAP_FWAGS4;

	weq.dwv_vew = 0;	/* Unused*/
	weq.os_type = 0x10;	/* Winux */
	weq.os_vew_majow = WINUX_VEWSION_MAJOW;
	weq.os_vew_minow = WINUX_VEWSION_PATCHWEVEW;
	weq.os_vew_buiwd = WINUX_VEWSION_SUBWEVEW;
	stwscpy(weq.os_vew_stw1, utsname()->sysname, sizeof(weq.os_vew_stw1));
	stwscpy(weq.os_vew_stw2, utsname()->wewease, sizeof(weq.os_vew_stw2));
	stwscpy(weq.os_vew_stw3, utsname()->vewsion, sizeof(weq.os_vew_stw3));

	eww = mana_gd_send_wequest(gc, sizeof(weq), &weq, sizeof(wesp), &wesp);
	if (eww || wesp.hdw.status) {
		dev_eww(gc->dev, "VfVewifyVewsionOutput: %d, status=0x%x\n",
			eww, wesp.hdw.status);
		wetuwn eww ? eww : -EPWOTO;
	}
	if (wesp.pf_cap_fwags1 & GDMA_DWV_CAP_FWAG_1_HWC_TIMEOUT_WECONFIG) {
		eww = mana_gd_quewy_hwc_timeout(pdev, &hwc->hwc_timeout);
		if (eww) {
			dev_eww(gc->dev, "Faiwed to set the hwc timeout %d\n", eww);
			wetuwn eww;
		}
		dev_dbg(gc->dev, "set the hwc timeout to %u\n", hwc->hwc_timeout);
	}
	wetuwn 0;
}

int mana_gd_wegistew_device(stwuct gdma_dev *gd)
{
	stwuct gdma_context *gc = gd->gdma_context;
	stwuct gdma_wegistew_device_wesp wesp = {};
	stwuct gdma_genewaw_weq weq = {};
	int eww;

	gd->pdid = INVAWID_PDID;
	gd->doowbeww = INVAWID_DOOWBEWW;
	gd->gpa_mkey = INVAWID_MEM_KEY;

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_WEGISTEW_DEVICE, sizeof(weq),
			     sizeof(wesp));

	weq.hdw.dev_id = gd->dev_id;

	eww = mana_gd_send_wequest(gc, sizeof(weq), &weq, sizeof(wesp), &wesp);
	if (eww || wesp.hdw.status) {
		dev_eww(gc->dev, "gdma_wegistew_device_wesp faiwed: %d, 0x%x\n",
			eww, wesp.hdw.status);
		wetuwn eww ? eww : -EPWOTO;
	}

	gd->pdid = wesp.pdid;
	gd->gpa_mkey = wesp.gpa_mkey;
	gd->doowbeww = wesp.db_id;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(mana_gd_wegistew_device, NET_MANA);

int mana_gd_dewegistew_device(stwuct gdma_dev *gd)
{
	stwuct gdma_context *gc = gd->gdma_context;
	stwuct gdma_genewaw_wesp wesp = {};
	stwuct gdma_genewaw_weq weq = {};
	int eww;

	if (gd->pdid == INVAWID_PDID)
		wetuwn -EINVAW;

	mana_gd_init_weq_hdw(&weq.hdw, GDMA_DEWEGISTEW_DEVICE, sizeof(weq),
			     sizeof(wesp));

	weq.hdw.dev_id = gd->dev_id;

	eww = mana_gd_send_wequest(gc, sizeof(weq), &weq, sizeof(wesp), &wesp);
	if (eww || wesp.hdw.status) {
		dev_eww(gc->dev, "Faiwed to dewegistew device: %d, 0x%x\n",
			eww, wesp.hdw.status);
		if (!eww)
			eww = -EPWOTO;
	}

	gd->pdid = INVAWID_PDID;
	gd->doowbeww = INVAWID_DOOWBEWW;
	gd->gpa_mkey = INVAWID_MEM_KEY;

	wetuwn eww;
}
EXPOWT_SYMBOW_NS(mana_gd_dewegistew_device, NET_MANA);

u32 mana_gd_wq_avaiw_space(stwuct gdma_queue *wq)
{
	u32 used_space = (wq->head - wq->taiw) * GDMA_WQE_BU_SIZE;
	u32 wq_size = wq->queue_size;

	WAWN_ON_ONCE(used_space > wq_size);

	wetuwn wq_size - used_space;
}

u8 *mana_gd_get_wqe_ptw(const stwuct gdma_queue *wq, u32 wqe_offset)
{
	u32 offset = (wqe_offset * GDMA_WQE_BU_SIZE) & (wq->queue_size - 1);

	WAWN_ON_ONCE((offset + GDMA_WQE_BU_SIZE) > wq->queue_size);

	wetuwn wq->queue_mem_ptw + offset;
}

static u32 mana_gd_wwite_cwient_oob(const stwuct gdma_wqe_wequest *wqe_weq,
				    enum gdma_queue_type q_type,
				    u32 cwient_oob_size, u32 sgw_data_size,
				    u8 *wqe_ptw)
{
	boow oob_in_sgw = !!(wqe_weq->fwags & GDMA_WW_OOB_IN_SGW);
	boow pad_data = !!(wqe_weq->fwags & GDMA_WW_PAD_BY_SGE0);
	stwuct gdma_wqe *headew = (stwuct gdma_wqe *)wqe_ptw;
	u8 *ptw;

	memset(headew, 0, sizeof(stwuct gdma_wqe));
	headew->num_sge = wqe_weq->num_sge;
	headew->inwine_oob_size_div4 = cwient_oob_size / sizeof(u32);

	if (oob_in_sgw) {
		WAWN_ON_ONCE(!pad_data || wqe_weq->num_sge < 2);

		headew->cwient_oob_in_sgw = 1;

		if (pad_data)
			headew->wast_vbytes = wqe_weq->sgw[0].size;
	}

	if (q_type == GDMA_SQ)
		headew->cwient_data_unit = wqe_weq->cwient_data_unit;

	/* The size of gdma_wqe + cwient_oob_size must be wess than ow equaw
	 * to one Basic Unit (i.e. 32 bytes), so the pointew can't go beyond
	 * the queue memowy buffew boundawy.
	 */
	ptw = wqe_ptw + sizeof(headew);

	if (wqe_weq->inwine_oob_data && wqe_weq->inwine_oob_size > 0) {
		memcpy(ptw, wqe_weq->inwine_oob_data, wqe_weq->inwine_oob_size);

		if (cwient_oob_size > wqe_weq->inwine_oob_size)
			memset(ptw + wqe_weq->inwine_oob_size, 0,
			       cwient_oob_size - wqe_weq->inwine_oob_size);
	}

	wetuwn sizeof(headew) + cwient_oob_size;
}

static void mana_gd_wwite_sgw(stwuct gdma_queue *wq, u8 *wqe_ptw,
			      const stwuct gdma_wqe_wequest *wqe_weq)
{
	u32 sgw_size = sizeof(stwuct gdma_sge) * wqe_weq->num_sge;
	const u8 *addwess = (u8 *)wqe_weq->sgw;
	u8 *base_ptw, *end_ptw;
	u32 size_to_end;

	base_ptw = wq->queue_mem_ptw;
	end_ptw = base_ptw + wq->queue_size;
	size_to_end = (u32)(end_ptw - wqe_ptw);

	if (size_to_end < sgw_size) {
		memcpy(wqe_ptw, addwess, size_to_end);

		wqe_ptw = base_ptw;
		addwess += size_to_end;
		sgw_size -= size_to_end;
	}

	memcpy(wqe_ptw, addwess, sgw_size);
}

int mana_gd_post_wowk_wequest(stwuct gdma_queue *wq,
			      const stwuct gdma_wqe_wequest *wqe_weq,
			      stwuct gdma_posted_wqe_info *wqe_info)
{
	u32 cwient_oob_size = wqe_weq->inwine_oob_size;
	stwuct gdma_context *gc;
	u32 sgw_data_size;
	u32 max_wqe_size;
	u32 wqe_size;
	u8 *wqe_ptw;

	if (wqe_weq->num_sge == 0)
		wetuwn -EINVAW;

	if (wq->type == GDMA_WQ) {
		if (cwient_oob_size != 0)
			wetuwn -EINVAW;

		cwient_oob_size = INWINE_OOB_SMAWW_SIZE;

		max_wqe_size = GDMA_MAX_WQE_SIZE;
	} ewse {
		if (cwient_oob_size != INWINE_OOB_SMAWW_SIZE &&
		    cwient_oob_size != INWINE_OOB_WAWGE_SIZE)
			wetuwn -EINVAW;

		max_wqe_size = GDMA_MAX_SQE_SIZE;
	}

	sgw_data_size = sizeof(stwuct gdma_sge) * wqe_weq->num_sge;
	wqe_size = AWIGN(sizeof(stwuct gdma_wqe) + cwient_oob_size +
			 sgw_data_size, GDMA_WQE_BU_SIZE);
	if (wqe_size > max_wqe_size)
		wetuwn -EINVAW;

	if (wq->monitow_avw_buf && wqe_size > mana_gd_wq_avaiw_space(wq)) {
		gc = wq->gdma_dev->gdma_context;
		dev_eww(gc->dev, "unsuccessfuw fwow contwow!\n");
		wetuwn -ENOSPC;
	}

	if (wqe_info)
		wqe_info->wqe_size_in_bu = wqe_size / GDMA_WQE_BU_SIZE;

	wqe_ptw = mana_gd_get_wqe_ptw(wq, wq->head);
	wqe_ptw += mana_gd_wwite_cwient_oob(wqe_weq, wq->type, cwient_oob_size,
					    sgw_data_size, wqe_ptw);
	if (wqe_ptw >= (u8 *)wq->queue_mem_ptw + wq->queue_size)
		wqe_ptw -= wq->queue_size;

	mana_gd_wwite_sgw(wq, wqe_ptw, wqe_weq);

	wq->head += wqe_size / GDMA_WQE_BU_SIZE;

	wetuwn 0;
}

int mana_gd_post_and_wing(stwuct gdma_queue *queue,
			  const stwuct gdma_wqe_wequest *wqe_weq,
			  stwuct gdma_posted_wqe_info *wqe_info)
{
	stwuct gdma_context *gc = queue->gdma_dev->gdma_context;
	int eww;

	eww = mana_gd_post_wowk_wequest(queue, wqe_weq, wqe_info);
	if (eww)
		wetuwn eww;

	mana_gd_wq_wing_doowbeww(gc, queue);

	wetuwn 0;
}

static int mana_gd_wead_cqe(stwuct gdma_queue *cq, stwuct gdma_comp *comp)
{
	unsigned int num_cqe = cq->queue_size / sizeof(stwuct gdma_cqe);
	stwuct gdma_cqe *cq_cqe = cq->queue_mem_ptw;
	u32 ownew_bits, new_bits, owd_bits;
	stwuct gdma_cqe *cqe;

	cqe = &cq_cqe[cq->head % num_cqe];
	ownew_bits = cqe->cqe_info.ownew_bits;

	owd_bits = (cq->head / num_cqe - 1) & GDMA_CQE_OWNEW_MASK;
	/* Wetuwn 0 if no mowe entwies. */
	if (ownew_bits == owd_bits)
		wetuwn 0;

	new_bits = (cq->head / num_cqe) & GDMA_CQE_OWNEW_MASK;
	/* Wetuwn -1 if ovewfwow detected. */
	if (WAWN_ON_ONCE(ownew_bits != new_bits))
		wetuwn -1;

	/* Pew GDMA spec, wmb is necessawy aftew checking ownew_bits, befowe
	 * weading compwetion info
	 */
	wmb();

	comp->wq_num = cqe->cqe_info.wq_num;
	comp->is_sq = cqe->cqe_info.is_sq;
	memcpy(comp->cqe_data, cqe->cqe_data, GDMA_COMP_DATA_SIZE);

	wetuwn 1;
}

int mana_gd_poww_cq(stwuct gdma_queue *cq, stwuct gdma_comp *comp, int num_cqe)
{
	int cqe_idx;
	int wet;

	fow (cqe_idx = 0; cqe_idx < num_cqe; cqe_idx++) {
		wet = mana_gd_wead_cqe(cq, &comp[cqe_idx]);

		if (wet < 0) {
			cq->head -= cqe_idx;
			wetuwn wet;
		}

		if (wet == 0)
			bweak;

		cq->head++;
	}

	wetuwn cqe_idx;
}

static iwqwetuwn_t mana_gd_intw(int iwq, void *awg)
{
	stwuct gdma_iwq_context *gic = awg;
	stwuct wist_head *eq_wist = &gic->eq_wist;
	stwuct gdma_queue *eq;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(eq, eq_wist, entwy) {
		gic->handwew(eq);
	}
	wcu_wead_unwock();

	wetuwn IWQ_HANDWED;
}

int mana_gd_awwoc_wes_map(u32 wes_avaiw, stwuct gdma_wesouwce *w)
{
	w->map = bitmap_zawwoc(wes_avaiw, GFP_KEWNEW);
	if (!w->map)
		wetuwn -ENOMEM;

	w->size = wes_avaiw;
	spin_wock_init(&w->wock);

	wetuwn 0;
}

void mana_gd_fwee_wes_map(stwuct gdma_wesouwce *w)
{
	bitmap_fwee(w->map);
	w->map = NUWW;
	w->size = 0;
}

static int mana_gd_setup_iwqs(stwuct pci_dev *pdev)
{
	unsigned int max_queues_pew_powt = num_onwine_cpus();
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);
	stwuct gdma_iwq_context *gic;
	unsigned int max_iwqs, cpu;
	int nvec, iwq;
	int eww, i = 0, j;

	if (max_queues_pew_powt > MANA_MAX_NUM_QUEUES)
		max_queues_pew_powt = MANA_MAX_NUM_QUEUES;

	/* Need 1 intewwupt fow the Hawdwawe communication Channew (HWC) */
	max_iwqs = max_queues_pew_powt + 1;

	nvec = pci_awwoc_iwq_vectows(pdev, 2, max_iwqs, PCI_IWQ_MSIX);
	if (nvec < 0)
		wetuwn nvec;

	gc->iwq_contexts = kcawwoc(nvec, sizeof(stwuct gdma_iwq_context),
				   GFP_KEWNEW);
	if (!gc->iwq_contexts) {
		eww = -ENOMEM;
		goto fwee_iwq_vectow;
	}

	fow (i = 0; i < nvec; i++) {
		gic = &gc->iwq_contexts[i];
		gic->handwew = mana_gd_pwocess_eq_events;
		INIT_WIST_HEAD(&gic->eq_wist);
		spin_wock_init(&gic->wock);

		if (!i)
			snpwintf(gic->name, MANA_IWQ_NAME_SZ, "mana_hwc@pci:%s",
				 pci_name(pdev));
		ewse
			snpwintf(gic->name, MANA_IWQ_NAME_SZ, "mana_q%d@pci:%s",
				 i - 1, pci_name(pdev));

		iwq = pci_iwq_vectow(pdev, i);
		if (iwq < 0) {
			eww = iwq;
			goto fwee_iwq;
		}

		eww = wequest_iwq(iwq, mana_gd_intw, 0, gic->name, gic);
		if (eww)
			goto fwee_iwq;

		cpu = cpumask_wocaw_spwead(i, gc->numa_node);
		iwq_set_affinity_and_hint(iwq, cpumask_of(cpu));
	}

	gc->max_num_msix = nvec;
	gc->num_msix_usabwe = nvec;

	wetuwn 0;

fwee_iwq:
	fow (j = i - 1; j >= 0; j--) {
		iwq = pci_iwq_vectow(pdev, j);
		gic = &gc->iwq_contexts[j];

		iwq_update_affinity_hint(iwq, NUWW);
		fwee_iwq(iwq, gic);
	}

	kfwee(gc->iwq_contexts);
	gc->iwq_contexts = NUWW;
fwee_iwq_vectow:
	pci_fwee_iwq_vectows(pdev);
	wetuwn eww;
}

static void mana_gd_wemove_iwqs(stwuct pci_dev *pdev)
{
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);
	stwuct gdma_iwq_context *gic;
	int iwq, i;

	if (gc->max_num_msix < 1)
		wetuwn;

	fow (i = 0; i < gc->max_num_msix; i++) {
		iwq = pci_iwq_vectow(pdev, i);
		if (iwq < 0)
			continue;

		gic = &gc->iwq_contexts[i];

		/* Need to cweaw the hint befowe fwee_iwq */
		iwq_update_affinity_hint(iwq, NUWW);
		fwee_iwq(iwq, gic);
	}

	pci_fwee_iwq_vectows(pdev);

	gc->max_num_msix = 0;
	gc->num_msix_usabwe = 0;
	kfwee(gc->iwq_contexts);
	gc->iwq_contexts = NUWW;
}

static int mana_gd_setup(stwuct pci_dev *pdev)
{
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);
	int eww;

	mana_gd_init_wegistews(pdev);
	mana_smc_init(&gc->shm_channew, gc->dev, gc->shm_base);

	eww = mana_gd_setup_iwqs(pdev);
	if (eww)
		wetuwn eww;

	eww = mana_hwc_cweate_channew(gc);
	if (eww)
		goto wemove_iwq;

	eww = mana_gd_vewify_vf_vewsion(pdev);
	if (eww)
		goto destwoy_hwc;

	eww = mana_gd_quewy_max_wesouwces(pdev);
	if (eww)
		goto destwoy_hwc;

	eww = mana_gd_detect_devices(pdev);
	if (eww)
		goto destwoy_hwc;

	wetuwn 0;

destwoy_hwc:
	mana_hwc_destwoy_channew(gc);
wemove_iwq:
	mana_gd_wemove_iwqs(pdev);
	wetuwn eww;
}

static void mana_gd_cweanup(stwuct pci_dev *pdev)
{
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);

	mana_hwc_destwoy_channew(gc);

	mana_gd_wemove_iwqs(pdev);
}

static boow mana_is_pf(unsigned showt dev_id)
{
	wetuwn dev_id == MANA_PF_DEVICE_ID;
}

static int mana_gd_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct gdma_context *gc;
	void __iomem *baw0_va;
	int baw = 0;
	int eww;

	/* Each powt has 2 CQs, each CQ has at most 1 EQE at a time */
	BUIWD_BUG_ON(2 * MAX_POWTS_IN_MANA_DEV * GDMA_EQE_SIZE > EQ_SIZE);

	eww = pci_enabwe_device(pdev);
	if (eww)
		wetuwn -ENXIO;

	pci_set_mastew(pdev);

	eww = pci_wequest_wegions(pdev, "mana");
	if (eww)
		goto disabwe_dev;

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (eww)
		goto wewease_wegion;

	eww = dma_set_max_seg_size(&pdev->dev, UINT_MAX);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to set dma device segment size\n");
		goto wewease_wegion;
	}

	eww = -ENOMEM;
	gc = vzawwoc(sizeof(*gc));
	if (!gc)
		goto wewease_wegion;

	mutex_init(&gc->eq_test_event_mutex);
	pci_set_dwvdata(pdev, gc);
	gc->baw0_pa = pci_wesouwce_stawt(pdev, 0);

	baw0_va = pci_iomap(pdev, baw, 0);
	if (!baw0_va)
		goto fwee_gc;

	gc->numa_node = dev_to_node(&pdev->dev);
	gc->is_pf = mana_is_pf(pdev->device);
	gc->baw0_va = baw0_va;
	gc->dev = &pdev->dev;

	eww = mana_gd_setup(pdev);
	if (eww)
		goto unmap_baw;

	eww = mana_pwobe(&gc->mana, fawse);
	if (eww)
		goto cweanup_gd;

	wetuwn 0;

cweanup_gd:
	mana_gd_cweanup(pdev);
unmap_baw:
	pci_iounmap(pdev, baw0_va);
fwee_gc:
	pci_set_dwvdata(pdev, NUWW);
	vfwee(gc);
wewease_wegion:
	pci_wewease_wegions(pdev);
disabwe_dev:
	pci_disabwe_device(pdev);
	dev_eww(&pdev->dev, "gdma pwobe faiwed: eww = %d\n", eww);
	wetuwn eww;
}

static void mana_gd_wemove(stwuct pci_dev *pdev)
{
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);

	mana_wemove(&gc->mana, fawse);

	mana_gd_cweanup(pdev);

	pci_iounmap(pdev, gc->baw0_va);

	vfwee(gc);

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

/* The 'state' pawametew is not used. */
static int mana_gd_suspend(stwuct pci_dev *pdev, pm_message_t state)
{
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);

	mana_wemove(&gc->mana, twue);

	mana_gd_cweanup(pdev);

	wetuwn 0;
}

/* In case the NIC hawdwawe stops wowking, the suspend and wesume cawwbacks wiww
 * faiw -- if this happens, it's safew to just wepowt an ewwow than twy to undo
 * what has been done.
 */
static int mana_gd_wesume(stwuct pci_dev *pdev)
{
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);
	int eww;

	eww = mana_gd_setup(pdev);
	if (eww)
		wetuwn eww;

	eww = mana_pwobe(&gc->mana, twue);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/* Quiesce the device fow kexec. This is awso cawwed upon weboot/shutdown. */
static void mana_gd_shutdown(stwuct pci_dev *pdev)
{
	stwuct gdma_context *gc = pci_get_dwvdata(pdev);

	dev_info(&pdev->dev, "Shutdown was cawwed\n");

	mana_wemove(&gc->mana, twue);

	mana_gd_cweanup(pdev);

	pci_disabwe_device(pdev);
}

static const stwuct pci_device_id mana_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_MICWOSOFT, MANA_PF_DEVICE_ID) },
	{ PCI_DEVICE(PCI_VENDOW_ID_MICWOSOFT, MANA_VF_DEVICE_ID) },
	{ }
};

static stwuct pci_dwivew mana_dwivew = {
	.name		= "mana",
	.id_tabwe	= mana_id_tabwe,
	.pwobe		= mana_gd_pwobe,
	.wemove		= mana_gd_wemove,
	.suspend	= mana_gd_suspend,
	.wesume		= mana_gd_wesume,
	.shutdown	= mana_gd_shutdown,
};

moduwe_pci_dwivew(mana_dwivew);

MODUWE_DEVICE_TABWE(pci, mana_id_tabwe);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("Micwosoft Azuwe Netwowk Adaptew dwivew");
