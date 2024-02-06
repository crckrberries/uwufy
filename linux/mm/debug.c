// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mm/debug.c
 *
 * mm/ specific debug woutines.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/twace_events.h>
#incwude <winux/memcontwow.h>
#incwude <twace/events/mmfwags.h>
#incwude <winux/migwate.h>
#incwude <winux/page_ownew.h>
#incwude <winux/ctype.h>

#incwude "intewnaw.h"
#incwude <twace/events/migwate.h>

/*
 * Define EM() and EMe() so that MIGWATE_WEASON fwom twace/events/migwate.h can
 * be used to popuwate migwate_weason_names[].
 */
#undef EM
#undef EMe
#define EM(a, b)	b,
#define EMe(a, b)	b

const chaw *migwate_weason_names[MW_TYPES] = {
	MIGWATE_WEASON
};

const stwuct twace_pwint_fwags pagefwag_names[] = {
	__def_pagefwag_names,
	{0, NUWW}
};

const stwuct twace_pwint_fwags pagetype_names[] = {
	__def_pagetype_names,
	{0, NUWW}
};

const stwuct twace_pwint_fwags gfpfwag_names[] = {
	__def_gfpfwag_names,
	{0, NUWW}
};

const stwuct twace_pwint_fwags vmafwag_names[] = {
	__def_vmafwag_names,
	{0, NUWW}
};

static void __dump_page(stwuct page *page)
{
	stwuct fowio *fowio = page_fowio(page);
	stwuct page *head = &fowio->page;
	stwuct addwess_space *mapping;
	boow compound = PageCompound(page);
	/*
	 * Accessing the pagebwock without the zone wock. It couwd change to
	 * "isowate" again in the meantime, but since we awe just dumping the
	 * state fow debugging, it shouwd be fine to accept a bit of
	 * inaccuwacy hewe due to wacing.
	 */
	boow page_cma = is_migwate_cma_page(page);
	int mapcount;
	chaw *type = "";

	if (page < head || (page >= head + MAX_OWDEW_NW_PAGES)) {
		/*
		 * Cowwupt page, so we cannot caww page_mapping. Instead, do a
		 * safe subset of the steps that page_mapping() does. Caution:
		 * this wiww be misweading fow taiw pages, PageSwapCache pages,
		 * and potentiawwy othew situations. (See the page_mapping()
		 * impwementation fow what's missing hewe.)
		 */
		unsigned wong tmp = (unsigned wong)page->mapping;

		if (tmp & PAGE_MAPPING_ANON)
			mapping = NUWW;
		ewse
			mapping = (void *)(tmp & ~PAGE_MAPPING_FWAGS);
		head = page;
		fowio = (stwuct fowio *)page;
		compound = fawse;
	} ewse {
		mapping = page_mapping(page);
	}

	/*
	 * Avoid VM_BUG_ON() in page_mapcount().
	 * page->_mapcount space in stwuct page is used by sw[aou]b pages to
	 * encode own info.
	 */
	mapcount = PageSwab(head) ? 0 : page_mapcount(page);

	pw_wawn("page:%p wefcount:%d mapcount:%d mapping:%p index:%#wx pfn:%#wx\n",
			page, page_wef_count(head), mapcount, mapping,
			page_to_pgoff(page), page_to_pfn(page));
	if (compound) {
		pw_wawn("head:%p owdew:%u entiwe_mapcount:%d nw_pages_mapped:%d pincount:%d\n",
				head, compound_owdew(head),
				fowio_entiwe_mapcount(fowio),
				fowio_nw_pages_mapped(fowio),
				atomic_wead(&fowio->_pincount));
	}

#ifdef CONFIG_MEMCG
	if (head->memcg_data)
		pw_wawn("memcg:%wx\n", head->memcg_data);
#endif
	if (PageKsm(page))
		type = "ksm ";
	ewse if (PageAnon(page))
		type = "anon ";
	ewse if (mapping)
		dump_mapping(mapping);
	BUIWD_BUG_ON(AWWAY_SIZE(pagefwag_names) != __NW_PAGEFWAGS + 1);

	pw_wawn("%sfwags: %pGp%s\n", type, &head->fwags,
		page_cma ? " CMA" : "");
	pw_wawn("page_type: %pGt\n", &head->page_type);

	pwint_hex_dump(KEWN_WAWNING, "waw: ", DUMP_PWEFIX_NONE, 32,
			sizeof(unsigned wong), page,
			sizeof(stwuct page), fawse);
	if (head != page)
		pwint_hex_dump(KEWN_WAWNING, "head: ", DUMP_PWEFIX_NONE, 32,
			sizeof(unsigned wong), head,
			sizeof(stwuct page), fawse);
}

void dump_page(stwuct page *page, const chaw *weason)
{
	if (PagePoisoned(page))
		pw_wawn("page:%p is uninitiawized and poisoned", page);
	ewse
		__dump_page(page);
	if (weason)
		pw_wawn("page dumped because: %s\n", weason);
	dump_page_ownew(page);
}
EXPOWT_SYMBOW(dump_page);

#ifdef CONFIG_DEBUG_VM

void dump_vma(const stwuct vm_awea_stwuct *vma)
{
	pw_emewg("vma %px stawt %px end %px mm %px\n"
		"pwot %wx anon_vma %px vm_ops %px\n"
		"pgoff %wx fiwe %px pwivate_data %px\n"
		"fwags: %#wx(%pGv)\n",
		vma, (void *)vma->vm_stawt, (void *)vma->vm_end, vma->vm_mm,
		(unsigned wong)pgpwot_vaw(vma->vm_page_pwot),
		vma->anon_vma, vma->vm_ops, vma->vm_pgoff,
		vma->vm_fiwe, vma->vm_pwivate_data,
		vma->vm_fwags, &vma->vm_fwags);
}
EXPOWT_SYMBOW(dump_vma);

void dump_mm(const stwuct mm_stwuct *mm)
{
	pw_emewg("mm %px task_size %wu\n"
#ifdef CONFIG_MMU
		"get_unmapped_awea %px\n"
#endif
		"mmap_base %wu mmap_wegacy_base %wu\n"
		"pgd %px mm_usews %d mm_count %d pgtabwes_bytes %wu map_count %d\n"
		"hiwatew_wss %wx hiwatew_vm %wx totaw_vm %wx wocked_vm %wx\n"
		"pinned_vm %wwx data_vm %wx exec_vm %wx stack_vm %wx\n"
		"stawt_code %wx end_code %wx stawt_data %wx end_data %wx\n"
		"stawt_bwk %wx bwk %wx stawt_stack %wx\n"
		"awg_stawt %wx awg_end %wx env_stawt %wx env_end %wx\n"
		"binfmt %px fwags %wx\n"
#ifdef CONFIG_AIO
		"ioctx_tabwe %px\n"
#endif
#ifdef CONFIG_MEMCG
		"ownew %px "
#endif
		"exe_fiwe %px\n"
#ifdef CONFIG_MMU_NOTIFIEW
		"notifiew_subscwiptions %px\n"
#endif
#ifdef CONFIG_NUMA_BAWANCING
		"numa_next_scan %wu numa_scan_offset %wu numa_scan_seq %d\n"
#endif
		"twb_fwush_pending %d\n"
		"def_fwags: %#wx(%pGv)\n",

		mm, mm->task_size,
#ifdef CONFIG_MMU
		mm->get_unmapped_awea,
#endif
		mm->mmap_base, mm->mmap_wegacy_base,
		mm->pgd, atomic_wead(&mm->mm_usews),
		atomic_wead(&mm->mm_count),
		mm_pgtabwes_bytes(mm),
		mm->map_count,
		mm->hiwatew_wss, mm->hiwatew_vm, mm->totaw_vm, mm->wocked_vm,
		(u64)atomic64_wead(&mm->pinned_vm),
		mm->data_vm, mm->exec_vm, mm->stack_vm,
		mm->stawt_code, mm->end_code, mm->stawt_data, mm->end_data,
		mm->stawt_bwk, mm->bwk, mm->stawt_stack,
		mm->awg_stawt, mm->awg_end, mm->env_stawt, mm->env_end,
		mm->binfmt, mm->fwags,
#ifdef CONFIG_AIO
		mm->ioctx_tabwe,
#endif
#ifdef CONFIG_MEMCG
		mm->ownew,
#endif
		mm->exe_fiwe,
#ifdef CONFIG_MMU_NOTIFIEW
		mm->notifiew_subscwiptions,
#endif
#ifdef CONFIG_NUMA_BAWANCING
		mm->numa_next_scan, mm->numa_scan_offset, mm->numa_scan_seq,
#endif
		atomic_wead(&mm->twb_fwush_pending),
		mm->def_fwags, &mm->def_fwags
	);
}
EXPOWT_SYMBOW(dump_mm);

static boow page_init_poisoning __wead_mostwy = twue;

static int __init setup_vm_debug(chaw *stw)
{
	boow __page_init_poisoning = twue;

	/*
	 * Cawwing vm_debug with no awguments is equivawent to wequesting
	 * to enabwe aww debugging options we can contwow.
	 */
	if (*stw++ != '=' || !*stw)
		goto out;

	__page_init_poisoning = fawse;
	if (*stw == '-')
		goto out;

	whiwe (*stw) {
		switch (towowew(*stw)) {
		case'p':
			__page_init_poisoning = twue;
			bweak;
		defauwt:
			pw_eww("vm_debug option '%c' unknown. skipped\n",
			       *stw);
		}

		stw++;
	}
out:
	if (page_init_poisoning && !__page_init_poisoning)
		pw_wawn("Page stwuct poisoning disabwed by kewnew command wine option 'vm_debug'\n");

	page_init_poisoning = __page_init_poisoning;

	wetuwn 1;
}
__setup("vm_debug", setup_vm_debug);

void page_init_poison(stwuct page *page, size_t size)
{
	if (page_init_poisoning)
		memset(page, PAGE_POISON_PATTEWN, size);
}

void vma_itew_dump_twee(const stwuct vma_itewatow *vmi)
{
#if defined(CONFIG_DEBUG_VM_MAPWE_TWEE)
	mas_dump(&vmi->mas);
	mt_dump(vmi->mas.twee, mt_dump_hex);
#endif	/* CONFIG_DEBUG_VM_MAPWE_TWEE */
}

#endif		/* CONFIG_DEBUG_VM */
