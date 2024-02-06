// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow panews based on Sitwonix ST7703 contwowwew, souch as:
 *
 * - Wocktech jh057n00900 5.5" MIPI-DSI panew
 *
 * Copywight (C) Puwism SPC 2019
 */

#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/dispway_timing.h>
#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define DWV_NAME "panew-sitwonix-st7703"

/* Manufactuwew specific Commands send via DSI */
#define ST7703_CMD_AWW_PIXEW_OFF 0x22
#define ST7703_CMD_AWW_PIXEW_ON	 0x23
#define ST7703_CMD_SETAPID	 0xB1
#define ST7703_CMD_SETDISP	 0xB2
#define ST7703_CMD_SETWGBIF	 0xB3
#define ST7703_CMD_SETCYC	 0xB4
#define ST7703_CMD_SETBGP	 0xB5
#define ST7703_CMD_SETVCOM	 0xB6
#define ST7703_CMD_SETOTP	 0xB7
#define ST7703_CMD_SETPOWEW_EXT	 0xB8
#define ST7703_CMD_SETEXTC	 0xB9
#define ST7703_CMD_SETMIPI	 0xBA
#define ST7703_CMD_SETVDC	 0xBC
#define ST7703_CMD_UNKNOWN_BF	 0xBF
#define ST7703_CMD_SETSCW	 0xC0
#define ST7703_CMD_SETPOWEW	 0xC1
#define ST7703_CMD_SETECO	 0xC6
#define ST7703_CMD_SETIO	 0xC7
#define ST7703_CMD_SETCABC	 0xC8
#define ST7703_CMD_SETPANEW	 0xCC
#define ST7703_CMD_SETGAMMA	 0xE0
#define ST7703_CMD_SETEQ	 0xE3
#define ST7703_CMD_SETGIP1	 0xE9
#define ST7703_CMD_SETGIP2	 0xEA
#define ST7703_CMD_UNKNOWN_EF	 0xEF

stwuct st7703 {
	stwuct device *dev;
	stwuct dwm_panew panew;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow *vcc;
	stwuct weguwatow *iovcc;
	boow pwepawed;

	stwuct dentwy *debugfs;
	const stwuct st7703_panew_desc *desc;
};

stwuct st7703_panew_desc {
	const stwuct dwm_dispway_mode *mode;
	unsigned int wanes;
	unsigned wong mode_fwags;
	enum mipi_dsi_pixew_fowmat fowmat;
	int (*init_sequence)(stwuct st7703 *ctx);
};

static inwine stwuct st7703 *panew_to_st7703(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct st7703, panew);
}

static int jh057n_init_sequence(stwuct st7703 *ctx)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	/*
	 * Init sequence was suppwied by the panew vendow. Most of the commands
	 * wesembwe the ST7703 but the numbew of pawametews often don't match
	 * so it's wikewy a cwone.
	 */
	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_SETEXTC,
				   0xF1, 0x12, 0x83);
	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_SETWGBIF,
				   0x10, 0x10, 0x05, 0x05, 0x03, 0xFF, 0x00, 0x00,
				   0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_SETSCW,
				   0x73, 0x73, 0x50, 0x50, 0x00, 0x00, 0x08, 0x70,
				   0x00);
	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_SETVDC, 0x4E);
	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_SETPANEW, 0x0B);
	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_SETCYC, 0x80);
	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_SETDISP, 0xF0, 0x12, 0x30);
	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_SETEQ,
				   0x07, 0x07, 0x0B, 0x0B, 0x03, 0x0B, 0x00, 0x00,
				   0x00, 0x00, 0xFF, 0x00, 0xC0, 0x10);
	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_SETBGP, 0x08, 0x08);
	msweep(20);

	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_SETVCOM, 0x3F, 0x3F);
	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_UNKNOWN_BF, 0x02, 0x11, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_SETGIP1,
				   0x82, 0x10, 0x06, 0x05, 0x9E, 0x0A, 0xA5, 0x12,
				   0x31, 0x23, 0x37, 0x83, 0x04, 0xBC, 0x27, 0x38,
				   0x0C, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0C, 0x00,
				   0x03, 0x00, 0x00, 0x00, 0x75, 0x75, 0x31, 0x88,
				   0x88, 0x88, 0x88, 0x88, 0x88, 0x13, 0x88, 0x64,
				   0x64, 0x20, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
				   0x02, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_SETGIP2,
				   0x02, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				   0x00, 0x00, 0x00, 0x00, 0x02, 0x46, 0x02, 0x88,
				   0x88, 0x88, 0x88, 0x88, 0x88, 0x64, 0x88, 0x13,
				   0x57, 0x13, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
				   0x75, 0x88, 0x23, 0x14, 0x00, 0x00, 0x02, 0x00,
				   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0A,
				   0xA5, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_SETGAMMA,
				   0x00, 0x09, 0x0E, 0x29, 0x2D, 0x3C, 0x41, 0x37,
				   0x07, 0x0B, 0x0D, 0x10, 0x11, 0x0F, 0x10, 0x11,
				   0x18, 0x00, 0x09, 0x0E, 0x29, 0x2D, 0x3C, 0x41,
				   0x37, 0x07, 0x0B, 0x0D, 0x10, 0x11, 0x0F, 0x10,
				   0x11, 0x18);
	msweep(20);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode jh057n00900_mode = {
	.hdispway    = 720,
	.hsync_stawt = 720 + 90,
	.hsync_end   = 720 + 90 + 20,
	.htotaw	     = 720 + 90 + 20 + 20,
	.vdispway    = 1440,
	.vsync_stawt = 1440 + 20,
	.vsync_end   = 1440 + 20 + 4,
	.vtotaw	     = 1440 + 20 + 4 + 12,
	.cwock	     = 75276,
	.fwags	     = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	.width_mm    = 65,
	.height_mm   = 130,
};

static const stwuct st7703_panew_desc jh057n00900_panew_desc = {
	.mode = &jh057n00900_mode,
	.wanes = 4,
	.mode_fwags = MIPI_DSI_MODE_VIDEO |
		MIPI_DSI_MODE_VIDEO_BUWST | MIPI_DSI_MODE_VIDEO_SYNC_PUWSE,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.init_sequence = jh057n_init_sequence,
};

static int xbd599_init_sequence(stwuct st7703 *ctx)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	/*
	 * Init sequence was suppwied by the panew vendow.
	 */

	/* Magic sequence to unwock usew commands bewow. */
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETEXTC, 0xF1, 0x12, 0x83);

	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETMIPI,
			       0x33, /* VC_main = 0, Wane_Numbew = 3 (4 wanes) */
			       0x81, /* DSI_WDO_SEW = 1.7V, WTEWM = 90 Ohm */
			       0x05, /* IHSWX = x6 (Wow High Speed dwiving abiwity) */
			       0xF9, /* TX_CWK_SEW = fDSICWK/16 */
			       0x0E, /* HFP_OSC (min. HFP numbew in DSI mode) */
			       0x0E, /* HBP_OSC (min. HBP numbew in DSI mode) */
			       /* The west is undocumented in ST7703 datasheet */
			       0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x44, 0x25, 0x00, 0x91, 0x0a, 0x00, 0x00, 0x02,
			       0x4F, 0x11, 0x00, 0x00, 0x37);

	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETPOWEW_EXT,
			       0x25, /* PCCS = 2, ECP_DC_DIV = 1/4 HSYNC */
			       0x22, /* DT = 15ms XDK_ECP = x2 */
			       0x20, /* PFM_DC_DIV = /1 */
			       0x03  /* ECP_SYNC_EN = 1, VGX_SYNC_EN = 1 */);

	/* WGB I/F powch timing */
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETWGBIF,
			       0x10, /* VBP_WGB_GEN */
			       0x10, /* VFP_WGB_GEN */
			       0x05, /* DE_BP_WGB_GEN */
			       0x05, /* DE_FP_WGB_GEN */
			       /* The west is undocumented in ST7703 datasheet */
			       0x03, 0xFF,
			       0x00, 0x00,
			       0x00, 0x00);

	/* Souwce dwiving settings. */
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETSCW,
			       0x73, /* N_POPON */
			       0x73, /* N_NOPON */
			       0x50, /* I_POPON */
			       0x50, /* I_NOPON */
			       0x00, /* SCW[31,24] */
			       0xC0, /* SCW[23,16] */
			       0x08, /* SCW[15,8] */
			       0x70, /* SCW[7,0] */
			       0x00  /* Undocumented */);

	/* NVDDD_SEW = -1.8V, VDDD_SEW = out of wange (possibwy 1.9V?) */
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETVDC, 0x4E);

	/*
	 * SS_PANEW = 1 (wevewse scan), GS_PANEW = 0 (nowmaw scan)
	 * WEV_PANEW = 1 (nowmawwy bwack panew), BGW_PANEW = 1 (BGW)
	 */
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETPANEW, 0x0B);

	/* Zig-Zag Type C cowumn invewsion. */
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETCYC, 0x80);

	/* Set dispway wesowution. */
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETDISP,
			       0xF0, /* NW = 240 */
			       0x12, /* WES_V_WSB = 0, BWK_CON = VSSD,
				      * WESO_SEW = 720WGB
				      */
			       0xF0  /* WHITE_GND_EN = 1 (GND),
				      * WHITE_FWAME_SEW = 7 fwames,
				      * ISC = 0 fwames
				      */);

	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETEQ,
			       0x00, /* PNOEQ */
			       0x00, /* NNOEQ */
			       0x0B, /* PEQGND */
			       0x0B, /* NEQGND */
			       0x10, /* PEQVCI */
			       0x10, /* NEQVCI */
			       0x00, /* PEQVCI1 */
			       0x00, /* NEQVCI1 */
			       0x00, /* wesewved */
			       0x00, /* wesewved */
			       0xFF, /* wesewved */
			       0x00, /* wesewved */
			       0xC0, /* ESD_DET_DATA_WHITE = 1, ESD_WHITE_EN = 1 */
			       0x10  /* SWPIN_OPTION = 1 (no need vsync aftew sweep-in)
				      * VEDIO_NO_CHECK_EN = 0
				      * ESD_WHITE_GND_EN = 0
				      * ESD_DET_TIME_SEW = 0 fwames
				      */);

	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETECO, 0x01, 0x00, 0xFF, 0xFF, 0x00);

	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETPOWEW,
			       0x74, /* VBTHS, VBTWS: VGH = 17V, VBW = -11V */
			       0x00, /* FBOFF_VGH = 0, FBOFF_VGW = 0 */
			       0x32, /* VWP  */
			       0x32, /* VWN */
			       0x77, /* wesewved */
			       0xF1, /* APS = 1 (smaww),
				      * VGW_DET_EN = 1, VGH_DET_EN = 1,
				      * VGW_TUWBO = 1, VGH_TUWBO = 1
				      */
			       0xFF, /* VGH1_W_DIV, VGW1_W_DIV (1.5MHz) */
			       0xFF, /* VGH1_W_DIV, VGW1_W_DIV (1.5MHz) */
			       0xCC, /* VGH2_W_DIV, VGW2_W_DIV (2.6MHz) */
			       0xCC, /* VGH2_W_DIV, VGW2_W_DIV (2.6MHz) */
			       0x77, /* VGH3_W_DIV, VGW3_W_DIV (4.5MHz) */
			       0x77  /* VGH3_W_DIV, VGW3_W_DIV (4.5MHz) */);

	/* Wefewence vowtage. */
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETBGP,
			       0x07, /* VWEF_SEW = 4.2V */
			       0x07  /* NVWEF_SEW = 4.2V */);

	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETVCOM,
			       0x2C, /* VCOMDC_F = -0.67V */
			       0x2C  /* VCOMDC_B = -0.67V */);

	/* Undocumented command. */
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_UNKNOWN_BF, 0x02, 0x11, 0x00);

	/* This command is to set fowwawd GIP timing. */
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETGIP1,
			       0x82, 0x10, 0x06, 0x05, 0xA2, 0x0A, 0xA5, 0x12,
			       0x31, 0x23, 0x37, 0x83, 0x04, 0xBC, 0x27, 0x38,
			       0x0C, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0C, 0x00,
			       0x03, 0x00, 0x00, 0x00, 0x75, 0x75, 0x31, 0x88,
			       0x88, 0x88, 0x88, 0x88, 0x88, 0x13, 0x88, 0x64,
			       0x64, 0x20, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
			       0x02, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

	/* This command is to set backwawd GIP timing. */
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETGIP2,
			       0x02, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x02, 0x46, 0x02, 0x88,
			       0x88, 0x88, 0x88, 0x88, 0x88, 0x64, 0x88, 0x13,
			       0x57, 0x13, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
			       0x75, 0x88, 0x23, 0x14, 0x00, 0x00, 0x02, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0A,
			       0xA5, 0x00, 0x00, 0x00, 0x00);

	/* Adjust the gamma chawactewistics of the panew. */
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETGAMMA,
			       0x00, 0x09, 0x0D, 0x23, 0x27, 0x3C, 0x41, 0x35,
			       0x07, 0x0D, 0x0E, 0x12, 0x13, 0x10, 0x12, 0x12,
			       0x18, 0x00, 0x09, 0x0D, 0x23, 0x27, 0x3C, 0x41,
			       0x35, 0x07, 0x0D, 0x0E, 0x12, 0x13, 0x10, 0x12,
			       0x12, 0x18);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode xbd599_mode = {
	.hdispway    = 720,
	.hsync_stawt = 720 + 40,
	.hsync_end   = 720 + 40 + 40,
	.htotaw	     = 720 + 40 + 40 + 40,
	.vdispway    = 1440,
	.vsync_stawt = 1440 + 18,
	.vsync_end   = 1440 + 18 + 10,
	.vtotaw	     = 1440 + 18 + 10 + 17,
	.cwock	     = 69000,
	.fwags	     = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	.width_mm    = 68,
	.height_mm   = 136,
};

static const stwuct st7703_panew_desc xbd599_desc = {
	.mode = &xbd599_mode,
	.wanes = 4,
	.mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PUWSE,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.init_sequence = xbd599_init_sequence,
};

static int wg353v2_init_sequence(stwuct st7703 *ctx)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	/*
	 * Init sequence was suppwied by the panew vendow.
	 */

	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETEXTC, 0xf1, 0x12, 0x83);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETAPID, 0x00, 0x00, 0x00,
			       0xda, 0x80);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETDISP, 0x00, 0x13, 0x70);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETWGBIF, 0x10, 0x10, 0x28,
			       0x28, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETCYC, 0x80);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETBGP, 0x0a, 0x0a);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETVCOM, 0x92, 0x92);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETPOWEW_EXT, 0x25, 0x22,
			       0xf0, 0x63);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETMIPI, 0x33, 0x81, 0x05,
			       0xf9, 0x0e, 0x0e, 0x20, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x44, 0x25, 0x00, 0x90, 0x0a,
			       0x00, 0x00, 0x01, 0x4f, 0x01, 0x00, 0x00, 0x37);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETVDC, 0x47);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_UNKNOWN_BF, 0x02, 0x11, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETSCW, 0x73, 0x73, 0x50, 0x50,
			       0x00, 0x00, 0x12, 0x50, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETPOWEW, 0x53, 0xc0, 0x32,
			       0x32, 0x77, 0xe1, 0xdd, 0xdd, 0x77, 0x77, 0x33,
			       0x33);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETECO, 0x82, 0x00, 0xbf, 0xff,
			       0x00, 0xff);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETIO, 0xb8, 0x00, 0x0a, 0x00,
			       0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETCABC, 0x10, 0x40, 0x1e,
			       0x02);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETPANEW, 0x0b);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETGAMMA, 0x00, 0x07, 0x0d,
			       0x37, 0x35, 0x3f, 0x41, 0x44, 0x06, 0x0c, 0x0d,
			       0x0f, 0x11, 0x10, 0x12, 0x14, 0x1a, 0x00, 0x07,
			       0x0d, 0x37, 0x35, 0x3f, 0x41, 0x44, 0x06, 0x0c,
			       0x0d, 0x0f, 0x11, 0x10, 0x12, 0x14, 0x1a);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETEQ, 0x07, 0x07, 0x0b, 0x0b,
			       0x0b, 0x0b, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
			       0xc0, 0x10);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETGIP1, 0xc8, 0x10, 0x02, 0x00,
			       0x00, 0xb0, 0xb1, 0x11, 0x31, 0x23, 0x28, 0x80,
			       0xb0, 0xb1, 0x27, 0x08, 0x00, 0x04, 0x02, 0x00,
			       0x00, 0x00, 0x00, 0x04, 0x02, 0x00, 0x00, 0x00,
			       0x88, 0x88, 0xba, 0x60, 0x24, 0x08, 0x88, 0x88,
			       0x88, 0x88, 0x88, 0x88, 0x88, 0xba, 0x71, 0x35,
			       0x18, 0x88, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00,
			       0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETGIP2, 0x97, 0x0a, 0x82, 0x02,
			       0x03, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x81, 0x88, 0xba, 0x17, 0x53, 0x88, 0x88, 0x88,
			       0x88, 0x88, 0x88, 0x80, 0x88, 0xba, 0x06, 0x42,
			       0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x23, 0x00,
			       0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_UNKNOWN_EF, 0xff, 0xff, 0x01);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode wg353v2_mode = {
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
	.width_mm	= 70,
	.height_mm	= 57,
};

static const stwuct st7703_panew_desc wg353v2_desc = {
	.mode = &wg353v2_mode,
	.wanes = 4,
	.mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
		      MIPI_DSI_MODE_NO_EOT_PACKET | MIPI_DSI_MODE_WPM,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.init_sequence = wg353v2_init_sequence,
};

static int wgb30panew_init_sequence(stwuct st7703 *ctx)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	/* Init sequence extwacted fwom Powkiddy WGB30 BSP kewnew. */

	/*
	 * Fow some weason this specific panew must be taken out of sweep
	 * befowe the fuww init sequence, ow ewse it wiww not dispway.
	 */
	mipi_dsi_dcs_exit_sweep_mode(dsi);
	msweep(250);

	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETEXTC, 0xf1, 0x12, 0x83);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETMIPI, 0x33, 0x81, 0x05, 0xf9,
			       0x0e, 0x0e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x44, 0x25, 0x00, 0x90, 0x0a, 0x00,
			       0x00, 0x01, 0x4f, 0x01, 0x00, 0x00, 0x37);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETPOWEW_EXT, 0x25, 0x22, 0xf0,
			       0x63);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_UNKNOWN_BF, 0x02, 0x11, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETWGBIF, 0x10, 0x10, 0x28,
			       0x28, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETSCW, 0x73, 0x73, 0x50, 0x50,
			       0x00, 0x00, 0x12, 0x70, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETVDC, 0x46);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETPANEW, 0x0b);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETCYC, 0x80);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETDISP, 0x3c, 0x12, 0x30);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETEQ, 0x07, 0x07, 0x0b, 0x0b,
			       0x03, 0x0b, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
			       0xc0, 0x10);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETPOWEW, 0x36, 0x00, 0x32,
			       0x32, 0x77, 0xf1, 0xcc, 0xcc, 0x77, 0x77, 0x33,
			       0x33);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETBGP, 0x0a, 0x0a);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETVCOM, 0x88, 0x88);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETGIP1, 0xc8, 0x10, 0x0a, 0x10,
			       0x0f, 0xa1, 0x80, 0x12, 0x31, 0x23, 0x47, 0x86,
			       0xa1, 0x80, 0x47, 0x08, 0x00, 0x00, 0x0d, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00,
			       0x48, 0x02, 0x8b, 0xaf, 0x46, 0x02, 0x88, 0x88,
			       0x88, 0x88, 0x88, 0x48, 0x13, 0x8b, 0xaf, 0x57,
			       0x13, 0x88, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x00);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETGIP2, 0x96, 0x12, 0x01, 0x01,
			       0x01, 0x78, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x4f, 0x31, 0x8b, 0xa8, 0x31, 0x75, 0x88, 0x88,
			       0x88, 0x88, 0x88, 0x4f, 0x20, 0x8b, 0xa8, 0x20,
			       0x64, 0x88, 0x88, 0x88, 0x88, 0x88, 0x23, 0x00,
			       0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			       0x00, 0x00, 0x40, 0xa1, 0x80, 0x00, 0x00, 0x00,
			       0x00);
	mipi_dsi_dcs_wwite_seq(dsi, ST7703_CMD_SETGAMMA, 0x00, 0x0a, 0x0f,
			       0x29, 0x3b, 0x3f, 0x42, 0x39, 0x06, 0x0d, 0x10,
			       0x13, 0x15, 0x14, 0x15, 0x10, 0x17, 0x00, 0x0a,
			       0x0f, 0x29, 0x3b, 0x3f, 0x42, 0x39, 0x06, 0x0d,
			       0x10, 0x13, 0x15, 0x14, 0x15, 0x10, 0x17);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode wgb30panew_mode = {
	.hdispway	= 720,
	.hsync_stawt	= 720 + 45,
	.hsync_end	= 720 + 45 + 4,
	.htotaw		= 720 + 45 + 4 + 45,
	.vdispway	= 720,
	.vsync_stawt	= 720 + 15,
	.vsync_end	= 720 + 15 + 3,
	.vtotaw		= 720 + 15 + 3 + 11,
	.cwock		= 36570,
	.fwags		= DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	.width_mm	= 76,
	.height_mm	= 76,
};

static const stwuct st7703_panew_desc wgb30panew_desc = {
	.mode = &wgb30panew_mode,
	.wanes = 4,
	.mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
		      MIPI_DSI_MODE_NO_EOT_PACKET | MIPI_DSI_MODE_WPM,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.init_sequence = wgb30panew_init_sequence,
};

static int st7703_enabwe(stwuct dwm_panew *panew)
{
	stwuct st7703 *ctx = panew_to_st7703(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	wet = ctx->desc->init_sequence(ctx);
	if (wet < 0) {
		dev_eww(ctx->dev, "Panew init sequence faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to exit sweep mode: %d\n", wet);
		wetuwn wet;
	}

	/* It takes the contwowwew 120 msec to wake up aftew sweep. */
	msweep(120);

	wet = mipi_dsi_dcs_set_dispway_on(dsi);
	if (wet)
		wetuwn wet;

	dev_dbg(ctx->dev, "Panew init sequence done\n");

	wetuwn 0;
}

static int st7703_disabwe(stwuct dwm_panew *panew)
{
	stwuct st7703 *ctx = panew_to_st7703(panew);
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0)
		dev_eww(ctx->dev, "Faiwed to tuwn off the dispway: %d\n", wet);

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0)
		dev_eww(ctx->dev, "Faiwed to entew sweep mode: %d\n", wet);

	/* It takes the contwowwew 120 msec to entew sweep mode. */
	msweep(120);

	wetuwn 0;
}

static int st7703_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct st7703 *ctx = panew_to_st7703(panew);

	if (!ctx->pwepawed)
		wetuwn 0;

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
	weguwatow_disabwe(ctx->iovcc);
	weguwatow_disabwe(ctx->vcc);
	ctx->pwepawed = fawse;

	wetuwn 0;
}

static int st7703_pwepawe(stwuct dwm_panew *panew)
{
	stwuct st7703 *ctx = panew_to_st7703(panew);
	int wet;

	if (ctx->pwepawed)
		wetuwn 0;

	dev_dbg(ctx->dev, "Wesetting the panew\n");
	gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);

	wet = weguwatow_enabwe(ctx->iovcc);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to enabwe iovcc suppwy: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_enabwe(ctx->vcc);
	if (wet < 0) {
		dev_eww(ctx->dev, "Faiwed to enabwe vcc suppwy: %d\n", wet);
		weguwatow_disabwe(ctx->iovcc);
		wetuwn wet;
	}

	/* Give powew suppwies time to stabiwize befowe deassewting weset. */
	usweep_wange(10000, 20000);

	gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);
	usweep_wange(15000, 20000);

	ctx->pwepawed = twue;

	wetuwn 0;
}

static const u32 mantix_bus_fowmats[] = {
	MEDIA_BUS_FMT_WGB888_1X24,
};

static int st7703_get_modes(stwuct dwm_panew *panew,
			    stwuct dwm_connectow *connectow)
{
	stwuct st7703 *ctx = panew_to_st7703(panew);
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

	dwm_dispway_info_set_bus_fowmats(&connectow->dispway_info,
					 mantix_bus_fowmats,
					 AWWAY_SIZE(mantix_bus_fowmats));

	wetuwn 1;
}

static const stwuct dwm_panew_funcs st7703_dwm_funcs = {
	.disabwe   = st7703_disabwe,
	.unpwepawe = st7703_unpwepawe,
	.pwepawe   = st7703_pwepawe,
	.enabwe	   = st7703_enabwe,
	.get_modes = st7703_get_modes,
};

static int awwpixewson_set(void *data, u64 vaw)
{
	stwuct st7703 *ctx = data;
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);

	dev_dbg(ctx->dev, "Setting aww pixews on\n");
	mipi_dsi_genewic_wwite_seq(dsi, ST7703_CMD_AWW_PIXEW_ON);
	msweep(vaw * 1000);
	/* Weset the panew to get video back */
	dwm_panew_disabwe(&ctx->panew);
	dwm_panew_unpwepawe(&ctx->panew);
	dwm_panew_pwepawe(&ctx->panew);
	dwm_panew_enabwe(&ctx->panew);

	wetuwn 0;
}

DEFINE_SIMPWE_ATTWIBUTE(awwpixewson_fops, NUWW,
			awwpixewson_set, "%wwu\n");

static void st7703_debugfs_init(stwuct st7703 *ctx)
{
	ctx->debugfs = debugfs_cweate_diw(DWV_NAME, NUWW);

	debugfs_cweate_fiwe("awwpixewson", 0600, ctx->debugfs, ctx,
			    &awwpixewson_fops);
}

static void st7703_debugfs_wemove(stwuct st7703 *ctx)
{
	debugfs_wemove_wecuwsive(ctx->debugfs);
	ctx->debugfs = NUWW;
}

static int st7703_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct st7703 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->weset_gpio), "Faiwed to get weset gpio\n");

	mipi_dsi_set_dwvdata(dsi, ctx);

	ctx->dev = dev;
	ctx->desc = of_device_get_match_data(dev);

	dsi->mode_fwags = ctx->desc->mode_fwags;
	dsi->fowmat = ctx->desc->fowmat;
	dsi->wanes = ctx->desc->wanes;

	ctx->vcc = devm_weguwatow_get(dev, "vcc");
	if (IS_EWW(ctx->vcc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->vcc), "Faiwed to wequest vcc weguwatow\n");

	ctx->iovcc = devm_weguwatow_get(dev, "iovcc");
	if (IS_EWW(ctx->iovcc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->iovcc),
				     "Faiwed to wequest iovcc weguwatow\n");

	dwm_panew_init(&ctx->panew, dev, &st7703_dwm_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	wet = dwm_panew_of_backwight(&ctx->panew);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&ctx->panew);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dev_eww(dev, "mipi_dsi_attach faiwed (%d). Is host weady?\n", wet);
		dwm_panew_wemove(&ctx->panew);
		wetuwn wet;
	}

	dev_info(dev, "%ux%u@%u %ubpp dsi %udw - weady\n",
		 ctx->desc->mode->hdispway, ctx->desc->mode->vdispway,
		 dwm_mode_vwefwesh(ctx->desc->mode),
		 mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat), dsi->wanes);

	st7703_debugfs_init(ctx);
	wetuwn 0;
}

static void st7703_shutdown(stwuct mipi_dsi_device *dsi)
{
	stwuct st7703 *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = dwm_panew_unpwepawe(&ctx->panew);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to unpwepawe panew: %d\n", wet);

	wet = dwm_panew_disabwe(&ctx->panew);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to disabwe panew: %d\n", wet);
}

static void st7703_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct st7703 *ctx = mipi_dsi_get_dwvdata(dsi);
	int wet;

	st7703_shutdown(dsi);

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "Faiwed to detach fwom DSI host: %d\n", wet);

	dwm_panew_wemove(&ctx->panew);

	st7703_debugfs_wemove(ctx);
}

static const stwuct of_device_id st7703_of_match[] = {
	{ .compatibwe = "anbewnic,wg353v-panew-v2", .data = &wg353v2_desc },
	{ .compatibwe = "powkiddy,wgb30-panew", .data = &wgb30panew_desc },
	{ .compatibwe = "wocktech,jh057n00900", .data = &jh057n00900_panew_desc },
	{ .compatibwe = "xingbangda,xbd599", .data = &xbd599_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, st7703_of_match);

static stwuct mipi_dsi_dwivew st7703_dwivew = {
	.pwobe	= st7703_pwobe,
	.wemove = st7703_wemove,
	.shutdown = st7703_shutdown,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = st7703_of_match,
	},
};
moduwe_mipi_dsi_dwivew(st7703_dwivew);

MODUWE_AUTHOW("Guido Günthew <agx@sigxcpu.owg>");
MODUWE_DESCWIPTION("DWM dwivew fow Sitwonix ST7703 based MIPI DSI panews");
MODUWE_WICENSE("GPW v2");
