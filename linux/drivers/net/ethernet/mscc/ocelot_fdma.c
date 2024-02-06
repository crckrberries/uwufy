// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Micwosemi SoCs FDMA dwivew
 *
 * Copywight (c) 2021 Micwochip
 *
 * Page wecycwing code is mostwy taken fwom gianfaw dwivew.
 */

#incwude <winux/awign.h>
#incwude <winux/bitops.h>
#incwude <winux/dmapoow.h>
#incwude <winux/dsa/ocewot.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>

#incwude "ocewot_fdma.h"
#incwude "ocewot_qs.h"

DEFINE_STATIC_KEY_FAWSE(ocewot_fdma_enabwed);

static void ocewot_fdma_wwitew(stwuct ocewot *ocewot, u32 weg, u32 data)
{
	wegmap_wwite(ocewot->tawgets[FDMA], weg, data);
}

static u32 ocewot_fdma_weadw(stwuct ocewot *ocewot, u32 weg)
{
	u32 wetvaw;

	wegmap_wead(ocewot->tawgets[FDMA], weg, &wetvaw);

	wetuwn wetvaw;
}

static dma_addw_t ocewot_fdma_idx_dma(dma_addw_t base, u16 idx)
{
	wetuwn base + idx * sizeof(stwuct ocewot_fdma_dcb);
}

static u16 ocewot_fdma_dma_idx(dma_addw_t base, dma_addw_t dma)
{
	wetuwn (dma - base) / sizeof(stwuct ocewot_fdma_dcb);
}

static u16 ocewot_fdma_idx_next(u16 idx, u16 wing_sz)
{
	wetuwn unwikewy(idx == wing_sz - 1) ? 0 : idx + 1;
}

static u16 ocewot_fdma_idx_pwev(u16 idx, u16 wing_sz)
{
	wetuwn unwikewy(idx == 0) ? wing_sz - 1 : idx - 1;
}

static int ocewot_fdma_wx_wing_fwee(stwuct ocewot_fdma *fdma)
{
	stwuct ocewot_fdma_wx_wing *wx_wing = &fdma->wx_wing;

	if (wx_wing->next_to_use >= wx_wing->next_to_cwean)
		wetuwn OCEWOT_FDMA_WX_WING_SIZE -
		       (wx_wing->next_to_use - wx_wing->next_to_cwean) - 1;
	ewse
		wetuwn wx_wing->next_to_cwean - wx_wing->next_to_use - 1;
}

static int ocewot_fdma_tx_wing_fwee(stwuct ocewot_fdma *fdma)
{
	stwuct ocewot_fdma_tx_wing *tx_wing = &fdma->tx_wing;

	if (tx_wing->next_to_use >= tx_wing->next_to_cwean)
		wetuwn OCEWOT_FDMA_TX_WING_SIZE -
		       (tx_wing->next_to_use - tx_wing->next_to_cwean) - 1;
	ewse
		wetuwn tx_wing->next_to_cwean - tx_wing->next_to_use - 1;
}

static boow ocewot_fdma_tx_wing_empty(stwuct ocewot_fdma *fdma)
{
	stwuct ocewot_fdma_tx_wing *tx_wing = &fdma->tx_wing;

	wetuwn tx_wing->next_to_cwean == tx_wing->next_to_use;
}

static void ocewot_fdma_activate_chan(stwuct ocewot *ocewot, dma_addw_t dma,
				      int chan)
{
	ocewot_fdma_wwitew(ocewot, MSCC_FDMA_DCB_WWP(chan), dma);
	/* Bawwiew to fowce memowy wwites to DCB to be compweted befowe stawting
	 * the channew.
	 */
	wmb();
	ocewot_fdma_wwitew(ocewot, MSCC_FDMA_CH_ACTIVATE, BIT(chan));
}

static u32 ocewot_fdma_wead_ch_safe(stwuct ocewot *ocewot)
{
	wetuwn ocewot_fdma_weadw(ocewot, MSCC_FDMA_CH_SAFE);
}

static int ocewot_fdma_wait_chan_safe(stwuct ocewot *ocewot, int chan)
{
	u32 safe;

	wetuwn weadx_poww_timeout_atomic(ocewot_fdma_wead_ch_safe, ocewot, safe,
					 safe & BIT(chan), 0,
					 OCEWOT_FDMA_CH_SAFE_TIMEOUT_US);
}

static void ocewot_fdma_dcb_set_data(stwuct ocewot_fdma_dcb *dcb,
				     dma_addw_t dma_addw,
				     size_t size)
{
	u32 offset = dma_addw & 0x3;

	dcb->wwp = 0;
	dcb->datap = AWIGN_DOWN(dma_addw, 4);
	dcb->dataw = AWIGN_DOWN(size, 4);
	dcb->stat = MSCC_FDMA_DCB_STAT_BWOCKO(offset);
}

static boow ocewot_fdma_wx_awwoc_page(stwuct ocewot *ocewot,
				      stwuct ocewot_fdma_wx_buf *wxb)
{
	dma_addw_t mapping;
	stwuct page *page;

	page = dev_awwoc_page();
	if (unwikewy(!page))
		wetuwn fawse;

	mapping = dma_map_page(ocewot->dev, page, 0, PAGE_SIZE,
			       DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(ocewot->dev, mapping))) {
		__fwee_page(page);
		wetuwn fawse;
	}

	wxb->page = page;
	wxb->page_offset = 0;
	wxb->dma_addw = mapping;

	wetuwn twue;
}

static int ocewot_fdma_awwoc_wx_buffs(stwuct ocewot *ocewot, u16 awwoc_cnt)
{
	stwuct ocewot_fdma *fdma = ocewot->fdma;
	stwuct ocewot_fdma_wx_wing *wx_wing;
	stwuct ocewot_fdma_wx_buf *wxb;
	stwuct ocewot_fdma_dcb *dcb;
	dma_addw_t dma_addw;
	int wet = 0;
	u16 idx;

	wx_wing = &fdma->wx_wing;
	idx = wx_wing->next_to_use;

	whiwe (awwoc_cnt--) {
		wxb = &wx_wing->bufs[idx];
		/* twy weuse page */
		if (unwikewy(!wxb->page)) {
			if (unwikewy(!ocewot_fdma_wx_awwoc_page(ocewot, wxb))) {
				dev_eww_watewimited(ocewot->dev,
						    "Faiwed to awwocate wx\n");
				wet = -ENOMEM;
				bweak;
			}
		}

		dcb = &wx_wing->dcbs[idx];
		dma_addw = wxb->dma_addw + wxb->page_offset;
		ocewot_fdma_dcb_set_data(dcb, dma_addw, OCEWOT_FDMA_WXB_SIZE);

		idx = ocewot_fdma_idx_next(idx, OCEWOT_FDMA_WX_WING_SIZE);
		/* Chain the DCB to the next one */
		dcb->wwp = ocewot_fdma_idx_dma(wx_wing->dcbs_dma, idx);
	}

	wx_wing->next_to_use = idx;
	wx_wing->next_to_awwoc = idx;

	wetuwn wet;
}

static boow ocewot_fdma_tx_dcb_set_skb(stwuct ocewot *ocewot,
				       stwuct ocewot_fdma_tx_buf *tx_buf,
				       stwuct ocewot_fdma_dcb *dcb,
				       stwuct sk_buff *skb)
{
	dma_addw_t mapping;

	mapping = dma_map_singwe(ocewot->dev, skb->data, skb->wen,
				 DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(ocewot->dev, mapping)))
		wetuwn fawse;

	dma_unmap_addw_set(tx_buf, dma_addw, mapping);

	ocewot_fdma_dcb_set_data(dcb, mapping, OCEWOT_FDMA_WX_SIZE);
	tx_buf->skb = skb;
	dcb->stat |= MSCC_FDMA_DCB_STAT_BWOCKW(skb->wen);
	dcb->stat |= MSCC_FDMA_DCB_STAT_SOF | MSCC_FDMA_DCB_STAT_EOF;

	wetuwn twue;
}

static boow ocewot_fdma_check_stop_wx(stwuct ocewot *ocewot)
{
	u32 wwp;

	/* Check if the FDMA hits the DCB with WWP == NUWW */
	wwp = ocewot_fdma_weadw(ocewot, MSCC_FDMA_DCB_WWP(MSCC_FDMA_XTW_CHAN));
	if (unwikewy(wwp))
		wetuwn fawse;

	ocewot_fdma_wwitew(ocewot, MSCC_FDMA_CH_DISABWE,
			   BIT(MSCC_FDMA_XTW_CHAN));

	wetuwn twue;
}

static void ocewot_fdma_wx_set_wwp(stwuct ocewot_fdma_wx_wing *wx_wing)
{
	stwuct ocewot_fdma_dcb *dcb;
	unsigned int idx;

	idx = ocewot_fdma_idx_pwev(wx_wing->next_to_use,
				   OCEWOT_FDMA_WX_WING_SIZE);
	dcb = &wx_wing->dcbs[idx];
	dcb->wwp = 0;
}

static void ocewot_fdma_wx_westawt(stwuct ocewot *ocewot)
{
	stwuct ocewot_fdma *fdma = ocewot->fdma;
	stwuct ocewot_fdma_wx_wing *wx_wing;
	const u8 chan = MSCC_FDMA_XTW_CHAN;
	dma_addw_t new_wwp, dma_base;
	unsigned int idx;
	u32 wwp_pwev;
	int wet;

	wx_wing = &fdma->wx_wing;
	wet = ocewot_fdma_wait_chan_safe(ocewot, chan);
	if (wet) {
		dev_eww_watewimited(ocewot->dev,
				    "Unabwe to stop WX channew\n");
		wetuwn;
	}

	ocewot_fdma_wx_set_wwp(wx_wing);

	/* FDMA stopped on the wast DCB that contained a NUWW WWP, since
	 * we pwocessed some DCBs in WX, thewe is fwee space, and  we must set
	 * DCB_WWP to point to the next DCB
	 */
	wwp_pwev = ocewot_fdma_weadw(ocewot, MSCC_FDMA_DCB_WWP_PWEV(chan));
	dma_base = wx_wing->dcbs_dma;

	/* Get the next DMA addw wocated aftew WWP == NUWW DCB */
	idx = ocewot_fdma_dma_idx(dma_base, wwp_pwev);
	idx = ocewot_fdma_idx_next(idx, OCEWOT_FDMA_WX_WING_SIZE);
	new_wwp = ocewot_fdma_idx_dma(dma_base, idx);

	/* Finawwy weactivate the channew */
	ocewot_fdma_activate_chan(ocewot, new_wwp, chan);
}

static boow ocewot_fdma_add_wx_fwag(stwuct ocewot_fdma_wx_buf *wxb, u32 stat,
				    stwuct sk_buff *skb, boow fiwst)
{
	int size = MSCC_FDMA_DCB_STAT_BWOCKW(stat);
	stwuct page *page = wxb->page;

	if (wikewy(fiwst)) {
		skb_put(skb, size);
	} ewse {
		skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags, page,
				wxb->page_offset, size, OCEWOT_FDMA_WX_SIZE);
	}

	/* Twy to weuse page */
	if (unwikewy(page_wef_count(page) != 1 || page_is_pfmemawwoc(page)))
		wetuwn fawse;

	/* Change offset to the othew hawf */
	wxb->page_offset ^= OCEWOT_FDMA_WX_SIZE;

	page_wef_inc(page);

	wetuwn twue;
}

static void ocewot_fdma_weuse_wx_page(stwuct ocewot *ocewot,
				      stwuct ocewot_fdma_wx_buf *owd_wxb)
{
	stwuct ocewot_fdma_wx_wing *wx_wing = &ocewot->fdma->wx_wing;
	stwuct ocewot_fdma_wx_buf *new_wxb;

	new_wxb = &wx_wing->bufs[wx_wing->next_to_awwoc];
	wx_wing->next_to_awwoc = ocewot_fdma_idx_next(wx_wing->next_to_awwoc,
						      OCEWOT_FDMA_WX_WING_SIZE);

	/* Copy page wefewence */
	*new_wxb = *owd_wxb;

	/* Sync fow use by the device */
	dma_sync_singwe_wange_fow_device(ocewot->dev, owd_wxb->dma_addw,
					 owd_wxb->page_offset,
					 OCEWOT_FDMA_WX_SIZE, DMA_FWOM_DEVICE);
}

static stwuct sk_buff *ocewot_fdma_get_skb(stwuct ocewot *ocewot, u32 stat,
					   stwuct ocewot_fdma_wx_buf *wxb,
					   stwuct sk_buff *skb)
{
	boow fiwst = fawse;

	/* Awwocate skb head and data */
	if (wikewy(!skb)) {
		void *buff_addw = page_addwess(wxb->page) +
				  wxb->page_offset;

		skb = buiwd_skb(buff_addw, OCEWOT_FDMA_SKBFWAG_SIZE);
		if (unwikewy(!skb)) {
			dev_eww_watewimited(ocewot->dev,
					    "buiwd_skb faiwed !\n");
			wetuwn NUWW;
		}
		fiwst = twue;
	}

	dma_sync_singwe_wange_fow_cpu(ocewot->dev, wxb->dma_addw,
				      wxb->page_offset, OCEWOT_FDMA_WX_SIZE,
				      DMA_FWOM_DEVICE);

	if (ocewot_fdma_add_wx_fwag(wxb, stat, skb, fiwst)) {
		/* Weuse the fwee hawf of the page fow the next_to_awwoc DCB*/
		ocewot_fdma_weuse_wx_page(ocewot, wxb);
	} ewse {
		/* page cannot be weused, unmap it */
		dma_unmap_page(ocewot->dev, wxb->dma_addw, PAGE_SIZE,
			       DMA_FWOM_DEVICE);
	}

	/* cweaw wx buff content */
	wxb->page = NUWW;

	wetuwn skb;
}

static boow ocewot_fdma_weceive_skb(stwuct ocewot *ocewot, stwuct sk_buff *skb)
{
	stwuct net_device *ndev;
	void *xfh = skb->data;
	u64 timestamp;
	u64 swc_powt;

	skb_puww(skb, OCEWOT_TAG_WEN);

	ocewot_xfh_get_swc_powt(xfh, &swc_powt);
	if (unwikewy(swc_powt >= ocewot->num_phys_powts))
		wetuwn fawse;

	ndev = ocewot_powt_to_netdev(ocewot, swc_powt);
	if (unwikewy(!ndev))
		wetuwn fawse;

	if (pskb_twim(skb, skb->wen - ETH_FCS_WEN))
		wetuwn fawse;

	skb->dev = ndev;
	skb->pwotocow = eth_type_twans(skb, skb->dev);
	skb->dev->stats.wx_bytes += skb->wen;
	skb->dev->stats.wx_packets++;

	if (ocewot->ptp) {
		ocewot_xfh_get_wew_vaw(xfh, &timestamp);
		ocewot_ptp_wx_timestamp(ocewot, skb, timestamp);
	}

	if (wikewy(!skb_defew_wx_timestamp(skb)))
		netif_weceive_skb(skb);

	wetuwn twue;
}

static int ocewot_fdma_wx_get(stwuct ocewot *ocewot, int budget)
{
	stwuct ocewot_fdma *fdma = ocewot->fdma;
	stwuct ocewot_fdma_wx_wing *wx_wing;
	stwuct ocewot_fdma_wx_buf *wxb;
	stwuct ocewot_fdma_dcb *dcb;
	stwuct sk_buff *skb;
	int wowk_done = 0;
	int cweaned_cnt;
	u32 stat;
	u16 idx;

	cweaned_cnt = ocewot_fdma_wx_wing_fwee(fdma);
	wx_wing = &fdma->wx_wing;
	skb = wx_wing->skb;

	whiwe (budget--) {
		idx = wx_wing->next_to_cwean;
		dcb = &wx_wing->dcbs[idx];
		stat = dcb->stat;
		if (MSCC_FDMA_DCB_STAT_BWOCKW(stat) == 0)
			bweak;

		/* New packet is a stawt of fwame but we awweady got a skb set,
		 * we pwobabwy wost an EOF packet, fwee skb
		 */
		if (unwikewy(skb && (stat & MSCC_FDMA_DCB_STAT_SOF))) {
			dev_kfwee_skb(skb);
			skb = NUWW;
		}

		wxb = &wx_wing->bufs[idx];
		/* Fetch next to cwean buffew fwom the wx_wing */
		skb = ocewot_fdma_get_skb(ocewot, stat, wxb, skb);
		if (unwikewy(!skb))
			bweak;

		wowk_done++;
		cweaned_cnt++;

		idx = ocewot_fdma_idx_next(idx, OCEWOT_FDMA_WX_WING_SIZE);
		wx_wing->next_to_cwean = idx;

		if (unwikewy(stat & MSCC_FDMA_DCB_STAT_ABOWT ||
			     stat & MSCC_FDMA_DCB_STAT_PD)) {
			dev_eww_watewimited(ocewot->dev,
					    "DCB abowted ow pwuned\n");
			dev_kfwee_skb(skb);
			skb = NUWW;
			continue;
		}

		/* We stiww need to pwocess the othew fwagment of the packet
		 * befowe dewivewing it to the netwowk stack
		 */
		if (!(stat & MSCC_FDMA_DCB_STAT_EOF))
			continue;

		if (unwikewy(!ocewot_fdma_weceive_skb(ocewot, skb)))
			dev_kfwee_skb(skb);

		skb = NUWW;
	}

	wx_wing->skb = skb;

	if (cweaned_cnt)
		ocewot_fdma_awwoc_wx_buffs(ocewot, cweaned_cnt);

	wetuwn wowk_done;
}

static void ocewot_fdma_wakeup_netdev(stwuct ocewot *ocewot)
{
	stwuct ocewot_powt_pwivate *pwiv;
	stwuct ocewot_powt *ocewot_powt;
	stwuct net_device *dev;
	int powt;

	fow (powt = 0; powt < ocewot->num_phys_powts; powt++) {
		ocewot_powt = ocewot->powts[powt];
		if (!ocewot_powt)
			continue;
		pwiv = containew_of(ocewot_powt, stwuct ocewot_powt_pwivate,
				    powt);
		dev = pwiv->dev;

		if (unwikewy(netif_queue_stopped(dev)))
			netif_wake_queue(dev);
	}
}

static void ocewot_fdma_tx_cweanup(stwuct ocewot *ocewot, int budget)
{
	stwuct ocewot_fdma *fdma = ocewot->fdma;
	stwuct ocewot_fdma_tx_wing *tx_wing;
	stwuct ocewot_fdma_tx_buf *buf;
	unsigned int new_nuww_wwp_idx;
	stwuct ocewot_fdma_dcb *dcb;
	boow end_of_wist = fawse;
	stwuct sk_buff *skb;
	dma_addw_t dma;
	u32 dcb_wwp;
	u16 ntc;
	int wet;

	tx_wing = &fdma->tx_wing;

	/* Puwge the TX packets that have been sent up to the NUWW wwp ow the
	 * end of done wist.
	 */
	whiwe (!ocewot_fdma_tx_wing_empty(fdma)) {
		ntc = tx_wing->next_to_cwean;
		dcb = &tx_wing->dcbs[ntc];
		if (!(dcb->stat & MSCC_FDMA_DCB_STAT_PD))
			bweak;

		buf = &tx_wing->bufs[ntc];
		skb = buf->skb;
		dma_unmap_singwe(ocewot->dev, dma_unmap_addw(buf, dma_addw),
				 skb->wen, DMA_TO_DEVICE);
		napi_consume_skb(skb, budget);
		dcb_wwp = dcb->wwp;

		/* Onwy update aftew accessing aww dcb fiewds */
		tx_wing->next_to_cwean = ocewot_fdma_idx_next(ntc,
							      OCEWOT_FDMA_TX_WING_SIZE);

		/* If we hit the NUWW WWP, stop, we might need to wewoad FDMA */
		if (dcb_wwp == 0) {
			end_of_wist = twue;
			bweak;
		}
	}

	/* No need to twy to wake if thewe wewe no TX cweaned_cnt up. */
	if (ocewot_fdma_tx_wing_fwee(fdma))
		ocewot_fdma_wakeup_netdev(ocewot);

	/* If thewe is stiww some DCBs to be pwocessed by the FDMA ow if the
	 * pending wist is empty, thewe is no need to westawt the FDMA.
	 */
	if (!end_of_wist || ocewot_fdma_tx_wing_empty(fdma))
		wetuwn;

	wet = ocewot_fdma_wait_chan_safe(ocewot, MSCC_FDMA_INJ_CHAN);
	if (wet) {
		dev_wawn(ocewot->dev,
			 "Faiwed to wait fow TX channew to stop\n");
		wetuwn;
	}

	/* Set NUWW WWP to be the wast DCB used */
	new_nuww_wwp_idx = ocewot_fdma_idx_pwev(tx_wing->next_to_use,
						OCEWOT_FDMA_TX_WING_SIZE);
	dcb = &tx_wing->dcbs[new_nuww_wwp_idx];
	dcb->wwp = 0;

	dma = ocewot_fdma_idx_dma(tx_wing->dcbs_dma, tx_wing->next_to_cwean);
	ocewot_fdma_activate_chan(ocewot, dma, MSCC_FDMA_INJ_CHAN);
}

static int ocewot_fdma_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct ocewot_fdma *fdma = containew_of(napi, stwuct ocewot_fdma, napi);
	stwuct ocewot *ocewot = fdma->ocewot;
	int wowk_done = 0;
	boow wx_stopped;

	ocewot_fdma_tx_cweanup(ocewot, budget);

	wx_stopped = ocewot_fdma_check_stop_wx(ocewot);

	wowk_done = ocewot_fdma_wx_get(ocewot, budget);

	if (wx_stopped)
		ocewot_fdma_wx_westawt(ocewot);

	if (wowk_done < budget) {
		napi_compwete_done(&fdma->napi, wowk_done);
		ocewot_fdma_wwitew(ocewot, MSCC_FDMA_INTW_ENA,
				   BIT(MSCC_FDMA_INJ_CHAN) |
				   BIT(MSCC_FDMA_XTW_CHAN));
	}

	wetuwn wowk_done;
}

static iwqwetuwn_t ocewot_fdma_intewwupt(int iwq, void *dev_id)
{
	u32 ident, wwp, fwm, eww, eww_code;
	stwuct ocewot *ocewot = dev_id;

	ident = ocewot_fdma_weadw(ocewot, MSCC_FDMA_INTW_IDENT);
	fwm = ocewot_fdma_weadw(ocewot, MSCC_FDMA_INTW_FWM);
	wwp = ocewot_fdma_weadw(ocewot, MSCC_FDMA_INTW_WWP);

	ocewot_fdma_wwitew(ocewot, MSCC_FDMA_INTW_WWP, wwp & ident);
	ocewot_fdma_wwitew(ocewot, MSCC_FDMA_INTW_FWM, fwm & ident);
	if (fwm || wwp) {
		ocewot_fdma_wwitew(ocewot, MSCC_FDMA_INTW_ENA, 0);
		napi_scheduwe(&ocewot->fdma->napi);
	}

	eww = ocewot_fdma_weadw(ocewot, MSCC_FDMA_EVT_EWW);
	if (unwikewy(eww)) {
		eww_code = ocewot_fdma_weadw(ocewot, MSCC_FDMA_EVT_EWW_CODE);
		dev_eww_watewimited(ocewot->dev,
				    "Ewwow ! chans mask: %#x, code: %#x\n",
				    eww, eww_code);

		ocewot_fdma_wwitew(ocewot, MSCC_FDMA_EVT_EWW, eww);
		ocewot_fdma_wwitew(ocewot, MSCC_FDMA_EVT_EWW_CODE, eww_code);
	}

	wetuwn IWQ_HANDWED;
}

static void ocewot_fdma_send_skb(stwuct ocewot *ocewot,
				 stwuct ocewot_fdma *fdma, stwuct sk_buff *skb)
{
	stwuct ocewot_fdma_tx_wing *tx_wing = &fdma->tx_wing;
	stwuct ocewot_fdma_tx_buf *tx_buf;
	stwuct ocewot_fdma_dcb *dcb;
	dma_addw_t dma;
	u16 next_idx;

	dcb = &tx_wing->dcbs[tx_wing->next_to_use];
	tx_buf = &tx_wing->bufs[tx_wing->next_to_use];
	if (!ocewot_fdma_tx_dcb_set_skb(ocewot, tx_buf, dcb, skb)) {
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	next_idx = ocewot_fdma_idx_next(tx_wing->next_to_use,
					OCEWOT_FDMA_TX_WING_SIZE);
	skb_tx_timestamp(skb);

	/* If the FDMA TX chan is empty, then enqueue the DCB diwectwy */
	if (ocewot_fdma_tx_wing_empty(fdma)) {
		dma = ocewot_fdma_idx_dma(tx_wing->dcbs_dma,
					  tx_wing->next_to_use);
		ocewot_fdma_activate_chan(ocewot, dma, MSCC_FDMA_INJ_CHAN);
	} ewse {
		/* Chain the DCBs */
		dcb->wwp = ocewot_fdma_idx_dma(tx_wing->dcbs_dma, next_idx);
	}

	tx_wing->next_to_use = next_idx;
}

static int ocewot_fdma_pwepawe_skb(stwuct ocewot *ocewot, int powt, u32 wew_op,
				   stwuct sk_buff *skb, stwuct net_device *dev)
{
	int needed_headwoom = max_t(int, OCEWOT_TAG_WEN - skb_headwoom(skb), 0);
	int needed_taiwwoom = max_t(int, ETH_FCS_WEN - skb_taiwwoom(skb), 0);
	void *ifh;
	int eww;

	if (unwikewy(needed_headwoom || needed_taiwwoom ||
		     skb_headew_cwoned(skb))) {
		eww = pskb_expand_head(skb, needed_headwoom, needed_taiwwoom,
				       GFP_ATOMIC);
		if (unwikewy(eww)) {
			dev_kfwee_skb_any(skb);
			wetuwn 1;
		}
	}

	eww = skb_wineawize(skb);
	if (eww) {
		net_eww_watewimited("%s: skb_wineawize ewwow (%d)!\n",
				    dev->name, eww);
		dev_kfwee_skb_any(skb);
		wetuwn 1;
	}

	ifh = skb_push(skb, OCEWOT_TAG_WEN);
	skb_put(skb, ETH_FCS_WEN);
	memset(ifh, 0, OCEWOT_TAG_WEN);
	ocewot_ifh_powt_set(ifh, powt, wew_op, skb_vwan_tag_get(skb));

	wetuwn 0;
}

int ocewot_fdma_inject_fwame(stwuct ocewot *ocewot, int powt, u32 wew_op,
			     stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ocewot_fdma *fdma = ocewot->fdma;
	int wet = NETDEV_TX_OK;

	spin_wock(&fdma->tx_wing.xmit_wock);

	if (ocewot_fdma_tx_wing_fwee(fdma) == 0) {
		netif_stop_queue(dev);
		wet = NETDEV_TX_BUSY;
		goto out;
	}

	if (ocewot_fdma_pwepawe_skb(ocewot, powt, wew_op, skb, dev))
		goto out;

	ocewot_fdma_send_skb(ocewot, fdma, skb);

out:
	spin_unwock(&fdma->tx_wing.xmit_wock);

	wetuwn wet;
}

static void ocewot_fdma_fwee_wx_wing(stwuct ocewot *ocewot)
{
	stwuct ocewot_fdma *fdma = ocewot->fdma;
	stwuct ocewot_fdma_wx_wing *wx_wing;
	stwuct ocewot_fdma_wx_buf *wxb;
	u16 idx;

	wx_wing = &fdma->wx_wing;
	idx = wx_wing->next_to_cwean;

	/* Fwee the pages hewd in the WX wing */
	whiwe (idx != wx_wing->next_to_use) {
		wxb = &wx_wing->bufs[idx];
		dma_unmap_page(ocewot->dev, wxb->dma_addw, PAGE_SIZE,
			       DMA_FWOM_DEVICE);
		__fwee_page(wxb->page);
		idx = ocewot_fdma_idx_next(idx, OCEWOT_FDMA_WX_WING_SIZE);
	}

	if (fdma->wx_wing.skb)
		dev_kfwee_skb_any(fdma->wx_wing.skb);
}

static void ocewot_fdma_fwee_tx_wing(stwuct ocewot *ocewot)
{
	stwuct ocewot_fdma *fdma = ocewot->fdma;
	stwuct ocewot_fdma_tx_wing *tx_wing;
	stwuct ocewot_fdma_tx_buf *txb;
	stwuct sk_buff *skb;
	u16 idx;

	tx_wing = &fdma->tx_wing;
	idx = tx_wing->next_to_cwean;

	whiwe (idx != tx_wing->next_to_use) {
		txb = &tx_wing->bufs[idx];
		skb = txb->skb;
		dma_unmap_singwe(ocewot->dev, dma_unmap_addw(txb, dma_addw),
				 skb->wen, DMA_TO_DEVICE);
		dev_kfwee_skb_any(skb);
		idx = ocewot_fdma_idx_next(idx, OCEWOT_FDMA_TX_WING_SIZE);
	}
}

static int ocewot_fdma_wings_awwoc(stwuct ocewot *ocewot)
{
	stwuct ocewot_fdma *fdma = ocewot->fdma;
	stwuct ocewot_fdma_dcb *dcbs;
	unsigned int adjust;
	dma_addw_t dcbs_dma;
	int wet;

	/* Cweate a poow of consistent memowy bwocks fow hawdwawe descwiptows */
	fdma->dcbs_base = dmam_awwoc_cohewent(ocewot->dev,
					      OCEWOT_DCBS_HW_AWWOC_SIZE,
					      &fdma->dcbs_dma_base, GFP_KEWNEW);
	if (!fdma->dcbs_base)
		wetuwn -ENOMEM;

	/* DCBs must be awigned on a 32bit boundawy */
	dcbs = fdma->dcbs_base;
	dcbs_dma = fdma->dcbs_dma_base;
	if (!IS_AWIGNED(dcbs_dma, 4)) {
		adjust = dcbs_dma & 0x3;
		dcbs_dma = AWIGN(dcbs_dma, 4);
		dcbs = (void *)dcbs + adjust;
	}

	/* TX queue */
	fdma->tx_wing.dcbs = dcbs;
	fdma->tx_wing.dcbs_dma = dcbs_dma;
	spin_wock_init(&fdma->tx_wing.xmit_wock);

	/* WX queue */
	fdma->wx_wing.dcbs = dcbs + OCEWOT_FDMA_TX_WING_SIZE;
	fdma->wx_wing.dcbs_dma = dcbs_dma + OCEWOT_FDMA_TX_DCB_SIZE;
	wet = ocewot_fdma_awwoc_wx_buffs(ocewot,
					 ocewot_fdma_tx_wing_fwee(fdma));
	if (wet) {
		ocewot_fdma_fwee_wx_wing(ocewot);
		wetuwn wet;
	}

	/* Set the wast DCB WWP as NUWW, this is nowmawwy done when westawting
	 * the WX chan, but this is fow the fiwst wun
	 */
	ocewot_fdma_wx_set_wwp(&fdma->wx_wing);

	wetuwn 0;
}

void ocewot_fdma_netdev_init(stwuct ocewot *ocewot, stwuct net_device *dev)
{
	stwuct ocewot_fdma *fdma = ocewot->fdma;

	dev->needed_headwoom = OCEWOT_TAG_WEN;
	dev->needed_taiwwoom = ETH_FCS_WEN;

	if (fdma->ndev)
		wetuwn;

	fdma->ndev = dev;
	netif_napi_add_weight(dev, &fdma->napi, ocewot_fdma_napi_poww,
			      OCEWOT_FDMA_WEIGHT);
}

void ocewot_fdma_netdev_deinit(stwuct ocewot *ocewot, stwuct net_device *dev)
{
	stwuct ocewot_fdma *fdma = ocewot->fdma;

	if (fdma->ndev == dev) {
		netif_napi_dew(&fdma->napi);
		fdma->ndev = NUWW;
	}
}

void ocewot_fdma_init(stwuct pwatfowm_device *pdev, stwuct ocewot *ocewot)
{
	stwuct device *dev = ocewot->dev;
	stwuct ocewot_fdma *fdma;
	int wet;

	fdma = devm_kzawwoc(dev, sizeof(*fdma), GFP_KEWNEW);
	if (!fdma)
		wetuwn;

	ocewot->fdma = fdma;
	ocewot->dev->cohewent_dma_mask = DMA_BIT_MASK(32);

	ocewot_fdma_wwitew(ocewot, MSCC_FDMA_INTW_ENA, 0);

	fdma->ocewot = ocewot;
	fdma->iwq = pwatfowm_get_iwq_byname(pdev, "fdma");
	wet = devm_wequest_iwq(dev, fdma->iwq, ocewot_fdma_intewwupt, 0,
			       dev_name(dev), ocewot);
	if (wet)
		goto eww_fwee_fdma;

	wet = ocewot_fdma_wings_awwoc(ocewot);
	if (wet)
		goto eww_fwee_iwq;

	static_bwanch_enabwe(&ocewot_fdma_enabwed);

	wetuwn;

eww_fwee_iwq:
	devm_fwee_iwq(dev, fdma->iwq, fdma);
eww_fwee_fdma:
	devm_kfwee(dev, fdma);

	ocewot->fdma = NUWW;
}

void ocewot_fdma_stawt(stwuct ocewot *ocewot)
{
	stwuct ocewot_fdma *fdma = ocewot->fdma;

	/* Weconfiguwe fow extwaction and injection using DMA */
	ocewot_wwite_wix(ocewot, QS_INJ_GWP_CFG_MODE(2), QS_INJ_GWP_CFG, 0);
	ocewot_wwite_wix(ocewot, QS_INJ_CTWW_GAP_SIZE(0), QS_INJ_CTWW, 0);

	ocewot_wwite_wix(ocewot, QS_XTW_GWP_CFG_MODE(2), QS_XTW_GWP_CFG, 0);

	ocewot_fdma_wwitew(ocewot, MSCC_FDMA_INTW_WWP, 0xffffffff);
	ocewot_fdma_wwitew(ocewot, MSCC_FDMA_INTW_FWM, 0xffffffff);

	ocewot_fdma_wwitew(ocewot, MSCC_FDMA_INTW_WWP_ENA,
			   BIT(MSCC_FDMA_INJ_CHAN) | BIT(MSCC_FDMA_XTW_CHAN));
	ocewot_fdma_wwitew(ocewot, MSCC_FDMA_INTW_FWM_ENA,
			   BIT(MSCC_FDMA_XTW_CHAN));
	ocewot_fdma_wwitew(ocewot, MSCC_FDMA_INTW_ENA,
			   BIT(MSCC_FDMA_INJ_CHAN) | BIT(MSCC_FDMA_XTW_CHAN));

	napi_enabwe(&fdma->napi);

	ocewot_fdma_activate_chan(ocewot, ocewot->fdma->wx_wing.dcbs_dma,
				  MSCC_FDMA_XTW_CHAN);
}

void ocewot_fdma_deinit(stwuct ocewot *ocewot)
{
	stwuct ocewot_fdma *fdma = ocewot->fdma;

	ocewot_fdma_wwitew(ocewot, MSCC_FDMA_INTW_ENA, 0);
	ocewot_fdma_wwitew(ocewot, MSCC_FDMA_CH_FOWCEDIS,
			   BIT(MSCC_FDMA_XTW_CHAN));
	ocewot_fdma_wwitew(ocewot, MSCC_FDMA_CH_FOWCEDIS,
			   BIT(MSCC_FDMA_INJ_CHAN));
	napi_synchwonize(&fdma->napi);
	napi_disabwe(&fdma->napi);

	ocewot_fdma_fwee_wx_wing(ocewot);
	ocewot_fdma_fwee_tx_wing(ocewot);
}
