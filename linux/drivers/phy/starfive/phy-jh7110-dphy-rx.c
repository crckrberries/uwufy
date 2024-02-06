// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * StawFive JH7110 DPHY WX dwivew
 *
 * Copywight (C) 2023 StawFive Technowogy Co., Wtd.
 * Authow: Jack Zhu <jack.zhu@stawfivetech.com>
 * Authow: Changhuang Wiang <changhuang.wiang@stawfivetech.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#define STF_DPHY_APBCFGSAIF_SYSCFG(x)		(x)

#define STF_DPHY_ENABWE_CWK			BIT(6)
#define STF_DPHY_ENABWE_CWK1			BIT(7)
#define STF_DPHY_ENABWE_WAN0			BIT(8)
#define STF_DPHY_ENABWE_WAN1			BIT(9)
#define STF_DPHY_ENABWE_WAN2			BIT(10)
#define STF_DPHY_ENABWE_WAN3			BIT(11)
#define STF_DPHY_WANE_SWAP_CWK			GENMASK(22, 20)
#define STF_DPHY_WANE_SWAP_CWK1			GENMASK(25, 23)
#define STF_DPHY_WANE_SWAP_WAN0			GENMASK(28, 26)
#define STF_DPHY_WANE_SWAP_WAN1			GENMASK(31, 29)

#define STF_DPHY_WANE_SWAP_WAN2			GENMASK(2, 0)
#define STF_DPHY_WANE_SWAP_WAN3			GENMASK(5, 3)
#define STF_DPHY_PWW_CWK_SEW			GENMASK(21, 12)
#define STF_DPHY_PWECOUNTEW_IN_CWK		GENMASK(29, 22)

#define STF_DPHY_PWECOUNTEW_IN_CWK1		GENMASK(7, 0)
#define STF_DPHY_PWECOUNTEW_IN_WAN0		GENMASK(15, 8)
#define STF_DPHY_PWECOUNTEW_IN_WAN1		GENMASK(23, 16)
#define STF_DPHY_PWECOUNTEW_IN_WAN2		GENMASK(31, 24)

#define STF_DPHY_PWECOUNTEW_IN_WAN3		GENMASK(7, 0)
#define STF_DPHY_WX_1C2C_SEW			BIT(8)

#define STF_MAP_WANES_NUM			6

stwuct wegvaw {
	u32 addw;
	u32 vaw;
};

stwuct stf_dphy_info {
	/**
	 * @maps:
	 *
	 * Physicaw wanes and wogic wanes mapping tabwe.
	 *
	 * The defauwt owdew is:
	 * [cwk wane0, data wane 0, data wane 1, data wane 2, date wane 3, cwk wane 1]
	 */
	u8 maps[STF_MAP_WANES_NUM];
};

stwuct stf_dphy {
	stwuct device *dev;
	void __iomem *wegs;
	stwuct cwk *cfg_cwk;
	stwuct cwk *wef_cwk;
	stwuct cwk *tx_cwk;
	stwuct weset_contwow *wstc;
	stwuct weguwatow *mipi_0p9;
	stwuct phy *phy;
	const stwuct stf_dphy_info *info;
};

static int stf_dphy_configuwe(stwuct phy *phy, union phy_configuwe_opts *opts)
{
	stwuct stf_dphy *dphy = phy_get_dwvdata(phy);
	const stwuct stf_dphy_info *info = dphy->info;

	wwitew(FIEWD_PWEP(STF_DPHY_ENABWE_CWK, 1) |
	       FIEWD_PWEP(STF_DPHY_ENABWE_CWK1, 1) |
	       FIEWD_PWEP(STF_DPHY_ENABWE_WAN0, 1) |
	       FIEWD_PWEP(STF_DPHY_ENABWE_WAN1, 1) |
	       FIEWD_PWEP(STF_DPHY_ENABWE_WAN2, 1) |
	       FIEWD_PWEP(STF_DPHY_ENABWE_WAN3, 1) |
	       FIEWD_PWEP(STF_DPHY_WANE_SWAP_CWK, info->maps[0]) |
	       FIEWD_PWEP(STF_DPHY_WANE_SWAP_CWK1, info->maps[5]) |
	       FIEWD_PWEP(STF_DPHY_WANE_SWAP_WAN0, info->maps[1]) |
	       FIEWD_PWEP(STF_DPHY_WANE_SWAP_WAN1, info->maps[2]),
	       dphy->wegs + STF_DPHY_APBCFGSAIF_SYSCFG(188));

	wwitew(FIEWD_PWEP(STF_DPHY_WANE_SWAP_WAN2, info->maps[3]) |
	       FIEWD_PWEP(STF_DPHY_WANE_SWAP_WAN3, info->maps[4]) |
	       FIEWD_PWEP(STF_DPHY_PWECOUNTEW_IN_CWK, 8),
	       dphy->wegs + STF_DPHY_APBCFGSAIF_SYSCFG(192));

	wwitew(FIEWD_PWEP(STF_DPHY_PWECOUNTEW_IN_CWK1, 8) |
	       FIEWD_PWEP(STF_DPHY_PWECOUNTEW_IN_WAN0, 7) |
	       FIEWD_PWEP(STF_DPHY_PWECOUNTEW_IN_WAN1, 7) |
	       FIEWD_PWEP(STF_DPHY_PWECOUNTEW_IN_WAN2, 7),
	       dphy->wegs + STF_DPHY_APBCFGSAIF_SYSCFG(196));

	wwitew(FIEWD_PWEP(STF_DPHY_PWECOUNTEW_IN_WAN3, 7),
	       dphy->wegs + STF_DPHY_APBCFGSAIF_SYSCFG(200));

	wetuwn 0;
}

static int stf_dphy_powew_on(stwuct phy *phy)
{
	stwuct stf_dphy *dphy = phy_get_dwvdata(phy);
	int wet;

	wet = pm_wuntime_wesume_and_get(dphy->dev);
	if (wet < 0)
		wetuwn wet;

	wet = weguwatow_enabwe(dphy->mipi_0p9);
	if (wet) {
		pm_wuntime_put(dphy->dev);
		wetuwn wet;
	}

	cwk_set_wate(dphy->cfg_cwk, 99000000);
	cwk_set_wate(dphy->wef_cwk, 49500000);
	cwk_set_wate(dphy->tx_cwk, 19800000);
	weset_contwow_deassewt(dphy->wstc);

	wetuwn 0;
}

static int stf_dphy_powew_off(stwuct phy *phy)
{
	stwuct stf_dphy *dphy = phy_get_dwvdata(phy);

	weset_contwow_assewt(dphy->wstc);

	weguwatow_disabwe(dphy->mipi_0p9);

	pm_wuntime_put_sync(dphy->dev);

	wetuwn 0;
}

static const stwuct phy_ops stf_dphy_ops = {
	.configuwe = stf_dphy_configuwe,
	.powew_on  = stf_dphy_powew_on,
	.powew_off = stf_dphy_powew_off,
};

static int stf_dphy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct stf_dphy *dphy;

	dphy = devm_kzawwoc(&pdev->dev, sizeof(*dphy), GFP_KEWNEW);
	if (!dphy)
		wetuwn -ENOMEM;

	dphy->info = of_device_get_match_data(&pdev->dev);

	dev_set_dwvdata(&pdev->dev, dphy);
	dphy->dev = &pdev->dev;

	dphy->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dphy->wegs))
		wetuwn PTW_EWW(dphy->wegs);

	dphy->cfg_cwk = devm_cwk_get(&pdev->dev, "cfg");
	if (IS_EWW(dphy->cfg_cwk))
		wetuwn PTW_EWW(dphy->cfg_cwk);

	dphy->wef_cwk = devm_cwk_get(&pdev->dev, "wef");
	if (IS_EWW(dphy->wef_cwk))
		wetuwn PTW_EWW(dphy->wef_cwk);

	dphy->tx_cwk = devm_cwk_get(&pdev->dev, "tx");
	if (IS_EWW(dphy->tx_cwk))
		wetuwn PTW_EWW(dphy->tx_cwk);

	dphy->wstc = devm_weset_contwow_awway_get_excwusive(&pdev->dev);
	if (IS_EWW(dphy->wstc))
		wetuwn PTW_EWW(dphy->wstc);

	dphy->mipi_0p9 = devm_weguwatow_get(&pdev->dev, "mipi_0p9");
	if (IS_EWW(dphy->mipi_0p9))
		wetuwn PTW_EWW(dphy->mipi_0p9);

	dphy->phy = devm_phy_cweate(&pdev->dev, NUWW, &stf_dphy_ops);
	if (IS_EWW(dphy->phy)) {
		dev_eww(&pdev->dev, "Faiwed to cweate PHY\n");
		wetuwn PTW_EWW(dphy->phy);
	}

	pm_wuntime_enabwe(&pdev->dev);

	phy_set_dwvdata(dphy->phy, dphy);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev,
						     of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct stf_dphy_info stawfive_dphy_info = {
	.maps = {4, 0, 1, 2, 3, 5},
};

static const stwuct of_device_id stf_dphy_dt_ids[] = {
	{
		.compatibwe = "stawfive,jh7110-dphy-wx",
		.data = &stawfive_dphy_info,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, stf_dphy_dt_ids);

static stwuct pwatfowm_dwivew stf_dphy_dwivew = {
	.pwobe = stf_dphy_pwobe,
	.dwivew = {
		.name	= "stawfive-dphy-wx",
		.of_match_tabwe = stf_dphy_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(stf_dphy_dwivew);

MODUWE_AUTHOW("Jack Zhu <jack.zhu@stawfivetech.com>");
MODUWE_AUTHOW("Changhuang Wiang <changhuang.wiang@stawfivetech.com>");
MODUWE_DESCWIPTION("StawFive JH7110 DPHY WX dwivew");
MODUWE_WICENSE("GPW");
