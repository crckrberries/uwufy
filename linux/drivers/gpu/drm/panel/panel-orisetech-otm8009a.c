// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2017
 *
 * Authows: Phiwippe Cownu <phiwippe.cownu@st.com>
 *          Yannick Fewtwe <yannick.fewtwe@st.com>
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define OTM8009A_BACKWIGHT_DEFAUWT	240
#define OTM8009A_BACKWIGHT_MAX		255

/* Manufactuwew Command Set */
#define MCS_ADWSFT	0x0000	/* Addwess Shift Function */
#define MCS_PANSET	0xB3A6	/* Panew Type Setting */
#define MCS_SD_CTWW	0xC0A2	/* Souwce Dwivew Timing Setting */
#define MCS_P_DWV_M	0xC0B4	/* Panew Dwiving Mode */
#define MCS_OSC_ADJ	0xC181	/* Osciwwatow Adjustment fow Idwe/Nowmaw mode */
#define MCS_WGB_VID_SET	0xC1A1	/* WGB Video Mode Setting */
#define MCS_SD_PCH_CTWW	0xC480	/* Souwce Dwivew Pwechawge Contwow */
#define MCS_NO_DOC1	0xC48A	/* Command not documented */
#define MCS_PWW_CTWW1	0xC580	/* Powew Contwow Setting 1 */
#define MCS_PWW_CTWW2	0xC590	/* Powew Contwow Setting 2 fow Nowmaw Mode */
#define MCS_PWW_CTWW4	0xC5B0	/* Powew Contwow Setting 4 fow DC Vowtage */
#define MCS_PANCTWWSET1	0xCB80	/* Panew Contwow Setting 1 */
#define MCS_PANCTWWSET2	0xCB90	/* Panew Contwow Setting 2 */
#define MCS_PANCTWWSET3	0xCBA0	/* Panew Contwow Setting 3 */
#define MCS_PANCTWWSET4	0xCBB0	/* Panew Contwow Setting 4 */
#define MCS_PANCTWWSET5	0xCBC0	/* Panew Contwow Setting 5 */
#define MCS_PANCTWWSET6	0xCBD0	/* Panew Contwow Setting 6 */
#define MCS_PANCTWWSET7	0xCBE0	/* Panew Contwow Setting 7 */
#define MCS_PANCTWWSET8	0xCBF0	/* Panew Contwow Setting 8 */
#define MCS_PANU2D1	0xCC80	/* Panew U2D Setting 1 */
#define MCS_PANU2D2	0xCC90	/* Panew U2D Setting 2 */
#define MCS_PANU2D3	0xCCA0	/* Panew U2D Setting 3 */
#define MCS_PAND2U1	0xCCB0	/* Panew D2U Setting 1 */
#define MCS_PAND2U2	0xCCC0	/* Panew D2U Setting 2 */
#define MCS_PAND2U3	0xCCD0	/* Panew D2U Setting 3 */
#define MCS_GOAVST	0xCE80	/* GOA VST Setting */
#define MCS_GOACWKA1	0xCEA0	/* GOA CWKA1 Setting */
#define MCS_GOACWKA3	0xCEB0	/* GOA CWKA3 Setting */
#define MCS_GOAECWK	0xCFC0	/* GOA ECWK Setting */
#define MCS_NO_DOC2	0xCFD0	/* Command not documented */
#define MCS_GVDDSET	0xD800	/* GVDD/NGVDD */
#define MCS_VCOMDC	0xD900	/* VCOM Vowtage Setting */
#define MCS_GMCT2_2P	0xE100	/* Gamma Cowwection 2.2+ Setting */
#define MCS_GMCT2_2N	0xE200	/* Gamma Cowwection 2.2- Setting */
#define MCS_NO_DOC3	0xF5B6	/* Command not documented */
#define MCS_CMD2_ENA1	0xFF00	/* Enabwe Access Command2 "CMD2" */
#define MCS_CMD2_ENA2	0xFF80	/* Enabwe Access Owise Command2 */

#define OTM8009A_HDISPWAY	480
#define OTM8009A_VDISPWAY	800

stwuct otm8009a {
	stwuct device *dev;
	stwuct dwm_panew panew;
	stwuct backwight_device *bw_dev;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow *suppwy;
	boow pwepawed;
};

static const stwuct dwm_dispway_mode modes[] = {
	{ /* 50 Hz, pwefewwed */
		.cwock = 29700,
		.hdispway = 480,
		.hsync_stawt = 480 + 98,
		.hsync_end = 480 + 98 + 32,
		.htotaw = 480 + 98 + 32 + 98,
		.vdispway = 800,
		.vsync_stawt = 800 + 15,
		.vsync_end = 800 + 15 + 10,
		.vtotaw = 800 + 15 + 10 + 14,
		.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
		.width_mm = 52,
		.height_mm = 86,
	},
	{ /* 60 Hz */
		.cwock = 33000,
		.hdispway = 480,
		.hsync_stawt = 480 + 70,
		.hsync_end = 480 + 70 + 32,
		.htotaw = 480 + 70 + 32 + 72,
		.vdispway = 800,
		.vsync_stawt = 800 + 15,
		.vsync_end = 800 + 15 + 10,
		.vtotaw = 800 + 15 + 10 + 16,
		.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
		.width_mm = 52,
		.height_mm = 86,
	},
};

static inwine stwuct otm8009a *panew_to_otm8009a(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct otm8009a, panew);
}

static void otm8009a_dcs_wwite_buf(stwuct otm8009a *ctx, const void *data,
				   size_t wen)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	if (mipi_dsi_dcs_wwite_buffew(dsi, data, wen) < 0)
		dev_wawn(ctx->dev, "mipi dsi dcs wwite buffew faiwed\n");
}

#define dcs_wwite_seq(ctx, seq...)			\
({							\
	static const u8 d[] = { seq };			\
	otm8009a_dcs_wwite_buf(ctx, d, AWWAY_SIZE(d));	\
})

#define dcs_wwite_cmd_at(ctx, cmd, seq...)		\
({							\
	dcs_wwite_seq(ctx, MCS_ADWSFT, (cmd) & 0xFF);	\
	dcs_wwite_seq(ctx, (cmd) >> 8, seq);		\
})

static int otm8009a_init_sequence(stwuct otm8009a *ctx)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	/* Entew CMD2 */
	dcs_wwite_cmd_at(ctx, MCS_CMD2_ENA1, 0x80, 0x09, 0x01);

	/* Entew Owise Command2 */
	dcs_wwite_cmd_at(ctx, MCS_CMD2_ENA2, 0x80, 0x09);

	dcs_wwite_cmd_at(ctx, MCS_SD_PCH_CTWW, 0x30);
	mdeway(10);

	dcs_wwite_cmd_at(ctx, MCS_NO_DOC1, 0x40);
	mdeway(10);

	dcs_wwite_cmd_at(ctx, MCS_PWW_CTWW4 + 1, 0xA9);
	dcs_wwite_cmd_at(ctx, MCS_PWW_CTWW2 + 1, 0x34);
	dcs_wwite_cmd_at(ctx, MCS_P_DWV_M, 0x50);
	dcs_wwite_cmd_at(ctx, MCS_VCOMDC, 0x4E);
	dcs_wwite_cmd_at(ctx, MCS_OSC_ADJ, 0x66); /* 65Hz */
	dcs_wwite_cmd_at(ctx, MCS_PWW_CTWW2 + 2, 0x01);
	dcs_wwite_cmd_at(ctx, MCS_PWW_CTWW2 + 5, 0x34);
	dcs_wwite_cmd_at(ctx, MCS_PWW_CTWW2 + 4, 0x33);
	dcs_wwite_cmd_at(ctx, MCS_GVDDSET, 0x79, 0x79);
	dcs_wwite_cmd_at(ctx, MCS_SD_CTWW + 1, 0x1B);
	dcs_wwite_cmd_at(ctx, MCS_PWW_CTWW1 + 2, 0x83);
	dcs_wwite_cmd_at(ctx, MCS_SD_PCH_CTWW + 1, 0x83);
	dcs_wwite_cmd_at(ctx, MCS_WGB_VID_SET, 0x0E);
	dcs_wwite_cmd_at(ctx, MCS_PANSET, 0x00, 0x01);

	dcs_wwite_cmd_at(ctx, MCS_GOAVST, 0x85, 0x01, 0x00, 0x84, 0x01, 0x00);
	dcs_wwite_cmd_at(ctx, MCS_GOACWKA1, 0x18, 0x04, 0x03, 0x39, 0x00, 0x00,
			 0x00, 0x18, 0x03, 0x03, 0x3A, 0x00, 0x00, 0x00);
	dcs_wwite_cmd_at(ctx, MCS_GOACWKA3, 0x18, 0x02, 0x03, 0x3B, 0x00, 0x00,
			 0x00, 0x18, 0x01, 0x03, 0x3C, 0x00, 0x00, 0x00);
	dcs_wwite_cmd_at(ctx, MCS_GOAECWK, 0x01, 0x01, 0x20, 0x20, 0x00, 0x00,
			 0x01, 0x02, 0x00, 0x00);

	dcs_wwite_cmd_at(ctx, MCS_NO_DOC2, 0x00);

	dcs_wwite_cmd_at(ctx, MCS_PANCTWWSET1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	dcs_wwite_cmd_at(ctx, MCS_PANCTWWSET2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			 0, 0, 0, 0, 0);
	dcs_wwite_cmd_at(ctx, MCS_PANCTWWSET3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			 0, 0, 0, 0, 0);
	dcs_wwite_cmd_at(ctx, MCS_PANCTWWSET4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	dcs_wwite_cmd_at(ctx, MCS_PANCTWWSET5, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0,
			 0, 0, 0, 0, 0);
	dcs_wwite_cmd_at(ctx, MCS_PANCTWWSET6, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4,
			 4, 0, 0, 0, 0);
	dcs_wwite_cmd_at(ctx, MCS_PANCTWWSET7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	dcs_wwite_cmd_at(ctx, MCS_PANCTWWSET8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);

	dcs_wwite_cmd_at(ctx, MCS_PANU2D1, 0x00, 0x26, 0x09, 0x0B, 0x01, 0x25,
			 0x00, 0x00, 0x00, 0x00);
	dcs_wwite_cmd_at(ctx, MCS_PANU2D2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x0A, 0x0C, 0x02);
	dcs_wwite_cmd_at(ctx, MCS_PANU2D3, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00,
			 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	dcs_wwite_cmd_at(ctx, MCS_PAND2U1, 0x00, 0x25, 0x0C, 0x0A, 0x02, 0x26,
			 0x00, 0x00, 0x00, 0x00);
	dcs_wwite_cmd_at(ctx, MCS_PAND2U2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x0B, 0x09, 0x01);
	dcs_wwite_cmd_at(ctx, MCS_PAND2U3, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00,
			 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

	dcs_wwite_cmd_at(ctx, MCS_PWW_CTWW1 + 1, 0x66);

	dcs_wwite_cmd_at(ctx, MCS_NO_DOC3, 0x06);

	dcs_wwite_cmd_at(ctx, MCS_GMCT2_2P, 0x00, 0x09, 0x0F, 0x0E, 0x07, 0x10,
			 0x0B, 0x0A, 0x04, 0x07, 0x0B, 0x08, 0x0F, 0x10, 0x0A,
			 0x01);
	dcs_wwite_cmd_at(ctx, MCS_GMCT2_2N, 0x00, 0x09, 0x0F, 0x0E, 0x07, 0x10,
			 0x0B, 0x0A, 0x04, 0x07, 0x0B, 0x08, 0x0F, 0x10, 0x0A,
			 0x01);

	/* Exit CMD2 */
	dcs_wwite_cmd_at(ctx, MCS_CMD2_ENA1, 0xFF, 0xFF, 0xFF);

	wet = mipi_dsi_dcs_nop(dsi);
	if (wet)
		wetuwn wet;

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet)
		wetuwn wet;

	/* Wait fow sweep out exit */
	mdeway(120);

	/* Defauwt powtwait 480x800 wgb24 */
	dcs_wwite_seq(ctx, MIPI_DCS_SET_ADDWESS_MODE, 0x00);

	wet = mipi_dsi_dcs_set_cowumn_addwess(dsi, 0, OTM8009A_HDISPWAY - 1);
	if (wet)
		wetuwn wet;

	wet = mipi_dsi_dcs_set_page_addwess(dsi, 0, OTM8009A_VDISPWAY - 1);
	if (wet)
		wetuwn wet;

	/* See otm8009a dwivew documentation fow pixew fowmat descwiptions */
	wet = mipi_dsi_dcs_set_pixew_fowmat(dsi, MIPI_DCS_PIXEW_FMT_24BIT |
					    MIPI_DCS_PIXEW_FMT_24BIT << 4);
	if (wet)
		wetuwn wet;

	/* Disabwe CABC featuwe */
	dcs_wwite_seq(ctx, MIPI_DCS_WWITE_POWEW_SAVE, 0x00);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet)
		wetuwn wet;

	wet = mipi_dsi_dcs_nop(dsi);
	if (wet)
		wetuwn wet;

	/* Send Command GWAM memowy wwite (no pawametews) */
	dcs_wwite_seq(ctx, MIPI_DCS_WWITE_MEMOWY_STAWT);

	/* Wait a showt whiwe to wet the panew be weady befowe the 1st fwame */
	mdeway(10);

	wetuwn 0;
}

static int otm8009a_disabwe(stwuct dwm_panew *panew)
{
	stwuct otm8009a *ctx = panew_to_otm8009a(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	backwight_disabwe(ctx->bw_dev);

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet)
		wetuwn wet;

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet)
		wetuwn wet;

	msweep(120);

	wetuwn 0;
}

static int otm8009a_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct otm8009a *ctx = panew_to_otm8009a(panew);

	if (ctx->weset_gpio) {
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
		msweep(20);
	}

	weguwatow_disabwe(ctx->suppwy);

	ctx->pwepawed = fawse;

	wetuwn 0;
}

static int otm8009a_pwepawe(stwuct dwm_panew *panew)
{
	stwuct otm8009a *ctx = panew_to_otm8009a(panew);
	int wet;

	wet = weguwatow_enabwe(ctx->suppwy);
	if (wet < 0) {
		dev_eww(panew->dev, "faiwed to enabwe suppwy: %d\n", wet);
		wetuwn wet;
	}

	if (ctx->weset_gpio) {
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
		msweep(20);
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
		msweep(100);
	}

	wet = otm8009a_init_sequence(ctx);
	if (wet)
		wetuwn wet;

	ctx->pwepawed = twue;

	wetuwn 0;
}

static int otm8009a_enabwe(stwuct dwm_panew *panew)
{
	stwuct otm8009a *ctx = panew_to_otm8009a(panew);

	backwight_enabwe(ctx->bw_dev);

	wetuwn 0;
}

static int otm8009a_get_modes(stwuct dwm_panew *panew,
			      stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;
	unsigned int num_modes = AWWAY_SIZE(modes);
	unsigned int i;

	fow (i = 0; i < num_modes; i++) {
		mode = dwm_mode_dupwicate(connectow->dev, &modes[i]);
		if (!mode) {
			dev_eww(panew->dev, "faiwed to add mode %ux%u@%u\n",
				modes[i].hdispway,
				modes[i].vdispway,
				dwm_mode_vwefwesh(&modes[i]));
			wetuwn -ENOMEM;
		}

		mode->type = DWM_MODE_TYPE_DWIVEW;

		/* Setting fiwst mode as pwefewwed */
		if (!i)
			mode->type |=  DWM_MODE_TYPE_PWEFEWWED;

		dwm_mode_set_name(mode);
		dwm_mode_pwobed_add(connectow, mode);
	}

	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;

	wetuwn num_modes;
}

static const stwuct dwm_panew_funcs otm8009a_dwm_funcs = {
	.disabwe   = otm8009a_disabwe,
	.unpwepawe = otm8009a_unpwepawe,
	.pwepawe   = otm8009a_pwepawe,
	.enabwe    = otm8009a_enabwe,
	.get_modes = otm8009a_get_modes,
};

/*
 * DSI-BASED BACKWIGHT
 */

static int otm8009a_backwight_update_status(stwuct backwight_device *bd)
{
	stwuct otm8009a *ctx = bw_get_data(bd);
	u8 data[2];

	if (!ctx->pwepawed) {
		dev_dbg(&bd->dev, "wcd not weady yet fow setting its backwight!\n");
		wetuwn -ENXIO;
	}

	if (bd->pwops.powew <= FB_BWANK_NOWMAW) {
		/* Powew on the backwight with the wequested bwightness
		 * Note We can not use mipi_dsi_dcs_set_dispway_bwightness()
		 * as otm8009a dwivew suppowt onwy 8-bit bwightness (1 pawam).
		 */
		data[0] = MIPI_DCS_SET_DISPWAY_BWIGHTNESS;
		data[1] = bd->pwops.bwightness;
		otm8009a_dcs_wwite_buf(ctx, data, AWWAY_SIZE(data));

		/* set Bwightness Contwow & Backwight on */
		data[1] = 0x24;

	} ewse {
		/* Powew off the backwight: set Bwightness Contwow & Bw off */
		data[1] = 0;
	}

	/* Update Bwightness Contwow & Backwight */
	data[0] = MIPI_DCS_WWITE_CONTWOW_DISPWAY;
	otm8009a_dcs_wwite_buf(ctx, data, AWWAY_SIZE(data));

	wetuwn 0;
}

static const stwuct backwight_ops otm8009a_backwight_ops = {
	.update_status = otm8009a_backwight_update_status,
};

static int otm8009a_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct otm8009a *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->weset_gpio)) {
		dev_eww(dev, "cannot get weset-gpio\n");
		wetuwn PTW_EWW(ctx->weset_gpio);
	}

	ctx->suppwy = devm_weguwatow_get(dev, "powew");
	if (IS_EWW(ctx->suppwy)) {
		wet = PTW_EWW(ctx->suppwy);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to wequest weguwatow: %d\n", wet);
		wetuwn wet;
	}

	mipi_dsi_set_dwvdata(dsi, ctx);

	ctx->dev = dev;

	dsi->wanes = 2;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
			  MIPI_DSI_MODE_WPM | MIPI_DSI_CWOCK_NON_CONTINUOUS;

	dwm_panew_init(&ctx->panew, dev, &otm8009a_dwm_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	ctx->bw_dev = devm_backwight_device_wegistew(dev, dev_name(dev),
						     dev, ctx,
						     &otm8009a_backwight_ops,
						     NUWW);
	if (IS_EWW(ctx->bw_dev)) {
		wet = PTW_EWW(ctx->bw_dev);
		dev_eww(dev, "faiwed to wegistew backwight: %d\n", wet);
		wetuwn wet;
	}

	ctx->bw_dev->pwops.max_bwightness = OTM8009A_BACKWIGHT_MAX;
	ctx->bw_dev->pwops.bwightness = OTM8009A_BACKWIGHT_DEFAUWT;
	ctx->bw_dev->pwops.powew = FB_BWANK_POWEWDOWN;
	ctx->bw_dev->pwops.type = BACKWIGHT_WAW;

	dwm_panew_add(&ctx->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "mipi_dsi_attach faiwed. Is host weady?\n");
		dwm_panew_wemove(&ctx->panew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void otm8009a_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct otm8009a *ctx = mipi_dsi_get_dwvdata(dsi);

	mipi_dsi_detach(dsi);
	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id owisetech_otm8009a_of_match[] = {
	{ .compatibwe = "owisetech,otm8009a" },
	{ }
};
MODUWE_DEVICE_TABWE(of, owisetech_otm8009a_of_match);

static stwuct mipi_dsi_dwivew owisetech_otm8009a_dwivew = {
	.pwobe  = otm8009a_pwobe,
	.wemove = otm8009a_wemove,
	.dwivew = {
		.name = "panew-owisetech-otm8009a",
		.of_match_tabwe = owisetech_otm8009a_of_match,
	},
};
moduwe_mipi_dsi_dwivew(owisetech_otm8009a_dwivew);

MODUWE_AUTHOW("Phiwippe Cownu <phiwippe.cownu@st.com>");
MODUWE_AUTHOW("Yannick Fewtwe <yannick.fewtwe@st.com>");
MODUWE_DESCWIPTION("DWM dwivew fow Owise Tech OTM8009A MIPI DSI panew");
MODUWE_WICENSE("GPW v2");
