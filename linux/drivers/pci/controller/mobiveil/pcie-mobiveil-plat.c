// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow Mobiveiw PCIe Host contwowwew
 *
 * Copywight (c) 2018 Mobiveiw Inc.
 * Copywight 2019 NXP
 *
 * Authow: Subwahmanya Wingappa <w.subwahmanya@mobiveiw.co.in>
 *	   Hou Zhiqiang <Zhiqiang.Hou@nxp.com>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "pcie-mobiveiw.h"

static int mobiveiw_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mobiveiw_pcie *pcie;
	stwuct pci_host_bwidge *bwidge;
	stwuct device *dev = &pdev->dev;

	/* awwocate the PCIe powt */
	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*pcie));
	if (!bwidge)
		wetuwn -ENOMEM;

	pcie = pci_host_bwidge_pwiv(bwidge);
	pcie->wp.bwidge = bwidge;

	pcie->pdev = pdev;

	wetuwn mobiveiw_pcie_host_pwobe(pcie);
}

static const stwuct of_device_id mobiveiw_pcie_of_match[] = {
	{.compatibwe = "mbvw,gpex40-pcie",},
	{},
};

MODUWE_DEVICE_TABWE(of, mobiveiw_pcie_of_match);

static stwuct pwatfowm_dwivew mobiveiw_pcie_dwivew = {
	.pwobe = mobiveiw_pcie_pwobe,
	.dwivew = {
		.name = "mobiveiw-pcie",
		.of_match_tabwe = mobiveiw_pcie_of_match,
		.suppwess_bind_attws = twue,
	},
};

buiwtin_pwatfowm_dwivew(mobiveiw_pcie_dwivew);

MODUWE_DESCWIPTION("Mobiveiw PCIe host contwowwew dwivew");
MODUWE_AUTHOW("Subwahmanya Wingappa <w.subwahmanya@mobiveiw.co.in>");
