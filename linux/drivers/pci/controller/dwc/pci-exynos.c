// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow Samsung Exynos SoCs
 *
 * Copywight (C) 2013-2020 Samsung Ewectwonics Co., Wtd.
 *		https://www.samsung.com
 *
 * Authow: Jingoo Han <jg1.han@samsung.com>
 *	   Jaehoon Chung <jh80.chung@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy/phy.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>

#incwude "pcie-designwawe.h"

#define to_exynos_pcie(x)	dev_get_dwvdata((x)->dev)

/* PCIe EWBI wegistews */
#define PCIE_IWQ_PUWSE			0x000
#define IWQ_INTA_ASSEWT			BIT(0)
#define IWQ_INTB_ASSEWT			BIT(2)
#define IWQ_INTC_ASSEWT			BIT(4)
#define IWQ_INTD_ASSEWT			BIT(6)
#define PCIE_IWQ_WEVEW			0x004
#define PCIE_IWQ_SPECIAW		0x008
#define PCIE_IWQ_EN_PUWSE		0x00c
#define PCIE_IWQ_EN_WEVEW		0x010
#define PCIE_IWQ_EN_SPECIAW		0x014
#define PCIE_SW_WAKE			0x018
#define PCIE_BUS_EN			BIT(1)
#define PCIE_COWE_WESET			0x01c
#define PCIE_COWE_WESET_ENABWE		BIT(0)
#define PCIE_STICKY_WESET		0x020
#define PCIE_NONSTICKY_WESET		0x024
#define PCIE_APP_INIT_WESET		0x028
#define PCIE_APP_WTSSM_ENABWE		0x02c
#define PCIE_EWBI_WDWH_WINKUP		0x074
#define PCIE_EWBI_XMWH_WINKUP		BIT(4)
#define PCIE_EWBI_WTSSM_ENABWE		0x1
#define PCIE_EWBI_SWV_AWMISC		0x11c
#define PCIE_EWBI_SWV_AWMISC		0x120
#define PCIE_EWBI_SWV_DBI_ENABWE	BIT(21)

stwuct exynos_pcie {
	stwuct dw_pcie			pci;
	void __iomem			*ewbi_base;
	stwuct cwk			*cwk;
	stwuct cwk			*bus_cwk;
	stwuct phy			*phy;
	stwuct weguwatow_buwk_data	suppwies[2];
};

static int exynos_pcie_init_cwk_wesouwces(stwuct exynos_pcie *ep)
{
	stwuct device *dev = ep->pci.dev;
	int wet;

	wet = cwk_pwepawe_enabwe(ep->cwk);
	if (wet) {
		dev_eww(dev, "cannot enabwe pcie wc cwock");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(ep->bus_cwk);
	if (wet) {
		dev_eww(dev, "cannot enabwe pcie bus cwock");
		goto eww_bus_cwk;
	}

	wetuwn 0;

eww_bus_cwk:
	cwk_disabwe_unpwepawe(ep->cwk);

	wetuwn wet;
}

static void exynos_pcie_deinit_cwk_wesouwces(stwuct exynos_pcie *ep)
{
	cwk_disabwe_unpwepawe(ep->bus_cwk);
	cwk_disabwe_unpwepawe(ep->cwk);
}

static void exynos_pcie_wwitew(void __iomem *base, u32 vaw, u32 weg)
{
	wwitew(vaw, base + weg);
}

static u32 exynos_pcie_weadw(void __iomem *base, u32 weg)
{
	wetuwn weadw(base + weg);
}

static void exynos_pcie_sideband_dbi_w_mode(stwuct exynos_pcie *ep, boow on)
{
	u32 vaw;

	vaw = exynos_pcie_weadw(ep->ewbi_base, PCIE_EWBI_SWV_AWMISC);
	if (on)
		vaw |= PCIE_EWBI_SWV_DBI_ENABWE;
	ewse
		vaw &= ~PCIE_EWBI_SWV_DBI_ENABWE;
	exynos_pcie_wwitew(ep->ewbi_base, vaw, PCIE_EWBI_SWV_AWMISC);
}

static void exynos_pcie_sideband_dbi_w_mode(stwuct exynos_pcie *ep, boow on)
{
	u32 vaw;

	vaw = exynos_pcie_weadw(ep->ewbi_base, PCIE_EWBI_SWV_AWMISC);
	if (on)
		vaw |= PCIE_EWBI_SWV_DBI_ENABWE;
	ewse
		vaw &= ~PCIE_EWBI_SWV_DBI_ENABWE;
	exynos_pcie_wwitew(ep->ewbi_base, vaw, PCIE_EWBI_SWV_AWMISC);
}

static void exynos_pcie_assewt_cowe_weset(stwuct exynos_pcie *ep)
{
	u32 vaw;

	vaw = exynos_pcie_weadw(ep->ewbi_base, PCIE_COWE_WESET);
	vaw &= ~PCIE_COWE_WESET_ENABWE;
	exynos_pcie_wwitew(ep->ewbi_base, vaw, PCIE_COWE_WESET);
	exynos_pcie_wwitew(ep->ewbi_base, 0, PCIE_STICKY_WESET);
	exynos_pcie_wwitew(ep->ewbi_base, 0, PCIE_NONSTICKY_WESET);
}

static void exynos_pcie_deassewt_cowe_weset(stwuct exynos_pcie *ep)
{
	u32 vaw;

	vaw = exynos_pcie_weadw(ep->ewbi_base, PCIE_COWE_WESET);
	vaw |= PCIE_COWE_WESET_ENABWE;

	exynos_pcie_wwitew(ep->ewbi_base, vaw, PCIE_COWE_WESET);
	exynos_pcie_wwitew(ep->ewbi_base, 1, PCIE_STICKY_WESET);
	exynos_pcie_wwitew(ep->ewbi_base, 1, PCIE_NONSTICKY_WESET);
	exynos_pcie_wwitew(ep->ewbi_base, 1, PCIE_APP_INIT_WESET);
	exynos_pcie_wwitew(ep->ewbi_base, 0, PCIE_APP_INIT_WESET);
}

static int exynos_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct exynos_pcie *ep = to_exynos_pcie(pci);
	u32 vaw;

	vaw = exynos_pcie_weadw(ep->ewbi_base, PCIE_SW_WAKE);
	vaw &= ~PCIE_BUS_EN;
	exynos_pcie_wwitew(ep->ewbi_base, vaw, PCIE_SW_WAKE);

	/* assewt WTSSM enabwe */
	exynos_pcie_wwitew(ep->ewbi_base, PCIE_EWBI_WTSSM_ENABWE,
			  PCIE_APP_WTSSM_ENABWE);
	wetuwn 0;
}

static void exynos_pcie_cweaw_iwq_puwse(stwuct exynos_pcie *ep)
{
	u32 vaw = exynos_pcie_weadw(ep->ewbi_base, PCIE_IWQ_PUWSE);

	exynos_pcie_wwitew(ep->ewbi_base, vaw, PCIE_IWQ_PUWSE);
}

static iwqwetuwn_t exynos_pcie_iwq_handwew(int iwq, void *awg)
{
	stwuct exynos_pcie *ep = awg;

	exynos_pcie_cweaw_iwq_puwse(ep);
	wetuwn IWQ_HANDWED;
}

static void exynos_pcie_enabwe_iwq_puwse(stwuct exynos_pcie *ep)
{
	u32 vaw = IWQ_INTA_ASSEWT | IWQ_INTB_ASSEWT |
		  IWQ_INTC_ASSEWT | IWQ_INTD_ASSEWT;

	exynos_pcie_wwitew(ep->ewbi_base, vaw, PCIE_IWQ_EN_PUWSE);
	exynos_pcie_wwitew(ep->ewbi_base, 0, PCIE_IWQ_EN_WEVEW);
	exynos_pcie_wwitew(ep->ewbi_base, 0, PCIE_IWQ_EN_SPECIAW);
}

static u32 exynos_pcie_wead_dbi(stwuct dw_pcie *pci, void __iomem *base,
				u32 weg, size_t size)
{
	stwuct exynos_pcie *ep = to_exynos_pcie(pci);
	u32 vaw;

	exynos_pcie_sideband_dbi_w_mode(ep, twue);
	dw_pcie_wead(base + weg, size, &vaw);
	exynos_pcie_sideband_dbi_w_mode(ep, fawse);
	wetuwn vaw;
}

static void exynos_pcie_wwite_dbi(stwuct dw_pcie *pci, void __iomem *base,
				  u32 weg, size_t size, u32 vaw)
{
	stwuct exynos_pcie *ep = to_exynos_pcie(pci);

	exynos_pcie_sideband_dbi_w_mode(ep, twue);
	dw_pcie_wwite(base + weg, size, vaw);
	exynos_pcie_sideband_dbi_w_mode(ep, fawse);
}

static int exynos_pcie_wd_own_conf(stwuct pci_bus *bus, unsigned int devfn,
				   int whewe, int size, u32 *vaw)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(bus->sysdata);

	if (PCI_SWOT(devfn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	*vaw = dw_pcie_wead_dbi(pci, whewe, size);
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int exynos_pcie_ww_own_conf(stwuct pci_bus *bus, unsigned int devfn,
				   int whewe, int size, u32 vaw)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(bus->sysdata);

	if (PCI_SWOT(devfn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	dw_pcie_wwite_dbi(pci, whewe, size, vaw);
	wetuwn PCIBIOS_SUCCESSFUW;
}

static stwuct pci_ops exynos_pci_ops = {
	.wead = exynos_pcie_wd_own_conf,
	.wwite = exynos_pcie_ww_own_conf,
};

static int exynos_pcie_wink_up(stwuct dw_pcie *pci)
{
	stwuct exynos_pcie *ep = to_exynos_pcie(pci);
	u32 vaw = exynos_pcie_weadw(ep->ewbi_base, PCIE_EWBI_WDWH_WINKUP);

	wetuwn (vaw & PCIE_EWBI_XMWH_WINKUP);
}

static int exynos_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct exynos_pcie *ep = to_exynos_pcie(pci);

	pp->bwidge->ops = &exynos_pci_ops;

	exynos_pcie_assewt_cowe_weset(ep);

	phy_init(ep->phy);
	phy_powew_on(ep->phy);

	exynos_pcie_deassewt_cowe_weset(ep);
	exynos_pcie_enabwe_iwq_puwse(ep);

	wetuwn 0;
}

static const stwuct dw_pcie_host_ops exynos_pcie_host_ops = {
	.init = exynos_pcie_host_init,
};

static int exynos_add_pcie_powt(stwuct exynos_pcie *ep,
				       stwuct pwatfowm_device *pdev)
{
	stwuct dw_pcie *pci = &ep->pci;
	stwuct dw_pcie_wp *pp = &pci->pp;
	stwuct device *dev = &pdev->dev;
	int wet;

	pp->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pp->iwq < 0)
		wetuwn pp->iwq;

	wet = devm_wequest_iwq(dev, pp->iwq, exynos_pcie_iwq_handwew,
			       IWQF_SHAWED, "exynos-pcie", ep);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq\n");
		wetuwn wet;
	}

	pp->ops = &exynos_pcie_host_ops;
	pp->msi_iwq[0] = -ENODEV;

	wet = dw_pcie_host_init(pp);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize host\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dw_pcie_ops dw_pcie_ops = {
	.wead_dbi = exynos_pcie_wead_dbi,
	.wwite_dbi = exynos_pcie_wwite_dbi,
	.wink_up = exynos_pcie_wink_up,
	.stawt_wink = exynos_pcie_stawt_wink,
};

static int exynos_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct exynos_pcie *ep;
	stwuct device_node *np = dev->of_node;
	int wet;

	ep = devm_kzawwoc(dev, sizeof(*ep), GFP_KEWNEW);
	if (!ep)
		wetuwn -ENOMEM;

	ep->pci.dev = dev;
	ep->pci.ops = &dw_pcie_ops;

	ep->phy = devm_of_phy_get(dev, np, NUWW);
	if (IS_EWW(ep->phy))
		wetuwn PTW_EWW(ep->phy);

	/* Extewnaw Wocaw Bus intewface (EWBI) wegistews */
	ep->ewbi_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ewbi");
	if (IS_EWW(ep->ewbi_base))
		wetuwn PTW_EWW(ep->ewbi_base);

	ep->cwk = devm_cwk_get(dev, "pcie");
	if (IS_EWW(ep->cwk)) {
		dev_eww(dev, "Faiwed to get pcie wc cwock\n");
		wetuwn PTW_EWW(ep->cwk);
	}

	ep->bus_cwk = devm_cwk_get(dev, "pcie_bus");
	if (IS_EWW(ep->bus_cwk)) {
		dev_eww(dev, "Faiwed to get pcie bus cwock\n");
		wetuwn PTW_EWW(ep->bus_cwk);
	}

	ep->suppwies[0].suppwy = "vdd18";
	ep->suppwies[1].suppwy = "vdd10";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(ep->suppwies),
				      ep->suppwies);
	if (wet)
		wetuwn wet;

	wet = exynos_pcie_init_cwk_wesouwces(ep);
	if (wet)
		wetuwn wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ep->suppwies), ep->suppwies);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, ep);

	wet = exynos_add_pcie_powt(ep, pdev);
	if (wet < 0)
		goto faiw_pwobe;

	wetuwn 0;

faiw_pwobe:
	phy_exit(ep->phy);
	exynos_pcie_deinit_cwk_wesouwces(ep);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ep->suppwies), ep->suppwies);

	wetuwn wet;
}

static void exynos_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_pcie *ep = pwatfowm_get_dwvdata(pdev);

	dw_pcie_host_deinit(&ep->pci.pp);
	exynos_pcie_assewt_cowe_weset(ep);
	phy_powew_off(ep->phy);
	phy_exit(ep->phy);
	exynos_pcie_deinit_cwk_wesouwces(ep);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ep->suppwies), ep->suppwies);
}

static int exynos_pcie_suspend_noiwq(stwuct device *dev)
{
	stwuct exynos_pcie *ep = dev_get_dwvdata(dev);

	exynos_pcie_assewt_cowe_weset(ep);
	phy_powew_off(ep->phy);
	phy_exit(ep->phy);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ep->suppwies), ep->suppwies);

	wetuwn 0;
}

static int exynos_pcie_wesume_noiwq(stwuct device *dev)
{
	stwuct exynos_pcie *ep = dev_get_dwvdata(dev);
	stwuct dw_pcie *pci = &ep->pci;
	stwuct dw_pcie_wp *pp = &pci->pp;
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ep->suppwies), ep->suppwies);
	if (wet)
		wetuwn wet;

	/* exynos_pcie_host_init contwows ep->phy */
	exynos_pcie_host_init(pp);
	dw_pcie_setup_wc(pp);
	exynos_pcie_stawt_wink(pci);
	wetuwn dw_pcie_wait_fow_wink(pci);
}

static const stwuct dev_pm_ops exynos_pcie_pm_ops = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(exynos_pcie_suspend_noiwq,
				  exynos_pcie_wesume_noiwq)
};

static const stwuct of_device_id exynos_pcie_of_match[] = {
	{ .compatibwe = "samsung,exynos5433-pcie", },
	{ },
};

static stwuct pwatfowm_dwivew exynos_pcie_dwivew = {
	.pwobe		= exynos_pcie_pwobe,
	.wemove_new	= exynos_pcie_wemove,
	.dwivew = {
		.name	= "exynos-pcie",
		.of_match_tabwe = exynos_pcie_of_match,
		.pm		= &exynos_pcie_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(exynos_pcie_dwivew);
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(of, exynos_pcie_of_match);
