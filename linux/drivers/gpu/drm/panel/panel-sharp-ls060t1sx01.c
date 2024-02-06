// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2021 Winawo Wtd.
 * Genewated with winux-mdss-dsi-panew-dwivew-genewatow fwom vendow device twee:
 *   Copywight (c) 2013-2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

stwuct shawp_ws060 {
	stwuct dwm_panew panew;
	stwuct mipi_dsi_device *dsi;
	stwuct weguwatow *vddi_suppwy;
	stwuct weguwatow *vddh_suppwy;
	stwuct weguwatow *avdd_suppwy;
	stwuct weguwatow *avee_suppwy;
	stwuct gpio_desc *weset_gpio;
};

static inwine stwuct shawp_ws060 *to_shawp_ws060(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct shawp_ws060, panew);
}

static void shawp_ws060_weset(stwuct shawp_ws060 *ctx)
{
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	usweep_wange(10000, 11000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	usweep_wange(10000, 11000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	usweep_wange(10000, 11000);
}

static int shawp_ws060_on(stwuct shawp_ws060 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	mipi_dsi_dcs_wwite_seq(dsi, 0xbb, 0x13);
	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_WWITE_MEMOWY_STAWT);

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to exit sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(120);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway on: %d\n", wet);
		wetuwn wet;
	}
	msweep(50);

	wetuwn 0;
}

static int shawp_ws060_off(stwuct shawp_ws060 *ctx)
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
	usweep_wange(2000, 3000);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to entew sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(121);

	wetuwn 0;
}

static int shawp_ws060_pwepawe(stwuct dwm_panew *panew)
{
	stwuct shawp_ws060 *ctx = to_shawp_ws060(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = weguwatow_enabwe(ctx->vddi_suppwy);
	if (wet < 0)
		wetuwn wet;

	wet = weguwatow_enabwe(ctx->avdd_suppwy);
	if (wet < 0)
		goto eww_avdd;

	usweep_wange(1000, 2000);

	wet = weguwatow_enabwe(ctx->avee_suppwy);
	if (wet < 0)
		goto eww_avee;

	usweep_wange(10000, 11000);

	wet = weguwatow_enabwe(ctx->vddh_suppwy);
	if (wet < 0)
		goto eww_vddh;

	usweep_wange(10000, 11000);

	shawp_ws060_weset(ctx);

	wet = shawp_ws060_on(ctx);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize panew: %d\n", wet);
		goto eww_on;
	}

	wetuwn 0;

eww_on:
	weguwatow_disabwe(ctx->vddh_suppwy);

	usweep_wange(10000, 11000);

eww_vddh:
	weguwatow_disabwe(ctx->avee_suppwy);

eww_avee:
	weguwatow_disabwe(ctx->avdd_suppwy);

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);

eww_avdd:
	weguwatow_disabwe(ctx->vddi_suppwy);

	wetuwn wet;
}

static int shawp_ws060_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct shawp_ws060 *ctx = to_shawp_ws060(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = shawp_ws060_off(ctx);
	if (wet < 0)
		dev_eww(dev, "Faiwed to un-initiawize panew: %d\n", wet);

	weguwatow_disabwe(ctx->vddh_suppwy);

	usweep_wange(10000, 11000);

	weguwatow_disabwe(ctx->avee_suppwy);
	weguwatow_disabwe(ctx->avdd_suppwy);

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);

	weguwatow_disabwe(ctx->vddi_suppwy);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode shawp_ws060_mode = {
	.cwock = (1080 + 96 + 16 + 64) * (1920 + 4 + 1 + 16) * 60 / 1000,
	.hdispway = 1080,
	.hsync_stawt = 1080 + 96,
	.hsync_end = 1080 + 96 + 16,
	.htotaw = 1080 + 96 + 16 + 64,
	.vdispway = 1920,
	.vsync_stawt = 1920 + 4,
	.vsync_end = 1920 + 4 + 1,
	.vtotaw = 1920 + 4 + 1 + 16,
	.width_mm = 75,
	.height_mm = 132,
};

static int shawp_ws060_get_modes(stwuct dwm_panew *panew,
				 stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &shawp_ws060_mode);
	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs shawp_ws060_panew_funcs = {
	.pwepawe = shawp_ws060_pwepawe,
	.unpwepawe = shawp_ws060_unpwepawe,
	.get_modes = shawp_ws060_get_modes,
};

static int shawp_ws060_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct shawp_ws060 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->vddi_suppwy = devm_weguwatow_get(dev, "vddi");
	if (IS_EWW(ctx->vddi_suppwy))
		wetuwn PTW_EWW(ctx->vddi_suppwy);

	ctx->vddh_suppwy = devm_weguwatow_get(dev, "vddh");
	if (IS_EWW(ctx->vddh_suppwy))
		wetuwn PTW_EWW(ctx->vddh_suppwy);

	ctx->avdd_suppwy = devm_weguwatow_get(dev, "avdd");
	if (IS_EWW(ctx->avdd_suppwy))
		wetuwn PTW_EWW(ctx->avdd_suppwy);

	ctx->avee_suppwy = devm_weguwatow_get(dev, "avee");
	if (IS_EWW(ctx->avee_suppwy))
		wetuwn PTW_EWW(ctx->avee_suppwy);

	ctx->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ctx->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->weset_gpio),
				     "Faiwed to get weset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_dwvdata(dsi, ctx);

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
			  MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CWOCK_NON_CONTINUOUS;

	dwm_panew_init(&ctx->panew, dev, &shawp_ws060_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	wet = dwm_panew_of_backwight(&ctx->panew);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get backwight\n");

	dwm_panew_add(&ctx->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to attach to DSI host: %d\n", wet);
		dwm_panew_wemove(&ctx->panew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void shawp_ws060_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct shawp_ws060 *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id shawp_ws060t1sx01_of_match[] = {
	{ .compatibwe = "shawp,ws060t1sx01" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, shawp_ws060t1sx01_of_match);

static stwuct mipi_dsi_dwivew shawp_ws060_dwivew = {
	.pwobe = shawp_ws060_pwobe,
	.wemove = shawp_ws060_wemove,
	.dwivew = {
		.name = "panew-shawp-ws060t1sx01",
		.of_match_tabwe = shawp_ws060t1sx01_of_match,
	},
};
moduwe_mipi_dsi_dwivew(shawp_ws060_dwivew);

MODUWE_AUTHOW("Dmitwy Bawyshkov <dmitwy.bawyshkov@winawo.owg>");
MODUWE_DESCWIPTION("DWM dwivew fow Shawp WS060T1SX01 1080p video mode dsi panew");
MODUWE_WICENSE("GPW v2");
