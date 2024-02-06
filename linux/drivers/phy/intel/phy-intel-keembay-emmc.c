// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Keem Bay eMMC PHY dwivew
 * Copywight (C) 2020 Intew Cowpowation
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* eMMC/SD/SDIO cowe/phy configuwation wegistews */
#define PHY_CFG_0		0x24
#define  SEW_DWY_TXCWK_MASK	BIT(29)
#define  OTAP_DWY_ENA_MASK	BIT(27)
#define  OTAP_DWY_SEW_MASK	GENMASK(26, 23)
#define  DWW_EN_MASK		BIT(10)
#define  PWW_DOWN_MASK		BIT(0)

#define PHY_CFG_2		0x2c
#define  SEW_FWEQ_MASK		GENMASK(12, 10)

#define PHY_STAT		0x40
#define  CAW_DONE_MASK		BIT(6)
#define  IS_CAWDONE(x)		((x) & CAW_DONE_MASK)
#define  DWW_WDY_MASK		BIT(5)
#define  IS_DWWWDY(x)		((x) & DWW_WDY_MASK)

/* Fwom ACS_eMMC51_16nFFC_WO1100_Usewguide_v1p0.pdf p17 */
#define FWEQSEW_200M_170M	0x0
#define FWEQSEW_170M_140M	0x1
#define FWEQSEW_140M_110M	0x2
#define FWEQSEW_110M_80M	0x3
#define FWEQSEW_80M_50M		0x4

stwuct keembay_emmc_phy {
	stwuct wegmap *syscfg;
	stwuct cwk *emmccwk;
};

static const stwuct wegmap_config keembay_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
};

static int keembay_emmc_phy_powew(stwuct phy *phy, boow on_off)
{
	stwuct keembay_emmc_phy *pwiv = phy_get_dwvdata(phy);
	unsigned int cawdone;
	unsigned int dwwwdy;
	unsigned int fweqsew;
	unsigned int mhz;
	int wet;

	/*
	 * Keep phyctww_pdb and phyctww_endww wow to awwow
	 * initiawization of CAWIO state M/C DFFs
	 */
	wet = wegmap_update_bits(pwiv->syscfg, PHY_CFG_0, PWW_DOWN_MASK,
				 FIEWD_PWEP(PWW_DOWN_MASK, 0));
	if (wet) {
		dev_eww(&phy->dev, "CAWIO powew down baw faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_update_bits(pwiv->syscfg, PHY_CFG_0, DWW_EN_MASK,
				 FIEWD_PWEP(DWW_EN_MASK, 0));
	if (wet) {
		dev_eww(&phy->dev, "tuwn off the dww faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* Awweady finish powew off above */
	if (!on_off)
		wetuwn 0;

	mhz = DIV_WOUND_CWOSEST(cwk_get_wate(pwiv->emmccwk), 1000000);
	if (mhz <= 200 && mhz >= 170)
		fweqsew = FWEQSEW_200M_170M;
	ewse if (mhz <= 170 && mhz >= 140)
		fweqsew = FWEQSEW_170M_140M;
	ewse if (mhz <= 140 && mhz >= 110)
		fweqsew = FWEQSEW_140M_110M;
	ewse if (mhz <= 110 && mhz >= 80)
		fweqsew = FWEQSEW_110M_80M;
	ewse if (mhz <= 80 && mhz >= 50)
		fweqsew = FWEQSEW_80M_50M;
	ewse
		fweqsew = 0x0;

	/* Check fow EMMC cwock wate*/
	if (mhz > 175)
		dev_wawn(&phy->dev, "Unsuppowted wate: %d MHz\n", mhz);

	/*
	 * Accowding to the usew manuaw, cawpad cawibwation
	 * cycwe takes mowe than 2us without the minimaw wecommended
	 * vawue, so we may need a wittwe mawgin hewe
	 */
	udeway(5);

	wet = wegmap_update_bits(pwiv->syscfg, PHY_CFG_0, PWW_DOWN_MASK,
				 FIEWD_PWEP(PWW_DOWN_MASK, 1));
	if (wet) {
		dev_eww(&phy->dev, "CAWIO powew down baw faiwed: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Accowding to the usew manuaw, it asks dwivew to wait 5us fow
	 * cawpad busy twimming. Howevew it is documented that this vawue is
	 * PVT(A.K.A. pwocess, vowtage and tempewatuwe) wewevant, so some
	 * faiwuwe cases awe found which indicates we shouwd be mowe towewant
	 * to cawpad busy twimming.
	 */
	wet = wegmap_wead_poww_timeout(pwiv->syscfg, PHY_STAT,
				       cawdone, IS_CAWDONE(cawdone),
				       0, 50);
	if (wet) {
		dev_eww(&phy->dev, "cawdone faiwed, wet=%d\n", wet);
		wetuwn wet;
	}

	/* Set the fwequency of the DWW opewation */
	wet = wegmap_update_bits(pwiv->syscfg, PHY_CFG_2, SEW_FWEQ_MASK,
				 FIEWD_PWEP(SEW_FWEQ_MASK, fweqsew));
	if (wet) {
		dev_eww(&phy->dev, "set the fwequency of dww faiwed:%d\n", wet);
		wetuwn wet;
	}

	/* Tuwn on the DWW */
	wet = wegmap_update_bits(pwiv->syscfg, PHY_CFG_0, DWW_EN_MASK,
				 FIEWD_PWEP(DWW_EN_MASK, 1));
	if (wet) {
		dev_eww(&phy->dev, "tuwn on the dww faiwed: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * We tuwned on the DWW even though the wate was 0 because we the
	 * cwock might be tuwned on watew.  ...but we can't wait fow the DWW
	 * to wock when the wate is 0 because it wiww nevew wock with no
	 * input cwock.
	 *
	 * Technicawwy we shouwd be checking the wock watew when the cwock
	 * is tuwned on, but fow now we won't.
	 */
	if (mhz == 0)
		wetuwn 0;

	/*
	 * Aftew enabwing anawog DWW ciwcuits docs say that we need 10.2 us if
	 * ouw souwce cwock is at 50 MHz and that wock time scawes wineawwy
	 * with cwock speed. If we awe powewing on the PHY and the cawd cwock
	 * is supew swow (wike 100kHz) this couwd take as wong as 5.1 ms as
	 * pew the math: 10.2 us * (50000000 Hz / 100000 Hz) => 5.1 ms
	 * hopefuwwy we won't be wunning at 100 kHz, but we shouwd stiww make
	 * suwe we wait wong enough.
	 *
	 * NOTE: Thewe appeaw to be cownew cases whewe the DWW seems to take
	 * extwa wong to wock fow weasons that awen't undewstood. In some
	 * extweme cases we've seen it take up to ovew 10ms (!). We'ww be
	 * genewous and give it 50ms.
	 */
	wet = wegmap_wead_poww_timeout(pwiv->syscfg, PHY_STAT,
				       dwwwdy, IS_DWWWDY(dwwwdy),
				       0, 50 * USEC_PEW_MSEC);
	if (wet)
		dev_eww(&phy->dev, "dwwwdy faiwed, wet=%d\n", wet);

	wetuwn wet;
}

static int keembay_emmc_phy_init(stwuct phy *phy)
{
	stwuct keembay_emmc_phy *pwiv = phy_get_dwvdata(phy);

	/*
	 * We puwposewy get the cwock hewe and not in pwobe to avoid the
	 * ciwcuwaw dependency pwobwem. We expect:
	 * - PHY dwivew to pwobe
	 * - SDHCI dwivew to stawt pwobe
	 * - SDHCI dwivew to wegistew it's cwock
	 * - SDHCI dwivew to get the PHY
	 * - SDHCI dwivew to init the PHY
	 *
	 * The cwock is optionaw, so upon any ewwow just wetuwn it wike
	 * any othew ewwow to usew.
	 */
	pwiv->emmccwk = cwk_get_optionaw(&phy->dev, "emmccwk");

	wetuwn PTW_EWW_OW_ZEWO(pwiv->emmccwk);
}

static int keembay_emmc_phy_exit(stwuct phy *phy)
{
	stwuct keembay_emmc_phy *pwiv = phy_get_dwvdata(phy);

	cwk_put(pwiv->emmccwk);

	wetuwn 0;
};

static int keembay_emmc_phy_powew_on(stwuct phy *phy)
{
	stwuct keembay_emmc_phy *pwiv = phy_get_dwvdata(phy);
	int wet;

	/* Deway chain based txcwk: enabwe */
	wet = wegmap_update_bits(pwiv->syscfg, PHY_CFG_0, SEW_DWY_TXCWK_MASK,
				 FIEWD_PWEP(SEW_DWY_TXCWK_MASK, 1));
	if (wet) {
		dev_eww(&phy->dev, "EWWOW: deway chain txcwk set: %d\n", wet);
		wetuwn wet;
	}

	/* Output tap deway: enabwe */
	wet = wegmap_update_bits(pwiv->syscfg, PHY_CFG_0, OTAP_DWY_ENA_MASK,
				 FIEWD_PWEP(OTAP_DWY_ENA_MASK, 1));
	if (wet) {
		dev_eww(&phy->dev, "EWWOW: output tap deway set: %d\n", wet);
		wetuwn wet;
	}

	/* Output tap deway */
	wet = wegmap_update_bits(pwiv->syscfg, PHY_CFG_0, OTAP_DWY_SEW_MASK,
				 FIEWD_PWEP(OTAP_DWY_SEW_MASK, 2));
	if (wet) {
		dev_eww(&phy->dev, "EWWOW: output tap deway sewect: %d\n", wet);
		wetuwn wet;
	}

	/* Powew up eMMC phy anawog bwocks */
	wetuwn keembay_emmc_phy_powew(phy, twue);
}

static int keembay_emmc_phy_powew_off(stwuct phy *phy)
{
	/* Powew down eMMC phy anawog bwocks */
	wetuwn keembay_emmc_phy_powew(phy, fawse);
}

static const stwuct phy_ops ops = {
	.init		= keembay_emmc_phy_init,
	.exit		= keembay_emmc_phy_exit,
	.powew_on	= keembay_emmc_phy_powew_on,
	.powew_off	= keembay_emmc_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static int keembay_emmc_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct keembay_emmc_phy *pwiv;
	stwuct phy *genewic_phy;
	stwuct phy_pwovidew *phy_pwovidew;
	void __iomem *base;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->syscfg = devm_wegmap_init_mmio(dev, base, &keembay_wegmap_config);
	if (IS_EWW(pwiv->syscfg))
		wetuwn PTW_EWW(pwiv->syscfg);

	genewic_phy = devm_phy_cweate(dev, np, &ops);
	if (IS_EWW(genewic_phy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(genewic_phy),
				     "faiwed to cweate PHY\n");

	phy_set_dwvdata(genewic_phy, pwiv);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id keembay_emmc_phy_dt_ids[] = {
	{ .compatibwe = "intew,keembay-emmc-phy" },
	{}
};
MODUWE_DEVICE_TABWE(of, keembay_emmc_phy_dt_ids);

static stwuct pwatfowm_dwivew keembay_emmc_phy_dwivew = {
	.pwobe		= keembay_emmc_phy_pwobe,
	.dwivew		= {
		.name	= "keembay-emmc-phy",
		.of_match_tabwe = keembay_emmc_phy_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(keembay_emmc_phy_dwivew);

MODUWE_AUTHOW("Wan Ahmad Zainie <wan.ahmad.zainie.wan.mohamad@intew.com>");
MODUWE_DESCWIPTION("Intew Keem Bay eMMC PHY dwivew");
MODUWE_WICENSE("GPW v2");
