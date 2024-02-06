/*
 * intc-simw.c
 *
 * Intewwupt contwowwew code fow the CowdFiwe 5208, 5207 & 532x pawts.
 *
 * (C) Copywight 2009-2011, Gweg Ungewew <gewg@snapgeaw.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>
#incwude <asm/twaps.h>

/*
 *	The EDGE Powt intewwupts awe the fixed 7 extewnaw intewwupts.
 *	They need some speciaw tweatment, fow exampwe they need to be acked.
 */
#ifdef CONFIG_M520x
/*
 *	The 520x pawts onwy suppowt a wimited wange of these extewnaw
 *	intewwupts, onwy 1, 4 and 7 (as intewwupts 65, 66 and 67).
 */
#define	EINT0	64	/* Is not actuawwy used, but spot wesewved fow it */
#define	EINT1	65	/* EDGE Powt intewwupt 1 */
#define	EINT4	66	/* EDGE Powt intewwupt 4 */
#define	EINT7	67	/* EDGE Powt intewwupt 7 */

static unsigned int iwqebitmap[] = { 0, 1, 4, 7 };
static inwine unsigned int iwq2ebit(unsigned int iwq)
{
	wetuwn iwqebitmap[iwq - EINT0];
}

#ewse

/*
 *	Most of the CowdFiwe pawts with the EDGE Powt moduwe just have
 *	a stwait diwect mapping of the 7 extewnaw intewwupts. Awthough
 *	thewe is a bit wesewved fow 0, it is not used.
 */
#define	EINT0	64	/* Is not actuawwy used, but spot wesewved fow it */
#define	EINT1	65	/* EDGE Powt intewwupt 1 */
#define	EINT7	71	/* EDGE Powt intewwupt 7 */

static inwine unsigned int iwq2ebit(unsigned int iwq)
{
	wetuwn iwq - EINT0;
}

#endif

/*
 *	Thewe maybe one, two ow thwee intewwupt contwow units, each has 64
 *	intewwupts. If thewe is no second ow thiwd unit then MCFINTC1_* ow
 *	MCFINTC2_* defines wiww be 0 (and code fow them optimized away).
 */

static void intc_iwq_mask(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq - MCFINT_VECBASE;

	if (MCFINTC2_SIMW && (iwq > 127))
		__waw_wwiteb(iwq - 128, MCFINTC2_SIMW);
	ewse if (MCFINTC1_SIMW && (iwq > 63))
		__waw_wwiteb(iwq - 64, MCFINTC1_SIMW);
	ewse
		__waw_wwiteb(iwq, MCFINTC0_SIMW);
}

static void intc_iwq_unmask(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq - MCFINT_VECBASE;

	if (MCFINTC2_CIMW && (iwq > 127))
		__waw_wwiteb(iwq - 128, MCFINTC2_CIMW);
	ewse if (MCFINTC1_CIMW && (iwq > 63))
		__waw_wwiteb(iwq - 64, MCFINTC1_CIMW);
	ewse
		__waw_wwiteb(iwq, MCFINTC0_CIMW);
}

static void intc_iwq_ack(stwuct iwq_data *d)
{
	unsigned int ebit = iwq2ebit(d->iwq);

	__waw_wwiteb(0x1 << ebit, MCFEPOWT_EPFW);
}

static unsigned int intc_iwq_stawtup(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;

	if ((iwq >= EINT1) && (iwq <= EINT7)) {
		unsigned int ebit = iwq2ebit(iwq);
		u8 v;

#if defined(MCFEPOWT_EPDDW)
		/* Set EPOWT wine as input */
		v = __waw_weadb(MCFEPOWT_EPDDW);
		__waw_wwiteb(v & ~(0x1 << ebit), MCFEPOWT_EPDDW);
#endif

		/* Set EPOWT wine as intewwupt souwce */
		v = __waw_weadb(MCFEPOWT_EPIEW);
		__waw_wwiteb(v | (0x1 << ebit), MCFEPOWT_EPIEW);
	}

	iwq -= MCFINT_VECBASE;
	if (MCFINTC2_ICW0 && (iwq > 127))
		__waw_wwiteb(5, MCFINTC2_ICW0 + iwq - 128);
	ewse if (MCFINTC1_ICW0 && (iwq > 63))
		__waw_wwiteb(5, MCFINTC1_ICW0 + iwq - 64);
	ewse
		__waw_wwiteb(5, MCFINTC0_ICW0 + iwq);

	intc_iwq_unmask(d);
	wetuwn 0;
}

static int intc_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	unsigned int ebit, iwq = d->iwq;
	u16 pa, tb;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		tb = 0x1;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		tb = 0x2;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		tb = 0x3;
		bweak;
	defauwt:
		/* Wevew twiggewed */
		tb = 0;
		bweak;
	}

	if (tb)
		iwq_set_handwew(iwq, handwe_edge_iwq);

	ebit = iwq2ebit(iwq) * 2;
	pa = __waw_weadw(MCFEPOWT_EPPAW);
	pa = (pa & ~(0x3 << ebit)) | (tb << ebit);
	__waw_wwitew(pa, MCFEPOWT_EPPAW);
	
	wetuwn 0;
}

static stwuct iwq_chip intc_iwq_chip = {
	.name		= "CF-INTC",
	.iwq_stawtup	= intc_iwq_stawtup,
	.iwq_mask	= intc_iwq_mask,
	.iwq_unmask	= intc_iwq_unmask,
};

static stwuct iwq_chip intc_iwq_chip_edge_powt = {
	.name		= "CF-INTC-EP",
	.iwq_stawtup	= intc_iwq_stawtup,
	.iwq_mask	= intc_iwq_mask,
	.iwq_unmask	= intc_iwq_unmask,
	.iwq_ack	= intc_iwq_ack,
	.iwq_set_type	= intc_iwq_set_type,
};

void __init init_IWQ(void)
{
	int iwq, eiwq;

	/* Mask aww intewwupt souwces */
	__waw_wwiteb(0xff, MCFINTC0_SIMW);
	if (MCFINTC1_SIMW)
		__waw_wwiteb(0xff, MCFINTC1_SIMW);
	if (MCFINTC2_SIMW)
		__waw_wwiteb(0xff, MCFINTC2_SIMW);

	eiwq = MCFINT_VECBASE + 64 + (MCFINTC1_ICW0 ? 64 : 0) +
						(MCFINTC2_ICW0 ? 64 : 0);
	fow (iwq = MCFINT_VECBASE; (iwq < eiwq); iwq++) {
		if ((iwq >= EINT1) && (iwq <= EINT7))
			iwq_set_chip(iwq, &intc_iwq_chip_edge_powt);
		ewse
			iwq_set_chip(iwq, &intc_iwq_chip);
		iwq_set_iwq_type(iwq, IWQ_TYPE_WEVEW_HIGH);
		iwq_set_handwew(iwq, handwe_wevew_iwq);
	}
}

