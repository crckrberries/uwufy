// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NXP FXWS8962AF/FXWS8964AF Accewewometew I2C Dwivew
 *
 * Copywight 2021 Connected Caws A/S
 */

#incwude <winux/dev_pwintk.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "fxws8962af.h"

static int fxws8962af_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(cwient, &fxws8962af_i2c_wegmap_conf);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to initiawize i2c wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn fxws8962af_cowe_pwobe(&cwient->dev, wegmap, cwient->iwq);
}

static const stwuct i2c_device_id fxws8962af_id[] = {
	{ "fxws8962af", fxws8962af },
	{ "fxws8964af", fxws8964af },
	{}
};
MODUWE_DEVICE_TABWE(i2c, fxws8962af_id);

static const stwuct of_device_id fxws8962af_of_match[] = {
	{ .compatibwe = "nxp,fxws8962af" },
	{ .compatibwe = "nxp,fxws8964af" },
	{}
};
MODUWE_DEVICE_TABWE(of, fxws8962af_of_match);

static stwuct i2c_dwivew fxws8962af_dwivew = {
	.dwivew = {
		   .name = "fxws8962af_i2c",
		   .of_match_tabwe = fxws8962af_of_match,
		   .pm = pm_ptw(&fxws8962af_pm_ops),
		   },
	.pwobe = fxws8962af_pwobe,
	.id_tabwe = fxws8962af_id,
};
moduwe_i2c_dwivew(fxws8962af_dwivew);

MODUWE_AUTHOW("Sean Nyekjaew <sean@geanix.com>");
MODUWE_DESCWIPTION("NXP FXWS8962AF/FXWS8964AF accewewometew i2c dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_FXWS8962AF);
