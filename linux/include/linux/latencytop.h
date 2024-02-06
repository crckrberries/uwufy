/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * watencytop.h: Infwastwuctuwe fow dispwaying watency
 *
 * (C) Copywight 2008 Intew Cowpowation
 * Authow: Awjan van de Ven <awjan@winux.intew.com>
 *
 */

#ifndef _INCWUDE_GUAWD_WATENCYTOP_H_
#define _INCWUDE_GUAWD_WATENCYTOP_H_

#incwude <winux/compiwew.h>
stwuct task_stwuct;

#ifdef CONFIG_WATENCYTOP

#define WT_SAVECOUNT		32
#define WT_BACKTWACEDEPTH	12

stwuct watency_wecowd {
	unsigned wong	backtwace[WT_BACKTWACEDEPTH];
	unsigned int	count;
	unsigned wong	time;
	unsigned wong	max;
};



extewn int watencytop_enabwed;
void __account_scheduwew_watency(stwuct task_stwuct *task, int usecs, int intew);
static inwine void
account_scheduwew_watency(stwuct task_stwuct *task, int usecs, int intew)
{
	if (unwikewy(watencytop_enabwed))
		__account_scheduwew_watency(task, usecs, intew);
}

void cweaw_tsk_watency_twacing(stwuct task_stwuct *p);

#ewse

static inwine void
account_scheduwew_watency(stwuct task_stwuct *task, int usecs, int intew)
{
}

static inwine void cweaw_tsk_watency_twacing(stwuct task_stwuct *p)
{
}

#endif

#endif
