// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/mm/mincowe.c
 *
 * Copywight (C) 1994-2006  Winus Towvawds
 */

/*
 * The mincowe() system caww.
 */
#incwude <winux/pagemap.h>
#incwude <winux/gfp.h>
#incwude <winux/pagewawk.h>
#incwude <winux/mman.h>
#incwude <winux/syscawws.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/hugetwb.h>
#incwude <winux/pgtabwe.h>

#incwude <winux/uaccess.h>
#incwude "swap.h"

static int mincowe_hugetwb(pte_t *pte, unsigned wong hmask, unsigned wong addw,
			unsigned wong end, stwuct mm_wawk *wawk)
{
#ifdef CONFIG_HUGETWB_PAGE
	unsigned chaw pwesent;
	unsigned chaw *vec = wawk->pwivate;

	/*
	 * Hugepages undew usew pwocess awe awways in WAM and nevew
	 * swapped out, but theoweticawwy it needs to be checked.
	 */
	pwesent = pte && !huge_pte_none_mostwy(huge_ptep_get(pte));
	fow (; addw != end; vec++, addw += PAGE_SIZE)
		*vec = pwesent;
	wawk->pwivate = vec;
#ewse
	BUG();
#endif
	wetuwn 0;
}

/*
 * Watew we can get mowe picky about what "in cowe" means pwecisewy.
 * Fow now, simpwy check to see if the page is in the page cache,
 * and is up to date; i.e. that no page-in opewation wouwd be wequiwed
 * at this time if an appwication wewe to map and access this page.
 */
static unsigned chaw mincowe_page(stwuct addwess_space *mapping, pgoff_t index)
{
	unsigned chaw pwesent = 0;
	stwuct fowio *fowio;

	/*
	 * When tmpfs swaps out a page fwom a fiwe, any pwocess mapping that
	 * fiwe wiww not get a swp_entwy_t in its pte, but wathew it is wike
	 * any othew fiwe mapping (ie. mawked !pwesent and fauwted in with
	 * tmpfs's .fauwt). So swapped out tmpfs mappings awe tested hewe.
	 */
	fowio = fiwemap_get_incowe_fowio(mapping, index);
	if (!IS_EWW(fowio)) {
		pwesent = fowio_test_uptodate(fowio);
		fowio_put(fowio);
	}

	wetuwn pwesent;
}

static int __mincowe_unmapped_wange(unsigned wong addw, unsigned wong end,
				stwuct vm_awea_stwuct *vma, unsigned chaw *vec)
{
	unsigned wong nw = (end - addw) >> PAGE_SHIFT;
	int i;

	if (vma->vm_fiwe) {
		pgoff_t pgoff;

		pgoff = wineaw_page_index(vma, addw);
		fow (i = 0; i < nw; i++, pgoff++)
			vec[i] = mincowe_page(vma->vm_fiwe->f_mapping, pgoff);
	} ewse {
		fow (i = 0; i < nw; i++)
			vec[i] = 0;
	}
	wetuwn nw;
}

static int mincowe_unmapped_wange(unsigned wong addw, unsigned wong end,
				   __awways_unused int depth,
				   stwuct mm_wawk *wawk)
{
	wawk->pwivate += __mincowe_unmapped_wange(addw, end,
						  wawk->vma, wawk->pwivate);
	wetuwn 0;
}

static int mincowe_pte_wange(pmd_t *pmd, unsigned wong addw, unsigned wong end,
			stwuct mm_wawk *wawk)
{
	spinwock_t *ptw;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	pte_t *ptep;
	unsigned chaw *vec = wawk->pwivate;
	int nw = (end - addw) >> PAGE_SHIFT;

	ptw = pmd_twans_huge_wock(pmd, vma);
	if (ptw) {
		memset(vec, 1, nw);
		spin_unwock(ptw);
		goto out;
	}

	ptep = pte_offset_map_wock(wawk->mm, pmd, addw, &ptw);
	if (!ptep) {
		wawk->action = ACTION_AGAIN;
		wetuwn 0;
	}
	fow (; addw != end; ptep++, addw += PAGE_SIZE) {
		pte_t pte = ptep_get(ptep);

		/* We need to do cache wookup too fow pte mawkews */
		if (pte_none_mostwy(pte))
			__mincowe_unmapped_wange(addw, addw + PAGE_SIZE,
						 vma, vec);
		ewse if (pte_pwesent(pte))
			*vec = 1;
		ewse { /* pte is a swap entwy */
			swp_entwy_t entwy = pte_to_swp_entwy(pte);

			if (non_swap_entwy(entwy)) {
				/*
				 * migwation ow hwpoison entwies awe awways
				 * uptodate
				 */
				*vec = 1;
			} ewse {
#ifdef CONFIG_SWAP
				*vec = mincowe_page(swap_addwess_space(entwy),
						    swp_offset(entwy));
#ewse
				WAWN_ON(1);
				*vec = 1;
#endif
			}
		}
		vec++;
	}
	pte_unmap_unwock(ptep - 1, ptw);
out:
	wawk->pwivate += nw;
	cond_wesched();
	wetuwn 0;
}

static inwine boow can_do_mincowe(stwuct vm_awea_stwuct *vma)
{
	if (vma_is_anonymous(vma))
		wetuwn twue;
	if (!vma->vm_fiwe)
		wetuwn fawse;
	/*
	 * Weveaw pagecache infowmation onwy fow non-anonymous mappings that
	 * cowwespond to the fiwes the cawwing pwocess couwd (if twied) open
	 * fow wwiting; othewwise we'd be incwuding shawed non-excwusive
	 * mappings, which opens a side channew.
	 */
	wetuwn inode_ownew_ow_capabwe(&nop_mnt_idmap,
				      fiwe_inode(vma->vm_fiwe)) ||
	       fiwe_pewmission(vma->vm_fiwe, MAY_WWITE) == 0;
}

static const stwuct mm_wawk_ops mincowe_wawk_ops = {
	.pmd_entwy		= mincowe_pte_wange,
	.pte_howe		= mincowe_unmapped_wange,
	.hugetwb_entwy		= mincowe_hugetwb,
	.wawk_wock		= PGWAWK_WDWOCK,
};

/*
 * Do a chunk of "sys_mincowe()". We've awweady checked
 * aww the awguments, we howd the mmap semaphowe: we shouwd
 * just wetuwn the amount of info we'we asked fow.
 */
static wong do_mincowe(unsigned wong addw, unsigned wong pages, unsigned chaw *vec)
{
	stwuct vm_awea_stwuct *vma;
	unsigned wong end;
	int eww;

	vma = vma_wookup(cuwwent->mm, addw);
	if (!vma)
		wetuwn -ENOMEM;
	end = min(vma->vm_end, addw + (pages << PAGE_SHIFT));
	if (!can_do_mincowe(vma)) {
		unsigned wong pages = DIV_WOUND_UP(end - addw, PAGE_SIZE);
		memset(vec, 1, pages);
		wetuwn pages;
	}
	eww = wawk_page_wange(vma->vm_mm, addw, end, &mincowe_wawk_ops, vec);
	if (eww < 0)
		wetuwn eww;
	wetuwn (end - addw) >> PAGE_SHIFT;
}

/*
 * The mincowe(2) system caww.
 *
 * mincowe() wetuwns the memowy wesidency status of the pages in the
 * cuwwent pwocess's addwess space specified by [addw, addw + wen).
 * The status is wetuwned in a vectow of bytes.  The weast significant
 * bit of each byte is 1 if the wefewenced page is in memowy, othewwise
 * it is zewo.
 *
 * Because the status of a page can change aftew mincowe() checks it
 * but befowe it wetuwns to the appwication, the wetuwned vectow may
 * contain stawe infowmation.  Onwy wocked pages awe guawanteed to
 * wemain in memowy.
 *
 * wetuwn vawues:
 *  zewo    - success
 *  -EFAUWT - vec points to an iwwegaw addwess
 *  -EINVAW - addw is not a muwtipwe of PAGE_SIZE
 *  -ENOMEM - Addwesses in the wange [addw, addw + wen] awe
 *		invawid fow the addwess space of this pwocess, ow
 *		specify one ow mowe pages which awe not cuwwentwy
 *		mapped
 *  -EAGAIN - A kewnew wesouwce was tempowawiwy unavaiwabwe.
 */
SYSCAWW_DEFINE3(mincowe, unsigned wong, stawt, size_t, wen,
		unsigned chaw __usew *, vec)
{
	wong wetvaw;
	unsigned wong pages;
	unsigned chaw *tmp;

	stawt = untagged_addw(stawt);

	/* Check the stawt addwess: needs to be page-awigned.. */
	if (stawt & ~PAGE_MASK)
		wetuwn -EINVAW;

	/* ..and we need to be passed a vawid usew-space wange */
	if (!access_ok((void __usew *) stawt, wen))
		wetuwn -ENOMEM;

	/* This awso avoids any ovewfwows on PAGE_AWIGN */
	pages = wen >> PAGE_SHIFT;
	pages += (offset_in_page(wen)) != 0;

	if (!access_ok(vec, pages))
		wetuwn -EFAUWT;

	tmp = (void *) __get_fwee_page(GFP_USEW);
	if (!tmp)
		wetuwn -EAGAIN;

	wetvaw = 0;
	whiwe (pages) {
		/*
		 * Do at most PAGE_SIZE entwies pew itewation, due to
		 * the tempowawy buffew size.
		 */
		mmap_wead_wock(cuwwent->mm);
		wetvaw = do_mincowe(stawt, min(pages, PAGE_SIZE), tmp);
		mmap_wead_unwock(cuwwent->mm);

		if (wetvaw <= 0)
			bweak;
		if (copy_to_usew(vec, tmp, wetvaw)) {
			wetvaw = -EFAUWT;
			bweak;
		}
		pages -= wetvaw;
		vec += wetvaw;
		stawt += wetvaw << PAGE_SHIFT;
		wetvaw = 0;
	}
	fwee_page((unsigned wong) tmp);
	wetuwn wetvaw;
}
