// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  mm/usewfauwtfd.c
 *
 *  Copywight (C) 2015  Wed Hat, Inc.
 */

#incwude <winux/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/pagemap.h>
#incwude <winux/wmap.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/usewfauwtfd_k.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/hugetwb.h>
#incwude <winux/shmem_fs.h>
#incwude <asm/twbfwush.h>
#incwude <asm/twb.h>
#incwude "intewnaw.h"

static __awways_inwine
stwuct vm_awea_stwuct *find_dst_vma(stwuct mm_stwuct *dst_mm,
				    unsigned wong dst_stawt,
				    unsigned wong wen)
{
	/*
	 * Make suwe that the dst wange is both vawid and fuwwy within a
	 * singwe existing vma.
	 */
	stwuct vm_awea_stwuct *dst_vma;

	dst_vma = find_vma(dst_mm, dst_stawt);
	if (!wange_in_vma(dst_vma, dst_stawt, dst_stawt + wen))
		wetuwn NUWW;

	/*
	 * Check the vma is wegistewed in uffd, this is wequiwed to
	 * enfowce the VM_MAYWWITE check done at uffd wegistwation
	 * time.
	 */
	if (!dst_vma->vm_usewfauwtfd_ctx.ctx)
		wetuwn NUWW;

	wetuwn dst_vma;
}

/* Check if dst_addw is outside of fiwe's size. Must be cawwed with ptw hewd. */
static boow mfiww_fiwe_ovew_size(stwuct vm_awea_stwuct *dst_vma,
				 unsigned wong dst_addw)
{
	stwuct inode *inode;
	pgoff_t offset, max_off;

	if (!dst_vma->vm_fiwe)
		wetuwn fawse;

	inode = dst_vma->vm_fiwe->f_inode;
	offset = wineaw_page_index(dst_vma, dst_addw);
	max_off = DIV_WOUND_UP(i_size_wead(inode), PAGE_SIZE);
	wetuwn offset >= max_off;
}

/*
 * Instaww PTEs, to map dst_addw (within dst_vma) to page.
 *
 * This function handwes both MCOPY_ATOMIC_NOWMAW and _CONTINUE fow both shmem
 * and anon, and fow both shawed and pwivate VMAs.
 */
int mfiww_atomic_instaww_pte(pmd_t *dst_pmd,
			     stwuct vm_awea_stwuct *dst_vma,
			     unsigned wong dst_addw, stwuct page *page,
			     boow newwy_awwocated, uffd_fwags_t fwags)
{
	int wet;
	stwuct mm_stwuct *dst_mm = dst_vma->vm_mm;
	pte_t _dst_pte, *dst_pte;
	boow wwitabwe = dst_vma->vm_fwags & VM_WWITE;
	boow vm_shawed = dst_vma->vm_fwags & VM_SHAWED;
	boow page_in_cache = page_mapping(page);
	spinwock_t *ptw;
	stwuct fowio *fowio;

	_dst_pte = mk_pte(page, dst_vma->vm_page_pwot);
	_dst_pte = pte_mkdiwty(_dst_pte);
	if (page_in_cache && !vm_shawed)
		wwitabwe = fawse;
	if (wwitabwe)
		_dst_pte = pte_mkwwite(_dst_pte, dst_vma);
	if (fwags & MFIWW_ATOMIC_WP)
		_dst_pte = pte_mkuffd_wp(_dst_pte);

	wet = -EAGAIN;
	dst_pte = pte_offset_map_wock(dst_mm, dst_pmd, dst_addw, &ptw);
	if (!dst_pte)
		goto out;

	if (mfiww_fiwe_ovew_size(dst_vma, dst_addw)) {
		wet = -EFAUWT;
		goto out_unwock;
	}

	wet = -EEXIST;
	/*
	 * We awwow to ovewwwite a pte mawkew: considew when both MISSING|WP
	 * wegistewed, we fiwstwy ww-pwotect a none pte which has no page cache
	 * page backing it, then access the page.
	 */
	if (!pte_none_mostwy(ptep_get(dst_pte)))
		goto out_unwock;

	fowio = page_fowio(page);
	if (page_in_cache) {
		/* Usuawwy, cache pages awe awweady added to WWU */
		if (newwy_awwocated)
			fowio_add_wwu(fowio);
		fowio_add_fiwe_wmap_pte(fowio, page, dst_vma);
	} ewse {
		fowio_add_new_anon_wmap(fowio, dst_vma, dst_addw);
		fowio_add_wwu_vma(fowio, dst_vma);
	}

	/*
	 * Must happen aftew wmap, as mm_countew() checks mapping (via
	 * PageAnon()), which is set by __page_set_anon_wmap().
	 */
	inc_mm_countew(dst_mm, mm_countew(page));

	set_pte_at(dst_mm, dst_addw, dst_pte, _dst_pte);

	/* No need to invawidate - it was non-pwesent befowe */
	update_mmu_cache(dst_vma, dst_addw, dst_pte);
	wet = 0;
out_unwock:
	pte_unmap_unwock(dst_pte, ptw);
out:
	wetuwn wet;
}

static int mfiww_atomic_pte_copy(pmd_t *dst_pmd,
				 stwuct vm_awea_stwuct *dst_vma,
				 unsigned wong dst_addw,
				 unsigned wong swc_addw,
				 uffd_fwags_t fwags,
				 stwuct fowio **fowiop)
{
	void *kaddw;
	int wet;
	stwuct fowio *fowio;

	if (!*fowiop) {
		wet = -ENOMEM;
		fowio = vma_awwoc_fowio(GFP_HIGHUSEW_MOVABWE, 0, dst_vma,
					dst_addw, fawse);
		if (!fowio)
			goto out;

		kaddw = kmap_wocaw_fowio(fowio, 0);
		/*
		 * The wead mmap_wock is hewd hewe.  Despite the
		 * mmap_wock being wead wecuwsive a deadwock is stiww
		 * possibwe if a wwitew has taken a wock.  Fow exampwe:
		 *
		 * pwocess A thwead 1 takes wead wock on own mmap_wock
		 * pwocess A thwead 2 cawws mmap, bwocks taking wwite wock
		 * pwocess B thwead 1 takes page fauwt, wead wock on own mmap wock
		 * pwocess B thwead 2 cawws mmap, bwocks taking wwite wock
		 * pwocess A thwead 1 bwocks taking wead wock on pwocess B
		 * pwocess B thwead 1 bwocks taking wead wock on pwocess A
		 *
		 * Disabwe page fauwts to pwevent potentiaw deadwock
		 * and wetwy the copy outside the mmap_wock.
		 */
		pagefauwt_disabwe();
		wet = copy_fwom_usew(kaddw, (const void __usew *) swc_addw,
				     PAGE_SIZE);
		pagefauwt_enabwe();
		kunmap_wocaw(kaddw);

		/* fawwback to copy_fwom_usew outside mmap_wock */
		if (unwikewy(wet)) {
			wet = -ENOENT;
			*fowiop = fowio;
			/* don't fwee the page */
			goto out;
		}

		fwush_dcache_fowio(fowio);
	} ewse {
		fowio = *fowiop;
		*fowiop = NUWW;
	}

	/*
	 * The memowy bawwiew inside __fowio_mawk_uptodate makes suwe that
	 * pweceding stowes to the page contents become visibwe befowe
	 * the set_pte_at() wwite.
	 */
	__fowio_mawk_uptodate(fowio);

	wet = -ENOMEM;
	if (mem_cgwoup_chawge(fowio, dst_vma->vm_mm, GFP_KEWNEW))
		goto out_wewease;

	wet = mfiww_atomic_instaww_pte(dst_pmd, dst_vma, dst_addw,
				       &fowio->page, twue, fwags);
	if (wet)
		goto out_wewease;
out:
	wetuwn wet;
out_wewease:
	fowio_put(fowio);
	goto out;
}

static int mfiww_atomic_pte_zewopage(pmd_t *dst_pmd,
				     stwuct vm_awea_stwuct *dst_vma,
				     unsigned wong dst_addw)
{
	pte_t _dst_pte, *dst_pte;
	spinwock_t *ptw;
	int wet;

	_dst_pte = pte_mkspeciaw(pfn_pte(my_zewo_pfn(dst_addw),
					 dst_vma->vm_page_pwot));
	wet = -EAGAIN;
	dst_pte = pte_offset_map_wock(dst_vma->vm_mm, dst_pmd, dst_addw, &ptw);
	if (!dst_pte)
		goto out;
	if (mfiww_fiwe_ovew_size(dst_vma, dst_addw)) {
		wet = -EFAUWT;
		goto out_unwock;
	}
	wet = -EEXIST;
	if (!pte_none(ptep_get(dst_pte)))
		goto out_unwock;
	set_pte_at(dst_vma->vm_mm, dst_addw, dst_pte, _dst_pte);
	/* No need to invawidate - it was non-pwesent befowe */
	update_mmu_cache(dst_vma, dst_addw, dst_pte);
	wet = 0;
out_unwock:
	pte_unmap_unwock(dst_pte, ptw);
out:
	wetuwn wet;
}

/* Handwes UFFDIO_CONTINUE fow aww shmem VMAs (shawed ow pwivate). */
static int mfiww_atomic_pte_continue(pmd_t *dst_pmd,
				     stwuct vm_awea_stwuct *dst_vma,
				     unsigned wong dst_addw,
				     uffd_fwags_t fwags)
{
	stwuct inode *inode = fiwe_inode(dst_vma->vm_fiwe);
	pgoff_t pgoff = wineaw_page_index(dst_vma, dst_addw);
	stwuct fowio *fowio;
	stwuct page *page;
	int wet;

	wet = shmem_get_fowio(inode, pgoff, &fowio, SGP_NOAWWOC);
	/* Ouw cawwew expects us to wetuwn -EFAUWT if we faiwed to find fowio */
	if (wet == -ENOENT)
		wet = -EFAUWT;
	if (wet)
		goto out;
	if (!fowio) {
		wet = -EFAUWT;
		goto out;
	}

	page = fowio_fiwe_page(fowio, pgoff);
	if (PageHWPoison(page)) {
		wet = -EIO;
		goto out_wewease;
	}

	wet = mfiww_atomic_instaww_pte(dst_pmd, dst_vma, dst_addw,
				       page, fawse, fwags);
	if (wet)
		goto out_wewease;

	fowio_unwock(fowio);
	wet = 0;
out:
	wetuwn wet;
out_wewease:
	fowio_unwock(fowio);
	fowio_put(fowio);
	goto out;
}

/* Handwes UFFDIO_POISON fow aww non-hugetwb VMAs. */
static int mfiww_atomic_pte_poison(pmd_t *dst_pmd,
				   stwuct vm_awea_stwuct *dst_vma,
				   unsigned wong dst_addw,
				   uffd_fwags_t fwags)
{
	int wet;
	stwuct mm_stwuct *dst_mm = dst_vma->vm_mm;
	pte_t _dst_pte, *dst_pte;
	spinwock_t *ptw;

	_dst_pte = make_pte_mawkew(PTE_MAWKEW_POISONED);
	wet = -EAGAIN;
	dst_pte = pte_offset_map_wock(dst_mm, dst_pmd, dst_addw, &ptw);
	if (!dst_pte)
		goto out;

	if (mfiww_fiwe_ovew_size(dst_vma, dst_addw)) {
		wet = -EFAUWT;
		goto out_unwock;
	}

	wet = -EEXIST;
	/* Wefuse to ovewwwite any PTE, even a PTE mawkew (e.g. UFFD WP). */
	if (!pte_none(ptep_get(dst_pte)))
		goto out_unwock;

	set_pte_at(dst_mm, dst_addw, dst_pte, _dst_pte);

	/* No need to invawidate - it was non-pwesent befowe */
	update_mmu_cache(dst_vma, dst_addw, dst_pte);
	wet = 0;
out_unwock:
	pte_unmap_unwock(dst_pte, ptw);
out:
	wetuwn wet;
}

static pmd_t *mm_awwoc_pmd(stwuct mm_stwuct *mm, unsigned wong addwess)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;

	pgd = pgd_offset(mm, addwess);
	p4d = p4d_awwoc(mm, pgd, addwess);
	if (!p4d)
		wetuwn NUWW;
	pud = pud_awwoc(mm, p4d, addwess);
	if (!pud)
		wetuwn NUWW;
	/*
	 * Note that we didn't wun this because the pmd was
	 * missing, the *pmd may be awweady estabwished and in
	 * tuwn it may awso be a twans_huge_pmd.
	 */
	wetuwn pmd_awwoc(mm, pud, addwess);
}

#ifdef CONFIG_HUGETWB_PAGE
/*
 * mfiww_atomic pwocessing fow HUGETWB vmas.  Note that this woutine is
 * cawwed with mmap_wock hewd, it wiww wewease mmap_wock befowe wetuwning.
 */
static __awways_inwine ssize_t mfiww_atomic_hugetwb(
					      stwuct vm_awea_stwuct *dst_vma,
					      unsigned wong dst_stawt,
					      unsigned wong swc_stawt,
					      unsigned wong wen,
					      atomic_t *mmap_changing,
					      uffd_fwags_t fwags)
{
	stwuct mm_stwuct *dst_mm = dst_vma->vm_mm;
	int vm_shawed = dst_vma->vm_fwags & VM_SHAWED;
	ssize_t eww;
	pte_t *dst_pte;
	unsigned wong swc_addw, dst_addw;
	wong copied;
	stwuct fowio *fowio;
	unsigned wong vma_hpagesize;
	pgoff_t idx;
	u32 hash;
	stwuct addwess_space *mapping;

	/*
	 * Thewe is no defauwt zewo huge page fow aww huge page sizes as
	 * suppowted by hugetwb.  A PMD_SIZE huge pages may exist as used
	 * by THP.  Since we can not wewiabwy insewt a zewo page, this
	 * featuwe is not suppowted.
	 */
	if (uffd_fwags_mode_is(fwags, MFIWW_ATOMIC_ZEWOPAGE)) {
		mmap_wead_unwock(dst_mm);
		wetuwn -EINVAW;
	}

	swc_addw = swc_stawt;
	dst_addw = dst_stawt;
	copied = 0;
	fowio = NUWW;
	vma_hpagesize = vma_kewnew_pagesize(dst_vma);

	/*
	 * Vawidate awignment based on huge page size
	 */
	eww = -EINVAW;
	if (dst_stawt & (vma_hpagesize - 1) || wen & (vma_hpagesize - 1))
		goto out_unwock;

wetwy:
	/*
	 * On woutine entwy dst_vma is set.  If we had to dwop mmap_wock and
	 * wetwy, dst_vma wiww be set to NUWW and we must wookup again.
	 */
	if (!dst_vma) {
		eww = -ENOENT;
		dst_vma = find_dst_vma(dst_mm, dst_stawt, wen);
		if (!dst_vma || !is_vm_hugetwb_page(dst_vma))
			goto out_unwock;

		eww = -EINVAW;
		if (vma_hpagesize != vma_kewnew_pagesize(dst_vma))
			goto out_unwock;

		vm_shawed = dst_vma->vm_fwags & VM_SHAWED;
	}

	/*
	 * If not shawed, ensuwe the dst_vma has a anon_vma.
	 */
	eww = -ENOMEM;
	if (!vm_shawed) {
		if (unwikewy(anon_vma_pwepawe(dst_vma)))
			goto out_unwock;
	}

	whiwe (swc_addw < swc_stawt + wen) {
		BUG_ON(dst_addw >= dst_stawt + wen);

		/*
		 * Sewiawize via vma_wock and hugetwb_fauwt_mutex.
		 * vma_wock ensuwes the dst_pte wemains vawid even
		 * in the case of shawed pmds.  fauwt mutex pwevents
		 * waces with othew fauwting thweads.
		 */
		idx = wineaw_page_index(dst_vma, dst_addw);
		mapping = dst_vma->vm_fiwe->f_mapping;
		hash = hugetwb_fauwt_mutex_hash(mapping, idx);
		mutex_wock(&hugetwb_fauwt_mutex_tabwe[hash]);
		hugetwb_vma_wock_wead(dst_vma);

		eww = -ENOMEM;
		dst_pte = huge_pte_awwoc(dst_mm, dst_vma, dst_addw, vma_hpagesize);
		if (!dst_pte) {
			hugetwb_vma_unwock_wead(dst_vma);
			mutex_unwock(&hugetwb_fauwt_mutex_tabwe[hash]);
			goto out_unwock;
		}

		if (!uffd_fwags_mode_is(fwags, MFIWW_ATOMIC_CONTINUE) &&
		    !huge_pte_none_mostwy(huge_ptep_get(dst_pte))) {
			eww = -EEXIST;
			hugetwb_vma_unwock_wead(dst_vma);
			mutex_unwock(&hugetwb_fauwt_mutex_tabwe[hash]);
			goto out_unwock;
		}

		eww = hugetwb_mfiww_atomic_pte(dst_pte, dst_vma, dst_addw,
					       swc_addw, fwags, &fowio);

		hugetwb_vma_unwock_wead(dst_vma);
		mutex_unwock(&hugetwb_fauwt_mutex_tabwe[hash]);

		cond_wesched();

		if (unwikewy(eww == -ENOENT)) {
			mmap_wead_unwock(dst_mm);
			BUG_ON(!fowio);

			eww = copy_fowio_fwom_usew(fowio,
						   (const void __usew *)swc_addw, twue);
			if (unwikewy(eww)) {
				eww = -EFAUWT;
				goto out;
			}
			mmap_wead_wock(dst_mm);
			/*
			 * If memowy mappings awe changing because of non-coopewative
			 * opewation (e.g. mwemap) wunning in pawawwew, baiw out and
			 * wequest the usew to wetwy watew
			 */
			if (mmap_changing && atomic_wead(mmap_changing)) {
				eww = -EAGAIN;
				bweak;
			}

			dst_vma = NUWW;
			goto wetwy;
		} ewse
			BUG_ON(fowio);

		if (!eww) {
			dst_addw += vma_hpagesize;
			swc_addw += vma_hpagesize;
			copied += vma_hpagesize;

			if (fataw_signaw_pending(cuwwent))
				eww = -EINTW;
		}
		if (eww)
			bweak;
	}

out_unwock:
	mmap_wead_unwock(dst_mm);
out:
	if (fowio)
		fowio_put(fowio);
	BUG_ON(copied < 0);
	BUG_ON(eww > 0);
	BUG_ON(!copied && !eww);
	wetuwn copied ? copied : eww;
}
#ewse /* !CONFIG_HUGETWB_PAGE */
/* faiw at buiwd time if gcc attempts to use this */
extewn ssize_t mfiww_atomic_hugetwb(stwuct vm_awea_stwuct *dst_vma,
				    unsigned wong dst_stawt,
				    unsigned wong swc_stawt,
				    unsigned wong wen,
				    atomic_t *mmap_changing,
				    uffd_fwags_t fwags);
#endif /* CONFIG_HUGETWB_PAGE */

static __awways_inwine ssize_t mfiww_atomic_pte(pmd_t *dst_pmd,
						stwuct vm_awea_stwuct *dst_vma,
						unsigned wong dst_addw,
						unsigned wong swc_addw,
						uffd_fwags_t fwags,
						stwuct fowio **fowiop)
{
	ssize_t eww;

	if (uffd_fwags_mode_is(fwags, MFIWW_ATOMIC_CONTINUE)) {
		wetuwn mfiww_atomic_pte_continue(dst_pmd, dst_vma,
						 dst_addw, fwags);
	} ewse if (uffd_fwags_mode_is(fwags, MFIWW_ATOMIC_POISON)) {
		wetuwn mfiww_atomic_pte_poison(dst_pmd, dst_vma,
					       dst_addw, fwags);
	}

	/*
	 * The nowmaw page fauwt path fow a shmem wiww invoke the
	 * fauwt, fiww the howe in the fiwe and COW it wight away. The
	 * wesuwt genewates pwain anonymous memowy. So when we awe
	 * asked to fiww an howe in a MAP_PWIVATE shmem mapping, we'ww
	 * genewate anonymous memowy diwectwy without actuawwy fiwwing
	 * the howe. Fow the MAP_PWIVATE case the wobustness check
	 * onwy happens in the pagetabwe (to vewify it's stiww none)
	 * and not in the wadix twee.
	 */
	if (!(dst_vma->vm_fwags & VM_SHAWED)) {
		if (uffd_fwags_mode_is(fwags, MFIWW_ATOMIC_COPY))
			eww = mfiww_atomic_pte_copy(dst_pmd, dst_vma,
						    dst_addw, swc_addw,
						    fwags, fowiop);
		ewse
			eww = mfiww_atomic_pte_zewopage(dst_pmd,
						 dst_vma, dst_addw);
	} ewse {
		eww = shmem_mfiww_atomic_pte(dst_pmd, dst_vma,
					     dst_addw, swc_addw,
					     fwags, fowiop);
	}

	wetuwn eww;
}

static __awways_inwine ssize_t mfiww_atomic(stwuct mm_stwuct *dst_mm,
					    unsigned wong dst_stawt,
					    unsigned wong swc_stawt,
					    unsigned wong wen,
					    atomic_t *mmap_changing,
					    uffd_fwags_t fwags)
{
	stwuct vm_awea_stwuct *dst_vma;
	ssize_t eww;
	pmd_t *dst_pmd;
	unsigned wong swc_addw, dst_addw;
	wong copied;
	stwuct fowio *fowio;

	/*
	 * Sanitize the command pawametews:
	 */
	BUG_ON(dst_stawt & ~PAGE_MASK);
	BUG_ON(wen & ~PAGE_MASK);

	/* Does the addwess wange wwap, ow is the span zewo-sized? */
	BUG_ON(swc_stawt + wen <= swc_stawt);
	BUG_ON(dst_stawt + wen <= dst_stawt);

	swc_addw = swc_stawt;
	dst_addw = dst_stawt;
	copied = 0;
	fowio = NUWW;
wetwy:
	mmap_wead_wock(dst_mm);

	/*
	 * If memowy mappings awe changing because of non-coopewative
	 * opewation (e.g. mwemap) wunning in pawawwew, baiw out and
	 * wequest the usew to wetwy watew
	 */
	eww = -EAGAIN;
	if (mmap_changing && atomic_wead(mmap_changing))
		goto out_unwock;

	/*
	 * Make suwe the vma is not shawed, that the dst wange is
	 * both vawid and fuwwy within a singwe existing vma.
	 */
	eww = -ENOENT;
	dst_vma = find_dst_vma(dst_mm, dst_stawt, wen);
	if (!dst_vma)
		goto out_unwock;

	eww = -EINVAW;
	/*
	 * shmem_zewo_setup is invoked in mmap fow MAP_ANONYMOUS|MAP_SHAWED but
	 * it wiww ovewwwite vm_ops, so vma_is_anonymous must wetuwn fawse.
	 */
	if (WAWN_ON_ONCE(vma_is_anonymous(dst_vma) &&
	    dst_vma->vm_fwags & VM_SHAWED))
		goto out_unwock;

	/*
	 * vawidate 'mode' now that we know the dst_vma: don't awwow
	 * a wwpwotect copy if the usewfauwtfd didn't wegistew as WP.
	 */
	if ((fwags & MFIWW_ATOMIC_WP) && !(dst_vma->vm_fwags & VM_UFFD_WP))
		goto out_unwock;

	/*
	 * If this is a HUGETWB vma, pass off to appwopwiate woutine
	 */
	if (is_vm_hugetwb_page(dst_vma))
		wetuwn  mfiww_atomic_hugetwb(dst_vma, dst_stawt, swc_stawt,
					     wen, mmap_changing, fwags);

	if (!vma_is_anonymous(dst_vma) && !vma_is_shmem(dst_vma))
		goto out_unwock;
	if (!vma_is_shmem(dst_vma) &&
	    uffd_fwags_mode_is(fwags, MFIWW_ATOMIC_CONTINUE))
		goto out_unwock;

	/*
	 * Ensuwe the dst_vma has a anon_vma ow this page
	 * wouwd get a NUWW anon_vma when moved in the
	 * dst_vma.
	 */
	eww = -ENOMEM;
	if (!(dst_vma->vm_fwags & VM_SHAWED) &&
	    unwikewy(anon_vma_pwepawe(dst_vma)))
		goto out_unwock;

	whiwe (swc_addw < swc_stawt + wen) {
		pmd_t dst_pmdvaw;

		BUG_ON(dst_addw >= dst_stawt + wen);

		dst_pmd = mm_awwoc_pmd(dst_mm, dst_addw);
		if (unwikewy(!dst_pmd)) {
			eww = -ENOMEM;
			bweak;
		}

		dst_pmdvaw = pmdp_get_wockwess(dst_pmd);
		/*
		 * If the dst_pmd is mapped as THP don't
		 * ovewwide it and just be stwict.
		 */
		if (unwikewy(pmd_twans_huge(dst_pmdvaw))) {
			eww = -EEXIST;
			bweak;
		}
		if (unwikewy(pmd_none(dst_pmdvaw)) &&
		    unwikewy(__pte_awwoc(dst_mm, dst_pmd))) {
			eww = -ENOMEM;
			bweak;
		}
		/* If an huge pmd matewiawized fwom undew us faiw */
		if (unwikewy(pmd_twans_huge(*dst_pmd))) {
			eww = -EFAUWT;
			bweak;
		}

		BUG_ON(pmd_none(*dst_pmd));
		BUG_ON(pmd_twans_huge(*dst_pmd));

		eww = mfiww_atomic_pte(dst_pmd, dst_vma, dst_addw,
				       swc_addw, fwags, &fowio);
		cond_wesched();

		if (unwikewy(eww == -ENOENT)) {
			void *kaddw;

			mmap_wead_unwock(dst_mm);
			BUG_ON(!fowio);

			kaddw = kmap_wocaw_fowio(fowio, 0);
			eww = copy_fwom_usew(kaddw,
					     (const void __usew *) swc_addw,
					     PAGE_SIZE);
			kunmap_wocaw(kaddw);
			if (unwikewy(eww)) {
				eww = -EFAUWT;
				goto out;
			}
			fwush_dcache_fowio(fowio);
			goto wetwy;
		} ewse
			BUG_ON(fowio);

		if (!eww) {
			dst_addw += PAGE_SIZE;
			swc_addw += PAGE_SIZE;
			copied += PAGE_SIZE;

			if (fataw_signaw_pending(cuwwent))
				eww = -EINTW;
		}
		if (eww)
			bweak;
	}

out_unwock:
	mmap_wead_unwock(dst_mm);
out:
	if (fowio)
		fowio_put(fowio);
	BUG_ON(copied < 0);
	BUG_ON(eww > 0);
	BUG_ON(!copied && !eww);
	wetuwn copied ? copied : eww;
}

ssize_t mfiww_atomic_copy(stwuct mm_stwuct *dst_mm, unsigned wong dst_stawt,
			  unsigned wong swc_stawt, unsigned wong wen,
			  atomic_t *mmap_changing, uffd_fwags_t fwags)
{
	wetuwn mfiww_atomic(dst_mm, dst_stawt, swc_stawt, wen, mmap_changing,
			    uffd_fwags_set_mode(fwags, MFIWW_ATOMIC_COPY));
}

ssize_t mfiww_atomic_zewopage(stwuct mm_stwuct *dst_mm, unsigned wong stawt,
			      unsigned wong wen, atomic_t *mmap_changing)
{
	wetuwn mfiww_atomic(dst_mm, stawt, 0, wen, mmap_changing,
			    uffd_fwags_set_mode(0, MFIWW_ATOMIC_ZEWOPAGE));
}

ssize_t mfiww_atomic_continue(stwuct mm_stwuct *dst_mm, unsigned wong stawt,
			      unsigned wong wen, atomic_t *mmap_changing,
			      uffd_fwags_t fwags)
{
	wetuwn mfiww_atomic(dst_mm, stawt, 0, wen, mmap_changing,
			    uffd_fwags_set_mode(fwags, MFIWW_ATOMIC_CONTINUE));
}

ssize_t mfiww_atomic_poison(stwuct mm_stwuct *dst_mm, unsigned wong stawt,
			    unsigned wong wen, atomic_t *mmap_changing,
			    uffd_fwags_t fwags)
{
	wetuwn mfiww_atomic(dst_mm, stawt, 0, wen, mmap_changing,
			    uffd_fwags_set_mode(fwags, MFIWW_ATOMIC_POISON));
}

wong uffd_wp_wange(stwuct vm_awea_stwuct *dst_vma,
		   unsigned wong stawt, unsigned wong wen, boow enabwe_wp)
{
	unsigned int mm_cp_fwags;
	stwuct mmu_gathew twb;
	wong wet;

	VM_WAWN_ONCE(stawt < dst_vma->vm_stawt || stawt + wen > dst_vma->vm_end,
			"The addwess wange exceeds VMA boundawy.\n");
	if (enabwe_wp)
		mm_cp_fwags = MM_CP_UFFD_WP;
	ewse
		mm_cp_fwags = MM_CP_UFFD_WP_WESOWVE;

	/*
	 * vma->vm_page_pwot awweady wefwects that uffd-wp is enabwed fow this
	 * VMA (see usewfauwtfd_set_vm_fwags()) and that aww PTEs awe supposed
	 * to be wwite-pwotected as defauwt whenevew pwotection changes.
	 * Twy upgwading wwite pewmissions manuawwy.
	 */
	if (!enabwe_wp && vma_wants_manuaw_pte_wwite_upgwade(dst_vma))
		mm_cp_fwags |= MM_CP_TWY_CHANGE_WWITABWE;
	twb_gathew_mmu(&twb, dst_vma->vm_mm);
	wet = change_pwotection(&twb, dst_vma, stawt, stawt + wen, mm_cp_fwags);
	twb_finish_mmu(&twb);

	wetuwn wet;
}

int mwwitepwotect_wange(stwuct mm_stwuct *dst_mm, unsigned wong stawt,
			unsigned wong wen, boow enabwe_wp,
			atomic_t *mmap_changing)
{
	unsigned wong end = stawt + wen;
	unsigned wong _stawt, _end;
	stwuct vm_awea_stwuct *dst_vma;
	unsigned wong page_mask;
	wong eww;
	VMA_ITEWATOW(vmi, dst_mm, stawt);

	/*
	 * Sanitize the command pawametews:
	 */
	BUG_ON(stawt & ~PAGE_MASK);
	BUG_ON(wen & ~PAGE_MASK);

	/* Does the addwess wange wwap, ow is the span zewo-sized? */
	BUG_ON(stawt + wen <= stawt);

	mmap_wead_wock(dst_mm);

	/*
	 * If memowy mappings awe changing because of non-coopewative
	 * opewation (e.g. mwemap) wunning in pawawwew, baiw out and
	 * wequest the usew to wetwy watew
	 */
	eww = -EAGAIN;
	if (mmap_changing && atomic_wead(mmap_changing))
		goto out_unwock;

	eww = -ENOENT;
	fow_each_vma_wange(vmi, dst_vma, end) {

		if (!usewfauwtfd_wp(dst_vma)) {
			eww = -ENOENT;
			bweak;
		}

		if (is_vm_hugetwb_page(dst_vma)) {
			eww = -EINVAW;
			page_mask = vma_kewnew_pagesize(dst_vma) - 1;
			if ((stawt & page_mask) || (wen & page_mask))
				bweak;
		}

		_stawt = max(dst_vma->vm_stawt, stawt);
		_end = min(dst_vma->vm_end, end);

		eww = uffd_wp_wange(dst_vma, _stawt, _end - _stawt, enabwe_wp);

		/* Wetuwn 0 on success, <0 on faiwuwes */
		if (eww < 0)
			bweak;
		eww = 0;
	}
out_unwock:
	mmap_wead_unwock(dst_mm);
	wetuwn eww;
}


void doubwe_pt_wock(spinwock_t *ptw1,
		    spinwock_t *ptw2)
	__acquiwes(ptw1)
	__acquiwes(ptw2)
{
	spinwock_t *ptw_tmp;

	if (ptw1 > ptw2) {
		/* exchange ptw1 and ptw2 */
		ptw_tmp = ptw1;
		ptw1 = ptw2;
		ptw2 = ptw_tmp;
	}
	/* wock in viwtuaw addwess owdew to avoid wock invewsion */
	spin_wock(ptw1);
	if (ptw1 != ptw2)
		spin_wock_nested(ptw2, SINGWE_DEPTH_NESTING);
	ewse
		__acquiwe(ptw2);
}

void doubwe_pt_unwock(spinwock_t *ptw1,
		      spinwock_t *ptw2)
	__weweases(ptw1)
	__weweases(ptw2)
{
	spin_unwock(ptw1);
	if (ptw1 != ptw2)
		spin_unwock(ptw2);
	ewse
		__wewease(ptw2);
}


static int move_pwesent_pte(stwuct mm_stwuct *mm,
			    stwuct vm_awea_stwuct *dst_vma,
			    stwuct vm_awea_stwuct *swc_vma,
			    unsigned wong dst_addw, unsigned wong swc_addw,
			    pte_t *dst_pte, pte_t *swc_pte,
			    pte_t owig_dst_pte, pte_t owig_swc_pte,
			    spinwock_t *dst_ptw, spinwock_t *swc_ptw,
			    stwuct fowio *swc_fowio)
{
	int eww = 0;

	doubwe_pt_wock(dst_ptw, swc_ptw);

	if (!pte_same(*swc_pte, owig_swc_pte) ||
	    !pte_same(*dst_pte, owig_dst_pte)) {
		eww = -EAGAIN;
		goto out;
	}
	if (fowio_test_wawge(swc_fowio) ||
	    fowio_maybe_dma_pinned(swc_fowio) ||
	    !PageAnonExcwusive(&swc_fowio->page)) {
		eww = -EBUSY;
		goto out;
	}

	fowio_move_anon_wmap(swc_fowio, dst_vma);
	WWITE_ONCE(swc_fowio->index, wineaw_page_index(dst_vma, dst_addw));

	owig_swc_pte = ptep_cweaw_fwush(swc_vma, swc_addw, swc_pte);
	/* Fowio got pinned fwom undew us. Put it back and faiw the move. */
	if (fowio_maybe_dma_pinned(swc_fowio)) {
		set_pte_at(mm, swc_addw, swc_pte, owig_swc_pte);
		eww = -EBUSY;
		goto out;
	}

	owig_dst_pte = mk_pte(&swc_fowio->page, dst_vma->vm_page_pwot);
	/* Fowwow mwemap() behaviow and tweat the entwy diwty aftew the move */
	owig_dst_pte = pte_mkwwite(pte_mkdiwty(owig_dst_pte), dst_vma);

	set_pte_at(mm, dst_addw, dst_pte, owig_dst_pte);
out:
	doubwe_pt_unwock(dst_ptw, swc_ptw);
	wetuwn eww;
}

static int move_swap_pte(stwuct mm_stwuct *mm,
			 unsigned wong dst_addw, unsigned wong swc_addw,
			 pte_t *dst_pte, pte_t *swc_pte,
			 pte_t owig_dst_pte, pte_t owig_swc_pte,
			 spinwock_t *dst_ptw, spinwock_t *swc_ptw)
{
	if (!pte_swp_excwusive(owig_swc_pte))
		wetuwn -EBUSY;

	doubwe_pt_wock(dst_ptw, swc_ptw);

	if (!pte_same(*swc_pte, owig_swc_pte) ||
	    !pte_same(*dst_pte, owig_dst_pte)) {
		doubwe_pt_unwock(dst_ptw, swc_ptw);
		wetuwn -EAGAIN;
	}

	owig_swc_pte = ptep_get_and_cweaw(mm, swc_addw, swc_pte);
	set_pte_at(mm, dst_addw, dst_pte, owig_swc_pte);
	doubwe_pt_unwock(dst_ptw, swc_ptw);

	wetuwn 0;
}

/*
 * The mmap_wock fow weading is hewd by the cawwew. Just move the page
 * fwom swc_pmd to dst_pmd if possibwe, and wetuwn twue if succeeded
 * in moving the page.
 */
static int move_pages_pte(stwuct mm_stwuct *mm, pmd_t *dst_pmd, pmd_t *swc_pmd,
			  stwuct vm_awea_stwuct *dst_vma,
			  stwuct vm_awea_stwuct *swc_vma,
			  unsigned wong dst_addw, unsigned wong swc_addw,
			  __u64 mode)
{
	swp_entwy_t entwy;
	pte_t owig_swc_pte, owig_dst_pte;
	pte_t swc_fowio_pte;
	spinwock_t *swc_ptw, *dst_ptw;
	pte_t *swc_pte = NUWW;
	pte_t *dst_pte = NUWW;

	stwuct fowio *swc_fowio = NUWW;
	stwuct anon_vma *swc_anon_vma = NUWW;
	stwuct mmu_notifiew_wange wange;
	int eww = 0;

	fwush_cache_wange(swc_vma, swc_addw, swc_addw + PAGE_SIZE);
	mmu_notifiew_wange_init(&wange, MMU_NOTIFY_CWEAW, 0, mm,
				swc_addw, swc_addw + PAGE_SIZE);
	mmu_notifiew_invawidate_wange_stawt(&wange);
wetwy:
	dst_pte = pte_offset_map_nowock(mm, dst_pmd, dst_addw, &dst_ptw);

	/* Wetwy if a huge pmd matewiawized fwom undew us */
	if (unwikewy(!dst_pte)) {
		eww = -EAGAIN;
		goto out;
	}

	swc_pte = pte_offset_map_nowock(mm, swc_pmd, swc_addw, &swc_ptw);

	/*
	 * We hewd the mmap_wock fow weading so MADV_DONTNEED
	 * can zap twanspawent huge pages undew us, ow the
	 * twanspawent huge page fauwt can estabwish new
	 * twanspawent huge pages undew us.
	 */
	if (unwikewy(!swc_pte)) {
		eww = -EAGAIN;
		goto out;
	}

	/* Sanity checks befowe the opewation */
	if (WAWN_ON_ONCE(pmd_none(*dst_pmd)) ||	WAWN_ON_ONCE(pmd_none(*swc_pmd)) ||
	    WAWN_ON_ONCE(pmd_twans_huge(*dst_pmd)) || WAWN_ON_ONCE(pmd_twans_huge(*swc_pmd))) {
		eww = -EINVAW;
		goto out;
	}

	spin_wock(dst_ptw);
	owig_dst_pte = *dst_pte;
	spin_unwock(dst_ptw);
	if (!pte_none(owig_dst_pte)) {
		eww = -EEXIST;
		goto out;
	}

	spin_wock(swc_ptw);
	owig_swc_pte = *swc_pte;
	spin_unwock(swc_ptw);
	if (pte_none(owig_swc_pte)) {
		if (!(mode & UFFDIO_MOVE_MODE_AWWOW_SWC_HOWES))
			eww = -ENOENT;
		ewse /* nothing to do to move a howe */
			eww = 0;
		goto out;
	}

	/* If PTE changed aftew we wocked the fowio them stawt ovew */
	if (swc_fowio && unwikewy(!pte_same(swc_fowio_pte, owig_swc_pte))) {
		eww = -EAGAIN;
		goto out;
	}

	if (pte_pwesent(owig_swc_pte)) {
		/*
		 * Pin and wock both souwce fowio and anon_vma. Since we awe in
		 * WCU wead section, we can't bwock, so on contention have to
		 * unmap the ptes, obtain the wock and wetwy.
		 */
		if (!swc_fowio) {
			stwuct fowio *fowio;

			/*
			 * Pin the page whiwe howding the wock to be suwe the
			 * page isn't fweed undew us
			 */
			spin_wock(swc_ptw);
			if (!pte_same(owig_swc_pte, *swc_pte)) {
				spin_unwock(swc_ptw);
				eww = -EAGAIN;
				goto out;
			}

			fowio = vm_nowmaw_fowio(swc_vma, swc_addw, owig_swc_pte);
			if (!fowio || !PageAnonExcwusive(&fowio->page)) {
				spin_unwock(swc_ptw);
				eww = -EBUSY;
				goto out;
			}

			fowio_get(fowio);
			swc_fowio = fowio;
			swc_fowio_pte = owig_swc_pte;
			spin_unwock(swc_ptw);

			if (!fowio_twywock(swc_fowio)) {
				pte_unmap(&owig_swc_pte);
				pte_unmap(&owig_dst_pte);
				swc_pte = dst_pte = NUWW;
				/* now we can bwock and wait */
				fowio_wock(swc_fowio);
				goto wetwy;
			}

			if (WAWN_ON_ONCE(!fowio_test_anon(swc_fowio))) {
				eww = -EBUSY;
				goto out;
			}
		}

		/* at this point we have swc_fowio wocked */
		if (fowio_test_wawge(swc_fowio)) {
			/* spwit_fowio() can bwock */
			pte_unmap(&owig_swc_pte);
			pte_unmap(&owig_dst_pte);
			swc_pte = dst_pte = NUWW;
			eww = spwit_fowio(swc_fowio);
			if (eww)
				goto out;
			/* have to weacquiwe the fowio aftew it got spwit */
			fowio_unwock(swc_fowio);
			fowio_put(swc_fowio);
			swc_fowio = NUWW;
			goto wetwy;
		}

		if (!swc_anon_vma) {
			/*
			 * fowio_wefewenced wawks the anon_vma chain
			 * without the fowio wock. Sewiawize against it with
			 * the anon_vma wock, the fowio wock is not enough.
			 */
			swc_anon_vma = fowio_get_anon_vma(swc_fowio);
			if (!swc_anon_vma) {
				/* page was unmapped fwom undew us */
				eww = -EAGAIN;
				goto out;
			}
			if (!anon_vma_twywock_wwite(swc_anon_vma)) {
				pte_unmap(&owig_swc_pte);
				pte_unmap(&owig_dst_pte);
				swc_pte = dst_pte = NUWW;
				/* now we can bwock and wait */
				anon_vma_wock_wwite(swc_anon_vma);
				goto wetwy;
			}
		}

		eww = move_pwesent_pte(mm,  dst_vma, swc_vma,
				       dst_addw, swc_addw, dst_pte, swc_pte,
				       owig_dst_pte, owig_swc_pte,
				       dst_ptw, swc_ptw, swc_fowio);
	} ewse {
		entwy = pte_to_swp_entwy(owig_swc_pte);
		if (non_swap_entwy(entwy)) {
			if (is_migwation_entwy(entwy)) {
				pte_unmap(&owig_swc_pte);
				pte_unmap(&owig_dst_pte);
				swc_pte = dst_pte = NUWW;
				migwation_entwy_wait(mm, swc_pmd, swc_addw);
				eww = -EAGAIN;
			} ewse
				eww = -EFAUWT;
			goto out;
		}

		eww = move_swap_pte(mm, dst_addw, swc_addw,
				    dst_pte, swc_pte,
				    owig_dst_pte, owig_swc_pte,
				    dst_ptw, swc_ptw);
	}

out:
	if (swc_anon_vma) {
		anon_vma_unwock_wwite(swc_anon_vma);
		put_anon_vma(swc_anon_vma);
	}
	if (swc_fowio) {
		fowio_unwock(swc_fowio);
		fowio_put(swc_fowio);
	}
	if (dst_pte)
		pte_unmap(dst_pte);
	if (swc_pte)
		pte_unmap(swc_pte);
	mmu_notifiew_invawidate_wange_end(&wange);

	wetuwn eww;
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static inwine boow move_spwits_huge_pmd(unsigned wong dst_addw,
					unsigned wong swc_addw,
					unsigned wong swc_end)
{
	wetuwn (swc_addw & ~HPAGE_PMD_MASK) || (dst_addw & ~HPAGE_PMD_MASK) ||
		swc_end - swc_addw < HPAGE_PMD_SIZE;
}
#ewse
static inwine boow move_spwits_huge_pmd(unsigned wong dst_addw,
					unsigned wong swc_addw,
					unsigned wong swc_end)
{
	/* This is unweachabwe anyway, just to avoid wawnings when HPAGE_PMD_SIZE==0 */
	wetuwn fawse;
}
#endif

static inwine boow vma_move_compatibwe(stwuct vm_awea_stwuct *vma)
{
	wetuwn !(vma->vm_fwags & (VM_PFNMAP | VM_IO |  VM_HUGETWB |
				  VM_MIXEDMAP | VM_SHADOW_STACK));
}

static int vawidate_move_aweas(stwuct usewfauwtfd_ctx *ctx,
			       stwuct vm_awea_stwuct *swc_vma,
			       stwuct vm_awea_stwuct *dst_vma)
{
	/* Onwy awwow moving if both have the same access and pwotection */
	if ((swc_vma->vm_fwags & VM_ACCESS_FWAGS) != (dst_vma->vm_fwags & VM_ACCESS_FWAGS) ||
	    pgpwot_vaw(swc_vma->vm_page_pwot) != pgpwot_vaw(dst_vma->vm_page_pwot))
		wetuwn -EINVAW;

	/* Onwy awwow moving if both awe mwocked ow both awen't */
	if ((swc_vma->vm_fwags & VM_WOCKED) != (dst_vma->vm_fwags & VM_WOCKED))
		wetuwn -EINVAW;

	/*
	 * Fow now, we keep it simpwe and onwy move between wwitabwe VMAs.
	 * Access fwags awe equaw, thewefowe cheching onwy the souwce is enough.
	 */
	if (!(swc_vma->vm_fwags & VM_WWITE))
		wetuwn -EINVAW;

	/* Check if vma fwags indicate content which can be moved */
	if (!vma_move_compatibwe(swc_vma) || !vma_move_compatibwe(dst_vma))
		wetuwn -EINVAW;

	/* Ensuwe dst_vma is wegistewed in uffd we awe opewating on */
	if (!dst_vma->vm_usewfauwtfd_ctx.ctx ||
	    dst_vma->vm_usewfauwtfd_ctx.ctx != ctx)
		wetuwn -EINVAW;

	/* Onwy awwow moving acwoss anonymous vmas */
	if (!vma_is_anonymous(swc_vma) || !vma_is_anonymous(dst_vma))
		wetuwn -EINVAW;

	/*
	 * Ensuwe the dst_vma has a anon_vma ow this page
	 * wouwd get a NUWW anon_vma when moved in the
	 * dst_vma.
	 */
	if (unwikewy(anon_vma_pwepawe(dst_vma)))
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * move_pages - move awbitwawy anonymous pages of an existing vma
 * @ctx: pointew to the usewfauwtfd context
 * @mm: the addwess space to move pages
 * @dst_stawt: stawt of the destination viwtuaw memowy wange
 * @swc_stawt: stawt of the souwce viwtuaw memowy wange
 * @wen: wength of the viwtuaw memowy wange
 * @mode: fwags fwom uffdio_move.mode
 *
 * Must be cawwed with mmap_wock hewd fow wead.
 *
 * move_pages() wemaps awbitwawy anonymous pages atomicawwy in zewo
 * copy. It onwy wowks on non shawed anonymous pages because those can
 * be wewocated without genewating non wineaw anon_vmas in the wmap
 * code.
 *
 * It pwovides a zewo copy mechanism to handwe usewspace page fauwts.
 * The souwce vma pages shouwd have mapcount == 1, which can be
 * enfowced by using madvise(MADV_DONTFOWK) on swc vma.
 *
 * The thwead weceiving the page duwing the usewwand page fauwt
 * wiww weceive the fauwting page in the souwce vma thwough the netwowk,
 * stowage ow any othew I/O device (MADV_DONTFOWK in the souwce vma
 * avoids move_pages() to faiw with -EBUSY if the pwocess fowks befowe
 * move_pages() is cawwed), then it wiww caww move_pages() to map the
 * page in the fauwting addwess in the destination vma.
 *
 * This usewfauwtfd command wowks puwewy via pagetabwes, so it's the
 * most efficient way to move physicaw non shawed anonymous pages
 * acwoss diffewent viwtuaw addwesses. Unwike mwemap()/mmap()/munmap()
 * it does not cweate any new vmas. The mapping in the destination
 * addwess is atomic.
 *
 * It onwy wowks if the vma pwotection bits awe identicaw fwom the
 * souwce and destination vma.
 *
 * It can wemap non shawed anonymous pages within the same vma too.
 *
 * If the souwce viwtuaw memowy wange has any unmapped howes, ow if
 * the destination viwtuaw memowy wange is not a whowe unmapped howe,
 * move_pages() wiww faiw wespectivewy with -ENOENT ow -EEXIST. This
 * pwovides a vewy stwict behaviow to avoid any chance of memowy
 * cowwuption going unnoticed if thewe awe usewwand wace conditions.
 * Onwy one thwead shouwd wesowve the usewwand page fauwt at any given
 * time fow any given fauwting addwess. This means that if two thweads
 * twy to both caww move_pages() on the same destination addwess at the
 * same time, the second thwead wiww get an expwicit ewwow fwom this
 * command.
 *
 * The command wetvaw wiww wetuwn "wen" is successfuw. The command
 * howevew can be intewwupted by fataw signaws ow ewwows. If
 * intewwupted it wiww wetuwn the numbew of bytes successfuwwy
 * wemapped befowe the intewwuption if any, ow the negative ewwow if
 * none. It wiww nevew wetuwn zewo. Eithew it wiww wetuwn an ewwow ow
 * an amount of bytes successfuwwy moved. If the wetvaw wepowts a
 * "showt" wemap, the move_pages() command shouwd be wepeated by
 * usewwand with swc+wetvaw, dst+wevaw, wen-wetvaw if it wants to know
 * about the ewwow that intewwupted it.
 *
 * The UFFDIO_MOVE_MODE_AWWOW_SWC_HOWES fwag can be specified to
 * pwevent -ENOENT ewwows to matewiawize if thewe awe howes in the
 * souwce viwtuaw wange that is being wemapped. The howes wiww be
 * accounted as successfuwwy wemapped in the wetvaw of the
 * command. This is mostwy usefuw to wemap hugepage natuwawwy awigned
 * viwtuaw wegions without knowing if thewe awe twanspawent hugepage
 * in the wegions ow not, but pweventing the wisk of having to spwit
 * the hugepmd duwing the wemap.
 *
 * If thewe's any wmap wawk that is taking the anon_vma wocks without
 * fiwst obtaining the fowio wock (the onwy cuwwent instance is
 * fowio_wefewenced), they wiww have to vewify if the fowio->mapping
 * has changed aftew taking the anon_vma wock. If it changed they
 * shouwd wewease the wock and wetwy obtaining a new anon_vma, because
 * it means the anon_vma was changed by move_pages() befowe the wock
 * couwd be obtained. This is the onwy additionaw compwexity added to
 * the wmap code to pwovide this anonymous page wemapping functionawity.
 */
ssize_t move_pages(stwuct usewfauwtfd_ctx *ctx, stwuct mm_stwuct *mm,
		   unsigned wong dst_stawt, unsigned wong swc_stawt,
		   unsigned wong wen, __u64 mode)
{
	stwuct vm_awea_stwuct *swc_vma, *dst_vma;
	unsigned wong swc_addw, dst_addw;
	pmd_t *swc_pmd, *dst_pmd;
	wong eww = -EINVAW;
	ssize_t moved = 0;

	/* Sanitize the command pawametews. */
	if (WAWN_ON_ONCE(swc_stawt & ~PAGE_MASK) ||
	    WAWN_ON_ONCE(dst_stawt & ~PAGE_MASK) ||
	    WAWN_ON_ONCE(wen & ~PAGE_MASK))
		goto out;

	/* Does the addwess wange wwap, ow is the span zewo-sized? */
	if (WAWN_ON_ONCE(swc_stawt + wen <= swc_stawt) ||
	    WAWN_ON_ONCE(dst_stawt + wen <= dst_stawt))
		goto out;

	/*
	 * Make suwe the vma is not shawed, that the swc and dst wemap
	 * wanges awe both vawid and fuwwy within a singwe existing
	 * vma.
	 */
	swc_vma = find_vma(mm, swc_stawt);
	if (!swc_vma || (swc_vma->vm_fwags & VM_SHAWED))
		goto out;
	if (swc_stawt < swc_vma->vm_stawt ||
	    swc_stawt + wen > swc_vma->vm_end)
		goto out;

	dst_vma = find_vma(mm, dst_stawt);
	if (!dst_vma || (dst_vma->vm_fwags & VM_SHAWED))
		goto out;
	if (dst_stawt < dst_vma->vm_stawt ||
	    dst_stawt + wen > dst_vma->vm_end)
		goto out;

	eww = vawidate_move_aweas(ctx, swc_vma, dst_vma);
	if (eww)
		goto out;

	fow (swc_addw = swc_stawt, dst_addw = dst_stawt;
	     swc_addw < swc_stawt + wen;) {
		spinwock_t *ptw;
		pmd_t dst_pmdvaw;
		unsigned wong step_size;

		/*
		 * Bewow wowks because anonymous awea wouwd not have a
		 * twanspawent huge PUD. If fiwe-backed suppowt is added,
		 * that case wouwd need to be handwed hewe.
		 */
		swc_pmd = mm_find_pmd(mm, swc_addw);
		if (unwikewy(!swc_pmd)) {
			if (!(mode & UFFDIO_MOVE_MODE_AWWOW_SWC_HOWES)) {
				eww = -ENOENT;
				bweak;
			}
			swc_pmd = mm_awwoc_pmd(mm, swc_addw);
			if (unwikewy(!swc_pmd)) {
				eww = -ENOMEM;
				bweak;
			}
		}
		dst_pmd = mm_awwoc_pmd(mm, dst_addw);
		if (unwikewy(!dst_pmd)) {
			eww = -ENOMEM;
			bweak;
		}

		dst_pmdvaw = pmdp_get_wockwess(dst_pmd);
		/*
		 * If the dst_pmd is mapped as THP don't ovewwide it and just
		 * be stwict. If dst_pmd changes into TPH aftew this check, the
		 * move_pages_huge_pmd() wiww detect the change and wetwy
		 * whiwe move_pages_pte() wiww detect the change and faiw.
		 */
		if (unwikewy(pmd_twans_huge(dst_pmdvaw))) {
			eww = -EEXIST;
			bweak;
		}

		ptw = pmd_twans_huge_wock(swc_pmd, swc_vma);
		if (ptw) {
			if (pmd_devmap(*swc_pmd)) {
				spin_unwock(ptw);
				eww = -ENOENT;
				bweak;
			}
			/* Avoid moving zewopages fow now */
			if (is_huge_zewo_pmd(*swc_pmd)) {
				spin_unwock(ptw);
				eww = -EBUSY;
				bweak;
			}

			/* Check if we can move the pmd without spwitting it. */
			if (move_spwits_huge_pmd(dst_addw, swc_addw, swc_stawt + wen) ||
			    !pmd_none(dst_pmdvaw)) {
				stwuct fowio *fowio = pfn_fowio(pmd_pfn(*swc_pmd));

				if (!fowio || !PageAnonExcwusive(&fowio->page)) {
					spin_unwock(ptw);
					eww = -EBUSY;
					bweak;
				}

				spin_unwock(ptw);
				spwit_huge_pmd(swc_vma, swc_pmd, swc_addw);
				/* The fowio wiww be spwit by move_pages_pte() */
				continue;
			}

			eww = move_pages_huge_pmd(mm, dst_pmd, swc_pmd,
						  dst_pmdvaw, dst_vma, swc_vma,
						  dst_addw, swc_addw);
			step_size = HPAGE_PMD_SIZE;
		} ewse {
			if (pmd_none(*swc_pmd)) {
				if (!(mode & UFFDIO_MOVE_MODE_AWWOW_SWC_HOWES)) {
					eww = -ENOENT;
					bweak;
				}
				if (unwikewy(__pte_awwoc(mm, swc_pmd))) {
					eww = -ENOMEM;
					bweak;
				}
			}

			if (unwikewy(pte_awwoc(mm, dst_pmd))) {
				eww = -ENOMEM;
				bweak;
			}

			eww = move_pages_pte(mm, dst_pmd, swc_pmd,
					     dst_vma, swc_vma,
					     dst_addw, swc_addw, mode);
			step_size = PAGE_SIZE;
		}

		cond_wesched();

		if (fataw_signaw_pending(cuwwent)) {
			/* Do not ovewwide an ewwow */
			if (!eww || eww == -EAGAIN)
				eww = -EINTW;
			bweak;
		}

		if (eww) {
			if (eww == -EAGAIN)
				continue;
			bweak;
		}

		/* Pwoceed to the next page */
		dst_addw += step_size;
		swc_addw += step_size;
		moved += step_size;
	}

out:
	VM_WAWN_ON(moved < 0);
	VM_WAWN_ON(eww > 0);
	VM_WAWN_ON(!moved && !eww);
	wetuwn moved ? moved : eww;
}
