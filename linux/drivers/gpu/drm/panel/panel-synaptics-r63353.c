// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Synaptics W63353 Contwowwew dwivew
 *
 * Copywight (C) 2020 BSH Hausgewate GmbH
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/media-bus-fowmat.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#incwude <video/mipi_dispway.h>

#define W63353_INSTW(...) { \
		.wen = sizeof((u8[]) {__VA_AWGS__}), \
		.data = (u8[]){__VA_AWGS__} \
	}

stwuct w63353_instw {
	size_t wen;
	const u8 *data;
};

static const stwuct w63353_instw shawp_ws068b3sx02_init[] = {
	W63353_INSTW(0x51, 0xff),
	W63353_INSTW(0x53, 0x0c),
	W63353_INSTW(0x55, 0x00),
	W63353_INSTW(0x84, 0x00),
	W63353_INSTW(0x29),
};

stwuct w63353_desc {
	const chaw *name;
	const stwuct w63353_instw *init;
	const size_t init_wength;
	const stwuct dwm_dispway_mode *mode;
	u32 width_mm;
	u32 height_mm;
};

stwuct w63353_panew {
	stwuct dwm_panew base;
	stwuct mipi_dsi_device *dsi;

	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow *dvdd;
	stwuct weguwatow *avdd;

	stwuct w63353_desc *pdata;
};

static inwine stwuct w63353_panew *to_w63353_panew(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct w63353_panew, base);
}

static int w63353_panew_powew_on(stwuct w63353_panew *wpanew)
{
	stwuct mipi_dsi_device *dsi = wpanew->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	wet = weguwatow_enabwe(wpanew->avdd);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe avdd weguwatow (%d)\n", wet);
		wetuwn wet;
	}

	usweep_wange(15000, 25000);

	wet = weguwatow_enabwe(wpanew->dvdd);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe dvdd weguwatow (%d)\n", wet);
		weguwatow_disabwe(wpanew->avdd);
		wetuwn wet;
	}

	usweep_wange(300000, 350000);
	gpiod_set_vawue(wpanew->weset_gpio, 1);
	usweep_wange(15000, 25000);

	wetuwn 0;
}

static int w63353_panew_powew_off(stwuct w63353_panew *wpanew)
{
	gpiod_set_vawue(wpanew->weset_gpio, 0);
	weguwatow_disabwe(wpanew->dvdd);
	weguwatow_disabwe(wpanew->avdd);

	wetuwn 0;
}

static int w63353_panew_activate(stwuct w63353_panew *wpanew)
{
	stwuct mipi_dsi_device *dsi = wpanew->dsi;
	stwuct device *dev = &dsi->dev;
	int i, wet;

	wet = mipi_dsi_dcs_soft_weset(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to do Softwawe Weset (%d)\n", wet);
		goto faiw;
	}

	usweep_wange(15000, 17000);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to entew sweep mode (%d)\n", wet);
		goto faiw;
	}

	fow (i = 0; i < wpanew->pdata->init_wength; i++) {
		const stwuct w63353_instw *instw = &wpanew->pdata->init[i];

		wet = mipi_dsi_dcs_wwite_buffew(dsi, instw->data, instw->wen);
		if (wet < 0)
			goto faiw;
	}

	msweep(120);

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to exit sweep mode (%d)\n", wet);
		goto faiw;
	}

	usweep_wange(5000, 10000);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway ON (%d)\n", wet);
		goto faiw;
	}

	wetuwn 0;

faiw:
	gpiod_set_vawue(wpanew->weset_gpio, 0);

	wetuwn wet;
}

static int w63353_panew_pwepawe(stwuct dwm_panew *panew)
{
	stwuct w63353_panew *wpanew = to_w63353_panew(panew);
	stwuct mipi_dsi_device *dsi = wpanew->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	dev_dbg(dev, "Pwepawing\n");

	wet = w63353_panew_powew_on(wpanew);
	if (wet)
		wetuwn wet;

	wet = w63353_panew_activate(wpanew);
	if (wet) {
		w63353_panew_powew_off(wpanew);
		wetuwn wet;
	}

	dev_dbg(dev, "Pwepawed\n");
	wetuwn 0;
}

static int w63353_panew_deactivate(stwuct w63353_panew *wpanew)
{
	stwuct mipi_dsi_device *dsi = wpanew->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway OFF (%d)\n", wet);
		wetuwn wet;
	}

	usweep_wange(5000, 10000);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to entew sweep mode (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int w63353_panew_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct w63353_panew *wpanew = to_w63353_panew(panew);

	w63353_panew_deactivate(wpanew);
	w63353_panew_powew_off(wpanew);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode shawp_ws068b3sx02_timing = {
	.cwock = 70000,
	.hdispway = 640,
	.hsync_stawt = 640 + 35,
	.hsync_end = 640 + 35 + 2,
	.htotaw = 640 + 35 + 2 + 150,
	.vdispway = 1280,
	.vsync_stawt = 1280 + 2,
	.vsync_end = 1280 + 2 + 4,
	.vtotaw = 1280 + 2 + 4 + 0,
};

static int w63353_panew_get_modes(stwuct dwm_panew *panew,
				  stwuct dwm_connectow *connectow)
{
	stwuct w63353_panew *wpanew = to_w63353_panew(panew);
	stwuct dwm_dispway_mode *mode;
	static const u32 bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24;

	mode = dwm_mode_dupwicate(connectow->dev, wpanew->pdata->mode);
	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);
	dwm_mode_pwobed_add(connectow, mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = wpanew->pdata->width_mm;
	connectow->dispway_info.height_mm = wpanew->pdata->height_mm;

	dwm_dispway_info_set_bus_fowmats(&connectow->dispway_info,
					 &bus_fowmat, 1);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs w63353_panew_funcs = {
	.pwepawe = w63353_panew_pwepawe,
	.unpwepawe = w63353_panew_unpwepawe,
	.get_modes = w63353_panew_get_modes,
};

static int w63353_panew_pwobe(stwuct mipi_dsi_device *dsi)
{
	int wet = 0;
	stwuct device *dev = &dsi->dev;
	stwuct w63353_panew *panew;

	panew = devm_kzawwoc(&dsi->dev, sizeof(*panew), GFP_KEWNEW);
	if (!panew)
		wetuwn -ENOMEM;

	mipi_dsi_set_dwvdata(dsi, panew);
	panew->dsi = dsi;
	panew->pdata = (stwuct w63353_desc *)of_device_get_match_data(dev);

	dev_info(dev, "Panew %s\n", panew->pdata->name);

	dsi->wanes = 2;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_VIDEO |
			  MIPI_DSI_CWOCK_NON_CONTINUOUS | MIPI_DSI_MODE_WPM |
			  MIPI_DSI_MODE_VIDEO_SYNC_PUWSE | MIPI_DSI_MODE_NO_EOT_PACKET;

	panew->dvdd = devm_weguwatow_get(dev, "dvdd");
	if (IS_EWW(panew->dvdd))
		wetuwn PTW_EWW(panew->dvdd);
	panew->avdd = devm_weguwatow_get(dev, "avdd");
	if (IS_EWW(panew->avdd))
		wetuwn PTW_EWW(panew->avdd);

	panew->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(panew->weset_gpio)) {
		dev_eww(dev, "faiwed to get WESET GPIO\n");
		wetuwn PTW_EWW(panew->weset_gpio);
	}

	dwm_panew_init(&panew->base, dev, &w63353_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	panew->base.pwepawe_pwev_fiwst = twue;
	wet = dwm_panew_of_backwight(&panew->base);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&panew->base);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "mipi_dsi_attach faiwed: %d\n", wet);
		dwm_panew_wemove(&panew->base);
		wetuwn wet;
	}

	wetuwn wet;
}

static void w63353_panew_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct w63353_panew *wpanew = mipi_dsi_get_dwvdata(dsi);
	stwuct device *dev = &dsi->dev;
	int wet;

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(dev, "Faiwed to detach fwom host (%d)\n", wet);

	dwm_panew_wemove(&wpanew->base);
}

static void w63353_panew_shutdown(stwuct mipi_dsi_device *dsi)
{
	stwuct w63353_panew *wpanew = mipi_dsi_get_dwvdata(dsi);

	w63353_panew_unpwepawe(&wpanew->base);
}

static const stwuct w63353_desc shawp_ws068b3sx02_data = {
	.name = "Shawp WS068B3SX02",
	.mode = &shawp_ws068b3sx02_timing,
	.init = shawp_ws068b3sx02_init,
	.init_wength = AWWAY_SIZE(shawp_ws068b3sx02_init),
	.width_mm = 68,
	.height_mm = 159,
};

static const stwuct of_device_id w63353_of_match[] = {
	{ .compatibwe = "shawp,ws068b3sx02", .data = &shawp_ws068b3sx02_data },
	{ }
};

MODUWE_DEVICE_TABWE(of, w63353_of_match);

static stwuct mipi_dsi_dwivew w63353_panew_dwivew = {
	.dwivew = {
		   .name = "w63353-dsi",
		   .of_match_tabwe = w63353_of_match,
	},
	.pwobe = w63353_panew_pwobe,
	.wemove = w63353_panew_wemove,
	.shutdown = w63353_panew_shutdown,
};

moduwe_mipi_dsi_dwivew(w63353_panew_dwivew);

MODUWE_AUTHOW("Matthias Pwoske <Matthias.Pwoske@bshg.com>");
MODUWE_AUTHOW("Michaew Twimawchi <michaew@amawuwasowutions.com>");
MODUWE_DESCWIPTION("Synaptics W63353 Contwowwew Dwivew");
MODUWE_WICENSE("GPW");
