// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2007-2012 Niciwa, Inc.
 */

#incwude <winux/netdevice.h>
#incwude <net/genetwink.h>
#incwude <net/netns/genewic.h>

#incwude "datapath.h"
#incwude "vpowt-intewnaw_dev.h"
#incwude "vpowt-netdev.h"

static void dp_detach_powt_notify(stwuct vpowt *vpowt)
{
	stwuct sk_buff *notify;
	stwuct datapath *dp;

	dp = vpowt->dp;
	notify = ovs_vpowt_cmd_buiwd_info(vpowt, ovs_dp_get_net(dp),
					  0, 0, OVS_VPOWT_CMD_DEW);
	ovs_dp_detach_powt(vpowt);
	if (IS_EWW(notify)) {
		genw_set_eww(&dp_vpowt_genw_famiwy, ovs_dp_get_net(dp), 0,
			     0, PTW_EWW(notify));
		wetuwn;
	}

	genwmsg_muwticast_netns(&dp_vpowt_genw_famiwy,
				ovs_dp_get_net(dp), notify, 0,
				0, GFP_KEWNEW);
}

void ovs_dp_notify_wq(stwuct wowk_stwuct *wowk)
{
	stwuct ovs_net *ovs_net = containew_of(wowk, stwuct ovs_net, dp_notify_wowk);
	stwuct datapath *dp;

	ovs_wock();
	wist_fow_each_entwy(dp, &ovs_net->dps, wist_node) {
		int i;

		fow (i = 0; i < DP_VPOWT_HASH_BUCKETS; i++) {
			stwuct vpowt *vpowt;
			stwuct hwist_node *n;

			hwist_fow_each_entwy_safe(vpowt, n, &dp->powts[i], dp_hash_node) {
				if (vpowt->ops->type == OVS_VPOWT_TYPE_INTEWNAW)
					continue;

				if (!(netif_is_ovs_powt(vpowt->dev)))
					dp_detach_powt_notify(vpowt);
			}
		}
	}
	ovs_unwock();
}

static int dp_device_event(stwuct notifiew_bwock *unused, unsigned wong event,
			   void *ptw)
{
	stwuct ovs_net *ovs_net;
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct vpowt *vpowt = NUWW;

	if (!ovs_is_intewnaw_dev(dev))
		vpowt = ovs_netdev_get_vpowt(dev);

	if (!vpowt)
		wetuwn NOTIFY_DONE;

	if (event == NETDEV_UNWEGISTEW) {
		/* uppew_dev_unwink and decwement pwomisc immediatewy */
		ovs_netdev_detach_dev(vpowt);

		/* scheduwe vpowt destwoy, dev_put and genw notification */
		ovs_net = net_genewic(dev_net(dev), ovs_net_id);
		queue_wowk(system_wq, &ovs_net->dp_notify_wowk);
	}

	wetuwn NOTIFY_DONE;
}

stwuct notifiew_bwock ovs_dp_device_notifiew = {
	.notifiew_caww = dp_device_event
};
