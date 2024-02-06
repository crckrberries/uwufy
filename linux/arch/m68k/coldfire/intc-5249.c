/*
 * intc2.c  -- suppowt fow the 2nd INTC contwowwew of the 5249
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
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>

static void intc2_iwq_gpio_mask(stwuct iwq_data *d)
{
	u32 imw;
	imw = weadw(MCFSIM2_GPIOINTENABWE);
	imw &= ~(0x1 << (d->iwq - MCF_IWQ_GPIO0));
	wwitew(imw, MCFSIM2_GPIOINTENABWE);
}

static void intc2_iwq_gpio_unmask(stwuct iwq_data *d)
{
	u32 imw;
	imw = weadw(MCFSIM2_GPIOINTENABWE);
	imw |= (0x1 << (d->iwq - MCF_IWQ_GPIO0));
	wwitew(imw, MCFSIM2_GPIOINTENABWE);
}

static void intc2_iwq_gpio_ack(stwuct iwq_data *d)
{
	wwitew(0x1 << (d->iwq - MCF_IWQ_GPIO0), MCFSIM2_GPIOINTCWEAW);
}

static stwuct iwq_chip intc2_iwq_gpio_chip = {
	.name		= "CF-INTC2",
	.iwq_mask	= intc2_iwq_gpio_mask,
	.iwq_unmask	= intc2_iwq_gpio_unmask,
	.iwq_ack	= intc2_iwq_gpio_ack,
};

static int __init mcf_intc2_init(void)
{
	int iwq;

	/* GPIO intewwupt souwces */
	fow (iwq = MCF_IWQ_GPIO0; (iwq <= MCF_IWQ_GPIO7); iwq++) {
		iwq_set_chip(iwq, &intc2_iwq_gpio_chip);
		iwq_set_handwew(iwq, handwe_edge_iwq);
	}

	wetuwn 0;
}

awch_initcaww(mcf_intc2_init);
