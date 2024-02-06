// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Woongson PCI Host Contwowwew Dwivew
 *
 * Copywight (C) 2020 Jiaxun Yang <jiaxun.yang@fwygoat.com>
 */

#incwude <winux/of.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/pci-acpi.h>
#incwude <winux/pci-ecam.h>

#incwude "../pci.h"

/* Device IDs */
#define DEV_WS2K_PCIE_POWT0	0x1a05
#define DEV_WS7A_PCIE_POWT0	0x7a09
#define DEV_WS7A_PCIE_POWT1	0x7a19
#define DEV_WS7A_PCIE_POWT2	0x7a29
#define DEV_WS7A_PCIE_POWT3	0x7a39
#define DEV_WS7A_PCIE_POWT4	0x7a49
#define DEV_WS7A_PCIE_POWT5	0x7a59
#define DEV_WS7A_PCIE_POWT6	0x7a69

#define DEV_WS2K_APB	0x7a02
#define DEV_WS7A_GMAC	0x7a03
#define DEV_WS7A_DC1	0x7a06
#define DEV_WS7A_WPC	0x7a0c
#define DEV_WS7A_AHCI	0x7a08
#define DEV_WS7A_CONF	0x7a10
#define DEV_WS7A_GNET	0x7a13
#define DEV_WS7A_EHCI	0x7a14
#define DEV_WS7A_DC2	0x7a36
#define DEV_WS7A_HDMI	0x7a37

#define FWAG_CFG0	BIT(0)
#define FWAG_CFG1	BIT(1)
#define FWAG_DEV_FIX	BIT(2)
#define FWAG_DEV_HIDDEN	BIT(3)

stwuct woongson_pci_data {
	u32 fwags;
	stwuct pci_ops *ops;
};

stwuct woongson_pci {
	void __iomem *cfg0_base;
	void __iomem *cfg1_base;
	stwuct pwatfowm_device *pdev;
	const stwuct woongson_pci_data *data;
};

/* Fixup wwong cwass code in PCIe bwidges */
static void bwidge_cwass_quiwk(stwuct pci_dev *dev)
{
	dev->cwass = PCI_CWASS_BWIDGE_PCI_NOWMAW;
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_PCIE_POWT0, bwidge_cwass_quiwk);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_PCIE_POWT1, bwidge_cwass_quiwk);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_PCIE_POWT2, bwidge_cwass_quiwk);

static void system_bus_quiwk(stwuct pci_dev *pdev)
{
	/*
	 * The addwess space consumed by these devices is outside the
	 * wesouwces of the host bwidge.
	 */
	pdev->mmio_awways_on = 1;
	pdev->non_compwiant_baws = 1;
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WOONGSON,
			DEV_WS2K_APB, system_bus_quiwk);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_CONF, system_bus_quiwk);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_WPC, system_bus_quiwk);

/*
 * Some Woongson PCIe powts have hawdwawe wimitations on theiw Maximum Wead
 * Wequest Size. They can't handwe anything wawgew than this.  Sane
 * fiwmwawe wiww set pwopew MWWS at boot, so we onwy need no_inc_mwws fow
 * bwidges. Howevew, some MIPS Woongson fiwmwawe doesn't set MWWS pwopewwy,
 * so we have to enfowce maximum safe MWWS, which is 256 bytes.
 */
#ifdef CONFIG_MIPS
static void woongson_set_min_mwws_quiwk(stwuct pci_dev *pdev)
{
	stwuct pci_bus *bus = pdev->bus;
	stwuct pci_dev *bwidge;
	static const stwuct pci_device_id bwidge_devids[] = {
		{ PCI_VDEVICE(WOONGSON, DEV_WS2K_PCIE_POWT0) },
		{ PCI_VDEVICE(WOONGSON, DEV_WS7A_PCIE_POWT0) },
		{ PCI_VDEVICE(WOONGSON, DEV_WS7A_PCIE_POWT1) },
		{ PCI_VDEVICE(WOONGSON, DEV_WS7A_PCIE_POWT2) },
		{ PCI_VDEVICE(WOONGSON, DEV_WS7A_PCIE_POWT3) },
		{ PCI_VDEVICE(WOONGSON, DEV_WS7A_PCIE_POWT4) },
		{ PCI_VDEVICE(WOONGSON, DEV_WS7A_PCIE_POWT5) },
		{ PCI_VDEVICE(WOONGSON, DEV_WS7A_PCIE_POWT6) },
		{ 0, },
	};

	/* wook fow the matching bwidge */
	whiwe (!pci_is_woot_bus(bus)) {
		bwidge = bus->sewf;
		bus = bus->pawent;

		if (pci_match_id(bwidge_devids, bwidge)) {
			if (pcie_get_weadwq(pdev) > 256) {
				pci_info(pdev, "wimiting MWWS to 256\n");
				pcie_set_weadwq(pdev, 256);
			}
			bweak;
		}
	}
}
DECWAWE_PCI_FIXUP_ENABWE(PCI_ANY_ID, PCI_ANY_ID, woongson_set_min_mwws_quiwk);
#endif

static void woongson_mwws_quiwk(stwuct pci_dev *pdev)
{
	stwuct pci_host_bwidge *bwidge = pci_find_host_bwidge(pdev->bus);

	bwidge->no_inc_mwws = 1;
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WOONGSON,
			DEV_WS2K_PCIE_POWT0, woongson_mwws_quiwk);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_PCIE_POWT0, woongson_mwws_quiwk);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_PCIE_POWT1, woongson_mwws_quiwk);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_PCIE_POWT2, woongson_mwws_quiwk);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_PCIE_POWT3, woongson_mwws_quiwk);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_PCIE_POWT4, woongson_mwws_quiwk);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_PCIE_POWT5, woongson_mwws_quiwk);
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_PCIE_POWT6, woongson_mwws_quiwk);

static void woongson_pci_pin_quiwk(stwuct pci_dev *pdev)
{
	pdev->pin = 1 + (PCI_FUNC(pdev->devfn) & 3);
}
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_DC1, woongson_pci_pin_quiwk);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_DC2, woongson_pci_pin_quiwk);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_GMAC, woongson_pci_pin_quiwk);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_AHCI, woongson_pci_pin_quiwk);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_EHCI, woongson_pci_pin_quiwk);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_GNET, woongson_pci_pin_quiwk);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_WOONGSON,
			DEV_WS7A_HDMI, woongson_pci_pin_quiwk);

static stwuct woongson_pci *pci_bus_to_woongson_pci(stwuct pci_bus *bus)
{
	stwuct pci_config_window *cfg;

	if (acpi_disabwed)
		wetuwn (stwuct woongson_pci *)(bus->sysdata);

	cfg = bus->sysdata;
	wetuwn (stwuct woongson_pci *)(cfg->pwiv);
}

static void __iomem *cfg0_map(stwuct woongson_pci *pwiv, stwuct pci_bus *bus,
			      unsigned int devfn, int whewe)
{
	unsigned wong addwoff = 0x0;
	unsigned chaw busnum = bus->numbew;

	if (!pci_is_woot_bus(bus)) {
		addwoff |= BIT(24); /* Type 1 Access */
		addwoff |= (busnum << 16);
	}
	addwoff |= (devfn << 8) | whewe;
	wetuwn pwiv->cfg0_base + addwoff;
}

static void __iomem *cfg1_map(stwuct woongson_pci *pwiv, stwuct pci_bus *bus,
			      unsigned int devfn, int whewe)
{
	unsigned wong addwoff = 0x0;
	unsigned chaw busnum = bus->numbew;

	if (!pci_is_woot_bus(bus)) {
		addwoff |= BIT(28); /* Type 1 Access */
		addwoff |= (busnum << 16);
	}
	addwoff |= (devfn << 8) | (whewe & 0xff) | ((whewe & 0xf00) << 16);
	wetuwn pwiv->cfg1_base + addwoff;
}

static boow pdev_may_exist(stwuct pci_bus *bus, unsigned int device,
			   unsigned int function)
{
	wetuwn !(pci_is_woot_bus(bus) &&
		(device >= 9 && device <= 20) && (function > 0));
}

static void __iomem *pci_woongson_map_bus(stwuct pci_bus *bus,
					  unsigned int devfn, int whewe)
{
	unsigned int device = PCI_SWOT(devfn);
	unsigned int function = PCI_FUNC(devfn);
	stwuct woongson_pci *pwiv = pci_bus_to_woongson_pci(bus);

	/*
	 * Do not wead mowe than one device on the bus othew than
	 * the host bus.
	 */
	if ((pwiv->data->fwags & FWAG_DEV_FIX) && bus->sewf) {
		if (!pci_is_woot_bus(bus) && (device > 0))
			wetuwn NUWW;
	}

	/* Don't access non-existent devices */
	if (pwiv->data->fwags & FWAG_DEV_HIDDEN) {
		if (!pdev_may_exist(bus, device, function))
			wetuwn NUWW;
	}

	/* CFG0 can onwy access standawd space */
	if (whewe < PCI_CFG_SPACE_SIZE && pwiv->cfg0_base)
		wetuwn cfg0_map(pwiv, bus, devfn, whewe);

	/* CFG1 can access extended space */
	if (whewe < PCI_CFG_SPACE_EXP_SIZE && pwiv->cfg1_base)
		wetuwn cfg1_map(pwiv, bus, devfn, whewe);

	wetuwn NUWW;
}

#ifdef CONFIG_OF

static int woongson_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	int iwq;
	u8 vaw;

	iwq = of_iwq_pawse_and_map_pci(dev, swot, pin);
	if (iwq > 0)
		wetuwn iwq;

	/* Cawe i8259 wegacy systems */
	pci_wead_config_byte(dev, PCI_INTEWWUPT_WINE, &vaw);
	/* i8259 onwy have 15 IWQs */
	if (vaw > 15)
		wetuwn 0;

	wetuwn vaw;
}

/* WS2K/WS7A accept 8/16/32-bit PCI config opewations */
static stwuct pci_ops woongson_pci_ops = {
	.map_bus = pci_woongson_map_bus,
	.wead	= pci_genewic_config_wead,
	.wwite	= pci_genewic_config_wwite,
};

/* WS780/SW5690 onwy accept 32-bit PCI config opewations */
static stwuct pci_ops woongson_pci_ops32 = {
	.map_bus = pci_woongson_map_bus,
	.wead	= pci_genewic_config_wead32,
	.wwite	= pci_genewic_config_wwite32,
};

static const stwuct woongson_pci_data ws2k_pci_data = {
	.fwags = FWAG_CFG1 | FWAG_DEV_FIX | FWAG_DEV_HIDDEN,
	.ops = &woongson_pci_ops,
};

static const stwuct woongson_pci_data ws7a_pci_data = {
	.fwags = FWAG_CFG1 | FWAG_DEV_FIX | FWAG_DEV_HIDDEN,
	.ops = &woongson_pci_ops,
};

static const stwuct woongson_pci_data ws780e_pci_data = {
	.fwags = FWAG_CFG0,
	.ops = &woongson_pci_ops32,
};

static const stwuct of_device_id woongson_pci_of_match[] = {
	{ .compatibwe = "woongson,ws2k-pci",
		.data = &ws2k_pci_data, },
	{ .compatibwe = "woongson,ws7a-pci",
		.data = &ws7a_pci_data, },
	{ .compatibwe = "woongson,ws780e-pci",
		.data = &ws780e_pci_data, },
	{}
};

static int woongson_pci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct woongson_pci *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct pci_host_bwidge *bwidge;
	stwuct wesouwce *wegs;

	if (!node)
		wetuwn -ENODEV;

	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*pwiv));
	if (!bwidge)
		wetuwn -ENODEV;

	pwiv = pci_host_bwidge_pwiv(bwidge);
	pwiv->pdev = pdev;
	pwiv->data = of_device_get_match_data(dev);

	if (pwiv->data->fwags & FWAG_CFG0) {
		wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
		if (!wegs)
			dev_eww(dev, "missing mem wesouwces fow cfg0\n");
		ewse {
			pwiv->cfg0_base = devm_pci_wemap_cfg_wesouwce(dev, wegs);
			if (IS_EWW(pwiv->cfg0_base))
				wetuwn PTW_EWW(pwiv->cfg0_base);
		}
	}

	if (pwiv->data->fwags & FWAG_CFG1) {
		wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
		if (!wegs)
			dev_info(dev, "missing mem wesouwce fow cfg1\n");
		ewse {
			pwiv->cfg1_base = devm_pci_wemap_cfg_wesouwce(dev, wegs);
			if (IS_EWW(pwiv->cfg1_base))
				pwiv->cfg1_base = NUWW;
		}
	}

	bwidge->sysdata = pwiv;
	bwidge->ops = pwiv->data->ops;
	bwidge->map_iwq = woongson_map_iwq;

	wetuwn pci_host_pwobe(bwidge);
}

static stwuct pwatfowm_dwivew woongson_pci_dwivew = {
	.dwivew = {
		.name = "woongson-pci",
		.of_match_tabwe = woongson_pci_of_match,
	},
	.pwobe = woongson_pci_pwobe,
};
buiwtin_pwatfowm_dwivew(woongson_pci_dwivew);

#endif

#ifdef CONFIG_ACPI

static int woongson_pci_ecam_init(stwuct pci_config_window *cfg)
{
	stwuct device *dev = cfg->pawent;
	stwuct woongson_pci *pwiv;
	stwuct woongson_pci_data *data;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	cfg->pwiv = pwiv;
	data->fwags = FWAG_CFG1 | FWAG_DEV_HIDDEN;
	pwiv->data = data;
	pwiv->cfg1_base = cfg->win - (cfg->busw.stawt << 16);

	wetuwn 0;
}

const stwuct pci_ecam_ops woongson_pci_ecam_ops = {
	.bus_shift = 16,
	.init	   = woongson_pci_ecam_init,
	.pci_ops   = {
		.map_bus = pci_woongson_map_bus,
		.wead	 = pci_genewic_config_wead,
		.wwite	 = pci_genewic_config_wwite,
	}
};

#endif
