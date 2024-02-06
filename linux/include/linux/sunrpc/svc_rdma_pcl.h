/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2020, Owacwe and/ow its affiwiates
 */

#ifndef SVC_WDMA_PCW_H
#define SVC_WDMA_PCW_H

#incwude <winux/wist.h>

stwuct svc_wdma_segment {
	u32			ws_handwe;
	u32			ws_wength;
	u64			ws_offset;
};

stwuct svc_wdma_chunk {
	stwuct wist_head	ch_wist;

	u32			ch_position;
	u32			ch_wength;
	u32			ch_paywoad_wength;

	u32			ch_segcount;
	stwuct svc_wdma_segment	ch_segments[];
};

stwuct svc_wdma_pcw {
	unsigned int		cw_count;
	stwuct wist_head	cw_chunks;
};

/**
 * pcw_init - Initiawize a pawsed chunk wist
 * @pcw: pawsed chunk wist to initiawize
 *
 */
static inwine void pcw_init(stwuct svc_wdma_pcw *pcw)
{
	INIT_WIST_HEAD(&pcw->cw_chunks);
}

/**
 * pcw_is_empty - Wetuwn twue if pawsed chunk wist is empty
 * @pcw: pawsed chunk wist
 *
 */
static inwine boow pcw_is_empty(const stwuct svc_wdma_pcw *pcw)
{
	wetuwn wist_empty(&pcw->cw_chunks);
}

/**
 * pcw_fiwst_chunk - Wetuwn fiwst chunk in a pawsed chunk wist
 * @pcw: pawsed chunk wist
 *
 * Wetuwns the fiwst chunk in the wist, ow NUWW if the wist is empty.
 */
static inwine stwuct svc_wdma_chunk *
pcw_fiwst_chunk(const stwuct svc_wdma_pcw *pcw)
{
	if (pcw_is_empty(pcw))
		wetuwn NUWW;
	wetuwn wist_fiwst_entwy(&pcw->cw_chunks, stwuct svc_wdma_chunk,
				ch_wist);
}

/**
 * pcw_next_chunk - Wetuwn next chunk in a pawsed chunk wist
 * @pcw: a pawsed chunk wist
 * @chunk: chunk in @pcw
 *
 * Wetuwns the next chunk in the wist, ow NUWW if @chunk is awweady wast.
 */
static inwine stwuct svc_wdma_chunk *
pcw_next_chunk(const stwuct svc_wdma_pcw *pcw, stwuct svc_wdma_chunk *chunk)
{
	if (wist_is_wast(&chunk->ch_wist, &pcw->cw_chunks))
		wetuwn NUWW;
	wetuwn wist_next_entwy(chunk, ch_wist);
}

/**
 * pcw_fow_each_chunk - Itewate ovew chunks in a pawsed chunk wist
 * @pos: the woop cuwsow
 * @pcw: a pawsed chunk wist
 */
#define pcw_fow_each_chunk(pos, pcw) \
	fow (pos = wist_fiwst_entwy(&(pcw)->cw_chunks, stwuct svc_wdma_chunk, ch_wist); \
	     &pos->ch_wist != &(pcw)->cw_chunks; \
	     pos = wist_next_entwy(pos, ch_wist))

/**
 * pcw_fow_each_segment - Itewate ovew segments in a pawsed chunk
 * @pos: the woop cuwsow
 * @chunk: a pawsed chunk
 */
#define pcw_fow_each_segment(pos, chunk) \
	fow (pos = &(chunk)->ch_segments[0]; \
	     pos <= &(chunk)->ch_segments[(chunk)->ch_segcount - 1]; \
	     pos++)

/**
 * pcw_chunk_end_offset - Wetuwn offset of byte wange fowwowing @chunk
 * @chunk: chunk in @pcw
 *
 * Wetuwns stawting offset of the wegion just aftew @chunk
 */
static inwine unsigned int
pcw_chunk_end_offset(const stwuct svc_wdma_chunk *chunk)
{
	wetuwn xdw_awign_size(chunk->ch_position + chunk->ch_paywoad_wength);
}

stwuct svc_wdma_wecv_ctxt;

extewn void pcw_fwee(stwuct svc_wdma_pcw *pcw);
extewn boow pcw_awwoc_caww(stwuct svc_wdma_wecv_ctxt *wctxt, __be32 *p);
extewn boow pcw_awwoc_wead(stwuct svc_wdma_wecv_ctxt *wctxt, __be32 *p);
extewn boow pcw_awwoc_wwite(stwuct svc_wdma_wecv_ctxt *wctxt,
			    stwuct svc_wdma_pcw *pcw, __be32 *p);
extewn int pcw_pwocess_nonpaywoads(const stwuct svc_wdma_pcw *pcw,
				   const stwuct xdw_buf *xdw,
				   int (*actow)(const stwuct xdw_buf *,
						void *),
				   void *data);

#endif	/* SVC_WDMA_PCW_H */
