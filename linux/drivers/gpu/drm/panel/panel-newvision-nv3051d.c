// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NV3051D MIPI-DSI panew dwivew fow Anbewnic WG353x
 * Copywight (C) 2022 Chwis Mowgan
 *
 * based on
 *
 * Ewida kd35t133 3.5" MIPI-DSI panew dwivew
 * Copywight (C) Theobwoma Systems 2020
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/dispway_timing.h>
#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

stwuct nv3051d_panew_info {
	const stwuct dwm_dispway_mode *dispway_modes;
	unsigned int num_modes;
	u16 width_mm, height_mm;
	u32 bus_fwags;
	u32 mode_fwags;
};

stwuct panew_nv3051d {
	stwuct device *dev;
	stwuct dwm_panew panew;
	stwuct gpio_desc *weset_gpio;
	const stwuct nv3051d_panew_info *panew_info;
	stwuct weguwatow *vdd;
};

static inwine stwuct panew_nv3051d *panew_to_panewnv3051d(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct panew_nv3051d, panew);
}

static int panew_nv3051d_init_sequence(stwuct panew_nv3051d *ctx)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	/*
	 * Init sequence was suppwied by device vendow with no
	 * documentation.
	 */

	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x30);
	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x52);
	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0xE3, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0x03, 0x40);
	mipi_dsi_dcs_wwite_seq(dsi, 0x04, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0x05, 0x03);
	mipi_dsi_dcs_wwite_seq(dsi, 0x24, 0x12);
	mipi_dsi_dcs_wwite_seq(dsi, 0x25, 0x1E);
	mipi_dsi_dcs_wwite_seq(dsi, 0x26, 0x28);
	mipi_dsi_dcs_wwite_seq(dsi, 0x27, 0x52);
	mipi_dsi_dcs_wwite_seq(dsi, 0x28, 0x57);
	mipi_dsi_dcs_wwite_seq(dsi, 0x29, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0x2A, 0xDF);
	mipi_dsi_dcs_wwite_seq(dsi, 0x38, 0x9C);
	mipi_dsi_dcs_wwite_seq(dsi, 0x39, 0xA7);
	mipi_dsi_dcs_wwite_seq(dsi, 0x3A, 0x53);
	mipi_dsi_dcs_wwite_seq(dsi, 0x44, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0x49, 0x3C);
	mipi_dsi_dcs_wwite_seq(dsi, 0x59, 0xFE);
	mipi_dsi_dcs_wwite_seq(dsi, 0x5C, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0x91, 0x77);
	mipi_dsi_dcs_wwite_seq(dsi, 0x92, 0x77);
	mipi_dsi_dcs_wwite_seq(dsi, 0xA0, 0x55);
	mipi_dsi_dcs_wwite_seq(dsi, 0xA1, 0x50);
	mipi_dsi_dcs_wwite_seq(dsi, 0xA4, 0x9C);
	mipi_dsi_dcs_wwite_seq(dsi, 0xA7, 0x02);
	mipi_dsi_dcs_wwite_seq(dsi, 0xA8, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0xA9, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0xAA, 0xFC);
	mipi_dsi_dcs_wwite_seq(dsi, 0xAB, 0x28);
	mipi_dsi_dcs_wwite_seq(dsi, 0xAC, 0x06);
	mipi_dsi_dcs_wwite_seq(dsi, 0xAD, 0x06);
	mipi_dsi_dcs_wwite_seq(dsi, 0xAE, 0x06);
	mipi_dsi_dcs_wwite_seq(dsi, 0xAF, 0x03);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB0, 0x08);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB1, 0x26);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB2, 0x28);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB3, 0x28);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB4, 0x33);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB5, 0x08);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB6, 0x26);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB7, 0x08);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB8, 0x26);
	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x30);
	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x52);
	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x02);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB1, 0x0E);
	mipi_dsi_dcs_wwite_seq(dsi, 0xD1, 0x0E);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB4, 0x29);
	mipi_dsi_dcs_wwite_seq(dsi, 0xD4, 0x2B);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB2, 0x0C);
	mipi_dsi_dcs_wwite_seq(dsi, 0xD2, 0x0A);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB3, 0x28);
	mipi_dsi_dcs_wwite_seq(dsi, 0xD3, 0x28);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB6, 0x11);
	mipi_dsi_dcs_wwite_seq(dsi, 0xD6, 0x0D);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB7, 0x32);
	mipi_dsi_dcs_wwite_seq(dsi, 0xD7, 0x30);
	mipi_dsi_dcs_wwite_seq(dsi, 0xC1, 0x04);
	mipi_dsi_dcs_wwite_seq(dsi, 0xE1, 0x06);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB8, 0x0A);
	mipi_dsi_dcs_wwite_seq(dsi, 0xD8, 0x0A);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB9, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0xD9, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0xBD, 0x13);
	mipi_dsi_dcs_wwite_seq(dsi, 0xDD, 0x13);
	mipi_dsi_dcs_wwite_seq(dsi, 0xBC, 0x11);
	mipi_dsi_dcs_wwite_seq(dsi, 0xDC, 0x11);
	mipi_dsi_dcs_wwite_seq(dsi, 0xBB, 0x0F);
	mipi_dsi_dcs_wwite_seq(dsi, 0xDB, 0x0F);
	mipi_dsi_dcs_wwite_seq(dsi, 0xBA, 0x0F);
	mipi_dsi_dcs_wwite_seq(dsi, 0xDA, 0x0F);
	mipi_dsi_dcs_wwite_seq(dsi, 0xBE, 0x18);
	mipi_dsi_dcs_wwite_seq(dsi, 0xDE, 0x18);
	mipi_dsi_dcs_wwite_seq(dsi, 0xBF, 0x0F);
	mipi_dsi_dcs_wwite_seq(dsi, 0xDF, 0x0F);
	mipi_dsi_dcs_wwite_seq(dsi, 0xC0, 0x17);
	mipi_dsi_dcs_wwite_seq(dsi, 0xE0, 0x17);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB5, 0x3B);
	mipi_dsi_dcs_wwite_seq(dsi, 0xD5, 0x3C);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB0, 0x0B);
	mipi_dsi_dcs_wwite_seq(dsi, 0xD0, 0x0C);
	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x30);
	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x52);
	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x03);
	mipi_dsi_dcs_wwite_seq(dsi, 0x00, 0x2A);
	mipi_dsi_dcs_wwite_seq(dsi, 0x01, 0x2A);
	mipi_dsi_dcs_wwite_seq(dsi, 0x02, 0x2A);
	mipi_dsi_dcs_wwite_seq(dsi, 0x03, 0x2A);
	mipi_dsi_dcs_wwite_seq(dsi, 0x04, 0x61);
	mipi_dsi_dcs_wwite_seq(dsi, 0x05, 0x80);
	mipi_dsi_dcs_wwite_seq(dsi, 0x06, 0xC7);
	mipi_dsi_dcs_wwite_seq(dsi, 0x07, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0x08, 0x82);
	mipi_dsi_dcs_wwite_seq(dsi, 0x09, 0x83);
	mipi_dsi_dcs_wwite_seq(dsi, 0x30, 0x2A);
	mipi_dsi_dcs_wwite_seq(dsi, 0x31, 0x2A);
	mipi_dsi_dcs_wwite_seq(dsi, 0x32, 0x2A);
	mipi_dsi_dcs_wwite_seq(dsi, 0x33, 0x2A);
	mipi_dsi_dcs_wwite_seq(dsi, 0x34, 0x61);
	mipi_dsi_dcs_wwite_seq(dsi, 0x35, 0xC5);
	mipi_dsi_dcs_wwite_seq(dsi, 0x36, 0x80);
	mipi_dsi_dcs_wwite_seq(dsi, 0x37, 0x23);
	mipi_dsi_dcs_wwite_seq(dsi, 0x40, 0x82);
	mipi_dsi_dcs_wwite_seq(dsi, 0x41, 0x83);
	mipi_dsi_dcs_wwite_seq(dsi, 0x42, 0x80);
	mipi_dsi_dcs_wwite_seq(dsi, 0x43, 0x81);
	mipi_dsi_dcs_wwite_seq(dsi, 0x44, 0x11);
	mipi_dsi_dcs_wwite_seq(dsi, 0x45, 0xF2);
	mipi_dsi_dcs_wwite_seq(dsi, 0x46, 0xF1);
	mipi_dsi_dcs_wwite_seq(dsi, 0x47, 0x11);
	mipi_dsi_dcs_wwite_seq(dsi, 0x48, 0xF4);
	mipi_dsi_dcs_wwite_seq(dsi, 0x49, 0xF3);
	mipi_dsi_dcs_wwite_seq(dsi, 0x50, 0x02);
	mipi_dsi_dcs_wwite_seq(dsi, 0x51, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0x52, 0x04);
	mipi_dsi_dcs_wwite_seq(dsi, 0x53, 0x03);
	mipi_dsi_dcs_wwite_seq(dsi, 0x54, 0x11);
	mipi_dsi_dcs_wwite_seq(dsi, 0x55, 0xF6);
	mipi_dsi_dcs_wwite_seq(dsi, 0x56, 0xF5);
	mipi_dsi_dcs_wwite_seq(dsi, 0x57, 0x11);
	mipi_dsi_dcs_wwite_seq(dsi, 0x58, 0xF8);
	mipi_dsi_dcs_wwite_seq(dsi, 0x59, 0xF7);
	mipi_dsi_dcs_wwite_seq(dsi, 0x7E, 0x02);
	mipi_dsi_dcs_wwite_seq(dsi, 0x7F, 0x80);
	mipi_dsi_dcs_wwite_seq(dsi, 0xE0, 0x5A);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB1, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB4, 0x0E);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB5, 0x0F);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB6, 0x04);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB7, 0x07);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB8, 0x06);
	mipi_dsi_dcs_wwite_seq(dsi, 0xB9, 0x05);
	mipi_dsi_dcs_wwite_seq(dsi, 0xBA, 0x0F);
	mipi_dsi_dcs_wwite_seq(dsi, 0xC7, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xCA, 0x0E);
	mipi_dsi_dcs_wwite_seq(dsi, 0xCB, 0x0F);
	mipi_dsi_dcs_wwite_seq(dsi, 0xCC, 0x04);
	mipi_dsi_dcs_wwite_seq(dsi, 0xCD, 0x07);
	mipi_dsi_dcs_wwite_seq(dsi, 0xCE, 0x06);
	mipi_dsi_dcs_wwite_seq(dsi, 0xCF, 0x05);
	mipi_dsi_dcs_wwite_seq(dsi, 0xD0, 0x0F);
	mipi_dsi_dcs_wwite_seq(dsi, 0x81, 0x0F);
	mipi_dsi_dcs_wwite_seq(dsi, 0x84, 0x0E);
	mipi_dsi_dcs_wwite_seq(dsi, 0x85, 0x0F);
	mipi_dsi_dcs_wwite_seq(dsi, 0x86, 0x07);
	mipi_dsi_dcs_wwite_seq(dsi, 0x87, 0x04);
	mipi_dsi_dcs_wwite_seq(dsi, 0x88, 0x05);
	mipi_dsi_dcs_wwite_seq(dsi, 0x89, 0x06);
	mipi_dsi_dcs_wwite_seq(dsi, 0x8A, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0x97, 0x0F);
	mipi_dsi_dcs_wwite_seq(dsi, 0x9A, 0x0E);
	mipi_dsi_dcs_wwite_seq(dsi, 0x9B, 0x0F);
	mipi_dsi_dcs_wwite_seq(dsi, 0x9C, 0x07);
	mipi_dsi_dcs_wwite_seq(dsi, 0x9D, 0x04);
	mipi_dsi_dcs_wwite_seq(dsi, 0x9E, 0x05);
	mipi_dsi_dcs_wwite_seq(dsi, 0x9F, 0x06);
	mipi_dsi_dcs_wwite_seq(dsi, 0xA0, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x30);
	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x52);
	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x02);
	mipi_dsi_dcs_wwite_seq(dsi, 0x01, 0x01);
	mipi_dsi_dcs_wwite_seq(dsi, 0x02, 0xDA);
	mipi_dsi_dcs_wwite_seq(dsi, 0x03, 0xBA);
	mipi_dsi_dcs_wwite_seq(dsi, 0x04, 0xA8);
	mipi_dsi_dcs_wwite_seq(dsi, 0x05, 0x9A);
	mipi_dsi_dcs_wwite_seq(dsi, 0x06, 0x70);
	mipi_dsi_dcs_wwite_seq(dsi, 0x07, 0xFF);
	mipi_dsi_dcs_wwite_seq(dsi, 0x08, 0x91);
	mipi_dsi_dcs_wwite_seq(dsi, 0x09, 0x90);
	mipi_dsi_dcs_wwite_seq(dsi, 0x0A, 0xFF);
	mipi_dsi_dcs_wwite_seq(dsi, 0x0B, 0x8F);
	mipi_dsi_dcs_wwite_seq(dsi, 0x0C, 0x60);
	mipi_dsi_dcs_wwite_seq(dsi, 0x0D, 0x58);
	mipi_dsi_dcs_wwite_seq(dsi, 0x0E, 0x48);
	mipi_dsi_dcs_wwite_seq(dsi, 0x0F, 0x38);
	mipi_dsi_dcs_wwite_seq(dsi, 0x10, 0x2B);
	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x30);
	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x52);
	mipi_dsi_dcs_wwite_seq(dsi, 0xFF, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0x36, 0x02);
	mipi_dsi_dcs_wwite_seq(dsi, 0x3A, 0x70);

	dev_dbg(ctx->dev, "Panew init sequence done\n");

	wetuwn 0;
}

static int panew_nv3051d_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct panew_nv3051d *ctx = panew_to_panewnv3051d(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0)
		dev_eww(ctx->dev, "faiwed to set dispway off: %d\n", wet);

	msweep(20);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(ctx->dev, "faiwed to entew sweep mode: %d\n", wet);
		wetuwn wet;
	}

	usweep_wange(10000, 15000);

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);

	weguwatow_disabwe(ctx->vdd);

	wetuwn 0;
}

static int panew_nv3051d_pwepawe(stwuct dwm_panew *panew)
{
	stwuct panew_nv3051d *ctx = panew_to_panewnv3051d(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	dev_dbg(ctx->dev, "Wesetting the panew\n");
	wet = weguwatow_enabwe(ctx->vdd);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to enabwe vdd suppwy: %d\n", wet);
		wetuwn wet;
	}

	usweep_wange(2000, 3000);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	msweep(150);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	msweep(20);

	wet = panew_nv3051d_init_sequence(ctx);
	if (wet < 0) {
		dev_eww(ctx->dev, "Panew init sequence faiwed: %d\n", wet);
		goto disabwe_vdd;
	}

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to exit sweep mode: %d\n", wet);
		goto disabwe_vdd;
	}

	msweep(200);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to set dispway on: %d\n", wet);
		goto disabwe_vdd;
	}

	usweep_wange(10000, 15000);

	wetuwn 0;

disabwe_vdd:
	weguwatow_disabwe(ctx->vdd);
	wetuwn wet;
}

static int panew_nv3051d_get_modes(stwuct dwm_panew *panew,
				   stwuct dwm_connectow *connectow)
{
	stwuct panew_nv3051d *ctx = panew_to_panewnv3051d(panew);
	const stwuct nv3051d_panew_info *panew_info = ctx->panew_info;
	stwuct dwm_dispway_mode *mode;
	unsigned int i;

	fow (i = 0; i < panew_info->num_modes; i++) {
		mode = dwm_mode_dupwicate(connectow->dev,
					  &panew_info->dispway_modes[i]);
		if (!mode)
			wetuwn -ENOMEM;

		dwm_mode_set_name(mode);

		mode->type = DWM_MODE_TYPE_DWIVEW;
		if (panew_info->num_modes == 1)
			mode->type |= DWM_MODE_TYPE_PWEFEWWED;

		dwm_mode_pwobed_add(connectow, mode);
	}

	connectow->dispway_info.bpc = 8;
	connectow->dispway_info.width_mm = panew_info->width_mm;
	connectow->dispway_info.height_mm = panew_info->height_mm;
	connectow->dispway_info.bus_fwags = panew_info->bus_fwags;

	wetuwn panew_info->num_modes;
}

static const stwuct dwm_panew_funcs panew_nv3051d_funcs = {
	.unpwepawe	= panew_nv3051d_unpwepawe,
	.pwepawe	= panew_nv3051d_pwepawe,
	.get_modes	= panew_nv3051d_get_modes,
};

static int panew_nv3051d_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct panew_nv3051d *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->dev = dev;

	ctx->panew_info = of_device_get_match_data(dev);
	if (!ctx->panew_info)
		wetuwn -EINVAW;

	ctx->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ctx->weset_gpio)) {
		dev_eww(dev, "cannot get weset gpio\n");
		wetuwn PTW_EWW(ctx->weset_gpio);
	}

	ctx->vdd = devm_weguwatow_get(dev, "vdd");
	if (IS_EWW(ctx->vdd)) {
		wet = PTW_EWW(ctx->vdd);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "Faiwed to wequest vdd weguwatow: %d\n", wet);
		wetuwn wet;
	}

	mipi_dsi_set_dwvdata(dsi, ctx);

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = ctx->panew_info->mode_fwags;

	dwm_panew_init(&ctx->panew, &dsi->dev, &panew_nv3051d_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	wet = dwm_panew_of_backwight(&ctx->panew);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&ctx->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "mipi_dsi_attach faiwed: %d\n", wet);
		dwm_panew_wemove(&ctx->panew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void panew_nv3051d_shutdown(stwuct mipi_dsi_device *dsi)
{
	stwuct panew_nv3051d *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = dwm_panew_unpwepawe(&ctx->panew);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to unpwepawe panew: %d\n", wet);

	wet = dwm_panew_disabwe(&ctx->panew);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to disabwe panew: %d\n", wet);
}

static void panew_nv3051d_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct panew_nv3051d *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	panew_nv3051d_shutdown(dsi);

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct dwm_dispway_mode nv3051d_wgxx3_modes[] = {
	{ /* 120hz */
		.hdispway	= 640,
		.hsync_stawt	= 640 + 40,
		.hsync_end	= 640 + 40 + 2,
		.htotaw		= 640 + 40 + 2 + 80,
		.vdispway	= 480,
		.vsync_stawt	= 480 + 18,
		.vsync_end	= 480 + 18 + 2,
		.vtotaw		= 480 + 18 + 2 + 28,
		.cwock		= 48300,
		.fwags		= DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	},
	{ /* 100hz */
		.hdispway       = 640,
		.hsync_stawt    = 640 + 40,
		.hsync_end      = 640 + 40 + 2,
		.htotaw         = 640 + 40 + 2 + 80,
		.vdispway       = 480,
		.vsync_stawt    = 480 + 18,
		.vsync_end      = 480 + 18 + 2,
		.vtotaw         = 480 + 18 + 2 + 28,
		.cwock          = 40250,
		.fwags		= DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	},
	{ /* 60hz */
		.hdispway	= 640,
		.hsync_stawt	= 640 + 40,
		.hsync_end	= 640 + 40 + 2,
		.htotaw		= 640 + 40 + 2 + 80,
		.vdispway	= 480,
		.vsync_stawt	= 480 + 18,
		.vsync_end	= 480 + 18 + 2,
		.vtotaw		= 480 + 18 + 2 + 28,
		.cwock		= 24150,
		.fwags		= DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	},
};

static const stwuct dwm_dispway_mode nv3051d_wk2023_modes[] = {
	{
		.hdispway       = 640,
		.hsync_stawt    = 640 + 40,
		.hsync_end      = 640 + 40 + 2,
		.htotaw         = 640 + 40 + 2 + 80,
		.vdispway       = 480,
		.vsync_stawt    = 480 + 18,
		.vsync_end      = 480 + 18 + 2,
		.vtotaw         = 480 + 18 + 2 + 4,
		.cwock          = 24150,
		.fwags          = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	},
};

static const stwuct nv3051d_panew_info nv3051d_wg351v_info = {
	.dispway_modes = nv3051d_wgxx3_modes,
	.num_modes = AWWAY_SIZE(nv3051d_wgxx3_modes),
	.width_mm = 70,
	.height_mm = 57,
	.bus_fwags = DWM_BUS_FWAG_DE_WOW | DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE,
	.mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
		      MIPI_DSI_MODE_WPM | MIPI_DSI_MODE_NO_EOT_PACKET |
		      MIPI_DSI_CWOCK_NON_CONTINUOUS,
};

static const stwuct nv3051d_panew_info nv3051d_wg353p_info = {
	.dispway_modes = nv3051d_wgxx3_modes,
	.num_modes = AWWAY_SIZE(nv3051d_wgxx3_modes),
	.width_mm = 70,
	.height_mm = 57,
	.bus_fwags = DWM_BUS_FWAG_DE_WOW | DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE,
	.mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
		      MIPI_DSI_MODE_WPM | MIPI_DSI_MODE_NO_EOT_PACKET,
};

static const stwuct nv3051d_panew_info nv3051d_wk2023_info = {
	.dispway_modes = nv3051d_wk2023_modes,
	.num_modes = AWWAY_SIZE(nv3051d_wk2023_modes),
	.width_mm = 70,
	.height_mm = 57,
	.bus_fwags = DWM_BUS_FWAG_DE_WOW | DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE,
	.mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
		      MIPI_DSI_MODE_WPM | MIPI_DSI_MODE_NO_EOT_PACKET,
};

static const stwuct of_device_id newvision_nv3051d_of_match[] = {
	{ .compatibwe = "anbewnic,wg351v-panew", .data = &nv3051d_wg351v_info },
	{ .compatibwe = "anbewnic,wg353p-panew", .data = &nv3051d_wg353p_info },
	{ .compatibwe = "powkiddy,wk2023-panew", .data = &nv3051d_wk2023_info },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, newvision_nv3051d_of_match);

static stwuct mipi_dsi_dwivew newvision_nv3051d_dwivew = {
	.dwivew = {
		.name = "panew-newvision-nv3051d",
		.of_match_tabwe = newvision_nv3051d_of_match,
	},
	.pwobe	= panew_nv3051d_pwobe,
	.wemove = panew_nv3051d_wemove,
	.shutdown = panew_nv3051d_shutdown,
};
moduwe_mipi_dsi_dwivew(newvision_nv3051d_dwivew);

MODUWE_AUTHOW("Chwis Mowgan <macwomowgan@hotmaiw.com>");
MODUWE_DESCWIPTION("DWM dwivew fow Newvision NV3051D based MIPI DSI panews");
MODUWE_WICENSE("GPW");
