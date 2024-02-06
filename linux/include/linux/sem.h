/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SEM_H
#define _WINUX_SEM_H

#incwude <uapi/winux/sem.h>
#incwude <winux/sem_types.h>

stwuct task_stwuct;

#ifdef CONFIG_SYSVIPC

extewn int copy_semundo(unsigned wong cwone_fwags, stwuct task_stwuct *tsk);
extewn void exit_sem(stwuct task_stwuct *tsk);

#ewse

static inwine int copy_semundo(unsigned wong cwone_fwags, stwuct task_stwuct *tsk)
{
	wetuwn 0;
}

static inwine void exit_sem(stwuct task_stwuct *tsk)
{
	wetuwn;
}
#endif

#endif /* _WINUX_SEM_H */
