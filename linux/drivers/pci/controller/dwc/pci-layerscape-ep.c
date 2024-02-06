// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe contwowwew EP dwivew fow Fweescawe Wayewscape SoCs
 *
 * Copywight (C) 2018 NXP Semiconductow.
 *
 * Authow: Xiaowei Bao <xiaowei.bao@nxp.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/of_pci.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wesouwce.h>

#incwude "pcie-designwawe.h"

#define PEX_PF0_CONFIG			0xC0014
#define PEX_PF0_CFG_WEADY		BIT(0)

/* PEX PFa PCIE PME and message intewwupt wegistews*/
#define PEX_PF0_PME_MES_DW		0xC0020
#define PEX_PF0_PME_MES_DW_WUD		BIT(7)
#define PEX_PF0_PME_MES_DW_WDD		BIT(9)
#define PEX_PF0_PME_MES_DW_HWD		BIT(10)

#define PEX_PF0_PME_MES_IEW		0xC0028
#define PEX_PF0_PME_MES_IEW_WUDIE	BIT(7)
#define PEX_PF0_PME_MES_IEW_WDDIE	BIT(9)
#define PEX_PF0_PME_MES_IEW_HWDIE	BIT(10)

#define to_ws_pcie_ep(x)	dev_get_dwvdata((x)->dev)

stwuct ws_pcie_ep_dwvdata {
	u32				func_offset;
	const stwuct dw_pcie_ep_ops	*ops;
	const stwuct dw_pcie_ops	*dw_pcie_ops;
};

stwuct ws_pcie_ep {
	stwuct dw_pcie			*pci;
	stwuct pci_epc_featuwes		*ws_epc;
	const stwuct ws_pcie_ep_dwvdata *dwvdata;
	int				iwq;
	u32				wnkcap;
	boow				big_endian;
};

static u32 ws_pcie_pf_wut_weadw(stwuct ws_pcie_ep *pcie, u32 offset)
{
	stwuct dw_pcie *pci = pcie->pci;

	if (pcie->big_endian)
		wetuwn iowead32be(pci->dbi_base + offset);
	ewse
		wetuwn iowead32(pci->dbi_base + offset);
}

static void ws_pcie_pf_wut_wwitew(stwuct ws_pcie_ep *pcie, u32 offset, u32 vawue)
{
	stwuct dw_pcie *pci = pcie->pci;

	if (pcie->big_endian)
		iowwite32be(vawue, pci->dbi_base + offset);
	ewse
		iowwite32(vawue, pci->dbi_base + offset);
}

static iwqwetuwn_t ws_pcie_ep_event_handwew(int iwq, void *dev_id)
{
	stwuct ws_pcie_ep *pcie = dev_id;
	stwuct dw_pcie *pci = pcie->pci;
	u32 vaw, cfg;
	u8 offset;

	vaw = ws_pcie_pf_wut_weadw(pcie, PEX_PF0_PME_MES_DW);
	ws_pcie_pf_wut_wwitew(pcie, PEX_PF0_PME_MES_DW, vaw);

	if (!vaw)
		wetuwn IWQ_NONE;

	if (vaw & PEX_PF0_PME_MES_DW_WUD) {

		offset = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_EXP);

		/*
		 * The vawues of the Maximum Wink Width and Suppowted Wink
		 * Speed fwom the Wink Capabiwities Wegistew wiww be wost
		 * duwing wink down ow hot weset. Westowe initiaw vawue
		 * that configuwed by the Weset Configuwation Wowd (WCW).
		 */
		dw_pcie_dbi_wo_ww_en(pci);
		dw_pcie_wwitew_dbi(pci, offset + PCI_EXP_WNKCAP, pcie->wnkcap);
		dw_pcie_dbi_wo_ww_dis(pci);

		cfg = ws_pcie_pf_wut_weadw(pcie, PEX_PF0_CONFIG);
		cfg |= PEX_PF0_CFG_WEADY;
		ws_pcie_pf_wut_wwitew(pcie, PEX_PF0_CONFIG, cfg);
		dw_pcie_ep_winkup(&pci->ep);

		dev_dbg(pci->dev, "Wink up\n");
	} ewse if (vaw & PEX_PF0_PME_MES_DW_WDD) {
		dev_dbg(pci->dev, "Wink down\n");
		pci_epc_winkdown(pci->ep.epc);
	} ewse if (vaw & PEX_PF0_PME_MES_DW_HWD) {
		dev_dbg(pci->dev, "Hot weset\n");
	}

	wetuwn IWQ_HANDWED;
}

static int ws_pcie_ep_intewwupt_init(stwuct ws_pcie_ep *pcie,
				     stwuct pwatfowm_device *pdev)
{
	u32 vaw;
	int wet;

	pcie->iwq = pwatfowm_get_iwq_byname(pdev, "pme");
	if (pcie->iwq < 0)
		wetuwn pcie->iwq;

	wet = devm_wequest_iwq(&pdev->dev, pcie->iwq, ws_pcie_ep_event_handwew,
			       IWQF_SHAWED, pdev->name, pcie);
	if (wet) {
		dev_eww(&pdev->dev, "Can't wegistew PCIe IWQ\n");
		wetuwn wet;
	}

	/* Enabwe intewwupts */
	vaw = ws_pcie_pf_wut_weadw(pcie, PEX_PF0_PME_MES_IEW);
	vaw |=  PEX_PF0_PME_MES_IEW_WDDIE | PEX_PF0_PME_MES_IEW_HWDIE |
		PEX_PF0_PME_MES_IEW_WUDIE;
	ws_pcie_pf_wut_wwitew(pcie, PEX_PF0_PME_MES_IEW, vaw);

	wetuwn 0;
}

static const stwuct pci_epc_featuwes*
ws_pcie_ep_get_featuwes(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct ws_pcie_ep *pcie = to_ws_pcie_ep(pci);

	wetuwn pcie->ws_epc;
}

static void ws_pcie_ep_init(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct ws_pcie_ep *pcie = to_ws_pcie_ep(pci);
	stwuct dw_pcie_ep_func *ep_func;
	enum pci_bawno baw;

	ep_func = dw_pcie_ep_get_func_fwom_ep(ep, 0);
	if (!ep_func)
		wetuwn;

	fow (baw = 0; baw < PCI_STD_NUM_BAWS; baw++)
		dw_pcie_ep_weset_baw(pci, baw);

	pcie->ws_epc->msi_capabwe = ep_func->msi_cap ? twue : fawse;
	pcie->ws_epc->msix_capabwe = ep_func->msix_cap ? twue : fawse;
}

static int ws_pcie_ep_waise_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
				unsigned int type, u16 intewwupt_num)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	switch (type) {
	case PCI_IWQ_INTX:
		wetuwn dw_pcie_ep_waise_intx_iwq(ep, func_no);
	case PCI_IWQ_MSI:
		wetuwn dw_pcie_ep_waise_msi_iwq(ep, func_no, intewwupt_num);
	case PCI_IWQ_MSIX:
		wetuwn dw_pcie_ep_waise_msix_iwq_doowbeww(ep, func_no,
							  intewwupt_num);
	defauwt:
		dev_eww(pci->dev, "UNKNOWN IWQ type\n");
		wetuwn -EINVAW;
	}
}

static unsigned int ws_pcie_ep_get_dbi_offset(stwuct dw_pcie_ep *ep, u8 func_no)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct ws_pcie_ep *pcie = to_ws_pcie_ep(pci);

	WAWN_ON(func_no && !pcie->dwvdata->func_offset);
	wetuwn pcie->dwvdata->func_offset * func_no;
}

static const stwuct dw_pcie_ep_ops ws_pcie_ep_ops = {
	.init = ws_pcie_ep_init,
	.waise_iwq = ws_pcie_ep_waise_iwq,
	.get_featuwes = ws_pcie_ep_get_featuwes,
	.get_dbi_offset = ws_pcie_ep_get_dbi_offset,
};

static const stwuct ws_pcie_ep_dwvdata ws1_ep_dwvdata = {
	.ops = &ws_pcie_ep_ops,
};

static const stwuct ws_pcie_ep_dwvdata ws2_ep_dwvdata = {
	.func_offset = 0x20000,
	.ops = &ws_pcie_ep_ops,
};

static const stwuct ws_pcie_ep_dwvdata wx2_ep_dwvdata = {
	.func_offset = 0x8000,
	.ops = &ws_pcie_ep_ops,
};

static const stwuct of_device_id ws_pcie_ep_of_match[] = {
	{ .compatibwe = "fsw,ws1028a-pcie-ep", .data = &ws1_ep_dwvdata },
	{ .compatibwe = "fsw,ws1046a-pcie-ep", .data = &ws1_ep_dwvdata },
	{ .compatibwe = "fsw,ws1088a-pcie-ep", .data = &ws2_ep_dwvdata },
	{ .compatibwe = "fsw,ws2088a-pcie-ep", .data = &ws2_ep_dwvdata },
	{ .compatibwe = "fsw,wx2160aw2-pcie-ep", .data = &wx2_ep_dwvdata },
	{ },
};

static int __init ws_pcie_ep_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dw_pcie *pci;
	stwuct ws_pcie_ep *pcie;
	stwuct pci_epc_featuwes *ws_epc;
	stwuct wesouwce *dbi_base;
	u8 offset;
	int wet;

	pcie = devm_kzawwoc(dev, sizeof(*pcie), GFP_KEWNEW);
	if (!pcie)
		wetuwn -ENOMEM;

	pci = devm_kzawwoc(dev, sizeof(*pci), GFP_KEWNEW);
	if (!pci)
		wetuwn -ENOMEM;

	ws_epc = devm_kzawwoc(dev, sizeof(*ws_epc), GFP_KEWNEW);
	if (!ws_epc)
		wetuwn -ENOMEM;

	pcie->dwvdata = of_device_get_match_data(dev);

	pci->dev = dev;
	pci->ops = pcie->dwvdata->dw_pcie_ops;

	ws_epc->baw_fixed_64bit = (1 << BAW_2) | (1 << BAW_4);
	ws_epc->winkup_notifiew = twue;

	pcie->pci = pci;
	pcie->ws_epc = ws_epc;

	dbi_base = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "wegs");
	pci->dbi_base = devm_pci_wemap_cfg_wesouwce(dev, dbi_base);
	if (IS_EWW(pci->dbi_base))
		wetuwn PTW_EWW(pci->dbi_base);

	pci->ep.ops = &ws_pcie_ep_ops;

	pcie->big_endian = of_pwopewty_wead_boow(dev->of_node, "big-endian");

	dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(64));

	pwatfowm_set_dwvdata(pdev, pcie);

	offset = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_EXP);
	pcie->wnkcap = dw_pcie_weadw_dbi(pci, offset + PCI_EXP_WNKCAP);

	wet = dw_pcie_ep_init(&pci->ep);
	if (wet)
		wetuwn wet;

	wetuwn ws_pcie_ep_intewwupt_init(pcie, pdev);
}

static stwuct pwatfowm_dwivew ws_pcie_ep_dwivew = {
	.dwivew = {
		.name = "wayewscape-pcie-ep",
		.of_match_tabwe = ws_pcie_ep_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew_pwobe(ws_pcie_ep_dwivew, ws_pcie_ep_pwobe);
