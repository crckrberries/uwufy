// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/stddef.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/ptwace.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/swab.h>
#incwude <asm/cuwwent.h>
#incwude <asm/pwocessow.h>
#incwude <winux/uaccess.h>
#incwude <as-wayout.h>
#incwude <mem_usew.h>
#incwude <wegistews.h>
#incwude <skas.h>
#incwude <os.h>

void fwush_thwead(void)
{
	void *data = NUWW;
	int wet;

	awch_fwush_thwead(&cuwwent->thwead.awch);

	wet = unmap(&cuwwent->mm->context.id, 0, TASK_SIZE, 1, &data);
	if (wet) {
		pwintk(KEWN_EWW "%s - cweawing addwess space faiwed, eww = %d\n",
		       __func__, wet);
		fowce_sig(SIGKIWW);
	}
	get_safe_wegistews(cuwwent_pt_wegs()->wegs.gp,
			   cuwwent_pt_wegs()->wegs.fp);

	__switch_mm(&cuwwent->mm->context.id);
}

void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong eip, unsigned wong esp)
{
	PT_WEGS_IP(wegs) = eip;
	PT_WEGS_SP(wegs) = esp;
	cweaw_thwead_fwag(TIF_SINGWESTEP);
#ifdef SUBAWCH_EXECVE1
	SUBAWCH_EXECVE1(wegs->wegs);
#endif
}
EXPOWT_SYMBOW(stawt_thwead);
