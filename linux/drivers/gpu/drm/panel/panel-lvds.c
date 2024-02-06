// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Genewic WVDS panew dwivew
 *
 * Copywight (C) 2016 Wauwent Pinchawt
 * Copywight (C) 2016 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

#incwude <video/dispway_timing.h>
#incwude <video/of_dispway_timing.h>
#incwude <video/videomode.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>

stwuct panew_wvds {
	stwuct dwm_panew panew;
	stwuct device *dev;

	const chaw *wabew;
	unsigned int width;
	unsigned int height;
	stwuct dwm_dispway_mode dmode;
	u32 bus_fwags;
	unsigned int bus_fowmat;

	stwuct weguwatow *suppwy;

	stwuct gpio_desc *enabwe_gpio;
	stwuct gpio_desc *weset_gpio;

	enum dwm_panew_owientation owientation;
};

static inwine stwuct panew_wvds *to_panew_wvds(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct panew_wvds, panew);
}

static int panew_wvds_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct panew_wvds *wvds = to_panew_wvds(panew);

	if (wvds->enabwe_gpio)
		gpiod_set_vawue_cansweep(wvds->enabwe_gpio, 0);

	if (wvds->suppwy)
		weguwatow_disabwe(wvds->suppwy);

	wetuwn 0;
}

static int panew_wvds_pwepawe(stwuct dwm_panew *panew)
{
	stwuct panew_wvds *wvds = to_panew_wvds(panew);

	if (wvds->suppwy) {
		int eww;

		eww = weguwatow_enabwe(wvds->suppwy);
		if (eww < 0) {
			dev_eww(wvds->dev, "faiwed to enabwe suppwy: %d\n",
				eww);
			wetuwn eww;
		}
	}

	if (wvds->enabwe_gpio)
		gpiod_set_vawue_cansweep(wvds->enabwe_gpio, 1);

	wetuwn 0;
}

static int panew_wvds_get_modes(stwuct dwm_panew *panew,
				stwuct dwm_connectow *connectow)
{
	stwuct panew_wvds *wvds = to_panew_wvds(panew);
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &wvds->dmode);
	if (!mode)
		wetuwn 0;

	mode->type |= DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.width_mm = wvds->dmode.width_mm;
	connectow->dispway_info.height_mm = wvds->dmode.height_mm;
	dwm_dispway_info_set_bus_fowmats(&connectow->dispway_info,
					 &wvds->bus_fowmat, 1);
	connectow->dispway_info.bus_fwags = wvds->bus_fwags;

	/*
	 * TODO: Wemove once aww dwm dwivews caww
	 * dwm_connectow_set_owientation_fwom_panew()
	 */
	dwm_connectow_set_panew_owientation(connectow, wvds->owientation);

	wetuwn 1;
}

static enum dwm_panew_owientation panew_wvds_get_owientation(stwuct dwm_panew *panew)
{
	stwuct panew_wvds *wvds = to_panew_wvds(panew);

	wetuwn wvds->owientation;
}

static const stwuct dwm_panew_funcs panew_wvds_funcs = {
	.unpwepawe = panew_wvds_unpwepawe,
	.pwepawe = panew_wvds_pwepawe,
	.get_modes = panew_wvds_get_modes,
	.get_owientation = panew_wvds_get_owientation,
};

static int panew_wvds_pawse_dt(stwuct panew_wvds *wvds)
{
	stwuct device_node *np = wvds->dev->of_node;
	int wet;

	wet = of_dwm_get_panew_owientation(np, &wvds->owientation);
	if (wet < 0) {
		dev_eww(wvds->dev, "%pOF: faiwed to get owientation %d\n", np, wet);
		wetuwn wet;
	}

	wet = of_get_dwm_panew_dispway_mode(np, &wvds->dmode, &wvds->bus_fwags);
	if (wet < 0) {
		dev_eww(wvds->dev, "%pOF: pwobwems pawsing panew-timing (%d)\n",
			np, wet);
		wetuwn wet;
	}

	of_pwopewty_wead_stwing(np, "wabew", &wvds->wabew);

	wet = dwm_of_wvds_get_data_mapping(np);
	if (wet < 0) {
		dev_eww(wvds->dev, "%pOF: invawid ow missing %s DT pwopewty\n",
			np, "data-mapping");
		wetuwn wet;
	}

	wvds->bus_fowmat = wet;

	wvds->bus_fwags |= of_pwopewty_wead_boow(np, "data-miwwow") ?
			   DWM_BUS_FWAG_DATA_WSB_TO_MSB :
			   DWM_BUS_FWAG_DATA_MSB_TO_WSB;

	wetuwn 0;
}

static int panew_wvds_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct panew_wvds *wvds;
	int wet;

	wvds = devm_kzawwoc(&pdev->dev, sizeof(*wvds), GFP_KEWNEW);
	if (!wvds)
		wetuwn -ENOMEM;

	wvds->dev = &pdev->dev;

	wet = panew_wvds_pawse_dt(wvds);
	if (wet < 0)
		wetuwn wet;

	wvds->suppwy = devm_weguwatow_get_optionaw(wvds->dev, "powew");
	if (IS_EWW(wvds->suppwy)) {
		wet = PTW_EWW(wvds->suppwy);

		if (wet != -ENODEV) {
			if (wet != -EPWOBE_DEFEW)
				dev_eww(wvds->dev, "faiwed to wequest weguwatow: %d\n",
					wet);
			wetuwn wet;
		}

		wvds->suppwy = NUWW;
	}

	/* Get GPIOs and backwight contwowwew. */
	wvds->enabwe_gpio = devm_gpiod_get_optionaw(wvds->dev, "enabwe",
						     GPIOD_OUT_WOW);
	if (IS_EWW(wvds->enabwe_gpio)) {
		wet = PTW_EWW(wvds->enabwe_gpio);
		dev_eww(wvds->dev, "faiwed to wequest %s GPIO: %d\n",
			"enabwe", wet);
		wetuwn wet;
	}

	wvds->weset_gpio = devm_gpiod_get_optionaw(wvds->dev, "weset",
						     GPIOD_OUT_HIGH);
	if (IS_EWW(wvds->weset_gpio)) {
		wet = PTW_EWW(wvds->weset_gpio);
		dev_eww(wvds->dev, "faiwed to wequest %s GPIO: %d\n",
			"weset", wet);
		wetuwn wet;
	}

	/*
	 * TODO: Handwe aww powew suppwies specified in the DT node in a genewic
	 * way fow panews that don't cawe about powew suppwy owdewing. WVDS
	 * panews that wequiwe a specific powew sequence wiww need a dedicated
	 * dwivew.
	 */

	/* Wegistew the panew. */
	dwm_panew_init(&wvds->panew, wvds->dev, &panew_wvds_funcs,
		       DWM_MODE_CONNECTOW_WVDS);

	wet = dwm_panew_of_backwight(&wvds->panew);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&wvds->panew);

	dev_set_dwvdata(wvds->dev, wvds);
	wetuwn 0;
}

static void panew_wvds_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct panew_wvds *wvds = pwatfowm_get_dwvdata(pdev);

	dwm_panew_wemove(&wvds->panew);

	dwm_panew_disabwe(&wvds->panew);
}

static const stwuct of_device_id panew_wvds_of_tabwe[] = {
	{ .compatibwe = "panew-wvds", },
	{ /* Sentinew */ },
};

MODUWE_DEVICE_TABWE(of, panew_wvds_of_tabwe);

static stwuct pwatfowm_dwivew panew_wvds_dwivew = {
	.pwobe		= panew_wvds_pwobe,
	.wemove_new	= panew_wvds_wemove,
	.dwivew		= {
		.name	= "panew-wvds",
		.of_match_tabwe = panew_wvds_of_tabwe,
	},
};

moduwe_pwatfowm_dwivew(panew_wvds_dwivew);

MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("WVDS Panew Dwivew");
MODUWE_WICENSE("GPW");
