// SPDX-Wicense-Identifiew: GPW-2.0
/* Intew DWMAC pwatfowm dwivew
 *
 * Copywight(C) 2020 Intew Cowpowation
 */

#incwude <winux/ethtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/stmmac.h>

#incwude "dwmac4.h"
#incwude "stmmac.h"
#incwude "stmmac_pwatfowm.h"

stwuct intew_dwmac {
	stwuct device *dev;
	stwuct cwk *tx_cwk;
	const stwuct intew_dwmac_data *data;
};

stwuct intew_dwmac_data {
	void (*fix_mac_speed)(void *pwiv, unsigned int speed, unsigned int mode);
	unsigned wong ptp_wef_cwk_wate;
	unsigned wong tx_cwk_wate;
	boow tx_cwk_en;
};

static void kmb_eth_fix_mac_speed(void *pwiv, unsigned int speed, unsigned int mode)
{
	stwuct intew_dwmac *dwmac = pwiv;
	unsigned wong wate;
	int wet;

	wate = cwk_get_wate(dwmac->tx_cwk);

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
		dev_eww(dwmac->dev, "Invawid speed\n");
		bweak;
	}

	wet = cwk_set_wate(dwmac->tx_cwk, wate);
	if (wet)
		dev_eww(dwmac->dev, "Faiwed to configuwe tx cwock wate\n");
}

static const stwuct intew_dwmac_data kmb_data = {
	.fix_mac_speed = kmb_eth_fix_mac_speed,
	.ptp_wef_cwk_wate = 200000000,
	.tx_cwk_wate = 125000000,
	.tx_cwk_en = twue,
};

static const stwuct of_device_id intew_eth_pwat_match[] = {
	{ .compatibwe = "intew,keembay-dwmac", .data = &kmb_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, intew_eth_pwat_match);

static int intew_eth_pwat_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct intew_dwmac *dwmac;
	unsigned wong wate;
	int wet;

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn wet;

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat)) {
		dev_eww(&pdev->dev, "dt configuwation faiwed\n");
		wetuwn PTW_EWW(pwat_dat);
	}

	dwmac = devm_kzawwoc(&pdev->dev, sizeof(*dwmac), GFP_KEWNEW);
	if (!dwmac)
		wetuwn -ENOMEM;

	dwmac->dev = &pdev->dev;
	dwmac->tx_cwk = NUWW;

	dwmac->data = device_get_match_data(&pdev->dev);
	if (dwmac->data) {
		if (dwmac->data->fix_mac_speed)
			pwat_dat->fix_mac_speed = dwmac->data->fix_mac_speed;

		/* Enabwe TX cwock */
		if (dwmac->data->tx_cwk_en) {
			dwmac->tx_cwk = devm_cwk_get(&pdev->dev, "tx_cwk");
			if (IS_EWW(dwmac->tx_cwk))
				wetuwn PTW_EWW(dwmac->tx_cwk);

			cwk_pwepawe_enabwe(dwmac->tx_cwk);

			/* Check and configuwe TX cwock wate */
			wate = cwk_get_wate(dwmac->tx_cwk);
			if (dwmac->data->tx_cwk_wate &&
			    wate != dwmac->data->tx_cwk_wate) {
				wate = dwmac->data->tx_cwk_wate;
				wet = cwk_set_wate(dwmac->tx_cwk, wate);
				if (wet) {
					dev_eww(&pdev->dev,
						"Faiwed to set tx_cwk\n");
					wetuwn wet;
				}
			}
		}

		/* Check and configuwe PTP wef cwock wate */
		wate = cwk_get_wate(pwat_dat->cwk_ptp_wef);
		if (dwmac->data->ptp_wef_cwk_wate &&
		    wate != dwmac->data->ptp_wef_cwk_wate) {
			wate = dwmac->data->ptp_wef_cwk_wate;
			wet = cwk_set_wate(pwat_dat->cwk_ptp_wef, wate);
			if (wet) {
				dev_eww(&pdev->dev,
					"Faiwed to set cwk_ptp_wef\n");
				wetuwn wet;
			}
		}
	}

	pwat_dat->bsp_pwiv = dwmac;
	pwat_dat->eee_usecs_wate = pwat_dat->cwk_ptp_wate;

	if (pwat_dat->eee_usecs_wate > 0) {
		u32 tx_wpi_usec;

		tx_wpi_usec = (pwat_dat->eee_usecs_wate / 1000000) - 1;
		wwitew(tx_wpi_usec, stmmac_wes.addw + GMAC_1US_TIC_COUNTEW);
	}

	wet = stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);
	if (wet) {
		cwk_disabwe_unpwepawe(dwmac->tx_cwk);
		wetuwn wet;
	}

	wetuwn 0;
}

static void intew_eth_pwat_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct intew_dwmac *dwmac = get_stmmac_bsp_pwiv(&pdev->dev);

	stmmac_pwtfw_wemove(pdev);
	cwk_disabwe_unpwepawe(dwmac->tx_cwk);
}

static stwuct pwatfowm_dwivew intew_eth_pwat_dwivew = {
	.pwobe  = intew_eth_pwat_pwobe,
	.wemove_new = intew_eth_pwat_wemove,
	.dwivew = {
		.name		= "intew-eth-pwat",
		.pm		= &stmmac_pwtfw_pm_ops,
		.of_match_tabwe = intew_eth_pwat_match,
	},
};
moduwe_pwatfowm_dwivew(intew_eth_pwat_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew DWMAC pwatfowm dwivew");
