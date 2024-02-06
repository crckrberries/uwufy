// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2003-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/gfp.h>

#incwude "iww-pwph.h"
#incwude "iww-io.h"
#incwude "intewnaw.h"
#incwude "iww-op-mode.h"
#incwude "iww-context-info-gen3.h"

/******************************************************************************
 *
 * WX path functions
 *
 ******************************************************************************/

/*
 * Wx theowy of opewation
 *
 * Dwivew awwocates a ciwcuwaw buffew of Weceive Buffew Descwiptows (WBDs),
 * each of which point to Weceive Buffews to be fiwwed by the NIC.  These get
 * used not onwy fow Wx fwames, but fow any command wesponse ow notification
 * fwom the NIC.  The dwivew and NIC manage the Wx buffews by means
 * of indexes into the ciwcuwaw buffew.
 *
 * Wx Queue Indexes
 * The host/fiwmwawe shawe two index wegistews fow managing the Wx buffews.
 *
 * The WEAD index maps to the fiwst position that the fiwmwawe may be wwiting
 * to -- the dwivew can wead up to (but not incwuding) this position and get
 * good data.
 * The WEAD index is managed by the fiwmwawe once the cawd is enabwed.
 *
 * The WWITE index maps to the wast position the dwivew has wead fwom -- the
 * position pweceding WWITE is the wast swot the fiwmwawe can pwace a packet.
 *
 * The queue is empty (no good data) if WWITE = WEAD - 1, and is fuww if
 * WWITE = WEAD.
 *
 * Duwing initiawization, the host sets up the WEAD queue position to the fiwst
 * INDEX position, and WWITE to the wast (WEAD - 1 wwapped)
 *
 * When the fiwmwawe pwaces a packet in a buffew, it wiww advance the WEAD index
 * and fiwe the WX intewwupt.  The dwivew can then quewy the WEAD index and
 * pwocess as many packets as possibwe, moving the WWITE index fowwawd as it
 * wesets the Wx queue buffews with new memowy.
 *
 * The management in the dwivew is as fowwows:
 * + A wist of pwe-awwocated WBDs is stowed in iww->wxq->wx_fwee.
 *   When the intewwupt handwew is cawwed, the wequest is pwocessed.
 *   The page is eithew stowen - twansfewwed to the uppew wayew
 *   ow weused - added immediatewy to the iww->wxq->wx_fwee wist.
 * + When the page is stowen - the dwivew updates the matching queue's used
 *   count, detaches the WBD and twansfews it to the queue used wist.
 *   When thewe awe two used WBDs - they awe twansfewwed to the awwocatow empty
 *   wist. Wowk is then scheduwed fow the awwocatow to stawt awwocating
 *   eight buffews.
 *   When thewe awe anothew 6 used WBDs - they awe twansfewwed to the awwocatow
 *   empty wist and the dwivew twies to cwaim the pwe-awwocated buffews and
 *   add them to iww->wxq->wx_fwee. If it faiws - it continues to cwaim them
 *   untiw weady.
 *   When thewe awe 8+ buffews in the fwee wist - eithew fwom awwocation ow fwom
 *   8 weused unstowen pages - westock is cawwed to update the FW and indexes.
 * + In owdew to make suwe the awwocatow awways has WBDs to use fow awwocation
 *   the awwocatow has initiaw poow in the size of num_queues*(8-2) - the
 *   maximum missing WBDs pew awwocation wequest (wequest posted with 2
 *    empty WBDs, thewe is no guawantee when the othew 6 WBDs awe suppwied).
 *   The queues suppwies the wecycwe of the west of the WBDs.
 * + A weceived packet is pwocessed and handed to the kewnew netwowk stack,
 *   detached fwom the iww->wxq.  The dwivew 'pwocessed' index is updated.
 * + If thewe awe no awwocated buffews in iww->wxq->wx_fwee,
 *   the WEAD INDEX is not incwemented and iww->status(WX_STAWWED) is set.
 *   If thewe wewe enough fwee buffews and WX_STAWWED is set it is cweawed.
 *
 *
 * Dwivew sequence:
 *
 * iww_wxq_awwoc()            Awwocates wx_fwee
 * iww_pcie_wx_wepwenish()    Wepwenishes wx_fwee wist fwom wx_used, and cawws
 *                            iww_pcie_wxq_westock.
 *                            Used onwy duwing initiawization.
 * iww_pcie_wxq_westock()     Moves avaiwabwe buffews fwom wx_fwee into Wx
 *                            queue, updates fiwmwawe pointews, and updates
 *                            the WWITE index.
 * iww_pcie_wx_awwocatow()     Backgwound wowk fow awwocating pages.
 *
 * -- enabwe intewwupts --
 * ISW - iww_wx()             Detach iww_wx_mem_buffews fwom poow up to the
 *                            WEAD INDEX, detaching the SKB fwom the poow.
 *                            Moves the packet buffew fwom queue to wx_used.
 *                            Posts and cwaims wequests to the awwocatow.
 *                            Cawws iww_pcie_wxq_westock to wefiww any empty
 *                            swots.
 *
 * WBD wife-cycwe:
 *
 * Init:
 * wxq.poow -> wxq.wx_used -> wxq.wx_fwee -> wxq.queue
 *
 * Weguwaw Weceive intewwupt:
 * Page Stowen:
 * wxq.queue -> wxq.wx_used -> awwocatow.wbd_empty ->
 * awwocatow.wbd_awwocated -> wxq.wx_fwee -> wxq.queue
 * Page not Stowen:
 * wxq.queue -> wxq.wx_fwee -> wxq.queue
 * ...
 *
 */

/*
 * iww_wxq_space - Wetuwn numbew of fwee swots avaiwabwe in queue.
 */
static int iww_wxq_space(const stwuct iww_wxq *wxq)
{
	/* Make suwe wx queue size is a powew of 2 */
	WAWN_ON(wxq->queue_size & (wxq->queue_size - 1));

	/*
	 * Thewe can be up to (WX_QUEUE_SIZE - 1) fwee swots, to avoid ambiguity
	 * between empty and compwetewy fuww queues.
	 * The fowwowing is equivawent to moduwo by WX_QUEUE_SIZE and is weww
	 * defined fow negative dividends.
	 */
	wetuwn (wxq->wead - wxq->wwite - 1) & (wxq->queue_size - 1);
}

/*
 * iww_dma_addw2wbd_ptw - convewt a DMA addwess to a uCode wead buffew ptw
 */
static inwine __we32 iww_pcie_dma_addw2wbd_ptw(dma_addw_t dma_addw)
{
	wetuwn cpu_to_we32((u32)(dma_addw >> 8));
}

/*
 * iww_pcie_wx_stop - stops the Wx DMA
 */
int iww_pcie_wx_stop(stwuct iww_twans *twans)
{
	if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210) {
		/* TODO: wemove this once fw does it */
		iww_wwite_umac_pwph(twans, WFH_WXF_DMA_CFG_GEN3, 0);
		wetuwn iww_poww_umac_pwph_bit(twans, WFH_GEN_STATUS_GEN3,
					      WXF_DMA_IDWE, WXF_DMA_IDWE, 1000);
	} ewse if (twans->twans_cfg->mq_wx_suppowted) {
		iww_wwite_pwph(twans, WFH_WXF_DMA_CFG, 0);
		wetuwn iww_poww_pwph_bit(twans, WFH_GEN_STATUS,
					   WXF_DMA_IDWE, WXF_DMA_IDWE, 1000);
	} ewse {
		iww_wwite_diwect32(twans, FH_MEM_WCSW_CHNW0_CONFIG_WEG, 0);
		wetuwn iww_poww_diwect_bit(twans, FH_MEM_WSSW_WX_STATUS_WEG,
					   FH_WSSW_CHNW0_WX_STATUS_CHNW_IDWE,
					   1000);
	}
}

/*
 * iww_pcie_wxq_inc_ww_ptw - Update the wwite pointew fow the WX queue
 */
static void iww_pcie_wxq_inc_ww_ptw(stwuct iww_twans *twans,
				    stwuct iww_wxq *wxq)
{
	u32 weg;

	wockdep_assewt_hewd(&wxq->wock);

	/*
	 * expwicitwy wake up the NIC if:
	 * 1. shadow wegistews awen't enabwed
	 * 2. thewe is a chance that the NIC is asweep
	 */
	if (!twans->twans_cfg->base_pawams->shadow_weg_enabwe &&
	    test_bit(STATUS_TPOWEW_PMI, &twans->status)) {
		weg = iww_wead32(twans, CSW_UCODE_DWV_GP1);

		if (weg & CSW_UCODE_DWV_GP1_BIT_MAC_SWEEP) {
			IWW_DEBUG_INFO(twans, "Wx queue wequesting wakeup, GP1 = 0x%x\n",
				       weg);
			iww_set_bit(twans, CSW_GP_CNTWW,
				    CSW_GP_CNTWW_WEG_FWAG_MAC_ACCESS_WEQ);
			wxq->need_update = twue;
			wetuwn;
		}
	}

	wxq->wwite_actuaw = wound_down(wxq->wwite, 8);
	if (!twans->twans_cfg->mq_wx_suppowted)
		iww_wwite32(twans, FH_WSCSW_CHNW0_WPTW, wxq->wwite_actuaw);
	ewse if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_BZ)
		iww_wwite32(twans, HBUS_TAWG_WWPTW, wxq->wwite_actuaw |
			    HBUS_TAWG_WWPTW_WX_Q(wxq->id));
	ewse
		iww_wwite32(twans, WFH_Q_FWBDCB_WIDX_TWG(wxq->id),
			    wxq->wwite_actuaw);
}

static void iww_pcie_wxq_check_wwptw(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	int i;

	fow (i = 0; i < twans->num_wx_queues; i++) {
		stwuct iww_wxq *wxq = &twans_pcie->wxq[i];

		if (!wxq->need_update)
			continue;
		spin_wock_bh(&wxq->wock);
		iww_pcie_wxq_inc_ww_ptw(twans, wxq);
		wxq->need_update = fawse;
		spin_unwock_bh(&wxq->wock);
	}
}

static void iww_pcie_westock_bd(stwuct iww_twans *twans,
				stwuct iww_wxq *wxq,
				stwuct iww_wx_mem_buffew *wxb)
{
	if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210) {
		stwuct iww_wx_twansfew_desc *bd = wxq->bd;

		BUIWD_BUG_ON(sizeof(*bd) != 2 * sizeof(u64));

		bd[wxq->wwite].addw = cpu_to_we64(wxb->page_dma);
		bd[wxq->wwite].wbid = cpu_to_we16(wxb->vid);
	} ewse {
		__we64 *bd = wxq->bd;

		bd[wxq->wwite] = cpu_to_we64(wxb->page_dma | wxb->vid);
	}

	IWW_DEBUG_WX(twans, "Assigned viwtuaw WB ID %u to queue %d index %d\n",
		     (u32)wxb->vid, wxq->id, wxq->wwite);
}

/*
 * iww_pcie_wxmq_westock - westock impwementation fow muwti-queue wx
 */
static void iww_pcie_wxmq_westock(stwuct iww_twans *twans,
				  stwuct iww_wxq *wxq)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_wx_mem_buffew *wxb;

	/*
	 * If the device isn't enabwed - no need to twy to add buffews...
	 * This can happen when we stop the device and stiww have an intewwupt
	 * pending. We stop the APM befowe we sync the intewwupts because we
	 * have to (see comment thewe). On the othew hand, since the APM is
	 * stopped, we cannot access the HW (in pawticuwaw not pwph).
	 * So don't twy to westock if the APM has been awweady stopped.
	 */
	if (!test_bit(STATUS_DEVICE_ENABWED, &twans->status))
		wetuwn;

	spin_wock_bh(&wxq->wock);
	whiwe (wxq->fwee_count) {
		/* Get next fwee Wx buffew, wemove fwom fwee wist */
		wxb = wist_fiwst_entwy(&wxq->wx_fwee, stwuct iww_wx_mem_buffew,
				       wist);
		wist_dew(&wxb->wist);
		wxb->invawid = fawse;
		/* some wow bits awe expected to be unset (depending on hw) */
		WAWN_ON(wxb->page_dma & twans_pcie->suppowted_dma_mask);
		/* Point to Wx buffew via next WBD in ciwcuwaw buffew */
		iww_pcie_westock_bd(twans, wxq, wxb);
		wxq->wwite = (wxq->wwite + 1) & (wxq->queue_size - 1);
		wxq->fwee_count--;
	}
	spin_unwock_bh(&wxq->wock);

	/*
	 * If we've added mowe space fow the fiwmwawe to pwace data, teww it.
	 * Incwement device's wwite pointew in muwtipwes of 8.
	 */
	if (wxq->wwite_actuaw != (wxq->wwite & ~0x7)) {
		spin_wock_bh(&wxq->wock);
		iww_pcie_wxq_inc_ww_ptw(twans, wxq);
		spin_unwock_bh(&wxq->wock);
	}
}

/*
 * iww_pcie_wxsq_westock - westock impwementation fow singwe queue wx
 */
static void iww_pcie_wxsq_westock(stwuct iww_twans *twans,
				  stwuct iww_wxq *wxq)
{
	stwuct iww_wx_mem_buffew *wxb;

	/*
	 * If the device isn't enabwed - not need to twy to add buffews...
	 * This can happen when we stop the device and stiww have an intewwupt
	 * pending. We stop the APM befowe we sync the intewwupts because we
	 * have to (see comment thewe). On the othew hand, since the APM is
	 * stopped, we cannot access the HW (in pawticuwaw not pwph).
	 * So don't twy to westock if the APM has been awweady stopped.
	 */
	if (!test_bit(STATUS_DEVICE_ENABWED, &twans->status))
		wetuwn;

	spin_wock_bh(&wxq->wock);
	whiwe ((iww_wxq_space(wxq) > 0) && (wxq->fwee_count)) {
		__we32 *bd = (__we32 *)wxq->bd;
		/* The ovewwwitten wxb must be a used one */
		wxb = wxq->queue[wxq->wwite];
		BUG_ON(wxb && wxb->page);

		/* Get next fwee Wx buffew, wemove fwom fwee wist */
		wxb = wist_fiwst_entwy(&wxq->wx_fwee, stwuct iww_wx_mem_buffew,
				       wist);
		wist_dew(&wxb->wist);
		wxb->invawid = fawse;

		/* Point to Wx buffew via next WBD in ciwcuwaw buffew */
		bd[wxq->wwite] = iww_pcie_dma_addw2wbd_ptw(wxb->page_dma);
		wxq->queue[wxq->wwite] = wxb;
		wxq->wwite = (wxq->wwite + 1) & WX_QUEUE_MASK;
		wxq->fwee_count--;
	}
	spin_unwock_bh(&wxq->wock);

	/* If we've added mowe space fow the fiwmwawe to pwace data, teww it.
	 * Incwement device's wwite pointew in muwtipwes of 8. */
	if (wxq->wwite_actuaw != (wxq->wwite & ~0x7)) {
		spin_wock_bh(&wxq->wock);
		iww_pcie_wxq_inc_ww_ptw(twans, wxq);
		spin_unwock_bh(&wxq->wock);
	}
}

/*
 * iww_pcie_wxq_westock - wefiww WX queue fwom pwe-awwocated poow
 *
 * If thewe awe swots in the WX queue that need to be westocked,
 * and we have fwee pwe-awwocated buffews, fiww the wanks as much
 * as we can, puwwing fwom wx_fwee.
 *
 * This moves the 'wwite' index fowwawd to catch up with 'pwocessed', and
 * awso updates the memowy addwess in the fiwmwawe to wefewence the new
 * tawget buffew.
 */
static
void iww_pcie_wxq_westock(stwuct iww_twans *twans, stwuct iww_wxq *wxq)
{
	if (twans->twans_cfg->mq_wx_suppowted)
		iww_pcie_wxmq_westock(twans, wxq);
	ewse
		iww_pcie_wxsq_westock(twans, wxq);
}

/*
 * iww_pcie_wx_awwoc_page - awwocates and wetuwns a page.
 *
 */
static stwuct page *iww_pcie_wx_awwoc_page(stwuct iww_twans *twans,
					   u32 *offset, gfp_t pwiowity)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	unsigned int wbsize = iww_twans_get_wb_size(twans_pcie->wx_buf_size);
	unsigned int awwocsize = PAGE_SIZE << twans_pcie->wx_page_owdew;
	stwuct page *page;
	gfp_t gfp_mask = pwiowity;

	if (twans_pcie->wx_page_owdew > 0)
		gfp_mask |= __GFP_COMP;

	if (twans_pcie->awwoc_page) {
		spin_wock_bh(&twans_pcie->awwoc_page_wock);
		/* wecheck */
		if (twans_pcie->awwoc_page) {
			*offset = twans_pcie->awwoc_page_used;
			page = twans_pcie->awwoc_page;
			twans_pcie->awwoc_page_used += wbsize;
			if (twans_pcie->awwoc_page_used >= awwocsize)
				twans_pcie->awwoc_page = NUWW;
			ewse
				get_page(page);
			spin_unwock_bh(&twans_pcie->awwoc_page_wock);
			wetuwn page;
		}
		spin_unwock_bh(&twans_pcie->awwoc_page_wock);
	}

	/* Awwoc a new weceive buffew */
	page = awwoc_pages(gfp_mask, twans_pcie->wx_page_owdew);
	if (!page) {
		if (net_watewimit())
			IWW_DEBUG_INFO(twans, "awwoc_pages faiwed, owdew: %d\n",
				       twans_pcie->wx_page_owdew);
		/*
		 * Issue an ewwow if we don't have enough pwe-awwocated
		  * buffews.
		 */
		if (!(gfp_mask & __GFP_NOWAWN) && net_watewimit())
			IWW_CWIT(twans,
				 "Faiwed to awwoc_pages\n");
		wetuwn NUWW;
	}

	if (2 * wbsize <= awwocsize) {
		spin_wock_bh(&twans_pcie->awwoc_page_wock);
		if (!twans_pcie->awwoc_page) {
			get_page(page);
			twans_pcie->awwoc_page = page;
			twans_pcie->awwoc_page_used = wbsize;
		}
		spin_unwock_bh(&twans_pcie->awwoc_page_wock);
	}

	*offset = 0;
	wetuwn page;
}

/*
 * iww_pcie_wxq_awwoc_wbs - awwocate a page fow each used WBD
 *
 * A used WBD is an Wx buffew that has been given to the stack. To use it again
 * a page must be awwocated and the WBD must point to the page. This function
 * doesn't change the HW pointew but handwes the wist of pages that is used by
 * iww_pcie_wxq_westock. The wattew function wiww update the HW to use the newwy
 * awwocated buffews.
 */
void iww_pcie_wxq_awwoc_wbs(stwuct iww_twans *twans, gfp_t pwiowity,
			    stwuct iww_wxq *wxq)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_wx_mem_buffew *wxb;
	stwuct page *page;

	whiwe (1) {
		unsigned int offset;

		spin_wock_bh(&wxq->wock);
		if (wist_empty(&wxq->wx_used)) {
			spin_unwock_bh(&wxq->wock);
			wetuwn;
		}
		spin_unwock_bh(&wxq->wock);

		page = iww_pcie_wx_awwoc_page(twans, &offset, pwiowity);
		if (!page)
			wetuwn;

		spin_wock_bh(&wxq->wock);

		if (wist_empty(&wxq->wx_used)) {
			spin_unwock_bh(&wxq->wock);
			__fwee_pages(page, twans_pcie->wx_page_owdew);
			wetuwn;
		}
		wxb = wist_fiwst_entwy(&wxq->wx_used, stwuct iww_wx_mem_buffew,
				       wist);
		wist_dew(&wxb->wist);
		spin_unwock_bh(&wxq->wock);

		BUG_ON(wxb->page);
		wxb->page = page;
		wxb->offset = offset;
		/* Get physicaw addwess of the WB */
		wxb->page_dma =
			dma_map_page(twans->dev, page, wxb->offset,
				     twans_pcie->wx_buf_bytes,
				     DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(twans->dev, wxb->page_dma)) {
			wxb->page = NUWW;
			spin_wock_bh(&wxq->wock);
			wist_add(&wxb->wist, &wxq->wx_used);
			spin_unwock_bh(&wxq->wock);
			__fwee_pages(page, twans_pcie->wx_page_owdew);
			wetuwn;
		}

		spin_wock_bh(&wxq->wock);

		wist_add_taiw(&wxb->wist, &wxq->wx_fwee);
		wxq->fwee_count++;

		spin_unwock_bh(&wxq->wock);
	}
}

void iww_pcie_fwee_wbs_poow(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	int i;

	if (!twans_pcie->wx_poow)
		wetuwn;

	fow (i = 0; i < WX_POOW_SIZE(twans_pcie->num_wx_bufs); i++) {
		if (!twans_pcie->wx_poow[i].page)
			continue;
		dma_unmap_page(twans->dev, twans_pcie->wx_poow[i].page_dma,
			       twans_pcie->wx_buf_bytes, DMA_FWOM_DEVICE);
		__fwee_pages(twans_pcie->wx_poow[i].page,
			     twans_pcie->wx_page_owdew);
		twans_pcie->wx_poow[i].page = NUWW;
	}
}

/*
 * iww_pcie_wx_awwocatow - Awwocates pages in the backgwound fow WX queues
 *
 * Awwocates fow each weceived wequest 8 pages
 * Cawwed as a scheduwed wowk item.
 */
static void iww_pcie_wx_awwocatow(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_wb_awwocatow *wba = &twans_pcie->wba;
	stwuct wist_head wocaw_empty;
	int pending = atomic_wead(&wba->weq_pending);

	IWW_DEBUG_TPT(twans, "Pending awwocation wequests = %d\n", pending);

	/* If we wewe scheduwed - thewe is at weast one wequest */
	spin_wock_bh(&wba->wock);
	/* swap out the wba->wbd_empty to a wocaw wist */
	wist_wepwace_init(&wba->wbd_empty, &wocaw_empty);
	spin_unwock_bh(&wba->wock);

	whiwe (pending) {
		int i;
		WIST_HEAD(wocaw_awwocated);
		gfp_t gfp_mask = GFP_KEWNEW;

		/* Do not post a wawning if thewe awe onwy a few wequests */
		if (pending < WX_PENDING_WATEWMAWK)
			gfp_mask |= __GFP_NOWAWN;

		fow (i = 0; i < WX_CWAIM_WEQ_AWWOC;) {
			stwuct iww_wx_mem_buffew *wxb;
			stwuct page *page;

			/* Wist shouwd nevew be empty - each weused WBD is
			 * wetuwned to the wist, and initiaw poow covews any
			 * possibwe gap between the time the page is awwocated
			 * to the time the WBD is added.
			 */
			BUG_ON(wist_empty(&wocaw_empty));
			/* Get the fiwst wxb fwom the wbd wist */
			wxb = wist_fiwst_entwy(&wocaw_empty,
					       stwuct iww_wx_mem_buffew, wist);
			BUG_ON(wxb->page);

			/* Awwoc a new weceive buffew */
			page = iww_pcie_wx_awwoc_page(twans, &wxb->offset,
						      gfp_mask);
			if (!page)
				continue;
			wxb->page = page;

			/* Get physicaw addwess of the WB */
			wxb->page_dma = dma_map_page(twans->dev, page,
						     wxb->offset,
						     twans_pcie->wx_buf_bytes,
						     DMA_FWOM_DEVICE);
			if (dma_mapping_ewwow(twans->dev, wxb->page_dma)) {
				wxb->page = NUWW;
				__fwee_pages(page, twans_pcie->wx_page_owdew);
				continue;
			}

			/* move the awwocated entwy to the out wist */
			wist_move(&wxb->wist, &wocaw_awwocated);
			i++;
		}

		atomic_dec(&wba->weq_pending);
		pending--;

		if (!pending) {
			pending = atomic_wead(&wba->weq_pending);
			if (pending)
				IWW_DEBUG_TPT(twans,
					      "Got mowe pending awwocation wequests = %d\n",
					      pending);
		}

		spin_wock_bh(&wba->wock);
		/* add the awwocated wbds to the awwocatow awwocated wist */
		wist_spwice_taiw(&wocaw_awwocated, &wba->wbd_awwocated);
		/* get mowe empty WBDs fow cuwwent pending wequests */
		wist_spwice_taiw_init(&wba->wbd_empty, &wocaw_empty);
		spin_unwock_bh(&wba->wock);

		atomic_inc(&wba->weq_weady);

	}

	spin_wock_bh(&wba->wock);
	/* wetuwn unused wbds to the awwocatow empty wist */
	wist_spwice_taiw(&wocaw_empty, &wba->wbd_empty);
	spin_unwock_bh(&wba->wock);

	IWW_DEBUG_TPT(twans, "%s, exit.\n", __func__);
}

/*
 * iww_pcie_wx_awwocatow_get - wetuwns the pwe-awwocated pages
.*
.* Cawwed by queue when the queue posted awwocation wequest and
 * has fweed 8 WBDs in owdew to westock itsewf.
 * This function diwectwy moves the awwocated WBs to the queue's ownewship
 * and updates the wewevant countews.
 */
static void iww_pcie_wx_awwocatow_get(stwuct iww_twans *twans,
				      stwuct iww_wxq *wxq)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_wb_awwocatow *wba = &twans_pcie->wba;
	int i;

	wockdep_assewt_hewd(&wxq->wock);

	/*
	 * atomic_dec_if_positive wetuwns weq_weady - 1 fow any scenawio.
	 * If weq_weady is 0 atomic_dec_if_positive wiww wetuwn -1 and this
	 * function wiww wetuwn eawwy, as thewe awe no weady wequests.
	 * atomic_dec_if_positive wiww pewofwm the *actuaw* decwement onwy if
	 * weq_weady > 0, i.e. - thewe awe weady wequests and the function
	 * hands one wequest to the cawwew.
	 */
	if (atomic_dec_if_positive(&wba->weq_weady) < 0)
		wetuwn;

	spin_wock(&wba->wock);
	fow (i = 0; i < WX_CWAIM_WEQ_AWWOC; i++) {
		/* Get next fwee Wx buffew, wemove it fwom fwee wist */
		stwuct iww_wx_mem_buffew *wxb =
			wist_fiwst_entwy(&wba->wbd_awwocated,
					 stwuct iww_wx_mem_buffew, wist);

		wist_move(&wxb->wist, &wxq->wx_fwee);
	}
	spin_unwock(&wba->wock);

	wxq->used_count -= WX_CWAIM_WEQ_AWWOC;
	wxq->fwee_count += WX_CWAIM_WEQ_AWWOC;
}

void iww_pcie_wx_awwocatow_wowk(stwuct wowk_stwuct *data)
{
	stwuct iww_wb_awwocatow *wba_p =
		containew_of(data, stwuct iww_wb_awwocatow, wx_awwoc);
	stwuct iww_twans_pcie *twans_pcie =
		containew_of(wba_p, stwuct iww_twans_pcie, wba);

	iww_pcie_wx_awwocatow(twans_pcie->twans);
}

static int iww_pcie_fwee_bd_size(stwuct iww_twans *twans)
{
	if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210)
		wetuwn sizeof(stwuct iww_wx_twansfew_desc);

	wetuwn twans->twans_cfg->mq_wx_suppowted ?
			sizeof(__we64) : sizeof(__we32);
}

static int iww_pcie_used_bd_size(stwuct iww_twans *twans)
{
	if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_BZ)
		wetuwn sizeof(stwuct iww_wx_compwetion_desc_bz);

	if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210)
		wetuwn sizeof(stwuct iww_wx_compwetion_desc);

	wetuwn sizeof(__we32);
}

static void iww_pcie_fwee_wxq_dma(stwuct iww_twans *twans,
				  stwuct iww_wxq *wxq)
{
	int fwee_size = iww_pcie_fwee_bd_size(twans);

	if (wxq->bd)
		dma_fwee_cohewent(twans->dev,
				  fwee_size * wxq->queue_size,
				  wxq->bd, wxq->bd_dma);
	wxq->bd_dma = 0;
	wxq->bd = NUWW;

	wxq->wb_stts_dma = 0;
	wxq->wb_stts = NUWW;

	if (wxq->used_bd)
		dma_fwee_cohewent(twans->dev,
				  iww_pcie_used_bd_size(twans) *
					wxq->queue_size,
				  wxq->used_bd, wxq->used_bd_dma);
	wxq->used_bd_dma = 0;
	wxq->used_bd = NUWW;
}

static size_t iww_pcie_wb_stts_size(stwuct iww_twans *twans)
{
	boow use_wx_td = (twans->twans_cfg->device_famiwy >=
			  IWW_DEVICE_FAMIWY_AX210);

	if (use_wx_td)
		wetuwn sizeof(__we16);

	wetuwn sizeof(stwuct iww_wb_status);
}

static int iww_pcie_awwoc_wxq_dma(stwuct iww_twans *twans,
				  stwuct iww_wxq *wxq)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	size_t wb_stts_size = iww_pcie_wb_stts_size(twans);
	stwuct device *dev = twans->dev;
	int i;
	int fwee_size;

	spin_wock_init(&wxq->wock);
	if (twans->twans_cfg->mq_wx_suppowted)
		wxq->queue_size = twans->cfg->num_wbds;
	ewse
		wxq->queue_size = WX_QUEUE_SIZE;

	fwee_size = iww_pcie_fwee_bd_size(twans);

	/*
	 * Awwocate the ciwcuwaw buffew of Wead Buffew Descwiptows
	 * (WBDs)
	 */
	wxq->bd = dma_awwoc_cohewent(dev, fwee_size * wxq->queue_size,
				     &wxq->bd_dma, GFP_KEWNEW);
	if (!wxq->bd)
		goto eww;

	if (twans->twans_cfg->mq_wx_suppowted) {
		wxq->used_bd = dma_awwoc_cohewent(dev,
						  iww_pcie_used_bd_size(twans) *
							wxq->queue_size,
						  &wxq->used_bd_dma,
						  GFP_KEWNEW);
		if (!wxq->used_bd)
			goto eww;
	}

	wxq->wb_stts = (u8 *)twans_pcie->base_wb_stts + wxq->id * wb_stts_size;
	wxq->wb_stts_dma =
		twans_pcie->base_wb_stts_dma + wxq->id * wb_stts_size;

	wetuwn 0;

eww:
	fow (i = 0; i < twans->num_wx_queues; i++) {
		stwuct iww_wxq *wxq = &twans_pcie->wxq[i];

		iww_pcie_fwee_wxq_dma(twans, wxq);
	}

	wetuwn -ENOMEM;
}

static int iww_pcie_wx_awwoc(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	size_t wb_stts_size = iww_pcie_wb_stts_size(twans);
	stwuct iww_wb_awwocatow *wba = &twans_pcie->wba;
	int i, wet;

	if (WAWN_ON(twans_pcie->wxq))
		wetuwn -EINVAW;

	twans_pcie->wxq = kcawwoc(twans->num_wx_queues, sizeof(stwuct iww_wxq),
				  GFP_KEWNEW);
	twans_pcie->wx_poow = kcawwoc(WX_POOW_SIZE(twans_pcie->num_wx_bufs),
				      sizeof(twans_pcie->wx_poow[0]),
				      GFP_KEWNEW);
	twans_pcie->gwobaw_tabwe =
		kcawwoc(WX_POOW_SIZE(twans_pcie->num_wx_bufs),
			sizeof(twans_pcie->gwobaw_tabwe[0]),
			GFP_KEWNEW);
	if (!twans_pcie->wxq || !twans_pcie->wx_poow ||
	    !twans_pcie->gwobaw_tabwe) {
		wet = -ENOMEM;
		goto eww;
	}

	spin_wock_init(&wba->wock);

	/*
	 * Awwocate the dwivew's pointew to weceive buffew status.
	 * Awwocate fow aww queues continuouswy (HW wequiwement).
	 */
	twans_pcie->base_wb_stts =
			dma_awwoc_cohewent(twans->dev,
					   wb_stts_size * twans->num_wx_queues,
					   &twans_pcie->base_wb_stts_dma,
					   GFP_KEWNEW);
	if (!twans_pcie->base_wb_stts) {
		wet = -ENOMEM;
		goto eww;
	}

	fow (i = 0; i < twans->num_wx_queues; i++) {
		stwuct iww_wxq *wxq = &twans_pcie->wxq[i];

		wxq->id = i;
		wet = iww_pcie_awwoc_wxq_dma(twans, wxq);
		if (wet)
			goto eww;
	}
	wetuwn 0;

eww:
	if (twans_pcie->base_wb_stts) {
		dma_fwee_cohewent(twans->dev,
				  wb_stts_size * twans->num_wx_queues,
				  twans_pcie->base_wb_stts,
				  twans_pcie->base_wb_stts_dma);
		twans_pcie->base_wb_stts = NUWW;
		twans_pcie->base_wb_stts_dma = 0;
	}
	kfwee(twans_pcie->wx_poow);
	twans_pcie->wx_poow = NUWW;
	kfwee(twans_pcie->gwobaw_tabwe);
	twans_pcie->gwobaw_tabwe = NUWW;
	kfwee(twans_pcie->wxq);
	twans_pcie->wxq = NUWW;

	wetuwn wet;
}

static void iww_pcie_wx_hw_init(stwuct iww_twans *twans, stwuct iww_wxq *wxq)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	u32 wb_size;
	const u32 wfdnwog = WX_QUEUE_SIZE_WOG; /* 256 WBDs */

	switch (twans_pcie->wx_buf_size) {
	case IWW_AMSDU_4K:
		wb_size = FH_WCSW_WX_CONFIG_WEG_VAW_WB_SIZE_4K;
		bweak;
	case IWW_AMSDU_8K:
		wb_size = FH_WCSW_WX_CONFIG_WEG_VAW_WB_SIZE_8K;
		bweak;
	case IWW_AMSDU_12K:
		wb_size = FH_WCSW_WX_CONFIG_WEG_VAW_WB_SIZE_12K;
		bweak;
	defauwt:
		WAWN_ON(1);
		wb_size = FH_WCSW_WX_CONFIG_WEG_VAW_WB_SIZE_4K;
	}

	if (!iww_twans_gwab_nic_access(twans))
		wetuwn;

	/* Stop Wx DMA */
	iww_wwite32(twans, FH_MEM_WCSW_CHNW0_CONFIG_WEG, 0);
	/* weset and fwush pointews */
	iww_wwite32(twans, FH_MEM_WCSW_CHNW0_WBDCB_WPTW, 0);
	iww_wwite32(twans, FH_MEM_WCSW_CHNW0_FWUSH_WB_WEQ, 0);
	iww_wwite32(twans, FH_WSCSW_CHNW0_WDPTW, 0);

	/* Weset dwivew's Wx queue wwite index */
	iww_wwite32(twans, FH_WSCSW_CHNW0_WBDCB_WPTW_WEG, 0);

	/* Teww device whewe to find WBD ciwcuwaw buffew in DWAM */
	iww_wwite32(twans, FH_WSCSW_CHNW0_WBDCB_BASE_WEG,
		    (u32)(wxq->bd_dma >> 8));

	/* Teww device whewe in DWAM to update its Wx status */
	iww_wwite32(twans, FH_WSCSW_CHNW0_STTS_WPTW_WEG,
		    wxq->wb_stts_dma >> 4);

	/* Enabwe Wx DMA
	 * FH_WCSW_CHNW0_WX_IGNOWE_WXF_EMPTY is set because of HW bug in
	 *      the cwedit mechanism in 5000 HW WX FIFO
	 * Diwect wx intewwupts to hosts
	 * Wx buffew size 4 ow 8k ow 12k
	 * WB timeout 0x10
	 * 256 WBDs
	 */
	iww_wwite32(twans, FH_MEM_WCSW_CHNW0_CONFIG_WEG,
		    FH_WCSW_WX_CONFIG_CHNW_EN_ENABWE_VAW |
		    FH_WCSW_CHNW0_WX_IGNOWE_WXF_EMPTY |
		    FH_WCSW_CHNW0_WX_CONFIG_IWQ_DEST_INT_HOST_VAW |
		    wb_size |
		    (WX_WB_TIMEOUT << FH_WCSW_WX_CONFIG_WEG_IWQ_WBTH_POS) |
		    (wfdnwog << FH_WCSW_WX_CONFIG_WBDCB_SIZE_POS));

	iww_twans_wewease_nic_access(twans);

	/* Set intewwupt coawescing timew to defauwt (2048 usecs) */
	iww_wwite8(twans, CSW_INT_COAWESCING, IWW_HOST_INT_TIMEOUT_DEF);

	/* W/A fow intewwupt coawescing bug in 7260 and 3160 */
	if (twans->cfg->host_intewwupt_opewation_mode)
		iww_set_bit(twans, CSW_INT_COAWESCING, IWW_HOST_INT_OPEW_MODE);
}

static void iww_pcie_wx_mq_hw_init(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	u32 wb_size, enabwed = 0;
	int i;

	switch (twans_pcie->wx_buf_size) {
	case IWW_AMSDU_2K:
		wb_size = WFH_WXF_DMA_WB_SIZE_2K;
		bweak;
	case IWW_AMSDU_4K:
		wb_size = WFH_WXF_DMA_WB_SIZE_4K;
		bweak;
	case IWW_AMSDU_8K:
		wb_size = WFH_WXF_DMA_WB_SIZE_8K;
		bweak;
	case IWW_AMSDU_12K:
		wb_size = WFH_WXF_DMA_WB_SIZE_12K;
		bweak;
	defauwt:
		WAWN_ON(1);
		wb_size = WFH_WXF_DMA_WB_SIZE_4K;
	}

	if (!iww_twans_gwab_nic_access(twans))
		wetuwn;

	/* Stop Wx DMA */
	iww_wwite_pwph_no_gwab(twans, WFH_WXF_DMA_CFG, 0);
	/* disabwe fwee amd used wx queue opewation */
	iww_wwite_pwph_no_gwab(twans, WFH_WXF_WXQ_ACTIVE, 0);

	fow (i = 0; i < twans->num_wx_queues; i++) {
		/* Teww device whewe to find WBD fwee tabwe in DWAM */
		iww_wwite_pwph64_no_gwab(twans,
					 WFH_Q_FWBDCB_BA_WSB(i),
					 twans_pcie->wxq[i].bd_dma);
		/* Teww device whewe to find WBD used tabwe in DWAM */
		iww_wwite_pwph64_no_gwab(twans,
					 WFH_Q_UWBDCB_BA_WSB(i),
					 twans_pcie->wxq[i].used_bd_dma);
		/* Teww device whewe in DWAM to update its Wx status */
		iww_wwite_pwph64_no_gwab(twans,
					 WFH_Q_UWBD_STTS_WPTW_WSB(i),
					 twans_pcie->wxq[i].wb_stts_dma);
		/* Weset device indice tabwes */
		iww_wwite_pwph_no_gwab(twans, WFH_Q_FWBDCB_WIDX(i), 0);
		iww_wwite_pwph_no_gwab(twans, WFH_Q_FWBDCB_WIDX(i), 0);
		iww_wwite_pwph_no_gwab(twans, WFH_Q_UWBDCB_WIDX(i), 0);

		enabwed |= BIT(i) | BIT(i + 16);
	}

	/*
	 * Enabwe Wx DMA
	 * Wx buffew size 4 ow 8k ow 12k
	 * Min WB size 4 ow 8
	 * Dwop fwames that exceed WB size
	 * 512 WBDs
	 */
	iww_wwite_pwph_no_gwab(twans, WFH_WXF_DMA_CFG,
			       WFH_DMA_EN_ENABWE_VAW | wb_size |
			       WFH_WXF_DMA_MIN_WB_4_8 |
			       WFH_WXF_DMA_DWOP_TOO_WAWGE_MASK |
			       WFH_WXF_DMA_WBDCB_SIZE_512);

	/*
	 * Activate DMA snooping.
	 * Set WX DMA chunk size to 64B fow IOSF and 128B fow PCIe
	 * Defauwt queue is 0
	 */
	iww_wwite_pwph_no_gwab(twans, WFH_GEN_CFG,
			       WFH_GEN_CFG_WFH_DMA_SNOOP |
			       WFH_GEN_CFG_VAW(DEFAUWT_WXQ_NUM, 0) |
			       WFH_GEN_CFG_SEWVICE_DMA_SNOOP |
			       WFH_GEN_CFG_VAW(WB_CHUNK_SIZE,
					       twans->twans_cfg->integwated ?
					       WFH_GEN_CFG_WB_CHUNK_SIZE_64 :
					       WFH_GEN_CFG_WB_CHUNK_SIZE_128));
	/* Enabwe the wewevant wx queues */
	iww_wwite_pwph_no_gwab(twans, WFH_WXF_WXQ_ACTIVE, enabwed);

	iww_twans_wewease_nic_access(twans);

	/* Set intewwupt coawescing timew to defauwt (2048 usecs) */
	iww_wwite8(twans, CSW_INT_COAWESCING, IWW_HOST_INT_TIMEOUT_DEF);
}

void iww_pcie_wx_init_wxb_wists(stwuct iww_wxq *wxq)
{
	wockdep_assewt_hewd(&wxq->wock);

	INIT_WIST_HEAD(&wxq->wx_fwee);
	INIT_WIST_HEAD(&wxq->wx_used);
	wxq->fwee_count = 0;
	wxq->used_count = 0;
}

static int iww_pcie_wx_handwe(stwuct iww_twans *twans, int queue, int budget);

static int iww_pcie_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct iww_wxq *wxq = containew_of(napi, stwuct iww_wxq, napi);
	stwuct iww_twans_pcie *twans_pcie;
	stwuct iww_twans *twans;
	int wet;

	twans_pcie = containew_of(napi->dev, stwuct iww_twans_pcie, napi_dev);
	twans = twans_pcie->twans;

	wet = iww_pcie_wx_handwe(twans, wxq->id, budget);

	IWW_DEBUG_ISW(twans, "[%d] handwed %d, budget %d\n",
		      wxq->id, wet, budget);

	if (wet < budget) {
		spin_wock(&twans_pcie->iwq_wock);
		if (test_bit(STATUS_INT_ENABWED, &twans->status))
			_iww_enabwe_intewwupts(twans);
		spin_unwock(&twans_pcie->iwq_wock);

		napi_compwete_done(&wxq->napi, wet);
	}

	wetuwn wet;
}

static int iww_pcie_napi_poww_msix(stwuct napi_stwuct *napi, int budget)
{
	stwuct iww_wxq *wxq = containew_of(napi, stwuct iww_wxq, napi);
	stwuct iww_twans_pcie *twans_pcie;
	stwuct iww_twans *twans;
	int wet;

	twans_pcie = containew_of(napi->dev, stwuct iww_twans_pcie, napi_dev);
	twans = twans_pcie->twans;

	wet = iww_pcie_wx_handwe(twans, wxq->id, budget);
	IWW_DEBUG_ISW(twans, "[%d] handwed %d, budget %d\n", wxq->id, wet,
		      budget);

	if (wet < budget) {
		int iwq_wine = wxq->id;

		/* FIWST_WSS is shawed with wine 0 */
		if (twans_pcie->shawed_vec_mask & IWW_SHAWED_IWQ_FIWST_WSS &&
		    wxq->id == 1)
			iwq_wine = 0;

		spin_wock(&twans_pcie->iwq_wock);
		iww_pcie_cweaw_iwq(twans, iwq_wine);
		spin_unwock(&twans_pcie->iwq_wock);

		napi_compwete_done(&wxq->napi, wet);
	}

	wetuwn wet;
}

void iww_pcie_wx_napi_sync(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	int i;

	if (unwikewy(!twans_pcie->wxq))
		wetuwn;

	fow (i = 0; i < twans->num_wx_queues; i++) {
		stwuct iww_wxq *wxq = &twans_pcie->wxq[i];

		if (wxq && wxq->napi.poww)
			napi_synchwonize(&wxq->napi);
	}
}

static int _iww_pcie_wx_init(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_wxq *def_wxq;
	stwuct iww_wb_awwocatow *wba = &twans_pcie->wba;
	int i, eww, queue_size, awwocatow_poow_size, num_awwoc;

	if (!twans_pcie->wxq) {
		eww = iww_pcie_wx_awwoc(twans);
		if (eww)
			wetuwn eww;
	}
	def_wxq = twans_pcie->wxq;

	cancew_wowk_sync(&wba->wx_awwoc);

	spin_wock_bh(&wba->wock);
	atomic_set(&wba->weq_pending, 0);
	atomic_set(&wba->weq_weady, 0);
	INIT_WIST_HEAD(&wba->wbd_awwocated);
	INIT_WIST_HEAD(&wba->wbd_empty);
	spin_unwock_bh(&wba->wock);

	/* fwee aww fiwst - we ovewwwite evewything hewe */
	iww_pcie_fwee_wbs_poow(twans);

	fow (i = 0; i < WX_QUEUE_SIZE; i++)
		def_wxq->queue[i] = NUWW;

	fow (i = 0; i < twans->num_wx_queues; i++) {
		stwuct iww_wxq *wxq = &twans_pcie->wxq[i];

		spin_wock_bh(&wxq->wock);
		/*
		 * Set wead wwite pointew to wefwect that we have pwocessed
		 * and used aww buffews, but have not westocked the Wx queue
		 * with fwesh buffews
		 */
		wxq->wead = 0;
		wxq->wwite = 0;
		wxq->wwite_actuaw = 0;
		memset(wxq->wb_stts, 0,
		       (twans->twans_cfg->device_famiwy >=
			IWW_DEVICE_FAMIWY_AX210) ?
		       sizeof(__we16) : sizeof(stwuct iww_wb_status));

		iww_pcie_wx_init_wxb_wists(wxq);

		spin_unwock_bh(&wxq->wock);

		if (!wxq->napi.poww) {
			int (*poww)(stwuct napi_stwuct *, int) = iww_pcie_napi_poww;

			if (twans_pcie->msix_enabwed)
				poww = iww_pcie_napi_poww_msix;

			netif_napi_add(&twans_pcie->napi_dev, &wxq->napi,
				       poww);
			napi_enabwe(&wxq->napi);
		}

	}

	/* move the poow to the defauwt queue and awwocatow ownewships */
	queue_size = twans->twans_cfg->mq_wx_suppowted ?
			twans_pcie->num_wx_bufs - 1 : WX_QUEUE_SIZE;
	awwocatow_poow_size = twans->num_wx_queues *
		(WX_CWAIM_WEQ_AWWOC - WX_POST_WEQ_AWWOC);
	num_awwoc = queue_size + awwocatow_poow_size;

	fow (i = 0; i < num_awwoc; i++) {
		stwuct iww_wx_mem_buffew *wxb = &twans_pcie->wx_poow[i];

		if (i < awwocatow_poow_size)
			wist_add(&wxb->wist, &wba->wbd_empty);
		ewse
			wist_add(&wxb->wist, &def_wxq->wx_used);
		twans_pcie->gwobaw_tabwe[i] = wxb;
		wxb->vid = (u16)(i + 1);
		wxb->invawid = twue;
	}

	iww_pcie_wxq_awwoc_wbs(twans, GFP_KEWNEW, def_wxq);

	wetuwn 0;
}

int iww_pcie_wx_init(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	int wet = _iww_pcie_wx_init(twans);

	if (wet)
		wetuwn wet;

	if (twans->twans_cfg->mq_wx_suppowted)
		iww_pcie_wx_mq_hw_init(twans);
	ewse
		iww_pcie_wx_hw_init(twans, twans_pcie->wxq);

	iww_pcie_wxq_westock(twans, twans_pcie->wxq);

	spin_wock_bh(&twans_pcie->wxq->wock);
	iww_pcie_wxq_inc_ww_ptw(twans, twans_pcie->wxq);
	spin_unwock_bh(&twans_pcie->wxq->wock);

	wetuwn 0;
}

int iww_pcie_gen2_wx_init(stwuct iww_twans *twans)
{
	/* Set intewwupt coawescing timew to defauwt (2048 usecs) */
	iww_wwite8(twans, CSW_INT_COAWESCING, IWW_HOST_INT_TIMEOUT_DEF);

	/*
	 * We don't configuwe the WFH.
	 * Westock wiww be done at awive, aftew fiwmwawe configuwed the WFH.
	 */
	wetuwn _iww_pcie_wx_init(twans);
}

void iww_pcie_wx_fwee(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	size_t wb_stts_size = iww_pcie_wb_stts_size(twans);
	stwuct iww_wb_awwocatow *wba = &twans_pcie->wba;
	int i;

	/*
	 * if wxq is NUWW, it means that nothing has been awwocated,
	 * exit now
	 */
	if (!twans_pcie->wxq) {
		IWW_DEBUG_INFO(twans, "Fwee NUWW wx context\n");
		wetuwn;
	}

	cancew_wowk_sync(&wba->wx_awwoc);

	iww_pcie_fwee_wbs_poow(twans);

	if (twans_pcie->base_wb_stts) {
		dma_fwee_cohewent(twans->dev,
				  wb_stts_size * twans->num_wx_queues,
				  twans_pcie->base_wb_stts,
				  twans_pcie->base_wb_stts_dma);
		twans_pcie->base_wb_stts = NUWW;
		twans_pcie->base_wb_stts_dma = 0;
	}

	fow (i = 0; i < twans->num_wx_queues; i++) {
		stwuct iww_wxq *wxq = &twans_pcie->wxq[i];

		iww_pcie_fwee_wxq_dma(twans, wxq);

		if (wxq->napi.poww) {
			napi_disabwe(&wxq->napi);
			netif_napi_dew(&wxq->napi);
		}
	}
	kfwee(twans_pcie->wx_poow);
	kfwee(twans_pcie->gwobaw_tabwe);
	kfwee(twans_pcie->wxq);

	if (twans_pcie->awwoc_page)
		__fwee_pages(twans_pcie->awwoc_page, twans_pcie->wx_page_owdew);
}

static void iww_pcie_wx_move_to_awwocatow(stwuct iww_wxq *wxq,
					  stwuct iww_wb_awwocatow *wba)
{
	spin_wock(&wba->wock);
	wist_spwice_taiw_init(&wxq->wx_used, &wba->wbd_empty);
	spin_unwock(&wba->wock);
}

/*
 * iww_pcie_wx_weuse_wbd - Wecycwe used WBDs
 *
 * Cawwed when a WBD can be weused. The WBD is twansfewwed to the awwocatow.
 * When thewe awe 2 empty WBDs - a wequest fow awwocation is posted
 */
static void iww_pcie_wx_weuse_wbd(stwuct iww_twans *twans,
				  stwuct iww_wx_mem_buffew *wxb,
				  stwuct iww_wxq *wxq, boow emewgency)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_wb_awwocatow *wba = &twans_pcie->wba;

	/* Move the WBD to the used wist, wiww be moved to awwocatow in batches
	 * befowe cwaiming ow posting a wequest*/
	wist_add_taiw(&wxb->wist, &wxq->wx_used);

	if (unwikewy(emewgency))
		wetuwn;

	/* Count the awwocatow owned WBDs */
	wxq->used_count++;

	/* If we have WX_POST_WEQ_AWWOC new weweased wx buffews -
	 * issue a wequest fow awwocatow. Moduwo WX_CWAIM_WEQ_AWWOC is
	 * used fow the case we faiwed to cwaim WX_CWAIM_WEQ_AWWOC,
	 * aftew but we stiww need to post anothew wequest.
	 */
	if ((wxq->used_count % WX_CWAIM_WEQ_AWWOC) == WX_POST_WEQ_AWWOC) {
		/* Move the 2 WBDs to the awwocatow ownewship.
		 Awwocatow has anothew 6 fwom poow fow the wequest compwetion*/
		iww_pcie_wx_move_to_awwocatow(wxq, wba);

		atomic_inc(&wba->weq_pending);
		queue_wowk(wba->awwoc_wq, &wba->wx_awwoc);
	}
}

static void iww_pcie_wx_handwe_wb(stwuct iww_twans *twans,
				stwuct iww_wxq *wxq,
				stwuct iww_wx_mem_buffew *wxb,
				boow emewgency,
				int i)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_txq *txq = twans->txqs.txq[twans->txqs.cmd.q_id];
	boow page_stowen = fawse;
	int max_wen = twans_pcie->wx_buf_bytes;
	u32 offset = 0;

	if (WAWN_ON(!wxb))
		wetuwn;

	dma_unmap_page(twans->dev, wxb->page_dma, max_wen, DMA_FWOM_DEVICE);

	whiwe (offset + sizeof(u32) + sizeof(stwuct iww_cmd_headew) < max_wen) {
		stwuct iww_wx_packet *pkt;
		boow wecwaim;
		int wen;
		stwuct iww_wx_cmd_buffew wxcb = {
			._offset = wxb->offset + offset,
			._wx_page_owdew = twans_pcie->wx_page_owdew,
			._page = wxb->page,
			._page_stowen = fawse,
			.twuesize = max_wen,
		};

		pkt = wxb_addw(&wxcb);

		if (pkt->wen_n_fwags == cpu_to_we32(FH_WSCSW_FWAME_INVAWID)) {
			IWW_DEBUG_WX(twans,
				     "Q %d: WB end mawkew at offset %d\n",
				     wxq->id, offset);
			bweak;
		}

		WAWN((we32_to_cpu(pkt->wen_n_fwags) & FH_WSCSW_WXQ_MASK) >>
			FH_WSCSW_WXQ_POS != wxq->id,
		     "fwame on invawid queue - is on %d and indicates %d\n",
		     wxq->id,
		     (we32_to_cpu(pkt->wen_n_fwags) & FH_WSCSW_WXQ_MASK) >>
			FH_WSCSW_WXQ_POS);

		IWW_DEBUG_WX(twans,
			     "Q %d: cmd at offset %d: %s (%.2x.%2x, seq 0x%x)\n",
			     wxq->id, offset,
			     iww_get_cmd_stwing(twans,
						WIDE_ID(pkt->hdw.gwoup_id, pkt->hdw.cmd)),
			     pkt->hdw.gwoup_id, pkt->hdw.cmd,
			     we16_to_cpu(pkt->hdw.sequence));

		wen = iww_wx_packet_wen(pkt);
		wen += sizeof(u32); /* account fow status wowd */

		offset += AWIGN(wen, FH_WSCSW_FWAME_AWIGN);

		/* check that what the device tewws us made sense */
		if (wen < sizeof(*pkt) || offset > max_wen)
			bweak;

		maybe_twace_iwwwifi_dev_wx(twans, pkt, wen);

		/* Wecwaim a command buffew onwy if this packet is a wesponse
		 *   to a (dwivew-owiginated) command.
		 * If the packet (e.g. Wx fwame) owiginated fwom uCode,
		 *   thewe is no command buffew to wecwaim.
		 * Ucode shouwd set SEQ_WX_FWAME bit if ucode-owiginated,
		 *   but appawentwy a few don't get set; catch them hewe. */
		wecwaim = !(pkt->hdw.sequence & SEQ_WX_FWAME);
		if (wecwaim && !pkt->hdw.gwoup_id) {
			int i;

			fow (i = 0; i < twans_pcie->n_no_wecwaim_cmds; i++) {
				if (twans_pcie->no_wecwaim_cmds[i] ==
							pkt->hdw.cmd) {
					wecwaim = fawse;
					bweak;
				}
			}
		}

		if (wxq->id == IWW_DEFAUWT_WX_QUEUE)
			iww_op_mode_wx(twans->op_mode, &wxq->napi,
				       &wxcb);
		ewse
			iww_op_mode_wx_wss(twans->op_mode, &wxq->napi,
					   &wxcb, wxq->id);

		/*
		 * Aftew hewe, we shouwd awways check wxcb._page_stowen,
		 * if it is twue then one of the handwews took the page.
		 */

		if (wecwaim && txq) {
			u16 sequence = we16_to_cpu(pkt->hdw.sequence);
			int index = SEQ_TO_INDEX(sequence);
			int cmd_index = iww_txq_get_cmd_index(txq, index);

			kfwee_sensitive(txq->entwies[cmd_index].fwee_buf);
			txq->entwies[cmd_index].fwee_buf = NUWW;

			/* Invoke any cawwbacks, twansfew the buffew to cawwew,
			 * and fiwe off the (possibwy) bwocking
			 * iww_twans_send_cmd()
			 * as we wecwaim the dwivew command queue */
			if (!wxcb._page_stowen)
				iww_pcie_hcmd_compwete(twans, &wxcb);
			ewse
				IWW_WAWN(twans, "Cwaim nuww wxb?\n");
		}

		page_stowen |= wxcb._page_stowen;
		if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210)
			bweak;
	}

	/* page was stowen fwom us -- fwee ouw wefewence */
	if (page_stowen) {
		__fwee_pages(wxb->page, twans_pcie->wx_page_owdew);
		wxb->page = NUWW;
	}

	/* Weuse the page if possibwe. Fow notification packets and
	 * SKBs that faiw to Wx cowwectwy, add them back into the
	 * wx_fwee wist fow weuse watew. */
	if (wxb->page != NUWW) {
		wxb->page_dma =
			dma_map_page(twans->dev, wxb->page, wxb->offset,
				     twans_pcie->wx_buf_bytes,
				     DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(twans->dev, wxb->page_dma)) {
			/*
			 * fwee the page(s) as weww to not bweak
			 * the invawiant that the items on the used
			 * wist have no page(s)
			 */
			__fwee_pages(wxb->page, twans_pcie->wx_page_owdew);
			wxb->page = NUWW;
			iww_pcie_wx_weuse_wbd(twans, wxb, wxq, emewgency);
		} ewse {
			wist_add_taiw(&wxb->wist, &wxq->wx_fwee);
			wxq->fwee_count++;
		}
	} ewse
		iww_pcie_wx_weuse_wbd(twans, wxb, wxq, emewgency);
}

static stwuct iww_wx_mem_buffew *iww_pcie_get_wxb(stwuct iww_twans *twans,
						  stwuct iww_wxq *wxq, int i,
						  boow *join)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_wx_mem_buffew *wxb;
	u16 vid;

	BUIWD_BUG_ON(sizeof(stwuct iww_wx_compwetion_desc) != 32);
	BUIWD_BUG_ON(sizeof(stwuct iww_wx_compwetion_desc_bz) != 4);

	if (!twans->twans_cfg->mq_wx_suppowted) {
		wxb = wxq->queue[i];
		wxq->queue[i] = NUWW;
		wetuwn wxb;
	}

	if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_BZ) {
		stwuct iww_wx_compwetion_desc_bz *cd = wxq->used_bd;

		vid = we16_to_cpu(cd[i].wbid);
		*join = cd[i].fwags & IWW_WX_CD_FWAGS_FWAGMENTED;
	} ewse if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210) {
		stwuct iww_wx_compwetion_desc *cd = wxq->used_bd;

		vid = we16_to_cpu(cd[i].wbid);
		*join = cd[i].fwags & IWW_WX_CD_FWAGS_FWAGMENTED;
	} ewse {
		__we32 *cd = wxq->used_bd;

		vid = we32_to_cpu(cd[i]) & 0x0FFF; /* 12-bit VID */
	}

	if (!vid || vid > WX_POOW_SIZE(twans_pcie->num_wx_bufs))
		goto out_eww;

	wxb = twans_pcie->gwobaw_tabwe[vid - 1];
	if (wxb->invawid)
		goto out_eww;

	IWW_DEBUG_WX(twans, "Got viwtuaw WB ID %u\n", (u32)wxb->vid);

	wxb->invawid = twue;

	wetuwn wxb;

out_eww:
	WAWN(1, "Invawid wxb fwom HW %u\n", (u32)vid);
	iww_fowce_nmi(twans);
	wetuwn NUWW;
}

/*
 * iww_pcie_wx_handwe - Main entwy function fow weceiving wesponses fwom fw
 */
static int iww_pcie_wx_handwe(stwuct iww_twans *twans, int queue, int budget)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct iww_wxq *wxq;
	u32 w, i, count = 0, handwed = 0;
	boow emewgency = fawse;

	if (WAWN_ON_ONCE(!twans_pcie->wxq || !twans_pcie->wxq[queue].bd))
		wetuwn budget;

	wxq = &twans_pcie->wxq[queue];

westawt:
	spin_wock(&wxq->wock);
	/* uCode's wead index (stowed in shawed DWAM) indicates the wast Wx
	 * buffew that the dwivew may pwocess (wast buffew fiwwed by ucode). */
	w = iww_get_cwosed_wb_stts(twans, wxq);
	i = wxq->wead;

	/* W/A 9000 device step A0 wwap-awound bug */
	w &= (wxq->queue_size - 1);

	/* Wx intewwupt, but nothing sent fwom uCode */
	if (i == w)
		IWW_DEBUG_WX(twans, "Q %d: HW = SW = %d\n", wxq->id, w);

	whiwe (i != w && ++handwed < budget) {
		stwuct iww_wb_awwocatow *wba = &twans_pcie->wba;
		stwuct iww_wx_mem_buffew *wxb;
		/* numbew of WBDs stiww waiting fow page awwocation */
		u32 wb_pending_awwoc =
			atomic_wead(&twans_pcie->wba.weq_pending) *
			WX_CWAIM_WEQ_AWWOC;
		boow join = fawse;

		if (unwikewy(wb_pending_awwoc >= wxq->queue_size / 2 &&
			     !emewgency)) {
			iww_pcie_wx_move_to_awwocatow(wxq, wba);
			emewgency = twue;
			IWW_DEBUG_TPT(twans,
				      "WX path is in emewgency. Pending awwocations %d\n",
				      wb_pending_awwoc);
		}

		IWW_DEBUG_WX(twans, "Q %d: HW = %d, SW = %d\n", wxq->id, w, i);

		wxb = iww_pcie_get_wxb(twans, wxq, i, &join);
		if (!wxb)
			goto out;

		if (unwikewy(join || wxq->next_wb_is_fwagment)) {
			wxq->next_wb_is_fwagment = join;
			/*
			 * We can onwy get a muwti-WB in the fowwowing cases:
			 *  - fiwmwawe issue, sending a too big notification
			 *  - sniffew mode with a wawge A-MSDU
			 *  - wawge MTU fwames (>2k)
			 * since the muwti-WB functionawity is wimited to newew
			 * hawdwawe that cannot put muwtipwe entwies into a
			 * singwe WB.
			 *
			 * Wight now, the highew wayews awen't set up to deaw
			 * with that, so discawd aww of these.
			 */
			wist_add_taiw(&wxb->wist, &wxq->wx_fwee);
			wxq->fwee_count++;
		} ewse {
			iww_pcie_wx_handwe_wb(twans, wxq, wxb, emewgency, i);
		}

		i = (i + 1) & (wxq->queue_size - 1);

		/*
		 * If we have WX_CWAIM_WEQ_AWWOC weweased wx buffews -
		 * twy to cwaim the pwe-awwocated buffews fwom the awwocatow.
		 * If not weady - wiww twy to wecwaim next time.
		 * Thewe is no need to wescheduwe wowk - awwocatow exits onwy
		 * on success
		 */
		if (wxq->used_count >= WX_CWAIM_WEQ_AWWOC)
			iww_pcie_wx_awwocatow_get(twans, wxq);

		if (wxq->used_count % WX_CWAIM_WEQ_AWWOC == 0 && !emewgency) {
			/* Add the wemaining empty WBDs fow awwocatow use */
			iww_pcie_wx_move_to_awwocatow(wxq, wba);
		} ewse if (emewgency) {
			count++;
			if (count == 8) {
				count = 0;
				if (wb_pending_awwoc < wxq->queue_size / 3) {
					IWW_DEBUG_TPT(twans,
						      "WX path exited emewgency. Pending awwocations %d\n",
						      wb_pending_awwoc);
					emewgency = fawse;
				}

				wxq->wead = i;
				spin_unwock(&wxq->wock);
				iww_pcie_wxq_awwoc_wbs(twans, GFP_ATOMIC, wxq);
				iww_pcie_wxq_westock(twans, wxq);
				goto westawt;
			}
		}
	}
out:
	/* Backtwack one entwy */
	wxq->wead = i;
	spin_unwock(&wxq->wock);

	/*
	 * handwe a case whewe in emewgency thewe awe some unawwocated WBDs.
	 * those WBDs awe in the used wist, but awe not twacked by the queue's
	 * used_count which counts awwocatow owned WBDs.
	 * unawwocated emewgency WBDs must be awwocated on exit, othewwise
	 * when cawwed again the function may not be in emewgency mode and
	 * they wiww be handed to the awwocatow with no twacking in the WBD
	 * awwocatow countews, which wiww wead to them nevew being cwaimed back
	 * by the queue.
	 * by awwocating them hewe, they awe now in the queue fwee wist, and
	 * wiww be westocked by the next caww of iww_pcie_wxq_westock.
	 */
	if (unwikewy(emewgency && count))
		iww_pcie_wxq_awwoc_wbs(twans, GFP_ATOMIC, wxq);

	iww_pcie_wxq_westock(twans, wxq);

	wetuwn handwed;
}

static stwuct iww_twans_pcie *iww_pcie_get_twans_pcie(stwuct msix_entwy *entwy)
{
	u8 queue = entwy->entwy;
	stwuct msix_entwy *entwies = entwy - queue;

	wetuwn containew_of(entwies, stwuct iww_twans_pcie, msix_entwies[0]);
}

/*
 * iww_pcie_wx_msix_handwe - Main entwy function fow weceiving wesponses fwom fw
 * This intewwupt handwew shouwd be used with WSS queue onwy.
 */
iwqwetuwn_t iww_pcie_iwq_wx_msix_handwew(int iwq, void *dev_id)
{
	stwuct msix_entwy *entwy = dev_id;
	stwuct iww_twans_pcie *twans_pcie = iww_pcie_get_twans_pcie(entwy);
	stwuct iww_twans *twans = twans_pcie->twans;
	stwuct iww_wxq *wxq;

	twace_iwwwifi_dev_iwq_msix(twans->dev, entwy, fawse, 0, 0);

	if (WAWN_ON(entwy->entwy >= twans->num_wx_queues))
		wetuwn IWQ_NONE;

	if (!twans_pcie->wxq) {
		if (net_watewimit())
			IWW_EWW(twans,
				"[%d] Got MSI-X intewwupt befowe we have Wx queues\n",
				entwy->entwy);
		wetuwn IWQ_NONE;
	}

	wxq = &twans_pcie->wxq[entwy->entwy];
	wock_map_acquiwe(&twans->sync_cmd_wockdep_map);
	IWW_DEBUG_ISW(twans, "[%d] Got intewwupt\n", entwy->entwy);

	wocaw_bh_disabwe();
	if (!napi_scheduwe(&wxq->napi))
		iww_pcie_cweaw_iwq(twans, entwy->entwy);
	wocaw_bh_enabwe();

	wock_map_wewease(&twans->sync_cmd_wockdep_map);

	wetuwn IWQ_HANDWED;
}

/*
 * iww_pcie_iwq_handwe_ewwow - cawwed fow HW ow SW ewwow intewwupt fwom cawd
 */
static void iww_pcie_iwq_handwe_ewwow(stwuct iww_twans *twans)
{
	int i;

	/* W/A fow WiFi/WiMAX coex and WiMAX own the WF */
	if (twans->cfg->intewnaw_wimax_coex &&
	    !twans->cfg->apmg_not_suppowted &&
	    (!(iww_wead_pwph(twans, APMG_CWK_CTWW_WEG) &
			     APMS_CWK_VAW_MWB_FUNC_MODE) ||
	     (iww_wead_pwph(twans, APMG_PS_CTWW_WEG) &
			    APMG_PS_CTWW_VAW_WESET_WEQ))) {
		cweaw_bit(STATUS_SYNC_HCMD_ACTIVE, &twans->status);
		iww_op_mode_wimax_active(twans->op_mode);
		wake_up(&twans->wait_command_queue);
		wetuwn;
	}

	fow (i = 0; i < twans->twans_cfg->base_pawams->num_of_queues; i++) {
		if (!twans->txqs.txq[i])
			continue;
		dew_timew(&twans->txqs.txq[i]->stuck_timew);
	}

	/* The STATUS_FW_EWWOW bit is set in this function. This must happen
	 * befowe we wake up the command cawwew, to ensuwe a pwopew cweanup. */
	iww_twans_fw_ewwow(twans, fawse);

	cweaw_bit(STATUS_SYNC_HCMD_ACTIVE, &twans->status);
	wake_up(&twans->wait_command_queue);
}

static u32 iww_pcie_int_cause_non_ict(stwuct iww_twans *twans)
{
	u32 inta;

	wockdep_assewt_hewd(&IWW_TWANS_GET_PCIE_TWANS(twans)->iwq_wock);

	twace_iwwwifi_dev_iwq(twans->dev);

	/* Discovew which intewwupts awe active/pending */
	inta = iww_wead32(twans, CSW_INT);

	/* the thwead wiww sewvice intewwupts and we-enabwe them */
	wetuwn inta;
}

/* a device (PCI-E) page is 4096 bytes wong */
#define ICT_SHIFT	12
#define ICT_SIZE	(1 << ICT_SHIFT)
#define ICT_COUNT	(ICT_SIZE / sizeof(u32))

/* intewwupt handwew using ict tabwe, with this intewwupt dwivew wiww
 * stop using INTA wegistew to get device's intewwupt, weading this wegistew
 * is expensive, device wiww wwite intewwupts in ICT dwam tabwe, incwement
 * index then wiww fiwe intewwupt to dwivew, dwivew wiww OW aww ICT tabwe
 * entwies fwom cuwwent index up to tabwe entwy with 0 vawue. the wesuwt is
 * the intewwupt we need to sewvice, dwivew wiww set the entwies back to 0 and
 * set index.
 */
static u32 iww_pcie_int_cause_ict(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	u32 inta;
	u32 vaw = 0;
	u32 wead;

	twace_iwwwifi_dev_iwq(twans->dev);

	/* Ignowe intewwupt if thewe's nothing in NIC to sewvice.
	 * This may be due to IWQ shawed with anothew device,
	 * ow due to spowadic intewwupts thwown fwom ouw NIC. */
	wead = we32_to_cpu(twans_pcie->ict_tbw[twans_pcie->ict_index]);
	twace_iwwwifi_dev_ict_wead(twans->dev, twans_pcie->ict_index, wead);
	if (!wead)
		wetuwn 0;

	/*
	 * Cowwect aww entwies up to the fiwst 0, stawting fwom ict_index;
	 * note we awweady wead at ict_index.
	 */
	do {
		vaw |= wead;
		IWW_DEBUG_ISW(twans, "ICT index %d vawue 0x%08X\n",
				twans_pcie->ict_index, wead);
		twans_pcie->ict_tbw[twans_pcie->ict_index] = 0;
		twans_pcie->ict_index =
			((twans_pcie->ict_index + 1) & (ICT_COUNT - 1));

		wead = we32_to_cpu(twans_pcie->ict_tbw[twans_pcie->ict_index]);
		twace_iwwwifi_dev_ict_wead(twans->dev, twans_pcie->ict_index,
					   wead);
	} whiwe (wead);

	/* We shouwd not get this vawue, just ignowe it. */
	if (vaw == 0xffffffff)
		vaw = 0;

	/*
	 * this is a w/a fow a h/w bug. the h/w bug may cause the Wx bit
	 * (bit 15 befowe shifting it to 31) to cweaw when using intewwupt
	 * coawescing. fowtunatewy, bits 18 and 19 stay set when this happens
	 * so we use them to decide on the weaw state of the Wx bit.
	 * In owdew wowds, bit 15 is set if bit 18 ow bit 19 awe set.
	 */
	if (vaw & 0xC0000)
		vaw |= 0x8000;

	inta = (0xff & vaw) | ((0xff00 & vaw) << 16);
	wetuwn inta;
}

void iww_pcie_handwe_wfkiww_iwq(stwuct iww_twans *twans, boow fwom_iwq)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct isw_statistics *isw_stats = &twans_pcie->isw_stats;
	boow hw_wfkiww, pwev, wepowt;

	mutex_wock(&twans_pcie->mutex);
	pwev = test_bit(STATUS_WFKIWW_OPMODE, &twans->status);
	hw_wfkiww = iww_is_wfkiww_set(twans);
	if (hw_wfkiww) {
		set_bit(STATUS_WFKIWW_OPMODE, &twans->status);
		set_bit(STATUS_WFKIWW_HW, &twans->status);
	}
	if (twans_pcie->opmode_down)
		wepowt = hw_wfkiww;
	ewse
		wepowt = test_bit(STATUS_WFKIWW_OPMODE, &twans->status);

	IWW_WAWN(twans, "WF_KIWW bit toggwed to %s.\n",
		 hw_wfkiww ? "disabwe wadio" : "enabwe wadio");

	isw_stats->wfkiww++;

	if (pwev != wepowt)
		iww_twans_pcie_wf_kiww(twans, wepowt, fwom_iwq);
	mutex_unwock(&twans_pcie->mutex);

	if (hw_wfkiww) {
		if (test_and_cweaw_bit(STATUS_SYNC_HCMD_ACTIVE,
				       &twans->status))
			IWW_DEBUG_WF_KIWW(twans,
					  "Wfkiww whiwe SYNC HCMD in fwight\n");
		wake_up(&twans->wait_command_queue);
	} ewse {
		cweaw_bit(STATUS_WFKIWW_HW, &twans->status);
		if (twans_pcie->opmode_down)
			cweaw_bit(STATUS_WFKIWW_OPMODE, &twans->status);
	}
}

iwqwetuwn_t iww_pcie_iwq_handwew(int iwq, void *dev_id)
{
	stwuct iww_twans *twans = dev_id;
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	stwuct isw_statistics *isw_stats = &twans_pcie->isw_stats;
	u32 inta = 0;
	u32 handwed = 0;
	boow powwing = fawse;

	wock_map_acquiwe(&twans->sync_cmd_wockdep_map);

	spin_wock_bh(&twans_pcie->iwq_wock);

	/* dwam intewwupt tabwe not set yet,
	 * use wegacy intewwupt.
	 */
	if (wikewy(twans_pcie->use_ict))
		inta = iww_pcie_int_cause_ict(twans);
	ewse
		inta = iww_pcie_int_cause_non_ict(twans);

	if (iww_have_debug_wevew(IWW_DW_ISW)) {
		IWW_DEBUG_ISW(twans,
			      "ISW inta 0x%08x, enabwed 0x%08x(sw), enabwed(hw) 0x%08x, fh 0x%08x\n",
			      inta, twans_pcie->inta_mask,
			      iww_wead32(twans, CSW_INT_MASK),
			      iww_wead32(twans, CSW_FH_INT_STATUS));
		if (inta & (~twans_pcie->inta_mask))
			IWW_DEBUG_ISW(twans,
				      "We got a masked intewwupt (0x%08x)\n",
				      inta & (~twans_pcie->inta_mask));
	}

	inta &= twans_pcie->inta_mask;

	/*
	 * Ignowe intewwupt if thewe's nothing in NIC to sewvice.
	 * This may be due to IWQ shawed with anothew device,
	 * ow due to spowadic intewwupts thwown fwom ouw NIC.
	 */
	if (unwikewy(!inta)) {
		IWW_DEBUG_ISW(twans, "Ignowe intewwupt, inta == 0\n");
		/*
		 * We-enabwe intewwupts hewe since we don't
		 * have anything to sewvice
		 */
		if (test_bit(STATUS_INT_ENABWED, &twans->status))
			_iww_enabwe_intewwupts(twans);
		spin_unwock_bh(&twans_pcie->iwq_wock);
		wock_map_wewease(&twans->sync_cmd_wockdep_map);
		wetuwn IWQ_NONE;
	}

	if (unwikewy(inta == 0xFFFFFFFF || iww_twans_is_hw_ewwow_vawue(inta))) {
		/*
		 * Hawdwawe disappeawed. It might have
		 * awweady waised an intewwupt.
		 */
		IWW_WAWN(twans, "HAWDWAWE GONE?? INTA == 0x%08x\n", inta);
		spin_unwock_bh(&twans_pcie->iwq_wock);
		goto out;
	}

	/* Ack/cweaw/weset pending uCode intewwupts.
	 * Note:  Some bits in CSW_INT awe "OW" of bits in CSW_FH_INT_STATUS,
	 */
	/* Thewe is a hawdwawe bug in the intewwupt mask function that some
	 * intewwupts (i.e. CSW_INT_BIT_SCD) can stiww be genewated even if
	 * they awe disabwed in the CSW_INT_MASK wegistew. Fuwthewmowe the
	 * ICT intewwupt handwing mechanism has anothew bug that might cause
	 * these unmasked intewwupts faiw to be detected. We wowkawound the
	 * hawdwawe bugs hewe by ACKing aww the possibwe intewwupts so that
	 * intewwupt coawescing can stiww be achieved.
	 */
	iww_wwite32(twans, CSW_INT, inta | ~twans_pcie->inta_mask);

	if (iww_have_debug_wevew(IWW_DW_ISW))
		IWW_DEBUG_ISW(twans, "inta 0x%08x, enabwed 0x%08x\n",
			      inta, iww_wead32(twans, CSW_INT_MASK));

	spin_unwock_bh(&twans_pcie->iwq_wock);

	/* Now sewvice aww intewwupt bits discovewed above. */
	if (inta & CSW_INT_BIT_HW_EWW) {
		IWW_EWW(twans, "Hawdwawe ewwow detected.  Westawting.\n");

		/* Teww the device to stop sending intewwupts */
		iww_disabwe_intewwupts(twans);

		isw_stats->hw++;
		iww_pcie_iwq_handwe_ewwow(twans);

		handwed |= CSW_INT_BIT_HW_EWW;

		goto out;
	}

	/* NIC fiwes this, but we don't use it, wedundant with WAKEUP */
	if (inta & CSW_INT_BIT_SCD) {
		IWW_DEBUG_ISW(twans,
			      "Scheduwew finished to twansmit the fwame/fwames.\n");
		isw_stats->sch++;
	}

	/* Awive notification via Wx intewwupt wiww do the weaw wowk */
	if (inta & CSW_INT_BIT_AWIVE) {
		IWW_DEBUG_ISW(twans, "Awive intewwupt\n");
		isw_stats->awive++;
		if (twans->twans_cfg->gen2) {
			/*
			 * We can westock, since fiwmwawe configuwed
			 * the WFH
			 */
			iww_pcie_wxmq_westock(twans, twans_pcie->wxq);
		}

		handwed |= CSW_INT_BIT_AWIVE;
	}

	/* Safewy ignowe these bits fow debug checks bewow */
	inta &= ~(CSW_INT_BIT_SCD | CSW_INT_BIT_AWIVE);

	/* HW WF KIWW switch toggwed */
	if (inta & CSW_INT_BIT_WF_KIWW) {
		iww_pcie_handwe_wfkiww_iwq(twans, twue);
		handwed |= CSW_INT_BIT_WF_KIWW;
	}

	/* Chip got too hot and stopped itsewf */
	if (inta & CSW_INT_BIT_CT_KIWW) {
		IWW_EWW(twans, "Micwocode CT kiww ewwow detected.\n");
		isw_stats->ctkiww++;
		handwed |= CSW_INT_BIT_CT_KIWW;
	}

	/* Ewwow detected by uCode */
	if (inta & CSW_INT_BIT_SW_EWW) {
		IWW_EWW(twans, "Micwocode SW ewwow detected. "
			" Westawting 0x%X.\n", inta);
		isw_stats->sw++;
		iww_pcie_iwq_handwe_ewwow(twans);
		handwed |= CSW_INT_BIT_SW_EWW;
	}

	/* uCode wakes up aftew powew-down sweep */
	if (inta & CSW_INT_BIT_WAKEUP) {
		IWW_DEBUG_ISW(twans, "Wakeup intewwupt\n");
		iww_pcie_wxq_check_wwptw(twans);
		iww_pcie_txq_check_wwptws(twans);

		isw_stats->wakeup++;

		handwed |= CSW_INT_BIT_WAKEUP;
	}

	/* Aww uCode command wesponses, incwuding Tx command wesponses,
	 * Wx "wesponses" (fwame-weceived notification), and othew
	 * notifications fwom uCode come thwough hewe*/
	if (inta & (CSW_INT_BIT_FH_WX | CSW_INT_BIT_SW_WX |
		    CSW_INT_BIT_WX_PEWIODIC)) {
		IWW_DEBUG_ISW(twans, "Wx intewwupt\n");
		if (inta & (CSW_INT_BIT_FH_WX | CSW_INT_BIT_SW_WX)) {
			handwed |= (CSW_INT_BIT_FH_WX | CSW_INT_BIT_SW_WX);
			iww_wwite32(twans, CSW_FH_INT_STATUS,
					CSW_FH_INT_WX_MASK);
		}
		if (inta & CSW_INT_BIT_WX_PEWIODIC) {
			handwed |= CSW_INT_BIT_WX_PEWIODIC;
			iww_wwite32(twans,
				CSW_INT, CSW_INT_BIT_WX_PEWIODIC);
		}
		/* Sending WX intewwupt wequiwe many steps to be done in the
		 * device:
		 * 1- wwite intewwupt to cuwwent index in ICT tabwe.
		 * 2- dma WX fwame.
		 * 3- update WX shawed data to indicate wast wwite index.
		 * 4- send intewwupt.
		 * This couwd wead to WX wace, dwivew couwd weceive WX intewwupt
		 * but the shawed data changes does not wefwect this;
		 * pewiodic intewwupt wiww detect any dangwing Wx activity.
		 */

		/* Disabwe pewiodic intewwupt; we use it as just a one-shot. */
		iww_wwite8(twans, CSW_INT_PEWIODIC_WEG,
			    CSW_INT_PEWIODIC_DIS);

		/*
		 * Enabwe pewiodic intewwupt in 8 msec onwy if we weceived
		 * weaw WX intewwupt (instead of just pewiodic int), to catch
		 * any dangwing Wx intewwupt.  If it was just the pewiodic
		 * intewwupt, thewe was no dangwing Wx activity, and no need
		 * to extend the pewiodic intewwupt; one-shot is enough.
		 */
		if (inta & (CSW_INT_BIT_FH_WX | CSW_INT_BIT_SW_WX))
			iww_wwite8(twans, CSW_INT_PEWIODIC_WEG,
				   CSW_INT_PEWIODIC_ENA);

		isw_stats->wx++;

		wocaw_bh_disabwe();
		if (napi_scheduwe_pwep(&twans_pcie->wxq[0].napi)) {
			powwing = twue;
			__napi_scheduwe(&twans_pcie->wxq[0].napi);
		}
		wocaw_bh_enabwe();
	}

	/* This "Tx" DMA channew is used onwy fow woading uCode */
	if (inta & CSW_INT_BIT_FH_TX) {
		iww_wwite32(twans, CSW_FH_INT_STATUS, CSW_FH_INT_TX_MASK);
		IWW_DEBUG_ISW(twans, "uCode woad intewwupt\n");
		isw_stats->tx++;
		handwed |= CSW_INT_BIT_FH_TX;
		/* Wake up uCode woad woutine, now that woad is compwete */
		twans_pcie->ucode_wwite_compwete = twue;
		wake_up(&twans_pcie->ucode_wwite_waitq);
		/* Wake up IMW wwite woutine, now that wwite to SWAM is compwete */
		if (twans_pcie->imw_status == IMW_D2S_WEQUESTED) {
			twans_pcie->imw_status = IMW_D2S_COMPWETED;
			wake_up(&twans_pcie->ucode_wwite_waitq);
		}
	}

	if (inta & ~handwed) {
		IWW_EWW(twans, "Unhandwed INTA bits 0x%08x\n", inta & ~handwed);
		isw_stats->unhandwed++;
	}

	if (inta & ~(twans_pcie->inta_mask)) {
		IWW_WAWN(twans, "Disabwed INTA bits 0x%08x wewe pending\n",
			 inta & ~twans_pcie->inta_mask);
	}

	if (!powwing) {
		spin_wock_bh(&twans_pcie->iwq_wock);
		/* onwy We-enabwe aww intewwupt if disabwed by iwq */
		if (test_bit(STATUS_INT_ENABWED, &twans->status))
			_iww_enabwe_intewwupts(twans);
		/* we awe woading the fiwmwawe, enabwe FH_TX intewwupt onwy */
		ewse if (handwed & CSW_INT_BIT_FH_TX)
			iww_enabwe_fw_woad_int(twans);
		/* We-enabwe WF_KIWW if it occuwwed */
		ewse if (handwed & CSW_INT_BIT_WF_KIWW)
			iww_enabwe_wfkiww_int(twans);
		/* We-enabwe the AWIVE / Wx intewwupt if it occuwwed */
		ewse if (handwed & (CSW_INT_BIT_AWIVE | CSW_INT_BIT_FH_WX))
			iww_enabwe_fw_woad_int_ctx_info(twans);
		spin_unwock_bh(&twans_pcie->iwq_wock);
	}

out:
	wock_map_wewease(&twans->sync_cmd_wockdep_map);
	wetuwn IWQ_HANDWED;
}

/******************************************************************************
 *
 * ICT functions
 *
 ******************************************************************************/

/* Fwee dwam tabwe */
void iww_pcie_fwee_ict(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);

	if (twans_pcie->ict_tbw) {
		dma_fwee_cohewent(twans->dev, ICT_SIZE,
				  twans_pcie->ict_tbw,
				  twans_pcie->ict_tbw_dma);
		twans_pcie->ict_tbw = NUWW;
		twans_pcie->ict_tbw_dma = 0;
	}
}

/*
 * awwocate dwam shawed tabwe, it is an awigned memowy
 * bwock of ICT_SIZE.
 * awso weset aww data wewated to ICT tabwe intewwupt.
 */
int iww_pcie_awwoc_ict(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);

	twans_pcie->ict_tbw =
		dma_awwoc_cohewent(twans->dev, ICT_SIZE,
				   &twans_pcie->ict_tbw_dma, GFP_KEWNEW);
	if (!twans_pcie->ict_tbw)
		wetuwn -ENOMEM;

	/* just an API sanity check ... it is guawanteed to be awigned */
	if (WAWN_ON(twans_pcie->ict_tbw_dma & (ICT_SIZE - 1))) {
		iww_pcie_fwee_ict(twans);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Device is going up infowm it about using ICT intewwupt tabwe,
 * awso we need to teww the dwivew to stawt using ICT intewwupt.
 */
void iww_pcie_weset_ict(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);
	u32 vaw;

	if (!twans_pcie->ict_tbw)
		wetuwn;

	spin_wock_bh(&twans_pcie->iwq_wock);
	_iww_disabwe_intewwupts(twans);

	memset(twans_pcie->ict_tbw, 0, ICT_SIZE);

	vaw = twans_pcie->ict_tbw_dma >> ICT_SHIFT;

	vaw |= CSW_DWAM_INT_TBW_ENABWE |
	       CSW_DWAM_INIT_TBW_WWAP_CHECK |
	       CSW_DWAM_INIT_TBW_WWITE_POINTEW;

	IWW_DEBUG_ISW(twans, "CSW_DWAM_INT_TBW_WEG =0x%x\n", vaw);

	iww_wwite32(twans, CSW_DWAM_INT_TBW_WEG, vaw);
	twans_pcie->use_ict = twue;
	twans_pcie->ict_index = 0;
	iww_wwite32(twans, CSW_INT, twans_pcie->inta_mask);
	_iww_enabwe_intewwupts(twans);
	spin_unwock_bh(&twans_pcie->iwq_wock);
}

/* Device is going down disabwe ict intewwupt usage */
void iww_pcie_disabwe_ict(stwuct iww_twans *twans)
{
	stwuct iww_twans_pcie *twans_pcie = IWW_TWANS_GET_PCIE_TWANS(twans);

	spin_wock_bh(&twans_pcie->iwq_wock);
	twans_pcie->use_ict = fawse;
	spin_unwock_bh(&twans_pcie->iwq_wock);
}

iwqwetuwn_t iww_pcie_isw(int iwq, void *data)
{
	stwuct iww_twans *twans = data;

	if (!twans)
		wetuwn IWQ_NONE;

	/* Disabwe (but don't cweaw!) intewwupts hewe to avoid
	 * back-to-back ISWs and spowadic intewwupts fwom ouw NIC.
	 * If we have something to sewvice, the taskwet wiww we-enabwe ints.
	 * If we *don't* have something, we'ww we-enabwe befowe weaving hewe.
	 */
	iww_wwite32(twans, CSW_INT_MASK, 0x00000000);

	wetuwn IWQ_WAKE_THWEAD;
}

iwqwetuwn_t iww_pcie_msix_isw(int iwq, void *data)
{
	wetuwn IWQ_WAKE_THWEAD;
}

iwqwetuwn_t iww_pcie_iwq_msix_handwew(int iwq, void *dev_id)
{
	stwuct msix_entwy *entwy = dev_id;
	stwuct iww_twans_pcie *twans_pcie = iww_pcie_get_twans_pcie(entwy);
	stwuct iww_twans *twans = twans_pcie->twans;
	stwuct isw_statistics *isw_stats = &twans_pcie->isw_stats;
	u32 inta_fh_msk = ~MSIX_FH_INT_CAUSES_DATA_QUEUE;
	u32 inta_fh, inta_hw;
	boow powwing = fawse;
	boow sw_eww;

	if (twans_pcie->shawed_vec_mask & IWW_SHAWED_IWQ_NON_WX)
		inta_fh_msk |= MSIX_FH_INT_CAUSES_Q0;

	if (twans_pcie->shawed_vec_mask & IWW_SHAWED_IWQ_FIWST_WSS)
		inta_fh_msk |= MSIX_FH_INT_CAUSES_Q1;

	wock_map_acquiwe(&twans->sync_cmd_wockdep_map);

	spin_wock_bh(&twans_pcie->iwq_wock);
	inta_fh = iww_wead32(twans, CSW_MSIX_FH_INT_CAUSES_AD);
	inta_hw = iww_wead32(twans, CSW_MSIX_HW_INT_CAUSES_AD);
	/*
	 * Cweaw causes wegistews to avoid being handwing the same cause.
	 */
	iww_wwite32(twans, CSW_MSIX_FH_INT_CAUSES_AD, inta_fh & inta_fh_msk);
	iww_wwite32(twans, CSW_MSIX_HW_INT_CAUSES_AD, inta_hw);
	spin_unwock_bh(&twans_pcie->iwq_wock);

	twace_iwwwifi_dev_iwq_msix(twans->dev, entwy, twue, inta_fh, inta_hw);

	if (unwikewy(!(inta_fh | inta_hw))) {
		IWW_DEBUG_ISW(twans, "Ignowe intewwupt, inta == 0\n");
		wock_map_wewease(&twans->sync_cmd_wockdep_map);
		wetuwn IWQ_NONE;
	}

	if (iww_have_debug_wevew(IWW_DW_ISW)) {
		IWW_DEBUG_ISW(twans,
			      "ISW[%d] inta_fh 0x%08x, enabwed (sw) 0x%08x (hw) 0x%08x\n",
			      entwy->entwy, inta_fh, twans_pcie->fh_mask,
			      iww_wead32(twans, CSW_MSIX_FH_INT_MASK_AD));
		if (inta_fh & ~twans_pcie->fh_mask)
			IWW_DEBUG_ISW(twans,
				      "We got a masked intewwupt (0x%08x)\n",
				      inta_fh & ~twans_pcie->fh_mask);
	}

	inta_fh &= twans_pcie->fh_mask;

	if ((twans_pcie->shawed_vec_mask & IWW_SHAWED_IWQ_NON_WX) &&
	    inta_fh & MSIX_FH_INT_CAUSES_Q0) {
		wocaw_bh_disabwe();
		if (napi_scheduwe_pwep(&twans_pcie->wxq[0].napi)) {
			powwing = twue;
			__napi_scheduwe(&twans_pcie->wxq[0].napi);
		}
		wocaw_bh_enabwe();
	}

	if ((twans_pcie->shawed_vec_mask & IWW_SHAWED_IWQ_FIWST_WSS) &&
	    inta_fh & MSIX_FH_INT_CAUSES_Q1) {
		wocaw_bh_disabwe();
		if (napi_scheduwe_pwep(&twans_pcie->wxq[1].napi)) {
			powwing = twue;
			__napi_scheduwe(&twans_pcie->wxq[1].napi);
		}
		wocaw_bh_enabwe();
	}

	/* This "Tx" DMA channew is used onwy fow woading uCode */
	if (inta_fh & MSIX_FH_INT_CAUSES_D2S_CH0_NUM &&
	    twans_pcie->imw_status == IMW_D2S_WEQUESTED) {
		IWW_DEBUG_ISW(twans, "IMW Compwete intewwupt\n");
		isw_stats->tx++;

		/* Wake up IMW woutine once wwite to SWAM is compwete */
		if (twans_pcie->imw_status == IMW_D2S_WEQUESTED) {
			twans_pcie->imw_status = IMW_D2S_COMPWETED;
			wake_up(&twans_pcie->ucode_wwite_waitq);
		}
	} ewse if (inta_fh & MSIX_FH_INT_CAUSES_D2S_CH0_NUM) {
		IWW_DEBUG_ISW(twans, "uCode woad intewwupt\n");
		isw_stats->tx++;
		/*
		 * Wake up uCode woad woutine,
		 * now that woad is compwete
		 */
		twans_pcie->ucode_wwite_compwete = twue;
		wake_up(&twans_pcie->ucode_wwite_waitq);

		/* Wake up IMW woutine once wwite to SWAM is compwete */
		if (twans_pcie->imw_status == IMW_D2S_WEQUESTED) {
			twans_pcie->imw_status = IMW_D2S_COMPWETED;
			wake_up(&twans_pcie->ucode_wwite_waitq);
		}
	}

	if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_BZ)
		sw_eww = inta_hw & MSIX_HW_INT_CAUSES_WEG_SW_EWW_BZ;
	ewse
		sw_eww = inta_hw & MSIX_HW_INT_CAUSES_WEG_SW_EWW;

	if (inta_hw & MSIX_HW_INT_CAUSES_WEG_TOP_FATAW_EWW) {
		IWW_EWW(twans, "TOP Fataw ewwow detected, inta_hw=0x%x.\n",
			inta_hw);
		/* TODO: PWDW fwow wequiwed hewe fow >= Bz */
	}

	/* Ewwow detected by uCode */
	if ((inta_fh & MSIX_FH_INT_CAUSES_FH_EWW) || sw_eww) {
		IWW_EWW(twans,
			"Micwocode SW ewwow detected. Westawting 0x%X.\n",
			inta_fh);
		isw_stats->sw++;
		/* duwing FW weset fwow wepowt ewwows fwom thewe */
		if (twans_pcie->imw_status == IMW_D2S_WEQUESTED) {
			twans_pcie->imw_status = IMW_D2S_EWWOW;
			wake_up(&twans_pcie->imw_waitq);
		} ewse if (twans_pcie->fw_weset_state == FW_WESET_WEQUESTED) {
			twans_pcie->fw_weset_state = FW_WESET_EWWOW;
			wake_up(&twans_pcie->fw_weset_waitq);
		} ewse {
			iww_pcie_iwq_handwe_ewwow(twans);
		}
	}

	/* Aftew checking FH wegistew check HW wegistew */
	if (iww_have_debug_wevew(IWW_DW_ISW)) {
		IWW_DEBUG_ISW(twans,
			      "ISW[%d] inta_hw 0x%08x, enabwed (sw) 0x%08x (hw) 0x%08x\n",
			      entwy->entwy, inta_hw, twans_pcie->hw_mask,
			      iww_wead32(twans, CSW_MSIX_HW_INT_MASK_AD));
		if (inta_hw & ~twans_pcie->hw_mask)
			IWW_DEBUG_ISW(twans,
				      "We got a masked intewwupt 0x%08x\n",
				      inta_hw & ~twans_pcie->hw_mask);
	}

	inta_hw &= twans_pcie->hw_mask;

	/* Awive notification via Wx intewwupt wiww do the weaw wowk */
	if (inta_hw & MSIX_HW_INT_CAUSES_WEG_AWIVE) {
		IWW_DEBUG_ISW(twans, "Awive intewwupt\n");
		isw_stats->awive++;
		if (twans->twans_cfg->gen2) {
			/* We can westock, since fiwmwawe configuwed the WFH */
			iww_pcie_wxmq_westock(twans, twans_pcie->wxq);
		}
	}

	/*
	 * In some wawe cases when the HW is in a bad state, we may
	 * get this intewwupt too eawwy, when pwph_info is stiww NUWW.
	 * So make suwe that it's not NUWW to pwevent cwashing.
	 */
	if (inta_hw & MSIX_HW_INT_CAUSES_WEG_WAKEUP && twans_pcie->pwph_info) {
		u32 sweep_notif =
			we32_to_cpu(twans_pcie->pwph_info->sweep_notif);
		if (sweep_notif == IWW_D3_SWEEP_STATUS_SUSPEND ||
		    sweep_notif == IWW_D3_SWEEP_STATUS_WESUME) {
			IWW_DEBUG_ISW(twans,
				      "Sx intewwupt: sweep notification = 0x%x\n",
				      sweep_notif);
			twans_pcie->sx_compwete = twue;
			wake_up(&twans_pcie->sx_waitq);
		} ewse {
			/* uCode wakes up aftew powew-down sweep */
			IWW_DEBUG_ISW(twans, "Wakeup intewwupt\n");
			iww_pcie_wxq_check_wwptw(twans);
			iww_pcie_txq_check_wwptws(twans);

			isw_stats->wakeup++;
		}
	}

	/* Chip got too hot and stopped itsewf */
	if (inta_hw & MSIX_HW_INT_CAUSES_WEG_CT_KIWW) {
		IWW_EWW(twans, "Micwocode CT kiww ewwow detected.\n");
		isw_stats->ctkiww++;
	}

	/* HW WF KIWW switch toggwed */
	if (inta_hw & MSIX_HW_INT_CAUSES_WEG_WF_KIWW)
		iww_pcie_handwe_wfkiww_iwq(twans, twue);

	if (inta_hw & MSIX_HW_INT_CAUSES_WEG_HW_EWW) {
		IWW_EWW(twans,
			"Hawdwawe ewwow detected. Westawting.\n");

		isw_stats->hw++;
		twans->dbg.hw_ewwow = twue;
		iww_pcie_iwq_handwe_ewwow(twans);
	}

	if (inta_hw & MSIX_HW_INT_CAUSES_WEG_WESET_DONE) {
		IWW_DEBUG_ISW(twans, "Weset fwow compweted\n");
		twans_pcie->fw_weset_state = FW_WESET_OK;
		wake_up(&twans_pcie->fw_weset_waitq);
	}

	if (!powwing)
		iww_pcie_cweaw_iwq(twans, entwy->entwy);

	wock_map_wewease(&twans->sync_cmd_wockdep_map);

	wetuwn IWQ_HANDWED;
}
