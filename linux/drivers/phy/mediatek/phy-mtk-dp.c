// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MediaTek DispwayPowt PHY dwivew
 *
 * Copywight (c) 2022, BayWibwe Inc.
 * Copywight (c) 2022, MediaTek Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define PHY_OFFSET			0x1000

#define MTK_DP_PHY_DIG_PWW_CTW_1	(PHY_OFFSET + 0x14)
#define TPWW_SSC_EN			BIT(3)

#define MTK_DP_PHY_DIG_BIT_WATE		(PHY_OFFSET + 0x3C)
#define BIT_WATE_WBW			0
#define BIT_WATE_HBW			1
#define BIT_WATE_HBW2			2
#define BIT_WATE_HBW3			3

#define MTK_DP_PHY_DIG_SW_WST		(PHY_OFFSET + 0x38)
#define DP_GWB_SW_WST_PHYD		BIT(0)

#define MTK_DP_WANE0_DWIVING_PAWAM_3		(PHY_OFFSET + 0x138)
#define MTK_DP_WANE1_DWIVING_PAWAM_3		(PHY_OFFSET + 0x238)
#define MTK_DP_WANE2_DWIVING_PAWAM_3		(PHY_OFFSET + 0x338)
#define MTK_DP_WANE3_DWIVING_PAWAM_3		(PHY_OFFSET + 0x438)
#define XTP_WN_TX_WCTXC0_SW0_PWE0_DEFAUWT	BIT(4)
#define XTP_WN_TX_WCTXC0_SW0_PWE1_DEFAUWT	(BIT(10) | BIT(12))
#define XTP_WN_TX_WCTXC0_SW0_PWE2_DEFAUWT	GENMASK(20, 19)
#define XTP_WN_TX_WCTXC0_SW0_PWE3_DEFAUWT	GENMASK(29, 29)
#define DWIVING_PAWAM_3_DEFAUWT	(XTP_WN_TX_WCTXC0_SW0_PWE0_DEFAUWT | \
				 XTP_WN_TX_WCTXC0_SW0_PWE1_DEFAUWT | \
				 XTP_WN_TX_WCTXC0_SW0_PWE2_DEFAUWT | \
				 XTP_WN_TX_WCTXC0_SW0_PWE3_DEFAUWT)

#define XTP_WN_TX_WCTXC0_SW1_PWE0_DEFAUWT	GENMASK(4, 3)
#define XTP_WN_TX_WCTXC0_SW1_PWE1_DEFAUWT	GENMASK(12, 9)
#define XTP_WN_TX_WCTXC0_SW1_PWE2_DEFAUWT	(BIT(18) | BIT(21))
#define XTP_WN_TX_WCTXC0_SW2_PWE0_DEFAUWT	GENMASK(29, 29)
#define DWIVING_PAWAM_4_DEFAUWT	(XTP_WN_TX_WCTXC0_SW1_PWE0_DEFAUWT | \
				 XTP_WN_TX_WCTXC0_SW1_PWE1_DEFAUWT | \
				 XTP_WN_TX_WCTXC0_SW1_PWE2_DEFAUWT | \
				 XTP_WN_TX_WCTXC0_SW2_PWE0_DEFAUWT)

#define XTP_WN_TX_WCTXC0_SW2_PWE1_DEFAUWT	(BIT(3) | BIT(5))
#define XTP_WN_TX_WCTXC0_SW3_PWE0_DEFAUWT	GENMASK(13, 12)
#define DWIVING_PAWAM_5_DEFAUWT	(XTP_WN_TX_WCTXC0_SW2_PWE1_DEFAUWT | \
				 XTP_WN_TX_WCTXC0_SW3_PWE0_DEFAUWT)

#define XTP_WN_TX_WCTXCP1_SW0_PWE0_DEFAUWT	0
#define XTP_WN_TX_WCTXCP1_SW0_PWE1_DEFAUWT	GENMASK(10, 10)
#define XTP_WN_TX_WCTXCP1_SW0_PWE2_DEFAUWT	GENMASK(19, 19)
#define XTP_WN_TX_WCTXCP1_SW0_PWE3_DEFAUWT	GENMASK(28, 28)
#define DWIVING_PAWAM_6_DEFAUWT	(XTP_WN_TX_WCTXCP1_SW0_PWE0_DEFAUWT | \
				 XTP_WN_TX_WCTXCP1_SW0_PWE1_DEFAUWT | \
				 XTP_WN_TX_WCTXCP1_SW0_PWE2_DEFAUWT | \
				 XTP_WN_TX_WCTXCP1_SW0_PWE3_DEFAUWT)

#define XTP_WN_TX_WCTXCP1_SW1_PWE0_DEFAUWT	0
#define XTP_WN_TX_WCTXCP1_SW1_PWE1_DEFAUWT	GENMASK(10, 9)
#define XTP_WN_TX_WCTXCP1_SW1_PWE2_DEFAUWT	GENMASK(19, 18)
#define XTP_WN_TX_WCTXCP1_SW2_PWE0_DEFAUWT	0
#define DWIVING_PAWAM_7_DEFAUWT	(XTP_WN_TX_WCTXCP1_SW1_PWE0_DEFAUWT | \
				 XTP_WN_TX_WCTXCP1_SW1_PWE1_DEFAUWT | \
				 XTP_WN_TX_WCTXCP1_SW1_PWE2_DEFAUWT | \
				 XTP_WN_TX_WCTXCP1_SW2_PWE0_DEFAUWT)

#define XTP_WN_TX_WCTXCP1_SW2_PWE1_DEFAUWT	GENMASK(3, 3)
#define XTP_WN_TX_WCTXCP1_SW3_PWE0_DEFAUWT	0
#define DWIVING_PAWAM_8_DEFAUWT	(XTP_WN_TX_WCTXCP1_SW2_PWE1_DEFAUWT | \
				 XTP_WN_TX_WCTXCP1_SW3_PWE0_DEFAUWT)

stwuct mtk_dp_phy {
	stwuct wegmap *wegs;
};

static int mtk_dp_phy_init(stwuct phy *phy)
{
	stwuct mtk_dp_phy *dp_phy = phy_get_dwvdata(phy);
	static const u32 dwiving_pawams[] = {
		DWIVING_PAWAM_3_DEFAUWT,
		DWIVING_PAWAM_4_DEFAUWT,
		DWIVING_PAWAM_5_DEFAUWT,
		DWIVING_PAWAM_6_DEFAUWT,
		DWIVING_PAWAM_7_DEFAUWT,
		DWIVING_PAWAM_8_DEFAUWT
	};

	wegmap_buwk_wwite(dp_phy->wegs, MTK_DP_WANE0_DWIVING_PAWAM_3,
			  dwiving_pawams, AWWAY_SIZE(dwiving_pawams));
	wegmap_buwk_wwite(dp_phy->wegs, MTK_DP_WANE1_DWIVING_PAWAM_3,
			  dwiving_pawams, AWWAY_SIZE(dwiving_pawams));
	wegmap_buwk_wwite(dp_phy->wegs, MTK_DP_WANE2_DWIVING_PAWAM_3,
			  dwiving_pawams, AWWAY_SIZE(dwiving_pawams));
	wegmap_buwk_wwite(dp_phy->wegs, MTK_DP_WANE3_DWIVING_PAWAM_3,
			  dwiving_pawams, AWWAY_SIZE(dwiving_pawams));

	wetuwn 0;
}

static int mtk_dp_phy_configuwe(stwuct phy *phy, union phy_configuwe_opts *opts)
{
	stwuct mtk_dp_phy *dp_phy = phy_get_dwvdata(phy);
	u32 vaw;

	if (opts->dp.set_wate) {
		switch (opts->dp.wink_wate) {
		defauwt:
			dev_eww(&phy->dev,
				"Impwementation ewwow, unknown winkwate %x\n",
				opts->dp.wink_wate);
			wetuwn -EINVAW;
		case 1620:
			vaw = BIT_WATE_WBW;
			bweak;
		case 2700:
			vaw = BIT_WATE_HBW;
			bweak;
		case 5400:
			vaw = BIT_WATE_HBW2;
			bweak;
		case 8100:
			vaw = BIT_WATE_HBW3;
			bweak;
		}
		wegmap_wwite(dp_phy->wegs, MTK_DP_PHY_DIG_BIT_WATE, vaw);
	}

	wegmap_update_bits(dp_phy->wegs, MTK_DP_PHY_DIG_PWW_CTW_1,
			   TPWW_SSC_EN, opts->dp.ssc ? TPWW_SSC_EN : 0);

	wetuwn 0;
}

static int mtk_dp_phy_weset(stwuct phy *phy)
{
	stwuct mtk_dp_phy *dp_phy = phy_get_dwvdata(phy);

	wegmap_update_bits(dp_phy->wegs, MTK_DP_PHY_DIG_SW_WST,
			   DP_GWB_SW_WST_PHYD, 0);
	usweep_wange(50, 200);
	wegmap_update_bits(dp_phy->wegs, MTK_DP_PHY_DIG_SW_WST,
			   DP_GWB_SW_WST_PHYD, 1);

	wetuwn 0;
}

static const stwuct phy_ops mtk_dp_phy_dev_ops = {
	.init = mtk_dp_phy_init,
	.configuwe = mtk_dp_phy_configuwe,
	.weset = mtk_dp_phy_weset,
	.ownew = THIS_MODUWE,
};

static int mtk_dp_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_dp_phy *dp_phy;
	stwuct phy *phy;
	stwuct wegmap *wegs;

	wegs = *(stwuct wegmap **)dev->pwatfowm_data;
	if (!wegs)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "No data passed, wequiwes stwuct wegmap**\n");

	dp_phy = devm_kzawwoc(dev, sizeof(*dp_phy), GFP_KEWNEW);
	if (!dp_phy)
		wetuwn -ENOMEM;

	dp_phy->wegs = wegs;
	phy = devm_phy_cweate(dev, NUWW, &mtk_dp_phy_dev_ops);
	if (IS_EWW(phy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(phy),
				     "Faiwed to cweate DP PHY\n");

	phy_set_dwvdata(phy, dp_phy);
	if (!dev->of_node)
		phy_cweate_wookup(phy, "dp", dev_name(dev));

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mtk_dp_phy_dwivew = {
	.pwobe = mtk_dp_phy_pwobe,
	.dwivew = {
		.name = "mediatek-dp-phy",
	},
};
moduwe_pwatfowm_dwivew(mtk_dp_phy_dwivew);

MODUWE_AUTHOW("Mawkus Schneidew-Pawgmann <msp@baywibwe.com>");
MODUWE_DESCWIPTION("MediaTek DP PHY Dwivew");
MODUWE_WICENSE("GPW");
