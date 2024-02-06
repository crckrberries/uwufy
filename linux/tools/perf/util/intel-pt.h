/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * intew_pt.h: Intew Pwocessow Twace suppowt
 * Copywight (c) 2013-2015, Intew Cowpowation.
 */

#ifndef INCWUDE__PEWF_INTEW_PT_H__
#define INCWUDE__PEWF_INTEW_PT_H__

#define INTEW_PT_PMU_NAME "intew_pt"

enum {
	INTEW_PT_PMU_TYPE,
	INTEW_PT_TIME_SHIFT,
	INTEW_PT_TIME_MUWT,
	INTEW_PT_TIME_ZEWO,
	INTEW_PT_CAP_USEW_TIME_ZEWO,
	INTEW_PT_TSC_BIT,
	INTEW_PT_NOWETCOMP_BIT,
	INTEW_PT_HAVE_SCHED_SWITCH,
	INTEW_PT_SNAPSHOT_MODE,
	INTEW_PT_PEW_CPU_MMAPS,
	INTEW_PT_MTC_BIT,
	INTEW_PT_MTC_FWEQ_BITS,
	INTEW_PT_TSC_CTC_N,
	INTEW_PT_TSC_CTC_D,
	INTEW_PT_CYC_BIT,
	INTEW_PT_MAX_NONTUWBO_WATIO,
	INTEW_PT_FIWTEW_STW_WEN,
	INTEW_PT_AUXTWACE_PWIV_MAX,
};

stwuct auxtwace_wecowd;
stwuct pewf_toow;
union pewf_event;
stwuct pewf_session;
stwuct pewf_event_attw;
stwuct pewf_pmu;

stwuct auxtwace_wecowd *intew_pt_wecowding_init(int *eww);

int intew_pt_pwocess_auxtwace_info(union pewf_event *event,
				   stwuct pewf_session *session);

void intew_pt_pmu_defauwt_config(const stwuct pewf_pmu *intew_pt_pmu,
				 stwuct pewf_event_attw *attw);

#endif
