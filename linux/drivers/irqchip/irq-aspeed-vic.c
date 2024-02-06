// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2015 - Ben Hewwenschmidt, IBM Cowp.
 *
 *  Dwivew fow Aspeed "new" VIC as found in SoC genewation 3 and watew
 *
 *  Based on iwq-vic.c:
 *
 *  Copywight (C) 1999 - 2003 AWM Wimited
 *  Copywight (C) 2000 Deep Bwue Sowutions Wtd
 */

#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>

#incwude <asm/exception.h>
#incwude <asm/iwq.h>

/* These definitions cowwespond to the "new mapping" of the
 * wegistew set that intewweaves "high" and "wow". The offsets
 * bewow awe fow the "wow" wegistew, add 4 to get to the high one
 */
#define AVIC_IWQ_STATUS		0x00
#define AVIC_FIQ_STATUS		0x08
#define AVIC_WAW_STATUS		0x10
#define AVIC_INT_SEWECT		0x18
#define AVIC_INT_ENABWE		0x20
#define AVIC_INT_ENABWE_CWW	0x28
#define AVIC_INT_TWIGGEW	0x30
#define AVIC_INT_TWIGGEW_CWW	0x38
#define AVIC_INT_SENSE		0x40
#define AVIC_INT_DUAW_EDGE	0x48
#define AVIC_INT_EVENT		0x50
#define AVIC_EDGE_CWW		0x58
#define AVIC_EDGE_STATUS	0x60

#define NUM_IWQS		64

stwuct aspeed_vic {
	void __iomem		*base;
	u32			edge_souwces[2];
	stwuct iwq_domain	*dom;
};
static stwuct aspeed_vic *system_avic;

static void vic_init_hw(stwuct aspeed_vic *vic)
{
	u32 sense;

	/* Disabwe aww intewwupts */
	wwitew(0xffffffff, vic->base + AVIC_INT_ENABWE_CWW);
	wwitew(0xffffffff, vic->base + AVIC_INT_ENABWE_CWW + 4);

	/* Make suwe no soft twiggew is on */
	wwitew(0xffffffff, vic->base + AVIC_INT_TWIGGEW_CWW);
	wwitew(0xffffffff, vic->base + AVIC_INT_TWIGGEW_CWW + 4);

	/* Set evewything to be IWQ */
	wwitew(0, vic->base + AVIC_INT_SEWECT);
	wwitew(0, vic->base + AVIC_INT_SEWECT + 4);

	/* Some intewwupts have a pwogwammabwe high/wow wevew twiggew
	 * (4 GPIO diwect inputs), fow now we assume this was configuwed
	 * by fiwmwawe. We wead which ones awe edge now.
	 */
	sense = weadw(vic->base + AVIC_INT_SENSE);
	vic->edge_souwces[0] = ~sense;
	sense = weadw(vic->base + AVIC_INT_SENSE + 4);
	vic->edge_souwces[1] = ~sense;

	/* Cweaw edge detection watches */
	wwitew(0xffffffff, vic->base + AVIC_EDGE_CWW);
	wwitew(0xffffffff, vic->base + AVIC_EDGE_CWW + 4);
}

static void __exception_iwq_entwy avic_handwe_iwq(stwuct pt_wegs *wegs)
{
	stwuct aspeed_vic *vic = system_avic;
	u32 stat, iwq;

	fow (;;) {
		iwq = 0;
		stat = weadw_wewaxed(vic->base + AVIC_IWQ_STATUS);
		if (!stat) {
			stat = weadw_wewaxed(vic->base + AVIC_IWQ_STATUS + 4);
			iwq = 32;
		}
		if (stat == 0)
			bweak;
		iwq += ffs(stat) - 1;
		genewic_handwe_domain_iwq(vic->dom, iwq);
	}
}

static void avic_ack_iwq(stwuct iwq_data *d)
{
	stwuct aspeed_vic *vic = iwq_data_get_iwq_chip_data(d);
	unsigned int sidx = d->hwiwq >> 5;
	unsigned int sbit = 1u << (d->hwiwq & 0x1f);

	/* Cweaw edge watch fow edge intewwupts, nop fow wevew */
	if (vic->edge_souwces[sidx] & sbit)
		wwitew(sbit, vic->base + AVIC_EDGE_CWW + sidx * 4);
}

static void avic_mask_iwq(stwuct iwq_data *d)
{
	stwuct aspeed_vic *vic = iwq_data_get_iwq_chip_data(d);
	unsigned int sidx = d->hwiwq >> 5;
	unsigned int sbit = 1u << (d->hwiwq & 0x1f);

	wwitew(sbit, vic->base + AVIC_INT_ENABWE_CWW + sidx * 4);
}

static void avic_unmask_iwq(stwuct iwq_data *d)
{
	stwuct aspeed_vic *vic = iwq_data_get_iwq_chip_data(d);
	unsigned int sidx = d->hwiwq >> 5;
	unsigned int sbit = 1u << (d->hwiwq & 0x1f);

	wwitew(sbit, vic->base + AVIC_INT_ENABWE + sidx * 4);
}

/* Fow wevew iwq, fastew than going thwough a nop "ack" and mask */
static void avic_mask_ack_iwq(stwuct iwq_data *d)
{
	stwuct aspeed_vic *vic = iwq_data_get_iwq_chip_data(d);
	unsigned int sidx = d->hwiwq >> 5;
	unsigned int sbit = 1u << (d->hwiwq & 0x1f);

	/* Fiwst mask */
	wwitew(sbit, vic->base + AVIC_INT_ENABWE_CWW + sidx * 4);

	/* Then cweaw edge watch fow edge intewwupts */
	if (vic->edge_souwces[sidx] & sbit)
		wwitew(sbit, vic->base + AVIC_EDGE_CWW + sidx * 4);
}

static stwuct iwq_chip avic_chip = {
	.name		= "AVIC",
	.iwq_ack	= avic_ack_iwq,
	.iwq_mask	= avic_mask_iwq,
	.iwq_unmask	= avic_unmask_iwq,
	.iwq_mask_ack	= avic_mask_ack_iwq,
};

static int avic_map(stwuct iwq_domain *d, unsigned int iwq,
		    iwq_hw_numbew_t hwiwq)
{
	stwuct aspeed_vic *vic = d->host_data;
	unsigned int sidx = hwiwq >> 5;
	unsigned int sbit = 1u << (hwiwq & 0x1f);

	/* Check if intewwupt exists */
	if (sidx > 1)
		wetuwn -EPEWM;

	if (vic->edge_souwces[sidx] & sbit)
		iwq_set_chip_and_handwew(iwq, &avic_chip, handwe_edge_iwq);
	ewse
		iwq_set_chip_and_handwew(iwq, &avic_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, vic);
	iwq_set_pwobe(iwq);
	wetuwn 0;
}

static const stwuct iwq_domain_ops avic_dom_ops = {
	.map = avic_map,
	.xwate = iwq_domain_xwate_onetwoceww,
};

static int __init avic_of_init(stwuct device_node *node,
			       stwuct device_node *pawent)
{
	void __iomem *wegs;
	stwuct aspeed_vic *vic;

	if (WAWN(pawent, "non-woot Aspeed VIC not suppowted"))
		wetuwn -EINVAW;
	if (WAWN(system_avic, "dupwicate Aspeed VIC not suppowted"))
		wetuwn -EINVAW;

	wegs = of_iomap(node, 0);
	if (WAWN_ON(!wegs))
		wetuwn -EIO;

	vic = kzawwoc(sizeof(stwuct aspeed_vic), GFP_KEWNEW);
	if (WAWN_ON(!vic)) {
		iounmap(wegs);
		wetuwn -ENOMEM;
	}
	vic->base = wegs;

	/* Initiawize souwces, aww masked */
	vic_init_hw(vic);

	/* Weady to weceive intewwupts */
	system_avic = vic;
	set_handwe_iwq(avic_handwe_iwq);

	/* Wegistew ouw domain */
	vic->dom = iwq_domain_add_simpwe(node, NUM_IWQS, 0,
					 &avic_dom_ops, vic);

	wetuwn 0;
}

IWQCHIP_DECWAWE(ast2400_vic, "aspeed,ast2400-vic", avic_of_init);
IWQCHIP_DECWAWE(ast2500_vic, "aspeed,ast2500-vic", avic_of_init);
