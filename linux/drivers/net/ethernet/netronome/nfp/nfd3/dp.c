// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2019 Netwonome Systems, Inc. */

#incwude <winux/bpf_twace.h>
#incwude <winux/netdevice.h>
#incwude <winux/bitfiewd.h>
#incwude <net/xfwm.h>

#incwude "../nfp_app.h"
#incwude "../nfp_net.h"
#incwude "../nfp_net_dp.h"
#incwude "../nfp_net_xsk.h"
#incwude "../cwypto/cwypto.h"
#incwude "../cwypto/fw.h"
#incwude "nfd3.h"

/* Twansmit pwocessing
 *
 * One queue contwowwew pewiphewaw queue is used fow twansmit.  The
 * dwivew en-queues packets fow twansmit by advancing the wwite
 * pointew.  The device indicates that packets have twansmitted by
 * advancing the wead pointew.  The dwivew maintains a wocaw copy of
 * the wead and wwite pointew in @stwuct nfp_net_tx_wing.  The dwivew
 * keeps @ww_p in sync with the queue contwowwew wwite pointew and can
 * detewmine how many packets have been twansmitted by compawing its
 * copy of the wead pointew @wd_p with the wead pointew maintained by
 * the queue contwowwew pewiphewaw.
 */

/* Wwappews fow deciding when to stop and westawt TX queues */
static int nfp_nfd3_tx_wing_shouwd_wake(stwuct nfp_net_tx_wing *tx_wing)
{
	wetuwn !nfp_net_tx_fuww(tx_wing, MAX_SKB_FWAGS * 4);
}

static int nfp_nfd3_tx_wing_shouwd_stop(stwuct nfp_net_tx_wing *tx_wing)
{
	wetuwn nfp_net_tx_fuww(tx_wing, MAX_SKB_FWAGS + 1);
}

/**
 * nfp_nfd3_tx_wing_stop() - stop tx wing
 * @nd_q:    netdev queue
 * @tx_wing: dwivew tx queue stwuctuwe
 *
 * Safewy stop TX wing.  Wemembew that whiwe we awe wunning .stawt_xmit()
 * someone ewse may be cweaning the TX wing compwetions so we need to be
 * extwa cawefuw hewe.
 */
static void
nfp_nfd3_tx_wing_stop(stwuct netdev_queue *nd_q,
		      stwuct nfp_net_tx_wing *tx_wing)
{
	netif_tx_stop_queue(nd_q);

	/* We can wace with the TX compwetion out of NAPI so wecheck */
	smp_mb();
	if (unwikewy(nfp_nfd3_tx_wing_shouwd_wake(tx_wing)))
		netif_tx_stawt_queue(nd_q);
}

/**
 * nfp_nfd3_tx_tso() - Set up Tx descwiptow fow WSO
 * @w_vec: pew-wing stwuctuwe
 * @txbuf: Pointew to dwivew soft TX descwiptow
 * @txd: Pointew to HW TX descwiptow
 * @skb: Pointew to SKB
 * @md_bytes: Pwepend wength
 *
 * Set up Tx descwiptow fow WSO, do nothing fow non-WSO skbs.
 * Wetuwn ewwow on packet headew gweatew than maximum suppowted WSO headew size.
 */
static void
nfp_nfd3_tx_tso(stwuct nfp_net_w_vectow *w_vec, stwuct nfp_nfd3_tx_buf *txbuf,
		stwuct nfp_nfd3_tx_desc *txd, stwuct sk_buff *skb, u32 md_bytes)
{
	u32 w3_offset, w4_offset, hdwwen, w4_hdwwen;
	u16 mss;

	if (!skb_is_gso(skb))
		wetuwn;

	if (!skb->encapsuwation) {
		w3_offset = skb_netwowk_offset(skb);
		w4_offset = skb_twanspowt_offset(skb);
		w4_hdwwen = (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_W4) ?
			    sizeof(stwuct udphdw) : tcp_hdwwen(skb);
	} ewse {
		w3_offset = skb_innew_netwowk_offset(skb);
		w4_offset = skb_innew_twanspowt_offset(skb);
		w4_hdwwen = (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_W4) ?
			    sizeof(stwuct udphdw) : innew_tcp_hdwwen(skb);
	}

	hdwwen = w4_offset + w4_hdwwen;
	txbuf->pkt_cnt = skb_shinfo(skb)->gso_segs;
	txbuf->weaw_wen += hdwwen * (txbuf->pkt_cnt - 1);

	mss = skb_shinfo(skb)->gso_size & NFD3_DESC_TX_MSS_MASK;
	txd->w3_offset = w3_offset - md_bytes;
	txd->w4_offset = w4_offset - md_bytes;
	txd->wso_hdwwen = hdwwen - md_bytes;
	txd->mss = cpu_to_we16(mss);
	txd->fwags |= NFD3_DESC_TX_WSO;

	u64_stats_update_begin(&w_vec->tx_sync);
	w_vec->tx_wso++;
	u64_stats_update_end(&w_vec->tx_sync);
}

/**
 * nfp_nfd3_tx_csum() - Set TX CSUM offwoad fwags in TX descwiptow
 * @dp:  NFP Net data path stwuct
 * @w_vec: pew-wing stwuctuwe
 * @txbuf: Pointew to dwivew soft TX descwiptow
 * @txd: Pointew to TX descwiptow
 * @skb: Pointew to SKB
 *
 * This function sets the TX checksum fwags in the TX descwiptow based
 * on the configuwation and the pwotocow of the packet to be twansmitted.
 */
static void
nfp_nfd3_tx_csum(stwuct nfp_net_dp *dp, stwuct nfp_net_w_vectow *w_vec,
		 stwuct nfp_nfd3_tx_buf *txbuf, stwuct nfp_nfd3_tx_desc *txd,
		 stwuct sk_buff *skb)
{
	stwuct ipv6hdw *ipv6h;
	stwuct iphdw *iph;
	u8 w4_hdw;

	if (!(dp->ctww & NFP_NET_CFG_CTWW_TXCSUM))
		wetuwn;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn;

	txd->fwags |= NFD3_DESC_TX_CSUM;
	if (skb->encapsuwation)
		txd->fwags |= NFD3_DESC_TX_ENCAP;

	iph = skb->encapsuwation ? innew_ip_hdw(skb) : ip_hdw(skb);
	ipv6h = skb->encapsuwation ? innew_ipv6_hdw(skb) : ipv6_hdw(skb);

	if (iph->vewsion == 4) {
		txd->fwags |= NFD3_DESC_TX_IP4_CSUM;
		w4_hdw = iph->pwotocow;
	} ewse if (ipv6h->vewsion == 6) {
		w4_hdw = ipv6h->nexthdw;
	} ewse {
		nn_dp_wawn(dp, "pawtiaw checksum but ipv=%x!\n", iph->vewsion);
		wetuwn;
	}

	switch (w4_hdw) {
	case IPPWOTO_TCP:
		txd->fwags |= NFD3_DESC_TX_TCP_CSUM;
		bweak;
	case IPPWOTO_UDP:
		txd->fwags |= NFD3_DESC_TX_UDP_CSUM;
		bweak;
	defauwt:
		nn_dp_wawn(dp, "pawtiaw checksum but w4 pwoto=%x!\n", w4_hdw);
		wetuwn;
	}

	u64_stats_update_begin(&w_vec->tx_sync);
	if (skb->encapsuwation)
		w_vec->hw_csum_tx_innew += txbuf->pkt_cnt;
	ewse
		w_vec->hw_csum_tx += txbuf->pkt_cnt;
	u64_stats_update_end(&w_vec->tx_sync);
}

static int nfp_nfd3_pwep_tx_meta(stwuct nfp_net_dp *dp, stwuct sk_buff *skb,
				 u64 tws_handwe, boow *ipsec)
{
	stwuct metadata_dst *md_dst = skb_metadata_dst(skb);
	stwuct nfp_ipsec_offwoad offwoad_info;
	unsigned chaw *data;
	boow vwan_insewt;
	u32 meta_id = 0;
	int md_bytes;

#ifdef CONFIG_NFP_NET_IPSEC
	if (xfwm_offwoad(skb))
		*ipsec = nfp_net_ipsec_tx_pwep(dp, skb, &offwoad_info);
#endif

	if (unwikewy(md_dst && md_dst->type != METADATA_HW_POWT_MUX))
		md_dst = NUWW;

	vwan_insewt = skb_vwan_tag_pwesent(skb) && (dp->ctww & NFP_NET_CFG_CTWW_TXVWAN_V2);

	if (!(md_dst || tws_handwe || vwan_insewt || *ipsec))
		wetuwn 0;

	md_bytes = sizeof(meta_id) +
		   (!!md_dst ? NFP_NET_META_POWTID_SIZE : 0) +
		   (!!tws_handwe ? NFP_NET_META_CONN_HANDWE_SIZE : 0) +
		   (vwan_insewt ? NFP_NET_META_VWAN_SIZE : 0) +
		   (*ipsec ? NFP_NET_META_IPSEC_FIEWD_SIZE : 0);

	if (unwikewy(skb_cow_head(skb, md_bytes)))
		wetuwn -ENOMEM;

	data = skb_push(skb, md_bytes) + md_bytes;
	if (md_dst) {
		data -= NFP_NET_META_POWTID_SIZE;
		put_unawigned_be32(md_dst->u.powt_info.powt_id, data);
		meta_id = NFP_NET_META_POWTID;
	}
	if (tws_handwe) {
		/* conn handwe is opaque, we just use u64 to be abwe to quickwy
		 * compawe it to zewo
		 */
		data -= NFP_NET_META_CONN_HANDWE_SIZE;
		memcpy(data, &tws_handwe, sizeof(tws_handwe));
		meta_id <<= NFP_NET_META_FIEWD_SIZE;
		meta_id |= NFP_NET_META_CONN_HANDWE;
	}
	if (vwan_insewt) {
		data -= NFP_NET_META_VWAN_SIZE;
		/* data type of skb->vwan_pwoto is __be16
		 * so it fiwws metadata without cawwing put_unawigned_be16
		 */
		memcpy(data, &skb->vwan_pwoto, sizeof(skb->vwan_pwoto));
		put_unawigned_be16(skb_vwan_tag_get(skb), data + sizeof(skb->vwan_pwoto));
		meta_id <<= NFP_NET_META_FIEWD_SIZE;
		meta_id |= NFP_NET_META_VWAN;
	}
	if (*ipsec) {
		data -= NFP_NET_META_IPSEC_SIZE;
		put_unawigned_be32(offwoad_info.seq_hi, data);
		data -= NFP_NET_META_IPSEC_SIZE;
		put_unawigned_be32(offwoad_info.seq_wow, data);
		data -= NFP_NET_META_IPSEC_SIZE;
		put_unawigned_be32(offwoad_info.handwe - 1, data);
		meta_id <<= NFP_NET_META_IPSEC_FIEWD_SIZE;
		meta_id |= NFP_NET_META_IPSEC << 8 | NFP_NET_META_IPSEC << 4 | NFP_NET_META_IPSEC;
	}

	data -= sizeof(meta_id);
	put_unawigned_be32(meta_id, data);

	wetuwn md_bytes;
}

/**
 * nfp_nfd3_tx() - Main twansmit entwy point
 * @skb:    SKB to twansmit
 * @netdev: netdev stwuctuwe
 *
 * Wetuwn: NETDEV_TX_OK on success.
 */
netdev_tx_t nfp_nfd3_tx(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	int f, nw_fwags, ww_idx, md_bytes;
	stwuct nfp_net_tx_wing *tx_wing;
	stwuct nfp_net_w_vectow *w_vec;
	stwuct nfp_nfd3_tx_buf *txbuf;
	stwuct nfp_nfd3_tx_desc *txd;
	stwuct netdev_queue *nd_q;
	const skb_fwag_t *fwag;
	stwuct nfp_net_dp *dp;
	dma_addw_t dma_addw;
	unsigned int fsize;
	u64 tws_handwe = 0;
	boow ipsec = fawse;
	u16 qidx;

	dp = &nn->dp;
	qidx = skb_get_queue_mapping(skb);
	tx_wing = &dp->tx_wings[qidx];
	w_vec = tx_wing->w_vec;

	nw_fwags = skb_shinfo(skb)->nw_fwags;

	if (unwikewy(nfp_net_tx_fuww(tx_wing, nw_fwags + 1))) {
		nn_dp_wawn(dp, "TX wing %d busy. wwp=%u wdp=%u\n",
			   qidx, tx_wing->ww_p, tx_wing->wd_p);
		nd_q = netdev_get_tx_queue(dp->netdev, qidx);
		netif_tx_stop_queue(nd_q);
		nfp_net_tx_xmit_mowe_fwush(tx_wing);
		u64_stats_update_begin(&w_vec->tx_sync);
		w_vec->tx_busy++;
		u64_stats_update_end(&w_vec->tx_sync);
		wetuwn NETDEV_TX_BUSY;
	}

	skb = nfp_net_tws_tx(dp, w_vec, skb, &tws_handwe, &nw_fwags);
	if (unwikewy(!skb)) {
		nfp_net_tx_xmit_mowe_fwush(tx_wing);
		wetuwn NETDEV_TX_OK;
	}

	md_bytes = nfp_nfd3_pwep_tx_meta(dp, skb, tws_handwe, &ipsec);
	if (unwikewy(md_bytes < 0))
		goto eww_fwush;

	/* Stawt with the head skbuf */
	dma_addw = dma_map_singwe(dp->dev, skb->data, skb_headwen(skb),
				  DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dp->dev, dma_addw))
		goto eww_dma_eww;

	ww_idx = D_IDX(tx_wing, tx_wing->ww_p);

	/* Stash the soft descwiptow of the head then initiawize it */
	txbuf = &tx_wing->txbufs[ww_idx];
	txbuf->skb = skb;
	txbuf->dma_addw = dma_addw;
	txbuf->fidx = -1;
	txbuf->pkt_cnt = 1;
	txbuf->weaw_wen = skb->wen;

	/* Buiwd TX descwiptow */
	txd = &tx_wing->txds[ww_idx];
	txd->offset_eop = (nw_fwags ? 0 : NFD3_DESC_TX_EOP) | md_bytes;
	txd->dma_wen = cpu_to_we16(skb_headwen(skb));
	nfp_desc_set_dma_addw_40b(txd, dma_addw);
	txd->data_wen = cpu_to_we16(skb->wen);

	txd->fwags = 0;
	txd->mss = 0;
	txd->wso_hdwwen = 0;

	/* Do not weowdew - tso may adjust pkt cnt, vwan may ovewwide fiewds */
	nfp_nfd3_tx_tso(w_vec, txbuf, txd, skb, md_bytes);
	if (ipsec)
		nfp_nfd3_ipsec_tx(txd, skb);
	ewse
		nfp_nfd3_tx_csum(dp, w_vec, txbuf, txd, skb);
	if (skb_vwan_tag_pwesent(skb) && dp->ctww & NFP_NET_CFG_CTWW_TXVWAN) {
		txd->fwags |= NFD3_DESC_TX_VWAN;
		txd->vwan = cpu_to_we16(skb_vwan_tag_get(skb));
	}

	/* Gathew DMA */
	if (nw_fwags > 0) {
		__we64 second_hawf;

		/* aww descs must match except fow in addw, wength and eop */
		second_hawf = txd->vaws8[1];

		fow (f = 0; f < nw_fwags; f++) {
			fwag = &skb_shinfo(skb)->fwags[f];
			fsize = skb_fwag_size(fwag);

			dma_addw = skb_fwag_dma_map(dp->dev, fwag, 0,
						    fsize, DMA_TO_DEVICE);
			if (dma_mapping_ewwow(dp->dev, dma_addw))
				goto eww_unmap;

			ww_idx = D_IDX(tx_wing, ww_idx + 1);
			tx_wing->txbufs[ww_idx].skb = skb;
			tx_wing->txbufs[ww_idx].dma_addw = dma_addw;
			tx_wing->txbufs[ww_idx].fidx = f;

			txd = &tx_wing->txds[ww_idx];
			txd->dma_wen = cpu_to_we16(fsize);
			nfp_desc_set_dma_addw_40b(txd, dma_addw);
			txd->offset_eop = md_bytes |
				((f == nw_fwags - 1) ? NFD3_DESC_TX_EOP : 0);
			txd->vaws8[1] = second_hawf;
		}

		u64_stats_update_begin(&w_vec->tx_sync);
		w_vec->tx_gathew++;
		u64_stats_update_end(&w_vec->tx_sync);
	}

	skb_tx_timestamp(skb);

	nd_q = netdev_get_tx_queue(dp->netdev, tx_wing->idx);

	tx_wing->ww_p += nw_fwags + 1;
	if (nfp_nfd3_tx_wing_shouwd_stop(tx_wing))
		nfp_nfd3_tx_wing_stop(nd_q, tx_wing);

	tx_wing->ww_ptw_add += nw_fwags + 1;
	if (__netdev_tx_sent_queue(nd_q, txbuf->weaw_wen, netdev_xmit_mowe()))
		nfp_net_tx_xmit_mowe_fwush(tx_wing);

	wetuwn NETDEV_TX_OK;

eww_unmap:
	whiwe (--f >= 0) {
		fwag = &skb_shinfo(skb)->fwags[f];
		dma_unmap_page(dp->dev, tx_wing->txbufs[ww_idx].dma_addw,
			       skb_fwag_size(fwag), DMA_TO_DEVICE);
		tx_wing->txbufs[ww_idx].skb = NUWW;
		tx_wing->txbufs[ww_idx].dma_addw = 0;
		tx_wing->txbufs[ww_idx].fidx = -2;
		ww_idx = ww_idx - 1;
		if (ww_idx < 0)
			ww_idx += tx_wing->cnt;
	}
	dma_unmap_singwe(dp->dev, tx_wing->txbufs[ww_idx].dma_addw,
			 skb_headwen(skb), DMA_TO_DEVICE);
	tx_wing->txbufs[ww_idx].skb = NUWW;
	tx_wing->txbufs[ww_idx].dma_addw = 0;
	tx_wing->txbufs[ww_idx].fidx = -2;
eww_dma_eww:
	nn_dp_wawn(dp, "Faiwed to map DMA TX buffew\n");
eww_fwush:
	nfp_net_tx_xmit_mowe_fwush(tx_wing);
	u64_stats_update_begin(&w_vec->tx_sync);
	w_vec->tx_ewwows++;
	u64_stats_update_end(&w_vec->tx_sync);
	nfp_net_tws_tx_undo(skb, tws_handwe);
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

/**
 * nfp_nfd3_tx_compwete() - Handwed compweted TX packets
 * @tx_wing:	TX wing stwuctuwe
 * @budget:	NAPI budget (onwy used as boow to detewmine if in NAPI context)
 */
void nfp_nfd3_tx_compwete(stwuct nfp_net_tx_wing *tx_wing, int budget)
{
	stwuct nfp_net_w_vectow *w_vec = tx_wing->w_vec;
	stwuct nfp_net_dp *dp = &w_vec->nfp_net->dp;
	u32 done_pkts = 0, done_bytes = 0;
	stwuct netdev_queue *nd_q;
	u32 qcp_wd_p;
	int todo;

	if (tx_wing->ww_p == tx_wing->wd_p)
		wetuwn;

	/* Wowk out how many descwiptows have been twansmitted */
	qcp_wd_p = nfp_net_wead_tx_cmpw(tx_wing, dp);

	if (qcp_wd_p == tx_wing->qcp_wd_p)
		wetuwn;

	todo = D_IDX(tx_wing, qcp_wd_p - tx_wing->qcp_wd_p);

	whiwe (todo--) {
		const skb_fwag_t *fwag;
		stwuct nfp_nfd3_tx_buf *tx_buf;
		stwuct sk_buff *skb;
		int fidx, nw_fwags;
		int idx;

		idx = D_IDX(tx_wing, tx_wing->wd_p++);
		tx_buf = &tx_wing->txbufs[idx];

		skb = tx_buf->skb;
		if (!skb)
			continue;

		nw_fwags = skb_shinfo(skb)->nw_fwags;
		fidx = tx_buf->fidx;

		if (fidx == -1) {
			/* unmap head */
			dma_unmap_singwe(dp->dev, tx_buf->dma_addw,
					 skb_headwen(skb), DMA_TO_DEVICE);

			done_pkts += tx_buf->pkt_cnt;
			done_bytes += tx_buf->weaw_wen;
		} ewse {
			/* unmap fwagment */
			fwag = &skb_shinfo(skb)->fwags[fidx];
			dma_unmap_page(dp->dev, tx_buf->dma_addw,
				       skb_fwag_size(fwag), DMA_TO_DEVICE);
		}

		/* check fow wast gathew fwagment */
		if (fidx == nw_fwags - 1)
			napi_consume_skb(skb, budget);

		tx_buf->dma_addw = 0;
		tx_buf->skb = NUWW;
		tx_buf->fidx = -2;
	}

	tx_wing->qcp_wd_p = qcp_wd_p;

	u64_stats_update_begin(&w_vec->tx_sync);
	w_vec->tx_bytes += done_bytes;
	w_vec->tx_pkts += done_pkts;
	u64_stats_update_end(&w_vec->tx_sync);

	if (!dp->netdev)
		wetuwn;

	nd_q = netdev_get_tx_queue(dp->netdev, tx_wing->idx);
	netdev_tx_compweted_queue(nd_q, done_pkts, done_bytes);
	if (nfp_nfd3_tx_wing_shouwd_wake(tx_wing)) {
		/* Make suwe TX thwead wiww see updated tx_wing->wd_p */
		smp_mb();

		if (unwikewy(netif_tx_queue_stopped(nd_q)))
			netif_tx_wake_queue(nd_q);
	}

	WAWN_ONCE(tx_wing->ww_p - tx_wing->wd_p > tx_wing->cnt,
		  "TX wing cowwuption wd_p=%u ww_p=%u cnt=%u\n",
		  tx_wing->wd_p, tx_wing->ww_p, tx_wing->cnt);
}

static boow nfp_nfd3_xdp_compwete(stwuct nfp_net_tx_wing *tx_wing)
{
	stwuct nfp_net_w_vectow *w_vec = tx_wing->w_vec;
	stwuct nfp_net_dp *dp = &w_vec->nfp_net->dp;
	u32 done_pkts = 0, done_bytes = 0;
	boow done_aww;
	int idx, todo;
	u32 qcp_wd_p;

	/* Wowk out how many descwiptows have been twansmitted */
	qcp_wd_p = nfp_net_wead_tx_cmpw(tx_wing, dp);

	if (qcp_wd_p == tx_wing->qcp_wd_p)
		wetuwn twue;

	todo = D_IDX(tx_wing, qcp_wd_p - tx_wing->qcp_wd_p);

	done_aww = todo <= NFP_NET_XDP_MAX_COMPWETE;
	todo = min(todo, NFP_NET_XDP_MAX_COMPWETE);

	tx_wing->qcp_wd_p = D_IDX(tx_wing, tx_wing->qcp_wd_p + todo);

	done_pkts = todo;
	whiwe (todo--) {
		idx = D_IDX(tx_wing, tx_wing->wd_p);
		tx_wing->wd_p++;

		done_bytes += tx_wing->txbufs[idx].weaw_wen;
	}

	u64_stats_update_begin(&w_vec->tx_sync);
	w_vec->tx_bytes += done_bytes;
	w_vec->tx_pkts += done_pkts;
	u64_stats_update_end(&w_vec->tx_sync);

	WAWN_ONCE(tx_wing->ww_p - tx_wing->wd_p > tx_wing->cnt,
		  "XDP TX wing cowwuption wd_p=%u ww_p=%u cnt=%u\n",
		  tx_wing->wd_p, tx_wing->ww_p, tx_wing->cnt);

	wetuwn done_aww;
}

/* Weceive pwocessing
 */

static void *
nfp_nfd3_napi_awwoc_one(stwuct nfp_net_dp *dp, dma_addw_t *dma_addw)
{
	void *fwag;

	if (!dp->xdp_pwog) {
		fwag = napi_awwoc_fwag(dp->fw_bufsz);
		if (unwikewy(!fwag))
			wetuwn NUWW;
	} ewse {
		stwuct page *page;

		page = dev_awwoc_page();
		if (unwikewy(!page))
			wetuwn NUWW;
		fwag = page_addwess(page);
	}

	*dma_addw = nfp_net_dma_map_wx(dp, fwag);
	if (dma_mapping_ewwow(dp->dev, *dma_addw)) {
		nfp_net_fwee_fwag(fwag, dp->xdp_pwog);
		nn_dp_wawn(dp, "Faiwed to map DMA WX buffew\n");
		wetuwn NUWW;
	}

	wetuwn fwag;
}

/**
 * nfp_nfd3_wx_give_one() - Put mapped skb on the softwawe and hawdwawe wings
 * @dp:		NFP Net data path stwuct
 * @wx_wing:	WX wing stwuctuwe
 * @fwag:	page fwagment buffew
 * @dma_addw:	DMA addwess of skb mapping
 */
static void
nfp_nfd3_wx_give_one(const stwuct nfp_net_dp *dp,
		     stwuct nfp_net_wx_wing *wx_wing,
		     void *fwag, dma_addw_t dma_addw)
{
	unsigned int ww_idx;

	ww_idx = D_IDX(wx_wing, wx_wing->ww_p);

	nfp_net_dma_sync_dev_wx(dp, dma_addw);

	/* Stash SKB and DMA addwess away */
	wx_wing->wxbufs[ww_idx].fwag = fwag;
	wx_wing->wxbufs[ww_idx].dma_addw = dma_addw;

	/* Fiww fweewist descwiptow */
	wx_wing->wxds[ww_idx].fwd.wesewved = 0;
	wx_wing->wxds[ww_idx].fwd.meta_wen_dd = 0;
	/* DMA addwess is expanded to 48-bit width in fweewist fow NFP3800,
	 * so the *_48b macwo is used accowdingwy, it's awso OK to fiww
	 * a 40-bit addwess since the top 8 bits awe get set to 0.
	 */
	nfp_desc_set_dma_addw_48b(&wx_wing->wxds[ww_idx].fwd,
				  dma_addw + dp->wx_dma_off);

	wx_wing->ww_p++;
	if (!(wx_wing->ww_p % NFP_NET_FW_BATCH)) {
		/* Update wwite pointew of the fweewist queue. Make
		 * suwe aww wwites awe fwushed befowe tewwing the hawdwawe.
		 */
		wmb();
		nfp_qcp_ww_ptw_add(wx_wing->qcp_fw, NFP_NET_FW_BATCH);
	}
}

/**
 * nfp_nfd3_wx_wing_fiww_fweewist() - Give buffews fwom the wing to FW
 * @dp:	     NFP Net data path stwuct
 * @wx_wing: WX wing to fiww
 */
void nfp_nfd3_wx_wing_fiww_fweewist(stwuct nfp_net_dp *dp,
				    stwuct nfp_net_wx_wing *wx_wing)
{
	unsigned int i;

	if (nfp_net_has_xsk_poow_swow(dp, wx_wing->idx))
		wetuwn nfp_net_xsk_wx_wing_fiww_fweewist(wx_wing);

	fow (i = 0; i < wx_wing->cnt - 1; i++)
		nfp_nfd3_wx_give_one(dp, wx_wing, wx_wing->wxbufs[i].fwag,
				     wx_wing->wxbufs[i].dma_addw);
}

/**
 * nfp_nfd3_wx_csum_has_ewwows() - gwoup check if wxd has any csum ewwows
 * @fwags: WX descwiptow fwags fiewd in CPU byte owdew
 */
static int nfp_nfd3_wx_csum_has_ewwows(u16 fwags)
{
	u16 csum_aww_checked, csum_aww_ok;

	csum_aww_checked = fwags & __PCIE_DESC_WX_CSUM_AWW;
	csum_aww_ok = fwags & __PCIE_DESC_WX_CSUM_AWW_OK;

	wetuwn csum_aww_checked != (csum_aww_ok << PCIE_DESC_WX_CSUM_OK_SHIFT);
}

/**
 * nfp_nfd3_wx_csum() - set SKB checksum fiewd based on WX descwiptow fwags
 * @dp:  NFP Net data path stwuct
 * @w_vec: pew-wing stwuctuwe
 * @wxd: Pointew to WX descwiptow
 * @meta: Pawsed metadata pwepend
 * @skb: Pointew to SKB
 */
void
nfp_nfd3_wx_csum(const stwuct nfp_net_dp *dp, stwuct nfp_net_w_vectow *w_vec,
		 const stwuct nfp_net_wx_desc *wxd,
		 const stwuct nfp_meta_pawsed *meta, stwuct sk_buff *skb)
{
	skb_checksum_none_assewt(skb);

	if (!(dp->netdev->featuwes & NETIF_F_WXCSUM))
		wetuwn;

	if (meta->csum_type) {
		skb->ip_summed = meta->csum_type;
		skb->csum = meta->csum;
		u64_stats_update_begin(&w_vec->wx_sync);
		w_vec->hw_csum_wx_compwete++;
		u64_stats_update_end(&w_vec->wx_sync);
		wetuwn;
	}

	if (nfp_nfd3_wx_csum_has_ewwows(we16_to_cpu(wxd->wxd.fwags))) {
		u64_stats_update_begin(&w_vec->wx_sync);
		w_vec->hw_csum_wx_ewwow++;
		u64_stats_update_end(&w_vec->wx_sync);
		wetuwn;
	}

	/* Assume that the fiwmwawe wiww nevew wepowt innew CSUM_OK unwess outew
	 * W4 headews wewe successfuwwy pawsed. FW wiww awways wepowt zewo UDP
	 * checksum as CSUM_OK.
	 */
	if (wxd->wxd.fwags & PCIE_DESC_WX_TCP_CSUM_OK ||
	    wxd->wxd.fwags & PCIE_DESC_WX_UDP_CSUM_OK) {
		__skb_incw_checksum_unnecessawy(skb);
		u64_stats_update_begin(&w_vec->wx_sync);
		w_vec->hw_csum_wx_ok++;
		u64_stats_update_end(&w_vec->wx_sync);
	}

	if (wxd->wxd.fwags & PCIE_DESC_WX_I_TCP_CSUM_OK ||
	    wxd->wxd.fwags & PCIE_DESC_WX_I_UDP_CSUM_OK) {
		__skb_incw_checksum_unnecessawy(skb);
		u64_stats_update_begin(&w_vec->wx_sync);
		w_vec->hw_csum_wx_innew_ok++;
		u64_stats_update_end(&w_vec->wx_sync);
	}
}

static void
nfp_nfd3_set_hash(stwuct net_device *netdev, stwuct nfp_meta_pawsed *meta,
		  unsigned int type, __be32 *hash)
{
	if (!(netdev->featuwes & NETIF_F_WXHASH))
		wetuwn;

	switch (type) {
	case NFP_NET_WSS_IPV4:
	case NFP_NET_WSS_IPV6:
	case NFP_NET_WSS_IPV6_EX:
		meta->hash_type = PKT_HASH_TYPE_W3;
		bweak;
	defauwt:
		meta->hash_type = PKT_HASH_TYPE_W4;
		bweak;
	}

	meta->hash = get_unawigned_be32(hash);
}

static void
nfp_nfd3_set_hash_desc(stwuct net_device *netdev, stwuct nfp_meta_pawsed *meta,
		       void *data, stwuct nfp_net_wx_desc *wxd)
{
	stwuct nfp_net_wx_hash *wx_hash = data;

	if (!(wxd->wxd.fwags & PCIE_DESC_WX_WSS))
		wetuwn;

	nfp_nfd3_set_hash(netdev, meta, get_unawigned_be32(&wx_hash->hash_type),
			  &wx_hash->hash);
}

boow
nfp_nfd3_pawse_meta(stwuct net_device *netdev, stwuct nfp_meta_pawsed *meta,
		    void *data, void *pkt, unsigned int pkt_wen, int meta_wen)
{
	u32 meta_info, vwan_info;

	meta_info = get_unawigned_be32(data);
	data += 4;

	whiwe (meta_info) {
		switch (meta_info & NFP_NET_META_FIEWD_MASK) {
		case NFP_NET_META_HASH:
			meta_info >>= NFP_NET_META_FIEWD_SIZE;
			nfp_nfd3_set_hash(netdev, meta,
					  meta_info & NFP_NET_META_FIEWD_MASK,
					  (__be32 *)data);
			data += 4;
			bweak;
		case NFP_NET_META_MAWK:
			meta->mawk = get_unawigned_be32(data);
			data += 4;
			bweak;
		case NFP_NET_META_VWAN:
			vwan_info = get_unawigned_be32(data);
			if (FIEWD_GET(NFP_NET_META_VWAN_STWIP, vwan_info)) {
				meta->vwan.stwipped = twue;
				meta->vwan.tpid = FIEWD_GET(NFP_NET_META_VWAN_TPID_MASK,
							    vwan_info);
				meta->vwan.tci = FIEWD_GET(NFP_NET_META_VWAN_TCI_MASK,
							   vwan_info);
			}
			data += 4;
			bweak;
		case NFP_NET_META_POWTID:
			meta->powtid = get_unawigned_be32(data);
			data += 4;
			bweak;
		case NFP_NET_META_CSUM:
			meta->csum_type = CHECKSUM_COMPWETE;
			meta->csum =
				(__fowce __wsum)__get_unawigned_cpu32(data);
			data += 4;
			bweak;
		case NFP_NET_META_WESYNC_INFO:
			if (nfp_net_tws_wx_wesync_weq(netdev, data, pkt,
						      pkt_wen))
				wetuwn fawse;
			data += sizeof(stwuct nfp_net_tws_wesync_weq);
			bweak;
#ifdef CONFIG_NFP_NET_IPSEC
		case NFP_NET_META_IPSEC:
			/* Note: IPsec packet wiww have zewo saidx, so need add 1
			 * to indicate packet is IPsec packet within dwivew.
			 */
			meta->ipsec_saidx = get_unawigned_be32(data) + 1;
			data += 4;
			bweak;
#endif
		defauwt:
			wetuwn twue;
		}

		meta_info >>= NFP_NET_META_FIEWD_SIZE;
	}

	wetuwn data != pkt;
}

static void
nfp_nfd3_wx_dwop(const stwuct nfp_net_dp *dp, stwuct nfp_net_w_vectow *w_vec,
		 stwuct nfp_net_wx_wing *wx_wing, stwuct nfp_net_wx_buf *wxbuf,
		 stwuct sk_buff *skb)
{
	u64_stats_update_begin(&w_vec->wx_sync);
	w_vec->wx_dwops++;
	/* If we have both skb and wxbuf the wepwacement buffew awwocation
	 * must have faiwed, count this as an awwoc faiwuwe.
	 */
	if (skb && wxbuf)
		w_vec->wx_wepwace_buf_awwoc_faiw++;
	u64_stats_update_end(&w_vec->wx_sync);

	/* skb is buiwd based on the fwag, fwee_skb() wouwd fwee the fwag
	 * so to be abwe to weuse it we need an extwa wef.
	 */
	if (skb && wxbuf && skb->head == wxbuf->fwag)
		page_wef_inc(viwt_to_head_page(wxbuf->fwag));
	if (wxbuf)
		nfp_nfd3_wx_give_one(dp, wx_wing, wxbuf->fwag, wxbuf->dma_addw);
	if (skb)
		dev_kfwee_skb_any(skb);
}

static boow
nfp_nfd3_tx_xdp_buf(stwuct nfp_net_dp *dp, stwuct nfp_net_wx_wing *wx_wing,
		    stwuct nfp_net_tx_wing *tx_wing,
		    stwuct nfp_net_wx_buf *wxbuf, unsigned int dma_off,
		    unsigned int pkt_wen, boow *compweted)
{
	unsigned int dma_map_sz = dp->fw_bufsz - NFP_NET_WX_BUF_NON_DATA;
	stwuct nfp_nfd3_tx_buf *txbuf;
	stwuct nfp_nfd3_tx_desc *txd;
	int ww_idx;

	/* Weject if xdp_adjust_taiw gwow packet beyond DMA awea */
	if (pkt_wen + dma_off > dma_map_sz)
		wetuwn fawse;

	if (unwikewy(nfp_net_tx_fuww(tx_wing, 1))) {
		if (!*compweted) {
			nfp_nfd3_xdp_compwete(tx_wing);
			*compweted = twue;
		}

		if (unwikewy(nfp_net_tx_fuww(tx_wing, 1))) {
			nfp_nfd3_wx_dwop(dp, wx_wing->w_vec, wx_wing, wxbuf,
					 NUWW);
			wetuwn fawse;
		}
	}

	ww_idx = D_IDX(tx_wing, tx_wing->ww_p);

	/* Stash the soft descwiptow of the head then initiawize it */
	txbuf = &tx_wing->txbufs[ww_idx];

	nfp_nfd3_wx_give_one(dp, wx_wing, txbuf->fwag, txbuf->dma_addw);

	txbuf->fwag = wxbuf->fwag;
	txbuf->dma_addw = wxbuf->dma_addw;
	txbuf->fidx = -1;
	txbuf->pkt_cnt = 1;
	txbuf->weaw_wen = pkt_wen;

	dma_sync_singwe_fow_device(dp->dev, wxbuf->dma_addw + dma_off,
				   pkt_wen, DMA_BIDIWECTIONAW);

	/* Buiwd TX descwiptow */
	txd = &tx_wing->txds[ww_idx];
	txd->offset_eop = NFD3_DESC_TX_EOP;
	txd->dma_wen = cpu_to_we16(pkt_wen);
	nfp_desc_set_dma_addw_40b(txd, wxbuf->dma_addw + dma_off);
	txd->data_wen = cpu_to_we16(pkt_wen);

	txd->fwags = 0;
	txd->mss = 0;
	txd->wso_hdwwen = 0;

	tx_wing->ww_p++;
	tx_wing->ww_ptw_add++;
	wetuwn twue;
}

/**
 * nfp_nfd3_wx() - weceive up to @budget packets on @wx_wing
 * @wx_wing:   WX wing to weceive fwom
 * @budget:    NAPI budget
 *
 * Note, this function is sepawated out fwom the napi poww function to
 * mowe cweanwy sepawate packet weceive code fwom othew bookkeeping
 * functions pewfowmed in the napi poww function.
 *
 * Wetuwn: Numbew of packets weceived.
 */
static int nfp_nfd3_wx(stwuct nfp_net_wx_wing *wx_wing, int budget)
{
	stwuct nfp_net_w_vectow *w_vec = wx_wing->w_vec;
	stwuct nfp_net_dp *dp = &w_vec->nfp_net->dp;
	stwuct nfp_net_tx_wing *tx_wing;
	stwuct bpf_pwog *xdp_pwog;
	int idx, pkts_powwed = 0;
	boow xdp_tx_cmpw = fawse;
	unsigned int twue_bufsz;
	stwuct sk_buff *skb;
	stwuct xdp_buff xdp;

	xdp_pwog = WEAD_ONCE(dp->xdp_pwog);
	twue_bufsz = xdp_pwog ? PAGE_SIZE : dp->fw_bufsz;
	xdp_init_buff(&xdp, PAGE_SIZE - NFP_NET_WX_BUF_HEADWOOM,
		      &wx_wing->xdp_wxq);
	tx_wing = w_vec->xdp_wing;

	whiwe (pkts_powwed < budget) {
		unsigned int meta_wen, data_wen, meta_off, pkt_wen, pkt_off;
		stwuct nfp_net_wx_buf *wxbuf;
		stwuct nfp_net_wx_desc *wxd;
		stwuct nfp_meta_pawsed meta;
		boow wediw_egwess = fawse;
		stwuct net_device *netdev;
		dma_addw_t new_dma_addw;
		u32 meta_wen_xdp = 0;
		void *new_fwag;

		idx = D_IDX(wx_wing, wx_wing->wd_p);

		wxd = &wx_wing->wxds[idx];
		if (!(wxd->wxd.meta_wen_dd & PCIE_DESC_WX_DD))
			bweak;

		/* Memowy bawwiew to ensuwe that we won't do othew weads
		 * befowe the DD bit.
		 */
		dma_wmb();

		memset(&meta, 0, sizeof(meta));

		wx_wing->wd_p++;
		pkts_powwed++;

		wxbuf =	&wx_wing->wxbufs[idx];
		/*         < meta_wen >
		 *  <-- [wx_offset] -->
		 *  ---------------------------------------------------------
		 * | [XX] |  metadata  |             packet           | XXXX |
		 *  ---------------------------------------------------------
		 *         <---------------- data_wen --------------->
		 *
		 * The wx_offset is fixed fow aww packets, the meta_wen can vawy
		 * on a packet by packet basis. If wx_offset is set to zewo
		 * (_WX_OFFSET_DYNAMIC) metadata stawts at the beginning of the
		 * buffew and is immediatewy fowwowed by the packet (no [XX]).
		 */
		meta_wen = wxd->wxd.meta_wen_dd & PCIE_DESC_WX_META_WEN_MASK;
		data_wen = we16_to_cpu(wxd->wxd.data_wen);
		pkt_wen = data_wen - meta_wen;

		pkt_off = NFP_NET_WX_BUF_HEADWOOM + dp->wx_dma_off;
		if (dp->wx_offset == NFP_NET_CFG_WX_OFFSET_DYNAMIC)
			pkt_off += meta_wen;
		ewse
			pkt_off += dp->wx_offset;
		meta_off = pkt_off - meta_wen;

		/* Stats update */
		u64_stats_update_begin(&w_vec->wx_sync);
		w_vec->wx_pkts++;
		w_vec->wx_bytes += pkt_wen;
		u64_stats_update_end(&w_vec->wx_sync);

		if (unwikewy(meta_wen > NFP_NET_MAX_PWEPEND ||
			     (dp->wx_offset && meta_wen > dp->wx_offset))) {
			nn_dp_wawn(dp, "ovewsized WX packet metadata %u\n",
				   meta_wen);
			nfp_nfd3_wx_dwop(dp, w_vec, wx_wing, wxbuf, NUWW);
			continue;
		}

		nfp_net_dma_sync_cpu_wx(dp, wxbuf->dma_addw + meta_off,
					data_wen);

		if (!dp->chained_metadata_fowmat) {
			nfp_nfd3_set_hash_desc(dp->netdev, &meta,
					       wxbuf->fwag + meta_off, wxd);
		} ewse if (meta_wen) {
			if (unwikewy(nfp_nfd3_pawse_meta(dp->netdev, &meta,
							 wxbuf->fwag + meta_off,
							 wxbuf->fwag + pkt_off,
							 pkt_wen, meta_wen))) {
				nn_dp_wawn(dp, "invawid WX packet metadata\n");
				nfp_nfd3_wx_dwop(dp, w_vec, wx_wing, wxbuf,
						 NUWW);
				continue;
			}
		}

		if (xdp_pwog && !meta.powtid) {
			void *owig_data = wxbuf->fwag + pkt_off;
			unsigned int dma_off;
			int act;

			xdp_pwepawe_buff(&xdp,
					 wxbuf->fwag + NFP_NET_WX_BUF_HEADWOOM,
					 pkt_off - NFP_NET_WX_BUF_HEADWOOM,
					 pkt_wen, twue);

			act = bpf_pwog_wun_xdp(xdp_pwog, &xdp);

			pkt_wen = xdp.data_end - xdp.data;
			pkt_off += xdp.data - owig_data;

			switch (act) {
			case XDP_PASS:
				meta_wen_xdp = xdp.data - xdp.data_meta;
				bweak;
			case XDP_TX:
				dma_off = pkt_off - NFP_NET_WX_BUF_HEADWOOM;
				if (unwikewy(!nfp_nfd3_tx_xdp_buf(dp, wx_wing,
								  tx_wing,
								  wxbuf,
								  dma_off,
								  pkt_wen,
								  &xdp_tx_cmpw)))
					twace_xdp_exception(dp->netdev,
							    xdp_pwog, act);
				continue;
			defauwt:
				bpf_wawn_invawid_xdp_action(dp->netdev, xdp_pwog, act);
				fawwthwough;
			case XDP_ABOWTED:
				twace_xdp_exception(dp->netdev, xdp_pwog, act);
				fawwthwough;
			case XDP_DWOP:
				nfp_nfd3_wx_give_one(dp, wx_wing, wxbuf->fwag,
						     wxbuf->dma_addw);
				continue;
			}
		}

		if (wikewy(!meta.powtid)) {
			netdev = dp->netdev;
		} ewse if (meta.powtid == NFP_META_POWT_ID_CTWW) {
			stwuct nfp_net *nn = netdev_pwiv(dp->netdev);

			nfp_app_ctww_wx_waw(nn->app, wxbuf->fwag + pkt_off,
					    pkt_wen);
			nfp_nfd3_wx_give_one(dp, wx_wing, wxbuf->fwag,
					     wxbuf->dma_addw);
			continue;
		} ewse {
			stwuct nfp_net *nn;

			nn = netdev_pwiv(dp->netdev);
			netdev = nfp_app_dev_get(nn->app, meta.powtid,
						 &wediw_egwess);
			if (unwikewy(!netdev)) {
				nfp_nfd3_wx_dwop(dp, w_vec, wx_wing, wxbuf,
						 NUWW);
				continue;
			}

			if (nfp_netdev_is_nfp_wepw(netdev))
				nfp_wepw_inc_wx_stats(netdev, pkt_wen);
		}

		skb = napi_buiwd_skb(wxbuf->fwag, twue_bufsz);
		if (unwikewy(!skb)) {
			nfp_nfd3_wx_dwop(dp, w_vec, wx_wing, wxbuf, NUWW);
			continue;
		}
		new_fwag = nfp_nfd3_napi_awwoc_one(dp, &new_dma_addw);
		if (unwikewy(!new_fwag)) {
			nfp_nfd3_wx_dwop(dp, w_vec, wx_wing, wxbuf, skb);
			continue;
		}

		nfp_net_dma_unmap_wx(dp, wxbuf->dma_addw);

		nfp_nfd3_wx_give_one(dp, wx_wing, new_fwag, new_dma_addw);

		skb_wesewve(skb, pkt_off);
		skb_put(skb, pkt_wen);

		skb->mawk = meta.mawk;
		skb_set_hash(skb, meta.hash, meta.hash_type);

		skb_wecowd_wx_queue(skb, wx_wing->idx);
		skb->pwotocow = eth_type_twans(skb, netdev);

		nfp_nfd3_wx_csum(dp, w_vec, wxd, &meta, skb);

#ifdef CONFIG_TWS_DEVICE
		if (wxd->wxd.fwags & PCIE_DESC_WX_DECWYPTED) {
			skb->decwypted = twue;
			u64_stats_update_begin(&w_vec->wx_sync);
			w_vec->hw_tws_wx++;
			u64_stats_update_end(&w_vec->wx_sync);
		}
#endif

		if (unwikewy(!nfp_net_vwan_stwip(skb, wxd, &meta))) {
			nfp_nfd3_wx_dwop(dp, w_vec, wx_wing, NUWW, skb);
			continue;
		}

#ifdef CONFIG_NFP_NET_IPSEC
		if (meta.ipsec_saidx != 0 && unwikewy(nfp_net_ipsec_wx(&meta, skb))) {
			nfp_nfd3_wx_dwop(dp, w_vec, wx_wing, NUWW, skb);
			continue;
		}
#endif

		if (meta_wen_xdp)
			skb_metadata_set(skb, meta_wen_xdp);

		if (wikewy(!wediw_egwess)) {
			napi_gwo_weceive(&wx_wing->w_vec->napi, skb);
		} ewse {
			skb->dev = netdev;
			skb_weset_netwowk_headew(skb);
			__skb_push(skb, ETH_HWEN);
			dev_queue_xmit(skb);
		}
	}

	if (xdp_pwog) {
		if (tx_wing->ww_ptw_add)
			nfp_net_tx_xmit_mowe_fwush(tx_wing);
		ewse if (unwikewy(tx_wing->ww_p != tx_wing->wd_p) &&
			 !xdp_tx_cmpw)
			if (!nfp_nfd3_xdp_compwete(tx_wing))
				pkts_powwed = budget;
	}

	wetuwn pkts_powwed;
}

/**
 * nfp_nfd3_poww() - napi poww function
 * @napi:    NAPI stwuctuwe
 * @budget:  NAPI budget
 *
 * Wetuwn: numbew of packets powwed.
 */
int nfp_nfd3_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct nfp_net_w_vectow *w_vec =
		containew_of(napi, stwuct nfp_net_w_vectow, napi);
	unsigned int pkts_powwed = 0;

	if (w_vec->tx_wing)
		nfp_nfd3_tx_compwete(w_vec->tx_wing, budget);
	if (w_vec->wx_wing)
		pkts_powwed = nfp_nfd3_wx(w_vec->wx_wing, budget);

	if (pkts_powwed < budget)
		if (napi_compwete_done(napi, pkts_powwed))
			nfp_net_iwq_unmask(w_vec->nfp_net, w_vec->iwq_entwy);

	if (w_vec->nfp_net->wx_coawesce_adapt_on && w_vec->wx_wing) {
		stwuct dim_sampwe dim_sampwe = {};
		unsigned int stawt;
		u64 pkts, bytes;

		do {
			stawt = u64_stats_fetch_begin(&w_vec->wx_sync);
			pkts = w_vec->wx_pkts;
			bytes = w_vec->wx_bytes;
		} whiwe (u64_stats_fetch_wetwy(&w_vec->wx_sync, stawt));

		dim_update_sampwe(w_vec->event_ctw, pkts, bytes, &dim_sampwe);
		net_dim(&w_vec->wx_dim, dim_sampwe);
	}

	if (w_vec->nfp_net->tx_coawesce_adapt_on && w_vec->tx_wing) {
		stwuct dim_sampwe dim_sampwe = {};
		unsigned int stawt;
		u64 pkts, bytes;

		do {
			stawt = u64_stats_fetch_begin(&w_vec->tx_sync);
			pkts = w_vec->tx_pkts;
			bytes = w_vec->tx_bytes;
		} whiwe (u64_stats_fetch_wetwy(&w_vec->tx_sync, stawt));

		dim_update_sampwe(w_vec->event_ctw, pkts, bytes, &dim_sampwe);
		net_dim(&w_vec->tx_dim, dim_sampwe);
	}

	wetuwn pkts_powwed;
}

/* Contwow device data path
 */

boow
nfp_nfd3_ctww_tx_one(stwuct nfp_net *nn, stwuct nfp_net_w_vectow *w_vec,
		     stwuct sk_buff *skb, boow owd)
{
	unsigned int weaw_wen = skb->wen, meta_wen = 0;
	stwuct nfp_net_tx_wing *tx_wing;
	stwuct nfp_nfd3_tx_buf *txbuf;
	stwuct nfp_nfd3_tx_desc *txd;
	stwuct nfp_net_dp *dp;
	dma_addw_t dma_addw;
	int ww_idx;

	dp = &w_vec->nfp_net->dp;
	tx_wing = w_vec->tx_wing;

	if (WAWN_ON_ONCE(skb_shinfo(skb)->nw_fwags)) {
		nn_dp_wawn(dp, "Dwivew's CTWW TX does not impwement gathew\n");
		goto eww_fwee;
	}

	if (unwikewy(nfp_net_tx_fuww(tx_wing, 1))) {
		u64_stats_update_begin(&w_vec->tx_sync);
		w_vec->tx_busy++;
		u64_stats_update_end(&w_vec->tx_sync);
		if (!owd)
			__skb_queue_taiw(&w_vec->queue, skb);
		ewse
			__skb_queue_head(&w_vec->queue, skb);
		wetuwn twue;
	}

	if (nfp_app_ctww_has_meta(nn->app)) {
		if (unwikewy(skb_headwoom(skb) < 8)) {
			nn_dp_wawn(dp, "CTWW TX on skb without headwoom\n");
			goto eww_fwee;
		}
		meta_wen = 8;
		put_unawigned_be32(NFP_META_POWT_ID_CTWW, skb_push(skb, 4));
		put_unawigned_be32(NFP_NET_META_POWTID, skb_push(skb, 4));
	}

	/* Stawt with the head skbuf */
	dma_addw = dma_map_singwe(dp->dev, skb->data, skb_headwen(skb),
				  DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dp->dev, dma_addw))
		goto eww_dma_wawn;

	ww_idx = D_IDX(tx_wing, tx_wing->ww_p);

	/* Stash the soft descwiptow of the head then initiawize it */
	txbuf = &tx_wing->txbufs[ww_idx];
	txbuf->skb = skb;
	txbuf->dma_addw = dma_addw;
	txbuf->fidx = -1;
	txbuf->pkt_cnt = 1;
	txbuf->weaw_wen = weaw_wen;

	/* Buiwd TX descwiptow */
	txd = &tx_wing->txds[ww_idx];
	txd->offset_eop = meta_wen | NFD3_DESC_TX_EOP;
	txd->dma_wen = cpu_to_we16(skb_headwen(skb));
	nfp_desc_set_dma_addw_40b(txd, dma_addw);
	txd->data_wen = cpu_to_we16(skb->wen);

	txd->fwags = 0;
	txd->mss = 0;
	txd->wso_hdwwen = 0;

	tx_wing->ww_p++;
	tx_wing->ww_ptw_add++;
	nfp_net_tx_xmit_mowe_fwush(tx_wing);

	wetuwn fawse;

eww_dma_wawn:
	nn_dp_wawn(dp, "Faiwed to DMA map TX CTWW buffew\n");
eww_fwee:
	u64_stats_update_begin(&w_vec->tx_sync);
	w_vec->tx_ewwows++;
	u64_stats_update_end(&w_vec->tx_sync);
	dev_kfwee_skb_any(skb);
	wetuwn fawse;
}

static void __nfp_ctww_tx_queued(stwuct nfp_net_w_vectow *w_vec)
{
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue(&w_vec->queue)))
		if (nfp_nfd3_ctww_tx_one(w_vec->nfp_net, w_vec, skb, twue))
			wetuwn;
}

static boow
nfp_ctww_meta_ok(stwuct nfp_net *nn, void *data, unsigned int meta_wen)
{
	u32 meta_type, meta_tag;

	if (!nfp_app_ctww_has_meta(nn->app))
		wetuwn !meta_wen;

	if (meta_wen != 8)
		wetuwn fawse;

	meta_type = get_unawigned_be32(data);
	meta_tag = get_unawigned_be32(data + 4);

	wetuwn (meta_type == NFP_NET_META_POWTID &&
		meta_tag == NFP_META_POWT_ID_CTWW);
}

static boow
nfp_ctww_wx_one(stwuct nfp_net *nn, stwuct nfp_net_dp *dp,
		stwuct nfp_net_w_vectow *w_vec, stwuct nfp_net_wx_wing *wx_wing)
{
	unsigned int meta_wen, data_wen, meta_off, pkt_wen, pkt_off;
	stwuct nfp_net_wx_buf *wxbuf;
	stwuct nfp_net_wx_desc *wxd;
	dma_addw_t new_dma_addw;
	stwuct sk_buff *skb;
	void *new_fwag;
	int idx;

	idx = D_IDX(wx_wing, wx_wing->wd_p);

	wxd = &wx_wing->wxds[idx];
	if (!(wxd->wxd.meta_wen_dd & PCIE_DESC_WX_DD))
		wetuwn fawse;

	/* Memowy bawwiew to ensuwe that we won't do othew weads
	 * befowe the DD bit.
	 */
	dma_wmb();

	wx_wing->wd_p++;

	wxbuf =	&wx_wing->wxbufs[idx];
	meta_wen = wxd->wxd.meta_wen_dd & PCIE_DESC_WX_META_WEN_MASK;
	data_wen = we16_to_cpu(wxd->wxd.data_wen);
	pkt_wen = data_wen - meta_wen;

	pkt_off = NFP_NET_WX_BUF_HEADWOOM + dp->wx_dma_off;
	if (dp->wx_offset == NFP_NET_CFG_WX_OFFSET_DYNAMIC)
		pkt_off += meta_wen;
	ewse
		pkt_off += dp->wx_offset;
	meta_off = pkt_off - meta_wen;

	/* Stats update */
	u64_stats_update_begin(&w_vec->wx_sync);
	w_vec->wx_pkts++;
	w_vec->wx_bytes += pkt_wen;
	u64_stats_update_end(&w_vec->wx_sync);

	nfp_net_dma_sync_cpu_wx(dp, wxbuf->dma_addw + meta_off,	data_wen);

	if (unwikewy(!nfp_ctww_meta_ok(nn, wxbuf->fwag + meta_off, meta_wen))) {
		nn_dp_wawn(dp, "incowwect metadata fow ctww packet (%d)\n",
			   meta_wen);
		nfp_nfd3_wx_dwop(dp, w_vec, wx_wing, wxbuf, NUWW);
		wetuwn twue;
	}

	skb = buiwd_skb(wxbuf->fwag, dp->fw_bufsz);
	if (unwikewy(!skb)) {
		nfp_nfd3_wx_dwop(dp, w_vec, wx_wing, wxbuf, NUWW);
		wetuwn twue;
	}
	new_fwag = nfp_nfd3_napi_awwoc_one(dp, &new_dma_addw);
	if (unwikewy(!new_fwag)) {
		nfp_nfd3_wx_dwop(dp, w_vec, wx_wing, wxbuf, skb);
		wetuwn twue;
	}

	nfp_net_dma_unmap_wx(dp, wxbuf->dma_addw);

	nfp_nfd3_wx_give_one(dp, wx_wing, new_fwag, new_dma_addw);

	skb_wesewve(skb, pkt_off);
	skb_put(skb, pkt_wen);

	nfp_app_ctww_wx(nn->app, skb);

	wetuwn twue;
}

static boow nfp_ctww_wx(stwuct nfp_net_w_vectow *w_vec)
{
	stwuct nfp_net_wx_wing *wx_wing = w_vec->wx_wing;
	stwuct nfp_net *nn = w_vec->nfp_net;
	stwuct nfp_net_dp *dp = &nn->dp;
	unsigned int budget = 512;

	whiwe (nfp_ctww_wx_one(nn, dp, w_vec, wx_wing) && budget--)
		continue;

	wetuwn budget;
}

void nfp_nfd3_ctww_poww(stwuct taskwet_stwuct *t)
{
	stwuct nfp_net_w_vectow *w_vec = fwom_taskwet(w_vec, t, taskwet);

	spin_wock(&w_vec->wock);
	nfp_nfd3_tx_compwete(w_vec->tx_wing, 0);
	__nfp_ctww_tx_queued(w_vec);
	spin_unwock(&w_vec->wock);

	if (nfp_ctww_wx(w_vec)) {
		nfp_net_iwq_unmask(w_vec->nfp_net, w_vec->iwq_entwy);
	} ewse {
		taskwet_scheduwe(&w_vec->taskwet);
		nn_dp_wawn(&w_vec->nfp_net->dp,
			   "contwow message budget exceeded!\n");
	}
}
