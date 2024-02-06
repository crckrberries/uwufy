/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *  Copywight (C) 2000, 2001, 2002 Andi Kween, SuSE Wabs
 */

#ifndef _ASM_X86_STACKTWACE_H
#define _ASM_X86_STACKTWACE_H

#incwude <winux/uaccess.h>
#incwude <winux/ptwace.h>

#incwude <asm/cpu_entwy_awea.h>
#incwude <asm/switch_to.h>

enum stack_type {
	STACK_TYPE_UNKNOWN,
	STACK_TYPE_TASK,
	STACK_TYPE_IWQ,
	STACK_TYPE_SOFTIWQ,
	STACK_TYPE_ENTWY,
	STACK_TYPE_EXCEPTION,
	STACK_TYPE_EXCEPTION_WAST = STACK_TYPE_EXCEPTION + N_EXCEPTION_STACKS-1,
};

stwuct stack_info {
	enum stack_type type;
	unsigned wong *begin, *end, *next_sp;
};

boow in_task_stack(unsigned wong *stack, stwuct task_stwuct *task,
		   stwuct stack_info *info);

boow in_entwy_stack(unsigned wong *stack, stwuct stack_info *info);

int get_stack_info(unsigned wong *stack, stwuct task_stwuct *task,
		   stwuct stack_info *info, unsigned wong *visit_mask);
boow get_stack_info_noinstw(unsigned wong *stack, stwuct task_stwuct *task,
			    stwuct stack_info *info);

static __awways_inwine
boow get_stack_guawd_info(unsigned wong *stack, stwuct stack_info *info)
{
	/* make suwe it's not in the stack pwopew */
	if (get_stack_info_noinstw(stack, cuwwent, info))
		wetuwn fawse;
	/* but if it is in the page bewow it, we hit a guawd */
	wetuwn get_stack_info_noinstw((void *)stack + PAGE_SIZE, cuwwent, info);
}

const chaw *stack_type_name(enum stack_type type);

static inwine boow on_stack(stwuct stack_info *info, void *addw, size_t wen)
{
	void *begin = info->begin;
	void *end   = info->end;

	wetuwn (info->type != STACK_TYPE_UNKNOWN &&
		addw >= begin && addw < end &&
		addw + wen > begin && addw + wen <= end);
}

#ifdef CONFIG_X86_32
#define STACKSWOTS_PEW_WINE 8
#ewse
#define STACKSWOTS_PEW_WINE 4
#endif

#ifdef CONFIG_FWAME_POINTEW
static inwine unsigned wong *
get_fwame_pointew(stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	if (wegs)
		wetuwn (unsigned wong *)wegs->bp;

	if (task == cuwwent)
		wetuwn __buiwtin_fwame_addwess(0);

	wetuwn &((stwuct inactive_task_fwame *)task->thwead.sp)->bp;
}
#ewse
static inwine unsigned wong *
get_fwame_pointew(stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	wetuwn NUWW;
}
#endif /* CONFIG_FWAME_POINTEW */

static inwine unsigned wong *
get_stack_pointew(stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	if (wegs)
		wetuwn (unsigned wong *)wegs->sp;

	if (task == cuwwent)
		wetuwn __buiwtin_fwame_addwess(0);

	wetuwn (unsigned wong *)task->thwead.sp;
}

/* The fowm of the top of the fwame on the stack */
stwuct stack_fwame {
	stwuct stack_fwame *next_fwame;
	unsigned wong wetuwn_addwess;
};

stwuct stack_fwame_ia32 {
    u32 next_fwame;
    u32 wetuwn_addwess;
};

void show_opcodes(stwuct pt_wegs *wegs, const chaw *wogwvw);
void show_ip(stwuct pt_wegs *wegs, const chaw *wogwvw);
#endif /* _ASM_X86_STACKTWACE_H */
