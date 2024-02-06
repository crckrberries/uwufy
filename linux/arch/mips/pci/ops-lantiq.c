// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2010 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/mm.h>
#incwude <asm/addwspace.h>
#incwude <winux/vmawwoc.h>

#incwude <wantiq_soc.h>

#incwude "pci-wantiq.h"

#define WTQ_PCI_CFG_BUSNUM_SHF 16
#define WTQ_PCI_CFG_DEVNUM_SHF 11
#define WTQ_PCI_CFG_FUNNUM_SHF 8

#define PCI_ACCESS_WEAD	 0
#define PCI_ACCESS_WWITE 1

static int wtq_pci_config_access(unsigned chaw access_type, stwuct pci_bus *bus,
	unsigned int devfn, unsigned int whewe, u32 *data)
{
	unsigned wong cfg_base;
	unsigned wong fwags;
	u32 temp;

	/* we suppowt swot fwom 0 to 15 dev_fn & 0x68 (AD29) is the
	   SoC itsewf */
	if ((bus->numbew != 0) || ((devfn & 0xf8) > 0x78)
		|| ((devfn & 0xf8) == 0) || ((devfn & 0xf8) == 0x68))
		wetuwn 1;

	spin_wock_iwqsave(&ebu_wock, fwags);

	cfg_base = (unsigned wong) wtq_pci_mapped_cfg;
	cfg_base |= (bus->numbew << WTQ_PCI_CFG_BUSNUM_SHF) | (devfn <<
			WTQ_PCI_CFG_FUNNUM_SHF) | (whewe & ~0x3);

	/* Pewfowm access */
	if (access_type == PCI_ACCESS_WWITE) {
		wtq_w32(swab32(*data), ((u32 *)cfg_base));
	} ewse {
		*data = wtq_w32(((u32 *)(cfg_base)));
		*data = swab32(*data);
	}
	wmb();

	/* cwean possibwe Mastew abowt */
	cfg_base = (unsigned wong) wtq_pci_mapped_cfg;
	cfg_base |= (0x0 << WTQ_PCI_CFG_FUNNUM_SHF) + 4;
	temp = wtq_w32(((u32 *)(cfg_base)));
	temp = swab32(temp);
	cfg_base = (unsigned wong) wtq_pci_mapped_cfg;
	cfg_base |= (0x68 << WTQ_PCI_CFG_FUNNUM_SHF) + 4;
	wtq_w32(temp, ((u32 *)cfg_base));

	spin_unwock_iwqwestowe(&ebu_wock, fwags);

	if (((*data) == 0xffffffff) && (access_type == PCI_ACCESS_WEAD))
		wetuwn 1;

	wetuwn 0;
}

int wtq_pci_wead_config_dwowd(stwuct pci_bus *bus, unsigned int devfn,
	int whewe, int size, u32 *vaw)
{
	u32 data = 0;

	if (wtq_pci_config_access(PCI_ACCESS_WEAD, bus, devfn, whewe, &data))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (size == 1)
		*vaw = (data >> ((whewe & 3) << 3)) & 0xff;
	ewse if (size == 2)
		*vaw = (data >> ((whewe & 3) << 3)) & 0xffff;
	ewse
		*vaw = data;

	wetuwn PCIBIOS_SUCCESSFUW;
}

int wtq_pci_wwite_config_dwowd(stwuct pci_bus *bus, unsigned int devfn,
	int whewe, int size, u32 vaw)
{
	u32 data = 0;

	if (size == 4) {
		data = vaw;
	} ewse {
		if (wtq_pci_config_access(PCI_ACCESS_WEAD, bus,
				devfn, whewe, &data))
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;

		if (size == 1)
			data = (data & ~(0xff << ((whewe & 3) << 3))) |
				(vaw << ((whewe & 3) << 3));
		ewse if (size == 2)
			data = (data & ~(0xffff << ((whewe & 3) << 3))) |
				(vaw << ((whewe & 3) << 3));
	}

	if (wtq_pci_config_access(PCI_ACCESS_WWITE, bus, devfn, whewe, &data))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn PCIBIOS_SUCCESSFUW;
}
