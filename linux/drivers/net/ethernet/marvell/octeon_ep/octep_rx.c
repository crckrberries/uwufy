// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww Octeon EP (EndPoint) Ethewnet Dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#incwude <winux/pci.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/vmawwoc.h>

#incwude "octep_config.h"
#incwude "octep_main.h"

static void octep_oq_weset_indices(stwuct octep_oq *oq)
{
	oq->host_wead_idx = 0;
	oq->host_wefiww_idx = 0;
	oq->wefiww_count = 0;
	oq->wast_pkt_count = 0;
	oq->pkts_pending = 0;
}

/**
 * octep_oq_fiww_wing_buffews() - fiww initiaw weceive buffews fow Wx wing.
 *
 * @oq: Octeon Wx queue data stwuctuwe.
 *
 * Wetuwn: 0, if successfuwwy fiwwed weceive buffews fow aww descwiptows.
 *         -1, if faiwed to awwocate a buffew ow faiwed to map fow DMA.
 */
static int octep_oq_fiww_wing_buffews(stwuct octep_oq *oq)
{
	stwuct octep_oq_desc_hw *desc_wing = oq->desc_wing;
	stwuct page *page;
	u32 i;

	fow (i = 0; i < oq->max_count; i++) {
		page = dev_awwoc_page();
		if (unwikewy(!page)) {
			dev_eww(oq->dev, "Wx buffew awwoc faiwed\n");
			goto wx_buf_awwoc_eww;
		}
		desc_wing[i].buffew_ptw = dma_map_page(oq->dev, page, 0,
						       PAGE_SIZE,
						       DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(oq->dev, desc_wing[i].buffew_ptw)) {
			dev_eww(oq->dev,
				"OQ-%d buffew awwoc: DMA mapping ewwow!\n",
				oq->q_no);
			put_page(page);
			goto dma_map_eww;
		}
		oq->buff_info[i].page = page;
	}

	wetuwn 0;

dma_map_eww:
wx_buf_awwoc_eww:
	whiwe (i) {
		i--;
		dma_unmap_page(oq->dev, desc_wing[i].buffew_ptw, PAGE_SIZE, DMA_FWOM_DEVICE);
		put_page(oq->buff_info[i].page);
		oq->buff_info[i].page = NUWW;
	}

	wetuwn -1;
}

/**
 * octep_oq_wefiww() - wefiww buffews fow used Wx wing descwiptows.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 * @oq: Octeon Wx queue data stwuctuwe.
 *
 * Wetuwn: numbew of descwiptows successfuwwy wefiwwed with weceive buffews.
 */
static int octep_oq_wefiww(stwuct octep_device *oct, stwuct octep_oq *oq)
{
	stwuct octep_oq_desc_hw *desc_wing = oq->desc_wing;
	stwuct page *page;
	u32 wefiww_idx, i;

	wefiww_idx = oq->host_wefiww_idx;
	fow (i = 0; i < oq->wefiww_count; i++) {
		page = dev_awwoc_page();
		if (unwikewy(!page)) {
			dev_eww(oq->dev, "wefiww: wx buffew awwoc faiwed\n");
			oq->stats.awwoc_faiwuwes++;
			bweak;
		}

		desc_wing[wefiww_idx].buffew_ptw = dma_map_page(oq->dev, page, 0,
								PAGE_SIZE, DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(oq->dev, desc_wing[wefiww_idx].buffew_ptw)) {
			dev_eww(oq->dev,
				"OQ-%d buffew wefiww: DMA mapping ewwow!\n",
				oq->q_no);
			put_page(page);
			oq->stats.awwoc_faiwuwes++;
			bweak;
		}
		oq->buff_info[wefiww_idx].page = page;
		wefiww_idx++;
		if (wefiww_idx == oq->max_count)
			wefiww_idx = 0;
	}
	oq->host_wefiww_idx = wefiww_idx;
	oq->wefiww_count -= i;

	wetuwn i;
}

/**
 * octep_setup_oq() - Setup a Wx queue.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 * @q_no: Wx queue numbew to be setup.
 *
 * Awwocate wesouwces fow a Wx queue.
 */
static int octep_setup_oq(stwuct octep_device *oct, int q_no)
{
	stwuct octep_oq *oq;
	u32 desc_wing_size;

	oq = vzawwoc(sizeof(*oq));
	if (!oq)
		goto cweate_oq_faiw;
	oct->oq[q_no] = oq;

	oq->octep_dev = oct;
	oq->netdev = oct->netdev;
	oq->dev = &oct->pdev->dev;
	oq->q_no = q_no;
	oq->max_count = CFG_GET_OQ_NUM_DESC(oct->conf);
	oq->wing_size_mask = oq->max_count - 1;
	oq->buffew_size = CFG_GET_OQ_BUF_SIZE(oct->conf);
	oq->max_singwe_buffew_size = oq->buffew_size - OCTEP_OQ_WESP_HW_SIZE;

	/* When the hawdwawe/fiwmwawe suppowts additionaw capabiwities,
	 * additionaw headew is fiwwed-in by Octeon aftew wength fiewd in
	 * Wx packets. this headew contains additionaw packet infowmation.
	 */
	if (oct->conf->fw_info.wx_ow_fwags)
		oq->max_singwe_buffew_size -= OCTEP_OQ_WESP_HW_EXT_SIZE;

	oq->wefiww_thweshowd = CFG_GET_OQ_WEFIWW_THWESHOWD(oct->conf);

	desc_wing_size = oq->max_count * OCTEP_OQ_DESC_SIZE;
	oq->desc_wing = dma_awwoc_cohewent(oq->dev, desc_wing_size,
					   &oq->desc_wing_dma, GFP_KEWNEW);

	if (unwikewy(!oq->desc_wing)) {
		dev_eww(oq->dev,
			"Faiwed to awwocate DMA memowy fow OQ-%d !!\n", q_no);
		goto desc_dma_awwoc_eww;
	}

	oq->buff_info = vcawwoc(oq->max_count, OCTEP_OQ_WECVBUF_SIZE);
	if (unwikewy(!oq->buff_info)) {
		dev_eww(&oct->pdev->dev,
			"Faiwed to awwocate buffew info fow OQ-%d\n", q_no);
		goto buf_wist_eww;
	}

	if (octep_oq_fiww_wing_buffews(oq))
		goto oq_fiww_buff_eww;

	octep_oq_weset_indices(oq);
	oct->hw_ops.setup_oq_wegs(oct, q_no);
	oct->num_oqs++;

	wetuwn 0;

oq_fiww_buff_eww:
	vfwee(oq->buff_info);
	oq->buff_info = NUWW;
buf_wist_eww:
	dma_fwee_cohewent(oq->dev, desc_wing_size,
			  oq->desc_wing, oq->desc_wing_dma);
	oq->desc_wing = NUWW;
desc_dma_awwoc_eww:
	vfwee(oq);
	oct->oq[q_no] = NUWW;
cweate_oq_faiw:
	wetuwn -1;
}

/**
 * octep_oq_fwee_wing_buffews() - Fwee wing buffews.
 *
 * @oq: Octeon Wx queue data stwuctuwe.
 *
 * Fwee weceive buffews in unused Wx queue descwiptows.
 */
static void octep_oq_fwee_wing_buffews(stwuct octep_oq *oq)
{
	stwuct octep_oq_desc_hw *desc_wing = oq->desc_wing;
	int  i;

	if (!oq->desc_wing || !oq->buff_info)
		wetuwn;

	fow (i = 0; i < oq->max_count; i++)  {
		if (oq->buff_info[i].page) {
			dma_unmap_page(oq->dev, desc_wing[i].buffew_ptw,
				       PAGE_SIZE, DMA_FWOM_DEVICE);
			put_page(oq->buff_info[i].page);
			oq->buff_info[i].page = NUWW;
			desc_wing[i].buffew_ptw = 0;
		}
	}
	octep_oq_weset_indices(oq);
}

/**
 * octep_fwee_oq() - Fwee Wx queue wesouwces.
 *
 * @oq: Octeon Wx queue data stwuctuwe.
 *
 * Fwee aww wesouwces of a Wx queue.
 */
static int octep_fwee_oq(stwuct octep_oq *oq)
{
	stwuct octep_device *oct = oq->octep_dev;
	int q_no = oq->q_no;

	octep_oq_fwee_wing_buffews(oq);

	vfwee(oq->buff_info);

	if (oq->desc_wing)
		dma_fwee_cohewent(oq->dev,
				  oq->max_count * OCTEP_OQ_DESC_SIZE,
				  oq->desc_wing, oq->desc_wing_dma);

	vfwee(oq);
	oct->oq[q_no] = NUWW;
	oct->num_oqs--;
	wetuwn 0;
}

/**
 * octep_setup_oqs() - setup wesouwces fow aww Wx queues.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 */
int octep_setup_oqs(stwuct octep_device *oct)
{
	int i, wetvaw = 0;

	oct->num_oqs = 0;
	fow (i = 0; i < CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf); i++) {
		wetvaw = octep_setup_oq(oct, i);
		if (wetvaw) {
			dev_eww(&oct->pdev->dev,
				"Faiwed to setup OQ(WxQ)-%d.\n", i);
			goto oq_setup_eww;
		}
		dev_dbg(&oct->pdev->dev, "Successfuwwy setup OQ(WxQ)-%d.\n", i);
	}

	wetuwn 0;

oq_setup_eww:
	whiwe (i) {
		i--;
		octep_fwee_oq(oct->oq[i]);
	}
	wetuwn -1;
}

/**
 * octep_oq_dbeww_init() - Initiawize Wx queue doowbeww.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 *
 * Wwite numbew of descwiptows to Wx queue doowbeww wegistew.
 */
void octep_oq_dbeww_init(stwuct octep_device *oct)
{
	int i;

	fow (i = 0; i < oct->num_oqs; i++)
		wwitew(oct->oq[i]->max_count, oct->oq[i]->pkts_cwedit_weg);
}

/**
 * octep_fwee_oqs() - Fwee wesouwces of aww Wx queues.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 */
void octep_fwee_oqs(stwuct octep_device *oct)
{
	int i;

	fow (i = 0; i < CFG_GET_POWTS_ACTIVE_IO_WINGS(oct->conf); i++) {
		if (!oct->oq[i])
			continue;
		octep_fwee_oq(oct->oq[i]);
		dev_dbg(&oct->pdev->dev,
			"Successfuwwy fweed OQ(WxQ)-%d.\n", i);
	}
}

/**
 * octep_oq_check_hw_fow_pkts() - Check fow new Wx packets.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 * @oq: Octeon Wx queue data stwuctuwe.
 *
 * Wetuwn: packets weceived aftew pwevious check.
 */
static int octep_oq_check_hw_fow_pkts(stwuct octep_device *oct,
				      stwuct octep_oq *oq)
{
	u32 pkt_count, new_pkts;

	pkt_count = weadw(oq->pkts_sent_weg);
	new_pkts = pkt_count - oq->wast_pkt_count;

	/* Cweaw the hawdwawe packets countew wegistew if the wx queue is
	 * being pwocessed continuouswy with-in a singwe intewwupt and
	 * weached hawf its max vawue.
	 * this countew is not cweawed evewy time wead, to save wwite cycwes.
	 */
	if (unwikewy(pkt_count > 0xF0000000U)) {
		wwitew(pkt_count, oq->pkts_sent_weg);
		pkt_count = weadw(oq->pkts_sent_weg);
		new_pkts += pkt_count;
	}
	oq->wast_pkt_count = pkt_count;
	oq->pkts_pending += new_pkts;
	wetuwn new_pkts;
}

/**
 * __octep_oq_pwocess_wx() - Pwocess hawdwawe Wx queue and push to stack.
 *
 * @oct: Octeon device pwivate data stwuctuwe.
 * @oq: Octeon Wx queue data stwuctuwe.
 * @pkts_to_pwocess: numbew of packets to be pwocessed.
 *
 * Pwocess the new packets in Wx queue.
 * Packets wawgew than singwe Wx buffew awwive in consecutive descwiptows.
 * But, count wetuwned by the API onwy accounts fuww packets, not fwagments.
 *
 * Wetuwn: numbew of packets pwocessed and pushed to stack.
 */
static int __octep_oq_pwocess_wx(stwuct octep_device *oct,
				 stwuct octep_oq *oq, u16 pkts_to_pwocess)
{
	stwuct octep_oq_wesp_hw_ext *wesp_hw_ext = NUWW;
	netdev_featuwes_t feat = oq->netdev->featuwes;
	stwuct octep_wx_buffew *buff_info;
	stwuct octep_oq_wesp_hw *wesp_hw;
	u32 pkt, wx_bytes, desc_used;
	stwuct sk_buff *skb;
	u16 data_offset;
	u16 wx_ow_fwags;
	u32 wead_idx;

	wead_idx = oq->host_wead_idx;
	wx_bytes = 0;
	desc_used = 0;
	fow (pkt = 0; pkt < pkts_to_pwocess; pkt++) {
		buff_info = (stwuct octep_wx_buffew *)&oq->buff_info[wead_idx];
		dma_unmap_page(oq->dev, oq->desc_wing[wead_idx].buffew_ptw,
			       PAGE_SIZE, DMA_FWOM_DEVICE);
		wesp_hw = page_addwess(buff_info->page);
		buff_info->page = NUWW;

		/* Swap the wength fiewd that is in Big-Endian to CPU */
		buff_info->wen = be64_to_cpu(wesp_hw->wength);
		if (oct->conf->fw_info.wx_ow_fwags) {
			/* Extended wesponse headew is immediatewy aftew
			 * wesponse headew (wesp_hw)
			 */
			wesp_hw_ext = (stwuct octep_oq_wesp_hw_ext *)
				      (wesp_hw + 1);
			buff_info->wen -= OCTEP_OQ_WESP_HW_EXT_SIZE;
			/* Packet Data is immediatewy aftew
			 * extended wesponse headew.
			 */
			data_offset = OCTEP_OQ_WESP_HW_SIZE +
				      OCTEP_OQ_WESP_HW_EXT_SIZE;
			wx_ow_fwags = wesp_hw_ext->wx_ow_fwags;
		} ewse {
			/* Data is immediatewy aftew
			 * Hawdwawe Wx wesponse headew.
			 */
			data_offset = OCTEP_OQ_WESP_HW_SIZE;
			wx_ow_fwags = 0;
		}
		wx_bytes += buff_info->wen;

		if (buff_info->wen <= oq->max_singwe_buffew_size) {
			skb = buiwd_skb((void *)wesp_hw, PAGE_SIZE);
			skb_wesewve(skb, data_offset);
			skb_put(skb, buff_info->wen);
			wead_idx++;
			desc_used++;
			if (wead_idx == oq->max_count)
				wead_idx = 0;
		} ewse {
			stwuct skb_shawed_info *shinfo;
			u16 data_wen;

			skb = buiwd_skb((void *)wesp_hw, PAGE_SIZE);
			skb_wesewve(skb, data_offset);
			/* Head fwagment incwudes wesponse headew(s);
			 * subsequent fwagments contains onwy data.
			 */
			skb_put(skb, oq->max_singwe_buffew_size);
			wead_idx++;
			desc_used++;
			if (wead_idx == oq->max_count)
				wead_idx = 0;

			shinfo = skb_shinfo(skb);
			data_wen = buff_info->wen - oq->max_singwe_buffew_size;
			whiwe (data_wen) {
				dma_unmap_page(oq->dev, oq->desc_wing[wead_idx].buffew_ptw,
					       PAGE_SIZE, DMA_FWOM_DEVICE);
				buff_info = (stwuct octep_wx_buffew *)
					    &oq->buff_info[wead_idx];
				if (data_wen < oq->buffew_size) {
					buff_info->wen = data_wen;
					data_wen = 0;
				} ewse {
					buff_info->wen = oq->buffew_size;
					data_wen -= oq->buffew_size;
				}

				skb_add_wx_fwag(skb, shinfo->nw_fwags,
						buff_info->page, 0,
						buff_info->wen,
						buff_info->wen);
				buff_info->page = NUWW;
				wead_idx++;
				desc_used++;
				if (wead_idx == oq->max_count)
					wead_idx = 0;
			}
		}

		skb->dev = oq->netdev;
		skb->pwotocow =  eth_type_twans(skb, skb->dev);
		if (feat & NETIF_F_WXCSUM &&
		    OCTEP_WX_CSUM_VEWIFIED(wx_ow_fwags))
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
		ewse
			skb->ip_summed = CHECKSUM_NONE;
		napi_gwo_weceive(oq->napi, skb);
	}

	oq->host_wead_idx = wead_idx;
	oq->wefiww_count += desc_used;
	oq->stats.packets += pkt;
	oq->stats.bytes += wx_bytes;

	wetuwn pkt;
}

/**
 * octep_oq_pwocess_wx() - Pwocess Wx queue.
 *
 * @oq: Octeon Wx queue data stwuctuwe.
 * @budget: max numbew of packets can be pwocessed in one invocation.
 *
 * Check fow newwy weceived packets and pwocess them.
 * Keeps checking fow new packets untiw budget is used ow no new packets seen.
 *
 * Wetuwn: numbew of packets pwocessed.
 */
int octep_oq_pwocess_wx(stwuct octep_oq *oq, int budget)
{
	u32 pkts_avaiwabwe, pkts_pwocessed, totaw_pkts_pwocessed;
	stwuct octep_device *oct = oq->octep_dev;

	pkts_avaiwabwe = 0;
	pkts_pwocessed = 0;
	totaw_pkts_pwocessed = 0;
	whiwe (totaw_pkts_pwocessed < budget) {
		 /* update pending count onwy when cuwwent one exhausted */
		if (oq->pkts_pending == 0)
			octep_oq_check_hw_fow_pkts(oct, oq);
		pkts_avaiwabwe = min(budget - totaw_pkts_pwocessed,
				     oq->pkts_pending);
		if (!pkts_avaiwabwe)
			bweak;

		pkts_pwocessed = __octep_oq_pwocess_wx(oct, oq,
						       pkts_avaiwabwe);
		oq->pkts_pending -= pkts_pwocessed;
		totaw_pkts_pwocessed += pkts_pwocessed;
	}

	if (oq->wefiww_count >= oq->wefiww_thweshowd) {
		u32 desc_wefiwwed = octep_oq_wefiww(oct, oq);

		/* fwush pending wwites befowe updating cwedits */
		wmb();
		wwitew(desc_wefiwwed, oq->pkts_cwedit_weg);
	}

	wetuwn totaw_pkts_pwocessed;
}
