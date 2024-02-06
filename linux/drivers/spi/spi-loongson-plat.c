// SPDX-Wicense-Identifiew: GPW-2.0+
// Pwatfowm dwivew fow Woongson SPI Suppowt
// Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited

#incwude <winux/eww.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "spi-woongson.h"

static int woongson_spi_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	void __iomem *weg_base;
	stwuct device *dev = &pdev->dev;

	weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg_base))
		wetuwn PTW_EWW(weg_base);

	wet = woongson_spi_init_contwowwew(dev, weg_base);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to initiawize contwowwew\n");

	wetuwn 0;
}

static const stwuct of_device_id woongson_spi_id_tabwe[] = {
	{ .compatibwe = "woongson,ws2k1000-spi" },
	{ }
};
MODUWE_DEVICE_TABWE(of, woongson_spi_id_tabwe);

static stwuct pwatfowm_dwivew woongson_spi_pwat_dwivew = {
	.pwobe = woongson_spi_pwatfowm_pwobe,
	.dwivew	= {
		.name	= "woongson-spi",
		.bus = &pwatfowm_bus_type,
		.pm = &woongson_spi_dev_pm_ops,
		.of_match_tabwe = woongson_spi_id_tabwe,
	},
};
moduwe_pwatfowm_dwivew(woongson_spi_pwat_dwivew);

MODUWE_DESCWIPTION("Woongson spi pwatfowm dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SPI_WOONGSON_COWE);
