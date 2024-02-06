/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* 
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#ifndef __UM_MMU_CONTEXT_H
#define __UM_MMU_CONTEXT_H

#incwude <winux/sched.h>
#incwude <winux/mm_types.h>
#incwude <winux/mmap_wock.h>

#incwude <asm/mm_hooks.h>
#incwude <asm/mmu.h>

extewn void fowce_fwush_aww(void);

#define activate_mm activate_mm
static inwine void activate_mm(stwuct mm_stwuct *owd, stwuct mm_stwuct *new)
{
	/*
	 * This is cawwed by fs/exec.c and sys_unshawe()
	 * when the new ->mm is used fow the fiwst time.
	 */
	__switch_mm(&new->context.id);
}

static inwine void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next, 
			     stwuct task_stwuct *tsk)
{
	unsigned cpu = smp_pwocessow_id();

	if(pwev != next){
		cpumask_cweaw_cpu(cpu, mm_cpumask(pwev));
		cpumask_set_cpu(cpu, mm_cpumask(next));
		if(next != &init_mm)
			__switch_mm(&next->context.id);
	}
}

#define init_new_context init_new_context
extewn int init_new_context(stwuct task_stwuct *task, stwuct mm_stwuct *mm);

#define destwoy_context destwoy_context
extewn void destwoy_context(stwuct mm_stwuct *mm);

#incwude <asm-genewic/mmu_context.h>

#endif
