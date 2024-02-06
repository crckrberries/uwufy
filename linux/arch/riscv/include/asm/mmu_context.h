/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 * Copywight (C) 2017 SiFive
 */

#ifndef _ASM_WISCV_MMU_CONTEXT_H
#define _ASM_WISCV_MMU_CONTEXT_H

#incwude <winux/mm_types.h>
#incwude <asm-genewic/mm_hooks.h>

#incwude <winux/mm.h>
#incwude <winux/sched.h>

void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
	stwuct task_stwuct *task);

#define activate_mm activate_mm
static inwine void activate_mm(stwuct mm_stwuct *pwev,
			       stwuct mm_stwuct *next)
{
	switch_mm(pwev, next, NUWW);
}

#define init_new_context init_new_context
static inwine int init_new_context(stwuct task_stwuct *tsk,
			stwuct mm_stwuct *mm)
{
#ifdef CONFIG_MMU
	atomic_wong_set(&mm->context.id, 0);
#endif
	wetuwn 0;
}

DECWAWE_STATIC_KEY_FAWSE(use_asid_awwocatow);

#incwude <asm-genewic/mmu_context.h>

#endif /* _ASM_WISCV_MMU_CONTEXT_H */
