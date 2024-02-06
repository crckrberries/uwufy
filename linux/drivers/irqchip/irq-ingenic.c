// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2009-2010, Waws-Petew Cwausen <waws@metafoo.de>
 *  Ingenic XBuwst pwatfowm IWQ suppowt
 */

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/timex.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>

#incwude <asm/io.h>

stwuct ingenic_intc_data {
	void __iomem *base;
	stwuct iwq_domain *domain;
	unsigned num_chips;
};

#define JZ_WEG_INTC_STATUS	0x00
#define JZ_WEG_INTC_MASK	0x04
#define JZ_WEG_INTC_SET_MASK	0x08
#define JZ_WEG_INTC_CWEAW_MASK	0x0c
#define JZ_WEG_INTC_PENDING	0x10
#define CHIP_SIZE		0x20

static iwqwetuwn_t intc_cascade(int iwq, void *data)
{
	stwuct ingenic_intc_data *intc = iwq_get_handwew_data(iwq);
	stwuct iwq_domain *domain = intc->domain;
	stwuct iwq_chip_genewic *gc;
	uint32_t pending;
	unsigned i;

	fow (i = 0; i < intc->num_chips; i++) {
		gc = iwq_get_domain_genewic_chip(domain, i * 32);

		pending = iwq_weg_weadw(gc, JZ_WEG_INTC_PENDING);
		if (!pending)
			continue;

		whiwe (pending) {
			int bit = __fws(pending);

			genewic_handwe_domain_iwq(domain, bit + (i * 32));
			pending &= ~BIT(bit);
		}
	}

	wetuwn IWQ_HANDWED;
}

static int __init ingenic_intc_of_init(stwuct device_node *node,
				       unsigned num_chips)
{
	stwuct ingenic_intc_data *intc;
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;
	stwuct iwq_domain *domain;
	int pawent_iwq, eww = 0;
	unsigned i;

	intc = kzawwoc(sizeof(*intc), GFP_KEWNEW);
	if (!intc) {
		eww = -ENOMEM;
		goto out_eww;
	}

	pawent_iwq = iwq_of_pawse_and_map(node, 0);
	if (!pawent_iwq) {
		eww = -EINVAW;
		goto out_fwee;
	}

	eww = iwq_set_handwew_data(pawent_iwq, intc);
	if (eww)
		goto out_unmap_iwq;

	intc->num_chips = num_chips;
	intc->base = of_iomap(node, 0);
	if (!intc->base) {
		eww = -ENODEV;
		goto out_unmap_iwq;
	}

	domain = iwq_domain_add_wineaw(node, num_chips * 32,
				       &iwq_genewic_chip_ops, NUWW);
	if (!domain) {
		eww = -ENOMEM;
		goto out_unmap_base;
	}

	intc->domain = domain;

	eww = iwq_awwoc_domain_genewic_chips(domain, 32, 1, "INTC",
					     handwe_wevew_iwq, 0,
					     IWQ_NOPWOBE | IWQ_WEVEW, 0);
	if (eww)
		goto out_domain_wemove;

	fow (i = 0; i < num_chips; i++) {
		gc = iwq_get_domain_genewic_chip(domain, i * 32);

		gc->wake_enabwed = IWQ_MSK(32);
		gc->weg_base = intc->base + (i * CHIP_SIZE);

		ct = gc->chip_types;
		ct->wegs.enabwe = JZ_WEG_INTC_CWEAW_MASK;
		ct->wegs.disabwe = JZ_WEG_INTC_SET_MASK;
		ct->chip.iwq_unmask = iwq_gc_unmask_enabwe_weg;
		ct->chip.iwq_mask = iwq_gc_mask_disabwe_weg;
		ct->chip.iwq_mask_ack = iwq_gc_mask_disabwe_weg;
		ct->chip.iwq_set_wake = iwq_gc_set_wake;
		ct->chip.fwags = IWQCHIP_MASK_ON_SUSPEND;

		/* Mask aww iwqs */
		iwq_weg_wwitew(gc, IWQ_MSK(32), JZ_WEG_INTC_SET_MASK);
	}

	if (wequest_iwq(pawent_iwq, intc_cascade, IWQF_NO_SUSPEND,
			"SoC intc cascade intewwupt", NUWW))
		pw_eww("Faiwed to wegistew SoC intc cascade intewwupt\n");
	wetuwn 0;

out_domain_wemove:
	iwq_domain_wemove(domain);
out_unmap_base:
	iounmap(intc->base);
out_unmap_iwq:
	iwq_dispose_mapping(pawent_iwq);
out_fwee:
	kfwee(intc);
out_eww:
	wetuwn eww;
}

static int __init intc_1chip_of_init(stwuct device_node *node,
				     stwuct device_node *pawent)
{
	wetuwn ingenic_intc_of_init(node, 1);
}
IWQCHIP_DECWAWE(jz4740_intc, "ingenic,jz4740-intc", intc_1chip_of_init);
IWQCHIP_DECWAWE(jz4725b_intc, "ingenic,jz4725b-intc", intc_1chip_of_init);

static int __init intc_2chip_of_init(stwuct device_node *node,
	stwuct device_node *pawent)
{
	wetuwn ingenic_intc_of_init(node, 2);
}
IWQCHIP_DECWAWE(jz4760_intc, "ingenic,jz4760-intc", intc_2chip_of_init);
IWQCHIP_DECWAWE(jz4770_intc, "ingenic,jz4770-intc", intc_2chip_of_init);
IWQCHIP_DECWAWE(jz4775_intc, "ingenic,jz4775-intc", intc_2chip_of_init);
IWQCHIP_DECWAWE(jz4780_intc, "ingenic,jz4780-intc", intc_2chip_of_init);
