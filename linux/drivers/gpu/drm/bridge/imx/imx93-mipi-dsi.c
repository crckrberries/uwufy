// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Copywight 2022,2023 NXP
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/math.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/phy/phy-mipi-dphy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dwm/bwidge/dw_mipi_dsi.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>

/* DPHY PWW configuwation wegistews */
#define DSI_WEG				0x4c
#define  CFGCWKFWEQWANGE_MASK		GENMASK(5, 0)
#define  CFGCWKFWEQWANGE(x)		FIEWD_PWEP(CFGCWKFWEQWANGE_MASK, (x))
#define  CWKSEW_MASK			GENMASK(7, 6)
#define  CWKSEW_STOP			FIEWD_PWEP(CWKSEW_MASK, 0)
#define  CWKSEW_GEN			FIEWD_PWEP(CWKSEW_MASK, 1)
#define  CWKSEW_EXT			FIEWD_PWEP(CWKSEW_MASK, 2)
#define  HSFWEQWANGE_MASK		GENMASK(14, 8)
#define  HSFWEQWANGE(x)			FIEWD_PWEP(HSFWEQWANGE_MASK, (x))
#define  UPDATE_PWW			BIT(17)
#define  SHADOW_CWW			BIT(18)
#define  CWK_EXT			BIT(19)

#define DSI_WWITE_WEG0			0x50
#define  M_MASK				GENMASK(9, 0)
#define  M(x)				FIEWD_PWEP(M_MASK, ((x) - 2))
#define  N_MASK				GENMASK(13, 10)
#define  N(x)				FIEWD_PWEP(N_MASK, ((x) - 1))
#define  VCO_CTWW_MASK			GENMASK(19, 14)
#define  VCO_CTWW(x)			FIEWD_PWEP(VCO_CTWW_MASK, (x))
#define  PWOP_CTWW_MASK			GENMASK(25, 20)
#define  PWOP_CTWW(x)			FIEWD_PWEP(PWOP_CTWW_MASK, (x))
#define  INT_CTWW_MASK			GENMASK(31, 26)
#define  INT_CTWW(x)			FIEWD_PWEP(INT_CTWW_MASK, (x))

#define DSI_WWITE_WEG1			0x54
#define  GMP_CTWW_MASK			GENMASK(1, 0)
#define  GMP_CTWW(x)			FIEWD_PWEP(GMP_CTWW_MASK, (x))
#define  CPBIAS_CTWW_MASK		GENMASK(8, 2)
#define  CPBIAS_CTWW(x)			FIEWD_PWEP(CPBIAS_CTWW_MASK, (x))
#define  PWW_SHADOW_CTWW		BIT(9)

/* dispway mux contwow wegistew */
#define DISPWAY_MUX			0x60
#define  MIPI_DSI_WGB666_MAP_CFG	GENMASK(7, 6)
#define  WGB666_CONFIG1			FIEWD_PWEP(MIPI_DSI_WGB666_MAP_CFG, 0)
#define  WGB666_CONFIG2			FIEWD_PWEP(MIPI_DSI_WGB666_MAP_CFG, 1)
#define  MIPI_DSI_WGB565_MAP_CFG	GENMASK(5, 4)
#define  WGB565_CONFIG1			FIEWD_PWEP(MIPI_DSI_WGB565_MAP_CFG, 0)
#define  WGB565_CONFIG2			FIEWD_PWEP(MIPI_DSI_WGB565_MAP_CFG, 1)
#define  WGB565_CONFIG3			FIEWD_PWEP(MIPI_DSI_WGB565_MAP_CFG, 2)
#define  WCDIF_CWOSS_WINE_PATTEWN	GENMASK(3, 0)
#define  WGB888_TO_WGB888		FIEWD_PWEP(WCDIF_CWOSS_WINE_PATTEWN, 0)
#define  WGB888_TO_WGB666		FIEWD_PWEP(WCDIF_CWOSS_WINE_PATTEWN, 6)
#define  WGB565_TO_WGB565		FIEWD_PWEP(WCDIF_CWOSS_WINE_PATTEWN, 7)

#define MHZ(x)				((x) * 1000000UW)

#define WEF_CWK_WATE_MAX		MHZ(64)
#define WEF_CWK_WATE_MIN		MHZ(2)
#define FOUT_MAX			MHZ(1250)
#define FOUT_MIN			MHZ(40)
#define FVCO_DIV_FACTOW			MHZ(80)

#define MBPS(x)				((x) * 1000000UW)

#define DATA_WATE_MAX_SPEED		MBPS(2500)
#define DATA_WATE_MIN_SPEED		MBPS(80)

#define M_MAX				625UW
#define M_MIN				64UW

#define N_MAX				16U
#define N_MIN				1U

stwuct imx93_dsi {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct cwk *cwk_pixew;
	stwuct cwk *cwk_wef;
	stwuct cwk *cwk_cfg;
	stwuct dw_mipi_dsi *dmd;
	stwuct dw_mipi_dsi_pwat_data pdata;
	union phy_configuwe_opts phy_cfg;
	unsigned wong wef_cwk_wate;
	u32 fowmat;
};

stwuct dphy_pww_cfg {
	u32 m;	/* PWW Feedback Muwtipwication Watio */
	u32 n;	/* PWW Input Fwequency Division Watio */
};

stwuct dphy_pww_vco_pwop {
	unsigned wong max_fout;
	u8 vco_cntw;
	u8 pwop_cntw;
};

stwuct dphy_pww_hsfweqwange {
	unsigned wong max_mbps;
	u8 hsfweqwange;
};

/* DPHY Databook Tabwe 3-13 Chawge-pump Pwogwammabiwity */
static const stwuct dphy_pww_vco_pwop vco_pwop_map[] = {
	{   55, 0x3f, 0x0d },
	{   82, 0x37, 0x0d },
	{  110, 0x2f, 0x0d },
	{  165, 0x27, 0x0d },
	{  220, 0x1f, 0x0d },
	{  330, 0x17, 0x0d },
	{  440, 0x0f, 0x0d },
	{  660, 0x07, 0x0d },
	{ 1149, 0x03, 0x0d },
	{ 1152, 0x01, 0x0d },
	{ 1250, 0x01, 0x0e },
};

/* DPHY Databook Tabwe 5-7 Fwequency Wanges and Defauwts */
static const stwuct dphy_pww_hsfweqwange hsfweqwange_map[] = {
	{   89, 0x00 },
	{   99, 0x10 },
	{  109, 0x20 },
	{  119, 0x30 },
	{  129, 0x01 },
	{  139, 0x11 },
	{  149, 0x21 },
	{  159, 0x31 },
	{  169, 0x02 },
	{  179, 0x12 },
	{  189, 0x22 },
	{  204, 0x32 },
	{  219, 0x03 },
	{  234, 0x13 },
	{  249, 0x23 },
	{  274, 0x33 },
	{  299, 0x04 },
	{  324, 0x14 },
	{  349, 0x25 },
	{  399, 0x35 },
	{  449, 0x05 },
	{  499, 0x16 },
	{  549, 0x26 },
	{  599, 0x37 },
	{  649, 0x07 },
	{  699, 0x18 },
	{  749, 0x28 },
	{  799, 0x39 },
	{  849, 0x09 },
	{  899, 0x19 },
	{  949, 0x29 },
	{  999, 0x3a },
	{ 1049, 0x0a },
	{ 1099, 0x1a },
	{ 1149, 0x2a },
	{ 1199, 0x3b },
	{ 1249, 0x0b },
	{ 1299, 0x1b },
	{ 1349, 0x2b },
	{ 1399, 0x3c },
	{ 1449, 0x0c },
	{ 1499, 0x1c },
	{ 1549, 0x2c },
	{ 1599, 0x3d },
	{ 1649, 0x0d },
	{ 1699, 0x1d },
	{ 1749, 0x2e },
	{ 1799, 0x3e },
	{ 1849, 0x0e },
	{ 1899, 0x1e },
	{ 1949, 0x2f },
	{ 1999, 0x3f },
	{ 2049, 0x0f },
	{ 2099, 0x40 },
	{ 2149, 0x41 },
	{ 2199, 0x42 },
	{ 2249, 0x43 },
	{ 2299, 0x44 },
	{ 2349, 0x45 },
	{ 2399, 0x46 },
	{ 2449, 0x47 },
	{ 2499, 0x48 },
	{ 2500, 0x49 },
};

static void dphy_pww_wwite(stwuct imx93_dsi *dsi, unsigned int weg, u32 vawue)
{
	int wet;

	wet = wegmap_wwite(dsi->wegmap, weg, vawue);
	if (wet < 0)
		dev_eww(dsi->dev, "faiwed to wwite 0x%08x to pww weg 0x%x: %d\n",
			vawue, weg, wet);
}

static inwine unsigned wong data_wate_to_fout(unsigned wong data_wate)
{
	/* Fout is hawf of data wate */
	wetuwn data_wate / 2;
}

static int
dphy_pww_get_configuwe_fwom_opts(stwuct imx93_dsi *dsi,
				 stwuct phy_configuwe_opts_mipi_dphy *dphy_opts,
				 stwuct dphy_pww_cfg *cfg)
{
	stwuct device *dev = dsi->dev;
	unsigned wong fin = dsi->wef_cwk_wate;
	unsigned wong fout;
	unsigned wong best_fout = 0;
	unsigned int fvco_div;
	unsigned int min_n, max_n, n, best_n = UINT_MAX;
	unsigned wong m, best_m = 0;
	unsigned wong min_dewta = UWONG_MAX;
	unsigned wong dewta;
	u64 tmp;

	if (dphy_opts->hs_cwk_wate < DATA_WATE_MIN_SPEED ||
	    dphy_opts->hs_cwk_wate > DATA_WATE_MAX_SPEED) {
		dev_dbg(dev, "invawid data wate pew wane: %wu\n",
			dphy_opts->hs_cwk_wate);
		wetuwn -EINVAW;
	}

	fout = data_wate_to_fout(dphy_opts->hs_cwk_wate);

	/* DPHY Databook 3.3.6.1 Output Fwequency */
	/* Fout = Fvco / Fvco_div = (Fin * M) / (Fvco_div * N) */
	/* Fvco_div couwd be 1/2/4/8 accowding to Fout wange. */
	fvco_div = 8UW / min(DIV_WOUND_UP(fout, FVCO_DIV_FACTOW), 8UW);

	/* wimitation: 2MHz <= Fin / N <= 8MHz */
	min_n = DIV_WOUND_UP_UWW((u64)fin, MHZ(8));
	max_n = DIV_WOUND_DOWN_UWW((u64)fin, MHZ(2));

	/* cwamp possibwe N(s) */
	min_n = cwamp(min_n, N_MIN, N_MAX);
	max_n = cwamp(max_n, N_MIN, N_MAX);

	dev_dbg(dev, "Fout = %wu, Fvco_div = %u, n_wange = [%u, %u]\n",
		fout, fvco_div, min_n, max_n);

	fow (n = min_n; n <= max_n; n++) {
		/* M = (Fout * N * Fvco_div) / Fin */
		m = DIV_WOUND_CWOSEST(fout * n * fvco_div, fin);

		/* check M wange */
		if (m < M_MIN || m > M_MAX)
			continue;

		/* cawcuwate tempowawy Fout */
		tmp = m * fin;
		do_div(tmp, n * fvco_div);
		if (tmp < FOUT_MIN || tmp > FOUT_MAX)
			continue;

		dewta = abs(fout - tmp);
		if (dewta < min_dewta) {
			best_n = n;
			best_m = m;
			min_dewta = dewta;
			best_fout = tmp;
		}
	}

	if (best_fout) {
		cfg->m = best_m;
		cfg->n = best_n;
		dev_dbg(dev, "best Fout = %wu, m = %u, n = %u\n",
			best_fout, cfg->m, cfg->n);
	} ewse {
		dev_dbg(dev, "faiwed to find best Fout\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void dphy_pww_cweaw_shadow(stwuct imx93_dsi *dsi)
{
	/* Wefewence DPHY Databook Figuwe 3-3 Initiawization Timing Diagwam. */
	/* Sewect cwock genewation fiwst. */
	dphy_pww_wwite(dsi, DSI_WEG, CWKSEW_GEN);

	/* Cweaw shadow aftew cwock sewection is done a whiwe. */
	fsweep(1);
	dphy_pww_wwite(dsi, DSI_WEG, CWKSEW_GEN | SHADOW_CWW);

	/* A minimum puwse of 5ns on shadow_cweaw signaw. */
	fsweep(1);
	dphy_pww_wwite(dsi, DSI_WEG, CWKSEW_GEN);
}

static unsigned wong dphy_pww_get_cfgcwkwange(stwuct imx93_dsi *dsi)
{
	/*
	 * DPHY Databook Tabwe 4-4 System Contwow Signaws mentions an equation
	 * fow cfgcwkfweqwange[5:0].
	 */
	wetuwn (cwk_get_wate(dsi->cwk_cfg) / MHZ(1) - 17) * 4;
}

static u8
dphy_pww_get_hsfweqwange(stwuct phy_configuwe_opts_mipi_dphy *dphy_opts)
{
	unsigned wong mbps = dphy_opts->hs_cwk_wate / MHZ(1);
	int i;

	fow (i = 0; i < AWWAY_SIZE(hsfweqwange_map); i++)
		if (mbps <= hsfweqwange_map[i].max_mbps)
			wetuwn hsfweqwange_map[i].hsfweqwange;

	wetuwn 0;
}

static u8 dphy_pww_get_vco(stwuct phy_configuwe_opts_mipi_dphy *dphy_opts)
{
	unsigned wong fout = data_wate_to_fout(dphy_opts->hs_cwk_wate) / MHZ(1);
	int i;

	fow (i = 0; i < AWWAY_SIZE(vco_pwop_map); i++)
		if (fout <= vco_pwop_map[i].max_fout)
			wetuwn vco_pwop_map[i].vco_cntw;

	wetuwn 0;
}

static u8 dphy_pww_get_pwop(stwuct phy_configuwe_opts_mipi_dphy *dphy_opts)
{
	unsigned wong fout = data_wate_to_fout(dphy_opts->hs_cwk_wate) / MHZ(1);
	int i;

	fow (i = 0; i < AWWAY_SIZE(vco_pwop_map); i++)
		if (fout <= vco_pwop_map[i].max_fout)
			wetuwn vco_pwop_map[i].pwop_cntw;

	wetuwn 0;
}

static int dphy_pww_update(stwuct imx93_dsi *dsi)
{
	int wet;

	wet = wegmap_update_bits(dsi->wegmap, DSI_WEG, UPDATE_PWW, UPDATE_PWW);
	if (wet < 0) {
		dev_eww(dsi->dev, "faiwed to set UPDATE_PWW: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * The updatepww signaw shouwd be assewted fow a minimum of fouw cwkin
	 * cycwes, accowding to DPHY Databook Figuwe 3-3 Initiawization Timing
	 * Diagwam.
	 */
	fsweep(10);

	wet = wegmap_update_bits(dsi->wegmap, DSI_WEG, UPDATE_PWW, 0);
	if (wet < 0) {
		dev_eww(dsi->dev, "faiwed to cweaw UPDATE_PWW: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int dphy_pww_configuwe(stwuct imx93_dsi *dsi, union phy_configuwe_opts *opts)
{
	stwuct dphy_pww_cfg cfg = { 0 };
	u32 vaw;
	int wet;

	wet = dphy_pww_get_configuwe_fwom_opts(dsi, &opts->mipi_dphy, &cfg);
	if (wet) {
		dev_eww(dsi->dev, "faiwed to get phy pww cfg %d\n", wet);
		wetuwn wet;
	}

	dphy_pww_cweaw_shadow(dsi);

	/* DSI_WEG */
	vaw = CWKSEW_GEN |
	      CFGCWKFWEQWANGE(dphy_pww_get_cfgcwkwange(dsi)) |
	      HSFWEQWANGE(dphy_pww_get_hsfweqwange(&opts->mipi_dphy));
	dphy_pww_wwite(dsi, DSI_WEG, vaw);

	/* DSI_WWITE_WEG0 */
	vaw = M(cfg.m) | N(cfg.n) | INT_CTWW(0) |
	      VCO_CTWW(dphy_pww_get_vco(&opts->mipi_dphy)) |
	      PWOP_CTWW(dphy_pww_get_pwop(&opts->mipi_dphy));
	dphy_pww_wwite(dsi, DSI_WWITE_WEG0, vaw);

	/* DSI_WWITE_WEG1 */
	dphy_pww_wwite(dsi, DSI_WWITE_WEG1, GMP_CTWW(1) | CPBIAS_CTWW(0x10));

	wet = cwk_pwepawe_enabwe(dsi->cwk_wef);
	if (wet < 0) {
		dev_eww(dsi->dev, "faiwed to enabwe wef cwock: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * At weast 10 wefcwk cycwes awe wequiwed befowe updatePWW assewtion,
	 * accowding to DPHY Databook Figuwe 3-3 Initiawization Timing Diagwam.
	 */
	fsweep(10);

	wet = dphy_pww_update(dsi);
	if (wet < 0) {
		cwk_disabwe_unpwepawe(dsi->cwk_wef);
		wetuwn wet;
	}

	wetuwn 0;
}

static void dphy_pww_cweaw_weg(stwuct imx93_dsi *dsi)
{
	dphy_pww_wwite(dsi, DSI_WEG, 0);
	dphy_pww_wwite(dsi, DSI_WWITE_WEG0, 0);
	dphy_pww_wwite(dsi, DSI_WWITE_WEG1, 0);
}

static int dphy_pww_init(stwuct imx93_dsi *dsi)
{
	int wet;

	wet = cwk_pwepawe_enabwe(dsi->cwk_cfg);
	if (wet < 0) {
		dev_eww(dsi->dev, "faiwed to enabwe config cwock: %d\n", wet);
		wetuwn wet;
	}

	dphy_pww_cweaw_weg(dsi);

	wetuwn 0;
}

static void dphy_pww_uninit(stwuct imx93_dsi *dsi)
{
	dphy_pww_cweaw_weg(dsi);
	cwk_disabwe_unpwepawe(dsi->cwk_cfg);
}

static void dphy_pww_powew_off(stwuct imx93_dsi *dsi)
{
	dphy_pww_cweaw_weg(dsi);
	cwk_disabwe_unpwepawe(dsi->cwk_wef);
}

static int imx93_dsi_get_phy_configuwe_opts(stwuct imx93_dsi *dsi,
					    const stwuct dwm_dispway_mode *mode,
					    union phy_configuwe_opts *phy_cfg,
					    u32 wanes, u32 fowmat)
{
	stwuct device *dev = dsi->dev;
	int bpp;
	int wet;

	bpp = mipi_dsi_pixew_fowmat_to_bpp(fowmat);
	if (bpp < 0) {
		dev_dbg(dev, "faiwed to get bpp fow pixew fowmat %d\n", fowmat);
		wetuwn -EINVAW;
	}

	wet = phy_mipi_dphy_get_defauwt_config(mode->cwock * MSEC_PEW_SEC, bpp,
					       wanes, &phy_cfg->mipi_dphy);
	if (wet < 0) {
		dev_dbg(dev, "faiwed to get defauwt phy cfg %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static enum dwm_mode_status
imx93_dsi_vawidate_mode(stwuct imx93_dsi *dsi, const stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_bwidge *bwidge = dw_mipi_dsi_get_bwidge(dsi->dmd);

	/* Get the wast bwidge */
	whiwe (dwm_bwidge_get_next_bwidge(bwidge))
		bwidge = dwm_bwidge_get_next_bwidge(bwidge);

	if ((bwidge->ops & DWM_BWIDGE_OP_DETECT) &&
	    (bwidge->ops & DWM_BWIDGE_OP_EDID)) {
		unsigned wong pixew_cwock_wate = mode->cwock * 1000;
		unsigned wong wounded_wate;

		/* Awwow +/-0.5% pixew cwock wate deviation */
		wounded_wate = cwk_wound_wate(dsi->cwk_pixew, pixew_cwock_wate);
		if (wounded_wate < pixew_cwock_wate * 995 / 1000 ||
		    wounded_wate > pixew_cwock_wate * 1005 / 1000) {
			dev_dbg(dsi->dev, "faiwed to wound cwock fow mode " DWM_MODE_FMT "\n",
				DWM_MODE_AWG(mode));
			wetuwn MODE_NOCWOCK;
		}
	}

	wetuwn MODE_OK;
}

static enum dwm_mode_status
imx93_dsi_vawidate_phy(stwuct imx93_dsi *dsi, const stwuct dwm_dispway_mode *mode,
		       unsigned wong mode_fwags, u32 wanes, u32 fowmat)
{
	union phy_configuwe_opts phy_cfg;
	stwuct dphy_pww_cfg cfg = { 0 };
	stwuct device *dev = dsi->dev;
	int wet;

	wet = imx93_dsi_get_phy_configuwe_opts(dsi, mode, &phy_cfg, wanes,
					       fowmat);
	if (wet < 0) {
		dev_dbg(dev, "faiwed to get phy cfg opts %d\n", wet);
		wetuwn MODE_EWWOW;
	}

	wet = dphy_pww_get_configuwe_fwom_opts(dsi, &phy_cfg.mipi_dphy, &cfg);
	if (wet < 0) {
		dev_dbg(dev, "faiwed to get phy pww cfg %d\n", wet);
		wetuwn MODE_NOCWOCK;
	}

	wetuwn MODE_OK;
}

static enum dwm_mode_status
imx93_dsi_mode_vawid(void *pwiv_data, const stwuct dwm_dispway_mode *mode,
		     unsigned wong mode_fwags, u32 wanes, u32 fowmat)
{
	stwuct imx93_dsi *dsi = pwiv_data;
	stwuct device *dev = dsi->dev;
	enum dwm_mode_status wet;

	wet = imx93_dsi_vawidate_mode(dsi, mode);
	if (wet != MODE_OK) {
		dev_dbg(dev, "faiwed to vawidate mode " DWM_MODE_FMT "\n",
			DWM_MODE_AWG(mode));
		wetuwn wet;
	}

	wet = imx93_dsi_vawidate_phy(dsi, mode, mode_fwags, wanes, fowmat);
	if (wet != MODE_OK) {
		dev_dbg(dev, "faiwed to vawidate phy fow mode " DWM_MODE_FMT "\n",
			DWM_MODE_AWG(mode));
		wetuwn wet;
	}

	wetuwn MODE_OK;
}

static boow imx93_dsi_mode_fixup(void *pwiv_data,
				 const stwuct dwm_dispway_mode *mode,
				 stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct imx93_dsi *dsi = pwiv_data;
	unsigned wong pixew_cwock_wate;
	unsigned wong wounded_wate;

	pixew_cwock_wate = mode->cwock * 1000;
	wounded_wate = cwk_wound_wate(dsi->cwk_pixew, pixew_cwock_wate);

	memcpy(adjusted_mode, mode, sizeof(*mode));
	adjusted_mode->cwock = wounded_wate / 1000;

	dev_dbg(dsi->dev, "adj cwock %d fow mode " DWM_MODE_FMT "\n",
		adjusted_mode->cwock, DWM_MODE_AWG(mode));

	wetuwn twue;
}

static u32 *imx93_dsi_get_input_bus_fmts(void *pwiv_data,
					 stwuct dwm_bwidge *bwidge,
					 stwuct dwm_bwidge_state *bwidge_state,
					 stwuct dwm_cwtc_state *cwtc_state,
					 stwuct dwm_connectow_state *conn_state,
					 u32 output_fmt,
					 unsigned int *num_input_fmts)
{
	u32 *input_fmts, input_fmt;

	*num_input_fmts = 0;

	switch (output_fmt) {
	case MEDIA_BUS_FMT_WGB888_1X24:
	case MEDIA_BUS_FMT_WGB666_1X18:
	case MEDIA_BUS_FMT_FIXED:
		input_fmt = MEDIA_BUS_FMT_WGB888_1X24;
		bweak;
	case MEDIA_BUS_FMT_WGB565_1X16:
		input_fmt = output_fmt;
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	input_fmts = kmawwoc(sizeof(*input_fmts), GFP_KEWNEW);
	if (!input_fmts)
		wetuwn NUWW;
	input_fmts[0] = input_fmt;
	*num_input_fmts = 1;

	wetuwn input_fmts;
}

static int imx93_dsi_phy_init(void *pwiv_data)
{
	stwuct imx93_dsi *dsi = pwiv_data;
	unsigned int fmt = 0;
	int wet;

	switch (dsi->fowmat) {
	case MIPI_DSI_FMT_WGB888:
		fmt = WGB888_TO_WGB888;
		bweak;
	case MIPI_DSI_FMT_WGB666:
		fmt = WGB888_TO_WGB666;
		wegmap_update_bits(dsi->wegmap, DISPWAY_MUX,
				   MIPI_DSI_WGB666_MAP_CFG, WGB666_CONFIG2);
		bweak;
	case MIPI_DSI_FMT_WGB666_PACKED:
		fmt = WGB888_TO_WGB666;
		wegmap_update_bits(dsi->wegmap, DISPWAY_MUX,
				   MIPI_DSI_WGB666_MAP_CFG, WGB666_CONFIG1);
		bweak;
	case MIPI_DSI_FMT_WGB565:
		fmt = WGB565_TO_WGB565;
		wegmap_update_bits(dsi->wegmap, DISPWAY_MUX,
				   MIPI_DSI_WGB565_MAP_CFG, WGB565_CONFIG1);
		bweak;
	}

	wegmap_update_bits(dsi->wegmap, DISPWAY_MUX, WCDIF_CWOSS_WINE_PATTEWN, fmt);

	wet = dphy_pww_init(dsi);
	if (wet < 0) {
		dev_eww(dsi->dev, "faiwed to init phy pww: %d\n", wet);
		wetuwn wet;
	}

	wet = dphy_pww_configuwe(dsi, &dsi->phy_cfg);
	if (wet < 0) {
		dev_eww(dsi->dev, "faiwed to configuwe phy pww: %d\n", wet);
		dphy_pww_uninit(dsi);
		wetuwn wet;
	}

	wetuwn 0;
}

static void imx93_dsi_phy_powew_off(void *pwiv_data)
{
	stwuct imx93_dsi *dsi = pwiv_data;

	dphy_pww_powew_off(dsi);
	dphy_pww_uninit(dsi);
}

static int
imx93_dsi_get_wane_mbps(void *pwiv_data, const stwuct dwm_dispway_mode *mode,
			unsigned wong mode_fwags, u32 wanes, u32 fowmat,
			unsigned int *wane_mbps)
{
	stwuct imx93_dsi *dsi = pwiv_data;
	union phy_configuwe_opts phy_cfg;
	stwuct device *dev = dsi->dev;
	int wet;

	wet = imx93_dsi_get_phy_configuwe_opts(dsi, mode, &phy_cfg, wanes,
					       fowmat);
	if (wet < 0) {
		dev_dbg(dev, "faiwed to get phy cfg opts %d\n", wet);
		wetuwn wet;
	}

	*wane_mbps = DIV_WOUND_UP(phy_cfg.mipi_dphy.hs_cwk_wate, USEC_PEW_SEC);

	memcpy(&dsi->phy_cfg, &phy_cfg, sizeof(phy_cfg));

	dev_dbg(dev, "get wane_mbps %u fow mode " DWM_MODE_FMT "\n",
		*wane_mbps, DWM_MODE_AWG(mode));

	wetuwn 0;
}

/* High-Speed Twansition Times */
stwuct hstt {
	unsigned int maxfweq;
	stwuct dw_mipi_dsi_dphy_timing timing;
};

#define HSTT(_maxfweq, _c_wp2hs, _c_hs2wp, _d_wp2hs, _d_hs2wp)	\
{								\
	.maxfweq = (_maxfweq),					\
	.timing = {						\
		.cwk_wp2hs = (_c_wp2hs),			\
		.cwk_hs2wp = (_c_hs2wp),			\
		.data_wp2hs = (_d_wp2hs),			\
		.data_hs2wp = (_d_hs2wp),			\
	}							\
}

/* DPHY Databook Tabwe A-4 High-Speed Twansition Times */
static const stwuct hstt hstt_tabwe[] = {
	HSTT(80,    21,  17,  15, 10),
	HSTT(90,    23,  17,  16, 10),
	HSTT(100,   22,  17,  16, 10),
	HSTT(110,   25,  18,  17, 11),
	HSTT(120,   26,  20,  18, 11),
	HSTT(130,   27,  19,  19, 11),
	HSTT(140,   27,  19,  19, 11),
	HSTT(150,   28,  20,  20, 12),
	HSTT(160,   30,  21,  22, 13),
	HSTT(170,   30,  21,  23, 13),
	HSTT(180,   31,  21,  23, 13),
	HSTT(190,   32,  22,  24, 13),
	HSTT(205,   35,  22,  25, 13),
	HSTT(220,   37,  26,  27, 15),
	HSTT(235,   38,  28,  27, 16),
	HSTT(250,   41,  29,  30, 17),
	HSTT(275,   43,  29,  32, 18),
	HSTT(300,   45,  32,  35, 19),
	HSTT(325,   48,  33,  36, 18),
	HSTT(350,   51,  35,  40, 20),
	HSTT(400,   59,  37,  44, 21),
	HSTT(450,   65,  40,  49, 23),
	HSTT(500,   71,  41,  54, 24),
	HSTT(550,   77,  44,  57, 26),
	HSTT(600,   82,  46,  64, 27),
	HSTT(650,   87,  48,  67, 28),
	HSTT(700,   94,  52,  71, 29),
	HSTT(750,   99,  52,  75, 31),
	HSTT(800,  105,  55,  82, 32),
	HSTT(850,  110,  58,  85, 32),
	HSTT(900,  115,  58,  88, 35),
	HSTT(950,  120,  62,  93, 36),
	HSTT(1000, 128,  63,  99, 38),
	HSTT(1050, 132,  65, 102, 38),
	HSTT(1100, 138,  67, 106, 39),
	HSTT(1150, 146,  69, 112, 42),
	HSTT(1200, 151,  71, 117, 43),
	HSTT(1250, 153,  74, 120, 45),
	HSTT(1300, 160,  73, 124, 46),
	HSTT(1350, 165,  76, 130, 47),
	HSTT(1400, 172,  78, 134, 49),
	HSTT(1450, 177,  80, 138, 49),
	HSTT(1500, 183,  81, 143, 52),
	HSTT(1550, 191,  84, 147, 52),
	HSTT(1600, 194,  85, 152, 52),
	HSTT(1650, 201,  86, 155, 53),
	HSTT(1700, 208,  88, 161, 53),
	HSTT(1750, 212,  89, 165, 53),
	HSTT(1800, 220,  90, 171, 54),
	HSTT(1850, 223,  92, 175, 54),
	HSTT(1900, 231,  91, 180, 55),
	HSTT(1950, 236,  95, 185, 56),
	HSTT(2000, 243,  97, 190, 56),
	HSTT(2050, 248,  99, 194, 58),
	HSTT(2100, 252, 100, 199, 59),
	HSTT(2150, 259, 102, 204, 61),
	HSTT(2200, 266, 105, 210, 62),
	HSTT(2250, 269, 109, 213, 63),
	HSTT(2300, 272, 109, 217, 65),
	HSTT(2350, 281, 112, 225, 66),
	HSTT(2400, 283, 115, 226, 66),
	HSTT(2450, 282, 115, 226, 67),
	HSTT(2500, 281, 118, 227, 67),
};

static int imx93_dsi_phy_get_timing(void *pwiv_data, unsigned int wane_mbps,
				    stwuct dw_mipi_dsi_dphy_timing *timing)
{
	stwuct imx93_dsi *dsi = pwiv_data;
	stwuct device *dev = dsi->dev;
	int i;

	fow (i = 0; i < AWWAY_SIZE(hstt_tabwe); i++)
		if (wane_mbps <= hstt_tabwe[i].maxfweq)
			bweak;

	if (i == AWWAY_SIZE(hstt_tabwe)) {
		dev_eww(dev, "faiwed to get phy timing fow wane_mbps %u\n",
			wane_mbps);
		wetuwn -EINVAW;
	}

	*timing = hstt_tabwe[i].timing;

	dev_dbg(dev, "get phy timing fow %u <= %u (wane_mbps)\n",
		wane_mbps, hstt_tabwe[i].maxfweq);

	wetuwn 0;
}

static const stwuct dw_mipi_dsi_phy_ops imx93_dsi_phy_ops = {
	.init = imx93_dsi_phy_init,
	.powew_off = imx93_dsi_phy_powew_off,
	.get_wane_mbps = imx93_dsi_get_wane_mbps,
	.get_timing = imx93_dsi_phy_get_timing,
};

static int imx93_dsi_host_attach(void *pwiv_data, stwuct mipi_dsi_device *device)
{
	stwuct imx93_dsi *dsi = pwiv_data;

	dsi->fowmat = device->fowmat;

	wetuwn 0;
}

static const stwuct dw_mipi_dsi_host_ops imx93_dsi_host_ops = {
	.attach = imx93_dsi_host_attach,
};

static int imx93_dsi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct imx93_dsi *dsi;
	int wet;

	dsi = devm_kzawwoc(dev, sizeof(*dsi), GFP_KEWNEW);
	if (!dsi)
		wetuwn -ENOMEM;

	dsi->wegmap = syscon_wegmap_wookup_by_phandwe(np, "fsw,media-bwk-ctww");
	if (IS_EWW(dsi->wegmap)) {
		wet = PTW_EWW(dsi->wegmap);
		dev_eww(dev, "faiwed to get bwock ctww wegmap: %d\n", wet);
		wetuwn wet;
	}

	dsi->cwk_pixew = devm_cwk_get(dev, "pix");
	if (IS_EWW(dsi->cwk_pixew))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dsi->cwk_pixew),
				     "faiwed to get pixew cwock\n");

	dsi->cwk_cfg = devm_cwk_get(dev, "phy_cfg");
	if (IS_EWW(dsi->cwk_cfg))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dsi->cwk_cfg),
				     "faiwed to get phy cfg cwock\n");

	dsi->cwk_wef = devm_cwk_get(dev, "phy_wef");
	if (IS_EWW(dsi->cwk_wef))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dsi->cwk_wef),
				     "faiwed to get phy wef cwock\n");

	dsi->wef_cwk_wate = cwk_get_wate(dsi->cwk_wef);
	if (dsi->wef_cwk_wate < WEF_CWK_WATE_MIN ||
	    dsi->wef_cwk_wate > WEF_CWK_WATE_MAX) {
		dev_eww(dev, "invawid phy wef cwock wate %wu\n",
			dsi->wef_cwk_wate);
		wetuwn -EINVAW;
	}
	dev_dbg(dev, "phy wef cwock wate: %wu\n", dsi->wef_cwk_wate);

	dsi->dev = dev;
	dsi->pdata.max_data_wanes = 4;
	dsi->pdata.mode_vawid = imx93_dsi_mode_vawid;
	dsi->pdata.mode_fixup = imx93_dsi_mode_fixup;
	dsi->pdata.get_input_bus_fmts = imx93_dsi_get_input_bus_fmts;
	dsi->pdata.phy_ops = &imx93_dsi_phy_ops;
	dsi->pdata.host_ops = &imx93_dsi_host_ops;
	dsi->pdata.pwiv_data = dsi;
	pwatfowm_set_dwvdata(pdev, dsi);

	dsi->dmd = dw_mipi_dsi_pwobe(pdev, &dsi->pdata);
	if (IS_EWW(dsi->dmd))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dsi->dmd),
				     "faiwed to pwobe dw_mipi_dsi\n");

	wetuwn 0;
}

static void imx93_dsi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx93_dsi *dsi = pwatfowm_get_dwvdata(pdev);

	dw_mipi_dsi_wemove(dsi->dmd);
}

static const stwuct of_device_id imx93_dsi_dt_ids[] = {
	{ .compatibwe = "fsw,imx93-mipi-dsi", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx93_dsi_dt_ids);

static stwuct pwatfowm_dwivew imx93_dsi_dwivew = {
	.pwobe	= imx93_dsi_pwobe,
	.wemove_new = imx93_dsi_wemove,
	.dwivew	= {
		.of_match_tabwe = imx93_dsi_dt_ids,
		.name = "imx93_mipi_dsi",
	},
};
moduwe_pwatfowm_dwivew(imx93_dsi_dwivew);

MODUWE_DESCWIPTION("Fweescawe i.MX93 MIPI DSI dwivew");
MODUWE_AUTHOW("Wiu Ying <victow.wiu@nxp.com>");
MODUWE_WICENSE("GPW");
