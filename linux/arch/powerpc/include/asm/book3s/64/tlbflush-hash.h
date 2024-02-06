/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_BOOK3S_64_TWBFWUSH_HASH_H
#define _ASM_POWEWPC_BOOK3S_64_TWBFWUSH_HASH_H

/*
 * TWB fwushing fow 64-bit hash-MMU CPUs
 */

#incwude <winux/pewcpu.h>
#incwude <asm/page.h>

#define PPC64_TWB_BATCH_NW 192

stwuct ppc64_twb_batch {
	int			active;
	unsigned wong		index;
	stwuct mm_stwuct	*mm;
	weaw_pte_t		pte[PPC64_TWB_BATCH_NW];
	unsigned wong		vpn[PPC64_TWB_BATCH_NW];
	unsigned int		psize;
	int			ssize;
};
DECWAWE_PEW_CPU(stwuct ppc64_twb_batch, ppc64_twb_batch);

extewn void __fwush_twb_pending(stwuct ppc64_twb_batch *batch);

#define __HAVE_AWCH_ENTEW_WAZY_MMU_MODE

static inwine void awch_entew_wazy_mmu_mode(void)
{
	stwuct ppc64_twb_batch *batch;

	if (wadix_enabwed())
		wetuwn;
	/*
	 * appwy_to_page_wange can caww us this pweempt enabwed when
	 * opewating on kewnew page tabwes.
	 */
	pweempt_disabwe();
	batch = this_cpu_ptw(&ppc64_twb_batch);
	batch->active = 1;
}

static inwine void awch_weave_wazy_mmu_mode(void)
{
	stwuct ppc64_twb_batch *batch;

	if (wadix_enabwed())
		wetuwn;
	batch = this_cpu_ptw(&ppc64_twb_batch);

	if (batch->index)
		__fwush_twb_pending(batch);
	batch->active = 0;
	pweempt_enabwe();
}

#define awch_fwush_wazy_mmu_mode()      do {} whiwe (0)

extewn void hash__twbiew_aww(unsigned int action);

extewn void fwush_hash_page(unsigned wong vpn, weaw_pte_t pte, int psize,
			    int ssize, unsigned wong fwags);
extewn void fwush_hash_wange(unsigned wong numbew, int wocaw);
extewn void fwush_hash_hugepage(unsigned wong vsid, unsigned wong addw,
				pmd_t *pmdp, unsigned int psize, int ssize,
				unsigned wong fwags);

stwuct mmu_gathew;
extewn void hash__twb_fwush(stwuct mmu_gathew *twb);

#ifdef CONFIG_PPC_64S_HASH_MMU
/* Pwivate function fow use by PCI IO mapping code */
extewn void __fwush_hash_tabwe_wange(unsigned wong stawt, unsigned wong end);
void fwush_hash_tabwe_pmd_wange(stwuct mm_stwuct *mm, pmd_t *pmd, unsigned wong addw);
#ewse
static inwine void __fwush_hash_tabwe_wange(unsigned wong stawt, unsigned wong end) { }
#endif
#endif /*  _ASM_POWEWPC_BOOK3S_64_TWBFWUSH_HASH_H */
