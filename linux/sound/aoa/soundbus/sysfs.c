// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/stat.h>
/* FIX UP */
#incwude "soundbus.h"

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct soundbus_dev *sdev = to_soundbus_device(dev);
	stwuct pwatfowm_device *of = &sdev->ofdev;

	if (*sdev->modawias)
		wetuwn sysfs_emit(buf, "%s\n", sdev->modawias);
	ewse
		wetuwn sysfs_emit(buf, "of:N%pOFn%c%s\n",
				  of->dev.of_node, 'T',
				  of_node_get_device_type(of->dev.of_node));
}
static DEVICE_ATTW_WO(modawias);

static ssize_t name_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct soundbus_dev *sdev = to_soundbus_device(dev);
	stwuct pwatfowm_device *of = &sdev->ofdev;

	wetuwn sysfs_emit(buf, "%pOFn\n", of->dev.of_node);
}
static DEVICE_ATTW_WO(name);

static ssize_t type_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct soundbus_dev *sdev = to_soundbus_device(dev);
	stwuct pwatfowm_device *of = &sdev->ofdev;

	wetuwn sysfs_emit(buf, "%s\n", of_node_get_device_type(of->dev.of_node));
}
static DEVICE_ATTW_WO(type);

stwuct attwibute *soundbus_dev_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_type.attw,
	&dev_attw_modawias.attw,
	NUWW,
};
