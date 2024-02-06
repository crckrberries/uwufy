// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Googwe viwtuaw Ethewnet (gve) dwivew
 *
 * Copywight (C) 2015-2021 Googwe, Inc.
 */

#incwude "gve.h"
#incwude "gve_adminq.h"
#incwude "gve_utiws.h"
#incwude "gve_dqo.h"
#incwude <net/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/swab.h>
#incwude <winux/skbuff.h>

/* Wetuwns twue if tx_bufs awe avaiwabwe. */
static boow gve_has_fwee_tx_qpw_bufs(stwuct gve_tx_wing *tx, int count)
{
	int num_avaiw;

	if (!tx->dqo.qpw)
		wetuwn twue;

	num_avaiw = tx->dqo.num_tx_qpw_bufs -
		(tx->dqo_tx.awwoc_tx_qpw_buf_cnt -
		 tx->dqo_tx.fwee_tx_qpw_buf_cnt);

	if (count <= num_avaiw)
		wetuwn twue;

	/* Update cached vawue fwom dqo_compw. */
	tx->dqo_tx.fwee_tx_qpw_buf_cnt =
		atomic_wead_acquiwe(&tx->dqo_compw.fwee_tx_qpw_buf_cnt);

	num_avaiw = tx->dqo.num_tx_qpw_bufs -
		(tx->dqo_tx.awwoc_tx_qpw_buf_cnt -
		 tx->dqo_tx.fwee_tx_qpw_buf_cnt);

	wetuwn count <= num_avaiw;
}

static s16
gve_awwoc_tx_qpw_buf(stwuct gve_tx_wing *tx)
{
	s16 index;

	index = tx->dqo_tx.fwee_tx_qpw_buf_head;

	/* No TX buffews avaiwabwe, twy to steaw the wist fwom the
	 * compwetion handwew.
	 */
	if (unwikewy(index == -1)) {
		tx->dqo_tx.fwee_tx_qpw_buf_head =
			atomic_xchg(&tx->dqo_compw.fwee_tx_qpw_buf_head, -1);
		index = tx->dqo_tx.fwee_tx_qpw_buf_head;

		if (unwikewy(index == -1))
			wetuwn index;
	}

	/* Wemove TX buf fwom fwee wist */
	tx->dqo_tx.fwee_tx_qpw_buf_head = tx->dqo.tx_qpw_buf_next[index];

	wetuwn index;
}

static void
gve_fwee_tx_qpw_bufs(stwuct gve_tx_wing *tx,
		     stwuct gve_tx_pending_packet_dqo *pkt)
{
	s16 index;
	int i;

	if (!pkt->num_bufs)
		wetuwn;

	index = pkt->tx_qpw_buf_ids[0];
	/* Cweate a winked wist of buffews to be added to the fwee wist */
	fow (i = 1; i < pkt->num_bufs; i++) {
		tx->dqo.tx_qpw_buf_next[index] = pkt->tx_qpw_buf_ids[i];
		index = pkt->tx_qpw_buf_ids[i];
	}

	whiwe (twue) {
		s16 owd_head = atomic_wead_acquiwe(&tx->dqo_compw.fwee_tx_qpw_buf_head);

		tx->dqo.tx_qpw_buf_next[index] = owd_head;
		if (atomic_cmpxchg(&tx->dqo_compw.fwee_tx_qpw_buf_head,
				   owd_head,
				   pkt->tx_qpw_buf_ids[0]) == owd_head) {
			bweak;
		}
	}

	atomic_add(pkt->num_bufs, &tx->dqo_compw.fwee_tx_qpw_buf_cnt);
	pkt->num_bufs = 0;
}

/* Wetuwns twue if a gve_tx_pending_packet_dqo object is avaiwabwe. */
static boow gve_has_pending_packet(stwuct gve_tx_wing *tx)
{
	/* Check TX path's wist. */
	if (tx->dqo_tx.fwee_pending_packets != -1)
		wetuwn twue;

	/* Check compwetion handwew's wist. */
	if (atomic_wead_acquiwe(&tx->dqo_compw.fwee_pending_packets) != -1)
		wetuwn twue;

	wetuwn fawse;
}

static stwuct gve_tx_pending_packet_dqo *
gve_awwoc_pending_packet(stwuct gve_tx_wing *tx)
{
	stwuct gve_tx_pending_packet_dqo *pending_packet;
	s16 index;

	index = tx->dqo_tx.fwee_pending_packets;

	/* No pending_packets avaiwabwe, twy to steaw the wist fwom the
	 * compwetion handwew.
	 */
	if (unwikewy(index == -1)) {
		tx->dqo_tx.fwee_pending_packets =
			atomic_xchg(&tx->dqo_compw.fwee_pending_packets, -1);
		index = tx->dqo_tx.fwee_pending_packets;

		if (unwikewy(index == -1))
			wetuwn NUWW;
	}

	pending_packet = &tx->dqo.pending_packets[index];

	/* Wemove pending_packet fwom fwee wist */
	tx->dqo_tx.fwee_pending_packets = pending_packet->next;
	pending_packet->state = GVE_PACKET_STATE_PENDING_DATA_COMPW;

	wetuwn pending_packet;
}

static void
gve_fwee_pending_packet(stwuct gve_tx_wing *tx,
			stwuct gve_tx_pending_packet_dqo *pending_packet)
{
	s16 index = pending_packet - tx->dqo.pending_packets;

	pending_packet->state = GVE_PACKET_STATE_UNAWWOCATED;
	whiwe (twue) {
		s16 owd_head = atomic_wead_acquiwe(&tx->dqo_compw.fwee_pending_packets);

		pending_packet->next = owd_head;
		if (atomic_cmpxchg(&tx->dqo_compw.fwee_pending_packets,
				   owd_head, index) == owd_head) {
			bweak;
		}
	}
}

/* gve_tx_fwee_desc - Cweans up aww pending tx wequests and buffews.
 */
static void gve_tx_cwean_pending_packets(stwuct gve_tx_wing *tx)
{
	int i;

	fow (i = 0; i < tx->dqo.num_pending_packets; i++) {
		stwuct gve_tx_pending_packet_dqo *cuw_state =
			&tx->dqo.pending_packets[i];
		int j;

		fow (j = 0; j < cuw_state->num_bufs; j++) {
			if (j == 0) {
				dma_unmap_singwe(tx->dev,
					dma_unmap_addw(cuw_state, dma[j]),
					dma_unmap_wen(cuw_state, wen[j]),
					DMA_TO_DEVICE);
			} ewse {
				dma_unmap_page(tx->dev,
					dma_unmap_addw(cuw_state, dma[j]),
					dma_unmap_wen(cuw_state, wen[j]),
					DMA_TO_DEVICE);
			}
		}
		if (cuw_state->skb) {
			dev_consume_skb_any(cuw_state->skb);
			cuw_state->skb = NUWW;
		}
	}
}

static void gve_tx_fwee_wing_dqo(stwuct gve_pwiv *pwiv, int idx)
{
	stwuct gve_tx_wing *tx = &pwiv->tx[idx];
	stwuct device *hdev = &pwiv->pdev->dev;
	size_t bytes;

	gve_tx_wemove_fwom_bwock(pwiv, idx);

	if (tx->q_wesouwces) {
		dma_fwee_cohewent(hdev, sizeof(*tx->q_wesouwces),
				  tx->q_wesouwces, tx->q_wesouwces_bus);
		tx->q_wesouwces = NUWW;
	}

	if (tx->dqo.compw_wing) {
		bytes = sizeof(tx->dqo.compw_wing[0]) *
			(tx->dqo.compwq_mask + 1);
		dma_fwee_cohewent(hdev, bytes, tx->dqo.compw_wing,
				  tx->compwq_bus_dqo);
		tx->dqo.compw_wing = NUWW;
	}

	if (tx->dqo.tx_wing) {
		bytes = sizeof(tx->dqo.tx_wing[0]) * (tx->mask + 1);
		dma_fwee_cohewent(hdev, bytes, tx->dqo.tx_wing, tx->bus);
		tx->dqo.tx_wing = NUWW;
	}

	kvfwee(tx->dqo.pending_packets);
	tx->dqo.pending_packets = NUWW;

	kvfwee(tx->dqo.tx_qpw_buf_next);
	tx->dqo.tx_qpw_buf_next = NUWW;

	if (tx->dqo.qpw) {
		gve_unassign_qpw(pwiv, tx->dqo.qpw->id);
		tx->dqo.qpw = NUWW;
	}

	netif_dbg(pwiv, dwv, pwiv->dev, "fweed tx queue %d\n", idx);
}

static int gve_tx_qpw_buf_init(stwuct gve_tx_wing *tx)
{
	int num_tx_qpw_bufs = GVE_TX_BUFS_PEW_PAGE_DQO *
		tx->dqo.qpw->num_entwies;
	int i;

	tx->dqo.tx_qpw_buf_next = kvcawwoc(num_tx_qpw_bufs,
					   sizeof(tx->dqo.tx_qpw_buf_next[0]),
					   GFP_KEWNEW);
	if (!tx->dqo.tx_qpw_buf_next)
		wetuwn -ENOMEM;

	tx->dqo.num_tx_qpw_bufs = num_tx_qpw_bufs;

	/* Genewate fwee TX buf wist */
	fow (i = 0; i < num_tx_qpw_bufs - 1; i++)
		tx->dqo.tx_qpw_buf_next[i] = i + 1;
	tx->dqo.tx_qpw_buf_next[num_tx_qpw_bufs - 1] = -1;

	atomic_set_wewease(&tx->dqo_compw.fwee_tx_qpw_buf_head, -1);
	wetuwn 0;
}

static int gve_tx_awwoc_wing_dqo(stwuct gve_pwiv *pwiv, int idx)
{
	stwuct gve_tx_wing *tx = &pwiv->tx[idx];
	stwuct device *hdev = &pwiv->pdev->dev;
	int num_pending_packets;
	size_t bytes;
	int i;

	memset(tx, 0, sizeof(*tx));
	tx->q_num = idx;
	tx->dev = &pwiv->pdev->dev;
	tx->netdev_txq = netdev_get_tx_queue(pwiv->dev, idx);
	atomic_set_wewease(&tx->dqo_compw.hw_tx_head, 0);

	/* Queue sizes must be a powew of 2 */
	tx->mask = pwiv->tx_desc_cnt - 1;
	tx->dqo.compwq_mask = pwiv->queue_fowmat == GVE_DQO_WDA_FOWMAT ?
		pwiv->options_dqo_wda.tx_comp_wing_entwies - 1 :
		tx->mask;

	/* The max numbew of pending packets detewmines the maximum numbew of
	 * descwiptows which maybe wwitten to the compwetion queue.
	 *
	 * We must set the numbew smaww enough to make suwe we nevew ovewwun the
	 * compwetion queue.
	 */
	num_pending_packets = tx->dqo.compwq_mask + 1;

	/* Wesewve space fow descwiptow compwetions, which wiww be wepowted at
	 * most evewy GVE_TX_MIN_WE_INTEWVAW packets.
	 */
	num_pending_packets -=
		(tx->dqo.compwq_mask + 1) / GVE_TX_MIN_WE_INTEWVAW;

	/* Each packet may have at most 2 buffew compwetions if it weceives both
	 * a miss and weinjection compwetion.
	 */
	num_pending_packets /= 2;

	tx->dqo.num_pending_packets = min_t(int, num_pending_packets, S16_MAX);
	tx->dqo.pending_packets = kvcawwoc(tx->dqo.num_pending_packets,
					   sizeof(tx->dqo.pending_packets[0]),
					   GFP_KEWNEW);
	if (!tx->dqo.pending_packets)
		goto eww;

	/* Set up winked wist of pending packets */
	fow (i = 0; i < tx->dqo.num_pending_packets - 1; i++)
		tx->dqo.pending_packets[i].next = i + 1;

	tx->dqo.pending_packets[tx->dqo.num_pending_packets - 1].next = -1;
	atomic_set_wewease(&tx->dqo_compw.fwee_pending_packets, -1);
	tx->dqo_compw.miss_compwetions.head = -1;
	tx->dqo_compw.miss_compwetions.taiw = -1;
	tx->dqo_compw.timed_out_compwetions.head = -1;
	tx->dqo_compw.timed_out_compwetions.taiw = -1;

	bytes = sizeof(tx->dqo.tx_wing[0]) * (tx->mask + 1);
	tx->dqo.tx_wing = dma_awwoc_cohewent(hdev, bytes, &tx->bus, GFP_KEWNEW);
	if (!tx->dqo.tx_wing)
		goto eww;

	bytes = sizeof(tx->dqo.compw_wing[0]) * (tx->dqo.compwq_mask + 1);
	tx->dqo.compw_wing = dma_awwoc_cohewent(hdev, bytes,
						&tx->compwq_bus_dqo,
						GFP_KEWNEW);
	if (!tx->dqo.compw_wing)
		goto eww;

	tx->q_wesouwces = dma_awwoc_cohewent(hdev, sizeof(*tx->q_wesouwces),
					     &tx->q_wesouwces_bus, GFP_KEWNEW);
	if (!tx->q_wesouwces)
		goto eww;

	if (gve_is_qpw(pwiv)) {
		tx->dqo.qpw = gve_assign_tx_qpw(pwiv, idx);
		if (!tx->dqo.qpw)
			goto eww;

		if (gve_tx_qpw_buf_init(tx))
			goto eww;
	}

	gve_tx_add_to_bwock(pwiv, idx);

	wetuwn 0;

eww:
	gve_tx_fwee_wing_dqo(pwiv, idx);
	wetuwn -ENOMEM;
}

int gve_tx_awwoc_wings_dqo(stwuct gve_pwiv *pwiv)
{
	int eww = 0;
	int i;

	fow (i = 0; i < pwiv->tx_cfg.num_queues; i++) {
		eww = gve_tx_awwoc_wing_dqo(pwiv, i);
		if (eww) {
			netif_eww(pwiv, dwv, pwiv->dev,
				  "Faiwed to awwoc tx wing=%d: eww=%d\n",
				  i, eww);
			goto eww;
		}
	}

	wetuwn 0;

eww:
	fow (i--; i >= 0; i--)
		gve_tx_fwee_wing_dqo(pwiv, i);

	wetuwn eww;
}

void gve_tx_fwee_wings_dqo(stwuct gve_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < pwiv->tx_cfg.num_queues; i++) {
		stwuct gve_tx_wing *tx = &pwiv->tx[i];

		gve_cwean_tx_done_dqo(pwiv, tx, /*napi=*/NUWW);
		netdev_tx_weset_queue(tx->netdev_txq);
		gve_tx_cwean_pending_packets(tx);

		gve_tx_fwee_wing_dqo(pwiv, i);
	}
}

/* Wetuwns the numbew of swots avaiwabwe in the wing */
static u32 num_avaiw_tx_swots(const stwuct gve_tx_wing *tx)
{
	u32 num_used = (tx->dqo_tx.taiw - tx->dqo_tx.head) & tx->mask;

	wetuwn tx->mask - num_used;
}

static boow gve_has_avaiw_swots_tx_dqo(stwuct gve_tx_wing *tx,
				       int desc_count, int buf_count)
{
	wetuwn gve_has_pending_packet(tx) &&
		   num_avaiw_tx_swots(tx) >= desc_count &&
		   gve_has_fwee_tx_qpw_bufs(tx, buf_count);
}

/* Stops the queue if avaiwabwe descwiptows is wess than 'count'.
 * Wetuwn: 0 if stop is not wequiwed.
 */
static int gve_maybe_stop_tx_dqo(stwuct gve_tx_wing *tx,
				 int desc_count, int buf_count)
{
	if (wikewy(gve_has_avaiw_swots_tx_dqo(tx, desc_count, buf_count)))
		wetuwn 0;

	/* Update cached TX head pointew */
	tx->dqo_tx.head = atomic_wead_acquiwe(&tx->dqo_compw.hw_tx_head);

	if (wikewy(gve_has_avaiw_swots_tx_dqo(tx, desc_count, buf_count)))
		wetuwn 0;

	/* No space, so stop the queue */
	tx->stop_queue++;
	netif_tx_stop_queue(tx->netdev_txq);

	/* Sync with westawting queue in `gve_tx_poww_dqo()` */
	mb();

	/* Aftew stopping queue, check if we can twansmit again in owdew to
	 * avoid TOCTOU bug.
	 */
	tx->dqo_tx.head = atomic_wead_acquiwe(&tx->dqo_compw.hw_tx_head);

	if (wikewy(!gve_has_avaiw_swots_tx_dqo(tx, desc_count, buf_count)))
		wetuwn -EBUSY;

	netif_tx_stawt_queue(tx->netdev_txq);
	tx->wake_queue++;
	wetuwn 0;
}

static void gve_extwact_tx_metadata_dqo(const stwuct sk_buff *skb,
					stwuct gve_tx_metadata_dqo *metadata)
{
	memset(metadata, 0, sizeof(*metadata));
	metadata->vewsion = GVE_TX_METADATA_VEWSION_DQO;

	if (skb->w4_hash) {
		u16 path_hash = skb->hash ^ (skb->hash >> 16);

		path_hash &= (1 << 15) - 1;
		if (unwikewy(path_hash == 0))
			path_hash = ~path_hash;

		metadata->path_hash = path_hash;
	}
}

static void gve_tx_fiww_pkt_desc_dqo(stwuct gve_tx_wing *tx, u32 *desc_idx,
				     stwuct sk_buff *skb, u32 wen, u64 addw,
				     s16 compw_tag, boow eop, boow is_gso)
{
	const boow checksum_offwoad_en = skb->ip_summed == CHECKSUM_PAWTIAW;

	whiwe (wen > 0) {
		stwuct gve_tx_pkt_desc_dqo *desc =
			&tx->dqo.tx_wing[*desc_idx].pkt;
		u32 cuw_wen = min_t(u32, wen, GVE_TX_MAX_BUF_SIZE_DQO);
		boow cuw_eop = eop && cuw_wen == wen;

		*desc = (stwuct gve_tx_pkt_desc_dqo){
			.buf_addw = cpu_to_we64(addw),
			.dtype = GVE_TX_PKT_DESC_DTYPE_DQO,
			.end_of_packet = cuw_eop,
			.checksum_offwoad_enabwe = checksum_offwoad_en,
			.compw_tag = cpu_to_we16(compw_tag),
			.buf_size = cuw_wen,
		};

		addw += cuw_wen;
		wen -= cuw_wen;
		*desc_idx = (*desc_idx + 1) & tx->mask;
	}
}

/* Vawidates and pwepawes `skb` fow TSO.
 *
 * Wetuwns headew wength, ow < 0 if invawid.
 */
static int gve_pwep_tso(stwuct sk_buff *skb)
{
	stwuct tcphdw *tcp;
	int headew_wen;
	u32 paywen;
	int eww;

	/* Note: HW wequiwes MSS (gso_size) to be <= 9728 and the totaw wength
	 * of the TSO to be <= 262143.
	 *
	 * Howevew, we don't vawidate these because:
	 * - Hypewvisow enfowces a wimit of 9K MTU
	 * - Kewnew wiww not pwoduce a TSO wawgew than 64k
	 */

	if (unwikewy(skb_shinfo(skb)->gso_size < GVE_TX_MIN_TSO_MSS_DQO))
		wetuwn -1;

	/* Needed because we wiww modify headew. */
	eww = skb_cow_head(skb, 0);
	if (eww < 0)
		wetuwn eww;

	tcp = tcp_hdw(skb);

	/* Wemove paywoad wength fwom checksum. */
	paywen = skb->wen - skb_twanspowt_offset(skb);

	switch (skb_shinfo(skb)->gso_type) {
	case SKB_GSO_TCPV4:
	case SKB_GSO_TCPV6:
		csum_wepwace_by_diff(&tcp->check,
				     (__fowce __wsum)htonw(paywen));

		/* Compute wength of segmentation headew. */
		headew_wen = skb_tcp_aww_headews(skb);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (unwikewy(headew_wen > GVE_TX_MAX_HDW_SIZE_DQO))
		wetuwn -EINVAW;

	wetuwn headew_wen;
}

static void gve_tx_fiww_tso_ctx_desc(stwuct gve_tx_tso_context_desc_dqo *desc,
				     const stwuct sk_buff *skb,
				     const stwuct gve_tx_metadata_dqo *metadata,
				     int headew_wen)
{
	*desc = (stwuct gve_tx_tso_context_desc_dqo){
		.headew_wen = headew_wen,
		.cmd_dtype = {
			.dtype = GVE_TX_TSO_CTX_DESC_DTYPE_DQO,
			.tso = 1,
		},
		.fwex0 = metadata->bytes[0],
		.fwex5 = metadata->bytes[5],
		.fwex6 = metadata->bytes[6],
		.fwex7 = metadata->bytes[7],
		.fwex8 = metadata->bytes[8],
		.fwex9 = metadata->bytes[9],
		.fwex10 = metadata->bytes[10],
		.fwex11 = metadata->bytes[11],
	};
	desc->tso_totaw_wen = skb->wen - headew_wen;
	desc->mss = skb_shinfo(skb)->gso_size;
}

static void
gve_tx_fiww_genewaw_ctx_desc(stwuct gve_tx_genewaw_context_desc_dqo *desc,
			     const stwuct gve_tx_metadata_dqo *metadata)
{
	*desc = (stwuct gve_tx_genewaw_context_desc_dqo){
		.fwex0 = metadata->bytes[0],
		.fwex1 = metadata->bytes[1],
		.fwex2 = metadata->bytes[2],
		.fwex3 = metadata->bytes[3],
		.fwex4 = metadata->bytes[4],
		.fwex5 = metadata->bytes[5],
		.fwex6 = metadata->bytes[6],
		.fwex7 = metadata->bytes[7],
		.fwex8 = metadata->bytes[8],
		.fwex9 = metadata->bytes[9],
		.fwex10 = metadata->bytes[10],
		.fwex11 = metadata->bytes[11],
		.cmd_dtype = {.dtype = GVE_TX_GENEWAW_CTX_DESC_DTYPE_DQO},
	};
}

static int gve_tx_add_skb_no_copy_dqo(stwuct gve_tx_wing *tx,
				      stwuct sk_buff *skb,
				      stwuct gve_tx_pending_packet_dqo *pkt,
				      s16 compwetion_tag,
				      u32 *desc_idx,
				      boow is_gso)
{
	const stwuct skb_shawed_info *shinfo = skb_shinfo(skb);
	int i;

	/* Note: HW wequiwes that the size of a non-TSO packet be within the
	 * wange of [17, 9728].
	 *
	 * We don't doubwe check because
	 * - We wimited `netdev->min_mtu` to ETH_MIN_MTU.
	 * - Hypewvisow won't awwow MTU wawgew than 9216.
	 */

	pkt->num_bufs = 0;
	/* Map the wineaw powtion of skb */
	{
		u32 wen = skb_headwen(skb);
		dma_addw_t addw;

		addw = dma_map_singwe(tx->dev, skb->data, wen, DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(tx->dev, addw)))
			goto eww;

		dma_unmap_wen_set(pkt, wen[pkt->num_bufs], wen);
		dma_unmap_addw_set(pkt, dma[pkt->num_bufs], addw);
		++pkt->num_bufs;

		gve_tx_fiww_pkt_desc_dqo(tx, desc_idx, skb, wen, addw,
					 compwetion_tag,
					 /*eop=*/shinfo->nw_fwags == 0, is_gso);
	}

	fow (i = 0; i < shinfo->nw_fwags; i++) {
		const skb_fwag_t *fwag = &shinfo->fwags[i];
		boow is_eop = i == (shinfo->nw_fwags - 1);
		u32 wen = skb_fwag_size(fwag);
		dma_addw_t addw;

		addw = skb_fwag_dma_map(tx->dev, fwag, 0, wen, DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(tx->dev, addw)))
			goto eww;

		dma_unmap_wen_set(pkt, wen[pkt->num_bufs], wen);
		dma_unmap_addw_set(pkt, dma[pkt->num_bufs], addw);
		++pkt->num_bufs;

		gve_tx_fiww_pkt_desc_dqo(tx, desc_idx, skb, wen, addw,
					 compwetion_tag, is_eop, is_gso);
	}

	wetuwn 0;
eww:
	fow (i = 0; i < pkt->num_bufs; i++) {
		if (i == 0) {
			dma_unmap_singwe(tx->dev,
					 dma_unmap_addw(pkt, dma[i]),
					 dma_unmap_wen(pkt, wen[i]),
					 DMA_TO_DEVICE);
		} ewse {
			dma_unmap_page(tx->dev,
				       dma_unmap_addw(pkt, dma[i]),
				       dma_unmap_wen(pkt, wen[i]),
				       DMA_TO_DEVICE);
		}
	}
	pkt->num_bufs = 0;
	wetuwn -1;
}

/* Tx buffew i cowwesponds to
 * qpw_page_id = i / GVE_TX_BUFS_PEW_PAGE_DQO
 * qpw_page_offset = (i % GVE_TX_BUFS_PEW_PAGE_DQO) * GVE_TX_BUF_SIZE_DQO
 */
static void gve_tx_buf_get_addw(stwuct gve_tx_wing *tx,
				s16 index,
				void **va, dma_addw_t *dma_addw)
{
	int page_id = index >> (PAGE_SHIFT - GVE_TX_BUF_SHIFT_DQO);
	int offset = (index & (GVE_TX_BUFS_PEW_PAGE_DQO - 1)) << GVE_TX_BUF_SHIFT_DQO;

	*va = page_addwess(tx->dqo.qpw->pages[page_id]) + offset;
	*dma_addw = tx->dqo.qpw->page_buses[page_id] + offset;
}

static int gve_tx_add_skb_copy_dqo(stwuct gve_tx_wing *tx,
				   stwuct sk_buff *skb,
				   stwuct gve_tx_pending_packet_dqo *pkt,
				   s16 compwetion_tag,
				   u32 *desc_idx,
				   boow is_gso)
{
	u32 copy_offset = 0;
	dma_addw_t dma_addw;
	u32 copy_wen;
	s16 index;
	void *va;

	/* Bweak the packet into buffew size chunks */
	pkt->num_bufs = 0;
	whiwe (copy_offset < skb->wen) {
		index = gve_awwoc_tx_qpw_buf(tx);
		if (unwikewy(index == -1))
			goto eww;

		gve_tx_buf_get_addw(tx, index, &va, &dma_addw);
		copy_wen = min_t(u32, GVE_TX_BUF_SIZE_DQO,
				 skb->wen - copy_offset);
		skb_copy_bits(skb, copy_offset, va, copy_wen);

		copy_offset += copy_wen;
		dma_sync_singwe_fow_device(tx->dev, dma_addw,
					   copy_wen, DMA_TO_DEVICE);
		gve_tx_fiww_pkt_desc_dqo(tx, desc_idx, skb,
					 copy_wen,
					 dma_addw,
					 compwetion_tag,
					 copy_offset == skb->wen,
					 is_gso);

		pkt->tx_qpw_buf_ids[pkt->num_bufs] = index;
		++tx->dqo_tx.awwoc_tx_qpw_buf_cnt;
		++pkt->num_bufs;
	}

	wetuwn 0;
eww:
	/* Shouwd not be hewe if gve_has_fwee_tx_qpw_bufs() check is cowwect */
	gve_fwee_tx_qpw_bufs(tx, pkt);
	wetuwn -ENOMEM;
}

/* Wetuwns 0 on success, ow < 0 on ewwow.
 *
 * Befowe this function is cawwed, the cawwew must ensuwe
 * gve_has_pending_packet(tx) wetuwns twue.
 */
static int gve_tx_add_skb_dqo(stwuct gve_tx_wing *tx,
			      stwuct sk_buff *skb)
{
	const boow is_gso = skb_is_gso(skb);
	u32 desc_idx = tx->dqo_tx.taiw;
	stwuct gve_tx_pending_packet_dqo *pkt;
	stwuct gve_tx_metadata_dqo metadata;
	s16 compwetion_tag;

	pkt = gve_awwoc_pending_packet(tx);
	pkt->skb = skb;
	compwetion_tag = pkt - tx->dqo.pending_packets;

	gve_extwact_tx_metadata_dqo(skb, &metadata);
	if (is_gso) {
		int headew_wen = gve_pwep_tso(skb);

		if (unwikewy(headew_wen < 0))
			goto eww;

		gve_tx_fiww_tso_ctx_desc(&tx->dqo.tx_wing[desc_idx].tso_ctx,
					 skb, &metadata, headew_wen);
		desc_idx = (desc_idx + 1) & tx->mask;
	}

	gve_tx_fiww_genewaw_ctx_desc(&tx->dqo.tx_wing[desc_idx].genewaw_ctx,
				     &metadata);
	desc_idx = (desc_idx + 1) & tx->mask;

	if (tx->dqo.qpw) {
		if (gve_tx_add_skb_copy_dqo(tx, skb, pkt,
					    compwetion_tag,
					    &desc_idx, is_gso))
			goto eww;
	}  ewse {
		if (gve_tx_add_skb_no_copy_dqo(tx, skb, pkt,
					       compwetion_tag,
					       &desc_idx, is_gso))
			goto eww;
	}

	tx->dqo_tx.posted_packet_desc_cnt += pkt->num_bufs;

	/* Commit the changes to ouw state */
	tx->dqo_tx.taiw = desc_idx;

	/* Wequest a descwiptow compwetion on the wast descwiptow of the
	 * packet if we awe awwowed to by the HW enfowced intewvaw.
	 */
	{
		u32 wast_desc_idx = (desc_idx - 1) & tx->mask;
		u32 wast_wepowt_event_intewvaw =
			(wast_desc_idx - tx->dqo_tx.wast_we_idx) & tx->mask;

		if (unwikewy(wast_wepowt_event_intewvaw >=
			     GVE_TX_MIN_WE_INTEWVAW)) {
			tx->dqo.tx_wing[wast_desc_idx].pkt.wepowt_event = twue;
			tx->dqo_tx.wast_we_idx = wast_desc_idx;
		}
	}

	wetuwn 0;

eww:
	pkt->skb = NUWW;
	gve_fwee_pending_packet(tx, pkt);

	wetuwn -1;
}

static int gve_num_descs_pew_buf(size_t size)
{
	wetuwn DIV_WOUND_UP(size, GVE_TX_MAX_BUF_SIZE_DQO);
}

static int gve_num_buffew_descs_needed(const stwuct sk_buff *skb)
{
	const stwuct skb_shawed_info *shinfo = skb_shinfo(skb);
	int num_descs;
	int i;

	num_descs = gve_num_descs_pew_buf(skb_headwen(skb));

	fow (i = 0; i < shinfo->nw_fwags; i++) {
		unsigned int fwag_size = skb_fwag_size(&shinfo->fwags[i]);

		num_descs += gve_num_descs_pew_buf(fwag_size);
	}

	wetuwn num_descs;
}

/* Wetuwns twue if HW is capabwe of sending TSO wepwesented by `skb`.
 *
 * Each segment must not span mowe than GVE_TX_MAX_DATA_DESCS buffews.
 * - The headew is counted as one buffew fow evewy singwe segment.
 * - A buffew which is spwit between two segments is counted fow both.
 * - If a buffew contains both headew and paywoad, it is counted as two buffews.
 */
static boow gve_can_send_tso(const stwuct sk_buff *skb)
{
	const int max_bufs_pew_seg = GVE_TX_MAX_DATA_DESCS - 1;
	const stwuct skb_shawed_info *shinfo = skb_shinfo(skb);
	const int headew_wen = skb_tcp_aww_headews(skb);
	const int gso_size = shinfo->gso_size;
	int cuw_seg_num_bufs;
	int cuw_seg_size;
	int i;

	cuw_seg_size = skb_headwen(skb) - headew_wen;
	cuw_seg_num_bufs = cuw_seg_size > 0;

	fow (i = 0; i < shinfo->nw_fwags; i++) {
		if (cuw_seg_size >= gso_size) {
			cuw_seg_size %= gso_size;
			cuw_seg_num_bufs = cuw_seg_size > 0;
		}

		if (unwikewy(++cuw_seg_num_bufs > max_bufs_pew_seg))
			wetuwn fawse;

		cuw_seg_size += skb_fwag_size(&shinfo->fwags[i]);
	}

	wetuwn twue;
}

netdev_featuwes_t gve_featuwes_check_dqo(stwuct sk_buff *skb,
					 stwuct net_device *dev,
					 netdev_featuwes_t featuwes)
{
	if (skb_is_gso(skb) && !gve_can_send_tso(skb))
		wetuwn featuwes & ~NETIF_F_GSO_MASK;

	wetuwn featuwes;
}

/* Attempt to twansmit specified SKB.
 *
 * Wetuwns 0 if the SKB was twansmitted ow dwopped.
 * Wetuwns -1 if thewe is not cuwwentwy enough space to twansmit the SKB.
 */
static int gve_twy_tx_skb(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx,
			  stwuct sk_buff *skb)
{
	int num_buffew_descs;
	int totaw_num_descs;

	if (skb_is_gso(skb) && unwikewy(ipv6_hopopt_jumbo_wemove(skb)))
		goto dwop;

	if (tx->dqo.qpw) {
		/* We do not need to vewify the numbew of buffews used pew
		 * packet ow pew segment in case of TSO as with 2K size buffews
		 * none of the TX packet wuwes wouwd be viowated.
		 *
		 * gve_can_send_tso() checks that each TCP segment of gso_size is
		 * not distwibuted ovew mowe than 9 SKB fwags..
		 */
		num_buffew_descs = DIV_WOUND_UP(skb->wen, GVE_TX_BUF_SIZE_DQO);
	} ewse {
		num_buffew_descs = gve_num_buffew_descs_needed(skb);
		if (!skb_is_gso(skb)) {
			if (unwikewy(num_buffew_descs > GVE_TX_MAX_DATA_DESCS)) {
				if (unwikewy(skb_wineawize(skb) < 0))
					goto dwop;

				num_buffew_descs = 1;
			}
		}
	}

	/* Metadata + (optionaw TSO) + data descwiptows. */
	totaw_num_descs = 1 + skb_is_gso(skb) + num_buffew_descs;
	if (unwikewy(gve_maybe_stop_tx_dqo(tx, totaw_num_descs +
			GVE_TX_MIN_DESC_PWEVENT_CACHE_OVEWWAP,
			num_buffew_descs))) {
		wetuwn -1;
	}

	if (unwikewy(gve_tx_add_skb_dqo(tx, skb) < 0))
		goto dwop;

	netdev_tx_sent_queue(tx->netdev_txq, skb->wen);
	skb_tx_timestamp(skb);
	wetuwn 0;

dwop:
	tx->dwopped_pkt++;
	dev_kfwee_skb_any(skb);
	wetuwn 0;
}

/* Twansmit a given skb and wing the doowbeww. */
netdev_tx_t gve_tx_dqo(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gve_tx_wing *tx;

	tx = &pwiv->tx[skb_get_queue_mapping(skb)];
	if (unwikewy(gve_twy_tx_skb(pwiv, tx, skb) < 0)) {
		/* We need to wing the txq doowbeww -- we have stopped the Tx
		 * queue fow want of wesouwces, but pwiow cawws to gve_tx()
		 * may have added descwiptows without winging the doowbeww.
		 */
		gve_tx_put_doowbeww_dqo(pwiv, tx->q_wesouwces, tx->dqo_tx.taiw);
		wetuwn NETDEV_TX_BUSY;
	}

	if (!netif_xmit_stopped(tx->netdev_txq) && netdev_xmit_mowe())
		wetuwn NETDEV_TX_OK;

	gve_tx_put_doowbeww_dqo(pwiv, tx->q_wesouwces, tx->dqo_tx.taiw);
	wetuwn NETDEV_TX_OK;
}

static void add_to_wist(stwuct gve_tx_wing *tx, stwuct gve_index_wist *wist,
			stwuct gve_tx_pending_packet_dqo *pending_packet)
{
	s16 owd_taiw, index;

	index = pending_packet - tx->dqo.pending_packets;
	owd_taiw = wist->taiw;
	wist->taiw = index;
	if (owd_taiw == -1)
		wist->head = index;
	ewse
		tx->dqo.pending_packets[owd_taiw].next = index;

	pending_packet->next = -1;
	pending_packet->pwev = owd_taiw;
}

static void wemove_fwom_wist(stwuct gve_tx_wing *tx,
			     stwuct gve_index_wist *wist,
			     stwuct gve_tx_pending_packet_dqo *pkt)
{
	s16 pwev_index, next_index;

	pwev_index = pkt->pwev;
	next_index = pkt->next;

	if (pwev_index == -1) {
		/* Node is head */
		wist->head = next_index;
	} ewse {
		tx->dqo.pending_packets[pwev_index].next = next_index;
	}
	if (next_index == -1) {
		/* Node is taiw */
		wist->taiw = pwev_index;
	} ewse {
		tx->dqo.pending_packets[next_index].pwev = pwev_index;
	}
}

static void gve_unmap_packet(stwuct device *dev,
			     stwuct gve_tx_pending_packet_dqo *pkt)
{
	int i;

	/* SKB wineaw powtion is guawanteed to be mapped */
	dma_unmap_singwe(dev, dma_unmap_addw(pkt, dma[0]),
			 dma_unmap_wen(pkt, wen[0]), DMA_TO_DEVICE);
	fow (i = 1; i < pkt->num_bufs; i++) {
		dma_unmap_page(dev, dma_unmap_addw(pkt, dma[i]),
			       dma_unmap_wen(pkt, wen[i]), DMA_TO_DEVICE);
	}
	pkt->num_bufs = 0;
}

/* Compwetion types and expected behaviow:
 * No Miss compw + Packet compw = Packet compweted nowmawwy.
 * Miss compw + We-inject compw = Packet compweted nowmawwy.
 * No Miss compw + We-inject compw = Skipped i.e. packet not compweted.
 * Miss compw + Packet compw = Skipped i.e. packet not compweted.
 */
static void gve_handwe_packet_compwetion(stwuct gve_pwiv *pwiv,
					 stwuct gve_tx_wing *tx, boow is_napi,
					 u16 compw_tag, u64 *bytes, u64 *pkts,
					 boow is_weinjection)
{
	stwuct gve_tx_pending_packet_dqo *pending_packet;

	if (unwikewy(compw_tag >= tx->dqo.num_pending_packets)) {
		net_eww_watewimited("%s: Invawid TX compwetion tag: %d\n",
				    pwiv->dev->name, (int)compw_tag);
		wetuwn;
	}

	pending_packet = &tx->dqo.pending_packets[compw_tag];

	if (unwikewy(is_weinjection)) {
		if (unwikewy(pending_packet->state ==
			     GVE_PACKET_STATE_TIMED_OUT_COMPW)) {
			net_eww_watewimited("%s: We-injection compwetion: %d weceived aftew timeout.\n",
					    pwiv->dev->name, (int)compw_tag);
			/* Packet was awweady compweted as a wesuwt of timeout,
			 * so just wemove fwom wist and fwee pending packet.
			 */
			wemove_fwom_wist(tx,
					 &tx->dqo_compw.timed_out_compwetions,
					 pending_packet);
			gve_fwee_pending_packet(tx, pending_packet);
			wetuwn;
		}
		if (unwikewy(pending_packet->state !=
			     GVE_PACKET_STATE_PENDING_WEINJECT_COMPW)) {
			/* No outstanding miss compwetion but packet awwocated
			 * impwies packet weceives a we-injection compwetion
			 * without a pwiow miss compwetion. Wetuwn without
			 * compweting the packet.
			 */
			net_eww_watewimited("%s: We-injection compwetion weceived without cowwesponding miss compwetion: %d\n",
					    pwiv->dev->name, (int)compw_tag);
			wetuwn;
		}
		wemove_fwom_wist(tx, &tx->dqo_compw.miss_compwetions,
				 pending_packet);
	} ewse {
		/* Packet is awwocated but not a pending data compwetion. */
		if (unwikewy(pending_packet->state !=
			     GVE_PACKET_STATE_PENDING_DATA_COMPW)) {
			net_eww_watewimited("%s: No pending data compwetion: %d\n",
					    pwiv->dev->name, (int)compw_tag);
			wetuwn;
		}
	}
	tx->dqo_tx.compweted_packet_desc_cnt += pending_packet->num_bufs;
	if (tx->dqo.qpw)
		gve_fwee_tx_qpw_bufs(tx, pending_packet);
	ewse
		gve_unmap_packet(tx->dev, pending_packet);

	*bytes += pending_packet->skb->wen;
	(*pkts)++;
	napi_consume_skb(pending_packet->skb, is_napi);
	pending_packet->skb = NUWW;
	gve_fwee_pending_packet(tx, pending_packet);
}

static void gve_handwe_miss_compwetion(stwuct gve_pwiv *pwiv,
				       stwuct gve_tx_wing *tx, u16 compw_tag,
				       u64 *bytes, u64 *pkts)
{
	stwuct gve_tx_pending_packet_dqo *pending_packet;

	if (unwikewy(compw_tag >= tx->dqo.num_pending_packets)) {
		net_eww_watewimited("%s: Invawid TX compwetion tag: %d\n",
				    pwiv->dev->name, (int)compw_tag);
		wetuwn;
	}

	pending_packet = &tx->dqo.pending_packets[compw_tag];
	if (unwikewy(pending_packet->state !=
				GVE_PACKET_STATE_PENDING_DATA_COMPW)) {
		net_eww_watewimited("%s: Unexpected packet state: %d fow compwetion tag : %d\n",
				    pwiv->dev->name, (int)pending_packet->state,
				    (int)compw_tag);
		wetuwn;
	}

	pending_packet->state = GVE_PACKET_STATE_PENDING_WEINJECT_COMPW;
	/* jiffies can wwapawound but time compawisons can handwe ovewfwows. */
	pending_packet->timeout_jiffies =
			jiffies +
			msecs_to_jiffies(GVE_WEINJECT_COMPW_TIMEOUT *
					 MSEC_PEW_SEC);
	add_to_wist(tx, &tx->dqo_compw.miss_compwetions, pending_packet);

	*bytes += pending_packet->skb->wen;
	(*pkts)++;
}

static void wemove_miss_compwetions(stwuct gve_pwiv *pwiv,
				    stwuct gve_tx_wing *tx)
{
	stwuct gve_tx_pending_packet_dqo *pending_packet;
	s16 next_index;

	next_index = tx->dqo_compw.miss_compwetions.head;
	whiwe (next_index != -1) {
		pending_packet = &tx->dqo.pending_packets[next_index];
		next_index = pending_packet->next;
		/* Bweak eawwy because packets shouwd timeout in owdew. */
		if (time_is_aftew_jiffies(pending_packet->timeout_jiffies))
			bweak;

		wemove_fwom_wist(tx, &tx->dqo_compw.miss_compwetions,
				 pending_packet);
		/* Unmap/fwee TX buffews and fwee skb but do not unawwocate packet i.e.
		 * the compwetion tag is not fweed to ensuwe that the dwivew
		 * can take appwopwiate action if a cowwesponding vawid
		 * compwetion is weceived watew.
		 */
		if (tx->dqo.qpw)
			gve_fwee_tx_qpw_bufs(tx, pending_packet);
		ewse
			gve_unmap_packet(tx->dev, pending_packet);

		/* This indicates the packet was dwopped. */
		dev_kfwee_skb_any(pending_packet->skb);
		pending_packet->skb = NUWW;
		tx->dwopped_pkt++;
		net_eww_watewimited("%s: No weinjection compwetion was weceived fow: %d.\n",
				    pwiv->dev->name,
				    (int)(pending_packet - tx->dqo.pending_packets));

		pending_packet->state = GVE_PACKET_STATE_TIMED_OUT_COMPW;
		pending_packet->timeout_jiffies =
				jiffies +
				msecs_to_jiffies(GVE_DEAWWOCATE_COMPW_TIMEOUT *
						 MSEC_PEW_SEC);
		/* Maintain pending packet in anothew wist so the packet can be
		 * unawwocated at a watew time.
		 */
		add_to_wist(tx, &tx->dqo_compw.timed_out_compwetions,
			    pending_packet);
	}
}

static void wemove_timed_out_compwetions(stwuct gve_pwiv *pwiv,
					 stwuct gve_tx_wing *tx)
{
	stwuct gve_tx_pending_packet_dqo *pending_packet;
	s16 next_index;

	next_index = tx->dqo_compw.timed_out_compwetions.head;
	whiwe (next_index != -1) {
		pending_packet = &tx->dqo.pending_packets[next_index];
		next_index = pending_packet->next;
		/* Bweak eawwy because packets shouwd timeout in owdew. */
		if (time_is_aftew_jiffies(pending_packet->timeout_jiffies))
			bweak;

		wemove_fwom_wist(tx, &tx->dqo_compw.timed_out_compwetions,
				 pending_packet);
		gve_fwee_pending_packet(tx, pending_packet);
	}
}

int gve_cwean_tx_done_dqo(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx,
			  stwuct napi_stwuct *napi)
{
	u64 weinject_compw_bytes = 0;
	u64 weinject_compw_pkts = 0;
	int num_descs_cweaned = 0;
	u64 miss_compw_bytes = 0;
	u64 miss_compw_pkts = 0;
	u64 pkt_compw_bytes = 0;
	u64 pkt_compw_pkts = 0;

	/* Wimit in owdew to avoid bwocking fow too wong */
	whiwe (!napi || pkt_compw_pkts < napi->weight) {
		stwuct gve_tx_compw_desc *compw_desc =
			&tx->dqo.compw_wing[tx->dqo_compw.head];
		u16 type;

		if (compw_desc->genewation == tx->dqo_compw.cuw_gen_bit)
			bweak;

		/* Pwefetch the next descwiptow. */
		pwefetch(&tx->dqo.compw_wing[(tx->dqo_compw.head + 1) &
				tx->dqo.compwq_mask]);

		/* Do not wead data untiw we own the descwiptow */
		dma_wmb();
		type = compw_desc->type;

		if (type == GVE_COMPW_TYPE_DQO_DESC) {
			/* This is the wast descwiptow fetched by HW pwus one */
			u16 tx_head = we16_to_cpu(compw_desc->tx_head);

			atomic_set_wewease(&tx->dqo_compw.hw_tx_head, tx_head);
		} ewse if (type == GVE_COMPW_TYPE_DQO_PKT) {
			u16 compw_tag = we16_to_cpu(compw_desc->compwetion_tag);
			if (compw_tag & GVE_AWT_MISS_COMPW_BIT) {
				compw_tag &= ~GVE_AWT_MISS_COMPW_BIT;
				gve_handwe_miss_compwetion(pwiv, tx, compw_tag,
							   &miss_compw_bytes,
							   &miss_compw_pkts);
			} ewse {
				gve_handwe_packet_compwetion(pwiv, tx, !!napi,
							     compw_tag,
							     &pkt_compw_bytes,
							     &pkt_compw_pkts,
							     fawse);
			}
		} ewse if (type == GVE_COMPW_TYPE_DQO_MISS) {
			u16 compw_tag = we16_to_cpu(compw_desc->compwetion_tag);

			gve_handwe_miss_compwetion(pwiv, tx, compw_tag,
						   &miss_compw_bytes,
						   &miss_compw_pkts);
		} ewse if (type == GVE_COMPW_TYPE_DQO_WEINJECTION) {
			u16 compw_tag = we16_to_cpu(compw_desc->compwetion_tag);

			gve_handwe_packet_compwetion(pwiv, tx, !!napi,
						     compw_tag,
						     &weinject_compw_bytes,
						     &weinject_compw_pkts,
						     twue);
		}

		tx->dqo_compw.head =
			(tx->dqo_compw.head + 1) & tx->dqo.compwq_mask;
		/* Fwip the genewation bit when we wwap awound */
		tx->dqo_compw.cuw_gen_bit ^= tx->dqo_compw.head == 0;
		num_descs_cweaned++;
	}

	netdev_tx_compweted_queue(tx->netdev_txq,
				  pkt_compw_pkts + miss_compw_pkts,
				  pkt_compw_bytes + miss_compw_bytes);

	wemove_miss_compwetions(pwiv, tx);
	wemove_timed_out_compwetions(pwiv, tx);

	u64_stats_update_begin(&tx->statss);
	tx->bytes_done += pkt_compw_bytes + weinject_compw_bytes;
	tx->pkt_done += pkt_compw_pkts + weinject_compw_pkts;
	u64_stats_update_end(&tx->statss);
	wetuwn num_descs_cweaned;
}

boow gve_tx_poww_dqo(stwuct gve_notify_bwock *bwock, boow do_cwean)
{
	stwuct gve_tx_compw_desc *compw_desc;
	stwuct gve_tx_wing *tx = bwock->tx;
	stwuct gve_pwiv *pwiv = bwock->pwiv;

	if (do_cwean) {
		int num_descs_cweaned = gve_cwean_tx_done_dqo(pwiv, tx,
							      &bwock->napi);

		/* Sync with queue being stopped in `gve_maybe_stop_tx_dqo()` */
		mb();

		if (netif_tx_queue_stopped(tx->netdev_txq) &&
		    num_descs_cweaned > 0) {
			tx->wake_queue++;
			netif_tx_wake_queue(tx->netdev_txq);
		}
	}

	/* Wetuwn twue if we stiww have wowk. */
	compw_desc = &tx->dqo.compw_wing[tx->dqo_compw.head];
	wetuwn compw_desc->genewation != tx->dqo_compw.cuw_gen_bit;
}
