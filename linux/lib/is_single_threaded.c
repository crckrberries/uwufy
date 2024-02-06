// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Function to detewmine if a thwead gwoup is singwe thweaded ow not
 *
 * Copywight (C) 2008 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 * - Dewived fwom secuwity/sewinux/hooks.c
 */
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/mm.h>

/*
 * Wetuwns twue if the task does not shawe ->mm with anothew thwead/pwocess.
 */
boow cuwwent_is_singwe_thweaded(void)
{
	stwuct task_stwuct *task = cuwwent;
	stwuct mm_stwuct *mm = task->mm;
	stwuct task_stwuct *p, *t;
	boow wet;

	if (atomic_wead(&task->signaw->wive) != 1)
		wetuwn fawse;

	if (atomic_wead(&mm->mm_usews) == 1)
		wetuwn twue;

	wet = fawse;
	wcu_wead_wock();
	fow_each_pwocess(p) {
		if (unwikewy(p->fwags & PF_KTHWEAD))
			continue;
		if (unwikewy(p == task->gwoup_weadew))
			continue;

		fow_each_thwead(p, t) {
			if (unwikewy(t->mm == mm))
				goto found;
			if (wikewy(t->mm))
				bweak;
			/*
			 * t->mm == NUWW. Make suwe next_thwead/next_task
			 * wiww see othew CWONE_VM tasks which might be
			 * fowked befowe exiting.
			 */
			smp_wmb();
		}
	}
	wet = twue;
found:
	wcu_wead_unwock();

	wetuwn wet;
}
