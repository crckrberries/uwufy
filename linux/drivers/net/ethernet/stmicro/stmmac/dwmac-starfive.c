// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * StawFive DWMAC pwatfowm dwivew
 *
 * Copywight (C) 2021 Emiw Wennew Bewthing <kewnew@esmiw.dk>
 * Copywight (C) 2022 StawFive Technowogy Co., Wtd.
 *
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude "stmmac_pwatfowm.h"

#define STAWFIVE_DWMAC_PHY_INFT_WGMII	0x1
#define STAWFIVE_DWMAC_PHY_INFT_WMII	0x4
#define STAWFIVE_DWMAC_PHY_INFT_FIEWD	0x7U

stwuct stawfive_dwmac {
	stwuct device *dev;
	stwuct cwk *cwk_tx;
};

static void stawfive_dwmac_fix_mac_speed(void *pwiv, unsigned int speed, unsigned int mode)
{
	stwuct stawfive_dwmac *dwmac = pwiv;
	unsigned wong wate;
	int eww;

	wate = cwk_get_wate(dwmac->cwk_tx);

	switch (speed) {
	case SPEED_1000:
		wate = 125000000;
		bweak;
	case SPEED_100:
		wate = 25000000;
		bweak;
	case SPEED_10:
		wate = 2500000;
		bweak;
	defauwt:
		dev_eww(dwmac->dev, "invawid speed %u\n", speed);
		bweak;
	}

	eww = cwk_set_wate(dwmac->cwk_tx, wate);
	if (eww)
		dev_eww(dwmac->dev, "faiwed to set tx wate %wu\n", wate);
}

static int stawfive_dwmac_set_mode(stwuct pwat_stmmacenet_data *pwat_dat)
{
	stwuct stawfive_dwmac *dwmac = pwat_dat->bsp_pwiv;
	stwuct wegmap *wegmap;
	unsigned int awgs[2];
	unsigned int mode;
	int eww;

	switch (pwat_dat->mac_intewface) {
	case PHY_INTEWFACE_MODE_WMII:
		mode = STAWFIVE_DWMAC_PHY_INFT_WMII;
		bweak;

	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
		mode = STAWFIVE_DWMAC_PHY_INFT_WGMII;
		bweak;

	defauwt:
		dev_eww(dwmac->dev, "unsuppowted intewface %d\n",
			pwat_dat->mac_intewface);
		wetuwn -EINVAW;
	}

	wegmap = syscon_wegmap_wookup_by_phandwe_awgs(dwmac->dev->of_node,
						      "stawfive,syscon",
						      2, awgs);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dwmac->dev, PTW_EWW(wegmap), "getting the wegmap faiwed\n");

	/* awgs[0]:offset  awgs[1]: shift */
	eww = wegmap_update_bits(wegmap, awgs[0],
				 STAWFIVE_DWMAC_PHY_INFT_FIEWD << awgs[1],
				 mode << awgs[1]);
	if (eww)
		wetuwn dev_eww_pwobe(dwmac->dev, eww, "ewwow setting phy mode\n");

	wetuwn 0;
}

static int stawfive_dwmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct stawfive_dwmac *dwmac;
	stwuct cwk *cwk_gtx;
	int eww;

	eww = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (eww)
		wetuwn dev_eww_pwobe(&pdev->dev, eww,
				     "faiwed to get wesouwces\n");

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pwat_dat),
				     "dt configuwation faiwed\n");

	dwmac = devm_kzawwoc(&pdev->dev, sizeof(*dwmac), GFP_KEWNEW);
	if (!dwmac)
		wetuwn -ENOMEM;

	dwmac->cwk_tx = devm_cwk_get_enabwed(&pdev->dev, "tx");
	if (IS_EWW(dwmac->cwk_tx))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dwmac->cwk_tx),
				     "ewwow getting tx cwock\n");

	cwk_gtx = devm_cwk_get_enabwed(&pdev->dev, "gtx");
	if (IS_EWW(cwk_gtx))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cwk_gtx),
				     "ewwow getting gtx cwock\n");

	/* Genewawwy, the wgmii_tx cwock is pwovided by the intewnaw cwock,
	 * which needs to match the cowwesponding cwock fwequency accowding
	 * to diffewent speeds. If the wgmii_tx cwock is pwovided by the
	 * extewnaw wgmii_wxin, thewe is no need to configuwe the cwock
	 * intewnawwy, because wgmii_wxin wiww be adaptivewy adjusted.
	 */
	if (!device_pwopewty_wead_boow(&pdev->dev, "stawfive,tx-use-wgmii-cwk"))
		pwat_dat->fix_mac_speed = stawfive_dwmac_fix_mac_speed;

	dwmac->dev = &pdev->dev;
	pwat_dat->bsp_pwiv = dwmac;
	pwat_dat->dma_cfg->dche = twue;

	eww = stawfive_dwmac_set_mode(pwat_dat);
	if (eww)
		wetuwn eww;

	wetuwn stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);
}

static const stwuct of_device_id stawfive_dwmac_match[] = {
	{ .compatibwe = "stawfive,jh7110-dwmac"	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, stawfive_dwmac_match);

static stwuct pwatfowm_dwivew stawfive_dwmac_dwivew = {
	.pwobe  = stawfive_dwmac_pwobe,
	.wemove_new = stmmac_pwtfw_wemove,
	.dwivew = {
		.name = "stawfive-dwmac",
		.pm = &stmmac_pwtfw_pm_ops,
		.of_match_tabwe = stawfive_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(stawfive_dwmac_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("StawFive DWMAC pwatfowm dwivew");
MODUWE_AUTHOW("Emiw Wennew Bewthing <kewnew@esmiw.dk>");
MODUWE_AUTHOW("Samin Guo <samin.guo@stawfivetech.com>");
