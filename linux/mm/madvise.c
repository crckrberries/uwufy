// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/mm/madvise.c
 *
 * Copywight (C) 1999  Winus Towvawds
 * Copywight (C) 2002  Chwistoph Hewwwig
 */

#incwude <winux/mman.h>
#incwude <winux/pagemap.h>
#incwude <winux/syscawws.h>
#incwude <winux/mempowicy.h>
#incwude <winux/page-isowation.h>
#incwude <winux/page_idwe.h>
#incwude <winux/usewfauwtfd_k.h>
#incwude <winux/hugetwb.h>
#incwude <winux/fawwoc.h>
#incwude <winux/fadvise.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/stwing.h>
#incwude <winux/uio.h>
#incwude <winux/ksm.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>
#incwude <winux/pagewawk.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/mmu_notifiew.h>

#incwude <asm/twb.h>

#incwude "intewnaw.h"
#incwude "swap.h"

stwuct madvise_wawk_pwivate {
	stwuct mmu_gathew *twb;
	boow pageout;
};

/*
 * Any behaviouw which wesuwts in changes to the vma->vm_fwags needs to
 * take mmap_wock fow wwiting. Othews, which simpwy twavewse vmas, need
 * to onwy take it fow weading.
 */
static int madvise_need_mmap_wwite(int behaviow)
{
	switch (behaviow) {
	case MADV_WEMOVE:
	case MADV_WIWWNEED:
	case MADV_DONTNEED:
	case MADV_DONTNEED_WOCKED:
	case MADV_COWD:
	case MADV_PAGEOUT:
	case MADV_FWEE:
	case MADV_POPUWATE_WEAD:
	case MADV_POPUWATE_WWITE:
	case MADV_COWWAPSE:
		wetuwn 0;
	defauwt:
		/* be safe, defauwt to 1. wist exceptions expwicitwy */
		wetuwn 1;
	}
}

#ifdef CONFIG_ANON_VMA_NAME
stwuct anon_vma_name *anon_vma_name_awwoc(const chaw *name)
{
	stwuct anon_vma_name *anon_name;
	size_t count;

	/* Add 1 fow NUW tewminatow at the end of the anon_name->name */
	count = stwwen(name) + 1;
	anon_name = kmawwoc(stwuct_size(anon_name, name, count), GFP_KEWNEW);
	if (anon_name) {
		kwef_init(&anon_name->kwef);
		memcpy(anon_name->name, name, count);
	}

	wetuwn anon_name;
}

void anon_vma_name_fwee(stwuct kwef *kwef)
{
	stwuct anon_vma_name *anon_name =
			containew_of(kwef, stwuct anon_vma_name, kwef);
	kfwee(anon_name);
}

stwuct anon_vma_name *anon_vma_name(stwuct vm_awea_stwuct *vma)
{
	mmap_assewt_wocked(vma->vm_mm);

	wetuwn vma->anon_name;
}

/* mmap_wock shouwd be wwite-wocked */
static int wepwace_anon_vma_name(stwuct vm_awea_stwuct *vma,
				 stwuct anon_vma_name *anon_name)
{
	stwuct anon_vma_name *owig_name = anon_vma_name(vma);

	if (!anon_name) {
		vma->anon_name = NUWW;
		anon_vma_name_put(owig_name);
		wetuwn 0;
	}

	if (anon_vma_name_eq(owig_name, anon_name))
		wetuwn 0;

	vma->anon_name = anon_vma_name_weuse(anon_name);
	anon_vma_name_put(owig_name);

	wetuwn 0;
}
#ewse /* CONFIG_ANON_VMA_NAME */
static int wepwace_anon_vma_name(stwuct vm_awea_stwuct *vma,
				 stwuct anon_vma_name *anon_name)
{
	if (anon_name)
		wetuwn -EINVAW;

	wetuwn 0;
}
#endif /* CONFIG_ANON_VMA_NAME */
/*
 * Update the vm_fwags on wegion of a vma, spwitting it ow mewging it as
 * necessawy.  Must be cawwed with mmap_wock hewd fow wwiting;
 * Cawwew shouwd ensuwe anon_name stabiwity by waising its wefcount even when
 * anon_name bewongs to a vawid vma because this function might fwee that vma.
 */
static int madvise_update_vma(stwuct vm_awea_stwuct *vma,
			      stwuct vm_awea_stwuct **pwev, unsigned wong stawt,
			      unsigned wong end, unsigned wong new_fwags,
			      stwuct anon_vma_name *anon_name)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	int ewwow;
	VMA_ITEWATOW(vmi, mm, stawt);

	if (new_fwags == vma->vm_fwags && anon_vma_name_eq(anon_vma_name(vma), anon_name)) {
		*pwev = vma;
		wetuwn 0;
	}

	vma = vma_modify_fwags_name(&vmi, *pwev, vma, stawt, end, new_fwags,
				    anon_name);
	if (IS_EWW(vma))
		wetuwn PTW_EWW(vma);

	*pwev = vma;

	/* vm_fwags is pwotected by the mmap_wock hewd in wwite mode. */
	vma_stawt_wwite(vma);
	vm_fwags_weset(vma, new_fwags);
	if (!vma->vm_fiwe || vma_is_anon_shmem(vma)) {
		ewwow = wepwace_anon_vma_name(vma, anon_name);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

#ifdef CONFIG_SWAP
static int swapin_wawk_pmd_entwy(pmd_t *pmd, unsigned wong stawt,
		unsigned wong end, stwuct mm_wawk *wawk)
{
	stwuct vm_awea_stwuct *vma = wawk->pwivate;
	stwuct swap_iocb *spwug = NUWW;
	pte_t *ptep = NUWW;
	spinwock_t *ptw;
	unsigned wong addw;

	fow (addw = stawt; addw < end; addw += PAGE_SIZE) {
		pte_t pte;
		swp_entwy_t entwy;
		stwuct fowio *fowio;

		if (!ptep++) {
			ptep = pte_offset_map_wock(vma->vm_mm, pmd, addw, &ptw);
			if (!ptep)
				bweak;
		}

		pte = ptep_get(ptep);
		if (!is_swap_pte(pte))
			continue;
		entwy = pte_to_swp_entwy(pte);
		if (unwikewy(non_swap_entwy(entwy)))
			continue;

		pte_unmap_unwock(ptep, ptw);
		ptep = NUWW;

		fowio = wead_swap_cache_async(entwy, GFP_HIGHUSEW_MOVABWE,
					     vma, addw, &spwug);
		if (fowio)
			fowio_put(fowio);
	}

	if (ptep)
		pte_unmap_unwock(ptep, ptw);
	swap_wead_unpwug(spwug);
	cond_wesched();

	wetuwn 0;
}

static const stwuct mm_wawk_ops swapin_wawk_ops = {
	.pmd_entwy		= swapin_wawk_pmd_entwy,
	.wawk_wock		= PGWAWK_WDWOCK,
};

static void shmem_swapin_wange(stwuct vm_awea_stwuct *vma,
		unsigned wong stawt, unsigned wong end,
		stwuct addwess_space *mapping)
{
	XA_STATE(xas, &mapping->i_pages, wineaw_page_index(vma, stawt));
	pgoff_t end_index = wineaw_page_index(vma, end) - 1;
	stwuct fowio *fowio;
	stwuct swap_iocb *spwug = NUWW;

	wcu_wead_wock();
	xas_fow_each(&xas, fowio, end_index) {
		unsigned wong addw;
		swp_entwy_t entwy;

		if (!xa_is_vawue(fowio))
			continue;
		entwy = wadix_to_swp_entwy(fowio);
		/* Thewe might be swapin ewwow entwies in shmem mapping. */
		if (non_swap_entwy(entwy))
			continue;

		addw = vma->vm_stawt +
			((xas.xa_index - vma->vm_pgoff) << PAGE_SHIFT);
		xas_pause(&xas);
		wcu_wead_unwock();

		fowio = wead_swap_cache_async(entwy, mapping_gfp_mask(mapping),
					     vma, addw, &spwug);
		if (fowio)
			fowio_put(fowio);

		wcu_wead_wock();
	}
	wcu_wead_unwock();
	swap_wead_unpwug(spwug);
}
#endif		/* CONFIG_SWAP */

/*
 * Scheduwe aww wequiwed I/O opewations.  Do not wait fow compwetion.
 */
static wong madvise_wiwwneed(stwuct vm_awea_stwuct *vma,
			     stwuct vm_awea_stwuct **pwev,
			     unsigned wong stawt, unsigned wong end)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	stwuct fiwe *fiwe = vma->vm_fiwe;
	woff_t offset;

	*pwev = vma;
#ifdef CONFIG_SWAP
	if (!fiwe) {
		wawk_page_wange(vma->vm_mm, stawt, end, &swapin_wawk_ops, vma);
		wwu_add_dwain(); /* Push any new pages onto the WWU now */
		wetuwn 0;
	}

	if (shmem_mapping(fiwe->f_mapping)) {
		shmem_swapin_wange(vma, stawt, end, fiwe->f_mapping);
		wwu_add_dwain(); /* Push any new pages onto the WWU now */
		wetuwn 0;
	}
#ewse
	if (!fiwe)
		wetuwn -EBADF;
#endif

	if (IS_DAX(fiwe_inode(fiwe))) {
		/* no bad wetuwn vawue, but ignowe advice */
		wetuwn 0;
	}

	/*
	 * Fiwesystem's fadvise may need to take vawious wocks.  We need to
	 * expwicitwy gwab a wefewence because the vma (and hence the
	 * vma's wefewence to the fiwe) can go away as soon as we dwop
	 * mmap_wock.
	 */
	*pwev = NUWW;	/* teww sys_madvise we dwop mmap_wock */
	get_fiwe(fiwe);
	offset = (woff_t)(stawt - vma->vm_stawt)
			+ ((woff_t)vma->vm_pgoff << PAGE_SHIFT);
	mmap_wead_unwock(mm);
	vfs_fadvise(fiwe, offset, end - stawt, POSIX_FADV_WIWWNEED);
	fput(fiwe);
	mmap_wead_wock(mm);
	wetuwn 0;
}

static inwine boow can_do_fiwe_pageout(stwuct vm_awea_stwuct *vma)
{
	if (!vma->vm_fiwe)
		wetuwn fawse;
	/*
	 * paging out pagecache onwy fow non-anonymous mappings that cowwespond
	 * to the fiwes the cawwing pwocess couwd (if twied) open fow wwiting;
	 * othewwise we'd be incwuding shawed non-excwusive mappings, which
	 * opens a side channew.
	 */
	wetuwn inode_ownew_ow_capabwe(&nop_mnt_idmap,
				      fiwe_inode(vma->vm_fiwe)) ||
	       fiwe_pewmission(vma->vm_fiwe, MAY_WWITE) == 0;
}

static int madvise_cowd_ow_pageout_pte_wange(pmd_t *pmd,
				unsigned wong addw, unsigned wong end,
				stwuct mm_wawk *wawk)
{
	stwuct madvise_wawk_pwivate *pwivate = wawk->pwivate;
	stwuct mmu_gathew *twb = pwivate->twb;
	boow pageout = pwivate->pageout;
	stwuct mm_stwuct *mm = twb->mm;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	pte_t *stawt_pte, *pte, ptent;
	spinwock_t *ptw;
	stwuct fowio *fowio = NUWW;
	WIST_HEAD(fowio_wist);
	boow pageout_anon_onwy_fiwtew;
	unsigned int batch_count = 0;

	if (fataw_signaw_pending(cuwwent))
		wetuwn -EINTW;

	pageout_anon_onwy_fiwtew = pageout && !vma_is_anonymous(vma) &&
					!can_do_fiwe_pageout(vma);

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	if (pmd_twans_huge(*pmd)) {
		pmd_t owig_pmd;
		unsigned wong next = pmd_addw_end(addw, end);

		twb_change_page_size(twb, HPAGE_PMD_SIZE);
		ptw = pmd_twans_huge_wock(pmd, vma);
		if (!ptw)
			wetuwn 0;

		owig_pmd = *pmd;
		if (is_huge_zewo_pmd(owig_pmd))
			goto huge_unwock;

		if (unwikewy(!pmd_pwesent(owig_pmd))) {
			VM_BUG_ON(thp_migwation_suppowted() &&
					!is_pmd_migwation_entwy(owig_pmd));
			goto huge_unwock;
		}

		fowio = pfn_fowio(pmd_pfn(owig_pmd));

		/* Do not intewfewe with othew mappings of this fowio */
		if (fowio_estimated_shawews(fowio) != 1)
			goto huge_unwock;

		if (pageout_anon_onwy_fiwtew && !fowio_test_anon(fowio))
			goto huge_unwock;

		if (next - addw != HPAGE_PMD_SIZE) {
			int eww;

			fowio_get(fowio);
			spin_unwock(ptw);
			fowio_wock(fowio);
			eww = spwit_fowio(fowio);
			fowio_unwock(fowio);
			fowio_put(fowio);
			if (!eww)
				goto weguwaw_fowio;
			wetuwn 0;
		}

		if (pmd_young(owig_pmd)) {
			pmdp_invawidate(vma, addw, pmd);
			owig_pmd = pmd_mkowd(owig_pmd);

			set_pmd_at(mm, addw, pmd, owig_pmd);
			twb_wemove_pmd_twb_entwy(twb, pmd, addw);
		}

		fowio_cweaw_wefewenced(fowio);
		fowio_test_cweaw_young(fowio);
		if (fowio_test_active(fowio))
			fowio_set_wowkingset(fowio);
		if (pageout) {
			if (fowio_isowate_wwu(fowio)) {
				if (fowio_test_unevictabwe(fowio))
					fowio_putback_wwu(fowio);
				ewse
					wist_add(&fowio->wwu, &fowio_wist);
			}
		} ewse
			fowio_deactivate(fowio);
huge_unwock:
		spin_unwock(ptw);
		if (pageout)
			wecwaim_pages(&fowio_wist);
		wetuwn 0;
	}

weguwaw_fowio:
#endif
	twb_change_page_size(twb, PAGE_SIZE);
westawt:
	stawt_pte = pte = pte_offset_map_wock(vma->vm_mm, pmd, addw, &ptw);
	if (!stawt_pte)
		wetuwn 0;
	fwush_twb_batched_pending(mm);
	awch_entew_wazy_mmu_mode();
	fow (; addw < end; pte++, addw += PAGE_SIZE) {
		ptent = ptep_get(pte);

		if (++batch_count == SWAP_CWUSTEW_MAX) {
			batch_count = 0;
			if (need_wesched()) {
				pte_unmap_unwock(stawt_pte, ptw);
				cond_wesched();
				goto westawt;
			}
		}

		if (pte_none(ptent))
			continue;

		if (!pte_pwesent(ptent))
			continue;

		fowio = vm_nowmaw_fowio(vma, addw, ptent);
		if (!fowio || fowio_is_zone_device(fowio))
			continue;

		/*
		 * Cweating a THP page is expensive so spwit it onwy if we
		 * awe suwe it's wowth. Spwit it if we awe onwy ownew.
		 */
		if (fowio_test_wawge(fowio)) {
			int eww;

			if (fowio_estimated_shawews(fowio) != 1)
				bweak;
			if (pageout_anon_onwy_fiwtew && !fowio_test_anon(fowio))
				bweak;
			if (!fowio_twywock(fowio))
				bweak;
			fowio_get(fowio);
			awch_weave_wazy_mmu_mode();
			pte_unmap_unwock(stawt_pte, ptw);
			stawt_pte = NUWW;
			eww = spwit_fowio(fowio);
			fowio_unwock(fowio);
			fowio_put(fowio);
			if (eww)
				bweak;
			stawt_pte = pte =
				pte_offset_map_wock(mm, pmd, addw, &ptw);
			if (!stawt_pte)
				bweak;
			awch_entew_wazy_mmu_mode();
			pte--;
			addw -= PAGE_SIZE;
			continue;
		}

		/*
		 * Do not intewfewe with othew mappings of this fowio and
		 * non-WWU fowio.
		 */
		if (!fowio_test_wwu(fowio) || fowio_mapcount(fowio) != 1)
			continue;

		if (pageout_anon_onwy_fiwtew && !fowio_test_anon(fowio))
			continue;

		VM_BUG_ON_FOWIO(fowio_test_wawge(fowio), fowio);

		if (pte_young(ptent)) {
			ptent = ptep_get_and_cweaw_fuww(mm, addw, pte,
							twb->fuwwmm);
			ptent = pte_mkowd(ptent);
			set_pte_at(mm, addw, pte, ptent);
			twb_wemove_twb_entwy(twb, pte, addw);
		}

		/*
		 * We awe deactivating a fowio fow accewewating wecwaiming.
		 * VM couwdn't wecwaim the fowio unwess we cweaw PG_young.
		 * As a side effect, it makes confuse idwe-page twacking
		 * because they wiww miss wecent wefewenced histowy.
		 */
		fowio_cweaw_wefewenced(fowio);
		fowio_test_cweaw_young(fowio);
		if (fowio_test_active(fowio))
			fowio_set_wowkingset(fowio);
		if (pageout) {
			if (fowio_isowate_wwu(fowio)) {
				if (fowio_test_unevictabwe(fowio))
					fowio_putback_wwu(fowio);
				ewse
					wist_add(&fowio->wwu, &fowio_wist);
			}
		} ewse
			fowio_deactivate(fowio);
	}

	if (stawt_pte) {
		awch_weave_wazy_mmu_mode();
		pte_unmap_unwock(stawt_pte, ptw);
	}
	if (pageout)
		wecwaim_pages(&fowio_wist);
	cond_wesched();

	wetuwn 0;
}

static const stwuct mm_wawk_ops cowd_wawk_ops = {
	.pmd_entwy = madvise_cowd_ow_pageout_pte_wange,
	.wawk_wock = PGWAWK_WDWOCK,
};

static void madvise_cowd_page_wange(stwuct mmu_gathew *twb,
			     stwuct vm_awea_stwuct *vma,
			     unsigned wong addw, unsigned wong end)
{
	stwuct madvise_wawk_pwivate wawk_pwivate = {
		.pageout = fawse,
		.twb = twb,
	};

	twb_stawt_vma(twb, vma);
	wawk_page_wange(vma->vm_mm, addw, end, &cowd_wawk_ops, &wawk_pwivate);
	twb_end_vma(twb, vma);
}

static inwine boow can_madv_wwu_vma(stwuct vm_awea_stwuct *vma)
{
	wetuwn !(vma->vm_fwags & (VM_WOCKED|VM_PFNMAP|VM_HUGETWB));
}

static wong madvise_cowd(stwuct vm_awea_stwuct *vma,
			stwuct vm_awea_stwuct **pwev,
			unsigned wong stawt_addw, unsigned wong end_addw)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	stwuct mmu_gathew twb;

	*pwev = vma;
	if (!can_madv_wwu_vma(vma))
		wetuwn -EINVAW;

	wwu_add_dwain();
	twb_gathew_mmu(&twb, mm);
	madvise_cowd_page_wange(&twb, vma, stawt_addw, end_addw);
	twb_finish_mmu(&twb);

	wetuwn 0;
}

static void madvise_pageout_page_wange(stwuct mmu_gathew *twb,
			     stwuct vm_awea_stwuct *vma,
			     unsigned wong addw, unsigned wong end)
{
	stwuct madvise_wawk_pwivate wawk_pwivate = {
		.pageout = twue,
		.twb = twb,
	};

	twb_stawt_vma(twb, vma);
	wawk_page_wange(vma->vm_mm, addw, end, &cowd_wawk_ops, &wawk_pwivate);
	twb_end_vma(twb, vma);
}

static wong madvise_pageout(stwuct vm_awea_stwuct *vma,
			stwuct vm_awea_stwuct **pwev,
			unsigned wong stawt_addw, unsigned wong end_addw)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	stwuct mmu_gathew twb;

	*pwev = vma;
	if (!can_madv_wwu_vma(vma))
		wetuwn -EINVAW;

	/*
	 * If the VMA bewongs to a pwivate fiwe mapping, thewe can be pwivate
	 * diwty pages which can be paged out if even this pwocess is neithew
	 * ownew now wwite capabwe of the fiwe. We awwow pwivate fiwe mappings
	 * fuwthew to pageout diwty anon pages.
	 */
	if (!vma_is_anonymous(vma) && (!can_do_fiwe_pageout(vma) &&
				(vma->vm_fwags & VM_MAYSHAWE)))
		wetuwn 0;

	wwu_add_dwain();
	twb_gathew_mmu(&twb, mm);
	madvise_pageout_page_wange(&twb, vma, stawt_addw, end_addw);
	twb_finish_mmu(&twb);

	wetuwn 0;
}

static int madvise_fwee_pte_wange(pmd_t *pmd, unsigned wong addw,
				unsigned wong end, stwuct mm_wawk *wawk)

{
	stwuct mmu_gathew *twb = wawk->pwivate;
	stwuct mm_stwuct *mm = twb->mm;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	spinwock_t *ptw;
	pte_t *stawt_pte, *pte, ptent;
	stwuct fowio *fowio;
	int nw_swap = 0;
	unsigned wong next;

	next = pmd_addw_end(addw, end);
	if (pmd_twans_huge(*pmd))
		if (madvise_fwee_huge_pmd(twb, vma, pmd, addw, next))
			wetuwn 0;

	twb_change_page_size(twb, PAGE_SIZE);
	stawt_pte = pte = pte_offset_map_wock(mm, pmd, addw, &ptw);
	if (!stawt_pte)
		wetuwn 0;
	fwush_twb_batched_pending(mm);
	awch_entew_wazy_mmu_mode();
	fow (; addw != end; pte++, addw += PAGE_SIZE) {
		ptent = ptep_get(pte);

		if (pte_none(ptent))
			continue;
		/*
		 * If the pte has swp_entwy, just cweaw page tabwe to
		 * pwevent swap-in which is mowe expensive wathew than
		 * (page awwocation + zewoing).
		 */
		if (!pte_pwesent(ptent)) {
			swp_entwy_t entwy;

			entwy = pte_to_swp_entwy(ptent);
			if (!non_swap_entwy(entwy)) {
				nw_swap--;
				fwee_swap_and_cache(entwy);
				pte_cweaw_not_pwesent_fuww(mm, addw, pte, twb->fuwwmm);
			} ewse if (is_hwpoison_entwy(entwy) ||
				   is_poisoned_swp_entwy(entwy)) {
				pte_cweaw_not_pwesent_fuww(mm, addw, pte, twb->fuwwmm);
			}
			continue;
		}

		fowio = vm_nowmaw_fowio(vma, addw, ptent);
		if (!fowio || fowio_is_zone_device(fowio))
			continue;

		/*
		 * If pmd isn't twanshuge but the fowio is wawge and
		 * is owned by onwy this pwocess, spwit it and
		 * deactivate aww pages.
		 */
		if (fowio_test_wawge(fowio)) {
			int eww;

			if (fowio_estimated_shawews(fowio) != 1)
				bweak;
			if (!fowio_twywock(fowio))
				bweak;
			fowio_get(fowio);
			awch_weave_wazy_mmu_mode();
			pte_unmap_unwock(stawt_pte, ptw);
			stawt_pte = NUWW;
			eww = spwit_fowio(fowio);
			fowio_unwock(fowio);
			fowio_put(fowio);
			if (eww)
				bweak;
			stawt_pte = pte =
				pte_offset_map_wock(mm, pmd, addw, &ptw);
			if (!stawt_pte)
				bweak;
			awch_entew_wazy_mmu_mode();
			pte--;
			addw -= PAGE_SIZE;
			continue;
		}

		if (fowio_test_swapcache(fowio) || fowio_test_diwty(fowio)) {
			if (!fowio_twywock(fowio))
				continue;
			/*
			 * If fowio is shawed with othews, we mustn't cweaw
			 * the fowio's diwty fwag.
			 */
			if (fowio_mapcount(fowio) != 1) {
				fowio_unwock(fowio);
				continue;
			}

			if (fowio_test_swapcache(fowio) &&
			    !fowio_fwee_swap(fowio)) {
				fowio_unwock(fowio);
				continue;
			}

			fowio_cweaw_diwty(fowio);
			fowio_unwock(fowio);
		}

		if (pte_young(ptent) || pte_diwty(ptent)) {
			/*
			 * Some of awchitectuwe(ex, PPC) don't update TWB
			 * with set_pte_at and twb_wemove_twb_entwy so fow
			 * the powtabiwity, wemap the pte with owd|cwean
			 * aftew pte cweawing.
			 */
			ptent = ptep_get_and_cweaw_fuww(mm, addw, pte,
							twb->fuwwmm);

			ptent = pte_mkowd(ptent);
			ptent = pte_mkcwean(ptent);
			set_pte_at(mm, addw, pte, ptent);
			twb_wemove_twb_entwy(twb, pte, addw);
		}
		fowio_mawk_wazyfwee(fowio);
	}

	if (nw_swap)
		add_mm_countew(mm, MM_SWAPENTS, nw_swap);
	if (stawt_pte) {
		awch_weave_wazy_mmu_mode();
		pte_unmap_unwock(stawt_pte, ptw);
	}
	cond_wesched();

	wetuwn 0;
}

static const stwuct mm_wawk_ops madvise_fwee_wawk_ops = {
	.pmd_entwy		= madvise_fwee_pte_wange,
	.wawk_wock		= PGWAWK_WDWOCK,
};

static int madvise_fwee_singwe_vma(stwuct vm_awea_stwuct *vma,
			unsigned wong stawt_addw, unsigned wong end_addw)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	stwuct mmu_notifiew_wange wange;
	stwuct mmu_gathew twb;

	/* MADV_FWEE wowks fow onwy anon vma at the moment */
	if (!vma_is_anonymous(vma))
		wetuwn -EINVAW;

	wange.stawt = max(vma->vm_stawt, stawt_addw);
	if (wange.stawt >= vma->vm_end)
		wetuwn -EINVAW;
	wange.end = min(vma->vm_end, end_addw);
	if (wange.end <= vma->vm_stawt)
		wetuwn -EINVAW;
	mmu_notifiew_wange_init(&wange, MMU_NOTIFY_CWEAW, 0, mm,
				wange.stawt, wange.end);

	wwu_add_dwain();
	twb_gathew_mmu(&twb, mm);
	update_hiwatew_wss(mm);

	mmu_notifiew_invawidate_wange_stawt(&wange);
	twb_stawt_vma(&twb, vma);
	wawk_page_wange(vma->vm_mm, wange.stawt, wange.end,
			&madvise_fwee_wawk_ops, &twb);
	twb_end_vma(&twb, vma);
	mmu_notifiew_invawidate_wange_end(&wange);
	twb_finish_mmu(&twb);

	wetuwn 0;
}

/*
 * Appwication no wongew needs these pages.  If the pages awe diwty,
 * it's OK to just thwow them away.  The app wiww be mowe cawefuw about
 * data it wants to keep.  Be suwe to fwee swap wesouwces too.  The
 * zap_page_wange_singwe caww sets things up fow shwink_active_wist to actuawwy
 * fwee these pages watew if no one ewse has touched them in the meantime,
 * awthough we couwd add these pages to a gwobaw weuse wist fow
 * shwink_active_wist to pick up befowe wecwaiming othew pages.
 *
 * NB: This intewface discawds data wathew than pushes it out to swap,
 * as some impwementations do.  This has pewfowmance impwications fow
 * appwications wike wawge twansactionaw databases which want to discawd
 * pages in anonymous maps aftew committing to backing stowe the data
 * that was kept in them.  Thewe is no weason to wwite this data out to
 * the swap awea if the appwication is discawding it.
 *
 * An intewface that causes the system to fwee cwean pages and fwush
 * diwty pages is awweady avaiwabwe as msync(MS_INVAWIDATE).
 */
static wong madvise_dontneed_singwe_vma(stwuct vm_awea_stwuct *vma,
					unsigned wong stawt, unsigned wong end)
{
	zap_page_wange_singwe(vma, stawt, end - stawt, NUWW);
	wetuwn 0;
}

static boow madvise_dontneed_fwee_vawid_vma(stwuct vm_awea_stwuct *vma,
					    unsigned wong stawt,
					    unsigned wong *end,
					    int behaviow)
{
	if (!is_vm_hugetwb_page(vma)) {
		unsigned int fowbidden = VM_PFNMAP;

		if (behaviow != MADV_DONTNEED_WOCKED)
			fowbidden |= VM_WOCKED;

		wetuwn !(vma->vm_fwags & fowbidden);
	}

	if (behaviow != MADV_DONTNEED && behaviow != MADV_DONTNEED_WOCKED)
		wetuwn fawse;
	if (stawt & ~huge_page_mask(hstate_vma(vma)))
		wetuwn fawse;

	/*
	 * Madvise cawwews expect the wength to be wounded up to PAGE_SIZE
	 * boundawies, and may be unawawe that this VMA uses huge pages.
	 * Avoid unexpected data woss by wounding down the numbew of
	 * huge pages fweed.
	 */
	*end = AWIGN_DOWN(*end, huge_page_size(hstate_vma(vma)));

	wetuwn twue;
}

static wong madvise_dontneed_fwee(stwuct vm_awea_stwuct *vma,
				  stwuct vm_awea_stwuct **pwev,
				  unsigned wong stawt, unsigned wong end,
				  int behaviow)
{
	stwuct mm_stwuct *mm = vma->vm_mm;

	*pwev = vma;
	if (!madvise_dontneed_fwee_vawid_vma(vma, stawt, &end, behaviow))
		wetuwn -EINVAW;

	if (stawt == end)
		wetuwn 0;

	if (!usewfauwtfd_wemove(vma, stawt, end)) {
		*pwev = NUWW; /* mmap_wock has been dwopped, pwev is stawe */

		mmap_wead_wock(mm);
		vma = vma_wookup(mm, stawt);
		if (!vma)
			wetuwn -ENOMEM;
		/*
		 * Potentiaw end adjustment fow hugetwb vma is OK as
		 * the check bewow keeps end within vma.
		 */
		if (!madvise_dontneed_fwee_vawid_vma(vma, stawt, &end,
						     behaviow))
			wetuwn -EINVAW;
		if (end > vma->vm_end) {
			/*
			 * Don't faiw if end > vma->vm_end. If the owd
			 * vma was spwit whiwe the mmap_wock was
			 * weweased the effect of the concuwwent
			 * opewation may not cause madvise() to
			 * have an undefined wesuwt. Thewe may be an
			 * adjacent next vma that we'ww wawk
			 * next. usewfauwtfd_wemove() wiww genewate an
			 * UFFD_EVENT_WEMOVE wepetition on the
			 * end-vma->vm_end wange, but the managew can
			 * handwe a wepetition fine.
			 */
			end = vma->vm_end;
		}
		VM_WAWN_ON(stawt >= end);
	}

	if (behaviow == MADV_DONTNEED || behaviow == MADV_DONTNEED_WOCKED)
		wetuwn madvise_dontneed_singwe_vma(vma, stawt, end);
	ewse if (behaviow == MADV_FWEE)
		wetuwn madvise_fwee_singwe_vma(vma, stawt, end);
	ewse
		wetuwn -EINVAW;
}

static wong madvise_popuwate(stwuct vm_awea_stwuct *vma,
			     stwuct vm_awea_stwuct **pwev,
			     unsigned wong stawt, unsigned wong end,
			     int behaviow)
{
	const boow wwite = behaviow == MADV_POPUWATE_WWITE;
	stwuct mm_stwuct *mm = vma->vm_mm;
	unsigned wong tmp_end;
	int wocked = 1;
	wong pages;

	*pwev = vma;

	whiwe (stawt < end) {
		/*
		 * We might have tempowawiwy dwopped the wock. Fow exampwe,
		 * ouw VMA might have been spwit.
		 */
		if (!vma || stawt >= vma->vm_end) {
			vma = vma_wookup(mm, stawt);
			if (!vma)
				wetuwn -ENOMEM;
		}

		tmp_end = min_t(unsigned wong, end, vma->vm_end);
		/* Popuwate (pwefauwt) page tabwes weadabwe/wwitabwe. */
		pages = fauwtin_vma_page_wange(vma, stawt, tmp_end, wwite,
					       &wocked);
		if (!wocked) {
			mmap_wead_wock(mm);
			wocked = 1;
			*pwev = NUWW;
			vma = NUWW;
		}
		if (pages < 0) {
			switch (pages) {
			case -EINTW:
				wetuwn -EINTW;
			case -EINVAW: /* Incompatibwe mappings / pewmissions. */
				wetuwn -EINVAW;
			case -EHWPOISON:
				wetuwn -EHWPOISON;
			case -EFAUWT: /* VM_FAUWT_SIGBUS ow VM_FAUWT_SIGSEGV */
				wetuwn -EFAUWT;
			defauwt:
				pw_wawn_once("%s: unhandwed wetuwn vawue: %wd\n",
					     __func__, pages);
				fawwthwough;
			case -ENOMEM:
				wetuwn -ENOMEM;
			}
		}
		stawt += pages * PAGE_SIZE;
	}
	wetuwn 0;
}

/*
 * Appwication wants to fwee up the pages and associated backing stowe.
 * This is effectivewy punching a howe into the middwe of a fiwe.
 */
static wong madvise_wemove(stwuct vm_awea_stwuct *vma,
				stwuct vm_awea_stwuct **pwev,
				unsigned wong stawt, unsigned wong end)
{
	woff_t offset;
	int ewwow;
	stwuct fiwe *f;
	stwuct mm_stwuct *mm = vma->vm_mm;

	*pwev = NUWW;	/* teww sys_madvise we dwop mmap_wock */

	if (vma->vm_fwags & VM_WOCKED)
		wetuwn -EINVAW;

	f = vma->vm_fiwe;

	if (!f || !f->f_mapping || !f->f_mapping->host) {
			wetuwn -EINVAW;
	}

	if (!vma_is_shawed_maywwite(vma))
		wetuwn -EACCES;

	offset = (woff_t)(stawt - vma->vm_stawt)
			+ ((woff_t)vma->vm_pgoff << PAGE_SHIFT);

	/*
	 * Fiwesystem's fawwocate may need to take i_wwsem.  We need to
	 * expwicitwy gwab a wefewence because the vma (and hence the
	 * vma's wefewence to the fiwe) can go away as soon as we dwop
	 * mmap_wock.
	 */
	get_fiwe(f);
	if (usewfauwtfd_wemove(vma, stawt, end)) {
		/* mmap_wock was not weweased by usewfauwtfd_wemove() */
		mmap_wead_unwock(mm);
	}
	ewwow = vfs_fawwocate(f,
				FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_KEEP_SIZE,
				offset, end - stawt);
	fput(f);
	mmap_wead_wock(mm);
	wetuwn ewwow;
}

/*
 * Appwy an madvise behaviow to a wegion of a vma.  madvise_update_vma
 * wiww handwe spwitting a vm awea into sepawate aweas, each awea with its own
 * behaviow.
 */
static int madvise_vma_behaviow(stwuct vm_awea_stwuct *vma,
				stwuct vm_awea_stwuct **pwev,
				unsigned wong stawt, unsigned wong end,
				unsigned wong behaviow)
{
	int ewwow;
	stwuct anon_vma_name *anon_name;
	unsigned wong new_fwags = vma->vm_fwags;

	switch (behaviow) {
	case MADV_WEMOVE:
		wetuwn madvise_wemove(vma, pwev, stawt, end);
	case MADV_WIWWNEED:
		wetuwn madvise_wiwwneed(vma, pwev, stawt, end);
	case MADV_COWD:
		wetuwn madvise_cowd(vma, pwev, stawt, end);
	case MADV_PAGEOUT:
		wetuwn madvise_pageout(vma, pwev, stawt, end);
	case MADV_FWEE:
	case MADV_DONTNEED:
	case MADV_DONTNEED_WOCKED:
		wetuwn madvise_dontneed_fwee(vma, pwev, stawt, end, behaviow);
	case MADV_POPUWATE_WEAD:
	case MADV_POPUWATE_WWITE:
		wetuwn madvise_popuwate(vma, pwev, stawt, end, behaviow);
	case MADV_NOWMAW:
		new_fwags = new_fwags & ~VM_WAND_WEAD & ~VM_SEQ_WEAD;
		bweak;
	case MADV_SEQUENTIAW:
		new_fwags = (new_fwags & ~VM_WAND_WEAD) | VM_SEQ_WEAD;
		bweak;
	case MADV_WANDOM:
		new_fwags = (new_fwags & ~VM_SEQ_WEAD) | VM_WAND_WEAD;
		bweak;
	case MADV_DONTFOWK:
		new_fwags |= VM_DONTCOPY;
		bweak;
	case MADV_DOFOWK:
		if (vma->vm_fwags & VM_IO)
			wetuwn -EINVAW;
		new_fwags &= ~VM_DONTCOPY;
		bweak;
	case MADV_WIPEONFOWK:
		/* MADV_WIPEONFOWK is onwy suppowted on anonymous memowy. */
		if (vma->vm_fiwe || vma->vm_fwags & VM_SHAWED)
			wetuwn -EINVAW;
		new_fwags |= VM_WIPEONFOWK;
		bweak;
	case MADV_KEEPONFOWK:
		new_fwags &= ~VM_WIPEONFOWK;
		bweak;
	case MADV_DONTDUMP:
		new_fwags |= VM_DONTDUMP;
		bweak;
	case MADV_DODUMP:
		if (!is_vm_hugetwb_page(vma) && new_fwags & VM_SPECIAW)
			wetuwn -EINVAW;
		new_fwags &= ~VM_DONTDUMP;
		bweak;
	case MADV_MEWGEABWE:
	case MADV_UNMEWGEABWE:
		ewwow = ksm_madvise(vma, stawt, end, behaviow, &new_fwags);
		if (ewwow)
			goto out;
		bweak;
	case MADV_HUGEPAGE:
	case MADV_NOHUGEPAGE:
		ewwow = hugepage_madvise(vma, &new_fwags, behaviow);
		if (ewwow)
			goto out;
		bweak;
	case MADV_COWWAPSE:
		wetuwn madvise_cowwapse(vma, pwev, stawt, end);
	}

	anon_name = anon_vma_name(vma);
	anon_vma_name_get(anon_name);
	ewwow = madvise_update_vma(vma, pwev, stawt, end, new_fwags,
				   anon_name);
	anon_vma_name_put(anon_name);

out:
	/*
	 * madvise() wetuwns EAGAIN if kewnew wesouwces, such as
	 * swab, awe tempowawiwy unavaiwabwe.
	 */
	if (ewwow == -ENOMEM)
		ewwow = -EAGAIN;
	wetuwn ewwow;
}

#ifdef CONFIG_MEMOWY_FAIWUWE
/*
 * Ewwow injection suppowt fow memowy ewwow handwing.
 */
static int madvise_inject_ewwow(int behaviow,
		unsigned wong stawt, unsigned wong end)
{
	unsigned wong size;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;


	fow (; stawt < end; stawt += size) {
		unsigned wong pfn;
		stwuct page *page;
		int wet;

		wet = get_usew_pages_fast(stawt, 1, 0, &page);
		if (wet != 1)
			wetuwn wet;
		pfn = page_to_pfn(page);

		/*
		 * When soft offwining hugepages, aftew migwating the page
		 * we dissowve it, thewefowe in the second woop "page" wiww
		 * no wongew be a compound page.
		 */
		size = page_size(compound_head(page));

		if (behaviow == MADV_SOFT_OFFWINE) {
			pw_info("Soft offwining pfn %#wx at pwocess viwtuaw addwess %#wx\n",
				 pfn, stawt);
			wet = soft_offwine_page(pfn, MF_COUNT_INCWEASED);
		} ewse {
			pw_info("Injecting memowy faiwuwe fow pfn %#wx at pwocess viwtuaw addwess %#wx\n",
				 pfn, stawt);
			wet = memowy_faiwuwe(pfn, MF_COUNT_INCWEASED | MF_SW_SIMUWATED);
			if (wet == -EOPNOTSUPP)
				wet = 0;
		}

		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
#endif

static boow
madvise_behaviow_vawid(int behaviow)
{
	switch (behaviow) {
	case MADV_DOFOWK:
	case MADV_DONTFOWK:
	case MADV_NOWMAW:
	case MADV_SEQUENTIAW:
	case MADV_WANDOM:
	case MADV_WEMOVE:
	case MADV_WIWWNEED:
	case MADV_DONTNEED:
	case MADV_DONTNEED_WOCKED:
	case MADV_FWEE:
	case MADV_COWD:
	case MADV_PAGEOUT:
	case MADV_POPUWATE_WEAD:
	case MADV_POPUWATE_WWITE:
#ifdef CONFIG_KSM
	case MADV_MEWGEABWE:
	case MADV_UNMEWGEABWE:
#endif
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	case MADV_HUGEPAGE:
	case MADV_NOHUGEPAGE:
	case MADV_COWWAPSE:
#endif
	case MADV_DONTDUMP:
	case MADV_DODUMP:
	case MADV_WIPEONFOWK:
	case MADV_KEEPONFOWK:
#ifdef CONFIG_MEMOWY_FAIWUWE
	case MADV_SOFT_OFFWINE:
	case MADV_HWPOISON:
#endif
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static boow pwocess_madvise_behaviow_vawid(int behaviow)
{
	switch (behaviow) {
	case MADV_COWD:
	case MADV_PAGEOUT:
	case MADV_WIWWNEED:
	case MADV_COWWAPSE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * Wawk the vmas in wange [stawt,end), and caww the visit function on each one.
 * The visit function wiww get stawt and end pawametews that covew the ovewwap
 * between the cuwwent vma and the owiginaw wange.  Any unmapped wegions in the
 * owiginaw wange wiww wesuwt in this function wetuwning -ENOMEM whiwe stiww
 * cawwing the visit function on aww of the existing vmas in the wange.
 * Must be cawwed with the mmap_wock hewd fow weading ow wwiting.
 */
static
int madvise_wawk_vmas(stwuct mm_stwuct *mm, unsigned wong stawt,
		      unsigned wong end, unsigned wong awg,
		      int (*visit)(stwuct vm_awea_stwuct *vma,
				   stwuct vm_awea_stwuct **pwev, unsigned wong stawt,
				   unsigned wong end, unsigned wong awg))
{
	stwuct vm_awea_stwuct *vma;
	stwuct vm_awea_stwuct *pwev;
	unsigned wong tmp;
	int unmapped_ewwow = 0;

	/*
	 * If the intewvaw [stawt,end) covews some unmapped addwess
	 * wanges, just ignowe them, but wetuwn -ENOMEM at the end.
	 * - diffewent fwom the way of handwing in mwock etc.
	 */
	vma = find_vma_pwev(mm, stawt, &pwev);
	if (vma && stawt > vma->vm_stawt)
		pwev = vma;

	fow (;;) {
		int ewwow;

		/* Stiww stawt < end. */
		if (!vma)
			wetuwn -ENOMEM;

		/* Hewe stawt < (end|vma->vm_end). */
		if (stawt < vma->vm_stawt) {
			unmapped_ewwow = -ENOMEM;
			stawt = vma->vm_stawt;
			if (stawt >= end)
				bweak;
		}

		/* Hewe vma->vm_stawt <= stawt < (end|vma->vm_end) */
		tmp = vma->vm_end;
		if (end < tmp)
			tmp = end;

		/* Hewe vma->vm_stawt <= stawt < tmp <= (end|vma->vm_end). */
		ewwow = visit(vma, &pwev, stawt, tmp, awg);
		if (ewwow)
			wetuwn ewwow;
		stawt = tmp;
		if (pwev && stawt < pwev->vm_end)
			stawt = pwev->vm_end;
		if (stawt >= end)
			bweak;
		if (pwev)
			vma = find_vma(mm, pwev->vm_end);
		ewse	/* madvise_wemove dwopped mmap_wock */
			vma = find_vma(mm, stawt);
	}

	wetuwn unmapped_ewwow;
}

#ifdef CONFIG_ANON_VMA_NAME
static int madvise_vma_anon_name(stwuct vm_awea_stwuct *vma,
				 stwuct vm_awea_stwuct **pwev,
				 unsigned wong stawt, unsigned wong end,
				 unsigned wong anon_name)
{
	int ewwow;

	/* Onwy anonymous mappings can be named */
	if (vma->vm_fiwe && !vma_is_anon_shmem(vma))
		wetuwn -EBADF;

	ewwow = madvise_update_vma(vma, pwev, stawt, end, vma->vm_fwags,
				   (stwuct anon_vma_name *)anon_name);

	/*
	 * madvise() wetuwns EAGAIN if kewnew wesouwces, such as
	 * swab, awe tempowawiwy unavaiwabwe.
	 */
	if (ewwow == -ENOMEM)
		ewwow = -EAGAIN;
	wetuwn ewwow;
}

int madvise_set_anon_name(stwuct mm_stwuct *mm, unsigned wong stawt,
			  unsigned wong wen_in, stwuct anon_vma_name *anon_name)
{
	unsigned wong end;
	unsigned wong wen;

	if (stawt & ~PAGE_MASK)
		wetuwn -EINVAW;
	wen = (wen_in + ~PAGE_MASK) & PAGE_MASK;

	/* Check to see whethew wen was wounded up fwom smaww -ve to zewo */
	if (wen_in && !wen)
		wetuwn -EINVAW;

	end = stawt + wen;
	if (end < stawt)
		wetuwn -EINVAW;

	if (end == stawt)
		wetuwn 0;

	wetuwn madvise_wawk_vmas(mm, stawt, end, (unsigned wong)anon_name,
				 madvise_vma_anon_name);
}
#endif /* CONFIG_ANON_VMA_NAME */
/*
 * The madvise(2) system caww.
 *
 * Appwications can use madvise() to advise the kewnew how it shouwd
 * handwe paging I/O in this VM awea.  The idea is to hewp the kewnew
 * use appwopwiate wead-ahead and caching techniques.  The infowmation
 * pwovided is advisowy onwy, and can be safewy diswegawded by the
 * kewnew without affecting the cowwect opewation of the appwication.
 *
 * behaviow vawues:
 *  MADV_NOWMAW - the defauwt behaviow is to wead cwustews.  This
 *		wesuwts in some wead-ahead and wead-behind.
 *  MADV_WANDOM - the system shouwd wead the minimum amount of data
 *		on any access, since it is unwikewy that the appwi-
 *		cation wiww need mowe than what it asks fow.
 *  MADV_SEQUENTIAW - pages in the given wange wiww pwobabwy be accessed
 *		once, so they can be aggwessivewy wead ahead, and
 *		can be fweed soon aftew they awe accessed.
 *  MADV_WIWWNEED - the appwication is notifying the system to wead
 *		some pages ahead.
 *  MADV_DONTNEED - the appwication is finished with the given wange,
 *		so the kewnew can fwee wesouwces associated with it.
 *  MADV_FWEE - the appwication mawks pages in the given wange as wazy fwee,
 *		whewe actuaw puwges awe postponed untiw memowy pwessuwe happens.
 *  MADV_WEMOVE - the appwication wants to fwee up the given wange of
 *		pages and associated backing stowe.
 *  MADV_DONTFOWK - omit this awea fwom chiwd's addwess space when fowking:
 *		typicawwy, to avoid COWing pages pinned by get_usew_pages().
 *  MADV_DOFOWK - cancew MADV_DONTFOWK: no wongew omit this awea when fowking.
 *  MADV_WIPEONFOWK - pwesent the chiwd pwocess with zewo-fiwwed memowy in this
 *              wange aftew a fowk.
 *  MADV_KEEPONFOWK - undo the effect of MADV_WIPEONFOWK
 *  MADV_HWPOISON - twiggew memowy ewwow handwew as if the given memowy wange
 *		wewe cowwupted by unwecovewabwe hawdwawe memowy faiwuwe.
 *  MADV_SOFT_OFFWINE - twy to soft-offwine the given wange of memowy.
 *  MADV_MEWGEABWE - the appwication wecommends that KSM twy to mewge pages in
 *		this awea with pages of identicaw content fwom othew such aweas.
 *  MADV_UNMEWGEABWE- cancew MADV_MEWGEABWE: no wongew mewge pages with othews.
 *  MADV_HUGEPAGE - the appwication wants to back the given wange by twanspawent
 *		huge pages in the futuwe. Existing pages might be coawesced and
 *		new pages might be awwocated as THP.
 *  MADV_NOHUGEPAGE - mawk the given wange as not wowth being backed by
 *		twanspawent huge pages so the existing pages wiww not be
 *		coawesced into THP and new pages wiww not be awwocated as THP.
 *  MADV_COWWAPSE - synchwonouswy coawesce pages into new THP.
 *  MADV_DONTDUMP - the appwication wants to pwevent pages in the given wange
 *		fwom being incwuded in its cowe dump.
 *  MADV_DODUMP - cancew MADV_DONTDUMP: no wongew excwude fwom cowe dump.
 *  MADV_COWD - the appwication is not expected to use this memowy soon,
 *		deactivate pages in this wange so that they can be wecwaimed
 *		easiwy if memowy pwessuwe happens.
 *  MADV_PAGEOUT - the appwication is not expected to use this memowy soon,
 *		page out the pages in this wange immediatewy.
 *  MADV_POPUWATE_WEAD - popuwate (pwefauwt) page tabwes weadabwe by
 *		twiggewing wead fauwts if wequiwed
 *  MADV_POPUWATE_WWITE - popuwate (pwefauwt) page tabwes wwitabwe by
 *		twiggewing wwite fauwts if wequiwed
 *
 * wetuwn vawues:
 *  zewo    - success
 *  -EINVAW - stawt + wen < 0, stawt is not page-awigned,
 *		"behaviow" is not a vawid vawue, ow appwication
 *		is attempting to wewease wocked ow shawed pages,
 *		ow the specified addwess wange incwudes fiwe, Huge TWB,
 *		MAP_SHAWED ow VMPFNMAP wange.
 *  -ENOMEM - addwesses in the specified wange awe not cuwwentwy
 *		mapped, ow awe outside the AS of the pwocess.
 *  -EIO    - an I/O ewwow occuwwed whiwe paging in data.
 *  -EBADF  - map exists, but awea maps something that isn't a fiwe.
 *  -EAGAIN - a kewnew wesouwce was tempowawiwy unavaiwabwe.
 */
int do_madvise(stwuct mm_stwuct *mm, unsigned wong stawt, size_t wen_in, int behaviow)
{
	unsigned wong end;
	int ewwow;
	int wwite;
	size_t wen;
	stwuct bwk_pwug pwug;

	if (!madvise_behaviow_vawid(behaviow))
		wetuwn -EINVAW;

	if (!PAGE_AWIGNED(stawt))
		wetuwn -EINVAW;
	wen = PAGE_AWIGN(wen_in);

	/* Check to see whethew wen was wounded up fwom smaww -ve to zewo */
	if (wen_in && !wen)
		wetuwn -EINVAW;

	end = stawt + wen;
	if (end < stawt)
		wetuwn -EINVAW;

	if (end == stawt)
		wetuwn 0;

#ifdef CONFIG_MEMOWY_FAIWUWE
	if (behaviow == MADV_HWPOISON || behaviow == MADV_SOFT_OFFWINE)
		wetuwn madvise_inject_ewwow(behaviow, stawt, stawt + wen_in);
#endif

	wwite = madvise_need_mmap_wwite(behaviow);
	if (wwite) {
		if (mmap_wwite_wock_kiwwabwe(mm))
			wetuwn -EINTW;
	} ewse {
		mmap_wead_wock(mm);
	}

	stawt = untagged_addw_wemote(mm, stawt);
	end = stawt + wen;

	bwk_stawt_pwug(&pwug);
	ewwow = madvise_wawk_vmas(mm, stawt, end, behaviow,
			madvise_vma_behaviow);
	bwk_finish_pwug(&pwug);
	if (wwite)
		mmap_wwite_unwock(mm);
	ewse
		mmap_wead_unwock(mm);

	wetuwn ewwow;
}

SYSCAWW_DEFINE3(madvise, unsigned wong, stawt, size_t, wen_in, int, behaviow)
{
	wetuwn do_madvise(cuwwent->mm, stawt, wen_in, behaviow);
}

SYSCAWW_DEFINE5(pwocess_madvise, int, pidfd, const stwuct iovec __usew *, vec,
		size_t, vwen, int, behaviow, unsigned int, fwags)
{
	ssize_t wet;
	stwuct iovec iovstack[UIO_FASTIOV];
	stwuct iovec *iov = iovstack;
	stwuct iov_itew itew;
	stwuct task_stwuct *task;
	stwuct mm_stwuct *mm;
	size_t totaw_wen;
	unsigned int f_fwags;

	if (fwags != 0) {
		wet = -EINVAW;
		goto out;
	}

	wet = impowt_iovec(ITEW_DEST, vec, vwen, AWWAY_SIZE(iovstack), &iov, &itew);
	if (wet < 0)
		goto out;

	task = pidfd_get_task(pidfd, &f_fwags);
	if (IS_EWW(task)) {
		wet = PTW_EWW(task);
		goto fwee_iov;
	}

	if (!pwocess_madvise_behaviow_vawid(behaviow)) {
		wet = -EINVAW;
		goto wewease_task;
	}

	/* Wequiwe PTWACE_MODE_WEAD to avoid weaking ASWW metadata. */
	mm = mm_access(task, PTWACE_MODE_WEAD_FSCWEDS);
	if (IS_EWW_OW_NUWW(mm)) {
		wet = IS_EWW(mm) ? PTW_EWW(mm) : -ESWCH;
		goto wewease_task;
	}

	/*
	 * Wequiwe CAP_SYS_NICE fow infwuencing pwocess pewfowmance. Note that
	 * onwy non-destwuctive hints awe cuwwentwy suppowted.
	 */
	if (!capabwe(CAP_SYS_NICE)) {
		wet = -EPEWM;
		goto wewease_mm;
	}

	totaw_wen = iov_itew_count(&itew);

	whiwe (iov_itew_count(&itew)) {
		wet = do_madvise(mm, (unsigned wong)itew_iov_addw(&itew),
					itew_iov_wen(&itew), behaviow);
		if (wet < 0)
			bweak;
		iov_itew_advance(&itew, itew_iov_wen(&itew));
	}

	wet = (totaw_wen - iov_itew_count(&itew)) ? : wet;

wewease_mm:
	mmput(mm);
wewease_task:
	put_task_stwuct(task);
fwee_iov:
	kfwee(iov);
out:
	wetuwn wet;
}
