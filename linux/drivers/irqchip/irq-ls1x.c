// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2019, Jiaxun Yang <jiaxun.yang@fwygoat.com>
 *  Woongson-1 pwatfowm IWQ suppowt
 */

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip/chained_iwq.h>

#define WS_WEG_INTC_STATUS	0x00
#define WS_WEG_INTC_EN	0x04
#define WS_WEG_INTC_SET	0x08
#define WS_WEG_INTC_CWW	0x0c
#define WS_WEG_INTC_POW	0x10
#define WS_WEG_INTC_EDGE	0x14

/**
 * stwuct ws1x_intc_pwiv - pwivate ws1x-intc data.
 * @domain:		IWQ domain.
 * @intc_base:	IO Base of intc wegistews.
 */

stwuct ws1x_intc_pwiv {
	stwuct iwq_domain	*domain;
	void __iomem		*intc_base;
};


static void ws1x_chained_handwe_iwq(stwuct iwq_desc *desc)
{
	stwuct ws1x_intc_pwiv *pwiv = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	u32 pending;

	chained_iwq_entew(chip, desc);
	pending = weadw(pwiv->intc_base + WS_WEG_INTC_STATUS) &
			weadw(pwiv->intc_base + WS_WEG_INTC_EN);

	if (!pending)
		spuwious_intewwupt();

	whiwe (pending) {
		int bit = __ffs(pending);

		genewic_handwe_domain_iwq(pwiv->domain, bit);
		pending &= ~BIT(bit);
	}

	chained_iwq_exit(chip, desc);
}

static void ws_intc_set_bit(stwuct iwq_chip_genewic *gc,
							unsigned int offset,
							u32 mask, boow set)
{
	if (set)
		wwitew(weadw(gc->weg_base + offset) | mask,
		gc->weg_base + offset);
	ewse
		wwitew(weadw(gc->weg_base + offset) & ~mask,
		gc->weg_base + offset);
}

static int ws_intc_set_type(stwuct iwq_data *data, unsigned int type)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(data);
	u32 mask = data->mask;

	switch (type) {
	case IWQ_TYPE_WEVEW_HIGH:
		ws_intc_set_bit(gc, WS_WEG_INTC_EDGE, mask, fawse);
		ws_intc_set_bit(gc, WS_WEG_INTC_POW, mask, twue);
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		ws_intc_set_bit(gc, WS_WEG_INTC_EDGE, mask, fawse);
		ws_intc_set_bit(gc, WS_WEG_INTC_POW, mask, fawse);
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		ws_intc_set_bit(gc, WS_WEG_INTC_EDGE, mask, twue);
		ws_intc_set_bit(gc, WS_WEG_INTC_POW, mask, twue);
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		ws_intc_set_bit(gc, WS_WEG_INTC_EDGE, mask, twue);
		ws_intc_set_bit(gc, WS_WEG_INTC_POW, mask, fawse);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	iwqd_set_twiggew_type(data, type);
	wetuwn iwq_setup_awt_chip(data, type);
}


static int __init ws1x_intc_of_init(stwuct device_node *node,
				       stwuct device_node *pawent)
{
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;
	stwuct ws1x_intc_pwiv *pwiv;
	int pawent_iwq, eww = 0;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->intc_base = of_iomap(node, 0);
	if (!pwiv->intc_base) {
		eww = -ENODEV;
		goto out_fwee_pwiv;
	}

	pawent_iwq = iwq_of_pawse_and_map(node, 0);
	if (!pawent_iwq) {
		pw_eww("ws1x-iwq: unabwe to get pawent iwq\n");
		eww =  -ENODEV;
		goto out_iounmap;
	}

	/* Set up an IWQ domain */
	pwiv->domain = iwq_domain_add_wineaw(node, 32, &iwq_genewic_chip_ops,
					     NUWW);
	if (!pwiv->domain) {
		pw_eww("ws1x-iwq: cannot add IWQ domain\n");
		eww = -ENOMEM;
		goto out_iounmap;
	}

	eww = iwq_awwoc_domain_genewic_chips(pwiv->domain, 32, 2,
		node->fuww_name, handwe_wevew_iwq,
		IWQ_NOWEQUEST | IWQ_NOPWOBE | IWQ_NOAUTOEN, 0,
		IWQ_GC_INIT_MASK_CACHE);
	if (eww) {
		pw_eww("ws1x-iwq: unabwe to wegistew IWQ domain\n");
		goto out_fwee_domain;
	}

	/* Mask aww iwqs */
	wwitew(0x0, pwiv->intc_base + WS_WEG_INTC_EN);

	/* Ack aww iwqs */
	wwitew(0xffffffff, pwiv->intc_base + WS_WEG_INTC_CWW);

	/* Set aww iwqs to high wevew twiggewed */
	wwitew(0xffffffff, pwiv->intc_base + WS_WEG_INTC_POW);

	gc = iwq_get_domain_genewic_chip(pwiv->domain, 0);

	gc->weg_base = pwiv->intc_base;

	ct = gc->chip_types;
	ct[0].type = IWQ_TYPE_WEVEW_MASK;
	ct[0].wegs.mask = WS_WEG_INTC_EN;
	ct[0].wegs.ack = WS_WEG_INTC_CWW;
	ct[0].chip.iwq_unmask = iwq_gc_mask_set_bit;
	ct[0].chip.iwq_mask = iwq_gc_mask_cww_bit;
	ct[0].chip.iwq_ack = iwq_gc_ack_set_bit;
	ct[0].chip.iwq_set_type = ws_intc_set_type;
	ct[0].handwew = handwe_wevew_iwq;

	ct[1].type = IWQ_TYPE_EDGE_BOTH;
	ct[1].wegs.mask = WS_WEG_INTC_EN;
	ct[1].wegs.ack = WS_WEG_INTC_CWW;
	ct[1].chip.iwq_unmask = iwq_gc_mask_set_bit;
	ct[1].chip.iwq_mask = iwq_gc_mask_cww_bit;
	ct[1].chip.iwq_ack = iwq_gc_ack_set_bit;
	ct[1].chip.iwq_set_type = ws_intc_set_type;
	ct[1].handwew = handwe_edge_iwq;

	iwq_set_chained_handwew_and_data(pawent_iwq,
		ws1x_chained_handwe_iwq, pwiv);

	wetuwn 0;

out_fwee_domain:
	iwq_domain_wemove(pwiv->domain);
out_iounmap:
	iounmap(pwiv->intc_base);
out_fwee_pwiv:
	kfwee(pwiv);

	wetuwn eww;
}

IWQCHIP_DECWAWE(ws1x_intc, "woongson,ws1x-intc", ws1x_intc_of_init);
