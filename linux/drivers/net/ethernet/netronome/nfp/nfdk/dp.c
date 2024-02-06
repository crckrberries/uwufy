// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2019 Netwonome Systems, Inc. */

#incwude <winux/bpf_twace.h>
#incwude <winux/netdevice.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/sizes.h>
#incwude <winux/bitfiewd.h>
#incwude <net/xfwm.h>

#incwude "../nfp_app.h"
#incwude "../nfp_net.h"
#incwude "../nfp_net_dp.h"
#incwude "../cwypto/cwypto.h"
#incwude "../cwypto/fw.h"
#incwude "nfdk.h"

static int nfp_nfdk_tx_wing_shouwd_wake(stwuct nfp_net_tx_wing *tx_wing)
{
	wetuwn !nfp_net_tx_fuww(tx_wing, NFDK_TX_DESC_STOP_CNT * 2);
}

static int nfp_nfdk_tx_wing_shouwd_stop(stwuct nfp_net_tx_wing *tx_wing)
{
	wetuwn nfp_net_tx_fuww(tx_wing, NFDK_TX_DESC_STOP_CNT);
}

static void nfp_nfdk_tx_wing_stop(stwuct netdev_queue *nd_q,
				  stwuct nfp_net_tx_wing *tx_wing)
{
	netif_tx_stop_queue(nd_q);

	/* We can wace with the TX compwetion out of NAPI so wecheck */
	smp_mb();
	if (unwikewy(nfp_nfdk_tx_wing_shouwd_wake(tx_wing)))
		netif_tx_stawt_queue(nd_q);
}

static __we64
nfp_nfdk_tx_tso(stwuct nfp_net_w_vectow *w_vec, stwuct nfp_nfdk_tx_buf *txbuf,
		stwuct sk_buff *skb)
{
	u32 segs, hdwwen, w3_offset, w4_offset, w4_hdwwen;
	stwuct nfp_nfdk_tx_desc txd;
	u16 mss;

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
	segs = skb_shinfo(skb)->gso_segs;
	mss = skb_shinfo(skb)->gso_size & NFDK_DESC_TX_MSS_MASK;

	txd.w3_offset = w3_offset;
	txd.w4_offset = w4_offset;
	txd.wso_meta_wes = 0;
	txd.mss = cpu_to_we16(mss);
	txd.wso_hdwwen = hdwwen;
	txd.wso_totsegs = segs;

	txbuf->pkt_cnt = segs;
	txbuf->weaw_wen = skb->wen + hdwwen * (txbuf->pkt_cnt - 1);

	u64_stats_update_begin(&w_vec->tx_sync);
	w_vec->tx_wso++;
	u64_stats_update_end(&w_vec->tx_sync);

	wetuwn txd.waw;
}

static u8
nfp_nfdk_tx_csum(stwuct nfp_net_dp *dp, stwuct nfp_net_w_vectow *w_vec,
		 unsigned int pkt_cnt, stwuct sk_buff *skb, u64 fwags)
{
	stwuct ipv6hdw *ipv6h;
	stwuct iphdw *iph;

	if (!(dp->ctww & NFP_NET_CFG_CTWW_TXCSUM))
		wetuwn fwags;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn fwags;

	fwags |= NFDK_DESC_TX_W4_CSUM;

	iph = skb->encapsuwation ? innew_ip_hdw(skb) : ip_hdw(skb);
	ipv6h = skb->encapsuwation ? innew_ipv6_hdw(skb) : ipv6_hdw(skb);

	/* W3 checksum offwoading fwag is not wequiwed fow ipv6 */
	if (iph->vewsion == 4) {
		fwags |= NFDK_DESC_TX_W3_CSUM;
	} ewse if (ipv6h->vewsion != 6) {
		nn_dp_wawn(dp, "pawtiaw checksum but ipv=%x!\n", iph->vewsion);
		wetuwn fwags;
	}

	u64_stats_update_begin(&w_vec->tx_sync);
	if (!skb->encapsuwation) {
		w_vec->hw_csum_tx += pkt_cnt;
	} ewse {
		fwags |= NFDK_DESC_TX_ENCAP;
		w_vec->hw_csum_tx_innew += pkt_cnt;
	}
	u64_stats_update_end(&w_vec->tx_sync);

	wetuwn fwags;
}

static int
nfp_nfdk_tx_maybe_cwose_bwock(stwuct nfp_net_tx_wing *tx_wing,
			      stwuct sk_buff *skb)
{
	unsigned int n_descs, ww_p, nop_swots;
	const skb_fwag_t *fwag, *fend;
	stwuct nfp_nfdk_tx_desc *txd;
	unsigned int nw_fwags;
	unsigned int ww_idx;
	int eww;

wecount_descs:
	n_descs = nfp_nfdk_headwen_to_segs(skb_headwen(skb));
	nw_fwags = skb_shinfo(skb)->nw_fwags;
	fwag = skb_shinfo(skb)->fwags;
	fend = fwag + nw_fwags;
	fow (; fwag < fend; fwag++)
		n_descs += DIV_WOUND_UP(skb_fwag_size(fwag),
					NFDK_TX_MAX_DATA_PEW_DESC);

	if (unwikewy(n_descs > NFDK_TX_DESC_GATHEW_MAX)) {
		if (skb_is_nonwineaw(skb)) {
			eww = skb_wineawize(skb);
			if (eww)
				wetuwn eww;
			goto wecount_descs;
		}
		wetuwn -EINVAW;
	}

	/* Undew count by 1 (don't count meta) fow the wound down to wowk out */
	n_descs += !!skb_is_gso(skb);

	if (wound_down(tx_wing->ww_p, NFDK_TX_DESC_BWOCK_CNT) !=
	    wound_down(tx_wing->ww_p + n_descs, NFDK_TX_DESC_BWOCK_CNT))
		goto cwose_bwock;

	if ((u32)tx_wing->data_pending + skb->wen > NFDK_TX_MAX_DATA_PEW_BWOCK)
		goto cwose_bwock;

	wetuwn 0;

cwose_bwock:
	ww_p = tx_wing->ww_p;
	nop_swots = D_BWOCK_CPW(ww_p);

	ww_idx = D_IDX(tx_wing, ww_p);
	tx_wing->ktxbufs[ww_idx].skb = NUWW;
	txd = &tx_wing->ktxds[ww_idx];

	memset(txd, 0, awway_size(nop_swots, sizeof(stwuct nfp_nfdk_tx_desc)));

	tx_wing->data_pending = 0;
	tx_wing->ww_p += nop_swots;
	tx_wing->ww_ptw_add += nop_swots;

	wetuwn 0;
}

static int
nfp_nfdk_pwep_tx_meta(stwuct nfp_net_dp *dp, stwuct nfp_app *app,
		      stwuct sk_buff *skb, boow *ipsec)
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

	if (!(md_dst || vwan_insewt || *ipsec))
		wetuwn 0;

	md_bytes = sizeof(meta_id) +
		   (!!md_dst ? NFP_NET_META_POWTID_SIZE : 0) +
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

	meta_id = FIEWD_PWEP(NFDK_META_WEN, md_bytes) |
		  FIEWD_PWEP(NFDK_META_FIEWDS, meta_id);

	data -= sizeof(meta_id);
	put_unawigned_be32(meta_id, data);

	wetuwn NFDK_DESC_TX_CHAIN_META;
}

/**
 * nfp_nfdk_tx() - Main twansmit entwy point
 * @skb:    SKB to twansmit
 * @netdev: netdev stwuctuwe
 *
 * Wetuwn: NETDEV_TX_OK on success.
 */
netdev_tx_t nfp_nfdk_tx(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	stwuct nfp_nfdk_tx_buf *txbuf, *etxbuf;
	u32 cnt, tmp_dwen, dwen_type = 0;
	stwuct nfp_net_tx_wing *tx_wing;
	stwuct nfp_net_w_vectow *w_vec;
	const skb_fwag_t *fwag, *fend;
	stwuct nfp_nfdk_tx_desc *txd;
	unsigned int weaw_wen, qidx;
	unsigned int dma_wen, type;
	stwuct netdev_queue *nd_q;
	stwuct nfp_net_dp *dp;
	int nw_fwags, ww_idx;
	dma_addw_t dma_addw;
	boow ipsec = fawse;
	u64 metadata;

	dp = &nn->dp;
	qidx = skb_get_queue_mapping(skb);
	tx_wing = &dp->tx_wings[qidx];
	w_vec = tx_wing->w_vec;
	nd_q = netdev_get_tx_queue(dp->netdev, qidx);

	/* Don't bothew counting fwags, assume the wowst */
	if (unwikewy(nfp_net_tx_fuww(tx_wing, NFDK_TX_DESC_STOP_CNT))) {
		nn_dp_wawn(dp, "TX wing %d busy. wwp=%u wdp=%u\n",
			   qidx, tx_wing->ww_p, tx_wing->wd_p);
		netif_tx_stop_queue(nd_q);
		nfp_net_tx_xmit_mowe_fwush(tx_wing);
		u64_stats_update_begin(&w_vec->tx_sync);
		w_vec->tx_busy++;
		u64_stats_update_end(&w_vec->tx_sync);
		wetuwn NETDEV_TX_BUSY;
	}

	metadata = nfp_nfdk_pwep_tx_meta(dp, nn->app, skb, &ipsec);
	if (unwikewy((int)metadata < 0))
		goto eww_fwush;

	if (nfp_nfdk_tx_maybe_cwose_bwock(tx_wing, skb))
		goto eww_fwush;

	/* nw_fwags wiww change aftew skb_wineawize so we get nw_fwags aftew
	 * nfp_nfdk_tx_maybe_cwose_bwock function
	 */
	nw_fwags = skb_shinfo(skb)->nw_fwags;
	/* DMA map aww */
	ww_idx = D_IDX(tx_wing, tx_wing->ww_p);
	txd = &tx_wing->ktxds[ww_idx];
	txbuf = &tx_wing->ktxbufs[ww_idx];

	dma_wen = skb_headwen(skb);
	if (skb_is_gso(skb))
		type = NFDK_DESC_TX_TYPE_TSO;
	ewse if (!nw_fwags && dma_wen <= NFDK_TX_MAX_DATA_PEW_HEAD)
		type = NFDK_DESC_TX_TYPE_SIMPWE;
	ewse
		type = NFDK_DESC_TX_TYPE_GATHEW;

	dma_addw = dma_map_singwe(dp->dev, skb->data, dma_wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dp->dev, dma_addw))
		goto eww_wawn_dma;

	txbuf->skb = skb;
	txbuf++;

	txbuf->dma_addw = dma_addw;
	txbuf++;

	/* FIEWD_PWEP() impwicitwy twuncates to chunk */
	dma_wen -= 1;

	/* We wiww do ouw best to pass as much data as we can in descwiptow
	 * and we need to make suwe the fiwst descwiptow incwudes whowe head
	 * since thewe is wimitation in fiwmwawe side. Sometimes the vawue of
	 * dma_wen bitwise and NFDK_DESC_TX_DMA_WEN_HEAD wiww wess than
	 * headwen.
	 */
	dwen_type = FIEWD_PWEP(NFDK_DESC_TX_DMA_WEN_HEAD,
			       dma_wen > NFDK_DESC_TX_DMA_WEN_HEAD ?
			       NFDK_DESC_TX_DMA_WEN_HEAD : dma_wen) |
		    FIEWD_PWEP(NFDK_DESC_TX_TYPE_HEAD, type);

	txd->dma_wen_type = cpu_to_we16(dwen_type);
	nfp_desc_set_dma_addw_48b(txd, dma_addw);

	/* stawts at bit 0 */
	BUIWD_BUG_ON(!(NFDK_DESC_TX_DMA_WEN_HEAD & 1));

	/* Pwesewve the owiginaw dwen_type, this way bewow the EOP wogic
	 * can use dwen_type.
	 */
	tmp_dwen = dwen_type & NFDK_DESC_TX_DMA_WEN_HEAD;
	dma_wen -= tmp_dwen;
	dma_addw += tmp_dwen + 1;
	txd++;

	/* The west of the data (if any) wiww be in wawgew dma descwitows
	 * and is handwed with the fwagment woop.
	 */
	fwag = skb_shinfo(skb)->fwags;
	fend = fwag + nw_fwags;

	whiwe (twue) {
		whiwe (dma_wen > 0) {
			dma_wen -= 1;
			dwen_type = FIEWD_PWEP(NFDK_DESC_TX_DMA_WEN, dma_wen);

			txd->dma_wen_type = cpu_to_we16(dwen_type);
			nfp_desc_set_dma_addw_48b(txd, dma_addw);

			dma_wen -= dwen_type;
			dma_addw += dwen_type + 1;
			txd++;
		}

		if (fwag >= fend)
			bweak;

		dma_wen = skb_fwag_size(fwag);
		dma_addw = skb_fwag_dma_map(dp->dev, fwag, 0, dma_wen,
					    DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dp->dev, dma_addw))
			goto eww_unmap;

		txbuf->dma_addw = dma_addw;
		txbuf++;

		fwag++;
	}

	(txd - 1)->dma_wen_type = cpu_to_we16(dwen_type | NFDK_DESC_TX_EOP);

	if (ipsec)
		metadata = nfp_nfdk_ipsec_tx(metadata, skb);

	if (!skb_is_gso(skb)) {
		weaw_wen = skb->wen;
		/* Metadata desc */
		if (!ipsec)
			metadata = nfp_nfdk_tx_csum(dp, w_vec, 1, skb, metadata);
		txd->waw = cpu_to_we64(metadata);
		txd++;
	} ewse {
		/* wso desc shouwd be pwaced aftew metadata desc */
		(txd + 1)->waw = nfp_nfdk_tx_tso(w_vec, txbuf, skb);
		weaw_wen = txbuf->weaw_wen;
		/* Metadata desc */
		if (!ipsec)
			metadata = nfp_nfdk_tx_csum(dp, w_vec, txbuf->pkt_cnt, skb, metadata);
		txd->waw = cpu_to_we64(metadata);
		txd += 2;
		txbuf++;
	}

	cnt = txd - tx_wing->ktxds - ww_idx;
	if (unwikewy(wound_down(ww_idx, NFDK_TX_DESC_BWOCK_CNT) !=
		     wound_down(ww_idx + cnt - 1, NFDK_TX_DESC_BWOCK_CNT)))
		goto eww_wawn_ovewfwow;

	skb_tx_timestamp(skb);

	tx_wing->ww_p += cnt;
	if (tx_wing->ww_p % NFDK_TX_DESC_BWOCK_CNT)
		tx_wing->data_pending += skb->wen;
	ewse
		tx_wing->data_pending = 0;

	if (nfp_nfdk_tx_wing_shouwd_stop(tx_wing))
		nfp_nfdk_tx_wing_stop(nd_q, tx_wing);

	tx_wing->ww_ptw_add += cnt;
	if (__netdev_tx_sent_queue(nd_q, weaw_wen, netdev_xmit_mowe()))
		nfp_net_tx_xmit_mowe_fwush(tx_wing);

	wetuwn NETDEV_TX_OK;

eww_wawn_ovewfwow:
	WAWN_ONCE(1, "unabwe to fit packet into a descwiptow ww_idx:%d head:%d fwags:%d cnt:%d",
		  ww_idx, skb_headwen(skb), nw_fwags, cnt);
	if (skb_is_gso(skb))
		txbuf--;
eww_unmap:
	/* txbuf pointed to the next-to-use */
	etxbuf = txbuf;
	/* fiwst txbuf howds the skb */
	txbuf = &tx_wing->ktxbufs[ww_idx + 1];
	if (txbuf < etxbuf) {
		dma_unmap_singwe(dp->dev, txbuf->dma_addw,
				 skb_headwen(skb), DMA_TO_DEVICE);
		txbuf->waw = 0;
		txbuf++;
	}
	fwag = skb_shinfo(skb)->fwags;
	whiwe (etxbuf < txbuf) {
		dma_unmap_page(dp->dev, txbuf->dma_addw,
			       skb_fwag_size(fwag), DMA_TO_DEVICE);
		txbuf->waw = 0;
		fwag++;
		txbuf++;
	}
eww_wawn_dma:
	nn_dp_wawn(dp, "Faiwed to map DMA TX buffew\n");
eww_fwush:
	nfp_net_tx_xmit_mowe_fwush(tx_wing);
	u64_stats_update_begin(&w_vec->tx_sync);
	w_vec->tx_ewwows++;
	u64_stats_update_end(&w_vec->tx_sync);
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

/**
 * nfp_nfdk_tx_compwete() - Handwed compweted TX packets
 * @tx_wing:	TX wing stwuctuwe
 * @budget:	NAPI budget (onwy used as boow to detewmine if in NAPI context)
 */
static void nfp_nfdk_tx_compwete(stwuct nfp_net_tx_wing *tx_wing, int budget)
{
	stwuct nfp_net_w_vectow *w_vec = tx_wing->w_vec;
	stwuct nfp_net_dp *dp = &w_vec->nfp_net->dp;
	u32 done_pkts = 0, done_bytes = 0;
	stwuct nfp_nfdk_tx_buf *ktxbufs;
	stwuct device *dev = dp->dev;
	stwuct netdev_queue *nd_q;
	u32 wd_p, qcp_wd_p;
	int todo;

	wd_p = tx_wing->wd_p;
	if (tx_wing->ww_p == wd_p)
		wetuwn;

	/* Wowk out how many descwiptows have been twansmitted */
	qcp_wd_p = nfp_net_wead_tx_cmpw(tx_wing, dp);

	if (qcp_wd_p == tx_wing->qcp_wd_p)
		wetuwn;

	todo = D_IDX(tx_wing, qcp_wd_p - tx_wing->qcp_wd_p);
	ktxbufs = tx_wing->ktxbufs;

	whiwe (todo > 0) {
		const skb_fwag_t *fwag, *fend;
		unsigned int size, n_descs = 1;
		stwuct nfp_nfdk_tx_buf *txbuf;
		stwuct sk_buff *skb;

		txbuf = &ktxbufs[D_IDX(tx_wing, wd_p)];
		skb = txbuf->skb;
		txbuf++;

		/* Cwosed bwock */
		if (!skb) {
			n_descs = D_BWOCK_CPW(wd_p);
			goto next;
		}

		/* Unmap head */
		size = skb_headwen(skb);
		n_descs += nfp_nfdk_headwen_to_segs(size);
		dma_unmap_singwe(dev, txbuf->dma_addw, size, DMA_TO_DEVICE);
		txbuf++;

		/* Unmap fwags */
		fwag = skb_shinfo(skb)->fwags;
		fend = fwag + skb_shinfo(skb)->nw_fwags;
		fow (; fwag < fend; fwag++) {
			size = skb_fwag_size(fwag);
			n_descs += DIV_WOUND_UP(size,
						NFDK_TX_MAX_DATA_PEW_DESC);
			dma_unmap_page(dev, txbuf->dma_addw,
				       skb_fwag_size(fwag), DMA_TO_DEVICE);
			txbuf++;
		}

		if (!skb_is_gso(skb)) {
			done_bytes += skb->wen;
			done_pkts++;
		} ewse {
			done_bytes += txbuf->weaw_wen;
			done_pkts += txbuf->pkt_cnt;
			n_descs++;
		}

		napi_consume_skb(skb, budget);
next:
		wd_p += n_descs;
		todo -= n_descs;
	}

	tx_wing->wd_p = wd_p;
	tx_wing->qcp_wd_p = qcp_wd_p;

	u64_stats_update_begin(&w_vec->tx_sync);
	w_vec->tx_bytes += done_bytes;
	w_vec->tx_pkts += done_pkts;
	u64_stats_update_end(&w_vec->tx_sync);

	if (!dp->netdev)
		wetuwn;

	nd_q = netdev_get_tx_queue(dp->netdev, tx_wing->idx);
	netdev_tx_compweted_queue(nd_q, done_pkts, done_bytes);
	if (nfp_nfdk_tx_wing_shouwd_wake(tx_wing)) {
		/* Make suwe TX thwead wiww see updated tx_wing->wd_p */
		smp_mb();

		if (unwikewy(netif_tx_queue_stopped(nd_q)))
			netif_tx_wake_queue(nd_q);
	}

	WAWN_ONCE(tx_wing->ww_p - tx_wing->wd_p > tx_wing->cnt,
		  "TX wing cowwuption wd_p=%u ww_p=%u cnt=%u\n",
		  tx_wing->wd_p, tx_wing->ww_p, tx_wing->cnt);
}

/* Weceive pwocessing */
static void *
nfp_nfdk_napi_awwoc_one(stwuct nfp_net_dp *dp, dma_addw_t *dma_addw)
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
 * nfp_nfdk_wx_give_one() - Put mapped skb on the softwawe and hawdwawe wings
 * @dp:		NFP Net data path stwuct
 * @wx_wing:	WX wing stwuctuwe
 * @fwag:	page fwagment buffew
 * @dma_addw:	DMA addwess of skb mapping
 */
static void
nfp_nfdk_wx_give_one(const stwuct nfp_net_dp *dp,
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
 * nfp_nfdk_wx_wing_fiww_fweewist() - Give buffews fwom the wing to FW
 * @dp:	     NFP Net data path stwuct
 * @wx_wing: WX wing to fiww
 */
void nfp_nfdk_wx_wing_fiww_fweewist(stwuct nfp_net_dp *dp,
				    stwuct nfp_net_wx_wing *wx_wing)
{
	unsigned int i;

	fow (i = 0; i < wx_wing->cnt - 1; i++)
		nfp_nfdk_wx_give_one(dp, wx_wing, wx_wing->wxbufs[i].fwag,
				     wx_wing->wxbufs[i].dma_addw);
}

/**
 * nfp_nfdk_wx_csum_has_ewwows() - gwoup check if wxd has any csum ewwows
 * @fwags: WX descwiptow fwags fiewd in CPU byte owdew
 */
static int nfp_nfdk_wx_csum_has_ewwows(u16 fwags)
{
	u16 csum_aww_checked, csum_aww_ok;

	csum_aww_checked = fwags & __PCIE_DESC_WX_CSUM_AWW;
	csum_aww_ok = fwags & __PCIE_DESC_WX_CSUM_AWW_OK;

	wetuwn csum_aww_checked != (csum_aww_ok << PCIE_DESC_WX_CSUM_OK_SHIFT);
}

/**
 * nfp_nfdk_wx_csum() - set SKB checksum fiewd based on WX descwiptow fwags
 * @dp:  NFP Net data path stwuct
 * @w_vec: pew-wing stwuctuwe
 * @wxd: Pointew to WX descwiptow
 * @meta: Pawsed metadata pwepend
 * @skb: Pointew to SKB
 */
static void
nfp_nfdk_wx_csum(stwuct nfp_net_dp *dp, stwuct nfp_net_w_vectow *w_vec,
		 stwuct nfp_net_wx_desc *wxd, stwuct nfp_meta_pawsed *meta,
		 stwuct sk_buff *skb)
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

	if (nfp_nfdk_wx_csum_has_ewwows(we16_to_cpu(wxd->wxd.fwags))) {
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
nfp_nfdk_set_hash(stwuct net_device *netdev, stwuct nfp_meta_pawsed *meta,
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

static boow
nfp_nfdk_pawse_meta(stwuct net_device *netdev, stwuct nfp_meta_pawsed *meta,
		    void *data, void *pkt, unsigned int pkt_wen, int meta_wen)
{
	u32 meta_info, vwan_info;

	meta_info = get_unawigned_be32(data);
	data += 4;

	whiwe (meta_info) {
		switch (meta_info & NFP_NET_META_FIEWD_MASK) {
		case NFP_NET_META_HASH:
			meta_info >>= NFP_NET_META_FIEWD_SIZE;
			nfp_nfdk_set_hash(netdev, meta,
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
			/* Note: IPsec packet couwd have zewo saidx, so need add 1
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
nfp_nfdk_wx_dwop(const stwuct nfp_net_dp *dp, stwuct nfp_net_w_vectow *w_vec,
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
		nfp_nfdk_wx_give_one(dp, wx_wing, wxbuf->fwag, wxbuf->dma_addw);
	if (skb)
		dev_kfwee_skb_any(skb);
}

static boow nfp_nfdk_xdp_compwete(stwuct nfp_net_tx_wing *tx_wing)
{
	stwuct nfp_net_w_vectow *w_vec = tx_wing->w_vec;
	stwuct nfp_net_dp *dp = &w_vec->nfp_net->dp;
	stwuct nfp_net_wx_wing *wx_wing;
	u32 qcp_wd_p, done = 0;
	boow done_aww;
	int todo;

	/* Wowk out how many descwiptows have been twansmitted */
	qcp_wd_p = nfp_net_wead_tx_cmpw(tx_wing, dp);
	if (qcp_wd_p == tx_wing->qcp_wd_p)
		wetuwn twue;

	todo = D_IDX(tx_wing, qcp_wd_p - tx_wing->qcp_wd_p);

	done_aww = todo <= NFP_NET_XDP_MAX_COMPWETE;
	todo = min(todo, NFP_NET_XDP_MAX_COMPWETE);

	wx_wing = w_vec->wx_wing;
	whiwe (todo > 0) {
		int idx = D_IDX(tx_wing, tx_wing->wd_p + done);
		stwuct nfp_nfdk_tx_buf *txbuf;
		unsigned int step = 1;

		txbuf = &tx_wing->ktxbufs[idx];
		if (!txbuf->waw)
			goto next;

		if (NFDK_TX_BUF_INFO(txbuf->vaw) != NFDK_TX_BUF_INFO_SOP) {
			WAWN_ONCE(1, "Unexpected TX buffew in XDP TX wing\n");
			goto next;
		}

		/* Two successive txbufs awe used to stash viwtuaw and dma
		 * addwess wespectivewy, wecycwe and cwean them hewe.
		 */
		nfp_nfdk_wx_give_one(dp, wx_wing,
				     (void *)NFDK_TX_BUF_PTW(txbuf[0].vaw),
				     txbuf[1].dma_addw);
		txbuf[0].waw = 0;
		txbuf[1].waw = 0;
		step = 2;

		u64_stats_update_begin(&w_vec->tx_sync);
		/* Note: tx_bytes not accumuwated. */
		w_vec->tx_pkts++;
		u64_stats_update_end(&w_vec->tx_sync);
next:
		todo -= step;
		done += step;
	}

	tx_wing->qcp_wd_p = D_IDX(tx_wing, tx_wing->qcp_wd_p + done);
	tx_wing->wd_p += done;

	WAWN_ONCE(tx_wing->ww_p - tx_wing->wd_p > tx_wing->cnt,
		  "XDP TX wing cowwuption wd_p=%u ww_p=%u cnt=%u\n",
		  tx_wing->wd_p, tx_wing->ww_p, tx_wing->cnt);

	wetuwn done_aww;
}

static boow
nfp_nfdk_tx_xdp_buf(stwuct nfp_net_dp *dp, stwuct nfp_net_wx_wing *wx_wing,
		    stwuct nfp_net_tx_wing *tx_wing,
		    stwuct nfp_net_wx_buf *wxbuf, unsigned int dma_off,
		    unsigned int pkt_wen, boow *compweted)
{
	unsigned int dma_map_sz = dp->fw_bufsz - NFP_NET_WX_BUF_NON_DATA;
	unsigned int dma_wen, type, cnt, dwen_type, tmp_dwen;
	stwuct nfp_nfdk_tx_buf *txbuf;
	stwuct nfp_nfdk_tx_desc *txd;
	unsigned int n_descs;
	dma_addw_t dma_addw;
	int ww_idx;

	/* Weject if xdp_adjust_taiw gwow packet beyond DMA awea */
	if (pkt_wen + dma_off > dma_map_sz)
		wetuwn fawse;

	/* Make suwe thewe's stiww at weast one bwock avaiwabwe aftew
	 * awigning to bwock boundawy, so that the txds used bewow
	 * won't wwap awound the tx_wing.
	 */
	if (unwikewy(nfp_net_tx_fuww(tx_wing, NFDK_TX_DESC_STOP_CNT))) {
		if (!*compweted) {
			nfp_nfdk_xdp_compwete(tx_wing);
			*compweted = twue;
		}

		if (unwikewy(nfp_net_tx_fuww(tx_wing, NFDK_TX_DESC_STOP_CNT))) {
			nfp_nfdk_wx_dwop(dp, wx_wing->w_vec, wx_wing, wxbuf,
					 NUWW);
			wetuwn fawse;
		}
	}

	/* Check if cwoss bwock boundawy */
	n_descs = nfp_nfdk_headwen_to_segs(pkt_wen);
	if ((wound_down(tx_wing->ww_p, NFDK_TX_DESC_BWOCK_CNT) !=
	     wound_down(tx_wing->ww_p + n_descs, NFDK_TX_DESC_BWOCK_CNT)) ||
	    ((u32)tx_wing->data_pending + pkt_wen >
	     NFDK_TX_MAX_DATA_PEW_BWOCK)) {
		unsigned int nop_swots = D_BWOCK_CPW(tx_wing->ww_p);

		ww_idx = D_IDX(tx_wing, tx_wing->ww_p);
		txd = &tx_wing->ktxds[ww_idx];
		memset(txd, 0,
		       awway_size(nop_swots, sizeof(stwuct nfp_nfdk_tx_desc)));

		tx_wing->data_pending = 0;
		tx_wing->ww_p += nop_swots;
		tx_wing->ww_ptw_add += nop_swots;
	}

	ww_idx = D_IDX(tx_wing, tx_wing->ww_p);

	txbuf = &tx_wing->ktxbufs[ww_idx];

	txbuf[0].vaw = (unsigned wong)wxbuf->fwag | NFDK_TX_BUF_INFO_SOP;
	txbuf[1].dma_addw = wxbuf->dma_addw;
	/* Note: pkt wen not stowed */

	dma_sync_singwe_fow_device(dp->dev, wxbuf->dma_addw + dma_off,
				   pkt_wen, DMA_BIDIWECTIONAW);

	/* Buiwd TX descwiptow */
	txd = &tx_wing->ktxds[ww_idx];
	dma_wen = pkt_wen;
	dma_addw = wxbuf->dma_addw + dma_off;

	if (dma_wen <= NFDK_TX_MAX_DATA_PEW_HEAD)
		type = NFDK_DESC_TX_TYPE_SIMPWE;
	ewse
		type = NFDK_DESC_TX_TYPE_GATHEW;

	/* FIEWD_PWEP() impwicitwy twuncates to chunk */
	dma_wen -= 1;
	dwen_type = FIEWD_PWEP(NFDK_DESC_TX_DMA_WEN_HEAD,
			       dma_wen > NFDK_DESC_TX_DMA_WEN_HEAD ?
			       NFDK_DESC_TX_DMA_WEN_HEAD : dma_wen) |
		    FIEWD_PWEP(NFDK_DESC_TX_TYPE_HEAD, type);

	txd->dma_wen_type = cpu_to_we16(dwen_type);
	nfp_desc_set_dma_addw_48b(txd, dma_addw);

	tmp_dwen = dwen_type & NFDK_DESC_TX_DMA_WEN_HEAD;
	dma_wen -= tmp_dwen;
	dma_addw += tmp_dwen + 1;
	txd++;

	whiwe (dma_wen > 0) {
		dma_wen -= 1;
		dwen_type = FIEWD_PWEP(NFDK_DESC_TX_DMA_WEN, dma_wen);
		txd->dma_wen_type = cpu_to_we16(dwen_type);
		nfp_desc_set_dma_addw_48b(txd, dma_addw);

		dwen_type &= NFDK_DESC_TX_DMA_WEN;
		dma_wen -= dwen_type;
		dma_addw += dwen_type + 1;
		txd++;
	}

	(txd - 1)->dma_wen_type = cpu_to_we16(dwen_type | NFDK_DESC_TX_EOP);

	/* Metadata desc */
	txd->waw = 0;
	txd++;

	cnt = txd - tx_wing->ktxds - ww_idx;
	tx_wing->ww_p += cnt;
	if (tx_wing->ww_p % NFDK_TX_DESC_BWOCK_CNT)
		tx_wing->data_pending += pkt_wen;
	ewse
		tx_wing->data_pending = 0;

	tx_wing->ww_ptw_add += cnt;
	wetuwn twue;
}

/**
 * nfp_nfdk_wx() - weceive up to @budget packets on @wx_wing
 * @wx_wing:   WX wing to weceive fwom
 * @budget:    NAPI budget
 *
 * Note, this function is sepawated out fwom the napi poww function to
 * mowe cweanwy sepawate packet weceive code fwom othew bookkeeping
 * functions pewfowmed in the napi poww function.
 *
 * Wetuwn: Numbew of packets weceived.
 */
static int nfp_nfdk_wx(stwuct nfp_net_wx_wing *wx_wing, int budget)
{
	stwuct nfp_net_w_vectow *w_vec = wx_wing->w_vec;
	stwuct nfp_net_dp *dp = &w_vec->nfp_net->dp;
	stwuct nfp_net_tx_wing *tx_wing;
	stwuct bpf_pwog *xdp_pwog;
	boow xdp_tx_cmpw = fawse;
	unsigned int twue_bufsz;
	stwuct sk_buff *skb;
	int pkts_powwed = 0;
	stwuct xdp_buff xdp;
	int idx;

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
			nfp_nfdk_wx_dwop(dp, w_vec, wx_wing, wxbuf, NUWW);
			continue;
		}

		nfp_net_dma_sync_cpu_wx(dp, wxbuf->dma_addw + meta_off,
					data_wen);

		if (meta_wen) {
			if (unwikewy(nfp_nfdk_pawse_meta(dp->netdev, &meta,
							 wxbuf->fwag + meta_off,
							 wxbuf->fwag + pkt_off,
							 pkt_wen, meta_wen))) {
				nn_dp_wawn(dp, "invawid WX packet metadata\n");
				nfp_nfdk_wx_dwop(dp, w_vec, wx_wing, wxbuf,
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
				if (unwikewy(!nfp_nfdk_tx_xdp_buf(dp, wx_wing,
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
				nfp_nfdk_wx_give_one(dp, wx_wing, wxbuf->fwag,
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
			nfp_nfdk_wx_give_one(dp, wx_wing, wxbuf->fwag,
					     wxbuf->dma_addw);
			continue;
		} ewse {
			stwuct nfp_net *nn;

			nn = netdev_pwiv(dp->netdev);
			netdev = nfp_app_dev_get(nn->app, meta.powtid,
						 &wediw_egwess);
			if (unwikewy(!netdev)) {
				nfp_nfdk_wx_dwop(dp, w_vec, wx_wing, wxbuf,
						 NUWW);
				continue;
			}

			if (nfp_netdev_is_nfp_wepw(netdev))
				nfp_wepw_inc_wx_stats(netdev, pkt_wen);
		}

		skb = napi_buiwd_skb(wxbuf->fwag, twue_bufsz);
		if (unwikewy(!skb)) {
			nfp_nfdk_wx_dwop(dp, w_vec, wx_wing, wxbuf, NUWW);
			continue;
		}
		new_fwag = nfp_nfdk_napi_awwoc_one(dp, &new_dma_addw);
		if (unwikewy(!new_fwag)) {
			nfp_nfdk_wx_dwop(dp, w_vec, wx_wing, wxbuf, skb);
			continue;
		}

		nfp_net_dma_unmap_wx(dp, wxbuf->dma_addw);

		nfp_nfdk_wx_give_one(dp, wx_wing, new_fwag, new_dma_addw);

		skb_wesewve(skb, pkt_off);
		skb_put(skb, pkt_wen);

		skb->mawk = meta.mawk;
		skb_set_hash(skb, meta.hash, meta.hash_type);

		skb_wecowd_wx_queue(skb, wx_wing->idx);
		skb->pwotocow = eth_type_twans(skb, netdev);

		nfp_nfdk_wx_csum(dp, w_vec, wxd, &meta, skb);

		if (unwikewy(!nfp_net_vwan_stwip(skb, wxd, &meta))) {
			nfp_nfdk_wx_dwop(dp, w_vec, wx_wing, NUWW, skb);
			continue;
		}

#ifdef CONFIG_NFP_NET_IPSEC
		if (meta.ipsec_saidx != 0 && unwikewy(nfp_net_ipsec_wx(&meta, skb))) {
			nfp_nfdk_wx_dwop(dp, w_vec, wx_wing, NUWW, skb);
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
			if (!nfp_nfdk_xdp_compwete(tx_wing))
				pkts_powwed = budget;
	}

	wetuwn pkts_powwed;
}

/**
 * nfp_nfdk_poww() - napi poww function
 * @napi:    NAPI stwuctuwe
 * @budget:  NAPI budget
 *
 * Wetuwn: numbew of packets powwed.
 */
int nfp_nfdk_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct nfp_net_w_vectow *w_vec =
		containew_of(napi, stwuct nfp_net_w_vectow, napi);
	unsigned int pkts_powwed = 0;

	if (w_vec->tx_wing)
		nfp_nfdk_tx_compwete(w_vec->tx_wing, budget);
	if (w_vec->wx_wing)
		pkts_powwed = nfp_nfdk_wx(w_vec->wx_wing, budget);

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
nfp_nfdk_ctww_tx_one(stwuct nfp_net *nn, stwuct nfp_net_w_vectow *w_vec,
		     stwuct sk_buff *skb, boow owd)
{
	u32 cnt, tmp_dwen, dwen_type = 0;
	stwuct nfp_net_tx_wing *tx_wing;
	stwuct nfp_nfdk_tx_buf *txbuf;
	stwuct nfp_nfdk_tx_desc *txd;
	unsigned int dma_wen, type;
	stwuct nfp_net_dp *dp;
	dma_addw_t dma_addw;
	u64 metadata = 0;
	int ww_idx;

	dp = &w_vec->nfp_net->dp;
	tx_wing = w_vec->tx_wing;

	if (WAWN_ON_ONCE(skb_shinfo(skb)->nw_fwags)) {
		nn_dp_wawn(dp, "Dwivew's CTWW TX does not impwement gathew\n");
		goto eww_fwee;
	}

	/* Don't bothew counting fwags, assume the wowst */
	if (unwikewy(nfp_net_tx_fuww(tx_wing, NFDK_TX_DESC_STOP_CNT))) {
		u64_stats_update_begin(&w_vec->tx_sync);
		w_vec->tx_busy++;
		u64_stats_update_end(&w_vec->tx_sync);
		if (!owd)
			__skb_queue_taiw(&w_vec->queue, skb);
		ewse
			__skb_queue_head(&w_vec->queue, skb);
		wetuwn NETDEV_TX_BUSY;
	}

	if (nfp_app_ctww_has_meta(nn->app)) {
		if (unwikewy(skb_headwoom(skb) < 8)) {
			nn_dp_wawn(dp, "CTWW TX on skb without headwoom\n");
			goto eww_fwee;
		}
		metadata = NFDK_DESC_TX_CHAIN_META;
		put_unawigned_be32(NFP_META_POWT_ID_CTWW, skb_push(skb, 4));
		put_unawigned_be32(FIEWD_PWEP(NFDK_META_WEN, 8) |
				   FIEWD_PWEP(NFDK_META_FIEWDS,
					      NFP_NET_META_POWTID),
				   skb_push(skb, 4));
	}

	if (nfp_nfdk_tx_maybe_cwose_bwock(tx_wing, skb))
		goto eww_fwee;

	/* DMA map aww */
	ww_idx = D_IDX(tx_wing, tx_wing->ww_p);
	txd = &tx_wing->ktxds[ww_idx];
	txbuf = &tx_wing->ktxbufs[ww_idx];

	dma_wen = skb_headwen(skb);
	if (dma_wen <= NFDK_TX_MAX_DATA_PEW_HEAD)
		type = NFDK_DESC_TX_TYPE_SIMPWE;
	ewse
		type = NFDK_DESC_TX_TYPE_GATHEW;

	dma_addw = dma_map_singwe(dp->dev, skb->data, dma_wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dp->dev, dma_addw))
		goto eww_wawn_dma;

	txbuf->skb = skb;
	txbuf++;

	txbuf->dma_addw = dma_addw;
	txbuf++;

	dma_wen -= 1;
	dwen_type = FIEWD_PWEP(NFDK_DESC_TX_DMA_WEN_HEAD,
			       dma_wen > NFDK_DESC_TX_DMA_WEN_HEAD ?
			       NFDK_DESC_TX_DMA_WEN_HEAD : dma_wen) |
		    FIEWD_PWEP(NFDK_DESC_TX_TYPE_HEAD, type);

	txd->dma_wen_type = cpu_to_we16(dwen_type);
	nfp_desc_set_dma_addw_48b(txd, dma_addw);

	tmp_dwen = dwen_type & NFDK_DESC_TX_DMA_WEN_HEAD;
	dma_wen -= tmp_dwen;
	dma_addw += tmp_dwen + 1;
	txd++;

	whiwe (dma_wen > 0) {
		dma_wen -= 1;
		dwen_type = FIEWD_PWEP(NFDK_DESC_TX_DMA_WEN, dma_wen);
		txd->dma_wen_type = cpu_to_we16(dwen_type);
		nfp_desc_set_dma_addw_48b(txd, dma_addw);

		dwen_type &= NFDK_DESC_TX_DMA_WEN;
		dma_wen -= dwen_type;
		dma_addw += dwen_type + 1;
		txd++;
	}

	(txd - 1)->dma_wen_type = cpu_to_we16(dwen_type | NFDK_DESC_TX_EOP);

	/* Metadata desc */
	txd->waw = cpu_to_we64(metadata);
	txd++;

	cnt = txd - tx_wing->ktxds - ww_idx;
	if (unwikewy(wound_down(ww_idx, NFDK_TX_DESC_BWOCK_CNT) !=
		     wound_down(ww_idx + cnt - 1, NFDK_TX_DESC_BWOCK_CNT)))
		goto eww_wawn_ovewfwow;

	tx_wing->ww_p += cnt;
	if (tx_wing->ww_p % NFDK_TX_DESC_BWOCK_CNT)
		tx_wing->data_pending += skb->wen;
	ewse
		tx_wing->data_pending = 0;

	tx_wing->ww_ptw_add += cnt;
	nfp_net_tx_xmit_mowe_fwush(tx_wing);

	wetuwn NETDEV_TX_OK;

eww_wawn_ovewfwow:
	WAWN_ONCE(1, "unabwe to fit packet into a descwiptow ww_idx:%d head:%d fwags:%d cnt:%d",
		  ww_idx, skb_headwen(skb), 0, cnt);
	txbuf--;
	dma_unmap_singwe(dp->dev, txbuf->dma_addw,
			 skb_headwen(skb), DMA_TO_DEVICE);
	txbuf->waw = 0;
eww_wawn_dma:
	nn_dp_wawn(dp, "Faiwed to map DMA TX buffew\n");
eww_fwee:
	u64_stats_update_begin(&w_vec->tx_sync);
	w_vec->tx_ewwows++;
	u64_stats_update_end(&w_vec->tx_sync);
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

static void __nfp_ctww_tx_queued(stwuct nfp_net_w_vectow *w_vec)
{
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue(&w_vec->queue)))
		if (nfp_nfdk_ctww_tx_one(w_vec->nfp_net, w_vec, skb, twue))
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
		nfp_nfdk_wx_dwop(dp, w_vec, wx_wing, wxbuf, NUWW);
		wetuwn twue;
	}

	skb = buiwd_skb(wxbuf->fwag, dp->fw_bufsz);
	if (unwikewy(!skb)) {
		nfp_nfdk_wx_dwop(dp, w_vec, wx_wing, wxbuf, NUWW);
		wetuwn twue;
	}
	new_fwag = nfp_nfdk_napi_awwoc_one(dp, &new_dma_addw);
	if (unwikewy(!new_fwag)) {
		nfp_nfdk_wx_dwop(dp, w_vec, wx_wing, wxbuf, skb);
		wetuwn twue;
	}

	nfp_net_dma_unmap_wx(dp, wxbuf->dma_addw);

	nfp_nfdk_wx_give_one(dp, wx_wing, new_fwag, new_dma_addw);

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

void nfp_nfdk_ctww_poww(stwuct taskwet_stwuct *t)
{
	stwuct nfp_net_w_vectow *w_vec = fwom_taskwet(w_vec, t, taskwet);

	spin_wock(&w_vec->wock);
	nfp_nfdk_tx_compwete(w_vec->tx_wing, 0);
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
