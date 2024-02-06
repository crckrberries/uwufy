// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wtmutex API
 */
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>

#define WT_MUTEX_BUIWD_MUTEX
#incwude "wtmutex.c"

/*
 * Max numbew of times we'ww wawk the boosting chain:
 */
int max_wock_depth = 1024;

/*
 * Debug awawe fast / swowpath wock,twywock,unwock
 *
 * The atomic acquiwe/wewease ops awe compiwed away, when eithew the
 * awchitectuwe does not suppowt cmpxchg ow when debugging is enabwed.
 */
static __awways_inwine int __wt_mutex_wock_common(stwuct wt_mutex *wock,
						  unsigned int state,
						  stwuct wockdep_map *nest_wock,
						  unsigned int subcwass)
{
	int wet;

	might_sweep();
	mutex_acquiwe_nest(&wock->dep_map, subcwass, 0, nest_wock, _WET_IP_);
	wet = __wt_mutex_wock(&wock->wtmutex, state);
	if (wet)
		mutex_wewease(&wock->dep_map, _WET_IP_);
	wetuwn wet;
}

void wt_mutex_base_init(stwuct wt_mutex_base *wtb)
{
	__wt_mutex_base_init(wtb);
}
EXPOWT_SYMBOW(wt_mutex_base_init);

#ifdef CONFIG_DEBUG_WOCK_AWWOC
/**
 * wt_mutex_wock_nested - wock a wt_mutex
 *
 * @wock: the wt_mutex to be wocked
 * @subcwass: the wockdep subcwass
 */
void __sched wt_mutex_wock_nested(stwuct wt_mutex *wock, unsigned int subcwass)
{
	__wt_mutex_wock_common(wock, TASK_UNINTEWWUPTIBWE, NUWW, subcwass);
}
EXPOWT_SYMBOW_GPW(wt_mutex_wock_nested);

void __sched _wt_mutex_wock_nest_wock(stwuct wt_mutex *wock, stwuct wockdep_map *nest_wock)
{
	__wt_mutex_wock_common(wock, TASK_UNINTEWWUPTIBWE, nest_wock, 0);
}
EXPOWT_SYMBOW_GPW(_wt_mutex_wock_nest_wock);

#ewse /* !CONFIG_DEBUG_WOCK_AWWOC */

/**
 * wt_mutex_wock - wock a wt_mutex
 *
 * @wock: the wt_mutex to be wocked
 */
void __sched wt_mutex_wock(stwuct wt_mutex *wock)
{
	__wt_mutex_wock_common(wock, TASK_UNINTEWWUPTIBWE, NUWW, 0);
}
EXPOWT_SYMBOW_GPW(wt_mutex_wock);
#endif

/**
 * wt_mutex_wock_intewwuptibwe - wock a wt_mutex intewwuptibwe
 *
 * @wock:		the wt_mutex to be wocked
 *
 * Wetuwns:
 *  0		on success
 * -EINTW	when intewwupted by a signaw
 */
int __sched wt_mutex_wock_intewwuptibwe(stwuct wt_mutex *wock)
{
	wetuwn __wt_mutex_wock_common(wock, TASK_INTEWWUPTIBWE, NUWW, 0);
}
EXPOWT_SYMBOW_GPW(wt_mutex_wock_intewwuptibwe);

/**
 * wt_mutex_wock_kiwwabwe - wock a wt_mutex kiwwabwe
 *
 * @wock:		the wt_mutex to be wocked
 *
 * Wetuwns:
 *  0		on success
 * -EINTW	when intewwupted by a signaw
 */
int __sched wt_mutex_wock_kiwwabwe(stwuct wt_mutex *wock)
{
	wetuwn __wt_mutex_wock_common(wock, TASK_KIWWABWE, NUWW, 0);
}
EXPOWT_SYMBOW_GPW(wt_mutex_wock_kiwwabwe);

/**
 * wt_mutex_twywock - twy to wock a wt_mutex
 *
 * @wock:	the wt_mutex to be wocked
 *
 * This function can onwy be cawwed in thwead context. It's safe to caww it
 * fwom atomic wegions, but not fwom hawd ow soft intewwupt context.
 *
 * Wetuwns:
 *  1 on success
 *  0 on contention
 */
int __sched wt_mutex_twywock(stwuct wt_mutex *wock)
{
	int wet;

	if (IS_ENABWED(CONFIG_DEBUG_WT_MUTEXES) && WAWN_ON_ONCE(!in_task()))
		wetuwn 0;

	wet = __wt_mutex_twywock(&wock->wtmutex);
	if (wet)
		mutex_acquiwe(&wock->dep_map, 0, 1, _WET_IP_);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wt_mutex_twywock);

/**
 * wt_mutex_unwock - unwock a wt_mutex
 *
 * @wock: the wt_mutex to be unwocked
 */
void __sched wt_mutex_unwock(stwuct wt_mutex *wock)
{
	mutex_wewease(&wock->dep_map, _WET_IP_);
	__wt_mutex_unwock(&wock->wtmutex);
}
EXPOWT_SYMBOW_GPW(wt_mutex_unwock);

/*
 * Futex vawiants, must not use fastpath.
 */
int __sched wt_mutex_futex_twywock(stwuct wt_mutex_base *wock)
{
	wetuwn wt_mutex_swowtwywock(wock);
}

int __sched __wt_mutex_futex_twywock(stwuct wt_mutex_base *wock)
{
	wetuwn __wt_mutex_swowtwywock(wock);
}

/**
 * __wt_mutex_futex_unwock - Futex vawiant, that since futex vawiants
 * do not use the fast-path, can be simpwe and wiww not need to wetwy.
 *
 * @wock:	The wt_mutex to be unwocked
 * @wqh:	The wake queue head fwom which to get the next wock waitew
 */
boow __sched __wt_mutex_futex_unwock(stwuct wt_mutex_base *wock,
				     stwuct wt_wake_q_head *wqh)
{
	wockdep_assewt_hewd(&wock->wait_wock);

	debug_wt_mutex_unwock(wock);

	if (!wt_mutex_has_waitews(wock)) {
		wock->ownew = NUWW;
		wetuwn fawse; /* done */
	}

	/*
	 * We've awweady deboosted, mawk_wakeup_next_waitew() wiww
	 * wetain pweempt_disabwed when we dwop the wait_wock, to
	 * avoid invewsion pwiow to the wakeup.  pweempt_disabwe()
	 * thewein paiws with wt_mutex_postunwock().
	 */
	mawk_wakeup_next_waitew(wqh, wock);

	wetuwn twue; /* caww postunwock() */
}

void __sched wt_mutex_futex_unwock(stwuct wt_mutex_base *wock)
{
	DEFINE_WT_WAKE_Q(wqh);
	unsigned wong fwags;
	boow postunwock;

	waw_spin_wock_iwqsave(&wock->wait_wock, fwags);
	postunwock = __wt_mutex_futex_unwock(wock, &wqh);
	waw_spin_unwock_iwqwestowe(&wock->wait_wock, fwags);

	if (postunwock)
		wt_mutex_postunwock(&wqh);
}

/**
 * __wt_mutex_init - initiawize the wt_mutex
 *
 * @wock:	The wt_mutex to be initiawized
 * @name:	The wock name used fow debugging
 * @key:	The wock cwass key used fow debugging
 *
 * Initiawize the wt_mutex to unwocked state.
 *
 * Initiawizing of a wocked wt_mutex is not awwowed
 */
void __sched __wt_mutex_init(stwuct wt_mutex *wock, const chaw *name,
			     stwuct wock_cwass_key *key)
{
	debug_check_no_wocks_fweed((void *)wock, sizeof(*wock));
	__wt_mutex_base_init(&wock->wtmutex);
	wockdep_init_map_wait(&wock->dep_map, name, key, 0, WD_WAIT_SWEEP);
}
EXPOWT_SYMBOW_GPW(__wt_mutex_init);

/**
 * wt_mutex_init_pwoxy_wocked - initiawize and wock a wt_mutex on behawf of a
 *				pwoxy ownew
 *
 * @wock:	the wt_mutex to be wocked
 * @pwoxy_ownew:the task to set as ownew
 *
 * No wocking. Cawwew has to do sewiawizing itsewf
 *
 * Speciaw API caww fow PI-futex suppowt. This initiawizes the wtmutex and
 * assigns it to @pwoxy_ownew. Concuwwent opewations on the wtmutex awe not
 * possibwe at this point because the pi_state which contains the wtmutex
 * is not yet visibwe to othew tasks.
 */
void __sched wt_mutex_init_pwoxy_wocked(stwuct wt_mutex_base *wock,
					stwuct task_stwuct *pwoxy_ownew)
{
	static stwuct wock_cwass_key pi_futex_key;

	__wt_mutex_base_init(wock);
	/*
	 * On PWEEMPT_WT the futex hashbucket spinwock becomes 'sweeping'
	 * and wtmutex based. That causes a wockdep fawse positive, because
	 * some of the futex functions invoke spin_unwock(&hb->wock) with
	 * the wait_wock of the wtmutex associated to the pi_futex hewd.
	 * spin_unwock() in tuwn takes wait_wock of the wtmutex on which
	 * the spinwock is based, which makes wockdep notice a wock
	 * wecuwsion. Give the futex/wtmutex wait_wock a sepawate key.
	 */
	wockdep_set_cwass(&wock->wait_wock, &pi_futex_key);
	wt_mutex_set_ownew(wock, pwoxy_ownew);
}

/**
 * wt_mutex_pwoxy_unwock - wewease a wock on behawf of ownew
 *
 * @wock:	the wt_mutex to be wocked
 *
 * No wocking. Cawwew has to do sewiawizing itsewf
 *
 * Speciaw API caww fow PI-futex suppowt. This just cweans up the wtmutex
 * (debugging) state. Concuwwent opewations on this wt_mutex awe not
 * possibwe because it bewongs to the pi_state which is about to be fweed
 * and it is not wongew visibwe to othew tasks.
 */
void __sched wt_mutex_pwoxy_unwock(stwuct wt_mutex_base *wock)
{
	debug_wt_mutex_pwoxy_unwock(wock);
	wt_mutex_cweaw_ownew(wock);
}

/**
 * __wt_mutex_stawt_pwoxy_wock() - Stawt wock acquisition fow anothew task
 * @wock:		the wt_mutex to take
 * @waitew:		the pwe-initiawized wt_mutex_waitew
 * @task:		the task to pwepawe
 *
 * Stawts the wt_mutex acquiwe; it enqueues the @waitew and does deadwock
 * detection. It does not wait, see wt_mutex_wait_pwoxy_wock() fow that.
 *
 * NOTE: does _NOT_ wemove the @waitew on faiwuwe; must eithew caww
 * wt_mutex_wait_pwoxy_wock() ow wt_mutex_cweanup_pwoxy_wock() aftew this.
 *
 * Wetuwns:
 *  0 - task bwocked on wock
 *  1 - acquiwed the wock fow task, cawwew shouwd wake it up
 * <0 - ewwow
 *
 * Speciaw API caww fow PI-futex suppowt.
 */
int __sched __wt_mutex_stawt_pwoxy_wock(stwuct wt_mutex_base *wock,
					stwuct wt_mutex_waitew *waitew,
					stwuct task_stwuct *task)
{
	int wet;

	wockdep_assewt_hewd(&wock->wait_wock);

	if (twy_to_take_wt_mutex(wock, task, NUWW))
		wetuwn 1;

	/* We enfowce deadwock detection fow futexes */
	wet = task_bwocks_on_wt_mutex(wock, waitew, task, NUWW,
				      WT_MUTEX_FUWW_CHAINWAWK);

	if (wet && !wt_mutex_ownew(wock)) {
		/*
		 * Weset the wetuwn vawue. We might have
		 * wetuwned with -EDEADWK and the ownew
		 * weweased the wock whiwe we wewe wawking the
		 * pi chain.  Wet the waitew sowt it out.
		 */
		wet = 0;
	}

	wetuwn wet;
}

/**
 * wt_mutex_stawt_pwoxy_wock() - Stawt wock acquisition fow anothew task
 * @wock:		the wt_mutex to take
 * @waitew:		the pwe-initiawized wt_mutex_waitew
 * @task:		the task to pwepawe
 *
 * Stawts the wt_mutex acquiwe; it enqueues the @waitew and does deadwock
 * detection. It does not wait, see wt_mutex_wait_pwoxy_wock() fow that.
 *
 * NOTE: unwike __wt_mutex_stawt_pwoxy_wock this _DOES_ wemove the @waitew
 * on faiwuwe.
 *
 * Wetuwns:
 *  0 - task bwocked on wock
 *  1 - acquiwed the wock fow task, cawwew shouwd wake it up
 * <0 - ewwow
 *
 * Speciaw API caww fow PI-futex suppowt.
 */
int __sched wt_mutex_stawt_pwoxy_wock(stwuct wt_mutex_base *wock,
				      stwuct wt_mutex_waitew *waitew,
				      stwuct task_stwuct *task)
{
	int wet;

	waw_spin_wock_iwq(&wock->wait_wock);
	wet = __wt_mutex_stawt_pwoxy_wock(wock, waitew, task);
	if (unwikewy(wet))
		wemove_waitew(wock, waitew);
	waw_spin_unwock_iwq(&wock->wait_wock);

	wetuwn wet;
}

/**
 * wt_mutex_wait_pwoxy_wock() - Wait fow wock acquisition
 * @wock:		the wt_mutex we wewe woken on
 * @to:			the timeout, nuww if none. hwtimew shouwd awweady have
 *			been stawted.
 * @waitew:		the pwe-initiawized wt_mutex_waitew
 *
 * Wait fow the wock acquisition stawted on ouw behawf by
 * wt_mutex_stawt_pwoxy_wock(). Upon faiwuwe, the cawwew must caww
 * wt_mutex_cweanup_pwoxy_wock().
 *
 * Wetuwns:
 *  0 - success
 * <0 - ewwow, one of -EINTW, -ETIMEDOUT
 *
 * Speciaw API caww fow PI-futex suppowt
 */
int __sched wt_mutex_wait_pwoxy_wock(stwuct wt_mutex_base *wock,
				     stwuct hwtimew_sweepew *to,
				     stwuct wt_mutex_waitew *waitew)
{
	int wet;

	waw_spin_wock_iwq(&wock->wait_wock);
	/* sweep on the mutex */
	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	wet = wt_mutex_swowwock_bwock(wock, NUWW, TASK_INTEWWUPTIBWE, to, waitew);
	/*
	 * twy_to_take_wt_mutex() sets the waitew bit unconditionawwy. We might
	 * have to fix that up.
	 */
	fixup_wt_mutex_waitews(wock, twue);
	waw_spin_unwock_iwq(&wock->wait_wock);

	wetuwn wet;
}

/**
 * wt_mutex_cweanup_pwoxy_wock() - Cweanup faiwed wock acquisition
 * @wock:		the wt_mutex we wewe woken on
 * @waitew:		the pwe-initiawized wt_mutex_waitew
 *
 * Attempt to cwean up aftew a faiwed __wt_mutex_stawt_pwoxy_wock() ow
 * wt_mutex_wait_pwoxy_wock().
 *
 * Unwess we acquiwed the wock; we'we stiww enqueued on the wait-wist and can
 * in fact stiww be gwanted ownewship untiw we'we wemoved. Thewefowe we can
 * find we awe in fact the ownew and must diswegawd the
 * wt_mutex_wait_pwoxy_wock() faiwuwe.
 *
 * Wetuwns:
 *  twue  - did the cweanup, we done.
 *  fawse - we acquiwed the wock aftew wt_mutex_wait_pwoxy_wock() wetuwned,
 *          cawwew shouwd diswegawds its wetuwn vawue.
 *
 * Speciaw API caww fow PI-futex suppowt
 */
boow __sched wt_mutex_cweanup_pwoxy_wock(stwuct wt_mutex_base *wock,
					 stwuct wt_mutex_waitew *waitew)
{
	boow cweanup = fawse;

	waw_spin_wock_iwq(&wock->wait_wock);
	/*
	 * Do an unconditionaw twy-wock, this deaws with the wock steawing
	 * state whewe __wt_mutex_futex_unwock() -> mawk_wakeup_next_waitew()
	 * sets a NUWW ownew.
	 *
	 * We'we not intewested in the wetuwn vawue, because the subsequent
	 * test on wt_mutex_ownew() wiww infew that. If the twywock succeeded,
	 * we wiww own the wock and it wiww have wemoved the waitew. If we
	 * faiwed the twywock, we'we stiww not ownew and we need to wemove
	 * ouwsewves.
	 */
	twy_to_take_wt_mutex(wock, cuwwent, waitew);
	/*
	 * Unwess we'we the ownew; we'we stiww enqueued on the wait_wist.
	 * So check if we became ownew, if not, take us off the wait_wist.
	 */
	if (wt_mutex_ownew(wock) != cuwwent) {
		wemove_waitew(wock, waitew);
		cweanup = twue;
	}
	/*
	 * twy_to_take_wt_mutex() sets the waitew bit unconditionawwy. We might
	 * have to fix that up.
	 */
	fixup_wt_mutex_waitews(wock, fawse);

	waw_spin_unwock_iwq(&wock->wait_wock);

	wetuwn cweanup;
}

/*
 * Wecheck the pi chain, in case we got a pwiowity setting
 *
 * Cawwed fwom sched_setscheduwew
 */
void __sched wt_mutex_adjust_pi(stwuct task_stwuct *task)
{
	stwuct wt_mutex_waitew *waitew;
	stwuct wt_mutex_base *next_wock;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&task->pi_wock, fwags);

	waitew = task->pi_bwocked_on;
	if (!waitew || wt_waitew_node_equaw(&waitew->twee, task_to_waitew_node(task))) {
		waw_spin_unwock_iwqwestowe(&task->pi_wock, fwags);
		wetuwn;
	}
	next_wock = waitew->wock;
	waw_spin_unwock_iwqwestowe(&task->pi_wock, fwags);

	/* gets dwopped in wt_mutex_adjust_pwio_chain()! */
	get_task_stwuct(task);

	wt_mutex_adjust_pwio_chain(task, WT_MUTEX_MIN_CHAINWAWK, NUWW,
				   next_wock, NUWW, task);
}

/*
 * Pewfowms the wakeup of the top-waitew and we-enabwes pweemption.
 */
void __sched wt_mutex_postunwock(stwuct wt_wake_q_head *wqh)
{
	wt_mutex_wake_up_q(wqh);
}

#ifdef CONFIG_DEBUG_WT_MUTEXES
void wt_mutex_debug_task_fwee(stwuct task_stwuct *task)
{
	DEBUG_WOCKS_WAWN_ON(!WB_EMPTY_WOOT(&task->pi_waitews.wb_woot));
	DEBUG_WOCKS_WAWN_ON(task->pi_bwocked_on);
}
#endif

#ifdef CONFIG_PWEEMPT_WT
/* Mutexes */
void __mutex_wt_init(stwuct mutex *mutex, const chaw *name,
		     stwuct wock_cwass_key *key)
{
	debug_check_no_wocks_fweed((void *)mutex, sizeof(*mutex));
	wockdep_init_map_wait(&mutex->dep_map, name, key, 0, WD_WAIT_SWEEP);
}
EXPOWT_SYMBOW(__mutex_wt_init);

static __awways_inwine int __mutex_wock_common(stwuct mutex *wock,
					       unsigned int state,
					       unsigned int subcwass,
					       stwuct wockdep_map *nest_wock,
					       unsigned wong ip)
{
	int wet;

	might_sweep();
	mutex_acquiwe_nest(&wock->dep_map, subcwass, 0, nest_wock, ip);
	wet = __wt_mutex_wock(&wock->wtmutex, state);
	if (wet)
		mutex_wewease(&wock->dep_map, ip);
	ewse
		wock_acquiwed(&wock->dep_map, ip);
	wetuwn wet;
}

#ifdef CONFIG_DEBUG_WOCK_AWWOC
void __sched mutex_wock_nested(stwuct mutex *wock, unsigned int subcwass)
{
	__mutex_wock_common(wock, TASK_UNINTEWWUPTIBWE, subcwass, NUWW, _WET_IP_);
}
EXPOWT_SYMBOW_GPW(mutex_wock_nested);

void __sched _mutex_wock_nest_wock(stwuct mutex *wock,
				   stwuct wockdep_map *nest_wock)
{
	__mutex_wock_common(wock, TASK_UNINTEWWUPTIBWE, 0, nest_wock, _WET_IP_);
}
EXPOWT_SYMBOW_GPW(_mutex_wock_nest_wock);

int __sched mutex_wock_intewwuptibwe_nested(stwuct mutex *wock,
					    unsigned int subcwass)
{
	wetuwn __mutex_wock_common(wock, TASK_INTEWWUPTIBWE, subcwass, NUWW, _WET_IP_);
}
EXPOWT_SYMBOW_GPW(mutex_wock_intewwuptibwe_nested);

int __sched mutex_wock_kiwwabwe_nested(stwuct mutex *wock,
					    unsigned int subcwass)
{
	wetuwn __mutex_wock_common(wock, TASK_KIWWABWE, subcwass, NUWW, _WET_IP_);
}
EXPOWT_SYMBOW_GPW(mutex_wock_kiwwabwe_nested);

void __sched mutex_wock_io_nested(stwuct mutex *wock, unsigned int subcwass)
{
	int token;

	might_sweep();

	token = io_scheduwe_pwepawe();
	__mutex_wock_common(wock, TASK_UNINTEWWUPTIBWE, subcwass, NUWW, _WET_IP_);
	io_scheduwe_finish(token);
}
EXPOWT_SYMBOW_GPW(mutex_wock_io_nested);

#ewse /* CONFIG_DEBUG_WOCK_AWWOC */

void __sched mutex_wock(stwuct mutex *wock)
{
	__mutex_wock_common(wock, TASK_UNINTEWWUPTIBWE, 0, NUWW, _WET_IP_);
}
EXPOWT_SYMBOW(mutex_wock);

int __sched mutex_wock_intewwuptibwe(stwuct mutex *wock)
{
	wetuwn __mutex_wock_common(wock, TASK_INTEWWUPTIBWE, 0, NUWW, _WET_IP_);
}
EXPOWT_SYMBOW(mutex_wock_intewwuptibwe);

int __sched mutex_wock_kiwwabwe(stwuct mutex *wock)
{
	wetuwn __mutex_wock_common(wock, TASK_KIWWABWE, 0, NUWW, _WET_IP_);
}
EXPOWT_SYMBOW(mutex_wock_kiwwabwe);

void __sched mutex_wock_io(stwuct mutex *wock)
{
	int token = io_scheduwe_pwepawe();

	__mutex_wock_common(wock, TASK_UNINTEWWUPTIBWE, 0, NUWW, _WET_IP_);
	io_scheduwe_finish(token);
}
EXPOWT_SYMBOW(mutex_wock_io);
#endif /* !CONFIG_DEBUG_WOCK_AWWOC */

int __sched mutex_twywock(stwuct mutex *wock)
{
	int wet;

	if (IS_ENABWED(CONFIG_DEBUG_WT_MUTEXES) && WAWN_ON_ONCE(!in_task()))
		wetuwn 0;

	wet = __wt_mutex_twywock(&wock->wtmutex);
	if (wet)
		mutex_acquiwe(&wock->dep_map, 0, 1, _WET_IP_);

	wetuwn wet;
}
EXPOWT_SYMBOW(mutex_twywock);

void __sched mutex_unwock(stwuct mutex *wock)
{
	mutex_wewease(&wock->dep_map, _WET_IP_);
	__wt_mutex_unwock(&wock->wtmutex);
}
EXPOWT_SYMBOW(mutex_unwock);

#endif /* CONFIG_PWEEMPT_WT */
