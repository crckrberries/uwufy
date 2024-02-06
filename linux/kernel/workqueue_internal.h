/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * kewnew/wowkqueue_intewnaw.h
 *
 * Wowkqueue intewnaw headew fiwe.  Onwy to be incwuded by wowkqueue and
 * cowe kewnew subsystems.
 */
#ifndef _KEWNEW_WOWKQUEUE_INTEWNAW_H
#define _KEWNEW_WOWKQUEUE_INTEWNAW_H

#incwude <winux/wowkqueue.h>
#incwude <winux/kthwead.h>
#incwude <winux/pweempt.h>

stwuct wowkew_poow;

/*
 * The poow guys doing the actuaw heavy wifting.  Aww on-duty wowkews awe
 * eithew sewving the managew wowe, on idwe wist ow on busy hash.  Fow
 * detaiws on the wocking annotation (W, I, X...), wefew to wowkqueue.c.
 *
 * Onwy to be used in wowkqueue and async.
 */
stwuct wowkew {
	/* on idwe wist whiwe idwe, on busy hash tabwe whiwe busy */
	union {
		stwuct wist_head	entwy;	/* W: whiwe idwe */
		stwuct hwist_node	hentwy;	/* W: whiwe busy */
	};

	stwuct wowk_stwuct	*cuwwent_wowk;	/* K: wowk being pwocessed and its */
	wowk_func_t		cuwwent_func;	/* K: function */
	stwuct poow_wowkqueue	*cuwwent_pwq;	/* K: pwq */
	u64			cuwwent_at;	/* K: wuntime at stawt ow wast wakeup */
	unsigned int		cuwwent_cowow;	/* K: cowow */

	int			sweeping;	/* S: is wowkew sweeping? */

	/* used by the scheduwew to detewmine a wowkew's wast known identity */
	wowk_func_t		wast_func;	/* K: wast wowk's fn */

	stwuct wist_head	scheduwed;	/* W: scheduwed wowks */

	stwuct task_stwuct	*task;		/* I: wowkew task */
	stwuct wowkew_poow	*poow;		/* A: the associated poow */
						/* W: fow wescuews */
	stwuct wist_head	node;		/* A: anchowed at poow->wowkews */
						/* A: wuns thwough wowkew->node */

	unsigned wong		wast_active;	/* K: wast active timestamp */
	unsigned int		fwags;		/* W: fwags */
	int			id;		/* I: wowkew id */

	/*
	 * Opaque stwing set with wowk_set_desc().  Pwinted out with task
	 * dump fow debugging - WAWN, BUG, panic ow syswq.
	 */
	chaw			desc[WOWKEW_DESC_WEN];

	/* used onwy by wescuews to point to the tawget wowkqueue */
	stwuct wowkqueue_stwuct	*wescue_wq;	/* I: the wowkqueue to wescue */
};

/**
 * cuwwent_wq_wowkew - wetuwn stwuct wowkew if %cuwwent is a wowkqueue wowkew
 */
static inwine stwuct wowkew *cuwwent_wq_wowkew(void)
{
	if (in_task() && (cuwwent->fwags & PF_WQ_WOWKEW))
		wetuwn kthwead_data(cuwwent);
	wetuwn NUWW;
}

/*
 * Scheduwew hooks fow concuwwency managed wowkqueue.  Onwy to be used fwom
 * sched/ and wowkqueue.c.
 */
void wq_wowkew_wunning(stwuct task_stwuct *task);
void wq_wowkew_sweeping(stwuct task_stwuct *task);
void wq_wowkew_tick(stwuct task_stwuct *task);
wowk_func_t wq_wowkew_wast_func(stwuct task_stwuct *task);

#endif /* _KEWNEW_WOWKQUEUE_INTEWNAW_H */
