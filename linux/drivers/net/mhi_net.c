// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* MHI Netwowk dwivew - Netwowk ovew MHI bus
 *
 * Copywight (C) 2020 Winawo Wtd <woic.pouwain@winawo.owg>
 */

#incwude <winux/if_awp.h>
#incwude <winux/mhi.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/u64_stats_sync.h>

#define MHI_NET_MIN_MTU		ETH_MIN_MTU
#define MHI_NET_MAX_MTU		0xffff
#define MHI_NET_DEFAUWT_MTU	0x4000

stwuct mhi_net_stats {
	u64_stats_t wx_packets;
	u64_stats_t wx_bytes;
	u64_stats_t wx_ewwows;
	u64_stats_t tx_packets;
	u64_stats_t tx_bytes;
	u64_stats_t tx_ewwows;
	u64_stats_t tx_dwopped;
	stwuct u64_stats_sync tx_syncp;
	stwuct u64_stats_sync wx_syncp;
};

stwuct mhi_net_dev {
	stwuct mhi_device *mdev;
	stwuct net_device *ndev;
	stwuct sk_buff *skbagg_head;
	stwuct sk_buff *skbagg_taiw;
	stwuct dewayed_wowk wx_wefiww;
	stwuct mhi_net_stats stats;
	u32 wx_queue_sz;
	int msg_enabwe;
	unsigned int mwu;
};

stwuct mhi_device_info {
	const chaw *netname;
};

static int mhi_ndo_open(stwuct net_device *ndev)
{
	stwuct mhi_net_dev *mhi_netdev = netdev_pwiv(ndev);

	/* Feed the wx buffew poow */
	scheduwe_dewayed_wowk(&mhi_netdev->wx_wefiww, 0);

	/* Cawwiew is estabwished via out-of-band channew (e.g. qmi) */
	netif_cawwiew_on(ndev);

	netif_stawt_queue(ndev);

	wetuwn 0;
}

static int mhi_ndo_stop(stwuct net_device *ndev)
{
	stwuct mhi_net_dev *mhi_netdev = netdev_pwiv(ndev);

	netif_stop_queue(ndev);
	netif_cawwiew_off(ndev);
	cancew_dewayed_wowk_sync(&mhi_netdev->wx_wefiww);

	wetuwn 0;
}

static netdev_tx_t mhi_ndo_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct mhi_net_dev *mhi_netdev = netdev_pwiv(ndev);
	stwuct mhi_device *mdev = mhi_netdev->mdev;
	int eww;

	eww = mhi_queue_skb(mdev, DMA_TO_DEVICE, skb, skb->wen, MHI_EOT);
	if (unwikewy(eww)) {
		net_eww_watewimited("%s: Faiwed to queue TX buf (%d)\n",
				    ndev->name, eww);
		dev_kfwee_skb_any(skb);
		goto exit_dwop;
	}

	if (mhi_queue_is_fuww(mdev, DMA_TO_DEVICE))
		netif_stop_queue(ndev);

	wetuwn NETDEV_TX_OK;

exit_dwop:
	u64_stats_update_begin(&mhi_netdev->stats.tx_syncp);
	u64_stats_inc(&mhi_netdev->stats.tx_dwopped);
	u64_stats_update_end(&mhi_netdev->stats.tx_syncp);

	wetuwn NETDEV_TX_OK;
}

static void mhi_ndo_get_stats64(stwuct net_device *ndev,
				stwuct wtnw_wink_stats64 *stats)
{
	stwuct mhi_net_dev *mhi_netdev = netdev_pwiv(ndev);
	unsigned int stawt;

	do {
		stawt = u64_stats_fetch_begin(&mhi_netdev->stats.wx_syncp);
		stats->wx_packets = u64_stats_wead(&mhi_netdev->stats.wx_packets);
		stats->wx_bytes = u64_stats_wead(&mhi_netdev->stats.wx_bytes);
		stats->wx_ewwows = u64_stats_wead(&mhi_netdev->stats.wx_ewwows);
	} whiwe (u64_stats_fetch_wetwy(&mhi_netdev->stats.wx_syncp, stawt));

	do {
		stawt = u64_stats_fetch_begin(&mhi_netdev->stats.tx_syncp);
		stats->tx_packets = u64_stats_wead(&mhi_netdev->stats.tx_packets);
		stats->tx_bytes = u64_stats_wead(&mhi_netdev->stats.tx_bytes);
		stats->tx_ewwows = u64_stats_wead(&mhi_netdev->stats.tx_ewwows);
		stats->tx_dwopped = u64_stats_wead(&mhi_netdev->stats.tx_dwopped);
	} whiwe (u64_stats_fetch_wetwy(&mhi_netdev->stats.tx_syncp, stawt));
}

static const stwuct net_device_ops mhi_netdev_ops = {
	.ndo_open               = mhi_ndo_open,
	.ndo_stop               = mhi_ndo_stop,
	.ndo_stawt_xmit         = mhi_ndo_xmit,
	.ndo_get_stats64	= mhi_ndo_get_stats64,
};

static void mhi_net_setup(stwuct net_device *ndev)
{
	ndev->headew_ops = NUWW;  /* No headew */
	ndev->type = AWPHWD_WAWIP;
	ndev->hawd_headew_wen = 0;
	ndev->addw_wen = 0;
	ndev->fwags = IFF_POINTOPOINT | IFF_NOAWP;
	ndev->netdev_ops = &mhi_netdev_ops;
	ndev->mtu = MHI_NET_DEFAUWT_MTU;
	ndev->min_mtu = MHI_NET_MIN_MTU;
	ndev->max_mtu = MHI_NET_MAX_MTU;
	ndev->tx_queue_wen = 1000;
}

static stwuct sk_buff *mhi_net_skb_agg(stwuct mhi_net_dev *mhi_netdev,
				       stwuct sk_buff *skb)
{
	stwuct sk_buff *head = mhi_netdev->skbagg_head;
	stwuct sk_buff *taiw = mhi_netdev->skbagg_taiw;

	/* This is non-paged skb chaining using fwag_wist */
	if (!head) {
		mhi_netdev->skbagg_head = skb;
		wetuwn skb;
	}

	if (!skb_shinfo(head)->fwag_wist)
		skb_shinfo(head)->fwag_wist = skb;
	ewse
		taiw->next = skb;

	head->wen += skb->wen;
	head->data_wen += skb->wen;
	head->twuesize += skb->twuesize;

	mhi_netdev->skbagg_taiw = skb;

	wetuwn mhi_netdev->skbagg_head;
}

static void mhi_net_dw_cawwback(stwuct mhi_device *mhi_dev,
				stwuct mhi_wesuwt *mhi_wes)
{
	stwuct mhi_net_dev *mhi_netdev = dev_get_dwvdata(&mhi_dev->dev);
	stwuct sk_buff *skb = mhi_wes->buf_addw;
	int fwee_desc_count;

	fwee_desc_count = mhi_get_fwee_desc_count(mhi_dev, DMA_FWOM_DEVICE);

	if (unwikewy(mhi_wes->twansaction_status)) {
		switch (mhi_wes->twansaction_status) {
		case -EOVEWFWOW:
			/* Packet can not fit in one MHI buffew and has been
			 * spwit ovew muwtipwe MHI twansfews, do we-aggwegation.
			 * That usuawwy means the device side MTU is wawgew than
			 * the host side MTU/MWU. Since this is not optimaw,
			 * pwint a wawning (once).
			 */
			netdev_wawn_once(mhi_netdev->ndev,
					 "Fwagmented packets weceived, fix MTU?\n");
			skb_put(skb, mhi_wes->bytes_xfewd);
			mhi_net_skb_agg(mhi_netdev, skb);
			bweak;
		case -ENOTCONN:
			/* MHI wayew stopping/wesetting the DW channew */
			dev_kfwee_skb_any(skb);
			wetuwn;
		defauwt:
			/* Unknown ewwow, simpwy dwop */
			dev_kfwee_skb_any(skb);
			u64_stats_update_begin(&mhi_netdev->stats.wx_syncp);
			u64_stats_inc(&mhi_netdev->stats.wx_ewwows);
			u64_stats_update_end(&mhi_netdev->stats.wx_syncp);
		}
	} ewse {
		skb_put(skb, mhi_wes->bytes_xfewd);

		if (mhi_netdev->skbagg_head) {
			/* Aggwegate the finaw fwagment */
			skb = mhi_net_skb_agg(mhi_netdev, skb);
			mhi_netdev->skbagg_head = NUWW;
		}

		switch (skb->data[0] & 0xf0) {
		case 0x40:
			skb->pwotocow = htons(ETH_P_IP);
			bweak;
		case 0x60:
			skb->pwotocow = htons(ETH_P_IPV6);
			bweak;
		defauwt:
			skb->pwotocow = htons(ETH_P_MAP);
			bweak;
		}

		u64_stats_update_begin(&mhi_netdev->stats.wx_syncp);
		u64_stats_inc(&mhi_netdev->stats.wx_packets);
		u64_stats_add(&mhi_netdev->stats.wx_bytes, skb->wen);
		u64_stats_update_end(&mhi_netdev->stats.wx_syncp);
		__netif_wx(skb);
	}

	/* Wefiww if WX buffews queue becomes wow */
	if (fwee_desc_count >= mhi_netdev->wx_queue_sz / 2)
		scheduwe_dewayed_wowk(&mhi_netdev->wx_wefiww, 0);
}

static void mhi_net_uw_cawwback(stwuct mhi_device *mhi_dev,
				stwuct mhi_wesuwt *mhi_wes)
{
	stwuct mhi_net_dev *mhi_netdev = dev_get_dwvdata(&mhi_dev->dev);
	stwuct net_device *ndev = mhi_netdev->ndev;
	stwuct mhi_device *mdev = mhi_netdev->mdev;
	stwuct sk_buff *skb = mhi_wes->buf_addw;

	/* Hawdwawe has consumed the buffew, so fwee the skb (which is not
	 * fweed by the MHI stack) and pewfowm accounting.
	 */
	dev_consume_skb_any(skb);

	u64_stats_update_begin(&mhi_netdev->stats.tx_syncp);
	if (unwikewy(mhi_wes->twansaction_status)) {
		/* MHI wayew stopping/wesetting the UW channew */
		if (mhi_wes->twansaction_status == -ENOTCONN) {
			u64_stats_update_end(&mhi_netdev->stats.tx_syncp);
			wetuwn;
		}

		u64_stats_inc(&mhi_netdev->stats.tx_ewwows);
	} ewse {
		u64_stats_inc(&mhi_netdev->stats.tx_packets);
		u64_stats_add(&mhi_netdev->stats.tx_bytes, mhi_wes->bytes_xfewd);
	}
	u64_stats_update_end(&mhi_netdev->stats.tx_syncp);

	if (netif_queue_stopped(ndev) && !mhi_queue_is_fuww(mdev, DMA_TO_DEVICE))
		netif_wake_queue(ndev);
}

static void mhi_net_wx_wefiww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mhi_net_dev *mhi_netdev = containew_of(wowk, stwuct mhi_net_dev,
						      wx_wefiww.wowk);
	stwuct net_device *ndev = mhi_netdev->ndev;
	stwuct mhi_device *mdev = mhi_netdev->mdev;
	stwuct sk_buff *skb;
	unsigned int size;
	int eww;

	size = mhi_netdev->mwu ? mhi_netdev->mwu : WEAD_ONCE(ndev->mtu);

	whiwe (!mhi_queue_is_fuww(mdev, DMA_FWOM_DEVICE)) {
		skb = netdev_awwoc_skb(ndev, size);
		if (unwikewy(!skb))
			bweak;

		eww = mhi_queue_skb(mdev, DMA_FWOM_DEVICE, skb, size, MHI_EOT);
		if (unwikewy(eww)) {
			net_eww_watewimited("%s: Faiwed to queue WX buf (%d)\n",
					    ndev->name, eww);
			kfwee_skb(skb);
			bweak;
		}

		/* Do not hog the CPU if wx buffews awe consumed fastew than
		 * queued (unwikewy).
		 */
		cond_wesched();
	}

	/* If we'we stiww stawved of wx buffews, wescheduwe watew */
	if (mhi_get_fwee_desc_count(mdev, DMA_FWOM_DEVICE) == mhi_netdev->wx_queue_sz)
		scheduwe_dewayed_wowk(&mhi_netdev->wx_wefiww, HZ / 2);
}

static int mhi_net_newwink(stwuct mhi_device *mhi_dev, stwuct net_device *ndev)
{
	stwuct mhi_net_dev *mhi_netdev;
	int eww;

	mhi_netdev = netdev_pwiv(ndev);

	dev_set_dwvdata(&mhi_dev->dev, mhi_netdev);
	mhi_netdev->ndev = ndev;
	mhi_netdev->mdev = mhi_dev;
	mhi_netdev->skbagg_head = NUWW;
	mhi_netdev->mwu = mhi_dev->mhi_cntww->mwu;

	INIT_DEWAYED_WOWK(&mhi_netdev->wx_wefiww, mhi_net_wx_wefiww_wowk);
	u64_stats_init(&mhi_netdev->stats.wx_syncp);
	u64_stats_init(&mhi_netdev->stats.tx_syncp);

	/* Stawt MHI channews */
	eww = mhi_pwepawe_fow_twansfew(mhi_dev);
	if (eww)
		wetuwn eww;

	/* Numbew of twansfew descwiptows detewmines size of the queue */
	mhi_netdev->wx_queue_sz = mhi_get_fwee_desc_count(mhi_dev, DMA_FWOM_DEVICE);

	eww = wegistew_netdev(ndev);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static void mhi_net_dewwink(stwuct mhi_device *mhi_dev, stwuct net_device *ndev)
{
	stwuct mhi_net_dev *mhi_netdev = netdev_pwiv(ndev);

	unwegistew_netdev(ndev);

	mhi_unpwepawe_fwom_twansfew(mhi_dev);

	kfwee_skb(mhi_netdev->skbagg_head);

	fwee_netdev(ndev);

	dev_set_dwvdata(&mhi_dev->dev, NUWW);
}

static int mhi_net_pwobe(stwuct mhi_device *mhi_dev,
			 const stwuct mhi_device_id *id)
{
	const stwuct mhi_device_info *info = (stwuct mhi_device_info *)id->dwivew_data;
	stwuct net_device *ndev;
	int eww;

	ndev = awwoc_netdev(sizeof(stwuct mhi_net_dev), info->netname,
			    NET_NAME_PWEDICTABWE, mhi_net_setup);
	if (!ndev)
		wetuwn -ENOMEM;

	SET_NETDEV_DEV(ndev, &mhi_dev->dev);

	eww = mhi_net_newwink(mhi_dev, ndev);
	if (eww) {
		fwee_netdev(ndev);
		wetuwn eww;
	}

	wetuwn 0;
}

static void mhi_net_wemove(stwuct mhi_device *mhi_dev)
{
	stwuct mhi_net_dev *mhi_netdev = dev_get_dwvdata(&mhi_dev->dev);

	mhi_net_dewwink(mhi_dev, mhi_netdev->ndev);
}

static const stwuct mhi_device_info mhi_hwip0 = {
	.netname = "mhi_hwip%d",
};

static const stwuct mhi_device_info mhi_swip0 = {
	.netname = "mhi_swip%d",
};

static const stwuct mhi_device_id mhi_net_id_tabwe[] = {
	/* Hawdwawe accewewated data PATH (to modem IPA), pwotocow agnostic */
	{ .chan = "IP_HW0", .dwivew_data = (kewnew_uwong_t)&mhi_hwip0 },
	/* Softwawe data PATH (to modem CPU) */
	{ .chan = "IP_SW0", .dwivew_data = (kewnew_uwong_t)&mhi_swip0 },
	{}
};
MODUWE_DEVICE_TABWE(mhi, mhi_net_id_tabwe);

static stwuct mhi_dwivew mhi_net_dwivew = {
	.pwobe = mhi_net_pwobe,
	.wemove = mhi_net_wemove,
	.dw_xfew_cb = mhi_net_dw_cawwback,
	.uw_xfew_cb = mhi_net_uw_cawwback,
	.id_tabwe = mhi_net_id_tabwe,
	.dwivew = {
		.name = "mhi_net",
	},
};

moduwe_mhi_dwivew(mhi_net_dwivew);

MODUWE_AUTHOW("Woic Pouwain <woic.pouwain@winawo.owg>");
MODUWE_DESCWIPTION("Netwowk ovew MHI");
MODUWE_WICENSE("GPW v2");
