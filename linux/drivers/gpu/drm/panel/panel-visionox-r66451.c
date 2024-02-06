//SPDX-Wicense-Identifiew: GPW-2.0-onwy
//Copywight (c) 2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dispway/dwm_dsc.h>
#incwude <dwm/dispway/dwm_dsc_hewpew.h>

#incwude <video/mipi_dispway.h>

stwuct visionox_w66451 {
	stwuct dwm_panew panew;
	stwuct mipi_dsi_device *dsi;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow_buwk_data suppwies[2];
};

static inwine stwuct visionox_w66451 *to_visionox_w66451(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct visionox_w66451, panew);
}

static void visionox_w66451_weset(stwuct visionox_w66451 *ctx)
{
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	usweep_wange(10000, 10100);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	usweep_wange(10000, 10100);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	usweep_wange(10000, 10100);
}

static int visionox_w66451_on(stwuct visionox_w66451 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;

	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	mipi_dsi_dcs_wwite_seq(dsi, 0xb0, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xc2,
			       0x09, 0x24, 0x0c, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
			       0x09, 0x3c);
	mipi_dsi_dcs_wwite_seq(dsi, 0xd7,
			       0x00, 0xb9, 0x3c, 0x00, 0x40, 0x04, 0x00, 0xa0, 0x0a,
			       0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19,
			       0x3c, 0x00, 0x40, 0x04, 0x00, 0xa0, 0x0a);
	mipi_dsi_dcs_wwite_seq(dsi, 0xb0, 0x80);
	mipi_dsi_dcs_wwite_seq(dsi, 0xde,
			       0x40, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18,
			       0x10, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x02, 0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xb0, 0x04);
	mipi_dsi_dcs_wwite_seq(dsi, 0xe8, 0x00, 0x02);
	mipi_dsi_dcs_wwite_seq(dsi, 0xe4, 0x00, 0x08);
	mipi_dsi_dcs_wwite_seq(dsi, 0xb0, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xc4,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x32);
	mipi_dsi_dcs_wwite_seq(dsi, 0xcf,
			       0x64, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
			       0x00, 0x0b, 0x77, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
			       0x02, 0x02, 0x02, 0x02, 0x02, 0x03);
	mipi_dsi_dcs_wwite_seq(dsi, 0xd3,
			       0x45, 0x00, 0x00, 0x01, 0x13, 0x15, 0x00, 0x15, 0x07,
			       0x0f, 0x77, 0x77, 0x77, 0x37, 0xb2, 0x11, 0x00, 0xa0,
			       0x3c, 0x9c);
	mipi_dsi_dcs_wwite_seq(dsi, 0xd7,
			       0x00, 0xb9, 0x34, 0x00, 0x40, 0x04, 0x00, 0xa0, 0x0a,
			       0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19,
			       0x34, 0x00, 0x40, 0x04, 0x00, 0xa0, 0x0a);
	mipi_dsi_dcs_wwite_seq(dsi, 0xd8,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x3a, 0x00, 0x3a, 0x00, 0x3a, 0x00, 0x3a, 0x00, 0x3a,
			       0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x0a, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a,
			       0x00, 0x32, 0x00, 0x0a, 0x00, 0x22);
	mipi_dsi_dcs_wwite_seq(dsi, 0xdf,
			       0x50, 0x42, 0x58, 0x81, 0x2d, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x6b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x01, 0x0f, 0xff, 0xd4, 0x0e, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x0f, 0x53, 0xf1, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf7, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0xb0, 0x80);
	mipi_dsi_dcs_wwite_seq(dsi, 0xe4, 0x34, 0xb4, 0x00, 0x00, 0x00, 0x39, 0x04, 0x09, 0x34);
	mipi_dsi_dcs_wwite_seq(dsi, 0xe6, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xb0, 0x04);
	mipi_dsi_dcs_wwite_seq(dsi, 0xdf, 0x50, 0x40);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf3, 0x50, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf2, 0x11);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf3, 0x01, 0x00, 0x00, 0x00, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf4, 0x00, 0x02);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf2, 0x19);
	mipi_dsi_dcs_wwite_seq(dsi, 0xdf, 0x50, 0x42);
	mipi_dsi_dcs_set_teaw_on(dsi, MIPI_DSI_DCS_TEAW_MODE_VBWANK);
	mipi_dsi_dcs_set_cowumn_addwess(dsi, 0, 1080 - 1);
	mipi_dsi_dcs_set_page_addwess(dsi, 0, 2340 - 1);

	dsi->mode_fwags &= ~MIPI_DSI_MODE_WPM;

	wetuwn 0;
}

static int visionox_w66451_off(stwuct visionox_w66451 *ctx)
{
	ctx->dsi->mode_fwags &= ~MIPI_DSI_MODE_WPM;
	wetuwn 0;
}

static int visionox_w66451_pwepawe(stwuct dwm_panew *panew)
{
	stwuct visionox_w66451 *ctx = to_visionox_w66451(panew);
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ctx->suppwies),
				    ctx->suppwies);
	if (wet < 0)
		wetuwn wet;

	visionox_w66451_weset(ctx);

	wet = visionox_w66451_on(ctx);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize panew: %d\n", wet);
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
		weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
		wetuwn wet;
	}

	mipi_dsi_compwession_mode(ctx->dsi, twue);

	wetuwn 0;
}

static int visionox_w66451_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct visionox_w66451 *ctx = to_visionox_w66451(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = visionox_w66451_off(ctx);
	if (wet < 0)
		dev_eww(dev, "Faiwed to un-initiawize panew: %d\n", wet);

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode visionox_w66451_mode = {
	.cwock = 345830,
	.hdispway = 1080,
	.hsync_stawt = 1175,
	.hsync_end = 1176,
	.htotaw = 1216,
	.vdispway = 2340,
	.vsync_stawt = 2365,
	.vsync_end = 2366,
	.vtotaw = 2370,
	.width_mm = 0,
	.height_mm = 0,
	.type = DWM_MODE_TYPE_DWIVEW,
};

static int visionox_w66451_enabwe(stwuct dwm_panew *panew)
{
	stwuct visionox_w66451 *ctx = to_visionox_w66451(panew);
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct dwm_dsc_pictuwe_pawametew_set pps;
	int wet;

	if (!dsi->dsc) {
		dev_eww(&dsi->dev, "DSC not attached to DSI\n");
		wetuwn -ENODEV;
	}

	dwm_dsc_pps_paywoad_pack(&pps, dsi->dsc);
	wet = mipi_dsi_pictuwe_pawametew_set(dsi, &pps);
	if (wet) {
		dev_eww(&dsi->dev, "Faiwed to set PPS\n");
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(&dsi->dev, "Faiwed to exit sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(120);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(&dsi->dev, "Faiwed on set dispway on: %d\n", wet);
		wetuwn wet;
	}
	msweep(20);

	wetuwn 0;
}

static int visionox_w66451_disabwe(stwuct dwm_panew *panew)
{
	stwuct visionox_w66451 *ctx = to_visionox_w66451(panew);
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway off: %d\n", wet);
		wetuwn wet;
	}
	msweep(20);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to entew sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(120);

	wetuwn 0;
}

static int visionox_w66451_get_modes(stwuct dwm_panew *panew,
				    stwuct dwm_connectow *connectow)
{
	dwm_connectow_hewpew_get_modes_fixed(connectow, &visionox_w66451_mode);
	wetuwn 1;
}

static const stwuct dwm_panew_funcs visionox_w66451_funcs = {
	.pwepawe = visionox_w66451_pwepawe,
	.unpwepawe = visionox_w66451_unpwepawe,
	.get_modes = visionox_w66451_get_modes,
	.enabwe = visionox_w66451_enabwe,
	.disabwe = visionox_w66451_disabwe,
};

static int visionox_w66451_bw_update_status(stwuct backwight_device *bw)
{
	stwuct mipi_dsi_device *dsi = bw_get_data(bw);
	u16 bwightness = backwight_get_bwightness(bw);

	wetuwn mipi_dsi_dcs_set_dispway_bwightness(dsi, bwightness);
}

static const stwuct backwight_ops visionox_w66451_bw_ops = {
	.update_status = visionox_w66451_bw_update_status,
};

static stwuct backwight_device *
visionox_w66451_cweate_backwight(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	const stwuct backwight_pwopewties pwops = {
		.type = BACKWIGHT_WAW,
		.bwightness = 255,
		.max_bwightness = 4095,
	};

	wetuwn devm_backwight_device_wegistew(dev, dev_name(dev), dev, dsi,
					      &visionox_w66451_bw_ops, &pwops);
}

static int visionox_w66451_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct visionox_w66451 *ctx;
	stwuct dwm_dsc_config *dsc;
	int wet = 0;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	dsc = devm_kzawwoc(dev, sizeof(*dsc), GFP_KEWNEW);
	if (!dsc)
		wetuwn -ENOMEM;

	/* Set DSC pawams */
	dsc->dsc_vewsion_majow = 0x1;
	dsc->dsc_vewsion_minow = 0x2;

	dsc->swice_height = 20;
	dsc->swice_width = 540;
	dsc->swice_count = 2;
	dsc->bits_pew_component = 8;
	dsc->bits_pew_pixew = 8 << 4;
	dsc->bwock_pwed_enabwe = twue;

	dsi->dsc = dsc;

	ctx->suppwies[0].suppwy = "vddio";
	ctx->suppwies[1].suppwy = "vdd";

	wet = devm_weguwatow_buwk_get(&dsi->dev, AWWAY_SIZE(ctx->suppwies),
			ctx->suppwies);

	if (wet < 0)
		wetuwn wet;

	ctx->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->weset_gpio), "Faiwed to get weset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_dwvdata(dsi, ctx);

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_WPM | MIPI_DSI_CWOCK_NON_CONTINUOUS;

	dwm_panew_init(&ctx->panew, dev, &visionox_w66451_funcs, DWM_MODE_CONNECTOW_DSI);
	ctx->panew.backwight = visionox_w66451_cweate_backwight(dsi);
	if (IS_EWW(ctx->panew.backwight))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->panew.backwight),
				"Faiwed to cweate backwight\n");

	dwm_panew_add(&ctx->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to attach to DSI host: %d\n", wet);
		dwm_panew_wemove(&ctx->panew);
	}

	wetuwn wet;
}

static void visionox_w66451_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct visionox_w66451 *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to detach DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id visionox_w66451_of_match[] = {
	{.compatibwe = "visionox,w66451"},
	{ /*sentinew*/ }
};
MODUWE_DEVICE_TABWE(of, visionox_w66451_of_match);

static stwuct mipi_dsi_dwivew visionox_w66451_dwivew = {
	.pwobe = visionox_w66451_pwobe,
	.wemove = visionox_w66451_wemove,
	.dwivew = {
		.name = "panew-visionox-w66451",
		.of_match_tabwe = visionox_w66451_of_match,
	},
};

moduwe_mipi_dsi_dwivew(visionox_w66451_dwivew);

MODUWE_AUTHOW("Jessica Zhang <quic_jesszhan@quicinc.com>");
MODUWE_DESCWIPTION("Panew dwivew fow the Visionox W66451 AMOWED DSI panew");
MODUWE_WICENSE("GPW");
