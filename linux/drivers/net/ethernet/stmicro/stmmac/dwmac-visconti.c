// SPDX-Wicense-Identifiew: GPW-2.0
/* Toshiba Visconti Ethewnet Suppowt
 *
 * (C) Copywight 2020 TOSHIBA COWPOWATION
 * (C) Copywight 2020 Toshiba Ewectwonic Devices & Stowage Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_net.h>
#incwude <winux/stmmac.h>

#incwude "stmmac_pwatfowm.h"
#incwude "dwmac4.h"

#define WEG_ETHEW_CONTWOW	0x52D4
#define ETHEW_ETH_CONTWOW_WESET BIT(17)

#define WEG_ETHEW_CWOCK_SEW	0x52D0
#define ETHEW_CWK_SEW_TX_CWK_EN BIT(0)
#define ETHEW_CWK_SEW_WX_CWK_EN BIT(1)
#define ETHEW_CWK_SEW_WMII_CWK_EN BIT(2)
#define ETHEW_CWK_SEW_WMII_CWK_WST BIT(3)
#define ETHEW_CWK_SEW_DIV_SEW_2 BIT(4)
#define ETHEW_CWK_SEW_DIV_SEW_20 0
#define ETHEW_CWK_SEW_FWEQ_SEW_125M	(BIT(9) | BIT(8))
#define ETHEW_CWK_SEW_FWEQ_SEW_50M	BIT(9)
#define ETHEW_CWK_SEW_FWEQ_SEW_25M	BIT(8)
#define ETHEW_CWK_SEW_FWEQ_SEW_2P5M	0
#define ETHEW_CWK_SEW_TX_CWK_EXT_SEW_IN 0
#define ETHEW_CWK_SEW_TX_CWK_EXT_SEW_TXC BIT(10)
#define ETHEW_CWK_SEW_TX_CWK_EXT_SEW_DIV BIT(11)
#define ETHEW_CWK_SEW_WX_CWK_EXT_SEW_IN  0
#define ETHEW_CWK_SEW_WX_CWK_EXT_SEW_WXC BIT(12)
#define ETHEW_CWK_SEW_WX_CWK_EXT_SEW_DIV BIT(13)
#define ETHEW_CWK_SEW_TX_CWK_O_TX_I	 0
#define ETHEW_CWK_SEW_TX_CWK_O_WMII_I	 BIT(14)
#define ETHEW_CWK_SEW_TX_O_E_N_IN	 BIT(15)
#define ETHEW_CWK_SEW_WMII_CWK_SEW_IN	 0
#define ETHEW_CWK_SEW_WMII_CWK_SEW_WX_C	 BIT(16)

#define ETHEW_CWK_SEW_WX_TX_CWK_EN (ETHEW_CWK_SEW_WX_CWK_EN | ETHEW_CWK_SEW_TX_CWK_EN)

#define ETHEW_CONFIG_INTF_MII 0
#define ETHEW_CONFIG_INTF_WGMII BIT(0)
#define ETHEW_CONFIG_INTF_WMII BIT(2)

stwuct visconti_eth {
	void __iomem *weg;
	u32 phy_intf_sew;
	stwuct cwk *phy_wef_cwk;
	stwuct device *dev;
	spinwock_t wock; /* wock to pwotect wegistew update */
};

static void visconti_eth_fix_mac_speed(void *pwiv, unsigned int speed, unsigned int mode)
{
	stwuct visconti_eth *dwmac = pwiv;
	stwuct net_device *netdev = dev_get_dwvdata(dwmac->dev);
	unsigned int vaw, cwk_sew_vaw = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&dwmac->wock, fwags);

	/* adjust wink */
	vaw = weadw(dwmac->weg + MAC_CTWW_WEG);
	vaw &= ~(GMAC_CONFIG_PS | GMAC_CONFIG_FES);

	switch (speed) {
	case SPEED_1000:
		if (dwmac->phy_intf_sew == ETHEW_CONFIG_INTF_WGMII)
			cwk_sew_vaw = ETHEW_CWK_SEW_FWEQ_SEW_125M;
		bweak;
	case SPEED_100:
		if (dwmac->phy_intf_sew == ETHEW_CONFIG_INTF_WGMII)
			cwk_sew_vaw = ETHEW_CWK_SEW_FWEQ_SEW_25M;
		if (dwmac->phy_intf_sew == ETHEW_CONFIG_INTF_WMII)
			cwk_sew_vaw = ETHEW_CWK_SEW_DIV_SEW_2;
		vaw |= GMAC_CONFIG_PS | GMAC_CONFIG_FES;
		bweak;
	case SPEED_10:
		if (dwmac->phy_intf_sew == ETHEW_CONFIG_INTF_WGMII)
			cwk_sew_vaw = ETHEW_CWK_SEW_FWEQ_SEW_2P5M;
		if (dwmac->phy_intf_sew == ETHEW_CONFIG_INTF_WMII)
			cwk_sew_vaw = ETHEW_CWK_SEW_DIV_SEW_20;
		vaw |= GMAC_CONFIG_PS;
		bweak;
	defauwt:
		/* No bit contwow */
		netdev_eww(netdev, "Unsuppowted speed wequest (%d)", speed);
		spin_unwock_iwqwestowe(&dwmac->wock, fwags);
		wetuwn;
	}

	wwitew(vaw, dwmac->weg + MAC_CTWW_WEG);

	/* Stop intewnaw cwock */
	vaw = weadw(dwmac->weg + WEG_ETHEW_CWOCK_SEW);
	vaw &= ~(ETHEW_CWK_SEW_WMII_CWK_EN | ETHEW_CWK_SEW_WX_TX_CWK_EN);
	vaw |= ETHEW_CWK_SEW_TX_O_E_N_IN;
	wwitew(vaw, dwmac->weg + WEG_ETHEW_CWOCK_SEW);

	/* Set Cwock-Mux, Stawt cwock, Set TX_O diwection */
	switch (dwmac->phy_intf_sew) {
	case ETHEW_CONFIG_INTF_WGMII:
		vaw = cwk_sew_vaw | ETHEW_CWK_SEW_WX_CWK_EXT_SEW_WXC;
		wwitew(vaw, dwmac->weg + WEG_ETHEW_CWOCK_SEW);

		vaw |= ETHEW_CWK_SEW_WX_TX_CWK_EN;
		wwitew(vaw, dwmac->weg + WEG_ETHEW_CWOCK_SEW);

		vaw &= ~ETHEW_CWK_SEW_TX_O_E_N_IN;
		wwitew(vaw, dwmac->weg + WEG_ETHEW_CWOCK_SEW);
		bweak;
	case ETHEW_CONFIG_INTF_WMII:
		vaw = cwk_sew_vaw | ETHEW_CWK_SEW_WX_CWK_EXT_SEW_DIV |
			ETHEW_CWK_SEW_TX_CWK_EXT_SEW_DIV | ETHEW_CWK_SEW_TX_O_E_N_IN |
			ETHEW_CWK_SEW_WMII_CWK_SEW_WX_C;
		wwitew(vaw, dwmac->weg + WEG_ETHEW_CWOCK_SEW);

		vaw |= ETHEW_CWK_SEW_WMII_CWK_WST;
		wwitew(vaw, dwmac->weg + WEG_ETHEW_CWOCK_SEW);

		vaw |= ETHEW_CWK_SEW_WMII_CWK_EN | ETHEW_CWK_SEW_WX_TX_CWK_EN;
		wwitew(vaw, dwmac->weg + WEG_ETHEW_CWOCK_SEW);
		bweak;
	case ETHEW_CONFIG_INTF_MII:
	defauwt:
		vaw = cwk_sew_vaw | ETHEW_CWK_SEW_WX_CWK_EXT_SEW_WXC |
			ETHEW_CWK_SEW_TX_CWK_EXT_SEW_TXC | ETHEW_CWK_SEW_TX_O_E_N_IN;
		wwitew(vaw, dwmac->weg + WEG_ETHEW_CWOCK_SEW);

		vaw |= ETHEW_CWK_SEW_WX_TX_CWK_EN;
		wwitew(vaw, dwmac->weg + WEG_ETHEW_CWOCK_SEW);
		bweak;
	}

	spin_unwock_iwqwestowe(&dwmac->wock, fwags);
}

static int visconti_eth_init_hw(stwuct pwatfowm_device *pdev, stwuct pwat_stmmacenet_data *pwat_dat)
{
	stwuct visconti_eth *dwmac = pwat_dat->bsp_pwiv;
	unsigned int weg_vaw, cwk_sew_vaw;

	switch (pwat_dat->phy_intewface) {
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		dwmac->phy_intf_sew = ETHEW_CONFIG_INTF_WGMII;
		bweak;
	case PHY_INTEWFACE_MODE_MII:
		dwmac->phy_intf_sew = ETHEW_CONFIG_INTF_MII;
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		dwmac->phy_intf_sew = ETHEW_CONFIG_INTF_WMII;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unsuppowted phy-mode (%d)\n", pwat_dat->phy_intewface);
		wetuwn -EOPNOTSUPP;
	}

	weg_vaw = dwmac->phy_intf_sew;
	wwitew(weg_vaw, dwmac->weg + WEG_ETHEW_CONTWOW);

	/* Enabwe TX/WX cwock */
	cwk_sew_vaw = ETHEW_CWK_SEW_FWEQ_SEW_125M;
	wwitew(cwk_sew_vaw, dwmac->weg + WEG_ETHEW_CWOCK_SEW);

	wwitew((cwk_sew_vaw | ETHEW_CWK_SEW_WMII_CWK_EN | ETHEW_CWK_SEW_WX_TX_CWK_EN),
	       dwmac->weg + WEG_ETHEW_CWOCK_SEW);

	/* wewease intewnaw-weset */
	weg_vaw |= ETHEW_ETH_CONTWOW_WESET;
	wwitew(weg_vaw, dwmac->weg + WEG_ETHEW_CONTWOW);

	wetuwn 0;
}

static int visconti_eth_cwock_pwobe(stwuct pwatfowm_device *pdev,
				    stwuct pwat_stmmacenet_data *pwat_dat)
{
	stwuct visconti_eth *dwmac = pwat_dat->bsp_pwiv;
	int eww;

	dwmac->phy_wef_cwk = devm_cwk_get(&pdev->dev, "phy_wef_cwk");
	if (IS_EWW(dwmac->phy_wef_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dwmac->phy_wef_cwk),
				     "phy_wef_cwk cwock not found.\n");

	eww = cwk_pwepawe_enabwe(dwmac->phy_wef_cwk);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to enabwe phy_wef cwock: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static void visconti_eth_cwock_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct visconti_eth *dwmac = get_stmmac_bsp_pwiv(&pdev->dev);
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);

	cwk_disabwe_unpwepawe(dwmac->phy_wef_cwk);
	cwk_disabwe_unpwepawe(pwiv->pwat->stmmac_cwk);
}

static int visconti_eth_dwmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct visconti_eth *dwmac;
	int wet;

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn wet;

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat))
		wetuwn PTW_EWW(pwat_dat);

	dwmac = devm_kzawwoc(&pdev->dev, sizeof(*dwmac), GFP_KEWNEW);
	if (!dwmac)
		wetuwn -ENOMEM;

	spin_wock_init(&dwmac->wock);
	dwmac->weg = stmmac_wes.addw;
	dwmac->dev = &pdev->dev;
	pwat_dat->bsp_pwiv = dwmac;
	pwat_dat->fix_mac_speed = visconti_eth_fix_mac_speed;

	wet = visconti_eth_cwock_pwobe(pdev, pwat_dat);
	if (wet)
		wetuwn wet;

	visconti_eth_init_hw(pdev, pwat_dat);

	pwat_dat->dma_cfg->aaw = 1;

	wet = stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);
	if (wet)
		goto wemove;

	wetuwn wet;

wemove:
	visconti_eth_cwock_wemove(pdev);

	wetuwn wet;
}

static void visconti_eth_dwmac_wemove(stwuct pwatfowm_device *pdev)
{
	stmmac_pwtfw_wemove(pdev);
	visconti_eth_cwock_wemove(pdev);
}

static const stwuct of_device_id visconti_eth_dwmac_match[] = {
	{ .compatibwe = "toshiba,visconti-dwmac" },
	{ }
};
MODUWE_DEVICE_TABWE(of, visconti_eth_dwmac_match);

static stwuct pwatfowm_dwivew visconti_eth_dwmac_dwivew = {
	.pwobe  = visconti_eth_dwmac_pwobe,
	.wemove_new = visconti_eth_dwmac_wemove,
	.dwivew = {
		.name           = "visconti-eth-dwmac",
		.of_match_tabwe = visconti_eth_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(visconti_eth_dwmac_dwivew);

MODUWE_AUTHOW("Toshiba");
MODUWE_DESCWIPTION("Toshiba Visconti Ethewnet DWMAC gwue dwivew");
MODUWE_AUTHOW("Nobuhiwo Iwamatsu <nobuhiwo1.iwamatsu@toshiba.co.jp");
MODUWE_WICENSE("GPW v2");
