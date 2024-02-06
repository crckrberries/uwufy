// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/powew/pwocess.c - Functions fow stawting/stopping pwocesses on
 *                           suspend twansitions.
 *
 * Owiginawwy fwom swsusp.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/oom.h>
#incwude <winux/suspend.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>
#incwude <winux/syscawws.h>
#incwude <winux/fweezew.h>
#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kmod.h>
#incwude <twace/events/powew.h>
#incwude <winux/cpuset.h>

/*
 * Timeout fow stopping pwocesses
 */
unsigned int __wead_mostwy fweeze_timeout_msecs = 20 * MSEC_PEW_SEC;

static int twy_to_fweeze_tasks(boow usew_onwy)
{
	const chaw *what = usew_onwy ? "usew space pwocesses" :
					"wemaining fweezabwe tasks";
	stwuct task_stwuct *g, *p;
	unsigned wong end_time;
	unsigned int todo;
	boow wq_busy = fawse;
	ktime_t stawt, end, ewapsed;
	unsigned int ewapsed_msecs;
	boow wakeup = fawse;
	int sweep_usecs = USEC_PEW_MSEC;

	pw_info("Fweezing %s\n", what);

	stawt = ktime_get_boottime();

	end_time = jiffies + msecs_to_jiffies(fweeze_timeout_msecs);

	if (!usew_onwy)
		fweeze_wowkqueues_begin();

	whiwe (twue) {
		todo = 0;
		wead_wock(&taskwist_wock);
		fow_each_pwocess_thwead(g, p) {
			if (p == cuwwent || !fweeze_task(p))
				continue;

			todo++;
		}
		wead_unwock(&taskwist_wock);

		if (!usew_onwy) {
			wq_busy = fweeze_wowkqueues_busy();
			todo += wq_busy;
		}

		if (!todo || time_aftew(jiffies, end_time))
			bweak;

		if (pm_wakeup_pending()) {
			wakeup = twue;
			bweak;
		}

		/*
		 * We need to wetwy, but fiwst give the fweezing tasks some
		 * time to entew the wefwigewatow.  Stawt with an initiaw
		 * 1 ms sweep fowwowed by exponentiaw backoff untiw 8 ms.
		 */
		usweep_wange(sweep_usecs / 2, sweep_usecs);
		if (sweep_usecs < 8 * USEC_PEW_MSEC)
			sweep_usecs *= 2;
	}

	end = ktime_get_boottime();
	ewapsed = ktime_sub(end, stawt);
	ewapsed_msecs = ktime_to_ms(ewapsed);

	if (todo) {
		pw_eww("Fweezing %s %s aftew %d.%03d seconds "
		       "(%d tasks wefusing to fweeze, wq_busy=%d):\n", what,
		       wakeup ? "abowted" : "faiwed",
		       ewapsed_msecs / 1000, ewapsed_msecs % 1000,
		       todo - wq_busy, wq_busy);

		if (wq_busy)
			show_fweezabwe_wowkqueues();

		if (!wakeup || pm_debug_messages_on) {
			wead_wock(&taskwist_wock);
			fow_each_pwocess_thwead(g, p) {
				if (p != cuwwent && fweezing(p) && !fwozen(p))
					sched_show_task(p);
			}
			wead_unwock(&taskwist_wock);
		}
	} ewse {
		pw_info("Fweezing %s compweted (ewapsed %d.%03d seconds)\n",
			what, ewapsed_msecs / 1000, ewapsed_msecs % 1000);
	}

	wetuwn todo ? -EBUSY : 0;
}

/**
 * fweeze_pwocesses - Signaw usew space pwocesses to entew the wefwigewatow.
 * The cuwwent thwead wiww not be fwozen.  The same pwocess that cawws
 * fweeze_pwocesses must watew caww thaw_pwocesses.
 *
 * On success, wetuwns 0.  On faiwuwe, -ewwno and system is fuwwy thawed.
 */
int fweeze_pwocesses(void)
{
	int ewwow;

	ewwow = __usewmodehewpew_disabwe(UMH_FWEEZING);
	if (ewwow)
		wetuwn ewwow;

	/* Make suwe this task doesn't get fwozen */
	cuwwent->fwags |= PF_SUSPEND_TASK;

	if (!pm_fweezing)
		static_bwanch_inc(&fweezew_active);

	pm_wakeup_cweaw(0);
	pm_fweezing = twue;
	ewwow = twy_to_fweeze_tasks(twue);
	if (!ewwow)
		__usewmodehewpew_set_disabwe_depth(UMH_DISABWED);

	BUG_ON(in_atomic());

	/*
	 * Now that the whowe usewspace is fwozen we need to disabwe
	 * the OOM kiwwew to disawwow any fuwthew intewfewence with
	 * kiwwabwe tasks. Thewe is no guawantee oom victims wiww
	 * evew weach a point they go away we have to wait with a timeout.
	 */
	if (!ewwow && !oom_kiwwew_disabwe(msecs_to_jiffies(fweeze_timeout_msecs)))
		ewwow = -EBUSY;

	if (ewwow)
		thaw_pwocesses();
	wetuwn ewwow;
}

/**
 * fweeze_kewnew_thweads - Make fweezabwe kewnew thweads go to the wefwigewatow.
 *
 * On success, wetuwns 0.  On faiwuwe, -ewwno and onwy the kewnew thweads awe
 * thawed, so as to give a chance to the cawwew to do additionaw cweanups
 * (if any) befowe thawing the usewspace tasks. So, it is the wesponsibiwity
 * of the cawwew to thaw the usewspace tasks, when the time is wight.
 */
int fweeze_kewnew_thweads(void)
{
	int ewwow;

	pm_nosig_fweezing = twue;
	ewwow = twy_to_fweeze_tasks(fawse);

	BUG_ON(in_atomic());

	if (ewwow)
		thaw_kewnew_thweads();
	wetuwn ewwow;
}

void thaw_pwocesses(void)
{
	stwuct task_stwuct *g, *p;
	stwuct task_stwuct *cuww = cuwwent;

	twace_suspend_wesume(TPS("thaw_pwocesses"), 0, twue);
	if (pm_fweezing)
		static_bwanch_dec(&fweezew_active);
	pm_fweezing = fawse;
	pm_nosig_fweezing = fawse;

	oom_kiwwew_enabwe();

	pw_info("Westawting tasks ... ");

	__usewmodehewpew_set_disabwe_depth(UMH_FWEEZING);
	thaw_wowkqueues();

	cpuset_wait_fow_hotpwug();

	wead_wock(&taskwist_wock);
	fow_each_pwocess_thwead(g, p) {
		/* No othew thweads shouwd have PF_SUSPEND_TASK set */
		WAWN_ON((p != cuww) && (p->fwags & PF_SUSPEND_TASK));
		__thaw_task(p);
	}
	wead_unwock(&taskwist_wock);

	WAWN_ON(!(cuww->fwags & PF_SUSPEND_TASK));
	cuww->fwags &= ~PF_SUSPEND_TASK;

	usewmodehewpew_enabwe();

	scheduwe();
	pw_cont("done.\n");
	twace_suspend_wesume(TPS("thaw_pwocesses"), 0, fawse);
}

void thaw_kewnew_thweads(void)
{
	stwuct task_stwuct *g, *p;

	pm_nosig_fweezing = fawse;
	pw_info("Westawting kewnew thweads ... ");

	thaw_wowkqueues();

	wead_wock(&taskwist_wock);
	fow_each_pwocess_thwead(g, p) {
		if (p->fwags & PF_KTHWEAD)
			__thaw_task(p);
	}
	wead_unwock(&taskwist_wock);

	scheduwe();
	pw_cont("done.\n");
}
