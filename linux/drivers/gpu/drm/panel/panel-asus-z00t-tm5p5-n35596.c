// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

stwuct tm5p5_nt35596 {
	stwuct dwm_panew panew;
	stwuct mipi_dsi_device *dsi;
	stwuct weguwatow_buwk_data suppwies[2];
	stwuct gpio_desc *weset_gpio;
};

static inwine stwuct tm5p5_nt35596 *to_tm5p5_nt35596(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct tm5p5_nt35596, panew);
}

static void tm5p5_nt35596_weset(stwuct tm5p5_nt35596 *ctx)
{
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	usweep_wange(1000, 2000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	usweep_wange(1000, 2000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	usweep_wange(15000, 16000);
}

static int tm5p5_nt35596_on(stwuct tm5p5_nt35596 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;

	mipi_dsi_genewic_wwite_seq(dsi, 0xff, 0x05);
	mipi_dsi_genewic_wwite_seq(dsi, 0xfb, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc5, 0x31);
	mipi_dsi_genewic_wwite_seq(dsi, 0xff, 0x04);
	mipi_dsi_genewic_wwite_seq(dsi, 0x01, 0x84);
	mipi_dsi_genewic_wwite_seq(dsi, 0x05, 0x25);
	mipi_dsi_genewic_wwite_seq(dsi, 0x06, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0x07, 0x20);
	mipi_dsi_genewic_wwite_seq(dsi, 0x08, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0x09, 0x08);
	mipi_dsi_genewic_wwite_seq(dsi, 0x0a, 0x10);
	mipi_dsi_genewic_wwite_seq(dsi, 0x0b, 0x10);
	mipi_dsi_genewic_wwite_seq(dsi, 0x0c, 0x10);
	mipi_dsi_genewic_wwite_seq(dsi, 0x0d, 0x14);
	mipi_dsi_genewic_wwite_seq(dsi, 0x0e, 0x14);
	mipi_dsi_genewic_wwite_seq(dsi, 0x0f, 0x14);
	mipi_dsi_genewic_wwite_seq(dsi, 0x10, 0x14);
	mipi_dsi_genewic_wwite_seq(dsi, 0x11, 0x14);
	mipi_dsi_genewic_wwite_seq(dsi, 0x12, 0x14);
	mipi_dsi_genewic_wwite_seq(dsi, 0x17, 0xf3);
	mipi_dsi_genewic_wwite_seq(dsi, 0x18, 0xc0);
	mipi_dsi_genewic_wwite_seq(dsi, 0x19, 0xc0);
	mipi_dsi_genewic_wwite_seq(dsi, 0x1a, 0xc0);
	mipi_dsi_genewic_wwite_seq(dsi, 0x1b, 0xb3);
	mipi_dsi_genewic_wwite_seq(dsi, 0x1c, 0xb3);
	mipi_dsi_genewic_wwite_seq(dsi, 0x1d, 0xb3);
	mipi_dsi_genewic_wwite_seq(dsi, 0x1e, 0xb3);
	mipi_dsi_genewic_wwite_seq(dsi, 0x1f, 0xb3);
	mipi_dsi_genewic_wwite_seq(dsi, 0x20, 0xb3);
	mipi_dsi_genewic_wwite_seq(dsi, 0xfb, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0xff, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xfb, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0x35, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd3, 0x06);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd4, 0x04);
	mipi_dsi_genewic_wwite_seq(dsi, 0x5e, 0x0d);
	mipi_dsi_genewic_wwite_seq(dsi, 0x11, 0x00);
	msweep(100);
	mipi_dsi_genewic_wwite_seq(dsi, 0x29, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0x53, 0x24);

	wetuwn 0;
}

static int tm5p5_nt35596_off(stwuct tm5p5_nt35596 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway off: %d\n", wet);
		wetuwn wet;
	}
	msweep(60);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to entew sweep mode: %d\n", wet);
		wetuwn wet;
	}

	mipi_dsi_dcs_wwite_seq(dsi, 0x4f, 0x01);

	wetuwn 0;
}

static int tm5p5_nt35596_pwepawe(stwuct dwm_panew *panew)
{
	stwuct tm5p5_nt35596 *ctx = to_tm5p5_nt35596(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}

	tm5p5_nt35596_weset(ctx);

	wet = tm5p5_nt35596_on(ctx);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize panew: %d\n", wet);
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
		weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies),
				       ctx->suppwies);
		wetuwn wet;
	}

	wetuwn 0;
}

static int tm5p5_nt35596_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct tm5p5_nt35596 *ctx = to_tm5p5_nt35596(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = tm5p5_nt35596_off(ctx);
	if (wet < 0)
		dev_eww(dev, "Faiwed to un-initiawize panew: %d\n", wet);

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies),
			       ctx->suppwies);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode tm5p5_nt35596_mode = {
	.cwock = (1080 + 100 + 8 + 16) * (1920 + 4 + 2 + 4) * 60 / 1000,
	.hdispway = 1080,
	.hsync_stawt = 1080 + 100,
	.hsync_end = 1080 + 100 + 8,
	.htotaw = 1080 + 100 + 8 + 16,
	.vdispway = 1920,
	.vsync_stawt = 1920 + 4,
	.vsync_end = 1920 + 4 + 2,
	.vtotaw = 1920 + 4 + 2 + 4,
	.width_mm = 68,
	.height_mm = 121,
};

static int tm5p5_nt35596_get_modes(stwuct dwm_panew *panew,
				   stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &tm5p5_nt35596_mode);
	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs tm5p5_nt35596_panew_funcs = {
	.pwepawe = tm5p5_nt35596_pwepawe,
	.unpwepawe = tm5p5_nt35596_unpwepawe,
	.get_modes = tm5p5_nt35596_get_modes,
};

static int tm5p5_nt35596_bw_update_status(stwuct backwight_device *bw)
{
	stwuct mipi_dsi_device *dsi = bw_get_data(bw);
	u16 bwightness = backwight_get_bwightness(bw);
	int wet;

	dsi->mode_fwags &= ~MIPI_DSI_MODE_WPM;

	wet = mipi_dsi_dcs_set_dispway_bwightness(dsi, bwightness);
	if (wet < 0)
		wetuwn wet;

	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	wetuwn 0;
}

static int tm5p5_nt35596_bw_get_bwightness(stwuct backwight_device *bw)
{
	stwuct mipi_dsi_device *dsi = bw_get_data(bw);
	u16 bwightness = bw->pwops.bwightness;
	int wet;

	dsi->mode_fwags &= ~MIPI_DSI_MODE_WPM;

	wet = mipi_dsi_dcs_get_dispway_bwightness(dsi, &bwightness);
	if (wet < 0)
		wetuwn wet;

	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	wetuwn bwightness & 0xff;
}

static const stwuct backwight_ops tm5p5_nt35596_bw_ops = {
	.update_status = tm5p5_nt35596_bw_update_status,
	.get_bwightness = tm5p5_nt35596_bw_get_bwightness,
};

static stwuct backwight_device *
tm5p5_nt35596_cweate_backwight(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	const stwuct backwight_pwopewties pwops = {
		.type = BACKWIGHT_WAW,
		.bwightness = 255,
		.max_bwightness = 255,
	};

	wetuwn devm_backwight_device_wegistew(dev, dev_name(dev), dev, dsi,
					      &tm5p5_nt35596_bw_ops, &pwops);
}

static int tm5p5_nt35596_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct tm5p5_nt35596 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->suppwies[0].suppwy = "vdd";
	ctx->suppwies[1].suppwy = "vddio";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(ctx->suppwies),
				      ctx->suppwies);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to get weguwatows: %d\n", wet);
		wetuwn wet;
	}

	ctx->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->weset_gpio)) {
		wet = PTW_EWW(ctx->weset_gpio);
		dev_eww(dev, "Faiwed to get weset-gpios: %d\n", wet);
		wetuwn wet;
	}

	ctx->dsi = dsi;
	mipi_dsi_set_dwvdata(dsi, ctx);

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
			  MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CWOCK_NON_CONTINUOUS | MIPI_DSI_MODE_WPM;

	dwm_panew_init(&ctx->panew, dev, &tm5p5_nt35596_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	ctx->panew.backwight = tm5p5_nt35596_cweate_backwight(dsi);
	if (IS_EWW(ctx->panew.backwight)) {
		wet = PTW_EWW(ctx->panew.backwight);
		dev_eww(dev, "Faiwed to cweate backwight: %d\n", wet);
		wetuwn wet;
	}

	dwm_panew_add(&ctx->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to attach to DSI host: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void tm5p5_nt35596_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct tm5p5_nt35596 *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev,
			"Faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id tm5p5_nt35596_of_match[] = {
	{ .compatibwe = "asus,z00t-tm5p5-n35596" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, tm5p5_nt35596_of_match);

static stwuct mipi_dsi_dwivew tm5p5_nt35596_dwivew = {
	.pwobe = tm5p5_nt35596_pwobe,
	.wemove = tm5p5_nt35596_wemove,
	.dwivew = {
		.name = "panew-tm5p5-nt35596",
		.of_match_tabwe = tm5p5_nt35596_of_match,
	},
};
moduwe_mipi_dsi_dwivew(tm5p5_nt35596_dwivew);

MODUWE_AUTHOW("Konwad Dybcio <konwadybcio@gmaiw.com>");
MODUWE_DESCWIPTION("DWM dwivew fow tm5p5 nt35596 1080p video mode dsi panew");
MODUWE_WICENSE("GPW v2");
