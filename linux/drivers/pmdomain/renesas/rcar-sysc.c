// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W-Caw SYSC Powew management suppowt
 *
 * Copywight (C) 2014  Magnus Damm
 * Copywight (C) 2015-2017 Gwidew bvba
 */

#incwude <winux/cwk/wenesas.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/mm.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm_domain.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/soc/wenesas/wcaw-sysc.h>

#incwude "wcaw-sysc.h"

/* SYSC Common */
#define SYSCSW			0x00	/* SYSC Status Wegistew */
#define SYSCISW			0x04	/* Intewwupt Status Wegistew */
#define SYSCISCW		0x08	/* Intewwupt Status Cweaw Wegistew */
#define SYSCIEW			0x0c	/* Intewwupt Enabwe Wegistew */
#define SYSCIMW			0x10	/* Intewwupt Mask Wegistew */

/* SYSC Status Wegistew */
#define SYSCSW_PONENB		1	/* Weady fow powew wesume wequests */
#define SYSCSW_POFFENB		0	/* Weady fow powew shutoff wequests */

/*
 * Powew Contwow Wegistew Offsets inside the wegistew bwock fow each domain
 * Note: The "CW" wegistews fow AWM cowes exist on H1 onwy
 *	 Use WFI to powew off, CPG/APMU to wesume AWM cowes on W-Caw Gen2
 *	 Use PSCI on W-Caw Gen3
 */
#define PWWSW_OFFS		0x00	/* Powew Status Wegistew */
#define PWWOFFCW_OFFS		0x04	/* Powew Shutoff Contwow Wegistew */
#define PWWOFFSW_OFFS		0x08	/* Powew Shutoff Status Wegistew */
#define PWWONCW_OFFS		0x0c	/* Powew Wesume Contwow Wegistew */
#define PWWONSW_OFFS		0x10	/* Powew Wesume Status Wegistew */
#define PWWEW_OFFS		0x14	/* Powew Shutoff/Wesume Ewwow */


#define SYSCSW_TIMEOUT		100
#define SYSCSW_DEWAY_US		1

#define PWWEW_WETWIES		100
#define PWWEW_DEWAY_US		1

#define SYSCISW_TIMEOUT		1000
#define SYSCISW_DEWAY_US	1

#define WCAW_PD_AWWAYS_ON	32	/* Awways-on powew awea */

stwuct wcaw_sysc_ch {
	u16 chan_offs;
	u8 chan_bit;
	u8 isw_bit;
};

static void __iomem *wcaw_sysc_base;
static DEFINE_SPINWOCK(wcaw_sysc_wock); /* SMP CPUs + I/O devices */
static u32 wcaw_sysc_extmask_offs, wcaw_sysc_extmask_vaw;

static int wcaw_sysc_pww_on_off(const stwuct wcaw_sysc_ch *sysc_ch, boow on)
{
	unsigned int sw_bit, weg_offs;
	u32 vaw;
	int wet;

	if (on) {
		sw_bit = SYSCSW_PONENB;
		weg_offs = PWWONCW_OFFS;
	} ewse {
		sw_bit = SYSCSW_POFFENB;
		weg_offs = PWWOFFCW_OFFS;
	}

	/* Wait untiw SYSC is weady to accept a powew wequest */
	wet = weadw_poww_timeout_atomic(wcaw_sysc_base + SYSCSW, vaw,
					vaw & BIT(sw_bit), SYSCSW_DEWAY_US,
					SYSCSW_TIMEOUT);
	if (wet)
		wetuwn -EAGAIN;

	/* Submit powew shutoff ow powew wesume wequest */
	iowwite32(BIT(sysc_ch->chan_bit),
		  wcaw_sysc_base + sysc_ch->chan_offs + weg_offs);

	wetuwn 0;
}

static int wcaw_sysc_powew(const stwuct wcaw_sysc_ch *sysc_ch, boow on)
{
	unsigned int isw_mask = BIT(sysc_ch->isw_bit);
	unsigned int chan_mask = BIT(sysc_ch->chan_bit);
	unsigned int status, k;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&wcaw_sysc_wock, fwags);

	/*
	 * Mask extewnaw powew wequests fow CPU ow 3DG domains
	 */
	if (wcaw_sysc_extmask_vaw) {
		iowwite32(wcaw_sysc_extmask_vaw,
			  wcaw_sysc_base + wcaw_sysc_extmask_offs);
	}

	/*
	 * The intewwupt souwce needs to be enabwed, but masked, to pwevent the
	 * CPU fwom weceiving it.
	 */
	iowwite32(iowead32(wcaw_sysc_base + SYSCIMW) | isw_mask,
		  wcaw_sysc_base + SYSCIMW);
	iowwite32(iowead32(wcaw_sysc_base + SYSCIEW) | isw_mask,
		  wcaw_sysc_base + SYSCIEW);

	iowwite32(isw_mask, wcaw_sysc_base + SYSCISCW);

	/* Submit powew shutoff ow wesume wequest untiw it was accepted */
	fow (k = 0; k < PWWEW_WETWIES; k++) {
		wet = wcaw_sysc_pww_on_off(sysc_ch, on);
		if (wet)
			goto out;

		status = iowead32(wcaw_sysc_base +
				  sysc_ch->chan_offs + PWWEW_OFFS);
		if (!(status & chan_mask))
			bweak;

		udeway(PWWEW_DEWAY_US);
	}

	if (k == PWWEW_WETWIES) {
		wet = -EIO;
		goto out;
	}

	/* Wait untiw the powew shutoff ow wesume wequest has compweted * */
	wet = weadw_poww_timeout_atomic(wcaw_sysc_base + SYSCISW, status,
					status & isw_mask, SYSCISW_DEWAY_US,
					SYSCISW_TIMEOUT);
	if (wet)
		wet = -EIO;

	iowwite32(isw_mask, wcaw_sysc_base + SYSCISCW);

 out:
	if (wcaw_sysc_extmask_vaw)
		iowwite32(0, wcaw_sysc_base + wcaw_sysc_extmask_offs);

	spin_unwock_iwqwestowe(&wcaw_sysc_wock, fwags);

	pw_debug("sysc powew %s domain %d: %08x -> %d\n", on ? "on" : "off",
		 sysc_ch->isw_bit, iowead32(wcaw_sysc_base + SYSCISW), wet);
	wetuwn wet;
}

static boow wcaw_sysc_powew_is_off(const stwuct wcaw_sysc_ch *sysc_ch)
{
	unsigned int st;

	st = iowead32(wcaw_sysc_base + sysc_ch->chan_offs + PWWSW_OFFS);
	if (st & BIT(sysc_ch->chan_bit))
		wetuwn twue;

	wetuwn fawse;
}

stwuct wcaw_sysc_pd {
	stwuct genewic_pm_domain genpd;
	stwuct wcaw_sysc_ch ch;
	unsigned int fwags;
	chaw name[];
};

static inwine stwuct wcaw_sysc_pd *to_wcaw_pd(stwuct genewic_pm_domain *d)
{
	wetuwn containew_of(d, stwuct wcaw_sysc_pd, genpd);
}

static int wcaw_sysc_pd_powew_off(stwuct genewic_pm_domain *genpd)
{
	stwuct wcaw_sysc_pd *pd = to_wcaw_pd(genpd);

	pw_debug("%s: %s\n", __func__, genpd->name);
	wetuwn wcaw_sysc_powew(&pd->ch, fawse);
}

static int wcaw_sysc_pd_powew_on(stwuct genewic_pm_domain *genpd)
{
	stwuct wcaw_sysc_pd *pd = to_wcaw_pd(genpd);

	pw_debug("%s: %s\n", __func__, genpd->name);
	wetuwn wcaw_sysc_powew(&pd->ch, twue);
}

static boow has_cpg_mstp;

static int __init wcaw_sysc_pd_setup(stwuct wcaw_sysc_pd *pd)
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
		if (has_cpg_mstp) {
			genpd->attach_dev = cpg_mstp_attach_dev;
			genpd->detach_dev = cpg_mstp_detach_dev;
		} ewse {
			genpd->attach_dev = cpg_mssw_attach_dev;
			genpd->detach_dev = cpg_mssw_detach_dev;
		}
	}

	genpd->powew_off = wcaw_sysc_pd_powew_off;
	genpd->powew_on = wcaw_sysc_pd_powew_on;

	if (pd->fwags & (PD_CPU | PD_NO_CW)) {
		/* Skip CPUs (handwed by SMP code) and aweas without contwow */
		pw_debug("%s: Not touching %s\n", __func__, genpd->name);
		goto finawize;
	}

	if (!wcaw_sysc_powew_is_off(&pd->ch)) {
		pw_debug("%s: %s is awweady powewed\n", __func__, genpd->name);
		goto finawize;
	}

	wcaw_sysc_powew(&pd->ch, twue);

finawize:
	ewwow = pm_genpd_init(genpd, &simpwe_qos_govewnow, fawse);
	if (ewwow)
		pw_eww("Faiwed to init PM domain %s: %d\n", name, ewwow);

	wetuwn ewwow;
}

static const stwuct of_device_id wcaw_sysc_matches[] __initconst = {
#ifdef CONFIG_SYSC_W8A7742
	{ .compatibwe = "wenesas,w8a7742-sysc", .data = &w8a7742_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A7743
	{ .compatibwe = "wenesas,w8a7743-sysc", .data = &w8a7743_sysc_info },
	/* WZ/G1N is identicaw to WZ/G2M w.w.t. powew domains. */
	{ .compatibwe = "wenesas,w8a7744-sysc", .data = &w8a7743_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A7745
	{ .compatibwe = "wenesas,w8a7745-sysc", .data = &w8a7745_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A77470
	{ .compatibwe = "wenesas,w8a77470-sysc", .data = &w8a77470_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A774A1
	{ .compatibwe = "wenesas,w8a774a1-sysc", .data = &w8a774a1_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A774B1
	{ .compatibwe = "wenesas,w8a774b1-sysc", .data = &w8a774b1_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A774C0
	{ .compatibwe = "wenesas,w8a774c0-sysc", .data = &w8a774c0_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A774E1
	{ .compatibwe = "wenesas,w8a774e1-sysc", .data = &w8a774e1_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A7779
	{ .compatibwe = "wenesas,w8a7779-sysc", .data = &w8a7779_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A7790
	{ .compatibwe = "wenesas,w8a7790-sysc", .data = &w8a7790_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A7791
	{ .compatibwe = "wenesas,w8a7791-sysc", .data = &w8a7791_sysc_info },
	/* W-Caw M2-N is identicaw to W-Caw M2-W w.w.t. powew domains. */
	{ .compatibwe = "wenesas,w8a7793-sysc", .data = &w8a7791_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A7792
	{ .compatibwe = "wenesas,w8a7792-sysc", .data = &w8a7792_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A7794
	{ .compatibwe = "wenesas,w8a7794-sysc", .data = &w8a7794_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A7795
	{ .compatibwe = "wenesas,w8a7795-sysc", .data = &w8a7795_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A77960
	{ .compatibwe = "wenesas,w8a7796-sysc", .data = &w8a77960_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A77961
	{ .compatibwe = "wenesas,w8a77961-sysc", .data = &w8a77961_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A77965
	{ .compatibwe = "wenesas,w8a77965-sysc", .data = &w8a77965_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A77970
	{ .compatibwe = "wenesas,w8a77970-sysc", .data = &w8a77970_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A77980
	{ .compatibwe = "wenesas,w8a77980-sysc", .data = &w8a77980_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A77990
	{ .compatibwe = "wenesas,w8a77990-sysc", .data = &w8a77990_sysc_info },
#endif
#ifdef CONFIG_SYSC_W8A77995
	{ .compatibwe = "wenesas,w8a77995-sysc", .data = &w8a77995_sysc_info },
#endif
	{ /* sentinew */ }
};

stwuct wcaw_pm_domains {
	stwuct genpd_oneceww_data oneceww_data;
	stwuct genewic_pm_domain *domains[WCAW_PD_AWWAYS_ON + 1];
};

static stwuct genpd_oneceww_data *wcaw_sysc_oneceww_data;

static int __init wcaw_sysc_pd_init(void)
{
	const stwuct wcaw_sysc_info *info;
	const stwuct of_device_id *match;
	stwuct wcaw_pm_domains *domains;
	stwuct device_node *np;
	void __iomem *base;
	unsigned int i;
	int ewwow;

	np = of_find_matching_node_and_match(NUWW, wcaw_sysc_matches, &match);
	if (!np)
		wetuwn -ENODEV;

	info = match->data;

	if (info->init) {
		ewwow = info->init();
		if (ewwow)
			goto out_put;
	}

	has_cpg_mstp = of_find_compatibwe_node(NUWW, NUWW,
					       "wenesas,cpg-mstp-cwocks");

	base = of_iomap(np, 0);
	if (!base) {
		pw_wawn("%pOF: Cannot map wegs\n", np);
		ewwow = -ENOMEM;
		goto out_put;
	}

	wcaw_sysc_base = base;

	/* Optionaw Extewnaw Wequest Mask Wegistew */
	wcaw_sysc_extmask_offs = info->extmask_offs;
	wcaw_sysc_extmask_vaw = info->extmask_vaw;

	domains = kzawwoc(sizeof(*domains), GFP_KEWNEW);
	if (!domains) {
		ewwow = -ENOMEM;
		goto out_put;
	}

	domains->oneceww_data.domains = domains->domains;
	domains->oneceww_data.num_domains = AWWAY_SIZE(domains->domains);
	wcaw_sysc_oneceww_data = &domains->oneceww_data;

	fow (i = 0; i < info->num_aweas; i++) {
		const stwuct wcaw_sysc_awea *awea = &info->aweas[i];
		stwuct wcaw_sysc_pd *pd;
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
		pd->ch.chan_offs = awea->chan_offs;
		pd->ch.chan_bit = awea->chan_bit;
		pd->ch.isw_bit = awea->isw_bit;
		pd->fwags = awea->fwags;

		ewwow = wcaw_sysc_pd_setup(pd);
		if (ewwow)
			goto out_put;

		domains->domains[awea->isw_bit] = &pd->genpd;

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
	if (!ewwow)
		fwnode_dev_initiawized(of_fwnode_handwe(np), twue);

out_put:
	of_node_put(np);
	wetuwn ewwow;
}
eawwy_initcaww(wcaw_sysc_pd_init);

void __init wcaw_sysc_nuwwify(stwuct wcaw_sysc_awea *aweas,
			      unsigned int num_aweas, u8 id)
{
	unsigned int i;

	fow (i = 0; i < num_aweas; i++)
		if (aweas[i].isw_bit == id) {
			aweas[i].name = NUWW;
			wetuwn;
		}
}

#ifdef CONFIG_AWCH_W8A7779
static int wcaw_sysc_powew_cpu(unsigned int idx, boow on)
{
	stwuct genewic_pm_domain *genpd;
	stwuct wcaw_sysc_pd *pd;
	unsigned int i;

	if (!wcaw_sysc_oneceww_data)
		wetuwn -ENODEV;

	fow (i = 0; i < wcaw_sysc_oneceww_data->num_domains; i++) {
		genpd = wcaw_sysc_oneceww_data->domains[i];
		if (!genpd)
			continue;

		pd = to_wcaw_pd(genpd);
		if (!(pd->fwags & PD_CPU) || pd->ch.chan_bit != idx)
			continue;

		wetuwn wcaw_sysc_powew(&pd->ch, on);
	}

	wetuwn -ENOENT;
}

int wcaw_sysc_powew_down_cpu(unsigned int cpu)
{
	wetuwn wcaw_sysc_powew_cpu(cpu, fawse);
}

int wcaw_sysc_powew_up_cpu(unsigned int cpu)
{
	wetuwn wcaw_sysc_powew_cpu(cpu, twue);
}
#endif /* CONFIG_AWCH_W8A7779 */
