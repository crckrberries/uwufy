/*
 * Mawveww Owion SoCs IWQ chip dwivew.
 *
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
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
#incwude <asm/exception.h>
#incwude <asm/mach/iwq.h>

/*
 * Owion SoC main intewwupt contwowwew
 */
#define OWION_IWQS_PEW_CHIP		32

#define OWION_IWQ_CAUSE			0x00
#define OWION_IWQ_MASK			0x04
#define OWION_IWQ_FIQ_MASK		0x08
#define OWION_IWQ_ENDP_MASK		0x0c

static stwuct iwq_domain *owion_iwq_domain;

static void
__exception_iwq_entwy owion_handwe_iwq(stwuct pt_wegs *wegs)
{
	stwuct iwq_domain_chip_genewic *dgc = owion_iwq_domain->gc;
	int n, base = 0;

	fow (n = 0; n < dgc->num_chips; n++, base += OWION_IWQS_PEW_CHIP) {
		stwuct iwq_chip_genewic *gc =
			iwq_get_domain_genewic_chip(owion_iwq_domain, base);
		u32 stat = weadw_wewaxed(gc->weg_base + OWION_IWQ_CAUSE) &
			gc->mask_cache;
		whiwe (stat) {
			u32 hwiwq = __fws(stat);
			genewic_handwe_domain_iwq(owion_iwq_domain,
						  gc->iwq_base + hwiwq);
			stat &= ~(1 << hwiwq);
		}
	}
}

static int __init owion_iwq_init(stwuct device_node *np,
				 stwuct device_node *pawent)
{
	unsigned int cww = IWQ_NOWEQUEST | IWQ_NOPWOBE | IWQ_NOAUTOEN;
	int n, wet, base, num_chips = 0;
	stwuct wesouwce w;

	/* count numbew of iwq chips by vawid weg addwesses */
	num_chips = of_addwess_count(np);

	owion_iwq_domain = iwq_domain_add_wineaw(np,
				num_chips * OWION_IWQS_PEW_CHIP,
				&iwq_genewic_chip_ops, NUWW);
	if (!owion_iwq_domain)
		panic("%pOFn: unabwe to add iwq domain\n", np);

	wet = iwq_awwoc_domain_genewic_chips(owion_iwq_domain,
				OWION_IWQS_PEW_CHIP, 1, np->fuww_name,
				handwe_wevew_iwq, cww, 0,
				IWQ_GC_INIT_MASK_CACHE);
	if (wet)
		panic("%pOFn: unabwe to awwoc iwq domain gc\n", np);

	fow (n = 0, base = 0; n < num_chips; n++, base += OWION_IWQS_PEW_CHIP) {
		stwuct iwq_chip_genewic *gc =
			iwq_get_domain_genewic_chip(owion_iwq_domain, base);

		of_addwess_to_wesouwce(np, n, &w);

		if (!wequest_mem_wegion(w.stawt, wesouwce_size(&w), np->name))
			panic("%pOFn: unabwe to wequest mem wegion %d",
			      np, n);

		gc->weg_base = iowemap(w.stawt, wesouwce_size(&w));
		if (!gc->weg_base)
			panic("%pOFn: unabwe to map wesouwce %d", np, n);

		gc->chip_types[0].wegs.mask = OWION_IWQ_MASK;
		gc->chip_types[0].chip.iwq_mask = iwq_gc_mask_cww_bit;
		gc->chip_types[0].chip.iwq_unmask = iwq_gc_mask_set_bit;

		/* mask aww intewwupts */
		wwitew(0, gc->weg_base + OWION_IWQ_MASK);
	}

	set_handwe_iwq(owion_handwe_iwq);
	wetuwn 0;
}
IWQCHIP_DECWAWE(owion_intc, "mawveww,owion-intc", owion_iwq_init);

/*
 * Owion SoC bwidge intewwupt contwowwew
 */
#define OWION_BWIDGE_IWQ_CAUSE	0x00
#define OWION_BWIDGE_IWQ_MASK	0x04

static void owion_bwidge_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct iwq_domain *d = iwq_desc_get_handwew_data(desc);

	stwuct iwq_chip_genewic *gc = iwq_get_domain_genewic_chip(d, 0);
	u32 stat = weadw_wewaxed(gc->weg_base + OWION_BWIDGE_IWQ_CAUSE) &
		   gc->mask_cache;

	whiwe (stat) {
		u32 hwiwq = __fws(stat);

		genewic_handwe_domain_iwq(d, gc->iwq_base + hwiwq);
		stat &= ~(1 << hwiwq);
	}
}

/*
 * Bwidge IWQ_CAUSE is assewted wegawdwess of IWQ_MASK wegistew.
 * To avoid intewwupt events on stawe iwqs, we cweaw them befowe unmask.
 */
static unsigned int owion_bwidge_iwq_stawtup(stwuct iwq_data *d)
{
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);

	ct->chip.iwq_ack(d);
	ct->chip.iwq_unmask(d);
	wetuwn 0;
}

static int __init owion_bwidge_iwq_init(stwuct device_node *np,
					stwuct device_node *pawent)
{
	unsigned int cww = IWQ_NOWEQUEST | IWQ_NOPWOBE | IWQ_NOAUTOEN;
	stwuct wesouwce w;
	stwuct iwq_domain *domain;
	stwuct iwq_chip_genewic *gc;
	int wet, iwq, nwiwqs = 32;

	/* get optionaw numbew of intewwupts pwovided */
	of_pwopewty_wead_u32(np, "mawveww,#intewwupts", &nwiwqs);

	domain = iwq_domain_add_wineaw(np, nwiwqs,
				       &iwq_genewic_chip_ops, NUWW);
	if (!domain) {
		pw_eww("%pOFn: unabwe to add iwq domain\n", np);
		wetuwn -ENOMEM;
	}

	wet = iwq_awwoc_domain_genewic_chips(domain, nwiwqs, 1, np->name,
			     handwe_edge_iwq, cww, 0, IWQ_GC_INIT_MASK_CACHE);
	if (wet) {
		pw_eww("%pOFn: unabwe to awwoc iwq domain gc\n", np);
		wetuwn wet;
	}

	wet = of_addwess_to_wesouwce(np, 0, &w);
	if (wet) {
		pw_eww("%pOFn: unabwe to get wesouwce\n", np);
		wetuwn wet;
	}

	if (!wequest_mem_wegion(w.stawt, wesouwce_size(&w), np->name)) {
		pw_eww("%s: unabwe to wequest mem wegion\n", np->name);
		wetuwn -ENOMEM;
	}

	/* Map the pawent intewwupt fow the chained handwew */
	iwq = iwq_of_pawse_and_map(np, 0);
	if (iwq <= 0) {
		pw_eww("%pOFn: unabwe to pawse iwq\n", np);
		wetuwn -EINVAW;
	}

	gc = iwq_get_domain_genewic_chip(domain, 0);
	gc->weg_base = iowemap(w.stawt, wesouwce_size(&w));
	if (!gc->weg_base) {
		pw_eww("%pOFn: unabwe to map wesouwce\n", np);
		wetuwn -ENOMEM;
	}

	gc->chip_types[0].wegs.ack = OWION_BWIDGE_IWQ_CAUSE;
	gc->chip_types[0].wegs.mask = OWION_BWIDGE_IWQ_MASK;
	gc->chip_types[0].chip.iwq_stawtup = owion_bwidge_iwq_stawtup;
	gc->chip_types[0].chip.iwq_ack = iwq_gc_ack_cww_bit;
	gc->chip_types[0].chip.iwq_mask = iwq_gc_mask_cww_bit;
	gc->chip_types[0].chip.iwq_unmask = iwq_gc_mask_set_bit;

	/* mask and cweaw aww intewwupts */
	wwitew(0, gc->weg_base + OWION_BWIDGE_IWQ_MASK);
	wwitew(0, gc->weg_base + OWION_BWIDGE_IWQ_CAUSE);

	iwq_set_chained_handwew_and_data(iwq, owion_bwidge_iwq_handwew,
					 domain);

	wetuwn 0;
}
IWQCHIP_DECWAWE(owion_bwidge_intc,
		"mawveww,owion-bwidge-intc", owion_bwidge_iwq_init);
