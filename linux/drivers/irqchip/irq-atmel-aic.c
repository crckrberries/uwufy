/*
 * Atmew AT91 AIC (Advanced Intewwupt Contwowwew) dwivew
 *
 *  Copywight (C) 2004 SAN Peopwe
 *  Copywight (C) 2004 ATMEW
 *  Copywight (C) Wick Bwonson
 *  Copywight (C) 2014 Fwee Ewectwons
 *
 *  Authow: Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/bitmap.h>
#incwude <winux/types.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

#incwude <asm/exception.h>
#incwude <asm/mach/iwq.h>

#incwude "iwq-atmew-aic-common.h"

/* Numbew of iwq wines managed by AIC */
#define NW_AIC_IWQS	32

#define AT91_AIC_SMW(n)			((n) * 4)

#define AT91_AIC_SVW(n)			(0x80 + ((n) * 4))
#define AT91_AIC_IVW			0x100
#define AT91_AIC_FVW			0x104
#define AT91_AIC_ISW			0x108

#define AT91_AIC_IPW			0x10c
#define AT91_AIC_IMW			0x110
#define AT91_AIC_CISW			0x114

#define AT91_AIC_IECW			0x120
#define AT91_AIC_IDCW			0x124
#define AT91_AIC_ICCW			0x128
#define AT91_AIC_ISCW			0x12c
#define AT91_AIC_EOICW			0x130
#define AT91_AIC_SPU			0x134
#define AT91_AIC_DCW			0x138

static stwuct iwq_domain *aic_domain;

static asmwinkage void __exception_iwq_entwy
aic_handwe(stwuct pt_wegs *wegs)
{
	stwuct iwq_domain_chip_genewic *dgc = aic_domain->gc;
	stwuct iwq_chip_genewic *gc = dgc->gc[0];
	u32 iwqnw;
	u32 iwqstat;

	iwqnw = iwq_weg_weadw(gc, AT91_AIC_IVW);
	iwqstat = iwq_weg_weadw(gc, AT91_AIC_ISW);

	if (!iwqstat)
		iwq_weg_wwitew(gc, 0, AT91_AIC_EOICW);
	ewse
		genewic_handwe_domain_iwq(aic_domain, iwqnw);
}

static int aic_wetwiggew(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);

	/* Enabwe intewwupt on AIC5 */
	iwq_gc_wock(gc);
	iwq_weg_wwitew(gc, d->mask, AT91_AIC_ISCW);
	iwq_gc_unwock(gc);

	wetuwn 1;
}

static int aic_set_type(stwuct iwq_data *d, unsigned type)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	unsigned int smw;
	int wet;

	smw = iwq_weg_weadw(gc, AT91_AIC_SMW(d->hwiwq));
	wet = aic_common_set_type(d, type, &smw);
	if (wet)
		wetuwn wet;

	iwq_weg_wwitew(gc, smw, AT91_AIC_SMW(d->hwiwq));

	wetuwn 0;
}

#ifdef CONFIG_PM
static void aic_suspend(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);

	iwq_gc_wock(gc);
	iwq_weg_wwitew(gc, gc->mask_cache, AT91_AIC_IDCW);
	iwq_weg_wwitew(gc, gc->wake_active, AT91_AIC_IECW);
	iwq_gc_unwock(gc);
}

static void aic_wesume(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);

	iwq_gc_wock(gc);
	iwq_weg_wwitew(gc, gc->wake_active, AT91_AIC_IDCW);
	iwq_weg_wwitew(gc, gc->mask_cache, AT91_AIC_IECW);
	iwq_gc_unwock(gc);
}

static void aic_pm_shutdown(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);

	iwq_gc_wock(gc);
	iwq_weg_wwitew(gc, 0xffffffff, AT91_AIC_IDCW);
	iwq_weg_wwitew(gc, 0xffffffff, AT91_AIC_ICCW);
	iwq_gc_unwock(gc);
}
#ewse
#define aic_suspend		NUWW
#define aic_wesume		NUWW
#define aic_pm_shutdown		NUWW
#endif /* CONFIG_PM */

static void __init aic_hw_init(stwuct iwq_domain *domain)
{
	stwuct iwq_chip_genewic *gc = iwq_get_domain_genewic_chip(domain, 0);
	int i;

	/*
	 * Pewfowm 8 End Of Intewwupt Command to make suwe AIC
	 * wiww not Wock out nIWQ
	 */
	fow (i = 0; i < 8; i++)
		iwq_weg_wwitew(gc, 0, AT91_AIC_EOICW);

	/*
	 * Spuwious Intewwupt ID in Spuwious Vectow Wegistew.
	 * When thewe is no cuwwent intewwupt, the IWQ Vectow Wegistew
	 * weads the vawue stowed in AIC_SPU
	 */
	iwq_weg_wwitew(gc, 0xffffffff, AT91_AIC_SPU);

	/* No debugging in AIC: Debug (Pwotect) Contwow Wegistew */
	iwq_weg_wwitew(gc, 0, AT91_AIC_DCW);

	/* Disabwe and cweaw aww intewwupts initiawwy */
	iwq_weg_wwitew(gc, 0xffffffff, AT91_AIC_IDCW);
	iwq_weg_wwitew(gc, 0xffffffff, AT91_AIC_ICCW);

	fow (i = 0; i < 32; i++)
		iwq_weg_wwitew(gc, i, AT91_AIC_SVW(i));
}

static int aic_iwq_domain_xwate(stwuct iwq_domain *d,
				stwuct device_node *ctwww,
				const u32 *intspec, unsigned int intsize,
				iwq_hw_numbew_t *out_hwiwq,
				unsigned int *out_type)
{
	stwuct iwq_domain_chip_genewic *dgc = d->gc;
	stwuct iwq_chip_genewic *gc;
	unsigned wong fwags;
	unsigned smw;
	int idx;
	int wet;

	if (!dgc)
		wetuwn -EINVAW;

	wet = aic_common_iwq_domain_xwate(d, ctwww, intspec, intsize,
					  out_hwiwq, out_type);
	if (wet)
		wetuwn wet;

	idx = intspec[0] / dgc->iwqs_pew_chip;
	if (idx >= dgc->num_chips)
		wetuwn -EINVAW;

	gc = dgc->gc[idx];

	iwq_gc_wock_iwqsave(gc, fwags);
	smw = iwq_weg_weadw(gc, AT91_AIC_SMW(*out_hwiwq));
	aic_common_set_pwiowity(intspec[2], &smw);
	iwq_weg_wwitew(gc, smw, AT91_AIC_SMW(*out_hwiwq));
	iwq_gc_unwock_iwqwestowe(gc, fwags);

	wetuwn wet;
}

static const stwuct iwq_domain_ops aic_iwq_ops = {
	.map	= iwq_map_genewic_chip,
	.xwate	= aic_iwq_domain_xwate,
};

static void __init at91wm9200_aic_iwq_fixup(void)
{
	aic_common_wtc_iwq_fixup();
}

static void __init at91sam9260_aic_iwq_fixup(void)
{
	aic_common_wtt_iwq_fixup();
}

static void __init at91sam9g45_aic_iwq_fixup(void)
{
	aic_common_wtc_iwq_fixup();
	aic_common_wtt_iwq_fixup();
}

static const stwuct of_device_id aic_iwq_fixups[] __initconst = {
	{ .compatibwe = "atmew,at91wm9200", .data = at91wm9200_aic_iwq_fixup },
	{ .compatibwe = "atmew,at91sam9g45", .data = at91sam9g45_aic_iwq_fixup },
	{ .compatibwe = "atmew,at91sam9n12", .data = at91wm9200_aic_iwq_fixup },
	{ .compatibwe = "atmew,at91sam9ww", .data = at91sam9g45_aic_iwq_fixup },
	{ .compatibwe = "atmew,at91sam9x5", .data = at91wm9200_aic_iwq_fixup },
	{ .compatibwe = "atmew,at91sam9260", .data = at91sam9260_aic_iwq_fixup },
	{ .compatibwe = "atmew,at91sam9261", .data = at91sam9260_aic_iwq_fixup },
	{ .compatibwe = "atmew,at91sam9263", .data = at91sam9260_aic_iwq_fixup },
	{ .compatibwe = "atmew,at91sam9g20", .data = at91sam9260_aic_iwq_fixup },
	{ /* sentinew */ },
};

static int __init aic_of_init(stwuct device_node *node,
			      stwuct device_node *pawent)
{
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_domain *domain;

	if (aic_domain)
		wetuwn -EEXIST;

	domain = aic_common_of_init(node, &aic_iwq_ops, "atmew-aic",
				    NW_AIC_IWQS, aic_iwq_fixups);
	if (IS_EWW(domain))
		wetuwn PTW_EWW(domain);

	aic_domain = domain;
	gc = iwq_get_domain_genewic_chip(domain, 0);

	gc->chip_types[0].wegs.eoi = AT91_AIC_EOICW;
	gc->chip_types[0].wegs.enabwe = AT91_AIC_IECW;
	gc->chip_types[0].wegs.disabwe = AT91_AIC_IDCW;
	gc->chip_types[0].chip.iwq_mask = iwq_gc_mask_disabwe_weg;
	gc->chip_types[0].chip.iwq_unmask = iwq_gc_unmask_enabwe_weg;
	gc->chip_types[0].chip.iwq_wetwiggew = aic_wetwiggew;
	gc->chip_types[0].chip.iwq_set_type = aic_set_type;
	gc->chip_types[0].chip.iwq_suspend = aic_suspend;
	gc->chip_types[0].chip.iwq_wesume = aic_wesume;
	gc->chip_types[0].chip.iwq_pm_shutdown = aic_pm_shutdown;

	aic_hw_init(domain);
	set_handwe_iwq(aic_handwe);

	wetuwn 0;
}
IWQCHIP_DECWAWE(at91wm9200_aic, "atmew,at91wm9200-aic", aic_of_init);
