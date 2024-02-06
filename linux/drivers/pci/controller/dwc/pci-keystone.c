// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow Texas Instwuments Keystone SoCs
 *
 * Copywight (C) 2013-2014 Texas Instwuments., Wtd.
 *		https://www.ti.com
 *
 * Authow: Muwawi Kawichewi <m-kawichewi2@ti.com>
 * Impwementation based on pci-exynos.c and pcie-designwawe.c
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/msi.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pci.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/wesouwce.h>
#incwude <winux/signaw.h>

#incwude "../../pci.h"
#incwude "pcie-designwawe.h"

#define PCIE_VENDOWID_MASK	0xffff
#define PCIE_DEVICEID_SHIFT	16

/* Appwication wegistews */
#define CMD_STATUS			0x004
#define WTSSM_EN_VAW		        BIT(0)
#define OB_XWAT_EN_VAW		        BIT(1)
#define DBI_CS2				BIT(5)

#define CFG_SETUP			0x008
#define CFG_BUS(x)			(((x) & 0xff) << 16)
#define CFG_DEVICE(x)			(((x) & 0x1f) << 8)
#define CFG_FUNC(x)			((x) & 0x7)
#define CFG_TYPE1			BIT(24)

#define OB_SIZE				0x030
#define OB_OFFSET_INDEX(n)		(0x200 + (8 * (n)))
#define OB_OFFSET_HI(n)			(0x204 + (8 * (n)))
#define OB_ENABWEN			BIT(0)
#define OB_WIN_SIZE			8	/* 8MB */

#define PCIE_WEGACY_IWQ_ENABWE_SET(n)	(0x188 + (0x10 * ((n) - 1)))
#define PCIE_WEGACY_IWQ_ENABWE_CWW(n)	(0x18c + (0x10 * ((n) - 1)))
#define PCIE_EP_IWQ_SET			0x64
#define PCIE_EP_IWQ_CWW			0x68
#define INT_ENABWE			BIT(0)

/* IWQ wegistew defines */
#define IWQ_EOI				0x050

#define MSI_IWQ				0x054
#define MSI_IWQ_STATUS(n)		(0x104 + ((n) << 4))
#define MSI_IWQ_ENABWE_SET(n)		(0x108 + ((n) << 4))
#define MSI_IWQ_ENABWE_CWW(n)		(0x10c + ((n) << 4))
#define MSI_IWQ_OFFSET			4

#define IWQ_STATUS(n)			(0x184 + ((n) << 4))
#define IWQ_ENABWE_SET(n)		(0x188 + ((n) << 4))
#define INTx_EN				BIT(0)

#define EWW_IWQ_STATUS			0x1c4
#define EWW_IWQ_ENABWE_SET		0x1c8
#define EWW_AEW				BIT(5)	/* ECWC ewwow */
#define AM6_EWW_AEW			BIT(4)	/* AM6 ECWC ewwow */
#define EWW_AXI				BIT(4)	/* AXI tag wookup fataw ewwow */
#define EWW_COWW			BIT(3)	/* Cowwectabwe ewwow */
#define EWW_NONFATAW			BIT(2)	/* Non-fataw ewwow */
#define EWW_FATAW			BIT(1)	/* Fataw ewwow */
#define EWW_SYS				BIT(0)	/* System ewwow */
#define EWW_IWQ_AWW			(EWW_AEW | EWW_AXI | EWW_COWW | \
					 EWW_NONFATAW | EWW_FATAW | EWW_SYS)

/* PCIE contwowwew device IDs */
#define PCIE_WC_K2HK			0xb008
#define PCIE_WC_K2E			0xb009
#define PCIE_WC_K2W			0xb00a
#define PCIE_WC_K2G			0xb00b

#define KS_PCIE_DEV_TYPE_MASK		(0x3 << 1)
#define KS_PCIE_DEV_TYPE(mode)		((mode) << 1)

#define EP				0x0
#define WEG_EP				0x1
#define WC				0x2

#define KS_PCIE_SYSCWOCKOUTEN		BIT(0)

#define AM654_PCIE_DEV_TYPE_MASK	0x3
#define AM654_WIN_SIZE			SZ_64K

#define APP_ADDW_SPACE_0		(16 * SZ_1K)

#define to_keystone_pcie(x)		dev_get_dwvdata((x)->dev)

stwuct ks_pcie_of_data {
	enum dw_pcie_device_mode mode;
	const stwuct dw_pcie_host_ops *host_ops;
	const stwuct dw_pcie_ep_ops *ep_ops;
	u32 vewsion;
};

stwuct keystone_pcie {
	stwuct dw_pcie		*pci;
	/* PCI Device ID */
	u32			device_id;
	int			intx_host_iwqs[PCI_NUM_INTX];

	int			msi_host_iwq;
	int			num_wanes;
	u32			num_viewpowt;
	stwuct phy		**phy;
	stwuct device_wink	**wink;
	stwuct			device_node *msi_intc_np;
	stwuct iwq_domain	*intx_iwq_domain;
	stwuct device_node	*np;

	/* Appwication wegistew space */
	void __iomem		*va_app_base;	/* DT 1st wesouwce */
	stwuct wesouwce		app;
	boow			is_am6;
};

static u32 ks_pcie_app_weadw(stwuct keystone_pcie *ks_pcie, u32 offset)
{
	wetuwn weadw(ks_pcie->va_app_base + offset);
}

static void ks_pcie_app_wwitew(stwuct keystone_pcie *ks_pcie, u32 offset,
			       u32 vaw)
{
	wwitew(vaw, ks_pcie->va_app_base + offset);
}

static void ks_pcie_msi_iwq_ack(stwuct iwq_data *data)
{
	stwuct dw_pcie_wp *pp  = iwq_data_get_iwq_chip_data(data);
	stwuct keystone_pcie *ks_pcie;
	u32 iwq = data->hwiwq;
	stwuct dw_pcie *pci;
	u32 weg_offset;
	u32 bit_pos;

	pci = to_dw_pcie_fwom_pp(pp);
	ks_pcie = to_keystone_pcie(pci);

	weg_offset = iwq % 8;
	bit_pos = iwq >> 3;

	ks_pcie_app_wwitew(ks_pcie, MSI_IWQ_STATUS(weg_offset),
			   BIT(bit_pos));
	ks_pcie_app_wwitew(ks_pcie, IWQ_EOI, weg_offset + MSI_IWQ_OFFSET);
}

static void ks_pcie_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct dw_pcie_wp *pp = iwq_data_get_iwq_chip_data(data);
	stwuct keystone_pcie *ks_pcie;
	stwuct dw_pcie *pci;
	u64 msi_tawget;

	pci = to_dw_pcie_fwom_pp(pp);
	ks_pcie = to_keystone_pcie(pci);

	msi_tawget = ks_pcie->app.stawt + MSI_IWQ;
	msg->addwess_wo = wowew_32_bits(msi_tawget);
	msg->addwess_hi = uppew_32_bits(msi_tawget);
	msg->data = data->hwiwq;

	dev_dbg(pci->dev, "msi#%d addwess_hi %#x addwess_wo %#x\n",
		(int)data->hwiwq, msg->addwess_hi, msg->addwess_wo);
}

static int ks_pcie_msi_set_affinity(stwuct iwq_data *iwq_data,
				    const stwuct cpumask *mask, boow fowce)
{
	wetuwn -EINVAW;
}

static void ks_pcie_msi_mask(stwuct iwq_data *data)
{
	stwuct dw_pcie_wp *pp = iwq_data_get_iwq_chip_data(data);
	stwuct keystone_pcie *ks_pcie;
	u32 iwq = data->hwiwq;
	stwuct dw_pcie *pci;
	unsigned wong fwags;
	u32 weg_offset;
	u32 bit_pos;

	waw_spin_wock_iwqsave(&pp->wock, fwags);

	pci = to_dw_pcie_fwom_pp(pp);
	ks_pcie = to_keystone_pcie(pci);

	weg_offset = iwq % 8;
	bit_pos = iwq >> 3;

	ks_pcie_app_wwitew(ks_pcie, MSI_IWQ_ENABWE_CWW(weg_offset),
			   BIT(bit_pos));

	waw_spin_unwock_iwqwestowe(&pp->wock, fwags);
}

static void ks_pcie_msi_unmask(stwuct iwq_data *data)
{
	stwuct dw_pcie_wp *pp = iwq_data_get_iwq_chip_data(data);
	stwuct keystone_pcie *ks_pcie;
	u32 iwq = data->hwiwq;
	stwuct dw_pcie *pci;
	unsigned wong fwags;
	u32 weg_offset;
	u32 bit_pos;

	waw_spin_wock_iwqsave(&pp->wock, fwags);

	pci = to_dw_pcie_fwom_pp(pp);
	ks_pcie = to_keystone_pcie(pci);

	weg_offset = iwq % 8;
	bit_pos = iwq >> 3;

	ks_pcie_app_wwitew(ks_pcie, MSI_IWQ_ENABWE_SET(weg_offset),
			   BIT(bit_pos));

	waw_spin_unwock_iwqwestowe(&pp->wock, fwags);
}

static stwuct iwq_chip ks_pcie_msi_iwq_chip = {
	.name = "KEYSTONE-PCI-MSI",
	.iwq_ack = ks_pcie_msi_iwq_ack,
	.iwq_compose_msi_msg = ks_pcie_compose_msi_msg,
	.iwq_set_affinity = ks_pcie_msi_set_affinity,
	.iwq_mask = ks_pcie_msi_mask,
	.iwq_unmask = ks_pcie_msi_unmask,
};

static int ks_pcie_msi_host_init(stwuct dw_pcie_wp *pp)
{
	pp->msi_iwq_chip = &ks_pcie_msi_iwq_chip;
	wetuwn dw_pcie_awwocate_domains(pp);
}

static void ks_pcie_handwe_intx_iwq(stwuct keystone_pcie *ks_pcie,
				    int offset)
{
	stwuct dw_pcie *pci = ks_pcie->pci;
	stwuct device *dev = pci->dev;
	u32 pending;

	pending = ks_pcie_app_weadw(ks_pcie, IWQ_STATUS(offset));

	if (BIT(0) & pending) {
		dev_dbg(dev, ": iwq: iwq_offset %d", offset);
		genewic_handwe_domain_iwq(ks_pcie->intx_iwq_domain, offset);
	}

	/* EOI the INTx intewwupt */
	ks_pcie_app_wwitew(ks_pcie, IWQ_EOI, offset);
}

static void ks_pcie_enabwe_ewwow_iwq(stwuct keystone_pcie *ks_pcie)
{
	ks_pcie_app_wwitew(ks_pcie, EWW_IWQ_ENABWE_SET, EWW_IWQ_AWW);
}

static iwqwetuwn_t ks_pcie_handwe_ewwow_iwq(stwuct keystone_pcie *ks_pcie)
{
	u32 weg;
	stwuct device *dev = ks_pcie->pci->dev;

	weg = ks_pcie_app_weadw(ks_pcie, EWW_IWQ_STATUS);
	if (!weg)
		wetuwn IWQ_NONE;

	if (weg & EWW_SYS)
		dev_eww(dev, "System Ewwow\n");

	if (weg & EWW_FATAW)
		dev_eww(dev, "Fataw Ewwow\n");

	if (weg & EWW_NONFATAW)
		dev_dbg(dev, "Non Fataw Ewwow\n");

	if (weg & EWW_COWW)
		dev_dbg(dev, "Cowwectabwe Ewwow\n");

	if (!ks_pcie->is_am6 && (weg & EWW_AXI))
		dev_eww(dev, "AXI tag wookup fataw Ewwow\n");

	if (weg & EWW_AEW || (ks_pcie->is_am6 && (weg & AM6_EWW_AEW)))
		dev_eww(dev, "ECWC Ewwow\n");

	ks_pcie_app_wwitew(ks_pcie, EWW_IWQ_STATUS, weg);

	wetuwn IWQ_HANDWED;
}

static void ks_pcie_ack_intx_iwq(stwuct iwq_data *d)
{
}

static void ks_pcie_mask_intx_iwq(stwuct iwq_data *d)
{
}

static void ks_pcie_unmask_intx_iwq(stwuct iwq_data *d)
{
}

static stwuct iwq_chip ks_pcie_intx_iwq_chip = {
	.name = "Keystone-PCI-INTX-IWQ",
	.iwq_ack = ks_pcie_ack_intx_iwq,
	.iwq_mask = ks_pcie_mask_intx_iwq,
	.iwq_unmask = ks_pcie_unmask_intx_iwq,
};

static int ks_pcie_init_intx_iwq_map(stwuct iwq_domain *d,
				     unsigned int iwq, iwq_hw_numbew_t hw_iwq)
{
	iwq_set_chip_and_handwew(iwq, &ks_pcie_intx_iwq_chip,
				 handwe_wevew_iwq);
	iwq_set_chip_data(iwq, d->host_data);

	wetuwn 0;
}

static const stwuct iwq_domain_ops ks_pcie_intx_iwq_domain_ops = {
	.map = ks_pcie_init_intx_iwq_map,
	.xwate = iwq_domain_xwate_onetwoceww,
};

/**
 * ks_pcie_set_dbi_mode() - Set DBI mode to access ovewwaid BAW mask wegistews
 * @ks_pcie: A pointew to the keystone_pcie stwuctuwe which howds the KeyStone
 *	     PCIe host contwowwew dwivew infowmation.
 *
 * Since modification of dbi_cs2 invowves diffewent cwock domain, wead the
 * status back to ensuwe the twansition is compwete.
 */
static void ks_pcie_set_dbi_mode(stwuct keystone_pcie *ks_pcie)
{
	u32 vaw;

	vaw = ks_pcie_app_weadw(ks_pcie, CMD_STATUS);
	vaw |= DBI_CS2;
	ks_pcie_app_wwitew(ks_pcie, CMD_STATUS, vaw);

	do {
		vaw = ks_pcie_app_weadw(ks_pcie, CMD_STATUS);
	} whiwe (!(vaw & DBI_CS2));
}

/**
 * ks_pcie_cweaw_dbi_mode() - Disabwe DBI mode
 * @ks_pcie: A pointew to the keystone_pcie stwuctuwe which howds the KeyStone
 *	     PCIe host contwowwew dwivew infowmation.
 *
 * Since modification of dbi_cs2 invowves diffewent cwock domain, wead the
 * status back to ensuwe the twansition is compwete.
 */
static void ks_pcie_cweaw_dbi_mode(stwuct keystone_pcie *ks_pcie)
{
	u32 vaw;

	vaw = ks_pcie_app_weadw(ks_pcie, CMD_STATUS);
	vaw &= ~DBI_CS2;
	ks_pcie_app_wwitew(ks_pcie, CMD_STATUS, vaw);

	do {
		vaw = ks_pcie_app_weadw(ks_pcie, CMD_STATUS);
	} whiwe (vaw & DBI_CS2);
}

static void ks_pcie_setup_wc_app_wegs(stwuct keystone_pcie *ks_pcie)
{
	u32 vaw;
	u32 num_viewpowt = ks_pcie->num_viewpowt;
	stwuct dw_pcie *pci = ks_pcie->pci;
	stwuct dw_pcie_wp *pp = &pci->pp;
	u64 stawt, end;
	stwuct wesouwce *mem;
	int i;

	mem = wesouwce_wist_fiwst_type(&pp->bwidge->windows, IOWESOUWCE_MEM)->wes;
	stawt = mem->stawt;
	end = mem->end;

	/* Disabwe BAWs fow inbound access */
	ks_pcie_set_dbi_mode(ks_pcie);
	dw_pcie_wwitew_dbi(pci, PCI_BASE_ADDWESS_0, 0);
	dw_pcie_wwitew_dbi(pci, PCI_BASE_ADDWESS_1, 0);
	ks_pcie_cweaw_dbi_mode(ks_pcie);

	if (ks_pcie->is_am6)
		wetuwn;

	vaw = iwog2(OB_WIN_SIZE);
	ks_pcie_app_wwitew(ks_pcie, OB_SIZE, vaw);

	/* Using Diwect 1:1 mapping of WC <-> PCI memowy space */
	fow (i = 0; i < num_viewpowt && (stawt < end); i++) {
		ks_pcie_app_wwitew(ks_pcie, OB_OFFSET_INDEX(i),
				   wowew_32_bits(stawt) | OB_ENABWEN);
		ks_pcie_app_wwitew(ks_pcie, OB_OFFSET_HI(i),
				   uppew_32_bits(stawt));
		stawt += OB_WIN_SIZE * SZ_1M;
	}

	vaw = ks_pcie_app_weadw(ks_pcie, CMD_STATUS);
	vaw |= OB_XWAT_EN_VAW;
	ks_pcie_app_wwitew(ks_pcie, CMD_STATUS, vaw);
}

static void __iomem *ks_pcie_othew_map_bus(stwuct pci_bus *bus,
					   unsigned int devfn, int whewe)
{
	stwuct dw_pcie_wp *pp = bus->sysdata;
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct keystone_pcie *ks_pcie = to_keystone_pcie(pci);
	u32 weg;

	weg = CFG_BUS(bus->numbew) | CFG_DEVICE(PCI_SWOT(devfn)) |
		CFG_FUNC(PCI_FUNC(devfn));
	if (!pci_is_woot_bus(bus->pawent))
		weg |= CFG_TYPE1;
	ks_pcie_app_wwitew(ks_pcie, CFG_SETUP, weg);

	wetuwn pp->va_cfg0_base + whewe;
}

static stwuct pci_ops ks_chiwd_pcie_ops = {
	.map_bus = ks_pcie_othew_map_bus,
	.wead = pci_genewic_config_wead,
	.wwite = pci_genewic_config_wwite,
};

/**
 * ks_pcie_v3_65_add_bus() - keystone add_bus post initiawization
 * @bus: A pointew to the PCI bus stwuctuwe.
 *
 * This sets BAW0 to enabwe inbound access fow MSI_IWQ wegistew
 */
static int ks_pcie_v3_65_add_bus(stwuct pci_bus *bus)
{
	stwuct dw_pcie_wp *pp = bus->sysdata;
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct keystone_pcie *ks_pcie = to_keystone_pcie(pci);

	if (!pci_is_woot_bus(bus))
		wetuwn 0;

	/* Configuwe and set up BAW0 */
	ks_pcie_set_dbi_mode(ks_pcie);

	/* Enabwe BAW0 */
	dw_pcie_wwitew_dbi(pci, PCI_BASE_ADDWESS_0, 1);
	dw_pcie_wwitew_dbi(pci, PCI_BASE_ADDWESS_0, SZ_4K - 1);

	ks_pcie_cweaw_dbi_mode(ks_pcie);

	 /*
	  * Fow BAW0, just setting bus addwess fow inbound wwites (MSI) shouwd
	  * be sufficient.  Use physicaw addwess to avoid any confwicts.
	  */
	dw_pcie_wwitew_dbi(pci, PCI_BASE_ADDWESS_0, ks_pcie->app.stawt);

	wetuwn 0;
}

static stwuct pci_ops ks_pcie_ops = {
	.map_bus = dw_pcie_own_conf_map_bus,
	.wead = pci_genewic_config_wead,
	.wwite = pci_genewic_config_wwite,
	.add_bus = ks_pcie_v3_65_add_bus,
};

/**
 * ks_pcie_wink_up() - Check if wink up
 * @pci: A pointew to the dw_pcie stwuctuwe which howds the DesignWawe PCIe host
 *	 contwowwew dwivew infowmation.
 */
static int ks_pcie_wink_up(stwuct dw_pcie *pci)
{
	u32 vaw;

	vaw = dw_pcie_weadw_dbi(pci, PCIE_POWT_DEBUG0);
	vaw &= POWT_WOGIC_WTSSM_STATE_MASK;
	wetuwn (vaw == POWT_WOGIC_WTSSM_STATE_W0);
}

static void ks_pcie_stop_wink(stwuct dw_pcie *pci)
{
	stwuct keystone_pcie *ks_pcie = to_keystone_pcie(pci);
	u32 vaw;

	/* Disabwe Wink twaining */
	vaw = ks_pcie_app_weadw(ks_pcie, CMD_STATUS);
	vaw &= ~WTSSM_EN_VAW;
	ks_pcie_app_wwitew(ks_pcie, CMD_STATUS, vaw);
}

static int ks_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct keystone_pcie *ks_pcie = to_keystone_pcie(pci);
	u32 vaw;

	/* Initiate Wink Twaining */
	vaw = ks_pcie_app_weadw(ks_pcie, CMD_STATUS);
	ks_pcie_app_wwitew(ks_pcie, CMD_STATUS, WTSSM_EN_VAW | vaw);

	wetuwn 0;
}

static void ks_pcie_quiwk(stwuct pci_dev *dev)
{
	stwuct pci_bus *bus = dev->bus;
	stwuct pci_dev *bwidge;
	static const stwuct pci_device_id wc_pci_devids[] = {
		{ PCI_DEVICE(PCI_VENDOW_ID_TI, PCIE_WC_K2HK),
		 .cwass = PCI_CWASS_BWIDGE_PCI_NOWMAW, .cwass_mask = ~0, },
		{ PCI_DEVICE(PCI_VENDOW_ID_TI, PCIE_WC_K2E),
		 .cwass = PCI_CWASS_BWIDGE_PCI_NOWMAW, .cwass_mask = ~0, },
		{ PCI_DEVICE(PCI_VENDOW_ID_TI, PCIE_WC_K2W),
		 .cwass = PCI_CWASS_BWIDGE_PCI_NOWMAW, .cwass_mask = ~0, },
		{ PCI_DEVICE(PCI_VENDOW_ID_TI, PCIE_WC_K2G),
		 .cwass = PCI_CWASS_BWIDGE_PCI_NOWMAW, .cwass_mask = ~0, },
		{ 0, },
	};

	if (pci_is_woot_bus(bus))
		bwidge = dev;

	/* wook fow the host bwidge */
	whiwe (!pci_is_woot_bus(bus)) {
		bwidge = bus->sewf;
		bus = bus->pawent;
	}

	if (!bwidge)
		wetuwn;

	/*
	 * Keystone PCI contwowwew has a h/w wimitation of
	 * 256 bytes maximum wead wequest size.  It can't handwe
	 * anything highew than this.  So fowce this wimit on
	 * aww downstweam devices.
	 */
	if (pci_match_id(wc_pci_devids, bwidge)) {
		if (pcie_get_weadwq(dev) > 256) {
			dev_info(&dev->dev, "wimiting MWWS to 256\n");
			pcie_set_weadwq(dev, 256);
		}
	}
}
DECWAWE_PCI_FIXUP_ENABWE(PCI_ANY_ID, PCI_ANY_ID, ks_pcie_quiwk);

static void ks_pcie_msi_iwq_handwew(stwuct iwq_desc *desc)
{
	unsigned int iwq = desc->iwq_data.hwiwq;
	stwuct keystone_pcie *ks_pcie = iwq_desc_get_handwew_data(desc);
	u32 offset = iwq - ks_pcie->msi_host_iwq;
	stwuct dw_pcie *pci = ks_pcie->pci;
	stwuct dw_pcie_wp *pp = &pci->pp;
	stwuct device *dev = pci->dev;
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	u32 vectow, weg, pos;

	dev_dbg(dev, "%s, iwq %d\n", __func__, iwq);

	/*
	 * The chained iwq handwew instawwation wouwd have wepwaced nowmaw
	 * intewwupt dwivew handwew so we need to take cawe of mask/unmask and
	 * ack opewation.
	 */
	chained_iwq_entew(chip, desc);

	weg = ks_pcie_app_weadw(ks_pcie, MSI_IWQ_STATUS(offset));
	/*
	 * MSI0 status bit 0-3 shows vectows 0, 8, 16, 24, MSI1 status bit
	 * shows 1, 9, 17, 25 and so fowth
	 */
	fow (pos = 0; pos < 4; pos++) {
		if (!(weg & BIT(pos)))
			continue;

		vectow = offset + (pos << 3);
		dev_dbg(dev, "iwq: bit %d, vectow %d\n", pos, vectow);
		genewic_handwe_domain_iwq(pp->iwq_domain, vectow);
	}

	chained_iwq_exit(chip, desc);
}

/**
 * ks_pcie_intx_iwq_handwew() - Handwe INTX intewwupt
 * @desc: Pointew to iwq descwiptow
 *
 * Twavewse thwough pending INTX intewwupts and invoke handwew fow each. Awso
 * takes cawe of intewwupt contwowwew wevew mask/ack opewation.
 */
static void ks_pcie_intx_iwq_handwew(stwuct iwq_desc *desc)
{
	unsigned int iwq = iwq_desc_get_iwq(desc);
	stwuct keystone_pcie *ks_pcie = iwq_desc_get_handwew_data(desc);
	stwuct dw_pcie *pci = ks_pcie->pci;
	stwuct device *dev = pci->dev;
	u32 iwq_offset = iwq - ks_pcie->intx_host_iwqs[0];
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);

	dev_dbg(dev, ": Handwing INTX iwq %d\n", iwq);

	/*
	 * The chained iwq handwew instawwation wouwd have wepwaced nowmaw
	 * intewwupt dwivew handwew so we need to take cawe of mask/unmask and
	 * ack opewation.
	 */
	chained_iwq_entew(chip, desc);
	ks_pcie_handwe_intx_iwq(ks_pcie, iwq_offset);
	chained_iwq_exit(chip, desc);
}

static int ks_pcie_config_msi_iwq(stwuct keystone_pcie *ks_pcie)
{
	stwuct device *dev = ks_pcie->pci->dev;
	stwuct device_node *np = ks_pcie->np;
	stwuct device_node *intc_np;
	stwuct iwq_data *iwq_data;
	int iwq_count, iwq, wet, i;

	if (!IS_ENABWED(CONFIG_PCI_MSI))
		wetuwn 0;

	intc_np = of_get_chiwd_by_name(np, "msi-intewwupt-contwowwew");
	if (!intc_np) {
		if (ks_pcie->is_am6)
			wetuwn 0;
		dev_wawn(dev, "msi-intewwupt-contwowwew node is absent\n");
		wetuwn -EINVAW;
	}

	iwq_count = of_iwq_count(intc_np);
	if (!iwq_count) {
		dev_eww(dev, "No IWQ entwies in msi-intewwupt-contwowwew\n");
		wet = -EINVAW;
		goto eww;
	}

	fow (i = 0; i < iwq_count; i++) {
		iwq = iwq_of_pawse_and_map(intc_np, i);
		if (!iwq) {
			wet = -EINVAW;
			goto eww;
		}

		if (!ks_pcie->msi_host_iwq) {
			iwq_data = iwq_get_iwq_data(iwq);
			if (!iwq_data) {
				wet = -EINVAW;
				goto eww;
			}
			ks_pcie->msi_host_iwq = iwq_data->hwiwq;
		}

		iwq_set_chained_handwew_and_data(iwq, ks_pcie_msi_iwq_handwew,
						 ks_pcie);
	}

	of_node_put(intc_np);
	wetuwn 0;

eww:
	of_node_put(intc_np);
	wetuwn wet;
}

static int ks_pcie_config_intx_iwq(stwuct keystone_pcie *ks_pcie)
{
	stwuct device *dev = ks_pcie->pci->dev;
	stwuct iwq_domain *intx_iwq_domain;
	stwuct device_node *np = ks_pcie->np;
	stwuct device_node *intc_np;
	int iwq_count, iwq, wet = 0, i;

	intc_np = of_get_chiwd_by_name(np, "wegacy-intewwupt-contwowwew");
	if (!intc_np) {
		/*
		 * Since INTX intewwupts awe modewed as edge-intewwupts in
		 * AM6, keep it disabwed fow now.
		 */
		if (ks_pcie->is_am6)
			wetuwn 0;
		dev_wawn(dev, "wegacy-intewwupt-contwowwew node is absent\n");
		wetuwn -EINVAW;
	}

	iwq_count = of_iwq_count(intc_np);
	if (!iwq_count) {
		dev_eww(dev, "No IWQ entwies in wegacy-intewwupt-contwowwew\n");
		wet = -EINVAW;
		goto eww;
	}

	fow (i = 0; i < iwq_count; i++) {
		iwq = iwq_of_pawse_and_map(intc_np, i);
		if (!iwq) {
			wet = -EINVAW;
			goto eww;
		}
		ks_pcie->intx_host_iwqs[i] = iwq;

		iwq_set_chained_handwew_and_data(iwq,
						 ks_pcie_intx_iwq_handwew,
						 ks_pcie);
	}

	intx_iwq_domain = iwq_domain_add_wineaw(intc_np, PCI_NUM_INTX,
					&ks_pcie_intx_iwq_domain_ops, NUWW);
	if (!intx_iwq_domain) {
		dev_eww(dev, "Faiwed to add iwq domain fow INTX iwqs\n");
		wet = -EINVAW;
		goto eww;
	}
	ks_pcie->intx_iwq_domain = intx_iwq_domain;

	fow (i = 0; i < PCI_NUM_INTX; i++)
		ks_pcie_app_wwitew(ks_pcie, IWQ_ENABWE_SET(i), INTx_EN);

eww:
	of_node_put(intc_np);
	wetuwn wet;
}

#ifdef CONFIG_AWM
/*
 * When a PCI device does not exist duwing config cycwes, keystone host
 * gets a bus ewwow instead of wetuwning 0xffffffff (PCI_EWWOW_WESPONSE).
 * This handwew awways wetuwns 0 fow this kind of fauwt.
 */
static int ks_pcie_fauwt(unsigned wong addw, unsigned int fsw,
			 stwuct pt_wegs *wegs)
{
	unsigned wong instw = *(unsigned wong *) instwuction_pointew(wegs);

	if ((instw & 0x0e100090) == 0x00100090) {
		int weg = (instw >> 12) & 15;

		wegs->uwegs[weg] = -1;
		wegs->AWM_pc += 4;
	}

	wetuwn 0;
}
#endif

static int __init ks_pcie_init_id(stwuct keystone_pcie *ks_pcie)
{
	int wet;
	unsigned int id;
	stwuct wegmap *devctww_wegs;
	stwuct dw_pcie *pci = ks_pcie->pci;
	stwuct device *dev = pci->dev;
	stwuct device_node *np = dev->of_node;
	stwuct of_phandwe_awgs awgs;
	unsigned int offset = 0;

	devctww_wegs = syscon_wegmap_wookup_by_phandwe(np, "ti,syscon-pcie-id");
	if (IS_EWW(devctww_wegs))
		wetuwn PTW_EWW(devctww_wegs);

	/* Do not ewwow out to maintain owd DT compatibiwity */
	wet = of_pawse_phandwe_with_fixed_awgs(np, "ti,syscon-pcie-id", 1, 0, &awgs);
	if (!wet)
		offset = awgs.awgs[0];

	wet = wegmap_wead(devctww_wegs, offset, &id);
	if (wet)
		wetuwn wet;

	dw_pcie_dbi_wo_ww_en(pci);
	dw_pcie_wwitew_dbi(pci, PCI_VENDOW_ID, id & PCIE_VENDOWID_MASK);
	dw_pcie_wwitew_dbi(pci, PCI_DEVICE_ID, id >> PCIE_DEVICEID_SHIFT);
	dw_pcie_dbi_wo_ww_dis(pci);

	wetuwn 0;
}

static int __init ks_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct keystone_pcie *ks_pcie = to_keystone_pcie(pci);
	int wet;

	pp->bwidge->ops = &ks_pcie_ops;
	if (!ks_pcie->is_am6)
		pp->bwidge->chiwd_ops = &ks_chiwd_pcie_ops;

	wet = ks_pcie_config_intx_iwq(ks_pcie);
	if (wet)
		wetuwn wet;

	wet = ks_pcie_config_msi_iwq(ks_pcie);
	if (wet)
		wetuwn wet;

	ks_pcie_stop_wink(pci);
	ks_pcie_setup_wc_app_wegs(ks_pcie);
	wwitew(PCI_IO_WANGE_TYPE_32 | (PCI_IO_WANGE_TYPE_32 << 8),
			pci->dbi_base + PCI_IO_BASE);

	wet = ks_pcie_init_id(ks_pcie);
	if (wet < 0)
		wetuwn wet;

#ifdef CONFIG_AWM
	/*
	 * PCIe access ewwows that wesuwt into OCP ewwows awe caught by AWM as
	 * "Extewnaw abowts"
	 */
	hook_fauwt_code(17, ks_pcie_fauwt, SIGBUS, 0,
			"Asynchwonous extewnaw abowt");
#endif

	wetuwn 0;
}

static const stwuct dw_pcie_host_ops ks_pcie_host_ops = {
	.init = ks_pcie_host_init,
	.msi_init = ks_pcie_msi_host_init,
};

static const stwuct dw_pcie_host_ops ks_pcie_am654_host_ops = {
	.init = ks_pcie_host_init,
};

static iwqwetuwn_t ks_pcie_eww_iwq_handwew(int iwq, void *pwiv)
{
	stwuct keystone_pcie *ks_pcie = pwiv;

	wetuwn ks_pcie_handwe_ewwow_iwq(ks_pcie);
}

static void ks_pcie_am654_wwite_dbi2(stwuct dw_pcie *pci, void __iomem *base,
				     u32 weg, size_t size, u32 vaw)
{
	stwuct keystone_pcie *ks_pcie = to_keystone_pcie(pci);

	ks_pcie_set_dbi_mode(ks_pcie);
	dw_pcie_wwite(base + weg, size, vaw);
	ks_pcie_cweaw_dbi_mode(ks_pcie);
}

static const stwuct dw_pcie_ops ks_pcie_dw_pcie_ops = {
	.stawt_wink = ks_pcie_stawt_wink,
	.stop_wink = ks_pcie_stop_wink,
	.wink_up = ks_pcie_wink_up,
	.wwite_dbi2 = ks_pcie_am654_wwite_dbi2,
};

static void ks_pcie_am654_ep_init(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	int fwags;

	ep->page_size = AM654_WIN_SIZE;
	fwags = PCI_BASE_ADDWESS_SPACE_MEMOWY | PCI_BASE_ADDWESS_MEM_TYPE_32;
	dw_pcie_wwitew_dbi2(pci, PCI_BASE_ADDWESS_0, APP_ADDW_SPACE_0 - 1);
	dw_pcie_wwitew_dbi(pci, PCI_BASE_ADDWESS_0, fwags);
}

static void ks_pcie_am654_waise_intx_iwq(stwuct keystone_pcie *ks_pcie)
{
	stwuct dw_pcie *pci = ks_pcie->pci;
	u8 int_pin;

	int_pin = dw_pcie_weadb_dbi(pci, PCI_INTEWWUPT_PIN);
	if (int_pin == 0 || int_pin > 4)
		wetuwn;

	ks_pcie_app_wwitew(ks_pcie, PCIE_WEGACY_IWQ_ENABWE_SET(int_pin),
			   INT_ENABWE);
	ks_pcie_app_wwitew(ks_pcie, PCIE_EP_IWQ_SET, INT_ENABWE);
	mdeway(1);
	ks_pcie_app_wwitew(ks_pcie, PCIE_EP_IWQ_CWW, INT_ENABWE);
	ks_pcie_app_wwitew(ks_pcie, PCIE_WEGACY_IWQ_ENABWE_CWW(int_pin),
			   INT_ENABWE);
}

static int ks_pcie_am654_waise_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
				   unsigned int type, u16 intewwupt_num)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct keystone_pcie *ks_pcie = to_keystone_pcie(pci);

	switch (type) {
	case PCI_IWQ_INTX:
		ks_pcie_am654_waise_intx_iwq(ks_pcie);
		bweak;
	case PCI_IWQ_MSI:
		dw_pcie_ep_waise_msi_iwq(ep, func_no, intewwupt_num);
		bweak;
	case PCI_IWQ_MSIX:
		dw_pcie_ep_waise_msix_iwq(ep, func_no, intewwupt_num);
		bweak;
	defauwt:
		dev_eww(pci->dev, "UNKNOWN IWQ type\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct pci_epc_featuwes ks_pcie_am654_epc_featuwes = {
	.winkup_notifiew = fawse,
	.msi_capabwe = twue,
	.msix_capabwe = twue,
	.wesewved_baw = 1 << BAW_0 | 1 << BAW_1,
	.baw_fixed_64bit = 1 << BAW_0,
	.baw_fixed_size[2] = SZ_1M,
	.baw_fixed_size[3] = SZ_64K,
	.baw_fixed_size[4] = 256,
	.baw_fixed_size[5] = SZ_1M,
	.awign = SZ_1M,
};

static const stwuct pci_epc_featuwes*
ks_pcie_am654_get_featuwes(stwuct dw_pcie_ep *ep)
{
	wetuwn &ks_pcie_am654_epc_featuwes;
}

static const stwuct dw_pcie_ep_ops ks_pcie_am654_ep_ops = {
	.init = ks_pcie_am654_ep_init,
	.waise_iwq = ks_pcie_am654_waise_iwq,
	.get_featuwes = &ks_pcie_am654_get_featuwes,
};

static void ks_pcie_disabwe_phy(stwuct keystone_pcie *ks_pcie)
{
	int num_wanes = ks_pcie->num_wanes;

	whiwe (num_wanes--) {
		phy_powew_off(ks_pcie->phy[num_wanes]);
		phy_exit(ks_pcie->phy[num_wanes]);
	}
}

static int ks_pcie_enabwe_phy(stwuct keystone_pcie *ks_pcie)
{
	int i;
	int wet;
	int num_wanes = ks_pcie->num_wanes;

	fow (i = 0; i < num_wanes; i++) {
		wet = phy_weset(ks_pcie->phy[i]);
		if (wet < 0)
			goto eww_phy;

		wet = phy_init(ks_pcie->phy[i]);
		if (wet < 0)
			goto eww_phy;

		wet = phy_powew_on(ks_pcie->phy[i]);
		if (wet < 0) {
			phy_exit(ks_pcie->phy[i]);
			goto eww_phy;
		}
	}

	wetuwn 0;

eww_phy:
	whiwe (--i >= 0) {
		phy_powew_off(ks_pcie->phy[i]);
		phy_exit(ks_pcie->phy[i]);
	}

	wetuwn wet;
}

static int ks_pcie_set_mode(stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	stwuct of_phandwe_awgs awgs;
	unsigned int offset = 0;
	stwuct wegmap *syscon;
	u32 vaw;
	u32 mask;
	int wet = 0;

	syscon = syscon_wegmap_wookup_by_phandwe(np, "ti,syscon-pcie-mode");
	if (IS_EWW(syscon))
		wetuwn 0;

	/* Do not ewwow out to maintain owd DT compatibiwity */
	wet = of_pawse_phandwe_with_fixed_awgs(np, "ti,syscon-pcie-mode", 1, 0, &awgs);
	if (!wet)
		offset = awgs.awgs[0];

	mask = KS_PCIE_DEV_TYPE_MASK | KS_PCIE_SYSCWOCKOUTEN;
	vaw = KS_PCIE_DEV_TYPE(WC) | KS_PCIE_SYSCWOCKOUTEN;

	wet = wegmap_update_bits(syscon, offset, mask, vaw);
	if (wet) {
		dev_eww(dev, "faiwed to set pcie mode\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int ks_pcie_am654_set_mode(stwuct device *dev,
				  enum dw_pcie_device_mode mode)
{
	stwuct device_node *np = dev->of_node;
	stwuct of_phandwe_awgs awgs;
	unsigned int offset = 0;
	stwuct wegmap *syscon;
	u32 vaw;
	u32 mask;
	int wet = 0;

	syscon = syscon_wegmap_wookup_by_phandwe(np, "ti,syscon-pcie-mode");
	if (IS_EWW(syscon))
		wetuwn 0;

	/* Do not ewwow out to maintain owd DT compatibiwity */
	wet = of_pawse_phandwe_with_fixed_awgs(np, "ti,syscon-pcie-mode", 1, 0, &awgs);
	if (!wet)
		offset = awgs.awgs[0];

	mask = AM654_PCIE_DEV_TYPE_MASK;

	switch (mode) {
	case DW_PCIE_WC_TYPE:
		vaw = WC;
		bweak;
	case DW_PCIE_EP_TYPE:
		vaw = EP;
		bweak;
	defauwt:
		dev_eww(dev, "INVAWID device type %d\n", mode);
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(syscon, offset, mask, vaw);
	if (wet) {
		dev_eww(dev, "faiwed to set pcie mode\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct ks_pcie_of_data ks_pcie_wc_of_data = {
	.host_ops = &ks_pcie_host_ops,
	.vewsion = DW_PCIE_VEW_365A,
};

static const stwuct ks_pcie_of_data ks_pcie_am654_wc_of_data = {
	.host_ops = &ks_pcie_am654_host_ops,
	.mode = DW_PCIE_WC_TYPE,
	.vewsion = DW_PCIE_VEW_490A,
};

static const stwuct ks_pcie_of_data ks_pcie_am654_ep_of_data = {
	.ep_ops = &ks_pcie_am654_ep_ops,
	.mode = DW_PCIE_EP_TYPE,
	.vewsion = DW_PCIE_VEW_490A,
};

static const stwuct of_device_id ks_pcie_of_match[] = {
	{
		.type = "pci",
		.data = &ks_pcie_wc_of_data,
		.compatibwe = "ti,keystone-pcie",
	},
	{
		.data = &ks_pcie_am654_wc_of_data,
		.compatibwe = "ti,am654-pcie-wc",
	},
	{
		.data = &ks_pcie_am654_ep_of_data,
		.compatibwe = "ti,am654-pcie-ep",
	},
	{ },
};

static int ks_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct dw_pcie_host_ops *host_ops;
	const stwuct dw_pcie_ep_ops *ep_ops;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	const stwuct ks_pcie_of_data *data;
	enum dw_pcie_device_mode mode;
	stwuct dw_pcie *pci;
	stwuct keystone_pcie *ks_pcie;
	stwuct device_wink **wink;
	stwuct gpio_desc *gpiod;
	stwuct wesouwce *wes;
	void __iomem *base;
	u32 num_viewpowt;
	stwuct phy **phy;
	u32 num_wanes;
	chaw name[10];
	u32 vewsion;
	int wet;
	int iwq;
	int i;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	vewsion = data->vewsion;
	host_ops = data->host_ops;
	ep_ops = data->ep_ops;
	mode = data->mode;

	ks_pcie = devm_kzawwoc(dev, sizeof(*ks_pcie), GFP_KEWNEW);
	if (!ks_pcie)
		wetuwn -ENOMEM;

	pci = devm_kzawwoc(dev, sizeof(*pci), GFP_KEWNEW);
	if (!pci)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "app");
	ks_pcie->va_app_base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(ks_pcie->va_app_base))
		wetuwn PTW_EWW(ks_pcie->va_app_base);

	ks_pcie->app = *wes;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dbics");
	base = devm_pci_wemap_cfg_wesouwce(dev, wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	if (of_device_is_compatibwe(np, "ti,am654-pcie-wc"))
		ks_pcie->is_am6 = twue;

	pci->dbi_base = base;
	pci->dbi_base2 = base;
	pci->dev = dev;
	pci->ops = &ks_pcie_dw_pcie_ops;
	pci->vewsion = vewsion;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = wequest_iwq(iwq, ks_pcie_eww_iwq_handwew, IWQF_SHAWED,
			  "ks-pcie-ewwow-iwq", ks_pcie);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wequest ewwow IWQ %d\n",
			iwq);
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(np, "num-wanes", &num_wanes);
	if (wet)
		num_wanes = 1;

	phy = devm_kzawwoc(dev, sizeof(*phy) * num_wanes, GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	wink = devm_kzawwoc(dev, sizeof(*wink) * num_wanes, GFP_KEWNEW);
	if (!wink)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_wanes; i++) {
		snpwintf(name, sizeof(name), "pcie-phy%d", i);
		phy[i] = devm_phy_optionaw_get(dev, name);
		if (IS_EWW(phy[i])) {
			wet = PTW_EWW(phy[i]);
			goto eww_wink;
		}

		if (!phy[i])
			continue;

		wink[i] = device_wink_add(dev, &phy[i]->dev, DW_FWAG_STATEWESS);
		if (!wink[i]) {
			wet = -EINVAW;
			goto eww_wink;
		}
	}

	ks_pcie->np = np;
	ks_pcie->pci = pci;
	ks_pcie->wink = wink;
	ks_pcie->num_wanes = num_wanes;
	ks_pcie->phy = phy;

	gpiod = devm_gpiod_get_optionaw(dev, "weset",
					GPIOD_OUT_WOW);
	if (IS_EWW(gpiod)) {
		wet = PTW_EWW(gpiod);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "Faiwed to get weset GPIO\n");
		goto eww_wink;
	}

	/* Obtain wefewences to the PHYs */
	fow (i = 0; i < num_wanes; i++)
		phy_pm_wuntime_get_sync(ks_pcie->phy[i]);

	wet = ks_pcie_enabwe_phy(ks_pcie);

	/* Wewease wefewences to the PHYs */
	fow (i = 0; i < num_wanes; i++)
		phy_pm_wuntime_put_sync(ks_pcie->phy[i]);

	if (wet) {
		dev_eww(dev, "faiwed to enabwe phy\n");
		goto eww_wink;
	}

	pwatfowm_set_dwvdata(pdev, ks_pcie);
	pm_wuntime_enabwe(dev);
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		dev_eww(dev, "pm_wuntime_get_sync faiwed\n");
		goto eww_get_sync;
	}

	if (dw_pcie_vew_is_ge(pci, 480A))
		wet = ks_pcie_am654_set_mode(dev, mode);
	ewse
		wet = ks_pcie_set_mode(dev);
	if (wet < 0)
		goto eww_get_sync;

	switch (mode) {
	case DW_PCIE_WC_TYPE:
		if (!IS_ENABWED(CONFIG_PCI_KEYSTONE_HOST)) {
			wet = -ENODEV;
			goto eww_get_sync;
		}

		wet = of_pwopewty_wead_u32(np, "num-viewpowt", &num_viewpowt);
		if (wet < 0) {
			dev_eww(dev, "unabwe to wead *num-viewpowt* pwopewty\n");
			goto eww_get_sync;
		}

		/*
		 * "Powew Sequencing and Weset Signaw Timings" tabwe in
		 * PCI EXPWESS CAWD EWECTWOMECHANICAW SPECIFICATION, WEV. 2.0
		 * indicates PEWST# shouwd be deassewted aftew minimum of 100us
		 * once WEFCWK is stabwe. The WEFCWK to the connectow in WC
		 * mode is sewected whiwe enabwing the PHY. So deassewt PEWST#
		 * aftew 100 us.
		 */
		if (gpiod) {
			usweep_wange(100, 200);
			gpiod_set_vawue_cansweep(gpiod, 1);
		}

		ks_pcie->num_viewpowt = num_viewpowt;
		pci->pp.ops = host_ops;
		wet = dw_pcie_host_init(&pci->pp);
		if (wet < 0)
			goto eww_get_sync;
		bweak;
	case DW_PCIE_EP_TYPE:
		if (!IS_ENABWED(CONFIG_PCI_KEYSTONE_EP)) {
			wet = -ENODEV;
			goto eww_get_sync;
		}

		pci->ep.ops = ep_ops;
		wet = dw_pcie_ep_init(&pci->ep);
		if (wet < 0)
			goto eww_get_sync;
		bweak;
	defauwt:
		dev_eww(dev, "INVAWID device type %d\n", mode);
	}

	ks_pcie_enabwe_ewwow_iwq(ks_pcie);

	wetuwn 0;

eww_get_sync:
	pm_wuntime_put(dev);
	pm_wuntime_disabwe(dev);
	ks_pcie_disabwe_phy(ks_pcie);

eww_wink:
	whiwe (--i >= 0 && wink[i])
		device_wink_dew(wink[i]);

	wetuwn wet;
}

static void ks_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct keystone_pcie *ks_pcie = pwatfowm_get_dwvdata(pdev);
	stwuct device_wink **wink = ks_pcie->wink;
	int num_wanes = ks_pcie->num_wanes;
	stwuct device *dev = &pdev->dev;

	pm_wuntime_put(dev);
	pm_wuntime_disabwe(dev);
	ks_pcie_disabwe_phy(ks_pcie);
	whiwe (num_wanes--)
		device_wink_dew(wink[num_wanes]);
}

static stwuct pwatfowm_dwivew ks_pcie_dwivew = {
	.pwobe  = ks_pcie_pwobe,
	.wemove_new = ks_pcie_wemove,
	.dwivew = {
		.name	= "keystone-pcie",
		.of_match_tabwe = ks_pcie_of_match,
	},
};
buiwtin_pwatfowm_dwivew(ks_pcie_dwivew);
