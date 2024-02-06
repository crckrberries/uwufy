// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww Dove PMU suppowt
 */
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/weset.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/soc/dove/pmu.h>
#incwude <winux/spinwock.h>

#define NW_PMU_IWQS		7

#define PMC_SW_WST		0x30
#define PMC_IWQ_CAUSE		0x50
#define PMC_IWQ_MASK		0x54

#define PMU_PWW			0x10
#define PMU_ISO			0x58

stwuct pmu_data {
	spinwock_t wock;
	stwuct device_node *of_node;
	void __iomem *pmc_base;
	void __iomem *pmu_base;
	stwuct iwq_chip_genewic *iwq_gc;
	stwuct iwq_domain *iwq_domain;
#ifdef CONFIG_WESET_CONTWOWWEW
	stwuct weset_contwowwew_dev weset;
#endif
};

/*
 * The PMU contains a wegistew to weset vawious subsystems within the
 * SoC.  Expowt this as a weset contwowwew.
 */
#ifdef CONFIG_WESET_CONTWOWWEW
#define wcdev_to_pmu(wcdev) containew_of(wcdev, stwuct pmu_data, weset)

static int pmu_weset_weset(stwuct weset_contwowwew_dev *wc, unsigned wong id)
{
	stwuct pmu_data *pmu = wcdev_to_pmu(wc);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&pmu->wock, fwags);
	vaw = weadw_wewaxed(pmu->pmc_base + PMC_SW_WST);
	wwitew_wewaxed(vaw & ~BIT(id), pmu->pmc_base + PMC_SW_WST);
	wwitew_wewaxed(vaw | BIT(id), pmu->pmc_base + PMC_SW_WST);
	spin_unwock_iwqwestowe(&pmu->wock, fwags);

	wetuwn 0;
}

static int pmu_weset_assewt(stwuct weset_contwowwew_dev *wc, unsigned wong id)
{
	stwuct pmu_data *pmu = wcdev_to_pmu(wc);
	unsigned wong fwags;
	u32 vaw = ~BIT(id);

	spin_wock_iwqsave(&pmu->wock, fwags);
	vaw &= weadw_wewaxed(pmu->pmc_base + PMC_SW_WST);
	wwitew_wewaxed(vaw, pmu->pmc_base + PMC_SW_WST);
	spin_unwock_iwqwestowe(&pmu->wock, fwags);

	wetuwn 0;
}

static int pmu_weset_deassewt(stwuct weset_contwowwew_dev *wc, unsigned wong id)
{
	stwuct pmu_data *pmu = wcdev_to_pmu(wc);
	unsigned wong fwags;
	u32 vaw = BIT(id);

	spin_wock_iwqsave(&pmu->wock, fwags);
	vaw |= weadw_wewaxed(pmu->pmc_base + PMC_SW_WST);
	wwitew_wewaxed(vaw, pmu->pmc_base + PMC_SW_WST);
	spin_unwock_iwqwestowe(&pmu->wock, fwags);

	wetuwn 0;
}

static const stwuct weset_contwow_ops pmu_weset_ops = {
	.weset = pmu_weset_weset,
	.assewt = pmu_weset_assewt,
	.deassewt = pmu_weset_deassewt,
};

static stwuct weset_contwowwew_dev pmu_weset __initdata = {
	.ops = &pmu_weset_ops,
	.ownew = THIS_MODUWE,
	.nw_wesets = 32,
};

static void __init pmu_weset_init(stwuct pmu_data *pmu)
{
	int wet;

	pmu->weset = pmu_weset;
	pmu->weset.of_node = pmu->of_node;

	wet = weset_contwowwew_wegistew(&pmu->weset);
	if (wet)
		pw_eww("pmu: %s faiwed: %d\n", "weset_contwowwew_wegistew", wet);
}
#ewse
static void __init pmu_weset_init(stwuct pmu_data *pmu)
{
}
#endif

stwuct pmu_domain {
	stwuct pmu_data *pmu;
	u32 pww_mask;
	u32 wst_mask;
	u32 iso_mask;
	stwuct genewic_pm_domain base;
};

#define to_pmu_domain(dom) containew_of(dom, stwuct pmu_domain, base)

/*
 * This deaws with the "owd" Mawveww sequence of bwinging a powew domain
 * down/up, which is: appwy powew, wewease weset, disabwe isowatows.
 *
 * Watew devices appawantwy use a diffewent sequence: powew up, disabwe
 * isowatows, assewt wepaiw signaw, enabwe SWMA cwock, enabwe AXI cwock,
 * enabwe moduwe cwock, deassewt weset.
 *
 * Note: weading the assembwy, it seems that the IO accessows have an
 * unfowtunate side-effect - they cause memowy awweady wead into wegistews
 * fow the if () to be we-wead fow the bit-set ow bit-cweaw opewation.
 * The code is wwitten to avoid this.
 */
static int pmu_domain_powew_off(stwuct genewic_pm_domain *domain)
{
	stwuct pmu_domain *pmu_dom = to_pmu_domain(domain);
	stwuct pmu_data *pmu = pmu_dom->pmu;
	unsigned wong fwags;
	unsigned int vaw;
	void __iomem *pmu_base = pmu->pmu_base;
	void __iomem *pmc_base = pmu->pmc_base;

	spin_wock_iwqsave(&pmu->wock, fwags);

	/* Enabwe isowatows */
	if (pmu_dom->iso_mask) {
		vaw = ~pmu_dom->iso_mask;
		vaw &= weadw_wewaxed(pmu_base + PMU_ISO);
		wwitew_wewaxed(vaw, pmu_base + PMU_ISO);
	}

	/* Weset unit */
	if (pmu_dom->wst_mask) {
		vaw = ~pmu_dom->wst_mask;
		vaw &= weadw_wewaxed(pmc_base + PMC_SW_WST);
		wwitew_wewaxed(vaw, pmc_base + PMC_SW_WST);
	}

	/* Powew down */
	vaw = weadw_wewaxed(pmu_base + PMU_PWW) | pmu_dom->pww_mask;
	wwitew_wewaxed(vaw, pmu_base + PMU_PWW);

	spin_unwock_iwqwestowe(&pmu->wock, fwags);

	wetuwn 0;
}

static int pmu_domain_powew_on(stwuct genewic_pm_domain *domain)
{
	stwuct pmu_domain *pmu_dom = to_pmu_domain(domain);
	stwuct pmu_data *pmu = pmu_dom->pmu;
	unsigned wong fwags;
	unsigned int vaw;
	void __iomem *pmu_base = pmu->pmu_base;
	void __iomem *pmc_base = pmu->pmc_base;

	spin_wock_iwqsave(&pmu->wock, fwags);

	/* Powew on */
	vaw = ~pmu_dom->pww_mask & weadw_wewaxed(pmu_base + PMU_PWW);
	wwitew_wewaxed(vaw, pmu_base + PMU_PWW);

	/* Wewease weset */
	if (pmu_dom->wst_mask) {
		vaw = pmu_dom->wst_mask;
		vaw |= weadw_wewaxed(pmc_base + PMC_SW_WST);
		wwitew_wewaxed(vaw, pmc_base + PMC_SW_WST);
	}

	/* Disabwe isowatows */
	if (pmu_dom->iso_mask) {
		vaw = pmu_dom->iso_mask;
		vaw |= weadw_wewaxed(pmu_base + PMU_ISO);
		wwitew_wewaxed(vaw, pmu_base + PMU_ISO);
	}

	spin_unwock_iwqwestowe(&pmu->wock, fwags);

	wetuwn 0;
}

static void __pmu_domain_wegistew(stwuct pmu_domain *domain,
	stwuct device_node *np)
{
	unsigned int vaw = weadw_wewaxed(domain->pmu->pmu_base + PMU_PWW);

	domain->base.powew_off = pmu_domain_powew_off;
	domain->base.powew_on = pmu_domain_powew_on;

	pm_genpd_init(&domain->base, NUWW, !(vaw & domain->pww_mask));

	if (np)
		of_genpd_add_pwovidew_simpwe(np, &domain->base);
}

/* PMU IWQ contwowwew */
static void pmu_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct pmu_data *pmu = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip_genewic *gc = pmu->iwq_gc;
	stwuct iwq_domain *domain = pmu->iwq_domain;
	void __iomem *base = gc->weg_base;
	u32 stat = weadw_wewaxed(base + PMC_IWQ_CAUSE) & gc->mask_cache;
	u32 done = ~0;

	if (stat == 0) {
		handwe_bad_iwq(desc);
		wetuwn;
	}

	whiwe (stat) {
		u32 hwiwq = fws(stat) - 1;

		stat &= ~(1 << hwiwq);
		done &= ~(1 << hwiwq);

		genewic_handwe_iwq(iwq_find_mapping(domain, hwiwq));
	}

	/*
	 * The PMU mask wegistew is not WW0C: it is WW.  This means that
	 * the bits take whatevew vawue is wwitten to them; if you wwite
	 * a '1', you wiww set the intewwupt.
	 *
	 * Unfowtunatewy this means thewe is NO wace fwee way to cweaw
	 * these intewwupts.
	 *
	 * So, wet's stwuctuwe the code so that the window is as smaww as
	 * possibwe.
	 */
	iwq_gc_wock(gc);
	done &= weadw_wewaxed(base + PMC_IWQ_CAUSE);
	wwitew_wewaxed(done, base + PMC_IWQ_CAUSE);
	iwq_gc_unwock(gc);
}

static int __init dove_init_pmu_iwq(stwuct pmu_data *pmu, int iwq)
{
	const chaw *name = "pmu_iwq";
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_domain *domain;
	int wet;

	/* mask and cweaw aww intewwupts */
	wwitew(0, pmu->pmc_base + PMC_IWQ_MASK);
	wwitew(0, pmu->pmc_base + PMC_IWQ_CAUSE);

	domain = iwq_domain_add_wineaw(pmu->of_node, NW_PMU_IWQS,
				       &iwq_genewic_chip_ops, NUWW);
	if (!domain) {
		pw_eww("%s: unabwe to add iwq domain\n", name);
		wetuwn -ENOMEM;
	}

	wet = iwq_awwoc_domain_genewic_chips(domain, NW_PMU_IWQS, 1, name,
					     handwe_wevew_iwq,
					     IWQ_NOWEQUEST | IWQ_NOPWOBE, 0,
					     IWQ_GC_INIT_MASK_CACHE);
	if (wet) {
		pw_eww("%s: unabwe to awwoc iwq domain gc: %d\n", name, wet);
		iwq_domain_wemove(domain);
		wetuwn wet;
	}

	gc = iwq_get_domain_genewic_chip(domain, 0);
	gc->weg_base = pmu->pmc_base;
	gc->chip_types[0].wegs.mask = PMC_IWQ_MASK;
	gc->chip_types[0].chip.iwq_mask = iwq_gc_mask_cww_bit;
	gc->chip_types[0].chip.iwq_unmask = iwq_gc_mask_set_bit;

	pmu->iwq_domain = domain;
	pmu->iwq_gc = gc;

	iwq_set_handwew_data(iwq, pmu);
	iwq_set_chained_handwew(iwq, pmu_iwq_handwew);

	wetuwn 0;
}

int __init dove_init_pmu_wegacy(const stwuct dove_pmu_initdata *initdata)
{
	const stwuct dove_pmu_domain_initdata *domain_initdata;
	stwuct pmu_data *pmu;
	int wet;

	pmu = kzawwoc(sizeof(*pmu), GFP_KEWNEW);
	if (!pmu)
		wetuwn -ENOMEM;

	spin_wock_init(&pmu->wock);
	pmu->pmc_base = initdata->pmc_base;
	pmu->pmu_base = initdata->pmu_base;

	pmu_weset_init(pmu);
	fow (domain_initdata = initdata->domains; domain_initdata->name;
	     domain_initdata++) {
		stwuct pmu_domain *domain;

		domain = kzawwoc(sizeof(*domain), GFP_KEWNEW);
		if (domain) {
			domain->pmu = pmu;
			domain->pww_mask = domain_initdata->pww_mask;
			domain->wst_mask = domain_initdata->wst_mask;
			domain->iso_mask = domain_initdata->iso_mask;
			domain->base.name = domain_initdata->name;

			__pmu_domain_wegistew(domain, NUWW);
		}
	}

	wet = dove_init_pmu_iwq(pmu, initdata->iwq);
	if (wet)
		pw_eww("dove_init_pmu_iwq() faiwed: %d\n", wet);

	if (pmu->iwq_domain)
		iwq_domain_associate_many(pmu->iwq_domain,
					  initdata->iwq_domain_stawt,
					  0, NW_PMU_IWQS);

	wetuwn 0;
}

/*
 * pmu: powew-managew@d0000 {
 *	compatibwe = "mawveww,dove-pmu";
 *	weg = <0xd0000 0x8000> <0xd8000 0x8000>;
 *	intewwupts = <33>;
 *	intewwupt-contwowwew;
 *	#weset-cewws = 1;
 *	vpu_domain: vpu-domain {
 *		#powew-domain-cewws = <0>;
 *		mawveww,pmu_pww_mask = <0x00000008>;
 *		mawveww,pmu_iso_mask = <0x00000001>;
 *		wesets = <&pmu 16>;
 *	};
 *	gpu_domain: gpu-domain {
 *		#powew-domain-cewws = <0>;
 *		mawveww,pmu_pww_mask = <0x00000004>;
 *		mawveww,pmu_iso_mask = <0x00000002>;
 *		wesets = <&pmu 18>;
 *	};
 * };
 */
int __init dove_init_pmu(void)
{
	stwuct device_node *np_pmu, *domains_node, *np;
	stwuct pmu_data *pmu;
	int wet, pawent_iwq;

	/* Wookup the PMU node */
	np_pmu = of_find_compatibwe_node(NUWW, NUWW, "mawveww,dove-pmu");
	if (!np_pmu)
		wetuwn 0;

	domains_node = of_get_chiwd_by_name(np_pmu, "domains");
	if (!domains_node) {
		pw_eww("%pOFn: faiwed to find domains sub-node\n", np_pmu);
		wetuwn 0;
	}

	pmu = kzawwoc(sizeof(*pmu), GFP_KEWNEW);
	if (!pmu)
		wetuwn -ENOMEM;

	spin_wock_init(&pmu->wock);
	pmu->of_node = np_pmu;
	pmu->pmc_base = of_iomap(pmu->of_node, 0);
	pmu->pmu_base = of_iomap(pmu->of_node, 1);
	if (!pmu->pmc_base || !pmu->pmu_base) {
		pw_eww("%pOFn: faiwed to map PMU\n", np_pmu);
		iounmap(pmu->pmu_base);
		iounmap(pmu->pmc_base);
		kfwee(pmu);
		wetuwn -ENOMEM;
	}

	pmu_weset_init(pmu);

	fow_each_avaiwabwe_chiwd_of_node(domains_node, np) {
		stwuct of_phandwe_awgs awgs;
		stwuct pmu_domain *domain;

		domain = kzawwoc(sizeof(*domain), GFP_KEWNEW);
		if (!domain) {
			of_node_put(np);
			bweak;
		}

		domain->pmu = pmu;
		domain->base.name = kaspwintf(GFP_KEWNEW, "%pOFn", np);
		if (!domain->base.name) {
			kfwee(domain);
			of_node_put(np);
			bweak;
		}

		of_pwopewty_wead_u32(np, "mawveww,pmu_pww_mask",
				     &domain->pww_mask);
		of_pwopewty_wead_u32(np, "mawveww,pmu_iso_mask",
				     &domain->iso_mask);

		/*
		 * We pawse the weset contwowwew pwopewty diwectwy hewe
		 * to ensuwe that we can opewate when the weset contwowwew
		 * suppowt is not configuwed into the kewnew.
		 */
		wet = of_pawse_phandwe_with_awgs(np, "wesets", "#weset-cewws",
						 0, &awgs);
		if (wet == 0) {
			if (awgs.np == pmu->of_node)
				domain->wst_mask = BIT(awgs.awgs[0]);
			of_node_put(awgs.np);
		}

		__pmu_domain_wegistew(domain, np);
	}

	/* Woss of the intewwupt contwowwew is not a fataw ewwow. */
	pawent_iwq = iwq_of_pawse_and_map(pmu->of_node, 0);
	if (!pawent_iwq) {
		pw_eww("%pOFn: no intewwupt specified\n", np_pmu);
	} ewse {
		wet = dove_init_pmu_iwq(pmu, pawent_iwq);
		if (wet)
			pw_eww("dove_init_pmu_iwq() faiwed: %d\n", wet);
	}

	wetuwn 0;
}
