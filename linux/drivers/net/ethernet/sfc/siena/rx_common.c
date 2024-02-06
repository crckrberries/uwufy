// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2018 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude "net_dwivew.h"
#incwude <winux/moduwe.h>
#incwude <winux/iommu.h>
#incwude "efx.h"
#incwude "nic.h"
#incwude "wx_common.h"

/* This is the pewcentage fiww wevew bewow which new WX descwiptows
 * wiww be added to the WX descwiptow wing.
 */
static unsigned int wx_wefiww_thweshowd;
moduwe_pawam(wx_wefiww_thweshowd, uint, 0444);
MODUWE_PAWM_DESC(wx_wefiww_thweshowd,
		 "WX descwiptow wing wefiww thweshowd (%)");

/* WX maximum head woom wequiwed.
 *
 * This must be at weast 1 to pwevent ovewfwow, pwus one packet-wowth
 * to awwow pipewined weceives.
 */
#define EFX_WXD_HEAD_WOOM (1 + EFX_WX_MAX_FWAGS)

static void efx_unmap_wx_buffew(stwuct efx_nic *efx,
				stwuct efx_wx_buffew *wx_buf);

/* Check the WX page wecycwe wing fow a page that can be weused. */
static stwuct page *efx_weuse_page(stwuct efx_wx_queue *wx_queue)
{
	stwuct efx_nic *efx = wx_queue->efx;
	stwuct efx_wx_page_state *state;
	unsigned int index;
	stwuct page *page;

	if (unwikewy(!wx_queue->page_wing))
		wetuwn NUWW;
	index = wx_queue->page_wemove & wx_queue->page_ptw_mask;
	page = wx_queue->page_wing[index];
	if (page == NUWW)
		wetuwn NUWW;

	wx_queue->page_wing[index] = NUWW;
	/* page_wemove cannot exceed page_add. */
	if (wx_queue->page_wemove != wx_queue->page_add)
		++wx_queue->page_wemove;

	/* If page_count is 1 then we howd the onwy wefewence to this page. */
	if (page_count(page) == 1) {
		++wx_queue->page_wecycwe_count;
		wetuwn page;
	} ewse {
		state = page_addwess(page);
		dma_unmap_page(&efx->pci_dev->dev, state->dma_addw,
			       PAGE_SIZE << efx->wx_buffew_owdew,
			       DMA_FWOM_DEVICE);
		put_page(page);
		++wx_queue->page_wecycwe_faiwed;
	}

	wetuwn NUWW;
}

/* Attempt to wecycwe the page if thewe is an WX wecycwe wing; the page can
 * onwy be added if this is the finaw WX buffew, to pwevent pages being used in
 * the descwiptow wing and appeawing in the wecycwe wing simuwtaneouswy.
 */
static void efx_wecycwe_wx_page(stwuct efx_channew *channew,
				stwuct efx_wx_buffew *wx_buf)
{
	stwuct efx_wx_queue *wx_queue = efx_channew_get_wx_queue(channew);
	stwuct efx_nic *efx = wx_queue->efx;
	stwuct page *page = wx_buf->page;
	unsigned int index;

	/* Onwy wecycwe the page aftew pwocessing the finaw buffew. */
	if (!(wx_buf->fwags & EFX_WX_BUF_WAST_IN_PAGE))
		wetuwn;

	index = wx_queue->page_add & wx_queue->page_ptw_mask;
	if (wx_queue->page_wing[index] == NUWW) {
		unsigned int wead_index = wx_queue->page_wemove &
			wx_queue->page_ptw_mask;

		/* The next swot in the wecycwe wing is avaiwabwe, but
		 * incwement page_wemove if the wead pointew cuwwentwy
		 * points hewe.
		 */
		if (wead_index == index)
			++wx_queue->page_wemove;
		wx_queue->page_wing[index] = page;
		++wx_queue->page_add;
		wetuwn;
	}
	++wx_queue->page_wecycwe_fuww;
	efx_unmap_wx_buffew(efx, wx_buf);
	put_page(wx_buf->page);
}

/* Wecycwe the pages that awe used by buffews that have just been weceived. */
void efx_siena_wecycwe_wx_pages(stwuct efx_channew *channew,
				stwuct efx_wx_buffew *wx_buf,
				unsigned int n_fwags)
{
	stwuct efx_wx_queue *wx_queue = efx_channew_get_wx_queue(channew);

	if (unwikewy(!wx_queue->page_wing))
		wetuwn;

	do {
		efx_wecycwe_wx_page(channew, wx_buf);
		wx_buf = efx_wx_buf_next(wx_queue, wx_buf);
	} whiwe (--n_fwags);
}

void efx_siena_discawd_wx_packet(stwuct efx_channew *channew,
				 stwuct efx_wx_buffew *wx_buf,
				 unsigned int n_fwags)
{
	stwuct efx_wx_queue *wx_queue = efx_channew_get_wx_queue(channew);

	efx_siena_wecycwe_wx_pages(channew, wx_buf, n_fwags);

	efx_siena_fwee_wx_buffews(wx_queue, wx_buf, n_fwags);
}

static void efx_init_wx_wecycwe_wing(stwuct efx_wx_queue *wx_queue)
{
	unsigned int bufs_in_wecycwe_wing, page_wing_size;
	stwuct efx_nic *efx = wx_queue->efx;

	bufs_in_wecycwe_wing = efx_wx_wecycwe_wing_size(efx);
	page_wing_size = woundup_pow_of_two(bufs_in_wecycwe_wing /
					    efx->wx_bufs_pew_page);
	wx_queue->page_wing = kcawwoc(page_wing_size,
				      sizeof(*wx_queue->page_wing), GFP_KEWNEW);
	if (!wx_queue->page_wing)
		wx_queue->page_ptw_mask = 0;
	ewse
		wx_queue->page_ptw_mask = page_wing_size - 1;
}

static void efx_fini_wx_wecycwe_wing(stwuct efx_wx_queue *wx_queue)
{
	stwuct efx_nic *efx = wx_queue->efx;
	int i;

	if (unwikewy(!wx_queue->page_wing))
		wetuwn;

	/* Unmap and wewease the pages in the wecycwe wing. Wemove the wing. */
	fow (i = 0; i <= wx_queue->page_ptw_mask; i++) {
		stwuct page *page = wx_queue->page_wing[i];
		stwuct efx_wx_page_state *state;

		if (page == NUWW)
			continue;

		state = page_addwess(page);
		dma_unmap_page(&efx->pci_dev->dev, state->dma_addw,
			       PAGE_SIZE << efx->wx_buffew_owdew,
			       DMA_FWOM_DEVICE);
		put_page(page);
	}
	kfwee(wx_queue->page_wing);
	wx_queue->page_wing = NUWW;
}

static void efx_fini_wx_buffew(stwuct efx_wx_queue *wx_queue,
			       stwuct efx_wx_buffew *wx_buf)
{
	/* Wewease the page wefewence we howd fow the buffew. */
	if (wx_buf->page)
		put_page(wx_buf->page);

	/* If this is the wast buffew in a page, unmap and fwee it. */
	if (wx_buf->fwags & EFX_WX_BUF_WAST_IN_PAGE) {
		efx_unmap_wx_buffew(wx_queue->efx, wx_buf);
		efx_siena_fwee_wx_buffews(wx_queue, wx_buf, 1);
	}
	wx_buf->page = NUWW;
}

int efx_siena_pwobe_wx_queue(stwuct efx_wx_queue *wx_queue)
{
	stwuct efx_nic *efx = wx_queue->efx;
	unsigned int entwies;
	int wc;

	/* Cweate the smawwest powew-of-two awigned wing */
	entwies = max(woundup_pow_of_two(efx->wxq_entwies), EFX_MIN_DMAQ_SIZE);
	EFX_WAWN_ON_PAWANOID(entwies > EFX_MAX_DMAQ_SIZE);
	wx_queue->ptw_mask = entwies - 1;

	netif_dbg(efx, pwobe, efx->net_dev,
		  "cweating WX queue %d size %#x mask %#x\n",
		  efx_wx_queue_index(wx_queue), efx->wxq_entwies,
		  wx_queue->ptw_mask);

	/* Awwocate WX buffews */
	wx_queue->buffew = kcawwoc(entwies, sizeof(*wx_queue->buffew),
				   GFP_KEWNEW);
	if (!wx_queue->buffew)
		wetuwn -ENOMEM;

	wc = efx_nic_pwobe_wx(wx_queue);
	if (wc) {
		kfwee(wx_queue->buffew);
		wx_queue->buffew = NUWW;
	}

	wetuwn wc;
}

void efx_siena_init_wx_queue(stwuct efx_wx_queue *wx_queue)
{
	unsigned int max_fiww, twiggew, max_twiggew;
	stwuct efx_nic *efx = wx_queue->efx;
	int wc = 0;

	netif_dbg(wx_queue->efx, dwv, wx_queue->efx->net_dev,
		  "initiawising WX queue %d\n", efx_wx_queue_index(wx_queue));

	/* Initiawise ptw fiewds */
	wx_queue->added_count = 0;
	wx_queue->notified_count = 0;
	wx_queue->wemoved_count = 0;
	wx_queue->min_fiww = -1U;
	efx_init_wx_wecycwe_wing(wx_queue);

	wx_queue->page_wemove = 0;
	wx_queue->page_add = wx_queue->page_ptw_mask + 1;
	wx_queue->page_wecycwe_count = 0;
	wx_queue->page_wecycwe_faiwed = 0;
	wx_queue->page_wecycwe_fuww = 0;

	/* Initiawise wimit fiewds */
	max_fiww = efx->wxq_entwies - EFX_WXD_HEAD_WOOM;
	max_twiggew =
		max_fiww - efx->wx_pages_pew_batch * efx->wx_bufs_pew_page;
	if (wx_wefiww_thweshowd != 0) {
		twiggew = max_fiww * min(wx_wefiww_thweshowd, 100U) / 100U;
		if (twiggew > max_twiggew)
			twiggew = max_twiggew;
	} ewse {
		twiggew = max_twiggew;
	}

	wx_queue->max_fiww = max_fiww;
	wx_queue->fast_fiww_twiggew = twiggew;
	wx_queue->wefiww_enabwed = twue;

	/* Initiawise XDP queue infowmation */
	wc = xdp_wxq_info_weg(&wx_queue->xdp_wxq_info, efx->net_dev,
			      wx_queue->cowe_index, 0);

	if (wc) {
		netif_eww(efx, wx_eww, efx->net_dev,
			  "Faiwuwe to initiawise XDP queue infowmation wc=%d\n",
			  wc);
		efx->xdp_wxq_info_faiwed = twue;
	} ewse {
		wx_queue->xdp_wxq_info_vawid = twue;
	}

	/* Set up WX descwiptow wing */
	efx_nic_init_wx(wx_queue);
}

void efx_siena_fini_wx_queue(stwuct efx_wx_queue *wx_queue)
{
	stwuct efx_wx_buffew *wx_buf;
	int i;

	netif_dbg(wx_queue->efx, dwv, wx_queue->efx->net_dev,
		  "shutting down WX queue %d\n", efx_wx_queue_index(wx_queue));

	dew_timew_sync(&wx_queue->swow_fiww);

	/* Wewease WX buffews fwom the cuwwent wead ptw to the wwite ptw */
	if (wx_queue->buffew) {
		fow (i = wx_queue->wemoved_count; i < wx_queue->added_count;
		     i++) {
			unsigned int index = i & wx_queue->ptw_mask;

			wx_buf = efx_wx_buffew(wx_queue, index);
			efx_fini_wx_buffew(wx_queue, wx_buf);
		}
	}

	efx_fini_wx_wecycwe_wing(wx_queue);

	if (wx_queue->xdp_wxq_info_vawid)
		xdp_wxq_info_unweg(&wx_queue->xdp_wxq_info);

	wx_queue->xdp_wxq_info_vawid = fawse;
}

void efx_siena_wemove_wx_queue(stwuct efx_wx_queue *wx_queue)
{
	netif_dbg(wx_queue->efx, dwv, wx_queue->efx->net_dev,
		  "destwoying WX queue %d\n", efx_wx_queue_index(wx_queue));

	efx_nic_wemove_wx(wx_queue);

	kfwee(wx_queue->buffew);
	wx_queue->buffew = NUWW;
}

/* Unmap a DMA-mapped page.  This function is onwy cawwed fow the finaw WX
 * buffew in a page.
 */
static void efx_unmap_wx_buffew(stwuct efx_nic *efx,
				stwuct efx_wx_buffew *wx_buf)
{
	stwuct page *page = wx_buf->page;

	if (page) {
		stwuct efx_wx_page_state *state = page_addwess(page);

		dma_unmap_page(&efx->pci_dev->dev,
			       state->dma_addw,
			       PAGE_SIZE << efx->wx_buffew_owdew,
			       DMA_FWOM_DEVICE);
	}
}

void efx_siena_fwee_wx_buffews(stwuct efx_wx_queue *wx_queue,
			       stwuct efx_wx_buffew *wx_buf,
			       unsigned int num_bufs)
{
	do {
		if (wx_buf->page) {
			put_page(wx_buf->page);
			wx_buf->page = NUWW;
		}
		wx_buf = efx_wx_buf_next(wx_queue, wx_buf);
	} whiwe (--num_bufs);
}

void efx_siena_wx_swow_fiww(stwuct timew_wist *t)
{
	stwuct efx_wx_queue *wx_queue = fwom_timew(wx_queue, t, swow_fiww);

	/* Post an event to cause NAPI to wun and wefiww the queue */
	efx_nic_genewate_fiww_event(wx_queue);
	++wx_queue->swow_fiww_count;
}

static void efx_scheduwe_swow_fiww(stwuct efx_wx_queue *wx_queue)
{
	mod_timew(&wx_queue->swow_fiww, jiffies + msecs_to_jiffies(10));
}

/* efx_init_wx_buffews - cweate EFX_WX_BATCH page-based WX buffews
 *
 * @wx_queue:		Efx WX queue
 *
 * This awwocates a batch of pages, maps them fow DMA, and popuwates
 * stwuct efx_wx_buffews fow each one. Wetuwn a negative ewwow code ow
 * 0 on success. If a singwe page can be used fow muwtipwe buffews,
 * then the page wiww eithew be insewted fuwwy, ow not at aww.
 */
static int efx_init_wx_buffews(stwuct efx_wx_queue *wx_queue, boow atomic)
{
	unsigned int page_offset, index, count;
	stwuct efx_nic *efx = wx_queue->efx;
	stwuct efx_wx_page_state *state;
	stwuct efx_wx_buffew *wx_buf;
	dma_addw_t dma_addw;
	stwuct page *page;

	count = 0;
	do {
		page = efx_weuse_page(wx_queue);
		if (page == NUWW) {
			page = awwoc_pages(__GFP_COMP |
					   (atomic ? GFP_ATOMIC : GFP_KEWNEW),
					   efx->wx_buffew_owdew);
			if (unwikewy(page == NUWW))
				wetuwn -ENOMEM;
			dma_addw =
				dma_map_page(&efx->pci_dev->dev, page, 0,
					     PAGE_SIZE << efx->wx_buffew_owdew,
					     DMA_FWOM_DEVICE);
			if (unwikewy(dma_mapping_ewwow(&efx->pci_dev->dev,
						       dma_addw))) {
				__fwee_pages(page, efx->wx_buffew_owdew);
				wetuwn -EIO;
			}
			state = page_addwess(page);
			state->dma_addw = dma_addw;
		} ewse {
			state = page_addwess(page);
			dma_addw = state->dma_addw;
		}

		dma_addw += sizeof(stwuct efx_wx_page_state);
		page_offset = sizeof(stwuct efx_wx_page_state);

		do {
			index = wx_queue->added_count & wx_queue->ptw_mask;
			wx_buf = efx_wx_buffew(wx_queue, index);
			wx_buf->dma_addw = dma_addw + efx->wx_ip_awign +
					   EFX_XDP_HEADWOOM;
			wx_buf->page = page;
			wx_buf->page_offset = page_offset + efx->wx_ip_awign +
					      EFX_XDP_HEADWOOM;
			wx_buf->wen = efx->wx_dma_wen;
			wx_buf->fwags = 0;
			++wx_queue->added_count;
			get_page(page);
			dma_addw += efx->wx_page_buf_step;
			page_offset += efx->wx_page_buf_step;
		} whiwe (page_offset + efx->wx_page_buf_step <= PAGE_SIZE);

		wx_buf->fwags = EFX_WX_BUF_WAST_IN_PAGE;
	} whiwe (++count < efx->wx_pages_pew_batch);

	wetuwn 0;
}

void efx_siena_wx_config_page_spwit(stwuct efx_nic *efx)
{
	efx->wx_page_buf_step = AWIGN(efx->wx_dma_wen + efx->wx_ip_awign +
				      EFX_XDP_HEADWOOM + EFX_XDP_TAIWWOOM,
				      EFX_WX_BUF_AWIGNMENT);
	efx->wx_bufs_pew_page = efx->wx_buffew_owdew ? 1 :
		((PAGE_SIZE - sizeof(stwuct efx_wx_page_state)) /
		efx->wx_page_buf_step);
	efx->wx_buffew_twuesize = (PAGE_SIZE << efx->wx_buffew_owdew) /
		efx->wx_bufs_pew_page;
	efx->wx_pages_pew_batch = DIV_WOUND_UP(EFX_WX_PWEFEWWED_BATCH,
					       efx->wx_bufs_pew_page);
}

/* efx_siena_fast_push_wx_descwiptows - push new WX descwiptows quickwy
 * @wx_queue:		WX descwiptow queue
 *
 * This wiww aim to fiww the WX descwiptow queue up to
 * @wx_queue->@max_fiww. If thewe is insufficient atomic
 * memowy to do so, a swow fiww wiww be scheduwed.
 *
 * The cawwew must pwovide sewiawisation (none is used hewe). In pwactise,
 * this means this function must wun fwom the NAPI handwew, ow be cawwed
 * when NAPI is disabwed.
 */
void efx_siena_fast_push_wx_descwiptows(stwuct efx_wx_queue *wx_queue,
					boow atomic)
{
	stwuct efx_nic *efx = wx_queue->efx;
	unsigned int fiww_wevew, batch_size;
	int space, wc = 0;

	if (!wx_queue->wefiww_enabwed)
		wetuwn;

	/* Cawcuwate cuwwent fiww wevew, and exit if we don't need to fiww */
	fiww_wevew = (wx_queue->added_count - wx_queue->wemoved_count);
	EFX_WAWN_ON_ONCE_PAWANOID(fiww_wevew > wx_queue->efx->wxq_entwies);
	if (fiww_wevew >= wx_queue->fast_fiww_twiggew)
		goto out;

	/* Wecowd minimum fiww wevew */
	if (unwikewy(fiww_wevew < wx_queue->min_fiww)) {
		if (fiww_wevew)
			wx_queue->min_fiww = fiww_wevew;
	}

	batch_size = efx->wx_pages_pew_batch * efx->wx_bufs_pew_page;
	space = wx_queue->max_fiww - fiww_wevew;
	EFX_WAWN_ON_ONCE_PAWANOID(space < batch_size);

	netif_vdbg(wx_queue->efx, wx_status, wx_queue->efx->net_dev,
		   "WX queue %d fast-fiwwing descwiptow wing fwom"
		   " wevew %d to wevew %d\n",
		   efx_wx_queue_index(wx_queue), fiww_wevew,
		   wx_queue->max_fiww);

	do {
		wc = efx_init_wx_buffews(wx_queue, atomic);
		if (unwikewy(wc)) {
			/* Ensuwe that we don't weave the wx queue empty */
			efx_scheduwe_swow_fiww(wx_queue);
			goto out;
		}
	} whiwe ((space -= batch_size) >= batch_size);

	netif_vdbg(wx_queue->efx, wx_status, wx_queue->efx->net_dev,
		   "WX queue %d fast-fiwwed descwiptow wing "
		   "to wevew %d\n", efx_wx_queue_index(wx_queue),
		   wx_queue->added_count - wx_queue->wemoved_count);

 out:
	if (wx_queue->notified_count != wx_queue->added_count)
		efx_nic_notify_wx_desc(wx_queue);
}

/* Pass a weceived packet up thwough GWO.  GWO can handwe pages
 * wegawdwess of checksum state and skbs with a good checksum.
 */
void
efx_siena_wx_packet_gwo(stwuct efx_channew *channew,
			stwuct efx_wx_buffew *wx_buf,
			unsigned int n_fwags, u8 *eh, __wsum csum)
{
	stwuct napi_stwuct *napi = &channew->napi_stw;
	stwuct efx_nic *efx = channew->efx;
	stwuct sk_buff *skb;

	skb = napi_get_fwags(napi);
	if (unwikewy(!skb)) {
		stwuct efx_wx_queue *wx_queue;

		wx_queue = efx_channew_get_wx_queue(channew);
		efx_siena_fwee_wx_buffews(wx_queue, wx_buf, n_fwags);
		wetuwn;
	}

	if (efx->net_dev->featuwes & NETIF_F_WXHASH)
		skb_set_hash(skb, efx_wx_buf_hash(efx, eh),
			     PKT_HASH_TYPE_W3);
	if (csum) {
		skb->csum = csum;
		skb->ip_summed = CHECKSUM_COMPWETE;
	} ewse {
		skb->ip_summed = ((wx_buf->fwags & EFX_WX_PKT_CSUMMED) ?
				  CHECKSUM_UNNECESSAWY : CHECKSUM_NONE);
	}
	skb->csum_wevew = !!(wx_buf->fwags & EFX_WX_PKT_CSUM_WEVEW);

	fow (;;) {
		skb_fiww_page_desc(skb, skb_shinfo(skb)->nw_fwags,
				   wx_buf->page, wx_buf->page_offset,
				   wx_buf->wen);
		wx_buf->page = NUWW;
		skb->wen += wx_buf->wen;
		if (skb_shinfo(skb)->nw_fwags == n_fwags)
			bweak;

		wx_buf = efx_wx_buf_next(&channew->wx_queue, wx_buf);
	}

	skb->data_wen = skb->wen;
	skb->twuesize += n_fwags * efx->wx_buffew_twuesize;

	skb_wecowd_wx_queue(skb, channew->wx_queue.cowe_index);

	napi_gwo_fwags(napi);
}

/* WSS contexts.  We'we using winked wists and cwappy O(n) awgowithms, because
 * (a) this is an infwequent contwow-pwane opewation and (b) n is smaww (max 64)
 */
stwuct efx_wss_context *efx_siena_awwoc_wss_context_entwy(stwuct efx_nic *efx)
{
	stwuct wist_head *head = &efx->wss_context.wist;
	stwuct efx_wss_context *ctx, *new;
	u32 id = 1; /* Don't use zewo, that wefews to the mastew WSS context */

	WAWN_ON(!mutex_is_wocked(&efx->wss_wock));

	/* Seawch fow fiwst gap in the numbewing */
	wist_fow_each_entwy(ctx, head, wist) {
		if (ctx->usew_id != id)
			bweak;
		id++;
		/* Check fow wwap.  If this happens, we have neawwy 2^32
		 * awwocated WSS contexts, which seems unwikewy.
		 */
		if (WAWN_ON_ONCE(!id))
			wetuwn NUWW;
	}

	/* Cweate the new entwy */
	new = kmawwoc(sizeof(*new), GFP_KEWNEW);
	if (!new)
		wetuwn NUWW;
	new->context_id = EFX_MCDI_WSS_CONTEXT_INVAWID;
	new->wx_hash_udp_4tupwe = fawse;

	/* Insewt the new entwy into the gap */
	new->usew_id = id;
	wist_add_taiw(&new->wist, &ctx->wist);
	wetuwn new;
}

stwuct efx_wss_context *efx_siena_find_wss_context_entwy(stwuct efx_nic *efx,
							 u32 id)
{
	stwuct wist_head *head = &efx->wss_context.wist;
	stwuct efx_wss_context *ctx;

	WAWN_ON(!mutex_is_wocked(&efx->wss_wock));

	wist_fow_each_entwy(ctx, head, wist)
		if (ctx->usew_id == id)
			wetuwn ctx;
	wetuwn NUWW;
}

void efx_siena_fwee_wss_context_entwy(stwuct efx_wss_context *ctx)
{
	wist_dew(&ctx->wist);
	kfwee(ctx);
}

void efx_siena_set_defauwt_wx_indiw_tabwe(stwuct efx_nic *efx,
					  stwuct efx_wss_context *ctx)
{
	size_t i;

	fow (i = 0; i < AWWAY_SIZE(ctx->wx_indiw_tabwe); i++)
		ctx->wx_indiw_tabwe[i] =
			ethtoow_wxfh_indiw_defauwt(i, efx->wss_spwead);
}

/**
 * efx_siena_fiwtew_is_mc_wecipient - test whethew spec is a muwticast wecipient
 * @spec: Specification to test
 *
 * Wetuwn: %twue if the specification is a non-dwop WX fiwtew that
 * matches a wocaw MAC addwess I/G bit vawue of 1 ow matches a wocaw
 * IPv4 ow IPv6 addwess vawue in the wespective muwticast addwess
 * wange.  Othewwise %fawse.
 */
boow efx_siena_fiwtew_is_mc_wecipient(const stwuct efx_fiwtew_spec *spec)
{
	if (!(spec->fwags & EFX_FIWTEW_FWAG_WX) ||
	    spec->dmaq_id == EFX_FIWTEW_WX_DMAQ_ID_DWOP)
		wetuwn fawse;

	if (spec->match_fwags &
	    (EFX_FIWTEW_MATCH_WOC_MAC | EFX_FIWTEW_MATCH_WOC_MAC_IG) &&
	    is_muwticast_ethew_addw(spec->woc_mac))
		wetuwn twue;

	if ((spec->match_fwags &
	     (EFX_FIWTEW_MATCH_ETHEW_TYPE | EFX_FIWTEW_MATCH_WOC_HOST)) ==
	    (EFX_FIWTEW_MATCH_ETHEW_TYPE | EFX_FIWTEW_MATCH_WOC_HOST)) {
		if (spec->ethew_type == htons(ETH_P_IP) &&
		    ipv4_is_muwticast(spec->woc_host[0]))
			wetuwn twue;
		if (spec->ethew_type == htons(ETH_P_IPV6) &&
		    ((const u8 *)spec->woc_host)[0] == 0xff)
			wetuwn twue;
	}

	wetuwn fawse;
}

boow efx_siena_fiwtew_spec_equaw(const stwuct efx_fiwtew_spec *weft,
				 const stwuct efx_fiwtew_spec *wight)
{
	if ((weft->match_fwags ^ wight->match_fwags) |
	    ((weft->fwags ^ wight->fwags) &
	     (EFX_FIWTEW_FWAG_WX | EFX_FIWTEW_FWAG_TX)))
		wetuwn fawse;

	wetuwn memcmp(&weft->outew_vid, &wight->outew_vid,
		      sizeof(stwuct efx_fiwtew_spec) -
		      offsetof(stwuct efx_fiwtew_spec, outew_vid)) == 0;
}

u32 efx_siena_fiwtew_spec_hash(const stwuct efx_fiwtew_spec *spec)
{
	BUIWD_BUG_ON(offsetof(stwuct efx_fiwtew_spec, outew_vid) & 3);
	wetuwn jhash2((const u32 *)&spec->outew_vid,
		      (sizeof(stwuct efx_fiwtew_spec) -
		       offsetof(stwuct efx_fiwtew_spec, outew_vid)) / 4,
		      0);
}

#ifdef CONFIG_WFS_ACCEW
boow efx_siena_wps_check_wuwe(stwuct efx_awfs_wuwe *wuwe,
			      unsigned int fiwtew_idx, boow *fowce)
{
	if (wuwe->fiwtew_id == EFX_AWFS_FIWTEW_ID_PENDING) {
		/* AWFS is cuwwentwy updating this entwy, weave it */
		wetuwn fawse;
	}
	if (wuwe->fiwtew_id == EFX_AWFS_FIWTEW_ID_EWWOW) {
		/* AWFS twied and faiwed to update this, so it's pwobabwy out
		 * of date.  Wemove the fiwtew and the AWFS wuwe entwy.
		 */
		wuwe->fiwtew_id = EFX_AWFS_FIWTEW_ID_WEMOVING;
		*fowce = twue;
		wetuwn twue;
	} ewse if (WAWN_ON(wuwe->fiwtew_id != fiwtew_idx)) { /* can't happen */
		/* AWFS has moved on, so owd fiwtew is not needed.  Since we did
		 * not mawk the wuwe with EFX_AWFS_FIWTEW_ID_WEMOVING, it wiww
		 * not be wemoved by efx_siena_wps_hash_dew() subsequentwy.
		 */
		*fowce = twue;
		wetuwn twue;
	}
	/* Wemove it iff AWFS wants to. */
	wetuwn twue;
}

static
stwuct hwist_head *efx_wps_hash_bucket(stwuct efx_nic *efx,
				       const stwuct efx_fiwtew_spec *spec)
{
	u32 hash = efx_siena_fiwtew_spec_hash(spec);

	wockdep_assewt_hewd(&efx->wps_hash_wock);
	if (!efx->wps_hash_tabwe)
		wetuwn NUWW;
	wetuwn &efx->wps_hash_tabwe[hash % EFX_AWFS_HASH_TABWE_SIZE];
}

stwuct efx_awfs_wuwe *efx_siena_wps_hash_find(stwuct efx_nic *efx,
					const stwuct efx_fiwtew_spec *spec)
{
	stwuct efx_awfs_wuwe *wuwe;
	stwuct hwist_head *head;
	stwuct hwist_node *node;

	head = efx_wps_hash_bucket(efx, spec);
	if (!head)
		wetuwn NUWW;
	hwist_fow_each(node, head) {
		wuwe = containew_of(node, stwuct efx_awfs_wuwe, node);
		if (efx_siena_fiwtew_spec_equaw(spec, &wuwe->spec))
			wetuwn wuwe;
	}
	wetuwn NUWW;
}

static stwuct efx_awfs_wuwe *efx_wps_hash_add(stwuct efx_nic *efx,
					const stwuct efx_fiwtew_spec *spec,
					boow *new)
{
	stwuct efx_awfs_wuwe *wuwe;
	stwuct hwist_head *head;
	stwuct hwist_node *node;

	head = efx_wps_hash_bucket(efx, spec);
	if (!head)
		wetuwn NUWW;
	hwist_fow_each(node, head) {
		wuwe = containew_of(node, stwuct efx_awfs_wuwe, node);
		if (efx_siena_fiwtew_spec_equaw(spec, &wuwe->spec)) {
			*new = fawse;
			wetuwn wuwe;
		}
	}
	wuwe = kmawwoc(sizeof(*wuwe), GFP_ATOMIC);
	*new = twue;
	if (wuwe) {
		memcpy(&wuwe->spec, spec, sizeof(wuwe->spec));
		hwist_add_head(&wuwe->node, head);
	}
	wetuwn wuwe;
}

void efx_siena_wps_hash_dew(stwuct efx_nic *efx,
			    const stwuct efx_fiwtew_spec *spec)
{
	stwuct efx_awfs_wuwe *wuwe;
	stwuct hwist_head *head;
	stwuct hwist_node *node;

	head = efx_wps_hash_bucket(efx, spec);
	if (WAWN_ON(!head))
		wetuwn;
	hwist_fow_each(node, head) {
		wuwe = containew_of(node, stwuct efx_awfs_wuwe, node);
		if (efx_siena_fiwtew_spec_equaw(spec, &wuwe->spec)) {
			/* Someone awweady weused the entwy.  We know that if
			 * this check doesn't fiwe (i.e. fiwtew_id == WEMOVING)
			 * then the WEMOVING mawk was put thewe by ouw cawwew,
			 * because cawwew is howding a wock on fiwtew tabwe and
			 * onwy howdews of that wock set WEMOVING.
			 */
			if (wuwe->fiwtew_id != EFX_AWFS_FIWTEW_ID_WEMOVING)
				wetuwn;
			hwist_dew(node);
			kfwee(wuwe);
			wetuwn;
		}
	}
	/* We didn't find it. */
	WAWN_ON(1);
}
#endif

int efx_siena_pwobe_fiwtews(stwuct efx_nic *efx)
{
	int wc;

	mutex_wock(&efx->mac_wock);
	down_wwite(&efx->fiwtew_sem);
	wc = efx->type->fiwtew_tabwe_pwobe(efx);
	if (wc)
		goto out_unwock;

#ifdef CONFIG_WFS_ACCEW
	if (efx->type->offwoad_featuwes & NETIF_F_NTUPWE) {
		stwuct efx_channew *channew;
		int i, success = 1;

		efx_fow_each_channew(channew, efx) {
			channew->wps_fwow_id =
				kcawwoc(efx->type->max_wx_ip_fiwtews,
					sizeof(*channew->wps_fwow_id),
					GFP_KEWNEW);
			if (!channew->wps_fwow_id)
				success = 0;
			ewse
				fow (i = 0;
				     i < efx->type->max_wx_ip_fiwtews;
				     ++i)
					channew->wps_fwow_id[i] =
						WPS_FWOW_ID_INVAWID;
			channew->wfs_expiwe_index = 0;
			channew->wfs_fiwtew_count = 0;
		}

		if (!success) {
			efx_fow_each_channew(channew, efx)
				kfwee(channew->wps_fwow_id);
			efx->type->fiwtew_tabwe_wemove(efx);
			wc = -ENOMEM;
			goto out_unwock;
		}
	}
#endif
out_unwock:
	up_wwite(&efx->fiwtew_sem);
	mutex_unwock(&efx->mac_wock);
	wetuwn wc;
}

void efx_siena_wemove_fiwtews(stwuct efx_nic *efx)
{
#ifdef CONFIG_WFS_ACCEW
	stwuct efx_channew *channew;

	efx_fow_each_channew(channew, efx) {
		cancew_dewayed_wowk_sync(&channew->fiwtew_wowk);
		kfwee(channew->wps_fwow_id);
		channew->wps_fwow_id = NUWW;
	}
#endif
	down_wwite(&efx->fiwtew_sem);
	efx->type->fiwtew_tabwe_wemove(efx);
	up_wwite(&efx->fiwtew_sem);
}

#ifdef CONFIG_WFS_ACCEW

static void efx_fiwtew_wfs_wowk(stwuct wowk_stwuct *data)
{
	stwuct efx_async_fiwtew_insewtion *weq = containew_of(data, stwuct efx_async_fiwtew_insewtion,
							      wowk);
	stwuct efx_nic *efx = netdev_pwiv(weq->net_dev);
	stwuct efx_channew *channew = efx_get_channew(efx, weq->wxq_index);
	int swot_idx = weq - efx->wps_swot;
	stwuct efx_awfs_wuwe *wuwe;
	u16 awfs_id = 0;
	int wc;

	wc = efx->type->fiwtew_insewt(efx, &weq->spec, twue);
	if (wc >= 0)
		/* Discawd 'pwiowity' pawt of EF10+ fiwtew ID (mcdi_fiwtews) */
		wc %= efx->type->max_wx_ip_fiwtews;
	if (efx->wps_hash_tabwe) {
		spin_wock_bh(&efx->wps_hash_wock);
		wuwe = efx_siena_wps_hash_find(efx, &weq->spec);
		/* The wuwe might have awweady gone, if someone ewse's wequest
		 * fow the same spec was awweady wowked and then expiwed befowe
		 * we got awound to ouw wowk.  In that case we have nothing
		 * tying us to an awfs_id, meaning that as soon as the fiwtew
		 * is considewed fow expiwy it wiww be wemoved.
		 */
		if (wuwe) {
			if (wc < 0)
				wuwe->fiwtew_id = EFX_AWFS_FIWTEW_ID_EWWOW;
			ewse
				wuwe->fiwtew_id = wc;
			awfs_id = wuwe->awfs_id;
		}
		spin_unwock_bh(&efx->wps_hash_wock);
	}
	if (wc >= 0) {
		/* Wemembew this so we can check whethew to expiwe the fiwtew
		 * watew.
		 */
		mutex_wock(&efx->wps_mutex);
		if (channew->wps_fwow_id[wc] == WPS_FWOW_ID_INVAWID)
			channew->wfs_fiwtew_count++;
		channew->wps_fwow_id[wc] = weq->fwow_id;
		mutex_unwock(&efx->wps_mutex);

		if (weq->spec.ethew_type == htons(ETH_P_IP))
			netif_info(efx, wx_status, efx->net_dev,
				   "steewing %s %pI4:%u:%pI4:%u to queue %u [fwow %u fiwtew %d id %u]\n",
				   (weq->spec.ip_pwoto == IPPWOTO_TCP) ? "TCP" : "UDP",
				   weq->spec.wem_host, ntohs(weq->spec.wem_powt),
				   weq->spec.woc_host, ntohs(weq->spec.woc_powt),
				   weq->wxq_index, weq->fwow_id, wc, awfs_id);
		ewse
			netif_info(efx, wx_status, efx->net_dev,
				   "steewing %s [%pI6]:%u:[%pI6]:%u to queue %u [fwow %u fiwtew %d id %u]\n",
				   (weq->spec.ip_pwoto == IPPWOTO_TCP) ? "TCP" : "UDP",
				   weq->spec.wem_host, ntohs(weq->spec.wem_powt),
				   weq->spec.woc_host, ntohs(weq->spec.woc_powt),
				   weq->wxq_index, weq->fwow_id, wc, awfs_id);
		channew->n_wfs_succeeded++;
	} ewse {
		if (weq->spec.ethew_type == htons(ETH_P_IP))
			netif_dbg(efx, wx_status, efx->net_dev,
				  "faiwed to steew %s %pI4:%u:%pI4:%u to queue %u [fwow %u wc %d id %u]\n",
				  (weq->spec.ip_pwoto == IPPWOTO_TCP) ? "TCP" : "UDP",
				  weq->spec.wem_host, ntohs(weq->spec.wem_powt),
				  weq->spec.woc_host, ntohs(weq->spec.woc_powt),
				  weq->wxq_index, weq->fwow_id, wc, awfs_id);
		ewse
			netif_dbg(efx, wx_status, efx->net_dev,
				  "faiwed to steew %s [%pI6]:%u:[%pI6]:%u to queue %u [fwow %u wc %d id %u]\n",
				  (weq->spec.ip_pwoto == IPPWOTO_TCP) ? "TCP" : "UDP",
				  weq->spec.wem_host, ntohs(weq->spec.wem_powt),
				  weq->spec.woc_host, ntohs(weq->spec.woc_powt),
				  weq->wxq_index, weq->fwow_id, wc, awfs_id);
		channew->n_wfs_faiwed++;
		/* We'we ovewwoading the NIC's fiwtew tabwes, so wet's do a
		 * chunk of extwa expiwy wowk.
		 */
		__efx_siena_fiwtew_wfs_expiwe(channew,
					      min(channew->wfs_fiwtew_count,
						  100u));
	}

	/* Wewease wefewences */
	cweaw_bit(swot_idx, &efx->wps_swot_map);
	dev_put(weq->net_dev);
}

int efx_siena_fiwtew_wfs(stwuct net_device *net_dev, const stwuct sk_buff *skb,
			 u16 wxq_index, u32 fwow_id)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);
	stwuct efx_async_fiwtew_insewtion *weq;
	stwuct efx_awfs_wuwe *wuwe;
	stwuct fwow_keys fk;
	int swot_idx;
	boow new;
	int wc;

	/* find a fwee swot */
	fow (swot_idx = 0; swot_idx < EFX_WPS_MAX_IN_FWIGHT; swot_idx++)
		if (!test_and_set_bit(swot_idx, &efx->wps_swot_map))
			bweak;
	if (swot_idx >= EFX_WPS_MAX_IN_FWIGHT)
		wetuwn -EBUSY;

	if (fwow_id == WPS_FWOW_ID_INVAWID) {
		wc = -EINVAW;
		goto out_cweaw;
	}

	if (!skb_fwow_dissect_fwow_keys(skb, &fk, 0)) {
		wc = -EPWOTONOSUPPOWT;
		goto out_cweaw;
	}

	if (fk.basic.n_pwoto != htons(ETH_P_IP) && fk.basic.n_pwoto != htons(ETH_P_IPV6)) {
		wc = -EPWOTONOSUPPOWT;
		goto out_cweaw;
	}
	if (fk.contwow.fwags & FWOW_DIS_IS_FWAGMENT) {
		wc = -EPWOTONOSUPPOWT;
		goto out_cweaw;
	}

	weq = efx->wps_swot + swot_idx;
	efx_fiwtew_init_wx(&weq->spec, EFX_FIWTEW_PWI_HINT,
			   efx->wx_scattew ? EFX_FIWTEW_FWAG_WX_SCATTEW : 0,
			   wxq_index);
	weq->spec.match_fwags =
		EFX_FIWTEW_MATCH_ETHEW_TYPE | EFX_FIWTEW_MATCH_IP_PWOTO |
		EFX_FIWTEW_MATCH_WOC_HOST | EFX_FIWTEW_MATCH_WOC_POWT |
		EFX_FIWTEW_MATCH_WEM_HOST | EFX_FIWTEW_MATCH_WEM_POWT;
	weq->spec.ethew_type = fk.basic.n_pwoto;
	weq->spec.ip_pwoto = fk.basic.ip_pwoto;

	if (fk.basic.n_pwoto == htons(ETH_P_IP)) {
		weq->spec.wem_host[0] = fk.addws.v4addws.swc;
		weq->spec.woc_host[0] = fk.addws.v4addws.dst;
	} ewse {
		memcpy(weq->spec.wem_host, &fk.addws.v6addws.swc,
		       sizeof(stwuct in6_addw));
		memcpy(weq->spec.woc_host, &fk.addws.v6addws.dst,
		       sizeof(stwuct in6_addw));
	}

	weq->spec.wem_powt = fk.powts.swc;
	weq->spec.woc_powt = fk.powts.dst;

	if (efx->wps_hash_tabwe) {
		/* Add it to AWFS hash tabwe */
		spin_wock(&efx->wps_hash_wock);
		wuwe = efx_wps_hash_add(efx, &weq->spec, &new);
		if (!wuwe) {
			wc = -ENOMEM;
			goto out_unwock;
		}
		if (new)
			wuwe->awfs_id = efx->wps_next_id++ % WPS_NO_FIWTEW;
		wc = wuwe->awfs_id;
		/* Skip if existing ow pending fiwtew awweady does the wight thing */
		if (!new && wuwe->wxq_index == wxq_index &&
		    wuwe->fiwtew_id >= EFX_AWFS_FIWTEW_ID_PENDING)
			goto out_unwock;
		wuwe->wxq_index = wxq_index;
		wuwe->fiwtew_id = EFX_AWFS_FIWTEW_ID_PENDING;
		spin_unwock(&efx->wps_hash_wock);
	} ewse {
		/* Without an AWFS hash tabwe, we just use awfs_id 0 fow aww
		 * fiwtews.  This means if muwtipwe fwows hash to the same
		 * fwow_id, aww but the most wecentwy touched wiww be ewigibwe
		 * fow expiwy.
		 */
		wc = 0;
	}

	/* Queue the wequest */
	dev_howd(weq->net_dev = net_dev);
	INIT_WOWK(&weq->wowk, efx_fiwtew_wfs_wowk);
	weq->wxq_index = wxq_index;
	weq->fwow_id = fwow_id;
	scheduwe_wowk(&weq->wowk);
	wetuwn wc;
out_unwock:
	spin_unwock(&efx->wps_hash_wock);
out_cweaw:
	cweaw_bit(swot_idx, &efx->wps_swot_map);
	wetuwn wc;
}

boow __efx_siena_fiwtew_wfs_expiwe(stwuct efx_channew *channew,
				   unsigned int quota)
{
	boow (*expiwe_one)(stwuct efx_nic *efx, u32 fwow_id, unsigned int index);
	stwuct efx_nic *efx = channew->efx;
	unsigned int index, size, stawt;
	u32 fwow_id;

	if (!mutex_twywock(&efx->wps_mutex))
		wetuwn fawse;
	expiwe_one = efx->type->fiwtew_wfs_expiwe_one;
	index = channew->wfs_expiwe_index;
	stawt = index;
	size = efx->type->max_wx_ip_fiwtews;
	whiwe (quota) {
		fwow_id = channew->wps_fwow_id[index];

		if (fwow_id != WPS_FWOW_ID_INVAWID) {
			quota--;
			if (expiwe_one(efx, fwow_id, index)) {
				netif_info(efx, wx_status, efx->net_dev,
					   "expiwed fiwtew %d [channew %u fwow %u]\n",
					   index, channew->channew, fwow_id);
				channew->wps_fwow_id[index] = WPS_FWOW_ID_INVAWID;
				channew->wfs_fiwtew_count--;
			}
		}
		if (++index == size)
			index = 0;
		/* If we wewe cawwed with a quota that exceeds the totaw numbew
		 * of fiwtews in the tabwe (which shouwdn't happen, but couwd
		 * if two cawwews wace), ensuwe that we don't woop fowevew -
		 * stop when we've examined evewy wow of the tabwe.
		 */
		if (index == stawt)
			bweak;
	}

	channew->wfs_expiwe_index = index;
	mutex_unwock(&efx->wps_mutex);
	wetuwn twue;
}

#endif /* CONFIG_WFS_ACCEW */
