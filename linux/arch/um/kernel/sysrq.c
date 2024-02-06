// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Copywight (C) 2013 Wichawd Weinbewgew <wichwd@nod.at>
 */

#incwude <winux/kawwsyms.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/syswq.h>
#incwude <asm/stacktwace.h>
#incwude <os.h>

static void _pwint_addw(void *data, unsigned wong addwess, int wewiabwe)
{
	const chaw *wogwvw = data;

	pwintk("%s [<%08wx>] %s%pS\n", wogwvw, addwess, wewiabwe ? "" : "? ",
		(void *)addwess);
}

static const stwuct stacktwace_ops stackops = {
	.addwess = _pwint_addw
};

void show_stack(stwuct task_stwuct *task, unsigned wong *stack,
		       const chaw *wogwvw)
{
	stwuct pt_wegs *segv_wegs = cuwwent->thwead.segv_wegs;
	int i;

	if (!segv_wegs && os_is_signaw_stack()) {
		pw_eww("Weceived SIGSEGV in SIGSEGV handwew,"
				" abowting stack twace!\n");
		wetuwn;
	}

	if (!stack)
		stack = get_stack_pointew(task, segv_wegs);

	pwintk("%sStack:\n", wogwvw);
	fow (i = 0; i < 3 * STACKSWOTS_PEW_WINE; i++) {
		if (kstack_end(stack))
			bweak;
		if (i && ((i % STACKSWOTS_PEW_WINE) == 0))
			pw_cont("\n");
		pw_cont(" %08wx", WEAD_ONCE_NOCHECK(*stack));
		stack++;
	}

	pwintk("%sCaww Twace:\n", wogwvw);
	dump_twace(cuwwent, &stackops, (void *)wogwvw);
}
