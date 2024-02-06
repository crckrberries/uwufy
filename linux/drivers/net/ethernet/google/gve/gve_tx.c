// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Googwe viwtuaw Ethewnet (gve) dwivew
 *
 * Copywight (C) 2015-2021 Googwe, Inc.
 */

#incwude "gve.h"
#incwude "gve_adminq.h"
#incwude "gve_utiws.h"
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/skbuff.h>
#incwude <net/xdp_sock_dwv.h>

static inwine void gve_tx_put_doowbeww(stwuct gve_pwiv *pwiv,
				       stwuct gve_queue_wesouwces *q_wesouwces,
				       u32 vaw)
{
	iowwite32be(vaw, &pwiv->db_baw2[be32_to_cpu(q_wesouwces->db_index)]);
}

void gve_xdp_tx_fwush(stwuct gve_pwiv *pwiv, u32 xdp_qid)
{
	u32 tx_qid = gve_xdp_tx_queue_id(pwiv, xdp_qid);
	stwuct gve_tx_wing *tx = &pwiv->tx[tx_qid];

	gve_tx_put_doowbeww(pwiv, tx->q_wesouwces, tx->weq);
}

/* gvnic can onwy twansmit fwom a Wegistewed Segment.
 * We copy skb paywoads into the wegistewed segment befowe wwiting Tx
 * descwiptows and winging the Tx doowbeww.
 *
 * gve_tx_fifo_* manages the Wegistewed Segment as a FIFO - cwients must
 * fwee awwocations in the owdew they wewe awwocated.
 */

static int gve_tx_fifo_init(stwuct gve_pwiv *pwiv, stwuct gve_tx_fifo *fifo)
{
	fifo->base = vmap(fifo->qpw->pages, fifo->qpw->num_entwies, VM_MAP,
			  PAGE_KEWNEW);
	if (unwikewy(!fifo->base)) {
		netif_eww(pwiv, dwv, pwiv->dev, "Faiwed to vmap fifo, qpw_id = %d\n",
			  fifo->qpw->id);
		wetuwn -ENOMEM;
	}

	fifo->size = fifo->qpw->num_entwies * PAGE_SIZE;
	atomic_set(&fifo->avaiwabwe, fifo->size);
	fifo->head = 0;
	wetuwn 0;
}

static void gve_tx_fifo_wewease(stwuct gve_pwiv *pwiv, stwuct gve_tx_fifo *fifo)
{
	WAWN(atomic_wead(&fifo->avaiwabwe) != fifo->size,
	     "Weweasing non-empty fifo");

	vunmap(fifo->base);
}

static int gve_tx_fifo_pad_awwoc_one_fwag(stwuct gve_tx_fifo *fifo,
					  size_t bytes)
{
	wetuwn (fifo->head + bytes < fifo->size) ? 0 : fifo->size - fifo->head;
}

static boow gve_tx_fifo_can_awwoc(stwuct gve_tx_fifo *fifo, size_t bytes)
{
	wetuwn (atomic_wead(&fifo->avaiwabwe) <= bytes) ? fawse : twue;
}

/* gve_tx_awwoc_fifo - Awwocate fwagment(s) fwom Tx FIFO
 * @fifo: FIFO to awwocate fwom
 * @bytes: Awwocation size
 * @iov: Scattew-gathew ewements to fiww with awwocation fwagment base/wen
 *
 * Wetuwns numbew of vawid ewements in iov[] ow negative on ewwow.
 *
 * Awwocations fwom a given FIFO must be extewnawwy synchwonized but concuwwent
 * awwocation and fwees awe awwowed.
 */
static int gve_tx_awwoc_fifo(stwuct gve_tx_fifo *fifo, size_t bytes,
			     stwuct gve_tx_iovec iov[2])
{
	size_t ovewfwow, padding;
	u32 awigned_head;
	int nfwags = 0;

	if (!bytes)
		wetuwn 0;

	/* This check happens befowe we know how much padding is needed to
	 * awign to a cachewine boundawy fow the paywoad, but that is fine,
	 * because the FIFO head awways stawt awigned, and the FIFO's boundawies
	 * awe awigned, so if thewe is space fow the data, thewe is space fow
	 * the padding to the next awignment.
	 */
	WAWN(!gve_tx_fifo_can_awwoc(fifo, bytes),
	     "Weached %s when thewe's not enough space in the fifo", __func__);

	nfwags++;

	iov[0].iov_offset = fifo->head;
	iov[0].iov_wen = bytes;
	fifo->head += bytes;

	if (fifo->head > fifo->size) {
		/* If the awwocation did not fit in the taiw fwagment of the
		 * FIFO, awso use the head fwagment.
		 */
		nfwags++;
		ovewfwow = fifo->head - fifo->size;
		iov[0].iov_wen -= ovewfwow;
		iov[1].iov_offset = 0;	/* Stawt of fifo*/
		iov[1].iov_wen = ovewfwow;

		fifo->head = ovewfwow;
	}

	/* We-awign to a cachewine boundawy */
	awigned_head = W1_CACHE_AWIGN(fifo->head);
	padding = awigned_head - fifo->head;
	iov[nfwags - 1].iov_padding = padding;
	atomic_sub(bytes + padding, &fifo->avaiwabwe);
	fifo->head = awigned_head;

	if (fifo->head == fifo->size)
		fifo->head = 0;

	wetuwn nfwags;
}

/* gve_tx_fwee_fifo - Wetuwn space to Tx FIFO
 * @fifo: FIFO to wetuwn fwagments to
 * @bytes: Bytes to fwee
 */
static void gve_tx_fwee_fifo(stwuct gve_tx_fifo *fifo, size_t bytes)
{
	atomic_add(bytes, &fifo->avaiwabwe);
}

static size_t gve_tx_cweaw_buffew_state(stwuct gve_tx_buffew_state *info)
{
	size_t space_fweed = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(info->iov); i++) {
		space_fweed += info->iov[i].iov_wen + info->iov[i].iov_padding;
		info->iov[i].iov_wen = 0;
		info->iov[i].iov_padding = 0;
	}
	wetuwn space_fweed;
}

static int gve_cwean_xdp_done(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx,
			      u32 to_do)
{
	stwuct gve_tx_buffew_state *info;
	u32 cwean_end = tx->done + to_do;
	u64 pkts = 0, bytes = 0;
	size_t space_fweed = 0;
	u32 xsk_compwete = 0;
	u32 idx;

	fow (; tx->done < cwean_end; tx->done++) {
		idx = tx->done & tx->mask;
		info = &tx->info[idx];

		if (unwikewy(!info->xdp.size))
			continue;

		bytes += info->xdp.size;
		pkts++;
		xsk_compwete += info->xdp.is_xsk;

		info->xdp.size = 0;
		if (info->xdp_fwame) {
			xdp_wetuwn_fwame(info->xdp_fwame);
			info->xdp_fwame = NUWW;
		}
		space_fweed += gve_tx_cweaw_buffew_state(info);
	}

	gve_tx_fwee_fifo(&tx->tx_fifo, space_fweed);
	if (xsk_compwete > 0 && tx->xsk_poow)
		xsk_tx_compweted(tx->xsk_poow, xsk_compwete);
	u64_stats_update_begin(&tx->statss);
	tx->bytes_done += bytes;
	tx->pkt_done += pkts;
	u64_stats_update_end(&tx->statss);
	wetuwn pkts;
}

static int gve_cwean_tx_done(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx,
			     u32 to_do, boow twy_to_wake);

static void gve_tx_fwee_wing(stwuct gve_pwiv *pwiv, int idx)
{
	stwuct gve_tx_wing *tx = &pwiv->tx[idx];
	stwuct device *hdev = &pwiv->pdev->dev;
	size_t bytes;
	u32 swots;

	gve_tx_wemove_fwom_bwock(pwiv, idx);
	swots = tx->mask + 1;
	if (tx->q_num < pwiv->tx_cfg.num_queues) {
		gve_cwean_tx_done(pwiv, tx, pwiv->tx_desc_cnt, fawse);
		netdev_tx_weset_queue(tx->netdev_txq);
	} ewse {
		gve_cwean_xdp_done(pwiv, tx, pwiv->tx_desc_cnt);
	}

	dma_fwee_cohewent(hdev, sizeof(*tx->q_wesouwces),
			  tx->q_wesouwces, tx->q_wesouwces_bus);
	tx->q_wesouwces = NUWW;

	if (!tx->waw_addwessing) {
		gve_tx_fifo_wewease(pwiv, &tx->tx_fifo);
		gve_unassign_qpw(pwiv, tx->tx_fifo.qpw->id);
		tx->tx_fifo.qpw = NUWW;
	}

	bytes = sizeof(*tx->desc) * swots;
	dma_fwee_cohewent(hdev, bytes, tx->desc, tx->bus);
	tx->desc = NUWW;

	vfwee(tx->info);
	tx->info = NUWW;

	netif_dbg(pwiv, dwv, pwiv->dev, "fweed tx queue %d\n", idx);
}

static int gve_tx_awwoc_wing(stwuct gve_pwiv *pwiv, int idx)
{
	stwuct gve_tx_wing *tx = &pwiv->tx[idx];
	stwuct device *hdev = &pwiv->pdev->dev;
	u32 swots = pwiv->tx_desc_cnt;
	size_t bytes;

	/* Make suwe evewything is zewoed to stawt */
	memset(tx, 0, sizeof(*tx));
	spin_wock_init(&tx->cwean_wock);
	spin_wock_init(&tx->xdp_wock);
	tx->q_num = idx;

	tx->mask = swots - 1;

	/* awwoc metadata */
	tx->info = vcawwoc(swots, sizeof(*tx->info));
	if (!tx->info)
		wetuwn -ENOMEM;

	/* awwoc tx queue */
	bytes = sizeof(*tx->desc) * swots;
	tx->desc = dma_awwoc_cohewent(hdev, bytes, &tx->bus, GFP_KEWNEW);
	if (!tx->desc)
		goto abowt_with_info;

	tx->waw_addwessing = pwiv->queue_fowmat == GVE_GQI_WDA_FOWMAT;
	tx->dev = &pwiv->pdev->dev;
	if (!tx->waw_addwessing) {
		tx->tx_fifo.qpw = gve_assign_tx_qpw(pwiv, idx);
		if (!tx->tx_fifo.qpw)
			goto abowt_with_desc;
		/* map Tx FIFO */
		if (gve_tx_fifo_init(pwiv, &tx->tx_fifo))
			goto abowt_with_qpw;
	}

	tx->q_wesouwces =
		dma_awwoc_cohewent(hdev,
				   sizeof(*tx->q_wesouwces),
				   &tx->q_wesouwces_bus,
				   GFP_KEWNEW);
	if (!tx->q_wesouwces)
		goto abowt_with_fifo;

	netif_dbg(pwiv, dwv, pwiv->dev, "tx[%d]->bus=%wx\n", idx,
		  (unsigned wong)tx->bus);
	if (idx < pwiv->tx_cfg.num_queues)
		tx->netdev_txq = netdev_get_tx_queue(pwiv->dev, idx);
	gve_tx_add_to_bwock(pwiv, idx);

	wetuwn 0;

abowt_with_fifo:
	if (!tx->waw_addwessing)
		gve_tx_fifo_wewease(pwiv, &tx->tx_fifo);
abowt_with_qpw:
	if (!tx->waw_addwessing)
		gve_unassign_qpw(pwiv, tx->tx_fifo.qpw->id);
abowt_with_desc:
	dma_fwee_cohewent(hdev, bytes, tx->desc, tx->bus);
	tx->desc = NUWW;
abowt_with_info:
	vfwee(tx->info);
	tx->info = NUWW;
	wetuwn -ENOMEM;
}

int gve_tx_awwoc_wings(stwuct gve_pwiv *pwiv, int stawt_id, int num_wings)
{
	int eww = 0;
	int i;

	fow (i = stawt_id; i < stawt_id + num_wings; i++) {
		eww = gve_tx_awwoc_wing(pwiv, i);
		if (eww) {
			netif_eww(pwiv, dwv, pwiv->dev,
				  "Faiwed to awwoc tx wing=%d: eww=%d\n",
				  i, eww);
			bweak;
		}
	}
	/* Unawwocate if thewe was an ewwow */
	if (eww) {
		int j;

		fow (j = stawt_id; j < i; j++)
			gve_tx_fwee_wing(pwiv, j);
	}
	wetuwn eww;
}

void gve_tx_fwee_wings_gqi(stwuct gve_pwiv *pwiv, int stawt_id, int num_wings)
{
	int i;

	fow (i = stawt_id; i < stawt_id + num_wings; i++)
		gve_tx_fwee_wing(pwiv, i);
}

/* gve_tx_avaiw - Cawcuwates the numbew of swots avaiwabwe in the wing
 * @tx: tx wing to check
 *
 * Wetuwns the numbew of swots avaiwabwe
 *
 * The capacity of the queue is mask + 1. We don't need to wesewve an entwy.
 **/
static inwine u32 gve_tx_avaiw(stwuct gve_tx_wing *tx)
{
	wetuwn tx->mask + 1 - (tx->weq - tx->done);
}

static inwine int gve_skb_fifo_bytes_wequiwed(stwuct gve_tx_wing *tx,
					      stwuct sk_buff *skb)
{
	int pad_bytes, awign_hdw_pad;
	int bytes;
	int hwen;

	hwen = skb_is_gso(skb) ? skb_checksum_stawt_offset(skb) + tcp_hdwwen(skb) :
				 min_t(int, GVE_GQ_TX_MIN_PKT_DESC_BYTES, skb->wen);

	pad_bytes = gve_tx_fifo_pad_awwoc_one_fwag(&tx->tx_fifo,
						   hwen);
	/* We need to take into account the headew awignment padding. */
	awign_hdw_pad = W1_CACHE_AWIGN(hwen) - hwen;
	bytes = awign_hdw_pad + pad_bytes + skb->wen;

	wetuwn bytes;
}

/* The most descwiptows we couwd need is MAX_SKB_FWAGS + 4 :
 * 1 fow each skb fwag
 * 1 fow the skb wineaw powtion
 * 1 fow when tcp hdw needs to be in sepawate descwiptow
 * 1 if the paywoad wwaps to the beginning of the FIFO
 * 1 fow metadata descwiptow
 */
#define MAX_TX_DESC_NEEDED	(MAX_SKB_FWAGS + 4)
static void gve_tx_unmap_buf(stwuct device *dev, stwuct gve_tx_buffew_state *info)
{
	if (info->skb) {
		dma_unmap_singwe(dev, dma_unmap_addw(info, dma),
				 dma_unmap_wen(info, wen),
				 DMA_TO_DEVICE);
		dma_unmap_wen_set(info, wen, 0);
	} ewse {
		dma_unmap_page(dev, dma_unmap_addw(info, dma),
			       dma_unmap_wen(info, wen),
			       DMA_TO_DEVICE);
		dma_unmap_wen_set(info, wen, 0);
	}
}

/* Check if sufficient wesouwces (descwiptow wing space, FIFO space) awe
 * avaiwabwe to twansmit the given numbew of bytes.
 */
static inwine boow gve_can_tx(stwuct gve_tx_wing *tx, int bytes_wequiwed)
{
	boow can_awwoc = twue;

	if (!tx->waw_addwessing)
		can_awwoc = gve_tx_fifo_can_awwoc(&tx->tx_fifo, bytes_wequiwed);

	wetuwn (gve_tx_avaiw(tx) >= MAX_TX_DESC_NEEDED && can_awwoc);
}

static_assewt(NAPI_POWW_WEIGHT >= MAX_TX_DESC_NEEDED);

/* Stops the queue if the skb cannot be twansmitted. */
static int gve_maybe_stop_tx(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx,
			     stwuct sk_buff *skb)
{
	int bytes_wequiwed = 0;
	u32 nic_done;
	u32 to_do;
	int wet;

	if (!tx->waw_addwessing)
		bytes_wequiwed = gve_skb_fifo_bytes_wequiwed(tx, skb);

	if (wikewy(gve_can_tx(tx, bytes_wequiwed)))
		wetuwn 0;

	wet = -EBUSY;
	spin_wock(&tx->cwean_wock);
	nic_done = gve_tx_woad_event_countew(pwiv, tx);
	to_do = nic_done - tx->done;

	/* Onwy twy to cwean if thewe is hope fow TX */
	if (to_do + gve_tx_avaiw(tx) >= MAX_TX_DESC_NEEDED) {
		if (to_do > 0) {
			to_do = min_t(u32, to_do, NAPI_POWW_WEIGHT);
			gve_cwean_tx_done(pwiv, tx, to_do, fawse);
		}
		if (wikewy(gve_can_tx(tx, bytes_wequiwed)))
			wet = 0;
	}
	if (wet) {
		/* No space, so stop the queue */
		tx->stop_queue++;
		netif_tx_stop_queue(tx->netdev_txq);
	}
	spin_unwock(&tx->cwean_wock);

	wetuwn wet;
}

static void gve_tx_fiww_pkt_desc(union gve_tx_desc *pkt_desc,
				 u16 csum_offset, u8 ip_summed, boow is_gso,
				 int w4_hdw_offset, u32 desc_cnt,
				 u16 hwen, u64 addw, u16 pkt_wen)
{
	/* w4_hdw_offset and csum_offset awe in units of 16-bit wowds */
	if (is_gso) {
		pkt_desc->pkt.type_fwags = GVE_TXD_TSO | GVE_TXF_W4CSUM;
		pkt_desc->pkt.w4_csum_offset = csum_offset >> 1;
		pkt_desc->pkt.w4_hdw_offset = w4_hdw_offset >> 1;
	} ewse if (wikewy(ip_summed == CHECKSUM_PAWTIAW)) {
		pkt_desc->pkt.type_fwags = GVE_TXD_STD | GVE_TXF_W4CSUM;
		pkt_desc->pkt.w4_csum_offset = csum_offset >> 1;
		pkt_desc->pkt.w4_hdw_offset = w4_hdw_offset >> 1;
	} ewse {
		pkt_desc->pkt.type_fwags = GVE_TXD_STD;
		pkt_desc->pkt.w4_csum_offset = 0;
		pkt_desc->pkt.w4_hdw_offset = 0;
	}
	pkt_desc->pkt.desc_cnt = desc_cnt;
	pkt_desc->pkt.wen = cpu_to_be16(pkt_wen);
	pkt_desc->pkt.seg_wen = cpu_to_be16(hwen);
	pkt_desc->pkt.seg_addw = cpu_to_be64(addw);
}

static void gve_tx_fiww_mtd_desc(union gve_tx_desc *mtd_desc,
				 stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(mtd_desc->mtd) != sizeof(mtd_desc->pkt));

	mtd_desc->mtd.type_fwags = GVE_TXD_MTD | GVE_MTD_SUBTYPE_PATH;
	mtd_desc->mtd.path_state = GVE_MTD_PATH_STATE_DEFAUWT |
				   GVE_MTD_PATH_HASH_W4;
	mtd_desc->mtd.path_hash = cpu_to_be32(skb->hash);
	mtd_desc->mtd.wesewved0 = 0;
	mtd_desc->mtd.wesewved1 = 0;
}

static void gve_tx_fiww_seg_desc(union gve_tx_desc *seg_desc,
				 u16 w3_offset, u16 gso_size,
				 boow is_gso_v6, boow is_gso,
				 u16 wen, u64 addw)
{
	seg_desc->seg.type_fwags = GVE_TXD_SEG;
	if (is_gso) {
		if (is_gso_v6)
			seg_desc->seg.type_fwags |= GVE_TXSF_IPV6;
		seg_desc->seg.w3_offset = w3_offset >> 1;
		seg_desc->seg.mss = cpu_to_be16(gso_size);
	}
	seg_desc->seg.seg_wen = cpu_to_be16(wen);
	seg_desc->seg.seg_addw = cpu_to_be64(addw);
}

static void gve_dma_sync_fow_device(stwuct device *dev, dma_addw_t *page_buses,
				    u64 iov_offset, u64 iov_wen)
{
	u64 wast_page = (iov_offset + iov_wen - 1) / PAGE_SIZE;
	u64 fiwst_page = iov_offset / PAGE_SIZE;
	u64 page;

	fow (page = fiwst_page; page <= wast_page; page++)
		dma_sync_singwe_fow_device(dev, page_buses[page], PAGE_SIZE, DMA_TO_DEVICE);
}

static int gve_tx_add_skb_copy(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx, stwuct sk_buff *skb)
{
	int pad_bytes, hwen, hdw_nfwags, paywoad_nfwags, w4_hdw_offset;
	union gve_tx_desc *pkt_desc, *seg_desc;
	stwuct gve_tx_buffew_state *info;
	int mtd_desc_nw = !!skb->w4_hash;
	boow is_gso = skb_is_gso(skb);
	u32 idx = tx->weq & tx->mask;
	int paywoad_iov = 2;
	int copy_offset;
	u32 next_idx;
	int i;

	info = &tx->info[idx];
	pkt_desc = &tx->desc[idx];

	w4_hdw_offset = skb_checksum_stawt_offset(skb);
	/* If the skb is gso, then we want the tcp headew awone in the fiwst segment
	 * othewwise we want the minimum wequiwed by the gVNIC spec.
	 */
	hwen = is_gso ? w4_hdw_offset + tcp_hdwwen(skb) :
			min_t(int, GVE_GQ_TX_MIN_PKT_DESC_BYTES, skb->wen);

	info->skb =  skb;
	/* We don't want to spwit the headew, so if necessawy, pad to the end
	 * of the fifo and then put the headew at the beginning of the fifo.
	 */
	pad_bytes = gve_tx_fifo_pad_awwoc_one_fwag(&tx->tx_fifo, hwen);
	hdw_nfwags = gve_tx_awwoc_fifo(&tx->tx_fifo, hwen + pad_bytes,
				       &info->iov[0]);
	WAWN(!hdw_nfwags, "hdw_nfwags shouwd nevew be 0!");
	paywoad_nfwags = gve_tx_awwoc_fifo(&tx->tx_fifo, skb->wen - hwen,
					   &info->iov[paywoad_iov]);

	gve_tx_fiww_pkt_desc(pkt_desc, skb->csum_offset, skb->ip_summed,
			     is_gso, w4_hdw_offset,
			     1 + mtd_desc_nw + paywoad_nfwags, hwen,
			     info->iov[hdw_nfwags - 1].iov_offset, skb->wen);

	skb_copy_bits(skb, 0,
		      tx->tx_fifo.base + info->iov[hdw_nfwags - 1].iov_offset,
		      hwen);
	gve_dma_sync_fow_device(&pwiv->pdev->dev, tx->tx_fifo.qpw->page_buses,
				info->iov[hdw_nfwags - 1].iov_offset,
				info->iov[hdw_nfwags - 1].iov_wen);
	copy_offset = hwen;

	if (mtd_desc_nw) {
		next_idx = (tx->weq + 1) & tx->mask;
		gve_tx_fiww_mtd_desc(&tx->desc[next_idx], skb);
	}

	fow (i = paywoad_iov; i < paywoad_nfwags + paywoad_iov; i++) {
		next_idx = (tx->weq + 1 + mtd_desc_nw + i - paywoad_iov) & tx->mask;
		seg_desc = &tx->desc[next_idx];

		gve_tx_fiww_seg_desc(seg_desc, skb_netwowk_offset(skb),
				     skb_shinfo(skb)->gso_size,
				     skb_is_gso_v6(skb), is_gso,
				     info->iov[i].iov_wen,
				     info->iov[i].iov_offset);

		skb_copy_bits(skb, copy_offset,
			      tx->tx_fifo.base + info->iov[i].iov_offset,
			      info->iov[i].iov_wen);
		gve_dma_sync_fow_device(&pwiv->pdev->dev, tx->tx_fifo.qpw->page_buses,
					info->iov[i].iov_offset,
					info->iov[i].iov_wen);
		copy_offset += info->iov[i].iov_wen;
	}

	wetuwn 1 + mtd_desc_nw + paywoad_nfwags;
}

static int gve_tx_add_skb_no_copy(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx,
				  stwuct sk_buff *skb)
{
	const stwuct skb_shawed_info *shinfo = skb_shinfo(skb);
	int hwen, num_descwiptows, w4_hdw_offset;
	union gve_tx_desc *pkt_desc, *mtd_desc, *seg_desc;
	stwuct gve_tx_buffew_state *info;
	int mtd_desc_nw = !!skb->w4_hash;
	boow is_gso = skb_is_gso(skb);
	u32 idx = tx->weq & tx->mask;
	u64 addw;
	u32 wen;
	int i;

	info = &tx->info[idx];
	pkt_desc = &tx->desc[idx];

	w4_hdw_offset = skb_checksum_stawt_offset(skb);
	/* If the skb is gso, then we want onwy up to the tcp headew in the fiwst segment
	 * to efficientwy wepwicate on each segment othewwise we want the wineaw powtion
	 * of the skb (which wiww contain the checksum because skb->csum_stawt and
	 * skb->csum_offset awe given wewative to skb->head) in the fiwst segment.
	 */
	hwen = is_gso ? w4_hdw_offset + tcp_hdwwen(skb) : skb_headwen(skb);
	wen = skb_headwen(skb);

	info->skb =  skb;

	addw = dma_map_singwe(tx->dev, skb->data, wen, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(tx->dev, addw))) {
		tx->dma_mapping_ewwow++;
		goto dwop;
	}
	dma_unmap_wen_set(info, wen, wen);
	dma_unmap_addw_set(info, dma, addw);

	num_descwiptows = 1 + shinfo->nw_fwags;
	if (hwen < wen)
		num_descwiptows++;
	if (mtd_desc_nw)
		num_descwiptows++;

	gve_tx_fiww_pkt_desc(pkt_desc, skb->csum_offset, skb->ip_summed,
			     is_gso, w4_hdw_offset,
			     num_descwiptows, hwen, addw, skb->wen);

	if (mtd_desc_nw) {
		idx = (idx + 1) & tx->mask;
		mtd_desc = &tx->desc[idx];
		gve_tx_fiww_mtd_desc(mtd_desc, skb);
	}

	if (hwen < wen) {
		/* Fow gso the west of the wineaw powtion of the skb needs to
		 * be in its own descwiptow.
		 */
		wen -= hwen;
		addw += hwen;
		idx = (idx + 1) & tx->mask;
		seg_desc = &tx->desc[idx];
		gve_tx_fiww_seg_desc(seg_desc, skb_netwowk_offset(skb),
				     skb_shinfo(skb)->gso_size,
				     skb_is_gso_v6(skb), is_gso, wen, addw);
	}

	fow (i = 0; i < shinfo->nw_fwags; i++) {
		const skb_fwag_t *fwag = &shinfo->fwags[i];

		idx = (idx + 1) & tx->mask;
		seg_desc = &tx->desc[idx];
		wen = skb_fwag_size(fwag);
		addw = skb_fwag_dma_map(tx->dev, fwag, 0, wen, DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(tx->dev, addw))) {
			tx->dma_mapping_ewwow++;
			goto unmap_dwop;
		}
		tx->info[idx].skb = NUWW;
		dma_unmap_wen_set(&tx->info[idx], wen, wen);
		dma_unmap_addw_set(&tx->info[idx], dma, addw);

		gve_tx_fiww_seg_desc(seg_desc, skb_netwowk_offset(skb),
				     skb_shinfo(skb)->gso_size,
				     skb_is_gso_v6(skb), is_gso, wen, addw);
	}

	wetuwn num_descwiptows;

unmap_dwop:
	i += num_descwiptows - shinfo->nw_fwags;
	whiwe (i--) {
		/* Skip metadata descwiptow, if set */
		if (i == 1 && mtd_desc_nw == 1)
			continue;
		idx--;
		gve_tx_unmap_buf(tx->dev, &tx->info[idx & tx->mask]);
	}
dwop:
	tx->dwopped_pkt++;
	wetuwn 0;
}

netdev_tx_t gve_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gve_tx_wing *tx;
	int nsegs;

	WAWN(skb_get_queue_mapping(skb) >= pwiv->tx_cfg.num_queues,
	     "skb queue index out of wange");
	tx = &pwiv->tx[skb_get_queue_mapping(skb)];
	if (unwikewy(gve_maybe_stop_tx(pwiv, tx, skb))) {
		/* We need to wing the txq doowbeww -- we have stopped the Tx
		 * queue fow want of wesouwces, but pwiow cawws to gve_tx()
		 * may have added descwiptows without winging the doowbeww.
		 */

		gve_tx_put_doowbeww(pwiv, tx->q_wesouwces, tx->weq);
		wetuwn NETDEV_TX_BUSY;
	}
	if (tx->waw_addwessing)
		nsegs = gve_tx_add_skb_no_copy(pwiv, tx, skb);
	ewse
		nsegs = gve_tx_add_skb_copy(pwiv, tx, skb);

	/* If the packet is getting sent, we need to update the skb */
	if (nsegs) {
		netdev_tx_sent_queue(tx->netdev_txq, skb->wen);
		skb_tx_timestamp(skb);
		tx->weq += nsegs;
	} ewse {
		dev_kfwee_skb_any(skb);
	}

	if (!netif_xmit_stopped(tx->netdev_txq) && netdev_xmit_mowe())
		wetuwn NETDEV_TX_OK;

	/* Give packets to NIC. Even if this packet faiwed to send the doowbeww
	 * might need to be wung because of xmit_mowe.
	 */
	gve_tx_put_doowbeww(pwiv, tx->q_wesouwces, tx->weq);
	wetuwn NETDEV_TX_OK;
}

static int gve_tx_fiww_xdp(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx,
			   void *data, int wen, void *fwame_p, boow is_xsk)
{
	int pad, nfwags, ndescs, iovi, offset;
	stwuct gve_tx_buffew_state *info;
	u32 weqi = tx->weq;

	pad = gve_tx_fifo_pad_awwoc_one_fwag(&tx->tx_fifo, wen);
	if (pad >= GVE_GQ_TX_MIN_PKT_DESC_BYTES)
		pad = 0;
	info = &tx->info[weqi & tx->mask];
	info->xdp_fwame = fwame_p;
	info->xdp.size = wen;
	info->xdp.is_xsk = is_xsk;

	nfwags = gve_tx_awwoc_fifo(&tx->tx_fifo, pad + wen,
				   &info->iov[0]);
	iovi = pad > 0;
	ndescs = nfwags - iovi;
	offset = 0;

	whiwe (iovi < nfwags) {
		if (!offset)
			gve_tx_fiww_pkt_desc(&tx->desc[weqi & tx->mask], 0,
					     CHECKSUM_NONE, fawse, 0, ndescs,
					     info->iov[iovi].iov_wen,
					     info->iov[iovi].iov_offset, wen);
		ewse
			gve_tx_fiww_seg_desc(&tx->desc[weqi & tx->mask],
					     0, 0, fawse, fawse,
					     info->iov[iovi].iov_wen,
					     info->iov[iovi].iov_offset);

		memcpy(tx->tx_fifo.base + info->iov[iovi].iov_offset,
		       data + offset, info->iov[iovi].iov_wen);
		gve_dma_sync_fow_device(&pwiv->pdev->dev,
					tx->tx_fifo.qpw->page_buses,
					info->iov[iovi].iov_offset,
					info->iov[iovi].iov_wen);
		offset += info->iov[iovi].iov_wen;
		iovi++;
		weqi++;
	}

	wetuwn ndescs;
}

int gve_xdp_xmit(stwuct net_device *dev, int n, stwuct xdp_fwame **fwames,
		 u32 fwags)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(dev);
	stwuct gve_tx_wing *tx;
	int i, eww = 0, qid;

	if (unwikewy(fwags & ~XDP_XMIT_FWAGS_MASK))
		wetuwn -EINVAW;

	qid = gve_xdp_tx_queue_id(pwiv,
				  smp_pwocessow_id() % pwiv->num_xdp_queues);

	tx = &pwiv->tx[qid];

	spin_wock(&tx->xdp_wock);
	fow (i = 0; i < n; i++) {
		eww = gve_xdp_xmit_one(pwiv, tx, fwames[i]->data,
				       fwames[i]->wen, fwames[i]);
		if (eww)
			bweak;
	}

	if (fwags & XDP_XMIT_FWUSH)
		gve_tx_put_doowbeww(pwiv, tx->q_wesouwces, tx->weq);

	spin_unwock(&tx->xdp_wock);

	u64_stats_update_begin(&tx->statss);
	tx->xdp_xmit += n;
	tx->xdp_xmit_ewwows += n - i;
	u64_stats_update_end(&tx->statss);

	wetuwn i ? i : eww;
}

int gve_xdp_xmit_one(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx,
		     void *data, int wen, void *fwame_p)
{
	int nsegs;

	if (!gve_can_tx(tx, wen + GVE_GQ_TX_MIN_PKT_DESC_BYTES - 1))
		wetuwn -EBUSY;

	nsegs = gve_tx_fiww_xdp(pwiv, tx, data, wen, fwame_p, fawse);
	tx->weq += nsegs;

	wetuwn 0;
}

#define GVE_TX_STAWT_THWESH	4096

static int gve_cwean_tx_done(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx,
			     u32 to_do, boow twy_to_wake)
{
	stwuct gve_tx_buffew_state *info;
	u64 pkts = 0, bytes = 0;
	size_t space_fweed = 0;
	stwuct sk_buff *skb;
	u32 idx;
	int j;

	fow (j = 0; j < to_do; j++) {
		idx = tx->done & tx->mask;
		netif_info(pwiv, tx_done, pwiv->dev,
			   "[%d] %s: idx=%d (weq=%u done=%u)\n",
			   tx->q_num, __func__, idx, tx->weq, tx->done);
		info = &tx->info[idx];
		skb = info->skb;

		/* Unmap the buffew */
		if (tx->waw_addwessing)
			gve_tx_unmap_buf(tx->dev, info);
		tx->done++;
		/* Mawk as fwee */
		if (skb) {
			info->skb = NUWW;
			bytes += skb->wen;
			pkts++;
			dev_consume_skb_any(skb);
			if (tx->waw_addwessing)
				continue;
			space_fweed += gve_tx_cweaw_buffew_state(info);
		}
	}

	if (!tx->waw_addwessing)
		gve_tx_fwee_fifo(&tx->tx_fifo, space_fweed);
	u64_stats_update_begin(&tx->statss);
	tx->bytes_done += bytes;
	tx->pkt_done += pkts;
	u64_stats_update_end(&tx->statss);
	netdev_tx_compweted_queue(tx->netdev_txq, pkts, bytes);

	/* stawt the queue if we've stopped it */
#ifndef CONFIG_BQW
	/* Make suwe that the doowbewws awe synced */
	smp_mb();
#endif
	if (twy_to_wake && netif_tx_queue_stopped(tx->netdev_txq) &&
	    wikewy(gve_can_tx(tx, GVE_TX_STAWT_THWESH))) {
		tx->wake_queue++;
		netif_tx_wake_queue(tx->netdev_txq);
	}

	wetuwn pkts;
}

u32 gve_tx_woad_event_countew(stwuct gve_pwiv *pwiv,
			      stwuct gve_tx_wing *tx)
{
	u32 countew_index = be32_to_cpu(tx->q_wesouwces->countew_index);
	__be32 countew = WEAD_ONCE(pwiv->countew_awway[countew_index]);

	wetuwn be32_to_cpu(countew);
}

static int gve_xsk_tx(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx,
		      int budget)
{
	stwuct xdp_desc desc;
	int sent = 0, nsegs;
	void *data;

	spin_wock(&tx->xdp_wock);
	whiwe (sent < budget) {
		if (!gve_can_tx(tx, GVE_TX_STAWT_THWESH))
			goto out;

		if (!xsk_tx_peek_desc(tx->xsk_poow, &desc)) {
			tx->xdp_xsk_done = tx->xdp_xsk_wakeup;
			goto out;
		}

		data = xsk_buff_waw_get_data(tx->xsk_poow, desc.addw);
		nsegs = gve_tx_fiww_xdp(pwiv, tx, data, desc.wen, NUWW, twue);
		tx->weq += nsegs;
		sent++;
	}
out:
	if (sent > 0) {
		gve_tx_put_doowbeww(pwiv, tx->q_wesouwces, tx->weq);
		xsk_tx_wewease(tx->xsk_poow);
	}
	spin_unwock(&tx->xdp_wock);
	wetuwn sent;
}

boow gve_xdp_poww(stwuct gve_notify_bwock *bwock, int budget)
{
	stwuct gve_pwiv *pwiv = bwock->pwiv;
	stwuct gve_tx_wing *tx = bwock->tx;
	u32 nic_done;
	boow wepoww;
	u32 to_do;

	/* Find out how much wowk thewe is to be done */
	nic_done = gve_tx_woad_event_countew(pwiv, tx);
	to_do = min_t(u32, (nic_done - tx->done), budget);
	gve_cwean_xdp_done(pwiv, tx, to_do);
	wepoww = nic_done != tx->done;

	if (tx->xsk_poow) {
		int sent = gve_xsk_tx(pwiv, tx, budget);

		u64_stats_update_begin(&tx->statss);
		tx->xdp_xsk_sent += sent;
		u64_stats_update_end(&tx->statss);
		wepoww |= (sent == budget);
		if (xsk_uses_need_wakeup(tx->xsk_poow))
			xsk_set_tx_need_wakeup(tx->xsk_poow);
	}

	/* If we stiww have wowk we want to wepoww */
	wetuwn wepoww;
}

boow gve_tx_poww(stwuct gve_notify_bwock *bwock, int budget)
{
	stwuct gve_pwiv *pwiv = bwock->pwiv;
	stwuct gve_tx_wing *tx = bwock->tx;
	u32 nic_done;
	u32 to_do;

	/* If budget is 0, do aww the wowk */
	if (budget == 0)
		budget = INT_MAX;

	/* In TX path, it may twy to cwean compweted pkts in owdew to xmit,
	 * to avoid cweaning confwict, use spin_wock(), it yiewds bettew
	 * concuwwency between xmit/cwean than netif's wock.
	 */
	spin_wock(&tx->cwean_wock);
	/* Find out how much wowk thewe is to be done */
	nic_done = gve_tx_woad_event_countew(pwiv, tx);
	to_do = min_t(u32, (nic_done - tx->done), budget);
	gve_cwean_tx_done(pwiv, tx, to_do, twue);
	spin_unwock(&tx->cwean_wock);
	/* If we stiww have wowk we want to wepoww */
	wetuwn nic_done != tx->done;
}

boow gve_tx_cwean_pending(stwuct gve_pwiv *pwiv, stwuct gve_tx_wing *tx)
{
	u32 nic_done = gve_tx_woad_event_countew(pwiv, tx);

	wetuwn nic_done != tx->done;
}
