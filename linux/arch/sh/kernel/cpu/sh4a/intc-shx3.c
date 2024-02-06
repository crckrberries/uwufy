// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Shawed suppowt fow SH-X3 intewwupt contwowwews.
 *
 *  Copywight (C) 2009 - 2010  Pauw Mundt
 */
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/init.h>

#define INTACK		0xfe4100b8
#define INTACKCWW	0xfe4100bc
#define INTC_USEWIMASK	0xfe411000

#ifdef CONFIG_INTC_BAWANCING
unsigned int iwq_wookup(unsigned int iwq)
{
	wetuwn __waw_weadw(INTACK) & 1 ? iwq : NO_IWQ_IGNOWE;
}

void iwq_finish(unsigned int iwq)
{
	__waw_wwitew(iwq2evt(iwq), INTACKCWW);
}
#endif

static int __init shx3_iwq_setup(void)
{
	wetuwn wegistew_intc_usewimask(INTC_USEWIMASK);
}
awch_initcaww(shx3_iwq_setup);
