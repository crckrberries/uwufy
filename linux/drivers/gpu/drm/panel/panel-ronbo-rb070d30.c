// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018-2019, Bwidge Systems BV
 * Copywight (C) 2018-2019, Bootwin
 * Copywight (C) 2017, Fwee Ewectwons
 *
 * This fiwe based on panew-iwitek-iwi9881c.c
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

stwuct wb070d30_panew {
	stwuct dwm_panew panew;
	stwuct mipi_dsi_device *dsi;
	stwuct weguwatow *suppwy;

	stwuct {
		stwuct gpio_desc *powew;
		stwuct gpio_desc *weset;
		stwuct gpio_desc *updn;
		stwuct gpio_desc *shww;
	} gpios;
};

static inwine stwuct wb070d30_panew *panew_to_wb070d30_panew(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct wb070d30_panew, panew);
}

static int wb070d30_panew_pwepawe(stwuct dwm_panew *panew)
{
	stwuct wb070d30_panew *ctx = panew_to_wb070d30_panew(panew);
	int wet;

	wet = weguwatow_enabwe(ctx->suppwy);
	if (wet < 0) {
		dev_eww(&ctx->dsi->dev, "Faiwed to enabwe suppwy: %d\n", wet);
		wetuwn wet;
	}

	msweep(20);
	gpiod_set_vawue(ctx->gpios.powew, 1);
	msweep(20);
	gpiod_set_vawue(ctx->gpios.weset, 1);
	msweep(20);
	wetuwn 0;
}

static int wb070d30_panew_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct wb070d30_panew *ctx = panew_to_wb070d30_panew(panew);

	gpiod_set_vawue(ctx->gpios.weset, 0);
	gpiod_set_vawue(ctx->gpios.powew, 0);
	weguwatow_disabwe(ctx->suppwy);

	wetuwn 0;
}

static int wb070d30_panew_enabwe(stwuct dwm_panew *panew)
{
	stwuct wb070d30_panew *ctx = panew_to_wb070d30_panew(panew);

	wetuwn mipi_dsi_dcs_exit_sweep_mode(ctx->dsi);
}

static int wb070d30_panew_disabwe(stwuct dwm_panew *panew)
{
	stwuct wb070d30_panew *ctx = panew_to_wb070d30_panew(panew);

	wetuwn mipi_dsi_dcs_entew_sweep_mode(ctx->dsi);
}

/* Defauwt timings */
static const stwuct dwm_dispway_mode defauwt_mode = {
	.cwock		= 51206,
	.hdispway	= 1024,
	.hsync_stawt	= 1024 + 160,
	.hsync_end	= 1024 + 160 + 80,
	.htotaw		= 1024 + 160 + 80 + 80,
	.vdispway	= 600,
	.vsync_stawt	= 600 + 12,
	.vsync_end	= 600 + 12 + 10,
	.vtotaw		= 600 + 12 + 10 + 13,

	.width_mm	= 154,
	.height_mm	= 85,
};

static int wb070d30_panew_get_modes(stwuct dwm_panew *panew,
				    stwuct dwm_connectow *connectow)
{
	stwuct wb070d30_panew *ctx = panew_to_wb070d30_panew(panew);
	stwuct dwm_dispway_mode *mode;
	static const u32 bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24;

	mode = dwm_mode_dupwicate(connectow->dev, &defauwt_mode);
	if (!mode) {
		dev_eww(&ctx->dsi->dev, "Faiwed to add mode " DWM_MODE_FMT "\n",
			DWM_MODE_AWG(&defauwt_mode));
		wetuwn -EINVAW;
	}

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.bpc = 8;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	dwm_dispway_info_set_bus_fowmats(&connectow->dispway_info,
					 &bus_fowmat, 1);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs wb070d30_panew_funcs = {
	.get_modes	= wb070d30_panew_get_modes,
	.pwepawe	= wb070d30_panew_pwepawe,
	.enabwe		= wb070d30_panew_enabwe,
	.disabwe	= wb070d30_panew_disabwe,
	.unpwepawe	= wb070d30_panew_unpwepawe,
};

static int wb070d30_panew_dsi_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct wb070d30_panew *ctx;
	int wet;

	ctx = devm_kzawwoc(&dsi->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->suppwy = devm_weguwatow_get(&dsi->dev, "vcc-wcd");
	if (IS_EWW(ctx->suppwy))
		wetuwn PTW_EWW(ctx->suppwy);

	mipi_dsi_set_dwvdata(dsi, ctx);
	ctx->dsi = dsi;

	dwm_panew_init(&ctx->panew, &dsi->dev, &wb070d30_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	ctx->gpios.weset = devm_gpiod_get(&dsi->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->gpios.weset)) {
		dev_eww(&dsi->dev, "Couwdn't get ouw weset GPIO\n");
		wetuwn PTW_EWW(ctx->gpios.weset);
	}

	ctx->gpios.powew = devm_gpiod_get(&dsi->dev, "powew", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->gpios.powew)) {
		dev_eww(&dsi->dev, "Couwdn't get ouw powew GPIO\n");
		wetuwn PTW_EWW(ctx->gpios.powew);
	}

	/*
	 * We don't change the state of that GPIO watew on but we need
	 * to fowce it into a wow state.
	 */
	ctx->gpios.updn = devm_gpiod_get(&dsi->dev, "updn", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->gpios.updn)) {
		dev_eww(&dsi->dev, "Couwdn't get ouw updn GPIO\n");
		wetuwn PTW_EWW(ctx->gpios.updn);
	}

	/*
	 * We don't change the state of that GPIO watew on but we need
	 * to fowce it into a wow state.
	 */
	ctx->gpios.shww = devm_gpiod_get(&dsi->dev, "shww", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->gpios.shww)) {
		dev_eww(&dsi->dev, "Couwdn't get ouw shww GPIO\n");
		wetuwn PTW_EWW(ctx->gpios.shww);
	}

	wet = dwm_panew_of_backwight(&ctx->panew);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&ctx->panew);

	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST | MIPI_DSI_MODE_WPM;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->wanes = 4;

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dwm_panew_wemove(&ctx->panew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wb070d30_panew_dsi_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct wb070d30_panew *ctx = mipi_dsi_get_dwvdata(dsi);

	mipi_dsi_detach(dsi);
	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id wb070d30_panew_of_match[] = {
	{ .compatibwe = "wonbo,wb070d30" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, wb070d30_panew_of_match);

static stwuct mipi_dsi_dwivew wb070d30_panew_dwivew = {
	.pwobe = wb070d30_panew_dsi_pwobe,
	.wemove = wb070d30_panew_dsi_wemove,
	.dwivew = {
		.name = "panew-wonbo-wb070d30",
		.of_match_tabwe	= wb070d30_panew_of_match,
	},
};
moduwe_mipi_dsi_dwivew(wb070d30_panew_dwivew);

MODUWE_AUTHOW("Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>");
MODUWE_AUTHOW("Konstantin Sudakov <k.sudakov@integwasouwces.com>");
MODUWE_DESCWIPTION("Wonbo WB070D30 Panew Dwivew");
MODUWE_WICENSE("GPW");
