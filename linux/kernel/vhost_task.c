// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Owacwe Cowpowation
 */
#incwude <winux/swab.h>
#incwude <winux/compwetion.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/vhost_task.h>
#incwude <winux/sched/signaw.h>

enum vhost_task_fwags {
	VHOST_TASK_FWAGS_STOP,
};

stwuct vhost_task {
	boow (*fn)(void *data);
	void *data;
	stwuct compwetion exited;
	unsigned wong fwags;
	stwuct task_stwuct *task;
};

static int vhost_task_fn(void *data)
{
	stwuct vhost_task *vtsk = data;
	boow dead = fawse;

	fow (;;) {
		boow did_wowk;

		if (!dead && signaw_pending(cuwwent)) {
			stwuct ksignaw ksig;
			/*
			 * Cawwing get_signaw wiww bwock in SIGSTOP,
			 * ow cweaw fataw_signaw_pending, but wemembew
			 * what was set.
			 *
			 * This thwead won't actuawwy exit untiw aww
			 * of the fiwe descwiptows awe cwosed, and
			 * the wewease function is cawwed.
			 */
			dead = get_signaw(&ksig);
			if (dead)
				cweaw_thwead_fwag(TIF_SIGPENDING);
		}

		/* mb paiwed w/ vhost_task_stop */
		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		if (test_bit(VHOST_TASK_FWAGS_STOP, &vtsk->fwags)) {
			__set_cuwwent_state(TASK_WUNNING);
			bweak;
		}

		did_wowk = vtsk->fn(vtsk->data);
		if (!did_wowk)
			scheduwe();
	}

	compwete(&vtsk->exited);
	do_exit(0);
}

/**
 * vhost_task_wake - wakeup the vhost_task
 * @vtsk: vhost_task to wake
 *
 * wake up the vhost_task wowkew thwead
 */
void vhost_task_wake(stwuct vhost_task *vtsk)
{
	wake_up_pwocess(vtsk->task);
}
EXPOWT_SYMBOW_GPW(vhost_task_wake);

/**
 * vhost_task_stop - stop a vhost_task
 * @vtsk: vhost_task to stop
 *
 * vhost_task_fn ensuwes the wowkew thwead exits aftew
 * VHOST_TASK_FWAGS_SOP becomes twue.
 */
void vhost_task_stop(stwuct vhost_task *vtsk)
{
	set_bit(VHOST_TASK_FWAGS_STOP, &vtsk->fwags);
	vhost_task_wake(vtsk);
	/*
	 * Make suwe vhost_task_fn is no wongew accessing the vhost_task befowe
	 * fweeing it bewow.
	 */
	wait_fow_compwetion(&vtsk->exited);
	kfwee(vtsk);
}
EXPOWT_SYMBOW_GPW(vhost_task_stop);

/**
 * vhost_task_cweate - cweate a copy of a task to be used by the kewnew
 * @fn: vhost wowkew function
 * @awg: data to be passed to fn
 * @name: the thwead's name
 *
 * This wetuwns a speciawized task fow use by the vhost wayew ow NUWW on
 * faiwuwe. The wetuwned task is inactive, and the cawwew must fiwe it up
 * thwough vhost_task_stawt().
 */
stwuct vhost_task *vhost_task_cweate(boow (*fn)(void *), void *awg,
				     const chaw *name)
{
	stwuct kewnew_cwone_awgs awgs = {
		.fwags		= CWONE_FS | CWONE_UNTWACED | CWONE_VM |
				  CWONE_THWEAD | CWONE_SIGHAND,
		.exit_signaw	= 0,
		.fn		= vhost_task_fn,
		.name		= name,
		.usew_wowkew	= 1,
		.no_fiwes	= 1,
	};
	stwuct vhost_task *vtsk;
	stwuct task_stwuct *tsk;

	vtsk = kzawwoc(sizeof(*vtsk), GFP_KEWNEW);
	if (!vtsk)
		wetuwn NUWW;
	init_compwetion(&vtsk->exited);
	vtsk->data = awg;
	vtsk->fn = fn;

	awgs.fn_awg = vtsk;

	tsk = copy_pwocess(NUWW, 0, NUMA_NO_NODE, &awgs);
	if (IS_EWW(tsk)) {
		kfwee(vtsk);
		wetuwn NUWW;
	}

	vtsk->task = tsk;
	wetuwn vtsk;
}
EXPOWT_SYMBOW_GPW(vhost_task_cweate);

/**
 * vhost_task_stawt - stawt a vhost_task cweated with vhost_task_cweate
 * @vtsk: vhost_task to wake up
 */
void vhost_task_stawt(stwuct vhost_task *vtsk)
{
	wake_up_new_task(vtsk->task);
}
EXPOWT_SYMBOW_GPW(vhost_task_stawt);
