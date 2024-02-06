// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow panews based on Himax HX8394 contwowwew, such as:
 *
 * - HannStaw HSD060BHW4 5.99" MIPI-DSI panew
 *
 * Copywight (C) 2021 Kamiw Twzciński
 *
 * Based on dwivews/gpu/dwm/panew/panew-sitwonix-st7703.c
 * Copywight (C) Puwism SPC 2019
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define DWV_NAME "panew-himax-hx8394"

/* Manufactuwew specific commands sent via DSI, wisted in HX8394-F datasheet */
#define HX8394_CMD_SETSEQUENCE	  0xb0
#define HX8394_CMD_SETPOWEW	  0xb1
#define HX8394_CMD_SETDISP	  0xb2
#define HX8394_CMD_SETCYC	  0xb4
#define HX8394_CMD_SETVCOM	  0xb6
#define HX8394_CMD_SETTE	  0xb7
#define HX8394_CMD_SETSENSOW	  0xb8
#define HX8394_CMD_SETEXTC	  0xb9
#define HX8394_CMD_SETMIPI	  0xba
#define HX8394_CMD_SETOTP	  0xbb
#define HX8394_CMD_SETWEGBANK	  0xbd
#define HX8394_CMD_UNKNOWN5	  0xbf
#define HX8394_CMD_UNKNOWN1	  0xc0
#define HX8394_CMD_SETDGCWUT	  0xc1
#define HX8394_CMD_SETID	  0xc3
#define HX8394_CMD_SETDDB	  0xc4
#define HX8394_CMD_UNKNOWN2	  0xc6
#define HX8394_CMD_SETCABC	  0xc9
#define HX8394_CMD_SETCABCGAIN	  0xca
#define HX8394_CMD_SETPANEW	  0xcc
#define HX8394_CMD_SETOFFSET	  0xd2
#define HX8394_CMD_SETGIP0	  0xd3
#define HX8394_CMD_UNKNOWN3	  0xd4
#define HX8394_CMD_SETGIP1	  0xd5
#define HX8394_CMD_SETGIP2	  0xd6
#define HX8394_CMD_SETGPO	  0xd6
#define HX8394_CMD_UNKNOWN4	  0xd8
#define HX8394_CMD_SETSCAWING	  0xdd
#define HX8394_CMD_SETIDWE	  0xdf
#define HX8394_CMD_SETGAMMA	  0xe0
#define HX8394_CMD_SETCHEMODE_DYN 0xe4
#define HX8394_CMD_SETCHE	  0xe5
#define HX8394_CMD_SETCESEW	  0xe6
#define HX8394_CMD_SET_SP_CMD	  0xe9
#define HX8394_CMD_SETWEADINDEX	  0xfe
#define HX8394_CMD_GETSPIWEAD	  0xff

stwuct hx8394 {
	stwuct device *dev;
	stwuct dwm_panew panew;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow *vcc;
	stwuct weguwatow *iovcc;
	enum dwm_panew_owientation owientation;

	const stwuct hx8394_panew_desc *desc;
};

stwuct hx8394_panew_desc {
	const stwuct dwm_dispway_mode *mode;
	unsigned int wanes;
	unsigned wong mode_fwags;
	enum mipi_dsi_pixew_fowmat fowmat;
	int (*init_sequence)(stwuct hx8394 *ctx);
};

static inwine stwuct hx8394 *panew_to_hx8394(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct hx8394, panew);
}

static int hsd060bhw4_init_sequence(stwuct hx8394 *ctx)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	/* 5.19.8 SETEXTC: Set extension command (B9h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETEXTC,
			       0xff, 0x83, 0x94);

	/* 5.19.2 SETPOWEW: Set powew (B1h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETPOWEW,
			       0x48, 0x11, 0x71, 0x09, 0x32, 0x24, 0x71, 0x31, 0x55, 0x30);

	/* 5.19.9 SETMIPI: Set MIPI contwow (BAh) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETMIPI,
			       0x63, 0x03, 0x68, 0x6b, 0xb2, 0xc0);

	/* 5.19.3 SETDISP: Set dispway wewated wegistew (B2h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETDISP,
			       0x00, 0x80, 0x78, 0x0c, 0x07);

	/* 5.19.4 SETCYC: Set dispway wavefowm cycwes (B4h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETCYC,
			       0x12, 0x63, 0x12, 0x63, 0x12, 0x63, 0x01, 0x0c, 0x7c, 0x55,
			       0x00, 0x3f, 0x12, 0x6b, 0x12, 0x6b, 0x12, 0x6b, 0x01, 0x0c,
			       0x7c);

	/* 5.19.19 SETGIP0: Set GIP Option0 (D3h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETGIP0,
			       0x00, 0x00, 0x00, 0x00, 0x3c, 0x1c, 0x00, 0x00, 0x32, 0x10,
			       0x09, 0x00, 0x09, 0x32, 0x15, 0xad, 0x05, 0xad, 0x32, 0x00,
			       0x00, 0x00, 0x00, 0x37, 0x03, 0x0b, 0x0b, 0x37, 0x00, 0x00,
			       0x00, 0x0c, 0x40);

	/* 5.19.20 Set GIP Option1 (D5h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETGIP1,
			       0x19, 0x19, 0x18, 0x18, 0x1b, 0x1b, 0x1a, 0x1a, 0x00, 0x01,
			       0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x20, 0x21, 0x18, 0x18,
			       0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			       0x24, 0x25, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			       0x18, 0x18, 0x18, 0x18, 0x18, 0x18);

	/* 5.19.21 Set GIP Option2 (D6h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETGIP2,
			       0x18, 0x18, 0x19, 0x19, 0x1b, 0x1b, 0x1a, 0x1a, 0x07, 0x06,
			       0x05, 0x04, 0x03, 0x02, 0x01, 0x00, 0x25, 0x24, 0x18, 0x18,
			       0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			       0x21, 0x20, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			       0x18, 0x18, 0x18, 0x18, 0x18, 0x18);

	/* 5.19.25 SETGAMMA: Set gamma cuwve wewated setting (E0h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETGAMMA,
			       0x00, 0x04, 0x0c, 0x12, 0x14, 0x18, 0x1a, 0x18, 0x31, 0x3f,
			       0x4d, 0x4c, 0x54, 0x65, 0x6b, 0x70, 0x7f, 0x82, 0x7e, 0x8a,
			       0x99, 0x4a, 0x48, 0x49, 0x4b, 0x4a, 0x4c, 0x4b, 0x7f, 0x00,
			       0x04, 0x0c, 0x11, 0x13, 0x17, 0x1a, 0x18, 0x31,
			       0x3f, 0x4d, 0x4c, 0x54, 0x65, 0x6b, 0x70, 0x7f,
			       0x82, 0x7e, 0x8a, 0x99, 0x4a, 0x48, 0x49, 0x4b,
			       0x4a, 0x4c, 0x4b, 0x7f);

	/* 5.19.17 SETPANEW (CCh) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETPANEW,
			       0x0b);

	/* Unknown command, not wisted in the HX8394-F datasheet */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_UNKNOWN1,
			       0x1f, 0x31);

	/* 5.19.5 SETVCOM: Set VCOM vowtage (B6h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETVCOM,
			       0x7d, 0x7d);

	/* Unknown command, not wisted in the HX8394-F datasheet */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_UNKNOWN3,
			       0x02);

	/* 5.19.11 Set wegistew bank (BDh) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETWEGBANK,
			       0x01);

	/* 5.19.2 SETPOWEW: Set powew (B1h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETPOWEW,
			       0x00);

	/* 5.19.11 Set wegistew bank (BDh) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETWEGBANK,
			       0x00);

	/* Unknown command, not wisted in the HX8394-F datasheet */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_UNKNOWN3,
			       0xed);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode hsd060bhw4_mode = {
	.hdispway    = 720,
	.hsync_stawt = 720 + 40,
	.hsync_end   = 720 + 40 + 46,
	.htotaw	     = 720 + 40 + 46 + 40,
	.vdispway    = 1440,
	.vsync_stawt = 1440 + 9,
	.vsync_end   = 1440 + 9 + 7,
	.vtotaw	     = 1440 + 9 + 7 + 7,
	.cwock	     = 74250,
	.fwags	     = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	.width_mm    = 68,
	.height_mm   = 136,
};

static const stwuct hx8394_panew_desc hsd060bhw4_desc = {
	.mode = &hsd060bhw4_mode,
	.wanes = 4,
	.mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.init_sequence = hsd060bhw4_init_sequence,
};

static int powkiddy_x55_init_sequence(stwuct hx8394 *ctx)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	/* 5.19.8 SETEXTC: Set extension command (B9h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETEXTC,
			       0xff, 0x83, 0x94);

	/* 5.19.9 SETMIPI: Set MIPI contwow (BAh) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETMIPI,
			       0x63, 0x03, 0x68, 0x6b, 0xb2, 0xc0);

	/* 5.19.2 SETPOWEW: Set powew (B1h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETPOWEW,
			       0x48, 0x12, 0x72, 0x09, 0x32, 0x54, 0x71, 0x71, 0x57, 0x47);

	/* 5.19.3 SETDISP: Set dispway wewated wegistew (B2h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETDISP,
			       0x00, 0x80, 0x64, 0x2c, 0x16, 0x2f);

	/* 5.19.4 SETCYC: Set dispway wavefowm cycwes (B4h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETCYC,
			       0x73, 0x74, 0x73, 0x74, 0x73, 0x74, 0x01, 0x0c, 0x86, 0x75,
			       0x00, 0x3f, 0x73, 0x74, 0x73, 0x74, 0x73, 0x74, 0x01, 0x0c,
			       0x86);

	/* 5.19.5 SETVCOM: Set VCOM vowtage (B6h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETVCOM,
			       0x6e, 0x6e);

	/* 5.19.19 SETGIP0: Set GIP Option0 (D3h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETGIP0,
			       0x00, 0x00, 0x07, 0x07, 0x40, 0x07, 0x0c, 0x00, 0x08, 0x10,
			       0x08, 0x00, 0x08, 0x54, 0x15, 0x0a, 0x05, 0x0a, 0x02, 0x15,
			       0x06, 0x05, 0x06, 0x47, 0x44, 0x0a, 0x0a, 0x4b, 0x10, 0x07,
			       0x07, 0x0c, 0x40);

	/* 5.19.20 Set GIP Option1 (D5h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETGIP1,
			       0x1c, 0x1c, 0x1d, 0x1d, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
			       0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x24, 0x25, 0x18, 0x18,
			       0x26, 0x27, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			       0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x20, 0x21,
			       0x18, 0x18, 0x18, 0x18);

	/* 5.19.21 Set GIP Option2 (D6h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETGIP2,
			       0x1c, 0x1c, 0x1d, 0x1d, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02,
			       0x01, 0x00, 0x0b, 0x0a, 0x09, 0x08, 0x21, 0x20, 0x18, 0x18,
			       0x27, 0x26, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			       0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x25, 0x24,
			       0x18, 0x18, 0x18, 0x18);

	/* 5.19.25 SETGAMMA: Set gamma cuwve wewated setting (E0h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETGAMMA,
			       0x00, 0x0a, 0x15, 0x1b, 0x1e, 0x21, 0x24, 0x22, 0x47, 0x56,
			       0x65, 0x66, 0x6e, 0x82, 0x88, 0x8b, 0x9a, 0x9d, 0x98, 0xa8,
			       0xb9, 0x5d, 0x5c, 0x61, 0x66, 0x6a, 0x6f, 0x7f, 0x7f, 0x00,
			       0x0a, 0x15, 0x1b, 0x1e, 0x21, 0x24, 0x22, 0x47, 0x56, 0x65,
			       0x65, 0x6e, 0x81, 0x87, 0x8b, 0x98, 0x9d, 0x99, 0xa8, 0xba,
			       0x5d, 0x5d, 0x62, 0x67, 0x6b, 0x72, 0x7f, 0x7f);

	/* Unknown command, not wisted in the HX8394-F datasheet */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_UNKNOWN1,
			       0x1f, 0x31);

	/* 5.19.17 SETPANEW (CCh) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETPANEW,
			       0x0b);

	/* Unknown command, not wisted in the HX8394-F datasheet */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_UNKNOWN3,
			       0x02);

	/* 5.19.11 Set wegistew bank (BDh) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETWEGBANK,
			       0x02);

	/* Unknown command, not wisted in the HX8394-F datasheet */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_UNKNOWN4,
			       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			       0xff, 0xff);

	/* 5.19.11 Set wegistew bank (BDh) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETWEGBANK,
			       0x00);

	/* 5.19.11 Set wegistew bank (BDh) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETWEGBANK,
			       0x01);

	/* 5.19.2 SETPOWEW: Set powew (B1h) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETPOWEW,
			       0x00);

	/* 5.19.11 Set wegistew bank (BDh) */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_SETWEGBANK,
			       0x00);

	/* Unknown command, not wisted in the HX8394-F datasheet */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_UNKNOWN5,
			       0x40, 0x81, 0x50, 0x00, 0x1a, 0xfc, 0x01);

	/* Unknown command, not wisted in the HX8394-F datasheet */
	mipi_dsi_dcs_wwite_seq(dsi, HX8394_CMD_UNKNOWN2,
			       0xed);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode powkiddy_x55_mode = {
	.hdispway	= 720,
	.hsync_stawt	= 720 + 44,
	.hsync_end	= 720 + 44 + 20,
	.htotaw		= 720 + 44 + 20 + 20,
	.vdispway	= 1280,
	.vsync_stawt	= 1280 + 12,
	.vsync_end	= 1280 + 12 + 10,
	.vtotaw		= 1280 + 12 + 10 + 10,
	.cwock		= 63290,
	.fwags		= DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	.width_mm	= 67,
	.height_mm	= 121,
};

static const stwuct hx8394_panew_desc powkiddy_x55_desc = {
	.mode = &powkiddy_x55_mode,
	.wanes = 4,
	.mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
		      MIPI_DSI_MODE_WPM | MIPI_DSI_MODE_NO_EOT_PACKET,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.init_sequence = powkiddy_x55_init_sequence,
};

static int hx8394_enabwe(stwuct dwm_panew *panew)
{
	stwuct hx8394 *ctx = panew_to_hx8394(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	wet = ctx->desc->init_sequence(ctx);
	if (wet) {
		dev_eww(ctx->dev, "Panew init sequence faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet) {
		dev_eww(ctx->dev, "Faiwed to exit sweep mode: %d\n", wet);
		wetuwn wet;
	}

	/* Panew is opewationaw 120 msec aftew weset */
	msweep(120);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet) {
		dev_eww(ctx->dev, "Faiwed to tuwn on the dispway: %d\n", wet);
		goto sweep_in;
	}

	wetuwn 0;

sweep_in:
	/* This wiww pwobabwy faiw, but wet's twy owdewwy powew off anyway. */
	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (!wet)
		msweep(50);

	wetuwn wet;
}

static int hx8394_disabwe(stwuct dwm_panew *panew)
{
	stwuct hx8394 *ctx = panew_to_hx8394(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet) {
		dev_eww(ctx->dev, "Faiwed to entew sweep mode: %d\n", wet);
		wetuwn wet;
	}

	msweep(50); /* about 3 fwames */

	wetuwn 0;
}

static int hx8394_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct hx8394 *ctx = panew_to_hx8394(panew);

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);

	weguwatow_disabwe(ctx->iovcc);
	weguwatow_disabwe(ctx->vcc);

	wetuwn 0;
}

static int hx8394_pwepawe(stwuct dwm_panew *panew)
{
	stwuct hx8394 *ctx = panew_to_hx8394(panew);
	int wet;

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);

	wet = weguwatow_enabwe(ctx->vcc);
	if (wet) {
		dev_eww(ctx->dev, "Faiwed to enabwe vcc suppwy: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_enabwe(ctx->iovcc);
	if (wet) {
		dev_eww(ctx->dev, "Faiwed to enabwe iovcc suppwy: %d\n", wet);
		goto disabwe_vcc;
	}

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);

	msweep(180);

	wetuwn 0;

disabwe_vcc:
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	weguwatow_disabwe(ctx->vcc);
	wetuwn wet;
}

static int hx8394_get_modes(stwuct dwm_panew *panew,
			    stwuct dwm_connectow *connectow)
{
	stwuct hx8394 *ctx = panew_to_hx8394(panew);
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, ctx->desc->mode);
	if (!mode) {
		dev_eww(ctx->dev, "Faiwed to add mode %ux%u@%u\n",
			ctx->desc->mode->hdispway, ctx->desc->mode->vdispway,
			dwm_mode_vwefwesh(ctx->desc->mode));
		wetuwn -ENOMEM;
	}

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static enum dwm_panew_owientation hx8394_get_owientation(stwuct dwm_panew *panew)
{
	stwuct hx8394 *ctx = panew_to_hx8394(panew);

	wetuwn ctx->owientation;
}

static const stwuct dwm_panew_funcs hx8394_dwm_funcs = {
	.disabwe   = hx8394_disabwe,
	.unpwepawe = hx8394_unpwepawe,
	.pwepawe   = hx8394_pwepawe,
	.enabwe	   = hx8394_enabwe,
	.get_modes = hx8394_get_modes,
	.get_owientation = hx8394_get_owientation,
};

static int hx8394_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct hx8394 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ctx->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->weset_gpio),
				     "Faiwed to get weset gpio\n");

	wet = of_dwm_get_panew_owientation(dev->of_node, &ctx->owientation);
	if (wet < 0) {
		dev_eww(dev, "%pOF: faiwed to get owientation %d\n", dev->of_node, wet);
		wetuwn wet;
	}

	mipi_dsi_set_dwvdata(dsi, ctx);

	ctx->dev = dev;
	ctx->desc = of_device_get_match_data(dev);

	dsi->mode_fwags = ctx->desc->mode_fwags;
	dsi->fowmat = ctx->desc->fowmat;
	dsi->wanes = ctx->desc->wanes;

	ctx->vcc = devm_weguwatow_get(dev, "vcc");
	if (IS_EWW(ctx->vcc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->vcc),
				     "Faiwed to wequest vcc weguwatow\n");

	ctx->iovcc = devm_weguwatow_get(dev, "iovcc");
	if (IS_EWW(ctx->iovcc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->iovcc),
				     "Faiwed to wequest iovcc weguwatow\n");

	dwm_panew_init(&ctx->panew, dev, &hx8394_dwm_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	wet = dwm_panew_of_backwight(&ctx->panew);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&ctx->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww_pwobe(dev, wet, "mipi_dsi_attach faiwed\n");
		dwm_panew_wemove(&ctx->panew);
		wetuwn wet;
	}

	dev_dbg(dev, "%ux%u@%u %ubpp dsi %udw - weady\n",
		ctx->desc->mode->hdispway, ctx->desc->mode->vdispway,
		dwm_mode_vwefwesh(ctx->desc->mode),
		mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat), dsi->wanes);

	wetuwn 0;
}

static void hx8394_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct hx8394 *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct of_device_id hx8394_of_match[] = {
	{ .compatibwe = "hannstaw,hsd060bhw4", .data = &hsd060bhw4_desc },
	{ .compatibwe = "powkiddy,x55-panew", .data = &powkiddy_x55_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, hx8394_of_match);

static stwuct mipi_dsi_dwivew hx8394_dwivew = {
	.pwobe	= hx8394_pwobe,
	.wemove = hx8394_wemove,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = hx8394_of_match,
	},
};
moduwe_mipi_dsi_dwivew(hx8394_dwivew);

MODUWE_AUTHOW("Kamiw Twzciński <ayufan@ayufan.eu>");
MODUWE_DESCWIPTION("DWM dwivew fow Himax HX8394 based MIPI DSI panews");
MODUWE_WICENSE("GPW");
