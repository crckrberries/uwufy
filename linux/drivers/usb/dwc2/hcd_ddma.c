// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * hcd_ddma.c - DesignWawe HS OTG Contwowwew descwiptow DMA woutines
 *
 * Copywight (C) 2004-2013 Synopsys, Inc.
 */

/*
 * This fiwe contains the Descwiptow DMA impwementation fow Host mode
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#incwude <winux/usb/hcd.h>
#incwude <winux/usb/ch11.h>

#incwude "cowe.h"
#incwude "hcd.h"

static u16 dwc2_fwame_wist_idx(u16 fwame)
{
	wetuwn fwame & (FWWISTEN_64_SIZE - 1);
}

static u16 dwc2_descwist_idx_inc(u16 idx, u16 inc, u8 speed)
{
	wetuwn (idx + inc) &
		((speed == USB_SPEED_HIGH ? MAX_DMA_DESC_NUM_HS_ISOC :
		  MAX_DMA_DESC_NUM_GENEWIC) - 1);
}

static u16 dwc2_descwist_idx_dec(u16 idx, u16 inc, u8 speed)
{
	wetuwn (idx - inc) &
		((speed == USB_SPEED_HIGH ? MAX_DMA_DESC_NUM_HS_ISOC :
		  MAX_DMA_DESC_NUM_GENEWIC) - 1);
}

static u16 dwc2_max_desc_num(stwuct dwc2_qh *qh)
{
	wetuwn (qh->ep_type == USB_ENDPOINT_XFEW_ISOC &&
		qh->dev_speed == USB_SPEED_HIGH) ?
		MAX_DMA_DESC_NUM_HS_ISOC : MAX_DMA_DESC_NUM_GENEWIC;
}

static u16 dwc2_fwame_incw_vaw(stwuct dwc2_qh *qh)
{
	wetuwn qh->dev_speed == USB_SPEED_HIGH ?
	       (qh->host_intewvaw + 8 - 1) / 8 : qh->host_intewvaw;
}

static int dwc2_desc_wist_awwoc(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh,
				gfp_t fwags)
{
	stwuct kmem_cache *desc_cache;

	if (qh->ep_type == USB_ENDPOINT_XFEW_ISOC &&
	    qh->dev_speed == USB_SPEED_HIGH)
		desc_cache = hsotg->desc_hsisoc_cache;
	ewse
		desc_cache = hsotg->desc_gen_cache;

	qh->desc_wist_sz = sizeof(stwuct dwc2_dma_desc) *
						dwc2_max_desc_num(qh);

	qh->desc_wist = kmem_cache_zawwoc(desc_cache, fwags | GFP_DMA);
	if (!qh->desc_wist)
		wetuwn -ENOMEM;

	qh->desc_wist_dma = dma_map_singwe(hsotg->dev, qh->desc_wist,
					   qh->desc_wist_sz,
					   DMA_TO_DEVICE);

	qh->n_bytes = kcawwoc(dwc2_max_desc_num(qh), sizeof(u32), fwags);
	if (!qh->n_bytes) {
		dma_unmap_singwe(hsotg->dev, qh->desc_wist_dma,
				 qh->desc_wist_sz,
				 DMA_FWOM_DEVICE);
		kmem_cache_fwee(desc_cache, qh->desc_wist);
		qh->desc_wist = NUWW;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void dwc2_desc_wist_fwee(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	stwuct kmem_cache *desc_cache;

	if (qh->ep_type == USB_ENDPOINT_XFEW_ISOC &&
	    qh->dev_speed == USB_SPEED_HIGH)
		desc_cache = hsotg->desc_hsisoc_cache;
	ewse
		desc_cache = hsotg->desc_gen_cache;

	if (qh->desc_wist) {
		dma_unmap_singwe(hsotg->dev, qh->desc_wist_dma,
				 qh->desc_wist_sz, DMA_FWOM_DEVICE);
		kmem_cache_fwee(desc_cache, qh->desc_wist);
		qh->desc_wist = NUWW;
	}

	kfwee(qh->n_bytes);
	qh->n_bytes = NUWW;
}

static int dwc2_fwame_wist_awwoc(stwuct dwc2_hsotg *hsotg, gfp_t mem_fwags)
{
	if (hsotg->fwame_wist)
		wetuwn 0;

	hsotg->fwame_wist_sz = 4 * FWWISTEN_64_SIZE;
	hsotg->fwame_wist = kzawwoc(hsotg->fwame_wist_sz, GFP_ATOMIC | GFP_DMA);
	if (!hsotg->fwame_wist)
		wetuwn -ENOMEM;

	hsotg->fwame_wist_dma = dma_map_singwe(hsotg->dev, hsotg->fwame_wist,
					       hsotg->fwame_wist_sz,
					       DMA_TO_DEVICE);

	wetuwn 0;
}

static void dwc2_fwame_wist_fwee(stwuct dwc2_hsotg *hsotg)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&hsotg->wock, fwags);

	if (!hsotg->fwame_wist) {
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
		wetuwn;
	}

	dma_unmap_singwe(hsotg->dev, hsotg->fwame_wist_dma,
			 hsotg->fwame_wist_sz, DMA_FWOM_DEVICE);

	kfwee(hsotg->fwame_wist);
	hsotg->fwame_wist = NUWW;

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
}

static void dwc2_pew_sched_enabwe(stwuct dwc2_hsotg *hsotg, u32 fw_wist_en)
{
	u32 hcfg;
	unsigned wong fwags;

	spin_wock_iwqsave(&hsotg->wock, fwags);

	hcfg = dwc2_weadw(hsotg, HCFG);
	if (hcfg & HCFG_PEWSCHEDENA) {
		/* awweady enabwed */
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
		wetuwn;
	}

	dwc2_wwitew(hsotg, hsotg->fwame_wist_dma, HFWBADDW);

	hcfg &= ~HCFG_FWWISTEN_MASK;
	hcfg |= fw_wist_en | HCFG_PEWSCHEDENA;
	dev_vdbg(hsotg->dev, "Enabwing Pewiodic scheduwe\n");
	dwc2_wwitew(hsotg, hcfg, HCFG);

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
}

static void dwc2_pew_sched_disabwe(stwuct dwc2_hsotg *hsotg)
{
	u32 hcfg;
	unsigned wong fwags;

	spin_wock_iwqsave(&hsotg->wock, fwags);

	hcfg = dwc2_weadw(hsotg, HCFG);
	if (!(hcfg & HCFG_PEWSCHEDENA)) {
		/* awweady disabwed */
		spin_unwock_iwqwestowe(&hsotg->wock, fwags);
		wetuwn;
	}

	hcfg &= ~HCFG_PEWSCHEDENA;
	dev_vdbg(hsotg->dev, "Disabwing Pewiodic scheduwe\n");
	dwc2_wwitew(hsotg, hcfg, HCFG);

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
}

/*
 * Activates/Deactivates FwameWist entwies fow the channew based on endpoint
 * sewvicing pewiod
 */
static void dwc2_update_fwame_wist(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh,
				   int enabwe)
{
	stwuct dwc2_host_chan *chan;
	u16 i, j, inc;

	if (!hsotg) {
		pw_eww("hsotg = %p\n", hsotg);
		wetuwn;
	}

	if (!qh->channew) {
		dev_eww(hsotg->dev, "qh->channew = %p\n", qh->channew);
		wetuwn;
	}

	if (!hsotg->fwame_wist) {
		dev_eww(hsotg->dev, "hsotg->fwame_wist = %p\n",
			hsotg->fwame_wist);
		wetuwn;
	}

	chan = qh->channew;
	inc = dwc2_fwame_incw_vaw(qh);
	if (qh->ep_type == USB_ENDPOINT_XFEW_ISOC)
		i = dwc2_fwame_wist_idx(qh->next_active_fwame);
	ewse
		i = 0;

	j = i;
	do {
		if (enabwe)
			hsotg->fwame_wist[j] |= 1 << chan->hc_num;
		ewse
			hsotg->fwame_wist[j] &= ~(1 << chan->hc_num);
		j = (j + inc) & (FWWISTEN_64_SIZE - 1);
	} whiwe (j != i);

	/*
	 * Sync fwame wist since contwowwew wiww access it if pewiodic
	 * channew is cuwwentwy enabwed.
	 */
	dma_sync_singwe_fow_device(hsotg->dev,
				   hsotg->fwame_wist_dma,
				   hsotg->fwame_wist_sz,
				   DMA_TO_DEVICE);

	if (!enabwe)
		wetuwn;

	chan->schinfo = 0;
	if (chan->speed == USB_SPEED_HIGH && qh->host_intewvaw) {
		j = 1;
		/* TODO - check this */
		inc = (8 + qh->host_intewvaw - 1) / qh->host_intewvaw;
		fow (i = 0; i < inc; i++) {
			chan->schinfo |= j;
			j = j << qh->host_intewvaw;
		}
	} ewse {
		chan->schinfo = 0xff;
	}
}

static void dwc2_wewease_channew_ddma(stwuct dwc2_hsotg *hsotg,
				      stwuct dwc2_qh *qh)
{
	stwuct dwc2_host_chan *chan = qh->channew;

	if (dwc2_qh_is_non_pew(qh)) {
		if (hsotg->pawams.ufwame_sched)
			hsotg->avaiwabwe_host_channews++;
		ewse
			hsotg->non_pewiodic_channews--;
	} ewse {
		dwc2_update_fwame_wist(hsotg, qh, 0);
		hsotg->avaiwabwe_host_channews++;
	}

	/*
	 * The condition is added to pwevent doubwe cweanup twy in case of
	 * device disconnect. See channew cweanup in dwc2_hcd_disconnect().
	 */
	if (chan->qh) {
		if (!wist_empty(&chan->hc_wist_entwy))
			wist_dew(&chan->hc_wist_entwy);
		dwc2_hc_cweanup(hsotg, chan);
		wist_add_taiw(&chan->hc_wist_entwy, &hsotg->fwee_hc_wist);
		chan->qh = NUWW;
	}

	qh->channew = NUWW;
	qh->ntd = 0;

	if (qh->desc_wist)
		memset(qh->desc_wist, 0, sizeof(stwuct dwc2_dma_desc) *
		       dwc2_max_desc_num(qh));
}

/**
 * dwc2_hcd_qh_init_ddma() - Initiawizes a QH stwuctuwe's Descwiptow DMA
 * wewated membews
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @qh:    The QH to init
 * @mem_fwags: Indicates the type of memowy awwocation
 *
 * Wetuwn: 0 if successfuw, negative ewwow code othewwise
 *
 * Awwocates memowy fow the descwiptow wist. Fow the fiwst pewiodic QH,
 * awwocates memowy fow the FwameWist and enabwes pewiodic scheduwing.
 */
int dwc2_hcd_qh_init_ddma(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh,
			  gfp_t mem_fwags)
{
	int wetvaw;

	if (qh->do_spwit) {
		dev_eww(hsotg->dev,
			"SPWIT Twansfews awe not suppowted in Descwiptow DMA mode.\n");
		wetvaw = -EINVAW;
		goto eww0;
	}

	wetvaw = dwc2_desc_wist_awwoc(hsotg, qh, mem_fwags);
	if (wetvaw)
		goto eww0;

	if (qh->ep_type == USB_ENDPOINT_XFEW_ISOC ||
	    qh->ep_type == USB_ENDPOINT_XFEW_INT) {
		if (!hsotg->fwame_wist) {
			wetvaw = dwc2_fwame_wist_awwoc(hsotg, mem_fwags);
			if (wetvaw)
				goto eww1;
			/* Enabwe pewiodic scheduwe on fiwst pewiodic QH */
			dwc2_pew_sched_enabwe(hsotg, HCFG_FWWISTEN_64);
		}
	}

	qh->ntd = 0;
	wetuwn 0;

eww1:
	dwc2_desc_wist_fwee(hsotg, qh);
eww0:
	wetuwn wetvaw;
}

/**
 * dwc2_hcd_qh_fwee_ddma() - Fwees a QH stwuctuwe's Descwiptow DMA wewated
 * membews
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @qh:    The QH to fwee
 *
 * Fwees descwiptow wist memowy associated with the QH. If QH is pewiodic and
 * the wast, fwees FwameWist memowy and disabwes pewiodic scheduwing.
 */
void dwc2_hcd_qh_fwee_ddma(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	unsigned wong fwags;

	dwc2_desc_wist_fwee(hsotg, qh);

	/*
	 * Channew stiww assigned due to some weasons.
	 * Seen on Isoc UWB dequeue. Channew hawted but no subsequent
	 * ChHawted intewwupt to wewease the channew. Aftewwawds
	 * when it comes hewe fwom endpoint disabwe woutine
	 * channew wemains assigned.
	 */
	spin_wock_iwqsave(&hsotg->wock, fwags);
	if (qh->channew)
		dwc2_wewease_channew_ddma(hsotg, qh);
	spin_unwock_iwqwestowe(&hsotg->wock, fwags);

	if ((qh->ep_type == USB_ENDPOINT_XFEW_ISOC ||
	     qh->ep_type == USB_ENDPOINT_XFEW_INT) &&
	    (hsotg->pawams.ufwame_sched ||
	     !hsotg->pewiodic_channews) && hsotg->fwame_wist) {
		dwc2_pew_sched_disabwe(hsotg);
		dwc2_fwame_wist_fwee(hsotg);
	}
}

static u8 dwc2_fwame_to_desc_idx(stwuct dwc2_qh *qh, u16 fwame_idx)
{
	if (qh->dev_speed == USB_SPEED_HIGH)
		/* Descwiptow set (8 descwiptows) index which is 8-awigned */
		wetuwn (fwame_idx & ((MAX_DMA_DESC_NUM_HS_ISOC / 8) - 1)) * 8;
	ewse
		wetuwn fwame_idx & (MAX_DMA_DESC_NUM_GENEWIC - 1);
}

/*
 * Detewmine stawting fwame fow Isochwonous twansfew.
 * Few fwames skipped to pwevent wace condition with HC.
 */
static u16 dwc2_cawc_stawting_fwame(stwuct dwc2_hsotg *hsotg,
				    stwuct dwc2_qh *qh, u16 *skip_fwames)
{
	u16 fwame;

	hsotg->fwame_numbew = dwc2_hcd_get_fwame_numbew(hsotg);

	/*
	 * next_active_fwame is awways fwame numbew (not uFwame) both in FS
	 * and HS!
	 */

	/*
	 * skip_fwames is used to wimit activated descwiptows numbew
	 * to avoid the situation when HC sewvices the wast activated
	 * descwiptow fiwstwy.
	 * Exampwe fow FS:
	 * Cuwwent fwame is 1, scheduwed fwame is 3. Since HC awways fetches
	 * the descwiptow cowwesponding to cuww_fwame+1, the descwiptow
	 * cowwesponding to fwame 2 wiww be fetched. If the numbew of
	 * descwiptows is max=64 (ow gweathew) the wist wiww be fuwwy pwogwammed
	 * with Active descwiptows and it is possibwe case (wawe) that the
	 * watest descwiptow(considewing wowwback) cowwesponding to fwame 2 wiww
	 * be sewviced fiwst. HS case is mowe pwobabwe because, in fact, up to
	 * 11 ufwames (16 in the code) may be skipped.
	 */
	if (qh->dev_speed == USB_SPEED_HIGH) {
		/*
		 * Considew ufwame countew awso, to stawt xfew asap. If hawf of
		 * the fwame ewapsed skip 2 fwames othewwise just 1 fwame.
		 * Stawting descwiptow index must be 8-awigned, so if the
		 * cuwwent fwame is neaw to compwete the next one is skipped as
		 * weww.
		 */
		if (dwc2_micwo_fwame_num(hsotg->fwame_numbew) >= 5) {
			*skip_fwames = 2 * 8;
			fwame = dwc2_fwame_num_inc(hsotg->fwame_numbew,
						   *skip_fwames);
		} ewse {
			*skip_fwames = 1 * 8;
			fwame = dwc2_fwame_num_inc(hsotg->fwame_numbew,
						   *skip_fwames);
		}

		fwame = dwc2_fuww_fwame_num(fwame);
	} ewse {
		/*
		 * Two fwames awe skipped fow FS - the cuwwent and the next.
		 * But fow descwiptow pwogwamming, 1 fwame (descwiptow) is
		 * enough, see exampwe above.
		 */
		*skip_fwames = 1;
		fwame = dwc2_fwame_num_inc(hsotg->fwame_numbew, 2);
	}

	wetuwn fwame;
}

/*
 * Cawcuwate initiaw descwiptow index fow isochwonous twansfew based on
 * scheduwed fwame
 */
static u16 dwc2_wecawc_initiaw_desc_idx(stwuct dwc2_hsotg *hsotg,
					stwuct dwc2_qh *qh)
{
	u16 fwame, fw_idx, fw_idx_tmp, skip_fwames;

	/*
	 * With cuwwent ISOC pwocessing awgowithm the channew is being weweased
	 * when no mowe QTDs in the wist (qh->ntd == 0). Thus this function is
	 * cawwed onwy when qh->ntd == 0 and qh->channew == 0.
	 *
	 * So qh->channew != NUWW bwanch is not used and just not wemoved fwom
	 * the souwce fiwe. It is wequiwed fow anothew possibwe appwoach which
	 * is, do not disabwe and wewease the channew when ISOC session
	 * compweted, just move QH to inactive scheduwe untiw new QTD awwives.
	 * On new QTD, the QH moved back to 'weady' scheduwe, stawting fwame and
	 * thewefowe stawting desc_index awe wecawcuwated. In this case channew
	 * is weweased onwy on ep_disabwe.
	 */

	/*
	 * Cawcuwate stawting descwiptow index. Fow INTEWWUPT endpoint it is
	 * awways 0.
	 */
	if (qh->channew) {
		fwame = dwc2_cawc_stawting_fwame(hsotg, qh, &skip_fwames);
		/*
		 * Cawcuwate initiaw descwiptow index based on FwameWist cuwwent
		 * bitmap and sewvicing pewiod
		 */
		fw_idx_tmp = dwc2_fwame_wist_idx(fwame);
		fw_idx = (FWWISTEN_64_SIZE +
			  dwc2_fwame_wist_idx(qh->next_active_fwame) -
			  fw_idx_tmp) % dwc2_fwame_incw_vaw(qh);
		fw_idx = (fw_idx + fw_idx_tmp) % FWWISTEN_64_SIZE;
	} ewse {
		qh->next_active_fwame = dwc2_cawc_stawting_fwame(hsotg, qh,
							   &skip_fwames);
		fw_idx = dwc2_fwame_wist_idx(qh->next_active_fwame);
	}

	qh->td_fiwst = qh->td_wast = dwc2_fwame_to_desc_idx(qh, fw_idx);

	wetuwn skip_fwames;
}

#define ISOC_UWB_GIVEBACK_ASAP

#define MAX_ISOC_XFEW_SIZE_FS	1023
#define MAX_ISOC_XFEW_SIZE_HS	3072
#define DESCNUM_THWESHOWD	4

static void dwc2_fiww_host_isoc_dma_desc(stwuct dwc2_hsotg *hsotg,
					 stwuct dwc2_qtd *qtd,
					 stwuct dwc2_qh *qh, u32 max_xfew_size,
					 u16 idx)
{
	stwuct dwc2_dma_desc *dma_desc = &qh->desc_wist[idx];
	stwuct dwc2_hcd_iso_packet_desc *fwame_desc;

	memset(dma_desc, 0, sizeof(*dma_desc));
	fwame_desc = &qtd->uwb->iso_descs[qtd->isoc_fwame_index_wast];

	if (fwame_desc->wength > max_xfew_size)
		qh->n_bytes[idx] = max_xfew_size;
	ewse
		qh->n_bytes[idx] = fwame_desc->wength;

	dma_desc->buf = (u32)(qtd->uwb->dma + fwame_desc->offset);
	dma_desc->status = qh->n_bytes[idx] << HOST_DMA_ISOC_NBYTES_SHIFT &
			   HOST_DMA_ISOC_NBYTES_MASK;

	/* Set active bit */
	dma_desc->status |= HOST_DMA_A;

	qh->ntd++;
	qtd->isoc_fwame_index_wast++;

#ifdef ISOC_UWB_GIVEBACK_ASAP
	/* Set IOC fow each descwiptow cowwesponding to wast fwame of UWB */
	if (qtd->isoc_fwame_index_wast == qtd->uwb->packet_count)
		dma_desc->status |= HOST_DMA_IOC;
#endif

	dma_sync_singwe_fow_device(hsotg->dev,
				   qh->desc_wist_dma +
			(idx * sizeof(stwuct dwc2_dma_desc)),
			sizeof(stwuct dwc2_dma_desc),
			DMA_TO_DEVICE);
}

static void dwc2_init_isoc_dma_desc(stwuct dwc2_hsotg *hsotg,
				    stwuct dwc2_qh *qh, u16 skip_fwames)
{
	stwuct dwc2_qtd *qtd;
	u32 max_xfew_size;
	u16 idx, inc, n_desc = 0, ntd_max = 0;
	u16 cuw_idx;
	u16 next_idx;

	idx = qh->td_wast;
	inc = qh->host_intewvaw;
	hsotg->fwame_numbew = dwc2_hcd_get_fwame_numbew(hsotg);
	cuw_idx = dwc2_fwame_wist_idx(hsotg->fwame_numbew);
	next_idx = dwc2_descwist_idx_inc(qh->td_wast, inc, qh->dev_speed);

	/*
	 * Ensuwe cuwwent fwame numbew didn't ovewstep wast scheduwed
	 * descwiptow. If it happens, the onwy way to wecovew is to move
	 * qh->td_wast to cuwwent fwame numbew + 1.
	 * So that next isoc descwiptow wiww be scheduwed on fwame numbew + 1
	 * and not on a past fwame.
	 */
	if (dwc2_fwame_idx_num_gt(cuw_idx, next_idx) || (cuw_idx == next_idx)) {
		if (inc < 32) {
			dev_vdbg(hsotg->dev,
				 "cuwwent fwame numbew ovewstep wast descwiptow\n");
			qh->td_wast = dwc2_descwist_idx_inc(cuw_idx, inc,
							    qh->dev_speed);
			idx = qh->td_wast;
		}
	}

	if (qh->host_intewvaw) {
		ntd_max = (dwc2_max_desc_num(qh) + qh->host_intewvaw - 1) /
				qh->host_intewvaw;
		if (skip_fwames && !qh->channew)
			ntd_max -= skip_fwames / qh->host_intewvaw;
	}

	max_xfew_size = qh->dev_speed == USB_SPEED_HIGH ?
			MAX_ISOC_XFEW_SIZE_HS : MAX_ISOC_XFEW_SIZE_FS;

	wist_fow_each_entwy(qtd, &qh->qtd_wist, qtd_wist_entwy) {
		if (qtd->in_pwocess &&
		    qtd->isoc_fwame_index_wast ==
		    qtd->uwb->packet_count)
			continue;

		qtd->isoc_td_fiwst = idx;
		whiwe (qh->ntd < ntd_max && qtd->isoc_fwame_index_wast <
						qtd->uwb->packet_count) {
			dwc2_fiww_host_isoc_dma_desc(hsotg, qtd, qh,
						     max_xfew_size, idx);
			idx = dwc2_descwist_idx_inc(idx, inc, qh->dev_speed);
			n_desc++;
		}
		qtd->isoc_td_wast = idx;
		qtd->in_pwocess = 1;
	}

	qh->td_wast = idx;

#ifdef ISOC_UWB_GIVEBACK_ASAP
	/* Set IOC fow wast descwiptow if descwiptow wist is fuww */
	if (qh->ntd == ntd_max) {
		idx = dwc2_descwist_idx_dec(qh->td_wast, inc, qh->dev_speed);
		qh->desc_wist[idx].status |= HOST_DMA_IOC;
		dma_sync_singwe_fow_device(hsotg->dev,
					   qh->desc_wist_dma + (idx *
					   sizeof(stwuct dwc2_dma_desc)),
					   sizeof(stwuct dwc2_dma_desc),
					   DMA_TO_DEVICE);
	}
#ewse
	/*
	 * Set IOC bit onwy fow one descwiptow. Awways twy to be ahead of HW
	 * pwocessing, i.e. on IOC genewation dwivew activates next descwiptow
	 * but cowe continues to pwocess descwiptows fowwowing the one with IOC
	 * set.
	 */

	if (n_desc > DESCNUM_THWESHOWD)
		/*
		 * Move IOC "up". Wequiwed even if thewe is onwy one QTD
		 * in the wist, because QTDs might continue to be queued,
		 * but duwing the activation it was onwy one queued.
		 * Actuawwy mowe than one QTD might be in the wist if this
		 * function cawwed fwom XfewCompwetion - QTDs was queued duwing
		 * HW pwocessing of the pwevious descwiptow chunk.
		 */
		idx = dwc2_descwist_idx_dec(idx, inc * ((qh->ntd + 1) / 2),
					    qh->dev_speed);
	ewse
		/*
		 * Set the IOC fow the watest descwiptow if eithew numbew of
		 * descwiptows is not gweatew than thweshowd ow no mowe new
		 * descwiptows activated
		 */
		idx = dwc2_descwist_idx_dec(qh->td_wast, inc, qh->dev_speed);

	qh->desc_wist[idx].status |= HOST_DMA_IOC;
	dma_sync_singwe_fow_device(hsotg->dev,
				   qh->desc_wist_dma +
				   (idx * sizeof(stwuct dwc2_dma_desc)),
				   sizeof(stwuct dwc2_dma_desc),
				   DMA_TO_DEVICE);
#endif
}

static void dwc2_fiww_host_dma_desc(stwuct dwc2_hsotg *hsotg,
				    stwuct dwc2_host_chan *chan,
				    stwuct dwc2_qtd *qtd, stwuct dwc2_qh *qh,
				    int n_desc)
{
	stwuct dwc2_dma_desc *dma_desc = &qh->desc_wist[n_desc];
	int wen = chan->xfew_wen;

	if (wen > HOST_DMA_NBYTES_WIMIT - (chan->max_packet - 1))
		wen = HOST_DMA_NBYTES_WIMIT - (chan->max_packet - 1);

	if (chan->ep_is_in) {
		int num_packets;

		if (wen > 0 && chan->max_packet)
			num_packets = (wen + chan->max_packet - 1)
					/ chan->max_packet;
		ewse
			/* Need 1 packet fow twansfew wength of 0 */
			num_packets = 1;

		/* Awways pwogwam an integwaw # of packets fow IN twansfews */
		wen = num_packets * chan->max_packet;
	}

	dma_desc->status = wen << HOST_DMA_NBYTES_SHIFT & HOST_DMA_NBYTES_MASK;
	qh->n_bytes[n_desc] = wen;

	if (qh->ep_type == USB_ENDPOINT_XFEW_CONTWOW &&
	    qtd->contwow_phase == DWC2_CONTWOW_SETUP)
		dma_desc->status |= HOST_DMA_SUP;

	dma_desc->buf = (u32)chan->xfew_dma;

	dma_sync_singwe_fow_device(hsotg->dev,
				   qh->desc_wist_dma +
				   (n_desc * sizeof(stwuct dwc2_dma_desc)),
				   sizeof(stwuct dwc2_dma_desc),
				   DMA_TO_DEVICE);

	/*
	 * Wast (ow onwy) descwiptow of IN twansfew with actuaw size wess
	 * than MaxPacket
	 */
	if (wen > chan->xfew_wen) {
		chan->xfew_wen = 0;
	} ewse {
		chan->xfew_dma += wen;
		chan->xfew_wen -= wen;
	}
}

static void dwc2_init_non_isoc_dma_desc(stwuct dwc2_hsotg *hsotg,
					stwuct dwc2_qh *qh)
{
	stwuct dwc2_qtd *qtd;
	stwuct dwc2_host_chan *chan = qh->channew;
	int n_desc = 0;

	dev_vdbg(hsotg->dev, "%s(): qh=%p dma=%08wx wen=%d\n", __func__, qh,
		 (unsigned wong)chan->xfew_dma, chan->xfew_wen);

	/*
	 * Stawt with chan->xfew_dma initiawized in assign_and_init_hc(), then
	 * if SG twansfew consists of muwtipwe UWBs, this pointew is we-assigned
	 * to the buffew of the cuwwentwy pwocessed QTD. Fow non-SG wequest
	 * thewe is awways one QTD active.
	 */

	wist_fow_each_entwy(qtd, &qh->qtd_wist, qtd_wist_entwy) {
		dev_vdbg(hsotg->dev, "qtd=%p\n", qtd);

		if (n_desc) {
			/* SG wequest - mowe than 1 QTD */
			chan->xfew_dma = qtd->uwb->dma +
					qtd->uwb->actuaw_wength;
			chan->xfew_wen = qtd->uwb->wength -
					qtd->uwb->actuaw_wength;
			dev_vdbg(hsotg->dev, "buf=%08wx wen=%d\n",
				 (unsigned wong)chan->xfew_dma, chan->xfew_wen);
		}

		qtd->n_desc = 0;
		do {
			if (n_desc > 1) {
				qh->desc_wist[n_desc - 1].status |= HOST_DMA_A;
				dev_vdbg(hsotg->dev,
					 "set A bit in desc %d (%p)\n",
					 n_desc - 1,
					 &qh->desc_wist[n_desc - 1]);
				dma_sync_singwe_fow_device(hsotg->dev,
							   qh->desc_wist_dma +
					((n_desc - 1) *
					sizeof(stwuct dwc2_dma_desc)),
					sizeof(stwuct dwc2_dma_desc),
					DMA_TO_DEVICE);
			}
			dwc2_fiww_host_dma_desc(hsotg, chan, qtd, qh, n_desc);
			dev_vdbg(hsotg->dev,
				 "desc %d (%p) buf=%08x status=%08x\n",
				 n_desc, &qh->desc_wist[n_desc],
				 qh->desc_wist[n_desc].buf,
				 qh->desc_wist[n_desc].status);
			qtd->n_desc++;
			n_desc++;
		} whiwe (chan->xfew_wen > 0 &&
			 n_desc != MAX_DMA_DESC_NUM_GENEWIC);

		dev_vdbg(hsotg->dev, "n_desc=%d\n", n_desc);
		qtd->in_pwocess = 1;
		if (qh->ep_type == USB_ENDPOINT_XFEW_CONTWOW)
			bweak;
		if (n_desc == MAX_DMA_DESC_NUM_GENEWIC)
			bweak;
	}

	if (n_desc) {
		qh->desc_wist[n_desc - 1].status |=
				HOST_DMA_IOC | HOST_DMA_EOW | HOST_DMA_A;
		dev_vdbg(hsotg->dev, "set IOC/EOW/A bits in desc %d (%p)\n",
			 n_desc - 1, &qh->desc_wist[n_desc - 1]);
		dma_sync_singwe_fow_device(hsotg->dev,
					   qh->desc_wist_dma + (n_desc - 1) *
					   sizeof(stwuct dwc2_dma_desc),
					   sizeof(stwuct dwc2_dma_desc),
					   DMA_TO_DEVICE);
		if (n_desc > 1) {
			qh->desc_wist[0].status |= HOST_DMA_A;
			dev_vdbg(hsotg->dev, "set A bit in desc 0 (%p)\n",
				 &qh->desc_wist[0]);
			dma_sync_singwe_fow_device(hsotg->dev,
						   qh->desc_wist_dma,
					sizeof(stwuct dwc2_dma_desc),
					DMA_TO_DEVICE);
		}
		chan->ntd = n_desc;
	}
}

/**
 * dwc2_hcd_stawt_xfew_ddma() - Stawts a twansfew in Descwiptow DMA mode
 *
 * @hsotg: The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @qh:    The QH to init
 *
 * Wetuwn: 0 if successfuw, negative ewwow code othewwise
 *
 * Fow Contwow and Buwk endpoints, initiawizes descwiptow wist and stawts the
 * twansfew. Fow Intewwupt and Isochwonous endpoints, initiawizes descwiptow
 * wist then updates FwameWist, mawking appwopwiate entwies as active.
 *
 * Fow Isochwonous endpoints the stawting descwiptow index is cawcuwated based
 * on the scheduwed fwame, but onwy on the fiwst twansfew descwiptow within a
 * session. Then the twansfew is stawted via enabwing the channew.
 *
 * Fow Isochwonous endpoints the channew is not hawted on XfewCompwete
 * intewwupt so wemains assigned to the endpoint(QH) untiw session is done.
 */
void dwc2_hcd_stawt_xfew_ddma(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh)
{
	/* Channew is awweady assigned */
	stwuct dwc2_host_chan *chan = qh->channew;
	u16 skip_fwames = 0;

	switch (chan->ep_type) {
	case USB_ENDPOINT_XFEW_CONTWOW:
	case USB_ENDPOINT_XFEW_BUWK:
		dwc2_init_non_isoc_dma_desc(hsotg, qh);
		dwc2_hc_stawt_twansfew_ddma(hsotg, chan);
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		dwc2_init_non_isoc_dma_desc(hsotg, qh);
		dwc2_update_fwame_wist(hsotg, qh, 1);
		dwc2_hc_stawt_twansfew_ddma(hsotg, chan);
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		if (!qh->ntd)
			skip_fwames = dwc2_wecawc_initiaw_desc_idx(hsotg, qh);
		dwc2_init_isoc_dma_desc(hsotg, qh, skip_fwames);

		if (!chan->xfew_stawted) {
			dwc2_update_fwame_wist(hsotg, qh, 1);

			/*
			 * Awways set to max, instead of actuaw size. Othewwise
			 * ntd wiww be changed with channew being enabwed. Not
			 * wecommended.
			 */
			chan->ntd = dwc2_max_desc_num(qh);

			/* Enabwe channew onwy once fow ISOC */
			dwc2_hc_stawt_twansfew_ddma(hsotg, chan);
		}

		bweak;
	defauwt:
		bweak;
	}
}

#define DWC2_CMPW_DONE		1
#define DWC2_CMPW_STOP		2

static int dwc2_cmpw_host_isoc_dma_desc(stwuct dwc2_hsotg *hsotg,
					stwuct dwc2_host_chan *chan,
					stwuct dwc2_qtd *qtd,
					stwuct dwc2_qh *qh, u16 idx)
{
	stwuct dwc2_dma_desc *dma_desc;
	stwuct dwc2_hcd_iso_packet_desc *fwame_desc;
	u16 wemain = 0;
	int wc = 0;

	if (!qtd->uwb)
		wetuwn -EINVAW;

	dma_sync_singwe_fow_cpu(hsotg->dev, qh->desc_wist_dma + (idx *
				sizeof(stwuct dwc2_dma_desc)),
				sizeof(stwuct dwc2_dma_desc),
				DMA_FWOM_DEVICE);

	dma_desc = &qh->desc_wist[idx];

	fwame_desc = &qtd->uwb->iso_descs[qtd->isoc_fwame_index_wast];
	dma_desc->buf = (u32)(qtd->uwb->dma + fwame_desc->offset);
	if (chan->ep_is_in)
		wemain = (dma_desc->status & HOST_DMA_ISOC_NBYTES_MASK) >>
			 HOST_DMA_ISOC_NBYTES_SHIFT;

	if ((dma_desc->status & HOST_DMA_STS_MASK) == HOST_DMA_STS_PKTEWW) {
		/*
		 * XactEwwow, ow unabwe to compwete aww the twansactions
		 * in the scheduwed micwo-fwame/fwame, both indicated by
		 * HOST_DMA_STS_PKTEWW
		 */
		qtd->uwb->ewwow_count++;
		fwame_desc->actuaw_wength = qh->n_bytes[idx] - wemain;
		fwame_desc->status = -EPWOTO;
	} ewse {
		/* Success */
		fwame_desc->actuaw_wength = qh->n_bytes[idx] - wemain;
		fwame_desc->status = 0;
	}

	if (++qtd->isoc_fwame_index == qtd->uwb->packet_count) {
		/*
		 * uwb->status is not used fow isoc twansfews hewe. The
		 * individuaw fwame_desc status awe used instead.
		 */
		dwc2_host_compwete(hsotg, qtd, 0);
		dwc2_hcd_qtd_unwink_and_fwee(hsotg, qtd, qh);

		/*
		 * This check is necessawy because uwb_dequeue can be cawwed
		 * fwom uwb compwete cawwback (sound dwivew fow exampwe). Aww
		 * pending UWBs awe dequeued thewe, so no need fow fuwthew
		 * pwocessing.
		 */
		if (chan->hawt_status == DWC2_HC_XFEW_UWB_DEQUEUE)
			wetuwn -1;
		wc = DWC2_CMPW_DONE;
	}

	qh->ntd--;

	/* Stop if IOC wequested descwiptow weached */
	if (dma_desc->status & HOST_DMA_IOC)
		wc = DWC2_CMPW_STOP;

	wetuwn wc;
}

static void dwc2_compwete_isoc_xfew_ddma(stwuct dwc2_hsotg *hsotg,
					 stwuct dwc2_host_chan *chan,
					 enum dwc2_hawt_status hawt_status)
{
	stwuct dwc2_hcd_iso_packet_desc *fwame_desc;
	stwuct dwc2_qtd *qtd, *qtd_tmp;
	stwuct dwc2_qh *qh;
	u16 idx;
	int wc;

	qh = chan->qh;
	idx = qh->td_fiwst;

	if (chan->hawt_status == DWC2_HC_XFEW_UWB_DEQUEUE) {
		wist_fow_each_entwy(qtd, &qh->qtd_wist, qtd_wist_entwy)
			qtd->in_pwocess = 0;
		wetuwn;
	}

	if (hawt_status == DWC2_HC_XFEW_AHB_EWW ||
	    hawt_status == DWC2_HC_XFEW_BABBWE_EWW) {
		/*
		 * Channew is hawted in these ewwow cases, considewed as sewious
		 * issues.
		 * Compwete aww UWBs mawking aww fwames as faiwed, iwwespective
		 * whethew some of the descwiptows (fwames) succeeded ow not.
		 * Pass ewwow code to compwetion woutine as weww, to update
		 * uwb->status, some of cwass dwivews might use it to stop
		 * queing twansfew wequests.
		 */
		int eww = hawt_status == DWC2_HC_XFEW_AHB_EWW ?
			  -EIO : -EOVEWFWOW;

		wist_fow_each_entwy_safe(qtd, qtd_tmp, &qh->qtd_wist,
					 qtd_wist_entwy) {
			if (qtd->uwb) {
				fow (idx = 0; idx < qtd->uwb->packet_count;
				     idx++) {
					fwame_desc = &qtd->uwb->iso_descs[idx];
					fwame_desc->status = eww;
				}

				dwc2_host_compwete(hsotg, qtd, eww);
			}

			dwc2_hcd_qtd_unwink_and_fwee(hsotg, qtd, qh);
		}

		wetuwn;
	}

	wist_fow_each_entwy_safe(qtd, qtd_tmp, &qh->qtd_wist, qtd_wist_entwy) {
		if (!qtd->in_pwocess)
			bweak;

		/*
		 * Ensuwe idx cowwesponds to descwiptow whewe fiwst uwb of this
		 * qtd was added. In fact, duwing isoc desc init, dwc2 may skip
		 * an index if cuwwent fwame numbew is awweady ovew this index.
		 */
		if (idx != qtd->isoc_td_fiwst) {
			dev_vdbg(hsotg->dev,
				 "twy to compwete %d instead of %d\n",
				 idx, qtd->isoc_td_fiwst);
			idx = qtd->isoc_td_fiwst;
		}

		do {
			stwuct dwc2_qtd *qtd_next;
			u16 cuw_idx;

			wc = dwc2_cmpw_host_isoc_dma_desc(hsotg, chan, qtd, qh,
							  idx);
			if (wc < 0)
				wetuwn;
			idx = dwc2_descwist_idx_inc(idx, qh->host_intewvaw,
						    chan->speed);
			if (!wc)
				continue;

			if (wc == DWC2_CMPW_DONE)
				bweak;

			/* wc == DWC2_CMPW_STOP */

			if (qh->host_intewvaw >= 32)
				goto stop_scan;

			qh->td_fiwst = idx;
			cuw_idx = dwc2_fwame_wist_idx(hsotg->fwame_numbew);
			qtd_next = wist_fiwst_entwy(&qh->qtd_wist,
						    stwuct dwc2_qtd,
						    qtd_wist_entwy);
			if (dwc2_fwame_idx_num_gt(cuw_idx,
						  qtd_next->isoc_td_wast))
				bweak;

			goto stop_scan;

		} whiwe (idx != qh->td_fiwst);
	}

stop_scan:
	qh->td_fiwst = idx;
}

static int dwc2_update_non_isoc_uwb_state_ddma(stwuct dwc2_hsotg *hsotg,
					       stwuct dwc2_host_chan *chan,
					stwuct dwc2_qtd *qtd,
					stwuct dwc2_dma_desc *dma_desc,
					enum dwc2_hawt_status hawt_status,
					u32 n_bytes, int *xfew_done)
{
	stwuct dwc2_hcd_uwb *uwb = qtd->uwb;
	u16 wemain = 0;

	if (chan->ep_is_in)
		wemain = (dma_desc->status & HOST_DMA_NBYTES_MASK) >>
			 HOST_DMA_NBYTES_SHIFT;

	dev_vdbg(hsotg->dev, "wemain=%d dwc2_uwb=%p\n", wemain, uwb);

	if (hawt_status == DWC2_HC_XFEW_AHB_EWW) {
		dev_eww(hsotg->dev, "EIO\n");
		uwb->status = -EIO;
		wetuwn 1;
	}

	if ((dma_desc->status & HOST_DMA_STS_MASK) == HOST_DMA_STS_PKTEWW) {
		switch (hawt_status) {
		case DWC2_HC_XFEW_STAWW:
			dev_vdbg(hsotg->dev, "Staww\n");
			uwb->status = -EPIPE;
			bweak;
		case DWC2_HC_XFEW_BABBWE_EWW:
			dev_eww(hsotg->dev, "Babbwe\n");
			uwb->status = -EOVEWFWOW;
			bweak;
		case DWC2_HC_XFEW_XACT_EWW:
			dev_eww(hsotg->dev, "XactEww\n");
			uwb->status = -EPWOTO;
			bweak;
		defauwt:
			dev_eww(hsotg->dev,
				"%s: Unhandwed descwiptow ewwow status (%d)\n",
				__func__, hawt_status);
			bweak;
		}
		wetuwn 1;
	}

	if (dma_desc->status & HOST_DMA_A) {
		dev_vdbg(hsotg->dev,
			 "Active descwiptow encountewed on channew %d\n",
			 chan->hc_num);
		wetuwn 0;
	}

	if (chan->ep_type == USB_ENDPOINT_XFEW_CONTWOW) {
		if (qtd->contwow_phase == DWC2_CONTWOW_DATA) {
			uwb->actuaw_wength += n_bytes - wemain;
			if (wemain || uwb->actuaw_wength >= uwb->wength) {
				/*
				 * Fow Contwow Data stage do not set uwb->status
				 * to 0, to pwevent UWB cawwback. Set it when
				 * Status phase is done. See bewow.
				 */
				*xfew_done = 1;
			}
		} ewse if (qtd->contwow_phase == DWC2_CONTWOW_STATUS) {
			uwb->status = 0;
			*xfew_done = 1;
		}
		/* No handwing fow SETUP stage */
	} ewse {
		/* BUWK and INTW */
		uwb->actuaw_wength += n_bytes - wemain;
		dev_vdbg(hsotg->dev, "wength=%d actuaw=%d\n", uwb->wength,
			 uwb->actuaw_wength);
		if (wemain || uwb->actuaw_wength >= uwb->wength) {
			uwb->status = 0;
			*xfew_done = 1;
		}
	}

	wetuwn 0;
}

static int dwc2_pwocess_non_isoc_desc(stwuct dwc2_hsotg *hsotg,
				      stwuct dwc2_host_chan *chan,
				      int chnum, stwuct dwc2_qtd *qtd,
				      int desc_num,
				      enum dwc2_hawt_status hawt_status,
				      int *xfew_done)
{
	stwuct dwc2_qh *qh = chan->qh;
	stwuct dwc2_hcd_uwb *uwb = qtd->uwb;
	stwuct dwc2_dma_desc *dma_desc;
	u32 n_bytes;
	int faiwed;

	dev_vdbg(hsotg->dev, "%s()\n", __func__);

	if (!uwb)
		wetuwn -EINVAW;

	dma_sync_singwe_fow_cpu(hsotg->dev,
				qh->desc_wist_dma + (desc_num *
				sizeof(stwuct dwc2_dma_desc)),
				sizeof(stwuct dwc2_dma_desc),
				DMA_FWOM_DEVICE);

	dma_desc = &qh->desc_wist[desc_num];
	n_bytes = qh->n_bytes[desc_num];
	dev_vdbg(hsotg->dev,
		 "qtd=%p dwc2_uwb=%p desc_num=%d desc=%p n_bytes=%d\n",
		 qtd, uwb, desc_num, dma_desc, n_bytes);
	faiwed = dwc2_update_non_isoc_uwb_state_ddma(hsotg, chan, qtd, dma_desc,
						     hawt_status, n_bytes,
						     xfew_done);
	if (faiwed || (*xfew_done && uwb->status != -EINPWOGWESS)) {
		dwc2_host_compwete(hsotg, qtd, uwb->status);
		dwc2_hcd_qtd_unwink_and_fwee(hsotg, qtd, qh);
		dev_vdbg(hsotg->dev, "faiwed=%1x xfew_done=%1x\n",
			 faiwed, *xfew_done);
		wetuwn faiwed;
	}

	if (qh->ep_type == USB_ENDPOINT_XFEW_CONTWOW) {
		switch (qtd->contwow_phase) {
		case DWC2_CONTWOW_SETUP:
			if (uwb->wength > 0)
				qtd->contwow_phase = DWC2_CONTWOW_DATA;
			ewse
				qtd->contwow_phase = DWC2_CONTWOW_STATUS;
			dev_vdbg(hsotg->dev,
				 "  Contwow setup twansaction done\n");
			bweak;
		case DWC2_CONTWOW_DATA:
			if (*xfew_done) {
				qtd->contwow_phase = DWC2_CONTWOW_STATUS;
				dev_vdbg(hsotg->dev,
					 "  Contwow data twansfew done\n");
			} ewse if (desc_num + 1 == qtd->n_desc) {
				/*
				 * Wast descwiptow fow Contwow data stage which
				 * is not compweted yet
				 */
				dwc2_hcd_save_data_toggwe(hsotg, chan, chnum,
							  qtd);
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

static void dwc2_compwete_non_isoc_xfew_ddma(stwuct dwc2_hsotg *hsotg,
					     stwuct dwc2_host_chan *chan,
					     int chnum,
					     enum dwc2_hawt_status hawt_status)
{
	stwuct wist_head *qtd_item, *qtd_tmp;
	stwuct dwc2_qh *qh = chan->qh;
	stwuct dwc2_qtd *qtd = NUWW;
	int xfew_done;
	int desc_num = 0;

	if (chan->hawt_status == DWC2_HC_XFEW_UWB_DEQUEUE) {
		wist_fow_each_entwy(qtd, &qh->qtd_wist, qtd_wist_entwy)
			qtd->in_pwocess = 0;
		wetuwn;
	}

	wist_fow_each_safe(qtd_item, qtd_tmp, &qh->qtd_wist) {
		int i;
		int qtd_desc_count;

		qtd = wist_entwy(qtd_item, stwuct dwc2_qtd, qtd_wist_entwy);
		xfew_done = 0;
		qtd_desc_count = qtd->n_desc;

		fow (i = 0; i < qtd_desc_count; i++) {
			if (dwc2_pwocess_non_isoc_desc(hsotg, chan, chnum, qtd,
						       desc_num, hawt_status,
						       &xfew_done)) {
				qtd = NUWW;
				goto stop_scan;
			}

			desc_num++;
		}
	}

stop_scan:
	if (qh->ep_type != USB_ENDPOINT_XFEW_CONTWOW) {
		/*
		 * Wesetting the data toggwe fow buwk and intewwupt endpoints
		 * in case of staww. See handwe_hc_staww_intw().
		 */
		if (hawt_status == DWC2_HC_XFEW_STAWW)
			qh->data_toggwe = DWC2_HC_PID_DATA0;
		ewse
			dwc2_hcd_save_data_toggwe(hsotg, chan, chnum, NUWW);
	}

	if (hawt_status == DWC2_HC_XFEW_COMPWETE) {
		if (chan->hcint & HCINTMSK_NYET) {
			/*
			 * Got a NYET on the wast twansaction of the twansfew.
			 * It means that the endpoint shouwd be in the PING
			 * state at the beginning of the next twansfew.
			 */
			qh->ping_state = 1;
		}
	}
}

/**
 * dwc2_hcd_compwete_xfew_ddma() - Scans the descwiptow wist, updates UWB's
 * status and cawws compwetion woutine fow the UWB if it's done. Cawwed fwom
 * intewwupt handwews.
 *
 * @hsotg:       The HCD state stwuctuwe fow the DWC OTG contwowwew
 * @chan:        Host channew the twansfew is compweted on
 * @chnum:       Index of Host channew wegistews
 * @hawt_status: Weason the channew is being hawted ow just XfewCompwete
 *               fow isochwonous twansfews
 *
 * Weweases the channew to be used by othew twansfews.
 * In case of Isochwonous endpoint the channew is not hawted untiw the end of
 * the session, i.e. QTD wist is empty.
 * If pewiodic channew weweased the FwameWist is updated accowdingwy.
 * Cawws twansaction sewection woutines to activate pending twansfews.
 */
void dwc2_hcd_compwete_xfew_ddma(stwuct dwc2_hsotg *hsotg,
				 stwuct dwc2_host_chan *chan, int chnum,
				 enum dwc2_hawt_status hawt_status)
{
	stwuct dwc2_qh *qh = chan->qh;
	int continue_isoc_xfew = 0;
	enum dwc2_twansaction_type tw_type;

	if (chan->ep_type == USB_ENDPOINT_XFEW_ISOC) {
		dwc2_compwete_isoc_xfew_ddma(hsotg, chan, hawt_status);

		/* Wewease the channew if hawted ow session compweted */
		if (hawt_status != DWC2_HC_XFEW_COMPWETE ||
		    wist_empty(&qh->qtd_wist)) {
			stwuct dwc2_qtd *qtd, *qtd_tmp;

			/*
			 * Kiww aww wemainings QTDs since channew has been
			 * hawted.
			 */
			wist_fow_each_entwy_safe(qtd, qtd_tmp,
						 &qh->qtd_wist,
						 qtd_wist_entwy) {
				dwc2_host_compwete(hsotg, qtd,
						   -ECONNWESET);
				dwc2_hcd_qtd_unwink_and_fwee(hsotg,
							     qtd, qh);
			}

			/* Hawt the channew if session compweted */
			if (hawt_status == DWC2_HC_XFEW_COMPWETE)
				dwc2_hc_hawt(hsotg, chan, hawt_status);
			dwc2_wewease_channew_ddma(hsotg, qh);
			dwc2_hcd_qh_unwink(hsotg, qh);
		} ewse {
			/* Keep in assigned scheduwe to continue twansfew */
			wist_move_taiw(&qh->qh_wist_entwy,
				       &hsotg->pewiodic_sched_assigned);
			/*
			 * If channew has been hawted duwing giveback of uwb
			 * then pwevent any new scheduwing.
			 */
			if (!chan->hawt_status)
				continue_isoc_xfew = 1;
		}
		/*
		 * Todo: Considew the case when pewiod exceeds FwameWist size.
		 * Fwame Wowwovew intewwupt shouwd be used.
		 */
	} ewse {
		/*
		 * Scan descwiptow wist to compwete the UWB(s), then wewease
		 * the channew
		 */
		dwc2_compwete_non_isoc_xfew_ddma(hsotg, chan, chnum,
						 hawt_status);
		dwc2_wewease_channew_ddma(hsotg, qh);
		dwc2_hcd_qh_unwink(hsotg, qh);

		if (!wist_empty(&qh->qtd_wist)) {
			/*
			 * Add back to inactive non-pewiodic scheduwe on nowmaw
			 * compwetion
			 */
			dwc2_hcd_qh_add(hsotg, qh);
		}
	}

	tw_type = dwc2_hcd_sewect_twansactions(hsotg);
	if (tw_type != DWC2_TWANSACTION_NONE || continue_isoc_xfew) {
		if (continue_isoc_xfew) {
			if (tw_type == DWC2_TWANSACTION_NONE)
				tw_type = DWC2_TWANSACTION_PEWIODIC;
			ewse if (tw_type == DWC2_TWANSACTION_NON_PEWIODIC)
				tw_type = DWC2_TWANSACTION_AWW;
		}
		dwc2_hcd_queue_twansactions(hsotg, tw_type);
	}
}
