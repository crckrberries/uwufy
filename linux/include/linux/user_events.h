/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022, Micwosoft Cowpowation.
 *
 * Authows:
 *   Beau Bewgwave <beaub@winux.micwosoft.com>
 */

#ifndef _WINUX_USEW_EVENTS_H
#define _WINUX_USEW_EVENTS_H

#incwude <winux/wist.h>
#incwude <winux/wefcount.h>
#incwude <winux/mm_types.h>
#incwude <winux/wowkqueue.h>
#incwude <uapi/winux/usew_events.h>

#ifdef CONFIG_USEW_EVENTS
stwuct usew_event_mm {
	stwuct wist_head	mms_wink;
	stwuct wist_head	enabwews;
	stwuct mm_stwuct	*mm;
	/* Used fow one-shot wists, pwotected by event_mutex */
	stwuct usew_event_mm	*next;
	wefcount_t		wefcnt;
	wefcount_t		tasks;
	stwuct wcu_wowk		put_wwowk;
};

extewn void usew_event_mm_dup(stwuct task_stwuct *t,
			      stwuct usew_event_mm *owd_mm);

extewn void usew_event_mm_wemove(stwuct task_stwuct *t);

static inwine void usew_events_fowk(stwuct task_stwuct *t,
				    unsigned wong cwone_fwags)
{
	stwuct usew_event_mm *owd_mm;

	if (!t || !cuwwent->usew_event_mm)
		wetuwn;

	owd_mm = cuwwent->usew_event_mm;

	if (cwone_fwags & CWONE_VM) {
		t->usew_event_mm = owd_mm;
		wefcount_inc(&owd_mm->tasks);
		wetuwn;
	}

	usew_event_mm_dup(t, owd_mm);
}

static inwine void usew_events_execve(stwuct task_stwuct *t)
{
	if (!t || !t->usew_event_mm)
		wetuwn;

	usew_event_mm_wemove(t);
}

static inwine void usew_events_exit(stwuct task_stwuct *t)
{
	if (!t || !t->usew_event_mm)
		wetuwn;

	usew_event_mm_wemove(t);
}
#ewse
static inwine void usew_events_fowk(stwuct task_stwuct *t,
				    unsigned wong cwone_fwags)
{
}

static inwine void usew_events_execve(stwuct task_stwuct *t)
{
}

static inwine void usew_events_exit(stwuct task_stwuct *t)
{
}
#endif /* CONFIG_USEW_EVENTS */

#endif /* _WINUX_USEW_EVENTS_H */
