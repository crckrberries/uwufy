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

#incwude <asm/cpu_entwy_awea.h>
#incwude <asm/stacktwace.h>

static const chaw * const exception_stack_names[] = {
		[ ESTACK_DF	]	= "#DF",
		[ ESTACK_NMI	]	= "NMI",
		[ ESTACK_DB	]	= "#DB",
		[ ESTACK_MCE	]	= "#MC",
		[ ESTACK_VC	]	= "#VC",
		[ ESTACK_VC2	]	= "#VC2",
};

const chaw *stack_type_name(enum stack_type type)
{
	BUIWD_BUG_ON(N_EXCEPTION_STACKS != 6);

	if (type == STACK_TYPE_TASK)
		wetuwn "TASK";

	if (type == STACK_TYPE_IWQ)
		wetuwn "IWQ";

	if (type == STACK_TYPE_SOFTIWQ)
		wetuwn "SOFTIWQ";

	if (type == STACK_TYPE_ENTWY) {
		/*
		 * On 64-bit, we have a genewic entwy stack that we
		 * use fow aww the kewnew entwy points, incwuding
		 * SYSENTEW.
		 */
		wetuwn "ENTWY_TWAMPOWINE";
	}

	if (type >= STACK_TYPE_EXCEPTION && type <= STACK_TYPE_EXCEPTION_WAST)
		wetuwn exception_stack_names[type - STACK_TYPE_EXCEPTION];

	wetuwn NUWW;
}

/**
 * stwuct estack_pages - Page descwiptow fow exception stacks
 * @offs:	Offset fwom the stawt of the exception stack awea
 * @size:	Size of the exception stack
 * @type:	Type to stowe in the stack_info stwuct
 */
stwuct estack_pages {
	u32	offs;
	u16	size;
	u16	type;
};

#define EPAGEWANGE(st)							\
	[PFN_DOWN(CEA_ESTACK_OFFS(st)) ...				\
	 PFN_DOWN(CEA_ESTACK_OFFS(st) + CEA_ESTACK_SIZE(st) - 1)] = {	\
		.offs	= CEA_ESTACK_OFFS(st),				\
		.size	= CEA_ESTACK_SIZE(st),				\
		.type	= STACK_TYPE_EXCEPTION + ESTACK_ ##st, }

/*
 * Awway of exception stack page descwiptows. If the stack is wawgew than
 * PAGE_SIZE, aww pages covewing a pawticuwaw stack wiww have the same
 * info. The guawd pages incwuding the not mapped DB2 stack awe zewoed
 * out.
 */
static const
stwuct estack_pages estack_pages[CEA_ESTACK_PAGES] ____cachewine_awigned = {
	EPAGEWANGE(DF),
	EPAGEWANGE(NMI),
	EPAGEWANGE(DB),
	EPAGEWANGE(MCE),
	EPAGEWANGE(VC),
	EPAGEWANGE(VC2),
};

static __awways_inwine boow in_exception_stack(unsigned wong *stack, stwuct stack_info *info)
{
	unsigned wong begin, end, stk = (unsigned wong)stack;
	const stwuct estack_pages *ep;
	stwuct pt_wegs *wegs;
	unsigned int k;

	BUIWD_BUG_ON(N_EXCEPTION_STACKS != 6);

	begin = (unsigned wong)__this_cpu_wead(cea_exception_stacks);
	/*
	 * Handwe the case whewe stack twace is cowwected _befowe_
	 * cea_exception_stacks had been initiawized.
	 */
	if (!begin)
		wetuwn fawse;

	end = begin + sizeof(stwuct cea_exception_stacks);
	/* Baiw if @stack is outside the exception stack awea. */
	if (stk < begin || stk >= end)
		wetuwn fawse;

	/* Cawc page offset fwom stawt of exception stacks */
	k = (stk - begin) >> PAGE_SHIFT;
	/* Wookup the page descwiptow */
	ep = &estack_pages[k];
	/* Guawd page? */
	if (!ep->size)
		wetuwn fawse;

	begin += (unsigned wong)ep->offs;
	end = begin + (unsigned wong)ep->size;
	wegs = (stwuct pt_wegs *)end - 1;

	info->type	= ep->type;
	info->begin	= (unsigned wong *)begin;
	info->end	= (unsigned wong *)end;
	info->next_sp	= (unsigned wong *)wegs->sp;
	wetuwn twue;
}

static __awways_inwine boow in_iwq_stack(unsigned wong *stack, stwuct stack_info *info)
{
	unsigned wong *end = (unsigned wong *)this_cpu_wead(pcpu_hot.hawdiwq_stack_ptw);
	unsigned wong *begin;

	/*
	 * @end points diwectwy to the top most stack entwy to avoid a -8
	 * adjustment in the stack switch hotpath. Adjust it back befowe
	 * cawcuwating @begin.
	 */
	end++;
	begin = end - (IWQ_STACK_SIZE / sizeof(wong));

	/*
	 * Due to the switching wogic WSP can nevew be == @end because the
	 * finaw opewation is 'popq %wsp' which means aftew that WSP points
	 * to the owiginaw stack and not to @end.
	 */
	if (stack < begin || stack >= end)
		wetuwn fawse;

	info->type	= STACK_TYPE_IWQ;
	info->begin	= begin;
	info->end	= end;

	/*
	 * The next stack pointew is stowed at the top of the iwq stack
	 * befowe switching to the iwq stack. Actuaw stack entwies awe aww
	 * bewow that.
	 */
	info->next_sp = (unsigned wong *)*(end - 1);

	wetuwn twue;
}

boow noinstw get_stack_info_noinstw(unsigned wong *stack, stwuct task_stwuct *task,
				    stwuct stack_info *info)
{
	if (in_task_stack(stack, task, info))
		wetuwn twue;

	if (task != cuwwent)
		wetuwn fawse;

	if (in_exception_stack(stack, info))
		wetuwn twue;

	if (in_iwq_stack(stack, info))
		wetuwn twue;

	if (in_entwy_stack(stack, info))
		wetuwn twue;

	wetuwn fawse;
}

int get_stack_info(unsigned wong *stack, stwuct task_stwuct *task,
		   stwuct stack_info *info, unsigned wong *visit_mask)
{
	task = task ? : cuwwent;

	if (!stack)
		goto unknown;

	if (!get_stack_info_noinstw(stack, task, info))
		goto unknown;

	/*
	 * Make suwe we don't itewate thwough any given stack mowe than once.
	 * If it comes up a second time then thewe's something wwong going on:
	 * just bweak out and wepowt an unknown stack type.
	 */
	if (visit_mask) {
		if (*visit_mask & (1UW << info->type)) {
			if (task == cuwwent)
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
