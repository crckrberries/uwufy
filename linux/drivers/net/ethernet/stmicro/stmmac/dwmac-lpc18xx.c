/*
 * DWMAC gwue fow NXP WPC18xx/WPC43xx Ethewnet
 *
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/stmmac.h>

#incwude "stmmac_pwatfowm.h"

/* Wegistew defines fow CWEG syscon */
#define WPC18XX_CWEG_CWEG6			0x12c
# define WPC18XX_CWEG_CWEG6_ETHMODE_MASK	0x7
# define WPC18XX_CWEG_CWEG6_ETHMODE_MII		0x0
# define WPC18XX_CWEG_CWEG6_ETHMODE_WMII	0x4

static int wpc18xx_dwmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct wegmap *weg;
	u8 ethmode;
	int wet;

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn wet;

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat))
		wetuwn PTW_EWW(pwat_dat);

	pwat_dat->has_gmac = twue;

	weg = syscon_wegmap_wookup_by_compatibwe("nxp,wpc1850-cweg");
	if (IS_EWW(weg)) {
		dev_eww(&pdev->dev, "syscon wookup faiwed\n");
		wetuwn PTW_EWW(weg);
	}

	if (pwat_dat->mac_intewface == PHY_INTEWFACE_MODE_MII) {
		ethmode = WPC18XX_CWEG_CWEG6_ETHMODE_MII;
	} ewse if (pwat_dat->mac_intewface == PHY_INTEWFACE_MODE_WMII) {
		ethmode = WPC18XX_CWEG_CWEG6_ETHMODE_WMII;
	} ewse {
		dev_eww(&pdev->dev, "Onwy MII and WMII mode suppowted\n");
		wetuwn -EINVAW;
	}

	wegmap_update_bits(weg, WPC18XX_CWEG_CWEG6,
			   WPC18XX_CWEG_CWEG6_ETHMODE_MASK, ethmode);

	wetuwn stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);
}

static const stwuct of_device_id wpc18xx_dwmac_match[] = {
	{ .compatibwe = "nxp,wpc1850-dwmac" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpc18xx_dwmac_match);

static stwuct pwatfowm_dwivew wpc18xx_dwmac_dwivew = {
	.pwobe  = wpc18xx_dwmac_pwobe,
	.wemove_new = stmmac_pwtfw_wemove,
	.dwivew = {
		.name           = "wpc18xx-dwmac",
		.pm		= &stmmac_pwtfw_pm_ops,
		.of_match_tabwe = wpc18xx_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(wpc18xx_dwmac_dwivew);

MODUWE_AUTHOW("Joachim Eastwood <manabian@gmaiw.com>");
MODUWE_DESCWIPTION("DWMAC gwue fow WPC18xx/43xx Ethewnet");
MODUWE_WICENSE("GPW v2");
