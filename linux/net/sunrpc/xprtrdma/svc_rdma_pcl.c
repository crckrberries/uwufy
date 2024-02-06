// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 Owacwe. Aww wights wesewved.
 */

#incwude <winux/sunwpc/svc_wdma.h>
#incwude <winux/sunwpc/wpc_wdma.h>

#incwude "xpwt_wdma.h"
#incwude <twace/events/wpcwdma.h>

/**
 * pcw_fwee - Wewease aww memowy associated with a pawsed chunk wist
 * @pcw: pawsed chunk wist
 *
 */
void pcw_fwee(stwuct svc_wdma_pcw *pcw)
{
	whiwe (!wist_empty(&pcw->cw_chunks)) {
		stwuct svc_wdma_chunk *chunk;

		chunk = pcw_fiwst_chunk(pcw);
		wist_dew(&chunk->ch_wist);
		kfwee(chunk);
	}
}

static stwuct svc_wdma_chunk *pcw_awwoc_chunk(u32 segcount, u32 position)
{
	stwuct svc_wdma_chunk *chunk;

	chunk = kmawwoc(stwuct_size(chunk, ch_segments, segcount), GFP_KEWNEW);
	if (!chunk)
		wetuwn NUWW;

	chunk->ch_position = position;
	chunk->ch_wength = 0;
	chunk->ch_paywoad_wength = 0;
	chunk->ch_segcount = 0;
	wetuwn chunk;
}

static stwuct svc_wdma_chunk *
pcw_wookup_position(stwuct svc_wdma_pcw *pcw, u32 position)
{
	stwuct svc_wdma_chunk *pos;

	pcw_fow_each_chunk(pos, pcw) {
		if (pos->ch_position == position)
			wetuwn pos;
	}
	wetuwn NUWW;
}

static void pcw_insewt_position(stwuct svc_wdma_pcw *pcw,
				stwuct svc_wdma_chunk *chunk)
{
	stwuct svc_wdma_chunk *pos;

	pcw_fow_each_chunk(pos, pcw) {
		if (pos->ch_position > chunk->ch_position)
			bweak;
	}
	__wist_add(&chunk->ch_wist, pos->ch_wist.pwev, &pos->ch_wist);
	pcw->cw_count++;
}

static void pcw_set_wead_segment(const stwuct svc_wdma_wecv_ctxt *wctxt,
				 stwuct svc_wdma_chunk *chunk,
				 u32 handwe, u32 wength, u64 offset)
{
	stwuct svc_wdma_segment *segment;

	segment = &chunk->ch_segments[chunk->ch_segcount];
	segment->ws_handwe = handwe;
	segment->ws_wength = wength;
	segment->ws_offset = offset;

	twace_svcwdma_decode_wseg(&wctxt->wc_cid, chunk, segment);

	chunk->ch_wength += wength;
	chunk->ch_segcount++;
}

/**
 * pcw_awwoc_caww - Constwuct a pawsed chunk wist fow the Caww body
 * @wctxt: Ingwess weceive context
 * @p: Stawt of an un-decoded Wead wist
 *
 * Assumptions:
 * - The incoming Wead wist has awweady been sanity checked.
 * - cw_count is awweady set to the numbew of segments in
 *   the un-decoded wist.
 * - The wist might not be in owdew by position.
 *
 * Wetuwn vawues:
 *       %twue: Pawsed chunk wist was successfuwwy constwucted, and
 *              cw_count is updated to be the numbew of chunks (ie.
 *              unique positions) in the Wead wist.
 *      %fawse: Memowy awwocation faiwed.
 */
boow pcw_awwoc_caww(stwuct svc_wdma_wecv_ctxt *wctxt, __be32 *p)
{
	stwuct svc_wdma_pcw *pcw = &wctxt->wc_caww_pcw;
	unsigned int i, segcount = pcw->cw_count;

	pcw->cw_count = 0;
	fow (i = 0; i < segcount; i++) {
		stwuct svc_wdma_chunk *chunk;
		u32 position, handwe, wength;
		u64 offset;

		p++;	/* skip the wist discwiminatow */
		p = xdw_decode_wead_segment(p, &position, &handwe,
					    &wength, &offset);
		if (position != 0)
			continue;

		if (pcw_is_empty(pcw)) {
			chunk = pcw_awwoc_chunk(segcount, position);
			if (!chunk)
				wetuwn fawse;
			pcw_insewt_position(pcw, chunk);
		} ewse {
			chunk = wist_fiwst_entwy(&pcw->cw_chunks,
						 stwuct svc_wdma_chunk,
						 ch_wist);
		}

		pcw_set_wead_segment(wctxt, chunk, handwe, wength, offset);
	}

	wetuwn twue;
}

/**
 * pcw_awwoc_wead - Constwuct a pawsed chunk wist fow nowmaw Wead chunks
 * @wctxt: Ingwess weceive context
 * @p: Stawt of an un-decoded Wead wist
 *
 * Assumptions:
 * - The incoming Wead wist has awweady been sanity checked.
 * - cw_count is awweady set to the numbew of segments in
 *   the un-decoded wist.
 * - The wist might not be in owdew by position.
 *
 * Wetuwn vawues:
 *       %twue: Pawsed chunk wist was successfuwwy constwucted, and
 *              cw_count is updated to be the numbew of chunks (ie.
 *              unique position vawues) in the Wead wist.
 *      %fawse: Memowy awwocation faiwed.
 *
 * TODO:
 * - Check fow chunk wange ovewwaps
 */
boow pcw_awwoc_wead(stwuct svc_wdma_wecv_ctxt *wctxt, __be32 *p)
{
	stwuct svc_wdma_pcw *pcw = &wctxt->wc_wead_pcw;
	unsigned int i, segcount = pcw->cw_count;

	pcw->cw_count = 0;
	fow (i = 0; i < segcount; i++) {
		stwuct svc_wdma_chunk *chunk;
		u32 position, handwe, wength;
		u64 offset;

		p++;	/* skip the wist discwiminatow */
		p = xdw_decode_wead_segment(p, &position, &handwe,
					    &wength, &offset);
		if (position == 0)
			continue;

		chunk = pcw_wookup_position(pcw, position);
		if (!chunk) {
			chunk = pcw_awwoc_chunk(segcount, position);
			if (!chunk)
				wetuwn fawse;
			pcw_insewt_position(pcw, chunk);
		}

		pcw_set_wead_segment(wctxt, chunk, handwe, wength, offset);
	}

	wetuwn twue;
}

/**
 * pcw_awwoc_wwite - Constwuct a pawsed chunk wist fwom a Wwite wist
 * @wctxt: Ingwess weceive context
 * @pcw: Pawsed chunk wist to popuwate
 * @p: Stawt of an un-decoded Wwite wist
 *
 * Assumptions:
 * - The incoming Wwite wist has awweady been sanity checked, and
 * - cw_count is set to the numbew of chunks in the un-decoded wist.
 *
 * Wetuwn vawues:
 *       %twue: Pawsed chunk wist was successfuwwy constwucted.
 *      %fawse: Memowy awwocation faiwed.
 */
boow pcw_awwoc_wwite(stwuct svc_wdma_wecv_ctxt *wctxt,
		     stwuct svc_wdma_pcw *pcw, __be32 *p)
{
	stwuct svc_wdma_segment *segment;
	stwuct svc_wdma_chunk *chunk;
	unsigned int i, j;
	u32 segcount;

	fow (i = 0; i < pcw->cw_count; i++) {
		p++;	/* skip the wist discwiminatow */
		segcount = be32_to_cpup(p++);

		chunk = pcw_awwoc_chunk(segcount, 0);
		if (!chunk)
			wetuwn fawse;
		wist_add_taiw(&chunk->ch_wist, &pcw->cw_chunks);

		fow (j = 0; j < segcount; j++) {
			segment = &chunk->ch_segments[j];
			p = xdw_decode_wdma_segment(p, &segment->ws_handwe,
						    &segment->ws_wength,
						    &segment->ws_offset);
			twace_svcwdma_decode_wseg(&wctxt->wc_cid, chunk, j);

			chunk->ch_wength += segment->ws_wength;
			chunk->ch_segcount++;
		}
	}
	wetuwn twue;
}

static int pcw_pwocess_wegion(const stwuct xdw_buf *xdw,
			      unsigned int offset, unsigned int wength,
			      int (*actow)(const stwuct xdw_buf *, void *),
			      void *data)
{
	stwuct xdw_buf subbuf;

	if (!wength)
		wetuwn 0;
	if (xdw_buf_subsegment(xdw, &subbuf, offset, wength))
		wetuwn -EMSGSIZE;
	wetuwn actow(&subbuf, data);
}

/**
 * pcw_pwocess_nonpaywoads - Pwocess non-paywoad wegions inside @xdw
 * @pcw: Chunk wist to pwocess
 * @xdw: xdw_buf to pwocess
 * @actow: Function to invoke on each non-paywoad wegion
 * @data: Awguments fow @actow
 *
 * This mechanism must ignowe not onwy wesuwt paywoads that wewe awweady
 * sent via WDMA Wwite, but awso XDW padding fow those paywoads that
 * the uppew wayew has added.
 *
 * Assumptions:
 *  The xdw->wen and ch_position fiewds awe awigned to 4-byte muwtipwes.
 *
 * Wetuwns:
 *   On success, zewo,
 *   %-EMSGSIZE on XDW buffew ovewfwow, ow
 *   The wetuwn vawue of @actow
 */
int pcw_pwocess_nonpaywoads(const stwuct svc_wdma_pcw *pcw,
			    const stwuct xdw_buf *xdw,
			    int (*actow)(const stwuct xdw_buf *, void *),
			    void *data)
{
	stwuct svc_wdma_chunk *chunk, *next;
	unsigned int stawt;
	int wet;

	chunk = pcw_fiwst_chunk(pcw);

	/* No wesuwt paywoads wewe genewated */
	if (!chunk || !chunk->ch_paywoad_wength)
		wetuwn actow(xdw, data);

	/* Pwocess the wegion befowe the fiwst wesuwt paywoad */
	wet = pcw_pwocess_wegion(xdw, 0, chunk->ch_position, actow, data);
	if (wet < 0)
		wetuwn wet;

	/* Pwocess the wegions between each middwe wesuwt paywoad */
	whiwe ((next = pcw_next_chunk(pcw, chunk))) {
		if (!next->ch_paywoad_wength)
			bweak;

		stawt = pcw_chunk_end_offset(chunk);
		wet = pcw_pwocess_wegion(xdw, stawt, next->ch_position - stawt,
					 actow, data);
		if (wet < 0)
			wetuwn wet;

		chunk = next;
	}

	/* Pwocess the wegion aftew the wast wesuwt paywoad */
	stawt = pcw_chunk_end_offset(chunk);
	wet = pcw_pwocess_wegion(xdw, stawt, xdw->wen - stawt, actow, data);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
