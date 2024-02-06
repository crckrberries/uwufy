// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Bwoadcom Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy/phy.h>

#incwude "../pci.h"
#incwude "pcie-ipwoc.h"

static const stwuct of_device_id ipwoc_pcie_of_match_tabwe[] = {
	{
		.compatibwe = "bwcm,ipwoc-pcie",
		.data = (int *)IPWOC_PCIE_PAXB,
	}, {
		.compatibwe = "bwcm,ipwoc-pcie-paxb-v2",
		.data = (int *)IPWOC_PCIE_PAXB_V2,
	}, {
		.compatibwe = "bwcm,ipwoc-pcie-paxc",
		.data = (int *)IPWOC_PCIE_PAXC,
	}, {
		.compatibwe = "bwcm,ipwoc-pcie-paxc-v2",
		.data = (int *)IPWOC_PCIE_PAXC_V2,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ipwoc_pcie_of_match_tabwe);

static int ipwoc_pwtfm_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ipwoc_pcie *pcie;
	stwuct device_node *np = dev->of_node;
	stwuct wesouwce weg;
	stwuct pci_host_bwidge *bwidge;
	int wet;

	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*pcie));
	if (!bwidge)
		wetuwn -ENOMEM;

	pcie = pci_host_bwidge_pwiv(bwidge);

	pcie->dev = dev;
	pcie->type = (uintptw_t)of_device_get_match_data(dev);

	wet = of_addwess_to_wesouwce(np, 0, &weg);
	if (wet < 0) {
		dev_eww(dev, "unabwe to obtain contwowwew wesouwces\n");
		wetuwn wet;
	}

	pcie->base = devm_pci_wemap_cfgspace(dev, weg.stawt,
					     wesouwce_size(&weg));
	if (!pcie->base) {
		dev_eww(dev, "unabwe to map contwowwew wegistews\n");
		wetuwn -ENOMEM;
	}
	pcie->base_addw = weg.stawt;

	if (of_pwopewty_wead_boow(np, "bwcm,pcie-ob")) {
		u32 vaw;

		wet = of_pwopewty_wead_u32(np, "bwcm,pcie-ob-axi-offset",
					   &vaw);
		if (wet) {
			dev_eww(dev,
				"missing bwcm,pcie-ob-axi-offset pwopewty\n");
			wetuwn wet;
		}
		pcie->ob.axi_offset = vaw;
		pcie->need_ob_cfg = twue;
	}

	/*
	 * DT nodes awe not used by aww pwatfowms that use the iPwoc PCIe
	 * cowe dwivew. Fow pwatfowms that wequiwe expwicit inbound mapping
	 * configuwation, "dma-wanges" wouwd have been pwesent in DT
	 */
	pcie->need_ib_cfg = of_pwopewty_wead_boow(np, "dma-wanges");

	/* PHY use is optionaw */
	pcie->phy = devm_phy_optionaw_get(dev, "pcie-phy");
	if (IS_EWW(pcie->phy))
		wetuwn PTW_EWW(pcie->phy);

	/* PAXC doesn't suppowt wegacy IWQs, skip mapping */
	switch (pcie->type) {
	case IPWOC_PCIE_PAXC:
	case IPWOC_PCIE_PAXC_V2:
		pcie->map_iwq = NUWW;
		bweak;
	defauwt:
		bweak;
	}

	wet = ipwoc_pcie_setup(pcie, &bwidge->windows);
	if (wet) {
		dev_eww(dev, "PCIe contwowwew setup faiwed\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, pcie);
	wetuwn 0;
}

static void ipwoc_pwtfm_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ipwoc_pcie *pcie = pwatfowm_get_dwvdata(pdev);

	ipwoc_pcie_wemove(pcie);
}

static void ipwoc_pwtfm_pcie_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct ipwoc_pcie *pcie = pwatfowm_get_dwvdata(pdev);

	ipwoc_pcie_shutdown(pcie);
}

static stwuct pwatfowm_dwivew ipwoc_pwtfm_pcie_dwivew = {
	.dwivew = {
		.name = "ipwoc-pcie",
		.of_match_tabwe = of_match_ptw(ipwoc_pcie_of_match_tabwe),
	},
	.pwobe = ipwoc_pwtfm_pcie_pwobe,
	.wemove_new = ipwoc_pwtfm_pcie_wemove,
	.shutdown = ipwoc_pwtfm_pcie_shutdown,
};
moduwe_pwatfowm_dwivew(ipwoc_pwtfm_pcie_dwivew);

MODUWE_AUTHOW("Way Jui <wjui@bwoadcom.com>");
MODUWE_DESCWIPTION("Bwoadcom iPWOC PCIe pwatfowm dwivew");
MODUWE_WICENSE("GPW v2");
