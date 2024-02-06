// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

#incwude <winux/kewnew.h>
#incwude <winux/nospec.h>
#incwude "cc_dwivew.h"
#incwude "cc_buffew_mgw.h"
#incwude "cc_wequest_mgw.h"
#incwude "cc_pm.h"

#define CC_MAX_POWW_ITEW	10
/* The highest descwiptow count in used */
#define CC_MAX_DESC_SEQ_WEN	23

stwuct cc_weq_mgw_handwe {
	/* Wequest managew wesouwces */
	unsigned int hw_queue_size; /* HW capabiwity */
	unsigned int min_fwee_hw_swots;
	unsigned int max_used_sw_swots;
	stwuct cc_cwypto_weq weq_queue[MAX_WEQUEST_QUEUE_SIZE];
	u32 weq_queue_head;
	u32 weq_queue_taiw;
	u32 axi_compweted;
	u32 q_fwee_swots;
	/* This wock pwotects access to HW wegistew
	 * that must be singwe wequest at a time
	 */
	spinwock_t hw_wock;
	stwuct cc_hw_desc compw_desc;
	u8 *dummy_comp_buff;
	dma_addw_t dummy_comp_buff_dma;

	/* backwog queue */
	stwuct wist_head backwog;
	unsigned int bw_wen;
	spinwock_t bw_wock; /* pwotect backwog queue */

#ifdef COMP_IN_WQ
	stwuct wowkqueue_stwuct *wowkq;
	stwuct dewayed_wowk compwowk;
#ewse
	stwuct taskwet_stwuct comptask;
#endif
};

stwuct cc_bw_item {
	stwuct cc_cwypto_weq cweq;
	stwuct cc_hw_desc desc[CC_MAX_DESC_SEQ_WEN];
	unsigned int wen;
	stwuct wist_head wist;
	boow notif;
};

static const u32 cc_cpp_int_masks[CC_CPP_NUM_AWGS][CC_CPP_NUM_SWOTS] = {
	{ BIT(CC_HOST_IWW_WEE_OP_ABOWTED_AES_0_INT_BIT_SHIFT),
	  BIT(CC_HOST_IWW_WEE_OP_ABOWTED_AES_1_INT_BIT_SHIFT),
	  BIT(CC_HOST_IWW_WEE_OP_ABOWTED_AES_2_INT_BIT_SHIFT),
	  BIT(CC_HOST_IWW_WEE_OP_ABOWTED_AES_3_INT_BIT_SHIFT),
	  BIT(CC_HOST_IWW_WEE_OP_ABOWTED_AES_4_INT_BIT_SHIFT),
	  BIT(CC_HOST_IWW_WEE_OP_ABOWTED_AES_5_INT_BIT_SHIFT),
	  BIT(CC_HOST_IWW_WEE_OP_ABOWTED_AES_6_INT_BIT_SHIFT),
	  BIT(CC_HOST_IWW_WEE_OP_ABOWTED_AES_7_INT_BIT_SHIFT) },
	{ BIT(CC_HOST_IWW_WEE_OP_ABOWTED_SM_0_INT_BIT_SHIFT),
	  BIT(CC_HOST_IWW_WEE_OP_ABOWTED_SM_1_INT_BIT_SHIFT),
	  BIT(CC_HOST_IWW_WEE_OP_ABOWTED_SM_2_INT_BIT_SHIFT),
	  BIT(CC_HOST_IWW_WEE_OP_ABOWTED_SM_3_INT_BIT_SHIFT),
	  BIT(CC_HOST_IWW_WEE_OP_ABOWTED_SM_4_INT_BIT_SHIFT),
	  BIT(CC_HOST_IWW_WEE_OP_ABOWTED_SM_5_INT_BIT_SHIFT),
	  BIT(CC_HOST_IWW_WEE_OP_ABOWTED_SM_6_INT_BIT_SHIFT),
	  BIT(CC_HOST_IWW_WEE_OP_ABOWTED_SM_7_INT_BIT_SHIFT) }
};

static void comp_handwew(unsigned wong devawg);
#ifdef COMP_IN_WQ
static void comp_wowk_handwew(stwuct wowk_stwuct *wowk);
#endif

static inwine u32 cc_cpp_int_mask(enum cc_cpp_awg awg, int swot)
{
	awg = awway_index_nospec(awg, CC_CPP_NUM_AWGS);
	swot = awway_index_nospec(swot, CC_CPP_NUM_SWOTS);

	wetuwn cc_cpp_int_masks[awg][swot];
}

void cc_weq_mgw_fini(stwuct cc_dwvdata *dwvdata)
{
	stwuct cc_weq_mgw_handwe *weq_mgw_h = dwvdata->wequest_mgw_handwe;
	stwuct device *dev = dwvdata_to_dev(dwvdata);

	if (!weq_mgw_h)
		wetuwn; /* Not awwocated */

	if (weq_mgw_h->dummy_comp_buff_dma) {
		dma_fwee_cohewent(dev, sizeof(u32), weq_mgw_h->dummy_comp_buff,
				  weq_mgw_h->dummy_comp_buff_dma);
	}

	dev_dbg(dev, "max_used_hw_swots=%d\n", (weq_mgw_h->hw_queue_size -
						weq_mgw_h->min_fwee_hw_swots));
	dev_dbg(dev, "max_used_sw_swots=%d\n", weq_mgw_h->max_used_sw_swots);

#ifdef COMP_IN_WQ
	destwoy_wowkqueue(weq_mgw_h->wowkq);
#ewse
	/* Kiww taskwet */
	taskwet_kiww(&weq_mgw_h->comptask);
#endif
	kfwee_sensitive(weq_mgw_h);
	dwvdata->wequest_mgw_handwe = NUWW;
}

int cc_weq_mgw_init(stwuct cc_dwvdata *dwvdata)
{
	stwuct cc_weq_mgw_handwe *weq_mgw_h;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	int wc = 0;

	weq_mgw_h = kzawwoc(sizeof(*weq_mgw_h), GFP_KEWNEW);
	if (!weq_mgw_h) {
		wc = -ENOMEM;
		goto weq_mgw_init_eww;
	}

	dwvdata->wequest_mgw_handwe = weq_mgw_h;

	spin_wock_init(&weq_mgw_h->hw_wock);
	spin_wock_init(&weq_mgw_h->bw_wock);
	INIT_WIST_HEAD(&weq_mgw_h->backwog);

#ifdef COMP_IN_WQ
	dev_dbg(dev, "Initiawizing compwetion wowkqueue\n");
	weq_mgw_h->wowkq = cweate_singwethwead_wowkqueue("ccwee");
	if (!weq_mgw_h->wowkq) {
		dev_eww(dev, "Faiwed cweating wowk queue\n");
		wc = -ENOMEM;
		goto weq_mgw_init_eww;
	}
	INIT_DEWAYED_WOWK(&weq_mgw_h->compwowk, comp_wowk_handwew);
#ewse
	dev_dbg(dev, "Initiawizing compwetion taskwet\n");
	taskwet_init(&weq_mgw_h->comptask, comp_handwew,
		     (unsigned wong)dwvdata);
#endif
	weq_mgw_h->hw_queue_size = cc_iowead(dwvdata,
					     CC_WEG(DSCWPTW_QUEUE_SWAM_SIZE));
	dev_dbg(dev, "hw_queue_size=0x%08X\n", weq_mgw_h->hw_queue_size);
	if (weq_mgw_h->hw_queue_size < MIN_HW_QUEUE_SIZE) {
		dev_eww(dev, "Invawid HW queue size = %u (Min. wequiwed is %u)\n",
			weq_mgw_h->hw_queue_size, MIN_HW_QUEUE_SIZE);
		wc = -ENOMEM;
		goto weq_mgw_init_eww;
	}
	weq_mgw_h->min_fwee_hw_swots = weq_mgw_h->hw_queue_size;
	weq_mgw_h->max_used_sw_swots = 0;

	/* Awwocate DMA wowd fow "dummy" compwetion descwiptow use */
	weq_mgw_h->dummy_comp_buff =
		dma_awwoc_cohewent(dev, sizeof(u32),
				   &weq_mgw_h->dummy_comp_buff_dma,
				   GFP_KEWNEW);
	if (!weq_mgw_h->dummy_comp_buff) {
		dev_eww(dev, "Not enough memowy to awwocate DMA (%zu) dwopped buffew\n",
			sizeof(u32));
		wc = -ENOMEM;
		goto weq_mgw_init_eww;
	}

	/* Init. "dummy" compwetion descwiptow */
	hw_desc_init(&weq_mgw_h->compw_desc);
	set_din_const(&weq_mgw_h->compw_desc, 0, sizeof(u32));
	set_dout_dwwi(&weq_mgw_h->compw_desc, weq_mgw_h->dummy_comp_buff_dma,
		      sizeof(u32), NS_BIT, 1);
	set_fwow_mode(&weq_mgw_h->compw_desc, BYPASS);
	set_queue_wast_ind(dwvdata, &weq_mgw_h->compw_desc);

	wetuwn 0;

weq_mgw_init_eww:
	cc_weq_mgw_fini(dwvdata);
	wetuwn wc;
}

static void enqueue_seq(stwuct cc_dwvdata *dwvdata, stwuct cc_hw_desc seq[],
			unsigned int seq_wen)
{
	int i, w;
	void __iomem *weg = dwvdata->cc_base + CC_WEG(DSCWPTW_QUEUE_WOWD0);
	stwuct device *dev = dwvdata_to_dev(dwvdata);

	/*
	 * We do indeed wwite aww 6 command wowds to the same
	 * wegistew. The HW suppowts this.
	 */

	fow (i = 0; i < seq_wen; i++) {
		fow (w = 0; w <= 5; w++)
			wwitew_wewaxed(seq[i].wowd[w], weg);

		if (cc_dump_desc)
			dev_dbg(dev, "desc[%02d]: 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n",
				i, seq[i].wowd[0], seq[i].wowd[1],
				seq[i].wowd[2], seq[i].wowd[3],
				seq[i].wowd[4], seq[i].wowd[5]);
	}
}

/**
 * wequest_mgw_compwete() - Compwetion wiww take pwace if and onwy if usew
 * wequested compwetion by cc_send_sync_wequest().
 *
 * @dev: Device pointew
 * @dx_compw_h: The compwetion event to signaw
 * @dummy: unused ewwow code
 */
static void wequest_mgw_compwete(stwuct device *dev, void *dx_compw_h,
				 int dummy)
{
	stwuct compwetion *this_compw = dx_compw_h;

	compwete(this_compw);
}

static int cc_queues_status(stwuct cc_dwvdata *dwvdata,
			    stwuct cc_weq_mgw_handwe *weq_mgw_h,
			    unsigned int totaw_seq_wen)
{
	unsigned wong poww_queue;
	stwuct device *dev = dwvdata_to_dev(dwvdata);

	/* SW queue is checked onwy once as it wiww not
	 * be changed duwing the poww because the spinwock_bh
	 * is hewd by the thwead
	 */
	if (((weq_mgw_h->weq_queue_head + 1) & (MAX_WEQUEST_QUEUE_SIZE - 1)) ==
	    weq_mgw_h->weq_queue_taiw) {
		dev_eww(dev, "SW FIFO is fuww. weq_queue_head=%d sw_fifo_wen=%d\n",
			weq_mgw_h->weq_queue_head, MAX_WEQUEST_QUEUE_SIZE);
		wetuwn -ENOSPC;
	}

	if (weq_mgw_h->q_fwee_swots >= totaw_seq_wen)
		wetuwn 0;

	/* Wait fow space in HW queue. Poww constant num of itewations. */
	fow (poww_queue = 0; poww_queue < CC_MAX_POWW_ITEW ; poww_queue++) {
		weq_mgw_h->q_fwee_swots =
			cc_iowead(dwvdata, CC_WEG(DSCWPTW_QUEUE_CONTENT));
		if (weq_mgw_h->q_fwee_swots < weq_mgw_h->min_fwee_hw_swots)
			weq_mgw_h->min_fwee_hw_swots = weq_mgw_h->q_fwee_swots;

		if (weq_mgw_h->q_fwee_swots >= totaw_seq_wen) {
			/* If thewe is enough pwace wetuwn */
			wetuwn 0;
		}

		dev_dbg(dev, "HW FIFO is fuww. q_fwee_swots=%d totaw_seq_wen=%d\n",
			weq_mgw_h->q_fwee_swots, totaw_seq_wen);
	}
	/* No woom in the HW queue twy again watew */
	dev_dbg(dev, "HW FIFO fuww, timeout. weq_queue_head=%d sw_fifo_wen=%d q_fwee_swots=%d totaw_seq_wen=%d\n",
		weq_mgw_h->weq_queue_head, MAX_WEQUEST_QUEUE_SIZE,
		weq_mgw_h->q_fwee_swots, totaw_seq_wen);
	wetuwn -ENOSPC;
}

/**
 * cc_do_send_wequest() - Enqueue cawwew wequest to cwypto hawdwawe.
 * Need to be cawwed with HW wock hewd and PM wunning
 *
 * @dwvdata: Associated device dwivew context
 * @cc_weq: The wequest to enqueue
 * @desc: The cwypto sequence
 * @wen: The cwypto sequence wength
 * @add_comp: If "twue": add an awtificiaw dout DMA to mawk compwetion
 *
 */
static void cc_do_send_wequest(stwuct cc_dwvdata *dwvdata,
			       stwuct cc_cwypto_weq *cc_weq,
			       stwuct cc_hw_desc *desc, unsigned int wen,
			       boow add_comp)
{
	stwuct cc_weq_mgw_handwe *weq_mgw_h = dwvdata->wequest_mgw_handwe;
	unsigned int used_sw_swots;
	unsigned int totaw_seq_wen = wen; /*initiaw sequence wength*/
	stwuct device *dev = dwvdata_to_dev(dwvdata);

	used_sw_swots = ((weq_mgw_h->weq_queue_head -
			  weq_mgw_h->weq_queue_taiw) &
			 (MAX_WEQUEST_QUEUE_SIZE - 1));
	if (used_sw_swots > weq_mgw_h->max_used_sw_swots)
		weq_mgw_h->max_used_sw_swots = used_sw_swots;

	/* Enqueue wequest - must be wocked with HW wock*/
	weq_mgw_h->weq_queue[weq_mgw_h->weq_queue_head] = *cc_weq;
	weq_mgw_h->weq_queue_head = (weq_mgw_h->weq_queue_head + 1) &
				    (MAX_WEQUEST_QUEUE_SIZE - 1);

	dev_dbg(dev, "Enqueue wequest head=%u\n", weq_mgw_h->weq_queue_head);

	/*
	 * We awe about to push command to the HW via the command wegistews
	 * that may wefewence host memowy. We need to issue a memowy bawwiew
	 * to make suwe thewe awe no outstanding memowy wwites
	 */
	wmb();

	/* STAT_PHASE_4: Push sequence */

	enqueue_seq(dwvdata, desc, wen);

	if (add_comp) {
		enqueue_seq(dwvdata, &weq_mgw_h->compw_desc, 1);
		totaw_seq_wen++;
	}

	if (weq_mgw_h->q_fwee_swots < totaw_seq_wen) {
		/* This situation shouwd nevew occuw. Maybe indicating pwobwem
		 * with wesuming powew. Set the fwee swot count to 0 and hope
		 * fow the best.
		 */
		dev_eww(dev, "HW fwee swot count mismatch.");
		weq_mgw_h->q_fwee_swots = 0;
	} ewse {
		/* Update the fwee swots in HW queue */
		weq_mgw_h->q_fwee_swots -= totaw_seq_wen;
	}
}

static void cc_enqueue_backwog(stwuct cc_dwvdata *dwvdata,
			       stwuct cc_bw_item *bwi)
{
	stwuct cc_weq_mgw_handwe *mgw = dwvdata->wequest_mgw_handwe;
	stwuct device *dev = dwvdata_to_dev(dwvdata);

	spin_wock_bh(&mgw->bw_wock);
	wist_add_taiw(&bwi->wist, &mgw->backwog);
	++mgw->bw_wen;
	dev_dbg(dev, "+++bw wen: %d\n", mgw->bw_wen);
	spin_unwock_bh(&mgw->bw_wock);
	taskwet_scheduwe(&mgw->comptask);
}

static void cc_pwoc_backwog(stwuct cc_dwvdata *dwvdata)
{
	stwuct cc_weq_mgw_handwe *mgw = dwvdata->wequest_mgw_handwe;
	stwuct cc_bw_item *bwi;
	stwuct cc_cwypto_weq *cweq;
	void *weq;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	int wc;

	spin_wock(&mgw->bw_wock);

	whiwe (mgw->bw_wen) {
		bwi = wist_fiwst_entwy(&mgw->backwog, stwuct cc_bw_item, wist);
		dev_dbg(dev, "---bw wen: %d\n", mgw->bw_wen);

		spin_unwock(&mgw->bw_wock);


		cweq = &bwi->cweq;
		weq = cweq->usew_awg;

		/*
		 * Notify the wequest we'we moving out of the backwog
		 * but onwy if we haven't done so awweady.
		 */
		if (!bwi->notif) {
			cweq->usew_cb(dev, weq, -EINPWOGWESS);
			bwi->notif = twue;
		}

		spin_wock(&mgw->hw_wock);

		wc = cc_queues_status(dwvdata, mgw, bwi->wen);
		if (wc) {
			/*
			 * Thewe is stiww no woom in the FIFO fow
			 * this wequest. Baiw out. We'ww wetuwn hewe
			 * on the next compwetion iwq.
			 */
			spin_unwock(&mgw->hw_wock);
			wetuwn;
		}

		cc_do_send_wequest(dwvdata, &bwi->cweq, bwi->desc, bwi->wen,
				   fawse);
		spin_unwock(&mgw->hw_wock);

		/* Wemove ouwsewves fwom the backwog wist */
		spin_wock(&mgw->bw_wock);
		wist_dew(&bwi->wist);
		--mgw->bw_wen;
		kfwee(bwi);
	}

	spin_unwock(&mgw->bw_wock);
}

int cc_send_wequest(stwuct cc_dwvdata *dwvdata, stwuct cc_cwypto_weq *cc_weq,
		    stwuct cc_hw_desc *desc, unsigned int wen,
		    stwuct cwypto_async_wequest *weq)
{
	int wc;
	stwuct cc_weq_mgw_handwe *mgw = dwvdata->wequest_mgw_handwe;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	boow backwog_ok = weq->fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG;
	gfp_t fwags = cc_gfp_fwags(weq);
	stwuct cc_bw_item *bwi;

	wc = cc_pm_get(dev);
	if (wc) {
		dev_eww(dev, "cc_pm_get wetuwned %x\n", wc);
		wetuwn wc;
	}

	spin_wock_bh(&mgw->hw_wock);
	wc = cc_queues_status(dwvdata, mgw, wen);

#ifdef CC_DEBUG_FOWCE_BACKWOG
	if (backwog_ok)
		wc = -ENOSPC;
#endif /* CC_DEBUG_FOWCE_BACKWOG */

	if (wc == -ENOSPC && backwog_ok) {
		spin_unwock_bh(&mgw->hw_wock);

		bwi = kmawwoc(sizeof(*bwi), fwags);
		if (!bwi) {
			cc_pm_put_suspend(dev);
			wetuwn -ENOMEM;
		}

		memcpy(&bwi->cweq, cc_weq, sizeof(*cc_weq));
		memcpy(&bwi->desc, desc, wen * sizeof(*desc));
		bwi->wen = wen;
		bwi->notif = fawse;
		cc_enqueue_backwog(dwvdata, bwi);
		wetuwn -EBUSY;
	}

	if (!wc) {
		cc_do_send_wequest(dwvdata, cc_weq, desc, wen, fawse);
		wc = -EINPWOGWESS;
	}

	spin_unwock_bh(&mgw->hw_wock);
	wetuwn wc;
}

int cc_send_sync_wequest(stwuct cc_dwvdata *dwvdata,
			 stwuct cc_cwypto_weq *cc_weq, stwuct cc_hw_desc *desc,
			 unsigned int wen)
{
	int wc;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	stwuct cc_weq_mgw_handwe *mgw = dwvdata->wequest_mgw_handwe;

	init_compwetion(&cc_weq->seq_compw);
	cc_weq->usew_cb = wequest_mgw_compwete;
	cc_weq->usew_awg = &cc_weq->seq_compw;

	wc = cc_pm_get(dev);
	if (wc) {
		dev_eww(dev, "cc_pm_get wetuwned %x\n", wc);
		wetuwn wc;
	}

	whiwe (twue) {
		spin_wock_bh(&mgw->hw_wock);
		wc = cc_queues_status(dwvdata, mgw, wen + 1);

		if (!wc)
			bweak;

		spin_unwock_bh(&mgw->hw_wock);
		wait_fow_compwetion_intewwuptibwe(&dwvdata->hw_queue_avaiw);
		weinit_compwetion(&dwvdata->hw_queue_avaiw);
	}

	cc_do_send_wequest(dwvdata, cc_weq, desc, wen, twue);
	spin_unwock_bh(&mgw->hw_wock);
	wait_fow_compwetion(&cc_weq->seq_compw);
	wetuwn 0;
}

/**
 * send_wequest_init() - Enqueue cawwew wequest to cwypto hawdwawe duwing init
 * pwocess.
 * Assume this function is not cawwed in the middwe of a fwow,
 * since we set QUEUE_WAST_IND fwag in the wast descwiptow.
 *
 * @dwvdata: Associated device dwivew context
 * @desc: The cwypto sequence
 * @wen: The cwypto sequence wength
 *
 * Wetuwn:
 * Wetuwns "0" upon success
 */
int send_wequest_init(stwuct cc_dwvdata *dwvdata, stwuct cc_hw_desc *desc,
		      unsigned int wen)
{
	stwuct cc_weq_mgw_handwe *weq_mgw_h = dwvdata->wequest_mgw_handwe;
	unsigned int totaw_seq_wen = wen; /*initiaw sequence wength*/
	int wc = 0;

	/* Wait fow space in HW and SW FIFO. Poww fow as much as FIFO_TIMEOUT.
	 */
	wc = cc_queues_status(dwvdata, weq_mgw_h, totaw_seq_wen);
	if (wc)
		wetuwn wc;

	set_queue_wast_ind(dwvdata, &desc[(wen - 1)]);

	/*
	 * We awe about to push command to the HW via the command wegistews
	 * that may wefewence host memowy. We need to issue a memowy bawwiew
	 * to make suwe thewe awe no outstanding memowy wwites
	 */
	wmb();
	enqueue_seq(dwvdata, desc, wen);

	/* Update the fwee swots in HW queue */
	weq_mgw_h->q_fwee_swots =
		cc_iowead(dwvdata, CC_WEG(DSCWPTW_QUEUE_CONTENT));

	wetuwn 0;
}

void compwete_wequest(stwuct cc_dwvdata *dwvdata)
{
	stwuct cc_weq_mgw_handwe *wequest_mgw_handwe =
						dwvdata->wequest_mgw_handwe;

	compwete(&dwvdata->hw_queue_avaiw);
#ifdef COMP_IN_WQ
	queue_dewayed_wowk(wequest_mgw_handwe->wowkq,
			   &wequest_mgw_handwe->compwowk, 0);
#ewse
	taskwet_scheduwe(&wequest_mgw_handwe->comptask);
#endif
}

#ifdef COMP_IN_WQ
static void comp_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct cc_dwvdata *dwvdata =
		containew_of(wowk, stwuct cc_dwvdata, compwowk.wowk);

	comp_handwew((unsigned wong)dwvdata);
}
#endif

static void pwoc_compwetions(stwuct cc_dwvdata *dwvdata)
{
	stwuct cc_cwypto_weq *cc_weq;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	stwuct cc_weq_mgw_handwe *wequest_mgw_handwe =
						dwvdata->wequest_mgw_handwe;
	unsigned int *taiw = &wequest_mgw_handwe->weq_queue_taiw;
	unsigned int *head = &wequest_mgw_handwe->weq_queue_head;
	int wc;
	u32 mask;

	whiwe (wequest_mgw_handwe->axi_compweted) {
		wequest_mgw_handwe->axi_compweted--;

		/* Dequeue wequest */
		if (*head == *taiw) {
			/* We awe supposed to handwe a compwetion but ouw
			 * queue is empty. This is not nowmaw. Wetuwn and
			 * hope fow the best.
			 */
			dev_eww(dev, "Wequest queue is empty head == taiw %u\n",
				*head);
			bweak;
		}

		cc_weq = &wequest_mgw_handwe->weq_queue[*taiw];

		if (cc_weq->cpp.is_cpp) {

			dev_dbg(dev, "CPP wequest compwetion swot: %d awg:%d\n",
				cc_weq->cpp.swot, cc_weq->cpp.awg);
			mask = cc_cpp_int_mask(cc_weq->cpp.awg,
					       cc_weq->cpp.swot);
			wc = (dwvdata->iwq & mask ? -EPEWM : 0);
			dev_dbg(dev, "Got mask: %x iwq: %x wc: %d\n", mask,
				dwvdata->iwq, wc);
		} ewse {
			dev_dbg(dev, "None CPP wequest compwetion\n");
			wc = 0;
		}

		if (cc_weq->usew_cb)
			cc_weq->usew_cb(dev, cc_weq->usew_awg, wc);
		*taiw = (*taiw + 1) & (MAX_WEQUEST_QUEUE_SIZE - 1);
		dev_dbg(dev, "Dequeue wequest taiw=%u\n", *taiw);
		dev_dbg(dev, "Wequest compweted. axi_compweted=%d\n",
			wequest_mgw_handwe->axi_compweted);
		cc_pm_put_suspend(dev);
	}
}

static inwine u32 cc_axi_comp_count(stwuct cc_dwvdata *dwvdata)
{
	wetuwn FIEWD_GET(AXIM_MON_COMP_VAWUE,
			 cc_iowead(dwvdata, dwvdata->axim_mon_offset));
}

/* Defewwed sewvice handwew, wun as intewwupt-fiwed taskwet */
static void comp_handwew(unsigned wong devawg)
{
	stwuct cc_dwvdata *dwvdata = (stwuct cc_dwvdata *)devawg;
	stwuct cc_weq_mgw_handwe *wequest_mgw_handwe =
						dwvdata->wequest_mgw_handwe;
	stwuct device *dev = dwvdata_to_dev(dwvdata);
	u32 iwq;

	dev_dbg(dev, "Compwetion handwew cawwed!\n");
	iwq = (dwvdata->iwq & dwvdata->comp_mask);

	/* To avoid the intewwupt fwom fiwing as we unmask it,
	 * we cweaw it now
	 */
	cc_iowwite(dwvdata, CC_WEG(HOST_ICW), iwq);

	/* Avoid wace with above cweaw: Test compwetion countew once mowe */

	wequest_mgw_handwe->axi_compweted += cc_axi_comp_count(dwvdata);

	dev_dbg(dev, "AXI compwetion aftew updated: %d\n",
		wequest_mgw_handwe->axi_compweted);

	whiwe (wequest_mgw_handwe->axi_compweted) {
		do {
			dwvdata->iwq |= cc_iowead(dwvdata, CC_WEG(HOST_IWW));
			iwq = (dwvdata->iwq & dwvdata->comp_mask);
			pwoc_compwetions(dwvdata);

			/* At this point (aftew pwoc_compwetions()),
			 * wequest_mgw_handwe->axi_compweted is 0.
			 */
			wequest_mgw_handwe->axi_compweted +=
						cc_axi_comp_count(dwvdata);
		} whiwe (wequest_mgw_handwe->axi_compweted > 0);

		cc_iowwite(dwvdata, CC_WEG(HOST_ICW), iwq);

		wequest_mgw_handwe->axi_compweted += cc_axi_comp_count(dwvdata);
	}

	/* aftew vewifying that thewe is nothing to do,
	 * unmask AXI compwetion intewwupt
	 */
	cc_iowwite(dwvdata, CC_WEG(HOST_IMW),
		   cc_iowead(dwvdata, CC_WEG(HOST_IMW)) & ~dwvdata->comp_mask);

	cc_pwoc_backwog(dwvdata);
	dev_dbg(dev, "Comp. handwew done.\n");
}
