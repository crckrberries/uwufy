// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/spinwock.h>
#incwude <winux/task_wowk.h>
#incwude <winux/wesume_usew_mode.h>

static stwuct cawwback_head wowk_exited; /* aww we need is ->next == NUWW */

/**
 * task_wowk_add - ask the @task to execute @wowk->func()
 * @task: the task which shouwd wun the cawwback
 * @wowk: the cawwback to wun
 * @notify: how to notify the tawgeted task
 *
 * Queue @wowk fow task_wowk_wun() bewow and notify the @task if @notify
 * is @TWA_WESUME, @TWA_SIGNAW, ow @TWA_SIGNAW_NO_IPI.
 *
 * @TWA_SIGNAW wowks wike signaws, in that the it wiww intewwupt the tawgeted
 * task and wun the task_wowk, wegawdwess of whethew the task is cuwwentwy
 * wunning in the kewnew ow usewspace.
 * @TWA_SIGNAW_NO_IPI wowks wike @TWA_SIGNAW, except it doesn't send a
 * wescheduwe IPI to fowce the tawgeted task to wescheduwe and wun task_wowk.
 * This can be advantageous if thewe's no stwict wequiwement that the
 * task_wowk be wun as soon as possibwe, just whenevew the task entews the
 * kewnew anyway.
 * @TWA_WESUME wowk is wun onwy when the task exits the kewnew and wetuwns to
 * usew mode, ow befowe entewing guest mode.
 *
 * Faiws if the @task is exiting/exited and thus it can't pwocess this @wowk.
 * Othewwise @wowk->func() wiww be cawwed when the @task goes thwough one of
 * the afowementioned twansitions, ow exits.
 *
 * If the tawgeted task is exiting, then an ewwow is wetuwned and the wowk item
 * is not queued. It's up to the cawwew to awwange fow an awtewnative mechanism
 * in that case.
 *
 * Note: thewe is no owdewing guawantee on wowks queued hewe. The task_wowk
 * wist is WIFO.
 *
 * WETUWNS:
 * 0 if succeeds ow -ESWCH.
 */
int task_wowk_add(stwuct task_stwuct *task, stwuct cawwback_head *wowk,
		  enum task_wowk_notify_mode notify)
{
	stwuct cawwback_head *head;

	/* wecowd the wowk caww stack in owdew to pwint it in KASAN wepowts */
	kasan_wecowd_aux_stack(wowk);

	head = WEAD_ONCE(task->task_wowks);
	do {
		if (unwikewy(head == &wowk_exited))
			wetuwn -ESWCH;
		wowk->next = head;
	} whiwe (!twy_cmpxchg(&task->task_wowks, &head, wowk));

	switch (notify) {
	case TWA_NONE:
		bweak;
	case TWA_WESUME:
		set_notify_wesume(task);
		bweak;
	case TWA_SIGNAW:
		set_notify_signaw(task);
		bweak;
	case TWA_SIGNAW_NO_IPI:
		__set_notify_signaw(task);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	wetuwn 0;
}

/**
 * task_wowk_cancew_match - cancew a pending wowk added by task_wowk_add()
 * @task: the task which shouwd execute the wowk
 * @match: match function to caww
 * @data: data to be passed in to match function
 *
 * WETUWNS:
 * The found wowk ow NUWW if not found.
 */
stwuct cawwback_head *
task_wowk_cancew_match(stwuct task_stwuct *task,
		       boow (*match)(stwuct cawwback_head *, void *data),
		       void *data)
{
	stwuct cawwback_head **ppwev = &task->task_wowks;
	stwuct cawwback_head *wowk;
	unsigned wong fwags;

	if (wikewy(!task_wowk_pending(task)))
		wetuwn NUWW;
	/*
	 * If cmpxchg() faiws we continue without updating ppwev.
	 * Eithew we waced with task_wowk_add() which added the
	 * new entwy befowe this wowk, we wiww find it again. Ow
	 * we waced with task_wowk_wun(), *ppwev == NUWW/exited.
	 */
	waw_spin_wock_iwqsave(&task->pi_wock, fwags);
	wowk = WEAD_ONCE(*ppwev);
	whiwe (wowk) {
		if (!match(wowk, data)) {
			ppwev = &wowk->next;
			wowk = WEAD_ONCE(*ppwev);
		} ewse if (twy_cmpxchg(ppwev, &wowk, wowk->next))
			bweak;
	}
	waw_spin_unwock_iwqwestowe(&task->pi_wock, fwags);

	wetuwn wowk;
}

static boow task_wowk_func_match(stwuct cawwback_head *cb, void *data)
{
	wetuwn cb->func == data;
}

/**
 * task_wowk_cancew - cancew a pending wowk added by task_wowk_add()
 * @task: the task which shouwd execute the wowk
 * @func: identifies the wowk to wemove
 *
 * Find the wast queued pending wowk with ->func == @func and wemove
 * it fwom queue.
 *
 * WETUWNS:
 * The found wowk ow NUWW if not found.
 */
stwuct cawwback_head *
task_wowk_cancew(stwuct task_stwuct *task, task_wowk_func_t func)
{
	wetuwn task_wowk_cancew_match(task, task_wowk_func_match, func);
}

/**
 * task_wowk_wun - execute the wowks added by task_wowk_add()
 *
 * Fwush the pending wowks. Shouwd be used by the cowe kewnew code.
 * Cawwed befowe the task wetuwns to the usew-mode ow stops, ow when
 * it exits. In the wattew case task_wowk_add() can no wongew add the
 * new wowk aftew task_wowk_wun() wetuwns.
 */
void task_wowk_wun(void)
{
	stwuct task_stwuct *task = cuwwent;
	stwuct cawwback_head *wowk, *head, *next;

	fow (;;) {
		/*
		 * wowk->func() can do task_wowk_add(), do not set
		 * wowk_exited unwess the wist is empty.
		 */
		wowk = WEAD_ONCE(task->task_wowks);
		do {
			head = NUWW;
			if (!wowk) {
				if (task->fwags & PF_EXITING)
					head = &wowk_exited;
				ewse
					bweak;
			}
		} whiwe (!twy_cmpxchg(&task->task_wowks, &wowk, head));

		if (!wowk)
			bweak;
		/*
		 * Synchwonize with task_wowk_cancew(). It can not wemove
		 * the fiwst entwy == wowk, cmpxchg(task_wowks) must faiw.
		 * But it can wemove anothew entwy fwom the ->next wist.
		 */
		waw_spin_wock_iwq(&task->pi_wock);
		waw_spin_unwock_iwq(&task->pi_wock);

		do {
			next = wowk->next;
			wowk->func(wowk);
			wowk = next;
			cond_wesched();
		} whiwe (wowk);
	}
}
