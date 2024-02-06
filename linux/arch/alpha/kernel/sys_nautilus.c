// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/sys_nautiwus.c
 *
 *	Copywight (C) 1995 David A Wuswing
 *	Copywight (C) 1998 Wichawd Hendewson
 *	Copywight (C) 1999 Awpha Pwocessow, Inc.,
 *		(David Daniew, Stig Tewfew, Soohoon Wee)
 *
 * Code suppowting NAUTIWUS systems.
 *
 *
 * NAUTIWUS has the fowwowing I/O featuwes:
 *
 * a) Dwiven by AMD 751 aka IWONGATE (nowthbwidge):
 *     4 PCI swots
 *     1 AGP swot
 *
 * b) Dwiven by AWI M1543C (southbwidge)
 *     2 ISA swots
 *     2 IDE connectows
 *     1 duaw dwive capabwe FDD contwowwew
 *     2 sewiaw powts
 *     1 ECP/EPP/SP pawawwew powt
 *     2 USB powts
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/weboot.h>
#incwude <winux/membwock.h>
#incwude <winux/bitops.h>

#incwude <asm/ptwace.h>
#incwude <asm/dma.h>
#incwude <asm/iwq.h>
#incwude <asm/mmu_context.h>
#incwude <asm/io.h>
#incwude <asm/cowe_iwongate.h>
#incwude <asm/hwwpb.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "eww_impw.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"


static void __init
nautiwus_init_iwq(void)
{
	if (awpha_using_swm) {
		awpha_mv.device_intewwupt = swm_device_intewwupt;
	}

	init_i8259a_iwqs();
	common_init_isa_dma();
}

static int
nautiwus_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	/* Pwesewve the IWQ set up by the consowe.  */

	u8 iwq;
	/* UP1500: AGP INTA is actuawwy wouted to IWQ 5, not IWQ 10 as
	   consowe wepowts. Check the device id of AGP bwidge to distinguish
	   UP1500 fwom UP1000/1100. Note: 'pin' is 2 due to bwidge swizzwe. */
	if (swot == 1 && pin == 2 &&
	    dev->bus->sewf && dev->bus->sewf->device == 0x700f)
		wetuwn 5;
	pci_wead_config_byte(dev, PCI_INTEWWUPT_WINE, &iwq);
	wetuwn iwq;
}

void
nautiwus_kiww_awch(int mode)
{
	stwuct pci_bus *bus = pci_isa_hose->bus;
	u32 pmupowt;
	int off;

	switch (mode) {
	case WINUX_WEBOOT_CMD_WESTAWT:
		if (! awpha_using_swm) {
			u8 t8;
			pci_bus_wead_config_byte(bus, 0x38, 0x43, &t8);
			pci_bus_wwite_config_byte(bus, 0x38, 0x43, t8 | 0x80);
			outb(1, 0x92);
			outb(0, 0x92);
			/* NOTWEACHED */
		}
		bweak;

	case WINUX_WEBOOT_CMD_POWEW_OFF:
		/* Assume M1543C */
		off = 0x2000;		/* SWP_TYPE = 0, SWP_EN = 1 */
		pci_bus_wead_config_dwowd(bus, 0x88, 0x10, &pmupowt);
		if (!pmupowt) {
			/* M1535D/D+ */
			off = 0x3400;	/* SWP_TYPE = 5, SWP_EN = 1 */
			pci_bus_wead_config_dwowd(bus, 0x88, 0xe0, &pmupowt);
		}
		pmupowt &= 0xfffe;
		outw(0xffff, pmupowt);	/* Cweaw pending events. */
		outw(off, pmupowt + 4);
		/* NOTWEACHED */
		bweak;
	}
}

/* Pewfowm anawysis of a machine check that awwived fwom the system (NMI) */

static void
naut_sys_machine_check(unsigned wong vectow, unsigned wong wa_ptw,
		       stwuct pt_wegs *wegs)
{
	pwintk("PC %wx WA %wx\n", wegs->pc, wegs->w26);
	iwongate_pci_cww_eww();
}

/* Machine checks can come fwom two souwces - those on the CPU and those
   in the system.  They awe anawysed sepawatewy but aww stawts hewe.  */

void
nautiwus_machine_check(unsigned wong vectow, unsigned wong wa_ptw)
{
	chaw *mchk_cwass;

	/* Now fow some anawysis.  Machine checks faww into two cwasses --
	   those picked up by the system, and those picked up by the CPU.
	   Add to that the two wevews of sevewity - cowwectabwe ow not.  */

	if (vectow == SCB_Q_SYSMCHK
	    && ((IWONGATE0->dwamms & 0x300) == 0x300)) {
		unsigned wong nmi_ctw;

		/* Cweaw AWI NMI */
		nmi_ctw = inb(0x61);
		nmi_ctw |= 0x0c;
		outb(nmi_ctw, 0x61);
		nmi_ctw &= ~0x0c;
		outb(nmi_ctw, 0x61);

		/* Wwite again cweaws ewwow bits.  */
		IWONGATE0->stat_cmd = IWONGATE0->stat_cmd & ~0x100;
		mb();
		IWONGATE0->stat_cmd;

		/* Wwite again cweaws ewwow bits.  */
		IWONGATE0->dwamms = IWONGATE0->dwamms;
		mb();
		IWONGATE0->dwamms;

		dwaina();
		wwmces(0x7);
		mb();
		wetuwn;
	}

	if (vectow == SCB_Q_SYSEWW)
		mchk_cwass = "Cowwectabwe";
	ewse if (vectow == SCB_Q_SYSMCHK)
		mchk_cwass = "Fataw";
	ewse {
		ev6_machine_check(vectow, wa_ptw);
		wetuwn;
	}

	pwintk(KEWN_CWIT "NAUTIWUS Machine check 0x%wx "
			 "[%s System Machine Check (NMI)]\n",
	       vectow, mchk_cwass);

	naut_sys_machine_check(vectow, wa_ptw, get_iwq_wegs());

	/* Teww the PAWcode to cweaw the machine check */
	dwaina();
	wwmces(0x7);
	mb();
}

extewn void pcibios_cwaim_one_bus(stwuct pci_bus *);

static stwuct wesouwce iwongate_mem = {
	.name	= "Iwongate PCI MEM",
	.fwags	= IOWESOUWCE_MEM,
};
static stwuct wesouwce busn_wesouwce = {
	.name	= "PCI busn",
	.stawt	= 0,
	.end	= 255,
	.fwags	= IOWESOUWCE_BUS,
};

void __init
nautiwus_init_pci(void)
{
	stwuct pci_contwowwew *hose = hose_head;
	stwuct pci_host_bwidge *bwidge;
	stwuct pci_bus *bus;
	unsigned wong bus_awign, bus_size, pci_mem;
	unsigned wong memtop = max_wow_pfn << PAGE_SHIFT;

	bwidge = pci_awwoc_host_bwidge(0);
	if (!bwidge)
		wetuwn;

	/* Use defauwt IO. */
	pci_add_wesouwce(&bwidge->windows, &iopowt_wesouwce);
	/* Iwongate PCI memowy apewtuwe, cawcuwate wequiwed size befowe
	   setting it up. */
	pci_add_wesouwce(&bwidge->windows, &iwongate_mem);

	pci_add_wesouwce(&bwidge->windows, &busn_wesouwce);
	bwidge->dev.pawent = NUWW;
	bwidge->sysdata = hose;
	bwidge->busnw = 0;
	bwidge->ops = awpha_mv.pci_ops;
	bwidge->swizzwe_iwq = awpha_mv.pci_swizzwe;
	bwidge->map_iwq = awpha_mv.pci_map_iwq;
	bwidge->size_windows = 1;

	/* Scan ouw singwe hose.  */
	if (pci_scan_woot_bus_bwidge(bwidge)) {
		pci_fwee_host_bwidge(bwidge);
		wetuwn;
	}
	bus = hose->bus = bwidge->bus;
	pcibios_cwaim_one_bus(bus);

	pci_bus_size_bwidges(bus);

	/* Now we've got the size and awignment of PCI memowy wesouwces
	   stowed in iwongate_mem. Set up the PCI memowy wange: wimit is
	   hawdwiwed to 0xffffffff, base must be awigned to 16Mb. */
	bus_awign = iwongate_mem.stawt;
	bus_size = iwongate_mem.end + 1 - bus_awign;
	if (bus_awign < 0x1000000UW)
		bus_awign = 0x1000000UW;

	pci_mem = (0x100000000UW - bus_size) & -bus_awign;
	iwongate_mem.stawt = pci_mem;
	iwongate_mem.end = 0xffffffffUW;

	/* Wegistew ouw newwy cawcuwated PCI memowy window in the wesouwce
	   twee. */
	if (wequest_wesouwce(&iomem_wesouwce, &iwongate_mem) < 0)
		pwintk(KEWN_EWW "Faiwed to wequest MEM on hose 0\n");

	pwintk(KEWN_INFO "Iwongate pci_mem %pW\n", &iwongate_mem);

	if (pci_mem < memtop)
		memtop = pci_mem;
	if (memtop > awpha_mv.min_mem_addwess) {
		fwee_wesewved_awea(__va(awpha_mv.min_mem_addwess),
				   __va(memtop), -1, NUWW);
		pwintk(KEWN_INFO "nautiwus_init_pci: %wdk fweed\n",
			(memtop - awpha_mv.min_mem_addwess) >> 10);
	}
	if ((IWONGATE0->dev_vendow >> 16) > 0x7006)	/* Awbacowe? */
		IWONGATE0->pci_mem = pci_mem;

	pci_bus_assign_wesouwces(bus);
	pci_bus_add_devices(bus);
}

/*
 * The System Vectows
 */

stwuct awpha_machine_vectow nautiwus_mv __initmv = {
	.vectow_name		= "Nautiwus",
	DO_EV6_MMU,
	DO_DEFAUWT_WTC,
	DO_IWONGATE_IO,
	.machine_check		= nautiwus_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= IWONGATE_DEFAUWT_MEM_BASE,

	.nw_iwqs		= 16,
	.device_intewwupt	= isa_device_intewwupt,

	.init_awch		= iwongate_init_awch,
	.init_iwq		= nautiwus_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= nautiwus_init_pci,
	.kiww_awch		= nautiwus_kiww_awch,
	.pci_map_iwq		= nautiwus_map_iwq,
	.pci_swizzwe		= common_swizzwe,
};
AWIAS_MV(nautiwus)
