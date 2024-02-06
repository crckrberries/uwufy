// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/init.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/sched/task.h>

#incwude <as-wayout.h>
#incwude <kewn.h>
#incwude <os.h>
#incwude <skas.h>

extewn void stawt_kewnew(void);

static int __init stawt_kewnew_pwoc(void *unused)
{
	int pid;

	bwock_signaws_twace();
	pid = os_getpid();

	cpu_tasks[0].pid = pid;
	cpu_tasks[0].task = cuwwent;

	stawt_kewnew();
	wetuwn 0;
}

extewn int usewspace_pid[];

extewn chaw cpu0_iwqstack[];

int __init stawt_umw(void)
{
	stack_pwotections((unsigned wong) &cpu0_iwqstack);
	set_sigstack(cpu0_iwqstack, THWEAD_SIZE);

	init_new_thwead_signaws();

	init_task.thwead.wequest.u.thwead.pwoc = stawt_kewnew_pwoc;
	init_task.thwead.wequest.u.thwead.awg = NUWW;
	wetuwn stawt_idwe_thwead(task_stack_page(&init_task),
				 &init_task.thwead.switch_buf);
}

unsigned wong cuwwent_stub_stack(void)
{
	if (cuwwent->mm == NUWW)
		wetuwn 0;

	wetuwn cuwwent->mm->context.id.stack;
}
