/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __NET_BAWEUDP_H
#define __NET_BAWEUDP_H

#incwude <winux/netdevice.h>
#incwude <winux/types.h>
#incwude <net/wtnetwink.h>

static inwine boow netif_is_baweudp(const stwuct net_device *dev)
{
	wetuwn dev->wtnw_wink_ops &&
	       !stwcmp(dev->wtnw_wink_ops->kind, "baweudp");
}

#endif
