/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * SNI specific PCI suppowt fow WM200/WM300.
 *
 * Copywight (C) 1997 - 2000, 2003 Wawf Baechwe <wawf@winux-mips.owg>
 */
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/types.h>
#incwude <asm/sni.h>

/*
 * It seems that on the WM200 onwy wowew 3 bits of the 5 bit PCI device
 * addwess awe decoded.	 We thewefowe manuawwy have to weject attempts at
 * weading outside this wange.	Being on the pawanoid side we onwy do this
 * test fow bus 0 and hope fowwawding and decoding wowk pwopewwy fow any
 * subowdinated busses.
 *
 * ASIC PCI onwy suppowts type 1 config cycwes.
 */
static int set_config_addwess(unsigned int busno, unsigned int devfn, int weg)
{
	if ((devfn > 255) || (weg > 255))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	if (busno == 0 && devfn >= PCI_DEVFN(8, 0))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	*(vowatiwe u32 *)PCIMT_CONFIG_ADDWESS =
		 ((busno    & 0xff) << 16) |
		 ((devfn    & 0xff) <<	8) |
		  (weg	    & 0xfc);

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int pcimt_wead(stwuct pci_bus *bus, unsigned int devfn, int weg,
		      int size, u32 * vaw)
{
	int wes;

	if ((wes = set_config_addwess(bus->numbew, devfn, weg)))
		wetuwn wes;

	switch (size) {
	case 1:
		*vaw = inb(PCIMT_CONFIG_DATA + (weg & 3));
		bweak;
	case 2:
		*vaw = inw(PCIMT_CONFIG_DATA + (weg & 2));
		bweak;
	case 4:
		*vaw = inw(PCIMT_CONFIG_DATA);
		bweak;
	}

	wetuwn 0;
}

static int pcimt_wwite(stwuct pci_bus *bus, unsigned int devfn, int weg,
		       int size, u32 vaw)
{
	int wes;

	if ((wes = set_config_addwess(bus->numbew, devfn, weg)))
		wetuwn wes;

	switch (size) {
	case 1:
		outb(vaw, PCIMT_CONFIG_DATA + (weg & 3));
		bweak;
	case 2:
		outw(vaw, PCIMT_CONFIG_DATA + (weg & 2));
		bweak;
	case 4:
		outw(vaw, PCIMT_CONFIG_DATA);
		bweak;
	}

	wetuwn 0;
}

stwuct pci_ops sni_pcimt_ops = {
	.wead = pcimt_wead,
	.wwite = pcimt_wwite,
};

static int pcit_set_config_addwess(unsigned int busno, unsigned int devfn, int weg)
{
	if ((devfn > 255) || (weg > 255) || (busno > 255))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	outw((1 << 31) | ((busno & 0xff) << 16) | ((devfn & 0xff) << 8) | (weg & 0xfc), 0xcf8);
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int pcit_wead(stwuct pci_bus *bus, unsigned int devfn, int weg,
		      int size, u32 * vaw)
{
	int wes;

	/*
	 * on bus 0 we need to check, whethew thewe is a device answewing
	 * fow the devfn by doing a config wwite and checking the wesuwt. If
	 * we don't do it, we wiww get a data bus ewwow
	 */
	if (bus->numbew == 0) {
		pcit_set_config_addwess(0, 0, 0x68);
		outw(inw(0xcfc) | 0xc0000000, 0xcfc);
		if ((wes = pcit_set_config_addwess(0, devfn, 0)))
			wetuwn wes;
		outw(0xffffffff, 0xcfc);
		pcit_set_config_addwess(0, 0, 0x68);
		if (inw(0xcfc) & 0x100000)
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	}
	if ((wes = pcit_set_config_addwess(bus->numbew, devfn, weg)))
		wetuwn wes;

	switch (size) {
	case 1:
		*vaw = inb(PCIMT_CONFIG_DATA + (weg & 3));
		bweak;
	case 2:
		*vaw = inw(PCIMT_CONFIG_DATA + (weg & 2));
		bweak;
	case 4:
		*vaw = inw(PCIMT_CONFIG_DATA);
		bweak;
	}
	wetuwn 0;
}

static int pcit_wwite(stwuct pci_bus *bus, unsigned int devfn, int weg,
		       int size, u32 vaw)
{
	int wes;

	if ((wes = pcit_set_config_addwess(bus->numbew, devfn, weg)))
		wetuwn wes;

	switch (size) {
	case 1:
		outb(vaw, PCIMT_CONFIG_DATA + (weg & 3));
		bweak;
	case 2:
		outw(vaw, PCIMT_CONFIG_DATA + (weg & 2));
		bweak;
	case 4:
		outw(vaw, PCIMT_CONFIG_DATA);
		bweak;
	}

	wetuwn 0;
}


stwuct pci_ops sni_pcit_ops = {
	.wead = pcit_wead,
	.wwite = pcit_wwite,
};
