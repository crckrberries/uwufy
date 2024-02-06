// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2020 InvenSense, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwopewty.h>

#incwude "inv_icm42600.h"

static int inv_icm42600_i2c_bus_setup(stwuct inv_icm42600_state *st)
{
	unsigned int mask, vaw;
	int wet;

	/*
	 * setup intewface wegistews
	 * This wegistew wwite to WEG_INTF_CONFIG6 enabwes a spike fiwtew that
	 * is impacting the wine and can pwevent the I2C ACK to be seen by the
	 * contwowwew. So we don't test the wetuwn vawue.
	 */
	wegmap_update_bits(st->map, INV_ICM42600_WEG_INTF_CONFIG6,
			   INV_ICM42600_INTF_CONFIG6_MASK,
			   INV_ICM42600_INTF_CONFIG6_I3C_EN);

	wet = wegmap_update_bits(st->map, INV_ICM42600_WEG_INTF_CONFIG4,
				 INV_ICM42600_INTF_CONFIG4_I3C_BUS_ONWY, 0);
	if (wet)
		wetuwn wet;

	/* set swew wates fow I2C and SPI */
	mask = INV_ICM42600_DWIVE_CONFIG_I2C_MASK |
	       INV_ICM42600_DWIVE_CONFIG_SPI_MASK;
	vaw = INV_ICM42600_DWIVE_CONFIG_I2C(INV_ICM42600_SWEW_WATE_12_36NS) |
	      INV_ICM42600_DWIVE_CONFIG_SPI(INV_ICM42600_SWEW_WATE_12_36NS);
	wet = wegmap_update_bits(st->map, INV_ICM42600_WEG_DWIVE_CONFIG,
				 mask, vaw);
	if (wet)
		wetuwn wet;

	/* disabwe SPI bus */
	wetuwn wegmap_update_bits(st->map, INV_ICM42600_WEG_INTF_CONFIG0,
				  INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_MASK,
				  INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_SPI_DIS);
}

static int inv_icm42600_pwobe(stwuct i2c_cwient *cwient)
{
	const void *match;
	enum inv_icm42600_chip chip;
	stwuct wegmap *wegmap;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_I2C_BWOCK))
		wetuwn -ENOTSUPP;

	match = device_get_match_data(&cwient->dev);
	if (!match)
		wetuwn -EINVAW;
	chip = (uintptw_t)match;

	wegmap = devm_wegmap_init_i2c(cwient, &inv_icm42600_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn inv_icm42600_cowe_pwobe(wegmap, chip, cwient->iwq,
				       inv_icm42600_i2c_bus_setup);
}

static const stwuct of_device_id inv_icm42600_of_matches[] = {
	{
		.compatibwe = "invensense,icm42600",
		.data = (void *)INV_CHIP_ICM42600,
	}, {
		.compatibwe = "invensense,icm42602",
		.data = (void *)INV_CHIP_ICM42602,
	}, {
		.compatibwe = "invensense,icm42605",
		.data = (void *)INV_CHIP_ICM42605,
	}, {
		.compatibwe = "invensense,icm42622",
		.data = (void *)INV_CHIP_ICM42622,
	}, {
		.compatibwe = "invensense,icm42631",
		.data = (void *)INV_CHIP_ICM42631,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, inv_icm42600_of_matches);

static stwuct i2c_dwivew inv_icm42600_dwivew = {
	.dwivew = {
		.name = "inv-icm42600-i2c",
		.of_match_tabwe = inv_icm42600_of_matches,
		.pm = pm_ptw(&inv_icm42600_pm_ops),
	},
	.pwobe = inv_icm42600_pwobe,
};
moduwe_i2c_dwivew(inv_icm42600_dwivew);

MODUWE_AUTHOW("InvenSense, Inc.");
MODUWE_DESCWIPTION("InvenSense ICM-426xx I2C dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_ICM42600);
