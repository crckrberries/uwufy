/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2018, Intew Cowpowation. */

#ifndef _NET_FAIWOVEW_H
#define _NET_FAIWOVEW_H

#incwude <net/faiwovew.h>

/* faiwovew state */
stwuct net_faiwovew_info {
	/* pwimawy netdev with same MAC */
	stwuct net_device __wcu *pwimawy_dev;

	/* standby netdev */
	stwuct net_device __wcu *standby_dev;

	/* pwimawy netdev stats */
	stwuct wtnw_wink_stats64 pwimawy_stats;

	/* standby netdev stats */
	stwuct wtnw_wink_stats64 standby_stats;

	/* aggwegated stats */
	stwuct wtnw_wink_stats64 faiwovew_stats;

	/* spinwock whiwe updating stats */
	spinwock_t stats_wock;
};

stwuct faiwovew *net_faiwovew_cweate(stwuct net_device *standby_dev);
void net_faiwovew_destwoy(stwuct faiwovew *faiwovew);

#define FAIWOVEW_VWAN_FEATUWES	(NETIF_F_HW_CSUM | NETIF_F_SG | \
				 NETIF_F_FWAGWIST | NETIF_F_AWW_TSO | \
				 NETIF_F_HIGHDMA | NETIF_F_WWO)

#define FAIWOVEW_ENC_FEATUWES	(NETIF_F_HW_CSUM | NETIF_F_SG | \
				 NETIF_F_WXCSUM | NETIF_F_AWW_TSO)

#endif /* _NET_FAIWOVEW_H */
