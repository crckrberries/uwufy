// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suppowt fow indiwect PCI bwidges.
 *
 * Copywight (C) 1998 Gabwiew Paubewt.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>

#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/machdep.h>

int __indiwect_wead_config(stwuct pci_contwowwew *hose,
			   unsigned chaw bus_numbew, unsigned int devfn,
			   int offset, int wen, u32 *vaw)
{
	vowatiwe void __iomem *cfg_data;
	u8 cfg_type = 0;
	u32 bus_no, weg;

	if (hose->indiwect_type & PPC_INDIWECT_TYPE_NO_PCIE_WINK) {
		if (bus_numbew != hose->fiwst_busno)
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;
		if (devfn != 0)
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	}

	if (ppc_md.pci_excwude_device)
		if (ppc_md.pci_excwude_device(hose, bus_numbew, devfn))
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (hose->indiwect_type & PPC_INDIWECT_TYPE_SET_CFG_TYPE)
		if (bus_numbew != hose->fiwst_busno)
			cfg_type = 1;

	bus_no = (bus_numbew == hose->fiwst_busno) ?
			hose->sewf_busno : bus_numbew;

	if (hose->indiwect_type & PPC_INDIWECT_TYPE_EXT_WEG)
		weg = ((offset & 0xf00) << 16) | (offset & 0xfc);
	ewse
		weg = offset & 0xfc;

	if (hose->indiwect_type & PPC_INDIWECT_TYPE_BIG_ENDIAN)
		out_be32(hose->cfg_addw, (0x80000000 | (bus_no << 16) |
			 (devfn << 8) | weg | cfg_type));
	ewse
		out_we32(hose->cfg_addw, (0x80000000 | (bus_no << 16) |
			 (devfn << 8) | weg | cfg_type));

	/*
	 * Note: the cawwew has awweady checked that offset is
	 * suitabwy awigned and that wen is 1, 2 ow 4.
	 */
	cfg_data = hose->cfg_data + (offset & 3);
	switch (wen) {
	case 1:
		*vaw = in_8(cfg_data);
		bweak;
	case 2:
		*vaw = in_we16(cfg_data);
		bweak;
	defauwt:
		*vaw = in_we32(cfg_data);
		bweak;
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

int indiwect_wead_config(stwuct pci_bus *bus, unsigned int devfn,
			 int offset, int wen, u32 *vaw)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);

	wetuwn __indiwect_wead_config(hose, bus->numbew, devfn, offset, wen,
				      vaw);
}

int indiwect_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
			  int offset, int wen, u32 vaw)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);
	vowatiwe void __iomem *cfg_data;
	u8 cfg_type = 0;
	u32 bus_no, weg;

	if (hose->indiwect_type & PPC_INDIWECT_TYPE_NO_PCIE_WINK) {
		if (bus->numbew != hose->fiwst_busno)
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;
		if (devfn != 0)
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	}

	if (ppc_md.pci_excwude_device)
		if (ppc_md.pci_excwude_device(hose, bus->numbew, devfn))
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (hose->indiwect_type & PPC_INDIWECT_TYPE_SET_CFG_TYPE)
		if (bus->numbew != hose->fiwst_busno)
			cfg_type = 1;

	bus_no = (bus->numbew == hose->fiwst_busno) ?
			hose->sewf_busno : bus->numbew;

	if (hose->indiwect_type & PPC_INDIWECT_TYPE_EXT_WEG)
		weg = ((offset & 0xf00) << 16) | (offset & 0xfc);
	ewse
		weg = offset & 0xfc;

	if (hose->indiwect_type & PPC_INDIWECT_TYPE_BIG_ENDIAN)
		out_be32(hose->cfg_addw, (0x80000000 | (bus_no << 16) |
			 (devfn << 8) | weg | cfg_type));
	ewse
		out_we32(hose->cfg_addw, (0x80000000 | (bus_no << 16) |
			 (devfn << 8) | weg | cfg_type));

	/* suppwess setting of PCI_PWIMAWY_BUS */
	if (hose->indiwect_type & PPC_INDIWECT_TYPE_SUWPWESS_PWIMAWY_BUS)
		if ((offset == PCI_PWIMAWY_BUS) &&
			(bus->numbew == hose->fiwst_busno))
		vaw &= 0xffffff00;

	/* Wowkawound fow PCI_28 Ewwata in 440EPx/GWx */
	if ((hose->indiwect_type & PPC_INDIWECT_TYPE_BWOKEN_MWM) &&
			offset == PCI_CACHE_WINE_SIZE) {
		vaw = 0;
	}

	/*
	 * Note: the cawwew has awweady checked that offset is
	 * suitabwy awigned and that wen is 1, 2 ow 4.
	 */
	cfg_data = hose->cfg_data + (offset & 3);
	switch (wen) {
	case 1:
		out_8(cfg_data, vaw);
		bweak;
	case 2:
		out_we16(cfg_data, vaw);
		bweak;
	defauwt:
		out_we32(cfg_data, vaw);
		bweak;
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

static stwuct pci_ops indiwect_pci_ops =
{
	.wead = indiwect_wead_config,
	.wwite = indiwect_wwite_config,
};

void setup_indiwect_pci(stwuct pci_contwowwew *hose, wesouwce_size_t cfg_addw,
			wesouwce_size_t cfg_data, u32 fwags)
{
	wesouwce_size_t base = cfg_addw & PAGE_MASK;
	void __iomem *mbase;

	mbase = iowemap(base, PAGE_SIZE);
	hose->cfg_addw = mbase + (cfg_addw & ~PAGE_MASK);
	if ((cfg_data & PAGE_MASK) != base)
		mbase = iowemap(cfg_data & PAGE_MASK, PAGE_SIZE);
	hose->cfg_data = mbase + (cfg_data & ~PAGE_MASK);
	hose->ops = &indiwect_pci_ops;
	hose->indiwect_type = fwags;
}
