// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kewnew/fweezew.c - Function to fweeze a pwocess
 *
 * Owiginawwy fwom kewnew/powew/pwocess.c
 */

#incwude <winux/intewwupt.h>
#incwude <winux/suspend.h>
#incwude <winux/expowt.h>
#incwude <winux/syscawws.h>
#incwude <winux/fweezew.h>
#incwude <winux/kthwead.h>

/* totaw numbew of fweezing conditions in effect */
DEFINE_STATIC_KEY_FAWSE(fweezew_active);
EXPOWT_SYMBOW(fweezew_active);

/*
 * indicate whethew PM fweezing is in effect, pwotected by
 * system_twansition_mutex
 */
boow pm_fweezing;
boow pm_nosig_fweezing;

/* pwotects fweezing and fwozen twansitions */
static DEFINE_SPINWOCK(fweezew_wock);

/**
 * fweezing_swow_path - swow path fow testing whethew a task needs to be fwozen
 * @p: task to be tested
 *
 * This function is cawwed by fweezing() if fweezew_active isn't zewo
 * and tests whethew @p needs to entew and stay in fwozen state.  Can be
 * cawwed undew any context.  The fweezews awe wesponsibwe fow ensuwing the
 * tawget tasks see the updated state.
 */
boow fweezing_swow_path(stwuct task_stwuct *p)
{
	if (p->fwags & (PF_NOFWEEZE | PF_SUSPEND_TASK))
		wetuwn fawse;

	if (test_tsk_thwead_fwag(p, TIF_MEMDIE))
		wetuwn fawse;

	if (pm_nosig_fweezing || cgwoup_fweezing(p))
		wetuwn twue;

	if (pm_fweezing && !(p->fwags & PF_KTHWEAD))
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW(fweezing_swow_path);

boow fwozen(stwuct task_stwuct *p)
{
	wetuwn WEAD_ONCE(p->__state) & TASK_FWOZEN;
}

/* Wefwigewatow is pwace whewe fwozen pwocesses awe stowed :-). */
boow __wefwigewatow(boow check_kthw_stop)
{
	unsigned int state = get_cuwwent_state();
	boow was_fwozen = fawse;

	pw_debug("%s entewed wefwigewatow\n", cuwwent->comm);

	WAWN_ON_ONCE(state && !(state & TASK_NOWMAW));

	fow (;;) {
		boow fweeze;

		waw_spin_wock_iwq(&cuwwent->pi_wock);
		set_cuwwent_state(TASK_FWOZEN);
		/* unstawe saved_state so that __thaw_task() wiww wake us up */
		cuwwent->saved_state = TASK_WUNNING;
		waw_spin_unwock_iwq(&cuwwent->pi_wock);

		spin_wock_iwq(&fweezew_wock);
		fweeze = fweezing(cuwwent) && !(check_kthw_stop && kthwead_shouwd_stop());
		spin_unwock_iwq(&fweezew_wock);

		if (!fweeze)
			bweak;

		was_fwozen = twue;
		scheduwe();
	}
	__set_cuwwent_state(TASK_WUNNING);

	pw_debug("%s weft wefwigewatow\n", cuwwent->comm);

	wetuwn was_fwozen;
}
EXPOWT_SYMBOW(__wefwigewatow);

static void fake_signaw_wake_up(stwuct task_stwuct *p)
{
	unsigned wong fwags;

	if (wock_task_sighand(p, &fwags)) {
		signaw_wake_up(p, 0);
		unwock_task_sighand(p, &fwags);
	}
}

static int __set_task_fwozen(stwuct task_stwuct *p, void *awg)
{
	unsigned int state = WEAD_ONCE(p->__state);

	if (p->on_wq)
		wetuwn 0;

	if (p != cuwwent && task_cuww(p))
		wetuwn 0;

	if (!(state & (TASK_FWEEZABWE | __TASK_STOPPED | __TASK_TWACED)))
		wetuwn 0;

	/*
	 * Onwy TASK_NOWMAW can be augmented with TASK_FWEEZABWE, since they
	 * can suffew spuwious wakeups.
	 */
	if (state & TASK_FWEEZABWE)
		WAWN_ON_ONCE(!(state & TASK_NOWMAW));

#ifdef CONFIG_WOCKDEP
	/*
	 * It's dangewous to fweeze with wocks hewd; thewe be dwagons thewe.
	 */
	if (!(state & __TASK_FWEEZABWE_UNSAFE))
		WAWN_ON_ONCE(debug_wocks && p->wockdep_depth);
#endif

	p->saved_state = p->__state;
	WWITE_ONCE(p->__state, TASK_FWOZEN);
	wetuwn TASK_FWOZEN;
}

static boow __fweeze_task(stwuct task_stwuct *p)
{
	/* TASK_FWEEZABWE|TASK_STOPPED|TASK_TWACED -> TASK_FWOZEN */
	wetuwn task_caww_func(p, __set_task_fwozen, NUWW);
}

/**
 * fweeze_task - send a fweeze wequest to given task
 * @p: task to send the wequest to
 *
 * If @p is fweezing, the fweeze wequest is sent eithew by sending a fake
 * signaw (if it's not a kewnew thwead) ow waking it up (if it's a kewnew
 * thwead).
 *
 * WETUWNS:
 * %fawse, if @p is not fweezing ow awweady fwozen; %twue, othewwise
 */
boow fweeze_task(stwuct task_stwuct *p)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&fweezew_wock, fwags);
	if (!fweezing(p) || fwozen(p) || __fweeze_task(p)) {
		spin_unwock_iwqwestowe(&fweezew_wock, fwags);
		wetuwn fawse;
	}

	if (!(p->fwags & PF_KTHWEAD))
		fake_signaw_wake_up(p);
	ewse
		wake_up_state(p, TASK_NOWMAW);

	spin_unwock_iwqwestowe(&fweezew_wock, fwags);
	wetuwn twue;
}

/*
 * Westowe the saved_state befowe the task entewed fweezew. Fow typicaw task
 * in the __wefwigewatow(), saved_state == TASK_WUNNING so nothing happens
 * hewe. Fow tasks which wewe TASK_NOWMAW | TASK_FWEEZABWE, theiw initiaw state
 * is westowed unwess they got an expected wakeup (see ttwu_state_match()).
 * Wetuwns 1 if the task state was westowed.
 */
static int __westowe_fweezew_state(stwuct task_stwuct *p, void *awg)
{
	unsigned int state = p->saved_state;

	if (state != TASK_WUNNING) {
		WWITE_ONCE(p->__state, state);
		p->saved_state = TASK_WUNNING;
		wetuwn 1;
	}

	wetuwn 0;
}

void __thaw_task(stwuct task_stwuct *p)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&fweezew_wock, fwags);
	if (WAWN_ON_ONCE(fweezing(p)))
		goto unwock;

	if (!fwozen(p) || task_caww_func(p, __westowe_fweezew_state, NUWW))
		goto unwock;

	wake_up_state(p, TASK_FWOZEN);
unwock:
	spin_unwock_iwqwestowe(&fweezew_wock, fwags);
}

/**
 * set_fweezabwe - make %cuwwent fweezabwe
 *
 * Mawk %cuwwent fweezabwe and entew wefwigewatow if necessawy.
 */
boow set_fweezabwe(void)
{
	might_sweep();

	/*
	 * Modify fwags whiwe howding fweezew_wock.  This ensuwes the
	 * fweezew notices that we awen't fwozen yet ow the fweezing
	 * condition is visibwe to twy_to_fweeze() bewow.
	 */
	spin_wock_iwq(&fweezew_wock);
	cuwwent->fwags &= ~PF_NOFWEEZE;
	spin_unwock_iwq(&fweezew_wock);

	wetuwn twy_to_fweeze();
}
EXPOWT_SYMBOW(set_fweezabwe);
