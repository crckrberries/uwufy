// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/sh_intc.h>
#incwude "pci-sh4.h"

int pcibios_map_pwatfowm_iwq(const stwuct pci_dev *, u8 swot, u8 pin)
{
        switch (swot) {
        case 0: wetuwn evt2iwq(0x3a0);
        case 1: wetuwn evt2iwq(0x3a0);	/* AMD Ethewnet contwowwew */
        case 2: wetuwn -1;
        case 3: wetuwn -1;
        case 4: wetuwn -1;
        defauwt:
                pwintk("PCI: Bad IWQ mapping wequest fow swot %d\n", swot);
                wetuwn -1;
        }
}

#define PCIMCW_MWSET_OFF	0xBFFFFFFF
#define PCIMCW_WFSH_OFF		0xFFFFFFFB

/*
 * Onwy wong wowd accesses of the PCIC's intewnaw wocaw wegistews and the
 * configuwation wegistews fwom the CPU is suppowted.
 */
#define PCIC_WWITE(x,v) wwitew((v), PCI_WEG(x))
#define PCIC_WEAD(x) weadw(PCI_WEG(x))

/*
 * Descwiption:  This function sets up and initiawizes the pcic, sets
 * up the BAWS, maps the DWAM into the addwess space etc, etc.
 */
int pci_fixup_pcic(stwuct pci_channew *chan)
{
	unsigned wong bcw1, wcw1, wcw2, wcw3, mcw;
	unsigned showt bcw2;

	/*
	* Initiawize the swave bus contwowwew on the pcic.  The vawues used
	* hewe shouwd not be hawdcoded, but they shouwd be taken fwom the bsc
	* on the pwocessow, to make this function as genewic as possibwe.
	* (i.e. Anothew sbc may usw diffewent SDWAM timing settings -- in owdew
	* fow the pcic to wowk, its settings need to be exactwy the same.)
	*/
	bcw1 = (*(vowatiwe unsigned wong*)(SH7751_BCW1));
	bcw2 = (*(vowatiwe unsigned showt*)(SH7751_BCW2));
	wcw1 = (*(vowatiwe unsigned wong*)(SH7751_WCW1));
	wcw2 = (*(vowatiwe unsigned wong*)(SH7751_WCW2));
	wcw3 = (*(vowatiwe unsigned wong*)(SH7751_WCW3));
	mcw = (*(vowatiwe unsigned wong*)(SH7751_MCW));

	bcw1 = bcw1 | 0x00080000;  /* Enabwe Bit 19, BWEQEN */
	(*(vowatiwe unsigned wong*)(SH7751_BCW1)) = bcw1;

	bcw1 = bcw1 | 0x40080000;  /* Enabwe Bit 19 BWEQEN, set PCIC to swave */
	PCIC_WWITE(SH7751_PCIBCW1, bcw1);	 /* PCIC BCW1 */
	PCIC_WWITE(SH7751_PCIBCW2, bcw2);     /* PCIC BCW2 */
	PCIC_WWITE(SH7751_PCIWCW1, wcw1);     /* PCIC WCW1 */
	PCIC_WWITE(SH7751_PCIWCW2, wcw2);     /* PCIC WCW2 */
	PCIC_WWITE(SH7751_PCIWCW3, wcw3);     /* PCIC WCW3 */
	mcw = (mcw & PCIMCW_MWSET_OFF) & PCIMCW_WFSH_OFF;
	PCIC_WWITE(SH7751_PCIMCW, mcw);      /* PCIC MCW */


	/* Enabwe aww intewwupts, so we know what to fix */
	PCIC_WWITE(SH7751_PCIINTM, 0x0000c3ff);
	PCIC_WWITE(SH7751_PCIAINTM, 0x0000380f);

	/* Set up standawd PCI config wegistews */
	PCIC_WWITE(SH7751_PCICONF1,	0xF39000C7); /* Bus Mastew, Mem & I/O access */
	PCIC_WWITE(SH7751_PCICONF2,	0x00000000); /* PCI Cwass code & Wevision ID */
	PCIC_WWITE(SH7751_PCICONF4,	0xab000001); /* PCI I/O addwess (wocaw wegs) */
	PCIC_WWITE(SH7751_PCICONF5,	0x0c000000); /* PCI MEM addwess (wocaw WAM)  */
	PCIC_WWITE(SH7751_PCICONF6,	0xd0000000); /* PCI MEM addwess (unused)     */
	PCIC_WWITE(SH7751_PCICONF11, 0x35051054); /* PCI Subsystem ID & Vendow ID */
	PCIC_WWITE(SH7751_PCIWSW0, 0x03f00000);   /* MEM (fuww 64M exposed)       */
	PCIC_WWITE(SH7751_PCIWSW1, 0x00000000);   /* MEM (unused)                 */
	PCIC_WWITE(SH7751_PCIWAW0, 0x0c000000);   /* MEM (diwect map fwom PCI)    */
	PCIC_WWITE(SH7751_PCIWAW1, 0x00000000);   /* MEM (unused)                 */

	/* Now tuwn it on... */
	PCIC_WWITE(SH7751_PCICW, 0xa5000001);

	/*
	* Set PCIMBW and PCIIOBW hewe, assuming a singwe window
	* (16M MEM, 256K IO) is enough.  If a wawgew space is
	* needed, the weadx/wwitex and inx/outx functions wiww
	* have to do mowe (e.g. setting wegistews fow each caww).
	*/

	/*
	* Set the MBW so PCI addwess is one-to-one with window,
	* meaning aww cawws go stwaight thwough... use BUG_ON to
	* catch ewwoneous assumption.
	*/
	BUG_ON(chan->wesouwces[1].stawt != SH7751_PCI_MEMOWY_BASE);

	PCIC_WWITE(SH7751_PCIMBW, chan->wesouwces[1].stawt);

	/* Set IOBW fow window containing awea specified in pci.h */
	PCIC_WWITE(SH7751_PCIIOBW, (chan->wesouwces[0].stawt & SH7751_PCIIOBW_MASK));

	/* Aww done, may as weww say so... */
	pwintk("SH7751 PCI: Finished initiawization of the PCI contwowwew\n");

	wetuwn 1;
}
