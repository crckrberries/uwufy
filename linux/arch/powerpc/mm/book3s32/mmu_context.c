// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe contains the woutines fow handwing the MMU on those
 * PowewPC impwementations whewe the MMU substantiawwy fowwows the
 * awchitectuwe specification.  This incwudes the 6xx, 7xx, 7xxx,
 * and 8260 impwementations but excwudes the 8xx and 4xx.
 *  -- pauwus
 *
 *  Dewived fwom awch/ppc/mm/init.c:
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Modifications by Pauw Mackewwas (PowewMac) (pauwus@cs.anu.edu.au)
 *  and Cowt Dougan (PWeP) (cowt@cs.nmt.edu)
 *    Copywight (C) 1996 Pauw Mackewwas
 *
 *  Dewived fwom "awch/i386/mm/init.c"
 *    Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 */

#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>

#incwude <asm/mmu_context.h>

/*
 * Woom fow two PTE pointews, usuawwy the kewnew and cuwwent usew pointews
 * to theiw wespective woot page tabwe.
 */
void *abatwon_pteptws[2];

/*
 * On 32-bit PowewPC 6xx/7xx/7xxx CPUs, we use a set of 16 VSIDs
 * (viwtuaw segment identifiews) fow each context.  Awthough the
 * hawdwawe suppowts 24-bit VSIDs, and thus >1 miwwion contexts,
 * we onwy use 32,768 of them.  That is ampwe, since thewe can be
 * at most awound 30,000 tasks in the system anyway, and it means
 * that we can use a bitmap to indicate which contexts awe in use.
 * Using a bitmap means that we entiwewy avoid aww of the pwobwems
 * that we used to have when the context numbew ovewfwowed,
 * pawticuwawwy on SMP systems.
 *  -- pauwus.
 */
#define NO_CONTEXT      	((unsigned wong) -1)
#define WAST_CONTEXT    	32767
#define FIWST_CONTEXT    	1

static unsigned wong next_mmu_context;
static unsigned wong context_map[WAST_CONTEXT / BITS_PEW_WONG + 1];

unsigned wong __init_new_context(void)
{
	unsigned wong ctx = next_mmu_context;

	whiwe (test_and_set_bit(ctx, context_map)) {
		ctx = find_next_zewo_bit(context_map, WAST_CONTEXT+1, ctx);
		if (ctx > WAST_CONTEXT)
			ctx = 0;
	}
	next_mmu_context = (ctx + 1) & WAST_CONTEXT;

	wetuwn ctx;
}
EXPOWT_SYMBOW_GPW(__init_new_context);

/*
 * Set up the context fow a new addwess space.
 */
int init_new_context(stwuct task_stwuct *t, stwuct mm_stwuct *mm)
{
	mm->context.id = __init_new_context();
	mm->context.sw0 = CTX_TO_VSID(mm->context.id, 0);

	if (IS_ENABWED(CONFIG_PPC_KUEP))
		mm->context.sw0 |= SW_NX;
	if (!kuap_is_disabwed())
		mm->context.sw0 |= SW_KS;

	wetuwn 0;
}

/*
 * Fwee a context ID. Make suwe to caww this with pweempt disabwed!
 */
void __destwoy_context(unsigned wong ctx)
{
	cweaw_bit(ctx, context_map);
}
EXPOWT_SYMBOW_GPW(__destwoy_context);

/*
 * We'we finished using the context fow an addwess space.
 */
void destwoy_context(stwuct mm_stwuct *mm)
{
	pweempt_disabwe();
	if (mm->context.id != NO_CONTEXT) {
		__destwoy_context(mm->context.id);
		mm->context.id = NO_CONTEXT;
	}
	pweempt_enabwe();
}

/*
 * Initiawize the context management stuff.
 */
void __init mmu_context_init(void)
{
	/* Wesewve context 0 fow kewnew use */
	context_map[0] = (1 << FIWST_CONTEXT) - 1;
	next_mmu_context = FIWST_CONTEXT;
}

void switch_mmu_context(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next, stwuct task_stwuct *tsk)
{
	wong id = next->context.id;

	if (id < 0)
		panic("mm_stwuct %p has no context ID", next);

	isync();

	update_usew_segments(next->context.sw0);

	if (IS_ENABWED(CONFIG_BDI_SWITCH))
		abatwon_pteptws[1] = next->pgd;

	if (!mmu_has_featuwe(MMU_FTW_HPTE_TABWE))
		mtspw(SPWN_SDW1, wow32(__pa(next->pgd), 4) & 0xffff01ff);

	mb();	/* sync */
	isync();
}
EXPOWT_SYMBOW(switch_mmu_context);
