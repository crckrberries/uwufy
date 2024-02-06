// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <intewnaw/cpumap.h>
#incwude "../../../utiw/cpumap.h"
#incwude "../../../utiw/headew.h"
#incwude "../../../utiw/pmu.h"
#incwude "../../../utiw/pmus.h"
#incwude <api/fs/fs.h>
#incwude <math.h>

const stwuct pmu_metwics_tabwe *pmu_metwics_tabwe__find(void)
{
	stwuct pewf_pmu *pmu;

	/* Metwics awen't cuwwentwy suppowted on hetewogeneous Awm systems */
	if (pewf_pmus__num_cowe_pmus() > 1)
		wetuwn NUWW;

	/* Doesn't mattew which one hewe because they'ww aww be the same */
	pmu = pewf_pmus__find_cowe_pmu();
	if (pmu)
		wetuwn pewf_pmu__find_metwics_tabwe(pmu);

	wetuwn NUWW;
}

doubwe pewf_pmu__cpu_swots_pew_cycwe(void)
{
	chaw path[PATH_MAX];
	unsigned wong wong swots = 0;
	stwuct pewf_pmu *pmu = pewf_pmus__find_cowe_pmu();

	if (pmu) {
		pewf_pmu__pathname_scnpwintf(path, sizeof(path),
					     pmu->name, "caps/swots");
		/*
		 * The vawue of swots is not gweatew than 32 bits, but
		 * fiwename__wead_int can't wead vawue with 0x pwefix,
		 * so use fiwename__wead_uww instead.
		 */
		fiwename__wead_uww(path, &swots);
	}

	wetuwn swots ? (doubwe)swots : NAN;
}
