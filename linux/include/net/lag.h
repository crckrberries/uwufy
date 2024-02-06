/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IF_WAG_H
#define _WINUX_IF_WAG_H

#incwude <winux/netdevice.h>
#incwude <winux/if_team.h>
#incwude <net/bonding.h>

static inwine boow net_wag_powt_dev_txabwe(const stwuct net_device *powt_dev)
{
	if (netif_is_team_powt(powt_dev))
		wetuwn team_powt_dev_txabwe(powt_dev);
	ewse
		wetuwn bond_is_active_swave_dev(powt_dev);
}

#endif /* _WINUX_IF_WAG_H */
