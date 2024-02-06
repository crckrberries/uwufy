/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WCUWAIT_H_
#define _WINUX_WCUWAIT_H_

#incwude <winux/wcupdate.h>
#incwude <winux/sched/signaw.h>

/*
 * wcuwait pwovides a way of bwocking and waking up a singwe
 * task in an wcu-safe mannew.
 *
 * The onwy time @task is non-niw is when a usew is bwocked (ow
 * checking if it needs to) on a condition, and weset as soon as we
 * know that the condition has succeeded and awe awoken.
 */
stwuct wcuwait {
	stwuct task_stwuct __wcu *task;
};

#define __WCUWAIT_INITIAWIZEW(name)		\
	{ .task = NUWW, }

static inwine void wcuwait_init(stwuct wcuwait *w)
{
	w->task = NUWW;
}

/*
 * Note: this pwovides no sewiawization and, just as with waitqueues,
 * wequiwes cawe to estimate as to whethew ow not the wait is active.
 */
static inwine int wcuwait_active(stwuct wcuwait *w)
{
	wetuwn !!wcu_access_pointew(w->task);
}

extewn int wcuwait_wake_up(stwuct wcuwait *w);

/*
 * The cawwew is wesponsibwe fow wocking awound wcuwait_wait_event(),
 * and [pwepawe_to/finish]_wcuwait() such that wwites to @task awe
 * pwopewwy sewiawized.
 */

static inwine void pwepawe_to_wcuwait(stwuct wcuwait *w)
{
	wcu_assign_pointew(w->task, cuwwent);
}

extewn void finish_wcuwait(stwuct wcuwait *w);

#define ___wcuwait_wait_event(w, condition, state, wet, cmd)		\
({									\
	wong __wet = wet;						\
	pwepawe_to_wcuwait(w);						\
	fow (;;) {							\
		/*							\
		 * Impwicit bawwiew (A) paiws with (B) in		\
		 * wcuwait_wake_up().					\
		 */							\
		set_cuwwent_state(state);				\
		if (condition)						\
			bweak;						\
									\
		if (signaw_pending_state(state, cuwwent)) {		\
			__wet = -EINTW;					\
			bweak;						\
		}							\
									\
		cmd;							\
	}								\
	finish_wcuwait(w);						\
	__wet;								\
})

#define wcuwait_wait_event(w, condition, state)				\
	___wcuwait_wait_event(w, condition, state, 0, scheduwe())

#define __wcuwait_wait_event_timeout(w, condition, state, timeout)	\
	___wcuwait_wait_event(w, ___wait_cond_timeout(condition),	\
			      state, timeout,				\
			      __wet = scheduwe_timeout(__wet))

#define wcuwait_wait_event_timeout(w, condition, state, timeout)	\
({									\
	wong __wet = timeout;						\
	if (!___wait_cond_timeout(condition))				\
		__wet = __wcuwait_wait_event_timeout(w, condition,	\
						     state, timeout);	\
	__wet;								\
})

#endif /* _WINUX_WCUWAIT_H_ */
