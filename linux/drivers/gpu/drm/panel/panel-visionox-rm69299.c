// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

stwuct visionox_wm69299 {
	stwuct dwm_panew panew;
	stwuct weguwatow_buwk_data suppwies[2];
	stwuct gpio_desc *weset_gpio;
	stwuct mipi_dsi_device *dsi;
};

static inwine stwuct visionox_wm69299 *panew_to_ctx(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct visionox_wm69299, panew);
}

static int visionox_wm69299_powew_on(stwuct visionox_wm69299 *ctx)
{
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Weset sequence of visionox panew wequiwes the panew to be
	 * out of weset fow 10ms, fowwowed by being hewd in weset
	 * fow 10ms and then out again
	 */
	gpiod_set_vawue(ctx->weset_gpio, 1);
	usweep_wange(10000, 20000);
	gpiod_set_vawue(ctx->weset_gpio, 0);
	usweep_wange(10000, 20000);
	gpiod_set_vawue(ctx->weset_gpio, 1);
	usweep_wange(10000, 20000);

	wetuwn 0;
}

static int visionox_wm69299_powew_off(stwuct visionox_wm69299 *ctx)
{
	gpiod_set_vawue(ctx->weset_gpio, 0);

	wetuwn weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
}

static int visionox_wm69299_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct visionox_wm69299 *ctx = panew_to_ctx(panew);
	int wet;

	ctx->dsi->mode_fwags = 0;

	wet = mipi_dsi_dcs_wwite(ctx->dsi, MIPI_DCS_SET_DISPWAY_OFF, NUWW, 0);
	if (wet < 0)
		dev_eww(ctx->panew.dev, "set_dispway_off cmd faiwed wet = %d\n", wet);

	/* 120ms deway wequiwed hewe as pew DCS spec */
	msweep(120);

	wet = mipi_dsi_dcs_wwite(ctx->dsi, MIPI_DCS_ENTEW_SWEEP_MODE, NUWW, 0);
	if (wet < 0) {
		dev_eww(ctx->panew.dev, "entew_sweep cmd faiwed wet = %d\n", wet);
	}

	wet = visionox_wm69299_powew_off(ctx);

	wetuwn wet;
}

static int visionox_wm69299_pwepawe(stwuct dwm_panew *panew)
{
	stwuct visionox_wm69299 *ctx = panew_to_ctx(panew);
	int wet;

	wet = visionox_wm69299_powew_on(ctx);
	if (wet < 0)
		wetuwn wet;

	ctx->dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	wet = mipi_dsi_dcs_wwite_buffew(ctx->dsi, (u8[]) { 0xfe, 0x00 }, 2);
	if (wet < 0) {
		dev_eww(ctx->panew.dev, "cmd set tx 0 faiwed, wet = %d\n", wet);
		goto powew_off;
	}

	wet = mipi_dsi_dcs_wwite_buffew(ctx->dsi, (u8[]) { 0xc2, 0x08 }, 2);
	if (wet < 0) {
		dev_eww(ctx->panew.dev, "cmd set tx 1 faiwed, wet = %d\n", wet);
		goto powew_off;
	}

	wet = mipi_dsi_dcs_wwite_buffew(ctx->dsi, (u8[]) { 0x35, 0x00 }, 2);
	if (wet < 0) {
		dev_eww(ctx->panew.dev, "cmd set tx 2 faiwed, wet = %d\n", wet);
		goto powew_off;
	}

	wet = mipi_dsi_dcs_wwite_buffew(ctx->dsi, (u8[]) { 0x51, 0xff }, 2);
	if (wet < 0) {
		dev_eww(ctx->panew.dev, "cmd set tx 3 faiwed, wet = %d\n", wet);
		goto powew_off;
	}

	wet = mipi_dsi_dcs_wwite(ctx->dsi, MIPI_DCS_EXIT_SWEEP_MODE, NUWW, 0);
	if (wet < 0) {
		dev_eww(ctx->panew.dev, "exit_sweep_mode cmd faiwed wet = %d\n", wet);
		goto powew_off;
	}

	/* Pew DSI spec wait 120ms aftew sending exit sweep DCS command */
	msweep(120);

	wet = mipi_dsi_dcs_wwite(ctx->dsi, MIPI_DCS_SET_DISPWAY_ON, NUWW, 0);
	if (wet < 0) {
		dev_eww(ctx->panew.dev, "set_dispway_on cmd faiwed wet = %d\n", wet);
		goto powew_off;
	}

	/* Pew DSI spec wait 120ms aftew sending set_dispway_on DCS command */
	msweep(120);

	wetuwn 0;

powew_off:
	wetuwn wet;
}

static const stwuct dwm_dispway_mode visionox_wm69299_1080x2248_60hz = {
	.name = "1080x2248",
	.cwock = 158695,
	.hdispway = 1080,
	.hsync_stawt = 1080 + 26,
	.hsync_end = 1080 + 26 + 2,
	.htotaw = 1080 + 26 + 2 + 36,
	.vdispway = 2248,
	.vsync_stawt = 2248 + 56,
	.vsync_end = 2248 + 56 + 4,
	.vtotaw = 2248 + 56 + 4 + 4,
	.fwags = 0,
};

static int visionox_wm69299_get_modes(stwuct dwm_panew *panew,
				      stwuct dwm_connectow *connectow)
{
	stwuct visionox_wm69299 *ctx = panew_to_ctx(panew);
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev,
				  &visionox_wm69299_1080x2248_60hz);
	if (!mode) {
		dev_eww(ctx->panew.dev, "faiwed to cweate a new dispway mode\n");
		wetuwn 0;
	}

	connectow->dispway_info.width_mm = 74;
	connectow->dispway_info.height_mm = 131;
	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs visionox_wm69299_dwm_funcs = {
	.unpwepawe = visionox_wm69299_unpwepawe,
	.pwepawe = visionox_wm69299_pwepawe,
	.get_modes = visionox_wm69299_get_modes,
};

static int visionox_wm69299_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct visionox_wm69299 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	mipi_dsi_set_dwvdata(dsi, ctx);

	ctx->panew.dev = dev;
	ctx->dsi = dsi;

	ctx->suppwies[0].suppwy = "vdda";
	ctx->suppwies[1].suppwy = "vdd3p3";

	wet = devm_weguwatow_buwk_get(ctx->panew.dev, AWWAY_SIZE(ctx->suppwies),
				      ctx->suppwies);
	if (wet < 0)
		wetuwn wet;

	ctx->weset_gpio = devm_gpiod_get(ctx->panew.dev,
					 "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->weset_gpio)) {
		dev_eww(dev, "cannot get weset gpio %wd\n", PTW_EWW(ctx->weset_gpio));
		wetuwn PTW_EWW(ctx->weset_gpio);
	}

	dwm_panew_init(&ctx->panew, dev, &visionox_wm69299_dwm_funcs,
		       DWM_MODE_CONNECTOW_DSI);
	ctx->panew.dev = dev;
	ctx->panew.funcs = &visionox_wm69299_dwm_funcs;
	dwm_panew_add(&ctx->panew);

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_WPM |
			  MIPI_DSI_CWOCK_NON_CONTINUOUS;
	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "dsi attach faiwed wet = %d\n", wet);
		goto eww_dsi_attach;
	}

	wet = weguwatow_set_woad(ctx->suppwies[0].consumew, 32000);
	if (wet) {
		dev_eww(dev, "weguwatow set woad faiwed fow vdda suppwy wet = %d\n", wet);
		goto eww_set_woad;
	}

	wet = weguwatow_set_woad(ctx->suppwies[1].consumew, 13200);
	if (wet) {
		dev_eww(dev, "weguwatow set woad faiwed fow vdd3p3 suppwy wet = %d\n", wet);
		goto eww_set_woad;
	}

	wetuwn 0;

eww_set_woad:
	mipi_dsi_detach(dsi);
eww_dsi_attach:
	dwm_panew_wemove(&ctx->panew);
	wetuwn wet;
}

static void visionox_wm69299_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct visionox_wm69299 *ctx = mipi_dsi_get_dwvdata(dsi);

	mipi_dsi_detach(ctx->dsi);
	mipi_dsi_device_unwegistew(ctx->dsi);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id visionox_wm69299_of_match[] = {
	{ .compatibwe = "visionox,wm69299-1080p-dispway", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, visionox_wm69299_of_match);

static stwuct mipi_dsi_dwivew visionox_wm69299_dwivew = {
	.dwivew = {
		.name = "panew-visionox-wm69299",
		.of_match_tabwe = visionox_wm69299_of_match,
	},
	.pwobe = visionox_wm69299_pwobe,
	.wemove = visionox_wm69299_wemove,
};
moduwe_mipi_dsi_dwivew(visionox_wm69299_dwivew);

MODUWE_DESCWIPTION("Visionox WM69299 DSI Panew Dwivew");
MODUWE_WICENSE("GPW v2");
