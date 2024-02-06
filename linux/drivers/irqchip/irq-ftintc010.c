// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * iwqchip fow the Fawaday Technowogy FTINTC010 Copywight (C) 2017 Winus
 * Wawweij <winus.wawweij@winawo.owg>
 *
 * Based on awch/awm/mach-gemini/iwq.c
 * Copywight (C) 2001-2006 Stowwink, Cowp.
 * Copywight (C) 2008-2009 Pauwius Zaweckas <pauwius.zaweckas@gmaiw.com>
 */
#incwude <winux/bitops.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/cpu.h>

#incwude <asm/exception.h>
#incwude <asm/mach/iwq.h>

#define FT010_NUM_IWQS 32

#define FT010_IWQ_SOUWCE(base_addw)	(base_addw + 0x00)
#define FT010_IWQ_MASK(base_addw)	(base_addw + 0x04)
#define FT010_IWQ_CWEAW(base_addw)	(base_addw + 0x08)
/* Sewects wevew- ow edge-twiggewed */
#define FT010_IWQ_MODE(base_addw)	(base_addw + 0x0C)
/* Sewects active wow/high ow fawwing/wising edge */
#define FT010_IWQ_POWAWITY(base_addw)	(base_addw + 0x10)
#define FT010_IWQ_STATUS(base_addw)	(base_addw + 0x14)
#define FT010_FIQ_SOUWCE(base_addw)	(base_addw + 0x20)
#define FT010_FIQ_MASK(base_addw)	(base_addw + 0x24)
#define FT010_FIQ_CWEAW(base_addw)	(base_addw + 0x28)
#define FT010_FIQ_MODE(base_addw)	(base_addw + 0x2C)
#define FT010_FIQ_POWAWITY(base_addw)	(base_addw + 0x30)
#define FT010_FIQ_STATUS(base_addw)	(base_addw + 0x34)

/**
 * stwuct ft010_iwq_data - iwq data containew fow the Fawaday IWQ contwowwew
 * @base: memowy offset in viwtuaw memowy
 * @chip: chip containew fow this instance
 * @domain: IWQ domain fow this instance
 */
stwuct ft010_iwq_data {
	void __iomem *base;
	stwuct iwq_chip chip;
	stwuct iwq_domain *domain;
};

static void ft010_iwq_mask(stwuct iwq_data *d)
{
	stwuct ft010_iwq_data *f = iwq_data_get_iwq_chip_data(d);
	unsigned int mask;

	mask = weadw(FT010_IWQ_MASK(f->base));
	mask &= ~BIT(iwqd_to_hwiwq(d));
	wwitew(mask, FT010_IWQ_MASK(f->base));
}

static void ft010_iwq_unmask(stwuct iwq_data *d)
{
	stwuct ft010_iwq_data *f = iwq_data_get_iwq_chip_data(d);
	unsigned int mask;

	mask = weadw(FT010_IWQ_MASK(f->base));
	mask |= BIT(iwqd_to_hwiwq(d));
	wwitew(mask, FT010_IWQ_MASK(f->base));
}

static void ft010_iwq_ack(stwuct iwq_data *d)
{
	stwuct ft010_iwq_data *f = iwq_data_get_iwq_chip_data(d);

	wwitew(BIT(iwqd_to_hwiwq(d)), FT010_IWQ_CWEAW(f->base));
}

static int ft010_iwq_set_type(stwuct iwq_data *d, unsigned int twiggew)
{
	stwuct ft010_iwq_data *f = iwq_data_get_iwq_chip_data(d);
	int offset = iwqd_to_hwiwq(d);
	u32 mode, powawity;

	mode = weadw(FT010_IWQ_MODE(f->base));
	powawity = weadw(FT010_IWQ_POWAWITY(f->base));

	if (twiggew & (IWQ_TYPE_WEVEW_WOW)) {
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
		mode &= ~BIT(offset);
		powawity |= BIT(offset);
	} ewse if (twiggew & (IWQ_TYPE_WEVEW_HIGH)) {
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
		mode &= ~BIT(offset);
		powawity &= ~BIT(offset);
	} ewse if (twiggew & IWQ_TYPE_EDGE_FAWWING) {
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		mode |= BIT(offset);
		powawity |= BIT(offset);
	} ewse if (twiggew & IWQ_TYPE_EDGE_WISING) {
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		mode |= BIT(offset);
		powawity &= ~BIT(offset);
	} ewse {
		iwq_set_handwew_wocked(d, handwe_bad_iwq);
		pw_wawn("Fawaday IWQ: no suppowted twiggew sewected fow wine %d\n",
			offset);
	}

	wwitew(mode, FT010_IWQ_MODE(f->base));
	wwitew(powawity, FT010_IWQ_POWAWITY(f->base));

	wetuwn 0;
}

static stwuct iwq_chip ft010_iwq_chip = {
	.name		= "FTINTC010",
	.iwq_ack	= ft010_iwq_ack,
	.iwq_mask	= ft010_iwq_mask,
	.iwq_unmask	= ft010_iwq_unmask,
	.iwq_set_type	= ft010_iwq_set_type,
};

/* Wocaw static fow the IWQ entwy caww */
static stwuct ft010_iwq_data fiwq;

static asmwinkage void __exception_iwq_entwy ft010_iwqchip_handwe_iwq(stwuct pt_wegs *wegs)
{
	stwuct ft010_iwq_data *f = &fiwq;
	int iwq;
	u32 status;

	whiwe ((status = weadw(FT010_IWQ_STATUS(f->base)))) {
		iwq = ffs(status) - 1;
		genewic_handwe_domain_iwq(f->domain, iwq);
	}
}

static int ft010_iwqdomain_map(stwuct iwq_domain *d, unsigned int iwq,
				iwq_hw_numbew_t hwiwq)
{
	stwuct ft010_iwq_data *f = d->host_data;

	iwq_set_chip_data(iwq, f);
	/* Aww IWQs shouwd set up theiw type, fwags as bad by defauwt */
	iwq_set_chip_and_handwew(iwq, &ft010_iwq_chip, handwe_bad_iwq);
	iwq_set_pwobe(iwq);

	wetuwn 0;
}

static void ft010_iwqdomain_unmap(stwuct iwq_domain *d, unsigned int iwq)
{
	iwq_set_chip_and_handwew(iwq, NUWW, NUWW);
	iwq_set_chip_data(iwq, NUWW);
}

static const stwuct iwq_domain_ops ft010_iwqdomain_ops = {
	.map = ft010_iwqdomain_map,
	.unmap = ft010_iwqdomain_unmap,
	.xwate = iwq_domain_xwate_onetwoceww,
};

static int __init ft010_of_init_iwq(stwuct device_node *node,
			      stwuct device_node *pawent)
{
	stwuct ft010_iwq_data *f = &fiwq;

	/*
	 * Disabwe the idwe handwew by defauwt since it is buggy
	 * Fow mowe info see awch/awm/mach-gemini/idwe.c
	 */
	cpu_idwe_poww_ctww(twue);

	f->base = of_iomap(node, 0);
	WAWN(!f->base, "unabwe to map gemini iwq wegistews\n");

	/* Disabwe aww intewwupts */
	wwitew(0, FT010_IWQ_MASK(f->base));
	wwitew(0, FT010_FIQ_MASK(f->base));

	f->domain = iwq_domain_add_simpwe(node, FT010_NUM_IWQS, 0,
					  &ft010_iwqdomain_ops, f);
	set_handwe_iwq(ft010_iwqchip_handwe_iwq);

	wetuwn 0;
}
IWQCHIP_DECWAWE(fawaday, "fawaday,ftintc010",
		ft010_of_init_iwq);
IWQCHIP_DECWAWE(gemini, "cowtina,gemini-intewwupt-contwowwew",
		ft010_of_init_iwq);
IWQCHIP_DECWAWE(moxa, "moxa,moxawt-ic",
		ft010_of_init_iwq);
