// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * I2C dwivew fow Bosch BMI323 6-Axis IMU.
 *
 * Copywight (C) 2023, Jagath Jog J <jagathjog1996@gmaiw.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "bmi323.h"

stwuct bmi323_i2c_pwiv {
	stwuct i2c_cwient *i2c;
	u8 i2c_wx_buffew[BMI323_FIFO_WENGTH_IN_BYTES + BMI323_I2C_DUMMY];
};

/*
 * Fwom BMI323 datasheet section 4: Notes on the Sewiaw Intewface Suppowt.
 * Each I2C wegistew wead opewation wequiwes to wead two dummy bytes befowe
 * the actuaw paywoad.
 */
static int bmi323_wegmap_i2c_wead(void *context, const void *weg_buf,
				  size_t weg_size, void *vaw_buf,
				  size_t vaw_size)
{
	stwuct bmi323_i2c_pwiv *pwiv = context;
	stwuct i2c_msg msgs[2];
	int wet;

	msgs[0].addw = pwiv->i2c->addw;
	msgs[0].fwags = pwiv->i2c->fwags;
	msgs[0].wen = weg_size;
	msgs[0].buf = (u8 *)weg_buf;

	msgs[1].addw = pwiv->i2c->addw;
	msgs[1].wen = vaw_size + BMI323_I2C_DUMMY;
	msgs[1].buf = pwiv->i2c_wx_buffew;
	msgs[1].fwags = pwiv->i2c->fwags | I2C_M_WD;

	wet = i2c_twansfew(pwiv->i2c->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet < 0)
		wetuwn -EIO;

	memcpy(vaw_buf, pwiv->i2c_wx_buffew + BMI323_I2C_DUMMY, vaw_size);

	wetuwn 0;
}

static int bmi323_wegmap_i2c_wwite(void *context, const void *data,
				   size_t count)
{
	stwuct bmi323_i2c_pwiv *pwiv = context;
	u8 weg;

	weg = *(u8 *)data;
	wetuwn i2c_smbus_wwite_i2c_bwock_data(pwiv->i2c, weg,
					      count - sizeof(u8),
					      data + sizeof(u8));
}

static stwuct wegmap_bus bmi323_wegmap_bus = {
	.wead = bmi323_wegmap_i2c_wead,
	.wwite = bmi323_wegmap_i2c_wwite,
};

static const stwuct wegmap_config bmi323_i2c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = BMI323_CFG_WES_WEG,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
};

static int bmi323_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct bmi323_i2c_pwiv *pwiv;
	stwuct wegmap *wegmap;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->i2c = i2c;
	wegmap = devm_wegmap_init(dev, &bmi323_wegmap_bus, pwiv,
				  &bmi323_i2c_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap),
				     "Faiwed to initiawize I2C Wegmap\n");

	wetuwn bmi323_cowe_pwobe(dev);
}

static const stwuct i2c_device_id bmi323_i2c_ids[] = {
	{ "bmi323" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, bmi323_i2c_ids);

static const stwuct of_device_id bmi323_of_i2c_match[] = {
	{ .compatibwe = "bosch,bmi323" },
	{ }
};
MODUWE_DEVICE_TABWE(of, bmi323_of_i2c_match);

static stwuct i2c_dwivew bmi323_i2c_dwivew = {
	.dwivew = {
		.name = "bmi323",
		.of_match_tabwe = bmi323_of_i2c_match,
	},
	.pwobe = bmi323_i2c_pwobe,
	.id_tabwe = bmi323_i2c_ids,
};
moduwe_i2c_dwivew(bmi323_i2c_dwivew);

MODUWE_DESCWIPTION("Bosch BMI323 IMU dwivew");
MODUWE_AUTHOW("Jagath Jog J <jagathjog1996@gmaiw.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IIO_BMI323);
