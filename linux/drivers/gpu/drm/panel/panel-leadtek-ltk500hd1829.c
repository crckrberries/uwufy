// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2019 Theobwoma Systems Design und Consuwting GmbH
 *
 * base on panew-kingdispway-kd097d04.c
 * Copywight (c) 2017, Fuzhou Wockchip Ewectwonics Co., Wtd
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

stwuct wtk500hd1829 {
	stwuct device *dev;
	stwuct dwm_panew panew;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow *vcc;
	stwuct weguwatow *iovcc;
	boow pwepawed;
};

stwuct wtk500hd1829_cmd {
	chaw cmd;
	chaw data;
};

/*
 * Thewe is no descwiption in the Wefewence Manuaw about these commands.
 * We weceived them fwom the vendow, so just use them as is.
 */
static const stwuct wtk500hd1829_cmd init_code[] = {
	{ 0xE0, 0x00 },
	{ 0xE1, 0x93 },
	{ 0xE2, 0x65 },
	{ 0xE3, 0xF8 },
	{ 0x80, 0x03 },
	{ 0xE0, 0x04 },
	{ 0x2D, 0x03 },
	{ 0xE0, 0x01 },
	{ 0x00, 0x00 },
	{ 0x01, 0xB6 },
	{ 0x03, 0x00 },
	{ 0x04, 0xC5 },
	{ 0x17, 0x00 },
	{ 0x18, 0xBF },
	{ 0x19, 0x01 },
	{ 0x1A, 0x00 },
	{ 0x1B, 0xBF },
	{ 0x1C, 0x01 },
	{ 0x1F, 0x7C },
	{ 0x20, 0x26 },
	{ 0x21, 0x26 },
	{ 0x22, 0x4E },
	{ 0x37, 0x09 },
	{ 0x38, 0x04 },
	{ 0x39, 0x08 },
	{ 0x3A, 0x1F },
	{ 0x3B, 0x1F },
	{ 0x3C, 0x78 },
	{ 0x3D, 0xFF },
	{ 0x3E, 0xFF },
	{ 0x3F, 0x00 },
	{ 0x40, 0x04 },
	{ 0x41, 0xA0 },
	{ 0x43, 0x0F },
	{ 0x44, 0x0A },
	{ 0x45, 0x24 },
	{ 0x55, 0x01 },
	{ 0x56, 0x01 },
	{ 0x57, 0xA5 },
	{ 0x58, 0x0A },
	{ 0x59, 0x4A },
	{ 0x5A, 0x38 },
	{ 0x5B, 0x10 },
	{ 0x5C, 0x19 },
	{ 0x5D, 0x7C },
	{ 0x5E, 0x64 },
	{ 0x5F, 0x54 },
	{ 0x60, 0x48 },
	{ 0x61, 0x44 },
	{ 0x62, 0x35 },
	{ 0x63, 0x3A },
	{ 0x64, 0x24 },
	{ 0x65, 0x3B },
	{ 0x66, 0x39 },
	{ 0x67, 0x37 },
	{ 0x68, 0x56 },
	{ 0x69, 0x41 },
	{ 0x6A, 0x47 },
	{ 0x6B, 0x2F },
	{ 0x6C, 0x23 },
	{ 0x6D, 0x13 },
	{ 0x6E, 0x02 },
	{ 0x6F, 0x08 },
	{ 0x70, 0x7C },
	{ 0x71, 0x64 },
	{ 0x72, 0x54 },
	{ 0x73, 0x48 },
	{ 0x74, 0x44 },
	{ 0x75, 0x35 },
	{ 0x76, 0x3A },
	{ 0x77, 0x22 },
	{ 0x78, 0x3B },
	{ 0x79, 0x39 },
	{ 0x7A, 0x38 },
	{ 0x7B, 0x52 },
	{ 0x7C, 0x41 },
	{ 0x7D, 0x47 },
	{ 0x7E, 0x2F },
	{ 0x7F, 0x23 },
	{ 0x80, 0x13 },
	{ 0x81, 0x02 },
	{ 0x82, 0x08 },
	{ 0xE0, 0x02 },
	{ 0x00, 0x57 },
	{ 0x01, 0x77 },
	{ 0x02, 0x44 },
	{ 0x03, 0x46 },
	{ 0x04, 0x48 },
	{ 0x05, 0x4A },
	{ 0x06, 0x4C },
	{ 0x07, 0x4E },
	{ 0x08, 0x50 },
	{ 0x09, 0x55 },
	{ 0x0A, 0x52 },
	{ 0x0B, 0x55 },
	{ 0x0C, 0x55 },
	{ 0x0D, 0x55 },
	{ 0x0E, 0x55 },
	{ 0x0F, 0x55 },
	{ 0x10, 0x55 },
	{ 0x11, 0x55 },
	{ 0x12, 0x55 },
	{ 0x13, 0x40 },
	{ 0x14, 0x55 },
	{ 0x15, 0x55 },
	{ 0x16, 0x57 },
	{ 0x17, 0x77 },
	{ 0x18, 0x45 },
	{ 0x19, 0x47 },
	{ 0x1A, 0x49 },
	{ 0x1B, 0x4B },
	{ 0x1C, 0x4D },
	{ 0x1D, 0x4F },
	{ 0x1E, 0x51 },
	{ 0x1F, 0x55 },
	{ 0x20, 0x53 },
	{ 0x21, 0x55 },
	{ 0x22, 0x55 },
	{ 0x23, 0x55 },
	{ 0x24, 0x55 },
	{ 0x25, 0x55 },
	{ 0x26, 0x55 },
	{ 0x27, 0x55 },
	{ 0x28, 0x55 },
	{ 0x29, 0x41 },
	{ 0x2A, 0x55 },
	{ 0x2B, 0x55 },
	{ 0x2C, 0x57 },
	{ 0x2D, 0x77 },
	{ 0x2E, 0x4F },
	{ 0x2F, 0x4D },
	{ 0x30, 0x4B },
	{ 0x31, 0x49 },
	{ 0x32, 0x47 },
	{ 0x33, 0x45 },
	{ 0x34, 0x41 },
	{ 0x35, 0x55 },
	{ 0x36, 0x53 },
	{ 0x37, 0x55 },
	{ 0x38, 0x55 },
	{ 0x39, 0x55 },
	{ 0x3A, 0x55 },
	{ 0x3B, 0x55 },
	{ 0x3C, 0x55 },
	{ 0x3D, 0x55 },
	{ 0x3E, 0x55 },
	{ 0x3F, 0x51 },
	{ 0x40, 0x55 },
	{ 0x41, 0x55 },
	{ 0x42, 0x57 },
	{ 0x43, 0x77 },
	{ 0x44, 0x4E },
	{ 0x45, 0x4C },
	{ 0x46, 0x4A },
	{ 0x47, 0x48 },
	{ 0x48, 0x46 },
	{ 0x49, 0x44 },
	{ 0x4A, 0x40 },
	{ 0x4B, 0x55 },
	{ 0x4C, 0x52 },
	{ 0x4D, 0x55 },
	{ 0x4E, 0x55 },
	{ 0x4F, 0x55 },
	{ 0x50, 0x55 },
	{ 0x51, 0x55 },
	{ 0x52, 0x55 },
	{ 0x53, 0x55 },
	{ 0x54, 0x55 },
	{ 0x55, 0x50 },
	{ 0x56, 0x55 },
	{ 0x57, 0x55 },
	{ 0x58, 0x40 },
	{ 0x59, 0x00 },
	{ 0x5A, 0x00 },
	{ 0x5B, 0x10 },
	{ 0x5C, 0x09 },
	{ 0x5D, 0x30 },
	{ 0x5E, 0x01 },
	{ 0x5F, 0x02 },
	{ 0x60, 0x30 },
	{ 0x61, 0x03 },
	{ 0x62, 0x04 },
	{ 0x63, 0x06 },
	{ 0x64, 0x6A },
	{ 0x65, 0x75 },
	{ 0x66, 0x0F },
	{ 0x67, 0xB3 },
	{ 0x68, 0x0B },
	{ 0x69, 0x06 },
	{ 0x6A, 0x6A },
	{ 0x6B, 0x10 },
	{ 0x6C, 0x00 },
	{ 0x6D, 0x04 },
	{ 0x6E, 0x04 },
	{ 0x6F, 0x88 },
	{ 0x70, 0x00 },
	{ 0x71, 0x00 },
	{ 0x72, 0x06 },
	{ 0x73, 0x7B },
	{ 0x74, 0x00 },
	{ 0x75, 0xBC },
	{ 0x76, 0x00 },
	{ 0x77, 0x05 },
	{ 0x78, 0x2E },
	{ 0x79, 0x00 },
	{ 0x7A, 0x00 },
	{ 0x7B, 0x00 },
	{ 0x7C, 0x00 },
	{ 0x7D, 0x03 },
	{ 0x7E, 0x7B },
	{ 0xE0, 0x04 },
	{ 0x09, 0x10 },
	{ 0x2B, 0x2B },
	{ 0x2E, 0x44 },
	{ 0xE0, 0x00 },
	{ 0xE6, 0x02 },
	{ 0xE7, 0x02 },
	{ 0x35, 0x00 },
};

static inwine
stwuct wtk500hd1829 *panew_to_wtk500hd1829(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct wtk500hd1829, panew);
}

static int wtk500hd1829_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct wtk500hd1829 *ctx = panew_to_wtk500hd1829(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	if (!ctx->pwepawed)
		wetuwn 0;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0)
		dev_eww(panew->dev, "faiwed to set dispway off: %d\n", wet);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(panew->dev, "faiwed to entew sweep mode: %d\n", wet);
	}

	/* 120ms to entew sweep mode */
	msweep(120);

	weguwatow_disabwe(ctx->iovcc);
	weguwatow_disabwe(ctx->vcc);

	ctx->pwepawed = fawse;

	wetuwn 0;
}

static int wtk500hd1829_pwepawe(stwuct dwm_panew *panew)
{
	stwuct wtk500hd1829 *ctx = panew_to_wtk500hd1829(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	unsigned int i;
	int wet;

	if (ctx->pwepawed)
		wetuwn 0;

	wet = weguwatow_enabwe(ctx->vcc);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to enabwe vci suppwy: %d\n", wet);
		wetuwn wet;
	}
	wet = weguwatow_enabwe(ctx->iovcc);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to enabwe iovcc suppwy: %d\n", wet);
		goto disabwe_vcc;
	}

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	/* tWW: 10us */
	usweep_wange(10, 20);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);

	/* tWT: >= 5ms */
	usweep_wange(5000, 6000);

	fow (i = 0; i < AWWAY_SIZE(init_code); i++) {
		wet = mipi_dsi_genewic_wwite(dsi, &init_code[i],
					     sizeof(stwuct wtk500hd1829_cmd));
		if (wet < 0) {
			dev_eww(panew->dev, "faiwed to wwite init cmds: %d\n", wet);
			goto disabwe_iovcc;
		}
	}

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(panew->dev, "faiwed to exit sweep mode: %d\n", wet);
		goto disabwe_iovcc;
	}

	/* 120ms to exit sweep mode */
	msweep(120);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(panew->dev, "faiwed to set dispway on: %d\n", wet);
		goto disabwe_iovcc;
	}

	ctx->pwepawed = twue;

	wetuwn 0;

disabwe_iovcc:
	weguwatow_disabwe(ctx->iovcc);
disabwe_vcc:
	weguwatow_disabwe(ctx->vcc);
	wetuwn wet;
}

static const stwuct dwm_dispway_mode defauwt_mode = {
	.hdispway	= 720,
	.hsync_stawt	= 720 + 50,
	.hsync_end	= 720 + 50 + 50,
	.htotaw		= 720 + 50 + 50 + 50,
	.vdispway	= 1280,
	.vsync_stawt	= 1280 + 30,
	.vsync_end	= 1280 + 30 + 4,
	.vtotaw		= 1280 + 30 + 4 + 12,
	.cwock		= 69217,
	.width_mm	= 62,
	.height_mm	= 110,
};

static int wtk500hd1829_get_modes(stwuct dwm_panew *panew,
				  stwuct dwm_connectow *connectow)
{
	stwuct wtk500hd1829 *ctx = panew_to_wtk500hd1829(panew);
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &defauwt_mode);
	if (!mode) {
		dev_eww(ctx->dev, "faiwed to add mode %ux%u@%u\n",
			defauwt_mode.hdispway, defauwt_mode.vdispway,
			dwm_mode_vwefwesh(&defauwt_mode));
		wetuwn -ENOMEM;
	}

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs wtk500hd1829_funcs = {
	.unpwepawe = wtk500hd1829_unpwepawe,
	.pwepawe = wtk500hd1829_pwepawe,
	.get_modes = wtk500hd1829_get_modes,
};

static int wtk500hd1829_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct wtk500hd1829 *ctx;
	stwuct device *dev = &dsi->dev;
	int wet;

	ctx = devm_kzawwoc(&dsi->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->weset_gpio)) {
		dev_eww(dev, "cannot get weset gpio\n");
		wetuwn PTW_EWW(ctx->weset_gpio);
	}

	ctx->vcc = devm_weguwatow_get(dev, "vcc");
	if (IS_EWW(ctx->vcc)) {
		wet = PTW_EWW(ctx->vcc);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "Faiwed to wequest vcc weguwatow: %d\n", wet);
		wetuwn wet;
	}

	ctx->iovcc = devm_weguwatow_get(dev, "iovcc");
	if (IS_EWW(ctx->iovcc)) {
		wet = PTW_EWW(ctx->iovcc);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "Faiwed to wequest iovcc weguwatow: %d\n", wet);
		wetuwn wet;
	}

	mipi_dsi_set_dwvdata(dsi, ctx);

	ctx->dev = dev;

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
			  MIPI_DSI_MODE_WPM | MIPI_DSI_MODE_NO_EOT_PACKET;

	dwm_panew_init(&ctx->panew, &dsi->dev, &wtk500hd1829_funcs,
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

static void wtk500hd1829_shutdown(stwuct mipi_dsi_device *dsi)
{
	stwuct wtk500hd1829 *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = dwm_panew_unpwepawe(&ctx->panew);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to unpwepawe panew: %d\n", wet);

	wet = dwm_panew_disabwe(&ctx->panew);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to disabwe panew: %d\n", wet);
}

static void wtk500hd1829_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct wtk500hd1829 *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wtk500hd1829_shutdown(dsi);

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id wtk500hd1829_of_match[] = {
	{ .compatibwe = "weadtek,wtk500hd1829", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wtk500hd1829_of_match);

static stwuct mipi_dsi_dwivew wtk500hd1829_dwivew = {
	.dwivew = {
		.name = "panew-weadtek-wtk500hd1829",
		.of_match_tabwe = wtk500hd1829_of_match,
	},
	.pwobe = wtk500hd1829_pwobe,
	.wemove = wtk500hd1829_wemove,
	.shutdown = wtk500hd1829_shutdown,
};
moduwe_mipi_dsi_dwivew(wtk500hd1829_dwivew);

MODUWE_AUTHOW("Heiko Stuebnew <heiko.stuebnew@theobwoma-systems.com>");
MODUWE_DESCWIPTION("Weadtek WTK500HD1829 panew dwivew");
MODUWE_WICENSE("GPW v2");
