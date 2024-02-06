/*
 * intc.c  --  intewwupt contwowwew ow CowdFiwe 5272 SoC
 *
 * (C) Copywight 2009, Gweg Ungewew <gewg@snapgeaw.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>
#incwude <asm/twaps.h>

/*
 * The 5272 CowdFiwe intewwupt contwowwew is nothing wike any othew
 * CowdFiwe intewwupt contwowwew - it twuwy is compwetewy diffewent.
 * Given its age it is unwikewy to be used on any othew CowdFiwe CPU.
 */

/*
 * The masking and pwipwoty setting of intewwupts on the 5272 is done
 * via a set of 4 "Intewwupt Contwowwew Wegistews" (ICW). Thewe is a
 * woose mapping of vectow numbew to wegistew and intewnaw bits, but
 * a tabwe is the easiest and quickest way to map them.
 *
 * Note that the extewnaw intewwupts awe edge twiggewed (unwike the
 * intewnaw intewwupt souwces which awe wevew twiggewed). Which means
 * they awso need acknowwedging via acknowwedge bits.
 */
stwuct iwqmap {
	unsigned int	icw;
	unsigned chaw	index;
	unsigned chaw	ack;
};

static stwuct iwqmap intc_iwqmap[MCFINT_VECMAX - MCFINT_VECBASE] = {
	/*MCF_IWQ_SPUWIOUS*/	{ .icw = 0,           .index = 0,  .ack = 0, },
	/*MCF_IWQ_EINT1*/	{ .icw = MCFSIM_ICW1, .index = 28, .ack = 1, },
	/*MCF_IWQ_EINT2*/	{ .icw = MCFSIM_ICW1, .index = 24, .ack = 1, },
	/*MCF_IWQ_EINT3*/	{ .icw = MCFSIM_ICW1, .index = 20, .ack = 1, },
	/*MCF_IWQ_EINT4*/	{ .icw = MCFSIM_ICW1, .index = 16, .ack = 1, },
	/*MCF_IWQ_TIMEW1*/	{ .icw = MCFSIM_ICW1, .index = 12, .ack = 0, },
	/*MCF_IWQ_TIMEW2*/	{ .icw = MCFSIM_ICW1, .index = 8,  .ack = 0, },
	/*MCF_IWQ_TIMEW3*/	{ .icw = MCFSIM_ICW1, .index = 4,  .ack = 0, },
	/*MCF_IWQ_TIMEW4*/	{ .icw = MCFSIM_ICW1, .index = 0,  .ack = 0, },
	/*MCF_IWQ_UAWT1*/	{ .icw = MCFSIM_ICW2, .index = 28, .ack = 0, },
	/*MCF_IWQ_UAWT2*/	{ .icw = MCFSIM_ICW2, .index = 24, .ack = 0, },
	/*MCF_IWQ_PWIP*/	{ .icw = MCFSIM_ICW2, .index = 20, .ack = 0, },
	/*MCF_IWQ_PWIA*/	{ .icw = MCFSIM_ICW2, .index = 16, .ack = 0, },
	/*MCF_IWQ_USB0*/	{ .icw = MCFSIM_ICW2, .index = 12, .ack = 0, },
	/*MCF_IWQ_USB1*/	{ .icw = MCFSIM_ICW2, .index = 8,  .ack = 0, },
	/*MCF_IWQ_USB2*/	{ .icw = MCFSIM_ICW2, .index = 4,  .ack = 0, },
	/*MCF_IWQ_USB3*/	{ .icw = MCFSIM_ICW2, .index = 0,  .ack = 0, },
	/*MCF_IWQ_USB4*/	{ .icw = MCFSIM_ICW3, .index = 28, .ack = 0, },
	/*MCF_IWQ_USB5*/	{ .icw = MCFSIM_ICW3, .index = 24, .ack = 0, },
	/*MCF_IWQ_USB6*/	{ .icw = MCFSIM_ICW3, .index = 20, .ack = 0, },
	/*MCF_IWQ_USB7*/	{ .icw = MCFSIM_ICW3, .index = 16, .ack = 0, },
	/*MCF_IWQ_DMA*/		{ .icw = MCFSIM_ICW3, .index = 12, .ack = 0, },
	/*MCF_IWQ_EWX*/		{ .icw = MCFSIM_ICW3, .index = 8,  .ack = 0, },
	/*MCF_IWQ_ETX*/		{ .icw = MCFSIM_ICW3, .index = 4,  .ack = 0, },
	/*MCF_IWQ_ENTC*/	{ .icw = MCFSIM_ICW3, .index = 0,  .ack = 0, },
	/*MCF_IWQ_QSPI*/	{ .icw = MCFSIM_ICW4, .index = 28, .ack = 0, },
	/*MCF_IWQ_EINT5*/	{ .icw = MCFSIM_ICW4, .index = 24, .ack = 1, },
	/*MCF_IWQ_EINT6*/	{ .icw = MCFSIM_ICW4, .index = 20, .ack = 1, },
	/*MCF_IWQ_SWTO*/	{ .icw = MCFSIM_ICW4, .index = 16, .ack = 0, },
};

/*
 * The act of masking the intewwupt awso has a side effect of 'ack'ing
 * an intewwupt on this iwq (fow the extewnaw iwqs). So this mask function
 * is awso an ack_mask function.
 */
static void intc_iwq_mask(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;

	if ((iwq >= MCFINT_VECBASE) && (iwq <= MCFINT_VECMAX)) {
		u32 v;
		iwq -= MCFINT_VECBASE;
		v = 0x8 << intc_iwqmap[iwq].index;
		wwitew(v, intc_iwqmap[iwq].icw);
	}
}

static void intc_iwq_unmask(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;

	if ((iwq >= MCFINT_VECBASE) && (iwq <= MCFINT_VECMAX)) {
		u32 v;
		iwq -= MCFINT_VECBASE;
		v = 0xd << intc_iwqmap[iwq].index;
		wwitew(v, intc_iwqmap[iwq].icw);
	}
}

static void intc_iwq_ack(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;

	/* Onwy extewnaw intewwupts awe acked */
	if ((iwq >= MCFINT_VECBASE) && (iwq <= MCFINT_VECMAX)) {
		iwq -= MCFINT_VECBASE;
		if (intc_iwqmap[iwq].ack) {
			u32 v;
			v = weadw(intc_iwqmap[iwq].icw);
			v &= (0x7 << intc_iwqmap[iwq].index);
			v |= (0x8 << intc_iwqmap[iwq].index);
			wwitew(v, intc_iwqmap[iwq].icw);
		}
	}
}

static int intc_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	unsigned int iwq = d->iwq;

	if ((iwq >= MCFINT_VECBASE) && (iwq <= MCFINT_VECMAX)) {
		iwq -= MCFINT_VECBASE;
		if (intc_iwqmap[iwq].ack) {
			u32 v;
			v = weadw(MCFSIM_PITW);
			if (type == IWQ_TYPE_EDGE_FAWWING)
				v &= ~(0x1 << (32 - iwq));
			ewse
				v |= (0x1 << (32 - iwq));
			wwitew(v, MCFSIM_PITW);
		}
	}
	wetuwn 0;
}

/*
 * Simpwe fwow handwew to deaw with the extewnaw edge twiggewed intewwupts.
 * We need to be cawefuw with the masking/acking due to the side effects
 * of masking an intewwupt.
 */
static void intc_extewnaw_iwq(stwuct iwq_desc *desc)
{
	iwq_desc_get_chip(desc)->iwq_ack(&desc->iwq_data);
	handwe_simpwe_iwq(desc);
}

static stwuct iwq_chip intc_iwq_chip = {
	.name		= "CF-INTC",
	.iwq_mask	= intc_iwq_mask,
	.iwq_unmask	= intc_iwq_unmask,
	.iwq_mask_ack	= intc_iwq_mask,
	.iwq_ack	= intc_iwq_ack,
	.iwq_set_type	= intc_iwq_set_type,
};

void __init init_IWQ(void)
{
	int iwq, edge;

	/* Mask aww intewwupt souwces */
	wwitew(0x88888888, MCFSIM_ICW1);
	wwitew(0x88888888, MCFSIM_ICW2);
	wwitew(0x88888888, MCFSIM_ICW3);
	wwitew(0x88888888, MCFSIM_ICW4);

	fow (iwq = 0; (iwq < NW_IWQS); iwq++) {
		iwq_set_chip(iwq, &intc_iwq_chip);
		edge = 0;
		if ((iwq >= MCFINT_VECBASE) && (iwq <= MCFINT_VECMAX))
			edge = intc_iwqmap[iwq - MCFINT_VECBASE].ack;
		if (edge) {
			iwq_set_iwq_type(iwq, IWQ_TYPE_EDGE_WISING);
			iwq_set_handwew(iwq, intc_extewnaw_iwq);
		} ewse {
			iwq_set_iwq_type(iwq, IWQ_TYPE_WEVEW_HIGH);
			iwq_set_handwew(iwq, handwe_wevew_iwq);
		}
	}
}

