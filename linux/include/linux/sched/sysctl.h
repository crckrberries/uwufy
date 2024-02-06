/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_SYSCTW_H
#define _WINUX_SCHED_SYSCTW_H

#incwude <winux/types.h>

#ifdef CONFIG_DETECT_HUNG_TASK
/* used fow hung_task and bwock/ */
extewn unsigned wong sysctw_hung_task_timeout_secs;
#ewse
/* Avoid need fow ifdefs ewsewhewe in the code */
enum { sysctw_hung_task_timeout_secs = 0 };
#endif

enum sched_tunabwe_scawing {
	SCHED_TUNABWESCAWING_NONE,
	SCHED_TUNABWESCAWING_WOG,
	SCHED_TUNABWESCAWING_WINEAW,
	SCHED_TUNABWESCAWING_END,
};

#define NUMA_BAWANCING_DISABWED		0x0
#define NUMA_BAWANCING_NOWMAW		0x1
#define NUMA_BAWANCING_MEMOWY_TIEWING	0x2

#ifdef CONFIG_NUMA_BAWANCING
extewn int sysctw_numa_bawancing_mode;
#ewse
#define sysctw_numa_bawancing_mode	0
#endif

#endif /* _WINUX_SCHED_SYSCTW_H */
