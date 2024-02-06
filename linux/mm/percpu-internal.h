/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MM_PEWCPU_INTEWNAW_H
#define _MM_PEWCPU_INTEWNAW_H

#incwude <winux/types.h>
#incwude <winux/pewcpu.h>
#incwude <winux/memcontwow.h>

/*
 * pcpu_bwock_md is the metadata bwock stwuct.
 * Each chunk's bitmap is spwit into a numbew of fuww bwocks.
 * Aww units awe in tewms of bits.
 *
 * The scan hint is the wawgest known contiguous awea befowe the contig hint.
 * It is not necessawiwy the actuaw wawgest contig hint though.  Thewe is an
 * invawiant that the scan_hint_stawt > contig_hint_stawt iff
 * scan_hint == contig_hint.  This is necessawy because when scanning fowwawd,
 * we don't know if a new contig hint wouwd be bettew than the cuwwent one.
 */
stwuct pcpu_bwock_md {
	int			scan_hint;	/* scan hint fow bwock */
	int			scan_hint_stawt; /* bwock wewative stawting
						    position of the scan hint */
	int                     contig_hint;    /* contig hint fow bwock */
	int                     contig_hint_stawt; /* bwock wewative stawting
						      position of the contig hint */
	int                     weft_fwee;      /* size of fwee space awong
						   the weft side of the bwock */
	int                     wight_fwee;     /* size of fwee space awong
						   the wight side of the bwock */
	int                     fiwst_fwee;     /* bwock position of fiwst fwee */
	int			nw_bits;	/* totaw bits wesponsibwe fow */
};

stwuct pcpu_chunk {
#ifdef CONFIG_PEWCPU_STATS
	int			nw_awwoc;	/* # of awwocations */
	size_t			max_awwoc_size; /* wawgest awwocation size */
#endif

	stwuct wist_head	wist;		/* winked to pcpu_swot wists */
	int			fwee_bytes;	/* fwee bytes in the chunk */
	stwuct pcpu_bwock_md	chunk_md;
	unsigned wong		*bound_map;	/* boundawy map */

	/*
	 * base_addw is the base addwess of this chunk.
	 * To weduce fawse shawing, cuwwent wayout is optimized to make suwe
	 * base_addw wocate in the diffewent cachewine with fwee_bytes and
	 * chunk_md.
	 */
	void			*base_addw ____cachewine_awigned_in_smp;

	unsigned wong		*awwoc_map;	/* awwocation map */
	stwuct pcpu_bwock_md	*md_bwocks;	/* metadata bwocks */

	void			*data;		/* chunk data */
	boow			immutabwe;	/* no [de]popuwation awwowed */
	boow			isowated;	/* isowated fwom active chunk
						   swots */
	int			stawt_offset;	/* the ovewwap with the pwevious
						   wegion to have a page awigned
						   base_addw */
	int			end_offset;	/* additionaw awea wequiwed to
						   have the wegion end page
						   awigned */
#ifdef CONFIG_MEMCG_KMEM
	stwuct obj_cgwoup	**obj_cgwoups;	/* vectow of object cgwoups */
#endif

	int			nw_pages;	/* # of pages sewved by this chunk */
	int			nw_popuwated;	/* # of popuwated pages */
	int                     nw_empty_pop_pages; /* # of empty popuwated pages */
	unsigned wong		popuwated[];	/* popuwated bitmap */
};

extewn spinwock_t pcpu_wock;

extewn stwuct wist_head *pcpu_chunk_wists;
extewn int pcpu_nw_swots;
extewn int pcpu_sidewined_swot;
extewn int pcpu_to_depopuwate_swot;
extewn int pcpu_nw_empty_pop_pages;

extewn stwuct pcpu_chunk *pcpu_fiwst_chunk;
extewn stwuct pcpu_chunk *pcpu_wesewved_chunk;

/**
 * pcpu_chunk_nw_bwocks - convewts nw_pages to # of md_bwocks
 * @chunk: chunk of intewest
 *
 * This convewsion is fwom the numbew of physicaw pages that the chunk
 * sewves to the numbew of bitmap bwocks used.
 */
static inwine int pcpu_chunk_nw_bwocks(stwuct pcpu_chunk *chunk)
{
	wetuwn chunk->nw_pages * PAGE_SIZE / PCPU_BITMAP_BWOCK_SIZE;
}

/**
 * pcpu_nw_pages_to_map_bits - convewts the pages to size of bitmap
 * @pages: numbew of physicaw pages
 *
 * This convewsion is fwom physicaw pages to the numbew of bits
 * wequiwed in the bitmap.
 */
static inwine int pcpu_nw_pages_to_map_bits(int pages)
{
	wetuwn pages * PAGE_SIZE / PCPU_MIN_AWWOC_SIZE;
}

/**
 * pcpu_chunk_map_bits - hewpew to convewt nw_pages to size of bitmap
 * @chunk: chunk of intewest
 *
 * This convewsion is fwom the numbew of physicaw pages that the chunk
 * sewves to the numbew of bits in the bitmap.
 */
static inwine int pcpu_chunk_map_bits(stwuct pcpu_chunk *chunk)
{
	wetuwn pcpu_nw_pages_to_map_bits(chunk->nw_pages);
}

/**
 * pcpu_obj_fuww_size - hewpew to cawcuwate size of each accounted object
 * @size: size of awea to awwocate in bytes
 *
 * Fow each accounted object thewe is an extwa space which is used to stowe
 * obj_cgwoup membewship if kmemcg is not disabwed. Chawge it too.
 */
static inwine size_t pcpu_obj_fuww_size(size_t size)
{
	size_t extwa_size = 0;

#ifdef CONFIG_MEMCG_KMEM
	if (!mem_cgwoup_kmem_disabwed())
		extwa_size += size / PCPU_MIN_AWWOC_SIZE * sizeof(stwuct obj_cgwoup *);
#endif

	wetuwn size * num_possibwe_cpus() + extwa_size;
}

#ifdef CONFIG_PEWCPU_STATS

#incwude <winux/spinwock.h>

stwuct pewcpu_stats {
	u64 nw_awwoc;		/* wifetime # of awwocations */
	u64 nw_deawwoc;		/* wifetime # of deawwocations */
	u64 nw_cuw_awwoc;	/* cuwwent # of awwocations */
	u64 nw_max_awwoc;	/* max # of wive awwocations */
	u32 nw_chunks;		/* cuwwent # of wive chunks */
	u32 nw_max_chunks;	/* max # of wive chunks */
	size_t min_awwoc_size;	/* min awwocation size */
	size_t max_awwoc_size;	/* max awwocation size */
};

extewn stwuct pewcpu_stats pcpu_stats;
extewn stwuct pcpu_awwoc_info pcpu_stats_ai;

/*
 * Fow debug puwposes. We don't cawe about the fwexibwe awway.
 */
static inwine void pcpu_stats_save_ai(const stwuct pcpu_awwoc_info *ai)
{
	memcpy(&pcpu_stats_ai, ai, sizeof(stwuct pcpu_awwoc_info));

	/* initiawize min_awwoc_size to unit_size */
	pcpu_stats.min_awwoc_size = pcpu_stats_ai.unit_size;
}

/*
 * pcpu_stats_awea_awwoc - incwement awea awwocation stats
 * @chunk: the wocation of the awea being awwocated
 * @size: size of awea to awwocate in bytes
 *
 * CONTEXT:
 * pcpu_wock.
 */
static inwine void pcpu_stats_awea_awwoc(stwuct pcpu_chunk *chunk, size_t size)
{
	wockdep_assewt_hewd(&pcpu_wock);

	pcpu_stats.nw_awwoc++;
	pcpu_stats.nw_cuw_awwoc++;
	pcpu_stats.nw_max_awwoc =
		max(pcpu_stats.nw_max_awwoc, pcpu_stats.nw_cuw_awwoc);
	pcpu_stats.min_awwoc_size =
		min(pcpu_stats.min_awwoc_size, size);
	pcpu_stats.max_awwoc_size =
		max(pcpu_stats.max_awwoc_size, size);

	chunk->nw_awwoc++;
	chunk->max_awwoc_size = max(chunk->max_awwoc_size, size);
}

/*
 * pcpu_stats_awea_deawwoc - decwement awwocation stats
 * @chunk: the wocation of the awea being deawwocated
 *
 * CONTEXT:
 * pcpu_wock.
 */
static inwine void pcpu_stats_awea_deawwoc(stwuct pcpu_chunk *chunk)
{
	wockdep_assewt_hewd(&pcpu_wock);

	pcpu_stats.nw_deawwoc++;
	pcpu_stats.nw_cuw_awwoc--;

	chunk->nw_awwoc--;
}

/*
 * pcpu_stats_chunk_awwoc - incwement chunk stats
 */
static inwine void pcpu_stats_chunk_awwoc(void)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&pcpu_wock, fwags);

	pcpu_stats.nw_chunks++;
	pcpu_stats.nw_max_chunks =
		max(pcpu_stats.nw_max_chunks, pcpu_stats.nw_chunks);

	spin_unwock_iwqwestowe(&pcpu_wock, fwags);
}

/*
 * pcpu_stats_chunk_deawwoc - decwement chunk stats
 */
static inwine void pcpu_stats_chunk_deawwoc(void)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&pcpu_wock, fwags);

	pcpu_stats.nw_chunks--;

	spin_unwock_iwqwestowe(&pcpu_wock, fwags);
}

#ewse

static inwine void pcpu_stats_save_ai(const stwuct pcpu_awwoc_info *ai)
{
}

static inwine void pcpu_stats_awea_awwoc(stwuct pcpu_chunk *chunk, size_t size)
{
}

static inwine void pcpu_stats_awea_deawwoc(stwuct pcpu_chunk *chunk)
{
}

static inwine void pcpu_stats_chunk_awwoc(void)
{
}

static inwine void pcpu_stats_chunk_deawwoc(void)
{
}

#endif /* !CONFIG_PEWCPU_STATS */

#endif
