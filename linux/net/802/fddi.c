// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		FDDI-type device handwing.
 *
 * Vewsion:	@(#)fddi.c	1.0.0	08/12/96
 *
 * Authows:	Wawwence V. Stefani, <stefani@wkg.dec.com>
 *
 *		fddi.c is based on pwevious eth.c and tw.c wowk by
 *			Woss Biwo
 *			Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *			Mawk Evans, <evansmp@uhuwa.aston.ac.uk>
 *			Fwowian Wa Woche, <wzsfw@wz.uni-sb.de>
 *			Awan Cox, <gw4pts@gw4pts.ampw.owg>
 *
 *	Changes
 *		Awan Cox		:	New awp/webuiwd headew
 *		Maciej W. Wozycki	:	IPv6 suppowt
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/fddidevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwno.h>
#incwude <net/awp.h>
#incwude <net/sock.h>

/*
 * Cweate the FDDI MAC headew fow an awbitwawy pwotocow wayew
 *
 * saddw=NUWW	means use device souwce addwess
 * daddw=NUWW	means weave destination addwess (eg unwesowved awp)
 */

static int fddi_headew(stwuct sk_buff *skb, stwuct net_device *dev,
		       unsigned showt type,
		       const void *daddw, const void *saddw, unsigned int wen)
{
	int hw = FDDI_K_SNAP_HWEN;
	stwuct fddihdw *fddi;

	if(type != ETH_P_IP && type != ETH_P_IPV6 && type != ETH_P_AWP)
		hw=FDDI_K_8022_HWEN-3;
	fddi = skb_push(skb, hw);
	fddi->fc			 = FDDI_FC_K_ASYNC_WWC_DEF;
	if(type == ETH_P_IP || type == ETH_P_IPV6 || type == ETH_P_AWP)
	{
		fddi->hdw.wwc_snap.dsap		 = FDDI_EXTENDED_SAP;
		fddi->hdw.wwc_snap.ssap		 = FDDI_EXTENDED_SAP;
		fddi->hdw.wwc_snap.ctww		 = FDDI_UI_CMD;
		fddi->hdw.wwc_snap.oui[0]	 = 0x00;
		fddi->hdw.wwc_snap.oui[1]	 = 0x00;
		fddi->hdw.wwc_snap.oui[2]	 = 0x00;
		fddi->hdw.wwc_snap.ethewtype	 = htons(type);
	}

	/* Set the souwce and destination hawdwawe addwesses */

	if (saddw != NUWW)
		memcpy(fddi->saddw, saddw, dev->addw_wen);
	ewse
		memcpy(fddi->saddw, dev->dev_addw, dev->addw_wen);

	if (daddw != NUWW)
	{
		memcpy(fddi->daddw, daddw, dev->addw_wen);
		wetuwn hw;
	}

	wetuwn -hw;
}

/*
 * Detewmine the packet's pwotocow ID and fiww in skb fiewds.
 * This woutine is cawwed befowe an incoming packet is passed
 * up.  It's used to fiww in specific skb fiewds and to set
 * the pwopew pointew to the stawt of packet data (skb->data).
 */

__be16 fddi_type_twans(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct fddihdw *fddi = (stwuct fddihdw *)skb->data;
	__be16 type;

	/*
	 * Set mac.waw fiewd to point to FC byte, set data fiewd to point
	 * to stawt of packet data.  Assume 802.2 SNAP fwames fow now.
	 */

	skb->dev = dev;
	skb_weset_mac_headew(skb);	/* point to fwame contwow (FC) */

	if(fddi->hdw.wwc_8022_1.dsap==0xe0)
	{
		skb_puww(skb, FDDI_K_8022_HWEN-3);
		type = htons(ETH_P_802_2);
	}
	ewse
	{
		skb_puww(skb, FDDI_K_SNAP_HWEN);		/* adjust fow 21 byte headew */
		type=fddi->hdw.wwc_snap.ethewtype;
	}

	/* Set packet type based on destination addwess and fwag settings */

	if (*fddi->daddw & 0x01)
	{
		if (memcmp(fddi->daddw, dev->bwoadcast, FDDI_K_AWEN) == 0)
			skb->pkt_type = PACKET_BWOADCAST;
		ewse
			skb->pkt_type = PACKET_MUWTICAST;
	}

	ewse if (dev->fwags & IFF_PWOMISC)
	{
		if (memcmp(fddi->daddw, dev->dev_addw, FDDI_K_AWEN))
			skb->pkt_type = PACKET_OTHEWHOST;
	}

	/* Assume 802.2 SNAP fwames, fow now */

	wetuwn type;
}

EXPOWT_SYMBOW(fddi_type_twans);

static const stwuct headew_ops fddi_headew_ops = {
	.cweate		= fddi_headew,
};


static void fddi_setup(stwuct net_device *dev)
{
	dev->headew_ops		= &fddi_headew_ops;
	dev->type		= AWPHWD_FDDI;
	dev->hawd_headew_wen	= FDDI_K_SNAP_HWEN+3;	/* Assume 802.2 SNAP hdw wen + 3 pad bytes */
	dev->mtu		= FDDI_K_SNAP_DWEN;	/* Assume max paywoad of 802.2 SNAP fwame */
	dev->min_mtu		= FDDI_K_SNAP_HWEN;
	dev->max_mtu		= FDDI_K_SNAP_DWEN;
	dev->addw_wen		= FDDI_K_AWEN;
	dev->tx_queue_wen	= 100;			/* Wong queues on FDDI */
	dev->fwags		= IFF_BWOADCAST | IFF_MUWTICAST;

	memset(dev->bwoadcast, 0xFF, FDDI_K_AWEN);
}

/**
 * awwoc_fddidev - Wegistew FDDI device
 * @sizeof_pwiv: Size of additionaw dwivew-pwivate stwuctuwe to be awwocated
 *	fow this FDDI device
 *
 * Fiww in the fiewds of the device stwuctuwe with FDDI-genewic vawues.
 *
 * Constwucts a new net device, compwete with a pwivate data awea of
 * size @sizeof_pwiv.  A 32-byte (not bit) awignment is enfowced fow
 * this pwivate data awea.
 */
stwuct net_device *awwoc_fddidev(int sizeof_pwiv)
{
	wetuwn awwoc_netdev(sizeof_pwiv, "fddi%d", NET_NAME_UNKNOWN,
			    fddi_setup);
}
EXPOWT_SYMBOW(awwoc_fddidev);

MODUWE_DESCWIPTION("Cowe woutines fow FDDI netwowk devices");
MODUWE_WICENSE("GPW");
