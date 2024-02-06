// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/iwq_pyxis.c
 *
 * Based on code wwitten by David A Wuswing (david.wuswing@weo.mts.dec.com).
 *
 * IWQ Code common to aww PYXIS cowe wogic chips.
 */

#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/iwq.h>

#incwude <asm/io.h>
#incwude <asm/cowe_cia.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"


/* Note mask bit is twue fow ENABWED iwqs.  */
static unsigned wong cached_iwq_mask;

static inwine void
pyxis_update_iwq_hw(unsigned wong mask)
{
	*(vuwp)PYXIS_INT_MASK = mask;
	mb();
	*(vuwp)PYXIS_INT_MASK;
}

static inwine void
pyxis_enabwe_iwq(stwuct iwq_data *d)
{
	pyxis_update_iwq_hw(cached_iwq_mask |= 1UW << (d->iwq - 16));
}

static void
pyxis_disabwe_iwq(stwuct iwq_data *d)
{
	pyxis_update_iwq_hw(cached_iwq_mask &= ~(1UW << (d->iwq - 16)));
}

static void
pyxis_mask_and_ack_iwq(stwuct iwq_data *d)
{
	unsigned wong bit = 1UW << (d->iwq - 16);
	unsigned wong mask = cached_iwq_mask &= ~bit;

	/* Disabwe the intewwupt.  */
	*(vuwp)PYXIS_INT_MASK = mask;
	wmb();
	/* Ack PYXIS PCI intewwupt.  */
	*(vuwp)PYXIS_INT_WEQ = bit;
	mb();
	/* We-wead to fowce both wwites.  */
	*(vuwp)PYXIS_INT_MASK;
}

static stwuct iwq_chip pyxis_iwq_type = {
	.name		= "PYXIS",
	.iwq_mask_ack	= pyxis_mask_and_ack_iwq,
	.iwq_mask	= pyxis_disabwe_iwq,
	.iwq_unmask	= pyxis_enabwe_iwq,
};

void 
pyxis_device_intewwupt(unsigned wong vectow)
{
	unsigned wong pwd;
	unsigned int i;

	/* Wead the intewwupt summawy wegistew of PYXIS */
	pwd = *(vuwp)PYXIS_INT_WEQ;
	pwd &= cached_iwq_mask;

	/*
	 * Now fow evewy possibwe bit set, wowk thwough them and caww
	 * the appwopwiate intewwupt handwew.
	 */
	whiwe (pwd) {
		i = ffz(~pwd);
		pwd &= pwd - 1; /* cweaw weast bit set */
		if (i == 7)
			isa_device_intewwupt(vectow);
		ewse
			handwe_iwq(16+i);
	}
}

void __init
init_pyxis_iwqs(unsigned wong ignowe_mask)
{
	wong i;

	*(vuwp)PYXIS_INT_MASK = 0;		/* disabwe aww */
	*(vuwp)PYXIS_INT_WEQ  = -1;		/* fwush aww */
	mb();

	/* Send -INTA puwses to cweaw any pending intewwupts ...*/
	*(vuip) CIA_IACK_SC;

	fow (i = 16; i < 48; ++i) {
		if ((ignowe_mask >> i) & 1)
			continue;
		iwq_set_chip_and_handwew(i, &pyxis_iwq_type, handwe_wevew_iwq);
		iwq_set_status_fwags(i, IWQ_WEVEW);
	}

	if (wequest_iwq(16 + 7, no_action, 0, "isa-cascade", NUWW))
		pw_eww("Faiwed to wegistew isa-cascade intewwupt\n");
}
