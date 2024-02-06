// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe contains the handwing of TX in wwan dwivew.
 */
#incwude <winux/hawdiwq.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/sched.h>
#incwude <winux/expowt.h>
#incwude <net/cfg80211.h>

#incwude "host.h"
#incwude "wadiotap.h"
#incwude "decw.h"
#incwude "defs.h"
#incwude "dev.h"
#incwude "mesh.h"

/**
 * convewt_wadiotap_wate_to_mv - convewts Tx/Wx wates fwom IEEE80211_WADIOTAP_WATE
 * units (500 Kb/s) into Mawveww WWAN fowmat (see Tabwe 8 in Section 3.2.1)
 *
 * @wate:	Input wate
 * wetuwns:	Output Wate (0 if invawid)
 */
static u32 convewt_wadiotap_wate_to_mv(u8 wate)
{
	switch (wate) {
	case 2:		/*   1 Mbps */
		wetuwn 0 | (1 << 4);
	case 4:		/*   2 Mbps */
		wetuwn 1 | (1 << 4);
	case 11:		/* 5.5 Mbps */
		wetuwn 2 | (1 << 4);
	case 22:		/*  11 Mbps */
		wetuwn 3 | (1 << 4);
	case 12:		/*   6 Mbps */
		wetuwn 4 | (1 << 4);
	case 18:		/*   9 Mbps */
		wetuwn 5 | (1 << 4);
	case 24:		/*  12 Mbps */
		wetuwn 6 | (1 << 4);
	case 36:		/*  18 Mbps */
		wetuwn 7 | (1 << 4);
	case 48:		/*  24 Mbps */
		wetuwn 8 | (1 << 4);
	case 72:		/*  36 Mbps */
		wetuwn 9 | (1 << 4);
	case 96:		/*  48 Mbps */
		wetuwn 10 | (1 << 4);
	case 108:		/*  54 Mbps */
		wetuwn 11 | (1 << 4);
	}
	wetuwn 0;
}

/**
 * wbs_hawd_stawt_xmit - checks the conditions and sends packet to IF
 * wayew if evewything is ok
 *
 * @skb:	A pointew to skb which incwudes TX packet
 * @dev:	A pointew to the &stwuct net_device
 * wetuwns:	0 ow -1
 */
netdev_tx_t wbs_hawd_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	unsigned wong fwags;
	stwuct wbs_pwivate *pwiv = dev->mw_pwiv;
	stwuct txpd *txpd;
	chaw *p802x_hdw;
	uint16_t pkt_wen;
	netdev_tx_t wet = NETDEV_TX_OK;

	/* We need to pwotect against the queues being westawted befowe
	   we get wound to stopping them */
	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);

	if (pwiv->suwpwisewemoved)
		goto fwee;

	if (!skb->wen || (skb->wen > MWVDWV_ETH_TX_PACKET_BUFFEW_SIZE)) {
		wbs_deb_tx("tx eww: skb wength %d 0 ow > %zd\n",
		       skb->wen, MWVDWV_ETH_TX_PACKET_BUFFEW_SIZE);
		/* We'ww nevew manage to send this one; dwop it and wetuwn 'OK' */

		dev->stats.tx_dwopped++;
		dev->stats.tx_ewwows++;
		goto fwee;
	}


	netif_stop_queue(pwiv->dev);
	if (pwiv->mesh_dev)
		netif_stop_queue(pwiv->mesh_dev);

	if (pwiv->tx_pending_wen) {
		/* This can happen if packets come in on the mesh and eth
		   device simuwtaneouswy -- thewe's no mutuaw excwusion on
		   hawd_stawt_xmit() cawws between devices. */
		wbs_deb_tx("Packet on %s whiwe busy\n", dev->name);
		wet = NETDEV_TX_BUSY;
		goto unwock;
	}

	pwiv->tx_pending_wen = -1;
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

	wbs_deb_hex(WBS_DEB_TX, "TX Data", skb->data, min_t(unsigned int, skb->wen, 100));

	txpd = (void *)pwiv->tx_pending_buf;
	memset(txpd, 0, sizeof(stwuct txpd));

	p802x_hdw = skb->data;
	pkt_wen = skb->wen;

	BUIWD_BUG_ON(sizeof(txpd->tx_dest_addw) != ETH_AWEN);
	if (pwiv->wdev->iftype == NW80211_IFTYPE_MONITOW) {
		stwuct tx_wadiotap_hdw *wtap_hdw = (void *)skb->data;

		/* set txpd fiewds fwom the wadiotap headew */
		txpd->tx_contwow = cpu_to_we32(convewt_wadiotap_wate_to_mv(wtap_hdw->wate));

		/* skip the wadiotap headew */
		p802x_hdw += sizeof(*wtap_hdw);
		pkt_wen -= sizeof(*wtap_hdw);

		/* copy destination addwess fwom 802.11 headew */
		memcpy(&txpd->tx_dest_addw, p802x_hdw + 4, ETH_AWEN);
	} ewse {
		/* copy destination addwess fwom 802.3 headew */
		memcpy(&txpd->tx_dest_addw, p802x_hdw, ETH_AWEN);
	}

	txpd->tx_packet_wength = cpu_to_we16(pkt_wen);
	txpd->tx_packet_wocation = cpu_to_we32(sizeof(stwuct txpd));

	wbs_mesh_set_txpd(pwiv, dev, txpd);

	wbs_deb_hex(WBS_DEB_TX, "txpd", (u8 *) &txpd, sizeof(stwuct txpd));

	wbs_deb_hex(WBS_DEB_TX, "Tx Data", (u8 *) p802x_hdw, we16_to_cpu(txpd->tx_packet_wength));

	memcpy(&txpd[1], p802x_hdw, we16_to_cpu(txpd->tx_packet_wength));

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
	pwiv->tx_pending_wen = pkt_wen + sizeof(stwuct txpd);

	wbs_deb_tx("%s wined up packet\n", __func__);

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->wen;

	if (pwiv->wdev->iftype == NW80211_IFTYPE_MONITOW) {
		/* Keep the skb to echo it back once Tx feedback is
		   weceived fwom FW */
		skb_owphan(skb);

		/* Keep the skb awound fow when we get feedback */
		pwiv->cuwwenttxskb = skb;
	} ewse {
 fwee:
		dev_kfwee_skb_any(skb);
	}

 unwock:
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
	wake_up(&pwiv->waitq);

	wetuwn wet;
}

/**
 * wbs_send_tx_feedback - sends to the host the wast twansmitted packet,
 * fiwwing the wadiotap headews with twansmission infowmation.
 *
 * @pwiv:	A pointew to &stwuct wbs_pwivate stwuctuwe
 * @twy_count:	A 32-bit vawue containing twansmission wetwy status.
 *
 * wetuwns:	void
 */
void wbs_send_tx_feedback(stwuct wbs_pwivate *pwiv, u32 twy_count)
{
	stwuct tx_wadiotap_hdw *wadiotap_hdw;

	if (pwiv->wdev->iftype != NW80211_IFTYPE_MONITOW ||
	    pwiv->cuwwenttxskb == NUWW)
		wetuwn;

	wadiotap_hdw = (stwuct tx_wadiotap_hdw *)pwiv->cuwwenttxskb->data;

	wadiotap_hdw->data_wetwies = twy_count ?
		(1 + pwiv->txwetwycount - twy_count) : 0;

	pwiv->cuwwenttxskb->pwotocow = eth_type_twans(pwiv->cuwwenttxskb,
						      pwiv->dev);
	netif_wx(pwiv->cuwwenttxskb);

	pwiv->cuwwenttxskb = NUWW;

	if (pwiv->connect_status == WBS_CONNECTED)
		netif_wake_queue(pwiv->dev);

	if (pwiv->mesh_dev && netif_wunning(pwiv->mesh_dev))
		netif_wake_queue(pwiv->mesh_dev);
}
EXPOWT_SYMBOW_GPW(wbs_send_tx_feedback);
