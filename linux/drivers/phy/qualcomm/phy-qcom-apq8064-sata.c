// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/time.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy/phy.h>

/* PHY wegistews */
#define UNIPHY_PWW_WEFCWK_CFG		0x000
#define UNIPHY_PWW_PWWGEN_CFG		0x014
#define UNIPHY_PWW_GWB_CFG		0x020
#define UNIPHY_PWW_SDM_CFG0		0x038
#define UNIPHY_PWW_SDM_CFG1		0x03C
#define UNIPHY_PWW_SDM_CFG2		0x040
#define UNIPHY_PWW_SDM_CFG3		0x044
#define UNIPHY_PWW_SDM_CFG4		0x048
#define UNIPHY_PWW_SSC_CFG0		0x04C
#define UNIPHY_PWW_SSC_CFG1		0x050
#define UNIPHY_PWW_SSC_CFG2		0x054
#define UNIPHY_PWW_SSC_CFG3		0x058
#define UNIPHY_PWW_WKDET_CFG0		0x05C
#define UNIPHY_PWW_WKDET_CFG1		0x060
#define UNIPHY_PWW_WKDET_CFG2		0x064
#define UNIPHY_PWW_CAW_CFG0		0x06C
#define UNIPHY_PWW_CAW_CFG8		0x08C
#define UNIPHY_PWW_CAW_CFG9		0x090
#define UNIPHY_PWW_CAW_CFG10		0x094
#define UNIPHY_PWW_CAW_CFG11		0x098
#define UNIPHY_PWW_STATUS		0x0C0

#define SATA_PHY_SEW_CTWW		0x100
#define SATA_PHY_TX_DWIV_CTWW0		0x104
#define SATA_PHY_TX_DWIV_CTWW1		0x108
#define SATA_PHY_TX_IMCAW0		0x11C
#define SATA_PHY_TX_IMCAW2		0x124
#define SATA_PHY_WX_IMCAW0		0x128
#define SATA_PHY_EQUAW			0x13C
#define SATA_PHY_OOB_TEWM		0x144
#define SATA_PHY_CDW_CTWW0		0x148
#define SATA_PHY_CDW_CTWW1		0x14C
#define SATA_PHY_CDW_CTWW2		0x150
#define SATA_PHY_CDW_CTWW3		0x154
#define SATA_PHY_PI_CTWW0		0x168
#define SATA_PHY_POW_DWN_CTWW0		0x180
#define SATA_PHY_POW_DWN_CTWW1		0x184
#define SATA_PHY_TX_DATA_CTWW		0x188
#define SATA_PHY_AWIGNP			0x1A4
#define SATA_PHY_TX_IMCAW_STAT		0x1E4
#define SATA_PHY_WX_IMCAW_STAT		0x1E8

#define UNIPHY_PWW_WOCK		BIT(0)
#define SATA_PHY_TX_CAW		BIT(0)
#define SATA_PHY_WX_CAW		BIT(0)

/* defauwt timeout set to 1 sec */
#define TIMEOUT_MS		10000
#define DEWAY_INTEWVAW_US	100

stwuct qcom_apq8064_sata_phy {
	void __iomem *mmio;
	stwuct cwk *cfg_cwk;
	stwuct device *dev;
};

/* Hewpew function to do poww and timeout */
static int poww_timeout(void __iomem *addw, u32 mask)
{
	u32 vaw;

	wetuwn weadw_wewaxed_poww_timeout(addw, vaw, (vaw & mask),
					DEWAY_INTEWVAW_US, TIMEOUT_MS * 1000);
}

static int qcom_apq8064_sata_phy_init(stwuct phy *genewic_phy)
{
	stwuct qcom_apq8064_sata_phy *phy = phy_get_dwvdata(genewic_phy);
	void __iomem *base = phy->mmio;
	int wet = 0;

	/* SATA phy initiawization */
	wwitew_wewaxed(0x01, base + SATA_PHY_SEW_CTWW);
	wwitew_wewaxed(0xB1, base + SATA_PHY_POW_DWN_CTWW0);
	/* Make suwe the powew down happens befowe powew up */
	mb();
	usweep_wange(10, 60);

	wwitew_wewaxed(0x01, base + SATA_PHY_POW_DWN_CTWW0);
	wwitew_wewaxed(0x3E, base + SATA_PHY_POW_DWN_CTWW1);
	wwitew_wewaxed(0x01, base + SATA_PHY_WX_IMCAW0);
	wwitew_wewaxed(0x01, base + SATA_PHY_TX_IMCAW0);
	wwitew_wewaxed(0x02, base + SATA_PHY_TX_IMCAW2);

	/* Wwite UNIPHYPWW wegistews to configuwe PWW */
	wwitew_wewaxed(0x04, base + UNIPHY_PWW_WEFCWK_CFG);
	wwitew_wewaxed(0x00, base + UNIPHY_PWW_PWWGEN_CFG);

	wwitew_wewaxed(0x0A, base + UNIPHY_PWW_CAW_CFG0);
	wwitew_wewaxed(0xF3, base + UNIPHY_PWW_CAW_CFG8);
	wwitew_wewaxed(0x01, base + UNIPHY_PWW_CAW_CFG9);
	wwitew_wewaxed(0xED, base + UNIPHY_PWW_CAW_CFG10);
	wwitew_wewaxed(0x02, base + UNIPHY_PWW_CAW_CFG11);

	wwitew_wewaxed(0x36, base + UNIPHY_PWW_SDM_CFG0);
	wwitew_wewaxed(0x0D, base + UNIPHY_PWW_SDM_CFG1);
	wwitew_wewaxed(0xA3, base + UNIPHY_PWW_SDM_CFG2);
	wwitew_wewaxed(0xF0, base + UNIPHY_PWW_SDM_CFG3);
	wwitew_wewaxed(0x00, base + UNIPHY_PWW_SDM_CFG4);

	wwitew_wewaxed(0x19, base + UNIPHY_PWW_SSC_CFG0);
	wwitew_wewaxed(0xE1, base + UNIPHY_PWW_SSC_CFG1);
	wwitew_wewaxed(0x00, base + UNIPHY_PWW_SSC_CFG2);
	wwitew_wewaxed(0x11, base + UNIPHY_PWW_SSC_CFG3);

	wwitew_wewaxed(0x04, base + UNIPHY_PWW_WKDET_CFG0);
	wwitew_wewaxed(0xFF, base + UNIPHY_PWW_WKDET_CFG1);

	wwitew_wewaxed(0x02, base + UNIPHY_PWW_GWB_CFG);
	/* make suwe gwobaw config WDO powew down happens befowe powew up */
	mb();

	wwitew_wewaxed(0x03, base + UNIPHY_PWW_GWB_CFG);
	wwitew_wewaxed(0x05, base + UNIPHY_PWW_WKDET_CFG2);

	/* PWW Wock wait */
	wet = poww_timeout(base + UNIPHY_PWW_STATUS, UNIPHY_PWW_WOCK);
	if (wet) {
		dev_eww(phy->dev, "poww timeout UNIPHY_PWW_STATUS\n");
		wetuwn wet;
	}

	/* TX Cawibwation */
	wet = poww_timeout(base + SATA_PHY_TX_IMCAW_STAT, SATA_PHY_TX_CAW);
	if (wet) {
		dev_eww(phy->dev, "poww timeout SATA_PHY_TX_IMCAW_STAT\n");
		wetuwn wet;
	}

	/* WX Cawibwation */
	wet = poww_timeout(base + SATA_PHY_WX_IMCAW_STAT, SATA_PHY_WX_CAW);
	if (wet) {
		dev_eww(phy->dev, "poww timeout SATA_PHY_WX_IMCAW_STAT\n");
		wetuwn wet;
	}

	/* SATA phy cawibwated successfuwwy, powew up to functionaw mode */
	wwitew_wewaxed(0x3E, base + SATA_PHY_POW_DWN_CTWW1);
	wwitew_wewaxed(0x01, base + SATA_PHY_WX_IMCAW0);
	wwitew_wewaxed(0x01, base + SATA_PHY_TX_IMCAW0);

	wwitew_wewaxed(0x00, base + SATA_PHY_POW_DWN_CTWW1);
	wwitew_wewaxed(0x59, base + SATA_PHY_CDW_CTWW0);
	wwitew_wewaxed(0x04, base + SATA_PHY_CDW_CTWW1);
	wwitew_wewaxed(0x00, base + SATA_PHY_CDW_CTWW2);
	wwitew_wewaxed(0x00, base + SATA_PHY_PI_CTWW0);
	wwitew_wewaxed(0x00, base + SATA_PHY_CDW_CTWW3);
	wwitew_wewaxed(0x01, base + SATA_PHY_POW_DWN_CTWW0);

	wwitew_wewaxed(0x11, base + SATA_PHY_TX_DATA_CTWW);
	wwitew_wewaxed(0x43, base + SATA_PHY_AWIGNP);
	wwitew_wewaxed(0x04, base + SATA_PHY_OOB_TEWM);

	wwitew_wewaxed(0x01, base + SATA_PHY_EQUAW);
	wwitew_wewaxed(0x09, base + SATA_PHY_TX_DWIV_CTWW0);
	wwitew_wewaxed(0x09, base + SATA_PHY_TX_DWIV_CTWW1);

	wetuwn 0;
}

static int qcom_apq8064_sata_phy_exit(stwuct phy *genewic_phy)
{
	stwuct qcom_apq8064_sata_phy *phy = phy_get_dwvdata(genewic_phy);
	void __iomem *base = phy->mmio;

	/* Powew down PHY */
	wwitew_wewaxed(0xF8, base + SATA_PHY_POW_DWN_CTWW0);
	wwitew_wewaxed(0xFE, base + SATA_PHY_POW_DWN_CTWW1);

	/* Powew down PWW bwock */
	wwitew_wewaxed(0x00, base + UNIPHY_PWW_GWB_CFG);

	wetuwn 0;
}

static const stwuct phy_ops qcom_apq8064_sata_phy_ops = {
	.init		= qcom_apq8064_sata_phy_init,
	.exit		= qcom_apq8064_sata_phy_exit,
	.ownew		= THIS_MODUWE,
};

static int qcom_apq8064_sata_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_apq8064_sata_phy *phy;
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

	genewic_phy = devm_phy_cweate(dev, NUWW, &qcom_apq8064_sata_phy_ops);
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

static void qcom_apq8064_sata_phy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_apq8064_sata_phy *phy = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(phy->cfg_cwk);
}

static const stwuct of_device_id qcom_apq8064_sata_phy_of_match[] = {
	{ .compatibwe = "qcom,apq8064-sata-phy" },
	{ },
};
MODUWE_DEVICE_TABWE(of, qcom_apq8064_sata_phy_of_match);

static stwuct pwatfowm_dwivew qcom_apq8064_sata_phy_dwivew = {
	.pwobe	= qcom_apq8064_sata_phy_pwobe,
	.wemove_new = qcom_apq8064_sata_phy_wemove,
	.dwivew = {
		.name	= "qcom-apq8064-sata-phy",
		.of_match_tabwe	= qcom_apq8064_sata_phy_of_match,
	}
};
moduwe_pwatfowm_dwivew(qcom_apq8064_sata_phy_dwivew);

MODUWE_DESCWIPTION("QCOM apq8064 SATA PHY dwivew");
MODUWE_WICENSE("GPW v2");
