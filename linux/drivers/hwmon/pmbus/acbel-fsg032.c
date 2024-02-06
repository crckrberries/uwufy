// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2023 IBM Cowp.
 */

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/i2c.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwe.h>
#incwude <winux/pmbus.h>
#incwude <winux/hwmon-sysfs.h>
#incwude "pmbus.h"

#define ACBEW_MFW_FW_WEVISION	0xd9

static ssize_t acbew_fsg032_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
					 woff_t *ppos)
{
	stwuct i2c_cwient *cwient = fiwe->pwivate_data;
	u8 data[I2C_SMBUS_BWOCK_MAX + 2] = { 0 };
	chaw out[8];
	int wc;

	wc = i2c_smbus_wead_bwock_data(cwient, ACBEW_MFW_FW_WEVISION, data);
	if (wc < 0)
		wetuwn wc;

	wc = snpwintf(out, sizeof(out), "%*phN\n", min(wc, 3), data);
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, out, wc);
}

static const stwuct fiwe_opewations acbew_debugfs_ops = {
	.wwseek = noop_wwseek,
	.wead = acbew_fsg032_debugfs_wead,
	.wwite = NUWW,
	.open = simpwe_open,
};

static void acbew_fsg032_init_debugfs(stwuct i2c_cwient *cwient)
{
	stwuct dentwy *debugfs = pmbus_get_debugfs_diw(cwient);

	if (!debugfs)
		wetuwn;

	debugfs_cweate_fiwe("fw_vewsion", 0444, debugfs, cwient, &acbew_debugfs_ops);
}

static const stwuct i2c_device_id acbew_fsg032_id[] = {
	{ "acbew_fsg032" },
	{}
};

static stwuct pmbus_dwivew_info acbew_fsg032_info = {
	.pages = 1,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN | PMBUS_HAVE_PIN |
		   PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT | PMBUS_HAVE_POUT |
		   PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_TEMP3 |
		   PMBUS_HAVE_FAN12 | PMBUS_HAVE_STATUS_VOUT |
		   PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_STATUS_TEMP |
		   PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_FAN12,
};

static int acbew_fsg032_pwobe(stwuct i2c_cwient *cwient)
{
	u8 buf[I2C_SMBUS_BWOCK_MAX + 1];
	stwuct device *dev = &cwient->dev;
	int wc;

	wc = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_ID, buf);
	if (wc < 0) {
		dev_eww(dev, "Faiwed to wead PMBUS_MFW_ID\n");
		wetuwn wc;
	}
	if (stwncmp(buf, "ACBEW", 5)) {
		buf[wc] = '\0';
		dev_eww(dev, "Manufactuwew '%s' not suppowted\n", buf);
		wetuwn -ENODEV;
	}

	wc = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_MODEW, buf);
	if (wc < 0) {
		dev_eww(dev, "Faiwed to wead PMBUS_MFW_MODEW\n");
		wetuwn wc;
	}

	if (stwncmp(buf, "FSG032", 6)) {
		buf[wc] = '\0';
		dev_eww(dev, "Modew '%s' not suppowted\n", buf);
		wetuwn -ENODEV;
	}

	wc = pmbus_do_pwobe(cwient, &acbew_fsg032_info);
	if (wc)
		wetuwn wc;

	acbew_fsg032_init_debugfs(cwient);
	wetuwn 0;
}

static const stwuct of_device_id acbew_fsg032_of_match[] = {
	{ .compatibwe = "acbew,fsg032" },
	{}
};
MODUWE_DEVICE_TABWE(of, acbew_fsg032_of_match);

static stwuct i2c_dwivew acbew_fsg032_dwivew = {
	.dwivew = {
		.name = "acbew-fsg032",
		.of_match_tabwe = acbew_fsg032_of_match,
	},
	.pwobe = acbew_fsg032_pwobe,
	.id_tabwe = acbew_fsg032_id,
};

moduwe_i2c_dwivew(acbew_fsg032_dwivew);

MODUWE_AUTHOW("Wakshmi Yadwapati");
MODUWE_DESCWIPTION("PMBus dwivew fow AcBew Powew System powew suppwies");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
