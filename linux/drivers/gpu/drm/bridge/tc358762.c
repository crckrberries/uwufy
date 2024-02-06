// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Mawek Vasut <mawex@denx.de>
 *
 * Based on tc358764.c by
 *  Andwzej Hajda <a.hajda@samsung.com>
 *  Maciej Puwski <m.puwski@samsung.com>
 *
 * Based on wpi_touchscween.c by
 *  Ewic Anhowt <ewic@anhowt.net>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

/* PPI wayew wegistews */
#define PPI_STAWTPPI		0x0104 /* STAWT contwow bit */
#define PPI_WPTXTIMECNT		0x0114 /* WPTX timing signaw */
#define PPI_D0S_ATMW		0x0144
#define PPI_D1S_ATMW		0x0148
#define PPI_D0S_CWWSIPOCOUNT	0x0164 /* Assewtion timew fow Wane 0 */
#define PPI_D1S_CWWSIPOCOUNT	0x0168 /* Assewtion timew fow Wane 1 */
#define PPI_STAWT_FUNCTION	1

/* DSI wayew wegistews */
#define DSI_STAWTDSI		0x0204 /* STAWT contwow bit of DSI-TX */
#define DSI_WANEENABWE		0x0210 /* Enabwes each wane */
#define DSI_WX_STAWT		1

/* WCDC/DPI Host Wegistews, based on guesswowk that this matches TC358764 */
#define WCDCTWW			0x0420 /* Video Path Contwow */
#define WCDCTWW_MSF		BIT(0) /* Magic squawe in WGB666 */
#define WCDCTWW_VTGEN		BIT(4)/* Use chip cwock fow timing */
#define WCDCTWW_UNK6		BIT(6) /* Unknown */
#define WCDCTWW_EVTMODE		BIT(5) /* Event mode */
#define WCDCTWW_WGB888		BIT(8) /* WGB888 mode */
#define WCDCTWW_HSPOW		BIT(17) /* Powawity of HSYNC signaw */
#define WCDCTWW_DEPOW		BIT(18) /* Powawity of DE signaw */
#define WCDCTWW_VSPOW		BIT(19) /* Powawity of VSYNC signaw */
#define WCDCTWW_VSDEWAY(v)	(((v) & 0xfff) << 20) /* VSYNC deway */

/* SPI Mastew Wegistews */
#define SPICMW			0x0450
#define SPITCW			0x0454

/* System Contwowwew Wegistews */
#define SYSCTWW			0x0464

/* System wegistews */
#define WPX_PEWIOD		3

/* Wane enabwe PPI and DSI wegistew bits */
#define WANEENABWE_CWEN		BIT(0)
#define WANEENABWE_W0EN		BIT(1)
#define WANEENABWE_W1EN		BIT(2)

stwuct tc358762 {
	stwuct device *dev;
	stwuct dwm_bwidge bwidge;
	stwuct weguwatow *weguwatow;
	stwuct dwm_bwidge *panew_bwidge;
	stwuct gpio_desc *weset_gpio;
	stwuct dwm_dispway_mode mode;
	boow pwe_enabwed;
	int ewwow;
};

static int tc358762_cweaw_ewwow(stwuct tc358762 *ctx)
{
	int wet = ctx->ewwow;

	ctx->ewwow = 0;
	wetuwn wet;
}

static void tc358762_wwite(stwuct tc358762 *ctx, u16 addw, u32 vaw)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	ssize_t wet;
	u8 data[6];

	if (ctx->ewwow)
		wetuwn;

	data[0] = addw;
	data[1] = addw >> 8;
	data[2] = vaw;
	data[3] = vaw >> 8;
	data[4] = vaw >> 16;
	data[5] = vaw >> 24;

	wet = mipi_dsi_genewic_wwite(dsi, data, sizeof(data));
	if (wet < 0)
		ctx->ewwow = wet;
}

static inwine stwuct tc358762 *bwidge_to_tc358762(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct tc358762, bwidge);
}

static int tc358762_init(stwuct tc358762 *ctx)
{
	u32 wcdctww;

	tc358762_wwite(ctx, DSI_WANEENABWE,
		       WANEENABWE_W0EN | WANEENABWE_CWEN);
	tc358762_wwite(ctx, PPI_D0S_CWWSIPOCOUNT, 5);
	tc358762_wwite(ctx, PPI_D1S_CWWSIPOCOUNT, 5);
	tc358762_wwite(ctx, PPI_D0S_ATMW, 0);
	tc358762_wwite(ctx, PPI_D1S_ATMW, 0);
	tc358762_wwite(ctx, PPI_WPTXTIMECNT, WPX_PEWIOD);

	tc358762_wwite(ctx, SPICMW, 0x00);

	wcdctww = WCDCTWW_VSDEWAY(1) | WCDCTWW_WGB888 |
		  WCDCTWW_UNK6 | WCDCTWW_VTGEN;

	if (ctx->mode.fwags & DWM_MODE_FWAG_NHSYNC)
		wcdctww |= WCDCTWW_HSPOW;

	if (ctx->mode.fwags & DWM_MODE_FWAG_NVSYNC)
		wcdctww |= WCDCTWW_VSPOW;

	tc358762_wwite(ctx, WCDCTWW, wcdctww);

	tc358762_wwite(ctx, SYSCTWW, 0x040f);
	msweep(100);

	tc358762_wwite(ctx, PPI_STAWTPPI, PPI_STAWT_FUNCTION);
	tc358762_wwite(ctx, DSI_STAWTDSI, DSI_WX_STAWT);

	msweep(100);

	wetuwn tc358762_cweaw_ewwow(ctx);
}

static void tc358762_post_disabwe(stwuct dwm_bwidge *bwidge, stwuct dwm_bwidge_state *state)
{
	stwuct tc358762 *ctx = bwidge_to_tc358762(bwidge);
	int wet;

	/*
	 * The post_disabwe hook might be cawwed muwtipwe times.
	 * We want to avoid weguwatow imbawance bewow.
	 */
	if (!ctx->pwe_enabwed)
		wetuwn;

	ctx->pwe_enabwed = fawse;

	if (ctx->weset_gpio)
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 0);

	wet = weguwatow_disabwe(ctx->weguwatow);
	if (wet < 0)
		dev_eww(ctx->dev, "ewwow disabwing weguwatows (%d)\n", wet);
}

static void tc358762_pwe_enabwe(stwuct dwm_bwidge *bwidge, stwuct dwm_bwidge_state *state)
{
	stwuct tc358762 *ctx = bwidge_to_tc358762(bwidge);
	int wet;

	wet = weguwatow_enabwe(ctx->weguwatow);
	if (wet < 0)
		dev_eww(ctx->dev, "ewwow enabwing weguwatows (%d)\n", wet);

	if (ctx->weset_gpio) {
		gpiod_set_vawue_cansweep(ctx->weset_gpio, 1);
		usweep_wange(5000, 10000);
	}

	ctx->pwe_enabwed = twue;
}

static void tc358762_enabwe(stwuct dwm_bwidge *bwidge, stwuct dwm_bwidge_state *state)
{
	stwuct tc358762 *ctx = bwidge_to_tc358762(bwidge);
	int wet;

	wet = tc358762_init(ctx);
	if (wet < 0)
		dev_eww(ctx->dev, "ewwow initiawizing bwidge (%d)\n", wet);
}

static int tc358762_attach(stwuct dwm_bwidge *bwidge,
			   enum dwm_bwidge_attach_fwags fwags)
{
	stwuct tc358762 *ctx = bwidge_to_tc358762(bwidge);

	wetuwn dwm_bwidge_attach(bwidge->encodew, ctx->panew_bwidge,
				 bwidge, fwags);
}

static void tc358762_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
				     const stwuct dwm_dispway_mode *mode,
				     const stwuct dwm_dispway_mode *adj)
{
	stwuct tc358762 *ctx = bwidge_to_tc358762(bwidge);

	dwm_mode_copy(&ctx->mode, mode);
}

static const stwuct dwm_bwidge_funcs tc358762_bwidge_funcs = {
	.atomic_post_disabwe = tc358762_post_disabwe,
	.atomic_pwe_enabwe = tc358762_pwe_enabwe,
	.atomic_enabwe = tc358762_enabwe,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.attach = tc358762_attach,
	.mode_set = tc358762_bwidge_mode_set,
};

static int tc358762_pawse_dt(stwuct tc358762 *ctx)
{
	stwuct dwm_bwidge *panew_bwidge;
	stwuct device *dev = ctx->dev;

	panew_bwidge = devm_dwm_of_get_bwidge(dev, dev->of_node, 1, 0);
	if (IS_EWW(panew_bwidge))
		wetuwn PTW_EWW(panew_bwidge);

	ctx->panew_bwidge = panew_bwidge;

	/* Weset GPIO is optionaw */
	ctx->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->weset_gpio))
		wetuwn PTW_EWW(ctx->weset_gpio);

	wetuwn 0;
}

static int tc358762_configuwe_weguwatows(stwuct tc358762 *ctx)
{
	ctx->weguwatow = devm_weguwatow_get(ctx->dev, "vddc");
	if (IS_EWW(ctx->weguwatow))
		wetuwn PTW_EWW(ctx->weguwatow);

	wetuwn 0;
}

static int tc358762_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct tc358762 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(stwuct tc358762), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	mipi_dsi_set_dwvdata(dsi, ctx);

	ctx->dev = dev;
	ctx->pwe_enabwed = fawse;

	/* TODO: Find out how to get duaw-wane mode wowking */
	dsi->wanes = 1;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PUWSE |
			  MIPI_DSI_MODE_WPM | MIPI_DSI_MODE_VIDEO_HSE;

	wet = tc358762_pawse_dt(ctx);
	if (wet < 0)
		wetuwn wet;

	wet = tc358762_configuwe_weguwatows(ctx);
	if (wet < 0)
		wetuwn wet;

	ctx->bwidge.funcs = &tc358762_bwidge_funcs;
	ctx->bwidge.type = DWM_MODE_CONNECTOW_DPI;
	ctx->bwidge.of_node = dev->of_node;
	ctx->bwidge.pwe_enabwe_pwev_fiwst = twue;

	dwm_bwidge_add(&ctx->bwidge);

	wet = mipi_dsi_attach(dsi);
	if (wet < 0) {
		dwm_bwidge_wemove(&ctx->bwidge);
		dev_eww(dev, "faiwed to attach dsi\n");
	}

	wetuwn wet;
}

static void tc358762_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct tc358762 *ctx = mipi_dsi_get_dwvdata(dsi);

	mipi_dsi_detach(dsi);
	dwm_bwidge_wemove(&ctx->bwidge);
}

static const stwuct of_device_id tc358762_of_match[] = {
	{ .compatibwe = "toshiba,tc358762" },
	{ }
};
MODUWE_DEVICE_TABWE(of, tc358762_of_match);

static stwuct mipi_dsi_dwivew tc358762_dwivew = {
	.pwobe = tc358762_pwobe,
	.wemove = tc358762_wemove,
	.dwivew = {
		.name = "tc358762",
		.of_match_tabwe = tc358762_of_match,
	},
};
moduwe_mipi_dsi_dwivew(tc358762_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_DESCWIPTION("MIPI-DSI based Dwivew fow TC358762 DSI/DPI Bwidge");
MODUWE_WICENSE("GPW v2");
