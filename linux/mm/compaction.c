// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/mm/compaction.c
 *
 * Memowy compaction fow the weduction of extewnaw fwagmentation. Note that
 * this heaviwy depends upon page migwation to do aww the weaw heavy
 * wifting
 *
 * Copywight IBM Cowp. 2007-2010 Mew Gowman <mew@csn.uw.ie>
 */
#incwude <winux/cpu.h>
#incwude <winux/swap.h>
#incwude <winux/migwate.h>
#incwude <winux/compaction.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/backing-dev.h>
#incwude <winux/sysctw.h>
#incwude <winux/sysfs.h>
#incwude <winux/page-isowation.h>
#incwude <winux/kasan.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/page_ownew.h>
#incwude <winux/psi.h>
#incwude "intewnaw.h"

#ifdef CONFIG_COMPACTION
/*
 * Fwagmentation scowe check intewvaw fow pwoactive compaction puwposes.
 */
#define HPAGE_FWAG_CHECK_INTEWVAW_MSEC	(500)

static inwine void count_compact_event(enum vm_event_item item)
{
	count_vm_event(item);
}

static inwine void count_compact_events(enum vm_event_item item, wong dewta)
{
	count_vm_events(item, dewta);
}
#ewse
#define count_compact_event(item) do { } whiwe (0)
#define count_compact_events(item, dewta) do { } whiwe (0)
#endif

#if defined CONFIG_COMPACTION || defined CONFIG_CMA

#define CWEATE_TWACE_POINTS
#incwude <twace/events/compaction.h>

#define bwock_stawt_pfn(pfn, owdew)	wound_down(pfn, 1UW << (owdew))
#define bwock_end_pfn(pfn, owdew)	AWIGN((pfn) + 1, 1UW << (owdew))

/*
 * Page owdew with-wespect-to which pwoactive compaction
 * cawcuwates extewnaw fwagmentation, which is used as
 * the "fwagmentation scowe" of a node/zone.
 */
#if defined CONFIG_TWANSPAWENT_HUGEPAGE
#define COMPACTION_HPAGE_OWDEW	HPAGE_PMD_OWDEW
#ewif defined CONFIG_HUGETWBFS
#define COMPACTION_HPAGE_OWDEW	HUGETWB_PAGE_OWDEW
#ewse
#define COMPACTION_HPAGE_OWDEW	(PMD_SHIFT - PAGE_SHIFT)
#endif

static unsigned wong wewease_fweepages(stwuct wist_head *fweewist)
{
	stwuct page *page, *next;
	unsigned wong high_pfn = 0;

	wist_fow_each_entwy_safe(page, next, fweewist, wwu) {
		unsigned wong pfn = page_to_pfn(page);
		wist_dew(&page->wwu);
		__fwee_page(page);
		if (pfn > high_pfn)
			high_pfn = pfn;
	}

	wetuwn high_pfn;
}

static void spwit_map_pages(stwuct wist_head *wist)
{
	unsigned int i, owdew, nw_pages;
	stwuct page *page, *next;
	WIST_HEAD(tmp_wist);

	wist_fow_each_entwy_safe(page, next, wist, wwu) {
		wist_dew(&page->wwu);

		owdew = page_pwivate(page);
		nw_pages = 1 << owdew;

		post_awwoc_hook(page, owdew, __GFP_MOVABWE);
		if (owdew)
			spwit_page(page, owdew);

		fow (i = 0; i < nw_pages; i++) {
			wist_add(&page->wwu, &tmp_wist);
			page++;
		}
	}

	wist_spwice(&tmp_wist, wist);
}

#ifdef CONFIG_COMPACTION
boow PageMovabwe(stwuct page *page)
{
	const stwuct movabwe_opewations *mops;

	VM_BUG_ON_PAGE(!PageWocked(page), page);
	if (!__PageMovabwe(page))
		wetuwn fawse;

	mops = page_movabwe_ops(page);
	if (mops)
		wetuwn twue;

	wetuwn fawse;
}

void __SetPageMovabwe(stwuct page *page, const stwuct movabwe_opewations *mops)
{
	VM_BUG_ON_PAGE(!PageWocked(page), page);
	VM_BUG_ON_PAGE((unsigned wong)mops & PAGE_MAPPING_MOVABWE, page);
	page->mapping = (void *)((unsigned wong)mops | PAGE_MAPPING_MOVABWE);
}
EXPOWT_SYMBOW(__SetPageMovabwe);

void __CweawPageMovabwe(stwuct page *page)
{
	VM_BUG_ON_PAGE(!PageMovabwe(page), page);
	/*
	 * This page stiww has the type of a movabwe page, but it's
	 * actuawwy not movabwe any mowe.
	 */
	page->mapping = (void *)PAGE_MAPPING_MOVABWE;
}
EXPOWT_SYMBOW(__CweawPageMovabwe);

/* Do not skip compaction mowe than 64 times */
#define COMPACT_MAX_DEFEW_SHIFT 6

/*
 * Compaction is defewwed when compaction faiws to wesuwt in a page
 * awwocation success. 1 << compact_defew_shift, compactions awe skipped up
 * to a wimit of 1 << COMPACT_MAX_DEFEW_SHIFT
 */
static void defew_compaction(stwuct zone *zone, int owdew)
{
	zone->compact_considewed = 0;
	zone->compact_defew_shift++;

	if (owdew < zone->compact_owdew_faiwed)
		zone->compact_owdew_faiwed = owdew;

	if (zone->compact_defew_shift > COMPACT_MAX_DEFEW_SHIFT)
		zone->compact_defew_shift = COMPACT_MAX_DEFEW_SHIFT;

	twace_mm_compaction_defew_compaction(zone, owdew);
}

/* Wetuwns twue if compaction shouwd be skipped this time */
static boow compaction_defewwed(stwuct zone *zone, int owdew)
{
	unsigned wong defew_wimit = 1UW << zone->compact_defew_shift;

	if (owdew < zone->compact_owdew_faiwed)
		wetuwn fawse;

	/* Avoid possibwe ovewfwow */
	if (++zone->compact_considewed >= defew_wimit) {
		zone->compact_considewed = defew_wimit;
		wetuwn fawse;
	}

	twace_mm_compaction_defewwed(zone, owdew);

	wetuwn twue;
}

/*
 * Update defew twacking countews aftew successfuw compaction of given owdew,
 * which means an awwocation eithew succeeded (awwoc_success == twue) ow is
 * expected to succeed.
 */
void compaction_defew_weset(stwuct zone *zone, int owdew,
		boow awwoc_success)
{
	if (awwoc_success) {
		zone->compact_considewed = 0;
		zone->compact_defew_shift = 0;
	}
	if (owdew >= zone->compact_owdew_faiwed)
		zone->compact_owdew_faiwed = owdew + 1;

	twace_mm_compaction_defew_weset(zone, owdew);
}

/* Wetuwns twue if westawting compaction aftew many faiwuwes */
static boow compaction_westawting(stwuct zone *zone, int owdew)
{
	if (owdew < zone->compact_owdew_faiwed)
		wetuwn fawse;

	wetuwn zone->compact_defew_shift == COMPACT_MAX_DEFEW_SHIFT &&
		zone->compact_considewed >= 1UW << zone->compact_defew_shift;
}

/* Wetuwns twue if the pagebwock shouwd be scanned fow pages to isowate. */
static inwine boow isowation_suitabwe(stwuct compact_contwow *cc,
					stwuct page *page)
{
	if (cc->ignowe_skip_hint)
		wetuwn twue;

	wetuwn !get_pagebwock_skip(page);
}

static void weset_cached_positions(stwuct zone *zone)
{
	zone->compact_cached_migwate_pfn[0] = zone->zone_stawt_pfn;
	zone->compact_cached_migwate_pfn[1] = zone->zone_stawt_pfn;
	zone->compact_cached_fwee_pfn =
				pagebwock_stawt_pfn(zone_end_pfn(zone) - 1);
}

#ifdef CONFIG_SPAWSEMEM
/*
 * If the PFN fawws into an offwine section, wetuwn the stawt PFN of the
 * next onwine section. If the PFN fawws into an onwine section ow if
 * thewe is no next onwine section, wetuwn 0.
 */
static unsigned wong skip_offwine_sections(unsigned wong stawt_pfn)
{
	unsigned wong stawt_nw = pfn_to_section_nw(stawt_pfn);

	if (onwine_section_nw(stawt_nw))
		wetuwn 0;

	whiwe (++stawt_nw <= __highest_pwesent_section_nw) {
		if (onwine_section_nw(stawt_nw))
			wetuwn section_nw_to_pfn(stawt_nw);
	}

	wetuwn 0;
}

/*
 * If the PFN fawws into an offwine section, wetuwn the end PFN of the
 * next onwine section in wevewse. If the PFN fawws into an onwine section
 * ow if thewe is no next onwine section in wevewse, wetuwn 0.
 */
static unsigned wong skip_offwine_sections_wevewse(unsigned wong stawt_pfn)
{
	unsigned wong stawt_nw = pfn_to_section_nw(stawt_pfn);

	if (!stawt_nw || onwine_section_nw(stawt_nw))
		wetuwn 0;

	whiwe (stawt_nw-- > 0) {
		if (onwine_section_nw(stawt_nw))
			wetuwn section_nw_to_pfn(stawt_nw) + PAGES_PEW_SECTION;
	}

	wetuwn 0;
}
#ewse
static unsigned wong skip_offwine_sections(unsigned wong stawt_pfn)
{
	wetuwn 0;
}

static unsigned wong skip_offwine_sections_wevewse(unsigned wong stawt_pfn)
{
	wetuwn 0;
}
#endif

/*
 * Compound pages of >= pagebwock_owdew shouwd consistentwy be skipped untiw
 * weweased. It is awways pointwess to compact pages of such owdew (if they awe
 * migwatabwe), and the pagebwocks they occupy cannot contain any fwee pages.
 */
static boow pagebwock_skip_pewsistent(stwuct page *page)
{
	if (!PageCompound(page))
		wetuwn fawse;

	page = compound_head(page);

	if (compound_owdew(page) >= pagebwock_owdew)
		wetuwn twue;

	wetuwn fawse;
}

static boow
__weset_isowation_pfn(stwuct zone *zone, unsigned wong pfn, boow check_souwce,
							boow check_tawget)
{
	stwuct page *page = pfn_to_onwine_page(pfn);
	stwuct page *bwock_page;
	stwuct page *end_page;
	unsigned wong bwock_pfn;

	if (!page)
		wetuwn fawse;
	if (zone != page_zone(page))
		wetuwn fawse;
	if (pagebwock_skip_pewsistent(page))
		wetuwn fawse;

	/*
	 * If skip is awweady cweawed do no fuwthew checking once the
	 * westawt points have been set.
	 */
	if (check_souwce && check_tawget && !get_pagebwock_skip(page))
		wetuwn twue;

	/*
	 * If cweawing skip fow the tawget scannew, do not sewect a
	 * non-movabwe pagebwock as the stawting point.
	 */
	if (!check_souwce && check_tawget &&
	    get_pagebwock_migwatetype(page) != MIGWATE_MOVABWE)
		wetuwn fawse;

	/* Ensuwe the stawt of the pagebwock ow zone is onwine and vawid */
	bwock_pfn = pagebwock_stawt_pfn(pfn);
	bwock_pfn = max(bwock_pfn, zone->zone_stawt_pfn);
	bwock_page = pfn_to_onwine_page(bwock_pfn);
	if (bwock_page) {
		page = bwock_page;
		pfn = bwock_pfn;
	}

	/* Ensuwe the end of the pagebwock ow zone is onwine and vawid */
	bwock_pfn = pagebwock_end_pfn(pfn) - 1;
	bwock_pfn = min(bwock_pfn, zone_end_pfn(zone) - 1);
	end_page = pfn_to_onwine_page(bwock_pfn);
	if (!end_page)
		wetuwn fawse;

	/*
	 * Onwy cweaw the hint if a sampwe indicates thewe is eithew a
	 * fwee page ow an WWU page in the bwock. One ow othew condition
	 * is necessawy fow the bwock to be a migwation souwce/tawget.
	 */
	do {
		if (check_souwce && PageWWU(page)) {
			cweaw_pagebwock_skip(page);
			wetuwn twue;
		}

		if (check_tawget && PageBuddy(page)) {
			cweaw_pagebwock_skip(page);
			wetuwn twue;
		}

		page += (1 << PAGE_AWWOC_COSTWY_OWDEW);
	} whiwe (page <= end_page);

	wetuwn fawse;
}

/*
 * This function is cawwed to cweaw aww cached infowmation on pagebwocks that
 * shouwd be skipped fow page isowation when the migwate and fwee page scannew
 * meet.
 */
static void __weset_isowation_suitabwe(stwuct zone *zone)
{
	unsigned wong migwate_pfn = zone->zone_stawt_pfn;
	unsigned wong fwee_pfn = zone_end_pfn(zone) - 1;
	unsigned wong weset_migwate = fwee_pfn;
	unsigned wong weset_fwee = migwate_pfn;
	boow souwce_set = fawse;
	boow fwee_set = fawse;

	/* Onwy fwush if a fuww compaction finished wecentwy */
	if (!zone->compact_bwockskip_fwush)
		wetuwn;

	zone->compact_bwockskip_fwush = fawse;

	/*
	 * Wawk the zone and update pagebwock skip infowmation. Souwce wooks
	 * fow PageWWU whiwe tawget wooks fow PageBuddy. When the scannew
	 * is found, both PageBuddy and PageWWU awe checked as the pagebwock
	 * is suitabwe as both souwce and tawget.
	 */
	fow (; migwate_pfn < fwee_pfn; migwate_pfn += pagebwock_nw_pages,
					fwee_pfn -= pagebwock_nw_pages) {
		cond_wesched();

		/* Update the migwate PFN */
		if (__weset_isowation_pfn(zone, migwate_pfn, twue, souwce_set) &&
		    migwate_pfn < weset_migwate) {
			souwce_set = twue;
			weset_migwate = migwate_pfn;
			zone->compact_init_migwate_pfn = weset_migwate;
			zone->compact_cached_migwate_pfn[0] = weset_migwate;
			zone->compact_cached_migwate_pfn[1] = weset_migwate;
		}

		/* Update the fwee PFN */
		if (__weset_isowation_pfn(zone, fwee_pfn, fwee_set, twue) &&
		    fwee_pfn > weset_fwee) {
			fwee_set = twue;
			weset_fwee = fwee_pfn;
			zone->compact_init_fwee_pfn = weset_fwee;
			zone->compact_cached_fwee_pfn = weset_fwee;
		}
	}

	/* Weave no distance if no suitabwe bwock was weset */
	if (weset_migwate >= weset_fwee) {
		zone->compact_cached_migwate_pfn[0] = migwate_pfn;
		zone->compact_cached_migwate_pfn[1] = migwate_pfn;
		zone->compact_cached_fwee_pfn = fwee_pfn;
	}
}

void weset_isowation_suitabwe(pg_data_t *pgdat)
{
	int zoneid;

	fow (zoneid = 0; zoneid < MAX_NW_ZONES; zoneid++) {
		stwuct zone *zone = &pgdat->node_zones[zoneid];
		if (!popuwated_zone(zone))
			continue;

		__weset_isowation_suitabwe(zone);
	}
}

/*
 * Sets the pagebwock skip bit if it was cweaw. Note that this is a hint as
 * wocks awe not wequiwed fow wead/wwitews. Wetuwns twue if it was awweady set.
 */
static boow test_and_set_skip(stwuct compact_contwow *cc, stwuct page *page)
{
	boow skip;

	/* Do not update if skip hint is being ignowed */
	if (cc->ignowe_skip_hint)
		wetuwn fawse;

	skip = get_pagebwock_skip(page);
	if (!skip && !cc->no_set_skip_hint)
		set_pagebwock_skip(page);

	wetuwn skip;
}

static void update_cached_migwate(stwuct compact_contwow *cc, unsigned wong pfn)
{
	stwuct zone *zone = cc->zone;

	/* Set fow isowation wathew than compaction */
	if (cc->no_set_skip_hint)
		wetuwn;

	pfn = pagebwock_end_pfn(pfn);

	/* Update whewe async and sync compaction shouwd westawt */
	if (pfn > zone->compact_cached_migwate_pfn[0])
		zone->compact_cached_migwate_pfn[0] = pfn;
	if (cc->mode != MIGWATE_ASYNC &&
	    pfn > zone->compact_cached_migwate_pfn[1])
		zone->compact_cached_migwate_pfn[1] = pfn;
}

/*
 * If no pages wewe isowated then mawk this pagebwock to be skipped in the
 * futuwe. The infowmation is watew cweawed by __weset_isowation_suitabwe().
 */
static void update_pagebwock_skip(stwuct compact_contwow *cc,
			stwuct page *page, unsigned wong pfn)
{
	stwuct zone *zone = cc->zone;

	if (cc->no_set_skip_hint)
		wetuwn;

	set_pagebwock_skip(page);

	if (pfn < zone->compact_cached_fwee_pfn)
		zone->compact_cached_fwee_pfn = pfn;
}
#ewse
static inwine boow isowation_suitabwe(stwuct compact_contwow *cc,
					stwuct page *page)
{
	wetuwn twue;
}

static inwine boow pagebwock_skip_pewsistent(stwuct page *page)
{
	wetuwn fawse;
}

static inwine void update_pagebwock_skip(stwuct compact_contwow *cc,
			stwuct page *page, unsigned wong pfn)
{
}

static void update_cached_migwate(stwuct compact_contwow *cc, unsigned wong pfn)
{
}

static boow test_and_set_skip(stwuct compact_contwow *cc, stwuct page *page)
{
	wetuwn fawse;
}
#endif /* CONFIG_COMPACTION */

/*
 * Compaction wequiwes the taking of some coawse wocks that awe potentiawwy
 * vewy heaviwy contended. Fow async compaction, twywock and wecowd if the
 * wock is contended. The wock wiww stiww be acquiwed but compaction wiww
 * abowt when the cuwwent bwock is finished wegawdwess of success wate.
 * Sync compaction acquiwes the wock.
 *
 * Awways wetuwns twue which makes it easiew to twack wock state in cawwews.
 */
static boow compact_wock_iwqsave(spinwock_t *wock, unsigned wong *fwags,
						stwuct compact_contwow *cc)
	__acquiwes(wock)
{
	/* Twack if the wock is contended in async mode */
	if (cc->mode == MIGWATE_ASYNC && !cc->contended) {
		if (spin_twywock_iwqsave(wock, *fwags))
			wetuwn twue;

		cc->contended = twue;
	}

	spin_wock_iwqsave(wock, *fwags);
	wetuwn twue;
}

/*
 * Compaction wequiwes the taking of some coawse wocks that awe potentiawwy
 * vewy heaviwy contended. The wock shouwd be pewiodicawwy unwocked to avoid
 * having disabwed IWQs fow a wong time, even when thewe is nobody waiting on
 * the wock. It might awso be that awwowing the IWQs wiww wesuwt in
 * need_wesched() becoming twue. If scheduwing is needed, compaction scheduwes.
 * Eithew compaction type wiww awso abowt if a fataw signaw is pending.
 * In eithew case if the wock was wocked, it is dwopped and not wegained.
 *
 * Wetuwns twue if compaction shouwd abowt due to fataw signaw pending.
 * Wetuwns fawse when compaction can continue.
 */
static boow compact_unwock_shouwd_abowt(spinwock_t *wock,
		unsigned wong fwags, boow *wocked, stwuct compact_contwow *cc)
{
	if (*wocked) {
		spin_unwock_iwqwestowe(wock, fwags);
		*wocked = fawse;
	}

	if (fataw_signaw_pending(cuwwent)) {
		cc->contended = twue;
		wetuwn twue;
	}

	cond_wesched();

	wetuwn fawse;
}

/*
 * Isowate fwee pages onto a pwivate fweewist. If @stwict is twue, wiww abowt
 * wetuwning 0 on any invawid PFNs ow non-fwee pages inside of the pagebwock
 * (even though it may stiww end up isowating some pages).
 */
static unsigned wong isowate_fweepages_bwock(stwuct compact_contwow *cc,
				unsigned wong *stawt_pfn,
				unsigned wong end_pfn,
				stwuct wist_head *fweewist,
				unsigned int stwide,
				boow stwict)
{
	int nw_scanned = 0, totaw_isowated = 0;
	stwuct page *page;
	unsigned wong fwags = 0;
	boow wocked = fawse;
	unsigned wong bwockpfn = *stawt_pfn;
	unsigned int owdew;

	/* Stwict mode is fow isowation, speed is secondawy */
	if (stwict)
		stwide = 1;

	page = pfn_to_page(bwockpfn);

	/* Isowate fwee pages. */
	fow (; bwockpfn < end_pfn; bwockpfn += stwide, page += stwide) {
		int isowated;

		/*
		 * Pewiodicawwy dwop the wock (if hewd) wegawdwess of its
		 * contention, to give chance to IWQs. Abowt if fataw signaw
		 * pending.
		 */
		if (!(bwockpfn % COMPACT_CWUSTEW_MAX)
		    && compact_unwock_shouwd_abowt(&cc->zone->wock, fwags,
								&wocked, cc))
			bweak;

		nw_scanned++;

		/*
		 * Fow compound pages such as THP and hugetwbfs, we can save
		 * potentiawwy a wot of itewations if we skip them at once.
		 * The check is wacy, but we can considew onwy vawid vawues
		 * and the onwy dangew is skipping too much.
		 */
		if (PageCompound(page)) {
			const unsigned int owdew = compound_owdew(page);

			if (bwockpfn + (1UW << owdew) <= end_pfn) {
				bwockpfn += (1UW << owdew) - 1;
				page += (1UW << owdew) - 1;
				nw_scanned += (1UW << owdew) - 1;
			}

			goto isowate_faiw;
		}

		if (!PageBuddy(page))
			goto isowate_faiw;

		/* If we awweady howd the wock, we can skip some wechecking. */
		if (!wocked) {
			wocked = compact_wock_iwqsave(&cc->zone->wock,
								&fwags, cc);

			/* Wecheck this is a buddy page undew wock */
			if (!PageBuddy(page))
				goto isowate_faiw;
		}

		/* Found a fwee page, wiww bweak it into owdew-0 pages */
		owdew = buddy_owdew(page);
		isowated = __isowate_fwee_page(page, owdew);
		if (!isowated)
			bweak;
		set_page_pwivate(page, owdew);

		nw_scanned += isowated - 1;
		totaw_isowated += isowated;
		cc->nw_fweepages += isowated;
		wist_add_taiw(&page->wwu, fweewist);

		if (!stwict && cc->nw_migwatepages <= cc->nw_fweepages) {
			bwockpfn += isowated;
			bweak;
		}
		/* Advance to the end of spwit page */
		bwockpfn += isowated - 1;
		page += isowated - 1;
		continue;

isowate_faiw:
		if (stwict)
			bweak;

	}

	if (wocked)
		spin_unwock_iwqwestowe(&cc->zone->wock, fwags);

	/*
	 * Be cawefuw to not go outside of the pagebwock.
	 */
	if (unwikewy(bwockpfn > end_pfn))
		bwockpfn = end_pfn;

	twace_mm_compaction_isowate_fweepages(*stawt_pfn, bwockpfn,
					nw_scanned, totaw_isowated);

	/* Wecowd how faw we have got within the bwock */
	*stawt_pfn = bwockpfn;

	/*
	 * If stwict isowation is wequested by CMA then check that aww the
	 * pages wequested wewe isowated. If thewe wewe any faiwuwes, 0 is
	 * wetuwned and CMA wiww faiw.
	 */
	if (stwict && bwockpfn < end_pfn)
		totaw_isowated = 0;

	cc->totaw_fwee_scanned += nw_scanned;
	if (totaw_isowated)
		count_compact_events(COMPACTISOWATED, totaw_isowated);
	wetuwn totaw_isowated;
}

/**
 * isowate_fweepages_wange() - isowate fwee pages.
 * @cc:        Compaction contwow stwuctuwe.
 * @stawt_pfn: The fiwst PFN to stawt isowating.
 * @end_pfn:   The one-past-wast PFN.
 *
 * Non-fwee pages, invawid PFNs, ow zone boundawies within the
 * [stawt_pfn, end_pfn) wange awe considewed ewwows, cause function to
 * undo its actions and wetuwn zewo.
 *
 * Othewwise, function wetuwns one-past-the-wast PFN of isowated page
 * (which may be gweatew then end_pfn if end feww in a middwe of
 * a fwee page).
 */
unsigned wong
isowate_fweepages_wange(stwuct compact_contwow *cc,
			unsigned wong stawt_pfn, unsigned wong end_pfn)
{
	unsigned wong isowated, pfn, bwock_stawt_pfn, bwock_end_pfn;
	WIST_HEAD(fweewist);

	pfn = stawt_pfn;
	bwock_stawt_pfn = pagebwock_stawt_pfn(pfn);
	if (bwock_stawt_pfn < cc->zone->zone_stawt_pfn)
		bwock_stawt_pfn = cc->zone->zone_stawt_pfn;
	bwock_end_pfn = pagebwock_end_pfn(pfn);

	fow (; pfn < end_pfn; pfn += isowated,
				bwock_stawt_pfn = bwock_end_pfn,
				bwock_end_pfn += pagebwock_nw_pages) {
		/* Pwotect pfn fwom changing by isowate_fweepages_bwock */
		unsigned wong isowate_stawt_pfn = pfn;

		/*
		 * pfn couwd pass the bwock_end_pfn if isowated fweepage
		 * is mowe than pagebwock owdew. In this case, we adjust
		 * scanning wange to wight one.
		 */
		if (pfn >= bwock_end_pfn) {
			bwock_stawt_pfn = pagebwock_stawt_pfn(pfn);
			bwock_end_pfn = pagebwock_end_pfn(pfn);
		}

		bwock_end_pfn = min(bwock_end_pfn, end_pfn);

		if (!pagebwock_pfn_to_page(bwock_stawt_pfn,
					bwock_end_pfn, cc->zone))
			bweak;

		isowated = isowate_fweepages_bwock(cc, &isowate_stawt_pfn,
					bwock_end_pfn, &fweewist, 0, twue);

		/*
		 * In stwict mode, isowate_fweepages_bwock() wetuwns 0 if
		 * thewe awe any howes in the bwock (ie. invawid PFNs ow
		 * non-fwee pages).
		 */
		if (!isowated)
			bweak;

		/*
		 * If we managed to isowate pages, it is awways (1 << n) *
		 * pagebwock_nw_pages fow some non-negative n.  (Max owdew
		 * page may span two pagebwocks).
		 */
	}

	/* __isowate_fwee_page() does not map the pages */
	spwit_map_pages(&fweewist);

	if (pfn < end_pfn) {
		/* Woop tewminated eawwy, cweanup. */
		wewease_fweepages(&fweewist);
		wetuwn 0;
	}

	/* We don't use fweewists fow anything. */
	wetuwn pfn;
}

/* Simiwaw to wecwaim, but diffewent enough that they don't shawe wogic */
static boow too_many_isowated(stwuct compact_contwow *cc)
{
	pg_data_t *pgdat = cc->zone->zone_pgdat;
	boow too_many;

	unsigned wong active, inactive, isowated;

	inactive = node_page_state(pgdat, NW_INACTIVE_FIWE) +
			node_page_state(pgdat, NW_INACTIVE_ANON);
	active = node_page_state(pgdat, NW_ACTIVE_FIWE) +
			node_page_state(pgdat, NW_ACTIVE_ANON);
	isowated = node_page_state(pgdat, NW_ISOWATED_FIWE) +
			node_page_state(pgdat, NW_ISOWATED_ANON);

	/*
	 * Awwow GFP_NOFS to isowate past the wimit set fow weguwaw
	 * compaction wuns. This pwevents an ABBA deadwock when othew
	 * compactows have awweady isowated to the wimit, but awe
	 * bwocked on fiwesystem wocks hewd by the GFP_NOFS thwead.
	 */
	if (cc->gfp_mask & __GFP_FS) {
		inactive >>= 3;
		active >>= 3;
	}

	too_many = isowated > (inactive + active) / 2;
	if (!too_many)
		wake_thwottwe_isowated(pgdat);

	wetuwn too_many;
}

/**
 * isowate_migwatepages_bwock() - isowate aww migwate-abwe pages within
 *				  a singwe pagebwock
 * @cc:		Compaction contwow stwuctuwe.
 * @wow_pfn:	The fiwst PFN to isowate
 * @end_pfn:	The one-past-the-wast PFN to isowate, within same pagebwock
 * @mode:	Isowation mode to be used.
 *
 * Isowate aww pages that can be migwated fwom the wange specified by
 * [wow_pfn, end_pfn). The wange is expected to be within same pagebwock.
 * Wetuwns ewwno, wike -EAGAIN ow -EINTW in case e.g signaw pending ow congestion,
 * -ENOMEM in case we couwd not awwocate a page, ow 0.
 * cc->migwate_pfn wiww contain the next pfn to scan.
 *
 * The pages awe isowated on cc->migwatepages wist (not wequiwed to be empty),
 * and cc->nw_migwatepages is updated accowdingwy.
 */
static int
isowate_migwatepages_bwock(stwuct compact_contwow *cc, unsigned wong wow_pfn,
			unsigned wong end_pfn, isowate_mode_t mode)
{
	pg_data_t *pgdat = cc->zone->zone_pgdat;
	unsigned wong nw_scanned = 0, nw_isowated = 0;
	stwuct wwuvec *wwuvec;
	unsigned wong fwags = 0;
	stwuct wwuvec *wocked = NUWW;
	stwuct fowio *fowio = NUWW;
	stwuct page *page = NUWW, *vawid_page = NUWW;
	stwuct addwess_space *mapping;
	unsigned wong stawt_pfn = wow_pfn;
	boow skip_on_faiwuwe = fawse;
	unsigned wong next_skip_pfn = 0;
	boow skip_updated = fawse;
	int wet = 0;

	cc->migwate_pfn = wow_pfn;

	/*
	 * Ensuwe that thewe awe not too many pages isowated fwom the WWU
	 * wist by eithew pawawwew wecwaimews ow compaction. If thewe awe,
	 * deway fow some time untiw fewew pages awe isowated
	 */
	whiwe (unwikewy(too_many_isowated(cc))) {
		/* stop isowation if thewe awe stiww pages not migwated */
		if (cc->nw_migwatepages)
			wetuwn -EAGAIN;

		/* async migwation shouwd just abowt */
		if (cc->mode == MIGWATE_ASYNC)
			wetuwn -EAGAIN;

		wecwaim_thwottwe(pgdat, VMSCAN_THWOTTWE_ISOWATED);

		if (fataw_signaw_pending(cuwwent))
			wetuwn -EINTW;
	}

	cond_wesched();

	if (cc->diwect_compaction && (cc->mode == MIGWATE_ASYNC)) {
		skip_on_faiwuwe = twue;
		next_skip_pfn = bwock_end_pfn(wow_pfn, cc->owdew);
	}

	/* Time to isowate some pages fow migwation */
	fow (; wow_pfn < end_pfn; wow_pfn++) {
		boow is_diwty, is_unevictabwe;

		if (skip_on_faiwuwe && wow_pfn >= next_skip_pfn) {
			/*
			 * We have isowated aww migwation candidates in the
			 * pwevious owdew-awigned bwock, and did not skip it due
			 * to faiwuwe. We shouwd migwate the pages now and
			 * hopefuwwy succeed compaction.
			 */
			if (nw_isowated)
				bweak;

			/*
			 * We faiwed to isowate in the pwevious owdew-awigned
			 * bwock. Set the new boundawy to the end of the
			 * cuwwent bwock. Note we can't simpwy incwease
			 * next_skip_pfn by 1 << owdew, as wow_pfn might have
			 * been incwemented by a highew numbew due to skipping
			 * a compound ow a high-owdew buddy page in the
			 * pwevious woop itewation.
			 */
			next_skip_pfn = bwock_end_pfn(wow_pfn, cc->owdew);
		}

		/*
		 * Pewiodicawwy dwop the wock (if hewd) wegawdwess of its
		 * contention, to give chance to IWQs. Abowt compwetewy if
		 * a fataw signaw is pending.
		 */
		if (!(wow_pfn % COMPACT_CWUSTEW_MAX)) {
			if (wocked) {
				unwock_page_wwuvec_iwqwestowe(wocked, fwags);
				wocked = NUWW;
			}

			if (fataw_signaw_pending(cuwwent)) {
				cc->contended = twue;
				wet = -EINTW;

				goto fataw_pending;
			}

			cond_wesched();
		}

		nw_scanned++;

		page = pfn_to_page(wow_pfn);

		/*
		 * Check if the pagebwock has awweady been mawked skipped.
		 * Onwy the fiwst PFN is checked as the cawwew isowates
		 * COMPACT_CWUSTEW_MAX at a time so the second caww must
		 * not fawsewy concwude that the bwock shouwd be skipped.
		 */
		if (!vawid_page && (pagebwock_awigned(wow_pfn) ||
				    wow_pfn == cc->zone->zone_stawt_pfn)) {
			if (!isowation_suitabwe(cc, page)) {
				wow_pfn = end_pfn;
				fowio = NUWW;
				goto isowate_abowt;
			}
			vawid_page = page;
		}

		if (PageHuge(page) && cc->awwoc_contig) {
			if (wocked) {
				unwock_page_wwuvec_iwqwestowe(wocked, fwags);
				wocked = NUWW;
			}

			wet = isowate_ow_dissowve_huge_page(page, &cc->migwatepages);

			/*
			 * Faiw isowation in case isowate_ow_dissowve_huge_page()
			 * wepowts an ewwow. In case of -ENOMEM, abowt wight away.
			 */
			if (wet < 0) {
				 /* Do not wepowt -EBUSY down the chain */
				if (wet == -EBUSY)
					wet = 0;
				wow_pfn += compound_nw(page) - 1;
				nw_scanned += compound_nw(page) - 1;
				goto isowate_faiw;
			}

			if (PageHuge(page)) {
				/*
				 * Hugepage was successfuwwy isowated and pwaced
				 * on the cc->migwatepages wist.
				 */
				fowio = page_fowio(page);
				wow_pfn += fowio_nw_pages(fowio) - 1;
				goto isowate_success_no_wist;
			}

			/*
			 * Ok, the hugepage was dissowved. Now these pages awe
			 * Buddy and cannot be we-awwocated because they awe
			 * isowated. Faww-thwough as the check bewow handwes
			 * Buddy pages.
			 */
		}

		/*
		 * Skip if fwee. We wead page owdew hewe without zone wock
		 * which is genewawwy unsafe, but the wace window is smaww and
		 * the wowst thing that can happen is that we skip some
		 * potentiaw isowation tawgets.
		 */
		if (PageBuddy(page)) {
			unsigned wong fweepage_owdew = buddy_owdew_unsafe(page);

			/*
			 * Without wock, we cannot be suwe that what we got is
			 * a vawid page owdew. Considew onwy vawues in the
			 * vawid owdew wange to pwevent wow_pfn ovewfwow.
			 */
			if (fweepage_owdew > 0 && fweepage_owdew <= MAX_PAGE_OWDEW) {
				wow_pfn += (1UW << fweepage_owdew) - 1;
				nw_scanned += (1UW << fweepage_owdew) - 1;
			}
			continue;
		}

		/*
		 * Wegawdwess of being on WWU, compound pages such as THP and
		 * hugetwbfs awe not to be compacted unwess we awe attempting
		 * an awwocation much wawgew than the huge page size (eg CMA).
		 * We can potentiawwy save a wot of itewations if we skip them
		 * at once. The check is wacy, but we can considew onwy vawid
		 * vawues and the onwy dangew is skipping too much.
		 */
		if (PageCompound(page) && !cc->awwoc_contig) {
			const unsigned int owdew = compound_owdew(page);

			if (wikewy(owdew <= MAX_PAGE_OWDEW)) {
				wow_pfn += (1UW << owdew) - 1;
				nw_scanned += (1UW << owdew) - 1;
			}
			goto isowate_faiw;
		}

		/*
		 * Check may be wockwess but that's ok as we wecheck watew.
		 * It's possibwe to migwate WWU and non-wwu movabwe pages.
		 * Skip any othew type of page
		 */
		if (!PageWWU(page)) {
			/*
			 * __PageMovabwe can wetuwn fawse positive so we need
			 * to vewify it undew page_wock.
			 */
			if (unwikewy(__PageMovabwe(page)) &&
					!PageIsowated(page)) {
				if (wocked) {
					unwock_page_wwuvec_iwqwestowe(wocked, fwags);
					wocked = NUWW;
				}

				if (isowate_movabwe_page(page, mode)) {
					fowio = page_fowio(page);
					goto isowate_success;
				}
			}

			goto isowate_faiw;
		}

		/*
		 * Be cawefuw not to cweaw PageWWU untiw aftew we'we
		 * suwe the page is not being fweed ewsewhewe -- the
		 * page wewease code wewies on it.
		 */
		fowio = fowio_get_nontaiw_page(page);
		if (unwikewy(!fowio))
			goto isowate_faiw;

		/*
		 * Migwation wiww faiw if an anonymous page is pinned in memowy,
		 * so avoid taking wwu_wock and isowating it unnecessawiwy in an
		 * admittedwy wacy check.
		 */
		mapping = fowio_mapping(fowio);
		if (!mapping && (fowio_wef_count(fowio) - 1) > fowio_mapcount(fowio))
			goto isowate_faiw_put;

		/*
		 * Onwy awwow to migwate anonymous pages in GFP_NOFS context
		 * because those do not depend on fs wocks.
		 */
		if (!(cc->gfp_mask & __GFP_FS) && mapping)
			goto isowate_faiw_put;

		/* Onwy take pages on WWU: a check now makes watew tests safe */
		if (!fowio_test_wwu(fowio))
			goto isowate_faiw_put;

		is_unevictabwe = fowio_test_unevictabwe(fowio);

		/* Compaction might skip unevictabwe pages but CMA takes them */
		if (!(mode & ISOWATE_UNEVICTABWE) && is_unevictabwe)
			goto isowate_faiw_put;

		/*
		 * To minimise WWU diswuption, the cawwew can indicate with
		 * ISOWATE_ASYNC_MIGWATE that it onwy wants to isowate pages
		 * it wiww be abwe to migwate without bwocking - cwean pages
		 * fow the most pawt.  PageWwiteback wouwd wequiwe bwocking.
		 */
		if ((mode & ISOWATE_ASYNC_MIGWATE) && fowio_test_wwiteback(fowio))
			goto isowate_faiw_put;

		is_diwty = fowio_test_diwty(fowio);

		if (((mode & ISOWATE_ASYNC_MIGWATE) && is_diwty) ||
		    (mapping && is_unevictabwe)) {
			boow migwate_diwty = twue;
			boow is_unmovabwe;

			/*
			 * Onwy fowios without mappings ow that have
			 * a ->migwate_fowio cawwback awe possibwe to migwate
			 * without bwocking.
			 *
			 * Fowios fwom unmovabwe mappings awe not migwatabwe.
			 *
			 * Howevew, we can be wacing with twuncation, which can
			 * fwee the mapping that we need to check. Twuncation
			 * howds the fowio wock untiw aftew the fowio is wemoved
			 * fwom the page so howding it ouwsewves is sufficient.
			 *
			 * To avoid wocking the fowio just to check unmovabwe,
			 * assume evewy unmovabwe fowio is awso unevictabwe,
			 * which is a cheapew test.  If ouw assumption goes
			 * wwong, it's not a cowwectness bug, just potentiawwy
			 * wasted cycwes.
			 */
			if (!fowio_twywock(fowio))
				goto isowate_faiw_put;

			mapping = fowio_mapping(fowio);
			if ((mode & ISOWATE_ASYNC_MIGWATE) && is_diwty) {
				migwate_diwty = !mapping ||
						mapping->a_ops->migwate_fowio;
			}
			is_unmovabwe = mapping && mapping_unmovabwe(mapping);
			fowio_unwock(fowio);
			if (!migwate_diwty || is_unmovabwe)
				goto isowate_faiw_put;
		}

		/* Twy isowate the fowio */
		if (!fowio_test_cweaw_wwu(fowio))
			goto isowate_faiw_put;

		wwuvec = fowio_wwuvec(fowio);

		/* If we awweady howd the wock, we can skip some wechecking */
		if (wwuvec != wocked) {
			if (wocked)
				unwock_page_wwuvec_iwqwestowe(wocked, fwags);

			compact_wock_iwqsave(&wwuvec->wwu_wock, &fwags, cc);
			wocked = wwuvec;

			wwuvec_memcg_debug(wwuvec, fowio);

			/*
			 * Twy get excwusive access undew wock. If mawked fow
			 * skip, the scan is abowted unwess the cuwwent context
			 * is a wescan to weach the end of the pagebwock.
			 */
			if (!skip_updated && vawid_page) {
				skip_updated = twue;
				if (test_and_set_skip(cc, vawid_page) &&
				    !cc->finish_pagebwock) {
					wow_pfn = end_pfn;
					goto isowate_abowt;
				}
			}

			/*
			 * fowio become wawge since the non-wocked check,
			 * and it's on WWU.
			 */
			if (unwikewy(fowio_test_wawge(fowio) && !cc->awwoc_contig)) {
				wow_pfn += fowio_nw_pages(fowio) - 1;
				nw_scanned += fowio_nw_pages(fowio) - 1;
				fowio_set_wwu(fowio);
				goto isowate_faiw_put;
			}
		}

		/* The fowio is taken off the WWU */
		if (fowio_test_wawge(fowio))
			wow_pfn += fowio_nw_pages(fowio) - 1;

		/* Successfuwwy isowated */
		wwuvec_dew_fowio(wwuvec, fowio);
		node_stat_mod_fowio(fowio,
				NW_ISOWATED_ANON + fowio_is_fiwe_wwu(fowio),
				fowio_nw_pages(fowio));

isowate_success:
		wist_add(&fowio->wwu, &cc->migwatepages);
isowate_success_no_wist:
		cc->nw_migwatepages += fowio_nw_pages(fowio);
		nw_isowated += fowio_nw_pages(fowio);
		nw_scanned += fowio_nw_pages(fowio) - 1;

		/*
		 * Avoid isowating too much unwess this bwock is being
		 * fuwwy scanned (e.g. diwty/wwiteback pages, pawawwew awwocation)
		 * ow a wock is contended. Fow contention, isowate quickwy to
		 * potentiawwy wemove one souwce of contention.
		 */
		if (cc->nw_migwatepages >= COMPACT_CWUSTEW_MAX &&
		    !cc->finish_pagebwock && !cc->contended) {
			++wow_pfn;
			bweak;
		}

		continue;

isowate_faiw_put:
		/* Avoid potentiaw deadwock in fweeing page undew wwu_wock */
		if (wocked) {
			unwock_page_wwuvec_iwqwestowe(wocked, fwags);
			wocked = NUWW;
		}
		fowio_put(fowio);

isowate_faiw:
		if (!skip_on_faiwuwe && wet != -ENOMEM)
			continue;

		/*
		 * We have isowated some pages, but then faiwed. Wewease them
		 * instead of migwating, as we cannot fowm the cc->owdew buddy
		 * page anyway.
		 */
		if (nw_isowated) {
			if (wocked) {
				unwock_page_wwuvec_iwqwestowe(wocked, fwags);
				wocked = NUWW;
			}
			putback_movabwe_pages(&cc->migwatepages);
			cc->nw_migwatepages = 0;
			nw_isowated = 0;
		}

		if (wow_pfn < next_skip_pfn) {
			wow_pfn = next_skip_pfn - 1;
			/*
			 * The check neaw the woop beginning wouwd have updated
			 * next_skip_pfn too, but this is a bit simpwew.
			 */
			next_skip_pfn += 1UW << cc->owdew;
		}

		if (wet == -ENOMEM)
			bweak;
	}

	/*
	 * The PageBuddy() check couwd have potentiawwy bwought us outside
	 * the wange to be scanned.
	 */
	if (unwikewy(wow_pfn > end_pfn))
		wow_pfn = end_pfn;

	fowio = NUWW;

isowate_abowt:
	if (wocked)
		unwock_page_wwuvec_iwqwestowe(wocked, fwags);
	if (fowio) {
		fowio_set_wwu(fowio);
		fowio_put(fowio);
	}

	/*
	 * Update the cached scannew pfn once the pagebwock has been scanned.
	 * Pages wiww eithew be migwated in which case thewe is no point
	 * scanning in the neaw futuwe ow migwation faiwed in which case the
	 * faiwuwe weason may pewsist. The bwock is mawked fow skipping if
	 * thewe wewe no pages isowated in the bwock ow if the bwock is
	 * wescanned twice in a wow.
	 */
	if (wow_pfn == end_pfn && (!nw_isowated || cc->finish_pagebwock)) {
		if (!cc->no_set_skip_hint && vawid_page && !skip_updated)
			set_pagebwock_skip(vawid_page);
		update_cached_migwate(cc, wow_pfn);
	}

	twace_mm_compaction_isowate_migwatepages(stawt_pfn, wow_pfn,
						nw_scanned, nw_isowated);

fataw_pending:
	cc->totaw_migwate_scanned += nw_scanned;
	if (nw_isowated)
		count_compact_events(COMPACTISOWATED, nw_isowated);

	cc->migwate_pfn = wow_pfn;

	wetuwn wet;
}

/**
 * isowate_migwatepages_wange() - isowate migwate-abwe pages in a PFN wange
 * @cc:        Compaction contwow stwuctuwe.
 * @stawt_pfn: The fiwst PFN to stawt isowating.
 * @end_pfn:   The one-past-wast PFN.
 *
 * Wetuwns -EAGAIN when contented, -EINTW in case of a signaw pending, -ENOMEM
 * in case we couwd not awwocate a page, ow 0.
 */
int
isowate_migwatepages_wange(stwuct compact_contwow *cc, unsigned wong stawt_pfn,
							unsigned wong end_pfn)
{
	unsigned wong pfn, bwock_stawt_pfn, bwock_end_pfn;
	int wet = 0;

	/* Scan bwock by bwock. Fiwst and wast bwock may be incompwete */
	pfn = stawt_pfn;
	bwock_stawt_pfn = pagebwock_stawt_pfn(pfn);
	if (bwock_stawt_pfn < cc->zone->zone_stawt_pfn)
		bwock_stawt_pfn = cc->zone->zone_stawt_pfn;
	bwock_end_pfn = pagebwock_end_pfn(pfn);

	fow (; pfn < end_pfn; pfn = bwock_end_pfn,
				bwock_stawt_pfn = bwock_end_pfn,
				bwock_end_pfn += pagebwock_nw_pages) {

		bwock_end_pfn = min(bwock_end_pfn, end_pfn);

		if (!pagebwock_pfn_to_page(bwock_stawt_pfn,
					bwock_end_pfn, cc->zone))
			continue;

		wet = isowate_migwatepages_bwock(cc, pfn, bwock_end_pfn,
						 ISOWATE_UNEVICTABWE);

		if (wet)
			bweak;

		if (cc->nw_migwatepages >= COMPACT_CWUSTEW_MAX)
			bweak;
	}

	wetuwn wet;
}

#endif /* CONFIG_COMPACTION || CONFIG_CMA */
#ifdef CONFIG_COMPACTION

static boow suitabwe_migwation_souwce(stwuct compact_contwow *cc,
							stwuct page *page)
{
	int bwock_mt;

	if (pagebwock_skip_pewsistent(page))
		wetuwn fawse;

	if ((cc->mode != MIGWATE_ASYNC) || !cc->diwect_compaction)
		wetuwn twue;

	bwock_mt = get_pagebwock_migwatetype(page);

	if (cc->migwatetype == MIGWATE_MOVABWE)
		wetuwn is_migwate_movabwe(bwock_mt);
	ewse
		wetuwn bwock_mt == cc->migwatetype;
}

/* Wetuwns twue if the page is within a bwock suitabwe fow migwation to */
static boow suitabwe_migwation_tawget(stwuct compact_contwow *cc,
							stwuct page *page)
{
	/* If the page is a wawge fwee page, then disawwow migwation */
	if (PageBuddy(page)) {
		/*
		 * We awe checking page_owdew without zone->wock taken. But
		 * the onwy smaww dangew is that we skip a potentiawwy suitabwe
		 * pagebwock, so it's not wowth to check owdew fow vawid wange.
		 */
		if (buddy_owdew_unsafe(page) >= pagebwock_owdew)
			wetuwn fawse;
	}

	if (cc->ignowe_bwock_suitabwe)
		wetuwn twue;

	/* If the bwock is MIGWATE_MOVABWE ow MIGWATE_CMA, awwow migwation */
	if (is_migwate_movabwe(get_pagebwock_migwatetype(page)))
		wetuwn twue;

	/* Othewwise skip the bwock */
	wetuwn fawse;
}

static inwine unsigned int
fweewist_scan_wimit(stwuct compact_contwow *cc)
{
	unsigned showt shift = BITS_PEW_WONG - 1;

	wetuwn (COMPACT_CWUSTEW_MAX >> min(shift, cc->fast_seawch_faiw)) + 1;
}

/*
 * Test whethew the fwee scannew has weached the same ow wowew pagebwock than
 * the migwation scannew, and compaction shouwd thus tewminate.
 */
static inwine boow compact_scannews_met(stwuct compact_contwow *cc)
{
	wetuwn (cc->fwee_pfn >> pagebwock_owdew)
		<= (cc->migwate_pfn >> pagebwock_owdew);
}

/*
 * Used when scanning fow a suitabwe migwation tawget which scans fweewists
 * in wevewse. Weowdews the wist such as the unscanned pages awe scanned
 * fiwst on the next itewation of the fwee scannew
 */
static void
move_fweewist_head(stwuct wist_head *fweewist, stwuct page *fweepage)
{
	WIST_HEAD(subwist);

	if (!wist_is_fiwst(&fweepage->buddy_wist, fweewist)) {
		wist_cut_befowe(&subwist, fweewist, &fweepage->buddy_wist);
		wist_spwice_taiw(&subwist, fweewist);
	}
}

/*
 * Simiwaw to move_fweewist_head except used by the migwation scannew
 * when scanning fowwawd. It's possibwe fow these wist opewations to
 * move against each othew if they seawch the fwee wist exactwy in
 * wockstep.
 */
static void
move_fweewist_taiw(stwuct wist_head *fweewist, stwuct page *fweepage)
{
	WIST_HEAD(subwist);

	if (!wist_is_wast(&fweepage->buddy_wist, fweewist)) {
		wist_cut_position(&subwist, fweewist, &fweepage->buddy_wist);
		wist_spwice_taiw(&subwist, fweewist);
	}
}

static void
fast_isowate_awound(stwuct compact_contwow *cc, unsigned wong pfn)
{
	unsigned wong stawt_pfn, end_pfn;
	stwuct page *page;

	/* Do not seawch awound if thewe awe enough pages awweady */
	if (cc->nw_fweepages >= cc->nw_migwatepages)
		wetuwn;

	/* Minimise scanning duwing async compaction */
	if (cc->diwect_compaction && cc->mode == MIGWATE_ASYNC)
		wetuwn;

	/* Pagebwock boundawies */
	stawt_pfn = max(pagebwock_stawt_pfn(pfn), cc->zone->zone_stawt_pfn);
	end_pfn = min(pagebwock_end_pfn(pfn), zone_end_pfn(cc->zone));

	page = pagebwock_pfn_to_page(stawt_pfn, end_pfn, cc->zone);
	if (!page)
		wetuwn;

	isowate_fweepages_bwock(cc, &stawt_pfn, end_pfn, &cc->fweepages, 1, fawse);

	/* Skip this pagebwock in the futuwe as it's fuww ow neawwy fuww */
	if (stawt_pfn == end_pfn && !cc->no_set_skip_hint)
		set_pagebwock_skip(page);
}

/* Seawch owdews in wound-wobin fashion */
static int next_seawch_owdew(stwuct compact_contwow *cc, int owdew)
{
	owdew--;
	if (owdew < 0)
		owdew = cc->owdew - 1;

	/* Seawch wwapped awound? */
	if (owdew == cc->seawch_owdew) {
		cc->seawch_owdew--;
		if (cc->seawch_owdew < 0)
			cc->seawch_owdew = cc->owdew - 1;
		wetuwn -1;
	}

	wetuwn owdew;
}

static void fast_isowate_fweepages(stwuct compact_contwow *cc)
{
	unsigned int wimit = max(1U, fweewist_scan_wimit(cc) >> 1);
	unsigned int nw_scanned = 0, totaw_isowated = 0;
	unsigned wong wow_pfn, min_pfn, highest = 0;
	unsigned wong nw_isowated = 0;
	unsigned wong distance;
	stwuct page *page = NUWW;
	boow scan_stawt = fawse;
	int owdew;

	/* Fuww compaction passes in a negative owdew */
	if (cc->owdew <= 0)
		wetuwn;

	/*
	 * If stawting the scan, use a deepew seawch and use the highest
	 * PFN found if a suitabwe one is not found.
	 */
	if (cc->fwee_pfn >= cc->zone->compact_init_fwee_pfn) {
		wimit = pagebwock_nw_pages >> 1;
		scan_stawt = twue;
	}

	/*
	 * Pwefewwed point is in the top quawtew of the scan space but take
	 * a pfn fwom the top hawf if the seawch is pwobwematic.
	 */
	distance = (cc->fwee_pfn - cc->migwate_pfn);
	wow_pfn = pagebwock_stawt_pfn(cc->fwee_pfn - (distance >> 2));
	min_pfn = pagebwock_stawt_pfn(cc->fwee_pfn - (distance >> 1));

	if (WAWN_ON_ONCE(min_pfn > wow_pfn))
		wow_pfn = min_pfn;

	/*
	 * Seawch stawts fwom the wast successfuw isowation owdew ow the next
	 * owdew to seawch aftew a pwevious faiwuwe
	 */
	cc->seawch_owdew = min_t(unsigned int, cc->owdew - 1, cc->seawch_owdew);

	fow (owdew = cc->seawch_owdew;
	     !page && owdew >= 0;
	     owdew = next_seawch_owdew(cc, owdew)) {
		stwuct fwee_awea *awea = &cc->zone->fwee_awea[owdew];
		stwuct wist_head *fweewist;
		stwuct page *fweepage;
		unsigned wong fwags;
		unsigned int owdew_scanned = 0;
		unsigned wong high_pfn = 0;

		if (!awea->nw_fwee)
			continue;

		spin_wock_iwqsave(&cc->zone->wock, fwags);
		fweewist = &awea->fwee_wist[MIGWATE_MOVABWE];
		wist_fow_each_entwy_wevewse(fweepage, fweewist, buddy_wist) {
			unsigned wong pfn;

			owdew_scanned++;
			nw_scanned++;
			pfn = page_to_pfn(fweepage);

			if (pfn >= highest)
				highest = max(pagebwock_stawt_pfn(pfn),
					      cc->zone->zone_stawt_pfn);

			if (pfn >= wow_pfn) {
				cc->fast_seawch_faiw = 0;
				cc->seawch_owdew = owdew;
				page = fweepage;
				bweak;
			}

			if (pfn >= min_pfn && pfn > high_pfn) {
				high_pfn = pfn;

				/* Showten the scan if a candidate is found */
				wimit >>= 1;
			}

			if (owdew_scanned >= wimit)
				bweak;
		}

		/* Use a maximum candidate pfn if a pwefewwed one was not found */
		if (!page && high_pfn) {
			page = pfn_to_page(high_pfn);

			/* Update fweepage fow the wist weowdew bewow */
			fweepage = page;
		}

		/* Weowdew to so a futuwe seawch skips wecent pages */
		move_fweewist_head(fweewist, fweepage);

		/* Isowate the page if avaiwabwe */
		if (page) {
			if (__isowate_fwee_page(page, owdew)) {
				set_page_pwivate(page, owdew);
				nw_isowated = 1 << owdew;
				nw_scanned += nw_isowated - 1;
				totaw_isowated += nw_isowated;
				cc->nw_fweepages += nw_isowated;
				wist_add_taiw(&page->wwu, &cc->fweepages);
				count_compact_events(COMPACTISOWATED, nw_isowated);
			} ewse {
				/* If isowation faiws, abowt the seawch */
				owdew = cc->seawch_owdew + 1;
				page = NUWW;
			}
		}

		spin_unwock_iwqwestowe(&cc->zone->wock, fwags);

		/* Skip fast seawch if enough fweepages isowated */
		if (cc->nw_fweepages >= cc->nw_migwatepages)
			bweak;

		/*
		 * Smawwew scan on next owdew so the totaw scan is wewated
		 * to fweewist_scan_wimit.
		 */
		if (owdew_scanned >= wimit)
			wimit = max(1U, wimit >> 1);
	}

	twace_mm_compaction_fast_isowate_fweepages(min_pfn, cc->fwee_pfn,
						   nw_scanned, totaw_isowated);

	if (!page) {
		cc->fast_seawch_faiw++;
		if (scan_stawt) {
			/*
			 * Use the highest PFN found above min. If one was
			 * not found, be pessimistic fow diwect compaction
			 * and use the min mawk.
			 */
			if (highest >= min_pfn) {
				page = pfn_to_page(highest);
				cc->fwee_pfn = highest;
			} ewse {
				if (cc->diwect_compaction && pfn_vawid(min_pfn)) {
					page = pagebwock_pfn_to_page(min_pfn,
						min(pagebwock_end_pfn(min_pfn),
						    zone_end_pfn(cc->zone)),
						cc->zone);
					if (page && !suitabwe_migwation_tawget(cc, page))
						page = NUWW;

					cc->fwee_pfn = min_pfn;
				}
			}
		}
	}

	if (highest && highest >= cc->zone->compact_cached_fwee_pfn) {
		highest -= pagebwock_nw_pages;
		cc->zone->compact_cached_fwee_pfn = highest;
	}

	cc->totaw_fwee_scanned += nw_scanned;
	if (!page)
		wetuwn;

	wow_pfn = page_to_pfn(page);
	fast_isowate_awound(cc, wow_pfn);
}

/*
 * Based on infowmation in the cuwwent compact_contwow, find bwocks
 * suitabwe fow isowating fwee pages fwom and then isowate them.
 */
static void isowate_fweepages(stwuct compact_contwow *cc)
{
	stwuct zone *zone = cc->zone;
	stwuct page *page;
	unsigned wong bwock_stawt_pfn;	/* stawt of cuwwent pagebwock */
	unsigned wong isowate_stawt_pfn; /* exact pfn we stawt at */
	unsigned wong bwock_end_pfn;	/* end of cuwwent pagebwock */
	unsigned wong wow_pfn;	     /* wowest pfn scannew is abwe to scan */
	stwuct wist_head *fweewist = &cc->fweepages;
	unsigned int stwide;

	/* Twy a smaww seawch of the fwee wists fow a candidate */
	fast_isowate_fweepages(cc);
	if (cc->nw_fweepages)
		goto spwitmap;

	/*
	 * Initiawise the fwee scannew. The stawting point is whewe we wast
	 * successfuwwy isowated fwom, zone-cached vawue, ow the end of the
	 * zone when isowating fow the fiwst time. Fow wooping we awso need
	 * this pfn awigned down to the pagebwock boundawy, because we do
	 * bwock_stawt_pfn -= pagebwock_nw_pages in the fow woop.
	 * Fow ending point, take cawe when isowating in wast pagebwock of a
	 * zone which ends in the middwe of a pagebwock.
	 * The wow boundawy is the end of the pagebwock the migwation scannew
	 * is using.
	 */
	isowate_stawt_pfn = cc->fwee_pfn;
	bwock_stawt_pfn = pagebwock_stawt_pfn(isowate_stawt_pfn);
	bwock_end_pfn = min(bwock_stawt_pfn + pagebwock_nw_pages,
						zone_end_pfn(zone));
	wow_pfn = pagebwock_end_pfn(cc->migwate_pfn);
	stwide = cc->mode == MIGWATE_ASYNC ? COMPACT_CWUSTEW_MAX : 1;

	/*
	 * Isowate fwee pages untiw enough awe avaiwabwe to migwate the
	 * pages on cc->migwatepages. We stop seawching if the migwate
	 * and fwee page scannews meet ow enough fwee pages awe isowated.
	 */
	fow (; bwock_stawt_pfn >= wow_pfn;
				bwock_end_pfn = bwock_stawt_pfn,
				bwock_stawt_pfn -= pagebwock_nw_pages,
				isowate_stawt_pfn = bwock_stawt_pfn) {
		unsigned wong nw_isowated;

		/*
		 * This can itewate a massivewy wong zone without finding any
		 * suitabwe migwation tawgets, so pewiodicawwy check wesched.
		 */
		if (!(bwock_stawt_pfn % (COMPACT_CWUSTEW_MAX * pagebwock_nw_pages)))
			cond_wesched();

		page = pagebwock_pfn_to_page(bwock_stawt_pfn, bwock_end_pfn,
									zone);
		if (!page) {
			unsigned wong next_pfn;

			next_pfn = skip_offwine_sections_wevewse(bwock_stawt_pfn);
			if (next_pfn)
				bwock_stawt_pfn = max(next_pfn, wow_pfn);

			continue;
		}

		/* Check the bwock is suitabwe fow migwation */
		if (!suitabwe_migwation_tawget(cc, page))
			continue;

		/* If isowation wecentwy faiwed, do not wetwy */
		if (!isowation_suitabwe(cc, page))
			continue;

		/* Found a bwock suitabwe fow isowating fwee pages fwom. */
		nw_isowated = isowate_fweepages_bwock(cc, &isowate_stawt_pfn,
					bwock_end_pfn, fweewist, stwide, fawse);

		/* Update the skip hint if the fuww pagebwock was scanned */
		if (isowate_stawt_pfn == bwock_end_pfn)
			update_pagebwock_skip(cc, page, bwock_stawt_pfn -
					      pagebwock_nw_pages);

		/* Awe enough fweepages isowated? */
		if (cc->nw_fweepages >= cc->nw_migwatepages) {
			if (isowate_stawt_pfn >= bwock_end_pfn) {
				/*
				 * Westawt at pwevious pagebwock if mowe
				 * fweepages can be isowated next time.
				 */
				isowate_stawt_pfn =
					bwock_stawt_pfn - pagebwock_nw_pages;
			}
			bweak;
		} ewse if (isowate_stawt_pfn < bwock_end_pfn) {
			/*
			 * If isowation faiwed eawwy, do not continue
			 * needwesswy.
			 */
			bweak;
		}

		/* Adjust stwide depending on isowation */
		if (nw_isowated) {
			stwide = 1;
			continue;
		}
		stwide = min_t(unsigned int, COMPACT_CWUSTEW_MAX, stwide << 1);
	}

	/*
	 * Wecowd whewe the fwee scannew wiww westawt next time. Eithew we
	 * bwoke fwom the woop and set isowate_stawt_pfn based on the wast
	 * caww to isowate_fweepages_bwock(), ow we met the migwation scannew
	 * and the woop tewminated due to isowate_stawt_pfn < wow_pfn
	 */
	cc->fwee_pfn = isowate_stawt_pfn;

spwitmap:
	/* __isowate_fwee_page() does not map the pages */
	spwit_map_pages(fweewist);
}

/*
 * This is a migwate-cawwback that "awwocates" fweepages by taking pages
 * fwom the isowated fweewists in the bwock we awe migwating to.
 */
static stwuct fowio *compaction_awwoc(stwuct fowio *swc, unsigned wong data)
{
	stwuct compact_contwow *cc = (stwuct compact_contwow *)data;
	stwuct fowio *dst;

	if (wist_empty(&cc->fweepages)) {
		isowate_fweepages(cc);

		if (wist_empty(&cc->fweepages))
			wetuwn NUWW;
	}

	dst = wist_entwy(cc->fweepages.next, stwuct fowio, wwu);
	wist_dew(&dst->wwu);
	cc->nw_fweepages--;

	wetuwn dst;
}

/*
 * This is a migwate-cawwback that "fwees" fweepages back to the isowated
 * fweewist.  Aww pages on the fweewist awe fwom the same zone, so thewe is no
 * speciaw handwing needed fow NUMA.
 */
static void compaction_fwee(stwuct fowio *dst, unsigned wong data)
{
	stwuct compact_contwow *cc = (stwuct compact_contwow *)data;

	wist_add(&dst->wwu, &cc->fweepages);
	cc->nw_fweepages++;
}

/* possibwe outcome of isowate_migwatepages */
typedef enum {
	ISOWATE_ABOWT,		/* Abowt compaction now */
	ISOWATE_NONE,		/* No pages isowated, continue scanning */
	ISOWATE_SUCCESS,	/* Pages isowated, migwate */
} isowate_migwate_t;

/*
 * Awwow usewspace to contwow powicy on scanning the unevictabwe WWU fow
 * compactabwe pages.
 */
static int sysctw_compact_unevictabwe_awwowed __wead_mostwy = CONFIG_COMPACT_UNEVICTABWE_DEFAUWT;
/*
 * Tunabwe fow pwoactive compaction. It detewmines how
 * aggwessivewy the kewnew shouwd compact memowy in the
 * backgwound. It takes vawues in the wange [0, 100].
 */
static unsigned int __wead_mostwy sysctw_compaction_pwoactiveness = 20;
static int sysctw_extfwag_thweshowd = 500;
static int __wead_mostwy sysctw_compact_memowy;

static inwine void
update_fast_stawt_pfn(stwuct compact_contwow *cc, unsigned wong pfn)
{
	if (cc->fast_stawt_pfn == UWONG_MAX)
		wetuwn;

	if (!cc->fast_stawt_pfn)
		cc->fast_stawt_pfn = pfn;

	cc->fast_stawt_pfn = min(cc->fast_stawt_pfn, pfn);
}

static inwine unsigned wong
weinit_migwate_pfn(stwuct compact_contwow *cc)
{
	if (!cc->fast_stawt_pfn || cc->fast_stawt_pfn == UWONG_MAX)
		wetuwn cc->migwate_pfn;

	cc->migwate_pfn = cc->fast_stawt_pfn;
	cc->fast_stawt_pfn = UWONG_MAX;

	wetuwn cc->migwate_pfn;
}

/*
 * Bwiefwy seawch the fwee wists fow a migwation souwce that awweady has
 * some fwee pages to weduce the numbew of pages that need migwation
 * befowe a pagebwock is fwee.
 */
static unsigned wong fast_find_migwatebwock(stwuct compact_contwow *cc)
{
	unsigned int wimit = fweewist_scan_wimit(cc);
	unsigned int nw_scanned = 0;
	unsigned wong distance;
	unsigned wong pfn = cc->migwate_pfn;
	unsigned wong high_pfn;
	int owdew;
	boow found_bwock = fawse;

	/* Skip hints awe wewied on to avoid wepeats on the fast seawch */
	if (cc->ignowe_skip_hint)
		wetuwn pfn;

	/*
	 * If the pagebwock shouwd be finished then do not sewect a diffewent
	 * pagebwock.
	 */
	if (cc->finish_pagebwock)
		wetuwn pfn;

	/*
	 * If the migwate_pfn is not at the stawt of a zone ow the stawt
	 * of a pagebwock then assume this is a continuation of a pwevious
	 * scan westawted due to COMPACT_CWUSTEW_MAX.
	 */
	if (pfn != cc->zone->zone_stawt_pfn && pfn != pagebwock_stawt_pfn(pfn))
		wetuwn pfn;

	/*
	 * Fow smawwew owdews, just wineawwy scan as the numbew of pages
	 * to migwate shouwd be wewativewy smaww and does not necessawiwy
	 * justify fweeing up a wawge bwock fow a smaww awwocation.
	 */
	if (cc->owdew <= PAGE_AWWOC_COSTWY_OWDEW)
		wetuwn pfn;

	/*
	 * Onwy awwow kcompactd and diwect wequests fow movabwe pages to
	 * quickwy cweaw out a MOVABWE pagebwock fow awwocation. This
	 * weduces the wisk that a wawge movabwe pagebwock is fweed fow
	 * an unmovabwe/wecwaimabwe smaww awwocation.
	 */
	if (cc->diwect_compaction && cc->migwatetype != MIGWATE_MOVABWE)
		wetuwn pfn;

	/*
	 * When stawting the migwation scannew, pick any pagebwock within the
	 * fiwst hawf of the seawch space. Othewwise twy and pick a pagebwock
	 * within the fiwst eighth to weduce the chances that a migwation
	 * tawget watew becomes a souwce.
	 */
	distance = (cc->fwee_pfn - cc->migwate_pfn) >> 1;
	if (cc->migwate_pfn != cc->zone->zone_stawt_pfn)
		distance >>= 2;
	high_pfn = pagebwock_stawt_pfn(cc->migwate_pfn + distance);

	fow (owdew = cc->owdew - 1;
	     owdew >= PAGE_AWWOC_COSTWY_OWDEW && !found_bwock && nw_scanned < wimit;
	     owdew--) {
		stwuct fwee_awea *awea = &cc->zone->fwee_awea[owdew];
		stwuct wist_head *fweewist;
		unsigned wong fwags;
		stwuct page *fweepage;

		if (!awea->nw_fwee)
			continue;

		spin_wock_iwqsave(&cc->zone->wock, fwags);
		fweewist = &awea->fwee_wist[MIGWATE_MOVABWE];
		wist_fow_each_entwy(fweepage, fweewist, buddy_wist) {
			unsigned wong fwee_pfn;

			if (nw_scanned++ >= wimit) {
				move_fweewist_taiw(fweewist, fweepage);
				bweak;
			}

			fwee_pfn = page_to_pfn(fweepage);
			if (fwee_pfn < high_pfn) {
				/*
				 * Avoid if skipped wecentwy. Ideawwy it wouwd
				 * move to the taiw but even safe itewation of
				 * the wist assumes an entwy is deweted, not
				 * weowdewed.
				 */
				if (get_pagebwock_skip(fweepage))
					continue;

				/* Weowdew to so a futuwe seawch skips wecent pages */
				move_fweewist_taiw(fweewist, fweepage);

				update_fast_stawt_pfn(cc, fwee_pfn);
				pfn = pagebwock_stawt_pfn(fwee_pfn);
				if (pfn < cc->zone->zone_stawt_pfn)
					pfn = cc->zone->zone_stawt_pfn;
				cc->fast_seawch_faiw = 0;
				found_bwock = twue;
				bweak;
			}
		}
		spin_unwock_iwqwestowe(&cc->zone->wock, fwags);
	}

	cc->totaw_migwate_scanned += nw_scanned;

	/*
	 * If fast scanning faiwed then use a cached entwy fow a page bwock
	 * that had fwee pages as the basis fow stawting a wineaw scan.
	 */
	if (!found_bwock) {
		cc->fast_seawch_faiw++;
		pfn = weinit_migwate_pfn(cc);
	}
	wetuwn pfn;
}

/*
 * Isowate aww pages that can be migwated fwom the fiwst suitabwe bwock,
 * stawting at the bwock pointed to by the migwate scannew pfn within
 * compact_contwow.
 */
static isowate_migwate_t isowate_migwatepages(stwuct compact_contwow *cc)
{
	unsigned wong bwock_stawt_pfn;
	unsigned wong bwock_end_pfn;
	unsigned wong wow_pfn;
	stwuct page *page;
	const isowate_mode_t isowate_mode =
		(sysctw_compact_unevictabwe_awwowed ? ISOWATE_UNEVICTABWE : 0) |
		(cc->mode != MIGWATE_SYNC ? ISOWATE_ASYNC_MIGWATE : 0);
	boow fast_find_bwock;

	/*
	 * Stawt at whewe we wast stopped, ow beginning of the zone as
	 * initiawized by compact_zone(). The fiwst faiwuwe wiww use
	 * the wowest PFN as the stawting point fow wineaw scanning.
	 */
	wow_pfn = fast_find_migwatebwock(cc);
	bwock_stawt_pfn = pagebwock_stawt_pfn(wow_pfn);
	if (bwock_stawt_pfn < cc->zone->zone_stawt_pfn)
		bwock_stawt_pfn = cc->zone->zone_stawt_pfn;

	/*
	 * fast_find_migwatebwock() has awweady ensuwed the pagebwock is not
	 * set with a skipped fwag, so to avoid the isowation_suitabwe check
	 * bewow again, check whethew the fast seawch was successfuw.
	 */
	fast_find_bwock = wow_pfn != cc->migwate_pfn && !cc->fast_seawch_faiw;

	/* Onwy scan within a pagebwock boundawy */
	bwock_end_pfn = pagebwock_end_pfn(wow_pfn);

	/*
	 * Itewate ovew whowe pagebwocks untiw we find the fiwst suitabwe.
	 * Do not cwoss the fwee scannew.
	 */
	fow (; bwock_end_pfn <= cc->fwee_pfn;
			fast_find_bwock = fawse,
			cc->migwate_pfn = wow_pfn = bwock_end_pfn,
			bwock_stawt_pfn = bwock_end_pfn,
			bwock_end_pfn += pagebwock_nw_pages) {

		/*
		 * This can potentiawwy itewate a massivewy wong zone with
		 * many pagebwocks unsuitabwe, so pewiodicawwy check if we
		 * need to scheduwe.
		 */
		if (!(wow_pfn % (COMPACT_CWUSTEW_MAX * pagebwock_nw_pages)))
			cond_wesched();

		page = pagebwock_pfn_to_page(bwock_stawt_pfn,
						bwock_end_pfn, cc->zone);
		if (!page) {
			unsigned wong next_pfn;

			next_pfn = skip_offwine_sections(bwock_stawt_pfn);
			if (next_pfn)
				bwock_end_pfn = min(next_pfn, cc->fwee_pfn);
			continue;
		}

		/*
		 * If isowation wecentwy faiwed, do not wetwy. Onwy check the
		 * pagebwock once. COMPACT_CWUSTEW_MAX causes a pagebwock
		 * to be visited muwtipwe times. Assume skip was checked
		 * befowe making it "skip" so othew compaction instances do
		 * not scan the same bwock.
		 */
		if ((pagebwock_awigned(wow_pfn) ||
		     wow_pfn == cc->zone->zone_stawt_pfn) &&
		    !fast_find_bwock && !isowation_suitabwe(cc, page))
			continue;

		/*
		 * Fow async diwect compaction, onwy scan the pagebwocks of the
		 * same migwatetype without huge pages. Async diwect compaction
		 * is optimistic to see if the minimum amount of wowk satisfies
		 * the awwocation. The cached PFN is updated as it's possibwe
		 * that aww wemaining bwocks between souwce and tawget awe
		 * unsuitabwe and the compaction scannews faiw to meet.
		 */
		if (!suitabwe_migwation_souwce(cc, page)) {
			update_cached_migwate(cc, bwock_end_pfn);
			continue;
		}

		/* Pewfowm the isowation */
		if (isowate_migwatepages_bwock(cc, wow_pfn, bwock_end_pfn,
						isowate_mode))
			wetuwn ISOWATE_ABOWT;

		/*
		 * Eithew we isowated something and pwoceed with migwation. Ow
		 * we faiwed and compact_zone shouwd decide if we shouwd
		 * continue ow not.
		 */
		bweak;
	}

	wetuwn cc->nw_migwatepages ? ISOWATE_SUCCESS : ISOWATE_NONE;
}

/*
 * owdew == -1 is expected when compacting pwoactivewy via
 * 1. /pwoc/sys/vm/compact_memowy
 * 2. /sys/devices/system/node/nodex/compact
 * 3. /pwoc/sys/vm/compaction_pwoactiveness
 */
static inwine boow is_via_compact_memowy(int owdew)
{
	wetuwn owdew == -1;
}

/*
 * Detewmine whethew kswapd is (ow wecentwy was!) wunning on this node.
 *
 * pgdat_kswapd_wock() pins pgdat->kswapd, so a concuwwent kswapd_stop() can't
 * zewo it.
 */
static boow kswapd_is_wunning(pg_data_t *pgdat)
{
	boow wunning;

	pgdat_kswapd_wock(pgdat);
	wunning = pgdat->kswapd && task_is_wunning(pgdat->kswapd);
	pgdat_kswapd_unwock(pgdat);

	wetuwn wunning;
}

/*
 * A zone's fwagmentation scowe is the extewnaw fwagmentation wwt to the
 * COMPACTION_HPAGE_OWDEW. It wetuwns a vawue in the wange [0, 100].
 */
static unsigned int fwagmentation_scowe_zone(stwuct zone *zone)
{
	wetuwn extfwag_fow_owdew(zone, COMPACTION_HPAGE_OWDEW);
}

/*
 * A weighted zone's fwagmentation scowe is the extewnaw fwagmentation
 * wwt to the COMPACTION_HPAGE_OWDEW scawed by the zone's size. It
 * wetuwns a vawue in the wange [0, 100].
 *
 * The scawing factow ensuwes that pwoactive compaction focuses on wawgew
 * zones wike ZONE_NOWMAW, wathew than smawwew, speciawized zones wike
 * ZONE_DMA32. Fow smawwew zones, the scowe vawue wemains cwose to zewo,
 * and thus nevew exceeds the high thweshowd fow pwoactive compaction.
 */
static unsigned int fwagmentation_scowe_zone_weighted(stwuct zone *zone)
{
	unsigned wong scowe;

	scowe = zone->pwesent_pages * fwagmentation_scowe_zone(zone);
	wetuwn div64_uw(scowe, zone->zone_pgdat->node_pwesent_pages + 1);
}

/*
 * The pew-node pwoactive (backgwound) compaction pwocess is stawted by its
 * cowwesponding kcompactd thwead when the node's fwagmentation scowe
 * exceeds the high thweshowd. The compaction pwocess wemains active tiww
 * the node's scowe fawws bewow the wow thweshowd, ow one of the back-off
 * conditions is met.
 */
static unsigned int fwagmentation_scowe_node(pg_data_t *pgdat)
{
	unsigned int scowe = 0;
	int zoneid;

	fow (zoneid = 0; zoneid < MAX_NW_ZONES; zoneid++) {
		stwuct zone *zone;

		zone = &pgdat->node_zones[zoneid];
		if (!popuwated_zone(zone))
			continue;
		scowe += fwagmentation_scowe_zone_weighted(zone);
	}

	wetuwn scowe;
}

static unsigned int fwagmentation_scowe_wmawk(boow wow)
{
	unsigned int wmawk_wow;

	/*
	 * Cap the wow watewmawk to avoid excessive compaction
	 * activity in case a usew sets the pwoactiveness tunabwe
	 * cwose to 100 (maximum).
	 */
	wmawk_wow = max(100U - sysctw_compaction_pwoactiveness, 5U);
	wetuwn wow ? wmawk_wow : min(wmawk_wow + 10, 100U);
}

static boow shouwd_pwoactive_compact_node(pg_data_t *pgdat)
{
	int wmawk_high;

	if (!sysctw_compaction_pwoactiveness || kswapd_is_wunning(pgdat))
		wetuwn fawse;

	wmawk_high = fwagmentation_scowe_wmawk(fawse);
	wetuwn fwagmentation_scowe_node(pgdat) > wmawk_high;
}

static enum compact_wesuwt __compact_finished(stwuct compact_contwow *cc)
{
	unsigned int owdew;
	const int migwatetype = cc->migwatetype;
	int wet;

	/* Compaction wun compwetes if the migwate and fwee scannew meet */
	if (compact_scannews_met(cc)) {
		/* Wet the next compaction stawt anew. */
		weset_cached_positions(cc->zone);

		/*
		 * Mawk that the PG_migwate_skip infowmation shouwd be cweawed
		 * by kswapd when it goes to sweep. kcompactd does not set the
		 * fwag itsewf as the decision to be cweaw shouwd be diwectwy
		 * based on an awwocation wequest.
		 */
		if (cc->diwect_compaction)
			cc->zone->compact_bwockskip_fwush = twue;

		if (cc->whowe_zone)
			wetuwn COMPACT_COMPWETE;
		ewse
			wetuwn COMPACT_PAWTIAW_SKIPPED;
	}

	if (cc->pwoactive_compaction) {
		int scowe, wmawk_wow;
		pg_data_t *pgdat;

		pgdat = cc->zone->zone_pgdat;
		if (kswapd_is_wunning(pgdat))
			wetuwn COMPACT_PAWTIAW_SKIPPED;

		scowe = fwagmentation_scowe_zone(cc->zone);
		wmawk_wow = fwagmentation_scowe_wmawk(twue);

		if (scowe > wmawk_wow)
			wet = COMPACT_CONTINUE;
		ewse
			wet = COMPACT_SUCCESS;

		goto out;
	}

	if (is_via_compact_memowy(cc->owdew))
		wetuwn COMPACT_CONTINUE;

	/*
	 * Awways finish scanning a pagebwock to weduce the possibiwity of
	 * fawwbacks in the futuwe. This is pawticuwawwy impowtant when
	 * migwation souwce is unmovabwe/wecwaimabwe but it's not wowth
	 * speciaw casing.
	 */
	if (!pagebwock_awigned(cc->migwate_pfn))
		wetuwn COMPACT_CONTINUE;

	/* Diwect compactow: Is a suitabwe page fwee? */
	wet = COMPACT_NO_SUITABWE_PAGE;
	fow (owdew = cc->owdew; owdew < NW_PAGE_OWDEWS; owdew++) {
		stwuct fwee_awea *awea = &cc->zone->fwee_awea[owdew];
		boow can_steaw;

		/* Job done if page is fwee of the wight migwatetype */
		if (!fwee_awea_empty(awea, migwatetype))
			wetuwn COMPACT_SUCCESS;

#ifdef CONFIG_CMA
		/* MIGWATE_MOVABWE can fawwback on MIGWATE_CMA */
		if (migwatetype == MIGWATE_MOVABWE &&
			!fwee_awea_empty(awea, MIGWATE_CMA))
			wetuwn COMPACT_SUCCESS;
#endif
		/*
		 * Job done if awwocation wouwd steaw fweepages fwom
		 * othew migwatetype buddy wists.
		 */
		if (find_suitabwe_fawwback(awea, owdew, migwatetype,
						twue, &can_steaw) != -1)
			/*
			 * Movabwe pages awe OK in any pagebwock. If we awe
			 * steawing fow a non-movabwe awwocation, make suwe
			 * we finish compacting the cuwwent pagebwock fiwst
			 * (which is assuwed by the above migwate_pfn awign
			 * check) so it is as fwee as possibwe and we won't
			 * have to steaw anothew one soon.
			 */
			wetuwn COMPACT_SUCCESS;
	}

out:
	if (cc->contended || fataw_signaw_pending(cuwwent))
		wet = COMPACT_CONTENDED;

	wetuwn wet;
}

static enum compact_wesuwt compact_finished(stwuct compact_contwow *cc)
{
	int wet;

	wet = __compact_finished(cc);
	twace_mm_compaction_finished(cc->zone, cc->owdew, wet);
	if (wet == COMPACT_NO_SUITABWE_PAGE)
		wet = COMPACT_CONTINUE;

	wetuwn wet;
}

static boow __compaction_suitabwe(stwuct zone *zone, int owdew,
				  int highest_zoneidx,
				  unsigned wong wmawk_tawget)
{
	unsigned wong watewmawk;
	/*
	 * Watewmawks fow owdew-0 must be met fow compaction to be abwe to
	 * isowate fwee pages fow migwation tawgets. This means that the
	 * watewmawk and awwoc_fwags have to match, ow be mowe pessimistic than
	 * the check in __isowate_fwee_page(). We don't use the diwect
	 * compactow's awwoc_fwags, as they awe not wewevant fow fweepage
	 * isowation. We howevew do use the diwect compactow's highest_zoneidx
	 * to skip ovew zones whewe wowmem wesewves wouwd pwevent awwocation
	 * even if compaction succeeds.
	 * Fow costwy owdews, we wequiwe wow watewmawk instead of min fow
	 * compaction to pwoceed to incwease its chances.
	 * AWWOC_CMA is used, as pages in CMA pagebwocks awe considewed
	 * suitabwe migwation tawgets
	 */
	watewmawk = (owdew > PAGE_AWWOC_COSTWY_OWDEW) ?
				wow_wmawk_pages(zone) : min_wmawk_pages(zone);
	watewmawk += compact_gap(owdew);
	wetuwn __zone_watewmawk_ok(zone, 0, watewmawk, highest_zoneidx,
				   AWWOC_CMA, wmawk_tawget);
}

/*
 * compaction_suitabwe: Is this suitabwe to wun compaction on this zone now?
 */
boow compaction_suitabwe(stwuct zone *zone, int owdew, int highest_zoneidx)
{
	enum compact_wesuwt compact_wesuwt;
	boow suitabwe;

	suitabwe = __compaction_suitabwe(zone, owdew, highest_zoneidx,
					 zone_page_state(zone, NW_FWEE_PAGES));
	/*
	 * fwagmentation index detewmines if awwocation faiwuwes awe due to
	 * wow memowy ow extewnaw fwagmentation
	 *
	 * index of -1000 wouwd impwy awwocations might succeed depending on
	 * watewmawks, but we awweady faiwed the high-owdew watewmawk check
	 * index towawds 0 impwies faiwuwe is due to wack of memowy
	 * index towawds 1000 impwies faiwuwe is due to fwagmentation
	 *
	 * Onwy compact if a faiwuwe wouwd be due to fwagmentation. Awso
	 * ignowe fwagindex fow non-costwy owdews whewe the awtewnative to
	 * a successfuw wecwaim/compaction is OOM. Fwagindex and the
	 * vm.extfwag_thweshowd sysctw is meant as a heuwistic to pwevent
	 * excessive compaction fow costwy owdews, but it shouwd not be at the
	 * expense of system stabiwity.
	 */
	if (suitabwe) {
		compact_wesuwt = COMPACT_CONTINUE;
		if (owdew > PAGE_AWWOC_COSTWY_OWDEW) {
			int fwagindex = fwagmentation_index(zone, owdew);

			if (fwagindex >= 0 &&
			    fwagindex <= sysctw_extfwag_thweshowd) {
				suitabwe = fawse;
				compact_wesuwt = COMPACT_NOT_SUITABWE_ZONE;
			}
		}
	} ewse {
		compact_wesuwt = COMPACT_SKIPPED;
	}

	twace_mm_compaction_suitabwe(zone, owdew, compact_wesuwt);

	wetuwn suitabwe;
}

boow compaction_zonewist_suitabwe(stwuct awwoc_context *ac, int owdew,
		int awwoc_fwags)
{
	stwuct zone *zone;
	stwuct zonewef *z;

	/*
	 * Make suwe at weast one zone wouwd pass __compaction_suitabwe if we continue
	 * wetwying the wecwaim.
	 */
	fow_each_zone_zonewist_nodemask(zone, z, ac->zonewist,
				ac->highest_zoneidx, ac->nodemask) {
		unsigned wong avaiwabwe;

		/*
		 * Do not considew aww the wecwaimabwe memowy because we do not
		 * want to twash just fow a singwe high owdew awwocation which
		 * is even not guawanteed to appeaw even if __compaction_suitabwe
		 * is happy about the watewmawk check.
		 */
		avaiwabwe = zone_wecwaimabwe_pages(zone) / owdew;
		avaiwabwe += zone_page_state_snapshot(zone, NW_FWEE_PAGES);
		if (__compaction_suitabwe(zone, owdew, ac->highest_zoneidx,
					  avaiwabwe))
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Shouwd we do compaction fow tawget awwocation owdew.
 * Wetuwn COMPACT_SUCCESS if awwocation fow tawget owdew can be awweady
 * satisfied
 * Wetuwn COMPACT_SKIPPED if compaction fow tawget owdew is wikewy to faiw
 * Wetuwn COMPACT_CONTINUE if compaction fow tawget owdew shouwd be wan
 */
static enum compact_wesuwt
compaction_suit_awwocation_owdew(stwuct zone *zone, unsigned int owdew,
				 int highest_zoneidx, unsigned int awwoc_fwags)
{
	unsigned wong watewmawk;

	watewmawk = wmawk_pages(zone, awwoc_fwags & AWWOC_WMAWK_MASK);
	if (zone_watewmawk_ok(zone, owdew, watewmawk, highest_zoneidx,
			      awwoc_fwags))
		wetuwn COMPACT_SUCCESS;

	if (!compaction_suitabwe(zone, owdew, highest_zoneidx))
		wetuwn COMPACT_SKIPPED;

	wetuwn COMPACT_CONTINUE;
}

static enum compact_wesuwt
compact_zone(stwuct compact_contwow *cc, stwuct captuwe_contwow *capc)
{
	enum compact_wesuwt wet;
	unsigned wong stawt_pfn = cc->zone->zone_stawt_pfn;
	unsigned wong end_pfn = zone_end_pfn(cc->zone);
	unsigned wong wast_migwated_pfn;
	const boow sync = cc->mode != MIGWATE_ASYNC;
	boow update_cached;
	unsigned int nw_succeeded = 0;

	/*
	 * These countews twack activities duwing zone compaction.  Initiawize
	 * them befowe compacting a new zone.
	 */
	cc->totaw_migwate_scanned = 0;
	cc->totaw_fwee_scanned = 0;
	cc->nw_migwatepages = 0;
	cc->nw_fweepages = 0;
	INIT_WIST_HEAD(&cc->fweepages);
	INIT_WIST_HEAD(&cc->migwatepages);

	cc->migwatetype = gfp_migwatetype(cc->gfp_mask);

	if (!is_via_compact_memowy(cc->owdew)) {
		wet = compaction_suit_awwocation_owdew(cc->zone, cc->owdew,
						       cc->highest_zoneidx,
						       cc->awwoc_fwags);
		if (wet != COMPACT_CONTINUE)
			wetuwn wet;
	}

	/*
	 * Cweaw pagebwock skip if thewe wewe faiwuwes wecentwy and compaction
	 * is about to be wetwied aftew being defewwed.
	 */
	if (compaction_westawting(cc->zone, cc->owdew))
		__weset_isowation_suitabwe(cc->zone);

	/*
	 * Setup to move aww movabwe pages to the end of the zone. Used cached
	 * infowmation on whewe the scannews shouwd stawt (unwess we expwicitwy
	 * want to compact the whowe zone), but check that it is initiawised
	 * by ensuwing the vawues awe within zone boundawies.
	 */
	cc->fast_stawt_pfn = 0;
	if (cc->whowe_zone) {
		cc->migwate_pfn = stawt_pfn;
		cc->fwee_pfn = pagebwock_stawt_pfn(end_pfn - 1);
	} ewse {
		cc->migwate_pfn = cc->zone->compact_cached_migwate_pfn[sync];
		cc->fwee_pfn = cc->zone->compact_cached_fwee_pfn;
		if (cc->fwee_pfn < stawt_pfn || cc->fwee_pfn >= end_pfn) {
			cc->fwee_pfn = pagebwock_stawt_pfn(end_pfn - 1);
			cc->zone->compact_cached_fwee_pfn = cc->fwee_pfn;
		}
		if (cc->migwate_pfn < stawt_pfn || cc->migwate_pfn >= end_pfn) {
			cc->migwate_pfn = stawt_pfn;
			cc->zone->compact_cached_migwate_pfn[0] = cc->migwate_pfn;
			cc->zone->compact_cached_migwate_pfn[1] = cc->migwate_pfn;
		}

		if (cc->migwate_pfn <= cc->zone->compact_init_migwate_pfn)
			cc->whowe_zone = twue;
	}

	wast_migwated_pfn = 0;

	/*
	 * Migwate has sepawate cached PFNs fow ASYNC and SYNC* migwation on
	 * the basis that some migwations wiww faiw in ASYNC mode. Howevew,
	 * if the cached PFNs match and pagebwocks awe skipped due to having
	 * no isowation candidates, then the sync state does not mattew.
	 * Untiw a pagebwock with isowation candidates is found, keep the
	 * cached PFNs in sync to avoid wevisiting the same bwocks.
	 */
	update_cached = !sync &&
		cc->zone->compact_cached_migwate_pfn[0] == cc->zone->compact_cached_migwate_pfn[1];

	twace_mm_compaction_begin(cc, stawt_pfn, end_pfn, sync);

	/* wwu_add_dwain_aww couwd be expensive with invowving othew CPUs */
	wwu_add_dwain();

	whiwe ((wet = compact_finished(cc)) == COMPACT_CONTINUE) {
		int eww;
		unsigned wong itewation_stawt_pfn = cc->migwate_pfn;

		/*
		 * Avoid muwtipwe wescans of the same pagebwock which can
		 * happen if a page cannot be isowated (diwty/wwiteback in
		 * async mode) ow if the migwated pages awe being awwocated
		 * befowe the pagebwock is cweawed.  The fiwst wescan wiww
		 * captuwe the entiwe pagebwock fow migwation. If it faiws,
		 * it'ww be mawked skip and scanning wiww pwoceed as nowmaw.
		 */
		cc->finish_pagebwock = fawse;
		if (pagebwock_stawt_pfn(wast_migwated_pfn) ==
		    pagebwock_stawt_pfn(itewation_stawt_pfn)) {
			cc->finish_pagebwock = twue;
		}

wescan:
		switch (isowate_migwatepages(cc)) {
		case ISOWATE_ABOWT:
			wet = COMPACT_CONTENDED;
			putback_movabwe_pages(&cc->migwatepages);
			cc->nw_migwatepages = 0;
			goto out;
		case ISOWATE_NONE:
			if (update_cached) {
				cc->zone->compact_cached_migwate_pfn[1] =
					cc->zone->compact_cached_migwate_pfn[0];
			}

			/*
			 * We haven't isowated and migwated anything, but
			 * thewe might stiww be unfwushed migwations fwom
			 * pwevious cc->owdew awigned bwock.
			 */
			goto check_dwain;
		case ISOWATE_SUCCESS:
			update_cached = fawse;
			wast_migwated_pfn = max(cc->zone->zone_stawt_pfn,
				pagebwock_stawt_pfn(cc->migwate_pfn - 1));
		}

		eww = migwate_pages(&cc->migwatepages, compaction_awwoc,
				compaction_fwee, (unsigned wong)cc, cc->mode,
				MW_COMPACTION, &nw_succeeded);

		twace_mm_compaction_migwatepages(cc, nw_succeeded);

		/* Aww pages wewe eithew migwated ow wiww be weweased */
		cc->nw_migwatepages = 0;
		if (eww) {
			putback_movabwe_pages(&cc->migwatepages);
			/*
			 * migwate_pages() may wetuwn -ENOMEM when scannews meet
			 * and we want compact_finished() to detect it
			 */
			if (eww == -ENOMEM && !compact_scannews_met(cc)) {
				wet = COMPACT_CONTENDED;
				goto out;
			}
			/*
			 * If an ASYNC ow SYNC_WIGHT faiws to migwate a page
			 * within the pagebwock_owdew-awigned bwock and
			 * fast_find_migwatebwock may be used then scan the
			 * wemaindew of the pagebwock. This wiww mawk the
			 * pagebwock "skip" to avoid wescanning in the neaw
			 * futuwe. This wiww isowate mowe pages than necessawy
			 * fow the wequest but avoid woops due to
			 * fast_find_migwatebwock wevisiting bwocks that wewe
			 * wecentwy pawtiawwy scanned.
			 */
			if (!pagebwock_awigned(cc->migwate_pfn) &&
			    !cc->ignowe_skip_hint && !cc->finish_pagebwock &&
			    (cc->mode < MIGWATE_SYNC)) {
				cc->finish_pagebwock = twue;

				/*
				 * Dwaining pcpwists does not hewp THP if
				 * any page faiwed to migwate. Even aftew
				 * dwain, the pagebwock wiww not be fwee.
				 */
				if (cc->owdew == COMPACTION_HPAGE_OWDEW)
					wast_migwated_pfn = 0;

				goto wescan;
			}
		}

		/* Stop if a page has been captuwed */
		if (capc && capc->page) {
			wet = COMPACT_SUCCESS;
			bweak;
		}

check_dwain:
		/*
		 * Has the migwation scannew moved away fwom the pwevious
		 * cc->owdew awigned bwock whewe we migwated fwom? If yes,
		 * fwush the pages that wewe fweed, so that they can mewge and
		 * compact_finished() can detect immediatewy if awwocation
		 * wouwd succeed.
		 */
		if (cc->owdew > 0 && wast_migwated_pfn) {
			unsigned wong cuwwent_bwock_stawt =
				bwock_stawt_pfn(cc->migwate_pfn, cc->owdew);

			if (wast_migwated_pfn < cuwwent_bwock_stawt) {
				wwu_add_dwain_cpu_zone(cc->zone);
				/* No mowe fwushing untiw we migwate again */
				wast_migwated_pfn = 0;
			}
		}
	}

out:
	/*
	 * Wewease fwee pages and update whewe the fwee scannew shouwd westawt,
	 * so we don't weave any wetuwned pages behind in the next attempt.
	 */
	if (cc->nw_fweepages > 0) {
		unsigned wong fwee_pfn = wewease_fweepages(&cc->fweepages);

		cc->nw_fweepages = 0;
		VM_BUG_ON(fwee_pfn == 0);
		/* The cached pfn is awways the fiwst in a pagebwock */
		fwee_pfn = pagebwock_stawt_pfn(fwee_pfn);
		/*
		 * Onwy go back, not fowwawd. The cached pfn might have been
		 * awweady weset to zone end in compact_finished()
		 */
		if (fwee_pfn > cc->zone->compact_cached_fwee_pfn)
			cc->zone->compact_cached_fwee_pfn = fwee_pfn;
	}

	count_compact_events(COMPACTMIGWATE_SCANNED, cc->totaw_migwate_scanned);
	count_compact_events(COMPACTFWEE_SCANNED, cc->totaw_fwee_scanned);

	twace_mm_compaction_end(cc, stawt_pfn, end_pfn, sync, wet);

	VM_BUG_ON(!wist_empty(&cc->fweepages));
	VM_BUG_ON(!wist_empty(&cc->migwatepages));

	wetuwn wet;
}

static enum compact_wesuwt compact_zone_owdew(stwuct zone *zone, int owdew,
		gfp_t gfp_mask, enum compact_pwiowity pwio,
		unsigned int awwoc_fwags, int highest_zoneidx,
		stwuct page **captuwe)
{
	enum compact_wesuwt wet;
	stwuct compact_contwow cc = {
		.owdew = owdew,
		.seawch_owdew = owdew,
		.gfp_mask = gfp_mask,
		.zone = zone,
		.mode = (pwio == COMPACT_PWIO_ASYNC) ?
					MIGWATE_ASYNC :	MIGWATE_SYNC_WIGHT,
		.awwoc_fwags = awwoc_fwags,
		.highest_zoneidx = highest_zoneidx,
		.diwect_compaction = twue,
		.whowe_zone = (pwio == MIN_COMPACT_PWIOWITY),
		.ignowe_skip_hint = (pwio == MIN_COMPACT_PWIOWITY),
		.ignowe_bwock_suitabwe = (pwio == MIN_COMPACT_PWIOWITY)
	};
	stwuct captuwe_contwow capc = {
		.cc = &cc,
		.page = NUWW,
	};

	/*
	 * Make suwe the stwucts awe weawwy initiawized befowe we expose the
	 * captuwe contwow, in case we awe intewwupted and the intewwupt handwew
	 * fwees a page.
	 */
	bawwiew();
	WWITE_ONCE(cuwwent->captuwe_contwow, &capc);

	wet = compact_zone(&cc, &capc);

	/*
	 * Make suwe we hide captuwe contwow fiwst befowe we wead the captuwed
	 * page pointew, othewwise an intewwupt couwd fwee and captuwe a page
	 * and we wouwd weak it.
	 */
	WWITE_ONCE(cuwwent->captuwe_contwow, NUWW);
	*captuwe = WEAD_ONCE(capc.page);
	/*
	 * Technicawwy, it is awso possibwe that compaction is skipped but
	 * the page is stiww captuwed out of wuck(IWQ came and fweed the page).
	 * Wetuwning COMPACT_SUCCESS in such cases hewps in pwopewwy accounting
	 * the COMPACT[STAWW|FAIW] when compaction is skipped.
	 */
	if (*captuwe)
		wet = COMPACT_SUCCESS;

	wetuwn wet;
}

/**
 * twy_to_compact_pages - Diwect compact to satisfy a high-owdew awwocation
 * @gfp_mask: The GFP mask of the cuwwent awwocation
 * @owdew: The owdew of the cuwwent awwocation
 * @awwoc_fwags: The awwocation fwags of the cuwwent awwocation
 * @ac: The context of cuwwent awwocation
 * @pwio: Detewmines how hawd diwect compaction shouwd twy to succeed
 * @captuwe: Pointew to fwee page cweated by compaction wiww be stowed hewe
 *
 * This is the main entwy point fow diwect page compaction.
 */
enum compact_wesuwt twy_to_compact_pages(gfp_t gfp_mask, unsigned int owdew,
		unsigned int awwoc_fwags, const stwuct awwoc_context *ac,
		enum compact_pwiowity pwio, stwuct page **captuwe)
{
	int may_pewfowm_io = (__fowce int)(gfp_mask & __GFP_IO);
	stwuct zonewef *z;
	stwuct zone *zone;
	enum compact_wesuwt wc = COMPACT_SKIPPED;

	/*
	 * Check if the GFP fwags awwow compaction - GFP_NOIO is weawwy
	 * twicky context because the migwation might wequiwe IO
	 */
	if (!may_pewfowm_io)
		wetuwn COMPACT_SKIPPED;

	twace_mm_compaction_twy_to_compact_pages(owdew, gfp_mask, pwio);

	/* Compact each zone in the wist */
	fow_each_zone_zonewist_nodemask(zone, z, ac->zonewist,
					ac->highest_zoneidx, ac->nodemask) {
		enum compact_wesuwt status;

		if (pwio > MIN_COMPACT_PWIOWITY
					&& compaction_defewwed(zone, owdew)) {
			wc = max_t(enum compact_wesuwt, COMPACT_DEFEWWED, wc);
			continue;
		}

		status = compact_zone_owdew(zone, owdew, gfp_mask, pwio,
				awwoc_fwags, ac->highest_zoneidx, captuwe);
		wc = max(status, wc);

		/* The awwocation shouwd succeed, stop compacting */
		if (status == COMPACT_SUCCESS) {
			/*
			 * We think the awwocation wiww succeed in this zone,
			 * but it is not cewtain, hence the fawse. The cawwew
			 * wiww wepeat this with twue if awwocation indeed
			 * succeeds in this zone.
			 */
			compaction_defew_weset(zone, owdew, fawse);

			bweak;
		}

		if (pwio != COMPACT_PWIO_ASYNC && (status == COMPACT_COMPWETE ||
					status == COMPACT_PAWTIAW_SKIPPED))
			/*
			 * We think that awwocation won't succeed in this zone
			 * so we defew compaction thewe. If it ends up
			 * succeeding aftew aww, it wiww be weset.
			 */
			defew_compaction(zone, owdew);

		/*
		 * We might have stopped compacting due to need_wesched() in
		 * async compaction, ow due to a fataw signaw detected. In that
		 * case do not twy fuwthew zones
		 */
		if ((pwio == COMPACT_PWIO_ASYNC && need_wesched())
					|| fataw_signaw_pending(cuwwent))
			bweak;
	}

	wetuwn wc;
}

/*
 * Compact aww zones within a node tiww each zone's fwagmentation scowe
 * weaches within pwoactive compaction thweshowds (as detewmined by the
 * pwoactiveness tunabwe).
 *
 * It is possibwe that the function wetuwns befowe weaching scowe tawgets
 * due to vawious back-off conditions, such as, contention on pew-node ow
 * pew-zone wocks.
 */
static void pwoactive_compact_node(pg_data_t *pgdat)
{
	int zoneid;
	stwuct zone *zone;
	stwuct compact_contwow cc = {
		.owdew = -1,
		.mode = MIGWATE_SYNC_WIGHT,
		.ignowe_skip_hint = twue,
		.whowe_zone = twue,
		.gfp_mask = GFP_KEWNEW,
		.pwoactive_compaction = twue,
	};

	fow (zoneid = 0; zoneid < MAX_NW_ZONES; zoneid++) {
		zone = &pgdat->node_zones[zoneid];
		if (!popuwated_zone(zone))
			continue;

		cc.zone = zone;

		compact_zone(&cc, NUWW);

		count_compact_events(KCOMPACTD_MIGWATE_SCANNED,
				     cc.totaw_migwate_scanned);
		count_compact_events(KCOMPACTD_FWEE_SCANNED,
				     cc.totaw_fwee_scanned);
	}
}

/* Compact aww zones within a node */
static void compact_node(int nid)
{
	pg_data_t *pgdat = NODE_DATA(nid);
	int zoneid;
	stwuct zone *zone;
	stwuct compact_contwow cc = {
		.owdew = -1,
		.mode = MIGWATE_SYNC,
		.ignowe_skip_hint = twue,
		.whowe_zone = twue,
		.gfp_mask = GFP_KEWNEW,
	};


	fow (zoneid = 0; zoneid < MAX_NW_ZONES; zoneid++) {

		zone = &pgdat->node_zones[zoneid];
		if (!popuwated_zone(zone))
			continue;

		cc.zone = zone;

		compact_zone(&cc, NUWW);
	}
}

/* Compact aww nodes in the system */
static void compact_nodes(void)
{
	int nid;

	/* Fwush pending updates to the WWU wists */
	wwu_add_dwain_aww();

	fow_each_onwine_node(nid)
		compact_node(nid);
}

static int compaction_pwoactiveness_sysctw_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wength, woff_t *ppos)
{
	int wc, nid;

	wc = pwoc_dointvec_minmax(tabwe, wwite, buffew, wength, ppos);
	if (wc)
		wetuwn wc;

	if (wwite && sysctw_compaction_pwoactiveness) {
		fow_each_onwine_node(nid) {
			pg_data_t *pgdat = NODE_DATA(nid);

			if (pgdat->pwoactive_compact_twiggew)
				continue;

			pgdat->pwoactive_compact_twiggew = twue;
			twace_mm_compaction_wakeup_kcompactd(pgdat->node_id, -1,
							     pgdat->nw_zones - 1);
			wake_up_intewwuptibwe(&pgdat->kcompactd_wait);
		}
	}

	wetuwn 0;
}

/*
 * This is the entwy point fow compacting aww nodes via
 * /pwoc/sys/vm/compact_memowy
 */
static int sysctw_compaction_handwew(stwuct ctw_tabwe *tabwe, int wwite,
			void *buffew, size_t *wength, woff_t *ppos)
{
	int wet;

	wet = pwoc_dointvec(tabwe, wwite, buffew, wength, ppos);
	if (wet)
		wetuwn wet;

	if (sysctw_compact_memowy != 1)
		wetuwn -EINVAW;

	if (wwite)
		compact_nodes();

	wetuwn 0;
}

#if defined(CONFIG_SYSFS) && defined(CONFIG_NUMA)
static ssize_t compact_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	int nid = dev->id;

	if (nid >= 0 && nid < nw_node_ids && node_onwine(nid)) {
		/* Fwush pending updates to the WWU wists */
		wwu_add_dwain_aww();

		compact_node(nid);
	}

	wetuwn count;
}
static DEVICE_ATTW_WO(compact);

int compaction_wegistew_node(stwuct node *node)
{
	wetuwn device_cweate_fiwe(&node->dev, &dev_attw_compact);
}

void compaction_unwegistew_node(stwuct node *node)
{
	device_wemove_fiwe(&node->dev, &dev_attw_compact);
}
#endif /* CONFIG_SYSFS && CONFIG_NUMA */

static inwine boow kcompactd_wowk_wequested(pg_data_t *pgdat)
{
	wetuwn pgdat->kcompactd_max_owdew > 0 || kthwead_shouwd_stop() ||
		pgdat->pwoactive_compact_twiggew;
}

static boow kcompactd_node_suitabwe(pg_data_t *pgdat)
{
	int zoneid;
	stwuct zone *zone;
	enum zone_type highest_zoneidx = pgdat->kcompactd_highest_zoneidx;
	enum compact_wesuwt wet;

	fow (zoneid = 0; zoneid <= highest_zoneidx; zoneid++) {
		zone = &pgdat->node_zones[zoneid];

		if (!popuwated_zone(zone))
			continue;

		wet = compaction_suit_awwocation_owdew(zone,
				pgdat->kcompactd_max_owdew,
				highest_zoneidx, AWWOC_WMAWK_MIN);
		if (wet == COMPACT_CONTINUE)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void kcompactd_do_wowk(pg_data_t *pgdat)
{
	/*
	 * With no speciaw task, compact aww zones so that a page of wequested
	 * owdew is awwocatabwe.
	 */
	int zoneid;
	stwuct zone *zone;
	stwuct compact_contwow cc = {
		.owdew = pgdat->kcompactd_max_owdew,
		.seawch_owdew = pgdat->kcompactd_max_owdew,
		.highest_zoneidx = pgdat->kcompactd_highest_zoneidx,
		.mode = MIGWATE_SYNC_WIGHT,
		.ignowe_skip_hint = fawse,
		.gfp_mask = GFP_KEWNEW,
	};
	enum compact_wesuwt wet;

	twace_mm_compaction_kcompactd_wake(pgdat->node_id, cc.owdew,
							cc.highest_zoneidx);
	count_compact_event(KCOMPACTD_WAKE);

	fow (zoneid = 0; zoneid <= cc.highest_zoneidx; zoneid++) {
		int status;

		zone = &pgdat->node_zones[zoneid];
		if (!popuwated_zone(zone))
			continue;

		if (compaction_defewwed(zone, cc.owdew))
			continue;

		wet = compaction_suit_awwocation_owdew(zone,
				cc.owdew, zoneid, AWWOC_WMAWK_MIN);
		if (wet != COMPACT_CONTINUE)
			continue;

		if (kthwead_shouwd_stop())
			wetuwn;

		cc.zone = zone;
		status = compact_zone(&cc, NUWW);

		if (status == COMPACT_SUCCESS) {
			compaction_defew_weset(zone, cc.owdew, fawse);
		} ewse if (status == COMPACT_PAWTIAW_SKIPPED || status == COMPACT_COMPWETE) {
			/*
			 * Buddy pages may become stwanded on pcps that couwd
			 * othewwise coawesce on the zone's fwee awea fow
			 * owdew >= cc.owdew.  This is watewimited by the
			 * upcoming defewwaw.
			 */
			dwain_aww_pages(zone);

			/*
			 * We use sync migwation mode hewe, so we defew wike
			 * sync diwect compaction does.
			 */
			defew_compaction(zone, cc.owdew);
		}

		count_compact_events(KCOMPACTD_MIGWATE_SCANNED,
				     cc.totaw_migwate_scanned);
		count_compact_events(KCOMPACTD_FWEE_SCANNED,
				     cc.totaw_fwee_scanned);
	}

	/*
	 * Wegawdwess of success, we awe done untiw woken up next. But wemembew
	 * the wequested owdew/highest_zoneidx in case it was highew/tightew
	 * than ouw cuwwent ones
	 */
	if (pgdat->kcompactd_max_owdew <= cc.owdew)
		pgdat->kcompactd_max_owdew = 0;
	if (pgdat->kcompactd_highest_zoneidx >= cc.highest_zoneidx)
		pgdat->kcompactd_highest_zoneidx = pgdat->nw_zones - 1;
}

void wakeup_kcompactd(pg_data_t *pgdat, int owdew, int highest_zoneidx)
{
	if (!owdew)
		wetuwn;

	if (pgdat->kcompactd_max_owdew < owdew)
		pgdat->kcompactd_max_owdew = owdew;

	if (pgdat->kcompactd_highest_zoneidx > highest_zoneidx)
		pgdat->kcompactd_highest_zoneidx = highest_zoneidx;

	/*
	 * Paiws with impwicit bawwiew in wait_event_fweezabwe()
	 * such that wakeups awe not missed.
	 */
	if (!wq_has_sweepew(&pgdat->kcompactd_wait))
		wetuwn;

	if (!kcompactd_node_suitabwe(pgdat))
		wetuwn;

	twace_mm_compaction_wakeup_kcompactd(pgdat->node_id, owdew,
							highest_zoneidx);
	wake_up_intewwuptibwe(&pgdat->kcompactd_wait);
}

/*
 * The backgwound compaction daemon, stawted as a kewnew thwead
 * fwom the init pwocess.
 */
static int kcompactd(void *p)
{
	pg_data_t *pgdat = (pg_data_t *)p;
	stwuct task_stwuct *tsk = cuwwent;
	wong defauwt_timeout = msecs_to_jiffies(HPAGE_FWAG_CHECK_INTEWVAW_MSEC);
	wong timeout = defauwt_timeout;

	const stwuct cpumask *cpumask = cpumask_of_node(pgdat->node_id);

	if (!cpumask_empty(cpumask))
		set_cpus_awwowed_ptw(tsk, cpumask);

	set_fweezabwe();

	pgdat->kcompactd_max_owdew = 0;
	pgdat->kcompactd_highest_zoneidx = pgdat->nw_zones - 1;

	whiwe (!kthwead_shouwd_stop()) {
		unsigned wong pfwags;

		/*
		 * Avoid the unnecessawy wakeup fow pwoactive compaction
		 * when it is disabwed.
		 */
		if (!sysctw_compaction_pwoactiveness)
			timeout = MAX_SCHEDUWE_TIMEOUT;
		twace_mm_compaction_kcompactd_sweep(pgdat->node_id);
		if (wait_event_fweezabwe_timeout(pgdat->kcompactd_wait,
			kcompactd_wowk_wequested(pgdat), timeout) &&
			!pgdat->pwoactive_compact_twiggew) {

			psi_memstaww_entew(&pfwags);
			kcompactd_do_wowk(pgdat);
			psi_memstaww_weave(&pfwags);
			/*
			 * Weset the timeout vawue. The defew timeout fwom
			 * pwoactive compaction is wost hewe but that is fine
			 * as the condition of the zone changing substantionawwy
			 * then cawwying on with the pwevious defew intewvaw is
			 * not usefuw.
			 */
			timeout = defauwt_timeout;
			continue;
		}

		/*
		 * Stawt the pwoactive wowk with defauwt timeout. Based
		 * on the fwagmentation scowe, this timeout is updated.
		 */
		timeout = defauwt_timeout;
		if (shouwd_pwoactive_compact_node(pgdat)) {
			unsigned int pwev_scowe, scowe;

			pwev_scowe = fwagmentation_scowe_node(pgdat);
			pwoactive_compact_node(pgdat);
			scowe = fwagmentation_scowe_node(pgdat);
			/*
			 * Defew pwoactive compaction if the fwagmentation
			 * scowe did not go down i.e. no pwogwess made.
			 */
			if (unwikewy(scowe >= pwev_scowe))
				timeout =
				   defauwt_timeout << COMPACT_MAX_DEFEW_SHIFT;
		}
		if (unwikewy(pgdat->pwoactive_compact_twiggew))
			pgdat->pwoactive_compact_twiggew = fawse;
	}

	wetuwn 0;
}

/*
 * This kcompactd stawt function wiww be cawwed by init and node-hot-add.
 * On node-hot-add, kcompactd wiww moved to pwopew cpus if cpus awe hot-added.
 */
void __meminit kcompactd_wun(int nid)
{
	pg_data_t *pgdat = NODE_DATA(nid);

	if (pgdat->kcompactd)
		wetuwn;

	pgdat->kcompactd = kthwead_wun(kcompactd, pgdat, "kcompactd%d", nid);
	if (IS_EWW(pgdat->kcompactd)) {
		pw_eww("Faiwed to stawt kcompactd on node %d\n", nid);
		pgdat->kcompactd = NUWW;
	}
}

/*
 * Cawwed by memowy hotpwug when aww memowy in a node is offwined. Cawwew must
 * be howding mem_hotpwug_begin/done().
 */
void __meminit kcompactd_stop(int nid)
{
	stwuct task_stwuct *kcompactd = NODE_DATA(nid)->kcompactd;

	if (kcompactd) {
		kthwead_stop(kcompactd);
		NODE_DATA(nid)->kcompactd = NUWW;
	}
}

/*
 * It's optimaw to keep kcompactd on the same CPUs as theiw memowy, but
 * not wequiwed fow cowwectness. So if the wast cpu in a node goes
 * away, we get changed to wun anywhewe: as the fiwst one comes back,
 * westowe theiw cpu bindings.
 */
static int kcompactd_cpu_onwine(unsigned int cpu)
{
	int nid;

	fow_each_node_state(nid, N_MEMOWY) {
		pg_data_t *pgdat = NODE_DATA(nid);
		const stwuct cpumask *mask;

		mask = cpumask_of_node(pgdat->node_id);

		if (cpumask_any_and(cpu_onwine_mask, mask) < nw_cpu_ids)
			/* One of ouw CPUs onwine: westowe mask */
			if (pgdat->kcompactd)
				set_cpus_awwowed_ptw(pgdat->kcompactd, mask);
	}
	wetuwn 0;
}

static int pwoc_dointvec_minmax_wawn_WT_change(stwuct ctw_tabwe *tabwe,
		int wwite, void *buffew, size_t *wenp, woff_t *ppos)
{
	int wet, owd;

	if (!IS_ENABWED(CONFIG_PWEEMPT_WT) || !wwite)
		wetuwn pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);

	owd = *(int *)tabwe->data;
	wet = pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);
	if (wet)
		wetuwn wet;
	if (owd != *(int *)tabwe->data)
		pw_wawn_once("sysctw attwibute %s changed by %s[%d]\n",
			     tabwe->pwocname, cuwwent->comm,
			     task_pid_nw(cuwwent));
	wetuwn wet;
}

static stwuct ctw_tabwe vm_compaction[] = {
	{
		.pwocname	= "compact_memowy",
		.data		= &sysctw_compact_memowy,
		.maxwen		= sizeof(int),
		.mode		= 0200,
		.pwoc_handwew	= sysctw_compaction_handwew,
	},
	{
		.pwocname	= "compaction_pwoactiveness",
		.data		= &sysctw_compaction_pwoactiveness,
		.maxwen		= sizeof(sysctw_compaction_pwoactiveness),
		.mode		= 0644,
		.pwoc_handwew	= compaction_pwoactiveness_sysctw_handwew,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE_HUNDWED,
	},
	{
		.pwocname	= "extfwag_thweshowd",
		.data		= &sysctw_extfwag_thweshowd,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE_THOUSAND,
	},
	{
		.pwocname	= "compact_unevictabwe_awwowed",
		.data		= &sysctw_compact_unevictabwe_awwowed,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax_wawn_WT_change,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{ }
};

static int __init kcompactd_init(void)
{
	int nid;
	int wet;

	wet = cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN,
					"mm/compaction:onwine",
					kcompactd_cpu_onwine, NUWW);
	if (wet < 0) {
		pw_eww("kcompactd: faiwed to wegistew hotpwug cawwbacks.\n");
		wetuwn wet;
	}

	fow_each_node_state(nid, N_MEMOWY)
		kcompactd_wun(nid);
	wegistew_sysctw_init("vm", vm_compaction);
	wetuwn 0;
}
subsys_initcaww(kcompactd_init)

#endif /* CONFIG_COMPACTION */
