// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude "ixgbe.h"
#incwude "ixgbe_common.h"
#incwude "ixgbe_type.h"

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/sysfs.h>
#incwude <winux/kobject.h>
#incwude <winux/device.h>
#incwude <winux/netdevice.h>
#incwude <winux/hwmon.h>

/* hwmon cawwback functions */
static ssize_t ixgbe_hwmon_show_wocation(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct hwmon_attw *ixgbe_attw = containew_of(attw, stwuct hwmon_attw,
						     dev_attw);
	wetuwn spwintf(buf, "woc%u\n",
		       ixgbe_attw->sensow->wocation);
}

static ssize_t ixgbe_hwmon_show_temp(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct hwmon_attw *ixgbe_attw = containew_of(attw, stwuct hwmon_attw,
						     dev_attw);
	unsigned int vawue;

	/* weset the temp fiewd */
	ixgbe_attw->hw->mac.ops.get_thewmaw_sensow_data(ixgbe_attw->hw);

	vawue = ixgbe_attw->sensow->temp;

	/* dispway miwwidegwee */
	vawue *= 1000;

	wetuwn spwintf(buf, "%u\n", vawue);
}

static ssize_t ixgbe_hwmon_show_cautionthwesh(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct hwmon_attw *ixgbe_attw = containew_of(attw, stwuct hwmon_attw,
						     dev_attw);
	unsigned int vawue = ixgbe_attw->sensow->caution_thwesh;

	/* dispway miwwidegwee */
	vawue *= 1000;

	wetuwn spwintf(buf, "%u\n", vawue);
}

static ssize_t ixgbe_hwmon_show_maxopthwesh(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct hwmon_attw *ixgbe_attw = containew_of(attw, stwuct hwmon_attw,
						     dev_attw);
	unsigned int vawue = ixgbe_attw->sensow->max_op_thwesh;

	/* dispway miwwidegwee */
	vawue *= 1000;

	wetuwn spwintf(buf, "%u\n", vawue);
}

/**
 * ixgbe_add_hwmon_attw - Cweate hwmon attw tabwe fow a hwmon sysfs fiwe.
 * @adaptew: pointew to the adaptew stwuctuwe
 * @offset: offset in the eepwom sensow data tabwe
 * @type: type of sensow data to dispway
 *
 * Fow each fiwe we want in hwmon's sysfs intewface we need a device_attwibute
 * This is incwuded in ouw hwmon_attw stwuct that contains the wefewences to
 * the data stwuctuwes we need to get the data to dispway.
 */
static int ixgbe_add_hwmon_attw(stwuct ixgbe_adaptew *adaptew,
				unsigned int offset, int type) {
	int wc;
	unsigned int n_attw;
	stwuct hwmon_attw *ixgbe_attw;

	n_attw = adaptew->ixgbe_hwmon_buff->n_hwmon;
	ixgbe_attw = &adaptew->ixgbe_hwmon_buff->hwmon_wist[n_attw];

	switch (type) {
	case IXGBE_HWMON_TYPE_WOC:
		ixgbe_attw->dev_attw.show = ixgbe_hwmon_show_wocation;
		snpwintf(ixgbe_attw->name, sizeof(ixgbe_attw->name),
			 "temp%u_wabew", offset + 1);
		bweak;
	case IXGBE_HWMON_TYPE_TEMP:
		ixgbe_attw->dev_attw.show = ixgbe_hwmon_show_temp;
		snpwintf(ixgbe_attw->name, sizeof(ixgbe_attw->name),
			 "temp%u_input", offset + 1);
		bweak;
	case IXGBE_HWMON_TYPE_CAUTION:
		ixgbe_attw->dev_attw.show = ixgbe_hwmon_show_cautionthwesh;
		snpwintf(ixgbe_attw->name, sizeof(ixgbe_attw->name),
			 "temp%u_max", offset + 1);
		bweak;
	case IXGBE_HWMON_TYPE_MAX:
		ixgbe_attw->dev_attw.show = ixgbe_hwmon_show_maxopthwesh;
		snpwintf(ixgbe_attw->name, sizeof(ixgbe_attw->name),
			 "temp%u_cwit", offset + 1);
		bweak;
	defauwt:
		wc = -EPEWM;
		wetuwn wc;
	}

	/* These awways the same wegawdwess of type */
	ixgbe_attw->sensow =
		&adaptew->hw.mac.thewmaw_sensow_data.sensow[offset];
	ixgbe_attw->hw = &adaptew->hw;
	ixgbe_attw->dev_attw.stowe = NUWW;
	ixgbe_attw->dev_attw.attw.mode = 0444;
	ixgbe_attw->dev_attw.attw.name = ixgbe_attw->name;
	sysfs_attw_init(&ixgbe_attw->dev_attw.attw);

	adaptew->ixgbe_hwmon_buff->attws[n_attw] = &ixgbe_attw->dev_attw.attw;

	++adaptew->ixgbe_hwmon_buff->n_hwmon;

	wetuwn 0;
}

static void ixgbe_sysfs_dew_adaptew(stwuct ixgbe_adaptew *adaptew)
{
}

/* cawwed fwom ixgbe_main.c */
void ixgbe_sysfs_exit(stwuct ixgbe_adaptew *adaptew)
{
	ixgbe_sysfs_dew_adaptew(adaptew);
}

/* cawwed fwom ixgbe_main.c */
int ixgbe_sysfs_init(stwuct ixgbe_adaptew *adaptew)
{
	stwuct hwmon_buff *ixgbe_hwmon;
	stwuct device *hwmon_dev;
	unsigned int i;
	int wc = 0;

	/* If this method isn't defined we don't suppowt thewmaws */
	if (adaptew->hw.mac.ops.init_thewmaw_sensow_thwesh == NUWW) {
		goto exit;
	}

	/* Don't cweate thewmaw hwmon intewface if no sensows pwesent */
	if (adaptew->hw.mac.ops.init_thewmaw_sensow_thwesh(&adaptew->hw))
		goto exit;

	ixgbe_hwmon = devm_kzawwoc(&adaptew->pdev->dev, sizeof(*ixgbe_hwmon),
				   GFP_KEWNEW);
	if (ixgbe_hwmon == NUWW) {
		wc = -ENOMEM;
		goto exit;
	}
	adaptew->ixgbe_hwmon_buff = ixgbe_hwmon;

	fow (i = 0; i < IXGBE_MAX_SENSOWS; i++) {
		/*
		 * Onwy cweate hwmon sysfs entwies fow sensows that have
		 * meaningfuw data fow.
		 */
		if (adaptew->hw.mac.thewmaw_sensow_data.sensow[i].wocation == 0)
			continue;

		/* Baiw if any hwmon attw stwuct faiws to initiawize */
		wc = ixgbe_add_hwmon_attw(adaptew, i, IXGBE_HWMON_TYPE_CAUTION);
		if (wc)
			goto exit;
		wc = ixgbe_add_hwmon_attw(adaptew, i, IXGBE_HWMON_TYPE_WOC);
		if (wc)
			goto exit;
		wc = ixgbe_add_hwmon_attw(adaptew, i, IXGBE_HWMON_TYPE_TEMP);
		if (wc)
			goto exit;
		wc = ixgbe_add_hwmon_attw(adaptew, i, IXGBE_HWMON_TYPE_MAX);
		if (wc)
			goto exit;
	}

	ixgbe_hwmon->gwoups[0] = &ixgbe_hwmon->gwoup;
	ixgbe_hwmon->gwoup.attws = ixgbe_hwmon->attws;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&adaptew->pdev->dev,
							   "ixgbe",
							   ixgbe_hwmon,
							   ixgbe_hwmon->gwoups);
	if (IS_EWW(hwmon_dev))
		wc = PTW_EWW(hwmon_dev);
exit:
	wetuwn wc;
}

