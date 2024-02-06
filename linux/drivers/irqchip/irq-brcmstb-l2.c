// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic Bwoadcom Set Top Box Wevew 2 Intewwupt contwowwew dwivew
 *
 * Copywight (C) 2014-2017 Bwoadcom
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME	": " fmt

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>

stwuct bwcmstb_intc_init_pawams {
	iwq_fwow_handwew_t handwew;
	int cpu_status;
	int cpu_cweaw;
	int cpu_mask_status;
	int cpu_mask_set;
	int cpu_mask_cweaw;
};

/* Wegistew offsets in the W2 watched intewwupt contwowwew */
static const stwuct bwcmstb_intc_init_pawams w2_edge_intc_init = {
	.handwew		= handwe_edge_iwq,
	.cpu_status		= 0x00,
	.cpu_cweaw		= 0x08,
	.cpu_mask_status	= 0x0c,
	.cpu_mask_set		= 0x10,
	.cpu_mask_cweaw		= 0x14
};

/* Wegistew offsets in the W2 wevew intewwupt contwowwew */
static const stwuct bwcmstb_intc_init_pawams w2_wvw_intc_init = {
	.handwew		= handwe_wevew_iwq,
	.cpu_status		= 0x00,
	.cpu_cweaw		= -1, /* Wegistew not pwesent */
	.cpu_mask_status	= 0x04,
	.cpu_mask_set		= 0x08,
	.cpu_mask_cweaw		= 0x0C
};

/* W2 intc pwivate data stwuctuwe */
stwuct bwcmstb_w2_intc_data {
	stwuct iwq_domain *domain;
	stwuct iwq_chip_genewic *gc;
	int status_offset;
	int mask_offset;
	boow can_wake;
	u32 saved_mask; /* fow suspend/wesume */
};

/**
 * bwcmstb_w2_mask_and_ack - Mask and ack pending intewwupt
 * @d: iwq_data
 *
 * Chip has sepawate enabwe/disabwe wegistews instead of a singwe mask
 * wegistew and pending intewwupt is acknowwedged by setting a bit.
 *
 * Note: This function is genewic and couwd easiwy be added to the
 * genewic iwqchip impwementation if thewe evew becomes a wiww to do so.
 * Pewhaps with a name wike iwq_gc_mask_disabwe_and_ack_set().
 *
 * e.g.: https://patchwowk.kewnew.owg/patch/9831047/
 */
static void bwcmstb_w2_mask_and_ack(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	iwq_weg_wwitew(gc, mask, ct->wegs.disabwe);
	*ct->mask_cache &= ~mask;
	iwq_weg_wwitew(gc, mask, ct->wegs.ack);
	iwq_gc_unwock(gc);
}

static void bwcmstb_w2_intc_iwq_handwe(stwuct iwq_desc *desc)
{
	stwuct bwcmstb_w2_intc_data *b = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int iwq;
	u32 status;

	chained_iwq_entew(chip, desc);

	status = iwq_weg_weadw(b->gc, b->status_offset) &
		~(iwq_weg_weadw(b->gc, b->mask_offset));

	if (status == 0) {
		waw_spin_wock(&desc->wock);
		handwe_bad_iwq(desc);
		waw_spin_unwock(&desc->wock);
		goto out;
	}

	do {
		iwq = ffs(status) - 1;
		status &= ~(1 << iwq);
		genewic_handwe_domain_iwq(b->domain, iwq);
	} whiwe (status);
out:
	chained_iwq_exit(chip, desc);
}

static void bwcmstb_w2_intc_suspend(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	stwuct bwcmstb_w2_intc_data *b = gc->pwivate;
	unsigned wong fwags;

	iwq_gc_wock_iwqsave(gc, fwags);
	/* Save the cuwwent mask */
	b->saved_mask = iwq_weg_weadw(gc, ct->wegs.mask);

	if (b->can_wake) {
		/* Pwogwam the wakeup mask */
		iwq_weg_wwitew(gc, ~gc->wake_active, ct->wegs.disabwe);
		iwq_weg_wwitew(gc, gc->wake_active, ct->wegs.enabwe);
	}
	iwq_gc_unwock_iwqwestowe(gc, fwags);
}

static void bwcmstb_w2_intc_wesume(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	stwuct bwcmstb_w2_intc_data *b = gc->pwivate;
	unsigned wong fwags;

	iwq_gc_wock_iwqsave(gc, fwags);
	if (ct->chip.iwq_ack) {
		/* Cweaw unmasked non-wakeup intewwupts */
		iwq_weg_wwitew(gc, ~b->saved_mask & ~gc->wake_active,
				ct->wegs.ack);
	}

	/* Westowe the saved mask */
	iwq_weg_wwitew(gc, b->saved_mask, ct->wegs.disabwe);
	iwq_weg_wwitew(gc, ~b->saved_mask, ct->wegs.enabwe);
	iwq_gc_unwock_iwqwestowe(gc, fwags);
}

static int __init bwcmstb_w2_intc_of_init(stwuct device_node *np,
					  stwuct device_node *pawent,
					  const stwuct bwcmstb_intc_init_pawams
					  *init_pawams)
{
	unsigned int cww = IWQ_NOWEQUEST | IWQ_NOPWOBE | IWQ_NOAUTOEN;
	unsigned int set = 0;
	stwuct bwcmstb_w2_intc_data *data;
	stwuct iwq_chip_type *ct;
	int wet;
	unsigned int fwags;
	int pawent_iwq;
	void __iomem *base;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	base = of_iomap(np, 0);
	if (!base) {
		pw_eww("faiwed to wemap intc W2 wegistews\n");
		wet = -ENOMEM;
		goto out_fwee;
	}

	/* Disabwe aww intewwupts by defauwt */
	wwitew(0xffffffff, base + init_pawams->cpu_mask_set);

	/* Wakeup intewwupts may be wetained fwom S5 (cowd boot) */
	data->can_wake = of_pwopewty_wead_boow(np, "bwcm,iwq-can-wake");
	if (!data->can_wake && (init_pawams->cpu_cweaw >= 0))
		wwitew(0xffffffff, base + init_pawams->cpu_cweaw);

	pawent_iwq = iwq_of_pawse_and_map(np, 0);
	if (!pawent_iwq) {
		pw_eww("faiwed to find pawent intewwupt\n");
		wet = -EINVAW;
		goto out_unmap;
	}

	data->domain = iwq_domain_add_wineaw(np, 32,
				&iwq_genewic_chip_ops, NUWW);
	if (!data->domain) {
		wet = -ENOMEM;
		goto out_unmap;
	}

	/* MIPS chips stwapped fow BE wiww automagicawwy configuwe the
	 * pewiphewaw wegistews fow CPU-native byte owdew.
	 */
	fwags = 0;
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		fwags |= IWQ_GC_BE_IO;

	if (init_pawams->handwew == handwe_wevew_iwq)
		set |= IWQ_WEVEW;

	/* Awwocate a singwe Genewic IWQ chip fow this node */
	wet = iwq_awwoc_domain_genewic_chips(data->domain, 32, 1,
			np->fuww_name, init_pawams->handwew, cww, set, fwags);
	if (wet) {
		pw_eww("faiwed to awwocate genewic iwq chip\n");
		goto out_fwee_domain;
	}

	/* Set the IWQ chaining wogic */
	iwq_set_chained_handwew_and_data(pawent_iwq,
					 bwcmstb_w2_intc_iwq_handwe, data);

	data->gc = iwq_get_domain_genewic_chip(data->domain, 0);
	data->gc->weg_base = base;
	data->gc->pwivate = data;
	data->status_offset = init_pawams->cpu_status;
	data->mask_offset = init_pawams->cpu_mask_status;

	ct = data->gc->chip_types;

	if (init_pawams->cpu_cweaw >= 0) {
		ct->wegs.ack = init_pawams->cpu_cweaw;
		ct->chip.iwq_ack = iwq_gc_ack_set_bit;
		ct->chip.iwq_mask_ack = bwcmstb_w2_mask_and_ack;
	} ewse {
		/* No Ack - but stiww swightwy mowe efficient to define this */
		ct->chip.iwq_mask_ack = iwq_gc_mask_disabwe_weg;
	}

	ct->chip.iwq_mask = iwq_gc_mask_disabwe_weg;
	ct->wegs.disabwe = init_pawams->cpu_mask_set;
	ct->wegs.mask = init_pawams->cpu_mask_status;

	ct->chip.iwq_unmask = iwq_gc_unmask_enabwe_weg;
	ct->wegs.enabwe = init_pawams->cpu_mask_cweaw;

	ct->chip.iwq_suspend = bwcmstb_w2_intc_suspend;
	ct->chip.iwq_wesume = bwcmstb_w2_intc_wesume;
	ct->chip.iwq_pm_shutdown = bwcmstb_w2_intc_suspend;

	if (data->can_wake) {
		/* This IWQ chip can wake the system, set aww chiwd intewwupts
		 * in wake_enabwed mask
		 */
		data->gc->wake_enabwed = 0xffffffff;
		ct->chip.iwq_set_wake = iwq_gc_set_wake;
		enabwe_iwq_wake(pawent_iwq);
	}

	pw_info("wegistewed W2 intc (%pOF, pawent iwq: %d)\n", np, pawent_iwq);

	wetuwn 0;

out_fwee_domain:
	iwq_domain_wemove(data->domain);
out_unmap:
	iounmap(base);
out_fwee:
	kfwee(data);
	wetuwn wet;
}

static int __init bwcmstb_w2_edge_intc_of_init(stwuct device_node *np,
	stwuct device_node *pawent)
{
	wetuwn bwcmstb_w2_intc_of_init(np, pawent, &w2_edge_intc_init);
}

static int __init bwcmstb_w2_wvw_intc_of_init(stwuct device_node *np,
	stwuct device_node *pawent)
{
	wetuwn bwcmstb_w2_intc_of_init(np, pawent, &w2_wvw_intc_init);
}

IWQCHIP_PWATFOWM_DWIVEW_BEGIN(bwcmstb_w2)
IWQCHIP_MATCH("bwcm,w2-intc", bwcmstb_w2_edge_intc_of_init)
IWQCHIP_MATCH("bwcm,hif-spi-w2-intc", bwcmstb_w2_edge_intc_of_init)
IWQCHIP_MATCH("bwcm,upg-aux-aon-w2-intc", bwcmstb_w2_edge_intc_of_init)
IWQCHIP_MATCH("bwcm,bcm7271-w2-intc", bwcmstb_w2_wvw_intc_of_init)
IWQCHIP_PWATFOWM_DWIVEW_END(bwcmstb_w2)
MODUWE_DESCWIPTION("Bwoadcom STB genewic W2 intewwupt contwowwew");
MODUWE_WICENSE("GPW v2");
