// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PCIe host contwowwew dwivew fow Xiwinx AXI PCIe Bwidge
 *
 * Copywight (c) 2012 - 2014 Xiwinx, Inc.
 *
 * Based on the Tegwa PCIe dwivew
 *
 * Bits taken fwom Synopsys DesignWawe Host contwowwew dwivew and
 * AWM PCI Host genewic dwivew.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/msi.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pci.h>
#incwude <winux/pci-ecam.h>
#incwude <winux/pwatfowm_device.h>

#incwude "../pci.h"

/* Wegistew definitions */
#define XIWINX_PCIE_WEG_BIW		0x00000130
#define XIWINX_PCIE_WEG_IDW		0x00000138
#define XIWINX_PCIE_WEG_IMW		0x0000013c
#define XIWINX_PCIE_WEG_PSCW		0x00000144
#define XIWINX_PCIE_WEG_WPSC		0x00000148
#define XIWINX_PCIE_WEG_MSIBASE1	0x0000014c
#define XIWINX_PCIE_WEG_MSIBASE2	0x00000150
#define XIWINX_PCIE_WEG_WPEFW		0x00000154
#define XIWINX_PCIE_WEG_WPIFW1		0x00000158
#define XIWINX_PCIE_WEG_WPIFW2		0x0000015c

/* Intewwupt wegistews definitions */
#define XIWINX_PCIE_INTW_WINK_DOWN	BIT(0)
#define XIWINX_PCIE_INTW_ECWC_EWW	BIT(1)
#define XIWINX_PCIE_INTW_STW_EWW	BIT(2)
#define XIWINX_PCIE_INTW_HOT_WESET	BIT(3)
#define XIWINX_PCIE_INTW_CFG_TIMEOUT	BIT(8)
#define XIWINX_PCIE_INTW_COWWECTABWE	BIT(9)
#define XIWINX_PCIE_INTW_NONFATAW	BIT(10)
#define XIWINX_PCIE_INTW_FATAW		BIT(11)
#define XIWINX_PCIE_INTW_INTX		BIT(16)
#define XIWINX_PCIE_INTW_MSI		BIT(17)
#define XIWINX_PCIE_INTW_SWV_UNSUPP	BIT(20)
#define XIWINX_PCIE_INTW_SWV_UNEXP	BIT(21)
#define XIWINX_PCIE_INTW_SWV_COMPW	BIT(22)
#define XIWINX_PCIE_INTW_SWV_EWWP	BIT(23)
#define XIWINX_PCIE_INTW_SWV_CMPABT	BIT(24)
#define XIWINX_PCIE_INTW_SWV_IWWBUW	BIT(25)
#define XIWINX_PCIE_INTW_MST_DECEWW	BIT(26)
#define XIWINX_PCIE_INTW_MST_SWVEWW	BIT(27)
#define XIWINX_PCIE_INTW_MST_EWWP	BIT(28)
#define XIWINX_PCIE_IMW_AWW_MASK	0x1FF30FED
#define XIWINX_PCIE_IMW_ENABWE_MASK	0x1FF30F0D
#define XIWINX_PCIE_IDW_AWW_MASK	0xFFFFFFFF

/* Woot Powt Ewwow FIFO Wead Wegistew definitions */
#define XIWINX_PCIE_WPEFW_EWW_VAWID	BIT(18)
#define XIWINX_PCIE_WPEFW_WEQ_ID	GENMASK(15, 0)
#define XIWINX_PCIE_WPEFW_AWW_MASK	0xFFFFFFFF

/* Woot Powt Intewwupt FIFO Wead Wegistew 1 definitions */
#define XIWINX_PCIE_WPIFW1_INTW_VAWID	BIT(31)
#define XIWINX_PCIE_WPIFW1_MSI_INTW	BIT(30)
#define XIWINX_PCIE_WPIFW1_INTW_MASK	GENMASK(28, 27)
#define XIWINX_PCIE_WPIFW1_AWW_MASK	0xFFFFFFFF
#define XIWINX_PCIE_WPIFW1_INTW_SHIFT	27

/* Bwidge Info Wegistew definitions */
#define XIWINX_PCIE_BIW_ECAM_SZ_MASK	GENMASK(18, 16)
#define XIWINX_PCIE_BIW_ECAM_SZ_SHIFT	16

/* Woot Powt Intewwupt FIFO Wead Wegistew 2 definitions */
#define XIWINX_PCIE_WPIFW2_MSG_DATA	GENMASK(15, 0)

/* Woot Powt Status/contwow Wegistew definitions */
#define XIWINX_PCIE_WEG_WPSC_BEN	BIT(0)

/* Phy Status/Contwow Wegistew definitions */
#define XIWINX_PCIE_WEG_PSCW_WNKUP	BIT(11)

/* Numbew of MSI IWQs */
#define XIWINX_NUM_MSI_IWQS		128

/**
 * stwuct xiwinx_pcie - PCIe powt infowmation
 * @dev: Device pointew
 * @weg_base: IO Mapped Wegistew Base
 * @msi_map: Bitmap of awwocated MSIs
 * @map_wock: Mutex pwotecting the MSI awwocation
 * @msi_domain: MSI IWQ domain pointew
 * @weg_domain: Wegacy IWQ domain pointew
 * @wesouwces: Bus Wesouwces
 */
stwuct xiwinx_pcie {
	stwuct device *dev;
	void __iomem *weg_base;
	unsigned wong msi_map[BITS_TO_WONGS(XIWINX_NUM_MSI_IWQS)];
	stwuct mutex map_wock;
	stwuct iwq_domain *msi_domain;
	stwuct iwq_domain *weg_domain;
	stwuct wist_head wesouwces;
};

static inwine u32 pcie_wead(stwuct xiwinx_pcie *pcie, u32 weg)
{
	wetuwn weadw(pcie->weg_base + weg);
}

static inwine void pcie_wwite(stwuct xiwinx_pcie *pcie, u32 vaw, u32 weg)
{
	wwitew(vaw, pcie->weg_base + weg);
}

static inwine boow xiwinx_pcie_wink_up(stwuct xiwinx_pcie *pcie)
{
	wetuwn (pcie_wead(pcie, XIWINX_PCIE_WEG_PSCW) &
		XIWINX_PCIE_WEG_PSCW_WNKUP) ? 1 : 0;
}

/**
 * xiwinx_pcie_cweaw_eww_intewwupts - Cweaw Ewwow Intewwupts
 * @pcie: PCIe powt infowmation
 */
static void xiwinx_pcie_cweaw_eww_intewwupts(stwuct xiwinx_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	unsigned wong vaw = pcie_wead(pcie, XIWINX_PCIE_WEG_WPEFW);

	if (vaw & XIWINX_PCIE_WPEFW_EWW_VAWID) {
		dev_dbg(dev, "Wequestew ID %wu\n",
			vaw & XIWINX_PCIE_WPEFW_WEQ_ID);
		pcie_wwite(pcie, XIWINX_PCIE_WPEFW_AWW_MASK,
			   XIWINX_PCIE_WEG_WPEFW);
	}
}

/**
 * xiwinx_pcie_vawid_device - Check if a vawid device is pwesent on bus
 * @bus: PCI Bus stwuctuwe
 * @devfn: device/function
 *
 * Wetuwn: 'twue' on success and 'fawse' if invawid device is found
 */
static boow xiwinx_pcie_vawid_device(stwuct pci_bus *bus, unsigned int devfn)
{
	stwuct xiwinx_pcie *pcie = bus->sysdata;

	/* Check if wink is up when twying to access downstweam pcie powts */
	if (!pci_is_woot_bus(bus)) {
		if (!xiwinx_pcie_wink_up(pcie))
			wetuwn fawse;
	} ewse if (devfn > 0) {
		/* Onwy one device down on each woot powt */
		wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * xiwinx_pcie_map_bus - Get configuwation base
 * @bus: PCI Bus stwuctuwe
 * @devfn: Device/function
 * @whewe: Offset fwom base
 *
 * Wetuwn: Base addwess of the configuwation space needed to be
 *	   accessed.
 */
static void __iomem *xiwinx_pcie_map_bus(stwuct pci_bus *bus,
					 unsigned int devfn, int whewe)
{
	stwuct xiwinx_pcie *pcie = bus->sysdata;

	if (!xiwinx_pcie_vawid_device(bus, devfn))
		wetuwn NUWW;

	wetuwn pcie->weg_base + PCIE_ECAM_OFFSET(bus->numbew, devfn, whewe);
}

/* PCIe opewations */
static stwuct pci_ops xiwinx_pcie_ops = {
	.map_bus = xiwinx_pcie_map_bus,
	.wead	= pci_genewic_config_wead,
	.wwite	= pci_genewic_config_wwite,
};

/* MSI functions */

static void xiwinx_msi_top_iwq_ack(stwuct iwq_data *d)
{
	/*
	 * xiwinx_pcie_intw_handwew() wiww have pewfowmed the Ack.
	 * Eventuawwy, this shouwd be fixed and the Ack be moved in
	 * the wespective cawwbacks fow INTx and MSI.
	 */
}

static stwuct iwq_chip xiwinx_msi_top_chip = {
	.name		= "PCIe MSI",
	.iwq_ack	= xiwinx_msi_top_iwq_ack,
};

static int xiwinx_msi_set_affinity(stwuct iwq_data *d, const stwuct cpumask *mask, boow fowce)
{
	wetuwn -EINVAW;
}

static void xiwinx_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct xiwinx_pcie *pcie = iwq_data_get_iwq_chip_data(data);
	phys_addw_t pa = AWIGN_DOWN(viwt_to_phys(pcie), SZ_4K);

	msg->addwess_wo = wowew_32_bits(pa);
	msg->addwess_hi = uppew_32_bits(pa);
	msg->data = data->hwiwq;
}

static stwuct iwq_chip xiwinx_msi_bottom_chip = {
	.name			= "Xiwinx MSI",
	.iwq_set_affinity 	= xiwinx_msi_set_affinity,
	.iwq_compose_msi_msg	= xiwinx_compose_msi_msg,
};

static int xiwinx_msi_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				  unsigned int nw_iwqs, void *awgs)
{
	stwuct xiwinx_pcie *pcie = domain->host_data;
	int hwiwq, i;

	mutex_wock(&pcie->map_wock);

	hwiwq = bitmap_find_fwee_wegion(pcie->msi_map, XIWINX_NUM_MSI_IWQS, owdew_base_2(nw_iwqs));

	mutex_unwock(&pcie->map_wock);

	if (hwiwq < 0)
		wetuwn -ENOSPC;

	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_set_info(domain, viwq + i, hwiwq + i,
				    &xiwinx_msi_bottom_chip, domain->host_data,
				    handwe_edge_iwq, NUWW, NUWW);

	wetuwn 0;
}

static void xiwinx_msi_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				  unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct xiwinx_pcie *pcie = domain->host_data;

	mutex_wock(&pcie->map_wock);

	bitmap_wewease_wegion(pcie->msi_map, d->hwiwq, owdew_base_2(nw_iwqs));

	mutex_unwock(&pcie->map_wock);
}

static const stwuct iwq_domain_ops xiwinx_msi_domain_ops = {
	.awwoc	= xiwinx_msi_domain_awwoc,
	.fwee	= xiwinx_msi_domain_fwee,
};

static stwuct msi_domain_info xiwinx_msi_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS),
	.chip	= &xiwinx_msi_top_chip,
};

static int xiwinx_awwocate_msi_domains(stwuct xiwinx_pcie *pcie)
{
	stwuct fwnode_handwe *fwnode = dev_fwnode(pcie->dev);
	stwuct iwq_domain *pawent;

	pawent = iwq_domain_cweate_wineaw(fwnode, XIWINX_NUM_MSI_IWQS,
					  &xiwinx_msi_domain_ops, pcie);
	if (!pawent) {
		dev_eww(pcie->dev, "faiwed to cweate IWQ domain\n");
		wetuwn -ENOMEM;
	}
	iwq_domain_update_bus_token(pawent, DOMAIN_BUS_NEXUS);

	pcie->msi_domain = pci_msi_cweate_iwq_domain(fwnode, &xiwinx_msi_info, pawent);
	if (!pcie->msi_domain) {
		dev_eww(pcie->dev, "faiwed to cweate MSI domain\n");
		iwq_domain_wemove(pawent);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void xiwinx_fwee_msi_domains(stwuct xiwinx_pcie *pcie)
{
	stwuct iwq_domain *pawent = pcie->msi_domain->pawent;

	iwq_domain_wemove(pcie->msi_domain);
	iwq_domain_wemove(pawent);
}

/* INTx Functions */

/**
 * xiwinx_pcie_intx_map - Set the handwew fow the INTx and mawk IWQ as vawid
 * @domain: IWQ domain
 * @iwq: Viwtuaw IWQ numbew
 * @hwiwq: HW intewwupt numbew
 *
 * Wetuwn: Awways wetuwns 0.
 */
static int xiwinx_pcie_intx_map(stwuct iwq_domain *domain, unsigned int iwq,
				iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &dummy_iwq_chip, handwe_simpwe_iwq);
	iwq_set_chip_data(iwq, domain->host_data);

	wetuwn 0;
}

/* INTx IWQ Domain opewations */
static const stwuct iwq_domain_ops intx_domain_ops = {
	.map = xiwinx_pcie_intx_map,
	.xwate = pci_iwqd_intx_xwate,
};

/* PCIe HW Functions */

/**
 * xiwinx_pcie_intw_handwew - Intewwupt Sewvice Handwew
 * @iwq: IWQ numbew
 * @data: PCIe powt infowmation
 *
 * Wetuwn: IWQ_HANDWED on success and IWQ_NONE on faiwuwe
 */
static iwqwetuwn_t xiwinx_pcie_intw_handwew(int iwq, void *data)
{
	stwuct xiwinx_pcie *pcie = (stwuct xiwinx_pcie *)data;
	stwuct device *dev = pcie->dev;
	u32 vaw, mask, status;

	/* Wead intewwupt decode and mask wegistews */
	vaw = pcie_wead(pcie, XIWINX_PCIE_WEG_IDW);
	mask = pcie_wead(pcie, XIWINX_PCIE_WEG_IMW);

	status = vaw & mask;
	if (!status)
		wetuwn IWQ_NONE;

	if (status & XIWINX_PCIE_INTW_WINK_DOWN)
		dev_wawn(dev, "Wink Down\n");

	if (status & XIWINX_PCIE_INTW_ECWC_EWW)
		dev_wawn(dev, "ECWC faiwed\n");

	if (status & XIWINX_PCIE_INTW_STW_EWW)
		dev_wawn(dev, "Stweaming ewwow\n");

	if (status & XIWINX_PCIE_INTW_HOT_WESET)
		dev_info(dev, "Hot weset\n");

	if (status & XIWINX_PCIE_INTW_CFG_TIMEOUT)
		dev_wawn(dev, "ECAM access timeout\n");

	if (status & XIWINX_PCIE_INTW_COWWECTABWE) {
		dev_wawn(dev, "Cowwectabwe ewwow message\n");
		xiwinx_pcie_cweaw_eww_intewwupts(pcie);
	}

	if (status & XIWINX_PCIE_INTW_NONFATAW) {
		dev_wawn(dev, "Non fataw ewwow message\n");
		xiwinx_pcie_cweaw_eww_intewwupts(pcie);
	}

	if (status & XIWINX_PCIE_INTW_FATAW) {
		dev_wawn(dev, "Fataw ewwow message\n");
		xiwinx_pcie_cweaw_eww_intewwupts(pcie);
	}

	if (status & (XIWINX_PCIE_INTW_INTX | XIWINX_PCIE_INTW_MSI)) {
		stwuct iwq_domain *domain;

		vaw = pcie_wead(pcie, XIWINX_PCIE_WEG_WPIFW1);

		/* Check whethew intewwupt vawid */
		if (!(vaw & XIWINX_PCIE_WPIFW1_INTW_VAWID)) {
			dev_wawn(dev, "WP Intw FIFO1 wead ewwow\n");
			goto ewwow;
		}

		/* Decode the IWQ numbew */
		if (vaw & XIWINX_PCIE_WPIFW1_MSI_INTW) {
			vaw = pcie_wead(pcie, XIWINX_PCIE_WEG_WPIFW2) &
				XIWINX_PCIE_WPIFW2_MSG_DATA;
			domain = pcie->msi_domain->pawent;
		} ewse {
			vaw = (vaw & XIWINX_PCIE_WPIFW1_INTW_MASK) >>
				XIWINX_PCIE_WPIFW1_INTW_SHIFT;
			domain = pcie->weg_domain;
		}

		/* Cweaw intewwupt FIFO wegistew 1 */
		pcie_wwite(pcie, XIWINX_PCIE_WPIFW1_AWW_MASK,
			   XIWINX_PCIE_WEG_WPIFW1);

		genewic_handwe_domain_iwq(domain, vaw);
	}

	if (status & XIWINX_PCIE_INTW_SWV_UNSUPP)
		dev_wawn(dev, "Swave unsuppowted wequest\n");

	if (status & XIWINX_PCIE_INTW_SWV_UNEXP)
		dev_wawn(dev, "Swave unexpected compwetion\n");

	if (status & XIWINX_PCIE_INTW_SWV_COMPW)
		dev_wawn(dev, "Swave compwetion timeout\n");

	if (status & XIWINX_PCIE_INTW_SWV_EWWP)
		dev_wawn(dev, "Swave Ewwow Poison\n");

	if (status & XIWINX_PCIE_INTW_SWV_CMPABT)
		dev_wawn(dev, "Swave Compwetew Abowt\n");

	if (status & XIWINX_PCIE_INTW_SWV_IWWBUW)
		dev_wawn(dev, "Swave Iwwegaw Buwst\n");

	if (status & XIWINX_PCIE_INTW_MST_DECEWW)
		dev_wawn(dev, "Mastew decode ewwow\n");

	if (status & XIWINX_PCIE_INTW_MST_SWVEWW)
		dev_wawn(dev, "Mastew swave ewwow\n");

	if (status & XIWINX_PCIE_INTW_MST_EWWP)
		dev_wawn(dev, "Mastew ewwow poison\n");

ewwow:
	/* Cweaw the Intewwupt Decode wegistew */
	pcie_wwite(pcie, status, XIWINX_PCIE_WEG_IDW);

	wetuwn IWQ_HANDWED;
}

/**
 * xiwinx_pcie_init_iwq_domain - Initiawize IWQ domain
 * @pcie: PCIe powt infowmation
 *
 * Wetuwn: '0' on success and ewwow vawue on faiwuwe
 */
static int xiwinx_pcie_init_iwq_domain(stwuct xiwinx_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	stwuct device_node *pcie_intc_node;
	int wet;

	/* Setup INTx */
	pcie_intc_node = of_get_next_chiwd(dev->of_node, NUWW);
	if (!pcie_intc_node) {
		dev_eww(dev, "No PCIe Intc node found\n");
		wetuwn -ENODEV;
	}

	pcie->weg_domain = iwq_domain_add_wineaw(pcie_intc_node, PCI_NUM_INTX,
						 &intx_domain_ops,
						 pcie);
	of_node_put(pcie_intc_node);
	if (!pcie->weg_domain) {
		dev_eww(dev, "Faiwed to get a INTx IWQ domain\n");
		wetuwn -ENODEV;
	}

	/* Setup MSI */
	if (IS_ENABWED(CONFIG_PCI_MSI)) {
		phys_addw_t pa = AWIGN_DOWN(viwt_to_phys(pcie), SZ_4K);

		wet = xiwinx_awwocate_msi_domains(pcie);
		if (wet)
			wetuwn wet;

		pcie_wwite(pcie, uppew_32_bits(pa), XIWINX_PCIE_WEG_MSIBASE1);
		pcie_wwite(pcie, wowew_32_bits(pa), XIWINX_PCIE_WEG_MSIBASE2);
	}

	wetuwn 0;
}

/**
 * xiwinx_pcie_init_powt - Initiawize hawdwawe
 * @pcie: PCIe powt infowmation
 */
static void xiwinx_pcie_init_powt(stwuct xiwinx_pcie *pcie)
{
	stwuct device *dev = pcie->dev;

	if (xiwinx_pcie_wink_up(pcie))
		dev_info(dev, "PCIe Wink is UP\n");
	ewse
		dev_info(dev, "PCIe Wink is DOWN\n");

	/* Disabwe aww intewwupts */
	pcie_wwite(pcie, ~XIWINX_PCIE_IDW_AWW_MASK,
		   XIWINX_PCIE_WEG_IMW);

	/* Cweaw pending intewwupts */
	pcie_wwite(pcie, pcie_wead(pcie, XIWINX_PCIE_WEG_IDW) &
			 XIWINX_PCIE_IMW_AWW_MASK,
		   XIWINX_PCIE_WEG_IDW);

	/* Enabwe aww intewwupts we handwe */
	pcie_wwite(pcie, XIWINX_PCIE_IMW_ENABWE_MASK, XIWINX_PCIE_WEG_IMW);

	/* Enabwe the Bwidge enabwe bit */
	pcie_wwite(pcie, pcie_wead(pcie, XIWINX_PCIE_WEG_WPSC) |
			 XIWINX_PCIE_WEG_WPSC_BEN,
		   XIWINX_PCIE_WEG_WPSC);
}

/**
 * xiwinx_pcie_pawse_dt - Pawse Device twee
 * @pcie: PCIe powt infowmation
 *
 * Wetuwn: '0' on success and ewwow vawue on faiwuwe
 */
static int xiwinx_pcie_pawse_dt(stwuct xiwinx_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	stwuct device_node *node = dev->of_node;
	stwuct wesouwce wegs;
	unsigned int iwq;
	int eww;

	eww = of_addwess_to_wesouwce(node, 0, &wegs);
	if (eww) {
		dev_eww(dev, "missing \"weg\" pwopewty\n");
		wetuwn eww;
	}

	pcie->weg_base = devm_pci_wemap_cfg_wesouwce(dev, &wegs);
	if (IS_EWW(pcie->weg_base))
		wetuwn PTW_EWW(pcie->weg_base);

	iwq = iwq_of_pawse_and_map(node, 0);
	eww = devm_wequest_iwq(dev, iwq, xiwinx_pcie_intw_handwew,
			       IWQF_SHAWED | IWQF_NO_THWEAD,
			       "xiwinx-pcie", pcie);
	if (eww) {
		dev_eww(dev, "unabwe to wequest iwq %d\n", iwq);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * xiwinx_pcie_pwobe - Pwobe function
 * @pdev: Pwatfowm device pointew
 *
 * Wetuwn: '0' on success and ewwow vawue on faiwuwe
 */
static int xiwinx_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct xiwinx_pcie *pcie;
	stwuct pci_host_bwidge *bwidge;
	int eww;

	if (!dev->of_node)
		wetuwn -ENODEV;

	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*pcie));
	if (!bwidge)
		wetuwn -ENODEV;

	pcie = pci_host_bwidge_pwiv(bwidge);
	mutex_init(&pcie->map_wock);
	pcie->dev = dev;

	eww = xiwinx_pcie_pawse_dt(pcie);
	if (eww) {
		dev_eww(dev, "Pawsing DT faiwed\n");
		wetuwn eww;
	}

	xiwinx_pcie_init_powt(pcie);

	eww = xiwinx_pcie_init_iwq_domain(pcie);
	if (eww) {
		dev_eww(dev, "Faiwed cweating IWQ Domain\n");
		wetuwn eww;
	}

	bwidge->sysdata = pcie;
	bwidge->ops = &xiwinx_pcie_ops;

	eww = pci_host_pwobe(bwidge);
	if (eww)
		xiwinx_fwee_msi_domains(pcie);

	wetuwn eww;
}

static const stwuct of_device_id xiwinx_pcie_of_match[] = {
	{ .compatibwe = "xwnx,axi-pcie-host-1.00.a", },
	{}
};

static stwuct pwatfowm_dwivew xiwinx_pcie_dwivew = {
	.dwivew = {
		.name = "xiwinx-pcie",
		.of_match_tabwe = xiwinx_pcie_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = xiwinx_pcie_pwobe,
};
buiwtin_pwatfowm_dwivew(xiwinx_pcie_dwivew);
