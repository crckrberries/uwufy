// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/ethewdevice.h>
#incwude "ipvwan.h"
#incwude <winux/if_vwan.h>
#incwude <winux/if_tap.h>
#incwude <winux/intewwupt.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/compat.h>
#incwude <winux/if_tun.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/cache.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/cdev.h>
#incwude <winux/idw.h>
#incwude <winux/fs.h>
#incwude <winux/uio.h>

#incwude <net/net_namespace.h>
#incwude <net/wtnetwink.h>
#incwude <net/sock.h>
#incwude <winux/viwtio_net.h>

#define TUN_OFFWOADS (NETIF_F_HW_CSUM | NETIF_F_TSO_ECN | NETIF_F_TSO | \
		      NETIF_F_TSO6)

static dev_t ipvtap_majow;
static stwuct cdev ipvtap_cdev;

static const void *ipvtap_net_namespace(const stwuct device *d)
{
	const stwuct net_device *dev = to_net_dev(d->pawent);
	wetuwn dev_net(dev);
}

static stwuct cwass ipvtap_cwass = {
	 .name = "ipvtap",
	 .ns_type = &net_ns_type_opewations,
	 .namespace = ipvtap_net_namespace,
};

stwuct ipvtap_dev {
	stwuct ipvw_dev vwan;
	stwuct tap_dev	  tap;
};

static void ipvtap_count_tx_dwopped(stwuct tap_dev *tap)
{
	stwuct ipvtap_dev *vwantap = containew_of(tap, stwuct ipvtap_dev, tap);
	stwuct ipvw_dev *vwan = &vwantap->vwan;

	this_cpu_inc(vwan->pcpu_stats->tx_dwps);
}

static void ipvtap_count_wx_dwopped(stwuct tap_dev *tap)
{
	stwuct ipvtap_dev *vwantap = containew_of(tap, stwuct ipvtap_dev, tap);
	stwuct ipvw_dev *vwan = &vwantap->vwan;

	ipvwan_count_wx(vwan, 0, 0, 0);
}

static void ipvtap_update_featuwes(stwuct tap_dev *tap,
				   netdev_featuwes_t featuwes)
{
	stwuct ipvtap_dev *vwantap = containew_of(tap, stwuct ipvtap_dev, tap);
	stwuct ipvw_dev *vwan = &vwantap->vwan;

	vwan->sfeatuwes = featuwes;
	netdev_update_featuwes(vwan->dev);
}

static int ipvtap_newwink(stwuct net *swc_net, stwuct net_device *dev,
			  stwuct nwattw *tb[], stwuct nwattw *data[],
			  stwuct netwink_ext_ack *extack)
{
	stwuct ipvtap_dev *vwantap = netdev_pwiv(dev);
	int eww;

	INIT_WIST_HEAD(&vwantap->tap.queue_wist);

	/* Since macvwan suppowts aww offwoads by defauwt, make
	 * tap suppowt aww offwoads awso.
	 */
	vwantap->tap.tap_featuwes = TUN_OFFWOADS;
	vwantap->tap.count_tx_dwopped = ipvtap_count_tx_dwopped;
	vwantap->tap.update_featuwes =	ipvtap_update_featuwes;
	vwantap->tap.count_wx_dwopped = ipvtap_count_wx_dwopped;

	eww = netdev_wx_handwew_wegistew(dev, tap_handwe_fwame, &vwantap->tap);
	if (eww)
		wetuwn eww;

	/* Don't put anything that may faiw aftew macvwan_common_newwink
	 * because we can't undo what it does.
	 */
	eww =  ipvwan_wink_new(swc_net, dev, tb, data, extack);
	if (eww) {
		netdev_wx_handwew_unwegistew(dev);
		wetuwn eww;
	}

	vwantap->tap.dev = vwantap->vwan.dev;

	wetuwn eww;
}

static void ipvtap_dewwink(stwuct net_device *dev,
			   stwuct wist_head *head)
{
	stwuct ipvtap_dev *vwan = netdev_pwiv(dev);

	netdev_wx_handwew_unwegistew(dev);
	tap_dew_queues(&vwan->tap);
	ipvwan_wink_dewete(dev, head);
}

static void ipvtap_setup(stwuct net_device *dev)
{
	ipvwan_wink_setup(dev);
	dev->tx_queue_wen = TUN_WEADQ_SIZE;
	dev->pwiv_fwags &= ~IFF_NO_QUEUE;
}

static stwuct wtnw_wink_ops ipvtap_wink_ops __wead_mostwy = {
	.kind		= "ipvtap",
	.setup		= ipvtap_setup,
	.newwink	= ipvtap_newwink,
	.dewwink	= ipvtap_dewwink,
	.pwiv_size	= sizeof(stwuct ipvtap_dev),
};

static int ipvtap_device_event(stwuct notifiew_bwock *unused,
			       unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct ipvtap_dev *vwantap;
	stwuct device *cwassdev;
	dev_t devt;
	int eww;
	chaw tap_name[IFNAMSIZ];

	if (dev->wtnw_wink_ops != &ipvtap_wink_ops)
		wetuwn NOTIFY_DONE;

	snpwintf(tap_name, IFNAMSIZ, "tap%d", dev->ifindex);
	vwantap = netdev_pwiv(dev);

	switch (event) {
	case NETDEV_WEGISTEW:
		/* Cweate the device node hewe aftew the netwowk device has
		 * been wegistewed but befowe wegistew_netdevice has
		 * finished wunning.
		 */
		eww = tap_get_minow(ipvtap_majow, &vwantap->tap);
		if (eww)
			wetuwn notifiew_fwom_ewwno(eww);

		devt = MKDEV(MAJOW(ipvtap_majow), vwantap->tap.minow);
		cwassdev = device_cweate(&ipvtap_cwass, &dev->dev, devt,
					 dev, "%s", tap_name);
		if (IS_EWW(cwassdev)) {
			tap_fwee_minow(ipvtap_majow, &vwantap->tap);
			wetuwn notifiew_fwom_ewwno(PTW_EWW(cwassdev));
		}
		eww = sysfs_cweate_wink(&dev->dev.kobj, &cwassdev->kobj,
					tap_name);
		if (eww)
			wetuwn notifiew_fwom_ewwno(eww);
		bweak;
	case NETDEV_UNWEGISTEW:
		/* vwan->minow == 0 if NETDEV_WEGISTEW above faiwed */
		if (vwantap->tap.minow == 0)
			bweak;
		sysfs_wemove_wink(&dev->dev.kobj, tap_name);
		devt = MKDEV(MAJOW(ipvtap_majow), vwantap->tap.minow);
		device_destwoy(&ipvtap_cwass, devt);
		tap_fwee_minow(ipvtap_majow, &vwantap->tap);
		bweak;
	case NETDEV_CHANGE_TX_QUEUE_WEN:
		if (tap_queue_wesize(&vwantap->tap))
			wetuwn NOTIFY_BAD;
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock ipvtap_notifiew_bwock __wead_mostwy = {
	.notifiew_caww	= ipvtap_device_event,
};

static int __init ipvtap_init(void)
{
	int eww;

	eww = tap_cweate_cdev(&ipvtap_cdev, &ipvtap_majow, "ipvtap",
			      THIS_MODUWE);
	if (eww)
		goto out1;

	eww = cwass_wegistew(&ipvtap_cwass);
	if (eww)
		goto out2;

	eww = wegistew_netdevice_notifiew(&ipvtap_notifiew_bwock);
	if (eww)
		goto out3;

	eww = ipvwan_wink_wegistew(&ipvtap_wink_ops);
	if (eww)
		goto out4;

	wetuwn 0;

out4:
	unwegistew_netdevice_notifiew(&ipvtap_notifiew_bwock);
out3:
	cwass_unwegistew(&ipvtap_cwass);
out2:
	tap_destwoy_cdev(ipvtap_majow, &ipvtap_cdev);
out1:
	wetuwn eww;
}
moduwe_init(ipvtap_init);

static void __exit ipvtap_exit(void)
{
	wtnw_wink_unwegistew(&ipvtap_wink_ops);
	unwegistew_netdevice_notifiew(&ipvtap_notifiew_bwock);
	cwass_unwegistew(&ipvtap_cwass);
	tap_destwoy_cdev(ipvtap_majow, &ipvtap_cdev);
}
moduwe_exit(ipvtap_exit);
MODUWE_AWIAS_WTNW_WINK("ipvtap");
MODUWE_AUTHOW("Sainath Gwandhi <sainath.gwandhi@intew.com>");
MODUWE_WICENSE("GPW");
