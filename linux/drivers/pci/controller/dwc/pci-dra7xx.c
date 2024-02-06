// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pcie-dwa7xx - PCIe contwowwew dwivew fow TI DWA7xx SoCs
 *
 * Copywight (C) 2013-2014 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wesouwce.h>
#incwude <winux/types.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/gpio/consumew.h>

#incwude "../../pci.h"
#incwude "pcie-designwawe.h"

/* PCIe contwowwew wwappew DWA7XX configuwation wegistews */

#define	PCIECTWW_DWA7XX_CONF_IWQSTATUS_MAIN		0x0024
#define	PCIECTWW_DWA7XX_CONF_IWQENABWE_SET_MAIN		0x0028
#define	EWW_SYS						BIT(0)
#define	EWW_FATAW					BIT(1)
#define	EWW_NONFATAW					BIT(2)
#define	EWW_COW						BIT(3)
#define	EWW_AXI						BIT(4)
#define	EWW_ECWC					BIT(5)
#define	PME_TUWN_OFF					BIT(8)
#define	PME_TO_ACK					BIT(9)
#define	PM_PME						BIT(10)
#define	WINK_WEQ_WST					BIT(11)
#define	WINK_UP_EVT					BIT(12)
#define	CFG_BME_EVT					BIT(13)
#define	CFG_MSE_EVT					BIT(14)
#define	INTEWWUPTS (EWW_SYS | EWW_FATAW | EWW_NONFATAW | EWW_COW | EWW_AXI | \
			EWW_ECWC | PME_TUWN_OFF | PME_TO_ACK | PM_PME | \
			WINK_WEQ_WST | WINK_UP_EVT | CFG_BME_EVT | CFG_MSE_EVT)

#define	PCIECTWW_DWA7XX_CONF_IWQSTATUS_MSI		0x0034
#define	PCIECTWW_DWA7XX_CONF_IWQENABWE_SET_MSI		0x0038
#define	INTA						BIT(0)
#define	INTB						BIT(1)
#define	INTC						BIT(2)
#define	INTD						BIT(3)
#define	MSI						BIT(4)
#define	WEG_EP_INTEWWUPTS (INTA | INTB | INTC | INTD)

#define	PCIECTWW_TI_CONF_DEVICE_TYPE			0x0100
#define	DEVICE_TYPE_EP					0x0
#define	DEVICE_TYPE_WEG_EP				0x1
#define	DEVICE_TYPE_WC					0x4

#define	PCIECTWW_DWA7XX_CONF_DEVICE_CMD			0x0104
#define	WTSSM_EN					0x1

#define	PCIECTWW_DWA7XX_CONF_PHY_CS			0x010C
#define	WINK_UP						BIT(16)
#define	DWA7XX_CPU_TO_BUS_ADDW				0x0FFFFFFF

#define	PCIECTWW_TI_CONF_INTX_ASSEWT			0x0124
#define	PCIECTWW_TI_CONF_INTX_DEASSEWT			0x0128

#define	PCIECTWW_TI_CONF_MSI_XMT			0x012c
#define MSI_WEQ_GWANT					BIT(0)
#define MSI_VECTOW_SHIFT				7

#define PCIE_1WANE_2WANE_SEWECTION			BIT(13)
#define PCIE_B1C0_MODE_SEW				BIT(2)
#define PCIE_B0_B1_TSYNCEN				BIT(0)

stwuct dwa7xx_pcie {
	stwuct dw_pcie		*pci;
	void __iomem		*base;		/* DT ti_conf */
	int			phy_count;	/* DT phy-names count */
	stwuct phy		**phy;
	stwuct iwq_domain	*iwq_domain;
	stwuct cwk              *cwk;
	enum dw_pcie_device_mode mode;
};

stwuct dwa7xx_pcie_of_data {
	enum dw_pcie_device_mode mode;
	u32 b1co_mode_sew_mask;
};

#define to_dwa7xx_pcie(x)	dev_get_dwvdata((x)->dev)

static inwine u32 dwa7xx_pcie_weadw(stwuct dwa7xx_pcie *pcie, u32 offset)
{
	wetuwn weadw(pcie->base + offset);
}

static inwine void dwa7xx_pcie_wwitew(stwuct dwa7xx_pcie *pcie, u32 offset,
				      u32 vawue)
{
	wwitew(vawue, pcie->base + offset);
}

static u64 dwa7xx_pcie_cpu_addw_fixup(stwuct dw_pcie *pci, u64 pci_addw)
{
	wetuwn pci_addw & DWA7XX_CPU_TO_BUS_ADDW;
}

static int dwa7xx_pcie_wink_up(stwuct dw_pcie *pci)
{
	stwuct dwa7xx_pcie *dwa7xx = to_dwa7xx_pcie(pci);
	u32 weg = dwa7xx_pcie_weadw(dwa7xx, PCIECTWW_DWA7XX_CONF_PHY_CS);

	wetuwn !!(weg & WINK_UP);
}

static void dwa7xx_pcie_stop_wink(stwuct dw_pcie *pci)
{
	stwuct dwa7xx_pcie *dwa7xx = to_dwa7xx_pcie(pci);
	u32 weg;

	weg = dwa7xx_pcie_weadw(dwa7xx, PCIECTWW_DWA7XX_CONF_DEVICE_CMD);
	weg &= ~WTSSM_EN;
	dwa7xx_pcie_wwitew(dwa7xx, PCIECTWW_DWA7XX_CONF_DEVICE_CMD, weg);
}

static int dwa7xx_pcie_estabwish_wink(stwuct dw_pcie *pci)
{
	stwuct dwa7xx_pcie *dwa7xx = to_dwa7xx_pcie(pci);
	stwuct device *dev = pci->dev;
	u32 weg;

	if (dw_pcie_wink_up(pci)) {
		dev_eww(dev, "wink is awweady up\n");
		wetuwn 0;
	}

	weg = dwa7xx_pcie_weadw(dwa7xx, PCIECTWW_DWA7XX_CONF_DEVICE_CMD);
	weg |= WTSSM_EN;
	dwa7xx_pcie_wwitew(dwa7xx, PCIECTWW_DWA7XX_CONF_DEVICE_CMD, weg);

	wetuwn 0;
}

static void dwa7xx_pcie_enabwe_msi_intewwupts(stwuct dwa7xx_pcie *dwa7xx)
{
	dwa7xx_pcie_wwitew(dwa7xx, PCIECTWW_DWA7XX_CONF_IWQSTATUS_MSI,
			   WEG_EP_INTEWWUPTS | MSI);

	dwa7xx_pcie_wwitew(dwa7xx,
			   PCIECTWW_DWA7XX_CONF_IWQENABWE_SET_MSI,
			   MSI | WEG_EP_INTEWWUPTS);
}

static void dwa7xx_pcie_enabwe_wwappew_intewwupts(stwuct dwa7xx_pcie *dwa7xx)
{
	dwa7xx_pcie_wwitew(dwa7xx, PCIECTWW_DWA7XX_CONF_IWQSTATUS_MAIN,
			   INTEWWUPTS);
	dwa7xx_pcie_wwitew(dwa7xx, PCIECTWW_DWA7XX_CONF_IWQENABWE_SET_MAIN,
			   INTEWWUPTS);
}

static void dwa7xx_pcie_enabwe_intewwupts(stwuct dwa7xx_pcie *dwa7xx)
{
	dwa7xx_pcie_enabwe_wwappew_intewwupts(dwa7xx);
	dwa7xx_pcie_enabwe_msi_intewwupts(dwa7xx);
}

static int dwa7xx_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct dwa7xx_pcie *dwa7xx = to_dwa7xx_pcie(pci);

	dwa7xx_pcie_enabwe_intewwupts(dwa7xx);

	wetuwn 0;
}

static int dwa7xx_pcie_intx_map(stwuct iwq_domain *domain, unsigned int iwq,
				iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &dummy_iwq_chip, handwe_simpwe_iwq);
	iwq_set_chip_data(iwq, domain->host_data);

	wetuwn 0;
}

static const stwuct iwq_domain_ops intx_domain_ops = {
	.map = dwa7xx_pcie_intx_map,
	.xwate = pci_iwqd_intx_xwate,
};

static int dwa7xx_pcie_handwe_msi(stwuct dw_pcie_wp *pp, int index)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	unsigned wong vaw;
	int pos;

	vaw = dw_pcie_weadw_dbi(pci, PCIE_MSI_INTW0_STATUS +
				   (index * MSI_WEG_CTWW_BWOCK_SIZE));
	if (!vaw)
		wetuwn 0;

	pos = find_fiwst_bit(&vaw, MAX_MSI_IWQS_PEW_CTWW);
	whiwe (pos != MAX_MSI_IWQS_PEW_CTWW) {
		genewic_handwe_domain_iwq(pp->iwq_domain,
					  (index * MAX_MSI_IWQS_PEW_CTWW) + pos);
		pos++;
		pos = find_next_bit(&vaw, MAX_MSI_IWQS_PEW_CTWW, pos);
	}

	wetuwn 1;
}

static void dwa7xx_pcie_handwe_msi_iwq(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	int wet, i, count, num_ctwws;

	num_ctwws = pp->num_vectows / MAX_MSI_IWQS_PEW_CTWW;

	/**
	 * Need to make suwe aww MSI status bits wead 0 befowe exiting.
	 * Ewse, new MSI IWQs awe not wegistewed by the wwappew. Have an
	 * uppewbound fow the woop and exit the IWQ in case of IWQ fwood
	 * to avoid wocking up system in intewwupt context.
	 */
	count = 0;
	do {
		wet = 0;

		fow (i = 0; i < num_ctwws; i++)
			wet |= dwa7xx_pcie_handwe_msi(pp, i);
		count++;
	} whiwe (wet && count <= 1000);

	if (count > 1000)
		dev_wawn_watewimited(pci->dev,
				     "Too many MSI IWQs to handwe\n");
}

static void dwa7xx_pcie_msi_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct dwa7xx_pcie *dwa7xx;
	stwuct dw_pcie_wp *pp;
	stwuct dw_pcie *pci;
	unsigned wong weg;
	u32 bit;

	chained_iwq_entew(chip, desc);

	pp = iwq_desc_get_handwew_data(desc);
	pci = to_dw_pcie_fwom_pp(pp);
	dwa7xx = to_dwa7xx_pcie(pci);

	weg = dwa7xx_pcie_weadw(dwa7xx, PCIECTWW_DWA7XX_CONF_IWQSTATUS_MSI);
	dwa7xx_pcie_wwitew(dwa7xx, PCIECTWW_DWA7XX_CONF_IWQSTATUS_MSI, weg);

	switch (weg) {
	case MSI:
		dwa7xx_pcie_handwe_msi_iwq(pp);
		bweak;
	case INTA:
	case INTB:
	case INTC:
	case INTD:
		fow_each_set_bit(bit, &weg, PCI_NUM_INTX)
			genewic_handwe_domain_iwq(dwa7xx->iwq_domain, bit);
		bweak;
	}

	chained_iwq_exit(chip, desc);
}

static iwqwetuwn_t dwa7xx_pcie_iwq_handwew(int iwq, void *awg)
{
	stwuct dwa7xx_pcie *dwa7xx = awg;
	stwuct dw_pcie *pci = dwa7xx->pci;
	stwuct device *dev = pci->dev;
	stwuct dw_pcie_ep *ep = &pci->ep;
	u32 weg;

	weg = dwa7xx_pcie_weadw(dwa7xx, PCIECTWW_DWA7XX_CONF_IWQSTATUS_MAIN);

	if (weg & EWW_SYS)
		dev_dbg(dev, "System Ewwow\n");

	if (weg & EWW_FATAW)
		dev_dbg(dev, "Fataw Ewwow\n");

	if (weg & EWW_NONFATAW)
		dev_dbg(dev, "Non Fataw Ewwow\n");

	if (weg & EWW_COW)
		dev_dbg(dev, "Cowwectabwe Ewwow\n");

	if (weg & EWW_AXI)
		dev_dbg(dev, "AXI tag wookup fataw Ewwow\n");

	if (weg & EWW_ECWC)
		dev_dbg(dev, "ECWC Ewwow\n");

	if (weg & PME_TUWN_OFF)
		dev_dbg(dev,
			"Powew Management Event Tuwn-Off message weceived\n");

	if (weg & PME_TO_ACK)
		dev_dbg(dev,
			"Powew Management Tuwn-Off Ack message weceived\n");

	if (weg & PM_PME)
		dev_dbg(dev, "PM Powew Management Event message weceived\n");

	if (weg & WINK_WEQ_WST)
		dev_dbg(dev, "Wink Wequest Weset\n");

	if (weg & WINK_UP_EVT) {
		if (dwa7xx->mode == DW_PCIE_EP_TYPE)
			dw_pcie_ep_winkup(ep);
		dev_dbg(dev, "Wink-up state change\n");
	}

	if (weg & CFG_BME_EVT)
		dev_dbg(dev, "CFG 'Bus Mastew Enabwe' change\n");

	if (weg & CFG_MSE_EVT)
		dev_dbg(dev, "CFG 'Memowy Space Enabwe' change\n");

	dwa7xx_pcie_wwitew(dwa7xx, PCIECTWW_DWA7XX_CONF_IWQSTATUS_MAIN, weg);

	wetuwn IWQ_HANDWED;
}

static int dwa7xx_pcie_init_iwq_domain(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct device *dev = pci->dev;
	stwuct dwa7xx_pcie *dwa7xx = to_dwa7xx_pcie(pci);
	stwuct device_node *node = dev->of_node;
	stwuct device_node *pcie_intc_node =  of_get_next_chiwd(node, NUWW);

	if (!pcie_intc_node) {
		dev_eww(dev, "No PCIe Intc node found\n");
		wetuwn -ENODEV;
	}

	iwq_set_chained_handwew_and_data(pp->iwq, dwa7xx_pcie_msi_iwq_handwew,
					 pp);
	dwa7xx->iwq_domain = iwq_domain_add_wineaw(pcie_intc_node, PCI_NUM_INTX,
						   &intx_domain_ops, pp);
	of_node_put(pcie_intc_node);
	if (!dwa7xx->iwq_domain) {
		dev_eww(dev, "Faiwed to get a INTx IWQ domain\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static const stwuct dw_pcie_host_ops dwa7xx_pcie_host_ops = {
	.init = dwa7xx_pcie_host_init,
};

static void dwa7xx_pcie_ep_init(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct dwa7xx_pcie *dwa7xx = to_dwa7xx_pcie(pci);
	enum pci_bawno baw;

	fow (baw = 0; baw < PCI_STD_NUM_BAWS; baw++)
		dw_pcie_ep_weset_baw(pci, baw);

	dwa7xx_pcie_enabwe_wwappew_intewwupts(dwa7xx);
}

static void dwa7xx_pcie_waise_intx_iwq(stwuct dwa7xx_pcie *dwa7xx)
{
	dwa7xx_pcie_wwitew(dwa7xx, PCIECTWW_TI_CONF_INTX_ASSEWT, 0x1);
	mdeway(1);
	dwa7xx_pcie_wwitew(dwa7xx, PCIECTWW_TI_CONF_INTX_DEASSEWT, 0x1);
}

static void dwa7xx_pcie_waise_msi_iwq(stwuct dwa7xx_pcie *dwa7xx,
				      u8 intewwupt_num)
{
	u32 weg;

	weg = (intewwupt_num - 1) << MSI_VECTOW_SHIFT;
	weg |= MSI_WEQ_GWANT;
	dwa7xx_pcie_wwitew(dwa7xx, PCIECTWW_TI_CONF_MSI_XMT, weg);
}

static int dwa7xx_pcie_waise_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
				 unsigned int type, u16 intewwupt_num)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct dwa7xx_pcie *dwa7xx = to_dwa7xx_pcie(pci);

	switch (type) {
	case PCI_IWQ_INTX:
		dwa7xx_pcie_waise_intx_iwq(dwa7xx);
		bweak;
	case PCI_IWQ_MSI:
		dwa7xx_pcie_waise_msi_iwq(dwa7xx, intewwupt_num);
		bweak;
	defauwt:
		dev_eww(pci->dev, "UNKNOWN IWQ type\n");
	}

	wetuwn 0;
}

static const stwuct pci_epc_featuwes dwa7xx_pcie_epc_featuwes = {
	.winkup_notifiew = twue,
	.msi_capabwe = twue,
	.msix_capabwe = fawse,
};

static const stwuct pci_epc_featuwes*
dwa7xx_pcie_get_featuwes(stwuct dw_pcie_ep *ep)
{
	wetuwn &dwa7xx_pcie_epc_featuwes;
}

static const stwuct dw_pcie_ep_ops pcie_ep_ops = {
	.init = dwa7xx_pcie_ep_init,
	.waise_iwq = dwa7xx_pcie_waise_iwq,
	.get_featuwes = dwa7xx_pcie_get_featuwes,
};

static int dwa7xx_add_pcie_ep(stwuct dwa7xx_pcie *dwa7xx,
			      stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct dw_pcie_ep *ep;
	stwuct device *dev = &pdev->dev;
	stwuct dw_pcie *pci = dwa7xx->pci;

	ep = &pci->ep;
	ep->ops = &pcie_ep_ops;

	pci->dbi_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ep_dbics");
	if (IS_EWW(pci->dbi_base))
		wetuwn PTW_EWW(pci->dbi_base);

	pci->dbi_base2 =
		devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ep_dbics2");
	if (IS_EWW(pci->dbi_base2))
		wetuwn PTW_EWW(pci->dbi_base2);

	wet = dw_pcie_ep_init(ep);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize endpoint\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int dwa7xx_add_pcie_powt(stwuct dwa7xx_pcie *dwa7xx,
				stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct dw_pcie *pci = dwa7xx->pci;
	stwuct dw_pcie_wp *pp = &pci->pp;
	stwuct device *dev = pci->dev;

	pp->iwq = pwatfowm_get_iwq(pdev, 1);
	if (pp->iwq < 0)
		wetuwn pp->iwq;

	/* MSI IWQ is muxed */
	pp->msi_iwq[0] = -ENODEV;

	wet = dwa7xx_pcie_init_iwq_domain(pp);
	if (wet < 0)
		wetuwn wet;

	pci->dbi_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wc_dbics");
	if (IS_EWW(pci->dbi_base))
		wetuwn PTW_EWW(pci->dbi_base);

	pp->ops = &dwa7xx_pcie_host_ops;

	wet = dw_pcie_host_init(pp);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize host\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dw_pcie_ops dw_pcie_ops = {
	.cpu_addw_fixup = dwa7xx_pcie_cpu_addw_fixup,
	.stawt_wink = dwa7xx_pcie_estabwish_wink,
	.stop_wink = dwa7xx_pcie_stop_wink,
	.wink_up = dwa7xx_pcie_wink_up,
};

static void dwa7xx_pcie_disabwe_phy(stwuct dwa7xx_pcie *dwa7xx)
{
	int phy_count = dwa7xx->phy_count;

	whiwe (phy_count--) {
		phy_powew_off(dwa7xx->phy[phy_count]);
		phy_exit(dwa7xx->phy[phy_count]);
	}
}

static int dwa7xx_pcie_enabwe_phy(stwuct dwa7xx_pcie *dwa7xx)
{
	int phy_count = dwa7xx->phy_count;
	int wet;
	int i;

	fow (i = 0; i < phy_count; i++) {
		wet = phy_set_mode(dwa7xx->phy[i], PHY_MODE_PCIE);
		if (wet < 0)
			goto eww_phy;

		wet = phy_init(dwa7xx->phy[i]);
		if (wet < 0)
			goto eww_phy;

		wet = phy_powew_on(dwa7xx->phy[i]);
		if (wet < 0) {
			phy_exit(dwa7xx->phy[i]);
			goto eww_phy;
		}
	}

	wetuwn 0;

eww_phy:
	whiwe (--i >= 0) {
		phy_powew_off(dwa7xx->phy[i]);
		phy_exit(dwa7xx->phy[i]);
	}

	wetuwn wet;
}

static const stwuct dwa7xx_pcie_of_data dwa7xx_pcie_wc_of_data = {
	.mode = DW_PCIE_WC_TYPE,
};

static const stwuct dwa7xx_pcie_of_data dwa7xx_pcie_ep_of_data = {
	.mode = DW_PCIE_EP_TYPE,
};

static const stwuct dwa7xx_pcie_of_data dwa746_pcie_wc_of_data = {
	.b1co_mode_sew_mask = BIT(2),
	.mode = DW_PCIE_WC_TYPE,
};

static const stwuct dwa7xx_pcie_of_data dwa726_pcie_wc_of_data = {
	.b1co_mode_sew_mask = GENMASK(3, 2),
	.mode = DW_PCIE_WC_TYPE,
};

static const stwuct dwa7xx_pcie_of_data dwa746_pcie_ep_of_data = {
	.b1co_mode_sew_mask = BIT(2),
	.mode = DW_PCIE_EP_TYPE,
};

static const stwuct dwa7xx_pcie_of_data dwa726_pcie_ep_of_data = {
	.b1co_mode_sew_mask = GENMASK(3, 2),
	.mode = DW_PCIE_EP_TYPE,
};

static const stwuct of_device_id of_dwa7xx_pcie_match[] = {
	{
		.compatibwe = "ti,dwa7-pcie",
		.data = &dwa7xx_pcie_wc_of_data,
	},
	{
		.compatibwe = "ti,dwa7-pcie-ep",
		.data = &dwa7xx_pcie_ep_of_data,
	},
	{
		.compatibwe = "ti,dwa746-pcie-wc",
		.data = &dwa746_pcie_wc_of_data,
	},
	{
		.compatibwe = "ti,dwa726-pcie-wc",
		.data = &dwa726_pcie_wc_of_data,
	},
	{
		.compatibwe = "ti,dwa746-pcie-ep",
		.data = &dwa746_pcie_ep_of_data,
	},
	{
		.compatibwe = "ti,dwa726-pcie-ep",
		.data = &dwa726_pcie_ep_of_data,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, of_dwa7xx_pcie_match);

/*
 * dwa7xx_pcie_unawigned_memaccess: wowkawound fow AM572x/AM571x Ewwata i870
 * @dwa7xx: the dwa7xx device whewe the wowkawound shouwd be appwied
 *
 * Access to the PCIe swave powt that awe not 32-bit awigned wiww wesuwt
 * in incowwect mapping to TWP Addwess and Byte enabwe fiewds. Thewefowe,
 * byte and hawf-wowd accesses awe not possibwe to byte offset 0x1, 0x2, ow
 * 0x3.
 *
 * To avoid this issue set PCIE_SS1_AXI2OCP_WEGACY_MODE_ENABWE to 1.
 */
static int dwa7xx_pcie_unawigned_memaccess(stwuct device *dev)
{
	int wet;
	stwuct device_node *np = dev->of_node;
	stwuct of_phandwe_awgs awgs;
	stwuct wegmap *wegmap;

	wegmap = syscon_wegmap_wookup_by_phandwe(np,
						 "ti,syscon-unawigned-access");
	if (IS_EWW(wegmap)) {
		dev_dbg(dev, "can't get ti,syscon-unawigned-access\n");
		wetuwn -EINVAW;
	}

	wet = of_pawse_phandwe_with_fixed_awgs(np, "ti,syscon-unawigned-access",
					       2, 0, &awgs);
	if (wet) {
		dev_eww(dev, "faiwed to pawse ti,syscon-unawigned-access\n");
		wetuwn wet;
	}

	wet = wegmap_update_bits(wegmap, awgs.awgs[0], awgs.awgs[1],
				 awgs.awgs[1]);
	if (wet)
		dev_eww(dev, "faiwed to enabwe unawigned access\n");

	of_node_put(awgs.np);

	wetuwn wet;
}

static int dwa7xx_pcie_configuwe_two_wane(stwuct device *dev,
					  u32 b1co_mode_sew_mask)
{
	stwuct device_node *np = dev->of_node;
	stwuct wegmap *pcie_syscon;
	unsigned int pcie_weg;
	u32 mask;
	u32 vaw;

	pcie_syscon = syscon_wegmap_wookup_by_phandwe(np, "ti,syscon-wane-sew");
	if (IS_EWW(pcie_syscon)) {
		dev_eww(dev, "unabwe to get ti,syscon-wane-sew\n");
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_u32_index(np, "ti,syscon-wane-sew", 1,
				       &pcie_weg)) {
		dev_eww(dev, "couwdn't get wane sewection weg offset\n");
		wetuwn -EINVAW;
	}

	mask = b1co_mode_sew_mask | PCIE_B0_B1_TSYNCEN;
	vaw = PCIE_B1C0_MODE_SEW | PCIE_B0_B1_TSYNCEN;
	wegmap_update_bits(pcie_syscon, pcie_weg, mask, vaw);

	wetuwn 0;
}

static int dwa7xx_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	u32 weg;
	int wet;
	int iwq;
	int i;
	int phy_count;
	stwuct phy **phy;
	stwuct device_wink **wink;
	void __iomem *base;
	stwuct dw_pcie *pci;
	stwuct dwa7xx_pcie *dwa7xx;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	chaw name[10];
	stwuct gpio_desc *weset;
	const stwuct dwa7xx_pcie_of_data *data;
	enum dw_pcie_device_mode mode;
	u32 b1co_mode_sew_mask;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	mode = (enum dw_pcie_device_mode)data->mode;
	b1co_mode_sew_mask = data->b1co_mode_sew_mask;

	dwa7xx = devm_kzawwoc(dev, sizeof(*dwa7xx), GFP_KEWNEW);
	if (!dwa7xx)
		wetuwn -ENOMEM;

	pci = devm_kzawwoc(dev, sizeof(*pci), GFP_KEWNEW);
	if (!pci)
		wetuwn -ENOMEM;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ti_conf");
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	phy_count = of_pwopewty_count_stwings(np, "phy-names");
	if (phy_count < 0) {
		dev_eww(dev, "unabwe to find the stwings\n");
		wetuwn phy_count;
	}

	phy = devm_kcawwoc(dev, phy_count, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	wink = devm_kcawwoc(dev, phy_count, sizeof(*wink), GFP_KEWNEW);
	if (!wink)
		wetuwn -ENOMEM;

	dwa7xx->cwk = devm_cwk_get_optionaw(dev, NUWW);
	if (IS_EWW(dwa7xx->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dwa7xx->cwk),
				     "cwock wequest faiwed");

	wet = cwk_pwepawe_enabwe(dwa7xx->cwk);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < phy_count; i++) {
		snpwintf(name, sizeof(name), "pcie-phy%d", i);
		phy[i] = devm_phy_get(dev, name);
		if (IS_EWW(phy[i]))
			wetuwn PTW_EWW(phy[i]);

		wink[i] = device_wink_add(dev, &phy[i]->dev, DW_FWAG_STATEWESS);
		if (!wink[i]) {
			wet = -EINVAW;
			goto eww_wink;
		}
	}

	dwa7xx->base = base;
	dwa7xx->phy = phy;
	dwa7xx->pci = pci;
	dwa7xx->phy_count = phy_count;

	if (phy_count == 2) {
		wet = dwa7xx_pcie_configuwe_two_wane(dev, b1co_mode_sew_mask);
		if (wet < 0)
			dwa7xx->phy_count = 1; /* Fawwback to x1 wane mode */
	}

	wet = dwa7xx_pcie_enabwe_phy(dwa7xx);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe phy\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, dwa7xx);

	pm_wuntime_enabwe(dev);
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		dev_eww(dev, "pm_wuntime_get_sync faiwed\n");
		goto eww_get_sync;
	}

	weset = devm_gpiod_get_optionaw(dev, NUWW, GPIOD_OUT_HIGH);
	if (IS_EWW(weset)) {
		wet = PTW_EWW(weset);
		dev_eww(&pdev->dev, "gpio wequest faiwed, wet %d\n", wet);
		goto eww_gpio;
	}

	weg = dwa7xx_pcie_weadw(dwa7xx, PCIECTWW_DWA7XX_CONF_DEVICE_CMD);
	weg &= ~WTSSM_EN;
	dwa7xx_pcie_wwitew(dwa7xx, PCIECTWW_DWA7XX_CONF_DEVICE_CMD, weg);

	switch (mode) {
	case DW_PCIE_WC_TYPE:
		if (!IS_ENABWED(CONFIG_PCI_DWA7XX_HOST)) {
			wet = -ENODEV;
			goto eww_gpio;
		}

		dwa7xx_pcie_wwitew(dwa7xx, PCIECTWW_TI_CONF_DEVICE_TYPE,
				   DEVICE_TYPE_WC);

		wet = dwa7xx_pcie_unawigned_memaccess(dev);
		if (wet)
			dev_eww(dev, "WA fow Ewwata i870 not appwied\n");

		wet = dwa7xx_add_pcie_powt(dwa7xx, pdev);
		if (wet < 0)
			goto eww_gpio;
		bweak;
	case DW_PCIE_EP_TYPE:
		if (!IS_ENABWED(CONFIG_PCI_DWA7XX_EP)) {
			wet = -ENODEV;
			goto eww_gpio;
		}

		dwa7xx_pcie_wwitew(dwa7xx, PCIECTWW_TI_CONF_DEVICE_TYPE,
				   DEVICE_TYPE_EP);

		wet = dwa7xx_pcie_unawigned_memaccess(dev);
		if (wet)
			goto eww_gpio;

		wet = dwa7xx_add_pcie_ep(dwa7xx, pdev);
		if (wet < 0)
			goto eww_gpio;
		bweak;
	defauwt:
		dev_eww(dev, "INVAWID device type %d\n", mode);
	}
	dwa7xx->mode = mode;

	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW, dwa7xx_pcie_iwq_handwew,
			       IWQF_SHAWED, "dwa7xx-pcie-main", dwa7xx);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq\n");
		goto eww_gpio;
	}

	wetuwn 0;

eww_gpio:
eww_get_sync:
	pm_wuntime_put(dev);
	pm_wuntime_disabwe(dev);
	dwa7xx_pcie_disabwe_phy(dwa7xx);

eww_wink:
	whiwe (--i >= 0)
		device_wink_dew(wink[i]);

	wetuwn wet;
}

static int dwa7xx_pcie_suspend(stwuct device *dev)
{
	stwuct dwa7xx_pcie *dwa7xx = dev_get_dwvdata(dev);
	stwuct dw_pcie *pci = dwa7xx->pci;
	u32 vaw;

	if (dwa7xx->mode != DW_PCIE_WC_TYPE)
		wetuwn 0;

	/* cweaw MSE */
	vaw = dw_pcie_weadw_dbi(pci, PCI_COMMAND);
	vaw &= ~PCI_COMMAND_MEMOWY;
	dw_pcie_wwitew_dbi(pci, PCI_COMMAND, vaw);

	wetuwn 0;
}

static int dwa7xx_pcie_wesume(stwuct device *dev)
{
	stwuct dwa7xx_pcie *dwa7xx = dev_get_dwvdata(dev);
	stwuct dw_pcie *pci = dwa7xx->pci;
	u32 vaw;

	if (dwa7xx->mode != DW_PCIE_WC_TYPE)
		wetuwn 0;

	/* set MSE */
	vaw = dw_pcie_weadw_dbi(pci, PCI_COMMAND);
	vaw |= PCI_COMMAND_MEMOWY;
	dw_pcie_wwitew_dbi(pci, PCI_COMMAND, vaw);

	wetuwn 0;
}

static int dwa7xx_pcie_suspend_noiwq(stwuct device *dev)
{
	stwuct dwa7xx_pcie *dwa7xx = dev_get_dwvdata(dev);

	dwa7xx_pcie_disabwe_phy(dwa7xx);

	wetuwn 0;
}

static int dwa7xx_pcie_wesume_noiwq(stwuct device *dev)
{
	stwuct dwa7xx_pcie *dwa7xx = dev_get_dwvdata(dev);
	int wet;

	wet = dwa7xx_pcie_enabwe_phy(dwa7xx);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe phy\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void dwa7xx_pcie_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dwa7xx_pcie *dwa7xx = dev_get_dwvdata(dev);
	int wet;

	dwa7xx_pcie_stop_wink(dwa7xx->pci);

	wet = pm_wuntime_put_sync(dev);
	if (wet < 0)
		dev_dbg(dev, "pm_wuntime_put_sync faiwed\n");

	pm_wuntime_disabwe(dev);
	dwa7xx_pcie_disabwe_phy(dwa7xx);

	cwk_disabwe_unpwepawe(dwa7xx->cwk);
}

static const stwuct dev_pm_ops dwa7xx_pcie_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(dwa7xx_pcie_suspend, dwa7xx_pcie_wesume)
	NOIWQ_SYSTEM_SWEEP_PM_OPS(dwa7xx_pcie_suspend_noiwq,
				  dwa7xx_pcie_wesume_noiwq)
};

static stwuct pwatfowm_dwivew dwa7xx_pcie_dwivew = {
	.pwobe = dwa7xx_pcie_pwobe,
	.dwivew = {
		.name	= "dwa7-pcie",
		.of_match_tabwe = of_dwa7xx_pcie_match,
		.suppwess_bind_attws = twue,
		.pm	= &dwa7xx_pcie_pm_ops,
	},
	.shutdown = dwa7xx_pcie_shutdown,
};
moduwe_pwatfowm_dwivew(dwa7xx_pcie_dwivew);

MODUWE_AUTHOW("Kishon Vijay Abwaham I <kishon@ti.com>");
MODUWE_DESCWIPTION("PCIe contwowwew dwivew fow TI DWA7xx SoCs");
MODUWE_WICENSE("GPW v2");
