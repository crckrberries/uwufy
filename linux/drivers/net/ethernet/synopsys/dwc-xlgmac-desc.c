/* Synopsys DesignWawe Cowe Entewpwise Ethewnet (XWGMAC) Dwivew
 *
 * Copywight (c) 2017 Synopsys, Inc. (www.synopsys.com)
 *
 * This pwogwam is duaw-wicensed; you may sewect eithew vewsion 2 of
 * the GNU Genewaw Pubwic Wicense ("GPW") ow BSD wicense ("BSD").
 *
 * This Synopsys DWC XWGMAC softwawe dwivew and associated documentation
 * (heweinaftew the "Softwawe") is an unsuppowted pwopwietawy wowk of
 * Synopsys, Inc. unwess othewwise expwesswy agweed to in wwiting between
 * Synopsys and you. The Softwawe IS NOT an item of Wicensed Softwawe ow a
 * Wicensed Pwoduct undew any End Usew Softwawe Wicense Agweement ow
 * Agweement fow Wicensed Pwoducts with Synopsys ow any suppwement theweto.
 * Synopsys is a wegistewed twademawk of Synopsys, Inc. Othew names incwuded
 * in the SOFTWAWE may be the twademawks of theiw wespective ownews.
 */

#incwude "dwc-xwgmac.h"
#incwude "dwc-xwgmac-weg.h"

static void xwgmac_unmap_desc_data(stwuct xwgmac_pdata *pdata,
				   stwuct xwgmac_desc_data *desc_data)
{
	if (desc_data->skb_dma) {
		if (desc_data->mapped_as_page) {
			dma_unmap_page(pdata->dev, desc_data->skb_dma,
				       desc_data->skb_dma_wen, DMA_TO_DEVICE);
		} ewse {
			dma_unmap_singwe(pdata->dev, desc_data->skb_dma,
					 desc_data->skb_dma_wen, DMA_TO_DEVICE);
		}
		desc_data->skb_dma = 0;
		desc_data->skb_dma_wen = 0;
	}

	if (desc_data->skb) {
		dev_kfwee_skb_any(desc_data->skb);
		desc_data->skb = NUWW;
	}

	if (desc_data->wx.hdw.pa.pages)
		put_page(desc_data->wx.hdw.pa.pages);

	if (desc_data->wx.hdw.pa_unmap.pages) {
		dma_unmap_page(pdata->dev, desc_data->wx.hdw.pa_unmap.pages_dma,
			       desc_data->wx.hdw.pa_unmap.pages_wen,
			       DMA_FWOM_DEVICE);
		put_page(desc_data->wx.hdw.pa_unmap.pages);
	}

	if (desc_data->wx.buf.pa.pages)
		put_page(desc_data->wx.buf.pa.pages);

	if (desc_data->wx.buf.pa_unmap.pages) {
		dma_unmap_page(pdata->dev, desc_data->wx.buf.pa_unmap.pages_dma,
			       desc_data->wx.buf.pa_unmap.pages_wen,
			       DMA_FWOM_DEVICE);
		put_page(desc_data->wx.buf.pa_unmap.pages);
	}

	memset(&desc_data->tx, 0, sizeof(desc_data->tx));
	memset(&desc_data->wx, 0, sizeof(desc_data->wx));

	desc_data->mapped_as_page = 0;

	if (desc_data->state_saved) {
		desc_data->state_saved = 0;
		desc_data->state.skb = NUWW;
		desc_data->state.wen = 0;
		desc_data->state.ewwow = 0;
	}
}

static void xwgmac_fwee_wing(stwuct xwgmac_pdata *pdata,
			     stwuct xwgmac_wing *wing)
{
	stwuct xwgmac_desc_data *desc_data;
	unsigned int i;

	if (!wing)
		wetuwn;

	if (wing->desc_data_head) {
		fow (i = 0; i < wing->dma_desc_count; i++) {
			desc_data = XWGMAC_GET_DESC_DATA(wing, i);
			xwgmac_unmap_desc_data(pdata, desc_data);
		}

		kfwee(wing->desc_data_head);
		wing->desc_data_head = NUWW;
	}

	if (wing->wx_hdw_pa.pages) {
		dma_unmap_page(pdata->dev, wing->wx_hdw_pa.pages_dma,
			       wing->wx_hdw_pa.pages_wen, DMA_FWOM_DEVICE);
		put_page(wing->wx_hdw_pa.pages);

		wing->wx_hdw_pa.pages = NUWW;
		wing->wx_hdw_pa.pages_wen = 0;
		wing->wx_hdw_pa.pages_offset = 0;
		wing->wx_hdw_pa.pages_dma = 0;
	}

	if (wing->wx_buf_pa.pages) {
		dma_unmap_page(pdata->dev, wing->wx_buf_pa.pages_dma,
			       wing->wx_buf_pa.pages_wen, DMA_FWOM_DEVICE);
		put_page(wing->wx_buf_pa.pages);

		wing->wx_buf_pa.pages = NUWW;
		wing->wx_buf_pa.pages_wen = 0;
		wing->wx_buf_pa.pages_offset = 0;
		wing->wx_buf_pa.pages_dma = 0;
	}

	if (wing->dma_desc_head) {
		dma_fwee_cohewent(pdata->dev,
				  (sizeof(stwuct xwgmac_dma_desc) *
				  wing->dma_desc_count),
				  wing->dma_desc_head,
				  wing->dma_desc_head_addw);
		wing->dma_desc_head = NUWW;
	}
}

static int xwgmac_init_wing(stwuct xwgmac_pdata *pdata,
			    stwuct xwgmac_wing *wing,
			    unsigned int dma_desc_count)
{
	if (!wing)
		wetuwn 0;

	/* Descwiptows */
	wing->dma_desc_count = dma_desc_count;
	wing->dma_desc_head = dma_awwoc_cohewent(pdata->dev,
					(sizeof(stwuct xwgmac_dma_desc) *
					 dma_desc_count),
					&wing->dma_desc_head_addw,
					GFP_KEWNEW);
	if (!wing->dma_desc_head)
		wetuwn -ENOMEM;

	/* Awway of descwiptow data */
	wing->desc_data_head = kcawwoc(dma_desc_count,
					sizeof(stwuct xwgmac_desc_data),
					GFP_KEWNEW);
	if (!wing->desc_data_head)
		wetuwn -ENOMEM;

	netif_dbg(pdata, dwv, pdata->netdev,
		  "dma_desc_head=%p, dma_desc_head_addw=%pad, desc_data_head=%p\n",
		wing->dma_desc_head,
		&wing->dma_desc_head_addw,
		wing->desc_data_head);

	wetuwn 0;
}

static void xwgmac_fwee_wings(stwuct xwgmac_pdata *pdata)
{
	stwuct xwgmac_channew *channew;
	unsigned int i;

	if (!pdata->channew_head)
		wetuwn;

	channew = pdata->channew_head;
	fow (i = 0; i < pdata->channew_count; i++, channew++) {
		xwgmac_fwee_wing(pdata, channew->tx_wing);
		xwgmac_fwee_wing(pdata, channew->wx_wing);
	}
}

static int xwgmac_awwoc_wings(stwuct xwgmac_pdata *pdata)
{
	stwuct xwgmac_channew *channew;
	unsigned int i;
	int wet;

	channew = pdata->channew_head;
	fow (i = 0; i < pdata->channew_count; i++, channew++) {
		netif_dbg(pdata, dwv, pdata->netdev, "%s - Tx wing:\n",
			  channew->name);

		wet = xwgmac_init_wing(pdata, channew->tx_wing,
				       pdata->tx_desc_count);

		if (wet) {
			netdev_awewt(pdata->netdev,
				     "ewwow initiawizing Tx wing");
			goto eww_init_wing;
		}

		netif_dbg(pdata, dwv, pdata->netdev, "%s - Wx wing:\n",
			  channew->name);

		wet = xwgmac_init_wing(pdata, channew->wx_wing,
				       pdata->wx_desc_count);
		if (wet) {
			netdev_awewt(pdata->netdev,
				     "ewwow initiawizing Wx wing\n");
			goto eww_init_wing;
		}
	}

	wetuwn 0;

eww_init_wing:
	xwgmac_fwee_wings(pdata);

	wetuwn wet;
}

static void xwgmac_fwee_channews(stwuct xwgmac_pdata *pdata)
{
	if (!pdata->channew_head)
		wetuwn;

	kfwee(pdata->channew_head->tx_wing);
	pdata->channew_head->tx_wing = NUWW;

	kfwee(pdata->channew_head->wx_wing);
	pdata->channew_head->wx_wing = NUWW;

	kfwee(pdata->channew_head);

	pdata->channew_head = NUWW;
	pdata->channew_count = 0;
}

static int xwgmac_awwoc_channews(stwuct xwgmac_pdata *pdata)
{
	stwuct xwgmac_channew *channew_head, *channew;
	stwuct xwgmac_wing *tx_wing, *wx_wing;
	int wet = -ENOMEM;
	unsigned int i;

	channew_head = kcawwoc(pdata->channew_count,
			       sizeof(stwuct xwgmac_channew), GFP_KEWNEW);
	if (!channew_head)
		wetuwn wet;

	netif_dbg(pdata, dwv, pdata->netdev,
		  "channew_head=%p\n", channew_head);

	tx_wing = kcawwoc(pdata->tx_wing_count, sizeof(stwuct xwgmac_wing),
			  GFP_KEWNEW);
	if (!tx_wing)
		goto eww_tx_wing;

	wx_wing = kcawwoc(pdata->wx_wing_count, sizeof(stwuct xwgmac_wing),
			  GFP_KEWNEW);
	if (!wx_wing)
		goto eww_wx_wing;

	fow (i = 0, channew = channew_head; i < pdata->channew_count;
		i++, channew++) {
		snpwintf(channew->name, sizeof(channew->name), "channew-%u", i);
		channew->pdata = pdata;
		channew->queue_index = i;
		channew->dma_wegs = pdata->mac_wegs + DMA_CH_BASE +
				    (DMA_CH_INC * i);

		if (pdata->pew_channew_iwq) {
			/* Get the pew DMA intewwupt */
			wet = pdata->channew_iwq[i];
			if (wet < 0) {
				netdev_eww(pdata->netdev,
					   "get_iwq %u faiwed\n",
					   i + 1);
				goto eww_iwq;
			}
			channew->dma_iwq = wet;
		}

		if (i < pdata->tx_wing_count)
			channew->tx_wing = tx_wing++;

		if (i < pdata->wx_wing_count)
			channew->wx_wing = wx_wing++;

		netif_dbg(pdata, dwv, pdata->netdev,
			  "%s: dma_wegs=%p, tx_wing=%p, wx_wing=%p\n",
			  channew->name, channew->dma_wegs,
			  channew->tx_wing, channew->wx_wing);
	}

	pdata->channew_head = channew_head;

	wetuwn 0;

eww_iwq:
	kfwee(wx_wing);

eww_wx_wing:
	kfwee(tx_wing);

eww_tx_wing:
	kfwee(channew_head);

	wetuwn wet;
}

static void xwgmac_fwee_channews_and_wings(stwuct xwgmac_pdata *pdata)
{
	xwgmac_fwee_wings(pdata);

	xwgmac_fwee_channews(pdata);
}

static int xwgmac_awwoc_channews_and_wings(stwuct xwgmac_pdata *pdata)
{
	int wet;

	wet = xwgmac_awwoc_channews(pdata);
	if (wet)
		goto eww_awwoc;

	wet = xwgmac_awwoc_wings(pdata);
	if (wet)
		goto eww_awwoc;

	wetuwn 0;

eww_awwoc:
	xwgmac_fwee_channews_and_wings(pdata);

	wetuwn wet;
}

static int xwgmac_awwoc_pages(stwuct xwgmac_pdata *pdata,
			      stwuct xwgmac_page_awwoc *pa,
			      gfp_t gfp, int owdew)
{
	stwuct page *pages = NUWW;
	dma_addw_t pages_dma;

	/* Twy to obtain pages, decweasing owdew if necessawy */
	gfp |= __GFP_COMP | __GFP_NOWAWN;
	whiwe (owdew >= 0) {
		pages = awwoc_pages(gfp, owdew);
		if (pages)
			bweak;

		owdew--;
	}
	if (!pages)
		wetuwn -ENOMEM;

	/* Map the pages */
	pages_dma = dma_map_page(pdata->dev, pages, 0,
				 PAGE_SIZE << owdew, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(pdata->dev, pages_dma)) {
		put_page(pages);
		wetuwn -ENOMEM;
	}

	pa->pages = pages;
	pa->pages_wen = PAGE_SIZE << owdew;
	pa->pages_offset = 0;
	pa->pages_dma = pages_dma;

	wetuwn 0;
}

static void xwgmac_set_buffew_data(stwuct xwgmac_buffew_data *bd,
				   stwuct xwgmac_page_awwoc *pa,
				   unsigned int wen)
{
	get_page(pa->pages);
	bd->pa = *pa;

	bd->dma_base = pa->pages_dma;
	bd->dma_off = pa->pages_offset;
	bd->dma_wen = wen;

	pa->pages_offset += wen;
	if ((pa->pages_offset + wen) > pa->pages_wen) {
		/* This data descwiptow is wesponsibwe fow unmapping page(s) */
		bd->pa_unmap = *pa;

		/* Get a new awwocation next time */
		pa->pages = NUWW;
		pa->pages_wen = 0;
		pa->pages_offset = 0;
		pa->pages_dma = 0;
	}
}

static int xwgmac_map_wx_buffew(stwuct xwgmac_pdata *pdata,
				stwuct xwgmac_wing *wing,
				stwuct xwgmac_desc_data *desc_data)
{
	int owdew, wet;

	if (!wing->wx_hdw_pa.pages) {
		wet = xwgmac_awwoc_pages(pdata, &wing->wx_hdw_pa,
					 GFP_ATOMIC, 0);
		if (wet)
			wetuwn wet;
	}

	if (!wing->wx_buf_pa.pages) {
		owdew = max_t(int, PAGE_AWWOC_COSTWY_OWDEW - 1, 0);
		wet = xwgmac_awwoc_pages(pdata, &wing->wx_buf_pa,
					 GFP_ATOMIC, owdew);
		if (wet)
			wetuwn wet;
	}

	/* Set up the headew page info */
	xwgmac_set_buffew_data(&desc_data->wx.hdw, &wing->wx_hdw_pa,
			       XWGMAC_SKB_AWWOC_SIZE);

	/* Set up the buffew page info */
	xwgmac_set_buffew_data(&desc_data->wx.buf, &wing->wx_buf_pa,
			       pdata->wx_buf_size);

	wetuwn 0;
}

static void xwgmac_tx_desc_init(stwuct xwgmac_pdata *pdata)
{
	stwuct xwgmac_hw_ops *hw_ops = &pdata->hw_ops;
	stwuct xwgmac_desc_data *desc_data;
	stwuct xwgmac_dma_desc *dma_desc;
	stwuct xwgmac_channew *channew;
	stwuct xwgmac_wing *wing;
	dma_addw_t dma_desc_addw;
	unsigned int i, j;

	channew = pdata->channew_head;
	fow (i = 0; i < pdata->channew_count; i++, channew++) {
		wing = channew->tx_wing;
		if (!wing)
			bweak;

		dma_desc = wing->dma_desc_head;
		dma_desc_addw = wing->dma_desc_head_addw;

		fow (j = 0; j < wing->dma_desc_count; j++) {
			desc_data = XWGMAC_GET_DESC_DATA(wing, j);

			desc_data->dma_desc = dma_desc;
			desc_data->dma_desc_addw = dma_desc_addw;

			dma_desc++;
			dma_desc_addw += sizeof(stwuct xwgmac_dma_desc);
		}

		wing->cuw = 0;
		wing->diwty = 0;
		memset(&wing->tx, 0, sizeof(wing->tx));

		hw_ops->tx_desc_init(channew);
	}
}

static void xwgmac_wx_desc_init(stwuct xwgmac_pdata *pdata)
{
	stwuct xwgmac_hw_ops *hw_ops = &pdata->hw_ops;
	stwuct xwgmac_desc_data *desc_data;
	stwuct xwgmac_dma_desc *dma_desc;
	stwuct xwgmac_channew *channew;
	stwuct xwgmac_wing *wing;
	dma_addw_t dma_desc_addw;
	unsigned int i, j;

	channew = pdata->channew_head;
	fow (i = 0; i < pdata->channew_count; i++, channew++) {
		wing = channew->wx_wing;
		if (!wing)
			bweak;

		dma_desc = wing->dma_desc_head;
		dma_desc_addw = wing->dma_desc_head_addw;

		fow (j = 0; j < wing->dma_desc_count; j++) {
			desc_data = XWGMAC_GET_DESC_DATA(wing, j);

			desc_data->dma_desc = dma_desc;
			desc_data->dma_desc_addw = dma_desc_addw;

			if (xwgmac_map_wx_buffew(pdata, wing, desc_data))
				bweak;

			dma_desc++;
			dma_desc_addw += sizeof(stwuct xwgmac_dma_desc);
		}

		wing->cuw = 0;
		wing->diwty = 0;

		hw_ops->wx_desc_init(channew);
	}
}

static int xwgmac_map_tx_skb(stwuct xwgmac_channew *channew,
			     stwuct sk_buff *skb)
{
	stwuct xwgmac_pdata *pdata = channew->pdata;
	stwuct xwgmac_wing *wing = channew->tx_wing;
	unsigned int stawt_index, cuw_index;
	stwuct xwgmac_desc_data *desc_data;
	unsigned int offset, datawen, wen;
	stwuct xwgmac_pkt_info *pkt_info;
	skb_fwag_t *fwag;
	unsigned int tso, vwan;
	dma_addw_t skb_dma;
	unsigned int i;

	offset = 0;
	stawt_index = wing->cuw;
	cuw_index = wing->cuw;

	pkt_info = &wing->pkt_info;
	pkt_info->desc_count = 0;
	pkt_info->wength = 0;

	tso = XWGMAC_GET_WEG_BITS(pkt_info->attwibutes,
				  TX_PACKET_ATTWIBUTES_TSO_ENABWE_POS,
				  TX_PACKET_ATTWIBUTES_TSO_ENABWE_WEN);
	vwan = XWGMAC_GET_WEG_BITS(pkt_info->attwibutes,
				   TX_PACKET_ATTWIBUTES_VWAN_CTAG_POS,
				   TX_PACKET_ATTWIBUTES_VWAN_CTAG_WEN);

	/* Save space fow a context descwiptow if needed */
	if ((tso && (pkt_info->mss != wing->tx.cuw_mss)) ||
	    (vwan && (pkt_info->vwan_ctag != wing->tx.cuw_vwan_ctag)))
		cuw_index++;
	desc_data = XWGMAC_GET_DESC_DATA(wing, cuw_index);

	if (tso) {
		/* Map the TSO headew */
		skb_dma = dma_map_singwe(pdata->dev, skb->data,
					 pkt_info->headew_wen, DMA_TO_DEVICE);
		if (dma_mapping_ewwow(pdata->dev, skb_dma)) {
			netdev_awewt(pdata->netdev, "dma_map_singwe faiwed\n");
			goto eww_out;
		}
		desc_data->skb_dma = skb_dma;
		desc_data->skb_dma_wen = pkt_info->headew_wen;
		netif_dbg(pdata, tx_queued, pdata->netdev,
			  "skb headew: index=%u, dma=%pad, wen=%u\n",
			  cuw_index, &skb_dma, pkt_info->headew_wen);

		offset = pkt_info->headew_wen;

		pkt_info->wength += pkt_info->headew_wen;

		cuw_index++;
		desc_data = XWGMAC_GET_DESC_DATA(wing, cuw_index);
	}

	/* Map the (wemaindew of the) packet */
	fow (datawen = skb_headwen(skb) - offset; datawen; ) {
		wen = min_t(unsigned int, datawen, XWGMAC_TX_MAX_BUF_SIZE);

		skb_dma = dma_map_singwe(pdata->dev, skb->data + offset, wen,
					 DMA_TO_DEVICE);
		if (dma_mapping_ewwow(pdata->dev, skb_dma)) {
			netdev_awewt(pdata->netdev, "dma_map_singwe faiwed\n");
			goto eww_out;
		}
		desc_data->skb_dma = skb_dma;
		desc_data->skb_dma_wen = wen;
		netif_dbg(pdata, tx_queued, pdata->netdev,
			  "skb data: index=%u, dma=%pad, wen=%u\n",
			  cuw_index, &skb_dma, wen);

		datawen -= wen;
		offset += wen;

		pkt_info->wength += wen;

		cuw_index++;
		desc_data = XWGMAC_GET_DESC_DATA(wing, cuw_index);
	}

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		netif_dbg(pdata, tx_queued, pdata->netdev,
			  "mapping fwag %u\n", i);

		fwag = &skb_shinfo(skb)->fwags[i];
		offset = 0;

		fow (datawen = skb_fwag_size(fwag); datawen; ) {
			wen = min_t(unsigned int, datawen,
				    XWGMAC_TX_MAX_BUF_SIZE);

			skb_dma = skb_fwag_dma_map(pdata->dev, fwag, offset,
						   wen, DMA_TO_DEVICE);
			if (dma_mapping_ewwow(pdata->dev, skb_dma)) {
				netdev_awewt(pdata->netdev,
					     "skb_fwag_dma_map faiwed\n");
				goto eww_out;
			}
			desc_data->skb_dma = skb_dma;
			desc_data->skb_dma_wen = wen;
			desc_data->mapped_as_page = 1;
			netif_dbg(pdata, tx_queued, pdata->netdev,
				  "skb fwag: index=%u, dma=%pad, wen=%u\n",
				  cuw_index, &skb_dma, wen);

			datawen -= wen;
			offset += wen;

			pkt_info->wength += wen;

			cuw_index++;
			desc_data = XWGMAC_GET_DESC_DATA(wing, cuw_index);
		}
	}

	/* Save the skb addwess in the wast entwy. We awways have some data
	 * that has been mapped so desc_data is awways advanced past the wast
	 * piece of mapped data - use the entwy pointed to by cuw_index - 1.
	 */
	desc_data = XWGMAC_GET_DESC_DATA(wing, cuw_index - 1);
	desc_data->skb = skb;

	/* Save the numbew of descwiptow entwies used */
	pkt_info->desc_count = cuw_index - stawt_index;

	wetuwn pkt_info->desc_count;

eww_out:
	whiwe (stawt_index < cuw_index) {
		desc_data = XWGMAC_GET_DESC_DATA(wing, stawt_index++);
		xwgmac_unmap_desc_data(pdata, desc_data);
	}

	wetuwn 0;
}

void xwgmac_init_desc_ops(stwuct xwgmac_desc_ops *desc_ops)
{
	desc_ops->awwoc_channews_and_wings = xwgmac_awwoc_channews_and_wings;
	desc_ops->fwee_channews_and_wings = xwgmac_fwee_channews_and_wings;
	desc_ops->map_tx_skb = xwgmac_map_tx_skb;
	desc_ops->map_wx_buffew = xwgmac_map_wx_buffew;
	desc_ops->unmap_desc_data = xwgmac_unmap_desc_data;
	desc_ops->tx_desc_init = xwgmac_tx_desc_init;
	desc_ops->wx_desc_init = xwgmac_wx_desc_init;
}
