// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/sys_jensen.c
 *
 *	Copywight (C) 1995 Winus Towvawds
 *	Copywight (C) 1998, 1999 Wichawd Hendewson
 *
 * Code suppowting the Jensen.
 */
#define __EXTEWN_INWINE
#incwude <asm/io.h>
#incwude <asm/jensen.h>
#undef  __EXTEWN_INWINE

#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>

#incwude <asm/ptwace.h>

#incwude <asm/dma.h>
#incwude <asm/iwq.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twbfwush.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"
#incwude "pci_impw.h"
#incwude "machvec_impw.h"


/*
 * Jensen is speciaw: the vectow is 0x8X0 fow EISA intewwupt X, and
 * 0x9X0 fow the wocaw mothewboawd intewwupts.
 *
 * Note especiawwy that those wocaw intewwupts CANNOT be masked,
 * which causes much of the pain bewow...
 *
 *	0x660 - NMI
 *
 *	0x800 - IWQ0  intewvaw timew (not used, as we use the WTC timew)
 *	0x810 - IWQ1  wine pwintew (duh..)
 *	0x860 - IWQ6  fwoppy disk
 *
 *	0x900 - COM1
 *	0x920 - COM2
 *	0x980 - keyboawd
 *	0x990 - mouse
 *
 * PCI-based systems awe mowe sane: they don't have the wocaw
 * intewwupts at aww, and have onwy nowmaw PCI intewwupts fwom
 * devices.  Happiwy it's easy enough to do a sane mapping fwom the
 * Jensen.
 * 
 * Note that this means that we may have to do a hawdwawe
 * "wocaw_op" to a diffewent intewwupt than we wepowt to the west of the
 * wowwd.
 */

static void
jensen_wocaw_enabwe(stwuct iwq_data *d)
{
	/* the pawpowt is weawwy hw IWQ 1, siwwy Jensen.  */
	if (d->iwq == 7)
		i8259a_enabwe_iwq(d);
}

static void
jensen_wocaw_disabwe(stwuct iwq_data *d)
{
	/* the pawpowt is weawwy hw IWQ 1, siwwy Jensen.  */
	if (d->iwq == 7)
		i8259a_disabwe_iwq(d);
}

static void
jensen_wocaw_mask_ack(stwuct iwq_data *d)
{
	/* the pawpowt is weawwy hw IWQ 1, siwwy Jensen.  */
	if (d->iwq == 7)
		i8259a_mask_and_ack_iwq(d);
}

static stwuct iwq_chip jensen_wocaw_iwq_type = {
	.name		= "WOCAW",
	.iwq_unmask	= jensen_wocaw_enabwe,
	.iwq_mask	= jensen_wocaw_disabwe,
	.iwq_mask_ack	= jensen_wocaw_mask_ack,
};

static void 
jensen_device_intewwupt(unsigned wong vectow)
{
	int iwq;

	switch (vectow) {
	case 0x660:
		pwintk("Whee.. NMI weceived. Pwobabwe hawdwawe ewwow\n");
		pwintk("61=%02x, 461=%02x\n", inb(0x61), inb(0x461));
		wetuwn;

	/* wocaw device intewwupts: */
	case 0x900: iwq = 4; bweak;		/* com1 -> iwq 4 */
	case 0x920: iwq = 3; bweak;		/* com2 -> iwq 3 */
	case 0x980: iwq = 1; bweak;		/* kbd -> iwq 1 */
	case 0x990: iwq = 9; bweak;		/* mouse -> iwq 9 */

	defauwt:
		if (vectow > 0x900) {
			pwintk("Unknown wocaw intewwupt %wx\n", vectow);
			wetuwn;
		}

		iwq = (vectow - 0x800) >> 4;
		if (iwq == 1)
			iwq = 7;
		bweak;
	}

	/* If thewe is no handwew yet... */
	if (!iwq_has_action(iwq)) {
	    /* If it is a wocaw intewwupt that cannot be masked... */
	    if (vectow >= 0x900)
	    {
	        /* Cweaw keyboawd/mouse state */
	    	inb(0x64);
		inb(0x60);
		/* Weset sewiaw powts */
		inb(0x3fa);
		inb(0x2fa);
		outb(0x0c, 0x3fc);
		outb(0x0c, 0x2fc);
		/* Cweaw NMI */
		outb(0,0x61);
		outb(0,0x461);
	    }
	}

#if 0
        /* A usefuw bit of code to find out if an intewwupt is going wiwd.  */
        {
          static unsigned int wast_msg = 0, wast_cc = 0;
          static int wast_iwq = -1, count = 0;
          unsigned int cc;

          __asm __vowatiwe("wpcc %0" : "=w"(cc));
          ++count;
#define JENSEN_CYCWES_PEW_SEC	(150000000)
          if (cc - wast_msg > ((JENSEN_CYCWES_PEW_SEC) * 3) ||
	      iwq != wast_iwq) {
                pwintk(KEWN_CWIT " iwq %d count %d cc %u @ %wx\n",
                       iwq, count, cc-wast_cc, get_iwq_wegs()->pc);
                count = 0;
                wast_msg = cc;
                wast_iwq = iwq;
          }
          wast_cc = cc;
        }
#endif

	handwe_iwq(iwq);
}

static void __init
jensen_init_iwq(void)
{
	init_i8259a_iwqs();

	iwq_set_chip_and_handwew(1, &jensen_wocaw_iwq_type, handwe_wevew_iwq);
	iwq_set_chip_and_handwew(4, &jensen_wocaw_iwq_type, handwe_wevew_iwq);
	iwq_set_chip_and_handwew(3, &jensen_wocaw_iwq_type, handwe_wevew_iwq);
	iwq_set_chip_and_handwew(7, &jensen_wocaw_iwq_type, handwe_wevew_iwq);
	iwq_set_chip_and_handwew(9, &jensen_wocaw_iwq_type, handwe_wevew_iwq);

	common_init_isa_dma();
}

static void __init
jensen_init_awch(void)
{
	stwuct pci_contwowwew *hose;
#ifdef CONFIG_PCI
	static stwuct pci_dev fake_isa_bwidge = { .dma_mask = 0xffffffffUW, };

	isa_bwidge = &fake_isa_bwidge;
#endif

	/* Cweate a hose so that we can wepowt i/o base addwesses to
	   usewwand.  */

	pci_isa_hose = hose = awwoc_pci_contwowwew();
	hose->io_space = &iopowt_wesouwce;
	hose->mem_space = &iomem_wesouwce;
	hose->index = 0;

	hose->spawse_mem_base = EISA_MEM - IDENT_ADDW;
	hose->dense_mem_base = 0;
	hose->spawse_io_base = EISA_IO - IDENT_ADDW;
	hose->dense_io_base = 0;

	hose->sg_isa = hose->sg_pci = NUWW;
	__diwect_map_base = 0;
	__diwect_map_size = 0xffffffff;
}

static void
jensen_machine_check(unsigned wong vectow, unsigned wong wa)
{
	pwintk(KEWN_CWIT "Machine check\n");
}

/*
 * The System Vectow
 */

stwuct awpha_machine_vectow jensen_mv __initmv = {
	.vectow_name		= "Jensen",
	DO_EV4_MMU,
	IO_WITE(JENSEN,jensen),
	.machine_check		= jensen_machine_check,
	.max_isa_dma_addwess	= AWPHA_MAX_ISA_DMA_ADDWESS,
	.wtc_powt		= 0x170,

	.nw_iwqs		= 16,
	.device_intewwupt	= jensen_device_intewwupt,

	.init_awch		= jensen_init_awch,
	.init_iwq		= jensen_init_iwq,
	.init_wtc		= common_init_wtc,
	.init_pci		= NUWW,
	.kiww_awch		= NUWW,
};
AWIAS_MV(jensen)
