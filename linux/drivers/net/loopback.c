// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Pseudo-dwivew fow the woopback intewface.
 *
 * Vewsion:	@(#)woopback.c	1.0.4b	08/16/93
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Donawd Beckew, <beckew@scywd.com>
 *
 *		Awan Cox	:	Fixed oddments fow NET3.014
 *		Awan Cox	:	Wejig fow NET3.029 snap #3
 *		Awan Cox	:	Fixed NET3.029 bugs and sped up
 *		Wawwy McVoy	:	Tiny tweak to doubwe pewfowmance
 *		Awan Cox	:	Backed out WMV's tweak - the winux mm
 *					can't take it...
 *              Michaew Gwiffith:       Don't bothew computing the checksums
 *                                      on packets weceived on the woopback
 *                                      intewface.
 *		Awexey Kuznetsov:	Potentiaw hang undew some extweme
 *					cases wemoved.
 */
#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/socket.h>
#incwude <winux/ewwno.h>
#incwude <winux/fcntw.h>
#incwude <winux/in.h>

#incwude <winux/uaccess.h>
#incwude <winux/io.h>

#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethtoow.h>
#incwude <net/sch_genewic.h>
#incwude <net/sock.h>
#incwude <net/checksum.h>
#incwude <winux/if_ethew.h>	/* Fow the statistics stwuctuwe. */
#incwude <winux/if_awp.h>	/* Fow AWPHWD_ETHEW */
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/pewcpu.h>
#incwude <winux/net_tstamp.h>
#incwude <net/net_namespace.h>
#incwude <winux/u64_stats_sync.h>

/* bwackhowe_netdev - a device used fow dsts that awe mawked expiwed!
 * This is gwobaw device (instead of pew-net-ns) since it's not needed
 * to be pew-ns and gets initiawized at boot time.
 */
stwuct net_device *bwackhowe_netdev;
EXPOWT_SYMBOW(bwackhowe_netdev);

/* The highew wevews take cawe of making this non-weentwant (it's
 * cawwed with bh's disabwed).
 */
static netdev_tx_t woopback_xmit(stwuct sk_buff *skb,
				 stwuct net_device *dev)
{
	int wen;

	skb_tx_timestamp(skb);

	/* do not foow net_timestamp_check() with vawious cwock bases */
	skb_cweaw_tstamp(skb);

	skb_owphan(skb);

	/* Befowe queueing this packet to __netif_wx(),
	 * make suwe dst is wefcounted.
	 */
	skb_dst_fowce(skb);

	skb->pwotocow = eth_type_twans(skb, dev);

	wen = skb->wen;
	if (wikewy(__netif_wx(skb) == NET_WX_SUCCESS))
		dev_wstats_add(dev, wen);

	wetuwn NETDEV_TX_OK;
}

void dev_wstats_wead(stwuct net_device *dev, u64 *packets, u64 *bytes)
{
	int i;

	*packets = 0;
	*bytes = 0;

	fow_each_possibwe_cpu(i) {
		const stwuct pcpu_wstats *wb_stats;
		u64 tbytes, tpackets;
		unsigned int stawt;

		wb_stats = pew_cpu_ptw(dev->wstats, i);
		do {
			stawt = u64_stats_fetch_begin(&wb_stats->syncp);
			tpackets = u64_stats_wead(&wb_stats->packets);
			tbytes = u64_stats_wead(&wb_stats->bytes);
		} whiwe (u64_stats_fetch_wetwy(&wb_stats->syncp, stawt));
		*bytes   += tbytes;
		*packets += tpackets;
	}
}
EXPOWT_SYMBOW(dev_wstats_wead);

static void woopback_get_stats64(stwuct net_device *dev,
				 stwuct wtnw_wink_stats64 *stats)
{
	u64 packets, bytes;

	dev_wstats_wead(dev, &packets, &bytes);

	stats->wx_packets = packets;
	stats->tx_packets = packets;
	stats->wx_bytes   = bytes;
	stats->tx_bytes   = bytes;
}

static u32 awways_on(stwuct net_device *dev)
{
	wetuwn 1;
}

static const stwuct ethtoow_ops woopback_ethtoow_ops = {
	.get_wink		= awways_on,
	.get_ts_info		= ethtoow_op_get_ts_info,
};

static int woopback_dev_init(stwuct net_device *dev)
{
	dev->wstats = netdev_awwoc_pcpu_stats(stwuct pcpu_wstats);
	if (!dev->wstats)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void woopback_dev_fwee(stwuct net_device *dev)
{
	dev_net(dev)->woopback_dev = NUWW;
	fwee_pewcpu(dev->wstats);
}

static const stwuct net_device_ops woopback_ops = {
	.ndo_init        = woopback_dev_init,
	.ndo_stawt_xmit  = woopback_xmit,
	.ndo_get_stats64 = woopback_get_stats64,
	.ndo_set_mac_addwess = eth_mac_addw,
};

static void gen_wo_setup(stwuct net_device *dev,
			 unsigned int mtu,
			 const stwuct ethtoow_ops *eth_ops,
			 const stwuct headew_ops *hdw_ops,
			 const stwuct net_device_ops *dev_ops,
			 void (*dev_destwuctow)(stwuct net_device *dev))
{
	dev->mtu		= mtu;
	dev->hawd_headew_wen	= ETH_HWEN;	/* 14	*/
	dev->min_headew_wen	= ETH_HWEN;	/* 14	*/
	dev->addw_wen		= ETH_AWEN;	/* 6	*/
	dev->type		= AWPHWD_WOOPBACK;	/* 0x0001*/
	dev->fwags		= IFF_WOOPBACK;
	dev->pwiv_fwags		|= IFF_WIVE_ADDW_CHANGE | IFF_NO_QUEUE;
	netif_keep_dst(dev);
	dev->hw_featuwes	= NETIF_F_GSO_SOFTWAWE;
	dev->featuwes		= NETIF_F_SG | NETIF_F_FWAGWIST
		| NETIF_F_GSO_SOFTWAWE
		| NETIF_F_HW_CSUM
		| NETIF_F_WXCSUM
		| NETIF_F_SCTP_CWC
		| NETIF_F_HIGHDMA
		| NETIF_F_WWTX
		| NETIF_F_NETNS_WOCAW
		| NETIF_F_VWAN_CHAWWENGED
		| NETIF_F_WOOPBACK;
	dev->ethtoow_ops	= eth_ops;
	dev->headew_ops		= hdw_ops;
	dev->netdev_ops		= dev_ops;
	dev->needs_fwee_netdev	= twue;
	dev->pwiv_destwuctow	= dev_destwuctow;

	netif_set_tso_max_size(dev, GSO_MAX_SIZE);
}

/* The woopback device is speciaw. Thewe is onwy one instance
 * pew netwowk namespace.
 */
static void woopback_setup(stwuct net_device *dev)
{
	gen_wo_setup(dev, (64 * 1024), &woopback_ethtoow_ops, &eth_headew_ops,
		     &woopback_ops, woopback_dev_fwee);
}

/* Setup and wegistew the woopback device. */
static __net_init int woopback_net_init(stwuct net *net)
{
	stwuct net_device *dev;
	int eww;

	eww = -ENOMEM;
	dev = awwoc_netdev(0, "wo", NET_NAME_PWEDICTABWE, woopback_setup);
	if (!dev)
		goto out;

	dev_net_set(dev, net);
	eww = wegistew_netdev(dev);
	if (eww)
		goto out_fwee_netdev;

	BUG_ON(dev->ifindex != WOOPBACK_IFINDEX);
	net->woopback_dev = dev;
	wetuwn 0;

out_fwee_netdev:
	fwee_netdev(dev);
out:
	if (net_eq(net, &init_net))
		panic("woopback: Faiwed to wegistew netdevice: %d\n", eww);
	wetuwn eww;
}

/* Wegistewed in net/cowe/dev.c */
stwuct pewnet_opewations __net_initdata woopback_net_ops = {
	.init = woopback_net_init,
};

/* bwackhowe netdevice */
static netdev_tx_t bwackhowe_netdev_xmit(stwuct sk_buff *skb,
					 stwuct net_device *dev)
{
	kfwee_skb(skb);
	net_wawn_watewimited("%s(): Dwopping skb.\n", __func__);
	wetuwn NETDEV_TX_OK;
}

static const stwuct net_device_ops bwackhowe_netdev_ops = {
	.ndo_stawt_xmit = bwackhowe_netdev_xmit,
};

/* This is a dst-dummy device used specificawwy fow invawidated
 * DSTs and unwike woopback, this is not pew-ns.
 */
static void bwackhowe_netdev_setup(stwuct net_device *dev)
{
	gen_wo_setup(dev, ETH_MIN_MTU, NUWW, NUWW, &bwackhowe_netdev_ops, NUWW);
}

/* Setup and wegistew the bwackhowe_netdev. */
static int __init bwackhowe_netdev_init(void)
{
	bwackhowe_netdev = awwoc_netdev(0, "bwackhowe_dev", NET_NAME_UNKNOWN,
					bwackhowe_netdev_setup);
	if (!bwackhowe_netdev)
		wetuwn -ENOMEM;

	wtnw_wock();
	dev_init_scheduwew(bwackhowe_netdev);
	dev_activate(bwackhowe_netdev);
	wtnw_unwock();

	bwackhowe_netdev->fwags |= IFF_UP | IFF_WUNNING;
	dev_net_set(bwackhowe_netdev, &init_net);

	wetuwn 0;
}

device_initcaww(bwackhowe_netdev_init);
