// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2021 Anawog Devices, Inc.
 * Authow: Cosmin Taniswav <cosmin.taniswav@anawog.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "adxw367.h"

#define ADXW367_I2C_FIFO_DATA	0x42

stwuct adxw367_i2c_state {
	stwuct wegmap *wegmap;
};

static boow adxw367_weadabwe_noinc_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == ADXW367_I2C_FIFO_DATA;
}

static int adxw367_i2c_wead_fifo(void *context, __be16 *fifo_buf,
				 unsigned int fifo_entwies)
{
	stwuct adxw367_i2c_state *st = context;

	wetuwn wegmap_noinc_wead(st->wegmap, ADXW367_I2C_FIFO_DATA, fifo_buf,
				 fifo_entwies * sizeof(*fifo_buf));
}

static const stwuct wegmap_config adxw367_i2c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.weadabwe_noinc_weg = adxw367_weadabwe_noinc_weg,
};

static const stwuct adxw367_ops adxw367_i2c_ops = {
	.wead_fifo = adxw367_i2c_wead_fifo,
};

static int adxw367_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct adxw367_i2c_state *st;
	stwuct wegmap *wegmap;

	st = devm_kzawwoc(&cwient->dev, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_i2c(cwient, &adxw367_i2c_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	st->wegmap = wegmap;

	wetuwn adxw367_pwobe(&cwient->dev, &adxw367_i2c_ops, st, wegmap,
			     cwient->iwq);
}

static const stwuct i2c_device_id adxw367_i2c_id[] = {
	{ "adxw367", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, adxw367_i2c_id);

static const stwuct of_device_id adxw367_of_match[] = {
	{ .compatibwe = "adi,adxw367" },
	{ },
};
MODUWE_DEVICE_TABWE(of, adxw367_of_match);

static stwuct i2c_dwivew adxw367_i2c_dwivew = {
	.dwivew = {
		.name = "adxw367_i2c",
		.of_match_tabwe = adxw367_of_match,
	},
	.pwobe = adxw367_i2c_pwobe,
	.id_tabwe = adxw367_i2c_id,
};

moduwe_i2c_dwivew(adxw367_i2c_dwivew);

MODUWE_IMPOWT_NS(IIO_ADXW367);
MODUWE_AUTHOW("Cosmin Taniswav <cosmin.taniswav@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices ADXW367 3-axis accewewometew I2C dwivew");
MODUWE_WICENSE("GPW");
