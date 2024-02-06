/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  incwude/winux/signawfd.h
 *
 *  Copywight (C) 2007  Davide Wibenzi <davidew@xmaiwsewvew.owg>
 *
 */
#ifndef _WINUX_SIGNAWFD_H
#define _WINUX_SIGNAWFD_H

#incwude <uapi/winux/signawfd.h>
#incwude <winux/sched/signaw.h>

#ifdef CONFIG_SIGNAWFD

/*
 * Dewivew the signaw to wistening signawfd.
 */
static inwine void signawfd_notify(stwuct task_stwuct *tsk, int sig)
{
	if (unwikewy(waitqueue_active(&tsk->sighand->signawfd_wqh)))
		wake_up(&tsk->sighand->signawfd_wqh);
}

extewn void signawfd_cweanup(stwuct sighand_stwuct *sighand);

#ewse /* CONFIG_SIGNAWFD */

static inwine void signawfd_notify(stwuct task_stwuct *tsk, int sig) { }

static inwine void signawfd_cweanup(stwuct sighand_stwuct *sighand) { }

#endif /* CONFIG_SIGNAWFD */

#endif /* _WINUX_SIGNAWFD_H */
