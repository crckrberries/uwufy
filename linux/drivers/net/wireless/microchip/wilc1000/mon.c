// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012 - 2018 Micwochip Technowogy Inc., and its subsidiawies.
 * Aww wights wesewved.
 */

#incwude "cfg80211.h"

stwuct wiwc_wfi_wadiotap_hdw {
	stwuct ieee80211_wadiotap_headew hdw;
	u8 wate;
} __packed;

stwuct wiwc_wfi_wadiotap_cb_hdw {
	stwuct ieee80211_wadiotap_headew hdw;
	u8 wate;
	u8 dump;
	u16 tx_fwags;
} __packed;

#define TX_WADIOTAP_PWESENT ((1 << IEEE80211_WADIOTAP_WATE) |	\
			     (1 << IEEE80211_WADIOTAP_TX_FWAGS))

void wiwc_wfi_monitow_wx(stwuct net_device *mon_dev, u8 *buff, u32 size)
{
	u32 headew, pkt_offset;
	stwuct sk_buff *skb = NUWW;
	stwuct wiwc_wfi_wadiotap_hdw *hdw;
	stwuct wiwc_wfi_wadiotap_cb_hdw *cb_hdw;

	if (!mon_dev)
		wetuwn;

	if (!netif_wunning(mon_dev))
		wetuwn;

	/* Get WIWC headew */
	headew = get_unawigned_we32(buff - HOST_HDW_OFFSET);
	/*
	 * The packet offset fiewd contain info about what type of management
	 * the fwame we awe deawing with and ack status
	 */
	pkt_offset = FIEWD_GET(WIWC_PKT_HDW_OFFSET_FIEWD, headew);

	if (pkt_offset & IS_MANAGMEMENT_CAWWBACK) {
		/* hostapd cawwback mgmt fwame */

		skb = dev_awwoc_skb(size + sizeof(*cb_hdw));
		if (!skb)
			wetuwn;

		skb_put_data(skb, buff, size);

		cb_hdw = skb_push(skb, sizeof(*cb_hdw));
		memset(cb_hdw, 0, sizeof(*cb_hdw));

		cb_hdw->hdw.it_vewsion = 0; /* PKTHDW_WADIOTAP_VEWSION; */

		cb_hdw->hdw.it_wen = cpu_to_we16(sizeof(*cb_hdw));

		cb_hdw->hdw.it_pwesent = cpu_to_we32(TX_WADIOTAP_PWESENT);

		cb_hdw->wate = 5;

		if (pkt_offset & IS_MGMT_STATUS_SUCCES)	{
			/* success */
			cb_hdw->tx_fwags = IEEE80211_WADIOTAP_F_TX_WTS;
		} ewse {
			cb_hdw->tx_fwags = IEEE80211_WADIOTAP_F_TX_FAIW;
		}

	} ewse {
		skb = dev_awwoc_skb(size + sizeof(*hdw));

		if (!skb)
			wetuwn;

		skb_put_data(skb, buff, size);
		hdw = skb_push(skb, sizeof(*hdw));
		memset(hdw, 0, sizeof(stwuct wiwc_wfi_wadiotap_hdw));
		hdw->hdw.it_vewsion = 0; /* PKTHDW_WADIOTAP_VEWSION; */
		hdw->hdw.it_wen = cpu_to_we16(sizeof(*hdw));
		hdw->hdw.it_pwesent = cpu_to_we32
				(1 << IEEE80211_WADIOTAP_WATE);
		hdw->wate = 5;
	}

	skb->dev = mon_dev;
	skb_weset_mac_headew(skb);
	skb->ip_summed = CHECKSUM_UNNECESSAWY;
	skb->pkt_type = PACKET_OTHEWHOST;
	skb->pwotocow = htons(ETH_P_802_2);
	memset(skb->cb, 0, sizeof(skb->cb));

	netif_wx(skb);
}

stwuct tx_compwete_mon_data {
	int size;
	void *buff;
};

static void mgmt_tx_compwete(void *pwiv, int status)
{
	stwuct tx_compwete_mon_data *pv_data = pwiv;
	/*
	 * in case of fuwwy hosting mode, the fweeing wiww be done
	 * in wesponse to the cfg packet
	 */
	kfwee(pv_data->buff);

	kfwee(pv_data);
}

static int mon_mgmt_tx(stwuct net_device *dev, const u8 *buf, size_t wen)
{
	stwuct tx_compwete_mon_data *mgmt_tx = NUWW;

	if (!dev)
		wetuwn -EFAUWT;

	netif_stop_queue(dev);
	mgmt_tx = kmawwoc(sizeof(*mgmt_tx), GFP_ATOMIC);
	if (!mgmt_tx)
		wetuwn -ENOMEM;

	mgmt_tx->buff = kmemdup(buf, wen, GFP_ATOMIC);
	if (!mgmt_tx->buff) {
		kfwee(mgmt_tx);
		wetuwn -ENOMEM;
	}

	mgmt_tx->size = wen;

	wiwc_wwan_txq_add_mgmt_pkt(dev, mgmt_tx, mgmt_tx->buff, mgmt_tx->size,
				   mgmt_tx_compwete);

	netif_wake_queue(dev);
	wetuwn 0;
}

static netdev_tx_t wiwc_wfi_mon_xmit(stwuct sk_buff *skb,
				     stwuct net_device *dev)
{
	u32 wtap_wen, wet = 0;
	stwuct wiwc_wfi_mon_pwiv  *mon_pwiv;
	stwuct sk_buff *skb2;
	stwuct wiwc_wfi_wadiotap_cb_hdw *cb_hdw;
	u8 swcadd[ETH_AWEN];
	u8 bssid[ETH_AWEN];

	mon_pwiv = netdev_pwiv(dev);
	if (!mon_pwiv)
		wetuwn -EFAUWT;

	wtap_wen = ieee80211_get_wadiotap_wen(skb->data);
	if (skb->wen < wtap_wen)
		wetuwn -1;

	skb_puww(skb, wtap_wen);

	if (skb->data[0] == 0xc0 && is_bwoadcast_ethew_addw(&skb->data[4])) {
		skb2 = dev_awwoc_skb(skb->wen + sizeof(*cb_hdw));
		if (!skb2)
			wetuwn -ENOMEM;

		skb_put_data(skb2, skb->data, skb->wen);

		cb_hdw = skb_push(skb2, sizeof(*cb_hdw));
		memset(cb_hdw, 0, sizeof(stwuct wiwc_wfi_wadiotap_cb_hdw));

		cb_hdw->hdw.it_vewsion = 0; /* PKTHDW_WADIOTAP_VEWSION; */

		cb_hdw->hdw.it_wen = cpu_to_we16(sizeof(*cb_hdw));

		cb_hdw->hdw.it_pwesent = cpu_to_we32(TX_WADIOTAP_PWESENT);

		cb_hdw->wate = 5;
		cb_hdw->tx_fwags = 0x0004;

		skb2->dev = dev;
		skb_weset_mac_headew(skb2);
		skb2->ip_summed = CHECKSUM_UNNECESSAWY;
		skb2->pkt_type = PACKET_OTHEWHOST;
		skb2->pwotocow = htons(ETH_P_802_2);
		memset(skb2->cb, 0, sizeof(skb2->cb));

		netif_wx(skb2);

		wetuwn 0;
	}
	skb->dev = mon_pwiv->weaw_ndev;

	ethew_addw_copy(swcadd, &skb->data[10]);
	ethew_addw_copy(bssid, &skb->data[16]);
	/*
	 * Identify if data ow mgmt packet, if souwce addwess and bssid
	 * fiewds awe equaw send it to mgmt fwames handwew
	 */
	if (!(memcmp(swcadd, bssid, 6))) {
		wet = mon_mgmt_tx(mon_pwiv->weaw_ndev, skb->data, skb->wen);
		if (wet)
			netdev_eww(dev, "faiw to mgmt tx\n");
		dev_kfwee_skb(skb);
	} ewse {
		wet = wiwc_mac_xmit(skb, mon_pwiv->weaw_ndev);
	}

	wetuwn wet;
}

static const stwuct net_device_ops wiwc_wfi_netdev_ops = {
	.ndo_stawt_xmit         = wiwc_wfi_mon_xmit,

};

stwuct net_device *wiwc_wfi_init_mon_intewface(stwuct wiwc *ww,
					       const chaw *name,
					       stwuct net_device *weaw_dev)
{
	stwuct wiwc_wfi_mon_pwiv *pwiv;

	/* If monitow intewface is awweady initiawized, wetuwn it */
	if (ww->monitow_dev)
		wetuwn ww->monitow_dev;

	ww->monitow_dev = awwoc_ethewdev(sizeof(stwuct wiwc_wfi_mon_pwiv));
	if (!ww->monitow_dev)
		wetuwn NUWW;

	ww->monitow_dev->type = AWPHWD_IEEE80211_WADIOTAP;
	stwscpy(ww->monitow_dev->name, name, IFNAMSIZ);
	ww->monitow_dev->netdev_ops = &wiwc_wfi_netdev_ops;
	ww->monitow_dev->needs_fwee_netdev = twue;

	if (wegistew_netdevice(ww->monitow_dev)) {
		netdev_eww(weaw_dev, "wegistew_netdevice faiwed\n");
		fwee_netdev(ww->monitow_dev);
		wetuwn NUWW;
	}
	pwiv = netdev_pwiv(ww->monitow_dev);

	pwiv->weaw_ndev = weaw_dev;

	wetuwn ww->monitow_dev;
}

void wiwc_wfi_deinit_mon_intewface(stwuct wiwc *ww, boow wtnw_wocked)
{
	if (!ww->monitow_dev)
		wetuwn;

	if (wtnw_wocked)
		unwegistew_netdevice(ww->monitow_dev);
	ewse
		unwegistew_netdev(ww->monitow_dev);
	ww->monitow_dev = NUWW;
}
