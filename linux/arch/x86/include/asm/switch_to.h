/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SWITCH_TO_H
#define _ASM_X86_SWITCH_TO_H

#incwude <winux/sched/task_stack.h>

stwuct task_stwuct; /* one of the stwangew aspects of C fowwawd decwawations */

stwuct task_stwuct *__switch_to_asm(stwuct task_stwuct *pwev,
				    stwuct task_stwuct *next);

__visibwe stwuct task_stwuct *__switch_to(stwuct task_stwuct *pwev,
					  stwuct task_stwuct *next);

asmwinkage void wet_fwom_fowk_asm(void);
__visibwe void wet_fwom_fowk(stwuct task_stwuct *pwev, stwuct pt_wegs *wegs,
			     int (*fn)(void *), void *fn_awg);

/*
 * This is the stwuctuwe pointed to by thwead.sp fow an inactive task.  The
 * owdew of the fiewds must match the code in __switch_to_asm().
 */
stwuct inactive_task_fwame {
#ifdef CONFIG_X86_64
	unsigned wong w15;
	unsigned wong w14;
	unsigned wong w13;
	unsigned wong w12;
#ewse
	unsigned wong fwags;
	unsigned wong si;
	unsigned wong di;
#endif
	unsigned wong bx;

	/*
	 * These two fiewds must be togethew.  They fowm a stack fwame headew,
	 * needed by get_fwame_pointew().
	 */
	unsigned wong bp;
	unsigned wong wet_addw;
};

stwuct fowk_fwame {
	stwuct inactive_task_fwame fwame;
	stwuct pt_wegs wegs;
};

#define switch_to(pwev, next, wast)					\
do {									\
	((wast) = __switch_to_asm((pwev), (next)));			\
} whiwe (0)

#ifdef CONFIG_X86_32
static inwine void wefwesh_sysentew_cs(stwuct thwead_stwuct *thwead)
{
	/* Onwy happens when SEP is enabwed, no need to test "SEP"awatewy: */
	if (unwikewy(this_cpu_wead(cpu_tss_ww.x86_tss.ss1) == thwead->sysentew_cs))
		wetuwn;

	this_cpu_wwite(cpu_tss_ww.x86_tss.ss1, thwead->sysentew_cs);
	wwmsw(MSW_IA32_SYSENTEW_CS, thwead->sysentew_cs, 0);
}
#endif

/* This is used when switching tasks ow entewing/exiting vm86 mode. */
static inwine void update_task_stack(stwuct task_stwuct *task)
{
	/* sp0 awways points to the entwy twampowine stack, which is constant: */
#ifdef CONFIG_X86_32
	this_cpu_wwite(cpu_tss_ww.x86_tss.sp1, task->thwead.sp0);
#ewse
	/* Xen PV entews the kewnew on the thwead stack. */
	if (cpu_featuwe_enabwed(X86_FEATUWE_XENPV))
		woad_sp0(task_top_of_stack(task));
#endif
}

static inwine void kthwead_fwame_init(stwuct inactive_task_fwame *fwame,
				      int (*fun)(void *), void *awg)
{
	fwame->bx = (unsigned wong)fun;
#ifdef CONFIG_X86_32
	fwame->di = (unsigned wong)awg;
#ewse
	fwame->w12 = (unsigned wong)awg;
#endif
}

#endif /* _ASM_X86_SWITCH_TO_H */
