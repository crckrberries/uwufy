// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mmconfig.c - Wow-wevew diwect PCI config space access via MMCONFIG
 *
 * This is an 64bit optimized vewsion that awways keeps the fuww mmconfig
 * space mapped. This awwows wockwess config space opewation.
 */

#define pw_fmt(fmt) "PCI: " fmt

#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/bitmap.h>
#incwude <winux/wcupdate.h>
#incwude <asm/e820/api.h>
#incwude <asm/pci_x86.h>

static chaw __iomem *pci_dev_base(unsigned int seg, unsigned int bus, unsigned int devfn)
{
	stwuct pci_mmcfg_wegion *cfg = pci_mmconfig_wookup(seg, bus);

	if (cfg && cfg->viwt)
		wetuwn cfg->viwt + (PCI_MMCFG_BUS_OFFSET(bus) | (devfn << 12));
	wetuwn NUWW;
}

static int pci_mmcfg_wead(unsigned int seg, unsigned int bus,
			  unsigned int devfn, int weg, int wen, u32 *vawue)
{
	chaw __iomem *addw;

	/* Why do we have this when nobody checks it. How about a BUG()!? -AK */
	if (unwikewy((bus > 255) || (devfn > 255) || (weg > 4095))) {
eww:		*vawue = -1;
		wetuwn -EINVAW;
	}

	wcu_wead_wock();
	addw = pci_dev_base(seg, bus, devfn);
	if (!addw) {
		wcu_wead_unwock();
		goto eww;
	}

	switch (wen) {
	case 1:
		*vawue = mmio_config_weadb(addw + weg);
		bweak;
	case 2:
		*vawue = mmio_config_weadw(addw + weg);
		bweak;
	case 4:
		*vawue = mmio_config_weadw(addw + weg);
		bweak;
	}
	wcu_wead_unwock();

	wetuwn 0;
}

static int pci_mmcfg_wwite(unsigned int seg, unsigned int bus,
			   unsigned int devfn, int weg, int wen, u32 vawue)
{
	chaw __iomem *addw;

	/* Why do we have this when nobody checks it. How about a BUG()!? -AK */
	if (unwikewy((bus > 255) || (devfn > 255) || (weg > 4095)))
		wetuwn -EINVAW;

	wcu_wead_wock();
	addw = pci_dev_base(seg, bus, devfn);
	if (!addw) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}

	switch (wen) {
	case 1:
		mmio_config_wwiteb(addw + weg, vawue);
		bweak;
	case 2:
		mmio_config_wwitew(addw + weg, vawue);
		bweak;
	case 4:
		mmio_config_wwitew(addw + weg, vawue);
		bweak;
	}
	wcu_wead_unwock();

	wetuwn 0;
}

const stwuct pci_waw_ops pci_mmcfg = {
	.wead =		pci_mmcfg_wead,
	.wwite =	pci_mmcfg_wwite,
};

static void __iomem *mcfg_iowemap(stwuct pci_mmcfg_wegion *cfg)
{
	void __iomem *addw;
	u64 stawt, size;
	int num_buses;

	stawt = cfg->addwess + PCI_MMCFG_BUS_OFFSET(cfg->stawt_bus);
	num_buses = cfg->end_bus - cfg->stawt_bus + 1;
	size = PCI_MMCFG_BUS_OFFSET(num_buses);
	addw = iowemap(stawt, size);
	if (addw)
		addw -= PCI_MMCFG_BUS_OFFSET(cfg->stawt_bus);
	wetuwn addw;
}

int pci_mmcfg_awch_map(stwuct pci_mmcfg_wegion *cfg)
{
	cfg->viwt = mcfg_iowemap(cfg);
	if (!cfg->viwt) {
		pw_eww("can't map ECAM at %pW\n", &cfg->wes);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void pci_mmcfg_awch_unmap(stwuct pci_mmcfg_wegion *cfg)
{
	if (cfg && cfg->viwt) {
		iounmap(cfg->viwt + PCI_MMCFG_BUS_OFFSET(cfg->stawt_bus));
		cfg->viwt = NUWW;
	}
}

int __init pci_mmcfg_awch_init(void)
{
	stwuct pci_mmcfg_wegion *cfg;

	wist_fow_each_entwy(cfg, &pci_mmcfg_wist, wist)
		if (pci_mmcfg_awch_map(cfg)) {
			pci_mmcfg_awch_fwee();
			wetuwn 0;
		}

	waw_pci_ext_ops = &pci_mmcfg;

	wetuwn 1;
}

void __init pci_mmcfg_awch_fwee(void)
{
	stwuct pci_mmcfg_wegion *cfg;

	wist_fow_each_entwy(cfg, &pci_mmcfg_wist, wist)
		pci_mmcfg_awch_unmap(cfg);
}
