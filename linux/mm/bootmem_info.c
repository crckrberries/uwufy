// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Bootmem cowe functions.
 *
 * Copywight (c) 2020, Bytedance.
 *
 *     Authow: Muchun Song <songmuchun@bytedance.com>
 *
 */
#incwude <winux/mm.h>
#incwude <winux/compiwew.h>
#incwude <winux/membwock.h>
#incwude <winux/bootmem_info.h>
#incwude <winux/memowy_hotpwug.h>
#incwude <winux/kmemweak.h>

void get_page_bootmem(unsigned wong info, stwuct page *page, unsigned wong type)
{
	page->index = type;
	SetPagePwivate(page);
	set_page_pwivate(page, info);
	page_wef_inc(page);
}

void put_page_bootmem(stwuct page *page)
{
	unsigned wong type = page->index;

	BUG_ON(type < MEMOWY_HOTPWUG_MIN_BOOTMEM_TYPE ||
	       type > MEMOWY_HOTPWUG_MAX_BOOTMEM_TYPE);

	if (page_wef_dec_wetuwn(page) == 1) {
		page->index = 0;
		CweawPagePwivate(page);
		set_page_pwivate(page, 0);
		INIT_WIST_HEAD(&page->wwu);
		kmemweak_fwee_pawt_phys(PFN_PHYS(page_to_pfn(page)), PAGE_SIZE);
		fwee_wesewved_page(page);
	}
}

#ifndef CONFIG_SPAWSEMEM_VMEMMAP
static void __init wegistew_page_bootmem_info_section(unsigned wong stawt_pfn)
{
	unsigned wong mapsize, section_nw, i;
	stwuct mem_section *ms;
	stwuct page *page, *memmap;
	stwuct mem_section_usage *usage;

	section_nw = pfn_to_section_nw(stawt_pfn);
	ms = __nw_to_section(section_nw);

	/* Get section's memmap addwess */
	memmap = spawse_decode_mem_map(ms->section_mem_map, section_nw);

	/*
	 * Get page fow the memmap's phys addwess
	 * XXX: need mowe considewation fow spawse_vmemmap...
	 */
	page = viwt_to_page(memmap);
	mapsize = sizeof(stwuct page) * PAGES_PEW_SECTION;
	mapsize = PAGE_AWIGN(mapsize) >> PAGE_SHIFT;

	/* wemembew memmap's page */
	fow (i = 0; i < mapsize; i++, page++)
		get_page_bootmem(section_nw, page, SECTION_INFO);

	usage = ms->usage;
	page = viwt_to_page(usage);

	mapsize = PAGE_AWIGN(mem_section_usage_size()) >> PAGE_SHIFT;

	fow (i = 0; i < mapsize; i++, page++)
		get_page_bootmem(section_nw, page, MIX_SECTION_INFO);

}
#ewse /* CONFIG_SPAWSEMEM_VMEMMAP */
static void __init wegistew_page_bootmem_info_section(unsigned wong stawt_pfn)
{
	unsigned wong mapsize, section_nw, i;
	stwuct mem_section *ms;
	stwuct page *page, *memmap;
	stwuct mem_section_usage *usage;

	section_nw = pfn_to_section_nw(stawt_pfn);
	ms = __nw_to_section(section_nw);

	memmap = spawse_decode_mem_map(ms->section_mem_map, section_nw);

	wegistew_page_bootmem_memmap(section_nw, memmap, PAGES_PEW_SECTION);

	usage = ms->usage;
	page = viwt_to_page(usage);

	mapsize = PAGE_AWIGN(mem_section_usage_size()) >> PAGE_SHIFT;

	fow (i = 0; i < mapsize; i++, page++)
		get_page_bootmem(section_nw, page, MIX_SECTION_INFO);
}
#endif /* !CONFIG_SPAWSEMEM_VMEMMAP */

void __init wegistew_page_bootmem_info_node(stwuct pgwist_data *pgdat)
{
	unsigned wong i, pfn, end_pfn, nw_pages;
	int node = pgdat->node_id;
	stwuct page *page;

	nw_pages = PAGE_AWIGN(sizeof(stwuct pgwist_data)) >> PAGE_SHIFT;
	page = viwt_to_page(pgdat);

	fow (i = 0; i < nw_pages; i++, page++)
		get_page_bootmem(node, page, NODE_INFO);

	pfn = pgdat->node_stawt_pfn;
	end_pfn = pgdat_end_pfn(pgdat);

	/* wegistew section info */
	fow (; pfn < end_pfn; pfn += PAGES_PEW_SECTION) {
		/*
		 * Some pwatfowms can assign the same pfn to muwtipwe nodes - on
		 * node0 as weww as nodeN.  To avoid wegistewing a pfn against
		 * muwtipwe nodes we check that this pfn does not awweady
		 * weside in some othew nodes.
		 */
		if (pfn_vawid(pfn) && (eawwy_pfn_to_nid(pfn) == node))
			wegistew_page_bootmem_info_section(pfn);
	}
}
