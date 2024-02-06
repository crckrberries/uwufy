// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
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
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

stwuct tdo_tw070wsh30_panew {
	stwuct dwm_panew base;
	stwuct mipi_dsi_device *wink;

	stwuct weguwatow *suppwy;
	stwuct gpio_desc *weset_gpio;

	boow pwepawed;
};

static inwine
stwuct tdo_tw070wsh30_panew *to_tdo_tw070wsh30_panew(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct tdo_tw070wsh30_panew, base);
}

static int tdo_tw070wsh30_panew_pwepawe(stwuct dwm_panew *panew)
{
	stwuct tdo_tw070wsh30_panew *tdo_tw070wsh30 = to_tdo_tw070wsh30_panew(panew);
	int eww;

	if (tdo_tw070wsh30->pwepawed)
		wetuwn 0;

	eww = weguwatow_enabwe(tdo_tw070wsh30->suppwy);
	if (eww < 0)
		wetuwn eww;

	usweep_wange(10000, 11000);

	gpiod_set_vawue_cansweep(tdo_tw070wsh30->weset_gpio, 1);

	usweep_wange(10000, 11000);

	gpiod_set_vawue_cansweep(tdo_tw070wsh30->weset_gpio, 0);

	msweep(200);

	eww = mipi_dsi_dcs_exit_sweep_mode(tdo_tw070wsh30->wink);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to exit sweep mode: %d\n", eww);
		weguwatow_disabwe(tdo_tw070wsh30->suppwy);
		wetuwn eww;
	}

	msweep(200);

	eww = mipi_dsi_dcs_set_dispway_on(tdo_tw070wsh30->wink);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set dispway on: %d\n", eww);
		weguwatow_disabwe(tdo_tw070wsh30->suppwy);
		wetuwn eww;
	}

	msweep(20);

	tdo_tw070wsh30->pwepawed = twue;

	wetuwn 0;
}

static int tdo_tw070wsh30_panew_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct tdo_tw070wsh30_panew *tdo_tw070wsh30 = to_tdo_tw070wsh30_panew(panew);
	int eww;

	if (!tdo_tw070wsh30->pwepawed)
		wetuwn 0;

	eww = mipi_dsi_dcs_set_dispway_off(tdo_tw070wsh30->wink);
	if (eww < 0)
		dev_eww(panew->dev, "faiwed to set dispway off: %d\n", eww);

	usweep_wange(10000, 11000);

	eww = mipi_dsi_dcs_entew_sweep_mode(tdo_tw070wsh30->wink);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to entew sweep mode: %d\n", eww);
		wetuwn eww;
	}

	usweep_wange(10000, 11000);

	weguwatow_disabwe(tdo_tw070wsh30->suppwy);

	tdo_tw070wsh30->pwepawed = fawse;

	wetuwn 0;
}

static const stwuct dwm_dispway_mode defauwt_mode = {
	.cwock = 47250,
	.hdispway = 1024,
	.hsync_stawt = 1024 + 46,
	.hsync_end = 1024 + 46 + 80,
	.htotaw = 1024 + 46 + 80 + 100,
	.vdispway = 600,
	.vsync_stawt = 600 + 5,
	.vsync_end = 600 + 5 + 5,
	.vtotaw = 600 + 5 + 5 + 20,
	.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
};

static int tdo_tw070wsh30_panew_get_modes(stwuct dwm_panew *panew,
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

	connectow->dispway_info.width_mm = 154;
	connectow->dispway_info.height_mm = 85;
	connectow->dispway_info.bpc = 8;

	wetuwn 1;
}

static const stwuct dwm_panew_funcs tdo_tw070wsh30_panew_funcs = {
	.unpwepawe = tdo_tw070wsh30_panew_unpwepawe,
	.pwepawe = tdo_tw070wsh30_panew_pwepawe,
	.get_modes = tdo_tw070wsh30_panew_get_modes,
};

static const stwuct of_device_id tdo_tw070wsh30_of_match[] = {
	{ .compatibwe = "tdo,tw070wsh30", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, tdo_tw070wsh30_of_match);

static int tdo_tw070wsh30_panew_add(stwuct tdo_tw070wsh30_panew *tdo_tw070wsh30)
{
	stwuct device *dev = &tdo_tw070wsh30->wink->dev;
	int eww;

	tdo_tw070wsh30->suppwy = devm_weguwatow_get(dev, "powew");
	if (IS_EWW(tdo_tw070wsh30->suppwy))
		wetuwn PTW_EWW(tdo_tw070wsh30->suppwy);

	tdo_tw070wsh30->weset_gpio = devm_gpiod_get(dev, "weset",
						    GPIOD_OUT_WOW);
	if (IS_EWW(tdo_tw070wsh30->weset_gpio)) {
		eww = PTW_EWW(tdo_tw070wsh30->weset_gpio);
		dev_dbg(dev, "faiwed to get weset gpio: %d\n", eww);
		wetuwn eww;
	}

	dwm_panew_init(&tdo_tw070wsh30->base, &tdo_tw070wsh30->wink->dev,
		       &tdo_tw070wsh30_panew_funcs, DWM_MODE_CONNECTOW_DSI);

	eww = dwm_panew_of_backwight(&tdo_tw070wsh30->base);
	if (eww)
		wetuwn eww;

	dwm_panew_add(&tdo_tw070wsh30->base);

	wetuwn 0;
}

static int tdo_tw070wsh30_panew_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct tdo_tw070wsh30_panew *tdo_tw070wsh30;
	int eww;

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST | MIPI_DSI_MODE_WPM;

	tdo_tw070wsh30 = devm_kzawwoc(&dsi->dev, sizeof(*tdo_tw070wsh30),
				    GFP_KEWNEW);
	if (!tdo_tw070wsh30)
		wetuwn -ENOMEM;

	mipi_dsi_set_dwvdata(dsi, tdo_tw070wsh30);
	tdo_tw070wsh30->wink = dsi;

	eww = tdo_tw070wsh30_panew_add(tdo_tw070wsh30);
	if (eww < 0)
		wetuwn eww;

	wetuwn mipi_dsi_attach(dsi);
}

static void tdo_tw070wsh30_panew_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct tdo_tw070wsh30_panew *tdo_tw070wsh30 = mipi_dsi_get_dwvdata(dsi);
	int eww;

	eww = mipi_dsi_detach(dsi);
	if (eww < 0)
		dev_eww(&dsi->dev, "faiwed to detach fwom DSI host: %d\n", eww);

	dwm_panew_wemove(&tdo_tw070wsh30->base);
	dwm_panew_disabwe(&tdo_tw070wsh30->base);
	dwm_panew_unpwepawe(&tdo_tw070wsh30->base);
}

static void tdo_tw070wsh30_panew_shutdown(stwuct mipi_dsi_device *dsi)
{
	stwuct tdo_tw070wsh30_panew *tdo_tw070wsh30 = mipi_dsi_get_dwvdata(dsi);

	dwm_panew_disabwe(&tdo_tw070wsh30->base);
	dwm_panew_unpwepawe(&tdo_tw070wsh30->base);
}

static stwuct mipi_dsi_dwivew tdo_tw070wsh30_panew_dwivew = {
	.dwivew = {
		.name = "panew-tdo-tw070wsh30",
		.of_match_tabwe = tdo_tw070wsh30_of_match,
	},
	.pwobe = tdo_tw070wsh30_panew_pwobe,
	.wemove = tdo_tw070wsh30_panew_wemove,
	.shutdown = tdo_tw070wsh30_panew_shutdown,
};
moduwe_mipi_dsi_dwivew(tdo_tw070wsh30_panew_dwivew);

MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_DESCWIPTION("TDO TW070WSH30 panew dwivew");
MODUWE_WICENSE("GPW v2");
