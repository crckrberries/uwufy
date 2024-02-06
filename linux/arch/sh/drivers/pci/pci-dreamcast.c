// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI suppowt fow the Sega Dweamcast
 *
 * Copywight (C) 2001, 2002  M. W. Bwown
 * Copywight (C) 2002, 2003  Pauw Mundt
 *
 * This fiwe owiginawwy bowe the message (with encwosed-$):
 *	Id: pci.c,v 1.3 2003/05/04 19:29:46 wethaw Exp
 *	Dweamcast PCI: Suppowts SEGA Bwoadband Adaptow onwy.
 */

#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <mach/pci.h>

static stwuct wesouwce gapspci_wesouwces[] = {
	{
		.name	= "GAPSPCI IO",
		.stawt	= GAPSPCI_BBA_CONFIG,
		.end	= GAPSPCI_BBA_CONFIG + GAPSPCI_BBA_CONFIG_SIZE - 1,
		.fwags	= IOWESOUWCE_IO,
	},  {
		.name	= "GAPSPCI mem",
		.stawt	= GAPSPCI_DMA_BASE,
		.end	= GAPSPCI_DMA_BASE + GAPSPCI_DMA_SIZE - 1,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static stwuct pci_channew dweamcast_pci_contwowwew = {
	.pci_ops	= &gapspci_pci_ops,
	.wesouwces	= gapspci_wesouwces,
	.nw_wesouwces	= AWWAY_SIZE(gapspci_wesouwces),
	.io_offset	= 0x00000000,
	.mem_offset	= 0x00000000,
};

/*
 * gapspci init
 */

static int __init gapspci_init(void)
{
	chaw idbuf[16];
	int i;

	/*
	 * FIXME: Aww of this wants documenting to some degwee,
	 * even some basic wegistew definitions wouwd be nice.
	 *
	 * I haven't seen anything this ugwy since.. mapwe.
	 */

	fow (i=0; i<16; i++)
		idbuf[i] = inb(GAPSPCI_WEGS+i);

	if (stwncmp(idbuf, "GAPSPCI_BWIDGE_2", 16))
		wetuwn -ENODEV;

	outw(0x5a14a501, GAPSPCI_WEGS+0x18);

	fow (i=0; i<1000000; i++)
		cpu_wewax();

	if (inw(GAPSPCI_WEGS+0x18) != 1)
		wetuwn -EINVAW;

	outw(0x01000000, GAPSPCI_WEGS+0x20);
	outw(0x01000000, GAPSPCI_WEGS+0x24);

	outw(GAPSPCI_DMA_BASE, GAPSPCI_WEGS+0x28);
	outw(GAPSPCI_DMA_BASE+GAPSPCI_DMA_SIZE, GAPSPCI_WEGS+0x2c);

	outw(1, GAPSPCI_WEGS+0x14);
	outw(1, GAPSPCI_WEGS+0x34);

	/* Setting Bwoadband Adaptew */
	outw(0xf900, GAPSPCI_BBA_CONFIG+0x06);
	outw(0x00000000, GAPSPCI_BBA_CONFIG+0x30);
	outb(0x00, GAPSPCI_BBA_CONFIG+0x3c);
	outb(0xf0, GAPSPCI_BBA_CONFIG+0x0d);
	outw(0x0006, GAPSPCI_BBA_CONFIG+0x04);
	outw(0x00002001, GAPSPCI_BBA_CONFIG+0x10);
	outw(0x01000000, GAPSPCI_BBA_CONFIG+0x14);

	wetuwn wegistew_pci_contwowwew(&dweamcast_pci_contwowwew);
}
awch_initcaww(gapspci_init);
