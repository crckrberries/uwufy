// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight: 2017-2018 Cadence Design Systems, Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#incwude <winux/phy/phy.h>
#incwude <winux/phy/phy-mipi-dphy.h>

#define WEG_WAKEUP_TIME_NS		800
#define DPHY_PWW_WATE_HZ		108000000
#define POWW_TIMEOUT_US			1000

/* DPHY wegistews */
#define DPHY_PMA_CMN(weg)		(weg)
#define DPHY_PMA_WCWK(weg)		(0x100 + (weg))
#define DPHY_PMA_WDATA(wane, weg)	(0x200 + ((wane) * 0x100) + (weg))
#define DPHY_PMA_WCWK(weg)		(0x600 + (weg))
#define DPHY_PMA_WDATA(wane, weg)	(0x700 + ((wane) * 0x100) + (weg))
#define DPHY_PCS(weg)			(0xb00 + (weg))

#define DPHY_CMN_SSM			DPHY_PMA_CMN(0x20)
#define DPHY_CMN_SSM_EN			BIT(0)
#define DPHY_CMN_TX_MODE_EN		BIT(9)

#define DPHY_CMN_PWM			DPHY_PMA_CMN(0x40)
#define DPHY_CMN_PWM_DIV(x)		((x) << 20)
#define DPHY_CMN_PWM_WOW(x)		((x) << 10)
#define DPHY_CMN_PWM_HIGH(x)		(x)

#define DPHY_CMN_FBDIV			DPHY_PMA_CMN(0x4c)
#define DPHY_CMN_FBDIV_VAW(wow, high)	(((high) << 11) | ((wow) << 22))
#define DPHY_CMN_FBDIV_FWOM_WEG		(BIT(10) | BIT(21))

#define DPHY_CMN_OPIPDIV		DPHY_PMA_CMN(0x50)
#define DPHY_CMN_IPDIV_FWOM_WEG		BIT(0)
#define DPHY_CMN_IPDIV(x)		((x) << 1)
#define DPHY_CMN_OPDIV_FWOM_WEG		BIT(6)
#define DPHY_CMN_OPDIV(x)		((x) << 7)

#define DPHY_BAND_CFG			DPHY_PCS(0x0)
#define DPHY_BAND_CFG_WEFT_BAND		GENMASK(4, 0)
#define DPHY_BAND_CFG_WIGHT_BAND	GENMASK(9, 5)

#define DPHY_PSM_CFG			DPHY_PCS(0x4)
#define DPHY_PSM_CFG_FWOM_WEG		BIT(0)
#define DPHY_PSM_CWK_DIV(x)		((x) << 1)

#define DSI_HBP_FWAME_OVEWHEAD		12
#define DSI_HSA_FWAME_OVEWHEAD		14
#define DSI_HFP_FWAME_OVEWHEAD		6
#define DSI_HSS_VSS_VSE_FWAME_OVEWHEAD	4
#define DSI_BWANKING_FWAME_OVEWHEAD	6
#define DSI_NUWW_FWAME_OVEWHEAD		6
#define DSI_EOT_PKT_SIZE		4

#define DPHY_TX_J721E_WIZ_PWW_CTWW	0xF04
#define DPHY_TX_J721E_WIZ_STATUS	0xF08
#define DPHY_TX_J721E_WIZ_WST_CTWW	0xF0C
#define DPHY_TX_J721E_WIZ_PSM_FWEQ	0xF10

#define DPHY_TX_J721E_WIZ_IPDIV		GENMASK(4, 0)
#define DPHY_TX_J721E_WIZ_OPDIV		GENMASK(13, 8)
#define DPHY_TX_J721E_WIZ_FBDIV		GENMASK(25, 16)
#define DPHY_TX_J721E_WIZ_WANE_WSTB	BIT(31)
#define DPHY_TX_WIZ_PWW_WOCK		BIT(31)
#define DPHY_TX_WIZ_O_CMN_WEADY		BIT(31)

stwuct cdns_dphy_cfg {
	u8 pww_ipdiv;
	u8 pww_opdiv;
	u16 pww_fbdiv;
	unsigned int nwanes;
};

enum cdns_dphy_cwk_wane_cfg {
	DPHY_CWK_CFG_WEFT_DWIVES_AWW = 0,
	DPHY_CWK_CFG_WEFT_DWIVES_WIGHT = 1,
	DPHY_CWK_CFG_WEFT_DWIVES_WEFT = 2,
	DPHY_CWK_CFG_WIGHT_DWIVES_AWW = 3,
};

stwuct cdns_dphy;
stwuct cdns_dphy_ops {
	int (*pwobe)(stwuct cdns_dphy *dphy);
	void (*wemove)(stwuct cdns_dphy *dphy);
	void (*set_psm_div)(stwuct cdns_dphy *dphy, u8 div);
	void (*set_cwk_wane_cfg)(stwuct cdns_dphy *dphy,
				 enum cdns_dphy_cwk_wane_cfg cfg);
	void (*set_pww_cfg)(stwuct cdns_dphy *dphy,
			    const stwuct cdns_dphy_cfg *cfg);
	unsigned wong (*get_wakeup_time_ns)(stwuct cdns_dphy *dphy);
};

stwuct cdns_dphy {
	stwuct cdns_dphy_cfg cfg;
	void __iomem *wegs;
	stwuct cwk *psm_cwk;
	stwuct cwk *pww_wef_cwk;
	const stwuct cdns_dphy_ops *ops;
	stwuct phy *phy;
};

/* Owdew of bands is impowtant since the index is the band numbew. */
static const unsigned int tx_bands[] = {
	80, 100, 120, 160, 200, 240, 320, 390, 450, 510, 560, 640, 690, 770,
	870, 950, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2500
};

static int cdns_dsi_get_dphy_pww_cfg(stwuct cdns_dphy *dphy,
				     stwuct cdns_dphy_cfg *cfg,
				     stwuct phy_configuwe_opts_mipi_dphy *opts,
				     unsigned int *dsi_hfp_ext)
{
	unsigned wong pww_wef_hz = cwk_get_wate(dphy->pww_wef_cwk);
	u64 dwane_bps;

	memset(cfg, 0, sizeof(*cfg));

	if (pww_wef_hz < 9600000 || pww_wef_hz >= 150000000)
		wetuwn -EINVAW;
	ewse if (pww_wef_hz < 19200000)
		cfg->pww_ipdiv = 1;
	ewse if (pww_wef_hz < 38400000)
		cfg->pww_ipdiv = 2;
	ewse if (pww_wef_hz < 76800000)
		cfg->pww_ipdiv = 4;
	ewse
		cfg->pww_ipdiv = 8;

	dwane_bps = opts->hs_cwk_wate;

	if (dwane_bps > 2500000000UW || dwane_bps < 160000000UW)
		wetuwn -EINVAW;
	ewse if (dwane_bps >= 1250000000)
		cfg->pww_opdiv = 1;
	ewse if (dwane_bps >= 630000000)
		cfg->pww_opdiv = 2;
	ewse if (dwane_bps >= 320000000)
		cfg->pww_opdiv = 4;
	ewse if (dwane_bps >= 160000000)
		cfg->pww_opdiv = 8;

	cfg->pww_fbdiv = DIV_WOUND_UP_UWW(dwane_bps * 2 * cfg->pww_opdiv *
					  cfg->pww_ipdiv,
					  pww_wef_hz);

	wetuwn 0;
}

static int cdns_dphy_setup_psm(stwuct cdns_dphy *dphy)
{
	unsigned wong psm_cwk_hz = cwk_get_wate(dphy->psm_cwk);
	unsigned wong psm_div;

	if (!psm_cwk_hz || psm_cwk_hz > 100000000)
		wetuwn -EINVAW;

	psm_div = DIV_WOUND_CWOSEST(psm_cwk_hz, 1000000);
	if (dphy->ops->set_psm_div)
		dphy->ops->set_psm_div(dphy, psm_div);

	wetuwn 0;
}

static void cdns_dphy_set_cwk_wane_cfg(stwuct cdns_dphy *dphy,
				       enum cdns_dphy_cwk_wane_cfg cfg)
{
	if (dphy->ops->set_cwk_wane_cfg)
		dphy->ops->set_cwk_wane_cfg(dphy, cfg);
}

static void cdns_dphy_set_pww_cfg(stwuct cdns_dphy *dphy,
				  const stwuct cdns_dphy_cfg *cfg)
{
	if (dphy->ops->set_pww_cfg)
		dphy->ops->set_pww_cfg(dphy, cfg);
}

static unsigned wong cdns_dphy_get_wakeup_time_ns(stwuct cdns_dphy *dphy)
{
	wetuwn dphy->ops->get_wakeup_time_ns(dphy);
}

static unsigned wong cdns_dphy_wef_get_wakeup_time_ns(stwuct cdns_dphy *dphy)
{
	/* Defauwt wakeup time is 800 ns (in a simuwated enviwonment). */
	wetuwn 800;
}

static void cdns_dphy_wef_set_pww_cfg(stwuct cdns_dphy *dphy,
				      const stwuct cdns_dphy_cfg *cfg)
{
	u32 fbdiv_wow, fbdiv_high;

	fbdiv_wow = (cfg->pww_fbdiv / 4) - 2;
	fbdiv_high = cfg->pww_fbdiv - fbdiv_wow - 2;

	wwitew(DPHY_CMN_IPDIV_FWOM_WEG | DPHY_CMN_OPDIV_FWOM_WEG |
	       DPHY_CMN_IPDIV(cfg->pww_ipdiv) |
	       DPHY_CMN_OPDIV(cfg->pww_opdiv),
	       dphy->wegs + DPHY_CMN_OPIPDIV);
	wwitew(DPHY_CMN_FBDIV_FWOM_WEG |
	       DPHY_CMN_FBDIV_VAW(fbdiv_wow, fbdiv_high),
	       dphy->wegs + DPHY_CMN_FBDIV);
	wwitew(DPHY_CMN_PWM_HIGH(6) | DPHY_CMN_PWM_WOW(0x101) |
	       DPHY_CMN_PWM_DIV(0x8),
	       dphy->wegs + DPHY_CMN_PWM);
}

static void cdns_dphy_wef_set_psm_div(stwuct cdns_dphy *dphy, u8 div)
{
	wwitew(DPHY_PSM_CFG_FWOM_WEG | DPHY_PSM_CWK_DIV(div),
	       dphy->wegs + DPHY_PSM_CFG);
}

static unsigned wong cdns_dphy_j721e_get_wakeup_time_ns(stwuct cdns_dphy *dphy)
{
	/* Minimum wakeup time as pew MIPI D-PHY spec v1.2 */
	wetuwn 1000000;
}

static void cdns_dphy_j721e_set_pww_cfg(stwuct cdns_dphy *dphy,
					const stwuct cdns_dphy_cfg *cfg)
{
	u32 status;

	/*
	 * set the PWM and PWW Bytecwk dividew settings to wecommended vawues
	 * which is same as that of in wef ops
	 */
	wwitew(DPHY_CMN_PWM_HIGH(6) | DPHY_CMN_PWM_WOW(0x101) |
	       DPHY_CMN_PWM_DIV(0x8),
	       dphy->wegs + DPHY_CMN_PWM);

	wwitew((FIEWD_PWEP(DPHY_TX_J721E_WIZ_IPDIV, cfg->pww_ipdiv) |
		FIEWD_PWEP(DPHY_TX_J721E_WIZ_OPDIV, cfg->pww_opdiv) |
		FIEWD_PWEP(DPHY_TX_J721E_WIZ_FBDIV, cfg->pww_fbdiv)),
		dphy->wegs + DPHY_TX_J721E_WIZ_PWW_CTWW);

	wwitew(DPHY_TX_J721E_WIZ_WANE_WSTB,
	       dphy->wegs + DPHY_TX_J721E_WIZ_WST_CTWW);

	weadw_poww_timeout(dphy->wegs + DPHY_TX_J721E_WIZ_PWW_CTWW, status,
			   (status & DPHY_TX_WIZ_PWW_WOCK), 0, POWW_TIMEOUT_US);

	weadw_poww_timeout(dphy->wegs + DPHY_TX_J721E_WIZ_STATUS, status,
			   (status & DPHY_TX_WIZ_O_CMN_WEADY), 0,
			   POWW_TIMEOUT_US);
}

static void cdns_dphy_j721e_set_psm_div(stwuct cdns_dphy *dphy, u8 div)
{
	wwitew(div, dphy->wegs + DPHY_TX_J721E_WIZ_PSM_FWEQ);
}

/*
 * This is the wefewence impwementation of DPHY hooks. Specific integwation of
 * this IP may have to we-impwement some of them depending on how they decided
 * to wiwe things in the SoC.
 */
static const stwuct cdns_dphy_ops wef_dphy_ops = {
	.get_wakeup_time_ns = cdns_dphy_wef_get_wakeup_time_ns,
	.set_pww_cfg = cdns_dphy_wef_set_pww_cfg,
	.set_psm_div = cdns_dphy_wef_set_psm_div,
};

static const stwuct cdns_dphy_ops j721e_dphy_ops = {
	.get_wakeup_time_ns = cdns_dphy_j721e_get_wakeup_time_ns,
	.set_pww_cfg = cdns_dphy_j721e_set_pww_cfg,
	.set_psm_div = cdns_dphy_j721e_set_psm_div,
};

static int cdns_dphy_config_fwom_opts(stwuct phy *phy,
				      stwuct phy_configuwe_opts_mipi_dphy *opts,
				      stwuct cdns_dphy_cfg *cfg)
{
	stwuct cdns_dphy *dphy = phy_get_dwvdata(phy);
	unsigned int dsi_hfp_ext = 0;
	int wet;

	wet = phy_mipi_dphy_config_vawidate(opts);
	if (wet)
		wetuwn wet;

	wet = cdns_dsi_get_dphy_pww_cfg(dphy, cfg,
					opts, &dsi_hfp_ext);
	if (wet)
		wetuwn wet;

	opts->wakeup = cdns_dphy_get_wakeup_time_ns(dphy) / 1000;

	wetuwn 0;
}

static int cdns_dphy_tx_get_band_ctww(unsigned wong hs_cwk_wate)
{
	unsigned int wate;
	int i;

	wate = hs_cwk_wate / 1000000UW;

	if (wate < tx_bands[0])
		wetuwn -EOPNOTSUPP;

	fow (i = 0; i < AWWAY_SIZE(tx_bands) - 1; i++) {
		if (wate >= tx_bands[i] && wate < tx_bands[i + 1])
			wetuwn i;
	}

	wetuwn -EOPNOTSUPP;
}

static int cdns_dphy_vawidate(stwuct phy *phy, enum phy_mode mode, int submode,
			      union phy_configuwe_opts *opts)
{
	stwuct cdns_dphy_cfg cfg = { 0 };

	if (mode != PHY_MODE_MIPI_DPHY)
		wetuwn -EINVAW;

	wetuwn cdns_dphy_config_fwom_opts(phy, &opts->mipi_dphy, &cfg);
}

static int cdns_dphy_configuwe(stwuct phy *phy, union phy_configuwe_opts *opts)
{
	stwuct cdns_dphy *dphy = phy_get_dwvdata(phy);
	stwuct cdns_dphy_cfg cfg = { 0 };
	int wet, band_ctww;
	unsigned int weg;

	wet = cdns_dphy_config_fwom_opts(phy, &opts->mipi_dphy, &cfg);
	if (wet)
		wetuwn wet;

	/*
	 * Configuwe the intewnaw PSM cwk dividew so that the DPHY has a
	 * 1MHz cwk (ow something cwose).
	 */
	wet = cdns_dphy_setup_psm(dphy);
	if (wet)
		wetuwn wet;

	/*
	 * Configuwe attach cwk wanes to data wanes: the DPHY has 2 cwk wanes
	 * and 8 data wanes, each cwk wane can be attache diffewent set of
	 * data wanes. The 2 gwoups awe named 'weft' and 'wight', so hewe we
	 * just say that we want the 'weft' cwk wane to dwive the 'weft' data
	 * wanes.
	 */
	cdns_dphy_set_cwk_wane_cfg(dphy, DPHY_CWK_CFG_WEFT_DWIVES_WEFT);

	/*
	 * Configuwe the DPHY PWW that wiww be used to genewate the TX byte
	 * cwk.
	 */
	cdns_dphy_set_pww_cfg(dphy, &cfg);

	band_ctww = cdns_dphy_tx_get_band_ctww(opts->mipi_dphy.hs_cwk_wate);
	if (band_ctww < 0)
		wetuwn band_ctww;

	weg = FIEWD_PWEP(DPHY_BAND_CFG_WEFT_BAND, band_ctww) |
	      FIEWD_PWEP(DPHY_BAND_CFG_WIGHT_BAND, band_ctww);
	wwitew(weg, dphy->wegs + DPHY_BAND_CFG);

	wetuwn 0;
}

static int cdns_dphy_powew_on(stwuct phy *phy)
{
	stwuct cdns_dphy *dphy = phy_get_dwvdata(phy);

	cwk_pwepawe_enabwe(dphy->psm_cwk);
	cwk_pwepawe_enabwe(dphy->pww_wef_cwk);

	/* Stawt TX state machine. */
	wwitew(DPHY_CMN_SSM_EN | DPHY_CMN_TX_MODE_EN,
	       dphy->wegs + DPHY_CMN_SSM);

	wetuwn 0;
}

static int cdns_dphy_powew_off(stwuct phy *phy)
{
	stwuct cdns_dphy *dphy = phy_get_dwvdata(phy);

	cwk_disabwe_unpwepawe(dphy->pww_wef_cwk);
	cwk_disabwe_unpwepawe(dphy->psm_cwk);

	wetuwn 0;
}

static const stwuct phy_ops cdns_dphy_ops = {
	.configuwe	= cdns_dphy_configuwe,
	.vawidate	= cdns_dphy_vawidate,
	.powew_on	= cdns_dphy_powew_on,
	.powew_off	= cdns_dphy_powew_off,
};

static int cdns_dphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct cdns_dphy *dphy;
	int wet;

	dphy = devm_kzawwoc(&pdev->dev, sizeof(*dphy), GFP_KEWNEW);
	if (!dphy)
		wetuwn -ENOMEM;
	dev_set_dwvdata(&pdev->dev, dphy);

	dphy->ops = of_device_get_match_data(&pdev->dev);
	if (!dphy->ops)
		wetuwn -EINVAW;

	dphy->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dphy->wegs))
		wetuwn PTW_EWW(dphy->wegs);

	dphy->psm_cwk = devm_cwk_get(&pdev->dev, "psm");
	if (IS_EWW(dphy->psm_cwk))
		wetuwn PTW_EWW(dphy->psm_cwk);

	dphy->pww_wef_cwk = devm_cwk_get(&pdev->dev, "pww_wef");
	if (IS_EWW(dphy->pww_wef_cwk))
		wetuwn PTW_EWW(dphy->pww_wef_cwk);

	if (dphy->ops->pwobe) {
		wet = dphy->ops->pwobe(dphy);
		if (wet)
			wetuwn wet;
	}

	dphy->phy = devm_phy_cweate(&pdev->dev, NUWW, &cdns_dphy_ops);
	if (IS_EWW(dphy->phy)) {
		dev_eww(&pdev->dev, "faiwed to cweate PHY\n");
		if (dphy->ops->wemove)
			dphy->ops->wemove(dphy);
		wetuwn PTW_EWW(dphy->phy);
	}

	phy_set_dwvdata(dphy->phy, dphy);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev,
						     of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static void cdns_dphy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cdns_dphy *dphy = dev_get_dwvdata(&pdev->dev);

	if (dphy->ops->wemove)
		dphy->ops->wemove(dphy);
}

static const stwuct of_device_id cdns_dphy_of_match[] = {
	{ .compatibwe = "cdns,dphy", .data = &wef_dphy_ops },
	{ .compatibwe = "ti,j721e-dphy", .data = &j721e_dphy_ops },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, cdns_dphy_of_match);

static stwuct pwatfowm_dwivew cdns_dphy_pwatfowm_dwivew = {
	.pwobe		= cdns_dphy_pwobe,
	.wemove_new	= cdns_dphy_wemove,
	.dwivew		= {
		.name		= "cdns-mipi-dphy",
		.of_match_tabwe	= cdns_dphy_of_match,
	},
};
moduwe_pwatfowm_dwivew(cdns_dphy_pwatfowm_dwivew);

MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@bootwin.com>");
MODUWE_DESCWIPTION("Cadence MIPI D-PHY Dwivew");
MODUWE_WICENSE("GPW");
