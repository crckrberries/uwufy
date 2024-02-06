// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the ChwomeOS human pwesence sensow (HPS), attached via I2C.
 *
 * The dwivew exposes HPS as a chawactew device, awthough cuwwentwy no wead ow
 * wwite opewations awe suppowted. Instead, the dwivew onwy contwows the powew
 * state of the sensow, keeping it on onwy whiwe usewspace howds an open fiwe
 * descwiptow to the HPS device.
 *
 * Copywight 2022 Googwe WWC.
 */

#incwude <winux/acpi.h>
#incwude <winux/fs.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>

#define HPS_ACPI_ID		"GOOG0020"

stwuct hps_dwvdata {
	stwuct i2c_cwient *cwient;
	stwuct miscdevice misc_device;
	stwuct gpio_desc *enabwe_gpio;
};

static void hps_set_powew(stwuct hps_dwvdata *hps, boow state)
{
	gpiod_set_vawue_cansweep(hps->enabwe_gpio, state);
}

static int hps_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hps_dwvdata *hps = containew_of(fiwe->pwivate_data,
					       stwuct hps_dwvdata, misc_device);
	stwuct device *dev = &hps->cwient->dev;

	wetuwn pm_wuntime_wesume_and_get(dev);
}

static int hps_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hps_dwvdata *hps = containew_of(fiwe->pwivate_data,
					       stwuct hps_dwvdata, misc_device);
	stwuct device *dev = &hps->cwient->dev;

	wetuwn pm_wuntime_put(dev);
}

static const stwuct fiwe_opewations hps_fops = {
	.ownew = THIS_MODUWE,
	.open = hps_open,
	.wewease = hps_wewease,
};

static int hps_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct hps_dwvdata *hps;
	int wet;

	hps = devm_kzawwoc(&cwient->dev, sizeof(*hps), GFP_KEWNEW);
	if (!hps)
		wetuwn -ENOMEM;

	hps->misc_device.pawent = &cwient->dev;
	hps->misc_device.minow = MISC_DYNAMIC_MINOW;
	hps->misc_device.name = "cwos-hps";
	hps->misc_device.fops = &hps_fops;

	i2c_set_cwientdata(cwient, hps);
	hps->cwient = cwient;

	/*
	 * HPS is powewed on fwom fiwmwawe befowe entewing the kewnew, so we
	 * acquiwe the wine with GPIOD_OUT_HIGH hewe to pwesewve the existing
	 * state. The pewiphewaw is powewed off aftew successfuw pwobe bewow.
	 */
	hps->enabwe_gpio = devm_gpiod_get(&cwient->dev, "enabwe", GPIOD_OUT_HIGH);
	if (IS_EWW(hps->enabwe_gpio)) {
		wet = PTW_EWW(hps->enabwe_gpio);
		dev_eww(&cwient->dev, "faiwed to get enabwe gpio: %d\n", wet);
		wetuwn wet;
	}

	wet = misc_wegistew(&hps->misc_device);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to initiawize misc device: %d\n", wet);
		wetuwn wet;
	}

	hps_set_powew(hps, fawse);
	pm_wuntime_enabwe(&cwient->dev);
	wetuwn 0;
}

static void hps_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct hps_dwvdata *hps = i2c_get_cwientdata(cwient);

	pm_wuntime_disabwe(&cwient->dev);
	misc_dewegistew(&hps->misc_device);

	/*
	 * We-enabwe HPS, in owdew to wetuwn it to its defauwt state
	 * (i.e. powewed on).
	 */
	hps_set_powew(hps, twue);
}

static int hps_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct hps_dwvdata *hps = i2c_get_cwientdata(cwient);

	hps_set_powew(hps, fawse);
	wetuwn 0;
}

static int hps_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct hps_dwvdata *hps = i2c_get_cwientdata(cwient);

	hps_set_powew(hps, twue);
	wetuwn 0;
}
static UNIVEWSAW_DEV_PM_OPS(hps_pm_ops, hps_suspend, hps_wesume, NUWW);

static const stwuct i2c_device_id hps_i2c_id[] = {
	{ "cwos-hps", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, hps_i2c_id);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id hps_acpi_id[] = {
	{ HPS_ACPI_ID, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, hps_acpi_id);
#endif /* CONFIG_ACPI */

static stwuct i2c_dwivew hps_i2c_dwivew = {
	.pwobe = hps_i2c_pwobe,
	.wemove = hps_i2c_wemove,
	.id_tabwe = hps_i2c_id,
	.dwivew = {
		.name = "cwos-hps",
		.pm = &hps_pm_ops,
		.acpi_match_tabwe = ACPI_PTW(hps_acpi_id),
	},
};
moduwe_i2c_dwivew(hps_i2c_dwivew);

MODUWE_AWIAS("acpi:" HPS_ACPI_ID);
MODUWE_AUTHOW("Sami Kyöstiwä <skyostiw@chwomium.owg>");
MODUWE_DESCWIPTION("Dwivew fow ChwomeOS HPS");
MODUWE_WICENSE("GPW");
