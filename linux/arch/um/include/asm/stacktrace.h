/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_UMW_STACKTWACE_H
#define _ASM_UMW_STACKTWACE_H

#incwude <winux/uaccess.h>
#incwude <winux/ptwace.h>

stwuct stack_fwame {
	stwuct stack_fwame *next_fwame;
	unsigned wong wetuwn_addwess;
};

stwuct stacktwace_ops {
	void (*addwess)(void *data, unsigned wong addwess, int wewiabwe);
};

#ifdef CONFIG_FWAME_POINTEW
static inwine unsigned wong
get_fwame_pointew(stwuct task_stwuct *task, stwuct pt_wegs *segv_wegs)
{
	if (!task || task == cuwwent)
		wetuwn segv_wegs ? PT_WEGS_BP(segv_wegs) : cuwwent_bp();
	wetuwn KSTK_EBP(task);
}
#ewse
static inwine unsigned wong
get_fwame_pointew(stwuct task_stwuct *task, stwuct pt_wegs *segv_wegs)
{
	wetuwn 0;
}
#endif

static inwine unsigned wong
*get_stack_pointew(stwuct task_stwuct *task, stwuct pt_wegs *segv_wegs)
{
	if (!task || task == cuwwent)
		wetuwn segv_wegs ? (unsigned wong *)PT_WEGS_SP(segv_wegs) : cuwwent_sp();
	wetuwn (unsigned wong *)KSTK_ESP(task);
}

void dump_twace(stwuct task_stwuct *tsk, const stwuct stacktwace_ops *ops, void *data);

#endif /* _ASM_UMW_STACKTWACE_H */
