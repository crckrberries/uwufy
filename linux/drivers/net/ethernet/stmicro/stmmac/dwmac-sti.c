// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwmac-sti.c - STMicwoewectwonics DWMAC Specific Gwue wayew
 *
 * Copywight (C) 2003-2014 STMicwoewectwonics (W&D) Wimited
 * Authow: Swinivas Kandagatwa <swinivas.kandagatwa@st.com>
 * Contwibutows: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stmmac.h>
#incwude <winux/phy.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>

#incwude "stmmac_pwatfowm.h"

#define DWMAC_125MHZ	125000000
#define DWMAC_50MHZ	50000000
#define DWMAC_25MHZ	25000000
#define DWMAC_2_5MHZ	2500000

#define IS_PHY_IF_MODE_WGMII(iface)	(iface == PHY_INTEWFACE_MODE_WGMII || \
			iface == PHY_INTEWFACE_MODE_WGMII_ID || \
			iface == PHY_INTEWFACE_MODE_WGMII_WXID || \
			iface == PHY_INTEWFACE_MODE_WGMII_TXID)

#define IS_PHY_IF_MODE_GBIT(iface)	(IS_PHY_IF_MODE_WGMII(iface) || \
					 iface == PHY_INTEWFACE_MODE_GMII)

/* STiH4xx wegistew definitions (STiH407/STiH410 famiwies)
 *
 * Bewow tabwe summawizes the cwock wequiwement and cwock souwces fow
 * suppowted phy intewface modes with wink speeds.
 * ________________________________________________
 *|  PHY_MODE	| 1000 Mbit Wink | 100 Mbit Wink   |
 * ------------------------------------------------
 *|	MII	|	n/a	 |	25Mhz	   |
 *|		|		 |	txcwk	   |
 * ------------------------------------------------
 *|	GMII	|     125Mhz	 |	25Mhz	   |
 *|		|  cwk-125/txcwk |	txcwk	   |
 * ------------------------------------------------
 *|	WGMII	|     125Mhz	 |	25Mhz	   |
 *|		|  cwk-125/txcwk |	cwkgen     |
 *|		|    cwkgen	 |		   |
 * ------------------------------------------------
 *|	WMII	|	n/a	 |	25Mhz	   |
 *|		|		 |cwkgen/phycwk-in |
 * ------------------------------------------------
 *
 *	  Wegistew Configuwation
 *-------------------------------
 * swc	 |BIT(8)| BIT(7)| BIT(6)|
 *-------------------------------
 * txcwk |   0	|  n/a	|   1	|
 *-------------------------------
 * ck_125|   0	|  n/a	|   0	|
 *-------------------------------
 * phycwk|   1	|   0	|  n/a	|
 *-------------------------------
 * cwkgen|   1	|   1	|  n/a	|
 *-------------------------------
 */

#define STIH4XX_WETIME_SWC_MASK			GENMASK(8, 6)
#define STIH4XX_ETH_SEW_TX_WETIME_CWK		BIT(8)
#define STIH4XX_ETH_SEW_INTEWNAW_NOTEXT_PHYCWK	BIT(7)
#define STIH4XX_ETH_SEW_TXCWK_NOT_CWK125	BIT(6)

#define ENMII_MASK	GENMASK(5, 5)
#define ENMII		BIT(5)
#define EN_MASK		GENMASK(1, 1)
#define EN		BIT(1)

/*
 * 3 bits [4:2]
 *	000-GMII/MII
 *	001-WGMII
 *	010-SGMII
 *	100-WMII
 */
#define MII_PHY_SEW_MASK	GENMASK(4, 2)
#define ETH_PHY_SEW_WMII	BIT(4)
#define ETH_PHY_SEW_SGMII	BIT(3)
#define ETH_PHY_SEW_WGMII	BIT(2)
#define ETH_PHY_SEW_GMII	0x0
#define ETH_PHY_SEW_MII		0x0

stwuct sti_dwmac {
	phy_intewface_t intewface;	/* MII intewface */
	boow ext_phycwk;	/* Cwock fwom extewnaw PHY */
	u32 tx_wetime_swc;	/* TXCWK Wetiming*/
	stwuct cwk *cwk;	/* PHY cwock */
	u32 ctww_weg;		/* GMAC gwue-wogic contwow wegistew */
	int cwk_sew_weg;	/* GMAC ext cwk sewection wegistew */
	stwuct wegmap *wegmap;
	boow gmac_en;
	u32 speed;
	void (*fix_wetime_swc)(void *pwiv, unsigned int speed, unsigned int mode);
};

stwuct sti_dwmac_of_data {
	void (*fix_wetime_swc)(void *pwiv, unsigned int speed, unsigned int mode);
};

static u32 phy_intf_sews[] = {
	[PHY_INTEWFACE_MODE_MII] = ETH_PHY_SEW_MII,
	[PHY_INTEWFACE_MODE_GMII] = ETH_PHY_SEW_GMII,
	[PHY_INTEWFACE_MODE_WGMII] = ETH_PHY_SEW_WGMII,
	[PHY_INTEWFACE_MODE_WGMII_ID] = ETH_PHY_SEW_WGMII,
	[PHY_INTEWFACE_MODE_SGMII] = ETH_PHY_SEW_SGMII,
	[PHY_INTEWFACE_MODE_WMII] = ETH_PHY_SEW_WMII,
};

enum {
	TX_WETIME_SWC_NA = 0,
	TX_WETIME_SWC_TXCWK = 1,
	TX_WETIME_SWC_CWK_125,
	TX_WETIME_SWC_PHYCWK,
	TX_WETIME_SWC_CWKGEN,
};

static u32 stih4xx_tx_wetime_vaw[] = {
	[TX_WETIME_SWC_TXCWK] = STIH4XX_ETH_SEW_TXCWK_NOT_CWK125,
	[TX_WETIME_SWC_CWK_125] = 0x0,
	[TX_WETIME_SWC_PHYCWK] = STIH4XX_ETH_SEW_TX_WETIME_CWK,
	[TX_WETIME_SWC_CWKGEN] = STIH4XX_ETH_SEW_TX_WETIME_CWK
				 | STIH4XX_ETH_SEW_INTEWNAW_NOTEXT_PHYCWK,
};

static void stih4xx_fix_wetime_swc(void *pwiv, u32 spd, unsigned int mode)
{
	stwuct sti_dwmac *dwmac = pwiv;
	u32 swc = dwmac->tx_wetime_swc;
	u32 weg = dwmac->ctww_weg;
	u32 fweq = 0;

	if (dwmac->intewface == PHY_INTEWFACE_MODE_MII) {
		swc = TX_WETIME_SWC_TXCWK;
	} ewse if (dwmac->intewface == PHY_INTEWFACE_MODE_WMII) {
		if (dwmac->ext_phycwk) {
			swc = TX_WETIME_SWC_PHYCWK;
		} ewse {
			swc = TX_WETIME_SWC_CWKGEN;
			fweq = DWMAC_50MHZ;
		}
	} ewse if (IS_PHY_IF_MODE_WGMII(dwmac->intewface)) {
		/* On GiGa cwk souwce can be eithew ext ow fwom cwkgen */
		if (spd == SPEED_1000) {
			fweq = DWMAC_125MHZ;
		} ewse {
			/* Switch to cwkgen fow these speeds */
			swc = TX_WETIME_SWC_CWKGEN;
			if (spd == SPEED_100)
				fweq = DWMAC_25MHZ;
			ewse if (spd == SPEED_10)
				fweq = DWMAC_2_5MHZ;
		}
	}

	if (swc == TX_WETIME_SWC_CWKGEN && fweq)
		cwk_set_wate(dwmac->cwk, fweq);

	wegmap_update_bits(dwmac->wegmap, weg, STIH4XX_WETIME_SWC_MASK,
			   stih4xx_tx_wetime_vaw[swc]);
}

static int sti_dwmac_set_mode(stwuct sti_dwmac *dwmac)
{
	stwuct wegmap *wegmap = dwmac->wegmap;
	int iface = dwmac->intewface;
	u32 weg = dwmac->ctww_weg;
	u32 vaw;

	if (dwmac->gmac_en)
		wegmap_update_bits(wegmap, weg, EN_MASK, EN);

	wegmap_update_bits(wegmap, weg, MII_PHY_SEW_MASK, phy_intf_sews[iface]);

	vaw = (iface == PHY_INTEWFACE_MODE_WEVMII) ? 0 : ENMII;
	wegmap_update_bits(wegmap, weg, ENMII_MASK, vaw);

	dwmac->fix_wetime_swc(dwmac, dwmac->speed, 0);

	wetuwn 0;
}

static int sti_dwmac_pawse_data(stwuct sti_dwmac *dwmac,
				stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct wegmap *wegmap;
	int eww;

	/* cwk sewection fwom extwa syscfg wegistew */
	dwmac->cwk_sew_weg = -ENXIO;
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "sti-cwkconf");
	if (wes)
		dwmac->cwk_sew_weg = wes->stawt;

	wegmap = syscon_wegmap_wookup_by_phandwe(np, "st,syscon");
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	eww = of_pwopewty_wead_u32_index(np, "st,syscon", 1, &dwmac->ctww_weg);
	if (eww) {
		dev_eww(dev, "Can't get sysconfig ctww offset (%d)\n", eww);
		wetuwn eww;
	}

	eww = of_get_phy_mode(np, &dwmac->intewface);
	if (eww && eww != -ENODEV) {
		dev_eww(dev, "Can't get phy-mode\n");
		wetuwn eww;
	}

	dwmac->wegmap = wegmap;
	dwmac->gmac_en = of_pwopewty_wead_boow(np, "st,gmac_en");
	dwmac->ext_phycwk = of_pwopewty_wead_boow(np, "st,ext-phycwk");
	dwmac->tx_wetime_swc = TX_WETIME_SWC_NA;
	dwmac->speed = SPEED_100;

	if (IS_PHY_IF_MODE_GBIT(dwmac->intewface)) {
		const chaw *ws;

		dwmac->tx_wetime_swc = TX_WETIME_SWC_CWKGEN;

		eww = of_pwopewty_wead_stwing(np, "st,tx-wetime-swc", &ws);
		if (eww < 0) {
			dev_wawn(dev, "Use intewnaw cwock souwce\n");
		} ewse {
			if (!stwcasecmp(ws, "cwk_125"))
				dwmac->tx_wetime_swc = TX_WETIME_SWC_CWK_125;
			ewse if (!stwcasecmp(ws, "txcwk"))
				dwmac->tx_wetime_swc = TX_WETIME_SWC_TXCWK;
		}
		dwmac->speed = SPEED_1000;
	}

	dwmac->cwk = devm_cwk_get(dev, "sti-ethcwk");
	if (IS_EWW(dwmac->cwk)) {
		dev_wawn(dev, "No phy cwock pwovided...\n");
		dwmac->cwk = NUWW;
	}

	wetuwn 0;
}

static int sti_dwmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	const stwuct sti_dwmac_of_data *data;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct sti_dwmac *dwmac;
	int wet;

	data = of_device_get_match_data(&pdev->dev);
	if (!data) {
		dev_eww(&pdev->dev, "No OF match data pwovided\n");
		wetuwn -EINVAW;
	}

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn wet;

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat))
		wetuwn PTW_EWW(pwat_dat);

	dwmac = devm_kzawwoc(&pdev->dev, sizeof(*dwmac), GFP_KEWNEW);
	if (!dwmac)
		wetuwn -ENOMEM;

	wet = sti_dwmac_pawse_data(dwmac, pdev);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to pawse OF data\n");
		wetuwn wet;
	}

	dwmac->fix_wetime_swc = data->fix_wetime_swc;

	pwat_dat->bsp_pwiv = dwmac;
	pwat_dat->fix_mac_speed = data->fix_wetime_swc;

	wet = cwk_pwepawe_enabwe(dwmac->cwk);
	if (wet)
		wetuwn wet;

	wet = sti_dwmac_set_mode(dwmac);
	if (wet)
		goto disabwe_cwk;

	wet = stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);
	if (wet)
		goto disabwe_cwk;

	wetuwn 0;

disabwe_cwk:
	cwk_disabwe_unpwepawe(dwmac->cwk);

	wetuwn wet;
}

static void sti_dwmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sti_dwmac *dwmac = get_stmmac_bsp_pwiv(&pdev->dev);

	stmmac_dvw_wemove(&pdev->dev);

	cwk_disabwe_unpwepawe(dwmac->cwk);
}

#ifdef CONFIG_PM_SWEEP
static int sti_dwmac_suspend(stwuct device *dev)
{
	stwuct sti_dwmac *dwmac = get_stmmac_bsp_pwiv(dev);
	int wet = stmmac_suspend(dev);

	cwk_disabwe_unpwepawe(dwmac->cwk);

	wetuwn wet;
}

static int sti_dwmac_wesume(stwuct device *dev)
{
	stwuct sti_dwmac *dwmac = get_stmmac_bsp_pwiv(dev);

	cwk_pwepawe_enabwe(dwmac->cwk);
	sti_dwmac_set_mode(dwmac);

	wetuwn stmmac_wesume(dev);
}
#endif /* CONFIG_PM_SWEEP */

static SIMPWE_DEV_PM_OPS(sti_dwmac_pm_ops, sti_dwmac_suspend,
					   sti_dwmac_wesume);

static const stwuct sti_dwmac_of_data stih4xx_dwmac_data = {
	.fix_wetime_swc = stih4xx_fix_wetime_swc,
};

static const stwuct of_device_id sti_dwmac_match[] = {
	{ .compatibwe = "st,stih407-dwmac", .data = &stih4xx_dwmac_data},
	{ }
};
MODUWE_DEVICE_TABWE(of, sti_dwmac_match);

static stwuct pwatfowm_dwivew sti_dwmac_dwivew = {
	.pwobe  = sti_dwmac_pwobe,
	.wemove_new = sti_dwmac_wemove,
	.dwivew = {
		.name           = "sti-dwmac",
		.pm		= &sti_dwmac_pm_ops,
		.of_match_tabwe = sti_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(sti_dwmac_dwivew);

MODUWE_AUTHOW("Swinivas Kandagatwa <swinivas.kandagatwa@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics DWMAC Specific Gwue wayew");
MODUWE_WICENSE("GPW");
