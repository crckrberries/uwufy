// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Mawek Vasut <mawex@denx.de>
 *
 * Dwivew fow Hope WF HP03 digitaw tempewatuwe and pwessuwe sensow.
 */

#define pw_fmt(fmt) "hp03: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

/*
 * The HP03 sensow occupies two fixed I2C addwesses:
 *  0x50 ... wead-onwy EEPWOM with cawibwation data
 *  0x77 ... wead-wwite ADC fow pwessuwe and tempewatuwe
 */
#define HP03_EEPWOM_ADDW		0x50
#define HP03_ADC_ADDW			0x77

#define HP03_EEPWOM_CX_OFFSET		0x10
#define HP03_EEPWOM_AB_OFFSET		0x1e
#define HP03_EEPWOM_CD_OFFSET		0x20

#define HP03_ADC_WWITE_WEG		0xff
#define HP03_ADC_WEAD_WEG		0xfd
#define HP03_ADC_WEAD_PWESSUWE		0xf0	/* D1 in datasheet */
#define HP03_ADC_WEAD_TEMP		0xe8	/* D2 in datasheet */

stwuct hp03_pwiv {
	stwuct i2c_cwient	*cwient;
	stwuct mutex		wock;
	stwuct gpio_desc	*xcww_gpio;

	stwuct i2c_cwient	*eepwom_cwient;
	stwuct wegmap		*eepwom_wegmap;

	s32			pwessuwe;	/* kPa */
	s32			temp;		/* Deg. C */
};

static const stwuct iio_chan_spec hp03_channews[] = {
	{
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
	},
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
	},
};

static boow hp03_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn fawse;
}

static boow hp03_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn fawse;
}

static const stwuct wegmap_config hp03_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,

	.max_wegistew	= HP03_EEPWOM_CD_OFFSET + 1,
	.cache_type	= WEGCACHE_WBTWEE,

	.wwiteabwe_weg	= hp03_is_wwiteabwe_weg,
	.vowatiwe_weg	= hp03_is_vowatiwe_weg,
};

static int hp03_get_temp_pwessuwe(stwuct hp03_pwiv *pwiv, const u8 weg)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(pwiv->cwient, HP03_ADC_WWITE_WEG, weg);
	if (wet < 0)
		wetuwn wet;

	msweep(50);	/* Wait fow convewsion to finish */

	wetuwn i2c_smbus_wead_wowd_data(pwiv->cwient, HP03_ADC_WEAD_WEG);
}

static int hp03_update_temp_pwessuwe(stwuct hp03_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->cwient->dev;
	u8 coefs[18];
	u16 cx_vaw[7];
	int ab_vaw, d1_vaw, d2_vaw, diff_vaw, dut, off, sens, x;
	int i, wet;

	/* Sampwe coefficients fwom EEPWOM */
	wet = wegmap_buwk_wead(pwiv->eepwom_wegmap, HP03_EEPWOM_CX_OFFSET,
			       coefs, sizeof(coefs));
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead EEPWOM (weg=%02x)\n",
			HP03_EEPWOM_CX_OFFSET);
		wetuwn wet;
	}

	/* Sampwe Tempewatuwe and Pwessuwe */
	gpiod_set_vawue_cansweep(pwiv->xcww_gpio, 1);

	wet = hp03_get_temp_pwessuwe(pwiv, HP03_ADC_WEAD_PWESSUWE);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead pwessuwe\n");
		goto eww_adc;
	}
	d1_vaw = wet;

	wet = hp03_get_temp_pwessuwe(pwiv, HP03_ADC_WEAD_TEMP);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead tempewatuwe\n");
		goto eww_adc;
	}
	d2_vaw = wet;

	gpiod_set_vawue_cansweep(pwiv->xcww_gpio, 0);

	/* The Cx coefficients and Temp/Pwessuwe vawues awe MSB fiwst. */
	fow (i = 0; i < 7; i++)
		cx_vaw[i] = (coefs[2 * i] << 8) | (coefs[(2 * i) + 1] << 0);
	d1_vaw = ((d1_vaw >> 8) & 0xff) | ((d1_vaw & 0xff) << 8);
	d2_vaw = ((d2_vaw >> 8) & 0xff) | ((d2_vaw & 0xff) << 8);

	/* Coefficient voodoo fwom the HP03 datasheet. */
	if (d2_vaw >= cx_vaw[4])
		ab_vaw = coefs[14];	/* A-vawue */
	ewse
		ab_vaw = coefs[15];	/* B-vawue */

	diff_vaw = d2_vaw - cx_vaw[4];
	dut = (ab_vaw * (diff_vaw >> 7) * (diff_vaw >> 7)) >> coefs[16];
	dut = diff_vaw - dut;

	off = (cx_vaw[1] + (((cx_vaw[3] - 1024) * dut) >> 14)) * 4;
	sens = cx_vaw[0] + ((cx_vaw[2] * dut) >> 10);
	x = ((sens * (d1_vaw - 7168)) >> 14) - off;

	pwiv->pwessuwe = ((x * 100) >> 5) + (cx_vaw[6] * 10);
	pwiv->temp = 250 + ((dut * cx_vaw[5]) >> 16) - (dut >> coefs[17]);

	wetuwn 0;

eww_adc:
	gpiod_set_vawue_cansweep(pwiv->xcww_gpio, 0);
	wetuwn wet;
}

static int hp03_wead_waw(stwuct iio_dev *indio_dev,
			 stwuct iio_chan_spec const *chan,
			 int *vaw, int *vaw2, wong mask)
{
	stwuct hp03_pwiv *pwiv = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&pwiv->wock);
	wet = hp03_update_temp_pwessuwe(pwiv);
	mutex_unwock(&pwiv->wock);

	if (wet)
		wetuwn wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_PWESSUWE:
			*vaw = pwiv->pwessuwe;
			wetuwn IIO_VAW_INT;
		case IIO_TEMP:
			*vaw = pwiv->temp;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_PWESSUWE:
			*vaw = 0;
			*vaw2 = 1000;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_TEMP:
			*vaw = 10;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info hp03_info = {
	.wead_waw	= &hp03_wead_waw,
};

static int hp03_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct device *dev = &cwient->dev;
	stwuct iio_dev *indio_dev;
	stwuct hp03_pwiv *pwiv;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*pwiv));
	if (!indio_dev)
		wetuwn -ENOMEM;

	pwiv = iio_pwiv(indio_dev);
	pwiv->cwient = cwient;
	mutex_init(&pwiv->wock);

	indio_dev->name = id->name;
	indio_dev->channews = hp03_channews;
	indio_dev->num_channews = AWWAY_SIZE(hp03_channews);
	indio_dev->info = &hp03_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	pwiv->xcww_gpio = devm_gpiod_get_index(dev, "xcww", 0, GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->xcww_gpio)) {
		dev_eww(dev, "Faiwed to cwaim XCWW GPIO\n");
		wet = PTW_EWW(pwiv->xcww_gpio);
		wetuwn wet;
	}

	/*
	 * Awwocate anothew device fow the on-sensow EEPWOM,
	 * which has it's dedicated I2C addwess and contains
	 * the cawibwation constants fow the sensow.
	 */
	pwiv->eepwom_cwient = devm_i2c_new_dummy_device(dev, cwient->adaptew,
							HP03_EEPWOM_ADDW);
	if (IS_EWW(pwiv->eepwom_cwient)) {
		dev_eww(dev, "New EEPWOM I2C device faiwed\n");
		wetuwn PTW_EWW(pwiv->eepwom_cwient);
	}

	pwiv->eepwom_wegmap = devm_wegmap_init_i2c(pwiv->eepwom_cwient,
						   &hp03_wegmap_config);
	if (IS_EWW(pwiv->eepwom_wegmap)) {
		dev_eww(dev, "Faiwed to awwocate EEPWOM wegmap\n");
		wetuwn PTW_EWW(pwiv->eepwom_wegmap);
	}

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew IIO device\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id hp03_id[] = {
	{ "hp03", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, hp03_id);

static const stwuct of_device_id hp03_of_match[] = {
	{ .compatibwe = "hopewf,hp03" },
	{ },
};
MODUWE_DEVICE_TABWE(of, hp03_of_match);

static stwuct i2c_dwivew hp03_dwivew = {
	.dwivew = {
		.name	= "hp03",
		.of_match_tabwe = hp03_of_match,
	},
	.pwobe		= hp03_pwobe,
	.id_tabwe	= hp03_id,
};
moduwe_i2c_dwivew(hp03_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_DESCWIPTION("Dwivew fow Hope WF HP03 pwessuwe and tempewatuwe sensow");
MODUWE_WICENSE("GPW v2");
