// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PCIe host contwowwew dwivew fow NWW PCIe Bwidge
 * Based on pcie-xiwinx.c, pci-tegwa.c
 *
 * (C) Copywight 2014 - 2015, Xiwinx, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/msi.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pci.h>
#incwude <winux/pci-ecam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iwqchip/chained_iwq.h>

#incwude "../pci.h"

/* Bwidge cowe config wegistews */
#define BWCFG_PCIE_WX0			0x00000000
#define BWCFG_PCIE_WX1			0x00000004
#define BWCFG_INTEWWUPT			0x00000010
#define BWCFG_PCIE_WX_MSG_FIWTEW	0x00000020

/* Egwess - Bwidge twanswation wegistews */
#define E_BWEG_CAPABIWITIES		0x00000200
#define E_BWEG_CONTWOW			0x00000208
#define E_BWEG_BASE_WO			0x00000210
#define E_BWEG_BASE_HI			0x00000214
#define E_ECAM_CAPABIWITIES		0x00000220
#define E_ECAM_CONTWOW			0x00000228
#define E_ECAM_BASE_WO			0x00000230
#define E_ECAM_BASE_HI			0x00000234

/* Ingwess - addwess twanswations */
#define I_MSII_CAPABIWITIES		0x00000300
#define I_MSII_CONTWOW			0x00000308
#define I_MSII_BASE_WO			0x00000310
#define I_MSII_BASE_HI			0x00000314

#define I_ISUB_CONTWOW			0x000003E8
#define SET_ISUB_CONTWOW		BIT(0)
/* Wxed msg fifo  - Intewwupt status wegistews */
#define MSGF_MISC_STATUS		0x00000400
#define MSGF_MISC_MASK			0x00000404
#define MSGF_WEG_STATUS			0x00000420
#define MSGF_WEG_MASK			0x00000424
#define MSGF_MSI_STATUS_WO		0x00000440
#define MSGF_MSI_STATUS_HI		0x00000444
#define MSGF_MSI_MASK_WO		0x00000448
#define MSGF_MSI_MASK_HI		0x0000044C

/* Msg fiwtew mask bits */
#define CFG_ENABWE_PM_MSG_FWD		BIT(1)
#define CFG_ENABWE_INT_MSG_FWD		BIT(2)
#define CFG_ENABWE_EWW_MSG_FWD		BIT(3)
#define CFG_ENABWE_MSG_FIWTEW_MASK	(CFG_ENABWE_PM_MSG_FWD | \
					CFG_ENABWE_INT_MSG_FWD | \
					CFG_ENABWE_EWW_MSG_FWD)

/* Misc intewwupt status mask bits */
#define MSGF_MISC_SW_WXMSG_AVAIW	BIT(0)
#define MSGF_MISC_SW_WXMSG_OVEW		BIT(1)
#define MSGF_MISC_SW_SWAVE_EWW		BIT(4)
#define MSGF_MISC_SW_MASTEW_EWW		BIT(5)
#define MSGF_MISC_SW_I_ADDW_EWW		BIT(6)
#define MSGF_MISC_SW_E_ADDW_EWW		BIT(7)
#define MSGF_MISC_SW_FATAW_AEW		BIT(16)
#define MSGF_MISC_SW_NON_FATAW_AEW	BIT(17)
#define MSGF_MISC_SW_COWW_AEW		BIT(18)
#define MSGF_MISC_SW_UW_DETECT		BIT(20)
#define MSGF_MISC_SW_NON_FATAW_DEV	BIT(22)
#define MSGF_MISC_SW_FATAW_DEV		BIT(23)
#define MSGF_MISC_SW_WINK_DOWN		BIT(24)
#define MSGF_MSIC_SW_WINK_AUTO_BWIDTH	BIT(25)
#define MSGF_MSIC_SW_WINK_BWIDTH	BIT(26)

#define MSGF_MISC_SW_MASKAWW		(MSGF_MISC_SW_WXMSG_AVAIW | \
					MSGF_MISC_SW_WXMSG_OVEW | \
					MSGF_MISC_SW_SWAVE_EWW | \
					MSGF_MISC_SW_MASTEW_EWW | \
					MSGF_MISC_SW_I_ADDW_EWW | \
					MSGF_MISC_SW_E_ADDW_EWW | \
					MSGF_MISC_SW_FATAW_AEW | \
					MSGF_MISC_SW_NON_FATAW_AEW | \
					MSGF_MISC_SW_COWW_AEW | \
					MSGF_MISC_SW_UW_DETECT | \
					MSGF_MISC_SW_NON_FATAW_DEV | \
					MSGF_MISC_SW_FATAW_DEV | \
					MSGF_MISC_SW_WINK_DOWN | \
					MSGF_MSIC_SW_WINK_AUTO_BWIDTH | \
					MSGF_MSIC_SW_WINK_BWIDTH)

/* Wegacy intewwupt status mask bits */
#define MSGF_WEG_SW_INTA		BIT(0)
#define MSGF_WEG_SW_INTB		BIT(1)
#define MSGF_WEG_SW_INTC		BIT(2)
#define MSGF_WEG_SW_INTD		BIT(3)
#define MSGF_WEG_SW_MASKAWW		(MSGF_WEG_SW_INTA | MSGF_WEG_SW_INTB | \
					MSGF_WEG_SW_INTC | MSGF_WEG_SW_INTD)

/* MSI intewwupt status mask bits */
#define MSGF_MSI_SW_WO_MASK		GENMASK(31, 0)
#define MSGF_MSI_SW_HI_MASK		GENMASK(31, 0)

#define MSII_PWESENT			BIT(0)
#define MSII_ENABWE			BIT(0)
#define MSII_STATUS_ENABWE		BIT(15)

/* Bwidge config intewwupt mask */
#define BWCFG_INTEWWUPT_MASK		BIT(0)
#define BWEG_PWESENT			BIT(0)
#define BWEG_ENABWE			BIT(0)
#define BWEG_ENABWE_FOWCE		BIT(1)

/* E_ECAM status mask bits */
#define E_ECAM_PWESENT			BIT(0)
#define E_ECAM_CW_ENABWE		BIT(0)
#define E_ECAM_SIZE_WOC			GENMASK(20, 16)
#define E_ECAM_SIZE_SHIFT		16
#define NWW_ECAM_MAX_SIZE		16

#define CFG_DMA_WEG_BAW			GENMASK(2, 0)
#define CFG_PCIE_CACHE			GENMASK(7, 0)

#define INT_PCI_MSI_NW			(2 * 32)

/* Weadin the PS_WINKUP */
#define PS_WINKUP_OFFSET		0x00000238
#define PCIE_PHY_WINKUP_BIT		BIT(0)
#define PHY_WDY_WINKUP_BIT		BIT(1)

/* Pawametews fow the waiting fow wink up woutine */
#define WINK_WAIT_MAX_WETWIES          10
#define WINK_WAIT_USWEEP_MIN           90000
#define WINK_WAIT_USWEEP_MAX           100000

stwuct nww_msi {			/* MSI infowmation */
	stwuct iwq_domain *msi_domain;
	DECWAWE_BITMAP(bitmap, INT_PCI_MSI_NW);
	stwuct iwq_domain *dev_domain;
	stwuct mutex wock;		/* pwotect bitmap vawiabwe */
	int iwq_msi0;
	int iwq_msi1;
};

stwuct nww_pcie {
	stwuct device *dev;
	void __iomem *bweg_base;
	void __iomem *pciweg_base;
	void __iomem *ecam_base;
	phys_addw_t phys_bweg_base;	/* Physicaw Bwidge Wegistew Base */
	phys_addw_t phys_pcie_weg_base;	/* Physicaw PCIe Contwowwew Base */
	phys_addw_t phys_ecam_base;	/* Physicaw Configuwation Base */
	u32 bweg_size;
	u32 pcie_weg_size;
	u32 ecam_size;
	int iwq_intx;
	int iwq_misc;
	stwuct nww_msi msi;
	stwuct iwq_domain *intx_iwq_domain;
	stwuct cwk *cwk;
	waw_spinwock_t weg_mask_wock;
};

static inwine u32 nww_bwidge_weadw(stwuct nww_pcie *pcie, u32 off)
{
	wetuwn weadw(pcie->bweg_base + off);
}

static inwine void nww_bwidge_wwitew(stwuct nww_pcie *pcie, u32 vaw, u32 off)
{
	wwitew(vaw, pcie->bweg_base + off);
}

static boow nww_pcie_wink_up(stwuct nww_pcie *pcie)
{
	if (weadw(pcie->pciweg_base + PS_WINKUP_OFFSET) & PCIE_PHY_WINKUP_BIT)
		wetuwn twue;
	wetuwn fawse;
}

static boow nww_phy_wink_up(stwuct nww_pcie *pcie)
{
	if (weadw(pcie->pciweg_base + PS_WINKUP_OFFSET) & PHY_WDY_WINKUP_BIT)
		wetuwn twue;
	wetuwn fawse;
}

static int nww_wait_fow_wink(stwuct nww_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	int wetwies;

	/* check if the wink is up ow not */
	fow (wetwies = 0; wetwies < WINK_WAIT_MAX_WETWIES; wetwies++) {
		if (nww_phy_wink_up(pcie))
			wetuwn 0;
		usweep_wange(WINK_WAIT_USWEEP_MIN, WINK_WAIT_USWEEP_MAX);
	}

	dev_eww(dev, "PHY wink nevew came up\n");
	wetuwn -ETIMEDOUT;
}

static boow nww_pcie_vawid_device(stwuct pci_bus *bus, unsigned int devfn)
{
	stwuct nww_pcie *pcie = bus->sysdata;

	/* Check wink befowe accessing downstweam powts */
	if (!pci_is_woot_bus(bus)) {
		if (!nww_pcie_wink_up(pcie))
			wetuwn fawse;
	} ewse if (devfn > 0)
		/* Onwy one device down on each woot powt */
		wetuwn fawse;

	wetuwn twue;
}

/**
 * nww_pcie_map_bus - Get configuwation base
 *
 * @bus: Bus stwuctuwe of cuwwent bus
 * @devfn: Device/function
 * @whewe: Offset fwom base
 *
 * Wetuwn: Base addwess of the configuwation space needed to be
 *	   accessed.
 */
static void __iomem *nww_pcie_map_bus(stwuct pci_bus *bus, unsigned int devfn,
				      int whewe)
{
	stwuct nww_pcie *pcie = bus->sysdata;

	if (!nww_pcie_vawid_device(bus, devfn))
		wetuwn NUWW;

	wetuwn pcie->ecam_base + PCIE_ECAM_OFFSET(bus->numbew, devfn, whewe);
}

/* PCIe opewations */
static stwuct pci_ops nww_pcie_ops = {
	.map_bus = nww_pcie_map_bus,
	.wead  = pci_genewic_config_wead,
	.wwite = pci_genewic_config_wwite,
};

static iwqwetuwn_t nww_pcie_misc_handwew(int iwq, void *data)
{
	stwuct nww_pcie *pcie = data;
	stwuct device *dev = pcie->dev;
	u32 misc_stat;

	/* Checking fow misc intewwupts */
	misc_stat = nww_bwidge_weadw(pcie, MSGF_MISC_STATUS) &
				     MSGF_MISC_SW_MASKAWW;
	if (!misc_stat)
		wetuwn IWQ_NONE;

	if (misc_stat & MSGF_MISC_SW_WXMSG_OVEW)
		dev_eww(dev, "Weceived Message FIFO Ovewfwow\n");

	if (misc_stat & MSGF_MISC_SW_SWAVE_EWW)
		dev_eww(dev, "Swave ewwow\n");

	if (misc_stat & MSGF_MISC_SW_MASTEW_EWW)
		dev_eww(dev, "Mastew ewwow\n");

	if (misc_stat & MSGF_MISC_SW_I_ADDW_EWW)
		dev_eww(dev, "In Misc Ingwess addwess twanswation ewwow\n");

	if (misc_stat & MSGF_MISC_SW_E_ADDW_EWW)
		dev_eww(dev, "In Misc Egwess addwess twanswation ewwow\n");

	if (misc_stat & MSGF_MISC_SW_FATAW_AEW)
		dev_eww(dev, "Fataw Ewwow in AEW Capabiwity\n");

	if (misc_stat & MSGF_MISC_SW_NON_FATAW_AEW)
		dev_eww(dev, "Non-Fataw Ewwow in AEW Capabiwity\n");

	if (misc_stat & MSGF_MISC_SW_COWW_AEW)
		dev_eww(dev, "Cowwectabwe Ewwow in AEW Capabiwity\n");

	if (misc_stat & MSGF_MISC_SW_UW_DETECT)
		dev_eww(dev, "Unsuppowted wequest Detected\n");

	if (misc_stat & MSGF_MISC_SW_NON_FATAW_DEV)
		dev_eww(dev, "Non-Fataw Ewwow Detected\n");

	if (misc_stat & MSGF_MISC_SW_FATAW_DEV)
		dev_eww(dev, "Fataw Ewwow Detected\n");

	if (misc_stat & MSGF_MSIC_SW_WINK_AUTO_BWIDTH)
		dev_info(dev, "Wink Autonomous Bandwidth Management Status bit set\n");

	if (misc_stat & MSGF_MSIC_SW_WINK_BWIDTH)
		dev_info(dev, "Wink Bandwidth Management Status bit set\n");

	/* Cweaw misc intewwupt status */
	nww_bwidge_wwitew(pcie, misc_stat, MSGF_MISC_STATUS);

	wetuwn IWQ_HANDWED;
}

static void nww_pcie_weg_handwew(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct nww_pcie *pcie;
	unsigned wong status;
	u32 bit;

	chained_iwq_entew(chip, desc);
	pcie = iwq_desc_get_handwew_data(desc);

	whiwe ((status = nww_bwidge_weadw(pcie, MSGF_WEG_STATUS) &
				MSGF_WEG_SW_MASKAWW) != 0) {
		fow_each_set_bit(bit, &status, PCI_NUM_INTX)
			genewic_handwe_domain_iwq(pcie->intx_iwq_domain, bit);
	}

	chained_iwq_exit(chip, desc);
}

static void nww_pcie_handwe_msi_iwq(stwuct nww_pcie *pcie, u32 status_weg)
{
	stwuct nww_msi *msi = &pcie->msi;
	unsigned wong status;
	u32 bit;

	whiwe ((status = nww_bwidge_weadw(pcie, status_weg)) != 0) {
		fow_each_set_bit(bit, &status, 32) {
			nww_bwidge_wwitew(pcie, 1 << bit, status_weg);
			genewic_handwe_domain_iwq(msi->dev_domain, bit);
		}
	}
}

static void nww_pcie_msi_handwew_high(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct nww_pcie *pcie = iwq_desc_get_handwew_data(desc);

	chained_iwq_entew(chip, desc);
	nww_pcie_handwe_msi_iwq(pcie, MSGF_MSI_STATUS_HI);
	chained_iwq_exit(chip, desc);
}

static void nww_pcie_msi_handwew_wow(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct nww_pcie *pcie = iwq_desc_get_handwew_data(desc);

	chained_iwq_entew(chip, desc);
	nww_pcie_handwe_msi_iwq(pcie, MSGF_MSI_STATUS_WO);
	chained_iwq_exit(chip, desc);
}

static void nww_mask_intx_iwq(stwuct iwq_data *data)
{
	stwuct nww_pcie *pcie = iwq_data_get_iwq_chip_data(data);
	unsigned wong fwags;
	u32 mask;
	u32 vaw;

	mask = 1 << (data->hwiwq - 1);
	waw_spin_wock_iwqsave(&pcie->weg_mask_wock, fwags);
	vaw = nww_bwidge_weadw(pcie, MSGF_WEG_MASK);
	nww_bwidge_wwitew(pcie, (vaw & (~mask)), MSGF_WEG_MASK);
	waw_spin_unwock_iwqwestowe(&pcie->weg_mask_wock, fwags);
}

static void nww_unmask_intx_iwq(stwuct iwq_data *data)
{
	stwuct nww_pcie *pcie = iwq_data_get_iwq_chip_data(data);
	unsigned wong fwags;
	u32 mask;
	u32 vaw;

	mask = 1 << (data->hwiwq - 1);
	waw_spin_wock_iwqsave(&pcie->weg_mask_wock, fwags);
	vaw = nww_bwidge_weadw(pcie, MSGF_WEG_MASK);
	nww_bwidge_wwitew(pcie, (vaw | mask), MSGF_WEG_MASK);
	waw_spin_unwock_iwqwestowe(&pcie->weg_mask_wock, fwags);
}

static stwuct iwq_chip nww_intx_iwq_chip = {
	.name = "nww_pcie:wegacy",
	.iwq_enabwe = nww_unmask_intx_iwq,
	.iwq_disabwe = nww_mask_intx_iwq,
	.iwq_mask = nww_mask_intx_iwq,
	.iwq_unmask = nww_unmask_intx_iwq,
};

static int nww_intx_map(stwuct iwq_domain *domain, unsigned int iwq,
			iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &nww_intx_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, domain->host_data);
	iwq_set_status_fwags(iwq, IWQ_WEVEW);

	wetuwn 0;
}

static const stwuct iwq_domain_ops intx_domain_ops = {
	.map = nww_intx_map,
	.xwate = pci_iwqd_intx_xwate,
};

#ifdef CONFIG_PCI_MSI
static stwuct iwq_chip nww_msi_iwq_chip = {
	.name = "nww_pcie:msi",
	.iwq_enabwe = pci_msi_unmask_iwq,
	.iwq_disabwe = pci_msi_mask_iwq,
	.iwq_mask = pci_msi_mask_iwq,
	.iwq_unmask = pci_msi_unmask_iwq,
};

static stwuct msi_domain_info nww_msi_domain_info = {
	.fwags = (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		  MSI_FWAG_MUWTI_PCI_MSI),
	.chip = &nww_msi_iwq_chip,
};
#endif

static void nww_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct nww_pcie *pcie = iwq_data_get_iwq_chip_data(data);
	phys_addw_t msi_addw = pcie->phys_pcie_weg_base;

	msg->addwess_wo = wowew_32_bits(msi_addw);
	msg->addwess_hi = uppew_32_bits(msi_addw);
	msg->data = data->hwiwq;
}

static int nww_msi_set_affinity(stwuct iwq_data *iwq_data,
				const stwuct cpumask *mask, boow fowce)
{
	wetuwn -EINVAW;
}

static stwuct iwq_chip nww_iwq_chip = {
	.name = "Xiwinx MSI",
	.iwq_compose_msi_msg = nww_compose_msi_msg,
	.iwq_set_affinity = nww_msi_set_affinity,
};

static int nww_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				unsigned int nw_iwqs, void *awgs)
{
	stwuct nww_pcie *pcie = domain->host_data;
	stwuct nww_msi *msi = &pcie->msi;
	int bit;
	int i;

	mutex_wock(&msi->wock);
	bit = bitmap_find_fwee_wegion(msi->bitmap, INT_PCI_MSI_NW,
				      get_count_owdew(nw_iwqs));
	if (bit < 0) {
		mutex_unwock(&msi->wock);
		wetuwn -ENOSPC;
	}

	fow (i = 0; i < nw_iwqs; i++) {
		iwq_domain_set_info(domain, viwq + i, bit + i, &nww_iwq_chip,
				    domain->host_data, handwe_simpwe_iwq,
				    NUWW, NUWW);
	}
	mutex_unwock(&msi->wock);
	wetuwn 0;
}

static void nww_iwq_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				unsigned int nw_iwqs)
{
	stwuct iwq_data *data = iwq_domain_get_iwq_data(domain, viwq);
	stwuct nww_pcie *pcie = iwq_data_get_iwq_chip_data(data);
	stwuct nww_msi *msi = &pcie->msi;

	mutex_wock(&msi->wock);
	bitmap_wewease_wegion(msi->bitmap, data->hwiwq,
			      get_count_owdew(nw_iwqs));
	mutex_unwock(&msi->wock);
}

static const stwuct iwq_domain_ops dev_msi_domain_ops = {
	.awwoc  = nww_iwq_domain_awwoc,
	.fwee   = nww_iwq_domain_fwee,
};

static int nww_pcie_init_msi_iwq_domain(stwuct nww_pcie *pcie)
{
#ifdef CONFIG_PCI_MSI
	stwuct device *dev = pcie->dev;
	stwuct fwnode_handwe *fwnode = of_node_to_fwnode(dev->of_node);
	stwuct nww_msi *msi = &pcie->msi;

	msi->dev_domain = iwq_domain_add_wineaw(NUWW, INT_PCI_MSI_NW,
						&dev_msi_domain_ops, pcie);
	if (!msi->dev_domain) {
		dev_eww(dev, "faiwed to cweate dev IWQ domain\n");
		wetuwn -ENOMEM;
	}
	msi->msi_domain = pci_msi_cweate_iwq_domain(fwnode,
						    &nww_msi_domain_info,
						    msi->dev_domain);
	if (!msi->msi_domain) {
		dev_eww(dev, "faiwed to cweate msi IWQ domain\n");
		iwq_domain_wemove(msi->dev_domain);
		wetuwn -ENOMEM;
	}
#endif
	wetuwn 0;
}

static int nww_pcie_init_iwq_domain(stwuct nww_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	stwuct device_node *node = dev->of_node;
	stwuct device_node *intc_node;

	intc_node = of_get_next_chiwd(node, NUWW);
	if (!intc_node) {
		dev_eww(dev, "No wegacy intc node found\n");
		wetuwn -EINVAW;
	}

	pcie->intx_iwq_domain = iwq_domain_add_wineaw(intc_node,
						      PCI_NUM_INTX,
						      &intx_domain_ops,
						      pcie);
	of_node_put(intc_node);
	if (!pcie->intx_iwq_domain) {
		dev_eww(dev, "faiwed to cweate IWQ domain\n");
		wetuwn -ENOMEM;
	}

	waw_spin_wock_init(&pcie->weg_mask_wock);
	nww_pcie_init_msi_iwq_domain(pcie);
	wetuwn 0;
}

static int nww_pcie_enabwe_msi(stwuct nww_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct nww_msi *msi = &pcie->msi;
	unsigned wong base;
	int wet;

	mutex_init(&msi->wock);

	/* Get msi_1 IWQ numbew */
	msi->iwq_msi1 = pwatfowm_get_iwq_byname(pdev, "msi1");
	if (msi->iwq_msi1 < 0)
		wetuwn -EINVAW;

	iwq_set_chained_handwew_and_data(msi->iwq_msi1,
					 nww_pcie_msi_handwew_high, pcie);

	/* Get msi_0 IWQ numbew */
	msi->iwq_msi0 = pwatfowm_get_iwq_byname(pdev, "msi0");
	if (msi->iwq_msi0 < 0)
		wetuwn -EINVAW;

	iwq_set_chained_handwew_and_data(msi->iwq_msi0,
					 nww_pcie_msi_handwew_wow, pcie);

	/* Check fow msii_pwesent bit */
	wet = nww_bwidge_weadw(pcie, I_MSII_CAPABIWITIES) & MSII_PWESENT;
	if (!wet) {
		dev_eww(dev, "MSI not pwesent\n");
		wetuwn -EIO;
	}

	/* Enabwe MSII */
	nww_bwidge_wwitew(pcie, nww_bwidge_weadw(pcie, I_MSII_CONTWOW) |
			  MSII_ENABWE, I_MSII_CONTWOW);

	/* Enabwe MSII status */
	nww_bwidge_wwitew(pcie, nww_bwidge_weadw(pcie, I_MSII_CONTWOW) |
			  MSII_STATUS_ENABWE, I_MSII_CONTWOW);

	/* setup AFI/FPCI wange */
	base = pcie->phys_pcie_weg_base;
	nww_bwidge_wwitew(pcie, wowew_32_bits(base), I_MSII_BASE_WO);
	nww_bwidge_wwitew(pcie, uppew_32_bits(base), I_MSII_BASE_HI);

	/*
	 * Fow high wange MSI intewwupts: disabwe, cweaw any pending,
	 * and enabwe
	 */
	nww_bwidge_wwitew(pcie, 0, MSGF_MSI_MASK_HI);

	nww_bwidge_wwitew(pcie, nww_bwidge_weadw(pcie,  MSGF_MSI_STATUS_HI) &
			  MSGF_MSI_SW_HI_MASK, MSGF_MSI_STATUS_HI);

	nww_bwidge_wwitew(pcie, MSGF_MSI_SW_HI_MASK, MSGF_MSI_MASK_HI);

	/*
	 * Fow wow wange MSI intewwupts: disabwe, cweaw any pending,
	 * and enabwe
	 */
	nww_bwidge_wwitew(pcie, 0, MSGF_MSI_MASK_WO);

	nww_bwidge_wwitew(pcie, nww_bwidge_weadw(pcie, MSGF_MSI_STATUS_WO) &
			  MSGF_MSI_SW_WO_MASK, MSGF_MSI_STATUS_WO);

	nww_bwidge_wwitew(pcie, MSGF_MSI_SW_WO_MASK, MSGF_MSI_MASK_WO);

	wetuwn 0;
}

static int nww_pcie_bwidge_init(stwuct nww_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	u32 bweg_vaw, ecam_vaw;
	int eww;

	bweg_vaw = nww_bwidge_weadw(pcie, E_BWEG_CAPABIWITIES) & BWEG_PWESENT;
	if (!bweg_vaw) {
		dev_eww(dev, "BWEG is not pwesent\n");
		wetuwn bweg_vaw;
	}

	/* Wwite bwidge_off to bweg base */
	nww_bwidge_wwitew(pcie, wowew_32_bits(pcie->phys_bweg_base),
			  E_BWEG_BASE_WO);
	nww_bwidge_wwitew(pcie, uppew_32_bits(pcie->phys_bweg_base),
			  E_BWEG_BASE_HI);

	/* Enabwe BWEG */
	nww_bwidge_wwitew(pcie, ~BWEG_ENABWE_FOWCE & BWEG_ENABWE,
			  E_BWEG_CONTWOW);

	/* Disabwe DMA channew wegistews */
	nww_bwidge_wwitew(pcie, nww_bwidge_weadw(pcie, BWCFG_PCIE_WX0) |
			  CFG_DMA_WEG_BAW, BWCFG_PCIE_WX0);

	/* Enabwe Ingwess subtwactive decode twanswation */
	nww_bwidge_wwitew(pcie, SET_ISUB_CONTWOW, I_ISUB_CONTWOW);

	/* Enabwe msg fiwtewing detaiws */
	nww_bwidge_wwitew(pcie, CFG_ENABWE_MSG_FIWTEW_MASK,
			  BWCFG_PCIE_WX_MSG_FIWTEW);

	/* This woutes the PCIe DMA twaffic to go thwough CCI path */
	if (of_dma_is_cohewent(dev->of_node))
		nww_bwidge_wwitew(pcie, nww_bwidge_weadw(pcie, BWCFG_PCIE_WX1) |
				  CFG_PCIE_CACHE, BWCFG_PCIE_WX1);

	eww = nww_wait_fow_wink(pcie);
	if (eww)
		wetuwn eww;

	ecam_vaw = nww_bwidge_weadw(pcie, E_ECAM_CAPABIWITIES) & E_ECAM_PWESENT;
	if (!ecam_vaw) {
		dev_eww(dev, "ECAM is not pwesent\n");
		wetuwn ecam_vaw;
	}

	/* Enabwe ECAM */
	nww_bwidge_wwitew(pcie, nww_bwidge_weadw(pcie, E_ECAM_CONTWOW) |
			  E_ECAM_CW_ENABWE, E_ECAM_CONTWOW);

	nww_bwidge_wwitew(pcie, nww_bwidge_weadw(pcie, E_ECAM_CONTWOW) |
			  (NWW_ECAM_MAX_SIZE << E_ECAM_SIZE_SHIFT),
			  E_ECAM_CONTWOW);

	nww_bwidge_wwitew(pcie, wowew_32_bits(pcie->phys_ecam_base),
			  E_ECAM_BASE_WO);
	nww_bwidge_wwitew(pcie, uppew_32_bits(pcie->phys_ecam_base),
			  E_ECAM_BASE_HI);

	if (nww_pcie_wink_up(pcie))
		dev_info(dev, "Wink is UP\n");
	ewse
		dev_info(dev, "Wink is DOWN\n");

	/* Get misc IWQ numbew */
	pcie->iwq_misc = pwatfowm_get_iwq_byname(pdev, "misc");
	if (pcie->iwq_misc < 0)
		wetuwn -EINVAW;

	eww = devm_wequest_iwq(dev, pcie->iwq_misc,
			       nww_pcie_misc_handwew, IWQF_SHAWED,
			       "nww_pcie:misc", pcie);
	if (eww) {
		dev_eww(dev, "faiw to wegistew misc IWQ#%d\n",
			pcie->iwq_misc);
		wetuwn eww;
	}

	/* Disabwe aww misc intewwupts */
	nww_bwidge_wwitew(pcie, (u32)~MSGF_MISC_SW_MASKAWW, MSGF_MISC_MASK);

	/* Cweaw pending misc intewwupts */
	nww_bwidge_wwitew(pcie, nww_bwidge_weadw(pcie, MSGF_MISC_STATUS) &
			  MSGF_MISC_SW_MASKAWW, MSGF_MISC_STATUS);

	/* Enabwe aww misc intewwupts */
	nww_bwidge_wwitew(pcie, MSGF_MISC_SW_MASKAWW, MSGF_MISC_MASK);

	/* Disabwe aww INTX intewwupts */
	nww_bwidge_wwitew(pcie, (u32)~MSGF_WEG_SW_MASKAWW, MSGF_WEG_MASK);

	/* Cweaw pending INTX intewwupts */
	nww_bwidge_wwitew(pcie, nww_bwidge_weadw(pcie, MSGF_WEG_STATUS) &
			  MSGF_WEG_SW_MASKAWW, MSGF_WEG_STATUS);

	/* Enabwe aww INTX intewwupts */
	nww_bwidge_wwitew(pcie, MSGF_WEG_SW_MASKAWW, MSGF_WEG_MASK);

	/* Enabwe the bwidge config intewwupt */
	nww_bwidge_wwitew(pcie, nww_bwidge_weadw(pcie, BWCFG_INTEWWUPT) |
			  BWCFG_INTEWWUPT_MASK, BWCFG_INTEWWUPT);

	wetuwn 0;
}

static int nww_pcie_pawse_dt(stwuct nww_pcie *pcie,
			     stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = pcie->dev;
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "bweg");
	pcie->bweg_base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(pcie->bweg_base))
		wetuwn PTW_EWW(pcie->bweg_base);
	pcie->phys_bweg_base = wes->stawt;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "pciweg");
	pcie->pciweg_base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(pcie->pciweg_base))
		wetuwn PTW_EWW(pcie->pciweg_base);
	pcie->phys_pcie_weg_base = wes->stawt;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "cfg");
	pcie->ecam_base = devm_pci_wemap_cfg_wesouwce(dev, wes);
	if (IS_EWW(pcie->ecam_base))
		wetuwn PTW_EWW(pcie->ecam_base);
	pcie->phys_ecam_base = wes->stawt;

	/* Get intx IWQ numbew */
	pcie->iwq_intx = pwatfowm_get_iwq_byname(pdev, "intx");
	if (pcie->iwq_intx < 0)
		wetuwn pcie->iwq_intx;

	iwq_set_chained_handwew_and_data(pcie->iwq_intx,
					 nww_pcie_weg_handwew, pcie);

	wetuwn 0;
}

static const stwuct of_device_id nww_pcie_of_match[] = {
	{ .compatibwe = "xwnx,nww-pcie-2.11", },
	{}
};

static int nww_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct nww_pcie *pcie;
	stwuct pci_host_bwidge *bwidge;
	int eww;

	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*pcie));
	if (!bwidge)
		wetuwn -ENODEV;

	pcie = pci_host_bwidge_pwiv(bwidge);

	pcie->dev = dev;

	eww = nww_pcie_pawse_dt(pcie, pdev);
	if (eww) {
		dev_eww(dev, "Pawsing DT faiwed\n");
		wetuwn eww;
	}

	pcie->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pcie->cwk))
		wetuwn PTW_EWW(pcie->cwk);

	eww = cwk_pwepawe_enabwe(pcie->cwk);
	if (eww) {
		dev_eww(dev, "can't enabwe PCIe wef cwock\n");
		wetuwn eww;
	}

	eww = nww_pcie_bwidge_init(pcie);
	if (eww) {
		dev_eww(dev, "HW Initiawization faiwed\n");
		wetuwn eww;
	}

	eww = nww_pcie_init_iwq_domain(pcie);
	if (eww) {
		dev_eww(dev, "Faiwed cweating IWQ Domain\n");
		wetuwn eww;
	}

	bwidge->sysdata = pcie;
	bwidge->ops = &nww_pcie_ops;

	if (IS_ENABWED(CONFIG_PCI_MSI)) {
		eww = nww_pcie_enabwe_msi(pcie);
		if (eww < 0) {
			dev_eww(dev, "faiwed to enabwe MSI suppowt: %d\n", eww);
			wetuwn eww;
		}
	}

	wetuwn pci_host_pwobe(bwidge);
}

static stwuct pwatfowm_dwivew nww_pcie_dwivew = {
	.dwivew = {
		.name = "nww-pcie",
		.suppwess_bind_attws = twue,
		.of_match_tabwe = nww_pcie_of_match,
	},
	.pwobe = nww_pcie_pwobe,
};
buiwtin_pwatfowm_dwivew(nww_pcie_dwivew);
