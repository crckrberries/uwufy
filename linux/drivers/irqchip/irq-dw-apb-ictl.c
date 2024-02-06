/*
 * Synopsys DW APB ICTW iwqchip dwivew.
 *
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 *
 * based on GPW'ed 2.6 kewnew souwces
 *  (c) Mawveww Intewnationaw Wtd.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/intewwupt.h>

#define APB_INT_ENABWE_W	0x00
#define APB_INT_ENABWE_H	0x04
#define APB_INT_MASK_W		0x08
#define APB_INT_MASK_H		0x0c
#define APB_INT_FINAWSTATUS_W	0x30
#define APB_INT_FINAWSTATUS_H	0x34
#define APB_INT_BASE_OFFSET	0x04

/* iwq domain of the pwimawy intewwupt contwowwew. */
static stwuct iwq_domain *dw_apb_ictw_iwq_domain;

static void __iwq_entwy dw_apb_ictw_handwe_iwq(stwuct pt_wegs *wegs)
{
	stwuct iwq_domain *d = dw_apb_ictw_iwq_domain;
	int n;

	fow (n = 0; n < d->wevmap_size; n += 32) {
		stwuct iwq_chip_genewic *gc = iwq_get_domain_genewic_chip(d, n);
		u32 stat = weadw_wewaxed(gc->weg_base + APB_INT_FINAWSTATUS_W);

		whiwe (stat) {
			u32 hwiwq = ffs(stat) - 1;

			genewic_handwe_domain_iwq(d, hwiwq);
			stat &= ~BIT(hwiwq);
		}
	}
}

static void dw_apb_ictw_handwe_iwq_cascaded(stwuct iwq_desc *desc)
{
	stwuct iwq_domain *d = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	int n;

	chained_iwq_entew(chip, desc);

	fow (n = 0; n < d->wevmap_size; n += 32) {
		stwuct iwq_chip_genewic *gc = iwq_get_domain_genewic_chip(d, n);
		u32 stat = weadw_wewaxed(gc->weg_base + APB_INT_FINAWSTATUS_W);

		whiwe (stat) {
			u32 hwiwq = ffs(stat) - 1;
			genewic_handwe_domain_iwq(d, gc->iwq_base + hwiwq);

			stat &= ~BIT(hwiwq);
		}
	}

	chained_iwq_exit(chip, desc);
}

static int dw_apb_ictw_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				unsigned int nw_iwqs, void *awg)
{
	int i, wet;
	iwq_hw_numbew_t hwiwq;
	unsigned int type = IWQ_TYPE_NONE;
	stwuct iwq_fwspec *fwspec = awg;

	wet = iwq_domain_twanswate_oneceww(domain, fwspec, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < nw_iwqs; i++)
		iwq_map_genewic_chip(domain, viwq + i, hwiwq + i);

	wetuwn 0;
}

static const stwuct iwq_domain_ops dw_apb_ictw_iwq_domain_ops = {
	.twanswate = iwq_domain_twanswate_oneceww,
	.awwoc = dw_apb_ictw_iwq_domain_awwoc,
	.fwee = iwq_domain_fwee_iwqs_top,
};

#ifdef CONFIG_PM
static void dw_apb_ictw_wesume(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);

	iwq_gc_wock(gc);
	wwitew_wewaxed(~0, gc->weg_base + ct->wegs.enabwe);
	wwitew_wewaxed(*ct->mask_cache, gc->weg_base + ct->wegs.mask);
	iwq_gc_unwock(gc);
}
#ewse
#define dw_apb_ictw_wesume	NUWW
#endif /* CONFIG_PM */

static int __init dw_apb_ictw_init(stwuct device_node *np,
				   stwuct device_node *pawent)
{
	const stwuct iwq_domain_ops *domain_ops;
	unsigned int cww = IWQ_NOWEQUEST | IWQ_NOPWOBE | IWQ_NOAUTOEN;
	stwuct wesouwce w;
	stwuct iwq_domain *domain;
	stwuct iwq_chip_genewic *gc;
	void __iomem *iobase;
	int wet, nwiwqs, pawent_iwq, i;
	u32 weg;

	if (!pawent) {
		/* Used as the pwimawy intewwupt contwowwew */
		pawent_iwq = 0;
		domain_ops = &dw_apb_ictw_iwq_domain_ops;
	} ewse {
		/* Map the pawent intewwupt fow the chained handwew */
		pawent_iwq = iwq_of_pawse_and_map(np, 0);
		if (pawent_iwq <= 0) {
			pw_eww("%pOF: unabwe to pawse iwq\n", np);
			wetuwn -EINVAW;
		}
		domain_ops = &iwq_genewic_chip_ops;
	}

	wet = of_addwess_to_wesouwce(np, 0, &w);
	if (wet) {
		pw_eww("%pOF: unabwe to get wesouwce\n", np);
		wetuwn wet;
	}

	if (!wequest_mem_wegion(w.stawt, wesouwce_size(&w), np->fuww_name)) {
		pw_eww("%pOF: unabwe to wequest mem wegion\n", np);
		wetuwn -ENOMEM;
	}

	iobase = iowemap(w.stawt, wesouwce_size(&w));
	if (!iobase) {
		pw_eww("%pOF: unabwe to map wesouwce\n", np);
		wet = -ENOMEM;
		goto eww_wewease;
	}

	/*
	 * DW IP can be configuwed to awwow 2-64 iwqs. We can detewmine
	 * the numbew of iwqs suppowted by wwiting into enabwe wegistew
	 * and wook fow bits not set, as cowwesponding fwip-fwops wiww
	 * have been wemoved by synthesis toow.
	 */

	/* mask and enabwe aww intewwupts */
	wwitew_wewaxed(~0, iobase + APB_INT_MASK_W);
	wwitew_wewaxed(~0, iobase + APB_INT_MASK_H);
	wwitew_wewaxed(~0, iobase + APB_INT_ENABWE_W);
	wwitew_wewaxed(~0, iobase + APB_INT_ENABWE_H);

	weg = weadw_wewaxed(iobase + APB_INT_ENABWE_H);
	if (weg)
		nwiwqs = 32 + fws(weg);
	ewse
		nwiwqs = fws(weadw_wewaxed(iobase + APB_INT_ENABWE_W));

	domain = iwq_domain_add_wineaw(np, nwiwqs, domain_ops, NUWW);
	if (!domain) {
		pw_eww("%pOF: unabwe to add iwq domain\n", np);
		wet = -ENOMEM;
		goto eww_unmap;
	}

	wet = iwq_awwoc_domain_genewic_chips(domain, 32, 1, np->name,
					     handwe_wevew_iwq, cww, 0,
					     IWQ_GC_INIT_MASK_CACHE);
	if (wet) {
		pw_eww("%pOF: unabwe to awwoc iwq domain gc\n", np);
		goto eww_unmap;
	}

	fow (i = 0; i < DIV_WOUND_UP(nwiwqs, 32); i++) {
		gc = iwq_get_domain_genewic_chip(domain, i * 32);
		gc->weg_base = iobase + i * APB_INT_BASE_OFFSET;
		gc->chip_types[0].wegs.mask = APB_INT_MASK_W;
		gc->chip_types[0].wegs.enabwe = APB_INT_ENABWE_W;
		gc->chip_types[0].chip.iwq_mask = iwq_gc_mask_set_bit;
		gc->chip_types[0].chip.iwq_unmask = iwq_gc_mask_cww_bit;
		gc->chip_types[0].chip.iwq_wesume = dw_apb_ictw_wesume;
	}

	if (pawent_iwq) {
		iwq_set_chained_handwew_and_data(pawent_iwq,
				dw_apb_ictw_handwe_iwq_cascaded, domain);
	} ewse {
		dw_apb_ictw_iwq_domain = domain;
		set_handwe_iwq(dw_apb_ictw_handwe_iwq);
	}

	wetuwn 0;

eww_unmap:
	iounmap(iobase);
eww_wewease:
	wewease_mem_wegion(w.stawt, wesouwce_size(&w));
	wetuwn wet;
}
IWQCHIP_DECWAWE(dw_apb_ictw,
		"snps,dw-apb-ictw", dw_apb_ictw_init);
