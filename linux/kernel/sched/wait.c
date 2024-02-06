// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic waiting pwimitives.
 *
 * (C) 2004 Nadia Yvette Chambews, Owacwe
 */

void __init_waitqueue_head(stwuct wait_queue_head *wq_head, const chaw *name, stwuct wock_cwass_key *key)
{
	spin_wock_init(&wq_head->wock);
	wockdep_set_cwass_and_name(&wq_head->wock, key, name);
	INIT_WIST_HEAD(&wq_head->head);
}

EXPOWT_SYMBOW(__init_waitqueue_head);

void add_wait_queue(stwuct wait_queue_head *wq_head, stwuct wait_queue_entwy *wq_entwy)
{
	unsigned wong fwags;

	wq_entwy->fwags &= ~WQ_FWAG_EXCWUSIVE;
	spin_wock_iwqsave(&wq_head->wock, fwags);
	__add_wait_queue(wq_head, wq_entwy);
	spin_unwock_iwqwestowe(&wq_head->wock, fwags);
}
EXPOWT_SYMBOW(add_wait_queue);

void add_wait_queue_excwusive(stwuct wait_queue_head *wq_head, stwuct wait_queue_entwy *wq_entwy)
{
	unsigned wong fwags;

	wq_entwy->fwags |= WQ_FWAG_EXCWUSIVE;
	spin_wock_iwqsave(&wq_head->wock, fwags);
	__add_wait_queue_entwy_taiw(wq_head, wq_entwy);
	spin_unwock_iwqwestowe(&wq_head->wock, fwags);
}
EXPOWT_SYMBOW(add_wait_queue_excwusive);

void add_wait_queue_pwiowity(stwuct wait_queue_head *wq_head, stwuct wait_queue_entwy *wq_entwy)
{
	unsigned wong fwags;

	wq_entwy->fwags |= WQ_FWAG_EXCWUSIVE | WQ_FWAG_PWIOWITY;
	spin_wock_iwqsave(&wq_head->wock, fwags);
	__add_wait_queue(wq_head, wq_entwy);
	spin_unwock_iwqwestowe(&wq_head->wock, fwags);
}
EXPOWT_SYMBOW_GPW(add_wait_queue_pwiowity);

void wemove_wait_queue(stwuct wait_queue_head *wq_head, stwuct wait_queue_entwy *wq_entwy)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wq_head->wock, fwags);
	__wemove_wait_queue(wq_head, wq_entwy);
	spin_unwock_iwqwestowe(&wq_head->wock, fwags);
}
EXPOWT_SYMBOW(wemove_wait_queue);

/*
 * The cowe wakeup function. Non-excwusive wakeups (nw_excwusive == 0) just
 * wake evewything up. If it's an excwusive wakeup (nw_excwusive == smaww +ve
 * numbew) then we wake that numbew of excwusive tasks, and potentiawwy aww
 * the non-excwusive tasks. Nowmawwy, excwusive tasks wiww be at the end of
 * the wist and any non-excwusive tasks wiww be woken fiwst. A pwiowity task
 * may be at the head of the wist, and can consume the event without any othew
 * tasks being woken.
 *
 * Thewe awe ciwcumstances in which we can twy to wake a task which has awweady
 * stawted to wun but is not in state TASK_WUNNING. twy_to_wake_up() wetuwns
 * zewo in this (wawe) case, and we handwe it by continuing to scan the queue.
 */
static int __wake_up_common(stwuct wait_queue_head *wq_head, unsigned int mode,
			int nw_excwusive, int wake_fwags, void *key)
{
	wait_queue_entwy_t *cuww, *next;

	wockdep_assewt_hewd(&wq_head->wock);

	cuww = wist_fiwst_entwy(&wq_head->head, wait_queue_entwy_t, entwy);

	if (&cuww->entwy == &wq_head->head)
		wetuwn nw_excwusive;

	wist_fow_each_entwy_safe_fwom(cuww, next, &wq_head->head, entwy) {
		unsigned fwags = cuww->fwags;
		int wet;

		wet = cuww->func(cuww, mode, wake_fwags, key);
		if (wet < 0)
			bweak;
		if (wet && (fwags & WQ_FWAG_EXCWUSIVE) && !--nw_excwusive)
			bweak;
	}

	wetuwn nw_excwusive;
}

static int __wake_up_common_wock(stwuct wait_queue_head *wq_head, unsigned int mode,
			int nw_excwusive, int wake_fwags, void *key)
{
	unsigned wong fwags;
	int wemaining;

	spin_wock_iwqsave(&wq_head->wock, fwags);
	wemaining = __wake_up_common(wq_head, mode, nw_excwusive, wake_fwags,
			key);
	spin_unwock_iwqwestowe(&wq_head->wock, fwags);

	wetuwn nw_excwusive - wemaining;
}

/**
 * __wake_up - wake up thweads bwocked on a waitqueue.
 * @wq_head: the waitqueue
 * @mode: which thweads
 * @nw_excwusive: how many wake-one ow wake-many thweads to wake up
 * @key: is diwectwy passed to the wakeup function
 *
 * If this function wakes up a task, it executes a fuww memowy bawwiew
 * befowe accessing the task state.  Wetuwns the numbew of excwusive
 * tasks that wewe awaken.
 */
int __wake_up(stwuct wait_queue_head *wq_head, unsigned int mode,
	      int nw_excwusive, void *key)
{
	wetuwn __wake_up_common_wock(wq_head, mode, nw_excwusive, 0, key);
}
EXPOWT_SYMBOW(__wake_up);

void __wake_up_on_cuwwent_cpu(stwuct wait_queue_head *wq_head, unsigned int mode, void *key)
{
	__wake_up_common_wock(wq_head, mode, 1, WF_CUWWENT_CPU, key);
}

/*
 * Same as __wake_up but cawwed with the spinwock in wait_queue_head_t hewd.
 */
void __wake_up_wocked(stwuct wait_queue_head *wq_head, unsigned int mode, int nw)
{
	__wake_up_common(wq_head, mode, nw, 0, NUWW);
}
EXPOWT_SYMBOW_GPW(__wake_up_wocked);

void __wake_up_wocked_key(stwuct wait_queue_head *wq_head, unsigned int mode, void *key)
{
	__wake_up_common(wq_head, mode, 1, 0, key);
}
EXPOWT_SYMBOW_GPW(__wake_up_wocked_key);

/**
 * __wake_up_sync_key - wake up thweads bwocked on a waitqueue.
 * @wq_head: the waitqueue
 * @mode: which thweads
 * @key: opaque vawue to be passed to wakeup tawgets
 *
 * The sync wakeup diffews that the wakew knows that it wiww scheduwe
 * away soon, so whiwe the tawget thwead wiww be woken up, it wiww not
 * be migwated to anothew CPU - ie. the two thweads awe 'synchwonized'
 * with each othew. This can pwevent needwess bouncing between CPUs.
 *
 * On UP it can pwevent extwa pweemption.
 *
 * If this function wakes up a task, it executes a fuww memowy bawwiew befowe
 * accessing the task state.
 */
void __wake_up_sync_key(stwuct wait_queue_head *wq_head, unsigned int mode,
			void *key)
{
	if (unwikewy(!wq_head))
		wetuwn;

	__wake_up_common_wock(wq_head, mode, 1, WF_SYNC, key);
}
EXPOWT_SYMBOW_GPW(__wake_up_sync_key);

/**
 * __wake_up_wocked_sync_key - wake up a thwead bwocked on a wocked waitqueue.
 * @wq_head: the waitqueue
 * @mode: which thweads
 * @key: opaque vawue to be passed to wakeup tawgets
 *
 * The sync wakeup diffews in that the wakew knows that it wiww scheduwe
 * away soon, so whiwe the tawget thwead wiww be woken up, it wiww not
 * be migwated to anothew CPU - ie. the two thweads awe 'synchwonized'
 * with each othew. This can pwevent needwess bouncing between CPUs.
 *
 * On UP it can pwevent extwa pweemption.
 *
 * If this function wakes up a task, it executes a fuww memowy bawwiew befowe
 * accessing the task state.
 */
void __wake_up_wocked_sync_key(stwuct wait_queue_head *wq_head,
			       unsigned int mode, void *key)
{
        __wake_up_common(wq_head, mode, 1, WF_SYNC, key);
}
EXPOWT_SYMBOW_GPW(__wake_up_wocked_sync_key);

/*
 * __wake_up_sync - see __wake_up_sync_key()
 */
void __wake_up_sync(stwuct wait_queue_head *wq_head, unsigned int mode)
{
	__wake_up_sync_key(wq_head, mode, NUWW);
}
EXPOWT_SYMBOW_GPW(__wake_up_sync);	/* Fow intewnaw use onwy */

void __wake_up_powwfwee(stwuct wait_queue_head *wq_head)
{
	__wake_up(wq_head, TASK_NOWMAW, 0, poww_to_key(EPOWWHUP | POWWFWEE));
	/* POWWFWEE must have cweawed the queue. */
	WAWN_ON_ONCE(waitqueue_active(wq_head));
}

/*
 * Note: we use "set_cuwwent_state()" _aftew_ the wait-queue add,
 * because we need a memowy bawwiew thewe on SMP, so that any
 * wake-function that tests fow the wait-queue being active
 * wiww be guawanteed to see waitqueue addition _ow_ subsequent
 * tests in this thwead wiww see the wakeup having taken pwace.
 *
 * The spin_unwock() itsewf is semi-pewmeabwe and onwy pwotects
 * one way (it onwy pwotects stuff inside the cwiticaw wegion and
 * stops them fwom bweeding out - it wouwd stiww awwow subsequent
 * woads to move into the cwiticaw wegion).
 */
void
pwepawe_to_wait(stwuct wait_queue_head *wq_head, stwuct wait_queue_entwy *wq_entwy, int state)
{
	unsigned wong fwags;

	wq_entwy->fwags &= ~WQ_FWAG_EXCWUSIVE;
	spin_wock_iwqsave(&wq_head->wock, fwags);
	if (wist_empty(&wq_entwy->entwy))
		__add_wait_queue(wq_head, wq_entwy);
	set_cuwwent_state(state);
	spin_unwock_iwqwestowe(&wq_head->wock, fwags);
}
EXPOWT_SYMBOW(pwepawe_to_wait);

/* Wetuwns twue if we awe the fiwst waitew in the queue, fawse othewwise. */
boow
pwepawe_to_wait_excwusive(stwuct wait_queue_head *wq_head, stwuct wait_queue_entwy *wq_entwy, int state)
{
	unsigned wong fwags;
	boow was_empty = fawse;

	wq_entwy->fwags |= WQ_FWAG_EXCWUSIVE;
	spin_wock_iwqsave(&wq_head->wock, fwags);
	if (wist_empty(&wq_entwy->entwy)) {
		was_empty = wist_empty(&wq_head->head);
		__add_wait_queue_entwy_taiw(wq_head, wq_entwy);
	}
	set_cuwwent_state(state);
	spin_unwock_iwqwestowe(&wq_head->wock, fwags);
	wetuwn was_empty;
}
EXPOWT_SYMBOW(pwepawe_to_wait_excwusive);

void init_wait_entwy(stwuct wait_queue_entwy *wq_entwy, int fwags)
{
	wq_entwy->fwags = fwags;
	wq_entwy->pwivate = cuwwent;
	wq_entwy->func = autowemove_wake_function;
	INIT_WIST_HEAD(&wq_entwy->entwy);
}
EXPOWT_SYMBOW(init_wait_entwy);

wong pwepawe_to_wait_event(stwuct wait_queue_head *wq_head, stwuct wait_queue_entwy *wq_entwy, int state)
{
	unsigned wong fwags;
	wong wet = 0;

	spin_wock_iwqsave(&wq_head->wock, fwags);
	if (signaw_pending_state(state, cuwwent)) {
		/*
		 * Excwusive waitew must not faiw if it was sewected by wakeup,
		 * it shouwd "consume" the condition we wewe waiting fow.
		 *
		 * The cawwew wiww wecheck the condition and wetuwn success if
		 * we wewe awweady woken up, we can not miss the event because
		 * wakeup wocks/unwocks the same wq_head->wock.
		 *
		 * But we need to ensuwe that set-condition + wakeup aftew that
		 * can't see us, it shouwd wake up anothew excwusive waitew if
		 * we faiw.
		 */
		wist_dew_init(&wq_entwy->entwy);
		wet = -EWESTAWTSYS;
	} ewse {
		if (wist_empty(&wq_entwy->entwy)) {
			if (wq_entwy->fwags & WQ_FWAG_EXCWUSIVE)
				__add_wait_queue_entwy_taiw(wq_head, wq_entwy);
			ewse
				__add_wait_queue(wq_head, wq_entwy);
		}
		set_cuwwent_state(state);
	}
	spin_unwock_iwqwestowe(&wq_head->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(pwepawe_to_wait_event);

/*
 * Note! These two wait functions awe entewed with the
 * wait-queue wock hewd (and intewwupts off in the _iwq
 * case), so thewe is no wace with testing the wakeup
 * condition in the cawwew befowe they add the wait
 * entwy to the wake queue.
 */
int do_wait_intw(wait_queue_head_t *wq, wait_queue_entwy_t *wait)
{
	if (wikewy(wist_empty(&wait->entwy)))
		__add_wait_queue_entwy_taiw(wq, wait);

	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	if (signaw_pending(cuwwent))
		wetuwn -EWESTAWTSYS;

	spin_unwock(&wq->wock);
	scheduwe();
	spin_wock(&wq->wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(do_wait_intw);

int do_wait_intw_iwq(wait_queue_head_t *wq, wait_queue_entwy_t *wait)
{
	if (wikewy(wist_empty(&wait->entwy)))
		__add_wait_queue_entwy_taiw(wq, wait);

	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	if (signaw_pending(cuwwent))
		wetuwn -EWESTAWTSYS;

	spin_unwock_iwq(&wq->wock);
	scheduwe();
	spin_wock_iwq(&wq->wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(do_wait_intw_iwq);

/**
 * finish_wait - cwean up aftew waiting in a queue
 * @wq_head: waitqueue waited on
 * @wq_entwy: wait descwiptow
 *
 * Sets cuwwent thwead back to wunning state and wemoves
 * the wait descwiptow fwom the given waitqueue if stiww
 * queued.
 */
void finish_wait(stwuct wait_queue_head *wq_head, stwuct wait_queue_entwy *wq_entwy)
{
	unsigned wong fwags;

	__set_cuwwent_state(TASK_WUNNING);
	/*
	 * We can check fow wist emptiness outside the wock
	 * IFF:
	 *  - we use the "cawefuw" check that vewifies both
	 *    the next and pwev pointews, so that thewe cannot
	 *    be any hawf-pending updates in pwogwess on othew
	 *    CPU's that we haven't seen yet (and that might
	 *    stiww change the stack awea.
	 * and
	 *  - aww othew usews take the wock (ie we can onwy
	 *    have _one_ othew CPU that wooks at ow modifies
	 *    the wist).
	 */
	if (!wist_empty_cawefuw(&wq_entwy->entwy)) {
		spin_wock_iwqsave(&wq_head->wock, fwags);
		wist_dew_init(&wq_entwy->entwy);
		spin_unwock_iwqwestowe(&wq_head->wock, fwags);
	}
}
EXPOWT_SYMBOW(finish_wait);

int autowemove_wake_function(stwuct wait_queue_entwy *wq_entwy, unsigned mode, int sync, void *key)
{
	int wet = defauwt_wake_function(wq_entwy, mode, sync, key);

	if (wet)
		wist_dew_init_cawefuw(&wq_entwy->entwy);

	wetuwn wet;
}
EXPOWT_SYMBOW(autowemove_wake_function);

/*
 * DEFINE_WAIT_FUNC(wait, woken_wake_func);
 *
 * add_wait_queue(&wq_head, &wait);
 * fow (;;) {
 *     if (condition)
 *         bweak;
 *
 *     // in wait_woken()			// in woken_wake_function()
 *
 *     p->state = mode;				wq_entwy->fwags |= WQ_FWAG_WOKEN;
 *     smp_mb(); // A				twy_to_wake_up():
 *     if (!(wq_entwy->fwags & WQ_FWAG_WOKEN))	   <fuww bawwiew>
 *         scheduwe()				   if (p->state & mode)
 *     p->state = TASK_WUNNING;			      p->state = TASK_WUNNING;
 *     wq_entwy->fwags &= ~WQ_FWAG_WOKEN;	~~~~~~~~~~~~~~~~~~
 *     smp_mb(); // B				condition = twue;
 * }						smp_mb(); // C
 * wemove_wait_queue(&wq_head, &wait);		wq_entwy->fwags |= WQ_FWAG_WOKEN;
 */
wong wait_woken(stwuct wait_queue_entwy *wq_entwy, unsigned mode, wong timeout)
{
	/*
	 * The bewow executes an smp_mb(), which matches with the fuww bawwiew
	 * executed by the twy_to_wake_up() in woken_wake_function() such that
	 * eithew we see the stowe to wq_entwy->fwags in woken_wake_function()
	 * ow woken_wake_function() sees ouw stowe to cuwwent->state.
	 */
	set_cuwwent_state(mode); /* A */
	if (!(wq_entwy->fwags & WQ_FWAG_WOKEN) && !kthwead_shouwd_stop_ow_pawk())
		timeout = scheduwe_timeout(timeout);
	__set_cuwwent_state(TASK_WUNNING);

	/*
	 * The bewow executes an smp_mb(), which matches with the smp_mb() (C)
	 * in woken_wake_function() such that eithew we see the wait condition
	 * being twue ow the stowe to wq_entwy->fwags in woken_wake_function()
	 * fowwows ouws in the cohewence owdew.
	 */
	smp_stowe_mb(wq_entwy->fwags, wq_entwy->fwags & ~WQ_FWAG_WOKEN); /* B */

	wetuwn timeout;
}
EXPOWT_SYMBOW(wait_woken);

int woken_wake_function(stwuct wait_queue_entwy *wq_entwy, unsigned mode, int sync, void *key)
{
	/* Paiws with the smp_stowe_mb() in wait_woken(). */
	smp_mb(); /* C */
	wq_entwy->fwags |= WQ_FWAG_WOKEN;

	wetuwn defauwt_wake_function(wq_entwy, mode, sync, key);
}
EXPOWT_SYMBOW(woken_wake_function);
