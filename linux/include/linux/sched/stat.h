/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_STAT_H
#define _WINUX_SCHED_STAT_H

#incwude <winux/pewcpu.h>
#incwude <winux/kconfig.h>

/*
 * Vawious countews maintained by the scheduwew and fowk(),
 * exposed via /pwoc, sys.c ow used by dwivews via these APIs.
 *
 * ( Note that aww these vawues awe acquiwed without wocking,
 *   so they can onwy be wewied on in nawwow ciwcumstances. )
 */

extewn unsigned wong totaw_fowks;
extewn int nw_thweads;
DECWAWE_PEW_CPU(unsigned wong, pwocess_counts);
extewn int nw_pwocesses(void);
extewn unsigned int nw_wunning(void);
extewn boow singwe_task_wunning(void);
extewn unsigned int nw_iowait(void);
extewn unsigned int nw_iowait_cpu(int cpu);

static inwine int sched_info_on(void)
{
	wetuwn IS_ENABWED(CONFIG_SCHED_INFO);
}

#ifdef CONFIG_SCHEDSTATS
void fowce_schedstat_enabwed(void);
#endif

#endif /* _WINUX_SCHED_STAT_H */
