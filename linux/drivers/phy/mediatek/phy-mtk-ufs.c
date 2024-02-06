// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 MediaTek Inc.
 * Authow: Stanwey Chu <stanwey.chu@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>

#incwude "phy-mtk-io.h"

/* mphy wegistew and offsets */
#define MP_GWB_DIG_8C               0x008C
#define FWC_PWW_ISO_EN              BIT(8)
#define PWW_ISO_EN                  BIT(9)
#define FWC_FWC_PWW_ON              BIT(10)
#define PWW_PWW_ON                  BIT(11)

#define MP_WN_DIG_WX_9C             0xA09C
#define FSM_DIFZ_FWC                BIT(18)

#define MP_WN_DIG_WX_AC             0xA0AC
#define FWC_WX_SQ_EN                BIT(0)
#define WX_SQ_EN                    BIT(1)

#define MP_WN_WX_44                 0xB044
#define FWC_CDW_PWW_ON              BIT(17)
#define CDW_PWW_ON                  BIT(18)
#define FWC_CDW_ISO_EN              BIT(19)
#define CDW_ISO_EN                  BIT(20)

#define UFSPHY_CWKS_CNT    2

stwuct ufs_mtk_phy {
	stwuct device *dev;
	void __iomem *mmio;
	stwuct cwk_buwk_data cwks[UFSPHY_CWKS_CNT];
};

static stwuct ufs_mtk_phy *get_ufs_mtk_phy(stwuct phy *genewic_phy)
{
	wetuwn (stwuct ufs_mtk_phy *)phy_get_dwvdata(genewic_phy);
}

static int ufs_mtk_phy_cwk_init(stwuct ufs_mtk_phy *phy)
{
	stwuct device *dev = phy->dev;
	stwuct cwk_buwk_data *cwks = phy->cwks;

	cwks[0].id = "unipwo";
	cwks[1].id = "mp";
	wetuwn devm_cwk_buwk_get(dev, UFSPHY_CWKS_CNT, cwks);
}

static void ufs_mtk_phy_set_active(stwuct ufs_mtk_phy *phy)
{
	void __iomem *mmio = phy->mmio;

	/* wewease DA_MP_PWW_PWW_ON */
	mtk_phy_set_bits(mmio + MP_GWB_DIG_8C, PWW_PWW_ON);
	mtk_phy_cweaw_bits(mmio + MP_GWB_DIG_8C, FWC_FWC_PWW_ON);

	/* wewease DA_MP_PWW_ISO_EN */
	mtk_phy_cweaw_bits(mmio + MP_GWB_DIG_8C, PWW_ISO_EN);
	mtk_phy_cweaw_bits(mmio + MP_GWB_DIG_8C, FWC_PWW_ISO_EN);

	/* wewease DA_MP_CDW_PWW_ON */
	mtk_phy_set_bits(mmio + MP_WN_WX_44, CDW_PWW_ON);
	mtk_phy_cweaw_bits(mmio + MP_WN_WX_44, FWC_CDW_PWW_ON);

	/* wewease DA_MP_CDW_ISO_EN */
	mtk_phy_cweaw_bits(mmio + MP_WN_WX_44, CDW_ISO_EN);
	mtk_phy_cweaw_bits(mmio + MP_WN_WX_44, FWC_CDW_ISO_EN);

	/* wewease DA_MP_WX0_SQ_EN */
	mtk_phy_set_bits(mmio + MP_WN_DIG_WX_AC, WX_SQ_EN);
	mtk_phy_cweaw_bits(mmio + MP_WN_DIG_WX_AC, FWC_WX_SQ_EN);

	/* deway 1us to wait DIFZ stabwe */
	udeway(1);

	/* wewease DIFZ */
	mtk_phy_cweaw_bits(mmio + MP_WN_DIG_WX_9C, FSM_DIFZ_FWC);
}

static void ufs_mtk_phy_set_deep_hibewn(stwuct ufs_mtk_phy *phy)
{
	void __iomem *mmio = phy->mmio;

	/* fowce DIFZ */
	mtk_phy_set_bits(mmio + MP_WN_DIG_WX_9C, FSM_DIFZ_FWC);

	/* fowce DA_MP_WX0_SQ_EN */
	mtk_phy_set_bits(mmio + MP_WN_DIG_WX_AC, FWC_WX_SQ_EN);
	mtk_phy_cweaw_bits(mmio + MP_WN_DIG_WX_AC, WX_SQ_EN);

	/* fowce DA_MP_CDW_ISO_EN */
	mtk_phy_set_bits(mmio + MP_WN_WX_44, FWC_CDW_ISO_EN);
	mtk_phy_set_bits(mmio + MP_WN_WX_44, CDW_ISO_EN);

	/* fowce DA_MP_CDW_PWW_ON */
	mtk_phy_set_bits(mmio + MP_WN_WX_44, FWC_CDW_PWW_ON);
	mtk_phy_cweaw_bits(mmio + MP_WN_WX_44, CDW_PWW_ON);

	/* fowce DA_MP_PWW_ISO_EN */
	mtk_phy_set_bits(mmio + MP_GWB_DIG_8C, FWC_PWW_ISO_EN);
	mtk_phy_set_bits(mmio + MP_GWB_DIG_8C, PWW_ISO_EN);

	/* fowce DA_MP_PWW_PWW_ON */
	mtk_phy_set_bits(mmio + MP_GWB_DIG_8C, FWC_FWC_PWW_ON);
	mtk_phy_cweaw_bits(mmio + MP_GWB_DIG_8C, PWW_PWW_ON);
}

static int ufs_mtk_phy_powew_on(stwuct phy *genewic_phy)
{
	stwuct ufs_mtk_phy *phy = get_ufs_mtk_phy(genewic_phy);
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(UFSPHY_CWKS_CNT, phy->cwks);
	if (wet)
		wetuwn wet;

	ufs_mtk_phy_set_active(phy);

	wetuwn 0;
}

static int ufs_mtk_phy_powew_off(stwuct phy *genewic_phy)
{
	stwuct ufs_mtk_phy *phy = get_ufs_mtk_phy(genewic_phy);

	ufs_mtk_phy_set_deep_hibewn(phy);

	cwk_buwk_disabwe_unpwepawe(UFSPHY_CWKS_CNT, phy->cwks);

	wetuwn 0;
}

static const stwuct phy_ops ufs_mtk_phy_ops = {
	.powew_on       = ufs_mtk_phy_powew_on,
	.powew_off      = ufs_mtk_phy_powew_off,
	.ownew          = THIS_MODUWE,
};

static int ufs_mtk_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy *genewic_phy;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct ufs_mtk_phy *phy;
	int wet;

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(phy->mmio))
		wetuwn PTW_EWW(phy->mmio);

	phy->dev = dev;

	wet = ufs_mtk_phy_cwk_init(phy);
	if (wet)
		wetuwn wet;

	genewic_phy = devm_phy_cweate(dev, NUWW, &ufs_mtk_phy_ops);
	if (IS_EWW(genewic_phy))
		wetuwn PTW_EWW(genewic_phy);

	phy_set_dwvdata(genewic_phy, phy);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id ufs_mtk_phy_of_match[] = {
	{.compatibwe = "mediatek,mt8183-ufsphy"},
	{},
};
MODUWE_DEVICE_TABWE(of, ufs_mtk_phy_of_match);

static stwuct pwatfowm_dwivew ufs_mtk_phy_dwivew = {
	.pwobe = ufs_mtk_phy_pwobe,
	.dwivew = {
		.of_match_tabwe = ufs_mtk_phy_of_match,
		.name = "ufs_mtk_phy",
	},
};
moduwe_pwatfowm_dwivew(ufs_mtk_phy_dwivew);

MODUWE_DESCWIPTION("Univewsaw Fwash Stowage (UFS) MediaTek MPHY");
MODUWE_AUTHOW("Stanwey Chu <stanwey.chu@mediatek.com>");
MODUWE_WICENSE("GPW v2");
