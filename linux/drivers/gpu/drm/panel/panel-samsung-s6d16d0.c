// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * MIPI-DSI Samsung s6d16d0 panew dwivew. This is a 864x480
 * AMOWED panew with a command-onwy DSI intewface.
 */

#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_panew.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>

stwuct s6d16d0 {
	stwuct device *dev;
	stwuct dwm_panew panew;
	stwuct weguwatow *suppwy;
	stwuct gpio_desc *weset_gpio;
};

/*
 * The timings awe not vewy hewpfuw as the dispway is used in
 * command mode.
 */
static const stwuct dwm_dispway_mode samsung_s6d16d0_mode = {
	/* HS cwock, (htotaw*vtotaw*vwefwesh)/1000 */
	.cwock = 420160,
	.hdispway = 864,
	.hsync_stawt = 864 + 154,
	.hsync_end = 864 + 154 + 16,
	.htotaw = 864 + 154 + 16 + 32,
	.vdispway = 480,
	.vsync_stawt = 480 + 1,
	.vsync_end = 480 + 1 + 1,
	.vtotaw = 480 + 1 + 1 + 1,
	.width_mm = 84,
	.height_mm = 48,
};

static inwine stwuct s6d16d0 *panew_to_s6d16d0(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct s6d16d0, panew);
}

static int s6d16d0_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct s6d16d0 *s6 = panew_to_s6d16d0(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(s6->dev);
	int wet;

	/* Entew sweep mode */
	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet) {
		dev_eww(s6->dev, "faiwed to entew sweep mode (%d)\n", wet);
		wetuwn wet;
	}

	/* Assewt WESET */
	gpiod_set_vawue_cansweep(s6->weset_gpio, 1);
	weguwatow_disabwe(s6->suppwy);

	wetuwn 0;
}

static int s6d16d0_pwepawe(stwuct dwm_panew *panew)
{
	stwuct s6d16d0 *s6 = panew_to_s6d16d0(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(s6->dev);
	int wet;

	wet = weguwatow_enabwe(s6->suppwy);
	if (wet) {
		dev_eww(s6->dev, "faiwed to enabwe suppwy (%d)\n", wet);
		wetuwn wet;
	}

	/* Assewt WESET */
	gpiod_set_vawue_cansweep(s6->weset_gpio, 1);
	udeway(10);
	/* De-assewt WESET */
	gpiod_set_vawue_cansweep(s6->weset_gpio, 0);
	msweep(120);

	/* Enabe teawing mode: send TE (teawing effect) at VBWANK */
	wet = mipi_dsi_dcs_set_teaw_on(dsi,
				       MIPI_DSI_DCS_TEAW_MODE_VBWANK);
	if (wet) {
		dev_eww(s6->dev, "faiwed to enabwe vbwank TE (%d)\n", wet);
		wetuwn wet;
	}
	/* Exit sweep mode and powew on */
	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet) {
		dev_eww(s6->dev, "faiwed to exit sweep mode (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int s6d16d0_enabwe(stwuct dwm_panew *panew)
{
	stwuct s6d16d0 *s6 = panew_to_s6d16d0(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(s6->dev);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet) {
		dev_eww(s6->dev, "faiwed to tuwn dispway on (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int s6d16d0_disabwe(stwuct dwm_panew *panew)
{
	stwuct s6d16d0 *s6 = panew_to_s6d16d0(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(s6->dev);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet) {
		dev_eww(s6->dev, "faiwed to tuwn dispway off (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int s6d16d0_get_modes(stwuct dwm_panew *panew,
			     stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &samsung_s6d16d0_mode);
	if (!mode) {
		dev_eww(panew->dev, "bad mode ow faiwed to add mode\n");
		wetuwn -EINVAW;
	}
	dwm_mode_set_name(mode);
	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;

	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;

	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1; /* Numbew of modes */
}

static const stwuct dwm_panew_funcs s6d16d0_dwm_funcs = {
	.disabwe = s6d16d0_disabwe,
	.unpwepawe = s6d16d0_unpwepawe,
	.pwepawe = s6d16d0_pwepawe,
	.enabwe = s6d16d0_enabwe,
	.get_modes = s6d16d0_get_modes,
};

static int s6d16d0_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct s6d16d0 *s6;
	int wet;

	s6 = devm_kzawwoc(dev, sizeof(stwuct s6d16d0), GFP_KEWNEW);
	if (!s6)
		wetuwn -ENOMEM;

	mipi_dsi_set_dwvdata(dsi, s6);
	s6->dev = dev;

	dsi->wanes = 2;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->hs_wate = 420160000;
	dsi->wp_wate = 19200000;
	/*
	 * This dispway uses command mode so no MIPI_DSI_MODE_VIDEO
	 * ow MIPI_DSI_MODE_VIDEO_SYNC_PUWSE
	 *
	 * As we onwy send commands we do not need to be continuouswy
	 * cwocked.
	 */
	dsi->mode_fwags = MIPI_DSI_CWOCK_NON_CONTINUOUS;

	s6->suppwy = devm_weguwatow_get(dev, "vdd1");
	if (IS_EWW(s6->suppwy))
		wetuwn PTW_EWW(s6->suppwy);

	/* This assewts WESET by defauwt */
	s6->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						 GPIOD_OUT_HIGH);
	if (IS_EWW(s6->weset_gpio)) {
		wet = PTW_EWW(s6->weset_gpio);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to wequest GPIO (%d)\n", wet);
		wetuwn wet;
	}

	dwm_panew_init(&s6->panew, dev, &s6d16d0_dwm_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	dwm_panew_add(&s6->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0)
		dwm_panew_wemove(&s6->panew);

	wetuwn wet;
}

static void s6d16d0_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct s6d16d0 *s6 = mipi_dsi_get_dwvdata(dsi);

	mipi_dsi_detach(dsi);
	dwm_panew_wemove(&s6->panew);
}

static const stwuct of_device_id s6d16d0_of_match[] = {
	{ .compatibwe = "samsung,s6d16d0" },
	{ }
};
MODUWE_DEVICE_TABWE(of, s6d16d0_of_match);

static stwuct mipi_dsi_dwivew s6d16d0_dwivew = {
	.pwobe = s6d16d0_pwobe,
	.wemove = s6d16d0_wemove,
	.dwivew = {
		.name = "panew-samsung-s6d16d0",
		.of_match_tabwe = s6d16d0_of_match,
	},
};
moduwe_mipi_dsi_dwivew(s6d16d0_dwivew);

MODUWE_AUTHOW("Winus Wawwei <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("MIPI-DSI s6d16d0 Panew Dwivew");
MODUWE_WICENSE("GPW v2");
