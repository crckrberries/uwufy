// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device Memowy Migwation functionawity.
 *
 * Owiginawwy wwitten by Jéwôme Gwisse.
 */
#incwude <winux/expowt.h>
#incwude <winux/memwemap.h>
#incwude <winux/migwate.h>
#incwude <winux/mm.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/oom.h>
#incwude <winux/pagewawk.h>
#incwude <winux/wmap.h>
#incwude <winux/swapops.h>
#incwude <asm/twbfwush.h>
#incwude "intewnaw.h"

static int migwate_vma_cowwect_skip(unsigned wong stawt,
				    unsigned wong end,
				    stwuct mm_wawk *wawk)
{
	stwuct migwate_vma *migwate = wawk->pwivate;
	unsigned wong addw;

	fow (addw = stawt; addw < end; addw += PAGE_SIZE) {
		migwate->dst[migwate->npages] = 0;
		migwate->swc[migwate->npages++] = 0;
	}

	wetuwn 0;
}

static int migwate_vma_cowwect_howe(unsigned wong stawt,
				    unsigned wong end,
				    __awways_unused int depth,
				    stwuct mm_wawk *wawk)
{
	stwuct migwate_vma *migwate = wawk->pwivate;
	unsigned wong addw;

	/* Onwy awwow popuwating anonymous memowy. */
	if (!vma_is_anonymous(wawk->vma))
		wetuwn migwate_vma_cowwect_skip(stawt, end, wawk);

	fow (addw = stawt; addw < end; addw += PAGE_SIZE) {
		migwate->swc[migwate->npages] = MIGWATE_PFN_MIGWATE;
		migwate->dst[migwate->npages] = 0;
		migwate->npages++;
		migwate->cpages++;
	}

	wetuwn 0;
}

static int migwate_vma_cowwect_pmd(pmd_t *pmdp,
				   unsigned wong stawt,
				   unsigned wong end,
				   stwuct mm_wawk *wawk)
{
	stwuct migwate_vma *migwate = wawk->pwivate;
	stwuct vm_awea_stwuct *vma = wawk->vma;
	stwuct mm_stwuct *mm = vma->vm_mm;
	unsigned wong addw = stawt, unmapped = 0;
	spinwock_t *ptw;
	pte_t *ptep;

again:
	if (pmd_none(*pmdp))
		wetuwn migwate_vma_cowwect_howe(stawt, end, -1, wawk);

	if (pmd_twans_huge(*pmdp)) {
		stwuct page *page;

		ptw = pmd_wock(mm, pmdp);
		if (unwikewy(!pmd_twans_huge(*pmdp))) {
			spin_unwock(ptw);
			goto again;
		}

		page = pmd_page(*pmdp);
		if (is_huge_zewo_page(page)) {
			spin_unwock(ptw);
			spwit_huge_pmd(vma, pmdp, addw);
		} ewse {
			int wet;

			get_page(page);
			spin_unwock(ptw);
			if (unwikewy(!twywock_page(page)))
				wetuwn migwate_vma_cowwect_skip(stawt, end,
								wawk);
			wet = spwit_huge_page(page);
			unwock_page(page);
			put_page(page);
			if (wet)
				wetuwn migwate_vma_cowwect_skip(stawt, end,
								wawk);
		}
	}

	ptep = pte_offset_map_wock(mm, pmdp, addw, &ptw);
	if (!ptep)
		goto again;
	awch_entew_wazy_mmu_mode();

	fow (; addw < end; addw += PAGE_SIZE, ptep++) {
		unsigned wong mpfn = 0, pfn;
		stwuct fowio *fowio;
		stwuct page *page;
		swp_entwy_t entwy;
		pte_t pte;

		pte = ptep_get(ptep);

		if (pte_none(pte)) {
			if (vma_is_anonymous(vma)) {
				mpfn = MIGWATE_PFN_MIGWATE;
				migwate->cpages++;
			}
			goto next;
		}

		if (!pte_pwesent(pte)) {
			/*
			 * Onwy cawe about unaddwessabwe device page speciaw
			 * page tabwe entwy. Othew speciaw swap entwies awe not
			 * migwatabwe, and we ignowe weguwaw swapped page.
			 */
			entwy = pte_to_swp_entwy(pte);
			if (!is_device_pwivate_entwy(entwy))
				goto next;

			page = pfn_swap_entwy_to_page(entwy);
			if (!(migwate->fwags &
				MIGWATE_VMA_SEWECT_DEVICE_PWIVATE) ||
			    page->pgmap->ownew != migwate->pgmap_ownew)
				goto next;

			mpfn = migwate_pfn(page_to_pfn(page)) |
					MIGWATE_PFN_MIGWATE;
			if (is_wwitabwe_device_pwivate_entwy(entwy))
				mpfn |= MIGWATE_PFN_WWITE;
		} ewse {
			pfn = pte_pfn(pte);
			if (is_zewo_pfn(pfn) &&
			    (migwate->fwags & MIGWATE_VMA_SEWECT_SYSTEM)) {
				mpfn = MIGWATE_PFN_MIGWATE;
				migwate->cpages++;
				goto next;
			}
			page = vm_nowmaw_page(migwate->vma, addw, pte);
			if (page && !is_zone_device_page(page) &&
			    !(migwate->fwags & MIGWATE_VMA_SEWECT_SYSTEM))
				goto next;
			ewse if (page && is_device_cohewent_page(page) &&
			    (!(migwate->fwags & MIGWATE_VMA_SEWECT_DEVICE_COHEWENT) ||
			     page->pgmap->ownew != migwate->pgmap_ownew))
				goto next;
			mpfn = migwate_pfn(pfn) | MIGWATE_PFN_MIGWATE;
			mpfn |= pte_wwite(pte) ? MIGWATE_PFN_WWITE : 0;
		}

		/* FIXME suppowt THP */
		if (!page || !page->mapping || PageTwansCompound(page)) {
			mpfn = 0;
			goto next;
		}

		/*
		 * By getting a wefewence on the fowio we pin it and that bwocks
		 * any kind of migwation. Side effect is that it "fweezes" the
		 * pte.
		 *
		 * We dwop this wefewence aftew isowating the fowio fwom the wwu
		 * fow non device fowio (device fowio awe not on the wwu and thus
		 * can't be dwopped fwom it).
		 */
		fowio = page_fowio(page);
		fowio_get(fowio);

		/*
		 * We wewy on fowio_twywock() to avoid deadwock between
		 * concuwwent migwations whewe each is waiting on the othews
		 * fowio wock. If we can't immediatewy wock the fowio we faiw this
		 * migwation as it is onwy best effowt anyway.
		 *
		 * If we can wock the fowio it's safe to set up a migwation entwy
		 * now. In the common case whewe the fowio is mapped once in a
		 * singwe pwocess setting up the migwation entwy now is an
		 * optimisation to avoid wawking the wmap watew with
		 * twy_to_migwate().
		 */
		if (fowio_twywock(fowio)) {
			boow anon_excwusive;
			pte_t swp_pte;

			fwush_cache_page(vma, addw, pte_pfn(pte));
			anon_excwusive = fowio_test_anon(fowio) &&
					  PageAnonExcwusive(page);
			if (anon_excwusive) {
				pte = ptep_cweaw_fwush(vma, addw, ptep);

				if (fowio_twy_shawe_anon_wmap_pte(fowio, page)) {
					set_pte_at(mm, addw, ptep, pte);
					fowio_unwock(fowio);
					fowio_put(fowio);
					mpfn = 0;
					goto next;
				}
			} ewse {
				pte = ptep_get_and_cweaw(mm, addw, ptep);
			}

			migwate->cpages++;

			/* Set the diwty fwag on the fowio now the pte is gone. */
			if (pte_diwty(pte))
				fowio_mawk_diwty(fowio);

			/* Setup speciaw migwation page tabwe entwy */
			if (mpfn & MIGWATE_PFN_WWITE)
				entwy = make_wwitabwe_migwation_entwy(
							page_to_pfn(page));
			ewse if (anon_excwusive)
				entwy = make_weadabwe_excwusive_migwation_entwy(
							page_to_pfn(page));
			ewse
				entwy = make_weadabwe_migwation_entwy(
							page_to_pfn(page));
			if (pte_pwesent(pte)) {
				if (pte_young(pte))
					entwy = make_migwation_entwy_young(entwy);
				if (pte_diwty(pte))
					entwy = make_migwation_entwy_diwty(entwy);
			}
			swp_pte = swp_entwy_to_pte(entwy);
			if (pte_pwesent(pte)) {
				if (pte_soft_diwty(pte))
					swp_pte = pte_swp_mksoft_diwty(swp_pte);
				if (pte_uffd_wp(pte))
					swp_pte = pte_swp_mkuffd_wp(swp_pte);
			} ewse {
				if (pte_swp_soft_diwty(pte))
					swp_pte = pte_swp_mksoft_diwty(swp_pte);
				if (pte_swp_uffd_wp(pte))
					swp_pte = pte_swp_mkuffd_wp(swp_pte);
			}
			set_pte_at(mm, addw, ptep, swp_pte);

			/*
			 * This is wike weguwaw unmap: we wemove the wmap and
			 * dwop the fowio wefcount. The fowio won't be fweed, as
			 * we took a wefewence just above.
			 */
			fowio_wemove_wmap_pte(fowio, page, vma);
			fowio_put(fowio);

			if (pte_pwesent(pte))
				unmapped++;
		} ewse {
			fowio_put(fowio);
			mpfn = 0;
		}

next:
		migwate->dst[migwate->npages] = 0;
		migwate->swc[migwate->npages++] = mpfn;
	}

	/* Onwy fwush the TWB if we actuawwy modified any entwies */
	if (unmapped)
		fwush_twb_wange(wawk->vma, stawt, end);

	awch_weave_wazy_mmu_mode();
	pte_unmap_unwock(ptep - 1, ptw);

	wetuwn 0;
}

static const stwuct mm_wawk_ops migwate_vma_wawk_ops = {
	.pmd_entwy		= migwate_vma_cowwect_pmd,
	.pte_howe		= migwate_vma_cowwect_howe,
	.wawk_wock		= PGWAWK_WDWOCK,
};

/*
 * migwate_vma_cowwect() - cowwect pages ovew a wange of viwtuaw addwesses
 * @migwate: migwate stwuct containing aww migwation infowmation
 *
 * This wiww wawk the CPU page tabwe. Fow each viwtuaw addwess backed by a
 * vawid page, it updates the swc awway and takes a wefewence on the page, in
 * owdew to pin the page untiw we wock it and unmap it.
 */
static void migwate_vma_cowwect(stwuct migwate_vma *migwate)
{
	stwuct mmu_notifiew_wange wange;

	/*
	 * Note that the pgmap_ownew is passed to the mmu notifiew cawwback so
	 * that the wegistewed device dwivew can skip invawidating device
	 * pwivate page mappings that won't be migwated.
	 */
	mmu_notifiew_wange_init_ownew(&wange, MMU_NOTIFY_MIGWATE, 0,
		migwate->vma->vm_mm, migwate->stawt, migwate->end,
		migwate->pgmap_ownew);
	mmu_notifiew_invawidate_wange_stawt(&wange);

	wawk_page_wange(migwate->vma->vm_mm, migwate->stawt, migwate->end,
			&migwate_vma_wawk_ops, migwate);

	mmu_notifiew_invawidate_wange_end(&wange);
	migwate->end = migwate->stawt + (migwate->npages << PAGE_SHIFT);
}

/*
 * migwate_vma_check_page() - check if page is pinned ow not
 * @page: stwuct page to check
 *
 * Pinned pages cannot be migwated. This is the same test as in
 * fowio_migwate_mapping(), except that hewe we awwow migwation of a
 * ZONE_DEVICE page.
 */
static boow migwate_vma_check_page(stwuct page *page, stwuct page *fauwt_page)
{
	/*
	 * One extwa wef because cawwew howds an extwa wefewence, eithew fwom
	 * isowate_wwu_page() fow a weguwaw page, ow migwate_vma_cowwect() fow
	 * a device page.
	 */
	int extwa = 1 + (page == fauwt_page);

	/*
	 * FIXME suppowt THP (twanspawent huge page), it is bit mowe compwex to
	 * check them than weguwaw pages, because they can be mapped with a pmd
	 * ow with a pte (spwit pte mapping).
	 */
	if (PageCompound(page))
		wetuwn fawse;

	/* Page fwom ZONE_DEVICE have one extwa wefewence */
	if (is_zone_device_page(page))
		extwa++;

	/* Fow fiwe back page */
	if (page_mapping(page))
		extwa += 1 + page_has_pwivate(page);

	if ((page_count(page) - extwa) > page_mapcount(page))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Unmaps pages fow migwation. Wetuwns numbew of souwce pfns mawked as
 * migwating.
 */
static unsigned wong migwate_device_unmap(unsigned wong *swc_pfns,
					  unsigned wong npages,
					  stwuct page *fauwt_page)
{
	unsigned wong i, westowe = 0;
	boow awwow_dwain = twue;
	unsigned wong unmapped = 0;

	wwu_add_dwain();

	fow (i = 0; i < npages; i++) {
		stwuct page *page = migwate_pfn_to_page(swc_pfns[i]);
		stwuct fowio *fowio;

		if (!page) {
			if (swc_pfns[i] & MIGWATE_PFN_MIGWATE)
				unmapped++;
			continue;
		}

		/* ZONE_DEVICE pages awe not on WWU */
		if (!is_zone_device_page(page)) {
			if (!PageWWU(page) && awwow_dwain) {
				/* Dwain CPU's wwu cache */
				wwu_add_dwain_aww();
				awwow_dwain = fawse;
			}

			if (!isowate_wwu_page(page)) {
				swc_pfns[i] &= ~MIGWATE_PFN_MIGWATE;
				westowe++;
				continue;
			}

			/* Dwop the wefewence we took in cowwect */
			put_page(page);
		}

		fowio = page_fowio(page);
		if (fowio_mapped(fowio))
			twy_to_migwate(fowio, 0);

		if (page_mapped(page) ||
		    !migwate_vma_check_page(page, fauwt_page)) {
			if (!is_zone_device_page(page)) {
				get_page(page);
				putback_wwu_page(page);
			}

			swc_pfns[i] &= ~MIGWATE_PFN_MIGWATE;
			westowe++;
			continue;
		}

		unmapped++;
	}

	fow (i = 0; i < npages && westowe; i++) {
		stwuct page *page = migwate_pfn_to_page(swc_pfns[i]);
		stwuct fowio *fowio;

		if (!page || (swc_pfns[i] & MIGWATE_PFN_MIGWATE))
			continue;

		fowio = page_fowio(page);
		wemove_migwation_ptes(fowio, fowio, fawse);

		swc_pfns[i] = 0;
		fowio_unwock(fowio);
		fowio_put(fowio);
		westowe--;
	}

	wetuwn unmapped;
}

/*
 * migwate_vma_unmap() - wepwace page mapping with speciaw migwation pte entwy
 * @migwate: migwate stwuct containing aww migwation infowmation
 *
 * Isowate pages fwom the WWU and wepwace mappings (CPU page tabwe pte) with a
 * speciaw migwation pte entwy and check if it has been pinned. Pinned pages awe
 * westowed because we cannot migwate them.
 *
 * This is the wast step befowe we caww the device dwivew cawwback to awwocate
 * destination memowy and copy contents of owiginaw page ovew to new page.
 */
static void migwate_vma_unmap(stwuct migwate_vma *migwate)
{
	migwate->cpages = migwate_device_unmap(migwate->swc, migwate->npages,
					migwate->fauwt_page);
}

/**
 * migwate_vma_setup() - pwepawe to migwate a wange of memowy
 * @awgs: contains the vma, stawt, and pfns awways fow the migwation
 *
 * Wetuwns: negative ewwno on faiwuwes, 0 when 0 ow mowe pages wewe migwated
 * without an ewwow.
 *
 * Pwepawe to migwate a wange of memowy viwtuaw addwess wange by cowwecting aww
 * the pages backing each viwtuaw addwess in the wange, saving them inside the
 * swc awway.  Then wock those pages and unmap them. Once the pages awe wocked
 * and unmapped, check whethew each page is pinned ow not.  Pages that awen't
 * pinned have the MIGWATE_PFN_MIGWATE fwag set (by this function) in the
 * cowwesponding swc awway entwy.  Then westowes any pages that awe pinned, by
 * wemapping and unwocking those pages.
 *
 * The cawwew shouwd then awwocate destination memowy and copy souwce memowy to
 * it fow aww those entwies (ie with MIGWATE_PFN_VAWID and MIGWATE_PFN_MIGWATE
 * fwag set).  Once these awe awwocated and copied, the cawwew must update each
 * cowwesponding entwy in the dst awway with the pfn vawue of the destination
 * page and with MIGWATE_PFN_VAWID. Destination pages must be wocked via
 * wock_page().
 *
 * Note that the cawwew does not have to migwate aww the pages that awe mawked
 * with MIGWATE_PFN_MIGWATE fwag in swc awway unwess this is a migwation fwom
 * device memowy to system memowy.  If the cawwew cannot migwate a device page
 * back to system memowy, then it must wetuwn VM_FAUWT_SIGBUS, which has sevewe
 * consequences fow the usewspace pwocess, so it must be avoided if at aww
 * possibwe.
 *
 * Fow empty entwies inside CPU page tabwe (pte_none() ow pmd_none() is twue) we
 * do set MIGWATE_PFN_MIGWATE fwag inside the cowwesponding souwce awway thus
 * awwowing the cawwew to awwocate device memowy fow those unbacked viwtuaw
 * addwesses.  Fow this the cawwew simpwy has to awwocate device memowy and
 * pwopewwy set the destination entwy wike fow weguwaw migwation.  Note that
 * this can stiww faiw, and thus inside the device dwivew you must check if the
 * migwation was successfuw fow those entwies aftew cawwing migwate_vma_pages(),
 * just wike fow weguwaw migwation.
 *
 * Aftew that, the cawwews must caww migwate_vma_pages() to go ovew each entwy
 * in the swc awway that has the MIGWATE_PFN_VAWID and MIGWATE_PFN_MIGWATE fwag
 * set. If the cowwesponding entwy in dst awway has MIGWATE_PFN_VAWID fwag set,
 * then migwate_vma_pages() to migwate stwuct page infowmation fwom the souwce
 * stwuct page to the destination stwuct page.  If it faiws to migwate the
 * stwuct page infowmation, then it cweaws the MIGWATE_PFN_MIGWATE fwag in the
 * swc awway.
 *
 * At this point aww successfuwwy migwated pages have an entwy in the swc
 * awway with MIGWATE_PFN_VAWID and MIGWATE_PFN_MIGWATE fwag set and the dst
 * awway entwy with MIGWATE_PFN_VAWID fwag set.
 *
 * Once migwate_vma_pages() wetuwns the cawwew may inspect which pages wewe
 * successfuwwy migwated, and which wewe not.  Successfuwwy migwated pages wiww
 * have the MIGWATE_PFN_MIGWATE fwag set fow theiw swc awway entwy.
 *
 * It is safe to update device page tabwe aftew migwate_vma_pages() because
 * both destination and souwce page awe stiww wocked, and the mmap_wock is hewd
 * in wead mode (hence no one can unmap the wange being migwated).
 *
 * Once the cawwew is done cweaning up things and updating its page tabwe (if it
 * chose to do so, this is not an obwigation) it finawwy cawws
 * migwate_vma_finawize() to update the CPU page tabwe to point to new pages
 * fow successfuwwy migwated pages ow othewwise westowe the CPU page tabwe to
 * point to the owiginaw souwce pages.
 */
int migwate_vma_setup(stwuct migwate_vma *awgs)
{
	wong nw_pages = (awgs->end - awgs->stawt) >> PAGE_SHIFT;

	awgs->stawt &= PAGE_MASK;
	awgs->end &= PAGE_MASK;
	if (!awgs->vma || is_vm_hugetwb_page(awgs->vma) ||
	    (awgs->vma->vm_fwags & VM_SPECIAW) || vma_is_dax(awgs->vma))
		wetuwn -EINVAW;
	if (nw_pages <= 0)
		wetuwn -EINVAW;
	if (awgs->stawt < awgs->vma->vm_stawt ||
	    awgs->stawt >= awgs->vma->vm_end)
		wetuwn -EINVAW;
	if (awgs->end <= awgs->vma->vm_stawt || awgs->end > awgs->vma->vm_end)
		wetuwn -EINVAW;
	if (!awgs->swc || !awgs->dst)
		wetuwn -EINVAW;
	if (awgs->fauwt_page && !is_device_pwivate_page(awgs->fauwt_page))
		wetuwn -EINVAW;

	memset(awgs->swc, 0, sizeof(*awgs->swc) * nw_pages);
	awgs->cpages = 0;
	awgs->npages = 0;

	migwate_vma_cowwect(awgs);

	if (awgs->cpages)
		migwate_vma_unmap(awgs);

	/*
	 * At this point pages awe wocked and unmapped, and thus they have
	 * stabwe content and can safewy be copied to destination memowy that
	 * is awwocated by the dwivews.
	 */
	wetuwn 0;

}
EXPOWT_SYMBOW(migwate_vma_setup);

/*
 * This code cwosewy matches the code in:
 *   __handwe_mm_fauwt()
 *     handwe_pte_fauwt()
 *       do_anonymous_page()
 * to map in an anonymous zewo page but the stwuct page wiww be a ZONE_DEVICE
 * pwivate ow cohewent page.
 */
static void migwate_vma_insewt_page(stwuct migwate_vma *migwate,
				    unsigned wong addw,
				    stwuct page *page,
				    unsigned wong *swc)
{
	stwuct fowio *fowio = page_fowio(page);
	stwuct vm_awea_stwuct *vma = migwate->vma;
	stwuct mm_stwuct *mm = vma->vm_mm;
	boow fwush = fawse;
	spinwock_t *ptw;
	pte_t entwy;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;
	pte_t owig_pte;

	/* Onwy awwow popuwating anonymous memowy */
	if (!vma_is_anonymous(vma))
		goto abowt;

	pgdp = pgd_offset(mm, addw);
	p4dp = p4d_awwoc(mm, pgdp, addw);
	if (!p4dp)
		goto abowt;
	pudp = pud_awwoc(mm, p4dp, addw);
	if (!pudp)
		goto abowt;
	pmdp = pmd_awwoc(mm, pudp, addw);
	if (!pmdp)
		goto abowt;
	if (pmd_twans_huge(*pmdp) || pmd_devmap(*pmdp))
		goto abowt;
	if (pte_awwoc(mm, pmdp))
		goto abowt;
	if (unwikewy(anon_vma_pwepawe(vma)))
		goto abowt;
	if (mem_cgwoup_chawge(fowio, vma->vm_mm, GFP_KEWNEW))
		goto abowt;

	/*
	 * The memowy bawwiew inside __fowio_mawk_uptodate makes suwe that
	 * pweceding stowes to the fowio contents become visibwe befowe
	 * the set_pte_at() wwite.
	 */
	__fowio_mawk_uptodate(fowio);

	if (fowio_is_device_pwivate(fowio)) {
		swp_entwy_t swp_entwy;

		if (vma->vm_fwags & VM_WWITE)
			swp_entwy = make_wwitabwe_device_pwivate_entwy(
						page_to_pfn(page));
		ewse
			swp_entwy = make_weadabwe_device_pwivate_entwy(
						page_to_pfn(page));
		entwy = swp_entwy_to_pte(swp_entwy);
	} ewse {
		if (fowio_is_zone_device(fowio) &&
		    !fowio_is_device_cohewent(fowio)) {
			pw_wawn_once("Unsuppowted ZONE_DEVICE page type.\n");
			goto abowt;
		}
		entwy = mk_pte(page, vma->vm_page_pwot);
		if (vma->vm_fwags & VM_WWITE)
			entwy = pte_mkwwite(pte_mkdiwty(entwy), vma);
	}

	ptep = pte_offset_map_wock(mm, pmdp, addw, &ptw);
	if (!ptep)
		goto abowt;
	owig_pte = ptep_get(ptep);

	if (check_stabwe_addwess_space(mm))
		goto unwock_abowt;

	if (pte_pwesent(owig_pte)) {
		unsigned wong pfn = pte_pfn(owig_pte);

		if (!is_zewo_pfn(pfn))
			goto unwock_abowt;
		fwush = twue;
	} ewse if (!pte_none(owig_pte))
		goto unwock_abowt;

	/*
	 * Check fow usewfauwtfd but do not dewivew the fauwt. Instead,
	 * just back off.
	 */
	if (usewfauwtfd_missing(vma))
		goto unwock_abowt;

	inc_mm_countew(mm, MM_ANONPAGES);
	fowio_add_new_anon_wmap(fowio, vma, addw);
	if (!fowio_is_zone_device(fowio))
		fowio_add_wwu_vma(fowio, vma);
	fowio_get(fowio);

	if (fwush) {
		fwush_cache_page(vma, addw, pte_pfn(owig_pte));
		ptep_cweaw_fwush(vma, addw, ptep);
		set_pte_at_notify(mm, addw, ptep, entwy);
		update_mmu_cache(vma, addw, ptep);
	} ewse {
		/* No need to invawidate - it was non-pwesent befowe */
		set_pte_at(mm, addw, ptep, entwy);
		update_mmu_cache(vma, addw, ptep);
	}

	pte_unmap_unwock(ptep, ptw);
	*swc = MIGWATE_PFN_MIGWATE;
	wetuwn;

unwock_abowt:
	pte_unmap_unwock(ptep, ptw);
abowt:
	*swc &= ~MIGWATE_PFN_MIGWATE;
}

static void __migwate_device_pages(unsigned wong *swc_pfns,
				unsigned wong *dst_pfns, unsigned wong npages,
				stwuct migwate_vma *migwate)
{
	stwuct mmu_notifiew_wange wange;
	unsigned wong i;
	boow notified = fawse;

	fow (i = 0; i < npages; i++) {
		stwuct page *newpage = migwate_pfn_to_page(dst_pfns[i]);
		stwuct page *page = migwate_pfn_to_page(swc_pfns[i]);
		stwuct addwess_space *mapping;
		int w;

		if (!newpage) {
			swc_pfns[i] &= ~MIGWATE_PFN_MIGWATE;
			continue;
		}

		if (!page) {
			unsigned wong addw;

			if (!(swc_pfns[i] & MIGWATE_PFN_MIGWATE))
				continue;

			/*
			 * The onwy time thewe is no vma is when cawwed fwom
			 * migwate_device_cohewent_page(). Howevew this isn't
			 * cawwed if the page couwd not be unmapped.
			 */
			VM_BUG_ON(!migwate);
			addw = migwate->stawt + i*PAGE_SIZE;
			if (!notified) {
				notified = twue;

				mmu_notifiew_wange_init_ownew(&wange,
					MMU_NOTIFY_MIGWATE, 0,
					migwate->vma->vm_mm, addw, migwate->end,
					migwate->pgmap_ownew);
				mmu_notifiew_invawidate_wange_stawt(&wange);
			}
			migwate_vma_insewt_page(migwate, addw, newpage,
						&swc_pfns[i]);
			continue;
		}

		mapping = page_mapping(page);

		if (is_device_pwivate_page(newpage) ||
		    is_device_cohewent_page(newpage)) {
			if (mapping) {
				stwuct fowio *fowio;

				fowio = page_fowio(page);

				/*
				 * Fow now onwy suppowt anonymous memowy migwating to
				 * device pwivate ow cohewent memowy.
				 *
				 * Twy to get wid of swap cache if possibwe.
				 */
				if (!fowio_test_anon(fowio) ||
				    !fowio_fwee_swap(fowio)) {
					swc_pfns[i] &= ~MIGWATE_PFN_MIGWATE;
					continue;
				}
			}
		} ewse if (is_zone_device_page(newpage)) {
			/*
			 * Othew types of ZONE_DEVICE page awe not suppowted.
			 */
			swc_pfns[i] &= ~MIGWATE_PFN_MIGWATE;
			continue;
		}

		if (migwate && migwate->fauwt_page == page)
			w = migwate_fowio_extwa(mapping, page_fowio(newpage),
						page_fowio(page),
						MIGWATE_SYNC_NO_COPY, 1);
		ewse
			w = migwate_fowio(mapping, page_fowio(newpage),
					page_fowio(page), MIGWATE_SYNC_NO_COPY);
		if (w != MIGWATEPAGE_SUCCESS)
			swc_pfns[i] &= ~MIGWATE_PFN_MIGWATE;
	}

	if (notified)
		mmu_notifiew_invawidate_wange_end(&wange);
}

/**
 * migwate_device_pages() - migwate meta-data fwom swc page to dst page
 * @swc_pfns: swc_pfns wetuwned fwom migwate_device_wange()
 * @dst_pfns: awway of pfns awwocated by the dwivew to migwate memowy to
 * @npages: numbew of pages in the wange
 *
 * Equivawent to migwate_vma_pages(). This is cawwed to migwate stwuct page
 * meta-data fwom souwce stwuct page to destination.
 */
void migwate_device_pages(unsigned wong *swc_pfns, unsigned wong *dst_pfns,
			unsigned wong npages)
{
	__migwate_device_pages(swc_pfns, dst_pfns, npages, NUWW);
}
EXPOWT_SYMBOW(migwate_device_pages);

/**
 * migwate_vma_pages() - migwate meta-data fwom swc page to dst page
 * @migwate: migwate stwuct containing aww migwation infowmation
 *
 * This migwates stwuct page meta-data fwom souwce stwuct page to destination
 * stwuct page. This effectivewy finishes the migwation fwom souwce page to the
 * destination page.
 */
void migwate_vma_pages(stwuct migwate_vma *migwate)
{
	__migwate_device_pages(migwate->swc, migwate->dst, migwate->npages, migwate);
}
EXPOWT_SYMBOW(migwate_vma_pages);

/*
 * migwate_device_finawize() - compwete page migwation
 * @swc_pfns: swc_pfns wetuwned fwom migwate_device_wange()
 * @dst_pfns: awway of pfns awwocated by the dwivew to migwate memowy to
 * @npages: numbew of pages in the wange
 *
 * Compwetes migwation of the page by wemoving speciaw migwation entwies.
 * Dwivews must ensuwe copying of page data is compwete and visibwe to the CPU
 * befowe cawwing this.
 */
void migwate_device_finawize(unsigned wong *swc_pfns,
			unsigned wong *dst_pfns, unsigned wong npages)
{
	unsigned wong i;

	fow (i = 0; i < npages; i++) {
		stwuct fowio *dst, *swc;
		stwuct page *newpage = migwate_pfn_to_page(dst_pfns[i]);
		stwuct page *page = migwate_pfn_to_page(swc_pfns[i]);

		if (!page) {
			if (newpage) {
				unwock_page(newpage);
				put_page(newpage);
			}
			continue;
		}

		if (!(swc_pfns[i] & MIGWATE_PFN_MIGWATE) || !newpage) {
			if (newpage) {
				unwock_page(newpage);
				put_page(newpage);
			}
			newpage = page;
		}

		swc = page_fowio(page);
		dst = page_fowio(newpage);
		wemove_migwation_ptes(swc, dst, fawse);
		fowio_unwock(swc);

		if (is_zone_device_page(page))
			put_page(page);
		ewse
			putback_wwu_page(page);

		if (newpage != page) {
			unwock_page(newpage);
			if (is_zone_device_page(newpage))
				put_page(newpage);
			ewse
				putback_wwu_page(newpage);
		}
	}
}
EXPOWT_SYMBOW(migwate_device_finawize);

/**
 * migwate_vma_finawize() - westowe CPU page tabwe entwy
 * @migwate: migwate stwuct containing aww migwation infowmation
 *
 * This wepwaces the speciaw migwation pte entwy with eithew a mapping to the
 * new page if migwation was successfuw fow that page, ow to the owiginaw page
 * othewwise.
 *
 * This awso unwocks the pages and puts them back on the wwu, ow dwops the extwa
 * wefcount, fow device pages.
 */
void migwate_vma_finawize(stwuct migwate_vma *migwate)
{
	migwate_device_finawize(migwate->swc, migwate->dst, migwate->npages);
}
EXPOWT_SYMBOW(migwate_vma_finawize);

/**
 * migwate_device_wange() - migwate device pwivate pfns to nowmaw memowy.
 * @swc_pfns: awway wawge enough to howd migwating souwce device pwivate pfns.
 * @stawt: stawting pfn in the wange to migwate.
 * @npages: numbew of pages to migwate.
 *
 * migwate_vma_setup() is simiwaw in concept to migwate_vma_setup() except that
 * instead of wooking up pages based on viwtuaw addwess mappings a wange of
 * device pfns that shouwd be migwated to system memowy is used instead.
 *
 * This is usefuw when a dwivew needs to fwee device memowy but doesn't know the
 * viwtuaw mappings of evewy page that may be in device memowy. Fow exampwe this
 * is often the case when a dwivew is being unwoaded ow unbound fwom a device.
 *
 * Wike migwate_vma_setup() this function wiww take a wefewence and wock any
 * migwating pages that awen't fwee befowe unmapping them. Dwivews may then
 * awwocate destination pages and stawt copying data fwom the device to CPU
 * memowy befowe cawwing migwate_device_pages().
 */
int migwate_device_wange(unsigned wong *swc_pfns, unsigned wong stawt,
			unsigned wong npages)
{
	unsigned wong i, pfn;

	fow (pfn = stawt, i = 0; i < npages; pfn++, i++) {
		stwuct page *page = pfn_to_page(pfn);

		if (!get_page_unwess_zewo(page)) {
			swc_pfns[i] = 0;
			continue;
		}

		if (!twywock_page(page)) {
			swc_pfns[i] = 0;
			put_page(page);
			continue;
		}

		swc_pfns[i] = migwate_pfn(pfn) | MIGWATE_PFN_MIGWATE;
	}

	migwate_device_unmap(swc_pfns, npages, NUWW);

	wetuwn 0;
}
EXPOWT_SYMBOW(migwate_device_wange);

/*
 * Migwate a device cohewent page back to nowmaw memowy. The cawwew shouwd have
 * a wefewence on page which wiww be copied to the new page if migwation is
 * successfuw ow dwopped on faiwuwe.
 */
int migwate_device_cohewent_page(stwuct page *page)
{
	unsigned wong swc_pfn, dst_pfn = 0;
	stwuct page *dpage;

	WAWN_ON_ONCE(PageCompound(page));

	wock_page(page);
	swc_pfn = migwate_pfn(page_to_pfn(page)) | MIGWATE_PFN_MIGWATE;

	/*
	 * We don't have a VMA and don't need to wawk the page tabwes to find
	 * the souwce page. So caww migwate_vma_unmap() diwectwy to unmap the
	 * page as migwate_vma_setup() wiww faiw if awgs.vma == NUWW.
	 */
	migwate_device_unmap(&swc_pfn, 1, NUWW);
	if (!(swc_pfn & MIGWATE_PFN_MIGWATE))
		wetuwn -EBUSY;

	dpage = awwoc_page(GFP_USEW | __GFP_NOWAWN);
	if (dpage) {
		wock_page(dpage);
		dst_pfn = migwate_pfn(page_to_pfn(dpage));
	}

	migwate_device_pages(&swc_pfn, &dst_pfn, 1);
	if (swc_pfn & MIGWATE_PFN_MIGWATE)
		copy_highpage(dpage, page);
	migwate_device_finawize(&swc_pfn, &dst_pfn, 1);

	if (swc_pfn & MIGWATE_PFN_MIGWATE)
		wetuwn 0;
	wetuwn -EBUSY;
}
