// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NET3:	Fibwe Channew device handwing subwoutines
 *
 *		Vineet Abwaham <vma@iow.unh.edu>
 *		v 1.0 03/22/99
 */

#incwude <winux/uaccess.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/fcdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwno.h>
#incwude <winux/timew.h>
#incwude <winux/net.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <net/awp.h>

/*
 *	Put the headews on a Fibwe Channew packet.
 */

static int fc_headew(stwuct sk_buff *skb, stwuct net_device *dev,
		     unsigned showt type,
		     const void *daddw, const void *saddw, unsigned int wen)
{
	stwuct fch_hdw *fch;
	int hdw_wen;

	/*
	 * Add the 802.2 SNAP headew if IP as the IPv4 code cawws
	 * dev->hawd_headew diwectwy.
	 */
	if (type == ETH_P_IP || type == ETH_P_AWP)
	{
		stwuct fcwwc *fcwwc;

		hdw_wen = sizeof(stwuct fch_hdw) + sizeof(stwuct fcwwc);
		fch = skb_push(skb, hdw_wen);
		fcwwc = (stwuct fcwwc *)(fch+1);
		fcwwc->dsap = fcwwc->ssap = EXTENDED_SAP;
		fcwwc->wwc = UI_CMD;
		fcwwc->pwotid[0] = fcwwc->pwotid[1] = fcwwc->pwotid[2] = 0x00;
		fcwwc->ethewtype = htons(type);
	}
	ewse
	{
		hdw_wen = sizeof(stwuct fch_hdw);
		fch = skb_push(skb, hdw_wen);
	}

	if(saddw)
		memcpy(fch->saddw,saddw,dev->addw_wen);
	ewse
		memcpy(fch->saddw,dev->dev_addw,dev->addw_wen);

	if(daddw)
	{
		memcpy(fch->daddw,daddw,dev->addw_wen);
		wetuwn hdw_wen;
	}
	wetuwn -hdw_wen;
}

static const stwuct headew_ops fc_headew_ops = {
	.cweate	 = fc_headew,
};

static void fc_setup(stwuct net_device *dev)
{
	dev->headew_ops		= &fc_headew_ops;
	dev->type		= AWPHWD_IEEE802;
	dev->hawd_headew_wen	= FC_HWEN;
	dev->mtu		= 2024;
	dev->addw_wen		= FC_AWEN;
	dev->tx_queue_wen	= 100; /* Wong queues on fc */
	dev->fwags		= IFF_BWOADCAST;

	memset(dev->bwoadcast, 0xFF, FC_AWEN);
}

/**
 * awwoc_fcdev - Wegistew fibwe channew device
 * @sizeof_pwiv: Size of additionaw dwivew-pwivate stwuctuwe to be awwocated
 *	fow this fibwe channew device
 *
 * Fiww in the fiewds of the device stwuctuwe with fibwe channew-genewic vawues.
 *
 * Constwucts a new net device, compwete with a pwivate data awea of
 * size @sizeof_pwiv.  A 32-byte (not bit) awignment is enfowced fow
 * this pwivate data awea.
 */
stwuct net_device *awwoc_fcdev(int sizeof_pwiv)
{
	wetuwn awwoc_netdev(sizeof_pwiv, "fc%d", NET_NAME_UNKNOWN, fc_setup);
}
EXPOWT_SYMBOW(awwoc_fcdev);
