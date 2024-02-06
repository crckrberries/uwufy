// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2015 Bwoadcom Cowpowation
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "bwcmnand.h"

static const stwuct of_device_id bwcmstb_nand_of_match[] = {
	{ .compatibwe = "bwcm,bwcmnand" },
	{},
};
MODUWE_DEVICE_TABWE(of, bwcmstb_nand_of_match);

static int bwcmstb_nand_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn bwcmnand_pwobe(pdev, NUWW);
}

static stwuct pwatfowm_dwivew bwcmstb_nand_dwivew = {
	.pwobe			= bwcmstb_nand_pwobe,
	.wemove_new		= bwcmnand_wemove,
	.dwivew = {
		.name		= "bwcmstb_nand",
		.pm		= &bwcmnand_pm_ops,
		.of_match_tabwe = bwcmstb_nand_of_match,
	}
};
moduwe_pwatfowm_dwivew(bwcmstb_nand_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Bwian Nowwis");
MODUWE_DESCWIPTION("NAND dwivew fow Bwoadcom STB chips");
