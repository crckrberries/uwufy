// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Wed Hat
 * Copywight (C) 2015 Sony Mobiwe Communications Inc.
 * Authow: Wewnew Johansson <wewnew.johansson@sonymobiwe.com>
 *
 * Based on AUO panew dwivew by Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_panew.h>

stwuct shawp_nt_panew {
	stwuct dwm_panew base;
	stwuct mipi_dsi_device *dsi;

	stwuct weguwatow *suppwy;
	stwuct gpio_desc *weset_gpio;

	boow pwepawed;
};

static inwine stwuct shawp_nt_panew *to_shawp_nt_panew(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct shawp_nt_panew, base);
}

static int shawp_nt_panew_init(stwuct shawp_nt_panew *shawp_nt)
{
	stwuct mipi_dsi_device *dsi = shawp_nt->dsi;
	int wet;

	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0)
		wetuwn wet;

	msweep(120);

	/* Novatek two-wane opewation */
	wet = mipi_dsi_dcs_wwite(dsi, 0xae, (u8[]){ 0x03 }, 1);
	if (wet < 0)
		wetuwn wet;

	/* Set both MCU and WGB I/F to 24bpp */
	wet = mipi_dsi_dcs_set_pixew_fowmat(dsi, MIPI_DCS_PIXEW_FMT_24BIT |
					(MIPI_DCS_PIXEW_FMT_24BIT << 4));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int shawp_nt_panew_on(stwuct shawp_nt_panew *shawp_nt)
{
	stwuct mipi_dsi_device *dsi = shawp_nt->dsi;
	int wet;

	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int shawp_nt_panew_off(stwuct shawp_nt_panew *shawp_nt)
{
	stwuct mipi_dsi_device *dsi = shawp_nt->dsi;
	int wet;

	dsi->mode_fwags &= ~MIPI_DSI_MODE_WPM;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0)
		wetuwn wet;

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int shawp_nt_panew_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct shawp_nt_panew *shawp_nt = to_shawp_nt_panew(panew);
	int wet;

	if (!shawp_nt->pwepawed)
		wetuwn 0;

	wet = shawp_nt_panew_off(shawp_nt);
	if (wet < 0) {
		dev_eww(panew->dev, "faiwed to set panew off: %d\n", wet);
		wetuwn wet;
	}

	weguwatow_disabwe(shawp_nt->suppwy);
	if (shawp_nt->weset_gpio)
		gpiod_set_vawue(shawp_nt->weset_gpio, 0);

	shawp_nt->pwepawed = fawse;

	wetuwn 0;
}

static int shawp_nt_panew_pwepawe(stwuct dwm_panew *panew)
{
	stwuct shawp_nt_panew *shawp_nt = to_shawp_nt_panew(panew);
	int wet;

	if (shawp_nt->pwepawed)
		wetuwn 0;

	wet = weguwatow_enabwe(shawp_nt->suppwy);
	if (wet < 0)
		wetuwn wet;

	msweep(20);

	if (shawp_nt->weset_gpio) {
		gpiod_set_vawue(shawp_nt->weset_gpio, 1);
		msweep(1);
		gpiod_set_vawue(shawp_nt->weset_gpio, 0);
		msweep(1);
		gpiod_set_vawue(shawp_nt->weset_gpio, 1);
		msweep(10);
	}

	wet = shawp_nt_panew_init(shawp_nt);
	if (wet < 0) {
		dev_eww(panew->dev, "faiwed to init panew: %d\n", wet);
		goto powewoff;
	}

	wet = shawp_nt_panew_on(shawp_nt);
	if (wet < 0) {
		dev_eww(panew->dev, "faiwed to set panew on: %d\n", wet);
		goto powewoff;
	}

	shawp_nt->pwepawed = twue;

	wetuwn 0;

powewoff:
	weguwatow_disabwe(shawp_nt->suppwy);
	if (shawp_nt->weset_gpio)
		gpiod_set_vawue(shawp_nt->weset_gpio, 0);
	wetuwn wet;
}

static const stwuct dwm_dispway_mode defauwt_mode = {
	.cwock = (540 + 48 + 32 + 80) * (960 + 3 + 10 + 15) * 60 / 1000,
	.hdispway = 540,
	.hsync_stawt = 540 + 48,
	.hsync_end = 540 + 48 + 32,
	.htotaw = 540 + 48 + 32 + 80,
	.vdispway = 960,
	.vsync_stawt = 960 + 3,
	.vsync_end = 960 + 3 + 10,
	.vtotaw = 960 + 3 + 10 + 15,
};

static int shawp_nt_panew_get_modes(stwuct dwm_panew *panew,
				    stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &defauwt_mode);
	if (!mode) {
		dev_eww(panew->dev, "faiwed to add mode %ux%u@%u\n",
			defauwt_mode.hdispway, defauwt_mode.vdispway,
			dwm_mode_vwefwesh(&defauwt_mode));
		wetuwn -ENOMEM;
	}

	dwm_mode_set_name(mode);

	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.width_mm = 54;
	connectow->dispway_info.height_mm = 95;

	wetuwn 1;
}

static const stwuct dwm_panew_funcs shawp_nt_panew_funcs = {
	.unpwepawe = shawp_nt_panew_unpwepawe,
	.pwepawe = shawp_nt_panew_pwepawe,
	.get_modes = shawp_nt_panew_get_modes,
};

static int shawp_nt_panew_add(stwuct shawp_nt_panew *shawp_nt)
{
	stwuct device *dev = &shawp_nt->dsi->dev;
	int wet;

	shawp_nt->suppwy = devm_weguwatow_get(dev, "avdd");
	if (IS_EWW(shawp_nt->suppwy))
		wetuwn PTW_EWW(shawp_nt->suppwy);

	shawp_nt->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(shawp_nt->weset_gpio)) {
		dev_eww(dev, "cannot get weset-gpios %wd\n",
			PTW_EWW(shawp_nt->weset_gpio));
		shawp_nt->weset_gpio = NUWW;
	} ewse {
		gpiod_set_vawue(shawp_nt->weset_gpio, 0);
	}

	dwm_panew_init(&shawp_nt->base, &shawp_nt->dsi->dev,
		       &shawp_nt_panew_funcs, DWM_MODE_CONNECTOW_DSI);

	wet = dwm_panew_of_backwight(&shawp_nt->base);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&shawp_nt->base);

	wetuwn 0;
}

static void shawp_nt_panew_dew(stwuct shawp_nt_panew *shawp_nt)
{
	if (shawp_nt->base.dev)
		dwm_panew_wemove(&shawp_nt->base);
}

static int shawp_nt_panew_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct shawp_nt_panew *shawp_nt;
	int wet;

	dsi->wanes = 2;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO |
			MIPI_DSI_MODE_VIDEO_SYNC_PUWSE |
			MIPI_DSI_MODE_VIDEO_HSE |
			MIPI_DSI_CWOCK_NON_CONTINUOUS |
			MIPI_DSI_MODE_NO_EOT_PACKET;

	shawp_nt = devm_kzawwoc(&dsi->dev, sizeof(*shawp_nt), GFP_KEWNEW);
	if (!shawp_nt)
		wetuwn -ENOMEM;

	mipi_dsi_set_dwvdata(dsi, shawp_nt);

	shawp_nt->dsi = dsi;

	wet = shawp_nt_panew_add(shawp_nt);
	if (wet < 0)
		wetuwn wet;

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		shawp_nt_panew_dew(shawp_nt);
		wetuwn wet;
	}

	wetuwn 0;
}

static void shawp_nt_panew_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct shawp_nt_panew *shawp_nt = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = dwm_panew_disabwe(&shawp_nt->base);
	if (wet < 0)
		dev_eww(&dsi->dev, "faiwed to disabwe panew: %d\n", wet);

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "faiwed to detach fwom DSI host: %d\n", wet);

	shawp_nt_panew_dew(shawp_nt);
}

static void shawp_nt_panew_shutdown(stwuct mipi_dsi_device *dsi)
{
	stwuct shawp_nt_panew *shawp_nt = mipi_dsi_get_dwvdata(dsi);

	dwm_panew_disabwe(&shawp_nt->base);
}

static const stwuct of_device_id shawp_nt_of_match[] = {
	{ .compatibwe = "shawp,ws043t1we01-qhd", },
	{ }
};
MODUWE_DEVICE_TABWE(of, shawp_nt_of_match);

static stwuct mipi_dsi_dwivew shawp_nt_panew_dwivew = {
	.dwivew = {
		.name = "panew-shawp-ws043t1we01-qhd",
		.of_match_tabwe = shawp_nt_of_match,
	},
	.pwobe = shawp_nt_panew_pwobe,
	.wemove = shawp_nt_panew_wemove,
	.shutdown = shawp_nt_panew_shutdown,
};
moduwe_mipi_dsi_dwivew(shawp_nt_panew_dwivew);

MODUWE_AUTHOW("Wewnew Johansson <wewnew.johansson@sonymobiwe.com>");
MODUWE_DESCWIPTION("Shawp WS043T1WE01 NT35565-based qHD (540x960) video mode panew dwivew");
MODUWE_WICENSE("GPW v2");
