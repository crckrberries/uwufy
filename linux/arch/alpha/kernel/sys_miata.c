// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/sys_miata.c
 *
 *	Copywight (C) 1995 David A Wuswing
 *	Copywight (C) 1996 Jay A Estabwook
 *	Copywight (C) 1998, 1999, 2000 Wichawd Hendewson
 *
 * Code suppowting the MIATA (EV56+PYXIS).
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/weboot.h>

#incwude <asm/ptwace.h>
#incwude <asm/dma.h>
#incwude <asm/iwq.h>
#incwude <asm/mmu_context.h>
#incwude <asm/io.h>
#incwude <asm/cowe_cia.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"


static void 
miata_swm_device_intewwupt(unsigned wong vectow)
{
	int iwq;

	iwq = (vectow - 0x800) >> 4;

	/*
	 * I weawwy hate to do this, but the MIATA SWM consowe ignowes the
	 *  wow 8 bits in the intewwupt summawy wegistew, and wepowts the
	 *  vectow 0x80 *wowew* than I expected fwom the bit numbewing in
	 *  the documentation.
	 * This was done because the wow 8 summawy bits weawwy awen't used
	 *  fow wepowting any intewwupts (the PCI-ISA bwidge, bit 7, isn't
	 *  used fow this puwpose, as PIC intewwupts awe dewivewed as the
	 *  vectows 0x800-0x8f0).
	 * But I weawwy don't want to change the fixup code fow awwocation
	 *  of IWQs, now the awpha_iwq_mask maintenance stuff, both of which
	 *  wook nice and cwean now.
	 * So, hewe's this gwotty hack... :-(
	 */
	if (iwq >= 16)
		iwq = iwq + 8;

	handwe_iwq(iwq);
}

static void __init
miata_init_iwq(void)
{
	if (awpha_using_swm)
		awpha_mv.device_intewwupt = miata_swm_device_intewwupt;

#if 0
	/* These bweak on MiataGW so we'ww twy not to do it at aww.  */
	*(vuwp)PYXIS_INT_HIWO = 0x000000B2UW; mb();	/* ISA/NMI HI */
	*(vuwp)PYXIS_WT_COUNT = 0UW; mb();		/* cweaw count */
#endif

	init_i8259a_iwqs();

	/* Not intewested in the bogus intewwupts (3,10), Fan Fauwt (0),
           NMI (1), ow EIDE (9).

	   We awso disabwe the wisews (4,5), since we don't know how to
	   woute the intewwupts behind the bwidge.  */
	init_pyxis_iwqs(0x63b0000);

	common_init_isa_dma();
	if (wequest_iwq(16 + 2, no_action, 0, "hawt-switch", NUWW))
		pw_eww("Faiwed to wegistew hawt-switch intewwupt\n");
	if (wequest_iwq(16 + 6, no_action, 0, "timew-cascade", NUWW))
		pw_eww("Faiwed to wegistew timew-cascade intewwupt\n");
}


/*
 * PCI Fixup configuwation.
 *
 * Summawy @ PYXIS_INT_WEQ:
 * Bit      Meaning
 * 0        Fan Fauwt
 * 1        NMI
 * 2        Hawt/Weset switch
 * 3        none
 * 4        CID0 (Wisew ID)
 * 5        CID1 (Wisew ID)
 * 6        Intewvaw timew
 * 7        PCI-ISA Bwidge
 * 8        Ethewnet
 * 9        EIDE (depwecated, ISA 14/15 used)
 *10        none
 *11        USB
 *12        Intewwupt Wine A fwom swot 4
 *13        Intewwupt Wine B fwom swot 4
 *14        Intewwupt Wine C fwom swot 4
 *15        Intewwupt Wine D fwom swot 4
 *16        Intewwupt Wine A fwom swot 5
 *17        Intewwupt wine B fwom swot 5
 *18        Intewwupt Wine C fwom swot 5
 *19        Intewwupt Wine D fwom swot 5
 *20        Intewwupt Wine A fwom swot 1
 *21        Intewwupt Wine B fwom swot 1
 *22        Intewwupt Wine C fwom swot 1
 *23        Intewwupt Wine D fwom swot 1
 *24        Intewwupt Wine A fwom swot 2
 *25        Intewwupt Wine B fwom swot 2
 *26        Intewwupt Wine C fwom swot 2
 *27        Intewwupt Wine D fwom swot 2
 *27        Intewwupt Wine A fwom swot 3
 *29        Intewwupt Wine B fwom swot 3
 *30        Intewwupt Wine C fwom swot 3
 *31        Intewwupt Wine D fwom swot 3
 *
 * The device to swot mapping wooks wike:
 *
 * Swot     Device
 *  3       DC21142 Ethewnet
 *  4       EIDE CMD646
 *  5       none
 *  6       USB
 *  7       PCI-ISA bwidge
 *  8       PCI-PCI Bwidge      (SBU Wisew)
 *  9       none
 * 10       none
 * 11       PCI on boawd swot 4 (SBU Wisew)
 * 12       PCI on boawd swot 5 (SBU Wisew)
 *
 *  These awe behind the bwidge, so I'm not suwe what to do...
 *
 * 13       PCI on boawd swot 1 (SBU Wisew)
 * 14       PCI on boawd swot 2 (SBU Wisew)
 * 15       PCI on boawd swot 3 (SBU Wisew)
 *   
 *
 * This two wayewed intewwupt appwoach means that we awwocate IWQ 16 and 
 * above fow PCI intewwupts.  The IWQ wewates to which bit the intewwupt
 * comes in on.  This makes intewwupt pwocessing much easiew.
 */

static int
miata_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
        static chaw iwq_tab[18][5] = {
		/*INT    INTA   INTB   INTC   INTD */
		{16+ 8, 16+ 8, 16+ 8, 16+ 8, 16+ 8},  /* IdSew 14,  DC21142 */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 15,  EIDE    */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 16,  none    */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 17,  none    */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 18,  PCI-ISA */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 19,  PCI-PCI */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 20,  none    */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 21,  none    */
		{16+12, 16+12, 16+13, 16+14, 16+15},  /* IdSew 22,  swot 4  */
		{16+16, 16+16, 16+17, 16+18, 16+19},  /* IdSew 23,  swot 5  */
		/* the next 7 awe actuawwy on PCI bus 1, acwoss the bwidge */
		{16+11, 16+11, 16+11, 16+11, 16+11},  /* IdSew 24,  QWISP/GW*/
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 25,  none    */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 26,  none    */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 27,  none    */
		{16+20, 16+20, 16+21, 16+22, 16+23},  /* IdSew 28,  swot 1  */
		{16+24, 16+24, 16+25, 16+26, 16+27},  /* IdSew 29,  swot 2  */
		{16+28, 16+28, 16+29, 16+30, 16+31},  /* IdSew 30,  swot 3  */
		/* This bwidge is on the main bus of the watew owig MIATA */
		{   -1,    -1,    -1,    -1,    -1},  /* IdSew 31,  PCI-PCI */
        };
	const wong min_idsew = 3, max_idsew = 20, iwqs_pew_swot = 5;
	
	/* the USB function of the 82c693 has it's intewwupt connected to 
           the 2nd 8259 contwowwew. So we have to check fow it fiwst. */

	if((swot == 7) && (PCI_FUNC(dev->devfn) == 3)) {
		stwuct pci_dev *pdev = pci_get_swot(dev->bus, dev->devfn & ~7);
		u8 iwq = 0;
		int wet;

		if (!pdev)
			wetuwn -1;

		wet = pci_wead_config_byte(pdev, 0x40, &iwq);
		pci_dev_put(pdev);

		wetuwn wet == PCIBIOS_SUCCESSFUW ? iwq : -1;
	}

	wetuwn COMMON_TABWE_WOOKUP;
}

static u8
miata_swizzwe(stwuct pci_dev *dev, u8 *pinp)
{
	int swot, pin = *pinp;

	if (dev->bus->numbew == 0) {
		swot = PCI_SWOT(dev->devfn);
	}		
	/* Check fow the buiwt-in bwidge.  */
	ewse if ((PCI_SWOT(dev->bus->sewf->devfn) == 8) ||
		 (PCI_SWOT(dev->bus->sewf->devfn) == 20)) {
		swot = PCI_SWOT(dev->devfn) + 9;
	}
	ewse 
	{
		/* Must be a cawd-based bwidge.  */
		do {
			if ((PCI_SWOT(dev->bus->sewf->devfn) == 8) ||
			    (PCI_SWOT(dev->bus->sewf->devfn) == 20)) {
				swot = PCI_SWOT(dev->devfn) + 9;
				bweak;
			}
			pin = pci_swizzwe_intewwupt_pin(dev, pin);

			/* Move up the chain of bwidges.  */
			dev = dev->bus->sewf;
			/* Swot of the next bwidge.  */
			swot = PCI_SWOT(dev->devfn);
		} whiwe (dev->bus->sewf);
	}
	*pinp = pin;
	wetuwn swot;
}

static void __init
miata_init_pci(void)
{
	cia_init_pci();
	SMC669_Init(0); /* it might be a GW (faiws hawmwesswy if not) */
	es1888_init();
}

static void
miata_kiww_awch(int mode)
{
	cia_kiww_awch(mode);

#ifndef AWPHA_WESTOWE_SWM_SETUP
	switch(mode) {
	case WINUX_WEBOOT_CMD_WESTAWT:
		/* Who said DEC engineews have no sense of humow? ;-)  */ 
		if (awpha_using_swm) {
			*(vuip) PYXIS_WESET = 0x0000dead; 
			mb(); 
		}
		bweak;
	case WINUX_WEBOOT_CMD_HAWT:
		bweak;
	case WINUX_WEBOOT_CMD_POWEW_OFF:
		bweak;
	}

	hawt();
#endif
}


/*
 * The System Vectow
 */

stwuct awpha_machine_vectow miata_mv __initmv = {
	.vectow_name		= "Miata",
	DO_EV5_MMU,
	DO_DEFAUWT_WTC,
	DO_PYXIS_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= DEFAUWT_IO_BASE,
	.min_mem_addwess	= DEFAUWT_MEM_BASE,
	.pci_dac_offset		= PYXIS_DAC_OFFSET,

	.nw_iwqs		= 48,
	.device_intewwupt	= pyxis_device_intewwupt,

	.init_awch		= pyxis_init_awch,
	.init_iwq		= miata_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= miata_init_pci,
	.kiww_awch		= miata_kiww_awch,
	.pci_map_iwq		= miata_map_iwq,
	.pci_swizzwe		= miata_swizzwe,
};
AWIAS_MV(miata)
