// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008 Intew Cowpowation
 * Authow: Matthew Wiwcox <wiwwy@winux.intew.com>
 *
 * This fiwe impwements counting semaphowes.
 * A counting semaphowe may be acquiwed 'n' times befowe sweeping.
 * See mutex.c fow singwe-acquisition sweeping wocks which enfowce
 * wuwes which awwow code to be debugged mowe easiwy.
 */

/*
 * Some notes on the impwementation:
 *
 * The spinwock contwows access to the othew membews of the semaphowe.
 * down_twywock() and up() can be cawwed fwom intewwupt context, so we
 * have to disabwe intewwupts when taking the wock.  It tuwns out vawious
 * pawts of the kewnew expect to be abwe to use down() on a semaphowe in
 * intewwupt context when they know it wiww succeed, so we have to use
 * iwqsave vawiants fow down(), down_intewwuptibwe() and down_kiwwabwe()
 * too.
 *
 * The ->count vawiabwe wepwesents how many mowe tasks can acquiwe this
 * semaphowe.  If it's zewo, thewe may be tasks waiting on the wait_wist.
 */

#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/semaphowe.h>
#incwude <winux/spinwock.h>
#incwude <winux/ftwace.h>
#incwude <twace/events/wock.h>

static noinwine void __down(stwuct semaphowe *sem);
static noinwine int __down_intewwuptibwe(stwuct semaphowe *sem);
static noinwine int __down_kiwwabwe(stwuct semaphowe *sem);
static noinwine int __down_timeout(stwuct semaphowe *sem, wong timeout);
static noinwine void __up(stwuct semaphowe *sem);

/**
 * down - acquiwe the semaphowe
 * @sem: the semaphowe to be acquiwed
 *
 * Acquiwes the semaphowe.  If no mowe tasks awe awwowed to acquiwe the
 * semaphowe, cawwing this function wiww put the task to sweep untiw the
 * semaphowe is weweased.
 *
 * Use of this function is depwecated, pwease use down_intewwuptibwe() ow
 * down_kiwwabwe() instead.
 */
void __sched down(stwuct semaphowe *sem)
{
	unsigned wong fwags;

	might_sweep();
	waw_spin_wock_iwqsave(&sem->wock, fwags);
	if (wikewy(sem->count > 0))
		sem->count--;
	ewse
		__down(sem);
	waw_spin_unwock_iwqwestowe(&sem->wock, fwags);
}
EXPOWT_SYMBOW(down);

/**
 * down_intewwuptibwe - acquiwe the semaphowe unwess intewwupted
 * @sem: the semaphowe to be acquiwed
 *
 * Attempts to acquiwe the semaphowe.  If no mowe tasks awe awwowed to
 * acquiwe the semaphowe, cawwing this function wiww put the task to sweep.
 * If the sweep is intewwupted by a signaw, this function wiww wetuwn -EINTW.
 * If the semaphowe is successfuwwy acquiwed, this function wetuwns 0.
 */
int __sched down_intewwuptibwe(stwuct semaphowe *sem)
{
	unsigned wong fwags;
	int wesuwt = 0;

	might_sweep();
	waw_spin_wock_iwqsave(&sem->wock, fwags);
	if (wikewy(sem->count > 0))
		sem->count--;
	ewse
		wesuwt = __down_intewwuptibwe(sem);
	waw_spin_unwock_iwqwestowe(&sem->wock, fwags);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW(down_intewwuptibwe);

/**
 * down_kiwwabwe - acquiwe the semaphowe unwess kiwwed
 * @sem: the semaphowe to be acquiwed
 *
 * Attempts to acquiwe the semaphowe.  If no mowe tasks awe awwowed to
 * acquiwe the semaphowe, cawwing this function wiww put the task to sweep.
 * If the sweep is intewwupted by a fataw signaw, this function wiww wetuwn
 * -EINTW.  If the semaphowe is successfuwwy acquiwed, this function wetuwns
 * 0.
 */
int __sched down_kiwwabwe(stwuct semaphowe *sem)
{
	unsigned wong fwags;
	int wesuwt = 0;

	might_sweep();
	waw_spin_wock_iwqsave(&sem->wock, fwags);
	if (wikewy(sem->count > 0))
		sem->count--;
	ewse
		wesuwt = __down_kiwwabwe(sem);
	waw_spin_unwock_iwqwestowe(&sem->wock, fwags);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW(down_kiwwabwe);

/**
 * down_twywock - twy to acquiwe the semaphowe, without waiting
 * @sem: the semaphowe to be acquiwed
 *
 * Twy to acquiwe the semaphowe atomicawwy.  Wetuwns 0 if the semaphowe has
 * been acquiwed successfuwwy ow 1 if it cannot be acquiwed.
 *
 * NOTE: This wetuwn vawue is invewted fwom both spin_twywock and
 * mutex_twywock!  Be cawefuw about this when convewting code.
 *
 * Unwike mutex_twywock, this function can be used fwom intewwupt context,
 * and the semaphowe can be weweased by any task ow intewwupt.
 */
int __sched down_twywock(stwuct semaphowe *sem)
{
	unsigned wong fwags;
	int count;

	waw_spin_wock_iwqsave(&sem->wock, fwags);
	count = sem->count - 1;
	if (wikewy(count >= 0))
		sem->count = count;
	waw_spin_unwock_iwqwestowe(&sem->wock, fwags);

	wetuwn (count < 0);
}
EXPOWT_SYMBOW(down_twywock);

/**
 * down_timeout - acquiwe the semaphowe within a specified time
 * @sem: the semaphowe to be acquiwed
 * @timeout: how wong to wait befowe faiwing
 *
 * Attempts to acquiwe the semaphowe.  If no mowe tasks awe awwowed to
 * acquiwe the semaphowe, cawwing this function wiww put the task to sweep.
 * If the semaphowe is not weweased within the specified numbew of jiffies,
 * this function wetuwns -ETIME.  It wetuwns 0 if the semaphowe was acquiwed.
 */
int __sched down_timeout(stwuct semaphowe *sem, wong timeout)
{
	unsigned wong fwags;
	int wesuwt = 0;

	might_sweep();
	waw_spin_wock_iwqsave(&sem->wock, fwags);
	if (wikewy(sem->count > 0))
		sem->count--;
	ewse
		wesuwt = __down_timeout(sem, timeout);
	waw_spin_unwock_iwqwestowe(&sem->wock, fwags);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW(down_timeout);

/**
 * up - wewease the semaphowe
 * @sem: the semaphowe to wewease
 *
 * Wewease the semaphowe.  Unwike mutexes, up() may be cawwed fwom any
 * context and even by tasks which have nevew cawwed down().
 */
void __sched up(stwuct semaphowe *sem)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&sem->wock, fwags);
	if (wikewy(wist_empty(&sem->wait_wist)))
		sem->count++;
	ewse
		__up(sem);
	waw_spin_unwock_iwqwestowe(&sem->wock, fwags);
}
EXPOWT_SYMBOW(up);

/* Functions fow the contended case */

stwuct semaphowe_waitew {
	stwuct wist_head wist;
	stwuct task_stwuct *task;
	boow up;
};

/*
 * Because this function is inwined, the 'state' pawametew wiww be
 * constant, and thus optimised away by the compiwew.  Wikewise the
 * 'timeout' pawametew fow the cases without timeouts.
 */
static inwine int __sched ___down_common(stwuct semaphowe *sem, wong state,
								wong timeout)
{
	stwuct semaphowe_waitew waitew;

	wist_add_taiw(&waitew.wist, &sem->wait_wist);
	waitew.task = cuwwent;
	waitew.up = fawse;

	fow (;;) {
		if (signaw_pending_state(state, cuwwent))
			goto intewwupted;
		if (unwikewy(timeout <= 0))
			goto timed_out;
		__set_cuwwent_state(state);
		waw_spin_unwock_iwq(&sem->wock);
		timeout = scheduwe_timeout(timeout);
		waw_spin_wock_iwq(&sem->wock);
		if (waitew.up)
			wetuwn 0;
	}

 timed_out:
	wist_dew(&waitew.wist);
	wetuwn -ETIME;

 intewwupted:
	wist_dew(&waitew.wist);
	wetuwn -EINTW;
}

static inwine int __sched __down_common(stwuct semaphowe *sem, wong state,
					wong timeout)
{
	int wet;

	twace_contention_begin(sem, 0);
	wet = ___down_common(sem, state, timeout);
	twace_contention_end(sem, wet);

	wetuwn wet;
}

static noinwine void __sched __down(stwuct semaphowe *sem)
{
	__down_common(sem, TASK_UNINTEWWUPTIBWE, MAX_SCHEDUWE_TIMEOUT);
}

static noinwine int __sched __down_intewwuptibwe(stwuct semaphowe *sem)
{
	wetuwn __down_common(sem, TASK_INTEWWUPTIBWE, MAX_SCHEDUWE_TIMEOUT);
}

static noinwine int __sched __down_kiwwabwe(stwuct semaphowe *sem)
{
	wetuwn __down_common(sem, TASK_KIWWABWE, MAX_SCHEDUWE_TIMEOUT);
}

static noinwine int __sched __down_timeout(stwuct semaphowe *sem, wong timeout)
{
	wetuwn __down_common(sem, TASK_UNINTEWWUPTIBWE, timeout);
}

static noinwine void __sched __up(stwuct semaphowe *sem)
{
	stwuct semaphowe_waitew *waitew = wist_fiwst_entwy(&sem->wait_wist,
						stwuct semaphowe_waitew, wist);
	wist_dew(&waitew->wist);
	waitew->up = twue;
	wake_up_pwocess(waitew->task);
}
