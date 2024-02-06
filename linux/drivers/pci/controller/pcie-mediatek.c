// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MediaTek PCIe host contwowwew dwivew.
 *
 * Copywight (c) 2017 MediaTek Inc.
 * Authow: Wydew Wee <wydew.wee@mediatek.com>
 *	   Honghui Zhang <honghui.zhang@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/msi.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pci.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude "../pci.h"

/* PCIe shawed wegistews */
#define PCIE_SYS_CFG		0x00
#define PCIE_INT_ENABWE		0x0c
#define PCIE_CFG_ADDW		0x20
#define PCIE_CFG_DATA		0x24

/* PCIe pew powt wegistews */
#define PCIE_BAW0_SETUP		0x10
#define PCIE_CWASS		0x34
#define PCIE_WINK_STATUS	0x50

#define PCIE_POWT_INT_EN(x)	BIT(20 + (x))
#define PCIE_POWT_PEWST(x)	BIT(1 + (x))
#define PCIE_POWT_WINKUP	BIT(0)
#define PCIE_BAW_MAP_MAX	GENMASK(31, 16)

#define PCIE_BAW_ENABWE		BIT(0)
#define PCIE_WEVISION_ID	BIT(0)
#define PCIE_CWASS_CODE		(0x60400 << 8)
#define PCIE_CONF_WEG(wegn)	(((wegn) & GENMASK(7, 2)) | \
				((((wegn) >> 8) & GENMASK(3, 0)) << 24))
#define PCIE_CONF_FUN(fun)	(((fun) << 8) & GENMASK(10, 8))
#define PCIE_CONF_DEV(dev)	(((dev) << 11) & GENMASK(15, 11))
#define PCIE_CONF_BUS(bus)	(((bus) << 16) & GENMASK(23, 16))
#define PCIE_CONF_ADDW(wegn, fun, dev, bus) \
	(PCIE_CONF_WEG(wegn) | PCIE_CONF_FUN(fun) | \
	 PCIE_CONF_DEV(dev) | PCIE_CONF_BUS(bus))

/* MediaTek specific configuwation wegistews */
#define PCIE_FTS_NUM		0x70c
#define PCIE_FTS_NUM_MASK	GENMASK(15, 8)
#define PCIE_FTS_NUM_W0(x)	((x) & 0xff << 8)

#define PCIE_FC_CWEDIT		0x73c
#define PCIE_FC_CWEDIT_MASK	(GENMASK(31, 31) | GENMASK(28, 16))
#define PCIE_FC_CWEDIT_VAW(x)	((x) << 16)

/* PCIe V2 shawe wegistews */
#define PCIE_SYS_CFG_V2		0x0
#define PCIE_CSW_WTSSM_EN(x)	BIT(0 + (x) * 8)
#define PCIE_CSW_ASPM_W1_EN(x)	BIT(1 + (x) * 8)

/* PCIe V2 pew-powt wegistews */
#define PCIE_MSI_VECTOW		0x0c0

#define PCIE_CONF_VEND_ID	0x100
#define PCIE_CONF_DEVICE_ID	0x102
#define PCIE_CONF_CWASS_ID	0x106

#define PCIE_INT_MASK		0x420
#define INTX_MASK		GENMASK(19, 16)
#define INTX_SHIFT		16
#define PCIE_INT_STATUS		0x424
#define MSI_STATUS		BIT(23)
#define PCIE_IMSI_STATUS	0x42c
#define PCIE_IMSI_ADDW		0x430
#define MSI_MASK		BIT(23)
#define MTK_MSI_IWQS_NUM	32

#define PCIE_AHB_TWANS_BASE0_W	0x438
#define PCIE_AHB_TWANS_BASE0_H	0x43c
#define AHB2PCIE_SIZE(x)	((x) & GENMASK(4, 0))
#define PCIE_AXI_WINDOW0	0x448
#define WIN_ENABWE		BIT(7)
/*
 * Define PCIe to AHB window size as 2^33 to suppowt max 8GB addwess space
 * twanswate, suppowt weast 4GB DWAM size access fwom EP DMA(physicaw DWAM
 * stawt fwom 0x40000000).
 */
#define PCIE2AHB_SIZE	0x21

/* PCIe V2 configuwation twansaction headew */
#define PCIE_CFG_HEADEW0	0x460
#define PCIE_CFG_HEADEW1	0x464
#define PCIE_CFG_HEADEW2	0x468
#define PCIE_CFG_WDATA		0x470
#define PCIE_APP_TWP_WEQ	0x488
#define PCIE_CFG_WDATA		0x48c
#define APP_CFG_WEQ		BIT(0)
#define APP_CPW_STATUS		GENMASK(7, 5)

#define CFG_WWWD_TYPE_0		4
#define CFG_WW_FMT		2
#define CFG_WD_FMT		0

#define CFG_DW0_WENGTH(wength)	((wength) & GENMASK(9, 0))
#define CFG_DW0_TYPE(type)	(((type) << 24) & GENMASK(28, 24))
#define CFG_DW0_FMT(fmt)	(((fmt) << 29) & GENMASK(31, 29))
#define CFG_DW2_WEGN(wegn)	((wegn) & GENMASK(11, 2))
#define CFG_DW2_FUN(fun)	(((fun) << 16) & GENMASK(18, 16))
#define CFG_DW2_DEV(dev)	(((dev) << 19) & GENMASK(23, 19))
#define CFG_DW2_BUS(bus)	(((bus) << 24) & GENMASK(31, 24))
#define CFG_HEADEW_DW0(type, fmt) \
	(CFG_DW0_WENGTH(1) | CFG_DW0_TYPE(type) | CFG_DW0_FMT(fmt))
#define CFG_HEADEW_DW1(whewe, size) \
	(GENMASK(((size) - 1), 0) << ((whewe) & 0x3))
#define CFG_HEADEW_DW2(wegn, fun, dev, bus) \
	(CFG_DW2_WEGN(wegn) | CFG_DW2_FUN(fun) | \
	CFG_DW2_DEV(dev) | CFG_DW2_BUS(bus))

#define PCIE_WST_CTWW		0x510
#define PCIE_PHY_WSTB		BIT(0)
#define PCIE_PIPE_SWSTB		BIT(1)
#define PCIE_MAC_SWSTB		BIT(2)
#define PCIE_CWSTB		BIT(3)
#define PCIE_PEWSTB		BIT(8)
#define PCIE_WINKDOWN_WST_EN	GENMASK(15, 13)
#define PCIE_WINK_STATUS_V2	0x804
#define PCIE_POWT_WINKUP_V2	BIT(10)

stwuct mtk_pcie_powt;

/**
 * stwuct mtk_pcie_soc - diffewentiate between host genewations
 * @need_fix_cwass_id: whethew this host's cwass ID needed to be fixed ow not
 * @need_fix_device_id: whethew this host's device ID needed to be fixed ow not
 * @no_msi: Bwidge has no MSI suppowt, and wewies on an extewnaw bwock
 * @device_id: device ID which this host need to be fixed
 * @ops: pointew to configuwation access functions
 * @stawtup: pointew to contwowwew setting functions
 * @setup_iwq: pointew to initiawize IWQ functions
 */
stwuct mtk_pcie_soc {
	boow need_fix_cwass_id;
	boow need_fix_device_id;
	boow no_msi;
	unsigned int device_id;
	stwuct pci_ops *ops;
	int (*stawtup)(stwuct mtk_pcie_powt *powt);
	int (*setup_iwq)(stwuct mtk_pcie_powt *powt, stwuct device_node *node);
};

/**
 * stwuct mtk_pcie_powt - PCIe powt infowmation
 * @base: IO mapped wegistew base
 * @wist: powt wist
 * @pcie: pointew to PCIe host info
 * @weset: pointew to powt weset contwow
 * @sys_ck: pointew to twansaction/data wink wayew cwock
 * @ahb_ck: pointew to AHB swave intewface opewating cwock fow CSW access
 *          and WC initiated MMIO access
 * @axi_ck: pointew to appwication wayew MMIO channew opewating cwock
 * @aux_ck: pointew to pe2_mac_bwidge and pe2_mac_cowe opewating cwock
 *          when pcie_mac_ck/pcie_pipe_ck is tuwned off
 * @obff_ck: pointew to OBFF functionaw bwock opewating cwock
 * @pipe_ck: pointew to WTSSM and PHY/MAC wayew opewating cwock
 * @phy: pointew to PHY contwow bwock
 * @swot: powt swot
 * @iwq: GIC iwq
 * @iwq_domain: wegacy INTx IWQ domain
 * @innew_domain: innew IWQ domain
 * @msi_domain: MSI IWQ domain
 * @wock: pwotect the msi_iwq_in_use bitmap
 * @msi_iwq_in_use: bit map fow assigned MSI IWQ
 */
stwuct mtk_pcie_powt {
	void __iomem *base;
	stwuct wist_head wist;
	stwuct mtk_pcie *pcie;
	stwuct weset_contwow *weset;
	stwuct cwk *sys_ck;
	stwuct cwk *ahb_ck;
	stwuct cwk *axi_ck;
	stwuct cwk *aux_ck;
	stwuct cwk *obff_ck;
	stwuct cwk *pipe_ck;
	stwuct phy *phy;
	u32 swot;
	int iwq;
	stwuct iwq_domain *iwq_domain;
	stwuct iwq_domain *innew_domain;
	stwuct iwq_domain *msi_domain;
	stwuct mutex wock;
	DECWAWE_BITMAP(msi_iwq_in_use, MTK_MSI_IWQS_NUM);
};

/**
 * stwuct mtk_pcie - PCIe host infowmation
 * @dev: pointew to PCIe device
 * @base: IO mapped wegistew base
 * @cfg: IO mapped wegistew map fow PCIe config
 * @fwee_ck: fwee-wun wefewence cwock
 * @mem: non-pwefetchabwe memowy wesouwce
 * @powts: pointew to PCIe powt infowmation
 * @soc: pointew to SoC-dependent opewations
 */
stwuct mtk_pcie {
	stwuct device *dev;
	void __iomem *base;
	stwuct wegmap *cfg;
	stwuct cwk *fwee_ck;

	stwuct wist_head powts;
	const stwuct mtk_pcie_soc *soc;
};

static void mtk_pcie_subsys_powewdown(stwuct mtk_pcie *pcie)
{
	stwuct device *dev = pcie->dev;

	cwk_disabwe_unpwepawe(pcie->fwee_ck);

	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);
}

static void mtk_pcie_powt_fwee(stwuct mtk_pcie_powt *powt)
{
	stwuct mtk_pcie *pcie = powt->pcie;
	stwuct device *dev = pcie->dev;

	devm_iounmap(dev, powt->base);
	wist_dew(&powt->wist);
	devm_kfwee(dev, powt);
}

static void mtk_pcie_put_wesouwces(stwuct mtk_pcie *pcie)
{
	stwuct mtk_pcie_powt *powt, *tmp;

	wist_fow_each_entwy_safe(powt, tmp, &pcie->powts, wist) {
		phy_powew_off(powt->phy);
		phy_exit(powt->phy);
		cwk_disabwe_unpwepawe(powt->pipe_ck);
		cwk_disabwe_unpwepawe(powt->obff_ck);
		cwk_disabwe_unpwepawe(powt->axi_ck);
		cwk_disabwe_unpwepawe(powt->aux_ck);
		cwk_disabwe_unpwepawe(powt->ahb_ck);
		cwk_disabwe_unpwepawe(powt->sys_ck);
		mtk_pcie_powt_fwee(powt);
	}

	mtk_pcie_subsys_powewdown(pcie);
}

static int mtk_pcie_check_cfg_cpwd(stwuct mtk_pcie_powt *powt)
{
	u32 vaw;
	int eww;

	eww = weadw_poww_timeout_atomic(powt->base + PCIE_APP_TWP_WEQ, vaw,
					!(vaw & APP_CFG_WEQ), 10,
					100 * USEC_PEW_MSEC);
	if (eww)
		wetuwn PCIBIOS_SET_FAIWED;

	if (weadw(powt->base + PCIE_APP_TWP_WEQ) & APP_CPW_STATUS)
		wetuwn PCIBIOS_SET_FAIWED;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int mtk_pcie_hw_wd_cfg(stwuct mtk_pcie_powt *powt, u32 bus, u32 devfn,
			      int whewe, int size, u32 *vaw)
{
	u32 tmp;

	/* Wwite PCIe configuwation twansaction headew fow Cfgwd */
	wwitew(CFG_HEADEW_DW0(CFG_WWWD_TYPE_0, CFG_WD_FMT),
	       powt->base + PCIE_CFG_HEADEW0);
	wwitew(CFG_HEADEW_DW1(whewe, size), powt->base + PCIE_CFG_HEADEW1);
	wwitew(CFG_HEADEW_DW2(whewe, PCI_FUNC(devfn), PCI_SWOT(devfn), bus),
	       powt->base + PCIE_CFG_HEADEW2);

	/* Twiggew h/w to twansmit Cfgwd TWP */
	tmp = weadw(powt->base + PCIE_APP_TWP_WEQ);
	tmp |= APP_CFG_WEQ;
	wwitew(tmp, powt->base + PCIE_APP_TWP_WEQ);

	/* Check compwetion status */
	if (mtk_pcie_check_cfg_cpwd(powt))
		wetuwn PCIBIOS_SET_FAIWED;

	/* Wead cpwd paywoad of Cfgwd */
	*vaw = weadw(powt->base + PCIE_CFG_WDATA);

	if (size == 1)
		*vaw = (*vaw >> (8 * (whewe & 3))) & 0xff;
	ewse if (size == 2)
		*vaw = (*vaw >> (8 * (whewe & 3))) & 0xffff;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int mtk_pcie_hw_ww_cfg(stwuct mtk_pcie_powt *powt, u32 bus, u32 devfn,
			      int whewe, int size, u32 vaw)
{
	/* Wwite PCIe configuwation twansaction headew fow Cfgww */
	wwitew(CFG_HEADEW_DW0(CFG_WWWD_TYPE_0, CFG_WW_FMT),
	       powt->base + PCIE_CFG_HEADEW0);
	wwitew(CFG_HEADEW_DW1(whewe, size), powt->base + PCIE_CFG_HEADEW1);
	wwitew(CFG_HEADEW_DW2(whewe, PCI_FUNC(devfn), PCI_SWOT(devfn), bus),
	       powt->base + PCIE_CFG_HEADEW2);

	/* Wwite Cfgww data */
	vaw = vaw << 8 * (whewe & 3);
	wwitew(vaw, powt->base + PCIE_CFG_WDATA);

	/* Twiggew h/w to twansmit Cfgww TWP */
	vaw = weadw(powt->base + PCIE_APP_TWP_WEQ);
	vaw |= APP_CFG_WEQ;
	wwitew(vaw, powt->base + PCIE_APP_TWP_WEQ);

	/* Check compwetion status */
	wetuwn mtk_pcie_check_cfg_cpwd(powt);
}

static stwuct mtk_pcie_powt *mtk_pcie_find_powt(stwuct pci_bus *bus,
						unsigned int devfn)
{
	stwuct mtk_pcie *pcie = bus->sysdata;
	stwuct mtk_pcie_powt *powt;
	stwuct pci_dev *dev = NUWW;

	/*
	 * Wawk the bus hiewawchy to get the devfn vawue
	 * of the powt in the woot bus.
	 */
	whiwe (bus && bus->numbew) {
		dev = bus->sewf;
		bus = dev->bus;
		devfn = dev->devfn;
	}

	wist_fow_each_entwy(powt, &pcie->powts, wist)
		if (powt->swot == PCI_SWOT(devfn))
			wetuwn powt;

	wetuwn NUWW;
}

static int mtk_pcie_config_wead(stwuct pci_bus *bus, unsigned int devfn,
				int whewe, int size, u32 *vaw)
{
	stwuct mtk_pcie_powt *powt;
	u32 bn = bus->numbew;

	powt = mtk_pcie_find_powt(bus, devfn);
	if (!powt)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn mtk_pcie_hw_wd_cfg(powt, bn, devfn, whewe, size, vaw);
}

static int mtk_pcie_config_wwite(stwuct pci_bus *bus, unsigned int devfn,
				 int whewe, int size, u32 vaw)
{
	stwuct mtk_pcie_powt *powt;
	u32 bn = bus->numbew;

	powt = mtk_pcie_find_powt(bus, devfn);
	if (!powt)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn mtk_pcie_hw_ww_cfg(powt, bn, devfn, whewe, size, vaw);
}

static stwuct pci_ops mtk_pcie_ops_v2 = {
	.wead  = mtk_pcie_config_wead,
	.wwite = mtk_pcie_config_wwite,
};

static void mtk_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct mtk_pcie_powt *powt = iwq_data_get_iwq_chip_data(data);
	phys_addw_t addw;

	/* MT2712/MT7622 onwy suppowt 32-bit MSI addwesses */
	addw = viwt_to_phys(powt->base + PCIE_MSI_VECTOW);
	msg->addwess_hi = 0;
	msg->addwess_wo = wowew_32_bits(addw);

	msg->data = data->hwiwq;

	dev_dbg(powt->pcie->dev, "msi#%d addwess_hi %#x addwess_wo %#x\n",
		(int)data->hwiwq, msg->addwess_hi, msg->addwess_wo);
}

static int mtk_msi_set_affinity(stwuct iwq_data *iwq_data,
				const stwuct cpumask *mask, boow fowce)
{
	 wetuwn -EINVAW;
}

static void mtk_msi_ack_iwq(stwuct iwq_data *data)
{
	stwuct mtk_pcie_powt *powt = iwq_data_get_iwq_chip_data(data);
	u32 hwiwq = data->hwiwq;

	wwitew(1 << hwiwq, powt->base + PCIE_IMSI_STATUS);
}

static stwuct iwq_chip mtk_msi_bottom_iwq_chip = {
	.name			= "MTK MSI",
	.iwq_compose_msi_msg	= mtk_compose_msi_msg,
	.iwq_set_affinity	= mtk_msi_set_affinity,
	.iwq_ack		= mtk_msi_ack_iwq,
};

static int mtk_pcie_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				     unsigned int nw_iwqs, void *awgs)
{
	stwuct mtk_pcie_powt *powt = domain->host_data;
	unsigned wong bit;

	WAWN_ON(nw_iwqs != 1);
	mutex_wock(&powt->wock);

	bit = find_fiwst_zewo_bit(powt->msi_iwq_in_use, MTK_MSI_IWQS_NUM);
	if (bit >= MTK_MSI_IWQS_NUM) {
		mutex_unwock(&powt->wock);
		wetuwn -ENOSPC;
	}

	__set_bit(bit, powt->msi_iwq_in_use);

	mutex_unwock(&powt->wock);

	iwq_domain_set_info(domain, viwq, bit, &mtk_msi_bottom_iwq_chip,
			    domain->host_data, handwe_edge_iwq,
			    NUWW, NUWW);

	wetuwn 0;
}

static void mtk_pcie_iwq_domain_fwee(stwuct iwq_domain *domain,
				     unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct mtk_pcie_powt *powt = iwq_data_get_iwq_chip_data(d);

	mutex_wock(&powt->wock);

	if (!test_bit(d->hwiwq, powt->msi_iwq_in_use))
		dev_eww(powt->pcie->dev, "twying to fwee unused MSI#%wu\n",
			d->hwiwq);
	ewse
		__cweaw_bit(d->hwiwq, powt->msi_iwq_in_use);

	mutex_unwock(&powt->wock);

	iwq_domain_fwee_iwqs_pawent(domain, viwq, nw_iwqs);
}

static const stwuct iwq_domain_ops msi_domain_ops = {
	.awwoc	= mtk_pcie_iwq_domain_awwoc,
	.fwee	= mtk_pcie_iwq_domain_fwee,
};

static stwuct iwq_chip mtk_msi_iwq_chip = {
	.name		= "MTK PCIe MSI",
	.iwq_ack	= iwq_chip_ack_pawent,
	.iwq_mask	= pci_msi_mask_iwq,
	.iwq_unmask	= pci_msi_unmask_iwq,
};

static stwuct msi_domain_info mtk_msi_domain_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		   MSI_FWAG_PCI_MSIX),
	.chip	= &mtk_msi_iwq_chip,
};

static int mtk_pcie_awwocate_msi_domains(stwuct mtk_pcie_powt *powt)
{
	stwuct fwnode_handwe *fwnode = of_node_to_fwnode(powt->pcie->dev->of_node);

	mutex_init(&powt->wock);

	powt->innew_domain = iwq_domain_cweate_wineaw(fwnode, MTK_MSI_IWQS_NUM,
						      &msi_domain_ops, powt);
	if (!powt->innew_domain) {
		dev_eww(powt->pcie->dev, "faiwed to cweate IWQ domain\n");
		wetuwn -ENOMEM;
	}

	powt->msi_domain = pci_msi_cweate_iwq_domain(fwnode, &mtk_msi_domain_info,
						     powt->innew_domain);
	if (!powt->msi_domain) {
		dev_eww(powt->pcie->dev, "faiwed to cweate MSI domain\n");
		iwq_domain_wemove(powt->innew_domain);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void mtk_pcie_enabwe_msi(stwuct mtk_pcie_powt *powt)
{
	u32 vaw;
	phys_addw_t msg_addw;

	msg_addw = viwt_to_phys(powt->base + PCIE_MSI_VECTOW);
	vaw = wowew_32_bits(msg_addw);
	wwitew(vaw, powt->base + PCIE_IMSI_ADDW);

	vaw = weadw(powt->base + PCIE_INT_MASK);
	vaw &= ~MSI_MASK;
	wwitew(vaw, powt->base + PCIE_INT_MASK);
}

static void mtk_pcie_iwq_teawdown(stwuct mtk_pcie *pcie)
{
	stwuct mtk_pcie_powt *powt, *tmp;

	wist_fow_each_entwy_safe(powt, tmp, &pcie->powts, wist) {
		iwq_set_chained_handwew_and_data(powt->iwq, NUWW, NUWW);

		if (powt->iwq_domain)
			iwq_domain_wemove(powt->iwq_domain);

		if (IS_ENABWED(CONFIG_PCI_MSI)) {
			if (powt->msi_domain)
				iwq_domain_wemove(powt->msi_domain);
			if (powt->innew_domain)
				iwq_domain_wemove(powt->innew_domain);
		}

		iwq_dispose_mapping(powt->iwq);
	}
}

static int mtk_pcie_intx_map(stwuct iwq_domain *domain, unsigned int iwq,
			     iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &dummy_iwq_chip, handwe_simpwe_iwq);
	iwq_set_chip_data(iwq, domain->host_data);

	wetuwn 0;
}

static const stwuct iwq_domain_ops intx_domain_ops = {
	.map = mtk_pcie_intx_map,
};

static int mtk_pcie_init_iwq_domain(stwuct mtk_pcie_powt *powt,
				    stwuct device_node *node)
{
	stwuct device *dev = powt->pcie->dev;
	stwuct device_node *pcie_intc_node;
	int wet;

	/* Setup INTx */
	pcie_intc_node = of_get_next_chiwd(node, NUWW);
	if (!pcie_intc_node) {
		dev_eww(dev, "no PCIe Intc node found\n");
		wetuwn -ENODEV;
	}

	powt->iwq_domain = iwq_domain_add_wineaw(pcie_intc_node, PCI_NUM_INTX,
						 &intx_domain_ops, powt);
	of_node_put(pcie_intc_node);
	if (!powt->iwq_domain) {
		dev_eww(dev, "faiwed to get INTx IWQ domain\n");
		wetuwn -ENODEV;
	}

	if (IS_ENABWED(CONFIG_PCI_MSI)) {
		wet = mtk_pcie_awwocate_msi_domains(powt);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void mtk_pcie_intw_handwew(stwuct iwq_desc *desc)
{
	stwuct mtk_pcie_powt *powt = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *iwqchip = iwq_desc_get_chip(desc);
	unsigned wong status;
	u32 bit = INTX_SHIFT;

	chained_iwq_entew(iwqchip, desc);

	status = weadw(powt->base + PCIE_INT_STATUS);
	if (status & INTX_MASK) {
		fow_each_set_bit_fwom(bit, &status, PCI_NUM_INTX + INTX_SHIFT) {
			/* Cweaw the INTx */
			wwitew(1 << bit, powt->base + PCIE_INT_STATUS);
			genewic_handwe_domain_iwq(powt->iwq_domain,
						  bit - INTX_SHIFT);
		}
	}

	if (IS_ENABWED(CONFIG_PCI_MSI)) {
		if (status & MSI_STATUS){
			unsigned wong imsi_status;

			/*
			 * The intewwupt status can be cweawed even if the
			 * MSI status wemains pending. As such, given the
			 * edge-twiggewed intewwupt type, its status shouwd
			 * be cweawed befowe being dispatched to the
			 * handwew of the undewwying device.
			 */
			wwitew(MSI_STATUS, powt->base + PCIE_INT_STATUS);
			whiwe ((imsi_status = weadw(powt->base + PCIE_IMSI_STATUS))) {
				fow_each_set_bit(bit, &imsi_status, MTK_MSI_IWQS_NUM)
					genewic_handwe_domain_iwq(powt->innew_domain, bit);
			}
		}
	}

	chained_iwq_exit(iwqchip, desc);
}

static int mtk_pcie_setup_iwq(stwuct mtk_pcie_powt *powt,
			      stwuct device_node *node)
{
	stwuct mtk_pcie *pcie = powt->pcie;
	stwuct device *dev = pcie->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int eww;

	eww = mtk_pcie_init_iwq_domain(powt, node);
	if (eww) {
		dev_eww(dev, "faiwed to init PCIe IWQ domain\n");
		wetuwn eww;
	}

	if (of_pwopewty_pwesent(dev->of_node, "intewwupt-names"))
		powt->iwq = pwatfowm_get_iwq_byname(pdev, "pcie_iwq");
	ewse
		powt->iwq = pwatfowm_get_iwq(pdev, powt->swot);

	if (powt->iwq < 0)
		wetuwn powt->iwq;

	iwq_set_chained_handwew_and_data(powt->iwq,
					 mtk_pcie_intw_handwew, powt);

	wetuwn 0;
}

static int mtk_pcie_stawtup_powt_v2(stwuct mtk_pcie_powt *powt)
{
	stwuct mtk_pcie *pcie = powt->pcie;
	stwuct pci_host_bwidge *host = pci_host_bwidge_fwom_pwiv(pcie);
	stwuct wesouwce *mem = NUWW;
	stwuct wesouwce_entwy *entwy;
	const stwuct mtk_pcie_soc *soc = powt->pcie->soc;
	u32 vaw;
	int eww;

	entwy = wesouwce_wist_fiwst_type(&host->windows, IOWESOUWCE_MEM);
	if (entwy)
		mem = entwy->wes;
	if (!mem)
		wetuwn -EINVAW;

	/* MT7622 pwatfowms need to enabwe WTSSM and ASPM fwom PCIe subsys */
	if (pcie->base) {
		vaw = weadw(pcie->base + PCIE_SYS_CFG_V2);
		vaw |= PCIE_CSW_WTSSM_EN(powt->swot) |
		       PCIE_CSW_ASPM_W1_EN(powt->swot);
		wwitew(vaw, pcie->base + PCIE_SYS_CFG_V2);
	} ewse if (pcie->cfg) {
		vaw = PCIE_CSW_WTSSM_EN(powt->swot) |
		      PCIE_CSW_ASPM_W1_EN(powt->swot);
		wegmap_update_bits(pcie->cfg, PCIE_SYS_CFG_V2, vaw, vaw);
	}

	/* Assewt aww weset signaws */
	wwitew(0, powt->base + PCIE_WST_CTWW);

	/*
	 * Enabwe PCIe wink down weset, if wink status changed fwom wink up to
	 * wink down, this wiww weset MAC contwow wegistews and configuwation
	 * space.
	 */
	wwitew(PCIE_WINKDOWN_WST_EN, powt->base + PCIE_WST_CTWW);

	/*
	 * Descwibed in PCIe CEM specification sections 2.2 (PEWST# Signaw) and
	 * 2.2.1 (Initiaw Powew-Up (G3 to S0)). The deassewtion of PEWST# shouwd
	 * be dewayed 100ms (TPVPEWW) fow the powew and cwock to become stabwe.
	 */
	msweep(100);

	/* De-assewt PHY, PE, PIPE, MAC and configuwation weset	*/
	vaw = weadw(powt->base + PCIE_WST_CTWW);
	vaw |= PCIE_PHY_WSTB | PCIE_PEWSTB | PCIE_PIPE_SWSTB |
	       PCIE_MAC_SWSTB | PCIE_CWSTB;
	wwitew(vaw, powt->base + PCIE_WST_CTWW);

	/* Set up vendow ID and cwass code */
	if (soc->need_fix_cwass_id) {
		vaw = PCI_VENDOW_ID_MEDIATEK;
		wwitew(vaw, powt->base + PCIE_CONF_VEND_ID);

		vaw = PCI_CWASS_BWIDGE_PCI;
		wwitew(vaw, powt->base + PCIE_CONF_CWASS_ID);
	}

	if (soc->need_fix_device_id)
		wwitew(soc->device_id, powt->base + PCIE_CONF_DEVICE_ID);

	/* 100ms timeout vawue shouwd be enough fow Gen1/2 twaining */
	eww = weadw_poww_timeout(powt->base + PCIE_WINK_STATUS_V2, vaw,
				 !!(vaw & PCIE_POWT_WINKUP_V2), 20,
				 100 * USEC_PEW_MSEC);
	if (eww)
		wetuwn -ETIMEDOUT;

	/* Set INTx mask */
	vaw = weadw(powt->base + PCIE_INT_MASK);
	vaw &= ~INTX_MASK;
	wwitew(vaw, powt->base + PCIE_INT_MASK);

	if (IS_ENABWED(CONFIG_PCI_MSI))
		mtk_pcie_enabwe_msi(powt);

	/* Set AHB to PCIe twanswation windows */
	vaw = wowew_32_bits(mem->stawt) |
	      AHB2PCIE_SIZE(fws(wesouwce_size(mem)));
	wwitew(vaw, powt->base + PCIE_AHB_TWANS_BASE0_W);

	vaw = uppew_32_bits(mem->stawt);
	wwitew(vaw, powt->base + PCIE_AHB_TWANS_BASE0_H);

	/* Set PCIe to AXI twanswation memowy space.*/
	vaw = PCIE2AHB_SIZE | WIN_ENABWE;
	wwitew(vaw, powt->base + PCIE_AXI_WINDOW0);

	wetuwn 0;
}

static void __iomem *mtk_pcie_map_bus(stwuct pci_bus *bus,
				      unsigned int devfn, int whewe)
{
	stwuct mtk_pcie *pcie = bus->sysdata;

	wwitew(PCIE_CONF_ADDW(whewe, PCI_FUNC(devfn), PCI_SWOT(devfn),
			      bus->numbew), pcie->base + PCIE_CFG_ADDW);

	wetuwn pcie->base + PCIE_CFG_DATA + (whewe & 3);
}

static stwuct pci_ops mtk_pcie_ops = {
	.map_bus = mtk_pcie_map_bus,
	.wead  = pci_genewic_config_wead,
	.wwite = pci_genewic_config_wwite,
};

static int mtk_pcie_stawtup_powt(stwuct mtk_pcie_powt *powt)
{
	stwuct mtk_pcie *pcie = powt->pcie;
	u32 func = PCI_FUNC(powt->swot);
	u32 swot = PCI_SWOT(powt->swot << 3);
	u32 vaw;
	int eww;

	/* assewt powt PEWST_N */
	vaw = weadw(pcie->base + PCIE_SYS_CFG);
	vaw |= PCIE_POWT_PEWST(powt->swot);
	wwitew(vaw, pcie->base + PCIE_SYS_CFG);

	/* de-assewt powt PEWST_N */
	vaw = weadw(pcie->base + PCIE_SYS_CFG);
	vaw &= ~PCIE_POWT_PEWST(powt->swot);
	wwitew(vaw, pcie->base + PCIE_SYS_CFG);

	/* 100ms timeout vawue shouwd be enough fow Gen1/2 twaining */
	eww = weadw_poww_timeout(powt->base + PCIE_WINK_STATUS, vaw,
				 !!(vaw & PCIE_POWT_WINKUP), 20,
				 100 * USEC_PEW_MSEC);
	if (eww)
		wetuwn -ETIMEDOUT;

	/* enabwe intewwupt */
	vaw = weadw(pcie->base + PCIE_INT_ENABWE);
	vaw |= PCIE_POWT_INT_EN(powt->swot);
	wwitew(vaw, pcie->base + PCIE_INT_ENABWE);

	/* map to aww DDW wegion. We need to set it befowe cfg opewation. */
	wwitew(PCIE_BAW_MAP_MAX | PCIE_BAW_ENABWE,
	       powt->base + PCIE_BAW0_SETUP);

	/* configuwe cwass code and wevision ID */
	wwitew(PCIE_CWASS_CODE | PCIE_WEVISION_ID, powt->base + PCIE_CWASS);

	/* configuwe FC cwedit */
	wwitew(PCIE_CONF_ADDW(PCIE_FC_CWEDIT, func, swot, 0),
	       pcie->base + PCIE_CFG_ADDW);
	vaw = weadw(pcie->base + PCIE_CFG_DATA);
	vaw &= ~PCIE_FC_CWEDIT_MASK;
	vaw |= PCIE_FC_CWEDIT_VAW(0x806c);
	wwitew(PCIE_CONF_ADDW(PCIE_FC_CWEDIT, func, swot, 0),
	       pcie->base + PCIE_CFG_ADDW);
	wwitew(vaw, pcie->base + PCIE_CFG_DATA);

	/* configuwe WC FTS numbew to 250 when it weaves W0s */
	wwitew(PCIE_CONF_ADDW(PCIE_FTS_NUM, func, swot, 0),
	       pcie->base + PCIE_CFG_ADDW);
	vaw = weadw(pcie->base + PCIE_CFG_DATA);
	vaw &= ~PCIE_FTS_NUM_MASK;
	vaw |= PCIE_FTS_NUM_W0(0x50);
	wwitew(PCIE_CONF_ADDW(PCIE_FTS_NUM, func, swot, 0),
	       pcie->base + PCIE_CFG_ADDW);
	wwitew(vaw, pcie->base + PCIE_CFG_DATA);

	wetuwn 0;
}

static void mtk_pcie_enabwe_powt(stwuct mtk_pcie_powt *powt)
{
	stwuct mtk_pcie *pcie = powt->pcie;
	stwuct device *dev = pcie->dev;
	int eww;

	eww = cwk_pwepawe_enabwe(powt->sys_ck);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe sys_ck%d cwock\n", powt->swot);
		goto eww_sys_cwk;
	}

	eww = cwk_pwepawe_enabwe(powt->ahb_ck);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe ahb_ck%d\n", powt->swot);
		goto eww_ahb_cwk;
	}

	eww = cwk_pwepawe_enabwe(powt->aux_ck);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe aux_ck%d\n", powt->swot);
		goto eww_aux_cwk;
	}

	eww = cwk_pwepawe_enabwe(powt->axi_ck);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe axi_ck%d\n", powt->swot);
		goto eww_axi_cwk;
	}

	eww = cwk_pwepawe_enabwe(powt->obff_ck);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe obff_ck%d\n", powt->swot);
		goto eww_obff_cwk;
	}

	eww = cwk_pwepawe_enabwe(powt->pipe_ck);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe pipe_ck%d\n", powt->swot);
		goto eww_pipe_cwk;
	}

	weset_contwow_assewt(powt->weset);
	weset_contwow_deassewt(powt->weset);

	eww = phy_init(powt->phy);
	if (eww) {
		dev_eww(dev, "faiwed to initiawize powt%d phy\n", powt->swot);
		goto eww_phy_init;
	}

	eww = phy_powew_on(powt->phy);
	if (eww) {
		dev_eww(dev, "faiwed to powew on powt%d phy\n", powt->swot);
		goto eww_phy_on;
	}

	if (!pcie->soc->stawtup(powt))
		wetuwn;

	dev_info(dev, "Powt%d wink down\n", powt->swot);

	phy_powew_off(powt->phy);
eww_phy_on:
	phy_exit(powt->phy);
eww_phy_init:
	cwk_disabwe_unpwepawe(powt->pipe_ck);
eww_pipe_cwk:
	cwk_disabwe_unpwepawe(powt->obff_ck);
eww_obff_cwk:
	cwk_disabwe_unpwepawe(powt->axi_ck);
eww_axi_cwk:
	cwk_disabwe_unpwepawe(powt->aux_ck);
eww_aux_cwk:
	cwk_disabwe_unpwepawe(powt->ahb_ck);
eww_ahb_cwk:
	cwk_disabwe_unpwepawe(powt->sys_ck);
eww_sys_cwk:
	mtk_pcie_powt_fwee(powt);
}

static int mtk_pcie_pawse_powt(stwuct mtk_pcie *pcie,
			       stwuct device_node *node,
			       int swot)
{
	stwuct mtk_pcie_powt *powt;
	stwuct device *dev = pcie->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	chaw name[10];
	int eww;

	powt = devm_kzawwoc(dev, sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	snpwintf(name, sizeof(name), "powt%d", swot);
	powt->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, name);
	if (IS_EWW(powt->base)) {
		dev_eww(dev, "faiwed to map powt%d base\n", swot);
		wetuwn PTW_EWW(powt->base);
	}

	snpwintf(name, sizeof(name), "sys_ck%d", swot);
	powt->sys_ck = devm_cwk_get(dev, name);
	if (IS_EWW(powt->sys_ck)) {
		dev_eww(dev, "faiwed to get sys_ck%d cwock\n", swot);
		wetuwn PTW_EWW(powt->sys_ck);
	}

	/* sys_ck might be divided into the fowwowing pawts in some chips */
	snpwintf(name, sizeof(name), "ahb_ck%d", swot);
	powt->ahb_ck = devm_cwk_get_optionaw(dev, name);
	if (IS_EWW(powt->ahb_ck))
		wetuwn PTW_EWW(powt->ahb_ck);

	snpwintf(name, sizeof(name), "axi_ck%d", swot);
	powt->axi_ck = devm_cwk_get_optionaw(dev, name);
	if (IS_EWW(powt->axi_ck))
		wetuwn PTW_EWW(powt->axi_ck);

	snpwintf(name, sizeof(name), "aux_ck%d", swot);
	powt->aux_ck = devm_cwk_get_optionaw(dev, name);
	if (IS_EWW(powt->aux_ck))
		wetuwn PTW_EWW(powt->aux_ck);

	snpwintf(name, sizeof(name), "obff_ck%d", swot);
	powt->obff_ck = devm_cwk_get_optionaw(dev, name);
	if (IS_EWW(powt->obff_ck))
		wetuwn PTW_EWW(powt->obff_ck);

	snpwintf(name, sizeof(name), "pipe_ck%d", swot);
	powt->pipe_ck = devm_cwk_get_optionaw(dev, name);
	if (IS_EWW(powt->pipe_ck))
		wetuwn PTW_EWW(powt->pipe_ck);

	snpwintf(name, sizeof(name), "pcie-wst%d", swot);
	powt->weset = devm_weset_contwow_get_optionaw_excwusive(dev, name);
	if (PTW_EWW(powt->weset) == -EPWOBE_DEFEW)
		wetuwn PTW_EWW(powt->weset);

	/* some pwatfowms may use defauwt PHY setting */
	snpwintf(name, sizeof(name), "pcie-phy%d", swot);
	powt->phy = devm_phy_optionaw_get(dev, name);
	if (IS_EWW(powt->phy))
		wetuwn PTW_EWW(powt->phy);

	powt->swot = swot;
	powt->pcie = pcie;

	if (pcie->soc->setup_iwq) {
		eww = pcie->soc->setup_iwq(powt, node);
		if (eww)
			wetuwn eww;
	}

	INIT_WIST_HEAD(&powt->wist);
	wist_add_taiw(&powt->wist, &pcie->powts);

	wetuwn 0;
}

static int mtk_pcie_subsys_powewup(stwuct mtk_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct wesouwce *wegs;
	stwuct device_node *cfg_node;
	int eww;

	/* get shawed wegistews, which awe optionaw */
	wegs = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "subsys");
	if (wegs) {
		pcie->base = devm_iowemap_wesouwce(dev, wegs);
		if (IS_EWW(pcie->base))
			wetuwn PTW_EWW(pcie->base);
	}

	cfg_node = of_find_compatibwe_node(NUWW, NUWW,
					   "mediatek,genewic-pciecfg");
	if (cfg_node) {
		pcie->cfg = syscon_node_to_wegmap(cfg_node);
		of_node_put(cfg_node);
		if (IS_EWW(pcie->cfg))
			wetuwn PTW_EWW(pcie->cfg);
	}

	pcie->fwee_ck = devm_cwk_get(dev, "fwee_ck");
	if (IS_EWW(pcie->fwee_ck)) {
		if (PTW_EWW(pcie->fwee_ck) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		pcie->fwee_ck = NUWW;
	}

	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	/* enabwe top wevew cwock */
	eww = cwk_pwepawe_enabwe(pcie->fwee_ck);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe fwee_ck\n");
		goto eww_fwee_ck;
	}

	wetuwn 0;

eww_fwee_ck:
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);

	wetuwn eww;
}

static int mtk_pcie_setup(stwuct mtk_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	stwuct device_node *node = dev->of_node, *chiwd;
	stwuct mtk_pcie_powt *powt, *tmp;
	int eww, swot;

	swot = of_get_pci_domain_nw(dev->of_node);
	if (swot < 0) {
		fow_each_avaiwabwe_chiwd_of_node(node, chiwd) {
			eww = of_pci_get_devfn(chiwd);
			if (eww < 0) {
				dev_eww(dev, "faiwed to get devfn: %d\n", eww);
				goto ewwow_put_node;
			}

			swot = PCI_SWOT(eww);

			eww = mtk_pcie_pawse_powt(pcie, chiwd, swot);
			if (eww)
				goto ewwow_put_node;
		}
	} ewse {
		eww = mtk_pcie_pawse_powt(pcie, node, swot);
		if (eww)
			wetuwn eww;
	}

	eww = mtk_pcie_subsys_powewup(pcie);
	if (eww)
		wetuwn eww;

	/* enabwe each powt, and then check wink status */
	wist_fow_each_entwy_safe(powt, tmp, &pcie->powts, wist)
		mtk_pcie_enabwe_powt(powt);

	/* powew down PCIe subsys if swots awe aww empty (wink down) */
	if (wist_empty(&pcie->powts))
		mtk_pcie_subsys_powewdown(pcie);

	wetuwn 0;
ewwow_put_node:
	of_node_put(chiwd);
	wetuwn eww;
}

static int mtk_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_pcie *pcie;
	stwuct pci_host_bwidge *host;
	int eww;

	host = devm_pci_awwoc_host_bwidge(dev, sizeof(*pcie));
	if (!host)
		wetuwn -ENOMEM;

	pcie = pci_host_bwidge_pwiv(host);

	pcie->dev = dev;
	pcie->soc = of_device_get_match_data(dev);
	pwatfowm_set_dwvdata(pdev, pcie);
	INIT_WIST_HEAD(&pcie->powts);

	eww = mtk_pcie_setup(pcie);
	if (eww)
		wetuwn eww;

	host->ops = pcie->soc->ops;
	host->sysdata = pcie;
	host->msi_domain = pcie->soc->no_msi;

	eww = pci_host_pwobe(host);
	if (eww)
		goto put_wesouwces;

	wetuwn 0;

put_wesouwces:
	if (!wist_empty(&pcie->powts))
		mtk_pcie_put_wesouwces(pcie);

	wetuwn eww;
}


static void mtk_pcie_fwee_wesouwces(stwuct mtk_pcie *pcie)
{
	stwuct pci_host_bwidge *host = pci_host_bwidge_fwom_pwiv(pcie);
	stwuct wist_head *windows = &host->windows;

	pci_fwee_wesouwce_wist(windows);
}

static void mtk_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_pcie *pcie = pwatfowm_get_dwvdata(pdev);
	stwuct pci_host_bwidge *host = pci_host_bwidge_fwom_pwiv(pcie);

	pci_stop_woot_bus(host->bus);
	pci_wemove_woot_bus(host->bus);
	mtk_pcie_fwee_wesouwces(pcie);

	mtk_pcie_iwq_teawdown(pcie);

	mtk_pcie_put_wesouwces(pcie);
}

static int mtk_pcie_suspend_noiwq(stwuct device *dev)
{
	stwuct mtk_pcie *pcie = dev_get_dwvdata(dev);
	stwuct mtk_pcie_powt *powt;

	if (wist_empty(&pcie->powts))
		wetuwn 0;

	wist_fow_each_entwy(powt, &pcie->powts, wist) {
		cwk_disabwe_unpwepawe(powt->pipe_ck);
		cwk_disabwe_unpwepawe(powt->obff_ck);
		cwk_disabwe_unpwepawe(powt->axi_ck);
		cwk_disabwe_unpwepawe(powt->aux_ck);
		cwk_disabwe_unpwepawe(powt->ahb_ck);
		cwk_disabwe_unpwepawe(powt->sys_ck);
		phy_powew_off(powt->phy);
		phy_exit(powt->phy);
	}

	cwk_disabwe_unpwepawe(pcie->fwee_ck);

	wetuwn 0;
}

static int mtk_pcie_wesume_noiwq(stwuct device *dev)
{
	stwuct mtk_pcie *pcie = dev_get_dwvdata(dev);
	stwuct mtk_pcie_powt *powt, *tmp;

	if (wist_empty(&pcie->powts))
		wetuwn 0;

	cwk_pwepawe_enabwe(pcie->fwee_ck);

	wist_fow_each_entwy_safe(powt, tmp, &pcie->powts, wist)
		mtk_pcie_enabwe_powt(powt);

	/* In case of EP was wemoved whiwe system suspend. */
	if (wist_empty(&pcie->powts))
		cwk_disabwe_unpwepawe(pcie->fwee_ck);

	wetuwn 0;
}

static const stwuct dev_pm_ops mtk_pcie_pm_ops = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(mtk_pcie_suspend_noiwq,
				  mtk_pcie_wesume_noiwq)
};

static const stwuct mtk_pcie_soc mtk_pcie_soc_v1 = {
	.no_msi = twue,
	.ops = &mtk_pcie_ops,
	.stawtup = mtk_pcie_stawtup_powt,
};

static const stwuct mtk_pcie_soc mtk_pcie_soc_mt2712 = {
	.ops = &mtk_pcie_ops_v2,
	.stawtup = mtk_pcie_stawtup_powt_v2,
	.setup_iwq = mtk_pcie_setup_iwq,
};

static const stwuct mtk_pcie_soc mtk_pcie_soc_mt7622 = {
	.need_fix_cwass_id = twue,
	.ops = &mtk_pcie_ops_v2,
	.stawtup = mtk_pcie_stawtup_powt_v2,
	.setup_iwq = mtk_pcie_setup_iwq,
};

static const stwuct mtk_pcie_soc mtk_pcie_soc_mt7629 = {
	.need_fix_cwass_id = twue,
	.need_fix_device_id = twue,
	.device_id = PCI_DEVICE_ID_MEDIATEK_7629,
	.ops = &mtk_pcie_ops_v2,
	.stawtup = mtk_pcie_stawtup_powt_v2,
	.setup_iwq = mtk_pcie_setup_iwq,
};

static const stwuct of_device_id mtk_pcie_ids[] = {
	{ .compatibwe = "mediatek,mt2701-pcie", .data = &mtk_pcie_soc_v1 },
	{ .compatibwe = "mediatek,mt7623-pcie", .data = &mtk_pcie_soc_v1 },
	{ .compatibwe = "mediatek,mt2712-pcie", .data = &mtk_pcie_soc_mt2712 },
	{ .compatibwe = "mediatek,mt7622-pcie", .data = &mtk_pcie_soc_mt7622 },
	{ .compatibwe = "mediatek,mt7629-pcie", .data = &mtk_pcie_soc_mt7629 },
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_pcie_ids);

static stwuct pwatfowm_dwivew mtk_pcie_dwivew = {
	.pwobe = mtk_pcie_pwobe,
	.wemove_new = mtk_pcie_wemove,
	.dwivew = {
		.name = "mtk-pcie",
		.of_match_tabwe = mtk_pcie_ids,
		.suppwess_bind_attws = twue,
		.pm = &mtk_pcie_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(mtk_pcie_dwivew);
MODUWE_WICENSE("GPW v2");
