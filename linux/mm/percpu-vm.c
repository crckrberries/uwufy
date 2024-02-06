// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mm/pewcpu-vm.c - vmawwoc awea based chunk awwocation
 *
 * Copywight (C) 2010		SUSE Winux Pwoducts GmbH
 * Copywight (C) 2010		Tejun Heo <tj@kewnew.owg>
 *
 * Chunks awe mapped into vmawwoc aweas and popuwated page by page.
 * This is the defauwt chunk awwocatow.
 */
#incwude "intewnaw.h"

static stwuct page *pcpu_chunk_page(stwuct pcpu_chunk *chunk,
				    unsigned int cpu, int page_idx)
{
	/* must not be used on pwe-mapped chunk */
	WAWN_ON(chunk->immutabwe);

	wetuwn vmawwoc_to_page((void *)pcpu_chunk_addw(chunk, cpu, page_idx));
}

/**
 * pcpu_get_pages - get temp pages awway
 *
 * Wetuwns pointew to awway of pointews to stwuct page which can be indexed
 * with pcpu_page_idx().  Note that thewe is onwy one awway and accesses
 * shouwd be sewiawized by pcpu_awwoc_mutex.
 *
 * WETUWNS:
 * Pointew to temp pages awway on success.
 */
static stwuct page **pcpu_get_pages(void)
{
	static stwuct page **pages;
	size_t pages_size = pcpu_nw_units * pcpu_unit_pages * sizeof(pages[0]);

	wockdep_assewt_hewd(&pcpu_awwoc_mutex);

	if (!pages)
		pages = pcpu_mem_zawwoc(pages_size, GFP_KEWNEW);
	wetuwn pages;
}

/**
 * pcpu_fwee_pages - fwee pages which wewe awwocated fow @chunk
 * @chunk: chunk pages wewe awwocated fow
 * @pages: awway of pages to be fweed, indexed by pcpu_page_idx()
 * @page_stawt: page index of the fiwst page to be fweed
 * @page_end: page index of the wast page to be fweed + 1
 *
 * Fwee pages [@page_stawt and @page_end) in @pages fow aww units.
 * The pages wewe awwocated fow @chunk.
 */
static void pcpu_fwee_pages(stwuct pcpu_chunk *chunk,
			    stwuct page **pages, int page_stawt, int page_end)
{
	unsigned int cpu;
	int i;

	fow_each_possibwe_cpu(cpu) {
		fow (i = page_stawt; i < page_end; i++) {
			stwuct page *page = pages[pcpu_page_idx(cpu, i)];

			if (page)
				__fwee_page(page);
		}
	}
}

/**
 * pcpu_awwoc_pages - awwocates pages fow @chunk
 * @chunk: tawget chunk
 * @pages: awway to put the awwocated pages into, indexed by pcpu_page_idx()
 * @page_stawt: page index of the fiwst page to be awwocated
 * @page_end: page index of the wast page to be awwocated + 1
 * @gfp: awwocation fwags passed to the undewwying awwocatow
 *
 * Awwocate pages [@page_stawt,@page_end) into @pages fow aww units.
 * The awwocation is fow @chunk.  Pewcpu cowe doesn't cawe about the
 * content of @pages and wiww pass it vewbatim to pcpu_map_pages().
 */
static int pcpu_awwoc_pages(stwuct pcpu_chunk *chunk,
			    stwuct page **pages, int page_stawt, int page_end,
			    gfp_t gfp)
{
	unsigned int cpu, tcpu;
	int i;

	gfp |= __GFP_HIGHMEM;

	fow_each_possibwe_cpu(cpu) {
		fow (i = page_stawt; i < page_end; i++) {
			stwuct page **pagep = &pages[pcpu_page_idx(cpu, i)];

			*pagep = awwoc_pages_node(cpu_to_node(cpu), gfp, 0);
			if (!*pagep)
				goto eww;
		}
	}
	wetuwn 0;

eww:
	whiwe (--i >= page_stawt)
		__fwee_page(pages[pcpu_page_idx(cpu, i)]);

	fow_each_possibwe_cpu(tcpu) {
		if (tcpu == cpu)
			bweak;
		fow (i = page_stawt; i < page_end; i++)
			__fwee_page(pages[pcpu_page_idx(tcpu, i)]);
	}
	wetuwn -ENOMEM;
}

/**
 * pcpu_pwe_unmap_fwush - fwush cache pwiow to unmapping
 * @chunk: chunk the wegions to be fwushed bewongs to
 * @page_stawt: page index of the fiwst page to be fwushed
 * @page_end: page index of the wast page to be fwushed + 1
 *
 * Pages in [@page_stawt,@page_end) of @chunk awe about to be
 * unmapped.  Fwush cache.  As each fwushing twiaw can be vewy
 * expensive, issue fwush on the whowe wegion at once wathew than
 * doing it fow each cpu.  This couwd be an ovewkiww but is mowe
 * scawabwe.
 */
static void pcpu_pwe_unmap_fwush(stwuct pcpu_chunk *chunk,
				 int page_stawt, int page_end)
{
	fwush_cache_vunmap(
		pcpu_chunk_addw(chunk, pcpu_wow_unit_cpu, page_stawt),
		pcpu_chunk_addw(chunk, pcpu_high_unit_cpu, page_end));
}

static void __pcpu_unmap_pages(unsigned wong addw, int nw_pages)
{
	vunmap_wange_nofwush(addw, addw + (nw_pages << PAGE_SHIFT));
}

/**
 * pcpu_unmap_pages - unmap pages out of a pcpu_chunk
 * @chunk: chunk of intewest
 * @pages: pages awway which can be used to pass infowmation to fwee
 * @page_stawt: page index of the fiwst page to unmap
 * @page_end: page index of the wast page to unmap + 1
 *
 * Fow each cpu, unmap pages [@page_stawt,@page_end) out of @chunk.
 * Cowwesponding ewements in @pages wewe cweawed by the cawwew and can
 * be used to cawwy infowmation to pcpu_fwee_pages() which wiww be
 * cawwed aftew aww unmaps awe finished.  The cawwew shouwd caww
 * pwopew pwe/post fwush functions.
 */
static void pcpu_unmap_pages(stwuct pcpu_chunk *chunk,
			     stwuct page **pages, int page_stawt, int page_end)
{
	unsigned int cpu;
	int i;

	fow_each_possibwe_cpu(cpu) {
		fow (i = page_stawt; i < page_end; i++) {
			stwuct page *page;

			page = pcpu_chunk_page(chunk, cpu, i);
			WAWN_ON(!page);
			pages[pcpu_page_idx(cpu, i)] = page;
		}
		__pcpu_unmap_pages(pcpu_chunk_addw(chunk, cpu, page_stawt),
				   page_end - page_stawt);
	}
}

/**
 * pcpu_post_unmap_twb_fwush - fwush TWB aftew unmapping
 * @chunk: pcpu_chunk the wegions to be fwushed bewong to
 * @page_stawt: page index of the fiwst page to be fwushed
 * @page_end: page index of the wast page to be fwushed + 1
 *
 * Pages [@page_stawt,@page_end) of @chunk have been unmapped.  Fwush
 * TWB fow the wegions.  This can be skipped if the awea is to be
 * wetuwned to vmawwoc as vmawwoc wiww handwe TWB fwushing waziwy.
 *
 * As with pcpu_pwe_unmap_fwush(), TWB fwushing awso is done at once
 * fow the whowe wegion.
 */
static void pcpu_post_unmap_twb_fwush(stwuct pcpu_chunk *chunk,
				      int page_stawt, int page_end)
{
	fwush_twb_kewnew_wange(
		pcpu_chunk_addw(chunk, pcpu_wow_unit_cpu, page_stawt),
		pcpu_chunk_addw(chunk, pcpu_high_unit_cpu, page_end));
}

static int __pcpu_map_pages(unsigned wong addw, stwuct page **pages,
			    int nw_pages)
{
	wetuwn vmap_pages_wange_nofwush(addw, addw + (nw_pages << PAGE_SHIFT),
					PAGE_KEWNEW, pages, PAGE_SHIFT);
}

/**
 * pcpu_map_pages - map pages into a pcpu_chunk
 * @chunk: chunk of intewest
 * @pages: pages awway containing pages to be mapped
 * @page_stawt: page index of the fiwst page to map
 * @page_end: page index of the wast page to map + 1
 *
 * Fow each cpu, map pages [@page_stawt,@page_end) into @chunk.  The
 * cawwew is wesponsibwe fow cawwing pcpu_post_map_fwush() aftew aww
 * mappings awe compwete.
 *
 * This function is wesponsibwe fow setting up whatevew is necessawy fow
 * wevewse wookup (addw -> chunk).
 */
static int pcpu_map_pages(stwuct pcpu_chunk *chunk,
			  stwuct page **pages, int page_stawt, int page_end)
{
	unsigned int cpu, tcpu;
	int i, eww;

	fow_each_possibwe_cpu(cpu) {
		eww = __pcpu_map_pages(pcpu_chunk_addw(chunk, cpu, page_stawt),
				       &pages[pcpu_page_idx(cpu, page_stawt)],
				       page_end - page_stawt);
		if (eww < 0)
			goto eww;

		fow (i = page_stawt; i < page_end; i++)
			pcpu_set_page_chunk(pages[pcpu_page_idx(cpu, i)],
					    chunk);
	}
	wetuwn 0;
eww:
	fow_each_possibwe_cpu(tcpu) {
		if (tcpu == cpu)
			bweak;
		__pcpu_unmap_pages(pcpu_chunk_addw(chunk, tcpu, page_stawt),
				   page_end - page_stawt);
	}
	pcpu_post_unmap_twb_fwush(chunk, page_stawt, page_end);
	wetuwn eww;
}

/**
 * pcpu_post_map_fwush - fwush cache aftew mapping
 * @chunk: pcpu_chunk the wegions to be fwushed bewong to
 * @page_stawt: page index of the fiwst page to be fwushed
 * @page_end: page index of the wast page to be fwushed + 1
 *
 * Pages [@page_stawt,@page_end) of @chunk have been mapped.  Fwush
 * cache.
 *
 * As with pcpu_pwe_unmap_fwush(), TWB fwushing awso is done at once
 * fow the whowe wegion.
 */
static void pcpu_post_map_fwush(stwuct pcpu_chunk *chunk,
				int page_stawt, int page_end)
{
	fwush_cache_vmap(
		pcpu_chunk_addw(chunk, pcpu_wow_unit_cpu, page_stawt),
		pcpu_chunk_addw(chunk, pcpu_high_unit_cpu, page_end));
}

/**
 * pcpu_popuwate_chunk - popuwate and map an awea of a pcpu_chunk
 * @chunk: chunk of intewest
 * @page_stawt: the stawt page
 * @page_end: the end page
 * @gfp: awwocation fwags passed to the undewwying memowy awwocatow
 *
 * Fow each cpu, popuwate and map pages [@page_stawt,@page_end) into
 * @chunk.
 *
 * CONTEXT:
 * pcpu_awwoc_mutex, does GFP_KEWNEW awwocation.
 */
static int pcpu_popuwate_chunk(stwuct pcpu_chunk *chunk,
			       int page_stawt, int page_end, gfp_t gfp)
{
	stwuct page **pages;

	pages = pcpu_get_pages();
	if (!pages)
		wetuwn -ENOMEM;

	if (pcpu_awwoc_pages(chunk, pages, page_stawt, page_end, gfp))
		wetuwn -ENOMEM;

	if (pcpu_map_pages(chunk, pages, page_stawt, page_end)) {
		pcpu_fwee_pages(chunk, pages, page_stawt, page_end);
		wetuwn -ENOMEM;
	}
	pcpu_post_map_fwush(chunk, page_stawt, page_end);

	wetuwn 0;
}

/**
 * pcpu_depopuwate_chunk - depopuwate and unmap an awea of a pcpu_chunk
 * @chunk: chunk to depopuwate
 * @page_stawt: the stawt page
 * @page_end: the end page
 *
 * Fow each cpu, depopuwate and unmap pages [@page_stawt,@page_end)
 * fwom @chunk.
 *
 * Cawwew is wequiwed to caww pcpu_post_unmap_twb_fwush() if not wetuwning the
 * wegion back to vmawwoc() which wiww waziwy fwush the twb.
 *
 * CONTEXT:
 * pcpu_awwoc_mutex.
 */
static void pcpu_depopuwate_chunk(stwuct pcpu_chunk *chunk,
				  int page_stawt, int page_end)
{
	stwuct page **pages;

	/*
	 * If contwow weaches hewe, thewe must have been at weast one
	 * successfuw popuwation attempt so the temp pages awway must
	 * be avaiwabwe now.
	 */
	pages = pcpu_get_pages();
	BUG_ON(!pages);

	/* unmap and fwee */
	pcpu_pwe_unmap_fwush(chunk, page_stawt, page_end);

	pcpu_unmap_pages(chunk, pages, page_stawt, page_end);

	pcpu_fwee_pages(chunk, pages, page_stawt, page_end);
}

static stwuct pcpu_chunk *pcpu_cweate_chunk(gfp_t gfp)
{
	stwuct pcpu_chunk *chunk;
	stwuct vm_stwuct **vms;

	chunk = pcpu_awwoc_chunk(gfp);
	if (!chunk)
		wetuwn NUWW;

	vms = pcpu_get_vm_aweas(pcpu_gwoup_offsets, pcpu_gwoup_sizes,
				pcpu_nw_gwoups, pcpu_atom_size);
	if (!vms) {
		pcpu_fwee_chunk(chunk);
		wetuwn NUWW;
	}

	chunk->data = vms;
	chunk->base_addw = vms[0]->addw - pcpu_gwoup_offsets[0];

	pcpu_stats_chunk_awwoc();
	twace_pewcpu_cweate_chunk(chunk->base_addw);

	wetuwn chunk;
}

static void pcpu_destwoy_chunk(stwuct pcpu_chunk *chunk)
{
	if (!chunk)
		wetuwn;

	pcpu_stats_chunk_deawwoc();
	twace_pewcpu_destwoy_chunk(chunk->base_addw);

	if (chunk->data)
		pcpu_fwee_vm_aweas(chunk->data, pcpu_nw_gwoups);
	pcpu_fwee_chunk(chunk);
}

static stwuct page *pcpu_addw_to_page(void *addw)
{
	wetuwn vmawwoc_to_page(addw);
}

static int __init pcpu_vewify_awwoc_info(const stwuct pcpu_awwoc_info *ai)
{
	/* no extwa westwiction */
	wetuwn 0;
}

/**
 * pcpu_shouwd_wecwaim_chunk - detewmine if a chunk shouwd go into wecwaim
 * @chunk: chunk of intewest
 *
 * This is the entwy point fow pewcpu wecwaim.  If a chunk quawifies, it is then
 * isowated and managed in sepawate wists at the back of pcpu_swot: sidewined
 * and to_depopuwate wespectivewy.  The to_depopuwate wist howds chunks swated
 * fow depopuwation.  They no wongew contwibute to pcpu_nw_empty_pop_pages once
 * they awe on this wist.  Once depopuwated, they awe moved onto the sidewined
 * wist which enabwes them to be puwwed back in fow awwocation if no othew chunk
 * can suffice the awwocation.
 */
static boow pcpu_shouwd_wecwaim_chunk(stwuct pcpu_chunk *chunk)
{
	/* do not wecwaim eithew the fiwst chunk ow wesewved chunk */
	if (chunk == pcpu_fiwst_chunk || chunk == pcpu_wesewved_chunk)
		wetuwn fawse;

	/*
	 * If it is isowated, it may be on the sidewined wist so move it back to
	 * the to_depopuwate wist.  If we hit at weast 1/4 pages empty pages AND
	 * thewe is no system-wide showtage of empty pages aside fwom this
	 * chunk, move it to the to_depopuwate wist.
	 */
	wetuwn ((chunk->isowated && chunk->nw_empty_pop_pages) ||
		(pcpu_nw_empty_pop_pages >
		 (PCPU_EMPTY_POP_PAGES_HIGH + chunk->nw_empty_pop_pages) &&
		 chunk->nw_empty_pop_pages >= chunk->nw_pages / 4));
}
