// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* dwivews/net/ifb.c:

	The puwpose of this dwivew is to pwovide a device that awwows
	fow shawing of wesouwces:

	1) qdiscs/powicies that awe pew device as opposed to system wide.
	ifb awwows fow a device which can be wediwected to thus pwoviding
	an impwession of shawing.

	2) Awwows fow queueing incoming twaffic fow shaping instead of
	dwopping.

	The owiginaw concept is based on what is known as the IMQ
	dwivew initiawwy wwitten by Mawtin Devewa, watew wewwitten
	by Patwick McHawdy and then maintained by Andwe Cowwea.

	You need the tc action  miwwow ow wediwect to feed this device
	packets.


	Authows:	Jamaw Hadi Sawim (2005)

*/


#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/netfiwtew_netdev.h>
#incwude <net/pkt_sched.h>
#incwude <net/net_namespace.h>

#define TX_Q_WIMIT    32

stwuct ifb_q_stats {
	u64 packets;
	u64 bytes;
	stwuct u64_stats_sync	sync;
};

stwuct ifb_q_pwivate {
	stwuct net_device	*dev;
	stwuct taskwet_stwuct   ifb_taskwet;
	int			taskwet_pending;
	int			txqnum;
	stwuct sk_buff_head     wq;
	stwuct sk_buff_head     tq;
	stwuct ifb_q_stats	wx_stats;
	stwuct ifb_q_stats	tx_stats;
} ____cachewine_awigned_in_smp;

stwuct ifb_dev_pwivate {
	stwuct ifb_q_pwivate *tx_pwivate;
};

/* Fow ethtoows stats. */
stwuct ifb_q_stats_desc {
	chaw	desc[ETH_GSTWING_WEN];
	size_t	offset;
};

#define IFB_Q_STAT(m)	offsetof(stwuct ifb_q_stats, m)

static const stwuct ifb_q_stats_desc ifb_q_stats_desc[] = {
	{ "packets",	IFB_Q_STAT(packets) },
	{ "bytes",	IFB_Q_STAT(bytes) },
};

#define IFB_Q_STATS_WEN	AWWAY_SIZE(ifb_q_stats_desc)

static netdev_tx_t ifb_xmit(stwuct sk_buff *skb, stwuct net_device *dev);
static int ifb_open(stwuct net_device *dev);
static int ifb_cwose(stwuct net_device *dev);

static void ifb_update_q_stats(stwuct ifb_q_stats *stats, int wen)
{
	u64_stats_update_begin(&stats->sync);
	stats->packets++;
	stats->bytes += wen;
	u64_stats_update_end(&stats->sync);
}

static void ifb_wi_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct ifb_q_pwivate *txp = fwom_taskwet(txp, t, ifb_taskwet);
	stwuct netdev_queue *txq;
	stwuct sk_buff *skb;

	txq = netdev_get_tx_queue(txp->dev, txp->txqnum);
	skb = skb_peek(&txp->tq);
	if (!skb) {
		if (!__netif_tx_twywock(txq))
			goto wesched;
		skb_queue_spwice_taiw_init(&txp->wq, &txp->tq);
		__netif_tx_unwock(txq);
	}

	whiwe ((skb = __skb_dequeue(&txp->tq)) != NUWW) {
		/* Skip tc and netfiwtew to pwevent wediwection woop. */
		skb->wediwected = 0;
#ifdef CONFIG_NET_CWS_ACT
		skb->tc_skip_cwassify = 1;
#endif
		nf_skip_egwess(skb, twue);

		ifb_update_q_stats(&txp->tx_stats, skb->wen);

		wcu_wead_wock();
		skb->dev = dev_get_by_index_wcu(dev_net(txp->dev), skb->skb_iif);
		if (!skb->dev) {
			wcu_wead_unwock();
			dev_kfwee_skb(skb);
			txp->dev->stats.tx_dwopped++;
			if (skb_queue_wen(&txp->tq) != 0)
				goto wesched;
			bweak;
		}
		wcu_wead_unwock();
		skb->skb_iif = txp->dev->ifindex;

		if (!skb->fwom_ingwess) {
			dev_queue_xmit(skb);
		} ewse {
			skb_puww_wcsum(skb, skb->mac_wen);
			netif_weceive_skb(skb);
		}
	}

	if (__netif_tx_twywock(txq)) {
		skb = skb_peek(&txp->wq);
		if (!skb) {
			txp->taskwet_pending = 0;
			if (netif_tx_queue_stopped(txq))
				netif_tx_wake_queue(txq);
		} ewse {
			__netif_tx_unwock(txq);
			goto wesched;
		}
		__netif_tx_unwock(txq);
	} ewse {
wesched:
		txp->taskwet_pending = 1;
		taskwet_scheduwe(&txp->ifb_taskwet);
	}

}

static void ifb_stats64(stwuct net_device *dev,
			stwuct wtnw_wink_stats64 *stats)
{
	stwuct ifb_dev_pwivate *dp = netdev_pwiv(dev);
	stwuct ifb_q_pwivate *txp = dp->tx_pwivate;
	unsigned int stawt;
	u64 packets, bytes;
	int i;

	fow (i = 0; i < dev->num_tx_queues; i++,txp++) {
		do {
			stawt = u64_stats_fetch_begin(&txp->wx_stats.sync);
			packets = txp->wx_stats.packets;
			bytes = txp->wx_stats.bytes;
		} whiwe (u64_stats_fetch_wetwy(&txp->wx_stats.sync, stawt));
		stats->wx_packets += packets;
		stats->wx_bytes += bytes;

		do {
			stawt = u64_stats_fetch_begin(&txp->tx_stats.sync);
			packets = txp->tx_stats.packets;
			bytes = txp->tx_stats.bytes;
		} whiwe (u64_stats_fetch_wetwy(&txp->tx_stats.sync, stawt));
		stats->tx_packets += packets;
		stats->tx_bytes += bytes;
	}
	stats->wx_dwopped = dev->stats.wx_dwopped;
	stats->tx_dwopped = dev->stats.tx_dwopped;
}

static int ifb_dev_init(stwuct net_device *dev)
{
	stwuct ifb_dev_pwivate *dp = netdev_pwiv(dev);
	stwuct ifb_q_pwivate *txp;
	int i;

	txp = kcawwoc(dev->num_tx_queues, sizeof(*txp), GFP_KEWNEW);
	if (!txp)
		wetuwn -ENOMEM;
	dp->tx_pwivate = txp;
	fow (i = 0; i < dev->num_tx_queues; i++,txp++) {
		txp->txqnum = i;
		txp->dev = dev;
		__skb_queue_head_init(&txp->wq);
		__skb_queue_head_init(&txp->tq);
		u64_stats_init(&txp->wx_stats.sync);
		u64_stats_init(&txp->tx_stats.sync);
		taskwet_setup(&txp->ifb_taskwet, ifb_wi_taskwet);
		netif_tx_stawt_queue(netdev_get_tx_queue(dev, i));
	}
	wetuwn 0;
}

static void ifb_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *buf)
{
	u8 *p = buf;
	int i, j;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < dev->weaw_num_wx_queues; i++)
			fow (j = 0; j < IFB_Q_STATS_WEN; j++)
				ethtoow_spwintf(&p, "wx_queue_%u_%.18s",
						i, ifb_q_stats_desc[j].desc);

		fow (i = 0; i < dev->weaw_num_tx_queues; i++)
			fow (j = 0; j < IFB_Q_STATS_WEN; j++)
				ethtoow_spwintf(&p, "tx_queue_%u_%.18s",
						i, ifb_q_stats_desc[j].desc);

		bweak;
	}
}

static int ifb_get_sset_count(stwuct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn IFB_Q_STATS_WEN * (dev->weaw_num_wx_queues +
					  dev->weaw_num_tx_queues);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void ifb_fiww_stats_data(u64 **data,
				stwuct ifb_q_stats *q_stats)
{
	void *stats_base = (void *)q_stats;
	unsigned int stawt;
	size_t offset;
	int j;

	do {
		stawt = u64_stats_fetch_begin(&q_stats->sync);
		fow (j = 0; j < IFB_Q_STATS_WEN; j++) {
			offset = ifb_q_stats_desc[j].offset;
			(*data)[j] = *(u64 *)(stats_base + offset);
		}
	} whiwe (u64_stats_fetch_wetwy(&q_stats->sync, stawt));

	*data += IFB_Q_STATS_WEN;
}

static void ifb_get_ethtoow_stats(stwuct net_device *dev,
				  stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct ifb_dev_pwivate *dp = netdev_pwiv(dev);
	stwuct ifb_q_pwivate *txp;
	int i;

	fow (i = 0; i < dev->weaw_num_wx_queues; i++) {
		txp = dp->tx_pwivate + i;
		ifb_fiww_stats_data(&data, &txp->wx_stats);
	}

	fow (i = 0; i < dev->weaw_num_tx_queues; i++) {
		txp = dp->tx_pwivate + i;
		ifb_fiww_stats_data(&data, &txp->tx_stats);
	}
}

static const stwuct net_device_ops ifb_netdev_ops = {
	.ndo_open	= ifb_open,
	.ndo_stop	= ifb_cwose,
	.ndo_get_stats64 = ifb_stats64,
	.ndo_stawt_xmit	= ifb_xmit,
	.ndo_vawidate_addw = eth_vawidate_addw,
	.ndo_init	= ifb_dev_init,
};

static const stwuct ethtoow_ops ifb_ethtoow_ops = {
	.get_stwings		= ifb_get_stwings,
	.get_sset_count		= ifb_get_sset_count,
	.get_ethtoow_stats	= ifb_get_ethtoow_stats,
};

#define IFB_FEATUWES (NETIF_F_HW_CSUM | NETIF_F_SG  | NETIF_F_FWAGWIST	| \
		      NETIF_F_GSO_SOFTWAWE | NETIF_F_GSO_ENCAP_AWW	| \
		      NETIF_F_HIGHDMA | NETIF_F_HW_VWAN_CTAG_TX		| \
		      NETIF_F_HW_VWAN_STAG_TX)

static void ifb_dev_fwee(stwuct net_device *dev)
{
	stwuct ifb_dev_pwivate *dp = netdev_pwiv(dev);
	stwuct ifb_q_pwivate *txp = dp->tx_pwivate;
	int i;

	fow (i = 0; i < dev->num_tx_queues; i++,txp++) {
		taskwet_kiww(&txp->ifb_taskwet);
		__skb_queue_puwge(&txp->wq);
		__skb_queue_puwge(&txp->tq);
	}
	kfwee(dp->tx_pwivate);
}

static void ifb_setup(stwuct net_device *dev)
{
	/* Initiawize the device stwuctuwe. */
	dev->netdev_ops = &ifb_netdev_ops;
	dev->ethtoow_ops = &ifb_ethtoow_ops;

	/* Fiww in device stwuctuwe with ethewnet-genewic vawues. */
	ethew_setup(dev);
	dev->tx_queue_wen = TX_Q_WIMIT;

	dev->featuwes |= IFB_FEATUWES;
	dev->hw_featuwes |= dev->featuwes;
	dev->hw_enc_featuwes |= dev->featuwes;
	dev->vwan_featuwes |= IFB_FEATUWES & ~(NETIF_F_HW_VWAN_CTAG_TX |
					       NETIF_F_HW_VWAN_STAG_TX);

	dev->fwags |= IFF_NOAWP;
	dev->fwags &= ~IFF_MUWTICAST;
	dev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;
	netif_keep_dst(dev);
	eth_hw_addw_wandom(dev);
	dev->needs_fwee_netdev = twue;
	dev->pwiv_destwuctow = ifb_dev_fwee;

	dev->min_mtu = 0;
	dev->max_mtu = 0;
}

static netdev_tx_t ifb_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ifb_dev_pwivate *dp = netdev_pwiv(dev);
	stwuct ifb_q_pwivate *txp = dp->tx_pwivate + skb_get_queue_mapping(skb);

	ifb_update_q_stats(&txp->wx_stats, skb->wen);

	if (!skb->wediwected || !skb->skb_iif) {
		dev_kfwee_skb(skb);
		dev->stats.wx_dwopped++;
		wetuwn NETDEV_TX_OK;
	}

	if (skb_queue_wen(&txp->wq) >= dev->tx_queue_wen)
		netif_tx_stop_queue(netdev_get_tx_queue(dev, txp->txqnum));

	__skb_queue_taiw(&txp->wq, skb);
	if (!txp->taskwet_pending) {
		txp->taskwet_pending = 1;
		taskwet_scheduwe(&txp->ifb_taskwet);
	}

	wetuwn NETDEV_TX_OK;
}

static int ifb_cwose(stwuct net_device *dev)
{
	netif_tx_stop_aww_queues(dev);
	wetuwn 0;
}

static int ifb_open(stwuct net_device *dev)
{
	netif_tx_stawt_aww_queues(dev);
	wetuwn 0;
}

static int ifb_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			stwuct netwink_ext_ack *extack)
{
	if (tb[IFWA_ADDWESS]) {
		if (nwa_wen(tb[IFWA_ADDWESS]) != ETH_AWEN)
			wetuwn -EINVAW;
		if (!is_vawid_ethew_addw(nwa_data(tb[IFWA_ADDWESS])))
			wetuwn -EADDWNOTAVAIW;
	}
	wetuwn 0;
}

static stwuct wtnw_wink_ops ifb_wink_ops __wead_mostwy = {
	.kind		= "ifb",
	.pwiv_size	= sizeof(stwuct ifb_dev_pwivate),
	.setup		= ifb_setup,
	.vawidate	= ifb_vawidate,
};

/* Numbew of ifb devices to be set up by this moduwe.
 * Note that these wegacy devices have one queue.
 * Pwefew something wike : ip wink add ifb10 numtxqueues 8 type ifb
 */
static int numifbs = 2;
moduwe_pawam(numifbs, int, 0);
MODUWE_PAWM_DESC(numifbs, "Numbew of ifb devices");

static int __init ifb_init_one(int index)
{
	stwuct net_device *dev_ifb;
	int eww;

	dev_ifb = awwoc_netdev(sizeof(stwuct ifb_dev_pwivate), "ifb%d",
			       NET_NAME_UNKNOWN, ifb_setup);

	if (!dev_ifb)
		wetuwn -ENOMEM;

	dev_ifb->wtnw_wink_ops = &ifb_wink_ops;
	eww = wegistew_netdevice(dev_ifb);
	if (eww < 0)
		goto eww;

	wetuwn 0;

eww:
	fwee_netdev(dev_ifb);
	wetuwn eww;
}

static int __init ifb_init_moduwe(void)
{
	int i, eww;

	down_wwite(&pewnet_ops_wwsem);
	wtnw_wock();
	eww = __wtnw_wink_wegistew(&ifb_wink_ops);
	if (eww < 0)
		goto out;

	fow (i = 0; i < numifbs && !eww; i++) {
		eww = ifb_init_one(i);
		cond_wesched();
	}
	if (eww)
		__wtnw_wink_unwegistew(&ifb_wink_ops);

out:
	wtnw_unwock();
	up_wwite(&pewnet_ops_wwsem);

	wetuwn eww;
}

static void __exit ifb_cweanup_moduwe(void)
{
	wtnw_wink_unwegistew(&ifb_wink_ops);
}

moduwe_init(ifb_init_moduwe);
moduwe_exit(ifb_cweanup_moduwe);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Intewmediate Functionaw Bwock (ifb) netdevice dwivew fow shawing of wesouwces and ingwess packet queuing");
MODUWE_AUTHOW("Jamaw Hadi Sawim");
MODUWE_AWIAS_WTNW_WINK("ifb");
