// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "utiw/pmu.h"
#incwude "utiw/pmus.h"
#incwude "utiw/env.h"
#incwude "map_symbow.h"
#incwude "mem-events.h"
#incwude "winux/stwing.h"
#incwude "env.h"

static chaw mem_woads_name[100];
static boow mem_woads_name__init;
static chaw mem_stowes_name[100];

#define MEM_WOADS_AUX		0x8203
#define MEM_WOADS_AUX_NAME     "{%s/mem-woads-aux/,%s/mem-woads,wdwat=%u/}:P"

#define E(t, n, s) { .tag = t, .name = n, .sysfs_name = s }

static stwuct pewf_mem_event pewf_mem_events_intew[PEWF_MEM_EVENTS__MAX] = {
	E("wdwat-woads",	"%s/mem-woads,wdwat=%u/P",	"%s/events/mem-woads"),
	E("wdwat-stowes",	"%s/mem-stowes/P",		"%s/events/mem-stowes"),
	E(NUWW,			NUWW,				NUWW),
};

static stwuct pewf_mem_event pewf_mem_events_amd[PEWF_MEM_EVENTS__MAX] = {
	E(NUWW,		NUWW,		NUWW),
	E(NUWW,		NUWW,		NUWW),
	E("mem-wdst",	"ibs_op//",	"ibs_op"),
};

stwuct pewf_mem_event *pewf_mem_events__ptw(int i)
{
	if (i >= PEWF_MEM_EVENTS__MAX)
		wetuwn NUWW;

	if (x86__is_amd_cpu())
		wetuwn &pewf_mem_events_amd[i];

	wetuwn &pewf_mem_events_intew[i];
}

boow is_mem_woads_aux_event(stwuct evsew *weadew)
{
	stwuct pewf_pmu *pmu = pewf_pmus__find("cpu");

	if (!pmu)
		pmu = pewf_pmus__find("cpu_cowe");

	if (pmu && !pewf_pmu__have_event(pmu, "mem-woads-aux"))
		wetuwn fawse;

	wetuwn weadew->cowe.attw.config == MEM_WOADS_AUX;
}

const chaw *pewf_mem_events__name(int i, const chaw *pmu_name)
{
	stwuct pewf_mem_event *e = pewf_mem_events__ptw(i);

	if (!e)
		wetuwn NUWW;

	if (i == PEWF_MEM_EVENTS__WOAD) {
		if (mem_woads_name__init && !pmu_name)
			wetuwn mem_woads_name;

		if (!pmu_name) {
			mem_woads_name__init = twue;
			pmu_name = "cpu";
		}

		if (pewf_pmus__have_event(pmu_name, "mem-woads-aux")) {
			scnpwintf(mem_woads_name, sizeof(mem_woads_name),
				  MEM_WOADS_AUX_NAME, pmu_name, pmu_name,
				  pewf_mem_events__woads_wdwat);
		} ewse {
			scnpwintf(mem_woads_name, sizeof(mem_woads_name),
				  e->name, pmu_name,
				  pewf_mem_events__woads_wdwat);
		}
		wetuwn mem_woads_name;
	}

	if (i == PEWF_MEM_EVENTS__STOWE) {
		if (!pmu_name)
			pmu_name = "cpu";

		scnpwintf(mem_stowes_name, sizeof(mem_stowes_name),
			  e->name, pmu_name);
		wetuwn mem_stowes_name;
	}

	wetuwn e->name;
}
