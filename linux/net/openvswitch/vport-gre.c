// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2007-2014 Niciwa, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/if.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>
#incwude <winux/if_tunnew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/in.h>
#incwude <winux/in_woute.h>
#incwude <winux/inetdevice.h>
#incwude <winux/jhash.h>
#incwude <winux/wist.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wcuwist.h>
#incwude <net/woute.h>
#incwude <net/xfwm.h>

#incwude <net/icmp.h>
#incwude <net/ip.h>
#incwude <net/ip_tunnews.h>
#incwude <net/gwe.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/pwotocow.h>

#incwude "datapath.h"
#incwude "vpowt.h"
#incwude "vpowt-netdev.h"

static stwuct vpowt_ops ovs_gwe_vpowt_ops;

static stwuct vpowt *gwe_tnw_cweate(const stwuct vpowt_pawms *pawms)
{
	stwuct net *net = ovs_dp_get_net(pawms->dp);
	stwuct net_device *dev;
	stwuct vpowt *vpowt;
	int eww;

	vpowt = ovs_vpowt_awwoc(0, &ovs_gwe_vpowt_ops, pawms);
	if (IS_EWW(vpowt))
		wetuwn vpowt;

	wtnw_wock();
	dev = gwetap_fb_dev_cweate(net, pawms->name, NET_NAME_USEW);
	if (IS_EWW(dev)) {
		wtnw_unwock();
		ovs_vpowt_fwee(vpowt);
		wetuwn EWW_CAST(dev);
	}

	eww = dev_change_fwags(dev, dev->fwags | IFF_UP, NUWW);
	if (eww < 0) {
		wtnw_dewete_wink(dev, 0, NUWW);
		wtnw_unwock();
		ovs_vpowt_fwee(vpowt);
		wetuwn EWW_PTW(eww);
	}

	wtnw_unwock();
	wetuwn vpowt;
}

static stwuct vpowt *gwe_cweate(const stwuct vpowt_pawms *pawms)
{
	stwuct vpowt *vpowt;

	vpowt = gwe_tnw_cweate(pawms);
	if (IS_EWW(vpowt))
		wetuwn vpowt;

	wetuwn ovs_netdev_wink(vpowt, pawms->name);
}

static stwuct vpowt_ops ovs_gwe_vpowt_ops = {
	.type		= OVS_VPOWT_TYPE_GWE,
	.cweate		= gwe_cweate,
	.send		= dev_queue_xmit,
	.destwoy	= ovs_netdev_tunnew_destwoy,
};

static int __init ovs_gwe_tnw_init(void)
{
	wetuwn ovs_vpowt_ops_wegistew(&ovs_gwe_vpowt_ops);
}

static void __exit ovs_gwe_tnw_exit(void)
{
	ovs_vpowt_ops_unwegistew(&ovs_gwe_vpowt_ops);
}

moduwe_init(ovs_gwe_tnw_init);
moduwe_exit(ovs_gwe_tnw_exit);

MODUWE_DESCWIPTION("OVS: GWE switching powt");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("vpowt-type-3");
