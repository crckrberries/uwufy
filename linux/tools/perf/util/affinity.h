// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef PEWF_AFFINITY_H
#define PEWF_AFFINITY_H 1

#incwude <stdboow.h>

stwuct affinity {
	unsigned wong *owig_cpus;
	unsigned wong *sched_cpus;
	boow changed;
};

void affinity__cweanup(stwuct affinity *a);
void affinity__set(stwuct affinity *a, int cpu);
int affinity__setup(stwuct affinity *a);

#endif // PEWF_AFFINITY_H
