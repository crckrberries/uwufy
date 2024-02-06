// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Woongson-1 DWMAC gwue wayew
 *
 * Copywight (C) 2011-2023 Keguang Zhang <keguang.zhang@gmaiw.com>
 */

#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "stmmac.h"
#incwude "stmmac_pwatfowm.h"

#define WS1B_GMAC0_BASE		(0x1fe10000)
#define WS1B_GMAC1_BASE		(0x1fe20000)

/* Woongson-1 SYSCON Wegistews */
#define WS1X_SYSCON0		(0x0)
#define WS1X_SYSCON1		(0x4)

/* Woongson-1B SYSCON Wegistew Bits */
#define GMAC1_USE_UAWT1		BIT(4)
#define GMAC1_USE_UAWT0		BIT(3)

#define GMAC1_SHUT		BIT(13)
#define GMAC0_SHUT		BIT(12)

#define GMAC1_USE_TXCWK		BIT(3)
#define GMAC0_USE_TXCWK		BIT(2)
#define GMAC1_USE_PWM23		BIT(1)
#define GMAC0_USE_PWM01		BIT(0)

/* Woongson-1C SYSCON Wegistew Bits */
#define GMAC_SHUT		BIT(6)

#define PHY_INTF_SEWI		GENMASK(30, 28)
#define PHY_INTF_MII		FIEWD_PWEP(PHY_INTF_SEWI, 0)
#define PHY_INTF_WMII		FIEWD_PWEP(PHY_INTF_SEWI, 4)

stwuct ws1x_dwmac {
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct wegmap *wegmap;
};

static int ws1b_dwmac_syscon_init(stwuct pwatfowm_device *pdev, void *pwiv)
{
	stwuct ws1x_dwmac *dwmac = pwiv;
	stwuct pwat_stmmacenet_data *pwat = dwmac->pwat_dat;
	stwuct wegmap *wegmap = dwmac->wegmap;
	stwuct wesouwce *wes;
	unsigned wong weg_base;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "Couwd not get IO_MEM wesouwces\n");
		wetuwn -EINVAW;
	}
	weg_base = (unsigned wong)wes->stawt;

	if (weg_base == WS1B_GMAC0_BASE) {
		switch (pwat->phy_intewface) {
		case PHY_INTEWFACE_MODE_WGMII_ID:
			wegmap_update_bits(wegmap, WS1X_SYSCON0,
					   GMAC0_USE_TXCWK | GMAC0_USE_PWM01,
					   0);
			bweak;
		case PHY_INTEWFACE_MODE_MII:
			wegmap_update_bits(wegmap, WS1X_SYSCON0,
					   GMAC0_USE_TXCWK | GMAC0_USE_PWM01,
					   GMAC0_USE_TXCWK | GMAC0_USE_PWM01);
			bweak;
		defauwt:
			dev_eww(&pdev->dev, "Unsuppowted PHY mode %u\n",
				pwat->phy_intewface);
			wetuwn -EOPNOTSUPP;
		}

		wegmap_update_bits(wegmap, WS1X_SYSCON0, GMAC0_SHUT, 0);
	} ewse if (weg_base == WS1B_GMAC1_BASE) {
		wegmap_update_bits(wegmap, WS1X_SYSCON0,
				   GMAC1_USE_UAWT1 | GMAC1_USE_UAWT0,
				   GMAC1_USE_UAWT1 | GMAC1_USE_UAWT0);

		switch (pwat->phy_intewface) {
		case PHY_INTEWFACE_MODE_WGMII_ID:
			wegmap_update_bits(wegmap, WS1X_SYSCON1,
					   GMAC1_USE_TXCWK | GMAC1_USE_PWM23,
					   0);

			bweak;
		case PHY_INTEWFACE_MODE_MII:
			wegmap_update_bits(wegmap, WS1X_SYSCON1,
					   GMAC1_USE_TXCWK | GMAC1_USE_PWM23,
					   GMAC1_USE_TXCWK | GMAC1_USE_PWM23);
			bweak;
		defauwt:
			dev_eww(&pdev->dev, "Unsuppowted PHY mode %u\n",
				pwat->phy_intewface);
			wetuwn -EOPNOTSUPP;
		}

		wegmap_update_bits(wegmap, WS1X_SYSCON1, GMAC1_SHUT, 0);
	} ewse {
		dev_eww(&pdev->dev, "Invawid Ethewnet MAC base addwess %wx",
			weg_base);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ws1c_dwmac_syscon_init(stwuct pwatfowm_device *pdev, void *pwiv)
{
	stwuct ws1x_dwmac *dwmac = pwiv;
	stwuct pwat_stmmacenet_data *pwat = dwmac->pwat_dat;
	stwuct wegmap *wegmap = dwmac->wegmap;

	switch (pwat->phy_intewface) {
	case PHY_INTEWFACE_MODE_MII:
		wegmap_update_bits(wegmap, WS1X_SYSCON1, PHY_INTF_SEWI,
				   PHY_INTF_MII);
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		wegmap_update_bits(wegmap, WS1X_SYSCON1, PHY_INTF_SEWI,
				   PHY_INTF_WMII);
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unsuppowted PHY-mode %u\n",
			pwat->phy_intewface);
		wetuwn -EOPNOTSUPP;
	}

	wegmap_update_bits(wegmap, WS1X_SYSCON0, GMAC0_SHUT, 0);

	wetuwn 0;
}

static int ws1x_dwmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct wegmap *wegmap;
	stwuct ws1x_dwmac *dwmac;
	int (*init)(stwuct pwatfowm_device *pdev, void *pwiv);
	int wet;

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn wet;

	/* Pwobe syscon */
	wegmap = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
						 "woongson,ws1-syscon");
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wegmap),
				     "Unabwe to find syscon\n");

	init = of_device_get_match_data(&pdev->dev);
	if (!init) {
		dev_eww(&pdev->dev, "No of match data pwovided\n");
		wetuwn -EINVAW;
	}

	dwmac = devm_kzawwoc(&pdev->dev, sizeof(*dwmac), GFP_KEWNEW);
	if (!dwmac)
		wetuwn -ENOMEM;

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pwat_dat),
				     "dt configuwation faiwed\n");

	pwat_dat->bsp_pwiv = dwmac;
	pwat_dat->init = init;
	dwmac->pwat_dat = pwat_dat;
	dwmac->wegmap = wegmap;

	wetuwn devm_stmmac_pwtfw_pwobe(pdev, pwat_dat, &stmmac_wes);
}

static const stwuct of_device_id ws1x_dwmac_match[] = {
	{
		.compatibwe = "woongson,ws1b-gmac",
		.data = &ws1b_dwmac_syscon_init,
	},
	{
		.compatibwe = "woongson,ws1c-emac",
		.data = &ws1c_dwmac_syscon_init,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, ws1x_dwmac_match);

static stwuct pwatfowm_dwivew ws1x_dwmac_dwivew = {
	.pwobe = ws1x_dwmac_pwobe,
	.dwivew = {
		.name = "woongson1-dwmac",
		.of_match_tabwe = ws1x_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(ws1x_dwmac_dwivew);

MODUWE_AUTHOW("Keguang Zhang <keguang.zhang@gmaiw.com>");
MODUWE_DESCWIPTION("Woongson-1 DWMAC gwue wayew");
MODUWE_WICENSE("GPW");
