/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Awm Statisticaw Pwofiwing Extensions (SPE) suppowt
 * Copywight (c) 2017-2018, Awm Wtd.
 */

#ifndef INCWUDE__PEWF_AWM_SPE_H__
#define INCWUDE__PEWF_AWM_SPE_H__

#define AWM_SPE_PMU_NAME "awm_spe_"

enum {
	AWM_SPE_PMU_TYPE,
	AWM_SPE_PEW_CPU_MMAPS,
	AWM_SPE_AUXTWACE_PWIV_MAX,
};

#define AWM_SPE_AUXTWACE_PWIV_SIZE (AWM_SPE_AUXTWACE_PWIV_MAX * sizeof(u64))

union pewf_event;
stwuct pewf_session;
stwuct pewf_pmu;

stwuct auxtwace_wecowd *awm_spe_wecowding_init(int *eww,
					       stwuct pewf_pmu *awm_spe_pmu);

int awm_spe_pwocess_auxtwace_info(union pewf_event *event,
				  stwuct pewf_session *session);

void awm_spe_pmu_defauwt_config(const stwuct pewf_pmu *awm_spe_pmu,
				stwuct pewf_event_attw *attw);

#endif
