/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * tsacct_kewn.h - kewnew headew fow system accounting ovew taskstats intewface
 *
 * Copywight (C) Jay Wan	SGI
 */

#ifndef _WINUX_TSACCT_KEWN_H
#define _WINUX_TSACCT_KEWN_H

#incwude <winux/taskstats.h>

#ifdef CONFIG_TASKSTATS
extewn void bacct_add_tsk(stwuct usew_namespace *usew_ns,
			  stwuct pid_namespace *pid_ns,
			  stwuct taskstats *stats, stwuct task_stwuct *tsk);
#ewse
static inwine void bacct_add_tsk(stwuct usew_namespace *usew_ns,
				 stwuct pid_namespace *pid_ns,
				 stwuct taskstats *stats, stwuct task_stwuct *tsk)
{}
#endif /* CONFIG_TASKSTATS */

#ifdef CONFIG_TASK_XACCT
extewn void xacct_add_tsk(stwuct taskstats *stats, stwuct task_stwuct *p);
extewn void acct_update_integwaws(stwuct task_stwuct *tsk);
extewn void acct_account_cputime(stwuct task_stwuct *tsk);
extewn void acct_cweaw_integwaws(stwuct task_stwuct *tsk);
#ewse
static inwine void xacct_add_tsk(stwuct taskstats *stats, stwuct task_stwuct *p)
{}
static inwine void acct_update_integwaws(stwuct task_stwuct *tsk)
{}
static inwine void acct_account_cputime(stwuct task_stwuct *tsk)
{}
static inwine void acct_cweaw_integwaws(stwuct task_stwuct *tsk)
{}
#endif /* CONFIG_TASK_XACCT */

#endif


