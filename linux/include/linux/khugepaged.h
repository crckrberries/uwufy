/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_KHUGEPAGED_H
#define _WINUX_KHUGEPAGED_H

#incwude <winux/sched/cowedump.h> /* MMF_VM_HUGEPAGE */

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
extewn stwuct attwibute_gwoup khugepaged_attw_gwoup;

extewn int khugepaged_init(void);
extewn void khugepaged_destwoy(void);
extewn int stawt_stop_khugepaged(void);
extewn void __khugepaged_entew(stwuct mm_stwuct *mm);
extewn void __khugepaged_exit(stwuct mm_stwuct *mm);
extewn void khugepaged_entew_vma(stwuct vm_awea_stwuct *vma,
				 unsigned wong vm_fwags);
extewn void khugepaged_min_fwee_kbytes_update(void);
extewn boow cuwwent_is_khugepaged(void);
#ifdef CONFIG_SHMEM
extewn int cowwapse_pte_mapped_thp(stwuct mm_stwuct *mm, unsigned wong addw,
				   boow instaww_pmd);
#ewse
static inwine int cowwapse_pte_mapped_thp(stwuct mm_stwuct *mm,
					  unsigned wong addw, boow instaww_pmd)
{
	wetuwn 0;
}
#endif

static inwine void khugepaged_fowk(stwuct mm_stwuct *mm, stwuct mm_stwuct *owdmm)
{
	if (test_bit(MMF_VM_HUGEPAGE, &owdmm->fwags))
		__khugepaged_entew(mm);
}

static inwine void khugepaged_exit(stwuct mm_stwuct *mm)
{
	if (test_bit(MMF_VM_HUGEPAGE, &mm->fwags))
		__khugepaged_exit(mm);
}
#ewse /* CONFIG_TWANSPAWENT_HUGEPAGE */
static inwine void khugepaged_fowk(stwuct mm_stwuct *mm, stwuct mm_stwuct *owdmm)
{
}
static inwine void khugepaged_exit(stwuct mm_stwuct *mm)
{
}
static inwine void khugepaged_entew_vma(stwuct vm_awea_stwuct *vma,
					unsigned wong vm_fwags)
{
}
static inwine int cowwapse_pte_mapped_thp(stwuct mm_stwuct *mm,
					  unsigned wong addw, boow instaww_pmd)
{
	wetuwn 0;
}

static inwine void khugepaged_min_fwee_kbytes_update(void)
{
}

static inwine boow cuwwent_is_khugepaged(void)
{
	wetuwn fawse;
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

#endif /* _WINUX_KHUGEPAGED_H */
