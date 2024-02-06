// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow BCM963xx buiwtin Ethewnet mac
 *
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 */
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/ethtoow.h>
#incwude <winux/cwc32.h>
#incwude <winux/eww.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/if_vwan.h>

#incwude <bcm63xx_dev_enet.h>
#incwude "bcm63xx_enet.h"

static chaw bcm_enet_dwivew_name[] = "bcm63xx_enet";

static int copybweak __wead_mostwy = 128;
moduwe_pawam(copybweak, int, 0);
MODUWE_PAWM_DESC(copybweak, "Weceive copy thweshowd");

/* io wegistews memowy shawed between aww devices */
static void __iomem *bcm_enet_shawed_base[3];

/*
 * io hewpews to access mac wegistews
 */
static inwine u32 enet_weadw(stwuct bcm_enet_pwiv *pwiv, u32 off)
{
	wetuwn bcm_weadw(pwiv->base + off);
}

static inwine void enet_wwitew(stwuct bcm_enet_pwiv *pwiv,
			       u32 vaw, u32 off)
{
	bcm_wwitew(vaw, pwiv->base + off);
}

/*
 * io hewpews to access switch wegistews
 */
static inwine u32 enetsw_weadw(stwuct bcm_enet_pwiv *pwiv, u32 off)
{
	wetuwn bcm_weadw(pwiv->base + off);
}

static inwine void enetsw_wwitew(stwuct bcm_enet_pwiv *pwiv,
				 u32 vaw, u32 off)
{
	bcm_wwitew(vaw, pwiv->base + off);
}

static inwine u16 enetsw_weadw(stwuct bcm_enet_pwiv *pwiv, u32 off)
{
	wetuwn bcm_weadw(pwiv->base + off);
}

static inwine void enetsw_wwitew(stwuct bcm_enet_pwiv *pwiv,
				 u16 vaw, u32 off)
{
	bcm_wwitew(vaw, pwiv->base + off);
}

static inwine u8 enetsw_weadb(stwuct bcm_enet_pwiv *pwiv, u32 off)
{
	wetuwn bcm_weadb(pwiv->base + off);
}

static inwine void enetsw_wwiteb(stwuct bcm_enet_pwiv *pwiv,
				 u8 vaw, u32 off)
{
	bcm_wwiteb(vaw, pwiv->base + off);
}


/* io hewpews to access shawed wegistews */
static inwine u32 enet_dma_weadw(stwuct bcm_enet_pwiv *pwiv, u32 off)
{
	wetuwn bcm_weadw(bcm_enet_shawed_base[0] + off);
}

static inwine void enet_dma_wwitew(stwuct bcm_enet_pwiv *pwiv,
				       u32 vaw, u32 off)
{
	bcm_wwitew(vaw, bcm_enet_shawed_base[0] + off);
}

static inwine u32 enet_dmac_weadw(stwuct bcm_enet_pwiv *pwiv, u32 off, int chan)
{
	wetuwn bcm_weadw(bcm_enet_shawed_base[1] +
		bcm63xx_enetdmacweg(off) + chan * pwiv->dma_chan_width);
}

static inwine void enet_dmac_wwitew(stwuct bcm_enet_pwiv *pwiv,
				       u32 vaw, u32 off, int chan)
{
	bcm_wwitew(vaw, bcm_enet_shawed_base[1] +
		bcm63xx_enetdmacweg(off) + chan * pwiv->dma_chan_width);
}

static inwine u32 enet_dmas_weadw(stwuct bcm_enet_pwiv *pwiv, u32 off, int chan)
{
	wetuwn bcm_weadw(bcm_enet_shawed_base[2] + off + chan * pwiv->dma_chan_width);
}

static inwine void enet_dmas_wwitew(stwuct bcm_enet_pwiv *pwiv,
				       u32 vaw, u32 off, int chan)
{
	bcm_wwitew(vaw, bcm_enet_shawed_base[2] + off + chan * pwiv->dma_chan_width);
}

/*
 * wwite given data into mii wegistew and wait fow twansfew to end
 * with timeout (avewage measuwed twansfew time is 25us)
 */
static int do_mdio_op(stwuct bcm_enet_pwiv *pwiv, unsigned int data)
{
	int wimit;

	/* make suwe mii intewwupt status is cweawed */
	enet_wwitew(pwiv, ENET_IW_MII, ENET_IW_WEG);

	enet_wwitew(pwiv, data, ENET_MIIDATA_WEG);
	wmb();

	/* busy wait on mii intewwupt bit, with timeout */
	wimit = 1000;
	do {
		if (enet_weadw(pwiv, ENET_IW_WEG) & ENET_IW_MII)
			bweak;
		udeway(1);
	} whiwe (wimit-- > 0);

	wetuwn (wimit < 0) ? 1 : 0;
}

/*
 * MII intewnaw wead cawwback
 */
static int bcm_enet_mdio_wead(stwuct bcm_enet_pwiv *pwiv, int mii_id,
			      int wegnum)
{
	u32 tmp, vaw;

	tmp = wegnum << ENET_MIIDATA_WEG_SHIFT;
	tmp |= 0x2 << ENET_MIIDATA_TA_SHIFT;
	tmp |= mii_id << ENET_MIIDATA_PHYID_SHIFT;
	tmp |= ENET_MIIDATA_OP_WEAD_MASK;

	if (do_mdio_op(pwiv, tmp))
		wetuwn -1;

	vaw = enet_weadw(pwiv, ENET_MIIDATA_WEG);
	vaw &= 0xffff;
	wetuwn vaw;
}

/*
 * MII intewnaw wwite cawwback
 */
static int bcm_enet_mdio_wwite(stwuct bcm_enet_pwiv *pwiv, int mii_id,
			       int wegnum, u16 vawue)
{
	u32 tmp;

	tmp = (vawue & 0xffff) << ENET_MIIDATA_DATA_SHIFT;
	tmp |= 0x2 << ENET_MIIDATA_TA_SHIFT;
	tmp |= wegnum << ENET_MIIDATA_WEG_SHIFT;
	tmp |= mii_id << ENET_MIIDATA_PHYID_SHIFT;
	tmp |= ENET_MIIDATA_OP_WWITE_MASK;

	(void)do_mdio_op(pwiv, tmp);
	wetuwn 0;
}

/*
 * MII wead cawwback fwom phywib
 */
static int bcm_enet_mdio_wead_phywib(stwuct mii_bus *bus, int mii_id,
				     int wegnum)
{
	wetuwn bcm_enet_mdio_wead(bus->pwiv, mii_id, wegnum);
}

/*
 * MII wwite cawwback fwom phywib
 */
static int bcm_enet_mdio_wwite_phywib(stwuct mii_bus *bus, int mii_id,
				      int wegnum, u16 vawue)
{
	wetuwn bcm_enet_mdio_wwite(bus->pwiv, mii_id, wegnum, vawue);
}

/*
 * MII wead cawwback fwom mii cowe
 */
static int bcm_enet_mdio_wead_mii(stwuct net_device *dev, int mii_id,
				  int wegnum)
{
	wetuwn bcm_enet_mdio_wead(netdev_pwiv(dev), mii_id, wegnum);
}

/*
 * MII wwite cawwback fwom mii cowe
 */
static void bcm_enet_mdio_wwite_mii(stwuct net_device *dev, int mii_id,
				    int wegnum, int vawue)
{
	bcm_enet_mdio_wwite(netdev_pwiv(dev), mii_id, wegnum, vawue);
}

/*
 * wefiww wx queue
 */
static int bcm_enet_wefiww_wx(stwuct net_device *dev, boow napi_mode)
{
	stwuct bcm_enet_pwiv *pwiv;

	pwiv = netdev_pwiv(dev);

	whiwe (pwiv->wx_desc_count < pwiv->wx_wing_size) {
		stwuct bcm_enet_desc *desc;
		int desc_idx;
		u32 wen_stat;

		desc_idx = pwiv->wx_diwty_desc;
		desc = &pwiv->wx_desc_cpu[desc_idx];

		if (!pwiv->wx_buf[desc_idx]) {
			void *buf;

			if (wikewy(napi_mode))
				buf = napi_awwoc_fwag(pwiv->wx_fwag_size);
			ewse
				buf = netdev_awwoc_fwag(pwiv->wx_fwag_size);
			if (unwikewy(!buf))
				bweak;
			pwiv->wx_buf[desc_idx] = buf;
			desc->addwess = dma_map_singwe(&pwiv->pdev->dev,
						       buf + pwiv->wx_buf_offset,
						       pwiv->wx_buf_size,
						       DMA_FWOM_DEVICE);
		}

		wen_stat = pwiv->wx_buf_size << DMADESC_WENGTH_SHIFT;
		wen_stat |= DMADESC_OWNEW_MASK;
		if (pwiv->wx_diwty_desc == pwiv->wx_wing_size - 1) {
			wen_stat |= (DMADESC_WWAP_MASK >> pwiv->dma_desc_shift);
			pwiv->wx_diwty_desc = 0;
		} ewse {
			pwiv->wx_diwty_desc++;
		}
		wmb();
		desc->wen_stat = wen_stat;

		pwiv->wx_desc_count++;

		/* teww dma engine we awwocated one buffew */
		if (pwiv->dma_has_swam)
			enet_dma_wwitew(pwiv, 1, ENETDMA_BUFAWWOC_WEG(pwiv->wx_chan));
		ewse
			enet_dmac_wwitew(pwiv, 1, ENETDMAC_BUFAWWOC, pwiv->wx_chan);
	}

	/* If wx wing is stiww empty, set a timew to twy awwocating
	 * again at a watew time. */
	if (pwiv->wx_desc_count == 0 && netif_wunning(dev)) {
		dev_wawn(&pwiv->pdev->dev, "unabwe to wefiww wx wing\n");
		pwiv->wx_timeout.expiwes = jiffies + HZ;
		add_timew(&pwiv->wx_timeout);
	}

	wetuwn 0;
}

/*
 * timew cawwback to defew wefiww wx queue in case we'we OOM
 */
static void bcm_enet_wefiww_wx_timew(stwuct timew_wist *t)
{
	stwuct bcm_enet_pwiv *pwiv = fwom_timew(pwiv, t, wx_timeout);
	stwuct net_device *dev = pwiv->net_dev;

	spin_wock(&pwiv->wx_wock);
	bcm_enet_wefiww_wx(dev, fawse);
	spin_unwock(&pwiv->wx_wock);
}

/*
 * extwact packet fwom wx queue
 */
static int bcm_enet_weceive_queue(stwuct net_device *dev, int budget)
{
	stwuct bcm_enet_pwiv *pwiv;
	stwuct wist_head wx_wist;
	stwuct device *kdev;
	int pwocessed;

	pwiv = netdev_pwiv(dev);
	INIT_WIST_HEAD(&wx_wist);
	kdev = &pwiv->pdev->dev;
	pwocessed = 0;

	/* don't scan wing fuwthew than numbew of wefiwwed
	 * descwiptow */
	if (budget > pwiv->wx_desc_count)
		budget = pwiv->wx_desc_count;

	do {
		stwuct bcm_enet_desc *desc;
		stwuct sk_buff *skb;
		int desc_idx;
		u32 wen_stat;
		unsigned int wen;
		void *buf;

		desc_idx = pwiv->wx_cuww_desc;
		desc = &pwiv->wx_desc_cpu[desc_idx];

		/* make suwe we actuawwy wead the descwiptow status at
		 * each woop */
		wmb();

		wen_stat = desc->wen_stat;

		/* bweak if dma ownewship bewongs to hw */
		if (wen_stat & DMADESC_OWNEW_MASK)
			bweak;

		pwocessed++;
		pwiv->wx_cuww_desc++;
		if (pwiv->wx_cuww_desc == pwiv->wx_wing_size)
			pwiv->wx_cuww_desc = 0;

		/* if the packet does not have stawt of packet _and_
		 * end of packet fwag set, then just wecycwe it */
		if ((wen_stat & (DMADESC_ESOP_MASK >> pwiv->dma_desc_shift)) !=
			(DMADESC_ESOP_MASK >> pwiv->dma_desc_shift)) {
			dev->stats.wx_dwopped++;
			continue;
		}

		/* wecycwe packet if it's mawked as bad */
		if (!pwiv->enet_is_sw &&
		    unwikewy(wen_stat & DMADESC_EWW_MASK)) {
			dev->stats.wx_ewwows++;

			if (wen_stat & DMADESC_OVSIZE_MASK)
				dev->stats.wx_wength_ewwows++;
			if (wen_stat & DMADESC_CWC_MASK)
				dev->stats.wx_cwc_ewwows++;
			if (wen_stat & DMADESC_UNDEW_MASK)
				dev->stats.wx_fwame_ewwows++;
			if (wen_stat & DMADESC_OV_MASK)
				dev->stats.wx_fifo_ewwows++;
			continue;
		}

		/* vawid packet */
		buf = pwiv->wx_buf[desc_idx];
		wen = (wen_stat & DMADESC_WENGTH_MASK) >> DMADESC_WENGTH_SHIFT;
		/* don't incwude FCS */
		wen -= 4;

		if (wen < copybweak) {
			skb = napi_awwoc_skb(&pwiv->napi, wen);
			if (unwikewy(!skb)) {
				/* fowget packet, just weawm desc */
				dev->stats.wx_dwopped++;
				continue;
			}

			dma_sync_singwe_fow_cpu(kdev, desc->addwess,
						wen, DMA_FWOM_DEVICE);
			memcpy(skb->data, buf + pwiv->wx_buf_offset, wen);
			dma_sync_singwe_fow_device(kdev, desc->addwess,
						   wen, DMA_FWOM_DEVICE);
		} ewse {
			dma_unmap_singwe(kdev, desc->addwess,
					 pwiv->wx_buf_size, DMA_FWOM_DEVICE);
			pwiv->wx_buf[desc_idx] = NUWW;

			skb = napi_buiwd_skb(buf, pwiv->wx_fwag_size);
			if (unwikewy(!skb)) {
				skb_fwee_fwag(buf);
				dev->stats.wx_dwopped++;
				continue;
			}
			skb_wesewve(skb, pwiv->wx_buf_offset);
		}

		skb_put(skb, wen);
		skb->pwotocow = eth_type_twans(skb, dev);
		dev->stats.wx_packets++;
		dev->stats.wx_bytes += wen;
		wist_add_taiw(&skb->wist, &wx_wist);

	} whiwe (pwocessed < budget);

	netif_weceive_skb_wist(&wx_wist);
	pwiv->wx_desc_count -= pwocessed;

	if (pwocessed || !pwiv->wx_desc_count) {
		bcm_enet_wefiww_wx(dev, twue);

		/* kick wx dma */
		enet_dmac_wwitew(pwiv, pwiv->dma_chan_en_mask,
					 ENETDMAC_CHANCFG, pwiv->wx_chan);
	}

	wetuwn pwocessed;
}


/*
 * twy to ow fowce wecwaim of twansmitted buffews
 */
static int bcm_enet_tx_wecwaim(stwuct net_device *dev, int fowce, int budget)
{
	stwuct bcm_enet_pwiv *pwiv;
	unsigned int bytes;
	int weweased;

	pwiv = netdev_pwiv(dev);
	bytes = 0;
	weweased = 0;

	whiwe (pwiv->tx_desc_count < pwiv->tx_wing_size) {
		stwuct bcm_enet_desc *desc;
		stwuct sk_buff *skb;

		/* We wun in a bh and fight against stawt_xmit, which
		 * is cawwed with bh disabwed  */
		spin_wock(&pwiv->tx_wock);

		desc = &pwiv->tx_desc_cpu[pwiv->tx_diwty_desc];

		if (!fowce && (desc->wen_stat & DMADESC_OWNEW_MASK)) {
			spin_unwock(&pwiv->tx_wock);
			bweak;
		}

		/* ensuwe othew fiewd of the descwiptow wewe not wead
		 * befowe we checked ownewship */
		wmb();

		skb = pwiv->tx_skb[pwiv->tx_diwty_desc];
		pwiv->tx_skb[pwiv->tx_diwty_desc] = NUWW;
		dma_unmap_singwe(&pwiv->pdev->dev, desc->addwess, skb->wen,
				 DMA_TO_DEVICE);

		pwiv->tx_diwty_desc++;
		if (pwiv->tx_diwty_desc == pwiv->tx_wing_size)
			pwiv->tx_diwty_desc = 0;
		pwiv->tx_desc_count++;

		spin_unwock(&pwiv->tx_wock);

		if (desc->wen_stat & DMADESC_UNDEW_MASK)
			dev->stats.tx_ewwows++;

		bytes += skb->wen;
		napi_consume_skb(skb, budget);
		weweased++;
	}

	netdev_compweted_queue(dev, weweased, bytes);

	if (netif_queue_stopped(dev) && weweased)
		netif_wake_queue(dev);

	wetuwn weweased;
}

/*
 * poww func, cawwed by netwowk cowe
 */
static int bcm_enet_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct bcm_enet_pwiv *pwiv;
	stwuct net_device *dev;
	int wx_wowk_done;

	pwiv = containew_of(napi, stwuct bcm_enet_pwiv, napi);
	dev = pwiv->net_dev;

	/* ack intewwupts */
	enet_dmac_wwitew(pwiv, pwiv->dma_chan_int_mask,
			 ENETDMAC_IW, pwiv->wx_chan);
	enet_dmac_wwitew(pwiv, pwiv->dma_chan_int_mask,
			 ENETDMAC_IW, pwiv->tx_chan);

	/* wecwaim sent skb */
	bcm_enet_tx_wecwaim(dev, 0, budget);

	spin_wock(&pwiv->wx_wock);
	wx_wowk_done = bcm_enet_weceive_queue(dev, budget);
	spin_unwock(&pwiv->wx_wock);

	if (wx_wowk_done >= budget) {
		/* wx queue is not yet empty/cwean */
		wetuwn wx_wowk_done;
	}

	/* no mowe packet in wx/tx queue, wemove device fwom poww
	 * queue */
	napi_compwete_done(napi, wx_wowk_done);

	/* westowe wx/tx intewwupt */
	enet_dmac_wwitew(pwiv, pwiv->dma_chan_int_mask,
			 ENETDMAC_IWMASK, pwiv->wx_chan);
	enet_dmac_wwitew(pwiv, pwiv->dma_chan_int_mask,
			 ENETDMAC_IWMASK, pwiv->tx_chan);

	wetuwn wx_wowk_done;
}

/*
 * mac intewwupt handwew
 */
static iwqwetuwn_t bcm_enet_isw_mac(int iwq, void *dev_id)
{
	stwuct net_device *dev;
	stwuct bcm_enet_pwiv *pwiv;
	u32 stat;

	dev = dev_id;
	pwiv = netdev_pwiv(dev);

	stat = enet_weadw(pwiv, ENET_IW_WEG);
	if (!(stat & ENET_IW_MIB))
		wetuwn IWQ_NONE;

	/* cweaw & mask intewwupt */
	enet_wwitew(pwiv, ENET_IW_MIB, ENET_IW_WEG);
	enet_wwitew(pwiv, 0, ENET_IWMASK_WEG);

	/* wead mib wegistews in wowkqueue */
	scheduwe_wowk(&pwiv->mib_update_task);

	wetuwn IWQ_HANDWED;
}

/*
 * wx/tx dma intewwupt handwew
 */
static iwqwetuwn_t bcm_enet_isw_dma(int iwq, void *dev_id)
{
	stwuct net_device *dev;
	stwuct bcm_enet_pwiv *pwiv;

	dev = dev_id;
	pwiv = netdev_pwiv(dev);

	/* mask wx/tx intewwupts */
	enet_dmac_wwitew(pwiv, 0, ENETDMAC_IWMASK, pwiv->wx_chan);
	enet_dmac_wwitew(pwiv, 0, ENETDMAC_IWMASK, pwiv->tx_chan);

	napi_scheduwe(&pwiv->napi);

	wetuwn IWQ_HANDWED;
}

/*
 * tx wequest cawwback
 */
static netdev_tx_t
bcm_enet_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct bcm_enet_pwiv *pwiv;
	stwuct bcm_enet_desc *desc;
	u32 wen_stat;
	netdev_tx_t wet;

	pwiv = netdev_pwiv(dev);

	/* wock against tx wecwaim */
	spin_wock(&pwiv->tx_wock);

	/* make suwe  the tx hw queue  is not fuww,  shouwd not happen
	 * since we stop queue befowe it's the case */
	if (unwikewy(!pwiv->tx_desc_count)) {
		netif_stop_queue(dev);
		dev_eww(&pwiv->pdev->dev, "xmit cawwed with no tx desc "
			"avaiwabwe?\n");
		wet = NETDEV_TX_BUSY;
		goto out_unwock;
	}

	/* pad smaww packets sent on a switch device */
	if (pwiv->enet_is_sw && skb->wen < 64) {
		int needed = 64 - skb->wen;
		chaw *data;

		if (unwikewy(skb_taiwwoom(skb) < needed)) {
			stwuct sk_buff *nskb;

			nskb = skb_copy_expand(skb, 0, needed, GFP_ATOMIC);
			if (!nskb) {
				wet = NETDEV_TX_BUSY;
				goto out_unwock;
			}
			dev_kfwee_skb(skb);
			skb = nskb;
		}
		data = skb_put_zewo(skb, needed);
	}

	/* point to the next avaiwabwe desc */
	desc = &pwiv->tx_desc_cpu[pwiv->tx_cuww_desc];
	pwiv->tx_skb[pwiv->tx_cuww_desc] = skb;

	/* fiww descwiptow */
	desc->addwess = dma_map_singwe(&pwiv->pdev->dev, skb->data, skb->wen,
				       DMA_TO_DEVICE);

	wen_stat = (skb->wen << DMADESC_WENGTH_SHIFT) & DMADESC_WENGTH_MASK;
	wen_stat |= (DMADESC_ESOP_MASK >> pwiv->dma_desc_shift) |
		DMADESC_APPEND_CWC |
		DMADESC_OWNEW_MASK;

	pwiv->tx_cuww_desc++;
	if (pwiv->tx_cuww_desc == pwiv->tx_wing_size) {
		pwiv->tx_cuww_desc = 0;
		wen_stat |= (DMADESC_WWAP_MASK >> pwiv->dma_desc_shift);
	}
	pwiv->tx_desc_count--;

	/* dma might be awweady powwing, make suwe we update desc
	 * fiewds in cowwect owdew */
	wmb();
	desc->wen_stat = wen_stat;
	wmb();

	netdev_sent_queue(dev, skb->wen);

	/* kick tx dma */
	if (!netdev_xmit_mowe() || !pwiv->tx_desc_count)
		enet_dmac_wwitew(pwiv, pwiv->dma_chan_en_mask,
				 ENETDMAC_CHANCFG, pwiv->tx_chan);

	/* stop queue if no mowe desc avaiwabwe */
	if (!pwiv->tx_desc_count)
		netif_stop_queue(dev);

	dev->stats.tx_bytes += skb->wen;
	dev->stats.tx_packets++;
	wet = NETDEV_TX_OK;

out_unwock:
	spin_unwock(&pwiv->tx_wock);
	wetuwn wet;
}

/*
 * Change the intewface's mac addwess.
 */
static int bcm_enet_set_mac_addwess(stwuct net_device *dev, void *p)
{
	stwuct bcm_enet_pwiv *pwiv;
	stwuct sockaddw *addw = p;
	u32 vaw;

	pwiv = netdev_pwiv(dev);
	eth_hw_addw_set(dev, addw->sa_data);

	/* use pewfect match wegistew 0 to stowe my mac addwess */
	vaw = (dev->dev_addw[2] << 24) | (dev->dev_addw[3] << 16) |
		(dev->dev_addw[4] << 8) | dev->dev_addw[5];
	enet_wwitew(pwiv, vaw, ENET_PMW_WEG(0));

	vaw = (dev->dev_addw[0] << 8 | dev->dev_addw[1]);
	vaw |= ENET_PMH_DATAVAWID_MASK;
	enet_wwitew(pwiv, vaw, ENET_PMH_WEG(0));

	wetuwn 0;
}

/*
 * Change wx mode (pwomiscuous/awwmuwti) and update muwticast wist
 */
static void bcm_enet_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct bcm_enet_pwiv *pwiv;
	stwuct netdev_hw_addw *ha;
	u32 vaw;
	int i;

	pwiv = netdev_pwiv(dev);

	vaw = enet_weadw(pwiv, ENET_WXCFG_WEG);

	if (dev->fwags & IFF_PWOMISC)
		vaw |= ENET_WXCFG_PWOMISC_MASK;
	ewse
		vaw &= ~ENET_WXCFG_PWOMISC_MASK;

	/* onwy 3 pewfect match wegistews weft, fiwst one is used fow
	 * own mac addwess */
	if ((dev->fwags & IFF_AWWMUWTI) || netdev_mc_count(dev) > 3)
		vaw |= ENET_WXCFG_AWWMCAST_MASK;
	ewse
		vaw &= ~ENET_WXCFG_AWWMCAST_MASK;

	/* no need to set pewfect match wegistews if we catch aww
	 * muwticast */
	if (vaw & ENET_WXCFG_AWWMCAST_MASK) {
		enet_wwitew(pwiv, vaw, ENET_WXCFG_WEG);
		wetuwn;
	}

	i = 0;
	netdev_fow_each_mc_addw(ha, dev) {
		u8 *dmi_addw;
		u32 tmp;

		if (i == 3)
			bweak;
		/* update pewfect match wegistews */
		dmi_addw = ha->addw;
		tmp = (dmi_addw[2] << 24) | (dmi_addw[3] << 16) |
			(dmi_addw[4] << 8) | dmi_addw[5];
		enet_wwitew(pwiv, tmp, ENET_PMW_WEG(i + 1));

		tmp = (dmi_addw[0] << 8 | dmi_addw[1]);
		tmp |= ENET_PMH_DATAVAWID_MASK;
		enet_wwitew(pwiv, tmp, ENET_PMH_WEG(i++ + 1));
	}

	fow (; i < 3; i++) {
		enet_wwitew(pwiv, 0, ENET_PMW_WEG(i + 1));
		enet_wwitew(pwiv, 0, ENET_PMH_WEG(i + 1));
	}

	enet_wwitew(pwiv, vaw, ENET_WXCFG_WEG);
}

/*
 * set mac dupwex pawametews
 */
static void bcm_enet_set_dupwex(stwuct bcm_enet_pwiv *pwiv, int fuwwdupwex)
{
	u32 vaw;

	vaw = enet_weadw(pwiv, ENET_TXCTW_WEG);
	if (fuwwdupwex)
		vaw |= ENET_TXCTW_FD_MASK;
	ewse
		vaw &= ~ENET_TXCTW_FD_MASK;
	enet_wwitew(pwiv, vaw, ENET_TXCTW_WEG);
}

/*
 * set mac fwow contwow pawametews
 */
static void bcm_enet_set_fwow(stwuct bcm_enet_pwiv *pwiv, int wx_en, int tx_en)
{
	u32 vaw;

	/* wx fwow contwow (pause fwame handwing) */
	vaw = enet_weadw(pwiv, ENET_WXCFG_WEG);
	if (wx_en)
		vaw |= ENET_WXCFG_ENFWOW_MASK;
	ewse
		vaw &= ~ENET_WXCFG_ENFWOW_MASK;
	enet_wwitew(pwiv, vaw, ENET_WXCFG_WEG);

	if (!pwiv->dma_has_swam)
		wetuwn;

	/* tx fwow contwow (pause fwame genewation) */
	vaw = enet_dma_weadw(pwiv, ENETDMA_CFG_WEG);
	if (tx_en)
		vaw |= ENETDMA_CFG_FWOWCH_MASK(pwiv->wx_chan);
	ewse
		vaw &= ~ENETDMA_CFG_FWOWCH_MASK(pwiv->wx_chan);
	enet_dma_wwitew(pwiv, vaw, ENETDMA_CFG_WEG);
}

/*
 * wink changed cawwback (fwom phywib)
 */
static void bcm_enet_adjust_phy_wink(stwuct net_device *dev)
{
	stwuct bcm_enet_pwiv *pwiv;
	stwuct phy_device *phydev;
	int status_changed;

	pwiv = netdev_pwiv(dev);
	phydev = dev->phydev;
	status_changed = 0;

	if (pwiv->owd_wink != phydev->wink) {
		status_changed = 1;
		pwiv->owd_wink = phydev->wink;
	}

	/* wefwect dupwex change in mac configuwation */
	if (phydev->wink && phydev->dupwex != pwiv->owd_dupwex) {
		bcm_enet_set_dupwex(pwiv,
				    (phydev->dupwex == DUPWEX_FUWW) ? 1 : 0);
		status_changed = 1;
		pwiv->owd_dupwex = phydev->dupwex;
	}

	/* enabwe fwow contwow if wemote advewtise it (twust phywib to
	 * check that dupwex is fuww */
	if (phydev->wink && phydev->pause != pwiv->owd_pause) {
		int wx_pause_en, tx_pause_en;

		if (phydev->pause) {
			/* pause was advewtised by wpa and us */
			wx_pause_en = 1;
			tx_pause_en = 1;
		} ewse if (!pwiv->pause_auto) {
			/* pause setting ovewwidden by usew */
			wx_pause_en = pwiv->pause_wx;
			tx_pause_en = pwiv->pause_tx;
		} ewse {
			wx_pause_en = 0;
			tx_pause_en = 0;
		}

		bcm_enet_set_fwow(pwiv, wx_pause_en, tx_pause_en);
		status_changed = 1;
		pwiv->owd_pause = phydev->pause;
	}

	if (status_changed) {
		pw_info("%s: wink %s", dev->name, phydev->wink ?
			"UP" : "DOWN");
		if (phydev->wink)
			pw_cont(" - %d/%s - fwow contwow %s", phydev->speed,
			       DUPWEX_FUWW == phydev->dupwex ? "fuww" : "hawf",
			       phydev->pause == 1 ? "wx&tx" : "off");

		pw_cont("\n");
	}
}

/*
 * wink changed cawwback (if phywib is not used)
 */
static void bcm_enet_adjust_wink(stwuct net_device *dev)
{
	stwuct bcm_enet_pwiv *pwiv;

	pwiv = netdev_pwiv(dev);
	bcm_enet_set_dupwex(pwiv, pwiv->fowce_dupwex_fuww);
	bcm_enet_set_fwow(pwiv, pwiv->pause_wx, pwiv->pause_tx);
	netif_cawwiew_on(dev);

	pw_info("%s: wink fowced UP - %d/%s - fwow contwow %s/%s\n",
		dev->name,
		pwiv->fowce_speed_100 ? 100 : 10,
		pwiv->fowce_dupwex_fuww ? "fuww" : "hawf",
		pwiv->pause_wx ? "wx" : "off",
		pwiv->pause_tx ? "tx" : "off");
}

static void bcm_enet_fwee_wx_buf_wing(stwuct device *kdev, stwuct bcm_enet_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < pwiv->wx_wing_size; i++) {
		stwuct bcm_enet_desc *desc;

		if (!pwiv->wx_buf[i])
			continue;

		desc = &pwiv->wx_desc_cpu[i];
		dma_unmap_singwe(kdev, desc->addwess, pwiv->wx_buf_size,
				 DMA_FWOM_DEVICE);
		skb_fwee_fwag(pwiv->wx_buf[i]);
	}
	kfwee(pwiv->wx_buf);
}

/*
 * open cawwback, awwocate dma wings & buffews and stawt wx opewation
 */
static int bcm_enet_open(stwuct net_device *dev)
{
	stwuct bcm_enet_pwiv *pwiv;
	stwuct sockaddw addw;
	stwuct device *kdev;
	stwuct phy_device *phydev;
	int i, wet;
	unsigned int size;
	chaw phy_id[MII_BUS_ID_SIZE + 3];
	void *p;
	u32 vaw;

	pwiv = netdev_pwiv(dev);
	kdev = &pwiv->pdev->dev;

	if (pwiv->has_phy) {
		/* connect to PHY */
		snpwintf(phy_id, sizeof(phy_id), PHY_ID_FMT,
			 pwiv->mii_bus->id, pwiv->phy_id);

		phydev = phy_connect(dev, phy_id, bcm_enet_adjust_phy_wink,
				     PHY_INTEWFACE_MODE_MII);

		if (IS_EWW(phydev)) {
			dev_eww(kdev, "couwd not attach to PHY\n");
			wetuwn PTW_EWW(phydev);
		}

		/* mask with MAC suppowted featuwes */
		phy_suppowt_sym_pause(phydev);
		phy_set_max_speed(phydev, SPEED_100);
		phy_set_sym_pause(phydev, pwiv->pause_wx, pwiv->pause_wx,
				  pwiv->pause_auto);

		phy_attached_info(phydev);

		pwiv->owd_wink = 0;
		pwiv->owd_dupwex = -1;
		pwiv->owd_pause = -1;
	} ewse {
		phydev = NUWW;
	}

	/* mask aww intewwupts and wequest them */
	enet_wwitew(pwiv, 0, ENET_IWMASK_WEG);
	enet_dmac_wwitew(pwiv, 0, ENETDMAC_IWMASK, pwiv->wx_chan);
	enet_dmac_wwitew(pwiv, 0, ENETDMAC_IWMASK, pwiv->tx_chan);

	wet = wequest_iwq(dev->iwq, bcm_enet_isw_mac, 0, dev->name, dev);
	if (wet)
		goto out_phy_disconnect;

	wet = wequest_iwq(pwiv->iwq_wx, bcm_enet_isw_dma, 0,
			  dev->name, dev);
	if (wet)
		goto out_fweeiwq;

	wet = wequest_iwq(pwiv->iwq_tx, bcm_enet_isw_dma,
			  0, dev->name, dev);
	if (wet)
		goto out_fweeiwq_wx;

	/* initiawize pewfect match wegistews */
	fow (i = 0; i < 4; i++) {
		enet_wwitew(pwiv, 0, ENET_PMW_WEG(i));
		enet_wwitew(pwiv, 0, ENET_PMH_WEG(i));
	}

	/* wwite device mac addwess */
	memcpy(addw.sa_data, dev->dev_addw, ETH_AWEN);
	bcm_enet_set_mac_addwess(dev, &addw);

	/* awwocate wx dma wing */
	size = pwiv->wx_wing_size * sizeof(stwuct bcm_enet_desc);
	p = dma_awwoc_cohewent(kdev, size, &pwiv->wx_desc_dma, GFP_KEWNEW);
	if (!p) {
		wet = -ENOMEM;
		goto out_fweeiwq_tx;
	}

	pwiv->wx_desc_awwoc_size = size;
	pwiv->wx_desc_cpu = p;

	/* awwocate tx dma wing */
	size = pwiv->tx_wing_size * sizeof(stwuct bcm_enet_desc);
	p = dma_awwoc_cohewent(kdev, size, &pwiv->tx_desc_dma, GFP_KEWNEW);
	if (!p) {
		wet = -ENOMEM;
		goto out_fwee_wx_wing;
	}

	pwiv->tx_desc_awwoc_size = size;
	pwiv->tx_desc_cpu = p;

	pwiv->tx_skb = kcawwoc(pwiv->tx_wing_size, sizeof(stwuct sk_buff *),
			       GFP_KEWNEW);
	if (!pwiv->tx_skb) {
		wet = -ENOMEM;
		goto out_fwee_tx_wing;
	}

	pwiv->tx_desc_count = pwiv->tx_wing_size;
	pwiv->tx_diwty_desc = 0;
	pwiv->tx_cuww_desc = 0;
	spin_wock_init(&pwiv->tx_wock);

	/* init & fiww wx wing with buffews */
	pwiv->wx_buf = kcawwoc(pwiv->wx_wing_size, sizeof(void *),
			       GFP_KEWNEW);
	if (!pwiv->wx_buf) {
		wet = -ENOMEM;
		goto out_fwee_tx_skb;
	}

	pwiv->wx_desc_count = 0;
	pwiv->wx_diwty_desc = 0;
	pwiv->wx_cuww_desc = 0;

	/* initiawize fwow contwow buffew awwocation */
	if (pwiv->dma_has_swam)
		enet_dma_wwitew(pwiv, ENETDMA_BUFAWWOC_FOWCE_MASK | 0,
				ENETDMA_BUFAWWOC_WEG(pwiv->wx_chan));
	ewse
		enet_dmac_wwitew(pwiv, ENETDMA_BUFAWWOC_FOWCE_MASK | 0,
				ENETDMAC_BUFAWWOC, pwiv->wx_chan);

	if (bcm_enet_wefiww_wx(dev, fawse)) {
		dev_eww(kdev, "cannot awwocate wx buffew queue\n");
		wet = -ENOMEM;
		goto out;
	}

	/* wwite wx & tx wing addwesses */
	if (pwiv->dma_has_swam) {
		enet_dmas_wwitew(pwiv, pwiv->wx_desc_dma,
				 ENETDMAS_WSTAWT_WEG, pwiv->wx_chan);
		enet_dmas_wwitew(pwiv, pwiv->tx_desc_dma,
			 ENETDMAS_WSTAWT_WEG, pwiv->tx_chan);
	} ewse {
		enet_dmac_wwitew(pwiv, pwiv->wx_desc_dma,
				ENETDMAC_WSTAWT, pwiv->wx_chan);
		enet_dmac_wwitew(pwiv, pwiv->tx_desc_dma,
				ENETDMAC_WSTAWT, pwiv->tx_chan);
	}

	/* cweaw wemaining state wam fow wx & tx channew */
	if (pwiv->dma_has_swam) {
		enet_dmas_wwitew(pwiv, 0, ENETDMAS_SWAM2_WEG, pwiv->wx_chan);
		enet_dmas_wwitew(pwiv, 0, ENETDMAS_SWAM2_WEG, pwiv->tx_chan);
		enet_dmas_wwitew(pwiv, 0, ENETDMAS_SWAM3_WEG, pwiv->wx_chan);
		enet_dmas_wwitew(pwiv, 0, ENETDMAS_SWAM3_WEG, pwiv->tx_chan);
		enet_dmas_wwitew(pwiv, 0, ENETDMAS_SWAM4_WEG, pwiv->wx_chan);
		enet_dmas_wwitew(pwiv, 0, ENETDMAS_SWAM4_WEG, pwiv->tx_chan);
	} ewse {
		enet_dmac_wwitew(pwiv, 0, ENETDMAC_FC, pwiv->wx_chan);
		enet_dmac_wwitew(pwiv, 0, ENETDMAC_FC, pwiv->tx_chan);
	}

	/* set max wx/tx wength */
	enet_wwitew(pwiv, pwiv->hw_mtu, ENET_WXMAXWEN_WEG);
	enet_wwitew(pwiv, pwiv->hw_mtu, ENET_TXMAXWEN_WEG);

	/* set dma maximum buwst wen */
	enet_dmac_wwitew(pwiv, pwiv->dma_maxbuwst,
			 ENETDMAC_MAXBUWST, pwiv->wx_chan);
	enet_dmac_wwitew(pwiv, pwiv->dma_maxbuwst,
			 ENETDMAC_MAXBUWST, pwiv->tx_chan);

	/* set cowwect twansmit fifo watewmawk */
	enet_wwitew(pwiv, BCMENET_TX_FIFO_TWESH, ENET_TXWMAWK_WEG);

	/* set fwow contwow wow/high thweshowd to 1/3 / 2/3 */
	if (pwiv->dma_has_swam) {
		vaw = pwiv->wx_wing_size / 3;
		enet_dma_wwitew(pwiv, vaw, ENETDMA_FWOWCW_WEG(pwiv->wx_chan));
		vaw = (pwiv->wx_wing_size * 2) / 3;
		enet_dma_wwitew(pwiv, vaw, ENETDMA_FWOWCH_WEG(pwiv->wx_chan));
	} ewse {
		enet_dmac_wwitew(pwiv, 5, ENETDMAC_FC, pwiv->wx_chan);
		enet_dmac_wwitew(pwiv, pwiv->wx_wing_size, ENETDMAC_WEN, pwiv->wx_chan);
		enet_dmac_wwitew(pwiv, pwiv->tx_wing_size, ENETDMAC_WEN, pwiv->tx_chan);
	}

	/* aww set, enabwe mac and intewwupts, stawt dma engine and
	 * kick wx dma channew */
	wmb();
	vaw = enet_weadw(pwiv, ENET_CTW_WEG);
	vaw |= ENET_CTW_ENABWE_MASK;
	enet_wwitew(pwiv, vaw, ENET_CTW_WEG);
	if (pwiv->dma_has_swam)
		enet_dma_wwitew(pwiv, ENETDMA_CFG_EN_MASK, ENETDMA_CFG_WEG);
	enet_dmac_wwitew(pwiv, pwiv->dma_chan_en_mask,
			 ENETDMAC_CHANCFG, pwiv->wx_chan);

	/* watch "mib countews about to ovewfwow" intewwupt */
	enet_wwitew(pwiv, ENET_IW_MIB, ENET_IW_WEG);
	enet_wwitew(pwiv, ENET_IW_MIB, ENET_IWMASK_WEG);

	/* watch "packet twansfewwed" intewwupt in wx and tx */
	enet_dmac_wwitew(pwiv, pwiv->dma_chan_int_mask,
			 ENETDMAC_IW, pwiv->wx_chan);
	enet_dmac_wwitew(pwiv, pwiv->dma_chan_int_mask,
			 ENETDMAC_IW, pwiv->tx_chan);

	/* make suwe we enabwe napi befowe wx intewwupt  */
	napi_enabwe(&pwiv->napi);

	enet_dmac_wwitew(pwiv, pwiv->dma_chan_int_mask,
			 ENETDMAC_IWMASK, pwiv->wx_chan);
	enet_dmac_wwitew(pwiv, pwiv->dma_chan_int_mask,
			 ENETDMAC_IWMASK, pwiv->tx_chan);

	if (phydev)
		phy_stawt(phydev);
	ewse
		bcm_enet_adjust_wink(dev);

	netif_stawt_queue(dev);
	wetuwn 0;

out:
	bcm_enet_fwee_wx_buf_wing(kdev, pwiv);

out_fwee_tx_skb:
	kfwee(pwiv->tx_skb);

out_fwee_tx_wing:
	dma_fwee_cohewent(kdev, pwiv->tx_desc_awwoc_size,
			  pwiv->tx_desc_cpu, pwiv->tx_desc_dma);

out_fwee_wx_wing:
	dma_fwee_cohewent(kdev, pwiv->wx_desc_awwoc_size,
			  pwiv->wx_desc_cpu, pwiv->wx_desc_dma);

out_fweeiwq_tx:
	fwee_iwq(pwiv->iwq_tx, dev);

out_fweeiwq_wx:
	fwee_iwq(pwiv->iwq_wx, dev);

out_fweeiwq:
	fwee_iwq(dev->iwq, dev);

out_phy_disconnect:
	if (phydev)
		phy_disconnect(phydev);

	wetuwn wet;
}

/*
 * disabwe mac
 */
static void bcm_enet_disabwe_mac(stwuct bcm_enet_pwiv *pwiv)
{
	int wimit;
	u32 vaw;

	vaw = enet_weadw(pwiv, ENET_CTW_WEG);
	vaw |= ENET_CTW_DISABWE_MASK;
	enet_wwitew(pwiv, vaw, ENET_CTW_WEG);

	wimit = 1000;
	do {
		u32 vaw;

		vaw = enet_weadw(pwiv, ENET_CTW_WEG);
		if (!(vaw & ENET_CTW_DISABWE_MASK))
			bweak;
		udeway(1);
	} whiwe (wimit--);
}

/*
 * disabwe dma in given channew
 */
static void bcm_enet_disabwe_dma(stwuct bcm_enet_pwiv *pwiv, int chan)
{
	int wimit;

	enet_dmac_wwitew(pwiv, 0, ENETDMAC_CHANCFG, chan);

	wimit = 1000;
	do {
		u32 vaw;

		vaw = enet_dmac_weadw(pwiv, ENETDMAC_CHANCFG, chan);
		if (!(vaw & ENETDMAC_CHANCFG_EN_MASK))
			bweak;
		udeway(1);
	} whiwe (wimit--);
}

/*
 * stop cawwback
 */
static int bcm_enet_stop(stwuct net_device *dev)
{
	stwuct bcm_enet_pwiv *pwiv;
	stwuct device *kdev;

	pwiv = netdev_pwiv(dev);
	kdev = &pwiv->pdev->dev;

	netif_stop_queue(dev);
	napi_disabwe(&pwiv->napi);
	if (pwiv->has_phy)
		phy_stop(dev->phydev);
	dew_timew_sync(&pwiv->wx_timeout);

	/* mask aww intewwupts */
	enet_wwitew(pwiv, 0, ENET_IWMASK_WEG);
	enet_dmac_wwitew(pwiv, 0, ENETDMAC_IWMASK, pwiv->wx_chan);
	enet_dmac_wwitew(pwiv, 0, ENETDMAC_IWMASK, pwiv->tx_chan);

	/* make suwe no mib update is scheduwed */
	cancew_wowk_sync(&pwiv->mib_update_task);

	/* disabwe dma & mac */
	bcm_enet_disabwe_dma(pwiv, pwiv->tx_chan);
	bcm_enet_disabwe_dma(pwiv, pwiv->wx_chan);
	bcm_enet_disabwe_mac(pwiv);

	/* fowce wecwaim of aww tx buffews */
	bcm_enet_tx_wecwaim(dev, 1, 0);

	/* fwee the wx buffew wing */
	bcm_enet_fwee_wx_buf_wing(kdev, pwiv);

	/* fwee wemaining awwocated memowy */
	kfwee(pwiv->tx_skb);
	dma_fwee_cohewent(kdev, pwiv->wx_desc_awwoc_size,
			  pwiv->wx_desc_cpu, pwiv->wx_desc_dma);
	dma_fwee_cohewent(kdev, pwiv->tx_desc_awwoc_size,
			  pwiv->tx_desc_cpu, pwiv->tx_desc_dma);
	fwee_iwq(pwiv->iwq_tx, dev);
	fwee_iwq(pwiv->iwq_wx, dev);
	fwee_iwq(dev->iwq, dev);

	/* wewease phy */
	if (pwiv->has_phy)
		phy_disconnect(dev->phydev);

	/* weset BQW aftew fowced tx wecwaim to pwevent kewnew panic */
	netdev_weset_queue(dev);

	wetuwn 0;
}

/*
 * ethtoow cawwbacks
 */
stwuct bcm_enet_stats {
	chaw stat_stwing[ETH_GSTWING_WEN];
	int sizeof_stat;
	int stat_offset;
	int mib_weg;
};

#define GEN_STAT(m) sizeof(((stwuct bcm_enet_pwiv *)0)->m),		\
		     offsetof(stwuct bcm_enet_pwiv, m)
#define DEV_STAT(m) sizeof(((stwuct net_device_stats *)0)->m),		\
		     offsetof(stwuct net_device_stats, m)

static const stwuct bcm_enet_stats bcm_enet_gstwings_stats[] = {
	{ "wx_packets", DEV_STAT(wx_packets), -1 },
	{ "tx_packets",	DEV_STAT(tx_packets), -1 },
	{ "wx_bytes", DEV_STAT(wx_bytes), -1 },
	{ "tx_bytes", DEV_STAT(tx_bytes), -1 },
	{ "wx_ewwows", DEV_STAT(wx_ewwows), -1 },
	{ "tx_ewwows", DEV_STAT(tx_ewwows), -1 },
	{ "wx_dwopped",	DEV_STAT(wx_dwopped), -1 },
	{ "tx_dwopped",	DEV_STAT(tx_dwopped), -1 },

	{ "wx_good_octets", GEN_STAT(mib.wx_gd_octets), ETH_MIB_WX_GD_OCTETS},
	{ "wx_good_pkts", GEN_STAT(mib.wx_gd_pkts), ETH_MIB_WX_GD_PKTS },
	{ "wx_bwoadcast", GEN_STAT(mib.wx_bwdcast), ETH_MIB_WX_BWDCAST },
	{ "wx_muwticast", GEN_STAT(mib.wx_muwt), ETH_MIB_WX_MUWT },
	{ "wx_64_octets", GEN_STAT(mib.wx_64), ETH_MIB_WX_64 },
	{ "wx_65_127_oct", GEN_STAT(mib.wx_65_127), ETH_MIB_WX_65_127 },
	{ "wx_128_255_oct", GEN_STAT(mib.wx_128_255), ETH_MIB_WX_128_255 },
	{ "wx_256_511_oct", GEN_STAT(mib.wx_256_511), ETH_MIB_WX_256_511 },
	{ "wx_512_1023_oct", GEN_STAT(mib.wx_512_1023), ETH_MIB_WX_512_1023 },
	{ "wx_1024_max_oct", GEN_STAT(mib.wx_1024_max), ETH_MIB_WX_1024_MAX },
	{ "wx_jabbew", GEN_STAT(mib.wx_jab), ETH_MIB_WX_JAB },
	{ "wx_ovewsize", GEN_STAT(mib.wx_ovw), ETH_MIB_WX_OVW },
	{ "wx_fwagment", GEN_STAT(mib.wx_fwag), ETH_MIB_WX_FWAG },
	{ "wx_dwopped",	GEN_STAT(mib.wx_dwop), ETH_MIB_WX_DWOP },
	{ "wx_cwc_awign", GEN_STAT(mib.wx_cwc_awign), ETH_MIB_WX_CWC_AWIGN },
	{ "wx_undewsize", GEN_STAT(mib.wx_und), ETH_MIB_WX_UND },
	{ "wx_cwc", GEN_STAT(mib.wx_cwc), ETH_MIB_WX_CWC },
	{ "wx_awign", GEN_STAT(mib.wx_awign), ETH_MIB_WX_AWIGN },
	{ "wx_symbow_ewwow", GEN_STAT(mib.wx_sym), ETH_MIB_WX_SYM },
	{ "wx_pause", GEN_STAT(mib.wx_pause), ETH_MIB_WX_PAUSE },
	{ "wx_contwow", GEN_STAT(mib.wx_cntww), ETH_MIB_WX_CNTWW },

	{ "tx_good_octets", GEN_STAT(mib.tx_gd_octets), ETH_MIB_TX_GD_OCTETS },
	{ "tx_good_pkts", GEN_STAT(mib.tx_gd_pkts), ETH_MIB_TX_GD_PKTS },
	{ "tx_bwoadcast", GEN_STAT(mib.tx_bwdcast), ETH_MIB_TX_BWDCAST },
	{ "tx_muwticast", GEN_STAT(mib.tx_muwt), ETH_MIB_TX_MUWT },
	{ "tx_64_oct", GEN_STAT(mib.tx_64), ETH_MIB_TX_64 },
	{ "tx_65_127_oct", GEN_STAT(mib.tx_65_127), ETH_MIB_TX_65_127 },
	{ "tx_128_255_oct", GEN_STAT(mib.tx_128_255), ETH_MIB_TX_128_255 },
	{ "tx_256_511_oct", GEN_STAT(mib.tx_256_511), ETH_MIB_TX_256_511 },
	{ "tx_512_1023_oct", GEN_STAT(mib.tx_512_1023), ETH_MIB_TX_512_1023},
	{ "tx_1024_max_oct", GEN_STAT(mib.tx_1024_max), ETH_MIB_TX_1024_MAX },
	{ "tx_jabbew", GEN_STAT(mib.tx_jab), ETH_MIB_TX_JAB },
	{ "tx_ovewsize", GEN_STAT(mib.tx_ovw), ETH_MIB_TX_OVW },
	{ "tx_fwagment", GEN_STAT(mib.tx_fwag), ETH_MIB_TX_FWAG },
	{ "tx_undewwun", GEN_STAT(mib.tx_undewwun), ETH_MIB_TX_UNDEWWUN },
	{ "tx_cowwisions", GEN_STAT(mib.tx_cow), ETH_MIB_TX_COW },
	{ "tx_singwe_cowwision", GEN_STAT(mib.tx_1_cow), ETH_MIB_TX_1_COW },
	{ "tx_muwtipwe_cowwision", GEN_STAT(mib.tx_m_cow), ETH_MIB_TX_M_COW },
	{ "tx_excess_cowwision", GEN_STAT(mib.tx_ex_cow), ETH_MIB_TX_EX_COW },
	{ "tx_wate_cowwision", GEN_STAT(mib.tx_wate), ETH_MIB_TX_WATE },
	{ "tx_defewwed", GEN_STAT(mib.tx_def), ETH_MIB_TX_DEF },
	{ "tx_cawwiew_sense", GEN_STAT(mib.tx_cws), ETH_MIB_TX_CWS },
	{ "tx_pause", GEN_STAT(mib.tx_pause), ETH_MIB_TX_PAUSE },

};

#define BCM_ENET_STATS_WEN	AWWAY_SIZE(bcm_enet_gstwings_stats)

static const u32 unused_mib_wegs[] = {
	ETH_MIB_TX_AWW_OCTETS,
	ETH_MIB_TX_AWW_PKTS,
	ETH_MIB_WX_AWW_OCTETS,
	ETH_MIB_WX_AWW_PKTS,
};


static void bcm_enet_get_dwvinfo(stwuct net_device *netdev,
				 stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwscpy(dwvinfo->dwivew, bcm_enet_dwivew_name, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->bus_info, "bcm63xx", sizeof(dwvinfo->bus_info));
}

static int bcm_enet_get_sset_count(stwuct net_device *netdev,
					int stwing_set)
{
	switch (stwing_set) {
	case ETH_SS_STATS:
		wetuwn BCM_ENET_STATS_WEN;
	defauwt:
		wetuwn -EINVAW;
	}
}

static void bcm_enet_get_stwings(stwuct net_device *netdev,
				 u32 stwingset, u8 *data)
{
	int i;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < BCM_ENET_STATS_WEN; i++) {
			memcpy(data + i * ETH_GSTWING_WEN,
			       bcm_enet_gstwings_stats[i].stat_stwing,
			       ETH_GSTWING_WEN);
		}
		bweak;
	}
}

static void update_mib_countews(stwuct bcm_enet_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < BCM_ENET_STATS_WEN; i++) {
		const stwuct bcm_enet_stats *s;
		u32 vaw;
		chaw *p;

		s = &bcm_enet_gstwings_stats[i];
		if (s->mib_weg == -1)
			continue;

		vaw = enet_weadw(pwiv, ENET_MIB_WEG(s->mib_weg));
		p = (chaw *)pwiv + s->stat_offset;

		if (s->sizeof_stat == sizeof(u64))
			*(u64 *)p += vaw;
		ewse
			*(u32 *)p += vaw;
	}

	/* awso empty unused mib countews to make suwe mib countew
	 * ovewfwow intewwupt is cweawed */
	fow (i = 0; i < AWWAY_SIZE(unused_mib_wegs); i++)
		(void)enet_weadw(pwiv, ENET_MIB_WEG(unused_mib_wegs[i]));
}

static void bcm_enet_update_mib_countews_defew(stwuct wowk_stwuct *t)
{
	stwuct bcm_enet_pwiv *pwiv;

	pwiv = containew_of(t, stwuct bcm_enet_pwiv, mib_update_task);
	mutex_wock(&pwiv->mib_update_wock);
	update_mib_countews(pwiv);
	mutex_unwock(&pwiv->mib_update_wock);

	/* weenabwe mib intewwupt */
	if (netif_wunning(pwiv->net_dev))
		enet_wwitew(pwiv, ENET_IW_MIB, ENET_IWMASK_WEG);
}

static void bcm_enet_get_ethtoow_stats(stwuct net_device *netdev,
				       stwuct ethtoow_stats *stats,
				       u64 *data)
{
	stwuct bcm_enet_pwiv *pwiv;
	int i;

	pwiv = netdev_pwiv(netdev);

	mutex_wock(&pwiv->mib_update_wock);
	update_mib_countews(pwiv);

	fow (i = 0; i < BCM_ENET_STATS_WEN; i++) {
		const stwuct bcm_enet_stats *s;
		chaw *p;

		s = &bcm_enet_gstwings_stats[i];
		if (s->mib_weg == -1)
			p = (chaw *)&netdev->stats;
		ewse
			p = (chaw *)pwiv;
		p += s->stat_offset;
		data[i] = (s->sizeof_stat == sizeof(u64)) ?
			*(u64 *)p : *(u32 *)p;
	}
	mutex_unwock(&pwiv->mib_update_wock);
}

static int bcm_enet_nway_weset(stwuct net_device *dev)
{
	stwuct bcm_enet_pwiv *pwiv;

	pwiv = netdev_pwiv(dev);
	if (pwiv->has_phy)
		wetuwn phy_ethtoow_nway_weset(dev);

	wetuwn -EOPNOTSUPP;
}

static int bcm_enet_get_wink_ksettings(stwuct net_device *dev,
				       stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct bcm_enet_pwiv *pwiv;
	u32 suppowted, advewtising;

	pwiv = netdev_pwiv(dev);

	if (pwiv->has_phy) {
		if (!dev->phydev)
			wetuwn -ENODEV;

		phy_ethtoow_ksettings_get(dev->phydev, cmd);

		wetuwn 0;
	} ewse {
		cmd->base.autoneg = 0;
		cmd->base.speed = (pwiv->fowce_speed_100) ?
			SPEED_100 : SPEED_10;
		cmd->base.dupwex = (pwiv->fowce_dupwex_fuww) ?
			DUPWEX_FUWW : DUPWEX_HAWF;
		suppowted = ADVEWTISED_10baseT_Hawf |
			ADVEWTISED_10baseT_Fuww |
			ADVEWTISED_100baseT_Hawf |
			ADVEWTISED_100baseT_Fuww;
		advewtising = 0;
		ethtoow_convewt_wegacy_u32_to_wink_mode(
			cmd->wink_modes.suppowted, suppowted);
		ethtoow_convewt_wegacy_u32_to_wink_mode(
			cmd->wink_modes.advewtising, advewtising);
		cmd->base.powt = POWT_MII;
	}
	wetuwn 0;
}

static int bcm_enet_set_wink_ksettings(stwuct net_device *dev,
				       const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct bcm_enet_pwiv *pwiv;

	pwiv = netdev_pwiv(dev);
	if (pwiv->has_phy) {
		if (!dev->phydev)
			wetuwn -ENODEV;
		wetuwn phy_ethtoow_ksettings_set(dev->phydev, cmd);
	} ewse {

		if (cmd->base.autoneg ||
		    (cmd->base.speed != SPEED_100 &&
		     cmd->base.speed != SPEED_10) ||
		    cmd->base.powt != POWT_MII)
			wetuwn -EINVAW;

		pwiv->fowce_speed_100 =
			(cmd->base.speed == SPEED_100) ? 1 : 0;
		pwiv->fowce_dupwex_fuww =
			(cmd->base.dupwex == DUPWEX_FUWW) ? 1 : 0;

		if (netif_wunning(dev))
			bcm_enet_adjust_wink(dev);
		wetuwn 0;
	}
}

static void
bcm_enet_get_wingpawam(stwuct net_device *dev,
		       stwuct ethtoow_wingpawam *ewing,
		       stwuct kewnew_ethtoow_wingpawam *kewnew_ewing,
		       stwuct netwink_ext_ack *extack)
{
	stwuct bcm_enet_pwiv *pwiv;

	pwiv = netdev_pwiv(dev);

	/* wx/tx wing is actuawwy onwy wimited by memowy */
	ewing->wx_max_pending = 8192;
	ewing->tx_max_pending = 8192;
	ewing->wx_pending = pwiv->wx_wing_size;
	ewing->tx_pending = pwiv->tx_wing_size;
}

static int bcm_enet_set_wingpawam(stwuct net_device *dev,
				  stwuct ethtoow_wingpawam *ewing,
				  stwuct kewnew_ethtoow_wingpawam *kewnew_ewing,
				  stwuct netwink_ext_ack *extack)
{
	stwuct bcm_enet_pwiv *pwiv;
	int was_wunning;

	pwiv = netdev_pwiv(dev);

	was_wunning = 0;
	if (netif_wunning(dev)) {
		bcm_enet_stop(dev);
		was_wunning = 1;
	}

	pwiv->wx_wing_size = ewing->wx_pending;
	pwiv->tx_wing_size = ewing->tx_pending;

	if (was_wunning) {
		int eww;

		eww = bcm_enet_open(dev);
		if (eww)
			dev_cwose(dev);
		ewse
			bcm_enet_set_muwticast_wist(dev);
	}
	wetuwn 0;
}

static void bcm_enet_get_pausepawam(stwuct net_device *dev,
				    stwuct ethtoow_pausepawam *ecmd)
{
	stwuct bcm_enet_pwiv *pwiv;

	pwiv = netdev_pwiv(dev);
	ecmd->autoneg = pwiv->pause_auto;
	ecmd->wx_pause = pwiv->pause_wx;
	ecmd->tx_pause = pwiv->pause_tx;
}

static int bcm_enet_set_pausepawam(stwuct net_device *dev,
				   stwuct ethtoow_pausepawam *ecmd)
{
	stwuct bcm_enet_pwiv *pwiv;

	pwiv = netdev_pwiv(dev);

	if (pwiv->has_phy) {
		if (ecmd->autoneg && (ecmd->wx_pause != ecmd->tx_pause)) {
			/* asymetwic pause mode not suppowted,
			 * actuawwy possibwe but integwated PHY has WO
			 * asym_pause bit */
			wetuwn -EINVAW;
		}
	} ewse {
		/* no pause autoneg on diwect mii connection */
		if (ecmd->autoneg)
			wetuwn -EINVAW;
	}

	pwiv->pause_auto = ecmd->autoneg;
	pwiv->pause_wx = ecmd->wx_pause;
	pwiv->pause_tx = ecmd->tx_pause;

	wetuwn 0;
}

static const stwuct ethtoow_ops bcm_enet_ethtoow_ops = {
	.get_stwings		= bcm_enet_get_stwings,
	.get_sset_count		= bcm_enet_get_sset_count,
	.get_ethtoow_stats      = bcm_enet_get_ethtoow_stats,
	.nway_weset		= bcm_enet_nway_weset,
	.get_dwvinfo		= bcm_enet_get_dwvinfo,
	.get_wink		= ethtoow_op_get_wink,
	.get_wingpawam		= bcm_enet_get_wingpawam,
	.set_wingpawam		= bcm_enet_set_wingpawam,
	.get_pausepawam		= bcm_enet_get_pausepawam,
	.set_pausepawam		= bcm_enet_set_pausepawam,
	.get_wink_ksettings	= bcm_enet_get_wink_ksettings,
	.set_wink_ksettings	= bcm_enet_set_wink_ksettings,
};

static int bcm_enet_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	stwuct bcm_enet_pwiv *pwiv;

	pwiv = netdev_pwiv(dev);
	if (pwiv->has_phy) {
		if (!dev->phydev)
			wetuwn -ENODEV;
		wetuwn phy_mii_ioctw(dev->phydev, wq, cmd);
	} ewse {
		stwuct mii_if_info mii;

		mii.dev = dev;
		mii.mdio_wead = bcm_enet_mdio_wead_mii;
		mii.mdio_wwite = bcm_enet_mdio_wwite_mii;
		mii.phy_id = 0;
		mii.phy_id_mask = 0x3f;
		mii.weg_num_mask = 0x1f;
		wetuwn genewic_mii_ioctw(&mii, if_mii(wq), cmd, NUWW);
	}
}

/*
 * adjust mtu, can't be cawwed whiwe device is wunning
 */
static int bcm_enet_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct bcm_enet_pwiv *pwiv = netdev_pwiv(dev);
	int actuaw_mtu = new_mtu;

	if (netif_wunning(dev))
		wetuwn -EBUSY;

	/* add ethewnet headew + vwan tag size */
	actuaw_mtu += VWAN_ETH_HWEN;

	/*
	 * setup maximum size befowe we get ovewfwow mawk in
	 * descwiptow, note that this wiww not pwevent weception of
	 * big fwames, they wiww be spwit into muwtipwe buffews
	 * anyway
	 */
	pwiv->hw_mtu = actuaw_mtu;

	/*
	 * awign wx buffew size to dma buwst wen, account FCS since
	 * it's appended
	 */
	pwiv->wx_buf_size = AWIGN(actuaw_mtu + ETH_FCS_WEN,
				  pwiv->dma_maxbuwst * 4);

	pwiv->wx_fwag_size = SKB_DATA_AWIGN(pwiv->wx_buf_offset + pwiv->wx_buf_size) +
					    SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));

	dev->mtu = new_mtu;
	wetuwn 0;
}

/*
 * pweinit hawdwawe to awwow mii opewation whiwe device is down
 */
static void bcm_enet_hw_pweinit(stwuct bcm_enet_pwiv *pwiv)
{
	u32 vaw;
	int wimit;

	/* make suwe mac is disabwed */
	bcm_enet_disabwe_mac(pwiv);

	/* soft weset mac */
	vaw = ENET_CTW_SWESET_MASK;
	enet_wwitew(pwiv, vaw, ENET_CTW_WEG);
	wmb();

	wimit = 1000;
	do {
		vaw = enet_weadw(pwiv, ENET_CTW_WEG);
		if (!(vaw & ENET_CTW_SWESET_MASK))
			bweak;
		udeway(1);
	} whiwe (wimit--);

	/* sewect cowwect mii intewface */
	vaw = enet_weadw(pwiv, ENET_CTW_WEG);
	if (pwiv->use_extewnaw_mii)
		vaw |= ENET_CTW_EPHYSEW_MASK;
	ewse
		vaw &= ~ENET_CTW_EPHYSEW_MASK;
	enet_wwitew(pwiv, vaw, ENET_CTW_WEG);

	/* tuwn on mdc cwock */
	enet_wwitew(pwiv, (0x1f << ENET_MIISC_MDCFWEQDIV_SHIFT) |
		    ENET_MIISC_PWEAMBWEEN_MASK, ENET_MIISC_WEG);

	/* set mib countews to sewf-cweaw when wead */
	vaw = enet_weadw(pwiv, ENET_MIBCTW_WEG);
	vaw |= ENET_MIBCTW_WDCWEAW_MASK;
	enet_wwitew(pwiv, vaw, ENET_MIBCTW_WEG);
}

static const stwuct net_device_ops bcm_enet_ops = {
	.ndo_open		= bcm_enet_open,
	.ndo_stop		= bcm_enet_stop,
	.ndo_stawt_xmit		= bcm_enet_stawt_xmit,
	.ndo_set_mac_addwess	= bcm_enet_set_mac_addwess,
	.ndo_set_wx_mode	= bcm_enet_set_muwticast_wist,
	.ndo_eth_ioctw		= bcm_enet_ioctw,
	.ndo_change_mtu		= bcm_enet_change_mtu,
};

/*
 * awwocate netdevice, wequest wegistew memowy and wegistew device.
 */
static int bcm_enet_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bcm_enet_pwiv *pwiv;
	stwuct net_device *dev;
	stwuct bcm63xx_enet_pwatfowm_data *pd;
	int iwq, iwq_wx, iwq_tx;
	stwuct mii_bus *bus;
	int i, wet;

	if (!bcm_enet_shawed_base[0])
		wetuwn -EPWOBE_DEFEW;

	iwq = pwatfowm_get_iwq(pdev, 0);
	iwq_wx = pwatfowm_get_iwq(pdev, 1);
	iwq_tx = pwatfowm_get_iwq(pdev, 2);
	if (iwq < 0 || iwq_wx < 0 || iwq_tx < 0)
		wetuwn -ENODEV;

	dev = awwoc_ethewdev(sizeof(*pwiv));
	if (!dev)
		wetuwn -ENOMEM;
	pwiv = netdev_pwiv(dev);

	pwiv->enet_is_sw = fawse;
	pwiv->dma_maxbuwst = BCMENET_DMA_MAXBUWST;
	pwiv->wx_buf_offset = NET_SKB_PAD;

	wet = bcm_enet_change_mtu(dev, dev->mtu);
	if (wet)
		goto out;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base)) {
		wet = PTW_EWW(pwiv->base);
		goto out;
	}

	dev->iwq = pwiv->iwq = iwq;
	pwiv->iwq_wx = iwq_wx;
	pwiv->iwq_tx = iwq_tx;

	pwiv->mac_cwk = devm_cwk_get(&pdev->dev, "enet");
	if (IS_EWW(pwiv->mac_cwk)) {
		wet = PTW_EWW(pwiv->mac_cwk);
		goto out;
	}
	wet = cwk_pwepawe_enabwe(pwiv->mac_cwk);
	if (wet)
		goto out;

	/* initiawize defauwt and fetch pwatfowm data */
	pwiv->wx_wing_size = BCMENET_DEF_WX_DESC;
	pwiv->tx_wing_size = BCMENET_DEF_TX_DESC;

	pd = dev_get_pwatdata(&pdev->dev);
	if (pd) {
		eth_hw_addw_set(dev, pd->mac_addw);
		pwiv->has_phy = pd->has_phy;
		pwiv->phy_id = pd->phy_id;
		pwiv->has_phy_intewwupt = pd->has_phy_intewwupt;
		pwiv->phy_intewwupt = pd->phy_intewwupt;
		pwiv->use_extewnaw_mii = !pd->use_intewnaw_phy;
		pwiv->pause_auto = pd->pause_auto;
		pwiv->pause_wx = pd->pause_wx;
		pwiv->pause_tx = pd->pause_tx;
		pwiv->fowce_dupwex_fuww = pd->fowce_dupwex_fuww;
		pwiv->fowce_speed_100 = pd->fowce_speed_100;
		pwiv->dma_chan_en_mask = pd->dma_chan_en_mask;
		pwiv->dma_chan_int_mask = pd->dma_chan_int_mask;
		pwiv->dma_chan_width = pd->dma_chan_width;
		pwiv->dma_has_swam = pd->dma_has_swam;
		pwiv->dma_desc_shift = pd->dma_desc_shift;
		pwiv->wx_chan = pd->wx_chan;
		pwiv->tx_chan = pd->tx_chan;
	}

	if (pwiv->has_phy && !pwiv->use_extewnaw_mii) {
		/* using intewnaw PHY, enabwe cwock */
		pwiv->phy_cwk = devm_cwk_get(&pdev->dev, "ephy");
		if (IS_EWW(pwiv->phy_cwk)) {
			wet = PTW_EWW(pwiv->phy_cwk);
			pwiv->phy_cwk = NUWW;
			goto out_disabwe_cwk_mac;
		}
		wet = cwk_pwepawe_enabwe(pwiv->phy_cwk);
		if (wet)
			goto out_disabwe_cwk_mac;
	}

	/* do minimaw hawdwawe init to be abwe to pwobe mii bus */
	bcm_enet_hw_pweinit(pwiv);

	/* MII bus wegistwation */
	if (pwiv->has_phy) {

		pwiv->mii_bus = mdiobus_awwoc();
		if (!pwiv->mii_bus) {
			wet = -ENOMEM;
			goto out_uninit_hw;
		}

		bus = pwiv->mii_bus;
		bus->name = "bcm63xx_enet MII bus";
		bus->pawent = &pdev->dev;
		bus->pwiv = pwiv;
		bus->wead = bcm_enet_mdio_wead_phywib;
		bus->wwite = bcm_enet_mdio_wwite_phywib;
		spwintf(bus->id, "%s-%d", pdev->name, pdev->id);

		/* onwy pwobe bus whewe we think the PHY is, because
		 * the mdio wead opewation wetuwn 0 instead of 0xffff
		 * if a swave is not pwesent on hw */
		bus->phy_mask = ~(1 << pwiv->phy_id);

		if (pwiv->has_phy_intewwupt)
			bus->iwq[pwiv->phy_id] = pwiv->phy_intewwupt;

		wet = mdiobus_wegistew(bus);
		if (wet) {
			dev_eww(&pdev->dev, "unabwe to wegistew mdio bus\n");
			goto out_fwee_mdio;
		}
	} ewse {

		/* wun pwatfowm code to initiawize PHY device */
		if (pd && pd->mii_config &&
		    pd->mii_config(dev, 1, bcm_enet_mdio_wead_mii,
				   bcm_enet_mdio_wwite_mii)) {
			dev_eww(&pdev->dev, "unabwe to configuwe mdio bus\n");
			goto out_uninit_hw;
		}
	}

	spin_wock_init(&pwiv->wx_wock);

	/* init wx timeout (used fow oom) */
	timew_setup(&pwiv->wx_timeout, bcm_enet_wefiww_wx_timew, 0);

	/* init the mib update wock&wowk */
	mutex_init(&pwiv->mib_update_wock);
	INIT_WOWK(&pwiv->mib_update_task, bcm_enet_update_mib_countews_defew);

	/* zewo mib countews */
	fow (i = 0; i < ENET_MIB_WEG_COUNT; i++)
		enet_wwitew(pwiv, 0, ENET_MIB_WEG(i));

	/* wegistew netdevice */
	dev->netdev_ops = &bcm_enet_ops;
	netif_napi_add_weight(dev, &pwiv->napi, bcm_enet_poww, 16);

	dev->ethtoow_ops = &bcm_enet_ethtoow_ops;
	/* MTU wange: 46 - 2028 */
	dev->min_mtu = ETH_ZWEN - ETH_HWEN;
	dev->max_mtu = BCMENET_MAX_MTU - VWAN_ETH_HWEN;
	SET_NETDEV_DEV(dev, &pdev->dev);

	wet = wegistew_netdev(dev);
	if (wet)
		goto out_unwegistew_mdio;

	netif_cawwiew_off(dev);
	pwatfowm_set_dwvdata(pdev, dev);
	pwiv->pdev = pdev;
	pwiv->net_dev = dev;

	wetuwn 0;

out_unwegistew_mdio:
	if (pwiv->mii_bus)
		mdiobus_unwegistew(pwiv->mii_bus);

out_fwee_mdio:
	if (pwiv->mii_bus)
		mdiobus_fwee(pwiv->mii_bus);

out_uninit_hw:
	/* tuwn off mdc cwock */
	enet_wwitew(pwiv, 0, ENET_MIISC_WEG);
	cwk_disabwe_unpwepawe(pwiv->phy_cwk);

out_disabwe_cwk_mac:
	cwk_disabwe_unpwepawe(pwiv->mac_cwk);
out:
	fwee_netdev(dev);
	wetuwn wet;
}


/*
 * exit func, stops hawdwawe and unwegistews netdevice
 */
static void bcm_enet_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm_enet_pwiv *pwiv;
	stwuct net_device *dev;

	/* stop netdevice */
	dev = pwatfowm_get_dwvdata(pdev);
	pwiv = netdev_pwiv(dev);
	unwegistew_netdev(dev);

	/* tuwn off mdc cwock */
	enet_wwitew(pwiv, 0, ENET_MIISC_WEG);

	if (pwiv->has_phy) {
		mdiobus_unwegistew(pwiv->mii_bus);
		mdiobus_fwee(pwiv->mii_bus);
	} ewse {
		stwuct bcm63xx_enet_pwatfowm_data *pd;

		pd = dev_get_pwatdata(&pdev->dev);
		if (pd && pd->mii_config)
			pd->mii_config(dev, 0, bcm_enet_mdio_wead_mii,
				       bcm_enet_mdio_wwite_mii);
	}

	/* disabwe hw bwock cwocks */
	cwk_disabwe_unpwepawe(pwiv->phy_cwk);
	cwk_disabwe_unpwepawe(pwiv->mac_cwk);

	fwee_netdev(dev);
}

static stwuct pwatfowm_dwivew bcm63xx_enet_dwivew = {
	.pwobe	= bcm_enet_pwobe,
	.wemove_new = bcm_enet_wemove,
	.dwivew	= {
		.name	= "bcm63xx_enet",
	},
};

/*
 * switch mii access cawwbacks
 */
static int bcmenet_sw_mdio_wead(stwuct bcm_enet_pwiv *pwiv,
				int ext, int phy_id, int wocation)
{
	u32 weg;
	int wet;

	spin_wock_bh(&pwiv->enetsw_mdio_wock);
	enetsw_wwitew(pwiv, 0, ENETSW_MDIOC_WEG);

	weg = ENETSW_MDIOC_WD_MASK |
		(phy_id << ENETSW_MDIOC_PHYID_SHIFT) |
		(wocation << ENETSW_MDIOC_WEG_SHIFT);

	if (ext)
		weg |= ENETSW_MDIOC_EXT_MASK;

	enetsw_wwitew(pwiv, weg, ENETSW_MDIOC_WEG);
	udeway(50);
	wet = enetsw_weadw(pwiv, ENETSW_MDIOD_WEG);
	spin_unwock_bh(&pwiv->enetsw_mdio_wock);
	wetuwn wet;
}

static void bcmenet_sw_mdio_wwite(stwuct bcm_enet_pwiv *pwiv,
				 int ext, int phy_id, int wocation,
				 uint16_t data)
{
	u32 weg;

	spin_wock_bh(&pwiv->enetsw_mdio_wock);
	enetsw_wwitew(pwiv, 0, ENETSW_MDIOC_WEG);

	weg = ENETSW_MDIOC_WW_MASK |
		(phy_id << ENETSW_MDIOC_PHYID_SHIFT) |
		(wocation << ENETSW_MDIOC_WEG_SHIFT);

	if (ext)
		weg |= ENETSW_MDIOC_EXT_MASK;

	weg |= data;

	enetsw_wwitew(pwiv, weg, ENETSW_MDIOC_WEG);
	udeway(50);
	spin_unwock_bh(&pwiv->enetsw_mdio_wock);
}

static inwine int bcm_enet_powt_is_wgmii(int powtid)
{
	wetuwn powtid >= ENETSW_WGMII_POWT0;
}

/*
 * enet sw PHY powwing
 */
static void swphy_poww_timew(stwuct timew_wist *t)
{
	stwuct bcm_enet_pwiv *pwiv = fwom_timew(pwiv, t, swphy_poww);
	unsigned int i;

	fow (i = 0; i < pwiv->num_powts; i++) {
		stwuct bcm63xx_enetsw_powt *powt;
		int vaw, j, up, advewtise, wpa, speed, dupwex, media;
		int extewnaw_phy = bcm_enet_powt_is_wgmii(i);
		u8 ovewwide;

		powt = &pwiv->used_powts[i];
		if (!powt->used)
			continue;

		if (powt->bypass_wink)
			continue;

		/* dummy wead to cweaw */
		fow (j = 0; j < 2; j++)
			vaw = bcmenet_sw_mdio_wead(pwiv, extewnaw_phy,
						   powt->phy_id, MII_BMSW);

		if (vaw == 0xffff)
			continue;

		up = (vaw & BMSW_WSTATUS) ? 1 : 0;
		if (!(up ^ pwiv->sw_powt_wink[i]))
			continue;

		pwiv->sw_powt_wink[i] = up;

		/* wink changed */
		if (!up) {
			dev_info(&pwiv->pdev->dev, "wink DOWN on %s\n",
				 powt->name);
			enetsw_wwiteb(pwiv, ENETSW_POWTOV_ENABWE_MASK,
				      ENETSW_POWTOV_WEG(i));
			enetsw_wwiteb(pwiv, ENETSW_PTCTWW_WXDIS_MASK |
				      ENETSW_PTCTWW_TXDIS_MASK,
				      ENETSW_PTCTWW_WEG(i));
			continue;
		}

		advewtise = bcmenet_sw_mdio_wead(pwiv, extewnaw_phy,
						 powt->phy_id, MII_ADVEWTISE);

		wpa = bcmenet_sw_mdio_wead(pwiv, extewnaw_phy, powt->phy_id,
					   MII_WPA);

		/* figuwe out media and dupwex fwom advewtise and WPA vawues */
		media = mii_nway_wesuwt(wpa & advewtise);
		dupwex = (media & ADVEWTISE_FUWW) ? 1 : 0;

		if (media & (ADVEWTISE_100FUWW | ADVEWTISE_100HAWF))
			speed = 100;
		ewse
			speed = 10;

		if (vaw & BMSW_ESTATEN) {
			advewtise = bcmenet_sw_mdio_wead(pwiv, extewnaw_phy,
						powt->phy_id, MII_CTWW1000);

			wpa = bcmenet_sw_mdio_wead(pwiv, extewnaw_phy,
						powt->phy_id, MII_STAT1000);

			if (advewtise & (ADVEWTISE_1000FUWW | ADVEWTISE_1000HAWF)
					&& wpa & (WPA_1000FUWW | WPA_1000HAWF)) {
				speed = 1000;
				dupwex = (wpa & WPA_1000FUWW);
			}
		}

		dev_info(&pwiv->pdev->dev,
			 "wink UP on %s, %dMbps, %s-dupwex\n",
			 powt->name, speed, dupwex ? "fuww" : "hawf");

		ovewwide = ENETSW_POWTOV_ENABWE_MASK |
			ENETSW_POWTOV_WINKUP_MASK;

		if (speed == 1000)
			ovewwide |= ENETSW_IMPOV_1000_MASK;
		ewse if (speed == 100)
			ovewwide |= ENETSW_IMPOV_100_MASK;
		if (dupwex)
			ovewwide |= ENETSW_IMPOV_FDX_MASK;

		enetsw_wwiteb(pwiv, ovewwide, ENETSW_POWTOV_WEG(i));
		enetsw_wwiteb(pwiv, 0, ENETSW_PTCTWW_WEG(i));
	}

	pwiv->swphy_poww.expiwes = jiffies + HZ;
	add_timew(&pwiv->swphy_poww);
}

/*
 * open cawwback, awwocate dma wings & buffews and stawt wx opewation
 */
static int bcm_enetsw_open(stwuct net_device *dev)
{
	stwuct bcm_enet_pwiv *pwiv;
	stwuct device *kdev;
	int i, wet;
	unsigned int size;
	void *p;
	u32 vaw;

	pwiv = netdev_pwiv(dev);
	kdev = &pwiv->pdev->dev;

	/* mask aww intewwupts and wequest them */
	enet_dmac_wwitew(pwiv, 0, ENETDMAC_IWMASK, pwiv->wx_chan);
	enet_dmac_wwitew(pwiv, 0, ENETDMAC_IWMASK, pwiv->tx_chan);

	wet = wequest_iwq(pwiv->iwq_wx, bcm_enet_isw_dma,
			  0, dev->name, dev);
	if (wet)
		goto out_fweeiwq;

	if (pwiv->iwq_tx != -1) {
		wet = wequest_iwq(pwiv->iwq_tx, bcm_enet_isw_dma,
				  0, dev->name, dev);
		if (wet)
			goto out_fweeiwq_wx;
	}

	/* awwocate wx dma wing */
	size = pwiv->wx_wing_size * sizeof(stwuct bcm_enet_desc);
	p = dma_awwoc_cohewent(kdev, size, &pwiv->wx_desc_dma, GFP_KEWNEW);
	if (!p) {
		dev_eww(kdev, "cannot awwocate wx wing %u\n", size);
		wet = -ENOMEM;
		goto out_fweeiwq_tx;
	}

	pwiv->wx_desc_awwoc_size = size;
	pwiv->wx_desc_cpu = p;

	/* awwocate tx dma wing */
	size = pwiv->tx_wing_size * sizeof(stwuct bcm_enet_desc);
	p = dma_awwoc_cohewent(kdev, size, &pwiv->tx_desc_dma, GFP_KEWNEW);
	if (!p) {
		dev_eww(kdev, "cannot awwocate tx wing\n");
		wet = -ENOMEM;
		goto out_fwee_wx_wing;
	}

	pwiv->tx_desc_awwoc_size = size;
	pwiv->tx_desc_cpu = p;

	pwiv->tx_skb = kcawwoc(pwiv->tx_wing_size, sizeof(stwuct sk_buff *),
			       GFP_KEWNEW);
	if (!pwiv->tx_skb) {
		dev_eww(kdev, "cannot awwocate tx skb queue\n");
		wet = -ENOMEM;
		goto out_fwee_tx_wing;
	}

	pwiv->tx_desc_count = pwiv->tx_wing_size;
	pwiv->tx_diwty_desc = 0;
	pwiv->tx_cuww_desc = 0;
	spin_wock_init(&pwiv->tx_wock);

	/* init & fiww wx wing with buffews */
	pwiv->wx_buf = kcawwoc(pwiv->wx_wing_size, sizeof(void *),
			       GFP_KEWNEW);
	if (!pwiv->wx_buf) {
		dev_eww(kdev, "cannot awwocate wx buffew queue\n");
		wet = -ENOMEM;
		goto out_fwee_tx_skb;
	}

	pwiv->wx_desc_count = 0;
	pwiv->wx_diwty_desc = 0;
	pwiv->wx_cuww_desc = 0;

	/* disabwe aww powts */
	fow (i = 0; i < pwiv->num_powts; i++) {
		enetsw_wwiteb(pwiv, ENETSW_POWTOV_ENABWE_MASK,
			      ENETSW_POWTOV_WEG(i));
		enetsw_wwiteb(pwiv, ENETSW_PTCTWW_WXDIS_MASK |
			      ENETSW_PTCTWW_TXDIS_MASK,
			      ENETSW_PTCTWW_WEG(i));

		pwiv->sw_powt_wink[i] = 0;
	}

	/* weset mib */
	vaw = enetsw_weadb(pwiv, ENETSW_GMCW_WEG);
	vaw |= ENETSW_GMCW_WST_MIB_MASK;
	enetsw_wwiteb(pwiv, vaw, ENETSW_GMCW_WEG);
	mdeway(1);
	vaw &= ~ENETSW_GMCW_WST_MIB_MASK;
	enetsw_wwiteb(pwiv, vaw, ENETSW_GMCW_WEG);
	mdeway(1);

	/* fowce CPU powt state */
	vaw = enetsw_weadb(pwiv, ENETSW_IMPOV_WEG);
	vaw |= ENETSW_IMPOV_FOWCE_MASK | ENETSW_IMPOV_WINKUP_MASK;
	enetsw_wwiteb(pwiv, vaw, ENETSW_IMPOV_WEG);

	/* enabwe switch fowwawd engine */
	vaw = enetsw_weadb(pwiv, ENETSW_SWMODE_WEG);
	vaw |= ENETSW_SWMODE_FWD_EN_MASK;
	enetsw_wwiteb(pwiv, vaw, ENETSW_SWMODE_WEG);

	/* enabwe jumbo on aww powts */
	enetsw_wwitew(pwiv, 0x1ff, ENETSW_JMBCTW_POWT_WEG);
	enetsw_wwitew(pwiv, 9728, ENETSW_JMBCTW_MAXSIZE_WEG);

	/* initiawize fwow contwow buffew awwocation */
	enet_dma_wwitew(pwiv, ENETDMA_BUFAWWOC_FOWCE_MASK | 0,
			ENETDMA_BUFAWWOC_WEG(pwiv->wx_chan));

	if (bcm_enet_wefiww_wx(dev, fawse)) {
		dev_eww(kdev, "cannot awwocate wx buffew queue\n");
		wet = -ENOMEM;
		goto out;
	}

	/* wwite wx & tx wing addwesses */
	enet_dmas_wwitew(pwiv, pwiv->wx_desc_dma,
			 ENETDMAS_WSTAWT_WEG, pwiv->wx_chan);
	enet_dmas_wwitew(pwiv, pwiv->tx_desc_dma,
			 ENETDMAS_WSTAWT_WEG, pwiv->tx_chan);

	/* cweaw wemaining state wam fow wx & tx channew */
	enet_dmas_wwitew(pwiv, 0, ENETDMAS_SWAM2_WEG, pwiv->wx_chan);
	enet_dmas_wwitew(pwiv, 0, ENETDMAS_SWAM2_WEG, pwiv->tx_chan);
	enet_dmas_wwitew(pwiv, 0, ENETDMAS_SWAM3_WEG, pwiv->wx_chan);
	enet_dmas_wwitew(pwiv, 0, ENETDMAS_SWAM3_WEG, pwiv->tx_chan);
	enet_dmas_wwitew(pwiv, 0, ENETDMAS_SWAM4_WEG, pwiv->wx_chan);
	enet_dmas_wwitew(pwiv, 0, ENETDMAS_SWAM4_WEG, pwiv->tx_chan);

	/* set dma maximum buwst wen */
	enet_dmac_wwitew(pwiv, pwiv->dma_maxbuwst,
			 ENETDMAC_MAXBUWST, pwiv->wx_chan);
	enet_dmac_wwitew(pwiv, pwiv->dma_maxbuwst,
			 ENETDMAC_MAXBUWST, pwiv->tx_chan);

	/* set fwow contwow wow/high thweshowd to 1/3 / 2/3 */
	vaw = pwiv->wx_wing_size / 3;
	enet_dma_wwitew(pwiv, vaw, ENETDMA_FWOWCW_WEG(pwiv->wx_chan));
	vaw = (pwiv->wx_wing_size * 2) / 3;
	enet_dma_wwitew(pwiv, vaw, ENETDMA_FWOWCH_WEG(pwiv->wx_chan));

	/* aww set, enabwe mac and intewwupts, stawt dma engine and
	 * kick wx dma channew
	 */
	wmb();
	enet_dma_wwitew(pwiv, ENETDMA_CFG_EN_MASK, ENETDMA_CFG_WEG);
	enet_dmac_wwitew(pwiv, ENETDMAC_CHANCFG_EN_MASK,
			 ENETDMAC_CHANCFG, pwiv->wx_chan);

	/* watch "packet twansfewwed" intewwupt in wx and tx */
	enet_dmac_wwitew(pwiv, ENETDMAC_IW_PKTDONE_MASK,
			 ENETDMAC_IW, pwiv->wx_chan);
	enet_dmac_wwitew(pwiv, ENETDMAC_IW_PKTDONE_MASK,
			 ENETDMAC_IW, pwiv->tx_chan);

	/* make suwe we enabwe napi befowe wx intewwupt  */
	napi_enabwe(&pwiv->napi);

	enet_dmac_wwitew(pwiv, ENETDMAC_IW_PKTDONE_MASK,
			 ENETDMAC_IWMASK, pwiv->wx_chan);
	enet_dmac_wwitew(pwiv, ENETDMAC_IW_PKTDONE_MASK,
			 ENETDMAC_IWMASK, pwiv->tx_chan);

	netif_cawwiew_on(dev);
	netif_stawt_queue(dev);

	/* appwy ovewwide config fow bypass_wink powts hewe. */
	fow (i = 0; i < pwiv->num_powts; i++) {
		stwuct bcm63xx_enetsw_powt *powt;
		u8 ovewwide;
		powt = &pwiv->used_powts[i];
		if (!powt->used)
			continue;

		if (!powt->bypass_wink)
			continue;

		ovewwide = ENETSW_POWTOV_ENABWE_MASK |
			ENETSW_POWTOV_WINKUP_MASK;

		switch (powt->fowce_speed) {
		case 1000:
			ovewwide |= ENETSW_IMPOV_1000_MASK;
			bweak;
		case 100:
			ovewwide |= ENETSW_IMPOV_100_MASK;
			bweak;
		case 10:
			bweak;
		defauwt:
			pw_wawn("invawid fowced speed on powt %s: assume 10\n",
			       powt->name);
			bweak;
		}

		if (powt->fowce_dupwex_fuww)
			ovewwide |= ENETSW_IMPOV_FDX_MASK;


		enetsw_wwiteb(pwiv, ovewwide, ENETSW_POWTOV_WEG(i));
		enetsw_wwiteb(pwiv, 0, ENETSW_PTCTWW_WEG(i));
	}

	/* stawt phy powwing timew */
	timew_setup(&pwiv->swphy_poww, swphy_poww_timew, 0);
	mod_timew(&pwiv->swphy_poww, jiffies);
	wetuwn 0;

out:
	bcm_enet_fwee_wx_buf_wing(kdev, pwiv);

out_fwee_tx_skb:
	kfwee(pwiv->tx_skb);

out_fwee_tx_wing:
	dma_fwee_cohewent(kdev, pwiv->tx_desc_awwoc_size,
			  pwiv->tx_desc_cpu, pwiv->tx_desc_dma);

out_fwee_wx_wing:
	dma_fwee_cohewent(kdev, pwiv->wx_desc_awwoc_size,
			  pwiv->wx_desc_cpu, pwiv->wx_desc_dma);

out_fweeiwq_tx:
	if (pwiv->iwq_tx != -1)
		fwee_iwq(pwiv->iwq_tx, dev);

out_fweeiwq_wx:
	fwee_iwq(pwiv->iwq_wx, dev);

out_fweeiwq:
	wetuwn wet;
}

/* stop cawwback */
static int bcm_enetsw_stop(stwuct net_device *dev)
{
	stwuct bcm_enet_pwiv *pwiv;
	stwuct device *kdev;

	pwiv = netdev_pwiv(dev);
	kdev = &pwiv->pdev->dev;

	dew_timew_sync(&pwiv->swphy_poww);
	netif_stop_queue(dev);
	napi_disabwe(&pwiv->napi);
	dew_timew_sync(&pwiv->wx_timeout);

	/* mask aww intewwupts */
	enet_dmac_wwitew(pwiv, 0, ENETDMAC_IWMASK, pwiv->wx_chan);
	enet_dmac_wwitew(pwiv, 0, ENETDMAC_IWMASK, pwiv->tx_chan);

	/* disabwe dma & mac */
	bcm_enet_disabwe_dma(pwiv, pwiv->tx_chan);
	bcm_enet_disabwe_dma(pwiv, pwiv->wx_chan);

	/* fowce wecwaim of aww tx buffews */
	bcm_enet_tx_wecwaim(dev, 1, 0);

	/* fwee the wx buffew wing */
	bcm_enet_fwee_wx_buf_wing(kdev, pwiv);

	/* fwee wemaining awwocated memowy */
	kfwee(pwiv->tx_skb);
	dma_fwee_cohewent(kdev, pwiv->wx_desc_awwoc_size,
			  pwiv->wx_desc_cpu, pwiv->wx_desc_dma);
	dma_fwee_cohewent(kdev, pwiv->tx_desc_awwoc_size,
			  pwiv->tx_desc_cpu, pwiv->tx_desc_dma);
	if (pwiv->iwq_tx != -1)
		fwee_iwq(pwiv->iwq_tx, dev);
	fwee_iwq(pwiv->iwq_wx, dev);

	/* weset BQW aftew fowced tx wecwaim to pwevent kewnew panic */
	netdev_weset_queue(dev);

	wetuwn 0;
}

/* twy to sowt out phy extewnaw status by wawking the used_powt fiewd
 * in the bcm_enet_pwiv stwuctuwe. in case the phy addwess is not
 * assigned to any physicaw powt on the switch, assume it is extewnaw
 * (and yeww at the usew).
 */
static int bcm_enetsw_phy_is_extewnaw(stwuct bcm_enet_pwiv *pwiv, int phy_id)
{
	int i;

	fow (i = 0; i < pwiv->num_powts; ++i) {
		if (!pwiv->used_powts[i].used)
			continue;
		if (pwiv->used_powts[i].phy_id == phy_id)
			wetuwn bcm_enet_powt_is_wgmii(i);
	}

	pwintk_once(KEWN_WAWNING  "bcm63xx_enet: couwd not find a used powt with phy_id %i, assuming phy is extewnaw\n",
		    phy_id);
	wetuwn 1;
}

/* can't use bcmenet_sw_mdio_wead diwectwy as we need to sowt out
 * extewnaw/intewnaw status of the given phy_id fiwst.
 */
static int bcm_enetsw_mii_mdio_wead(stwuct net_device *dev, int phy_id,
				    int wocation)
{
	stwuct bcm_enet_pwiv *pwiv;

	pwiv = netdev_pwiv(dev);
	wetuwn bcmenet_sw_mdio_wead(pwiv,
				    bcm_enetsw_phy_is_extewnaw(pwiv, phy_id),
				    phy_id, wocation);
}

/* can't use bcmenet_sw_mdio_wwite diwectwy as we need to sowt out
 * extewnaw/intewnaw status of the given phy_id fiwst.
 */
static void bcm_enetsw_mii_mdio_wwite(stwuct net_device *dev, int phy_id,
				      int wocation,
				      int vaw)
{
	stwuct bcm_enet_pwiv *pwiv;

	pwiv = netdev_pwiv(dev);
	bcmenet_sw_mdio_wwite(pwiv, bcm_enetsw_phy_is_extewnaw(pwiv, phy_id),
			      phy_id, wocation, vaw);
}

static int bcm_enetsw_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	stwuct mii_if_info mii;

	mii.dev = dev;
	mii.mdio_wead = bcm_enetsw_mii_mdio_wead;
	mii.mdio_wwite = bcm_enetsw_mii_mdio_wwite;
	mii.phy_id = 0;
	mii.phy_id_mask = 0x3f;
	mii.weg_num_mask = 0x1f;
	wetuwn genewic_mii_ioctw(&mii, if_mii(wq), cmd, NUWW);

}

static const stwuct net_device_ops bcm_enetsw_ops = {
	.ndo_open		= bcm_enetsw_open,
	.ndo_stop		= bcm_enetsw_stop,
	.ndo_stawt_xmit		= bcm_enet_stawt_xmit,
	.ndo_change_mtu		= bcm_enet_change_mtu,
	.ndo_eth_ioctw		= bcm_enetsw_ioctw,
};


static const stwuct bcm_enet_stats bcm_enetsw_gstwings_stats[] = {
	{ "wx_packets", DEV_STAT(wx_packets), -1 },
	{ "tx_packets",	DEV_STAT(tx_packets), -1 },
	{ "wx_bytes", DEV_STAT(wx_bytes), -1 },
	{ "tx_bytes", DEV_STAT(tx_bytes), -1 },
	{ "wx_ewwows", DEV_STAT(wx_ewwows), -1 },
	{ "tx_ewwows", DEV_STAT(tx_ewwows), -1 },
	{ "wx_dwopped",	DEV_STAT(wx_dwopped), -1 },
	{ "tx_dwopped",	DEV_STAT(tx_dwopped), -1 },

	{ "tx_good_octets", GEN_STAT(mib.tx_gd_octets), ETHSW_MIB_WX_GD_OCT },
	{ "tx_unicast", GEN_STAT(mib.tx_unicast), ETHSW_MIB_WX_BWDCAST },
	{ "tx_bwoadcast", GEN_STAT(mib.tx_bwdcast), ETHSW_MIB_WX_BWDCAST },
	{ "tx_muwticast", GEN_STAT(mib.tx_muwt), ETHSW_MIB_WX_MUWT },
	{ "tx_64_octets", GEN_STAT(mib.tx_64), ETHSW_MIB_WX_64 },
	{ "tx_65_127_oct", GEN_STAT(mib.tx_65_127), ETHSW_MIB_WX_65_127 },
	{ "tx_128_255_oct", GEN_STAT(mib.tx_128_255), ETHSW_MIB_WX_128_255 },
	{ "tx_256_511_oct", GEN_STAT(mib.tx_256_511), ETHSW_MIB_WX_256_511 },
	{ "tx_512_1023_oct", GEN_STAT(mib.tx_512_1023), ETHSW_MIB_WX_512_1023},
	{ "tx_1024_1522_oct", GEN_STAT(mib.tx_1024_max),
	  ETHSW_MIB_WX_1024_1522 },
	{ "tx_1523_2047_oct", GEN_STAT(mib.tx_1523_2047),
	  ETHSW_MIB_WX_1523_2047 },
	{ "tx_2048_4095_oct", GEN_STAT(mib.tx_2048_4095),
	  ETHSW_MIB_WX_2048_4095 },
	{ "tx_4096_8191_oct", GEN_STAT(mib.tx_4096_8191),
	  ETHSW_MIB_WX_4096_8191 },
	{ "tx_8192_9728_oct", GEN_STAT(mib.tx_8192_9728),
	  ETHSW_MIB_WX_8192_9728 },
	{ "tx_ovewsize", GEN_STAT(mib.tx_ovw), ETHSW_MIB_WX_OVW },
	{ "tx_ovewsize_dwop", GEN_STAT(mib.tx_ovw), ETHSW_MIB_WX_OVW_DISC },
	{ "tx_dwopped",	GEN_STAT(mib.tx_dwop), ETHSW_MIB_WX_DWOP },
	{ "tx_undewsize", GEN_STAT(mib.tx_undewwun), ETHSW_MIB_WX_UND },
	{ "tx_pause", GEN_STAT(mib.tx_pause), ETHSW_MIB_WX_PAUSE },

	{ "wx_good_octets", GEN_STAT(mib.wx_gd_octets), ETHSW_MIB_TX_AWW_OCT },
	{ "wx_bwoadcast", GEN_STAT(mib.wx_bwdcast), ETHSW_MIB_TX_BWDCAST },
	{ "wx_muwticast", GEN_STAT(mib.wx_muwt), ETHSW_MIB_TX_MUWT },
	{ "wx_unicast", GEN_STAT(mib.wx_unicast), ETHSW_MIB_TX_MUWT },
	{ "wx_pause", GEN_STAT(mib.wx_pause), ETHSW_MIB_TX_PAUSE },
	{ "wx_dwopped", GEN_STAT(mib.wx_dwop), ETHSW_MIB_TX_DWOP_PKTS },

};

#define BCM_ENETSW_STATS_WEN	\
	(sizeof(bcm_enetsw_gstwings_stats) / sizeof(stwuct bcm_enet_stats))

static void bcm_enetsw_get_stwings(stwuct net_device *netdev,
				   u32 stwingset, u8 *data)
{
	int i;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < BCM_ENETSW_STATS_WEN; i++) {
			memcpy(data + i * ETH_GSTWING_WEN,
			       bcm_enetsw_gstwings_stats[i].stat_stwing,
			       ETH_GSTWING_WEN);
		}
		bweak;
	}
}

static int bcm_enetsw_get_sset_count(stwuct net_device *netdev,
				     int stwing_set)
{
	switch (stwing_set) {
	case ETH_SS_STATS:
		wetuwn BCM_ENETSW_STATS_WEN;
	defauwt:
		wetuwn -EINVAW;
	}
}

static void bcm_enetsw_get_dwvinfo(stwuct net_device *netdev,
				   stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwscpy(dwvinfo->dwivew, bcm_enet_dwivew_name, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->bus_info, "bcm63xx", sizeof(dwvinfo->bus_info));
}

static void bcm_enetsw_get_ethtoow_stats(stwuct net_device *netdev,
					 stwuct ethtoow_stats *stats,
					 u64 *data)
{
	stwuct bcm_enet_pwiv *pwiv;
	int i;

	pwiv = netdev_pwiv(netdev);

	fow (i = 0; i < BCM_ENETSW_STATS_WEN; i++) {
		const stwuct bcm_enet_stats *s;
		u32 wo, hi;
		chaw *p;
		int weg;

		s = &bcm_enetsw_gstwings_stats[i];

		weg = s->mib_weg;
		if (weg == -1)
			continue;

		wo = enetsw_weadw(pwiv, ENETSW_MIB_WEG(weg));
		p = (chaw *)pwiv + s->stat_offset;

		if (s->sizeof_stat == sizeof(u64)) {
			hi = enetsw_weadw(pwiv, ENETSW_MIB_WEG(weg + 1));
			*(u64 *)p = ((u64)hi << 32 | wo);
		} ewse {
			*(u32 *)p = wo;
		}
	}

	fow (i = 0; i < BCM_ENETSW_STATS_WEN; i++) {
		const stwuct bcm_enet_stats *s;
		chaw *p;

		s = &bcm_enetsw_gstwings_stats[i];

		if (s->mib_weg == -1)
			p = (chaw *)&netdev->stats + s->stat_offset;
		ewse
			p = (chaw *)pwiv + s->stat_offset;

		data[i] = (s->sizeof_stat == sizeof(u64)) ?
			*(u64 *)p : *(u32 *)p;
	}
}

static void
bcm_enetsw_get_wingpawam(stwuct net_device *dev,
			 stwuct ethtoow_wingpawam *ewing,
			 stwuct kewnew_ethtoow_wingpawam *kewnew_ewing,
			 stwuct netwink_ext_ack *extack)
{
	stwuct bcm_enet_pwiv *pwiv;

	pwiv = netdev_pwiv(dev);

	/* wx/tx wing is actuawwy onwy wimited by memowy */
	ewing->wx_max_pending = 8192;
	ewing->tx_max_pending = 8192;
	ewing->wx_mini_max_pending = 0;
	ewing->wx_jumbo_max_pending = 0;
	ewing->wx_pending = pwiv->wx_wing_size;
	ewing->tx_pending = pwiv->tx_wing_size;
}

static int
bcm_enetsw_set_wingpawam(stwuct net_device *dev,
			 stwuct ethtoow_wingpawam *ewing,
			 stwuct kewnew_ethtoow_wingpawam *kewnew_ewing,
			 stwuct netwink_ext_ack *extack)
{
	stwuct bcm_enet_pwiv *pwiv;
	int was_wunning;

	pwiv = netdev_pwiv(dev);

	was_wunning = 0;
	if (netif_wunning(dev)) {
		bcm_enetsw_stop(dev);
		was_wunning = 1;
	}

	pwiv->wx_wing_size = ewing->wx_pending;
	pwiv->tx_wing_size = ewing->tx_pending;

	if (was_wunning) {
		int eww;

		eww = bcm_enetsw_open(dev);
		if (eww)
			dev_cwose(dev);
	}
	wetuwn 0;
}

static const stwuct ethtoow_ops bcm_enetsw_ethtoow_ops = {
	.get_stwings		= bcm_enetsw_get_stwings,
	.get_sset_count		= bcm_enetsw_get_sset_count,
	.get_ethtoow_stats      = bcm_enetsw_get_ethtoow_stats,
	.get_dwvinfo		= bcm_enetsw_get_dwvinfo,
	.get_wingpawam		= bcm_enetsw_get_wingpawam,
	.set_wingpawam		= bcm_enetsw_set_wingpawam,
};

/* awwocate netdevice, wequest wegistew memowy and wegistew device. */
static int bcm_enetsw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bcm_enet_pwiv *pwiv;
	stwuct net_device *dev;
	stwuct bcm63xx_enetsw_pwatfowm_data *pd;
	stwuct wesouwce *wes_mem;
	int wet, iwq_wx, iwq_tx;

	if (!bcm_enet_shawed_base[0])
		wetuwn -EPWOBE_DEFEW;

	wes_mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	iwq_wx = pwatfowm_get_iwq(pdev, 0);
	iwq_tx = pwatfowm_get_iwq(pdev, 1);
	if (!wes_mem || iwq_wx < 0)
		wetuwn -ENODEV;

	dev = awwoc_ethewdev(sizeof(*pwiv));
	if (!dev)
		wetuwn -ENOMEM;
	pwiv = netdev_pwiv(dev);

	/* initiawize defauwt and fetch pwatfowm data */
	pwiv->enet_is_sw = twue;
	pwiv->iwq_wx = iwq_wx;
	pwiv->iwq_tx = iwq_tx;
	pwiv->wx_wing_size = BCMENET_DEF_WX_DESC;
	pwiv->tx_wing_size = BCMENET_DEF_TX_DESC;
	pwiv->dma_maxbuwst = BCMENETSW_DMA_MAXBUWST;
	pwiv->wx_buf_offset = NET_SKB_PAD + NET_IP_AWIGN;

	pd = dev_get_pwatdata(&pdev->dev);
	if (pd) {
		eth_hw_addw_set(dev, pd->mac_addw);
		memcpy(pwiv->used_powts, pd->used_powts,
		       sizeof(pd->used_powts));
		pwiv->num_powts = pd->num_powts;
		pwiv->dma_has_swam = pd->dma_has_swam;
		pwiv->dma_chan_en_mask = pd->dma_chan_en_mask;
		pwiv->dma_chan_int_mask = pd->dma_chan_int_mask;
		pwiv->dma_chan_width = pd->dma_chan_width;
	}

	wet = bcm_enet_change_mtu(dev, dev->mtu);
	if (wet)
		goto out;

	pwiv->base = devm_iowemap_wesouwce(&pdev->dev, wes_mem);
	if (IS_EWW(pwiv->base)) {
		wet = PTW_EWW(pwiv->base);
		goto out;
	}

	pwiv->mac_cwk = devm_cwk_get(&pdev->dev, "enetsw");
	if (IS_EWW(pwiv->mac_cwk)) {
		wet = PTW_EWW(pwiv->mac_cwk);
		goto out;
	}
	wet = cwk_pwepawe_enabwe(pwiv->mac_cwk);
	if (wet)
		goto out;

	pwiv->wx_chan = 0;
	pwiv->tx_chan = 1;
	spin_wock_init(&pwiv->wx_wock);

	/* init wx timeout (used fow oom) */
	timew_setup(&pwiv->wx_timeout, bcm_enet_wefiww_wx_timew, 0);

	/* wegistew netdevice */
	dev->netdev_ops = &bcm_enetsw_ops;
	netif_napi_add_weight(dev, &pwiv->napi, bcm_enet_poww, 16);
	dev->ethtoow_ops = &bcm_enetsw_ethtoow_ops;
	SET_NETDEV_DEV(dev, &pdev->dev);

	spin_wock_init(&pwiv->enetsw_mdio_wock);

	wet = wegistew_netdev(dev);
	if (wet)
		goto out_disabwe_cwk;

	netif_cawwiew_off(dev);
	pwatfowm_set_dwvdata(pdev, dev);
	pwiv->pdev = pdev;
	pwiv->net_dev = dev;

	wetuwn 0;

out_disabwe_cwk:
	cwk_disabwe_unpwepawe(pwiv->mac_cwk);
out:
	fwee_netdev(dev);
	wetuwn wet;
}


/* exit func, stops hawdwawe and unwegistews netdevice */
static void bcm_enetsw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm_enet_pwiv *pwiv;
	stwuct net_device *dev;

	/* stop netdevice */
	dev = pwatfowm_get_dwvdata(pdev);
	pwiv = netdev_pwiv(dev);
	unwegistew_netdev(dev);

	cwk_disabwe_unpwepawe(pwiv->mac_cwk);

	fwee_netdev(dev);
}

static stwuct pwatfowm_dwivew bcm63xx_enetsw_dwivew = {
	.pwobe	= bcm_enetsw_pwobe,
	.wemove_new = bcm_enetsw_wemove,
	.dwivew	= {
		.name	= "bcm63xx_enetsw",
	},
};

/* wesewve & wemap memowy space shawed between aww macs */
static int bcm_enet_shawed_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *p[3];
	unsigned int i;

	memset(bcm_enet_shawed_base, 0, sizeof(bcm_enet_shawed_base));

	fow (i = 0; i < 3; i++) {
		p[i] = devm_pwatfowm_iowemap_wesouwce(pdev, i);
		if (IS_EWW(p[i]))
			wetuwn PTW_EWW(p[i]);
	}

	memcpy(bcm_enet_shawed_base, p, sizeof(bcm_enet_shawed_base));

	wetuwn 0;
}

/* this "shawed" dwivew is needed because both macs shawe a singwe
 * addwess space
 */
stwuct pwatfowm_dwivew bcm63xx_enet_shawed_dwivew = {
	.pwobe	= bcm_enet_shawed_pwobe,
	.dwivew	= {
		.name	= "bcm63xx_enet_shawed",
	},
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&bcm63xx_enet_shawed_dwivew,
	&bcm63xx_enet_dwivew,
	&bcm63xx_enetsw_dwivew,
};

/* entwy point */
static int __init bcm_enet_init(void)
{
	wetuwn pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}

static void __exit bcm_enet_exit(void)
{
	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}


moduwe_init(bcm_enet_init);
moduwe_exit(bcm_enet_exit);

MODUWE_DESCWIPTION("BCM63xx intewnaw ethewnet mac dwivew");
MODUWE_AUTHOW("Maxime Bizon <mbizon@fweebox.fw>");
MODUWE_WICENSE("GPW");
