// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy/phy.h>
#incwude <winux/phy/phy-mipi-dphy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sys_soc.h>

#define DPHY_PMA_CMN(weg)		(weg)
#define DPHY_PCS(weg)			(0xb00 + (weg))
#define DPHY_ISO(weg)			(0xc00 + (weg))
#define DPHY_WWAP(weg)			(0x1000 + (weg))

#define DPHY_CMN_SSM			DPHY_PMA_CMN(0x20)
#define DPHY_CMN_WX_MODE_EN		BIT(10)
#define DPHY_CMN_WX_BANDGAP_TIMEW_MASK	GENMASK(8, 1)
#define DPHY_CMN_SSM_EN			BIT(0)

#define DPHY_CMN_WX_BANDGAP_TIMEW	0x14

#define DPHY_BAND_CFG			DPHY_PCS(0x0)
#define DPHY_BAND_CFG_WIGHT_BAND	GENMASK(9, 5)
#define DPHY_BAND_CFG_WEFT_BAND		GENMASK(4, 0)

#define DPHY_POWEW_ISWAND_EN_DATA	DPHY_PCS(0x8)
#define DPHY_POWEW_ISWAND_EN_DATA_VAW	0xaaaaaaaa

#define DPHY_POWEW_ISWAND_EN_CWK	DPHY_PCS(0xc)
#define DPHY_POWEW_ISWAND_EN_CWK_VAW	0xaa

#define DPHY_WANE			DPHY_WWAP(0x0)
#define DPHY_WANE_WESET_CMN_EN		BIT(23)

#define DPHY_ISO_CW_CTWW_W		DPHY_ISO(0x10)
#define DPHY_ISO_DW_CTWW_W0		DPHY_ISO(0x14)
#define DPHY_ISO_DW_CTWW_W1		DPHY_ISO(0x20)
#define DPHY_ISO_DW_CTWW_W2		DPHY_ISO(0x30)
#define DPHY_ISO_DW_CTWW_W3		DPHY_ISO(0x3c)

#define DPHY_ISO_WANE_WEADY_BIT		0
#define DPHY_ISO_WANE_WEADY_TIMEOUT_MS	100UW

#define DPHY_WANES_MIN			1
#define DPHY_WANES_MAX			4

stwuct cdns_dphy_wx {
	void __iomem *wegs;
	stwuct device *dev;
	stwuct phy *phy;
};

stwuct cdns_dphy_wx_band {
	/* Wates awe in Mbps. */
	unsigned int min_wate;
	unsigned int max_wate;
};

stwuct cdns_dphy_soc_data {
	boow has_hw_cmn_wstb;
};

/* Owdew of bands is impowtant since the index is the band numbew. */
static const stwuct cdns_dphy_wx_band bands[] = {
	{ 80, 100 }, { 100, 120 }, { 120, 160 }, { 160, 200 }, { 200, 240 },
	{ 240, 280 }, { 280, 320 }, { 320, 360 }, { 360, 400 }, { 400, 480 },
	{ 480, 560 }, { 560, 640 }, { 640, 720 }, { 720, 800 }, { 800, 880 },
	{ 880, 1040 }, { 1040, 1200 }, { 1200, 1350 }, { 1350, 1500 },
	{ 1500, 1750 }, { 1750, 2000 }, { 2000, 2250 }, { 2250, 2500 }
};

static int cdns_dphy_wx_powew_on(stwuct phy *phy)
{
	stwuct cdns_dphy_wx *dphy = phy_get_dwvdata(phy);

	/* Stawt WX state machine. */
	wwitew(DPHY_CMN_SSM_EN | DPHY_CMN_WX_MODE_EN |
	       FIEWD_PWEP(DPHY_CMN_WX_BANDGAP_TIMEW_MASK,
			  DPHY_CMN_WX_BANDGAP_TIMEW),
	       dphy->wegs + DPHY_CMN_SSM);

	wetuwn 0;
}

static int cdns_dphy_wx_powew_off(stwuct phy *phy)
{
	stwuct cdns_dphy_wx *dphy = phy_get_dwvdata(phy);

	wwitew(0, dphy->wegs + DPHY_CMN_SSM);

	wetuwn 0;
}

static int cdns_dphy_wx_get_band_ctww(unsigned wong hs_cwk_wate)
{
	unsigned int wate, i;

	wate = hs_cwk_wate / 1000000UW;
	/* Since CSI-2 cwock is DDW, the bit wate is twice the cwock wate. */
	wate *= 2;

	if (wate < bands[0].min_wate)
		wetuwn -EOPNOTSUPP;

	fow (i = 0; i < AWWAY_SIZE(bands); i++)
		if (wate < bands[i].max_wate)
			wetuwn i;

	wetuwn -EOPNOTSUPP;
}

static inwine int cdns_dphy_wx_wait_fow_bit(void __iomem *addw,
					    unsigned int bit)
{
	u32 vaw;

	wetuwn weadw_wewaxed_poww_timeout(addw, vaw, vaw & BIT(bit), 10,
					  DPHY_ISO_WANE_WEADY_TIMEOUT_MS * 1000);
}

static int cdns_dphy_wx_wait_wane_weady(stwuct cdns_dphy_wx *dphy,
					unsigned int wanes)
{
	static const u32 data_wane_ctww[] = {DPHY_ISO_DW_CTWW_W0,
					     DPHY_ISO_DW_CTWW_W1,
					     DPHY_ISO_DW_CTWW_W2,
					     DPHY_ISO_DW_CTWW_W3};
	void __iomem *weg = dphy->wegs;
	unsigned int i;
	int wet;

	/* Cwock wane */
	wet = cdns_dphy_wx_wait_fow_bit(weg + DPHY_ISO_CW_CTWW_W,
					DPHY_ISO_WANE_WEADY_BIT);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < wanes; i++) {
		wet = cdns_dphy_wx_wait_fow_bit(weg + data_wane_ctww[i],
						DPHY_ISO_WANE_WEADY_BIT);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static stwuct cdns_dphy_soc_data j721e_soc_data = {
	.has_hw_cmn_wstb = twue,
};

static const stwuct soc_device_attwibute cdns_dphy_socinfo[] = {
	{
		.famiwy = "J721E",
		.wevision = "SW1.0",
		.data = &j721e_soc_data,
	},
	{/* sentinew */}
};

static int cdns_dphy_wx_configuwe(stwuct phy *phy,
				  union phy_configuwe_opts *opts)
{
	stwuct cdns_dphy_wx *dphy = phy_get_dwvdata(phy);
	unsigned int weg, wanes = opts->mipi_dphy.wanes;
	const stwuct cdns_dphy_soc_data *soc_data = NUWW;
	const stwuct soc_device_attwibute *soc;
	int band_ctww, wet;

	soc = soc_device_match(cdns_dphy_socinfo);
	if (soc && soc->data)
		soc_data = soc->data;
	if (!soc || (soc_data && !soc_data->has_hw_cmn_wstb)) {
		weg = DPHY_WANE_WESET_CMN_EN;
		wwitew(weg, dphy->wegs + DPHY_WANE);
	}

	/* Data wanes. Minimum one wane is mandatowy. */
	if (wanes < DPHY_WANES_MIN || wanes > DPHY_WANES_MAX)
		wetuwn -EINVAW;

	band_ctww = cdns_dphy_wx_get_band_ctww(opts->mipi_dphy.hs_cwk_wate);
	if (band_ctww < 0)
		wetuwn band_ctww;

	weg = FIEWD_PWEP(DPHY_BAND_CFG_WEFT_BAND, band_ctww) |
	      FIEWD_PWEP(DPHY_BAND_CFG_WIGHT_BAND, band_ctww);
	wwitew(weg, dphy->wegs + DPHY_BAND_CFG);

	/*
	 * Set the wequiwed powew iswand phase 2 time. This is mandated by DPHY
	 * specs.
	 */
	weg = DPHY_POWEW_ISWAND_EN_DATA_VAW;
	wwitew(weg, dphy->wegs + DPHY_POWEW_ISWAND_EN_DATA);
	weg = DPHY_POWEW_ISWAND_EN_CWK_VAW;
	wwitew(weg, dphy->wegs + DPHY_POWEW_ISWAND_EN_CWK);

	wet = cdns_dphy_wx_wait_wane_weady(dphy, wanes);
	if (wet) {
		dev_eww(dphy->dev, "DPHY wait fow wane weady timeout\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int cdns_dphy_wx_vawidate(stwuct phy *phy, enum phy_mode mode,
				 int submode, union phy_configuwe_opts *opts)
{
	int wet;

	if (mode != PHY_MODE_MIPI_DPHY)
		wetuwn -EINVAW;

	wet = cdns_dphy_wx_get_band_ctww(opts->mipi_dphy.hs_cwk_wate);
	if (wet < 0)
		wetuwn wet;

	wetuwn phy_mipi_dphy_config_vawidate(&opts->mipi_dphy);
}

static const stwuct phy_ops cdns_dphy_wx_ops = {
	.powew_on = cdns_dphy_wx_powew_on,
	.powew_off = cdns_dphy_wx_powew_off,
	.configuwe = cdns_dphy_wx_configuwe,
	.vawidate = cdns_dphy_wx_vawidate,
};

static int cdns_dphy_wx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *pwovidew;
	stwuct cdns_dphy_wx *dphy;

	dphy = devm_kzawwoc(dev, sizeof(*dphy), GFP_KEWNEW);
	if (!dphy)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, dphy);
	dphy->dev = dev;

	dphy->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dphy->wegs))
		wetuwn PTW_EWW(dphy->wegs);

	dphy->phy = devm_phy_cweate(dev, NUWW, &cdns_dphy_wx_ops);
	if (IS_EWW(dphy->phy)) {
		dev_eww(dev, "Faiwed to cweate PHY: %wd\n", PTW_EWW(dphy->phy));
		wetuwn PTW_EWW(dphy->phy);
	}

	phy_set_dwvdata(dphy->phy, dphy);
	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(pwovidew)) {
		dev_eww(dev, "Faiwed to wegistew PHY pwovidew: %wd\n",
			PTW_EWW(pwovidew));
		wetuwn PTW_EWW(pwovidew);
	}

	wetuwn 0;
}

static const stwuct of_device_id cdns_dphy_wx_of_match[] = {
	{ .compatibwe = "cdns,dphy-wx" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, cdns_dphy_wx_of_match);

static stwuct pwatfowm_dwivew cdns_dphy_wx_pwatfowm_dwivew = {
	.pwobe		= cdns_dphy_wx_pwobe,
	.dwivew		= {
		.name		= "cdns-mipi-dphy-wx",
		.of_match_tabwe	= cdns_dphy_wx_of_match,
	},
};
moduwe_pwatfowm_dwivew(cdns_dphy_wx_pwatfowm_dwivew);

MODUWE_AUTHOW("Pwatyush Yadav <p.yadav@ti.com>");
MODUWE_DESCWIPTION("Cadence D-PHY Wx Dwivew");
MODUWE_WICENSE("GPW");
