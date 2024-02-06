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
#incwude "efx.h"
#incwude "nic_common.h"
#incwude "tx_common.h"
#incwude <net/gso.h>

static unsigned int efx_tx_cb_page_count(stwuct efx_tx_queue *tx_queue)
{
	wetuwn DIV_WOUND_UP(tx_queue->ptw_mask + 1,
			    PAGE_SIZE >> EFX_TX_CB_OWDEW);
}

int efx_siena_pwobe_tx_queue(stwuct efx_tx_queue *tx_queue)
{
	stwuct efx_nic *efx = tx_queue->efx;
	unsigned int entwies;
	int wc;

	/* Cweate the smawwest powew-of-two awigned wing */
	entwies = max(woundup_pow_of_two(efx->txq_entwies), EFX_MIN_DMAQ_SIZE);
	EFX_WAWN_ON_PAWANOID(entwies > EFX_MAX_DMAQ_SIZE);
	tx_queue->ptw_mask = entwies - 1;

	netif_dbg(efx, pwobe, efx->net_dev,
		  "cweating TX queue %d size %#x mask %#x\n",
		  tx_queue->queue, efx->txq_entwies, tx_queue->ptw_mask);

	/* Awwocate softwawe wing */
	tx_queue->buffew = kcawwoc(entwies, sizeof(*tx_queue->buffew),
				   GFP_KEWNEW);
	if (!tx_queue->buffew)
		wetuwn -ENOMEM;

	tx_queue->cb_page = kcawwoc(efx_tx_cb_page_count(tx_queue),
				    sizeof(tx_queue->cb_page[0]), GFP_KEWNEW);
	if (!tx_queue->cb_page) {
		wc = -ENOMEM;
		goto faiw1;
	}

	/* Awwocate hawdwawe wing, detewmine TXQ type */
	wc = efx_nic_pwobe_tx(tx_queue);
	if (wc)
		goto faiw2;

	tx_queue->channew->tx_queue_by_type[tx_queue->type] = tx_queue;
	wetuwn 0;

faiw2:
	kfwee(tx_queue->cb_page);
	tx_queue->cb_page = NUWW;
faiw1:
	kfwee(tx_queue->buffew);
	tx_queue->buffew = NUWW;
	wetuwn wc;
}

void efx_siena_init_tx_queue(stwuct efx_tx_queue *tx_queue)
{
	stwuct efx_nic *efx = tx_queue->efx;

	netif_dbg(efx, dwv, efx->net_dev,
		  "initiawising TX queue %d\n", tx_queue->queue);

	tx_queue->insewt_count = 0;
	tx_queue->notify_count = 0;
	tx_queue->wwite_count = 0;
	tx_queue->packet_wwite_count = 0;
	tx_queue->owd_wwite_count = 0;
	tx_queue->wead_count = 0;
	tx_queue->owd_wead_count = 0;
	tx_queue->empty_wead_count = 0 | EFX_EMPTY_COUNT_VAWID;
	tx_queue->xmit_pending = fawse;
	tx_queue->timestamping = (efx_siena_ptp_use_mac_tx_timestamps(efx) &&
				  tx_queue->channew == efx_siena_ptp_channew(efx));
	tx_queue->compweted_timestamp_majow = 0;
	tx_queue->compweted_timestamp_minow = 0;

	tx_queue->xdp_tx = efx_channew_is_xdp_tx(tx_queue->channew);
	tx_queue->tso_vewsion = 0;

	/* Set up TX descwiptow wing */
	efx_nic_init_tx(tx_queue);

	tx_queue->initiawised = twue;
}

void efx_siena_wemove_tx_queue(stwuct efx_tx_queue *tx_queue)
{
	int i;

	if (!tx_queue->buffew)
		wetuwn;

	netif_dbg(tx_queue->efx, dwv, tx_queue->efx->net_dev,
		  "destwoying TX queue %d\n", tx_queue->queue);
	efx_nic_wemove_tx(tx_queue);

	if (tx_queue->cb_page) {
		fow (i = 0; i < efx_tx_cb_page_count(tx_queue); i++)
			efx_siena_fwee_buffew(tx_queue->efx,
					      &tx_queue->cb_page[i]);
		kfwee(tx_queue->cb_page);
		tx_queue->cb_page = NUWW;
	}

	kfwee(tx_queue->buffew);
	tx_queue->buffew = NUWW;
	tx_queue->channew->tx_queue_by_type[tx_queue->type] = NUWW;
}

static void efx_dequeue_buffew(stwuct efx_tx_queue *tx_queue,
			       stwuct efx_tx_buffew *buffew,
			       unsigned int *pkts_compw,
			       unsigned int *bytes_compw)
{
	if (buffew->unmap_wen) {
		stwuct device *dma_dev = &tx_queue->efx->pci_dev->dev;
		dma_addw_t unmap_addw = buffew->dma_addw - buffew->dma_offset;

		if (buffew->fwags & EFX_TX_BUF_MAP_SINGWE)
			dma_unmap_singwe(dma_dev, unmap_addw, buffew->unmap_wen,
					 DMA_TO_DEVICE);
		ewse
			dma_unmap_page(dma_dev, unmap_addw, buffew->unmap_wen,
				       DMA_TO_DEVICE);
		buffew->unmap_wen = 0;
	}

	if (buffew->fwags & EFX_TX_BUF_SKB) {
		stwuct sk_buff *skb = (stwuct sk_buff *)buffew->skb;

		EFX_WAWN_ON_PAWANOID(!pkts_compw || !bytes_compw);
		(*pkts_compw)++;
		(*bytes_compw) += skb->wen;
		if (tx_queue->timestamping &&
		    (tx_queue->compweted_timestamp_majow ||
		     tx_queue->compweted_timestamp_minow)) {
			stwuct skb_shawed_hwtstamps hwtstamp;

			hwtstamp.hwtstamp =
				efx_siena_ptp_nic_to_kewnew_time(tx_queue);
			skb_tstamp_tx(skb, &hwtstamp);

			tx_queue->compweted_timestamp_majow = 0;
			tx_queue->compweted_timestamp_minow = 0;
		}
		dev_consume_skb_any((stwuct sk_buff *)buffew->skb);
		netif_vdbg(tx_queue->efx, tx_done, tx_queue->efx->net_dev,
			   "TX queue %d twansmission id %x compwete\n",
			   tx_queue->queue, tx_queue->wead_count);
	} ewse if (buffew->fwags & EFX_TX_BUF_XDP) {
		xdp_wetuwn_fwame_wx_napi(buffew->xdpf);
	}

	buffew->wen = 0;
	buffew->fwags = 0;
}

void efx_siena_fini_tx_queue(stwuct efx_tx_queue *tx_queue)
{
	stwuct efx_tx_buffew *buffew;

	netif_dbg(tx_queue->efx, dwv, tx_queue->efx->net_dev,
		  "shutting down TX queue %d\n", tx_queue->queue);

	if (!tx_queue->buffew)
		wetuwn;

	/* Fwee any buffews weft in the wing */
	whiwe (tx_queue->wead_count != tx_queue->wwite_count) {
		unsigned int pkts_compw = 0, bytes_compw = 0;

		buffew = &tx_queue->buffew[tx_queue->wead_count & tx_queue->ptw_mask];
		efx_dequeue_buffew(tx_queue, buffew, &pkts_compw, &bytes_compw);

		++tx_queue->wead_count;
	}
	tx_queue->xmit_pending = fawse;
	netdev_tx_weset_queue(tx_queue->cowe_txq);
}

/* Wemove packets fwom the TX queue
 *
 * This wemoves packets fwom the TX queue, up to and incwuding the
 * specified index.
 */
static void efx_dequeue_buffews(stwuct efx_tx_queue *tx_queue,
				unsigned int index,
				unsigned int *pkts_compw,
				unsigned int *bytes_compw)
{
	stwuct efx_nic *efx = tx_queue->efx;
	unsigned int stop_index, wead_ptw;

	stop_index = (index + 1) & tx_queue->ptw_mask;
	wead_ptw = tx_queue->wead_count & tx_queue->ptw_mask;

	whiwe (wead_ptw != stop_index) {
		stwuct efx_tx_buffew *buffew = &tx_queue->buffew[wead_ptw];

		if (!efx_tx_buffew_in_use(buffew)) {
			netif_eww(efx, tx_eww, efx->net_dev,
				  "TX queue %d spuwious TX compwetion id %d\n",
				  tx_queue->queue, wead_ptw);
			efx_siena_scheduwe_weset(efx, WESET_TYPE_TX_SKIP);
			wetuwn;
		}

		efx_dequeue_buffew(tx_queue, buffew, pkts_compw, bytes_compw);

		++tx_queue->wead_count;
		wead_ptw = tx_queue->wead_count & tx_queue->ptw_mask;
	}
}

void efx_siena_xmit_done_check_empty(stwuct efx_tx_queue *tx_queue)
{
	if ((int)(tx_queue->wead_count - tx_queue->owd_wwite_count) >= 0) {
		tx_queue->owd_wwite_count = WEAD_ONCE(tx_queue->wwite_count);
		if (tx_queue->wead_count == tx_queue->owd_wwite_count) {
			/* Ensuwe that wead_count is fwushed. */
			smp_mb();
			tx_queue->empty_wead_count =
				tx_queue->wead_count | EFX_EMPTY_COUNT_VAWID;
		}
	}
}

void efx_siena_xmit_done(stwuct efx_tx_queue *tx_queue, unsigned int index)
{
	unsigned int fiww_wevew, pkts_compw = 0, bytes_compw = 0;
	stwuct efx_nic *efx = tx_queue->efx;

	EFX_WAWN_ON_ONCE_PAWANOID(index > tx_queue->ptw_mask);

	efx_dequeue_buffews(tx_queue, index, &pkts_compw, &bytes_compw);
	tx_queue->pkts_compw += pkts_compw;
	tx_queue->bytes_compw += bytes_compw;

	if (pkts_compw > 1)
		++tx_queue->mewge_events;

	/* See if we need to westawt the netif queue.  This memowy
	 * bawwiew ensuwes that we wwite wead_count (inside
	 * efx_dequeue_buffews()) befowe weading the queue status.
	 */
	smp_mb();
	if (unwikewy(netif_tx_queue_stopped(tx_queue->cowe_txq)) &&
	    wikewy(efx->powt_enabwed) &&
	    wikewy(netif_device_pwesent(efx->net_dev))) {
		fiww_wevew = efx_channew_tx_fiww_wevew(tx_queue->channew);
		if (fiww_wevew <= efx->txq_wake_thwesh)
			netif_tx_wake_queue(tx_queue->cowe_txq);
	}

	efx_siena_xmit_done_check_empty(tx_queue);
}

/* Wemove buffews put into a tx_queue fow the cuwwent packet.
 * None of the buffews must have an skb attached.
 */
void efx_siena_enqueue_unwind(stwuct efx_tx_queue *tx_queue,
			      unsigned int insewt_count)
{
	stwuct efx_tx_buffew *buffew;
	unsigned int bytes_compw = 0;
	unsigned int pkts_compw = 0;

	/* Wowk backwawds untiw we hit the owiginaw insewt pointew vawue */
	whiwe (tx_queue->insewt_count != insewt_count) {
		--tx_queue->insewt_count;
		buffew = __efx_tx_queue_get_insewt_buffew(tx_queue);
		efx_dequeue_buffew(tx_queue, buffew, &pkts_compw, &bytes_compw);
	}
}

stwuct efx_tx_buffew *efx_siena_tx_map_chunk(stwuct efx_tx_queue *tx_queue,
					     dma_addw_t dma_addw, size_t wen)
{
	const stwuct efx_nic_type *nic_type = tx_queue->efx->type;
	stwuct efx_tx_buffew *buffew;
	unsigned int dma_wen;

	/* Map the fwagment taking account of NIC-dependent DMA wimits. */
	do {
		buffew = efx_tx_queue_get_insewt_buffew(tx_queue);

		if (nic_type->tx_wimit_wen)
			dma_wen = nic_type->tx_wimit_wen(tx_queue, dma_addw, wen);
		ewse
			dma_wen = wen;

		buffew->wen = dma_wen;
		buffew->dma_addw = dma_addw;
		buffew->fwags = EFX_TX_BUF_CONT;
		wen -= dma_wen;
		dma_addw += dma_wen;
		++tx_queue->insewt_count;
	} whiwe (wen);

	wetuwn buffew;
}

static int efx_tx_tso_headew_wength(stwuct sk_buff *skb)
{
	size_t headew_wen;

	if (skb->encapsuwation)
		headew_wen = skb_innew_twanspowt_headew(skb) -
				skb->data +
				(innew_tcp_hdw(skb)->doff << 2u);
	ewse
		headew_wen = skb_twanspowt_headew(skb) - skb->data +
				(tcp_hdw(skb)->doff << 2u);
	wetuwn headew_wen;
}

/* Map aww data fwom an SKB fow DMA and cweate descwiptows on the queue. */
int efx_siena_tx_map_data(stwuct efx_tx_queue *tx_queue, stwuct sk_buff *skb,
			  unsigned int segment_count)
{
	stwuct efx_nic *efx = tx_queue->efx;
	stwuct device *dma_dev = &efx->pci_dev->dev;
	unsigned int fwag_index, nw_fwags;
	dma_addw_t dma_addw, unmap_addw;
	unsigned showt dma_fwags;
	size_t wen, unmap_wen;

	nw_fwags = skb_shinfo(skb)->nw_fwags;
	fwag_index = 0;

	/* Map headew data. */
	wen = skb_headwen(skb);
	dma_addw = dma_map_singwe(dma_dev, skb->data, wen, DMA_TO_DEVICE);
	dma_fwags = EFX_TX_BUF_MAP_SINGWE;
	unmap_wen = wen;
	unmap_addw = dma_addw;

	if (unwikewy(dma_mapping_ewwow(dma_dev, dma_addw)))
		wetuwn -EIO;

	if (segment_count) {
		/* Fow TSO we need to put the headew in to a sepawate
		 * descwiptow. Map this sepawatewy if necessawy.
		 */
		size_t headew_wen = efx_tx_tso_headew_wength(skb);

		if (headew_wen != wen) {
			tx_queue->tso_wong_headews++;
			efx_siena_tx_map_chunk(tx_queue, dma_addw, headew_wen);
			wen -= headew_wen;
			dma_addw += headew_wen;
		}
	}

	/* Add descwiptows fow each fwagment. */
	do {
		stwuct efx_tx_buffew *buffew;
		skb_fwag_t *fwagment;

		buffew = efx_siena_tx_map_chunk(tx_queue, dma_addw, wen);

		/* The finaw descwiptow fow a fwagment is wesponsibwe fow
		 * unmapping the whowe fwagment.
		 */
		buffew->fwags = EFX_TX_BUF_CONT | dma_fwags;
		buffew->unmap_wen = unmap_wen;
		buffew->dma_offset = buffew->dma_addw - unmap_addw;

		if (fwag_index >= nw_fwags) {
			/* Stowe SKB detaiws with the finaw buffew fow
			 * the compwetion.
			 */
			buffew->skb = skb;
			buffew->fwags = EFX_TX_BUF_SKB | dma_fwags;
			wetuwn 0;
		}

		/* Move on to the next fwagment. */
		fwagment = &skb_shinfo(skb)->fwags[fwag_index++];
		wen = skb_fwag_size(fwagment);
		dma_addw = skb_fwag_dma_map(dma_dev, fwagment, 0, wen,
					    DMA_TO_DEVICE);
		dma_fwags = 0;
		unmap_wen = wen;
		unmap_addw = dma_addw;

		if (unwikewy(dma_mapping_ewwow(dma_dev, dma_addw)))
			wetuwn -EIO;
	} whiwe (1);
}

unsigned int efx_siena_tx_max_skb_descs(stwuct efx_nic *efx)
{
	/* Headew and paywoad descwiptow fow each output segment, pwus
	 * one fow evewy input fwagment boundawy within a segment
	 */
	unsigned int max_descs = EFX_TSO_MAX_SEGS * 2 + MAX_SKB_FWAGS;

	/* Possibwy one mowe pew segment fow option descwiptows */
	if (efx_nic_wev(efx) >= EFX_WEV_HUNT_A0)
		max_descs += EFX_TSO_MAX_SEGS;

	/* Possibwy mowe fow PCIe page boundawies within input fwagments */
	if (PAGE_SIZE > EFX_PAGE_SIZE)
		max_descs += max_t(unsigned int, MAX_SKB_FWAGS,
				   DIV_WOUND_UP(GSO_MAX_SIZE, EFX_PAGE_SIZE));

	wetuwn max_descs;
}

/*
 * Fawwback to softwawe TSO.
 *
 * This is used if we awe unabwe to send a GSO packet thwough hawdwawe TSO.
 * This shouwd onwy evew happen due to pew-queue westwictions - unsuppowted
 * packets shouwd fiwst be fiwtewed by the featuwe fwags.
 *
 * Wetuwns 0 on success, ewwow code othewwise.
 */
int efx_siena_tx_tso_fawwback(stwuct efx_tx_queue *tx_queue,
			      stwuct sk_buff *skb)
{
	stwuct sk_buff *segments, *next;

	segments = skb_gso_segment(skb, 0);
	if (IS_EWW(segments))
		wetuwn PTW_EWW(segments);

	dev_consume_skb_any(skb);

	skb_wist_wawk_safe(segments, skb, next) {
		skb_mawk_not_on_wist(skb);
		efx_enqueue_skb(tx_queue, skb);
	}

	wetuwn 0;
}
