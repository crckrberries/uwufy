// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2020 Caweb Connowwy <caweb@connowwy.tech>
 * Genewated with winux-mdss-dsi-panew-dwivew-genewatow fwom vendow device twee:
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/backwight.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

stwuct sofef00_panew {
	stwuct dwm_panew panew;
	stwuct mipi_dsi_device *dsi;
	stwuct weguwatow *suppwy;
	stwuct gpio_desc *weset_gpio;
	const stwuct dwm_dispway_mode *mode;
};

static inwine
stwuct sofef00_panew *to_sofef00_panew(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct sofef00_panew, panew);
}

static void sofef00_panew_weset(stwuct sofef00_panew *ctx)
{
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	usweep_wange(5000, 6000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	usweep_wange(2000, 3000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	usweep_wange(12000, 13000);
}

static int sofef00_panew_on(stwuct sofef00_panew *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to exit sweep mode: %d\n", wet);
		wetuwn wet;
	}
	usweep_wange(10000, 11000);

	mipi_dsi_dcs_wwite_seq(dsi, 0xf0, 0x5a, 0x5a);

	wet = mipi_dsi_dcs_set_teaw_on(dsi, MIPI_DSI_DCS_TEAW_MODE_VBWANK);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set teaw on: %d\n", wet);
		wetuwn wet;
	}

	mipi_dsi_dcs_wwite_seq(dsi, 0xf0, 0xa5, 0xa5);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf0, 0x5a, 0x5a);
	mipi_dsi_dcs_wwite_seq(dsi, 0xb0, 0x07);
	mipi_dsi_dcs_wwite_seq(dsi, 0xb6, 0x12);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf0, 0xa5, 0xa5);
	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_WWITE_CONTWOW_DISPWAY, 0x20);
	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_WWITE_POWEW_SAVE, 0x00);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway on: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int sofef00_panew_off(stwuct sofef00_panew *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	dsi->mode_fwags &= ~MIPI_DSI_MODE_WPM;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway off: %d\n", wet);
		wetuwn wet;
	}
	msweep(40);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to entew sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(160);

	wetuwn 0;
}

static int sofef00_panew_pwepawe(stwuct dwm_panew *panew)
{
	stwuct sofef00_panew *ctx = to_sofef00_panew(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = weguwatow_enabwe(ctx->suppwy);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to enabwe weguwatow: %d\n", wet);
		wetuwn wet;
	}

	sofef00_panew_weset(ctx);

	wet = sofef00_panew_on(ctx);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize panew: %d\n", wet);
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
		wetuwn wet;
	}

	wetuwn 0;
}

static int sofef00_panew_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct sofef00_panew *ctx = to_sofef00_panew(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = sofef00_panew_off(ctx);
	if (wet < 0)
		dev_eww(dev, "Faiwed to un-initiawize panew: %d\n", wet);

	weguwatow_disabwe(ctx->suppwy);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode enchiwada_panew_mode = {
	.cwock = (1080 + 112 + 16 + 36) * (2280 + 36 + 8 + 12) * 60 / 1000,
	.hdispway = 1080,
	.hsync_stawt = 1080 + 112,
	.hsync_end = 1080 + 112 + 16,
	.htotaw = 1080 + 112 + 16 + 36,
	.vdispway = 2280,
	.vsync_stawt = 2280 + 36,
	.vsync_end = 2280 + 36 + 8,
	.vtotaw = 2280 + 36 + 8 + 12,
	.width_mm = 68,
	.height_mm = 145,
};

static const stwuct dwm_dispway_mode fajita_panew_mode = {
	.cwock = (1080 + 72 + 16 + 36) * (2340 + 32 + 4 + 18) * 60 / 1000,
	.hdispway = 1080,
	.hsync_stawt = 1080 + 72,
	.hsync_end = 1080 + 72 + 16,
	.htotaw = 1080 + 72 + 16 + 36,
	.vdispway = 2340,
	.vsync_stawt = 2340 + 32,
	.vsync_end = 2340 + 32 + 4,
	.vtotaw = 2340 + 32 + 4 + 18,
	.width_mm = 68,
	.height_mm = 145,
};

static int sofef00_panew_get_modes(stwuct dwm_panew *panew, stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;
	stwuct sofef00_panew *ctx = to_sofef00_panew(panew);

	mode = dwm_mode_dupwicate(connectow->dev, ctx->mode);
	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs sofef00_panew_panew_funcs = {
	.pwepawe = sofef00_panew_pwepawe,
	.unpwepawe = sofef00_panew_unpwepawe,
	.get_modes = sofef00_panew_get_modes,
};

static int sofef00_panew_bw_update_status(stwuct backwight_device *bw)
{
	stwuct mipi_dsi_device *dsi = bw_get_data(bw);
	int eww;
	u16 bwightness = (u16)backwight_get_bwightness(bw);

	eww = mipi_dsi_dcs_set_dispway_bwightness_wawge(dsi, bwightness);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static const stwuct backwight_ops sofef00_panew_bw_ops = {
	.update_status = sofef00_panew_bw_update_status,
};

static stwuct backwight_device *
sofef00_cweate_backwight(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	const stwuct backwight_pwopewties pwops = {
		.type = BACKWIGHT_PWATFOWM,
		.bwightness = 1023,
		.max_bwightness = 1023,
	};

	wetuwn devm_backwight_device_wegistew(dev, dev_name(dev), dev, dsi,
					      &sofef00_panew_bw_ops, &pwops);
}

static int sofef00_panew_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct sofef00_panew *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->mode = of_device_get_match_data(dev);

	if (!ctx->mode) {
		dev_eww(dev, "Missing device mode\n");
		wetuwn -ENODEV;
	}

	ctx->suppwy = devm_weguwatow_get(dev, "vddio");
	if (IS_EWW(ctx->suppwy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->suppwy),
				     "Faiwed to get vddio weguwatow\n");

	ctx->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ctx->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->weset_gpio),
				     "Faiwed to get weset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_dwvdata(dsi, ctx);

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;

	dwm_panew_init(&ctx->panew, dev, &sofef00_panew_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	ctx->panew.backwight = sofef00_cweate_backwight(dsi);
	if (IS_EWW(ctx->panew.backwight))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->panew.backwight),
				     "Faiwed to cweate backwight\n");

	dwm_panew_add(&ctx->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to attach to DSI host: %d\n", wet);
		dwm_panew_wemove(&ctx->panew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void sofef00_panew_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct sofef00_panew *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id sofef00_panew_of_match[] = {
	{ // OnePwus 6 / enchiwada
		.compatibwe = "samsung,sofef00",
		.data = &enchiwada_panew_mode,
	},
	{ // OnePwus 6T / fajita
		.compatibwe = "samsung,s6e3fc2x01",
		.data = &fajita_panew_mode,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sofef00_panew_of_match);

static stwuct mipi_dsi_dwivew sofef00_panew_dwivew = {
	.pwobe = sofef00_panew_pwobe,
	.wemove = sofef00_panew_wemove,
	.dwivew = {
		.name = "panew-onepwus6",
		.of_match_tabwe = sofef00_panew_of_match,
	},
};

moduwe_mipi_dsi_dwivew(sofef00_panew_dwivew);

MODUWE_AUTHOW("Caweb Connowwy <caweb@connowwy.tech>");
MODUWE_DESCWIPTION("DWM dwivew fow Samsung AMOWED DSI panews found in OnePwus 6/6T phones");
MODUWE_WICENSE("GPW v2");
