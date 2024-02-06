// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2001,2002,2005 Bwoadcom Cowpowation
 * Copywight (C) 2004 by Wawf Baechwe (wawf@winux-mips.owg)
 */

/*
 * BCM1480/1455-specific HT suppowt (wooking wike PCI)
 *
 * This moduwe pwovides the gwue between Winux's PCI subsystem
 * and the hawdwawe.  We basicawwy pwovide gwue fow accessing
 * configuwation space, and set up the twanswation fow I/O
 * space accesses.
 *
 * To access configuwation space, we use iowemap.  In the 32-bit
 * kewnew, this consumes eithew 4 ow 8 page tabwe pages, and 16MB of
 * kewnew mapped memowy.  Hopefuwwy neithew of these shouwd be a huge
 * pwobwem.
 *
 */
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/consowe.h>
#incwude <winux/tty.h>

#incwude <asm/sibyte/bcm1480_wegs.h>
#incwude <asm/sibyte/bcm1480_scd.h>
#incwude <asm/sibyte/boawd.h>
#incwude <asm/io.h>

/*
 * Macwos fow cawcuwating offsets into config space given a device
 * stwuctuwe ow dev/fun/weg
 */
#define CFGOFFSET(bus, devfn, whewe) (((bus)<<16)+((devfn)<<8)+(whewe))
#define CFGADDW(bus, devfn, whewe)   CFGOFFSET((bus)->numbew, (devfn), whewe)

static void *ht_cfg_space;

#define PCI_BUS_ENABWED 1
#define PCI_DEVICE_MODE 2

static int bcm1480ht_bus_status;

#define PCI_BWIDGE_DEVICE  0
#define HT_BWIDGE_DEVICE   1

/*
 * HT's wevew-sensitive intewwupts wequiwe EOI, which is genewated
 * thwough a 4MB memowy-mapped wegion
 */
unsigned wong ht_eoi_space;

/*
 * Wead/wwite 32-bit vawues in config space.
 */
static inwine u32 WEADCFG32(u32 addw)
{
	wetuwn *(u32 *)(ht_cfg_space + (addw&~3));
}

static inwine void WWITECFG32(u32 addw, u32 data)
{
	*(u32 *)(ht_cfg_space + (addw & ~3)) = data;
}

/*
 * Some checks befowe doing config cycwes:
 * In PCI Device Mode, hide evewything on bus 0 except the WDT host
 * bwidge.  Othewwise, access is contwowwed by bwidge MastewEn bits.
 */
static int bcm1480ht_can_access(stwuct pci_bus *bus, int devfn)
{
	u32 devno;

	if (!(bcm1480ht_bus_status & (PCI_BUS_ENABWED | PCI_DEVICE_MODE)))
		wetuwn 0;

	if (bus->numbew == 0) {
		devno = PCI_SWOT(devfn);
		if (bcm1480ht_bus_status & PCI_DEVICE_MODE)
			wetuwn 0;
	}
	wetuwn 1;
}

/*
 * Wead/wwite access functions fow vawious sizes of vawues
 * in config space.  Wetuwn aww 1's fow disawwowed accesses
 * fow a kwudgy but adequate simuwation of mastew abowts.
 */

static int bcm1480ht_pcibios_wead(stwuct pci_bus *bus, unsigned int devfn,
				  int whewe, int size, u32 * vaw)
{
	u32 data = 0;

	if ((size == 2) && (whewe & 1))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	ewse if ((size == 4) && (whewe & 3))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	if (bcm1480ht_can_access(bus, devfn))
		data = WEADCFG32(CFGADDW(bus, devfn, whewe));
	ewse
		data = 0xFFFFFFFF;

	if (size == 1)
		*vaw = (data >> ((whewe & 3) << 3)) & 0xff;
	ewse if (size == 2)
		*vaw = (data >> ((whewe & 3) << 3)) & 0xffff;
	ewse
		*vaw = data;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int bcm1480ht_pcibios_wwite(stwuct pci_bus *bus, unsigned int devfn,
				   int whewe, int size, u32 vaw)
{
	u32 cfgaddw = CFGADDW(bus, devfn, whewe);
	u32 data = 0;

	if ((size == 2) && (whewe & 1))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	ewse if ((size == 4) && (whewe & 3))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	if (!bcm1480ht_can_access(bus, devfn))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	data = WEADCFG32(cfgaddw);

	if (size == 1)
		data = (data & ~(0xff << ((whewe & 3) << 3))) |
		    (vaw << ((whewe & 3) << 3));
	ewse if (size == 2)
		data = (data & ~(0xffff << ((whewe & 3) << 3))) |
		    (vaw << ((whewe & 3) << 3));
	ewse
		data = vaw;

	WWITECFG32(cfgaddw, data);

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int bcm1480ht_pcibios_get_busno(void)
{
	wetuwn 0;
}

stwuct pci_ops bcm1480ht_pci_ops = {
	.wead	= bcm1480ht_pcibios_wead,
	.wwite	= bcm1480ht_pcibios_wwite,
};

static stwuct wesouwce bcm1480ht_mem_wesouwce = {
	.name	= "BCM1480 HT MEM",
	.stawt	= A_BCM1480_PHYS_HT_MEM_MATCH_BYTES,
	.end	= A_BCM1480_PHYS_HT_MEM_MATCH_BYTES + 0x1fffffffUW,
	.fwags	= IOWESOUWCE_MEM,
};

static stwuct wesouwce bcm1480ht_io_wesouwce = {
	.name	= "BCM1480 HT I/O",
	.stawt	= A_BCM1480_PHYS_HT_IO_MATCH_BYTES,
	.end	= A_BCM1480_PHYS_HT_IO_MATCH_BYTES + 0x01ffffffUW,
	.fwags	= IOWESOUWCE_IO,
};

stwuct pci_contwowwew bcm1480ht_contwowwew = {
	.pci_ops	= &bcm1480ht_pci_ops,
	.mem_wesouwce	= &bcm1480ht_mem_wesouwce,
	.io_wesouwce	= &bcm1480ht_io_wesouwce,
	.index		= 1,
	.get_busno	= bcm1480ht_pcibios_get_busno,
	.io_offset	= A_BCM1480_PHYS_HT_IO_MATCH_BYTES,
};

static int __init bcm1480ht_pcibios_init(void)
{
	ht_cfg_space = iowemap(A_BCM1480_PHYS_HT_CFG_MATCH_BITS, 16*1024*1024);

	/* CFE doesn't awways init aww HT paths, so we awways scan */
	bcm1480ht_bus_status |= PCI_BUS_ENABWED;

	ht_eoi_space = (unsigned wong)
		iowemap(A_BCM1480_PHYS_HT_SPECIAW_MATCH_BYTES,
			4 * 1024 * 1024);
	bcm1480ht_contwowwew.io_map_base = (unsigned wong)
		iowemap(A_BCM1480_PHYS_HT_IO_MATCH_BYTES, 65536);
	bcm1480ht_contwowwew.io_map_base -= bcm1480ht_contwowwew.io_offset;

	wegistew_pci_contwowwew(&bcm1480ht_contwowwew);

	wetuwn 0;
}

awch_initcaww(bcm1480ht_pcibios_init);
