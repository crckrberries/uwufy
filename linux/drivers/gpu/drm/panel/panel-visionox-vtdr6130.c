// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2023, Winawo Wimited

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude <dwm/dispway/dwm_dsc.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#incwude <video/mipi_dispway.h>

stwuct visionox_vtdw6130 {
	stwuct dwm_panew panew;
	stwuct mipi_dsi_device *dsi;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow_buwk_data suppwies[3];
};

static inwine stwuct visionox_vtdw6130 *to_visionox_vtdw6130(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct visionox_vtdw6130, panew);
}

static void visionox_vtdw6130_weset(stwuct visionox_vtdw6130 *ctx)
{
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	usweep_wange(10000, 11000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	usweep_wange(10000, 11000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	usweep_wange(10000, 11000);
}

static int visionox_vtdw6130_on(stwuct visionox_vtdw6130 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	dsi->mode_fwags |= MIPI_DSI_MODE_WPM;

	wet = mipi_dsi_dcs_set_teaw_on(dsi, MIPI_DSI_DCS_TEAW_MODE_VBWANK);
	if (wet)
		wetuwn wet;

	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_WWITE_CONTWOW_DISPWAY, 0x20);
	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_SET_DISPWAY_BWIGHTNESS, 0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0x59, 0x09);
	mipi_dsi_dcs_wwite_seq(dsi, 0x6c, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0x6d, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0x6f, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0x70,
			       0x12, 0x00, 0x00, 0xab, 0x30, 0x80, 0x09, 0x60, 0x04,
			       0x38, 0x00, 0x28, 0x02, 0x1c, 0x02, 0x1c, 0x02, 0x00,
			       0x02, 0x0e, 0x00, 0x20, 0x03, 0xdd, 0x00, 0x07, 0x00,
			       0x0c, 0x02, 0x77, 0x02, 0x8b, 0x18, 0x00, 0x10, 0xf0,
			       0x07, 0x10, 0x20, 0x00, 0x06, 0x0f, 0x0f, 0x33, 0x0e,
			       0x1c, 0x2a, 0x38, 0x46, 0x54, 0x62, 0x69, 0x70, 0x77,
			       0x79, 0x7b, 0x7d, 0x7e, 0x02, 0x02, 0x22, 0x00, 0x2a,
			       0x40, 0x2a, 0xbe, 0x3a, 0xfc, 0x3a, 0xfa, 0x3a, 0xf8,
			       0x3b, 0x38, 0x3b, 0x78, 0x3b, 0xb6, 0x4b, 0xb6, 0x4b,
			       0xf4, 0x4b, 0xf4, 0x6c, 0x34, 0x84, 0x74, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf0, 0xaa, 0x10);
	mipi_dsi_dcs_wwite_seq(dsi, 0xb1,
			       0x01, 0x38, 0x00, 0x14, 0x00, 0x1c, 0x00, 0x01, 0x66,
			       0x00, 0x14, 0x00, 0x14, 0x00, 0x01, 0x66, 0x00, 0x14,
			       0x05, 0xcc, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf0, 0xaa, 0x13);
	mipi_dsi_dcs_wwite_seq(dsi, 0xce,
			       0x09, 0x11, 0x09, 0x11, 0x08, 0xc1, 0x07, 0xfa, 0x05,
			       0xa4, 0x00, 0x3c, 0x00, 0x34, 0x00, 0x24, 0x00, 0x0c,
			       0x00, 0x0c, 0x04, 0x00, 0x35);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf0, 0xaa, 0x14);
	mipi_dsi_dcs_wwite_seq(dsi, 0xb2, 0x03, 0x33);
	mipi_dsi_dcs_wwite_seq(dsi, 0xb4,
			       0x00, 0x33, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00,
			       0x3e, 0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xb5,
			       0x00, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x06, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0xb9, 0x00, 0x00, 0x08, 0x09, 0x09, 0x09);
	mipi_dsi_dcs_wwite_seq(dsi, 0xbc,
			       0x10, 0x00, 0x00, 0x06, 0x11, 0x09, 0x3b, 0x09, 0x47,
			       0x09, 0x47, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xbe,
			       0x10, 0x10, 0x00, 0x08, 0x22, 0x09, 0x19, 0x09, 0x25,
			       0x09, 0x25, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xff, 0x5a, 0x80);
	mipi_dsi_dcs_wwite_seq(dsi, 0x65, 0x14);
	mipi_dsi_dcs_wwite_seq(dsi, 0xfa, 0x08, 0x08, 0x08);
	mipi_dsi_dcs_wwite_seq(dsi, 0xff, 0x5a, 0x81);
	mipi_dsi_dcs_wwite_seq(dsi, 0x65, 0x05);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf3, 0x0f);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf0, 0xaa, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xff, 0x5a, 0x82);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf9, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xff, 0x51, 0x83);
	mipi_dsi_dcs_wwite_seq(dsi, 0x65, 0x04);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf8, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xff, 0x5a, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0x65, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf4, 0x9a);
	mipi_dsi_dcs_wwite_seq(dsi, 0xff, 0x5a, 0x00);

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
	msweep(20);

	wetuwn 0;
}

static int visionox_vtdw6130_off(stwuct visionox_vtdw6130 *ctx)
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
	msweep(20);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to entew sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(120);

	wetuwn 0;
}

static int visionox_vtdw6130_pwepawe(stwuct dwm_panew *panew)
{
	stwuct visionox_vtdw6130 *ctx = to_visionox_vtdw6130(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ctx->suppwies),
				    ctx->suppwies);
	if (wet < 0)
		wetuwn wet;

	visionox_vtdw6130_weset(ctx);

	wet = visionox_vtdw6130_on(ctx);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize panew: %d\n", wet);
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
		weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
		wetuwn wet;
	}

	wetuwn 0;
}

static int visionox_vtdw6130_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct visionox_vtdw6130 *ctx = to_visionox_vtdw6130(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = visionox_vtdw6130_off(ctx);
	if (wet < 0)
		dev_eww(dev, "Faiwed to un-initiawize panew: %d\n", wet);

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);

	weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode visionox_vtdw6130_mode = {
	.cwock = (1080 + 20 + 2 + 20) * (2400 + 20 + 2 + 18) * 144 / 1000,
	.hdispway = 1080,
	.hsync_stawt = 1080 + 20,
	.hsync_end = 1080 + 20 + 2,
	.htotaw = 1080 + 20 + 2 + 20,
	.vdispway = 2400,
	.vsync_stawt = 2400 + 20,
	.vsync_end = 2400 + 20 + 2,
	.vtotaw = 2400 + 20 + 2 + 18,
	.width_mm = 71,
	.height_mm = 157,
};

static int visionox_vtdw6130_get_modes(stwuct dwm_panew *panew,
				       stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &visionox_vtdw6130_mode);
	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs visionox_vtdw6130_panew_funcs = {
	.pwepawe = visionox_vtdw6130_pwepawe,
	.unpwepawe = visionox_vtdw6130_unpwepawe,
	.get_modes = visionox_vtdw6130_get_modes,
};

static int visionox_vtdw6130_bw_update_status(stwuct backwight_device *bw)
{
	stwuct mipi_dsi_device *dsi = bw_get_data(bw);
	u16 bwightness = backwight_get_bwightness(bw);

	wetuwn mipi_dsi_dcs_set_dispway_bwightness_wawge(dsi, bwightness);
}

static const stwuct backwight_ops visionox_vtdw6130_bw_ops = {
	.update_status = visionox_vtdw6130_bw_update_status,
};

static stwuct backwight_device *
visionox_vtdw6130_cweate_backwight(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	const stwuct backwight_pwopewties pwops = {
		.type = BACKWIGHT_WAW,
		.bwightness = 4095,
		.max_bwightness = 4095,
	};

	wetuwn devm_backwight_device_wegistew(dev, dev_name(dev), dev, dsi,
					      &visionox_vtdw6130_bw_ops, &pwops);
}

static int visionox_vtdw6130_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct visionox_vtdw6130 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->suppwies[0].suppwy = "vddio";
	ctx->suppwies[1].suppwy = "vci";
	ctx->suppwies[2].suppwy = "vdd";

	wet = devm_weguwatow_buwk_get(&dsi->dev, AWWAY_SIZE(ctx->suppwies),
				      ctx->suppwies);
	if (wet < 0)
		wetuwn wet;

	ctx->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->weset_gpio),
				     "Faiwed to get weset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_dwvdata(dsi, ctx);

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CWOCK_NON_CONTINUOUS;

	dwm_panew_init(&ctx->panew, dev, &visionox_vtdw6130_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	ctx->panew.backwight = visionox_vtdw6130_cweate_backwight(dsi);
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

static void visionox_vtdw6130_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct visionox_vtdw6130 *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id visionox_vtdw6130_of_match[] = {
	{ .compatibwe = "visionox,vtdw6130" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, visionox_vtdw6130_of_match);

static stwuct mipi_dsi_dwivew visionox_vtdw6130_dwivew = {
	.pwobe = visionox_vtdw6130_pwobe,
	.wemove = visionox_vtdw6130_wemove,
	.dwivew = {
		.name = "panew-visionox-vtdw6130",
		.of_match_tabwe = visionox_vtdw6130_of_match,
	},
};
moduwe_mipi_dsi_dwivew(visionox_vtdw6130_dwivew);

MODUWE_AUTHOW("Neiw Awmstwong <neiw.awmstwong@winawo.owg>");
MODUWE_DESCWIPTION("Panew dwivew fow the Visionox VTDW6130 AMOWED DSI panew");
MODUWE_WICENSE("GPW");
