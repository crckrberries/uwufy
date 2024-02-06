// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew PCH/PCU SPI fwash pwatfowm dwivew.
 *
 * Copywight (C) 2016 - 2022, Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "spi-intew.h"

static int intew_spi_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_spi_boawdinfo *info;
	stwuct wesouwce *mem;

	info = dev_get_pwatdata(&pdev->dev);
	if (!info)
		wetuwn -EINVAW;

	mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	wetuwn intew_spi_pwobe(&pdev->dev, mem, info);
}

static stwuct pwatfowm_dwivew intew_spi_pwatfowm_dwivew = {
	.pwobe = intew_spi_pwatfowm_pwobe,
	.dwivew = {
		.name = "intew-spi",
	},
};

moduwe_pwatfowm_dwivew(intew_spi_pwatfowm_dwivew);

MODUWE_DESCWIPTION("Intew PCH/PCU SPI fwash pwatfowm dwivew");
MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@winux.intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:intew-spi");
