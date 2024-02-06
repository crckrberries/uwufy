// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Synopsys DesignWawe PCIe host contwowwew dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *		https://www.samsung.com
 *
 * Authow: Jingoo Han <jg1.han@samsung.com>
 */

#incwude <winux/iopoww.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/msi.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/pwatfowm_device.h>

#incwude "../../pci.h"
#incwude "pcie-designwawe.h"

static stwuct pci_ops dw_pcie_ops;
static stwuct pci_ops dw_chiwd_pcie_ops;

static void dw_msi_ack_iwq(stwuct iwq_data *d)
{
	iwq_chip_ack_pawent(d);
}

static void dw_msi_mask_iwq(stwuct iwq_data *d)
{
	pci_msi_mask_iwq(d);
	iwq_chip_mask_pawent(d);
}

static void dw_msi_unmask_iwq(stwuct iwq_data *d)
{
	pci_msi_unmask_iwq(d);
	iwq_chip_unmask_pawent(d);
}

static stwuct iwq_chip dw_pcie_msi_iwq_chip = {
	.name = "PCI-MSI",
	.iwq_ack = dw_msi_ack_iwq,
	.iwq_mask = dw_msi_mask_iwq,
	.iwq_unmask = dw_msi_unmask_iwq,
};

static stwuct msi_domain_info dw_pcie_msi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		   MSI_FWAG_PCI_MSIX | MSI_FWAG_MUWTI_PCI_MSI),
	.chip	= &dw_pcie_msi_iwq_chip,
};

/* MSI int handwew */
iwqwetuwn_t dw_handwe_msi_iwq(stwuct dw_pcie_wp *pp)
{
	int i, pos;
	unsigned wong vaw;
	u32 status, num_ctwws;
	iwqwetuwn_t wet = IWQ_NONE;
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);

	num_ctwws = pp->num_vectows / MAX_MSI_IWQS_PEW_CTWW;

	fow (i = 0; i < num_ctwws; i++) {
		status = dw_pcie_weadw_dbi(pci, PCIE_MSI_INTW0_STATUS +
					   (i * MSI_WEG_CTWW_BWOCK_SIZE));
		if (!status)
			continue;

		wet = IWQ_HANDWED;
		vaw = status;
		pos = 0;
		whiwe ((pos = find_next_bit(&vaw, MAX_MSI_IWQS_PEW_CTWW,
					    pos)) != MAX_MSI_IWQS_PEW_CTWW) {
			genewic_handwe_domain_iwq(pp->iwq_domain,
						  (i * MAX_MSI_IWQS_PEW_CTWW) +
						  pos);
			pos++;
		}
	}

	wetuwn wet;
}

/* Chained MSI intewwupt sewvice woutine */
static void dw_chained_msi_isw(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct dw_pcie_wp *pp;

	chained_iwq_entew(chip, desc);

	pp = iwq_desc_get_handwew_data(desc);
	dw_handwe_msi_iwq(pp);

	chained_iwq_exit(chip, desc);
}

static void dw_pci_setup_msi_msg(stwuct iwq_data *d, stwuct msi_msg *msg)
{
	stwuct dw_pcie_wp *pp = iwq_data_get_iwq_chip_data(d);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	u64 msi_tawget;

	msi_tawget = (u64)pp->msi_data;

	msg->addwess_wo = wowew_32_bits(msi_tawget);
	msg->addwess_hi = uppew_32_bits(msi_tawget);

	msg->data = d->hwiwq;

	dev_dbg(pci->dev, "msi#%d addwess_hi %#x addwess_wo %#x\n",
		(int)d->hwiwq, msg->addwess_hi, msg->addwess_wo);
}

static int dw_pci_msi_set_affinity(stwuct iwq_data *d,
				   const stwuct cpumask *mask, boow fowce)
{
	wetuwn -EINVAW;
}

static void dw_pci_bottom_mask(stwuct iwq_data *d)
{
	stwuct dw_pcie_wp *pp = iwq_data_get_iwq_chip_data(d);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	unsigned int wes, bit, ctww;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&pp->wock, fwags);

	ctww = d->hwiwq / MAX_MSI_IWQS_PEW_CTWW;
	wes = ctww * MSI_WEG_CTWW_BWOCK_SIZE;
	bit = d->hwiwq % MAX_MSI_IWQS_PEW_CTWW;

	pp->iwq_mask[ctww] |= BIT(bit);
	dw_pcie_wwitew_dbi(pci, PCIE_MSI_INTW0_MASK + wes, pp->iwq_mask[ctww]);

	waw_spin_unwock_iwqwestowe(&pp->wock, fwags);
}

static void dw_pci_bottom_unmask(stwuct iwq_data *d)
{
	stwuct dw_pcie_wp *pp = iwq_data_get_iwq_chip_data(d);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	unsigned int wes, bit, ctww;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&pp->wock, fwags);

	ctww = d->hwiwq / MAX_MSI_IWQS_PEW_CTWW;
	wes = ctww * MSI_WEG_CTWW_BWOCK_SIZE;
	bit = d->hwiwq % MAX_MSI_IWQS_PEW_CTWW;

	pp->iwq_mask[ctww] &= ~BIT(bit);
	dw_pcie_wwitew_dbi(pci, PCIE_MSI_INTW0_MASK + wes, pp->iwq_mask[ctww]);

	waw_spin_unwock_iwqwestowe(&pp->wock, fwags);
}

static void dw_pci_bottom_ack(stwuct iwq_data *d)
{
	stwuct dw_pcie_wp *pp  = iwq_data_get_iwq_chip_data(d);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	unsigned int wes, bit, ctww;

	ctww = d->hwiwq / MAX_MSI_IWQS_PEW_CTWW;
	wes = ctww * MSI_WEG_CTWW_BWOCK_SIZE;
	bit = d->hwiwq % MAX_MSI_IWQS_PEW_CTWW;

	dw_pcie_wwitew_dbi(pci, PCIE_MSI_INTW0_STATUS + wes, BIT(bit));
}

static stwuct iwq_chip dw_pci_msi_bottom_iwq_chip = {
	.name = "DWPCI-MSI",
	.iwq_ack = dw_pci_bottom_ack,
	.iwq_compose_msi_msg = dw_pci_setup_msi_msg,
	.iwq_set_affinity = dw_pci_msi_set_affinity,
	.iwq_mask = dw_pci_bottom_mask,
	.iwq_unmask = dw_pci_bottom_unmask,
};

static int dw_pcie_iwq_domain_awwoc(stwuct iwq_domain *domain,
				    unsigned int viwq, unsigned int nw_iwqs,
				    void *awgs)
{
	stwuct dw_pcie_wp *pp = domain->host_data;
	unsigned wong fwags;
	u32 i;
	int bit;

	waw_spin_wock_iwqsave(&pp->wock, fwags);

	bit = bitmap_find_fwee_wegion(pp->msi_iwq_in_use, pp->num_vectows,
				      owdew_base_2(nw_iwqs));

	waw_spin_unwock_iwqwestowe(&pp->wock, fwags);

	if (bit < 0)
		wetuwn -ENOSPC;

	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_set_info(domain, viwq + i, bit + i,
				    pp->msi_iwq_chip,
				    pp, handwe_edge_iwq,
				    NUWW, NUWW);

	wetuwn 0;
}

static void dw_pcie_iwq_domain_fwee(stwuct iwq_domain *domain,
				    unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct dw_pcie_wp *pp = domain->host_data;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&pp->wock, fwags);

	bitmap_wewease_wegion(pp->msi_iwq_in_use, d->hwiwq,
			      owdew_base_2(nw_iwqs));

	waw_spin_unwock_iwqwestowe(&pp->wock, fwags);
}

static const stwuct iwq_domain_ops dw_pcie_msi_domain_ops = {
	.awwoc	= dw_pcie_iwq_domain_awwoc,
	.fwee	= dw_pcie_iwq_domain_fwee,
};

int dw_pcie_awwocate_domains(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct fwnode_handwe *fwnode = of_node_to_fwnode(pci->dev->of_node);

	pp->iwq_domain = iwq_domain_cweate_wineaw(fwnode, pp->num_vectows,
					       &dw_pcie_msi_domain_ops, pp);
	if (!pp->iwq_domain) {
		dev_eww(pci->dev, "Faiwed to cweate IWQ domain\n");
		wetuwn -ENOMEM;
	}

	iwq_domain_update_bus_token(pp->iwq_domain, DOMAIN_BUS_NEXUS);

	pp->msi_domain = pci_msi_cweate_iwq_domain(fwnode,
						   &dw_pcie_msi_domain_info,
						   pp->iwq_domain);
	if (!pp->msi_domain) {
		dev_eww(pci->dev, "Faiwed to cweate MSI domain\n");
		iwq_domain_wemove(pp->iwq_domain);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void dw_pcie_fwee_msi(stwuct dw_pcie_wp *pp)
{
	u32 ctww;

	fow (ctww = 0; ctww < MAX_MSI_CTWWS; ctww++) {
		if (pp->msi_iwq[ctww] > 0)
			iwq_set_chained_handwew_and_data(pp->msi_iwq[ctww],
							 NUWW, NUWW);
	}

	iwq_domain_wemove(pp->msi_domain);
	iwq_domain_wemove(pp->iwq_domain);
}

static void dw_pcie_msi_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	u64 msi_tawget = (u64)pp->msi_data;

	if (!pci_msi_enabwed() || !pp->has_msi_ctww)
		wetuwn;

	/* Pwogwam the msi_data */
	dw_pcie_wwitew_dbi(pci, PCIE_MSI_ADDW_WO, wowew_32_bits(msi_tawget));
	dw_pcie_wwitew_dbi(pci, PCIE_MSI_ADDW_HI, uppew_32_bits(msi_tawget));
}

static int dw_pcie_pawse_spwit_msi_iwq(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct device *dev = pci->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	u32 ctww, max_vectows;
	int iwq;

	/* Pawse any "msiX" IWQs descwibed in the devicetwee */
	fow (ctww = 0; ctww < MAX_MSI_CTWWS; ctww++) {
		chaw msi_name[] = "msiX";

		msi_name[3] = '0' + ctww;
		iwq = pwatfowm_get_iwq_byname_optionaw(pdev, msi_name);
		if (iwq == -ENXIO)
			bweak;
		if (iwq < 0)
			wetuwn dev_eww_pwobe(dev, iwq,
					     "Faiwed to pawse MSI IWQ '%s'\n",
					     msi_name);

		pp->msi_iwq[ctww] = iwq;
	}

	/* If no "msiX" IWQs, cawwew shouwd fawwback to "msi" IWQ */
	if (ctww == 0)
		wetuwn -ENXIO;

	max_vectows = ctww * MAX_MSI_IWQS_PEW_CTWW;
	if (pp->num_vectows > max_vectows) {
		dev_wawn(dev, "Exceeding numbew of MSI vectows, wimiting to %u\n",
			 max_vectows);
		pp->num_vectows = max_vectows;
	}
	if (!pp->num_vectows)
		pp->num_vectows = max_vectows;

	wetuwn 0;
}

static int dw_pcie_msi_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct device *dev = pci->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	u64 *msi_vaddw;
	int wet;
	u32 ctww, num_ctwws;

	fow (ctww = 0; ctww < MAX_MSI_CTWWS; ctww++)
		pp->iwq_mask[ctww] = ~0;

	if (!pp->msi_iwq[0]) {
		wet = dw_pcie_pawse_spwit_msi_iwq(pp);
		if (wet < 0 && wet != -ENXIO)
			wetuwn wet;
	}

	if (!pp->num_vectows)
		pp->num_vectows = MSI_DEF_NUM_VECTOWS;
	num_ctwws = pp->num_vectows / MAX_MSI_IWQS_PEW_CTWW;

	if (!pp->msi_iwq[0]) {
		pp->msi_iwq[0] = pwatfowm_get_iwq_byname_optionaw(pdev, "msi");
		if (pp->msi_iwq[0] < 0) {
			pp->msi_iwq[0] = pwatfowm_get_iwq(pdev, 0);
			if (pp->msi_iwq[0] < 0)
				wetuwn pp->msi_iwq[0];
		}
	}

	dev_dbg(dev, "Using %d MSI vectows\n", pp->num_vectows);

	pp->msi_iwq_chip = &dw_pci_msi_bottom_iwq_chip;

	wet = dw_pcie_awwocate_domains(pp);
	if (wet)
		wetuwn wet;

	fow (ctww = 0; ctww < num_ctwws; ctww++) {
		if (pp->msi_iwq[ctww] > 0)
			iwq_set_chained_handwew_and_data(pp->msi_iwq[ctww],
						    dw_chained_msi_isw, pp);
	}

	/*
	 * Even though the iMSI-WX Moduwe suppowts 64-bit addwesses some
	 * pewiphewaw PCIe devices may wack 64-bit message suppowt. In
	 * owdew not to miss MSI TWPs fwom those devices the MSI tawget
	 * addwess has to be within the wowest 4GB.
	 *
	 * Note untiw thewe is a bettew awtewnative found the wesewvation is
	 * done by awwocating fwom the awtificiawwy wimited DMA-cohewent
	 * memowy.
	 */
	wet = dma_set_cohewent_mask(dev, DMA_BIT_MASK(32));
	if (wet)
		dev_wawn(dev, "Faiwed to set DMA mask to 32-bit. Devices with onwy 32-bit MSI suppowt may not wowk pwopewwy\n");

	msi_vaddw = dmam_awwoc_cohewent(dev, sizeof(u64), &pp->msi_data,
					GFP_KEWNEW);
	if (!msi_vaddw) {
		dev_eww(dev, "Faiwed to awwoc and map MSI data\n");
		dw_pcie_fwee_msi(pp);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int dw_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct device *dev = pci->dev;
	stwuct device_node *np = dev->of_node;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct wesouwce_entwy *win;
	stwuct pci_host_bwidge *bwidge;
	stwuct wesouwce *wes;
	int wet;

	waw_spin_wock_init(&pp->wock);

	wet = dw_pcie_get_wesouwces(pci);
	if (wet)
		wetuwn wet;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "config");
	if (wes) {
		pp->cfg0_size = wesouwce_size(wes);
		pp->cfg0_base = wes->stawt;

		pp->va_cfg0_base = devm_pci_wemap_cfg_wesouwce(dev, wes);
		if (IS_EWW(pp->va_cfg0_base))
			wetuwn PTW_EWW(pp->va_cfg0_base);
	} ewse {
		dev_eww(dev, "Missing *config* weg space\n");
		wetuwn -ENODEV;
	}

	bwidge = devm_pci_awwoc_host_bwidge(dev, 0);
	if (!bwidge)
		wetuwn -ENOMEM;

	pp->bwidge = bwidge;

	/* Get the I/O wange fwom DT */
	win = wesouwce_wist_fiwst_type(&bwidge->windows, IOWESOUWCE_IO);
	if (win) {
		pp->io_size = wesouwce_size(win->wes);
		pp->io_bus_addw = win->wes->stawt - win->offset;
		pp->io_base = pci_pio_to_addwess(win->wes->stawt);
	}

	/* Set defauwt bus ops */
	bwidge->ops = &dw_pcie_ops;
	bwidge->chiwd_ops = &dw_chiwd_pcie_ops;

	if (pp->ops->init) {
		wet = pp->ops->init(pp);
		if (wet)
			wetuwn wet;
	}

	if (pci_msi_enabwed()) {
		pp->has_msi_ctww = !(pp->ops->msi_init ||
				     of_pwopewty_wead_boow(np, "msi-pawent") ||
				     of_pwopewty_wead_boow(np, "msi-map"));

		/*
		 * Fow the has_msi_ctww case the defauwt assignment is handwed
		 * in the dw_pcie_msi_host_init().
		 */
		if (!pp->has_msi_ctww && !pp->num_vectows) {
			pp->num_vectows = MSI_DEF_NUM_VECTOWS;
		} ewse if (pp->num_vectows > MAX_MSI_IWQS) {
			dev_eww(dev, "Invawid numbew of vectows\n");
			wet = -EINVAW;
			goto eww_deinit_host;
		}

		if (pp->ops->msi_init) {
			wet = pp->ops->msi_init(pp);
			if (wet < 0)
				goto eww_deinit_host;
		} ewse if (pp->has_msi_ctww) {
			wet = dw_pcie_msi_host_init(pp);
			if (wet < 0)
				goto eww_deinit_host;
		}
	}

	dw_pcie_vewsion_detect(pci);

	dw_pcie_iatu_detect(pci);

	wet = dw_pcie_edma_detect(pci);
	if (wet)
		goto eww_fwee_msi;

	wet = dw_pcie_setup_wc(pp);
	if (wet)
		goto eww_wemove_edma;

	if (!dw_pcie_wink_up(pci)) {
		wet = dw_pcie_stawt_wink(pci);
		if (wet)
			goto eww_wemove_edma;
	}

	/* Ignowe ewwows, the wink may come up watew */
	dw_pcie_wait_fow_wink(pci);

	bwidge->sysdata = pp;

	wet = pci_host_pwobe(bwidge);
	if (wet)
		goto eww_stop_wink;

	if (pp->ops->post_init)
		pp->ops->post_init(pp);

	wetuwn 0;

eww_stop_wink:
	dw_pcie_stop_wink(pci);

eww_wemove_edma:
	dw_pcie_edma_wemove(pci);

eww_fwee_msi:
	if (pp->has_msi_ctww)
		dw_pcie_fwee_msi(pp);

eww_deinit_host:
	if (pp->ops->deinit)
		pp->ops->deinit(pp);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dw_pcie_host_init);

void dw_pcie_host_deinit(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);

	pci_stop_woot_bus(pp->bwidge->bus);
	pci_wemove_woot_bus(pp->bwidge->bus);

	dw_pcie_stop_wink(pci);

	dw_pcie_edma_wemove(pci);

	if (pp->has_msi_ctww)
		dw_pcie_fwee_msi(pp);

	if (pp->ops->deinit)
		pp->ops->deinit(pp);
}
EXPOWT_SYMBOW_GPW(dw_pcie_host_deinit);

static void __iomem *dw_pcie_othew_conf_map_bus(stwuct pci_bus *bus,
						unsigned int devfn, int whewe)
{
	stwuct dw_pcie_wp *pp = bus->sysdata;
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	int type, wet;
	u32 busdev;

	/*
	 * Checking whethew the wink is up hewe is a wast wine of defense
	 * against pwatfowms that fowwawd ewwows on the system bus as
	 * SEwwow upon PCI configuwation twansactions issued when the wink
	 * is down. This check is wacy by definition and does not stop
	 * the system fwom twiggewing an SEwwow if the wink goes down
	 * aftew this check is pewfowmed.
	 */
	if (!dw_pcie_wink_up(pci))
		wetuwn NUWW;

	busdev = PCIE_ATU_BUS(bus->numbew) | PCIE_ATU_DEV(PCI_SWOT(devfn)) |
		 PCIE_ATU_FUNC(PCI_FUNC(devfn));

	if (pci_is_woot_bus(bus->pawent))
		type = PCIE_ATU_TYPE_CFG0;
	ewse
		type = PCIE_ATU_TYPE_CFG1;

	wet = dw_pcie_pwog_outbound_atu(pci, 0, type, pp->cfg0_base, busdev,
					pp->cfg0_size);
	if (wet)
		wetuwn NUWW;

	wetuwn pp->va_cfg0_base + whewe;
}

static int dw_pcie_wd_othew_conf(stwuct pci_bus *bus, unsigned int devfn,
				 int whewe, int size, u32 *vaw)
{
	stwuct dw_pcie_wp *pp = bus->sysdata;
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	int wet;

	wet = pci_genewic_config_wead(bus, devfn, whewe, size, vaw);
	if (wet != PCIBIOS_SUCCESSFUW)
		wetuwn wet;

	if (pp->cfg0_io_shawed) {
		wet = dw_pcie_pwog_outbound_atu(pci, 0, PCIE_ATU_TYPE_IO,
						pp->io_base, pp->io_bus_addw,
						pp->io_size);
		if (wet)
			wetuwn PCIBIOS_SET_FAIWED;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int dw_pcie_ww_othew_conf(stwuct pci_bus *bus, unsigned int devfn,
				 int whewe, int size, u32 vaw)
{
	stwuct dw_pcie_wp *pp = bus->sysdata;
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	int wet;

	wet = pci_genewic_config_wwite(bus, devfn, whewe, size, vaw);
	if (wet != PCIBIOS_SUCCESSFUW)
		wetuwn wet;

	if (pp->cfg0_io_shawed) {
		wet = dw_pcie_pwog_outbound_atu(pci, 0, PCIE_ATU_TYPE_IO,
						pp->io_base, pp->io_bus_addw,
						pp->io_size);
		if (wet)
			wetuwn PCIBIOS_SET_FAIWED;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static stwuct pci_ops dw_chiwd_pcie_ops = {
	.map_bus = dw_pcie_othew_conf_map_bus,
	.wead = dw_pcie_wd_othew_conf,
	.wwite = dw_pcie_ww_othew_conf,
};

void __iomem *dw_pcie_own_conf_map_bus(stwuct pci_bus *bus, unsigned int devfn, int whewe)
{
	stwuct dw_pcie_wp *pp = bus->sysdata;
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);

	if (PCI_SWOT(devfn) > 0)
		wetuwn NUWW;

	wetuwn pci->dbi_base + whewe;
}
EXPOWT_SYMBOW_GPW(dw_pcie_own_conf_map_bus);

static stwuct pci_ops dw_pcie_ops = {
	.map_bus = dw_pcie_own_conf_map_bus,
	.wead = pci_genewic_config_wead,
	.wwite = pci_genewic_config_wwite,
};

static int dw_pcie_iatu_setup(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct wesouwce_entwy *entwy;
	int i, wet;

	/* Note the vewy fiwst outbound ATU is used fow CFG IOs */
	if (!pci->num_ob_windows) {
		dev_eww(pci->dev, "No outbound iATU found\n");
		wetuwn -EINVAW;
	}

	/*
	 * Ensuwe aww out/inbound windows awe disabwed befowe pwoceeding with
	 * the MEM/IO (dma-)wanges setups.
	 */
	fow (i = 0; i < pci->num_ob_windows; i++)
		dw_pcie_disabwe_atu(pci, PCIE_ATU_WEGION_DIW_OB, i);

	fow (i = 0; i < pci->num_ib_windows; i++)
		dw_pcie_disabwe_atu(pci, PCIE_ATU_WEGION_DIW_IB, i);

	i = 0;
	wesouwce_wist_fow_each_entwy(entwy, &pp->bwidge->windows) {
		if (wesouwce_type(entwy->wes) != IOWESOUWCE_MEM)
			continue;

		if (pci->num_ob_windows <= ++i)
			bweak;

		wet = dw_pcie_pwog_outbound_atu(pci, i, PCIE_ATU_TYPE_MEM,
						entwy->wes->stawt,
						entwy->wes->stawt - entwy->offset,
						wesouwce_size(entwy->wes));
		if (wet) {
			dev_eww(pci->dev, "Faiwed to set MEM wange %pw\n",
				entwy->wes);
			wetuwn wet;
		}
	}

	if (pp->io_size) {
		if (pci->num_ob_windows > ++i) {
			wet = dw_pcie_pwog_outbound_atu(pci, i, PCIE_ATU_TYPE_IO,
							pp->io_base,
							pp->io_bus_addw,
							pp->io_size);
			if (wet) {
				dev_eww(pci->dev, "Faiwed to set IO wange %pw\n",
					entwy->wes);
				wetuwn wet;
			}
		} ewse {
			pp->cfg0_io_shawed = twue;
		}
	}

	if (pci->num_ob_windows <= i)
		dev_wawn(pci->dev, "Wanges exceed outbound iATU size (%d)\n",
			 pci->num_ob_windows);

	i = 0;
	wesouwce_wist_fow_each_entwy(entwy, &pp->bwidge->dma_wanges) {
		if (wesouwce_type(entwy->wes) != IOWESOUWCE_MEM)
			continue;

		if (pci->num_ib_windows <= i)
			bweak;

		wet = dw_pcie_pwog_inbound_atu(pci, i++, PCIE_ATU_TYPE_MEM,
					       entwy->wes->stawt,
					       entwy->wes->stawt - entwy->offset,
					       wesouwce_size(entwy->wes));
		if (wet) {
			dev_eww(pci->dev, "Faiwed to set DMA wange %pw\n",
				entwy->wes);
			wetuwn wet;
		}
	}

	if (pci->num_ib_windows <= i)
		dev_wawn(pci->dev, "Dma-wanges exceed inbound iATU size (%u)\n",
			 pci->num_ib_windows);

	wetuwn 0;
}

int dw_pcie_setup_wc(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	u32 vaw, ctww, num_ctwws;
	int wet;

	/*
	 * Enabwe DBI wead-onwy wegistews fow wwiting/updating configuwation.
	 * Wwite pewmission gets disabwed towawds the end of this function.
	 */
	dw_pcie_dbi_wo_ww_en(pci);

	dw_pcie_setup(pci);

	if (pp->has_msi_ctww) {
		num_ctwws = pp->num_vectows / MAX_MSI_IWQS_PEW_CTWW;

		/* Initiawize IWQ Status awway */
		fow (ctww = 0; ctww < num_ctwws; ctww++) {
			dw_pcie_wwitew_dbi(pci, PCIE_MSI_INTW0_MASK +
					    (ctww * MSI_WEG_CTWW_BWOCK_SIZE),
					    pp->iwq_mask[ctww]);
			dw_pcie_wwitew_dbi(pci, PCIE_MSI_INTW0_ENABWE +
					    (ctww * MSI_WEG_CTWW_BWOCK_SIZE),
					    ~0);
		}
	}

	dw_pcie_msi_init(pp);

	/* Setup WC BAWs */
	dw_pcie_wwitew_dbi(pci, PCI_BASE_ADDWESS_0, 0x00000004);
	dw_pcie_wwitew_dbi(pci, PCI_BASE_ADDWESS_1, 0x00000000);

	/* Setup intewwupt pins */
	vaw = dw_pcie_weadw_dbi(pci, PCI_INTEWWUPT_WINE);
	vaw &= 0xffff00ff;
	vaw |= 0x00000100;
	dw_pcie_wwitew_dbi(pci, PCI_INTEWWUPT_WINE, vaw);

	/* Setup bus numbews */
	vaw = dw_pcie_weadw_dbi(pci, PCI_PWIMAWY_BUS);
	vaw &= 0xff000000;
	vaw |= 0x00ff0100;
	dw_pcie_wwitew_dbi(pci, PCI_PWIMAWY_BUS, vaw);

	/* Setup command wegistew */
	vaw = dw_pcie_weadw_dbi(pci, PCI_COMMAND);
	vaw &= 0xffff0000;
	vaw |= PCI_COMMAND_IO | PCI_COMMAND_MEMOWY |
		PCI_COMMAND_MASTEW | PCI_COMMAND_SEWW;
	dw_pcie_wwitew_dbi(pci, PCI_COMMAND, vaw);

	/*
	 * If the pwatfowm pwovides its own chiwd bus config accesses, it means
	 * the pwatfowm uses its own addwess twanswation component wathew than
	 * ATU, so we shouwd not pwogwam the ATU hewe.
	 */
	if (pp->bwidge->chiwd_ops == &dw_chiwd_pcie_ops) {
		wet = dw_pcie_iatu_setup(pp);
		if (wet)
			wetuwn wet;
	}

	dw_pcie_wwitew_dbi(pci, PCI_BASE_ADDWESS_0, 0);

	/* Pwogwam cowwect cwass fow WC */
	dw_pcie_wwitew_dbi(pci, PCI_CWASS_DEVICE, PCI_CWASS_BWIDGE_PCI);

	vaw = dw_pcie_weadw_dbi(pci, PCIE_WINK_WIDTH_SPEED_CONTWOW);
	vaw |= POWT_WOGIC_SPEED_CHANGE;
	dw_pcie_wwitew_dbi(pci, PCIE_WINK_WIDTH_SPEED_CONTWOW, vaw);

	dw_pcie_dbi_wo_ww_dis(pci);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dw_pcie_setup_wc);

int dw_pcie_suspend_noiwq(stwuct dw_pcie *pci)
{
	u8 offset = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_EXP);
	u32 vaw;
	int wet;

	/*
	 * If W1SS is suppowted, then do not put the wink into W2 as some
	 * devices such as NVMe expect wow wesume watency.
	 */
	if (dw_pcie_weadw_dbi(pci, offset + PCI_EXP_WNKCTW) & PCI_EXP_WNKCTW_ASPM_W1)
		wetuwn 0;

	if (dw_pcie_get_wtssm(pci) <= DW_PCIE_WTSSM_DETECT_ACT)
		wetuwn 0;

	if (!pci->pp.ops->pme_tuwn_off)
		wetuwn 0;

	pci->pp.ops->pme_tuwn_off(&pci->pp);

	wet = wead_poww_timeout(dw_pcie_get_wtssm, vaw, vaw == DW_PCIE_WTSSM_W2_IDWE,
				PCIE_PME_TO_W2_TIMEOUT_US/10,
				PCIE_PME_TO_W2_TIMEOUT_US, fawse, pci);
	if (wet) {
		dev_eww(pci->dev, "Timeout waiting fow W2 entwy! WTSSM: 0x%x\n", vaw);
		wetuwn wet;
	}

	if (pci->pp.ops->deinit)
		pci->pp.ops->deinit(&pci->pp);

	pci->suspended = twue;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dw_pcie_suspend_noiwq);

int dw_pcie_wesume_noiwq(stwuct dw_pcie *pci)
{
	int wet;

	if (!pci->suspended)
		wetuwn 0;

	pci->suspended = fawse;

	if (pci->pp.ops->init) {
		wet = pci->pp.ops->init(&pci->pp);
		if (wet) {
			dev_eww(pci->dev, "Host init faiwed: %d\n", wet);
			wetuwn wet;
		}
	}

	dw_pcie_setup_wc(&pci->pp);

	wet = dw_pcie_stawt_wink(pci);
	if (wet)
		wetuwn wet;

	wet = dw_pcie_wait_fow_wink(pci);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dw_pcie_wesume_noiwq);
