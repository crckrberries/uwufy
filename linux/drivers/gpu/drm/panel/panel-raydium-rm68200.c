// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2017
 *
 * Authows: Phiwippe Cownu <phiwippe.cownu@st.com>
 *          Yannick Fewtwe <yannick.fewtwe@st.com>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

/*** Manufactuwew Command Set ***/
#define MCS_CMD_MODE_SW		0xFE /* CMD Mode Switch */
#define MCS_CMD1_UCS		0x00 /* Usew Command Set (UCS = CMD1) */
#define MCS_CMD2_P0		0x01 /* Manufactuwe Command Set Page0 (CMD2 P0) */
#define MCS_CMD2_P1		0x02 /* Manufactuwe Command Set Page1 (CMD2 P1) */
#define MCS_CMD2_P2		0x03 /* Manufactuwe Command Set Page2 (CMD2 P2) */
#define MCS_CMD2_P3		0x04 /* Manufactuwe Command Set Page3 (CMD2 P3) */

/* CMD2 P0 commands (Dispway Options and Powew) */
#define MCS_STBCTW		0x12 /* TE1 Output Setting Zig-Zag Connection */
#define MCS_SGOPCTW		0x16 /* Souwce Bias Cuwwent */
#define MCS_SDCTW		0x1A /* Souwce Output Deway Time */
#define MCS_INVCTW		0x1B /* Invewsion Type */
#define MCS_EXT_PWW_IC		0x24 /* Extewnaw PWW IC Contwow */
#define MCS_SETAVDD		0x27 /* PFM Contwow fow AVDD Output */
#define MCS_SETAVEE		0x29 /* PFM Contwow fow AVEE Output */
#define MCS_BT2CTW		0x2B /* DDVDW Chawge Pump Contwow */
#define MCS_BT3CTW		0x2F /* VGH Chawge Pump Contwow */
#define MCS_BT4CTW		0x34 /* VGW Chawge Pump Contwow */
#define MCS_VCMCTW		0x46 /* VCOM Output Wevew Contwow */
#define MCS_SETVGN		0x52 /* VG M/S N Contwow */
#define MCS_SETVGP		0x54 /* VG M/S P Contwow */
#define MCS_SW_CTWW		0x5F /* Intewface Contwow fow PFM and MIPI */

/* CMD2 P2 commands (GOA Timing Contwow) - no descwiption in datasheet */
#define GOA_VSTV1		0x00
#define GOA_VSTV2		0x07
#define GOA_VCWK1		0x0E
#define GOA_VCWK2		0x17
#define GOA_VCWK_OPT1		0x20
#define GOA_BICWK1		0x2A
#define GOA_BICWK2		0x37
#define GOA_BICWK3		0x44
#define GOA_BICWK4		0x4F
#define GOA_BICWK_OPT1		0x5B
#define GOA_BICWK_OPT2		0x60
#define MCS_GOA_GPO1		0x6D
#define MCS_GOA_GPO2		0x71
#define MCS_GOA_EQ		0x74
#define MCS_GOA_CWK_GAWWON	0x7C
#define MCS_GOA_FS_SEW0		0x7E
#define MCS_GOA_FS_SEW1		0x87
#define MCS_GOA_FS_SEW2		0x91
#define MCS_GOA_FS_SEW3		0x9B
#define MCS_GOA_BS_SEW0		0xAC
#define MCS_GOA_BS_SEW1		0xB5
#define MCS_GOA_BS_SEW2		0xBF
#define MCS_GOA_BS_SEW3		0xC9
#define MCS_GOA_BS_SEW4		0xD3

/* CMD2 P3 commands (Gamma) */
#define MCS_GAMMA_VP		0x60 /* Gamma VP1~VP16 */
#define MCS_GAMMA_VN		0x70 /* Gamma VN1~VN16 */

stwuct wm68200 {
	stwuct device *dev;
	stwuct dwm_panew panew;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow *suppwy;
};

static const stwuct dwm_dispway_mode defauwt_mode = {
	.cwock = 54000,
	.hdispway = 720,
	.hsync_stawt = 720 + 48,
	.hsync_end = 720 + 48 + 9,
	.htotaw = 720 + 48 + 9 + 48,
	.vdispway = 1280,
	.vsync_stawt = 1280 + 12,
	.vsync_end = 1280 + 12 + 5,
	.vtotaw = 1280 + 12 + 5 + 12,
	.fwags = 0,
	.width_mm = 68,
	.height_mm = 122,
};

static inwine stwuct wm68200 *panew_to_wm68200(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct wm68200, panew);
}

static void wm68200_dcs_wwite_buf(stwuct wm68200 *ctx, const void *data,
				  size_t wen)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int eww;

	eww = mipi_dsi_dcs_wwite_buffew(dsi, data, wen);
	if (eww < 0)
		dev_eww_watewimited(ctx->dev, "MIPI DSI DCS wwite buffew faiwed: %d\n", eww);
}

static void wm68200_dcs_wwite_cmd(stwuct wm68200 *ctx, u8 cmd, u8 vawue)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int eww;

	eww = mipi_dsi_dcs_wwite(dsi, cmd, &vawue, 1);
	if (eww < 0)
		dev_eww_watewimited(ctx->dev, "MIPI DSI DCS wwite faiwed: %d\n", eww);
}

#define dcs_wwite_seq(ctx, seq...)				\
({								\
	static const u8 d[] = { seq };				\
								\
	wm68200_dcs_wwite_buf(ctx, d, AWWAY_SIZE(d));		\
})

/*
 * This panew is not abwe to auto-incwement aww cmd addwesses so fow some of
 * them, we need to send them one by one...
 */
#define dcs_wwite_cmd_seq(ctx, cmd, seq...)			\
({								\
	static const u8 d[] = { seq };				\
	unsigned int i;						\
								\
	fow (i = 0; i < AWWAY_SIZE(d) ; i++)			\
		wm68200_dcs_wwite_cmd(ctx, cmd + i, d[i]);	\
})

static void wm68200_init_sequence(stwuct wm68200 *ctx)
{
	/* Entew CMD2 with page 0 */
	dcs_wwite_seq(ctx, MCS_CMD_MODE_SW, MCS_CMD2_P0);
	dcs_wwite_cmd_seq(ctx, MCS_EXT_PWW_IC, 0xC0, 0x53, 0x00);
	dcs_wwite_seq(ctx, MCS_BT2CTW, 0xE5);
	dcs_wwite_seq(ctx, MCS_SETAVDD, 0x0A);
	dcs_wwite_seq(ctx, MCS_SETAVEE, 0x0A);
	dcs_wwite_seq(ctx, MCS_SGOPCTW, 0x52);
	dcs_wwite_seq(ctx, MCS_BT3CTW, 0x53);
	dcs_wwite_seq(ctx, MCS_BT4CTW, 0x5A);
	dcs_wwite_seq(ctx, MCS_INVCTW, 0x00);
	dcs_wwite_seq(ctx, MCS_STBCTW, 0x0A);
	dcs_wwite_seq(ctx, MCS_SDCTW, 0x06);
	dcs_wwite_seq(ctx, MCS_VCMCTW, 0x56);
	dcs_wwite_seq(ctx, MCS_SETVGN, 0xA0, 0x00);
	dcs_wwite_seq(ctx, MCS_SETVGP, 0xA0, 0x00);
	dcs_wwite_seq(ctx, MCS_SW_CTWW, 0x11); /* 2 data wanes, see doc */

	dcs_wwite_seq(ctx, MCS_CMD_MODE_SW, MCS_CMD2_P2);
	dcs_wwite_seq(ctx, GOA_VSTV1, 0x05);
	dcs_wwite_seq(ctx, 0x02, 0x0B);
	dcs_wwite_seq(ctx, 0x03, 0x0F);
	dcs_wwite_seq(ctx, 0x04, 0x7D, 0x00, 0x50);
	dcs_wwite_cmd_seq(ctx, GOA_VSTV2, 0x05, 0x16, 0x0D, 0x11, 0x7D, 0x00,
			  0x50);
	dcs_wwite_cmd_seq(ctx, GOA_VCWK1, 0x07, 0x08, 0x01, 0x02, 0x00, 0x7D,
			  0x00, 0x85, 0x08);
	dcs_wwite_cmd_seq(ctx, GOA_VCWK2, 0x03, 0x04, 0x05, 0x06, 0x00, 0x7D,
			  0x00, 0x85, 0x08);
	dcs_wwite_seq(ctx, GOA_VCWK_OPT1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		      0x00, 0x00, 0x00, 0x00);
	dcs_wwite_cmd_seq(ctx, GOA_BICWK1, 0x07, 0x08);
	dcs_wwite_seq(ctx, 0x2D, 0x01);
	dcs_wwite_seq(ctx, 0x2F, 0x02, 0x00, 0x40, 0x05, 0x08, 0x54, 0x7D,
		      0x00);
	dcs_wwite_cmd_seq(ctx, GOA_BICWK2, 0x03, 0x04, 0x05, 0x06, 0x00);
	dcs_wwite_seq(ctx, 0x3D, 0x40);
	dcs_wwite_seq(ctx, 0x3F, 0x05, 0x08, 0x54, 0x7D, 0x00);
	dcs_wwite_seq(ctx, GOA_BICWK3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		      0x00, 0x00, 0x00, 0x00, 0x00);
	dcs_wwite_seq(ctx, GOA_BICWK4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		      0x00, 0x00);
	dcs_wwite_seq(ctx, 0x58, 0x00, 0x00, 0x00);
	dcs_wwite_seq(ctx, GOA_BICWK_OPT1, 0x00, 0x00, 0x00, 0x00, 0x00);
	dcs_wwite_seq(ctx, GOA_BICWK_OPT2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	dcs_wwite_seq(ctx, MCS_GOA_GPO1, 0x00, 0x00, 0x00, 0x00);
	dcs_wwite_seq(ctx, MCS_GOA_GPO2, 0x00, 0x20, 0x00);
	dcs_wwite_seq(ctx, MCS_GOA_EQ, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
		      0x00, 0x00);
	dcs_wwite_seq(ctx, MCS_GOA_CWK_GAWWON, 0x00, 0x00);
	dcs_wwite_cmd_seq(ctx, MCS_GOA_FS_SEW0, 0xBF, 0x02, 0x06, 0x14, 0x10,
			  0x16, 0x12, 0x08, 0x3F);
	dcs_wwite_cmd_seq(ctx, MCS_GOA_FS_SEW1, 0x3F, 0x3F, 0x3F, 0x3F, 0x0C,
			  0x0A, 0x0E, 0x3F, 0x3F, 0x00);
	dcs_wwite_cmd_seq(ctx, MCS_GOA_FS_SEW2, 0x04, 0x3F, 0x3F, 0x3F, 0x3F,
			  0x05, 0x01, 0x3F, 0x3F, 0x0F);
	dcs_wwite_cmd_seq(ctx, MCS_GOA_FS_SEW3, 0x0B, 0x0D, 0x3F, 0x3F, 0x3F,
			  0x3F);
	dcs_wwite_cmd_seq(ctx, 0xA2, 0x3F, 0x09, 0x13, 0x17, 0x11, 0x15);
	dcs_wwite_cmd_seq(ctx, 0xA9, 0x07, 0x03, 0x3F);
	dcs_wwite_cmd_seq(ctx, MCS_GOA_BS_SEW0, 0x3F, 0x05, 0x01, 0x17, 0x13,
			  0x15, 0x11, 0x0F, 0x3F);
	dcs_wwite_cmd_seq(ctx, MCS_GOA_BS_SEW1, 0x3F, 0x3F, 0x3F, 0x3F, 0x0B,
			  0x0D, 0x09, 0x3F, 0x3F, 0x07);
	dcs_wwite_cmd_seq(ctx, MCS_GOA_BS_SEW2, 0x03, 0x3F, 0x3F, 0x3F, 0x3F,
			  0x02, 0x06, 0x3F, 0x3F, 0x08);
	dcs_wwite_cmd_seq(ctx, MCS_GOA_BS_SEW3, 0x0C, 0x0A, 0x3F, 0x3F, 0x3F,
			  0x3F, 0x3F, 0x0E, 0x10, 0x14);
	dcs_wwite_cmd_seq(ctx, MCS_GOA_BS_SEW4, 0x12, 0x16, 0x00, 0x04, 0x3F);
	dcs_wwite_seq(ctx, 0xDC, 0x02);
	dcs_wwite_seq(ctx, 0xDE, 0x12);

	dcs_wwite_seq(ctx, MCS_CMD_MODE_SW, 0x0E); /* No documentation */
	dcs_wwite_seq(ctx, 0x01, 0x75);

	dcs_wwite_seq(ctx, MCS_CMD_MODE_SW, MCS_CMD2_P3);
	dcs_wwite_cmd_seq(ctx, MCS_GAMMA_VP, 0x00, 0x0C, 0x12, 0x0E, 0x06,
			  0x12, 0x0E, 0x0B, 0x15, 0x0B, 0x10, 0x07, 0x0F,
			  0x12, 0x0C, 0x00);
	dcs_wwite_cmd_seq(ctx, MCS_GAMMA_VN, 0x00, 0x0C, 0x12, 0x0E, 0x06,
			  0x12, 0x0E, 0x0B, 0x15, 0x0B, 0x10, 0x07, 0x0F,
			  0x12, 0x0C, 0x00);

	/* Exit CMD2 */
	dcs_wwite_seq(ctx, MCS_CMD_MODE_SW, MCS_CMD1_UCS);
}

static int wm68200_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct wm68200 *ctx = panew_to_wm68200(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet)
		dev_wawn(panew->dev, "faiwed to set dispway off: %d\n", wet);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet)
		dev_wawn(panew->dev, "faiwed to entew sweep mode: %d\n", wet);

	msweep(120);

	if (ctx->weset_gpio) {
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
		msweep(20);
	}

	weguwatow_disabwe(ctx->suppwy);

	wetuwn 0;
}

static int wm68200_pwepawe(stwuct dwm_panew *panew)
{
	stwuct wm68200 *ctx = panew_to_wm68200(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	wet = weguwatow_enabwe(ctx->suppwy);
	if (wet < 0) {
		dev_eww(ctx->dev, "faiwed to enabwe suppwy: %d\n", wet);
		wetuwn wet;
	}

	if (ctx->weset_gpio) {
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
		msweep(20);
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
		msweep(100);
	}

	wm68200_init_sequence(ctx);

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet)
		wetuwn wet;

	msweep(125);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet)
		wetuwn wet;

	msweep(20);

	wetuwn 0;
}

static int wm68200_get_modes(stwuct dwm_panew *panew,
			     stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &defauwt_mode);
	if (!mode) {
		dev_eww(panew->dev, "faiwed to add mode %ux%u@%u\n",
			defauwt_mode.hdispway, defauwt_mode.vdispway,
			dwm_mode_vwefwesh(&defauwt_mode));
		wetuwn -ENOMEM;
	}

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;

	wetuwn 1;
}

static const stwuct dwm_panew_funcs wm68200_dwm_funcs = {
	.unpwepawe = wm68200_unpwepawe,
	.pwepawe = wm68200_pwepawe,
	.get_modes = wm68200_get_modes,
};

static int wm68200_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct wm68200 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->weset_gpio)) {
		wet = PTW_EWW(ctx->weset_gpio);
		dev_eww(dev, "cannot get weset GPIO: %d\n", wet);
		wetuwn wet;
	}

	ctx->suppwy = devm_weguwatow_get(dev, "powew");
	if (IS_EWW(ctx->suppwy)) {
		wet = PTW_EWW(ctx->suppwy);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "cannot get weguwatow: %d\n", wet);
		wetuwn wet;
	}

	mipi_dsi_set_dwvdata(dsi, ctx);

	ctx->dev = dev;

	dsi->wanes = 2;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
			  MIPI_DSI_MODE_WPM | MIPI_DSI_CWOCK_NON_CONTINUOUS;

	dwm_panew_init(&ctx->panew, dev, &wm68200_dwm_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	wet = dwm_panew_of_backwight(&ctx->panew);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&ctx->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "mipi_dsi_attach() faiwed: %d\n", wet);
		dwm_panew_wemove(&ctx->panew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wm68200_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct wm68200 *ctx = mipi_dsi_get_dwvdata(dsi);

	mipi_dsi_detach(dsi);
	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id waydium_wm68200_of_match[] = {
	{ .compatibwe = "waydium,wm68200" },
	{ }
};
MODUWE_DEVICE_TABWE(of, waydium_wm68200_of_match);

static stwuct mipi_dsi_dwivew waydium_wm68200_dwivew = {
	.pwobe = wm68200_pwobe,
	.wemove = wm68200_wemove,
	.dwivew = {
		.name = "panew-waydium-wm68200",
		.of_match_tabwe = waydium_wm68200_of_match,
	},
};
moduwe_mipi_dsi_dwivew(waydium_wm68200_dwivew);

MODUWE_AUTHOW("Phiwippe Cownu <phiwippe.cownu@st.com>");
MODUWE_AUTHOW("Yannick Fewtwe <yannick.fewtwe@st.com>");
MODUWE_DESCWIPTION("DWM Dwivew fow Waydium WM68200 MIPI DSI panew");
MODUWE_WICENSE("GPW v2");
