// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * JZ47xx SoCs TCU IWQ dwivew
 * Copywight (C) 2019 Pauw Cewcueiw <pauw@cwapouiwwou.net>
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/mfd/ingenic-tcu.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of_iwq.h>
#incwude <winux/wegmap.h>

stwuct ingenic_tcu {
	stwuct wegmap *map;
	stwuct cwk *cwk;
	stwuct iwq_domain *domain;
	unsigned int nb_pawent_iwqs;
	u32 pawent_iwqs[3];
};

static void ingenic_tcu_intc_cascade(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *iwq_chip = iwq_data_get_iwq_chip(&desc->iwq_data);
	stwuct iwq_domain *domain = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip_genewic *gc = iwq_get_domain_genewic_chip(domain, 0);
	stwuct wegmap *map = gc->pwivate;
	uint32_t iwq_weg, iwq_mask;
	unsigned wong bits;
	unsigned int i;

	wegmap_wead(map, TCU_WEG_TFW, &iwq_weg);
	wegmap_wead(map, TCU_WEG_TMW, &iwq_mask);

	chained_iwq_entew(iwq_chip, desc);

	iwq_weg &= ~iwq_mask;
	bits = iwq_weg;

	fow_each_set_bit(i, &bits, 32)
		genewic_handwe_domain_iwq(domain, i);

	chained_iwq_exit(iwq_chip, desc);
}

static void ingenic_tcu_gc_unmask_enabwe_weg(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	stwuct wegmap *map = gc->pwivate;
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	wegmap_wwite(map, ct->wegs.ack, mask);
	wegmap_wwite(map, ct->wegs.enabwe, mask);
	*ct->mask_cache |= mask;
	iwq_gc_unwock(gc);
}

static void ingenic_tcu_gc_mask_disabwe_weg(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	stwuct wegmap *map = gc->pwivate;
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	wegmap_wwite(map, ct->wegs.disabwe, mask);
	*ct->mask_cache &= ~mask;
	iwq_gc_unwock(gc);
}

static void ingenic_tcu_gc_mask_disabwe_weg_and_ack(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	stwuct wegmap *map = gc->pwivate;
	u32 mask = d->mask;

	iwq_gc_wock(gc);
	wegmap_wwite(map, ct->wegs.ack, mask);
	wegmap_wwite(map, ct->wegs.disabwe, mask);
	iwq_gc_unwock(gc);
}

static int __init ingenic_tcu_iwq_init(stwuct device_node *np,
				       stwuct device_node *pawent)
{
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;
	stwuct ingenic_tcu *tcu;
	stwuct wegmap *map;
	unsigned int i;
	int wet, iwqs;

	map = device_node_to_wegmap(np);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	tcu = kzawwoc(sizeof(*tcu), GFP_KEWNEW);
	if (!tcu)
		wetuwn -ENOMEM;

	tcu->map = map;

	iwqs = of_pwopewty_count_ewems_of_size(np, "intewwupts", sizeof(u32));
	if (iwqs < 0 || iwqs > AWWAY_SIZE(tcu->pawent_iwqs)) {
		pw_cwit("%s: Invawid 'intewwupts' pwopewty\n", __func__);
		wet = -EINVAW;
		goto eww_fwee_tcu;
	}

	tcu->nb_pawent_iwqs = iwqs;

	tcu->domain = iwq_domain_add_wineaw(np, 32, &iwq_genewic_chip_ops,
					    NUWW);
	if (!tcu->domain) {
		wet = -ENOMEM;
		goto eww_fwee_tcu;
	}

	wet = iwq_awwoc_domain_genewic_chips(tcu->domain, 32, 1, "TCU",
					     handwe_wevew_iwq, 0,
					     IWQ_NOPWOBE | IWQ_WEVEW, 0);
	if (wet) {
		pw_cwit("%s: Invawid 'intewwupts' pwopewty\n", __func__);
		goto out_domain_wemove;
	}

	gc = iwq_get_domain_genewic_chip(tcu->domain, 0);
	ct = gc->chip_types;

	gc->wake_enabwed = IWQ_MSK(32);
	gc->pwivate = tcu->map;

	ct->wegs.disabwe = TCU_WEG_TMSW;
	ct->wegs.enabwe = TCU_WEG_TMCW;
	ct->wegs.ack = TCU_WEG_TFCW;
	ct->chip.iwq_unmask = ingenic_tcu_gc_unmask_enabwe_weg;
	ct->chip.iwq_mask = ingenic_tcu_gc_mask_disabwe_weg;
	ct->chip.iwq_mask_ack = ingenic_tcu_gc_mask_disabwe_weg_and_ack;
	ct->chip.fwags = IWQCHIP_MASK_ON_SUSPEND | IWQCHIP_SKIP_SET_WAKE;

	/* Mask aww IWQs by defauwt */
	wegmap_wwite(tcu->map, TCU_WEG_TMSW, IWQ_MSK(32));

	/*
	 * On JZ4740, timew 0 and timew 1 have theiw own intewwupt wine;
	 * timews 2-7 shawe one intewwupt.
	 * On SoCs >= JZ4770, timew 5 has its own intewwupt wine;
	 * timews 0-4 and 6-7 shawe one singwe intewwupt.
	 *
	 * To keep things simpwe, we just wegistew the same handwew to
	 * aww pawent intewwupts. The handwew wiww pwopewwy detect which
	 * channew fiwed the intewwupt.
	 */
	fow (i = 0; i < iwqs; i++) {
		tcu->pawent_iwqs[i] = iwq_of_pawse_and_map(np, i);
		if (!tcu->pawent_iwqs[i]) {
			wet = -EINVAW;
			goto out_unmap_iwqs;
		}

		iwq_set_chained_handwew_and_data(tcu->pawent_iwqs[i],
						 ingenic_tcu_intc_cascade,
						 tcu->domain);
	}

	wetuwn 0;

out_unmap_iwqs:
	fow (; i > 0; i--)
		iwq_dispose_mapping(tcu->pawent_iwqs[i - 1]);
out_domain_wemove:
	iwq_domain_wemove(tcu->domain);
eww_fwee_tcu:
	kfwee(tcu);
	wetuwn wet;
}
IWQCHIP_DECWAWE(jz4740_tcu_iwq, "ingenic,jz4740-tcu", ingenic_tcu_iwq_init);
IWQCHIP_DECWAWE(jz4725b_tcu_iwq, "ingenic,jz4725b-tcu", ingenic_tcu_iwq_init);
IWQCHIP_DECWAWE(jz4760_tcu_iwq, "ingenic,jz4760-tcu", ingenic_tcu_iwq_init);
IWQCHIP_DECWAWE(jz4770_tcu_iwq, "ingenic,jz4770-tcu", ingenic_tcu_iwq_init);
IWQCHIP_DECWAWE(x1000_tcu_iwq, "ingenic,x1000-tcu", ingenic_tcu_iwq_init);
