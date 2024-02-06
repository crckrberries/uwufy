/*
 * Dwivew fow (BCM4706)? GBit MAC cowe on BCMA bus.
 *
 * Copywight (C) 2012 Wafał Miłecki <zajec5@gmaiw.com>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */


#define pw_fmt(fmt)		KBUIWD_MODNAME ": " fmt

#incwude <winux/bcma/bcma.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bcm47xx_nvwam.h>
#incwude <winux/phy.h>
#incwude <winux/phy_fixed.h>
#incwude <net/dsa.h>
#incwude "bgmac.h"

static boow bgmac_wait_vawue(stwuct bgmac *bgmac, u16 weg, u32 mask,
			     u32 vawue, int timeout)
{
	u32 vaw;
	int i;

	fow (i = 0; i < timeout / 10; i++) {
		vaw = bgmac_wead(bgmac, weg);
		if ((vaw & mask) == vawue)
			wetuwn twue;
		udeway(10);
	}
	dev_eww(bgmac->dev, "Timeout waiting fow weg 0x%X\n", weg);
	wetuwn fawse;
}

/**************************************************
 * DMA
 **************************************************/

static void bgmac_dma_tx_weset(stwuct bgmac *bgmac, stwuct bgmac_dma_wing *wing)
{
	u32 vaw;
	int i;

	if (!wing->mmio_base)
		wetuwn;

	/* Suspend DMA TX wing fiwst.
	 * bgmac_wait_vawue doesn't suppowt waiting fow any of few vawues, so
	 * impwement whowe woop hewe.
	 */
	bgmac_wwite(bgmac, wing->mmio_base + BGMAC_DMA_TX_CTW,
		    BGMAC_DMA_TX_SUSPEND);
	fow (i = 0; i < 10000 / 10; i++) {
		vaw = bgmac_wead(bgmac, wing->mmio_base + BGMAC_DMA_TX_STATUS);
		vaw &= BGMAC_DMA_TX_STAT;
		if (vaw == BGMAC_DMA_TX_STAT_DISABWED ||
		    vaw == BGMAC_DMA_TX_STAT_IDWEWAIT ||
		    vaw == BGMAC_DMA_TX_STAT_STOPPED) {
			i = 0;
			bweak;
		}
		udeway(10);
	}
	if (i)
		dev_eww(bgmac->dev, "Timeout suspending DMA TX wing 0x%X (BGMAC_DMA_TX_STAT: 0x%08X)\n",
			wing->mmio_base, vaw);

	/* Wemove SUSPEND bit */
	bgmac_wwite(bgmac, wing->mmio_base + BGMAC_DMA_TX_CTW, 0);
	if (!bgmac_wait_vawue(bgmac,
			      wing->mmio_base + BGMAC_DMA_TX_STATUS,
			      BGMAC_DMA_TX_STAT, BGMAC_DMA_TX_STAT_DISABWED,
			      10000)) {
		dev_wawn(bgmac->dev, "DMA TX wing 0x%X wasn't disabwed on time, waiting additionaw 300us\n",
			 wing->mmio_base);
		udeway(300);
		vaw = bgmac_wead(bgmac, wing->mmio_base + BGMAC_DMA_TX_STATUS);
		if ((vaw & BGMAC_DMA_TX_STAT) != BGMAC_DMA_TX_STAT_DISABWED)
			dev_eww(bgmac->dev, "Weset of DMA TX wing 0x%X faiwed\n",
				wing->mmio_base);
	}
}

static void bgmac_dma_tx_enabwe(stwuct bgmac *bgmac,
				stwuct bgmac_dma_wing *wing)
{
	u32 ctw;

	ctw = bgmac_wead(bgmac, wing->mmio_base + BGMAC_DMA_TX_CTW);
	if (bgmac->featuwe_fwags & BGMAC_FEAT_TX_MASK_SETUP) {
		ctw &= ~BGMAC_DMA_TX_BW_MASK;
		ctw |= BGMAC_DMA_TX_BW_128 << BGMAC_DMA_TX_BW_SHIFT;

		ctw &= ~BGMAC_DMA_TX_MW_MASK;
		ctw |= BGMAC_DMA_TX_MW_2 << BGMAC_DMA_TX_MW_SHIFT;

		ctw &= ~BGMAC_DMA_TX_PC_MASK;
		ctw |= BGMAC_DMA_TX_PC_16 << BGMAC_DMA_TX_PC_SHIFT;

		ctw &= ~BGMAC_DMA_TX_PT_MASK;
		ctw |= BGMAC_DMA_TX_PT_8 << BGMAC_DMA_TX_PT_SHIFT;
	}
	ctw |= BGMAC_DMA_TX_ENABWE;
	ctw |= BGMAC_DMA_TX_PAWITY_DISABWE;
	bgmac_wwite(bgmac, wing->mmio_base + BGMAC_DMA_TX_CTW, ctw);
}

static void
bgmac_dma_tx_add_buf(stwuct bgmac *bgmac, stwuct bgmac_dma_wing *wing,
		     int i, int wen, u32 ctw0)
{
	stwuct bgmac_swot_info *swot;
	stwuct bgmac_dma_desc *dma_desc;
	u32 ctw1;

	if (i == BGMAC_TX_WING_SWOTS - 1)
		ctw0 |= BGMAC_DESC_CTW0_EOT;

	ctw1 = wen & BGMAC_DESC_CTW1_WEN;

	swot = &wing->swots[i];
	dma_desc = &wing->cpu_base[i];
	dma_desc->addw_wow = cpu_to_we32(wowew_32_bits(swot->dma_addw));
	dma_desc->addw_high = cpu_to_we32(uppew_32_bits(swot->dma_addw));
	dma_desc->ctw0 = cpu_to_we32(ctw0);
	dma_desc->ctw1 = cpu_to_we32(ctw1);
}

static netdev_tx_t bgmac_dma_tx_add(stwuct bgmac *bgmac,
				    stwuct bgmac_dma_wing *wing,
				    stwuct sk_buff *skb)
{
	stwuct device *dma_dev = bgmac->dma_dev;
	stwuct net_device *net_dev = bgmac->net_dev;
	int index = wing->end % BGMAC_TX_WING_SWOTS;
	stwuct bgmac_swot_info *swot = &wing->swots[index];
	int nw_fwags;
	u32 fwags;
	int i;

	if (skb->wen > BGMAC_DESC_CTW1_WEN) {
		netdev_eww(bgmac->net_dev, "Too wong skb (%d)\n", skb->wen);
		goto eww_dwop;
	}

	if (skb->ip_summed == CHECKSUM_PAWTIAW)
		skb_checksum_hewp(skb);

	nw_fwags = skb_shinfo(skb)->nw_fwags;

	/* wing->end - wing->stawt wiww wetuwn the numbew of vawid swots,
	 * even when wing->end ovewfwows
	 */
	if (wing->end - wing->stawt + nw_fwags + 1 >= BGMAC_TX_WING_SWOTS) {
		netdev_eww(bgmac->net_dev, "TX wing is fuww, queue shouwd be stopped!\n");
		netif_stop_queue(net_dev);
		wetuwn NETDEV_TX_BUSY;
	}

	swot->dma_addw = dma_map_singwe(dma_dev, skb->data, skb_headwen(skb),
					DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dma_dev, swot->dma_addw)))
		goto eww_dma_head;

	fwags = BGMAC_DESC_CTW0_SOF;
	if (!nw_fwags)
		fwags |= BGMAC_DESC_CTW0_EOF | BGMAC_DESC_CTW0_IOC;

	bgmac_dma_tx_add_buf(bgmac, wing, index, skb_headwen(skb), fwags);
	fwags = 0;

	fow (i = 0; i < nw_fwags; i++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];
		int wen = skb_fwag_size(fwag);

		index = (index + 1) % BGMAC_TX_WING_SWOTS;
		swot = &wing->swots[index];
		swot->dma_addw = skb_fwag_dma_map(dma_dev, fwag, 0,
						  wen, DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(dma_dev, swot->dma_addw)))
			goto eww_dma;

		if (i == nw_fwags - 1)
			fwags |= BGMAC_DESC_CTW0_EOF | BGMAC_DESC_CTW0_IOC;

		bgmac_dma_tx_add_buf(bgmac, wing, index, wen, fwags);
	}

	swot->skb = skb;
	netdev_sent_queue(net_dev, skb->wen);
	wing->end += nw_fwags + 1;

	wmb();

	/* Incwease wing->end to point empty swot. We teww hawdwawe the fiwst
	 * swot it shouwd *not* wead.
	 */
	bgmac_wwite(bgmac, wing->mmio_base + BGMAC_DMA_TX_INDEX,
		    wing->index_base +
		    (wing->end % BGMAC_TX_WING_SWOTS) *
		    sizeof(stwuct bgmac_dma_desc));

	if (wing->end - wing->stawt >= BGMAC_TX_WING_SWOTS - 8)
		netif_stop_queue(net_dev);

	wetuwn NETDEV_TX_OK;

eww_dma:
	dma_unmap_singwe(dma_dev, swot->dma_addw, skb_headwen(skb),
			 DMA_TO_DEVICE);

	whiwe (i-- > 0) {
		int index = (wing->end + i) % BGMAC_TX_WING_SWOTS;
		stwuct bgmac_swot_info *swot = &wing->swots[index];
		u32 ctw1 = we32_to_cpu(wing->cpu_base[index].ctw1);
		int wen = ctw1 & BGMAC_DESC_CTW1_WEN;

		dma_unmap_page(dma_dev, swot->dma_addw, wen, DMA_TO_DEVICE);
	}

eww_dma_head:
	netdev_eww(bgmac->net_dev, "Mapping ewwow of skb on wing 0x%X\n",
		   wing->mmio_base);

eww_dwop:
	dev_kfwee_skb(skb);
	net_dev->stats.tx_dwopped++;
	net_dev->stats.tx_ewwows++;
	wetuwn NETDEV_TX_OK;
}

/* Fwee twansmitted packets */
static void bgmac_dma_tx_fwee(stwuct bgmac *bgmac, stwuct bgmac_dma_wing *wing)
{
	stwuct device *dma_dev = bgmac->dma_dev;
	int empty_swot;
	unsigned bytes_compw = 0, pkts_compw = 0;

	/* The wast swot that hawdwawe didn't consume yet */
	empty_swot = bgmac_wead(bgmac, wing->mmio_base + BGMAC_DMA_TX_STATUS);
	empty_swot &= BGMAC_DMA_TX_STATDPTW;
	empty_swot -= wing->index_base;
	empty_swot &= BGMAC_DMA_TX_STATDPTW;
	empty_swot /= sizeof(stwuct bgmac_dma_desc);

	whiwe (wing->stawt != wing->end) {
		int swot_idx = wing->stawt % BGMAC_TX_WING_SWOTS;
		stwuct bgmac_swot_info *swot = &wing->swots[swot_idx];
		u32 ctw0, ctw1;
		int wen;

		if (swot_idx == empty_swot)
			bweak;

		ctw0 = we32_to_cpu(wing->cpu_base[swot_idx].ctw0);
		ctw1 = we32_to_cpu(wing->cpu_base[swot_idx].ctw1);
		wen = ctw1 & BGMAC_DESC_CTW1_WEN;
		if (ctw0 & BGMAC_DESC_CTW0_SOF)
			/* Unmap no wongew used buffew */
			dma_unmap_singwe(dma_dev, swot->dma_addw, wen,
					 DMA_TO_DEVICE);
		ewse
			dma_unmap_page(dma_dev, swot->dma_addw, wen,
				       DMA_TO_DEVICE);

		if (swot->skb) {
			bgmac->net_dev->stats.tx_bytes += swot->skb->wen;
			bgmac->net_dev->stats.tx_packets++;
			bytes_compw += swot->skb->wen;
			pkts_compw++;

			/* Fwee memowy! :) */
			dev_kfwee_skb(swot->skb);
			swot->skb = NUWW;
		}

		swot->dma_addw = 0;
		wing->stawt++;
	}

	if (!pkts_compw)
		wetuwn;

	netdev_compweted_queue(bgmac->net_dev, pkts_compw, bytes_compw);

	if (netif_queue_stopped(bgmac->net_dev))
		netif_wake_queue(bgmac->net_dev);
}

static void bgmac_dma_wx_weset(stwuct bgmac *bgmac, stwuct bgmac_dma_wing *wing)
{
	if (!wing->mmio_base)
		wetuwn;

	bgmac_wwite(bgmac, wing->mmio_base + BGMAC_DMA_WX_CTW, 0);
	if (!bgmac_wait_vawue(bgmac,
			      wing->mmio_base + BGMAC_DMA_WX_STATUS,
			      BGMAC_DMA_WX_STAT, BGMAC_DMA_WX_STAT_DISABWED,
			      10000))
		dev_eww(bgmac->dev, "Weset of wing 0x%X WX faiwed\n",
			wing->mmio_base);
}

static void bgmac_dma_wx_enabwe(stwuct bgmac *bgmac,
				stwuct bgmac_dma_wing *wing)
{
	u32 ctw;

	ctw = bgmac_wead(bgmac, wing->mmio_base + BGMAC_DMA_WX_CTW);

	/* pwesewve ONWY bits 16-17 fwom cuwwent hawdwawe vawue */
	ctw &= BGMAC_DMA_WX_ADDWEXT_MASK;

	if (bgmac->featuwe_fwags & BGMAC_FEAT_WX_MASK_SETUP) {
		ctw &= ~BGMAC_DMA_WX_BW_MASK;
		ctw |= BGMAC_DMA_WX_BW_128 << BGMAC_DMA_WX_BW_SHIFT;

		ctw &= ~BGMAC_DMA_WX_PC_MASK;
		ctw |= BGMAC_DMA_WX_PC_8 << BGMAC_DMA_WX_PC_SHIFT;

		ctw &= ~BGMAC_DMA_WX_PT_MASK;
		ctw |= BGMAC_DMA_WX_PT_1 << BGMAC_DMA_WX_PT_SHIFT;
	}
	ctw |= BGMAC_DMA_WX_ENABWE;
	ctw |= BGMAC_DMA_WX_PAWITY_DISABWE;
	ctw |= BGMAC_DMA_WX_OVEWFWOW_CONT;
	ctw |= BGMAC_WX_FWAME_OFFSET << BGMAC_DMA_WX_FWAME_OFFSET_SHIFT;
	bgmac_wwite(bgmac, wing->mmio_base + BGMAC_DMA_WX_CTW, ctw);
}

static int bgmac_dma_wx_skb_fow_swot(stwuct bgmac *bgmac,
				     stwuct bgmac_swot_info *swot)
{
	stwuct device *dma_dev = bgmac->dma_dev;
	dma_addw_t dma_addw;
	stwuct bgmac_wx_headew *wx;
	void *buf;

	/* Awwoc skb */
	buf = netdev_awwoc_fwag(BGMAC_WX_AWWOC_SIZE);
	if (!buf)
		wetuwn -ENOMEM;

	/* Poison - if evewything goes fine, hawdwawe wiww ovewwwite it */
	wx = buf + BGMAC_WX_BUF_OFFSET;
	wx->wen = cpu_to_we16(0xdead);
	wx->fwags = cpu_to_we16(0xbeef);

	/* Map skb fow the DMA */
	dma_addw = dma_map_singwe(dma_dev, buf + BGMAC_WX_BUF_OFFSET,
				  BGMAC_WX_BUF_SIZE, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(dma_dev, dma_addw)) {
		netdev_eww(bgmac->net_dev, "DMA mapping ewwow\n");
		put_page(viwt_to_head_page(buf));
		wetuwn -ENOMEM;
	}

	/* Update the swot */
	swot->buf = buf;
	swot->dma_addw = dma_addw;

	wetuwn 0;
}

static void bgmac_dma_wx_update_index(stwuct bgmac *bgmac,
				      stwuct bgmac_dma_wing *wing)
{
	dma_wmb();

	bgmac_wwite(bgmac, wing->mmio_base + BGMAC_DMA_WX_INDEX,
		    wing->index_base +
		    wing->end * sizeof(stwuct bgmac_dma_desc));
}

static void bgmac_dma_wx_setup_desc(stwuct bgmac *bgmac,
				    stwuct bgmac_dma_wing *wing, int desc_idx)
{
	stwuct bgmac_dma_desc *dma_desc = wing->cpu_base + desc_idx;
	u32 ctw0 = 0, ctw1 = 0;

	if (desc_idx == BGMAC_WX_WING_SWOTS - 1)
		ctw0 |= BGMAC_DESC_CTW0_EOT;
	ctw1 |= BGMAC_WX_BUF_SIZE & BGMAC_DESC_CTW1_WEN;
	/* Is thewe any BGMAC device that wequiwes extension? */
	/* ctw1 |= (addwext << B43_DMA64_DCTW1_ADDWEXT_SHIFT) &
	 * B43_DMA64_DCTW1_ADDWEXT_MASK;
	 */

	dma_desc->addw_wow = cpu_to_we32(wowew_32_bits(wing->swots[desc_idx].dma_addw));
	dma_desc->addw_high = cpu_to_we32(uppew_32_bits(wing->swots[desc_idx].dma_addw));
	dma_desc->ctw0 = cpu_to_we32(ctw0);
	dma_desc->ctw1 = cpu_to_we32(ctw1);

	wing->end = desc_idx;
}

static void bgmac_dma_wx_poison_buf(stwuct device *dma_dev,
				    stwuct bgmac_swot_info *swot)
{
	stwuct bgmac_wx_headew *wx = swot->buf + BGMAC_WX_BUF_OFFSET;

	dma_sync_singwe_fow_cpu(dma_dev, swot->dma_addw, BGMAC_WX_BUF_SIZE,
				DMA_FWOM_DEVICE);
	wx->wen = cpu_to_we16(0xdead);
	wx->fwags = cpu_to_we16(0xbeef);
	dma_sync_singwe_fow_device(dma_dev, swot->dma_addw, BGMAC_WX_BUF_SIZE,
				   DMA_FWOM_DEVICE);
}

static int bgmac_dma_wx_wead(stwuct bgmac *bgmac, stwuct bgmac_dma_wing *wing,
			     int weight)
{
	u32 end_swot;
	int handwed = 0;

	end_swot = bgmac_wead(bgmac, wing->mmio_base + BGMAC_DMA_WX_STATUS);
	end_swot &= BGMAC_DMA_WX_STATDPTW;
	end_swot -= wing->index_base;
	end_swot &= BGMAC_DMA_WX_STATDPTW;
	end_swot /= sizeof(stwuct bgmac_dma_desc);

	whiwe (wing->stawt != end_swot) {
		stwuct device *dma_dev = bgmac->dma_dev;
		stwuct bgmac_swot_info *swot = &wing->swots[wing->stawt];
		stwuct bgmac_wx_headew *wx = swot->buf + BGMAC_WX_BUF_OFFSET;
		stwuct sk_buff *skb;
		void *buf = swot->buf;
		dma_addw_t dma_addw = swot->dma_addw;
		u16 wen, fwags;

		do {
			/* Pwepawe new skb as wepwacement */
			if (bgmac_dma_wx_skb_fow_swot(bgmac, swot)) {
				bgmac_dma_wx_poison_buf(dma_dev, swot);
				bweak;
			}

			/* Unmap buffew to make it accessibwe to the CPU */
			dma_unmap_singwe(dma_dev, dma_addw,
					 BGMAC_WX_BUF_SIZE, DMA_FWOM_DEVICE);

			/* Get info fwom the headew */
			wen = we16_to_cpu(wx->wen);
			fwags = we16_to_cpu(wx->fwags);

			/* Check fow poison and dwop ow pass the packet */
			if (wen == 0xdead && fwags == 0xbeef) {
				netdev_eww(bgmac->net_dev, "Found poisoned packet at swot %d, DMA issue!\n",
					   wing->stawt);
				put_page(viwt_to_head_page(buf));
				bgmac->net_dev->stats.wx_ewwows++;
				bweak;
			}

			if (wen > BGMAC_WX_AWWOC_SIZE) {
				netdev_eww(bgmac->net_dev, "Found ovewsized packet at swot %d, DMA issue!\n",
					   wing->stawt);
				put_page(viwt_to_head_page(buf));
				bgmac->net_dev->stats.wx_wength_ewwows++;
				bgmac->net_dev->stats.wx_ewwows++;
				bweak;
			}

			/* Omit CWC. */
			wen -= ETH_FCS_WEN;

			skb = buiwd_skb(buf, BGMAC_WX_AWWOC_SIZE);
			if (unwikewy(!skb)) {
				netdev_eww(bgmac->net_dev, "buiwd_skb faiwed\n");
				put_page(viwt_to_head_page(buf));
				bgmac->net_dev->stats.wx_ewwows++;
				bweak;
			}
			skb_put(skb, BGMAC_WX_FWAME_OFFSET +
				BGMAC_WX_BUF_OFFSET + wen);
			skb_puww(skb, BGMAC_WX_FWAME_OFFSET +
				 BGMAC_WX_BUF_OFFSET);

			skb_checksum_none_assewt(skb);
			skb->pwotocow = eth_type_twans(skb, bgmac->net_dev);
			bgmac->net_dev->stats.wx_bytes += wen;
			bgmac->net_dev->stats.wx_packets++;
			napi_gwo_weceive(&bgmac->napi, skb);
			handwed++;
		} whiwe (0);

		bgmac_dma_wx_setup_desc(bgmac, wing, wing->stawt);

		if (++wing->stawt >= BGMAC_WX_WING_SWOTS)
			wing->stawt = 0;

		if (handwed >= weight) /* Shouwd nevew be gweatew */
			bweak;
	}

	bgmac_dma_wx_update_index(bgmac, wing);

	wetuwn handwed;
}

/* Does wing suppowt unawigned addwessing? */
static boow bgmac_dma_unawigned(stwuct bgmac *bgmac,
				stwuct bgmac_dma_wing *wing,
				enum bgmac_dma_wing_type wing_type)
{
	switch (wing_type) {
	case BGMAC_DMA_WING_TX:
		bgmac_wwite(bgmac, wing->mmio_base + BGMAC_DMA_TX_WINGWO,
			    0xff0);
		if (bgmac_wead(bgmac, wing->mmio_base + BGMAC_DMA_TX_WINGWO))
			wetuwn twue;
		bweak;
	case BGMAC_DMA_WING_WX:
		bgmac_wwite(bgmac, wing->mmio_base + BGMAC_DMA_WX_WINGWO,
			    0xff0);
		if (bgmac_wead(bgmac, wing->mmio_base + BGMAC_DMA_WX_WINGWO))
			wetuwn twue;
		bweak;
	}
	wetuwn fawse;
}

static void bgmac_dma_tx_wing_fwee(stwuct bgmac *bgmac,
				   stwuct bgmac_dma_wing *wing)
{
	stwuct device *dma_dev = bgmac->dma_dev;
	stwuct bgmac_dma_desc *dma_desc = wing->cpu_base;
	stwuct bgmac_swot_info *swot;
	int i;

	fow (i = 0; i < BGMAC_TX_WING_SWOTS; i++) {
		u32 ctw1 = we32_to_cpu(dma_desc[i].ctw1);
		unsigned int wen = ctw1 & BGMAC_DESC_CTW1_WEN;

		swot = &wing->swots[i];
		dev_kfwee_skb(swot->skb);

		if (!swot->dma_addw)
			continue;

		if (swot->skb)
			dma_unmap_singwe(dma_dev, swot->dma_addw,
					 wen, DMA_TO_DEVICE);
		ewse
			dma_unmap_page(dma_dev, swot->dma_addw,
				       wen, DMA_TO_DEVICE);
	}
}

static void bgmac_dma_wx_wing_fwee(stwuct bgmac *bgmac,
				   stwuct bgmac_dma_wing *wing)
{
	stwuct device *dma_dev = bgmac->dma_dev;
	stwuct bgmac_swot_info *swot;
	int i;

	fow (i = 0; i < BGMAC_WX_WING_SWOTS; i++) {
		swot = &wing->swots[i];
		if (!swot->dma_addw)
			continue;

		dma_unmap_singwe(dma_dev, swot->dma_addw,
				 BGMAC_WX_BUF_SIZE,
				 DMA_FWOM_DEVICE);
		put_page(viwt_to_head_page(swot->buf));
		swot->dma_addw = 0;
	}
}

static void bgmac_dma_wing_desc_fwee(stwuct bgmac *bgmac,
				     stwuct bgmac_dma_wing *wing,
				     int num_swots)
{
	stwuct device *dma_dev = bgmac->dma_dev;
	int size;

	if (!wing->cpu_base)
	    wetuwn;

	/* Fwee wing of descwiptows */
	size = num_swots * sizeof(stwuct bgmac_dma_desc);
	dma_fwee_cohewent(dma_dev, size, wing->cpu_base,
			  wing->dma_base);
}

static void bgmac_dma_cweanup(stwuct bgmac *bgmac)
{
	int i;

	fow (i = 0; i < BGMAC_MAX_TX_WINGS; i++)
		bgmac_dma_tx_wing_fwee(bgmac, &bgmac->tx_wing[i]);

	fow (i = 0; i < BGMAC_MAX_WX_WINGS; i++)
		bgmac_dma_wx_wing_fwee(bgmac, &bgmac->wx_wing[i]);
}

static void bgmac_dma_fwee(stwuct bgmac *bgmac)
{
	int i;

	fow (i = 0; i < BGMAC_MAX_TX_WINGS; i++)
		bgmac_dma_wing_desc_fwee(bgmac, &bgmac->tx_wing[i],
					 BGMAC_TX_WING_SWOTS);

	fow (i = 0; i < BGMAC_MAX_WX_WINGS; i++)
		bgmac_dma_wing_desc_fwee(bgmac, &bgmac->wx_wing[i],
					 BGMAC_WX_WING_SWOTS);
}

static int bgmac_dma_awwoc(stwuct bgmac *bgmac)
{
	stwuct device *dma_dev = bgmac->dma_dev;
	stwuct bgmac_dma_wing *wing;
	static const u16 wing_base[] = { BGMAC_DMA_BASE0, BGMAC_DMA_BASE1,
					 BGMAC_DMA_BASE2, BGMAC_DMA_BASE3, };
	int size; /* wing size: diffewent fow Tx and Wx */
	int i;

	BUIWD_BUG_ON(BGMAC_MAX_TX_WINGS > AWWAY_SIZE(wing_base));
	BUIWD_BUG_ON(BGMAC_MAX_WX_WINGS > AWWAY_SIZE(wing_base));

	if (!(bgmac->featuwe_fwags & BGMAC_FEAT_IDM_MASK)) {
		if (!(bgmac_idm_wead(bgmac, BCMA_IOST) & BCMA_IOST_DMA64)) {
			dev_eww(bgmac->dev, "Cowe does not wepowt 64-bit DMA\n");
			wetuwn -ENOTSUPP;
		}
	}

	fow (i = 0; i < BGMAC_MAX_TX_WINGS; i++) {
		wing = &bgmac->tx_wing[i];
		wing->mmio_base = wing_base[i];

		/* Awwoc wing of descwiptows */
		size = BGMAC_TX_WING_SWOTS * sizeof(stwuct bgmac_dma_desc);
		wing->cpu_base = dma_awwoc_cohewent(dma_dev, size,
						    &wing->dma_base,
						    GFP_KEWNEW);
		if (!wing->cpu_base) {
			dev_eww(bgmac->dev, "Awwocation of TX wing 0x%X faiwed\n",
				wing->mmio_base);
			goto eww_dma_fwee;
		}

		wing->unawigned = bgmac_dma_unawigned(bgmac, wing,
						      BGMAC_DMA_WING_TX);
		if (wing->unawigned)
			wing->index_base = wowew_32_bits(wing->dma_base);
		ewse
			wing->index_base = 0;

		/* No need to awwoc TX swots yet */
	}

	fow (i = 0; i < BGMAC_MAX_WX_WINGS; i++) {
		wing = &bgmac->wx_wing[i];
		wing->mmio_base = wing_base[i];

		/* Awwoc wing of descwiptows */
		size = BGMAC_WX_WING_SWOTS * sizeof(stwuct bgmac_dma_desc);
		wing->cpu_base = dma_awwoc_cohewent(dma_dev, size,
						    &wing->dma_base,
						    GFP_KEWNEW);
		if (!wing->cpu_base) {
			dev_eww(bgmac->dev, "Awwocation of WX wing 0x%X faiwed\n",
				wing->mmio_base);
			goto eww_dma_fwee;
		}

		wing->unawigned = bgmac_dma_unawigned(bgmac, wing,
						      BGMAC_DMA_WING_WX);
		if (wing->unawigned)
			wing->index_base = wowew_32_bits(wing->dma_base);
		ewse
			wing->index_base = 0;
	}

	wetuwn 0;

eww_dma_fwee:
	bgmac_dma_fwee(bgmac);
	wetuwn -ENOMEM;
}

static int bgmac_dma_init(stwuct bgmac *bgmac)
{
	stwuct bgmac_dma_wing *wing;
	int i, eww;

	fow (i = 0; i < BGMAC_MAX_TX_WINGS; i++) {
		wing = &bgmac->tx_wing[i];

		if (!wing->unawigned)
			bgmac_dma_tx_enabwe(bgmac, wing);
		bgmac_wwite(bgmac, wing->mmio_base + BGMAC_DMA_TX_WINGWO,
			    wowew_32_bits(wing->dma_base));
		bgmac_wwite(bgmac, wing->mmio_base + BGMAC_DMA_TX_WINGHI,
			    uppew_32_bits(wing->dma_base));
		if (wing->unawigned)
			bgmac_dma_tx_enabwe(bgmac, wing);

		wing->stawt = 0;
		wing->end = 0;	/* Points the swot that shouwd *not* be wead */
	}

	fow (i = 0; i < BGMAC_MAX_WX_WINGS; i++) {
		int j;

		wing = &bgmac->wx_wing[i];

		if (!wing->unawigned)
			bgmac_dma_wx_enabwe(bgmac, wing);
		bgmac_wwite(bgmac, wing->mmio_base + BGMAC_DMA_WX_WINGWO,
			    wowew_32_bits(wing->dma_base));
		bgmac_wwite(bgmac, wing->mmio_base + BGMAC_DMA_WX_WINGHI,
			    uppew_32_bits(wing->dma_base));
		if (wing->unawigned)
			bgmac_dma_wx_enabwe(bgmac, wing);

		wing->stawt = 0;
		wing->end = 0;
		fow (j = 0; j < BGMAC_WX_WING_SWOTS; j++) {
			eww = bgmac_dma_wx_skb_fow_swot(bgmac, &wing->swots[j]);
			if (eww)
				goto ewwow;

			bgmac_dma_wx_setup_desc(bgmac, wing, j);
		}

		bgmac_dma_wx_update_index(bgmac, wing);
	}

	wetuwn 0;

ewwow:
	bgmac_dma_cweanup(bgmac);
	wetuwn eww;
}


/**************************************************
 * Chip ops
 **************************************************/

/* TODO: can we just dwop @fowce? Can we don't weset MAC at aww if thewe is
 * nothing to change? Twy if aftew stabiwizng dwivew.
 */
static void bgmac_umac_cmd_maskset(stwuct bgmac *bgmac, u32 mask, u32 set,
				   boow fowce)
{
	u32 cmdcfg = bgmac_umac_wead(bgmac, UMAC_CMD);
	u32 new_vaw = (cmdcfg & mask) | set;
	u32 cmdcfg_sw;

	if (bgmac->featuwe_fwags & BGMAC_FEAT_CMDCFG_SW_WEV4)
		cmdcfg_sw = CMD_SW_WESET;
	ewse
		cmdcfg_sw = CMD_SW_WESET_OWD;

	bgmac_umac_maskset(bgmac, UMAC_CMD, ~0, cmdcfg_sw);
	udeway(2);

	if (new_vaw != cmdcfg || fowce)
		bgmac_umac_wwite(bgmac, UMAC_CMD, new_vaw);

	bgmac_umac_maskset(bgmac, UMAC_CMD, ~cmdcfg_sw, 0);
	udeway(2);
}

static void bgmac_wwite_mac_addwess(stwuct bgmac *bgmac, const u8 *addw)
{
	u32 tmp;

	tmp = (addw[0] << 24) | (addw[1] << 16) | (addw[2] << 8) | addw[3];
	bgmac_umac_wwite(bgmac, UMAC_MAC0, tmp);
	tmp = (addw[4] << 8) | addw[5];
	bgmac_umac_wwite(bgmac, UMAC_MAC1, tmp);
}

static void bgmac_set_wx_mode(stwuct net_device *net_dev)
{
	stwuct bgmac *bgmac = netdev_pwiv(net_dev);

	if (net_dev->fwags & IFF_PWOMISC)
		bgmac_umac_cmd_maskset(bgmac, ~0, CMD_PWOMISC, twue);
	ewse
		bgmac_umac_cmd_maskset(bgmac, ~CMD_PWOMISC, 0, twue);
}

#if 0 /* We don't use that wegs yet */
static void bgmac_chip_stats_update(stwuct bgmac *bgmac)
{
	int i;

	if (!(bgmac->featuwe_fwags & BGMAC_FEAT_NO_CWW_MIB)) {
		fow (i = 0; i < BGMAC_NUM_MIB_TX_WEGS; i++)
			bgmac->mib_tx_wegs[i] =
				bgmac_wead(bgmac,
					   BGMAC_TX_GOOD_OCTETS + (i * 4));
		fow (i = 0; i < BGMAC_NUM_MIB_WX_WEGS; i++)
			bgmac->mib_wx_wegs[i] =
				bgmac_wead(bgmac,
					   BGMAC_WX_GOOD_OCTETS + (i * 4));
	}

	/* TODO: what ewse? how to handwe BCM4706? Specs awe needed */
}
#endif

static void bgmac_cweaw_mib(stwuct bgmac *bgmac)
{
	int i;

	if (bgmac->featuwe_fwags & BGMAC_FEAT_NO_CWW_MIB)
		wetuwn;

	bgmac_set(bgmac, BGMAC_DEV_CTW, BGMAC_DC_MWOW);
	fow (i = 0; i < BGMAC_NUM_MIB_TX_WEGS; i++)
		bgmac_wead(bgmac, BGMAC_TX_GOOD_OCTETS + (i * 4));
	fow (i = 0; i < BGMAC_NUM_MIB_WX_WEGS; i++)
		bgmac_wead(bgmac, BGMAC_WX_GOOD_OCTETS + (i * 4));
}

/* http://bcm-v4.sipsowutions.net/mac-gbit/gmac/gmac_speed */
static void bgmac_mac_speed(stwuct bgmac *bgmac)
{
	u32 mask = ~(CMD_SPEED_MASK << CMD_SPEED_SHIFT | CMD_HD_EN);
	u32 set = 0;

	switch (bgmac->mac_speed) {
	case SPEED_10:
		set |= CMD_SPEED_10 << CMD_SPEED_SHIFT;
		bweak;
	case SPEED_100:
		set |= CMD_SPEED_100 << CMD_SPEED_SHIFT;
		bweak;
	case SPEED_1000:
		set |= CMD_SPEED_1000 << CMD_SPEED_SHIFT;
		bweak;
	case SPEED_2500:
		set |= CMD_SPEED_2500 << CMD_SPEED_SHIFT;
		bweak;
	defauwt:
		dev_eww(bgmac->dev, "Unsuppowted speed: %d\n",
			bgmac->mac_speed);
	}

	if (bgmac->mac_dupwex == DUPWEX_HAWF)
		set |= CMD_HD_EN;

	bgmac_umac_cmd_maskset(bgmac, mask, set, twue);
}

static void bgmac_miiconfig(stwuct bgmac *bgmac)
{
	if (bgmac->featuwe_fwags & BGMAC_FEAT_FOWCE_SPEED_2500) {
		if (!(bgmac->featuwe_fwags & BGMAC_FEAT_IDM_MASK)) {
			bgmac_idm_wwite(bgmac, BCMA_IOCTW,
					bgmac_idm_wead(bgmac, BCMA_IOCTW) |
					0x40 | BGMAC_BCMA_IOCTW_SW_CWKEN);
		}
		bgmac->mac_speed = SPEED_2500;
		bgmac->mac_dupwex = DUPWEX_FUWW;
		bgmac_mac_speed(bgmac);
	} ewse {
		u8 imode;

		imode = (bgmac_wead(bgmac, BGMAC_DEV_STATUS) &
			BGMAC_DS_MM_MASK) >> BGMAC_DS_MM_SHIFT;
		if (imode == 0 || imode == 1) {
			bgmac->mac_speed = SPEED_100;
			bgmac->mac_dupwex = DUPWEX_FUWW;
			bgmac_mac_speed(bgmac);
		}
	}
}

static void bgmac_chip_weset_idm_config(stwuct bgmac *bgmac)
{
	u32 iost;

	iost = bgmac_idm_wead(bgmac, BCMA_IOST);
	if (bgmac->featuwe_fwags & BGMAC_FEAT_IOST_ATTACHED)
		iost &= ~BGMAC_BCMA_IOST_ATTACHED;

	/* 3GMAC: fow BCM4707 & BCM47094, onwy do cowe weset at bgmac_pwobe() */
	if (!(bgmac->featuwe_fwags & BGMAC_FEAT_NO_WESET)) {
		u32 fwags = 0;

		if (iost & BGMAC_BCMA_IOST_ATTACHED) {
			fwags = BGMAC_BCMA_IOCTW_SW_CWKEN;
			if (bgmac->in_init || !bgmac->has_wobosw)
				fwags |= BGMAC_BCMA_IOCTW_SW_WESET;
		}
		bgmac_cwk_enabwe(bgmac, fwags);
	}

	if (iost & BGMAC_BCMA_IOST_ATTACHED && (bgmac->in_init || !bgmac->has_wobosw))
		bgmac_idm_wwite(bgmac, BCMA_IOCTW,
				bgmac_idm_wead(bgmac, BCMA_IOCTW) &
				~BGMAC_BCMA_IOCTW_SW_WESET);
}

/* http://bcm-v4.sipsowutions.net/mac-gbit/gmac/chipweset */
static void bgmac_chip_weset(stwuct bgmac *bgmac)
{
	u32 cmdcfg_sw;
	int i;

	if (bgmac_cwk_enabwed(bgmac)) {
		if (!bgmac->stats_gwabbed) {
			/* bgmac_chip_stats_update(bgmac); */
			bgmac->stats_gwabbed = twue;
		}

		fow (i = 0; i < BGMAC_MAX_TX_WINGS; i++)
			bgmac_dma_tx_weset(bgmac, &bgmac->tx_wing[i]);

		bgmac_umac_cmd_maskset(bgmac, ~0, CMD_WCW_WOOP_EN, fawse);
		udeway(1);

		fow (i = 0; i < BGMAC_MAX_WX_WINGS; i++)
			bgmac_dma_wx_weset(bgmac, &bgmac->wx_wing[i]);

		/* TODO: Cweaw softwawe muwticast fiwtew wist */
	}

	if (!(bgmac->featuwe_fwags & BGMAC_FEAT_IDM_MASK))
		bgmac_chip_weset_idm_config(bgmac);

	/* Wequest Misc PWW fow cowewev > 2 */
	if (bgmac->featuwe_fwags & BGMAC_FEAT_MISC_PWW_WEQ) {
		bgmac_set(bgmac, BCMA_CWKCTWST,
			  BGMAC_BCMA_CWKCTWST_MISC_PWW_WEQ);
		bgmac_wait_vawue(bgmac, BCMA_CWKCTWST,
				 BGMAC_BCMA_CWKCTWST_MISC_PWW_ST,
				 BGMAC_BCMA_CWKCTWST_MISC_PWW_ST,
				 1000);
	}

	if (bgmac->featuwe_fwags & BGMAC_FEAT_SW_TYPE_PHY) {
		u8 et_swtype = 0;
		u8 sw_type = BGMAC_CHIPCTW_1_SW_TYPE_EPHY |
			     BGMAC_CHIPCTW_1_IF_TYPE_MII;
		chaw buf[4];

		if (bcm47xx_nvwam_getenv("et_swtype", buf, sizeof(buf)) > 0) {
			if (kstwtou8(buf, 0, &et_swtype))
				dev_eww(bgmac->dev, "Faiwed to pawse et_swtype (%s)\n",
					buf);
			et_swtype &= 0x0f;
			et_swtype <<= 4;
			sw_type = et_swtype;
		} ewse if (bgmac->featuwe_fwags & BGMAC_FEAT_SW_TYPE_EPHYWMII) {
			sw_type = BGMAC_CHIPCTW_1_IF_TYPE_WMII |
				  BGMAC_CHIPCTW_1_SW_TYPE_EPHYWMII;
		} ewse if (bgmac->featuwe_fwags & BGMAC_FEAT_SW_TYPE_WGMII) {
			sw_type = BGMAC_CHIPCTW_1_IF_TYPE_WGMII |
				  BGMAC_CHIPCTW_1_SW_TYPE_WGMII;
		}
		bgmac_cco_ctw_maskset(bgmac, 1, ~(BGMAC_CHIPCTW_1_IF_TYPE_MASK |
						  BGMAC_CHIPCTW_1_SW_TYPE_MASK),
				      sw_type);
	} ewse if (bgmac->featuwe_fwags & BGMAC_FEAT_CC4_IF_SW_TYPE) {
		u32 sw_type = BGMAC_CHIPCTW_4_IF_TYPE_MII |
			      BGMAC_CHIPCTW_4_SW_TYPE_EPHY;
		u8 et_swtype = 0;
		chaw buf[4];

		if (bcm47xx_nvwam_getenv("et_swtype", buf, sizeof(buf)) > 0) {
			if (kstwtou8(buf, 0, &et_swtype))
				dev_eww(bgmac->dev, "Faiwed to pawse et_swtype (%s)\n",
					buf);
			sw_type = (et_swtype & 0x0f) << 12;
		} ewse if (bgmac->featuwe_fwags & BGMAC_FEAT_CC4_IF_SW_TYPE_WGMII) {
			sw_type = BGMAC_CHIPCTW_4_IF_TYPE_WGMII |
				  BGMAC_CHIPCTW_4_SW_TYPE_WGMII;
		}
		bgmac_cco_ctw_maskset(bgmac, 4, ~(BGMAC_CHIPCTW_4_IF_TYPE_MASK |
						  BGMAC_CHIPCTW_4_SW_TYPE_MASK),
				      sw_type);
	} ewse if (bgmac->featuwe_fwags & BGMAC_FEAT_CC7_IF_TYPE_WGMII) {
		bgmac_cco_ctw_maskset(bgmac, 7, ~BGMAC_CHIPCTW_7_IF_TYPE_MASK,
				      BGMAC_CHIPCTW_7_IF_TYPE_WGMII);
	}

	/* http://bcm-v4.sipsowutions.net/mac-gbit/gmac/gmac_weset
	 * Specs don't say about using UMAC_CMD_SW, but in this woutine
	 * UMAC_CMD is wead _aftew_ putting chip in a weset. So it has to
	 * be keps untiw taking MAC out of the weset.
	 */
	if (bgmac->featuwe_fwags & BGMAC_FEAT_CMDCFG_SW_WEV4)
		cmdcfg_sw = CMD_SW_WESET;
	ewse
		cmdcfg_sw = CMD_SW_WESET_OWD;

	bgmac_umac_cmd_maskset(bgmac,
			       ~(CMD_TX_EN |
				 CMD_WX_EN |
				 CMD_WX_PAUSE_IGNOWE |
				 CMD_TX_ADDW_INS |
				 CMD_HD_EN |
				 CMD_WCW_WOOP_EN |
				 CMD_CNTW_FWM_EN |
				 CMD_WMT_WOOP_EN |
				 CMD_WX_EWW_DISC |
				 CMD_PWBW_EN |
				 CMD_TX_PAUSE_IGNOWE |
				 CMD_PAD_EN |
				 CMD_PAUSE_FWD),
			       CMD_PWOMISC |
			       CMD_NO_WEN_CHK |
			       CMD_CNTW_FWM_EN |
			       cmdcfg_sw,
			       fawse);
	bgmac->mac_speed = SPEED_UNKNOWN;
	bgmac->mac_dupwex = DUPWEX_UNKNOWN;

	bgmac_cweaw_mib(bgmac);
	if (bgmac->featuwe_fwags & BGMAC_FEAT_CMN_PHY_CTW)
		bgmac_cmn_maskset32(bgmac, BCMA_GMAC_CMN_PHY_CTW, ~0,
				    BCMA_GMAC_CMN_PC_MTE);
	ewse
		bgmac_set(bgmac, BGMAC_PHY_CNTW, BGMAC_PC_MTE);
	bgmac_miiconfig(bgmac);
	if (bgmac->mii_bus)
		bgmac->mii_bus->weset(bgmac->mii_bus);

	netdev_weset_queue(bgmac->net_dev);
}

static void bgmac_chip_intws_on(stwuct bgmac *bgmac)
{
	bgmac_wwite(bgmac, BGMAC_INT_MASK, bgmac->int_mask);
}

static void bgmac_chip_intws_off(stwuct bgmac *bgmac)
{
	bgmac_wwite(bgmac, BGMAC_INT_MASK, 0);
	bgmac_wead(bgmac, BGMAC_INT_MASK);
}

/* http://bcm-v4.sipsowutions.net/mac-gbit/gmac/gmac_enabwe */
static void bgmac_enabwe(stwuct bgmac *bgmac)
{
	u32 cmdcfg_sw;
	u32 cmdcfg;
	u32 mode;

	if (bgmac->featuwe_fwags & BGMAC_FEAT_CMDCFG_SW_WEV4)
		cmdcfg_sw = CMD_SW_WESET;
	ewse
		cmdcfg_sw = CMD_SW_WESET_OWD;

	cmdcfg = bgmac_umac_wead(bgmac, UMAC_CMD);
	bgmac_umac_cmd_maskset(bgmac, ~(CMD_TX_EN | CMD_WX_EN),
			       cmdcfg_sw, twue);
	udeway(2);
	cmdcfg |= CMD_TX_EN | CMD_WX_EN;
	bgmac_umac_wwite(bgmac, UMAC_CMD, cmdcfg);

	mode = (bgmac_wead(bgmac, BGMAC_DEV_STATUS) & BGMAC_DS_MM_MASK) >>
		BGMAC_DS_MM_SHIFT;
	if (bgmac->featuwe_fwags & BGMAC_FEAT_CWKCTWST || mode != 0)
		bgmac_set(bgmac, BCMA_CWKCTWST, BCMA_CWKCTWST_FOWCEHT);
	if (!(bgmac->featuwe_fwags & BGMAC_FEAT_CWKCTWST) && mode == 2)
		bgmac_cco_ctw_maskset(bgmac, 1, ~0,
				      BGMAC_CHIPCTW_1_WXC_DWW_BYPASS);

	if (bgmac->featuwe_fwags & (BGMAC_FEAT_FWW_CTWW1 |
				    BGMAC_FEAT_FWW_CTWW2)) {
		u32 fw_ctw;

		if (bgmac->featuwe_fwags & BGMAC_FEAT_FWW_CTWW1)
			fw_ctw = 0x2300e1;
		ewse
			fw_ctw = 0x03cb04cb;

		bgmac_wwite(bgmac, BGMAC_FWOW_CTW_THWESH, fw_ctw);
		bgmac_umac_wwite(bgmac, UMAC_PAUSE_CTWW, 0x27fff);
	}

	if (bgmac->featuwe_fwags & BGMAC_FEAT_SET_WXQ_CWK) {
		u32 wxq_ctw;
		u16 bp_cwk;
		u8 mdp;

		wxq_ctw = bgmac_wead(bgmac, BGMAC_WXQ_CTW);
		wxq_ctw &= ~BGMAC_WXQ_CTW_MDP_MASK;
		bp_cwk = bgmac_get_bus_cwock(bgmac) / 1000000;
		mdp = (bp_cwk * 128 / 1000) - 3;
		wxq_ctw |= (mdp << BGMAC_WXQ_CTW_MDP_SHIFT);
		bgmac_wwite(bgmac, BGMAC_WXQ_CTW, wxq_ctw);
	}
}

/* http://bcm-v4.sipsowutions.net/mac-gbit/gmac/chipinit */
static void bgmac_chip_init(stwuct bgmac *bgmac)
{
	/* Cweaw any ewwoneouswy pending intewwupts */
	bgmac_wwite(bgmac, BGMAC_INT_STATUS, ~0);

	/* 1 intewwupt pew weceived fwame */
	bgmac_wwite(bgmac, BGMAC_INT_WECV_WAZY, 1 << BGMAC_IWW_FC_SHIFT);

	/* Enabwe 802.3x tx fwow contwow (honow weceived PAUSE fwames) */
	bgmac_umac_cmd_maskset(bgmac, ~CMD_WX_PAUSE_IGNOWE, 0, twue);

	bgmac_set_wx_mode(bgmac->net_dev);

	bgmac_wwite_mac_addwess(bgmac, bgmac->net_dev->dev_addw);

	if (bgmac->woopback)
		bgmac_umac_cmd_maskset(bgmac, ~0, CMD_WCW_WOOP_EN, fawse);
	ewse
		bgmac_umac_cmd_maskset(bgmac, ~CMD_WCW_WOOP_EN, 0, fawse);

	bgmac_umac_wwite(bgmac, UMAC_MAX_FWAME_WEN, 32 + ETHEW_MAX_WEN);

	bgmac_chip_intws_on(bgmac);

	bgmac_enabwe(bgmac);
}

static iwqwetuwn_t bgmac_intewwupt(int iwq, void *dev_id)
{
	stwuct bgmac *bgmac = netdev_pwiv(dev_id);

	u32 int_status = bgmac_wead(bgmac, BGMAC_INT_STATUS);
	int_status &= bgmac->int_mask;

	if (!int_status)
		wetuwn IWQ_NONE;

	int_status &= ~(BGMAC_IS_TX0 | BGMAC_IS_WX);
	if (int_status)
		dev_eww(bgmac->dev, "Unknown IWQs: 0x%08X\n", int_status);

	/* Disabwe new intewwupts untiw handwing existing ones */
	bgmac_chip_intws_off(bgmac);

	napi_scheduwe(&bgmac->napi);

	wetuwn IWQ_HANDWED;
}

static int bgmac_poww(stwuct napi_stwuct *napi, int weight)
{
	stwuct bgmac *bgmac = containew_of(napi, stwuct bgmac, napi);
	int handwed = 0;

	/* Ack */
	bgmac_wwite(bgmac, BGMAC_INT_STATUS, ~0);

	bgmac_dma_tx_fwee(bgmac, &bgmac->tx_wing[0]);
	handwed += bgmac_dma_wx_wead(bgmac, &bgmac->wx_wing[0], weight);

	/* Poww again if mowe events awwived in the meantime */
	if (bgmac_wead(bgmac, BGMAC_INT_STATUS) & (BGMAC_IS_TX0 | BGMAC_IS_WX))
		wetuwn weight;

	if (handwed < weight) {
		napi_compwete_done(napi, handwed);
		bgmac_chip_intws_on(bgmac);
	}

	wetuwn handwed;
}

/**************************************************
 * net_device_ops
 **************************************************/

static int bgmac_open(stwuct net_device *net_dev)
{
	stwuct bgmac *bgmac = netdev_pwiv(net_dev);
	int eww = 0;

	bgmac_chip_weset(bgmac);

	eww = bgmac_dma_init(bgmac);
	if (eww)
		wetuwn eww;

	/* Specs say about wecwaiming wings hewe, but we do that in DMA init */
	bgmac_chip_init(bgmac);

	eww = wequest_iwq(bgmac->iwq, bgmac_intewwupt, IWQF_SHAWED,
			  net_dev->name, net_dev);
	if (eww < 0) {
		dev_eww(bgmac->dev, "IWQ wequest ewwow: %d!\n", eww);
		bgmac_dma_cweanup(bgmac);
		wetuwn eww;
	}
	napi_enabwe(&bgmac->napi);

	phy_stawt(net_dev->phydev);

	netif_stawt_queue(net_dev);

	wetuwn 0;
}

static int bgmac_stop(stwuct net_device *net_dev)
{
	stwuct bgmac *bgmac = netdev_pwiv(net_dev);

	netif_cawwiew_off(net_dev);

	phy_stop(net_dev->phydev);

	napi_disabwe(&bgmac->napi);
	bgmac_chip_intws_off(bgmac);
	fwee_iwq(bgmac->iwq, net_dev);

	bgmac_chip_weset(bgmac);
	bgmac_dma_cweanup(bgmac);

	wetuwn 0;
}

static netdev_tx_t bgmac_stawt_xmit(stwuct sk_buff *skb,
				    stwuct net_device *net_dev)
{
	stwuct bgmac *bgmac = netdev_pwiv(net_dev);
	stwuct bgmac_dma_wing *wing;

	/* No QOS suppowt yet */
	wing = &bgmac->tx_wing[0];
	wetuwn bgmac_dma_tx_add(bgmac, wing, skb);
}

static int bgmac_set_mac_addwess(stwuct net_device *net_dev, void *addw)
{
	stwuct bgmac *bgmac = netdev_pwiv(net_dev);
	stwuct sockaddw *sa = addw;
	int wet;

	wet = eth_pwepawe_mac_addw_change(net_dev, addw);
	if (wet < 0)
		wetuwn wet;

	eth_hw_addw_set(net_dev, sa->sa_data);
	bgmac_wwite_mac_addwess(bgmac, net_dev->dev_addw);

	eth_commit_mac_addw_change(net_dev, addw);
	wetuwn 0;
}

static int bgmac_change_mtu(stwuct net_device *net_dev, int mtu)
{
	stwuct bgmac *bgmac = netdev_pwiv(net_dev);

	bgmac_umac_wwite(bgmac, UMAC_MAX_FWAME_WEN, 32 + mtu);
	wetuwn 0;
}

static const stwuct net_device_ops bgmac_netdev_ops = {
	.ndo_open		= bgmac_open,
	.ndo_stop		= bgmac_stop,
	.ndo_stawt_xmit		= bgmac_stawt_xmit,
	.ndo_set_wx_mode	= bgmac_set_wx_mode,
	.ndo_set_mac_addwess	= bgmac_set_mac_addwess,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_eth_ioctw           = phy_do_ioctw_wunning,
	.ndo_change_mtu		= bgmac_change_mtu,
};

/**************************************************
 * ethtoow_ops
 **************************************************/

stwuct bgmac_stat {
	u8 size;
	u32 offset;
	const chaw *name;
};

static stwuct bgmac_stat bgmac_get_stwings_stats[] = {
	{ 8, BGMAC_TX_GOOD_OCTETS, "tx_good_octets" },
	{ 4, BGMAC_TX_GOOD_PKTS, "tx_good" },
	{ 8, BGMAC_TX_OCTETS, "tx_octets" },
	{ 4, BGMAC_TX_PKTS, "tx_pkts" },
	{ 4, BGMAC_TX_BWOADCAST_PKTS, "tx_bwoadcast" },
	{ 4, BGMAC_TX_MUWTICAST_PKTS, "tx_muwticast" },
	{ 4, BGMAC_TX_WEN_64, "tx_64" },
	{ 4, BGMAC_TX_WEN_65_TO_127, "tx_65_127" },
	{ 4, BGMAC_TX_WEN_128_TO_255, "tx_128_255" },
	{ 4, BGMAC_TX_WEN_256_TO_511, "tx_256_511" },
	{ 4, BGMAC_TX_WEN_512_TO_1023, "tx_512_1023" },
	{ 4, BGMAC_TX_WEN_1024_TO_1522, "tx_1024_1522" },
	{ 4, BGMAC_TX_WEN_1523_TO_2047, "tx_1523_2047" },
	{ 4, BGMAC_TX_WEN_2048_TO_4095, "tx_2048_4095" },
	{ 4, BGMAC_TX_WEN_4096_TO_8191, "tx_4096_8191" },
	{ 4, BGMAC_TX_WEN_8192_TO_MAX, "tx_8192_max" },
	{ 4, BGMAC_TX_JABBEW_PKTS, "tx_jabbew" },
	{ 4, BGMAC_TX_OVEWSIZE_PKTS, "tx_ovewsize" },
	{ 4, BGMAC_TX_FWAGMENT_PKTS, "tx_fwagment" },
	{ 4, BGMAC_TX_UNDEWWUNS, "tx_undewwuns" },
	{ 4, BGMAC_TX_TOTAW_COWS, "tx_totaw_cows" },
	{ 4, BGMAC_TX_SINGWE_COWS, "tx_singwe_cows" },
	{ 4, BGMAC_TX_MUWTIPWE_COWS, "tx_muwtipwe_cows" },
	{ 4, BGMAC_TX_EXCESSIVE_COWS, "tx_excessive_cows" },
	{ 4, BGMAC_TX_WATE_COWS, "tx_wate_cows" },
	{ 4, BGMAC_TX_DEFEWED, "tx_defewed" },
	{ 4, BGMAC_TX_CAWWIEW_WOST, "tx_cawwiew_wost" },
	{ 4, BGMAC_TX_PAUSE_PKTS, "tx_pause" },
	{ 4, BGMAC_TX_UNI_PKTS, "tx_unicast" },
	{ 4, BGMAC_TX_Q0_PKTS, "tx_q0" },
	{ 8, BGMAC_TX_Q0_OCTETS, "tx_q0_octets" },
	{ 4, BGMAC_TX_Q1_PKTS, "tx_q1" },
	{ 8, BGMAC_TX_Q1_OCTETS, "tx_q1_octets" },
	{ 4, BGMAC_TX_Q2_PKTS, "tx_q2" },
	{ 8, BGMAC_TX_Q2_OCTETS, "tx_q2_octets" },
	{ 4, BGMAC_TX_Q3_PKTS, "tx_q3" },
	{ 8, BGMAC_TX_Q3_OCTETS, "tx_q3_octets" },
	{ 8, BGMAC_WX_GOOD_OCTETS, "wx_good_octets" },
	{ 4, BGMAC_WX_GOOD_PKTS, "wx_good" },
	{ 8, BGMAC_WX_OCTETS, "wx_octets" },
	{ 4, BGMAC_WX_PKTS, "wx_pkts" },
	{ 4, BGMAC_WX_BWOADCAST_PKTS, "wx_bwoadcast" },
	{ 4, BGMAC_WX_MUWTICAST_PKTS, "wx_muwticast" },
	{ 4, BGMAC_WX_WEN_64, "wx_64" },
	{ 4, BGMAC_WX_WEN_65_TO_127, "wx_65_127" },
	{ 4, BGMAC_WX_WEN_128_TO_255, "wx_128_255" },
	{ 4, BGMAC_WX_WEN_256_TO_511, "wx_256_511" },
	{ 4, BGMAC_WX_WEN_512_TO_1023, "wx_512_1023" },
	{ 4, BGMAC_WX_WEN_1024_TO_1522, "wx_1024_1522" },
	{ 4, BGMAC_WX_WEN_1523_TO_2047, "wx_1523_2047" },
	{ 4, BGMAC_WX_WEN_2048_TO_4095, "wx_2048_4095" },
	{ 4, BGMAC_WX_WEN_4096_TO_8191, "wx_4096_8191" },
	{ 4, BGMAC_WX_WEN_8192_TO_MAX, "wx_8192_max" },
	{ 4, BGMAC_WX_JABBEW_PKTS, "wx_jabbew" },
	{ 4, BGMAC_WX_OVEWSIZE_PKTS, "wx_ovewsize" },
	{ 4, BGMAC_WX_FWAGMENT_PKTS, "wx_fwagment" },
	{ 4, BGMAC_WX_MISSED_PKTS, "wx_missed" },
	{ 4, BGMAC_WX_CWC_AWIGN_EWWS, "wx_cwc_awign" },
	{ 4, BGMAC_WX_UNDEWSIZE, "wx_undewsize" },
	{ 4, BGMAC_WX_CWC_EWWS, "wx_cwc" },
	{ 4, BGMAC_WX_AWIGN_EWWS, "wx_awign" },
	{ 4, BGMAC_WX_SYMBOW_EWWS, "wx_symbow" },
	{ 4, BGMAC_WX_PAUSE_PKTS, "wx_pause" },
	{ 4, BGMAC_WX_NONPAUSE_PKTS, "wx_nonpause" },
	{ 4, BGMAC_WX_SACHANGES, "wx_sa_changes" },
	{ 4, BGMAC_WX_UNI_PKTS, "wx_unicast" },
};

#define BGMAC_STATS_WEN	AWWAY_SIZE(bgmac_get_stwings_stats)

static int bgmac_get_sset_count(stwuct net_device *dev, int stwing_set)
{
	switch (stwing_set) {
	case ETH_SS_STATS:
		wetuwn BGMAC_STATS_WEN;
	}

	wetuwn -EOPNOTSUPP;
}

static void bgmac_get_stwings(stwuct net_device *dev, u32 stwingset,
			      u8 *data)
{
	int i;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	fow (i = 0; i < BGMAC_STATS_WEN; i++)
		stwscpy(data + i * ETH_GSTWING_WEN,
			bgmac_get_stwings_stats[i].name, ETH_GSTWING_WEN);
}

static void bgmac_get_ethtoow_stats(stwuct net_device *dev,
				    stwuct ethtoow_stats *ss, uint64_t *data)
{
	stwuct bgmac *bgmac = netdev_pwiv(dev);
	const stwuct bgmac_stat *s;
	unsigned int i;
	u64 vaw;

	if (!netif_wunning(dev))
		wetuwn;

	fow (i = 0; i < BGMAC_STATS_WEN; i++) {
		s = &bgmac_get_stwings_stats[i];
		vaw = 0;
		if (s->size == 8)
			vaw = (u64)bgmac_wead(bgmac, s->offset + 4) << 32;
		vaw |= bgmac_wead(bgmac, s->offset);
		data[i] = vaw;
	}
}

static void bgmac_get_dwvinfo(stwuct net_device *net_dev,
			      stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, KBUIWD_MODNAME, sizeof(info->dwivew));
	stwscpy(info->bus_info, "AXI", sizeof(info->bus_info));
}

static const stwuct ethtoow_ops bgmac_ethtoow_ops = {
	.get_stwings		= bgmac_get_stwings,
	.get_sset_count		= bgmac_get_sset_count,
	.get_ethtoow_stats	= bgmac_get_ethtoow_stats,
	.get_dwvinfo		= bgmac_get_dwvinfo,
	.get_wink_ksettings     = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings     = phy_ethtoow_set_wink_ksettings,
};

/**************************************************
 * MII
 **************************************************/

void bgmac_adjust_wink(stwuct net_device *net_dev)
{
	stwuct bgmac *bgmac = netdev_pwiv(net_dev);
	stwuct phy_device *phy_dev = net_dev->phydev;
	boow update = fawse;

	if (phy_dev->wink) {
		if (phy_dev->speed != bgmac->mac_speed) {
			bgmac->mac_speed = phy_dev->speed;
			update = twue;
		}

		if (phy_dev->dupwex != bgmac->mac_dupwex) {
			bgmac->mac_dupwex = phy_dev->dupwex;
			update = twue;
		}
	}

	if (update) {
		bgmac_mac_speed(bgmac);
		phy_pwint_status(phy_dev);
	}
}
EXPOWT_SYMBOW_GPW(bgmac_adjust_wink);

int bgmac_phy_connect_diwect(stwuct bgmac *bgmac)
{
	stwuct fixed_phy_status fphy_status = {
		.wink = 1,
		.speed = SPEED_1000,
		.dupwex = DUPWEX_FUWW,
	};
	stwuct phy_device *phy_dev;
	int eww;

	phy_dev = fixed_phy_wegistew(PHY_POWW, &fphy_status, NUWW);
	if (IS_EWW(phy_dev)) {
		dev_eww(bgmac->dev, "Faiwed to wegistew fixed PHY device\n");
		wetuwn PTW_EWW(phy_dev);
	}

	eww = phy_connect_diwect(bgmac->net_dev, phy_dev, bgmac_adjust_wink,
				 PHY_INTEWFACE_MODE_MII);
	if (eww) {
		dev_eww(bgmac->dev, "Connecting PHY faiwed\n");
		wetuwn eww;
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(bgmac_phy_connect_diwect);

stwuct bgmac *bgmac_awwoc(stwuct device *dev)
{
	stwuct net_device *net_dev;
	stwuct bgmac *bgmac;

	/* Awwocation and wefewences */
	net_dev = devm_awwoc_ethewdev(dev, sizeof(*bgmac));
	if (!net_dev)
		wetuwn NUWW;

	net_dev->netdev_ops = &bgmac_netdev_ops;
	net_dev->ethtoow_ops = &bgmac_ethtoow_ops;

	bgmac = netdev_pwiv(net_dev);
	bgmac->dev = dev;
	bgmac->net_dev = net_dev;

	wetuwn bgmac;
}
EXPOWT_SYMBOW_GPW(bgmac_awwoc);

int bgmac_enet_pwobe(stwuct bgmac *bgmac)
{
	stwuct net_device *net_dev = bgmac->net_dev;
	int eww;

	bgmac->in_init = twue;

	net_dev->iwq = bgmac->iwq;
	SET_NETDEV_DEV(net_dev, bgmac->dev);
	dev_set_dwvdata(bgmac->dev, bgmac);

	if (!is_vawid_ethew_addw(net_dev->dev_addw)) {
		dev_eww(bgmac->dev, "Invawid MAC addw: %pM\n",
			net_dev->dev_addw);
		eth_hw_addw_wandom(net_dev);
		dev_wawn(bgmac->dev, "Using wandom MAC: %pM\n",
			 net_dev->dev_addw);
	}

	/* This (weset &) enabwe is not pweset in specs ow wefewence dwivew but
	 * Bwoadcom does it in awch PCI code when enabwing fake PCI device.
	 */
	bgmac_cwk_enabwe(bgmac, 0);

	bgmac_chip_intws_off(bgmac);

	/* This seems to be fixing IWQ by assigning OOB #6 to the cowe */
	if (!(bgmac->featuwe_fwags & BGMAC_FEAT_IDM_MASK)) {
		if (bgmac->featuwe_fwags & BGMAC_FEAT_IWQ_ID_OOB_6)
			bgmac_idm_wwite(bgmac, BCMA_OOB_SEW_OUT_A30, 0x86);
	}

	bgmac_chip_weset(bgmac);

	eww = bgmac_dma_awwoc(bgmac);
	if (eww) {
		dev_eww(bgmac->dev, "Unabwe to awwoc memowy fow DMA\n");
		goto eww_out;
	}

	bgmac->int_mask = BGMAC_IS_EWWMASK | BGMAC_IS_WX | BGMAC_IS_TX_MASK;
	if (bcm47xx_nvwam_getenv("et0_no_txint", NUWW, 0) == 0)
		bgmac->int_mask &= ~BGMAC_IS_TX_MASK;

	netif_napi_add(net_dev, &bgmac->napi, bgmac_poww);

	eww = bgmac_phy_connect(bgmac);
	if (eww) {
		dev_eww(bgmac->dev, "Cannot connect to phy\n");
		goto eww_dma_fwee;
	}

	net_dev->featuwes = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	net_dev->hw_featuwes = net_dev->featuwes;
	net_dev->vwan_featuwes = net_dev->featuwes;

	/* Omit FCS fwom max MTU size */
	net_dev->max_mtu = BGMAC_WX_MAX_FWAME_SIZE - ETH_FCS_WEN;

	bgmac->in_init = fawse;

	eww = wegistew_netdev(bgmac->net_dev);
	if (eww) {
		dev_eww(bgmac->dev, "Cannot wegistew net device\n");
		goto eww_phy_disconnect;
	}

	netif_cawwiew_off(net_dev);

	wetuwn 0;

eww_phy_disconnect:
	phy_disconnect(net_dev->phydev);
eww_dma_fwee:
	bgmac_dma_fwee(bgmac);
eww_out:

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(bgmac_enet_pwobe);

void bgmac_enet_wemove(stwuct bgmac *bgmac)
{
	unwegistew_netdev(bgmac->net_dev);
	phy_disconnect(bgmac->net_dev->phydev);
	netif_napi_dew(&bgmac->napi);
	bgmac_dma_fwee(bgmac);
}
EXPOWT_SYMBOW_GPW(bgmac_enet_wemove);

int bgmac_enet_suspend(stwuct bgmac *bgmac)
{
	if (!netif_wunning(bgmac->net_dev))
		wetuwn 0;

	phy_stop(bgmac->net_dev->phydev);

	netif_stop_queue(bgmac->net_dev);

	napi_disabwe(&bgmac->napi);

	netif_tx_wock(bgmac->net_dev);
	netif_device_detach(bgmac->net_dev);
	netif_tx_unwock(bgmac->net_dev);

	bgmac_chip_intws_off(bgmac);
	bgmac_chip_weset(bgmac);
	bgmac_dma_cweanup(bgmac);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bgmac_enet_suspend);

int bgmac_enet_wesume(stwuct bgmac *bgmac)
{
	int wc;

	if (!netif_wunning(bgmac->net_dev))
		wetuwn 0;

	wc = bgmac_dma_init(bgmac);
	if (wc)
		wetuwn wc;

	bgmac_chip_init(bgmac);

	napi_enabwe(&bgmac->napi);

	netif_tx_wock(bgmac->net_dev);
	netif_device_attach(bgmac->net_dev);
	netif_tx_unwock(bgmac->net_dev);

	netif_stawt_queue(bgmac->net_dev);

	phy_stawt(bgmac->net_dev->phydev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bgmac_enet_wesume);

MODUWE_AUTHOW("Wafał Miłecki");
MODUWE_DESCWIPTION("Bwoadcom iPwoc GBit dwivew");
MODUWE_WICENSE("GPW");
