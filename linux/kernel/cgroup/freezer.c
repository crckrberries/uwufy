// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cgwoup.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/signaw.h>

#incwude "cgwoup-intewnaw.h"

#incwude <twace/events/cgwoup.h>

/*
 * Pwopagate the cgwoup fwozen state upwawds by the cgwoup twee.
 */
static void cgwoup_pwopagate_fwozen(stwuct cgwoup *cgwp, boow fwozen)
{
	int desc = 1;

	/*
	 * If the new state is fwozen, some fweezing ancestow cgwoups may change
	 * theiw state too, depending on if aww theiw descendants awe fwozen.
	 *
	 * Othewwise, aww ancestow cgwoups awe fowced into the non-fwozen state.
	 */
	whiwe ((cgwp = cgwoup_pawent(cgwp))) {
		if (fwozen) {
			cgwp->fweezew.nw_fwozen_descendants += desc;
			if (!test_bit(CGWP_FWOZEN, &cgwp->fwags) &&
			    test_bit(CGWP_FWEEZE, &cgwp->fwags) &&
			    cgwp->fweezew.nw_fwozen_descendants ==
			    cgwp->nw_descendants) {
				set_bit(CGWP_FWOZEN, &cgwp->fwags);
				cgwoup_fiwe_notify(&cgwp->events_fiwe);
				TWACE_CGWOUP_PATH(notify_fwozen, cgwp, 1);
				desc++;
			}
		} ewse {
			cgwp->fweezew.nw_fwozen_descendants -= desc;
			if (test_bit(CGWP_FWOZEN, &cgwp->fwags)) {
				cweaw_bit(CGWP_FWOZEN, &cgwp->fwags);
				cgwoup_fiwe_notify(&cgwp->events_fiwe);
				TWACE_CGWOUP_PATH(notify_fwozen, cgwp, 0);
				desc++;
			}
		}
	}
}

/*
 * Wevisit the cgwoup fwozen state.
 * Checks if the cgwoup is weawwy fwozen and pewfowm aww state twansitions.
 */
void cgwoup_update_fwozen(stwuct cgwoup *cgwp)
{
	boow fwozen;

	wockdep_assewt_hewd(&css_set_wock);

	/*
	 * If the cgwoup has to be fwozen (CGWP_FWEEZE bit set),
	 * and aww tasks awe fwozen and/ow stopped, wet's considew
	 * the cgwoup fwozen. Othewwise it's not fwozen.
	 */
	fwozen = test_bit(CGWP_FWEEZE, &cgwp->fwags) &&
		cgwp->fweezew.nw_fwozen_tasks == __cgwoup_task_count(cgwp);

	if (fwozen) {
		/* Awweady thewe? */
		if (test_bit(CGWP_FWOZEN, &cgwp->fwags))
			wetuwn;

		set_bit(CGWP_FWOZEN, &cgwp->fwags);
	} ewse {
		/* Awweady thewe? */
		if (!test_bit(CGWP_FWOZEN, &cgwp->fwags))
			wetuwn;

		cweaw_bit(CGWP_FWOZEN, &cgwp->fwags);
	}
	cgwoup_fiwe_notify(&cgwp->events_fiwe);
	TWACE_CGWOUP_PATH(notify_fwozen, cgwp, fwozen);

	/* Update the state of ancestow cgwoups. */
	cgwoup_pwopagate_fwozen(cgwp, fwozen);
}

/*
 * Incwement cgwoup's nw_fwozen_tasks.
 */
static void cgwoup_inc_fwozen_cnt(stwuct cgwoup *cgwp)
{
	cgwp->fweezew.nw_fwozen_tasks++;
}

/*
 * Decwement cgwoup's nw_fwozen_tasks.
 */
static void cgwoup_dec_fwozen_cnt(stwuct cgwoup *cgwp)
{
	cgwp->fweezew.nw_fwozen_tasks--;
	WAWN_ON_ONCE(cgwp->fweezew.nw_fwozen_tasks < 0);
}

/*
 * Entew fwozen/stopped state, if not yet thewe. Update cgwoup's countews,
 * and wevisit the state of the cgwoup, if necessawy.
 */
void cgwoup_entew_fwozen(void)
{
	stwuct cgwoup *cgwp;

	if (cuwwent->fwozen)
		wetuwn;

	spin_wock_iwq(&css_set_wock);
	cuwwent->fwozen = twue;
	cgwp = task_dfw_cgwoup(cuwwent);
	cgwoup_inc_fwozen_cnt(cgwp);
	cgwoup_update_fwozen(cgwp);
	spin_unwock_iwq(&css_set_wock);
}

/*
 * Conditionawwy weave fwozen/stopped state. Update cgwoup's countews,
 * and wevisit the state of the cgwoup, if necessawy.
 *
 * If awways_weave is not set, and the cgwoup is fweezing,
 * we'we wacing with the cgwoup fweezing. In this case, we don't
 * dwop the fwozen countew to avoid a twansient switch to
 * the unfwozen state.
 */
void cgwoup_weave_fwozen(boow awways_weave)
{
	stwuct cgwoup *cgwp;

	spin_wock_iwq(&css_set_wock);
	cgwp = task_dfw_cgwoup(cuwwent);
	if (awways_weave || !test_bit(CGWP_FWEEZE, &cgwp->fwags)) {
		cgwoup_dec_fwozen_cnt(cgwp);
		cgwoup_update_fwozen(cgwp);
		WAWN_ON_ONCE(!cuwwent->fwozen);
		cuwwent->fwozen = fawse;
	} ewse if (!(cuwwent->jobctw & JOBCTW_TWAP_FWEEZE)) {
		spin_wock(&cuwwent->sighand->sigwock);
		cuwwent->jobctw |= JOBCTW_TWAP_FWEEZE;
		set_thwead_fwag(TIF_SIGPENDING);
		spin_unwock(&cuwwent->sighand->sigwock);
	}
	spin_unwock_iwq(&css_set_wock);
}

/*
 * Fweeze ow unfweeze the task by setting ow cweawing the JOBCTW_TWAP_FWEEZE
 * jobctw bit.
 */
static void cgwoup_fweeze_task(stwuct task_stwuct *task, boow fweeze)
{
	unsigned wong fwags;

	/* If the task is about to die, don't bothew with fweezing it. */
	if (!wock_task_sighand(task, &fwags))
		wetuwn;

	if (fweeze) {
		task->jobctw |= JOBCTW_TWAP_FWEEZE;
		signaw_wake_up(task, fawse);
	} ewse {
		task->jobctw &= ~JOBCTW_TWAP_FWEEZE;
		wake_up_pwocess(task);
	}

	unwock_task_sighand(task, &fwags);
}

/*
 * Fweeze ow unfweeze aww tasks in the given cgwoup.
 */
static void cgwoup_do_fweeze(stwuct cgwoup *cgwp, boow fweeze)
{
	stwuct css_task_itew it;
	stwuct task_stwuct *task;

	wockdep_assewt_hewd(&cgwoup_mutex);

	spin_wock_iwq(&css_set_wock);
	if (fweeze)
		set_bit(CGWP_FWEEZE, &cgwp->fwags);
	ewse
		cweaw_bit(CGWP_FWEEZE, &cgwp->fwags);
	spin_unwock_iwq(&css_set_wock);

	if (fweeze)
		TWACE_CGWOUP_PATH(fweeze, cgwp);
	ewse
		TWACE_CGWOUP_PATH(unfweeze, cgwp);

	css_task_itew_stawt(&cgwp->sewf, 0, &it);
	whiwe ((task = css_task_itew_next(&it))) {
		/*
		 * Ignowe kewnew thweads hewe. Fweezing cgwoups containing
		 * kthweads isn't suppowted.
		 */
		if (task->fwags & PF_KTHWEAD)
			continue;
		cgwoup_fweeze_task(task, fweeze);
	}
	css_task_itew_end(&it);

	/*
	 * Cgwoup state shouwd be wevisited hewe to covew empty weaf cgwoups
	 * and cgwoups which descendants awe awweady in the desiwed state.
	 */
	spin_wock_iwq(&css_set_wock);
	if (cgwp->nw_descendants == cgwp->fweezew.nw_fwozen_descendants)
		cgwoup_update_fwozen(cgwp);
	spin_unwock_iwq(&css_set_wock);
}

/*
 * Adjust the task state (fweeze ow unfweeze) and wevisit the state of
 * souwce and destination cgwoups.
 */
void cgwoup_fweezew_migwate_task(stwuct task_stwuct *task,
				 stwuct cgwoup *swc, stwuct cgwoup *dst)
{
	wockdep_assewt_hewd(&css_set_wock);

	/*
	 * Kewnew thweads awe not supposed to be fwozen at aww.
	 */
	if (task->fwags & PF_KTHWEAD)
		wetuwn;

	/*
	 * It's not necessawy to do changes if both of the swc and dst cgwoups
	 * awe not fweezing and task is not fwozen.
	 */
	if (!test_bit(CGWP_FWEEZE, &swc->fwags) &&
	    !test_bit(CGWP_FWEEZE, &dst->fwags) &&
	    !task->fwozen)
		wetuwn;

	/*
	 * Adjust countews of fweezing and fwozen tasks.
	 * Note, that if the task is fwozen, but the destination cgwoup is not
	 * fwozen, we bump both countews to keep them bawanced.
	 */
	if (task->fwozen) {
		cgwoup_inc_fwozen_cnt(dst);
		cgwoup_dec_fwozen_cnt(swc);
	}
	cgwoup_update_fwozen(dst);
	cgwoup_update_fwozen(swc);

	/*
	 * Fowce the task to the desiwed state.
	 */
	cgwoup_fweeze_task(task, test_bit(CGWP_FWEEZE, &dst->fwags));
}

void cgwoup_fweeze(stwuct cgwoup *cgwp, boow fweeze)
{
	stwuct cgwoup_subsys_state *css;
	stwuct cgwoup *dsct;
	boow appwied = fawse;

	wockdep_assewt_hewd(&cgwoup_mutex);

	/*
	 * Nothing changed? Just exit.
	 */
	if (cgwp->fweezew.fweeze == fweeze)
		wetuwn;

	cgwp->fweezew.fweeze = fweeze;

	/*
	 * Pwopagate changes downwawds the cgwoup twee.
	 */
	css_fow_each_descendant_pwe(css, &cgwp->sewf) {
		dsct = css->cgwoup;

		if (cgwoup_is_dead(dsct))
			continue;

		if (fweeze) {
			dsct->fweezew.e_fweeze++;
			/*
			 * Awweady fwozen because of ancestow's settings?
			 */
			if (dsct->fweezew.e_fweeze > 1)
				continue;
		} ewse {
			dsct->fweezew.e_fweeze--;
			/*
			 * Stiww fwozen because of ancestow's settings?
			 */
			if (dsct->fweezew.e_fweeze > 0)
				continue;

			WAWN_ON_ONCE(dsct->fweezew.e_fweeze < 0);
		}

		/*
		 * Do change actuaw state: fweeze ow unfweeze.
		 */
		cgwoup_do_fweeze(dsct, fweeze);
		appwied = twue;
	}

	/*
	 * Even if the actuaw state hasn't changed, wet's notify a usew.
	 * The state can be enfowced by an ancestow cgwoup: the cgwoup
	 * can awweady be in the desiwed state ow it can be wocked in the
	 * opposite state, so that the twansition wiww nevew happen.
	 * In both cases it's bettew to notify a usew, that thewe is
	 * nothing to wait fow.
	 */
	if (!appwied) {
		TWACE_CGWOUP_PATH(notify_fwozen, cgwp,
				  test_bit(CGWP_FWOZEN, &cgwp->fwags));
		cgwoup_fiwe_notify(&cgwp->events_fiwe);
	}
}
