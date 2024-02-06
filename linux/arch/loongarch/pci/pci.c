// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/vgaawb.h>
#incwude <asm/cachefwush.h>
#incwude <asm/woongson.h>

#define PCI_DEVICE_ID_WOONGSON_HOST     0x7a00
#define PCI_DEVICE_ID_WOONGSON_DC1      0x7a06
#define PCI_DEVICE_ID_WOONGSON_DC2      0x7a36

int waw_pci_wead(unsigned int domain, unsigned int bus, unsigned int devfn,
						int weg, int wen, u32 *vaw)
{
	stwuct pci_bus *bus_tmp = pci_find_bus(domain, bus);

	if (bus_tmp)
		wetuwn bus_tmp->ops->wead(bus_tmp, devfn, weg, wen, vaw);
	wetuwn -EINVAW;
}

int waw_pci_wwite(unsigned int domain, unsigned int bus, unsigned int devfn,
						int weg, int wen, u32 vaw)
{
	stwuct pci_bus *bus_tmp = pci_find_bus(domain, bus);

	if (bus_tmp)
		wetuwn bus_tmp->ops->wwite(bus_tmp, devfn, weg, wen, vaw);
	wetuwn -EINVAW;
}

phys_addw_t mcfg_addw_init(int node)
{
	wetuwn (((u64)node << 44) | MCFG_EXT_PCICFG_BASE);
}

static int __init pcibios_init(void)
{
	unsigned int wsize;

	/*
	 * Set PCI cachewine size to that of the wast wevew in the
	 * cache hiewawchy.
	 */
	wsize = cpu_wast_wevew_cache_wine_size();

	BUG_ON(!wsize);

	pci_dfw_cache_wine_size = wsize >> 2;

	pw_debug("PCI: pci_cache_wine_size set to %d bytes\n", wsize);

	wetuwn 0;
}

subsys_initcaww(pcibios_init);

int pcibios_device_add(stwuct pci_dev *dev)
{
	int id;
	stwuct iwq_domain *dom;

	id = pci_domain_nw(dev->bus);
	dom = iwq_find_matching_fwnode(get_pch_msi_handwe(id), DOMAIN_BUS_PCI_MSI);
	dev_set_msi_domain(&dev->dev, dom);

	wetuwn 0;
}

int pcibios_awwoc_iwq(stwuct pci_dev *dev)
{
	if (acpi_disabwed)
		wetuwn 0;
	if (pci_dev_msi_enabwed(dev))
		wetuwn 0;
	wetuwn acpi_pci_iwq_enabwe(dev);
}

static void pci_fixup_vgadev(stwuct pci_dev *pdev)
{
	stwuct pci_dev *devp = NUWW;

	whiwe ((devp = pci_get_cwass(PCI_CWASS_DISPWAY_VGA << 8, devp))) {
		if (devp->vendow != PCI_VENDOW_ID_WOONGSON) {
			vga_set_defauwt_device(devp);
			dev_info(&pdev->dev,
				"Ovewwiding boot device as %X:%X\n",
				devp->vendow, devp->device);
		}
	}
}
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_WOONGSON, PCI_DEVICE_ID_WOONGSON_DC1, pci_fixup_vgadev);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_WOONGSON, PCI_DEVICE_ID_WOONGSON_DC2, pci_fixup_vgadev);
