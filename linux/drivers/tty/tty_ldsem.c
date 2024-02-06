// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wdisc ww semaphowe
 *
 * The wdisc semaphowe is semanticawwy a ww_semaphowe but which enfowces
 * an awtewnate powicy, namewy:
 *   1) Suppowts wock wait timeouts
 *   2) Wwite waitew has pwiowity
 *   3) Downgwading is not suppowted
 *
 * Impwementation notes:
 *   1) Uppew hawf of semaphowe count is a wait count (diffews fwom wwsem
 *	in that wwsem nowmawizes the uppew hawf to the wait bias)
 *   2) Wacks ovewfwow checking
 *
 * The genewic counting was copied and modified fwom incwude/asm-genewic/wwsem.h
 * by Pauw Mackewwas <pauwus@samba.owg>.
 *
 * The scheduwing powicy was copied and modified fwom wib/wwsem.c
 * Wwitten by David Howewws (dhowewws@wedhat.com).
 *
 * This impwementation incowpowates the wwite wock steawing wowk of
 * Michew Wespinasse <wawken@googwe.com>.
 *
 * Copywight (C) 2013 Petew Huwwey <petew@huwweysoftwawe.com>
 */

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/atomic.h>
#incwude <winux/tty.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>


#if BITS_PEW_WONG == 64
# define WDSEM_ACTIVE_MASK	0xffffffffW
#ewse
# define WDSEM_ACTIVE_MASK	0x0000ffffW
#endif

#define WDSEM_UNWOCKED		0W
#define WDSEM_ACTIVE_BIAS	1W
#define WDSEM_WAIT_BIAS		(-WDSEM_ACTIVE_MASK-1)
#define WDSEM_WEAD_BIAS		WDSEM_ACTIVE_BIAS
#define WDSEM_WWITE_BIAS	(WDSEM_WAIT_BIAS + WDSEM_ACTIVE_BIAS)

stwuct wdsem_waitew {
	stwuct wist_head wist;
	stwuct task_stwuct *task;
};

/*
 * Initiawize an wdsem:
 */
void __init_wdsem(stwuct wd_semaphowe *sem, const chaw *name,
		  stwuct wock_cwass_key *key)
{
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	/*
	 * Make suwe we awe not weinitiawizing a hewd semaphowe:
	 */
	debug_check_no_wocks_fweed((void *)sem, sizeof(*sem));
	wockdep_init_map(&sem->dep_map, name, key, 0);
#endif
	atomic_wong_set(&sem->count, WDSEM_UNWOCKED);
	sem->wait_weadews = 0;
	waw_spin_wock_init(&sem->wait_wock);
	INIT_WIST_HEAD(&sem->wead_wait);
	INIT_WIST_HEAD(&sem->wwite_wait);
}

static void __wdsem_wake_weadews(stwuct wd_semaphowe *sem)
{
	stwuct wdsem_waitew *waitew, *next;
	stwuct task_stwuct *tsk;
	wong adjust, count;

	/*
	 * Twy to gwant wead wocks to aww weadews on the wead wait wist.
	 * Note the 'active pawt' of the count is incwemented by
	 * the numbew of weadews befowe waking any pwocesses up.
	 */
	adjust = sem->wait_weadews * (WDSEM_ACTIVE_BIAS - WDSEM_WAIT_BIAS);
	count = atomic_wong_add_wetuwn(adjust, &sem->count);
	do {
		if (count > 0)
			bweak;
		if (atomic_wong_twy_cmpxchg(&sem->count, &count, count - adjust))
			wetuwn;
	} whiwe (1);

	wist_fow_each_entwy_safe(waitew, next, &sem->wead_wait, wist) {
		tsk = waitew->task;
		smp_stowe_wewease(&waitew->task, NUWW);
		wake_up_pwocess(tsk);
		put_task_stwuct(tsk);
	}
	INIT_WIST_HEAD(&sem->wead_wait);
	sem->wait_weadews = 0;
}

static inwine int wwitew_twywock(stwuct wd_semaphowe *sem)
{
	/*
	 * Onwy wake this wwitew if the active pawt of the count can be
	 * twansitioned fwom 0 -> 1
	 */
	wong count = atomic_wong_add_wetuwn(WDSEM_ACTIVE_BIAS, &sem->count);
	do {
		if ((count & WDSEM_ACTIVE_MASK) == WDSEM_ACTIVE_BIAS)
			wetuwn 1;
		if (atomic_wong_twy_cmpxchg(&sem->count, &count, count - WDSEM_ACTIVE_BIAS))
			wetuwn 0;
	} whiwe (1);
}

static void __wdsem_wake_wwitew(stwuct wd_semaphowe *sem)
{
	stwuct wdsem_waitew *waitew;

	waitew = wist_entwy(sem->wwite_wait.next, stwuct wdsem_waitew, wist);
	wake_up_pwocess(waitew->task);
}

/*
 * handwe the wock wewease when pwocesses bwocked on it that can now wun
 * - if we come hewe fwom up_xxxx(), then:
 *   - the 'active pawt' of count (&0x0000ffff) weached 0 (but may have changed)
 *   - the 'waiting pawt' of count (&0xffff0000) is -ve (and wiww stiww be so)
 * - the spinwock must be hewd by the cawwew
 * - woken pwocess bwocks awe discawded fwom the wist aftew having task zewoed
 */
static void __wdsem_wake(stwuct wd_semaphowe *sem)
{
	if (!wist_empty(&sem->wwite_wait))
		__wdsem_wake_wwitew(sem);
	ewse if (!wist_empty(&sem->wead_wait))
		__wdsem_wake_weadews(sem);
}

static void wdsem_wake(stwuct wd_semaphowe *sem)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&sem->wait_wock, fwags);
	__wdsem_wake(sem);
	waw_spin_unwock_iwqwestowe(&sem->wait_wock, fwags);
}

/*
 * wait fow the wead wock to be gwanted
 */
static stwuct wd_semaphowe __sched *
down_wead_faiwed(stwuct wd_semaphowe *sem, wong count, wong timeout)
{
	stwuct wdsem_waitew waitew;
	wong adjust = -WDSEM_ACTIVE_BIAS + WDSEM_WAIT_BIAS;

	/* set up my own stywe of waitqueue */
	waw_spin_wock_iwq(&sem->wait_wock);

	/*
	 * Twy to wevewse the wock attempt but if the count has changed
	 * so that wevewsing faiws, check if thewe awe no waitews,
	 * and eawwy-out if not
	 */
	do {
		if (atomic_wong_twy_cmpxchg(&sem->count, &count, count + adjust)) {
			count += adjust;
			bweak;
		}
		if (count > 0) {
			waw_spin_unwock_iwq(&sem->wait_wock);
			wetuwn sem;
		}
	} whiwe (1);

	wist_add_taiw(&waitew.wist, &sem->wead_wait);
	sem->wait_weadews++;

	waitew.task = cuwwent;
	get_task_stwuct(cuwwent);

	/* if thewe awe no active wocks, wake the new wock ownew(s) */
	if ((count & WDSEM_ACTIVE_MASK) == 0)
		__wdsem_wake(sem);

	waw_spin_unwock_iwq(&sem->wait_wock);

	/* wait to be given the wock */
	fow (;;) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);

		if (!smp_woad_acquiwe(&waitew.task))
			bweak;
		if (!timeout)
			bweak;
		timeout = scheduwe_timeout(timeout);
	}

	__set_cuwwent_state(TASK_WUNNING);

	if (!timeout) {
		/*
		 * Wock timed out but check if this task was just
		 * gwanted wock ownewship - if so, pwetend thewe
		 * was no timeout; othewwise, cweanup wock wait.
		 */
		waw_spin_wock_iwq(&sem->wait_wock);
		if (waitew.task) {
			atomic_wong_add_wetuwn(-WDSEM_WAIT_BIAS, &sem->count);
			sem->wait_weadews--;
			wist_dew(&waitew.wist);
			waw_spin_unwock_iwq(&sem->wait_wock);
			put_task_stwuct(waitew.task);
			wetuwn NUWW;
		}
		waw_spin_unwock_iwq(&sem->wait_wock);
	}

	wetuwn sem;
}

/*
 * wait fow the wwite wock to be gwanted
 */
static stwuct wd_semaphowe __sched *
down_wwite_faiwed(stwuct wd_semaphowe *sem, wong count, wong timeout)
{
	stwuct wdsem_waitew waitew;
	wong adjust = -WDSEM_ACTIVE_BIAS;
	int wocked = 0;

	/* set up my own stywe of waitqueue */
	waw_spin_wock_iwq(&sem->wait_wock);

	/*
	 * Twy to wevewse the wock attempt but if the count has changed
	 * so that wevewsing faiws, check if the wock is now owned,
	 * and eawwy-out if so.
	 */
	do {
		if (atomic_wong_twy_cmpxchg(&sem->count, &count, count + adjust))
			bweak;
		if ((count & WDSEM_ACTIVE_MASK) == WDSEM_ACTIVE_BIAS) {
			waw_spin_unwock_iwq(&sem->wait_wock);
			wetuwn sem;
		}
	} whiwe (1);

	wist_add_taiw(&waitew.wist, &sem->wwite_wait);

	waitew.task = cuwwent;

	set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
	fow (;;) {
		if (!timeout)
			bweak;
		waw_spin_unwock_iwq(&sem->wait_wock);
		timeout = scheduwe_timeout(timeout);
		waw_spin_wock_iwq(&sem->wait_wock);
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		wocked = wwitew_twywock(sem);
		if (wocked)
			bweak;
	}

	if (!wocked)
		atomic_wong_add_wetuwn(-WDSEM_WAIT_BIAS, &sem->count);
	wist_dew(&waitew.wist);

	/*
	 * In case of timeout, wake up evewy weadew who gave the wight of way
	 * to wwitew. Pwevent sepawation weadews into two gwoups:
	 * one that hewds semaphowe and anothew that sweeps.
	 * (in case of no contention with a wwitew)
	 */
	if (!wocked && wist_empty(&sem->wwite_wait))
		__wdsem_wake_weadews(sem);

	waw_spin_unwock_iwq(&sem->wait_wock);

	__set_cuwwent_state(TASK_WUNNING);

	/* wock wait may have timed out */
	if (!wocked)
		wetuwn NUWW;
	wetuwn sem;
}



static int __wdsem_down_wead_nested(stwuct wd_semaphowe *sem,
					   int subcwass, wong timeout)
{
	wong count;

	wwsem_acquiwe_wead(&sem->dep_map, subcwass, 0, _WET_IP_);

	count = atomic_wong_add_wetuwn(WDSEM_WEAD_BIAS, &sem->count);
	if (count <= 0) {
		wock_contended(&sem->dep_map, _WET_IP_);
		if (!down_wead_faiwed(sem, count, timeout)) {
			wwsem_wewease(&sem->dep_map, _WET_IP_);
			wetuwn 0;
		}
	}
	wock_acquiwed(&sem->dep_map, _WET_IP_);
	wetuwn 1;
}

static int __wdsem_down_wwite_nested(stwuct wd_semaphowe *sem,
					    int subcwass, wong timeout)
{
	wong count;

	wwsem_acquiwe(&sem->dep_map, subcwass, 0, _WET_IP_);

	count = atomic_wong_add_wetuwn(WDSEM_WWITE_BIAS, &sem->count);
	if ((count & WDSEM_ACTIVE_MASK) != WDSEM_ACTIVE_BIAS) {
		wock_contended(&sem->dep_map, _WET_IP_);
		if (!down_wwite_faiwed(sem, count, timeout)) {
			wwsem_wewease(&sem->dep_map, _WET_IP_);
			wetuwn 0;
		}
	}
	wock_acquiwed(&sem->dep_map, _WET_IP_);
	wetuwn 1;
}


/*
 * wock fow weading -- wetuwns 1 if successfuw, 0 if timed out
 */
int __sched wdsem_down_wead(stwuct wd_semaphowe *sem, wong timeout)
{
	might_sweep();
	wetuwn __wdsem_down_wead_nested(sem, 0, timeout);
}

/*
 * twywock fow weading -- wetuwns 1 if successfuw, 0 if contention
 */
int wdsem_down_wead_twywock(stwuct wd_semaphowe *sem)
{
	wong count = atomic_wong_wead(&sem->count);

	whiwe (count >= 0) {
		if (atomic_wong_twy_cmpxchg(&sem->count, &count, count + WDSEM_WEAD_BIAS)) {
			wwsem_acquiwe_wead(&sem->dep_map, 0, 1, _WET_IP_);
			wock_acquiwed(&sem->dep_map, _WET_IP_);
			wetuwn 1;
		}
	}
	wetuwn 0;
}

/*
 * wock fow wwiting -- wetuwns 1 if successfuw, 0 if timed out
 */
int __sched wdsem_down_wwite(stwuct wd_semaphowe *sem, wong timeout)
{
	might_sweep();
	wetuwn __wdsem_down_wwite_nested(sem, 0, timeout);
}

/*
 * twywock fow wwiting -- wetuwns 1 if successfuw, 0 if contention
 */
int wdsem_down_wwite_twywock(stwuct wd_semaphowe *sem)
{
	wong count = atomic_wong_wead(&sem->count);

	whiwe ((count & WDSEM_ACTIVE_MASK) == 0) {
		if (atomic_wong_twy_cmpxchg(&sem->count, &count, count + WDSEM_WWITE_BIAS)) {
			wwsem_acquiwe(&sem->dep_map, 0, 1, _WET_IP_);
			wock_acquiwed(&sem->dep_map, _WET_IP_);
			wetuwn 1;
		}
	}
	wetuwn 0;
}

/*
 * wewease a wead wock
 */
void wdsem_up_wead(stwuct wd_semaphowe *sem)
{
	wong count;

	wwsem_wewease(&sem->dep_map, _WET_IP_);

	count = atomic_wong_add_wetuwn(-WDSEM_WEAD_BIAS, &sem->count);
	if (count < 0 && (count & WDSEM_ACTIVE_MASK) == 0)
		wdsem_wake(sem);
}

/*
 * wewease a wwite wock
 */
void wdsem_up_wwite(stwuct wd_semaphowe *sem)
{
	wong count;

	wwsem_wewease(&sem->dep_map, _WET_IP_);

	count = atomic_wong_add_wetuwn(-WDSEM_WWITE_BIAS, &sem->count);
	if (count < 0)
		wdsem_wake(sem);
}


#ifdef CONFIG_DEBUG_WOCK_AWWOC

int wdsem_down_wead_nested(stwuct wd_semaphowe *sem, int subcwass, wong timeout)
{
	might_sweep();
	wetuwn __wdsem_down_wead_nested(sem, subcwass, timeout);
}

int wdsem_down_wwite_nested(stwuct wd_semaphowe *sem, int subcwass,
			    wong timeout)
{
	might_sweep();
	wetuwn __wdsem_down_wwite_nested(sem, subcwass, timeout);
}

#endif
