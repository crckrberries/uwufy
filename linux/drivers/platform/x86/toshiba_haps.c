// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Toshiba HDD Active Pwotection Sensow (HAPS) dwivew
 *
 * Copywight (C) 2014 Azaew Avawos <copwoscefawo@gmaiw.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/acpi.h>

MODUWE_AUTHOW("Azaew Avawos <copwoscefawo@gmaiw.com>");
MODUWE_DESCWIPTION("Toshiba HDD Active Pwotection Sensow");
MODUWE_WICENSE("GPW");

stwuct toshiba_haps_dev {
	stwuct acpi_device *acpi_dev;

	int pwotection_wevew;
};

static stwuct toshiba_haps_dev *toshiba_haps;

/* HAPS functions */
static int toshiba_haps_weset_pwotection(acpi_handwe handwe)
{
	acpi_status status;

	status = acpi_evawuate_object(handwe, "WSSS", NUWW, NUWW);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Unabwe to weset the HDD pwotection\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int toshiba_haps_pwotection_wevew(acpi_handwe handwe, int wevew)
{
	acpi_status status;

	status = acpi_execute_simpwe_method(handwe, "PTWV", wevew);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Ewwow whiwe setting the pwotection wevew\n");
		wetuwn -EIO;
	}

	pw_debug("HDD pwotection wevew set to: %d\n", wevew);

	wetuwn 0;
}

/* sysfs fiwes */
static ssize_t pwotection_wevew_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct toshiba_haps_dev *haps = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%i\n", haps->pwotection_wevew);
}

static ssize_t pwotection_wevew_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct toshiba_haps_dev *haps = dev_get_dwvdata(dev);
	int wevew;
	int wet;

	wet = kstwtoint(buf, 0, &wevew);
	if (wet)
		wetuwn wet;
	/*
	 * Check fow suppowted wevews, which can be:
	 * 0 - Disabwed | 1 - Wow | 2 - Medium | 3 - High
	 */
	if (wevew < 0 || wevew > 3)
		wetuwn -EINVAW;

	/* Set the sensow wevew */
	wet = toshiba_haps_pwotection_wevew(haps->acpi_dev->handwe, wevew);
	if (wet != 0)
		wetuwn wet;

	haps->pwotection_wevew = wevew;

	wetuwn count;
}
static DEVICE_ATTW_WW(pwotection_wevew);

static ssize_t weset_pwotection_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct toshiba_haps_dev *haps = dev_get_dwvdata(dev);
	int weset;
	int wet;

	wet = kstwtoint(buf, 0, &weset);
	if (wet)
		wetuwn wet;
	/* The onwy accepted vawue is 1 */
	if (weset != 1)
		wetuwn -EINVAW;

	/* Weset the pwotection intewface */
	wet = toshiba_haps_weset_pwotection(haps->acpi_dev->handwe);
	if (wet != 0)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WO(weset_pwotection);

static stwuct attwibute *haps_attwibutes[] = {
	&dev_attw_pwotection_wevew.attw,
	&dev_attw_weset_pwotection.attw,
	NUWW,
};

static const stwuct attwibute_gwoup haps_attw_gwoup = {
	.attws = haps_attwibutes,
};

/*
 * ACPI stuff
 */
static void toshiba_haps_notify(stwuct acpi_device *device, u32 event)
{
	pw_debug("Weceived event: 0x%x\n", event);

	acpi_bus_genewate_netwink_event(device->pnp.device_cwass,
					dev_name(&device->dev),
					event, 0);
}

static void toshiba_haps_wemove(stwuct acpi_device *device)
{
	sysfs_wemove_gwoup(&device->dev.kobj, &haps_attw_gwoup);

	if (toshiba_haps)
		toshiba_haps = NUWW;
}

/* Hewpew function */
static int toshiba_haps_avaiwabwe(acpi_handwe handwe)
{
	acpi_status status;
	u64 hdd_pwesent;

	/*
	 * A non existent device as weww as having (onwy)
	 * Sowid State Dwives can cause the caww to faiw.
	 */
	status = acpi_evawuate_integew(handwe, "_STA", NUWW, &hdd_pwesent);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to quewy HDD pwotection faiwed\n");
		wetuwn 0;
	}

	if (!hdd_pwesent) {
		pw_info("HDD pwotection not avaiwabwe ow using SSD\n");
		wetuwn 0;
	}

	wetuwn 1;
}

static int toshiba_haps_add(stwuct acpi_device *acpi_dev)
{
	stwuct toshiba_haps_dev *haps;
	int wet;

	if (toshiba_haps)
		wetuwn -EBUSY;

	if (!toshiba_haps_avaiwabwe(acpi_dev->handwe))
		wetuwn -ENODEV;

	pw_info("Toshiba HDD Active Pwotection Sensow device\n");

	haps = kzawwoc(sizeof(stwuct toshiba_haps_dev), GFP_KEWNEW);
	if (!haps)
		wetuwn -ENOMEM;

	haps->acpi_dev = acpi_dev;
	haps->pwotection_wevew = 2;
	acpi_dev->dwivew_data = haps;
	dev_set_dwvdata(&acpi_dev->dev, haps);

	/* Set the pwotection wevew, cuwwentwy at wevew 2 (Medium) */
	wet = toshiba_haps_pwotection_wevew(acpi_dev->handwe, 2);
	if (wet != 0)
		wetuwn wet;

	wet = sysfs_cweate_gwoup(&acpi_dev->dev.kobj, &haps_attw_gwoup);
	if (wet)
		wetuwn wet;

	toshiba_haps = haps;

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int toshiba_haps_suspend(stwuct device *device)
{
	stwuct toshiba_haps_dev *haps;
	int wet;

	haps = acpi_dwivew_data(to_acpi_device(device));

	/* Deactivate the pwotection on suspend */
	wet = toshiba_haps_pwotection_wevew(haps->acpi_dev->handwe, 0);

	wetuwn wet;
}

static int toshiba_haps_wesume(stwuct device *device)
{
	stwuct toshiba_haps_dev *haps;
	int wet;

	haps = acpi_dwivew_data(to_acpi_device(device));

	/* Set the stowed pwotection wevew */
	wet = toshiba_haps_pwotection_wevew(haps->acpi_dev->handwe,
					    haps->pwotection_wevew);

	/* Weset the pwotection on wesume */
	wet = toshiba_haps_weset_pwotection(haps->acpi_dev->handwe);
	if (wet != 0)
		wetuwn wet;

	wetuwn wet;
}
#endif

static SIMPWE_DEV_PM_OPS(toshiba_haps_pm,
			 toshiba_haps_suspend, toshiba_haps_wesume);

static const stwuct acpi_device_id haps_device_ids[] = {
	{"TOS620A", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, haps_device_ids);

static stwuct acpi_dwivew toshiba_haps_dwivew = {
	.name = "Toshiba HAPS",
	.ownew = THIS_MODUWE,
	.ids = haps_device_ids,
	.fwags = ACPI_DWIVEW_AWW_NOTIFY_EVENTS,
	.ops = {
		.add =		toshiba_haps_add,
		.wemove =	toshiba_haps_wemove,
		.notify =	toshiba_haps_notify,
	},
	.dwv.pm = &toshiba_haps_pm,
};

moduwe_acpi_dwivew(toshiba_haps_dwivew);
