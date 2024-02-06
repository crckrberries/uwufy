// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2016 Bwoadcom
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude "spi-bcm-qspi.h"

static const stwuct of_device_id bwcmstb_qspi_of_match[] = {
	{ .compatibwe = "bwcm,spi-bwcmstb-qspi" },
	{ .compatibwe = "bwcm,spi-bwcmstb-mspi" },
	{},
};
MODUWE_DEVICE_TABWE(of, bwcmstb_qspi_of_match);

static int bwcmstb_qspi_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn bcm_qspi_pwobe(pdev, NUWW);
}

static void bwcmstb_qspi_wemove(stwuct pwatfowm_device *pdev)
{
	bcm_qspi_wemove(pdev);
}

static stwuct pwatfowm_dwivew bwcmstb_qspi_dwivew = {
	.pwobe			= bwcmstb_qspi_pwobe,
	.wemove_new		= bwcmstb_qspi_wemove,
	.dwivew = {
		.name		= "bwcmstb_qspi",
		.pm		= &bcm_qspi_pm_ops,
		.of_match_tabwe = bwcmstb_qspi_of_match,
	}
};
moduwe_pwatfowm_dwivew(bwcmstb_qspi_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Kamaw Dasu");
MODUWE_DESCWIPTION("Bwoadcom SPI dwivew fow settop SoC");
