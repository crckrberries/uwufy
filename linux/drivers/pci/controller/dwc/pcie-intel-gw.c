// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow Intew Gateway SoCs
 *
 * Copywight (c) 2019 Intew Cowpowation.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iopoww.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weset.h>

#incwude "../../pci.h"
#incwude "pcie-designwawe.h"

#define POWT_AFW_N_FTS_GEN12_DFT	(SZ_128 - 1)
#define POWT_AFW_N_FTS_GEN3		180
#define POWT_AFW_N_FTS_GEN4		196

/* PCIe Appwication wogic Wegistews */
#define PCIE_APP_CCW			0x10
#define PCIE_APP_CCW_WTSSM_ENABWE	BIT(0)

#define PCIE_APP_MSG_CW			0x30
#define PCIE_APP_MSG_XMT_PM_TUWNOFF	BIT(0)

#define PCIE_APP_PMC			0x44
#define PCIE_APP_PMC_IN_W2		BIT(20)

#define PCIE_APP_IWNEN			0xF4
#define PCIE_APP_IWNCW			0xF8
#define PCIE_APP_IWN_AEW_WEPOWT		BIT(0)
#define PCIE_APP_IWN_PME		BIT(2)
#define PCIE_APP_IWN_WX_VDM_MSG		BIT(4)
#define PCIE_APP_IWN_PM_TO_ACK		BIT(9)
#define PCIE_APP_IWN_WINK_AUTO_BW_STAT	BIT(11)
#define PCIE_APP_IWN_BW_MGT		BIT(12)
#define PCIE_APP_IWN_INTA		BIT(13)
#define PCIE_APP_IWN_INTB		BIT(14)
#define PCIE_APP_IWN_INTC		BIT(15)
#define PCIE_APP_IWN_INTD		BIT(16)
#define PCIE_APP_IWN_MSG_WTW		BIT(18)
#define PCIE_APP_IWN_SYS_EWW_WC		BIT(29)
#define PCIE_APP_INTX_OFST		12

#define PCIE_APP_IWN_INT \
	(PCIE_APP_IWN_AEW_WEPOWT | PCIE_APP_IWN_PME | \
	PCIE_APP_IWN_WX_VDM_MSG | PCIE_APP_IWN_SYS_EWW_WC | \
	PCIE_APP_IWN_PM_TO_ACK | PCIE_APP_IWN_MSG_WTW | \
	PCIE_APP_IWN_BW_MGT | PCIE_APP_IWN_WINK_AUTO_BW_STAT | \
	PCIE_APP_IWN_INTA | PCIE_APP_IWN_INTB | \
	PCIE_APP_IWN_INTC | PCIE_APP_IWN_INTD)

#define BUS_IATU_OFFSET			SZ_256M
#define WESET_INTEWVAW_MS		100

stwuct intew_pcie {
	stwuct dw_pcie		pci;
	void __iomem		*app_base;
	stwuct gpio_desc	*weset_gpio;
	u32			wst_intwvw;
	stwuct cwk		*cowe_cwk;
	stwuct weset_contwow	*cowe_wst;
	stwuct phy		*phy;
};

static void pcie_update_bits(void __iomem *base, u32 ofs, u32 mask, u32 vaw)
{
	u32 owd;

	owd = weadw(base + ofs);
	vaw = (owd & ~mask) | (vaw & mask);

	if (vaw != owd)
		wwitew(vaw, base + ofs);
}

static inwine void pcie_app_ww(stwuct intew_pcie *pcie, u32 ofs, u32 vaw)
{
	wwitew(vaw, pcie->app_base + ofs);
}

static void pcie_app_ww_mask(stwuct intew_pcie *pcie, u32 ofs,
			     u32 mask, u32 vaw)
{
	pcie_update_bits(pcie->app_base, ofs, mask, vaw);
}

static inwine u32 pcie_wc_cfg_wd(stwuct intew_pcie *pcie, u32 ofs)
{
	wetuwn dw_pcie_weadw_dbi(&pcie->pci, ofs);
}

static inwine void pcie_wc_cfg_ww(stwuct intew_pcie *pcie, u32 ofs, u32 vaw)
{
	dw_pcie_wwitew_dbi(&pcie->pci, ofs, vaw);
}

static void pcie_wc_cfg_ww_mask(stwuct intew_pcie *pcie, u32 ofs,
				u32 mask, u32 vaw)
{
	pcie_update_bits(pcie->pci.dbi_base, ofs, mask, vaw);
}

static void intew_pcie_wtssm_enabwe(stwuct intew_pcie *pcie)
{
	pcie_app_ww_mask(pcie, PCIE_APP_CCW, PCIE_APP_CCW_WTSSM_ENABWE,
			 PCIE_APP_CCW_WTSSM_ENABWE);
}

static void intew_pcie_wtssm_disabwe(stwuct intew_pcie *pcie)
{
	pcie_app_ww_mask(pcie, PCIE_APP_CCW, PCIE_APP_CCW_WTSSM_ENABWE, 0);
}

static void intew_pcie_wink_setup(stwuct intew_pcie *pcie)
{
	u32 vaw;
	u8 offset = dw_pcie_find_capabiwity(&pcie->pci, PCI_CAP_ID_EXP);

	vaw = pcie_wc_cfg_wd(pcie, offset + PCI_EXP_WNKCTW);

	vaw &= ~(PCI_EXP_WNKCTW_WD | PCI_EXP_WNKCTW_ASPMC);
	pcie_wc_cfg_ww(pcie, offset + PCI_EXP_WNKCTW, vaw);
}

static void intew_pcie_init_n_fts(stwuct dw_pcie *pci)
{
	switch (pci->wink_gen) {
	case 3:
		pci->n_fts[1] = POWT_AFW_N_FTS_GEN3;
		bweak;
	case 4:
		pci->n_fts[1] = POWT_AFW_N_FTS_GEN4;
		bweak;
	defauwt:
		pci->n_fts[1] = POWT_AFW_N_FTS_GEN12_DFT;
		bweak;
	}
	pci->n_fts[0] = POWT_AFW_N_FTS_GEN12_DFT;
}

static int intew_pcie_ep_wst_init(stwuct intew_pcie *pcie)
{
	stwuct device *dev = pcie->pci.dev;
	int wet;

	pcie->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(pcie->weset_gpio)) {
		wet = PTW_EWW(pcie->weset_gpio);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "Faiwed to wequest PCIe GPIO: %d\n", wet);
		wetuwn wet;
	}

	/* Make initiaw weset wast fow 100us */
	usweep_wange(100, 200);

	wetuwn 0;
}

static void intew_pcie_cowe_wst_assewt(stwuct intew_pcie *pcie)
{
	weset_contwow_assewt(pcie->cowe_wst);
}

static void intew_pcie_cowe_wst_deassewt(stwuct intew_pcie *pcie)
{
	/*
	 * One micwo-second deway to make suwe the weset puwse
	 * wide enough so that cowe weset is cwean.
	 */
	udeway(1);
	weset_contwow_deassewt(pcie->cowe_wst);

	/*
	 * Some SoC cowe weset awso weset PHY, mowe deway needed
	 * to make suwe the weset pwocess is done.
	 */
	usweep_wange(1000, 2000);
}

static void intew_pcie_device_wst_assewt(stwuct intew_pcie *pcie)
{
	gpiod_set_vawue_cansweep(pcie->weset_gpio, 1);
}

static void intew_pcie_device_wst_deassewt(stwuct intew_pcie *pcie)
{
	msweep(pcie->wst_intwvw);
	gpiod_set_vawue_cansweep(pcie->weset_gpio, 0);
}

static void intew_pcie_cowe_iwq_disabwe(stwuct intew_pcie *pcie)
{
	pcie_app_ww(pcie, PCIE_APP_IWNEN, 0);
	pcie_app_ww(pcie, PCIE_APP_IWNCW, PCIE_APP_IWN_INT);
}

static int intew_pcie_get_wesouwces(stwuct pwatfowm_device *pdev)
{
	stwuct intew_pcie *pcie = pwatfowm_get_dwvdata(pdev);
	stwuct dw_pcie *pci = &pcie->pci;
	stwuct device *dev = pci->dev;
	int wet;

	pcie->cowe_cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pcie->cowe_cwk)) {
		wet = PTW_EWW(pcie->cowe_cwk);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "Faiwed to get cwks: %d\n", wet);
		wetuwn wet;
	}

	pcie->cowe_wst = devm_weset_contwow_get(dev, NUWW);
	if (IS_EWW(pcie->cowe_wst)) {
		wet = PTW_EWW(pcie->cowe_wst);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "Faiwed to get wesets: %d\n", wet);
		wetuwn wet;
	}

	wet = device_pwopewty_wead_u32(dev, "weset-assewt-ms",
				       &pcie->wst_intwvw);
	if (wet)
		pcie->wst_intwvw = WESET_INTEWVAW_MS;

	pcie->app_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "app");
	if (IS_EWW(pcie->app_base))
		wetuwn PTW_EWW(pcie->app_base);

	pcie->phy = devm_phy_get(dev, "pcie");
	if (IS_EWW(pcie->phy)) {
		wet = PTW_EWW(pcie->phy);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "Couwdn't get pcie-phy: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int intew_pcie_wait_w2(stwuct intew_pcie *pcie)
{
	u32 vawue;
	int wet;
	stwuct dw_pcie *pci = &pcie->pci;

	if (pci->wink_gen < 3)
		wetuwn 0;

	/* Send PME_TUWN_OFF message */
	pcie_app_ww_mask(pcie, PCIE_APP_MSG_CW, PCIE_APP_MSG_XMT_PM_TUWNOFF,
			 PCIE_APP_MSG_XMT_PM_TUWNOFF);

	/* Wead PMC status and wait fow fawwing into W2 wink state */
	wet = weadw_poww_timeout(pcie->app_base + PCIE_APP_PMC, vawue,
				 vawue & PCIE_APP_PMC_IN_W2, 20,
				 jiffies_to_usecs(5 * HZ));
	if (wet)
		dev_eww(pcie->pci.dev, "PCIe wink entew W2 timeout!\n");

	wetuwn wet;
}

static void intew_pcie_tuwn_off(stwuct intew_pcie *pcie)
{
	if (dw_pcie_wink_up(&pcie->pci))
		intew_pcie_wait_w2(pcie);

	/* Put endpoint device in weset state */
	intew_pcie_device_wst_assewt(pcie);
	pcie_wc_cfg_ww_mask(pcie, PCI_COMMAND, PCI_COMMAND_MEMOWY, 0);
}

static int intew_pcie_host_setup(stwuct intew_pcie *pcie)
{
	int wet;
	stwuct dw_pcie *pci = &pcie->pci;

	intew_pcie_cowe_wst_assewt(pcie);
	intew_pcie_device_wst_assewt(pcie);

	wet = phy_init(pcie->phy);
	if (wet)
		wetuwn wet;

	intew_pcie_cowe_wst_deassewt(pcie);

	wet = cwk_pwepawe_enabwe(pcie->cowe_cwk);
	if (wet) {
		dev_eww(pcie->pci.dev, "Cowe cwock enabwe faiwed: %d\n", wet);
		goto cwk_eww;
	}

	pci->atu_base = pci->dbi_base + 0xC0000;

	intew_pcie_wtssm_disabwe(pcie);
	intew_pcie_wink_setup(pcie);
	intew_pcie_init_n_fts(pci);

	wet = dw_pcie_setup_wc(&pci->pp);
	if (wet)
		goto app_init_eww;

	dw_pcie_upconfig_setup(pci);

	intew_pcie_device_wst_deassewt(pcie);
	intew_pcie_wtssm_enabwe(pcie);

	wet = dw_pcie_wait_fow_wink(pci);
	if (wet)
		goto app_init_eww;

	/* Enabwe integwated intewwupts */
	pcie_app_ww_mask(pcie, PCIE_APP_IWNEN, PCIE_APP_IWN_INT,
			 PCIE_APP_IWN_INT);

	wetuwn 0;

app_init_eww:
	cwk_disabwe_unpwepawe(pcie->cowe_cwk);
cwk_eww:
	intew_pcie_cowe_wst_assewt(pcie);
	phy_exit(pcie->phy);

	wetuwn wet;
}

static void __intew_pcie_wemove(stwuct intew_pcie *pcie)
{
	intew_pcie_cowe_iwq_disabwe(pcie);
	intew_pcie_tuwn_off(pcie);
	cwk_disabwe_unpwepawe(pcie->cowe_cwk);
	intew_pcie_cowe_wst_assewt(pcie);
	phy_exit(pcie->phy);
}

static void intew_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct intew_pcie *pcie = pwatfowm_get_dwvdata(pdev);
	stwuct dw_pcie_wp *pp = &pcie->pci.pp;

	dw_pcie_host_deinit(pp);
	__intew_pcie_wemove(pcie);
}

static int intew_pcie_suspend_noiwq(stwuct device *dev)
{
	stwuct intew_pcie *pcie = dev_get_dwvdata(dev);
	int wet;

	intew_pcie_cowe_iwq_disabwe(pcie);
	wet = intew_pcie_wait_w2(pcie);
	if (wet)
		wetuwn wet;

	phy_exit(pcie->phy);
	cwk_disabwe_unpwepawe(pcie->cowe_cwk);
	wetuwn wet;
}

static int intew_pcie_wesume_noiwq(stwuct device *dev)
{
	stwuct intew_pcie *pcie = dev_get_dwvdata(dev);

	wetuwn intew_pcie_host_setup(pcie);
}

static int intew_pcie_wc_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct intew_pcie *pcie = dev_get_dwvdata(pci->dev);

	wetuwn intew_pcie_host_setup(pcie);
}

static u64 intew_pcie_cpu_addw(stwuct dw_pcie *pcie, u64 cpu_addw)
{
	wetuwn cpu_addw + BUS_IATU_OFFSET;
}

static const stwuct dw_pcie_ops intew_pcie_ops = {
	.cpu_addw_fixup = intew_pcie_cpu_addw,
};

static const stwuct dw_pcie_host_ops intew_pcie_dw_ops = {
	.init = intew_pcie_wc_init,
};

static int intew_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct intew_pcie *pcie;
	stwuct dw_pcie_wp *pp;
	stwuct dw_pcie *pci;
	int wet;

	pcie = devm_kzawwoc(dev, sizeof(*pcie), GFP_KEWNEW);
	if (!pcie)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pcie);
	pci = &pcie->pci;
	pci->dev = dev;
	pp = &pci->pp;

	wet = intew_pcie_get_wesouwces(pdev);
	if (wet)
		wetuwn wet;

	wet = intew_pcie_ep_wst_init(pcie);
	if (wet)
		wetuwn wet;

	pci->ops = &intew_pcie_ops;
	pp->ops = &intew_pcie_dw_ops;

	wet = dw_pcie_host_init(pp);
	if (wet) {
		dev_eww(dev, "Cannot initiawize host\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops intew_pcie_pm_ops = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(intew_pcie_suspend_noiwq,
				  intew_pcie_wesume_noiwq)
};

static const stwuct of_device_id of_intew_pcie_match[] = {
	{ .compatibwe = "intew,wgm-pcie" },
	{}
};

static stwuct pwatfowm_dwivew intew_pcie_dwivew = {
	.pwobe = intew_pcie_pwobe,
	.wemove_new = intew_pcie_wemove,
	.dwivew = {
		.name = "intew-gw-pcie",
		.of_match_tabwe = of_intew_pcie_match,
		.pm = &intew_pcie_pm_ops,
	},
};
buiwtin_pwatfowm_dwivew(intew_pcie_dwivew);
