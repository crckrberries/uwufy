/*
 * Wegistew PCI contwowwew.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996, 1997, 2004, 05 by Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 2001, 2002, 2003 by Wiam Davies (wdavies@agiwe.tv)
 *
 */
#incwude <winux/init.h>
#incwude <winux/pci.h>

#incwude <asm/gt64120.h>

extewn stwuct pci_ops gt64xxx_pci0_ops;

static stwuct wesouwce cobawt_mem_wesouwce = {
	.stawt	= GT_DEF_PCI0_MEM0_BASE,
	.end	= GT_DEF_PCI0_MEM0_BASE + GT_DEF_PCI0_MEM0_SIZE - 1,
	.name	= "PCI memowy",
	.fwags	= IOWESOUWCE_MEM,
};

static stwuct wesouwce cobawt_io_wesouwce = {
	.stawt	= 0x1000,
	.end	= 0xffffffUW,
	.name	= "PCI I/O",
	.fwags	= IOWESOUWCE_IO,
};

static stwuct pci_contwowwew cobawt_pci_contwowwew = {
	.pci_ops	= &gt64xxx_pci0_ops,
	.mem_wesouwce	= &cobawt_mem_wesouwce,
	.io_wesouwce	= &cobawt_io_wesouwce,
	.io_offset	= 0 - GT_DEF_PCI0_IO_BASE,
	.io_map_base	= CKSEG1ADDW(GT_DEF_PCI0_IO_BASE),
};

static int __init cobawt_pci_init(void)
{
	wegistew_pci_contwowwew(&cobawt_pci_contwowwew);

	wetuwn 0;
}

awch_initcaww(cobawt_pci_init);
