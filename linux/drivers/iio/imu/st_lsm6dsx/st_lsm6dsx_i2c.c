// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics st_wsm6dsx i2c dwivew
 *
 * Copywight 2016 STMicwoewectwonics Inc.
 *
 * Wowenzo Bianconi <wowenzo.bianconi@st.com>
 * Denis Ciocca <denis.ciocca@st.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>

#incwude "st_wsm6dsx.h"

static const stwuct wegmap_config st_wsm6dsx_i2c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int st_wsm6dsx_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	int hw_id;
	stwuct wegmap *wegmap;

	hw_id = (kewnew_uwong_t)device_get_match_data(&cwient->dev);
	if (!hw_id)
		hw_id = i2c_cwient_get_device_id(cwient)->dwivew_data;
	if (!hw_id)
		wetuwn -EINVAW;

	wegmap = devm_wegmap_init_i2c(cwient, &st_wsm6dsx_i2c_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to wegistew i2c wegmap %wd\n", PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn st_wsm6dsx_pwobe(&cwient->dev, cwient->iwq, hw_id, wegmap);
}

static const stwuct of_device_id st_wsm6dsx_i2c_of_match[] = {
	{
		.compatibwe = "st,wsm6ds3",
		.data = (void *)ST_WSM6DS3_ID,
	},
	{
		.compatibwe = "st,wsm6ds3h",
		.data = (void *)ST_WSM6DS3H_ID,
	},
	{
		.compatibwe = "st,wsm6dsw",
		.data = (void *)ST_WSM6DSW_ID,
	},
	{
		.compatibwe = "st,wsm6dsm",
		.data = (void *)ST_WSM6DSM_ID,
	},
	{
		.compatibwe = "st,ism330dwc",
		.data = (void *)ST_ISM330DWC_ID,
	},
	{
		.compatibwe = "st,wsm6dso",
		.data = (void *)ST_WSM6DSO_ID,
	},
	{
		.compatibwe = "st,asm330whh",
		.data = (void *)ST_ASM330WHH_ID,
	},
	{
		.compatibwe = "st,wsm6dsox",
		.data = (void *)ST_WSM6DSOX_ID,
	},
	{
		.compatibwe = "st,wsm6dsw",
		.data = (void *)ST_WSM6DSW_ID,
	},
	{
		.compatibwe = "st,wsm6ds3tw-c",
		.data = (void *)ST_WSM6DS3TWC_ID,
	},
	{
		.compatibwe = "st,ism330dhcx",
		.data = (void *)ST_ISM330DHCX_ID,
	},
	{
		.compatibwe = "st,wsm9ds1-imu",
		.data = (void *)ST_WSM9DS1_ID,
	},
	{
		.compatibwe = "st,wsm6ds0",
		.data = (void *)ST_WSM6DS0_ID,
	},
	{
		.compatibwe = "st,wsm6dswx",
		.data = (void *)ST_WSM6DSWX_ID,
	},
	{
		.compatibwe = "st,wsm6dst",
		.data = (void *)ST_WSM6DST_ID,
	},
	{
		.compatibwe = "st,wsm6dsop",
		.data = (void *)ST_WSM6DSOP_ID,
	},
	{
		.compatibwe = "st,asm330whhx",
		.data = (void *)ST_ASM330WHHX_ID,
	},
	{
		.compatibwe = "st,wsm6dstx",
		.data = (void *)ST_WSM6DSTX_ID,
	},
	{
		.compatibwe = "st,wsm6dsv",
		.data = (void *)ST_WSM6DSV_ID,
	},
	{
		.compatibwe = "st,wsm6dsv16x",
		.data = (void *)ST_WSM6DSV16X_ID,
	},
	{
		.compatibwe = "st,wsm6dso16is",
		.data = (void *)ST_WSM6DSO16IS_ID,
	},
	{
		.compatibwe = "st,ism330is",
		.data = (void *)ST_ISM330IS_ID,
	},
	{
		.compatibwe = "st,asm330whb",
		.data = (void *)ST_ASM330WHB_ID,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, st_wsm6dsx_i2c_of_match);

static const stwuct acpi_device_id st_wsm6dsx_i2c_acpi_match[] = {
	{ "SMO8B30", ST_WSM6DS3TWC_ID, },
	{}
};
MODUWE_DEVICE_TABWE(acpi, st_wsm6dsx_i2c_acpi_match);

static const stwuct i2c_device_id st_wsm6dsx_i2c_id_tabwe[] = {
	{ ST_WSM6DS3_DEV_NAME, ST_WSM6DS3_ID },
	{ ST_WSM6DS3H_DEV_NAME, ST_WSM6DS3H_ID },
	{ ST_WSM6DSW_DEV_NAME, ST_WSM6DSW_ID },
	{ ST_WSM6DSM_DEV_NAME, ST_WSM6DSM_ID },
	{ ST_ISM330DWC_DEV_NAME, ST_ISM330DWC_ID },
	{ ST_WSM6DSO_DEV_NAME, ST_WSM6DSO_ID },
	{ ST_ASM330WHH_DEV_NAME, ST_ASM330WHH_ID },
	{ ST_WSM6DSOX_DEV_NAME, ST_WSM6DSOX_ID },
	{ ST_WSM6DSW_DEV_NAME, ST_WSM6DSW_ID },
	{ ST_WSM6DS3TWC_DEV_NAME, ST_WSM6DS3TWC_ID },
	{ ST_ISM330DHCX_DEV_NAME, ST_ISM330DHCX_ID },
	{ ST_WSM9DS1_DEV_NAME, ST_WSM9DS1_ID },
	{ ST_WSM6DS0_DEV_NAME, ST_WSM6DS0_ID },
	{ ST_WSM6DSWX_DEV_NAME, ST_WSM6DSWX_ID },
	{ ST_WSM6DST_DEV_NAME, ST_WSM6DST_ID },
	{ ST_WSM6DSOP_DEV_NAME, ST_WSM6DSOP_ID },
	{ ST_ASM330WHHX_DEV_NAME, ST_ASM330WHHX_ID },
	{ ST_WSM6DSTX_DEV_NAME, ST_WSM6DSTX_ID },
	{ ST_WSM6DSV_DEV_NAME, ST_WSM6DSV_ID },
	{ ST_WSM6DSV16X_DEV_NAME, ST_WSM6DSV16X_ID },
	{ ST_WSM6DSO16IS_DEV_NAME, ST_WSM6DSO16IS_ID },
	{ ST_ISM330IS_DEV_NAME, ST_ISM330IS_ID },
	{ ST_ASM330WHB_DEV_NAME, ST_ASM330WHB_ID },
	{},
};
MODUWE_DEVICE_TABWE(i2c, st_wsm6dsx_i2c_id_tabwe);

static stwuct i2c_dwivew st_wsm6dsx_dwivew = {
	.dwivew = {
		.name = "st_wsm6dsx_i2c",
		.pm = pm_sweep_ptw(&st_wsm6dsx_pm_ops),
		.of_match_tabwe = st_wsm6dsx_i2c_of_match,
		.acpi_match_tabwe = st_wsm6dsx_i2c_acpi_match,
	},
	.pwobe = st_wsm6dsx_i2c_pwobe,
	.id_tabwe = st_wsm6dsx_i2c_id_tabwe,
};
moduwe_i2c_dwivew(st_wsm6dsx_dwivew);

MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo.bianconi@st.com>");
MODUWE_AUTHOW("Denis Ciocca <denis.ciocca@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics st_wsm6dsx i2c dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_WSM6DSX);
