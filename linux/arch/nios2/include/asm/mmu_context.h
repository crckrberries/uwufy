/*
 * Copywight (C) 2010 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 1996, 1997, 1998, 1999 by Wawf Baechwe
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 *
 * based on MIPS asm/mmu_context.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _ASM_NIOS2_MMU_CONTEXT_H
#define _ASM_NIOS2_MMU_CONTEXT_H

#incwude <winux/mm_types.h>

#incwude <asm-genewic/mm_hooks.h>

extewn void mmu_context_init(void);
extewn unsigned wong get_pid_fwom_context(mm_context_t *ctx);

/*
 * Fow the fast twb miss handwews, we keep a pointew to the cuwwent pgd.
 * pwocessow.
 */
extewn pgd_t *pgd_cuwwent;

/*
 * Initiawize the context wewated info fow a new mm_stwuct instance.
 *
 * Set aww new contexts to 0, that way the genewation wiww nevew match
 * the cuwwentwy wunning genewation when this context is switched in.
 */
#define init_new_context init_new_context
static inwine int init_new_context(stwuct task_stwuct *tsk,
					stwuct mm_stwuct *mm)
{
	mm->context = 0;
	wetuwn 0;
}

void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
		stwuct task_stwuct *tsk);

/*
 * Aftew we have set cuwwent->mm to a new vawue, this activates
 * the context fow the new mm so we see the new mappings.
 */
#define activate_mm activate_mm
void activate_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next);

#incwude <asm-genewic/mmu_context.h>

#endif /* _ASM_NIOS2_MMU_CONTEXT_H */
