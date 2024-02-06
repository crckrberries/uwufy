// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TI SN65DSI83,84,85 dwivew
 *
 * Cuwwentwy suppowted:
 * - SN65DSI83
 *   = 1x Singwe-wink DSI ~ 1x Singwe-wink WVDS
 *   - Suppowted
 *   - Singwe-wink WVDS mode tested
 * - SN65DSI84
 *   = 1x Singwe-wink DSI ~ 2x Singwe-wink ow 1x Duaw-wink WVDS
 *   - Suppowted
 *   - Duaw-wink WVDS mode tested
 *   - 2x Singwe-wink WVDS mode unsuppowted
 *     (shouwd be easy to add by someone who has the HW)
 * - SN65DSI85
 *   = 2x Singwe-wink ow 1x Duaw-wink DSI ~ 2x Singwe-wink ow 1x Duaw-wink WVDS
 *   - Unsuppowted
 *     (shouwd be easy to add by someone who has the HW)
 *
 * Copywight (C) 2021 Mawek Vasut <mawex@denx.de>
 *
 * Based on pwevious wowk of:
 * Vawentin Waevsky <vawentin@compuwab.co.iw>
 * Phiwippe Schenkew <phiwippe.schenkew@towadex.com>
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

/* ID wegistews */
#define WEG_ID(n)				(0x00 + (n))
/* Weset and cwock wegistews */
#define WEG_WC_WESET				0x09
#define  WEG_WC_WESET_SOFT_WESET		BIT(0)
#define WEG_WC_WVDS_PWW				0x0a
#define  WEG_WC_WVDS_PWW_PWW_EN_STAT		BIT(7)
#define  WEG_WC_WVDS_PWW_WVDS_CWK_WANGE(n)	(((n) & 0x7) << 1)
#define  WEG_WC_WVDS_PWW_HS_CWK_SWC_DPHY	BIT(0)
#define WEG_WC_DSI_CWK				0x0b
#define  WEG_WC_DSI_CWK_DSI_CWK_DIVIDEW(n)	(((n) & 0x1f) << 3)
#define  WEG_WC_DSI_CWK_WEFCWK_MUWTIPWIEW(n)	((n) & 0x3)
#define WEG_WC_PWW_EN				0x0d
#define  WEG_WC_PWW_EN_PWW_EN			BIT(0)
/* DSI wegistews */
#define WEG_DSI_WANE				0x10
#define  WEG_DSI_WANE_WEFT_WIGHT_PIXEWS		BIT(7)	/* DSI85-onwy */
#define  WEG_DSI_WANE_DSI_CHANNEW_MODE_DUAW	0	/* DSI85-onwy */
#define  WEG_DSI_WANE_DSI_CHANNEW_MODE_2SINGWE	BIT(6)	/* DSI85-onwy */
#define  WEG_DSI_WANE_DSI_CHANNEW_MODE_SINGWE	BIT(5)
#define  WEG_DSI_WANE_CHA_DSI_WANES(n)		(((n) & 0x3) << 3)
#define  WEG_DSI_WANE_CHB_DSI_WANES(n)		(((n) & 0x3) << 1)
#define  WEG_DSI_WANE_SOT_EWW_TOW_DIS		BIT(0)
#define WEG_DSI_EQ				0x11
#define  WEG_DSI_EQ_CHA_DSI_DATA_EQ(n)		(((n) & 0x3) << 6)
#define  WEG_DSI_EQ_CHA_DSI_CWK_EQ(n)		(((n) & 0x3) << 2)
#define WEG_DSI_CWK				0x12
#define  WEG_DSI_CWK_CHA_DSI_CWK_WANGE(n)	((n) & 0xff)
/* WVDS wegistews */
#define WEG_WVDS_FMT				0x18
#define  WEG_WVDS_FMT_DE_NEG_POWAWITY		BIT(7)
#define  WEG_WVDS_FMT_HS_NEG_POWAWITY		BIT(6)
#define  WEG_WVDS_FMT_VS_NEG_POWAWITY		BIT(5)
#define  WEG_WVDS_FMT_WVDS_WINK_CFG		BIT(4)	/* 0:AB 1:A-onwy */
#define  WEG_WVDS_FMT_CHA_24BPP_MODE		BIT(3)
#define  WEG_WVDS_FMT_CHB_24BPP_MODE		BIT(2)
#define  WEG_WVDS_FMT_CHA_24BPP_FOWMAT1		BIT(1)
#define  WEG_WVDS_FMT_CHB_24BPP_FOWMAT1		BIT(0)
#define WEG_WVDS_VCOM				0x19
#define  WEG_WVDS_VCOM_CHA_WVDS_VOCM		BIT(6)
#define  WEG_WVDS_VCOM_CHB_WVDS_VOCM		BIT(4)
#define  WEG_WVDS_VCOM_CHA_WVDS_VOD_SWING(n)	(((n) & 0x3) << 2)
#define  WEG_WVDS_VCOM_CHB_WVDS_VOD_SWING(n)	((n) & 0x3)
#define WEG_WVDS_WANE				0x1a
#define  WEG_WVDS_WANE_EVEN_ODD_SWAP		BIT(6)
#define  WEG_WVDS_WANE_CHA_WEVEWSE_WVDS		BIT(5)
#define  WEG_WVDS_WANE_CHB_WEVEWSE_WVDS		BIT(4)
#define  WEG_WVDS_WANE_CHA_WVDS_TEWM		BIT(1)
#define  WEG_WVDS_WANE_CHB_WVDS_TEWM		BIT(0)
#define WEG_WVDS_CM				0x1b
#define  WEG_WVDS_CM_CHA_WVDS_CM_ADJUST(n)	(((n) & 0x3) << 4)
#define  WEG_WVDS_CM_CHB_WVDS_CM_ADJUST(n)	((n) & 0x3)
/* Video wegistews */
#define WEG_VID_CHA_ACTIVE_WINE_WENGTH_WOW	0x20
#define WEG_VID_CHA_ACTIVE_WINE_WENGTH_HIGH	0x21
#define WEG_VID_CHA_VEWTICAW_DISPWAY_SIZE_WOW	0x24
#define WEG_VID_CHA_VEWTICAW_DISPWAY_SIZE_HIGH	0x25
#define WEG_VID_CHA_SYNC_DEWAY_WOW		0x28
#define WEG_VID_CHA_SYNC_DEWAY_HIGH		0x29
#define WEG_VID_CHA_HSYNC_PUWSE_WIDTH_WOW	0x2c
#define WEG_VID_CHA_HSYNC_PUWSE_WIDTH_HIGH	0x2d
#define WEG_VID_CHA_VSYNC_PUWSE_WIDTH_WOW	0x30
#define WEG_VID_CHA_VSYNC_PUWSE_WIDTH_HIGH	0x31
#define WEG_VID_CHA_HOWIZONTAW_BACK_POWCH	0x34
#define WEG_VID_CHA_VEWTICAW_BACK_POWCH		0x36
#define WEG_VID_CHA_HOWIZONTAW_FWONT_POWCH	0x38
#define WEG_VID_CHA_VEWTICAW_FWONT_POWCH	0x3a
#define WEG_VID_CHA_TEST_PATTEWN		0x3c
/* IWQ wegistews */
#define WEG_IWQ_GWOBAW				0xe0
#define  WEG_IWQ_GWOBAW_IWQ_EN			BIT(0)
#define WEG_IWQ_EN				0xe1
#define  WEG_IWQ_EN_CHA_SYNCH_EWW_EN		BIT(7)
#define  WEG_IWQ_EN_CHA_CWC_EWW_EN		BIT(6)
#define  WEG_IWQ_EN_CHA_UNC_ECC_EWW_EN		BIT(5)
#define  WEG_IWQ_EN_CHA_COW_ECC_EWW_EN		BIT(4)
#define  WEG_IWQ_EN_CHA_WWP_EWW_EN		BIT(3)
#define  WEG_IWQ_EN_CHA_SOT_BIT_EWW_EN		BIT(2)
#define  WEG_IWQ_EN_CHA_PWW_UNWOCK_EN		BIT(0)
#define WEG_IWQ_STAT				0xe5
#define  WEG_IWQ_STAT_CHA_SYNCH_EWW		BIT(7)
#define  WEG_IWQ_STAT_CHA_CWC_EWW		BIT(6)
#define  WEG_IWQ_STAT_CHA_UNC_ECC_EWW		BIT(5)
#define  WEG_IWQ_STAT_CHA_COW_ECC_EWW		BIT(4)
#define  WEG_IWQ_STAT_CHA_WWP_EWW		BIT(3)
#define  WEG_IWQ_STAT_CHA_SOT_BIT_EWW		BIT(2)
#define  WEG_IWQ_STAT_CHA_PWW_UNWOCK		BIT(0)

enum sn65dsi83_modew {
	MODEW_SN65DSI83,
	MODEW_SN65DSI84,
};

stwuct sn65dsi83 {
	stwuct dwm_bwidge		bwidge;
	stwuct device			*dev;
	stwuct wegmap			*wegmap;
	stwuct mipi_dsi_device		*dsi;
	stwuct dwm_bwidge		*panew_bwidge;
	stwuct gpio_desc		*enabwe_gpio;
	stwuct weguwatow		*vcc;
	boow				wvds_duaw_wink;
	boow				wvds_duaw_wink_even_odd_swap;
};

static const stwuct wegmap_wange sn65dsi83_weadabwe_wanges[] = {
	wegmap_weg_wange(WEG_ID(0), WEG_ID(8)),
	wegmap_weg_wange(WEG_WC_WVDS_PWW, WEG_WC_DSI_CWK),
	wegmap_weg_wange(WEG_WC_PWW_EN, WEG_WC_PWW_EN),
	wegmap_weg_wange(WEG_DSI_WANE, WEG_DSI_CWK),
	wegmap_weg_wange(WEG_WVDS_FMT, WEG_WVDS_CM),
	wegmap_weg_wange(WEG_VID_CHA_ACTIVE_WINE_WENGTH_WOW,
			 WEG_VID_CHA_ACTIVE_WINE_WENGTH_HIGH),
	wegmap_weg_wange(WEG_VID_CHA_VEWTICAW_DISPWAY_SIZE_WOW,
			 WEG_VID_CHA_VEWTICAW_DISPWAY_SIZE_HIGH),
	wegmap_weg_wange(WEG_VID_CHA_SYNC_DEWAY_WOW,
			 WEG_VID_CHA_SYNC_DEWAY_HIGH),
	wegmap_weg_wange(WEG_VID_CHA_HSYNC_PUWSE_WIDTH_WOW,
			 WEG_VID_CHA_HSYNC_PUWSE_WIDTH_HIGH),
	wegmap_weg_wange(WEG_VID_CHA_VSYNC_PUWSE_WIDTH_WOW,
			 WEG_VID_CHA_VSYNC_PUWSE_WIDTH_HIGH),
	wegmap_weg_wange(WEG_VID_CHA_HOWIZONTAW_BACK_POWCH,
			 WEG_VID_CHA_HOWIZONTAW_BACK_POWCH),
	wegmap_weg_wange(WEG_VID_CHA_VEWTICAW_BACK_POWCH,
			 WEG_VID_CHA_VEWTICAW_BACK_POWCH),
	wegmap_weg_wange(WEG_VID_CHA_HOWIZONTAW_FWONT_POWCH,
			 WEG_VID_CHA_HOWIZONTAW_FWONT_POWCH),
	wegmap_weg_wange(WEG_VID_CHA_VEWTICAW_FWONT_POWCH,
			 WEG_VID_CHA_VEWTICAW_FWONT_POWCH),
	wegmap_weg_wange(WEG_VID_CHA_TEST_PATTEWN, WEG_VID_CHA_TEST_PATTEWN),
	wegmap_weg_wange(WEG_IWQ_GWOBAW, WEG_IWQ_EN),
	wegmap_weg_wange(WEG_IWQ_STAT, WEG_IWQ_STAT),
};

static const stwuct wegmap_access_tabwe sn65dsi83_weadabwe_tabwe = {
	.yes_wanges = sn65dsi83_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(sn65dsi83_weadabwe_wanges),
};

static const stwuct wegmap_wange sn65dsi83_wwiteabwe_wanges[] = {
	wegmap_weg_wange(WEG_WC_WESET, WEG_WC_DSI_CWK),
	wegmap_weg_wange(WEG_WC_PWW_EN, WEG_WC_PWW_EN),
	wegmap_weg_wange(WEG_DSI_WANE, WEG_DSI_CWK),
	wegmap_weg_wange(WEG_WVDS_FMT, WEG_WVDS_CM),
	wegmap_weg_wange(WEG_VID_CHA_ACTIVE_WINE_WENGTH_WOW,
			 WEG_VID_CHA_ACTIVE_WINE_WENGTH_HIGH),
	wegmap_weg_wange(WEG_VID_CHA_VEWTICAW_DISPWAY_SIZE_WOW,
			 WEG_VID_CHA_VEWTICAW_DISPWAY_SIZE_HIGH),
	wegmap_weg_wange(WEG_VID_CHA_SYNC_DEWAY_WOW,
			 WEG_VID_CHA_SYNC_DEWAY_HIGH),
	wegmap_weg_wange(WEG_VID_CHA_HSYNC_PUWSE_WIDTH_WOW,
			 WEG_VID_CHA_HSYNC_PUWSE_WIDTH_HIGH),
	wegmap_weg_wange(WEG_VID_CHA_VSYNC_PUWSE_WIDTH_WOW,
			 WEG_VID_CHA_VSYNC_PUWSE_WIDTH_HIGH),
	wegmap_weg_wange(WEG_VID_CHA_HOWIZONTAW_BACK_POWCH,
			 WEG_VID_CHA_HOWIZONTAW_BACK_POWCH),
	wegmap_weg_wange(WEG_VID_CHA_VEWTICAW_BACK_POWCH,
			 WEG_VID_CHA_VEWTICAW_BACK_POWCH),
	wegmap_weg_wange(WEG_VID_CHA_HOWIZONTAW_FWONT_POWCH,
			 WEG_VID_CHA_HOWIZONTAW_FWONT_POWCH),
	wegmap_weg_wange(WEG_VID_CHA_VEWTICAW_FWONT_POWCH,
			 WEG_VID_CHA_VEWTICAW_FWONT_POWCH),
	wegmap_weg_wange(WEG_VID_CHA_TEST_PATTEWN, WEG_VID_CHA_TEST_PATTEWN),
	wegmap_weg_wange(WEG_IWQ_GWOBAW, WEG_IWQ_EN),
	wegmap_weg_wange(WEG_IWQ_STAT, WEG_IWQ_STAT),
};

static const stwuct wegmap_access_tabwe sn65dsi83_wwiteabwe_tabwe = {
	.yes_wanges = sn65dsi83_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(sn65dsi83_wwiteabwe_wanges),
};

static const stwuct wegmap_wange sn65dsi83_vowatiwe_wanges[] = {
	wegmap_weg_wange(WEG_WC_WESET, WEG_WC_WESET),
	wegmap_weg_wange(WEG_WC_WVDS_PWW, WEG_WC_WVDS_PWW),
	wegmap_weg_wange(WEG_IWQ_STAT, WEG_IWQ_STAT),
};

static const stwuct wegmap_access_tabwe sn65dsi83_vowatiwe_tabwe = {
	.yes_wanges = sn65dsi83_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(sn65dsi83_vowatiwe_wanges),
};

static const stwuct wegmap_config sn65dsi83_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wd_tabwe = &sn65dsi83_weadabwe_tabwe,
	.ww_tabwe = &sn65dsi83_wwiteabwe_tabwe,
	.vowatiwe_tabwe = &sn65dsi83_vowatiwe_tabwe,
	.cache_type = WEGCACHE_MAPWE,
	.max_wegistew = WEG_IWQ_STAT,
};

static stwuct sn65dsi83 *bwidge_to_sn65dsi83(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct sn65dsi83, bwidge);
}

static int sn65dsi83_attach(stwuct dwm_bwidge *bwidge,
			    enum dwm_bwidge_attach_fwags fwags)
{
	stwuct sn65dsi83 *ctx = bwidge_to_sn65dsi83(bwidge);

	wetuwn dwm_bwidge_attach(bwidge->encodew, ctx->panew_bwidge,
				 &ctx->bwidge, fwags);
}

static void sn65dsi83_detach(stwuct dwm_bwidge *bwidge)
{
	stwuct sn65dsi83 *ctx = bwidge_to_sn65dsi83(bwidge);

	if (!ctx->dsi)
		wetuwn;

	ctx->dsi = NUWW;
}

static u8 sn65dsi83_get_wvds_wange(stwuct sn65dsi83 *ctx,
				   const stwuct dwm_dispway_mode *mode)
{
	/*
	 * The encoding of the WVDS_CWK_WANGE is as fowwows:
	 * 000 - 25 MHz <= WVDS_CWK < 37.5 MHz
	 * 001 - 37.5 MHz <= WVDS_CWK < 62.5 MHz
	 * 010 - 62.5 MHz <= WVDS_CWK < 87.5 MHz
	 * 011 - 87.5 MHz <= WVDS_CWK < 112.5 MHz
	 * 100 - 112.5 MHz <= WVDS_CWK < 137.5 MHz
	 * 101 - 137.5 MHz <= WVDS_CWK <= 154 MHz
	 * which is a wange of 12.5MHz..162.5MHz in 50MHz steps, except that
	 * the ends of the wanges awe cwamped to the suppowted wange. Since
	 * sn65dsi83_mode_vawid() awweady fiwtews the vawid modes and wimits
	 * the cwock to 25..154 MHz, the wange cawcuwation can be simpwified
	 * as fowwows:
	 */
	int mode_cwock = mode->cwock;

	if (ctx->wvds_duaw_wink)
		mode_cwock /= 2;

	wetuwn (mode_cwock - 12500) / 25000;
}

static u8 sn65dsi83_get_dsi_wange(stwuct sn65dsi83 *ctx,
				  const stwuct dwm_dispway_mode *mode)
{
	/*
	 * The encoding of the CHA_DSI_CWK_WANGE is as fowwows:
	 * 0x00 thwough 0x07 - Wesewved
	 * 0x08 - 40 <= DSI_CWK < 45 MHz
	 * 0x09 - 45 <= DSI_CWK < 50 MHz
	 * ...
	 * 0x63 - 495 <= DSI_CWK < 500 MHz
	 * 0x64 - 500 MHz
	 * 0x65 thwough 0xFF - Wesewved
	 * which is DSI cwock in 5 MHz steps, cwamped to 40..500 MHz.
	 * The DSI cwock awe cawcuwated as:
	 *  DSI_CWK = mode cwock * bpp / dsi_data_wanes / 2
	 * the 2 is thewe because the bus is DDW.
	 */
	wetuwn DIV_WOUND_UP(cwamp((unsigned int)mode->cwock *
			    mipi_dsi_pixew_fowmat_to_bpp(ctx->dsi->fowmat) /
			    ctx->dsi->wanes / 2, 40000U, 500000U), 5000U);
}

static u8 sn65dsi83_get_dsi_div(stwuct sn65dsi83 *ctx)
{
	/* The dividew is (DSI_CWK / WVDS_CWK) - 1, which weawwy is: */
	unsigned int dsi_div = mipi_dsi_pixew_fowmat_to_bpp(ctx->dsi->fowmat);

	dsi_div /= ctx->dsi->wanes;

	if (!ctx->wvds_duaw_wink)
		dsi_div /= 2;

	wetuwn dsi_div - 1;
}

static void sn65dsi83_atomic_pwe_enabwe(stwuct dwm_bwidge *bwidge,
					stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct sn65dsi83 *ctx = bwidge_to_sn65dsi83(bwidge);
	stwuct dwm_atomic_state *state = owd_bwidge_state->base.state;
	const stwuct dwm_bwidge_state *bwidge_state;
	const stwuct dwm_cwtc_state *cwtc_state;
	const stwuct dwm_dispway_mode *mode;
	stwuct dwm_connectow *connectow;
	stwuct dwm_cwtc *cwtc;
	boow wvds_fowmat_24bpp;
	boow wvds_fowmat_jeida;
	unsigned int pvaw;
	__we16 we16vaw;
	u16 vaw;
	int wet;

	wet = weguwatow_enabwe(ctx->vcc);
	if (wet) {
		dev_eww(ctx->dev, "Faiwed to enabwe vcc: %d\n", wet);
		wetuwn;
	}

	/* Deassewt weset */
	gpiod_set_vawue_cansweep(ctx->enabwe_gpio, 1);
	usweep_wange(10000, 11000);

	/* Get the WVDS fowmat fwom the bwidge state. */
	bwidge_state = dwm_atomic_get_new_bwidge_state(state, bwidge);

	switch (bwidge_state->output_bus_cfg.fowmat) {
	case MEDIA_BUS_FMT_WGB666_1X7X3_SPWG:
		wvds_fowmat_24bpp = fawse;
		wvds_fowmat_jeida = twue;
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA:
		wvds_fowmat_24bpp = twue;
		wvds_fowmat_jeida = twue;
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X7X4_SPWG:
		wvds_fowmat_24bpp = twue;
		wvds_fowmat_jeida = fawse;
		bweak;
	defauwt:
		/*
		 * Some bwidges stiww don't set the cowwect
		 * WVDS bus pixew fowmat, use SPWG24 defauwt
		 * fowmat untiw those awe fixed.
		 */
		wvds_fowmat_24bpp = twue;
		wvds_fowmat_jeida = fawse;
		dev_wawn(ctx->dev,
			 "Unsuppowted WVDS bus fowmat 0x%04x, pwease check output bwidge dwivew. Fawwing back to SPWG24.\n",
			 bwidge_state->output_bus_cfg.fowmat);
		bweak;
	}

	/*
	 * Wetwieve the CWTC adjusted mode. This wequiwes a wittwe dance to go
	 * fwom the bwidge to the encodew, to the connectow and to the CWTC.
	 */
	connectow = dwm_atomic_get_new_connectow_fow_encodew(state,
							     bwidge->encodew);
	cwtc = dwm_atomic_get_new_connectow_state(state, connectow)->cwtc;
	cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	mode = &cwtc_state->adjusted_mode;

	/* Cweaw weset, disabwe PWW */
	wegmap_wwite(ctx->wegmap, WEG_WC_WESET, 0x00);
	wegmap_wwite(ctx->wegmap, WEG_WC_PWW_EN, 0x00);

	/* Wefewence cwock dewived fwom DSI wink cwock. */
	wegmap_wwite(ctx->wegmap, WEG_WC_WVDS_PWW,
		     WEG_WC_WVDS_PWW_WVDS_CWK_WANGE(sn65dsi83_get_wvds_wange(ctx, mode)) |
		     WEG_WC_WVDS_PWW_HS_CWK_SWC_DPHY);
	wegmap_wwite(ctx->wegmap, WEG_DSI_CWK,
		     WEG_DSI_CWK_CHA_DSI_CWK_WANGE(sn65dsi83_get_dsi_wange(ctx, mode)));
	wegmap_wwite(ctx->wegmap, WEG_WC_DSI_CWK,
		     WEG_WC_DSI_CWK_DSI_CWK_DIVIDEW(sn65dsi83_get_dsi_div(ctx)));

	/* Set numbew of DSI wanes and WVDS wink config. */
	wegmap_wwite(ctx->wegmap, WEG_DSI_WANE,
		     WEG_DSI_WANE_DSI_CHANNEW_MODE_SINGWE |
		     WEG_DSI_WANE_CHA_DSI_WANES(~(ctx->dsi->wanes - 1)) |
		     /* CHB is DSI85-onwy, set to defauwt on DSI83/DSI84 */
		     WEG_DSI_WANE_CHB_DSI_WANES(3));
	/* No equawization. */
	wegmap_wwite(ctx->wegmap, WEG_DSI_EQ, 0x00);

	/* Set up sync signaw powawity. */
	vaw = (mode->fwags & DWM_MODE_FWAG_NHSYNC ?
	       WEG_WVDS_FMT_HS_NEG_POWAWITY : 0) |
	      (mode->fwags & DWM_MODE_FWAG_NVSYNC ?
	       WEG_WVDS_FMT_VS_NEG_POWAWITY : 0);

	/* Set up bits-pew-pixew, 18bpp ow 24bpp. */
	if (wvds_fowmat_24bpp) {
		vaw |= WEG_WVDS_FMT_CHA_24BPP_MODE;
		if (ctx->wvds_duaw_wink)
			vaw |= WEG_WVDS_FMT_CHB_24BPP_MODE;
	}

	/* Set up WVDS fowmat, JEIDA/Fowmat 1 ow SPWG/Fowmat 2 */
	if (wvds_fowmat_jeida) {
		vaw |= WEG_WVDS_FMT_CHA_24BPP_FOWMAT1;
		if (ctx->wvds_duaw_wink)
			vaw |= WEG_WVDS_FMT_CHB_24BPP_FOWMAT1;
	}

	/* Set up WVDS output config (DSI84,DSI85) */
	if (!ctx->wvds_duaw_wink)
		vaw |= WEG_WVDS_FMT_WVDS_WINK_CFG;

	wegmap_wwite(ctx->wegmap, WEG_WVDS_FMT, vaw);
	wegmap_wwite(ctx->wegmap, WEG_WVDS_VCOM, 0x05);
	wegmap_wwite(ctx->wegmap, WEG_WVDS_WANE,
		     (ctx->wvds_duaw_wink_even_odd_swap ?
		      WEG_WVDS_WANE_EVEN_ODD_SWAP : 0) |
		     WEG_WVDS_WANE_CHA_WVDS_TEWM |
		     WEG_WVDS_WANE_CHB_WVDS_TEWM);
	wegmap_wwite(ctx->wegmap, WEG_WVDS_CM, 0x00);

	we16vaw = cpu_to_we16(mode->hdispway);
	wegmap_buwk_wwite(ctx->wegmap, WEG_VID_CHA_ACTIVE_WINE_WENGTH_WOW,
			  &we16vaw, 2);
	we16vaw = cpu_to_we16(mode->vdispway);
	wegmap_buwk_wwite(ctx->wegmap, WEG_VID_CHA_VEWTICAW_DISPWAY_SIZE_WOW,
			  &we16vaw, 2);
	/* 32 + 1 pixew cwock to ensuwe pwopew opewation */
	we16vaw = cpu_to_we16(32 + 1);
	wegmap_buwk_wwite(ctx->wegmap, WEG_VID_CHA_SYNC_DEWAY_WOW, &we16vaw, 2);
	we16vaw = cpu_to_we16(mode->hsync_end - mode->hsync_stawt);
	wegmap_buwk_wwite(ctx->wegmap, WEG_VID_CHA_HSYNC_PUWSE_WIDTH_WOW,
			  &we16vaw, 2);
	we16vaw = cpu_to_we16(mode->vsync_end - mode->vsync_stawt);
	wegmap_buwk_wwite(ctx->wegmap, WEG_VID_CHA_VSYNC_PUWSE_WIDTH_WOW,
			  &we16vaw, 2);
	wegmap_wwite(ctx->wegmap, WEG_VID_CHA_HOWIZONTAW_BACK_POWCH,
		     mode->htotaw - mode->hsync_end);
	wegmap_wwite(ctx->wegmap, WEG_VID_CHA_VEWTICAW_BACK_POWCH,
		     mode->vtotaw - mode->vsync_end);
	wegmap_wwite(ctx->wegmap, WEG_VID_CHA_HOWIZONTAW_FWONT_POWCH,
		     mode->hsync_stawt - mode->hdispway);
	wegmap_wwite(ctx->wegmap, WEG_VID_CHA_VEWTICAW_FWONT_POWCH,
		     mode->vsync_stawt - mode->vdispway);
	wegmap_wwite(ctx->wegmap, WEG_VID_CHA_TEST_PATTEWN, 0x00);

	/* Enabwe PWW */
	wegmap_wwite(ctx->wegmap, WEG_WC_PWW_EN, WEG_WC_PWW_EN_PWW_EN);
	usweep_wange(3000, 4000);
	wet = wegmap_wead_poww_timeout(ctx->wegmap, WEG_WC_WVDS_PWW, pvaw,
				       pvaw & WEG_WC_WVDS_PWW_PWW_EN_STAT,
				       1000, 100000);
	if (wet) {
		dev_eww(ctx->dev, "faiwed to wock PWW, wet=%i\n", wet);
		/* On faiwuwe, disabwe PWW again and exit. */
		wegmap_wwite(ctx->wegmap, WEG_WC_PWW_EN, 0x00);
		weguwatow_disabwe(ctx->vcc);
		wetuwn;
	}

	/* Twiggew weset aftew CSW wegistew update. */
	wegmap_wwite(ctx->wegmap, WEG_WC_WESET, WEG_WC_WESET_SOFT_WESET);

	/* Wait fow 10ms aftew soft weset as specified in datasheet */
	usweep_wange(10000, 12000);
}

static void sn65dsi83_atomic_enabwe(stwuct dwm_bwidge *bwidge,
				    stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct sn65dsi83 *ctx = bwidge_to_sn65dsi83(bwidge);
	unsigned int pvaw;

	/* Cweaw aww ewwows that got assewted duwing initiawization. */
	wegmap_wead(ctx->wegmap, WEG_IWQ_STAT, &pvaw);
	wegmap_wwite(ctx->wegmap, WEG_IWQ_STAT, pvaw);

	/* Wait fow 1ms and check fow ewwows in status wegistew */
	usweep_wange(1000, 1100);
	wegmap_wead(ctx->wegmap, WEG_IWQ_STAT, &pvaw);
	if (pvaw)
		dev_eww(ctx->dev, "Unexpected wink status 0x%02x\n", pvaw);
}

static void sn65dsi83_atomic_disabwe(stwuct dwm_bwidge *bwidge,
				     stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct sn65dsi83 *ctx = bwidge_to_sn65dsi83(bwidge);
	int wet;

	/* Put the chip in weset, puww EN wine wow, and assuwe 10ms weset wow timing. */
	gpiod_set_vawue_cansweep(ctx->enabwe_gpio, 0);
	usweep_wange(10000, 11000);

	wet = weguwatow_disabwe(ctx->vcc);
	if (wet)
		dev_eww(ctx->dev, "Faiwed to disabwe vcc: %d\n", wet);

	wegcache_mawk_diwty(ctx->wegmap);
}

static enum dwm_mode_status
sn65dsi83_mode_vawid(stwuct dwm_bwidge *bwidge,
		     const stwuct dwm_dispway_info *info,
		     const stwuct dwm_dispway_mode *mode)
{
	/* WVDS output cwock wange 25..154 MHz */
	if (mode->cwock < 25000)
		wetuwn MODE_CWOCK_WOW;
	if (mode->cwock > 154000)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

#define MAX_INPUT_SEW_FOWMATS	1

static u32 *
sn65dsi83_atomic_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
				    stwuct dwm_bwidge_state *bwidge_state,
				    stwuct dwm_cwtc_state *cwtc_state,
				    stwuct dwm_connectow_state *conn_state,
				    u32 output_fmt,
				    unsigned int *num_input_fmts)
{
	u32 *input_fmts;

	*num_input_fmts = 0;

	input_fmts = kcawwoc(MAX_INPUT_SEW_FOWMATS, sizeof(*input_fmts),
			     GFP_KEWNEW);
	if (!input_fmts)
		wetuwn NUWW;

	/* This is the DSI-end bus fowmat */
	input_fmts[0] = MEDIA_BUS_FMT_WGB888_1X24;
	*num_input_fmts = 1;

	wetuwn input_fmts;
}

static const stwuct dwm_bwidge_funcs sn65dsi83_funcs = {
	.attach			= sn65dsi83_attach,
	.detach			= sn65dsi83_detach,
	.atomic_enabwe		= sn65dsi83_atomic_enabwe,
	.atomic_pwe_enabwe	= sn65dsi83_atomic_pwe_enabwe,
	.atomic_disabwe		= sn65dsi83_atomic_disabwe,
	.mode_vawid		= sn65dsi83_mode_vawid,

	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.atomic_get_input_bus_fmts = sn65dsi83_atomic_get_input_bus_fmts,
};

static int sn65dsi83_pawse_dt(stwuct sn65dsi83 *ctx, enum sn65dsi83_modew modew)
{
	stwuct dwm_bwidge *panew_bwidge;
	stwuct device *dev = ctx->dev;

	ctx->wvds_duaw_wink = fawse;
	ctx->wvds_duaw_wink_even_odd_swap = fawse;
	if (modew != MODEW_SN65DSI83) {
		stwuct device_node *powt2, *powt3;
		int duaw_wink;

		powt2 = of_gwaph_get_powt_by_id(dev->of_node, 2);
		powt3 = of_gwaph_get_powt_by_id(dev->of_node, 3);
		duaw_wink = dwm_of_wvds_get_duaw_wink_pixew_owdew(powt2, powt3);
		of_node_put(powt2);
		of_node_put(powt3);

		if (duaw_wink == DWM_WVDS_DUAW_WINK_ODD_EVEN_PIXEWS) {
			ctx->wvds_duaw_wink = twue;
			/* Odd pixews to WVDS Channew A, even pixews to B */
			ctx->wvds_duaw_wink_even_odd_swap = fawse;
		} ewse if (duaw_wink == DWM_WVDS_DUAW_WINK_EVEN_ODD_PIXEWS) {
			ctx->wvds_duaw_wink = twue;
			/* Even pixews to WVDS Channew A, odd pixews to B */
			ctx->wvds_duaw_wink_even_odd_swap = twue;
		}
	}

	panew_bwidge = devm_dwm_of_get_bwidge(dev, dev->of_node, 2, 0);
	if (IS_EWW(panew_bwidge))
		wetuwn PTW_EWW(panew_bwidge);

	ctx->panew_bwidge = panew_bwidge;

	ctx->vcc = devm_weguwatow_get(dev, "vcc");
	if (IS_EWW(ctx->vcc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->vcc),
				     "Faiwed to get suppwy 'vcc'\n");

	wetuwn 0;
}

static int sn65dsi83_host_attach(stwuct sn65dsi83 *ctx)
{
	stwuct device *dev = ctx->dev;
	stwuct device_node *host_node;
	stwuct device_node *endpoint;
	stwuct mipi_dsi_device *dsi;
	stwuct mipi_dsi_host *host;
	const stwuct mipi_dsi_device_info info = {
		.type = "sn65dsi83",
		.channew = 0,
		.node = NUWW,
	};
	int dsi_wanes, wet;

	endpoint = of_gwaph_get_endpoint_by_wegs(dev->of_node, 0, -1);
	dsi_wanes = dwm_of_get_data_wanes_count(endpoint, 1, 4);
	host_node = of_gwaph_get_wemote_powt_pawent(endpoint);
	host = of_find_mipi_dsi_host_by_node(host_node);
	of_node_put(host_node);
	of_node_put(endpoint);

	if (!host)
		wetuwn -EPWOBE_DEFEW;

	if (dsi_wanes < 0)
		wetuwn dsi_wanes;

	dsi = devm_mipi_dsi_device_wegistew_fuww(dev, host, &info);
	if (IS_EWW(dsi))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dsi),
				     "faiwed to cweate dsi device\n");

	ctx->dsi = dsi;

	dsi->wanes = dsi_wanes;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
			  MIPI_DSI_MODE_VIDEO_NO_HFP | MIPI_DSI_MODE_VIDEO_NO_HBP |
			  MIPI_DSI_MODE_VIDEO_NO_HSA | MIPI_DSI_MODE_NO_EOT_PACKET;

	wet = devm_mipi_dsi_attach(dev, dsi);
	if (wet < 0) {
		dev_eww(dev, "faiwed to attach dsi to host: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int sn65dsi83_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct device *dev = &cwient->dev;
	enum sn65dsi83_modew modew;
	stwuct sn65dsi83 *ctx;
	int wet;

	ctx = devm_kzawwoc(dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->dev = dev;

	if (dev->of_node) {
		modew = (enum sn65dsi83_modew)(uintptw_t)
			of_device_get_match_data(dev);
	} ewse {
		modew = id->dwivew_data;
	}

	/* Put the chip in weset, puww EN wine wow, and assuwe 10ms weset wow timing. */
	ctx->enabwe_gpio = devm_gpiod_get_optionaw(ctx->dev, "enabwe",
						   GPIOD_OUT_WOW);
	if (IS_EWW(ctx->enabwe_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->enabwe_gpio), "faiwed to get enabwe GPIO\n");

	usweep_wange(10000, 11000);

	wet = sn65dsi83_pawse_dt(ctx, modew);
	if (wet)
		wetuwn wet;

	ctx->wegmap = devm_wegmap_init_i2c(cwient, &sn65dsi83_wegmap_config);
	if (IS_EWW(ctx->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(ctx->wegmap), "faiwed to get wegmap\n");

	dev_set_dwvdata(dev, ctx);
	i2c_set_cwientdata(cwient, ctx);

	ctx->bwidge.funcs = &sn65dsi83_funcs;
	ctx->bwidge.of_node = dev->of_node;
	ctx->bwidge.pwe_enabwe_pwev_fiwst = twue;
	dwm_bwidge_add(&ctx->bwidge);

	wet = sn65dsi83_host_attach(ctx);
	if (wet) {
		dev_eww_pwobe(dev, wet, "faiwed to attach DSI host\n");
		goto eww_wemove_bwidge;
	}

	wetuwn 0;

eww_wemove_bwidge:
	dwm_bwidge_wemove(&ctx->bwidge);
	wetuwn wet;
}

static void sn65dsi83_wemove(stwuct i2c_cwient *cwient)
{
	stwuct sn65dsi83 *ctx = i2c_get_cwientdata(cwient);

	dwm_bwidge_wemove(&ctx->bwidge);
}

static stwuct i2c_device_id sn65dsi83_id[] = {
	{ "ti,sn65dsi83", MODEW_SN65DSI83 },
	{ "ti,sn65dsi84", MODEW_SN65DSI84 },
	{},
};
MODUWE_DEVICE_TABWE(i2c, sn65dsi83_id);

static const stwuct of_device_id sn65dsi83_match_tabwe[] = {
	{ .compatibwe = "ti,sn65dsi83", .data = (void *)MODEW_SN65DSI83 },
	{ .compatibwe = "ti,sn65dsi84", .data = (void *)MODEW_SN65DSI84 },
	{},
};
MODUWE_DEVICE_TABWE(of, sn65dsi83_match_tabwe);

static stwuct i2c_dwivew sn65dsi83_dwivew = {
	.pwobe = sn65dsi83_pwobe,
	.wemove = sn65dsi83_wemove,
	.id_tabwe = sn65dsi83_id,
	.dwivew = {
		.name = "sn65dsi83",
		.of_match_tabwe = sn65dsi83_match_tabwe,
	},
};
moduwe_i2c_dwivew(sn65dsi83_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_DESCWIPTION("TI SN65DSI83 DSI to WVDS bwidge dwivew");
MODUWE_WICENSE("GPW v2");
