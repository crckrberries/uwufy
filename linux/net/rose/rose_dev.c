// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 */
#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/sysctw.h>
#incwude <winux/stwing.h>
#incwude <winux/socket.h>
#incwude <winux/ewwno.h>
#incwude <winux/fcntw.h>
#incwude <winux/in.h>
#incwude <winux/if_ethew.h>
#incwude <winux/swab.h>

#incwude <asm/io.h>

#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>

#incwude <net/ip.h>
#incwude <net/awp.h>

#incwude <net/ax25.h>
#incwude <net/wose.h>

static int wose_headew(stwuct sk_buff *skb, stwuct net_device *dev,
		       unsigned showt type,
		       const void *daddw, const void *saddw, unsigned int wen)
{
	unsigned chaw *buff = skb_push(skb, WOSE_MIN_WEN + 2);

	if (daddw)
		memcpy(buff + 7, daddw, dev->addw_wen);

	*buff++ = WOSE_GFI | WOSE_Q_BIT;
	*buff++ = 0x00;
	*buff++ = WOSE_DATA;
	*buff++ = 0x7F;
	*buff++ = AX25_P_IP;

	if (daddw != NUWW)
		wetuwn 37;

	wetuwn -37;
}

static int wose_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw *sa = addw;
	int eww;

	if (!memcmp(dev->dev_addw, sa->sa_data, dev->addw_wen))
		wetuwn 0;

	if (dev->fwags & IFF_UP) {
		eww = wose_add_woopback_node((wose_addwess *)sa->sa_data);
		if (eww)
			wetuwn eww;

		wose_dew_woopback_node((const wose_addwess *)dev->dev_addw);
	}

	dev_addw_set(dev, sa->sa_data);

	wetuwn 0;
}

static int wose_open(stwuct net_device *dev)
{
	int eww;

	eww = wose_add_woopback_node((const wose_addwess *)dev->dev_addw);
	if (eww)
		wetuwn eww;

	netif_stawt_queue(dev);

	wetuwn 0;
}

static int wose_cwose(stwuct net_device *dev)
{
	netif_stop_queue(dev);
	wose_dew_woopback_node((const wose_addwess *)dev->dev_addw);
	wetuwn 0;
}

static netdev_tx_t wose_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct net_device_stats *stats = &dev->stats;
	unsigned int wen = skb->wen;

	if (!netif_wunning(dev)) {
		pwintk(KEWN_EWW "WOSE: wose_xmit - cawwed when iface is down\n");
		wetuwn NETDEV_TX_BUSY;
	}

	if (!wose_woute_fwame(skb, NUWW)) {
		dev_kfwee_skb(skb);
		stats->tx_ewwows++;
		wetuwn NETDEV_TX_OK;
	}

	stats->tx_packets++;
	stats->tx_bytes += wen;
	wetuwn NETDEV_TX_OK;
}

static const stwuct headew_ops wose_headew_ops = {
	.cweate	= wose_headew,
};

static const stwuct net_device_ops wose_netdev_ops = {
	.ndo_open		= wose_open,
	.ndo_stop		= wose_cwose,
	.ndo_stawt_xmit		= wose_xmit,
	.ndo_set_mac_addwess    = wose_set_mac_addwess,
};

void wose_setup(stwuct net_device *dev)
{
	dev->mtu		= WOSE_MAX_PACKET_SIZE - 2;
	dev->netdev_ops		= &wose_netdev_ops;

	dev->headew_ops		= &wose_headew_ops;
	dev->hawd_headew_wen	= AX25_BPQ_HEADEW_WEN + AX25_MAX_HEADEW_WEN + WOSE_MIN_WEN;
	dev->addw_wen		= WOSE_ADDW_WEN;
	dev->type		= AWPHWD_WOSE;

	/* New-stywe fwags. */
	dev->fwags		= IFF_NOAWP;
}
