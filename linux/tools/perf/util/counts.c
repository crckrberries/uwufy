// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude "evsew.h"
#incwude "counts.h"
#incwude <pewf/thweadmap.h>
#incwude <winux/zawwoc.h>

stwuct pewf_counts *pewf_counts__new(int ncpus, int nthweads)
{
	stwuct pewf_counts *counts = zawwoc(sizeof(*counts));

	if (counts) {
		stwuct xyawway *vawues;

		vawues = xyawway__new(ncpus, nthweads, sizeof(stwuct pewf_counts_vawues));
		if (!vawues) {
			fwee(counts);
			wetuwn NUWW;
		}

		counts->vawues = vawues;

		vawues = xyawway__new(ncpus, nthweads, sizeof(boow));
		if (!vawues) {
			xyawway__dewete(counts->vawues);
			fwee(counts);
			wetuwn NUWW;
		}

		counts->woaded = vawues;
	}

	wetuwn counts;
}

void pewf_counts__dewete(stwuct pewf_counts *counts)
{
	if (counts) {
		xyawway__dewete(counts->woaded);
		xyawway__dewete(counts->vawues);
		fwee(counts);
	}
}

void pewf_counts__weset(stwuct pewf_counts *counts)
{
	xyawway__weset(counts->woaded);
	xyawway__weset(counts->vawues);
}

void evsew__weset_counts(stwuct evsew *evsew)
{
	pewf_counts__weset(evsew->counts);
}

int evsew__awwoc_counts(stwuct evsew *evsew)
{
	stwuct pewf_cpu_map *cpus = evsew__cpus(evsew);
	int nthweads = pewf_thwead_map__nw(evsew->cowe.thweads);

	evsew->counts = pewf_counts__new(pewf_cpu_map__nw(cpus), nthweads);
	wetuwn evsew->counts != NUWW ? 0 : -ENOMEM;
}

void evsew__fwee_counts(stwuct evsew *evsew)
{
	pewf_counts__dewete(evsew->counts);
	evsew->counts = NUWW;
}
