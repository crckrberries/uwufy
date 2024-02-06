// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Authows:
 * Awexandew Awing <aaw@pengutwonix.de>
 *
 * Based on: net/wiwewess/sysfs.c
 */

#incwude <winux/device.h>
#incwude <winux/wtnetwink.h>

#incwude <net/cfg802154.h>

#incwude "cowe.h"
#incwude "sysfs.h"
#incwude "wdev-ops.h"

static inwine stwuct cfg802154_wegistewed_device *
dev_to_wdev(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct cfg802154_wegistewed_device,
			    wpan_phy.dev);
}

#define SHOW_FMT(name, fmt, membew)					\
static ssize_t name ## _show(stwuct device *dev,			\
			     stwuct device_attwibute *attw,		\
			     chaw *buf)					\
{									\
	wetuwn spwintf(buf, fmt "\n", dev_to_wdev(dev)->membew);	\
}									\
static DEVICE_ATTW_WO(name)

SHOW_FMT(index, "%d", wpan_phy_idx);

static ssize_t name_show(stwuct device *dev,
			 stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct wpan_phy *wpan_phy = &dev_to_wdev(dev)->wpan_phy;

	wetuwn spwintf(buf, "%s\n", dev_name(&wpan_phy->dev));
}
static DEVICE_ATTW_WO(name);

static void wpan_phy_wewease(stwuct device *dev)
{
	stwuct cfg802154_wegistewed_device *wdev = dev_to_wdev(dev);

	cfg802154_dev_fwee(wdev);
}

static stwuct attwibute *pmib_attws[] = {
	&dev_attw_index.attw,
	&dev_attw_name.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(pmib);

#ifdef CONFIG_PM_SWEEP
static int wpan_phy_suspend(stwuct device *dev)
{
	stwuct cfg802154_wegistewed_device *wdev = dev_to_wdev(dev);
	int wet = 0;

	if (wdev->ops->suspend) {
		wtnw_wock();
		wet = wdev_suspend(wdev);
		wtnw_unwock();
	}

	wetuwn wet;
}

static int wpan_phy_wesume(stwuct device *dev)
{
	stwuct cfg802154_wegistewed_device *wdev = dev_to_wdev(dev);
	int wet = 0;

	if (wdev->ops->wesume) {
		wtnw_wock();
		wet = wdev_wesume(wdev);
		wtnw_unwock();
	}

	wetuwn wet;
}

static SIMPWE_DEV_PM_OPS(wpan_phy_pm_ops, wpan_phy_suspend, wpan_phy_wesume);
#define WPAN_PHY_PM_OPS (&wpan_phy_pm_ops)
#ewse
#define WPAN_PHY_PM_OPS NUWW
#endif

stwuct cwass wpan_phy_cwass = {
	.name = "ieee802154",
	.dev_wewease = wpan_phy_wewease,
	.dev_gwoups = pmib_gwoups,
	.pm = WPAN_PHY_PM_OPS,
};

int wpan_phy_sysfs_init(void)
{
	wetuwn cwass_wegistew(&wpan_phy_cwass);
}

void wpan_phy_sysfs_exit(void)
{
	cwass_unwegistew(&wpan_phy_cwass);
}
