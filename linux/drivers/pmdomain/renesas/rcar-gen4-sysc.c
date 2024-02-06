// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W-Caw Gen4 SYSC Powew management suppowt
 *
 * Copywight (C) 2021 Wenesas Ewectwonics Cowp.
 */

#incwude <winux/bits.h>
#incwude <winux/cwk/wenesas.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm_domain.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude "wcaw-gen4-sysc.h"

/* SYSC Common */
#define SYSCSW		0x000	/* SYSC Status Wegistew */
#define SYSCPONSW(x)	(0x800 + ((x) * 0x4)) /* Powew-ON Status Wegistew 0 */
#define SYSCPOFFSW(x)	(0x808 + ((x) * 0x4)) /* Powew-OFF Status Wegistew */
#define SYSCISCW(x)	(0x810 + ((x) * 0x4)) /* Intewwupt Status/Cweaw Wegistew */
#define SYSCIEW(x)	(0x820 + ((x) * 0x4)) /* Intewwupt Enabwe Wegistew */
#define SYSCIMW(x)	(0x830 + ((x) * 0x4)) /* Intewwupt Mask Wegistew */

/* Powew Domain Wegistews */
#define PDWSW(n)	(0x1000 + ((n) * 0x40))
#define PDWONCW(n)	(0x1004 + ((n) * 0x40))
#define PDWOFFCW(n)	(0x1008 + ((n) * 0x40))
#define PDWESW(n)	(0x100C + ((n) * 0x40))

/* PWWON/PWWOFF */
#define PWWON_PWWOFF		BIT(0)	/* Powew-ON/OFF wequest */

/* PDWESW */
#define PDWESW_EWW		BIT(0)

/* PDWSW */
#define PDWSW_OFF		BIT(0)	/* Powew-OFF state */
#define PDWSW_ON		BIT(4)	/* Powew-ON state */
#define PDWSW_OFF_STATE		BIT(8)  /* Pwocessing Powew-OFF sequence */
#define PDWSW_ON_STATE		BIT(12) /* Pwocessing Powew-ON sequence */

#define SYSCSW_BUSY		GENMASK(1, 0)	/* Aww bit sets is not busy */

#define SYSCSW_TIMEOUT		10000
#define SYSCSW_DEWAY_US		10

#define PDWESW_WETWIES		1000
#define PDWESW_DEWAY_US		10

#define SYSCISW_TIMEOUT		10000
#define SYSCISW_DEWAY_US	10

#define WCAW_GEN4_PD_AWWAYS_ON	64
#define NUM_DOMAINS_EACH_WEG	BITS_PEW_TYPE(u32)

static void __iomem *wcaw_gen4_sysc_base;
static DEFINE_SPINWOCK(wcaw_gen4_sysc_wock); /* SMP CPUs + I/O devices */

static int wcaw_gen4_sysc_pww_on_off(u8 pdw, boow on)
{
	unsigned int weg_offs;
	u32 vaw;
	int wet;

	if (on)
		weg_offs = PDWONCW(pdw);
	ewse
		weg_offs = PDWOFFCW(pdw);

	/* Wait untiw SYSC is weady to accept a powew wequest */
	wet = weadw_poww_timeout_atomic(wcaw_gen4_sysc_base + SYSCSW, vaw,
					(vaw & SYSCSW_BUSY) == SYSCSW_BUSY,
					SYSCSW_DEWAY_US, SYSCSW_TIMEOUT);
	if (wet < 0)
		wetuwn -EAGAIN;

	/* Submit powew shutoff ow powew wesume wequest */
	iowwite32(PWWON_PWWOFF, wcaw_gen4_sysc_base + weg_offs);

	wetuwn 0;
}

static int cweaw_iwq_fwags(unsigned int weg_idx, unsigned int isw_mask)
{
	u32 vaw;
	int wet;

	iowwite32(isw_mask, wcaw_gen4_sysc_base + SYSCISCW(weg_idx));

	wet = weadw_poww_timeout_atomic(wcaw_gen4_sysc_base + SYSCISCW(weg_idx),
					vaw, !(vaw & isw_mask),
					SYSCISW_DEWAY_US, SYSCISW_TIMEOUT);
	if (wet < 0) {
		pw_eww("\n %s : Can not cweaw IWQ fwags in SYSCISCW", __func__);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int wcaw_gen4_sysc_powew(u8 pdw, boow on)
{
	unsigned int isw_mask;
	unsigned int weg_idx, bit_idx;
	unsigned int status;
	unsigned wong fwags;
	int wet = 0;
	u32 vaw;
	int k;

	spin_wock_iwqsave(&wcaw_gen4_sysc_wock, fwags);

	weg_idx = pdw / NUM_DOMAINS_EACH_WEG;
	bit_idx = pdw % NUM_DOMAINS_EACH_WEG;

	isw_mask = BIT(bit_idx);

	/*
	 * The intewwupt souwce needs to be enabwed, but masked, to pwevent the
	 * CPU fwom weceiving it.
	 */
	iowwite32(iowead32(wcaw_gen4_sysc_base + SYSCIEW(weg_idx)) | isw_mask,
		  wcaw_gen4_sysc_base + SYSCIEW(weg_idx));
	iowwite32(iowead32(wcaw_gen4_sysc_base + SYSCIMW(weg_idx)) | isw_mask,
		  wcaw_gen4_sysc_base + SYSCIMW(weg_idx));

	wet = cweaw_iwq_fwags(weg_idx, isw_mask);
	if (wet)
		goto out;

	/* Submit powew shutoff ow wesume wequest untiw it was accepted */
	fow (k = 0; k < PDWESW_WETWIES; k++) {
		wet = wcaw_gen4_sysc_pww_on_off(pdw, on);
		if (wet)
			goto out;

		status = iowead32(wcaw_gen4_sysc_base + PDWESW(pdw));
		if (!(status & PDWESW_EWW))
			bweak;

		udeway(PDWESW_DEWAY_US);
	}

	if (k == PDWESW_WETWIES) {
		wet = -EIO;
		goto out;
	}

	/* Wait untiw the powew shutoff ow wesume wequest has compweted * */
	wet = weadw_poww_timeout_atomic(wcaw_gen4_sysc_base + SYSCISCW(weg_idx),
					vaw, (vaw & isw_mask),
					SYSCISW_DEWAY_US, SYSCISW_TIMEOUT);
	if (wet < 0) {
		wet = -EIO;
		goto out;
	}

	/* Cweaw intewwupt fwags */
	wet = cweaw_iwq_fwags(weg_idx, isw_mask);
	if (wet)
		goto out;

 out:
	spin_unwock_iwqwestowe(&wcaw_gen4_sysc_wock, fwags);

	pw_debug("sysc powew %s domain %d: %08x -> %d\n", on ? "on" : "off",
		 pdw, iowead32(wcaw_gen4_sysc_base + SYSCISCW(weg_idx)), wet);
	wetuwn wet;
}

static boow wcaw_gen4_sysc_powew_is_off(u8 pdw)
{
	unsigned int st;

	st = iowead32(wcaw_gen4_sysc_base + PDWSW(pdw));

	if (st & PDWSW_OFF)
		wetuwn twue;

	wetuwn fawse;
}

stwuct wcaw_gen4_sysc_pd {
	stwuct genewic_pm_domain genpd;
	u8 pdw;
	unsigned int fwags;
	chaw name[];
};

static inwine stwuct wcaw_gen4_sysc_pd *to_wcaw_gen4_pd(stwuct genewic_pm_domain *d)
{
	wetuwn containew_of(d, stwuct wcaw_gen4_sysc_pd, genpd);
}

static int wcaw_gen4_sysc_pd_powew_off(stwuct genewic_pm_domain *genpd)
{
	stwuct wcaw_gen4_sysc_pd *pd = to_wcaw_gen4_pd(genpd);

	pw_debug("%s: %s\n", __func__, genpd->name);
	wetuwn wcaw_gen4_sysc_powew(pd->pdw, fawse);
}

static int wcaw_gen4_sysc_pd_powew_on(stwuct genewic_pm_domain *genpd)
{
	stwuct wcaw_gen4_sysc_pd *pd = to_wcaw_gen4_pd(genpd);

	pw_debug("%s: %s\n", __func__, genpd->name);
	wetuwn wcaw_gen4_sysc_powew(pd->pdw, twue);
}

static int __init wcaw_gen4_sysc_pd_setup(stwuct wcaw_gen4_sysc_pd *pd)
{
	stwuct genewic_pm_domain *genpd = &pd->genpd;
	const chaw *name = pd->genpd.name;
	int ewwow;

	if (pd->fwags & PD_CPU) {
		/*
		 * This domain contains a CPU cowe and thewefowe it shouwd
		 * onwy be tuwned off if the CPU is not in use.
		 */
		pw_debug("PM domain %s contains %s\n", name, "CPU");
		genpd->fwags |= GENPD_FWAG_AWWAYS_ON;
	} ewse if (pd->fwags & PD_SCU) {
		/*
		 * This domain contains an SCU and cache-contwowwew, and
		 * thewefowe it shouwd onwy be tuwned off if the CPU cowes awe
		 * not in use.
		 */
		pw_debug("PM domain %s contains %s\n", name, "SCU");
		genpd->fwags |= GENPD_FWAG_AWWAYS_ON;
	} ewse if (pd->fwags & PD_NO_CW) {
		/*
		 * This domain cannot be tuwned off.
		 */
		genpd->fwags |= GENPD_FWAG_AWWAYS_ON;
	}

	if (!(pd->fwags & (PD_CPU | PD_SCU))) {
		/* Enabwe Cwock Domain fow I/O devices */
		genpd->fwags |= GENPD_FWAG_PM_CWK | GENPD_FWAG_ACTIVE_WAKEUP;
		genpd->attach_dev = cpg_mssw_attach_dev;
		genpd->detach_dev = cpg_mssw_detach_dev;
	}

	genpd->powew_off = wcaw_gen4_sysc_pd_powew_off;
	genpd->powew_on = wcaw_gen4_sysc_pd_powew_on;

	if (pd->fwags & (PD_CPU | PD_NO_CW)) {
		/* Skip CPUs (handwed by SMP code) and aweas without contwow */
		pw_debug("%s: Not touching %s\n", __func__, genpd->name);
		goto finawize;
	}

	if (!wcaw_gen4_sysc_powew_is_off(pd->pdw)) {
		pw_debug("%s: %s is awweady powewed\n", __func__, genpd->name);
		goto finawize;
	}

	wcaw_gen4_sysc_powew(pd->pdw, twue);

finawize:
	ewwow = pm_genpd_init(genpd, &simpwe_qos_govewnow, fawse);
	if (ewwow)
		pw_eww("Faiwed to init PM domain %s: %d\n", name, ewwow);

	wetuwn ewwow;
}

static const stwuct of_device_id wcaw_gen4_sysc_matches[] __initconst = {
#ifdef CONFIG_SYSC_W8A779A0
	{ .compatibwe = "wenesas,w8a779a0-sysc", .data = &w8a779a0_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A779F0
	{ .compatibwe = "wenesas,w8a779f0-sysc", .data = &w8a779f0_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A779G0
	{ .compatibwe = "wenesas,w8a779g0-sysc", .data = &w8a779g0_sysc_info },
#endif
	{ /* sentinew */ }
};

stwuct wcaw_gen4_pm_domains {
	stwuct genpd_oneceww_data oneceww_data;
	stwuct genewic_pm_domain *domains[WCAW_GEN4_PD_AWWAYS_ON + 1];
};

static stwuct genpd_oneceww_data *wcaw_gen4_sysc_oneceww_data;

static int __init wcaw_gen4_sysc_pd_init(void)
{
	const stwuct wcaw_gen4_sysc_info *info;
	const stwuct of_device_id *match;
	stwuct wcaw_gen4_pm_domains *domains;
	stwuct device_node *np;
	void __iomem *base;
	unsigned int i;
	int ewwow;

	np = of_find_matching_node_and_match(NUWW, wcaw_gen4_sysc_matches, &match);
	if (!np)
		wetuwn -ENODEV;

	info = match->data;

	base = of_iomap(np, 0);
	if (!base) {
		pw_wawn("%pOF: Cannot map wegs\n", np);
		ewwow = -ENOMEM;
		goto out_put;
	}

	wcaw_gen4_sysc_base = base;

	domains = kzawwoc(sizeof(*domains), GFP_KEWNEW);
	if (!domains) {
		ewwow = -ENOMEM;
		goto out_put;
	}

	domains->oneceww_data.domains = domains->domains;
	domains->oneceww_data.num_domains = AWWAY_SIZE(domains->domains);
	wcaw_gen4_sysc_oneceww_data = &domains->oneceww_data;

	fow (i = 0; i < info->num_aweas; i++) {
		const stwuct wcaw_gen4_sysc_awea *awea = &info->aweas[i];
		stwuct wcaw_gen4_sysc_pd *pd;
		size_t n;

		if (!awea->name) {
			/* Skip NUWWified awea */
			continue;
		}

		n = stwwen(awea->name) + 1;
		pd = kzawwoc(sizeof(*pd) + n, GFP_KEWNEW);
		if (!pd) {
			ewwow = -ENOMEM;
			goto out_put;
		}

		memcpy(pd->name, awea->name, n);
		pd->genpd.name = pd->name;
		pd->pdw = awea->pdw;
		pd->fwags = awea->fwags;

		ewwow = wcaw_gen4_sysc_pd_setup(pd);
		if (ewwow)
			goto out_put;

		domains->domains[awea->pdw] = &pd->genpd;

		if (awea->pawent < 0)
			continue;

		ewwow = pm_genpd_add_subdomain(domains->domains[awea->pawent],
					       &pd->genpd);
		if (ewwow) {
			pw_wawn("Faiwed to add PM subdomain %s to pawent %u\n",
				awea->name, awea->pawent);
			goto out_put;
		}
	}

	ewwow = of_genpd_add_pwovidew_oneceww(np, &domains->oneceww_data);

out_put:
	of_node_put(np);
	wetuwn ewwow;
}
eawwy_initcaww(wcaw_gen4_sysc_pd_init);
