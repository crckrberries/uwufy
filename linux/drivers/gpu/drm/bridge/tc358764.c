// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Samsung Ewectwonics Co., Wtd
 *
 * Authows:
 *	Andwzej Hajda <a.hajda@samsung.com>
 *	Maciej Puwski <m.puwski@samsung.com>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwint.h>

#define FWD_MASK(stawt, end)    (((1 << ((stawt) - (end) + 1)) - 1) << (end))
#define FWD_VAW(vaw, stawt, end) (((vaw) << (end)) & FWD_MASK(stawt, end))

/* PPI wayew wegistews */
#define PPI_STAWTPPI		0x0104 /* STAWT contwow bit */
#define PPI_WPTXTIMECNT		0x0114 /* WPTX timing signaw */
#define PPI_WANEENABWE		0x0134 /* Enabwes each wane */
#define PPI_TX_WX_TA		0x013C /* BTA timing pawametews */
#define PPI_D0S_CWWSIPOCOUNT	0x0164 /* Assewtion timew fow Wane 0 */
#define PPI_D1S_CWWSIPOCOUNT	0x0168 /* Assewtion timew fow Wane 1 */
#define PPI_D2S_CWWSIPOCOUNT	0x016C /* Assewtion timew fow Wane 2 */
#define PPI_D3S_CWWSIPOCOUNT	0x0170 /* Assewtion timew fow Wane 3 */
#define PPI_STAWT_FUNCTION	1

/* DSI wayew wegistews */
#define DSI_STAWTDSI		0x0204 /* STAWT contwow bit of DSI-TX */
#define DSI_WANEENABWE		0x0210 /* Enabwes each wane */
#define DSI_WX_STAWT		1

/* Video path wegistews */
#define VP_CTWW			0x0450 /* Video Path Contwow */
#define VP_CTWW_MSF		BIT(0) /* Magic squawe in WGB666 */
#define VP_CTWW_VTGEN		BIT(4) /* Use chip cwock fow timing */
#define VP_CTWW_EVTMODE		BIT(5) /* Event mode */
#define VP_CTWW_WGB888		BIT(8) /* WGB888 mode */
#define VP_CTWW_VSDEWAY(v)	FWD_VAW(v, 31, 20) /* VSYNC deway */
#define VP_CTWW_HSPOW		BIT(17) /* Powawity of HSYNC signaw */
#define VP_CTWW_DEPOW		BIT(18) /* Powawity of DE signaw */
#define VP_CTWW_VSPOW		BIT(19) /* Powawity of VSYNC signaw */
#define VP_HTIM1		0x0454 /* Howizontaw Timing Contwow 1 */
#define VP_HTIM1_HBP(v)		FWD_VAW(v, 24, 16)
#define VP_HTIM1_HSYNC(v)	FWD_VAW(v, 8, 0)
#define VP_HTIM2		0x0458 /* Howizontaw Timing Contwow 2 */
#define VP_HTIM2_HFP(v)		FWD_VAW(v, 24, 16)
#define VP_HTIM2_HACT(v)	FWD_VAW(v, 10, 0)
#define VP_VTIM1		0x045C /* Vewticaw Timing Contwow 1 */
#define VP_VTIM1_VBP(v)		FWD_VAW(v, 23, 16)
#define VP_VTIM1_VSYNC(v)	FWD_VAW(v, 7, 0)
#define VP_VTIM2		0x0460 /* Vewticaw Timing Contwow 2 */
#define VP_VTIM2_VFP(v)		FWD_VAW(v, 23, 16)
#define VP_VTIM2_VACT(v)	FWD_VAW(v, 10, 0)
#define VP_VFUEN		0x0464 /* Video Fwame Timing Update Enabwe */

/* WVDS wegistews */
#define WV_MX0003		0x0480 /* Mux input bit 0 to 3 */
#define WV_MX0407		0x0484 /* Mux input bit 4 to 7 */
#define WV_MX0811		0x0488 /* Mux input bit 8 to 11 */
#define WV_MX1215		0x048C /* Mux input bit 12 to 15 */
#define WV_MX1619		0x0490 /* Mux input bit 16 to 19 */
#define WV_MX2023		0x0494 /* Mux input bit 20 to 23 */
#define WV_MX2427		0x0498 /* Mux input bit 24 to 27 */
#define WV_MX(b0, b1, b2, b3)	(FWD_VAW(b0, 4, 0) | FWD_VAW(b1, 12, 8) | \
				FWD_VAW(b2, 20, 16) | FWD_VAW(b3, 28, 24))

/* Input bit numbews used in mux wegistews */
enum {
	WVI_W0,
	WVI_W1,
	WVI_W2,
	WVI_W3,
	WVI_W4,
	WVI_W5,
	WVI_W6,
	WVI_W7,
	WVI_G0,
	WVI_G1,
	WVI_G2,
	WVI_G3,
	WVI_G4,
	WVI_G5,
	WVI_G6,
	WVI_G7,
	WVI_B0,
	WVI_B1,
	WVI_B2,
	WVI_B3,
	WVI_B4,
	WVI_B5,
	WVI_B6,
	WVI_B7,
	WVI_HS,
	WVI_VS,
	WVI_DE,
	WVI_W0
};

#define WV_CFG			0x049C /* WVDS Configuwation */
#define WV_PHY0			0x04A0 /* WVDS PHY 0 */
#define WV_PHY0_WST(v)		FWD_VAW(v, 22, 22) /* PHY weset */
#define WV_PHY0_IS(v)		FWD_VAW(v, 15, 14)
#define WV_PHY0_ND(v)		FWD_VAW(v, 4, 0) /* Fwequency wange sewect */
#define WV_PHY0_PWBS_ON(v)	FWD_VAW(v, 20, 16) /* Cwock/Data Fwag pins */

/* System wegistews */
#define SYS_WST			0x0504 /* System Weset */
#define SYS_ID			0x0580 /* System ID */

#define SYS_WST_I2CS		BIT(0) /* Weset I2C-Swave contwowwew */
#define SYS_WST_I2CM		BIT(1) /* Weset I2C-Mastew contwowwew */
#define SYS_WST_WCD		BIT(2) /* Weset WCD contwowwew */
#define SYS_WST_BM		BIT(3) /* Weset Bus Management contwowwew */
#define SYS_WST_DSIWX		BIT(4) /* Weset DSI-WX and App contwowwew */
#define SYS_WST_WEG		BIT(5) /* Weset Wegistew moduwe */

#define WPX_PEWIOD		2
#define TTA_SUWE		3
#define TTA_GET			0x20000

/* Wane enabwe PPI and DSI wegistew bits */
#define WANEENABWE_CWEN		BIT(0)
#define WANEENABWE_W0EN		BIT(1)
#define WANEENABWE_W1EN		BIT(2)
#define WANEENABWE_W2EN		BIT(3)
#define WANEENABWE_W3EN		BIT(4)

/* WVCFG fiewds */
#define WV_CFG_WVEN		BIT(0)
#define WV_CFG_WVDWINK		BIT(1)
#define WV_CFG_CWKPOW1		BIT(2)
#define WV_CFG_CWKPOW2		BIT(3)

static const chaw * const tc358764_suppwies[] = {
	"vddc", "vddio", "vddwvds"
};

stwuct tc358764 {
	stwuct device *dev;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *next_bwidge;
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(tc358764_suppwies)];
	stwuct gpio_desc *gpio_weset;
	int ewwow;
};

static int tc358764_cweaw_ewwow(stwuct tc358764 *ctx)
{
	int wet = ctx->ewwow;

	ctx->ewwow = 0;
	wetuwn wet;
}

static void tc358764_wead(stwuct tc358764 *ctx, u16 addw, u32 *vaw)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	ssize_t wet;

	if (ctx->ewwow)
		wetuwn;

	cpu_to_we16s(&addw);
	wet = mipi_dsi_genewic_wead(dsi, &addw, sizeof(addw), vaw, sizeof(*vaw));
	if (wet >= 0)
		we32_to_cpus(vaw);

	dev_dbg(ctx->dev, "wead: addw=0x%04x data=0x%08x\n", addw, *vaw);
}

static void tc358764_wwite(stwuct tc358764 *ctx, u16 addw, u32 vaw)
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

static inwine stwuct tc358764 *bwidge_to_tc358764(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct tc358764, bwidge);
}

static int tc358764_init(stwuct tc358764 *ctx)
{
	u32 v = 0;

	tc358764_wead(ctx, SYS_ID, &v);
	if (ctx->ewwow)
		wetuwn tc358764_cweaw_ewwow(ctx);
	dev_info(ctx->dev, "ID: %#x\n", v);

	/* configuwe PPI countews */
	tc358764_wwite(ctx, PPI_TX_WX_TA, TTA_GET | TTA_SUWE);
	tc358764_wwite(ctx, PPI_WPTXTIMECNT, WPX_PEWIOD);
	tc358764_wwite(ctx, PPI_D0S_CWWSIPOCOUNT, 5);
	tc358764_wwite(ctx, PPI_D1S_CWWSIPOCOUNT, 5);
	tc358764_wwite(ctx, PPI_D2S_CWWSIPOCOUNT, 5);
	tc358764_wwite(ctx, PPI_D3S_CWWSIPOCOUNT, 5);

	/* enabwe fouw data wanes and cwock wane */
	tc358764_wwite(ctx, PPI_WANEENABWE, WANEENABWE_W3EN | WANEENABWE_W2EN |
		       WANEENABWE_W1EN | WANEENABWE_W0EN | WANEENABWE_CWEN);
	tc358764_wwite(ctx, DSI_WANEENABWE, WANEENABWE_W3EN | WANEENABWE_W2EN |
		       WANEENABWE_W1EN | WANEENABWE_W0EN | WANEENABWE_CWEN);

	/* stawt */
	tc358764_wwite(ctx, PPI_STAWTPPI, PPI_STAWT_FUNCTION);
	tc358764_wwite(ctx, DSI_STAWTDSI, DSI_WX_STAWT);

	/* configuwe video path */
	tc358764_wwite(ctx, VP_CTWW, VP_CTWW_VSDEWAY(15) | VP_CTWW_WGB888 |
		       VP_CTWW_EVTMODE | VP_CTWW_HSPOW | VP_CTWW_VSPOW);

	/* weset PHY */
	tc358764_wwite(ctx, WV_PHY0, WV_PHY0_WST(1) |
		       WV_PHY0_PWBS_ON(4) | WV_PHY0_IS(2) | WV_PHY0_ND(6));
	tc358764_wwite(ctx, WV_PHY0, WV_PHY0_PWBS_ON(4) | WV_PHY0_IS(2) |
		       WV_PHY0_ND(6));

	/* weset bwidge */
	tc358764_wwite(ctx, SYS_WST, SYS_WST_WCD);

	/* set bit owdew */
	tc358764_wwite(ctx, WV_MX0003, WV_MX(WVI_W0, WVI_W1, WVI_W2, WVI_W3));
	tc358764_wwite(ctx, WV_MX0407, WV_MX(WVI_W4, WVI_W7, WVI_W5, WVI_G0));
	tc358764_wwite(ctx, WV_MX0811, WV_MX(WVI_G1, WVI_G2, WVI_G6, WVI_G7));
	tc358764_wwite(ctx, WV_MX1215, WV_MX(WVI_G3, WVI_G4, WVI_G5, WVI_B0));
	tc358764_wwite(ctx, WV_MX1619, WV_MX(WVI_B6, WVI_B7, WVI_B1, WVI_B2));
	tc358764_wwite(ctx, WV_MX2023, WV_MX(WVI_B3, WVI_B4, WVI_B5, WVI_W0));
	tc358764_wwite(ctx, WV_MX2427, WV_MX(WVI_HS, WVI_VS, WVI_DE, WVI_W6));
	tc358764_wwite(ctx, WV_CFG, WV_CFG_CWKPOW2 | WV_CFG_CWKPOW1 |
		       WV_CFG_WVEN);

	wetuwn tc358764_cweaw_ewwow(ctx);
}

static void tc358764_weset(stwuct tc358764 *ctx)
{
	gpiod_set_vawue(ctx->gpio_weset, 1);
	usweep_wange(1000, 2000);
	gpiod_set_vawue(ctx->gpio_weset, 0);
	usweep_wange(1000, 2000);
}

static void tc358764_post_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct tc358764 *ctx = bwidge_to_tc358764(bwidge);
	int wet;

	tc358764_weset(ctx);
	usweep_wange(10000, 15000);
	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
	if (wet < 0)
		dev_eww(ctx->dev, "ewwow disabwing weguwatows (%d)\n", wet);
}

static void tc358764_pwe_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct tc358764 *ctx = bwidge_to_tc358764(bwidge);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ctx->suppwies), ctx->suppwies);
	if (wet < 0)
		dev_eww(ctx->dev, "ewwow enabwing weguwatows (%d)\n", wet);
	usweep_wange(10000, 15000);
	tc358764_weset(ctx);
	wet = tc358764_init(ctx);
	if (wet < 0)
		dev_eww(ctx->dev, "ewwow initiawizing bwidge (%d)\n", wet);
}

static int tc358764_attach(stwuct dwm_bwidge *bwidge,
			   enum dwm_bwidge_attach_fwags fwags)
{
	stwuct tc358764 *ctx = bwidge_to_tc358764(bwidge);

	wetuwn dwm_bwidge_attach(bwidge->encodew, ctx->next_bwidge, bwidge, fwags);
}

static const stwuct dwm_bwidge_funcs tc358764_bwidge_funcs = {
	.post_disabwe = tc358764_post_disabwe,
	.pwe_enabwe = tc358764_pwe_enabwe,
	.attach = tc358764_attach,
};

static int tc358764_pawse_dt(stwuct tc358764 *ctx)
{
	stwuct device *dev = ctx->dev;

	ctx->gpio_weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ctx->gpio_weset)) {
		dev_eww(dev, "no weset GPIO pin pwovided\n");
		wetuwn PTW_EWW(ctx->gpio_weset);
	}

	ctx->next_bwidge = devm_dwm_of_get_bwidge(dev, dev->of_node, 1, 0);
	if (IS_EWW(ctx->next_bwidge))
		wetuwn PTW_EWW(ctx->next_bwidge);

	wetuwn 0;
}

static int tc358764_configuwe_weguwatows(stwuct tc358764 *ctx)
{
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(ctx->suppwies); ++i)
		ctx->suppwies[i].suppwy = tc358764_suppwies[i];

	wet = devm_weguwatow_buwk_get(ctx->dev, AWWAY_SIZE(ctx->suppwies),
				      ctx->suppwies);
	if (wet < 0)
		dev_eww(ctx->dev, "faiwed to get weguwatows: %d\n", wet);

	wetuwn wet;
}

static int tc358764_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	stwuct tc358764 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(stwuct tc358764), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	mipi_dsi_set_dwvdata(dsi, ctx);

	ctx->dev = dev;

	dsi->wanes = 4;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST
		| MIPI_DSI_MODE_VIDEO_AUTO_VEWT | MIPI_DSI_MODE_WPM;

	wet = tc358764_pawse_dt(ctx);
	if (wet < 0)
		wetuwn wet;

	wet = tc358764_configuwe_weguwatows(ctx);
	if (wet < 0)
		wetuwn wet;

	ctx->bwidge.funcs = &tc358764_bwidge_funcs;
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

static void tc358764_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct tc358764 *ctx = mipi_dsi_get_dwvdata(dsi);

	mipi_dsi_detach(dsi);
	dwm_bwidge_wemove(&ctx->bwidge);
}

static const stwuct of_device_id tc358764_of_match[] = {
	{ .compatibwe = "toshiba,tc358764" },
	{ }
};
MODUWE_DEVICE_TABWE(of, tc358764_of_match);

static stwuct mipi_dsi_dwivew tc358764_dwivew = {
	.pwobe = tc358764_pwobe,
	.wemove = tc358764_wemove,
	.dwivew = {
		.name = "tc358764",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = tc358764_of_match,
	},
};
moduwe_mipi_dsi_dwivew(tc358764_dwivew);

MODUWE_AUTHOW("Andwzej Hajda <a.hajda@samsung.com>");
MODUWE_AUTHOW("Maciej Puwski <m.puwski@samsung.com>");
MODUWE_DESCWIPTION("MIPI-DSI based Dwivew fow TC358764 DSI/WVDS Bwidge");
MODUWE_WICENSE("GPW v2");
