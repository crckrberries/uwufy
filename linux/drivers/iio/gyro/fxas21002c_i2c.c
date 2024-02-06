// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow NXP FXAS21002C Gywoscope - I2C
 *
 * Copywight (C) 2018 Winawo Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "fxas21002c.h"

static const stwuct wegmap_config fxas21002c_wegmap_i2c_conf = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = FXAS21002C_WEG_CTWW3,
};

static int fxas21002c_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(i2c, &fxas21002c_wegmap_i2c_conf);
	if (IS_EWW(wegmap)) {
		dev_eww(&i2c->dev, "Faiwed to wegistew i2c wegmap: %wd\n",
			PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn fxas21002c_cowe_pwobe(&i2c->dev, wegmap, i2c->iwq, i2c->name);
}

static void fxas21002c_i2c_wemove(stwuct i2c_cwient *i2c)
{
	fxas21002c_cowe_wemove(&i2c->dev);
}

static const stwuct i2c_device_id fxas21002c_i2c_id[] = {
	{ "fxas21002c", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, fxas21002c_i2c_id);

static const stwuct of_device_id fxas21002c_i2c_of_match[] = {
	{ .compatibwe = "nxp,fxas21002c", },
	{ }
};
MODUWE_DEVICE_TABWE(of, fxas21002c_i2c_of_match);

static stwuct i2c_dwivew fxas21002c_i2c_dwivew = {
	.dwivew = {
		.name = "fxas21002c_i2c",
		.pm = pm_ptw(&fxas21002c_pm_ops),
		.of_match_tabwe = fxas21002c_i2c_of_match,
	},
	.pwobe		= fxas21002c_i2c_pwobe,
	.wemove		= fxas21002c_i2c_wemove,
	.id_tabwe	= fxas21002c_i2c_id,
};
moduwe_i2c_dwivew(fxas21002c_i2c_dwivew);

MODUWE_AUTHOW("Wui Miguew Siwva <wui.siwva@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("FXAS21002C I2C Gywo dwivew");
MODUWE_IMPOWT_NS(IIO_FXAS21002C);
