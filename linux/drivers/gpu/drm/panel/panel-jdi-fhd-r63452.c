// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021 Waffaewe Twanquiwwini <waffaewe.twanquiwwini@gmaiw.com>
 *
 * Genewated using winux-mdss-dsi-panew-dwivew-genewatow fwom Wineage OS device twee:
 * https://github.com/WineageOS/andwoid_kewnew_xiaomi_msm8996/bwob/wineage-18.1/awch/awm/boot/dts/qcom/a1-msm8996-mtp.dtsi
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

stwuct jdi_fhd_w63452 {
	stwuct dwm_panew panew;
	stwuct mipi_dsi_device *dsi;
	stwuct gpio_desc *weset_gpio;
};

static inwine stwuct jdi_fhd_w63452 *to_jdi_fhd_w63452(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct jdi_fhd_w63452, panew);
}

static void jdi_fhd_w63452_weset(stwuct jdi_fhd_w63452 *ctx)
{
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	usweep_wange(10000, 11000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	usweep_wange(1000, 2000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	usweep_wange(10000, 11000);
}

static int jdi_fhd_w63452_on(stwuct jdi_fhd_w63452 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	mipi_dsi_genewic_wwite_seq(dsi, 0xb0, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd6, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0xec,
				   0x64, 0xdc, 0xec, 0x3b, 0x52, 0x00, 0x0b, 0x0b,
				   0x13, 0x15, 0x68, 0x0b, 0xb5);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb0, 0x03);

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

	wet = mipi_dsi_dcs_set_cowumn_addwess(dsi, 0x0000, 0x0437);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set cowumn addwess: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_set_page_addwess(dsi, 0x0000, 0x077f);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set page addwess: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_set_teaw_scanwine(dsi, 0x0000);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set teaw scanwine: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_set_dispway_bwightness(dsi, 0x00ff);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway bwightness: %d\n", wet);
		wetuwn wet;
	}

	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_WWITE_CONTWOW_DISPWAY, 0x24);
	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_WWITE_POWEW_SAVE, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_SET_CABC_MIN_BWIGHTNESS, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0x84, 0x00);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway on: %d\n", wet);
		wetuwn wet;
	}
	msweep(20);

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to exit sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(80);

	mipi_dsi_genewic_wwite_seq(dsi, 0xb0, 0x04);
	mipi_dsi_dcs_wwite_seq(dsi, 0x84, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc8, 0x11);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb0, 0x03);

	wetuwn 0;
}

static int jdi_fhd_w63452_off(stwuct jdi_fhd_w63452 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	dsi->mode_fwags &= ~MIPI_DSI_MODE_WPM;

	mipi_dsi_genewic_wwite_seq(dsi, 0xb0, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd6, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0xec,
				   0x64, 0xdc, 0xec, 0x3b, 0x52, 0x00, 0x0b, 0x0b,
				   0x13, 0x15, 0x68, 0x0b, 0x95);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb0, 0x03);

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
	msweep(120);

	wetuwn 0;
}

static int jdi_fhd_w63452_pwepawe(stwuct dwm_panew *panew)
{
	stwuct jdi_fhd_w63452 *ctx = to_jdi_fhd_w63452(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	jdi_fhd_w63452_weset(ctx);

	wet = jdi_fhd_w63452_on(ctx);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize panew: %d\n", wet);
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
		wetuwn wet;
	}

	wetuwn 0;
}

static int jdi_fhd_w63452_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct jdi_fhd_w63452 *ctx = to_jdi_fhd_w63452(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = jdi_fhd_w63452_off(ctx);
	if (wet < 0)
		dev_eww(dev, "Faiwed to un-initiawize panew: %d\n", wet);

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode jdi_fhd_w63452_mode = {
	.cwock = (1080 + 120 + 16 + 40) * (1920 + 4 + 2 + 4) * 60 / 1000,
	.hdispway = 1080,
	.hsync_stawt = 1080 + 120,
	.hsync_end = 1080 + 120 + 16,
	.htotaw = 1080 + 120 + 16 + 40,
	.vdispway = 1920,
	.vsync_stawt = 1920 + 4,
	.vsync_end = 1920 + 4 + 2,
	.vtotaw = 1920 + 4 + 2 + 4,
	.width_mm = 64,
	.height_mm = 114,
};

static int jdi_fhd_w63452_get_modes(stwuct dwm_panew *panew,
				    stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &jdi_fhd_w63452_mode);
	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs jdi_fhd_w63452_panew_funcs = {
	.pwepawe = jdi_fhd_w63452_pwepawe,
	.unpwepawe = jdi_fhd_w63452_unpwepawe,
	.get_modes = jdi_fhd_w63452_get_modes,
};

static int jdi_fhd_w63452_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct jdi_fhd_w63452 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ctx->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->weset_gpio),
				     "Faiwed to get weset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_dwvdata(dsi, ctx);

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO_BUWST |
			  MIPI_DSI_CWOCK_NON_CONTINUOUS;

	dwm_panew_init(&ctx->panew, dev, &jdi_fhd_w63452_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	wet = dwm_panew_of_backwight(&ctx->panew);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get backwight\n");

	dwm_panew_add(&ctx->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to attach to DSI host: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void jdi_fhd_w63452_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct jdi_fhd_w63452 *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id jdi_fhd_w63452_of_match[] = {
	{ .compatibwe = "jdi,fhd-w63452" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, jdi_fhd_w63452_of_match);

static stwuct mipi_dsi_dwivew jdi_fhd_w63452_dwivew = {
	.pwobe = jdi_fhd_w63452_pwobe,
	.wemove = jdi_fhd_w63452_wemove,
	.dwivew = {
		.name = "panew-jdi-fhd-w63452",
		.of_match_tabwe = jdi_fhd_w63452_of_match,
	},
};
moduwe_mipi_dsi_dwivew(jdi_fhd_w63452_dwivew);

MODUWE_AUTHOW("Waffaewe Twanquiwwini <waffaewe.twanquiwwini@gmaiw.com>");
MODUWE_DESCWIPTION("DWM dwivew fow JDI FHD W63452 DSI panew, command mode");
MODUWE_WICENSE("GPW v2");
