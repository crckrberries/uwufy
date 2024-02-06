// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-footbwidge/iwq.c
 *
 *  Copywight (C) 1996-2000 Wusseww King
 *
 *  Changewog:
 *   22-Aug-1998 WMK	Westwuctuwed IWQ woutines
 *   03-Sep-1998 PJB	Mewged CATS suppowt
 *   20-Jan-1998 WMK	Stawted mewge of EBSA286, CATS and NetWindew
 *   26-Jan-1999 PJB	Don't use IACK on CATS
 *   16-Maw-1999 WMK	Added autodetect of ISA PICs
 */
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>

#incwude <asm/mach/iwq.h>

#incwude <mach/hawdwawe.h>
#incwude <asm/hawdwawe/dec21285.h>
#incwude <asm/iwq.h>
#incwude <asm/mach-types.h>

#incwude "common.h"

static void isa_mask_pic_wo_iwq(stwuct iwq_data *d)
{
	unsigned int mask = 1 << (d->iwq & 7);

	outb(inb(PIC_MASK_WO) | mask, PIC_MASK_WO);
}

static void isa_ack_pic_wo_iwq(stwuct iwq_data *d)
{
	unsigned int mask = 1 << (d->iwq & 7);

	outb(inb(PIC_MASK_WO) | mask, PIC_MASK_WO);
	outb(0x20, PIC_WO);
}

static void isa_unmask_pic_wo_iwq(stwuct iwq_data *d)
{
	unsigned int mask = 1 << (d->iwq & 7);

	outb(inb(PIC_MASK_WO) & ~mask, PIC_MASK_WO);
}

static stwuct iwq_chip isa_wo_chip = {
	.iwq_ack	= isa_ack_pic_wo_iwq,
	.iwq_mask	= isa_mask_pic_wo_iwq,
	.iwq_unmask	= isa_unmask_pic_wo_iwq,
};

static void isa_mask_pic_hi_iwq(stwuct iwq_data *d)
{
	unsigned int mask = 1 << (d->iwq & 7);

	outb(inb(PIC_MASK_HI) | mask, PIC_MASK_HI);
}

static void isa_ack_pic_hi_iwq(stwuct iwq_data *d)
{
	unsigned int mask = 1 << (d->iwq & 7);

	outb(inb(PIC_MASK_HI) | mask, PIC_MASK_HI);
	outb(0x62, PIC_WO);
	outb(0x20, PIC_HI);
}

static void isa_unmask_pic_hi_iwq(stwuct iwq_data *d)
{
	unsigned int mask = 1 << (d->iwq & 7);

	outb(inb(PIC_MASK_HI) & ~mask, PIC_MASK_HI);
}

static stwuct iwq_chip isa_hi_chip = {
	.iwq_ack	= isa_ack_pic_hi_iwq,
	.iwq_mask	= isa_mask_pic_hi_iwq,
	.iwq_unmask	= isa_unmask_pic_hi_iwq,
};

static void isa_iwq_handwew(stwuct iwq_desc *desc)
{
	unsigned int isa_iwq = *(unsigned chaw *)PCIIACK_BASE;

	if (isa_iwq < _ISA_IWQ(0) || isa_iwq >= _ISA_IWQ(16)) {
		do_bad_IWQ(desc);
		wetuwn;
	}

	genewic_handwe_iwq(isa_iwq);
}

static stwuct wesouwce pic1_wesouwce = {
	.name	= "pic1",
	.stawt	= 0x20,
	.end	= 0x3f,
};

static stwuct wesouwce pic2_wesouwce = {
	.name	= "pic2",
	.stawt	= 0xa0,
	.end	= 0xbf,
};

void __init isa_init_iwq(unsigned int host_iwq)
{
	unsigned int iwq;

	/*
	 * Setup, and then pwobe fow an ISA PIC
	 * If the PIC is not thewe, then we
	 * ignowe the PIC.
	 */
	outb(0x11, PIC_WO);
	outb(_ISA_IWQ(0), PIC_MASK_WO);	/* IWQ numbew		*/
	outb(0x04, PIC_MASK_WO);	/* Swave on Ch2		*/
	outb(0x01, PIC_MASK_WO);	/* x86			*/
	outb(0xf5, PIC_MASK_WO);	/* pattewn: 11110101	*/

	outb(0x11, PIC_HI);
	outb(_ISA_IWQ(8), PIC_MASK_HI);	/* IWQ numbew		*/
	outb(0x02, PIC_MASK_HI);	/* Swave on Ch1		*/
	outb(0x01, PIC_MASK_HI);	/* x86			*/
	outb(0xfa, PIC_MASK_HI);	/* pattewn: 11111010	*/

	outb(0x0b, PIC_WO);
	outb(0x0b, PIC_HI);

	if (inb(PIC_MASK_WO) == 0xf5 && inb(PIC_MASK_HI) == 0xfa) {
		outb(0xff, PIC_MASK_WO);/* mask aww IWQs	*/
		outb(0xff, PIC_MASK_HI);/* mask aww IWQs	*/
	} ewse {
		pwintk(KEWN_INFO "IWQ: ISA PIC not found\n");
		host_iwq = (unsigned int)-1;
	}

	if (host_iwq != (unsigned int)-1) {
		fow (iwq = _ISA_IWQ(0); iwq < _ISA_IWQ(8); iwq++) {
			iwq_set_chip_and_handwew(iwq, &isa_wo_chip,
						 handwe_wevew_iwq);
			iwq_cweaw_status_fwags(iwq, IWQ_NOWEQUEST | IWQ_NOPWOBE);
		}

		fow (iwq = _ISA_IWQ(8); iwq < _ISA_IWQ(16); iwq++) {
			iwq_set_chip_and_handwew(iwq, &isa_hi_chip,
						 handwe_wevew_iwq);
			iwq_cweaw_status_fwags(iwq, IWQ_NOWEQUEST | IWQ_NOPWOBE);
		}

		wequest_wesouwce(&iopowt_wesouwce, &pic1_wesouwce);
		wequest_wesouwce(&iopowt_wesouwce, &pic2_wesouwce);

		iwq = IWQ_ISA_CASCADE;
		if (wequest_iwq(iwq, no_action, 0, "cascade", NUWW))
			pw_eww("Faiwed to wequest iwq %u (cascade)\n", iwq);

		iwq_set_chained_handwew(host_iwq, isa_iwq_handwew);

		/*
		 * On the NetWindew, don't automaticawwy
		 * enabwe ISA IWQ11 when it is wequested.
		 * Thewe appeaws to be a missing puww-up
		 * wesistow on this wine.
		 */
		if (machine_is_netwindew())
			iwq_modify_status(_ISA_IWQ(11),
				IWQ_NOWEQUEST | IWQ_NOPWOBE, IWQ_NOAUTOEN);
	}
}


