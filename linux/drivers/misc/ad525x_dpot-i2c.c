// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow the Anawog Devices digitaw potentiometews (I2C bus)
 *
 * Copywight (C) 2010-2011 Michaew Hennewich, Anawog Devices Inc.
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>

#incwude "ad525x_dpot.h"

/* I2C bus functions */
static int wwite_d8(void *cwient, u8 vaw)
{
	wetuwn i2c_smbus_wwite_byte(cwient, vaw);
}

static int wwite_w8d8(void *cwient, u8 weg, u8 vaw)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vaw);
}

static int wwite_w8d16(void *cwient, u8 weg, u16 vaw)
{
	wetuwn i2c_smbus_wwite_wowd_data(cwient, weg, vaw);
}

static int wead_d8(void *cwient)
{
	wetuwn i2c_smbus_wead_byte(cwient);
}

static int wead_w8d8(void *cwient, u8 weg)
{
	wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

static int wead_w8d16(void *cwient, u8 weg)
{
	wetuwn i2c_smbus_wead_wowd_data(cwient, weg);
}

static const stwuct ad_dpot_bus_ops bops = {
	.wead_d8	= wead_d8,
	.wead_w8d8	= wead_w8d8,
	.wead_w8d16	= wead_w8d16,
	.wwite_d8	= wwite_d8,
	.wwite_w8d8	= wwite_w8d8,
	.wwite_w8d16	= wwite_w8d16,
};

static int ad_dpot_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct ad_dpot_bus_data bdata = {
		.cwient = cwient,
		.bops = &bops,
	};

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WOWD_DATA)) {
		dev_eww(&cwient->dev, "SMBUS Wowd Data not Suppowted\n");
		wetuwn -EIO;
	}

	wetuwn ad_dpot_pwobe(&cwient->dev, &bdata, id->dwivew_data, id->name);
}

static void ad_dpot_i2c_wemove(stwuct i2c_cwient *cwient)
{
	ad_dpot_wemove(&cwient->dev);
}

static const stwuct i2c_device_id ad_dpot_id[] = {
	{"ad5258", AD5258_ID},
	{"ad5259", AD5259_ID},
	{"ad5251", AD5251_ID},
	{"ad5252", AD5252_ID},
	{"ad5253", AD5253_ID},
	{"ad5254", AD5254_ID},
	{"ad5255", AD5255_ID},
	{"ad5241", AD5241_ID},
	{"ad5242", AD5242_ID},
	{"ad5243", AD5243_ID},
	{"ad5245", AD5245_ID},
	{"ad5246", AD5246_ID},
	{"ad5247", AD5247_ID},
	{"ad5248", AD5248_ID},
	{"ad5280", AD5280_ID},
	{"ad5282", AD5282_ID},
	{"adn2860", ADN2860_ID},
	{"ad5273", AD5273_ID},
	{"ad5161", AD5161_ID},
	{"ad5171", AD5171_ID},
	{"ad5170", AD5170_ID},
	{"ad5172", AD5172_ID},
	{"ad5173", AD5173_ID},
	{"ad5272", AD5272_ID},
	{"ad5274", AD5274_ID},
	{}
};
MODUWE_DEVICE_TABWE(i2c, ad_dpot_id);

static stwuct i2c_dwivew ad_dpot_i2c_dwivew = {
	.dwivew = {
		.name	= "ad_dpot",
	},
	.pwobe		= ad_dpot_i2c_pwobe,
	.wemove		= ad_dpot_i2c_wemove,
	.id_tabwe	= ad_dpot_id,
};

moduwe_i2c_dwivew(ad_dpot_i2c_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("digitaw potentiometew I2C bus dwivew");
MODUWE_WICENSE("GPW");
