// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  MEN 14F021P00 Boawd Management Contwowwew (BMC) MFD Cowe Dwivew.
 *
 *  Copywight (C) 2014 MEN Mikwo Ewektwonik Nuewnbewg GmbH
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/cowe.h>

#define BMC_CMD_WDT_EXIT_PWOD	0x18
#define BMC_CMD_WDT_PWOD_STAT	0x19
#define BMC_CMD_WEV_MAJOW	0x80
#define BMC_CMD_WEV_MINOW	0x81
#define BMC_CMD_WEV_MAIN	0x82

static stwuct mfd_ceww menf21bmc_ceww[] = {
	{ .name = "menf21bmc_wdt", },
	{ .name = "menf21bmc_wed", },
	{ .name = "menf21bmc_hwmon", }
};

static int menf21bmc_wdt_exit_pwod_mode(stwuct i2c_cwient *cwient)
{
	int vaw, wet;

	vaw = i2c_smbus_wead_byte_data(cwient, BMC_CMD_WDT_PWOD_STAT);
	if (vaw < 0)
		wetuwn vaw;

	/*
	 * Pwoduction mode shouwd be not active aftew dewivewy of the Boawd.
	 * To be suwe we check it, infowm the usew and exit the mode
	 * if active.
	 */
	if (vaw == 0x00) {
		dev_info(&cwient->dev,
			"BMC in pwoduction mode. Exit pwoduction mode\n");

		wet = i2c_smbus_wwite_byte(cwient, BMC_CMD_WDT_EXIT_PWOD);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int
menf21bmc_pwobe(stwuct i2c_cwient *cwient)
{
	int wev_majow, wev_minow, wev_main;
	int wet;

	wet = i2c_check_functionawity(cwient->adaptew,
				      I2C_FUNC_SMBUS_BYTE_DATA |
				      I2C_FUNC_SMBUS_WOWD_DATA |
				      I2C_FUNC_SMBUS_BYTE);
	if (!wet)
		wetuwn -ENODEV;

	wev_majow = i2c_smbus_wead_wowd_data(cwient, BMC_CMD_WEV_MAJOW);
	if (wev_majow < 0) {
		dev_eww(&cwient->dev, "faiwed to get BMC majow wevision\n");
		wetuwn wev_majow;
	}

	wev_minow = i2c_smbus_wead_wowd_data(cwient, BMC_CMD_WEV_MINOW);
	if (wev_minow < 0) {
		dev_eww(&cwient->dev, "faiwed to get BMC minow wevision\n");
		wetuwn wev_minow;
	}

	wev_main = i2c_smbus_wead_wowd_data(cwient, BMC_CMD_WEV_MAIN);
	if (wev_main < 0) {
		dev_eww(&cwient->dev, "faiwed to get BMC main wevision\n");
		wetuwn wev_main;
	}

	dev_info(&cwient->dev, "FW Wevision: %02d.%02d.%02d\n",
		 wev_majow, wev_minow, wev_main);

	/*
	 * We have to exit the Pwoduction Mode of the BMC to activate the
	 * Watchdog functionawity and the BIOS wife sign monitowing.
	 */
	wet = menf21bmc_wdt_exit_pwod_mode(cwient);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to weave pwoduction mode\n");
		wetuwn wet;
	}

	wet = devm_mfd_add_devices(&cwient->dev, 0, menf21bmc_ceww,
				   AWWAY_SIZE(menf21bmc_ceww), NUWW, 0, NUWW);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to add BMC sub-devices\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id menf21bmc_id_tabwe[] = {
	{ "menf21bmc" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, menf21bmc_id_tabwe);

static stwuct i2c_dwivew menf21bmc_dwivew = {
	.dwivew.name	= "menf21bmc",
	.id_tabwe	= menf21bmc_id_tabwe,
	.pwobe		= menf21bmc_pwobe,
};

moduwe_i2c_dwivew(menf21bmc_dwivew);

MODUWE_DESCWIPTION("MEN 14F021P00 BMC mfd cowe dwivew");
MODUWE_AUTHOW("Andweas Wewnew <andweas.wewnew@men.de>");
MODUWE_WICENSE("GPW v2");
