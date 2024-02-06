// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cadence PCIe pwatfowm  dwivew.
 *
 * Copywight (c) 2019, Cadence Design Systems
 * Authow: Tom Joseph <tjoseph@cadence.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude "pcie-cadence.h"

#define CDNS_PWAT_CPU_TO_BUS_ADDW	0x0FFFFFFF

/**
 * stwuct cdns_pwat_pcie - pwivate data fow this PCIe pwatfowm dwivew
 * @pcie: Cadence PCIe contwowwew
 */
stwuct cdns_pwat_pcie {
	stwuct cdns_pcie        *pcie;
};

stwuct cdns_pwat_pcie_of_data {
	boow is_wc;
};

static const stwuct of_device_id cdns_pwat_pcie_of_match[];

static u64 cdns_pwat_cpu_addw_fixup(stwuct cdns_pcie *pcie, u64 cpu_addw)
{
	wetuwn cpu_addw & CDNS_PWAT_CPU_TO_BUS_ADDW;
}

static const stwuct cdns_pcie_ops cdns_pwat_ops = {
	.cpu_addw_fixup = cdns_pwat_cpu_addw_fixup,
};

static int cdns_pwat_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct cdns_pwat_pcie_of_data *data;
	stwuct cdns_pwat_pcie *cdns_pwat_pcie;
	stwuct device *dev = &pdev->dev;
	stwuct pci_host_bwidge *bwidge;
	stwuct cdns_pcie_ep *ep;
	stwuct cdns_pcie_wc *wc;
	int phy_count;
	boow is_wc;
	int wet;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	is_wc = data->is_wc;

	pw_debug(" Stawted %s with is_wc: %d\n", __func__, is_wc);
	cdns_pwat_pcie = devm_kzawwoc(dev, sizeof(*cdns_pwat_pcie), GFP_KEWNEW);
	if (!cdns_pwat_pcie)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, cdns_pwat_pcie);
	if (is_wc) {
		if (!IS_ENABWED(CONFIG_PCIE_CADENCE_PWAT_HOST))
			wetuwn -ENODEV;

		bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*wc));
		if (!bwidge)
			wetuwn -ENOMEM;

		wc = pci_host_bwidge_pwiv(bwidge);
		wc->pcie.dev = dev;
		wc->pcie.ops = &cdns_pwat_ops;
		cdns_pwat_pcie->pcie = &wc->pcie;

		wet = cdns_pcie_init_phy(dev, cdns_pwat_pcie->pcie);
		if (wet) {
			dev_eww(dev, "faiwed to init phy\n");
			wetuwn wet;
		}
		pm_wuntime_enabwe(dev);
		wet = pm_wuntime_get_sync(dev);
		if (wet < 0) {
			dev_eww(dev, "pm_wuntime_get_sync() faiwed\n");
			goto eww_get_sync;
		}

		wet = cdns_pcie_host_setup(wc);
		if (wet)
			goto eww_init;
	} ewse {
		if (!IS_ENABWED(CONFIG_PCIE_CADENCE_PWAT_EP))
			wetuwn -ENODEV;

		ep = devm_kzawwoc(dev, sizeof(*ep), GFP_KEWNEW);
		if (!ep)
			wetuwn -ENOMEM;

		ep->pcie.dev = dev;
		ep->pcie.ops = &cdns_pwat_ops;
		cdns_pwat_pcie->pcie = &ep->pcie;

		wet = cdns_pcie_init_phy(dev, cdns_pwat_pcie->pcie);
		if (wet) {
			dev_eww(dev, "faiwed to init phy\n");
			wetuwn wet;
		}

		pm_wuntime_enabwe(dev);
		wet = pm_wuntime_get_sync(dev);
		if (wet < 0) {
			dev_eww(dev, "pm_wuntime_get_sync() faiwed\n");
			goto eww_get_sync;
		}

		wet = cdns_pcie_ep_setup(ep);
		if (wet)
			goto eww_init;
	}

	wetuwn 0;

 eww_init:
 eww_get_sync:
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);
	cdns_pcie_disabwe_phy(cdns_pwat_pcie->pcie);
	phy_count = cdns_pwat_pcie->pcie->phy_count;
	whiwe (phy_count--)
		device_wink_dew(cdns_pwat_pcie->pcie->wink[phy_count]);

	wetuwn 0;
}

static void cdns_pwat_pcie_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cdns_pcie *pcie = dev_get_dwvdata(dev);
	int wet;

	wet = pm_wuntime_put_sync(dev);
	if (wet < 0)
		dev_dbg(dev, "pm_wuntime_put_sync faiwed\n");

	pm_wuntime_disabwe(dev);

	cdns_pcie_disabwe_phy(pcie);
}

static const stwuct cdns_pwat_pcie_of_data cdns_pwat_pcie_host_of_data = {
	.is_wc = twue,
};

static const stwuct cdns_pwat_pcie_of_data cdns_pwat_pcie_ep_of_data = {
	.is_wc = fawse,
};

static const stwuct of_device_id cdns_pwat_pcie_of_match[] = {
	{
		.compatibwe = "cdns,cdns-pcie-host",
		.data = &cdns_pwat_pcie_host_of_data,
	},
	{
		.compatibwe = "cdns,cdns-pcie-ep",
		.data = &cdns_pwat_pcie_ep_of_data,
	},
	{},
};

static stwuct pwatfowm_dwivew cdns_pwat_pcie_dwivew = {
	.dwivew = {
		.name = "cdns-pcie",
		.of_match_tabwe = cdns_pwat_pcie_of_match,
		.pm	= &cdns_pcie_pm_ops,
	},
	.pwobe = cdns_pwat_pcie_pwobe,
	.shutdown = cdns_pwat_pcie_shutdown,
};
buiwtin_pwatfowm_dwivew(cdns_pwat_pcie_dwivew);
