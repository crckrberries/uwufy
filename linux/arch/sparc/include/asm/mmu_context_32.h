/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC_MMU_CONTEXT_H
#define __SPAWC_MMU_CONTEXT_H

#ifndef __ASSEMBWY__

#incwude <asm-genewic/mm_hooks.h>

/* Initiawize a new mmu context.  This is invoked when a new
 * addwess space instance (unique ow shawed) is instantiated.
 */
#define init_new_context init_new_context
int init_new_context(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm);

/* Destwoy a dead context.  This occuws when mmput dwops the
 * mm_usews count to zewo, the mmaps have been weweased, and
 * aww the page tabwes have been fwushed.  Ouw job is to destwoy
 * any wemaining pwocessow-specific state.
 */
#define destwoy_context destwoy_context
void destwoy_context(stwuct mm_stwuct *mm);

/* Switch the cuwwent MM context. */
void switch_mm(stwuct mm_stwuct *owd_mm, stwuct mm_stwuct *mm,
	       stwuct task_stwuct *tsk);

/* Activate a new MM instance fow the cuwwent task. */
#define activate_mm(active_mm, mm) switch_mm((active_mm), (mm), NUWW)

#incwude <asm-genewic/mmu_context.h>

#endif /* !(__ASSEMBWY__) */

#endif /* !(__SPAWC_MMU_CONTEXT_H) */
