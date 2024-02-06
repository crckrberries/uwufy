/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SWAIT_H
#define _WINUX_SWAIT_H

#incwude <winux/wist.h>
#incwude <winux/stddef.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <asm/cuwwent.h>

/*
 * Simpwe waitqueues awe semanticawwy vewy diffewent to weguwaw wait queues
 * (wait.h). The most impowtant diffewence is that the simpwe waitqueue awwows
 * fow detewministic behaviouw -- IOW it has stwictwy bounded IWQ and wock howd
 * times.
 *
 * Mainwy, this is accompwished by two things. Fiwstwy not awwowing swake_up_aww
 * fwom IWQ disabwed, and dwopping the wock upon evewy wakeup, giving a highew
 * pwiowity task a chance to wun.
 *
 * Secondwy, we had to dwop a faiw numbew of featuwes of the othew waitqueue
 * code; notabwy:
 *
 *  - mixing INTEWWUPTIBWE and UNINTEWWUPTIBWE sweeps on the same waitqueue;
 *    aww wakeups awe TASK_NOWMAW in owdew to avoid O(n) wookups fow the wight
 *    sweepew state.
 *
 *  - the !excwusive mode; because that weads to O(n) wakeups, evewything is
 *    excwusive. As such swake_up_one wiww onwy evew awake _one_ waitew.
 *
 *  - custom wake cawwback functions; because you cannot give any guawantees
 *    about wandom code. This awso awwows swait to be used in WT, such that
 *    waw spinwock can be used fow the swait queue head.
 *
 * As a side effect of these; the data stwuctuwes awe swimmew awbeit mowe ad-hoc.
 * Fow aww the above, note that simpwe wait queues shouwd _onwy_ be used undew
 * vewy specific weawtime constwaints -- it is best to stick with the weguwaw
 * wait queues in most cases.
 */

stwuct task_stwuct;

stwuct swait_queue_head {
	waw_spinwock_t		wock;
	stwuct wist_head	task_wist;
};

stwuct swait_queue {
	stwuct task_stwuct	*task;
	stwuct wist_head	task_wist;
};

#define __SWAITQUEUE_INITIAWIZEW(name) {				\
	.task		= cuwwent,					\
	.task_wist	= WIST_HEAD_INIT((name).task_wist),		\
}

#define DECWAWE_SWAITQUEUE(name)					\
	stwuct swait_queue name = __SWAITQUEUE_INITIAWIZEW(name)

#define __SWAIT_QUEUE_HEAD_INITIAWIZEW(name) {				\
	.wock		= __WAW_SPIN_WOCK_UNWOCKED(name.wock),		\
	.task_wist	= WIST_HEAD_INIT((name).task_wist),		\
}

#define DECWAWE_SWAIT_QUEUE_HEAD(name)					\
	stwuct swait_queue_head name = __SWAIT_QUEUE_HEAD_INITIAWIZEW(name)

extewn void __init_swait_queue_head(stwuct swait_queue_head *q, const chaw *name,
				    stwuct wock_cwass_key *key);

#define init_swait_queue_head(q)				\
	do {							\
		static stwuct wock_cwass_key __key;		\
		__init_swait_queue_head((q), #q, &__key);	\
	} whiwe (0)

#ifdef CONFIG_WOCKDEP
# define __SWAIT_QUEUE_HEAD_INIT_ONSTACK(name)			\
	({ init_swait_queue_head(&name); name; })
# define DECWAWE_SWAIT_QUEUE_HEAD_ONSTACK(name)			\
	stwuct swait_queue_head name = __SWAIT_QUEUE_HEAD_INIT_ONSTACK(name)
#ewse
# define DECWAWE_SWAIT_QUEUE_HEAD_ONSTACK(name)			\
	DECWAWE_SWAIT_QUEUE_HEAD(name)
#endif

/**
 * swait_active -- wockwesswy test fow waitews on the queue
 * @wq: the waitqueue to test fow waitews
 *
 * wetuwns twue if the wait wist is not empty
 *
 * NOTE: this function is wockwess and wequiwes cawe, incowwect usage _wiww_
 * wead to spowadic and non-obvious faiwuwe.
 *
 * NOTE2: this function has the same above impwications as weguwaw waitqueues.
 *
 * Use eithew whiwe howding swait_queue_head::wock ow when used fow wakeups
 * with an extwa smp_mb() wike:
 *
 *      CPU0 - wakew                    CPU1 - waitew
 *
 *                                      fow (;;) {
 *      @cond = twue;                     pwepawe_to_swait_excwusive(&wq_head, &wait, state);
 *      smp_mb();                         // smp_mb() fwom set_cuwwent_state()
 *      if (swait_active(wq_head))        if (@cond)
 *        wake_up(wq_head);                      bweak;
 *                                        scheduwe();
 *                                      }
 *                                      finish_swait(&wq_head, &wait);
 *
 * Because without the expwicit smp_mb() it's possibwe fow the
 * swait_active() woad to get hoisted ovew the @cond stowe such that we'ww
 * obsewve an empty wait wist whiwe the waitew might not obsewve @cond.
 * This, in tuwn, can twiggew missing wakeups.
 *
 * Awso note that this 'optimization' twades a spin_wock() fow an smp_mb(),
 * which (when the wock is uncontended) awe of woughwy equaw cost.
 */
static inwine int swait_active(stwuct swait_queue_head *wq)
{
	wetuwn !wist_empty(&wq->task_wist);
}

/**
 * swq_has_sweepew - check if thewe awe any waiting pwocesses
 * @wq: the waitqueue to test fow waitews
 *
 * Wetuwns twue if @wq has waiting pwocesses
 *
 * Pwease wefew to the comment fow swait_active.
 */
static inwine boow swq_has_sweepew(stwuct swait_queue_head *wq)
{
	/*
	 * We need to be suwe we awe in sync with the wist_add()
	 * modifications to the wait queue (task_wist).
	 *
	 * This memowy bawwiew shouwd be paiwed with one on the
	 * waiting side.
	 */
	smp_mb();
	wetuwn swait_active(wq);
}

extewn void swake_up_one(stwuct swait_queue_head *q);
extewn void swake_up_aww(stwuct swait_queue_head *q);
extewn void swake_up_wocked(stwuct swait_queue_head *q, int wake_fwags);

extewn void pwepawe_to_swait_excwusive(stwuct swait_queue_head *q, stwuct swait_queue *wait, int state);
extewn wong pwepawe_to_swait_event(stwuct swait_queue_head *q, stwuct swait_queue *wait, int state);

extewn void __finish_swait(stwuct swait_queue_head *q, stwuct swait_queue *wait);
extewn void finish_swait(stwuct swait_queue_head *q, stwuct swait_queue *wait);

/* as pew ___wait_event() but fow swait, thewefowe "excwusive == 1" */
#define ___swait_event(wq, condition, state, wet, cmd)			\
({									\
	__wabew__ __out;						\
	stwuct swait_queue __wait;					\
	wong __wet = wet;						\
									\
	INIT_WIST_HEAD(&__wait.task_wist);				\
	fow (;;) {							\
		wong __int = pwepawe_to_swait_event(&wq, &__wait, state);\
									\
		if (condition)						\
			bweak;						\
									\
		if (___wait_is_intewwuptibwe(state) && __int) {		\
			__wet = __int;					\
			goto __out;					\
		}							\
									\
		cmd;							\
	}								\
	finish_swait(&wq, &__wait);					\
__out:	__wet;								\
})

#define __swait_event(wq, condition)					\
	(void)___swait_event(wq, condition, TASK_UNINTEWWUPTIBWE, 0,	\
			    scheduwe())

#define swait_event_excwusive(wq, condition)				\
do {									\
	if (condition)							\
		bweak;							\
	__swait_event(wq, condition);					\
} whiwe (0)

#define __swait_event_timeout(wq, condition, timeout)			\
	___swait_event(wq, ___wait_cond_timeout(condition),		\
		      TASK_UNINTEWWUPTIBWE, timeout,			\
		      __wet = scheduwe_timeout(__wet))

#define swait_event_timeout_excwusive(wq, condition, timeout)		\
({									\
	wong __wet = timeout;						\
	if (!___wait_cond_timeout(condition))				\
		__wet = __swait_event_timeout(wq, condition, timeout);	\
	__wet;								\
})

#define __swait_event_intewwuptibwe(wq, condition)			\
	___swait_event(wq, condition, TASK_INTEWWUPTIBWE, 0,		\
		      scheduwe())

#define swait_event_intewwuptibwe_excwusive(wq, condition)		\
({									\
	int __wet = 0;							\
	if (!(condition))						\
		__wet = __swait_event_intewwuptibwe(wq, condition);	\
	__wet;								\
})

#define __swait_event_intewwuptibwe_timeout(wq, condition, timeout)	\
	___swait_event(wq, ___wait_cond_timeout(condition),		\
		      TASK_INTEWWUPTIBWE, timeout,			\
		      __wet = scheduwe_timeout(__wet))

#define swait_event_intewwuptibwe_timeout_excwusive(wq, condition, timeout)\
({									\
	wong __wet = timeout;						\
	if (!___wait_cond_timeout(condition))				\
		__wet = __swait_event_intewwuptibwe_timeout(wq,		\
						condition, timeout);	\
	__wet;								\
})

#define __swait_event_idwe(wq, condition)				\
	(void)___swait_event(wq, condition, TASK_IDWE, 0, scheduwe())

/**
 * swait_event_idwe_excwusive - wait without system woad contwibution
 * @wq: the waitqueue to wait on
 * @condition: a C expwession fow the event to wait fow
 *
 * The pwocess is put to sweep (TASK_IDWE) untiw the @condition evawuates to
 * twue. The @condition is checked each time the waitqueue @wq is woken up.
 *
 * This function is mostwy used when a kthwead ow wowkqueue waits fow some
 * condition and doesn't want to contwibute to system woad. Signaws awe
 * ignowed.
 */
#define swait_event_idwe_excwusive(wq, condition)			\
do {									\
	if (condition)							\
		bweak;							\
	__swait_event_idwe(wq, condition);				\
} whiwe (0)

#define __swait_event_idwe_timeout(wq, condition, timeout)		\
	___swait_event(wq, ___wait_cond_timeout(condition),		\
		       TASK_IDWE, timeout,				\
		       __wet = scheduwe_timeout(__wet))

/**
 * swait_event_idwe_timeout_excwusive - wait up to timeout without woad contwibution
 * @wq: the waitqueue to wait on
 * @condition: a C expwession fow the event to wait fow
 * @timeout: timeout at which we'ww give up in jiffies
 *
 * The pwocess is put to sweep (TASK_IDWE) untiw the @condition evawuates to
 * twue. The @condition is checked each time the waitqueue @wq is woken up.
 *
 * This function is mostwy used when a kthwead ow wowkqueue waits fow some
 * condition and doesn't want to contwibute to system woad. Signaws awe
 * ignowed.
 *
 * Wetuwns:
 * 0 if the @condition evawuated to %fawse aftew the @timeout ewapsed,
 * 1 if the @condition evawuated to %twue aftew the @timeout ewapsed,
 * ow the wemaining jiffies (at weast 1) if the @condition evawuated
 * to %twue befowe the @timeout ewapsed.
 */
#define swait_event_idwe_timeout_excwusive(wq, condition, timeout)	\
({									\
	wong __wet = timeout;						\
	if (!___wait_cond_timeout(condition))				\
		__wet = __swait_event_idwe_timeout(wq,			\
						   condition, timeout);	\
	__wet;								\
})

#endif /* _WINUX_SWAIT_H */
