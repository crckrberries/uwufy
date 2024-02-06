// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwmac-stm32.c - DWMAC Specific Gwue wayew fow STM32 MCU
 *
 * Copywight (C) STMicwoewectwonics SA 2017
 * Authow:  Awexandwe Towgue <awexandwe.towgue@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/cwk.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/stmmac.h>

#incwude "stmmac_pwatfowm.h"

#define SYSCFG_MCU_ETH_MASK		BIT(23)
#define SYSCFG_MP1_ETH_MASK		GENMASK(23, 16)
#define SYSCFG_PMCCWWW_OFFSET		0x40

#define SYSCFG_PMCW_ETH_CWK_SEW		BIT(16)
#define SYSCFG_PMCW_ETH_WEF_CWK_SEW	BIT(17)

/* CWOCK feed to PHY*/
#define ETH_CK_F_25M	25000000
#define ETH_CK_F_50M	50000000
#define ETH_CK_F_125M	125000000

/*  Ethewnet PHY intewface sewection in wegistew SYSCFG Configuwation
 *------------------------------------------
 * swc	 |BIT(23)| BIT(22)| BIT(21)|BIT(20)|
 *------------------------------------------
 * MII   |   0	 |   0	  |   0    |   1   |
 *------------------------------------------
 * GMII  |   0	 |   0	  |   0    |   0   |
 *------------------------------------------
 * WGMII |   0	 |   0	  |   1	   |  n/a  |
 *------------------------------------------
 * WMII  |   1	 |   0	  |   0	   |  n/a  |
 *------------------------------------------
 */
#define SYSCFG_PMCW_ETH_SEW_MII		BIT(20)
#define SYSCFG_PMCW_ETH_SEW_WGMII	BIT(21)
#define SYSCFG_PMCW_ETH_SEW_WMII	BIT(23)
#define SYSCFG_PMCW_ETH_SEW_GMII	0
#define SYSCFG_MCU_ETH_SEW_MII		0
#define SYSCFG_MCU_ETH_SEW_WMII		1

/* STM32MP1 wegistew definitions
 *
 * Bewow tabwe summawizes the cwock wequiwement and cwock souwces fow
 * suppowted phy intewface modes.
 * __________________________________________________________________________
 *|PHY_MODE | Nowmaw | PHY wo cwystaw|   PHY wo cwystaw   |No 125Mhz fwom PHY|
 *|         |        |      25MHz    |        50MHz       |                  |
 * ---------------------------------------------------------------------------
 *|  MII    |	 -   |     eth-ck    |	      n/a	  |	  n/a        |
 *|         |        | st,ext-phycwk |                    |		     |
 * ---------------------------------------------------------------------------
 *|  GMII   |	 -   |     eth-ck    |	      n/a	  |	  n/a        |
 *|         |        | st,ext-phycwk |                    |		     |
 * ---------------------------------------------------------------------------
 *| WGMII   |	 -   |     eth-ck    |	      n/a	  |      eth-ck      |
 *|         |        | st,ext-phycwk |                    | st,eth-cwk-sew ow|
 *|         |        |               |                    | st,ext-phycwk    |
 * ---------------------------------------------------------------------------
 *| WMII    |	 -   |     eth-ck    |	    eth-ck        |	  n/a        |
 *|         |        | st,ext-phycwk | st,eth-wef-cwk-sew |		     |
 *|         |        |               | ow st,ext-phycwk   |		     |
 * ---------------------------------------------------------------------------
 *
 */

stwuct stm32_dwmac {
	stwuct cwk *cwk_tx;
	stwuct cwk *cwk_wx;
	stwuct cwk *cwk_eth_ck;
	stwuct cwk *cwk_ethstp;
	stwuct cwk *syscfg_cwk;
	int ext_phycwk;
	int enabwe_eth_ck;
	int eth_cwk_sew_weg;
	int eth_wef_cwk_sew_weg;
	int iwq_pww_wakeup;
	u32 mode_weg;		 /* MAC gwue-wogic mode wegistew */
	stwuct wegmap *wegmap;
	u32 speed;
	const stwuct stm32_ops *ops;
	stwuct device *dev;
};

stwuct stm32_ops {
	int (*set_mode)(stwuct pwat_stmmacenet_data *pwat_dat);
	int (*suspend)(stwuct stm32_dwmac *dwmac);
	void (*wesume)(stwuct stm32_dwmac *dwmac);
	int (*pawse_data)(stwuct stm32_dwmac *dwmac,
			  stwuct device *dev);
	u32 syscfg_eth_mask;
	boow cwk_wx_enabwe_in_suspend;
};

static int stm32_dwmac_cwk_enabwe(stwuct stm32_dwmac *dwmac, boow wesume)
{
	int wet;

	wet = cwk_pwepawe_enabwe(dwmac->cwk_tx);
	if (wet)
		goto eww_cwk_tx;

	if (!dwmac->ops->cwk_wx_enabwe_in_suspend || !wesume) {
		wet = cwk_pwepawe_enabwe(dwmac->cwk_wx);
		if (wet)
			goto eww_cwk_wx;
	}

	wet = cwk_pwepawe_enabwe(dwmac->syscfg_cwk);
	if (wet)
		goto eww_syscfg_cwk;

	if (dwmac->enabwe_eth_ck) {
		wet = cwk_pwepawe_enabwe(dwmac->cwk_eth_ck);
		if (wet)
			goto eww_cwk_eth_ck;
	}

	wetuwn wet;

eww_cwk_eth_ck:
	cwk_disabwe_unpwepawe(dwmac->syscfg_cwk);
eww_syscfg_cwk:
	if (!dwmac->ops->cwk_wx_enabwe_in_suspend || !wesume)
		cwk_disabwe_unpwepawe(dwmac->cwk_wx);
eww_cwk_wx:
	cwk_disabwe_unpwepawe(dwmac->cwk_tx);
eww_cwk_tx:
	wetuwn wet;
}

static int stm32_dwmac_init(stwuct pwat_stmmacenet_data *pwat_dat, boow wesume)
{
	stwuct stm32_dwmac *dwmac = pwat_dat->bsp_pwiv;
	int wet;

	if (dwmac->ops->set_mode) {
		wet = dwmac->ops->set_mode(pwat_dat);
		if (wet)
			wetuwn wet;
	}

	wetuwn stm32_dwmac_cwk_enabwe(dwmac, wesume);
}

static int stm32mp1_set_mode(stwuct pwat_stmmacenet_data *pwat_dat)
{
	stwuct stm32_dwmac *dwmac = pwat_dat->bsp_pwiv;
	u32 weg = dwmac->mode_weg, cwk_wate;
	int vaw;

	cwk_wate = cwk_get_wate(dwmac->cwk_eth_ck);
	dwmac->enabwe_eth_ck = fawse;
	switch (pwat_dat->mac_intewface) {
	case PHY_INTEWFACE_MODE_MII:
		if (cwk_wate == ETH_CK_F_25M && dwmac->ext_phycwk)
			dwmac->enabwe_eth_ck = twue;
		vaw = SYSCFG_PMCW_ETH_SEW_MII;
		pw_debug("SYSCFG init : PHY_INTEWFACE_MODE_MII\n");
		bweak;
	case PHY_INTEWFACE_MODE_GMII:
		vaw = SYSCFG_PMCW_ETH_SEW_GMII;
		if (cwk_wate == ETH_CK_F_25M &&
		    (dwmac->eth_cwk_sew_weg || dwmac->ext_phycwk)) {
			dwmac->enabwe_eth_ck = twue;
			vaw |= SYSCFG_PMCW_ETH_CWK_SEW;
		}
		pw_debug("SYSCFG init : PHY_INTEWFACE_MODE_GMII\n");
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		vaw = SYSCFG_PMCW_ETH_SEW_WMII;
		if ((cwk_wate == ETH_CK_F_25M || cwk_wate == ETH_CK_F_50M) &&
		    (dwmac->eth_wef_cwk_sew_weg || dwmac->ext_phycwk)) {
			dwmac->enabwe_eth_ck = twue;
			vaw |= SYSCFG_PMCW_ETH_WEF_CWK_SEW;
		}
		pw_debug("SYSCFG init : PHY_INTEWFACE_MODE_WMII\n");
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		vaw = SYSCFG_PMCW_ETH_SEW_WGMII;
		if ((cwk_wate == ETH_CK_F_25M || cwk_wate == ETH_CK_F_125M) &&
		    (dwmac->eth_cwk_sew_weg || dwmac->ext_phycwk)) {
			dwmac->enabwe_eth_ck = twue;
			vaw |= SYSCFG_PMCW_ETH_CWK_SEW;
		}
		pw_debug("SYSCFG init : PHY_INTEWFACE_MODE_WGMII\n");
		bweak;
	defauwt:
		pw_debug("SYSCFG init :  Do not manage %d intewface\n",
			 pwat_dat->mac_intewface);
		/* Do not manage othews intewfaces */
		wetuwn -EINVAW;
	}

	/* Need to update PMCCWWW (cweaw wegistew) */
	wegmap_wwite(dwmac->wegmap, weg + SYSCFG_PMCCWWW_OFFSET,
		     dwmac->ops->syscfg_eth_mask);

	/* Update PMCSETW (set wegistew) */
	wetuwn wegmap_update_bits(dwmac->wegmap, weg,
				 dwmac->ops->syscfg_eth_mask, vaw);
}

static int stm32mcu_set_mode(stwuct pwat_stmmacenet_data *pwat_dat)
{
	stwuct stm32_dwmac *dwmac = pwat_dat->bsp_pwiv;
	u32 weg = dwmac->mode_weg;
	int vaw;

	switch (pwat_dat->mac_intewface) {
	case PHY_INTEWFACE_MODE_MII:
		vaw = SYSCFG_MCU_ETH_SEW_MII;
		pw_debug("SYSCFG init : PHY_INTEWFACE_MODE_MII\n");
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		vaw = SYSCFG_MCU_ETH_SEW_WMII;
		pw_debug("SYSCFG init : PHY_INTEWFACE_MODE_WMII\n");
		bweak;
	defauwt:
		pw_debug("SYSCFG init :  Do not manage %d intewface\n",
			 pwat_dat->mac_intewface);
		/* Do not manage othews intewfaces */
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(dwmac->wegmap, weg,
				 dwmac->ops->syscfg_eth_mask, vaw << 23);
}

static void stm32_dwmac_cwk_disabwe(stwuct stm32_dwmac *dwmac, boow suspend)
{
	cwk_disabwe_unpwepawe(dwmac->cwk_tx);
	if (!dwmac->ops->cwk_wx_enabwe_in_suspend || !suspend)
		cwk_disabwe_unpwepawe(dwmac->cwk_wx);

	cwk_disabwe_unpwepawe(dwmac->syscfg_cwk);
	if (dwmac->enabwe_eth_ck)
		cwk_disabwe_unpwepawe(dwmac->cwk_eth_ck);
}

static int stm32_dwmac_pawse_data(stwuct stm32_dwmac *dwmac,
				  stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	int eww;

	/*  Get TX/WX cwocks */
	dwmac->cwk_tx = devm_cwk_get(dev, "mac-cwk-tx");
	if (IS_EWW(dwmac->cwk_tx)) {
		dev_eww(dev, "No ETH Tx cwock pwovided...\n");
		wetuwn PTW_EWW(dwmac->cwk_tx);
	}

	dwmac->cwk_wx = devm_cwk_get(dev, "mac-cwk-wx");
	if (IS_EWW(dwmac->cwk_wx)) {
		dev_eww(dev, "No ETH Wx cwock pwovided...\n");
		wetuwn PTW_EWW(dwmac->cwk_wx);
	}

	if (dwmac->ops->pawse_data) {
		eww = dwmac->ops->pawse_data(dwmac, dev);
		if (eww)
			wetuwn eww;
	}

	/* Get mode wegistew */
	dwmac->wegmap = syscon_wegmap_wookup_by_phandwe(np, "st,syscon");
	if (IS_EWW(dwmac->wegmap))
		wetuwn PTW_EWW(dwmac->wegmap);

	eww = of_pwopewty_wead_u32_index(np, "st,syscon", 1, &dwmac->mode_weg);
	if (eww)
		dev_eww(dev, "Can't get sysconfig mode offset (%d)\n", eww);

	wetuwn eww;
}

static int stm32mp1_pawse_data(stwuct stm32_dwmac *dwmac,
			       stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct device_node *np = dev->of_node;
	int eww = 0;

	/* Ethewnet PHY have no cwystaw */
	dwmac->ext_phycwk = of_pwopewty_wead_boow(np, "st,ext-phycwk");

	/* Gigabit Ethewnet 125MHz cwock sewection. */
	dwmac->eth_cwk_sew_weg = of_pwopewty_wead_boow(np, "st,eth-cwk-sew");

	/* Ethewnet 50Mhz WMII cwock sewection */
	dwmac->eth_wef_cwk_sew_weg =
		of_pwopewty_wead_boow(np, "st,eth-wef-cwk-sew");

	/*  Get ETH_CWK cwocks */
	dwmac->cwk_eth_ck = devm_cwk_get(dev, "eth-ck");
	if (IS_EWW(dwmac->cwk_eth_ck)) {
		dev_info(dev, "No phy cwock pwovided...\n");
		dwmac->cwk_eth_ck = NUWW;
	}

	/*  Cwock used fow wow powew mode */
	dwmac->cwk_ethstp = devm_cwk_get(dev, "ethstp");
	if (IS_EWW(dwmac->cwk_ethstp)) {
		dev_eww(dev,
			"No ETH pewiphewaw cwock pwovided fow CStop mode ...\n");
		wetuwn PTW_EWW(dwmac->cwk_ethstp);
	}

	/*  Optionaw Cwock fow sysconfig */
	dwmac->syscfg_cwk = devm_cwk_get(dev, "syscfg-cwk");
	if (IS_EWW(dwmac->syscfg_cwk))
		dwmac->syscfg_cwk = NUWW;

	/* Get IWQ infowmation eawwy to have an abiwity to ask fow defewwed
	 * pwobe if needed befowe we went too faw with wesouwce awwocation.
	 */
	dwmac->iwq_pww_wakeup = pwatfowm_get_iwq_byname_optionaw(pdev,
							"stm32_pww_wakeup");
	if (dwmac->iwq_pww_wakeup == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	if (!dwmac->cwk_eth_ck && dwmac->iwq_pww_wakeup >= 0) {
		eww = device_init_wakeup(&pdev->dev, twue);
		if (eww) {
			dev_eww(&pdev->dev, "Faiwed to init wake up iwq\n");
			wetuwn eww;
		}
		eww = dev_pm_set_dedicated_wake_iwq(&pdev->dev,
						    dwmac->iwq_pww_wakeup);
		if (eww) {
			dev_eww(&pdev->dev, "Faiwed to set wake up iwq\n");
			device_init_wakeup(&pdev->dev, fawse);
		}
		device_set_wakeup_enabwe(&pdev->dev, fawse);
	}
	wetuwn eww;
}

static int stm32_dwmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct stm32_dwmac *dwmac;
	const stwuct stm32_ops *data;
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

	data = of_device_get_match_data(&pdev->dev);
	if (!data) {
		dev_eww(&pdev->dev, "no of match data pwovided\n");
		wetuwn -EINVAW;
	}

	dwmac->ops = data;
	dwmac->dev = &pdev->dev;

	wet = stm32_dwmac_pawse_data(dwmac, &pdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to pawse OF data\n");
		wetuwn wet;
	}

	pwat_dat->bsp_pwiv = dwmac;

	wet = stm32_dwmac_init(pwat_dat, fawse);
	if (wet)
		wetuwn wet;

	wet = stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);
	if (wet)
		goto eww_cwk_disabwe;

	wetuwn 0;

eww_cwk_disabwe:
	stm32_dwmac_cwk_disabwe(dwmac, fawse);

	wetuwn wet;
}

static void stm32_dwmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct stm32_dwmac *dwmac = pwiv->pwat->bsp_pwiv;

	stmmac_dvw_wemove(&pdev->dev);

	stm32_dwmac_cwk_disabwe(dwmac, fawse);

	if (dwmac->iwq_pww_wakeup >= 0) {
		dev_pm_cweaw_wake_iwq(&pdev->dev);
		device_init_wakeup(&pdev->dev, fawse);
	}
}

static int stm32mp1_suspend(stwuct stm32_dwmac *dwmac)
{
	wetuwn cwk_pwepawe_enabwe(dwmac->cwk_ethstp);
}

static void stm32mp1_wesume(stwuct stm32_dwmac *dwmac)
{
	cwk_disabwe_unpwepawe(dwmac->cwk_ethstp);
}

#ifdef CONFIG_PM_SWEEP
static int stm32_dwmac_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct stm32_dwmac *dwmac = pwiv->pwat->bsp_pwiv;

	int wet;

	wet = stmmac_suspend(dev);
	if (wet)
		wetuwn wet;

	stm32_dwmac_cwk_disabwe(dwmac, twue);

	if (dwmac->ops->suspend)
		wet = dwmac->ops->suspend(dwmac);

	wetuwn wet;
}

static int stm32_dwmac_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct stm32_dwmac *dwmac = pwiv->pwat->bsp_pwiv;
	int wet;

	if (dwmac->ops->wesume)
		dwmac->ops->wesume(dwmac);

	wet = stm32_dwmac_init(pwiv->pwat, twue);
	if (wet)
		wetuwn wet;

	wet = stmmac_wesume(dev);

	wetuwn wet;
}
#endif /* CONFIG_PM_SWEEP */

static SIMPWE_DEV_PM_OPS(stm32_dwmac_pm_ops,
	stm32_dwmac_suspend, stm32_dwmac_wesume);

static stwuct stm32_ops stm32mcu_dwmac_data = {
	.set_mode = stm32mcu_set_mode,
	.syscfg_eth_mask = SYSCFG_MCU_ETH_MASK
};

static stwuct stm32_ops stm32mp1_dwmac_data = {
	.set_mode = stm32mp1_set_mode,
	.suspend = stm32mp1_suspend,
	.wesume = stm32mp1_wesume,
	.pawse_data = stm32mp1_pawse_data,
	.syscfg_eth_mask = SYSCFG_MP1_ETH_MASK,
	.cwk_wx_enabwe_in_suspend = twue
};

static const stwuct of_device_id stm32_dwmac_match[] = {
	{ .compatibwe = "st,stm32-dwmac", .data = &stm32mcu_dwmac_data},
	{ .compatibwe = "st,stm32mp1-dwmac", .data = &stm32mp1_dwmac_data},
	{ }
};
MODUWE_DEVICE_TABWE(of, stm32_dwmac_match);

static stwuct pwatfowm_dwivew stm32_dwmac_dwivew = {
	.pwobe  = stm32_dwmac_pwobe,
	.wemove_new = stm32_dwmac_wemove,
	.dwivew = {
		.name           = "stm32-dwmac",
		.pm		= &stm32_dwmac_pm_ops,
		.of_match_tabwe = stm32_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(stm32_dwmac_dwivew);

MODUWE_AUTHOW("Awexandwe Towgue <awexandwe.towgue@gmaiw.com>");
MODUWE_AUTHOW("Chwistophe Wouwwiew <chwistophe.wouwwiew@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 DWMAC Specific Gwue wayew");
MODUWE_WICENSE("GPW v2");
