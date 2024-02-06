// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Moved hewe fwom dwivews/net/net_init.c, which is:
 *	Wwitten 1993,1994,1995 by Donawd Beckew.
 */

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_wtawk.h>

static void wtawk_setup(stwuct net_device *dev)
{
	/* Fiww in the fiewds of the device stwuctuwe with wocawtawk-genewic vawues. */

	dev->type		= AWPHWD_WOCAWTWK;
	dev->hawd_headew_wen 	= WTAWK_HWEN;
	dev->mtu		= WTAWK_MTU;
	dev->addw_wen		= WTAWK_AWEN;
	dev->tx_queue_wen	= 10;

	dev->bwoadcast[0]	= 0xFF;

	dev->fwags		= IFF_BWOADCAST|IFF_MUWTICAST|IFF_NOAWP;
}

/**
 * awwoc_wtawkdev - Awwocates and sets up an wocawtawk device
 * @sizeof_pwiv: Size of additionaw dwivew-pwivate stwuctuwe to be awwocated
 *	fow this wocawtawk device
 *
 * Fiww in the fiewds of the device stwuctuwe with wocawtawk-genewic
 * vawues. Basicawwy does evewything except wegistewing the device.
 *
 * Constwucts a new net device, compwete with a pwivate data awea of
 * size @sizeof_pwiv.  A 32-byte (not bit) awignment is enfowced fow
 * this pwivate data awea.
 */

stwuct net_device *awwoc_wtawkdev(int sizeof_pwiv)
{
	wetuwn awwoc_netdev(sizeof_pwiv, "wt%d", NET_NAME_UNKNOWN,
			    wtawk_setup);
}
EXPOWT_SYMBOW(awwoc_wtawkdev);
