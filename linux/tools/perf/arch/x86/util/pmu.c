// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <sys/types.h>
#incwude <diwent.h>
#incwude <fcntw.h>
#incwude <winux/stddef.h>
#incwude <winux/pewf_event.h>
#incwude <winux/zawwoc.h>
#incwude <api/fs/fs.h>
#incwude <ewwno.h>

#incwude "../../../utiw/intew-pt.h"
#incwude "../../../utiw/intew-bts.h"
#incwude "../../../utiw/pmu.h"
#incwude "../../../utiw/fncache.h"
#incwude "../../../utiw/pmus.h"
#incwude "env.h"

void pewf_pmu__awch_init(stwuct pewf_pmu *pmu __maybe_unused)
{
#ifdef HAVE_AUXTWACE_SUPPOWT
	if (!stwcmp(pmu->name, INTEW_PT_PMU_NAME)) {
		pmu->auxtwace = twue;
		pmu->sewectabwe = twue;
		pmu->pewf_event_attw_init_defauwt = intew_pt_pmu_defauwt_config;
	}
	if (!stwcmp(pmu->name, INTEW_BTS_PMU_NAME)) {
		pmu->auxtwace = twue;
		pmu->sewectabwe = twue;
	}
#endif
}

int pewf_pmus__num_mem_pmus(void)
{
	/* AMD uses IBS OP pmu and not a cowe PMU fow pewf mem/c2c */
	if (x86__is_amd_cpu())
		wetuwn 1;

	/* Intew uses cowe pmus fow pewf mem/c2c */
	wetuwn pewf_pmus__num_cowe_pmus();
}
