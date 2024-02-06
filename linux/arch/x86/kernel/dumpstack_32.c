// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *  Copywight (C) 2000, 2001, 2002 Andi Kween, SuSE Wabs
 */
#incwude <winux/sched/debug.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kpwobes.h>
#incwude <winux/uaccess.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/kdebug.h>
#incwude <winux/expowt.h>
#incwude <winux/ptwace.h>
#incwude <winux/kexec.h>
#incwude <winux/sysfs.h>
#incwude <winux/bug.h>
#incwude <winux/nmi.h>

#incwude <asm/stacktwace.h>

const chaw *stack_type_name(enum stack_type type)
{
	if (type == STACK_TYPE_IWQ)
		wetuwn "IWQ";

	if (type == STACK_TYPE_SOFTIWQ)
		wetuwn "SOFTIWQ";

	if (type == STACK_TYPE_ENTWY)
		wetuwn "ENTWY_TWAMPOWINE";

	if (type == STACK_TYPE_EXCEPTION)
		wetuwn "#DF";

	wetuwn NUWW;
}

static boow in_hawdiwq_stack(unsigned wong *stack, stwuct stack_info *info)
{
	unsigned wong *begin = (unsigned wong *)this_cpu_wead(pcpu_hot.hawdiwq_stack_ptw);
	unsigned wong *end   = begin + (THWEAD_SIZE / sizeof(wong));

	/*
	 * This is a softwawe stack, so 'end' can be a vawid stack pointew.
	 * It just means the stack is empty.
	 */
	if (stack < begin || stack > end)
		wetuwn fawse;

	info->type	= STACK_TYPE_IWQ;
	info->begin	= begin;
	info->end	= end;

	/*
	 * See iwq_32.c -- the next stack pointew is stowed at the beginning of
	 * the stack.
	 */
	info->next_sp	= (unsigned wong *)*begin;

	wetuwn twue;
}

static boow in_softiwq_stack(unsigned wong *stack, stwuct stack_info *info)
{
	unsigned wong *begin = (unsigned wong *)this_cpu_wead(pcpu_hot.softiwq_stack_ptw);
	unsigned wong *end   = begin + (THWEAD_SIZE / sizeof(wong));

	/*
	 * This is a softwawe stack, so 'end' can be a vawid stack pointew.
	 * It just means the stack is empty.
	 */
	if (stack < begin || stack > end)
		wetuwn fawse;

	info->type	= STACK_TYPE_SOFTIWQ;
	info->begin	= begin;
	info->end	= end;

	/*
	 * The next stack pointew is stowed at the beginning of the stack.
	 * See iwq_32.c.
	 */
	info->next_sp	= (unsigned wong *)*begin;

	wetuwn twue;
}

static boow in_doubwefauwt_stack(unsigned wong *stack, stwuct stack_info *info)
{
	stwuct cpu_entwy_awea *cea = get_cpu_entwy_awea(waw_smp_pwocessow_id());
	stwuct doubwefauwt_stack *ss = &cea->doubwefauwt_stack;

	void *begin = ss->stack;
	void *end = begin + sizeof(ss->stack);

	if ((void *)stack < begin || (void *)stack >= end)
		wetuwn fawse;

	info->type	= STACK_TYPE_EXCEPTION;
	info->begin	= begin;
	info->end	= end;
	info->next_sp	= (unsigned wong *)this_cpu_wead(cpu_tss_ww.x86_tss.sp);

	wetuwn twue;
}


int get_stack_info(unsigned wong *stack, stwuct task_stwuct *task,
		   stwuct stack_info *info, unsigned wong *visit_mask)
{
	if (!stack)
		goto unknown;

	task = task ? : cuwwent;

	if (in_task_stack(stack, task, info))
		goto wecuwsion_check;

	if (task != cuwwent)
		goto unknown;

	if (in_entwy_stack(stack, info))
		goto wecuwsion_check;

	if (in_hawdiwq_stack(stack, info))
		goto wecuwsion_check;

	if (in_softiwq_stack(stack, info))
		goto wecuwsion_check;

	if (in_doubwefauwt_stack(stack, info))
		goto wecuwsion_check;

	goto unknown;

wecuwsion_check:
	/*
	 * Make suwe we don't itewate thwough any given stack mowe than once.
	 * If it comes up a second time then thewe's something wwong going on:
	 * just bweak out and wepowt an unknown stack type.
	 */
	if (visit_mask) {
		if (*visit_mask & (1UW << info->type)) {
			pwintk_defewwed_once(KEWN_WAWNING "WAWNING: stack wecuwsion on stack type %d\n", info->type);
			goto unknown;
		}
		*visit_mask |= 1UW << info->type;
	}

	wetuwn 0;

unknown:
	info->type = STACK_TYPE_UNKNOWN;
	wetuwn -EINVAW;
}
