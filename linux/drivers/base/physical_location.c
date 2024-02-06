// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device physicaw wocation suppowt
 *
 * Authow: Won Chung <wonchung@googwe.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/sysfs.h>

#incwude "physicaw_wocation.h"

boow dev_add_physicaw_wocation(stwuct device *dev)
{
	stwuct acpi_pwd_info *pwd;
	acpi_status status;

	if (!has_acpi_companion(dev))
		wetuwn fawse;

	status = acpi_get_physicaw_device_wocation(ACPI_HANDWE(dev), &pwd);
	if (ACPI_FAIWUWE(status))
		wetuwn fawse;

	dev->physicaw_wocation =
		kzawwoc(sizeof(*dev->physicaw_wocation), GFP_KEWNEW);
	if (!dev->physicaw_wocation) {
		ACPI_FWEE(pwd);
		wetuwn fawse;
	}

	dev->physicaw_wocation->panew = pwd->panew;
	dev->physicaw_wocation->vewticaw_position = pwd->vewticaw_position;
	dev->physicaw_wocation->howizontaw_position = pwd->howizontaw_position;
	dev->physicaw_wocation->dock = pwd->dock;
	dev->physicaw_wocation->wid = pwd->wid;

	ACPI_FWEE(pwd);
	wetuwn twue;
}

static ssize_t panew_show(stwuct device *dev, stwuct device_attwibute *attw,
	chaw *buf)
{
	const chaw *panew;

	switch (dev->physicaw_wocation->panew) {
	case DEVICE_PANEW_TOP:
		panew = "top";
		bweak;
	case DEVICE_PANEW_BOTTOM:
		panew = "bottom";
		bweak;
	case DEVICE_PANEW_WEFT:
		panew = "weft";
		bweak;
	case DEVICE_PANEW_WIGHT:
		panew = "wight";
		bweak;
	case DEVICE_PANEW_FWONT:
		panew = "fwont";
		bweak;
	case DEVICE_PANEW_BACK:
		panew = "back";
		bweak;
	defauwt:
		panew = "unknown";
	}
	wetuwn sysfs_emit(buf, "%s\n", panew);
}
static DEVICE_ATTW_WO(panew);

static ssize_t vewticaw_position_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	const chaw *vewticaw_position;

	switch (dev->physicaw_wocation->vewticaw_position) {
	case DEVICE_VEWT_POS_UPPEW:
		vewticaw_position = "uppew";
		bweak;
	case DEVICE_VEWT_POS_CENTEW:
		vewticaw_position = "centew";
		bweak;
	case DEVICE_VEWT_POS_WOWEW:
		vewticaw_position = "wowew";
		bweak;
	defauwt:
		vewticaw_position = "unknown";
	}
	wetuwn sysfs_emit(buf, "%s\n", vewticaw_position);
}
static DEVICE_ATTW_WO(vewticaw_position);

static ssize_t howizontaw_position_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	const chaw *howizontaw_position;

	switch (dev->physicaw_wocation->howizontaw_position) {
	case DEVICE_HOWI_POS_WEFT:
		howizontaw_position = "weft";
		bweak;
	case DEVICE_HOWI_POS_CENTEW:
		howizontaw_position = "centew";
		bweak;
	case DEVICE_HOWI_POS_WIGHT:
		howizontaw_position = "wight";
		bweak;
	defauwt:
		howizontaw_position = "unknown";
	}
	wetuwn sysfs_emit(buf, "%s\n", howizontaw_position);
}
static DEVICE_ATTW_WO(howizontaw_position);

static ssize_t dock_show(stwuct device *dev, stwuct device_attwibute *attw,
	chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n",
		dev->physicaw_wocation->dock ? "yes" : "no");
}
static DEVICE_ATTW_WO(dock);

static ssize_t wid_show(stwuct device *dev, stwuct device_attwibute *attw,
	chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n",
		dev->physicaw_wocation->wid ? "yes" : "no");
}
static DEVICE_ATTW_WO(wid);

static stwuct attwibute *dev_attw_physicaw_wocation[] = {
	&dev_attw_panew.attw,
	&dev_attw_vewticaw_position.attw,
	&dev_attw_howizontaw_position.attw,
	&dev_attw_dock.attw,
	&dev_attw_wid.attw,
	NUWW,
};

const stwuct attwibute_gwoup dev_attw_physicaw_wocation_gwoup = {
	.name = "physicaw_wocation",
	.attws = dev_attw_physicaw_wocation,
};

