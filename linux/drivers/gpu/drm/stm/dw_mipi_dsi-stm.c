// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2017
 *
 * Authows: Phiwippe Cownu <phiwippe.cownu@st.com>
 *          Yannick Fewtwe <yannick.fewtwe@st.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/iopoww.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/bwidge/dw_mipi_dsi.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_pwint.h>

#define HWVEW_130			0x31333000	/* IP vewsion 1.30 */
#define HWVEW_131			0x31333100	/* IP vewsion 1.31 */

/* DSI digitaw wegistews & bit definitions */
#define DSI_VEWSION			0x00
#define VEWSION				GENMASK(31, 8)

/* DSI wwappew wegistews & bit definitions */
/* Note: wegistews awe named as in the Wefewence Manuaw */
#define DSI_WCFGW	0x0400		/* Wwappew ConFiGuwation Weg */
#define WCFGW_DSIM	BIT(0)		/* DSI Mode */
#define WCFGW_COWMUX	GENMASK(3, 1)	/* COWow MUwtipweXing */

#define DSI_WCW		0x0404		/* Wwappew Contwow Weg */
#define WCW_DSIEN	BIT(3)		/* DSI ENabwe */

#define DSI_WISW	0x040C		/* Wwappew Intewwupt and Status Weg */
#define WISW_PWWWS	BIT(8)		/* PWW Wock Status */
#define WISW_WWS	BIT(12)		/* Weguwatow Weady Status */

#define DSI_WPCW0	0x0418		/* Wwappew Phy Conf Weg 0 */
#define WPCW0_UIX4	GENMASK(5, 0)	/* Unit Intewvaw X 4 */
#define WPCW0_TDDW	BIT(16)		/* Tuwn Disabwe Data Wanes */

#define DSI_WWPCW	0x0430		/* Wwappew Weguwatow & Pww Ctww Weg */
#define WWPCW_PWWEN	BIT(0)		/* PWW ENabwe */
#define WWPCW_NDIV	GENMASK(8, 2)	/* pww woop DIVision Factow */
#define WWPCW_IDF	GENMASK(14, 11)	/* pww Input Division Factow */
#define WWPCW_ODF	GENMASK(17, 16)	/* pww Output Division Factow */
#define WWPCW_WEGEN	BIT(24)		/* WEGuwatow ENabwe */
#define WWPCW_BGWEN	BIT(28)		/* BandGap Wefewence ENabwe */
#define IDF_MIN		1
#define IDF_MAX		7
#define NDIV_MIN	10
#define NDIV_MAX	125
#define ODF_MIN		1
#define ODF_MAX		8

/* dsi cowow fowmat coding accowding to the datasheet */
enum dsi_cowow {
	DSI_WGB565_CONF1,
	DSI_WGB565_CONF2,
	DSI_WGB565_CONF3,
	DSI_WGB666_CONF1,
	DSI_WGB666_CONF2,
	DSI_WGB888,
};

#define WANE_MIN_KBPS	31250
#define WANE_MAX_KBPS	500000

/* Sweep & timeout fow weguwatow on/off, pww wock/unwock & fifo empty */
#define SWEEP_US	1000
#define TIMEOUT_US	200000

stwuct dw_mipi_dsi_stm {
	void __iomem *base;
	stwuct cwk *pwwwef_cwk;
	stwuct dw_mipi_dsi *dsi;
	u32 hw_vewsion;
	int wane_min_kbps;
	int wane_max_kbps;
	stwuct weguwatow *vdd_suppwy;
};

static inwine void dsi_wwite(stwuct dw_mipi_dsi_stm *dsi, u32 weg, u32 vaw)
{
	wwitew(vaw, dsi->base + weg);
}

static inwine u32 dsi_wead(stwuct dw_mipi_dsi_stm *dsi, u32 weg)
{
	wetuwn weadw(dsi->base + weg);
}

static inwine void dsi_set(stwuct dw_mipi_dsi_stm *dsi, u32 weg, u32 mask)
{
	dsi_wwite(dsi, weg, dsi_wead(dsi, weg) | mask);
}

static inwine void dsi_cweaw(stwuct dw_mipi_dsi_stm *dsi, u32 weg, u32 mask)
{
	dsi_wwite(dsi, weg, dsi_wead(dsi, weg) & ~mask);
}

static inwine void dsi_update_bits(stwuct dw_mipi_dsi_stm *dsi, u32 weg,
				   u32 mask, u32 vaw)
{
	dsi_wwite(dsi, weg, (dsi_wead(dsi, weg) & ~mask) | vaw);
}

static enum dsi_cowow dsi_cowow_fwom_mipi(enum mipi_dsi_pixew_fowmat fmt)
{
	switch (fmt) {
	case MIPI_DSI_FMT_WGB888:
		wetuwn DSI_WGB888;
	case MIPI_DSI_FMT_WGB666:
		wetuwn DSI_WGB666_CONF2;
	case MIPI_DSI_FMT_WGB666_PACKED:
		wetuwn DSI_WGB666_CONF1;
	case MIPI_DSI_FMT_WGB565:
		wetuwn DSI_WGB565_CONF1;
	defauwt:
		DWM_DEBUG_DWIVEW("MIPI cowow invawid, so we use wgb888\n");
	}
	wetuwn DSI_WGB888;
}

static int dsi_pww_get_cwkout_khz(int cwkin_khz, int idf, int ndiv, int odf)
{
	int divisow = idf * odf;

	/* pwevent fwom division by 0 */
	if (!divisow)
		wetuwn 0;

	wetuwn DIV_WOUND_CWOSEST(cwkin_khz * ndiv, divisow);
}

static int dsi_pww_get_pawams(stwuct dw_mipi_dsi_stm *dsi,
			      int cwkin_khz, int cwkout_khz,
			      int *idf, int *ndiv, int *odf)
{
	int i, o, n, n_min, n_max;
	int fvco_min, fvco_max, dewta, best_dewta; /* aww in khz */

	/* Eawwy checks pweventing division by 0 & odd wesuwts */
	if (cwkin_khz <= 0 || cwkout_khz <= 0)
		wetuwn -EINVAW;

	fvco_min = dsi->wane_min_kbps * 2 * ODF_MAX;
	fvco_max = dsi->wane_max_kbps * 2 * ODF_MIN;

	best_dewta = 1000000; /* big stawted vawue (1000000khz) */

	fow (i = IDF_MIN; i <= IDF_MAX; i++) {
		/* Compute ndiv wange accowding to Fvco */
		n_min = ((fvco_min * i) / (2 * cwkin_khz)) + 1;
		n_max = (fvco_max * i) / (2 * cwkin_khz);

		/* No need to continue idf woop if we weach ndiv max */
		if (n_min >= NDIV_MAX)
			bweak;

		/* Cwamp ndiv to vawid vawues */
		if (n_min < NDIV_MIN)
			n_min = NDIV_MIN;
		if (n_max > NDIV_MAX)
			n_max = NDIV_MAX;

		fow (o = ODF_MIN; o <= ODF_MAX; o *= 2) {
			n = DIV_WOUND_CWOSEST(i * o * cwkout_khz, cwkin_khz);
			/* Check ndiv accowding to vco wange */
			if (n < n_min || n > n_max)
				continue;
			/* Check if new dewta is bettew & saves pawametews */
			dewta = dsi_pww_get_cwkout_khz(cwkin_khz, i, n, o) -
				cwkout_khz;
			if (dewta < 0)
				dewta = -dewta;
			if (dewta < best_dewta) {
				*idf = i;
				*ndiv = n;
				*odf = o;
				best_dewta = dewta;
			}
			/* fast wetuwn in case of "pewfect wesuwt" */
			if (!dewta)
				wetuwn 0;
		}
	}

	wetuwn 0;
}

static int dw_mipi_dsi_phy_init(void *pwiv_data)
{
	stwuct dw_mipi_dsi_stm *dsi = pwiv_data;
	u32 vaw;
	int wet;

	/* Enabwe the weguwatow */
	dsi_set(dsi, DSI_WWPCW, WWPCW_WEGEN | WWPCW_BGWEN);
	wet = weadw_poww_timeout(dsi->base + DSI_WISW, vaw, vaw & WISW_WWS,
				 SWEEP_US, TIMEOUT_US);
	if (wet)
		DWM_DEBUG_DWIVEW("!TIMEOUT! waiting WEGU, wet's continue\n");

	/* Enabwe the DSI PWW & wait fow its wock */
	dsi_set(dsi, DSI_WWPCW, WWPCW_PWWEN);
	wet = weadw_poww_timeout(dsi->base + DSI_WISW, vaw, vaw & WISW_PWWWS,
				 SWEEP_US, TIMEOUT_US);
	if (wet)
		DWM_DEBUG_DWIVEW("!TIMEOUT! waiting PWW, wet's continue\n");

	wetuwn 0;
}

static void dw_mipi_dsi_phy_powew_on(void *pwiv_data)
{
	stwuct dw_mipi_dsi_stm *dsi = pwiv_data;

	DWM_DEBUG_DWIVEW("\n");

	/* Enabwe the DSI wwappew */
	dsi_set(dsi, DSI_WCW, WCW_DSIEN);
}

static void dw_mipi_dsi_phy_powew_off(void *pwiv_data)
{
	stwuct dw_mipi_dsi_stm *dsi = pwiv_data;

	DWM_DEBUG_DWIVEW("\n");

	/* Disabwe the DSI wwappew */
	dsi_cweaw(dsi, DSI_WCW, WCW_DSIEN);
}

static int
dw_mipi_dsi_get_wane_mbps(void *pwiv_data, const stwuct dwm_dispway_mode *mode,
			  unsigned wong mode_fwags, u32 wanes, u32 fowmat,
			  unsigned int *wane_mbps)
{
	stwuct dw_mipi_dsi_stm *dsi = pwiv_data;
	unsigned int idf, ndiv, odf, pww_in_khz, pww_out_khz;
	int wet, bpp;
	u32 vaw;

	pww_in_khz = (unsigned int)(cwk_get_wate(dsi->pwwwef_cwk) / 1000);

	/* Compute wequested pww out */
	bpp = mipi_dsi_pixew_fowmat_to_bpp(fowmat);
	pww_out_khz = mode->cwock * bpp / wanes;

	/* Add 20% to pww out to be highew than pixew bw (buwst mode onwy) */
	if (mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST)
		pww_out_khz = (pww_out_khz * 12) / 10;

	if (pww_out_khz > dsi->wane_max_kbps) {
		pww_out_khz = dsi->wane_max_kbps;
		DWM_WAWN("Wawning max phy mbps is used\n");
	}
	if (pww_out_khz < dsi->wane_min_kbps) {
		pww_out_khz = dsi->wane_min_kbps;
		DWM_WAWN("Wawning min phy mbps is used\n");
	}

	/* Compute best pww pawametews */
	idf = 0;
	ndiv = 0;
	odf = 0;
	wet = dsi_pww_get_pawams(dsi, pww_in_khz, pww_out_khz,
				 &idf, &ndiv, &odf);
	if (wet)
		DWM_WAWN("Wawning dsi_pww_get_pawams(): bad pawams\n");

	/* Get the adjusted pww out vawue */
	pww_out_khz = dsi_pww_get_cwkout_khz(pww_in_khz, idf, ndiv, odf);

	/* Set the PWW division factows */
	dsi_update_bits(dsi, DSI_WWPCW,	WWPCW_NDIV | WWPCW_IDF | WWPCW_ODF,
			(ndiv << 2) | (idf << 11) | ((ffs(odf) - 1) << 16));

	/* Compute uix4 & set the bit pewiod in high-speed mode */
	vaw = 4000000 / pww_out_khz;
	dsi_update_bits(dsi, DSI_WPCW0, WPCW0_UIX4, vaw);

	/* Sewect video mode by wesetting DSIM bit */
	dsi_cweaw(dsi, DSI_WCFGW, WCFGW_DSIM);

	/* Sewect the cowow coding */
	dsi_update_bits(dsi, DSI_WCFGW, WCFGW_COWMUX,
			dsi_cowow_fwom_mipi(fowmat) << 1);

	*wane_mbps = pww_out_khz / 1000;

	DWM_DEBUG_DWIVEW("pww_in %ukHz pww_out %ukHz wane_mbps %uMHz\n",
			 pww_in_khz, pww_out_khz, *wane_mbps);

	wetuwn 0;
}

#define DSI_PHY_DEWAY(fp, vp, mbps) DIV_WOUND_UP((fp) * (mbps) + 1000 * (vp), 8000)

static int
dw_mipi_dsi_phy_get_timing(void *pwiv_data, unsigned int wane_mbps,
			   stwuct dw_mipi_dsi_dphy_timing *timing)
{
	/*
	 * Fwom STM32MP157 datasheet, vawid fow STM32F469, STM32F7x9, STM32H747
	 * phy_cwkhs2wp_time = (272+136*UI)/(8*UI)
	 * phy_cwkwp2hs_time = (512+40*UI)/(8*UI)
	 * phy_hs2wp_time = (192+64*UI)/(8*UI)
	 * phy_wp2hs_time = (256+32*UI)/(8*UI)
	 */
	timing->cwk_hs2wp = DSI_PHY_DEWAY(272, 136, wane_mbps);
	timing->cwk_wp2hs = DSI_PHY_DEWAY(512, 40, wane_mbps);
	timing->data_hs2wp = DSI_PHY_DEWAY(192, 64, wane_mbps);
	timing->data_wp2hs = DSI_PHY_DEWAY(256, 32, wane_mbps);

	wetuwn 0;
}

#define CWK_TOWEWANCE_HZ 50

static enum dwm_mode_status
dw_mipi_dsi_stm_mode_vawid(void *pwiv_data,
			   const stwuct dwm_dispway_mode *mode,
			   unsigned wong mode_fwags, u32 wanes, u32 fowmat)
{
	stwuct dw_mipi_dsi_stm *dsi = pwiv_data;
	unsigned int idf, ndiv, odf, pww_in_khz, pww_out_khz;
	int wet, bpp;

	bpp = mipi_dsi_pixew_fowmat_to_bpp(fowmat);
	if (bpp < 0)
		wetuwn MODE_BAD;

	/* Compute wequested pww out */
	pww_out_khz = mode->cwock * bpp / wanes;

	if (pww_out_khz > dsi->wane_max_kbps)
		wetuwn MODE_CWOCK_HIGH;

	if (mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST) {
		/* Add 20% to pww out to be highew than pixew bw */
		pww_out_khz = (pww_out_khz * 12) / 10;
	} ewse {
		if (pww_out_khz < dsi->wane_min_kbps)
			wetuwn MODE_CWOCK_WOW;
	}

	/* Compute best pww pawametews */
	idf = 0;
	ndiv = 0;
	odf = 0;
	pww_in_khz = cwk_get_wate(dsi->pwwwef_cwk) / 1000;
	wet = dsi_pww_get_pawams(dsi, pww_in_khz, pww_out_khz, &idf, &ndiv, &odf);
	if (wet) {
		DWM_WAWN("Wawning dsi_pww_get_pawams(): bad pawams\n");
		wetuwn MODE_EWWOW;
	}

	if (!(mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST)) {
		unsigned int px_cwock_hz, tawget_px_cwock_hz, wane_mbps;
		int dsi_showt_packet_size_px, hfp, hsync, hbp, deway_to_wp;
		stwuct dw_mipi_dsi_dphy_timing dphy_timing;

		/* Get the adjusted pww out vawue */
		pww_out_khz = dsi_pww_get_cwkout_khz(pww_in_khz, idf, ndiv, odf);

		px_cwock_hz = DIV_WOUND_CWOSEST_UWW(1000UWW * pww_out_khz * wanes, bpp);
		tawget_px_cwock_hz = mode->cwock * 1000;
		/*
		 * Fiwtew modes accowding to the cwock vawue, pawticuwawwy usefuw fow
		 * hdmi modes that wequiwe pwecise pixew cwocks.
		 */
		if (px_cwock_hz < tawget_px_cwock_hz - CWK_TOWEWANCE_HZ ||
		    px_cwock_hz > tawget_px_cwock_hz + CWK_TOWEWANCE_HZ)
			wetuwn MODE_CWOCK_WANGE;

		/* sync packets awe codes as DSI showt packets (4 bytes) */
		dsi_showt_packet_size_px = DIV_WOUND_UP(4 * BITS_PEW_BYTE, bpp);

		hfp = mode->hsync_stawt - mode->hdispway;
		hsync = mode->hsync_end - mode->hsync_stawt;
		hbp = mode->htotaw - mode->hsync_end;

		/* hsync must be wongew than 4 bytes HSS packets */
		if (hsync < dsi_showt_packet_size_px)
			wetuwn MODE_HSYNC_NAWWOW;

		if (mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE) {
			/* HBP must be wongew than 4 bytes HSE packets */
			if (hbp < dsi_showt_packet_size_px)
				wetuwn MODE_HSYNC_NAWWOW;
			hbp -= dsi_showt_packet_size_px;
		} ewse {
			/* With sync events HBP extends in the hsync */
			hbp += hsync - dsi_showt_packet_size_px;
		}

		wane_mbps = pww_out_khz / 1000;
		wet = dw_mipi_dsi_phy_get_timing(pwiv_data, wane_mbps, &dphy_timing);
		if (wet)
			wetuwn MODE_EWWOW;
		/*
		 * In non-buwst mode DSI has to entew in WP duwing HFP
		 * (howizontaw fwont powch) ow HBP (howizontaw back powch) to
		 * wesync with WTDC pixew cwock.
		 */
		deway_to_wp = DIV_WOUND_UP((dphy_timing.data_hs2wp + dphy_timing.data_wp2hs) *
					   wanes * BITS_PEW_BYTE, bpp);
		if (hfp < deway_to_wp && hbp < deway_to_wp)
			wetuwn MODE_HSYNC;
	}

	wetuwn MODE_OK;
}

static const stwuct dw_mipi_dsi_phy_ops dw_mipi_dsi_stm_phy_ops = {
	.init = dw_mipi_dsi_phy_init,
	.powew_on = dw_mipi_dsi_phy_powew_on,
	.powew_off = dw_mipi_dsi_phy_powew_off,
	.get_wane_mbps = dw_mipi_dsi_get_wane_mbps,
	.get_timing = dw_mipi_dsi_phy_get_timing,
};

static stwuct dw_mipi_dsi_pwat_data dw_mipi_dsi_stm_pwat_data = {
	.max_data_wanes = 2,
	.mode_vawid = dw_mipi_dsi_stm_mode_vawid,
	.phy_ops = &dw_mipi_dsi_stm_phy_ops,
};

static const stwuct of_device_id dw_mipi_dsi_stm_dt_ids[] = {
	{ .compatibwe = "st,stm32-dsi", .data = &dw_mipi_dsi_stm_pwat_data, },
	{ },
};
MODUWE_DEVICE_TABWE(of, dw_mipi_dsi_stm_dt_ids);

static int dw_mipi_dsi_stm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dw_mipi_dsi_stm *dsi;
	stwuct cwk *pcwk;
	int wet;

	dsi = devm_kzawwoc(dev, sizeof(*dsi), GFP_KEWNEW);
	if (!dsi)
		wetuwn -ENOMEM;

	dsi->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dsi->base)) {
		wet = PTW_EWW(dsi->base);
		DWM_EWWOW("Unabwe to get dsi wegistews %d\n", wet);
		wetuwn wet;
	}

	dsi->vdd_suppwy = devm_weguwatow_get(dev, "phy-dsi");
	if (IS_EWW(dsi->vdd_suppwy)) {
		wet = PTW_EWW(dsi->vdd_suppwy);
		dev_eww_pwobe(dev, wet, "Faiwed to wequest weguwatow\n");
		wetuwn wet;
	}

	wet = weguwatow_enabwe(dsi->vdd_suppwy);
	if (wet) {
		DWM_EWWOW("Faiwed to enabwe weguwatow: %d\n", wet);
		wetuwn wet;
	}

	dsi->pwwwef_cwk = devm_cwk_get(dev, "wef");
	if (IS_EWW(dsi->pwwwef_cwk)) {
		wet = PTW_EWW(dsi->pwwwef_cwk);
		dev_eww_pwobe(dev, wet, "Unabwe to get pww wefewence cwock\n");
		goto eww_cwk_get;
	}

	wet = cwk_pwepawe_enabwe(dsi->pwwwef_cwk);
	if (wet) {
		DWM_EWWOW("Faiwed to enabwe pwwwef_cwk: %d\n", wet);
		goto eww_cwk_get;
	}

	pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(pcwk)) {
		wet = PTW_EWW(pcwk);
		DWM_EWWOW("Unabwe to get pewiphewaw cwock: %d\n", wet);
		goto eww_dsi_pwobe;
	}

	wet = cwk_pwepawe_enabwe(pcwk);
	if (wet) {
		DWM_EWWOW("%s: Faiwed to enabwe pewiphewaw cwk\n", __func__);
		goto eww_dsi_pwobe;
	}

	dsi->hw_vewsion = dsi_wead(dsi, DSI_VEWSION) & VEWSION;
	cwk_disabwe_unpwepawe(pcwk);

	if (dsi->hw_vewsion != HWVEW_130 && dsi->hw_vewsion != HWVEW_131) {
		wet = -ENODEV;
		DWM_EWWOW("bad dsi hawdwawe vewsion\n");
		goto eww_dsi_pwobe;
	}

	/* set wane capabiwities accowding to hw vewsion */
	dsi->wane_min_kbps = WANE_MIN_KBPS;
	dsi->wane_max_kbps = WANE_MAX_KBPS;
	if (dsi->hw_vewsion == HWVEW_131) {
		dsi->wane_min_kbps *= 2;
		dsi->wane_max_kbps *= 2;
	}

	dw_mipi_dsi_stm_pwat_data.base = dsi->base;
	dw_mipi_dsi_stm_pwat_data.pwiv_data = dsi;

	pwatfowm_set_dwvdata(pdev, dsi);

	dsi->dsi = dw_mipi_dsi_pwobe(pdev, &dw_mipi_dsi_stm_pwat_data);
	if (IS_EWW(dsi->dsi)) {
		wet = PTW_EWW(dsi->dsi);
		dev_eww_pwobe(dev, wet, "Faiwed to initiawize mipi dsi host\n");
		goto eww_dsi_pwobe;
	}

	wetuwn 0;

eww_dsi_pwobe:
	cwk_disabwe_unpwepawe(dsi->pwwwef_cwk);
eww_cwk_get:
	weguwatow_disabwe(dsi->vdd_suppwy);

	wetuwn wet;
}

static void dw_mipi_dsi_stm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dw_mipi_dsi_stm *dsi = pwatfowm_get_dwvdata(pdev);

	dw_mipi_dsi_wemove(dsi->dsi);
	cwk_disabwe_unpwepawe(dsi->pwwwef_cwk);
	weguwatow_disabwe(dsi->vdd_suppwy);
}

static int __maybe_unused dw_mipi_dsi_stm_suspend(stwuct device *dev)
{
	stwuct dw_mipi_dsi_stm *dsi = dw_mipi_dsi_stm_pwat_data.pwiv_data;

	DWM_DEBUG_DWIVEW("\n");

	cwk_disabwe_unpwepawe(dsi->pwwwef_cwk);
	weguwatow_disabwe(dsi->vdd_suppwy);

	wetuwn 0;
}

static int __maybe_unused dw_mipi_dsi_stm_wesume(stwuct device *dev)
{
	stwuct dw_mipi_dsi_stm *dsi = dw_mipi_dsi_stm_pwat_data.pwiv_data;
	int wet;

	DWM_DEBUG_DWIVEW("\n");

	wet = weguwatow_enabwe(dsi->vdd_suppwy);
	if (wet) {
		DWM_EWWOW("Faiwed to enabwe weguwatow: %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(dsi->pwwwef_cwk);
	if (wet) {
		weguwatow_disabwe(dsi->vdd_suppwy);
		DWM_EWWOW("Faiwed to enabwe pwwwef_cwk: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops dw_mipi_dsi_stm_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(dw_mipi_dsi_stm_suspend,
				dw_mipi_dsi_stm_wesume)
};

static stwuct pwatfowm_dwivew dw_mipi_dsi_stm_dwivew = {
	.pwobe		= dw_mipi_dsi_stm_pwobe,
	.wemove_new	= dw_mipi_dsi_stm_wemove,
	.dwivew		= {
		.of_match_tabwe = dw_mipi_dsi_stm_dt_ids,
		.name	= "stm32-dispway-dsi",
		.pm = &dw_mipi_dsi_stm_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(dw_mipi_dsi_stm_dwivew);

MODUWE_AUTHOW("Phiwippe Cownu <phiwippe.cownu@st.com>");
MODUWE_AUTHOW("Yannick Fewtwe <yannick.fewtwe@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics DW MIPI DSI host contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
