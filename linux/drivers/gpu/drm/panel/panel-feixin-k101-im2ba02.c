// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019-2020 Icenowy Zheng <icenowy@aosc.io>
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define K101_IM2BA02_INIT_CMD_WEN	2

static const chaw * const weguwatow_names[] = {
	"dvdd",
	"avdd",
	"cvdd"
};

stwuct k101_im2ba02 {
	stwuct dwm_panew	panew;
	stwuct mipi_dsi_device	*dsi;

	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(weguwatow_names)];
	stwuct gpio_desc	*weset;
};

static inwine stwuct k101_im2ba02 *panew_to_k101_im2ba02(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct k101_im2ba02, panew);
}

stwuct k101_im2ba02_init_cmd {
	u8 data[K101_IM2BA02_INIT_CMD_WEN];
};

static const stwuct k101_im2ba02_init_cmd k101_im2ba02_init_cmds[] = {
	/* Switch to page 0 */
	{ .data = { 0xE0, 0x00 } },

	/* Seems to be some passwowd */
	{ .data = { 0xE1, 0x93} },
	{ .data = { 0xE2, 0x65 } },
	{ .data = { 0xE3, 0xF8 } },

	/* Wane numbew, 0x02 - 3 wanes, 0x03 - 4 wanes */
	{ .data = { 0x80, 0x03 } },

	/* Sequence contwow */
	{ .data = { 0x70, 0x02 } },
	{ .data = { 0x71, 0x23 } },
	{ .data = { 0x72, 0x06 } },

	/* Switch to page 1 */
	{ .data = { 0xE0, 0x01 } },

	/* Set VCOM */
	{ .data = { 0x00, 0x00 } },
	{ .data = { 0x01, 0x66 } },
	/* Set VCOM_Wevewse */
	{ .data = { 0x03, 0x00 } },
	{ .data = { 0x04, 0x25 } },

	/* Set Gamma Powew, VG[MS][PN] */
	{ .data = { 0x17, 0x00 } },
	{ .data = { 0x18, 0x6D } },
	{ .data = { 0x19, 0x00 } },
	{ .data = { 0x1A, 0x00 } },
	{ .data = { 0x1B, 0xBF } }, /* VGMN = -4.5V */
	{ .data = { 0x1C, 0x00 } },

	/* Set Gate Powew */
	{ .data = { 0x1F, 0x3E } }, /* VGH_W = 15V */
	{ .data = { 0x20, 0x28 } }, /* VGW_W = -11V */
	{ .data = { 0x21, 0x28 } }, /* VGW_W2 = -11V */
	{ .data = { 0x22, 0x0E } }, /* PA[6:4] = 0, PA[0] = 0 */

	/* Set Panew */
	{ .data = { 0x37, 0x09 } }, /* SS = 1, BGW = 1 */

	/* Set WGBCYC */
	{ .data = { 0x38, 0x04 } }, /* JDT = 100 cowumn invewsion */
	{ .data = { 0x39, 0x08 } }, /* WGB_N_EQ1 */
	{ .data = { 0x3A, 0x12 } }, /* WGB_N_EQ2 */
	{ .data = { 0x3C, 0x78 } }, /* set EQ3 fow TE_H */
	{ .data = { 0x3D, 0xFF } }, /* set CHGEN_ON */
	{ .data = { 0x3E, 0xFF } }, /* set CHGEN_OFF */
	{ .data = { 0x3F, 0x7F } }, /* set CHGEN_OFF2 */

	/* Set TCON pawametew */
	{ .data = { 0x40, 0x06 } }, /* WSO = 800 points */
	{ .data = { 0x41, 0xA0 } }, /* WN = 1280 wines */

	/* Set powew vowtage */
	{ .data = { 0x55, 0x0F } }, /* DCDCM */
	{ .data = { 0x56, 0x01 } },
	{ .data = { 0x57, 0x69 } },
	{ .data = { 0x58, 0x0A } },
	{ .data = { 0x59, 0x0A } },
	{ .data = { 0x5A, 0x45 } },
	{ .data = { 0x5B, 0x15 } },

	/* Set gamma */
	{ .data = { 0x5D, 0x7C } },
	{ .data = { 0x5E, 0x65 } },
	{ .data = { 0x5F, 0x55 } },
	{ .data = { 0x60, 0x49 } },
	{ .data = { 0x61, 0x44 } },
	{ .data = { 0x62, 0x35 } },
	{ .data = { 0x63, 0x3A } },
	{ .data = { 0x64, 0x23 } },
	{ .data = { 0x65, 0x3D } },
	{ .data = { 0x66, 0x3C } },
	{ .data = { 0x67, 0x3D } },
	{ .data = { 0x68, 0x5D } },
	{ .data = { 0x69, 0x4D } },
	{ .data = { 0x6A, 0x56 } },
	{ .data = { 0x6B, 0x48 } },
	{ .data = { 0x6C, 0x45 } },
	{ .data = { 0x6D, 0x38 } },
	{ .data = { 0x6E, 0x25 } },
	{ .data = { 0x6F, 0x00 } },
	{ .data = { 0x70, 0x7C } },
	{ .data = { 0x71, 0x65 } },
	{ .data = { 0x72, 0x55 } },
	{ .data = { 0x73, 0x49 } },
	{ .data = { 0x74, 0x44 } },
	{ .data = { 0x75, 0x35 } },
	{ .data = { 0x76, 0x3A } },
	{ .data = { 0x77, 0x23 } },
	{ .data = { 0x78, 0x3D } },
	{ .data = { 0x79, 0x3C } },
	{ .data = { 0x7A, 0x3D } },
	{ .data = { 0x7B, 0x5D } },
	{ .data = { 0x7C, 0x4D } },
	{ .data = { 0x7D, 0x56 } },
	{ .data = { 0x7E, 0x48 } },
	{ .data = { 0x7F, 0x45 } },
	{ .data = { 0x80, 0x38 } },
	{ .data = { 0x81, 0x25 } },
	{ .data = { 0x82, 0x00 } },

	/* Switch to page 2, fow GIP */
	{ .data = { 0xE0, 0x02 } },

	{ .data = { 0x00, 0x1E } },
	{ .data = { 0x01, 0x1E } },
	{ .data = { 0x02, 0x41 } },
	{ .data = { 0x03, 0x41 } },
	{ .data = { 0x04, 0x43 } },
	{ .data = { 0x05, 0x43 } },
	{ .data = { 0x06, 0x1F } },
	{ .data = { 0x07, 0x1F } },
	{ .data = { 0x08, 0x1F } },
	{ .data = { 0x09, 0x1F } },
	{ .data = { 0x0A, 0x1E } },
	{ .data = { 0x0B, 0x1E } },
	{ .data = { 0x0C, 0x1F } },
	{ .data = { 0x0D, 0x47 } },
	{ .data = { 0x0E, 0x47 } },
	{ .data = { 0x0F, 0x45 } },
	{ .data = { 0x10, 0x45 } },
	{ .data = { 0x11, 0x4B } },
	{ .data = { 0x12, 0x4B } },
	{ .data = { 0x13, 0x49 } },
	{ .data = { 0x14, 0x49 } },
	{ .data = { 0x15, 0x1F } },

	{ .data = { 0x16, 0x1E } },
	{ .data = { 0x17, 0x1E } },
	{ .data = { 0x18, 0x40 } },
	{ .data = { 0x19, 0x40 } },
	{ .data = { 0x1A, 0x42 } },
	{ .data = { 0x1B, 0x42 } },
	{ .data = { 0x1C, 0x1F } },
	{ .data = { 0x1D, 0x1F } },
	{ .data = { 0x1E, 0x1F } },
	{ .data = { 0x1F, 0x1f } },
	{ .data = { 0x20, 0x1E } },
	{ .data = { 0x21, 0x1E } },
	{ .data = { 0x22, 0x1f } },
	{ .data = { 0x23, 0x46 } },
	{ .data = { 0x24, 0x46 } },
	{ .data = { 0x25, 0x44 } },
	{ .data = { 0x26, 0x44 } },
	{ .data = { 0x27, 0x4A } },
	{ .data = { 0x28, 0x4A } },
	{ .data = { 0x29, 0x48 } },
	{ .data = { 0x2A, 0x48 } },
	{ .data = { 0x2B, 0x1f } },

	{ .data = { 0x2C, 0x1F } },
	{ .data = { 0x2D, 0x1F } },
	{ .data = { 0x2E, 0x42 } },
	{ .data = { 0x2F, 0x42 } },
	{ .data = { 0x30, 0x40 } },
	{ .data = { 0x31, 0x40 } },
	{ .data = { 0x32, 0x1E } },
	{ .data = { 0x33, 0x1E } },
	{ .data = { 0x34, 0x1F } },
	{ .data = { 0x35, 0x1F } },
	{ .data = { 0x36, 0x1E } },
	{ .data = { 0x37, 0x1E } },
	{ .data = { 0x38, 0x1F } },
	{ .data = { 0x39, 0x48 } },
	{ .data = { 0x3A, 0x48 } },
	{ .data = { 0x3B, 0x4A } },
	{ .data = { 0x3C, 0x4A } },
	{ .data = { 0x3D, 0x44 } },
	{ .data = { 0x3E, 0x44 } },
	{ .data = { 0x3F, 0x46 } },
	{ .data = { 0x40, 0x46 } },
	{ .data = { 0x41, 0x1F } },

	{ .data = { 0x42, 0x1F } },
	{ .data = { 0x43, 0x1F } },
	{ .data = { 0x44, 0x43 } },
	{ .data = { 0x45, 0x43 } },
	{ .data = { 0x46, 0x41 } },
	{ .data = { 0x47, 0x41 } },
	{ .data = { 0x48, 0x1E } },
	{ .data = { 0x49, 0x1E } },
	{ .data = { 0x4A, 0x1E } },
	{ .data = { 0x4B, 0x1F } },
	{ .data = { 0x4C, 0x1E } },
	{ .data = { 0x4D, 0x1E } },
	{ .data = { 0x4E, 0x1F } },
	{ .data = { 0x4F, 0x49 } },
	{ .data = { 0x50, 0x49 } },
	{ .data = { 0x51, 0x4B } },
	{ .data = { 0x52, 0x4B } },
	{ .data = { 0x53, 0x45 } },
	{ .data = { 0x54, 0x45 } },
	{ .data = { 0x55, 0x47 } },
	{ .data = { 0x56, 0x47 } },
	{ .data = { 0x57, 0x1F } },

	{ .data = { 0x58, 0x10 } },
	{ .data = { 0x59, 0x00 } },
	{ .data = { 0x5A, 0x00 } },
	{ .data = { 0x5B, 0x30 } },
	{ .data = { 0x5C, 0x02 } },
	{ .data = { 0x5D, 0x40 } },
	{ .data = { 0x5E, 0x01 } },
	{ .data = { 0x5F, 0x02 } },
	{ .data = { 0x60, 0x30 } },
	{ .data = { 0x61, 0x01 } },
	{ .data = { 0x62, 0x02 } },
	{ .data = { 0x63, 0x6A } },
	{ .data = { 0x64, 0x6A } },
	{ .data = { 0x65, 0x05 } },
	{ .data = { 0x66, 0x12 } },
	{ .data = { 0x67, 0x74 } },
	{ .data = { 0x68, 0x04 } },
	{ .data = { 0x69, 0x6A } },
	{ .data = { 0x6A, 0x6A } },
	{ .data = { 0x6B, 0x08 } },

	{ .data = { 0x6C, 0x00 } },
	{ .data = { 0x6D, 0x04 } },
	{ .data = { 0x6E, 0x04 } },
	{ .data = { 0x6F, 0x88 } },
	{ .data = { 0x70, 0x00 } },
	{ .data = { 0x71, 0x00 } },
	{ .data = { 0x72, 0x06 } },
	{ .data = { 0x73, 0x7B } },
	{ .data = { 0x74, 0x00 } },
	{ .data = { 0x75, 0x07 } },
	{ .data = { 0x76, 0x00 } },
	{ .data = { 0x77, 0x5D } },
	{ .data = { 0x78, 0x17 } },
	{ .data = { 0x79, 0x1F } },
	{ .data = { 0x7A, 0x00 } },
	{ .data = { 0x7B, 0x00 } },
	{ .data = { 0x7C, 0x00 } },
	{ .data = { 0x7D, 0x03 } },
	{ .data = { 0x7E, 0x7B } },

	{ .data = { 0xE0, 0x04 } },
	{ .data = { 0x2B, 0x2B } },
	{ .data = { 0x2E, 0x44 } },

	{ .data = { 0xE0, 0x01 } },
	{ .data = { 0x0E, 0x01 } },

	{ .data = { 0xE0, 0x03 } },
	{ .data = { 0x98, 0x2F } },

	{ .data = { 0xE0, 0x00 } },
	{ .data = { 0xE6, 0x02 } },
	{ .data = { 0xE7, 0x02 } },

	{ .data = { 0x11, 0x00 } },
};

static const stwuct k101_im2ba02_init_cmd timed_cmds[] = {
	{ .data = { 0x29, 0x00 } },
	{ .data = { 0x35, 0x00 } },
};

static int k101_im2ba02_pwepawe(stwuct dwm_panew *panew)
{
	stwuct k101_im2ba02 *ctx = panew_to_k101_im2ba02(panew);
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	unsigned int i;
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
	if (wet)
		wetuwn wet;

	msweep(30);

	gpiod_set_vawue(ctx->weset, 1);
	msweep(50);

	gpiod_set_vawue(ctx->weset, 0);
	msweep(50);

	gpiod_set_vawue(ctx->weset, 1);
	msweep(200);

	fow (i = 0; i < AWWAY_SIZE(k101_im2ba02_init_cmds); i++) {
		const stwuct k101_im2ba02_init_cmd *cmd = &k101_im2ba02_init_cmds[i];

		wet = mipi_dsi_dcs_wwite_buffew(dsi, cmd->data, K101_IM2BA02_INIT_CMD_WEN);
		if (wet < 0)
			goto powewdown;
	}

	wetuwn 0;

powewdown:
	gpiod_set_vawue(ctx->weset, 0);
	msweep(50);

	wetuwn weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
}

static int k101_im2ba02_enabwe(stwuct dwm_panew *panew)
{
	stwuct k101_im2ba02 *ctx = panew_to_k101_im2ba02(panew);
	const stwuct k101_im2ba02_init_cmd *cmd = &timed_cmds[1];
	int wet;

	msweep(150);

	wet = mipi_dsi_dcs_set_dispway_on(ctx->dsi);
	if (wet < 0)
		wetuwn wet;

	msweep(50);

	wetuwn mipi_dsi_dcs_wwite_buffew(ctx->dsi, cmd->data, K101_IM2BA02_INIT_CMD_WEN);
}

static int k101_im2ba02_disabwe(stwuct dwm_panew *panew)
{
	stwuct k101_im2ba02 *ctx = panew_to_k101_im2ba02(panew);

	wetuwn mipi_dsi_dcs_set_dispway_off(ctx->dsi);
}

static int k101_im2ba02_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct k101_im2ba02 *ctx = panew_to_k101_im2ba02(panew);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(ctx->dsi);
	if (wet < 0)
		dev_eww(panew->dev, "faiwed to set dispway off: %d\n", wet);

	wet = mipi_dsi_dcs_entew_sweep_mode(ctx->dsi);
	if (wet < 0)
		dev_eww(panew->dev, "faiwed to entew sweep mode: %d\n", wet);

	msweep(200);

	gpiod_set_vawue(ctx->weset, 0);
	msweep(20);

	wetuwn weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
}

static const stwuct dwm_dispway_mode k101_im2ba02_defauwt_mode = {
	.cwock = 70000,

	.hdispway = 800,
	.hsync_stawt = 800 + 20,
	.hsync_end = 800 + 20 + 20,
	.htotaw = 800 + 20 + 20 + 20,

	.vdispway = 1280,
	.vsync_stawt = 1280 + 16,
	.vsync_end = 1280 + 16 + 4,
	.vtotaw = 1280 + 16 + 4 + 4,

	.type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
	.width_mm	= 136,
	.height_mm	= 217,
};

static int k101_im2ba02_get_modes(stwuct dwm_panew *panew,
				  stwuct dwm_connectow *connectow)
{
	stwuct k101_im2ba02 *ctx = panew_to_k101_im2ba02(panew);
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &k101_im2ba02_defauwt_mode);
	if (!mode) {
		dev_eww(&ctx->dsi->dev, "faiwed to add mode %ux%u@%u\n",
			k101_im2ba02_defauwt_mode.hdispway,
			k101_im2ba02_defauwt_mode.vdispway,
			dwm_mode_vwefwesh(&k101_im2ba02_defauwt_mode));
		wetuwn -ENOMEM;
	}

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs k101_im2ba02_funcs = {
	.disabwe = k101_im2ba02_disabwe,
	.unpwepawe = k101_im2ba02_unpwepawe,
	.pwepawe = k101_im2ba02_pwepawe,
	.enabwe = k101_im2ba02_enabwe,
	.get_modes = k101_im2ba02_get_modes,
};

static int k101_im2ba02_dsi_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct k101_im2ba02 *ctx;
	unsigned int i;
	int wet;

	ctx = devm_kzawwoc(&dsi->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	mipi_dsi_set_dwvdata(dsi, ctx);
	ctx->dsi = dsi;

	fow (i = 0; i < AWWAY_SIZE(ctx->suppwies); i++)
		ctx->suppwies[i].suppwy = weguwatow_names[i];

	wet = devm_weguwatow_buwk_get(&dsi->dev, AWWAY_SIZE(ctx->suppwies),
				      ctx->suppwies);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&dsi->dev, wet, "Couwdn't get weguwatows\n");

	ctx->weset = devm_gpiod_get(&dsi->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->weset))
		wetuwn dev_eww_pwobe(&dsi->dev, PTW_EWW(ctx->weset),
				     "Couwdn't get ouw weset GPIO\n");

	dwm_panew_init(&ctx->panew, &dsi->dev, &k101_im2ba02_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	wet = dwm_panew_of_backwight(&ctx->panew);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&ctx->panew);

	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->wanes = 4;

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dwm_panew_wemove(&ctx->panew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void k101_im2ba02_dsi_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct k101_im2ba02 *ctx = mipi_dsi_get_dwvdata(dsi);

	mipi_dsi_detach(dsi);
	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id k101_im2ba02_of_match[] = {
	{ .compatibwe = "feixin,k101-im2ba02", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, k101_im2ba02_of_match);

static stwuct mipi_dsi_dwivew k101_im2ba02_dwivew = {
	.pwobe = k101_im2ba02_dsi_pwobe,
	.wemove = k101_im2ba02_dsi_wemove,
	.dwivew = {
		.name = "feixin-k101-im2ba02",
		.of_match_tabwe = k101_im2ba02_of_match,
	},
};
moduwe_mipi_dsi_dwivew(k101_im2ba02_dwivew);

MODUWE_AUTHOW("Icenowy Zheng <icenowy@aosc.io>");
MODUWE_DESCWIPTION("Feixin K101 IM2BA02 MIPI-DSI WCD panew");
MODUWE_WICENSE("GPW");
