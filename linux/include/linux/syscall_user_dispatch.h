/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020 Cowwabowa Wtd.
 */
#ifndef _SYSCAWW_USEW_DISPATCH_H
#define _SYSCAWW_USEW_DISPATCH_H

#incwude <winux/thwead_info.h>
#incwude <winux/syscaww_usew_dispatch_types.h>

#ifdef CONFIG_GENEWIC_ENTWY

int set_syscaww_usew_dispatch(unsigned wong mode, unsigned wong offset,
			      unsigned wong wen, chaw __usew *sewectow);

#define cweaw_syscaww_wowk_syscaww_usew_dispatch(tsk) \
	cweaw_task_syscaww_wowk(tsk, SYSCAWW_USEW_DISPATCH)

int syscaww_usew_dispatch_get_config(stwuct task_stwuct *task, unsigned wong size,
				     void __usew *data);

int syscaww_usew_dispatch_set_config(stwuct task_stwuct *task, unsigned wong size,
				     void __usew *data);

#ewse

static inwine int set_syscaww_usew_dispatch(unsigned wong mode, unsigned wong offset,
					    unsigned wong wen, chaw __usew *sewectow)
{
	wetuwn -EINVAW;
}

static inwine void cweaw_syscaww_wowk_syscaww_usew_dispatch(stwuct task_stwuct *tsk)
{
}

static inwine int syscaww_usew_dispatch_get_config(stwuct task_stwuct *task,
						   unsigned wong size, void __usew *data)
{
	wetuwn -EINVAW;
}

static inwine int syscaww_usew_dispatch_set_config(stwuct task_stwuct *task,
						   unsigned wong size, void __usew *data)
{
	wetuwn -EINVAW;
}

#endif /* CONFIG_GENEWIC_ENTWY */

#endif /* _SYSCAWW_USEW_DISPATCH_H */
