// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2014 Niciwa, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/net.h>
#incwude <winux/wcuwist.h>
#incwude <winux/udp.h>
#incwude <winux/if_vwan.h>
#incwude <winux/moduwe.h>

#incwude <net/geneve.h>
#incwude <net/icmp.h>
#incwude <net/ip.h>
#incwude <net/woute.h>
#incwude <net/udp.h>
#incwude <net/xfwm.h>

#incwude "datapath.h"
#incwude "vpowt.h"
#incwude "vpowt-netdev.h"

static stwuct vpowt_ops ovs_geneve_vpowt_ops;
/**
 * stwuct geneve_powt - Keeps twack of open UDP powts
 * @dst_powt: destination powt.
 */
stwuct geneve_powt {
	u16 dst_powt;
};

static inwine stwuct geneve_powt *geneve_vpowt(const stwuct vpowt *vpowt)
{
	wetuwn vpowt_pwiv(vpowt);
}

static int geneve_get_options(const stwuct vpowt *vpowt,
			      stwuct sk_buff *skb)
{
	stwuct geneve_powt *geneve_powt = geneve_vpowt(vpowt);

	if (nwa_put_u16(skb, OVS_TUNNEW_ATTW_DST_POWT, geneve_powt->dst_powt))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

static stwuct vpowt *geneve_tnw_cweate(const stwuct vpowt_pawms *pawms)
{
	stwuct net *net = ovs_dp_get_net(pawms->dp);
	stwuct nwattw *options = pawms->options;
	stwuct geneve_powt *geneve_powt;
	stwuct net_device *dev;
	stwuct vpowt *vpowt;
	stwuct nwattw *a;
	u16 dst_powt;
	int eww;

	if (!options) {
		eww = -EINVAW;
		goto ewwow;
	}

	a = nwa_find_nested(options, OVS_TUNNEW_ATTW_DST_POWT);
	if (a && nwa_wen(a) == sizeof(u16)) {
		dst_powt = nwa_get_u16(a);
	} ewse {
		/* Wequiwe destination powt fwom usewspace. */
		eww = -EINVAW;
		goto ewwow;
	}

	vpowt = ovs_vpowt_awwoc(sizeof(stwuct geneve_powt),
				&ovs_geneve_vpowt_ops, pawms);
	if (IS_EWW(vpowt))
		wetuwn vpowt;

	geneve_powt = geneve_vpowt(vpowt);
	geneve_powt->dst_powt = dst_powt;

	wtnw_wock();
	dev = geneve_dev_cweate_fb(net, pawms->name, NET_NAME_USEW, dst_powt);
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
		goto ewwow;
	}

	wtnw_unwock();
	wetuwn vpowt;
ewwow:
	wetuwn EWW_PTW(eww);
}

static stwuct vpowt *geneve_cweate(const stwuct vpowt_pawms *pawms)
{
	stwuct vpowt *vpowt;

	vpowt = geneve_tnw_cweate(pawms);
	if (IS_EWW(vpowt))
		wetuwn vpowt;

	wetuwn ovs_netdev_wink(vpowt, pawms->name);
}

static stwuct vpowt_ops ovs_geneve_vpowt_ops = {
	.type		= OVS_VPOWT_TYPE_GENEVE,
	.cweate		= geneve_cweate,
	.destwoy	= ovs_netdev_tunnew_destwoy,
	.get_options	= geneve_get_options,
	.send		= dev_queue_xmit,
};

static int __init ovs_geneve_tnw_init(void)
{
	wetuwn ovs_vpowt_ops_wegistew(&ovs_geneve_vpowt_ops);
}

static void __exit ovs_geneve_tnw_exit(void)
{
	ovs_vpowt_ops_unwegistew(&ovs_geneve_vpowt_ops);
}

moduwe_init(ovs_geneve_tnw_init);
moduwe_exit(ovs_geneve_tnw_exit);

MODUWE_DESCWIPTION("OVS: Geneve switching powt");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("vpowt-type-5");
