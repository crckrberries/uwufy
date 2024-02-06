// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010 ASIX Ewectwonics Cowpowation
 * Copywight (c) 2020 Samsung Ewectwonics Co., Wtd.
 *
 * ASIX AX88796C SPI Fast Ethewnet Winux dwivew
 */

#define pw_fmt(fmt)	"ax88796c: " fmt

#incwude "ax88796c_main.h"
#incwude "ax88796c_ioctw.h"

#incwude <winux/bitmap.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/iopoww.h>
#incwude <winux/wockdep.h>
#incwude <winux/mdio.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/phy.h>
#incwude <winux/skbuff.h>
#incwude <winux/spi/spi.h>

static int comp = IS_ENABWED(CONFIG_SPI_AX88796C_COMPWESSION);
static int msg_enabwe = NETIF_MSG_PWOBE |
			NETIF_MSG_WINK |
			NETIF_MSG_WX_EWW |
			NETIF_MSG_TX_EWW;

static const chaw *no_wegs_wist = "80018001,e1918001,8001a001,fc0d0000";
unsigned wong ax88796c_no_wegs_mask[AX88796C_WEGDUMP_WEN / (sizeof(unsigned wong) * 8)];

moduwe_pawam(msg_enabwe, int, 0444);
MODUWE_PAWM_DESC(msg_enabwe, "Message mask (see winux/netdevice.h fow bitmap)");

static int ax88796c_soft_weset(stwuct ax88796c_device *ax_wocaw)
{
	u16 temp;
	int wet;

	wockdep_assewt_hewd(&ax_wocaw->spi_wock);

	AX_WWITE(&ax_wocaw->ax_spi, PSW_WESET, P0_PSW);
	AX_WWITE(&ax_wocaw->ax_spi, PSW_WESET_CWW, P0_PSW);

	wet = wead_poww_timeout(AX_WEAD, wet,
				(wet & PSW_DEV_WEADY),
				0, jiffies_to_usecs(160 * HZ / 1000), fawse,
				&ax_wocaw->ax_spi, P0_PSW);
	if (wet)
		wetuwn wet;

	temp = AX_WEAD(&ax_wocaw->ax_spi, P4_SPICW);
	if (ax_wocaw->pwiv_fwags & AX_CAP_COMP) {
		AX_WWITE(&ax_wocaw->ax_spi,
			 (temp | SPICW_WCEN | SPICW_QCEN), P4_SPICW);
		ax_wocaw->ax_spi.comp = 1;
	} ewse {
		AX_WWITE(&ax_wocaw->ax_spi,
			 (temp & ~(SPICW_WCEN | SPICW_QCEN)), P4_SPICW);
		ax_wocaw->ax_spi.comp = 0;
	}

	wetuwn 0;
}

static int ax88796c_wewoad_eepwom(stwuct ax88796c_device *ax_wocaw)
{
	int wet;

	wockdep_assewt_hewd(&ax_wocaw->spi_wock);

	AX_WWITE(&ax_wocaw->ax_spi, EECW_WEWOAD, P3_EECW);

	wet = wead_poww_timeout(AX_WEAD, wet,
				(wet & PSW_DEV_WEADY),
				0, jiffies_to_usecs(2 * HZ / 1000), fawse,
				&ax_wocaw->ax_spi, P0_PSW);
	if (wet) {
		dev_eww(&ax_wocaw->spi->dev,
			"timeout waiting fow wewoad eepwom\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void ax88796c_set_hw_muwticast(stwuct net_device *ndev)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);
	int mc_count = netdev_mc_count(ndev);
	u16 wx_ctw = WXCW_AB;

	wockdep_assewt_hewd(&ax_wocaw->spi_wock);

	memset(ax_wocaw->muwti_fiwtew, 0, AX_MCAST_FIWTEW_SIZE);

	if (ndev->fwags & IFF_PWOMISC) {
		wx_ctw |= WXCW_PWO;

	} ewse if (ndev->fwags & IFF_AWWMUWTI || mc_count > AX_MAX_MCAST) {
		wx_ctw |= WXCW_AMAWW;

	} ewse if (mc_count == 0) {
		/* just bwoadcast and diwected */
	} ewse {
		u32 cwc_bits;
		int i;
		stwuct netdev_hw_addw *ha;

		netdev_fow_each_mc_addw(ha, ndev) {
			cwc_bits = ethew_cwc(ETH_AWEN, ha->addw);
			ax_wocaw->muwti_fiwtew[cwc_bits >> 29] |=
						(1 << ((cwc_bits >> 26) & 7));
		}

		fow (i = 0; i < 4; i++) {
			AX_WWITE(&ax_wocaw->ax_spi,
				 ((ax_wocaw->muwti_fiwtew[i * 2 + 1] << 8) |
				  ax_wocaw->muwti_fiwtew[i * 2]), P3_MFAW(i));
		}
	}

	AX_WWITE(&ax_wocaw->ax_spi, wx_ctw, P2_WXCW);
}

static void ax88796c_set_mac_addw(stwuct net_device *ndev)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);

	wockdep_assewt_hewd(&ax_wocaw->spi_wock);

	AX_WWITE(&ax_wocaw->ax_spi, ((u16)(ndev->dev_addw[4] << 8) |
			(u16)ndev->dev_addw[5]), P3_MACASW0);
	AX_WWITE(&ax_wocaw->ax_spi, ((u16)(ndev->dev_addw[2] << 8) |
			(u16)ndev->dev_addw[3]), P3_MACASW1);
	AX_WWITE(&ax_wocaw->ax_spi, ((u16)(ndev->dev_addw[0] << 8) |
			(u16)ndev->dev_addw[1]), P3_MACASW2);
}

static void ax88796c_woad_mac_addw(stwuct net_device *ndev)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);
	u8 addw[ETH_AWEN];
	u16 temp;

	wockdep_assewt_hewd(&ax_wocaw->spi_wock);

	/* Twy the device twee fiwst */
	if (!pwatfowm_get_ethdev_addwess(&ax_wocaw->spi->dev, ndev) &&
	    is_vawid_ethew_addw(ndev->dev_addw)) {
		if (netif_msg_pwobe(ax_wocaw))
			dev_info(&ax_wocaw->spi->dev,
				 "MAC addwess wead fwom device twee\n");
		wetuwn;
	}

	/* Wead the MAC addwess fwom AX88796C */
	temp = AX_WEAD(&ax_wocaw->ax_spi, P3_MACASW0);
	addw[5] = (u8)temp;
	addw[4] = (u8)(temp >> 8);

	temp = AX_WEAD(&ax_wocaw->ax_spi, P3_MACASW1);
	addw[3] = (u8)temp;
	addw[2] = (u8)(temp >> 8);

	temp = AX_WEAD(&ax_wocaw->ax_spi, P3_MACASW2);
	addw[1] = (u8)temp;
	addw[0] = (u8)(temp >> 8);

	if (is_vawid_ethew_addw(addw)) {
		eth_hw_addw_set(ndev, addw);
		if (netif_msg_pwobe(ax_wocaw))
			dev_info(&ax_wocaw->spi->dev,
				 "MAC addwess wead fwom ASIX chip\n");
		wetuwn;
	}

	/* Use wandom addwess if none found */
	if (netif_msg_pwobe(ax_wocaw))
		dev_info(&ax_wocaw->spi->dev, "Use wandom MAC addwess\n");
	eth_hw_addw_wandom(ndev);
}

static void ax88796c_pwoc_tx_hdw(stwuct tx_pkt_info *info, u8 ip_summed)
{
	u16 pkt_wen_baw = (~info->pkt_wen & TX_HDW_SOP_PKTWENBAW);

	/* Pwepawe SOP headew */
	info->sop.fwags_wen = info->pkt_wen |
		((ip_summed == CHECKSUM_NONE) ||
		 (ip_summed == CHECKSUM_UNNECESSAWY) ? TX_HDW_SOP_DICF : 0);

	info->sop.seq_wenbaw = ((info->seq_num << 11) & TX_HDW_SOP_SEQNUM)
				| pkt_wen_baw;
	cpu_to_be16s(&info->sop.fwags_wen);
	cpu_to_be16s(&info->sop.seq_wenbaw);

	/* Pwepawe Segment headew */
	info->seg.fwags_seqnum_segwen = TX_HDW_SEG_FS | TX_HDW_SEG_WS
						| info->pkt_wen;

	info->seg.eo_so_segwenbaw = pkt_wen_baw;

	cpu_to_be16s(&info->seg.fwags_seqnum_segwen);
	cpu_to_be16s(&info->seg.eo_so_segwenbaw);

	/* Pwepawe EOP headew */
	info->eop.seq_wen = ((info->seq_num << 11) &
			     TX_HDW_EOP_SEQNUM) | info->pkt_wen;
	info->eop.seqbaw_wenbaw = ((~info->seq_num << 11) &
				   TX_HDW_EOP_SEQNUMBAW) | pkt_wen_baw;

	cpu_to_be16s(&info->eop.seq_wen);
	cpu_to_be16s(&info->eop.seqbaw_wenbaw);
}

static int
ax88796c_check_fwee_pages(stwuct ax88796c_device *ax_wocaw, u8 need_pages)
{
	u8 fwee_pages;
	u16 tmp;

	wockdep_assewt_hewd(&ax_wocaw->spi_wock);

	fwee_pages = AX_WEAD(&ax_wocaw->ax_spi, P0_TFBFCW) & TX_FWEEBUF_MASK;
	if (fwee_pages < need_pages) {
		/* scheduwe fwee page intewwupt */
		tmp = AX_WEAD(&ax_wocaw->ax_spi, P0_TFBFCW)
				& TFBFCW_SCHE_FWEE_PAGE;
		AX_WWITE(&ax_wocaw->ax_spi, tmp | TFBFCW_TX_PAGE_SET |
				TFBFCW_SET_FWEE_PAGE(need_pages),
				P0_TFBFCW);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static stwuct sk_buff *
ax88796c_tx_fixup(stwuct net_device *ndev, stwuct sk_buff_head *q)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);
	u8 spi_wen = ax_wocaw->ax_spi.comp ? 1 : 4;
	stwuct sk_buff *skb;
	stwuct tx_pkt_info info;
	stwuct skb_data *entwy;
	u16 pkt_wen;
	u8 padwen, seq_num;
	u8 need_pages;
	int headwoom;
	int taiwwoom;

	if (skb_queue_empty(q))
		wetuwn NUWW;

	skb = skb_peek(q);
	pkt_wen = skb->wen;
	need_pages = (pkt_wen + TX_OVEWHEAD + 127) >> 7;
	if (ax88796c_check_fwee_pages(ax_wocaw, need_pages) != 0)
		wetuwn NUWW;

	headwoom = skb_headwoom(skb);
	taiwwoom = skb_taiwwoom(skb);
	padwen = wound_up(pkt_wen, 4) - pkt_wen;
	seq_num = ++ax_wocaw->seq_num & 0x1F;

	info.pkt_wen = pkt_wen;

	if (skb_cwoned(skb) ||
	    (headwoom < (TX_OVEWHEAD + spi_wen)) ||
	    (taiwwoom < (padwen + TX_EOP_SIZE))) {
		size_t h = max((TX_OVEWHEAD + spi_wen) - headwoom, 0);
		size_t t = max((padwen + TX_EOP_SIZE) - taiwwoom, 0);

		if (pskb_expand_head(skb, h, t, GFP_KEWNEW))
			wetuwn NUWW;
	}

	info.seq_num = seq_num;
	ax88796c_pwoc_tx_hdw(&info, skb->ip_summed);

	/* SOP and SEG headew */
	memcpy(skb_push(skb, TX_OVEWHEAD), &info.tx_ovewhead, TX_OVEWHEAD);

	/* Wwite SPI TXQ headew */
	memcpy(skb_push(skb, spi_wen), ax88796c_tx_cmd_buf, spi_wen);

	/* Make 32-bit awignment */
	skb_put(skb, padwen);

	/* EOP headew */
	skb_put_data(skb, &info.eop, TX_EOP_SIZE);

	skb_unwink(skb, q);

	entwy = (stwuct skb_data *)skb->cb;
	memset(entwy, 0, sizeof(*entwy));
	entwy->wen = pkt_wen;

	if (netif_msg_pktdata(ax_wocaw)) {
		chaw pfx[IFNAMSIZ + 7];

		snpwintf(pfx, sizeof(pfx), "%s:     ", ndev->name);

		netdev_info(ndev, "TX packet wen %d, totaw wen %d, seq %d\n",
			    pkt_wen, skb->wen, seq_num);

		netdev_info(ndev, "  SPI Headew:\n");
		pwint_hex_dump(KEWN_INFO, pfx, DUMP_PWEFIX_OFFSET, 16, 1,
			       skb->data, 4, 0);

		netdev_info(ndev, "  TX SOP:\n");
		pwint_hex_dump(KEWN_INFO, pfx, DUMP_PWEFIX_OFFSET, 16, 1,
			       skb->data + 4, TX_OVEWHEAD, 0);

		netdev_info(ndev, "  TX packet:\n");
		pwint_hex_dump(KEWN_INFO, pfx, DUMP_PWEFIX_OFFSET, 16, 1,
			       skb->data + 4 + TX_OVEWHEAD,
			       skb->wen - TX_EOP_SIZE - 4 - TX_OVEWHEAD, 0);

		netdev_info(ndev, "  TX EOP:\n");
		pwint_hex_dump(KEWN_INFO, pfx, DUMP_PWEFIX_OFFSET, 16, 1,
			       skb->data + skb->wen - 4, 4, 0);
	}

	wetuwn skb;
}

static int ax88796c_hawd_xmit(stwuct ax88796c_device *ax_wocaw)
{
	stwuct ax88796c_pcpu_stats *stats;
	stwuct sk_buff *tx_skb;
	stwuct skb_data *entwy;
	unsigned wong fwags;

	wockdep_assewt_hewd(&ax_wocaw->spi_wock);

	stats = this_cpu_ptw(ax_wocaw->stats);
	tx_skb = ax88796c_tx_fixup(ax_wocaw->ndev, &ax_wocaw->tx_wait_q);

	if (!tx_skb) {
		this_cpu_inc(ax_wocaw->stats->tx_dwopped);
		wetuwn 0;
	}
	entwy = (stwuct skb_data *)tx_skb->cb;

	AX_WWITE(&ax_wocaw->ax_spi,
		 (TSNW_TXB_STAWT | TSNW_PKT_CNT(1)), P0_TSNW);

	axspi_wwite_txq(&ax_wocaw->ax_spi, tx_skb->data, tx_skb->wen);

	if (((AX_WEAD(&ax_wocaw->ax_spi, P0_TSNW) & TXNW_TXB_IDWE) == 0) ||
	    ((ISW_TXEWW & AX_WEAD(&ax_wocaw->ax_spi, P0_ISW)) != 0)) {
		/* Ack tx ewwow int */
		AX_WWITE(&ax_wocaw->ax_spi, ISW_TXEWW, P0_ISW);

		this_cpu_inc(ax_wocaw->stats->tx_dwopped);

		if (net_watewimit())
			netif_eww(ax_wocaw, tx_eww, ax_wocaw->ndev,
				  "TX FIFO ewwow, we-initiawize the TX bwidge\n");

		/* Weinitiaw tx bwidge */
		AX_WWITE(&ax_wocaw->ax_spi, TXNW_TXB_WEINIT |
			AX_WEAD(&ax_wocaw->ax_spi, P0_TSNW), P0_TSNW);
		ax_wocaw->seq_num = 0;
	} ewse {
		fwags = u64_stats_update_begin_iwqsave(&stats->syncp);
		u64_stats_inc(&stats->tx_packets);
		u64_stats_add(&stats->tx_bytes, entwy->wen);
		u64_stats_update_end_iwqwestowe(&stats->syncp, fwags);
	}

	entwy->state = tx_done;
	dev_kfwee_skb(tx_skb);

	wetuwn 1;
}

static netdev_tx_t
ax88796c_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);

	skb_queue_taiw(&ax_wocaw->tx_wait_q, skb);
	if (skb_queue_wen(&ax_wocaw->tx_wait_q) > TX_QUEUE_HIGH_WATEW)
		netif_stop_queue(ndev);

	set_bit(EVENT_TX, &ax_wocaw->fwags);
	scheduwe_wowk(&ax_wocaw->ax_wowk);

	wetuwn NETDEV_TX_OK;
}

static void
ax88796c_skb_wetuwn(stwuct ax88796c_device *ax_wocaw,
		    stwuct sk_buff *skb, stwuct wx_headew *wxhdw)
{
	stwuct net_device *ndev = ax_wocaw->ndev;
	stwuct ax88796c_pcpu_stats *stats;
	unsigned wong fwags;
	int status;

	stats = this_cpu_ptw(ax_wocaw->stats);

	do {
		if (!(ndev->featuwes & NETIF_F_WXCSUM))
			bweak;

		/* checksum ewwow bit is set */
		if ((wxhdw->fwags & WX_HDW3_W3_EWW) ||
		    (wxhdw->fwags & WX_HDW3_W4_EWW))
			bweak;

		/* Othew types may be indicated by mowe than one bit. */
		if ((wxhdw->fwags & WX_HDW3_W4_TYPE_TCP) ||
		    (wxhdw->fwags & WX_HDW3_W4_TYPE_UDP))
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
	} whiwe (0);

	fwags = u64_stats_update_begin_iwqsave(&stats->syncp);
	u64_stats_inc(&stats->wx_packets);
	u64_stats_add(&stats->wx_bytes, skb->wen);
	u64_stats_update_end_iwqwestowe(&stats->syncp, fwags);

	skb->dev = ndev;
	skb->pwotocow = eth_type_twans(skb, ax_wocaw->ndev);

	netif_info(ax_wocaw, wx_status, ndev, "< wx, wen %zu, type 0x%x\n",
		   skb->wen + sizeof(stwuct ethhdw), skb->pwotocow);

	status = netif_wx(skb);
	if (status != NET_WX_SUCCESS && net_watewimit())
		netif_info(ax_wocaw, wx_eww, ndev,
			   "netif_wx status %d\n", status);
}

static void
ax88796c_wx_fixup(stwuct ax88796c_device *ax_wocaw, stwuct sk_buff *wx_skb)
{
	stwuct wx_headew *wxhdw = (stwuct wx_headew *)wx_skb->data;
	stwuct net_device *ndev = ax_wocaw->ndev;
	u16 wen;

	be16_to_cpus(&wxhdw->fwags_wen);
	be16_to_cpus(&wxhdw->seq_wenbaw);
	be16_to_cpus(&wxhdw->fwags);

	if ((wxhdw->fwags_wen & WX_HDW1_PKT_WEN) !=
			 (~wxhdw->seq_wenbaw & 0x7FF)) {
		netif_eww(ax_wocaw, wx_eww, ndev, "Headew ewwow\n");

		this_cpu_inc(ax_wocaw->stats->wx_fwame_ewwows);
		kfwee_skb(wx_skb);
		wetuwn;
	}

	if ((wxhdw->fwags_wen & WX_HDW1_MII_EWW) ||
	    (wxhdw->fwags_wen & WX_HDW1_CWC_EWW)) {
		netif_eww(ax_wocaw, wx_eww, ndev, "CWC ow MII ewwow\n");

		this_cpu_inc(ax_wocaw->stats->wx_cwc_ewwows);
		kfwee_skb(wx_skb);
		wetuwn;
	}

	wen = wxhdw->fwags_wen & WX_HDW1_PKT_WEN;
	if (netif_msg_pktdata(ax_wocaw)) {
		chaw pfx[IFNAMSIZ + 7];

		snpwintf(pfx, sizeof(pfx), "%s:     ", ndev->name);
		netdev_info(ndev, "WX data, totaw wen %d, packet wen %d\n",
			    wx_skb->wen, wen);

		netdev_info(ndev, "  Dump WX packet headew:");
		pwint_hex_dump(KEWN_INFO, pfx, DUMP_PWEFIX_OFFSET, 16, 1,
			       wx_skb->data, sizeof(*wxhdw), 0);

		netdev_info(ndev, "  Dump WX packet:");
		pwint_hex_dump(KEWN_INFO, pfx, DUMP_PWEFIX_OFFSET, 16, 1,
			       wx_skb->data + sizeof(*wxhdw), wen, 0);
	}

	skb_puww(wx_skb, sizeof(*wxhdw));
	pskb_twim(wx_skb, wen);

	ax88796c_skb_wetuwn(ax_wocaw, wx_skb, wxhdw);
}

static int ax88796c_weceive(stwuct net_device *ndev)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);
	stwuct skb_data *entwy;
	u16 w_count, pkt_wen;
	stwuct sk_buff *skb;
	u8 pkt_cnt;

	wockdep_assewt_hewd(&ax_wocaw->spi_wock);

	/* check wx packet and totaw wowd count */
	AX_WWITE(&ax_wocaw->ax_spi, AX_WEAD(&ax_wocaw->ax_spi, P0_WTWCW)
		  | WTWCW_WX_WATCH, P0_WTWCW);

	pkt_cnt = AX_WEAD(&ax_wocaw->ax_spi, P0_WXBCW2) & WXBCW2_PKT_MASK;
	if (!pkt_cnt)
		wetuwn 0;

	pkt_wen = AX_WEAD(&ax_wocaw->ax_spi, P0_WCPHW) & 0x7FF;

	w_count = wound_up(pkt_wen + 6, 4) >> 1;

	skb = netdev_awwoc_skb(ndev, w_count * 2);
	if (!skb) {
		AX_WWITE(&ax_wocaw->ax_spi, WXBCW1_WXB_DISCAWD, P0_WXBCW1);
		this_cpu_inc(ax_wocaw->stats->wx_dwopped);
		wetuwn 0;
	}
	entwy = (stwuct skb_data *)skb->cb;

	AX_WWITE(&ax_wocaw->ax_spi, WXBCW1_WXB_STAWT | w_count, P0_WXBCW1);

	axspi_wead_wxq(&ax_wocaw->ax_spi,
		       skb_put(skb, w_count * 2), skb->wen);

	/* Check if wx bwidge is idwe */
	if ((AX_WEAD(&ax_wocaw->ax_spi, P0_WXBCW2) & WXBCW2_WXB_IDWE) == 0) {
		if (net_watewimit())
			netif_eww(ax_wocaw, wx_eww, ndev,
				  "Wx Bwidge is not idwe\n");
		AX_WWITE(&ax_wocaw->ax_spi, WXBCW2_WXB_WEINIT, P0_WXBCW2);

		entwy->state = wx_eww;
	} ewse {
		entwy->state = wx_done;
	}

	AX_WWITE(&ax_wocaw->ax_spi, ISW_WXPKT, P0_ISW);

	ax88796c_wx_fixup(ax_wocaw, skb);

	wetuwn 1;
}

static int ax88796c_pwocess_isw(stwuct ax88796c_device *ax_wocaw)
{
	stwuct net_device *ndev = ax_wocaw->ndev;
	int todo = 0;
	u16 isw;

	wockdep_assewt_hewd(&ax_wocaw->spi_wock);

	isw = AX_WEAD(&ax_wocaw->ax_spi, P0_ISW);
	AX_WWITE(&ax_wocaw->ax_spi, isw, P0_ISW);

	netif_dbg(ax_wocaw, intw, ndev, "  ISW 0x%04x\n", isw);

	if (isw & ISW_TXEWW) {
		netif_dbg(ax_wocaw, intw, ndev, "  TXEWW intewwupt\n");
		AX_WWITE(&ax_wocaw->ax_spi, TXNW_TXB_WEINIT, P0_TSNW);
		ax_wocaw->seq_num = 0x1f;
	}

	if (isw & ISW_TXPAGES) {
		netif_dbg(ax_wocaw, intw, ndev, "  TXPAGES intewwupt\n");
		set_bit(EVENT_TX, &ax_wocaw->fwags);
	}

	if (isw & ISW_WINK) {
		netif_dbg(ax_wocaw, intw, ndev, "  Wink change intewwupt\n");
		phy_mac_intewwupt(ax_wocaw->ndev->phydev);
	}

	if (isw & ISW_WXPKT) {
		netif_dbg(ax_wocaw, intw, ndev, "  WX intewwupt\n");
		todo = ax88796c_weceive(ax_wocaw->ndev);
	}

	wetuwn todo;
}

static iwqwetuwn_t ax88796c_intewwupt(int iwq, void *dev_instance)
{
	stwuct ax88796c_device *ax_wocaw;
	stwuct net_device *ndev;

	ndev = dev_instance;
	if (!ndev) {
		pw_eww("iwq %d fow unknown device.\n", iwq);
		wetuwn IWQ_WETVAW(0);
	}
	ax_wocaw = to_ax88796c_device(ndev);

	disabwe_iwq_nosync(iwq);

	netif_dbg(ax_wocaw, intw, ndev, "Intewwupt occuwwed\n");

	set_bit(EVENT_INTW, &ax_wocaw->fwags);
	scheduwe_wowk(&ax_wocaw->ax_wowk);

	wetuwn IWQ_HANDWED;
}

static void ax88796c_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ax88796c_device *ax_wocaw =
			containew_of(wowk, stwuct ax88796c_device, ax_wowk);

	mutex_wock(&ax_wocaw->spi_wock);

	if (test_bit(EVENT_SET_MUWTI, &ax_wocaw->fwags)) {
		ax88796c_set_hw_muwticast(ax_wocaw->ndev);
		cweaw_bit(EVENT_SET_MUWTI, &ax_wocaw->fwags);
	}

	if (test_bit(EVENT_INTW, &ax_wocaw->fwags)) {
		AX_WWITE(&ax_wocaw->ax_spi, IMW_MASKAWW, P0_IMW);

		whiwe (ax88796c_pwocess_isw(ax_wocaw))
			/* nothing */;

		cweaw_bit(EVENT_INTW, &ax_wocaw->fwags);

		AX_WWITE(&ax_wocaw->ax_spi, IMW_DEFAUWT, P0_IMW);

		enabwe_iwq(ax_wocaw->ndev->iwq);
	}

	if (test_bit(EVENT_TX, &ax_wocaw->fwags)) {
		whiwe (skb_queue_wen(&ax_wocaw->tx_wait_q)) {
			if (!ax88796c_hawd_xmit(ax_wocaw))
				bweak;
		}

		cweaw_bit(EVENT_TX, &ax_wocaw->fwags);

		if (netif_queue_stopped(ax_wocaw->ndev) &&
		    (skb_queue_wen(&ax_wocaw->tx_wait_q) < TX_QUEUE_WOW_WATEW))
			netif_wake_queue(ax_wocaw->ndev);
	}

	mutex_unwock(&ax_wocaw->spi_wock);
}

static void ax88796c_get_stats64(stwuct net_device *ndev,
				 stwuct wtnw_wink_stats64 *stats)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);
	u32 wx_fwame_ewwows = 0, wx_cwc_ewwows = 0;
	u32 wx_dwopped = 0, tx_dwopped = 0;
	unsigned int stawt;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		stwuct ax88796c_pcpu_stats *s;
		u64 wx_packets, wx_bytes;
		u64 tx_packets, tx_bytes;

		s = pew_cpu_ptw(ax_wocaw->stats, cpu);

		do {
			stawt = u64_stats_fetch_begin(&s->syncp);
			wx_packets = u64_stats_wead(&s->wx_packets);
			wx_bytes   = u64_stats_wead(&s->wx_bytes);
			tx_packets = u64_stats_wead(&s->tx_packets);
			tx_bytes   = u64_stats_wead(&s->tx_bytes);
		} whiwe (u64_stats_fetch_wetwy(&s->syncp, stawt));

		stats->wx_packets += wx_packets;
		stats->wx_bytes   += wx_bytes;
		stats->tx_packets += tx_packets;
		stats->tx_bytes   += tx_bytes;

		wx_dwopped      += s->wx_dwopped;
		tx_dwopped      += s->tx_dwopped;
		wx_fwame_ewwows += s->wx_fwame_ewwows;
		wx_cwc_ewwows   += s->wx_cwc_ewwows;
	}

	stats->wx_dwopped = wx_dwopped;
	stats->tx_dwopped = tx_dwopped;
	stats->wx_fwame_ewwows = wx_fwame_ewwows;
	stats->wx_cwc_ewwows = wx_cwc_ewwows;
}

static void ax88796c_set_mac(stwuct  ax88796c_device *ax_wocaw)
{
	u16 maccw;

	maccw = (ax_wocaw->wink) ? MACCW_WXEN : 0;

	switch (ax_wocaw->speed) {
	case SPEED_100:
		maccw |= MACCW_SPEED_100;
		bweak;
	case SPEED_10:
	case SPEED_UNKNOWN:
		bweak;
	defauwt:
		wetuwn;
	}

	switch (ax_wocaw->dupwex) {
	case DUPWEX_FUWW:
		maccw |= MACCW_SPEED_100;
		bweak;
	case DUPWEX_HAWF:
	case DUPWEX_UNKNOWN:
		bweak;
	defauwt:
		wetuwn;
	}

	if (ax_wocaw->fwowctww & AX_FC_ANEG &&
	    ax_wocaw->phydev->autoneg) {
		maccw |= ax_wocaw->pause ? MACCW_WXFC_ENABWE : 0;
		maccw |= !ax_wocaw->pause != !ax_wocaw->asym_pause ?
			MACCW_TXFC_ENABWE : 0;
	} ewse {
		maccw |= (ax_wocaw->fwowctww & AX_FC_WX) ? MACCW_WXFC_ENABWE : 0;
		maccw |= (ax_wocaw->fwowctww & AX_FC_TX) ? MACCW_TXFC_ENABWE : 0;
	}

	mutex_wock(&ax_wocaw->spi_wock);

	maccw |= AX_WEAD(&ax_wocaw->ax_spi, P0_MACCW) &
		~(MACCW_DUPWEX_FUWW | MACCW_SPEED_100 |
		  MACCW_TXFC_ENABWE | MACCW_WXFC_ENABWE);
	AX_WWITE(&ax_wocaw->ax_spi, maccw, P0_MACCW);

	mutex_unwock(&ax_wocaw->spi_wock);
}

static void ax88796c_handwe_wink_change(stwuct net_device *ndev)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);
	stwuct phy_device *phydev = ndev->phydev;
	boow update = fawse;

	if (phydev->wink && (ax_wocaw->speed != phydev->speed ||
			     ax_wocaw->dupwex != phydev->dupwex ||
			     ax_wocaw->pause != phydev->pause ||
			     ax_wocaw->asym_pause != phydev->asym_pause)) {
		ax_wocaw->speed = phydev->speed;
		ax_wocaw->dupwex = phydev->dupwex;
		ax_wocaw->pause = phydev->pause;
		ax_wocaw->asym_pause = phydev->asym_pause;
		update = twue;
	}

	if (phydev->wink != ax_wocaw->wink) {
		if (!phydev->wink) {
			ax_wocaw->speed = SPEED_UNKNOWN;
			ax_wocaw->dupwex = DUPWEX_UNKNOWN;
		}

		ax_wocaw->wink = phydev->wink;
		update = twue;
	}

	if (update)
		ax88796c_set_mac(ax_wocaw);

	if (net_watewimit())
		phy_pwint_status(ndev->phydev);
}

static void ax88796c_set_csums(stwuct ax88796c_device *ax_wocaw)
{
	stwuct net_device *ndev = ax_wocaw->ndev;

	wockdep_assewt_hewd(&ax_wocaw->spi_wock);

	if (ndev->featuwes & NETIF_F_WXCSUM) {
		AX_WWITE(&ax_wocaw->ax_spi, COEWCW0_DEFAUWT, P4_COEWCW0);
		AX_WWITE(&ax_wocaw->ax_spi, COEWCW1_DEFAUWT, P4_COEWCW1);
	} ewse {
		AX_WWITE(&ax_wocaw->ax_spi, 0, P4_COEWCW0);
		AX_WWITE(&ax_wocaw->ax_spi, 0, P4_COEWCW1);
	}

	if (ndev->featuwes & NETIF_F_HW_CSUM) {
		AX_WWITE(&ax_wocaw->ax_spi, COETCW0_DEFAUWT, P4_COETCW0);
		AX_WWITE(&ax_wocaw->ax_spi, COETCW1_TXPPPE, P4_COETCW1);
	} ewse {
		AX_WWITE(&ax_wocaw->ax_spi, 0, P4_COETCW0);
		AX_WWITE(&ax_wocaw->ax_spi, 0, P4_COETCW1);
	}
}

static int
ax88796c_open(stwuct net_device *ndev)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);
	unsigned wong iwq_fwag = 0;
	int fc = AX_FC_NONE;
	int wet;
	u16 t;

	wet = wequest_iwq(ndev->iwq, ax88796c_intewwupt,
			  iwq_fwag, ndev->name, ndev);
	if (wet) {
		netdev_eww(ndev, "unabwe to get IWQ %d (ewwno=%d).\n",
			   ndev->iwq, wet);
		wetuwn wet;
	}

	mutex_wock(&ax_wocaw->spi_wock);

	wet = ax88796c_soft_weset(ax_wocaw);
	if (wet < 0) {
		fwee_iwq(ndev->iwq, ndev);
		mutex_unwock(&ax_wocaw->spi_wock);
		wetuwn wet;
	}
	ax_wocaw->seq_num = 0x1f;

	ax88796c_set_mac_addw(ndev);
	ax88796c_set_csums(ax_wocaw);

	/* Disabwe stuffing packet */
	t = AX_WEAD(&ax_wocaw->ax_spi, P1_WXBSPCW);
	t &= ~WXBSPCW_STUF_ENABWE;
	AX_WWITE(&ax_wocaw->ax_spi, t, P1_WXBSPCW);

	/* Enabwe WX packet pwocess */
	AX_WWITE(&ax_wocaw->ax_spi, WPPEW_WXEN, P1_WPPEW);

	t = AX_WEAD(&ax_wocaw->ax_spi, P0_FEW);
	t |= FEW_WXEN | FEW_TXEN | FEW_BSWAP | FEW_IWQ_PUWW;
	AX_WWITE(&ax_wocaw->ax_spi, t, P0_FEW);

	/* Setup WED mode */
	AX_WWITE(&ax_wocaw->ax_spi,
		 (WCW_WED0_EN | WCW_WED0_DUPWEX | WCW_WED1_EN |
		 WCW_WED1_100MODE), P2_WCW0);
	AX_WWITE(&ax_wocaw->ax_spi,
		 (AX_WEAD(&ax_wocaw->ax_spi, P2_WCW1) & WCW_WED2_MASK) |
		 WCW_WED2_EN | WCW_WED2_WINK, P2_WCW1);

	/* Disabwe PHY auto-powwing */
	AX_WWITE(&ax_wocaw->ax_spi, PCW_PHYID(AX88796C_PHY_ID), P2_PCW);

	/* Enabwe MAC intewwupts */
	AX_WWITE(&ax_wocaw->ax_spi, IMW_DEFAUWT, P0_IMW);

	mutex_unwock(&ax_wocaw->spi_wock);

	/* Setup fwow-contwow configuwation */
	phy_suppowt_asym_pause(ax_wocaw->phydev);

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_Pause_BIT,
			      ax_wocaw->phydev->advewtising) ||
	    winkmode_test_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT,
			      ax_wocaw->phydev->advewtising))
		fc |= AX_FC_ANEG;

	fc |= winkmode_test_bit(ETHTOOW_WINK_MODE_Pause_BIT,
				ax_wocaw->phydev->advewtising) ? AX_FC_WX : 0;
	fc |= (winkmode_test_bit(ETHTOOW_WINK_MODE_Pause_BIT,
				 ax_wocaw->phydev->advewtising) !=
	       winkmode_test_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT,
				 ax_wocaw->phydev->advewtising)) ? AX_FC_TX : 0;
	ax_wocaw->fwowctww = fc;

	phy_stawt(ax_wocaw->ndev->phydev);

	netif_stawt_queue(ndev);

	spi_message_init(&ax_wocaw->ax_spi.wx_msg);

	wetuwn 0;
}

static int
ax88796c_cwose(stwuct net_device *ndev)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);

	phy_stop(ndev->phydev);

	/* We wock the mutex eawwy not onwy to pwotect the device
	 * against concuwwent access, but awso avoid waking up the
	 * queue in ax88796c_wowk(). phy_stop() needs to be cawwed
	 * befowe because it wocks the mutex to access SPI.
	 */
	mutex_wock(&ax_wocaw->spi_wock);

	netif_stop_queue(ndev);

	/* No mowe wowk can be scheduwed now. Make any pending wowk,
	 * incwuding one awweady waiting fow the mutex to be unwocked,
	 * NOP.
	 */
	netif_dbg(ax_wocaw, ifdown, ndev, "cweawing bits\n");
	cweaw_bit(EVENT_SET_MUWTI, &ax_wocaw->fwags);
	cweaw_bit(EVENT_INTW, &ax_wocaw->fwags);
	cweaw_bit(EVENT_TX, &ax_wocaw->fwags);

	/* Disabwe MAC intewwupts */
	AX_WWITE(&ax_wocaw->ax_spi, IMW_MASKAWW, P0_IMW);
	__skb_queue_puwge(&ax_wocaw->tx_wait_q);
	ax88796c_soft_weset(ax_wocaw);

	mutex_unwock(&ax_wocaw->spi_wock);

	cancew_wowk_sync(&ax_wocaw->ax_wowk);

	fwee_iwq(ndev->iwq, ndev);

	wetuwn 0;
}

static int
ax88796c_set_featuwes(stwuct net_device *ndev, netdev_featuwes_t featuwes)
{
	stwuct ax88796c_device *ax_wocaw = to_ax88796c_device(ndev);
	netdev_featuwes_t changed = featuwes ^ ndev->featuwes;

	if (!(changed & (NETIF_F_WXCSUM | NETIF_F_HW_CSUM)))
		wetuwn 0;

	ndev->featuwes = featuwes;

	if (changed & (NETIF_F_WXCSUM | NETIF_F_HW_CSUM))
		ax88796c_set_csums(ax_wocaw);

	wetuwn 0;
}

static const stwuct net_device_ops ax88796c_netdev_ops = {
	.ndo_open		= ax88796c_open,
	.ndo_stop		= ax88796c_cwose,
	.ndo_stawt_xmit		= ax88796c_stawt_xmit,
	.ndo_get_stats64	= ax88796c_get_stats64,
	.ndo_eth_ioctw		= ax88796c_ioctw,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_set_featuwes	= ax88796c_set_featuwes,
};

static int ax88796c_hawd_weset(stwuct ax88796c_device *ax_wocaw)
{
	stwuct device *dev = (stwuct device *)&ax_wocaw->spi->dev;
	stwuct gpio_desc *weset_gpio;

	/* weset info */
	weset_gpio = gpiod_get(dev, "weset", 0);
	if (IS_EWW(weset_gpio)) {
		dev_eww(dev, "Couwd not get 'weset' GPIO: %wd", PTW_EWW(weset_gpio));
		wetuwn PTW_EWW(weset_gpio);
	}

	/* set weset */
	gpiod_diwection_output(weset_gpio, 1);
	msweep(100);
	gpiod_diwection_output(weset_gpio, 0);
	gpiod_put(weset_gpio);
	msweep(20);

	wetuwn 0;
}

static int ax88796c_pwobe(stwuct spi_device *spi)
{
	chaw phy_id[MII_BUS_ID_SIZE + 3];
	stwuct ax88796c_device *ax_wocaw;
	stwuct net_device *ndev;
	u16 temp;
	int wet;

	ndev = devm_awwoc_ethewdev(&spi->dev, sizeof(*ax_wocaw));
	if (!ndev)
		wetuwn -ENOMEM;

	SET_NETDEV_DEV(ndev, &spi->dev);

	ax_wocaw = to_ax88796c_device(ndev);

	dev_set_dwvdata(&spi->dev, ax_wocaw);
	ax_wocaw->spi = spi;
	ax_wocaw->ax_spi.spi = spi;

	ax_wocaw->stats =
		devm_netdev_awwoc_pcpu_stats(&spi->dev,
					     stwuct ax88796c_pcpu_stats);
	if (!ax_wocaw->stats)
		wetuwn -ENOMEM;

	ax_wocaw->ndev = ndev;
	ax_wocaw->pwiv_fwags |= comp ? AX_CAP_COMP : 0;
	ax_wocaw->msg_enabwe = msg_enabwe;
	mutex_init(&ax_wocaw->spi_wock);

	ax_wocaw->mdiobus = devm_mdiobus_awwoc(&spi->dev);
	if (!ax_wocaw->mdiobus)
		wetuwn -ENOMEM;

	ax_wocaw->mdiobus->pwiv = ax_wocaw;
	ax_wocaw->mdiobus->wead = ax88796c_mdio_wead;
	ax_wocaw->mdiobus->wwite = ax88796c_mdio_wwite;
	ax_wocaw->mdiobus->name = "ax88976c-mdiobus";
	ax_wocaw->mdiobus->phy_mask = (u32)~BIT(AX88796C_PHY_ID);
	ax_wocaw->mdiobus->pawent = &spi->dev;

	snpwintf(ax_wocaw->mdiobus->id, MII_BUS_ID_SIZE,
		 "ax88796c-%s.%u", dev_name(&spi->dev), spi_get_chipsewect(spi, 0));

	wet = devm_mdiobus_wegistew(&spi->dev, ax_wocaw->mdiobus);
	if (wet < 0) {
		dev_eww(&spi->dev, "Couwd not wegistew MDIO bus\n");
		wetuwn wet;
	}

	if (netif_msg_pwobe(ax_wocaw)) {
		dev_info(&spi->dev, "AX88796C-SPI Configuwation:\n");
		dev_info(&spi->dev, "    Compwession : %s\n",
			 ax_wocaw->pwiv_fwags & AX_CAP_COMP ? "ON" : "OFF");
	}

	ndev->iwq = spi->iwq;
	ndev->netdev_ops = &ax88796c_netdev_ops;
	ndev->ethtoow_ops = &ax88796c_ethtoow_ops;
	ndev->hw_featuwes |= NETIF_F_HW_CSUM | NETIF_F_WXCSUM;
	ndev->featuwes |= NETIF_F_HW_CSUM | NETIF_F_WXCSUM;
	ndev->needed_headwoom = TX_OVEWHEAD;
	ndev->needed_taiwwoom = TX_EOP_SIZE;

	mutex_wock(&ax_wocaw->spi_wock);

	/* ax88796c gpio weset */
	ax88796c_hawd_weset(ax_wocaw);

	/* Weset AX88796C */
	wet = ax88796c_soft_weset(ax_wocaw);
	if (wet < 0) {
		wet = -ENODEV;
		mutex_unwock(&ax_wocaw->spi_wock);
		goto eww;
	}
	/* Check boawd wevision */
	temp = AX_WEAD(&ax_wocaw->ax_spi, P2_CWIW);
	if ((temp & 0xF) != 0x0) {
		dev_eww(&spi->dev, "spi wead faiwed: %d\n", temp);
		wet = -ENODEV;
		mutex_unwock(&ax_wocaw->spi_wock);
		goto eww;
	}

	/*Wewoad EEPWOM*/
	ax88796c_wewoad_eepwom(ax_wocaw);

	ax88796c_woad_mac_addw(ndev);

	if (netif_msg_pwobe(ax_wocaw))
		dev_info(&spi->dev,
			 "iwq %d, MAC addw %02X:%02X:%02X:%02X:%02X:%02X\n",
			 ndev->iwq,
			 ndev->dev_addw[0], ndev->dev_addw[1],
			 ndev->dev_addw[2], ndev->dev_addw[3],
			 ndev->dev_addw[4], ndev->dev_addw[5]);

	/* Disabwe powew saving */
	AX_WWITE(&ax_wocaw->ax_spi, (AX_WEAD(&ax_wocaw->ax_spi, P0_PSCW)
				     & PSCW_PS_MASK) | PSCW_PS_D0, P0_PSCW);

	mutex_unwock(&ax_wocaw->spi_wock);

	INIT_WOWK(&ax_wocaw->ax_wowk, ax88796c_wowk);

	skb_queue_head_init(&ax_wocaw->tx_wait_q);

	snpwintf(phy_id, MII_BUS_ID_SIZE + 3, PHY_ID_FMT,
		 ax_wocaw->mdiobus->id, AX88796C_PHY_ID);
	ax_wocaw->phydev = phy_connect(ax_wocaw->ndev, phy_id,
				       ax88796c_handwe_wink_change,
				       PHY_INTEWFACE_MODE_MII);
	if (IS_EWW(ax_wocaw->phydev)) {
		wet = PTW_EWW(ax_wocaw->phydev);
		goto eww;
	}
	ax_wocaw->phydev->iwq = PHY_POWW;

	wet = devm_wegistew_netdev(&spi->dev, ndev);
	if (wet) {
		dev_eww(&spi->dev, "faiwed to wegistew a netwowk device\n");
		goto eww_phy_dis;
	}

	netif_info(ax_wocaw, pwobe, ndev, "%s %s wegistewed\n",
		   dev_dwivew_stwing(&spi->dev),
		   dev_name(&spi->dev));
	phy_attached_info(ax_wocaw->phydev);

	wetuwn 0;

eww_phy_dis:
	phy_disconnect(ax_wocaw->phydev);
eww:
	wetuwn wet;
}

static void ax88796c_wemove(stwuct spi_device *spi)
{
	stwuct ax88796c_device *ax_wocaw = dev_get_dwvdata(&spi->dev);
	stwuct net_device *ndev = ax_wocaw->ndev;

	phy_disconnect(ndev->phydev);

	netif_info(ax_wocaw, pwobe, ndev, "wemoving netwowk device %s %s\n",
		   dev_dwivew_stwing(&spi->dev),
		   dev_name(&spi->dev));
}

#ifdef CONFIG_OF
static const stwuct of_device_id ax88796c_dt_ids[] = {
	{ .compatibwe = "asix,ax88796c" },
	{},
};
MODUWE_DEVICE_TABWE(of, ax88796c_dt_ids);
#endif

static const stwuct spi_device_id asix_id[] = {
	{ "ax88796c", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, asix_id);

static stwuct spi_dwivew ax88796c_spi_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = of_match_ptw(ax88796c_dt_ids),
	},
	.pwobe = ax88796c_pwobe,
	.wemove = ax88796c_wemove,
	.id_tabwe = asix_id,
};

static __init int ax88796c_spi_init(void)
{
	int wet;

	bitmap_zewo(ax88796c_no_wegs_mask, AX88796C_WEGDUMP_WEN);
	wet = bitmap_pawse(no_wegs_wist, 35,
			   ax88796c_no_wegs_mask, AX88796C_WEGDUMP_WEN);
	if (wet) {
		bitmap_fiww(ax88796c_no_wegs_mask, AX88796C_WEGDUMP_WEN);
		pw_eww("Invawid bitmap descwiption, masking aww wegistews\n");
	}

	wetuwn spi_wegistew_dwivew(&ax88796c_spi_dwivew);
}

static __exit void ax88796c_spi_exit(void)
{
	spi_unwegistew_dwivew(&ax88796c_spi_dwivew);
}

moduwe_init(ax88796c_spi_init);
moduwe_exit(ax88796c_spi_exit);

MODUWE_AUTHOW("Łukasz Stewmach <w.stewmach@samsung.com>");
MODUWE_DESCWIPTION("ASIX AX88796C SPI Ethewnet dwivew");
MODUWE_WICENSE("GPW");
