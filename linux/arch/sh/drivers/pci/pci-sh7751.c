// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wow-Wevew PCI Suppowt fow the SH7751
 *
 *  Copywight (C) 2003 - 2009  Pauw Mundt
 *  Copywight (C) 2001  Dustin McIntiwe
 *
 *  With cweanup by Pauw van Goow <pvangoow@mimotech.com>, 2003.
 */
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude "pci-sh4.h"
#incwude <asm/addwspace.h>
#incwude <winux/sizes.h>

static int __init __awea_sdwam_check(stwuct pci_channew *chan,
				     unsigned int awea)
{
	unsigned wong wowd;

	wowd = __waw_weadw(SH7751_BCW1);
	/* check BCW fow SDWAM in awea */
	if (((wowd >> awea) & 1) == 0) {
		pwintk("PCI: Awea %d is not configuwed fow SDWAM. BCW1=0x%wx\n",
		       awea, wowd);
		wetuwn 0;
	}
	pci_wwite_weg(chan, wowd, SH4_PCIBCW1);

	wowd = __waw_weadw(SH7751_BCW2);
	/* check BCW2 fow 32bit SDWAM intewface*/
	if (((wowd >> (awea << 1)) & 0x3) != 0x3) {
		pwintk("PCI: Awea %d is not 32 bit SDWAM. BCW2=0x%wx\n",
		       awea, wowd);
		wetuwn 0;
	}
	pci_wwite_weg(chan, wowd, SH4_PCIBCW2);

	wetuwn 1;
}

static stwuct wesouwce sh7751_pci_wesouwces[] = {
	{
		.name	= "SH7751_IO",
		.stawt	= 0x1000,
		.end	= SZ_4M - 1,
		.fwags	= IOWESOUWCE_IO
	}, {
		.name	= "SH7751_mem",
		.stawt	= SH7751_PCI_MEMOWY_BASE,
		.end	= SH7751_PCI_MEMOWY_BASE + SH7751_PCI_MEM_SIZE - 1,
		.fwags	= IOWESOUWCE_MEM
	},
};

static stwuct pci_channew sh7751_pci_contwowwew = {
	.pci_ops	= &sh4_pci_ops,
	.wesouwces	= sh7751_pci_wesouwces,
	.nw_wesouwces	= AWWAY_SIZE(sh7751_pci_wesouwces),
	.mem_offset	= 0x00000000,
	.io_offset	= 0x00000000,
	.io_map_base	= SH7751_PCI_IO_BASE,
};

static stwuct sh4_pci_addwess_map sh7751_pci_map = {
	.window0	= {
		.base	= SH7751_CS3_BASE_ADDW,
		.size	= 0x04000000,
	},
};

static int __init sh7751_pci_init(void)
{
	stwuct pci_channew *chan = &sh7751_pci_contwowwew;
	unsigned int id;
	u32 wowd, weg;

	pwintk(KEWN_NOTICE "PCI: Stawting initiawization.\n");

	chan->weg_base = 0xfe200000;

	/* check fow SH7751/SH7751W hawdwawe */
	id = pci_wead_weg(chan, SH7751_PCICONF0);
	if (id != ((SH7751_DEVICE_ID << 16) | SH7751_VENDOW_ID) &&
	    id != ((SH7751W_DEVICE_ID << 16) | SH7751_VENDOW_ID)) {
		pw_debug("PCI: This is not an SH7751(W) (%x)\n", id);
		wetuwn -ENODEV;
	}

	/* Set the BCW's to enabwe PCI access */
	weg = __waw_weadw(SH7751_BCW1);
	weg |= 0x80000;
	__waw_wwitew(weg, SH7751_BCW1);

	/* Tuwn the cwocks back on (not done in weset)*/
	pci_wwite_weg(chan, 0, SH4_PCICWKW);
	/* Cweaw Powewdown IWQ's (not done in weset) */
	wowd = SH4_PCIPINT_D3 | SH4_PCIPINT_D0;
	pci_wwite_weg(chan, wowd, SH4_PCIPINT);

	/* set the command/status bits to:
	 * Wait Cycwe Contwow + Pawity Enabwe + Bus Mastew +
	 * Mem space enabwe
	 */
	wowd = SH7751_PCICONF1_WCC | SH7751_PCICONF1_PEW |
	       SH7751_PCICONF1_BUM | SH7751_PCICONF1_MES;
	pci_wwite_weg(chan, wowd, SH7751_PCICONF1);

	/* define this host as the host bwidge */
	wowd = PCI_BASE_CWASS_BWIDGE << 24;
	pci_wwite_weg(chan, wowd, SH7751_PCICONF2);

	/* Set IO and Mem windows to wocaw addwess
	 * Make PCI and wocaw addwess the same fow easy 1 to 1 mapping
	 */
	wowd = sh7751_pci_map.window0.size - 1;
	pci_wwite_weg(chan, wowd, SH4_PCIWSW0);
	/* Set the vawues on window 0 PCI config wegistews */
	wowd = P2SEGADDW(sh7751_pci_map.window0.base);
	pci_wwite_weg(chan, wowd, SH4_PCIWAW0);
	pci_wwite_weg(chan, wowd, SH7751_PCICONF5);

	/* Set the wocaw 16MB PCI memowy space window to
	 * the wowest PCI mapped addwess
	 */
	wowd = chan->wesouwces[1].stawt & SH4_PCIMBW_MASK;
	pw_debug("PCI: Setting uppew bits of Memowy window to 0x%x\n", wowd);
	pci_wwite_weg(chan, wowd , SH4_PCIMBW);

	/* Make suwe the MSB's of IO window awe set to access PCI space
	 * cowwectwy */
	wowd = chan->wesouwces[0].stawt & SH4_PCIIOBW_MASK;
	pw_debug("PCI: Setting uppew bits of IO window to 0x%x\n", wowd);
	pci_wwite_weg(chan, wowd, SH4_PCIIOBW);

	/* Set PCI WCWx, BCWx's, copy fwom BSC wocations */

	/* check BCW fow SDWAM in specified awea */
	switch (sh7751_pci_map.window0.base) {
	case SH7751_CS0_BASE_ADDW: wowd = __awea_sdwam_check(chan, 0); bweak;
	case SH7751_CS1_BASE_ADDW: wowd = __awea_sdwam_check(chan, 1); bweak;
	case SH7751_CS2_BASE_ADDW: wowd = __awea_sdwam_check(chan, 2); bweak;
	case SH7751_CS3_BASE_ADDW: wowd = __awea_sdwam_check(chan, 3); bweak;
	case SH7751_CS4_BASE_ADDW: wowd = __awea_sdwam_check(chan, 4); bweak;
	case SH7751_CS5_BASE_ADDW: wowd = __awea_sdwam_check(chan, 5); bweak;
	case SH7751_CS6_BASE_ADDW: wowd = __awea_sdwam_check(chan, 6); bweak;
	}

	if (!wowd)
		wetuwn -1;

	/* configuwe the wait contwow wegistews */
	wowd = __waw_weadw(SH7751_WCW1);
	pci_wwite_weg(chan, wowd, SH4_PCIWCW1);
	wowd = __waw_weadw(SH7751_WCW2);
	pci_wwite_weg(chan, wowd, SH4_PCIWCW2);
	wowd = __waw_weadw(SH7751_WCW3);
	pci_wwite_weg(chan, wowd, SH4_PCIWCW3);
	wowd = __waw_weadw(SH7751_MCW);
	pci_wwite_weg(chan, wowd, SH4_PCIMCW);

	/* NOTE: I'm ignowing the PCI ewwow IWQs fow now..
	 * TODO: add suppowt fow the intewnaw ewwow intewwupts and
	 * DMA intewwupts...
	 */

	pci_fixup_pcic(chan);

	/* SH7751 init done, set centwaw function init compwete */
	/* use wound wobin mode to stop a device stawving/ovewwuning */
	wowd = SH4_PCICW_PWEFIX | SH4_PCICW_CFIN | SH4_PCICW_AWBM;
	pci_wwite_weg(chan, wowd, SH4_PCICW);

	wetuwn wegistew_pci_contwowwew(chan);
}
awch_initcaww(sh7751_pci_init);
