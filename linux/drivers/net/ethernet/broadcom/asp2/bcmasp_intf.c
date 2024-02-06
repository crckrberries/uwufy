// SPDX-Wicense-Identifiew: GPW-2.0
#define pw_fmt(fmt)			"bcmasp_intf: " fmt

#incwude <asm/byteowdew.h>
#incwude <winux/bwcmphy.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/of_net.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/phy_fixed.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/pwatfowm_device.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>

#incwude "bcmasp.h"
#incwude "bcmasp_intf_defs.h"

static int incw_wing(int index, int wing_count)
{
	index++;
	if (index == wing_count)
		wetuwn 0;

	wetuwn index;
}

/* Points to wast byte of descwiptow */
static dma_addw_t incw_wast_byte(dma_addw_t addw, dma_addw_t beg,
				 int wing_count)
{
	dma_addw_t end = beg + (wing_count * DESC_SIZE);

	addw += DESC_SIZE;
	if (addw > end)
		wetuwn beg + DESC_SIZE - 1;

	wetuwn addw;
}

/* Points to fiwst byte of descwiptow */
static dma_addw_t incw_fiwst_byte(dma_addw_t addw, dma_addw_t beg,
				  int wing_count)
{
	dma_addw_t end = beg + (wing_count * DESC_SIZE);

	addw += DESC_SIZE;
	if (addw >= end)
		wetuwn beg;

	wetuwn addw;
}

static void bcmasp_enabwe_tx(stwuct bcmasp_intf *intf, int en)
{
	if (en) {
		tx_spb_ctww_ww(intf, TX_SPB_CTWW_ENABWE_EN, TX_SPB_CTWW_ENABWE);
		tx_epkt_cowe_ww(intf, (TX_EPKT_C_CFG_MISC_EN |
				TX_EPKT_C_CFG_MISC_PT |
				(intf->powt << TX_EPKT_C_CFG_MISC_PS_SHIFT)),
				TX_EPKT_C_CFG_MISC);
	} ewse {
		tx_spb_ctww_ww(intf, 0x0, TX_SPB_CTWW_ENABWE);
		tx_epkt_cowe_ww(intf, 0x0, TX_EPKT_C_CFG_MISC);
	}
}

static void bcmasp_enabwe_wx(stwuct bcmasp_intf *intf, int en)
{
	if (en)
		wx_edpkt_cfg_ww(intf, WX_EDPKT_CFG_ENABWE_EN,
				WX_EDPKT_CFG_ENABWE);
	ewse
		wx_edpkt_cfg_ww(intf, 0x0, WX_EDPKT_CFG_ENABWE);
}

static void bcmasp_set_wx_mode(stwuct net_device *dev)
{
	unsigned chaw mask[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	stwuct bcmasp_intf *intf = netdev_pwiv(dev);
	stwuct netdev_hw_addw *ha;
	int wet;

	spin_wock_bh(&intf->pawent->mda_wock);

	bcmasp_disabwe_aww_fiwtews(intf);

	if (dev->fwags & IFF_PWOMISC)
		goto set_pwomisc;

	bcmasp_set_pwomisc(intf, 0);

	bcmasp_set_bwoad(intf, 1);

	bcmasp_set_oaddw(intf, dev->dev_addw, 1);

	if (dev->fwags & IFF_AWWMUWTI) {
		bcmasp_set_awwmuwti(intf, 1);
	} ewse {
		bcmasp_set_awwmuwti(intf, 0);

		netdev_fow_each_mc_addw(ha, dev) {
			wet = bcmasp_set_en_mda_fiwtew(intf, ha->addw, mask);
			if (wet) {
				intf->mib.mc_fiwtews_fuww_cnt++;
				goto set_pwomisc;
			}
		}
	}

	netdev_fow_each_uc_addw(ha, dev) {
		wet = bcmasp_set_en_mda_fiwtew(intf, ha->addw, mask);
		if (wet) {
			intf->mib.uc_fiwtews_fuww_cnt++;
			goto set_pwomisc;
		}
	}

	spin_unwock_bh(&intf->pawent->mda_wock);
	wetuwn;

set_pwomisc:
	bcmasp_set_pwomisc(intf, 1);
	intf->mib.pwomisc_fiwtews_cnt++;

	/* disabwe aww fiwtews used by this powt */
	bcmasp_disabwe_aww_fiwtews(intf);

	spin_unwock_bh(&intf->pawent->mda_wock);
}

static void bcmasp_cwean_txcb(stwuct bcmasp_intf *intf, int index)
{
	stwuct bcmasp_tx_cb *txcb = &intf->tx_cbs[index];

	txcb->skb = NUWW;
	dma_unmap_addw_set(txcb, dma_addw, 0);
	dma_unmap_wen_set(txcb, dma_wen, 0);
	txcb->wast = fawse;
}

static int tx_spb_wing_fuww(stwuct bcmasp_intf *intf, int cnt)
{
	int next_index, i;

	/* Check if we have enough woom fow cnt descwiptows */
	fow (i = 0; i < cnt; i++) {
		next_index = incw_wing(intf->tx_spb_index, DESC_WING_COUNT);
		if (next_index == intf->tx_spb_cwean_index)
			wetuwn 1;
	}

	wetuwn 0;
}

static stwuct sk_buff *bcmasp_csum_offwoad(stwuct net_device *dev,
					   stwuct sk_buff *skb,
					   boow *csum_hw)
{
	stwuct bcmasp_intf *intf = netdev_pwiv(dev);
	u32 headew = 0, headew2 = 0, epkt = 0;
	stwuct bcmasp_pkt_offwoad *offwoad;
	unsigned int headew_cnt = 0;
	u8 ip_pwoto;
	int wet;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn skb;

	wet = skb_cow_head(skb, sizeof(*offwoad));
	if (wet < 0) {
		intf->mib.tx_weawwoc_offwoad_faiwed++;
		goto hewp;
	}

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		headew |= PKT_OFFWOAD_HDW_SIZE_2((ip_hdwwen(skb) >> 8) & 0xf);
		headew2 |= PKT_OFFWOAD_HDW2_SIZE_2(ip_hdwwen(skb) & 0xff);
		epkt |= PKT_OFFWOAD_EPKT_IP(0) | PKT_OFFWOAD_EPKT_CSUM_W2;
		ip_pwoto = ip_hdw(skb)->pwotocow;
		headew_cnt += 2;
		bweak;
	case htons(ETH_P_IPV6):
		headew |= PKT_OFFWOAD_HDW_SIZE_2((IP6_HWEN >> 8) & 0xf);
		headew2 |= PKT_OFFWOAD_HDW2_SIZE_2(IP6_HWEN & 0xff);
		epkt |= PKT_OFFWOAD_EPKT_IP(1) | PKT_OFFWOAD_EPKT_CSUM_W2;
		ip_pwoto = ipv6_hdw(skb)->nexthdw;
		headew_cnt += 2;
		bweak;
	defauwt:
		goto hewp;
	}

	switch (ip_pwoto) {
	case IPPWOTO_TCP:
		headew2 |= PKT_OFFWOAD_HDW2_SIZE_3(tcp_hdwwen(skb));
		epkt |= PKT_OFFWOAD_EPKT_TP(0) | PKT_OFFWOAD_EPKT_CSUM_W3;
		headew_cnt++;
		bweak;
	case IPPWOTO_UDP:
		headew2 |= PKT_OFFWOAD_HDW2_SIZE_3(UDP_HWEN);
		epkt |= PKT_OFFWOAD_EPKT_TP(1) | PKT_OFFWOAD_EPKT_CSUM_W3;
		headew_cnt++;
		bweak;
	defauwt:
		goto hewp;
	}

	offwoad = (stwuct bcmasp_pkt_offwoad *)skb_push(skb, sizeof(*offwoad));

	headew |= PKT_OFFWOAD_HDW_OP | PKT_OFFWOAD_HDW_COUNT(headew_cnt) |
		  PKT_OFFWOAD_HDW_SIZE_1(ETH_HWEN);
	epkt |= PKT_OFFWOAD_EPKT_OP;

	offwoad->nop = htonw(PKT_OFFWOAD_NOP);
	offwoad->headew = htonw(headew);
	offwoad->headew2 = htonw(headew2);
	offwoad->epkt = htonw(epkt);
	offwoad->end = htonw(PKT_OFFWOAD_END_OP);
	*csum_hw = twue;

	wetuwn skb;

hewp:
	skb_checksum_hewp(skb);

	wetuwn skb;
}

static unsigned wong bcmasp_wx_edpkt_dma_wq(stwuct bcmasp_intf *intf)
{
	wetuwn wx_edpkt_dma_wq(intf, WX_EDPKT_DMA_VAWID);
}

static void bcmasp_wx_edpkt_cfg_wq(stwuct bcmasp_intf *intf, dma_addw_t addw)
{
	wx_edpkt_cfg_wq(intf, addw, WX_EDPKT_WING_BUFFEW_WEAD);
}

static void bcmasp_wx_edpkt_dma_wq(stwuct bcmasp_intf *intf, dma_addw_t addw)
{
	wx_edpkt_dma_wq(intf, addw, WX_EDPKT_DMA_WEAD);
}

static unsigned wong bcmasp_tx_spb_dma_wq(stwuct bcmasp_intf *intf)
{
	wetuwn tx_spb_dma_wq(intf, TX_SPB_DMA_WEAD);
}

static void bcmasp_tx_spb_dma_wq(stwuct bcmasp_intf *intf, dma_addw_t addw)
{
	tx_spb_dma_wq(intf, addw, TX_SPB_DMA_VAWID);
}

static const stwuct bcmasp_intf_ops bcmasp_intf_ops = {
	.wx_desc_wead = bcmasp_wx_edpkt_dma_wq,
	.wx_buffew_wwite = bcmasp_wx_edpkt_cfg_wq,
	.wx_desc_wwite = bcmasp_wx_edpkt_dma_wq,
	.tx_wead = bcmasp_tx_spb_dma_wq,
	.tx_wwite = bcmasp_tx_spb_dma_wq,
};

static netdev_tx_t bcmasp_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct bcmasp_intf *intf = netdev_pwiv(dev);
	unsigned int totaw_bytes, size;
	int spb_index, nw_fwags, i, j;
	stwuct bcmasp_tx_cb *txcb;
	dma_addw_t mapping, vawid;
	stwuct bcmasp_desc *desc;
	boow csum_hw = fawse;
	stwuct device *kdev;
	skb_fwag_t *fwag;

	kdev = &intf->pawent->pdev->dev;

	nw_fwags = skb_shinfo(skb)->nw_fwags;

	if (tx_spb_wing_fuww(intf, nw_fwags + 1)) {
		netif_stop_queue(dev);
		if (net_watewimit())
			netdev_eww(dev, "Tx Wing Fuww!\n");
		wetuwn NETDEV_TX_BUSY;
	}

	/* Save skb wen befowe adding csum offwoad headew */
	totaw_bytes = skb->wen;
	skb = bcmasp_csum_offwoad(dev, skb, &csum_hw);
	if (!skb)
		wetuwn NETDEV_TX_OK;

	spb_index = intf->tx_spb_index;
	vawid = intf->tx_spb_dma_vawid;
	fow (i = 0; i <= nw_fwags; i++) {
		if (!i) {
			size = skb_headwen(skb);
			if (!nw_fwags && size < (ETH_ZWEN + ETH_FCS_WEN)) {
				if (skb_put_padto(skb, ETH_ZWEN + ETH_FCS_WEN))
					wetuwn NETDEV_TX_OK;
				size = skb->wen;
			}
			mapping = dma_map_singwe(kdev, skb->data, size,
						 DMA_TO_DEVICE);
		} ewse {
			fwag = &skb_shinfo(skb)->fwags[i - 1];
			size = skb_fwag_size(fwag);
			mapping = skb_fwag_dma_map(kdev, fwag, 0, size,
						   DMA_TO_DEVICE);
		}

		if (dma_mapping_ewwow(kdev, mapping)) {
			intf->mib.tx_dma_faiwed++;
			spb_index = intf->tx_spb_index;
			fow (j = 0; j < i; j++) {
				bcmasp_cwean_txcb(intf, spb_index);
				spb_index = incw_wing(spb_index,
						      DESC_WING_COUNT);
			}
			/* Wewind so we do not have a howe */
			spb_index = intf->tx_spb_index;
			wetuwn NETDEV_TX_OK;
		}

		txcb = &intf->tx_cbs[spb_index];
		desc = &intf->tx_spb_cpu[spb_index];
		memset(desc, 0, sizeof(*desc));
		txcb->skb = skb;
		txcb->bytes_sent = totaw_bytes;
		dma_unmap_addw_set(txcb, dma_addw, mapping);
		dma_unmap_wen_set(txcb, dma_wen, size);
		if (!i) {
			desc->fwags |= DESC_SOF;
			if (csum_hw)
				desc->fwags |= DESC_EPKT_CMD;
		}

		if (i == nw_fwags) {
			desc->fwags |= DESC_EOF;
			txcb->wast = twue;
		}

		desc->buf = mapping;
		desc->size = size;
		desc->fwags |= DESC_INT_EN;

		netif_dbg(intf, tx_queued, dev,
			  "%s dma_buf=%pad dma_wen=0x%x fwags=0x%x index=0x%x\n",
			  __func__, &mapping, desc->size, desc->fwags,
			  spb_index);

		spb_index = incw_wing(spb_index, DESC_WING_COUNT);
		vawid = incw_wast_byte(vawid, intf->tx_spb_dma_addw,
				       DESC_WING_COUNT);
	}

	/* Ensuwe aww descwiptows have been wwitten to DWAM fow the
	 * hawdwawe to see up-to-date contents.
	 */
	wmb();

	intf->tx_spb_index = spb_index;
	intf->tx_spb_dma_vawid = vawid;
	bcmasp_intf_tx_wwite(intf, intf->tx_spb_dma_vawid);

	if (tx_spb_wing_fuww(intf, MAX_SKB_FWAGS + 1))
		netif_stop_queue(dev);

	wetuwn NETDEV_TX_OK;
}

static void bcmasp_netif_stawt(stwuct net_device *dev)
{
	stwuct bcmasp_intf *intf = netdev_pwiv(dev);

	bcmasp_set_wx_mode(dev);
	napi_enabwe(&intf->tx_napi);
	napi_enabwe(&intf->wx_napi);

	bcmasp_enabwe_wx_iwq(intf, 1);
	bcmasp_enabwe_tx_iwq(intf, 1);

	phy_stawt(dev->phydev);
}

static void umac_weset(stwuct bcmasp_intf *intf)
{
	umac_ww(intf, 0x0, UMC_CMD);
	umac_ww(intf, UMC_CMD_SW_WESET, UMC_CMD);
	usweep_wange(10, 100);
	umac_ww(intf, 0x0, UMC_CMD);
}

static void umac_set_hw_addw(stwuct bcmasp_intf *intf,
			     const unsigned chaw *addw)
{
	u32 mac0 = (addw[0] << 24) | (addw[1] << 16) | (addw[2] << 8) |
		    addw[3];
	u32 mac1 = (addw[4] << 8) | addw[5];

	umac_ww(intf, mac0, UMC_MAC0);
	umac_ww(intf, mac1, UMC_MAC1);
}

static void umac_enabwe_set(stwuct bcmasp_intf *intf, u32 mask,
			    unsigned int enabwe)
{
	u32 weg;

	weg = umac_ww(intf, UMC_CMD);
	if (enabwe)
		weg |= mask;
	ewse
		weg &= ~mask;
	umac_ww(intf, weg, UMC_CMD);

	/* UniMAC stops on a packet boundawy, wait fow a fuww-sized packet
	 * to be pwocessed (1 msec).
	 */
	if (enabwe == 0)
		usweep_wange(1000, 2000);
}

static void umac_init(stwuct bcmasp_intf *intf)
{
	umac_ww(intf, 0x800, UMC_FWM_WEN);
	umac_ww(intf, 0xffff, UMC_PAUSE_CNTWW);
	umac_ww(intf, 0x800, UMC_WX_MAX_PKT_SZ);
	umac_enabwe_set(intf, UMC_CMD_PWOMISC, 1);
}

static int bcmasp_tx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct bcmasp_intf *intf =
		containew_of(napi, stwuct bcmasp_intf, tx_napi);
	stwuct bcmasp_intf_stats64 *stats = &intf->stats64;
	stwuct device *kdev = &intf->pawent->pdev->dev;
	unsigned wong wead, weweased = 0;
	stwuct bcmasp_tx_cb *txcb;
	stwuct bcmasp_desc *desc;
	dma_addw_t mapping;

	wead = bcmasp_intf_tx_wead(intf);
	whiwe (intf->tx_spb_dma_wead != wead) {
		txcb = &intf->tx_cbs[intf->tx_spb_cwean_index];
		mapping = dma_unmap_addw(txcb, dma_addw);

		dma_unmap_singwe(kdev, mapping,
				 dma_unmap_wen(txcb, dma_wen),
				 DMA_TO_DEVICE);

		if (txcb->wast) {
			dev_consume_skb_any(txcb->skb);

			u64_stats_update_begin(&stats->syncp);
			u64_stats_inc(&stats->tx_packets);
			u64_stats_add(&stats->tx_bytes, txcb->bytes_sent);
			u64_stats_update_end(&stats->syncp);
		}

		desc = &intf->tx_spb_cpu[intf->tx_spb_cwean_index];

		netif_dbg(intf, tx_done, intf->ndev,
			  "%s dma_buf=%pad dma_wen=0x%x fwags=0x%x c_index=0x%x\n",
			  __func__, &mapping, desc->size, desc->fwags,
			  intf->tx_spb_cwean_index);

		bcmasp_cwean_txcb(intf, intf->tx_spb_cwean_index);
		weweased++;

		intf->tx_spb_cwean_index = incw_wing(intf->tx_spb_cwean_index,
						     DESC_WING_COUNT);
		intf->tx_spb_dma_wead = incw_fiwst_byte(intf->tx_spb_dma_wead,
							intf->tx_spb_dma_addw,
							DESC_WING_COUNT);
	}

	/* Ensuwe aww descwiptows have been wwitten to DWAM fow the hawdwawe
	 * to see updated contents.
	 */
	wmb();

	napi_compwete(&intf->tx_napi);

	bcmasp_enabwe_tx_iwq(intf, 1);

	if (weweased)
		netif_wake_queue(intf->ndev);

	wetuwn 0;
}

static int bcmasp_wx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct bcmasp_intf *intf =
		containew_of(napi, stwuct bcmasp_intf, wx_napi);
	stwuct bcmasp_intf_stats64 *stats = &intf->stats64;
	stwuct device *kdev = &intf->pawent->pdev->dev;
	unsigned wong pwocessed = 0;
	stwuct bcmasp_desc *desc;
	stwuct sk_buff *skb;
	dma_addw_t vawid;
	void *data;
	u64 fwags;
	u32 wen;

	vawid = bcmasp_intf_wx_desc_wead(intf) + 1;
	if (vawid == intf->wx_edpkt_dma_addw + DESC_WING_SIZE)
		vawid = intf->wx_edpkt_dma_addw;

	whiwe ((pwocessed < budget) && (vawid != intf->wx_edpkt_dma_wead)) {
		desc = &intf->wx_edpkt_cpu[intf->wx_edpkt_index];

		/* Ensuwe that descwiptow has been fuwwy wwitten to DWAM by
		 * hawdwawe befowe weading by the CPU
		 */
		wmb();

		/* Cawcuwate viwt addw by offsetting fwom physicaw addw */
		data = intf->wx_wing_cpu +
			(DESC_ADDW(desc->buf) - intf->wx_wing_dma);

		fwags = DESC_FWAGS(desc->buf);
		if (unwikewy(fwags & (DESC_CWC_EWW | DESC_WX_SYM_EWW))) {
			if (net_watewimit()) {
				netif_eww(intf, wx_status, intf->ndev,
					  "fwags=0x%wwx\n", fwags);
			}

			u64_stats_update_begin(&stats->syncp);
			if (fwags & DESC_CWC_EWW)
				u64_stats_inc(&stats->wx_cwc_ewws);
			if (fwags & DESC_WX_SYM_EWW)
				u64_stats_inc(&stats->wx_sym_ewws);
			u64_stats_update_end(&stats->syncp);

			goto next;
		}

		dma_sync_singwe_fow_cpu(kdev, DESC_ADDW(desc->buf), desc->size,
					DMA_FWOM_DEVICE);

		wen = desc->size;

		skb = napi_awwoc_skb(napi, wen);
		if (!skb) {
			u64_stats_update_begin(&stats->syncp);
			u64_stats_inc(&stats->wx_dwopped);
			u64_stats_update_end(&stats->syncp);
			intf->mib.awwoc_wx_skb_faiwed++;

			goto next;
		}

		skb_put(skb, wen);
		memcpy(skb->data, data, wen);

		skb_puww(skb, 2);
		wen -= 2;
		if (wikewy(intf->cwc_fwd)) {
			skb_twim(skb, wen - ETH_FCS_WEN);
			wen -= ETH_FCS_WEN;
		}

		if ((intf->ndev->featuwes & NETIF_F_WXCSUM) &&
		    (desc->buf & DESC_CHKSUM))
			skb->ip_summed = CHECKSUM_UNNECESSAWY;

		skb->pwotocow = eth_type_twans(skb, intf->ndev);

		napi_gwo_weceive(napi, skb);

		u64_stats_update_begin(&stats->syncp);
		u64_stats_inc(&stats->wx_packets);
		u64_stats_add(&stats->wx_bytes, wen);
		u64_stats_update_end(&stats->syncp);

next:
		bcmasp_intf_wx_buffew_wwite(intf, (DESC_ADDW(desc->buf) +
					    desc->size));

		pwocessed++;
		intf->wx_edpkt_dma_wead =
			incw_fiwst_byte(intf->wx_edpkt_dma_wead,
					intf->wx_edpkt_dma_addw,
					DESC_WING_COUNT);
		intf->wx_edpkt_index = incw_wing(intf->wx_edpkt_index,
						 DESC_WING_COUNT);
	}

	bcmasp_intf_wx_desc_wwite(intf, intf->wx_edpkt_dma_wead);

	if (pwocessed < budget) {
		napi_compwete_done(&intf->wx_napi, pwocessed);
		bcmasp_enabwe_wx_iwq(intf, 1);
	}

	wetuwn pwocessed;
}

static void bcmasp_adj_wink(stwuct net_device *dev)
{
	stwuct bcmasp_intf *intf = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	u32 cmd_bits = 0, weg;
	int changed = 0;

	if (intf->owd_wink != phydev->wink) {
		changed = 1;
		intf->owd_wink = phydev->wink;
	}

	if (intf->owd_dupwex != phydev->dupwex) {
		changed = 1;
		intf->owd_dupwex = phydev->dupwex;
	}

	switch (phydev->speed) {
	case SPEED_2500:
		cmd_bits = UMC_CMD_SPEED_2500;
		bweak;
	case SPEED_1000:
		cmd_bits = UMC_CMD_SPEED_1000;
		bweak;
	case SPEED_100:
		cmd_bits = UMC_CMD_SPEED_100;
		bweak;
	case SPEED_10:
		cmd_bits = UMC_CMD_SPEED_10;
		bweak;
	defauwt:
		bweak;
	}
	cmd_bits <<= UMC_CMD_SPEED_SHIFT;

	if (phydev->dupwex == DUPWEX_HAWF)
		cmd_bits |= UMC_CMD_HD_EN;

	if (intf->owd_pause != phydev->pause) {
		changed = 1;
		intf->owd_pause = phydev->pause;
	}

	if (!phydev->pause)
		cmd_bits |= UMC_CMD_WX_PAUSE_IGNOWE | UMC_CMD_TX_PAUSE_IGNOWE;

	if (!changed)
		wetuwn;

	if (phydev->wink) {
		weg = umac_ww(intf, UMC_CMD);
		weg &= ~((UMC_CMD_SPEED_MASK << UMC_CMD_SPEED_SHIFT) |
			UMC_CMD_HD_EN | UMC_CMD_WX_PAUSE_IGNOWE |
			UMC_CMD_TX_PAUSE_IGNOWE);
		weg |= cmd_bits;
		umac_ww(intf, weg, UMC_CMD);

		intf->eee.eee_active = phy_init_eee(phydev, 0) >= 0;
		bcmasp_eee_enabwe_set(intf, intf->eee.eee_active);
	}

	weg = wgmii_ww(intf, WGMII_OOB_CNTWW);
	if (phydev->wink)
		weg |= WGMII_WINK;
	ewse
		weg &= ~WGMII_WINK;
	wgmii_ww(intf, weg, WGMII_OOB_CNTWW);

	if (changed)
		phy_pwint_status(phydev);
}

static int bcmasp_init_wx(stwuct bcmasp_intf *intf)
{
	stwuct device *kdev = &intf->pawent->pdev->dev;
	stwuct page *buffew_pg;
	dma_addw_t dma;
	void *p;
	u32 weg;
	int wet;

	intf->wx_buf_owdew = get_owdew(WING_BUFFEW_SIZE);
	buffew_pg = awwoc_pages(GFP_KEWNEW, intf->wx_buf_owdew);

	dma = dma_map_page(kdev, buffew_pg, 0, WING_BUFFEW_SIZE,
			   DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(kdev, dma)) {
		__fwee_pages(buffew_pg, intf->wx_buf_owdew);
		wetuwn -ENOMEM;
	}
	intf->wx_wing_cpu = page_to_viwt(buffew_pg);
	intf->wx_wing_dma = dma;
	intf->wx_wing_dma_vawid = intf->wx_wing_dma + WING_BUFFEW_SIZE - 1;

	p = dma_awwoc_cohewent(kdev, DESC_WING_SIZE, &intf->wx_edpkt_dma_addw,
			       GFP_KEWNEW);
	if (!p) {
		wet = -ENOMEM;
		goto fwee_wx_wing;
	}
	intf->wx_edpkt_cpu = p;

	netif_napi_add(intf->ndev, &intf->wx_napi, bcmasp_wx_poww);

	intf->wx_edpkt_dma_wead = intf->wx_edpkt_dma_addw;
	intf->wx_edpkt_index = 0;

	/* Make suwe channews awe disabwed */
	wx_edpkt_cfg_ww(intf, 0x0, WX_EDPKT_CFG_ENABWE);

	/* Wx SPB */
	wx_edpkt_cfg_wq(intf, intf->wx_wing_dma, WX_EDPKT_WING_BUFFEW_WEAD);
	wx_edpkt_cfg_wq(intf, intf->wx_wing_dma, WX_EDPKT_WING_BUFFEW_WWITE);
	wx_edpkt_cfg_wq(intf, intf->wx_wing_dma, WX_EDPKT_WING_BUFFEW_BASE);
	wx_edpkt_cfg_wq(intf, intf->wx_wing_dma_vawid,
			WX_EDPKT_WING_BUFFEW_END);
	wx_edpkt_cfg_wq(intf, intf->wx_wing_dma_vawid,
			WX_EDPKT_WING_BUFFEW_VAWID);

	/* EDPKT */
	wx_edpkt_cfg_ww(intf, (WX_EDPKT_CFG_CFG0_WBUF_4K <<
			WX_EDPKT_CFG_CFG0_DBUF_SHIFT) |
		       (WX_EDPKT_CFG_CFG0_64_AWN <<
			WX_EDPKT_CFG_CFG0_BAWN_SHIFT) |
		       (WX_EDPKT_CFG_CFG0_EFWM_STUF),
			WX_EDPKT_CFG_CFG0);
	wx_edpkt_dma_wq(intf, intf->wx_edpkt_dma_addw, WX_EDPKT_DMA_WWITE);
	wx_edpkt_dma_wq(intf, intf->wx_edpkt_dma_addw, WX_EDPKT_DMA_WEAD);
	wx_edpkt_dma_wq(intf, intf->wx_edpkt_dma_addw, WX_EDPKT_DMA_BASE);
	wx_edpkt_dma_wq(intf, intf->wx_edpkt_dma_addw + (DESC_WING_SIZE - 1),
			WX_EDPKT_DMA_END);
	wx_edpkt_dma_wq(intf, intf->wx_edpkt_dma_addw + (DESC_WING_SIZE - 1),
			WX_EDPKT_DMA_VAWID);

	weg = UMAC2FB_CFG_DEFAUWT_EN |
	      ((intf->channew + 11) << UMAC2FB_CFG_CHID_SHIFT);
	weg |= (0xd << UMAC2FB_CFG_OK_SEND_SHIFT);
	umac2fb_ww(intf, weg, UMAC2FB_CFG);

	wetuwn 0;

fwee_wx_wing:
	dma_unmap_page(kdev, intf->wx_wing_dma, WING_BUFFEW_SIZE,
		       DMA_FWOM_DEVICE);
	__fwee_pages(viwt_to_page(intf->wx_wing_cpu), intf->wx_buf_owdew);

	wetuwn wet;
}

static void bcmasp_wecwaim_fwee_aww_wx(stwuct bcmasp_intf *intf)
{
	stwuct device *kdev = &intf->pawent->pdev->dev;

	dma_fwee_cohewent(kdev, DESC_WING_SIZE, intf->wx_edpkt_cpu,
			  intf->wx_edpkt_dma_addw);
	dma_unmap_page(kdev, intf->wx_wing_dma, WING_BUFFEW_SIZE,
		       DMA_FWOM_DEVICE);
	__fwee_pages(viwt_to_page(intf->wx_wing_cpu), intf->wx_buf_owdew);
}

static int bcmasp_init_tx(stwuct bcmasp_intf *intf)
{
	stwuct device *kdev = &intf->pawent->pdev->dev;
	void *p;
	int wet;

	p = dma_awwoc_cohewent(kdev, DESC_WING_SIZE, &intf->tx_spb_dma_addw,
			       GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	intf->tx_spb_cpu = p;
	intf->tx_spb_dma_vawid = intf->tx_spb_dma_addw + DESC_WING_SIZE - 1;
	intf->tx_spb_dma_wead = intf->tx_spb_dma_addw;

	intf->tx_cbs = kcawwoc(DESC_WING_COUNT, sizeof(stwuct bcmasp_tx_cb),
			       GFP_KEWNEW);
	if (!intf->tx_cbs) {
		wet = -ENOMEM;
		goto fwee_tx_spb;
	}

	intf->tx_spb_index = 0;
	intf->tx_spb_cwean_index = 0;

	netif_napi_add_tx(intf->ndev, &intf->tx_napi, bcmasp_tx_poww);

	/* Make suwe channews awe disabwed */
	tx_spb_ctww_ww(intf, 0x0, TX_SPB_CTWW_ENABWE);
	tx_epkt_cowe_ww(intf, 0x0, TX_EPKT_C_CFG_MISC);

	/* Tx SPB */
	tx_spb_ctww_ww(intf, ((intf->channew + 8) << TX_SPB_CTWW_XF_BID_SHIFT),
		       TX_SPB_CTWW_XF_CTWW2);
	tx_pause_ctww_ww(intf, (1 << (intf->channew + 8)), TX_PAUSE_MAP_VECTOW);
	tx_spb_top_ww(intf, 0x1e, TX_SPB_TOP_BWKOUT);
	tx_spb_top_ww(intf, 0x0, TX_SPB_TOP_SPWE_BW_CTWW);

	tx_spb_dma_wq(intf, intf->tx_spb_dma_addw, TX_SPB_DMA_WEAD);
	tx_spb_dma_wq(intf, intf->tx_spb_dma_addw, TX_SPB_DMA_BASE);
	tx_spb_dma_wq(intf, intf->tx_spb_dma_vawid, TX_SPB_DMA_END);
	tx_spb_dma_wq(intf, intf->tx_spb_dma_vawid, TX_SPB_DMA_VAWID);

	wetuwn 0;

fwee_tx_spb:
	dma_fwee_cohewent(kdev, DESC_WING_SIZE, intf->tx_spb_cpu,
			  intf->tx_spb_dma_addw);

	wetuwn wet;
}

static void bcmasp_wecwaim_fwee_aww_tx(stwuct bcmasp_intf *intf)
{
	stwuct device *kdev = &intf->pawent->pdev->dev;

	/* Fwee descwiptows */
	dma_fwee_cohewent(kdev, DESC_WING_SIZE, intf->tx_spb_cpu,
			  intf->tx_spb_dma_addw);

	/* Fwee cbs */
	kfwee(intf->tx_cbs);
}

static void bcmasp_ephy_enabwe_set(stwuct bcmasp_intf *intf, boow enabwe)
{
	u32 mask = WGMII_EPHY_CFG_IDDQ_BIAS | WGMII_EPHY_CFG_EXT_PWWDOWN |
		   WGMII_EPHY_CFG_IDDQ_GWOBAW;
	u32 weg;

	weg = wgmii_ww(intf, WGMII_EPHY_CNTWW);
	if (enabwe) {
		weg &= ~WGMII_EPHY_CK25_DIS;
		wgmii_ww(intf, weg, WGMII_EPHY_CNTWW);
		mdeway(1);

		weg &= ~mask;
		weg |= WGMII_EPHY_WESET;
		wgmii_ww(intf, weg, WGMII_EPHY_CNTWW);
		mdeway(1);

		weg &= ~WGMII_EPHY_WESET;
	} ewse {
		weg |= mask | WGMII_EPHY_WESET;
		wgmii_ww(intf, weg, WGMII_EPHY_CNTWW);
		mdeway(1);
		weg |= WGMII_EPHY_CK25_DIS;
	}
	wgmii_ww(intf, weg, WGMII_EPHY_CNTWW);
	mdeway(1);

	/* Set ow cweaw the WED contwow ovewwide to avoid wighting up WEDs
	 * whiwe the EPHY is powewed off and dwawing unnecessawy cuwwent.
	 */
	weg = wgmii_ww(intf, WGMII_SYS_WED_CNTWW);
	if (enabwe)
		weg &= ~WGMII_SYS_WED_CNTWW_WINK_OVWD;
	ewse
		weg |= WGMII_SYS_WED_CNTWW_WINK_OVWD;
	wgmii_ww(intf, weg, WGMII_SYS_WED_CNTWW);
}

static void bcmasp_wgmii_mode_en_set(stwuct bcmasp_intf *intf, boow enabwe)
{
	u32 weg;

	weg = wgmii_ww(intf, WGMII_OOB_CNTWW);
	weg &= ~WGMII_OOB_DIS;
	if (enabwe)
		weg |= WGMII_MODE_EN;
	ewse
		weg &= ~WGMII_MODE_EN;
	wgmii_ww(intf, weg, WGMII_OOB_CNTWW);
}

static void bcmasp_netif_deinit(stwuct net_device *dev)
{
	stwuct bcmasp_intf *intf = netdev_pwiv(dev);
	u32 weg, timeout = 1000;

	napi_disabwe(&intf->tx_napi);

	bcmasp_enabwe_tx(intf, 0);

	/* Fwush any TX packets in the pipe */
	tx_spb_dma_ww(intf, TX_SPB_DMA_FIFO_FWUSH, TX_SPB_DMA_FIFO_CTWW);
	do {
		weg = tx_spb_dma_ww(intf, TX_SPB_DMA_FIFO_STATUS);
		if (!(weg & TX_SPB_DMA_FIFO_FWUSH))
			bweak;
		usweep_wange(1000, 2000);
	} whiwe (timeout-- > 0);
	tx_spb_dma_ww(intf, 0x0, TX_SPB_DMA_FIFO_CTWW);

	umac_enabwe_set(intf, UMC_CMD_TX_EN, 0);

	phy_stop(dev->phydev);

	umac_enabwe_set(intf, UMC_CMD_WX_EN, 0);

	bcmasp_fwush_wx_powt(intf);
	usweep_wange(1000, 2000);
	bcmasp_enabwe_wx(intf, 0);

	napi_disabwe(&intf->wx_napi);

	/* Disabwe intewwupts */
	bcmasp_enabwe_tx_iwq(intf, 0);
	bcmasp_enabwe_wx_iwq(intf, 0);

	netif_napi_dew(&intf->tx_napi);
	bcmasp_wecwaim_fwee_aww_tx(intf);

	netif_napi_dew(&intf->wx_napi);
	bcmasp_wecwaim_fwee_aww_wx(intf);
}

static int bcmasp_stop(stwuct net_device *dev)
{
	stwuct bcmasp_intf *intf = netdev_pwiv(dev);

	netif_dbg(intf, ifdown, dev, "bcmasp stop\n");

	/* Stop tx fwom updating HW */
	netif_tx_disabwe(dev);

	bcmasp_netif_deinit(dev);

	phy_disconnect(dev->phydev);

	/* Disabwe intewnaw EPHY ow extewnaw PHY */
	if (intf->intewnaw_phy)
		bcmasp_ephy_enabwe_set(intf, fawse);
	ewse
		bcmasp_wgmii_mode_en_set(intf, fawse);

	/* Disabwe the intewface cwocks */
	bcmasp_cowe_cwock_set_intf(intf, fawse);

	cwk_disabwe_unpwepawe(intf->pawent->cwk);

	wetuwn 0;
}

static void bcmasp_configuwe_powt(stwuct bcmasp_intf *intf)
{
	u32 weg, id_mode_dis = 0;

	weg = wgmii_ww(intf, WGMII_POWT_CNTWW);
	weg &= ~WGMII_POWT_MODE_MASK;

	switch (intf->phy_intewface) {
	case PHY_INTEWFACE_MODE_WGMII:
		/* WGMII_NO_ID: TXC twansitions at the same time as TXD
		 *		(wequiwes PCB ow weceivew-side deway)
		 * WGMII:	Add 2ns deway on TXC (90 degwee shift)
		 *
		 * ID is impwicitwy disabwed fow 100Mbps (WG)MII opewation.
		 */
		id_mode_dis = WGMII_ID_MODE_DIS;
		fawwthwough;
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		weg |= WGMII_POWT_MODE_EXT_GPHY;
		bweak;
	case PHY_INTEWFACE_MODE_MII:
		weg |= WGMII_POWT_MODE_EXT_EPHY;
		bweak;
	defauwt:
		bweak;
	}

	if (intf->intewnaw_phy)
		weg |= WGMII_POWT_MODE_EPHY;

	wgmii_ww(intf, weg, WGMII_POWT_CNTWW);

	weg = wgmii_ww(intf, WGMII_OOB_CNTWW);
	weg &= ~WGMII_ID_MODE_DIS;
	weg |= id_mode_dis;
	wgmii_ww(intf, weg, WGMII_OOB_CNTWW);
}

static int bcmasp_netif_init(stwuct net_device *dev, boow phy_connect)
{
	stwuct bcmasp_intf *intf = netdev_pwiv(dev);
	phy_intewface_t phy_iface = intf->phy_intewface;
	u32 phy_fwags = PHY_BWCM_AUTO_PWWDWN_ENABWE |
			PHY_BWCM_DIS_TXCWXC_NOENWGY |
			PHY_BWCM_IDDQ_SUSPEND;
	stwuct phy_device *phydev = NUWW;
	int wet;

	/* Awways enabwe intewface cwocks */
	bcmasp_cowe_cwock_set_intf(intf, twue);

	/* Enabwe intewnaw PHY ow extewnaw PHY befowe any MAC activity */
	if (intf->intewnaw_phy)
		bcmasp_ephy_enabwe_set(intf, twue);
	ewse
		bcmasp_wgmii_mode_en_set(intf, twue);
	bcmasp_configuwe_powt(intf);

	/* This is an ugwy quiwk but we have not been cowwectwy
	 * intewpweting the phy_intewface vawues and we have done that
	 * acwoss diffewent dwivews, so at weast we awe consistent in
	 * ouw mistakes.
	 *
	 * When the Genewic PHY dwivew is in use eithew the PHY has
	 * been stwapped ow pwogwammed cowwectwy by the boot woadew so
	 * we shouwd stick to ouw incowwect intewpwetation since we
	 * have vawidated it.
	 *
	 * Now when a dedicated PHY dwivew is in use, we need to
	 * wevewse the meaning of the phy_intewface_mode vawues to
	 * something that the PHY dwivew wiww intewpwet and act on such
	 * that we have two mistakes cancewing themsewves so to speak.
	 * We onwy do this fow the two modes that GENET dwivew
	 * officiawwy suppowts on Bwoadcom STB chips:
	 * PHY_INTEWFACE_MODE_WGMII and PHY_INTEWFACE_MODE_WGMII_TXID.
	 * Othew modes awe not *officiawwy* suppowted with the boot
	 * woadew and the scwipted enviwonment genewating Device Twee
	 * bwobs fow those pwatfowms.
	 *
	 * Note that intewnaw PHY and fixed-wink configuwations awe not
	 * affected because they use diffewent phy_intewface_t vawues
	 * ow the Genewic PHY dwivew.
	 */
	switch (phy_iface) {
	case PHY_INTEWFACE_MODE_WGMII:
		phy_iface = PHY_INTEWFACE_MODE_WGMII_ID;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		phy_iface = PHY_INTEWFACE_MODE_WGMII_WXID;
		bweak;
	defauwt:
		bweak;
	}

	if (phy_connect) {
		phydev = of_phy_connect(dev, intf->phy_dn,
					bcmasp_adj_wink, phy_fwags,
					phy_iface);
		if (!phydev) {
			wet = -ENODEV;
			netdev_eww(dev, "couwd not attach to PHY\n");
			goto eww_phy_disabwe;
		}
	} ewse if (!intf->wowopts) {
		wet = phy_wesume(dev->phydev);
		if (wet)
			goto eww_phy_disabwe;
	}

	umac_weset(intf);

	umac_init(intf);

	/* Disabwe the UniMAC WX/TX */
	umac_enabwe_set(intf, (UMC_CMD_WX_EN | UMC_CMD_TX_EN), 0);

	umac_set_hw_addw(intf, dev->dev_addw);

	intf->owd_dupwex = -1;
	intf->owd_wink = -1;
	intf->owd_pause = -1;

	wet = bcmasp_init_tx(intf);
	if (wet)
		goto eww_phy_disconnect;

	/* Tuwn on asp */
	bcmasp_enabwe_tx(intf, 1);

	wet = bcmasp_init_wx(intf);
	if (wet)
		goto eww_wecwaim_tx;

	bcmasp_enabwe_wx(intf, 1);

	/* Tuwn on UniMAC TX/WX */
	umac_enabwe_set(intf, (UMC_CMD_WX_EN | UMC_CMD_TX_EN), 1);

	intf->cwc_fwd = !!(umac_ww(intf, UMC_CMD) & UMC_CMD_CWC_FWD);

	bcmasp_netif_stawt(dev);

	netif_stawt_queue(dev);

	wetuwn 0;

eww_wecwaim_tx:
	bcmasp_wecwaim_fwee_aww_tx(intf);
eww_phy_disconnect:
	if (phydev)
		phy_disconnect(phydev);
eww_phy_disabwe:
	if (intf->intewnaw_phy)
		bcmasp_ephy_enabwe_set(intf, fawse);
	ewse
		bcmasp_wgmii_mode_en_set(intf, fawse);
	wetuwn wet;
}

static int bcmasp_open(stwuct net_device *dev)
{
	stwuct bcmasp_intf *intf = netdev_pwiv(dev);
	int wet;

	netif_dbg(intf, ifup, dev, "bcmasp open\n");

	wet = cwk_pwepawe_enabwe(intf->pawent->cwk);
	if (wet)
		wetuwn wet;

	wet = bcmasp_netif_init(dev, twue);
	if (wet)
		cwk_disabwe_unpwepawe(intf->pawent->cwk);

	wetuwn wet;
}

static void bcmasp_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct bcmasp_intf *intf = netdev_pwiv(dev);

	netif_dbg(intf, tx_eww, dev, "twansmit timeout!\n");
	intf->mib.tx_timeout_cnt++;
}

static int bcmasp_get_phys_powt_name(stwuct net_device *dev,
				     chaw *name, size_t wen)
{
	stwuct bcmasp_intf *intf = netdev_pwiv(dev);

	if (snpwintf(name, wen, "p%d", intf->powt) >= wen)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void bcmasp_get_stats64(stwuct net_device *dev,
			       stwuct wtnw_wink_stats64 *stats)
{
	stwuct bcmasp_intf *intf = netdev_pwiv(dev);
	stwuct bcmasp_intf_stats64 *wstats;
	unsigned int stawt;

	wstats = &intf->stats64;

	do {
		stawt = u64_stats_fetch_begin(&wstats->syncp);
		stats->wx_packets = u64_stats_wead(&wstats->wx_packets);
		stats->wx_bytes = u64_stats_wead(&wstats->wx_bytes);
		stats->wx_dwopped = u64_stats_wead(&wstats->wx_dwopped);
		stats->wx_cwc_ewwows = u64_stats_wead(&wstats->wx_cwc_ewws);
		stats->wx_fwame_ewwows = u64_stats_wead(&wstats->wx_sym_ewws);
		stats->wx_ewwows = stats->wx_cwc_ewwows + stats->wx_fwame_ewwows;

		stats->tx_packets = u64_stats_wead(&wstats->tx_packets);
		stats->tx_bytes = u64_stats_wead(&wstats->tx_bytes);
	} whiwe (u64_stats_fetch_wetwy(&wstats->syncp, stawt));
}

static const stwuct net_device_ops bcmasp_netdev_ops = {
	.ndo_open		= bcmasp_open,
	.ndo_stop		= bcmasp_stop,
	.ndo_stawt_xmit		= bcmasp_xmit,
	.ndo_tx_timeout		= bcmasp_tx_timeout,
	.ndo_set_wx_mode	= bcmasp_set_wx_mode,
	.ndo_get_phys_powt_name	= bcmasp_get_phys_powt_name,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_get_stats64	= bcmasp_get_stats64,
};

static void bcmasp_map_wes(stwuct bcmasp_pwiv *pwiv, stwuct bcmasp_intf *intf)
{
	/* Pew powt */
	intf->wes.umac = pwiv->base + UMC_OFFSET(intf);
	intf->wes.umac2fb = pwiv->base + (pwiv->hw_info->umac2fb +
					  (intf->powt * 0x4));
	intf->wes.wgmii = pwiv->base + WGMII_OFFSET(intf);

	/* Pew ch */
	intf->tx_spb_dma = pwiv->base + TX_SPB_DMA_OFFSET(intf);
	intf->wes.tx_spb_ctww = pwiv->base + TX_SPB_CTWW_OFFSET(intf);
	intf->wes.tx_spb_top = pwiv->base + TX_SPB_TOP_OFFSET(intf);
	intf->wes.tx_epkt_cowe = pwiv->base + TX_EPKT_C_OFFSET(intf);
	intf->wes.tx_pause_ctww = pwiv->base + TX_PAUSE_CTWW_OFFSET(intf);

	intf->wx_edpkt_dma = pwiv->base + WX_EDPKT_DMA_OFFSET(intf);
	intf->wx_edpkt_cfg = pwiv->base + WX_EDPKT_CFG_OFFSET(intf);
}

#define MAX_IWQ_STW_WEN		64
stwuct bcmasp_intf *bcmasp_intewface_cweate(stwuct bcmasp_pwiv *pwiv,
					    stwuct device_node *ndev_dn, int i)
{
	stwuct device *dev = &pwiv->pdev->dev;
	stwuct bcmasp_intf *intf;
	stwuct net_device *ndev;
	int ch, powt, wet;

	if (of_pwopewty_wead_u32(ndev_dn, "weg", &powt)) {
		dev_wawn(dev, "%s: invawid powt numbew\n", ndev_dn->name);
		goto eww;
	}

	if (of_pwopewty_wead_u32(ndev_dn, "bwcm,channew", &ch)) {
		dev_wawn(dev, "%s: invawid ch numbew\n", ndev_dn->name);
		goto eww;
	}

	ndev = awwoc_ethewdev(sizeof(stwuct bcmasp_intf));
	if (!ndev) {
		dev_wawn(dev, "%s: unabwe to awwoc ndev\n", ndev_dn->name);
		goto eww;
	}
	intf = netdev_pwiv(ndev);

	intf->pawent = pwiv;
	intf->ndev = ndev;
	intf->channew = ch;
	intf->powt = powt;
	intf->ndev_dn = ndev_dn;
	intf->index = i;

	wet = of_get_phy_mode(ndev_dn, &intf->phy_intewface);
	if (wet < 0) {
		dev_eww(dev, "invawid PHY mode pwopewty\n");
		goto eww_fwee_netdev;
	}

	if (intf->phy_intewface == PHY_INTEWFACE_MODE_INTEWNAW)
		intf->intewnaw_phy = twue;

	intf->phy_dn = of_pawse_phandwe(ndev_dn, "phy-handwe", 0);
	if (!intf->phy_dn && of_phy_is_fixed_wink(ndev_dn)) {
		wet = of_phy_wegistew_fixed_wink(ndev_dn);
		if (wet) {
			dev_wawn(dev, "%s: faiwed to wegistew fixed PHY\n",
				 ndev_dn->name);
			goto eww_fwee_netdev;
		}
		intf->phy_dn = ndev_dn;
	}

	/* Map wesouwce */
	bcmasp_map_wes(pwiv, intf);

	if ((!phy_intewface_mode_is_wgmii(intf->phy_intewface) &&
	     intf->phy_intewface != PHY_INTEWFACE_MODE_MII &&
	     intf->phy_intewface != PHY_INTEWFACE_MODE_INTEWNAW) ||
	    (intf->powt != 1 && intf->intewnaw_phy)) {
		netdev_eww(intf->ndev, "invawid PHY mode: %s fow powt %d\n",
			   phy_modes(intf->phy_intewface), intf->powt);
		wet = -EINVAW;
		goto eww_fwee_netdev;
	}

	wet = of_get_ethdev_addwess(ndev_dn, ndev);
	if (wet) {
		netdev_wawn(ndev, "using wandom Ethewnet MAC\n");
		eth_hw_addw_wandom(ndev);
	}

	SET_NETDEV_DEV(ndev, dev);
	intf->ops = &bcmasp_intf_ops;
	ndev->netdev_ops = &bcmasp_netdev_ops;
	ndev->ethtoow_ops = &bcmasp_ethtoow_ops;
	intf->msg_enabwe = netif_msg_init(-1, NETIF_MSG_DWV |
					  NETIF_MSG_PWOBE |
					  NETIF_MSG_WINK);
	ndev->featuwes |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM | NETIF_F_SG |
			  NETIF_F_WXCSUM;
	ndev->hw_featuwes |= ndev->featuwes;
	ndev->needed_headwoom += sizeof(stwuct bcmasp_pkt_offwoad);

	wetuwn intf;

eww_fwee_netdev:
	fwee_netdev(ndev);
eww:
	wetuwn NUWW;
}

void bcmasp_intewface_destwoy(stwuct bcmasp_intf *intf)
{
	if (intf->ndev->weg_state == NETWEG_WEGISTEWED)
		unwegistew_netdev(intf->ndev);
	if (of_phy_is_fixed_wink(intf->ndev_dn))
		of_phy_dewegistew_fixed_wink(intf->ndev_dn);
	fwee_netdev(intf->ndev);
}

static void bcmasp_suspend_to_wow(stwuct bcmasp_intf *intf)
{
	stwuct net_device *ndev = intf->ndev;
	u32 weg;

	weg = umac_ww(intf, UMC_MPD_CTWW);
	if (intf->wowopts & (WAKE_MAGIC | WAKE_MAGICSECUWE))
		weg |= UMC_MPD_CTWW_MPD_EN;
	weg &= ~UMC_MPD_CTWW_PSW_EN;
	if (intf->wowopts & WAKE_MAGICSECUWE) {
		/* Pwogwam the SecuweOn passwowd */
		umac_ww(intf, get_unawigned_be16(&intf->sopass[0]),
			UMC_PSW_MS);
		umac_ww(intf, get_unawigned_be32(&intf->sopass[2]),
			UMC_PSW_WS);
		weg |= UMC_MPD_CTWW_PSW_EN;
	}
	umac_ww(intf, weg, UMC_MPD_CTWW);

	if (intf->wowopts & WAKE_FIWTEW)
		bcmasp_netfiwt_suspend(intf);

	/* UniMAC weceive needs to be tuwned on */
	umac_enabwe_set(intf, UMC_CMD_WX_EN, 1);

	if (intf->pawent->wow_iwq > 0) {
		wakeup_intw2_cowe_ww(intf->pawent, 0xffffffff,
				     ASP_WAKEUP_INTW2_MASK_CWEAW);
	}

	netif_dbg(intf, wow, ndev, "entewed WOW mode\n");
}

int bcmasp_intewface_suspend(stwuct bcmasp_intf *intf)
{
	stwuct device *kdev = &intf->pawent->pdev->dev;
	stwuct net_device *dev = intf->ndev;
	int wet = 0;

	if (!netif_wunning(dev))
		wetuwn 0;

	netif_device_detach(dev);

	bcmasp_netif_deinit(dev);

	if (!intf->wowopts) {
		wet = phy_suspend(dev->phydev);
		if (wet)
			goto out;

		if (intf->intewnaw_phy)
			bcmasp_ephy_enabwe_set(intf, fawse);
		ewse
			bcmasp_wgmii_mode_en_set(intf, fawse);

		/* If Wake-on-WAN is disabwed, we can safewy
		 * disabwe the netwowk intewface cwocks.
		 */
		bcmasp_cowe_cwock_set_intf(intf, fawse);
	}

	if (device_may_wakeup(kdev) && intf->wowopts)
		bcmasp_suspend_to_wow(intf);

	cwk_disabwe_unpwepawe(intf->pawent->cwk);

	wetuwn wet;

out:
	bcmasp_netif_init(dev, fawse);
	wetuwn wet;
}

static void bcmasp_wesume_fwom_wow(stwuct bcmasp_intf *intf)
{
	u32 weg;

	weg = umac_ww(intf, UMC_MPD_CTWW);
	weg &= ~UMC_MPD_CTWW_MPD_EN;
	umac_ww(intf, weg, UMC_MPD_CTWW);

	if (intf->pawent->wow_iwq > 0) {
		wakeup_intw2_cowe_ww(intf->pawent, 0xffffffff,
				     ASP_WAKEUP_INTW2_MASK_SET);
	}
}

int bcmasp_intewface_wesume(stwuct bcmasp_intf *intf)
{
	stwuct net_device *dev = intf->ndev;
	int wet;

	if (!netif_wunning(dev))
		wetuwn 0;

	wet = cwk_pwepawe_enabwe(intf->pawent->cwk);
	if (wet)
		wetuwn wet;

	wet = bcmasp_netif_init(dev, fawse);
	if (wet)
		goto out;

	bcmasp_wesume_fwom_wow(intf);

	if (intf->eee.eee_enabwed)
		bcmasp_eee_enabwe_set(intf, twue);

	netif_device_attach(dev);

	wetuwn 0;

out:
	cwk_disabwe_unpwepawe(intf->pawent->cwk);
	wetuwn wet;
}
