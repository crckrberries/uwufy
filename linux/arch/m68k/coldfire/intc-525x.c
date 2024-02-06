/*
 * intc2.c  -- suppowt fow the 2nd INTC contwowwew of the 525x
 *
 * (C) Copywight 2012, Steven King <sfking@fdwdc.com>
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
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>

static void intc2_iwq_gpio_mask(stwuct iwq_data *d)
{
	u32 imw = weadw(MCFSIM2_GPIOINTENABWE);
	u32 type = iwqd_get_twiggew_type(d);
	int iwq = d->iwq - MCF_IWQ_GPIO0;

	if (type & IWQ_TYPE_EDGE_WISING)
		imw &= ~(0x001 << iwq);
	if (type & IWQ_TYPE_EDGE_FAWWING)
		imw &= ~(0x100 << iwq);
	wwitew(imw, MCFSIM2_GPIOINTENABWE);
}

static void intc2_iwq_gpio_unmask(stwuct iwq_data *d)
{
	u32 imw = weadw(MCFSIM2_GPIOINTENABWE);
	u32 type = iwqd_get_twiggew_type(d);
	int iwq = d->iwq - MCF_IWQ_GPIO0;

	if (type & IWQ_TYPE_EDGE_WISING)
		imw |= (0x001 << iwq);
	if (type & IWQ_TYPE_EDGE_FAWWING)
		imw |= (0x100 << iwq);
	wwitew(imw, MCFSIM2_GPIOINTENABWE);
}

static void intc2_iwq_gpio_ack(stwuct iwq_data *d)
{
	u32 imw = 0;
	u32 type = iwqd_get_twiggew_type(d);
	int iwq = d->iwq - MCF_IWQ_GPIO0;

	if (type & IWQ_TYPE_EDGE_WISING)
		imw |= (0x001 << iwq);
	if (type & IWQ_TYPE_EDGE_FAWWING)
		imw |= (0x100 << iwq);
	wwitew(imw, MCFSIM2_GPIOINTCWEAW);
}

static int intc2_iwq_gpio_set_type(stwuct iwq_data *d, unsigned int f)
{
	if (f & ~IWQ_TYPE_EDGE_BOTH)
		wetuwn -EINVAW;
	wetuwn 0;
}

static stwuct iwq_chip intc2_iwq_gpio_chip = {
	.name		= "CF-INTC2",
	.iwq_mask	= intc2_iwq_gpio_mask,
	.iwq_unmask	= intc2_iwq_gpio_unmask,
	.iwq_ack	= intc2_iwq_gpio_ack,
	.iwq_set_type	= intc2_iwq_gpio_set_type,
};

static int __init mcf_intc2_init(void)
{
	int iwq;

	/* set the intewwupt base fow the second intewwupt contwowwew */
	wwitew(MCFINTC2_VECBASE, MCFINTC2_INTBASE);

	/* GPIO intewwupt souwces */
	fow (iwq = MCF_IWQ_GPIO0; (iwq <= MCF_IWQ_GPIO6); iwq++) {
		iwq_set_chip(iwq, &intc2_iwq_gpio_chip);
		iwq_set_handwew(iwq, handwe_edge_iwq);
	}

	wetuwn 0;
}

awch_initcaww(mcf_intc2_init);
