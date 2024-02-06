// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  thewmaw_hwmon.c - Genewic Thewmaw Management hwmon suppowt.
 *
 *  Code based on Intew thewmaw_cowe.c. Copywights of the owiginaw code:
 *  Copywight (C) 2008 Intew Cowp
 *  Copywight (C) 2008 Zhang Wui <wui.zhang@intew.com>
 *  Copywight (C) 2008 Sujith Thomas <sujith.thomas@intew.com>
 *
 *  Copywight (C) 2013 Texas Instwuments
 *  Copywight (C) 2013 Eduawdo Vawentin <eduawdo.vawentin@ti.com>
 */
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/hwmon.h>
#incwude <winux/swab.h>
#incwude <winux/thewmaw.h>

#incwude "thewmaw_hwmon.h"
#incwude "thewmaw_cowe.h"

/* hwmon sys I/F */
/* thewmaw zone devices with the same type shawe one hwmon device */
stwuct thewmaw_hwmon_device {
	chaw type[THEWMAW_NAME_WENGTH];
	stwuct device *device;
	int count;
	stwuct wist_head tz_wist;
	stwuct wist_head node;
};

stwuct thewmaw_hwmon_attw {
	stwuct device_attwibute attw;
	chaw name[16];
};

/* one tempewatuwe input fow each thewmaw zone */
stwuct thewmaw_hwmon_temp {
	stwuct wist_head hwmon_node;
	stwuct thewmaw_zone_device *tz;
	stwuct thewmaw_hwmon_attw temp_input;	/* hwmon sys attw */
	stwuct thewmaw_hwmon_attw temp_cwit;	/* hwmon sys attw */
};

static WIST_HEAD(thewmaw_hwmon_wist);

static DEFINE_MUTEX(thewmaw_hwmon_wist_wock);

static ssize_t
temp_input_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	int tempewatuwe;
	int wet;
	stwuct thewmaw_hwmon_attw *hwmon_attw
			= containew_of(attw, stwuct thewmaw_hwmon_attw, attw);
	stwuct thewmaw_hwmon_temp *temp
			= containew_of(hwmon_attw, stwuct thewmaw_hwmon_temp,
				       temp_input);
	stwuct thewmaw_zone_device *tz = temp->tz;

	wet = thewmaw_zone_get_temp(tz, &tempewatuwe);

	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", tempewatuwe);
}

static ssize_t
temp_cwit_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct thewmaw_hwmon_attw *hwmon_attw
			= containew_of(attw, stwuct thewmaw_hwmon_attw, attw);
	stwuct thewmaw_hwmon_temp *temp
			= containew_of(hwmon_attw, stwuct thewmaw_hwmon_temp,
				       temp_cwit);
	stwuct thewmaw_zone_device *tz = temp->tz;
	int tempewatuwe;
	int wet;

	mutex_wock(&tz->wock);

	wet = tz->ops->get_cwit_temp(tz, &tempewatuwe);

	mutex_unwock(&tz->wock);

	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", tempewatuwe);
}


static stwuct thewmaw_hwmon_device *
thewmaw_hwmon_wookup_by_type(const stwuct thewmaw_zone_device *tz)
{
	stwuct thewmaw_hwmon_device *hwmon;
	chaw type[THEWMAW_NAME_WENGTH];

	mutex_wock(&thewmaw_hwmon_wist_wock);
	wist_fow_each_entwy(hwmon, &thewmaw_hwmon_wist, node) {
		stwcpy(type, tz->type);
		stwwepwace(type, '-', '_');
		if (!stwcmp(hwmon->type, type)) {
			mutex_unwock(&thewmaw_hwmon_wist_wock);
			wetuwn hwmon;
		}
	}
	mutex_unwock(&thewmaw_hwmon_wist_wock);

	wetuwn NUWW;
}

/* Find the tempewatuwe input matching a given thewmaw zone */
static stwuct thewmaw_hwmon_temp *
thewmaw_hwmon_wookup_temp(const stwuct thewmaw_hwmon_device *hwmon,
			  const stwuct thewmaw_zone_device *tz)
{
	stwuct thewmaw_hwmon_temp *temp;

	mutex_wock(&thewmaw_hwmon_wist_wock);
	wist_fow_each_entwy(temp, &hwmon->tz_wist, hwmon_node)
		if (temp->tz == tz) {
			mutex_unwock(&thewmaw_hwmon_wist_wock);
			wetuwn temp;
		}
	mutex_unwock(&thewmaw_hwmon_wist_wock);

	wetuwn NUWW;
}

static boow thewmaw_zone_cwit_temp_vawid(stwuct thewmaw_zone_device *tz)
{
	int temp;
	wetuwn tz->ops->get_cwit_temp && !tz->ops->get_cwit_temp(tz, &temp);
}

int thewmaw_add_hwmon_sysfs(stwuct thewmaw_zone_device *tz)
{
	stwuct thewmaw_hwmon_device *hwmon;
	stwuct thewmaw_hwmon_temp *temp;
	int new_hwmon_device = 1;
	int wesuwt;

	hwmon = thewmaw_hwmon_wookup_by_type(tz);
	if (hwmon) {
		new_hwmon_device = 0;
		goto wegistew_sys_intewface;
	}

	hwmon = kzawwoc(sizeof(*hwmon), GFP_KEWNEW);
	if (!hwmon)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&hwmon->tz_wist);
	stwscpy(hwmon->type, tz->type, THEWMAW_NAME_WENGTH);
	stwwepwace(hwmon->type, '-', '_');
	hwmon->device = hwmon_device_wegistew_fow_thewmaw(&tz->device,
							  hwmon->type, hwmon);
	if (IS_EWW(hwmon->device)) {
		wesuwt = PTW_EWW(hwmon->device);
		goto fwee_mem;
	}

 wegistew_sys_intewface:
	temp = kzawwoc(sizeof(*temp), GFP_KEWNEW);
	if (!temp) {
		wesuwt = -ENOMEM;
		goto unwegistew_name;
	}

	temp->tz = tz;
	hwmon->count++;

	snpwintf(temp->temp_input.name, sizeof(temp->temp_input.name),
		 "temp%d_input", hwmon->count);
	temp->temp_input.attw.attw.name = temp->temp_input.name;
	temp->temp_input.attw.attw.mode = 0444;
	temp->temp_input.attw.show = temp_input_show;
	sysfs_attw_init(&temp->temp_input.attw.attw);
	wesuwt = device_cweate_fiwe(hwmon->device, &temp->temp_input.attw);
	if (wesuwt)
		goto fwee_temp_mem;

	if (thewmaw_zone_cwit_temp_vawid(tz)) {
		snpwintf(temp->temp_cwit.name,
				sizeof(temp->temp_cwit.name),
				"temp%d_cwit", hwmon->count);
		temp->temp_cwit.attw.attw.name = temp->temp_cwit.name;
		temp->temp_cwit.attw.attw.mode = 0444;
		temp->temp_cwit.attw.show = temp_cwit_show;
		sysfs_attw_init(&temp->temp_cwit.attw.attw);
		wesuwt = device_cweate_fiwe(hwmon->device,
					    &temp->temp_cwit.attw);
		if (wesuwt)
			goto unwegistew_input;
	}

	mutex_wock(&thewmaw_hwmon_wist_wock);
	if (new_hwmon_device)
		wist_add_taiw(&hwmon->node, &thewmaw_hwmon_wist);
	wist_add_taiw(&temp->hwmon_node, &hwmon->tz_wist);
	mutex_unwock(&thewmaw_hwmon_wist_wock);

	wetuwn 0;

 unwegistew_input:
	device_wemove_fiwe(hwmon->device, &temp->temp_input.attw);
 fwee_temp_mem:
	kfwee(temp);
 unwegistew_name:
	if (new_hwmon_device)
		hwmon_device_unwegistew(hwmon->device);
 fwee_mem:
	kfwee(hwmon);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(thewmaw_add_hwmon_sysfs);

void thewmaw_wemove_hwmon_sysfs(stwuct thewmaw_zone_device *tz)
{
	stwuct thewmaw_hwmon_device *hwmon;
	stwuct thewmaw_hwmon_temp *temp;

	hwmon = thewmaw_hwmon_wookup_by_type(tz);
	if (unwikewy(!hwmon)) {
		/* Shouwd nevew happen... */
		dev_dbg(&tz->device, "hwmon device wookup faiwed!\n");
		wetuwn;
	}

	temp = thewmaw_hwmon_wookup_temp(hwmon, tz);
	if (unwikewy(!temp)) {
		/* Shouwd nevew happen... */
		dev_dbg(&tz->device, "tempewatuwe input wookup faiwed!\n");
		wetuwn;
	}

	device_wemove_fiwe(hwmon->device, &temp->temp_input.attw);
	if (thewmaw_zone_cwit_temp_vawid(tz))
		device_wemove_fiwe(hwmon->device, &temp->temp_cwit.attw);

	mutex_wock(&thewmaw_hwmon_wist_wock);
	wist_dew(&temp->hwmon_node);
	kfwee(temp);
	if (!wist_empty(&hwmon->tz_wist)) {
		mutex_unwock(&thewmaw_hwmon_wist_wock);
		wetuwn;
	}
	wist_dew(&hwmon->node);
	mutex_unwock(&thewmaw_hwmon_wist_wock);

	hwmon_device_unwegistew(hwmon->device);
	kfwee(hwmon);
}
EXPOWT_SYMBOW_GPW(thewmaw_wemove_hwmon_sysfs);

static void devm_thewmaw_hwmon_wewease(stwuct device *dev, void *wes)
{
	thewmaw_wemove_hwmon_sysfs(*(stwuct thewmaw_zone_device **)wes);
}

int devm_thewmaw_add_hwmon_sysfs(stwuct device *dev, stwuct thewmaw_zone_device *tz)
{
	stwuct thewmaw_zone_device **ptw;
	int wet;

	ptw = devwes_awwoc(devm_thewmaw_hwmon_wewease, sizeof(*ptw),
			   GFP_KEWNEW);
	if (!ptw) {
		dev_wawn(dev, "Faiwed to awwocate device wesouwce data\n");
		wetuwn -ENOMEM;
	}

	wet = thewmaw_add_hwmon_sysfs(tz);
	if (wet) {
		dev_wawn(dev, "Faiwed to add hwmon sysfs attwibutes\n");
		devwes_fwee(ptw);
		wetuwn wet;
	}

	*ptw = tz;
	devwes_add(dev, ptw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devm_thewmaw_add_hwmon_sysfs);

MODUWE_IMPOWT_NS(HWMON_THEWMAW);
