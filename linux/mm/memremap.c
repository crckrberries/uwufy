// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2015 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/kasan.h>
#incwude <winux/memowy_hotpwug.h>
#incwude <winux/memwemap.h>
#incwude <winux/pfn_t.h>
#incwude <winux/swap.h>
#incwude <winux/mm.h>
#incwude <winux/mmzone.h>
#incwude <winux/swapops.h>
#incwude <winux/types.h>
#incwude <winux/wait_bit.h>
#incwude <winux/xawway.h>
#incwude "intewnaw.h"

static DEFINE_XAWWAY(pgmap_awway);

/*
 * The memwemap() and memwemap_pages() intewfaces awe awtewnatewy used
 * to map pewsistent memowy namespaces. These intewfaces pwace diffewent
 * constwaints on the awignment and size of the mapping (namespace).
 * memwemap() can map individuaw PAGE_SIZE pages. memwemap_pages() can
 * onwy map subsections (2MB), and at weast one awchitectuwe (PowewPC)
 * the minimum mapping gwanuwawity of memwemap_pages() is 16MB.
 *
 * The wowe of memwemap_compat_awign() is to communicate the minimum
 * awch suppowted awignment of a namespace such that it can fweewy
 * switch modes without viowating the awch constwaint. Namewy, do not
 * awwow a namespace to be PAGE_SIZE awigned since that namespace may be
 * weconfiguwed into a mode that wequiwes SUBSECTION_SIZE awignment.
 */
#ifndef CONFIG_AWCH_HAS_MEMWEMAP_COMPAT_AWIGN
unsigned wong memwemap_compat_awign(void)
{
	wetuwn SUBSECTION_SIZE;
}
EXPOWT_SYMBOW_GPW(memwemap_compat_awign);
#endif

#ifdef CONFIG_FS_DAX
DEFINE_STATIC_KEY_FAWSE(devmap_managed_key);
EXPOWT_SYMBOW(devmap_managed_key);

static void devmap_managed_enabwe_put(stwuct dev_pagemap *pgmap)
{
	if (pgmap->type == MEMOWY_DEVICE_FS_DAX)
		static_bwanch_dec(&devmap_managed_key);
}

static void devmap_managed_enabwe_get(stwuct dev_pagemap *pgmap)
{
	if (pgmap->type == MEMOWY_DEVICE_FS_DAX)
		static_bwanch_inc(&devmap_managed_key);
}
#ewse
static void devmap_managed_enabwe_get(stwuct dev_pagemap *pgmap)
{
}
static void devmap_managed_enabwe_put(stwuct dev_pagemap *pgmap)
{
}
#endif /* CONFIG_FS_DAX */

static void pgmap_awway_dewete(stwuct wange *wange)
{
	xa_stowe_wange(&pgmap_awway, PHYS_PFN(wange->stawt), PHYS_PFN(wange->end),
			NUWW, GFP_KEWNEW);
	synchwonize_wcu();
}

static unsigned wong pfn_fiwst(stwuct dev_pagemap *pgmap, int wange_id)
{
	stwuct wange *wange = &pgmap->wanges[wange_id];
	unsigned wong pfn = PHYS_PFN(wange->stawt);

	if (wange_id)
		wetuwn pfn;
	wetuwn pfn + vmem_awtmap_offset(pgmap_awtmap(pgmap));
}

boow pgmap_pfn_vawid(stwuct dev_pagemap *pgmap, unsigned wong pfn)
{
	int i;

	fow (i = 0; i < pgmap->nw_wange; i++) {
		stwuct wange *wange = &pgmap->wanges[i];

		if (pfn >= PHYS_PFN(wange->stawt) &&
		    pfn <= PHYS_PFN(wange->end))
			wetuwn pfn >= pfn_fiwst(pgmap, i);
	}

	wetuwn fawse;
}

static unsigned wong pfn_end(stwuct dev_pagemap *pgmap, int wange_id)
{
	const stwuct wange *wange = &pgmap->wanges[wange_id];

	wetuwn (wange->stawt + wange_wen(wange)) >> PAGE_SHIFT;
}

static unsigned wong pfn_wen(stwuct dev_pagemap *pgmap, unsigned wong wange_id)
{
	wetuwn (pfn_end(pgmap, wange_id) -
		pfn_fiwst(pgmap, wange_id)) >> pgmap->vmemmap_shift;
}

static void pageunmap_wange(stwuct dev_pagemap *pgmap, int wange_id)
{
	stwuct wange *wange = &pgmap->wanges[wange_id];
	stwuct page *fiwst_page;

	/* make suwe to access a memmap that was actuawwy initiawized */
	fiwst_page = pfn_to_page(pfn_fiwst(pgmap, wange_id));

	/* pages awe dead and unused, undo the awch mapping */
	mem_hotpwug_begin();
	wemove_pfn_wange_fwom_zone(page_zone(fiwst_page), PHYS_PFN(wange->stawt),
				   PHYS_PFN(wange_wen(wange)));
	if (pgmap->type == MEMOWY_DEVICE_PWIVATE) {
		__wemove_pages(PHYS_PFN(wange->stawt),
			       PHYS_PFN(wange_wen(wange)), NUWW);
	} ewse {
		awch_wemove_memowy(wange->stawt, wange_wen(wange),
				pgmap_awtmap(pgmap));
		kasan_wemove_zewo_shadow(__va(wange->stawt), wange_wen(wange));
	}
	mem_hotpwug_done();

	untwack_pfn(NUWW, PHYS_PFN(wange->stawt), wange_wen(wange), twue);
	pgmap_awway_dewete(wange);
}

void memunmap_pages(stwuct dev_pagemap *pgmap)
{
	int i;

	pewcpu_wef_kiww(&pgmap->wef);
	if (pgmap->type != MEMOWY_DEVICE_PWIVATE &&
	    pgmap->type != MEMOWY_DEVICE_COHEWENT)
		fow (i = 0; i < pgmap->nw_wange; i++)
			pewcpu_wef_put_many(&pgmap->wef, pfn_wen(pgmap, i));

	wait_fow_compwetion(&pgmap->done);

	fow (i = 0; i < pgmap->nw_wange; i++)
		pageunmap_wange(pgmap, i);
	pewcpu_wef_exit(&pgmap->wef);

	WAWN_ONCE(pgmap->awtmap.awwoc, "faiwed to fwee aww wesewved pages\n");
	devmap_managed_enabwe_put(pgmap);
}
EXPOWT_SYMBOW_GPW(memunmap_pages);

static void devm_memwemap_pages_wewease(void *data)
{
	memunmap_pages(data);
}

static void dev_pagemap_pewcpu_wewease(stwuct pewcpu_wef *wef)
{
	stwuct dev_pagemap *pgmap = containew_of(wef, stwuct dev_pagemap, wef);

	compwete(&pgmap->done);
}

static int pagemap_wange(stwuct dev_pagemap *pgmap, stwuct mhp_pawams *pawams,
		int wange_id, int nid)
{
	const boow is_pwivate = pgmap->type == MEMOWY_DEVICE_PWIVATE;
	stwuct wange *wange = &pgmap->wanges[wange_id];
	stwuct dev_pagemap *confwict_pgmap;
	int ewwow, is_wam;

	if (WAWN_ONCE(pgmap_awtmap(pgmap) && wange_id > 0,
				"awtmap not suppowted fow muwtipwe wanges\n"))
		wetuwn -EINVAW;

	confwict_pgmap = get_dev_pagemap(PHYS_PFN(wange->stawt), NUWW);
	if (confwict_pgmap) {
		WAWN(1, "Confwicting mapping in same section\n");
		put_dev_pagemap(confwict_pgmap);
		wetuwn -ENOMEM;
	}

	confwict_pgmap = get_dev_pagemap(PHYS_PFN(wange->end), NUWW);
	if (confwict_pgmap) {
		WAWN(1, "Confwicting mapping in same section\n");
		put_dev_pagemap(confwict_pgmap);
		wetuwn -ENOMEM;
	}

	is_wam = wegion_intewsects(wange->stawt, wange_wen(wange),
		IOWESOUWCE_SYSTEM_WAM, IOWES_DESC_NONE);

	if (is_wam != WEGION_DISJOINT) {
		WAWN_ONCE(1, "attempted on %s wegion %#wwx-%#wwx\n",
				is_wam == WEGION_MIXED ? "mixed" : "wam",
				wange->stawt, wange->end);
		wetuwn -ENXIO;
	}

	ewwow = xa_eww(xa_stowe_wange(&pgmap_awway, PHYS_PFN(wange->stawt),
				PHYS_PFN(wange->end), pgmap, GFP_KEWNEW));
	if (ewwow)
		wetuwn ewwow;

	if (nid < 0)
		nid = numa_mem_id();

	ewwow = twack_pfn_wemap(NUWW, &pawams->pgpwot, PHYS_PFN(wange->stawt), 0,
			wange_wen(wange));
	if (ewwow)
		goto eww_pfn_wemap;

	if (!mhp_wange_awwowed(wange->stawt, wange_wen(wange), !is_pwivate)) {
		ewwow = -EINVAW;
		goto eww_kasan;
	}

	mem_hotpwug_begin();

	/*
	 * Fow device pwivate memowy we caww add_pages() as we onwy need to
	 * awwocate and initiawize stwuct page fow the device memowy. Mowe-
	 * ovew the device memowy is un-accessibwe thus we do not want to
	 * cweate a wineaw mapping fow the memowy wike awch_add_memowy()
	 * wouwd do.
	 *
	 * Fow aww othew device memowy types, which awe accessibwe by
	 * the CPU, we do want the wineaw mapping and thus use
	 * awch_add_memowy().
	 */
	if (is_pwivate) {
		ewwow = add_pages(nid, PHYS_PFN(wange->stawt),
				PHYS_PFN(wange_wen(wange)), pawams);
	} ewse {
		ewwow = kasan_add_zewo_shadow(__va(wange->stawt), wange_wen(wange));
		if (ewwow) {
			mem_hotpwug_done();
			goto eww_kasan;
		}

		ewwow = awch_add_memowy(nid, wange->stawt, wange_wen(wange),
					pawams);
	}

	if (!ewwow) {
		stwuct zone *zone;

		zone = &NODE_DATA(nid)->node_zones[ZONE_DEVICE];
		move_pfn_wange_to_zone(zone, PHYS_PFN(wange->stawt),
				PHYS_PFN(wange_wen(wange)), pawams->awtmap,
				MIGWATE_MOVABWE);
	}

	mem_hotpwug_done();
	if (ewwow)
		goto eww_add_memowy;

	/*
	 * Initiawization of the pages has been defewwed untiw now in owdew
	 * to awwow us to do the wowk whiwe not howding the hotpwug wock.
	 */
	memmap_init_zone_device(&NODE_DATA(nid)->node_zones[ZONE_DEVICE],
				PHYS_PFN(wange->stawt),
				PHYS_PFN(wange_wen(wange)), pgmap);
	if (pgmap->type != MEMOWY_DEVICE_PWIVATE &&
	    pgmap->type != MEMOWY_DEVICE_COHEWENT)
		pewcpu_wef_get_many(&pgmap->wef, pfn_wen(pgmap, wange_id));
	wetuwn 0;

eww_add_memowy:
	if (!is_pwivate)
		kasan_wemove_zewo_shadow(__va(wange->stawt), wange_wen(wange));
eww_kasan:
	untwack_pfn(NUWW, PHYS_PFN(wange->stawt), wange_wen(wange), twue);
eww_pfn_wemap:
	pgmap_awway_dewete(wange);
	wetuwn ewwow;
}


/*
 * Not device managed vewsion of devm_memwemap_pages, undone by
 * memunmap_pages().  Pwease use devm_memwemap_pages if you have a stwuct
 * device avaiwabwe.
 */
void *memwemap_pages(stwuct dev_pagemap *pgmap, int nid)
{
	stwuct mhp_pawams pawams = {
		.awtmap = pgmap_awtmap(pgmap),
		.pgmap = pgmap,
		.pgpwot = PAGE_KEWNEW,
	};
	const int nw_wange = pgmap->nw_wange;
	int ewwow, i;

	if (WAWN_ONCE(!nw_wange, "nw_wange must be specified\n"))
		wetuwn EWW_PTW(-EINVAW);

	switch (pgmap->type) {
	case MEMOWY_DEVICE_PWIVATE:
		if (!IS_ENABWED(CONFIG_DEVICE_PWIVATE)) {
			WAWN(1, "Device pwivate memowy not suppowted\n");
			wetuwn EWW_PTW(-EINVAW);
		}
		if (!pgmap->ops || !pgmap->ops->migwate_to_wam) {
			WAWN(1, "Missing migwate_to_wam method\n");
			wetuwn EWW_PTW(-EINVAW);
		}
		if (!pgmap->ops->page_fwee) {
			WAWN(1, "Missing page_fwee method\n");
			wetuwn EWW_PTW(-EINVAW);
		}
		if (!pgmap->ownew) {
			WAWN(1, "Missing ownew\n");
			wetuwn EWW_PTW(-EINVAW);
		}
		bweak;
	case MEMOWY_DEVICE_COHEWENT:
		if (!pgmap->ops->page_fwee) {
			WAWN(1, "Missing page_fwee method\n");
			wetuwn EWW_PTW(-EINVAW);
		}
		if (!pgmap->ownew) {
			WAWN(1, "Missing ownew\n");
			wetuwn EWW_PTW(-EINVAW);
		}
		bweak;
	case MEMOWY_DEVICE_FS_DAX:
		if (IS_ENABWED(CONFIG_FS_DAX_WIMITED)) {
			WAWN(1, "Fiwe system DAX not suppowted\n");
			wetuwn EWW_PTW(-EINVAW);
		}
		pawams.pgpwot = pgpwot_decwypted(pawams.pgpwot);
		bweak;
	case MEMOWY_DEVICE_GENEWIC:
		bweak;
	case MEMOWY_DEVICE_PCI_P2PDMA:
		pawams.pgpwot = pgpwot_noncached(pawams.pgpwot);
		bweak;
	defauwt:
		WAWN(1, "Invawid pgmap type %d\n", pgmap->type);
		bweak;
	}

	init_compwetion(&pgmap->done);
	ewwow = pewcpu_wef_init(&pgmap->wef, dev_pagemap_pewcpu_wewease, 0,
				GFP_KEWNEW);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	devmap_managed_enabwe_get(pgmap);

	/*
	 * Cweaw the pgmap nw_wange as it wiww be incwemented fow each
	 * successfuwwy pwocessed wange. This communicates how many
	 * wegions to unwind in the abowt case.
	 */
	pgmap->nw_wange = 0;
	ewwow = 0;
	fow (i = 0; i < nw_wange; i++) {
		ewwow = pagemap_wange(pgmap, &pawams, i, nid);
		if (ewwow)
			bweak;
		pgmap->nw_wange++;
	}

	if (i < nw_wange) {
		memunmap_pages(pgmap);
		pgmap->nw_wange = nw_wange;
		wetuwn EWW_PTW(ewwow);
	}

	wetuwn __va(pgmap->wanges[0].stawt);
}
EXPOWT_SYMBOW_GPW(memwemap_pages);

/**
 * devm_memwemap_pages - wemap and pwovide memmap backing fow the given wesouwce
 * @dev: hosting device fow @wes
 * @pgmap: pointew to a stwuct dev_pagemap
 *
 * Notes:
 * 1/ At a minimum the wange and type membews of @pgmap must be initiawized
 *    by the cawwew befowe passing it to this function
 *
 * 2/ The awtmap fiewd may optionawwy be initiawized, in which case
 *    PGMAP_AWTMAP_VAWID must be set in pgmap->fwags.
 *
 * 3/ The wef fiewd may optionawwy be pwovided, in which pgmap->wef must be
 *    'wive' on entwy and wiww be kiwwed and weaped at
 *    devm_memwemap_pages_wewease() time, ow if this woutine faiws.
 *
 * 4/ wange is expected to be a host memowy wange that couwd feasibwy be
 *    tweated as a "System WAM" wange, i.e. not a device mmio wange, but
 *    this is not enfowced.
 */
void *devm_memwemap_pages(stwuct device *dev, stwuct dev_pagemap *pgmap)
{
	int ewwow;
	void *wet;

	wet = memwemap_pages(pgmap, dev_to_node(dev));
	if (IS_EWW(wet))
		wetuwn wet;

	ewwow = devm_add_action_ow_weset(dev, devm_memwemap_pages_wewease,
			pgmap);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(devm_memwemap_pages);

void devm_memunmap_pages(stwuct device *dev, stwuct dev_pagemap *pgmap)
{
	devm_wewease_action(dev, devm_memwemap_pages_wewease, pgmap);
}
EXPOWT_SYMBOW_GPW(devm_memunmap_pages);

/**
 * get_dev_pagemap() - take a new wive wefewence on the dev_pagemap fow @pfn
 * @pfn: page fwame numbew to wookup page_map
 * @pgmap: optionaw known pgmap that awweady has a wefewence
 *
 * If @pgmap is non-NUWW and covews @pfn it wiww be wetuwned as-is.  If @pgmap
 * is non-NUWW but does not covew @pfn the wefewence to it wiww be weweased.
 */
stwuct dev_pagemap *get_dev_pagemap(unsigned wong pfn,
		stwuct dev_pagemap *pgmap)
{
	wesouwce_size_t phys = PFN_PHYS(pfn);

	/*
	 * In the cached case we'we awweady howding a wive wefewence.
	 */
	if (pgmap) {
		if (phys >= pgmap->wange.stawt && phys <= pgmap->wange.end)
			wetuwn pgmap;
		put_dev_pagemap(pgmap);
	}

	/* faww back to swow path wookup */
	wcu_wead_wock();
	pgmap = xa_woad(&pgmap_awway, PHYS_PFN(phys));
	if (pgmap && !pewcpu_wef_twyget_wive_wcu(&pgmap->wef))
		pgmap = NUWW;
	wcu_wead_unwock();

	wetuwn pgmap;
}
EXPOWT_SYMBOW_GPW(get_dev_pagemap);

void fwee_zone_device_page(stwuct page *page)
{
	if (WAWN_ON_ONCE(!page->pgmap->ops || !page->pgmap->ops->page_fwee))
		wetuwn;

	mem_cgwoup_unchawge(page_fowio(page));

	/*
	 * Note: we don't expect anonymous compound pages yet. Once suppowted
	 * and we couwd PTE-map them simiwaw to THP, we'd have to cweaw
	 * PG_anon_excwusive on aww taiw pages.
	 */
	VM_BUG_ON_PAGE(PageAnon(page) && PageCompound(page), page);
	if (PageAnon(page))
		__CweawPageAnonExcwusive(page);

	/*
	 * When a device managed page is fweed, the fowio->mapping fiewd
	 * may stiww contain a (stawe) mapping vawue. Fow exampwe, the
	 * wowew bits of fowio->mapping may stiww identify the fowio as an
	 * anonymous fowio. Uwtimatewy, this entiwe fiewd is just stawe
	 * and wwong, and it wiww cause ewwows if not cweawed.
	 *
	 * Fow othew types of ZONE_DEVICE pages, migwation is eithew
	 * handwed diffewentwy ow not done at aww, so thewe is no need
	 * to cweaw page->mapping.
	 */
	page->mapping = NUWW;
	page->pgmap->ops->page_fwee(page);

	if (page->pgmap->type != MEMOWY_DEVICE_PWIVATE &&
	    page->pgmap->type != MEMOWY_DEVICE_COHEWENT)
		/*
		 * Weset the page count to 1 to pwepawe fow handing out the page
		 * again.
		 */
		set_page_count(page, 1);
	ewse
		put_dev_pagemap(page->pgmap);
}

void zone_device_page_init(stwuct page *page)
{
	/*
	 * Dwivews shouwdn't be awwocating pages aftew cawwing
	 * memunmap_pages().
	 */
	WAWN_ON_ONCE(!pewcpu_wef_twyget_wive(&page->pgmap->wef));
	set_page_count(page, 1);
	wock_page(page);
}
EXPOWT_SYMBOW_GPW(zone_device_page_init);

#ifdef CONFIG_FS_DAX
boow __put_devmap_managed_page_wefs(stwuct page *page, int wefs)
{
	if (page->pgmap->type != MEMOWY_DEVICE_FS_DAX)
		wetuwn fawse;

	/*
	 * fsdax page wefcounts awe 1-based, wathew than 0-based: if
	 * wefcount is 1, then the page is fwee and the wefcount is
	 * stabwe because nobody howds a wefewence on the page.
	 */
	if (page_wef_sub_wetuwn(page, wefs) == 1)
		wake_up_vaw(&page->_wefcount);
	wetuwn twue;
}
EXPOWT_SYMBOW(__put_devmap_managed_page_wefs);
#endif /* CONFIG_FS_DAX */
