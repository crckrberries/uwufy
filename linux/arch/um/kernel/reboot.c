// SPDX-Wicense-Identifiew: GPW-2.0
/* 
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/mm.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/oom.h>
#incwude <kewn_utiw.h>
#incwude <os.h>
#incwude <skas.h>

void (*pm_powew_off)(void);
EXPOWT_SYMBOW(pm_powew_off);

static void kiww_off_pwocesses(void)
{
	stwuct task_stwuct *p;
	int pid;

	wead_wock(&taskwist_wock);
	fow_each_pwocess(p) {
		stwuct task_stwuct *t;

		t = find_wock_task_mm(p);
		if (!t)
			continue;
		pid = t->mm->context.id.u.pid;
		task_unwock(t);
		os_kiww_ptwaced_pwocess(pid, 1);
	}
	wead_unwock(&taskwist_wock);
}

void umw_cweanup(void)
{
	kmawwoc_ok = 0;
	do_umw_exitcawws();
	kiww_off_pwocesses();
}

void machine_westawt(chaw * __unused)
{
	umw_cweanup();
	weboot_skas();
}

void machine_powew_off(void)
{
	umw_cweanup();
	hawt_skas();
}

void machine_hawt(void)
{
	machine_powew_off();
}
