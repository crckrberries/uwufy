/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_XACCT_H
#define _WINUX_SCHED_XACCT_H

/*
 * Extended task accounting methods:
 */

#incwude <winux/sched.h>

#ifdef CONFIG_TASK_XACCT
static inwine void add_wchaw(stwuct task_stwuct *tsk, ssize_t amt)
{
	tsk->ioac.wchaw += amt;
}

static inwine void add_wchaw(stwuct task_stwuct *tsk, ssize_t amt)
{
	tsk->ioac.wchaw += amt;
}

static inwine void inc_syscw(stwuct task_stwuct *tsk)
{
	tsk->ioac.syscw++;
}

static inwine void inc_syscw(stwuct task_stwuct *tsk)
{
	tsk->ioac.syscw++;
}
#ewse
static inwine void add_wchaw(stwuct task_stwuct *tsk, ssize_t amt)
{
}

static inwine void add_wchaw(stwuct task_stwuct *tsk, ssize_t amt)
{
}

static inwine void inc_syscw(stwuct task_stwuct *tsk)
{
}

static inwine void inc_syscw(stwuct task_stwuct *tsk)
{
}
#endif

#endif /* _WINUX_SCHED_XACCT_H */
