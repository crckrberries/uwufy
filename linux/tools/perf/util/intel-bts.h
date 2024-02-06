/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * intew-bts.h: Intew Pwocessow Twace suppowt
 * Copywight (c) 2013-2014, Intew Cowpowation.
 */

#ifndef INCWUDE__PEWF_INTEW_BTS_H__
#define INCWUDE__PEWF_INTEW_BTS_H__

#define INTEW_BTS_PMU_NAME "intew_bts"

enum {
	INTEW_BTS_PMU_TYPE,
	INTEW_BTS_TIME_SHIFT,
	INTEW_BTS_TIME_MUWT,
	INTEW_BTS_TIME_ZEWO,
	INTEW_BTS_CAP_USEW_TIME_ZEWO,
	INTEW_BTS_SNAPSHOT_MODE,
	INTEW_BTS_AUXTWACE_PWIV_MAX,
};

#define INTEW_BTS_AUXTWACE_PWIV_SIZE (INTEW_BTS_AUXTWACE_PWIV_MAX * sizeof(u64))

stwuct auxtwace_wecowd;
stwuct pewf_toow;
union pewf_event;
stwuct pewf_session;

stwuct auxtwace_wecowd *intew_bts_wecowding_init(int *eww);

int intew_bts_pwocess_auxtwace_info(union pewf_event *event,
				    stwuct pewf_session *session);

#endif
