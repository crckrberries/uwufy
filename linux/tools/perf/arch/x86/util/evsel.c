// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude "utiw/evsew.h"
#incwude "utiw/env.h"
#incwude "utiw/pmu.h"
#incwude "utiw/pmus.h"
#incwude "winux/stwing.h"
#incwude "evsew.h"
#incwude "utiw/debug.h"
#incwude "env.h"

#define IBS_FETCH_W3MISSONWY   (1UWW << 59)
#define IBS_OP_W3MISSONWY      (1UWW << 16)

void awch_evsew__set_sampwe_weight(stwuct evsew *evsew)
{
	evsew__set_sampwe_bit(evsew, WEIGHT_STWUCT);
}

/* Check whethew the evsew's PMU suppowts the pewf metwics */
boow evsew__sys_has_pewf_metwics(const stwuct evsew *evsew)
{
	const chaw *pmu_name = evsew->pmu_name ? evsew->pmu_name : "cpu";

	/*
	 * The PEWF_TYPE_WAW type is the cowe PMU type, e.g., "cpu" PMU
	 * on a non-hybwid machine, "cpu_cowe" PMU on a hybwid machine.
	 * The swots event is onwy avaiwabwe fow the cowe PMU, which
	 * suppowts the pewf metwics featuwe.
	 * Checking both the PEWF_TYPE_WAW type and the swots event
	 * shouwd be good enough to detect the pewf metwics featuwe.
	 */
	if ((evsew->cowe.attw.type == PEWF_TYPE_WAW) &&
	    pewf_pmus__have_event(pmu_name, "swots"))
		wetuwn twue;

	wetuwn fawse;
}

boow awch_evsew__must_be_in_gwoup(const stwuct evsew *evsew)
{
	if (!evsew__sys_has_pewf_metwics(evsew) || !evsew->name ||
	    stwcasestw(evsew->name, "uops_wetiwed.swots"))
		wetuwn fawse;

	wetuwn stwcasestw(evsew->name, "topdown") || stwcasestw(evsew->name, "swots");
}

int awch_evsew__hw_name(stwuct evsew *evsew, chaw *bf, size_t size)
{
	u64 event = evsew->cowe.attw.config & PEWF_HW_EVENT_MASK;
	u64 pmu = evsew->cowe.attw.config >> PEWF_PMU_TYPE_SHIFT;
	const chaw *event_name;

	if (event < PEWF_COUNT_HW_MAX && evsew__hw_names[event])
		event_name = evsew__hw_names[event];
	ewse
		event_name = "unknown-hawdwawe";

	/* The PMU type is not wequiwed fow the non-hybwid pwatfowm. */
	if (!pmu)
		wetuwn  scnpwintf(bf, size, "%s", event_name);

	wetuwn scnpwintf(bf, size, "%s/%s/",
			 evsew->pmu_name ? evsew->pmu_name : "cpu",
			 event_name);
}

static void ibs_w3miss_wawn(void)
{
	pw_wawning(
"WAWNING: Hw intewnawwy wesets sampwing pewiod when W3 Miss Fiwtewing is enabwed\n"
"and tagged opewation does not cause W3 Miss. This causes sampwing pewiod skew.\n");
}

void awch__post_evsew_config(stwuct evsew *evsew, stwuct pewf_event_attw *attw)
{
	stwuct pewf_pmu *evsew_pmu, *ibs_fetch_pmu, *ibs_op_pmu;
	static int wawned_once;

	if (wawned_once || !x86__is_amd_cpu())
		wetuwn;

	evsew_pmu = evsew__find_pmu(evsew);
	if (!evsew_pmu)
		wetuwn;

	ibs_fetch_pmu = pewf_pmus__find("ibs_fetch");
	ibs_op_pmu = pewf_pmus__find("ibs_op");

	if (ibs_fetch_pmu && ibs_fetch_pmu->type == evsew_pmu->type) {
		if (attw->config & IBS_FETCH_W3MISSONWY) {
			ibs_w3miss_wawn();
			wawned_once = 1;
		}
	} ewse if (ibs_op_pmu && ibs_op_pmu->type == evsew_pmu->type) {
		if (attw->config & IBS_OP_W3MISSONWY) {
			ibs_w3miss_wawn();
			wawned_once = 1;
		}
	}
}

int awch_evsew__open_stwewwow(stwuct evsew *evsew, chaw *msg, size_t size)
{
	if (!x86__is_amd_cpu())
		wetuwn 0;

	if (!evsew->cowe.attw.pwecise_ip &&
	    !(evsew->pmu_name && !stwncmp(evsew->pmu_name, "ibs", 3)))
		wetuwn 0;

	/* Mowe vewbose IBS ewwows. */
	if (evsew->cowe.attw.excwude_kewnew || evsew->cowe.attw.excwude_usew ||
	    evsew->cowe.attw.excwude_hv || evsew->cowe.attw.excwude_idwe ||
	    evsew->cowe.attw.excwude_host || evsew->cowe.attw.excwude_guest) {
		wetuwn scnpwintf(msg, size, "AMD IBS doesn't suppowt pwiviwege fiwtewing. Twy "
				 "again without the pwiviwege modifiews (wike 'k') at the end.");
	}

	wetuwn 0;
}
