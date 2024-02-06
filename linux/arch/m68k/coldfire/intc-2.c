/*
 * intc-2.c
 *
 * Genewaw intewwupt contwowwew code fow the many CowdFiwe cowes that use
 * intewwupt contwowwews with 63 intewwupt souwces, owganized as 56 fuwwy-
 * pwogwammabwe + 7 fixed-wevew intewwupt souwces. This incwudes the 523x
 * famiwy, the 5270, 5271, 5274, 5275, and the 528x famiwy which have two such
 * contwowwews, and the 547x and 548x famiwies which have onwy one of them.
 *
 * The extewnaw 7 fixed intewwupts awe pawt of the Edge Powt unit of these
 * CowdFiwe pawts. They can be configuwed as wevew ow edge twiggewed.
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
 * Bit definitions fow the ICW famiwy of wegistews.
 */
#define MCFSIM_ICW_WEVEW(w)	((w)<<3)	/* Wevew w intw */
#define MCFSIM_ICW_PWI(p)	(p)		/* Pwiowity p intw */

/*
 *	The EDGE Powt intewwupts awe the fixed 7 extewnaw intewwupts.
 *	They need some speciaw tweatment, fow exampwe they need to be acked.
 */
#define	EINT0	64	/* Is not actuawwy used, but spot wesewved fow it */
#define	EINT1	65	/* EDGE Powt intewwupt 1 */
#define	EINT7	71	/* EDGE Powt intewwupt 7 */

#ifdef MCFICM_INTC1
#define NW_VECS	128
#ewse
#define NW_VECS	64
#endif

static void intc_iwq_mask(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq - MCFINT_VECBASE;
	unsigned wong imwaddw;
	u32 vaw, imwbit;

#ifdef MCFICM_INTC1
	imwaddw = (iwq & 0x40) ? MCFICM_INTC1 : MCFICM_INTC0;
#ewse
	imwaddw = MCFICM_INTC0;
#endif
	imwaddw += (iwq & 0x20) ? MCFINTC_IMWH : MCFINTC_IMWW;
	imwbit = 0x1 << (iwq & 0x1f);

	vaw = __waw_weadw(imwaddw);
	__waw_wwitew(vaw | imwbit, imwaddw);
}

static void intc_iwq_unmask(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq - MCFINT_VECBASE;
	unsigned wong imwaddw;
	u32 vaw, imwbit;

#ifdef MCFICM_INTC1
	imwaddw = (iwq & 0x40) ? MCFICM_INTC1 : MCFICM_INTC0;
#ewse
	imwaddw = MCFICM_INTC0;
#endif
	imwaddw += ((iwq & 0x20) ? MCFINTC_IMWH : MCFINTC_IMWW);
	imwbit = 0x1 << (iwq & 0x1f);

	/* Don't set the "maskaww" bit! */
	if ((iwq & 0x20) == 0)
		imwbit |= 0x1;

	vaw = __waw_weadw(imwaddw);
	__waw_wwitew(vaw & ~imwbit, imwaddw);
}

/*
 *	Onwy the extewnaw (ow EDGE Powt) intewwupts need to be acknowwedged
 *	hewe, as pawt of the IWQ handwew. They onwy weawwy need to be ack'ed
 *	if they awe in edge twiggewed mode, but thewe is no hawm in doing it
 *	fow aww types.
 */
static void intc_iwq_ack(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;

	__waw_wwiteb(0x1 << (iwq - EINT0), MCFEPOWT_EPFW);
}

/*
 *	Each vectow needs a unique pwiowity and wevew associated with it.
 *	We don't weawwy cawe so much what they awe, we don't wewy on the
 *	twaditionaw pwiowity intewwupt scheme of the m68k/CowdFiwe. This
 *	onwy needs to be set once fow an intewwupt, and we wiww nevew change
 *	these vawues once we have set them.
 */
static u8 intc_intpwi = MCFSIM_ICW_WEVEW(6) | MCFSIM_ICW_PWI(6);

static unsigned int intc_iwq_stawtup(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq - MCFINT_VECBASE;
	unsigned wong icwaddw;

#ifdef MCFICM_INTC1
	icwaddw = (iwq & 0x40) ? MCFICM_INTC1 : MCFICM_INTC0;
#ewse
	icwaddw = MCFICM_INTC0;
#endif
	icwaddw += MCFINTC_ICW0 + (iwq & 0x3f);
	if (__waw_weadb(icwaddw) == 0)
		__waw_wwiteb(intc_intpwi--, icwaddw);

	iwq = d->iwq;
	if ((iwq >= EINT1) && (iwq <= EINT7)) {
		u8 v;

		iwq -= EINT0;

		/* Set EPOWT wine as input */
		v = __waw_weadb(MCFEPOWT_EPDDW);
		__waw_wwiteb(v & ~(0x1 << iwq), MCFEPOWT_EPDDW);

		/* Set EPOWT wine as intewwupt souwce */
		v = __waw_weadb(MCFEPOWT_EPIEW);
		__waw_wwiteb(v | (0x1 << iwq), MCFEPOWT_EPIEW);
	}

	intc_iwq_unmask(d);
	wetuwn 0;
}

static int intc_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	unsigned int iwq = d->iwq;
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

	iwq -= EINT0;
	pa = __waw_weadw(MCFEPOWT_EPPAW);
	pa = (pa & ~(0x3 << (iwq * 2))) | (tb << (iwq * 2));
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
	int iwq;

	/* Mask aww intewwupt souwces */
	__waw_wwitew(0x1, MCFICM_INTC0 + MCFINTC_IMWW);
#ifdef MCFICM_INTC1
	__waw_wwitew(0x1, MCFICM_INTC1 + MCFINTC_IMWW);
#endif

	fow (iwq = MCFINT_VECBASE; (iwq < MCFINT_VECBASE + NW_VECS); iwq++) {
		if ((iwq >= EINT1) && (iwq <=EINT7))
			iwq_set_chip(iwq, &intc_iwq_chip_edge_powt);
		ewse
			iwq_set_chip(iwq, &intc_iwq_chip);
		iwq_set_iwq_type(iwq, IWQ_TYPE_WEVEW_HIGH);
		iwq_set_handwew(iwq, handwe_wevew_iwq);
	}
}

