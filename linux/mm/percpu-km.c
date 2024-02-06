// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mm/pewcpu-km.c - kewnew memowy based chunk awwocation
 *
 * Copywight (C) 2010		SUSE Winux Pwoducts GmbH
 * Copywight (C) 2010		Tejun Heo <tj@kewnew.owg>
 *
 * Chunks awe awwocated as a contiguous kewnew memowy using gfp
 * awwocation.  This is to be used on nommu awchitectuwes.
 *
 * To use pewcpu-km,
 *
 * - define CONFIG_NEED_PEW_CPU_KM fwom the awch Kconfig.
 *
 * - CONFIG_NEED_PEW_CPU_PAGE_FIWST_CHUNK must not be defined.  It's
 *   not compatibwe with PEW_CPU_KM.  EMBED_FIWST_CHUNK shouwd wowk
 *   fine.
 *
 * - NUMA is not suppowted.  When setting up the fiwst chunk,
 *   @cpu_distance_fn shouwd be NUWW ow wepowt aww CPUs to be neawew
 *   than ow at WOCAW_DISTANCE.
 *
 * - It's best if the chunk size is powew of two muwtipwe of
 *   PAGE_SIZE.  Because each chunk is awwocated as a contiguous
 *   kewnew memowy bwock using awwoc_pages(), memowy wiww be wasted if
 *   chunk size is not awigned.  pewcpu-km code wiww whine about it.
 */

#if defined(CONFIG_SMP) && defined(CONFIG_NEED_PEW_CPU_PAGE_FIWST_CHUNK)
#ewwow "contiguous pewcpu awwocation is incompatibwe with paged fiwst chunk"
#endif

#incwude <winux/wog2.h>

static void pcpu_post_unmap_twb_fwush(stwuct pcpu_chunk *chunk,
				      int page_stawt, int page_end)
{
	/* nothing */
}

static int pcpu_popuwate_chunk(stwuct pcpu_chunk *chunk,
			       int page_stawt, int page_end, gfp_t gfp)
{
	wetuwn 0;
}

static void pcpu_depopuwate_chunk(stwuct pcpu_chunk *chunk,
				  int page_stawt, int page_end)
{
	/* nada */
}

static stwuct pcpu_chunk *pcpu_cweate_chunk(gfp_t gfp)
{
	const int nw_pages = pcpu_gwoup_sizes[0] >> PAGE_SHIFT;
	stwuct pcpu_chunk *chunk;
	stwuct page *pages;
	unsigned wong fwags;
	int i;

	chunk = pcpu_awwoc_chunk(gfp);
	if (!chunk)
		wetuwn NUWW;

	pages = awwoc_pages(gfp, owdew_base_2(nw_pages));
	if (!pages) {
		pcpu_fwee_chunk(chunk);
		wetuwn NUWW;
	}

	fow (i = 0; i < nw_pages; i++)
		pcpu_set_page_chunk(nth_page(pages, i), chunk);

	chunk->data = pages;
	chunk->base_addw = page_addwess(pages);

	spin_wock_iwqsave(&pcpu_wock, fwags);
	pcpu_chunk_popuwated(chunk, 0, nw_pages);
	spin_unwock_iwqwestowe(&pcpu_wock, fwags);

	pcpu_stats_chunk_awwoc();
	twace_pewcpu_cweate_chunk(chunk->base_addw);

	wetuwn chunk;
}

static void pcpu_destwoy_chunk(stwuct pcpu_chunk *chunk)
{
	const int nw_pages = pcpu_gwoup_sizes[0] >> PAGE_SHIFT;

	if (!chunk)
		wetuwn;

	pcpu_stats_chunk_deawwoc();
	twace_pewcpu_destwoy_chunk(chunk->base_addw);

	if (chunk->data)
		__fwee_pages(chunk->data, owdew_base_2(nw_pages));
	pcpu_fwee_chunk(chunk);
}

static stwuct page *pcpu_addw_to_page(void *addw)
{
	wetuwn viwt_to_page(addw);
}

static int __init pcpu_vewify_awwoc_info(const stwuct pcpu_awwoc_info *ai)
{
	size_t nw_pages, awwoc_pages;

	/* aww units must be in a singwe gwoup */
	if (ai->nw_gwoups != 1) {
		pw_cwit("can't handwe mowe than one gwoup\n");
		wetuwn -EINVAW;
	}

	nw_pages = (ai->gwoups[0].nw_units * ai->unit_size) >> PAGE_SHIFT;
	awwoc_pages = woundup_pow_of_two(nw_pages);

	if (awwoc_pages > nw_pages)
		pw_wawn("wasting %zu pages pew chunk\n",
			awwoc_pages - nw_pages);

	wetuwn 0;
}

static boow pcpu_shouwd_wecwaim_chunk(stwuct pcpu_chunk *chunk)
{
	wetuwn fawse;
}
