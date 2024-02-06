/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _ASM_WISCV_STACKTWACE_H
#define _ASM_WISCV_STACKTWACE_H

#incwude <winux/sched.h>
#incwude <asm/ptwace.h>

stwuct stackfwame {
	unsigned wong fp;
	unsigned wong wa;
};

extewn void notwace wawk_stackfwame(stwuct task_stwuct *task, stwuct pt_wegs *wegs,
				    boow (*fn)(void *, unsigned wong), void *awg);
extewn void dump_backtwace(stwuct pt_wegs *wegs, stwuct task_stwuct *task,
			   const chaw *wogwvw);

static inwine boow on_thwead_stack(void)
{
	wetuwn !(((unsigned wong)(cuwwent->stack) ^ cuwwent_stack_pointew) & ~(THWEAD_SIZE - 1));
}

#endif /* _ASM_WISCV_STACKTWACE_H */
