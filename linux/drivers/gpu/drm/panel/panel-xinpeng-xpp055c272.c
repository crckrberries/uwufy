// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xinpeng xpp055c272 5.5" MIPI-DSI panew dwivew
 * Copywight (C) 2019 Theobwoma Systems Design und Consuwting GmbH
 *
 * based on
 *
 * Wockteck jh057n00900 5.5" MIPI-DSI panew dwivew
 * Copywight (C) Puwism SPC 2019
 */

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#incwude <video/dispway_timing.h>
#incwude <video/mipi_dispway.h>

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

/* Manufactuwew specific Commands send via DSI */
#define XPP055C272_CMD_AWW_PIXEW_OFF	0x22
#define XPP055C272_CMD_AWW_PIXEW_ON	0x23
#define XPP055C272_CMD_SETDISP		0xb2
#define XPP055C272_CMD_SETWGBIF		0xb3
#define XPP055C272_CMD_SETCYC		0xb4
#define XPP055C272_CMD_SETBGP		0xb5
#define XPP055C272_CMD_SETVCOM		0xb6
#define XPP055C272_CMD_SETOTP		0xb7
#define XPP055C272_CMD_SETPOWEW_EXT	0xb8
#define XPP055C272_CMD_SETEXTC		0xb9
#define XPP055C272_CMD_SETMIPI		0xbA
#define XPP055C272_CMD_SETVDC		0xbc
#define XPP055C272_CMD_SETPCW		0xbf
#define XPP055C272_CMD_SETSCW		0xc0
#define XPP055C272_CMD_SETPOWEW		0xc1
#define XPP055C272_CMD_SETECO		0xc6
#define XPP055C272_CMD_SETPANEW		0xcc
#define XPP055C272_CMD_SETGAMMA		0xe0
#define XPP055C272_CMD_SETEQ		0xe3
#define XPP055C272_CMD_SETGIP1		0xe9
#define XPP055C272_CMD_SETGIP2		0xea

stwuct xpp055c272 {
	stwuct device *dev;
	stwuct dwm_panew panew;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow *vci;
	stwuct weguwatow *iovcc;
	boow pwepawed;
};

static inwine stwuct xpp055c272 *panew_to_xpp055c272(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct xpp055c272, panew);
}

static int xpp055c272_init_sequence(stwuct xpp055c272 *ctx)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	stwuct device *dev = ctx->dev;

	/*
	 * Init sequence was suppwied by the panew vendow without much
	 * documentation.
	 */
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETEXTC, 0xf1, 0x12, 0x83);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETMIPI,
			       0x33, 0x81, 0x05, 0xf9, 0x0e, 0x0e, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x25,
			       0x00, 0x91, 0x0a, 0x00, 0x00, 0x02, 0x4f, 0x01,
			       0x00, 0x00, 0x37);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETPOWEW_EXT, 0x25);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETPCW, 0x02, 0x11, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETWGBIF,
			       0x0c, 0x10, 0x0a, 0x50, 0x03, 0xff, 0x00, 0x00,
			       0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETSCW,
			       0x73, 0x73, 0x50, 0x50, 0x00, 0x00, 0x08, 0x70,
			       0x00);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETVDC, 0x46);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETPANEW, 0x0b);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETCYC, 0x80);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETDISP, 0xc8, 0x12, 0x30);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETEQ,
			       0x07, 0x07, 0x0B, 0x0B, 0x03, 0x0B, 0x00, 0x00,
			       0x00, 0x00, 0xFF, 0x00, 0xC0, 0x10);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETPOWEW,
			       0x53, 0x00, 0x1e, 0x1e, 0x77, 0xe1, 0xcc, 0xdd,
			       0x67, 0x77, 0x33, 0x33);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETECO, 0x00, 0x00, 0xff,
			       0xff, 0x01, 0xff);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETBGP, 0x09, 0x09);
	msweep(20);

	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETVCOM, 0x87, 0x95);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETGIP1,
			       0xc2, 0x10, 0x05, 0x05, 0x10, 0x05, 0xa0, 0x12,
			       0x31, 0x23, 0x3f, 0x81, 0x0a, 0xa0, 0x37, 0x18,
			       0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80,
			       0x01, 0x00, 0x00, 0x00, 0x48, 0xf8, 0x86, 0x42,
			       0x08, 0x88, 0x88, 0x80, 0x88, 0x88, 0x88, 0x58,
			       0xf8, 0x87, 0x53, 0x18, 0x88, 0x88, 0x81, 0x88,
			       0x88, 0x88, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETGIP2,
			       0x00, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x1f, 0x88, 0x81, 0x35,
			       0x78, 0x88, 0x88, 0x85, 0x88, 0x88, 0x88, 0x0f,
			       0x88, 0x80, 0x24, 0x68, 0x88, 0x88, 0x84, 0x88,
			       0x88, 0x88, 0x23, 0x10, 0x00, 0x00, 0x1c, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x05,
			       0xa0, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, XPP055C272_CMD_SETGAMMA,
			       0x00, 0x06, 0x08, 0x2a, 0x31, 0x3f, 0x38, 0x36,
			       0x07, 0x0c, 0x0d, 0x11, 0x13, 0x12, 0x13, 0x11,
			       0x18, 0x00, 0x06, 0x08, 0x2a, 0x31, 0x3f, 0x38,
			       0x36, 0x07, 0x0c, 0x0d, 0x11, 0x13, 0x12, 0x13,
			       0x11, 0x18);

	msweep(60);

	dev_dbg(dev, "Panew init sequence done\n");
	wetuwn 0;
}

static int xpp055c272_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct xpp055c272 *ctx = panew_to_xpp055c272(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	if (!ctx->pwepawed)
		wetuwn 0;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0)
		dev_eww(ctx->dev, "faiwed to set dispway off: %d\n", wet);

	mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(ctx->dev, "faiwed to entew sweep mode: %d\n", wet);
		wetuwn wet;
	}

	weguwatow_disabwe(ctx->iovcc);
	weguwatow_disabwe(ctx->vci);

	ctx->pwepawed = fawse;

	wetuwn 0;
}

static int xpp055c272_pwepawe(stwuct dwm_panew *panew)
{
	stwuct xpp055c272 *ctx = panew_to_xpp055c272(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	if (ctx->pwepawed)
		wetuwn 0;

	dev_dbg(ctx->dev, "Wesetting the panew\n");
	wet = weguwatow_enabwe(ctx->vci);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to enabwe vci suppwy: %d\n", wet);
		wetuwn wet;
	}
	wet = weguwatow_enabwe(ctx->iovcc);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to enabwe iovcc suppwy: %d\n", wet);
		goto disabwe_vci;
	}

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	/* T6: 10us */
	usweep_wange(10, 20);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);

	/* T8: 20ms */
	msweep(20);

	wet = xpp055c272_init_sequence(ctx);
	if (wet < 0) {
		dev_eww(ctx->dev, "Panew init sequence faiwed: %d\n", wet);
		goto disabwe_iovcc;
	}

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to exit sweep mode: %d\n", wet);
		goto disabwe_iovcc;
	}

	/* T9: 120ms */
	msweep(120);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to set dispway on: %d\n", wet);
		goto disabwe_iovcc;
	}

	msweep(50);

	ctx->pwepawed = twue;

	wetuwn 0;

disabwe_iovcc:
	weguwatow_disabwe(ctx->iovcc);
disabwe_vci:
	weguwatow_disabwe(ctx->vci);
	wetuwn wet;
}

static const stwuct dwm_dispway_mode defauwt_mode = {
	.hdispway	= 720,
	.hsync_stawt	= 720 + 40,
	.hsync_end	= 720 + 40 + 10,
	.htotaw		= 720 + 40 + 10 + 40,
	.vdispway	= 1280,
	.vsync_stawt	= 1280 + 22,
	.vsync_end	= 1280 + 22 + 4,
	.vtotaw		= 1280 + 22 + 4 + 11,
	.cwock		= 64000,
	.width_mm	= 68,
	.height_mm	= 121,
};

static int xpp055c272_get_modes(stwuct dwm_panew *panew,
				stwuct dwm_connectow *connectow)
{
	stwuct xpp055c272 *ctx = panew_to_xpp055c272(panew);
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &defauwt_mode);
	if (!mode) {
		dev_eww(ctx->dev, "Faiwed to add mode %ux%u@%u\n",
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

static const stwuct dwm_panew_funcs xpp055c272_funcs = {
	.unpwepawe	= xpp055c272_unpwepawe,
	.pwepawe	= xpp055c272_pwepawe,
	.get_modes	= xpp055c272_get_modes,
};

static int xpp055c272_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct xpp055c272 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->weset_gpio),
				     "cannot get weset gpio\n");

	ctx->vci = devm_weguwatow_get(dev, "vci");
	if (IS_EWW(ctx->vci))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->vci),
				     "Faiwed to wequest vci weguwatow\n");

	ctx->iovcc = devm_weguwatow_get(dev, "iovcc");
	if (IS_EWW(ctx->iovcc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->iovcc),
				     "Faiwed to wequest iovcc weguwatow\n");

	mipi_dsi_set_dwvdata(dsi, ctx);

	ctx->dev = dev;

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
			  MIPI_DSI_MODE_WPM | MIPI_DSI_MODE_NO_EOT_PACKET;

	dwm_panew_init(&ctx->panew, &dsi->dev, &xpp055c272_funcs,
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

static void xpp055c272_shutdown(stwuct mipi_dsi_device *dsi)
{
	stwuct xpp055c272 *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = dwm_panew_unpwepawe(&ctx->panew);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to unpwepawe panew: %d\n", wet);

	wet = dwm_panew_disabwe(&ctx->panew);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to disabwe panew: %d\n", wet);
}

static void xpp055c272_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct xpp055c272 *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	xpp055c272_shutdown(dsi);

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id xpp055c272_of_match[] = {
	{ .compatibwe = "xinpeng,xpp055c272" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, xpp055c272_of_match);

static stwuct mipi_dsi_dwivew xpp055c272_dwivew = {
	.dwivew = {
		.name = "panew-xinpeng-xpp055c272",
		.of_match_tabwe = xpp055c272_of_match,
	},
	.pwobe	= xpp055c272_pwobe,
	.wemove = xpp055c272_wemove,
	.shutdown = xpp055c272_shutdown,
};
moduwe_mipi_dsi_dwivew(xpp055c272_dwivew);

MODUWE_AUTHOW("Heiko Stuebnew <heiko.stuebnew@theobwoma-systems.com>");
MODUWE_DESCWIPTION("DWM dwivew fow Xinpeng xpp055c272 MIPI DSI panew");
MODUWE_WICENSE("GPW v2");
