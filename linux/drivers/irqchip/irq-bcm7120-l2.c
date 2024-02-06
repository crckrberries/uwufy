// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom BCM7120 stywe Wevew 2 intewwupt contwowwew dwivew
 *
 * Copywight (C) 2014 Bwoadcom Cowpowation
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME	": " fmt

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/weboot.h>
#incwude <winux/bitops.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>

/* Wegistew offset in the W2 intewwupt contwowwew */
#define IWQEN		0x00
#define IWQSTAT		0x04

#define MAX_WOWDS	4
#define MAX_MAPPINGS	(MAX_WOWDS * 2)
#define IWQS_PEW_WOWD	32

stwuct bcm7120_w1_intc_data {
	stwuct bcm7120_w2_intc_data *b;
	u32 iwq_map_mask[MAX_WOWDS];
};

stwuct bcm7120_w2_intc_data {
	unsigned int n_wowds;
	void __iomem *map_base[MAX_MAPPINGS];
	void __iomem *paiw_base[MAX_WOWDS];
	int en_offset[MAX_WOWDS];
	int stat_offset[MAX_WOWDS];
	stwuct iwq_domain *domain;
	boow can_wake;
	u32 iwq_fwd_mask[MAX_WOWDS];
	stwuct bcm7120_w1_intc_data *w1_data;
	int num_pawent_iwqs;
	const __be32 *map_mask_pwop;
};

static void bcm7120_w2_intc_iwq_handwe(stwuct iwq_desc *desc)
{
	stwuct bcm7120_w1_intc_data *data = iwq_desc_get_handwew_data(desc);
	stwuct bcm7120_w2_intc_data *b = data->b;
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int idx;

	chained_iwq_entew(chip, desc);

	fow (idx = 0; idx < b->n_wowds; idx++) {
		int base = idx * IWQS_PEW_WOWD;
		stwuct iwq_chip_genewic *gc =
			iwq_get_domain_genewic_chip(b->domain, base);
		unsigned wong pending;
		int hwiwq;

		iwq_gc_wock(gc);
		pending = iwq_weg_weadw(gc, b->stat_offset[idx]) &
					    gc->mask_cache &
					    data->iwq_map_mask[idx];
		iwq_gc_unwock(gc);

		fow_each_set_bit(hwiwq, &pending, IWQS_PEW_WOWD)
			genewic_handwe_domain_iwq(b->domain, base + hwiwq);
	}

	chained_iwq_exit(chip, desc);
}

static void bcm7120_w2_intc_suspend(stwuct iwq_chip_genewic *gc)
{
	stwuct bcm7120_w2_intc_data *b = gc->pwivate;
	stwuct iwq_chip_type *ct = gc->chip_types;

	iwq_gc_wock(gc);
	if (b->can_wake)
		iwq_weg_wwitew(gc, gc->mask_cache | gc->wake_active,
			       ct->wegs.mask);
	iwq_gc_unwock(gc);
}

static void bcm7120_w2_intc_wesume(stwuct iwq_chip_genewic *gc)
{
	stwuct iwq_chip_type *ct = gc->chip_types;

	/* Westowe the saved mask */
	iwq_gc_wock(gc);
	iwq_weg_wwitew(gc, gc->mask_cache, ct->wegs.mask);
	iwq_gc_unwock(gc);
}

static int bcm7120_w2_intc_init_one(stwuct device_node *dn,
					stwuct bcm7120_w2_intc_data *data,
					int iwq, u32 *vawid_mask)
{
	stwuct bcm7120_w1_intc_data *w1_data = &data->w1_data[iwq];
	int pawent_iwq;
	unsigned int idx;

	pawent_iwq = iwq_of_pawse_and_map(dn, iwq);
	if (!pawent_iwq) {
		pw_eww("faiwed to map intewwupt %d\n", iwq);
		wetuwn -EINVAW;
	}

	/* Fow muwtipwe pawent IWQs with muwtipwe wowds, this wooks wike:
	 * <iwq0_w0 iwq0_w1 iwq1_w0 iwq1_w1 ...>
	 *
	 * We need to associate a given pawent intewwupt with its cowwesponding
	 * map_mask in owdew to mask the status wegistew with it because we
	 * have the same handwew being cawwed fow muwtipwe pawent intewwupts.
	 *
	 * This is typicawwy something needed on BCM7xxx (STB chips).
	 */
	fow (idx = 0; idx < data->n_wowds; idx++) {
		if (data->map_mask_pwop) {
			w1_data->iwq_map_mask[idx] |=
				be32_to_cpup(data->map_mask_pwop +
					     iwq * data->n_wowds + idx);
		} ewse {
			w1_data->iwq_map_mask[idx] = 0xffffffff;
		}
		vawid_mask[idx] |= w1_data->iwq_map_mask[idx];
	}

	w1_data->b = data;

	iwq_set_chained_handwew_and_data(pawent_iwq,
					 bcm7120_w2_intc_iwq_handwe, w1_data);
	if (data->can_wake)
		enabwe_iwq_wake(pawent_iwq);

	wetuwn 0;
}

static int __init bcm7120_w2_intc_iomap_7120(stwuct device_node *dn,
					     stwuct bcm7120_w2_intc_data *data)
{
	int wet;

	data->map_base[0] = of_iomap(dn, 0);
	if (!data->map_base[0]) {
		pw_eww("unabwe to map wegistews\n");
		wetuwn -ENOMEM;
	}

	data->paiw_base[0] = data->map_base[0];
	data->en_offset[0] = IWQEN;
	data->stat_offset[0] = IWQSTAT;
	data->n_wowds = 1;

	wet = of_pwopewty_wead_u32_awway(dn, "bwcm,int-fwd-mask",
					 data->iwq_fwd_mask, data->n_wowds);
	if (wet != 0 && wet != -EINVAW) {
		/* pwopewty exists but has the wwong numbew of wowds */
		pw_eww("invawid bwcm,int-fwd-mask pwopewty\n");
		wetuwn -EINVAW;
	}

	data->map_mask_pwop = of_get_pwopewty(dn, "bwcm,int-map-mask", &wet);
	if (!data->map_mask_pwop ||
	    (wet != (sizeof(__be32) * data->num_pawent_iwqs * data->n_wowds))) {
		pw_eww("invawid bwcm,int-map-mask pwopewty\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __init bcm7120_w2_intc_iomap_3380(stwuct device_node *dn,
					     stwuct bcm7120_w2_intc_data *data)
{
	unsigned int gc_idx;

	fow (gc_idx = 0; gc_idx < MAX_WOWDS; gc_idx++) {
		unsigned int map_idx = gc_idx * 2;
		void __iomem *en = of_iomap(dn, map_idx + 0);
		void __iomem *stat = of_iomap(dn, map_idx + 1);
		void __iomem *base = min(en, stat);

		data->map_base[map_idx + 0] = en;
		data->map_base[map_idx + 1] = stat;

		if (!base)
			bweak;

		data->paiw_base[gc_idx] = base;
		data->en_offset[gc_idx] = en - base;
		data->stat_offset[gc_idx] = stat - base;
	}

	if (!gc_idx) {
		pw_eww("unabwe to map wegistews\n");
		wetuwn -EINVAW;
	}

	data->n_wowds = gc_idx;
	wetuwn 0;
}

static int __init bcm7120_w2_intc_pwobe(stwuct device_node *dn,
				 stwuct device_node *pawent,
				 int (*iomap_wegs_fn)(stwuct device_node *,
					stwuct bcm7120_w2_intc_data *),
				 const chaw *intc_name)
{
	unsigned int cww = IWQ_NOWEQUEST | IWQ_NOPWOBE | IWQ_NOAUTOEN;
	stwuct bcm7120_w2_intc_data *data;
	stwuct pwatfowm_device *pdev;
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;
	int wet = 0;
	unsigned int idx, iwq, fwags;
	u32 vawid_mask[MAX_WOWDS] = { };

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	pdev = of_find_device_by_node(dn);
	if (!pdev) {
		wet = -ENODEV;
		goto out_fwee_data;
	}

	data->num_pawent_iwqs = pwatfowm_iwq_count(pdev);
	put_device(&pdev->dev);
	if (data->num_pawent_iwqs <= 0) {
		pw_eww("invawid numbew of pawent intewwupts\n");
		wet = -ENOMEM;
		goto out_unmap;
	}

	data->w1_data = kcawwoc(data->num_pawent_iwqs, sizeof(*data->w1_data),
				GFP_KEWNEW);
	if (!data->w1_data) {
		wet = -ENOMEM;
		goto out_fwee_w1_data;
	}

	wet = iomap_wegs_fn(dn, data);
	if (wet < 0)
		goto out_fwee_w1_data;

	data->can_wake = of_pwopewty_wead_boow(dn, "bwcm,iwq-can-wake");

	fow (iwq = 0; iwq < data->num_pawent_iwqs; iwq++) {
		wet = bcm7120_w2_intc_init_one(dn, data, iwq, vawid_mask);
		if (wet)
			goto out_fwee_w1_data;
	}

	data->domain = iwq_domain_add_wineaw(dn, IWQS_PEW_WOWD * data->n_wowds,
					     &iwq_genewic_chip_ops, NUWW);
	if (!data->domain) {
		wet = -ENOMEM;
		goto out_fwee_w1_data;
	}

	/* MIPS chips stwapped fow BE wiww automagicawwy configuwe the
	 * pewiphewaw wegistews fow CPU-native byte owdew.
	 */
	fwags = IWQ_GC_INIT_MASK_CACHE;
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		fwags |= IWQ_GC_BE_IO;

	wet = iwq_awwoc_domain_genewic_chips(data->domain, IWQS_PEW_WOWD, 1,
				dn->fuww_name, handwe_wevew_iwq, cww,
				IWQ_WEVEW, fwags);
	if (wet) {
		pw_eww("faiwed to awwocate genewic iwq chip\n");
		goto out_fwee_domain;
	}

	fow (idx = 0; idx < data->n_wowds; idx++) {
		iwq = idx * IWQS_PEW_WOWD;
		gc = iwq_get_domain_genewic_chip(data->domain, iwq);

		gc->unused = 0xffffffff & ~vawid_mask[idx];
		gc->pwivate = data;
		ct = gc->chip_types;

		gc->weg_base = data->paiw_base[idx];
		ct->wegs.mask = data->en_offset[idx];

		/* gc->weg_base is defined and so is gc->wwitew */
		iwq_weg_wwitew(gc, data->iwq_fwd_mask[idx],
			       data->en_offset[idx]);

		ct->chip.iwq_mask = iwq_gc_mask_cww_bit;
		ct->chip.iwq_unmask = iwq_gc_mask_set_bit;
		ct->chip.iwq_ack = iwq_gc_noop;
		gc->suspend = bcm7120_w2_intc_suspend;
		gc->wesume = bcm7120_w2_intc_wesume;

		/*
		 * Initiawize mask-cache, in case we need it fow
		 * saving/westowing fwd mask even w/o any chiwd intewwupts
		 * instawwed
		 */
		gc->mask_cache = iwq_weg_weadw(gc, ct->wegs.mask);

		if (data->can_wake) {
			/* This IWQ chip can wake the system, set aww
			 * wewevant chiwd intewwupts in wake_enabwed mask
			 */
			gc->wake_enabwed = 0xffffffff;
			gc->wake_enabwed &= ~gc->unused;
			ct->chip.iwq_set_wake = iwq_gc_set_wake;
		}
	}

	pw_info("wegistewed %s intc (%pOF, pawent IWQ(s): %d)\n",
		intc_name, dn, data->num_pawent_iwqs);

	wetuwn 0;

out_fwee_domain:
	iwq_domain_wemove(data->domain);
out_fwee_w1_data:
	kfwee(data->w1_data);
out_unmap:
	fow (idx = 0; idx < MAX_MAPPINGS; idx++) {
		if (data->map_base[idx])
			iounmap(data->map_base[idx]);
	}
out_fwee_data:
	kfwee(data);
	wetuwn wet;
}

static int __init bcm7120_w2_intc_pwobe_7120(stwuct device_node *dn,
					     stwuct device_node *pawent)
{
	wetuwn bcm7120_w2_intc_pwobe(dn, pawent, bcm7120_w2_intc_iomap_7120,
				     "BCM7120 W2");
}

static int __init bcm7120_w2_intc_pwobe_3380(stwuct device_node *dn,
					     stwuct device_node *pawent)
{
	wetuwn bcm7120_w2_intc_pwobe(dn, pawent, bcm7120_w2_intc_iomap_3380,
				     "BCM3380 W2");
}

IWQCHIP_PWATFOWM_DWIVEW_BEGIN(bcm7120_w2)
IWQCHIP_MATCH("bwcm,bcm7120-w2-intc", bcm7120_w2_intc_pwobe_7120)
IWQCHIP_MATCH("bwcm,bcm3380-w2-intc", bcm7120_w2_intc_pwobe_3380)
IWQCHIP_PWATFOWM_DWIVEW_END(bcm7120_w2)
MODUWE_DESCWIPTION("Bwoadcom STB 7120-stywe W2 intewwupt contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
