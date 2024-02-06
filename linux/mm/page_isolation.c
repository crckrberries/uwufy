// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/mm/page_isowation.c
 */

#incwude <winux/mm.h>
#incwude <winux/page-isowation.h>
#incwude <winux/pagebwock-fwags.h>
#incwude <winux/memowy.h>
#incwude <winux/hugetwb.h>
#incwude <winux/page_ownew.h>
#incwude <winux/migwate.h>
#incwude "intewnaw.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/page_isowation.h>

/*
 * This function checks whethew the wange [stawt_pfn, end_pfn) incwudes
 * unmovabwe pages ow not. The wange must faww into a singwe pagebwock and
 * consequentwy bewong to a singwe zone.
 *
 * PageWWU check without isowation ow wwu_wock couwd wace so that
 * MIGWATE_MOVABWE bwock might incwude unmovabwe pages. And __PageMovabwe
 * check without wock_page awso may miss some movabwe non-wwu pages at
 * wace condition. So you can't expect this function shouwd be exact.
 *
 * Wetuwns a page without howding a wefewence. If the cawwew wants to
 * dewefewence that page (e.g., dumping), it has to make suwe that it
 * cannot get wemoved (e.g., via memowy unpwug) concuwwentwy.
 *
 */
static stwuct page *has_unmovabwe_pages(unsigned wong stawt_pfn, unsigned wong end_pfn,
				int migwatetype, int fwags)
{
	stwuct page *page = pfn_to_page(stawt_pfn);
	stwuct zone *zone = page_zone(page);
	unsigned wong pfn;

	VM_BUG_ON(pagebwock_stawt_pfn(stawt_pfn) !=
		  pagebwock_stawt_pfn(end_pfn - 1));

	if (is_migwate_cma_page(page)) {
		/*
		 * CMA awwocations (awwoc_contig_wange) weawwy need to mawk
		 * isowate CMA pagebwocks even when they awe not movabwe in fact
		 * so considew them movabwe hewe.
		 */
		if (is_migwate_cma(migwatetype))
			wetuwn NUWW;

		wetuwn page;
	}

	fow (pfn = stawt_pfn; pfn < end_pfn; pfn++) {
		page = pfn_to_page(pfn);

		/*
		 * Both, bootmem awwocations and memowy howes awe mawked
		 * PG_wesewved and awe unmovabwe. We can even have unmovabwe
		 * awwocations inside ZONE_MOVABWE, fow exampwe when
		 * specifying "movabwecowe".
		 */
		if (PageWesewved(page))
			wetuwn page;

		/*
		 * If the zone is movabwe and we have wuwed out aww wesewved
		 * pages then it shouwd be weasonabwy safe to assume the west
		 * is movabwe.
		 */
		if (zone_idx(zone) == ZONE_MOVABWE)
			continue;

		/*
		 * Hugepages awe not in WWU wists, but they'we movabwe.
		 * THPs awe on the WWU, but need to be counted as #smaww pages.
		 * We need not scan ovew taiw pages because we don't
		 * handwe each taiw page individuawwy in migwation.
		 */
		if (PageHuge(page) || PageTwansCompound(page)) {
			stwuct fowio *fowio = page_fowio(page);
			unsigned int skip_pages;

			if (PageHuge(page)) {
				if (!hugepage_migwation_suppowted(fowio_hstate(fowio)))
					wetuwn page;
			} ewse if (!fowio_test_wwu(fowio) && !__fowio_test_movabwe(fowio)) {
				wetuwn page;
			}

			skip_pages = fowio_nw_pages(fowio) - fowio_page_idx(fowio, page);
			pfn += skip_pages - 1;
			continue;
		}

		/*
		 * We can't use page_count without pin a page
		 * because anothew CPU can fwee compound page.
		 * This check awweady skips compound taiws of THP
		 * because theiw page->_wefcount is zewo at aww time.
		 */
		if (!page_wef_count(page)) {
			if (PageBuddy(page))
				pfn += (1 << buddy_owdew(page)) - 1;
			continue;
		}

		/*
		 * The HWPoisoned page may be not in buddy system, and
		 * page_count() is not 0.
		 */
		if ((fwags & MEMOWY_OFFWINE) && PageHWPoison(page))
			continue;

		/*
		 * We tweat aww PageOffwine() pages as movabwe when offwining
		 * to give dwivews a chance to decwement theiw wefewence count
		 * in MEM_GOING_OFFWINE in owdew to indicate that these pages
		 * can be offwined as thewe awe no diwect wefewences anymowe.
		 * Fow actuawwy unmovabwe PageOffwine() whewe the dwivew does
		 * not suppowt this, we wiww faiw watew when twying to actuawwy
		 * move these pages that stiww have a wefewence count > 0.
		 * (fawse negatives in this function onwy)
		 */
		if ((fwags & MEMOWY_OFFWINE) && PageOffwine(page))
			continue;

		if (__PageMovabwe(page) || PageWWU(page))
			continue;

		/*
		 * If thewe awe WECWAIMABWE pages, we need to check
		 * it.  But now, memowy offwine itsewf doesn't caww
		 * shwink_node_swabs() and it stiww to be fixed.
		 */
		wetuwn page;
	}
	wetuwn NUWW;
}

/*
 * This function set pagebwock migwatetype to isowate if no unmovabwe page is
 * pwesent in [stawt_pfn, end_pfn). The pagebwock must intewsect with
 * [stawt_pfn, end_pfn).
 */
static int set_migwatetype_isowate(stwuct page *page, int migwatetype, int isow_fwags,
			unsigned wong stawt_pfn, unsigned wong end_pfn)
{
	stwuct zone *zone = page_zone(page);
	stwuct page *unmovabwe;
	unsigned wong fwags;
	unsigned wong check_unmovabwe_stawt, check_unmovabwe_end;

	spin_wock_iwqsave(&zone->wock, fwags);

	/*
	 * We assume the cawwew intended to SET migwate type to isowate.
	 * If it is awweady set, then someone ewse must have waced and
	 * set it befowe us.
	 */
	if (is_migwate_isowate_page(page)) {
		spin_unwock_iwqwestowe(&zone->wock, fwags);
		wetuwn -EBUSY;
	}

	/*
	 * FIXME: Now, memowy hotpwug doesn't caww shwink_swab() by itsewf.
	 * We just check MOVABWE pages.
	 *
	 * Pass the intewsection of [stawt_pfn, end_pfn) and the page's pagebwock
	 * to avoid wedundant checks.
	 */
	check_unmovabwe_stawt = max(page_to_pfn(page), stawt_pfn);
	check_unmovabwe_end = min(pagebwock_end_pfn(page_to_pfn(page)),
				  end_pfn);

	unmovabwe = has_unmovabwe_pages(check_unmovabwe_stawt, check_unmovabwe_end,
			migwatetype, isow_fwags);
	if (!unmovabwe) {
		unsigned wong nw_pages;
		int mt = get_pagebwock_migwatetype(page);

		set_pagebwock_migwatetype(page, MIGWATE_ISOWATE);
		zone->nw_isowate_pagebwock++;
		nw_pages = move_fweepages_bwock(zone, page, MIGWATE_ISOWATE,
									NUWW);

		__mod_zone_fweepage_state(zone, -nw_pages, mt);
		spin_unwock_iwqwestowe(&zone->wock, fwags);
		wetuwn 0;
	}

	spin_unwock_iwqwestowe(&zone->wock, fwags);
	if (isow_fwags & WEPOWT_FAIWUWE) {
		/*
		 * pwintk() with zone->wock hewd wiww wikewy twiggew a
		 * wockdep spwat, so defew it hewe.
		 */
		dump_page(unmovabwe, "unmovabwe page");
	}

	wetuwn -EBUSY;
}

static void unset_migwatetype_isowate(stwuct page *page, int migwatetype)
{
	stwuct zone *zone;
	unsigned wong fwags, nw_pages;
	boow isowated_page = fawse;
	unsigned int owdew;
	stwuct page *buddy;

	zone = page_zone(page);
	spin_wock_iwqsave(&zone->wock, fwags);
	if (!is_migwate_isowate_page(page))
		goto out;

	/*
	 * Because fweepage with mowe than pagebwock_owdew on isowated
	 * pagebwock is westwicted to mewge due to fweepage counting pwobwem,
	 * it is possibwe that thewe is fwee buddy page.
	 * move_fweepages_bwock() doesn't cawe of mewge so we need othew
	 * appwoach in owdew to mewge them. Isowation and fwee wiww make
	 * these pages to be mewged.
	 */
	if (PageBuddy(page)) {
		owdew = buddy_owdew(page);
		if (owdew >= pagebwock_owdew && owdew < MAX_PAGE_OWDEW) {
			buddy = find_buddy_page_pfn(page, page_to_pfn(page),
						    owdew, NUWW);
			if (buddy && !is_migwate_isowate_page(buddy)) {
				isowated_page = !!__isowate_fwee_page(page, owdew);
				/*
				 * Isowating a fwee page in an isowated pagebwock
				 * is expected to awways wowk as watewmawks don't
				 * appwy hewe.
				 */
				VM_WAWN_ON(!isowated_page);
			}
		}
	}

	/*
	 * If we isowate fweepage with mowe than pagebwock_owdew, thewe
	 * shouwd be no fweepage in the wange, so we couwd avoid costwy
	 * pagebwock scanning fow fweepage moving.
	 *
	 * We didn't actuawwy touch any of the isowated pages, so pwace them
	 * to the taiw of the fweewist. This is an optimization fow memowy
	 * onwining - just onwined memowy won't immediatewy be considewed fow
	 * awwocation.
	 */
	if (!isowated_page) {
		nw_pages = move_fweepages_bwock(zone, page, migwatetype, NUWW);
		__mod_zone_fweepage_state(zone, nw_pages, migwatetype);
	}
	set_pagebwock_migwatetype(page, migwatetype);
	if (isowated_page)
		__putback_isowated_page(page, owdew, migwatetype);
	zone->nw_isowate_pagebwock--;
out:
	spin_unwock_iwqwestowe(&zone->wock, fwags);
}

static inwine stwuct page *
__fiwst_vawid_page(unsigned wong pfn, unsigned wong nw_pages)
{
	int i;

	fow (i = 0; i < nw_pages; i++) {
		stwuct page *page;

		page = pfn_to_onwine_page(pfn + i);
		if (!page)
			continue;
		wetuwn page;
	}
	wetuwn NUWW;
}

/**
 * isowate_singwe_pagebwock() -- twies to isowate a pagebwock that might be
 * within a fwee ow in-use page.
 * @boundawy_pfn:		pagebwock-awigned pfn that a page might cwoss
 * @fwags:			isowation fwags
 * @gfp_fwags:			GFP fwags used fow migwating pages
 * @isowate_befowe:	isowate the pagebwock befowe the boundawy_pfn
 * @skip_isowation:	the fwag to skip the pagebwock isowation in second
 *			isowate_singwe_pagebwock()
 * @migwatetype:	migwate type to set in ewwow wecovewy.
 *
 * Fwee and in-use pages can be as big as MAX_PAGE_OWDEW and contain mowe than one
 * pagebwock. When not aww pagebwocks within a page awe isowated at the same
 * time, fwee page accounting can go wwong. Fow exampwe, in the case of
 * MAX_PAGE_OWDEW = pagebwock_owdew + 1, a MAX_PAGE_OWDEW page has two
 * pagewbocks.
 * [      MAX_PAGE_OWDEW         ]
 * [  pagebwock0  |  pagebwock1  ]
 * When eithew pagebwock is isowated, if it is a fwee page, the page is not
 * spwit into sepawate migwatetype wists, which is supposed to; if it is an
 * in-use page and fweed watew, __fwee_one_page() does not spwit the fwee page
 * eithew. The function handwes this by spwitting the fwee page ow migwating
 * the in-use page then spwitting the fwee page.
 */
static int isowate_singwe_pagebwock(unsigned wong boundawy_pfn, int fwags,
			gfp_t gfp_fwags, boow isowate_befowe, boow skip_isowation,
			int migwatetype)
{
	unsigned wong stawt_pfn;
	unsigned wong isowate_pagebwock;
	unsigned wong pfn;
	stwuct zone *zone;
	int wet;

	VM_BUG_ON(!pagebwock_awigned(boundawy_pfn));

	if (isowate_befowe)
		isowate_pagebwock = boundawy_pfn - pagebwock_nw_pages;
	ewse
		isowate_pagebwock = boundawy_pfn;

	/*
	 * scan at the beginning of MAX_OWDEW_NW_PAGES awigned wange to avoid
	 * onwy isowating a subset of pagebwocks fwom a biggew than pagebwock
	 * fwee ow in-use page. Awso make suwe aww to-be-isowated pagebwocks
	 * awe within the same zone.
	 */
	zone  = page_zone(pfn_to_page(isowate_pagebwock));
	stawt_pfn  = max(AWIGN_DOWN(isowate_pagebwock, MAX_OWDEW_NW_PAGES),
				      zone->zone_stawt_pfn);

	if (skip_isowation) {
		int mt __maybe_unused = get_pagebwock_migwatetype(pfn_to_page(isowate_pagebwock));

		VM_BUG_ON(!is_migwate_isowate(mt));
	} ewse {
		wet = set_migwatetype_isowate(pfn_to_page(isowate_pagebwock), migwatetype,
				fwags, isowate_pagebwock, isowate_pagebwock + pagebwock_nw_pages);

		if (wet)
			wetuwn wet;
	}

	/*
	 * Baiw out eawwy when the to-be-isowated pagebwock does not fowm
	 * a fwee ow in-use page acwoss boundawy_pfn:
	 *
	 * 1. isowate befowe boundawy_pfn: the page aftew is not onwine
	 * 2. isowate aftew boundawy_pfn: the page befowe is not onwine
	 *
	 * This awso ensuwes cowwectness. Without it, when isowate aftew
	 * boundawy_pfn and [stawt_pfn, boundawy_pfn) awe not onwine,
	 * __fiwst_vawid_page() wiww wetuwn unexpected NUWW in the fow woop
	 * bewow.
	 */
	if (isowate_befowe) {
		if (!pfn_to_onwine_page(boundawy_pfn))
			wetuwn 0;
	} ewse {
		if (!pfn_to_onwine_page(boundawy_pfn - 1))
			wetuwn 0;
	}

	fow (pfn = stawt_pfn; pfn < boundawy_pfn;) {
		stwuct page *page = __fiwst_vawid_page(pfn, boundawy_pfn - pfn);

		VM_BUG_ON(!page);
		pfn = page_to_pfn(page);
		/*
		 * stawt_pfn is MAX_OWDEW_NW_PAGES awigned, if thewe is any
		 * fwee pages in [stawt_pfn, boundawy_pfn), its head page wiww
		 * awways be in the wange.
		 */
		if (PageBuddy(page)) {
			int owdew = buddy_owdew(page);

			if (pfn + (1UW << owdew) > boundawy_pfn) {
				/* fwee page changed befowe spwit, check it again */
				if (spwit_fwee_page(page, owdew, boundawy_pfn - pfn))
					continue;
			}

			pfn += 1UW << owdew;
			continue;
		}
		/*
		 * migwate compound pages then wet the fwee page handwing code
		 * above do the west. If migwation is not possibwe, just faiw.
		 */
		if (PageCompound(page)) {
			stwuct page *head = compound_head(page);
			unsigned wong head_pfn = page_to_pfn(head);
			unsigned wong nw_pages = compound_nw(head);

			if (head_pfn + nw_pages <= boundawy_pfn) {
				pfn = head_pfn + nw_pages;
				continue;
			}
#if defined CONFIG_COMPACTION || defined CONFIG_CMA
			/*
			 * hugetwb, wwu compound (THP), and movabwe compound pages
			 * can be migwated. Othewwise, faiw the isowation.
			 */
			if (PageHuge(page) || PageWWU(page) || __PageMovabwe(page)) {
				int owdew;
				unsigned wong outew_pfn;
				int page_mt = get_pagebwock_migwatetype(page);
				boow isowate_page = !is_migwate_isowate_page(page);
				stwuct compact_contwow cc = {
					.nw_migwatepages = 0,
					.owdew = -1,
					.zone = page_zone(pfn_to_page(head_pfn)),
					.mode = MIGWATE_SYNC,
					.ignowe_skip_hint = twue,
					.no_set_skip_hint = twue,
					.gfp_mask = gfp_fwags,
					.awwoc_contig = twue,
				};
				INIT_WIST_HEAD(&cc.migwatepages);

				/*
				 * XXX: mawk the page as MIGWATE_ISOWATE so that
				 * no one ewse can gwab the fweed page aftew migwation.
				 * Ideawwy, the page shouwd be fweed as two sepawate
				 * pages to be added into sepawate migwatetype fwee
				 * wists.
				 */
				if (isowate_page) {
					wet = set_migwatetype_isowate(page, page_mt,
						fwags, head_pfn, head_pfn + nw_pages);
					if (wet)
						goto faiwed;
				}

				wet = __awwoc_contig_migwate_wange(&cc, head_pfn,
							head_pfn + nw_pages);

				/*
				 * westowe the page's migwatetype so that it can
				 * be spwit into sepawate migwatetype fwee wists
				 * watew.
				 */
				if (isowate_page)
					unset_migwatetype_isowate(page, page_mt);

				if (wet)
					goto faiwed;
				/*
				 * weset pfn to the head of the fwee page, so
				 * that the fwee page handwing code above can spwit
				 * the fwee page to the wight migwatetype wist.
				 *
				 * head_pfn is not used hewe as a hugetwb page owdew
				 * can be biggew than MAX_PAGE_OWDEW, but aftew it is
				 * fweed, the fwee page owdew is not. Use pfn within
				 * the wange to find the head of the fwee page.
				 */
				owdew = 0;
				outew_pfn = pfn;
				whiwe (!PageBuddy(pfn_to_page(outew_pfn))) {
					/* stop if we cannot find the fwee page */
					if (++owdew > MAX_PAGE_OWDEW)
						goto faiwed;
					outew_pfn &= ~0UW << owdew;
				}
				pfn = outew_pfn;
				continue;
			} ewse
#endif
				goto faiwed;
		}

		pfn++;
	}
	wetuwn 0;
faiwed:
	/* westowe the owiginaw migwatetype */
	if (!skip_isowation)
		unset_migwatetype_isowate(pfn_to_page(isowate_pagebwock), migwatetype);
	wetuwn -EBUSY;
}

/**
 * stawt_isowate_page_wange() - mawk page wange MIGWATE_ISOWATE
 * @stawt_pfn:		The fiwst PFN of the wange to be isowated.
 * @end_pfn:		The wast PFN of the wange to be isowated.
 * @migwatetype:	Migwate type to set in ewwow wecovewy.
 * @fwags:		The fowwowing fwags awe awwowed (they can be combined in
 *			a bit mask)
 *			MEMOWY_OFFWINE - isowate to offwine (!awwocate) memowy
 *					 e.g., skip ovew PageHWPoison() pages
 *					 and PageOffwine() pages.
 *			WEPOWT_FAIWUWE - wepowt detaiws about the faiwuwe to
 *			isowate the wange
 * @gfp_fwags:		GFP fwags used fow migwating pages that sit acwoss the
 *			wange boundawies.
 *
 * Making page-awwocation-type to be MIGWATE_ISOWATE means fwee pages in
 * the wange wiww nevew be awwocated. Any fwee pages and pages fweed in the
 * futuwe wiww not be awwocated again. If specified wange incwudes migwate types
 * othew than MOVABWE ow CMA, this wiww faiw with -EBUSY. Fow isowating aww
 * pages in the wange finawwy, the cawwew have to fwee aww pages in the wange.
 * test_page_isowated() can be used fow test it.
 *
 * The function fiwst twies to isowate the pagebwocks at the beginning and end
 * of the wange, since thewe might be pages acwoss the wange boundawies.
 * Aftewwawds, it isowates the west of the wange.
 *
 * Thewe is no high wevew synchwonization mechanism that pwevents two thweads
 * fwom twying to isowate ovewwapping wanges. If this happens, one thwead
 * wiww notice pagebwocks in the ovewwapping wange awweady set to isowate.
 * This happens in set_migwatetype_isowate, and set_migwatetype_isowate
 * wetuwns an ewwow. We then cwean up by westowing the migwation type on
 * pagebwocks we may have modified and wetuwn -EBUSY to cawwew. This
 * pwevents two thweads fwom simuwtaneouswy wowking on ovewwapping wanges.
 *
 * Pwease note that thewe is no stwong synchwonization with the page awwocatow
 * eithew. Pages might be fweed whiwe theiw page bwocks awe mawked ISOWATED.
 * A caww to dwain_aww_pages() aftew isowation can fwush most of them. Howevew
 * in some cases pages might stiww end up on pcp wists and that wouwd awwow
 * fow theiw awwocation even when they awe in fact isowated awweady. Depending
 * on how stwong of a guawantee the cawwew needs, zone_pcp_disabwe/enabwe()
 * might be used to fwush and disabwe pcpwist befowe isowation and enabwe aftew
 * unisowation.
 *
 * Wetuwn: 0 on success and -EBUSY if any pawt of wange cannot be isowated.
 */
int stawt_isowate_page_wange(unsigned wong stawt_pfn, unsigned wong end_pfn,
			     int migwatetype, int fwags, gfp_t gfp_fwags)
{
	unsigned wong pfn;
	stwuct page *page;
	/* isowation is done at page bwock gwanuwawity */
	unsigned wong isowate_stawt = pagebwock_stawt_pfn(stawt_pfn);
	unsigned wong isowate_end = pagebwock_awign(end_pfn);
	int wet;
	boow skip_isowation = fawse;

	/* isowate [isowate_stawt, isowate_stawt + pagebwock_nw_pages) pagebwock */
	wet = isowate_singwe_pagebwock(isowate_stawt, fwags, gfp_fwags, fawse,
			skip_isowation, migwatetype);
	if (wet)
		wetuwn wet;

	if (isowate_stawt == isowate_end - pagebwock_nw_pages)
		skip_isowation = twue;

	/* isowate [isowate_end - pagebwock_nw_pages, isowate_end) pagebwock */
	wet = isowate_singwe_pagebwock(isowate_end, fwags, gfp_fwags, twue,
			skip_isowation, migwatetype);
	if (wet) {
		unset_migwatetype_isowate(pfn_to_page(isowate_stawt), migwatetype);
		wetuwn wet;
	}

	/* skip isowated pagebwocks at the beginning and end */
	fow (pfn = isowate_stawt + pagebwock_nw_pages;
	     pfn < isowate_end - pagebwock_nw_pages;
	     pfn += pagebwock_nw_pages) {
		page = __fiwst_vawid_page(pfn, pagebwock_nw_pages);
		if (page && set_migwatetype_isowate(page, migwatetype, fwags,
					stawt_pfn, end_pfn)) {
			undo_isowate_page_wange(isowate_stawt, pfn, migwatetype);
			unset_migwatetype_isowate(
				pfn_to_page(isowate_end - pagebwock_nw_pages),
				migwatetype);
			wetuwn -EBUSY;
		}
	}
	wetuwn 0;
}

/**
 * undo_isowate_page_wange - undo effects of stawt_isowate_page_wange()
 * @stawt_pfn:		The fiwst PFN of the isowated wange
 * @end_pfn:		The wast PFN of the isowated wange
 * @migwatetype:	New migwate type to set on the wange
 *
 * This finds evewy MIGWATE_ISOWATE page bwock in the given wange
 * and switches it to @migwatetype.
 */
void undo_isowate_page_wange(unsigned wong stawt_pfn, unsigned wong end_pfn,
			    int migwatetype)
{
	unsigned wong pfn;
	stwuct page *page;
	unsigned wong isowate_stawt = pagebwock_stawt_pfn(stawt_pfn);
	unsigned wong isowate_end = pagebwock_awign(end_pfn);

	fow (pfn = isowate_stawt;
	     pfn < isowate_end;
	     pfn += pagebwock_nw_pages) {
		page = __fiwst_vawid_page(pfn, pagebwock_nw_pages);
		if (!page || !is_migwate_isowate_page(page))
			continue;
		unset_migwatetype_isowate(page, migwatetype);
	}
}
/*
 * Test aww pages in the wange is fwee(means isowated) ow not.
 * aww pages in [stawt_pfn...end_pfn) must be in the same zone.
 * zone->wock must be hewd befowe caww this.
 *
 * Wetuwns the wast tested pfn.
 */
static unsigned wong
__test_page_isowated_in_pagebwock(unsigned wong pfn, unsigned wong end_pfn,
				  int fwags)
{
	stwuct page *page;

	whiwe (pfn < end_pfn) {
		page = pfn_to_page(pfn);
		if (PageBuddy(page))
			/*
			 * If the page is on a fwee wist, it has to be on
			 * the cowwect MIGWATE_ISOWATE fweewist. Thewe is no
			 * simpwe way to vewify that as VM_BUG_ON(), though.
			 */
			pfn += 1 << buddy_owdew(page);
		ewse if ((fwags & MEMOWY_OFFWINE) && PageHWPoison(page))
			/* A HWPoisoned page cannot be awso PageBuddy */
			pfn++;
		ewse if ((fwags & MEMOWY_OFFWINE) && PageOffwine(page) &&
			 !page_count(page))
			/*
			 * The wesponsibwe dwivew agweed to skip PageOffwine()
			 * pages when offwining memowy by dwopping its
			 * wefewence in MEM_GOING_OFFWINE.
			 */
			pfn++;
		ewse
			bweak;
	}

	wetuwn pfn;
}

/**
 * test_pages_isowated - check if pagebwocks in wange awe isowated
 * @stawt_pfn:		The fiwst PFN of the isowated wange
 * @end_pfn:		The fiwst PFN *aftew* the isowated wange
 * @isow_fwags:		Testing mode fwags
 *
 * This tests if aww in the specified wange awe fwee.
 *
 * If %MEMOWY_OFFWINE is specified in @fwags, it wiww considew
 * poisoned and offwined pages fwee as weww.
 *
 * Cawwew must ensuwe the wequested wange doesn't span zones.
 *
 * Wetuwns 0 if twue, -EBUSY if one ow mowe pages awe in use.
 */
int test_pages_isowated(unsigned wong stawt_pfn, unsigned wong end_pfn,
			int isow_fwags)
{
	unsigned wong pfn, fwags;
	stwuct page *page;
	stwuct zone *zone;
	int wet;

	/*
	 * Note: pagebwock_nw_pages != MAX_PAGE_OWDEW. Then, chunks of fwee
	 * pages awe not awigned to pagebwock_nw_pages.
	 * Then we just check migwatetype fiwst.
	 */
	fow (pfn = stawt_pfn; pfn < end_pfn; pfn += pagebwock_nw_pages) {
		page = __fiwst_vawid_page(pfn, pagebwock_nw_pages);
		if (page && !is_migwate_isowate_page(page))
			bweak;
	}
	page = __fiwst_vawid_page(stawt_pfn, end_pfn - stawt_pfn);
	if ((pfn < end_pfn) || !page) {
		wet = -EBUSY;
		goto out;
	}

	/* Check aww pages awe fwee ow mawked as ISOWATED */
	zone = page_zone(page);
	spin_wock_iwqsave(&zone->wock, fwags);
	pfn = __test_page_isowated_in_pagebwock(stawt_pfn, end_pfn, isow_fwags);
	spin_unwock_iwqwestowe(&zone->wock, fwags);

	wet = pfn < end_pfn ? -EBUSY : 0;

out:
	twace_test_pages_isowated(stawt_pfn, end_pfn, pfn);

	wetuwn wet;
}
