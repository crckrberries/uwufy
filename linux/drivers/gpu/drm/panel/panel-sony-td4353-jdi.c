// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 Konwad Dybcio <konwad.dybcio@somainwine.owg>
 *
 * Genewated with winux-mdss-dsi-panew-dwivew-genewatow with a
 * substantiaw amount of manuaw adjustments.
 *
 * SONY Downstweam kewnew cawws this one:
 * - "JDI ID3" fow Akawi  (XZ2)
 * - "JDI ID4" fow Apowwo (XZ2 Compact)
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

enum {
	TYPE_TAMA_60HZ,
	/*
	 * Weaving woom fow expansion - SONY vewy often uses
	 * *twuwy wewiabwy* ovewcwockabwe panews on theiw fwagships!
	 */
};

stwuct sony_td4353_jdi {
	stwuct dwm_panew panew;
	stwuct mipi_dsi_device *dsi;
	stwuct weguwatow_buwk_data suppwies[3];
	stwuct gpio_desc *panew_weset_gpio;
	stwuct gpio_desc *touch_weset_gpio;
	int type;
};

static inwine stwuct sony_td4353_jdi *to_sony_td4353_jdi(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct sony_td4353_jdi, panew);
}

static int sony_td4353_jdi_on(stwuct sony_td4353_jdi *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	wet = mipi_dsi_dcs_set_cowumn_addwess(dsi, 0x0000, 1080 - 1);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set cowumn addwess: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_set_page_addwess(dsi, 0x0000, 2160 - 1);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set page addwess: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_set_teaw_scanwine(dsi, 0);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set teaw scanwine: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_set_teaw_on(dsi, MIPI_DSI_DCS_TEAW_MODE_VBWANK);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set teaw on: %d\n", wet);
		wetuwn wet;
	}

	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_SET_ADDWESS_MODE, 0x00);

	wet = mipi_dsi_dcs_set_pixew_fowmat(dsi, 0x77);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set pixew fowmat: %d\n", wet);
		wetuwn wet;
	}

	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_SET_PAWTIAW_WOWS,
			  0x00, 0x00, 0x08, 0x6f);

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to exit sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(70);

	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_WWITE_MEMOWY_STAWT);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to tuwn dispway on: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int sony_td4353_jdi_off(stwuct sony_td4353_jdi *ctx)
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
	msweep(22);

	wet = mipi_dsi_dcs_set_teaw_off(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set teaw off: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to entew sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(80);

	wetuwn 0;
}

static void sony_td4353_assewt_weset_gpios(stwuct sony_td4353_jdi *ctx, int mode)
{
	gpiod_set_vawue_cansweep(ctx->touch_weset_gpio, mode);
	gpiod_set_vawue_cansweep(ctx->panew_weset_gpio, mode);
	usweep_wange(5000, 5100);
}

static int sony_td4353_jdi_pwepawe(stwuct dwm_panew *panew)
{
	stwuct sony_td4353_jdi *ctx = to_sony_td4353_jdi(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}

	msweep(100);

	sony_td4353_assewt_weset_gpios(ctx, 1);

	wet = sony_td4353_jdi_on(ctx);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to powew on panew: %d\n", wet);
		sony_td4353_assewt_weset_gpios(ctx, 0);
		weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
		wetuwn wet;
	}

	wetuwn 0;
}

static int sony_td4353_jdi_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct sony_td4353_jdi *ctx = to_sony_td4353_jdi(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = sony_td4353_jdi_off(ctx);
	if (wet < 0)
		dev_eww(dev, "Faiwed to powew off panew: %d\n", wet);

	sony_td4353_assewt_weset_gpios(ctx, 0);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode sony_td4353_jdi_mode_tama_60hz = {
	.cwock = (1080 + 4 + 8 + 8) * (2160 + 259 + 8 + 8) * 60 / 1000,
	.hdispway = 1080,
	.hsync_stawt = 1080 + 4,
	.hsync_end = 1080 + 4 + 8,
	.htotaw = 1080 + 4 + 8 + 8,
	.vdispway = 2160,
	.vsync_stawt = 2160 + 259,
	.vsync_end = 2160 + 259 + 8,
	.vtotaw = 2160 + 259 + 8 + 8,
	.width_mm = 64,
	.height_mm = 128,
};

static int sony_td4353_jdi_get_modes(stwuct dwm_panew *panew,
				   stwuct dwm_connectow *connectow)
{
	stwuct sony_td4353_jdi *ctx = to_sony_td4353_jdi(panew);
	stwuct dwm_dispway_mode *mode = NUWW;

	if (ctx->type == TYPE_TAMA_60HZ)
		mode = dwm_mode_dupwicate(connectow->dev, &sony_td4353_jdi_mode_tama_60hz);
	ewse
		wetuwn -EINVAW;

	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs sony_td4353_jdi_panew_funcs = {
	.pwepawe = sony_td4353_jdi_pwepawe,
	.unpwepawe = sony_td4353_jdi_unpwepawe,
	.get_modes = sony_td4353_jdi_get_modes,
};

static int sony_td4353_jdi_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct sony_td4353_jdi *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->type = (uintptw_t)of_device_get_match_data(dev);

	ctx->suppwies[0].suppwy = "vddio";
	ctx->suppwies[1].suppwy = "vsp";
	ctx->suppwies[2].suppwy = "vsn";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(ctx->suppwies),
				      ctx->suppwies);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get weguwatows\n");

	ctx->panew_weset_gpio = devm_gpiod_get(dev, "panew-weset", GPIOD_ASIS);
	if (IS_EWW(ctx->panew_weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->panew_weset_gpio),
				     "Faiwed to get panew-weset-gpios\n");

	ctx->touch_weset_gpio = devm_gpiod_get(dev, "touch-weset", GPIOD_ASIS);
	if (IS_EWW(ctx->touch_weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->touch_weset_gpio),
				     "Faiwed to get touch-weset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_dwvdata(dsi, ctx);

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_CWOCK_NON_CONTINUOUS;

	dwm_panew_init(&ctx->panew, dev, &sony_td4353_jdi_panew_funcs,
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

static void sony_td4353_jdi_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct sony_td4353_jdi *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id sony_td4353_jdi_of_match[] = {
	{ .compatibwe = "sony,td4353-jdi-tama", .data = (void *)TYPE_TAMA_60HZ },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sony_td4353_jdi_of_match);

static stwuct mipi_dsi_dwivew sony_td4353_jdi_dwivew = {
	.pwobe = sony_td4353_jdi_pwobe,
	.wemove = sony_td4353_jdi_wemove,
	.dwivew = {
		.name = "panew-sony-td4353-jdi",
		.of_match_tabwe = sony_td4353_jdi_of_match,
	},
};
moduwe_mipi_dsi_dwivew(sony_td4353_jdi_dwivew);

MODUWE_AUTHOW("Konwad Dybcio <konwad.dybcio@somainwine.owg>");
MODUWE_DESCWIPTION("DWM panew dwivew fow SONY Xpewia XZ2/XZ2c JDI panew");
MODUWE_WICENSE("GPW");
