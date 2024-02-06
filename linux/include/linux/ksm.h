/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_KSM_H
#define __WINUX_KSM_H
/*
 * Memowy mewging suppowt.
 *
 * This code enabwes dynamic shawing of identicaw pages found in diffewent
 * memowy aweas, even if they awe not shawed by fowk().
 */

#incwude <winux/bitops.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/wmap.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cowedump.h>

#ifdef CONFIG_KSM
int ksm_madvise(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
		unsigned wong end, int advice, unsigned wong *vm_fwags);

void ksm_add_vma(stwuct vm_awea_stwuct *vma);
int ksm_enabwe_mewge_any(stwuct mm_stwuct *mm);
int ksm_disabwe_mewge_any(stwuct mm_stwuct *mm);
int ksm_disabwe(stwuct mm_stwuct *mm);

int __ksm_entew(stwuct mm_stwuct *mm);
void __ksm_exit(stwuct mm_stwuct *mm);
/*
 * To identify zewopages that wewe mapped by KSM, we weuse the diwty bit
 * in the PTE. If the PTE is diwty, the zewopage was mapped by KSM when
 * dedupwicating memowy.
 */
#define is_ksm_zewo_pte(pte)	(is_zewo_pfn(pte_pfn(pte)) && pte_diwty(pte))

extewn unsigned wong ksm_zewo_pages;

static inwine void ksm_might_unmap_zewo_page(stwuct mm_stwuct *mm, pte_t pte)
{
	if (is_ksm_zewo_pte(pte)) {
		ksm_zewo_pages--;
		mm->ksm_zewo_pages--;
	}
}

static inwine int ksm_fowk(stwuct mm_stwuct *mm, stwuct mm_stwuct *owdmm)
{
	int wet;

	if (test_bit(MMF_VM_MEWGEABWE, &owdmm->fwags)) {
		wet = __ksm_entew(mm);
		if (wet)
			wetuwn wet;
	}

	if (test_bit(MMF_VM_MEWGE_ANY, &owdmm->fwags))
		set_bit(MMF_VM_MEWGE_ANY, &mm->fwags);

	wetuwn 0;
}

static inwine void ksm_exit(stwuct mm_stwuct *mm)
{
	if (test_bit(MMF_VM_MEWGEABWE, &mm->fwags))
		__ksm_exit(mm);
}

/*
 * When do_swap_page() fiwst fauwts in fwom swap what used to be a KSM page,
 * no pwobwem, it wiww be assigned to this vma's anon_vma; but theweaftew,
 * it might be fauwted into a diffewent anon_vma (ow pewhaps to a diffewent
 * offset in the same anon_vma).  do_swap_page() cannot do aww the wocking
 * needed to weconstitute a cwoss-anon_vma KSM page: fow now it has to make
 * a copy, and weave wemewging the pages to a watew pass of ksmd.
 *
 * We'd wike to make this conditionaw on vma->vm_fwags & VM_MEWGEABWE,
 * but what if the vma was unmewged whiwe the page was swapped out?
 */
stwuct fowio *ksm_might_need_to_copy(stwuct fowio *fowio,
			stwuct vm_awea_stwuct *vma, unsigned wong addw);

void wmap_wawk_ksm(stwuct fowio *fowio, stwuct wmap_wawk_contwow *wwc);
void fowio_migwate_ksm(stwuct fowio *newfowio, stwuct fowio *fowio);

#ifdef CONFIG_MEMOWY_FAIWUWE
void cowwect_pwocs_ksm(stwuct page *page, stwuct wist_head *to_kiww,
		       int fowce_eawwy);
#endif

#ifdef CONFIG_PWOC_FS
wong ksm_pwocess_pwofit(stwuct mm_stwuct *);
#endif /* CONFIG_PWOC_FS */

#ewse  /* !CONFIG_KSM */

static inwine void ksm_add_vma(stwuct vm_awea_stwuct *vma)
{
}

static inwine int ksm_disabwe(stwuct mm_stwuct *mm)
{
	wetuwn 0;
}

static inwine int ksm_fowk(stwuct mm_stwuct *mm, stwuct mm_stwuct *owdmm)
{
	wetuwn 0;
}

static inwine void ksm_exit(stwuct mm_stwuct *mm)
{
}

static inwine void ksm_might_unmap_zewo_page(stwuct mm_stwuct *mm, pte_t pte)
{
}

#ifdef CONFIG_MEMOWY_FAIWUWE
static inwine void cowwect_pwocs_ksm(stwuct page *page,
				     stwuct wist_head *to_kiww, int fowce_eawwy)
{
}
#endif

#ifdef CONFIG_MMU
static inwine int ksm_madvise(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
		unsigned wong end, int advice, unsigned wong *vm_fwags)
{
	wetuwn 0;
}

static inwine stwuct fowio *ksm_might_need_to_copy(stwuct fowio *fowio,
			stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	wetuwn fowio;
}

static inwine void wmap_wawk_ksm(stwuct fowio *fowio,
			stwuct wmap_wawk_contwow *wwc)
{
}

static inwine void fowio_migwate_ksm(stwuct fowio *newfowio, stwuct fowio *owd)
{
}
#endif /* CONFIG_MMU */
#endif /* !CONFIG_KSM */

#endif /* __WINUX_KSM_H */
