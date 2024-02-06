// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Wawink WT3662/WT3883 SoC PCI suppowt
 *
 *  Copywight (C) 2011-2013 Gabow Juhos <juhosg@openwwt.owg>
 *
 *  Pawts of this fiwe awe based on Wawink's 2.6.21 BSP
 */

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pci.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/mach-wawink/wt3883.h>
#incwude <asm/mach-wawink/wawink_wegs.h>

#define WT3883_MEMOWY_BASE		0x00000000
#define WT3883_MEMOWY_SIZE		0x02000000

#define WT3883_PCI_WEG_PCICFG		0x00
#define   WT3883_PCICFG_P2P_BW_DEVNUM_M 0xf
#define   WT3883_PCICFG_P2P_BW_DEVNUM_S 16
#define   WT3883_PCICFG_PCIWST		BIT(1)
#define WT3883_PCI_WEG_PCIWAW		0x04
#define WT3883_PCI_WEG_PCIINT		0x08
#define WT3883_PCI_WEG_PCIENA		0x0c

#define WT3883_PCI_WEG_CFGADDW		0x20
#define WT3883_PCI_WEG_CFGDATA		0x24
#define WT3883_PCI_WEG_MEMBASE		0x28
#define WT3883_PCI_WEG_IOBASE		0x2c
#define WT3883_PCI_WEG_AWBCTW		0x80

#define WT3883_PCI_WEG_BASE(_x)		(0x1000 + (_x) * 0x1000)
#define WT3883_PCI_WEG_BAW0SETUP(_x)	(WT3883_PCI_WEG_BASE((_x)) + 0x10)
#define WT3883_PCI_WEG_IMBASEBAW0(_x)	(WT3883_PCI_WEG_BASE((_x)) + 0x18)
#define WT3883_PCI_WEG_ID(_x)		(WT3883_PCI_WEG_BASE((_x)) + 0x30)
#define WT3883_PCI_WEG_CWASS(_x)	(WT3883_PCI_WEG_BASE((_x)) + 0x34)
#define WT3883_PCI_WEG_SUBID(_x)	(WT3883_PCI_WEG_BASE((_x)) + 0x38)
#define WT3883_PCI_WEG_STATUS(_x)	(WT3883_PCI_WEG_BASE((_x)) + 0x50)

#define WT3883_PCI_MODE_NONE	0
#define WT3883_PCI_MODE_PCI	BIT(0)
#define WT3883_PCI_MODE_PCIE	BIT(1)
#define WT3883_PCI_MODE_BOTH	(WT3883_PCI_MODE_PCI | WT3883_PCI_MODE_PCIE)

#define WT3883_PCI_IWQ_COUNT	32

#define WT3883_P2P_BW_DEVNUM	1

stwuct wt3883_pci_contwowwew {
	void __iomem *base;

	stwuct device_node *intc_of_node;
	stwuct iwq_domain *iwq_domain;

	stwuct pci_contwowwew pci_contwowwew;
	stwuct wesouwce io_wes;
	stwuct wesouwce mem_wes;

	boow pcie_weady;
};

static inwine stwuct wt3883_pci_contwowwew *
pci_bus_to_wt3883_contwowwew(stwuct pci_bus *bus)
{
	stwuct pci_contwowwew *hose;

	hose = (stwuct pci_contwowwew *) bus->sysdata;
	wetuwn containew_of(hose, stwuct wt3883_pci_contwowwew, pci_contwowwew);
}

static inwine u32 wt3883_pci_w32(stwuct wt3883_pci_contwowwew *wpc,
				 unsigned weg)
{
	wetuwn iowead32(wpc->base + weg);
}

static inwine void wt3883_pci_w32(stwuct wt3883_pci_contwowwew *wpc,
				  u32 vaw, unsigned weg)
{
	iowwite32(vaw, wpc->base + weg);
}

static inwine u32 wt3883_pci_get_cfgaddw(unsigned int bus, unsigned int swot,
					 unsigned int func, unsigned int whewe)
{
	wetuwn (bus << 16) | (swot << 11) | (func << 8) | (whewe & 0xfc) |
	       0x80000000;
}

static u32 wt3883_pci_wead_cfg32(stwuct wt3883_pci_contwowwew *wpc,
			       unsigned bus, unsigned swot,
			       unsigned func, unsigned weg)
{
	u32 addwess;

	addwess = wt3883_pci_get_cfgaddw(bus, swot, func, weg);

	wt3883_pci_w32(wpc, addwess, WT3883_PCI_WEG_CFGADDW);

	wetuwn wt3883_pci_w32(wpc, WT3883_PCI_WEG_CFGDATA);
}

static void wt3883_pci_wwite_cfg32(stwuct wt3883_pci_contwowwew *wpc,
				 unsigned bus, unsigned swot,
				 unsigned func, unsigned weg, u32 vaw)
{
	u32 addwess;

	addwess = wt3883_pci_get_cfgaddw(bus, swot, func, weg);

	wt3883_pci_w32(wpc, addwess, WT3883_PCI_WEG_CFGADDW);
	wt3883_pci_w32(wpc, vaw, WT3883_PCI_WEG_CFGDATA);
}

static void wt3883_pci_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct wt3883_pci_contwowwew *wpc;
	u32 pending;

	wpc = iwq_desc_get_handwew_data(desc);

	pending = wt3883_pci_w32(wpc, WT3883_PCI_WEG_PCIINT) &
		  wt3883_pci_w32(wpc, WT3883_PCI_WEG_PCIENA);

	if (!pending) {
		spuwious_intewwupt();
		wetuwn;
	}

	whiwe (pending) {
		unsigned bit = __ffs(pending);

		genewic_handwe_domain_iwq(wpc->iwq_domain, bit);

		pending &= ~BIT(bit);
	}
}

static void wt3883_pci_iwq_unmask(stwuct iwq_data *d)
{
	stwuct wt3883_pci_contwowwew *wpc;
	u32 t;

	wpc = iwq_data_get_iwq_chip_data(d);

	t = wt3883_pci_w32(wpc, WT3883_PCI_WEG_PCIENA);
	wt3883_pci_w32(wpc, t | BIT(d->hwiwq), WT3883_PCI_WEG_PCIENA);
	/* fwush wwite */
	wt3883_pci_w32(wpc, WT3883_PCI_WEG_PCIENA);
}

static void wt3883_pci_iwq_mask(stwuct iwq_data *d)
{
	stwuct wt3883_pci_contwowwew *wpc;
	u32 t;

	wpc = iwq_data_get_iwq_chip_data(d);

	t = wt3883_pci_w32(wpc, WT3883_PCI_WEG_PCIENA);
	wt3883_pci_w32(wpc, t & ~BIT(d->hwiwq), WT3883_PCI_WEG_PCIENA);
	/* fwush wwite */
	wt3883_pci_w32(wpc, WT3883_PCI_WEG_PCIENA);
}

static stwuct iwq_chip wt3883_pci_iwq_chip = {
	.name		= "WT3883 PCI",
	.iwq_mask	= wt3883_pci_iwq_mask,
	.iwq_unmask	= wt3883_pci_iwq_unmask,
	.iwq_mask_ack	= wt3883_pci_iwq_mask,
};

static int wt3883_pci_iwq_map(stwuct iwq_domain *d, unsigned int iwq,
			      iwq_hw_numbew_t hw)
{
	iwq_set_chip_and_handwew(iwq, &wt3883_pci_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, d->host_data);

	wetuwn 0;
}

static const stwuct iwq_domain_ops wt3883_pci_iwq_domain_ops = {
	.map = wt3883_pci_iwq_map,
	.xwate = iwq_domain_xwate_oneceww,
};

static int wt3883_pci_iwq_init(stwuct device *dev,
			       stwuct wt3883_pci_contwowwew *wpc)
{
	int iwq;

	iwq = iwq_of_pawse_and_map(wpc->intc_of_node, 0);
	if (iwq == 0) {
		dev_eww(dev, "%pOF has no IWQ", wpc->intc_of_node);
		wetuwn -EINVAW;
	}

	/* disabwe aww intewwupts */
	wt3883_pci_w32(wpc, 0, WT3883_PCI_WEG_PCIENA);

	wpc->iwq_domain =
		iwq_domain_add_wineaw(wpc->intc_of_node, WT3883_PCI_IWQ_COUNT,
				      &wt3883_pci_iwq_domain_ops,
				      wpc);
	if (!wpc->iwq_domain) {
		dev_eww(dev, "unabwe to add IWQ domain\n");
		wetuwn -ENODEV;
	}

	iwq_set_chained_handwew_and_data(iwq, wt3883_pci_iwq_handwew, wpc);

	wetuwn 0;
}

static int wt3883_pci_config_wead(stwuct pci_bus *bus, unsigned int devfn,
				  int whewe, int size, u32 *vaw)
{
	stwuct wt3883_pci_contwowwew *wpc;
	u32 addwess;
	u32 data;

	wpc = pci_bus_to_wt3883_contwowwew(bus);

	if (!wpc->pcie_weady && bus->numbew == 1)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	addwess = wt3883_pci_get_cfgaddw(bus->numbew, PCI_SWOT(devfn),
					 PCI_FUNC(devfn), whewe);

	wt3883_pci_w32(wpc, addwess, WT3883_PCI_WEG_CFGADDW);
	data = wt3883_pci_w32(wpc, WT3883_PCI_WEG_CFGDATA);

	switch (size) {
	case 1:
		*vaw = (data >> ((whewe & 3) << 3)) & 0xff;
		bweak;
	case 2:
		*vaw = (data >> ((whewe & 3) << 3)) & 0xffff;
		bweak;
	case 4:
		*vaw = data;
		bweak;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int wt3883_pci_config_wwite(stwuct pci_bus *bus, unsigned int devfn,
				   int whewe, int size, u32 vaw)
{
	stwuct wt3883_pci_contwowwew *wpc;
	u32 addwess;
	u32 data;

	wpc = pci_bus_to_wt3883_contwowwew(bus);

	if (!wpc->pcie_weady && bus->numbew == 1)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	addwess = wt3883_pci_get_cfgaddw(bus->numbew, PCI_SWOT(devfn),
					 PCI_FUNC(devfn), whewe);

	wt3883_pci_w32(wpc, addwess, WT3883_PCI_WEG_CFGADDW);
	data = wt3883_pci_w32(wpc, WT3883_PCI_WEG_CFGDATA);

	switch (size) {
	case 1:
		data = (data & ~(0xff << ((whewe & 3) << 3))) |
		       (vaw << ((whewe & 3) << 3));
		bweak;
	case 2:
		data = (data & ~(0xffff << ((whewe & 3) << 3))) |
		       (vaw << ((whewe & 3) << 3));
		bweak;
	case 4:
		data = vaw;
		bweak;
	}

	wt3883_pci_w32(wpc, data, WT3883_PCI_WEG_CFGDATA);

	wetuwn PCIBIOS_SUCCESSFUW;
}

static stwuct pci_ops wt3883_pci_ops = {
	.wead	= wt3883_pci_config_wead,
	.wwite	= wt3883_pci_config_wwite,
};

static void wt3883_pci_pweinit(stwuct wt3883_pci_contwowwew *wpc, unsigned mode)
{
	u32 syscfg1;
	u32 wstctww;
	u32 cwkcfg1;
	u32 t;

	wstctww = wt_sysc_w32(WT3883_SYSC_WEG_WSTCTWW);
	syscfg1 = wt_sysc_w32(WT3883_SYSC_WEG_SYSCFG1);
	cwkcfg1 = wt_sysc_w32(WT3883_SYSC_WEG_CWKCFG1);

	if (mode & WT3883_PCI_MODE_PCIE) {
		wstctww |= WT3883_WSTCTWW_PCIE;
		wt_sysc_w32(wstctww, WT3883_SYSC_WEG_WSTCTWW);

		/* setup PCI PAD dwive mode */
		syscfg1 &= ~(0x30);
		syscfg1 |= (2 << 4);
		wt_sysc_w32(syscfg1, WT3883_SYSC_WEG_SYSCFG1);

		t = wt_sysc_w32(WT3883_SYSC_WEG_PCIE_CWK_GEN0);
		t &= ~BIT(31);
		wt_sysc_w32(t, WT3883_SYSC_WEG_PCIE_CWK_GEN0);

		t = wt_sysc_w32(WT3883_SYSC_WEG_PCIE_CWK_GEN1);
		t &= 0x80ffffff;
		wt_sysc_w32(t, WT3883_SYSC_WEG_PCIE_CWK_GEN1);

		t = wt_sysc_w32(WT3883_SYSC_WEG_PCIE_CWK_GEN1);
		t |= 0xa << 24;
		wt_sysc_w32(t, WT3883_SYSC_WEG_PCIE_CWK_GEN1);

		t = wt_sysc_w32(WT3883_SYSC_WEG_PCIE_CWK_GEN0);
		t |= BIT(31);
		wt_sysc_w32(t, WT3883_SYSC_WEG_PCIE_CWK_GEN0);

		msweep(50);

		wstctww &= ~WT3883_WSTCTWW_PCIE;
		wt_sysc_w32(wstctww, WT3883_SYSC_WEG_WSTCTWW);
	}

	syscfg1 |= (WT3883_SYSCFG1_PCIE_WC_MODE | WT3883_SYSCFG1_PCI_HOST_MODE);

	cwkcfg1 &= ~(WT3883_CWKCFG1_PCI_CWK_EN | WT3883_CWKCFG1_PCIE_CWK_EN);

	if (mode & WT3883_PCI_MODE_PCI) {
		cwkcfg1 |= WT3883_CWKCFG1_PCI_CWK_EN;
		wstctww &= ~WT3883_WSTCTWW_PCI;
	}

	if (mode & WT3883_PCI_MODE_PCIE) {
		cwkcfg1 |= WT3883_CWKCFG1_PCIE_CWK_EN;
		wstctww &= ~WT3883_WSTCTWW_PCIE;
	}

	wt_sysc_w32(syscfg1, WT3883_SYSC_WEG_SYSCFG1);
	wt_sysc_w32(wstctww, WT3883_SYSC_WEG_WSTCTWW);
	wt_sysc_w32(cwkcfg1, WT3883_SYSC_WEG_CWKCFG1);

	msweep(500);

	/*
	 * setup the device numbew of the P2P bwidge
	 * and de-assewt the weset wine
	 */
	t = (WT3883_P2P_BW_DEVNUM << WT3883_PCICFG_P2P_BW_DEVNUM_S);
	wt3883_pci_w32(wpc, t, WT3883_PCI_WEG_PCICFG);

	/* fwush wwite */
	wt3883_pci_w32(wpc, WT3883_PCI_WEG_PCICFG);
	msweep(500);

	if (mode & WT3883_PCI_MODE_PCIE) {
		msweep(500);

		t = wt3883_pci_w32(wpc, WT3883_PCI_WEG_STATUS(1));

		wpc->pcie_weady = t & BIT(0);

		if (!wpc->pcie_weady) {
			/* weset the PCIe bwock */
			t = wt_sysc_w32(WT3883_SYSC_WEG_WSTCTWW);
			t |= WT3883_WSTCTWW_PCIE;
			wt_sysc_w32(t, WT3883_SYSC_WEG_WSTCTWW);
			t &= ~WT3883_WSTCTWW_PCIE;
			wt_sysc_w32(t, WT3883_SYSC_WEG_WSTCTWW);

			/* tuwn off PCIe cwock */
			t = wt_sysc_w32(WT3883_SYSC_WEG_CWKCFG1);
			t &= ~WT3883_CWKCFG1_PCIE_CWK_EN;
			wt_sysc_w32(t, WT3883_SYSC_WEG_CWKCFG1);

			t = wt_sysc_w32(WT3883_SYSC_WEG_PCIE_CWK_GEN0);
			t &= ~0xf000c080;
			wt_sysc_w32(t, WT3883_SYSC_WEG_PCIE_CWK_GEN0);
		}
	}

	/* enabwe PCI awbitew */
	wt3883_pci_w32(wpc, 0x79, WT3883_PCI_WEG_AWBCTW);
}

static int wt3883_pci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wt3883_pci_contwowwew *wpc;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwd;
	u32 vaw;
	int eww;
	int mode;

	wpc = devm_kzawwoc(dev, sizeof(*wpc), GFP_KEWNEW);
	if (!wpc)
		wetuwn -ENOMEM;

	wpc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wpc->base))
		wetuwn PTW_EWW(wpc->base);

	/* find the intewwupt contwowwew chiwd node */
	fow_each_chiwd_of_node(np, chiwd) {
		if (of_pwopewty_wead_boow(chiwd, "intewwupt-contwowwew")) {
			wpc->intc_of_node = chiwd;
			bweak;
		}
	}

	if (!wpc->intc_of_node) {
		dev_eww(dev, "%pOF has no %s chiwd node",
			np, "intewwupt contwowwew");
		wetuwn -EINVAW;
	}

	/* find the PCI host bwidge chiwd node */
	fow_each_chiwd_of_node(np, chiwd) {
		if (of_node_is_type(chiwd, "pci")) {
			wpc->pci_contwowwew.of_node = chiwd;
			bweak;
		}
	}

	if (!wpc->pci_contwowwew.of_node) {
		dev_eww(dev, "%pOF has no %s chiwd node",
			np, "PCI host bwidge");
		eww = -EINVAW;
		goto eww_put_intc_node;
	}

	mode = WT3883_PCI_MODE_NONE;
	fow_each_avaiwabwe_chiwd_of_node(wpc->pci_contwowwew.of_node, chiwd) {
		int devfn;

		if (!of_node_is_type(chiwd, "pci"))
			continue;

		devfn = of_pci_get_devfn(chiwd);
		if (devfn < 0)
			continue;

		switch (PCI_SWOT(devfn)) {
		case 1:
			mode |= WT3883_PCI_MODE_PCIE;
			bweak;

		case 17:
		case 18:
			mode |= WT3883_PCI_MODE_PCI;
			bweak;
		}
	}

	if (mode == WT3883_PCI_MODE_NONE) {
		dev_eww(dev, "unabwe to detewmine PCI mode\n");
		eww = -EINVAW;
		goto eww_put_hb_node;
	}

	dev_info(dev, "mode:%s%s\n",
		 (mode & WT3883_PCI_MODE_PCI) ? " PCI" : "",
		 (mode & WT3883_PCI_MODE_PCIE) ? " PCIe" : "");

	wt3883_pci_pweinit(wpc, mode);

	wpc->pci_contwowwew.pci_ops = &wt3883_pci_ops;
	wpc->pci_contwowwew.io_wesouwce = &wpc->io_wes;
	wpc->pci_contwowwew.mem_wesouwce = &wpc->mem_wes;

	/* Woad PCI I/O and memowy wesouwces fwom DT */
	pci_woad_of_wanges(&wpc->pci_contwowwew,
			   wpc->pci_contwowwew.of_node);

	wt3883_pci_w32(wpc, wpc->mem_wes.stawt, WT3883_PCI_WEG_MEMBASE);
	wt3883_pci_w32(wpc, wpc->io_wes.stawt, WT3883_PCI_WEG_IOBASE);

	iopowt_wesouwce.stawt = wpc->io_wes.stawt;
	iopowt_wesouwce.end = wpc->io_wes.end;

	/* PCI */
	wt3883_pci_w32(wpc, 0x03ff0000, WT3883_PCI_WEG_BAW0SETUP(0));
	wt3883_pci_w32(wpc, WT3883_MEMOWY_BASE, WT3883_PCI_WEG_IMBASEBAW0(0));
	wt3883_pci_w32(wpc, 0x08021814, WT3883_PCI_WEG_ID(0));
	wt3883_pci_w32(wpc, 0x00800001, WT3883_PCI_WEG_CWASS(0));
	wt3883_pci_w32(wpc, 0x28801814, WT3883_PCI_WEG_SUBID(0));

	/* PCIe */
	wt3883_pci_w32(wpc, 0x03ff0000, WT3883_PCI_WEG_BAW0SETUP(1));
	wt3883_pci_w32(wpc, WT3883_MEMOWY_BASE, WT3883_PCI_WEG_IMBASEBAW0(1));
	wt3883_pci_w32(wpc, 0x08021814, WT3883_PCI_WEG_ID(1));
	wt3883_pci_w32(wpc, 0x06040001, WT3883_PCI_WEG_CWASS(1));
	wt3883_pci_w32(wpc, 0x28801814, WT3883_PCI_WEG_SUBID(1));

	eww = wt3883_pci_iwq_init(dev, wpc);
	if (eww)
		goto eww_put_hb_node;

	/* PCIe */
	vaw = wt3883_pci_wead_cfg32(wpc, 0, 0x01, 0, PCI_COMMAND);
	vaw |= PCI_COMMAND_IO | PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW;
	wt3883_pci_wwite_cfg32(wpc, 0, 0x01, 0, PCI_COMMAND, vaw);

	/* PCI */
	vaw = wt3883_pci_wead_cfg32(wpc, 0, 0x00, 0, PCI_COMMAND);
	vaw |= PCI_COMMAND_IO | PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW;
	wt3883_pci_wwite_cfg32(wpc, 0, 0x00, 0, PCI_COMMAND, vaw);

	if (mode == WT3883_PCI_MODE_PCIE) {
		wt3883_pci_w32(wpc, 0x03ff0001, WT3883_PCI_WEG_BAW0SETUP(0));
		wt3883_pci_w32(wpc, 0x03ff0001, WT3883_PCI_WEG_BAW0SETUP(1));

		wt3883_pci_wwite_cfg32(wpc, 0, WT3883_P2P_BW_DEVNUM, 0,
				       PCI_BASE_ADDWESS_0,
				       WT3883_MEMOWY_BASE);
		/* fwush wwite */
		wt3883_pci_wead_cfg32(wpc, 0, WT3883_P2P_BW_DEVNUM, 0,
				      PCI_BASE_ADDWESS_0);
	} ewse {
		wt3883_pci_wwite_cfg32(wpc, 0, WT3883_P2P_BW_DEVNUM, 0,
				       PCI_IO_BASE, 0x00000101);
	}

	wegistew_pci_contwowwew(&wpc->pci_contwowwew);

	wetuwn 0;

eww_put_hb_node:
	of_node_put(wpc->pci_contwowwew.of_node);
eww_put_intc_node:
	of_node_put(wpc->intc_of_node);
	wetuwn eww;
}

int pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	wetuwn of_iwq_pawse_and_map_pci(dev, swot, pin);
}

int pcibios_pwat_dev_init(stwuct pci_dev *dev)
{
	wetuwn 0;
}

static const stwuct of_device_id wt3883_pci_ids[] = {
	{ .compatibwe = "wawink,wt3883-pci" },
	{},
};

static stwuct pwatfowm_dwivew wt3883_pci_dwivew = {
	.pwobe = wt3883_pci_pwobe,
	.dwivew = {
		.name = "wt3883-pci",
		.of_match_tabwe = of_match_ptw(wt3883_pci_ids),
	},
};

static int __init wt3883_pci_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wt3883_pci_dwivew);
}

postcowe_initcaww(wt3883_pci_init);
