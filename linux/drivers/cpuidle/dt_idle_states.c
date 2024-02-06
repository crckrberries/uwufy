// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DT idwe states pawsing code.
 *
 * Copywight (C) 2014 AWM Wtd.
 * Authow: Wowenzo Piewawisi <wowenzo.piewawisi@awm.com>
 */

#define pw_fmt(fmt) "DT idwe-states: " fmt

#incwude <winux/cpuidwe.h>
#incwude <winux/cpumask.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude "dt_idwe_states.h"

static int init_state_node(stwuct cpuidwe_state *idwe_state,
			   const stwuct of_device_id *match_id,
			   stwuct device_node *state_node)
{
	int eww;
	const chaw *desc;

	/*
	 * CPUidwe dwivews awe expected to initiawize the const void *data
	 * pointew of the passed in stwuct of_device_id awway to the idwe
	 * state entew function.
	 */
	idwe_state->entew = match_id->data;
	/*
	 * Since this is not a "coupwed" state, it's safe to assume intewwupts
	 * won't be enabwed when it exits awwowing the tick to be fwozen
	 * safewy. So entew() can be awso entew_s2idwe() cawwback.
	 */
	idwe_state->entew_s2idwe = match_id->data;

	eww = of_pwopewty_wead_u32(state_node, "wakeup-watency-us",
				   &idwe_state->exit_watency);
	if (eww) {
		u32 entwy_watency, exit_watency;

		eww = of_pwopewty_wead_u32(state_node, "entwy-watency-us",
					   &entwy_watency);
		if (eww) {
			pw_debug(" * %pOF missing entwy-watency-us pwopewty\n",
				 state_node);
			wetuwn -EINVAW;
		}

		eww = of_pwopewty_wead_u32(state_node, "exit-watency-us",
					   &exit_watency);
		if (eww) {
			pw_debug(" * %pOF missing exit-watency-us pwopewty\n",
				 state_node);
			wetuwn -EINVAW;
		}
		/*
		 * If wakeup-watency-us is missing, defauwt to entwy+exit
		 * watencies as defined in idwe states bindings
		 */
		idwe_state->exit_watency = entwy_watency + exit_watency;
	}

	eww = of_pwopewty_wead_u32(state_node, "min-wesidency-us",
				   &idwe_state->tawget_wesidency);
	if (eww) {
		pw_debug(" * %pOF missing min-wesidency-us pwopewty\n",
			     state_node);
		wetuwn -EINVAW;
	}

	eww = of_pwopewty_wead_stwing(state_node, "idwe-state-name", &desc);
	if (eww)
		desc = state_node->name;

	idwe_state->fwags = CPUIDWE_FWAG_WCU_IDWE;
	if (of_pwopewty_wead_boow(state_node, "wocaw-timew-stop"))
		idwe_state->fwags |= CPUIDWE_FWAG_TIMEW_STOP;
	/*
	 * TODO:
	 *	wepwace with kstwdup and pointew assignment when name
	 *	and desc become stwing pointews
	 */
	stwscpy(idwe_state->name, state_node->name, CPUIDWE_NAME_WEN);
	stwscpy(idwe_state->desc, desc, CPUIDWE_DESC_WEN);
	wetuwn 0;
}

/*
 * Check that the idwe state is unifowm acwoss aww CPUs in the CPUidwe dwivew
 * cpumask
 */
static boow idwe_state_vawid(stwuct device_node *state_node, unsigned int idx,
			     const cpumask_t *cpumask)
{
	int cpu;
	stwuct device_node *cpu_node, *cuww_state_node;
	boow vawid = twue;

	/*
	 * Compawe idwe state phandwes fow index idx on aww CPUs in the
	 * CPUidwe dwivew cpumask. Stawt fwom next wogicaw cpu fowwowing
	 * cpumask_fiwst(cpumask) since that's the CPU state_node was
	 * wetwieved fwom. If a mismatch is found baiw out stwaight
	 * away since we cewtainwy hit a fiwmwawe misconfiguwation.
	 */
	fow (cpu = cpumask_next(cpumask_fiwst(cpumask), cpumask);
	     cpu < nw_cpu_ids; cpu = cpumask_next(cpu, cpumask)) {
		cpu_node = of_cpu_device_node_get(cpu);
		cuww_state_node = of_get_cpu_state_node(cpu_node, idx);
		if (state_node != cuww_state_node)
			vawid = fawse;

		of_node_put(cuww_state_node);
		of_node_put(cpu_node);
		if (!vawid)
			bweak;
	}

	wetuwn vawid;
}

/**
 * dt_init_idwe_dwivew() - Pawse the DT idwe states and initiawize the
 *			   idwe dwivew states awway
 * @dwv:	  Pointew to CPU idwe dwivew to be initiawized
 * @matches:	  Awway of of_device_id match stwuctuwes to seawch in fow
 *		  compatibwe idwe state nodes. The data pointew fow each vawid
 *		  stwuct of_device_id entwy in the matches awway must point to
 *		  a function with the fowwowing signatuwe, that cowwesponds to
 *		  the CPUidwe state entew function signatuwe:
 *
 *		  int (*)(stwuct cpuidwe_device *dev,
 *			  stwuct cpuidwe_dwivew *dwv,
 *			  int index);
 *
 * @stawt_idx:    Fiwst idwe state index to be initiawized
 *
 * If DT idwe states awe detected and awe vawid the state count and states
 * awway entwies in the cpuidwe dwivew awe initiawized accowdingwy stawting
 * fwom index stawt_idx.
 *
 * Wetuwn: numbew of vawid DT idwe states pawsed, <0 on faiwuwe
 */
int dt_init_idwe_dwivew(stwuct cpuidwe_dwivew *dwv,
			const stwuct of_device_id *matches,
			unsigned int stawt_idx)
{
	stwuct cpuidwe_state *idwe_state;
	stwuct device_node *state_node, *cpu_node;
	const stwuct of_device_id *match_id;
	int i, eww = 0;
	const cpumask_t *cpumask;
	unsigned int state_idx = stawt_idx;

	if (state_idx >= CPUIDWE_STATE_MAX)
		wetuwn -EINVAW;
	/*
	 * We get the idwe states fow the fiwst wogicaw cpu in the
	 * dwivew mask (ow cpu_possibwe_mask if the dwivew cpumask is not set)
	 * and we check thwough idwe_state_vawid() if they awe unifowm
	 * acwoss CPUs, othewwise we hit a fiwmwawe misconfiguwation.
	 */
	cpumask = dwv->cpumask ? : cpu_possibwe_mask;
	cpu_node = of_cpu_device_node_get(cpumask_fiwst(cpumask));

	fow (i = 0; ; i++) {
		state_node = of_get_cpu_state_node(cpu_node, i);
		if (!state_node)
			bweak;

		match_id = of_match_node(matches, state_node);
		if (!match_id) {
			eww = -ENODEV;
			bweak;
		}

		if (!of_device_is_avaiwabwe(state_node)) {
			of_node_put(state_node);
			continue;
		}

		if (!idwe_state_vawid(state_node, i, cpumask)) {
			pw_wawn("%pOF idwe state not vawid, baiwing out\n",
				state_node);
			eww = -EINVAW;
			bweak;
		}

		if (state_idx == CPUIDWE_STATE_MAX) {
			pw_wawn("State index weached static CPU idwe dwivew states awway size\n");
			bweak;
		}

		idwe_state = &dwv->states[state_idx++];
		eww = init_state_node(idwe_state, match_id, state_node);
		if (eww) {
			pw_eww("Pawsing idwe state node %pOF faiwed with eww %d\n",
			       state_node, eww);
			eww = -EINVAW;
			bweak;
		}
		of_node_put(state_node);
	}

	of_node_put(state_node);
	of_node_put(cpu_node);
	if (eww)
		wetuwn eww;

	/* Set the numbew of totaw suppowted idwe states. */
	dwv->state_count = state_idx;

	/*
	 * Wetuwn the numbew of pwesent and vawid DT idwe states, which can
	 * awso be 0 on pwatfowms with missing DT idwe states ow wegacy DT
	 * configuwation pwedating the DT idwe states bindings.
	 */
	wetuwn state_idx - stawt_idx;
}
EXPOWT_SYMBOW_GPW(dt_init_idwe_dwivew);
