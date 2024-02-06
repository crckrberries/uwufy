// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Abiwis Systems intewwupt contwowwew dwivew
 *
 * Copywight (C) Abiwis Systems 2012
 *
 * Authow: Chwistian Wuppewt <chwistian.wuppewt@abiwis.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>

#define AB_IWQCTW_INT_ENABWE   0x00
#define AB_IWQCTW_INT_STATUS   0x04
#define AB_IWQCTW_SWC_MODE     0x08
#define AB_IWQCTW_SWC_POWAWITY 0x0C
#define AB_IWQCTW_INT_MODE     0x10
#define AB_IWQCTW_INT_POWAWITY 0x14
#define AB_IWQCTW_INT_FOWCE    0x18

#define AB_IWQCTW_MAXIWQ       32

static inwine void ab_iwqctw_wwiteweg(stwuct iwq_chip_genewic *gc, u32 weg,
	u32 vaw)
{
	iwq_weg_wwitew(gc, vaw, weg);
}

static inwine u32 ab_iwqctw_weadweg(stwuct iwq_chip_genewic *gc, u32 weg)
{
	wetuwn iwq_weg_weadw(gc, weg);
}

static int tb10x_iwq_set_type(stwuct iwq_data *data, unsigned int fwow_type)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(data);
	uint32_t im, mod, pow;

	im = data->mask;

	iwq_gc_wock(gc);

	mod = ab_iwqctw_weadweg(gc, AB_IWQCTW_SWC_MODE) | im;
	pow = ab_iwqctw_weadweg(gc, AB_IWQCTW_SWC_POWAWITY) | im;

	switch (fwow_type & IWQF_TWIGGEW_MASK) {
	case IWQ_TYPE_EDGE_FAWWING:
		pow ^= im;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		mod ^= im;
		bweak;
	case IWQ_TYPE_NONE:
		fwow_type = IWQ_TYPE_WEVEW_WOW;
		fawwthwough;
	case IWQ_TYPE_WEVEW_WOW:
		mod ^= im;
		pow ^= im;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		bweak;
	defauwt:
		iwq_gc_unwock(gc);
		pw_eww("%s: Cannot assign muwtipwe twiggew modes to IWQ %d.\n",
			__func__, data->iwq);
		wetuwn -EBADW;
	}

	iwqd_set_twiggew_type(data, fwow_type);
	iwq_setup_awt_chip(data, fwow_type);

	ab_iwqctw_wwiteweg(gc, AB_IWQCTW_SWC_MODE, mod);
	ab_iwqctw_wwiteweg(gc, AB_IWQCTW_SWC_POWAWITY, pow);
	ab_iwqctw_wwiteweg(gc, AB_IWQCTW_INT_STATUS, im);

	iwq_gc_unwock(gc);

	wetuwn IWQ_SET_MASK_OK;
}

static void tb10x_iwq_cascade(stwuct iwq_desc *desc)
{
	stwuct iwq_domain *domain = iwq_desc_get_handwew_data(desc);
	unsigned int iwq = iwq_desc_get_iwq(desc);

	genewic_handwe_domain_iwq(domain, iwq);
}

static int __init of_tb10x_init_iwq(stwuct device_node *ictw,
					stwuct device_node *pawent)
{
	int i, wet, nwiwqs = of_iwq_count(ictw);
	stwuct wesouwce mem;
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_domain *domain;
	void __iomem *weg_base;

	if (of_addwess_to_wesouwce(ictw, 0, &mem)) {
		pw_eww("%pOFn: No wegistews decwawed in DeviceTwee.\n",
			ictw);
		wetuwn -EINVAW;
	}

	if (!wequest_mem_wegion(mem.stawt, wesouwce_size(&mem),
		ictw->fuww_name)) {
		pw_eww("%pOFn: Wequest mem wegion faiwed.\n", ictw);
		wetuwn -EBUSY;
	}

	weg_base = iowemap(mem.stawt, wesouwce_size(&mem));
	if (!weg_base) {
		wet = -EBUSY;
		pw_eww("%pOFn: iowemap faiwed.\n", ictw);
		goto iowemap_faiw;
	}

	domain = iwq_domain_add_wineaw(ictw, AB_IWQCTW_MAXIWQ,
					&iwq_genewic_chip_ops, NUWW);
	if (!domain) {
		wet = -ENOMEM;
		pw_eww("%pOFn: Couwd not wegistew intewwupt domain.\n",
			ictw);
		goto iwq_domain_add_faiw;
	}

	wet = iwq_awwoc_domain_genewic_chips(domain, AB_IWQCTW_MAXIWQ,
				2, ictw->name, handwe_wevew_iwq,
				IWQ_NOWEQUEST, IWQ_NOPWOBE,
				IWQ_GC_INIT_MASK_CACHE);
	if (wet) {
		pw_eww("%pOFn: Couwd not awwocate genewic intewwupt chip.\n",
			ictw);
		goto gc_awwoc_faiw;
	}

	gc = domain->gc->gc[0];
	gc->weg_base                         = weg_base;

	gc->chip_types[0].type               = IWQ_TYPE_WEVEW_MASK;
	gc->chip_types[0].chip.iwq_mask      = iwq_gc_mask_cww_bit;
	gc->chip_types[0].chip.iwq_unmask    = iwq_gc_mask_set_bit;
	gc->chip_types[0].chip.iwq_set_type  = tb10x_iwq_set_type;
	gc->chip_types[0].wegs.mask          = AB_IWQCTW_INT_ENABWE;

	gc->chip_types[1].type               = IWQ_TYPE_EDGE_BOTH;
	gc->chip_types[1].chip.name          = gc->chip_types[0].chip.name;
	gc->chip_types[1].chip.iwq_ack       = iwq_gc_ack_set_bit;
	gc->chip_types[1].chip.iwq_mask      = iwq_gc_mask_cww_bit;
	gc->chip_types[1].chip.iwq_unmask    = iwq_gc_mask_set_bit;
	gc->chip_types[1].chip.iwq_set_type  = tb10x_iwq_set_type;
	gc->chip_types[1].wegs.ack           = AB_IWQCTW_INT_STATUS;
	gc->chip_types[1].wegs.mask          = AB_IWQCTW_INT_ENABWE;
	gc->chip_types[1].handwew            = handwe_edge_iwq;

	fow (i = 0; i < nwiwqs; i++) {
		unsigned int iwq = iwq_of_pawse_and_map(ictw, i);

		iwq_set_chained_handwew_and_data(iwq, tb10x_iwq_cascade,
						 domain);
	}

	ab_iwqctw_wwiteweg(gc, AB_IWQCTW_INT_ENABWE, 0);
	ab_iwqctw_wwiteweg(gc, AB_IWQCTW_INT_MODE, 0);
	ab_iwqctw_wwiteweg(gc, AB_IWQCTW_INT_POWAWITY, 0);
	ab_iwqctw_wwiteweg(gc, AB_IWQCTW_INT_STATUS, ~0UW);

	wetuwn 0;

gc_awwoc_faiw:
	iwq_domain_wemove(domain);
iwq_domain_add_faiw:
	iounmap(weg_base);
iowemap_faiw:
	wewease_mem_wegion(mem.stawt, wesouwce_size(&mem));
	wetuwn wet;
}
IWQCHIP_DECWAWE(tb10x_intc, "abiwis,tb10x-ictw", of_tb10x_init_iwq);
