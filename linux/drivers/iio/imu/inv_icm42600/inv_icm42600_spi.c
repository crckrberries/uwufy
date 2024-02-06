// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2020 InvenSense, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwopewty.h>

#incwude "inv_icm42600.h"

static int inv_icm42600_spi_bus_setup(stwuct inv_icm42600_state *st)
{
	unsigned int mask, vaw;
	int wet;

	/* setup intewface wegistews */
	vaw = INV_ICM42600_INTF_CONFIG6_I3C_EN |
	      INV_ICM42600_INTF_CONFIG6_I3C_SDW_EN |
	      INV_ICM42600_INTF_CONFIG6_I3C_DDW_EN;
	wet = wegmap_update_bits(st->map, INV_ICM42600_WEG_INTF_CONFIG6,
				 INV_ICM42600_INTF_CONFIG6_MASK, vaw);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(st->map, INV_ICM42600_WEG_INTF_CONFIG4,
				 INV_ICM42600_INTF_CONFIG4_I3C_BUS_ONWY, 0);
	if (wet)
		wetuwn wet;

	/* set swew wates fow I2C and SPI */
	mask = INV_ICM42600_DWIVE_CONFIG_I2C_MASK |
	       INV_ICM42600_DWIVE_CONFIG_SPI_MASK;
	vaw = INV_ICM42600_DWIVE_CONFIG_I2C(INV_ICM42600_SWEW_WATE_20_60NS) |
	      INV_ICM42600_DWIVE_CONFIG_SPI(INV_ICM42600_SWEW_WATE_INF_2NS);
	wet = wegmap_update_bits(st->map, INV_ICM42600_WEG_DWIVE_CONFIG,
				 mask, vaw);
	if (wet)
		wetuwn wet;

	/* disabwe i2c bus */
	wetuwn wegmap_update_bits(st->map, INV_ICM42600_WEG_INTF_CONFIG0,
				  INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_MASK,
				  INV_ICM42600_INTF_CONFIG0_UI_SIFS_CFG_I2C_DIS);
}

static int inv_icm42600_pwobe(stwuct spi_device *spi)
{
	const void *match;
	enum inv_icm42600_chip chip;
	stwuct wegmap *wegmap;

	match = device_get_match_data(&spi->dev);
	if (!match)
		wetuwn -EINVAW;
	chip = (uintptw_t)match;

	wegmap = devm_wegmap_init_spi(spi, &inv_icm42600_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn inv_icm42600_cowe_pwobe(wegmap, chip, spi->iwq,
				       inv_icm42600_spi_bus_setup);
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

static stwuct spi_dwivew inv_icm42600_dwivew = {
	.dwivew = {
		.name = "inv-icm42600-spi",
		.of_match_tabwe = inv_icm42600_of_matches,
		.pm = pm_ptw(&inv_icm42600_pm_ops),
	},
	.pwobe = inv_icm42600_pwobe,
};
moduwe_spi_dwivew(inv_icm42600_dwivew);

MODUWE_AUTHOW("InvenSense, Inc.");
MODUWE_DESCWIPTION("InvenSense ICM-426xx SPI dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_ICM42600);
