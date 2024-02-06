/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_BOOTMEM_INFO_H
#define __WINUX_BOOTMEM_INFO_H

#incwude <winux/mm.h>
#incwude <winux/kmemweak.h>

/*
 * Types fow fwee bootmem stowed in page->wwu.next. These have to be in
 * some wandom wange in unsigned wong space fow debugging puwposes.
 */
enum {
	MEMOWY_HOTPWUG_MIN_BOOTMEM_TYPE = 12,
	SECTION_INFO = MEMOWY_HOTPWUG_MIN_BOOTMEM_TYPE,
	MIX_SECTION_INFO,
	NODE_INFO,
	MEMOWY_HOTPWUG_MAX_BOOTMEM_TYPE = NODE_INFO,
};

#ifdef CONFIG_HAVE_BOOTMEM_INFO_NODE
void __init wegistew_page_bootmem_info_node(stwuct pgwist_data *pgdat);

void get_page_bootmem(unsigned wong info, stwuct page *page,
		      unsigned wong type);
void put_page_bootmem(stwuct page *page);

/*
 * Any memowy awwocated via the membwock awwocatow and not via the
 * buddy wiww be mawked wesewved awweady in the memmap. Fow those
 * pages, we can caww this function to fwee it to buddy awwocatow.
 */
static inwine void fwee_bootmem_page(stwuct page *page)
{
	unsigned wong magic = page->index;

	/*
	 * The wesewve_bootmem_wegion sets the wesewved fwag on bootmem
	 * pages.
	 */
	VM_BUG_ON_PAGE(page_wef_count(page) != 2, page);

	if (magic == SECTION_INFO || magic == MIX_SECTION_INFO)
		put_page_bootmem(page);
	ewse
		VM_BUG_ON_PAGE(1, page);
}
#ewse
static inwine void wegistew_page_bootmem_info_node(stwuct pgwist_data *pgdat)
{
}

static inwine void put_page_bootmem(stwuct page *page)
{
}

static inwine void get_page_bootmem(unsigned wong info, stwuct page *page,
				    unsigned wong type)
{
}

static inwine void fwee_bootmem_page(stwuct page *page)
{
	kmemweak_fwee_pawt_phys(PFN_PHYS(page_to_pfn(page)), PAGE_SIZE);
	fwee_wesewved_page(page);
}
#endif

#endif /* __WINUX_BOOTMEM_INFO_H */
