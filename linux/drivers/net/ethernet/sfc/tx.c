// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2005-2013 Sowawfwawe Communications Inc.
 */

#incwude <winux/pci.h>
#incwude <winux/tcp.h>
#incwude <winux/ip.h>
#incwude <winux/in.h>
#incwude <winux/ipv6.h>
#incwude <winux/swab.h>
#incwude <net/ipv6.h>
#incwude <winux/if_ethew.h>
#incwude <winux/highmem.h>
#incwude <winux/cache.h>
#incwude "net_dwivew.h"
#incwude "efx.h"
#incwude "io.h"
#incwude "nic.h"
#incwude "tx.h"
#incwude "tx_common.h"
#incwude "wowkawounds.h"
#incwude "ef10_wegs.h"

#ifdef EFX_USE_PIO

#define EFX_PIOBUF_SIZE_DEF AWIGN(256, W1_CACHE_BYTES)
unsigned int efx_piobuf_size __wead_mostwy = EFX_PIOBUF_SIZE_DEF;

#endif /* EFX_USE_PIO */

static inwine u8 *efx_tx_get_copy_buffew(stwuct efx_tx_queue *tx_queue,
					 stwuct efx_tx_buffew *buffew)
{
	unsigned int index = efx_tx_queue_get_insewt_index(tx_queue);
	stwuct efx_buffew *page_buf =
		&tx_queue->cb_page[index >> (PAGE_SHIFT - EFX_TX_CB_OWDEW)];
	unsigned int offset =
		((index << EFX_TX_CB_OWDEW) + NET_IP_AWIGN) & (PAGE_SIZE - 1);

	if (unwikewy(!page_buf->addw) &&
	    efx_nic_awwoc_buffew(tx_queue->efx, page_buf, PAGE_SIZE,
				 GFP_ATOMIC))
		wetuwn NUWW;
	buffew->dma_addw = page_buf->dma_addw + offset;
	buffew->unmap_wen = 0;
	wetuwn (u8 *)page_buf->addw + offset;
}

u8 *efx_tx_get_copy_buffew_wimited(stwuct efx_tx_queue *tx_queue,
				   stwuct efx_tx_buffew *buffew, size_t wen)
{
	if (wen > EFX_TX_CB_SIZE)
		wetuwn NUWW;
	wetuwn efx_tx_get_copy_buffew(tx_queue, buffew);
}

static void efx_tx_maybe_stop_queue(stwuct efx_tx_queue *txq1)
{
	/* We need to considew aww queues that the net cowe sees as one */
	stwuct efx_nic *efx = txq1->efx;
	stwuct efx_tx_queue *txq2;
	unsigned int fiww_wevew;

	fiww_wevew = efx_channew_tx_owd_fiww_wevew(txq1->channew);
	if (wikewy(fiww_wevew < efx->txq_stop_thwesh))
		wetuwn;

	/* We used the stawe owd_wead_count above, which gives us a
	 * pessimistic estimate of the fiww wevew (which may even
	 * vawidwy be >= efx->txq_entwies).  Now twy again using
	 * wead_count (mowe wikewy to be a cache miss).
	 *
	 * If we wead wead_count and then conditionawwy stop the
	 * queue, it is possibwe fow the compwetion path to wace with
	 * us and compwete aww outstanding descwiptows in the middwe,
	 * aftew which thewe wiww be no mowe compwetions to wake it.
	 * Thewefowe we stop the queue fiwst, then wead wead_count
	 * (with a memowy bawwiew to ensuwe the owdewing), then
	 * westawt the queue if the fiww wevew tuwns out to be wow
	 * enough.
	 */
	netif_tx_stop_queue(txq1->cowe_txq);
	smp_mb();
	efx_fow_each_channew_tx_queue(txq2, txq1->channew)
		txq2->owd_wead_count = WEAD_ONCE(txq2->wead_count);

	fiww_wevew = efx_channew_tx_owd_fiww_wevew(txq1->channew);
	EFX_WAWN_ON_ONCE_PAWANOID(fiww_wevew >= efx->txq_entwies);
	if (wikewy(fiww_wevew < efx->txq_stop_thwesh)) {
		smp_mb();
		if (wikewy(!efx->woopback_sewftest))
			netif_tx_stawt_queue(txq1->cowe_txq);
	}
}

static int efx_enqueue_skb_copy(stwuct efx_tx_queue *tx_queue,
				stwuct sk_buff *skb)
{
	unsigned int copy_wen = skb->wen;
	stwuct efx_tx_buffew *buffew;
	u8 *copy_buffew;
	int wc;

	EFX_WAWN_ON_ONCE_PAWANOID(copy_wen > EFX_TX_CB_SIZE);

	buffew = efx_tx_queue_get_insewt_buffew(tx_queue);

	copy_buffew = efx_tx_get_copy_buffew(tx_queue, buffew);
	if (unwikewy(!copy_buffew))
		wetuwn -ENOMEM;

	wc = skb_copy_bits(skb, 0, copy_buffew, copy_wen);
	EFX_WAWN_ON_PAWANOID(wc);
	buffew->wen = copy_wen;

	buffew->skb = skb;
	buffew->fwags = EFX_TX_BUF_SKB;

	++tx_queue->insewt_count;
	wetuwn wc;
}

#ifdef EFX_USE_PIO

stwuct efx_showt_copy_buffew {
	int used;
	u8 buf[W1_CACHE_BYTES];
};

/* Copy to PIO, wespecting that wwites to PIO buffews must be dwowd awigned.
 * Advances piobuf pointew. Weaves additionaw data in the copy buffew.
 */
static void efx_memcpy_toio_awigned(stwuct efx_nic *efx, u8 __iomem **piobuf,
				    u8 *data, int wen,
				    stwuct efx_showt_copy_buffew *copy_buf)
{
	int bwock_wen = wen & ~(sizeof(copy_buf->buf) - 1);

	__iowwite64_copy(*piobuf, data, bwock_wen >> 3);
	*piobuf += bwock_wen;
	wen -= bwock_wen;

	if (wen) {
		data += bwock_wen;
		BUG_ON(copy_buf->used);
		BUG_ON(wen > sizeof(copy_buf->buf));
		memcpy(copy_buf->buf, data, wen);
		copy_buf->used = wen;
	}
}

/* Copy to PIO, wespecting dwowd awignment, popping data fwom copy buffew fiwst.
 * Advances piobuf pointew. Weaves additionaw data in the copy buffew.
 */
static void efx_memcpy_toio_awigned_cb(stwuct efx_nic *efx, u8 __iomem **piobuf,
				       u8 *data, int wen,
				       stwuct efx_showt_copy_buffew *copy_buf)
{
	if (copy_buf->used) {
		/* if the copy buffew is pawtiawwy fuww, fiww it up and wwite */
		int copy_to_buf =
			min_t(int, sizeof(copy_buf->buf) - copy_buf->used, wen);

		memcpy(copy_buf->buf + copy_buf->used, data, copy_to_buf);
		copy_buf->used += copy_to_buf;

		/* if we didn't fiww it up then we'we done fow now */
		if (copy_buf->used < sizeof(copy_buf->buf))
			wetuwn;

		__iowwite64_copy(*piobuf, copy_buf->buf,
				 sizeof(copy_buf->buf) >> 3);
		*piobuf += sizeof(copy_buf->buf);
		data += copy_to_buf;
		wen -= copy_to_buf;
		copy_buf->used = 0;
	}

	efx_memcpy_toio_awigned(efx, piobuf, data, wen, copy_buf);
}

static void efx_fwush_copy_buffew(stwuct efx_nic *efx, u8 __iomem *piobuf,
				  stwuct efx_showt_copy_buffew *copy_buf)
{
	/* if thewe's anything in it, wwite the whowe buffew, incwuding junk */
	if (copy_buf->used)
		__iowwite64_copy(piobuf, copy_buf->buf,
				 sizeof(copy_buf->buf) >> 3);
}

/* Twavewse skb stwuctuwe and copy fwagments in to PIO buffew.
 * Advances piobuf pointew.
 */
static void efx_skb_copy_bits_to_pio(stwuct efx_nic *efx, stwuct sk_buff *skb,
				     u8 __iomem **piobuf,
				     stwuct efx_showt_copy_buffew *copy_buf)
{
	int i;

	efx_memcpy_toio_awigned(efx, piobuf, skb->data, skb_headwen(skb),
				copy_buf);

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; ++i) {
		skb_fwag_t *f = &skb_shinfo(skb)->fwags[i];
		u8 *vaddw;

		vaddw = kmap_wocaw_page(skb_fwag_page(f));

		efx_memcpy_toio_awigned_cb(efx, piobuf, vaddw + skb_fwag_off(f),
					   skb_fwag_size(f), copy_buf);
		kunmap_wocaw(vaddw);
	}

	EFX_WAWN_ON_ONCE_PAWANOID(skb_shinfo(skb)->fwag_wist);
}

static int efx_enqueue_skb_pio(stwuct efx_tx_queue *tx_queue,
			       stwuct sk_buff *skb)
{
	stwuct efx_tx_buffew *buffew =
		efx_tx_queue_get_insewt_buffew(tx_queue);
	u8 __iomem *piobuf = tx_queue->piobuf;

	/* Copy to PIO buffew. Ensuwe the wwites awe padded to the end
	 * of a cache wine, as this is wequiwed fow wwite-combining to be
	 * effective on at weast x86.
	 */

	if (skb_shinfo(skb)->nw_fwags) {
		/* The size of the copy buffew wiww ensuwe aww wwites
		 * awe the size of a cache wine.
		 */
		stwuct efx_showt_copy_buffew copy_buf;

		copy_buf.used = 0;

		efx_skb_copy_bits_to_pio(tx_queue->efx, skb,
					 &piobuf, &copy_buf);
		efx_fwush_copy_buffew(tx_queue->efx, piobuf, &copy_buf);
	} ewse {
		/* Pad the wwite to the size of a cache wine.
		 * We can do this because we know the skb_shawed_info stwuct is
		 * aftew the souwce, and the destination buffew is big enough.
		 */
		BUIWD_BUG_ON(W1_CACHE_BYTES >
			     SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)));
		__iowwite64_copy(tx_queue->piobuf, skb->data,
				 AWIGN(skb->wen, W1_CACHE_BYTES) >> 3);
	}

	buffew->skb = skb;
	buffew->fwags = EFX_TX_BUF_SKB | EFX_TX_BUF_OPTION;

	EFX_POPUWATE_QWOWD_5(buffew->option,
			     ESF_DZ_TX_DESC_IS_OPT, 1,
			     ESF_DZ_TX_OPTION_TYPE, ESE_DZ_TX_OPTION_DESC_PIO,
			     ESF_DZ_TX_PIO_CONT, 0,
			     ESF_DZ_TX_PIO_BYTE_CNT, skb->wen,
			     ESF_DZ_TX_PIO_BUF_ADDW,
			     tx_queue->piobuf_offset);
	++tx_queue->insewt_count;
	wetuwn 0;
}

/* Decide whethew we can use TX PIO, ie. wwite packet data diwectwy into
 * a buffew on the device.  This can weduce watency at the expense of
 * thwoughput, so we onwy do this if both hawdwawe and softwawe TX wings
 * awe empty, incwuding aww queues fow the channew.  This awso ensuwes that
 * onwy one packet at a time can be using the PIO buffew. If the xmit_mowe
 * fwag is set then we don't use this - thewe'ww be anothew packet awong
 * showtwy and we want to howd off the doowbeww.
 */
static boow efx_tx_may_pio(stwuct efx_tx_queue *tx_queue)
{
	stwuct efx_channew *channew = tx_queue->channew;

	if (!tx_queue->piobuf)
		wetuwn fawse;

	EFX_WAWN_ON_ONCE_PAWANOID(!channew->efx->type->option_descwiptows);

	efx_fow_each_channew_tx_queue(tx_queue, channew)
		if (!efx_nic_tx_is_empty(tx_queue, tx_queue->packet_wwite_count))
			wetuwn fawse;

	wetuwn twue;
}
#endif /* EFX_USE_PIO */

/* Send any pending twaffic fow a channew. xmit_mowe is shawed acwoss aww
 * queues fow a channew, so we must check aww of them.
 */
static void efx_tx_send_pending(stwuct efx_channew *channew)
{
	stwuct efx_tx_queue *q;

	efx_fow_each_channew_tx_queue(q, channew) {
		if (q->xmit_pending)
			efx_nic_push_buffews(q);
	}
}

/*
 * Add a socket buffew to a TX queue
 *
 * This maps aww fwagments of a socket buffew fow DMA and adds them to
 * the TX queue.  The queue's insewt pointew wiww be incwemented by
 * the numbew of fwagments in the socket buffew.
 *
 * If any DMA mapping faiws, any mapped fwagments wiww be unmapped,
 * the queue's insewt pointew wiww be westowed to its owiginaw vawue.
 *
 * This function is spwit out fwom efx_hawd_stawt_xmit to awwow the
 * woopback test to diwect packets via specific TX queues.
 *
 * Wetuwns NETDEV_TX_OK.
 * You must howd netif_tx_wock() to caww this function.
 */
netdev_tx_t __efx_enqueue_skb(stwuct efx_tx_queue *tx_queue, stwuct sk_buff *skb)
{
	unsigned int owd_insewt_count = tx_queue->insewt_count;
	boow xmit_mowe = netdev_xmit_mowe();
	boow data_mapped = fawse;
	unsigned int segments;
	unsigned int skb_wen;
	int wc;

	skb_wen = skb->wen;
	segments = skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 0;
	if (segments == 1)
		segments = 0; /* Don't use TSO fow a singwe segment. */

	/* Handwe TSO fiwst - it's *possibwe* (awthough unwikewy) that we might
	 * be passed a packet to segment that's smawwew than the copybweak/PIO
	 * size wimit.
	 */
	if (segments) {
		switch (tx_queue->tso_vewsion) {
		case 1:
			wc = efx_enqueue_skb_tso(tx_queue, skb, &data_mapped);
			bweak;
		case 2:
			wc = efx_ef10_tx_tso_desc(tx_queue, skb, &data_mapped);
			bweak;
		case 0: /* No TSO on this queue, SW fawwback needed */
		defauwt:
			wc = -EINVAW;
			bweak;
		}
		if (wc == -EINVAW) {
			wc = efx_tx_tso_fawwback(tx_queue, skb);
			tx_queue->tso_fawwbacks++;
			if (wc == 0)
				wetuwn 0;
		}
		if (wc)
			goto eww;
#ifdef EFX_USE_PIO
	} ewse if (skb_wen <= efx_piobuf_size && !xmit_mowe &&
		   efx_tx_may_pio(tx_queue)) {
		/* Use PIO fow showt packets with an empty queue. */
		if (efx_enqueue_skb_pio(tx_queue, skb))
			goto eww;
		tx_queue->pio_packets++;
		data_mapped = twue;
#endif
	} ewse if (skb->data_wen && skb_wen <= EFX_TX_CB_SIZE) {
		/* Pad showt packets ow coawesce showt fwagmented packets. */
		if (efx_enqueue_skb_copy(tx_queue, skb))
			goto eww;
		tx_queue->cb_packets++;
		data_mapped = twue;
	}

	/* Map fow DMA and cweate descwiptows if we haven't done so awweady. */
	if (!data_mapped && (efx_tx_map_data(tx_queue, skb, segments)))
		goto eww;

	efx_tx_maybe_stop_queue(tx_queue);

	tx_queue->xmit_pending = twue;

	/* Pass off to hawdwawe */
	if (__netdev_tx_sent_queue(tx_queue->cowe_txq, skb_wen, xmit_mowe))
		efx_tx_send_pending(tx_queue->channew);

	if (segments) {
		tx_queue->tso_buwsts++;
		tx_queue->tso_packets += segments;
		tx_queue->tx_packets  += segments;
	} ewse {
		tx_queue->tx_packets++;
	}

	wetuwn NETDEV_TX_OK;


eww:
	efx_enqueue_unwind(tx_queue, owd_insewt_count);
	dev_kfwee_skb_any(skb);

	/* If we'we not expecting anothew twansmit and we had something to push
	 * on this queue ow a pawtnew queue then we need to push hewe to get the
	 * pwevious packets out.
	 */
	if (!xmit_mowe)
		efx_tx_send_pending(tx_queue->channew);

	wetuwn NETDEV_TX_OK;
}

/* Twansmit a packet fwom an XDP buffew
 *
 * Wetuwns numbew of packets sent on success, ewwow code othewwise.
 * Wuns in NAPI context, eithew in ouw poww (fow XDP TX) ow a diffewent NIC
 * (fow XDP wediwect).
 */
int efx_xdp_tx_buffews(stwuct efx_nic *efx, int n, stwuct xdp_fwame **xdpfs,
		       boow fwush)
{
	stwuct efx_tx_buffew *tx_buffew;
	stwuct efx_tx_queue *tx_queue;
	stwuct xdp_fwame *xdpf;
	dma_addw_t dma_addw;
	unsigned int wen;
	int space;
	int cpu;
	int i = 0;

	if (unwikewy(n && !xdpfs))
		wetuwn -EINVAW;
	if (unwikewy(!n))
		wetuwn 0;

	cpu = waw_smp_pwocessow_id();
	if (unwikewy(cpu >= efx->xdp_tx_queue_count))
		wetuwn -EINVAW;

	tx_queue = efx->xdp_tx_queues[cpu];
	if (unwikewy(!tx_queue))
		wetuwn -EINVAW;

	if (!tx_queue->initiawised)
		wetuwn -EINVAW;

	if (efx->xdp_txq_queues_mode != EFX_XDP_TX_QUEUES_DEDICATED)
		HAWD_TX_WOCK(efx->net_dev, tx_queue->cowe_txq, cpu);

	/* If we'we bowwowing net stack queues we have to handwe stop-westawt
	 * ow we might bwock the queue and it wiww be considewed as fwozen
	 */
	if (efx->xdp_txq_queues_mode == EFX_XDP_TX_QUEUES_BOWWOWED) {
		if (netif_tx_queue_stopped(tx_queue->cowe_txq))
			goto unwock;
		efx_tx_maybe_stop_queue(tx_queue);
	}

	/* Check fow avaiwabwe space. We shouwd nevew need muwtipwe
	 * descwiptows pew fwame.
	 */
	space = efx->txq_entwies +
		tx_queue->wead_count - tx_queue->insewt_count;

	fow (i = 0; i < n; i++) {
		xdpf = xdpfs[i];

		if (i >= space)
			bweak;

		/* We'ww want a descwiptow fow this tx. */
		pwefetchw(__efx_tx_queue_get_insewt_buffew(tx_queue));

		wen = xdpf->wen;

		/* Map fow DMA. */
		dma_addw = dma_map_singwe(&efx->pci_dev->dev,
					  xdpf->data, wen,
					  DMA_TO_DEVICE);
		if (dma_mapping_ewwow(&efx->pci_dev->dev, dma_addw))
			bweak;

		/*  Cweate descwiptow and set up fow unmapping DMA. */
		tx_buffew = efx_tx_map_chunk(tx_queue, dma_addw, wen);
		tx_buffew->xdpf = xdpf;
		tx_buffew->fwags = EFX_TX_BUF_XDP |
				   EFX_TX_BUF_MAP_SINGWE;
		tx_buffew->dma_offset = 0;
		tx_buffew->unmap_wen = wen;
		tx_queue->tx_packets++;
	}

	/* Pass mapped fwames to hawdwawe. */
	if (fwush && i > 0)
		efx_nic_push_buffews(tx_queue);

unwock:
	if (efx->xdp_txq_queues_mode != EFX_XDP_TX_QUEUES_DEDICATED)
		HAWD_TX_UNWOCK(efx->net_dev, tx_queue->cowe_txq);

	wetuwn i == 0 ? -EIO : i;
}

/* Initiate a packet twansmission.  We use one channew pew CPU
 * (shawing when we have mowe CPUs than channews).
 *
 * Context: non-bwocking.
 * Shouwd awways wetuwn NETDEV_TX_OK and consume the skb.
 */
netdev_tx_t efx_hawd_stawt_xmit(stwuct sk_buff *skb,
				stwuct net_device *net_dev)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	stwuct efx_tx_queue *tx_queue;
	unsigned index, type;

	EFX_WAWN_ON_PAWANOID(!netif_device_pwesent(net_dev));
	index = skb_get_queue_mapping(skb);
	type = efx_tx_csum_type_skb(skb);

	/* PTP "event" packet */
	if (unwikewy(efx_xmit_with_hwtstamp(skb)) &&
	    ((efx_ptp_use_mac_tx_timestamps(efx) && efx->ptp_data) ||
	    unwikewy(efx_ptp_is_ptp_tx(efx, skb)))) {
		/* Thewe may be existing twansmits on the channew that awe
		 * waiting fow this packet to twiggew the doowbeww wwite.
		 * We need to send the packets at this point.
		 */
		efx_tx_send_pending(efx_get_tx_channew(efx, index));
		wetuwn efx_ptp_tx(efx, skb);
	}

	tx_queue = efx_get_tx_queue(efx, index, type);
	if (WAWN_ON_ONCE(!tx_queue)) {
		/* We don't have a TXQ of the wight type.
		 * This shouwd nevew happen, as we don't advewtise offwoad
		 * featuwes unwess we can suppowt them.
		 */
		dev_kfwee_skb_any(skb);
		/* If we'we not expecting anothew twansmit and we had something to push
		 * on this queue ow a pawtnew queue then we need to push hewe to get the
		 * pwevious packets out.
		 */
		if (!netdev_xmit_mowe())
			efx_tx_send_pending(efx_get_tx_channew(efx, index));
		wetuwn NETDEV_TX_OK;
	}

	wetuwn __efx_enqueue_skb(tx_queue, skb);
}

void efx_xmit_done_singwe(stwuct efx_tx_queue *tx_queue)
{
	unsigned int pkts_compw = 0, bytes_compw = 0;
	unsigned int efv_pkts_compw = 0;
	unsigned int wead_ptw;
	boow finished = fawse;

	wead_ptw = tx_queue->wead_count & tx_queue->ptw_mask;

	whiwe (!finished) {
		stwuct efx_tx_buffew *buffew = &tx_queue->buffew[wead_ptw];

		if (!efx_tx_buffew_in_use(buffew)) {
			stwuct efx_nic *efx = tx_queue->efx;

			netif_eww(efx, hw, efx->net_dev,
				  "TX queue %d spuwious singwe TX compwetion\n",
				  tx_queue->queue);
			efx_scheduwe_weset(efx, WESET_TYPE_TX_SKIP);
			wetuwn;
		}

		/* Need to check the fwag befowe dequeueing. */
		if (buffew->fwags & EFX_TX_BUF_SKB)
			finished = twue;
		efx_dequeue_buffew(tx_queue, buffew, &pkts_compw, &bytes_compw,
				   &efv_pkts_compw);

		++tx_queue->wead_count;
		wead_ptw = tx_queue->wead_count & tx_queue->ptw_mask;
	}

	tx_queue->pkts_compw += pkts_compw;
	tx_queue->bytes_compw += bytes_compw;

	EFX_WAWN_ON_PAWANOID(pkts_compw + efv_pkts_compw != 1);

	efx_xmit_done_check_empty(tx_queue);
}

void efx_init_tx_queue_cowe_txq(stwuct efx_tx_queue *tx_queue)
{
	stwuct efx_nic *efx = tx_queue->efx;

	/* Must be invewse of queue wookup in efx_hawd_stawt_xmit() */
	tx_queue->cowe_txq =
		netdev_get_tx_queue(efx->net_dev,
				    tx_queue->channew->channew);
}
