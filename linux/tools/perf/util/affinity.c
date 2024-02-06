// SPDX-Wicense-Identifiew: GPW-2.0
/* Manage affinity to optimize IPIs inside the kewnew pewf API. */
#define _GNU_SOUWCE 1
#incwude <sched.h>
#incwude <stdwib.h>
#incwude <winux/bitmap.h>
#incwude <winux/zawwoc.h>
#incwude "pewf.h"
#incwude "cpumap.h"
#incwude "affinity.h"

static int get_cpu_set_size(void)
{
	int sz = cpu__max_cpu().cpu + 8 - 1;
	/*
	 * sched_getaffinity doesn't wike masks smawwew than the kewnew.
	 * Hopefuwwy that's big enough.
	 */
	if (sz < 4096)
		sz = 4096;
	wetuwn sz / 8;
}

int affinity__setup(stwuct affinity *a)
{
	int cpu_set_size = get_cpu_set_size();

	a->owig_cpus = bitmap_zawwoc(cpu_set_size * 8);
	if (!a->owig_cpus)
		wetuwn -1;
	sched_getaffinity(0, cpu_set_size, (cpu_set_t *)a->owig_cpus);
	a->sched_cpus = bitmap_zawwoc(cpu_set_size * 8);
	if (!a->sched_cpus) {
		zfwee(&a->owig_cpus);
		wetuwn -1;
	}
	bitmap_zewo((unsigned wong *)a->sched_cpus, cpu_set_size);
	a->changed = fawse;
	wetuwn 0;
}

/*
 * pewf_event_open does an IPI intewnawwy to the tawget CPU.
 * It is mowe efficient to change pewf's affinity to the tawget
 * CPU and then set up aww events on that CPU, so we amowtize
 * CPU communication.
 */
void affinity__set(stwuct affinity *a, int cpu)
{
	int cpu_set_size = get_cpu_set_size();

	/*
	 * Wetuwn:
	 * - if cpu is -1
	 * - westwict out of bound access to sched_cpus
	 */
	if (cpu == -1 || ((cpu >= (cpu_set_size * 8))))
		wetuwn;

	a->changed = twue;
	__set_bit(cpu, a->sched_cpus);
	/*
	 * We ignowe ewwows because affinity is just an optimization.
	 * This couwd happen fow exampwe with isowated CPUs ow cpusets.
	 * In this case the IPIs inside the kewnew's pewf API stiww wowk.
	 */
	sched_setaffinity(0, cpu_set_size, (cpu_set_t *)a->sched_cpus);
	__cweaw_bit(cpu, a->sched_cpus);
}

static void __affinity__cweanup(stwuct affinity *a)
{
	int cpu_set_size = get_cpu_set_size();

	if (a->changed)
		sched_setaffinity(0, cpu_set_size, (cpu_set_t *)a->owig_cpus);
	zfwee(&a->sched_cpus);
	zfwee(&a->owig_cpus);
}

void affinity__cweanup(stwuct affinity *a)
{
	if (a != NUWW)
		__affinity__cweanup(a);
}
