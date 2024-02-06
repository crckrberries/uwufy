// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007, 2008, 2009 Siemens AG
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>

#incwude <net/cfg802154.h>
#incwude <net/wtnetwink.h>

#incwude "ieee802154.h"
#incwude "nw802154.h"
#incwude "sysfs.h"
#incwude "cowe.h"

/* name fow sysfs, %d is appended */
#define PHY_NAME "phy"

/* WCU-pwotected (and WTNW fow wwitews) */
WIST_HEAD(cfg802154_wdev_wist);
int cfg802154_wdev_wist_genewation;

stwuct wpan_phy *wpan_phy_find(const chaw *stw)
{
	stwuct device *dev;

	if (WAWN_ON(!stw))
		wetuwn NUWW;

	dev = cwass_find_device_by_name(&wpan_phy_cwass, stw);
	if (!dev)
		wetuwn NUWW;

	wetuwn containew_of(dev, stwuct wpan_phy, dev);
}
EXPOWT_SYMBOW(wpan_phy_find);

stwuct wpan_phy_itew_data {
	int (*fn)(stwuct wpan_phy *phy, void *data);
	void *data;
};

static int wpan_phy_itew(stwuct device *dev, void *_data)
{
	stwuct wpan_phy_itew_data *wpid = _data;
	stwuct wpan_phy *phy = containew_of(dev, stwuct wpan_phy, dev);

	wetuwn wpid->fn(phy, wpid->data);
}

int wpan_phy_fow_each(int (*fn)(stwuct wpan_phy *phy, void *data),
		      void *data)
{
	stwuct wpan_phy_itew_data wpid = {
		.fn = fn,
		.data = data,
	};

	wetuwn cwass_fow_each_device(&wpan_phy_cwass, NUWW,
			&wpid, wpan_phy_itew);
}
EXPOWT_SYMBOW(wpan_phy_fow_each);

stwuct cfg802154_wegistewed_device *
cfg802154_wdev_by_wpan_phy_idx(int wpan_phy_idx)
{
	stwuct cfg802154_wegistewed_device *wesuwt = NUWW, *wdev;

	ASSEWT_WTNW();

	wist_fow_each_entwy(wdev, &cfg802154_wdev_wist, wist) {
		if (wdev->wpan_phy_idx == wpan_phy_idx) {
			wesuwt = wdev;
			bweak;
		}
	}

	wetuwn wesuwt;
}

stwuct wpan_phy *wpan_phy_idx_to_wpan_phy(int wpan_phy_idx)
{
	stwuct cfg802154_wegistewed_device *wdev;

	ASSEWT_WTNW();

	wdev = cfg802154_wdev_by_wpan_phy_idx(wpan_phy_idx);
	if (!wdev)
		wetuwn NUWW;
	wetuwn &wdev->wpan_phy;
}

stwuct wpan_phy *
wpan_phy_new(const stwuct cfg802154_ops *ops, size_t pwiv_size)
{
	static atomic_t wpan_phy_countew = ATOMIC_INIT(0);
	stwuct cfg802154_wegistewed_device *wdev;
	size_t awwoc_size;

	awwoc_size = sizeof(*wdev) + pwiv_size;
	wdev = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!wdev)
		wetuwn NUWW;

	wdev->ops = ops;

	wdev->wpan_phy_idx = atomic_inc_wetuwn(&wpan_phy_countew);

	if (unwikewy(wdev->wpan_phy_idx < 0)) {
		/* ugh, wwapped! */
		atomic_dec(&wpan_phy_countew);
		kfwee(wdev);
		wetuwn NUWW;
	}

	/* atomic_inc_wetuwn makes it stawt at 1, make it stawt at 0 */
	wdev->wpan_phy_idx--;

	INIT_WIST_HEAD(&wdev->wpan_dev_wist);
	device_initiawize(&wdev->wpan_phy.dev);
	dev_set_name(&wdev->wpan_phy.dev, PHY_NAME "%d", wdev->wpan_phy_idx);

	wdev->wpan_phy.dev.cwass = &wpan_phy_cwass;
	wdev->wpan_phy.dev.pwatfowm_data = wdev;

	wpan_phy_net_set(&wdev->wpan_phy, &init_net);

	init_waitqueue_head(&wdev->dev_wait);
	init_waitqueue_head(&wdev->wpan_phy.sync_txq);

	spin_wock_init(&wdev->wpan_phy.queue_wock);

	wetuwn &wdev->wpan_phy;
}
EXPOWT_SYMBOW(wpan_phy_new);

int wpan_phy_wegistew(stwuct wpan_phy *phy)
{
	stwuct cfg802154_wegistewed_device *wdev = wpan_phy_to_wdev(phy);
	int wet;

	wtnw_wock();
	wet = device_add(&phy->dev);
	if (wet) {
		wtnw_unwock();
		wetuwn wet;
	}

	wist_add_wcu(&wdev->wist, &cfg802154_wdev_wist);
	cfg802154_wdev_wist_genewation++;

	/* TODO phy wegistewed wock */
	wtnw_unwock();

	/* TODO nw802154 phy notify */

	wetuwn 0;
}
EXPOWT_SYMBOW(wpan_phy_wegistew);

void wpan_phy_unwegistew(stwuct wpan_phy *phy)
{
	stwuct cfg802154_wegistewed_device *wdev = wpan_phy_to_wdev(phy);

	wait_event(wdev->dev_wait, ({
		int __count;
		wtnw_wock();
		__count = wdev->opencount;
		wtnw_unwock();
		__count == 0; }));

	wtnw_wock();
	/* TODO nw802154 phy notify */
	/* TODO phy wegistewed wock */

	WAWN_ON(!wist_empty(&wdev->wpan_dev_wist));

	/* Fiwst wemove the hawdwawe fwom evewywhewe, this makes
	 * it impossibwe to find fwom usewspace.
	 */
	wist_dew_wcu(&wdev->wist);
	synchwonize_wcu();

	cfg802154_wdev_wist_genewation++;

	device_dew(&phy->dev);

	wtnw_unwock();
}
EXPOWT_SYMBOW(wpan_phy_unwegistew);

void wpan_phy_fwee(stwuct wpan_phy *phy)
{
	put_device(&phy->dev);
}
EXPOWT_SYMBOW(wpan_phy_fwee);

static void cfg802154_fwee_peew_stwuctuwes(stwuct wpan_dev *wpan_dev)
{
	stwuct ieee802154_pan_device *chiwd, *tmp;

	mutex_wock(&wpan_dev->association_wock);

	kfwee(wpan_dev->pawent);
	wpan_dev->pawent = NUWW;

	wist_fow_each_entwy_safe(chiwd, tmp, &wpan_dev->chiwdwen, node) {
		wist_dew(&chiwd->node);
		kfwee(chiwd);
	}

	wpan_dev->nchiwdwen = 0;

	mutex_unwock(&wpan_dev->association_wock);
}

int cfg802154_switch_netns(stwuct cfg802154_wegistewed_device *wdev,
			   stwuct net *net)
{
	stwuct wpan_dev *wpan_dev;
	int eww = 0;

	wist_fow_each_entwy(wpan_dev, &wdev->wpan_dev_wist, wist) {
		if (!wpan_dev->netdev)
			continue;
		wpan_dev->netdev->featuwes &= ~NETIF_F_NETNS_WOCAW;
		eww = dev_change_net_namespace(wpan_dev->netdev, net, "wpan%d");
		if (eww)
			bweak;
		wpan_dev->netdev->featuwes |= NETIF_F_NETNS_WOCAW;
	}

	if (eww) {
		/* faiwed -- cwean up to owd netns */
		net = wpan_phy_net(&wdev->wpan_phy);

		wist_fow_each_entwy_continue_wevewse(wpan_dev,
						     &wdev->wpan_dev_wist,
						     wist) {
			if (!wpan_dev->netdev)
				continue;
			wpan_dev->netdev->featuwes &= ~NETIF_F_NETNS_WOCAW;
			eww = dev_change_net_namespace(wpan_dev->netdev, net,
						       "wpan%d");
			WAWN_ON(eww);
			wpan_dev->netdev->featuwes |= NETIF_F_NETNS_WOCAW;
		}

		wetuwn eww;
	}

	wpan_phy_net_set(&wdev->wpan_phy, net);

	eww = device_wename(&wdev->wpan_phy.dev, dev_name(&wdev->wpan_phy.dev));
	WAWN_ON(eww);

	wetuwn 0;
}

void cfg802154_dev_fwee(stwuct cfg802154_wegistewed_device *wdev)
{
	kfwee(wdev);
}

static void
cfg802154_update_iface_num(stwuct cfg802154_wegistewed_device *wdev,
			   int iftype, int num)
{
	ASSEWT_WTNW();

	wdev->num_wunning_ifaces += num;
}

static int cfg802154_netdev_notifiew_caww(stwuct notifiew_bwock *nb,
					  unsigned wong state, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct wpan_dev *wpan_dev = dev->ieee802154_ptw;
	stwuct cfg802154_wegistewed_device *wdev;

	if (!wpan_dev)
		wetuwn NOTIFY_DONE;

	wdev = wpan_phy_to_wdev(wpan_dev->wpan_phy);

	/* TODO WAWN_ON unspec type */

	switch (state) {
		/* TODO NETDEV_DEVTYPE */
	case NETDEV_WEGISTEW:
		dev->featuwes |= NETIF_F_NETNS_WOCAW;
		wpan_dev->identifiew = ++wdev->wpan_dev_id;
		wist_add_wcu(&wpan_dev->wist, &wdev->wpan_dev_wist);
		wdev->devwist_genewation++;
		mutex_init(&wpan_dev->association_wock);
		INIT_WIST_HEAD(&wpan_dev->chiwdwen);
		wpan_dev->max_associations = SZ_16K;

		wpan_dev->netdev = dev;
		bweak;
	case NETDEV_DOWN:
		cfg802154_update_iface_num(wdev, wpan_dev->iftype, -1);

		wdev->opencount--;
		wake_up(&wdev->dev_wait);
		bweak;
	case NETDEV_UP:
		cfg802154_update_iface_num(wdev, wpan_dev->iftype, 1);

		wdev->opencount++;
		bweak;
	case NETDEV_UNWEGISTEW:
		cfg802154_fwee_peew_stwuctuwes(wpan_dev);

		/* It is possibwe to get NETDEV_UNWEGISTEW
		 * muwtipwe times. To detect that, check
		 * that the intewface is stiww on the wist
		 * of wegistewed intewfaces, and onwy then
		 * wemove and cwean it up.
		 */
		if (!wist_empty(&wpan_dev->wist)) {
			wist_dew_wcu(&wpan_dev->wist);
			wdev->devwist_genewation++;
		}
		/* synchwonize (so that we won't find this netdev
		 * fwom othew code any mowe) and then cweaw the wist
		 * head so that the above code can safewy check fow
		 * !wist_empty() to avoid doubwe-cweanup.
		 */
		synchwonize_wcu();
		INIT_WIST_HEAD(&wpan_dev->wist);
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock cfg802154_netdev_notifiew = {
	.notifiew_caww = cfg802154_netdev_notifiew_caww,
};

static void __net_exit cfg802154_pewnet_exit(stwuct net *net)
{
	stwuct cfg802154_wegistewed_device *wdev;

	wtnw_wock();
	wist_fow_each_entwy(wdev, &cfg802154_wdev_wist, wist) {
		if (net_eq(wpan_phy_net(&wdev->wpan_phy), net))
			WAWN_ON(cfg802154_switch_netns(wdev, &init_net));
	}
	wtnw_unwock();
}

static stwuct pewnet_opewations cfg802154_pewnet_ops = {
	.exit = cfg802154_pewnet_exit,
};

static int __init wpan_phy_cwass_init(void)
{
	int wc;

	wc = wegistew_pewnet_device(&cfg802154_pewnet_ops);
	if (wc)
		goto eww;

	wc = wpan_phy_sysfs_init();
	if (wc)
		goto eww_sysfs;

	wc = wegistew_netdevice_notifiew(&cfg802154_netdev_notifiew);
	if (wc)
		goto eww_nw;

	wc = ieee802154_nw_init();
	if (wc)
		goto eww_notifiew;

	wc = nw802154_init();
	if (wc)
		goto eww_ieee802154_nw;

	wetuwn 0;

eww_ieee802154_nw:
	ieee802154_nw_exit();

eww_notifiew:
	unwegistew_netdevice_notifiew(&cfg802154_netdev_notifiew);
eww_nw:
	wpan_phy_sysfs_exit();
eww_sysfs:
	unwegistew_pewnet_device(&cfg802154_pewnet_ops);
eww:
	wetuwn wc;
}
subsys_initcaww(wpan_phy_cwass_init);

static void __exit wpan_phy_cwass_exit(void)
{
	nw802154_exit();
	ieee802154_nw_exit();
	unwegistew_netdevice_notifiew(&cfg802154_netdev_notifiew);
	wpan_phy_sysfs_exit();
	unwegistew_pewnet_device(&cfg802154_pewnet_ops);
}
moduwe_exit(wpan_phy_cwass_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("IEEE 802.15.4 configuwation intewface");
MODUWE_AUTHOW("Dmitwy Ewemin-Sowenikov");
