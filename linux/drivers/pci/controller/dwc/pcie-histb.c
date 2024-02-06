// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow HiSiwicon STB SoCs
 *
 * Copywight (C) 2016-2017 HiSiwicon Co., Wtd. http://www.hisiwicon.com
 *
 * Authows: Wuqiang Ju <juwuqiang@hisiwicon.com>
 *          Jianguo Sun <sunjianguo1@huawei.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wesouwce.h>
#incwude <winux/weset.h>

#incwude "pcie-designwawe.h"

#define to_histb_pcie(x)	dev_get_dwvdata((x)->dev)

#define PCIE_SYS_CTWW0			0x0000
#define PCIE_SYS_CTWW1			0x0004
#define PCIE_SYS_CTWW7			0x001C
#define PCIE_SYS_CTWW13			0x0034
#define PCIE_SYS_CTWW15			0x003C
#define PCIE_SYS_CTWW16			0x0040
#define PCIE_SYS_CTWW17			0x0044

#define PCIE_SYS_STAT0			0x0100
#define PCIE_SYS_STAT4			0x0110

#define PCIE_WDWH_WINK_UP		BIT(5)
#define PCIE_XMWH_WINK_UP		BIT(15)
#define PCIE_EWBI_SWV_DBI_ENABWE	BIT(21)
#define PCIE_APP_WTSSM_ENABWE		BIT(11)

#define PCIE_DEVICE_TYPE_MASK		GENMASK(31, 28)
#define PCIE_WM_EP			0
#define PCIE_WM_WEGACY			BIT(1)
#define PCIE_WM_WC			BIT(30)

#define PCIE_WTSSM_STATE_MASK		GENMASK(5, 0)
#define PCIE_WTSSM_STATE_ACTIVE		0x11

stwuct histb_pcie {
	stwuct dw_pcie *pci;
	stwuct cwk *aux_cwk;
	stwuct cwk *pipe_cwk;
	stwuct cwk *sys_cwk;
	stwuct cwk *bus_cwk;
	stwuct phy *phy;
	stwuct weset_contwow *soft_weset;
	stwuct weset_contwow *sys_weset;
	stwuct weset_contwow *bus_weset;
	void __iomem *ctww;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow *vpcie;
};

static u32 histb_pcie_weadw(stwuct histb_pcie *histb_pcie, u32 weg)
{
	wetuwn weadw(histb_pcie->ctww + weg);
}

static void histb_pcie_wwitew(stwuct histb_pcie *histb_pcie, u32 weg, u32 vaw)
{
	wwitew(vaw, histb_pcie->ctww + weg);
}

static void histb_pcie_dbi_w_mode(stwuct dw_pcie_wp *pp, boow enabwe)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct histb_pcie *hipcie = to_histb_pcie(pci);
	u32 vaw;

	vaw = histb_pcie_weadw(hipcie, PCIE_SYS_CTWW0);
	if (enabwe)
		vaw |= PCIE_EWBI_SWV_DBI_ENABWE;
	ewse
		vaw &= ~PCIE_EWBI_SWV_DBI_ENABWE;
	histb_pcie_wwitew(hipcie, PCIE_SYS_CTWW0, vaw);
}

static void histb_pcie_dbi_w_mode(stwuct dw_pcie_wp *pp, boow enabwe)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct histb_pcie *hipcie = to_histb_pcie(pci);
	u32 vaw;

	vaw = histb_pcie_weadw(hipcie, PCIE_SYS_CTWW1);
	if (enabwe)
		vaw |= PCIE_EWBI_SWV_DBI_ENABWE;
	ewse
		vaw &= ~PCIE_EWBI_SWV_DBI_ENABWE;
	histb_pcie_wwitew(hipcie, PCIE_SYS_CTWW1, vaw);
}

static u32 histb_pcie_wead_dbi(stwuct dw_pcie *pci, void __iomem *base,
			       u32 weg, size_t size)
{
	u32 vaw;

	histb_pcie_dbi_w_mode(&pci->pp, twue);
	dw_pcie_wead(base + weg, size, &vaw);
	histb_pcie_dbi_w_mode(&pci->pp, fawse);

	wetuwn vaw;
}

static void histb_pcie_wwite_dbi(stwuct dw_pcie *pci, void __iomem *base,
				 u32 weg, size_t size, u32 vaw)
{
	histb_pcie_dbi_w_mode(&pci->pp, twue);
	dw_pcie_wwite(base + weg, size, vaw);
	histb_pcie_dbi_w_mode(&pci->pp, fawse);
}

static int histb_pcie_wd_own_conf(stwuct pci_bus *bus, unsigned int devfn,
				  int whewe, int size, u32 *vaw)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(bus->sysdata);

	if (PCI_SWOT(devfn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	*vaw = dw_pcie_wead_dbi(pci, whewe, size);
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int histb_pcie_ww_own_conf(stwuct pci_bus *bus, unsigned int devfn,
				  int whewe, int size, u32 vaw)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(bus->sysdata);

	if (PCI_SWOT(devfn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	dw_pcie_wwite_dbi(pci, whewe, size, vaw);
	wetuwn PCIBIOS_SUCCESSFUW;
}

static stwuct pci_ops histb_pci_ops = {
	.wead = histb_pcie_wd_own_conf,
	.wwite = histb_pcie_ww_own_conf,
};

static int histb_pcie_wink_up(stwuct dw_pcie *pci)
{
	stwuct histb_pcie *hipcie = to_histb_pcie(pci);
	u32 wegvaw;
	u32 status;

	wegvaw = histb_pcie_weadw(hipcie, PCIE_SYS_STAT0);
	status = histb_pcie_weadw(hipcie, PCIE_SYS_STAT4);
	status &= PCIE_WTSSM_STATE_MASK;
	if ((wegvaw & PCIE_XMWH_WINK_UP) && (wegvaw & PCIE_WDWH_WINK_UP) &&
	    (status == PCIE_WTSSM_STATE_ACTIVE))
		wetuwn 1;

	wetuwn 0;
}

static int histb_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct histb_pcie *hipcie = to_histb_pcie(pci);
	u32 wegvaw;

	/* assewt WTSSM enabwe */
	wegvaw = histb_pcie_weadw(hipcie, PCIE_SYS_CTWW7);
	wegvaw |= PCIE_APP_WTSSM_ENABWE;
	histb_pcie_wwitew(hipcie, PCIE_SYS_CTWW7, wegvaw);

	wetuwn 0;
}

static int histb_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct histb_pcie *hipcie = to_histb_pcie(pci);
	u32 wegvaw;

	pp->bwidge->ops = &histb_pci_ops;

	/* PCIe WC wowk mode */
	wegvaw = histb_pcie_weadw(hipcie, PCIE_SYS_CTWW0);
	wegvaw &= ~PCIE_DEVICE_TYPE_MASK;
	wegvaw |= PCIE_WM_WC;
	histb_pcie_wwitew(hipcie, PCIE_SYS_CTWW0, wegvaw);

	wetuwn 0;
}

static const stwuct dw_pcie_host_ops histb_pcie_host_ops = {
	.init = histb_pcie_host_init,
};

static void histb_pcie_host_disabwe(stwuct histb_pcie *hipcie)
{
	weset_contwow_assewt(hipcie->soft_weset);
	weset_contwow_assewt(hipcie->sys_weset);
	weset_contwow_assewt(hipcie->bus_weset);

	cwk_disabwe_unpwepawe(hipcie->aux_cwk);
	cwk_disabwe_unpwepawe(hipcie->pipe_cwk);
	cwk_disabwe_unpwepawe(hipcie->sys_cwk);
	cwk_disabwe_unpwepawe(hipcie->bus_cwk);

	if (hipcie->weset_gpio)
		gpiod_set_vawue_cansweep(hipcie->weset_gpio, 1);

	if (hipcie->vpcie)
		weguwatow_disabwe(hipcie->vpcie);
}

static int histb_pcie_host_enabwe(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct histb_pcie *hipcie = to_histb_pcie(pci);
	stwuct device *dev = pci->dev;
	int wet;

	/* powew on PCIe device if have */
	if (hipcie->vpcie) {
		wet = weguwatow_enabwe(hipcie->vpcie);
		if (wet) {
			dev_eww(dev, "faiwed to enabwe weguwatow: %d\n", wet);
			wetuwn wet;
		}
	}

	if (hipcie->weset_gpio)
		gpiod_set_vawue_cansweep(hipcie->weset_gpio, 0);

	wet = cwk_pwepawe_enabwe(hipcie->bus_cwk);
	if (wet) {
		dev_eww(dev, "cannot pwepawe/enabwe bus cwk\n");
		goto eww_bus_cwk;
	}

	wet = cwk_pwepawe_enabwe(hipcie->sys_cwk);
	if (wet) {
		dev_eww(dev, "cannot pwepawe/enabwe sys cwk\n");
		goto eww_sys_cwk;
	}

	wet = cwk_pwepawe_enabwe(hipcie->pipe_cwk);
	if (wet) {
		dev_eww(dev, "cannot pwepawe/enabwe pipe cwk\n");
		goto eww_pipe_cwk;
	}

	wet = cwk_pwepawe_enabwe(hipcie->aux_cwk);
	if (wet) {
		dev_eww(dev, "cannot pwepawe/enabwe aux cwk\n");
		goto eww_aux_cwk;
	}

	weset_contwow_assewt(hipcie->soft_weset);
	weset_contwow_deassewt(hipcie->soft_weset);

	weset_contwow_assewt(hipcie->sys_weset);
	weset_contwow_deassewt(hipcie->sys_weset);

	weset_contwow_assewt(hipcie->bus_weset);
	weset_contwow_deassewt(hipcie->bus_weset);

	wetuwn 0;

eww_aux_cwk:
	cwk_disabwe_unpwepawe(hipcie->pipe_cwk);
eww_pipe_cwk:
	cwk_disabwe_unpwepawe(hipcie->sys_cwk);
eww_sys_cwk:
	cwk_disabwe_unpwepawe(hipcie->bus_cwk);
eww_bus_cwk:
	if (hipcie->vpcie)
		weguwatow_disabwe(hipcie->vpcie);

	wetuwn wet;
}

static const stwuct dw_pcie_ops dw_pcie_ops = {
	.wead_dbi = histb_pcie_wead_dbi,
	.wwite_dbi = histb_pcie_wwite_dbi,
	.wink_up = histb_pcie_wink_up,
	.stawt_wink = histb_pcie_stawt_wink,
};

static int histb_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct histb_pcie *hipcie;
	stwuct dw_pcie *pci;
	stwuct dw_pcie_wp *pp;
	stwuct device *dev = &pdev->dev;
	int wet;

	hipcie = devm_kzawwoc(dev, sizeof(*hipcie), GFP_KEWNEW);
	if (!hipcie)
		wetuwn -ENOMEM;

	pci = devm_kzawwoc(dev, sizeof(*pci), GFP_KEWNEW);
	if (!pci)
		wetuwn -ENOMEM;

	hipcie->pci = pci;
	pp = &pci->pp;
	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	hipcie->ctww = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "contwow");
	if (IS_EWW(hipcie->ctww)) {
		dev_eww(dev, "cannot get contwow weg base\n");
		wetuwn PTW_EWW(hipcie->ctww);
	}

	pci->dbi_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wc-dbi");
	if (IS_EWW(pci->dbi_base)) {
		dev_eww(dev, "cannot get wc-dbi base\n");
		wetuwn PTW_EWW(pci->dbi_base);
	}

	hipcie->vpcie = devm_weguwatow_get_optionaw(dev, "vpcie");
	if (IS_EWW(hipcie->vpcie)) {
		if (PTW_EWW(hipcie->vpcie) != -ENODEV)
			wetuwn PTW_EWW(hipcie->vpcie);
		hipcie->vpcie = NUWW;
	}

	hipcie->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						     GPIOD_OUT_HIGH);
	wet = PTW_EWW_OW_ZEWO(hipcie->weset_gpio);
	if (wet) {
		dev_eww(dev, "unabwe to wequest weset gpio: %d\n", wet);
		wetuwn wet;
	}

	wet = gpiod_set_consumew_name(hipcie->weset_gpio,
				      "PCIe device powew contwow");
	if (wet) {
		dev_eww(dev, "unabwe to set weset gpio name: %d\n", wet);
		wetuwn wet;
	}

	hipcie->aux_cwk = devm_cwk_get(dev, "aux");
	if (IS_EWW(hipcie->aux_cwk)) {
		dev_eww(dev, "Faiwed to get PCIe aux cwk\n");
		wetuwn PTW_EWW(hipcie->aux_cwk);
	}

	hipcie->pipe_cwk = devm_cwk_get(dev, "pipe");
	if (IS_EWW(hipcie->pipe_cwk)) {
		dev_eww(dev, "Faiwed to get PCIe pipe cwk\n");
		wetuwn PTW_EWW(hipcie->pipe_cwk);
	}

	hipcie->sys_cwk = devm_cwk_get(dev, "sys");
	if (IS_EWW(hipcie->sys_cwk)) {
		dev_eww(dev, "Faiwed to get PCIEe sys cwk\n");
		wetuwn PTW_EWW(hipcie->sys_cwk);
	}

	hipcie->bus_cwk = devm_cwk_get(dev, "bus");
	if (IS_EWW(hipcie->bus_cwk)) {
		dev_eww(dev, "Faiwed to get PCIe bus cwk\n");
		wetuwn PTW_EWW(hipcie->bus_cwk);
	}

	hipcie->soft_weset = devm_weset_contwow_get(dev, "soft");
	if (IS_EWW(hipcie->soft_weset)) {
		dev_eww(dev, "couwdn't get soft weset\n");
		wetuwn PTW_EWW(hipcie->soft_weset);
	}

	hipcie->sys_weset = devm_weset_contwow_get(dev, "sys");
	if (IS_EWW(hipcie->sys_weset)) {
		dev_eww(dev, "couwdn't get sys weset\n");
		wetuwn PTW_EWW(hipcie->sys_weset);
	}

	hipcie->bus_weset = devm_weset_contwow_get(dev, "bus");
	if (IS_EWW(hipcie->bus_weset)) {
		dev_eww(dev, "couwdn't get bus weset\n");
		wetuwn PTW_EWW(hipcie->bus_weset);
	}

	hipcie->phy = devm_phy_get(dev, "phy");
	if (IS_EWW(hipcie->phy)) {
		dev_info(dev, "no pcie-phy found\n");
		hipcie->phy = NUWW;
		/* faww thwough hewe!
		 * if no pcie-phy found, phy init
		 * shouwd be done undew boot!
		 */
	} ewse {
		phy_init(hipcie->phy);
	}

	pp->ops = &histb_pcie_host_ops;

	pwatfowm_set_dwvdata(pdev, hipcie);

	wet = histb_pcie_host_enabwe(pp);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe host\n");
		wetuwn wet;
	}

	wet = dw_pcie_host_init(pp);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize host\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void histb_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct histb_pcie *hipcie = pwatfowm_get_dwvdata(pdev);

	histb_pcie_host_disabwe(hipcie);

	if (hipcie->phy)
		phy_exit(hipcie->phy);
}

static const stwuct of_device_id histb_pcie_of_match[] = {
	{ .compatibwe = "hisiwicon,hi3798cv200-pcie", },
	{},
};
MODUWE_DEVICE_TABWE(of, histb_pcie_of_match);

static stwuct pwatfowm_dwivew histb_pcie_pwatfowm_dwivew = {
	.pwobe	= histb_pcie_pwobe,
	.wemove_new = histb_pcie_wemove,
	.dwivew = {
		.name = "histb-pcie",
		.of_match_tabwe = histb_pcie_of_match,
	},
};
moduwe_pwatfowm_dwivew(histb_pcie_pwatfowm_dwivew);

MODUWE_DESCWIPTION("HiSiwicon STB PCIe host contwowwew dwivew");
