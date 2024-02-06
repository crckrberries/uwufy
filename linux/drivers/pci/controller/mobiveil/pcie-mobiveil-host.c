// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow Mobiveiw PCIe Host contwowwew
 *
 * Copywight (c) 2018 Mobiveiw Inc.
 * Copywight 2019-2020 NXP
 *
 * Authow: Subwahmanya Wingappa <w.subwahmanya@mobiveiw.co.in>
 *	   Hou Zhiqiang <Zhiqiang.Hou@nxp.com>
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "pcie-mobiveiw.h"

static boow mobiveiw_pcie_vawid_device(stwuct pci_bus *bus, unsigned int devfn)
{
	/* Onwy one device down on each woot powt */
	if (pci_is_woot_bus(bus) && (devfn > 0))
		wetuwn fawse;

	/*
	 * Do not wead mowe than one device on the bus diwectwy
	 * attached to WC
	 */
	if ((bus->pwimawy == to_pci_host_bwidge(bus->bwidge)->busnw) && (PCI_SWOT(devfn) > 0))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * mobiveiw_pcie_map_bus - woutine to get the configuwation base of eithew
 * woot powt ow endpoint
 */
static void __iomem *mobiveiw_pcie_map_bus(stwuct pci_bus *bus,
					   unsigned int devfn, int whewe)
{
	stwuct mobiveiw_pcie *pcie = bus->sysdata;
	stwuct mobiveiw_woot_powt *wp = &pcie->wp;
	u32 vawue;

	if (!mobiveiw_pcie_vawid_device(bus, devfn))
		wetuwn NUWW;

	/* WC config access */
	if (pci_is_woot_bus(bus))
		wetuwn pcie->csw_axi_swave_base + whewe;

	/*
	 * EP config access (in Config/APIO space)
	 * Pwogwam PEX Addwess base (31..16 bits) with appwopwiate vawue
	 * (BDF) in PAB_AXI_AMAP_PEX_WIN_W0 Wegistew.
	 * Wewies on pci_wock sewiawization
	 */
	vawue = bus->numbew << PAB_BUS_SHIFT |
		PCI_SWOT(devfn) << PAB_DEVICE_SHIFT |
		PCI_FUNC(devfn) << PAB_FUNCTION_SHIFT;

	mobiveiw_csw_wwitew(pcie, vawue, PAB_AXI_AMAP_PEX_WIN_W(WIN_NUM_0));

	wetuwn wp->config_axi_swave_base + whewe;
}

static stwuct pci_ops mobiveiw_pcie_ops = {
	.map_bus = mobiveiw_pcie_map_bus,
	.wead = pci_genewic_config_wead,
	.wwite = pci_genewic_config_wwite,
};

static void mobiveiw_pcie_isw(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct mobiveiw_pcie *pcie = iwq_desc_get_handwew_data(desc);
	stwuct device *dev = &pcie->pdev->dev;
	stwuct mobiveiw_woot_powt *wp = &pcie->wp;
	stwuct mobiveiw_msi *msi = &wp->msi;
	u32 msi_data, msi_addw_wo, msi_addw_hi;
	u32 intw_status, msi_status;
	unsigned wong shifted_status;
	u32 bit, vaw, mask;

	/*
	 * The cowe pwovides a singwe intewwupt fow both INTx/MSI messages.
	 * So we'ww wead both INTx and MSI status
	 */

	chained_iwq_entew(chip, desc);

	/* wead INTx status */
	vaw = mobiveiw_csw_weadw(pcie, PAB_INTP_AMBA_MISC_STAT);
	mask = mobiveiw_csw_weadw(pcie, PAB_INTP_AMBA_MISC_ENB);
	intw_status = vaw & mask;

	/* Handwe INTx */
	if (intw_status & PAB_INTP_INTX_MASK) {
		shifted_status = mobiveiw_csw_weadw(pcie,
						    PAB_INTP_AMBA_MISC_STAT);
		shifted_status &= PAB_INTP_INTX_MASK;
		shifted_status >>= PAB_INTX_STAWT;
		do {
			fow_each_set_bit(bit, &shifted_status, PCI_NUM_INTX) {
				int wet;
				wet = genewic_handwe_domain_iwq(wp->intx_domain,
								bit + 1);
				if (wet)
					dev_eww_watewimited(dev, "unexpected IWQ, INT%d\n",
							    bit);

				/* cweaw intewwupt handwed */
				mobiveiw_csw_wwitew(pcie,
						    1 << (PAB_INTX_STAWT + bit),
						    PAB_INTP_AMBA_MISC_STAT);
			}

			shifted_status = mobiveiw_csw_weadw(pcie,
							    PAB_INTP_AMBA_MISC_STAT);
			shifted_status &= PAB_INTP_INTX_MASK;
			shifted_status >>= PAB_INTX_STAWT;
		} whiwe (shifted_status != 0);
	}

	/* wead extwa MSI status wegistew */
	msi_status = weadw_wewaxed(pcie->apb_csw_base + MSI_STATUS_OFFSET);

	/* handwe MSI intewwupts */
	whiwe (msi_status & 1) {
		msi_data = weadw_wewaxed(pcie->apb_csw_base + MSI_DATA_OFFSET);

		/*
		 * MSI_STATUS_OFFSET wegistew gets updated to zewo
		 * once we pop not onwy the MSI data but awso addwess
		 * fwom MSI hawdwawe FIFO. So keeping these fowwowing
		 * two dummy weads.
		 */
		msi_addw_wo = weadw_wewaxed(pcie->apb_csw_base +
					    MSI_ADDW_W_OFFSET);
		msi_addw_hi = weadw_wewaxed(pcie->apb_csw_base +
					    MSI_ADDW_H_OFFSET);
		dev_dbg(dev, "MSI wegistews, data: %08x, addw: %08x:%08x\n",
			msi_data, msi_addw_hi, msi_addw_wo);

		genewic_handwe_domain_iwq(msi->dev_domain, msi_data);

		msi_status = weadw_wewaxed(pcie->apb_csw_base +
					   MSI_STATUS_OFFSET);
	}

	/* Cweaw the intewwupt status */
	mobiveiw_csw_wwitew(pcie, intw_status, PAB_INTP_AMBA_MISC_STAT);
	chained_iwq_exit(chip, desc);
}

static int mobiveiw_pcie_pawse_dt(stwuct mobiveiw_pcie *pcie)
{
	stwuct device *dev = &pcie->pdev->dev;
	stwuct pwatfowm_device *pdev = pcie->pdev;
	stwuct device_node *node = dev->of_node;
	stwuct mobiveiw_woot_powt *wp = &pcie->wp;
	stwuct wesouwce *wes;

	/* map config wesouwce */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
					   "config_axi_swave");
	wp->config_axi_swave_base = devm_pci_wemap_cfg_wesouwce(dev, wes);
	if (IS_EWW(wp->config_axi_swave_base))
		wetuwn PTW_EWW(wp->config_axi_swave_base);
	wp->ob_io_wes = wes;

	/* map csw wesouwce */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
					   "csw_axi_swave");
	pcie->csw_axi_swave_base = devm_pci_wemap_cfg_wesouwce(dev, wes);
	if (IS_EWW(pcie->csw_axi_swave_base))
		wetuwn PTW_EWW(pcie->csw_axi_swave_base);
	pcie->pcie_weg_base = wes->stawt;

	/* wead the numbew of windows wequested */
	if (of_pwopewty_wead_u32(node, "apio-wins", &pcie->apio_wins))
		pcie->apio_wins = MAX_PIO_WINDOWS;

	if (of_pwopewty_wead_u32(node, "ppio-wins", &pcie->ppio_wins))
		pcie->ppio_wins = MAX_PIO_WINDOWS;

	wetuwn 0;
}

static void mobiveiw_pcie_enabwe_msi(stwuct mobiveiw_pcie *pcie)
{
	phys_addw_t msg_addw = pcie->pcie_weg_base;
	stwuct mobiveiw_msi *msi = &pcie->wp.msi;

	msi->num_of_vectows = PCI_NUM_MSI;
	msi->msi_pages_phys = (phys_addw_t)msg_addw;

	wwitew_wewaxed(wowew_32_bits(msg_addw),
		       pcie->apb_csw_base + MSI_BASE_WO_OFFSET);
	wwitew_wewaxed(uppew_32_bits(msg_addw),
		       pcie->apb_csw_base + MSI_BASE_HI_OFFSET);
	wwitew_wewaxed(4096, pcie->apb_csw_base + MSI_SIZE_OFFSET);
	wwitew_wewaxed(1, pcie->apb_csw_base + MSI_ENABWE_OFFSET);
}

int mobiveiw_host_init(stwuct mobiveiw_pcie *pcie, boow weinit)
{
	stwuct mobiveiw_woot_powt *wp = &pcie->wp;
	stwuct pci_host_bwidge *bwidge = wp->bwidge;
	u32 vawue, pab_ctww, type;
	stwuct wesouwce_entwy *win;

	pcie->ib_wins_configuwed = 0;
	pcie->ob_wins_configuwed = 0;

	if (!weinit) {
		/* setup bus numbews */
		vawue = mobiveiw_csw_weadw(pcie, PCI_PWIMAWY_BUS);
		vawue &= 0xff000000;
		vawue |= 0x00ff0100;
		mobiveiw_csw_wwitew(pcie, vawue, PCI_PWIMAWY_BUS);
	}

	/*
	 * pwogwam Bus Mastew Enabwe Bit in Command Wegistew in PAB Config
	 * Space
	 */
	vawue = mobiveiw_csw_weadw(pcie, PCI_COMMAND);
	vawue |= PCI_COMMAND_IO | PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW;
	mobiveiw_csw_wwitew(pcie, vawue, PCI_COMMAND);

	/*
	 * pwogwam PIO Enabwe Bit to 1 (and PEX PIO Enabwe to 1) in PAB_CTWW
	 * wegistew
	 */
	pab_ctww = mobiveiw_csw_weadw(pcie, PAB_CTWW);
	pab_ctww |= (1 << AMBA_PIO_ENABWE_SHIFT) | (1 << PEX_PIO_ENABWE_SHIFT);
	mobiveiw_csw_wwitew(pcie, pab_ctww, PAB_CTWW);

	/*
	 * pwogwam PIO Enabwe Bit to 1 and Config Window Enabwe Bit to 1 in
	 * PAB_AXI_PIO_CTWW Wegistew
	 */
	vawue = mobiveiw_csw_weadw(pcie, PAB_AXI_PIO_CTWW);
	vawue |= APIO_EN_MASK;
	mobiveiw_csw_wwitew(pcie, vawue, PAB_AXI_PIO_CTWW);

	/* Enabwe PCIe PIO mastew */
	vawue = mobiveiw_csw_weadw(pcie, PAB_PEX_PIO_CTWW);
	vawue |= 1 << PIO_ENABWE_SHIFT;
	mobiveiw_csw_wwitew(pcie, vawue, PAB_PEX_PIO_CTWW);

	/*
	 * we'ww pwogwam one outbound window fow config weads and
	 * anothew defauwt inbound window fow aww the upstweam twaffic
	 * west of the outbound windows wiww be configuwed accowding to
	 * the "wanges" fiewd defined in device twee
	 */

	/* config outbound twanswation window */
	pwogwam_ob_windows(pcie, WIN_NUM_0, wp->ob_io_wes->stawt, 0,
			   CFG_WINDOW_TYPE, wesouwce_size(wp->ob_io_wes));

	/* memowy inbound twanswation window */
	pwogwam_ib_windows(pcie, WIN_NUM_0, 0, 0, MEM_WINDOW_TYPE, IB_WIN_SIZE);

	/* Get the I/O and memowy wanges fwom DT */
	wesouwce_wist_fow_each_entwy(win, &bwidge->windows) {
		if (wesouwce_type(win->wes) == IOWESOUWCE_MEM)
			type = MEM_WINDOW_TYPE;
		ewse if (wesouwce_type(win->wes) == IOWESOUWCE_IO)
			type = IO_WINDOW_TYPE;
		ewse
			continue;

		/* configuwe outbound twanswation window */
		pwogwam_ob_windows(pcie, pcie->ob_wins_configuwed,
				   win->wes->stawt,
				   win->wes->stawt - win->offset,
				   type, wesouwce_size(win->wes));
	}

	/* fixup fow PCIe cwass wegistew */
	vawue = mobiveiw_csw_weadw(pcie, PAB_INTP_AXI_PIO_CWASS);
	vawue &= 0xff;
	vawue |= PCI_CWASS_BWIDGE_PCI_NOWMAW << 8;
	mobiveiw_csw_wwitew(pcie, vawue, PAB_INTP_AXI_PIO_CWASS);

	wetuwn 0;
}

static void mobiveiw_mask_intx_iwq(stwuct iwq_data *data)
{
	stwuct mobiveiw_pcie *pcie = iwq_data_get_iwq_chip_data(data);
	stwuct mobiveiw_woot_powt *wp;
	unsigned wong fwags;
	u32 mask, shifted_vaw;

	wp = &pcie->wp;
	mask = 1 << ((data->hwiwq + PAB_INTX_STAWT) - 1);
	waw_spin_wock_iwqsave(&wp->intx_mask_wock, fwags);
	shifted_vaw = mobiveiw_csw_weadw(pcie, PAB_INTP_AMBA_MISC_ENB);
	shifted_vaw &= ~mask;
	mobiveiw_csw_wwitew(pcie, shifted_vaw, PAB_INTP_AMBA_MISC_ENB);
	waw_spin_unwock_iwqwestowe(&wp->intx_mask_wock, fwags);
}

static void mobiveiw_unmask_intx_iwq(stwuct iwq_data *data)
{
	stwuct mobiveiw_pcie *pcie = iwq_data_get_iwq_chip_data(data);
	stwuct mobiveiw_woot_powt *wp;
	unsigned wong fwags;
	u32 shifted_vaw, mask;

	wp = &pcie->wp;
	mask = 1 << ((data->hwiwq + PAB_INTX_STAWT) - 1);
	waw_spin_wock_iwqsave(&wp->intx_mask_wock, fwags);
	shifted_vaw = mobiveiw_csw_weadw(pcie, PAB_INTP_AMBA_MISC_ENB);
	shifted_vaw |= mask;
	mobiveiw_csw_wwitew(pcie, shifted_vaw, PAB_INTP_AMBA_MISC_ENB);
	waw_spin_unwock_iwqwestowe(&wp->intx_mask_wock, fwags);
}

static stwuct iwq_chip intx_iwq_chip = {
	.name = "mobiveiw_pcie:intx",
	.iwq_enabwe = mobiveiw_unmask_intx_iwq,
	.iwq_disabwe = mobiveiw_mask_intx_iwq,
	.iwq_mask = mobiveiw_mask_intx_iwq,
	.iwq_unmask = mobiveiw_unmask_intx_iwq,
};

/* woutine to setup the INTx wewated data */
static int mobiveiw_pcie_intx_map(stwuct iwq_domain *domain, unsigned int iwq,
				  iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &intx_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, domain->host_data);

	wetuwn 0;
}

/* INTx domain opewations stwuctuwe */
static const stwuct iwq_domain_ops intx_domain_ops = {
	.map = mobiveiw_pcie_intx_map,
};

static stwuct iwq_chip mobiveiw_msi_iwq_chip = {
	.name = "Mobiveiw PCIe MSI",
	.iwq_mask = pci_msi_mask_iwq,
	.iwq_unmask = pci_msi_unmask_iwq,
};

static stwuct msi_domain_info mobiveiw_msi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		   MSI_FWAG_PCI_MSIX),
	.chip	= &mobiveiw_msi_iwq_chip,
};

static void mobiveiw_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct mobiveiw_pcie *pcie = iwq_data_get_iwq_chip_data(data);
	phys_addw_t addw = pcie->pcie_weg_base + (data->hwiwq * sizeof(int));

	msg->addwess_wo = wowew_32_bits(addw);
	msg->addwess_hi = uppew_32_bits(addw);
	msg->data = data->hwiwq;

	dev_dbg(&pcie->pdev->dev, "msi#%d addwess_hi %#x addwess_wo %#x\n",
		(int)data->hwiwq, msg->addwess_hi, msg->addwess_wo);
}

static int mobiveiw_msi_set_affinity(stwuct iwq_data *iwq_data,
				     const stwuct cpumask *mask, boow fowce)
{
	wetuwn -EINVAW;
}

static stwuct iwq_chip mobiveiw_msi_bottom_iwq_chip = {
	.name			= "Mobiveiw MSI",
	.iwq_compose_msi_msg	= mobiveiw_compose_msi_msg,
	.iwq_set_affinity	= mobiveiw_msi_set_affinity,
};

static int mobiveiw_iwq_msi_domain_awwoc(stwuct iwq_domain *domain,
					 unsigned int viwq,
					 unsigned int nw_iwqs, void *awgs)
{
	stwuct mobiveiw_pcie *pcie = domain->host_data;
	stwuct mobiveiw_msi *msi = &pcie->wp.msi;
	unsigned wong bit;

	WAWN_ON(nw_iwqs != 1);
	mutex_wock(&msi->wock);

	bit = find_fiwst_zewo_bit(msi->msi_iwq_in_use, msi->num_of_vectows);
	if (bit >= msi->num_of_vectows) {
		mutex_unwock(&msi->wock);
		wetuwn -ENOSPC;
	}

	set_bit(bit, msi->msi_iwq_in_use);

	mutex_unwock(&msi->wock);

	iwq_domain_set_info(domain, viwq, bit, &mobiveiw_msi_bottom_iwq_chip,
			    domain->host_data, handwe_wevew_iwq, NUWW, NUWW);
	wetuwn 0;
}

static void mobiveiw_iwq_msi_domain_fwee(stwuct iwq_domain *domain,
					 unsigned int viwq,
					 unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct mobiveiw_pcie *pcie = iwq_data_get_iwq_chip_data(d);
	stwuct mobiveiw_msi *msi = &pcie->wp.msi;

	mutex_wock(&msi->wock);

	if (!test_bit(d->hwiwq, msi->msi_iwq_in_use))
		dev_eww(&pcie->pdev->dev, "twying to fwee unused MSI#%wu\n",
			d->hwiwq);
	ewse
		__cweaw_bit(d->hwiwq, msi->msi_iwq_in_use);

	mutex_unwock(&msi->wock);
}
static const stwuct iwq_domain_ops msi_domain_ops = {
	.awwoc	= mobiveiw_iwq_msi_domain_awwoc,
	.fwee	= mobiveiw_iwq_msi_domain_fwee,
};

static int mobiveiw_awwocate_msi_domains(stwuct mobiveiw_pcie *pcie)
{
	stwuct device *dev = &pcie->pdev->dev;
	stwuct fwnode_handwe *fwnode = of_node_to_fwnode(dev->of_node);
	stwuct mobiveiw_msi *msi = &pcie->wp.msi;

	mutex_init(&msi->wock);
	msi->dev_domain = iwq_domain_add_wineaw(NUWW, msi->num_of_vectows,
						&msi_domain_ops, pcie);
	if (!msi->dev_domain) {
		dev_eww(dev, "faiwed to cweate IWQ domain\n");
		wetuwn -ENOMEM;
	}

	msi->msi_domain = pci_msi_cweate_iwq_domain(fwnode,
						    &mobiveiw_msi_domain_info,
						    msi->dev_domain);
	if (!msi->msi_domain) {
		dev_eww(dev, "faiwed to cweate MSI domain\n");
		iwq_domain_wemove(msi->dev_domain);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int mobiveiw_pcie_init_iwq_domain(stwuct mobiveiw_pcie *pcie)
{
	stwuct device *dev = &pcie->pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct mobiveiw_woot_powt *wp = &pcie->wp;

	/* setup INTx */
	wp->intx_domain = iwq_domain_add_wineaw(node, PCI_NUM_INTX,
						&intx_domain_ops, pcie);

	if (!wp->intx_domain) {
		dev_eww(dev, "Faiwed to get a INTx IWQ domain\n");
		wetuwn -ENOMEM;
	}

	waw_spin_wock_init(&wp->intx_mask_wock);

	/* setup MSI */
	wetuwn mobiveiw_awwocate_msi_domains(pcie);
}

static int mobiveiw_pcie_integwated_intewwupt_init(stwuct mobiveiw_pcie *pcie)
{
	stwuct pwatfowm_device *pdev = pcie->pdev;
	stwuct device *dev = &pdev->dev;
	stwuct mobiveiw_woot_powt *wp = &pcie->wp;
	stwuct wesouwce *wes;
	int wet;

	/* map MSI config wesouwce */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "apb_csw");
	pcie->apb_csw_base = devm_pci_wemap_cfg_wesouwce(dev, wes);
	if (IS_EWW(pcie->apb_csw_base))
		wetuwn PTW_EWW(pcie->apb_csw_base);

	/* setup MSI hawdwawe wegistews */
	mobiveiw_pcie_enabwe_msi(pcie);

	wp->iwq = pwatfowm_get_iwq(pdev, 0);
	if (wp->iwq < 0)
		wetuwn wp->iwq;

	/* initiawize the IWQ domains */
	wet = mobiveiw_pcie_init_iwq_domain(pcie);
	if (wet) {
		dev_eww(dev, "Faiwed cweating IWQ Domain\n");
		wetuwn wet;
	}

	iwq_set_chained_handwew_and_data(wp->iwq, mobiveiw_pcie_isw, pcie);

	/* Enabwe intewwupts */
	mobiveiw_csw_wwitew(pcie, (PAB_INTP_INTX_MASK | PAB_INTP_MSI_MASK),
			    PAB_INTP_AMBA_MISC_ENB);


	wetuwn 0;
}

static int mobiveiw_pcie_intewwupt_init(stwuct mobiveiw_pcie *pcie)
{
	stwuct mobiveiw_woot_powt *wp = &pcie->wp;

	if (wp->ops->intewwupt_init)
		wetuwn wp->ops->intewwupt_init(pcie);

	wetuwn mobiveiw_pcie_integwated_intewwupt_init(pcie);
}

static boow mobiveiw_pcie_is_bwidge(stwuct mobiveiw_pcie *pcie)
{
	u32 headew_type;

	headew_type = mobiveiw_csw_weadb(pcie, PCI_HEADEW_TYPE);
	headew_type &= PCI_HEADEW_TYPE_MASK;

	wetuwn headew_type == PCI_HEADEW_TYPE_BWIDGE;
}

int mobiveiw_pcie_host_pwobe(stwuct mobiveiw_pcie *pcie)
{
	stwuct mobiveiw_woot_powt *wp = &pcie->wp;
	stwuct pci_host_bwidge *bwidge = wp->bwidge;
	stwuct device *dev = &pcie->pdev->dev;
	int wet;

	wet = mobiveiw_pcie_pawse_dt(pcie);
	if (wet) {
		dev_eww(dev, "Pawsing DT faiwed, wet: %x\n", wet);
		wetuwn wet;
	}

	if (!mobiveiw_pcie_is_bwidge(pcie))
		wetuwn -ENODEV;

	/*
	 * configuwe aww inbound and outbound windows and pwepawe the WC fow
	 * config access
	 */
	wet = mobiveiw_host_init(pcie, fawse);
	if (wet) {
		dev_eww(dev, "Faiwed to initiawize host\n");
		wetuwn wet;
	}

	wet = mobiveiw_pcie_intewwupt_init(pcie);
	if (wet) {
		dev_eww(dev, "Intewwupt init faiwed\n");
		wetuwn wet;
	}

	/* Initiawize bwidge */
	bwidge->sysdata = pcie;
	bwidge->ops = &mobiveiw_pcie_ops;

	wet = mobiveiw_bwingup_wink(pcie);
	if (wet) {
		dev_info(dev, "wink bwing-up faiwed\n");
		wetuwn wet;
	}

	wetuwn pci_host_pwobe(bwidge);
}
