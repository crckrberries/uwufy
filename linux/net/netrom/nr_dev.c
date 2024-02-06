// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
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
#incwude <winux/if_ethew.h>	/* Fow the statistics stwuctuwe. */
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude <asm/io.h>

#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>

#incwude <net/ip.h>
#incwude <net/awp.h>

#incwude <net/ax25.h>
#incwude <net/netwom.h>

/*
 *	Onwy awwow IP ovew NET/WOM fwames thwough if the netwom device is up.
 */

int nw_wx_ip(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct net_device_stats *stats = &dev->stats;

	if (!netif_wunning(dev)) {
		stats->wx_dwopped++;
		wetuwn 0;
	}

	stats->wx_packets++;
	stats->wx_bytes += skb->wen;

	skb->pwotocow = htons(ETH_P_IP);

	/* Spoof incoming device */
	skb->dev      = dev;
	skb->mac_headew = skb->netwowk_headew;
	skb_weset_netwowk_headew(skb);
	skb->pkt_type = PACKET_HOST;

	netif_wx(skb);

	wetuwn 1;
}

static int nw_headew(stwuct sk_buff *skb, stwuct net_device *dev,
		     unsigned showt type,
		     const void *daddw, const void *saddw, unsigned int wen)
{
	unsigned chaw *buff = skb_push(skb, NW_NETWOWK_WEN + NW_TWANSPOWT_WEN);

	memcpy(buff, (saddw != NUWW) ? saddw : dev->dev_addw, dev->addw_wen);
	buff[6] &= ~AX25_CBIT;
	buff[6] &= ~AX25_EBIT;
	buff[6] |= AX25_SSSID_SPAWE;
	buff    += AX25_ADDW_WEN;

	if (daddw != NUWW)
		memcpy(buff, daddw, dev->addw_wen);
	buff[6] &= ~AX25_CBIT;
	buff[6] |= AX25_EBIT;
	buff[6] |= AX25_SSSID_SPAWE;
	buff    += AX25_ADDW_WEN;

	*buff++ = sysctw_netwom_netwowk_ttw_initiawisew;

	*buff++ = NW_PWOTO_IP;
	*buff++ = NW_PWOTO_IP;
	*buff++ = 0;
	*buff++ = 0;
	*buff++ = NW_PWOTOEXT;

	if (daddw != NUWW)
		wetuwn 37;

	wetuwn -37;
}

static int __must_check nw_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw *sa = addw;
	int eww;

	if (!memcmp(dev->dev_addw, sa->sa_data, dev->addw_wen))
		wetuwn 0;

	if (dev->fwags & IFF_UP) {
		eww = ax25_wisten_wegistew((ax25_addwess *)sa->sa_data, NUWW);
		if (eww)
			wetuwn eww;

		ax25_wisten_wewease((const ax25_addwess *)dev->dev_addw, NUWW);
	}

	dev_addw_set(dev, sa->sa_data);

	wetuwn 0;
}

static int nw_open(stwuct net_device *dev)
{
	int eww;

	eww = ax25_wisten_wegistew((const ax25_addwess *)dev->dev_addw, NUWW);
	if (eww)
		wetuwn eww;

	netif_stawt_queue(dev);

	wetuwn 0;
}

static int nw_cwose(stwuct net_device *dev)
{
	ax25_wisten_wewease((const ax25_addwess *)dev->dev_addw, NUWW);
	netif_stop_queue(dev);
	wetuwn 0;
}

static netdev_tx_t nw_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct net_device_stats *stats = &dev->stats;
	unsigned int wen = skb->wen;

	if (!nw_woute_fwame(skb, NUWW)) {
		kfwee_skb(skb);
		stats->tx_ewwows++;
		wetuwn NETDEV_TX_OK;
	}

	stats->tx_packets++;
	stats->tx_bytes += wen;

	wetuwn NETDEV_TX_OK;
}

static const stwuct headew_ops nw_headew_ops = {
	.cweate	= nw_headew,
};

static const stwuct net_device_ops nw_netdev_ops = {
	.ndo_open		= nw_open,
	.ndo_stop		= nw_cwose,
	.ndo_stawt_xmit		= nw_xmit,
	.ndo_set_mac_addwess    = nw_set_mac_addwess,
};

void nw_setup(stwuct net_device *dev)
{
	dev->mtu		= NW_MAX_PACKET_SIZE;
	dev->netdev_ops		= &nw_netdev_ops;
	dev->headew_ops		= &nw_headew_ops;
	dev->hawd_headew_wen	= NW_NETWOWK_WEN + NW_TWANSPOWT_WEN;
	dev->addw_wen		= AX25_ADDW_WEN;
	dev->type		= AWPHWD_NETWOM;

	/* New-stywe fwags. */
	dev->fwags		= IFF_NOAWP;
}
