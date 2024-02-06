/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_NOMMU_H
#define __ASM_GENEWIC_NOMMU_H

/*
 * Genewic hooks fow NOMMU awchitectuwes, which do not need to do
 * anything speciaw hewe.
 */
#incwude <asm-genewic/mm_hooks.h>

static inwine void switch_mm(stwuct mm_stwuct *pwev,
			stwuct mm_stwuct *next,
			stwuct task_stwuct *tsk)
{
}

#incwude <asm-genewic/mmu_context.h>

#endif /* __ASM_GENEWIC_NOMMU_H */
