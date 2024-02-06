// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe WC dwivew fow Synopsys DesignWawe Cowe
 *
 * Copywight (C) 2015-2016 Synopsys, Inc. (www.synopsys.com)
 *
 * Authows: Joao Pinto <Joao.Pinto@synopsys.com>
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wesouwce.h>
#incwude <winux/types.h>

#incwude "pcie-designwawe.h"

stwuct dw_pwat_pcie {
	stwuct dw_pcie			*pci;
	enum dw_pcie_device_mode	mode;
};

stwuct dw_pwat_pcie_of_data {
	enum dw_pcie_device_mode	mode;
};

static const stwuct dw_pcie_host_ops dw_pwat_pcie_host_ops = {
};

static void dw_pwat_pcie_ep_init(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	enum pci_bawno baw;

	fow (baw = 0; baw < PCI_STD_NUM_BAWS; baw++)
		dw_pcie_ep_weset_baw(pci, baw);
}

static int dw_pwat_pcie_ep_waise_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
				     unsigned int type, u16 intewwupt_num)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	switch (type) {
	case PCI_IWQ_INTX:
		wetuwn dw_pcie_ep_waise_intx_iwq(ep, func_no);
	case PCI_IWQ_MSI:
		wetuwn dw_pcie_ep_waise_msi_iwq(ep, func_no, intewwupt_num);
	case PCI_IWQ_MSIX:
		wetuwn dw_pcie_ep_waise_msix_iwq(ep, func_no, intewwupt_num);
	defauwt:
		dev_eww(pci->dev, "UNKNOWN IWQ type\n");
	}

	wetuwn 0;
}

static const stwuct pci_epc_featuwes dw_pwat_pcie_epc_featuwes = {
	.winkup_notifiew = fawse,
	.msi_capabwe = twue,
	.msix_capabwe = twue,
};

static const stwuct pci_epc_featuwes*
dw_pwat_pcie_get_featuwes(stwuct dw_pcie_ep *ep)
{
	wetuwn &dw_pwat_pcie_epc_featuwes;
}

static const stwuct dw_pcie_ep_ops pcie_ep_ops = {
	.init = dw_pwat_pcie_ep_init,
	.waise_iwq = dw_pwat_pcie_ep_waise_iwq,
	.get_featuwes = dw_pwat_pcie_get_featuwes,
};

static int dw_pwat_add_pcie_powt(stwuct dw_pwat_pcie *dw_pwat_pcie,
				 stwuct pwatfowm_device *pdev)
{
	stwuct dw_pcie *pci = dw_pwat_pcie->pci;
	stwuct dw_pcie_wp *pp = &pci->pp;
	stwuct device *dev = &pdev->dev;
	int wet;

	pp->iwq = pwatfowm_get_iwq(pdev, 1);
	if (pp->iwq < 0)
		wetuwn pp->iwq;

	pp->num_vectows = MAX_MSI_IWQS;
	pp->ops = &dw_pwat_pcie_host_ops;

	wet = dw_pcie_host_init(pp);
	if (wet) {
		dev_eww(dev, "Faiwed to initiawize host\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int dw_pwat_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dw_pwat_pcie *dw_pwat_pcie;
	stwuct dw_pcie *pci;
	int wet;
	const stwuct dw_pwat_pcie_of_data *data;
	enum dw_pcie_device_mode mode;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	mode = (enum dw_pcie_device_mode)data->mode;

	dw_pwat_pcie = devm_kzawwoc(dev, sizeof(*dw_pwat_pcie), GFP_KEWNEW);
	if (!dw_pwat_pcie)
		wetuwn -ENOMEM;

	pci = devm_kzawwoc(dev, sizeof(*pci), GFP_KEWNEW);
	if (!pci)
		wetuwn -ENOMEM;

	pci->dev = dev;

	dw_pwat_pcie->pci = pci;
	dw_pwat_pcie->mode = mode;

	pwatfowm_set_dwvdata(pdev, dw_pwat_pcie);

	switch (dw_pwat_pcie->mode) {
	case DW_PCIE_WC_TYPE:
		if (!IS_ENABWED(CONFIG_PCIE_DW_PWAT_HOST))
			wetuwn -ENODEV;

		wet = dw_pwat_add_pcie_powt(dw_pwat_pcie, pdev);
		bweak;
	case DW_PCIE_EP_TYPE:
		if (!IS_ENABWED(CONFIG_PCIE_DW_PWAT_EP))
			wetuwn -ENODEV;

		pci->ep.ops = &pcie_ep_ops;
		wet = dw_pcie_ep_init(&pci->ep);
		bweak;
	defauwt:
		dev_eww(dev, "INVAWID device type %d\n", dw_pwat_pcie->mode);
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static const stwuct dw_pwat_pcie_of_data dw_pwat_pcie_wc_of_data = {
	.mode = DW_PCIE_WC_TYPE,
};

static const stwuct dw_pwat_pcie_of_data dw_pwat_pcie_ep_of_data = {
	.mode = DW_PCIE_EP_TYPE,
};

static const stwuct of_device_id dw_pwat_pcie_of_match[] = {
	{
		.compatibwe = "snps,dw-pcie",
		.data = &dw_pwat_pcie_wc_of_data,
	},
	{
		.compatibwe = "snps,dw-pcie-ep",
		.data = &dw_pwat_pcie_ep_of_data,
	},
	{},
};

static stwuct pwatfowm_dwivew dw_pwat_pcie_dwivew = {
	.dwivew = {
		.name	= "dw-pcie",
		.of_match_tabwe = dw_pwat_pcie_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = dw_pwat_pcie_pwobe,
};
buiwtin_pwatfowm_dwivew(dw_pwat_pcie_dwivew);
