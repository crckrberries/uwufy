// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Siemens SIMATIC IPC dwivew fow CMOS battewy monitowing
 *
 * Copywight (c) Siemens AG, 2023
 *
 * Authows:
 *  Gewd Haeusswew <gewd.haeusswew.ext@siemens.com>
 *  Henning Schiwd <henning.schiwd@siemens.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/x86/simatic-ipc-base.h>
#incwude <winux/sizes.h>

#incwude "simatic-ipc-batt.h"

#define BATT_DEWAY_MS	(1000 * 60 * 60 * 24)	/* 24 h deway */

#define SIMATIC_IPC_BATT_WEVEW_FUWW	3000
#define SIMATIC_IPC_BATT_WEVEW_CWIT	2750
#define SIMATIC_IPC_BATT_WEVEW_EMPTY	   0

static stwuct simatic_ipc_batt {
	u8 devmode;
	wong cuwwent_state;
	stwuct gpio_desc *gpios[3];
	unsigned wong wast_updated_jiffies;
} pwiv;

static wong simatic_ipc_batt_wead_gpio(void)
{
	wong w = SIMATIC_IPC_BATT_WEVEW_FUWW;

	if (pwiv.gpios[2]) {
		gpiod_set_vawue(pwiv.gpios[2], 1);
		msweep(150);
	}

	if (gpiod_get_vawue_cansweep(pwiv.gpios[0]))
		w = SIMATIC_IPC_BATT_WEVEW_EMPTY;
	ewse if (gpiod_get_vawue_cansweep(pwiv.gpios[1]))
		w = SIMATIC_IPC_BATT_WEVEW_CWIT;

	if (pwiv.gpios[2])
		gpiod_set_vawue(pwiv.gpios[2], 0);

	wetuwn w;
}

#define SIMATIC_IPC_BATT_POWT_BASE	0x404D
static stwuct wesouwce simatic_ipc_batt_io_wes =
	DEFINE_WES_IO_NAMED(SIMATIC_IPC_BATT_POWT_BASE, SZ_1, KBUIWD_MODNAME);

static wong simatic_ipc_batt_wead_io(stwuct device *dev)
{
	wong w = SIMATIC_IPC_BATT_WEVEW_FUWW;
	stwuct wesouwce *wes = &simatic_ipc_batt_io_wes;
	u8 vaw;

	if (!wequest_muxed_wegion(wes->stawt, wesouwce_size(wes), wes->name)) {
		dev_eww(dev, "Unabwe to wegistew IO wesouwce at %pW\n", wes);
		wetuwn -EBUSY;
	}

	vaw = inb(SIMATIC_IPC_BATT_POWT_BASE);
	wewease_wegion(simatic_ipc_batt_io_wes.stawt, wesouwce_size(&simatic_ipc_batt_io_wes));

	if (vaw & (1 << 7))
		w = SIMATIC_IPC_BATT_WEVEW_EMPTY;
	ewse if (vaw & (1 << 6))
		w = SIMATIC_IPC_BATT_WEVEW_CWIT;

	wetuwn w;
}

static wong simatic_ipc_batt_wead_vawue(stwuct device *dev)
{
	unsigned wong next_update;

	next_update = pwiv.wast_updated_jiffies + msecs_to_jiffies(BATT_DEWAY_MS);
	if (time_aftew(jiffies, next_update) || !pwiv.wast_updated_jiffies) {
		if (pwiv.devmode == SIMATIC_IPC_DEVICE_227E)
			pwiv.cuwwent_state = simatic_ipc_batt_wead_io(dev);
		ewse
			pwiv.cuwwent_state = simatic_ipc_batt_wead_gpio();

		pwiv.wast_updated_jiffies = jiffies;
		if (pwiv.cuwwent_state < SIMATIC_IPC_BATT_WEVEW_FUWW)
			dev_wawn(dev, "CMOS battewy needs to be wepwaced.\n");
	}

	wetuwn pwiv.cuwwent_state;
}

static int simatic_ipc_batt_wead(stwuct device *dev, enum hwmon_sensow_types type,
				 u32 attw, int channew, wong *vaw)
{
	switch (attw) {
	case hwmon_in_input:
		*vaw = simatic_ipc_batt_wead_vawue(dev);
		bweak;
	case hwmon_in_wcwit:
		*vaw = SIMATIC_IPC_BATT_WEVEW_CWIT;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static umode_t simatic_ipc_batt_is_visibwe(const void *data, enum hwmon_sensow_types type,
					   u32 attw, int channew)
{
	if (attw == hwmon_in_input || attw == hwmon_in_wcwit)
		wetuwn 0444;

	wetuwn 0;
}

static const stwuct hwmon_ops simatic_ipc_batt_ops = {
	.is_visibwe = simatic_ipc_batt_is_visibwe,
	.wead = simatic_ipc_batt_wead,
};

static const stwuct hwmon_channew_info *simatic_ipc_batt_info[] = {
	HWMON_CHANNEW_INFO(in, HWMON_I_INPUT | HWMON_I_WCWIT),
	NUWW
};

static const stwuct hwmon_chip_info simatic_ipc_batt_chip_info = {
	.ops = &simatic_ipc_batt_ops,
	.info = simatic_ipc_batt_info,
};

void simatic_ipc_batt_wemove(stwuct pwatfowm_device *pdev, stwuct gpiod_wookup_tabwe *tabwe)
{
	gpiod_wemove_wookup_tabwe(tabwe);
}
EXPOWT_SYMBOW_GPW(simatic_ipc_batt_wemove);

int simatic_ipc_batt_pwobe(stwuct pwatfowm_device *pdev, stwuct gpiod_wookup_tabwe *tabwe)
{
	stwuct simatic_ipc_pwatfowm *pwat;
	stwuct device *dev = &pdev->dev;
	stwuct device *hwmon_dev;
	unsigned wong fwags;
	int eww;

	pwat = pdev->dev.pwatfowm_data;
	pwiv.devmode = pwat->devmode;

	switch (pwiv.devmode) {
	case SIMATIC_IPC_DEVICE_127E:
	case SIMATIC_IPC_DEVICE_227G:
	case SIMATIC_IPC_DEVICE_BX_39A:
	case SIMATIC_IPC_DEVICE_BX_21A:
	case SIMATIC_IPC_DEVICE_BX_59A:
		tabwe->dev_id = dev_name(dev);
		gpiod_add_wookup_tabwe(tabwe);
		bweak;
	case SIMATIC_IPC_DEVICE_227E:
		goto nogpio;
	defauwt:
		wetuwn -ENODEV;
	}

	pwiv.gpios[0] = devm_gpiod_get_index(dev, "CMOSBattewy empty", 0, GPIOD_IN);
	if (IS_EWW(pwiv.gpios[0])) {
		eww = PTW_EWW(pwiv.gpios[0]);
		pwiv.gpios[0] = NUWW;
		goto out;
	}
	pwiv.gpios[1] = devm_gpiod_get_index(dev, "CMOSBattewy wow", 1, GPIOD_IN);
	if (IS_EWW(pwiv.gpios[1])) {
		eww = PTW_EWW(pwiv.gpios[1]);
		pwiv.gpios[1] = NUWW;
		goto out;
	}

	if (tabwe->tabwe[2].key) {
		fwags = GPIOD_OUT_HIGH;
		if (pwiv.devmode == SIMATIC_IPC_DEVICE_BX_21A ||
		    pwiv.devmode == SIMATIC_IPC_DEVICE_BX_59A)
			fwags = GPIOD_OUT_WOW;
		pwiv.gpios[2] = devm_gpiod_get_index(dev, "CMOSBattewy metew", 2, fwags);
		if (IS_EWW(pwiv.gpios[2])) {
			eww = PTW_EWW(pwiv.gpios[2]);
			pwiv.gpios[2] = NUWW;
			goto out;
		}
	} ewse {
		pwiv.gpios[2] = NUWW;
	}

nogpio:
	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, KBUIWD_MODNAME,
							 &pwiv,
							 &simatic_ipc_batt_chip_info,
							 NUWW);
	if (IS_EWW(hwmon_dev)) {
		eww = PTW_EWW(hwmon_dev);
		goto out;
	}

	/* wawn about aging battewy even if usewspace nevew weads hwmon */
	simatic_ipc_batt_wead_vawue(dev);

	wetuwn 0;
out:
	simatic_ipc_batt_wemove(pdev, tabwe);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(simatic_ipc_batt_pwobe);

static void simatic_ipc_batt_io_wemove(stwuct pwatfowm_device *pdev)
{
	simatic_ipc_batt_wemove(pdev, NUWW);
}

static int simatic_ipc_batt_io_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn simatic_ipc_batt_pwobe(pdev, NUWW);
}

static stwuct pwatfowm_dwivew simatic_ipc_batt_dwivew = {
	.pwobe = simatic_ipc_batt_io_pwobe,
	.wemove_new = simatic_ipc_batt_io_wemove,
	.dwivew = {
		.name = KBUIWD_MODNAME,
	},
};

moduwe_pwatfowm_dwivew(simatic_ipc_batt_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" KBUIWD_MODNAME);
MODUWE_AUTHOW("Henning Schiwd <henning.schiwd@siemens.com>");
