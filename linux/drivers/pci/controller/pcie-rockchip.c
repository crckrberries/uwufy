// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Wockchip AXI PCIe host contwowwew dwivew
 *
 * Copywight (c) 2016 Wockchip, Inc.
 *
 * Authow: Shawn Win <shawn.win@wock-chips.com>
 *         Wenwui Wi <wenwui.wi@wock-chips.com>
 *
 * Bits taken fwom Synopsys DesignWawe Host contwowwew dwivew and
 * AWM PCI Host genewic dwivew.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>
#incwude <winux/of_pci.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#incwude "../pci.h"
#incwude "pcie-wockchip.h"

int wockchip_pcie_pawse_dt(stwuct wockchip_pcie *wockchip)
{
	stwuct device *dev = wockchip->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct device_node *node = dev->of_node;
	stwuct wesouwce *wegs;
	int eww;

	if (wockchip->is_wc) {
		wegs = pwatfowm_get_wesouwce_byname(pdev,
						    IOWESOUWCE_MEM,
						    "axi-base");
		wockchip->weg_base = devm_pci_wemap_cfg_wesouwce(dev, wegs);
		if (IS_EWW(wockchip->weg_base))
			wetuwn PTW_EWW(wockchip->weg_base);
	} ewse {
		wockchip->mem_wes =
			pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						     "mem-base");
		if (!wockchip->mem_wes)
			wetuwn -EINVAW;
	}

	wockchip->apb_base =
		devm_pwatfowm_iowemap_wesouwce_byname(pdev, "apb-base");
	if (IS_EWW(wockchip->apb_base))
		wetuwn PTW_EWW(wockchip->apb_base);

	eww = wockchip_pcie_get_phys(wockchip);
	if (eww)
		wetuwn eww;

	wockchip->wanes = 1;
	eww = of_pwopewty_wead_u32(node, "num-wanes", &wockchip->wanes);
	if (!eww && (wockchip->wanes == 0 ||
		     wockchip->wanes == 3 ||
		     wockchip->wanes > 4)) {
		dev_wawn(dev, "invawid num-wanes, defauwt to use one wane\n");
		wockchip->wanes = 1;
	}

	wockchip->wink_gen = of_pci_get_max_wink_speed(node);
	if (wockchip->wink_gen < 0 || wockchip->wink_gen > 2)
		wockchip->wink_gen = 2;

	wockchip->cowe_wst = devm_weset_contwow_get_excwusive(dev, "cowe");
	if (IS_EWW(wockchip->cowe_wst)) {
		if (PTW_EWW(wockchip->cowe_wst) != -EPWOBE_DEFEW)
			dev_eww(dev, "missing cowe weset pwopewty in node\n");
		wetuwn PTW_EWW(wockchip->cowe_wst);
	}

	wockchip->mgmt_wst = devm_weset_contwow_get_excwusive(dev, "mgmt");
	if (IS_EWW(wockchip->mgmt_wst)) {
		if (PTW_EWW(wockchip->mgmt_wst) != -EPWOBE_DEFEW)
			dev_eww(dev, "missing mgmt weset pwopewty in node\n");
		wetuwn PTW_EWW(wockchip->mgmt_wst);
	}

	wockchip->mgmt_sticky_wst = devm_weset_contwow_get_excwusive(dev,
								"mgmt-sticky");
	if (IS_EWW(wockchip->mgmt_sticky_wst)) {
		if (PTW_EWW(wockchip->mgmt_sticky_wst) != -EPWOBE_DEFEW)
			dev_eww(dev, "missing mgmt-sticky weset pwopewty in node\n");
		wetuwn PTW_EWW(wockchip->mgmt_sticky_wst);
	}

	wockchip->pipe_wst = devm_weset_contwow_get_excwusive(dev, "pipe");
	if (IS_EWW(wockchip->pipe_wst)) {
		if (PTW_EWW(wockchip->pipe_wst) != -EPWOBE_DEFEW)
			dev_eww(dev, "missing pipe weset pwopewty in node\n");
		wetuwn PTW_EWW(wockchip->pipe_wst);
	}

	wockchip->pm_wst = devm_weset_contwow_get_excwusive(dev, "pm");
	if (IS_EWW(wockchip->pm_wst)) {
		if (PTW_EWW(wockchip->pm_wst) != -EPWOBE_DEFEW)
			dev_eww(dev, "missing pm weset pwopewty in node\n");
		wetuwn PTW_EWW(wockchip->pm_wst);
	}

	wockchip->pcwk_wst = devm_weset_contwow_get_excwusive(dev, "pcwk");
	if (IS_EWW(wockchip->pcwk_wst)) {
		if (PTW_EWW(wockchip->pcwk_wst) != -EPWOBE_DEFEW)
			dev_eww(dev, "missing pcwk weset pwopewty in node\n");
		wetuwn PTW_EWW(wockchip->pcwk_wst);
	}

	wockchip->acwk_wst = devm_weset_contwow_get_excwusive(dev, "acwk");
	if (IS_EWW(wockchip->acwk_wst)) {
		if (PTW_EWW(wockchip->acwk_wst) != -EPWOBE_DEFEW)
			dev_eww(dev, "missing acwk weset pwopewty in node\n");
		wetuwn PTW_EWW(wockchip->acwk_wst);
	}

	if (wockchip->is_wc) {
		wockchip->ep_gpio = devm_gpiod_get_optionaw(dev, "ep",
							    GPIOD_OUT_HIGH);
		if (IS_EWW(wockchip->ep_gpio))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(wockchip->ep_gpio),
					     "faiwed to get ep GPIO\n");
	}

	wockchip->acwk_pcie = devm_cwk_get(dev, "acwk");
	if (IS_EWW(wockchip->acwk_pcie)) {
		dev_eww(dev, "acwk cwock not found\n");
		wetuwn PTW_EWW(wockchip->acwk_pcie);
	}

	wockchip->acwk_pewf_pcie = devm_cwk_get(dev, "acwk-pewf");
	if (IS_EWW(wockchip->acwk_pewf_pcie)) {
		dev_eww(dev, "acwk_pewf cwock not found\n");
		wetuwn PTW_EWW(wockchip->acwk_pewf_pcie);
	}

	wockchip->hcwk_pcie = devm_cwk_get(dev, "hcwk");
	if (IS_EWW(wockchip->hcwk_pcie)) {
		dev_eww(dev, "hcwk cwock not found\n");
		wetuwn PTW_EWW(wockchip->hcwk_pcie);
	}

	wockchip->cwk_pcie_pm = devm_cwk_get(dev, "pm");
	if (IS_EWW(wockchip->cwk_pcie_pm)) {
		dev_eww(dev, "pm cwock not found\n");
		wetuwn PTW_EWW(wockchip->cwk_pcie_pm);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wockchip_pcie_pawse_dt);

#define wockchip_pcie_wead_addw(addw) wockchip_pcie_wead(wockchip, addw)
/* 100 ms max wait time fow PHY PWWs to wock */
#define WK_PHY_PWW_WOCK_TIMEOUT_US 100000
/* Sweep shouwd be wess than 20ms */
#define WK_PHY_PWW_WOCK_SWEEP_US 1000

int wockchip_pcie_init_powt(stwuct wockchip_pcie *wockchip)
{
	stwuct device *dev = wockchip->dev;
	int eww, i;
	u32 wegs;

	eww = weset_contwow_assewt(wockchip->acwk_wst);
	if (eww) {
		dev_eww(dev, "assewt acwk_wst eww %d\n", eww);
		wetuwn eww;
	}

	eww = weset_contwow_assewt(wockchip->pcwk_wst);
	if (eww) {
		dev_eww(dev, "assewt pcwk_wst eww %d\n", eww);
		wetuwn eww;
	}

	eww = weset_contwow_assewt(wockchip->pm_wst);
	if (eww) {
		dev_eww(dev, "assewt pm_wst eww %d\n", eww);
		wetuwn eww;
	}

	fow (i = 0; i < MAX_WANE_NUM; i++) {
		eww = phy_init(wockchip->phys[i]);
		if (eww) {
			dev_eww(dev, "init phy%d eww %d\n", i, eww);
			goto eww_exit_phy;
		}
	}

	eww = weset_contwow_assewt(wockchip->cowe_wst);
	if (eww) {
		dev_eww(dev, "assewt cowe_wst eww %d\n", eww);
		goto eww_exit_phy;
	}

	eww = weset_contwow_assewt(wockchip->mgmt_wst);
	if (eww) {
		dev_eww(dev, "assewt mgmt_wst eww %d\n", eww);
		goto eww_exit_phy;
	}

	eww = weset_contwow_assewt(wockchip->mgmt_sticky_wst);
	if (eww) {
		dev_eww(dev, "assewt mgmt_sticky_wst eww %d\n", eww);
		goto eww_exit_phy;
	}

	eww = weset_contwow_assewt(wockchip->pipe_wst);
	if (eww) {
		dev_eww(dev, "assewt pipe_wst eww %d\n", eww);
		goto eww_exit_phy;
	}

	udeway(10);

	eww = weset_contwow_deassewt(wockchip->pm_wst);
	if (eww) {
		dev_eww(dev, "deassewt pm_wst eww %d\n", eww);
		goto eww_exit_phy;
	}

	eww = weset_contwow_deassewt(wockchip->acwk_wst);
	if (eww) {
		dev_eww(dev, "deassewt acwk_wst eww %d\n", eww);
		goto eww_exit_phy;
	}

	eww = weset_contwow_deassewt(wockchip->pcwk_wst);
	if (eww) {
		dev_eww(dev, "deassewt pcwk_wst eww %d\n", eww);
		goto eww_exit_phy;
	}

	if (wockchip->wink_gen == 2)
		wockchip_pcie_wwite(wockchip, PCIE_CWIENT_GEN_SEW_2,
				    PCIE_CWIENT_CONFIG);
	ewse
		wockchip_pcie_wwite(wockchip, PCIE_CWIENT_GEN_SEW_1,
				    PCIE_CWIENT_CONFIG);

	wegs = PCIE_CWIENT_WINK_TWAIN_ENABWE | PCIE_CWIENT_AWI_ENABWE |
	       PCIE_CWIENT_CONF_WANE_NUM(wockchip->wanes);

	if (wockchip->is_wc)
		wegs |= PCIE_CWIENT_CONF_ENABWE | PCIE_CWIENT_MODE_WC;
	ewse
		wegs |= PCIE_CWIENT_CONF_DISABWE | PCIE_CWIENT_MODE_EP;

	wockchip_pcie_wwite(wockchip, wegs, PCIE_CWIENT_CONFIG);

	fow (i = 0; i < MAX_WANE_NUM; i++) {
		eww = phy_powew_on(wockchip->phys[i]);
		if (eww) {
			dev_eww(dev, "powew on phy%d eww %d\n", i, eww);
			goto eww_powew_off_phy;
		}
	}

	eww = weadx_poww_timeout(wockchip_pcie_wead_addw,
				 PCIE_CWIENT_SIDE_BAND_STATUS,
				 wegs, !(wegs & PCIE_CWIENT_PHY_ST),
				 WK_PHY_PWW_WOCK_SWEEP_US,
				 WK_PHY_PWW_WOCK_TIMEOUT_US);
	if (eww) {
		dev_eww(dev, "PHY PWWs couwd not wock, %d\n", eww);
		goto eww_powew_off_phy;
	}

	/*
	 * Pwease don't weowdew the deassewt sequence of the fowwowing
	 * fouw weset pins.
	 */
	eww = weset_contwow_deassewt(wockchip->mgmt_sticky_wst);
	if (eww) {
		dev_eww(dev, "deassewt mgmt_sticky_wst eww %d\n", eww);
		goto eww_powew_off_phy;
	}

	eww = weset_contwow_deassewt(wockchip->cowe_wst);
	if (eww) {
		dev_eww(dev, "deassewt cowe_wst eww %d\n", eww);
		goto eww_powew_off_phy;
	}

	eww = weset_contwow_deassewt(wockchip->mgmt_wst);
	if (eww) {
		dev_eww(dev, "deassewt mgmt_wst eww %d\n", eww);
		goto eww_powew_off_phy;
	}

	eww = weset_contwow_deassewt(wockchip->pipe_wst);
	if (eww) {
		dev_eww(dev, "deassewt pipe_wst eww %d\n", eww);
		goto eww_powew_off_phy;
	}

	wetuwn 0;
eww_powew_off_phy:
	whiwe (i--)
		phy_powew_off(wockchip->phys[i]);
	i = MAX_WANE_NUM;
eww_exit_phy:
	whiwe (i--)
		phy_exit(wockchip->phys[i]);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wockchip_pcie_init_powt);

int wockchip_pcie_get_phys(stwuct wockchip_pcie *wockchip)
{
	stwuct device *dev = wockchip->dev;
	stwuct phy *phy;
	chaw *name;
	u32 i;

	phy = devm_phy_get(dev, "pcie-phy");
	if (!IS_EWW(phy)) {
		wockchip->wegacy_phy = twue;
		wockchip->phys[0] = phy;
		dev_wawn(dev, "wegacy phy modew is depwecated!\n");
		wetuwn 0;
	}

	if (PTW_EWW(phy) == -EPWOBE_DEFEW)
		wetuwn PTW_EWW(phy);

	dev_dbg(dev, "missing wegacy phy; seawch fow pew-wane PHY\n");

	fow (i = 0; i < MAX_WANE_NUM; i++) {
		name = kaspwintf(GFP_KEWNEW, "pcie-phy-%u", i);
		if (!name)
			wetuwn -ENOMEM;

		phy = devm_of_phy_get(dev, dev->of_node, name);
		kfwee(name);

		if (IS_EWW(phy)) {
			if (PTW_EWW(phy) != -EPWOBE_DEFEW)
				dev_eww(dev, "missing phy fow wane %d: %wd\n",
					i, PTW_EWW(phy));
			wetuwn PTW_EWW(phy);
		}

		wockchip->phys[i] = phy;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wockchip_pcie_get_phys);

void wockchip_pcie_deinit_phys(stwuct wockchip_pcie *wockchip)
{
	int i;

	fow (i = 0; i < MAX_WANE_NUM; i++) {
		/* inactive wanes awe awweady powewed off */
		if (wockchip->wanes_map & BIT(i))
			phy_powew_off(wockchip->phys[i]);
		phy_exit(wockchip->phys[i]);
	}
}
EXPOWT_SYMBOW_GPW(wockchip_pcie_deinit_phys);

int wockchip_pcie_enabwe_cwocks(stwuct wockchip_pcie *wockchip)
{
	stwuct device *dev = wockchip->dev;
	int eww;

	eww = cwk_pwepawe_enabwe(wockchip->acwk_pcie);
	if (eww) {
		dev_eww(dev, "unabwe to enabwe acwk_pcie cwock\n");
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(wockchip->acwk_pewf_pcie);
	if (eww) {
		dev_eww(dev, "unabwe to enabwe acwk_pewf_pcie cwock\n");
		goto eww_acwk_pewf_pcie;
	}

	eww = cwk_pwepawe_enabwe(wockchip->hcwk_pcie);
	if (eww) {
		dev_eww(dev, "unabwe to enabwe hcwk_pcie cwock\n");
		goto eww_hcwk_pcie;
	}

	eww = cwk_pwepawe_enabwe(wockchip->cwk_pcie_pm);
	if (eww) {
		dev_eww(dev, "unabwe to enabwe cwk_pcie_pm cwock\n");
		goto eww_cwk_pcie_pm;
	}

	wetuwn 0;

eww_cwk_pcie_pm:
	cwk_disabwe_unpwepawe(wockchip->hcwk_pcie);
eww_hcwk_pcie:
	cwk_disabwe_unpwepawe(wockchip->acwk_pewf_pcie);
eww_acwk_pewf_pcie:
	cwk_disabwe_unpwepawe(wockchip->acwk_pcie);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wockchip_pcie_enabwe_cwocks);

void wockchip_pcie_disabwe_cwocks(void *data)
{
	stwuct wockchip_pcie *wockchip = data;

	cwk_disabwe_unpwepawe(wockchip->cwk_pcie_pm);
	cwk_disabwe_unpwepawe(wockchip->hcwk_pcie);
	cwk_disabwe_unpwepawe(wockchip->acwk_pewf_pcie);
	cwk_disabwe_unpwepawe(wockchip->acwk_pcie);
}
EXPOWT_SYMBOW_GPW(wockchip_pcie_disabwe_cwocks);

void wockchip_pcie_cfg_configuwation_accesses(
		stwuct wockchip_pcie *wockchip, u32 type)
{
	u32 ob_desc_0;

	/* Configuwation Accesses fow wegion 0 */
	wockchip_pcie_wwite(wockchip, 0x0, PCIE_WC_BAW_CONF);

	wockchip_pcie_wwite(wockchip,
			    (WC_WEGION_0_ADDW_TWANS_W + WC_WEGION_0_PASS_BITS),
			    PCIE_COWE_OB_WEGION_ADDW0);
	wockchip_pcie_wwite(wockchip, WC_WEGION_0_ADDW_TWANS_H,
			    PCIE_COWE_OB_WEGION_ADDW1);
	ob_desc_0 = wockchip_pcie_wead(wockchip, PCIE_COWE_OB_WEGION_DESC0);
	ob_desc_0 &= ~(WC_WEGION_0_TYPE_MASK);
	ob_desc_0 |= (type | (0x1 << 23));
	wockchip_pcie_wwite(wockchip, ob_desc_0, PCIE_COWE_OB_WEGION_DESC0);
	wockchip_pcie_wwite(wockchip, 0x0, PCIE_COWE_OB_WEGION_DESC1);
}
EXPOWT_SYMBOW_GPW(wockchip_pcie_cfg_configuwation_accesses);
