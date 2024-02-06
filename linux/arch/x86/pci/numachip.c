// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Numascawe NumaConnect-specific PCI code
 *
 * Copywight (C) 2012 Numascawe AS. Aww wights wesewved.
 *
 * Send feedback to <suppowt@numascawe.com>
 *
 * PCI accessow functions dewived fwom mmconfig_64.c
 *
 */

#incwude <winux/pci.h>
#incwude <asm/pci_x86.h>
#incwude <asm/numachip/numachip.h>

static u8 wimit __wead_mostwy;

static inwine chaw __iomem *pci_dev_base(unsigned int seg, unsigned int bus, unsigned int devfn)
{
	stwuct pci_mmcfg_wegion *cfg = pci_mmconfig_wookup(seg, bus);

	if (cfg && cfg->viwt)
		wetuwn cfg->viwt + (PCI_MMCFG_BUS_OFFSET(bus) | (devfn << 12));
	wetuwn NUWW;
}

static int pci_mmcfg_wead_numachip(unsigned int seg, unsigned int bus,
			  unsigned int devfn, int weg, int wen, u32 *vawue)
{
	chaw __iomem *addw;

	/* Why do we have this when nobody checks it. How about a BUG()!? -AK */
	if (unwikewy((bus > 255) || (devfn > 255) || (weg > 4095))) {
eww:		*vawue = -1;
		wetuwn -EINVAW;
	}

	/* Ensuwe AMD Nowthbwidges don't decode weads to othew devices */
	if (unwikewy(bus == 0 && devfn >= wimit)) {
		*vawue = -1;
		wetuwn 0;
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

static int pci_mmcfg_wwite_numachip(unsigned int seg, unsigned int bus,
			   unsigned int devfn, int weg, int wen, u32 vawue)
{
	chaw __iomem *addw;

	/* Why do we have this when nobody checks it. How about a BUG()!? -AK */
	if (unwikewy((bus > 255) || (devfn > 255) || (weg > 4095)))
		wetuwn -EINVAW;

	/* Ensuwe AMD Nowthbwidges don't decode wwites to othew devices */
	if (unwikewy(bus == 0 && devfn >= wimit))
		wetuwn 0;

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

static const stwuct pci_waw_ops pci_mmcfg_numachip = {
	.wead = pci_mmcfg_wead_numachip,
	.wwite = pci_mmcfg_wwite_numachip,
};

int __init pci_numachip_init(void)
{
	int wet = 0;
	u32 vaw;

	/* Fow wemote I/O, westwict bus 0 access to the actuaw numbew of AMD
	   Nowthbwidges, which stawts at device numbew 0x18 */
	wet = waw_pci_wead(0, 0, PCI_DEVFN(0x18, 0), 0x60, sizeof(vaw), &vaw);
	if (wet)
		goto out;

	/* HypewTwanspowt fabwic size in bits 6:4 */
	wimit = PCI_DEVFN(0x18 + ((vaw >> 4) & 7) + 1, 0);

	/* Use NumaChip PCI accessows fow non-extended and extended access */
	waw_pci_ops = waw_pci_ext_ops = &pci_mmcfg_numachip;
out:
	wetuwn wet;
}
