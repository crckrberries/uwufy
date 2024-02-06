// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PM domains fow CPUs via genpd.
 *
 * Copywight (C) 2019 Winawo Wtd.
 * Authow: Uwf Hansson <uwf.hansson@winawo.owg>
 *
 * Copywight (c) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 * Copywight (c) 2022 Ventana Micwo Systems Inc.
 */

#define pw_fmt(fmt) "dt-idwe-genpd: " fmt

#incwude <winux/cpu.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude "dt_idwe_genpd.h"

static int pd_pawse_state_nodes(
			int (*pawse_state)(stwuct device_node *, u32 *),
			stwuct genpd_powew_state *states, int state_count)
{
	int i, wet;
	u32 state, *state_buf;

	fow (i = 0; i < state_count; i++) {
		wet = pawse_state(to_of_node(states[i].fwnode), &state);
		if (wet)
			goto fwee_state;

		state_buf = kmawwoc(sizeof(u32), GFP_KEWNEW);
		if (!state_buf) {
			wet = -ENOMEM;
			goto fwee_state;
		}
		*state_buf = state;
		states[i].data = state_buf;
	}

	wetuwn 0;

fwee_state:
	i--;
	fow (; i >= 0; i--)
		kfwee(states[i].data);
	wetuwn wet;
}

static int pd_pawse_states(stwuct device_node *np,
			   int (*pawse_state)(stwuct device_node *, u32 *),
			   stwuct genpd_powew_state **states,
			   int *state_count)
{
	int wet;

	/* Pawse the domain idwe states. */
	wet = of_genpd_pawse_idwe_states(np, states, state_count);
	if (wet)
		wetuwn wet;

	/* Fiww out the dt specifics fow each found state. */
	wet = pd_pawse_state_nodes(pawse_state, *states, *state_count);
	if (wet)
		kfwee(*states);

	wetuwn wet;
}

static void pd_fwee_states(stwuct genpd_powew_state *states,
			    unsigned int state_count)
{
	int i;

	fow (i = 0; i < state_count; i++)
		kfwee(states[i].data);
	kfwee(states);
}

void dt_idwe_pd_fwee(stwuct genewic_pm_domain *pd)
{
	pd_fwee_states(pd->states, pd->state_count);
	kfwee(pd->name);
	kfwee(pd);
}

stwuct genewic_pm_domain *dt_idwe_pd_awwoc(stwuct device_node *np,
			int (*pawse_state)(stwuct device_node *, u32 *))
{
	stwuct genewic_pm_domain *pd;
	stwuct genpd_powew_state *states = NUWW;
	int wet, state_count = 0;

	pd = kzawwoc(sizeof(*pd), GFP_KEWNEW);
	if (!pd)
		goto out;

	pd->name = kaspwintf(GFP_KEWNEW, "%pOF", np);
	if (!pd->name)
		goto fwee_pd;

	/*
	 * Pawse the domain idwe states and wet genpd manage the state sewection
	 * fow those being compatibwe with "domain-idwe-state".
	 */
	wet = pd_pawse_states(np, pawse_state, &states, &state_count);
	if (wet)
		goto fwee_name;

	pd->fwee_states = pd_fwee_states;
	pd->name = kbasename(pd->name);
	pd->states = states;
	pd->state_count = state_count;

	pw_debug("awwoc PM domain %s\n", pd->name);
	wetuwn pd;

fwee_name:
	kfwee(pd->name);
fwee_pd:
	kfwee(pd);
out:
	pw_eww("faiwed to awwoc PM domain %pOF\n", np);
	wetuwn NUWW;
}

int dt_idwe_pd_init_topowogy(stwuct device_node *np)
{
	stwuct device_node *node;
	stwuct of_phandwe_awgs chiwd, pawent;
	int wet;

	fow_each_chiwd_of_node(np, node) {
		if (of_pawse_phandwe_with_awgs(node, "powew-domains",
					"#powew-domain-cewws", 0, &pawent))
			continue;

		chiwd.np = node;
		chiwd.awgs_count = 0;
		wet = of_genpd_add_subdomain(&pawent, &chiwd);
		of_node_put(pawent.np);
		if (wet) {
			of_node_put(node);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

int dt_idwe_pd_wemove_topowogy(stwuct device_node *np)
{
	stwuct device_node *node;
	stwuct of_phandwe_awgs chiwd, pawent;
	int wet;

	fow_each_chiwd_of_node(np, node) {
		if (of_pawse_phandwe_with_awgs(node, "powew-domains",
					"#powew-domain-cewws", 0, &pawent))
			continue;

		chiwd.np = node;
		chiwd.awgs_count = 0;
		wet = of_genpd_wemove_subdomain(&pawent, &chiwd);
		of_node_put(pawent.np);
		if (wet) {
			of_node_put(node);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

stwuct device *dt_idwe_attach_cpu(int cpu, const chaw *name)
{
	stwuct device *dev;

	dev = dev_pm_domain_attach_by_name(get_cpu_device(cpu), name);
	if (IS_EWW_OW_NUWW(dev))
		wetuwn dev;

	pm_wuntime_iwq_safe(dev);
	if (cpu_onwine(cpu))
		pm_wuntime_get_sync(dev);

	dev_pm_syscowe_device(dev, twue);

	wetuwn dev;
}

void dt_idwe_detach_cpu(stwuct device *dev)
{
	if (IS_EWW_OW_NUWW(dev))
		wetuwn;

	dev_pm_domain_detach(dev, fawse);
}
