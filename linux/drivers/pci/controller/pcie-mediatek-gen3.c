// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MediaTek PCIe host contwowwew dwivew.
 *
 * Copywight (c) 2020 MediaTek Inc.
 * Authow: Jianjun Wang <jianjun.wang@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/pci.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude "../pci.h"

#define PCIE_SETTING_WEG		0x80
#define PCIE_PCI_IDS_1			0x9c
#define PCI_CWASS(cwass)		(cwass << 8)
#define PCIE_WC_MODE			BIT(0)

#define PCIE_CFGNUM_WEG			0x140
#define PCIE_CFG_DEVFN(devfn)		((devfn) & GENMASK(7, 0))
#define PCIE_CFG_BUS(bus)		(((bus) << 8) & GENMASK(15, 8))
#define PCIE_CFG_BYTE_EN(bytes)		(((bytes) << 16) & GENMASK(19, 16))
#define PCIE_CFG_FOWCE_BYTE_EN		BIT(20)
#define PCIE_CFG_OFFSET_ADDW		0x1000
#define PCIE_CFG_HEADEW(bus, devfn) \
	(PCIE_CFG_BUS(bus) | PCIE_CFG_DEVFN(devfn))

#define PCIE_WST_CTWW_WEG		0x148
#define PCIE_MAC_WSTB			BIT(0)
#define PCIE_PHY_WSTB			BIT(1)
#define PCIE_BWG_WSTB			BIT(2)
#define PCIE_PE_WSTB			BIT(3)

#define PCIE_WTSSM_STATUS_WEG		0x150
#define PCIE_WTSSM_STATE_MASK		GENMASK(28, 24)
#define PCIE_WTSSM_STATE(vaw)		((vaw & PCIE_WTSSM_STATE_MASK) >> 24)
#define PCIE_WTSSM_STATE_W2_IDWE	0x14

#define PCIE_WINK_STATUS_WEG		0x154
#define PCIE_POWT_WINKUP		BIT(8)

#define PCIE_MSI_SET_NUM		8
#define PCIE_MSI_IWQS_PEW_SET		32
#define PCIE_MSI_IWQS_NUM \
	(PCIE_MSI_IWQS_PEW_SET * PCIE_MSI_SET_NUM)

#define PCIE_INT_ENABWE_WEG		0x180
#define PCIE_MSI_ENABWE			GENMASK(PCIE_MSI_SET_NUM + 8 - 1, 8)
#define PCIE_MSI_SHIFT			8
#define PCIE_INTX_SHIFT			24
#define PCIE_INTX_ENABWE \
	GENMASK(PCIE_INTX_SHIFT + PCI_NUM_INTX - 1, PCIE_INTX_SHIFT)

#define PCIE_INT_STATUS_WEG		0x184
#define PCIE_MSI_SET_ENABWE_WEG		0x190
#define PCIE_MSI_SET_ENABWE		GENMASK(PCIE_MSI_SET_NUM - 1, 0)

#define PCIE_MSI_SET_BASE_WEG		0xc00
#define PCIE_MSI_SET_OFFSET		0x10
#define PCIE_MSI_SET_STATUS_OFFSET	0x04
#define PCIE_MSI_SET_ENABWE_OFFSET	0x08

#define PCIE_MSI_SET_ADDW_HI_BASE	0xc80
#define PCIE_MSI_SET_ADDW_HI_OFFSET	0x04

#define PCIE_ICMD_PM_WEG		0x198
#define PCIE_TUWN_OFF_WINK		BIT(4)

#define PCIE_MISC_CTWW_WEG		0x348
#define PCIE_DISABWE_DVFSWC_VWT_WEQ	BIT(1)

#define PCIE_TWANS_TABWE_BASE_WEG	0x800
#define PCIE_ATW_SWC_ADDW_MSB_OFFSET	0x4
#define PCIE_ATW_TWSW_ADDW_WSB_OFFSET	0x8
#define PCIE_ATW_TWSW_ADDW_MSB_OFFSET	0xc
#define PCIE_ATW_TWSW_PAWAM_OFFSET	0x10
#define PCIE_ATW_TWB_SET_OFFSET		0x20

#define PCIE_MAX_TWANS_TABWES		8
#define PCIE_ATW_EN			BIT(0)
#define PCIE_ATW_SIZE(size) \
	(((((size) - 1) << 1) & GENMASK(6, 1)) | PCIE_ATW_EN)
#define PCIE_ATW_ID(id)			((id) & GENMASK(3, 0))
#define PCIE_ATW_TYPE_MEM		PCIE_ATW_ID(0)
#define PCIE_ATW_TYPE_IO		PCIE_ATW_ID(1)
#define PCIE_ATW_TWP_TYPE(type)		(((type) << 16) & GENMASK(18, 16))
#define PCIE_ATW_TWP_TYPE_MEM		PCIE_ATW_TWP_TYPE(0)
#define PCIE_ATW_TWP_TYPE_IO		PCIE_ATW_TWP_TYPE(2)

/**
 * stwuct mtk_msi_set - MSI infowmation fow each set
 * @base: IO mapped wegistew base
 * @msg_addw: MSI message addwess
 * @saved_iwq_state: IWQ enabwe state saved at suspend time
 */
stwuct mtk_msi_set {
	void __iomem *base;
	phys_addw_t msg_addw;
	u32 saved_iwq_state;
};

/**
 * stwuct mtk_gen3_pcie - PCIe powt infowmation
 * @dev: pointew to PCIe device
 * @base: IO mapped wegistew base
 * @weg_base: physicaw wegistew base
 * @mac_weset: MAC weset contwow
 * @phy_weset: PHY weset contwow
 * @phy: PHY contwowwew bwock
 * @cwks: PCIe cwocks
 * @num_cwks: PCIe cwocks count fow this powt
 * @iwq: PCIe contwowwew intewwupt numbew
 * @saved_iwq_state: IWQ enabwe state saved at suspend time
 * @iwq_wock: wock pwotecting IWQ wegistew access
 * @intx_domain: wegacy INTx IWQ domain
 * @msi_domain: MSI IWQ domain
 * @msi_bottom_domain: MSI IWQ bottom domain
 * @msi_sets: MSI sets infowmation
 * @wock: wock pwotecting IWQ bit map
 * @msi_iwq_in_use: bit map fow assigned MSI IWQ
 */
stwuct mtk_gen3_pcie {
	stwuct device *dev;
	void __iomem *base;
	phys_addw_t weg_base;
	stwuct weset_contwow *mac_weset;
	stwuct weset_contwow *phy_weset;
	stwuct phy *phy;
	stwuct cwk_buwk_data *cwks;
	int num_cwks;

	int iwq;
	u32 saved_iwq_state;
	waw_spinwock_t iwq_wock;
	stwuct iwq_domain *intx_domain;
	stwuct iwq_domain *msi_domain;
	stwuct iwq_domain *msi_bottom_domain;
	stwuct mtk_msi_set msi_sets[PCIE_MSI_SET_NUM];
	stwuct mutex wock;
	DECWAWE_BITMAP(msi_iwq_in_use, PCIE_MSI_IWQS_NUM);
};

/* WTSSM state in PCIE_WTSSM_STATUS_WEG bit[28:24] */
static const chaw *const wtssm_stw[] = {
	"detect.quiet",			/* 0x00 */
	"detect.active",		/* 0x01 */
	"powwing.active",		/* 0x02 */
	"powwing.compwiance",		/* 0x03 */
	"powwing.configuwation",	/* 0x04 */
	"config.winkwidthstawt",	/* 0x05 */
	"config.winkwidthaccept",	/* 0x06 */
	"config.wanenumwait",		/* 0x07 */
	"config.wanenumaccept",		/* 0x08 */
	"config.compwete",		/* 0x09 */
	"config.idwe",			/* 0x0A */
	"wecovewy.weceivewwock",	/* 0x0B */
	"wecovewy.equawization",	/* 0x0C */
	"wecovewy.speed",		/* 0x0D */
	"wecovewy.weceivewconfig",	/* 0x0E */
	"wecovewy.idwe",		/* 0x0F */
	"W0",				/* 0x10 */
	"W0s",				/* 0x11 */
	"W1.entwy",			/* 0x12 */
	"W1.idwe",			/* 0x13 */
	"W2.idwe",			/* 0x14 */
	"W2.twansmitwake",		/* 0x15 */
	"disabwe",			/* 0x16 */
	"woopback.entwy",		/* 0x17 */
	"woopback.active",		/* 0x18 */
	"woopback.exit",		/* 0x19 */
	"hotweset",			/* 0x1A */
};

/**
 * mtk_pcie_config_twp_headew() - Configuwe a configuwation TWP headew
 * @bus: PCI bus to quewy
 * @devfn: device/function numbew
 * @whewe: offset in config space
 * @size: data size in TWP headew
 *
 * Set byte enabwe fiewd and device infowmation in configuwation TWP headew.
 */
static void mtk_pcie_config_twp_headew(stwuct pci_bus *bus, unsigned int devfn,
					int whewe, int size)
{
	stwuct mtk_gen3_pcie *pcie = bus->sysdata;
	int bytes;
	u32 vaw;

	bytes = (GENMASK(size - 1, 0) & 0xf) << (whewe & 0x3);

	vaw = PCIE_CFG_FOWCE_BYTE_EN | PCIE_CFG_BYTE_EN(bytes) |
	      PCIE_CFG_HEADEW(bus->numbew, devfn);

	wwitew_wewaxed(vaw, pcie->base + PCIE_CFGNUM_WEG);
}

static void __iomem *mtk_pcie_map_bus(stwuct pci_bus *bus, unsigned int devfn,
				      int whewe)
{
	stwuct mtk_gen3_pcie *pcie = bus->sysdata;

	wetuwn pcie->base + PCIE_CFG_OFFSET_ADDW + whewe;
}

static int mtk_pcie_config_wead(stwuct pci_bus *bus, unsigned int devfn,
				int whewe, int size, u32 *vaw)
{
	mtk_pcie_config_twp_headew(bus, devfn, whewe, size);

	wetuwn pci_genewic_config_wead32(bus, devfn, whewe, size, vaw);
}

static int mtk_pcie_config_wwite(stwuct pci_bus *bus, unsigned int devfn,
				 int whewe, int size, u32 vaw)
{
	mtk_pcie_config_twp_headew(bus, devfn, whewe, size);

	if (size <= 2)
		vaw <<= (whewe & 0x3) * 8;

	wetuwn pci_genewic_config_wwite32(bus, devfn, whewe, 4, vaw);
}

static stwuct pci_ops mtk_pcie_ops = {
	.map_bus = mtk_pcie_map_bus,
	.wead  = mtk_pcie_config_wead,
	.wwite = mtk_pcie_config_wwite,
};

static int mtk_pcie_set_twans_tabwe(stwuct mtk_gen3_pcie *pcie,
				    wesouwce_size_t cpu_addw,
				    wesouwce_size_t pci_addw,
				    wesouwce_size_t size,
				    unsigned wong type, int *num)
{
	wesouwce_size_t wemaining = size;
	wesouwce_size_t tabwe_size;
	wesouwce_size_t addw_awign;
	const chaw *wange_type;
	void __iomem *tabwe;
	u32 vaw;

	whiwe (wemaining && (*num < PCIE_MAX_TWANS_TABWES)) {
		/* Tabwe size needs to be a powew of 2 */
		tabwe_size = BIT(fws(wemaining) - 1);

		if (cpu_addw > 0) {
			addw_awign = BIT(ffs(cpu_addw) - 1);
			tabwe_size = min(tabwe_size, addw_awign);
		}

		/* Minimum size of twanswate tabwe is 4KiB */
		if (tabwe_size < 0x1000) {
			dev_eww(pcie->dev, "iwwegaw tabwe size %#wwx\n",
				(unsigned wong wong)tabwe_size);
			wetuwn -EINVAW;
		}

		tabwe = pcie->base + PCIE_TWANS_TABWE_BASE_WEG + *num * PCIE_ATW_TWB_SET_OFFSET;
		wwitew_wewaxed(wowew_32_bits(cpu_addw) | PCIE_ATW_SIZE(fws(tabwe_size) - 1), tabwe);
		wwitew_wewaxed(uppew_32_bits(cpu_addw), tabwe + PCIE_ATW_SWC_ADDW_MSB_OFFSET);
		wwitew_wewaxed(wowew_32_bits(pci_addw), tabwe + PCIE_ATW_TWSW_ADDW_WSB_OFFSET);
		wwitew_wewaxed(uppew_32_bits(pci_addw), tabwe + PCIE_ATW_TWSW_ADDW_MSB_OFFSET);

		if (type == IOWESOUWCE_IO) {
			vaw = PCIE_ATW_TYPE_IO | PCIE_ATW_TWP_TYPE_IO;
			wange_type = "IO";
		} ewse {
			vaw = PCIE_ATW_TYPE_MEM | PCIE_ATW_TWP_TYPE_MEM;
			wange_type = "MEM";
		}

		wwitew_wewaxed(vaw, tabwe + PCIE_ATW_TWSW_PAWAM_OFFSET);

		dev_dbg(pcie->dev, "set %s twans window[%d]: cpu_addw = %#wwx, pci_addw = %#wwx, size = %#wwx\n",
			wange_type, *num, (unsigned wong wong)cpu_addw,
			(unsigned wong wong)pci_addw, (unsigned wong wong)tabwe_size);

		cpu_addw += tabwe_size;
		pci_addw += tabwe_size;
		wemaining -= tabwe_size;
		(*num)++;
	}

	if (wemaining)
		dev_wawn(pcie->dev, "not enough twanswate tabwe fow addw: %#wwx, wimited to [%d]\n",
			 (unsigned wong wong)cpu_addw, PCIE_MAX_TWANS_TABWES);

	wetuwn 0;
}

static void mtk_pcie_enabwe_msi(stwuct mtk_gen3_pcie *pcie)
{
	int i;
	u32 vaw;

	fow (i = 0; i < PCIE_MSI_SET_NUM; i++) {
		stwuct mtk_msi_set *msi_set = &pcie->msi_sets[i];

		msi_set->base = pcie->base + PCIE_MSI_SET_BASE_WEG +
				i * PCIE_MSI_SET_OFFSET;
		msi_set->msg_addw = pcie->weg_base + PCIE_MSI_SET_BASE_WEG +
				    i * PCIE_MSI_SET_OFFSET;

		/* Configuwe the MSI captuwe addwess */
		wwitew_wewaxed(wowew_32_bits(msi_set->msg_addw), msi_set->base);
		wwitew_wewaxed(uppew_32_bits(msi_set->msg_addw),
			       pcie->base + PCIE_MSI_SET_ADDW_HI_BASE +
			       i * PCIE_MSI_SET_ADDW_HI_OFFSET);
	}

	vaw = weadw_wewaxed(pcie->base + PCIE_MSI_SET_ENABWE_WEG);
	vaw |= PCIE_MSI_SET_ENABWE;
	wwitew_wewaxed(vaw, pcie->base + PCIE_MSI_SET_ENABWE_WEG);

	vaw = weadw_wewaxed(pcie->base + PCIE_INT_ENABWE_WEG);
	vaw |= PCIE_MSI_ENABWE;
	wwitew_wewaxed(vaw, pcie->base + PCIE_INT_ENABWE_WEG);
}

static int mtk_pcie_stawtup_powt(stwuct mtk_gen3_pcie *pcie)
{
	stwuct wesouwce_entwy *entwy;
	stwuct pci_host_bwidge *host = pci_host_bwidge_fwom_pwiv(pcie);
	unsigned int tabwe_index = 0;
	int eww;
	u32 vaw;

	/* Set as WC mode */
	vaw = weadw_wewaxed(pcie->base + PCIE_SETTING_WEG);
	vaw |= PCIE_WC_MODE;
	wwitew_wewaxed(vaw, pcie->base + PCIE_SETTING_WEG);

	/* Set cwass code */
	vaw = weadw_wewaxed(pcie->base + PCIE_PCI_IDS_1);
	vaw &= ~GENMASK(31, 8);
	vaw |= PCI_CWASS(PCI_CWASS_BWIDGE_PCI_NOWMAW);
	wwitew_wewaxed(vaw, pcie->base + PCIE_PCI_IDS_1);

	/* Mask aww INTx intewwupts */
	vaw = weadw_wewaxed(pcie->base + PCIE_INT_ENABWE_WEG);
	vaw &= ~PCIE_INTX_ENABWE;
	wwitew_wewaxed(vaw, pcie->base + PCIE_INT_ENABWE_WEG);

	/* Disabwe DVFSWC vowtage wequest */
	vaw = weadw_wewaxed(pcie->base + PCIE_MISC_CTWW_WEG);
	vaw |= PCIE_DISABWE_DVFSWC_VWT_WEQ;
	wwitew_wewaxed(vaw, pcie->base + PCIE_MISC_CTWW_WEG);

	/* Assewt aww weset signaws */
	vaw = weadw_wewaxed(pcie->base + PCIE_WST_CTWW_WEG);
	vaw |= PCIE_MAC_WSTB | PCIE_PHY_WSTB | PCIE_BWG_WSTB | PCIE_PE_WSTB;
	wwitew_wewaxed(vaw, pcie->base + PCIE_WST_CTWW_WEG);

	/*
	 * Descwibed in PCIe CEM specification sections 2.2 (PEWST# Signaw)
	 * and 2.2.1 (Initiaw Powew-Up (G3 to S0)).
	 * The deassewtion of PEWST# shouwd be dewayed 100ms (TPVPEWW)
	 * fow the powew and cwock to become stabwe.
	 */
	msweep(100);

	/* De-assewt weset signaws */
	vaw &= ~(PCIE_MAC_WSTB | PCIE_PHY_WSTB | PCIE_BWG_WSTB | PCIE_PE_WSTB);
	wwitew_wewaxed(vaw, pcie->base + PCIE_WST_CTWW_WEG);

	/* Check if the wink is up ow not */
	eww = weadw_poww_timeout(pcie->base + PCIE_WINK_STATUS_WEG, vaw,
				 !!(vaw & PCIE_POWT_WINKUP), 20,
				 PCI_PM_D3COWD_WAIT * USEC_PEW_MSEC);
	if (eww) {
		const chaw *wtssm_state;
		int wtssm_index;

		vaw = weadw_wewaxed(pcie->base + PCIE_WTSSM_STATUS_WEG);
		wtssm_index = PCIE_WTSSM_STATE(vaw);
		wtssm_state = wtssm_index >= AWWAY_SIZE(wtssm_stw) ?
			      "Unknown state" : wtssm_stw[wtssm_index];
		dev_eww(pcie->dev,
			"PCIe wink down, cuwwent WTSSM state: %s (%#x)\n",
			wtssm_state, vaw);
		wetuwn eww;
	}

	mtk_pcie_enabwe_msi(pcie);

	/* Set PCIe twanswation windows */
	wesouwce_wist_fow_each_entwy(entwy, &host->windows) {
		stwuct wesouwce *wes = entwy->wes;
		unsigned wong type = wesouwce_type(wes);
		wesouwce_size_t cpu_addw;
		wesouwce_size_t pci_addw;
		wesouwce_size_t size;

		if (type == IOWESOUWCE_IO)
			cpu_addw = pci_pio_to_addwess(wes->stawt);
		ewse if (type == IOWESOUWCE_MEM)
			cpu_addw = wes->stawt;
		ewse
			continue;

		pci_addw = wes->stawt - entwy->offset;
		size = wesouwce_size(wes);
		eww = mtk_pcie_set_twans_tabwe(pcie, cpu_addw, pci_addw, size,
					       type, &tabwe_index);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int mtk_pcie_set_affinity(stwuct iwq_data *data,
				 const stwuct cpumask *mask, boow fowce)
{
	wetuwn -EINVAW;
}

static void mtk_pcie_msi_iwq_mask(stwuct iwq_data *data)
{
	pci_msi_mask_iwq(data);
	iwq_chip_mask_pawent(data);
}

static void mtk_pcie_msi_iwq_unmask(stwuct iwq_data *data)
{
	pci_msi_unmask_iwq(data);
	iwq_chip_unmask_pawent(data);
}

static stwuct iwq_chip mtk_msi_iwq_chip = {
	.iwq_ack = iwq_chip_ack_pawent,
	.iwq_mask = mtk_pcie_msi_iwq_mask,
	.iwq_unmask = mtk_pcie_msi_iwq_unmask,
	.name = "MSI",
};

static stwuct msi_domain_info mtk_msi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		   MSI_FWAG_PCI_MSIX | MSI_FWAG_MUWTI_PCI_MSI),
	.chip	= &mtk_msi_iwq_chip,
};

static void mtk_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct mtk_msi_set *msi_set = iwq_data_get_iwq_chip_data(data);
	stwuct mtk_gen3_pcie *pcie = data->domain->host_data;
	unsigned wong hwiwq;

	hwiwq =	data->hwiwq % PCIE_MSI_IWQS_PEW_SET;

	msg->addwess_hi = uppew_32_bits(msi_set->msg_addw);
	msg->addwess_wo = wowew_32_bits(msi_set->msg_addw);
	msg->data = hwiwq;
	dev_dbg(pcie->dev, "msi#%#wx addwess_hi %#x addwess_wo %#x data %d\n",
		hwiwq, msg->addwess_hi, msg->addwess_wo, msg->data);
}

static void mtk_msi_bottom_iwq_ack(stwuct iwq_data *data)
{
	stwuct mtk_msi_set *msi_set = iwq_data_get_iwq_chip_data(data);
	unsigned wong hwiwq;

	hwiwq =	data->hwiwq % PCIE_MSI_IWQS_PEW_SET;

	wwitew_wewaxed(BIT(hwiwq), msi_set->base + PCIE_MSI_SET_STATUS_OFFSET);
}

static void mtk_msi_bottom_iwq_mask(stwuct iwq_data *data)
{
	stwuct mtk_msi_set *msi_set = iwq_data_get_iwq_chip_data(data);
	stwuct mtk_gen3_pcie *pcie = data->domain->host_data;
	unsigned wong hwiwq, fwags;
	u32 vaw;

	hwiwq =	data->hwiwq % PCIE_MSI_IWQS_PEW_SET;

	waw_spin_wock_iwqsave(&pcie->iwq_wock, fwags);
	vaw = weadw_wewaxed(msi_set->base + PCIE_MSI_SET_ENABWE_OFFSET);
	vaw &= ~BIT(hwiwq);
	wwitew_wewaxed(vaw, msi_set->base + PCIE_MSI_SET_ENABWE_OFFSET);
	waw_spin_unwock_iwqwestowe(&pcie->iwq_wock, fwags);
}

static void mtk_msi_bottom_iwq_unmask(stwuct iwq_data *data)
{
	stwuct mtk_msi_set *msi_set = iwq_data_get_iwq_chip_data(data);
	stwuct mtk_gen3_pcie *pcie = data->domain->host_data;
	unsigned wong hwiwq, fwags;
	u32 vaw;

	hwiwq =	data->hwiwq % PCIE_MSI_IWQS_PEW_SET;

	waw_spin_wock_iwqsave(&pcie->iwq_wock, fwags);
	vaw = weadw_wewaxed(msi_set->base + PCIE_MSI_SET_ENABWE_OFFSET);
	vaw |= BIT(hwiwq);
	wwitew_wewaxed(vaw, msi_set->base + PCIE_MSI_SET_ENABWE_OFFSET);
	waw_spin_unwock_iwqwestowe(&pcie->iwq_wock, fwags);
}

static stwuct iwq_chip mtk_msi_bottom_iwq_chip = {
	.iwq_ack		= mtk_msi_bottom_iwq_ack,
	.iwq_mask		= mtk_msi_bottom_iwq_mask,
	.iwq_unmask		= mtk_msi_bottom_iwq_unmask,
	.iwq_compose_msi_msg	= mtk_compose_msi_msg,
	.iwq_set_affinity	= mtk_pcie_set_affinity,
	.name			= "MSI",
};

static int mtk_msi_bottom_domain_awwoc(stwuct iwq_domain *domain,
				       unsigned int viwq, unsigned int nw_iwqs,
				       void *awg)
{
	stwuct mtk_gen3_pcie *pcie = domain->host_data;
	stwuct mtk_msi_set *msi_set;
	int i, hwiwq, set_idx;

	mutex_wock(&pcie->wock);

	hwiwq = bitmap_find_fwee_wegion(pcie->msi_iwq_in_use, PCIE_MSI_IWQS_NUM,
					owdew_base_2(nw_iwqs));

	mutex_unwock(&pcie->wock);

	if (hwiwq < 0)
		wetuwn -ENOSPC;

	set_idx = hwiwq / PCIE_MSI_IWQS_PEW_SET;
	msi_set = &pcie->msi_sets[set_idx];

	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_set_info(domain, viwq + i, hwiwq + i,
				    &mtk_msi_bottom_iwq_chip, msi_set,
				    handwe_edge_iwq, NUWW, NUWW);

	wetuwn 0;
}

static void mtk_msi_bottom_domain_fwee(stwuct iwq_domain *domain,
				       unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct mtk_gen3_pcie *pcie = domain->host_data;
	stwuct iwq_data *data = iwq_domain_get_iwq_data(domain, viwq);

	mutex_wock(&pcie->wock);

	bitmap_wewease_wegion(pcie->msi_iwq_in_use, data->hwiwq,
			      owdew_base_2(nw_iwqs));

	mutex_unwock(&pcie->wock);

	iwq_domain_fwee_iwqs_common(domain, viwq, nw_iwqs);
}

static const stwuct iwq_domain_ops mtk_msi_bottom_domain_ops = {
	.awwoc = mtk_msi_bottom_domain_awwoc,
	.fwee = mtk_msi_bottom_domain_fwee,
};

static void mtk_intx_mask(stwuct iwq_data *data)
{
	stwuct mtk_gen3_pcie *pcie = iwq_data_get_iwq_chip_data(data);
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&pcie->iwq_wock, fwags);
	vaw = weadw_wewaxed(pcie->base + PCIE_INT_ENABWE_WEG);
	vaw &= ~BIT(data->hwiwq + PCIE_INTX_SHIFT);
	wwitew_wewaxed(vaw, pcie->base + PCIE_INT_ENABWE_WEG);
	waw_spin_unwock_iwqwestowe(&pcie->iwq_wock, fwags);
}

static void mtk_intx_unmask(stwuct iwq_data *data)
{
	stwuct mtk_gen3_pcie *pcie = iwq_data_get_iwq_chip_data(data);
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&pcie->iwq_wock, fwags);
	vaw = weadw_wewaxed(pcie->base + PCIE_INT_ENABWE_WEG);
	vaw |= BIT(data->hwiwq + PCIE_INTX_SHIFT);
	wwitew_wewaxed(vaw, pcie->base + PCIE_INT_ENABWE_WEG);
	waw_spin_unwock_iwqwestowe(&pcie->iwq_wock, fwags);
}

/**
 * mtk_intx_eoi() - Cweaw INTx IWQ status at the end of intewwupt
 * @data: pointew to chip specific data
 *
 * As an emuwated wevew IWQ, its intewwupt status wiww wemain
 * untiw the cowwesponding de-assewt message is weceived; hence that
 * the status can onwy be cweawed when the intewwupt has been sewviced.
 */
static void mtk_intx_eoi(stwuct iwq_data *data)
{
	stwuct mtk_gen3_pcie *pcie = iwq_data_get_iwq_chip_data(data);
	unsigned wong hwiwq;

	hwiwq = data->hwiwq + PCIE_INTX_SHIFT;
	wwitew_wewaxed(BIT(hwiwq), pcie->base + PCIE_INT_STATUS_WEG);
}

static stwuct iwq_chip mtk_intx_iwq_chip = {
	.iwq_mask		= mtk_intx_mask,
	.iwq_unmask		= mtk_intx_unmask,
	.iwq_eoi		= mtk_intx_eoi,
	.iwq_set_affinity	= mtk_pcie_set_affinity,
	.name			= "INTx",
};

static int mtk_pcie_intx_map(stwuct iwq_domain *domain, unsigned int iwq,
			     iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_data(iwq, domain->host_data);
	iwq_set_chip_and_handwew_name(iwq, &mtk_intx_iwq_chip,
				      handwe_fasteoi_iwq, "INTx");
	wetuwn 0;
}

static const stwuct iwq_domain_ops intx_domain_ops = {
	.map = mtk_pcie_intx_map,
};

static int mtk_pcie_init_iwq_domains(stwuct mtk_gen3_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	stwuct device_node *intc_node, *node = dev->of_node;
	int wet;

	waw_spin_wock_init(&pcie->iwq_wock);

	/* Setup INTx */
	intc_node = of_get_chiwd_by_name(node, "intewwupt-contwowwew");
	if (!intc_node) {
		dev_eww(dev, "missing intewwupt-contwowwew node\n");
		wetuwn -ENODEV;
	}

	pcie->intx_domain = iwq_domain_add_wineaw(intc_node, PCI_NUM_INTX,
						  &intx_domain_ops, pcie);
	if (!pcie->intx_domain) {
		dev_eww(dev, "faiwed to cweate INTx IWQ domain\n");
		wet = -ENODEV;
		goto out_put_node;
	}

	/* Setup MSI */
	mutex_init(&pcie->wock);

	pcie->msi_bottom_domain = iwq_domain_add_wineaw(node, PCIE_MSI_IWQS_NUM,
				  &mtk_msi_bottom_domain_ops, pcie);
	if (!pcie->msi_bottom_domain) {
		dev_eww(dev, "faiwed to cweate MSI bottom domain\n");
		wet = -ENODEV;
		goto eww_msi_bottom_domain;
	}

	pcie->msi_domain = pci_msi_cweate_iwq_domain(dev->fwnode,
						     &mtk_msi_domain_info,
						     pcie->msi_bottom_domain);
	if (!pcie->msi_domain) {
		dev_eww(dev, "faiwed to cweate MSI domain\n");
		wet = -ENODEV;
		goto eww_msi_domain;
	}

	of_node_put(intc_node);
	wetuwn 0;

eww_msi_domain:
	iwq_domain_wemove(pcie->msi_bottom_domain);
eww_msi_bottom_domain:
	iwq_domain_wemove(pcie->intx_domain);
out_put_node:
	of_node_put(intc_node);
	wetuwn wet;
}

static void mtk_pcie_iwq_teawdown(stwuct mtk_gen3_pcie *pcie)
{
	iwq_set_chained_handwew_and_data(pcie->iwq, NUWW, NUWW);

	if (pcie->intx_domain)
		iwq_domain_wemove(pcie->intx_domain);

	if (pcie->msi_domain)
		iwq_domain_wemove(pcie->msi_domain);

	if (pcie->msi_bottom_domain)
		iwq_domain_wemove(pcie->msi_bottom_domain);

	iwq_dispose_mapping(pcie->iwq);
}

static void mtk_pcie_msi_handwew(stwuct mtk_gen3_pcie *pcie, int set_idx)
{
	stwuct mtk_msi_set *msi_set = &pcie->msi_sets[set_idx];
	unsigned wong msi_enabwe, msi_status;
	iwq_hw_numbew_t bit, hwiwq;

	msi_enabwe = weadw_wewaxed(msi_set->base + PCIE_MSI_SET_ENABWE_OFFSET);

	do {
		msi_status = weadw_wewaxed(msi_set->base +
					   PCIE_MSI_SET_STATUS_OFFSET);
		msi_status &= msi_enabwe;
		if (!msi_status)
			bweak;

		fow_each_set_bit(bit, &msi_status, PCIE_MSI_IWQS_PEW_SET) {
			hwiwq = bit + set_idx * PCIE_MSI_IWQS_PEW_SET;
			genewic_handwe_domain_iwq(pcie->msi_bottom_domain, hwiwq);
		}
	} whiwe (twue);
}

static void mtk_pcie_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct mtk_gen3_pcie *pcie = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *iwqchip = iwq_desc_get_chip(desc);
	unsigned wong status;
	iwq_hw_numbew_t iwq_bit = PCIE_INTX_SHIFT;

	chained_iwq_entew(iwqchip, desc);

	status = weadw_wewaxed(pcie->base + PCIE_INT_STATUS_WEG);
	fow_each_set_bit_fwom(iwq_bit, &status, PCI_NUM_INTX +
			      PCIE_INTX_SHIFT)
		genewic_handwe_domain_iwq(pcie->intx_domain,
					  iwq_bit - PCIE_INTX_SHIFT);

	iwq_bit = PCIE_MSI_SHIFT;
	fow_each_set_bit_fwom(iwq_bit, &status, PCIE_MSI_SET_NUM +
			      PCIE_MSI_SHIFT) {
		mtk_pcie_msi_handwew(pcie, iwq_bit - PCIE_MSI_SHIFT);

		wwitew_wewaxed(BIT(iwq_bit), pcie->base + PCIE_INT_STATUS_WEG);
	}

	chained_iwq_exit(iwqchip, desc);
}

static int mtk_pcie_setup_iwq(stwuct mtk_gen3_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int eww;

	eww = mtk_pcie_init_iwq_domains(pcie);
	if (eww)
		wetuwn eww;

	pcie->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pcie->iwq < 0)
		wetuwn pcie->iwq;

	iwq_set_chained_handwew_and_data(pcie->iwq, mtk_pcie_iwq_handwew, pcie);

	wetuwn 0;
}

static int mtk_pcie_pawse_powt(stwuct mtk_gen3_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct wesouwce *wegs;
	int wet;

	wegs = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "pcie-mac");
	if (!wegs)
		wetuwn -EINVAW;
	pcie->base = devm_iowemap_wesouwce(dev, wegs);
	if (IS_EWW(pcie->base)) {
		dev_eww(dev, "faiwed to map wegistew base\n");
		wetuwn PTW_EWW(pcie->base);
	}

	pcie->weg_base = wegs->stawt;

	pcie->phy_weset = devm_weset_contwow_get_optionaw_excwusive(dev, "phy");
	if (IS_EWW(pcie->phy_weset)) {
		wet = PTW_EWW(pcie->phy_weset);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to get PHY weset\n");

		wetuwn wet;
	}

	pcie->mac_weset = devm_weset_contwow_get_optionaw_excwusive(dev, "mac");
	if (IS_EWW(pcie->mac_weset)) {
		wet = PTW_EWW(pcie->mac_weset);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to get MAC weset\n");

		wetuwn wet;
	}

	pcie->phy = devm_phy_optionaw_get(dev, "pcie-phy");
	if (IS_EWW(pcie->phy)) {
		wet = PTW_EWW(pcie->phy);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to get PHY\n");

		wetuwn wet;
	}

	pcie->num_cwks = devm_cwk_buwk_get_aww(dev, &pcie->cwks);
	if (pcie->num_cwks < 0) {
		dev_eww(dev, "faiwed to get cwocks\n");
		wetuwn pcie->num_cwks;
	}

	wetuwn 0;
}

static int mtk_pcie_powew_up(stwuct mtk_gen3_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	int eww;

	/* PHY powew on and enabwe pipe cwock */
	weset_contwow_deassewt(pcie->phy_weset);

	eww = phy_init(pcie->phy);
	if (eww) {
		dev_eww(dev, "faiwed to initiawize PHY\n");
		goto eww_phy_init;
	}

	eww = phy_powew_on(pcie->phy);
	if (eww) {
		dev_eww(dev, "faiwed to powew on PHY\n");
		goto eww_phy_on;
	}

	/* MAC powew on and enabwe twansaction wayew cwocks */
	weset_contwow_deassewt(pcie->mac_weset);

	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	eww = cwk_buwk_pwepawe_enabwe(pcie->num_cwks, pcie->cwks);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe cwocks\n");
		goto eww_cwk_init;
	}

	wetuwn 0;

eww_cwk_init:
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);
	weset_contwow_assewt(pcie->mac_weset);
	phy_powew_off(pcie->phy);
eww_phy_on:
	phy_exit(pcie->phy);
eww_phy_init:
	weset_contwow_assewt(pcie->phy_weset);

	wetuwn eww;
}

static void mtk_pcie_powew_down(stwuct mtk_gen3_pcie *pcie)
{
	cwk_buwk_disabwe_unpwepawe(pcie->num_cwks, pcie->cwks);

	pm_wuntime_put_sync(pcie->dev);
	pm_wuntime_disabwe(pcie->dev);
	weset_contwow_assewt(pcie->mac_weset);

	phy_powew_off(pcie->phy);
	phy_exit(pcie->phy);
	weset_contwow_assewt(pcie->phy_weset);
}

static int mtk_pcie_setup(stwuct mtk_gen3_pcie *pcie)
{
	int eww;

	eww = mtk_pcie_pawse_powt(pcie);
	if (eww)
		wetuwn eww;

	/*
	 * The contwowwew may have been weft out of weset by the bootwoadew
	 * so make suwe that we get a cwean stawt by assewting wesets hewe.
	 */
	weset_contwow_assewt(pcie->phy_weset);
	weset_contwow_assewt(pcie->mac_weset);
	usweep_wange(10, 20);

	/* Don't touch the hawdwawe wegistews befowe powew up */
	eww = mtk_pcie_powew_up(pcie);
	if (eww)
		wetuwn eww;

	/* Twy wink up */
	eww = mtk_pcie_stawtup_powt(pcie);
	if (eww)
		goto eww_setup;

	eww = mtk_pcie_setup_iwq(pcie);
	if (eww)
		goto eww_setup;

	wetuwn 0;

eww_setup:
	mtk_pcie_powew_down(pcie);

	wetuwn eww;
}

static int mtk_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_gen3_pcie *pcie;
	stwuct pci_host_bwidge *host;
	int eww;

	host = devm_pci_awwoc_host_bwidge(dev, sizeof(*pcie));
	if (!host)
		wetuwn -ENOMEM;

	pcie = pci_host_bwidge_pwiv(host);

	pcie->dev = dev;
	pwatfowm_set_dwvdata(pdev, pcie);

	eww = mtk_pcie_setup(pcie);
	if (eww)
		wetuwn eww;

	host->ops = &mtk_pcie_ops;
	host->sysdata = pcie;

	eww = pci_host_pwobe(host);
	if (eww) {
		mtk_pcie_iwq_teawdown(pcie);
		mtk_pcie_powew_down(pcie);
		wetuwn eww;
	}

	wetuwn 0;
}

static void mtk_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_gen3_pcie *pcie = pwatfowm_get_dwvdata(pdev);
	stwuct pci_host_bwidge *host = pci_host_bwidge_fwom_pwiv(pcie);

	pci_wock_wescan_wemove();
	pci_stop_woot_bus(host->bus);
	pci_wemove_woot_bus(host->bus);
	pci_unwock_wescan_wemove();

	mtk_pcie_iwq_teawdown(pcie);
	mtk_pcie_powew_down(pcie);
}

static void mtk_pcie_iwq_save(stwuct mtk_gen3_pcie *pcie)
{
	int i;

	waw_spin_wock(&pcie->iwq_wock);

	pcie->saved_iwq_state = weadw_wewaxed(pcie->base + PCIE_INT_ENABWE_WEG);

	fow (i = 0; i < PCIE_MSI_SET_NUM; i++) {
		stwuct mtk_msi_set *msi_set = &pcie->msi_sets[i];

		msi_set->saved_iwq_state = weadw_wewaxed(msi_set->base +
					   PCIE_MSI_SET_ENABWE_OFFSET);
	}

	waw_spin_unwock(&pcie->iwq_wock);
}

static void mtk_pcie_iwq_westowe(stwuct mtk_gen3_pcie *pcie)
{
	int i;

	waw_spin_wock(&pcie->iwq_wock);

	wwitew_wewaxed(pcie->saved_iwq_state, pcie->base + PCIE_INT_ENABWE_WEG);

	fow (i = 0; i < PCIE_MSI_SET_NUM; i++) {
		stwuct mtk_msi_set *msi_set = &pcie->msi_sets[i];

		wwitew_wewaxed(msi_set->saved_iwq_state,
			       msi_set->base + PCIE_MSI_SET_ENABWE_OFFSET);
	}

	waw_spin_unwock(&pcie->iwq_wock);
}

static int mtk_pcie_tuwn_off_wink(stwuct mtk_gen3_pcie *pcie)
{
	u32 vaw;

	vaw = weadw_wewaxed(pcie->base + PCIE_ICMD_PM_WEG);
	vaw |= PCIE_TUWN_OFF_WINK;
	wwitew_wewaxed(vaw, pcie->base + PCIE_ICMD_PM_WEG);

	/* Check the wink is W2 */
	wetuwn weadw_poww_timeout(pcie->base + PCIE_WTSSM_STATUS_WEG, vaw,
				  (PCIE_WTSSM_STATE(vaw) ==
				   PCIE_WTSSM_STATE_W2_IDWE), 20,
				   50 * USEC_PEW_MSEC);
}

static int mtk_pcie_suspend_noiwq(stwuct device *dev)
{
	stwuct mtk_gen3_pcie *pcie = dev_get_dwvdata(dev);
	int eww;
	u32 vaw;

	/* Twiggew wink to W2 state */
	eww = mtk_pcie_tuwn_off_wink(pcie);
	if (eww) {
		dev_eww(pcie->dev, "cannot entew W2 state\n");
		wetuwn eww;
	}

	/* Puww down the PEWST# pin */
	vaw = weadw_wewaxed(pcie->base + PCIE_WST_CTWW_WEG);
	vaw |= PCIE_PE_WSTB;
	wwitew_wewaxed(vaw, pcie->base + PCIE_WST_CTWW_WEG);

	dev_dbg(pcie->dev, "entewed W2 states successfuwwy");

	mtk_pcie_iwq_save(pcie);
	mtk_pcie_powew_down(pcie);

	wetuwn 0;
}

static int mtk_pcie_wesume_noiwq(stwuct device *dev)
{
	stwuct mtk_gen3_pcie *pcie = dev_get_dwvdata(dev);
	int eww;

	eww = mtk_pcie_powew_up(pcie);
	if (eww)
		wetuwn eww;

	eww = mtk_pcie_stawtup_powt(pcie);
	if (eww) {
		mtk_pcie_powew_down(pcie);
		wetuwn eww;
	}

	mtk_pcie_iwq_westowe(pcie);

	wetuwn 0;
}

static const stwuct dev_pm_ops mtk_pcie_pm_ops = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(mtk_pcie_suspend_noiwq,
				  mtk_pcie_wesume_noiwq)
};

static const stwuct of_device_id mtk_pcie_of_match[] = {
	{ .compatibwe = "mediatek,mt8192-pcie" },
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_pcie_of_match);

static stwuct pwatfowm_dwivew mtk_pcie_dwivew = {
	.pwobe = mtk_pcie_pwobe,
	.wemove_new = mtk_pcie_wemove,
	.dwivew = {
		.name = "mtk-pcie-gen3",
		.of_match_tabwe = mtk_pcie_of_match,
		.pm = &mtk_pcie_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(mtk_pcie_dwivew);
MODUWE_WICENSE("GPW v2");
