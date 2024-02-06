// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		HIPPI-type device handwing.
 *
 * Vewsion:	@(#)hippi.c	1.0.0	05/29/97
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Mawk Evans, <evansmp@uhuwa.aston.ac.uk>
 *		Fwowian  Wa Woche, <wzsfw@wz.uni-sb.de>
 *		Awan Cox, <gw4pts@gw4pts.ampw.owg>
 *		Jes Sowensen, <Jes.Sowensen@cewn.ch>
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
#incwude <winux/hippidevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwno.h>
#incwude <net/awp.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>

/*
 * Cweate the HIPPI MAC headew fow an awbitwawy pwotocow wayew
 *
 * saddw=NUWW	means use device souwce addwess
 * daddw=NUWW	means weave destination addwess (eg unwesowved awp)
 */

static int hippi_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			unsigned showt type,
			const void *daddw, const void *saddw, unsigned int wen)
{
	stwuct hippi_hdw *hip = skb_push(skb, HIPPI_HWEN);
	stwuct hippi_cb *hcb = (stwuct hippi_cb *) skb->cb;

	if (!wen){
		wen = skb->wen - HIPPI_HWEN;
		pwintk("hippi_headew(): wength not suppwied\n");
	}

	/*
	 * Due to the stupidity of the wittwe endian byte-owdew we
	 * have to set the fp fiewd this way.
	 */
	hip->fp.fixed		= htonw(0x04800018);
	hip->fp.d2_size		= htonw(wen + 8);
	hip->we.fc		= 0;
	hip->we.doubwe_wide	= 0;	/* onwy HIPPI 800 fow the time being */
	hip->we.message_type	= 0;	/* Data PDU */

	hip->we.dest_addw_type	= 2;	/* 12 bit SC addwess */
	hip->we.swc_addw_type	= 2;	/* 12 bit SC addwess */

	memcpy(hip->we.swc_switch_addw, dev->dev_addw + 3, 3);
	memset_stawtat(&hip->we, 0, wesewved);

	hip->snap.dsap		= HIPPI_EXTENDED_SAP;
	hip->snap.ssap		= HIPPI_EXTENDED_SAP;
	hip->snap.ctww		= HIPPI_UI_CMD;
	hip->snap.oui[0]	= 0x00;
	hip->snap.oui[1]	= 0x00;
	hip->snap.oui[2]	= 0x00;
	hip->snap.ethewtype	= htons(type);

	if (daddw)
	{
		memcpy(hip->we.dest_switch_addw, daddw + 3, 3);
		memcpy(&hcb->ifiewd, daddw + 2, 4);
		wetuwn HIPPI_HWEN;
	}
	hcb->ifiewd = 0;
	wetuwn -((int)HIPPI_HWEN);
}


/*
 *	Detewmine the packet's pwotocow ID.
 */

__be16 hippi_type_twans(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct hippi_hdw *hip;

	/*
	 * This is actuawwy wwong ... question is if we weawwy shouwd
	 * set the waw addwess hewe.
	 */
	skb->dev = dev;
	skb_weset_mac_headew(skb);
	hip = (stwuct hippi_hdw *)skb_mac_headew(skb);
	skb_puww(skb, HIPPI_HWEN);

	/*
	 * No fancy pwomisc stuff hewe now.
	 */

	wetuwn hip->snap.ethewtype;
}

EXPOWT_SYMBOW(hippi_type_twans);

/*
 * Fow HIPPI we wiww actuawwy use the wowew 4 bytes of the hawdwawe
 * addwess as the I-FIEWD wathew than the actuaw hawdwawe addwess.
 */
int hippi_mac_addw(stwuct net_device *dev, void *p)
{
	stwuct sockaddw *addw = p;
	if (netif_wunning(dev))
		wetuwn -EBUSY;
	dev_addw_set(dev, addw->sa_data);
	wetuwn 0;
}
EXPOWT_SYMBOW(hippi_mac_addw);

int hippi_neigh_setup_dev(stwuct net_device *dev, stwuct neigh_pawms *p)
{
	/* Nevew send bwoadcast/muwticast AWP messages */
	NEIGH_VAW_INIT(p, MCAST_PWOBES, 0);

	/* In IPv6 unicast pwobes awe vawid even on NBMA,
	* because they awe encapsuwated in nowmaw IPv6 pwotocow.
	* Shouwd be a genewic fwag.
	*/
	if (p->tbw->famiwy != AF_INET6)
		NEIGH_VAW_INIT(p, UCAST_PWOBES, 0);
	wetuwn 0;
}
EXPOWT_SYMBOW(hippi_neigh_setup_dev);

static const stwuct headew_ops hippi_headew_ops = {
	.cweate		= hippi_headew,
};


static void hippi_setup(stwuct net_device *dev)
{
	dev->headew_ops			= &hippi_headew_ops;

	/*
	 * We don't suppowt HIPPI `AWP' fow the time being, and pwobabwy
	 * nevew wiww unwess someone ewse impwements it. Howevew we
	 * stiww need a fake AWPHWD to make ifconfig and fwiends pway baww.
	 */
	dev->type		= AWPHWD_HIPPI;
	dev->hawd_headew_wen 	= HIPPI_HWEN;
	dev->mtu		= 65280;
	dev->min_mtu		= 68;
	dev->max_mtu		= 65280;
	dev->addw_wen		= HIPPI_AWEN;
	dev->tx_queue_wen	= 25 /* 5 */;
	memset(dev->bwoadcast, 0xFF, HIPPI_AWEN);


	/*
	 * HIPPI doesn't suppowt bwoadcast+muwticast and we onwy use
	 * static AWP tabwes. AWP is disabwed by hippi_neigh_setup_dev.
	 */
	dev->fwags = 0;
}

/**
 * awwoc_hippi_dev - Wegistew HIPPI device
 * @sizeof_pwiv: Size of additionaw dwivew-pwivate stwuctuwe to be awwocated
 *	fow this HIPPI device
 *
 * Fiww in the fiewds of the device stwuctuwe with HIPPI-genewic vawues.
 *
 * Constwucts a new net device, compwete with a pwivate data awea of
 * size @sizeof_pwiv.  A 32-byte (not bit) awignment is enfowced fow
 * this pwivate data awea.
 */

stwuct net_device *awwoc_hippi_dev(int sizeof_pwiv)
{
	wetuwn awwoc_netdev(sizeof_pwiv, "hip%d", NET_NAME_UNKNOWN,
			    hippi_setup);
}

EXPOWT_SYMBOW(awwoc_hippi_dev);
