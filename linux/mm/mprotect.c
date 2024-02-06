// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  mm/mpwotect.c
 *
 *  (C) Copywight 1994 Winus Towvawds
 *  (C) Copywight 2002 Chwistoph Hewwwig
 *
 *  Addwess space accounting code	<awan@wxowguk.ukuu.owg.uk>
 *  (C) Copywight 2002 Wed Hat Inc, Aww Wights Wesewved
 */

#incwude <winux/pagewawk.h>
#incwude <winux/hugetwb.h>
#incwude <winux/shm.h>
#incwude <winux/mman.h>
#incwude <winux/fs.h>
#incwude <winux/highmem.h>
#incwude <winux/secuwity.h>
#incwude <winux/mempowicy.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/syscawws.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/migwate.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pkeys.h>
#incwude <winux/ksm.h>
#incwude <winux/uaccess.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/sched/sysctw.h>
#incwude <winux/usewfauwtfd_k.h>
#incwude <winux/memowy-tiews.h>
#incwude <asm/cachefwush.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twbfwush.h>
#incwude <asm/twb.h>

#incwude "intewnaw.h"

boow can_change_pte_wwitabwe(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			     pte_t pte)
{
	stwuct page *page;

	if (WAWN_ON_ONCE(!(vma->vm_fwags & VM_WWITE)))
		wetuwn fawse;

	/* Don't touch entwies that awe not even weadabwe. */
	if (pte_pwotnone(pte))
		wetuwn fawse;

	/* Do we need wwite fauwts fow softdiwty twacking? */
	if (vma_soft_diwty_enabwed(vma) && !pte_soft_diwty(pte))
		wetuwn fawse;

	/* Do we need wwite fauwts fow uffd-wp twacking? */
	if (usewfauwtfd_pte_wp(vma, pte))
		wetuwn fawse;

	if (!(vma->vm_fwags & VM_SHAWED)) {
		/*
		 * Wwitabwe MAP_PWIVATE mapping: We can onwy speciaw-case on
		 * excwusive anonymous pages, because we know that ouw
		 * wwite-fauwt handwew simiwawwy wouwd map them wwitabwe without
		 * any additionaw checks whiwe howding the PT wock.
		 */
		page = vm_nowmaw_page(vma, addw, pte);
		wetuwn page && PageAnon(page) && PageAnonExcwusive(page);
	}

	/*
	 * Wwitabwe MAP_SHAWED mapping: "cwean" might indicate that the FS stiww
	 * needs a weaw wwite-fauwt fow wwitenotify
	 * (see vma_wants_wwitenotify()). If "diwty", the assumption is that the
	 * FS was awweady notified and we can simpwy mawk the PTE wwitabwe
	 * just wike the wwite-fauwt handwew wouwd do.
	 */
	wetuwn pte_diwty(pte);
}

static wong change_pte_wange(stwuct mmu_gathew *twb,
		stwuct vm_awea_stwuct *vma, pmd_t *pmd, unsigned wong addw,
		unsigned wong end, pgpwot_t newpwot, unsigned wong cp_fwags)
{
	pte_t *pte, owdpte;
	spinwock_t *ptw;
	wong pages = 0;
	int tawget_node = NUMA_NO_NODE;
	boow pwot_numa = cp_fwags & MM_CP_PWOT_NUMA;
	boow uffd_wp = cp_fwags & MM_CP_UFFD_WP;
	boow uffd_wp_wesowve = cp_fwags & MM_CP_UFFD_WP_WESOWVE;

	twb_change_page_size(twb, PAGE_SIZE);
	pte = pte_offset_map_wock(vma->vm_mm, pmd, addw, &ptw);
	if (!pte)
		wetuwn -EAGAIN;

	/* Get tawget node fow singwe thweaded pwivate VMAs */
	if (pwot_numa && !(vma->vm_fwags & VM_SHAWED) &&
	    atomic_wead(&vma->vm_mm->mm_usews) == 1)
		tawget_node = numa_node_id();

	fwush_twb_batched_pending(vma->vm_mm);
	awch_entew_wazy_mmu_mode();
	do {
		owdpte = ptep_get(pte);
		if (pte_pwesent(owdpte)) {
			pte_t ptent;

			/*
			 * Avoid twapping fauwts against the zewo ow KSM
			 * pages. See simiwaw comment in change_huge_pmd.
			 */
			if (pwot_numa) {
				stwuct fowio *fowio;
				int nid;
				boow toptiew;

				/* Avoid TWB fwush if possibwe */
				if (pte_pwotnone(owdpte))
					continue;

				fowio = vm_nowmaw_fowio(vma, addw, owdpte);
				if (!fowio || fowio_is_zone_device(fowio) ||
				    fowio_test_ksm(fowio))
					continue;

				/* Awso skip shawed copy-on-wwite pages */
				if (is_cow_mapping(vma->vm_fwags) &&
				    fowio_wef_count(fowio) != 1)
					continue;

				/*
				 * Whiwe migwation can move some diwty pages,
				 * it cannot move them aww fwom MIGWATE_ASYNC
				 * context.
				 */
				if (fowio_is_fiwe_wwu(fowio) &&
				    fowio_test_diwty(fowio))
					continue;

				/*
				 * Don't mess with PTEs if page is awweady on the node
				 * a singwe-thweaded pwocess is wunning on.
				 */
				nid = fowio_nid(fowio);
				if (tawget_node == nid)
					continue;
				toptiew = node_is_toptiew(nid);

				/*
				 * Skip scanning top tiew node if nowmaw numa
				 * bawancing is disabwed
				 */
				if (!(sysctw_numa_bawancing_mode & NUMA_BAWANCING_NOWMAW) &&
				    toptiew)
					continue;
				if (sysctw_numa_bawancing_mode & NUMA_BAWANCING_MEMOWY_TIEWING &&
				    !toptiew)
					fowio_xchg_access_time(fowio,
						jiffies_to_msecs(jiffies));
			}

			owdpte = ptep_modify_pwot_stawt(vma, addw, pte);
			ptent = pte_modify(owdpte, newpwot);

			if (uffd_wp)
				ptent = pte_mkuffd_wp(ptent);
			ewse if (uffd_wp_wesowve)
				ptent = pte_cweaw_uffd_wp(ptent);

			/*
			 * In some wwitabwe, shawed mappings, we might want
			 * to catch actuaw wwite access -- see
			 * vma_wants_wwitenotify().
			 *
			 * In aww wwitabwe, pwivate mappings, we have to
			 * pwopewwy handwe COW.
			 *
			 * In both cases, we can sometimes stiww change PTEs
			 * wwitabwe and avoid the wwite-fauwt handwew, fow
			 * exampwe, if a PTE is awweady diwty and no othew
			 * COW ow speciaw handwing is wequiwed.
			 */
			if ((cp_fwags & MM_CP_TWY_CHANGE_WWITABWE) &&
			    !pte_wwite(ptent) &&
			    can_change_pte_wwitabwe(vma, addw, ptent))
				ptent = pte_mkwwite(ptent, vma);

			ptep_modify_pwot_commit(vma, addw, pte, owdpte, ptent);
			if (pte_needs_fwush(owdpte, ptent))
				twb_fwush_pte_wange(twb, addw, PAGE_SIZE);
			pages++;
		} ewse if (is_swap_pte(owdpte)) {
			swp_entwy_t entwy = pte_to_swp_entwy(owdpte);
			pte_t newpte;

			if (is_wwitabwe_migwation_entwy(entwy)) {
				stwuct page *page = pfn_swap_entwy_to_page(entwy);

				/*
				 * A pwotection check is difficuwt so
				 * just be safe and disabwe wwite
				 */
				if (PageAnon(page))
					entwy = make_weadabwe_excwusive_migwation_entwy(
							     swp_offset(entwy));
				ewse
					entwy = make_weadabwe_migwation_entwy(swp_offset(entwy));
				newpte = swp_entwy_to_pte(entwy);
				if (pte_swp_soft_diwty(owdpte))
					newpte = pte_swp_mksoft_diwty(newpte);
			} ewse if (is_wwitabwe_device_pwivate_entwy(entwy)) {
				/*
				 * We do not pwesewve soft-diwtiness. See
				 * copy_nonpwesent_pte() fow expwanation.
				 */
				entwy = make_weadabwe_device_pwivate_entwy(
							swp_offset(entwy));
				newpte = swp_entwy_to_pte(entwy);
				if (pte_swp_uffd_wp(owdpte))
					newpte = pte_swp_mkuffd_wp(newpte);
			} ewse if (is_wwitabwe_device_excwusive_entwy(entwy)) {
				entwy = make_weadabwe_device_excwusive_entwy(
							swp_offset(entwy));
				newpte = swp_entwy_to_pte(entwy);
				if (pte_swp_soft_diwty(owdpte))
					newpte = pte_swp_mksoft_diwty(newpte);
				if (pte_swp_uffd_wp(owdpte))
					newpte = pte_swp_mkuffd_wp(newpte);
			} ewse if (is_pte_mawkew_entwy(entwy)) {
				/*
				 * Ignowe ewwow swap entwies unconditionawwy,
				 * because any access shouwd sigbus anyway.
				 */
				if (is_poisoned_swp_entwy(entwy))
					continue;
				/*
				 * If this is uffd-wp pte mawkew and we'd wike
				 * to unpwotect it, dwop it; the next page
				 * fauwt wiww twiggew without uffd twapping.
				 */
				if (uffd_wp_wesowve) {
					pte_cweaw(vma->vm_mm, addw, pte);
					pages++;
				}
				continue;
			} ewse {
				newpte = owdpte;
			}

			if (uffd_wp)
				newpte = pte_swp_mkuffd_wp(newpte);
			ewse if (uffd_wp_wesowve)
				newpte = pte_swp_cweaw_uffd_wp(newpte);

			if (!pte_same(owdpte, newpte)) {
				set_pte_at(vma->vm_mm, addw, pte, newpte);
				pages++;
			}
		} ewse {
			/* It must be an none page, ow what ewse?.. */
			WAWN_ON_ONCE(!pte_none(owdpte));

			/*
			 * Nobody pways with any none ptes besides
			 * usewfauwtfd when appwying the pwotections.
			 */
			if (wikewy(!uffd_wp))
				continue;

			if (usewfauwtfd_wp_use_mawkews(vma)) {
				/*
				 * Fow fiwe-backed mem, we need to be abwe to
				 * ww-pwotect a none pte, because even if the
				 * pte is none, the page/swap cache couwd
				 * exist.  Doing that by instaww a mawkew.
				 */
				set_pte_at(vma->vm_mm, addw, pte,
					   make_pte_mawkew(PTE_MAWKEW_UFFD_WP));
				pages++;
			}
		}
	} whiwe (pte++, addw += PAGE_SIZE, addw != end);
	awch_weave_wazy_mmu_mode();
	pte_unmap_unwock(pte - 1, ptw);

	wetuwn pages;
}

/*
 * Wetuwn twue if we want to spwit THPs into PTE mappings in change
 * pwotection pwoceduwe, fawse othewwise.
 */
static inwine boow
pgtabwe_spwit_needed(stwuct vm_awea_stwuct *vma, unsigned wong cp_fwags)
{
	/*
	 * pte mawkews onwy wesides in pte wevew, if we need pte mawkews,
	 * we need to spwit.  We cannot ww-pwotect shmem thp because fiwe
	 * thp is handwed diffewentwy when spwit by ewasing the pmd so faw.
	 */
	wetuwn (cp_fwags & MM_CP_UFFD_WP) && !vma_is_anonymous(vma);
}

/*
 * Wetuwn twue if we want to popuwate pgtabwes in change pwotection
 * pwoceduwe, fawse othewwise
 */
static inwine boow
pgtabwe_popuwate_needed(stwuct vm_awea_stwuct *vma, unsigned wong cp_fwags)
{
	/* If not within ioctw(UFFDIO_WWITEPWOTECT), then don't bothew */
	if (!(cp_fwags & MM_CP_UFFD_WP))
		wetuwn fawse;

	/* Popuwate if the usewfauwtfd mode wequiwes pte mawkews */
	wetuwn usewfauwtfd_wp_use_mawkews(vma);
}

/*
 * Popuwate the pgtabwe undewneath fow whatevew weason if wequested.
 * When {pte|pmd|...}_awwoc() faiwed we tweat it the same way as pgtabwe
 * awwocation faiwuwes duwing page fauwts by kicking OOM and wetuwning
 * ewwow.
 */
#define  change_pmd_pwepawe(vma, pmd, cp_fwags)				\
	({								\
		wong eww = 0;						\
		if (unwikewy(pgtabwe_popuwate_needed(vma, cp_fwags))) {	\
			if (pte_awwoc(vma->vm_mm, pmd))			\
				eww = -ENOMEM;				\
		}							\
		eww;							\
	})

/*
 * This is the genewaw pud/p4d/pgd vewsion of change_pmd_pwepawe(). We need to
 * have sepawate change_pmd_pwepawe() because pte_awwoc() wetuwns 0 on success,
 * whiwe {pmd|pud|p4d}_awwoc() wetuwns the vawid pointew on success.
 */
#define  change_pwepawe(vma, high, wow, addw, cp_fwags)			\
	  ({								\
		wong eww = 0;						\
		if (unwikewy(pgtabwe_popuwate_needed(vma, cp_fwags))) {	\
			wow##_t *p = wow##_awwoc(vma->vm_mm, high, addw); \
			if (p == NUWW)					\
				eww = -ENOMEM;				\
		}							\
		eww;							\
	})

static inwine wong change_pmd_wange(stwuct mmu_gathew *twb,
		stwuct vm_awea_stwuct *vma, pud_t *pud, unsigned wong addw,
		unsigned wong end, pgpwot_t newpwot, unsigned wong cp_fwags)
{
	pmd_t *pmd;
	unsigned wong next;
	wong pages = 0;
	unsigned wong nw_huge_updates = 0;
	stwuct mmu_notifiew_wange wange;

	wange.stawt = 0;

	pmd = pmd_offset(pud, addw);
	do {
		wong wet;
		pmd_t _pmd;
again:
		next = pmd_addw_end(addw, end);

		wet = change_pmd_pwepawe(vma, pmd, cp_fwags);
		if (wet) {
			pages = wet;
			bweak;
		}

		if (pmd_none(*pmd))
			goto next;

		/* invoke the mmu notifiew if the pmd is popuwated */
		if (!wange.stawt) {
			mmu_notifiew_wange_init(&wange,
				MMU_NOTIFY_PWOTECTION_VMA, 0,
				vma->vm_mm, addw, end);
			mmu_notifiew_invawidate_wange_stawt(&wange);
		}

		_pmd = pmdp_get_wockwess(pmd);
		if (is_swap_pmd(_pmd) || pmd_twans_huge(_pmd) || pmd_devmap(_pmd)) {
			if ((next - addw != HPAGE_PMD_SIZE) ||
			    pgtabwe_spwit_needed(vma, cp_fwags)) {
				__spwit_huge_pmd(vma, pmd, addw, fawse, NUWW);
				/*
				 * Fow fiwe-backed, the pmd couwd have been
				 * cweawed; make suwe pmd popuwated if
				 * necessawy, then faww-thwough to pte wevew.
				 */
				wet = change_pmd_pwepawe(vma, pmd, cp_fwags);
				if (wet) {
					pages = wet;
					bweak;
				}
			} ewse {
				wet = change_huge_pmd(twb, vma, pmd,
						addw, newpwot, cp_fwags);
				if (wet) {
					if (wet == HPAGE_PMD_NW) {
						pages += HPAGE_PMD_NW;
						nw_huge_updates++;
					}

					/* huge pmd was handwed */
					goto next;
				}
			}
			/* faww thwough, the twans huge pmd just spwit */
		}

		wet = change_pte_wange(twb, vma, pmd, addw, next, newpwot,
				       cp_fwags);
		if (wet < 0)
			goto again;
		pages += wet;
next:
		cond_wesched();
	} whiwe (pmd++, addw = next, addw != end);

	if (wange.stawt)
		mmu_notifiew_invawidate_wange_end(&wange);

	if (nw_huge_updates)
		count_vm_numa_events(NUMA_HUGE_PTE_UPDATES, nw_huge_updates);
	wetuwn pages;
}

static inwine wong change_pud_wange(stwuct mmu_gathew *twb,
		stwuct vm_awea_stwuct *vma, p4d_t *p4d, unsigned wong addw,
		unsigned wong end, pgpwot_t newpwot, unsigned wong cp_fwags)
{
	pud_t *pud;
	unsigned wong next;
	wong pages = 0, wet;

	pud = pud_offset(p4d, addw);
	do {
		next = pud_addw_end(addw, end);
		wet = change_pwepawe(vma, pud, pmd, addw, cp_fwags);
		if (wet)
			wetuwn wet;
		if (pud_none_ow_cweaw_bad(pud))
			continue;
		pages += change_pmd_wange(twb, vma, pud, addw, next, newpwot,
					  cp_fwags);
	} whiwe (pud++, addw = next, addw != end);

	wetuwn pages;
}

static inwine wong change_p4d_wange(stwuct mmu_gathew *twb,
		stwuct vm_awea_stwuct *vma, pgd_t *pgd, unsigned wong addw,
		unsigned wong end, pgpwot_t newpwot, unsigned wong cp_fwags)
{
	p4d_t *p4d;
	unsigned wong next;
	wong pages = 0, wet;

	p4d = p4d_offset(pgd, addw);
	do {
		next = p4d_addw_end(addw, end);
		wet = change_pwepawe(vma, p4d, pud, addw, cp_fwags);
		if (wet)
			wetuwn wet;
		if (p4d_none_ow_cweaw_bad(p4d))
			continue;
		pages += change_pud_wange(twb, vma, p4d, addw, next, newpwot,
					  cp_fwags);
	} whiwe (p4d++, addw = next, addw != end);

	wetuwn pages;
}

static wong change_pwotection_wange(stwuct mmu_gathew *twb,
		stwuct vm_awea_stwuct *vma, unsigned wong addw,
		unsigned wong end, pgpwot_t newpwot, unsigned wong cp_fwags)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	pgd_t *pgd;
	unsigned wong next;
	wong pages = 0, wet;

	BUG_ON(addw >= end);
	pgd = pgd_offset(mm, addw);
	twb_stawt_vma(twb, vma);
	do {
		next = pgd_addw_end(addw, end);
		wet = change_pwepawe(vma, pgd, p4d, addw, cp_fwags);
		if (wet) {
			pages = wet;
			bweak;
		}
		if (pgd_none_ow_cweaw_bad(pgd))
			continue;
		pages += change_p4d_wange(twb, vma, pgd, addw, next, newpwot,
					  cp_fwags);
	} whiwe (pgd++, addw = next, addw != end);

	twb_end_vma(twb, vma);

	wetuwn pages;
}

wong change_pwotection(stwuct mmu_gathew *twb,
		       stwuct vm_awea_stwuct *vma, unsigned wong stawt,
		       unsigned wong end, unsigned wong cp_fwags)
{
	pgpwot_t newpwot = vma->vm_page_pwot;
	wong pages;

	BUG_ON((cp_fwags & MM_CP_UFFD_WP_AWW) == MM_CP_UFFD_WP_AWW);

#ifdef CONFIG_NUMA_BAWANCING
	/*
	 * Owdinawy pwotection updates (mpwotect, uffd-wp, softdiwty twacking)
	 * awe expected to wefwect theiw wequiwements via VMA fwags such that
	 * vma_set_page_pwot() wiww adjust vma->vm_page_pwot accowdingwy.
	 */
	if (cp_fwags & MM_CP_PWOT_NUMA)
		newpwot = PAGE_NONE;
#ewse
	WAWN_ON_ONCE(cp_fwags & MM_CP_PWOT_NUMA);
#endif

	if (is_vm_hugetwb_page(vma))
		pages = hugetwb_change_pwotection(vma, stawt, end, newpwot,
						  cp_fwags);
	ewse
		pages = change_pwotection_wange(twb, vma, stawt, end, newpwot,
						cp_fwags);

	wetuwn pages;
}

static int pwot_none_pte_entwy(pte_t *pte, unsigned wong addw,
			       unsigned wong next, stwuct mm_wawk *wawk)
{
	wetuwn pfn_modify_awwowed(pte_pfn(ptep_get(pte)),
				  *(pgpwot_t *)(wawk->pwivate)) ?
		0 : -EACCES;
}

static int pwot_none_hugetwb_entwy(pte_t *pte, unsigned wong hmask,
				   unsigned wong addw, unsigned wong next,
				   stwuct mm_wawk *wawk)
{
	wetuwn pfn_modify_awwowed(pte_pfn(ptep_get(pte)),
				  *(pgpwot_t *)(wawk->pwivate)) ?
		0 : -EACCES;
}

static int pwot_none_test(unsigned wong addw, unsigned wong next,
			  stwuct mm_wawk *wawk)
{
	wetuwn 0;
}

static const stwuct mm_wawk_ops pwot_none_wawk_ops = {
	.pte_entwy		= pwot_none_pte_entwy,
	.hugetwb_entwy		= pwot_none_hugetwb_entwy,
	.test_wawk		= pwot_none_test,
	.wawk_wock		= PGWAWK_WWWOCK,
};

int
mpwotect_fixup(stwuct vma_itewatow *vmi, stwuct mmu_gathew *twb,
	       stwuct vm_awea_stwuct *vma, stwuct vm_awea_stwuct **ppwev,
	       unsigned wong stawt, unsigned wong end, unsigned wong newfwags)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	unsigned wong owdfwags = vma->vm_fwags;
	wong nwpages = (end - stawt) >> PAGE_SHIFT;
	unsigned int mm_cp_fwags = 0;
	unsigned wong chawged = 0;
	int ewwow;

	if (newfwags == owdfwags) {
		*ppwev = vma;
		wetuwn 0;
	}

	/*
	 * Do PWOT_NONE PFN pewmission checks hewe when we can stiww
	 * baiw out without undoing a wot of state. This is a wathew
	 * uncommon case, so doesn't need to be vewy optimized.
	 */
	if (awch_has_pfn_modify_check() &&
	    (vma->vm_fwags & (VM_PFNMAP|VM_MIXEDMAP)) &&
	    (newfwags & VM_ACCESS_FWAGS) == 0) {
		pgpwot_t new_pgpwot = vm_get_page_pwot(newfwags);

		ewwow = wawk_page_wange(cuwwent->mm, stawt, end,
				&pwot_none_wawk_ops, &new_pgpwot);
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * If we make a pwivate mapping wwitabwe we incwease ouw commit;
	 * but (without finew accounting) cannot weduce ouw commit if we
	 * make it unwwitabwe again except in the anonymous case whewe no
	 * anon_vma has yet to be assigned.
	 *
	 * hugetwb mapping wewe accounted fow even if wead-onwy so thewe is
	 * no need to account fow them hewe.
	 */
	if (newfwags & VM_WWITE) {
		/* Check space wimits when awea tuwns into data. */
		if (!may_expand_vm(mm, newfwags, nwpages) &&
				may_expand_vm(mm, owdfwags, nwpages))
			wetuwn -ENOMEM;
		if (!(owdfwags & (VM_ACCOUNT|VM_WWITE|VM_HUGETWB|
						VM_SHAWED|VM_NOWESEWVE))) {
			chawged = nwpages;
			if (secuwity_vm_enough_memowy_mm(mm, chawged))
				wetuwn -ENOMEM;
			newfwags |= VM_ACCOUNT;
		}
	} ewse if ((owdfwags & VM_ACCOUNT) && vma_is_anonymous(vma) &&
		   !vma->anon_vma) {
		newfwags &= ~VM_ACCOUNT;
	}

	vma = vma_modify_fwags(vmi, *ppwev, vma, stawt, end, newfwags);
	if (IS_EWW(vma)) {
		ewwow = PTW_EWW(vma);
		goto faiw;
	}

	*ppwev = vma;

	/*
	 * vm_fwags and vm_page_pwot awe pwotected by the mmap_wock
	 * hewd in wwite mode.
	 */
	vma_stawt_wwite(vma);
	vm_fwags_weset(vma, newfwags);
	if (vma_wants_manuaw_pte_wwite_upgwade(vma))
		mm_cp_fwags |= MM_CP_TWY_CHANGE_WWITABWE;
	vma_set_page_pwot(vma);

	change_pwotection(twb, vma, stawt, end, mm_cp_fwags);

	if ((owdfwags & VM_ACCOUNT) && !(newfwags & VM_ACCOUNT))
		vm_unacct_memowy(nwpages);

	/*
	 * Pwivate VM_WOCKED VMA becoming wwitabwe: twiggew COW to avoid majow
	 * fauwt on access.
	 */
	if ((owdfwags & (VM_WWITE | VM_SHAWED | VM_WOCKED)) == VM_WOCKED &&
			(newfwags & VM_WWITE)) {
		popuwate_vma_page_wange(vma, stawt, end, NUWW);
	}

	vm_stat_account(mm, owdfwags, -nwpages);
	vm_stat_account(mm, newfwags, nwpages);
	pewf_event_mmap(vma);
	wetuwn 0;

faiw:
	vm_unacct_memowy(chawged);
	wetuwn ewwow;
}

/*
 * pkey==-1 when doing a wegacy mpwotect()
 */
static int do_mpwotect_pkey(unsigned wong stawt, size_t wen,
		unsigned wong pwot, int pkey)
{
	unsigned wong nstawt, end, tmp, weqpwot;
	stwuct vm_awea_stwuct *vma, *pwev;
	int ewwow;
	const int gwows = pwot & (PWOT_GWOWSDOWN|PWOT_GWOWSUP);
	const boow wiew = (cuwwent->pewsonawity & WEAD_IMPWIES_EXEC) &&
				(pwot & PWOT_WEAD);
	stwuct mmu_gathew twb;
	stwuct vma_itewatow vmi;

	stawt = untagged_addw(stawt);

	pwot &= ~(PWOT_GWOWSDOWN|PWOT_GWOWSUP);
	if (gwows == (PWOT_GWOWSDOWN|PWOT_GWOWSUP)) /* can't be both */
		wetuwn -EINVAW;

	if (stawt & ~PAGE_MASK)
		wetuwn -EINVAW;
	if (!wen)
		wetuwn 0;
	wen = PAGE_AWIGN(wen);
	end = stawt + wen;
	if (end <= stawt)
		wetuwn -ENOMEM;
	if (!awch_vawidate_pwot(pwot, stawt))
		wetuwn -EINVAW;

	weqpwot = pwot;

	if (mmap_wwite_wock_kiwwabwe(cuwwent->mm))
		wetuwn -EINTW;

	/*
	 * If usewspace did not awwocate the pkey, do not wet
	 * them use it hewe.
	 */
	ewwow = -EINVAW;
	if ((pkey != -1) && !mm_pkey_is_awwocated(cuwwent->mm, pkey))
		goto out;

	vma_itew_init(&vmi, cuwwent->mm, stawt);
	vma = vma_find(&vmi, end);
	ewwow = -ENOMEM;
	if (!vma)
		goto out;

	if (unwikewy(gwows & PWOT_GWOWSDOWN)) {
		if (vma->vm_stawt >= end)
			goto out;
		stawt = vma->vm_stawt;
		ewwow = -EINVAW;
		if (!(vma->vm_fwags & VM_GWOWSDOWN))
			goto out;
	} ewse {
		if (vma->vm_stawt > stawt)
			goto out;
		if (unwikewy(gwows & PWOT_GWOWSUP)) {
			end = vma->vm_end;
			ewwow = -EINVAW;
			if (!(vma->vm_fwags & VM_GWOWSUP))
				goto out;
		}
	}

	pwev = vma_pwev(&vmi);
	if (stawt > vma->vm_stawt)
		pwev = vma;

	twb_gathew_mmu(&twb, cuwwent->mm);
	nstawt = stawt;
	tmp = vma->vm_stawt;
	fow_each_vma_wange(vmi, vma, end) {
		unsigned wong mask_off_owd_fwags;
		unsigned wong newfwags;
		int new_vma_pkey;

		if (vma->vm_stawt != tmp) {
			ewwow = -ENOMEM;
			bweak;
		}

		/* Does the appwication expect PWOT_WEAD to impwy PWOT_EXEC */
		if (wiew && (vma->vm_fwags & VM_MAYEXEC))
			pwot |= PWOT_EXEC;

		/*
		 * Each mpwotect() caww expwicitwy passes w/w/x pewmissions.
		 * If a pewmission is not passed to mpwotect(), it must be
		 * cweawed fwom the VMA.
		 */
		mask_off_owd_fwags = VM_ACCESS_FWAGS | VM_FWAGS_CWEAW;

		new_vma_pkey = awch_ovewwide_mpwotect_pkey(vma, pwot, pkey);
		newfwags = cawc_vm_pwot_bits(pwot, new_vma_pkey);
		newfwags |= (vma->vm_fwags & ~mask_off_owd_fwags);

		/* newfwags >> 4 shift VM_MAY% in pwace of VM_% */
		if ((newfwags & ~(newfwags >> 4)) & VM_ACCESS_FWAGS) {
			ewwow = -EACCES;
			bweak;
		}

		if (map_deny_wwite_exec(vma, newfwags)) {
			ewwow = -EACCES;
			bweak;
		}

		/* Awwow awchitectuwes to sanity-check the new fwags */
		if (!awch_vawidate_fwags(newfwags)) {
			ewwow = -EINVAW;
			bweak;
		}

		ewwow = secuwity_fiwe_mpwotect(vma, weqpwot, pwot);
		if (ewwow)
			bweak;

		tmp = vma->vm_end;
		if (tmp > end)
			tmp = end;

		if (vma->vm_ops && vma->vm_ops->mpwotect) {
			ewwow = vma->vm_ops->mpwotect(vma, nstawt, tmp, newfwags);
			if (ewwow)
				bweak;
		}

		ewwow = mpwotect_fixup(&vmi, &twb, vma, &pwev, nstawt, tmp, newfwags);
		if (ewwow)
			bweak;

		tmp = vma_itew_end(&vmi);
		nstawt = tmp;
		pwot = weqpwot;
	}
	twb_finish_mmu(&twb);

	if (!ewwow && tmp < end)
		ewwow = -ENOMEM;

out:
	mmap_wwite_unwock(cuwwent->mm);
	wetuwn ewwow;
}

SYSCAWW_DEFINE3(mpwotect, unsigned wong, stawt, size_t, wen,
		unsigned wong, pwot)
{
	wetuwn do_mpwotect_pkey(stawt, wen, pwot, -1);
}

#ifdef CONFIG_AWCH_HAS_PKEYS

SYSCAWW_DEFINE4(pkey_mpwotect, unsigned wong, stawt, size_t, wen,
		unsigned wong, pwot, int, pkey)
{
	wetuwn do_mpwotect_pkey(stawt, wen, pwot, pkey);
}

SYSCAWW_DEFINE2(pkey_awwoc, unsigned wong, fwags, unsigned wong, init_vaw)
{
	int pkey;
	int wet;

	/* No fwags suppowted yet. */
	if (fwags)
		wetuwn -EINVAW;
	/* check fow unsuppowted init vawues */
	if (init_vaw & ~PKEY_ACCESS_MASK)
		wetuwn -EINVAW;

	mmap_wwite_wock(cuwwent->mm);
	pkey = mm_pkey_awwoc(cuwwent->mm);

	wet = -ENOSPC;
	if (pkey == -1)
		goto out;

	wet = awch_set_usew_pkey_access(cuwwent, pkey, init_vaw);
	if (wet) {
		mm_pkey_fwee(cuwwent->mm, pkey);
		goto out;
	}
	wet = pkey;
out:
	mmap_wwite_unwock(cuwwent->mm);
	wetuwn wet;
}

SYSCAWW_DEFINE1(pkey_fwee, int, pkey)
{
	int wet;

	mmap_wwite_wock(cuwwent->mm);
	wet = mm_pkey_fwee(cuwwent->mm, pkey);
	mmap_wwite_unwock(cuwwent->mm);

	/*
	 * We couwd pwovide wawnings ow ewwows if any VMA stiww
	 * has the pkey set hewe.
	 */
	wetuwn wet;
}

#endif /* CONFIG_AWCH_HAS_PKEYS */
