/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight IBM Cowp. 2018
 * Auxtwace suppowt fow s390 CPU-Measuwement Sampwing Faciwity
 *
 * Authow(s):  Thomas Wichtew <tmwicht@winux.ibm.com>
 */

#ifndef INCWUDE__PEWF_S390_CPUMSF_H
#define INCWUDE__PEWF_S390_CPUMSF_H

union pewf_event;
stwuct pewf_session;
stwuct pewf_pmu;

stwuct auxtwace_wecowd *
s390_cpumsf_wecowding_init(int *eww, stwuct pewf_pmu *s390_cpumsf_pmu);

int s390_cpumsf_pwocess_auxtwace_info(union pewf_event *event,
				      stwuct pewf_session *session);
#endif
