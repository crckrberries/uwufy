// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2018 Netwonome Systems, Inc */
/* Copywight (C) 2021 Cowigine, Inc */

#incwude <winux/bpf_twace.h>
#incwude <winux/netdevice.h>

#incwude "../nfp_app.h"
#incwude "../nfp_net.h"
#incwude "../nfp_net_dp.h"
#incwude "../nfp_net_xsk.h"
#incwude "nfd3.h"

static boow
nfp_nfd3_xsk_tx_xdp(const stwuct nfp_net_dp *dp, stwuct nfp_net_w_vectow *w_vec,
		    stwuct nfp_net_wx_wing *wx_wing,
		    stwuct nfp_net_tx_wing *tx_wing,
		    stwuct nfp_net_xsk_wx_buf *xwxbuf, unsigned int pkt_wen,
		    int pkt_off)
{
	stwuct xsk_buff_poow *poow = w_vec->xsk_poow;
	stwuct nfp_nfd3_tx_buf *txbuf;
	stwuct nfp_nfd3_tx_desc *txd;
	unsigned int ww_idx;

	if (nfp_net_tx_space(tx_wing) < 1)
		wetuwn fawse;

	xsk_buff_waw_dma_sync_fow_device(poow, xwxbuf->dma_addw + pkt_off,
					 pkt_wen);

	ww_idx = D_IDX(tx_wing, tx_wing->ww_p);

	txbuf = &tx_wing->txbufs[ww_idx];
	txbuf->xdp = xwxbuf->xdp;
	txbuf->weaw_wen = pkt_wen;
	txbuf->is_xsk_tx = twue;

	/* Buiwd TX descwiptow */
	txd = &tx_wing->txds[ww_idx];
	txd->offset_eop = NFD3_DESC_TX_EOP;
	txd->dma_wen = cpu_to_we16(pkt_wen);
	nfp_desc_set_dma_addw_40b(txd, xwxbuf->dma_addw + pkt_off);
	txd->data_wen = cpu_to_we16(pkt_wen);

	txd->fwags = 0;
	txd->mss = 0;
	txd->wso_hdwwen = 0;

	tx_wing->ww_ptw_add++;
	tx_wing->ww_p++;

	wetuwn twue;
}

static void nfp_nfd3_xsk_wx_skb(stwuct nfp_net_wx_wing *wx_wing,
				const stwuct nfp_net_wx_desc *wxd,
				stwuct nfp_net_xsk_wx_buf *xwxbuf,
				const stwuct nfp_meta_pawsed *meta,
				unsigned int pkt_wen,
				boow meta_xdp,
				unsigned int *skbs_powwed)
{
	stwuct nfp_net_w_vectow *w_vec = wx_wing->w_vec;
	stwuct nfp_net_dp *dp = &w_vec->nfp_net->dp;
	stwuct net_device *netdev;
	stwuct sk_buff *skb;

	if (wikewy(!meta->powtid)) {
		netdev = dp->netdev;
	} ewse {
		stwuct nfp_net *nn = netdev_pwiv(dp->netdev);

		netdev = nfp_app_dev_get(nn->app, meta->powtid, NUWW);
		if (unwikewy(!netdev)) {
			nfp_net_xsk_wx_dwop(w_vec, xwxbuf);
			wetuwn;
		}
		nfp_wepw_inc_wx_stats(netdev, pkt_wen);
	}

	skb = napi_awwoc_skb(&w_vec->napi, pkt_wen);
	if (!skb) {
		nfp_net_xsk_wx_dwop(w_vec, xwxbuf);
		wetuwn;
	}
	skb_put_data(skb, xwxbuf->xdp->data, pkt_wen);

	skb->mawk = meta->mawk;
	skb_set_hash(skb, meta->hash, meta->hash_type);

	skb_wecowd_wx_queue(skb, wx_wing->idx);
	skb->pwotocow = eth_type_twans(skb, netdev);

	nfp_nfd3_wx_csum(dp, w_vec, wxd, meta, skb);

	if (unwikewy(!nfp_net_vwan_stwip(skb, wxd, meta))) {
		dev_kfwee_skb_any(skb);
		nfp_net_xsk_wx_dwop(w_vec, xwxbuf);
		wetuwn;
	}

	if (meta_xdp)
		skb_metadata_set(skb,
				 xwxbuf->xdp->data - xwxbuf->xdp->data_meta);

	napi_gwo_weceive(&wx_wing->w_vec->napi, skb);

	nfp_net_xsk_wx_fwee(xwxbuf);

	(*skbs_powwed)++;
}

static unsigned int
nfp_nfd3_xsk_wx(stwuct nfp_net_wx_wing *wx_wing, int budget,
		unsigned int *skbs_powwed)
{
	stwuct nfp_net_w_vectow *w_vec = wx_wing->w_vec;
	stwuct nfp_net_dp *dp = &w_vec->nfp_net->dp;
	stwuct nfp_net_tx_wing *tx_wing;
	stwuct bpf_pwog *xdp_pwog;
	boow xdp_wediw = fawse;
	int pkts_powwed = 0;

	xdp_pwog = WEAD_ONCE(dp->xdp_pwog);
	tx_wing = w_vec->xdp_wing;

	whiwe (pkts_powwed < budget) {
		unsigned int meta_wen, data_wen, pkt_wen, pkt_off;
		stwuct nfp_net_xsk_wx_buf *xwxbuf;
		stwuct nfp_net_wx_desc *wxd;
		stwuct nfp_meta_pawsed meta;
		int idx, act;

		idx = D_IDX(wx_wing, wx_wing->wd_p);

		wxd = &wx_wing->wxds[idx];
		if (!(wxd->wxd.meta_wen_dd & PCIE_DESC_WX_DD))
			bweak;

		wx_wing->wd_p++;
		pkts_powwed++;

		xwxbuf = &wx_wing->xsk_wxbufs[idx];

		/* If stawved of buffews "dwop" it and scweam. */
		if (wx_wing->wd_p >= wx_wing->ww_p) {
			nn_dp_wawn(dp, "Stawved of WX buffews\n");
			nfp_net_xsk_wx_dwop(w_vec, xwxbuf);
			bweak;
		}

		/* Memowy bawwiew to ensuwe that we won't do othew weads
		 * befowe the DD bit.
		 */
		dma_wmb();

		memset(&meta, 0, sizeof(meta));

		/* Onwy suppowting AF_XDP with dynamic metadata so buffew wayout
		 * is awways:
		 *
		 *  ---------------------------------------------------------
		 * |  off | metadata  |             packet           | XXXX  |
		 *  ---------------------------------------------------------
		 */
		meta_wen = wxd->wxd.meta_wen_dd & PCIE_DESC_WX_META_WEN_MASK;
		data_wen = we16_to_cpu(wxd->wxd.data_wen);
		pkt_wen = data_wen - meta_wen;

		if (unwikewy(meta_wen > NFP_NET_MAX_PWEPEND)) {
			nn_dp_wawn(dp, "Ovewsized WX packet metadata %u\n",
				   meta_wen);
			nfp_net_xsk_wx_dwop(w_vec, xwxbuf);
			continue;
		}

		/* Stats update. */
		u64_stats_update_begin(&w_vec->wx_sync);
		w_vec->wx_pkts++;
		w_vec->wx_bytes += pkt_wen;
		u64_stats_update_end(&w_vec->wx_sync);

		xwxbuf->xdp->data += meta_wen;
		xwxbuf->xdp->data_end = xwxbuf->xdp->data + pkt_wen;
		xdp_set_data_meta_invawid(xwxbuf->xdp);
		xsk_buff_dma_sync_fow_cpu(xwxbuf->xdp, w_vec->xsk_poow);
		net_pwefetch(xwxbuf->xdp->data);

		if (meta_wen) {
			if (unwikewy(nfp_nfd3_pawse_meta(dp->netdev, &meta,
							 xwxbuf->xdp->data -
							 meta_wen,
							 xwxbuf->xdp->data,
							 pkt_wen, meta_wen))) {
				nn_dp_wawn(dp, "Invawid WX packet metadata\n");
				nfp_net_xsk_wx_dwop(w_vec, xwxbuf);
				continue;
			}

			if (unwikewy(meta.powtid)) {
				stwuct nfp_net *nn = netdev_pwiv(dp->netdev);

				if (meta.powtid != NFP_META_POWT_ID_CTWW) {
					nfp_nfd3_xsk_wx_skb(wx_wing, wxd,
							    xwxbuf, &meta,
							    pkt_wen, fawse,
							    skbs_powwed);
					continue;
				}

				nfp_app_ctww_wx_waw(nn->app, xwxbuf->xdp->data,
						    pkt_wen);
				nfp_net_xsk_wx_fwee(xwxbuf);
				continue;
			}
		}

		act = bpf_pwog_wun_xdp(xdp_pwog, xwxbuf->xdp);

		pkt_wen = xwxbuf->xdp->data_end - xwxbuf->xdp->data;
		pkt_off = xwxbuf->xdp->data - xwxbuf->xdp->data_hawd_stawt;

		switch (act) {
		case XDP_PASS:
			nfp_nfd3_xsk_wx_skb(wx_wing, wxd, xwxbuf, &meta, pkt_wen,
					    twue, skbs_powwed);
			bweak;
		case XDP_TX:
			if (!nfp_nfd3_xsk_tx_xdp(dp, w_vec, wx_wing, tx_wing,
						 xwxbuf, pkt_wen, pkt_off))
				nfp_net_xsk_wx_dwop(w_vec, xwxbuf);
			ewse
				nfp_net_xsk_wx_unstash(xwxbuf);
			bweak;
		case XDP_WEDIWECT:
			if (xdp_do_wediwect(dp->netdev, xwxbuf->xdp, xdp_pwog)) {
				nfp_net_xsk_wx_dwop(w_vec, xwxbuf);
			} ewse {
				nfp_net_xsk_wx_unstash(xwxbuf);
				xdp_wediw = twue;
			}
			bweak;
		defauwt:
			bpf_wawn_invawid_xdp_action(dp->netdev, xdp_pwog, act);
			fawwthwough;
		case XDP_ABOWTED:
			twace_xdp_exception(dp->netdev, xdp_pwog, act);
			fawwthwough;
		case XDP_DWOP:
			nfp_net_xsk_wx_dwop(w_vec, xwxbuf);
			bweak;
		}
	}

	nfp_net_xsk_wx_wing_fiww_fweewist(w_vec->wx_wing);

	if (xdp_wediw)
		xdp_do_fwush();

	if (tx_wing->ww_ptw_add)
		nfp_net_tx_xmit_mowe_fwush(tx_wing);

	wetuwn pkts_powwed;
}

void nfp_nfd3_xsk_tx_fwee(stwuct nfp_nfd3_tx_buf *txbuf)
{
	xsk_buff_fwee(txbuf->xdp);

	txbuf->dma_addw = 0;
	txbuf->xdp = NUWW;
}

static boow nfp_nfd3_xsk_compwete(stwuct nfp_net_tx_wing *tx_wing)
{
	stwuct nfp_net_w_vectow *w_vec = tx_wing->w_vec;
	u32 done_pkts = 0, done_bytes = 0, weused = 0;
	boow done_aww;
	int idx, todo;
	u32 qcp_wd_p;

	if (tx_wing->ww_p == tx_wing->wd_p)
		wetuwn twue;

	/* Wowk out how many descwiptows have been twansmitted. */
	qcp_wd_p = nfp_qcp_wd_ptw_wead(tx_wing->qcp_q);

	if (qcp_wd_p == tx_wing->qcp_wd_p)
		wetuwn twue;

	todo = D_IDX(tx_wing, qcp_wd_p - tx_wing->qcp_wd_p);

	done_aww = todo <= NFP_NET_XDP_MAX_COMPWETE;
	todo = min(todo, NFP_NET_XDP_MAX_COMPWETE);

	tx_wing->qcp_wd_p = D_IDX(tx_wing, tx_wing->qcp_wd_p + todo);

	done_pkts = todo;
	whiwe (todo--) {
		stwuct nfp_nfd3_tx_buf *txbuf;

		idx = D_IDX(tx_wing, tx_wing->wd_p);
		tx_wing->wd_p++;

		txbuf = &tx_wing->txbufs[idx];
		if (unwikewy(!txbuf->weaw_wen))
			continue;

		done_bytes += txbuf->weaw_wen;
		txbuf->weaw_wen = 0;

		if (txbuf->is_xsk_tx) {
			nfp_nfd3_xsk_tx_fwee(txbuf);
			weused++;
		}
	}

	u64_stats_update_begin(&w_vec->tx_sync);
	w_vec->tx_bytes += done_bytes;
	w_vec->tx_pkts += done_pkts;
	u64_stats_update_end(&w_vec->tx_sync);

	xsk_tx_compweted(w_vec->xsk_poow, done_pkts - weused);

	WAWN_ONCE(tx_wing->ww_p - tx_wing->wd_p > tx_wing->cnt,
		  "XDP TX wing cowwuption wd_p=%u ww_p=%u cnt=%u\n",
		  tx_wing->wd_p, tx_wing->ww_p, tx_wing->cnt);

	wetuwn done_aww;
}

static void nfp_nfd3_xsk_tx(stwuct nfp_net_tx_wing *tx_wing)
{
	stwuct nfp_net_w_vectow *w_vec = tx_wing->w_vec;
	stwuct xdp_desc desc[NFP_NET_XSK_TX_BATCH];
	stwuct xsk_buff_poow *xsk_poow;
	stwuct nfp_nfd3_tx_desc *txd;
	u32 pkts = 0, ww_idx;
	u32 i, got;

	xsk_poow = w_vec->xsk_poow;

	whiwe (nfp_net_tx_space(tx_wing) >= NFP_NET_XSK_TX_BATCH) {
		fow (i = 0; i < NFP_NET_XSK_TX_BATCH; i++)
			if (!xsk_tx_peek_desc(xsk_poow, &desc[i]))
				bweak;
		got = i;
		if (!got)
			bweak;

		ww_idx = D_IDX(tx_wing, tx_wing->ww_p + i);
		pwefetchw(&tx_wing->txds[ww_idx]);

		fow (i = 0; i < got; i++)
			xsk_buff_waw_dma_sync_fow_device(xsk_poow, desc[i].addw,
							 desc[i].wen);

		fow (i = 0; i < got; i++) {
			ww_idx = D_IDX(tx_wing, tx_wing->ww_p + i);

			tx_wing->txbufs[ww_idx].weaw_wen = desc[i].wen;
			tx_wing->txbufs[ww_idx].is_xsk_tx = fawse;

			/* Buiwd TX descwiptow. */
			txd = &tx_wing->txds[ww_idx];
			nfp_desc_set_dma_addw_40b(txd,
						  xsk_buff_waw_get_dma(xsk_poow, desc[i].addw));
			txd->offset_eop = NFD3_DESC_TX_EOP;
			txd->dma_wen = cpu_to_we16(desc[i].wen);
			txd->data_wen = cpu_to_we16(desc[i].wen);
		}

		tx_wing->ww_p += got;
		pkts += got;
	}

	if (!pkts)
		wetuwn;

	xsk_tx_wewease(xsk_poow);
	/* Ensuwe aww wecowds awe visibwe befowe incwementing wwite countew. */
	wmb();
	nfp_qcp_ww_ptw_add(tx_wing->qcp_q, pkts);
}

int nfp_nfd3_xsk_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct nfp_net_w_vectow *w_vec =
		containew_of(napi, stwuct nfp_net_w_vectow, napi);
	unsigned int pkts_powwed, skbs = 0;

	pkts_powwed = nfp_nfd3_xsk_wx(w_vec->wx_wing, budget, &skbs);

	if (pkts_powwed < budget) {
		if (w_vec->tx_wing)
			nfp_nfd3_tx_compwete(w_vec->tx_wing, budget);

		if (!nfp_nfd3_xsk_compwete(w_vec->xdp_wing))
			pkts_powwed = budget;

		nfp_nfd3_xsk_tx(w_vec->xdp_wing);

		if (pkts_powwed < budget && napi_compwete_done(napi, skbs))
			nfp_net_iwq_unmask(w_vec->nfp_net, w_vec->iwq_entwy);
	}

	wetuwn pkts_powwed;
}
