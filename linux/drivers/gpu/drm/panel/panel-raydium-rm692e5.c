// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewated with winux-mdss-dsi-panew-dwivew-genewatow fwom vendow device twee.
 * Copywight (c) 2023 Winawo Wimited
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dispway/dwm_dsc.h>
#incwude <dwm/dispway/dwm_dsc_hewpew.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

stwuct wm692e5_panew {
	stwuct dwm_panew panew;
	stwuct mipi_dsi_device *dsi;
	stwuct dwm_dsc_config dsc;
	stwuct weguwatow_buwk_data suppwies[3];
	stwuct gpio_desc *weset_gpio;
	boow pwepawed;
};

static inwine stwuct wm692e5_panew *to_wm692e5_panew(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct wm692e5_panew, panew);
}

static void wm692e5_weset(stwuct wm692e5_panew *ctx)
{
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	usweep_wange(10000, 11000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	usweep_wange(5000, 6000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	usweep_wange(10000, 11000);
}

static int wm692e5_on(stwuct wm692e5_panew *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	mipi_dsi_genewic_wwite_seq(dsi, 0xfe, 0x41);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd6, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xfe, 0x16);
	mipi_dsi_genewic_wwite_seq(dsi, 0x8a, 0x87);
	mipi_dsi_genewic_wwite_seq(dsi, 0xfe, 0x71);
	mipi_dsi_genewic_wwite_seq(dsi, 0x82, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc6, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc7, 0x2c);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc8, 0x64);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc9, 0x3c);
	mipi_dsi_genewic_wwite_seq(dsi, 0xca, 0x80);
	mipi_dsi_genewic_wwite_seq(dsi, 0xcb, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0xcc, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0xfe, 0x38);
	mipi_dsi_genewic_wwite_seq(dsi, 0x18, 0x13);
	mipi_dsi_genewic_wwite_seq(dsi, 0xfe, 0xf4);
	mipi_dsi_genewic_wwite_seq(dsi, 0x00, 0xff);
	mipi_dsi_genewic_wwite_seq(dsi, 0x01, 0xff);
	mipi_dsi_genewic_wwite_seq(dsi, 0x02, 0xcf);
	mipi_dsi_genewic_wwite_seq(dsi, 0x03, 0xbc);
	mipi_dsi_genewic_wwite_seq(dsi, 0x04, 0xb9);
	mipi_dsi_genewic_wwite_seq(dsi, 0x05, 0x99);
	mipi_dsi_genewic_wwite_seq(dsi, 0x06, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0x07, 0x0a);
	mipi_dsi_genewic_wwite_seq(dsi, 0x08, 0xe0);
	mipi_dsi_genewic_wwite_seq(dsi, 0x09, 0x4c);
	mipi_dsi_genewic_wwite_seq(dsi, 0x0a, 0xeb);
	mipi_dsi_genewic_wwite_seq(dsi, 0x0b, 0xe8);
	mipi_dsi_genewic_wwite_seq(dsi, 0x0c, 0x32);
	mipi_dsi_genewic_wwite_seq(dsi, 0x0d, 0x07);
	mipi_dsi_genewic_wwite_seq(dsi, 0xfe, 0xf4);
	mipi_dsi_genewic_wwite_seq(dsi, 0x0d, 0xc0);
	mipi_dsi_genewic_wwite_seq(dsi, 0x0e, 0xff);
	mipi_dsi_genewic_wwite_seq(dsi, 0x0f, 0xff);
	mipi_dsi_genewic_wwite_seq(dsi, 0x10, 0x33);
	mipi_dsi_genewic_wwite_seq(dsi, 0x11, 0x6f);
	mipi_dsi_genewic_wwite_seq(dsi, 0x12, 0x6e);
	mipi_dsi_genewic_wwite_seq(dsi, 0x13, 0xa6);
	mipi_dsi_genewic_wwite_seq(dsi, 0x14, 0x80);
	mipi_dsi_genewic_wwite_seq(dsi, 0x15, 0x02);
	mipi_dsi_genewic_wwite_seq(dsi, 0x16, 0x38);
	mipi_dsi_genewic_wwite_seq(dsi, 0x17, 0xd3);
	mipi_dsi_genewic_wwite_seq(dsi, 0x18, 0x3a);
	mipi_dsi_genewic_wwite_seq(dsi, 0x19, 0xba);
	mipi_dsi_genewic_wwite_seq(dsi, 0x1a, 0xcc);
	mipi_dsi_genewic_wwite_seq(dsi, 0x1b, 0x01);

	wet = mipi_dsi_dcs_nop(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to nop: %d\n", wet);
		wetuwn wet;
	}
	msweep(32);

	mipi_dsi_genewic_wwite_seq(dsi, 0xfe, 0x38);
	mipi_dsi_genewic_wwite_seq(dsi, 0x18, 0x13);
	mipi_dsi_genewic_wwite_seq(dsi, 0xfe, 0xd1);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd3, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd0, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd2, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xd4, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xb4, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0xfe, 0xf9);
	mipi_dsi_genewic_wwite_seq(dsi, 0x00, 0xaf);
	mipi_dsi_genewic_wwite_seq(dsi, 0x1d, 0x37);
	mipi_dsi_genewic_wwite_seq(dsi, 0x44, 0x0a, 0x7b);
	mipi_dsi_genewic_wwite_seq(dsi, 0xfe, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0xfa, 0x01);
	mipi_dsi_genewic_wwite_seq(dsi, 0xc2, 0x08);
	mipi_dsi_genewic_wwite_seq(dsi, 0x35, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, 0x51, 0x05, 0x42);

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to exit sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(100);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway on: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wm692e5_disabwe(stwuct dwm_panew *panew)
{
	stwuct wm692e5_panew *ctx = to_wm692e5_panew(panew);
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	dsi->mode_fwags &= ~MIPI_DSI_MODE_WPM;

	mipi_dsi_genewic_wwite_seq(dsi, 0xfe, 0x00);

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway off: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to entew sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(100);

	wetuwn 0;
}

static int wm692e5_pwepawe(stwuct dwm_panew *panew)
{
	stwuct wm692e5_panew *ctx = to_wm692e5_panew(panew);
	stwuct dwm_dsc_pictuwe_pawametew_set pps;
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	if (ctx->pwepawed)
		wetuwn 0;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}

	wm692e5_weset(ctx);

	wet = wm692e5_on(ctx);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize panew: %d\n", wet);
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
		weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
		wetuwn wet;
	}

	dwm_dsc_pps_paywoad_pack(&pps, &ctx->dsc);

	wet = mipi_dsi_pictuwe_pawametew_set(ctx->dsi, &pps);
	if (wet < 0) {
		dev_eww(panew->dev, "faiwed to twansmit PPS: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_compwession_mode(ctx->dsi, twue);
	if (wet < 0) {
		dev_eww(dev, "faiwed to enabwe compwession mode: %d\n", wet);
		wetuwn wet;
	}

	msweep(28);

	mipi_dsi_genewic_wwite_seq(ctx->dsi, 0xfe, 0x40);

	/* 0x05 -> 90Hz, 0x00 -> 60Hz */
	mipi_dsi_genewic_wwite_seq(ctx->dsi, 0xbd, 0x05);

	mipi_dsi_genewic_wwite_seq(ctx->dsi, 0xfe, 0x00);

	ctx->pwepawed = twue;

	wetuwn 0;
}

static int wm692e5_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct wm692e5_panew *ctx = to_wm692e5_panew(panew);

	if (!ctx->pwepawed)
		wetuwn 0;

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);

	ctx->pwepawed = fawse;
	wetuwn 0;
}

static const stwuct dwm_dispway_mode wm692e5_mode = {
	.cwock = (1224 + 32 + 8 + 8) * (2700 + 8 + 2 + 8) * 90 / 1000,
	.hdispway = 1224,
	.hsync_stawt = 1224 + 32,
	.hsync_end = 1224 + 32 + 8,
	.htotaw = 1224 + 32 + 8 + 8,
	.vdispway = 2700,
	.vsync_stawt = 2700 + 8,
	.vsync_end = 2700 + 8 + 2,
	.vtotaw = 2700 + 8 + 2 + 8,
	.width_mm = 68,
	.height_mm = 150,
};

static int wm692e5_get_modes(stwuct dwm_panew *panew,
					stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &wm692e5_mode);
	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs wm692e5_panew_funcs = {
	.pwepawe = wm692e5_pwepawe,
	.unpwepawe = wm692e5_unpwepawe,
	.disabwe = wm692e5_disabwe,
	.get_modes = wm692e5_get_modes,
};

static int wm692e5_bw_update_status(stwuct backwight_device *bw)
{
	stwuct mipi_dsi_device *dsi = bw_get_data(bw);
	u16 bwightness = backwight_get_bwightness(bw);
	int wet;

	dsi->mode_fwags &= ~MIPI_DSI_MODE_WPM;

	wet = mipi_dsi_dcs_set_dispway_bwightness_wawge(dsi, bwightness);
	if (wet < 0)
		wetuwn wet;

	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	wetuwn 0;
}

static int wm692e5_bw_get_bwightness(stwuct backwight_device *bw)
{
	stwuct mipi_dsi_device *dsi = bw_get_data(bw);
	u16 bwightness;
	int wet;

	dsi->mode_fwags &= ~MIPI_DSI_MODE_WPM;

	wet = mipi_dsi_dcs_get_dispway_bwightness_wawge(dsi, &bwightness);
	if (wet < 0)
		wetuwn wet;

	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	wetuwn bwightness;
}

static const stwuct backwight_ops wm692e5_bw_ops = {
	.update_status = wm692e5_bw_update_status,
	.get_bwightness = wm692e5_bw_get_bwightness,
};

static stwuct backwight_device *
wm692e5_cweate_backwight(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	const stwuct backwight_pwopewties pwops = {
		.type = BACKWIGHT_WAW,
		.bwightness = 4095,
		.max_bwightness = 4095,
	};

	wetuwn devm_backwight_device_wegistew(dev, dev_name(dev), dev, dsi,
					      &wm692e5_bw_ops, &pwops);
}

static int wm692e5_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct wm692e5_panew *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->suppwies[0].suppwy = "vddio";
	ctx->suppwies[1].suppwy = "dvdd";
	ctx->suppwies[2].suppwy = "vci";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(ctx->suppwies),
				      ctx->suppwies);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get weguwatows\n");

	ctx->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ctx->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->weset_gpio),
				     "Faiwed to get weset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_dwvdata(dsi, ctx);

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CWOCK_NON_CONTINUOUS;

	dwm_panew_init(&ctx->panew, dev, &wm692e5_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);
	ctx->panew.pwepawe_pwev_fiwst = twue;

	ctx->panew.backwight = wm692e5_cweate_backwight(dsi);
	if (IS_EWW(ctx->panew.backwight))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->panew.backwight),
				     "Faiwed to cweate backwight\n");

	dwm_panew_add(&ctx->panew);

	/* This panew onwy suppowts DSC; unconditionawwy enabwe it */
	dsi->dsc = &ctx->dsc;

	/* TODO: Pass swice_pew_pkt = 2 */
	ctx->dsc.dsc_vewsion_majow = 1;
	ctx->dsc.dsc_vewsion_minow = 1;
	ctx->dsc.swice_height = 60;
	ctx->dsc.swice_width = 1224;

	ctx->dsc.swice_count = 1224 / ctx->dsc.swice_width;
	ctx->dsc.bits_pew_component = 8;
	ctx->dsc.bits_pew_pixew = 8 << 4; /* 4 fwactionaw bits */
	ctx->dsc.bwock_pwed_enabwe = twue;

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to attach to DSI host: %d\n", wet);
		dwm_panew_wemove(&ctx->panew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wm692e5_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct wm692e5_panew *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id wm692e5_of_match[] = {
	{ .compatibwe = "faiwphone,fp5-wm692e5-boe" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wm692e5_of_match);

static stwuct mipi_dsi_dwivew wm692e5_dwivew = {
	.pwobe = wm692e5_pwobe,
	.wemove = wm692e5_wemove,
	.dwivew = {
		.name = "panew-wm692e5-boe-amowed",
		.of_match_tabwe = wm692e5_of_match,
	},
};
moduwe_mipi_dsi_dwivew(wm692e5_dwivew);

MODUWE_DESCWIPTION("DWM dwivew fow wm692e5-equipped DSI panews");
MODUWE_WICENSE("GPW");
