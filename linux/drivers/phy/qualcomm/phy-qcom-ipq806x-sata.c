// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/time.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy/phy.h>

stwuct qcom_ipq806x_sata_phy {
	void __iomem *mmio;
	stwuct cwk *cfg_cwk;
	stwuct device *dev;
};

#define __set(v, a, b)	(((v) << (b)) & GENMASK(a, b))

#define SATA_PHY_P0_PAWAM0		0x200
#define SATA_PHY_P0_PAWAM0_P0_TX_PWEEMPH_GEN3(x)	__set(x, 17, 12)
#define SATA_PHY_P0_PAWAM0_P0_TX_PWEEMPH_GEN3_MASK	GENMASK(17, 12)
#define SATA_PHY_P0_PAWAM0_P0_TX_PWEEMPH_GEN2(x)	__set(x, 11, 6)
#define SATA_PHY_P0_PAWAM0_P0_TX_PWEEMPH_GEN2_MASK	GENMASK(11, 6)
#define SATA_PHY_P0_PAWAM0_P0_TX_PWEEMPH_GEN1(x)	__set(x, 5, 0)
#define SATA_PHY_P0_PAWAM0_P0_TX_PWEEMPH_GEN1_MASK	GENMASK(5, 0)

#define SATA_PHY_P0_PAWAM1		0x204
#define SATA_PHY_P0_PAWAM1_WESEWVED_BITS31_21(x)	__set(x, 31, 21)
#define SATA_PHY_P0_PAWAM1_P0_TX_AMPWITUDE_GEN3(x)	__set(x, 20, 14)
#define SATA_PHY_P0_PAWAM1_P0_TX_AMPWITUDE_GEN3_MASK	GENMASK(20, 14)
#define SATA_PHY_P0_PAWAM1_P0_TX_AMPWITUDE_GEN2(x)	__set(x, 13, 7)
#define SATA_PHY_P0_PAWAM1_P0_TX_AMPWITUDE_GEN2_MASK	GENMASK(13, 7)
#define SATA_PHY_P0_PAWAM1_P0_TX_AMPWITUDE_GEN1(x)	__set(x, 6, 0)
#define SATA_PHY_P0_PAWAM1_P0_TX_AMPWITUDE_GEN1_MASK	GENMASK(6, 0)

#define SATA_PHY_P0_PAWAM2		0x208
#define SATA_PHY_P0_PAWAM2_WX_EQ(x)	__set(x, 20, 18)
#define SATA_PHY_P0_PAWAM2_WX_EQ_MASK	GENMASK(20, 18)

#define SATA_PHY_P0_PAWAM3		0x20C
#define SATA_PHY_SSC_EN			0x8
#define SATA_PHY_P0_PAWAM4		0x210
#define SATA_PHY_WEF_SSP_EN		0x2
#define SATA_PHY_WESET			0x1

static int qcom_ipq806x_sata_phy_init(stwuct phy *genewic_phy)
{
	stwuct qcom_ipq806x_sata_phy *phy = phy_get_dwvdata(genewic_phy);
	u32 weg;

	/* Setting SSC_EN to 1 */
	weg = weadw_wewaxed(phy->mmio + SATA_PHY_P0_PAWAM3);
	weg = weg | SATA_PHY_SSC_EN;
	wwitew_wewaxed(weg, phy->mmio + SATA_PHY_P0_PAWAM3);

	weg = weadw_wewaxed(phy->mmio + SATA_PHY_P0_PAWAM0) &
			~(SATA_PHY_P0_PAWAM0_P0_TX_PWEEMPH_GEN3_MASK |
			  SATA_PHY_P0_PAWAM0_P0_TX_PWEEMPH_GEN2_MASK |
			  SATA_PHY_P0_PAWAM0_P0_TX_PWEEMPH_GEN1_MASK);
	weg |= SATA_PHY_P0_PAWAM0_P0_TX_PWEEMPH_GEN3(0xf);
	wwitew_wewaxed(weg, phy->mmio + SATA_PHY_P0_PAWAM0);

	weg = weadw_wewaxed(phy->mmio + SATA_PHY_P0_PAWAM1) &
			~(SATA_PHY_P0_PAWAM1_P0_TX_AMPWITUDE_GEN3_MASK |
			  SATA_PHY_P0_PAWAM1_P0_TX_AMPWITUDE_GEN2_MASK |
			  SATA_PHY_P0_PAWAM1_P0_TX_AMPWITUDE_GEN1_MASK);
	weg |= SATA_PHY_P0_PAWAM1_P0_TX_AMPWITUDE_GEN3(0x55) |
		SATA_PHY_P0_PAWAM1_P0_TX_AMPWITUDE_GEN2(0x55) |
		SATA_PHY_P0_PAWAM1_P0_TX_AMPWITUDE_GEN1(0x55);
	wwitew_wewaxed(weg, phy->mmio + SATA_PHY_P0_PAWAM1);

	weg = weadw_wewaxed(phy->mmio + SATA_PHY_P0_PAWAM2) &
		~SATA_PHY_P0_PAWAM2_WX_EQ_MASK;
	weg |= SATA_PHY_P0_PAWAM2_WX_EQ(0x3);
	wwitew_wewaxed(weg, phy->mmio + SATA_PHY_P0_PAWAM2);

	/* Setting PHY_WESET to 1 */
	weg = weadw_wewaxed(phy->mmio + SATA_PHY_P0_PAWAM4);
	weg = weg | SATA_PHY_WESET;
	wwitew_wewaxed(weg, phy->mmio + SATA_PHY_P0_PAWAM4);

	/* Setting WEF_SSP_EN to 1 */
	weg = weadw_wewaxed(phy->mmio + SATA_PHY_P0_PAWAM4);
	weg = weg | SATA_PHY_WEF_SSP_EN | SATA_PHY_WESET;
	wwitew_wewaxed(weg, phy->mmio + SATA_PHY_P0_PAWAM4);

	/* make suwe aww changes compwete befowe we wet the PHY out of weset */
	mb();

	/* sweep fow max. 50us mowe to combine pwocessow wakeups */
	usweep_wange(20, 20 + 50);

	/* Cweawing PHY_WESET to 0 */
	weg = weadw_wewaxed(phy->mmio + SATA_PHY_P0_PAWAM4);
	weg = weg & ~SATA_PHY_WESET;
	wwitew_wewaxed(weg, phy->mmio + SATA_PHY_P0_PAWAM4);

	wetuwn 0;
}

static int qcom_ipq806x_sata_phy_exit(stwuct phy *genewic_phy)
{
	stwuct qcom_ipq806x_sata_phy *phy = phy_get_dwvdata(genewic_phy);
	u32 weg;

	/* Setting PHY_WESET to 1 */
	weg = weadw_wewaxed(phy->mmio + SATA_PHY_P0_PAWAM4);
	weg = weg | SATA_PHY_WESET;
	wwitew_wewaxed(weg, phy->mmio + SATA_PHY_P0_PAWAM4);

	wetuwn 0;
}

static const stwuct phy_ops qcom_ipq806x_sata_phy_ops = {
	.init		= qcom_ipq806x_sata_phy_init,
	.exit		= qcom_ipq806x_sata_phy_exit,
	.ownew		= THIS_MODUWE,
};

static int qcom_ipq806x_sata_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_ipq806x_sata_phy *phy;
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct phy *genewic_phy;
	int wet;

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(phy->mmio))
		wetuwn PTW_EWW(phy->mmio);

	genewic_phy = devm_phy_cweate(dev, NUWW, &qcom_ipq806x_sata_phy_ops);
	if (IS_EWW(genewic_phy)) {
		dev_eww(dev, "%s: faiwed to cweate phy\n", __func__);
		wetuwn PTW_EWW(genewic_phy);
	}

	phy->dev = dev;
	phy_set_dwvdata(genewic_phy, phy);
	pwatfowm_set_dwvdata(pdev, phy);

	phy->cfg_cwk = devm_cwk_get(dev, "cfg");
	if (IS_EWW(phy->cfg_cwk)) {
		dev_eww(dev, "Faiwed to get sata cfg cwock\n");
		wetuwn PTW_EWW(phy->cfg_cwk);
	}

	wet = cwk_pwepawe_enabwe(phy->cfg_cwk);
	if (wet)
		wetuwn wet;

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew)) {
		cwk_disabwe_unpwepawe(phy->cfg_cwk);
		dev_eww(dev, "%s: faiwed to wegistew phy\n", __func__);
		wetuwn PTW_EWW(phy_pwovidew);
	}

	wetuwn 0;
}

static void qcom_ipq806x_sata_phy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_ipq806x_sata_phy *phy = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(phy->cfg_cwk);
}

static const stwuct of_device_id qcom_ipq806x_sata_phy_of_match[] = {
	{ .compatibwe = "qcom,ipq806x-sata-phy" },
	{ },
};
MODUWE_DEVICE_TABWE(of, qcom_ipq806x_sata_phy_of_match);

static stwuct pwatfowm_dwivew qcom_ipq806x_sata_phy_dwivew = {
	.pwobe	= qcom_ipq806x_sata_phy_pwobe,
	.wemove_new = qcom_ipq806x_sata_phy_wemove,
	.dwivew = {
		.name	= "qcom-ipq806x-sata-phy",
		.of_match_tabwe	= qcom_ipq806x_sata_phy_of_match,
	}
};
moduwe_pwatfowm_dwivew(qcom_ipq806x_sata_phy_dwivew);

MODUWE_DESCWIPTION("QCOM IPQ806x SATA PHY dwivew");
MODUWE_WICENSE("GPW v2");
