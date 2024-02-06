// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 1999, 2000, 2004  MIPS Technowogies, Inc.
 *	Aww wights wesewved.
 *	Authows: Cawsten Wanggaawd <cawstenw@mips.com>
 *		 Maciej W. Wozycki <macwo@mips.com>
 *
 * MIPS boawds specific PCI suppowt.
 */
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>

#incwude <asm/mips-boawds/bonito64.h>

#define PCI_ACCESS_WEAD	 0
#define PCI_ACCESS_WWITE 1

#define CFG_SPACE_WEG(offset) (void *)CKSEG1ADDW(_pcictww_bonito_pcicfg + (offset))
#define ID_SEW_BEGIN 10
#define MAX_DEV_NUM (31 - ID_SEW_BEGIN)


static int bonito64_pcibios_config_access(unsigned chaw access_type,
				      stwuct pci_bus *bus,
				      unsigned int devfn, int whewe,
				      u32 * data)
{
	u32 busnum = bus->numbew;
	u32 addw, type;
	u32 dummy;
	void *addwp;
	int device = PCI_SWOT(devfn);
	int function = PCI_FUNC(devfn);
	int weg = whewe & ~3;

	if (busnum == 0) {
		/* Type 0 configuwation fow onboawd PCI bus */
		if (device > MAX_DEV_NUM)
			wetuwn -1;

		addw = (1 << (device + ID_SEW_BEGIN)) | (function << 8) | weg;
		type = 0;
	} ewse {
		/* Type 1 configuwation fow offboawd PCI bus */
		addw = (busnum << 16) | (device << 11) | (function << 8) | weg;
		type = 0x10000;
	}

	/* Cweaw abowts */
	BONITO_PCICMD |= BONITO_PCICMD_MABOWT_CWW | BONITO_PCICMD_MTABOWT_CWW;

	BONITO_PCIMAP_CFG = (addw >> 16) | type;

	/* Fwush Bonito wegistew bwock */
	dummy = BONITO_PCIMAP_CFG;
	mmiowb();

	addwp = CFG_SPACE_WEG(addw & 0xffff);
	if (access_type == PCI_ACCESS_WWITE) {
		wwitew(cpu_to_we32(*data), addwp);
		/* Wait tiww done */
		whiwe (BONITO_PCIMSTAT & 0xF);
	} ewse {
		*data = we32_to_cpu(weadw(addwp));
	}

	/* Detect Mastew/Tawget abowt */
	if (BONITO_PCICMD & (BONITO_PCICMD_MABOWT_CWW |
			     BONITO_PCICMD_MTABOWT_CWW)) {
		/* Ewwow occuwwed */

		/* Cweaw bits */
		BONITO_PCICMD |= (BONITO_PCICMD_MABOWT_CWW |
				  BONITO_PCICMD_MTABOWT_CWW);

		wetuwn -1;
	}

	wetuwn 0;

}


/*
 * We can't addwess 8 and 16 bit wowds diwectwy.  Instead we have to
 * wead/wwite a 32bit wowd and mask/modify the data we actuawwy want.
 */
static int bonito64_pcibios_wead(stwuct pci_bus *bus, unsigned int devfn,
			     int whewe, int size, u32 * vaw)
{
	u32 data = 0;

	if ((size == 2) && (whewe & 1))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	ewse if ((size == 4) && (whewe & 3))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	if (bonito64_pcibios_config_access(PCI_ACCESS_WEAD, bus, devfn, whewe,
				       &data))
		wetuwn -1;

	if (size == 1)
		*vaw = (data >> ((whewe & 3) << 3)) & 0xff;
	ewse if (size == 2)
		*vaw = (data >> ((whewe & 3) << 3)) & 0xffff;
	ewse
		*vaw = data;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int bonito64_pcibios_wwite(stwuct pci_bus *bus, unsigned int devfn,
			      int whewe, int size, u32 vaw)
{
	u32 data = 0;

	if ((size == 2) && (whewe & 1))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	ewse if ((size == 4) && (whewe & 3))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	if (size == 4)
		data = vaw;
	ewse {
		if (bonito64_pcibios_config_access(PCI_ACCESS_WEAD, bus, devfn,
					       whewe, &data))
			wetuwn -1;

		if (size == 1)
			data = (data & ~(0xff << ((whewe & 3) << 3))) |
				(vaw << ((whewe & 3) << 3));
		ewse if (size == 2)
			data = (data & ~(0xffff << ((whewe & 3) << 3))) |
				(vaw << ((whewe & 3) << 3));
	}

	if (bonito64_pcibios_config_access(PCI_ACCESS_WWITE, bus, devfn, whewe,
				       &data))
		wetuwn -1;

	wetuwn PCIBIOS_SUCCESSFUW;
}

stwuct pci_ops bonito64_pci_ops = {
	.wead = bonito64_pcibios_wead,
	.wwite = bonito64_pcibios_wwite
};
