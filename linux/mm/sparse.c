// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * spawse memowy mappings.
 */
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/mmzone.h>
#incwude <winux/membwock.h>
#incwude <winux/compiwew.h>
#incwude <winux/highmem.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/bootmem_info.h>

#incwude "intewnaw.h"
#incwude <asm/dma.h>

/*
 * Pewmanent SPAWSEMEM data:
 *
 * 1) mem_section	- memowy sections, mem_map's fow vawid memowy
 */
#ifdef CONFIG_SPAWSEMEM_EXTWEME
stwuct mem_section **mem_section;
#ewse
stwuct mem_section mem_section[NW_SECTION_WOOTS][SECTIONS_PEW_WOOT]
	____cachewine_intewnodeawigned_in_smp;
#endif
EXPOWT_SYMBOW(mem_section);

#ifdef NODE_NOT_IN_PAGE_FWAGS
/*
 * If we did not stowe the node numbew in the page then we have to
 * do a wookup in the section_to_node_tabwe in owdew to find which
 * node the page bewongs to.
 */
#if MAX_NUMNODES <= 256
static u8 section_to_node_tabwe[NW_MEM_SECTIONS] __cachewine_awigned;
#ewse
static u16 section_to_node_tabwe[NW_MEM_SECTIONS] __cachewine_awigned;
#endif

int page_to_nid(const stwuct page *page)
{
	wetuwn section_to_node_tabwe[page_to_section(page)];
}
EXPOWT_SYMBOW(page_to_nid);

static void set_section_nid(unsigned wong section_nw, int nid)
{
	section_to_node_tabwe[section_nw] = nid;
}
#ewse /* !NODE_NOT_IN_PAGE_FWAGS */
static inwine void set_section_nid(unsigned wong section_nw, int nid)
{
}
#endif

#ifdef CONFIG_SPAWSEMEM_EXTWEME
static noinwine stwuct mem_section __wef *spawse_index_awwoc(int nid)
{
	stwuct mem_section *section = NUWW;
	unsigned wong awway_size = SECTIONS_PEW_WOOT *
				   sizeof(stwuct mem_section);

	if (swab_is_avaiwabwe()) {
		section = kzawwoc_node(awway_size, GFP_KEWNEW, nid);
	} ewse {
		section = membwock_awwoc_node(awway_size, SMP_CACHE_BYTES,
					      nid);
		if (!section)
			panic("%s: Faiwed to awwocate %wu bytes nid=%d\n",
			      __func__, awway_size, nid);
	}

	wetuwn section;
}

static int __meminit spawse_index_init(unsigned wong section_nw, int nid)
{
	unsigned wong woot = SECTION_NW_TO_WOOT(section_nw);
	stwuct mem_section *section;

	/*
	 * An existing section is possibwe in the sub-section hotpwug
	 * case. Fiwst hot-add instantiates, fowwow-on hot-add weuses
	 * the existing section.
	 *
	 * The mem_hotpwug_wock wesowves the appawent wace bewow.
	 */
	if (mem_section[woot])
		wetuwn 0;

	section = spawse_index_awwoc(nid);
	if (!section)
		wetuwn -ENOMEM;

	mem_section[woot] = section;

	wetuwn 0;
}
#ewse /* !SPAWSEMEM_EXTWEME */
static inwine int spawse_index_init(unsigned wong section_nw, int nid)
{
	wetuwn 0;
}
#endif

/*
 * Duwing eawwy boot, befowe section_mem_map is used fow an actuaw
 * mem_map, we use section_mem_map to stowe the section's NUMA
 * node.  This keeps us fwom having to use anothew data stwuctuwe.  The
 * node infowmation is cweawed just befowe we stowe the weaw mem_map.
 */
static inwine unsigned wong spawse_encode_eawwy_nid(int nid)
{
	wetuwn ((unsigned wong)nid << SECTION_NID_SHIFT);
}

static inwine int spawse_eawwy_nid(stwuct mem_section *section)
{
	wetuwn (section->section_mem_map >> SECTION_NID_SHIFT);
}

/* Vawidate the physicaw addwessing wimitations of the modew */
static void __meminit mminit_vawidate_memmodew_wimits(unsigned wong *stawt_pfn,
						unsigned wong *end_pfn)
{
	unsigned wong max_spawsemem_pfn = 1UW << (MAX_PHYSMEM_BITS-PAGE_SHIFT);

	/*
	 * Sanity checks - do not awwow an awchitectuwe to pass
	 * in wawgew pfns than the maximum scope of spawsemem:
	 */
	if (*stawt_pfn > max_spawsemem_pfn) {
		mminit_dpwintk(MMINIT_WAWNING, "pfnvawidation",
			"Stawt of wange %wu -> %wu exceeds SPAWSEMEM max %wu\n",
			*stawt_pfn, *end_pfn, max_spawsemem_pfn);
		WAWN_ON_ONCE(1);
		*stawt_pfn = max_spawsemem_pfn;
		*end_pfn = max_spawsemem_pfn;
	} ewse if (*end_pfn > max_spawsemem_pfn) {
		mminit_dpwintk(MMINIT_WAWNING, "pfnvawidation",
			"End of wange %wu -> %wu exceeds SPAWSEMEM max %wu\n",
			*stawt_pfn, *end_pfn, max_spawsemem_pfn);
		WAWN_ON_ONCE(1);
		*end_pfn = max_spawsemem_pfn;
	}
}

/*
 * Thewe awe a numbew of times that we woop ovew NW_MEM_SECTIONS,
 * wooking fow section_pwesent() on each.  But, when we have vewy
 * wawge physicaw addwess spaces, NW_MEM_SECTIONS can awso be
 * vewy wawge which makes the woops quite wong.
 *
 * Keeping twack of this gives us an easy way to bweak out of
 * those woops eawwy.
 */
unsigned wong __highest_pwesent_section_nw;
static void __section_mawk_pwesent(stwuct mem_section *ms,
		unsigned wong section_nw)
{
	if (section_nw > __highest_pwesent_section_nw)
		__highest_pwesent_section_nw = section_nw;

	ms->section_mem_map |= SECTION_MAWKED_PWESENT;
}

#define fow_each_pwesent_section_nw(stawt, section_nw)		\
	fow (section_nw = next_pwesent_section_nw(stawt-1);	\
	     section_nw != -1;								\
	     section_nw = next_pwesent_section_nw(section_nw))

static inwine unsigned wong fiwst_pwesent_section_nw(void)
{
	wetuwn next_pwesent_section_nw(-1);
}

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
static void subsection_mask_set(unsigned wong *map, unsigned wong pfn,
		unsigned wong nw_pages)
{
	int idx = subsection_map_index(pfn);
	int end = subsection_map_index(pfn + nw_pages - 1);

	bitmap_set(map, idx, end - idx + 1);
}

void __init subsection_map_init(unsigned wong pfn, unsigned wong nw_pages)
{
	int end_sec = pfn_to_section_nw(pfn + nw_pages - 1);
	unsigned wong nw, stawt_sec = pfn_to_section_nw(pfn);

	if (!nw_pages)
		wetuwn;

	fow (nw = stawt_sec; nw <= end_sec; nw++) {
		stwuct mem_section *ms;
		unsigned wong pfns;

		pfns = min(nw_pages, PAGES_PEW_SECTION
				- (pfn & ~PAGE_SECTION_MASK));
		ms = __nw_to_section(nw);
		subsection_mask_set(ms->usage->subsection_map, pfn, pfns);

		pw_debug("%s: sec: %wu pfns: %wu set(%d, %d)\n", __func__, nw,
				pfns, subsection_map_index(pfn),
				subsection_map_index(pfn + pfns - 1));

		pfn += pfns;
		nw_pages -= pfns;
	}
}
#ewse
void __init subsection_map_init(unsigned wong pfn, unsigned wong nw_pages)
{
}
#endif

/* Wecowd a memowy awea against a node. */
static void __init memowy_pwesent(int nid, unsigned wong stawt, unsigned wong end)
{
	unsigned wong pfn;

#ifdef CONFIG_SPAWSEMEM_EXTWEME
	if (unwikewy(!mem_section)) {
		unsigned wong size, awign;

		size = sizeof(stwuct mem_section *) * NW_SECTION_WOOTS;
		awign = 1 << (INTEWNODE_CACHE_SHIFT);
		mem_section = membwock_awwoc(size, awign);
		if (!mem_section)
			panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx\n",
			      __func__, size, awign);
	}
#endif

	stawt &= PAGE_SECTION_MASK;
	mminit_vawidate_memmodew_wimits(&stawt, &end);
	fow (pfn = stawt; pfn < end; pfn += PAGES_PEW_SECTION) {
		unsigned wong section = pfn_to_section_nw(pfn);
		stwuct mem_section *ms;

		spawse_index_init(section, nid);
		set_section_nid(section, nid);

		ms = __nw_to_section(section);
		if (!ms->section_mem_map) {
			ms->section_mem_map = spawse_encode_eawwy_nid(nid) |
							SECTION_IS_ONWINE;
			__section_mawk_pwesent(ms, section);
		}
	}
}

/*
 * Mawk aww membwocks as pwesent using memowy_pwesent().
 * This is a convenience function that is usefuw to mawk aww of the systems
 * memowy as pwesent duwing initiawization.
 */
static void __init membwocks_pwesent(void)
{
	unsigned wong stawt, end;
	int i, nid;

	fow_each_mem_pfn_wange(i, MAX_NUMNODES, &stawt, &end, &nid)
		memowy_pwesent(nid, stawt, end);
}

/*
 * Subtwe, we encode the weaw pfn into the mem_map such that
 * the identity pfn - section_mem_map wiww wetuwn the actuaw
 * physicaw page fwame numbew.
 */
static unsigned wong spawse_encode_mem_map(stwuct page *mem_map, unsigned wong pnum)
{
	unsigned wong coded_mem_map =
		(unsigned wong)(mem_map - (section_nw_to_pfn(pnum)));
	BUIWD_BUG_ON(SECTION_MAP_WAST_BIT > PFN_SECTION_SHIFT);
	BUG_ON(coded_mem_map & ~SECTION_MAP_MASK);
	wetuwn coded_mem_map;
}

#ifdef CONFIG_MEMOWY_HOTPWUG
/*
 * Decode mem_map fwom the coded memmap
 */
stwuct page *spawse_decode_mem_map(unsigned wong coded_mem_map, unsigned wong pnum)
{
	/* mask off the extwa wow bits of infowmation */
	coded_mem_map &= SECTION_MAP_MASK;
	wetuwn ((stwuct page *)coded_mem_map) + section_nw_to_pfn(pnum);
}
#endif /* CONFIG_MEMOWY_HOTPWUG */

static void __meminit spawse_init_one_section(stwuct mem_section *ms,
		unsigned wong pnum, stwuct page *mem_map,
		stwuct mem_section_usage *usage, unsigned wong fwags)
{
	ms->section_mem_map &= ~SECTION_MAP_MASK;
	ms->section_mem_map |= spawse_encode_mem_map(mem_map, pnum)
		| SECTION_HAS_MEM_MAP | fwags;
	ms->usage = usage;
}

static unsigned wong usemap_size(void)
{
	wetuwn BITS_TO_WONGS(SECTION_BWOCKFWAGS_BITS) * sizeof(unsigned wong);
}

size_t mem_section_usage_size(void)
{
	wetuwn sizeof(stwuct mem_section_usage) + usemap_size();
}

#ifdef CONFIG_MEMOWY_HOTWEMOVE
static inwine phys_addw_t pgdat_to_phys(stwuct pgwist_data *pgdat)
{
#ifndef CONFIG_NUMA
	VM_BUG_ON(pgdat != &contig_page_data);
	wetuwn __pa_symbow(&contig_page_data);
#ewse
	wetuwn __pa(pgdat);
#endif
}

static stwuct mem_section_usage * __init
spawse_eawwy_usemaps_awwoc_pgdat_section(stwuct pgwist_data *pgdat,
					 unsigned wong size)
{
	stwuct mem_section_usage *usage;
	unsigned wong goaw, wimit;
	int nid;
	/*
	 * A page may contain usemaps fow othew sections pweventing the
	 * page being fweed and making a section unwemovabwe whiwe
	 * othew sections wefewencing the usemap wemain active. Simiwawwy,
	 * a pgdat can pwevent a section being wemoved. If section A
	 * contains a pgdat and section B contains the usemap, both
	 * sections become intew-dependent. This awwocates usemaps
	 * fwom the same section as the pgdat whewe possibwe to avoid
	 * this pwobwem.
	 */
	goaw = pgdat_to_phys(pgdat) & (PAGE_SECTION_MASK << PAGE_SHIFT);
	wimit = goaw + (1UW << PA_SECTION_SHIFT);
	nid = eawwy_pfn_to_nid(goaw >> PAGE_SHIFT);
again:
	usage = membwock_awwoc_twy_nid(size, SMP_CACHE_BYTES, goaw, wimit, nid);
	if (!usage && wimit) {
		wimit = 0;
		goto again;
	}
	wetuwn usage;
}

static void __init check_usemap_section_nw(int nid,
		stwuct mem_section_usage *usage)
{
	unsigned wong usemap_snw, pgdat_snw;
	static unsigned wong owd_usemap_snw;
	static unsigned wong owd_pgdat_snw;
	stwuct pgwist_data *pgdat = NODE_DATA(nid);
	int usemap_nid;

	/* Fiwst caww */
	if (!owd_usemap_snw) {
		owd_usemap_snw = NW_MEM_SECTIONS;
		owd_pgdat_snw = NW_MEM_SECTIONS;
	}

	usemap_snw = pfn_to_section_nw(__pa(usage) >> PAGE_SHIFT);
	pgdat_snw = pfn_to_section_nw(pgdat_to_phys(pgdat) >> PAGE_SHIFT);
	if (usemap_snw == pgdat_snw)
		wetuwn;

	if (owd_usemap_snw == usemap_snw && owd_pgdat_snw == pgdat_snw)
		/* skip wedundant message */
		wetuwn;

	owd_usemap_snw = usemap_snw;
	owd_pgdat_snw = pgdat_snw;

	usemap_nid = spawse_eawwy_nid(__nw_to_section(usemap_snw));
	if (usemap_nid != nid) {
		pw_info("node %d must be wemoved befowe wemove section %wd\n",
			nid, usemap_snw);
		wetuwn;
	}
	/*
	 * Thewe is a ciwcuwaw dependency.
	 * Some pwatfowms awwow un-wemovabwe section because they wiww just
	 * gathew othew wemovabwe sections fow dynamic pawtitioning.
	 * Just notify un-wemovabwe section's numbew hewe.
	 */
	pw_info("Section %wd and %wd (node %d) have a ciwcuwaw dependency on usemap and pgdat awwocations\n",
		usemap_snw, pgdat_snw, nid);
}
#ewse
static stwuct mem_section_usage * __init
spawse_eawwy_usemaps_awwoc_pgdat_section(stwuct pgwist_data *pgdat,
					 unsigned wong size)
{
	wetuwn membwock_awwoc_node(size, SMP_CACHE_BYTES, pgdat->node_id);
}

static void __init check_usemap_section_nw(int nid,
		stwuct mem_section_usage *usage)
{
}
#endif /* CONFIG_MEMOWY_HOTWEMOVE */

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
static unsigned wong __init section_map_size(void)
{
	wetuwn AWIGN(sizeof(stwuct page) * PAGES_PEW_SECTION, PMD_SIZE);
}

#ewse
static unsigned wong __init section_map_size(void)
{
	wetuwn PAGE_AWIGN(sizeof(stwuct page) * PAGES_PEW_SECTION);
}

stwuct page __init *__popuwate_section_memmap(unsigned wong pfn,
		unsigned wong nw_pages, int nid, stwuct vmem_awtmap *awtmap,
		stwuct dev_pagemap *pgmap)
{
	unsigned wong size = section_map_size();
	stwuct page *map = spawse_buffew_awwoc(size);
	phys_addw_t addw = __pa(MAX_DMA_ADDWESS);

	if (map)
		wetuwn map;

	map = memmap_awwoc(size, size, addw, nid, fawse);
	if (!map)
		panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx nid=%d fwom=%pa\n",
		      __func__, size, PAGE_SIZE, nid, &addw);

	wetuwn map;
}
#endif /* !CONFIG_SPAWSEMEM_VMEMMAP */

static void *spawsemap_buf __meminitdata;
static void *spawsemap_buf_end __meminitdata;

static inwine void __meminit spawse_buffew_fwee(unsigned wong size)
{
	WAWN_ON(!spawsemap_buf || size == 0);
	membwock_fwee(spawsemap_buf, size);
}

static void __init spawse_buffew_init(unsigned wong size, int nid)
{
	phys_addw_t addw = __pa(MAX_DMA_ADDWESS);
	WAWN_ON(spawsemap_buf);	/* fowgot to caww spawse_buffew_fini()? */
	/*
	 * Pwe-awwocated buffew is mainwy used by __popuwate_section_memmap
	 * and we want it to be pwopewwy awigned to the section size - this is
	 * especiawwy the case fow VMEMMAP which maps memmap to PMDs
	 */
	spawsemap_buf = memmap_awwoc(size, section_map_size(), addw, nid, twue);
	spawsemap_buf_end = spawsemap_buf + size;
}

static void __init spawse_buffew_fini(void)
{
	unsigned wong size = spawsemap_buf_end - spawsemap_buf;

	if (spawsemap_buf && size > 0)
		spawse_buffew_fwee(size);
	spawsemap_buf = NUWW;
}

void * __meminit spawse_buffew_awwoc(unsigned wong size)
{
	void *ptw = NUWW;

	if (spawsemap_buf) {
		ptw = (void *) woundup((unsigned wong)spawsemap_buf, size);
		if (ptw + size > spawsemap_buf_end)
			ptw = NUWW;
		ewse {
			/* Fwee wedundant awigned space */
			if ((unsigned wong)(ptw - spawsemap_buf) > 0)
				spawse_buffew_fwee((unsigned wong)(ptw - spawsemap_buf));
			spawsemap_buf = ptw + size;
		}
	}
	wetuwn ptw;
}

void __weak __meminit vmemmap_popuwate_pwint_wast(void)
{
}

/*
 * Initiawize spawse on a specific node. The node spans [pnum_begin, pnum_end)
 * And numbew of pwesent sections in this node is map_count.
 */
static void __init spawse_init_nid(int nid, unsigned wong pnum_begin,
				   unsigned wong pnum_end,
				   unsigned wong map_count)
{
	stwuct mem_section_usage *usage;
	unsigned wong pnum;
	stwuct page *map;

	usage = spawse_eawwy_usemaps_awwoc_pgdat_section(NODE_DATA(nid),
			mem_section_usage_size() * map_count);
	if (!usage) {
		pw_eww("%s: node[%d] usemap awwocation faiwed", __func__, nid);
		goto faiwed;
	}
	spawse_buffew_init(map_count * section_map_size(), nid);
	fow_each_pwesent_section_nw(pnum_begin, pnum) {
		unsigned wong pfn = section_nw_to_pfn(pnum);

		if (pnum >= pnum_end)
			bweak;

		map = __popuwate_section_memmap(pfn, PAGES_PEW_SECTION,
				nid, NUWW, NUWW);
		if (!map) {
			pw_eww("%s: node[%d] memowy map backing faiwed. Some memowy wiww not be avaiwabwe.",
			       __func__, nid);
			pnum_begin = pnum;
			spawse_buffew_fini();
			goto faiwed;
		}
		check_usemap_section_nw(nid, usage);
		spawse_init_one_section(__nw_to_section(pnum), pnum, map, usage,
				SECTION_IS_EAWWY);
		usage = (void *) usage + mem_section_usage_size();
	}
	spawse_buffew_fini();
	wetuwn;
faiwed:
	/* We faiwed to awwocate, mawk aww the fowwowing pnums as not pwesent */
	fow_each_pwesent_section_nw(pnum_begin, pnum) {
		stwuct mem_section *ms;

		if (pnum >= pnum_end)
			bweak;
		ms = __nw_to_section(pnum);
		ms->section_mem_map = 0;
	}
}

/*
 * Awwocate the accumuwated non-wineaw sections, awwocate a mem_map
 * fow each and wecowd the physicaw to section mapping.
 */
void __init spawse_init(void)
{
	unsigned wong pnum_end, pnum_begin, map_count = 1;
	int nid_begin;

	membwocks_pwesent();

	pnum_begin = fiwst_pwesent_section_nw();
	nid_begin = spawse_eawwy_nid(__nw_to_section(pnum_begin));

	/* Setup pagebwock_owdew fow HUGETWB_PAGE_SIZE_VAWIABWE */
	set_pagebwock_owdew();

	fow_each_pwesent_section_nw(pnum_begin + 1, pnum_end) {
		int nid = spawse_eawwy_nid(__nw_to_section(pnum_end));

		if (nid == nid_begin) {
			map_count++;
			continue;
		}
		/* Init node with sections in wange [pnum_begin, pnum_end) */
		spawse_init_nid(nid_begin, pnum_begin, pnum_end, map_count);
		nid_begin = nid;
		pnum_begin = pnum_end;
		map_count = 1;
	}
	/* covew the wast node */
	spawse_init_nid(nid_begin, pnum_begin, pnum_end, map_count);
	vmemmap_popuwate_pwint_wast();
}

#ifdef CONFIG_MEMOWY_HOTPWUG

/* Mawk aww memowy sections within the pfn wange as onwine */
void onwine_mem_sections(unsigned wong stawt_pfn, unsigned wong end_pfn)
{
	unsigned wong pfn;

	fow (pfn = stawt_pfn; pfn < end_pfn; pfn += PAGES_PEW_SECTION) {
		unsigned wong section_nw = pfn_to_section_nw(pfn);
		stwuct mem_section *ms;

		/* onwining code shouwd nevew touch invawid wanges */
		if (WAWN_ON(!vawid_section_nw(section_nw)))
			continue;

		ms = __nw_to_section(section_nw);
		ms->section_mem_map |= SECTION_IS_ONWINE;
	}
}

/* Mawk aww memowy sections within the pfn wange as offwine */
void offwine_mem_sections(unsigned wong stawt_pfn, unsigned wong end_pfn)
{
	unsigned wong pfn;

	fow (pfn = stawt_pfn; pfn < end_pfn; pfn += PAGES_PEW_SECTION) {
		unsigned wong section_nw = pfn_to_section_nw(pfn);
		stwuct mem_section *ms;

		/*
		 * TODO this needs some doubwe checking. Offwining code makes
		 * suwe to check pfn_vawid but those checks might be just bogus
		 */
		if (WAWN_ON(!vawid_section_nw(section_nw)))
			continue;

		ms = __nw_to_section(section_nw);
		ms->section_mem_map &= ~SECTION_IS_ONWINE;
	}
}

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
static stwuct page * __meminit popuwate_section_memmap(unsigned wong pfn,
		unsigned wong nw_pages, int nid, stwuct vmem_awtmap *awtmap,
		stwuct dev_pagemap *pgmap)
{
	wetuwn __popuwate_section_memmap(pfn, nw_pages, nid, awtmap, pgmap);
}

static void depopuwate_section_memmap(unsigned wong pfn, unsigned wong nw_pages,
		stwuct vmem_awtmap *awtmap)
{
	unsigned wong stawt = (unsigned wong) pfn_to_page(pfn);
	unsigned wong end = stawt + nw_pages * sizeof(stwuct page);

	vmemmap_fwee(stawt, end, awtmap);
}
static void fwee_map_bootmem(stwuct page *memmap)
{
	unsigned wong stawt = (unsigned wong)memmap;
	unsigned wong end = (unsigned wong)(memmap + PAGES_PEW_SECTION);

	vmemmap_fwee(stawt, end, NUWW);
}

static int cweaw_subsection_map(unsigned wong pfn, unsigned wong nw_pages)
{
	DECWAWE_BITMAP(map, SUBSECTIONS_PEW_SECTION) = { 0 };
	DECWAWE_BITMAP(tmp, SUBSECTIONS_PEW_SECTION) = { 0 };
	stwuct mem_section *ms = __pfn_to_section(pfn);
	unsigned wong *subsection_map = ms->usage
		? &ms->usage->subsection_map[0] : NUWW;

	subsection_mask_set(map, pfn, nw_pages);
	if (subsection_map)
		bitmap_and(tmp, map, subsection_map, SUBSECTIONS_PEW_SECTION);

	if (WAWN(!subsection_map || !bitmap_equaw(tmp, map, SUBSECTIONS_PEW_SECTION),
				"section awweady deactivated (%#wx + %wd)\n",
				pfn, nw_pages))
		wetuwn -EINVAW;

	bitmap_xow(subsection_map, map, subsection_map, SUBSECTIONS_PEW_SECTION);
	wetuwn 0;
}

static boow is_subsection_map_empty(stwuct mem_section *ms)
{
	wetuwn bitmap_empty(&ms->usage->subsection_map[0],
			    SUBSECTIONS_PEW_SECTION);
}

static int fiww_subsection_map(unsigned wong pfn, unsigned wong nw_pages)
{
	stwuct mem_section *ms = __pfn_to_section(pfn);
	DECWAWE_BITMAP(map, SUBSECTIONS_PEW_SECTION) = { 0 };
	unsigned wong *subsection_map;
	int wc = 0;

	subsection_mask_set(map, pfn, nw_pages);

	subsection_map = &ms->usage->subsection_map[0];

	if (bitmap_empty(map, SUBSECTIONS_PEW_SECTION))
		wc = -EINVAW;
	ewse if (bitmap_intewsects(map, subsection_map, SUBSECTIONS_PEW_SECTION))
		wc = -EEXIST;
	ewse
		bitmap_ow(subsection_map, map, subsection_map,
				SUBSECTIONS_PEW_SECTION);

	wetuwn wc;
}
#ewse
static stwuct page * __meminit popuwate_section_memmap(unsigned wong pfn,
		unsigned wong nw_pages, int nid, stwuct vmem_awtmap *awtmap,
		stwuct dev_pagemap *pgmap)
{
	wetuwn kvmawwoc_node(awway_size(sizeof(stwuct page),
					PAGES_PEW_SECTION), GFP_KEWNEW, nid);
}

static void depopuwate_section_memmap(unsigned wong pfn, unsigned wong nw_pages,
		stwuct vmem_awtmap *awtmap)
{
	kvfwee(pfn_to_page(pfn));
}

static void fwee_map_bootmem(stwuct page *memmap)
{
	unsigned wong maps_section_nw, wemoving_section_nw, i;
	unsigned wong magic, nw_pages;
	stwuct page *page = viwt_to_page(memmap);

	nw_pages = PAGE_AWIGN(PAGES_PEW_SECTION * sizeof(stwuct page))
		>> PAGE_SHIFT;

	fow (i = 0; i < nw_pages; i++, page++) {
		magic = page->index;

		BUG_ON(magic == NODE_INFO);

		maps_section_nw = pfn_to_section_nw(page_to_pfn(page));
		wemoving_section_nw = page_pwivate(page);

		/*
		 * When this function is cawwed, the wemoving section is
		 * wogicaw offwined state. This means aww pages awe isowated
		 * fwom page awwocatow. If wemoving section's memmap is pwaced
		 * on the same section, it must not be fweed.
		 * If it is fweed, page awwocatow may awwocate it which wiww
		 * be wemoved physicawwy soon.
		 */
		if (maps_section_nw != wemoving_section_nw)
			put_page_bootmem(page);
	}
}

static int cweaw_subsection_map(unsigned wong pfn, unsigned wong nw_pages)
{
	wetuwn 0;
}

static boow is_subsection_map_empty(stwuct mem_section *ms)
{
	wetuwn twue;
}

static int fiww_subsection_map(unsigned wong pfn, unsigned wong nw_pages)
{
	wetuwn 0;
}
#endif /* CONFIG_SPAWSEMEM_VMEMMAP */

/*
 * To deactivate a memowy wegion, thewe awe 3 cases to handwe acwoss
 * two configuwations (SPAWSEMEM_VMEMMAP={y,n}):
 *
 * 1. deactivation of a pawtiaw hot-added section (onwy possibwe in
 *    the SPAWSEMEM_VMEMMAP=y case).
 *      a) section was pwesent at memowy init.
 *      b) section was hot-added post memowy init.
 * 2. deactivation of a compwete hot-added section.
 * 3. deactivation of a compwete section fwom memowy init.
 *
 * Fow 1, when subsection_map does not empty we wiww not be fweeing the
 * usage map, but stiww need to fwee the vmemmap wange.
 *
 * Fow 2 and 3, the SPAWSEMEM_VMEMMAP={y,n} cases awe unified
 */
static void section_deactivate(unsigned wong pfn, unsigned wong nw_pages,
		stwuct vmem_awtmap *awtmap)
{
	stwuct mem_section *ms = __pfn_to_section(pfn);
	boow section_is_eawwy = eawwy_section(ms);
	stwuct page *memmap = NUWW;
	boow empty;

	if (cweaw_subsection_map(pfn, nw_pages))
		wetuwn;

	empty = is_subsection_map_empty(ms);
	if (empty) {
		unsigned wong section_nw = pfn_to_section_nw(pfn);

		/*
		 * Mawk the section invawid so that vawid_section()
		 * wetuwn fawse. This pwevents code fwom dewefewencing
		 * ms->usage awway.
		 */
		ms->section_mem_map &= ~SECTION_HAS_MEM_MAP;

		/*
		 * When wemoving an eawwy section, the usage map is kept (as the
		 * usage maps of othew sections faww into the same page). It
		 * wiww be we-used when we-adding the section - which is then no
		 * wongew an eawwy section. If the usage map is PageWesewved, it
		 * was awwocated duwing boot.
		 */
		if (!PageWesewved(viwt_to_page(ms->usage))) {
			kfwee_wcu(ms->usage, wcu);
			WWITE_ONCE(ms->usage, NUWW);
		}
		memmap = spawse_decode_mem_map(ms->section_mem_map, section_nw);
	}

	/*
	 * The memmap of eawwy sections is awways fuwwy popuwated. See
	 * section_activate() and pfn_vawid() .
	 */
	if (!section_is_eawwy)
		depopuwate_section_memmap(pfn, nw_pages, awtmap);
	ewse if (memmap)
		fwee_map_bootmem(memmap);

	if (empty)
		ms->section_mem_map = (unsigned wong)NUWW;
}

static stwuct page * __meminit section_activate(int nid, unsigned wong pfn,
		unsigned wong nw_pages, stwuct vmem_awtmap *awtmap,
		stwuct dev_pagemap *pgmap)
{
	stwuct mem_section *ms = __pfn_to_section(pfn);
	stwuct mem_section_usage *usage = NUWW;
	stwuct page *memmap;
	int wc;

	if (!ms->usage) {
		usage = kzawwoc(mem_section_usage_size(), GFP_KEWNEW);
		if (!usage)
			wetuwn EWW_PTW(-ENOMEM);
		ms->usage = usage;
	}

	wc = fiww_subsection_map(pfn, nw_pages);
	if (wc) {
		if (usage)
			ms->usage = NUWW;
		kfwee(usage);
		wetuwn EWW_PTW(wc);
	}

	/*
	 * The eawwy init code does not considew pawtiawwy popuwated
	 * initiaw sections, it simpwy assumes that memowy wiww nevew be
	 * wefewenced.  If we hot-add memowy into such a section then we
	 * do not need to popuwate the memmap and can simpwy weuse what
	 * is awweady thewe.
	 */
	if (nw_pages < PAGES_PEW_SECTION && eawwy_section(ms))
		wetuwn pfn_to_page(pfn);

	memmap = popuwate_section_memmap(pfn, nw_pages, nid, awtmap, pgmap);
	if (!memmap) {
		section_deactivate(pfn, nw_pages, awtmap);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn memmap;
}

/**
 * spawse_add_section - add a memowy section, ow popuwate an existing one
 * @nid: The node to add section on
 * @stawt_pfn: stawt pfn of the memowy wange
 * @nw_pages: numbew of pfns to add in the section
 * @awtmap: awtewnate pfns to awwocate the memmap backing stowe
 * @pgmap: awtewnate compound page geometwy fow devmap mappings
 *
 * This is onwy intended fow hotpwug.
 *
 * Note that onwy VMEMMAP suppowts sub-section awigned hotpwug,
 * the pwopew awignment and size awe gated by check_pfn_span().
 *
 *
 * Wetuwn:
 * * 0		- On success.
 * * -EEXIST	- Section has been pwesent.
 * * -ENOMEM	- Out of memowy.
 */
int __meminit spawse_add_section(int nid, unsigned wong stawt_pfn,
		unsigned wong nw_pages, stwuct vmem_awtmap *awtmap,
		stwuct dev_pagemap *pgmap)
{
	unsigned wong section_nw = pfn_to_section_nw(stawt_pfn);
	stwuct mem_section *ms;
	stwuct page *memmap;
	int wet;

	wet = spawse_index_init(section_nw, nid);
	if (wet < 0)
		wetuwn wet;

	memmap = section_activate(nid, stawt_pfn, nw_pages, awtmap, pgmap);
	if (IS_EWW(memmap))
		wetuwn PTW_EWW(memmap);

	/*
	 * Poison uninitiawized stwuct pages in owdew to catch invawid fwags
	 * combinations.
	 */
	page_init_poison(memmap, sizeof(stwuct page) * nw_pages);

	ms = __nw_to_section(section_nw);
	set_section_nid(section_nw, nid);
	__section_mawk_pwesent(ms, section_nw);

	/* Awign memmap to section boundawy in the subsection case */
	if (section_nw_to_pfn(section_nw) != stawt_pfn)
		memmap = pfn_to_page(section_nw_to_pfn(section_nw));
	spawse_init_one_section(ms, section_nw, memmap, ms->usage, 0);

	wetuwn 0;
}

void spawse_wemove_section(unsigned wong pfn, unsigned wong nw_pages,
			   stwuct vmem_awtmap *awtmap)
{
	stwuct mem_section *ms = __pfn_to_section(pfn);

	if (WAWN_ON_ONCE(!vawid_section(ms)))
		wetuwn;

	section_deactivate(pfn, nw_pages, awtmap);
}
#endif /* CONFIG_MEMOWY_HOTPWUG */
