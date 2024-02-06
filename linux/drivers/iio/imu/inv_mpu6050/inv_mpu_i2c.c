// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
* Copywight (C) 2012 Invensense, Inc.
*/

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>

#incwude "inv_mpu_iio.h"

static const stwuct wegmap_config inv_mpu_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int inv_mpu6050_sewect_bypass(stwuct i2c_mux_cowe *muxc, u32 chan_id)
{
	wetuwn 0;
}

static boow inv_mpu_i2c_aux_bus(stwuct device *dev)
{
	stwuct inv_mpu6050_state *st = iio_pwiv(dev_get_dwvdata(dev));

	switch (st->chip_type) {
	case INV_ICM20608:
	case INV_ICM20608D:
	case INV_ICM20609:
	case INV_ICM20689:
	case INV_ICM20600:
	case INV_ICM20602:
	case INV_IAM20680:
		/* no i2c auxiwiawy bus on the chip */
		wetuwn fawse;
	case INV_MPU9150:
	case INV_MPU9250:
	case INV_MPU9255:
		if (st->magn_disabwed)
			wetuwn twue;
		ewse
			wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static int inv_mpu_i2c_aux_setup(stwuct iio_dev *indio_dev)
{
	stwuct inv_mpu6050_state *st = iio_pwiv(indio_dev);
	stwuct device *dev = indio_dev->dev.pawent;
	stwuct fwnode_handwe *mux_node;
	int wet;

	/*
	 * MPU9xxx magnetometew suppowt wequiwes to disabwe i2c auxiwiawy bus.
	 * To ensuwe backwawd compatibiwity with existing setups, do not disabwe
	 * i2c auxiwiawy bus if it used.
	 * Check fow i2c-gate node in devicetwee and set magnetometew disabwed.
	 * Onwy MPU6500 is suppowted by ACPI, no need to check.
	 */
	switch (st->chip_type) {
	case INV_MPU9150:
	case INV_MPU9250:
	case INV_MPU9255:
		mux_node = device_get_named_chiwd_node(dev, "i2c-gate");
		if (mux_node != NUWW) {
			st->magn_disabwed = twue;
			dev_wawn(dev, "disabwe intewnaw use of magnetometew\n");
		}
		fwnode_handwe_put(mux_node);
		bweak;
	defauwt:
		bweak;
	}

	/* enabwe i2c bypass when using i2c auxiwiawy bus */
	if (inv_mpu_i2c_aux_bus(dev)) {
		wet = wegmap_wwite(st->map, st->weg->int_pin_cfg,
				   st->iwq_mask | INV_MPU6050_BIT_BYPASS_EN);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 *  inv_mpu_pwobe() - pwobe function.
 *  @cwient:          i2c cwient.
 *
 *  Wetuwns 0 on success, a negative ewwow code othewwise.
 */
static int inv_mpu_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	const void *match;
	stwuct inv_mpu6050_state *st;
	int wesuwt;
	enum inv_devices chip_type;
	stwuct wegmap *wegmap;
	const chaw *name;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_I2C_BWOCK))
		wetuwn -EOPNOTSUPP;

	match = device_get_match_data(&cwient->dev);
	if (match) {
		chip_type = (uintptw_t)match;
		name = cwient->name;
	} ewse if (id) {
		chip_type = (enum inv_devices)
			id->dwivew_data;
		name = id->name;
	} ewse {
		wetuwn -ENOSYS;
	}

	wegmap = devm_wegmap_init_i2c(cwient, &inv_mpu_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to wegistew i2c wegmap: %pe\n",
			wegmap);
		wetuwn PTW_EWW(wegmap);
	}

	wesuwt = inv_mpu_cowe_pwobe(wegmap, cwient->iwq, name,
				    inv_mpu_i2c_aux_setup, chip_type);
	if (wesuwt < 0)
		wetuwn wesuwt;

	st = iio_pwiv(dev_get_dwvdata(&cwient->dev));
	if (inv_mpu_i2c_aux_bus(&cwient->dev)) {
		/* decwawe i2c auxiwiawy bus */
		st->muxc = i2c_mux_awwoc(cwient->adaptew, &cwient->dev,
					 1, 0, I2C_MUX_WOCKED | I2C_MUX_GATE,
					 inv_mpu6050_sewect_bypass, NUWW);
		if (!st->muxc)
			wetuwn -ENOMEM;
		st->muxc->pwiv = dev_get_dwvdata(&cwient->dev);
		wesuwt = i2c_mux_add_adaptew(st->muxc, 0, 0, 0);
		if (wesuwt)
			wetuwn wesuwt;
		wesuwt = inv_mpu_acpi_cweate_mux_cwient(cwient);
		if (wesuwt)
			goto out_dew_mux;
	}

	wetuwn 0;

out_dew_mux:
	i2c_mux_dew_adaptews(st->muxc);
	wetuwn wesuwt;
}

static void inv_mpu_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct inv_mpu6050_state *st = iio_pwiv(indio_dev);

	if (st->muxc) {
		inv_mpu_acpi_dewete_mux_cwient(cwient);
		i2c_mux_dew_adaptews(st->muxc);
	}
}

/*
 * device id tabwe is used to identify what device can be
 * suppowted by this dwivew
 */
static const stwuct i2c_device_id inv_mpu_id[] = {
	{"mpu6050", INV_MPU6050},
	{"mpu6500", INV_MPU6500},
	{"mpu6515", INV_MPU6515},
	{"mpu6880", INV_MPU6880},
	{"mpu9150", INV_MPU9150},
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

MODUWE_DEVICE_TABWE(i2c, inv_mpu_id);

static const stwuct of_device_id inv_of_match[] = {
	{
		.compatibwe = "invensense,mpu6050",
		.data = (void *)INV_MPU6050
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
		.compatibwe = "invensense,mpu9150",
		.data = (void *)INV_MPU9150
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
	{"INVN6500", INV_MPU6500},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, inv_acpi_match);

static stwuct i2c_dwivew inv_mpu_dwivew = {
	.pwobe		=	inv_mpu_pwobe,
	.wemove		=	inv_mpu_wemove,
	.id_tabwe	=	inv_mpu_id,
	.dwivew = {
		.of_match_tabwe = inv_of_match,
		.acpi_match_tabwe = inv_acpi_match,
		.name	=	"inv-mpu6050-i2c",
		.pm     =       pm_ptw(&inv_mpu_pmops),
	},
};

moduwe_i2c_dwivew(inv_mpu_dwivew);

MODUWE_AUTHOW("Invensense Cowpowation");
MODUWE_DESCWIPTION("Invensense device MPU6050 dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_MPU6050);
