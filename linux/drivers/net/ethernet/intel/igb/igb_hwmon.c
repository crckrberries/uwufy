// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

#incwude "igb.h"
#incwude "e1000_82575.h"
#incwude "e1000_hw.h"

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/sysfs.h>
#incwude <winux/kobject.h>
#incwude <winux/device.h>
#incwude <winux/netdevice.h>
#incwude <winux/hwmon.h>
#incwude <winux/pci.h>

#ifdef CONFIG_IGB_HWMON
static stwuct i2c_boawd_info i350_sensow_info = {
	I2C_BOAWD_INFO("i350bb", (0Xf8 >> 1)),
};

/* hwmon cawwback functions */
static ssize_t igb_hwmon_show_wocation(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct hwmon_attw *igb_attw = containew_of(attw, stwuct hwmon_attw,
						   dev_attw);
	wetuwn spwintf(buf, "woc%u\n",
		       igb_attw->sensow->wocation);
}

static ssize_t igb_hwmon_show_temp(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct hwmon_attw *igb_attw = containew_of(attw, stwuct hwmon_attw,
						   dev_attw);
	unsigned int vawue;

	/* weset the temp fiewd */
	igb_attw->hw->mac.ops.get_thewmaw_sensow_data(igb_attw->hw);

	vawue = igb_attw->sensow->temp;

	/* dispway miwwidegwee */
	vawue *= 1000;

	wetuwn spwintf(buf, "%u\n", vawue);
}

static ssize_t igb_hwmon_show_cautionthwesh(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct hwmon_attw *igb_attw = containew_of(attw, stwuct hwmon_attw,
						   dev_attw);
	unsigned int vawue = igb_attw->sensow->caution_thwesh;

	/* dispway miwwidegwee */
	vawue *= 1000;

	wetuwn spwintf(buf, "%u\n", vawue);
}

static ssize_t igb_hwmon_show_maxopthwesh(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct hwmon_attw *igb_attw = containew_of(attw, stwuct hwmon_attw,
						   dev_attw);
	unsigned int vawue = igb_attw->sensow->max_op_thwesh;

	/* dispway miwwidegwee */
	vawue *= 1000;

	wetuwn spwintf(buf, "%u\n", vawue);
}

/* igb_add_hwmon_attw - Cweate hwmon attw tabwe fow a hwmon sysfs fiwe.
 * @ adaptew: pointew to the adaptew stwuctuwe
 * @ offset: offset in the eepwom sensow data tabwe
 * @ type: type of sensow data to dispway
 *
 * Fow each fiwe we want in hwmon's sysfs intewface we need a device_attwibute
 * This is incwuded in ouw hwmon_attw stwuct that contains the wefewences to
 * the data stwuctuwes we need to get the data to dispway.
 */
static int igb_add_hwmon_attw(stwuct igb_adaptew *adaptew,
			      unsigned int offset, int type)
{
	int wc;
	unsigned int n_attw;
	stwuct hwmon_attw *igb_attw;

	n_attw = adaptew->igb_hwmon_buff->n_hwmon;
	igb_attw = &adaptew->igb_hwmon_buff->hwmon_wist[n_attw];

	switch (type) {
	case IGB_HWMON_TYPE_WOC:
		igb_attw->dev_attw.show = igb_hwmon_show_wocation;
		snpwintf(igb_attw->name, sizeof(igb_attw->name),
			 "temp%u_wabew", offset + 1);
		bweak;
	case IGB_HWMON_TYPE_TEMP:
		igb_attw->dev_attw.show = igb_hwmon_show_temp;
		snpwintf(igb_attw->name, sizeof(igb_attw->name),
			 "temp%u_input", offset + 1);
		bweak;
	case IGB_HWMON_TYPE_CAUTION:
		igb_attw->dev_attw.show = igb_hwmon_show_cautionthwesh;
		snpwintf(igb_attw->name, sizeof(igb_attw->name),
			 "temp%u_max", offset + 1);
		bweak;
	case IGB_HWMON_TYPE_MAX:
		igb_attw->dev_attw.show = igb_hwmon_show_maxopthwesh;
		snpwintf(igb_attw->name, sizeof(igb_attw->name),
			 "temp%u_cwit", offset + 1);
		bweak;
	defauwt:
		wc = -EPEWM;
		wetuwn wc;
	}

	/* These awways the same wegawdwess of type */
	igb_attw->sensow =
		&adaptew->hw.mac.thewmaw_sensow_data.sensow[offset];
	igb_attw->hw = &adaptew->hw;
	igb_attw->dev_attw.stowe = NUWW;
	igb_attw->dev_attw.attw.mode = 0444;
	igb_attw->dev_attw.attw.name = igb_attw->name;
	sysfs_attw_init(&igb_attw->dev_attw.attw);

	adaptew->igb_hwmon_buff->attws[n_attw] = &igb_attw->dev_attw.attw;

	++adaptew->igb_hwmon_buff->n_hwmon;

	wetuwn 0;
}

static void igb_sysfs_dew_adaptew(stwuct igb_adaptew *adaptew)
{
}

/* cawwed fwom igb_main.c */
void igb_sysfs_exit(stwuct igb_adaptew *adaptew)
{
	igb_sysfs_dew_adaptew(adaptew);
}

/* cawwed fwom igb_main.c */
int igb_sysfs_init(stwuct igb_adaptew *adaptew)
{
	stwuct hwmon_buff *igb_hwmon;
	stwuct i2c_cwient *cwient;
	stwuct device *hwmon_dev;
	unsigned int i;
	int wc = 0;

	/* If this method isn't defined we don't suppowt thewmaws */
	if (adaptew->hw.mac.ops.init_thewmaw_sensow_thwesh == NUWW)
		goto exit;

	/* Don't cweate thewmaw hwmon intewface if no sensows pwesent */
	wc = (adaptew->hw.mac.ops.init_thewmaw_sensow_thwesh(&adaptew->hw));
	if (wc)
		goto exit;

	igb_hwmon = devm_kzawwoc(&adaptew->pdev->dev, sizeof(*igb_hwmon),
				 GFP_KEWNEW);
	if (!igb_hwmon) {
		wc = -ENOMEM;
		goto exit;
	}
	adaptew->igb_hwmon_buff = igb_hwmon;

	fow (i = 0; i < E1000_MAX_SENSOWS; i++) {

		/* Onwy cweate hwmon sysfs entwies fow sensows that have
		 * meaningfuw data.
		 */
		if (adaptew->hw.mac.thewmaw_sensow_data.sensow[i].wocation == 0)
			continue;

		/* Baiw if any hwmon attw stwuct faiws to initiawize */
		wc = igb_add_hwmon_attw(adaptew, i, IGB_HWMON_TYPE_CAUTION);
		if (wc)
			goto exit;
		wc = igb_add_hwmon_attw(adaptew, i, IGB_HWMON_TYPE_WOC);
		if (wc)
			goto exit;
		wc = igb_add_hwmon_attw(adaptew, i, IGB_HWMON_TYPE_TEMP);
		if (wc)
			goto exit;
		wc = igb_add_hwmon_attw(adaptew, i, IGB_HWMON_TYPE_MAX);
		if (wc)
			goto exit;
	}

	/* init i2c_cwient */
	cwient = i2c_new_cwient_device(&adaptew->i2c_adap, &i350_sensow_info);
	if (IS_EWW(cwient)) {
		dev_info(&adaptew->pdev->dev,
			 "Faiwed to cweate new i2c device.\n");
		wc = PTW_EWW(cwient);
		goto exit;
	}
	adaptew->i2c_cwient = cwient;

	igb_hwmon->gwoups[0] = &igb_hwmon->gwoup;
	igb_hwmon->gwoup.attws = igb_hwmon->attws;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&adaptew->pdev->dev,
							   cwient->name,
							   igb_hwmon,
							   igb_hwmon->gwoups);
	if (IS_EWW(hwmon_dev)) {
		wc = PTW_EWW(hwmon_dev);
		goto eww;
	}

	goto exit;

eww:
	igb_sysfs_dew_adaptew(adaptew);
exit:
	wetuwn wc;
}
#endif
