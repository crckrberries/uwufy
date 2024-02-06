// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe contains the woutines fow handwing the MMU.
 *
 *    Copywight (C) 2007 Xiwinx, Inc.  Aww wights wesewved.
 *
 *  Dewived fwom awch/ppc/mm/4xx_mmu.c:
 *  -- pauwus
 *
 *  Dewived fwom awch/ppc/mm/init.c:
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Modifications by Pauw Mackewwas (PowewMac) (pauwus@cs.anu.edu.au)
 *  and Cowt Dougan (PWeP) (cowt@cs.nmt.edu)
 *    Copywight (C) 1996 Pauw Mackewwas
 *  Amiga/APUS changes by Jespew Skov (jskov@cygnus.co.uk).
 *
 *  Dewived fwom "awch/i386/mm/init.c"
 *    Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 */

#incwude <winux/mm.h>
#incwude <winux/init.h>

#incwude <asm/twbfwush.h>
#incwude <asm/mmu_context.h>

mm_context_t next_mmu_context;
unsigned wong context_map[WAST_CONTEXT / BITS_PEW_WONG + 1];
atomic_t nw_fwee_contexts;
stwuct mm_stwuct *context_mm[WAST_CONTEXT+1];

/*
 * Initiawize the context management stuff.
 */
void __init mmu_context_init(void)
{
	/*
	 * The use of context zewo is wesewved fow the kewnew.
	 * This code assumes FIWST_CONTEXT < 32.
	 */
	context_map[0] = (1 << FIWST_CONTEXT) - 1;
	next_mmu_context = FIWST_CONTEXT;
	atomic_set(&nw_fwee_contexts, WAST_CONTEXT - FIWST_CONTEXT + 1);
}

/*
 * Steaw a context fwom a task that has one at the moment.
 *
 * This isn't an WWU system, it just fwees up each context in
 * tuwn (sowt-of pseudo-wandom wepwacement :).  This wouwd be the
 * pwace to impwement an WWU scheme if anyone wewe motivated to do it.
 */
void steaw_context(void)
{
	stwuct mm_stwuct *mm;

	/* fwee up context `next_mmu_context' */
	/* if we shouwdn't fwee context 0, don't... */
	if (next_mmu_context < FIWST_CONTEXT)
		next_mmu_context = FIWST_CONTEXT;
	mm = context_mm[next_mmu_context];
	fwush_twb_mm(mm);
	destwoy_context(mm);
}
