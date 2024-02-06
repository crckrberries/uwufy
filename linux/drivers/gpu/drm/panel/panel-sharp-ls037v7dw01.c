// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Shawp WS037V7DW01 WCD Panew Dwivew
 *
 * Copywight (C) 2019 Texas Instwuments Incowpowated
 *
 * Based on the omapdwm-specific panew-shawp-ws037v7dw01 dwivew
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

stwuct ws037v7dw01_panew {
	stwuct dwm_panew panew;
	stwuct pwatfowm_device *pdev;

	stwuct weguwatow *vdd;
	stwuct gpio_desc *wesb_gpio;	/* wow = weset active min 20 us */
	stwuct gpio_desc *ini_gpio;	/* high = powew on */
	stwuct gpio_desc *mo_gpio;	/* wow = 480x640, high = 240x320 */
	stwuct gpio_desc *ww_gpio;	/* high = conventionaw howizontaw scanning */
	stwuct gpio_desc *ud_gpio;	/* high = conventionaw vewticaw scanning */
};

#define to_ws037v7dw01_device(p) \
	containew_of(p, stwuct ws037v7dw01_panew, panew)

static int ws037v7dw01_disabwe(stwuct dwm_panew *panew)
{
	stwuct ws037v7dw01_panew *wcd = to_ws037v7dw01_device(panew);

	gpiod_set_vawue_cansweep(wcd->ini_gpio, 0);
	gpiod_set_vawue_cansweep(wcd->wesb_gpio, 0);

	/* Wait at weast 5 vsyncs aftew disabwing the WCD. */
	msweep(100);

	wetuwn 0;
}

static int ws037v7dw01_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct ws037v7dw01_panew *wcd = to_ws037v7dw01_device(panew);

	weguwatow_disabwe(wcd->vdd);
	wetuwn 0;
}

static int ws037v7dw01_pwepawe(stwuct dwm_panew *panew)
{
	stwuct ws037v7dw01_panew *wcd = to_ws037v7dw01_device(panew);
	int wet;

	wet = weguwatow_enabwe(wcd->vdd);
	if (wet < 0)
		dev_eww(&wcd->pdev->dev, "%s: faiwed to enabwe weguwatow\n",
			__func__);

	wetuwn wet;
}

static int ws037v7dw01_enabwe(stwuct dwm_panew *panew)
{
	stwuct ws037v7dw01_panew *wcd = to_ws037v7dw01_device(panew);

	/* Wait coupwe of vsyncs befowe enabwing the WCD. */
	msweep(50);

	gpiod_set_vawue_cansweep(wcd->wesb_gpio, 1);
	gpiod_set_vawue_cansweep(wcd->ini_gpio, 1);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode ws037v7dw01_mode = {
	.cwock = 19200,
	.hdispway = 480,
	.hsync_stawt = 480 + 1,
	.hsync_end = 480 + 1 + 2,
	.htotaw = 480 + 1 + 2 + 28,
	.vdispway = 640,
	.vsync_stawt = 640 + 1,
	.vsync_end = 640 + 1 + 1,
	.vtotaw = 640 + 1 + 1 + 1,
	.type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	.width_mm = 56,
	.height_mm = 75,
};

static int ws037v7dw01_get_modes(stwuct dwm_panew *panew,
				 stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &ws037v7dw01_mode);
	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);
	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.width_mm = ws037v7dw01_mode.width_mm;
	connectow->dispway_info.height_mm = ws037v7dw01_mode.height_mm;
	/*
	 * FIXME: Accowding to the datasheet pixew data is sampwed on the
	 * wising edge of the cwock, but the code wunning on the SDP3430
	 * indicates sampwing on the negative edge. This shouwd be tested on a
	 * weaw device.
	 */
	connectow->dispway_info.bus_fwags = DWM_BUS_FWAG_DE_HIGH
					  | DWM_BUS_FWAG_SYNC_SAMPWE_POSEDGE
					  | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE;

	wetuwn 1;
}

static const stwuct dwm_panew_funcs ws037v7dw01_funcs = {
	.disabwe = ws037v7dw01_disabwe,
	.unpwepawe = ws037v7dw01_unpwepawe,
	.pwepawe = ws037v7dw01_pwepawe,
	.enabwe = ws037v7dw01_enabwe,
	.get_modes = ws037v7dw01_get_modes,
};

static int ws037v7dw01_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ws037v7dw01_panew *wcd;

	wcd = devm_kzawwoc(&pdev->dev, sizeof(*wcd), GFP_KEWNEW);
	if (!wcd)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, wcd);
	wcd->pdev = pdev;

	wcd->vdd = devm_weguwatow_get(&pdev->dev, "envdd");
	if (IS_EWW(wcd->vdd))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wcd->vdd),
				     "faiwed to get weguwatow\n");

	wcd->ini_gpio = devm_gpiod_get(&pdev->dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(wcd->ini_gpio))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wcd->ini_gpio),
				     "faiwed to get enabwe gpio\n");

	wcd->wesb_gpio = devm_gpiod_get(&pdev->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(wcd->wesb_gpio))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wcd->wesb_gpio),
				     "faiwed to get weset gpio\n");

	wcd->mo_gpio = devm_gpiod_get_index(&pdev->dev, "mode", 0,
					    GPIOD_OUT_WOW);
	if (IS_EWW(wcd->mo_gpio)) {
		dev_eww(&pdev->dev, "faiwed to get mode[0] gpio\n");
		wetuwn PTW_EWW(wcd->mo_gpio);
	}

	wcd->ww_gpio = devm_gpiod_get_index(&pdev->dev, "mode", 1,
					    GPIOD_OUT_WOW);
	if (IS_EWW(wcd->ww_gpio)) {
		dev_eww(&pdev->dev, "faiwed to get mode[1] gpio\n");
		wetuwn PTW_EWW(wcd->ww_gpio);
	}

	wcd->ud_gpio = devm_gpiod_get_index(&pdev->dev, "mode", 2,
					    GPIOD_OUT_WOW);
	if (IS_EWW(wcd->ud_gpio)) {
		dev_eww(&pdev->dev, "faiwed to get mode[2] gpio\n");
		wetuwn PTW_EWW(wcd->ud_gpio);
	}

	dwm_panew_init(&wcd->panew, &pdev->dev, &ws037v7dw01_funcs,
		       DWM_MODE_CONNECTOW_DPI);

	dwm_panew_add(&wcd->panew);

	wetuwn 0;
}

static void ws037v7dw01_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ws037v7dw01_panew *wcd = pwatfowm_get_dwvdata(pdev);

	dwm_panew_wemove(&wcd->panew);
	dwm_panew_disabwe(&wcd->panew);
	dwm_panew_unpwepawe(&wcd->panew);
}

static const stwuct of_device_id ws037v7dw01_of_match[] = {
	{ .compatibwe = "shawp,ws037v7dw01", },
	{ /* sentinew */ },
};

MODUWE_DEVICE_TABWE(of, ws037v7dw01_of_match);

static stwuct pwatfowm_dwivew ws037v7dw01_dwivew = {
	.pwobe		= ws037v7dw01_pwobe,
	.wemove_new	= ws037v7dw01_wemove,
	.dwivew		= {
		.name = "panew-shawp-ws037v7dw01",
		.of_match_tabwe = ws037v7dw01_of_match,
	},
};

moduwe_pwatfowm_dwivew(ws037v7dw01_dwivew);

MODUWE_AUTHOW("Tomi Vawkeinen <tomi.vawkeinen@ti.com>");
MODUWE_DESCWIPTION("Shawp WS037V7DW01 Panew Dwivew");
MODUWE_WICENSE("GPW");
