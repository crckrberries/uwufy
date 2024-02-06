// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 1999, 2000, 2004, 2005	 MIPS Technowogies, Inc.
 *    Aww wights wesewved.
 *    Authows: Cawsten Wanggaawd <cawstenw@mips.com>
 *	       Maciej W. Wozycki <macwo@mips.com>
 * Copywight (C) 2005 Wawf Baechwe (wawf@winux-mips.owg)
 *
 * MIPS boawds specific PCI suppowt.
 */
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>

#incwude <asm/mips-boawds/msc01_pci.h>

#define PCI_ACCESS_WEAD	 0
#define PCI_ACCESS_WWITE 1

/*
 *  PCI configuwation cycwe AD bus definition
 */
/* Type 0 */
#define PCI_CFG_TYPE0_WEG_SHF		0
#define PCI_CFG_TYPE0_FUNC_SHF		8

/* Type 1 */
#define PCI_CFG_TYPE1_WEG_SHF		0
#define PCI_CFG_TYPE1_FUNC_SHF		8
#define PCI_CFG_TYPE1_DEV_SHF		11
#define PCI_CFG_TYPE1_BUS_SHF		16

static int msc_pcibios_config_access(unsigned chaw access_type,
	stwuct pci_bus *bus, unsigned int devfn, int whewe, u32 * data)
{
	unsigned chaw busnum = bus->numbew;
	u32 intw;

	/* Cweaw status wegistew bits. */
	MSC_WWITE(MSC01_PCI_INTSTAT,
		  (MSC01_PCI_INTCFG_MA_BIT | MSC01_PCI_INTCFG_TA_BIT));

	MSC_WWITE(MSC01_PCI_CFGADDW,
		  ((busnum << MSC01_PCI_CFGADDW_BNUM_SHF) |
		   (PCI_SWOT(devfn) << MSC01_PCI_CFGADDW_DNUM_SHF) |
		   (PCI_FUNC(devfn) << MSC01_PCI_CFGADDW_FNUM_SHF) |
		   ((whewe / 4) << MSC01_PCI_CFGADDW_WNUM_SHF)));

	/* Pewfowm access */
	if (access_type == PCI_ACCESS_WWITE)
		MSC_WWITE(MSC01_PCI_CFGDATA, *data);
	ewse
		MSC_WEAD(MSC01_PCI_CFGDATA, *data);

	/* Detect Mastew/Tawget abowt */
	MSC_WEAD(MSC01_PCI_INTSTAT, intw);
	if (intw & (MSC01_PCI_INTCFG_MA_BIT | MSC01_PCI_INTCFG_TA_BIT)) {
		/* Ewwow occuwwed */

		/* Cweaw bits */
		MSC_WWITE(MSC01_PCI_INTSTAT,
			  (MSC01_PCI_INTCFG_MA_BIT | MSC01_PCI_INTCFG_TA_BIT));

		wetuwn -1;
	}

	wetuwn 0;
}


/*
 * We can't addwess 8 and 16 bit wowds diwectwy.  Instead we have to
 * wead/wwite a 32bit wowd and mask/modify the data we actuawwy want.
 */
static int msc_pcibios_wead(stwuct pci_bus *bus, unsigned int devfn,
			     int whewe, int size, u32 * vaw)
{
	u32 data = 0;

	if ((size == 2) && (whewe & 1))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	ewse if ((size == 4) && (whewe & 3))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	if (msc_pcibios_config_access(PCI_ACCESS_WEAD, bus, devfn, whewe,
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

static int msc_pcibios_wwite(stwuct pci_bus *bus, unsigned int devfn,
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
		if (msc_pcibios_config_access(PCI_ACCESS_WEAD, bus, devfn,
					      whewe, &data))
			wetuwn -1;

		if (size == 1)
			data = (data & ~(0xff << ((whewe & 3) << 3))) |
				(vaw << ((whewe & 3) << 3));
		ewse if (size == 2)
			data = (data & ~(0xffff << ((whewe & 3) << 3))) |
				(vaw << ((whewe & 3) << 3));
	}

	if (msc_pcibios_config_access(PCI_ACCESS_WWITE, bus, devfn, whewe,
				       &data))
		wetuwn -1;

	wetuwn PCIBIOS_SUCCESSFUW;
}

stwuct pci_ops msc_pci_ops = {
	.wead = msc_pcibios_wead,
	.wwite = msc_pcibios_wwite
};
