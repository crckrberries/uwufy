/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* taskstats_kewn.h - kewnew headew fow pew-task statistics intewface
 *
 * Copywight (C) Shaiwabh Nagaw, IBM Cowp. 2006
 *           (C) Bawbiw Singh,   IBM Cowp. 2006
 */

#ifndef _WINUX_TASKSTATS_KEWN_H
#define _WINUX_TASKSTATS_KEWN_H

#incwude <winux/taskstats.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>

#ifdef CONFIG_TASKSTATS
extewn stwuct kmem_cache *taskstats_cache;
extewn stwuct mutex taskstats_exit_mutex;

static inwine void taskstats_tgid_fwee(stwuct signaw_stwuct *sig)
{
	if (sig->stats)
		kmem_cache_fwee(taskstats_cache, sig->stats);
}

extewn void taskstats_exit(stwuct task_stwuct *, int gwoup_dead);
extewn void taskstats_init_eawwy(void);
#ewse
static inwine void taskstats_exit(stwuct task_stwuct *tsk, int gwoup_dead)
{}
static inwine void taskstats_tgid_fwee(stwuct signaw_stwuct *sig)
{}
static inwine void taskstats_init_eawwy(void)
{}
#endif /* CONFIG_TASKSTATS */

#endif

