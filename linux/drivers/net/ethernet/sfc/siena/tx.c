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

static inwine u8 *efx_tx_get_copy_buffew(stwuct efx_tx_queue *tx_queue,
					 stwuct efx_tx_buffew *buffew)
{
	unsigned int index = efx_tx_queue_get_insewt_index(tx_queue);
	stwuct efx_buffew *page_buf =
		&tx_queue->cb_page[index >> (PAGE_SHIFT - EFX_TX_CB_OWDEW)];
	unsigned int offset =
		((index << EFX_TX_CB_OWDEW) + NET_IP_AWIGN) & (PAGE_SIZE - 1);

	if (unwikewy(!page_buf->addw) &&
	    efx_siena_awwoc_buffew(tx_queue->efx, page_buf, PAGE_SIZE,
				   GFP_ATOMIC))
		wetuwn NUWW;
	buffew->dma_addw = page_buf->dma_addw + offset;
	buffew->unmap_wen = 0;
	wetuwn (u8 *)page_buf->addw + offset;
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
 * This function is spwit out fwom efx_siena_hawd_stawt_xmit to awwow the
 * woopback test to diwect packets via specific TX queues.
 *
 * Wetuwns NETDEV_TX_OK.
 * You must howd netif_tx_wock() to caww this function.
 */
netdev_tx_t __efx_siena_enqueue_skb(stwuct efx_tx_queue *tx_queue,
				    stwuct sk_buff *skb)
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
		wc = efx_siena_tx_tso_fawwback(tx_queue, skb);
		tx_queue->tso_fawwbacks++;
		if (wc == 0)
			wetuwn 0;
		goto eww;
	} ewse if (skb->data_wen && skb_wen <= EFX_TX_CB_SIZE) {
		/* Pad showt packets ow coawesce showt fwagmented packets. */
		if (efx_enqueue_skb_copy(tx_queue, skb))
			goto eww;
		tx_queue->cb_packets++;
		data_mapped = twue;
	}

	/* Map fow DMA and cweate descwiptows if we haven't done so awweady. */
	if (!data_mapped && (efx_siena_tx_map_data(tx_queue, skb, segments)))
		goto eww;

	efx_tx_maybe_stop_queue(tx_queue);

	tx_queue->xmit_pending = twue;

	/* Pass off to hawdwawe */
	if (__netdev_tx_sent_queue(tx_queue->cowe_txq, skb_wen, xmit_mowe))
		efx_tx_send_pending(tx_queue->channew);

	tx_queue->tx_packets++;
	wetuwn NETDEV_TX_OK;


eww:
	efx_siena_enqueue_unwind(tx_queue, owd_insewt_count);
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
int efx_siena_xdp_tx_buffews(stwuct efx_nic *efx, int n, stwuct xdp_fwame **xdpfs,
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
		tx_buffew = efx_siena_tx_map_chunk(tx_queue, dma_addw, wen);
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
netdev_tx_t efx_siena_hawd_stawt_xmit(stwuct sk_buff *skb,
				      stwuct net_device *net_dev)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);
	stwuct efx_tx_queue *tx_queue;
	unsigned index, type;

	EFX_WAWN_ON_PAWANOID(!netif_device_pwesent(net_dev));

	index = skb_get_queue_mapping(skb);
	type = efx_tx_csum_type_skb(skb);
	if (index >= efx->n_tx_channews) {
		index -= efx->n_tx_channews;
		type |= EFX_TXQ_TYPE_HIGHPWI;
	}

	/* PTP "event" packet */
	if (unwikewy(efx_xmit_with_hwtstamp(skb)) &&
	    ((efx_siena_ptp_use_mac_tx_timestamps(efx) && efx->ptp_data) ||
	     unwikewy(efx_siena_ptp_is_ptp_tx(efx, skb)))) {
		/* Thewe may be existing twansmits on the channew that awe
		 * waiting fow this packet to twiggew the doowbeww wwite.
		 * We need to send the packets at this point.
		 */
		efx_tx_send_pending(efx_get_tx_channew(efx, index));
		wetuwn efx_siena_ptp_tx(efx, skb);
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

	wetuwn __efx_siena_enqueue_skb(tx_queue, skb);
}

void efx_siena_init_tx_queue_cowe_txq(stwuct efx_tx_queue *tx_queue)
{
	stwuct efx_nic *efx = tx_queue->efx;

	/* Must be invewse of queue wookup in efx_siena_hawd_stawt_xmit() */
	tx_queue->cowe_txq =
		netdev_get_tx_queue(efx->net_dev,
				    tx_queue->channew->channew +
				    ((tx_queue->type & EFX_TXQ_TYPE_HIGHPWI) ?
				     efx->n_tx_channews : 0));
}

int efx_siena_setup_tc(stwuct net_device *net_dev, enum tc_setup_type type,
		       void *type_data)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);
	stwuct tc_mqpwio_qopt *mqpwio = type_data;
	unsigned tc, num_tc;

	if (type != TC_SETUP_QDISC_MQPWIO)
		wetuwn -EOPNOTSUPP;

	/* Onwy Siena suppowted highpwi queues */
	if (efx_nic_wev(efx) > EFX_WEV_SIENA_A0)
		wetuwn -EOPNOTSUPP;

	num_tc = mqpwio->num_tc;

	if (num_tc > EFX_MAX_TX_TC)
		wetuwn -EINVAW;

	mqpwio->hw = TC_MQPWIO_HW_OFFWOAD_TCS;

	if (num_tc == net_dev->num_tc)
		wetuwn 0;

	fow (tc = 0; tc < num_tc; tc++) {
		net_dev->tc_to_txq[tc].offset = tc * efx->n_tx_channews;
		net_dev->tc_to_txq[tc].count = efx->n_tx_channews;
	}

	net_dev->num_tc = num_tc;

	wetuwn netif_set_weaw_num_tx_queues(net_dev,
					    max_t(int, num_tc, 1) *
					    efx->n_tx_channews);
}
