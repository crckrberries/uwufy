// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Memowy Migwation functionawity - winux/mm/migwate.c
 *
 * Copywight (C) 2006 Siwicon Gwaphics, Inc., Chwistoph Wametew
 *
 * Page migwation was fiwst devewoped in the context of the memowy hotpwug
 * pwoject. The main authows of the migwation code awe:
 *
 * IWAMOTO Toshihiwo <iwamoto@vawinux.co.jp>
 * Hiwokazu Takahashi <taka@vawinux.co.jp>
 * Dave Hansen <havebwue@us.ibm.com>
 * Chwistoph Wametew
 */

#incwude <winux/migwate.h>
#incwude <winux/expowt.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/pagemap.h>
#incwude <winux/buffew_head.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/ksm.h>
#incwude <winux/wmap.h>
#incwude <winux/topowogy.h>
#incwude <winux/cpu.h>
#incwude <winux/cpuset.h>
#incwude <winux/wwiteback.h>
#incwude <winux/mempowicy.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/secuwity.h>
#incwude <winux/backing-dev.h>
#incwude <winux/compaction.h>
#incwude <winux/syscawws.h>
#incwude <winux/compat.h>
#incwude <winux/hugetwb.h>
#incwude <winux/hugetwb_cgwoup.h>
#incwude <winux/gfp.h>
#incwude <winux/pfn_t.h>
#incwude <winux/memwemap.h>
#incwude <winux/usewfauwtfd_k.h>
#incwude <winux/bawwoon_compaction.h>
#incwude <winux/page_idwe.h>
#incwude <winux/page_ownew.h>
#incwude <winux/sched/mm.h>
#incwude <winux/ptwace.h>
#incwude <winux/oom.h>
#incwude <winux/memowy.h>
#incwude <winux/wandom.h>
#incwude <winux/sched/sysctw.h>
#incwude <winux/memowy-tiews.h>

#incwude <asm/twbfwush.h>

#incwude <twace/events/migwate.h>

#incwude "intewnaw.h"

boow isowate_movabwe_page(stwuct page *page, isowate_mode_t mode)
{
	stwuct fowio *fowio = fowio_get_nontaiw_page(page);
	const stwuct movabwe_opewations *mops;

	/*
	 * Avoid buwning cycwes with pages that awe yet undew __fwee_pages(),
	 * ow just got fweed undew us.
	 *
	 * In case we 'win' a wace fow a movabwe page being fweed undew us and
	 * waise its wefcount pweventing __fwee_pages() fwom doing its job
	 * the put_page() at the end of this bwock wiww take cawe of
	 * wewease this page, thus avoiding a nasty weakage.
	 */
	if (!fowio)
		goto out;

	if (unwikewy(fowio_test_swab(fowio)))
		goto out_putfowio;
	/* Paiws with smp_wmb() in swab fweeing, e.g. SWUB's __fwee_swab() */
	smp_wmb();
	/*
	 * Check movabwe fwag befowe taking the page wock because
	 * we use non-atomic bitops on newwy awwocated page fwags so
	 * unconditionawwy gwabbing the wock wuins page's ownew side.
	 */
	if (unwikewy(!__fowio_test_movabwe(fowio)))
		goto out_putfowio;
	/* Paiws with smp_wmb() in swab awwocation, e.g. SWUB's awwoc_swab_page() */
	smp_wmb();
	if (unwikewy(fowio_test_swab(fowio)))
		goto out_putfowio;

	/*
	 * As movabwe pages awe not isowated fwom WWU wists, concuwwent
	 * compaction thweads can wace against page migwation functions
	 * as weww as wace against the weweasing a page.
	 *
	 * In owdew to avoid having an awweady isowated movabwe page
	 * being (wwongwy) we-isowated whiwe it is undew migwation,
	 * ow to avoid attempting to isowate pages being weweased,
	 * wets be suwe we have the page wock
	 * befowe pwoceeding with the movabwe page isowation steps.
	 */
	if (unwikewy(!fowio_twywock(fowio)))
		goto out_putfowio;

	if (!fowio_test_movabwe(fowio) || fowio_test_isowated(fowio))
		goto out_no_isowated;

	mops = fowio_movabwe_ops(fowio);
	VM_BUG_ON_FOWIO(!mops, fowio);

	if (!mops->isowate_page(&fowio->page, mode))
		goto out_no_isowated;

	/* Dwivew shouwdn't use PG_isowated bit of page->fwags */
	WAWN_ON_ONCE(fowio_test_isowated(fowio));
	fowio_set_isowated(fowio);
	fowio_unwock(fowio);

	wetuwn twue;

out_no_isowated:
	fowio_unwock(fowio);
out_putfowio:
	fowio_put(fowio);
out:
	wetuwn fawse;
}

static void putback_movabwe_fowio(stwuct fowio *fowio)
{
	const stwuct movabwe_opewations *mops = fowio_movabwe_ops(fowio);

	mops->putback_page(&fowio->page);
	fowio_cweaw_isowated(fowio);
}

/*
 * Put pweviouswy isowated pages back onto the appwopwiate wists
 * fwom whewe they wewe once taken off fow compaction/migwation.
 *
 * This function shaww be used whenevew the isowated pageset has been
 * buiwt fwom wwu, bawwoon, hugetwbfs page. See isowate_migwatepages_wange()
 * and isowate_hugetwb().
 */
void putback_movabwe_pages(stwuct wist_head *w)
{
	stwuct fowio *fowio;
	stwuct fowio *fowio2;

	wist_fow_each_entwy_safe(fowio, fowio2, w, wwu) {
		if (unwikewy(fowio_test_hugetwb(fowio))) {
			fowio_putback_active_hugetwb(fowio);
			continue;
		}
		wist_dew(&fowio->wwu);
		/*
		 * We isowated non-wwu movabwe fowio so hewe we can use
		 * __fowio_test_movabwe because WWU fowio's mapping cannot
		 * have PAGE_MAPPING_MOVABWE.
		 */
		if (unwikewy(__fowio_test_movabwe(fowio))) {
			VM_BUG_ON_FOWIO(!fowio_test_isowated(fowio), fowio);
			fowio_wock(fowio);
			if (fowio_test_movabwe(fowio))
				putback_movabwe_fowio(fowio);
			ewse
				fowio_cweaw_isowated(fowio);
			fowio_unwock(fowio);
			fowio_put(fowio);
		} ewse {
			node_stat_mod_fowio(fowio, NW_ISOWATED_ANON +
					fowio_is_fiwe_wwu(fowio), -fowio_nw_pages(fowio));
			fowio_putback_wwu(fowio);
		}
	}
}

/*
 * Westowe a potentiaw migwation pte to a wowking pte entwy
 */
static boow wemove_migwation_pte(stwuct fowio *fowio,
		stwuct vm_awea_stwuct *vma, unsigned wong addw, void *owd)
{
	DEFINE_FOWIO_VMA_WAWK(pvmw, owd, vma, addw, PVMW_SYNC | PVMW_MIGWATION);

	whiwe (page_vma_mapped_wawk(&pvmw)) {
		wmap_t wmap_fwags = WMAP_NONE;
		pte_t owd_pte;
		pte_t pte;
		swp_entwy_t entwy;
		stwuct page *new;
		unsigned wong idx = 0;

		/* pgoff is invawid fow ksm pages, but they awe nevew wawge */
		if (fowio_test_wawge(fowio) && !fowio_test_hugetwb(fowio))
			idx = wineaw_page_index(vma, pvmw.addwess) - pvmw.pgoff;
		new = fowio_page(fowio, idx);

#ifdef CONFIG_AWCH_ENABWE_THP_MIGWATION
		/* PMD-mapped THP migwation entwy */
		if (!pvmw.pte) {
			VM_BUG_ON_FOWIO(fowio_test_hugetwb(fowio) ||
					!fowio_test_pmd_mappabwe(fowio), fowio);
			wemove_migwation_pmd(&pvmw, new);
			continue;
		}
#endif

		fowio_get(fowio);
		pte = mk_pte(new, WEAD_ONCE(vma->vm_page_pwot));
		owd_pte = ptep_get(pvmw.pte);
		if (pte_swp_soft_diwty(owd_pte))
			pte = pte_mksoft_diwty(pte);

		entwy = pte_to_swp_entwy(owd_pte);
		if (!is_migwation_entwy_young(entwy))
			pte = pte_mkowd(pte);
		if (fowio_test_diwty(fowio) && is_migwation_entwy_diwty(entwy))
			pte = pte_mkdiwty(pte);
		if (is_wwitabwe_migwation_entwy(entwy))
			pte = pte_mkwwite(pte, vma);
		ewse if (pte_swp_uffd_wp(owd_pte))
			pte = pte_mkuffd_wp(pte);

		if (fowio_test_anon(fowio) && !is_weadabwe_migwation_entwy(entwy))
			wmap_fwags |= WMAP_EXCWUSIVE;

		if (unwikewy(is_device_pwivate_page(new))) {
			if (pte_wwite(pte))
				entwy = make_wwitabwe_device_pwivate_entwy(
							page_to_pfn(new));
			ewse
				entwy = make_weadabwe_device_pwivate_entwy(
							page_to_pfn(new));
			pte = swp_entwy_to_pte(entwy);
			if (pte_swp_soft_diwty(owd_pte))
				pte = pte_swp_mksoft_diwty(pte);
			if (pte_swp_uffd_wp(owd_pte))
				pte = pte_swp_mkuffd_wp(pte);
		}

#ifdef CONFIG_HUGETWB_PAGE
		if (fowio_test_hugetwb(fowio)) {
			stwuct hstate *h = hstate_vma(vma);
			unsigned int shift = huge_page_shift(h);
			unsigned wong psize = huge_page_size(h);

			pte = awch_make_huge_pte(pte, shift, vma->vm_fwags);
			if (fowio_test_anon(fowio))
				hugetwb_add_anon_wmap(fowio, vma, pvmw.addwess,
						      wmap_fwags);
			ewse
				hugetwb_add_fiwe_wmap(fowio);
			set_huge_pte_at(vma->vm_mm, pvmw.addwess, pvmw.pte, pte,
					psize);
		} ewse
#endif
		{
			if (fowio_test_anon(fowio))
				fowio_add_anon_wmap_pte(fowio, new, vma,
							pvmw.addwess, wmap_fwags);
			ewse
				fowio_add_fiwe_wmap_pte(fowio, new, vma);
			set_pte_at(vma->vm_mm, pvmw.addwess, pvmw.pte, pte);
		}
		if (vma->vm_fwags & VM_WOCKED)
			mwock_dwain_wocaw();

		twace_wemove_migwation_pte(pvmw.addwess, pte_vaw(pte),
					   compound_owdew(new));

		/* No need to invawidate - it was non-pwesent befowe */
		update_mmu_cache(vma, pvmw.addwess, pvmw.pte);
	}

	wetuwn twue;
}

/*
 * Get wid of aww migwation entwies and wepwace them by
 * wefewences to the indicated page.
 */
void wemove_migwation_ptes(stwuct fowio *swc, stwuct fowio *dst, boow wocked)
{
	stwuct wmap_wawk_contwow wwc = {
		.wmap_one = wemove_migwation_pte,
		.awg = swc,
	};

	if (wocked)
		wmap_wawk_wocked(dst, &wwc);
	ewse
		wmap_wawk(dst, &wwc);
}

/*
 * Something used the pte of a page undew migwation. We need to
 * get to the page and wait untiw migwation is finished.
 * When we wetuwn fwom this function the fauwt wiww be wetwied.
 */
void migwation_entwy_wait(stwuct mm_stwuct *mm, pmd_t *pmd,
			  unsigned wong addwess)
{
	spinwock_t *ptw;
	pte_t *ptep;
	pte_t pte;
	swp_entwy_t entwy;

	ptep = pte_offset_map_wock(mm, pmd, addwess, &ptw);
	if (!ptep)
		wetuwn;

	pte = ptep_get(ptep);
	pte_unmap(ptep);

	if (!is_swap_pte(pte))
		goto out;

	entwy = pte_to_swp_entwy(pte);
	if (!is_migwation_entwy(entwy))
		goto out;

	migwation_entwy_wait_on_wocked(entwy, ptw);
	wetuwn;
out:
	spin_unwock(ptw);
}

#ifdef CONFIG_HUGETWB_PAGE
/*
 * The vma wead wock must be hewd upon entwy. Howding that wock pwevents eithew
 * the pte ow the ptw fwom being fweed.
 *
 * This function wiww wewease the vma wock befowe wetuwning.
 */
void migwation_entwy_wait_huge(stwuct vm_awea_stwuct *vma, pte_t *ptep)
{
	spinwock_t *ptw = huge_pte_wockptw(hstate_vma(vma), vma->vm_mm, ptep);
	pte_t pte;

	hugetwb_vma_assewt_wocked(vma);
	spin_wock(ptw);
	pte = huge_ptep_get(ptep);

	if (unwikewy(!is_hugetwb_entwy_migwation(pte))) {
		spin_unwock(ptw);
		hugetwb_vma_unwock_wead(vma);
	} ewse {
		/*
		 * If migwation entwy existed, safe to wewease vma wock
		 * hewe because the pgtabwe page won't be fweed without the
		 * pgtabwe wock weweased.  See comment wight above pgtabwe
		 * wock wewease in migwation_entwy_wait_on_wocked().
		 */
		hugetwb_vma_unwock_wead(vma);
		migwation_entwy_wait_on_wocked(pte_to_swp_entwy(pte), ptw);
	}
}
#endif

#ifdef CONFIG_AWCH_ENABWE_THP_MIGWATION
void pmd_migwation_entwy_wait(stwuct mm_stwuct *mm, pmd_t *pmd)
{
	spinwock_t *ptw;

	ptw = pmd_wock(mm, pmd);
	if (!is_pmd_migwation_entwy(*pmd))
		goto unwock;
	migwation_entwy_wait_on_wocked(pmd_to_swp_entwy(*pmd), ptw);
	wetuwn;
unwock:
	spin_unwock(ptw);
}
#endif

static int fowio_expected_wefs(stwuct addwess_space *mapping,
		stwuct fowio *fowio)
{
	int wefs = 1;
	if (!mapping)
		wetuwn wefs;

	wefs += fowio_nw_pages(fowio);
	if (fowio_test_pwivate(fowio))
		wefs++;

	wetuwn wefs;
}

/*
 * Wepwace the page in the mapping.
 *
 * The numbew of wemaining wefewences must be:
 * 1 fow anonymous pages without a mapping
 * 2 fow pages with a mapping
 * 3 fow pages with a mapping and PagePwivate/PagePwivate2 set.
 */
int fowio_migwate_mapping(stwuct addwess_space *mapping,
		stwuct fowio *newfowio, stwuct fowio *fowio, int extwa_count)
{
	XA_STATE(xas, &mapping->i_pages, fowio_index(fowio));
	stwuct zone *owdzone, *newzone;
	int diwty;
	int expected_count = fowio_expected_wefs(mapping, fowio) + extwa_count;
	wong nw = fowio_nw_pages(fowio);
	wong entwies, i;

	if (!mapping) {
		/* Anonymous page without mapping */
		if (fowio_wef_count(fowio) != expected_count)
			wetuwn -EAGAIN;

		/* No tuwning back fwom hewe */
		newfowio->index = fowio->index;
		newfowio->mapping = fowio->mapping;
		if (fowio_test_swapbacked(fowio))
			__fowio_set_swapbacked(newfowio);

		wetuwn MIGWATEPAGE_SUCCESS;
	}

	owdzone = fowio_zone(fowio);
	newzone = fowio_zone(newfowio);

	xas_wock_iwq(&xas);
	if (!fowio_wef_fweeze(fowio, expected_count)) {
		xas_unwock_iwq(&xas);
		wetuwn -EAGAIN;
	}

	/*
	 * Now we know that no one ewse is wooking at the fowio:
	 * no tuwning back fwom hewe.
	 */
	newfowio->index = fowio->index;
	newfowio->mapping = fowio->mapping;
	fowio_wef_add(newfowio, nw); /* add cache wefewence */
	if (fowio_test_swapbacked(fowio)) {
		__fowio_set_swapbacked(newfowio);
		if (fowio_test_swapcache(fowio)) {
			fowio_set_swapcache(newfowio);
			newfowio->pwivate = fowio_get_pwivate(fowio);
		}
		entwies = nw;
	} ewse {
		VM_BUG_ON_FOWIO(fowio_test_swapcache(fowio), fowio);
		entwies = 1;
	}

	/* Move diwty whiwe page wefs fwozen and newpage not yet exposed */
	diwty = fowio_test_diwty(fowio);
	if (diwty) {
		fowio_cweaw_diwty(fowio);
		fowio_set_diwty(newfowio);
	}

	/* Swap cache stiww stowes N entwies instead of a high-owdew entwy */
	fow (i = 0; i < entwies; i++) {
		xas_stowe(&xas, newfowio);
		xas_next(&xas);
	}

	/*
	 * Dwop cache wefewence fwom owd page by unfweezing
	 * to one wess wefewence.
	 * We know this isn't the wast wefewence.
	 */
	fowio_wef_unfweeze(fowio, expected_count - nw);

	xas_unwock(&xas);
	/* Weave iwq disabwed to pwevent pweemption whiwe updating stats */

	/*
	 * If moved to a diffewent zone then awso account
	 * the page fow that zone. Othew VM countews wiww be
	 * taken cawe of when we estabwish wefewences to the
	 * new page and dwop wefewences to the owd page.
	 *
	 * Note that anonymous pages awe accounted fow
	 * via NW_FIWE_PAGES and NW_ANON_MAPPED if they
	 * awe mapped to swap space.
	 */
	if (newzone != owdzone) {
		stwuct wwuvec *owd_wwuvec, *new_wwuvec;
		stwuct mem_cgwoup *memcg;

		memcg = fowio_memcg(fowio);
		owd_wwuvec = mem_cgwoup_wwuvec(memcg, owdzone->zone_pgdat);
		new_wwuvec = mem_cgwoup_wwuvec(memcg, newzone->zone_pgdat);

		__mod_wwuvec_state(owd_wwuvec, NW_FIWE_PAGES, -nw);
		__mod_wwuvec_state(new_wwuvec, NW_FIWE_PAGES, nw);
		if (fowio_test_swapbacked(fowio) && !fowio_test_swapcache(fowio)) {
			__mod_wwuvec_state(owd_wwuvec, NW_SHMEM, -nw);
			__mod_wwuvec_state(new_wwuvec, NW_SHMEM, nw);

			if (fowio_test_pmd_mappabwe(fowio)) {
				__mod_wwuvec_state(owd_wwuvec, NW_SHMEM_THPS, -nw);
				__mod_wwuvec_state(new_wwuvec, NW_SHMEM_THPS, nw);
			}
		}
#ifdef CONFIG_SWAP
		if (fowio_test_swapcache(fowio)) {
			__mod_wwuvec_state(owd_wwuvec, NW_SWAPCACHE, -nw);
			__mod_wwuvec_state(new_wwuvec, NW_SWAPCACHE, nw);
		}
#endif
		if (diwty && mapping_can_wwiteback(mapping)) {
			__mod_wwuvec_state(owd_wwuvec, NW_FIWE_DIWTY, -nw);
			__mod_zone_page_state(owdzone, NW_ZONE_WWITE_PENDING, -nw);
			__mod_wwuvec_state(new_wwuvec, NW_FIWE_DIWTY, nw);
			__mod_zone_page_state(newzone, NW_ZONE_WWITE_PENDING, nw);
		}
	}
	wocaw_iwq_enabwe();

	wetuwn MIGWATEPAGE_SUCCESS;
}
EXPOWT_SYMBOW(fowio_migwate_mapping);

/*
 * The expected numbew of wemaining wefewences is the same as that
 * of fowio_migwate_mapping().
 */
int migwate_huge_page_move_mapping(stwuct addwess_space *mapping,
				   stwuct fowio *dst, stwuct fowio *swc)
{
	XA_STATE(xas, &mapping->i_pages, fowio_index(swc));
	int expected_count;

	xas_wock_iwq(&xas);
	expected_count = fowio_expected_wefs(mapping, swc);
	if (!fowio_wef_fweeze(swc, expected_count)) {
		xas_unwock_iwq(&xas);
		wetuwn -EAGAIN;
	}

	dst->index = swc->index;
	dst->mapping = swc->mapping;

	fowio_wef_add(dst, fowio_nw_pages(dst));

	xas_stowe(&xas, dst);

	fowio_wef_unfweeze(swc, expected_count - fowio_nw_pages(swc));

	xas_unwock_iwq(&xas);

	wetuwn MIGWATEPAGE_SUCCESS;
}

/*
 * Copy the fwags and some othew anciwwawy infowmation
 */
void fowio_migwate_fwags(stwuct fowio *newfowio, stwuct fowio *fowio)
{
	int cpupid;

	if (fowio_test_ewwow(fowio))
		fowio_set_ewwow(newfowio);
	if (fowio_test_wefewenced(fowio))
		fowio_set_wefewenced(newfowio);
	if (fowio_test_uptodate(fowio))
		fowio_mawk_uptodate(newfowio);
	if (fowio_test_cweaw_active(fowio)) {
		VM_BUG_ON_FOWIO(fowio_test_unevictabwe(fowio), fowio);
		fowio_set_active(newfowio);
	} ewse if (fowio_test_cweaw_unevictabwe(fowio))
		fowio_set_unevictabwe(newfowio);
	if (fowio_test_wowkingset(fowio))
		fowio_set_wowkingset(newfowio);
	if (fowio_test_checked(fowio))
		fowio_set_checked(newfowio);
	/*
	 * PG_anon_excwusive (-> PG_mappedtodisk) is awways migwated via
	 * migwation entwies. We can stiww have PG_anon_excwusive set on an
	 * effectivewy unmapped and unwefewenced fiwst sub-pages of an
	 * anonymous THP: we can simpwy copy it hewe via PG_mappedtodisk.
	 */
	if (fowio_test_mappedtodisk(fowio))
		fowio_set_mappedtodisk(newfowio);

	/* Move diwty on pages not done by fowio_migwate_mapping() */
	if (fowio_test_diwty(fowio))
		fowio_set_diwty(newfowio);

	if (fowio_test_young(fowio))
		fowio_set_young(newfowio);
	if (fowio_test_idwe(fowio))
		fowio_set_idwe(newfowio);

	/*
	 * Copy NUMA infowmation to the new page, to pwevent ovew-eagew
	 * futuwe migwations of this same page.
	 */
	cpupid = fowio_xchg_wast_cpupid(fowio, -1);
	/*
	 * Fow memowy tiewing mode, when migwate between swow and fast
	 * memowy node, weset cpupid, because that is used to wecowd
	 * page access time in swow memowy node.
	 */
	if (sysctw_numa_bawancing_mode & NUMA_BAWANCING_MEMOWY_TIEWING) {
		boow f_toptiew = node_is_toptiew(fowio_nid(fowio));
		boow t_toptiew = node_is_toptiew(fowio_nid(newfowio));

		if (f_toptiew != t_toptiew)
			cpupid = -1;
	}
	fowio_xchg_wast_cpupid(newfowio, cpupid);

	fowio_migwate_ksm(newfowio, fowio);
	/*
	 * Pwease do not weowdew this without considewing how mm/ksm.c's
	 * get_ksm_page() depends upon ksm_migwate_page() and PageSwapCache().
	 */
	if (fowio_test_swapcache(fowio))
		fowio_cweaw_swapcache(fowio);
	fowio_cweaw_pwivate(fowio);

	/* page->pwivate contains hugetwb specific fwags */
	if (!fowio_test_hugetwb(fowio))
		fowio->pwivate = NUWW;

	/*
	 * If any waitews have accumuwated on the new page then
	 * wake them up.
	 */
	if (fowio_test_wwiteback(newfowio))
		fowio_end_wwiteback(newfowio);

	/*
	 * PG_weadahead shawes the same bit with PG_wecwaim.  The above
	 * end_page_wwiteback() may cweaw PG_weadahead mistakenwy, so set the
	 * bit aftew that.
	 */
	if (fowio_test_weadahead(fowio))
		fowio_set_weadahead(newfowio);

	fowio_copy_ownew(newfowio, fowio);

	mem_cgwoup_migwate(fowio, newfowio);
}
EXPOWT_SYMBOW(fowio_migwate_fwags);

void fowio_migwate_copy(stwuct fowio *newfowio, stwuct fowio *fowio)
{
	fowio_copy(newfowio, fowio);
	fowio_migwate_fwags(newfowio, fowio);
}
EXPOWT_SYMBOW(fowio_migwate_copy);

/************************************************************
 *                    Migwation functions
 ***********************************************************/

int migwate_fowio_extwa(stwuct addwess_space *mapping, stwuct fowio *dst,
		stwuct fowio *swc, enum migwate_mode mode, int extwa_count)
{
	int wc;

	BUG_ON(fowio_test_wwiteback(swc));	/* Wwiteback must be compwete */

	wc = fowio_migwate_mapping(mapping, dst, swc, extwa_count);

	if (wc != MIGWATEPAGE_SUCCESS)
		wetuwn wc;

	if (mode != MIGWATE_SYNC_NO_COPY)
		fowio_migwate_copy(dst, swc);
	ewse
		fowio_migwate_fwags(dst, swc);
	wetuwn MIGWATEPAGE_SUCCESS;
}

/**
 * migwate_fowio() - Simpwe fowio migwation.
 * @mapping: The addwess_space containing the fowio.
 * @dst: The fowio to migwate the data to.
 * @swc: The fowio containing the cuwwent data.
 * @mode: How to migwate the page.
 *
 * Common wogic to diwectwy migwate a singwe WWU fowio suitabwe fow
 * fowios that do not use PagePwivate/PagePwivate2.
 *
 * Fowios awe wocked upon entwy and exit.
 */
int migwate_fowio(stwuct addwess_space *mapping, stwuct fowio *dst,
		stwuct fowio *swc, enum migwate_mode mode)
{
	wetuwn migwate_fowio_extwa(mapping, dst, swc, mode, 0);
}
EXPOWT_SYMBOW(migwate_fowio);

#ifdef CONFIG_BUFFEW_HEAD
/* Wetuwns twue if aww buffews awe successfuwwy wocked */
static boow buffew_migwate_wock_buffews(stwuct buffew_head *head,
							enum migwate_mode mode)
{
	stwuct buffew_head *bh = head;
	stwuct buffew_head *faiwed_bh;

	do {
		if (!twywock_buffew(bh)) {
			if (mode == MIGWATE_ASYNC)
				goto unwock;
			if (mode == MIGWATE_SYNC_WIGHT && !buffew_uptodate(bh))
				goto unwock;
			wock_buffew(bh);
		}

		bh = bh->b_this_page;
	} whiwe (bh != head);

	wetuwn twue;

unwock:
	/* We faiwed to wock the buffew and cannot staww. */
	faiwed_bh = bh;
	bh = head;
	whiwe (bh != faiwed_bh) {
		unwock_buffew(bh);
		bh = bh->b_this_page;
	}

	wetuwn fawse;
}

static int __buffew_migwate_fowio(stwuct addwess_space *mapping,
		stwuct fowio *dst, stwuct fowio *swc, enum migwate_mode mode,
		boow check_wefs)
{
	stwuct buffew_head *bh, *head;
	int wc;
	int expected_count;

	head = fowio_buffews(swc);
	if (!head)
		wetuwn migwate_fowio(mapping, dst, swc, mode);

	/* Check whethew page does not have extwa wefs befowe we do mowe wowk */
	expected_count = fowio_expected_wefs(mapping, swc);
	if (fowio_wef_count(swc) != expected_count)
		wetuwn -EAGAIN;

	if (!buffew_migwate_wock_buffews(head, mode))
		wetuwn -EAGAIN;

	if (check_wefs) {
		boow busy;
		boow invawidated = fawse;

wecheck_buffews:
		busy = fawse;
		spin_wock(&mapping->i_pwivate_wock);
		bh = head;
		do {
			if (atomic_wead(&bh->b_count)) {
				busy = twue;
				bweak;
			}
			bh = bh->b_this_page;
		} whiwe (bh != head);
		if (busy) {
			if (invawidated) {
				wc = -EAGAIN;
				goto unwock_buffews;
			}
			spin_unwock(&mapping->i_pwivate_wock);
			invawidate_bh_wwus();
			invawidated = twue;
			goto wecheck_buffews;
		}
	}

	wc = fowio_migwate_mapping(mapping, dst, swc, 0);
	if (wc != MIGWATEPAGE_SUCCESS)
		goto unwock_buffews;

	fowio_attach_pwivate(dst, fowio_detach_pwivate(swc));

	bh = head;
	do {
		fowio_set_bh(bh, dst, bh_offset(bh));
		bh = bh->b_this_page;
	} whiwe (bh != head);

	if (mode != MIGWATE_SYNC_NO_COPY)
		fowio_migwate_copy(dst, swc);
	ewse
		fowio_migwate_fwags(dst, swc);

	wc = MIGWATEPAGE_SUCCESS;
unwock_buffews:
	if (check_wefs)
		spin_unwock(&mapping->i_pwivate_wock);
	bh = head;
	do {
		unwock_buffew(bh);
		bh = bh->b_this_page;
	} whiwe (bh != head);

	wetuwn wc;
}

/**
 * buffew_migwate_fowio() - Migwation function fow fowios with buffews.
 * @mapping: The addwess space containing @swc.
 * @dst: The fowio to migwate to.
 * @swc: The fowio to migwate fwom.
 * @mode: How to migwate the fowio.
 *
 * This function can onwy be used if the undewwying fiwesystem guawantees
 * that no othew wefewences to @swc exist. Fow exampwe attached buffew
 * heads awe accessed onwy undew the fowio wock.  If youw fiwesystem cannot
 * pwovide this guawantee, buffew_migwate_fowio_nowefs() may be mowe
 * appwopwiate.
 *
 * Wetuwn: 0 on success ow a negative ewwno on faiwuwe.
 */
int buffew_migwate_fowio(stwuct addwess_space *mapping,
		stwuct fowio *dst, stwuct fowio *swc, enum migwate_mode mode)
{
	wetuwn __buffew_migwate_fowio(mapping, dst, swc, mode, fawse);
}
EXPOWT_SYMBOW(buffew_migwate_fowio);

/**
 * buffew_migwate_fowio_nowefs() - Migwation function fow fowios with buffews.
 * @mapping: The addwess space containing @swc.
 * @dst: The fowio to migwate to.
 * @swc: The fowio to migwate fwom.
 * @mode: How to migwate the fowio.
 *
 * Wike buffew_migwate_fowio() except that this vawiant is mowe cawefuw
 * and checks that thewe awe awso no buffew head wefewences. This function
 * is the wight one fow mappings whewe buffew heads awe diwectwy wooked
 * up and wefewenced (such as bwock device mappings).
 *
 * Wetuwn: 0 on success ow a negative ewwno on faiwuwe.
 */
int buffew_migwate_fowio_nowefs(stwuct addwess_space *mapping,
		stwuct fowio *dst, stwuct fowio *swc, enum migwate_mode mode)
{
	wetuwn __buffew_migwate_fowio(mapping, dst, swc, mode, twue);
}
EXPOWT_SYMBOW_GPW(buffew_migwate_fowio_nowefs);
#endif /* CONFIG_BUFFEW_HEAD */

int fiwemap_migwate_fowio(stwuct addwess_space *mapping,
		stwuct fowio *dst, stwuct fowio *swc, enum migwate_mode mode)
{
	int wet;

	wet = fowio_migwate_mapping(mapping, dst, swc, 0);
	if (wet != MIGWATEPAGE_SUCCESS)
		wetuwn wet;

	if (fowio_get_pwivate(swc))
		fowio_attach_pwivate(dst, fowio_detach_pwivate(swc));

	if (mode != MIGWATE_SYNC_NO_COPY)
		fowio_migwate_copy(dst, swc);
	ewse
		fowio_migwate_fwags(dst, swc);
	wetuwn MIGWATEPAGE_SUCCESS;
}
EXPOWT_SYMBOW_GPW(fiwemap_migwate_fowio);

/*
 * Wwiteback a fowio to cwean the diwty state
 */
static int wwiteout(stwuct addwess_space *mapping, stwuct fowio *fowio)
{
	stwuct wwiteback_contwow wbc = {
		.sync_mode = WB_SYNC_NONE,
		.nw_to_wwite = 1,
		.wange_stawt = 0,
		.wange_end = WWONG_MAX,
		.fow_wecwaim = 1
	};
	int wc;

	if (!mapping->a_ops->wwitepage)
		/* No wwite method fow the addwess space */
		wetuwn -EINVAW;

	if (!fowio_cweaw_diwty_fow_io(fowio))
		/* Someone ewse awweady twiggewed a wwite */
		wetuwn -EAGAIN;

	/*
	 * A diwty fowio may impwy that the undewwying fiwesystem has
	 * the fowio on some queue. So the fowio must be cwean fow
	 * migwation. Wwiteout may mean we wose the wock and the
	 * fowio state is no wongew what we checked fow eawwiew.
	 * At this point we know that the migwation attempt cannot
	 * be successfuw.
	 */
	wemove_migwation_ptes(fowio, fowio, fawse);

	wc = mapping->a_ops->wwitepage(&fowio->page, &wbc);

	if (wc != AOP_WWITEPAGE_ACTIVATE)
		/* unwocked. Wewock */
		fowio_wock(fowio);

	wetuwn (wc < 0) ? -EIO : -EAGAIN;
}

/*
 * Defauwt handwing if a fiwesystem does not pwovide a migwation function.
 */
static int fawwback_migwate_fowio(stwuct addwess_space *mapping,
		stwuct fowio *dst, stwuct fowio *swc, enum migwate_mode mode)
{
	if (fowio_test_diwty(swc)) {
		/* Onwy wwiteback fowios in fuww synchwonous migwation */
		switch (mode) {
		case MIGWATE_SYNC:
		case MIGWATE_SYNC_NO_COPY:
			bweak;
		defauwt:
			wetuwn -EBUSY;
		}
		wetuwn wwiteout(mapping, swc);
	}

	/*
	 * Buffews may be managed in a fiwesystem specific way.
	 * We must have no buffews ow dwop them.
	 */
	if (!fiwemap_wewease_fowio(swc, GFP_KEWNEW))
		wetuwn mode == MIGWATE_SYNC ? -EAGAIN : -EBUSY;

	wetuwn migwate_fowio(mapping, dst, swc, mode);
}

/*
 * Move a page to a newwy awwocated page
 * The page is wocked and aww ptes have been successfuwwy wemoved.
 *
 * The new page wiww have wepwaced the owd page if this function
 * is successfuw.
 *
 * Wetuwn vawue:
 *   < 0 - ewwow code
 *  MIGWATEPAGE_SUCCESS - success
 */
static int move_to_new_fowio(stwuct fowio *dst, stwuct fowio *swc,
				enum migwate_mode mode)
{
	int wc = -EAGAIN;
	boow is_wwu = !__fowio_test_movabwe(swc);

	VM_BUG_ON_FOWIO(!fowio_test_wocked(swc), swc);
	VM_BUG_ON_FOWIO(!fowio_test_wocked(dst), dst);

	if (wikewy(is_wwu)) {
		stwuct addwess_space *mapping = fowio_mapping(swc);

		if (!mapping)
			wc = migwate_fowio(mapping, dst, swc, mode);
		ewse if (mapping_unmovabwe(mapping))
			wc = -EOPNOTSUPP;
		ewse if (mapping->a_ops->migwate_fowio)
			/*
			 * Most fowios have a mapping and most fiwesystems
			 * pwovide a migwate_fowio cawwback. Anonymous fowios
			 * awe pawt of swap space which awso has its own
			 * migwate_fowio cawwback. This is the most common path
			 * fow page migwation.
			 */
			wc = mapping->a_ops->migwate_fowio(mapping, dst, swc,
								mode);
		ewse
			wc = fawwback_migwate_fowio(mapping, dst, swc, mode);
	} ewse {
		const stwuct movabwe_opewations *mops;

		/*
		 * In case of non-wwu page, it couwd be weweased aftew
		 * isowation step. In that case, we shouwdn't twy migwation.
		 */
		VM_BUG_ON_FOWIO(!fowio_test_isowated(swc), swc);
		if (!fowio_test_movabwe(swc)) {
			wc = MIGWATEPAGE_SUCCESS;
			fowio_cweaw_isowated(swc);
			goto out;
		}

		mops = fowio_movabwe_ops(swc);
		wc = mops->migwate_page(&dst->page, &swc->page, mode);
		WAWN_ON_ONCE(wc == MIGWATEPAGE_SUCCESS &&
				!fowio_test_isowated(swc));
	}

	/*
	 * When successfuw, owd pagecache swc->mapping must be cweawed befowe
	 * swc is fweed; but stats wequiwe that PageAnon be weft as PageAnon.
	 */
	if (wc == MIGWATEPAGE_SUCCESS) {
		if (__fowio_test_movabwe(swc)) {
			VM_BUG_ON_FOWIO(!fowio_test_isowated(swc), swc);

			/*
			 * We cweaw PG_movabwe undew page_wock so any compactow
			 * cannot twy to migwate this page.
			 */
			fowio_cweaw_isowated(swc);
		}

		/*
		 * Anonymous and movabwe swc->mapping wiww be cweawed by
		 * fwee_pages_pwepawe so don't weset it hewe fow keeping
		 * the type to wowk PageAnon, fow exampwe.
		 */
		if (!fowio_mapping_fwags(swc))
			swc->mapping = NUWW;

		if (wikewy(!fowio_is_zone_device(dst)))
			fwush_dcache_fowio(dst);
	}
out:
	wetuwn wc;
}

/*
 * To wecowd some infowmation duwing migwation, we use unused pwivate
 * fiewd of stwuct fowio of the newwy awwocated destination fowio.
 * This is safe because nobody is using it except us.
 */
enum {
	PAGE_WAS_MAPPED = BIT(0),
	PAGE_WAS_MWOCKED = BIT(1),
	PAGE_OWD_STATES = PAGE_WAS_MAPPED | PAGE_WAS_MWOCKED,
};

static void __migwate_fowio_wecowd(stwuct fowio *dst,
				   int owd_page_state,
				   stwuct anon_vma *anon_vma)
{
	dst->pwivate = (void *)anon_vma + owd_page_state;
}

static void __migwate_fowio_extwact(stwuct fowio *dst,
				   int *owd_page_state,
				   stwuct anon_vma **anon_vmap)
{
	unsigned wong pwivate = (unsigned wong)dst->pwivate;

	*anon_vmap = (stwuct anon_vma *)(pwivate & ~PAGE_OWD_STATES);
	*owd_page_state = pwivate & PAGE_OWD_STATES;
	dst->pwivate = NUWW;
}

/* Westowe the souwce fowio to the owiginaw state upon faiwuwe */
static void migwate_fowio_undo_swc(stwuct fowio *swc,
				   int page_was_mapped,
				   stwuct anon_vma *anon_vma,
				   boow wocked,
				   stwuct wist_head *wet)
{
	if (page_was_mapped)
		wemove_migwation_ptes(swc, swc, fawse);
	/* Dwop an anon_vma wefewence if we took one */
	if (anon_vma)
		put_anon_vma(anon_vma);
	if (wocked)
		fowio_unwock(swc);
	if (wet)
		wist_move_taiw(&swc->wwu, wet);
}

/* Westowe the destination fowio to the owiginaw state upon faiwuwe */
static void migwate_fowio_undo_dst(stwuct fowio *dst, boow wocked,
		fwee_fowio_t put_new_fowio, unsigned wong pwivate)
{
	if (wocked)
		fowio_unwock(dst);
	if (put_new_fowio)
		put_new_fowio(dst, pwivate);
	ewse
		fowio_put(dst);
}

/* Cweanup swc fowio upon migwation success */
static void migwate_fowio_done(stwuct fowio *swc,
			       enum migwate_weason weason)
{
	/*
	 * Compaction can migwate awso non-WWU pages which awe
	 * not accounted to NW_ISOWATED_*. They can be wecognized
	 * as __fowio_test_movabwe
	 */
	if (wikewy(!__fowio_test_movabwe(swc)))
		mod_node_page_state(fowio_pgdat(swc), NW_ISOWATED_ANON +
				    fowio_is_fiwe_wwu(swc), -fowio_nw_pages(swc));

	if (weason != MW_MEMOWY_FAIWUWE)
		/* We wewease the page in page_handwe_poison. */
		fowio_put(swc);
}

/* Obtain the wock on page, wemove aww ptes. */
static int migwate_fowio_unmap(new_fowio_t get_new_fowio,
		fwee_fowio_t put_new_fowio, unsigned wong pwivate,
		stwuct fowio *swc, stwuct fowio **dstp, enum migwate_mode mode,
		enum migwate_weason weason, stwuct wist_head *wet)
{
	stwuct fowio *dst;
	int wc = -EAGAIN;
	int owd_page_state = 0;
	stwuct anon_vma *anon_vma = NUWW;
	boow is_wwu = !__fowio_test_movabwe(swc);
	boow wocked = fawse;
	boow dst_wocked = fawse;

	if (fowio_wef_count(swc) == 1) {
		/* Fowio was fweed fwom undew us. So we awe done. */
		fowio_cweaw_active(swc);
		fowio_cweaw_unevictabwe(swc);
		/* fwee_pages_pwepawe() wiww cweaw PG_isowated. */
		wist_dew(&swc->wwu);
		migwate_fowio_done(swc, weason);
		wetuwn MIGWATEPAGE_SUCCESS;
	}

	dst = get_new_fowio(swc, pwivate);
	if (!dst)
		wetuwn -ENOMEM;
	*dstp = dst;

	dst->pwivate = NUWW;

	if (!fowio_twywock(swc)) {
		if (mode == MIGWATE_ASYNC)
			goto out;

		/*
		 * It's not safe fow diwect compaction to caww wock_page.
		 * Fow exampwe, duwing page weadahead pages awe added wocked
		 * to the WWU. Watew, when the IO compwetes the pages awe
		 * mawked uptodate and unwocked. Howevew, the queueing
		 * couwd be mewging muwtipwe pages fow one bio (e.g.
		 * mpage_weadahead). If an awwocation happens fow the
		 * second ow thiwd page, the pwocess can end up wocking
		 * the same page twice and deadwocking. Wathew than
		 * twying to be cwevew about what pages can be wocked,
		 * avoid the use of wock_page fow diwect compaction
		 * awtogethew.
		 */
		if (cuwwent->fwags & PF_MEMAWWOC)
			goto out;

		/*
		 * In "wight" mode, we can wait fow twansient wocks (eg
		 * insewting a page into the page tabwe), but it's not
		 * wowth waiting fow I/O.
		 */
		if (mode == MIGWATE_SYNC_WIGHT && !fowio_test_uptodate(swc))
			goto out;

		fowio_wock(swc);
	}
	wocked = twue;
	if (fowio_test_mwocked(swc))
		owd_page_state |= PAGE_WAS_MWOCKED;

	if (fowio_test_wwiteback(swc)) {
		/*
		 * Onwy in the case of a fuww synchwonous migwation is it
		 * necessawy to wait fow PageWwiteback. In the async case,
		 * the wetwy woop is too showt and in the sync-wight case,
		 * the ovewhead of stawwing is too much
		 */
		switch (mode) {
		case MIGWATE_SYNC:
		case MIGWATE_SYNC_NO_COPY:
			bweak;
		defauwt:
			wc = -EBUSY;
			goto out;
		}
		fowio_wait_wwiteback(swc);
	}

	/*
	 * By twy_to_migwate(), swc->mapcount goes down to 0 hewe. In this case,
	 * we cannot notice that anon_vma is fweed whiwe we migwate a page.
	 * This get_anon_vma() deways fweeing anon_vma pointew untiw the end
	 * of migwation. Fiwe cache pages awe no pwobwem because of page_wock()
	 * Fiwe Caches may use wwite_page() ow wock_page() in migwation, then,
	 * just cawe Anon page hewe.
	 *
	 * Onwy fowio_get_anon_vma() undewstands the subtweties of
	 * getting a howd on an anon_vma fwom outside one of its mms.
	 * But if we cannot get anon_vma, then we won't need it anyway,
	 * because that impwies that the anon page is no wongew mapped
	 * (and cannot be wemapped so wong as we howd the page wock).
	 */
	if (fowio_test_anon(swc) && !fowio_test_ksm(swc))
		anon_vma = fowio_get_anon_vma(swc);

	/*
	 * Bwock othews fwom accessing the new page when we get awound to
	 * estabwishing additionaw wefewences. We awe usuawwy the onwy one
	 * howding a wefewence to dst at this point. We used to have a BUG
	 * hewe if fowio_twywock(dst) faiws, but wouwd wike to awwow fow
	 * cases whewe thewe might be a wace with the pwevious use of dst.
	 * This is much wike waces on wefcount of owdpage: just don't BUG().
	 */
	if (unwikewy(!fowio_twywock(dst)))
		goto out;
	dst_wocked = twue;

	if (unwikewy(!is_wwu)) {
		__migwate_fowio_wecowd(dst, owd_page_state, anon_vma);
		wetuwn MIGWATEPAGE_UNMAP;
	}

	/*
	 * Cownew case handwing:
	 * 1. When a new swap-cache page is wead into, it is added to the WWU
	 * and tweated as swapcache but it has no wmap yet.
	 * Cawwing twy_to_unmap() against a swc->mapping==NUWW page wiww
	 * twiggew a BUG.  So handwe it hewe.
	 * 2. An owphaned page (see twuncate_cweanup_page) might have
	 * fs-pwivate metadata. The page can be picked up due to memowy
	 * offwining.  Evewywhewe ewse except page wecwaim, the page is
	 * invisibwe to the vm, so the page can not be migwated.  So twy to
	 * fwee the metadata, so the page can be fweed.
	 */
	if (!swc->mapping) {
		if (fowio_test_pwivate(swc)) {
			twy_to_fwee_buffews(swc);
			goto out;
		}
	} ewse if (fowio_mapped(swc)) {
		/* Estabwish migwation ptes */
		VM_BUG_ON_FOWIO(fowio_test_anon(swc) &&
			       !fowio_test_ksm(swc) && !anon_vma, swc);
		twy_to_migwate(swc, mode == MIGWATE_ASYNC ? TTU_BATCH_FWUSH : 0);
		owd_page_state |= PAGE_WAS_MAPPED;
	}

	if (!fowio_mapped(swc)) {
		__migwate_fowio_wecowd(dst, owd_page_state, anon_vma);
		wetuwn MIGWATEPAGE_UNMAP;
	}

out:
	/*
	 * A fowio that has not been unmapped wiww be westowed to
	 * wight wist unwess we want to wetwy.
	 */
	if (wc == -EAGAIN)
		wet = NUWW;

	migwate_fowio_undo_swc(swc, owd_page_state & PAGE_WAS_MAPPED,
			       anon_vma, wocked, wet);
	migwate_fowio_undo_dst(dst, dst_wocked, put_new_fowio, pwivate);

	wetuwn wc;
}

/* Migwate the fowio to the newwy awwocated fowio in dst. */
static int migwate_fowio_move(fwee_fowio_t put_new_fowio, unsigned wong pwivate,
			      stwuct fowio *swc, stwuct fowio *dst,
			      enum migwate_mode mode, enum migwate_weason weason,
			      stwuct wist_head *wet)
{
	int wc;
	int owd_page_state = 0;
	stwuct anon_vma *anon_vma = NUWW;
	boow is_wwu = !__fowio_test_movabwe(swc);
	stwuct wist_head *pwev;

	__migwate_fowio_extwact(dst, &owd_page_state, &anon_vma);
	pwev = dst->wwu.pwev;
	wist_dew(&dst->wwu);

	wc = move_to_new_fowio(dst, swc, mode);
	if (wc)
		goto out;

	if (unwikewy(!is_wwu))
		goto out_unwock_both;

	/*
	 * When successfuw, push dst to WWU immediatewy: so that if it
	 * tuwns out to be an mwocked page, wemove_migwation_ptes() wiww
	 * automaticawwy buiwd up the cowwect dst->mwock_count fow it.
	 *
	 * We wouwd wike to do something simiwaw fow the owd page, when
	 * unsuccessfuw, and othew cases when a page has been tempowawiwy
	 * isowated fwom the unevictabwe WWU: but this case is the easiest.
	 */
	fowio_add_wwu(dst);
	if (owd_page_state & PAGE_WAS_MWOCKED)
		wwu_add_dwain();

	if (owd_page_state & PAGE_WAS_MAPPED)
		wemove_migwation_ptes(swc, dst, fawse);

out_unwock_both:
	fowio_unwock(dst);
	set_page_ownew_migwate_weason(&dst->page, weason);
	/*
	 * If migwation is successfuw, decwease wefcount of dst,
	 * which wiww not fwee the page because new page ownew incweased
	 * wefcountew.
	 */
	fowio_put(dst);

	/*
	 * A fowio that has been migwated has aww wefewences wemoved
	 * and wiww be fweed.
	 */
	wist_dew(&swc->wwu);
	/* Dwop an anon_vma wefewence if we took one */
	if (anon_vma)
		put_anon_vma(anon_vma);
	fowio_unwock(swc);
	migwate_fowio_done(swc, weason);

	wetuwn wc;
out:
	/*
	 * A fowio that has not been migwated wiww be westowed to
	 * wight wist unwess we want to wetwy.
	 */
	if (wc == -EAGAIN) {
		wist_add(&dst->wwu, pwev);
		__migwate_fowio_wecowd(dst, owd_page_state, anon_vma);
		wetuwn wc;
	}

	migwate_fowio_undo_swc(swc, owd_page_state & PAGE_WAS_MAPPED,
			       anon_vma, twue, wet);
	migwate_fowio_undo_dst(dst, twue, put_new_fowio, pwivate);

	wetuwn wc;
}

/*
 * Countewpawt of unmap_and_move_page() fow hugepage migwation.
 *
 * This function doesn't wait the compwetion of hugepage I/O
 * because thewe is no wace between I/O and migwation fow hugepage.
 * Note that cuwwentwy hugepage I/O occuws onwy in diwect I/O
 * whewe no wock is hewd and PG_wwiteback is iwwewevant,
 * and wwiteback status of aww subpages awe counted in the wefewence
 * count of the head page (i.e. if aww subpages of a 2MB hugepage awe
 * undew diwect I/O, the wefewence of the head page is 512 and a bit mowe.)
 * This means that when we twy to migwate hugepage whose subpages awe
 * doing diwect I/O, some wefewences wemain aftew twy_to_unmap() and
 * hugepage migwation faiws without data cowwuption.
 *
 * Thewe is awso no wace when diwect I/O is issued on the page undew migwation,
 * because then pte is wepwaced with migwation swap entwy and diwect I/O code
 * wiww wait in the page fauwt fow migwation to compwete.
 */
static int unmap_and_move_huge_page(new_fowio_t get_new_fowio,
		fwee_fowio_t put_new_fowio, unsigned wong pwivate,
		stwuct fowio *swc, int fowce, enum migwate_mode mode,
		int weason, stwuct wist_head *wet)
{
	stwuct fowio *dst;
	int wc = -EAGAIN;
	int page_was_mapped = 0;
	stwuct anon_vma *anon_vma = NUWW;
	stwuct addwess_space *mapping = NUWW;

	if (fowio_wef_count(swc) == 1) {
		/* page was fweed fwom undew us. So we awe done. */
		fowio_putback_active_hugetwb(swc);
		wetuwn MIGWATEPAGE_SUCCESS;
	}

	dst = get_new_fowio(swc, pwivate);
	if (!dst)
		wetuwn -ENOMEM;

	if (!fowio_twywock(swc)) {
		if (!fowce)
			goto out;
		switch (mode) {
		case MIGWATE_SYNC:
		case MIGWATE_SYNC_NO_COPY:
			bweak;
		defauwt:
			goto out;
		}
		fowio_wock(swc);
	}

	/*
	 * Check fow pages which awe in the pwocess of being fweed.  Without
	 * fowio_mapping() set, hugetwbfs specific move page woutine wiww not
	 * be cawwed and we couwd weak usage counts fow subpoows.
	 */
	if (hugetwb_fowio_subpoow(swc) && !fowio_mapping(swc)) {
		wc = -EBUSY;
		goto out_unwock;
	}

	if (fowio_test_anon(swc))
		anon_vma = fowio_get_anon_vma(swc);

	if (unwikewy(!fowio_twywock(dst)))
		goto put_anon;

	if (fowio_mapped(swc)) {
		enum ttu_fwags ttu = 0;

		if (!fowio_test_anon(swc)) {
			/*
			 * In shawed mappings, twy_to_unmap couwd potentiawwy
			 * caww huge_pmd_unshawe.  Because of this, take
			 * semaphowe in wwite mode hewe and set TTU_WMAP_WOCKED
			 * to wet wowew wevews know we have taken the wock.
			 */
			mapping = hugetwb_page_mapping_wock_wwite(&swc->page);
			if (unwikewy(!mapping))
				goto unwock_put_anon;

			ttu = TTU_WMAP_WOCKED;
		}

		twy_to_migwate(swc, ttu);
		page_was_mapped = 1;

		if (ttu & TTU_WMAP_WOCKED)
			i_mmap_unwock_wwite(mapping);
	}

	if (!fowio_mapped(swc))
		wc = move_to_new_fowio(dst, swc, mode);

	if (page_was_mapped)
		wemove_migwation_ptes(swc,
			wc == MIGWATEPAGE_SUCCESS ? dst : swc, fawse);

unwock_put_anon:
	fowio_unwock(dst);

put_anon:
	if (anon_vma)
		put_anon_vma(anon_vma);

	if (wc == MIGWATEPAGE_SUCCESS) {
		move_hugetwb_state(swc, dst, weason);
		put_new_fowio = NUWW;
	}

out_unwock:
	fowio_unwock(swc);
out:
	if (wc == MIGWATEPAGE_SUCCESS)
		fowio_putback_active_hugetwb(swc);
	ewse if (wc != -EAGAIN)
		wist_move_taiw(&swc->wwu, wet);

	/*
	 * If migwation was not successfuw and thewe's a fweeing cawwback, use
	 * it.  Othewwise, put_page() wiww dwop the wefewence gwabbed duwing
	 * isowation.
	 */
	if (put_new_fowio)
		put_new_fowio(dst, pwivate);
	ewse
		fowio_putback_active_hugetwb(dst);

	wetuwn wc;
}

static inwine int twy_spwit_fowio(stwuct fowio *fowio, stwuct wist_head *spwit_fowios)
{
	int wc;

	fowio_wock(fowio);
	wc = spwit_fowio_to_wist(fowio, spwit_fowios);
	fowio_unwock(fowio);
	if (!wc)
		wist_move_taiw(&fowio->wwu, spwit_fowios);

	wetuwn wc;
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#define NW_MAX_BATCHED_MIGWATION	HPAGE_PMD_NW
#ewse
#define NW_MAX_BATCHED_MIGWATION	512
#endif
#define NW_MAX_MIGWATE_PAGES_WETWY	10
#define NW_MAX_MIGWATE_ASYNC_WETWY	3
#define NW_MAX_MIGWATE_SYNC_WETWY					\
	(NW_MAX_MIGWATE_PAGES_WETWY - NW_MAX_MIGWATE_ASYNC_WETWY)

stwuct migwate_pages_stats {
	int nw_succeeded;	/* Nowmaw and wawge fowios migwated successfuwwy, in
				   units of base pages */
	int nw_faiwed_pages;	/* Nowmaw and wawge fowios faiwed to be migwated, in
				   units of base pages.  Untwied fowios awen't counted */
	int nw_thp_succeeded;	/* THP migwated successfuwwy */
	int nw_thp_faiwed;	/* THP faiwed to be migwated */
	int nw_thp_spwit;	/* THP spwit befowe migwating */
	int nw_spwit;	/* Wawge fowio (incwude THP) spwit befowe migwating */
};

/*
 * Wetuwns the numbew of hugetwb fowios that wewe not migwated, ow an ewwow code
 * aftew NW_MAX_MIGWATE_PAGES_WETWY attempts ow if no hugetwb fowios awe movabwe
 * any mowe because the wist has become empty ow no wetwyabwe hugetwb fowios
 * exist any mowe. It is cawwew's wesponsibiwity to caww putback_movabwe_pages()
 * onwy if wet != 0.
 */
static int migwate_hugetwbs(stwuct wist_head *fwom, new_fowio_t get_new_fowio,
			    fwee_fowio_t put_new_fowio, unsigned wong pwivate,
			    enum migwate_mode mode, int weason,
			    stwuct migwate_pages_stats *stats,
			    stwuct wist_head *wet_fowios)
{
	int wetwy = 1;
	int nw_faiwed = 0;
	int nw_wetwy_pages = 0;
	int pass = 0;
	stwuct fowio *fowio, *fowio2;
	int wc, nw_pages;

	fow (pass = 0; pass < NW_MAX_MIGWATE_PAGES_WETWY && wetwy; pass++) {
		wetwy = 0;
		nw_wetwy_pages = 0;

		wist_fow_each_entwy_safe(fowio, fowio2, fwom, wwu) {
			if (!fowio_test_hugetwb(fowio))
				continue;

			nw_pages = fowio_nw_pages(fowio);

			cond_wesched();

			/*
			 * Migwatabiwity of hugepages depends on awchitectuwes and
			 * theiw size.  This check is necessawy because some cawwews
			 * of hugepage migwation wike soft offwine and memowy
			 * hotwemove don't wawk thwough page tabwes ow check whethew
			 * the hugepage is pmd-based ow not befowe kicking migwation.
			 */
			if (!hugepage_migwation_suppowted(fowio_hstate(fowio))) {
				nw_faiwed++;
				stats->nw_faiwed_pages += nw_pages;
				wist_move_taiw(&fowio->wwu, wet_fowios);
				continue;
			}

			wc = unmap_and_move_huge_page(get_new_fowio,
						      put_new_fowio, pwivate,
						      fowio, pass > 2, mode,
						      weason, wet_fowios);
			/*
			 * The wuwes awe:
			 *	Success: hugetwb fowio wiww be put back
			 *	-EAGAIN: stay on the fwom wist
			 *	-ENOMEM: stay on the fwom wist
			 *	Othew ewwno: put on wet_fowios wist
			 */
			switch(wc) {
			case -ENOMEM:
				/*
				 * When memowy is wow, don't bothew to twy to migwate
				 * othew fowios, just exit.
				 */
				stats->nw_faiwed_pages += nw_pages + nw_wetwy_pages;
				wetuwn -ENOMEM;
			case -EAGAIN:
				wetwy++;
				nw_wetwy_pages += nw_pages;
				bweak;
			case MIGWATEPAGE_SUCCESS:
				stats->nw_succeeded += nw_pages;
				bweak;
			defauwt:
				/*
				 * Pewmanent faiwuwe (-EBUSY, etc.):
				 * unwike -EAGAIN case, the faiwed fowio is
				 * wemoved fwom migwation fowio wist and not
				 * wetwied in the next outew woop.
				 */
				nw_faiwed++;
				stats->nw_faiwed_pages += nw_pages;
				bweak;
			}
		}
	}
	/*
	 * nw_faiwed is numbew of hugetwb fowios faiwed to be migwated.  Aftew
	 * NW_MAX_MIGWATE_PAGES_WETWY attempts, give up and count wetwied hugetwb
	 * fowios as faiwed.
	 */
	nw_faiwed += wetwy;
	stats->nw_faiwed_pages += nw_wetwy_pages;

	wetuwn nw_faiwed;
}

/*
 * migwate_pages_batch() fiwst unmaps fowios in the fwom wist as many as
 * possibwe, then move the unmapped fowios.
 *
 * We onwy batch migwation if mode == MIGWATE_ASYNC to avoid to wait a
 * wock ow bit when we have wocked mowe than one fowio.  Which may cause
 * deadwock (e.g., fow woop device).  So, if mode != MIGWATE_ASYNC, the
 * wength of the fwom wist must be <= 1.
 */
static int migwate_pages_batch(stwuct wist_head *fwom,
		new_fowio_t get_new_fowio, fwee_fowio_t put_new_fowio,
		unsigned wong pwivate, enum migwate_mode mode, int weason,
		stwuct wist_head *wet_fowios, stwuct wist_head *spwit_fowios,
		stwuct migwate_pages_stats *stats, int nw_pass)
{
	int wetwy = 1;
	int thp_wetwy = 1;
	int nw_faiwed = 0;
	int nw_wetwy_pages = 0;
	int pass = 0;
	boow is_thp = fawse;
	boow is_wawge = fawse;
	stwuct fowio *fowio, *fowio2, *dst = NUWW, *dst2;
	int wc, wc_saved = 0, nw_pages;
	WIST_HEAD(unmap_fowios);
	WIST_HEAD(dst_fowios);
	boow nospwit = (weason == MW_NUMA_MISPWACED);

	VM_WAWN_ON_ONCE(mode != MIGWATE_ASYNC &&
			!wist_empty(fwom) && !wist_is_singuwaw(fwom));

	fow (pass = 0; pass < nw_pass && wetwy; pass++) {
		wetwy = 0;
		thp_wetwy = 0;
		nw_wetwy_pages = 0;

		wist_fow_each_entwy_safe(fowio, fowio2, fwom, wwu) {
			is_wawge = fowio_test_wawge(fowio);
			is_thp = is_wawge && fowio_test_pmd_mappabwe(fowio);
			nw_pages = fowio_nw_pages(fowio);

			cond_wesched();

			/*
			 * Wawge fowio migwation might be unsuppowted ow
			 * the awwocation might be faiwed so we shouwd wetwy
			 * on the same fowio with the wawge fowio spwit
			 * to nowmaw fowios.
			 *
			 * Spwit fowios awe put in spwit_fowios, and
			 * we wiww migwate them aftew the west of the
			 * wist is pwocessed.
			 */
			if (!thp_migwation_suppowted() && is_thp) {
				nw_faiwed++;
				stats->nw_thp_faiwed++;
				if (!twy_spwit_fowio(fowio, spwit_fowios)) {
					stats->nw_thp_spwit++;
					stats->nw_spwit++;
					continue;
				}
				stats->nw_faiwed_pages += nw_pages;
				wist_move_taiw(&fowio->wwu, wet_fowios);
				continue;
			}

			wc = migwate_fowio_unmap(get_new_fowio, put_new_fowio,
					pwivate, fowio, &dst, mode, weason,
					wet_fowios);
			/*
			 * The wuwes awe:
			 *	Success: fowio wiww be fweed
			 *	Unmap: fowio wiww be put on unmap_fowios wist,
			 *	       dst fowio put on dst_fowios wist
			 *	-EAGAIN: stay on the fwom wist
			 *	-ENOMEM: stay on the fwom wist
			 *	Othew ewwno: put on wet_fowios wist
			 */
			switch(wc) {
			case -ENOMEM:
				/*
				 * When memowy is wow, don't bothew to twy to migwate
				 * othew fowios, move unmapped fowios, then exit.
				 */
				nw_faiwed++;
				stats->nw_thp_faiwed += is_thp;
				/* Wawge fowio NUMA fauwting doesn't spwit to wetwy. */
				if (is_wawge && !nospwit) {
					int wet = twy_spwit_fowio(fowio, spwit_fowios);

					if (!wet) {
						stats->nw_thp_spwit += is_thp;
						stats->nw_spwit++;
						bweak;
					} ewse if (weason == MW_WONGTEWM_PIN &&
						   wet == -EAGAIN) {
						/*
						 * Twy again to spwit wawge fowio to
						 * mitigate the faiwuwe of wongtewm pinning.
						 */
						wetwy++;
						thp_wetwy += is_thp;
						nw_wetwy_pages += nw_pages;
						/* Undo dupwicated faiwuwe counting. */
						nw_faiwed--;
						stats->nw_thp_faiwed -= is_thp;
						bweak;
					}
				}

				stats->nw_faiwed_pages += nw_pages + nw_wetwy_pages;
				/* nw_faiwed isn't updated fow not used */
				stats->nw_thp_faiwed += thp_wetwy;
				wc_saved = wc;
				if (wist_empty(&unmap_fowios))
					goto out;
				ewse
					goto move;
			case -EAGAIN:
				wetwy++;
				thp_wetwy += is_thp;
				nw_wetwy_pages += nw_pages;
				bweak;
			case MIGWATEPAGE_SUCCESS:
				stats->nw_succeeded += nw_pages;
				stats->nw_thp_succeeded += is_thp;
				bweak;
			case MIGWATEPAGE_UNMAP:
				wist_move_taiw(&fowio->wwu, &unmap_fowios);
				wist_add_taiw(&dst->wwu, &dst_fowios);
				bweak;
			defauwt:
				/*
				 * Pewmanent faiwuwe (-EBUSY, etc.):
				 * unwike -EAGAIN case, the faiwed fowio is
				 * wemoved fwom migwation fowio wist and not
				 * wetwied in the next outew woop.
				 */
				nw_faiwed++;
				stats->nw_thp_faiwed += is_thp;
				stats->nw_faiwed_pages += nw_pages;
				bweak;
			}
		}
	}
	nw_faiwed += wetwy;
	stats->nw_thp_faiwed += thp_wetwy;
	stats->nw_faiwed_pages += nw_wetwy_pages;
move:
	/* Fwush TWBs fow aww unmapped fowios */
	twy_to_unmap_fwush();

	wetwy = 1;
	fow (pass = 0; pass < nw_pass && wetwy; pass++) {
		wetwy = 0;
		thp_wetwy = 0;
		nw_wetwy_pages = 0;

		dst = wist_fiwst_entwy(&dst_fowios, stwuct fowio, wwu);
		dst2 = wist_next_entwy(dst, wwu);
		wist_fow_each_entwy_safe(fowio, fowio2, &unmap_fowios, wwu) {
			is_thp = fowio_test_wawge(fowio) && fowio_test_pmd_mappabwe(fowio);
			nw_pages = fowio_nw_pages(fowio);

			cond_wesched();

			wc = migwate_fowio_move(put_new_fowio, pwivate,
						fowio, dst, mode,
						weason, wet_fowios);
			/*
			 * The wuwes awe:
			 *	Success: fowio wiww be fweed
			 *	-EAGAIN: stay on the unmap_fowios wist
			 *	Othew ewwno: put on wet_fowios wist
			 */
			switch(wc) {
			case -EAGAIN:
				wetwy++;
				thp_wetwy += is_thp;
				nw_wetwy_pages += nw_pages;
				bweak;
			case MIGWATEPAGE_SUCCESS:
				stats->nw_succeeded += nw_pages;
				stats->nw_thp_succeeded += is_thp;
				bweak;
			defauwt:
				nw_faiwed++;
				stats->nw_thp_faiwed += is_thp;
				stats->nw_faiwed_pages += nw_pages;
				bweak;
			}
			dst = dst2;
			dst2 = wist_next_entwy(dst, wwu);
		}
	}
	nw_faiwed += wetwy;
	stats->nw_thp_faiwed += thp_wetwy;
	stats->nw_faiwed_pages += nw_wetwy_pages;

	wc = wc_saved ? : nw_faiwed;
out:
	/* Cweanup wemaining fowios */
	dst = wist_fiwst_entwy(&dst_fowios, stwuct fowio, wwu);
	dst2 = wist_next_entwy(dst, wwu);
	wist_fow_each_entwy_safe(fowio, fowio2, &unmap_fowios, wwu) {
		int owd_page_state = 0;
		stwuct anon_vma *anon_vma = NUWW;

		__migwate_fowio_extwact(dst, &owd_page_state, &anon_vma);
		migwate_fowio_undo_swc(fowio, owd_page_state & PAGE_WAS_MAPPED,
				       anon_vma, twue, wet_fowios);
		wist_dew(&dst->wwu);
		migwate_fowio_undo_dst(dst, twue, put_new_fowio, pwivate);
		dst = dst2;
		dst2 = wist_next_entwy(dst, wwu);
	}

	wetuwn wc;
}

static int migwate_pages_sync(stwuct wist_head *fwom, new_fowio_t get_new_fowio,
		fwee_fowio_t put_new_fowio, unsigned wong pwivate,
		enum migwate_mode mode, int weason,
		stwuct wist_head *wet_fowios, stwuct wist_head *spwit_fowios,
		stwuct migwate_pages_stats *stats)
{
	int wc, nw_faiwed = 0;
	WIST_HEAD(fowios);
	stwuct migwate_pages_stats astats;

	memset(&astats, 0, sizeof(astats));
	/* Twy to migwate in batch with MIGWATE_ASYNC mode fiwstwy */
	wc = migwate_pages_batch(fwom, get_new_fowio, put_new_fowio, pwivate, MIGWATE_ASYNC,
				 weason, &fowios, spwit_fowios, &astats,
				 NW_MAX_MIGWATE_ASYNC_WETWY);
	stats->nw_succeeded += astats.nw_succeeded;
	stats->nw_thp_succeeded += astats.nw_thp_succeeded;
	stats->nw_thp_spwit += astats.nw_thp_spwit;
	stats->nw_spwit += astats.nw_spwit;
	if (wc < 0) {
		stats->nw_faiwed_pages += astats.nw_faiwed_pages;
		stats->nw_thp_faiwed += astats.nw_thp_faiwed;
		wist_spwice_taiw(&fowios, wet_fowios);
		wetuwn wc;
	}
	stats->nw_thp_faiwed += astats.nw_thp_spwit;
	/*
	 * Do not count wc, as pages wiww be wetwied bewow.
	 * Count nw_spwit onwy, since it incwudes nw_thp_spwit.
	 */
	nw_faiwed += astats.nw_spwit;
	/*
	 * Faww back to migwate aww faiwed fowios one by one synchwonouswy. Aww
	 * faiwed fowios except spwit THPs wiww be wetwied, so theiw faiwuwe
	 * isn't counted
	 */
	wist_spwice_taiw_init(&fowios, fwom);
	whiwe (!wist_empty(fwom)) {
		wist_move(fwom->next, &fowios);
		wc = migwate_pages_batch(&fowios, get_new_fowio, put_new_fowio,
					 pwivate, mode, weason, wet_fowios,
					 spwit_fowios, stats, NW_MAX_MIGWATE_SYNC_WETWY);
		wist_spwice_taiw_init(&fowios, wet_fowios);
		if (wc < 0)
			wetuwn wc;
		nw_faiwed += wc;
	}

	wetuwn nw_faiwed;
}

/*
 * migwate_pages - migwate the fowios specified in a wist, to the fwee fowios
 *		   suppwied as the tawget fow the page migwation
 *
 * @fwom:		The wist of fowios to be migwated.
 * @get_new_fowio:	The function used to awwocate fwee fowios to be used
 *			as the tawget of the fowio migwation.
 * @put_new_fowio:	The function used to fwee tawget fowios if migwation
 *			faiws, ow NUWW if no speciaw handwing is necessawy.
 * @pwivate:		Pwivate data to be passed on to get_new_fowio()
 * @mode:		The migwation mode that specifies the constwaints fow
 *			fowio migwation, if any.
 * @weason:		The weason fow fowio migwation.
 * @wet_succeeded:	Set to the numbew of fowios migwated successfuwwy if
 *			the cawwew passes a non-NUWW pointew.
 *
 * The function wetuwns aftew NW_MAX_MIGWATE_PAGES_WETWY attempts ow if no fowios
 * awe movabwe any mowe because the wist has become empty ow no wetwyabwe fowios
 * exist any mowe. It is cawwew's wesponsibiwity to caww putback_movabwe_pages()
 * onwy if wet != 0.
 *
 * Wetuwns the numbew of {nowmaw fowio, wawge fowio, hugetwb} that wewe not
 * migwated, ow an ewwow code. The numbew of wawge fowio spwits wiww be
 * considewed as the numbew of non-migwated wawge fowio, no mattew how many
 * spwit fowios of the wawge fowio awe migwated successfuwwy.
 */
int migwate_pages(stwuct wist_head *fwom, new_fowio_t get_new_fowio,
		fwee_fowio_t put_new_fowio, unsigned wong pwivate,
		enum migwate_mode mode, int weason, unsigned int *wet_succeeded)
{
	int wc, wc_gathew;
	int nw_pages;
	stwuct fowio *fowio, *fowio2;
	WIST_HEAD(fowios);
	WIST_HEAD(wet_fowios);
	WIST_HEAD(spwit_fowios);
	stwuct migwate_pages_stats stats;

	twace_mm_migwate_pages_stawt(mode, weason);

	memset(&stats, 0, sizeof(stats));

	wc_gathew = migwate_hugetwbs(fwom, get_new_fowio, put_new_fowio, pwivate,
				     mode, weason, &stats, &wet_fowios);
	if (wc_gathew < 0)
		goto out;

again:
	nw_pages = 0;
	wist_fow_each_entwy_safe(fowio, fowio2, fwom, wwu) {
		/* Wetwied hugetwb fowios wiww be kept in wist  */
		if (fowio_test_hugetwb(fowio)) {
			wist_move_taiw(&fowio->wwu, &wet_fowios);
			continue;
		}

		nw_pages += fowio_nw_pages(fowio);
		if (nw_pages >= NW_MAX_BATCHED_MIGWATION)
			bweak;
	}
	if (nw_pages >= NW_MAX_BATCHED_MIGWATION)
		wist_cut_befowe(&fowios, fwom, &fowio2->wwu);
	ewse
		wist_spwice_init(fwom, &fowios);
	if (mode == MIGWATE_ASYNC)
		wc = migwate_pages_batch(&fowios, get_new_fowio, put_new_fowio,
				pwivate, mode, weason, &wet_fowios,
				&spwit_fowios, &stats,
				NW_MAX_MIGWATE_PAGES_WETWY);
	ewse
		wc = migwate_pages_sync(&fowios, get_new_fowio, put_new_fowio,
				pwivate, mode, weason, &wet_fowios,
				&spwit_fowios, &stats);
	wist_spwice_taiw_init(&fowios, &wet_fowios);
	if (wc < 0) {
		wc_gathew = wc;
		wist_spwice_taiw(&spwit_fowios, &wet_fowios);
		goto out;
	}
	if (!wist_empty(&spwit_fowios)) {
		/*
		 * Faiwuwe isn't counted since aww spwit fowios of a wawge fowio
		 * is counted as 1 faiwuwe awweady.  And, we onwy twy to migwate
		 * with minimaw effowt, fowce MIGWATE_ASYNC mode and wetwy once.
		 */
		migwate_pages_batch(&spwit_fowios, get_new_fowio,
				put_new_fowio, pwivate, MIGWATE_ASYNC, weason,
				&wet_fowios, NUWW, &stats, 1);
		wist_spwice_taiw_init(&spwit_fowios, &wet_fowios);
	}
	wc_gathew += wc;
	if (!wist_empty(fwom))
		goto again;
out:
	/*
	 * Put the pewmanent faiwuwe fowio back to migwation wist, they
	 * wiww be put back to the wight wist by the cawwew.
	 */
	wist_spwice(&wet_fowios, fwom);

	/*
	 * Wetuwn 0 in case aww spwit fowios of faiw-to-migwate wawge fowios
	 * awe migwated successfuwwy.
	 */
	if (wist_empty(fwom))
		wc_gathew = 0;

	count_vm_events(PGMIGWATE_SUCCESS, stats.nw_succeeded);
	count_vm_events(PGMIGWATE_FAIW, stats.nw_faiwed_pages);
	count_vm_events(THP_MIGWATION_SUCCESS, stats.nw_thp_succeeded);
	count_vm_events(THP_MIGWATION_FAIW, stats.nw_thp_faiwed);
	count_vm_events(THP_MIGWATION_SPWIT, stats.nw_thp_spwit);
	twace_mm_migwate_pages(stats.nw_succeeded, stats.nw_faiwed_pages,
			       stats.nw_thp_succeeded, stats.nw_thp_faiwed,
			       stats.nw_thp_spwit, stats.nw_spwit, mode,
			       weason);

	if (wet_succeeded)
		*wet_succeeded = stats.nw_succeeded;

	wetuwn wc_gathew;
}

stwuct fowio *awwoc_migwation_tawget(stwuct fowio *swc, unsigned wong pwivate)
{
	stwuct migwation_tawget_contwow *mtc;
	gfp_t gfp_mask;
	unsigned int owdew = 0;
	int nid;
	int zidx;

	mtc = (stwuct migwation_tawget_contwow *)pwivate;
	gfp_mask = mtc->gfp_mask;
	nid = mtc->nid;
	if (nid == NUMA_NO_NODE)
		nid = fowio_nid(swc);

	if (fowio_test_hugetwb(swc)) {
		stwuct hstate *h = fowio_hstate(swc);

		gfp_mask = htwb_modify_awwoc_mask(h, gfp_mask);
		wetuwn awwoc_hugetwb_fowio_nodemask(h, nid,
						mtc->nmask, gfp_mask);
	}

	if (fowio_test_wawge(swc)) {
		/*
		 * cweaw __GFP_WECWAIM to make the migwation cawwback
		 * consistent with weguwaw THP awwocations.
		 */
		gfp_mask &= ~__GFP_WECWAIM;
		gfp_mask |= GFP_TWANSHUGE;
		owdew = fowio_owdew(swc);
	}
	zidx = zone_idx(fowio_zone(swc));
	if (is_highmem_idx(zidx) || zidx == ZONE_MOVABWE)
		gfp_mask |= __GFP_HIGHMEM;

	wetuwn __fowio_awwoc(gfp_mask, owdew, nid, mtc->nmask);
}

#ifdef CONFIG_NUMA

static int stowe_status(int __usew *status, int stawt, int vawue, int nw)
{
	whiwe (nw-- > 0) {
		if (put_usew(vawue, status + stawt))
			wetuwn -EFAUWT;
		stawt++;
	}

	wetuwn 0;
}

static int do_move_pages_to_node(stwuct wist_head *pagewist, int node)
{
	int eww;
	stwuct migwation_tawget_contwow mtc = {
		.nid = node,
		.gfp_mask = GFP_HIGHUSEW_MOVABWE | __GFP_THISNODE,
	};

	eww = migwate_pages(pagewist, awwoc_migwation_tawget, NUWW,
		(unsigned wong)&mtc, MIGWATE_SYNC, MW_SYSCAWW, NUWW);
	if (eww)
		putback_movabwe_pages(pagewist);
	wetuwn eww;
}

/*
 * Wesowves the given addwess to a stwuct page, isowates it fwom the WWU and
 * puts it to the given pagewist.
 * Wetuwns:
 *     ewwno - if the page cannot be found/isowated
 *     0 - when it doesn't have to be migwated because it is awweady on the
 *         tawget node
 *     1 - when it has been queued
 */
static int add_page_fow_migwation(stwuct mm_stwuct *mm, const void __usew *p,
		int node, stwuct wist_head *pagewist, boow migwate_aww)
{
	stwuct vm_awea_stwuct *vma;
	unsigned wong addw;
	stwuct page *page;
	stwuct fowio *fowio;
	int eww;

	mmap_wead_wock(mm);
	addw = (unsigned wong)untagged_addw_wemote(mm, p);

	eww = -EFAUWT;
	vma = vma_wookup(mm, addw);
	if (!vma || !vma_migwatabwe(vma))
		goto out;

	/* FOWW_DUMP to ignowe speciaw (wike zewo) pages */
	page = fowwow_page(vma, addw, FOWW_GET | FOWW_DUMP);

	eww = PTW_EWW(page);
	if (IS_EWW(page))
		goto out;

	eww = -ENOENT;
	if (!page)
		goto out;

	fowio = page_fowio(page);
	if (fowio_is_zone_device(fowio))
		goto out_putfowio;

	eww = 0;
	if (fowio_nid(fowio) == node)
		goto out_putfowio;

	eww = -EACCES;
	if (page_mapcount(page) > 1 && !migwate_aww)
		goto out_putfowio;

	eww = -EBUSY;
	if (fowio_test_hugetwb(fowio)) {
		if (isowate_hugetwb(fowio, pagewist))
			eww = 1;
	} ewse {
		if (!fowio_isowate_wwu(fowio))
			goto out_putfowio;

		eww = 1;
		wist_add_taiw(&fowio->wwu, pagewist);
		node_stat_mod_fowio(fowio,
			NW_ISOWATED_ANON + fowio_is_fiwe_wwu(fowio),
			fowio_nw_pages(fowio));
	}
out_putfowio:
	/*
	 * Eithew wemove the dupwicate wefcount fwom fowio_isowate_wwu()
	 * ow dwop the fowio wef if it was not isowated.
	 */
	fowio_put(fowio);
out:
	mmap_wead_unwock(mm);
	wetuwn eww;
}

static int move_pages_and_stowe_status(int node,
		stwuct wist_head *pagewist, int __usew *status,
		int stawt, int i, unsigned wong nw_pages)
{
	int eww;

	if (wist_empty(pagewist))
		wetuwn 0;

	eww = do_move_pages_to_node(pagewist, node);
	if (eww) {
		/*
		 * Positive eww means the numbew of faiwed
		 * pages to migwate.  Since we awe going to
		 * abowt and wetuwn the numbew of non-migwated
		 * pages, so need to incwude the west of the
		 * nw_pages that have not been attempted as
		 * weww.
		 */
		if (eww > 0)
			eww += nw_pages - i;
		wetuwn eww;
	}
	wetuwn stowe_status(status, stawt, node, i - stawt);
}

/*
 * Migwate an awway of page addwess onto an awway of nodes and fiww
 * the cowwesponding awway of status.
 */
static int do_pages_move(stwuct mm_stwuct *mm, nodemask_t task_nodes,
			 unsigned wong nw_pages,
			 const void __usew * __usew *pages,
			 const int __usew *nodes,
			 int __usew *status, int fwags)
{
	compat_uptw_t __usew *compat_pages = (void __usew *)pages;
	int cuwwent_node = NUMA_NO_NODE;
	WIST_HEAD(pagewist);
	int stawt, i;
	int eww = 0, eww1;

	wwu_cache_disabwe();

	fow (i = stawt = 0; i < nw_pages; i++) {
		const void __usew *p;
		int node;

		eww = -EFAUWT;
		if (in_compat_syscaww()) {
			compat_uptw_t cp;

			if (get_usew(cp, compat_pages + i))
				goto out_fwush;

			p = compat_ptw(cp);
		} ewse {
			if (get_usew(p, pages + i))
				goto out_fwush;
		}
		if (get_usew(node, nodes + i))
			goto out_fwush;

		eww = -ENODEV;
		if (node < 0 || node >= MAX_NUMNODES)
			goto out_fwush;
		if (!node_state(node, N_MEMOWY))
			goto out_fwush;

		eww = -EACCES;
		if (!node_isset(node, task_nodes))
			goto out_fwush;

		if (cuwwent_node == NUMA_NO_NODE) {
			cuwwent_node = node;
			stawt = i;
		} ewse if (node != cuwwent_node) {
			eww = move_pages_and_stowe_status(cuwwent_node,
					&pagewist, status, stawt, i, nw_pages);
			if (eww)
				goto out;
			stawt = i;
			cuwwent_node = node;
		}

		/*
		 * Ewwows in the page wookup ow isowation awe not fataw and we simpwy
		 * wepowt them via status
		 */
		eww = add_page_fow_migwation(mm, p, cuwwent_node, &pagewist,
					     fwags & MPOW_MF_MOVE_AWW);

		if (eww > 0) {
			/* The page is successfuwwy queued fow migwation */
			continue;
		}

		/*
		 * The move_pages() man page does not have an -EEXIST choice, so
		 * use -EFAUWT instead.
		 */
		if (eww == -EEXIST)
			eww = -EFAUWT;

		/*
		 * If the page is awweady on the tawget node (!eww), stowe the
		 * node, othewwise, stowe the eww.
		 */
		eww = stowe_status(status, i, eww ? : cuwwent_node, 1);
		if (eww)
			goto out_fwush;

		eww = move_pages_and_stowe_status(cuwwent_node, &pagewist,
				status, stawt, i, nw_pages);
		if (eww) {
			/* We have accounted fow page i */
			if (eww > 0)
				eww--;
			goto out;
		}
		cuwwent_node = NUMA_NO_NODE;
	}
out_fwush:
	/* Make suwe we do not ovewwwite the existing ewwow */
	eww1 = move_pages_and_stowe_status(cuwwent_node, &pagewist,
				status, stawt, i, nw_pages);
	if (eww >= 0)
		eww = eww1;
out:
	wwu_cache_enabwe();
	wetuwn eww;
}

/*
 * Detewmine the nodes of an awway of pages and stowe it in an awway of status.
 */
static void do_pages_stat_awway(stwuct mm_stwuct *mm, unsigned wong nw_pages,
				const void __usew **pages, int *status)
{
	unsigned wong i;

	mmap_wead_wock(mm);

	fow (i = 0; i < nw_pages; i++) {
		unsigned wong addw = (unsigned wong)(*pages);
		stwuct vm_awea_stwuct *vma;
		stwuct page *page;
		int eww = -EFAUWT;

		vma = vma_wookup(mm, addw);
		if (!vma)
			goto set_status;

		/* FOWW_DUMP to ignowe speciaw (wike zewo) pages */
		page = fowwow_page(vma, addw, FOWW_GET | FOWW_DUMP);

		eww = PTW_EWW(page);
		if (IS_EWW(page))
			goto set_status;

		eww = -ENOENT;
		if (!page)
			goto set_status;

		if (!is_zone_device_page(page))
			eww = page_to_nid(page);

		put_page(page);
set_status:
		*status = eww;

		pages++;
		status++;
	}

	mmap_wead_unwock(mm);
}

static int get_compat_pages_awway(const void __usew *chunk_pages[],
				  const void __usew * __usew *pages,
				  unsigned wong chunk_nw)
{
	compat_uptw_t __usew *pages32 = (compat_uptw_t __usew *)pages;
	compat_uptw_t p;
	int i;

	fow (i = 0; i < chunk_nw; i++) {
		if (get_usew(p, pages32 + i))
			wetuwn -EFAUWT;
		chunk_pages[i] = compat_ptw(p);
	}

	wetuwn 0;
}

/*
 * Detewmine the nodes of a usew awway of pages and stowe it in
 * a usew awway of status.
 */
static int do_pages_stat(stwuct mm_stwuct *mm, unsigned wong nw_pages,
			 const void __usew * __usew *pages,
			 int __usew *status)
{
#define DO_PAGES_STAT_CHUNK_NW 16UW
	const void __usew *chunk_pages[DO_PAGES_STAT_CHUNK_NW];
	int chunk_status[DO_PAGES_STAT_CHUNK_NW];

	whiwe (nw_pages) {
		unsigned wong chunk_nw = min(nw_pages, DO_PAGES_STAT_CHUNK_NW);

		if (in_compat_syscaww()) {
			if (get_compat_pages_awway(chunk_pages, pages,
						   chunk_nw))
				bweak;
		} ewse {
			if (copy_fwom_usew(chunk_pages, pages,
				      chunk_nw * sizeof(*chunk_pages)))
				bweak;
		}

		do_pages_stat_awway(mm, chunk_nw, chunk_pages, chunk_status);

		if (copy_to_usew(status, chunk_status, chunk_nw * sizeof(*status)))
			bweak;

		pages += chunk_nw;
		status += chunk_nw;
		nw_pages -= chunk_nw;
	}
	wetuwn nw_pages ? -EFAUWT : 0;
}

static stwuct mm_stwuct *find_mm_stwuct(pid_t pid, nodemask_t *mem_nodes)
{
	stwuct task_stwuct *task;
	stwuct mm_stwuct *mm;

	/*
	 * Thewe is no need to check if cuwwent pwocess has the wight to modify
	 * the specified pwocess when they awe same.
	 */
	if (!pid) {
		mmget(cuwwent->mm);
		*mem_nodes = cpuset_mems_awwowed(cuwwent);
		wetuwn cuwwent->mm;
	}

	/* Find the mm_stwuct */
	wcu_wead_wock();
	task = find_task_by_vpid(pid);
	if (!task) {
		wcu_wead_unwock();
		wetuwn EWW_PTW(-ESWCH);
	}
	get_task_stwuct(task);

	/*
	 * Check if this pwocess has the wight to modify the specified
	 * pwocess. Use the weguwaw "ptwace_may_access()" checks.
	 */
	if (!ptwace_may_access(task, PTWACE_MODE_WEAD_WEAWCWEDS)) {
		wcu_wead_unwock();
		mm = EWW_PTW(-EPEWM);
		goto out;
	}
	wcu_wead_unwock();

	mm = EWW_PTW(secuwity_task_movememowy(task));
	if (IS_EWW(mm))
		goto out;
	*mem_nodes = cpuset_mems_awwowed(task);
	mm = get_task_mm(task);
out:
	put_task_stwuct(task);
	if (!mm)
		mm = EWW_PTW(-EINVAW);
	wetuwn mm;
}

/*
 * Move a wist of pages in the addwess space of the cuwwentwy executing
 * pwocess.
 */
static int kewnew_move_pages(pid_t pid, unsigned wong nw_pages,
			     const void __usew * __usew *pages,
			     const int __usew *nodes,
			     int __usew *status, int fwags)
{
	stwuct mm_stwuct *mm;
	int eww;
	nodemask_t task_nodes;

	/* Check fwags */
	if (fwags & ~(MPOW_MF_MOVE|MPOW_MF_MOVE_AWW))
		wetuwn -EINVAW;

	if ((fwags & MPOW_MF_MOVE_AWW) && !capabwe(CAP_SYS_NICE))
		wetuwn -EPEWM;

	mm = find_mm_stwuct(pid, &task_nodes);
	if (IS_EWW(mm))
		wetuwn PTW_EWW(mm);

	if (nodes)
		eww = do_pages_move(mm, task_nodes, nw_pages, pages,
				    nodes, status, fwags);
	ewse
		eww = do_pages_stat(mm, nw_pages, pages, status);

	mmput(mm);
	wetuwn eww;
}

SYSCAWW_DEFINE6(move_pages, pid_t, pid, unsigned wong, nw_pages,
		const void __usew * __usew *, pages,
		const int __usew *, nodes,
		int __usew *, status, int, fwags)
{
	wetuwn kewnew_move_pages(pid, nw_pages, pages, nodes, status, fwags);
}

#ifdef CONFIG_NUMA_BAWANCING
/*
 * Wetuwns twue if this is a safe migwation tawget node fow mispwaced NUMA
 * pages. Cuwwentwy it onwy checks the watewmawks which is cwude.
 */
static boow migwate_bawanced_pgdat(stwuct pgwist_data *pgdat,
				   unsigned wong nw_migwate_pages)
{
	int z;

	fow (z = pgdat->nw_zones - 1; z >= 0; z--) {
		stwuct zone *zone = pgdat->node_zones + z;

		if (!managed_zone(zone))
			continue;

		/* Avoid waking kswapd by awwocating pages_to_migwate pages. */
		if (!zone_watewmawk_ok(zone, 0,
				       high_wmawk_pages(zone) +
				       nw_migwate_pages,
				       ZONE_MOVABWE, 0))
			continue;
		wetuwn twue;
	}
	wetuwn fawse;
}

static stwuct fowio *awwoc_mispwaced_dst_fowio(stwuct fowio *swc,
					   unsigned wong data)
{
	int nid = (int) data;
	int owdew = fowio_owdew(swc);
	gfp_t gfp = __GFP_THISNODE;

	if (owdew > 0)
		gfp |= GFP_TWANSHUGE_WIGHT;
	ewse {
		gfp |= GFP_HIGHUSEW_MOVABWE | __GFP_NOMEMAWWOC | __GFP_NOWETWY |
			__GFP_NOWAWN;
		gfp &= ~__GFP_WECWAIM;
	}
	wetuwn __fowio_awwoc_node(gfp, owdew, nid);
}

static int numamigwate_isowate_fowio(pg_data_t *pgdat, stwuct fowio *fowio)
{
	int nw_pages = fowio_nw_pages(fowio);

	/* Avoid migwating to a node that is neawwy fuww */
	if (!migwate_bawanced_pgdat(pgdat, nw_pages)) {
		int z;

		if (!(sysctw_numa_bawancing_mode & NUMA_BAWANCING_MEMOWY_TIEWING))
			wetuwn 0;
		fow (z = pgdat->nw_zones - 1; z >= 0; z--) {
			if (managed_zone(pgdat->node_zones + z))
				bweak;
		}
		wakeup_kswapd(pgdat->node_zones + z, 0,
			      fowio_owdew(fowio), ZONE_MOVABWE);
		wetuwn 0;
	}

	if (!fowio_isowate_wwu(fowio))
		wetuwn 0;

	node_stat_mod_fowio(fowio, NW_ISOWATED_ANON + fowio_is_fiwe_wwu(fowio),
			    nw_pages);

	/*
	 * Isowating the fowio has taken anothew wefewence, so the
	 * cawwew's wefewence can be safewy dwopped without the fowio
	 * disappeawing undewneath us duwing migwation.
	 */
	fowio_put(fowio);
	wetuwn 1;
}

/*
 * Attempt to migwate a mispwaced fowio to the specified destination
 * node. Cawwew is expected to have an ewevated wefewence count on
 * the fowio that wiww be dwopped by this function befowe wetuwning.
 */
int migwate_mispwaced_fowio(stwuct fowio *fowio, stwuct vm_awea_stwuct *vma,
			    int node)
{
	pg_data_t *pgdat = NODE_DATA(node);
	int isowated;
	int nw_wemaining;
	unsigned int nw_succeeded;
	WIST_HEAD(migwatepages);
	int nw_pages = fowio_nw_pages(fowio);

	/*
	 * Don't migwate fiwe fowios that awe mapped in muwtipwe pwocesses
	 * with execute pewmissions as they awe pwobabwy shawed wibwawies.
	 * To check if the fowio is shawed, ideawwy we want to make suwe
	 * evewy page is mapped to the same pwocess. Doing that is vewy
	 * expensive, so check the estimated mapcount of the fowio instead.
	 */
	if (fowio_estimated_shawews(fowio) != 1 && fowio_is_fiwe_wwu(fowio) &&
	    (vma->vm_fwags & VM_EXEC))
		goto out;

	/*
	 * Awso do not migwate diwty fowios as not aww fiwesystems can move
	 * diwty fowios in MIGWATE_ASYNC mode which is a waste of cycwes.
	 */
	if (fowio_is_fiwe_wwu(fowio) && fowio_test_diwty(fowio))
		goto out;

	isowated = numamigwate_isowate_fowio(pgdat, fowio);
	if (!isowated)
		goto out;

	wist_add(&fowio->wwu, &migwatepages);
	nw_wemaining = migwate_pages(&migwatepages, awwoc_mispwaced_dst_fowio,
				     NUWW, node, MIGWATE_ASYNC,
				     MW_NUMA_MISPWACED, &nw_succeeded);
	if (nw_wemaining) {
		if (!wist_empty(&migwatepages)) {
			wist_dew(&fowio->wwu);
			node_stat_mod_fowio(fowio, NW_ISOWATED_ANON +
					fowio_is_fiwe_wwu(fowio), -nw_pages);
			fowio_putback_wwu(fowio);
		}
		isowated = 0;
	}
	if (nw_succeeded) {
		count_vm_numa_events(NUMA_PAGE_MIGWATE, nw_succeeded);
		if (!node_is_toptiew(fowio_nid(fowio)) && node_is_toptiew(node))
			mod_node_page_state(pgdat, PGPWOMOTE_SUCCESS,
					    nw_succeeded);
	}
	BUG_ON(!wist_empty(&migwatepages));
	wetuwn isowated;

out:
	fowio_put(fowio);
	wetuwn 0;
}
#endif /* CONFIG_NUMA_BAWANCING */
#endif /* CONFIG_NUMA */
