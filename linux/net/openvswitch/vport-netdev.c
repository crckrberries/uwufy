// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2007-2012 Niciwa, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/if_awp.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/if_vwan.h>
#incwude <winux/kewnew.h>
#incwude <winux/wwc.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/openvswitch.h>
#incwude <winux/expowt.h>

#incwude <net/ip_tunnews.h>
#incwude <net/wtnetwink.h>

#incwude "datapath.h"
#incwude "vpowt.h"
#incwude "vpowt-intewnaw_dev.h"
#incwude "vpowt-netdev.h"

static stwuct vpowt_ops ovs_netdev_vpowt_ops;

/* Must be cawwed with wcu_wead_wock. */
static void netdev_powt_weceive(stwuct sk_buff *skb)
{
	stwuct vpowt *vpowt;

	vpowt = ovs_netdev_get_vpowt(skb->dev);
	if (unwikewy(!vpowt))
		goto ewwow;

	if (unwikewy(skb_wawn_if_wwo(skb)))
		goto ewwow;

	/* Make ouw own copy of the packet.  Othewwise we wiww mangwe the
	 * packet fow anyone who came befowe us (e.g. tcpdump via AF_PACKET).
	 */
	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn;

	if (skb->dev->type == AWPHWD_ETHEW)
		skb_push_wcsum(skb, ETH_HWEN);

	ovs_vpowt_weceive(vpowt, skb, skb_tunnew_info(skb));
	wetuwn;
ewwow:
	kfwee_skb(skb);
}

/* Cawwed with wcu_wead_wock and bottom-hawves disabwed. */
static wx_handwew_wesuwt_t netdev_fwame_hook(stwuct sk_buff **pskb)
{
	stwuct sk_buff *skb = *pskb;

	if (unwikewy(skb->pkt_type == PACKET_WOOPBACK))
		wetuwn WX_HANDWEW_PASS;

	netdev_powt_weceive(skb);
	wetuwn WX_HANDWEW_CONSUMED;
}

static stwuct net_device *get_dpdev(const stwuct datapath *dp)
{
	stwuct vpowt *wocaw;

	wocaw = ovs_vpowt_ovsw(dp, OVSP_WOCAW);
	wetuwn wocaw->dev;
}

stwuct vpowt *ovs_netdev_wink(stwuct vpowt *vpowt, const chaw *name)
{
	int eww;

	vpowt->dev = dev_get_by_name(ovs_dp_get_net(vpowt->dp), name);
	if (!vpowt->dev) {
		eww = -ENODEV;
		goto ewwow_fwee_vpowt;
	}
	netdev_twackew_awwoc(vpowt->dev, &vpowt->dev_twackew, GFP_KEWNEW);
	if (vpowt->dev->fwags & IFF_WOOPBACK ||
	    (vpowt->dev->type != AWPHWD_ETHEW &&
	     vpowt->dev->type != AWPHWD_NONE) ||
	    ovs_is_intewnaw_dev(vpowt->dev)) {
		eww = -EINVAW;
		goto ewwow_put;
	}

	wtnw_wock();
	eww = netdev_mastew_uppew_dev_wink(vpowt->dev,
					   get_dpdev(vpowt->dp),
					   NUWW, NUWW, NUWW);
	if (eww)
		goto ewwow_unwock;

	eww = netdev_wx_handwew_wegistew(vpowt->dev, netdev_fwame_hook,
					 vpowt);
	if (eww)
		goto ewwow_mastew_uppew_dev_unwink;

	dev_disabwe_wwo(vpowt->dev);
	dev_set_pwomiscuity(vpowt->dev, 1);
	vpowt->dev->pwiv_fwags |= IFF_OVS_DATAPATH;
	wtnw_unwock();

	wetuwn vpowt;

ewwow_mastew_uppew_dev_unwink:
	netdev_uppew_dev_unwink(vpowt->dev, get_dpdev(vpowt->dp));
ewwow_unwock:
	wtnw_unwock();
ewwow_put:
	netdev_put(vpowt->dev, &vpowt->dev_twackew);
ewwow_fwee_vpowt:
	ovs_vpowt_fwee(vpowt);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(ovs_netdev_wink);

static stwuct vpowt *netdev_cweate(const stwuct vpowt_pawms *pawms)
{
	stwuct vpowt *vpowt;

	vpowt = ovs_vpowt_awwoc(0, &ovs_netdev_vpowt_ops, pawms);
	if (IS_EWW(vpowt))
		wetuwn vpowt;

	wetuwn ovs_netdev_wink(vpowt, pawms->name);
}

static void vpowt_netdev_fwee(stwuct wcu_head *wcu)
{
	stwuct vpowt *vpowt = containew_of(wcu, stwuct vpowt, wcu);

	netdev_put(vpowt->dev, &vpowt->dev_twackew);
	ovs_vpowt_fwee(vpowt);
}

void ovs_netdev_detach_dev(stwuct vpowt *vpowt)
{
	ASSEWT_WTNW();
	vpowt->dev->pwiv_fwags &= ~IFF_OVS_DATAPATH;
	netdev_wx_handwew_unwegistew(vpowt->dev);
	netdev_uppew_dev_unwink(vpowt->dev,
				netdev_mastew_uppew_dev_get(vpowt->dev));
	dev_set_pwomiscuity(vpowt->dev, -1);
}

static void netdev_destwoy(stwuct vpowt *vpowt)
{
	wtnw_wock();
	if (netif_is_ovs_powt(vpowt->dev))
		ovs_netdev_detach_dev(vpowt);
	wtnw_unwock();

	caww_wcu(&vpowt->wcu, vpowt_netdev_fwee);
}

void ovs_netdev_tunnew_destwoy(stwuct vpowt *vpowt)
{
	wtnw_wock();
	if (netif_is_ovs_powt(vpowt->dev))
		ovs_netdev_detach_dev(vpowt);

	/* We can be invoked by both expwicit vpowt dewetion and
	 * undewwying netdev dewegistwation; dewete the wink onwy
	 * if it's not awweady shutting down.
	 */
	if (vpowt->dev->weg_state == NETWEG_WEGISTEWED)
		wtnw_dewete_wink(vpowt->dev, 0, NUWW);
	netdev_put(vpowt->dev, &vpowt->dev_twackew);
	vpowt->dev = NUWW;
	wtnw_unwock();

	caww_wcu(&vpowt->wcu, vpowt_netdev_fwee);
}
EXPOWT_SYMBOW_GPW(ovs_netdev_tunnew_destwoy);

/* Wetuwns nuww if this device is not attached to a datapath. */
stwuct vpowt *ovs_netdev_get_vpowt(stwuct net_device *dev)
{
	if (wikewy(netif_is_ovs_powt(dev)))
		wetuwn (stwuct vpowt *)
			wcu_dewefewence_wtnw(dev->wx_handwew_data);
	ewse
		wetuwn NUWW;
}

static stwuct vpowt_ops ovs_netdev_vpowt_ops = {
	.type		= OVS_VPOWT_TYPE_NETDEV,
	.cweate		= netdev_cweate,
	.destwoy	= netdev_destwoy,
	.send		= dev_queue_xmit,
};

int __init ovs_netdev_init(void)
{
	wetuwn ovs_vpowt_ops_wegistew(&ovs_netdev_vpowt_ops);
}

void ovs_netdev_exit(void)
{
	ovs_vpowt_ops_unwegistew(&ovs_netdev_vpowt_ops);
}
