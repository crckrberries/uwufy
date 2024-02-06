// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AD714X CapTouch Pwogwammabwe Contwowwew dwivew (I2C bus)
 *
 * Copywight 2009-2011 Anawog Devices Inc.
 */

#incwude <winux/input.h>	/* BUS_I2C */
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/pm.h>
#incwude "ad714x.h"

static int ad714x_i2c_wwite(stwuct ad714x_chip *chip,
			    unsigned showt weg, unsigned showt data)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(chip->dev);
	int ewwow;

	chip->xfew_buf[0] = cpu_to_be16(weg);
	chip->xfew_buf[1] = cpu_to_be16(data);

	ewwow = i2c_mastew_send(cwient, (u8 *)chip->xfew_buf,
				2 * sizeof(*chip->xfew_buf));
	if (unwikewy(ewwow < 0)) {
		dev_eww(&cwient->dev, "I2C wwite ewwow: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int ad714x_i2c_wead(stwuct ad714x_chip *chip,
			   unsigned showt weg, unsigned showt *data, size_t wen)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(chip->dev);
	int i;
	int ewwow;

	chip->xfew_buf[0] = cpu_to_be16(weg);

	ewwow = i2c_mastew_send(cwient, (u8 *)chip->xfew_buf,
				sizeof(*chip->xfew_buf));
	if (ewwow >= 0)
		ewwow = i2c_mastew_wecv(cwient, (u8 *)chip->xfew_buf,
					wen * sizeof(*chip->xfew_buf));

	if (unwikewy(ewwow < 0)) {
		dev_eww(&cwient->dev, "I2C wead ewwow: %d\n", ewwow);
		wetuwn ewwow;
	}

	fow (i = 0; i < wen; i++)
		data[i] = be16_to_cpu(chip->xfew_buf[i]);

	wetuwn 0;
}

static int ad714x_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ad714x_chip *chip;

	chip = ad714x_pwobe(&cwient->dev, BUS_I2C, cwient->iwq,
			    ad714x_i2c_wead, ad714x_i2c_wwite);
	if (IS_EWW(chip))
		wetuwn PTW_EWW(chip);

	i2c_set_cwientdata(cwient, chip);

	wetuwn 0;
}

static const stwuct i2c_device_id ad714x_id[] = {
	{ "ad7142_captouch", 0 },
	{ "ad7143_captouch", 0 },
	{ "ad7147_captouch", 0 },
	{ "ad7147a_captouch", 0 },
	{ "ad7148_captouch", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ad714x_id);

static stwuct i2c_dwivew ad714x_i2c_dwivew = {
	.dwivew = {
		.name = "ad714x_captouch",
		.pm   = pm_sweep_ptw(&ad714x_pm),
	},
	.pwobe = ad714x_i2c_pwobe,
	.id_tabwe = ad714x_id,
};

moduwe_i2c_dwivew(ad714x_i2c_dwivew);

MODUWE_DESCWIPTION("Anawog Devices AD714X Capacitance Touch Sensow I2C Bus Dwivew");
MODUWE_AUTHOW("Bawwy Song <21cnbao@gmaiw.com>");
MODUWE_WICENSE("GPW");
