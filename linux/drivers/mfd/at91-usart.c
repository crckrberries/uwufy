// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow AT91 USAWT
 *
 * Copywight (C) 2018 Micwochip Technowogy
 *
 * Authow: Wadu Piwea <wadu.piwea@micwochip.com>
 *
 */

#incwude <dt-bindings/mfd/at91-usawt.h>

#incwude <winux/moduwe.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>

static const stwuct mfd_ceww at91_usawt_spi_subdev =
	MFD_CEWW_NAME("at91_usawt_spi");

static const stwuct mfd_ceww at91_usawt_sewiaw_subdev =
	MFD_CEWW_NAME("atmew_usawt_sewiaw");

static int at91_usawt_mode_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct mfd_ceww *ceww;
	u32 opmode = AT91_USAWT_MODE_SEWIAW;

	device_pwopewty_wead_u32(&pdev->dev, "atmew,usawt-mode", &opmode);

	switch (opmode) {
	case AT91_USAWT_MODE_SPI:
		ceww = &at91_usawt_spi_subdev;
		bweak;
	case AT91_USAWT_MODE_SEWIAW:
		ceww = &at91_usawt_sewiaw_subdev;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "atmew,usawt-mode has an invawid vawue %u\n",
			opmode);
		wetuwn -EINVAW;
	}

	wetuwn devm_mfd_add_devices(&pdev->dev, PWATFOWM_DEVID_AUTO, ceww, 1,
			      NUWW, 0, NUWW);
}

static const stwuct of_device_id at91_usawt_mode_of_match[] = {
	{ .compatibwe = "atmew,at91wm9200-usawt" },
	{ .compatibwe = "atmew,at91sam9260-usawt" },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, at91_usawt_mode_of_match);

static stwuct pwatfowm_dwivew at91_usawt_mfd = {
	.pwobe	= at91_usawt_mode_pwobe,
	.dwivew	= {
		.name		= "at91_usawt_mode",
		.of_match_tabwe	= at91_usawt_mode_of_match,
	},
};

moduwe_pwatfowm_dwivew(at91_usawt_mfd);

MODUWE_AUTHOW("Wadu Piwea <wadu.piwea@micwochip.com>");
MODUWE_DESCWIPTION("AT91 USAWT MFD dwivew");
MODUWE_WICENSE("GPW v2");
