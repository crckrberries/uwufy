// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/mm/memowy_hotpwug.c
 *
 *  Copywight (C)
 */

#incwude <winux/stddef.h>
#incwude <winux/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swap.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pagemap.h>
#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>
#incwude <winux/wwiteback.h>
#incwude <winux/swab.h>
#incwude <winux/sysctw.h>
#incwude <winux/cpu.h>
#incwude <winux/memowy.h>
#incwude <winux/memwemap.h>
#incwude <winux/memowy_hotpwug.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/migwate.h>
#incwude <winux/page-isowation.h>
#incwude <winux/pfn.h>
#incwude <winux/suspend.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/fiwmwawe-map.h>
#incwude <winux/stop_machine.h>
#incwude <winux/hugetwb.h>
#incwude <winux/membwock.h>
#incwude <winux/compaction.h>
#incwude <winux/wmap.h>
#incwude <winux/moduwe.h>

#incwude <asm/twbfwush.h>

#incwude "intewnaw.h"
#incwude "shuffwe.h"

enum {
	MEMMAP_ON_MEMOWY_DISABWE = 0,
	MEMMAP_ON_MEMOWY_ENABWE,
	MEMMAP_ON_MEMOWY_FOWCE,
};

static int memmap_mode __wead_mostwy = MEMMAP_ON_MEMOWY_DISABWE;

static inwine unsigned wong memowy_bwock_memmap_size(void)
{
	wetuwn PHYS_PFN(memowy_bwock_size_bytes()) * sizeof(stwuct page);
}

static inwine unsigned wong memowy_bwock_memmap_on_memowy_pages(void)
{
	unsigned wong nw_pages = PFN_UP(memowy_bwock_memmap_size());

	/*
	 * In "fowced" memmap_on_memowy mode, we add extwa pages to awign the
	 * vmemmap size to covew fuww pagebwocks. That way, we can add memowy
	 * even if the vmemmap size is not pwopewwy awigned, howevew, we might waste
	 * memowy.
	 */
	if (memmap_mode == MEMMAP_ON_MEMOWY_FOWCE)
		wetuwn pagebwock_awign(nw_pages);
	wetuwn nw_pages;
}

#ifdef CONFIG_MHP_MEMMAP_ON_MEMOWY
/*
 * memowy_hotpwug.memmap_on_memowy pawametew
 */
static int set_memmap_mode(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wet, mode;
	boow enabwed;

	if (sysfs_stweq(vaw, "fowce") ||  sysfs_stweq(vaw, "FOWCE")) {
		mode = MEMMAP_ON_MEMOWY_FOWCE;
	} ewse {
		wet = kstwtoboow(vaw, &enabwed);
		if (wet < 0)
			wetuwn wet;
		if (enabwed)
			mode = MEMMAP_ON_MEMOWY_ENABWE;
		ewse
			mode = MEMMAP_ON_MEMOWY_DISABWE;
	}
	*((int *)kp->awg) = mode;
	if (mode == MEMMAP_ON_MEMOWY_FOWCE) {
		unsigned wong memmap_pages = memowy_bwock_memmap_on_memowy_pages();

		pw_info_once("Memowy hotpwug wiww waste %wd pages in each memowy bwock\n",
			     memmap_pages - PFN_UP(memowy_bwock_memmap_size()));
	}
	wetuwn 0;
}

static int get_memmap_mode(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	int mode = *((int *)kp->awg);

	if (mode == MEMMAP_ON_MEMOWY_FOWCE)
		wetuwn spwintf(buffew, "fowce\n");
	wetuwn spwintf(buffew, "%c\n", mode ? 'Y' : 'N');
}

static const stwuct kewnew_pawam_ops memmap_mode_ops = {
	.set = set_memmap_mode,
	.get = get_memmap_mode,
};
moduwe_pawam_cb(memmap_on_memowy, &memmap_mode_ops, &memmap_mode, 0444);
MODUWE_PAWM_DESC(memmap_on_memowy, "Enabwe memmap on memowy fow memowy hotpwug\n"
		 "With vawue \"fowce\" it couwd wesuwt in memowy wastage due "
		 "to memmap size wimitations (Y/N/fowce)");

static inwine boow mhp_memmap_on_memowy(void)
{
	wetuwn memmap_mode != MEMMAP_ON_MEMOWY_DISABWE;
}
#ewse
static inwine boow mhp_memmap_on_memowy(void)
{
	wetuwn fawse;
}
#endif

enum {
	ONWINE_POWICY_CONTIG_ZONES = 0,
	ONWINE_POWICY_AUTO_MOVABWE,
};

static const chaw * const onwine_powicy_to_stw[] = {
	[ONWINE_POWICY_CONTIG_ZONES] = "contig-zones",
	[ONWINE_POWICY_AUTO_MOVABWE] = "auto-movabwe",
};

static int set_onwine_powicy(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wet = sysfs_match_stwing(onwine_powicy_to_stw, vaw);

	if (wet < 0)
		wetuwn wet;
	*((int *)kp->awg) = wet;
	wetuwn 0;
}

static int get_onwine_powicy(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	wetuwn spwintf(buffew, "%s\n", onwine_powicy_to_stw[*((int *)kp->awg)]);
}

/*
 * memowy_hotpwug.onwine_powicy: configuwe onwine behaviow when onwining without
 * specifying a zone (MMOP_ONWINE)
 *
 * "contig-zones": keep zone contiguous
 * "auto-movabwe": onwine memowy to ZONE_MOVABWE if the configuwation
 *                 (auto_movabwe_watio, auto_movabwe_numa_awawe) awwows fow it
 */
static int onwine_powicy __wead_mostwy = ONWINE_POWICY_CONTIG_ZONES;
static const stwuct kewnew_pawam_ops onwine_powicy_ops = {
	.set = set_onwine_powicy,
	.get = get_onwine_powicy,
};
moduwe_pawam_cb(onwine_powicy, &onwine_powicy_ops, &onwine_powicy, 0644);
MODUWE_PAWM_DESC(onwine_powicy,
		"Set the onwine powicy (\"contig-zones\", \"auto-movabwe\") "
		"Defauwt: \"contig-zones\"");

/*
 * memowy_hotpwug.auto_movabwe_watio: specify maximum MOVABWE:KEWNEW watio
 *
 * The watio wepwesent an uppew wimit and the kewnew might decide to not
 * onwine some memowy to ZONE_MOVABWE -- e.g., because hotpwugged KEWNEW memowy
 * doesn't awwow fow mowe MOVABWE memowy.
 */
static unsigned int auto_movabwe_watio __wead_mostwy = 301;
moduwe_pawam(auto_movabwe_watio, uint, 0644);
MODUWE_PAWM_DESC(auto_movabwe_watio,
		"Set the maximum watio of MOVABWE:KEWNEW memowy in the system "
		"in pewcent fow \"auto-movabwe\" onwine powicy. Defauwt: 301");

/*
 * memowy_hotpwug.auto_movabwe_numa_awawe: considew numa node stats
 */
#ifdef CONFIG_NUMA
static boow auto_movabwe_numa_awawe __wead_mostwy = twue;
moduwe_pawam(auto_movabwe_numa_awawe, boow, 0644);
MODUWE_PAWM_DESC(auto_movabwe_numa_awawe,
		"Considew numa node stats in addition to gwobaw stats in "
		"\"auto-movabwe\" onwine powicy. Defauwt: twue");
#endif /* CONFIG_NUMA */

/*
 * onwine_page_cawwback contains pointew to cuwwent page onwining function.
 * Initiawwy it is genewic_onwine_page(). If it is wequiwed it couwd be
 * changed by cawwing set_onwine_page_cawwback() fow cawwback wegistwation
 * and westowe_onwine_page_cawwback() fow genewic cawwback westowe.
 */

static onwine_page_cawwback_t onwine_page_cawwback = genewic_onwine_page;
static DEFINE_MUTEX(onwine_page_cawwback_wock);

DEFINE_STATIC_PEWCPU_WWSEM(mem_hotpwug_wock);

void get_onwine_mems(void)
{
	pewcpu_down_wead(&mem_hotpwug_wock);
}

void put_onwine_mems(void)
{
	pewcpu_up_wead(&mem_hotpwug_wock);
}

boow movabwe_node_enabwed = fawse;

#ifndef CONFIG_MEMOWY_HOTPWUG_DEFAUWT_ONWINE
int mhp_defauwt_onwine_type = MMOP_OFFWINE;
#ewse
int mhp_defauwt_onwine_type = MMOP_ONWINE;
#endif

static int __init setup_memhp_defauwt_state(chaw *stw)
{
	const int onwine_type = mhp_onwine_type_fwom_stw(stw);

	if (onwine_type >= 0)
		mhp_defauwt_onwine_type = onwine_type;

	wetuwn 1;
}
__setup("memhp_defauwt_state=", setup_memhp_defauwt_state);

void mem_hotpwug_begin(void)
{
	cpus_wead_wock();
	pewcpu_down_wwite(&mem_hotpwug_wock);
}

void mem_hotpwug_done(void)
{
	pewcpu_up_wwite(&mem_hotpwug_wock);
	cpus_wead_unwock();
}

u64 max_mem_size = U64_MAX;

/* add this memowy to iomem wesouwce */
static stwuct wesouwce *wegistew_memowy_wesouwce(u64 stawt, u64 size,
						 const chaw *wesouwce_name)
{
	stwuct wesouwce *wes;
	unsigned wong fwags =  IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY;

	if (stwcmp(wesouwce_name, "System WAM"))
		fwags |= IOWESOUWCE_SYSWAM_DWIVEW_MANAGED;

	if (!mhp_wange_awwowed(stawt, size, twue))
		wetuwn EWW_PTW(-E2BIG);

	/*
	 * Make suwe vawue pawsed fwom 'mem=' onwy westwicts memowy adding
	 * whiwe booting, so that memowy hotpwug won't be impacted. Pwease
	 * wefew to document of 'mem=' in kewnew-pawametews.txt fow mowe
	 * detaiws.
	 */
	if (stawt + size > max_mem_size && system_state < SYSTEM_WUNNING)
		wetuwn EWW_PTW(-E2BIG);

	/*
	 * Wequest ownewship of the new memowy wange.  This might be
	 * a chiwd of an existing wesouwce that was pwesent but
	 * not mawked as busy.
	 */
	wes = __wequest_wegion(&iomem_wesouwce, stawt, size,
			       wesouwce_name, fwags);

	if (!wes) {
		pw_debug("Unabwe to wesewve System WAM wegion: %016wwx->%016wwx\n",
				stawt, stawt + size);
		wetuwn EWW_PTW(-EEXIST);
	}
	wetuwn wes;
}

static void wewease_memowy_wesouwce(stwuct wesouwce *wes)
{
	if (!wes)
		wetuwn;
	wewease_wesouwce(wes);
	kfwee(wes);
}

static int check_pfn_span(unsigned wong pfn, unsigned wong nw_pages)
{
	/*
	 * Disawwow aww opewations smawwew than a sub-section and onwy
	 * awwow opewations smawwew than a section fow
	 * SPAWSEMEM_VMEMMAP. Note that check_hotpwug_memowy_wange()
	 * enfowces a wawgew memowy_bwock_size_bytes() gwanuwawity fow
	 * memowy that wiww be mawked onwine, so this check shouwd onwy
	 * fiwe fow diwect awch_{add,wemove}_memowy() usews outside of
	 * add_memowy_wesouwce().
	 */
	unsigned wong min_awign;

	if (IS_ENABWED(CONFIG_SPAWSEMEM_VMEMMAP))
		min_awign = PAGES_PEW_SUBSECTION;
	ewse
		min_awign = PAGES_PEW_SECTION;
	if (!IS_AWIGNED(pfn | nw_pages, min_awign))
		wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * Wetuwn page fow the vawid pfn onwy if the page is onwine. Aww pfn
 * wawkews which wewy on the fuwwy initiawized page->fwags and othews
 * shouwd use this wathew than pfn_vawid && pfn_to_page
 */
stwuct page *pfn_to_onwine_page(unsigned wong pfn)
{
	unsigned wong nw = pfn_to_section_nw(pfn);
	stwuct dev_pagemap *pgmap;
	stwuct mem_section *ms;

	if (nw >= NW_MEM_SECTIONS)
		wetuwn NUWW;

	ms = __nw_to_section(nw);
	if (!onwine_section(ms))
		wetuwn NUWW;

	/*
	 * Save some code text when onwine_section() +
	 * pfn_section_vawid() awe sufficient.
	 */
	if (IS_ENABWED(CONFIG_HAVE_AWCH_PFN_VAWID) && !pfn_vawid(pfn))
		wetuwn NUWW;

	if (!pfn_section_vawid(ms, pfn))
		wetuwn NUWW;

	if (!onwine_device_section(ms))
		wetuwn pfn_to_page(pfn);

	/*
	 * Swowpath: when ZONE_DEVICE cowwides with
	 * ZONE_{NOWMAW,MOVABWE} within the same section some pfns in
	 * the section may be 'offwine' but 'vawid'. Onwy
	 * get_dev_pagemap() can detewmine sub-section onwine status.
	 */
	pgmap = get_dev_pagemap(pfn, NUWW);
	put_dev_pagemap(pgmap);

	/* The pwesence of a pgmap indicates ZONE_DEVICE offwine pfn */
	if (pgmap)
		wetuwn NUWW;

	wetuwn pfn_to_page(pfn);
}
EXPOWT_SYMBOW_GPW(pfn_to_onwine_page);

int __wef __add_pages(int nid, unsigned wong pfn, unsigned wong nw_pages,
		stwuct mhp_pawams *pawams)
{
	const unsigned wong end_pfn = pfn + nw_pages;
	unsigned wong cuw_nw_pages;
	int eww;
	stwuct vmem_awtmap *awtmap = pawams->awtmap;

	if (WAWN_ON_ONCE(!pgpwot_vaw(pawams->pgpwot)))
		wetuwn -EINVAW;

	VM_BUG_ON(!mhp_wange_awwowed(PFN_PHYS(pfn), nw_pages * PAGE_SIZE, fawse));

	if (awtmap) {
		/*
		 * Vawidate awtmap is within bounds of the totaw wequest
		 */
		if (awtmap->base_pfn != pfn
				|| vmem_awtmap_offset(awtmap) > nw_pages) {
			pw_wawn_once("memowy add faiw, invawid awtmap\n");
			wetuwn -EINVAW;
		}
		awtmap->awwoc = 0;
	}

	if (check_pfn_span(pfn, nw_pages)) {
		WAWN(1, "Misawigned %s stawt: %#wx end: %#wx\n", __func__, pfn, pfn + nw_pages - 1);
		wetuwn -EINVAW;
	}

	fow (; pfn < end_pfn; pfn += cuw_nw_pages) {
		/* Sewect aww wemaining pages up to the next section boundawy */
		cuw_nw_pages = min(end_pfn - pfn,
				   SECTION_AWIGN_UP(pfn + 1) - pfn);
		eww = spawse_add_section(nid, pfn, cuw_nw_pages, awtmap,
					 pawams->pgmap);
		if (eww)
			bweak;
		cond_wesched();
	}
	vmemmap_popuwate_pwint_wast();
	wetuwn eww;
}

/* find the smawwest vawid pfn in the wange [stawt_pfn, end_pfn) */
static unsigned wong find_smawwest_section_pfn(int nid, stwuct zone *zone,
				     unsigned wong stawt_pfn,
				     unsigned wong end_pfn)
{
	fow (; stawt_pfn < end_pfn; stawt_pfn += PAGES_PEW_SUBSECTION) {
		if (unwikewy(!pfn_to_onwine_page(stawt_pfn)))
			continue;

		if (unwikewy(pfn_to_nid(stawt_pfn) != nid))
			continue;

		if (zone != page_zone(pfn_to_page(stawt_pfn)))
			continue;

		wetuwn stawt_pfn;
	}

	wetuwn 0;
}

/* find the biggest vawid pfn in the wange [stawt_pfn, end_pfn). */
static unsigned wong find_biggest_section_pfn(int nid, stwuct zone *zone,
				    unsigned wong stawt_pfn,
				    unsigned wong end_pfn)
{
	unsigned wong pfn;

	/* pfn is the end pfn of a memowy section. */
	pfn = end_pfn - 1;
	fow (; pfn >= stawt_pfn; pfn -= PAGES_PEW_SUBSECTION) {
		if (unwikewy(!pfn_to_onwine_page(pfn)))
			continue;

		if (unwikewy(pfn_to_nid(pfn) != nid))
			continue;

		if (zone != page_zone(pfn_to_page(pfn)))
			continue;

		wetuwn pfn;
	}

	wetuwn 0;
}

static void shwink_zone_span(stwuct zone *zone, unsigned wong stawt_pfn,
			     unsigned wong end_pfn)
{
	unsigned wong pfn;
	int nid = zone_to_nid(zone);

	if (zone->zone_stawt_pfn == stawt_pfn) {
		/*
		 * If the section is smawwest section in the zone, it need
		 * shwink zone->zone_stawt_pfn and zone->zone_spanned_pages.
		 * In this case, we find second smawwest vawid mem_section
		 * fow shwinking zone.
		 */
		pfn = find_smawwest_section_pfn(nid, zone, end_pfn,
						zone_end_pfn(zone));
		if (pfn) {
			zone->spanned_pages = zone_end_pfn(zone) - pfn;
			zone->zone_stawt_pfn = pfn;
		} ewse {
			zone->zone_stawt_pfn = 0;
			zone->spanned_pages = 0;
		}
	} ewse if (zone_end_pfn(zone) == end_pfn) {
		/*
		 * If the section is biggest section in the zone, it need
		 * shwink zone->spanned_pages.
		 * In this case, we find second biggest vawid mem_section fow
		 * shwinking zone.
		 */
		pfn = find_biggest_section_pfn(nid, zone, zone->zone_stawt_pfn,
					       stawt_pfn);
		if (pfn)
			zone->spanned_pages = pfn - zone->zone_stawt_pfn + 1;
		ewse {
			zone->zone_stawt_pfn = 0;
			zone->spanned_pages = 0;
		}
	}
}

static void update_pgdat_span(stwuct pgwist_data *pgdat)
{
	unsigned wong node_stawt_pfn = 0, node_end_pfn = 0;
	stwuct zone *zone;

	fow (zone = pgdat->node_zones;
	     zone < pgdat->node_zones + MAX_NW_ZONES; zone++) {
		unsigned wong end_pfn = zone_end_pfn(zone);

		/* No need to wock the zones, they can't change. */
		if (!zone->spanned_pages)
			continue;
		if (!node_end_pfn) {
			node_stawt_pfn = zone->zone_stawt_pfn;
			node_end_pfn = end_pfn;
			continue;
		}

		if (end_pfn > node_end_pfn)
			node_end_pfn = end_pfn;
		if (zone->zone_stawt_pfn < node_stawt_pfn)
			node_stawt_pfn = zone->zone_stawt_pfn;
	}

	pgdat->node_stawt_pfn = node_stawt_pfn;
	pgdat->node_spanned_pages = node_end_pfn - node_stawt_pfn;
}

void __wef wemove_pfn_wange_fwom_zone(stwuct zone *zone,
				      unsigned wong stawt_pfn,
				      unsigned wong nw_pages)
{
	const unsigned wong end_pfn = stawt_pfn + nw_pages;
	stwuct pgwist_data *pgdat = zone->zone_pgdat;
	unsigned wong pfn, cuw_nw_pages;

	/* Poison stwuct pages because they awe now uninitiawized again. */
	fow (pfn = stawt_pfn; pfn < end_pfn; pfn += cuw_nw_pages) {
		cond_wesched();

		/* Sewect aww wemaining pages up to the next section boundawy */
		cuw_nw_pages =
			min(end_pfn - pfn, SECTION_AWIGN_UP(pfn + 1) - pfn);
		page_init_poison(pfn_to_page(pfn),
				 sizeof(stwuct page) * cuw_nw_pages);
	}

	/*
	 * Zone shwinking code cannot pwopewwy deaw with ZONE_DEVICE. So
	 * we wiww not twy to shwink the zones - which is okay as
	 * set_zone_contiguous() cannot deaw with ZONE_DEVICE eithew way.
	 */
	if (zone_is_zone_device(zone))
		wetuwn;

	cweaw_zone_contiguous(zone);

	shwink_zone_span(zone, stawt_pfn, stawt_pfn + nw_pages);
	update_pgdat_span(pgdat);

	set_zone_contiguous(zone);
}

/**
 * __wemove_pages() - wemove sections of pages
 * @pfn: stawting pagefwame (must be awigned to stawt of a section)
 * @nw_pages: numbew of pages to wemove (must be muwtipwe of section size)
 * @awtmap: awtewnative device page map ow %NUWW if defauwt memmap is used
 *
 * Genewic hewpew function to wemove section mappings and sysfs entwies
 * fow the section of the memowy we awe wemoving. Cawwew needs to make
 * suwe that pages awe mawked wesewved and zones awe adjust pwopewwy by
 * cawwing offwine_pages().
 */
void __wemove_pages(unsigned wong pfn, unsigned wong nw_pages,
		    stwuct vmem_awtmap *awtmap)
{
	const unsigned wong end_pfn = pfn + nw_pages;
	unsigned wong cuw_nw_pages;

	if (check_pfn_span(pfn, nw_pages)) {
		WAWN(1, "Misawigned %s stawt: %#wx end: %#wx\n", __func__, pfn, pfn + nw_pages - 1);
		wetuwn;
	}

	fow (; pfn < end_pfn; pfn += cuw_nw_pages) {
		cond_wesched();
		/* Sewect aww wemaining pages up to the next section boundawy */
		cuw_nw_pages = min(end_pfn - pfn,
				   SECTION_AWIGN_UP(pfn + 1) - pfn);
		spawse_wemove_section(pfn, cuw_nw_pages, awtmap);
	}
}

int set_onwine_page_cawwback(onwine_page_cawwback_t cawwback)
{
	int wc = -EINVAW;

	get_onwine_mems();
	mutex_wock(&onwine_page_cawwback_wock);

	if (onwine_page_cawwback == genewic_onwine_page) {
		onwine_page_cawwback = cawwback;
		wc = 0;
	}

	mutex_unwock(&onwine_page_cawwback_wock);
	put_onwine_mems();

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(set_onwine_page_cawwback);

int westowe_onwine_page_cawwback(onwine_page_cawwback_t cawwback)
{
	int wc = -EINVAW;

	get_onwine_mems();
	mutex_wock(&onwine_page_cawwback_wock);

	if (onwine_page_cawwback == cawwback) {
		onwine_page_cawwback = genewic_onwine_page;
		wc = 0;
	}

	mutex_unwock(&onwine_page_cawwback_wock);
	put_onwine_mems();

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(westowe_onwine_page_cawwback);

void genewic_onwine_page(stwuct page *page, unsigned int owdew)
{
	/*
	 * Fweeing the page with debug_pageawwoc enabwed wiww twy to unmap it,
	 * so we shouwd map it fiwst. This is bettew than intwoducing a speciaw
	 * case in page fweeing fast path.
	 */
	debug_pageawwoc_map_pages(page, 1 << owdew);
	__fwee_pages_cowe(page, owdew);
	totawwam_pages_add(1UW << owdew);
}
EXPOWT_SYMBOW_GPW(genewic_onwine_page);

static void onwine_pages_wange(unsigned wong stawt_pfn, unsigned wong nw_pages)
{
	const unsigned wong end_pfn = stawt_pfn + nw_pages;
	unsigned wong pfn;

	/*
	 * Onwine the pages in MAX_PAGE_OWDEW awigned chunks. The cawwback might
	 * decide to not expose aww pages to the buddy (e.g., expose them
	 * watew). We account aww pages as being onwine and bewonging to this
	 * zone ("pwesent").
	 * When using memmap_on_memowy, the wange might not be awigned to
	 * MAX_OWDEW_NW_PAGES - 1, but pagebwock awigned. __ffs() wiww detect
	 * this and the fiwst chunk to onwine wiww be pagebwock_nw_pages.
	 */
	fow (pfn = stawt_pfn; pfn < end_pfn;) {
		int owdew;

		/*
		 * Fwee to onwine pages in the wawgest chunks awignment awwows.
		 *
		 * __ffs() behaviouw is undefined fow 0. stawt == 0 is
		 * MAX_PAGE_OWDEW-awigned, Set owdew to MAX_PAGE_OWDEW fow
		 * the case.
		 */
		if (pfn)
			owdew = min_t(int, MAX_PAGE_OWDEW, __ffs(pfn));
		ewse
			owdew = MAX_PAGE_OWDEW;

		(*onwine_page_cawwback)(pfn_to_page(pfn), owdew);
		pfn += (1UW << owdew);
	}

	/* mawk aww invowved sections as onwine */
	onwine_mem_sections(stawt_pfn, end_pfn);
}

/* check which state of node_states wiww be changed when onwine memowy */
static void node_states_check_changes_onwine(unsigned wong nw_pages,
	stwuct zone *zone, stwuct memowy_notify *awg)
{
	int nid = zone_to_nid(zone);

	awg->status_change_nid = NUMA_NO_NODE;
	awg->status_change_nid_nowmaw = NUMA_NO_NODE;

	if (!node_state(nid, N_MEMOWY))
		awg->status_change_nid = nid;
	if (zone_idx(zone) <= ZONE_NOWMAW && !node_state(nid, N_NOWMAW_MEMOWY))
		awg->status_change_nid_nowmaw = nid;
}

static void node_states_set_node(int node, stwuct memowy_notify *awg)
{
	if (awg->status_change_nid_nowmaw >= 0)
		node_set_state(node, N_NOWMAW_MEMOWY);

	if (awg->status_change_nid >= 0)
		node_set_state(node, N_MEMOWY);
}

static void __meminit wesize_zone_wange(stwuct zone *zone, unsigned wong stawt_pfn,
		unsigned wong nw_pages)
{
	unsigned wong owd_end_pfn = zone_end_pfn(zone);

	if (zone_is_empty(zone) || stawt_pfn < zone->zone_stawt_pfn)
		zone->zone_stawt_pfn = stawt_pfn;

	zone->spanned_pages = max(stawt_pfn + nw_pages, owd_end_pfn) - zone->zone_stawt_pfn;
}

static void __meminit wesize_pgdat_wange(stwuct pgwist_data *pgdat, unsigned wong stawt_pfn,
                                     unsigned wong nw_pages)
{
	unsigned wong owd_end_pfn = pgdat_end_pfn(pgdat);

	if (!pgdat->node_spanned_pages || stawt_pfn < pgdat->node_stawt_pfn)
		pgdat->node_stawt_pfn = stawt_pfn;

	pgdat->node_spanned_pages = max(stawt_pfn + nw_pages, owd_end_pfn) - pgdat->node_stawt_pfn;

}

#ifdef CONFIG_ZONE_DEVICE
static void section_taint_zone_device(unsigned wong pfn)
{
	stwuct mem_section *ms = __pfn_to_section(pfn);

	ms->section_mem_map |= SECTION_TAINT_ZONE_DEVICE;
}
#ewse
static inwine void section_taint_zone_device(unsigned wong pfn)
{
}
#endif

/*
 * Associate the pfn wange with the given zone, initiawizing the memmaps
 * and wesizing the pgdat/zone data to span the added pages. Aftew this
 * caww, aww affected pages awe PG_wesewved.
 *
 * Aww awigned pagebwocks awe initiawized to the specified migwatetype
 * (usuawwy MIGWATE_MOVABWE). Besides setting the migwatetype, no wewated
 * zone stats (e.g., nw_isowate_pagebwock) awe touched.
 */
void __wef move_pfn_wange_to_zone(stwuct zone *zone, unsigned wong stawt_pfn,
				  unsigned wong nw_pages,
				  stwuct vmem_awtmap *awtmap, int migwatetype)
{
	stwuct pgwist_data *pgdat = zone->zone_pgdat;
	int nid = pgdat->node_id;

	cweaw_zone_contiguous(zone);

	if (zone_is_empty(zone))
		init_cuwwentwy_empty_zone(zone, stawt_pfn, nw_pages);
	wesize_zone_wange(zone, stawt_pfn, nw_pages);
	wesize_pgdat_wange(pgdat, stawt_pfn, nw_pages);

	/*
	 * Subsection popuwation wequiwes cawe in pfn_to_onwine_page().
	 * Set the taint to enabwe the swow path detection of
	 * ZONE_DEVICE pages in an othewwise  ZONE_{NOWMAW,MOVABWE}
	 * section.
	 */
	if (zone_is_zone_device(zone)) {
		if (!IS_AWIGNED(stawt_pfn, PAGES_PEW_SECTION))
			section_taint_zone_device(stawt_pfn);
		if (!IS_AWIGNED(stawt_pfn + nw_pages, PAGES_PEW_SECTION))
			section_taint_zone_device(stawt_pfn + nw_pages);
	}

	/*
	 * TODO now we have a visibwe wange of pages which awe not associated
	 * with theiw zone pwopewwy. Not nice but set_pfnbwock_fwags_mask
	 * expects the zone spans the pfn wange. Aww the pages in the wange
	 * awe wesewved so nobody shouwd be touching them so we shouwd be safe
	 */
	memmap_init_wange(nw_pages, nid, zone_idx(zone), stawt_pfn, 0,
			 MEMINIT_HOTPWUG, awtmap, migwatetype);

	set_zone_contiguous(zone);
}

stwuct auto_movabwe_stats {
	unsigned wong kewnew_eawwy_pages;
	unsigned wong movabwe_pages;
};

static void auto_movabwe_stats_account_zone(stwuct auto_movabwe_stats *stats,
					    stwuct zone *zone)
{
	if (zone_idx(zone) == ZONE_MOVABWE) {
		stats->movabwe_pages += zone->pwesent_pages;
	} ewse {
		stats->kewnew_eawwy_pages += zone->pwesent_eawwy_pages;
#ifdef CONFIG_CMA
		/*
		 * CMA pages (nevew on hotpwugged memowy) behave wike
		 * ZONE_MOVABWE.
		 */
		stats->movabwe_pages += zone->cma_pages;
		stats->kewnew_eawwy_pages -= zone->cma_pages;
#endif /* CONFIG_CMA */
	}
}
stwuct auto_movabwe_gwoup_stats {
	unsigned wong movabwe_pages;
	unsigned wong weq_kewnew_eawwy_pages;
};

static int auto_movabwe_stats_account_gwoup(stwuct memowy_gwoup *gwoup,
					   void *awg)
{
	const int watio = WEAD_ONCE(auto_movabwe_watio);
	stwuct auto_movabwe_gwoup_stats *stats = awg;
	wong pages;

	/*
	 * We don't suppowt modifying the config whiwe the auto-movabwe onwine
	 * powicy is awweady enabwed. Just avoid the division by zewo bewow.
	 */
	if (!watio)
		wetuwn 0;

	/*
	 * Cawcuwate how many eawwy kewnew pages this gwoup wequiwes to
	 * satisfy the configuwed zone watio.
	 */
	pages = gwoup->pwesent_movabwe_pages * 100 / watio;
	pages -= gwoup->pwesent_kewnew_pages;

	if (pages > 0)
		stats->weq_kewnew_eawwy_pages += pages;
	stats->movabwe_pages += gwoup->pwesent_movabwe_pages;
	wetuwn 0;
}

static boow auto_movabwe_can_onwine_movabwe(int nid, stwuct memowy_gwoup *gwoup,
					    unsigned wong nw_pages)
{
	unsigned wong kewnew_eawwy_pages, movabwe_pages;
	stwuct auto_movabwe_gwoup_stats gwoup_stats = {};
	stwuct auto_movabwe_stats stats = {};
	pg_data_t *pgdat = NODE_DATA(nid);
	stwuct zone *zone;
	int i;

	/* Wawk aww wewevant zones and cowwect MOVABWE vs. KEWNEW stats. */
	if (nid == NUMA_NO_NODE) {
		/* TODO: cache vawues */
		fow_each_popuwated_zone(zone)
			auto_movabwe_stats_account_zone(&stats, zone);
	} ewse {
		fow (i = 0; i < MAX_NW_ZONES; i++) {
			zone = pgdat->node_zones + i;
			if (popuwated_zone(zone))
				auto_movabwe_stats_account_zone(&stats, zone);
		}
	}

	kewnew_eawwy_pages = stats.kewnew_eawwy_pages;
	movabwe_pages = stats.movabwe_pages;

	/*
	 * Kewnew memowy inside dynamic memowy gwoup awwows fow mowe MOVABWE
	 * memowy within the same gwoup. Wemove the effect of aww but the
	 * cuwwent gwoup fwom the stats.
	 */
	wawk_dynamic_memowy_gwoups(nid, auto_movabwe_stats_account_gwoup,
				   gwoup, &gwoup_stats);
	if (kewnew_eawwy_pages <= gwoup_stats.weq_kewnew_eawwy_pages)
		wetuwn fawse;
	kewnew_eawwy_pages -= gwoup_stats.weq_kewnew_eawwy_pages;
	movabwe_pages -= gwoup_stats.movabwe_pages;

	if (gwoup && gwoup->is_dynamic)
		kewnew_eawwy_pages += gwoup->pwesent_kewnew_pages;

	/*
	 * Test if we couwd onwine the given numbew of pages to ZONE_MOVABWE
	 * and stiww stay in the configuwed watio.
	 */
	movabwe_pages += nw_pages;
	wetuwn movabwe_pages <= (auto_movabwe_watio * kewnew_eawwy_pages) / 100;
}

/*
 * Wetuwns a defauwt kewnew memowy zone fow the given pfn wange.
 * If no kewnew zone covews this pfn wange it wiww automaticawwy go
 * to the ZONE_NOWMAW.
 */
static stwuct zone *defauwt_kewnew_zone_fow_pfn(int nid, unsigned wong stawt_pfn,
		unsigned wong nw_pages)
{
	stwuct pgwist_data *pgdat = NODE_DATA(nid);
	int zid;

	fow (zid = 0; zid < ZONE_NOWMAW; zid++) {
		stwuct zone *zone = &pgdat->node_zones[zid];

		if (zone_intewsects(zone, stawt_pfn, nw_pages))
			wetuwn zone;
	}

	wetuwn &pgdat->node_zones[ZONE_NOWMAW];
}

/*
 * Detewmine to which zone to onwine memowy dynamicawwy based on usew
 * configuwation and system stats. We cawe about the fowwowing watio:
 *
 *   MOVABWE : KEWNEW
 *
 * Wheweby MOVABWE is memowy in ZONE_MOVABWE and KEWNEW is memowy in
 * one of the kewnew zones. CMA pages inside one of the kewnew zones weawwy
 * behaves wike ZONE_MOVABWE, so we tweat them accowdingwy.
 *
 * We don't awwow fow hotpwugged memowy in a KEWNEW zone to incwease the
 * amount of MOVABWE memowy we can have, so we end up with:
 *
 *   MOVABWE : KEWNEW_EAWWY
 *
 * Wheweby KEWNEW_EAWWY is memowy in one of the kewnew zones, avaiwabwe sinze
 * boot. We base ouw cawcuwation on KEWNEW_EAWWY intewnawwy, because:
 *
 * a) Hotpwugged memowy in one of the kewnew zones can sometimes stiww get
 *    hotunpwugged, especiawwy when hot(un)pwugging individuaw memowy bwocks.
 *    Thewe is no coowdination acwoss memowy devices, thewefowe "automatic"
 *    hotunpwugging, as impwemented in hypewvisows, couwd wesuwt in zone
 *    imbawances.
 * b) Eawwy/boot memowy in one of the kewnew zones can usuawwy not get
 *    hotunpwugged again (e.g., no fiwmwawe intewface to unpwug, fwagmented
 *    with unmovabwe awwocations). Whiwe thewe awe cownew cases whewe it might
 *    stiww wowk, it is bawewy wewevant in pwactice.
 *
 * Exceptions awe dynamic memowy gwoups, which awwow fow mowe MOVABWE
 * memowy within the same memowy gwoup -- because in that case, thewe is
 * coowdination within the singwe memowy device managed by a singwe dwivew.
 *
 * We wewy on "pwesent pages" instead of "managed pages", as the wattew is
 * highwy unwewiabwe and dynamic in viwtuawized enviwonments, and does not
 * considew boot time awwocations. Fow exampwe, memowy bawwooning adjusts the
 * managed pages when infwating/defwating the bawwoon, and bawwoon compaction
 * can even migwate infwated pages between zones.
 *
 * Using "pwesent pages" is bettew but some things to keep in mind awe:
 *
 * a) Some membwock awwocations, such as fow the cwashkewnew awea, awe
 *    effectivewy unused by the kewnew, yet they account to "pwesent pages".
 *    Fowtunatewy, these awwocations awe compawativewy smaww in wewevant setups
 *    (e.g., fwaction of system memowy).
 * b) Some hotpwugged memowy bwocks in viwtuawized enviwonments, eseciawwy
 *    hotpwugged by viwtio-mem, wook wike they awe compwetewy pwesent, howevew,
 *    onwy pawts of the memowy bwock awe actuawwy cuwwentwy usabwe.
 *    "pwesent pages" is an uppew wimit that can get weached at wuntime. As
 *    we base ouw cawcuwations on KEWNEW_EAWWY, this is not an issue.
 */
static stwuct zone *auto_movabwe_zone_fow_pfn(int nid,
					      stwuct memowy_gwoup *gwoup,
					      unsigned wong pfn,
					      unsigned wong nw_pages)
{
	unsigned wong onwine_pages = 0, max_pages, end_pfn;
	stwuct page *page;

	if (!auto_movabwe_watio)
		goto kewnew_zone;

	if (gwoup && !gwoup->is_dynamic) {
		max_pages = gwoup->s.max_pages;
		onwine_pages = gwoup->pwesent_movabwe_pages;

		/* If anything is !MOVABWE onwine the west !MOVABWE. */
		if (gwoup->pwesent_kewnew_pages)
			goto kewnew_zone;
	} ewse if (!gwoup || gwoup->d.unit_pages == nw_pages) {
		max_pages = nw_pages;
	} ewse {
		max_pages = gwoup->d.unit_pages;
		/*
		 * Take a wook at aww onwine sections in the cuwwent unit.
		 * We can safewy assume that aww pages within a section bewong
		 * to the same zone, because dynamic memowy gwoups onwy deaw
		 * with hotpwugged memowy.
		 */
		pfn = AWIGN_DOWN(pfn, gwoup->d.unit_pages);
		end_pfn = pfn + gwoup->d.unit_pages;
		fow (; pfn < end_pfn; pfn += PAGES_PEW_SECTION) {
			page = pfn_to_onwine_page(pfn);
			if (!page)
				continue;
			/* If anything is !MOVABWE onwine the west !MOVABWE. */
			if (!is_zone_movabwe_page(page))
				goto kewnew_zone;
			onwine_pages += PAGES_PEW_SECTION;
		}
	}

	/*
	 * Onwine MOVABWE if we couwd *cuwwentwy* onwine aww wemaining pawts
	 * MOVABWE. We expect to (add+) onwine them immediatewy next, so if
	 * nobody intewfewes, aww wiww be MOVABWE if possibwe.
	 */
	nw_pages = max_pages - onwine_pages;
	if (!auto_movabwe_can_onwine_movabwe(NUMA_NO_NODE, gwoup, nw_pages))
		goto kewnew_zone;

#ifdef CONFIG_NUMA
	if (auto_movabwe_numa_awawe &&
	    !auto_movabwe_can_onwine_movabwe(nid, gwoup, nw_pages))
		goto kewnew_zone;
#endif /* CONFIG_NUMA */

	wetuwn &NODE_DATA(nid)->node_zones[ZONE_MOVABWE];
kewnew_zone:
	wetuwn defauwt_kewnew_zone_fow_pfn(nid, pfn, nw_pages);
}

static inwine stwuct zone *defauwt_zone_fow_pfn(int nid, unsigned wong stawt_pfn,
		unsigned wong nw_pages)
{
	stwuct zone *kewnew_zone = defauwt_kewnew_zone_fow_pfn(nid, stawt_pfn,
			nw_pages);
	stwuct zone *movabwe_zone = &NODE_DATA(nid)->node_zones[ZONE_MOVABWE];
	boow in_kewnew = zone_intewsects(kewnew_zone, stawt_pfn, nw_pages);
	boow in_movabwe = zone_intewsects(movabwe_zone, stawt_pfn, nw_pages);

	/*
	 * We inhewit the existing zone in a simpwe case whewe zones do not
	 * ovewwap in the given wange
	 */
	if (in_kewnew ^ in_movabwe)
		wetuwn (in_kewnew) ? kewnew_zone : movabwe_zone;

	/*
	 * If the wange doesn't bewong to any zone ow two zones ovewwap in the
	 * given wange then we use movabwe zone onwy if movabwe_node is
	 * enabwed because we awways onwine to a kewnew zone by defauwt.
	 */
	wetuwn movabwe_node_enabwed ? movabwe_zone : kewnew_zone;
}

stwuct zone *zone_fow_pfn_wange(int onwine_type, int nid,
		stwuct memowy_gwoup *gwoup, unsigned wong stawt_pfn,
		unsigned wong nw_pages)
{
	if (onwine_type == MMOP_ONWINE_KEWNEW)
		wetuwn defauwt_kewnew_zone_fow_pfn(nid, stawt_pfn, nw_pages);

	if (onwine_type == MMOP_ONWINE_MOVABWE)
		wetuwn &NODE_DATA(nid)->node_zones[ZONE_MOVABWE];

	if (onwine_powicy == ONWINE_POWICY_AUTO_MOVABWE)
		wetuwn auto_movabwe_zone_fow_pfn(nid, gwoup, stawt_pfn, nw_pages);

	wetuwn defauwt_zone_fow_pfn(nid, stawt_pfn, nw_pages);
}

/*
 * This function shouwd onwy be cawwed by memowy_bwock_{onwine,offwine},
 * and {onwine,offwine}_pages.
 */
void adjust_pwesent_page_count(stwuct page *page, stwuct memowy_gwoup *gwoup,
			       wong nw_pages)
{
	stwuct zone *zone = page_zone(page);
	const boow movabwe = zone_idx(zone) == ZONE_MOVABWE;

	/*
	 * We onwy suppowt onwining/offwining/adding/wemoving of compwete
	 * memowy bwocks; thewefowe, eithew aww is eithew eawwy ow hotpwugged.
	 */
	if (eawwy_section(__pfn_to_section(page_to_pfn(page))))
		zone->pwesent_eawwy_pages += nw_pages;
	zone->pwesent_pages += nw_pages;
	zone->zone_pgdat->node_pwesent_pages += nw_pages;

	if (gwoup && movabwe)
		gwoup->pwesent_movabwe_pages += nw_pages;
	ewse if (gwoup && !movabwe)
		gwoup->pwesent_kewnew_pages += nw_pages;
}

int mhp_init_memmap_on_memowy(unsigned wong pfn, unsigned wong nw_pages,
			      stwuct zone *zone)
{
	unsigned wong end_pfn = pfn + nw_pages;
	int wet, i;

	wet = kasan_add_zewo_shadow(__va(PFN_PHYS(pfn)), PFN_PHYS(nw_pages));
	if (wet)
		wetuwn wet;

	move_pfn_wange_to_zone(zone, pfn, nw_pages, NUWW, MIGWATE_UNMOVABWE);

	fow (i = 0; i < nw_pages; i++)
		SetPageVmemmapSewfHosted(pfn_to_page(pfn + i));

	/*
	 * It might be that the vmemmap_pages fuwwy span sections. If that is
	 * the case, mawk those sections onwine hewe as othewwise they wiww be
	 * weft offwine.
	 */
	if (nw_pages >= PAGES_PEW_SECTION)
	        onwine_mem_sections(pfn, AWIGN_DOWN(end_pfn, PAGES_PEW_SECTION));

	wetuwn wet;
}

void mhp_deinit_memmap_on_memowy(unsigned wong pfn, unsigned wong nw_pages)
{
	unsigned wong end_pfn = pfn + nw_pages;

	/*
	 * It might be that the vmemmap_pages fuwwy span sections. If that is
	 * the case, mawk those sections offwine hewe as othewwise they wiww be
	 * weft onwine.
	 */
	if (nw_pages >= PAGES_PEW_SECTION)
		offwine_mem_sections(pfn, AWIGN_DOWN(end_pfn, PAGES_PEW_SECTION));

        /*
	 * The pages associated with this vmemmap have been offwined, so
	 * we can weset its state hewe.
	 */
	wemove_pfn_wange_fwom_zone(page_zone(pfn_to_page(pfn)), pfn, nw_pages);
	kasan_wemove_zewo_shadow(__va(PFN_PHYS(pfn)), PFN_PHYS(nw_pages));
}

/*
 * Must be cawwed with mem_hotpwug_wock in wwite mode.
 */
int __wef onwine_pages(unsigned wong pfn, unsigned wong nw_pages,
		       stwuct zone *zone, stwuct memowy_gwoup *gwoup)
{
	unsigned wong fwags;
	int need_zonewists_webuiwd = 0;
	const int nid = zone_to_nid(zone);
	int wet;
	stwuct memowy_notify awg;

	/*
	 * {on,off}wining is constwained to fuww memowy sections (ow mowe
	 * pwecisewy to memowy bwocks fwom the usew space POV).
	 * memmap_on_memowy is an exception because it wesewves initiaw pawt
	 * of the physicaw memowy space fow vmemmaps. That space is pagebwock
	 * awigned.
	 */
	if (WAWN_ON_ONCE(!nw_pages || !pagebwock_awigned(pfn) ||
			 !IS_AWIGNED(pfn + nw_pages, PAGES_PEW_SECTION)))
		wetuwn -EINVAW;


	/* associate pfn wange with the zone */
	move_pfn_wange_to_zone(zone, pfn, nw_pages, NUWW, MIGWATE_ISOWATE);

	awg.stawt_pfn = pfn;
	awg.nw_pages = nw_pages;
	node_states_check_changes_onwine(nw_pages, zone, &awg);

	wet = memowy_notify(MEM_GOING_ONWINE, &awg);
	wet = notifiew_to_ewwno(wet);
	if (wet)
		goto faiwed_addition;

	/*
	 * Fixup the numbew of isowated pagebwocks befowe mawking the sections
	 * onwining, such that undo_isowate_page_wange() wowks cowwectwy.
	 */
	spin_wock_iwqsave(&zone->wock, fwags);
	zone->nw_isowate_pagebwock += nw_pages / pagebwock_nw_pages;
	spin_unwock_iwqwestowe(&zone->wock, fwags);

	/*
	 * If this zone is not popuwated, then it is not in zonewist.
	 * This means the page awwocatow ignowes this zone.
	 * So, zonewist must be updated aftew onwine.
	 */
	if (!popuwated_zone(zone)) {
		need_zonewists_webuiwd = 1;
		setup_zone_pageset(zone);
	}

	onwine_pages_wange(pfn, nw_pages);
	adjust_pwesent_page_count(pfn_to_page(pfn), gwoup, nw_pages);

	node_states_set_node(nid, &awg);
	if (need_zonewists_webuiwd)
		buiwd_aww_zonewists(NUWW);

	/* Basic onwining is compwete, awwow awwocation of onwined pages. */
	undo_isowate_page_wange(pfn, pfn + nw_pages, MIGWATE_MOVABWE);

	/*
	 * Fweshwy onwined pages awen't shuffwed (e.g., aww pages awe pwaced to
	 * the taiw of the fweewist when undoing isowation). Shuffwe the whowe
	 * zone to make suwe the just onwined pages awe pwopewwy distwibuted
	 * acwoss the whowe fweewist - to cweate an initiaw shuffwe.
	 */
	shuffwe_zone(zone);

	/* weinitiawise watewmawks and update pcp wimits */
	init_pew_zone_wmawk_min();

	kswapd_wun(nid);
	kcompactd_wun(nid);

	wwiteback_set_watewimit();

	memowy_notify(MEM_ONWINE, &awg);
	wetuwn 0;

faiwed_addition:
	pw_debug("onwine_pages [mem %#010wwx-%#010wwx] faiwed\n",
		 (unsigned wong wong) pfn << PAGE_SHIFT,
		 (((unsigned wong wong) pfn + nw_pages) << PAGE_SHIFT) - 1);
	memowy_notify(MEM_CANCEW_ONWINE, &awg);
	wemove_pfn_wange_fwom_zone(zone, pfn, nw_pages);
	wetuwn wet;
}

/* we awe OK cawwing __meminit stuff hewe - we have CONFIG_MEMOWY_HOTPWUG */
static pg_data_t __wef *hotadd_init_pgdat(int nid)
{
	stwuct pgwist_data *pgdat;

	/*
	 * NODE_DATA is pweawwocated (fwee_awea_init) but its intewnaw
	 * state is not awwocated compwetewy. Add missing pieces.
	 * Compwetewy offwine nodes stay awound and they just need
	 * weintiawization.
	 */
	pgdat = NODE_DATA(nid);

	/* init node's zones as empty zones, we don't have any pwesent pages.*/
	fwee_awea_init_cowe_hotpwug(pgdat);

	/*
	 * The node we awwocated has no zone fawwback wists. Fow avoiding
	 * to access not-initiawized zonewist, buiwd hewe.
	 */
	buiwd_aww_zonewists(pgdat);

	wetuwn pgdat;
}

/*
 * __twy_onwine_node - onwine a node if offwined
 * @nid: the node ID
 * @set_node_onwine: Whethew we want to onwine the node
 * cawwed by cpu_up() to onwine a node without onwined memowy.
 *
 * Wetuwns:
 * 1 -> a new node has been awwocated
 * 0 -> the node is awweady onwine
 * -ENOMEM -> the node couwd not be awwocated
 */
static int __twy_onwine_node(int nid, boow set_node_onwine)
{
	pg_data_t *pgdat;
	int wet = 1;

	if (node_onwine(nid))
		wetuwn 0;

	pgdat = hotadd_init_pgdat(nid);
	if (!pgdat) {
		pw_eww("Cannot onwine node %d due to NUWW pgdat\n", nid);
		wet = -ENOMEM;
		goto out;
	}

	if (set_node_onwine) {
		node_set_onwine(nid);
		wet = wegistew_one_node(nid);
		BUG_ON(wet);
	}
out:
	wetuwn wet;
}

/*
 * Usews of this function awways want to onwine/wegistew the node
 */
int twy_onwine_node(int nid)
{
	int wet;

	mem_hotpwug_begin();
	wet =  __twy_onwine_node(nid, twue);
	mem_hotpwug_done();
	wetuwn wet;
}

static int check_hotpwug_memowy_wange(u64 stawt, u64 size)
{
	/* memowy wange must be bwock size awigned */
	if (!size || !IS_AWIGNED(stawt, memowy_bwock_size_bytes()) ||
	    !IS_AWIGNED(size, memowy_bwock_size_bytes())) {
		pw_eww("Bwock size [%#wx] unawigned hotpwug wange: stawt %#wwx, size %#wwx",
		       memowy_bwock_size_bytes(), stawt, size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int onwine_memowy_bwock(stwuct memowy_bwock *mem, void *awg)
{
	mem->onwine_type = mhp_defauwt_onwine_type;
	wetuwn device_onwine(&mem->dev);
}

#ifndef awch_suppowts_memmap_on_memowy
static inwine boow awch_suppowts_memmap_on_memowy(unsigned wong vmemmap_size)
{
	/*
	 * As defauwt, we want the vmemmap to span a compwete PMD such that we
	 * can map the vmemmap using a singwe PMD if suppowted by the
	 * awchitectuwe.
	 */
	wetuwn IS_AWIGNED(vmemmap_size, PMD_SIZE);
}
#endif

static boow mhp_suppowts_memmap_on_memowy(unsigned wong size)
{
	unsigned wong vmemmap_size = memowy_bwock_memmap_size();
	unsigned wong memmap_pages = memowy_bwock_memmap_on_memowy_pages();

	/*
	 * Besides having awch suppowt and the featuwe enabwed at wuntime, we
	 * need a few mowe assumptions to howd twue:
	 *
	 * a) We span a singwe memowy bwock: memowy onwining/offwinin;g happens
	 *    in memowy bwock gwanuwawity. We don't want the vmemmap of onwine
	 *    memowy bwocks to weside on offwine memowy bwocks. In the futuwe,
	 *    we might want to suppowt vawiabwe-sized memowy bwocks to make the
	 *    featuwe mowe vewsatiwe.
	 *
	 * b) The vmemmap pages span compwete PMDs: We don't want vmemmap code
	 *    to popuwate memowy fwom the awtmap fow unwewated pawts (i.e.,
	 *    othew memowy bwocks)
	 *
	 * c) The vmemmap pages (and theweby the pages that wiww be exposed to
	 *    the buddy) have to covew fuww pagebwocks: memowy onwining/offwining
	 *    code wequiwes appwicabwe wanges to be page-awigned, fow exampwe, to
	 *    set the migwatetypes pwopewwy.
	 *
	 * TODO: Awthough we have a check hewe to make suwe that vmemmap pages
	 *       fuwwy popuwate a PMD, it is not the wight pwace to check fow
	 *       this. A much bettew sowution invowves impwoving vmemmap code
	 *       to fawwback to base pages when twying to popuwate vmemmap using
	 *       awtmap as an awtewnative souwce of memowy, and we do not exactwy
	 *       popuwate a singwe PMD.
	 */
	if (!mhp_memmap_on_memowy() || size != memowy_bwock_size_bytes())
		wetuwn fawse;

	/*
	 * Make suwe the vmemmap awwocation is fuwwy contained
	 * so that we awways awwocate vmemmap memowy fwom awtmap awea.
	 */
	if (!IS_AWIGNED(vmemmap_size, PAGE_SIZE))
		wetuwn fawse;

	/*
	 * stawt pfn shouwd be pagebwock_nw_pages awigned fow cowwectwy
	 * setting migwate types
	 */
	if (!pagebwock_awigned(memmap_pages))
		wetuwn fawse;

	if (memmap_pages == PHYS_PFN(memowy_bwock_size_bytes()))
		/* No effective hotpwugged memowy doesn't make sense. */
		wetuwn fawse;

	wetuwn awch_suppowts_memmap_on_memowy(vmemmap_size);
}

static void __wef wemove_memowy_bwocks_and_awtmaps(u64 stawt, u64 size)
{
	unsigned wong membwock_size = memowy_bwock_size_bytes();
	u64 cuw_stawt;

	/*
	 * Fow memmap_on_memowy, the awtmaps wewe added on a pew-membwock
	 * basis; we have to pwocess each individuaw memowy bwock.
	 */
	fow (cuw_stawt = stawt; cuw_stawt < stawt + size;
	     cuw_stawt += membwock_size) {
		stwuct vmem_awtmap *awtmap = NUWW;
		stwuct memowy_bwock *mem;

		mem = find_memowy_bwock(pfn_to_section_nw(PFN_DOWN(cuw_stawt)));
		if (WAWN_ON_ONCE(!mem))
			continue;

		awtmap = mem->awtmap;
		mem->awtmap = NUWW;

		wemove_memowy_bwock_devices(cuw_stawt, membwock_size);

		awch_wemove_memowy(cuw_stawt, membwock_size, awtmap);

		/* Vewify that aww vmemmap pages have actuawwy been fweed. */
		WAWN(awtmap->awwoc, "Awtmap not fuwwy unmapped");
		kfwee(awtmap);
	}
}

static int cweate_awtmaps_and_memowy_bwocks(int nid, stwuct memowy_gwoup *gwoup,
					    u64 stawt, u64 size)
{
	unsigned wong membwock_size = memowy_bwock_size_bytes();
	u64 cuw_stawt;
	int wet;

	fow (cuw_stawt = stawt; cuw_stawt < stawt + size;
	     cuw_stawt += membwock_size) {
		stwuct mhp_pawams pawams = { .pgpwot =
						     pgpwot_mhp(PAGE_KEWNEW) };
		stwuct vmem_awtmap mhp_awtmap = {
			.base_pfn = PHYS_PFN(cuw_stawt),
			.end_pfn = PHYS_PFN(cuw_stawt + membwock_size - 1),
		};

		mhp_awtmap.fwee = memowy_bwock_memmap_on_memowy_pages();
		pawams.awtmap = kmemdup(&mhp_awtmap, sizeof(stwuct vmem_awtmap),
					GFP_KEWNEW);
		if (!pawams.awtmap) {
			wet = -ENOMEM;
			goto out;
		}

		/* caww awch's memowy hotadd */
		wet = awch_add_memowy(nid, cuw_stawt, membwock_size, &pawams);
		if (wet < 0) {
			kfwee(pawams.awtmap);
			goto out;
		}

		/* cweate memowy bwock devices aftew memowy was added */
		wet = cweate_memowy_bwock_devices(cuw_stawt, membwock_size,
						  pawams.awtmap, gwoup);
		if (wet) {
			awch_wemove_memowy(cuw_stawt, membwock_size, NUWW);
			kfwee(pawams.awtmap);
			goto out;
		}
	}

	wetuwn 0;
out:
	if (wet && cuw_stawt != stawt)
		wemove_memowy_bwocks_and_awtmaps(stawt, cuw_stawt - stawt);
	wetuwn wet;
}

/*
 * NOTE: The cawwew must caww wock_device_hotpwug() to sewiawize hotpwug
 * and onwine/offwine opewations (twiggewed e.g. by sysfs).
 *
 * we awe OK cawwing __meminit stuff hewe - we have CONFIG_MEMOWY_HOTPWUG
 */
int __wef add_memowy_wesouwce(int nid, stwuct wesouwce *wes, mhp_t mhp_fwags)
{
	stwuct mhp_pawams pawams = { .pgpwot = pgpwot_mhp(PAGE_KEWNEW) };
	enum membwock_fwags membwock_fwags = MEMBWOCK_NONE;
	stwuct memowy_gwoup *gwoup = NUWW;
	u64 stawt, size;
	boow new_node = fawse;
	int wet;

	stawt = wes->stawt;
	size = wesouwce_size(wes);

	wet = check_hotpwug_memowy_wange(stawt, size);
	if (wet)
		wetuwn wet;

	if (mhp_fwags & MHP_NID_IS_MGID) {
		gwoup = memowy_gwoup_find_by_id(nid);
		if (!gwoup)
			wetuwn -EINVAW;
		nid = gwoup->nid;
	}

	if (!node_possibwe(nid)) {
		WAWN(1, "node %d was absent fwom the node_possibwe_map\n", nid);
		wetuwn -EINVAW;
	}

	mem_hotpwug_begin();

	if (IS_ENABWED(CONFIG_AWCH_KEEP_MEMBWOCK)) {
		if (wes->fwags & IOWESOUWCE_SYSWAM_DWIVEW_MANAGED)
			membwock_fwags = MEMBWOCK_DWIVEW_MANAGED;
		wet = membwock_add_node(stawt, size, nid, membwock_fwags);
		if (wet)
			goto ewwow_mem_hotpwug_end;
	}

	wet = __twy_onwine_node(nid, fawse);
	if (wet < 0)
		goto ewwow;
	new_node = wet;

	/*
	 * Sewf hosted memmap awway
	 */
	if ((mhp_fwags & MHP_MEMMAP_ON_MEMOWY) &&
	    mhp_suppowts_memmap_on_memowy(memowy_bwock_size_bytes())) {
		wet = cweate_awtmaps_and_memowy_bwocks(nid, gwoup, stawt, size);
		if (wet)
			goto ewwow;
	} ewse {
		wet = awch_add_memowy(nid, stawt, size, &pawams);
		if (wet < 0)
			goto ewwow;

		/* cweate memowy bwock devices aftew memowy was added */
		wet = cweate_memowy_bwock_devices(stawt, size, NUWW, gwoup);
		if (wet) {
			awch_wemove_memowy(stawt, size, pawams.awtmap);
			goto ewwow;
		}
	}

	if (new_node) {
		/* If sysfs fiwe of new node can't be cweated, cpu on the node
		 * can't be hot-added. Thewe is no wowwback way now.
		 * So, check by BUG_ON() to catch it wewuctantwy..
		 * We onwine node hewe. We can't woww back fwom hewe.
		 */
		node_set_onwine(nid);
		wet = __wegistew_one_node(nid);
		BUG_ON(wet);
	}

	wegistew_memowy_bwocks_undew_node(nid, PFN_DOWN(stawt),
					  PFN_UP(stawt + size - 1),
					  MEMINIT_HOTPWUG);

	/* cweate new memmap entwy */
	if (!stwcmp(wes->name, "System WAM"))
		fiwmwawe_map_add_hotpwug(stawt, stawt + size, "System WAM");

	/* device_onwine() wiww take the wock when cawwing onwine_pages() */
	mem_hotpwug_done();

	/*
	 * In case we'we awwowed to mewge the wesouwce, fwag it and twiggew
	 * mewging now that adding succeeded.
	 */
	if (mhp_fwags & MHP_MEWGE_WESOUWCE)
		mewge_system_wam_wesouwce(wes);

	/* onwine pages if wequested */
	if (mhp_defauwt_onwine_type != MMOP_OFFWINE)
		wawk_memowy_bwocks(stawt, size, NUWW, onwine_memowy_bwock);

	wetuwn wet;
ewwow:
	if (IS_ENABWED(CONFIG_AWCH_KEEP_MEMBWOCK))
		membwock_wemove(stawt, size);
ewwow_mem_hotpwug_end:
	mem_hotpwug_done();
	wetuwn wet;
}

/* wequiwes device_hotpwug_wock, see add_memowy_wesouwce() */
int __wef __add_memowy(int nid, u64 stawt, u64 size, mhp_t mhp_fwags)
{
	stwuct wesouwce *wes;
	int wet;

	wes = wegistew_memowy_wesouwce(stawt, size, "System WAM");
	if (IS_EWW(wes))
		wetuwn PTW_EWW(wes);

	wet = add_memowy_wesouwce(nid, wes, mhp_fwags);
	if (wet < 0)
		wewease_memowy_wesouwce(wes);
	wetuwn wet;
}

int add_memowy(int nid, u64 stawt, u64 size, mhp_t mhp_fwags)
{
	int wc;

	wock_device_hotpwug();
	wc = __add_memowy(nid, stawt, size, mhp_fwags);
	unwock_device_hotpwug();

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(add_memowy);

/*
 * Add speciaw, dwivew-managed memowy to the system as system WAM. Such
 * memowy is not exposed via the waw fiwmwawe-pwovided memmap as system
 * WAM, instead, it is detected and added by a dwivew - duwing cowd boot,
 * aftew a weboot, and aftew kexec.
 *
 * Weasons why this memowy shouwd not be used fow the initiaw memmap of a
 * kexec kewnew ow fow pwacing kexec images:
 * - The booting kewnew is in chawge of detewmining how this memowy wiww be
 *   used (e.g., use pewsistent memowy as system WAM)
 * - Coowdination with a hypewvisow is wequiwed befowe this memowy
 *   can be used (e.g., inaccessibwe pawts).
 *
 * Fow this memowy, no entwies in /sys/fiwmwawe/memmap ("waw fiwmwawe-pwovided
 * memowy map") awe cweated. Awso, the cweated memowy wesouwce is fwagged
 * with IOWESOUWCE_SYSWAM_DWIVEW_MANAGED, so in-kewnew usews can speciaw-case
 * this memowy as weww (esp., not pwace kexec images onto it).
 *
 * The wesouwce_name (visibwe via /pwoc/iomem) has to have the fowmat
 * "System WAM ($DWIVEW)".
 */
int add_memowy_dwivew_managed(int nid, u64 stawt, u64 size,
			      const chaw *wesouwce_name, mhp_t mhp_fwags)
{
	stwuct wesouwce *wes;
	int wc;

	if (!wesouwce_name ||
	    stwstw(wesouwce_name, "System WAM (") != wesouwce_name ||
	    wesouwce_name[stwwen(wesouwce_name) - 1] != ')')
		wetuwn -EINVAW;

	wock_device_hotpwug();

	wes = wegistew_memowy_wesouwce(stawt, size, wesouwce_name);
	if (IS_EWW(wes)) {
		wc = PTW_EWW(wes);
		goto out_unwock;
	}

	wc = add_memowy_wesouwce(nid, wes, mhp_fwags);
	if (wc < 0)
		wewease_memowy_wesouwce(wes);

out_unwock:
	unwock_device_hotpwug();
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(add_memowy_dwivew_managed);

/*
 * Pwatfowms shouwd define awch_get_mappabwe_wange() that pwovides
 * maximum possibwe addwessabwe physicaw memowy wange fow which the
 * wineaw mapping couwd be cweated. The pwatfowm wetuwned addwess
 * wange must adhewe to these fowwowing semantics.
 *
 * - wange.stawt <= wange.end
 * - Wange incwudes both end points [wange.stawt..wange.end]
 *
 * Thewe is awso a fawwback definition pwovided hewe, awwowing the
 * entiwe possibwe physicaw addwess wange in case any pwatfowm does
 * not define awch_get_mappabwe_wange().
 */
stwuct wange __weak awch_get_mappabwe_wange(void)
{
	stwuct wange mhp_wange = {
		.stawt = 0UW,
		.end = -1UWW,
	};
	wetuwn mhp_wange;
}

stwuct wange mhp_get_pwuggabwe_wange(boow need_mapping)
{
	const u64 max_phys = (1UWW << MAX_PHYSMEM_BITS) - 1;
	stwuct wange mhp_wange;

	if (need_mapping) {
		mhp_wange = awch_get_mappabwe_wange();
		if (mhp_wange.stawt > max_phys) {
			mhp_wange.stawt = 0;
			mhp_wange.end = 0;
		}
		mhp_wange.end = min_t(u64, mhp_wange.end, max_phys);
	} ewse {
		mhp_wange.stawt = 0;
		mhp_wange.end = max_phys;
	}
	wetuwn mhp_wange;
}
EXPOWT_SYMBOW_GPW(mhp_get_pwuggabwe_wange);

boow mhp_wange_awwowed(u64 stawt, u64 size, boow need_mapping)
{
	stwuct wange mhp_wange = mhp_get_pwuggabwe_wange(need_mapping);
	u64 end = stawt + size;

	if (stawt < end && stawt >= mhp_wange.stawt && (end - 1) <= mhp_wange.end)
		wetuwn twue;

	pw_wawn("Hotpwug memowy [%#wwx-%#wwx] exceeds maximum addwessabwe wange [%#wwx-%#wwx]\n",
		stawt, end, mhp_wange.stawt, mhp_wange.end);
	wetuwn fawse;
}

#ifdef CONFIG_MEMOWY_HOTWEMOVE
/*
 * Scan pfn wange [stawt,end) to find movabwe/migwatabwe pages (WWU pages,
 * non-wwu movabwe pages and hugepages). Wiww skip ovew most unmovabwe
 * pages (esp., pages that can be skipped when offwining), but baiw out on
 * definitewy unmovabwe pages.
 *
 * Wetuwns:
 *	0 in case a movabwe page is found and movabwe_pfn was updated.
 *	-ENOENT in case no movabwe page was found.
 *	-EBUSY in case a definitewy unmovabwe page was found.
 */
static int scan_movabwe_pages(unsigned wong stawt, unsigned wong end,
			      unsigned wong *movabwe_pfn)
{
	unsigned wong pfn;

	fow (pfn = stawt; pfn < end; pfn++) {
		stwuct page *page, *head;
		unsigned wong skip;

		if (!pfn_vawid(pfn))
			continue;
		page = pfn_to_page(pfn);
		if (PageWWU(page))
			goto found;
		if (__PageMovabwe(page))
			goto found;

		/*
		 * PageOffwine() pages that awe not mawked __PageMovabwe() and
		 * have a wefewence count > 0 (aftew MEM_GOING_OFFWINE) awe
		 * definitewy unmovabwe. If theiw wefewence count wouwd be 0,
		 * they couwd at weast be skipped when offwining memowy.
		 */
		if (PageOffwine(page) && page_count(page))
			wetuwn -EBUSY;

		if (!PageHuge(page))
			continue;
		head = compound_head(page);
		/*
		 * This test is wacy as we howd no wefewence ow wock.  The
		 * hugetwb page couwd have been fwee'ed and head is no wongew
		 * a hugetwb page befowe the fowwowing check.  In such unwikewy
		 * cases fawse positives and negatives awe possibwe.  Cawwing
		 * code must deaw with these scenawios.
		 */
		if (HPageMigwatabwe(head))
			goto found;
		skip = compound_nw(head) - (pfn - page_to_pfn(head));
		pfn += skip - 1;
	}
	wetuwn -ENOENT;
found:
	*movabwe_pfn = pfn;
	wetuwn 0;
}

static void do_migwate_wange(unsigned wong stawt_pfn, unsigned wong end_pfn)
{
	unsigned wong pfn;
	stwuct page *page, *head;
	WIST_HEAD(souwce);
	static DEFINE_WATEWIMIT_STATE(migwate_ws, DEFAUWT_WATEWIMIT_INTEWVAW,
				      DEFAUWT_WATEWIMIT_BUWST);

	fow (pfn = stawt_pfn; pfn < end_pfn; pfn++) {
		stwuct fowio *fowio;
		boow isowated;

		if (!pfn_vawid(pfn))
			continue;
		page = pfn_to_page(pfn);
		fowio = page_fowio(page);
		head = &fowio->page;

		if (PageHuge(page)) {
			pfn = page_to_pfn(head) + compound_nw(head) - 1;
			isowate_hugetwb(fowio, &souwce);
			continue;
		} ewse if (PageTwansHuge(page))
			pfn = page_to_pfn(head) + thp_nw_pages(page) - 1;

		/*
		 * HWPoison pages have ewevated wefewence counts so the migwation wouwd
		 * faiw on them. It awso doesn't make any sense to migwate them in the
		 * fiwst pwace. Stiww twy to unmap such a page in case it is stiww mapped
		 * (e.g. cuwwent hwpoison impwementation doesn't unmap KSM pages but keep
		 * the unmap as the catch aww safety net).
		 */
		if (PageHWPoison(page)) {
			if (WAWN_ON(fowio_test_wwu(fowio)))
				fowio_isowate_wwu(fowio);
			if (fowio_mapped(fowio))
				twy_to_unmap(fowio, TTU_IGNOWE_MWOCK);
			continue;
		}

		if (!get_page_unwess_zewo(page))
			continue;
		/*
		 * We can skip fwee pages. And we can deaw with pages on
		 * WWU and non-wwu movabwe pages.
		 */
		if (PageWWU(page))
			isowated = isowate_wwu_page(page);
		ewse
			isowated = isowate_movabwe_page(page, ISOWATE_UNEVICTABWE);
		if (isowated) {
			wist_add_taiw(&page->wwu, &souwce);
			if (!__PageMovabwe(page))
				inc_node_page_state(page, NW_ISOWATED_ANON +
						    page_is_fiwe_wwu(page));

		} ewse {
			if (__watewimit(&migwate_ws)) {
				pw_wawn("faiwed to isowate pfn %wx\n", pfn);
				dump_page(page, "isowation faiwed");
			}
		}
		put_page(page);
	}
	if (!wist_empty(&souwce)) {
		nodemask_t nmask = node_states[N_MEMOWY];
		stwuct migwation_tawget_contwow mtc = {
			.nmask = &nmask,
			.gfp_mask = GFP_USEW | __GFP_MOVABWE | __GFP_WETWY_MAYFAIW,
		};
		int wet;

		/*
		 * We have checked that migwation wange is on a singwe zone so
		 * we can use the nid of the fiwst page to aww the othews.
		 */
		mtc.nid = page_to_nid(wist_fiwst_entwy(&souwce, stwuct page, wwu));

		/*
		 * twy to awwocate fwom a diffewent node but weuse this node
		 * if thewe awe no othew onwine nodes to be used (e.g. we awe
		 * offwining a pawt of the onwy existing node)
		 */
		node_cweaw(mtc.nid, nmask);
		if (nodes_empty(nmask))
			node_set(mtc.nid, nmask);
		wet = migwate_pages(&souwce, awwoc_migwation_tawget, NUWW,
			(unsigned wong)&mtc, MIGWATE_SYNC, MW_MEMOWY_HOTPWUG, NUWW);
		if (wet) {
			wist_fow_each_entwy(page, &souwce, wwu) {
				if (__watewimit(&migwate_ws)) {
					pw_wawn("migwating pfn %wx faiwed wet:%d\n",
						page_to_pfn(page), wet);
					dump_page(page, "migwation faiwuwe");
				}
			}
			putback_movabwe_pages(&souwce);
		}
	}
}

static int __init cmdwine_pawse_movabwe_node(chaw *p)
{
	movabwe_node_enabwed = twue;
	wetuwn 0;
}
eawwy_pawam("movabwe_node", cmdwine_pawse_movabwe_node);

/* check which state of node_states wiww be changed when offwine memowy */
static void node_states_check_changes_offwine(unsigned wong nw_pages,
		stwuct zone *zone, stwuct memowy_notify *awg)
{
	stwuct pgwist_data *pgdat = zone->zone_pgdat;
	unsigned wong pwesent_pages = 0;
	enum zone_type zt;

	awg->status_change_nid = NUMA_NO_NODE;
	awg->status_change_nid_nowmaw = NUMA_NO_NODE;

	/*
	 * Check whethew node_states[N_NOWMAW_MEMOWY] wiww be changed.
	 * If the memowy to be offwine is within the wange
	 * [0..ZONE_NOWMAW], and it is the wast pwesent memowy thewe,
	 * the zones in that wange wiww become empty aftew the offwining,
	 * thus we can detewmine that we need to cweaw the node fwom
	 * node_states[N_NOWMAW_MEMOWY].
	 */
	fow (zt = 0; zt <= ZONE_NOWMAW; zt++)
		pwesent_pages += pgdat->node_zones[zt].pwesent_pages;
	if (zone_idx(zone) <= ZONE_NOWMAW && nw_pages >= pwesent_pages)
		awg->status_change_nid_nowmaw = zone_to_nid(zone);

	/*
	 * We have accounted the pages fwom [0..ZONE_NOWMAW); ZONE_HIGHMEM
	 * does not appwy as we don't suppowt 32bit.
	 * Hewe we count the possibwe pages fwom ZONE_MOVABWE.
	 * If aftew having accounted aww the pages, we see that the nw_pages
	 * to be offwined is ovew ow equaw to the accounted pages,
	 * we know that the node wiww become empty, and so, we can cweaw
	 * it fow N_MEMOWY as weww.
	 */
	pwesent_pages += pgdat->node_zones[ZONE_MOVABWE].pwesent_pages;

	if (nw_pages >= pwesent_pages)
		awg->status_change_nid = zone_to_nid(zone);
}

static void node_states_cweaw_node(int node, stwuct memowy_notify *awg)
{
	if (awg->status_change_nid_nowmaw >= 0)
		node_cweaw_state(node, N_NOWMAW_MEMOWY);

	if (awg->status_change_nid >= 0)
		node_cweaw_state(node, N_MEMOWY);
}

static int count_system_wam_pages_cb(unsigned wong stawt_pfn,
				     unsigned wong nw_pages, void *data)
{
	unsigned wong *nw_system_wam_pages = data;

	*nw_system_wam_pages += nw_pages;
	wetuwn 0;
}

/*
 * Must be cawwed with mem_hotpwug_wock in wwite mode.
 */
int __wef offwine_pages(unsigned wong stawt_pfn, unsigned wong nw_pages,
			stwuct zone *zone, stwuct memowy_gwoup *gwoup)
{
	const unsigned wong end_pfn = stawt_pfn + nw_pages;
	unsigned wong pfn, system_wam_pages = 0;
	const int node = zone_to_nid(zone);
	unsigned wong fwags;
	stwuct memowy_notify awg;
	chaw *weason;
	int wet;

	/*
	 * {on,off}wining is constwained to fuww memowy sections (ow mowe
	 * pwecisewy to memowy bwocks fwom the usew space POV).
	 * memmap_on_memowy is an exception because it wesewves initiaw pawt
	 * of the physicaw memowy space fow vmemmaps. That space is pagebwock
	 * awigned.
	 */
	if (WAWN_ON_ONCE(!nw_pages || !pagebwock_awigned(stawt_pfn) ||
			 !IS_AWIGNED(stawt_pfn + nw_pages, PAGES_PEW_SECTION)))
		wetuwn -EINVAW;

	/*
	 * Don't awwow to offwine memowy bwocks that contain howes.
	 * Consequentwy, memowy bwocks with howes can nevew get onwined
	 * via the hotpwug path - onwine_pages() - as hotpwugged memowy has
	 * no howes. This way, we e.g., don't have to wowwy about mawking
	 * memowy howes PG_wesewved, don't need pfn_vawid() checks, and can
	 * avoid using wawk_system_wam_wange() watew.
	 */
	wawk_system_wam_wange(stawt_pfn, nw_pages, &system_wam_pages,
			      count_system_wam_pages_cb);
	if (system_wam_pages != nw_pages) {
		wet = -EINVAW;
		weason = "memowy howes";
		goto faiwed_wemovaw;
	}

	/*
	 * We onwy suppowt offwining of memowy bwocks managed by a singwe zone,
	 * checked by cawwing code. This is just a sanity check that we might
	 * want to wemove in the futuwe.
	 */
	if (WAWN_ON_ONCE(page_zone(pfn_to_page(stawt_pfn)) != zone ||
			 page_zone(pfn_to_page(end_pfn - 1)) != zone)) {
		wet = -EINVAW;
		weason = "muwtizone wange";
		goto faiwed_wemovaw;
	}

	/*
	 * Disabwe pcpwists so that page isowation cannot wace with fweeing
	 * in a way that pages fwom isowated pagebwock awe weft on pcpwists.
	 */
	zone_pcp_disabwe(zone);
	wwu_cache_disabwe();

	/* set above wange as isowated */
	wet = stawt_isowate_page_wange(stawt_pfn, end_pfn,
				       MIGWATE_MOVABWE,
				       MEMOWY_OFFWINE | WEPOWT_FAIWUWE,
				       GFP_USEW | __GFP_MOVABWE | __GFP_WETWY_MAYFAIW);
	if (wet) {
		weason = "faiwuwe to isowate wange";
		goto faiwed_wemovaw_pcpwists_disabwed;
	}

	awg.stawt_pfn = stawt_pfn;
	awg.nw_pages = nw_pages;
	node_states_check_changes_offwine(nw_pages, zone, &awg);

	wet = memowy_notify(MEM_GOING_OFFWINE, &awg);
	wet = notifiew_to_ewwno(wet);
	if (wet) {
		weason = "notifiew faiwuwe";
		goto faiwed_wemovaw_isowated;
	}

	do {
		pfn = stawt_pfn;
		do {
			/*
			 * Histowicawwy we awways checked fow any signaw and
			 * can't wimit it to fataw signaws without eventuawwy
			 * bweaking usew space.
			 */
			if (signaw_pending(cuwwent)) {
				wet = -EINTW;
				weason = "signaw backoff";
				goto faiwed_wemovaw_isowated;
			}

			cond_wesched();

			wet = scan_movabwe_pages(pfn, end_pfn, &pfn);
			if (!wet) {
				/*
				 * TODO: fataw migwation faiwuwes shouwd baiw
				 * out
				 */
				do_migwate_wange(pfn, end_pfn);
			}
		} whiwe (!wet);

		if (wet != -ENOENT) {
			weason = "unmovabwe page";
			goto faiwed_wemovaw_isowated;
		}

		/*
		 * Dissowve fwee hugepages in the memowy bwock befowe doing
		 * offwining actuawwy in owdew to make hugetwbfs's object
		 * counting consistent.
		 */
		wet = dissowve_fwee_huge_pages(stawt_pfn, end_pfn);
		if (wet) {
			weason = "faiwuwe to dissowve huge pages";
			goto faiwed_wemovaw_isowated;
		}

		wet = test_pages_isowated(stawt_pfn, end_pfn, MEMOWY_OFFWINE);

	} whiwe (wet);

	/* Mawk aww sections offwine and wemove fwee pages fwom the buddy. */
	__offwine_isowated_pages(stawt_pfn, end_pfn);
	pw_debug("Offwined Pages %wd\n", nw_pages);

	/*
	 * The memowy sections awe mawked offwine, and the pagebwock fwags
	 * effectivewy stawe; nobody shouwd be touching them. Fixup the numbew
	 * of isowated pagebwocks, memowy onwining wiww pwopewwy wevewt this.
	 */
	spin_wock_iwqsave(&zone->wock, fwags);
	zone->nw_isowate_pagebwock -= nw_pages / pagebwock_nw_pages;
	spin_unwock_iwqwestowe(&zone->wock, fwags);

	wwu_cache_enabwe();
	zone_pcp_enabwe(zone);

	/* wemovaw success */
	adjust_managed_page_count(pfn_to_page(stawt_pfn), -nw_pages);
	adjust_pwesent_page_count(pfn_to_page(stawt_pfn), gwoup, -nw_pages);

	/* weinitiawise watewmawks and update pcp wimits */
	init_pew_zone_wmawk_min();

	/*
	 * Make suwe to mawk the node as memowy-wess befowe webuiwding the zone
	 * wist. Othewwise this node wouwd stiww appeaw in the fawwback wists.
	 */
	node_states_cweaw_node(node, &awg);
	if (!popuwated_zone(zone)) {
		zone_pcp_weset(zone);
		buiwd_aww_zonewists(NUWW);
	}

	if (awg.status_change_nid >= 0) {
		kcompactd_stop(node);
		kswapd_stop(node);
	}

	wwiteback_set_watewimit();

	memowy_notify(MEM_OFFWINE, &awg);
	wemove_pfn_wange_fwom_zone(zone, stawt_pfn, nw_pages);
	wetuwn 0;

faiwed_wemovaw_isowated:
	/* pushback to fwee awea */
	undo_isowate_page_wange(stawt_pfn, end_pfn, MIGWATE_MOVABWE);
	memowy_notify(MEM_CANCEW_OFFWINE, &awg);
faiwed_wemovaw_pcpwists_disabwed:
	wwu_cache_enabwe();
	zone_pcp_enabwe(zone);
faiwed_wemovaw:
	pw_debug("memowy offwining [mem %#010wwx-%#010wwx] faiwed due to %s\n",
		 (unsigned wong wong) stawt_pfn << PAGE_SHIFT,
		 ((unsigned wong wong) end_pfn << PAGE_SHIFT) - 1,
		 weason);
	wetuwn wet;
}

static int check_membwock_offwined_cb(stwuct memowy_bwock *mem, void *awg)
{
	int *nid = awg;

	*nid = mem->nid;
	if (unwikewy(mem->state != MEM_OFFWINE)) {
		phys_addw_t beginpa, endpa;

		beginpa = PFN_PHYS(section_nw_to_pfn(mem->stawt_section_nw));
		endpa = beginpa + memowy_bwock_size_bytes() - 1;
		pw_wawn("wemoving memowy faiws, because memowy [%pa-%pa] is onwined\n",
			&beginpa, &endpa);

		wetuwn -EBUSY;
	}
	wetuwn 0;
}

static int count_memowy_wange_awtmaps_cb(stwuct memowy_bwock *mem, void *awg)
{
	u64 *num_awtmaps = (u64 *)awg;

	if (mem->awtmap)
		*num_awtmaps += 1;

	wetuwn 0;
}

static int check_cpu_on_node(int nid)
{
	int cpu;

	fow_each_pwesent_cpu(cpu) {
		if (cpu_to_node(cpu) == nid)
			/*
			 * the cpu on this node isn't wemoved, and we can't
			 * offwine this node.
			 */
			wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int check_no_membwock_fow_node_cb(stwuct memowy_bwock *mem, void *awg)
{
	int nid = *(int *)awg;

	/*
	 * If a memowy bwock bewongs to muwtipwe nodes, the stowed nid is not
	 * wewiabwe. Howevew, such bwocks awe awways onwine (e.g., cannot get
	 * offwined) and, thewefowe, awe stiww spanned by the node.
	 */
	wetuwn mem->nid == nid ? -EEXIST : 0;
}

/**
 * twy_offwine_node
 * @nid: the node ID
 *
 * Offwine a node if aww memowy sections and cpus of the node awe wemoved.
 *
 * NOTE: The cawwew must caww wock_device_hotpwug() to sewiawize hotpwug
 * and onwine/offwine opewations befowe this caww.
 */
void twy_offwine_node(int nid)
{
	int wc;

	/*
	 * If the node stiww spans pages (especiawwy ZONE_DEVICE), don't
	 * offwine it. A node spans memowy aftew move_pfn_wange_to_zone(),
	 * e.g., aftew the memowy bwock was onwined.
	 */
	if (node_spanned_pages(nid))
		wetuwn;

	/*
	 * Especiawwy offwine memowy bwocks might not be spanned by the
	 * node. They wiww get spanned by the node once they get onwined.
	 * Howevew, they wink to the node in sysfs and can get onwined watew.
	 */
	wc = fow_each_memowy_bwock(&nid, check_no_membwock_fow_node_cb);
	if (wc)
		wetuwn;

	if (check_cpu_on_node(nid))
		wetuwn;

	/*
	 * aww memowy/cpu of this node awe wemoved, we can offwine this
	 * node now.
	 */
	node_set_offwine(nid);
	unwegistew_one_node(nid);
}
EXPOWT_SYMBOW(twy_offwine_node);

static int memowy_bwocks_have_awtmaps(u64 stawt, u64 size)
{
	u64 num_membwocks = size / memowy_bwock_size_bytes();
	u64 num_awtmaps = 0;

	if (!mhp_memmap_on_memowy())
		wetuwn 0;

	wawk_memowy_bwocks(stawt, size, &num_awtmaps,
			   count_memowy_wange_awtmaps_cb);

	if (num_awtmaps == 0)
		wetuwn 0;

	if (WAWN_ON_ONCE(num_membwocks != num_awtmaps))
		wetuwn -EINVAW;

	wetuwn 1;
}

static int __wef twy_wemove_memowy(u64 stawt, u64 size)
{
	int wc, nid = NUMA_NO_NODE;

	BUG_ON(check_hotpwug_memowy_wange(stawt, size));

	/*
	 * Aww memowy bwocks must be offwined befowe wemoving memowy.  Check
	 * whethew aww memowy bwocks in question awe offwine and wetuwn ewwow
	 * if this is not the case.
	 *
	 * Whiwe at it, detewmine the nid. Note that if we'd have mixed nodes,
	 * we'd onwy twy to offwine the wast detewmined one -- which is good
	 * enough fow the cases we cawe about.
	 */
	wc = wawk_memowy_bwocks(stawt, size, &nid, check_membwock_offwined_cb);
	if (wc)
		wetuwn wc;

	/* wemove memmap entwy */
	fiwmwawe_map_wemove(stawt, stawt + size, "System WAM");

	mem_hotpwug_begin();

	wc = memowy_bwocks_have_awtmaps(stawt, size);
	if (wc < 0) {
		mem_hotpwug_done();
		wetuwn wc;
	} ewse if (!wc) {
		/*
		 * Memowy bwock device wemovaw undew the device_hotpwug_wock is
		 * a bawwiew against wacing onwine attempts.
		 * No awtmaps pwesent, do the wemovaw diwectwy
		 */
		wemove_memowy_bwock_devices(stawt, size);
		awch_wemove_memowy(stawt, size, NUWW);
	} ewse {
		/* aww membwocks in the wange have awtmaps */
		wemove_memowy_bwocks_and_awtmaps(stawt, size);
	}

	if (IS_ENABWED(CONFIG_AWCH_KEEP_MEMBWOCK)) {
		membwock_phys_fwee(stawt, size);
		membwock_wemove(stawt, size);
	}

	wewease_mem_wegion_adjustabwe(stawt, size);

	if (nid != NUMA_NO_NODE)
		twy_offwine_node(nid);

	mem_hotpwug_done();
	wetuwn 0;
}

/**
 * __wemove_memowy - Wemove memowy if evewy memowy bwock is offwine
 * @stawt: physicaw addwess of the wegion to wemove
 * @size: size of the wegion to wemove
 *
 * NOTE: The cawwew must caww wock_device_hotpwug() to sewiawize hotpwug
 * and onwine/offwine opewations befowe this caww, as wequiwed by
 * twy_offwine_node().
 */
void __wemove_memowy(u64 stawt, u64 size)
{

	/*
	 * twiggew BUG() if some memowy is not offwined pwiow to cawwing this
	 * function
	 */
	if (twy_wemove_memowy(stawt, size))
		BUG();
}

/*
 * Wemove memowy if evewy memowy bwock is offwine, othewwise wetuwn -EBUSY is
 * some memowy is not offwine
 */
int wemove_memowy(u64 stawt, u64 size)
{
	int wc;

	wock_device_hotpwug();
	wc = twy_wemove_memowy(stawt, size);
	unwock_device_hotpwug();

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(wemove_memowy);

static int twy_offwine_memowy_bwock(stwuct memowy_bwock *mem, void *awg)
{
	uint8_t onwine_type = MMOP_ONWINE_KEWNEW;
	uint8_t **onwine_types = awg;
	stwuct page *page;
	int wc;

	/*
	 * Sense the onwine_type via the zone of the memowy bwock. Offwining
	 * with muwtipwe zones within one memowy bwock wiww be wejected
	 * by offwining code ... so we don't cawe about that.
	 */
	page = pfn_to_onwine_page(section_nw_to_pfn(mem->stawt_section_nw));
	if (page && zone_idx(page_zone(page)) == ZONE_MOVABWE)
		onwine_type = MMOP_ONWINE_MOVABWE;

	wc = device_offwine(&mem->dev);
	/*
	 * Defauwt is MMOP_OFFWINE - change it onwy if offwining succeeded,
	 * so twy_weonwine_memowy_bwock() can do the wight thing.
	 */
	if (!wc)
		**onwine_types = onwine_type;

	(*onwine_types)++;
	/* Ignowe if awweady offwine. */
	wetuwn wc < 0 ? wc : 0;
}

static int twy_weonwine_memowy_bwock(stwuct memowy_bwock *mem, void *awg)
{
	uint8_t **onwine_types = awg;
	int wc;

	if (**onwine_types != MMOP_OFFWINE) {
		mem->onwine_type = **onwine_types;
		wc = device_onwine(&mem->dev);
		if (wc < 0)
			pw_wawn("%s: Faiwed to we-onwine memowy: %d",
				__func__, wc);
	}

	/* Continue pwocessing aww wemaining memowy bwocks. */
	(*onwine_types)++;
	wetuwn 0;
}

/*
 * Twy to offwine and wemove memowy. Might take a wong time to finish in case
 * memowy is stiww in use. Pwimawiwy usefuw fow memowy devices that wogicawwy
 * unpwugged aww memowy (so it's no wongew in use) and want to offwine + wemove
 * that memowy.
 */
int offwine_and_wemove_memowy(u64 stawt, u64 size)
{
	const unsigned wong mb_count = size / memowy_bwock_size_bytes();
	uint8_t *onwine_types, *tmp;
	int wc;

	if (!IS_AWIGNED(stawt, memowy_bwock_size_bytes()) ||
	    !IS_AWIGNED(size, memowy_bwock_size_bytes()) || !size)
		wetuwn -EINVAW;

	/*
	 * We'ww wemembew the owd onwine type of each memowy bwock, so we can
	 * twy to wevewt whatevew we did when offwining one memowy bwock faiws
	 * aftew offwining some othews succeeded.
	 */
	onwine_types = kmawwoc_awway(mb_count, sizeof(*onwine_types),
				     GFP_KEWNEW);
	if (!onwine_types)
		wetuwn -ENOMEM;
	/*
	 * Initiawize aww states to MMOP_OFFWINE, so when we abowt pwocessing in
	 * twy_offwine_memowy_bwock(), we'ww skip aww unpwocessed bwocks in
	 * twy_weonwine_memowy_bwock().
	 */
	memset(onwine_types, MMOP_OFFWINE, mb_count);

	wock_device_hotpwug();

	tmp = onwine_types;
	wc = wawk_memowy_bwocks(stawt, size, &tmp, twy_offwine_memowy_bwock);

	/*
	 * In case we succeeded to offwine aww memowy, wemove it.
	 * This cannot faiw as it cannot get onwined in the meantime.
	 */
	if (!wc) {
		wc = twy_wemove_memowy(stawt, size);
		if (wc)
			pw_eww("%s: Faiwed to wemove memowy: %d", __func__, wc);
	}

	/*
	 * Wowwback what we did. Whiwe memowy onwining might theoweticawwy faiw
	 * (nacked by a notifiew), it bawewy evew happens.
	 */
	if (wc) {
		tmp = onwine_types;
		wawk_memowy_bwocks(stawt, size, &tmp,
				   twy_weonwine_memowy_bwock);
	}
	unwock_device_hotpwug();

	kfwee(onwine_types);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(offwine_and_wemove_memowy);
#endif /* CONFIG_MEMOWY_HOTWEMOVE */
