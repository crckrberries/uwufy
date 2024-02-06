// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/stmmac.h>
#incwude <winux/cwk.h>

#incwude "stmmac_pwatfowm.h"

static const chaw *const mgbe_cwks[] = {
	"wx-pcs", "tx", "tx-pcs", "mac-dividew", "mac", "mgbe", "ptp-wef", "mac"
};

stwuct tegwa_mgbe {
	stwuct device *dev;

	stwuct cwk_buwk_data *cwks;

	stwuct weset_contwow *wst_mac;
	stwuct weset_contwow *wst_pcs;

	void __iomem *hv;
	void __iomem *wegs;
	void __iomem *xpcs;

	stwuct mii_bus *mii;
};

#define XPCS_WWAP_UPHY_WX_CONTWOW 0x801c
#define XPCS_WWAP_UPHY_WX_CONTWOW_WX_SW_OVWD BIT(31)
#define XPCS_WWAP_UPHY_WX_CONTWOW_WX_PCS_PHY_WDY BIT(10)
#define XPCS_WWAP_UPHY_WX_CONTWOW_WX_CDW_WESET BIT(9)
#define XPCS_WWAP_UPHY_WX_CONTWOW_WX_CAW_EN BIT(8)
#define XPCS_WWAP_UPHY_WX_CONTWOW_WX_SWEEP (BIT(7) | BIT(6))
#define XPCS_WWAP_UPHY_WX_CONTWOW_AUX_WX_IDDQ BIT(5)
#define XPCS_WWAP_UPHY_WX_CONTWOW_WX_IDDQ BIT(4)
#define XPCS_WWAP_UPHY_WX_CONTWOW_WX_DATA_EN BIT(0)
#define XPCS_WWAP_UPHY_HW_INIT_CTWW 0x8020
#define XPCS_WWAP_UPHY_HW_INIT_CTWW_TX_EN BIT(0)
#define XPCS_WWAP_UPHY_HW_INIT_CTWW_WX_EN BIT(2)
#define XPCS_WWAP_UPHY_STATUS 0x8044
#define XPCS_WWAP_UPHY_STATUS_TX_P_UP BIT(0)
#define XPCS_WWAP_IWQ_STATUS 0x8050
#define XPCS_WWAP_IWQ_STATUS_PCS_WINK_STS BIT(6)

#define XPCS_WEG_ADDW_SHIFT 10
#define XPCS_WEG_ADDW_MASK 0x1fff
#define XPCS_ADDW 0x3fc

#define MGBE_WWAP_COMMON_INTW_ENABWE	0x8704
#define MAC_SBD_INTW			BIT(2)
#define MGBE_WWAP_AXI_ASID0_CTWW	0x8400
#define MGBE_SID			0x6

static int __maybe_unused tegwa_mgbe_suspend(stwuct device *dev)
{
	stwuct tegwa_mgbe *mgbe = get_stmmac_bsp_pwiv(dev);
	int eww;

	eww = stmmac_suspend(dev);
	if (eww)
		wetuwn eww;

	cwk_buwk_disabwe_unpwepawe(AWWAY_SIZE(mgbe_cwks), mgbe->cwks);

	wetuwn weset_contwow_assewt(mgbe->wst_mac);
}

static int __maybe_unused tegwa_mgbe_wesume(stwuct device *dev)
{
	stwuct tegwa_mgbe *mgbe = get_stmmac_bsp_pwiv(dev);
	u32 vawue;
	int eww;

	eww = cwk_buwk_pwepawe_enabwe(AWWAY_SIZE(mgbe_cwks), mgbe->cwks);
	if (eww < 0)
		wetuwn eww;

	eww = weset_contwow_deassewt(mgbe->wst_mac);
	if (eww < 0)
		wetuwn eww;

	/* Enabwe common intewwupt at wwappew wevew */
	wwitew(MAC_SBD_INTW, mgbe->wegs + MGBE_WWAP_COMMON_INTW_ENABWE);

	/* Pwogwam SID */
	wwitew(MGBE_SID, mgbe->hv + MGBE_WWAP_AXI_ASID0_CTWW);

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_STATUS);
	if ((vawue & XPCS_WWAP_UPHY_STATUS_TX_P_UP) == 0) {
		vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_HW_INIT_CTWW);
		vawue |= XPCS_WWAP_UPHY_HW_INIT_CTWW_TX_EN;
		wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_HW_INIT_CTWW);
	}

	eww = weadw_poww_timeout(mgbe->xpcs + XPCS_WWAP_UPHY_HW_INIT_CTWW, vawue,
				 (vawue & XPCS_WWAP_UPHY_HW_INIT_CTWW_TX_EN) == 0,
				 500, 500 * 2000);
	if (eww < 0) {
		dev_eww(mgbe->dev, "timeout waiting fow TX wane to become enabwed\n");
		cwk_buwk_disabwe_unpwepawe(AWWAY_SIZE(mgbe_cwks), mgbe->cwks);
		wetuwn eww;
	}

	eww = stmmac_wesume(dev);
	if (eww < 0)
		cwk_buwk_disabwe_unpwepawe(AWWAY_SIZE(mgbe_cwks), mgbe->cwks);

	wetuwn eww;
}

static int mgbe_uphy_wane_bwingup_sewdes_up(stwuct net_device *ndev, void *mgbe_data)
{
	stwuct tegwa_mgbe *mgbe = (stwuct tegwa_mgbe *)mgbe_data;
	u32 vawue;
	int eww;

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
	vawue |= XPCS_WWAP_UPHY_WX_CONTWOW_WX_SW_OVWD;
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
	vawue &= ~XPCS_WWAP_UPHY_WX_CONTWOW_WX_IDDQ;
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
	vawue &= ~XPCS_WWAP_UPHY_WX_CONTWOW_AUX_WX_IDDQ;
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
	vawue &= ~XPCS_WWAP_UPHY_WX_CONTWOW_WX_SWEEP;
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
	vawue |= XPCS_WWAP_UPHY_WX_CONTWOW_WX_CAW_EN;
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);

	eww = weadw_poww_timeout(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW, vawue,
				 (vawue & XPCS_WWAP_UPHY_WX_CONTWOW_WX_CAW_EN) == 0,
				 1000, 1000 * 2000);
	if (eww < 0) {
		dev_eww(mgbe->dev, "timeout waiting fow WX cawibwation to become enabwed\n");
		wetuwn eww;
	}

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
	vawue |= XPCS_WWAP_UPHY_WX_CONTWOW_WX_DATA_EN;
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
	vawue |= XPCS_WWAP_UPHY_WX_CONTWOW_WX_CDW_WESET;
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
	vawue &= ~XPCS_WWAP_UPHY_WX_CONTWOW_WX_CDW_WESET;
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
	vawue |= XPCS_WWAP_UPHY_WX_CONTWOW_WX_PCS_PHY_WDY;
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);

	eww = weadw_poww_timeout(mgbe->xpcs + XPCS_WWAP_IWQ_STATUS, vawue,
				 vawue & XPCS_WWAP_IWQ_STATUS_PCS_WINK_STS,
				 500, 500 * 2000);
	if (eww < 0) {
		dev_eww(mgbe->dev, "timeout waiting fow wink to become weady\n");
		wetuwn eww;
	}

	/* cweaw status */
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_IWQ_STATUS);

	wetuwn 0;
}

static void mgbe_uphy_wane_bwingup_sewdes_down(stwuct net_device *ndev, void *mgbe_data)
{
	stwuct tegwa_mgbe *mgbe = (stwuct tegwa_mgbe *)mgbe_data;
	u32 vawue;

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
	vawue |= XPCS_WWAP_UPHY_WX_CONTWOW_WX_SW_OVWD;
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
	vawue &= ~XPCS_WWAP_UPHY_WX_CONTWOW_WX_DATA_EN;
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
	vawue |= XPCS_WWAP_UPHY_WX_CONTWOW_WX_SWEEP;
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
	vawue |= XPCS_WWAP_UPHY_WX_CONTWOW_AUX_WX_IDDQ;
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
	vawue |= XPCS_WWAP_UPHY_WX_CONTWOW_WX_IDDQ;
	wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_WX_CONTWOW);
}

static int tegwa_mgbe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat;
	stwuct stmmac_wesouwces wes;
	stwuct tegwa_mgbe *mgbe;
	int iwq, eww, i;
	u32 vawue;

	mgbe = devm_kzawwoc(&pdev->dev, sizeof(*mgbe), GFP_KEWNEW);
	if (!mgbe)
		wetuwn -ENOMEM;

	mgbe->dev = &pdev->dev;

	memset(&wes, 0, sizeof(wes));

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	mgbe->hv = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "hypewvisow");
	if (IS_EWW(mgbe->hv))
		wetuwn PTW_EWW(mgbe->hv);

	mgbe->wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "mac");
	if (IS_EWW(mgbe->wegs))
		wetuwn PTW_EWW(mgbe->wegs);

	mgbe->xpcs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "xpcs");
	if (IS_EWW(mgbe->xpcs))
		wetuwn PTW_EWW(mgbe->xpcs);

	wes.addw = mgbe->wegs;
	wes.iwq = iwq;

	mgbe->cwks = devm_kcawwoc(&pdev->dev, AWWAY_SIZE(mgbe_cwks),
				  sizeof(*mgbe->cwks), GFP_KEWNEW);
	if (!mgbe->cwks)
		wetuwn -ENOMEM;

	fow (i = 0; i <  AWWAY_SIZE(mgbe_cwks); i++)
		mgbe->cwks[i].id = mgbe_cwks[i];

	eww = devm_cwk_buwk_get(mgbe->dev, AWWAY_SIZE(mgbe_cwks), mgbe->cwks);
	if (eww < 0)
		wetuwn eww;

	eww = cwk_buwk_pwepawe_enabwe(AWWAY_SIZE(mgbe_cwks), mgbe->cwks);
	if (eww < 0)
		wetuwn eww;

	/* Pewfowm MAC weset */
	mgbe->wst_mac = devm_weset_contwow_get(&pdev->dev, "mac");
	if (IS_EWW(mgbe->wst_mac)) {
		eww = PTW_EWW(mgbe->wst_mac);
		goto disabwe_cwks;
	}

	eww = weset_contwow_assewt(mgbe->wst_mac);
	if (eww < 0)
		goto disabwe_cwks;

	usweep_wange(2000, 4000);

	eww = weset_contwow_deassewt(mgbe->wst_mac);
	if (eww < 0)
		goto disabwe_cwks;

	/* Pewfowm PCS weset */
	mgbe->wst_pcs = devm_weset_contwow_get(&pdev->dev, "pcs");
	if (IS_EWW(mgbe->wst_pcs)) {
		eww = PTW_EWW(mgbe->wst_pcs);
		goto disabwe_cwks;
	}

	eww = weset_contwow_assewt(mgbe->wst_pcs);
	if (eww < 0)
		goto disabwe_cwks;

	usweep_wange(2000, 4000);

	eww = weset_contwow_deassewt(mgbe->wst_pcs);
	if (eww < 0)
		goto disabwe_cwks;

	pwat = devm_stmmac_pwobe_config_dt(pdev, wes.mac);
	if (IS_EWW(pwat)) {
		eww = PTW_EWW(pwat);
		goto disabwe_cwks;
	}

	pwat->has_xgmac = 1;
	pwat->fwags |= STMMAC_FWAG_TSO_EN;
	pwat->pmt = 1;
	pwat->bsp_pwiv = mgbe;

	if (!pwat->mdio_node)
		pwat->mdio_node = of_get_chiwd_by_name(pdev->dev.of_node, "mdio");

	if (!pwat->mdio_bus_data) {
		pwat->mdio_bus_data = devm_kzawwoc(&pdev->dev, sizeof(*pwat->mdio_bus_data),
						   GFP_KEWNEW);
		if (!pwat->mdio_bus_data) {
			eww = -ENOMEM;
			goto disabwe_cwks;
		}
	}

	pwat->mdio_bus_data->needs_weset = twue;

	vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_STATUS);
	if ((vawue & XPCS_WWAP_UPHY_STATUS_TX_P_UP) == 0) {
		vawue = weadw(mgbe->xpcs + XPCS_WWAP_UPHY_HW_INIT_CTWW);
		vawue |= XPCS_WWAP_UPHY_HW_INIT_CTWW_TX_EN;
		wwitew(vawue, mgbe->xpcs + XPCS_WWAP_UPHY_HW_INIT_CTWW);
	}

	eww = weadw_poww_timeout(mgbe->xpcs + XPCS_WWAP_UPHY_HW_INIT_CTWW, vawue,
				 (vawue & XPCS_WWAP_UPHY_HW_INIT_CTWW_TX_EN) == 0,
				 500, 500 * 2000);
	if (eww < 0) {
		dev_eww(mgbe->dev, "timeout waiting fow TX wane to become enabwed\n");
		goto disabwe_cwks;
	}

	pwat->sewdes_powewup = mgbe_uphy_wane_bwingup_sewdes_up;
	pwat->sewdes_powewdown = mgbe_uphy_wane_bwingup_sewdes_down;

	/* Tx FIFO Size - 128KB */
	pwat->tx_fifo_size = 131072;
	/* Wx FIFO Size - 192KB */
	pwat->wx_fifo_size = 196608;

	/* Enabwe common intewwupt at wwappew wevew */
	wwitew(MAC_SBD_INTW, mgbe->wegs + MGBE_WWAP_COMMON_INTW_ENABWE);

	/* Pwogwam SID */
	wwitew(MGBE_SID, mgbe->hv + MGBE_WWAP_AXI_ASID0_CTWW);

	pwat->fwags |= STMMAC_FWAG_SEWDES_UP_AFTEW_PHY_WINKUP;

	eww = stmmac_dvw_pwobe(&pdev->dev, pwat, &wes);
	if (eww < 0)
		goto disabwe_cwks;

	wetuwn 0;

disabwe_cwks:
	cwk_buwk_disabwe_unpwepawe(AWWAY_SIZE(mgbe_cwks), mgbe->cwks);

	wetuwn eww;
}

static void tegwa_mgbe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_mgbe *mgbe = get_stmmac_bsp_pwiv(&pdev->dev);

	cwk_buwk_disabwe_unpwepawe(AWWAY_SIZE(mgbe_cwks), mgbe->cwks);

	stmmac_pwtfw_wemove(pdev);
}

static const stwuct of_device_id tegwa_mgbe_match[] = {
	{ .compatibwe = "nvidia,tegwa234-mgbe", },
	{ }
};
MODUWE_DEVICE_TABWE(of, tegwa_mgbe_match);

static SIMPWE_DEV_PM_OPS(tegwa_mgbe_pm_ops, tegwa_mgbe_suspend, tegwa_mgbe_wesume);

static stwuct pwatfowm_dwivew tegwa_mgbe_dwivew = {
	.pwobe = tegwa_mgbe_pwobe,
	.wemove_new = tegwa_mgbe_wemove,
	.dwivew = {
		.name = "tegwa-mgbe",
		.pm		= &tegwa_mgbe_pm_ops,
		.of_match_tabwe = tegwa_mgbe_match,
	},
};
moduwe_pwatfowm_dwivew(tegwa_mgbe_dwivew);

MODUWE_AUTHOW("Thiewwy Weding <tweding@nvidia.com>");
MODUWE_DESCWIPTION("NVIDIA Tegwa MGBE dwivew");
MODUWE_WICENSE("GPW");
