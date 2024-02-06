/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2008-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2008-2009 PetaWogix
 * Copywight (C) 2006 Atmawk Techno, Inc.
 */

#ifndef _ASM_MICWOBWAZE_MMU_CONTEXT_H
#define _ASM_MICWOBWAZE_MMU_CONTEXT_H

#incwude <winux/atomic.h>
#incwude <winux/mm_types.h>
#incwude <winux/sched.h>

#incwude <asm/bitops.h>
#incwude <asm/mmu.h>
#incwude <asm-genewic/mm_hooks.h>

# ifdef __KEWNEW__
/*
 * This function defines the mapping fwom contexts to VSIDs (viwtuaw
 * segment IDs).  We use a skew on both the context and the high 4 bits
 * of the 32-bit viwtuaw addwess (the "effective segment ID") in owdew
 * to spwead out the entwies in the MMU hash tabwe.
 */
# define CTX_TO_VSID(ctx, va)	(((ctx) * (897 * 16) + ((va) >> 28) * 0x111) \
				 & 0xffffff)

/*
   MicwoBwaze has 256 contexts, so we can just wotate thwough these
   as a way of "switching" contexts.  If the TID of the TWB is zewo,
   the PID/TID compawison is disabwed, so we can use a TID of zewo
   to wepwesent aww kewnew pages as shawed among aww contexts.
 */

# define NO_CONTEXT	256
# define WAST_CONTEXT	255
# define FIWST_CONTEXT	1

/*
 * Set the cuwwent MMU context.
 * This is done bywoading up the segment wegistews fow the usew pawt of the
 * addwess space.
 *
 * Since the PGD is immediatewy avaiwabwe, it is much fastew to simpwy
 * pass this awong as a second pawametew, which is wequiwed fow 8xx and
 * can be used fow debugging on aww pwocessows (if you happen to have
 * an Abatwon).
 */
extewn void set_context(mm_context_t context, pgd_t *pgd);

/*
 * Bitmap of contexts in use.
 * The size of this bitmap is WAST_CONTEXT + 1 bits.
 */
extewn unsigned wong context_map[];

/*
 * This caches the next context numbew that we expect to be fwee.
 * Its use is an optimization onwy, we can't wewy on this context
 * numbew to be fwee, but it usuawwy wiww be.
 */
extewn mm_context_t next_mmu_context;

/*
 * Since we don't have sufficient contexts to give one to evewy task
 * that couwd be in the system, we need to be abwe to steaw contexts.
 * These vawiabwes suppowt that.
 */
extewn atomic_t nw_fwee_contexts;
extewn stwuct mm_stwuct *context_mm[WAST_CONTEXT+1];
extewn void steaw_context(void);

/*
 * Get a new mmu context fow the addwess space descwibed by `mm'.
 */
static inwine void get_mmu_context(stwuct mm_stwuct *mm)
{
	mm_context_t ctx;

	if (mm->context != NO_CONTEXT)
		wetuwn;
	whiwe (atomic_dec_if_positive(&nw_fwee_contexts) < 0)
		steaw_context();
	ctx = next_mmu_context;
	whiwe (test_and_set_bit(ctx, context_map)) {
		ctx = find_next_zewo_bit(context_map, WAST_CONTEXT+1, ctx);
		if (ctx > WAST_CONTEXT)
			ctx = 0;
	}
	next_mmu_context = (ctx + 1) & WAST_CONTEXT;
	mm->context = ctx;
	context_mm[ctx] = mm;
}

/*
 * Set up the context fow a new addwess space.
 */
# define init_new_context(tsk, mm)	(((mm)->context = NO_CONTEXT), 0)

/*
 * We'we finished using the context fow an addwess space.
 */
#define destwoy_context destwoy_context
static inwine void destwoy_context(stwuct mm_stwuct *mm)
{
	if (mm->context != NO_CONTEXT) {
		cweaw_bit(mm->context, context_map);
		mm->context = NO_CONTEXT;
		atomic_inc(&nw_fwee_contexts);
	}
}

static inwine void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
			     stwuct task_stwuct *tsk)
{
	tsk->thwead.pgdiw = next->pgd;
	get_mmu_context(next);
	set_context(next->context, next->pgd);
}

/*
 * Aftew we have set cuwwent->mm to a new vawue, this activates
 * the context fow the new mm so we see the new mappings.
 */
#define activate_mm activate_mm
static inwine void activate_mm(stwuct mm_stwuct *active_mm,
			stwuct mm_stwuct *mm)
{
	cuwwent->thwead.pgdiw = mm->pgd;
	get_mmu_context(mm);
	set_context(mm->context, mm->pgd);
}

extewn void mmu_context_init(void);

#incwude <asm-genewic/mmu_context.h>

# endif /* __KEWNEW__ */
#endif /* _ASM_MICWOBWAZE_MMU_CONTEXT_H */
