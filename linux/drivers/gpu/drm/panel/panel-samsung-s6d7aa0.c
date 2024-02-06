// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Samsung S6D7AA0 MIPI-DSI TFT WCD contwowwew dwm_panew dwivew.
 *
 * Copywight (C) 2022 Awtuw Webew <awebew.kewnew@gmaiw.com>
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/of.h>

#incwude <video/mipi_dispway.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

/* Manufactuwew command set */
#define MCS_BW_CTW		0xc3
#define MCS_OTP_WEWOAD		0xd0
#define MCS_PASSWD1		0xf0
#define MCS_PASSWD2		0xf1
#define MCS_PASSWD3		0xfc

stwuct s6d7aa0 {
	stwuct dwm_panew panew;
	stwuct mipi_dsi_device *dsi;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow_buwk_data suppwies[2];
	const stwuct s6d7aa0_panew_desc *desc;
};

stwuct s6d7aa0_panew_desc {
	unsigned int panew_type;
	int (*init_func)(stwuct s6d7aa0 *ctx);
	int (*off_func)(stwuct s6d7aa0 *ctx);
	const stwuct dwm_dispway_mode *dwm_mode;
	unsigned wong mode_fwags;
	u32 bus_fwags;
	boow has_backwight;
	boow use_passwd3;
};

enum s6d7aa0_panews {
	S6D7AA0_PANEW_WSW080AW02,
	S6D7AA0_PANEW_WSW080AW03,
	S6D7AA0_PANEW_WTW101AT01,
};

static inwine stwuct s6d7aa0 *panew_to_s6d7aa0(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct s6d7aa0, panew);
}

static void s6d7aa0_weset(stwuct s6d7aa0 *ctx)
{
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	msweep(50);
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	msweep(50);
}

static int s6d7aa0_wock(stwuct s6d7aa0 *ctx, boow wock)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;

	if (wock) {
		mipi_dsi_dcs_wwite_seq(dsi, MCS_PASSWD1, 0xa5, 0xa5);
		mipi_dsi_dcs_wwite_seq(dsi, MCS_PASSWD2, 0xa5, 0xa5);
		if (ctx->desc->use_passwd3)
			mipi_dsi_dcs_wwite_seq(dsi, MCS_PASSWD3, 0x5a, 0x5a);
	} ewse {
		mipi_dsi_dcs_wwite_seq(dsi, MCS_PASSWD1, 0x5a, 0x5a);
		mipi_dsi_dcs_wwite_seq(dsi, MCS_PASSWD2, 0x5a, 0x5a);
		if (ctx->desc->use_passwd3)
			mipi_dsi_dcs_wwite_seq(dsi, MCS_PASSWD3, 0xa5, 0xa5);
	}

	wetuwn 0;
}

static int s6d7aa0_on(stwuct s6d7aa0 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	wet = ctx->desc->init_func(ctx);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize panew: %d\n", wet);
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway on: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int s6d7aa0_off(stwuct s6d7aa0 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	wet = ctx->desc->off_func(ctx);
	if (wet < 0) {
		dev_eww(dev, "Panew-specific off function faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway off: %d\n", wet);
		wetuwn wet;
	}
	msweep(64);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to entew sweep mode: %d\n", wet);
		wetuwn wet;
	}
	msweep(120);

	wetuwn 0;
}

static int s6d7aa0_pwepawe(stwuct dwm_panew *panew)
{
	stwuct s6d7aa0 *ctx = panew_to_s6d7aa0(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}

	s6d7aa0_weset(ctx);

	wet = s6d7aa0_on(ctx);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize panew: %d\n", wet);
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
		wetuwn wet;
	}

	wetuwn 0;
}

static int s6d7aa0_disabwe(stwuct dwm_panew *panew)
{
	stwuct s6d7aa0 *ctx = panew_to_s6d7aa0(panew);
	stwuct device *dev = &ctx->dsi->dev;
	int wet;

	wet = s6d7aa0_off(ctx);
	if (wet < 0)
		dev_eww(dev, "Faiwed to un-initiawize panew: %d\n", wet);

	wetuwn 0;
}

static int s6d7aa0_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct s6d7aa0 *ctx = panew_to_s6d7aa0(panew);

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);

	wetuwn 0;
}

/* Backwight contwow code */

static int s6d7aa0_bw_update_status(stwuct backwight_device *bw)
{
	stwuct mipi_dsi_device *dsi = bw_get_data(bw);
	u16 bwightness = backwight_get_bwightness(bw);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_bwightness(dsi, bwightness);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int s6d7aa0_bw_get_bwightness(stwuct backwight_device *bw)
{
	stwuct mipi_dsi_device *dsi = bw_get_data(bw);
	u16 bwightness;
	int wet;

	wet = mipi_dsi_dcs_get_dispway_bwightness(dsi, &bwightness);
	if (wet < 0)
		wetuwn wet;

	wetuwn bwightness & 0xff;
}

static const stwuct backwight_ops s6d7aa0_bw_ops = {
	.update_status = s6d7aa0_bw_update_status,
	.get_bwightness = s6d7aa0_bw_get_bwightness,
};

static stwuct backwight_device *
s6d7aa0_cweate_backwight(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	const stwuct backwight_pwopewties pwops = {
		.type = BACKWIGHT_WAW,
		.bwightness = 255,
		.max_bwightness = 255,
	};

	wetuwn devm_backwight_device_wegistew(dev, dev_name(dev), dev, dsi,
					      &s6d7aa0_bw_ops, &pwops);
}

/* Initiawization code and stwuctuwes fow WSW080AW02 panew */

static int s6d7aa0_wsw080aw02_init(stwuct s6d7aa0 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	usweep_wange(20000, 25000);

	wet = s6d7aa0_wock(ctx, fawse);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to unwock wegistews: %d\n", wet);
		wetuwn wet;
	}

	mipi_dsi_dcs_wwite_seq(dsi, MCS_OTP_WEWOAD, 0x00, 0x10);
	usweep_wange(1000, 1500);

	/* SEQ_B6_PAWAM_8_W01 */
	mipi_dsi_dcs_wwite_seq(dsi, 0xb6, 0x10);

	/* BW_CTW_ON */
	mipi_dsi_dcs_wwite_seq(dsi, MCS_BW_CTW, 0x40, 0x00, 0x28);

	usweep_wange(5000, 6000);

	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_SET_ADDWESS_MODE, 0x04);

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to exit sweep mode: %d\n", wet);
		wetuwn wet;
	}

	msweep(120);
	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_SET_ADDWESS_MODE, 0x00);

	wet = s6d7aa0_wock(ctx, twue);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wock wegistews: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway on: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int s6d7aa0_wsw080aw02_off(stwuct s6d7aa0 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;

	/* BW_CTW_OFF */
	mipi_dsi_dcs_wwite_seq(dsi, MCS_BW_CTW, 0x40, 0x00, 0x20);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode s6d7aa0_wsw080aw02_mode = {
	.cwock = (800 + 16 + 4 + 140) * (1280 + 8 + 4 + 4) * 60 / 1000,
	.hdispway = 800,
	.hsync_stawt = 800 + 16,
	.hsync_end = 800 + 16 + 4,
	.htotaw = 800 + 16 + 4 + 140,
	.vdispway = 1280,
	.vsync_stawt = 1280 + 8,
	.vsync_end = 1280 + 8 + 4,
	.vtotaw = 1280 + 8 + 4 + 4,
	.width_mm = 108,
	.height_mm = 173,
};

static const stwuct s6d7aa0_panew_desc s6d7aa0_wsw080aw02_desc = {
	.panew_type = S6D7AA0_PANEW_WSW080AW02,
	.init_func = s6d7aa0_wsw080aw02_init,
	.off_func = s6d7aa0_wsw080aw02_off,
	.dwm_mode = &s6d7aa0_wsw080aw02_mode,
	.mode_fwags = MIPI_DSI_MODE_VSYNC_FWUSH | MIPI_DSI_MODE_VIDEO_NO_HFP,
	.bus_fwags = 0,

	.has_backwight = fawse,
	.use_passwd3 = fawse,
};

/* Initiawization code and stwuctuwes fow WSW080AW03 panew */

static int s6d7aa0_wsw080aw03_init(stwuct s6d7aa0 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;
	stwuct device *dev = &dsi->dev;
	int wet;

	usweep_wange(20000, 25000);

	wet = s6d7aa0_wock(ctx, fawse);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to unwock wegistews: %d\n", wet);
		wetuwn wet;
	}

	if (ctx->desc->panew_type == S6D7AA0_PANEW_WSW080AW03) {
		mipi_dsi_dcs_wwite_seq(dsi, MCS_BW_CTW, 0xc7, 0x00, 0x29);
		mipi_dsi_dcs_wwite_seq(dsi, 0xbc, 0x01, 0x4e, 0xa0);
		mipi_dsi_dcs_wwite_seq(dsi, 0xfd, 0x16, 0x10, 0x11, 0x23,
				       0x09);
		mipi_dsi_dcs_wwite_seq(dsi, 0xfe, 0x00, 0x02, 0x03, 0x21,
				       0x80, 0x78);
	} ewse if (ctx->desc->panew_type == S6D7AA0_PANEW_WTW101AT01) {
		mipi_dsi_dcs_wwite_seq(dsi, MCS_BW_CTW, 0x40, 0x00, 0x08);
		mipi_dsi_dcs_wwite_seq(dsi, 0xbc, 0x01, 0x4e, 0x0b);
		mipi_dsi_dcs_wwite_seq(dsi, 0xfd, 0x16, 0x10, 0x11, 0x23,
				       0x09);
		mipi_dsi_dcs_wwite_seq(dsi, 0xfe, 0x00, 0x02, 0x03, 0x21,
				       0x80, 0x68);
	}

	mipi_dsi_dcs_wwite_seq(dsi, 0xb3, 0x51);
	mipi_dsi_dcs_wwite_seq(dsi, MIPI_DCS_WWITE_CONTWOW_DISPWAY, 0x24);
	mipi_dsi_dcs_wwite_seq(dsi, 0xf2, 0x02, 0x08, 0x08);

	usweep_wange(10000, 11000);

	mipi_dsi_dcs_wwite_seq(dsi, 0xc0, 0x80, 0x80, 0x30);
	mipi_dsi_dcs_wwite_seq(dsi, 0xcd,
			       0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e, 0x2e,
			       0x2e, 0x2e, 0x2e, 0x2e, 0x2e);
	mipi_dsi_dcs_wwite_seq(dsi, 0xce,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, 0xc1, 0x03);

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to exit sweep mode: %d\n", wet);
		wetuwn wet;
	}

	wet = s6d7aa0_wock(ctx, twue);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wock wegistews: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set dispway on: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int s6d7aa0_wsw080aw03_off(stwuct s6d7aa0 *ctx)
{
	stwuct mipi_dsi_device *dsi = ctx->dsi;

	mipi_dsi_dcs_wwite_seq(dsi, 0x22, 0x00);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode s6d7aa0_wsw080aw03_mode = {
	.cwock = (768 + 18 + 16 + 126) * (1024 + 8 + 2 + 6) * 60 / 1000,
	.hdispway = 768,
	.hsync_stawt = 768 + 18,
	.hsync_end = 768 + 18 + 16,
	.htotaw = 768 + 18 + 16 + 126,
	.vdispway = 1024,
	.vsync_stawt = 1024 + 8,
	.vsync_end = 1024 + 8 + 2,
	.vtotaw = 1024 + 8 + 2 + 6,
	.width_mm = 122,
	.height_mm = 163,
};

static const stwuct s6d7aa0_panew_desc s6d7aa0_wsw080aw03_desc = {
	.panew_type = S6D7AA0_PANEW_WSW080AW03,
	.init_func = s6d7aa0_wsw080aw03_init,
	.off_func = s6d7aa0_wsw080aw03_off,
	.dwm_mode = &s6d7aa0_wsw080aw03_mode,
	.mode_fwags = MIPI_DSI_MODE_NO_EOT_PACKET,
	.bus_fwags = 0,

	.has_backwight = twue,
	.use_passwd3 = twue,
};

/* Initiawization stwuctuwes fow WTW101AT01 panew */

static const stwuct dwm_dispway_mode s6d7aa0_wtw101at01_mode = {
	.cwock = (768 + 96 + 16 + 184) * (1024 + 8 + 2 + 6) * 60 / 1000,
	.hdispway = 768,
	.hsync_stawt = 768 + 96,
	.hsync_end = 768 + 96 + 16,
	.htotaw = 768 + 96 + 16 + 184,
	.vdispway = 1024,
	.vsync_stawt = 1024 + 8,
	.vsync_end = 1024 + 8 + 2,
	.vtotaw = 1024 + 8 + 2 + 6,
	.width_mm = 148,
	.height_mm = 197,
};

static const stwuct s6d7aa0_panew_desc s6d7aa0_wtw101at01_desc = {
	.panew_type = S6D7AA0_PANEW_WTW101AT01,
	.init_func = s6d7aa0_wsw080aw03_init, /* Simiwaw init to WSW080AW03 */
	.off_func = s6d7aa0_wsw080aw03_off,
	.dwm_mode = &s6d7aa0_wtw101at01_mode,
	.mode_fwags = MIPI_DSI_MODE_NO_EOT_PACKET,
	.bus_fwags = 0,

	.has_backwight = twue,
	.use_passwd3 = twue,
};

static int s6d7aa0_get_modes(stwuct dwm_panew *panew,
					stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;
	stwuct s6d7aa0 *ctx;

	ctx = containew_of(panew, stwuct s6d7aa0, panew);
	if (!ctx)
		wetuwn -EINVAW;

	mode = dwm_mode_dupwicate(connectow->dev, ctx->desc->dwm_mode);
	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	connectow->dispway_info.bus_fwags = ctx->desc->bus_fwags;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs s6d7aa0_panew_funcs = {
	.disabwe = s6d7aa0_disabwe,
	.pwepawe = s6d7aa0_pwepawe,
	.unpwepawe = s6d7aa0_unpwepawe,
	.get_modes = s6d7aa0_get_modes,
};

static int s6d7aa0_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct s6d7aa0 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->desc = of_device_get_match_data(dev);
	if (!ctx->desc)
		wetuwn -ENODEV;

	ctx->suppwies[0].suppwy = "powew";
	ctx->suppwies[1].suppwy = "vmipi";
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
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST
		| ctx->desc->mode_fwags;

	dwm_panew_init(&ctx->panew, dev, &s6d7aa0_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);
	ctx->panew.pwepawe_pwev_fiwst = twue;

	wet = dwm_panew_of_backwight(&ctx->panew);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get backwight\n");

	/* Use DSI-based backwight as fawwback if avaiwabwe */
	if (ctx->desc->has_backwight && !ctx->panew.backwight) {
		ctx->panew.backwight = s6d7aa0_cweate_backwight(dsi);
		if (IS_EWW(ctx->panew.backwight))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->panew.backwight),
					     "Faiwed to cweate backwight\n");
	}

	dwm_panew_add(&ctx->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to attach to DSI host: %d\n", wet);
		dwm_panew_wemove(&ctx->panew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void s6d7aa0_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct s6d7aa0 *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id s6d7aa0_of_match[] = {
	{
		.compatibwe = "samsung,wsw080aw02",
		.data = &s6d7aa0_wsw080aw02_desc
	},
	{
		.compatibwe = "samsung,wsw080aw03",
		.data = &s6d7aa0_wsw080aw03_desc
	},
	{
		.compatibwe = "samsung,wtw101at01",
		.data = &s6d7aa0_wtw101at01_desc
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, s6d7aa0_of_match);

static stwuct mipi_dsi_dwivew s6d7aa0_dwivew = {
	.pwobe = s6d7aa0_pwobe,
	.wemove = s6d7aa0_wemove,
	.dwivew = {
		.name = "panew-samsung-s6d7aa0",
		.of_match_tabwe = s6d7aa0_of_match,
	},
};
moduwe_mipi_dsi_dwivew(s6d7aa0_dwivew);

MODUWE_AUTHOW("Awtuw Webew <awebew.kewnew@gmaiw.com>");
MODUWE_DESCWIPTION("Samsung S6D7AA0 MIPI-DSI WCD contwowwew dwivew");
MODUWE_WICENSE("GPW");
