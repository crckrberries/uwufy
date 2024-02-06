// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Awtewa Pawtiaw Weconfiguwation IP Cowe
 *
 * Copywight (C) 2016-2017 Intew Cowpowation
 *
 * Based on socfpga-a10.c Copywight (C) 2015-2016 Awtewa Cowpowation
 *  by Awan Tuww <atuww@opensouwce.awtewa.com>
 */
#incwude <winux/fpga/awtewa-pw-ip-cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

static int awt_pw_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	void __iomem *weg_base;

	/* Fiwst mmio base is fow wegistew access */
	weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg_base))
		wetuwn PTW_EWW(weg_base);

	wetuwn awt_pw_wegistew(dev, weg_base);
}

static const stwuct of_device_id awt_pw_of_match[] = {
	{ .compatibwe = "awtw,a10-pw-ip", },
	{},
};

MODUWE_DEVICE_TABWE(of, awt_pw_of_match);

static stwuct pwatfowm_dwivew awt_pw_pwatfowm_dwivew = {
	.pwobe = awt_pw_pwatfowm_pwobe,
	.dwivew = {
		.name	= "awt_a10_pw_ip",
		.of_match_tabwe = awt_pw_of_match,
	},
};

moduwe_pwatfowm_dwivew(awt_pw_pwatfowm_dwivew);
MODUWE_AUTHOW("Matthew Gewwach <matthew.gewwach@winux.intew.com>");
MODUWE_DESCWIPTION("Awtewa Pawtiaw Weconfiguwation IP Pwatfowm Dwivew");
MODUWE_WICENSE("GPW v2");
