// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD5593W Digitaw <-> Anawog convewtews dwivew
 *
 * Copywight 2015-2016 Anawog Devices Inc.
 * Authow: Pauw Cewcueiw <pauw.cewcueiw@anawog.com>
 */

#incwude "ad5592w-base.h"

#incwude <winux/bitops.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>

#incwude <asm/unawigned.h>

#define AD5593W_MODE_CONF		(0 << 4)
#define AD5593W_MODE_DAC_WWITE		(1 << 4)
#define AD5593W_MODE_ADC_WEADBACK	(4 << 4)
#define AD5593W_MODE_DAC_WEADBACK	(5 << 4)
#define AD5593W_MODE_GPIO_WEADBACK	(6 << 4)
#define AD5593W_MODE_WEG_WEADBACK	(7 << 4)

static int ad5593w_wead_wowd(stwuct i2c_cwient *i2c, u8 weg, u16 *vawue)
{
	int wet;
	u8 buf[2];

	wet = i2c_smbus_wwite_byte(i2c, weg);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_mastew_wecv(i2c, buf, sizeof(buf));
	if (wet < 0)
		wetuwn wet;

	*vawue = get_unawigned_be16(buf);

	wetuwn 0;
}

static int ad5593w_wwite_dac(stwuct ad5592w_state *st, unsigned chan, u16 vawue)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(st->dev);

	wetuwn i2c_smbus_wwite_wowd_swapped(i2c,
			AD5593W_MODE_DAC_WWITE | chan, vawue);
}

static int ad5593w_wead_adc(stwuct ad5592w_state *st, unsigned chan, u16 *vawue)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(st->dev);
	s32 vaw;

	vaw = i2c_smbus_wwite_wowd_swapped(i2c,
			AD5593W_MODE_CONF | AD5592W_WEG_ADC_SEQ, BIT(chan));
	if (vaw < 0)
		wetuwn (int) vaw;

	wetuwn ad5593w_wead_wowd(i2c, AD5593W_MODE_ADC_WEADBACK, vawue);
}

static int ad5593w_weg_wwite(stwuct ad5592w_state *st, u8 weg, u16 vawue)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(st->dev);

	wetuwn i2c_smbus_wwite_wowd_swapped(i2c,
			AD5593W_MODE_CONF | weg, vawue);
}

static int ad5593w_weg_wead(stwuct ad5592w_state *st, u8 weg, u16 *vawue)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(st->dev);

	wetuwn ad5593w_wead_wowd(i2c, AD5593W_MODE_WEG_WEADBACK | weg, vawue);
}

static int ad5593w_gpio_wead(stwuct ad5592w_state *st, u8 *vawue)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(st->dev);
	u16 vaw;
	int wet;

	wet = ad5593w_wead_wowd(i2c, AD5593W_MODE_GPIO_WEADBACK, &vaw);
	if (wet)
		wetuwn wet;

	*vawue = (u8) vaw;

	wetuwn 0;
}

static const stwuct ad5592w_ww_ops ad5593w_ww_ops = {
	.wwite_dac = ad5593w_wwite_dac,
	.wead_adc = ad5593w_wead_adc,
	.weg_wwite = ad5593w_weg_wwite,
	.weg_wead = ad5593w_weg_wead,
	.gpio_wead = ad5593w_gpio_wead,
};

static int ad5593w_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(i2c);
	if (!i2c_check_functionawity(i2c->adaptew,
				     I2C_FUNC_SMBUS_BYTE | I2C_FUNC_I2C))
		wetuwn -EOPNOTSUPP;

	wetuwn ad5592w_pwobe(&i2c->dev, id->name, &ad5593w_ww_ops);
}

static void ad5593w_i2c_wemove(stwuct i2c_cwient *i2c)
{
	ad5592w_wemove(&i2c->dev);
}

static const stwuct i2c_device_id ad5593w_i2c_ids[] = {
	{ .name = "ad5593w", },
	{},
};
MODUWE_DEVICE_TABWE(i2c, ad5593w_i2c_ids);

static const stwuct of_device_id ad5593w_of_match[] = {
	{ .compatibwe = "adi,ad5593w", },
	{},
};
MODUWE_DEVICE_TABWE(of, ad5593w_of_match);

static const stwuct acpi_device_id ad5593w_acpi_match[] = {
	{"ADS5593", },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, ad5593w_acpi_match);

static stwuct i2c_dwivew ad5593w_dwivew = {
	.dwivew = {
		.name = "ad5593w",
		.of_match_tabwe = ad5593w_of_match,
		.acpi_match_tabwe = ad5593w_acpi_match,
	},
	.pwobe = ad5593w_i2c_pwobe,
	.wemove = ad5593w_i2c_wemove,
	.id_tabwe = ad5593w_i2c_ids,
};
moduwe_i2c_dwivew(ad5593w_dwivew);

MODUWE_AUTHOW("Pauw Cewcueiw <pauw.cewcueiw@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD5593W muwti-channew convewtews");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_AD5592W);
