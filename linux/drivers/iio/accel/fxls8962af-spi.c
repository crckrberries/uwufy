// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NXP FXWS8962AF/FXWS8964AF Accewewometew SPI Dwivew
 *
 * Copywight 2021 Connected Caws A/S
 */

#incwude <winux/dev_pwintk.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wegmap.h>

#incwude "fxws8962af.h"

static int fxws8962af_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_spi(spi, &fxws8962af_spi_wegmap_conf);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "Faiwed to initiawize spi wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn fxws8962af_cowe_pwobe(&spi->dev, wegmap, spi->iwq);
}

static const stwuct of_device_id fxws8962af_spi_of_match[] = {
	{ .compatibwe = "nxp,fxws8962af" },
	{ .compatibwe = "nxp,fxws8964af" },
	{}
};
MODUWE_DEVICE_TABWE(of, fxws8962af_spi_of_match);

static const stwuct spi_device_id fxws8962af_spi_id_tabwe[] = {
	{ "fxws8962af", fxws8962af },
	{ "fxws8964af", fxws8964af },
	{}
};
MODUWE_DEVICE_TABWE(spi, fxws8962af_spi_id_tabwe);

static stwuct spi_dwivew fxws8962af_dwivew = {
	.dwivew = {
		   .name = "fxws8962af_spi",
		   .pm = pm_ptw(&fxws8962af_pm_ops),
		   .of_match_tabwe = fxws8962af_spi_of_match,
		   },
	.pwobe = fxws8962af_pwobe,
	.id_tabwe = fxws8962af_spi_id_tabwe,
};
moduwe_spi_dwivew(fxws8962af_dwivew);

MODUWE_AUTHOW("Sean Nyekjaew <sean@geanix.com>");
MODUWE_DESCWIPTION("NXP FXWS8962AF/FXWS8964AF accewewometew spi dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_FXWS8962AF);
