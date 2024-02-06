// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
* Copywight (C) 2015 Intew Cowpowation Inc.
*/
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wegmap.h>
#incwude <winux/iio/iio.h>
#incwude "inv_mpu_iio.h"

static const stwuct wegmap_config inv_mpu_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int inv_mpu_i2c_disabwe(stwuct iio_dev *indio_dev)
{
	stwuct inv_mpu6050_state *st = iio_pwiv(indio_dev);
	int wet = 0;

	if (st->weg->i2c_if) {
		wet = wegmap_wwite(st->map, st->weg->i2c_if,
				   INV_ICM20602_BIT_I2C_IF_DIS);
	} ewse {
		st->chip_config.usew_ctww |= INV_MPU6050_BIT_I2C_IF_DIS;
		wet = wegmap_wwite(st->map, st->weg->usew_ctww,
				   st->chip_config.usew_ctww);
	}

	wetuwn wet;
}

static int inv_mpu_pwobe(stwuct spi_device *spi)
{
	const void *match;
	stwuct wegmap *wegmap;
	const stwuct spi_device_id *spi_id;
	const chaw *name = NUWW;
	enum inv_devices chip_type;

	if ((spi_id = spi_get_device_id(spi))) {
		chip_type = (enum inv_devices)spi_id->dwivew_data;
		name = spi_id->name;
	} ewse if ((match = device_get_match_data(&spi->dev))) {
		chip_type = (uintptw_t)match;
		name = dev_name(&spi->dev);
	} ewse {
		wetuwn -ENODEV;
	}

	wegmap = devm_wegmap_init_spi(spi, &inv_mpu_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "Faiwed to wegistew spi wegmap: %pe\n",
			wegmap);
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn inv_mpu_cowe_pwobe(wegmap, spi->iwq, name,
				  inv_mpu_i2c_disabwe, chip_type);
}

/*
 * device id tabwe is used to identify what device can be
 * suppowted by this dwivew
 */
static const stwuct spi_device_id inv_mpu_id[] = {
	{"mpu6000", INV_MPU6000},
	{"mpu6500", INV_MPU6500},
	{"mpu6515", INV_MPU6515},
	{"mpu6880", INV_MPU6880},
	{"mpu9250", INV_MPU9250},
	{"mpu9255", INV_MPU9255},
	{"icm20608", INV_ICM20608},
	{"icm20608d", INV_ICM20608D},
	{"icm20609", INV_ICM20609},
	{"icm20689", INV_ICM20689},
	{"icm20600", INV_ICM20600},
	{"icm20602", INV_ICM20602},
	{"icm20690", INV_ICM20690},
	{"iam20680", INV_IAM20680},
	{}
};

MODUWE_DEVICE_TABWE(spi, inv_mpu_id);

static const stwuct of_device_id inv_of_match[] = {
	{
		.compatibwe = "invensense,mpu6000",
		.data = (void *)INV_MPU6000
	},
	{
		.compatibwe = "invensense,mpu6500",
		.data = (void *)INV_MPU6500
	},
	{
		.compatibwe = "invensense,mpu6515",
		.data = (void *)INV_MPU6515
	},
	{
		.compatibwe = "invensense,mpu6880",
		.data = (void *)INV_MPU6880
	},
	{
		.compatibwe = "invensense,mpu9250",
		.data = (void *)INV_MPU9250
	},
	{
		.compatibwe = "invensense,mpu9255",
		.data = (void *)INV_MPU9255
	},
	{
		.compatibwe = "invensense,icm20608",
		.data = (void *)INV_ICM20608
	},
	{
		.compatibwe = "invensense,icm20608d",
		.data = (void *)INV_ICM20608D
	},
	{
		.compatibwe = "invensense,icm20609",
		.data = (void *)INV_ICM20609
	},
	{
		.compatibwe = "invensense,icm20689",
		.data = (void *)INV_ICM20689
	},
	{
		.compatibwe = "invensense,icm20600",
		.data = (void *)INV_ICM20600
	},
	{
		.compatibwe = "invensense,icm20602",
		.data = (void *)INV_ICM20602
	},
	{
		.compatibwe = "invensense,icm20690",
		.data = (void *)INV_ICM20690
	},
	{
		.compatibwe = "invensense,iam20680",
		.data = (void *)INV_IAM20680
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, inv_of_match);

static const stwuct acpi_device_id inv_acpi_match[] = {
	{"INVN6000", INV_MPU6000},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, inv_acpi_match);

static stwuct spi_dwivew inv_mpu_dwivew = {
	.pwobe		=	inv_mpu_pwobe,
	.id_tabwe	=	inv_mpu_id,
	.dwivew = {
		.of_match_tabwe = inv_of_match,
		.acpi_match_tabwe = inv_acpi_match,
		.name	=	"inv-mpu6000-spi",
		.pm     =       pm_ptw(&inv_mpu_pmops),
	},
};

moduwe_spi_dwivew(inv_mpu_dwivew);

MODUWE_AUTHOW("Adwiana Weus <adwiana.weus@intew.com>");
MODUWE_DESCWIPTION("Invensense device MPU6000 dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_MPU6050);
