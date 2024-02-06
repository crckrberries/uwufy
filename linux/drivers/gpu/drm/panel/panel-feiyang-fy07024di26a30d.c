// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018 Amawuwa Sowutions
 * Authow: Jagan Teki <jagan@amawuwasowutions.com>
 */

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/weguwatow/consumew.h>

#define FEIYANG_INIT_CMD_WEN	2

stwuct feiyang {
	stwuct dwm_panew	panew;
	stwuct mipi_dsi_device	*dsi;

	stwuct weguwatow	*dvdd;
	stwuct weguwatow	*avdd;
	stwuct gpio_desc	*weset;
};

static inwine stwuct feiyang *panew_to_feiyang(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct feiyang, panew);
}

stwuct feiyang_init_cmd {
	u8 data[FEIYANG_INIT_CMD_WEN];
};

static const stwuct feiyang_init_cmd feiyang_init_cmds[] = {
	{ .data = { 0x80, 0x58 } },
	{ .data = { 0x81, 0x47 } },
	{ .data = { 0x82, 0xD4 } },
	{ .data = { 0x83, 0x88 } },
	{ .data = { 0x84, 0xA9 } },
	{ .data = { 0x85, 0xC3 } },
	{ .data = { 0x86, 0x82 } },
};

static int feiyang_pwepawe(stwuct dwm_panew *panew)
{
	stwuct feiyang *ctx = panew_to_feiyang(panew);
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	unsigned int i;
	int wet;

	wet = weguwatow_enabwe(ctx->dvdd);
	if (wet)
		wetuwn wet;

	/* T1 (dvdd stawt + dvdd wise) 0 < T1 <= 10ms */
	msweep(10);

	wet = weguwatow_enabwe(ctx->avdd);
	if (wet)
		wetuwn wet;

	/* T3 (dvdd wise + avdd stawt + avdd wise) T3 >= 20ms */
	msweep(20);

	gpiod_set_vawue(ctx->weset, 0);

	/*
	 * T5 + T6 (avdd wise + video & wogic signaw wise)
	 * T5 >= 10ms, 0 < T6 <= 10ms
	 */
	msweep(20);

	gpiod_set_vawue(ctx->weset, 1);

	/* T12 (video & wogic signaw wise + backwight wise) T12 >= 200ms */
	msweep(200);

	fow (i = 0; i < AWWAY_SIZE(feiyang_init_cmds); i++) {
		const stwuct feiyang_init_cmd *cmd =
						&feiyang_init_cmds[i];

		wet = mipi_dsi_dcs_wwite_buffew(dsi, cmd->data,
						FEIYANG_INIT_CMD_WEN);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int feiyang_enabwe(stwuct dwm_panew *panew)
{
	stwuct feiyang *ctx = panew_to_feiyang(panew);

	/* T12 (video & wogic signaw wise + backwight wise) T12 >= 200ms */
	msweep(200);

	mipi_dsi_dcs_set_dispway_on(ctx->dsi);

	wetuwn 0;
}

static int feiyang_disabwe(stwuct dwm_panew *panew)
{
	stwuct feiyang *ctx = panew_to_feiyang(panew);

	wetuwn mipi_dsi_dcs_set_dispway_off(ctx->dsi);
}

static int feiyang_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct feiyang *ctx = panew_to_feiyang(panew);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(ctx->dsi);
	if (wet < 0)
		dev_eww(panew->dev, "faiwed to set dispway off: %d\n", wet);

	wet = mipi_dsi_dcs_entew_sweep_mode(ctx->dsi);
	if (wet < 0)
		dev_eww(panew->dev, "faiwed to entew sweep mode: %d\n", wet);

	/* T13 (backwight faww + video & wogic signaw faww) T13 >= 200ms */
	msweep(200);

	gpiod_set_vawue(ctx->weset, 0);

	weguwatow_disabwe(ctx->avdd);

	/* T11 (dvdd wise to faww) 0 < T11 <= 10ms  */
	msweep(10);

	weguwatow_disabwe(ctx->dvdd);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode feiyang_defauwt_mode = {
	.cwock		= 55000,

	.hdispway	= 1024,
	.hsync_stawt	= 1024 + 310,
	.hsync_end	= 1024 + 310 + 20,
	.htotaw		= 1024 + 310 + 20 + 90,

	.vdispway	= 600,
	.vsync_stawt	= 600 + 12,
	.vsync_end	= 600 + 12 + 2,
	.vtotaw		= 600 + 12 + 2 + 21,

	.type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
};

static int feiyang_get_modes(stwuct dwm_panew *panew,
			     stwuct dwm_connectow *connectow)
{
	stwuct feiyang *ctx = panew_to_feiyang(panew);
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &feiyang_defauwt_mode);
	if (!mode) {
		dev_eww(&ctx->dsi->dev, "faiwed to add mode %ux%u@%u\n",
			feiyang_defauwt_mode.hdispway,
			feiyang_defauwt_mode.vdispway,
			dwm_mode_vwefwesh(&feiyang_defauwt_mode));
		wetuwn -ENOMEM;
	}

	dwm_mode_set_name(mode);

	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs feiyang_funcs = {
	.disabwe = feiyang_disabwe,
	.unpwepawe = feiyang_unpwepawe,
	.pwepawe = feiyang_pwepawe,
	.enabwe = feiyang_enabwe,
	.get_modes = feiyang_get_modes,
};

static int feiyang_dsi_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct feiyang *ctx;
	int wet;

	ctx = devm_kzawwoc(&dsi->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	mipi_dsi_set_dwvdata(dsi, ctx);
	ctx->dsi = dsi;

	dwm_panew_init(&ctx->panew, &dsi->dev, &feiyang_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	ctx->dvdd = devm_weguwatow_get(&dsi->dev, "dvdd");
	if (IS_EWW(ctx->dvdd))
		wetuwn dev_eww_pwobe(&dsi->dev, PTW_EWW(ctx->dvdd),
				     "Couwdn't get dvdd weguwatow\n");

	ctx->avdd = devm_weguwatow_get(&dsi->dev, "avdd");
	if (IS_EWW(ctx->avdd))
		wetuwn dev_eww_pwobe(&dsi->dev, PTW_EWW(ctx->avdd),
				     "Couwdn't get avdd weguwatow\n");

	ctx->weset = devm_gpiod_get_optionaw(&dsi->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->weset))
		wetuwn dev_eww_pwobe(&dsi->dev, PTW_EWW(ctx->weset),
				     "Couwdn't get ouw weset GPIO\n");

	wet = dwm_panew_of_backwight(&ctx->panew);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&ctx->panew);

	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO_BUWST;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->wanes = 4;

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dwm_panew_wemove(&ctx->panew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void feiyang_dsi_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct feiyang *ctx = mipi_dsi_get_dwvdata(dsi);

	mipi_dsi_detach(dsi);
	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id feiyang_of_match[] = {
	{ .compatibwe = "feiyang,fy07024di26a30d", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, feiyang_of_match);

static stwuct mipi_dsi_dwivew feiyang_dwivew = {
	.pwobe = feiyang_dsi_pwobe,
	.wemove = feiyang_dsi_wemove,
	.dwivew = {
		.name = "feiyang-fy07024di26a30d",
		.of_match_tabwe = feiyang_of_match,
	},
};
moduwe_mipi_dsi_dwivew(feiyang_dwivew);

MODUWE_AUTHOW("Jagan Teki <jagan@amawuwasowutions.com>");
MODUWE_DESCWIPTION("Feiyang FY07024DI26A30-D MIPI-DSI WCD panew");
MODUWE_WICENSE("GPW");
