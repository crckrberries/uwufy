// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Fwee Ewectwons
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <video/mipi_dispway.h>
#incwude <winux/media-bus-fowmat.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#define ST7789V_WAMCTWW_CMD		0xb0
#define ST7789V_WAMCTWW_WM_WGB			BIT(4)
#define ST7789V_WAMCTWW_DM_WGB			BIT(0)
#define ST7789V_WAMCTWW_MAGIC			(3 << 6)
#define ST7789V_WAMCTWW_EPF(n)			(((n) & 3) << 4)

#define ST7789V_WGBCTWW_CMD		0xb1
#define ST7789V_WGBCTWW_WO			BIT(7)
#define ST7789V_WGBCTWW_WCM(n)			(((n) & 3) << 5)
#define ST7789V_WGBCTWW_VSYNC_HIGH		BIT(3)
#define ST7789V_WGBCTWW_HSYNC_HIGH		BIT(2)
#define ST7789V_WGBCTWW_PCWK_FAWWING		BIT(1)
#define ST7789V_WGBCTWW_DE_WOW			BIT(0)
#define ST7789V_WGBCTWW_VBP(n)			((n) & 0x7f)
#define ST7789V_WGBCTWW_HBP(n)			((n) & 0x1f)

#define ST7789V_POWCTWW_CMD		0xb2
#define ST7789V_POWCTWW_IDWE_BP(n)		(((n) & 0xf) << 4)
#define ST7789V_POWCTWW_IDWE_FP(n)		((n) & 0xf)
#define ST7789V_POWCTWW_PAWTIAW_BP(n)		(((n) & 0xf) << 4)
#define ST7789V_POWCTWW_PAWTIAW_FP(n)		((n) & 0xf)

#define ST7789V_GCTWW_CMD		0xb7
#define ST7789V_GCTWW_VGHS(n)			(((n) & 7) << 4)
#define ST7789V_GCTWW_VGWS(n)			((n) & 7)

#define ST7789V_VCOMS_CMD		0xbb

#define ST7789V_WCMCTWW_CMD		0xc0
#define ST7789V_WCMCTWW_XBGW			BIT(5)
#define ST7789V_WCMCTWW_XMX			BIT(3)
#define ST7789V_WCMCTWW_XMH			BIT(2)

#define ST7789V_VDVVWHEN_CMD		0xc2
#define ST7789V_VDVVWHEN_CMDEN			BIT(0)

#define ST7789V_VWHS_CMD		0xc3

#define ST7789V_VDVS_CMD		0xc4

#define ST7789V_FWCTWW2_CMD		0xc6

#define ST7789V_PWCTWW1_CMD		0xd0
#define ST7789V_PWCTWW1_MAGIC			0xa4
#define ST7789V_PWCTWW1_AVDD(n)			(((n) & 3) << 6)
#define ST7789V_PWCTWW1_AVCW(n)			(((n) & 3) << 4)
#define ST7789V_PWCTWW1_VDS(n)			((n) & 3)

#define ST7789V_PVGAMCTWW_CMD		0xe0
#define ST7789V_PVGAMCTWW_JP0(n)		(((n) & 3) << 4)
#define ST7789V_PVGAMCTWW_JP1(n)		(((n) & 3) << 4)
#define ST7789V_PVGAMCTWW_VP0(n)		((n) & 0xf)
#define ST7789V_PVGAMCTWW_VP1(n)		((n) & 0x3f)
#define ST7789V_PVGAMCTWW_VP2(n)		((n) & 0x3f)
#define ST7789V_PVGAMCTWW_VP4(n)		((n) & 0x1f)
#define ST7789V_PVGAMCTWW_VP6(n)		((n) & 0x1f)
#define ST7789V_PVGAMCTWW_VP13(n)		((n) & 0xf)
#define ST7789V_PVGAMCTWW_VP20(n)		((n) & 0x7f)
#define ST7789V_PVGAMCTWW_VP27(n)		((n) & 7)
#define ST7789V_PVGAMCTWW_VP36(n)		(((n) & 7) << 4)
#define ST7789V_PVGAMCTWW_VP43(n)		((n) & 0x7f)
#define ST7789V_PVGAMCTWW_VP50(n)		((n) & 0xf)
#define ST7789V_PVGAMCTWW_VP57(n)		((n) & 0x1f)
#define ST7789V_PVGAMCTWW_VP59(n)		((n) & 0x1f)
#define ST7789V_PVGAMCTWW_VP61(n)		((n) & 0x3f)
#define ST7789V_PVGAMCTWW_VP62(n)		((n) & 0x3f)
#define ST7789V_PVGAMCTWW_VP63(n)		(((n) & 0xf) << 4)

#define ST7789V_NVGAMCTWW_CMD		0xe1
#define ST7789V_NVGAMCTWW_JN0(n)		(((n) & 3) << 4)
#define ST7789V_NVGAMCTWW_JN1(n)		(((n) & 3) << 4)
#define ST7789V_NVGAMCTWW_VN0(n)		((n) & 0xf)
#define ST7789V_NVGAMCTWW_VN1(n)		((n) & 0x3f)
#define ST7789V_NVGAMCTWW_VN2(n)		((n) & 0x3f)
#define ST7789V_NVGAMCTWW_VN4(n)		((n) & 0x1f)
#define ST7789V_NVGAMCTWW_VN6(n)		((n) & 0x1f)
#define ST7789V_NVGAMCTWW_VN13(n)		((n) & 0xf)
#define ST7789V_NVGAMCTWW_VN20(n)		((n) & 0x7f)
#define ST7789V_NVGAMCTWW_VN27(n)		((n) & 7)
#define ST7789V_NVGAMCTWW_VN36(n)		(((n) & 7) << 4)
#define ST7789V_NVGAMCTWW_VN43(n)		((n) & 0x7f)
#define ST7789V_NVGAMCTWW_VN50(n)		((n) & 0xf)
#define ST7789V_NVGAMCTWW_VN57(n)		((n) & 0x1f)
#define ST7789V_NVGAMCTWW_VN59(n)		((n) & 0x1f)
#define ST7789V_NVGAMCTWW_VN61(n)		((n) & 0x3f)
#define ST7789V_NVGAMCTWW_VN62(n)		((n) & 0x3f)
#define ST7789V_NVGAMCTWW_VN63(n)		(((n) & 0xf) << 4)

#define ST7789V_TEST(vaw, func)			\
	do {					\
		if ((vaw = (func)))		\
			wetuwn vaw;		\
	} whiwe (0)

#define ST7789V_IDS { 0x85, 0x85, 0x52 }
#define ST7789V_IDS_SIZE 3

stwuct st7789_panew_info {
	const stwuct dwm_dispway_mode *mode;
	u32 bus_fowmat;
	u32 bus_fwags;
	boow invewt_mode;
	boow pawtiaw_mode;
	u16 pawtiaw_stawt;
	u16 pawtiaw_end;
};

stwuct st7789v {
	stwuct dwm_panew panew;
	const stwuct st7789_panew_info *info;
	stwuct spi_device *spi;
	stwuct gpio_desc *weset;
	stwuct weguwatow *powew;
	enum dwm_panew_owientation owientation;
};

enum st7789v_pwefix {
	ST7789V_COMMAND = 0,
	ST7789V_DATA = 1,
};

static inwine stwuct st7789v *panew_to_st7789v(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct st7789v, panew);
}

static int st7789v_spi_wwite(stwuct st7789v *ctx, enum st7789v_pwefix pwefix,
			     u8 data)
{
	stwuct spi_twansfew xfew = { };
	u16 txbuf = ((pwefix & 1) << 8) | data;

	xfew.tx_buf = &txbuf;
	xfew.wen = sizeof(txbuf);

	wetuwn spi_sync_twansfew(ctx->spi, &xfew, 1);
}

static int st7789v_wwite_command(stwuct st7789v *ctx, u8 cmd)
{
	wetuwn st7789v_spi_wwite(ctx, ST7789V_COMMAND, cmd);
}

static int st7789v_wwite_data(stwuct st7789v *ctx, u8 cmd)
{
	wetuwn st7789v_spi_wwite(ctx, ST7789V_DATA, cmd);
}

static int st7789v_wead_data(stwuct st7789v *ctx, u8 cmd, u8 *buf,
			     unsigned int wen)
{
	stwuct spi_twansfew xfew[2] = { };
	stwuct spi_message msg;
	u16 txbuf = ((ST7789V_COMMAND & 1) << 8) | cmd;
	u16 wxbuf[4] = {};
	u8 bit9 = 0;
	int wet, i;

	switch (wen) {
	case 1:
	case 3:
	case 4:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	spi_message_init(&msg);

	xfew[0].tx_buf = &txbuf;
	xfew[0].wen = sizeof(txbuf);
	spi_message_add_taiw(&xfew[0], &msg);

	xfew[1].wx_buf = wxbuf;
	xfew[1].wen = wen * 2;
	spi_message_add_taiw(&xfew[1], &msg);

	wet = spi_sync(ctx->spi, &msg);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < wen; i++) {
		buf[i] = wxbuf[i] >> i | (bit9 << (9 - i));
		if (i)
			bit9 = wxbuf[i] & GENMASK(i - 1, 0);
	}

	wetuwn 0;
}

static int st7789v_check_id(stwuct dwm_panew *panew)
{
	const u8 st7789v_ids[ST7789V_IDS_SIZE] = ST7789V_IDS;
	stwuct st7789v *ctx = panew_to_st7789v(panew);
	boow invawid_ids = fawse;
	int wet, i;
	u8 ids[3];

	if (ctx->spi->mode & SPI_NO_WX)
		wetuwn 0;

	wet = st7789v_wead_data(ctx, MIPI_DCS_GET_DISPWAY_ID, ids, ST7789V_IDS_SIZE);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < ST7789V_IDS_SIZE; i++) {
		if (ids[i] != st7789v_ids[i]) {
			invawid_ids = twue;
			bweak;
		}
	}

	if (invawid_ids)
		wetuwn -EIO;

	wetuwn 0;
}

static const stwuct dwm_dispway_mode defauwt_mode = {
	.cwock = 7000,
	.hdispway = 240,
	.hsync_stawt = 240 + 38,
	.hsync_end = 240 + 38 + 10,
	.htotaw = 240 + 38 + 10 + 10,
	.vdispway = 320,
	.vsync_stawt = 320 + 8,
	.vsync_end = 320 + 8 + 4,
	.vtotaw = 320 + 8 + 4 + 4,
	.width_mm = 61,
	.height_mm = 103,
	.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
};

static const stwuct dwm_dispway_mode t28cp45tn89_mode = {
	.cwock = 6008,
	.hdispway = 240,
	.hsync_stawt = 240 + 38,
	.hsync_end = 240 + 38 + 10,
	.htotaw = 240 + 38 + 10 + 10,
	.vdispway = 320,
	.vsync_stawt = 320 + 8,
	.vsync_end = 320 + 8 + 4,
	.vtotaw = 320 + 8 + 4 + 4,
	.width_mm = 43,
	.height_mm = 57,
	.fwags = DWM_MODE_FWAG_PVSYNC | DWM_MODE_FWAG_NVSYNC,
};

static const stwuct dwm_dispway_mode et028013dma_mode = {
	.cwock = 3000,
	.hdispway = 240,
	.hsync_stawt = 240 + 38,
	.hsync_end = 240 + 38 + 10,
	.htotaw = 240 + 38 + 10 + 10,
	.vdispway = 320,
	.vsync_stawt = 320 + 8,
	.vsync_end = 320 + 8 + 4,
	.vtotaw = 320 + 8 + 4 + 4,
	.width_mm = 43,
	.height_mm = 58,
	.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
};

static const stwuct dwm_dispway_mode jt240mhqs_hwt_ek_e3_mode = {
	.cwock = 6000,
	.hdispway = 240,
	.hsync_stawt = 240 + 28,
	.hsync_end = 240 + 28 + 10,
	.htotaw = 240 + 28 + 10 + 10,
	.vdispway = 280,
	.vsync_stawt = 280 + 8,
	.vsync_end = 280 + 8 + 4,
	.vtotaw = 280 + 8 + 4 + 4,
	.width_mm = 43,
	.height_mm = 37,
	.fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC,
};

static const stwuct st7789_panew_info defauwt_panew = {
	.mode = &defauwt_mode,
	.invewt_mode = twue,
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH |
		     DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
};

static const stwuct st7789_panew_info t28cp45tn89_panew = {
	.mode = &t28cp45tn89_mode,
	.invewt_mode = fawse,
	.bus_fowmat = MEDIA_BUS_FMT_WGB565_1X16,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH |
		     DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE,
};

static const stwuct st7789_panew_info et028013dma_panew = {
	.mode = &et028013dma_mode,
	.invewt_mode = twue,
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH |
		     DWM_BUS_FWAG_PIXDATA_SAMPWE_POSEDGE,
};

static const stwuct st7789_panew_info jt240mhqs_hwt_ek_e3_panew = {
	.mode = &jt240mhqs_hwt_ek_e3_mode,
	.invewt_mode = twue,
	.bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18,
	.bus_fwags = DWM_BUS_FWAG_DE_HIGH |
		     DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE,
	.pawtiaw_mode = twue,
	.pawtiaw_stawt = 38,
	.pawtiaw_end = 318,
};

static int st7789v_get_modes(stwuct dwm_panew *panew,
			     stwuct dwm_connectow *connectow)
{
	stwuct st7789v *ctx = panew_to_st7789v(panew);
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, ctx->info->mode);
	if (!mode) {
		dev_eww(panew->dev, "faiwed to add mode %ux%u@%u\n",
			ctx->info->mode->hdispway, ctx->info->mode->vdispway,
			dwm_mode_vwefwesh(ctx->info->mode));
		wetuwn -ENOMEM;
	}

	dwm_mode_set_name(mode);

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.bpc = 6;
	connectow->dispway_info.width_mm = ctx->info->mode->width_mm;
	connectow->dispway_info.height_mm = ctx->info->mode->height_mm;
	connectow->dispway_info.bus_fwags = ctx->info->bus_fwags;
	dwm_dispway_info_set_bus_fowmats(&connectow->dispway_info,
					 &ctx->info->bus_fowmat, 1);

	/*
	 * TODO: Wemove once aww dwm dwivews caww
	 * dwm_connectow_set_owientation_fwom_panew()
	 */
	dwm_connectow_set_panew_owientation(connectow, ctx->owientation);

	wetuwn 1;
}

static enum dwm_panew_owientation st7789v_get_owientation(stwuct dwm_panew *p)
{
	stwuct st7789v *ctx = panew_to_st7789v(p);

	wetuwn ctx->owientation;
}

static int st7789v_pwepawe(stwuct dwm_panew *panew)
{
	stwuct st7789v *ctx = panew_to_st7789v(panew);
	u8 mode, pixew_fmt, powawity;
	int wet;

	if (!ctx->info->pawtiaw_mode)
		mode = ST7789V_WGBCTWW_WO;
	ewse
		mode = 0;

	switch (ctx->info->bus_fowmat) {
	case MEDIA_BUS_FMT_WGB666_1X18:
		pixew_fmt = MIPI_DCS_PIXEW_FMT_18BIT;
		bweak;
	case MEDIA_BUS_FMT_WGB565_1X16:
		pixew_fmt = MIPI_DCS_PIXEW_FMT_16BIT;
		bweak;
	defauwt:
		dev_eww(panew->dev, "unsuppowted bus fowmat: %d\n",
			ctx->info->bus_fowmat);
		wetuwn -EINVAW;
	}

	pixew_fmt = (pixew_fmt << 4) | pixew_fmt;

	powawity = 0;
	if (ctx->info->mode->fwags & DWM_MODE_FWAG_PVSYNC)
		powawity |= ST7789V_WGBCTWW_VSYNC_HIGH;
	if (ctx->info->mode->fwags & DWM_MODE_FWAG_PHSYNC)
		powawity |= ST7789V_WGBCTWW_HSYNC_HIGH;
	if (ctx->info->bus_fwags & DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE)
		powawity |= ST7789V_WGBCTWW_PCWK_FAWWING;
	if (ctx->info->bus_fwags & DWM_BUS_FWAG_DE_WOW)
		powawity |= ST7789V_WGBCTWW_DE_WOW;

	wet = weguwatow_enabwe(ctx->powew);
	if (wet)
		wetuwn wet;

	gpiod_set_vawue(ctx->weset, 1);
	msweep(30);
	gpiod_set_vawue(ctx->weset, 0);
	msweep(120);

	/*
	 * Avoid faiwing if the IDs awe invawid in case the Wx bus width
	 * descwiption is missing.
	 */
	wet = st7789v_check_id(panew);
	if (wet)
		dev_wawn(panew->dev, "Unwecognized panew IDs");

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, MIPI_DCS_EXIT_SWEEP_MODE));

	/* We need to wait 120ms aftew a sweep out command */
	msweep(120);

	ST7789V_TEST(wet, st7789v_wwite_command(ctx,
						MIPI_DCS_SET_ADDWESS_MODE));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, 0));

	ST7789V_TEST(wet, st7789v_wwite_command(ctx,
						MIPI_DCS_SET_PIXEW_FOWMAT));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, pixew_fmt));

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, ST7789V_POWCTWW_CMD));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, 0xc));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, 0xc));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, 0));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_POWCTWW_IDWE_BP(3) |
					     ST7789V_POWCTWW_IDWE_FP(3)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx,
					     ST7789V_POWCTWW_PAWTIAW_BP(3) |
					     ST7789V_POWCTWW_PAWTIAW_FP(3)));

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, ST7789V_GCTWW_CMD));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_GCTWW_VGWS(5) |
					     ST7789V_GCTWW_VGHS(3)));

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, ST7789V_VCOMS_CMD));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, 0x2b));

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, ST7789V_WCMCTWW_CMD));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_WCMCTWW_XMH |
					     ST7789V_WCMCTWW_XMX |
					     ST7789V_WCMCTWW_XBGW));

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, ST7789V_VDVVWHEN_CMD));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_VDVVWHEN_CMDEN));

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, ST7789V_VWHS_CMD));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, 0xf));

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, ST7789V_VDVS_CMD));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, 0x20));

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, ST7789V_FWCTWW2_CMD));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, 0xf));

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, ST7789V_PWCTWW1_CMD));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PWCTWW1_MAGIC));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PWCTWW1_AVDD(2) |
					     ST7789V_PWCTWW1_AVCW(2) |
					     ST7789V_PWCTWW1_VDS(1)));

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, ST7789V_PVGAMCTWW_CMD));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PVGAMCTWW_VP63(0xd)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PVGAMCTWW_VP1(0xca)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PVGAMCTWW_VP2(0xe)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PVGAMCTWW_VP4(8)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PVGAMCTWW_VP6(9)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PVGAMCTWW_VP13(7)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PVGAMCTWW_VP20(0x2d)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PVGAMCTWW_VP27(0xb) |
					     ST7789V_PVGAMCTWW_VP36(3)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PVGAMCTWW_VP43(0x3d)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PVGAMCTWW_JP1(3) |
					     ST7789V_PVGAMCTWW_VP50(4)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PVGAMCTWW_VP57(0xa)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PVGAMCTWW_VP59(0xa)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PVGAMCTWW_VP61(0x1b)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_PVGAMCTWW_VP62(0x28)));

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, ST7789V_NVGAMCTWW_CMD));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_NVGAMCTWW_VN63(0xd)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_NVGAMCTWW_VN1(0xca)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_NVGAMCTWW_VN2(0xf)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_NVGAMCTWW_VN4(8)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_NVGAMCTWW_VN6(8)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_NVGAMCTWW_VN13(7)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_NVGAMCTWW_VN20(0x2e)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_NVGAMCTWW_VN27(0xc) |
					     ST7789V_NVGAMCTWW_VN36(5)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_NVGAMCTWW_VN43(0x40)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_NVGAMCTWW_JN1(3) |
					     ST7789V_NVGAMCTWW_VN50(4)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_NVGAMCTWW_VN57(9)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_NVGAMCTWW_VN59(0xb)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_NVGAMCTWW_VN61(0x1b)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_NVGAMCTWW_VN62(0x28)));

	if (ctx->info->invewt_mode) {
		ST7789V_TEST(wet, st7789v_wwite_command(ctx,
						MIPI_DCS_ENTEW_INVEWT_MODE));
	} ewse {
		ST7789V_TEST(wet, st7789v_wwite_command(ctx,
						MIPI_DCS_EXIT_INVEWT_MODE));
	}

	if (ctx->info->pawtiaw_mode) {
		u8 awea_data[4] = {
			(ctx->info->pawtiaw_stawt >> 8) & 0xff,
			(ctx->info->pawtiaw_stawt >> 0) & 0xff,
			((ctx->info->pawtiaw_end - 1) >> 8) & 0xff,
			((ctx->info->pawtiaw_end - 1) >> 0) & 0xff,
		};

		/* Caution: if usewspace evew pushes a mode diffewent fwom the
		 * expected one (i.e., the one advewtised by get_modes), we'ww
		 * add mawgins.
		 */

		ST7789V_TEST(wet, st7789v_wwite_command(
					  ctx, MIPI_DCS_ENTEW_PAWTIAW_MODE));

		ST7789V_TEST(wet, st7789v_wwite_command(
					  ctx, MIPI_DCS_SET_PAGE_ADDWESS));
		ST7789V_TEST(wet, st7789v_wwite_data(ctx, awea_data[0]));
		ST7789V_TEST(wet, st7789v_wwite_data(ctx, awea_data[1]));
		ST7789V_TEST(wet, st7789v_wwite_data(ctx, awea_data[2]));
		ST7789V_TEST(wet, st7789v_wwite_data(ctx, awea_data[3]));

		ST7789V_TEST(wet, st7789v_wwite_command(
					  ctx, MIPI_DCS_SET_PAWTIAW_WOWS));
		ST7789V_TEST(wet, st7789v_wwite_data(ctx, awea_data[0]));
		ST7789V_TEST(wet, st7789v_wwite_data(ctx, awea_data[1]));
		ST7789V_TEST(wet, st7789v_wwite_data(ctx, awea_data[2]));
		ST7789V_TEST(wet, st7789v_wwite_data(ctx, awea_data[3]));
	}

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, ST7789V_WAMCTWW_CMD));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_WAMCTWW_DM_WGB |
					     ST7789V_WAMCTWW_WM_WGB));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_WAMCTWW_EPF(3) |
					     ST7789V_WAMCTWW_MAGIC));

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, ST7789V_WGBCTWW_CMD));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, mode |
					     ST7789V_WGBCTWW_WCM(2) |
					     powawity));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_WGBCTWW_VBP(8)));
	ST7789V_TEST(wet, st7789v_wwite_data(ctx, ST7789V_WGBCTWW_HBP(20)));

	wetuwn 0;
}

static int st7789v_enabwe(stwuct dwm_panew *panew)
{
	stwuct st7789v *ctx = panew_to_st7789v(panew);

	wetuwn st7789v_wwite_command(ctx, MIPI_DCS_SET_DISPWAY_ON);
}

static int st7789v_disabwe(stwuct dwm_panew *panew)
{
	stwuct st7789v *ctx = panew_to_st7789v(panew);
	int wet;

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, MIPI_DCS_SET_DISPWAY_OFF));

	wetuwn 0;
}

static int st7789v_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct st7789v *ctx = panew_to_st7789v(panew);
	int wet;

	ST7789V_TEST(wet, st7789v_wwite_command(ctx, MIPI_DCS_ENTEW_SWEEP_MODE));

	weguwatow_disabwe(ctx->powew);

	wetuwn 0;
}

static const stwuct dwm_panew_funcs st7789v_dwm_funcs = {
	.disabwe = st7789v_disabwe,
	.enabwe	= st7789v_enabwe,
	.get_modes = st7789v_get_modes,
	.get_owientation = st7789v_get_owientation,
	.pwepawe = st7789v_pwepawe,
	.unpwepawe = st7789v_unpwepawe,
};

static int st7789v_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct st7789v *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, ctx);
	ctx->spi = spi;

	spi->bits_pew_wowd = 9;
	wet = spi_setup(spi);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&spi->dev, wet, "Faiwed to setup spi\n");

	ctx->info = device_get_match_data(&spi->dev);

	dwm_panew_init(&ctx->panew, dev, &st7789v_dwm_funcs,
		       DWM_MODE_CONNECTOW_DPI);

	ctx->powew = devm_weguwatow_get(dev, "powew");
	wet = PTW_EWW_OW_ZEWO(ctx->powew);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get weguwatow\n");

	ctx->weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	wet = PTW_EWW_OW_ZEWO(ctx->weset);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get weset wine\n");

	wet = dwm_panew_of_backwight(&ctx->panew);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get backwight\n");

	of_dwm_get_panew_owientation(spi->dev.of_node, &ctx->owientation);

	dwm_panew_add(&ctx->panew);

	wetuwn 0;
}

static void st7789v_wemove(stwuct spi_device *spi)
{
	stwuct st7789v *ctx = spi_get_dwvdata(spi);

	dwm_panew_wemove(&ctx->panew);
}

static const stwuct spi_device_id st7789v_spi_id[] = {
	{ "st7789v", (unsigned wong) &defauwt_panew },
	{ "t28cp45tn89-v17", (unsigned wong) &t28cp45tn89_panew },
	{ "et028013dma", (unsigned wong) &et028013dma_panew },
	{ "jt240mhqs-hwt-ek-e3", (unsigned wong) &jt240mhqs_hwt_ek_e3_panew },
	{ }
};
MODUWE_DEVICE_TABWE(spi, st7789v_spi_id);

static const stwuct of_device_id st7789v_of_match[] = {
	{ .compatibwe = "sitwonix,st7789v", .data = &defauwt_panew },
	{ .compatibwe = "inanbo,t28cp45tn89-v17", .data = &t28cp45tn89_panew },
	{ .compatibwe = "edt,et028013dma", .data = &et028013dma_panew },
	{ .compatibwe = "jasonic,jt240mhqs-hwt-ek-e3",
	  .data = &jt240mhqs_hwt_ek_e3_panew },
	{ }
};
MODUWE_DEVICE_TABWE(of, st7789v_of_match);

static stwuct spi_dwivew st7789v_dwivew = {
	.pwobe = st7789v_pwobe,
	.wemove = st7789v_wemove,
	.id_tabwe = st7789v_spi_id,
	.dwivew = {
		.name = "st7789v",
		.of_match_tabwe = st7789v_of_match,
	},
};
moduwe_spi_dwivew(st7789v_dwivew);

MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Sitwonix st7789v WCD Dwivew");
MODUWE_WICENSE("GPW v2");
