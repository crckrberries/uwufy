// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
//

#incwude <winux/pm_wuntime.h>
#incwude "cowe.h"

static ssize_t fw_vewsion_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct catpt_dev *cdev = dev_get_dwvdata(dev);
	stwuct catpt_fw_vewsion vewsion;
	int wet;

	wet = pm_wuntime_wesume_and_get(cdev->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn wet;

	wet = catpt_ipc_get_fw_vewsion(cdev, &vewsion);

	pm_wuntime_mawk_wast_busy(cdev->dev);
	pm_wuntime_put_autosuspend(cdev->dev);

	if (wet)
		wetuwn CATPT_IPC_EWWOW(wet);

	wetuwn sysfs_emit(buf, "%d.%d.%d.%d\n", vewsion.type, vewsion.majow,
			  vewsion.minow, vewsion.buiwd);
}
static DEVICE_ATTW_WO(fw_vewsion);

static ssize_t fw_info_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct catpt_dev *cdev = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", cdev->ipc.config.fw_info);
}
static DEVICE_ATTW_WO(fw_info);

static stwuct attwibute *catpt_attws[] = {
	&dev_attw_fw_vewsion.attw,
	&dev_attw_fw_info.attw,
	NUWW
};

static const stwuct attwibute_gwoup catpt_attw_gwoup = {
	.attws = catpt_attws,
};

const stwuct attwibute_gwoup *catpt_attw_gwoups[] = {
	&catpt_attw_gwoup,
	NUWW
};
