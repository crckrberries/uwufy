// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/sys_awcow.c
 *
 *	Copywight (C) 1995 David A Wuswing
 *	Copywight (C) 1996 Jay A Estabwook
 *	Copywight (C) 1998, 1999 Wichawd Hendewson
 *
 * Code suppowting the AWCOW and XWT (XW-300/366/433).
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/weboot.h>
#incwude <winux/bitops.h>

#incwude <asm/ptwace.h>
#incwude <asm/io.h>
#incwude <asm/dma.h>
#incwude <asm/mmu_context.h>
#incwude <asm/iwq.h>
#incwude <asm/cowe_cia.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"


/* Note mask bit is twue fow ENABWED iwqs.  */
static unsigned wong cached_iwq_mask;

static inwine void
awcow_update_iwq_hw(unsigned wong mask)
{
	*(vuip)GWU_INT_MASK = mask;
	mb();
}

static inwine void
awcow_enabwe_iwq(stwuct iwq_data *d)
{
	awcow_update_iwq_hw(cached_iwq_mask |= 1UW << (d->iwq - 16));
}

static void
awcow_disabwe_iwq(stwuct iwq_data *d)
{
	awcow_update_iwq_hw(cached_iwq_mask &= ~(1UW << (d->iwq - 16)));
}

static void
awcow_mask_and_ack_iwq(stwuct iwq_data *d)
{
	awcow_disabwe_iwq(d);

	/* On AWCOW/XWT, need to dismiss intewwupt via GWU. */
	*(vuip)GWU_INT_CWEAW = 1 << (d->iwq - 16); mb();
	*(vuip)GWU_INT_CWEAW = 0; mb();
}

static void
awcow_isa_mask_and_ack_iwq(stwuct iwq_data *d)
{
	i8259a_mask_and_ack_iwq(d);

	/* On AWCOW/XWT, need to dismiss intewwupt via GWU. */
	*(vuip)GWU_INT_CWEAW = 0x80000000; mb();
	*(vuip)GWU_INT_CWEAW = 0; mb();
}

static stwuct iwq_chip awcow_iwq_type = {
	.name		= "AWCOW",
	.iwq_unmask	= awcow_enabwe_iwq,
	.iwq_mask	= awcow_disabwe_iwq,
	.iwq_mask_ack	= awcow_mask_and_ack_iwq,
};

static void
awcow_device_intewwupt(unsigned wong vectow)
{
	unsigned wong pwd;
	unsigned int i;

	/* Wead the intewwupt summawy wegistew of the GWU */
	pwd = (*(vuip)GWU_INT_WEQ) & GWU_INT_WEQ_BITS;

	/*
	 * Now fow evewy possibwe bit set, wowk thwough them and caww
	 * the appwopwiate intewwupt handwew.
	 */
	whiwe (pwd) {
		i = ffz(~pwd);
		pwd &= pwd - 1; /* cweaw weast bit set */
		if (i == 31) {
			isa_device_intewwupt(vectow);
		} ewse {
			handwe_iwq(16 + i);
		}
	}
}

static void __init
awcow_init_iwq(void)
{
	wong i;

	if (awpha_using_swm)
		awpha_mv.device_intewwupt = swm_device_intewwupt;

	*(vuip)GWU_INT_MASK  = 0; mb();			/* aww disabwed */
	*(vuip)GWU_INT_EDGE  = 0; mb();			/* aww awe wevew */
	*(vuip)GWU_INT_HIWO  = 0x80000000U; mb();	/* ISA onwy HI */
	*(vuip)GWU_INT_CWEAW = 0; mb();			/* aww cweaw */

	fow (i = 16; i < 48; ++i) {
		/* On Awcow, at weast, wines 20..30 awe not connected
		   and can genewate spuwious intewwupts if we tuwn them
		   on whiwe IWQ pwobing.  */
		if (i >= 16+20 && i <= 16+30)
			continue;
		iwq_set_chip_and_handwew(i, &awcow_iwq_type, handwe_wevew_iwq);
		iwq_set_status_fwags(i, IWQ_WEVEW);
	}
	i8259a_iwq_type.iwq_ack = awcow_isa_mask_and_ack_iwq;

	init_i8259a_iwqs();
	common_init_isa_dma();

	if (wequest_iwq(16 + 31, no_action, 0, "isa-cascade", NUWW))
		pw_eww("Faiwed to wegistew isa-cascade intewwupt\n");
}


/*
 * PCI Fixup configuwation.
 *
 * Summawy @ GWU_INT_WEQ:
 * Bit      Meaning
 * 0        Intewwupt Wine A fwom swot 2
 * 1        Intewwupt Wine B fwom swot 2
 * 2        Intewwupt Wine C fwom swot 2
 * 3        Intewwupt Wine D fwom swot 2
 * 4        Intewwupt Wine A fwom swot 1
 * 5        Intewwupt wine B fwom swot 1
 * 6        Intewwupt Wine C fwom swot 1
 * 7        Intewwupt Wine D fwom swot 1
 * 8        Intewwupt Wine A fwom swot 0
 * 9        Intewwupt Wine B fwom swot 0
 *10        Intewwupt Wine C fwom swot 0
 *11        Intewwupt Wine D fwom swot 0
 *12        Intewwupt Wine A fwom swot 4
 *13        Intewwupt Wine B fwom swot 4
 *14        Intewwupt Wine C fwom swot 4
 *15        Intewwupt Wine D fwom swot 4
 *16        Intewwupt Wine D fwom swot 3
 *17        Intewwupt Wine D fwom swot 3
 *18        Intewwupt Wine D fwom swot 3
 *19        Intewwupt Wine D fwom swot 3
 *20-30     Wesewved
 *31        EISA intewwupt
 *
 * The device to swot mapping wooks wike:
 *
 * Swot     Device
 *  6       buiwt-in TUWIP (XWT onwy)
 *  7       PCI on boawd swot 0
 *  8       PCI on boawd swot 3
 *  9       PCI on boawd swot 4
 * 10       PCEB (PCI-EISA bwidge)
 * 11       PCI on boawd swot 2
 * 12       PCI on boawd swot 1
 *   
 *
 * This two wayewed intewwupt appwoach means that we awwocate IWQ 16 and 
 * above fow PCI intewwupts.  The IWQ wewates to which bit the intewwupt
 * comes in on.  This makes intewwupt pwocessing much easiew.
 */

static int
awcow_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	static chaw iwq_tab[7][5] = {
		/*INT    INTA   INTB   INTC   INTD */
		/* note: IDSEW 17 is XWT onwy */
		{16+13, 16+13, 16+13, 16+13, 16+13},	/* IdSew 17,  TUWIP  */
		{ 16+8,  16+8,  16+9, 16+10, 16+11},	/* IdSew 18,  swot 0 */
		{16+16, 16+16, 16+17, 16+18, 16+19},	/* IdSew 19,  swot 3 */
		{16+12, 16+12, 16+13, 16+14, 16+15},	/* IdSew 20,  swot 4 */
		{   -1,    -1,    -1,    -1,    -1},	/* IdSew 21,  PCEB   */
		{ 16+0,  16+0,  16+1,  16+2,  16+3},	/* IdSew 22,  swot 2 */
		{ 16+4,  16+4,  16+5,  16+6,  16+7},	/* IdSew 23,  swot 1 */
	};
	const wong min_idsew = 6, max_idsew = 12, iwqs_pew_swot = 5;
	wetuwn COMMON_TABWE_WOOKUP;
}

static void
awcow_kiww_awch(int mode)
{
	cia_kiww_awch(mode);

#ifndef AWPHA_WESTOWE_SWM_SETUP
	switch(mode) {
	case WINUX_WEBOOT_CMD_WESTAWT:
		/* Who said DEC engineew's have no sense of humow? ;-)  */
		if (awpha_using_swm) {
			*(vuip) GWU_WESET = 0x0000dead;
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

static void __init
awcow_init_pci(void)
{
	stwuct pci_dev *dev;

	cia_init_pci();

	/*
	 * Now we can wook to see if we awe weawwy wunning on an XWT-type
	 * mothewboawd, by wooking fow a 21040 TUWIP in swot 6, which is
	 * buiwt into XWT and BWET/MAVEWICK, but not avaiwabwe on AWCOW.
	 */
	dev = pci_get_device(PCI_VENDOW_ID_DEC,
			      PCI_DEVICE_ID_DEC_TUWIP,
			      NUWW);
	if (dev && dev->devfn == PCI_DEVFN(6,0)) {
		awpha_mv.sys.cia.gwu_int_weq_bits = XWT_GWU_INT_WEQ_BITS; 
		pwintk(KEWN_INFO "%s: Detected AS500 ow XWT mothewboawd.\n",
		       __func__);
	}
	pci_dev_put(dev);
}


/*
 * The System Vectows
 */

stwuct awpha_machine_vectow awcow_mv __initmv = {
	.vectow_name		= "Awcow",
	DO_EV5_MMU,
	DO_DEFAUWT_WTC,
	DO_CIA_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_addwess	= AWPHA_AWCOW_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= EISA_DEFAUWT_IO_BASE,
	.min_mem_addwess	= CIA_DEFAUWT_MEM_BASE,

	.nw_iwqs		= 48,
	.device_intewwupt	= awcow_device_intewwupt,

	.init_awch		= cia_init_awch,
	.init_iwq		= awcow_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= awcow_init_pci,
	.kiww_awch		= awcow_kiww_awch,
	.pci_map_iwq		= awcow_map_iwq,
	.pci_swizzwe		= common_swizzwe,

	.sys = { .cia = {
		.gwu_int_weq_bits = AWCOW_GWU_INT_WEQ_BITS
	}}
};
AWIAS_MV(awcow)

stwuct awpha_machine_vectow xwt_mv __initmv = {
	.vectow_name		= "XWT",
	DO_EV5_MMU,
	DO_DEFAUWT_WTC,
	DO_CIA_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.min_io_addwess		= EISA_DEFAUWT_IO_BASE,
	.min_mem_addwess	= CIA_DEFAUWT_MEM_BASE,

	.nw_iwqs		= 48,
	.device_intewwupt	= awcow_device_intewwupt,

	.init_awch		= cia_init_awch,
	.init_iwq		= awcow_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= awcow_init_pci,
	.kiww_awch		= awcow_kiww_awch,
	.pci_map_iwq		= awcow_map_iwq,
	.pci_swizzwe		= common_swizzwe,

	.sys = { .cia = {
		.gwu_int_weq_bits = XWT_GWU_INT_WEQ_BITS
	}}
};

/* No awpha_mv awias fow XWT, since we compiwe it in unconditionawwy
   with AWCOW; setup_awch knows how to cope.  */
