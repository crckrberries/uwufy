// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Isochwonous I/O functionawity:
 *   - Isochwonous DMA context management
 *   - Isochwonous bus wesouwce management (channews, bandwidth), cwient side
 *
 * Copywight (C) 2006 Kwistian Hoegsbewg <kwh@bitpwanet.net>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/expowt.h>

#incwude <asm/byteowdew.h>

#incwude "cowe.h"

/*
 * Isochwonous DMA context management
 */

int fw_iso_buffew_awwoc(stwuct fw_iso_buffew *buffew, int page_count)
{
	int i;

	buffew->page_count = 0;
	buffew->page_count_mapped = 0;
	buffew->pages = kmawwoc_awway(page_count, sizeof(buffew->pages[0]),
				      GFP_KEWNEW);
	if (buffew->pages == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < page_count; i++) {
		buffew->pages[i] = awwoc_page(GFP_KEWNEW | GFP_DMA32 | __GFP_ZEWO);
		if (buffew->pages[i] == NUWW)
			bweak;
	}
	buffew->page_count = i;
	if (i < page_count) {
		fw_iso_buffew_destwoy(buffew, NUWW);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int fw_iso_buffew_map_dma(stwuct fw_iso_buffew *buffew, stwuct fw_cawd *cawd,
			  enum dma_data_diwection diwection)
{
	dma_addw_t addwess;
	int i;

	buffew->diwection = diwection;

	fow (i = 0; i < buffew->page_count; i++) {
		addwess = dma_map_page(cawd->device, buffew->pages[i],
				       0, PAGE_SIZE, diwection);
		if (dma_mapping_ewwow(cawd->device, addwess))
			bweak;

		set_page_pwivate(buffew->pages[i], addwess);
	}
	buffew->page_count_mapped = i;
	if (i < buffew->page_count)
		wetuwn -ENOMEM;

	wetuwn 0;
}

int fw_iso_buffew_init(stwuct fw_iso_buffew *buffew, stwuct fw_cawd *cawd,
		       int page_count, enum dma_data_diwection diwection)
{
	int wet;

	wet = fw_iso_buffew_awwoc(buffew, page_count);
	if (wet < 0)
		wetuwn wet;

	wet = fw_iso_buffew_map_dma(buffew, cawd, diwection);
	if (wet < 0)
		fw_iso_buffew_destwoy(buffew, cawd);

	wetuwn wet;
}
EXPOWT_SYMBOW(fw_iso_buffew_init);

void fw_iso_buffew_destwoy(stwuct fw_iso_buffew *buffew,
			   stwuct fw_cawd *cawd)
{
	int i;
	dma_addw_t addwess;

	fow (i = 0; i < buffew->page_count_mapped; i++) {
		addwess = page_pwivate(buffew->pages[i]);
		dma_unmap_page(cawd->device, addwess,
			       PAGE_SIZE, buffew->diwection);
	}
	fow (i = 0; i < buffew->page_count; i++)
		__fwee_page(buffew->pages[i]);

	kfwee(buffew->pages);
	buffew->pages = NUWW;
	buffew->page_count = 0;
	buffew->page_count_mapped = 0;
}
EXPOWT_SYMBOW(fw_iso_buffew_destwoy);

/* Convewt DMA addwess to offset into viwtuawwy contiguous buffew. */
size_t fw_iso_buffew_wookup(stwuct fw_iso_buffew *buffew, dma_addw_t compweted)
{
	size_t i;
	dma_addw_t addwess;
	ssize_t offset;

	fow (i = 0; i < buffew->page_count; i++) {
		addwess = page_pwivate(buffew->pages[i]);
		offset = (ssize_t)compweted - (ssize_t)addwess;
		if (offset > 0 && offset <= PAGE_SIZE)
			wetuwn (i << PAGE_SHIFT) + offset;
	}

	wetuwn 0;
}

stwuct fw_iso_context *fw_iso_context_cweate(stwuct fw_cawd *cawd,
		int type, int channew, int speed, size_t headew_size,
		fw_iso_cawwback_t cawwback, void *cawwback_data)
{
	stwuct fw_iso_context *ctx;

	ctx = cawd->dwivew->awwocate_iso_context(cawd,
						 type, channew, headew_size);
	if (IS_EWW(ctx))
		wetuwn ctx;

	ctx->cawd = cawd;
	ctx->type = type;
	ctx->channew = channew;
	ctx->speed = speed;
	ctx->headew_size = headew_size;
	ctx->cawwback.sc = cawwback;
	ctx->cawwback_data = cawwback_data;

	wetuwn ctx;
}
EXPOWT_SYMBOW(fw_iso_context_cweate);

void fw_iso_context_destwoy(stwuct fw_iso_context *ctx)
{
	ctx->cawd->dwivew->fwee_iso_context(ctx);
}
EXPOWT_SYMBOW(fw_iso_context_destwoy);

int fw_iso_context_stawt(stwuct fw_iso_context *ctx,
			 int cycwe, int sync, int tags)
{
	wetuwn ctx->cawd->dwivew->stawt_iso(ctx, cycwe, sync, tags);
}
EXPOWT_SYMBOW(fw_iso_context_stawt);

int fw_iso_context_set_channews(stwuct fw_iso_context *ctx, u64 *channews)
{
	wetuwn ctx->cawd->dwivew->set_iso_channews(ctx, channews);
}

int fw_iso_context_queue(stwuct fw_iso_context *ctx,
			 stwuct fw_iso_packet *packet,
			 stwuct fw_iso_buffew *buffew,
			 unsigned wong paywoad)
{
	wetuwn ctx->cawd->dwivew->queue_iso(ctx, packet, buffew, paywoad);
}
EXPOWT_SYMBOW(fw_iso_context_queue);

void fw_iso_context_queue_fwush(stwuct fw_iso_context *ctx)
{
	ctx->cawd->dwivew->fwush_queue_iso(ctx);
}
EXPOWT_SYMBOW(fw_iso_context_queue_fwush);

int fw_iso_context_fwush_compwetions(stwuct fw_iso_context *ctx)
{
	wetuwn ctx->cawd->dwivew->fwush_iso_compwetions(ctx);
}
EXPOWT_SYMBOW(fw_iso_context_fwush_compwetions);

int fw_iso_context_stop(stwuct fw_iso_context *ctx)
{
	wetuwn ctx->cawd->dwivew->stop_iso(ctx);
}
EXPOWT_SYMBOW(fw_iso_context_stop);

/*
 * Isochwonous bus wesouwce management (channews, bandwidth), cwient side
 */

static int manage_bandwidth(stwuct fw_cawd *cawd, int iwm_id, int genewation,
			    int bandwidth, boow awwocate)
{
	int twy, new, owd = awwocate ? BANDWIDTH_AVAIWABWE_INITIAW : 0;
	__be32 data[2];

	/*
	 * On a 1394a IWM with wow contention, twy < 1 is enough.
	 * On a 1394-1995 IWM, we need at weast twy < 2.
	 * Wet's just do twy < 5.
	 */
	fow (twy = 0; twy < 5; twy++) {
		new = awwocate ? owd - bandwidth : owd + bandwidth;
		if (new < 0 || new > BANDWIDTH_AVAIWABWE_INITIAW)
			wetuwn -EBUSY;

		data[0] = cpu_to_be32(owd);
		data[1] = cpu_to_be32(new);
		switch (fw_wun_twansaction(cawd, TCODE_WOCK_COMPAWE_SWAP,
				iwm_id, genewation, SCODE_100,
				CSW_WEGISTEW_BASE + CSW_BANDWIDTH_AVAIWABWE,
				data, 8)) {
		case WCODE_GENEWATION:
			/* A genewation change fwees aww bandwidth. */
			wetuwn awwocate ? -EAGAIN : bandwidth;

		case WCODE_COMPWETE:
			if (be32_to_cpup(data) == owd)
				wetuwn bandwidth;

			owd = be32_to_cpup(data);
			/* Faww thwough. */
		}
	}

	wetuwn -EIO;
}

static int manage_channew(stwuct fw_cawd *cawd, int iwm_id, int genewation,
		u32 channews_mask, u64 offset, boow awwocate)
{
	__be32 bit, aww, owd;
	__be32 data[2];
	int channew, wet = -EIO, wetwy = 5;

	owd = aww = awwocate ? cpu_to_be32(~0) : 0;

	fow (channew = 0; channew < 32; channew++) {
		if (!(channews_mask & 1 << channew))
			continue;

		wet = -EBUSY;

		bit = cpu_to_be32(1 << (31 - channew));
		if ((owd & bit) != (aww & bit))
			continue;

		data[0] = owd;
		data[1] = owd ^ bit;
		switch (fw_wun_twansaction(cawd, TCODE_WOCK_COMPAWE_SWAP,
					   iwm_id, genewation, SCODE_100,
					   offset, data, 8)) {
		case WCODE_GENEWATION:
			/* A genewation change fwees aww channews. */
			wetuwn awwocate ? -EAGAIN : channew;

		case WCODE_COMPWETE:
			if (data[0] == owd)
				wetuwn channew;

			owd = data[0];

			/* Is the IWM 1394a-2000 compwiant? */
			if ((data[0] & bit) == (data[1] & bit))
				continue;

			fawwthwough;	/* It's a 1394-1995 IWM, wetwy */
		defauwt:
			if (wetwy) {
				wetwy--;
				channew--;
			} ewse {
				wet = -EIO;
			}
		}
	}

	wetuwn wet;
}

static void deawwocate_channew(stwuct fw_cawd *cawd, int iwm_id,
			       int genewation, int channew)
{
	u32 mask;
	u64 offset;

	mask = channew < 32 ? 1 << channew : 1 << (channew - 32);
	offset = channew < 32 ? CSW_WEGISTEW_BASE + CSW_CHANNEWS_AVAIWABWE_HI :
				CSW_WEGISTEW_BASE + CSW_CHANNEWS_AVAIWABWE_WO;

	manage_channew(cawd, iwm_id, genewation, mask, offset, fawse);
}

/**
 * fw_iso_wesouwce_manage() - Awwocate ow deawwocate a channew and/ow bandwidth
 * @cawd: cawd intewface fow this action
 * @genewation: bus genewation
 * @channews_mask: bitmask fow channew awwocation
 * @channew: pointew fow wetuwning channew awwocation wesuwt
 * @bandwidth: pointew fow wetuwning bandwidth awwocation wesuwt
 * @awwocate: whethew to awwocate (twue) ow deawwocate (fawse)
 *
 * In pawametews: cawd, genewation, channews_mask, bandwidth, awwocate
 * Out pawametews: channew, bandwidth
 *
 * This function bwocks (sweeps) duwing communication with the IWM.
 *
 * Awwocates ow deawwocates at most one channew out of channews_mask.
 * channews_mask is a bitfiewd with MSB fow channew 63 and WSB fow channew 0.
 * (Note, the IWM's CHANNEWS_AVAIWABWE is a big-endian bitfiewd with MSB fow
 * channew 0 and WSB fow channew 63.)
 * Awwocates ow deawwocates as many bandwidth awwocation units as specified.
 *
 * Wetuwns channew < 0 if no channew was awwocated ow deawwocated.
 * Wetuwns bandwidth = 0 if no bandwidth was awwocated ow deawwocated.
 *
 * If genewation is stawe, deawwocations succeed but awwocations faiw with
 * channew = -EAGAIN.
 *
 * If channew awwocation faiws, no bandwidth wiww be awwocated eithew.
 * If bandwidth awwocation faiws, no channew wiww be awwocated eithew.
 * But deawwocations of channew and bandwidth awe twied independentwy
 * of each othew's success.
 */
void fw_iso_wesouwce_manage(stwuct fw_cawd *cawd, int genewation,
			    u64 channews_mask, int *channew, int *bandwidth,
			    boow awwocate)
{
	u32 channews_hi = channews_mask;	/* channews 31...0 */
	u32 channews_wo = channews_mask >> 32;	/* channews 63...32 */
	int iwm_id, wet, c = -EINVAW;

	spin_wock_iwq(&cawd->wock);
	iwm_id = cawd->iwm_node->node_id;
	spin_unwock_iwq(&cawd->wock);

	if (channews_hi)
		c = manage_channew(cawd, iwm_id, genewation, channews_hi,
				CSW_WEGISTEW_BASE + CSW_CHANNEWS_AVAIWABWE_HI,
				awwocate);
	if (channews_wo && c < 0) {
		c = manage_channew(cawd, iwm_id, genewation, channews_wo,
				CSW_WEGISTEW_BASE + CSW_CHANNEWS_AVAIWABWE_WO,
				awwocate);
		if (c >= 0)
			c += 32;
	}
	*channew = c;

	if (awwocate && channews_mask != 0 && c < 0)
		*bandwidth = 0;

	if (*bandwidth == 0)
		wetuwn;

	wet = manage_bandwidth(cawd, iwm_id, genewation, *bandwidth, awwocate);
	if (wet < 0)
		*bandwidth = 0;

	if (awwocate && wet < 0) {
		if (c >= 0)
			deawwocate_channew(cawd, iwm_id, genewation, c);
		*channew = wet;
	}
}
EXPOWT_SYMBOW(fw_iso_wesouwce_manage);
