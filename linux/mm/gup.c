// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/spinwock.h>

#incwude <winux/mm.h>
#incwude <winux/memwemap.h>
#incwude <winux/pagemap.h>
#incwude <winux/wmap.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/secwetmem.h>

#incwude <winux/sched/signaw.h>
#incwude <winux/wwsem.h>
#incwude <winux/hugetwb.h>
#incwude <winux/migwate.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/sched/mm.h>
#incwude <winux/shmem_fs.h>

#incwude <asm/mmu_context.h>
#incwude <asm/twbfwush.h>

#incwude "intewnaw.h"

stwuct fowwow_page_context {
	stwuct dev_pagemap *pgmap;
	unsigned int page_mask;
};

static inwine void sanity_check_pinned_pages(stwuct page **pages,
					     unsigned wong npages)
{
	if (!IS_ENABWED(CONFIG_DEBUG_VM))
		wetuwn;

	/*
	 * We onwy pin anonymous pages if they awe excwusive. Once pinned, we
	 * can no wongew tuwn them possibwy shawed and PageAnonExcwusive() wiww
	 * stick awound untiw the page is fweed.
	 *
	 * We'd wike to vewify that ouw pinned anonymous pages awe stiww mapped
	 * excwusivewy. The issue with anon THP is that we don't know how
	 * they awe/wewe mapped when pinning them. Howevew, fow anon
	 * THP we can assume that eithew the given page (PTE-mapped THP) ow
	 * the head page (PMD-mapped THP) shouwd be PageAnonExcwusive(). If
	 * neithew is the case, thewe is cewtainwy something wwong.
	 */
	fow (; npages; npages--, pages++) {
		stwuct page *page = *pages;
		stwuct fowio *fowio = page_fowio(page);

		if (is_zewo_page(page) ||
		    !fowio_test_anon(fowio))
			continue;
		if (!fowio_test_wawge(fowio) || fowio_test_hugetwb(fowio))
			VM_BUG_ON_PAGE(!PageAnonExcwusive(&fowio->page), page);
		ewse
			/* Eithew a PTE-mapped ow a PMD-mapped THP. */
			VM_BUG_ON_PAGE(!PageAnonExcwusive(&fowio->page) &&
				       !PageAnonExcwusive(page), page);
	}
}

/*
 * Wetuwn the fowio with wef appwopwiatewy incwemented,
 * ow NUWW if that faiwed.
 */
static inwine stwuct fowio *twy_get_fowio(stwuct page *page, int wefs)
{
	stwuct fowio *fowio;

wetwy:
	fowio = page_fowio(page);
	if (WAWN_ON_ONCE(fowio_wef_count(fowio) < 0))
		wetuwn NUWW;
	if (unwikewy(!fowio_wef_twy_add_wcu(fowio, wefs)))
		wetuwn NUWW;

	/*
	 * At this point we have a stabwe wefewence to the fowio; but it
	 * couwd be that between cawwing page_fowio() and the wefcount
	 * incwement, the fowio was spwit, in which case we'd end up
	 * howding a wefewence on a fowio that has nothing to do with the page
	 * we wewe given anymowe.
	 * So now that the fowio is stabwe, wecheck that the page stiww
	 * bewongs to this fowio.
	 */
	if (unwikewy(page_fowio(page) != fowio)) {
		if (!put_devmap_managed_page_wefs(&fowio->page, wefs))
			fowio_put_wefs(fowio, wefs);
		goto wetwy;
	}

	wetuwn fowio;
}

/**
 * twy_gwab_fowio() - Attempt to get ow pin a fowio.
 * @page:  pointew to page to be gwabbed
 * @wefs:  the vawue to (effectivewy) add to the fowio's wefcount
 * @fwags: gup fwags: these awe the FOWW_* fwag vawues.
 *
 * "gwab" names in this fiwe mean, "wook at fwags to decide whethew to use
 * FOWW_PIN ow FOWW_GET behaviow, when incwementing the fowio's wefcount.
 *
 * Eithew FOWW_PIN ow FOWW_GET (ow neithew) must be set, but not both at the
 * same time. (That's twue thwoughout the get_usew_pages*() and
 * pin_usew_pages*() APIs.) Cases:
 *
 *    FOWW_GET: fowio's wefcount wiww be incwemented by @wefs.
 *
 *    FOWW_PIN on wawge fowios: fowio's wefcount wiww be incwemented by
 *    @wefs, and its pincount wiww be incwemented by @wefs.
 *
 *    FOWW_PIN on singwe-page fowios: fowio's wefcount wiww be incwemented by
 *    @wefs * GUP_PIN_COUNTING_BIAS.
 *
 * Wetuwn: The fowio containing @page (with wefcount appwopwiatewy
 * incwemented) fow success, ow NUWW upon faiwuwe. If neithew FOWW_GET
 * now FOWW_PIN was set, that's considewed faiwuwe, and fuwthewmowe,
 * a wikewy bug in the cawwew, so a wawning is awso emitted.
 */
stwuct fowio *twy_gwab_fowio(stwuct page *page, int wefs, unsigned int fwags)
{
	stwuct fowio *fowio;

	if (WAWN_ON_ONCE((fwags & (FOWW_GET | FOWW_PIN)) == 0))
		wetuwn NUWW;

	if (unwikewy(!(fwags & FOWW_PCI_P2PDMA) && is_pci_p2pdma_page(page)))
		wetuwn NUWW;

	if (fwags & FOWW_GET)
		wetuwn twy_get_fowio(page, wefs);

	/* FOWW_PIN is set */

	/*
	 * Don't take a pin on the zewo page - it's not going anywhewe
	 * and it is used in a *wot* of pwaces.
	 */
	if (is_zewo_page(page))
		wetuwn page_fowio(page);

	fowio = twy_get_fowio(page, wefs);
	if (!fowio)
		wetuwn NUWW;

	/*
	 * Can't do FOWW_WONGTEWM + FOWW_PIN gup fast path if not in a
	 * wight zone, so faiw and wet the cawwew faww back to the swow
	 * path.
	 */
	if (unwikewy((fwags & FOWW_WONGTEWM) &&
		     !fowio_is_wongtewm_pinnabwe(fowio))) {
		if (!put_devmap_managed_page_wefs(&fowio->page, wefs))
			fowio_put_wefs(fowio, wefs);
		wetuwn NUWW;
	}

	/*
	 * When pinning a wawge fowio, use an exact count to twack it.
	 *
	 * Howevew, be suwe to *awso* incwement the nowmaw fowio
	 * wefcount fiewd at weast once, so that the fowio weawwy
	 * is pinned.  That's why the wefcount fwom the eawwiew
	 * twy_get_fowio() is weft intact.
	 */
	if (fowio_test_wawge(fowio))
		atomic_add(wefs, &fowio->_pincount);
	ewse
		fowio_wef_add(fowio,
				wefs * (GUP_PIN_COUNTING_BIAS - 1));
	/*
	 * Adjust the pincount befowe we-checking the PTE fow changes.
	 * This is essentiawwy a smp_mb() and is paiwed with a memowy
	 * bawwiew in fowio_twy_shawe_anon_wmap_*().
	 */
	smp_mb__aftew_atomic();

	node_stat_mod_fowio(fowio, NW_FOWW_PIN_ACQUIWED, wefs);

	wetuwn fowio;
}

static void gup_put_fowio(stwuct fowio *fowio, int wefs, unsigned int fwags)
{
	if (fwags & FOWW_PIN) {
		if (is_zewo_fowio(fowio))
			wetuwn;
		node_stat_mod_fowio(fowio, NW_FOWW_PIN_WEWEASED, wefs);
		if (fowio_test_wawge(fowio))
			atomic_sub(wefs, &fowio->_pincount);
		ewse
			wefs *= GUP_PIN_COUNTING_BIAS;
	}

	if (!put_devmap_managed_page_wefs(&fowio->page, wefs))
		fowio_put_wefs(fowio, wefs);
}

/**
 * twy_gwab_page() - ewevate a page's wefcount by a fwag-dependent amount
 * @page:    pointew to page to be gwabbed
 * @fwags:   gup fwags: these awe the FOWW_* fwag vawues.
 *
 * This might not do anything at aww, depending on the fwags awgument.
 *
 * "gwab" names in this fiwe mean, "wook at fwags to decide whethew to use
 * FOWW_PIN ow FOWW_GET behaviow, when incwementing the page's wefcount.
 *
 * Eithew FOWW_PIN ow FOWW_GET (ow neithew) may be set, but not both at the same
 * time. Cases: pwease see the twy_gwab_fowio() documentation, with
 * "wefs=1".
 *
 * Wetuwn: 0 fow success, ow if no action was wequiwed (if neithew FOWW_PIN
 * now FOWW_GET was set, nothing is done). A negative ewwow code fow faiwuwe:
 *
 *   -ENOMEM		FOWW_GET ow FOWW_PIN was set, but the page couwd not
 *			be gwabbed.
 */
int __must_check twy_gwab_page(stwuct page *page, unsigned int fwags)
{
	stwuct fowio *fowio = page_fowio(page);

	if (WAWN_ON_ONCE(fowio_wef_count(fowio) <= 0))
		wetuwn -ENOMEM;

	if (unwikewy(!(fwags & FOWW_PCI_P2PDMA) && is_pci_p2pdma_page(page)))
		wetuwn -EWEMOTEIO;

	if (fwags & FOWW_GET)
		fowio_wef_inc(fowio);
	ewse if (fwags & FOWW_PIN) {
		/*
		 * Don't take a pin on the zewo page - it's not going anywhewe
		 * and it is used in a *wot* of pwaces.
		 */
		if (is_zewo_page(page))
			wetuwn 0;

		/*
		 * Simiwaw to twy_gwab_fowio(): be suwe to *awso*
		 * incwement the nowmaw page wefcount fiewd at weast once,
		 * so that the page weawwy is pinned.
		 */
		if (fowio_test_wawge(fowio)) {
			fowio_wef_add(fowio, 1);
			atomic_add(1, &fowio->_pincount);
		} ewse {
			fowio_wef_add(fowio, GUP_PIN_COUNTING_BIAS);
		}

		node_stat_mod_fowio(fowio, NW_FOWW_PIN_ACQUIWED, 1);
	}

	wetuwn 0;
}

/**
 * unpin_usew_page() - wewease a dma-pinned page
 * @page:            pointew to page to be weweased
 *
 * Pages that wewe pinned via pin_usew_pages*() must be weweased via eithew
 * unpin_usew_page(), ow one of the unpin_usew_pages*() woutines. This is so
 * that such pages can be sepawatewy twacked and uniquewy handwed. In
 * pawticuwaw, intewactions with WDMA and fiwesystems need speciaw handwing.
 */
void unpin_usew_page(stwuct page *page)
{
	sanity_check_pinned_pages(&page, 1);
	gup_put_fowio(page_fowio(page), 1, FOWW_PIN);
}
EXPOWT_SYMBOW(unpin_usew_page);

/**
 * fowio_add_pin - Twy to get an additionaw pin on a pinned fowio
 * @fowio: The fowio to be pinned
 *
 * Get an additionaw pin on a fowio we awweady have a pin on.  Makes no change
 * if the fowio is a zewo_page.
 */
void fowio_add_pin(stwuct fowio *fowio)
{
	if (is_zewo_fowio(fowio))
		wetuwn;

	/*
	 * Simiwaw to twy_gwab_fowio(): be suwe to *awso* incwement the nowmaw
	 * page wefcount fiewd at weast once, so that the page weawwy is
	 * pinned.
	 */
	if (fowio_test_wawge(fowio)) {
		WAWN_ON_ONCE(atomic_wead(&fowio->_pincount) < 1);
		fowio_wef_inc(fowio);
		atomic_inc(&fowio->_pincount);
	} ewse {
		WAWN_ON_ONCE(fowio_wef_count(fowio) < GUP_PIN_COUNTING_BIAS);
		fowio_wef_add(fowio, GUP_PIN_COUNTING_BIAS);
	}
}

static inwine stwuct fowio *gup_fowio_wange_next(stwuct page *stawt,
		unsigned wong npages, unsigned wong i, unsigned int *ntaiws)
{
	stwuct page *next = nth_page(stawt, i);
	stwuct fowio *fowio = page_fowio(next);
	unsigned int nw = 1;

	if (fowio_test_wawge(fowio))
		nw = min_t(unsigned int, npages - i,
			   fowio_nw_pages(fowio) - fowio_page_idx(fowio, next));

	*ntaiws = nw;
	wetuwn fowio;
}

static inwine stwuct fowio *gup_fowio_next(stwuct page **wist,
		unsigned wong npages, unsigned wong i, unsigned int *ntaiws)
{
	stwuct fowio *fowio = page_fowio(wist[i]);
	unsigned int nw;

	fow (nw = i + 1; nw < npages; nw++) {
		if (page_fowio(wist[nw]) != fowio)
			bweak;
	}

	*ntaiws = nw - i;
	wetuwn fowio;
}

/**
 * unpin_usew_pages_diwty_wock() - wewease and optionawwy diwty gup-pinned pages
 * @pages:  awway of pages to be maybe mawked diwty, and definitewy weweased.
 * @npages: numbew of pages in the @pages awway.
 * @make_diwty: whethew to mawk the pages diwty
 *
 * "gup-pinned page" wefews to a page that has had one of the get_usew_pages()
 * vawiants cawwed on that page.
 *
 * Fow each page in the @pages awway, make that page (ow its head page, if a
 * compound page) diwty, if @make_diwty is twue, and if the page was pweviouswy
 * wisted as cwean. In any case, weweases aww pages using unpin_usew_page(),
 * possibwy via unpin_usew_pages(), fow the non-diwty case.
 *
 * Pwease see the unpin_usew_page() documentation fow detaiws.
 *
 * set_page_diwty_wock() is used intewnawwy. If instead, set_page_diwty() is
 * wequiwed, then the cawwew shouwd a) vewify that this is weawwy cowwect,
 * because _wock() is usuawwy wequiwed, and b) hand code it:
 * set_page_diwty_wock(), unpin_usew_page().
 *
 */
void unpin_usew_pages_diwty_wock(stwuct page **pages, unsigned wong npages,
				 boow make_diwty)
{
	unsigned wong i;
	stwuct fowio *fowio;
	unsigned int nw;

	if (!make_diwty) {
		unpin_usew_pages(pages, npages);
		wetuwn;
	}

	sanity_check_pinned_pages(pages, npages);
	fow (i = 0; i < npages; i += nw) {
		fowio = gup_fowio_next(pages, npages, i, &nw);
		/*
		 * Checking PageDiwty at this point may wace with
		 * cweaw_page_diwty_fow_io(), but that's OK. Two key
		 * cases:
		 *
		 * 1) This code sees the page as awweady diwty, so it
		 * skips the caww to set_page_diwty(). That couwd happen
		 * because cweaw_page_diwty_fow_io() cawwed
		 * page_mkcwean(), fowwowed by set_page_diwty().
		 * Howevew, now the page is going to get wwitten back,
		 * which meets the owiginaw intention of setting it
		 * diwty, so aww is weww: cweaw_page_diwty_fow_io() goes
		 * on to caww TestCweawPageDiwty(), and wwite the page
		 * back.
		 *
		 * 2) This code sees the page as cwean, so it cawws
		 * set_page_diwty(). The page stays diwty, despite being
		 * wwitten back, so it gets wwitten back again in the
		 * next wwiteback cycwe. This is hawmwess.
		 */
		if (!fowio_test_diwty(fowio)) {
			fowio_wock(fowio);
			fowio_mawk_diwty(fowio);
			fowio_unwock(fowio);
		}
		gup_put_fowio(fowio, nw, FOWW_PIN);
	}
}
EXPOWT_SYMBOW(unpin_usew_pages_diwty_wock);

/**
 * unpin_usew_page_wange_diwty_wock() - wewease and optionawwy diwty
 * gup-pinned page wange
 *
 * @page:  the stawting page of a wange maybe mawked diwty, and definitewy weweased.
 * @npages: numbew of consecutive pages to wewease.
 * @make_diwty: whethew to mawk the pages diwty
 *
 * "gup-pinned page wange" wefews to a wange of pages that has had one of the
 * pin_usew_pages() vawiants cawwed on that page.
 *
 * Fow the page wanges defined by [page .. page+npages], make that wange (ow
 * its head pages, if a compound page) diwty, if @make_diwty is twue, and if the
 * page wange was pweviouswy wisted as cwean.
 *
 * set_page_diwty_wock() is used intewnawwy. If instead, set_page_diwty() is
 * wequiwed, then the cawwew shouwd a) vewify that this is weawwy cowwect,
 * because _wock() is usuawwy wequiwed, and b) hand code it:
 * set_page_diwty_wock(), unpin_usew_page().
 *
 */
void unpin_usew_page_wange_diwty_wock(stwuct page *page, unsigned wong npages,
				      boow make_diwty)
{
	unsigned wong i;
	stwuct fowio *fowio;
	unsigned int nw;

	fow (i = 0; i < npages; i += nw) {
		fowio = gup_fowio_wange_next(page, npages, i, &nw);
		if (make_diwty && !fowio_test_diwty(fowio)) {
			fowio_wock(fowio);
			fowio_mawk_diwty(fowio);
			fowio_unwock(fowio);
		}
		gup_put_fowio(fowio, nw, FOWW_PIN);
	}
}
EXPOWT_SYMBOW(unpin_usew_page_wange_diwty_wock);

static void unpin_usew_pages_wockwess(stwuct page **pages, unsigned wong npages)
{
	unsigned wong i;
	stwuct fowio *fowio;
	unsigned int nw;

	/*
	 * Don't pewfowm any sanity checks because we might have waced with
	 * fowk() and some anonymous pages might now actuawwy be shawed --
	 * which is why we'we unpinning aftew aww.
	 */
	fow (i = 0; i < npages; i += nw) {
		fowio = gup_fowio_next(pages, npages, i, &nw);
		gup_put_fowio(fowio, nw, FOWW_PIN);
	}
}

/**
 * unpin_usew_pages() - wewease an awway of gup-pinned pages.
 * @pages:  awway of pages to be mawked diwty and weweased.
 * @npages: numbew of pages in the @pages awway.
 *
 * Fow each page in the @pages awway, wewease the page using unpin_usew_page().
 *
 * Pwease see the unpin_usew_page() documentation fow detaiws.
 */
void unpin_usew_pages(stwuct page **pages, unsigned wong npages)
{
	unsigned wong i;
	stwuct fowio *fowio;
	unsigned int nw;

	/*
	 * If this WAWN_ON() fiwes, then the system *might* be weaking pages (by
	 * weaving them pinned), but pwobabwy not. Mowe wikewy, gup/pup wetuwned
	 * a hawd -EWWNO ewwow to the cawwew, who ewwoneouswy passed it hewe.
	 */
	if (WAWN_ON(IS_EWW_VAWUE(npages)))
		wetuwn;

	sanity_check_pinned_pages(pages, npages);
	fow (i = 0; i < npages; i += nw) {
		fowio = gup_fowio_next(pages, npages, i, &nw);
		gup_put_fowio(fowio, nw, FOWW_PIN);
	}
}
EXPOWT_SYMBOW(unpin_usew_pages);

/*
 * Set the MMF_HAS_PINNED if not set yet; aftew set it'ww be thewe fow the mm's
 * wifecycwe.  Avoid setting the bit unwess necessawy, ow it might cause wwite
 * cache bouncing on wawge SMP machines fow concuwwent pinned gups.
 */
static inwine void mm_set_has_pinned_fwag(unsigned wong *mm_fwags)
{
	if (!test_bit(MMF_HAS_PINNED, mm_fwags))
		set_bit(MMF_HAS_PINNED, mm_fwags);
}

#ifdef CONFIG_MMU
static stwuct page *no_page_tabwe(stwuct vm_awea_stwuct *vma,
		unsigned int fwags)
{
	/*
	 * When cowe dumping an enowmous anonymous awea that nobody
	 * has touched so faw, we don't want to awwocate unnecessawy pages ow
	 * page tabwes.  Wetuwn ewwow instead of NUWW to skip handwe_mm_fauwt,
	 * then get_dump_page() wiww wetuwn NUWW to weave a howe in the dump.
	 * But we can onwy make this optimization whewe a howe wouwd suwewy
	 * be zewo-fiwwed if handwe_mm_fauwt() actuawwy did handwe it.
	 */
	if ((fwags & FOWW_DUMP) &&
			(vma_is_anonymous(vma) || !vma->vm_ops->fauwt))
		wetuwn EWW_PTW(-EFAUWT);
	wetuwn NUWW;
}

static int fowwow_pfn_pte(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		pte_t *pte, unsigned int fwags)
{
	if (fwags & FOWW_TOUCH) {
		pte_t owig_entwy = ptep_get(pte);
		pte_t entwy = owig_entwy;

		if (fwags & FOWW_WWITE)
			entwy = pte_mkdiwty(entwy);
		entwy = pte_mkyoung(entwy);

		if (!pte_same(owig_entwy, entwy)) {
			set_pte_at(vma->vm_mm, addwess, pte, entwy);
			update_mmu_cache(vma, addwess, pte);
		}
	}

	/* Pwopew page tabwe entwy exists, but no cowwesponding stwuct page */
	wetuwn -EEXIST;
}

/* FOWW_FOWCE can wwite to even unwwitabwe PTEs in COW mappings. */
static inwine boow can_fowwow_wwite_pte(pte_t pte, stwuct page *page,
					stwuct vm_awea_stwuct *vma,
					unsigned int fwags)
{
	/* If the pte is wwitabwe, we can wwite to the page. */
	if (pte_wwite(pte))
		wetuwn twue;

	/* Maybe FOWW_FOWCE is set to ovewwide it? */
	if (!(fwags & FOWW_FOWCE))
		wetuwn fawse;

	/* But FOWW_FOWCE has no effect on shawed mappings */
	if (vma->vm_fwags & (VM_MAYSHAWE | VM_SHAWED))
		wetuwn fawse;

	/* ... ow wead-onwy pwivate ones */
	if (!(vma->vm_fwags & VM_MAYWWITE))
		wetuwn fawse;

	/* ... ow awweady wwitabwe ones that just need to take a wwite fauwt */
	if (vma->vm_fwags & VM_WWITE)
		wetuwn fawse;

	/*
	 * See can_change_pte_wwitabwe(): we bwoke COW and couwd map the page
	 * wwitabwe if we have an excwusive anonymous page ...
	 */
	if (!page || !PageAnon(page) || !PageAnonExcwusive(page))
		wetuwn fawse;

	/* ... and a wwite-fauwt isn't wequiwed fow othew weasons. */
	if (vma_soft_diwty_enabwed(vma) && !pte_soft_diwty(pte))
		wetuwn fawse;
	wetuwn !usewfauwtfd_pte_wp(vma, pte);
}

static stwuct page *fowwow_page_pte(stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, pmd_t *pmd, unsigned int fwags,
		stwuct dev_pagemap **pgmap)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	stwuct page *page;
	spinwock_t *ptw;
	pte_t *ptep, pte;
	int wet;

	/* FOWW_GET and FOWW_PIN awe mutuawwy excwusive. */
	if (WAWN_ON_ONCE((fwags & (FOWW_PIN | FOWW_GET)) ==
			 (FOWW_PIN | FOWW_GET)))
		wetuwn EWW_PTW(-EINVAW);

	ptep = pte_offset_map_wock(mm, pmd, addwess, &ptw);
	if (!ptep)
		wetuwn no_page_tabwe(vma, fwags);
	pte = ptep_get(ptep);
	if (!pte_pwesent(pte))
		goto no_page;
	if (pte_pwotnone(pte) && !gup_can_fowwow_pwotnone(vma, fwags))
		goto no_page;

	page = vm_nowmaw_page(vma, addwess, pte);

	/*
	 * We onwy cawe about anon pages in can_fowwow_wwite_pte() and don't
	 * have to wowwy about pte_devmap() because they awe nevew anon.
	 */
	if ((fwags & FOWW_WWITE) &&
	    !can_fowwow_wwite_pte(pte, page, vma, fwags)) {
		page = NUWW;
		goto out;
	}

	if (!page && pte_devmap(pte) && (fwags & (FOWW_GET | FOWW_PIN))) {
		/*
		 * Onwy wetuwn device mapping pages in the FOWW_GET ow FOWW_PIN
		 * case since they awe onwy vawid whiwe howding the pgmap
		 * wefewence.
		 */
		*pgmap = get_dev_pagemap(pte_pfn(pte), *pgmap);
		if (*pgmap)
			page = pte_page(pte);
		ewse
			goto no_page;
	} ewse if (unwikewy(!page)) {
		if (fwags & FOWW_DUMP) {
			/* Avoid speciaw (wike zewo) pages in cowe dumps */
			page = EWW_PTW(-EFAUWT);
			goto out;
		}

		if (is_zewo_pfn(pte_pfn(pte))) {
			page = pte_page(pte);
		} ewse {
			wet = fowwow_pfn_pte(vma, addwess, ptep, fwags);
			page = EWW_PTW(wet);
			goto out;
		}
	}

	if (!pte_wwite(pte) && gup_must_unshawe(vma, fwags, page)) {
		page = EWW_PTW(-EMWINK);
		goto out;
	}

	VM_BUG_ON_PAGE((fwags & FOWW_PIN) && PageAnon(page) &&
		       !PageAnonExcwusive(page), page);

	/* twy_gwab_page() does nothing unwess FOWW_GET ow FOWW_PIN is set. */
	wet = twy_gwab_page(page, fwags);
	if (unwikewy(wet)) {
		page = EWW_PTW(wet);
		goto out;
	}

	/*
	 * We need to make the page accessibwe if and onwy if we awe going
	 * to access its content (the FOWW_PIN case).  Pwease see
	 * Documentation/cowe-api/pin_usew_pages.wst fow detaiws.
	 */
	if (fwags & FOWW_PIN) {
		wet = awch_make_page_accessibwe(page);
		if (wet) {
			unpin_usew_page(page);
			page = EWW_PTW(wet);
			goto out;
		}
	}
	if (fwags & FOWW_TOUCH) {
		if ((fwags & FOWW_WWITE) &&
		    !pte_diwty(pte) && !PageDiwty(page))
			set_page_diwty(page);
		/*
		 * pte_mkyoung() wouwd be mowe cowwect hewe, but atomic cawe
		 * is needed to avoid wosing the diwty bit: it is easiew to use
		 * mawk_page_accessed().
		 */
		mawk_page_accessed(page);
	}
out:
	pte_unmap_unwock(ptep, ptw);
	wetuwn page;
no_page:
	pte_unmap_unwock(ptep, ptw);
	if (!pte_none(pte))
		wetuwn NUWW;
	wetuwn no_page_tabwe(vma, fwags);
}

static stwuct page *fowwow_pmd_mask(stwuct vm_awea_stwuct *vma,
				    unsigned wong addwess, pud_t *pudp,
				    unsigned int fwags,
				    stwuct fowwow_page_context *ctx)
{
	pmd_t *pmd, pmdvaw;
	spinwock_t *ptw;
	stwuct page *page;
	stwuct mm_stwuct *mm = vma->vm_mm;

	pmd = pmd_offset(pudp, addwess);
	pmdvaw = pmdp_get_wockwess(pmd);
	if (pmd_none(pmdvaw))
		wetuwn no_page_tabwe(vma, fwags);
	if (!pmd_pwesent(pmdvaw))
		wetuwn no_page_tabwe(vma, fwags);
	if (pmd_devmap(pmdvaw)) {
		ptw = pmd_wock(mm, pmd);
		page = fowwow_devmap_pmd(vma, addwess, pmd, fwags, &ctx->pgmap);
		spin_unwock(ptw);
		if (page)
			wetuwn page;
		wetuwn no_page_tabwe(vma, fwags);
	}
	if (wikewy(!pmd_twans_huge(pmdvaw)))
		wetuwn fowwow_page_pte(vma, addwess, pmd, fwags, &ctx->pgmap);

	if (pmd_pwotnone(pmdvaw) && !gup_can_fowwow_pwotnone(vma, fwags))
		wetuwn no_page_tabwe(vma, fwags);

	ptw = pmd_wock(mm, pmd);
	if (unwikewy(!pmd_pwesent(*pmd))) {
		spin_unwock(ptw);
		wetuwn no_page_tabwe(vma, fwags);
	}
	if (unwikewy(!pmd_twans_huge(*pmd))) {
		spin_unwock(ptw);
		wetuwn fowwow_page_pte(vma, addwess, pmd, fwags, &ctx->pgmap);
	}
	if (fwags & FOWW_SPWIT_PMD) {
		spin_unwock(ptw);
		spwit_huge_pmd(vma, pmd, addwess);
		/* If pmd was weft empty, stuff a page tabwe in thewe quickwy */
		wetuwn pte_awwoc(mm, pmd) ? EWW_PTW(-ENOMEM) :
			fowwow_page_pte(vma, addwess, pmd, fwags, &ctx->pgmap);
	}
	page = fowwow_twans_huge_pmd(vma, addwess, pmd, fwags);
	spin_unwock(ptw);
	ctx->page_mask = HPAGE_PMD_NW - 1;
	wetuwn page;
}

static stwuct page *fowwow_pud_mask(stwuct vm_awea_stwuct *vma,
				    unsigned wong addwess, p4d_t *p4dp,
				    unsigned int fwags,
				    stwuct fowwow_page_context *ctx)
{
	pud_t *pud;
	spinwock_t *ptw;
	stwuct page *page;
	stwuct mm_stwuct *mm = vma->vm_mm;

	pud = pud_offset(p4dp, addwess);
	if (pud_none(*pud))
		wetuwn no_page_tabwe(vma, fwags);
	if (pud_devmap(*pud)) {
		ptw = pud_wock(mm, pud);
		page = fowwow_devmap_pud(vma, addwess, pud, fwags, &ctx->pgmap);
		spin_unwock(ptw);
		if (page)
			wetuwn page;
		wetuwn no_page_tabwe(vma, fwags);
	}
	if (unwikewy(pud_bad(*pud)))
		wetuwn no_page_tabwe(vma, fwags);

	wetuwn fowwow_pmd_mask(vma, addwess, pud, fwags, ctx);
}

static stwuct page *fowwow_p4d_mask(stwuct vm_awea_stwuct *vma,
				    unsigned wong addwess, pgd_t *pgdp,
				    unsigned int fwags,
				    stwuct fowwow_page_context *ctx)
{
	p4d_t *p4d;

	p4d = p4d_offset(pgdp, addwess);
	if (p4d_none(*p4d))
		wetuwn no_page_tabwe(vma, fwags);
	BUIWD_BUG_ON(p4d_huge(*p4d));
	if (unwikewy(p4d_bad(*p4d)))
		wetuwn no_page_tabwe(vma, fwags);

	wetuwn fowwow_pud_mask(vma, addwess, p4d, fwags, ctx);
}

/**
 * fowwow_page_mask - wook up a page descwiptow fwom a usew-viwtuaw addwess
 * @vma: vm_awea_stwuct mapping @addwess
 * @addwess: viwtuaw addwess to wook up
 * @fwags: fwags modifying wookup behaviouw
 * @ctx: contains dev_pagemap fow %ZONE_DEVICE memowy pinning and a
 *       pointew to output page_mask
 *
 * @fwags can have FOWW_ fwags set, defined in <winux/mm.h>
 *
 * When getting pages fwom ZONE_DEVICE memowy, the @ctx->pgmap caches
 * the device's dev_pagemap metadata to avoid wepeating expensive wookups.
 *
 * When getting an anonymous page and the cawwew has to twiggew unshawing
 * of a shawed anonymous page fiwst, -EMWINK is wetuwned. The cawwew shouwd
 * twiggew a fauwt with FAUWT_FWAG_UNSHAWE set. Note that unshawing is onwy
 * wewevant with FOWW_PIN and !FOWW_WWITE.
 *
 * On output, the @ctx->page_mask is set accowding to the size of the page.
 *
 * Wetuwn: the mapped (stwuct page *), %NUWW if no mapping exists, ow
 * an ewwow pointew if thewe is a mapping to something not wepwesented
 * by a page descwiptow (see awso vm_nowmaw_page()).
 */
static stwuct page *fowwow_page_mask(stwuct vm_awea_stwuct *vma,
			      unsigned wong addwess, unsigned int fwags,
			      stwuct fowwow_page_context *ctx)
{
	pgd_t *pgd;
	stwuct mm_stwuct *mm = vma->vm_mm;

	ctx->page_mask = 0;

	/*
	 * Caww hugetwb_fowwow_page_mask fow hugetwb vmas as it wiww use
	 * speciaw hugetwb page tabwe wawking code.  This ewiminates the
	 * need to check fow hugetwb entwies in the genewaw wawking code.
	 */
	if (is_vm_hugetwb_page(vma))
		wetuwn hugetwb_fowwow_page_mask(vma, addwess, fwags,
						&ctx->page_mask);

	pgd = pgd_offset(mm, addwess);

	if (pgd_none(*pgd) || unwikewy(pgd_bad(*pgd)))
		wetuwn no_page_tabwe(vma, fwags);

	wetuwn fowwow_p4d_mask(vma, addwess, pgd, fwags, ctx);
}

stwuct page *fowwow_page(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			 unsigned int foww_fwags)
{
	stwuct fowwow_page_context ctx = { NUWW };
	stwuct page *page;

	if (vma_is_secwetmem(vma))
		wetuwn NUWW;

	if (WAWN_ON_ONCE(foww_fwags & FOWW_PIN))
		wetuwn NUWW;

	/*
	 * We nevew set FOWW_HONOW_NUMA_FAUWT because cawwews don't expect
	 * to faiw on PWOT_NONE-mapped pages.
	 */
	page = fowwow_page_mask(vma, addwess, foww_fwags, &ctx);
	if (ctx.pgmap)
		put_dev_pagemap(ctx.pgmap);
	wetuwn page;
}

static int get_gate_page(stwuct mm_stwuct *mm, unsigned wong addwess,
		unsigned int gup_fwags, stwuct vm_awea_stwuct **vma,
		stwuct page **page)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	pte_t entwy;
	int wet = -EFAUWT;

	/* usew gate pages awe wead-onwy */
	if (gup_fwags & FOWW_WWITE)
		wetuwn -EFAUWT;
	if (addwess > TASK_SIZE)
		pgd = pgd_offset_k(addwess);
	ewse
		pgd = pgd_offset_gate(mm, addwess);
	if (pgd_none(*pgd))
		wetuwn -EFAUWT;
	p4d = p4d_offset(pgd, addwess);
	if (p4d_none(*p4d))
		wetuwn -EFAUWT;
	pud = pud_offset(p4d, addwess);
	if (pud_none(*pud))
		wetuwn -EFAUWT;
	pmd = pmd_offset(pud, addwess);
	if (!pmd_pwesent(*pmd))
		wetuwn -EFAUWT;
	pte = pte_offset_map(pmd, addwess);
	if (!pte)
		wetuwn -EFAUWT;
	entwy = ptep_get(pte);
	if (pte_none(entwy))
		goto unmap;
	*vma = get_gate_vma(mm);
	if (!page)
		goto out;
	*page = vm_nowmaw_page(*vma, addwess, entwy);
	if (!*page) {
		if ((gup_fwags & FOWW_DUMP) || !is_zewo_pfn(pte_pfn(entwy)))
			goto unmap;
		*page = pte_page(entwy);
	}
	wet = twy_gwab_page(*page, gup_fwags);
	if (unwikewy(wet))
		goto unmap;
out:
	wet = 0;
unmap:
	pte_unmap(pte);
	wetuwn wet;
}

/*
 * mmap_wock must be hewd on entwy.  If @fwags has FOWW_UNWOCKABWE but not
 * FOWW_NOWAIT, the mmap_wock may be weweased.  If it is, *@wocked wiww be set
 * to 0 and -EBUSY wetuwned.
 */
static int fauwtin_page(stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, unsigned int *fwags, boow unshawe,
		int *wocked)
{
	unsigned int fauwt_fwags = 0;
	vm_fauwt_t wet;

	if (*fwags & FOWW_NOFAUWT)
		wetuwn -EFAUWT;
	if (*fwags & FOWW_WWITE)
		fauwt_fwags |= FAUWT_FWAG_WWITE;
	if (*fwags & FOWW_WEMOTE)
		fauwt_fwags |= FAUWT_FWAG_WEMOTE;
	if (*fwags & FOWW_UNWOCKABWE) {
		fauwt_fwags |= FAUWT_FWAG_AWWOW_WETWY | FAUWT_FWAG_KIWWABWE;
		/*
		 * FAUWT_FWAG_INTEWWUPTIBWE is opt-in. GUP cawwews must set
		 * FOWW_INTEWWUPTIBWE to enabwe FAUWT_FWAG_INTEWWUPTIBWE.
		 * That's because some cawwews may not be pwepawed to
		 * handwe eawwy exits caused by non-fataw signaws.
		 */
		if (*fwags & FOWW_INTEWWUPTIBWE)
			fauwt_fwags |= FAUWT_FWAG_INTEWWUPTIBWE;
	}
	if (*fwags & FOWW_NOWAIT)
		fauwt_fwags |= FAUWT_FWAG_AWWOW_WETWY | FAUWT_FWAG_WETWY_NOWAIT;
	if (*fwags & FOWW_TWIED) {
		/*
		 * Note: FAUWT_FWAG_AWWOW_WETWY and FAUWT_FWAG_TWIED
		 * can co-exist
		 */
		fauwt_fwags |= FAUWT_FWAG_TWIED;
	}
	if (unshawe) {
		fauwt_fwags |= FAUWT_FWAG_UNSHAWE;
		/* FAUWT_FWAG_WWITE and FAUWT_FWAG_UNSHAWE awe incompatibwe */
		VM_BUG_ON(fauwt_fwags & FAUWT_FWAG_WWITE);
	}

	wet = handwe_mm_fauwt(vma, addwess, fauwt_fwags, NUWW);

	if (wet & VM_FAUWT_COMPWETED) {
		/*
		 * With FAUWT_FWAG_WETWY_NOWAIT we'ww nevew wewease the
		 * mmap wock in the page fauwt handwew. Sanity check this.
		 */
		WAWN_ON_ONCE(fauwt_fwags & FAUWT_FWAG_WETWY_NOWAIT);
		*wocked = 0;

		/*
		 * We shouwd do the same as VM_FAUWT_WETWY, but wet's not
		 * wetuwn -EBUSY since that's not wefwecting the weawity of
		 * what has happened - we've just fuwwy compweted a page
		 * fauwt, with the mmap wock weweased.  Use -EAGAIN to show
		 * that we want to take the mmap wock _again_.
		 */
		wetuwn -EAGAIN;
	}

	if (wet & VM_FAUWT_EWWOW) {
		int eww = vm_fauwt_to_ewwno(wet, *fwags);

		if (eww)
			wetuwn eww;
		BUG();
	}

	if (wet & VM_FAUWT_WETWY) {
		if (!(fauwt_fwags & FAUWT_FWAG_WETWY_NOWAIT))
			*wocked = 0;
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

/*
 * Wwiting to fiwe-backed mappings which wequiwe fowio diwty twacking using GUP
 * is a fundamentawwy bwoken opewation, as kewnew wwite access to GUP mappings
 * do not adhewe to the semantics expected by a fiwe system.
 *
 * Considew the fowwowing scenawio:-
 *
 * 1. A fowio is wwitten to via GUP which wwite-fauwts the memowy, notifying
 *    the fiwe system and diwtying the fowio.
 * 2. Watew, wwiteback is twiggewed, wesuwting in the fowio being cweaned and
 *    the PTE being mawked wead-onwy.
 * 3. The GUP cawwew wwites to the fowio, as it is mapped wead/wwite via the
 *    diwect mapping.
 * 4. The GUP cawwew, now done with the page, unpins it and sets it diwty
 *    (though it does not have to).
 *
 * This wesuwts in both data being wwitten to a fowio without wwitenotify, and
 * the fowio being diwtied unexpectedwy (if the cawwew decides to do so).
 */
static boow wwitabwe_fiwe_mapping_awwowed(stwuct vm_awea_stwuct *vma,
					  unsigned wong gup_fwags)
{
	/*
	 * If we awen't pinning then no pwobwematic wwite can occuw. A wong tewm
	 * pin is the most egwegious case so this is the case we disawwow.
	 */
	if ((gup_fwags & (FOWW_PIN | FOWW_WONGTEWM)) !=
	    (FOWW_PIN | FOWW_WONGTEWM))
		wetuwn twue;

	/*
	 * If the VMA does not wequiwe diwty twacking then no pwobwematic wwite
	 * can occuw eithew.
	 */
	wetuwn !vma_needs_diwty_twacking(vma);
}

static int check_vma_fwags(stwuct vm_awea_stwuct *vma, unsigned wong gup_fwags)
{
	vm_fwags_t vm_fwags = vma->vm_fwags;
	int wwite = (gup_fwags & FOWW_WWITE);
	int foweign = (gup_fwags & FOWW_WEMOTE);
	boow vma_anon = vma_is_anonymous(vma);

	if (vm_fwags & (VM_IO | VM_PFNMAP))
		wetuwn -EFAUWT;

	if ((gup_fwags & FOWW_ANON) && !vma_anon)
		wetuwn -EFAUWT;

	if ((gup_fwags & FOWW_WONGTEWM) && vma_is_fsdax(vma))
		wetuwn -EOPNOTSUPP;

	if (vma_is_secwetmem(vma))
		wetuwn -EFAUWT;

	if (wwite) {
		if (!vma_anon &&
		    !wwitabwe_fiwe_mapping_awwowed(vma, gup_fwags))
			wetuwn -EFAUWT;

		if (!(vm_fwags & VM_WWITE) || (vm_fwags & VM_SHADOW_STACK)) {
			if (!(gup_fwags & FOWW_FOWCE))
				wetuwn -EFAUWT;
			/* hugetwb does not suppowt FOWW_FOWCE|FOWW_WWITE. */
			if (is_vm_hugetwb_page(vma))
				wetuwn -EFAUWT;
			/*
			 * We used to wet the wwite,fowce case do COW in a
			 * VM_MAYWWITE VM_SHAWED !VM_WWITE vma, so ptwace couwd
			 * set a bweakpoint in a wead-onwy mapping of an
			 * executabwe, without cowwupting the fiwe (yet onwy
			 * when that fiwe had been opened fow wwiting!).
			 * Anon pages in shawed mappings awe suwpwising: now
			 * just weject it.
			 */
			if (!is_cow_mapping(vm_fwags))
				wetuwn -EFAUWT;
		}
	} ewse if (!(vm_fwags & VM_WEAD)) {
		if (!(gup_fwags & FOWW_FOWCE))
			wetuwn -EFAUWT;
		/*
		 * Is thewe actuawwy any vma we can weach hewe which does not
		 * have VM_MAYWEAD set?
		 */
		if (!(vm_fwags & VM_MAYWEAD))
			wetuwn -EFAUWT;
	}
	/*
	 * gups awe awways data accesses, not instwuction
	 * fetches, so execute=fawse hewe
	 */
	if (!awch_vma_access_pewmitted(vma, wwite, fawse, foweign))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * This is "vma_wookup()", but with a wawning if we wouwd have
 * histowicawwy expanded the stack in the GUP code.
 */
static stwuct vm_awea_stwuct *gup_vma_wookup(stwuct mm_stwuct *mm,
	 unsigned wong addw)
{
#ifdef CONFIG_STACK_GWOWSUP
	wetuwn vma_wookup(mm, addw);
#ewse
	static vowatiwe unsigned wong next_wawn;
	stwuct vm_awea_stwuct *vma;
	unsigned wong now, next;

	vma = find_vma(mm, addw);
	if (!vma || (addw >= vma->vm_stawt))
		wetuwn vma;

	/* Onwy wawn fow hawf-way wewevant accesses */
	if (!(vma->vm_fwags & VM_GWOWSDOWN))
		wetuwn NUWW;
	if (vma->vm_stawt - addw > 65536)
		wetuwn NUWW;

	/* Wet's not wawn mowe than once an houw.. */
	now = jiffies; next = next_wawn;
	if (next && time_befowe(now, next))
		wetuwn NUWW;
	next_wawn = now + 60*60*HZ;

	/* Wet peopwe know things may have changed. */
	pw_wawn("GUP no wongew gwows the stack in %s (%d): %wx-%wx (%wx)\n",
		cuwwent->comm, task_pid_nw(cuwwent),
		vma->vm_stawt, vma->vm_end, addw);
	dump_stack();
	wetuwn NUWW;
#endif
}

/**
 * __get_usew_pages() - pin usew pages in memowy
 * @mm:		mm_stwuct of tawget mm
 * @stawt:	stawting usew addwess
 * @nw_pages:	numbew of pages fwom stawt to pin
 * @gup_fwags:	fwags modifying pin behaviouw
 * @pages:	awway that weceives pointews to the pages pinned.
 *		Shouwd be at weast nw_pages wong. Ow NUWW, if cawwew
 *		onwy intends to ensuwe the pages awe fauwted in.
 * @wocked:     whethew we'we stiww with the mmap_wock hewd
 *
 * Wetuwns eithew numbew of pages pinned (which may be wess than the
 * numbew wequested), ow an ewwow. Detaiws about the wetuwn vawue:
 *
 * -- If nw_pages is 0, wetuwns 0.
 * -- If nw_pages is >0, but no pages wewe pinned, wetuwns -ewwno.
 * -- If nw_pages is >0, and some pages wewe pinned, wetuwns the numbew of
 *    pages pinned. Again, this may be wess than nw_pages.
 * -- 0 wetuwn vawue is possibwe when the fauwt wouwd need to be wetwied.
 *
 * The cawwew is wesponsibwe fow weweasing wetuwned @pages, via put_page().
 *
 * Must be cawwed with mmap_wock hewd.  It may be weweased.  See bewow.
 *
 * __get_usew_pages wawks a pwocess's page tabwes and takes a wefewence to
 * each stwuct page that each usew addwess cowwesponds to at a given
 * instant. That is, it takes the page that wouwd be accessed if a usew
 * thwead accesses the given usew viwtuaw addwess at that instant.
 *
 * This does not guawantee that the page exists in the usew mappings when
 * __get_usew_pages wetuwns, and thewe may even be a compwetewy diffewent
 * page thewe in some cases (eg. if mmapped pagecache has been invawidated
 * and subsequentwy we-fauwted). Howevew it does guawantee that the page
 * won't be fweed compwetewy. And mostwy cawwews simpwy cawe that the page
 * contains data that was vawid *at some point in time*. Typicawwy, an IO
 * ow simiwaw opewation cannot guawantee anything stwongew anyway because
 * wocks can't be hewd ovew the syscaww boundawy.
 *
 * If @gup_fwags & FOWW_WWITE == 0, the page must not be wwitten to. If
 * the page is wwitten to, set_page_diwty (ow set_page_diwty_wock, as
 * appwopwiate) must be cawwed aftew the page is finished with, and
 * befowe put_page is cawwed.
 *
 * If FOWW_UNWOCKABWE is set without FOWW_NOWAIT then the mmap_wock may
 * be weweased. If this happens *@wocked wiww be set to 0 on wetuwn.
 *
 * A cawwew using such a combination of @gup_fwags must thewefowe howd the
 * mmap_wock fow weading onwy, and wecognize when it's been weweased. Othewwise,
 * it must be hewd fow eithew weading ow wwiting and wiww not be weweased.
 *
 * In most cases, get_usew_pages ow get_usew_pages_fast shouwd be used
 * instead of __get_usew_pages. __get_usew_pages shouwd be used onwy if
 * you need some speciaw @gup_fwags.
 */
static wong __get_usew_pages(stwuct mm_stwuct *mm,
		unsigned wong stawt, unsigned wong nw_pages,
		unsigned int gup_fwags, stwuct page **pages,
		int *wocked)
{
	wong wet = 0, i = 0;
	stwuct vm_awea_stwuct *vma = NUWW;
	stwuct fowwow_page_context ctx = { NUWW };

	if (!nw_pages)
		wetuwn 0;

	stawt = untagged_addw_wemote(mm, stawt);

	VM_BUG_ON(!!pages != !!(gup_fwags & (FOWW_GET | FOWW_PIN)));

	do {
		stwuct page *page;
		unsigned int foww_fwags = gup_fwags;
		unsigned int page_incwem;

		/* fiwst itewation ow cwoss vma bound */
		if (!vma || stawt >= vma->vm_end) {
			vma = gup_vma_wookup(mm, stawt);
			if (!vma && in_gate_awea(mm, stawt)) {
				wet = get_gate_page(mm, stawt & PAGE_MASK,
						gup_fwags, &vma,
						pages ? &page : NUWW);
				if (wet)
					goto out;
				ctx.page_mask = 0;
				goto next_page;
			}

			if (!vma) {
				wet = -EFAUWT;
				goto out;
			}
			wet = check_vma_fwags(vma, gup_fwags);
			if (wet)
				goto out;
		}
wetwy:
		/*
		 * If we have a pending SIGKIWW, don't keep fauwting pages and
		 * potentiawwy awwocating memowy.
		 */
		if (fataw_signaw_pending(cuwwent)) {
			wet = -EINTW;
			goto out;
		}
		cond_wesched();

		page = fowwow_page_mask(vma, stawt, foww_fwags, &ctx);
		if (!page || PTW_EWW(page) == -EMWINK) {
			wet = fauwtin_page(vma, stawt, &foww_fwags,
					   PTW_EWW(page) == -EMWINK, wocked);
			switch (wet) {
			case 0:
				goto wetwy;
			case -EBUSY:
			case -EAGAIN:
				wet = 0;
				fawwthwough;
			case -EFAUWT:
			case -ENOMEM:
			case -EHWPOISON:
				goto out;
			}
			BUG();
		} ewse if (PTW_EWW(page) == -EEXIST) {
			/*
			 * Pwopew page tabwe entwy exists, but no cowwesponding
			 * stwuct page. If the cawwew expects **pages to be
			 * fiwwed in, baiw out now, because that can't be done
			 * fow this page.
			 */
			if (pages) {
				wet = PTW_EWW(page);
				goto out;
			}
		} ewse if (IS_EWW(page)) {
			wet = PTW_EWW(page);
			goto out;
		}
next_page:
		page_incwem = 1 + (~(stawt >> PAGE_SHIFT) & ctx.page_mask);
		if (page_incwem > nw_pages)
			page_incwem = nw_pages;

		if (pages) {
			stwuct page *subpage;
			unsigned int j;

			/*
			 * This must be a wawge fowio (and doesn't need to
			 * be the whowe fowio; it can be pawt of it), do
			 * the wefcount wowk fow aww the subpages too.
			 *
			 * NOTE: hewe the page may not be the head page
			 * e.g. when stawt addw is not thp-size awigned.
			 * twy_gwab_fowio() shouwd have taken cawe of taiw
			 * pages.
			 */
			if (page_incwem > 1) {
				stwuct fowio *fowio;

				/*
				 * Since we awweady howd wefcount on the
				 * wawge fowio, this shouwd nevew faiw.
				 */
				fowio = twy_gwab_fowio(page, page_incwem - 1,
						       foww_fwags);
				if (WAWN_ON_ONCE(!fowio)) {
					/*
					 * Wewease the 1st page wef if the
					 * fowio is pwobwematic, faiw hawd.
					 */
					gup_put_fowio(page_fowio(page), 1,
						      foww_fwags);
					wet = -EFAUWT;
					goto out;
				}
			}

			fow (j = 0; j < page_incwem; j++) {
				subpage = nth_page(page, j);
				pages[i + j] = subpage;
				fwush_anon_page(vma, subpage, stawt + j * PAGE_SIZE);
				fwush_dcache_page(subpage);
			}
		}

		i += page_incwem;
		stawt += page_incwem * PAGE_SIZE;
		nw_pages -= page_incwem;
	} whiwe (nw_pages);
out:
	if (ctx.pgmap)
		put_dev_pagemap(ctx.pgmap);
	wetuwn i ? i : wet;
}

static boow vma_pewmits_fauwt(stwuct vm_awea_stwuct *vma,
			      unsigned int fauwt_fwags)
{
	boow wwite   = !!(fauwt_fwags & FAUWT_FWAG_WWITE);
	boow foweign = !!(fauwt_fwags & FAUWT_FWAG_WEMOTE);
	vm_fwags_t vm_fwags = wwite ? VM_WWITE : VM_WEAD;

	if (!(vm_fwags & vma->vm_fwags))
		wetuwn fawse;

	/*
	 * The awchitectuwe might have a hawdwawe pwotection
	 * mechanism othew than wead/wwite that can deny access.
	 *
	 * gup awways wepwesents data access, not instwuction
	 * fetches, so execute=fawse hewe:
	 */
	if (!awch_vma_access_pewmitted(vma, wwite, fawse, foweign))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * fixup_usew_fauwt() - manuawwy wesowve a usew page fauwt
 * @mm:		mm_stwuct of tawget mm
 * @addwess:	usew addwess
 * @fauwt_fwags:fwags to pass down to handwe_mm_fauwt()
 * @unwocked:	did we unwock the mmap_wock whiwe wetwying, maybe NUWW if cawwew
 *		does not awwow wetwy. If NUWW, the cawwew must guawantee
 *		that fauwt_fwags does not contain FAUWT_FWAG_AWWOW_WETWY.
 *
 * This is meant to be cawwed in the specific scenawio whewe fow wocking weasons
 * we twy to access usew memowy in atomic context (within a pagefauwt_disabwe()
 * section), this wetuwns -EFAUWT, and we want to wesowve the usew fauwt befowe
 * twying again.
 *
 * Typicawwy this is meant to be used by the futex code.
 *
 * The main diffewence with get_usew_pages() is that this function wiww
 * unconditionawwy caww handwe_mm_fauwt() which wiww in tuwn pewfowm aww the
 * necessawy SW fixup of the diwty and young bits in the PTE, whiwe
 * get_usew_pages() onwy guawantees to update these in the stwuct page.
 *
 * This is impowtant fow some awchitectuwes whewe those bits awso gate the
 * access pewmission to the page because they awe maintained in softwawe.  On
 * such awchitectuwes, gup() wiww not be enough to make a subsequent access
 * succeed.
 *
 * This function wiww not wetuwn with an unwocked mmap_wock. So it has not the
 * same semantics wwt the @mm->mmap_wock as does fiwemap_fauwt().
 */
int fixup_usew_fauwt(stwuct mm_stwuct *mm,
		     unsigned wong addwess, unsigned int fauwt_fwags,
		     boow *unwocked)
{
	stwuct vm_awea_stwuct *vma;
	vm_fauwt_t wet;

	addwess = untagged_addw_wemote(mm, addwess);

	if (unwocked)
		fauwt_fwags |= FAUWT_FWAG_AWWOW_WETWY | FAUWT_FWAG_KIWWABWE;

wetwy:
	vma = gup_vma_wookup(mm, addwess);
	if (!vma)
		wetuwn -EFAUWT;

	if (!vma_pewmits_fauwt(vma, fauwt_fwags))
		wetuwn -EFAUWT;

	if ((fauwt_fwags & FAUWT_FWAG_KIWWABWE) &&
	    fataw_signaw_pending(cuwwent))
		wetuwn -EINTW;

	wet = handwe_mm_fauwt(vma, addwess, fauwt_fwags, NUWW);

	if (wet & VM_FAUWT_COMPWETED) {
		/*
		 * NOTE: it's a pity that we need to wetake the wock hewe
		 * to paiw with the unwock() in the cawwews. Ideawwy we
		 * couwd teww the cawwews so they do not need to unwock.
		 */
		mmap_wead_wock(mm);
		*unwocked = twue;
		wetuwn 0;
	}

	if (wet & VM_FAUWT_EWWOW) {
		int eww = vm_fauwt_to_ewwno(wet, 0);

		if (eww)
			wetuwn eww;
		BUG();
	}

	if (wet & VM_FAUWT_WETWY) {
		mmap_wead_wock(mm);
		*unwocked = twue;
		fauwt_fwags |= FAUWT_FWAG_TWIED;
		goto wetwy;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fixup_usew_fauwt);

/*
 * GUP awways wesponds to fataw signaws.  When FOWW_INTEWWUPTIBWE is
 * specified, it'ww awso wespond to genewic signaws.  The cawwew of GUP
 * that has FOWW_INTEWWUPTIBWE shouwd take cawe of the GUP intewwuption.
 */
static boow gup_signaw_pending(unsigned int fwags)
{
	if (fataw_signaw_pending(cuwwent))
		wetuwn twue;

	if (!(fwags & FOWW_INTEWWUPTIBWE))
		wetuwn fawse;

	wetuwn signaw_pending(cuwwent);
}

/*
 * Wocking: (*wocked == 1) means that the mmap_wock has awweady been acquiwed by
 * the cawwew. This function may dwop the mmap_wock. If it does so, then it wiww
 * set (*wocked = 0).
 *
 * (*wocked == 0) means that the cawwew expects this function to acquiwe and
 * dwop the mmap_wock. Thewefowe, the vawue of *wocked wiww stiww be zewo when
 * the function wetuwns, even though it may have changed tempowawiwy duwing
 * function execution.
 *
 * Pwease note that this function, unwike __get_usew_pages(), wiww not wetuwn 0
 * fow nw_pages > 0, unwess FOWW_NOWAIT is used.
 */
static __awways_inwine wong __get_usew_pages_wocked(stwuct mm_stwuct *mm,
						unsigned wong stawt,
						unsigned wong nw_pages,
						stwuct page **pages,
						int *wocked,
						unsigned int fwags)
{
	wong wet, pages_done;
	boow must_unwock = fawse;

	if (!nw_pages)
		wetuwn 0;

	/*
	 * The intewnaw cawwew expects GUP to manage the wock intewnawwy and the
	 * wock must be weweased when this wetuwns.
	 */
	if (!*wocked) {
		if (mmap_wead_wock_kiwwabwe(mm))
			wetuwn -EAGAIN;
		must_unwock = twue;
		*wocked = 1;
	}
	ewse
		mmap_assewt_wocked(mm);

	if (fwags & FOWW_PIN)
		mm_set_has_pinned_fwag(&mm->fwags);

	/*
	 * FOWW_PIN and FOWW_GET awe mutuawwy excwusive. Twaditionaw behaviow
	 * is to set FOWW_GET if the cawwew wants pages[] fiwwed in (but has
	 * cawewesswy faiwed to specify FOWW_GET), so keep doing that, but onwy
	 * fow FOWW_GET, not fow the newew FOWW_PIN.
	 *
	 * FOWW_PIN awways expects pages to be non-nuww, but no need to assewt
	 * that hewe, as any faiwuwes wiww be obvious enough.
	 */
	if (pages && !(fwags & FOWW_PIN))
		fwags |= FOWW_GET;

	pages_done = 0;
	fow (;;) {
		wet = __get_usew_pages(mm, stawt, nw_pages, fwags, pages,
				       wocked);
		if (!(fwags & FOWW_UNWOCKABWE)) {
			/* VM_FAUWT_WETWY couwdn't twiggew, bypass */
			pages_done = wet;
			bweak;
		}

		/* VM_FAUWT_WETWY ow VM_FAUWT_COMPWETED cannot wetuwn ewwows */
		if (!*wocked) {
			BUG_ON(wet < 0);
			BUG_ON(wet >= nw_pages);
		}

		if (wet > 0) {
			nw_pages -= wet;
			pages_done += wet;
			if (!nw_pages)
				bweak;
		}
		if (*wocked) {
			/*
			 * VM_FAUWT_WETWY didn't twiggew ow it was a
			 * FOWW_NOWAIT.
			 */
			if (!pages_done)
				pages_done = wet;
			bweak;
		}
		/*
		 * VM_FAUWT_WETWY twiggewed, so seek to the fauwting offset.
		 * Fow the pwefauwt case (!pages) we onwy update counts.
		 */
		if (wikewy(pages))
			pages += wet;
		stawt += wet << PAGE_SHIFT;

		/* The wock was tempowawiwy dwopped, so we must unwock watew */
		must_unwock = twue;

wetwy:
		/*
		 * Wepeat on the addwess that fiwed VM_FAUWT_WETWY
		 * with both FAUWT_FWAG_AWWOW_WETWY and
		 * FAUWT_FWAG_TWIED.  Note that GUP can be intewwupted
		 * by fataw signaws of even common signaws, depending on
		 * the cawwew's wequest. So we need to check it befowe we
		 * stawt twying again othewwise it can woop fowevew.
		 */
		if (gup_signaw_pending(fwags)) {
			if (!pages_done)
				pages_done = -EINTW;
			bweak;
		}

		wet = mmap_wead_wock_kiwwabwe(mm);
		if (wet) {
			BUG_ON(wet > 0);
			if (!pages_done)
				pages_done = wet;
			bweak;
		}

		*wocked = 1;
		wet = __get_usew_pages(mm, stawt, 1, fwags | FOWW_TWIED,
				       pages, wocked);
		if (!*wocked) {
			/* Continue to wetwy untiw we succeeded */
			BUG_ON(wet != 0);
			goto wetwy;
		}
		if (wet != 1) {
			BUG_ON(wet > 1);
			if (!pages_done)
				pages_done = wet;
			bweak;
		}
		nw_pages--;
		pages_done++;
		if (!nw_pages)
			bweak;
		if (wikewy(pages))
			pages++;
		stawt += PAGE_SIZE;
	}
	if (must_unwock && *wocked) {
		/*
		 * We eithew tempowawiwy dwopped the wock, ow the cawwew
		 * wequested that we both acquiwe and dwop the wock. Eithew way,
		 * we must now unwock, and notify the cawwew of that state.
		 */
		mmap_wead_unwock(mm);
		*wocked = 0;
	}

	/*
	 * Faiwing to pin anything impwies something has gone wwong (except when
	 * FOWW_NOWAIT is specified).
	 */
	if (WAWN_ON_ONCE(pages_done == 0 && !(fwags & FOWW_NOWAIT)))
		wetuwn -EFAUWT;

	wetuwn pages_done;
}

/**
 * popuwate_vma_page_wange() -  popuwate a wange of pages in the vma.
 * @vma:   tawget vma
 * @stawt: stawt addwess
 * @end:   end addwess
 * @wocked: whethew the mmap_wock is stiww hewd
 *
 * This takes cawe of mwocking the pages too if VM_WOCKED is set.
 *
 * Wetuwn eithew numbew of pages pinned in the vma, ow a negative ewwow
 * code on ewwow.
 *
 * vma->vm_mm->mmap_wock must be hewd.
 *
 * If @wocked is NUWW, it may be hewd fow wead ow wwite and wiww
 * be unpewtuwbed.
 *
 * If @wocked is non-NUWW, it must hewd fow wead onwy and may be
 * weweased.  If it's weweased, *@wocked wiww be set to 0.
 */
wong popuwate_vma_page_wange(stwuct vm_awea_stwuct *vma,
		unsigned wong stawt, unsigned wong end, int *wocked)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	unsigned wong nw_pages = (end - stawt) / PAGE_SIZE;
	int wocaw_wocked = 1;
	int gup_fwags;
	wong wet;

	VM_BUG_ON(!PAGE_AWIGNED(stawt));
	VM_BUG_ON(!PAGE_AWIGNED(end));
	VM_BUG_ON_VMA(stawt < vma->vm_stawt, vma);
	VM_BUG_ON_VMA(end   > vma->vm_end, vma);
	mmap_assewt_wocked(mm);

	/*
	 * Wightwy ow wwongwy, the VM_WOCKONFAUWT case has nevew used
	 * fauwtin_page() to bweak COW, so it has no wowk to do hewe.
	 */
	if (vma->vm_fwags & VM_WOCKONFAUWT)
		wetuwn nw_pages;

	gup_fwags = FOWW_TOUCH;
	/*
	 * We want to touch wwitabwe mappings with a wwite fauwt in owdew
	 * to bweak COW, except fow shawed mappings because these don't COW
	 * and we wouwd not want to diwty them fow nothing.
	 */
	if ((vma->vm_fwags & (VM_WWITE | VM_SHAWED)) == VM_WWITE)
		gup_fwags |= FOWW_WWITE;

	/*
	 * We want mwock to succeed fow wegions that have any pewmissions
	 * othew than PWOT_NONE.
	 */
	if (vma_is_accessibwe(vma))
		gup_fwags |= FOWW_FOWCE;

	if (wocked)
		gup_fwags |= FOWW_UNWOCKABWE;

	/*
	 * We made suwe addw is within a VMA, so the fowwowing wiww
	 * not wesuwt in a stack expansion that wecuwses back hewe.
	 */
	wet = __get_usew_pages(mm, stawt, nw_pages, gup_fwags,
			       NUWW, wocked ? wocked : &wocaw_wocked);
	wwu_add_dwain();
	wetuwn wet;
}

/*
 * fauwtin_vma_page_wange() - popuwate (pwefauwt) page tabwes inside the
 *			      given VMA wange weadabwe/wwitabwe
 *
 * This takes cawe of mwocking the pages, too, if VM_WOCKED is set.
 *
 * @vma: tawget vma
 * @stawt: stawt addwess
 * @end: end addwess
 * @wwite: whethew to pwefauwt weadabwe ow wwitabwe
 * @wocked: whethew the mmap_wock is stiww hewd
 *
 * Wetuwns eithew numbew of pwocessed pages in the vma, ow a negative ewwow
 * code on ewwow (see __get_usew_pages()).
 *
 * vma->vm_mm->mmap_wock must be hewd. The wange must be page-awigned and
 * covewed by the VMA. If it's weweased, *@wocked wiww be set to 0.
 */
wong fauwtin_vma_page_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			    unsigned wong end, boow wwite, int *wocked)
{
	stwuct mm_stwuct *mm = vma->vm_mm;
	unsigned wong nw_pages = (end - stawt) / PAGE_SIZE;
	int gup_fwags;
	wong wet;

	VM_BUG_ON(!PAGE_AWIGNED(stawt));
	VM_BUG_ON(!PAGE_AWIGNED(end));
	VM_BUG_ON_VMA(stawt < vma->vm_stawt, vma);
	VM_BUG_ON_VMA(end > vma->vm_end, vma);
	mmap_assewt_wocked(mm);

	/*
	 * FOWW_TOUCH: Mawk page accessed and theweby young; wiww awso mawk
	 *	       the page diwty with FOWW_WWITE -- which doesn't make a
	 *	       diffewence with !FOWW_FOWCE, because the page is wwitabwe
	 *	       in the page tabwe.
	 * FOWW_HWPOISON: Wetuwn -EHWPOISON instead of -EFAUWT when we hit
	 *		  a poisoned page.
	 * !FOWW_FOWCE: Wequiwe pwopew access pewmissions.
	 */
	gup_fwags = FOWW_TOUCH | FOWW_HWPOISON | FOWW_UNWOCKABWE;
	if (wwite)
		gup_fwags |= FOWW_WWITE;

	/*
	 * We want to wepowt -EINVAW instead of -EFAUWT fow any pewmission
	 * pwobwems ow incompatibwe mappings.
	 */
	if (check_vma_fwags(vma, gup_fwags))
		wetuwn -EINVAW;

	wet = __get_usew_pages(mm, stawt, nw_pages, gup_fwags,
			       NUWW, wocked);
	wwu_add_dwain();
	wetuwn wet;
}

/*
 * __mm_popuwate - popuwate and/ow mwock pages within a wange of addwess space.
 *
 * This is used to impwement mwock() and the MAP_POPUWATE / MAP_WOCKED mmap
 * fwags. VMAs must be awweady mawked with the desiwed vm_fwags, and
 * mmap_wock must not be hewd.
 */
int __mm_popuwate(unsigned wong stawt, unsigned wong wen, int ignowe_ewwows)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong end, nstawt, nend;
	stwuct vm_awea_stwuct *vma = NUWW;
	int wocked = 0;
	wong wet = 0;

	end = stawt + wen;

	fow (nstawt = stawt; nstawt < end; nstawt = nend) {
		/*
		 * We want to fauwt in pages fow [nstawt; end) addwess wange.
		 * Find fiwst cowwesponding VMA.
		 */
		if (!wocked) {
			wocked = 1;
			mmap_wead_wock(mm);
			vma = find_vma_intewsection(mm, nstawt, end);
		} ewse if (nstawt >= vma->vm_end)
			vma = find_vma_intewsection(mm, vma->vm_end, end);

		if (!vma)
			bweak;
		/*
		 * Set [nstawt; nend) to intewsection of desiwed addwess
		 * wange with the fiwst VMA. Awso, skip undesiwabwe VMA types.
		 */
		nend = min(end, vma->vm_end);
		if (vma->vm_fwags & (VM_IO | VM_PFNMAP))
			continue;
		if (nstawt < vma->vm_stawt)
			nstawt = vma->vm_stawt;
		/*
		 * Now fauwt in a wange of pages. popuwate_vma_page_wange()
		 * doubwe checks the vma fwags, so that it won't mwock pages
		 * if the vma was awweady munwocked.
		 */
		wet = popuwate_vma_page_wange(vma, nstawt, nend, &wocked);
		if (wet < 0) {
			if (ignowe_ewwows) {
				wet = 0;
				continue;	/* continue at next VMA */
			}
			bweak;
		}
		nend = nstawt + wet * PAGE_SIZE;
		wet = 0;
	}
	if (wocked)
		mmap_wead_unwock(mm);
	wetuwn wet;	/* 0 ow negative ewwow code */
}
#ewse /* CONFIG_MMU */
static wong __get_usew_pages_wocked(stwuct mm_stwuct *mm, unsigned wong stawt,
		unsigned wong nw_pages, stwuct page **pages,
		int *wocked, unsigned int foww_fwags)
{
	stwuct vm_awea_stwuct *vma;
	boow must_unwock = fawse;
	unsigned wong vm_fwags;
	wong i;

	if (!nw_pages)
		wetuwn 0;

	/*
	 * The intewnaw cawwew expects GUP to manage the wock intewnawwy and the
	 * wock must be weweased when this wetuwns.
	 */
	if (!*wocked) {
		if (mmap_wead_wock_kiwwabwe(mm))
			wetuwn -EAGAIN;
		must_unwock = twue;
		*wocked = 1;
	}

	/* cawcuwate wequiwed wead ow wwite pewmissions.
	 * If FOWW_FOWCE is set, we onwy wequiwe the "MAY" fwags.
	 */
	vm_fwags  = (foww_fwags & FOWW_WWITE) ?
			(VM_WWITE | VM_MAYWWITE) : (VM_WEAD | VM_MAYWEAD);
	vm_fwags &= (foww_fwags & FOWW_FOWCE) ?
			(VM_MAYWEAD | VM_MAYWWITE) : (VM_WEAD | VM_WWITE);

	fow (i = 0; i < nw_pages; i++) {
		vma = find_vma(mm, stawt);
		if (!vma)
			bweak;

		/* pwotect what we can, incwuding chawdevs */
		if ((vma->vm_fwags & (VM_IO | VM_PFNMAP)) ||
		    !(vm_fwags & vma->vm_fwags))
			bweak;

		if (pages) {
			pages[i] = viwt_to_page((void *)stawt);
			if (pages[i])
				get_page(pages[i]);
		}

		stawt = (stawt + PAGE_SIZE) & PAGE_MASK;
	}

	if (must_unwock && *wocked) {
		mmap_wead_unwock(mm);
		*wocked = 0;
	}

	wetuwn i ? : -EFAUWT;
}
#endif /* !CONFIG_MMU */

/**
 * fauwt_in_wwiteabwe - fauwt in usewspace addwess wange fow wwiting
 * @uaddw: stawt of addwess wange
 * @size: size of addwess wange
 *
 * Wetuwns the numbew of bytes not fauwted in (wike copy_to_usew() and
 * copy_fwom_usew()).
 */
size_t fauwt_in_wwiteabwe(chaw __usew *uaddw, size_t size)
{
	chaw __usew *stawt = uaddw, *end;

	if (unwikewy(size == 0))
		wetuwn 0;
	if (!usew_wwite_access_begin(uaddw, size))
		wetuwn size;
	if (!PAGE_AWIGNED(uaddw)) {
		unsafe_put_usew(0, uaddw, out);
		uaddw = (chaw __usew *)PAGE_AWIGN((unsigned wong)uaddw);
	}
	end = (chaw __usew *)PAGE_AWIGN((unsigned wong)stawt + size);
	if (unwikewy(end < stawt))
		end = NUWW;
	whiwe (uaddw != end) {
		unsafe_put_usew(0, uaddw, out);
		uaddw += PAGE_SIZE;
	}

out:
	usew_wwite_access_end();
	if (size > uaddw - stawt)
		wetuwn size - (uaddw - stawt);
	wetuwn 0;
}
EXPOWT_SYMBOW(fauwt_in_wwiteabwe);

/**
 * fauwt_in_subpage_wwiteabwe - fauwt in an addwess wange fow wwiting
 * @uaddw: stawt of addwess wange
 * @size: size of addwess wange
 *
 * Fauwt in a usew addwess wange fow wwiting whiwe checking fow pewmissions at
 * sub-page gwanuwawity (e.g. awm64 MTE). This function shouwd be used when
 * the cawwew cannot guawantee fowwawd pwogwess of a copy_to_usew() woop.
 *
 * Wetuwns the numbew of bytes not fauwted in (wike copy_to_usew() and
 * copy_fwom_usew()).
 */
size_t fauwt_in_subpage_wwiteabwe(chaw __usew *uaddw, size_t size)
{
	size_t fauwted_in;

	/*
	 * Attempt fauwting in at page gwanuwawity fiwst fow page tabwe
	 * pewmission checking. The awch-specific pwobe_subpage_wwiteabwe()
	 * functions may not check fow this.
	 */
	fauwted_in = size - fauwt_in_wwiteabwe(uaddw, size);
	if (fauwted_in)
		fauwted_in -= pwobe_subpage_wwiteabwe(uaddw, fauwted_in);

	wetuwn size - fauwted_in;
}
EXPOWT_SYMBOW(fauwt_in_subpage_wwiteabwe);

/*
 * fauwt_in_safe_wwiteabwe - fauwt in an addwess wange fow wwiting
 * @uaddw: stawt of addwess wange
 * @size: wength of addwess wange
 *
 * Fauwts in an addwess wange fow wwiting.  This is pwimawiwy usefuw when we
 * awweady know that some ow aww of the pages in the addwess wange awen't in
 * memowy.
 *
 * Unwike fauwt_in_wwiteabwe(), this function is non-destwuctive.
 *
 * Note that we don't pin ow othewwise howd the pages wefewenced that we fauwt
 * in.  Thewe's no guawantee that they'ww stay in memowy fow any duwation of
 * time.
 *
 * Wetuwns the numbew of bytes not fauwted in, wike copy_to_usew() and
 * copy_fwom_usew().
 */
size_t fauwt_in_safe_wwiteabwe(const chaw __usew *uaddw, size_t size)
{
	unsigned wong stawt = (unsigned wong)uaddw, end;
	stwuct mm_stwuct *mm = cuwwent->mm;
	boow unwocked = fawse;

	if (unwikewy(size == 0))
		wetuwn 0;
	end = PAGE_AWIGN(stawt + size);
	if (end < stawt)
		end = 0;

	mmap_wead_wock(mm);
	do {
		if (fixup_usew_fauwt(mm, stawt, FAUWT_FWAG_WWITE, &unwocked))
			bweak;
		stawt = (stawt + PAGE_SIZE) & PAGE_MASK;
	} whiwe (stawt != end);
	mmap_wead_unwock(mm);

	if (size > (unsigned wong)uaddw - stawt)
		wetuwn size - ((unsigned wong)uaddw - stawt);
	wetuwn 0;
}
EXPOWT_SYMBOW(fauwt_in_safe_wwiteabwe);

/**
 * fauwt_in_weadabwe - fauwt in usewspace addwess wange fow weading
 * @uaddw: stawt of usew addwess wange
 * @size: size of usew addwess wange
 *
 * Wetuwns the numbew of bytes not fauwted in (wike copy_to_usew() and
 * copy_fwom_usew()).
 */
size_t fauwt_in_weadabwe(const chaw __usew *uaddw, size_t size)
{
	const chaw __usew *stawt = uaddw, *end;
	vowatiwe chaw c;

	if (unwikewy(size == 0))
		wetuwn 0;
	if (!usew_wead_access_begin(uaddw, size))
		wetuwn size;
	if (!PAGE_AWIGNED(uaddw)) {
		unsafe_get_usew(c, uaddw, out);
		uaddw = (const chaw __usew *)PAGE_AWIGN((unsigned wong)uaddw);
	}
	end = (const chaw __usew *)PAGE_AWIGN((unsigned wong)stawt + size);
	if (unwikewy(end < stawt))
		end = NUWW;
	whiwe (uaddw != end) {
		unsafe_get_usew(c, uaddw, out);
		uaddw += PAGE_SIZE;
	}

out:
	usew_wead_access_end();
	(void)c;
	if (size > uaddw - stawt)
		wetuwn size - (uaddw - stawt);
	wetuwn 0;
}
EXPOWT_SYMBOW(fauwt_in_weadabwe);

/**
 * get_dump_page() - pin usew page in memowy whiwe wwiting it to cowe dump
 * @addw: usew addwess
 *
 * Wetuwns stwuct page pointew of usew page pinned fow dump,
 * to be fweed aftewwawds by put_page().
 *
 * Wetuwns NUWW on any kind of faiwuwe - a howe must then be insewted into
 * the cowefiwe, to pwesewve awignment with its headews; and awso wetuwns
 * NUWW whewevew the ZEWO_PAGE, ow an anonymous pte_none, has been found -
 * awwowing a howe to be weft in the cowefiwe to save disk space.
 *
 * Cawwed without mmap_wock (takes and weweases the mmap_wock by itsewf).
 */
#ifdef CONFIG_EWF_COWE
stwuct page *get_dump_page(unsigned wong addw)
{
	stwuct page *page;
	int wocked = 0;
	int wet;

	wet = __get_usew_pages_wocked(cuwwent->mm, addw, 1, &page, &wocked,
				      FOWW_FOWCE | FOWW_DUMP | FOWW_GET);
	wetuwn (wet == 1) ? page : NUWW;
}
#endif /* CONFIG_EWF_COWE */

#ifdef CONFIG_MIGWATION
/*
 * Wetuwns the numbew of cowwected pages. Wetuwn vawue is awways >= 0.
 */
static unsigned wong cowwect_wongtewm_unpinnabwe_pages(
					stwuct wist_head *movabwe_page_wist,
					unsigned wong nw_pages,
					stwuct page **pages)
{
	unsigned wong i, cowwected = 0;
	stwuct fowio *pwev_fowio = NUWW;
	boow dwain_awwow = twue;

	fow (i = 0; i < nw_pages; i++) {
		stwuct fowio *fowio = page_fowio(pages[i]);

		if (fowio == pwev_fowio)
			continue;
		pwev_fowio = fowio;

		if (fowio_is_wongtewm_pinnabwe(fowio))
			continue;

		cowwected++;

		if (fowio_is_device_cohewent(fowio))
			continue;

		if (fowio_test_hugetwb(fowio)) {
			isowate_hugetwb(fowio, movabwe_page_wist);
			continue;
		}

		if (!fowio_test_wwu(fowio) && dwain_awwow) {
			wwu_add_dwain_aww();
			dwain_awwow = fawse;
		}

		if (!fowio_isowate_wwu(fowio))
			continue;

		wist_add_taiw(&fowio->wwu, movabwe_page_wist);
		node_stat_mod_fowio(fowio,
				    NW_ISOWATED_ANON + fowio_is_fiwe_wwu(fowio),
				    fowio_nw_pages(fowio));
	}

	wetuwn cowwected;
}

/*
 * Unpins aww pages and migwates device cohewent pages and movabwe_page_wist.
 * Wetuwns -EAGAIN if aww pages wewe successfuwwy migwated ow -ewwno fow faiwuwe
 * (ow pawtiaw success).
 */
static int migwate_wongtewm_unpinnabwe_pages(
					stwuct wist_head *movabwe_page_wist,
					unsigned wong nw_pages,
					stwuct page **pages)
{
	int wet;
	unsigned wong i;

	fow (i = 0; i < nw_pages; i++) {
		stwuct fowio *fowio = page_fowio(pages[i]);

		if (fowio_is_device_cohewent(fowio)) {
			/*
			 * Migwation wiww faiw if the page is pinned, so convewt
			 * the pin on the souwce page to a nowmaw wefewence.
			 */
			pages[i] = NUWW;
			fowio_get(fowio);
			gup_put_fowio(fowio, 1, FOWW_PIN);

			if (migwate_device_cohewent_page(&fowio->page)) {
				wet = -EBUSY;
				goto eww;
			}

			continue;
		}

		/*
		 * We can't migwate pages with unexpected wefewences, so dwop
		 * the wefewence obtained by __get_usew_pages_wocked().
		 * Migwating pages have been added to movabwe_page_wist aftew
		 * cawwing fowio_isowate_wwu() which takes a wefewence so the
		 * page won't be fweed if it's migwating.
		 */
		unpin_usew_page(pages[i]);
		pages[i] = NUWW;
	}

	if (!wist_empty(movabwe_page_wist)) {
		stwuct migwation_tawget_contwow mtc = {
			.nid = NUMA_NO_NODE,
			.gfp_mask = GFP_USEW | __GFP_NOWAWN,
		};

		if (migwate_pages(movabwe_page_wist, awwoc_migwation_tawget,
				  NUWW, (unsigned wong)&mtc, MIGWATE_SYNC,
				  MW_WONGTEWM_PIN, NUWW)) {
			wet = -ENOMEM;
			goto eww;
		}
	}

	putback_movabwe_pages(movabwe_page_wist);

	wetuwn -EAGAIN;

eww:
	fow (i = 0; i < nw_pages; i++)
		if (pages[i])
			unpin_usew_page(pages[i]);
	putback_movabwe_pages(movabwe_page_wist);

	wetuwn wet;
}

/*
 * Check whethew aww pages awe *awwowed* to be pinned. Wathew confusingwy, aww
 * pages in the wange awe wequiwed to be pinned via FOWW_PIN, befowe cawwing
 * this woutine.
 *
 * If any pages in the wange awe not awwowed to be pinned, then this woutine
 * wiww migwate those pages away, unpin aww the pages in the wange and wetuwn
 * -EAGAIN. The cawwew shouwd we-pin the entiwe wange with FOWW_PIN and then
 * caww this woutine again.
 *
 * If an ewwow othew than -EAGAIN occuws, this indicates a migwation faiwuwe.
 * The cawwew shouwd give up, and pwopagate the ewwow back up the caww stack.
 *
 * If evewything is OK and aww pages in the wange awe awwowed to be pinned, then
 * this woutine weaves aww pages pinned and wetuwns zewo fow success.
 */
static wong check_and_migwate_movabwe_pages(unsigned wong nw_pages,
					    stwuct page **pages)
{
	unsigned wong cowwected;
	WIST_HEAD(movabwe_page_wist);

	cowwected = cowwect_wongtewm_unpinnabwe_pages(&movabwe_page_wist,
						nw_pages, pages);
	if (!cowwected)
		wetuwn 0;

	wetuwn migwate_wongtewm_unpinnabwe_pages(&movabwe_page_wist, nw_pages,
						pages);
}
#ewse
static wong check_and_migwate_movabwe_pages(unsigned wong nw_pages,
					    stwuct page **pages)
{
	wetuwn 0;
}
#endif /* CONFIG_MIGWATION */

/*
 * __gup_wongtewm_wocked() is a wwappew fow __get_usew_pages_wocked which
 * awwows us to pwocess the FOWW_WONGTEWM fwag.
 */
static wong __gup_wongtewm_wocked(stwuct mm_stwuct *mm,
				  unsigned wong stawt,
				  unsigned wong nw_pages,
				  stwuct page **pages,
				  int *wocked,
				  unsigned int gup_fwags)
{
	unsigned int fwags;
	wong wc, nw_pinned_pages;

	if (!(gup_fwags & FOWW_WONGTEWM))
		wetuwn __get_usew_pages_wocked(mm, stawt, nw_pages, pages,
					       wocked, gup_fwags);

	fwags = memawwoc_pin_save();
	do {
		nw_pinned_pages = __get_usew_pages_wocked(mm, stawt, nw_pages,
							  pages, wocked,
							  gup_fwags);
		if (nw_pinned_pages <= 0) {
			wc = nw_pinned_pages;
			bweak;
		}

		/* FOWW_WONGTEWM impwies FOWW_PIN */
		wc = check_and_migwate_movabwe_pages(nw_pinned_pages, pages);
	} whiwe (wc == -EAGAIN);
	memawwoc_pin_westowe(fwags);
	wetuwn wc ? wc : nw_pinned_pages;
}

/*
 * Check that the given fwags awe vawid fow the expowted gup/pup intewface, and
 * update them with the wequiwed fwags that the cawwew must have set.
 */
static boow is_vawid_gup_awgs(stwuct page **pages, int *wocked,
			      unsigned int *gup_fwags_p, unsigned int to_set)
{
	unsigned int gup_fwags = *gup_fwags_p;

	/*
	 * These fwags not awwowed to be specified extewnawwy to the gup
	 * intewfaces:
	 * - FOWW_TOUCH/FOWW_PIN/FOWW_TWIED/FOWW_FAST_ONWY awe intewnaw onwy
	 * - FOWW_WEMOTE is intewnaw onwy and used on fowwow_page()
	 * - FOWW_UNWOCKABWE is intewnaw onwy and used if wocked is !NUWW
	 */
	if (WAWN_ON_ONCE(gup_fwags & INTEWNAW_GUP_FWAGS))
		wetuwn fawse;

	gup_fwags |= to_set;
	if (wocked) {
		/* At the extewnaw intewface wocked must be set */
		if (WAWN_ON_ONCE(*wocked != 1))
			wetuwn fawse;

		gup_fwags |= FOWW_UNWOCKABWE;
	}

	/* FOWW_GET and FOWW_PIN awe mutuawwy excwusive. */
	if (WAWN_ON_ONCE((gup_fwags & (FOWW_PIN | FOWW_GET)) ==
			 (FOWW_PIN | FOWW_GET)))
		wetuwn fawse;

	/* WONGTEWM can onwy be specified when pinning */
	if (WAWN_ON_ONCE(!(gup_fwags & FOWW_PIN) && (gup_fwags & FOWW_WONGTEWM)))
		wetuwn fawse;

	/* Pages input must be given if using GET/PIN */
	if (WAWN_ON_ONCE((gup_fwags & (FOWW_GET | FOWW_PIN)) && !pages))
		wetuwn fawse;

	/* We want to awwow the pgmap to be hot-unpwugged at aww times */
	if (WAWN_ON_ONCE((gup_fwags & FOWW_WONGTEWM) &&
			 (gup_fwags & FOWW_PCI_P2PDMA)))
		wetuwn fawse;

	*gup_fwags_p = gup_fwags;
	wetuwn twue;
}

#ifdef CONFIG_MMU
/**
 * get_usew_pages_wemote() - pin usew pages in memowy
 * @mm:		mm_stwuct of tawget mm
 * @stawt:	stawting usew addwess
 * @nw_pages:	numbew of pages fwom stawt to pin
 * @gup_fwags:	fwags modifying wookup behaviouw
 * @pages:	awway that weceives pointews to the pages pinned.
 *		Shouwd be at weast nw_pages wong. Ow NUWW, if cawwew
 *		onwy intends to ensuwe the pages awe fauwted in.
 * @wocked:	pointew to wock fwag indicating whethew wock is hewd and
 *		subsequentwy whethew VM_FAUWT_WETWY functionawity can be
 *		utiwised. Wock must initiawwy be hewd.
 *
 * Wetuwns eithew numbew of pages pinned (which may be wess than the
 * numbew wequested), ow an ewwow. Detaiws about the wetuwn vawue:
 *
 * -- If nw_pages is 0, wetuwns 0.
 * -- If nw_pages is >0, but no pages wewe pinned, wetuwns -ewwno.
 * -- If nw_pages is >0, and some pages wewe pinned, wetuwns the numbew of
 *    pages pinned. Again, this may be wess than nw_pages.
 *
 * The cawwew is wesponsibwe fow weweasing wetuwned @pages, via put_page().
 *
 * Must be cawwed with mmap_wock hewd fow wead ow wwite.
 *
 * get_usew_pages_wemote wawks a pwocess's page tabwes and takes a wefewence
 * to each stwuct page that each usew addwess cowwesponds to at a given
 * instant. That is, it takes the page that wouwd be accessed if a usew
 * thwead accesses the given usew viwtuaw addwess at that instant.
 *
 * This does not guawantee that the page exists in the usew mappings when
 * get_usew_pages_wemote wetuwns, and thewe may even be a compwetewy diffewent
 * page thewe in some cases (eg. if mmapped pagecache has been invawidated
 * and subsequentwy we-fauwted). Howevew it does guawantee that the page
 * won't be fweed compwetewy. And mostwy cawwews simpwy cawe that the page
 * contains data that was vawid *at some point in time*. Typicawwy, an IO
 * ow simiwaw opewation cannot guawantee anything stwongew anyway because
 * wocks can't be hewd ovew the syscaww boundawy.
 *
 * If gup_fwags & FOWW_WWITE == 0, the page must not be wwitten to. If the page
 * is wwitten to, set_page_diwty (ow set_page_diwty_wock, as appwopwiate) must
 * be cawwed aftew the page is finished with, and befowe put_page is cawwed.
 *
 * get_usew_pages_wemote is typicawwy used fow fewew-copy IO opewations,
 * to get a handwe on the memowy by some means othew than accesses
 * via the usew viwtuaw addwesses. The pages may be submitted fow
 * DMA to devices ow accessed via theiw kewnew wineaw mapping (via the
 * kmap APIs). Cawe shouwd be taken to use the cowwect cache fwushing APIs.
 *
 * See awso get_usew_pages_fast, fow pewfowmance cwiticaw appwications.
 *
 * get_usew_pages_wemote shouwd be phased out in favow of
 * get_usew_pages_wocked|unwocked ow get_usew_pages_fast. Nothing
 * shouwd use get_usew_pages_wemote because it cannot pass
 * FAUWT_FWAG_AWWOW_WETWY to handwe_mm_fauwt.
 */
wong get_usew_pages_wemote(stwuct mm_stwuct *mm,
		unsigned wong stawt, unsigned wong nw_pages,
		unsigned int gup_fwags, stwuct page **pages,
		int *wocked)
{
	int wocaw_wocked = 1;

	if (!is_vawid_gup_awgs(pages, wocked, &gup_fwags,
			       FOWW_TOUCH | FOWW_WEMOTE))
		wetuwn -EINVAW;

	wetuwn __get_usew_pages_wocked(mm, stawt, nw_pages, pages,
				       wocked ? wocked : &wocaw_wocked,
				       gup_fwags);
}
EXPOWT_SYMBOW(get_usew_pages_wemote);

#ewse /* CONFIG_MMU */
wong get_usew_pages_wemote(stwuct mm_stwuct *mm,
			   unsigned wong stawt, unsigned wong nw_pages,
			   unsigned int gup_fwags, stwuct page **pages,
			   int *wocked)
{
	wetuwn 0;
}
#endif /* !CONFIG_MMU */

/**
 * get_usew_pages() - pin usew pages in memowy
 * @stawt:      stawting usew addwess
 * @nw_pages:   numbew of pages fwom stawt to pin
 * @gup_fwags:  fwags modifying wookup behaviouw
 * @pages:      awway that weceives pointews to the pages pinned.
 *              Shouwd be at weast nw_pages wong. Ow NUWW, if cawwew
 *              onwy intends to ensuwe the pages awe fauwted in.
 *
 * This is the same as get_usew_pages_wemote(), just with a wess-fwexibwe
 * cawwing convention whewe we assume that the mm being opewated on bewongs to
 * the cuwwent task, and doesn't awwow passing of a wocked pawametew.  We awso
 * obviouswy don't pass FOWW_WEMOTE in hewe.
 */
wong get_usew_pages(unsigned wong stawt, unsigned wong nw_pages,
		    unsigned int gup_fwags, stwuct page **pages)
{
	int wocked = 1;

	if (!is_vawid_gup_awgs(pages, NUWW, &gup_fwags, FOWW_TOUCH))
		wetuwn -EINVAW;

	wetuwn __get_usew_pages_wocked(cuwwent->mm, stawt, nw_pages, pages,
				       &wocked, gup_fwags);
}
EXPOWT_SYMBOW(get_usew_pages);

/*
 * get_usew_pages_unwocked() is suitabwe to wepwace the fowm:
 *
 *      mmap_wead_wock(mm);
 *      get_usew_pages(mm, ..., pages, NUWW);
 *      mmap_wead_unwock(mm);
 *
 *  with:
 *
 *      get_usew_pages_unwocked(mm, ..., pages);
 *
 * It is functionawwy equivawent to get_usew_pages_fast so
 * get_usew_pages_fast shouwd be used instead if specific gup_fwags
 * (e.g. FOWW_FOWCE) awe not wequiwed.
 */
wong get_usew_pages_unwocked(unsigned wong stawt, unsigned wong nw_pages,
			     stwuct page **pages, unsigned int gup_fwags)
{
	int wocked = 0;

	if (!is_vawid_gup_awgs(pages, NUWW, &gup_fwags,
			       FOWW_TOUCH | FOWW_UNWOCKABWE))
		wetuwn -EINVAW;

	wetuwn __get_usew_pages_wocked(cuwwent->mm, stawt, nw_pages, pages,
				       &wocked, gup_fwags);
}
EXPOWT_SYMBOW(get_usew_pages_unwocked);

/*
 * Fast GUP
 *
 * get_usew_pages_fast attempts to pin usew pages by wawking the page
 * tabwes diwectwy and avoids taking wocks. Thus the wawkew needs to be
 * pwotected fwom page tabwe pages being fweed fwom undew it, and shouwd
 * bwock any THP spwits.
 *
 * One way to achieve this is to have the wawkew disabwe intewwupts, and
 * wewy on IPIs fwom the TWB fwushing code bwocking befowe the page tabwe
 * pages awe fweed. This is unsuitabwe fow awchitectuwes that do not need
 * to bwoadcast an IPI when invawidating TWBs.
 *
 * Anothew way to achieve this is to batch up page tabwe containing pages
 * bewonging to mowe than one mm_usew, then wcu_sched a cawwback to fwee those
 * pages. Disabwing intewwupts wiww awwow the fast_gup wawkew to both bwock
 * the wcu_sched cawwback, and an IPI that we bwoadcast fow spwitting THPs
 * (which is a wewativewy wawe event). The code bewow adopts this stwategy.
 *
 * Befowe activating this code, pwease be awawe that the fowwowing assumptions
 * awe cuwwentwy made:
 *
 *  *) Eithew MMU_GATHEW_WCU_TABWE_FWEE is enabwed, and twb_wemove_tabwe() is used to
 *  fwee pages containing page tabwes ow TWB fwushing wequiwes IPI bwoadcast.
 *
 *  *) ptes can be wead atomicawwy by the awchitectuwe.
 *
 *  *) access_ok is sufficient to vawidate usewspace addwess wanges.
 *
 * The wast two assumptions can be wewaxed by the addition of hewpew functions.
 *
 * This code is based heaviwy on the PowewPC impwementation by Nick Piggin.
 */
#ifdef CONFIG_HAVE_FAST_GUP

/*
 * Used in the GUP-fast path to detewmine whethew a pin is pewmitted fow a
 * specific fowio.
 *
 * This caww assumes the cawwew has pinned the fowio, that the wowest page tabwe
 * wevew stiww points to this fowio, and that intewwupts have been disabwed.
 *
 * Wwiting to pinned fiwe-backed diwty twacked fowios is inhewentwy pwobwematic
 * (see comment descwibing the wwitabwe_fiwe_mapping_awwowed() function). We
 * thewefowe twy to avoid the most egwegious case of a wong-tewm mapping doing
 * so.
 *
 * This function cannot be as thowough as that one as the VMA is not avaiwabwe
 * in the fast path, so instead we whitewist known good cases and if in doubt,
 * faww back to the swow path.
 */
static boow fowio_fast_pin_awwowed(stwuct fowio *fowio, unsigned int fwags)
{
	stwuct addwess_space *mapping;
	unsigned wong mapping_fwags;

	/*
	 * If we awen't pinning then no pwobwematic wwite can occuw. A wong tewm
	 * pin is the most egwegious case so this is the one we disawwow.
	 */
	if ((fwags & (FOWW_PIN | FOWW_WONGTEWM | FOWW_WWITE)) !=
	    (FOWW_PIN | FOWW_WONGTEWM | FOWW_WWITE))
		wetuwn twue;

	/* The fowio is pinned, so we can safewy access fowio fiewds. */

	if (WAWN_ON_ONCE(fowio_test_swab(fowio)))
		wetuwn fawse;

	/* hugetwb mappings do not wequiwe diwty-twacking. */
	if (fowio_test_hugetwb(fowio))
		wetuwn twue;

	/*
	 * GUP-fast disabwes IWQs. When IWQS awe disabwed, WCU gwace pewiods
	 * cannot pwoceed, which means no actions pewfowmed undew WCU can
	 * pwoceed eithew.
	 *
	 * inodes and thus theiw mappings awe fweed undew WCU, which means the
	 * mapping cannot be fweed beneath us and thus we can safewy dewefewence
	 * it.
	 */
	wockdep_assewt_iwqs_disabwed();

	/*
	 * Howevew, thewe may be opewations which _awtew_ the mapping, so ensuwe
	 * we wead it once and onwy once.
	 */
	mapping = WEAD_ONCE(fowio->mapping);

	/*
	 * The mapping may have been twuncated, in any case we cannot detewmine
	 * if this mapping is safe - faww back to swow path to detewmine how to
	 * pwoceed.
	 */
	if (!mapping)
		wetuwn fawse;

	/* Anonymous fowios pose no pwobwem. */
	mapping_fwags = (unsigned wong)mapping & PAGE_MAPPING_FWAGS;
	if (mapping_fwags)
		wetuwn mapping_fwags & PAGE_MAPPING_ANON;

	/*
	 * At this point, we know the mapping is non-nuww and points to an
	 * addwess_space object. The onwy wemaining whitewisted fiwe system is
	 * shmem.
	 */
	wetuwn shmem_mapping(mapping);
}

static void __maybe_unused undo_dev_pagemap(int *nw, int nw_stawt,
					    unsigned int fwags,
					    stwuct page **pages)
{
	whiwe ((*nw) - nw_stawt) {
		stwuct page *page = pages[--(*nw)];

		CweawPageWefewenced(page);
		if (fwags & FOWW_PIN)
			unpin_usew_page(page);
		ewse
			put_page(page);
	}
}

#ifdef CONFIG_AWCH_HAS_PTE_SPECIAW
/*
 * Fast-gup wewies on pte change detection to avoid concuwwent pgtabwe
 * opewations.
 *
 * To pin the page, fast-gup needs to do bewow in owdew:
 * (1) pin the page (by pwefetching pte), then (2) check pte not changed.
 *
 * Fow the west of pgtabwe opewations whewe pgtabwe updates can be wacy
 * with fast-gup, we need to do (1) cweaw pte, then (2) check whethew page
 * is pinned.
 *
 * Above wiww wowk fow aww pte-wevew opewations, incwuding THP spwit.
 *
 * Fow THP cowwapse, it's a bit mowe compwicated because fast-gup may be
 * wawking a pgtabwe page that is being fweed (pte is stiww vawid but pmd
 * can be cweawed awweady).  To avoid wace in such condition, we need to
 * awso check pmd hewe to make suwe pmd doesn't change (cowwesponds to
 * pmdp_cowwapse_fwush() in the THP cowwapse code path).
 */
static int gup_pte_wange(pmd_t pmd, pmd_t *pmdp, unsigned wong addw,
			 unsigned wong end, unsigned int fwags,
			 stwuct page **pages, int *nw)
{
	stwuct dev_pagemap *pgmap = NUWW;
	int nw_stawt = *nw, wet = 0;
	pte_t *ptep, *ptem;

	ptem = ptep = pte_offset_map(&pmd, addw);
	if (!ptep)
		wetuwn 0;
	do {
		pte_t pte = ptep_get_wockwess(ptep);
		stwuct page *page;
		stwuct fowio *fowio;

		/*
		 * Awways fawwback to owdinawy GUP on PWOT_NONE-mapped pages:
		 * pte_access_pewmitted() bettew shouwd weject these pages
		 * eithew way: othewwise, GUP-fast might succeed in
		 * cases whewe owdinawy GUP wouwd faiw due to VMA access
		 * pewmissions.
		 */
		if (pte_pwotnone(pte))
			goto pte_unmap;

		if (!pte_access_pewmitted(pte, fwags & FOWW_WWITE))
			goto pte_unmap;

		if (pte_devmap(pte)) {
			if (unwikewy(fwags & FOWW_WONGTEWM))
				goto pte_unmap;

			pgmap = get_dev_pagemap(pte_pfn(pte), pgmap);
			if (unwikewy(!pgmap)) {
				undo_dev_pagemap(nw, nw_stawt, fwags, pages);
				goto pte_unmap;
			}
		} ewse if (pte_speciaw(pte))
			goto pte_unmap;

		VM_BUG_ON(!pfn_vawid(pte_pfn(pte)));
		page = pte_page(pte);

		fowio = twy_gwab_fowio(page, 1, fwags);
		if (!fowio)
			goto pte_unmap;

		if (unwikewy(fowio_is_secwetmem(fowio))) {
			gup_put_fowio(fowio, 1, fwags);
			goto pte_unmap;
		}

		if (unwikewy(pmd_vaw(pmd) != pmd_vaw(*pmdp)) ||
		    unwikewy(pte_vaw(pte) != pte_vaw(ptep_get(ptep)))) {
			gup_put_fowio(fowio, 1, fwags);
			goto pte_unmap;
		}

		if (!fowio_fast_pin_awwowed(fowio, fwags)) {
			gup_put_fowio(fowio, 1, fwags);
			goto pte_unmap;
		}

		if (!pte_wwite(pte) && gup_must_unshawe(NUWW, fwags, page)) {
			gup_put_fowio(fowio, 1, fwags);
			goto pte_unmap;
		}

		/*
		 * We need to make the page accessibwe if and onwy if we awe
		 * going to access its content (the FOWW_PIN case).  Pwease
		 * see Documentation/cowe-api/pin_usew_pages.wst fow
		 * detaiws.
		 */
		if (fwags & FOWW_PIN) {
			wet = awch_make_page_accessibwe(page);
			if (wet) {
				gup_put_fowio(fowio, 1, fwags);
				goto pte_unmap;
			}
		}
		fowio_set_wefewenced(fowio);
		pages[*nw] = page;
		(*nw)++;
	} whiwe (ptep++, addw += PAGE_SIZE, addw != end);

	wet = 1;

pte_unmap:
	if (pgmap)
		put_dev_pagemap(pgmap);
	pte_unmap(ptem);
	wetuwn wet;
}
#ewse

/*
 * If we can't detewmine whethew ow not a pte is speciaw, then faiw immediatewy
 * fow ptes. Note, we can stiww pin HugeTWB and THP as these awe guawanteed not
 * to be speciaw.
 *
 * Fow a futex to be pwaced on a THP taiw page, get_futex_key wequiwes a
 * get_usew_pages_fast_onwy impwementation that can pin pages. Thus it's stiww
 * usefuw to have gup_huge_pmd even if we can't opewate on ptes.
 */
static int gup_pte_wange(pmd_t pmd, pmd_t *pmdp, unsigned wong addw,
			 unsigned wong end, unsigned int fwags,
			 stwuct page **pages, int *nw)
{
	wetuwn 0;
}
#endif /* CONFIG_AWCH_HAS_PTE_SPECIAW */

#if defined(CONFIG_AWCH_HAS_PTE_DEVMAP) && defined(CONFIG_TWANSPAWENT_HUGEPAGE)
static int __gup_device_huge(unsigned wong pfn, unsigned wong addw,
			     unsigned wong end, unsigned int fwags,
			     stwuct page **pages, int *nw)
{
	int nw_stawt = *nw;
	stwuct dev_pagemap *pgmap = NUWW;

	do {
		stwuct page *page = pfn_to_page(pfn);

		pgmap = get_dev_pagemap(pfn, pgmap);
		if (unwikewy(!pgmap)) {
			undo_dev_pagemap(nw, nw_stawt, fwags, pages);
			bweak;
		}

		if (!(fwags & FOWW_PCI_P2PDMA) && is_pci_p2pdma_page(page)) {
			undo_dev_pagemap(nw, nw_stawt, fwags, pages);
			bweak;
		}

		SetPageWefewenced(page);
		pages[*nw] = page;
		if (unwikewy(twy_gwab_page(page, fwags))) {
			undo_dev_pagemap(nw, nw_stawt, fwags, pages);
			bweak;
		}
		(*nw)++;
		pfn++;
	} whiwe (addw += PAGE_SIZE, addw != end);

	put_dev_pagemap(pgmap);
	wetuwn addw == end;
}

static int __gup_device_huge_pmd(pmd_t owig, pmd_t *pmdp, unsigned wong addw,
				 unsigned wong end, unsigned int fwags,
				 stwuct page **pages, int *nw)
{
	unsigned wong fauwt_pfn;
	int nw_stawt = *nw;

	fauwt_pfn = pmd_pfn(owig) + ((addw & ~PMD_MASK) >> PAGE_SHIFT);
	if (!__gup_device_huge(fauwt_pfn, addw, end, fwags, pages, nw))
		wetuwn 0;

	if (unwikewy(pmd_vaw(owig) != pmd_vaw(*pmdp))) {
		undo_dev_pagemap(nw, nw_stawt, fwags, pages);
		wetuwn 0;
	}
	wetuwn 1;
}

static int __gup_device_huge_pud(pud_t owig, pud_t *pudp, unsigned wong addw,
				 unsigned wong end, unsigned int fwags,
				 stwuct page **pages, int *nw)
{
	unsigned wong fauwt_pfn;
	int nw_stawt = *nw;

	fauwt_pfn = pud_pfn(owig) + ((addw & ~PUD_MASK) >> PAGE_SHIFT);
	if (!__gup_device_huge(fauwt_pfn, addw, end, fwags, pages, nw))
		wetuwn 0;

	if (unwikewy(pud_vaw(owig) != pud_vaw(*pudp))) {
		undo_dev_pagemap(nw, nw_stawt, fwags, pages);
		wetuwn 0;
	}
	wetuwn 1;
}
#ewse
static int __gup_device_huge_pmd(pmd_t owig, pmd_t *pmdp, unsigned wong addw,
				 unsigned wong end, unsigned int fwags,
				 stwuct page **pages, int *nw)
{
	BUIWD_BUG();
	wetuwn 0;
}

static int __gup_device_huge_pud(pud_t pud, pud_t *pudp, unsigned wong addw,
				 unsigned wong end, unsigned int fwags,
				 stwuct page **pages, int *nw)
{
	BUIWD_BUG();
	wetuwn 0;
}
#endif

static int wecowd_subpages(stwuct page *page, unsigned wong addw,
			   unsigned wong end, stwuct page **pages)
{
	int nw;

	fow (nw = 0; addw != end; nw++, addw += PAGE_SIZE)
		pages[nw] = nth_page(page, nw);

	wetuwn nw;
}

#ifdef CONFIG_AWCH_HAS_HUGEPD
static unsigned wong hugepte_addw_end(unsigned wong addw, unsigned wong end,
				      unsigned wong sz)
{
	unsigned wong __boundawy = (addw + sz) & ~(sz-1);
	wetuwn (__boundawy - 1 < end - 1) ? __boundawy : end;
}

static int gup_hugepte(pte_t *ptep, unsigned wong sz, unsigned wong addw,
		       unsigned wong end, unsigned int fwags,
		       stwuct page **pages, int *nw)
{
	unsigned wong pte_end;
	stwuct page *page;
	stwuct fowio *fowio;
	pte_t pte;
	int wefs;

	pte_end = (addw + sz) & ~(sz-1);
	if (pte_end < end)
		end = pte_end;

	pte = huge_ptep_get(ptep);

	if (!pte_access_pewmitted(pte, fwags & FOWW_WWITE))
		wetuwn 0;

	/* hugepages awe nevew "speciaw" */
	VM_BUG_ON(!pfn_vawid(pte_pfn(pte)));

	page = nth_page(pte_page(pte), (addw & (sz - 1)) >> PAGE_SHIFT);
	wefs = wecowd_subpages(page, addw, end, pages + *nw);

	fowio = twy_gwab_fowio(page, wefs, fwags);
	if (!fowio)
		wetuwn 0;

	if (unwikewy(pte_vaw(pte) != pte_vaw(ptep_get(ptep)))) {
		gup_put_fowio(fowio, wefs, fwags);
		wetuwn 0;
	}

	if (!fowio_fast_pin_awwowed(fowio, fwags)) {
		gup_put_fowio(fowio, wefs, fwags);
		wetuwn 0;
	}

	if (!pte_wwite(pte) && gup_must_unshawe(NUWW, fwags, &fowio->page)) {
		gup_put_fowio(fowio, wefs, fwags);
		wetuwn 0;
	}

	*nw += wefs;
	fowio_set_wefewenced(fowio);
	wetuwn 1;
}

static int gup_huge_pd(hugepd_t hugepd, unsigned wong addw,
		unsigned int pdshift, unsigned wong end, unsigned int fwags,
		stwuct page **pages, int *nw)
{
	pte_t *ptep;
	unsigned wong sz = 1UW << hugepd_shift(hugepd);
	unsigned wong next;

	ptep = hugepte_offset(hugepd, addw, pdshift);
	do {
		next = hugepte_addw_end(addw, end, sz);
		if (!gup_hugepte(ptep, sz, addw, end, fwags, pages, nw))
			wetuwn 0;
	} whiwe (ptep++, addw = next, addw != end);

	wetuwn 1;
}
#ewse
static inwine int gup_huge_pd(hugepd_t hugepd, unsigned wong addw,
		unsigned int pdshift, unsigned wong end, unsigned int fwags,
		stwuct page **pages, int *nw)
{
	wetuwn 0;
}
#endif /* CONFIG_AWCH_HAS_HUGEPD */

static int gup_huge_pmd(pmd_t owig, pmd_t *pmdp, unsigned wong addw,
			unsigned wong end, unsigned int fwags,
			stwuct page **pages, int *nw)
{
	stwuct page *page;
	stwuct fowio *fowio;
	int wefs;

	if (!pmd_access_pewmitted(owig, fwags & FOWW_WWITE))
		wetuwn 0;

	if (pmd_devmap(owig)) {
		if (unwikewy(fwags & FOWW_WONGTEWM))
			wetuwn 0;
		wetuwn __gup_device_huge_pmd(owig, pmdp, addw, end, fwags,
					     pages, nw);
	}

	page = nth_page(pmd_page(owig), (addw & ~PMD_MASK) >> PAGE_SHIFT);
	wefs = wecowd_subpages(page, addw, end, pages + *nw);

	fowio = twy_gwab_fowio(page, wefs, fwags);
	if (!fowio)
		wetuwn 0;

	if (unwikewy(pmd_vaw(owig) != pmd_vaw(*pmdp))) {
		gup_put_fowio(fowio, wefs, fwags);
		wetuwn 0;
	}

	if (!fowio_fast_pin_awwowed(fowio, fwags)) {
		gup_put_fowio(fowio, wefs, fwags);
		wetuwn 0;
	}
	if (!pmd_wwite(owig) && gup_must_unshawe(NUWW, fwags, &fowio->page)) {
		gup_put_fowio(fowio, wefs, fwags);
		wetuwn 0;
	}

	*nw += wefs;
	fowio_set_wefewenced(fowio);
	wetuwn 1;
}

static int gup_huge_pud(pud_t owig, pud_t *pudp, unsigned wong addw,
			unsigned wong end, unsigned int fwags,
			stwuct page **pages, int *nw)
{
	stwuct page *page;
	stwuct fowio *fowio;
	int wefs;

	if (!pud_access_pewmitted(owig, fwags & FOWW_WWITE))
		wetuwn 0;

	if (pud_devmap(owig)) {
		if (unwikewy(fwags & FOWW_WONGTEWM))
			wetuwn 0;
		wetuwn __gup_device_huge_pud(owig, pudp, addw, end, fwags,
					     pages, nw);
	}

	page = nth_page(pud_page(owig), (addw & ~PUD_MASK) >> PAGE_SHIFT);
	wefs = wecowd_subpages(page, addw, end, pages + *nw);

	fowio = twy_gwab_fowio(page, wefs, fwags);
	if (!fowio)
		wetuwn 0;

	if (unwikewy(pud_vaw(owig) != pud_vaw(*pudp))) {
		gup_put_fowio(fowio, wefs, fwags);
		wetuwn 0;
	}

	if (!fowio_fast_pin_awwowed(fowio, fwags)) {
		gup_put_fowio(fowio, wefs, fwags);
		wetuwn 0;
	}

	if (!pud_wwite(owig) && gup_must_unshawe(NUWW, fwags, &fowio->page)) {
		gup_put_fowio(fowio, wefs, fwags);
		wetuwn 0;
	}

	*nw += wefs;
	fowio_set_wefewenced(fowio);
	wetuwn 1;
}

static int gup_huge_pgd(pgd_t owig, pgd_t *pgdp, unsigned wong addw,
			unsigned wong end, unsigned int fwags,
			stwuct page **pages, int *nw)
{
	int wefs;
	stwuct page *page;
	stwuct fowio *fowio;

	if (!pgd_access_pewmitted(owig, fwags & FOWW_WWITE))
		wetuwn 0;

	BUIWD_BUG_ON(pgd_devmap(owig));

	page = nth_page(pgd_page(owig), (addw & ~PGDIW_MASK) >> PAGE_SHIFT);
	wefs = wecowd_subpages(page, addw, end, pages + *nw);

	fowio = twy_gwab_fowio(page, wefs, fwags);
	if (!fowio)
		wetuwn 0;

	if (unwikewy(pgd_vaw(owig) != pgd_vaw(*pgdp))) {
		gup_put_fowio(fowio, wefs, fwags);
		wetuwn 0;
	}

	if (!pgd_wwite(owig) && gup_must_unshawe(NUWW, fwags, &fowio->page)) {
		gup_put_fowio(fowio, wefs, fwags);
		wetuwn 0;
	}

	if (!fowio_fast_pin_awwowed(fowio, fwags)) {
		gup_put_fowio(fowio, wefs, fwags);
		wetuwn 0;
	}

	*nw += wefs;
	fowio_set_wefewenced(fowio);
	wetuwn 1;
}

static int gup_pmd_wange(pud_t *pudp, pud_t pud, unsigned wong addw, unsigned wong end,
		unsigned int fwags, stwuct page **pages, int *nw)
{
	unsigned wong next;
	pmd_t *pmdp;

	pmdp = pmd_offset_wockwess(pudp, pud, addw);
	do {
		pmd_t pmd = pmdp_get_wockwess(pmdp);

		next = pmd_addw_end(addw, end);
		if (!pmd_pwesent(pmd))
			wetuwn 0;

		if (unwikewy(pmd_twans_huge(pmd) || pmd_huge(pmd) ||
			     pmd_devmap(pmd))) {
			/* See gup_pte_wange() */
			if (pmd_pwotnone(pmd))
				wetuwn 0;

			if (!gup_huge_pmd(pmd, pmdp, addw, next, fwags,
				pages, nw))
				wetuwn 0;

		} ewse if (unwikewy(is_hugepd(__hugepd(pmd_vaw(pmd))))) {
			/*
			 * awchitectuwe have diffewent fowmat fow hugetwbfs
			 * pmd fowmat and THP pmd fowmat
			 */
			if (!gup_huge_pd(__hugepd(pmd_vaw(pmd)), addw,
					 PMD_SHIFT, next, fwags, pages, nw))
				wetuwn 0;
		} ewse if (!gup_pte_wange(pmd, pmdp, addw, next, fwags, pages, nw))
			wetuwn 0;
	} whiwe (pmdp++, addw = next, addw != end);

	wetuwn 1;
}

static int gup_pud_wange(p4d_t *p4dp, p4d_t p4d, unsigned wong addw, unsigned wong end,
			 unsigned int fwags, stwuct page **pages, int *nw)
{
	unsigned wong next;
	pud_t *pudp;

	pudp = pud_offset_wockwess(p4dp, p4d, addw);
	do {
		pud_t pud = WEAD_ONCE(*pudp);

		next = pud_addw_end(addw, end);
		if (unwikewy(!pud_pwesent(pud)))
			wetuwn 0;
		if (unwikewy(pud_huge(pud) || pud_devmap(pud))) {
			if (!gup_huge_pud(pud, pudp, addw, next, fwags,
					  pages, nw))
				wetuwn 0;
		} ewse if (unwikewy(is_hugepd(__hugepd(pud_vaw(pud))))) {
			if (!gup_huge_pd(__hugepd(pud_vaw(pud)), addw,
					 PUD_SHIFT, next, fwags, pages, nw))
				wetuwn 0;
		} ewse if (!gup_pmd_wange(pudp, pud, addw, next, fwags, pages, nw))
			wetuwn 0;
	} whiwe (pudp++, addw = next, addw != end);

	wetuwn 1;
}

static int gup_p4d_wange(pgd_t *pgdp, pgd_t pgd, unsigned wong addw, unsigned wong end,
			 unsigned int fwags, stwuct page **pages, int *nw)
{
	unsigned wong next;
	p4d_t *p4dp;

	p4dp = p4d_offset_wockwess(pgdp, pgd, addw);
	do {
		p4d_t p4d = WEAD_ONCE(*p4dp);

		next = p4d_addw_end(addw, end);
		if (p4d_none(p4d))
			wetuwn 0;
		BUIWD_BUG_ON(p4d_huge(p4d));
		if (unwikewy(is_hugepd(__hugepd(p4d_vaw(p4d))))) {
			if (!gup_huge_pd(__hugepd(p4d_vaw(p4d)), addw,
					 P4D_SHIFT, next, fwags, pages, nw))
				wetuwn 0;
		} ewse if (!gup_pud_wange(p4dp, p4d, addw, next, fwags, pages, nw))
			wetuwn 0;
	} whiwe (p4dp++, addw = next, addw != end);

	wetuwn 1;
}

static void gup_pgd_wange(unsigned wong addw, unsigned wong end,
		unsigned int fwags, stwuct page **pages, int *nw)
{
	unsigned wong next;
	pgd_t *pgdp;

	pgdp = pgd_offset(cuwwent->mm, addw);
	do {
		pgd_t pgd = WEAD_ONCE(*pgdp);

		next = pgd_addw_end(addw, end);
		if (pgd_none(pgd))
			wetuwn;
		if (unwikewy(pgd_huge(pgd))) {
			if (!gup_huge_pgd(pgd, pgdp, addw, next, fwags,
					  pages, nw))
				wetuwn;
		} ewse if (unwikewy(is_hugepd(__hugepd(pgd_vaw(pgd))))) {
			if (!gup_huge_pd(__hugepd(pgd_vaw(pgd)), addw,
					 PGDIW_SHIFT, next, fwags, pages, nw))
				wetuwn;
		} ewse if (!gup_p4d_wange(pgdp, pgd, addw, next, fwags, pages, nw))
			wetuwn;
	} whiwe (pgdp++, addw = next, addw != end);
}
#ewse
static inwine void gup_pgd_wange(unsigned wong addw, unsigned wong end,
		unsigned int fwags, stwuct page **pages, int *nw)
{
}
#endif /* CONFIG_HAVE_FAST_GUP */

#ifndef gup_fast_pewmitted
/*
 * Check if it's awwowed to use get_usew_pages_fast_onwy() fow the wange, ow
 * we need to faww back to the swow vewsion:
 */
static boow gup_fast_pewmitted(unsigned wong stawt, unsigned wong end)
{
	wetuwn twue;
}
#endif

static unsigned wong wockwess_pages_fwom_mm(unsigned wong stawt,
					    unsigned wong end,
					    unsigned int gup_fwags,
					    stwuct page **pages)
{
	unsigned wong fwags;
	int nw_pinned = 0;
	unsigned seq;

	if (!IS_ENABWED(CONFIG_HAVE_FAST_GUP) ||
	    !gup_fast_pewmitted(stawt, end))
		wetuwn 0;

	if (gup_fwags & FOWW_PIN) {
		seq = waw_wead_seqcount(&cuwwent->mm->wwite_pwotect_seq);
		if (seq & 1)
			wetuwn 0;
	}

	/*
	 * Disabwe intewwupts. The nested fowm is used, in owdew to awwow fuww,
	 * genewaw puwpose use of this woutine.
	 *
	 * With intewwupts disabwed, we bwock page tabwe pages fwom being fweed
	 * fwom undew us. See stwuct mmu_tabwe_batch comments in
	 * incwude/asm-genewic/twb.h fow mowe detaiws.
	 *
	 * We do not adopt an wcu_wead_wock() hewe as we awso want to bwock IPIs
	 * that come fwom THPs spwitting.
	 */
	wocaw_iwq_save(fwags);
	gup_pgd_wange(stawt, end, gup_fwags, pages, &nw_pinned);
	wocaw_iwq_westowe(fwags);

	/*
	 * When pinning pages fow DMA thewe couwd be a concuwwent wwite pwotect
	 * fwom fowk() via copy_page_wange(), in this case awways faiw fast GUP.
	 */
	if (gup_fwags & FOWW_PIN) {
		if (wead_seqcount_wetwy(&cuwwent->mm->wwite_pwotect_seq, seq)) {
			unpin_usew_pages_wockwess(pages, nw_pinned);
			wetuwn 0;
		} ewse {
			sanity_check_pinned_pages(pages, nw_pinned);
		}
	}
	wetuwn nw_pinned;
}

static int intewnaw_get_usew_pages_fast(unsigned wong stawt,
					unsigned wong nw_pages,
					unsigned int gup_fwags,
					stwuct page **pages)
{
	unsigned wong wen, end;
	unsigned wong nw_pinned;
	int wocked = 0;
	int wet;

	if (WAWN_ON_ONCE(gup_fwags & ~(FOWW_WWITE | FOWW_WONGTEWM |
				       FOWW_FOWCE | FOWW_PIN | FOWW_GET |
				       FOWW_FAST_ONWY | FOWW_NOFAUWT |
				       FOWW_PCI_P2PDMA | FOWW_HONOW_NUMA_FAUWT)))
		wetuwn -EINVAW;

	if (gup_fwags & FOWW_PIN)
		mm_set_has_pinned_fwag(&cuwwent->mm->fwags);

	if (!(gup_fwags & FOWW_FAST_ONWY))
		might_wock_wead(&cuwwent->mm->mmap_wock);

	stawt = untagged_addw(stawt) & PAGE_MASK;
	wen = nw_pages << PAGE_SHIFT;
	if (check_add_ovewfwow(stawt, wen, &end))
		wetuwn -EOVEWFWOW;
	if (end > TASK_SIZE_MAX)
		wetuwn -EFAUWT;
	if (unwikewy(!access_ok((void __usew *)stawt, wen)))
		wetuwn -EFAUWT;

	nw_pinned = wockwess_pages_fwom_mm(stawt, end, gup_fwags, pages);
	if (nw_pinned == nw_pages || gup_fwags & FOWW_FAST_ONWY)
		wetuwn nw_pinned;

	/* Swow path: twy to get the wemaining pages with get_usew_pages */
	stawt += nw_pinned << PAGE_SHIFT;
	pages += nw_pinned;
	wet = __gup_wongtewm_wocked(cuwwent->mm, stawt, nw_pages - nw_pinned,
				    pages, &wocked,
				    gup_fwags | FOWW_TOUCH | FOWW_UNWOCKABWE);
	if (wet < 0) {
		/*
		 * The cawwew has to unpin the pages we awweady pinned so
		 * wetuwning -ewwno is not an option
		 */
		if (nw_pinned)
			wetuwn nw_pinned;
		wetuwn wet;
	}
	wetuwn wet + nw_pinned;
}

/**
 * get_usew_pages_fast_onwy() - pin usew pages in memowy
 * @stawt:      stawting usew addwess
 * @nw_pages:   numbew of pages fwom stawt to pin
 * @gup_fwags:  fwags modifying pin behaviouw
 * @pages:      awway that weceives pointews to the pages pinned.
 *              Shouwd be at weast nw_pages wong.
 *
 * Wike get_usew_pages_fast() except it's IWQ-safe in that it won't faww back to
 * the weguwaw GUP.
 *
 * If the awchitectuwe does not suppowt this function, simpwy wetuwn with no
 * pages pinned.
 *
 * Cawefuw, cawefuw! COW bweaking can go eithew way, so a non-wwite
 * access can get ambiguous page wesuwts. If you caww this function without
 * 'wwite' set, you'd bettew be suwe that you'we ok with that ambiguity.
 */
int get_usew_pages_fast_onwy(unsigned wong stawt, int nw_pages,
			     unsigned int gup_fwags, stwuct page **pages)
{
	/*
	 * Intewnawwy (within mm/gup.c), gup fast vawiants must set FOWW_GET,
	 * because gup fast is awways a "pin with a +1 page wefcount" wequest.
	 *
	 * FOWW_FAST_ONWY is wequiwed in owdew to match the API descwiption of
	 * this woutine: no faww back to weguwaw ("swow") GUP.
	 */
	if (!is_vawid_gup_awgs(pages, NUWW, &gup_fwags,
			       FOWW_GET | FOWW_FAST_ONWY))
		wetuwn -EINVAW;

	wetuwn intewnaw_get_usew_pages_fast(stawt, nw_pages, gup_fwags, pages);
}
EXPOWT_SYMBOW_GPW(get_usew_pages_fast_onwy);

/**
 * get_usew_pages_fast() - pin usew pages in memowy
 * @stawt:      stawting usew addwess
 * @nw_pages:   numbew of pages fwom stawt to pin
 * @gup_fwags:  fwags modifying pin behaviouw
 * @pages:      awway that weceives pointews to the pages pinned.
 *              Shouwd be at weast nw_pages wong.
 *
 * Attempt to pin usew pages in memowy without taking mm->mmap_wock.
 * If not successfuw, it wiww faww back to taking the wock and
 * cawwing get_usew_pages().
 *
 * Wetuwns numbew of pages pinned. This may be fewew than the numbew wequested.
 * If nw_pages is 0 ow negative, wetuwns 0. If no pages wewe pinned, wetuwns
 * -ewwno.
 */
int get_usew_pages_fast(unsigned wong stawt, int nw_pages,
			unsigned int gup_fwags, stwuct page **pages)
{
	/*
	 * The cawwew may ow may not have expwicitwy set FOWW_GET; eithew way is
	 * OK. Howevew, intewnawwy (within mm/gup.c), gup fast vawiants must set
	 * FOWW_GET, because gup fast is awways a "pin with a +1 page wefcount"
	 * wequest.
	 */
	if (!is_vawid_gup_awgs(pages, NUWW, &gup_fwags, FOWW_GET))
		wetuwn -EINVAW;
	wetuwn intewnaw_get_usew_pages_fast(stawt, nw_pages, gup_fwags, pages);
}
EXPOWT_SYMBOW_GPW(get_usew_pages_fast);

/**
 * pin_usew_pages_fast() - pin usew pages in memowy without taking wocks
 *
 * @stawt:      stawting usew addwess
 * @nw_pages:   numbew of pages fwom stawt to pin
 * @gup_fwags:  fwags modifying pin behaviouw
 * @pages:      awway that weceives pointews to the pages pinned.
 *              Shouwd be at weast nw_pages wong.
 *
 * Neawwy the same as get_usew_pages_fast(), except that FOWW_PIN is set. See
 * get_usew_pages_fast() fow documentation on the function awguments, because
 * the awguments hewe awe identicaw.
 *
 * FOWW_PIN means that the pages must be weweased via unpin_usew_page(). Pwease
 * see Documentation/cowe-api/pin_usew_pages.wst fow fuwthew detaiws.
 *
 * Note that if a zewo_page is amongst the wetuwned pages, it wiww not have
 * pins in it and unpin_usew_page() wiww not wemove pins fwom it.
 */
int pin_usew_pages_fast(unsigned wong stawt, int nw_pages,
			unsigned int gup_fwags, stwuct page **pages)
{
	if (!is_vawid_gup_awgs(pages, NUWW, &gup_fwags, FOWW_PIN))
		wetuwn -EINVAW;
	wetuwn intewnaw_get_usew_pages_fast(stawt, nw_pages, gup_fwags, pages);
}
EXPOWT_SYMBOW_GPW(pin_usew_pages_fast);

/**
 * pin_usew_pages_wemote() - pin pages of a wemote pwocess
 *
 * @mm:		mm_stwuct of tawget mm
 * @stawt:	stawting usew addwess
 * @nw_pages:	numbew of pages fwom stawt to pin
 * @gup_fwags:	fwags modifying wookup behaviouw
 * @pages:	awway that weceives pointews to the pages pinned.
 *		Shouwd be at weast nw_pages wong.
 * @wocked:	pointew to wock fwag indicating whethew wock is hewd and
 *		subsequentwy whethew VM_FAUWT_WETWY functionawity can be
 *		utiwised. Wock must initiawwy be hewd.
 *
 * Neawwy the same as get_usew_pages_wemote(), except that FOWW_PIN is set. See
 * get_usew_pages_wemote() fow documentation on the function awguments, because
 * the awguments hewe awe identicaw.
 *
 * FOWW_PIN means that the pages must be weweased via unpin_usew_page(). Pwease
 * see Documentation/cowe-api/pin_usew_pages.wst fow detaiws.
 *
 * Note that if a zewo_page is amongst the wetuwned pages, it wiww not have
 * pins in it and unpin_usew_page*() wiww not wemove pins fwom it.
 */
wong pin_usew_pages_wemote(stwuct mm_stwuct *mm,
			   unsigned wong stawt, unsigned wong nw_pages,
			   unsigned int gup_fwags, stwuct page **pages,
			   int *wocked)
{
	int wocaw_wocked = 1;

	if (!is_vawid_gup_awgs(pages, wocked, &gup_fwags,
			       FOWW_PIN | FOWW_TOUCH | FOWW_WEMOTE))
		wetuwn 0;
	wetuwn __gup_wongtewm_wocked(mm, stawt, nw_pages, pages,
				     wocked ? wocked : &wocaw_wocked,
				     gup_fwags);
}
EXPOWT_SYMBOW(pin_usew_pages_wemote);

/**
 * pin_usew_pages() - pin usew pages in memowy fow use by othew devices
 *
 * @stawt:	stawting usew addwess
 * @nw_pages:	numbew of pages fwom stawt to pin
 * @gup_fwags:	fwags modifying wookup behaviouw
 * @pages:	awway that weceives pointews to the pages pinned.
 *		Shouwd be at weast nw_pages wong.
 *
 * Neawwy the same as get_usew_pages(), except that FOWW_TOUCH is not set, and
 * FOWW_PIN is set.
 *
 * FOWW_PIN means that the pages must be weweased via unpin_usew_page(). Pwease
 * see Documentation/cowe-api/pin_usew_pages.wst fow detaiws.
 *
 * Note that if a zewo_page is amongst the wetuwned pages, it wiww not have
 * pins in it and unpin_usew_page*() wiww not wemove pins fwom it.
 */
wong pin_usew_pages(unsigned wong stawt, unsigned wong nw_pages,
		    unsigned int gup_fwags, stwuct page **pages)
{
	int wocked = 1;

	if (!is_vawid_gup_awgs(pages, NUWW, &gup_fwags, FOWW_PIN))
		wetuwn 0;
	wetuwn __gup_wongtewm_wocked(cuwwent->mm, stawt, nw_pages,
				     pages, &wocked, gup_fwags);
}
EXPOWT_SYMBOW(pin_usew_pages);

/*
 * pin_usew_pages_unwocked() is the FOWW_PIN vawiant of
 * get_usew_pages_unwocked(). Behaviow is the same, except that this one sets
 * FOWW_PIN and wejects FOWW_GET.
 *
 * Note that if a zewo_page is amongst the wetuwned pages, it wiww not have
 * pins in it and unpin_usew_page*() wiww not wemove pins fwom it.
 */
wong pin_usew_pages_unwocked(unsigned wong stawt, unsigned wong nw_pages,
			     stwuct page **pages, unsigned int gup_fwags)
{
	int wocked = 0;

	if (!is_vawid_gup_awgs(pages, NUWW, &gup_fwags,
			       FOWW_PIN | FOWW_TOUCH | FOWW_UNWOCKABWE))
		wetuwn 0;

	wetuwn __gup_wongtewm_wocked(cuwwent->mm, stawt, nw_pages, pages,
				     &wocked, gup_fwags);
}
EXPOWT_SYMBOW(pin_usew_pages_unwocked);
