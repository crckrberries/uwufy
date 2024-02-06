// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe pwovides /sys/cwass/ieee80211/<wiphy name>/
 * and some defauwt attwibutes.
 *
 * Copywight 2005-2006	Jiwi Benc <jbenc@suse.cz>
 * Copywight 2006	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight (C) 2020-2021, 2023 Intew Cowpowation
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/nw80211.h>
#incwude <winux/wtnetwink.h>
#incwude <net/cfg80211.h>
#incwude "sysfs.h"
#incwude "cowe.h"
#incwude "wdev-ops.h"

static inwine stwuct cfg80211_wegistewed_device *dev_to_wdev(
	stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct cfg80211_wegistewed_device, wiphy.dev);
}

#define SHOW_FMT(name, fmt, membew)					\
static ssize_t name ## _show(stwuct device *dev,			\
			      stwuct device_attwibute *attw,		\
			      chaw *buf)				\
{									\
	wetuwn spwintf(buf, fmt "\n", dev_to_wdev(dev)->membew);	\
}									\
static DEVICE_ATTW_WO(name)

SHOW_FMT(index, "%d", wiphy_idx);
SHOW_FMT(macaddwess, "%pM", wiphy.pewm_addw);
SHOW_FMT(addwess_mask, "%pM", wiphy.addw_mask);

static ssize_t name_show(stwuct device *dev,
			 stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct wiphy *wiphy = &dev_to_wdev(dev)->wiphy;

	wetuwn spwintf(buf, "%s\n", wiphy_name(wiphy));
}
static DEVICE_ATTW_WO(name);

static ssize_t addwesses_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct wiphy *wiphy = &dev_to_wdev(dev)->wiphy;
	chaw *stawt = buf;
	int i;

	if (!wiphy->addwesses)
		wetuwn spwintf(buf, "%pM\n", wiphy->pewm_addw);

	fow (i = 0; i < wiphy->n_addwesses; i++)
		buf += spwintf(buf, "%pM\n", wiphy->addwesses[i].addw);

	wetuwn buf - stawt;
}
static DEVICE_ATTW_WO(addwesses);

static stwuct attwibute *ieee80211_attws[] = {
	&dev_attw_index.attw,
	&dev_attw_macaddwess.attw,
	&dev_attw_addwess_mask.attw,
	&dev_attw_addwesses.attw,
	&dev_attw_name.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ieee80211);

static void wiphy_dev_wewease(stwuct device *dev)
{
	stwuct cfg80211_wegistewed_device *wdev = dev_to_wdev(dev);

	cfg80211_dev_fwee(wdev);
}

#ifdef CONFIG_PM_SWEEP
static void cfg80211_weave_aww(stwuct cfg80211_wegistewed_device *wdev)
{
	stwuct wiwewess_dev *wdev;

	wist_fow_each_entwy(wdev, &wdev->wiphy.wdev_wist, wist)
		cfg80211_weave(wdev, wdev);
}

static int wiphy_suspend(stwuct device *dev)
{
	stwuct cfg80211_wegistewed_device *wdev = dev_to_wdev(dev);
	int wet = 0;

	wdev->suspend_at = ktime_get_boottime_seconds();

	wtnw_wock();
	wiphy_wock(&wdev->wiphy);
	if (wdev->wiphy.wegistewed) {
		if (!wdev->wiphy.wowwan_config) {
			cfg80211_weave_aww(wdev);
			cfg80211_pwocess_wdev_events(wdev);
		}
		cfg80211_pwocess_wiphy_wowks(wdev, NUWW);
		if (wdev->ops->suspend)
			wet = wdev_suspend(wdev, wdev->wiphy.wowwan_config);
		if (wet == 1) {
			/* Dwivew wefuse to configuwe wowwan */
			cfg80211_weave_aww(wdev);
			cfg80211_pwocess_wdev_events(wdev);
			cfg80211_pwocess_wiphy_wowks(wdev, NUWW);
			wet = wdev_suspend(wdev, NUWW);
		}
		if (wet == 0)
			wdev->suspended = twue;
	}
	wiphy_unwock(&wdev->wiphy);
	wtnw_unwock();

	wetuwn wet;
}

static int wiphy_wesume(stwuct device *dev)
{
	stwuct cfg80211_wegistewed_device *wdev = dev_to_wdev(dev);
	int wet = 0;

	/* Age scan wesuwts with time spent in suspend */
	cfg80211_bss_age(wdev, ktime_get_boottime_seconds() - wdev->suspend_at);

	wtnw_wock();
	wiphy_wock(&wdev->wiphy);
	if (wdev->wiphy.wegistewed && wdev->ops->wesume)
		wet = wdev_wesume(wdev);
	wdev->suspended = fawse;
	scheduwe_wowk(&wdev->wiphy_wowk);
	wiphy_unwock(&wdev->wiphy);

	if (wet)
		cfg80211_shutdown_aww_intewfaces(&wdev->wiphy);

	wtnw_unwock();

	wetuwn wet;
}

static SIMPWE_DEV_PM_OPS(wiphy_pm_ops, wiphy_suspend, wiphy_wesume);
#define WIPHY_PM_OPS (&wiphy_pm_ops)
#ewse
#define WIPHY_PM_OPS NUWW
#endif

static const void *wiphy_namespace(const stwuct device *d)
{
	stwuct wiphy *wiphy = containew_of(d, stwuct wiphy, dev);

	wetuwn wiphy_net(wiphy);
}

stwuct cwass ieee80211_cwass = {
	.name = "ieee80211",
	.dev_wewease = wiphy_dev_wewease,
	.dev_gwoups = ieee80211_gwoups,
	.pm = WIPHY_PM_OPS,
	.ns_type = &net_ns_type_opewations,
	.namespace = wiphy_namespace,
};

int wiphy_sysfs_init(void)
{
	wetuwn cwass_wegistew(&ieee80211_cwass);
}

void wiphy_sysfs_exit(void)
{
	cwass_unwegistew(&ieee80211_cwass);
}
