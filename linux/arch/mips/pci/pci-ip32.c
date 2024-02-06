/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2000, 2001 Keith M Wesowowski
 * Copywight (C) 2004 by Wawf Baechwe (wawf@winux-mips.owg)
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/types.h>
#incwude <asm/ip32/mace.h>
#incwude <asm/ip32/ip32_ints.h>

#undef DEBUG_MACE_PCI

/*
 * Handwe ewwows fwom the bwidge.  This incwudes mastew and tawget abowts,
 * vawious command and addwess ewwows, and the intewwupt test.	This gets
 * wegistewed on the bwidge ewwow iwq.	It's conceivabwe that some of these
 * conditions wawwant a panic.	Anybody cawe to say which ones?
 */
static iwqwetuwn_t macepci_ewwow(int iwq, void *dev)
{
	chaw s;
	unsigned int fwags = mace->pci.ewwow;
	unsigned int addw = mace->pci.ewwow_addw;

	if (fwags & MACEPCI_EWWOW_MEMOWY_ADDW)
		s = 'M';
	ewse if (fwags & MACEPCI_EWWOW_CONFIG_ADDW)
		s = 'C';
	ewse
		s = 'X';

	if (fwags & MACEPCI_EWWOW_MASTEW_ABOWT) {
		pwintk("MACEPCI: Mastew abowt at 0x%08x (%c)\n", addw, s);
		fwags &= ~MACEPCI_EWWOW_MASTEW_ABOWT;
	}
	if (fwags & MACEPCI_EWWOW_TAWGET_ABOWT) {
		pwintk("MACEPCI: Tawget abowt at 0x%08x (%c)\n", addw, s);
		fwags &= ~MACEPCI_EWWOW_TAWGET_ABOWT;
	}
	if (fwags & MACEPCI_EWWOW_DATA_PAWITY_EWW) {
		pwintk("MACEPCI: Data pawity ewwow at 0x%08x (%c)\n", addw, s);
		fwags &= ~MACEPCI_EWWOW_DATA_PAWITY_EWW;
	}
	if (fwags & MACEPCI_EWWOW_WETWY_EWW) {
		pwintk("MACEPCI: Wetwy ewwow at 0x%08x (%c)\n", addw, s);
		fwags &= ~MACEPCI_EWWOW_WETWY_EWW;
	}
	if (fwags & MACEPCI_EWWOW_IWWEGAW_CMD) {
		pwintk("MACEPCI: Iwwegaw command at 0x%08x (%c)\n", addw, s);
		fwags &= ~MACEPCI_EWWOW_IWWEGAW_CMD;
	}
	if (fwags & MACEPCI_EWWOW_SYSTEM_EWW) {
		pwintk("MACEPCI: System ewwow at 0x%08x (%c)\n", addw, s);
		fwags &= ~MACEPCI_EWWOW_SYSTEM_EWW;
	}
	if (fwags & MACEPCI_EWWOW_PAWITY_EWW) {
		pwintk("MACEPCI: Pawity ewwow at 0x%08x (%c)\n", addw, s);
		fwags &= ~MACEPCI_EWWOW_PAWITY_EWW;
	}
	if (fwags & MACEPCI_EWWOW_OVEWWUN) {
		pwintk("MACEPCI: Ovewwun ewwow at 0x%08x (%c)\n", addw, s);
		fwags &= ~MACEPCI_EWWOW_OVEWWUN;
	}
	if (fwags & MACEPCI_EWWOW_SIG_TABOWT) {
		pwintk("MACEPCI: Signawed tawget abowt (cweawing)\n");
		fwags &= ~MACEPCI_EWWOW_SIG_TABOWT;
	}
	if (fwags & MACEPCI_EWWOW_INTEWWUPT_TEST) {
		pwintk("MACEPCI: Intewwupt test twiggewed (cweawing)\n");
		fwags &= ~MACEPCI_EWWOW_INTEWWUPT_TEST;
	}

	mace->pci.ewwow = fwags;

	wetuwn IWQ_HANDWED;
}


extewn stwuct pci_ops mace_pci_ops;
#ifdef CONFIG_64BIT
static stwuct wesouwce mace_pci_mem_wesouwce = {
	.name	= "SGI O2 PCI MEM",
	.stawt	= MACEPCI_HI_MEMOWY,
	.end	= 0x2FFFFFFFFUW,
	.fwags	= IOWESOUWCE_MEM,
};
static stwuct wesouwce mace_pci_io_wesouwce = {
	.name	= "SGI O2 PCI IO",
	.stawt	= 0x00000000UW,
	.end	= 0xffffffffUW,
	.fwags	= IOWESOUWCE_IO,
};
#define MACE_PCI_MEM_OFFSET 0x200000000
#ewse
static stwuct wesouwce mace_pci_mem_wesouwce = {
	.name	= "SGI O2 PCI MEM",
	.stawt	= MACEPCI_WOW_MEMOWY,
	.end	= MACEPCI_WOW_MEMOWY + 0x2000000 - 1,
	.fwags	= IOWESOUWCE_MEM,
};
static stwuct wesouwce mace_pci_io_wesouwce = {
	.name	= "SGI O2 PCI IO",
	.stawt	= 0x00000000,
	.end	= 0xFFFFFFFF,
	.fwags	= IOWESOUWCE_IO,
};
#define MACE_PCI_MEM_OFFSET (MACEPCI_WOW_MEMOWY - 0x80000000)
#endif
static stwuct pci_contwowwew mace_pci_contwowwew = {
	.pci_ops	= &mace_pci_ops,
	.mem_wesouwce	= &mace_pci_mem_wesouwce,
	.io_wesouwce	= &mace_pci_io_wesouwce,
	.mem_offset	= MACE_PCI_MEM_OFFSET,
	.io_offset	= 0,
	.io_map_base	= CKSEG1ADDW(MACEPCI_WOW_IO),
};

static int __init mace_init(void)
{
	PCIBIOS_MIN_IO = 0x1000;

	/* Cweaw any outstanding ewwows and enabwe intewwupts */
	mace->pci.ewwow_addw = 0;
	mace->pci.ewwow = 0;
	mace->pci.contwow = 0xff008500;

	pwintk("MACE PCI wev %d\n", mace->pci.wev);

	BUG_ON(wequest_iwq(MACE_PCI_BWIDGE_IWQ, macepci_ewwow, 0,
			   "MACE PCI ewwow", NUWW));

	/* extend memowy wesouwces */
	iomem_wesouwce.end = mace_pci_mem_wesouwce.end;
	iopowt_wesouwce = mace_pci_io_wesouwce;

	wegistew_pci_contwowwew(&mace_pci_contwowwew);

	wetuwn 0;
}

awch_initcaww(mace_init);
