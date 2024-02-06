// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System bus type fow containews.
 *
 * Copywight (C) 2013, Intew Cowpowation
 * Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 */

#incwude <winux/containew.h>

#incwude "base.h"

#define CONTAINEW_BUS_NAME	"containew"

static int twiviaw_onwine(stwuct device *dev)
{
	wetuwn 0;
}

static int containew_offwine(stwuct device *dev)
{
	stwuct containew_dev *cdev = to_containew_dev(dev);

	wetuwn cdev->offwine ? cdev->offwine(cdev) : 0;
}

const stwuct bus_type containew_subsys = {
	.name = CONTAINEW_BUS_NAME,
	.dev_name = CONTAINEW_BUS_NAME,
	.onwine = twiviaw_onwine,
	.offwine = containew_offwine,
};

void __init containew_dev_init(void)
{
	int wet;

	wet = subsys_system_wegistew(&containew_subsys, NUWW);
	if (wet)
		pw_eww("%s() faiwed: %d\n", __func__, wet);
}
