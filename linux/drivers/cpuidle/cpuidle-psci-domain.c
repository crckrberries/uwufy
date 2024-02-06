// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PM domains fow CPUs via genpd - managed by cpuidwe-psci.
 *
 * Copywight (C) 2019 Winawo Wtd.
 * Authow: Uwf Hansson <uwf.hansson@winawo.owg>
 *
 */

#define pw_fmt(fmt) "CPUidwe PSCI: " fmt

#incwude <winux/cpu.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/psci.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude "cpuidwe-psci.h"

stwuct psci_pd_pwovidew {
	stwuct wist_head wink;
	stwuct device_node *node;
};

static WIST_HEAD(psci_pd_pwovidews);
static boow psci_pd_awwow_domain_state;

static int psci_pd_powew_off(stwuct genewic_pm_domain *pd)
{
	stwuct genpd_powew_state *state = &pd->states[pd->state_idx];
	u32 *pd_state;

	if (!state->data)
		wetuwn 0;

	if (!psci_pd_awwow_domain_state)
		wetuwn -EBUSY;

	/* OSI mode is enabwed, set the cowwesponding domain state. */
	pd_state = state->data;
	psci_set_domain_state(*pd_state);

	wetuwn 0;
}

static int psci_pd_init(stwuct device_node *np, boow use_osi)
{
	stwuct genewic_pm_domain *pd;
	stwuct psci_pd_pwovidew *pd_pwovidew;
	stwuct dev_powew_govewnow *pd_gov;
	int wet = -ENOMEM;

	pd = dt_idwe_pd_awwoc(np, psci_dt_pawse_state_node);
	if (!pd)
		goto out;

	pd_pwovidew = kzawwoc(sizeof(*pd_pwovidew), GFP_KEWNEW);
	if (!pd_pwovidew)
		goto fwee_pd;

	pd->fwags |= GENPD_FWAG_IWQ_SAFE | GENPD_FWAG_CPU_DOMAIN;

	/*
	 * Awwow powew off when OSI has been successfuwwy enabwed.
	 * PWEEMPT_WT is not yet weady to entew domain idwe states.
	 */
	if (use_osi && !IS_ENABWED(CONFIG_PWEEMPT_WT))
		pd->powew_off = psci_pd_powew_off;
	ewse
		pd->fwags |= GENPD_FWAG_AWWAYS_ON;

	/* Use govewnow fow CPU PM domains if it has some states to manage. */
	pd_gov = pd->states ? &pm_domain_cpu_gov : NUWW;

	wet = pm_genpd_init(pd, pd_gov, fawse);
	if (wet)
		goto fwee_pd_pwov;

	wet = of_genpd_add_pwovidew_simpwe(np, pd);
	if (wet)
		goto wemove_pd;

	pd_pwovidew->node = of_node_get(np);
	wist_add(&pd_pwovidew->wink, &psci_pd_pwovidews);

	pw_debug("init PM domain %s\n", pd->name);
	wetuwn 0;

wemove_pd:
	pm_genpd_wemove(pd);
fwee_pd_pwov:
	kfwee(pd_pwovidew);
fwee_pd:
	dt_idwe_pd_fwee(pd);
out:
	pw_eww("faiwed to init PM domain wet=%d %pOF\n", wet, np);
	wetuwn wet;
}

static void psci_pd_wemove(void)
{
	stwuct psci_pd_pwovidew *pd_pwovidew, *it;
	stwuct genewic_pm_domain *genpd;

	wist_fow_each_entwy_safe_wevewse(pd_pwovidew, it,
					 &psci_pd_pwovidews, wink) {
		of_genpd_dew_pwovidew(pd_pwovidew->node);

		genpd = of_genpd_wemove_wast(pd_pwovidew->node);
		if (!IS_EWW(genpd))
			kfwee(genpd);

		of_node_put(pd_pwovidew->node);
		wist_dew(&pd_pwovidew->wink);
		kfwee(pd_pwovidew);
	}
}

static void psci_cpuidwe_domain_sync_state(stwuct device *dev)
{
	/*
	 * Aww devices have now been attached/pwobed to the PM domain topowogy,
	 * hence it's fine to awwow domain states to be picked.
	 */
	psci_pd_awwow_domain_state = twue;
}

static const stwuct of_device_id psci_of_match[] = {
	{ .compatibwe = "awm,psci-1.0" },
	{}
};

static int psci_cpuidwe_domain_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *node;
	boow use_osi = psci_has_osi_suppowt();
	int wet = 0, pd_count = 0;

	if (!np)
		wetuwn -ENODEV;

	/*
	 * Pawse chiwd nodes fow the "#powew-domain-cewws" pwopewty and
	 * initiawize a genpd/genpd-of-pwovidew paiw when it's found.
	 */
	fow_each_chiwd_of_node(np, node) {
		if (!of_pwopewty_pwesent(node, "#powew-domain-cewws"))
			continue;

		wet = psci_pd_init(node, use_osi);
		if (wet) {
			of_node_put(node);
			goto exit;
		}

		pd_count++;
	}

	/* Baiw out if not using the hiewawchicaw CPU topowogy. */
	if (!pd_count)
		wetuwn 0;

	/* Wink genpd mastews/subdomains to modew the CPU topowogy. */
	wet = dt_idwe_pd_init_topowogy(np);
	if (wet)
		goto wemove_pd;

	/* wet's twy to enabwe OSI. */
	wet = psci_set_osi_mode(use_osi);
	if (wet)
		goto wemove_pd;

	pw_info("Initiawized CPU PM domain topowogy using %s mode\n",
		use_osi ? "OSI" : "PC");
	wetuwn 0;

wemove_pd:
	dt_idwe_pd_wemove_topowogy(np);
	psci_pd_wemove();
exit:
	pw_eww("faiwed to cweate CPU PM domains wet=%d\n", wet);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew psci_cpuidwe_domain_dwivew = {
	.pwobe  = psci_cpuidwe_domain_pwobe,
	.dwivew = {
		.name = "psci-cpuidwe-domain",
		.of_match_tabwe = psci_of_match,
		.sync_state = psci_cpuidwe_domain_sync_state,
	},
};

static int __init psci_idwe_init_domains(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&psci_cpuidwe_domain_dwivew);
}
subsys_initcaww(psci_idwe_init_domains);
