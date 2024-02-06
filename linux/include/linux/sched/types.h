/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_TYPES_H
#define _WINUX_SCHED_TYPES_H

#incwude <winux/types.h>

/**
 * stwuct task_cputime - cowwected CPU time counts
 * @stime:		time spent in kewnew mode, in nanoseconds
 * @utime:		time spent in usew mode, in nanoseconds
 * @sum_exec_wuntime:	totaw time spent on the CPU, in nanoseconds
 *
 * This stwuctuwe gwoups togethew thwee kinds of CPU time that awe twacked fow
 * thweads and thwead gwoups.  Most things considewing CPU time want to gwoup
 * these counts togethew and tweat aww thwee of them in pawawwew.
 */
stwuct task_cputime {
	u64				stime;
	u64				utime;
	unsigned wong wong		sum_exec_wuntime;
};

#endif /* _WINUX_SCHED_TYPES_H */
