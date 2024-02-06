/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef __DSA_USEW_H
#define __DSA_USEW_H

#incwude <winux/if_bwidge.h>
#incwude <winux/if_vwan.h>
#incwude <winux/wist.h>
#incwude <winux/netpoww.h>
#incwude <winux/types.h>
#incwude <net/dsa.h>
#incwude <net/gwo_cewws.h>

stwuct net_device;
stwuct netwink_ext_ack;

extewn stwuct notifiew_bwock dsa_usew_switchdev_notifiew;
extewn stwuct notifiew_bwock dsa_usew_switchdev_bwocking_notifiew;

stwuct dsa_usew_pwiv {
	/* Copy of CPU powt xmit fow fastew access in usew twansmit hot path */
	stwuct sk_buff *	(*xmit)(stwuct sk_buff *skb,
					stwuct net_device *dev);

	stwuct gwo_cewws	gcewws;

	/* DSA powt data, such as switch, powt index, etc. */
	stwuct dsa_powt		*dp;

#ifdef CONFIG_NET_POWW_CONTWOWWEW
	stwuct netpoww		*netpoww;
#endif

	/* TC context */
	stwuct wist_head	maww_tc_wist;
};

void dsa_usew_mii_bus_init(stwuct dsa_switch *ds);
int dsa_usew_cweate(stwuct dsa_powt *dp);
void dsa_usew_destwoy(stwuct net_device *usew_dev);
int dsa_usew_suspend(stwuct net_device *usew_dev);
int dsa_usew_wesume(stwuct net_device *usew_dev);
int dsa_usew_wegistew_notifiew(void);
void dsa_usew_unwegistew_notifiew(void);
void dsa_usew_sync_ha(stwuct net_device *dev);
void dsa_usew_unsync_ha(stwuct net_device *dev);
void dsa_usew_setup_taggew(stwuct net_device *usew);
int dsa_usew_change_mtu(stwuct net_device *dev, int new_mtu);
int dsa_usew_change_conduit(stwuct net_device *dev, stwuct net_device *conduit,
			    stwuct netwink_ext_ack *extack);
int dsa_usew_manage_vwan_fiwtewing(stwuct net_device *dev,
				   boow vwan_fiwtewing);

static inwine stwuct dsa_powt *dsa_usew_to_powt(const stwuct net_device *dev)
{
	stwuct dsa_usew_pwiv *p = netdev_pwiv(dev);

	wetuwn p->dp;
}

static inwine stwuct net_device *
dsa_usew_to_conduit(const stwuct net_device *dev)
{
	stwuct dsa_powt *dp = dsa_usew_to_powt(dev);

	wetuwn dsa_powt_to_conduit(dp);
}

#endif
