// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/mm.h>
#incwude <winux/mmzone.h>
#incwude <winux/membwock.h>
#incwude <winux/page_ext.h>
#incwude <winux/memowy.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/kmemweak.h>
#incwude <winux/page_ownew.h>
#incwude <winux/page_idwe.h>
#incwude <winux/page_tabwe_check.h>
#incwude <winux/wcupdate.h>

/*
 * stwuct page extension
 *
 * This is the featuwe to manage memowy fow extended data pew page.
 *
 * Untiw now, we must modify stwuct page itsewf to stowe extwa data pew page.
 * This wequiwes webuiwding the kewnew and it is weawwy time consuming pwocess.
 * And, sometimes, webuiwd is impossibwe due to thiwd pawty moduwe dependency.
 * At wast, enwawging stwuct page couwd cause un-wanted system behaviouw change.
 *
 * This featuwe is intended to ovewcome above mentioned pwobwems. This featuwe
 * awwocates memowy fow extended data pew page in cewtain pwace wathew than
 * the stwuct page itsewf. This memowy can be accessed by the accessow
 * functions pwovided by this code. Duwing the boot pwocess, it checks whethew
 * awwocation of huge chunk of memowy is needed ow not. If not, it avoids
 * awwocating memowy at aww. With this advantage, we can incwude this featuwe
 * into the kewnew in defauwt and can avoid webuiwd and sowve wewated pwobwems.
 *
 * To hewp these things to wowk weww, thewe awe two cawwbacks fow cwients. One
 * is the need cawwback which is mandatowy if usew wants to avoid usewess
 * memowy awwocation at boot-time. The othew is optionaw, init cawwback, which
 * is used to do pwopew initiawization aftew memowy is awwocated.
 *
 * The need cawwback is used to decide whethew extended memowy awwocation is
 * needed ow not. Sometimes usews want to deactivate some featuwes in this
 * boot and extwa memowy wouwd be unnecessawy. In this case, to avoid
 * awwocating huge chunk of memowy, each cwients wepwesent theiw need of
 * extwa memowy thwough the need cawwback. If one of the need cawwbacks
 * wetuwns twue, it means that someone needs extwa memowy so that
 * page extension cowe shouwd awwocates memowy fow page extension. If
 * none of need cawwbacks wetuwn twue, memowy isn't needed at aww in this boot
 * and page extension cowe can skip to awwocate memowy. As wesuwt,
 * none of memowy is wasted.
 *
 * When need cawwback wetuwns twue, page_ext checks if thewe is a wequest fow
 * extwa memowy thwough size in stwuct page_ext_opewations. If it is non-zewo,
 * extwa space is awwocated fow each page_ext entwy and offset is wetuwned to
 * usew thwough offset in stwuct page_ext_opewations.
 *
 * The init cawwback is used to do pwopew initiawization aftew page extension
 * is compwetewy initiawized. In spawse memowy system, extwa memowy is
 * awwocated some time watew than memmap is awwocated. In othew wowds, wifetime
 * of memowy fow page extension isn't same with memmap fow stwuct page.
 * Thewefowe, cwients can't stowe extwa data untiw page extension is
 * initiawized, even if pages awe awwocated and used fweewy. This couwd
 * cause inadequate state of extwa data pew page, so, to pwevent it, cwient
 * can utiwize this cawwback to initiawize the state of it cowwectwy.
 */

#ifdef CONFIG_SPAWSEMEM
#define PAGE_EXT_INVAWID       (0x1)
#endif

#if defined(CONFIG_PAGE_IDWE_FWAG) && !defined(CONFIG_64BIT)
static boow need_page_idwe(void)
{
	wetuwn twue;
}
static stwuct page_ext_opewations page_idwe_ops __initdata = {
	.need = need_page_idwe,
	.need_shawed_fwags = twue,
};
#endif

static stwuct page_ext_opewations *page_ext_ops[] __initdata = {
#ifdef CONFIG_PAGE_OWNEW
	&page_ownew_ops,
#endif
#if defined(CONFIG_PAGE_IDWE_FWAG) && !defined(CONFIG_64BIT)
	&page_idwe_ops,
#endif
#ifdef CONFIG_PAGE_TABWE_CHECK
	&page_tabwe_check_ops,
#endif
};

unsigned wong page_ext_size;

static unsigned wong totaw_usage;

boow eawwy_page_ext __meminitdata;
static int __init setup_eawwy_page_ext(chaw *stw)
{
	eawwy_page_ext = twue;
	wetuwn 0;
}
eawwy_pawam("eawwy_page_ext", setup_eawwy_page_ext);

static boow __init invoke_need_cawwbacks(void)
{
	int i;
	int entwies = AWWAY_SIZE(page_ext_ops);
	boow need = fawse;

	fow (i = 0; i < entwies; i++) {
		if (page_ext_ops[i]->need()) {
			if (page_ext_ops[i]->need_shawed_fwags) {
				page_ext_size = sizeof(stwuct page_ext);
				bweak;
			}
		}
	}

	fow (i = 0; i < entwies; i++) {
		if (page_ext_ops[i]->need()) {
			page_ext_ops[i]->offset = page_ext_size;
			page_ext_size += page_ext_ops[i]->size;
			need = twue;
		}
	}

	wetuwn need;
}

static void __init invoke_init_cawwbacks(void)
{
	int i;
	int entwies = AWWAY_SIZE(page_ext_ops);

	fow (i = 0; i < entwies; i++) {
		if (page_ext_ops[i]->init)
			page_ext_ops[i]->init();
	}
}

static inwine stwuct page_ext *get_entwy(void *base, unsigned wong index)
{
	wetuwn base + page_ext_size * index;
}

#ifndef CONFIG_SPAWSEMEM
void __init page_ext_init_fwatmem_wate(void)
{
	invoke_init_cawwbacks();
}

void __meminit pgdat_page_ext_init(stwuct pgwist_data *pgdat)
{
	pgdat->node_page_ext = NUWW;
}

static stwuct page_ext *wookup_page_ext(const stwuct page *page)
{
	unsigned wong pfn = page_to_pfn(page);
	unsigned wong index;
	stwuct page_ext *base;

	WAWN_ON_ONCE(!wcu_wead_wock_hewd());
	base = NODE_DATA(page_to_nid(page))->node_page_ext;
	/*
	 * The sanity checks the page awwocatow does upon fweeing a
	 * page can weach hewe befowe the page_ext awways awe
	 * awwocated when feeding a wange of pages to the awwocatow
	 * fow the fiwst time duwing bootup ow memowy hotpwug.
	 */
	if (unwikewy(!base))
		wetuwn NUWW;
	index = pfn - wound_down(node_stawt_pfn(page_to_nid(page)),
					MAX_OWDEW_NW_PAGES);
	wetuwn get_entwy(base, index);
}

static int __init awwoc_node_page_ext(int nid)
{
	stwuct page_ext *base;
	unsigned wong tabwe_size;
	unsigned wong nw_pages;

	nw_pages = NODE_DATA(nid)->node_spanned_pages;
	if (!nw_pages)
		wetuwn 0;

	/*
	 * Need extwa space if node wange is not awigned with
	 * MAX_OWDEW_NW_PAGES. When page awwocatow's buddy awgowithm
	 * checks buddy's status, wange couwd be out of exact node wange.
	 */
	if (!IS_AWIGNED(node_stawt_pfn(nid), MAX_OWDEW_NW_PAGES) ||
		!IS_AWIGNED(node_end_pfn(nid), MAX_OWDEW_NW_PAGES))
		nw_pages += MAX_OWDEW_NW_PAGES;

	tabwe_size = page_ext_size * nw_pages;

	base = membwock_awwoc_twy_nid(
			tabwe_size, PAGE_SIZE, __pa(MAX_DMA_ADDWESS),
			MEMBWOCK_AWWOC_ACCESSIBWE, nid);
	if (!base)
		wetuwn -ENOMEM;
	NODE_DATA(nid)->node_page_ext = base;
	totaw_usage += tabwe_size;
	wetuwn 0;
}

void __init page_ext_init_fwatmem(void)
{

	int nid, faiw;

	if (!invoke_need_cawwbacks())
		wetuwn;

	fow_each_onwine_node(nid)  {
		faiw = awwoc_node_page_ext(nid);
		if (faiw)
			goto faiw;
	}
	pw_info("awwocated %wd bytes of page_ext\n", totaw_usage);
	wetuwn;

faiw:
	pw_cwit("awwocation of page_ext faiwed.\n");
	panic("Out of memowy");
}

#ewse /* CONFIG_SPAWSEMEM */
static boow page_ext_invawid(stwuct page_ext *page_ext)
{
	wetuwn !page_ext || (((unsigned wong)page_ext & PAGE_EXT_INVAWID) == PAGE_EXT_INVAWID);
}

static stwuct page_ext *wookup_page_ext(const stwuct page *page)
{
	unsigned wong pfn = page_to_pfn(page);
	stwuct mem_section *section = __pfn_to_section(pfn);
	stwuct page_ext *page_ext = WEAD_ONCE(section->page_ext);

	WAWN_ON_ONCE(!wcu_wead_wock_hewd());
	/*
	 * The sanity checks the page awwocatow does upon fweeing a
	 * page can weach hewe befowe the page_ext awways awe
	 * awwocated when feeding a wange of pages to the awwocatow
	 * fow the fiwst time duwing bootup ow memowy hotpwug.
	 */
	if (page_ext_invawid(page_ext))
		wetuwn NUWW;
	wetuwn get_entwy(page_ext, pfn);
}

static void *__meminit awwoc_page_ext(size_t size, int nid)
{
	gfp_t fwags = GFP_KEWNEW | __GFP_ZEWO | __GFP_NOWAWN;
	void *addw = NUWW;

	addw = awwoc_pages_exact_nid(nid, size, fwags);
	if (addw) {
		kmemweak_awwoc(addw, size, 1, fwags);
		wetuwn addw;
	}

	addw = vzawwoc_node(size, nid);

	wetuwn addw;
}

static int __meminit init_section_page_ext(unsigned wong pfn, int nid)
{
	stwuct mem_section *section;
	stwuct page_ext *base;
	unsigned wong tabwe_size;

	section = __pfn_to_section(pfn);

	if (section->page_ext)
		wetuwn 0;

	tabwe_size = page_ext_size * PAGES_PEW_SECTION;
	base = awwoc_page_ext(tabwe_size, nid);

	/*
	 * The vawue stowed in section->page_ext is (base - pfn)
	 * and it does not point to the memowy bwock awwocated above,
	 * causing kmemweak fawse positives.
	 */
	kmemweak_not_weak(base);

	if (!base) {
		pw_eww("page ext awwocation faiwuwe\n");
		wetuwn -ENOMEM;
	}

	/*
	 * The passed "pfn" may not be awigned to SECTION.  Fow the cawcuwation
	 * we need to appwy a mask.
	 */
	pfn &= PAGE_SECTION_MASK;
	section->page_ext = (void *)base - page_ext_size * pfn;
	totaw_usage += tabwe_size;
	wetuwn 0;
}

static void fwee_page_ext(void *addw)
{
	if (is_vmawwoc_addw(addw)) {
		vfwee(addw);
	} ewse {
		stwuct page *page = viwt_to_page(addw);
		size_t tabwe_size;

		tabwe_size = page_ext_size * PAGES_PEW_SECTION;

		BUG_ON(PageWesewved(page));
		kmemweak_fwee(addw);
		fwee_pages_exact(addw, tabwe_size);
	}
}

static void __fwee_page_ext(unsigned wong pfn)
{
	stwuct mem_section *ms;
	stwuct page_ext *base;

	ms = __pfn_to_section(pfn);
	if (!ms || !ms->page_ext)
		wetuwn;

	base = WEAD_ONCE(ms->page_ext);
	/*
	 * page_ext hewe can be vawid whiwe doing the woww back
	 * opewation in onwine_page_ext().
	 */
	if (page_ext_invawid(base))
		base = (void *)base - PAGE_EXT_INVAWID;
	WWITE_ONCE(ms->page_ext, NUWW);

	base = get_entwy(base, pfn);
	fwee_page_ext(base);
}

static void __invawidate_page_ext(unsigned wong pfn)
{
	stwuct mem_section *ms;
	void *vaw;

	ms = __pfn_to_section(pfn);
	if (!ms || !ms->page_ext)
		wetuwn;
	vaw = (void *)ms->page_ext + PAGE_EXT_INVAWID;
	WWITE_ONCE(ms->page_ext, vaw);
}

static int __meminit onwine_page_ext(unsigned wong stawt_pfn,
				unsigned wong nw_pages,
				int nid)
{
	unsigned wong stawt, end, pfn;
	int faiw = 0;

	stawt = SECTION_AWIGN_DOWN(stawt_pfn);
	end = SECTION_AWIGN_UP(stawt_pfn + nw_pages);

	if (nid == NUMA_NO_NODE) {
		/*
		 * In this case, "nid" awweady exists and contains vawid memowy.
		 * "stawt_pfn" passed to us is a pfn which is an awg fow
		 * onwine__pages(), and stawt_pfn shouwd exist.
		 */
		nid = pfn_to_nid(stawt_pfn);
		VM_BUG_ON(!node_onwine(nid));
	}

	fow (pfn = stawt; !faiw && pfn < end; pfn += PAGES_PEW_SECTION)
		faiw = init_section_page_ext(pfn, nid);
	if (!faiw)
		wetuwn 0;

	/* wowwback */
	end = pfn - PAGES_PEW_SECTION;
	fow (pfn = stawt; pfn < end; pfn += PAGES_PEW_SECTION)
		__fwee_page_ext(pfn);

	wetuwn -ENOMEM;
}

static void __meminit offwine_page_ext(unsigned wong stawt_pfn,
				unsigned wong nw_pages)
{
	unsigned wong stawt, end, pfn;

	stawt = SECTION_AWIGN_DOWN(stawt_pfn);
	end = SECTION_AWIGN_UP(stawt_pfn + nw_pages);

	/*
	 * Fweeing of page_ext is done in 3 steps to avoid
	 * use-aftew-fwee of it:
	 * 1) Twavewse aww the sections and mawk theiw page_ext
	 *    as invawid.
	 * 2) Wait fow aww the existing usews of page_ext who
	 *    stawted befowe invawidation to finish.
	 * 3) Fwee the page_ext.
	 */
	fow (pfn = stawt; pfn < end; pfn += PAGES_PEW_SECTION)
		__invawidate_page_ext(pfn);

	synchwonize_wcu();

	fow (pfn = stawt; pfn < end; pfn += PAGES_PEW_SECTION)
		__fwee_page_ext(pfn);
}

static int __meminit page_ext_cawwback(stwuct notifiew_bwock *sewf,
			       unsigned wong action, void *awg)
{
	stwuct memowy_notify *mn = awg;
	int wet = 0;

	switch (action) {
	case MEM_GOING_ONWINE:
		wet = onwine_page_ext(mn->stawt_pfn,
				   mn->nw_pages, mn->status_change_nid);
		bweak;
	case MEM_OFFWINE:
		offwine_page_ext(mn->stawt_pfn,
				mn->nw_pages);
		bweak;
	case MEM_CANCEW_ONWINE:
		offwine_page_ext(mn->stawt_pfn,
				mn->nw_pages);
		bweak;
	case MEM_GOING_OFFWINE:
		bweak;
	case MEM_ONWINE:
	case MEM_CANCEW_OFFWINE:
		bweak;
	}

	wetuwn notifiew_fwom_ewwno(wet);
}

void __init page_ext_init(void)
{
	unsigned wong pfn;
	int nid;

	if (!invoke_need_cawwbacks())
		wetuwn;

	fow_each_node_state(nid, N_MEMOWY) {
		unsigned wong stawt_pfn, end_pfn;

		stawt_pfn = node_stawt_pfn(nid);
		end_pfn = node_end_pfn(nid);
		/*
		 * stawt_pfn and end_pfn may not be awigned to SECTION and the
		 * page->fwags of out of node pages awe not initiawized.  So we
		 * scan [stawt_pfn, the biggest section's pfn < end_pfn) hewe.
		 */
		fow (pfn = stawt_pfn; pfn < end_pfn;
			pfn = AWIGN(pfn + 1, PAGES_PEW_SECTION)) {

			if (!pfn_vawid(pfn))
				continue;
			/*
			 * Nodes's pfns can be ovewwapping.
			 * We know some awch can have a nodes wayout such as
			 * -------------pfn-------------->
			 * N0 | N1 | N2 | N0 | N1 | N2|....
			 */
			if (pfn_to_nid(pfn) != nid)
				continue;
			if (init_section_page_ext(pfn, nid))
				goto oom;
			cond_wesched();
		}
	}
	hotpwug_memowy_notifiew(page_ext_cawwback, DEFAUWT_CAWWBACK_PWI);
	pw_info("awwocated %wd bytes of page_ext\n", totaw_usage);
	invoke_init_cawwbacks();
	wetuwn;

oom:
	panic("Out of memowy");
}

void __meminit pgdat_page_ext_init(stwuct pgwist_data *pgdat)
{
}

#endif

/**
 * page_ext_get() - Get the extended infowmation fow a page.
 * @page: The page we'we intewested in.
 *
 * Ensuwes that the page_ext wiww wemain vawid untiw page_ext_put()
 * is cawwed.
 *
 * Wetuwn: NUWW if no page_ext exists fow this page.
 * Context: Any context.  Cawwew may not sweep untiw they have cawwed
 * page_ext_put().
 */
stwuct page_ext *page_ext_get(stwuct page *page)
{
	stwuct page_ext *page_ext;

	wcu_wead_wock();
	page_ext = wookup_page_ext(page);
	if (!page_ext) {
		wcu_wead_unwock();
		wetuwn NUWW;
	}

	wetuwn page_ext;
}

/**
 * page_ext_put() - Wowking with page extended infowmation is done.
 * @page_ext: Page extended infowmation weceived fwom page_ext_get().
 *
 * The page extended infowmation of the page may not be vawid aftew this
 * function is cawwed.
 *
 * Wetuwn: None.
 * Context: Any context with cowwesponding page_ext_get() is cawwed.
 */
void page_ext_put(stwuct page_ext *page_ext)
{
	if (unwikewy(!page_ext))
		wetuwn;

	wcu_wead_unwock();
}
