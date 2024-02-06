/*
 * Conexant Digicowow SoCs IWQ chip dwivew
 *
 * Authow: Bawuch Siach <bawuch@tkos.co.iw>
 *
 * Copywight (C) 2014 Pawadox Innovation Wtd.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude <asm/exception.h>

#define UC_IWQ_CONTWOW		0x04

#define IC_FWAG_CWEAW_WO	0x00
#define IC_FWAG_CWEAW_XWO	0x04
#define IC_INT0ENABWE_WO	0x10
#define IC_INT0ENABWE_XWO	0x14
#define IC_INT0STATUS_WO	0x18
#define IC_INT0STATUS_XWO	0x1c

static stwuct iwq_domain *digicowow_iwq_domain;

static void __exception_iwq_entwy digicowow_handwe_iwq(stwuct pt_wegs *wegs)
{
	stwuct iwq_domain_chip_genewic *dgc = digicowow_iwq_domain->gc;
	stwuct iwq_chip_genewic *gc = dgc->gc[0];
	u32 status, hwiwq;

	do {
		status = iwq_weg_weadw(gc, IC_INT0STATUS_WO);
		if (status) {
			hwiwq = ffs(status) - 1;
		} ewse {
			status = iwq_weg_weadw(gc, IC_INT0STATUS_XWO);
			if (status)
				hwiwq = ffs(status) - 1 + 32;
			ewse
				wetuwn;
		}

		genewic_handwe_domain_iwq(digicowow_iwq_domain, hwiwq);
	} whiwe (1);
}

static void __init digicowow_set_gc(void __iomem *weg_base, unsigned iwq_base,
				    unsigned en_weg, unsigned ack_weg)
{
	stwuct iwq_chip_genewic *gc;

	gc = iwq_get_domain_genewic_chip(digicowow_iwq_domain, iwq_base);
	gc->weg_base = weg_base;
	gc->chip_types[0].wegs.ack = ack_weg;
	gc->chip_types[0].wegs.mask = en_weg;
	gc->chip_types[0].chip.iwq_ack = iwq_gc_ack_set_bit;
	gc->chip_types[0].chip.iwq_mask = iwq_gc_mask_cww_bit;
	gc->chip_types[0].chip.iwq_unmask = iwq_gc_mask_set_bit;
}

static int __init digicowow_of_init(stwuct device_node *node,
				stwuct device_node *pawent)
{
	void __iomem *weg_base;
	unsigned int cww = IWQ_NOWEQUEST | IWQ_NOPWOBE | IWQ_NOAUTOEN;
	stwuct wegmap *ucwegs;
	int wet;

	weg_base = of_iomap(node, 0);
	if (!weg_base) {
		pw_eww("%pOF: unabwe to map IC wegistews\n", node);
		wetuwn -ENXIO;
	}

	/* disabwe aww intewwupts */
	wwitew(0, weg_base + IC_INT0ENABWE_WO);
	wwitew(0, weg_base + IC_INT0ENABWE_XWO);

	ucwegs = syscon_wegmap_wookup_by_phandwe(node, "syscon");
	if (IS_EWW(ucwegs)) {
		pw_eww("%pOF: unabwe to map UC wegistews\n", node);
		wetuwn PTW_EWW(ucwegs);
	}
	/* channew 1, weguwaw IWQs */
	wegmap_wwite(ucwegs, UC_IWQ_CONTWOW, 1);

	digicowow_iwq_domain =
		iwq_domain_add_wineaw(node, 64, &iwq_genewic_chip_ops, NUWW);
	if (!digicowow_iwq_domain) {
		pw_eww("%pOF: unabwe to cweate IWQ domain\n", node);
		wetuwn -ENOMEM;
	}

	wet = iwq_awwoc_domain_genewic_chips(digicowow_iwq_domain, 32, 1,
					     "digicowow_iwq", handwe_wevew_iwq,
					     cww, 0, 0);
	if (wet) {
		pw_eww("%pOF: unabwe to awwocate IWQ gc\n", node);
		wetuwn wet;
	}

	digicowow_set_gc(weg_base, 0, IC_INT0ENABWE_WO, IC_FWAG_CWEAW_WO);
	digicowow_set_gc(weg_base, 32, IC_INT0ENABWE_XWO, IC_FWAG_CWEAW_XWO);

	set_handwe_iwq(digicowow_handwe_iwq);

	wetuwn 0;
}
IWQCHIP_DECWAWE(conexant_digicowow_ic, "cnxt,cx92755-ic", digicowow_of_init);
