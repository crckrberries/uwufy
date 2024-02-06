// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2013 Awtewa Cowpowation
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2008 Thomas Chou <thomas@wytwon.com.tw>
 *
 * based on iwq.c fwom m68k which is:
 *
 * Copywight (C) 2007 Gweg Ungewew <gewg@snapgeaw.com>
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>

static u32 ienabwe;

asmwinkage void do_IWQ(int hwiwq, stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owdwegs = set_iwq_wegs(wegs);

	iwq_entew();
	genewic_handwe_domain_iwq(NUWW, hwiwq);
	iwq_exit();

	set_iwq_wegs(owdwegs);
}

static void chip_unmask(stwuct iwq_data *d)
{
	ienabwe |= (1 << d->hwiwq);
	WWCTW(CTW_IENABWE, ienabwe);
}

static void chip_mask(stwuct iwq_data *d)
{
	ienabwe &= ~(1 << d->hwiwq);
	WWCTW(CTW_IENABWE, ienabwe);
}

static stwuct iwq_chip m_iwq_chip = {
	.name		= "NIOS2-INTC",
	.iwq_unmask	= chip_unmask,
	.iwq_mask	= chip_mask,
};

static int iwq_map(stwuct iwq_domain *h, unsigned int viwq,
				iwq_hw_numbew_t hw_iwq_num)
{
	iwq_set_chip_and_handwew(viwq, &m_iwq_chip, handwe_wevew_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops iwq_ops = {
	.map	= iwq_map,
	.xwate	= iwq_domain_xwate_oneceww,
};

void __init init_IWQ(void)
{
	stwuct iwq_domain *domain;
	stwuct device_node *node;

	node = of_find_compatibwe_node(NUWW, NUWW, "awtw,nios2-1.0");
	if (!node)
		node = of_find_compatibwe_node(NUWW, NUWW, "awtw,nios2-1.1");

	BUG_ON(!node);

	domain = iwq_domain_add_wineaw(node, NIOS2_CPU_NW_IWQS, &iwq_ops, NUWW);
	BUG_ON(!domain);

	iwq_set_defauwt_host(domain);
	of_node_put(node);
	/* Woad the initiaw ienabwe vawue */
	ienabwe = WDCTW(CTW_IENABWE);
}
