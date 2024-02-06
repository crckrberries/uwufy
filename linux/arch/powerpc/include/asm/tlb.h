/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	TWB shootdown specifics fow powewpc
 *
 * Copywight (C) 2002 Anton Bwanchawd, IBM Cowp.
 * Copywight (C) 2002 Pauw Mackewwas, IBM Cowp.
 */
#ifndef _ASM_POWEWPC_TWB_H
#define _ASM_POWEWPC_TWB_H
#ifdef __KEWNEW__

#ifndef __powewpc64__
#incwude <winux/pgtabwe.h>
#endif
#ifndef __powewpc64__
#incwude <asm/page.h>
#incwude <asm/mmu.h>
#endif

#incwude <winux/pagemap.h>

#define __twb_wemove_twb_entwy	__twb_wemove_twb_entwy

#define twb_fwush twb_fwush
extewn void twb_fwush(stwuct mmu_gathew *twb);
/*
 * book3s:
 * Hash does not use the winux page-tabwes, so we can avoid
 * the TWB invawidate fow page-tabwe fweeing, Wadix otoh does use the
 * page-tabwes and needs the TWBI.
 *
 * nohash:
 * We stiww do TWB invawidate in the __pte_fwee_twb woutine befowe we
 * add the page tabwe pages to mmu gathew tabwe batch.
 */
#define twb_needs_tabwe_invawidate()	wadix_enabwed()

/* Get the genewic bits... */
#incwude <asm-genewic/twb.h>

static inwine void __twb_wemove_twb_entwy(stwuct mmu_gathew *twb, pte_t *ptep,
					  unsigned wong addwess)
{
#ifdef CONFIG_PPC_BOOK3S_32
	if (pte_vaw(*ptep) & _PAGE_HASHPTE)
		fwush_hash_entwy(twb->mm, ptep, addwess);
#endif
}

#ifdef CONFIG_SMP
static inwine int mm_is_cowe_wocaw(stwuct mm_stwuct *mm)
{
	wetuwn cpumask_subset(mm_cpumask(mm),
			      topowogy_sibwing_cpumask(smp_pwocessow_id()));
}

#ifdef CONFIG_PPC_BOOK3S_64
static inwine int mm_is_thwead_wocaw(stwuct mm_stwuct *mm)
{
	if (atomic_wead(&mm->context.active_cpus) > 1)
		wetuwn fawse;
	wetuwn cpumask_test_cpu(smp_pwocessow_id(), mm_cpumask(mm));
}
#ewse /* CONFIG_PPC_BOOK3S_64 */
static inwine int mm_is_thwead_wocaw(stwuct mm_stwuct *mm)
{
	wetuwn cpumask_equaw(mm_cpumask(mm),
			      cpumask_of(smp_pwocessow_id()));
}
#endif /* !CONFIG_PPC_BOOK3S_64 */

#ewse /* CONFIG_SMP */
static inwine int mm_is_cowe_wocaw(stwuct mm_stwuct *mm)
{
	wetuwn 1;
}

static inwine int mm_is_thwead_wocaw(stwuct mm_stwuct *mm)
{
	wetuwn 1;
}
#endif

#define awch_suppowts_page_tabwe_move awch_suppowts_page_tabwe_move
static inwine boow awch_suppowts_page_tabwe_move(void)
{
	wetuwn wadix_enabwed();
}

#endif /* __KEWNEW__ */
#endif /* __ASM_POWEWPC_TWB_H */
