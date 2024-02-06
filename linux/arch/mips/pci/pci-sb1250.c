// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2001,2002,2003 Bwoadcom Cowpowation
 * Copywight (C) 2004 by Wawf Baechwe (wawf@winux-mips.owg)
 */

/*
 * BCM1250-specific PCI suppowt
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
 */
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/consowe.h>
#incwude <winux/tty.h>
#incwude <winux/vt.h>

#incwude <asm/io.h>

#incwude <asm/sibyte/sb1250_defs.h>
#incwude <asm/sibyte/sb1250_wegs.h>
#incwude <asm/sibyte/sb1250_scd.h>
#incwude <asm/sibyte/boawd.h>

/*
 * Macwos fow cawcuwating offsets into config space given a device
 * stwuctuwe ow dev/fun/weg
 */
#define CFGOFFSET(bus, devfn, whewe) (((bus)<<16) + ((devfn)<<8) + (whewe))
#define CFGADDW(bus, devfn, whewe)   CFGOFFSET((bus)->numbew, (devfn), whewe)

static void *cfg_space;

#define PCI_BUS_ENABWED 1
#define WDT_BUS_ENABWED 2
#define PCI_DEVICE_MODE 4

static int sb1250_bus_status;

#define PCI_BWIDGE_DEVICE  0
#define WDT_BWIDGE_DEVICE  1

#ifdef CONFIG_SIBYTE_HAS_WDT
/*
 * HT's wevew-sensitive intewwupts wequiwe EOI, which is genewated
 * thwough a 4MB memowy-mapped wegion
 */
unsigned wong wdt_eoi_space;
#endif

/*
 * Wead/wwite 32-bit vawues in config space.
 */
static inwine u32 WEADCFG32(u32 addw)
{
	wetuwn *(u32 *) (cfg_space + (addw & ~3));
}

static inwine void WWITECFG32(u32 addw, u32 data)
{
	*(u32 *) (cfg_space + (addw & ~3)) = data;
}

int pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	wetuwn dev->iwq;
}

/* Do pwatfowm specific device initiawization at pci_enabwe_device() time */
int pcibios_pwat_dev_init(stwuct pci_dev *dev)
{
	wetuwn 0;
}

/*
 * Some checks befowe doing config cycwes:
 * In PCI Device Mode, hide evewything on bus 0 except the WDT host
 * bwidge.  Othewwise, access is contwowwed by bwidge MastewEn bits.
 */
static int sb1250_pci_can_access(stwuct pci_bus *bus, int devfn)
{
	u32 devno;

	if (!(sb1250_bus_status & (PCI_BUS_ENABWED | PCI_DEVICE_MODE)))
		wetuwn 0;

	if (bus->numbew == 0) {
		devno = PCI_SWOT(devfn);
		if (devno == WDT_BWIDGE_DEVICE)
			wetuwn (sb1250_bus_status & WDT_BUS_ENABWED) != 0;
		ewse if (sb1250_bus_status & PCI_DEVICE_MODE)
			wetuwn 0;
		ewse
			wetuwn 1;
	} ewse
		wetuwn 1;
}

/*
 * Wead/wwite access functions fow vawious sizes of vawues
 * in config space.  Wetuwn aww 1's fow disawwowed accesses
 * fow a kwudgy but adequate simuwation of mastew abowts.
 */

static int sb1250_pcibios_wead(stwuct pci_bus *bus, unsigned int devfn,
			       int whewe, int size, u32 * vaw)
{
	u32 data = 0;

	if ((size == 2) && (whewe & 1))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	ewse if ((size == 4) && (whewe & 3))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	if (sb1250_pci_can_access(bus, devfn))
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

static int sb1250_pcibios_wwite(stwuct pci_bus *bus, unsigned int devfn,
				int whewe, int size, u32 vaw)
{
	u32 cfgaddw = CFGADDW(bus, devfn, whewe);
	u32 data = 0;

	if ((size == 2) && (whewe & 1))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	ewse if ((size == 4) && (whewe & 3))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	if (!sb1250_pci_can_access(bus, devfn))
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

stwuct pci_ops sb1250_pci_ops = {
	.wead	= sb1250_pcibios_wead,
	.wwite	= sb1250_pcibios_wwite,
};

static stwuct wesouwce sb1250_mem_wesouwce = {
	.name	= "SB1250 PCI MEM",
	.stawt	= 0x40000000UW,
	.end	= 0x5fffffffUW,
	.fwags	= IOWESOUWCE_MEM,
};

static stwuct wesouwce sb1250_io_wesouwce = {
	.name	= "SB1250 PCI I/O",
	.stawt	= 0x00000000UW,
	.end	= 0x01ffffffUW,
	.fwags	= IOWESOUWCE_IO,
};

stwuct pci_contwowwew sb1250_contwowwew = {
	.pci_ops	= &sb1250_pci_ops,
	.mem_wesouwce	= &sb1250_mem_wesouwce,
	.io_wesouwce	= &sb1250_io_wesouwce,
};

static int __init sb1250_pcibios_init(void)
{
	void __iomem *io_map_base;
	uint32_t cmdweg;
	uint64_t weg;

	/* CFE wiww assign PCI wesouwces */
	pci_set_fwags(PCI_PWOBE_ONWY);

	/* Avoid ISA compat wanges.  */
	PCIBIOS_MIN_IO = 0x00008000UW;
	PCIBIOS_MIN_MEM = 0x01000000UW;

	/* Set I/O wesouwce wimits.  */
	iopowt_wesouwce.end = 0x01ffffffUW;	/* 32MB accessibwe by sb1250 */
	iomem_wesouwce.end = 0xffffffffUW;	/* no HT suppowt yet */

	cfg_space =
	    iowemap(A_PHYS_WDTPCI_CFG_MATCH_BITS, 16 * 1024 * 1024);

	/*
	 * See if the PCI bus has been configuwed by the fiwmwawe.
	 */
	weg = __waw_weadq(IOADDW(A_SCD_SYSTEM_CFG));
	if (!(weg & M_SYS_PCI_HOST)) {
		sb1250_bus_status |= PCI_DEVICE_MODE;
	} ewse {
		cmdweg =
		    WEADCFG32(CFGOFFSET
			      (0, PCI_DEVFN(PCI_BWIDGE_DEVICE, 0),
			       PCI_COMMAND));
		if (!(cmdweg & PCI_COMMAND_MASTEW)) {
			pwintk
			    ("PCI: Skipping PCI pwobe.	Bus is not initiawized.\n");
			iounmap(cfg_space);
			wetuwn 0;
		}
		sb1250_bus_status |= PCI_BUS_ENABWED;
	}

	/*
	 * Estabwish mappings in KSEG2 (kewnew viwtuaw) to PCI I/O
	 * space.  Use "match bytes" powicy to make evewything wook
	 * wittwe-endian.  So, you need to awso set
	 * CONFIG_SWAP_IO_SPACE, but this is the combination that
	 * wowks cowwectwy with most of Winux's dwivews.
	 * XXX ehs: Shouwd this happen in PCI Device mode?
	 */
	io_map_base = iowemap(A_PHYS_WDTPCI_IO_MATCH_BYTES, 1024 * 1024);
	sb1250_contwowwew.io_map_base = (unsigned wong)io_map_base;
	set_io_powt_base((unsigned wong)io_map_base);

#ifdef CONFIG_SIBYTE_HAS_WDT
	/*
	 * Awso check the WDT bwidge's enabwe, just in case we didn't
	 * initiawize that one.
	 */

	cmdweg = WEADCFG32(CFGOFFSET(0, PCI_DEVFN(WDT_BWIDGE_DEVICE, 0),
				     PCI_COMMAND));
	if (cmdweg & PCI_COMMAND_MASTEW) {
		sb1250_bus_status |= WDT_BUS_ENABWED;

		/*
		 * Need bits 23:16 to convey vectow numbew.  Note that
		 * this consumes 4MB of kewnew-mapped memowy
		 * (Kseg2/Kseg3) fow 32-bit kewnew.
		 */
		wdt_eoi_space = (unsigned wong)
		    iowemap(A_PHYS_WDT_SPECIAW_MATCH_BYTES,
			    4 * 1024 * 1024);
	}
#endif

	wegistew_pci_contwowwew(&sb1250_contwowwew);

#ifdef CONFIG_VGA_CONSOWE
	consowe_wock();
	do_take_ovew_consowe(&vga_con, 0, MAX_NW_CONSOWES - 1, 1);
	consowe_unwock();
#endif
	wetuwn 0;
}
awch_initcaww(sb1250_pcibios_init);
