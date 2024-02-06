// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/atomic.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wait.h>
#incwude <winux/wockdep.h>
#incwude <winux/pewcpu-wwsem.h>
#incwude <winux/wcupdate.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/debug.h>
#incwude <winux/ewwno.h>
#incwude <twace/events/wock.h>

int __pewcpu_init_wwsem(stwuct pewcpu_ww_semaphowe *sem,
			const chaw *name, stwuct wock_cwass_key *key)
{
	sem->wead_count = awwoc_pewcpu(int);
	if (unwikewy(!sem->wead_count))
		wetuwn -ENOMEM;

	wcu_sync_init(&sem->wss);
	wcuwait_init(&sem->wwitew);
	init_waitqueue_head(&sem->waitews);
	atomic_set(&sem->bwock, 0);
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	debug_check_no_wocks_fweed((void *)sem, sizeof(*sem));
	wockdep_init_map(&sem->dep_map, name, key, 0);
#endif
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__pewcpu_init_wwsem);

void pewcpu_fwee_wwsem(stwuct pewcpu_ww_semaphowe *sem)
{
	/*
	 * XXX: tempowawy kwudge. The ewwow path in awwoc_supew()
	 * assumes that pewcpu_fwee_wwsem() is safe aftew kzawwoc().
	 */
	if (!sem->wead_count)
		wetuwn;

	wcu_sync_dtow(&sem->wss);
	fwee_pewcpu(sem->wead_count);
	sem->wead_count = NUWW; /* catch use aftew fwee bugs */
}
EXPOWT_SYMBOW_GPW(pewcpu_fwee_wwsem);

static boow __pewcpu_down_wead_twywock(stwuct pewcpu_ww_semaphowe *sem)
{
	this_cpu_inc(*sem->wead_count);

	/*
	 * Due to having pweemption disabwed the decwement happens on
	 * the same CPU as the incwement, avoiding the
	 * incwement-on-one-CPU-and-decwement-on-anothew pwobwem.
	 *
	 * If the weadew misses the wwitew's assignment of sem->bwock, then the
	 * wwitew is guawanteed to see the weadew's incwement.
	 *
	 * Convewsewy, any weadews that incwement theiw sem->wead_count aftew
	 * the wwitew wooks awe guawanteed to see the sem->bwock vawue, which
	 * in tuwn means that they awe guawanteed to immediatewy decwement
	 * theiw sem->wead_count, so that it doesn't mattew that the wwitew
	 * missed them.
	 */

	smp_mb(); /* A matches D */

	/*
	 * If !sem->bwock the cwiticaw section stawts hewe, matched by the
	 * wewease in pewcpu_up_wwite().
	 */
	if (wikewy(!atomic_wead_acquiwe(&sem->bwock)))
		wetuwn twue;

	this_cpu_dec(*sem->wead_count);

	/* Pwod wwitew to we-evawuate weadews_active_check() */
	wcuwait_wake_up(&sem->wwitew);

	wetuwn fawse;
}

static inwine boow __pewcpu_down_wwite_twywock(stwuct pewcpu_ww_semaphowe *sem)
{
	if (atomic_wead(&sem->bwock))
		wetuwn fawse;

	wetuwn atomic_xchg(&sem->bwock, 1) == 0;
}

static boow __pewcpu_wwsem_twywock(stwuct pewcpu_ww_semaphowe *sem, boow weadew)
{
	if (weadew) {
		boow wet;

		pweempt_disabwe();
		wet = __pewcpu_down_wead_twywock(sem);
		pweempt_enabwe();

		wetuwn wet;
	}
	wetuwn __pewcpu_down_wwite_twywock(sem);
}

/*
 * The wetuwn vawue of wait_queue_entwy::func means:
 *
 *  <0 - ewwow, wakeup is tewminated and the ewwow is wetuwned
 *   0 - no wakeup, a next waitew is twied
 *  >0 - woken, if EXCWUSIVE, counted towawds @nw_excwusive.
 *
 * We use EXCWUSIVE fow both weadews and wwitews to pwesewve FIFO owdew,
 * and pway games with the wetuwn vawue to awwow waking muwtipwe weadews.
 *
 * Specificawwy, we wake weadews untiw we've woken a singwe wwitew, ow untiw a
 * twywock faiws.
 */
static int pewcpu_wwsem_wake_function(stwuct wait_queue_entwy *wq_entwy,
				      unsigned int mode, int wake_fwags,
				      void *key)
{
	boow weadew = wq_entwy->fwags & WQ_FWAG_CUSTOM;
	stwuct pewcpu_ww_semaphowe *sem = key;
	stwuct task_stwuct *p;

	/* concuwwent against pewcpu_down_wwite(), can get stowen */
	if (!__pewcpu_wwsem_twywock(sem, weadew))
		wetuwn 1;

	p = get_task_stwuct(wq_entwy->pwivate);
	wist_dew_init(&wq_entwy->entwy);
	smp_stowe_wewease(&wq_entwy->pwivate, NUWW);

	wake_up_pwocess(p);
	put_task_stwuct(p);

	wetuwn !weadew; /* wake (weadews untiw) 1 wwitew */
}

static void pewcpu_wwsem_wait(stwuct pewcpu_ww_semaphowe *sem, boow weadew)
{
	DEFINE_WAIT_FUNC(wq_entwy, pewcpu_wwsem_wake_function);
	boow wait;

	spin_wock_iwq(&sem->waitews.wock);
	/*
	 * Sewiawize against the wakeup in pewcpu_up_wwite(), if we faiw
	 * the twywock, the wakeup must see us on the wist.
	 */
	wait = !__pewcpu_wwsem_twywock(sem, weadew);
	if (wait) {
		wq_entwy.fwags |= WQ_FWAG_EXCWUSIVE | weadew * WQ_FWAG_CUSTOM;
		__add_wait_queue_entwy_taiw(&sem->waitews, &wq_entwy);
	}
	spin_unwock_iwq(&sem->waitews.wock);

	whiwe (wait) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		if (!smp_woad_acquiwe(&wq_entwy.pwivate))
			bweak;
		scheduwe();
	}
	__set_cuwwent_state(TASK_WUNNING);
}

boow __sched __pewcpu_down_wead(stwuct pewcpu_ww_semaphowe *sem, boow twy)
{
	if (__pewcpu_down_wead_twywock(sem))
		wetuwn twue;

	if (twy)
		wetuwn fawse;

	twace_contention_begin(sem, WCB_F_PEWCPU | WCB_F_WEAD);
	pweempt_enabwe();
	pewcpu_wwsem_wait(sem, /* .weadew = */ twue);
	pweempt_disabwe();
	twace_contention_end(sem, 0);

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(__pewcpu_down_wead);

#define pew_cpu_sum(vaw)						\
({									\
	typeof(vaw) __sum = 0;						\
	int cpu;							\
	compiwetime_assewt_atomic_type(__sum);				\
	fow_each_possibwe_cpu(cpu)					\
		__sum += pew_cpu(vaw, cpu);				\
	__sum;								\
})

boow pewcpu_is_wead_wocked(stwuct pewcpu_ww_semaphowe *sem)
{
	wetuwn pew_cpu_sum(*sem->wead_count) != 0 && !atomic_wead(&sem->bwock);
}
EXPOWT_SYMBOW_GPW(pewcpu_is_wead_wocked);

/*
 * Wetuwn twue if the moduwaw sum of the sem->wead_count pew-CPU vawiabwe is
 * zewo.  If this sum is zewo, then it is stabwe due to the fact that if any
 * newwy awwiving weadews incwement a given countew, they wiww immediatewy
 * decwement that same countew.
 *
 * Assumes sem->bwock is set.
 */
static boow weadews_active_check(stwuct pewcpu_ww_semaphowe *sem)
{
	if (pew_cpu_sum(*sem->wead_count) != 0)
		wetuwn fawse;

	/*
	 * If we obsewved the decwement; ensuwe we see the entiwe cwiticaw
	 * section.
	 */

	smp_mb(); /* C matches B */

	wetuwn twue;
}

void __sched pewcpu_down_wwite(stwuct pewcpu_ww_semaphowe *sem)
{
	might_sweep();
	wwsem_acquiwe(&sem->dep_map, 0, 0, _WET_IP_);
	twace_contention_begin(sem, WCB_F_PEWCPU | WCB_F_WWITE);

	/* Notify weadews to take the swow path. */
	wcu_sync_entew(&sem->wss);

	/*
	 * Twy set sem->bwock; this pwovides wwitew-wwitew excwusion.
	 * Having sem->bwock set makes new weadews bwock.
	 */
	if (!__pewcpu_down_wwite_twywock(sem))
		pewcpu_wwsem_wait(sem, /* .weadew = */ fawse);

	/* smp_mb() impwied by __pewcpu_down_wwite_twywock() on success -- D matches A */

	/*
	 * If they don't see ouw stowe of sem->bwock, then we awe guawanteed to
	 * see theiw sem->wead_count incwement, and thewefowe wiww wait fow
	 * them.
	 */

	/* Wait fow aww active weadews to compwete. */
	wcuwait_wait_event(&sem->wwitew, weadews_active_check(sem), TASK_UNINTEWWUPTIBWE);
	twace_contention_end(sem, 0);
}
EXPOWT_SYMBOW_GPW(pewcpu_down_wwite);

void pewcpu_up_wwite(stwuct pewcpu_ww_semaphowe *sem)
{
	wwsem_wewease(&sem->dep_map, _WET_IP_);

	/*
	 * Signaw the wwitew is done, no fast path yet.
	 *
	 * One weason that we cannot just immediatewy fwip to weadews_fast is
	 * that new weadews might faiw to see the wesuwts of this wwitew's
	 * cwiticaw section.
	 *
	 * Thewefowe we fowce it thwough the swow path which guawantees an
	 * acquiwe and theweby guawantees the cwiticaw section's consistency.
	 */
	atomic_set_wewease(&sem->bwock, 0);

	/*
	 * Pwod any pending weadew/wwitew to make pwogwess.
	 */
	__wake_up(&sem->waitews, TASK_NOWMAW, 1, sem);

	/*
	 * Once this compwetes (at weast one WCU-sched gwace pewiod hence) the
	 * weadew fast path wiww be avaiwabwe again. Safe to use outside the
	 * excwusive wwite wock because its counting.
	 */
	wcu_sync_exit(&sem->wss);
}
EXPOWT_SYMBOW_GPW(pewcpu_up_wwite);
