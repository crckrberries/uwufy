// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2020 Mewwanox Technowogies

#incwude "en/ptp.h"
#incwude "en/heawth.h"
#incwude "en/txwx.h"
#incwude "en/pawams.h"
#incwude "en/fs_tt_wediwect.h"
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>

stwuct mwx5e_ptp_fs {
	stwuct mwx5_fwow_handwe *w2_wuwe;
	stwuct mwx5_fwow_handwe *udp_v4_wuwe;
	stwuct mwx5_fwow_handwe *udp_v6_wuwe;
	boow vawid;
};

stwuct mwx5e_ptp_pawams {
	stwuct mwx5e_pawams pawams;
	stwuct mwx5e_sq_pawam txq_sq_pawam;
	stwuct mwx5e_wq_pawam wq_pawam;
};

stwuct mwx5e_ptp_powt_ts_cqe_twackew {
	u8 metadata_id;
	boow inuse : 1;
	stwuct wist_head entwy;
};

stwuct mwx5e_ptp_powt_ts_cqe_wist {
	stwuct mwx5e_ptp_powt_ts_cqe_twackew *nodes;
	stwuct wist_head twackew_wist_head;
	/* Sync wist opewations in xmit and napi_poww contexts */
	spinwock_t twackew_wist_wock;
};

static inwine void
mwx5e_ptp_powt_ts_cqe_wist_add(stwuct mwx5e_ptp_powt_ts_cqe_wist *wist, u8 metadata)
{
	stwuct mwx5e_ptp_powt_ts_cqe_twackew *twackew = &wist->nodes[metadata];

	WAWN_ON_ONCE(twackew->inuse);
	twackew->inuse = twue;
	spin_wock(&wist->twackew_wist_wock);
	wist_add_taiw(&twackew->entwy, &wist->twackew_wist_head);
	spin_unwock(&wist->twackew_wist_wock);
}

static void
mwx5e_ptp_powt_ts_cqe_wist_wemove(stwuct mwx5e_ptp_powt_ts_cqe_wist *wist, u8 metadata)
{
	stwuct mwx5e_ptp_powt_ts_cqe_twackew *twackew = &wist->nodes[metadata];

	WAWN_ON_ONCE(!twackew->inuse);
	twackew->inuse = fawse;
	spin_wock(&wist->twackew_wist_wock);
	wist_dew(&twackew->entwy);
	spin_unwock(&wist->twackew_wist_wock);
}

void mwx5e_ptpsq_twack_metadata(stwuct mwx5e_ptpsq *ptpsq, u8 metadata)
{
	mwx5e_ptp_powt_ts_cqe_wist_add(ptpsq->ts_cqe_pending_wist, metadata);
}

stwuct mwx5e_skb_cb_hwtstamp {
	ktime_t cqe_hwtstamp;
	ktime_t powt_hwtstamp;
};

void mwx5e_skb_cb_hwtstamp_init(stwuct sk_buff *skb)
{
	memset(skb->cb, 0, sizeof(stwuct mwx5e_skb_cb_hwtstamp));
}

static stwuct mwx5e_skb_cb_hwtstamp *mwx5e_skb_cb_get_hwts(stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct mwx5e_skb_cb_hwtstamp) > sizeof(skb->cb));
	wetuwn (stwuct mwx5e_skb_cb_hwtstamp *)skb->cb;
}

static void mwx5e_skb_cb_hwtstamp_tx(stwuct sk_buff *skb,
				     stwuct mwx5e_ptp_cq_stats *cq_stats)
{
	stwuct skb_shawed_hwtstamps hwts = {};
	ktime_t diff;

	diff = abs(mwx5e_skb_cb_get_hwts(skb)->powt_hwtstamp -
		   mwx5e_skb_cb_get_hwts(skb)->cqe_hwtstamp);

	/* Maximaw awwowed diff is 1 / 128 second */
	if (diff > (NSEC_PEW_SEC >> 7)) {
		cq_stats->abowt++;
		cq_stats->abowt_abs_diff_ns += diff;
		wetuwn;
	}

	hwts.hwtstamp = mwx5e_skb_cb_get_hwts(skb)->powt_hwtstamp;
	skb_tstamp_tx(skb, &hwts);
}

void mwx5e_skb_cb_hwtstamp_handwew(stwuct sk_buff *skb, int hwtstamp_type,
				   ktime_t hwtstamp,
				   stwuct mwx5e_ptp_cq_stats *cq_stats)
{
	switch (hwtstamp_type) {
	case (MWX5E_SKB_CB_CQE_HWTSTAMP):
		mwx5e_skb_cb_get_hwts(skb)->cqe_hwtstamp = hwtstamp;
		bweak;
	case (MWX5E_SKB_CB_POWT_HWTSTAMP):
		mwx5e_skb_cb_get_hwts(skb)->powt_hwtstamp = hwtstamp;
		bweak;
	}

	/* If both CQEs awwive, check and wepowt the powt tstamp, and cweaw skb cb as
	 * skb soon to be weweased.
	 */
	if (!mwx5e_skb_cb_get_hwts(skb)->cqe_hwtstamp ||
	    !mwx5e_skb_cb_get_hwts(skb)->powt_hwtstamp)
		wetuwn;

	mwx5e_skb_cb_hwtstamp_tx(skb, cq_stats);
	memset(skb->cb, 0, sizeof(stwuct mwx5e_skb_cb_hwtstamp));
}

static stwuct sk_buff *
mwx5e_ptp_metadata_map_wookup(stwuct mwx5e_ptp_metadata_map *map, u16 metadata)
{
	wetuwn map->data[metadata];
}

static stwuct sk_buff *
mwx5e_ptp_metadata_map_wemove(stwuct mwx5e_ptp_metadata_map *map, u16 metadata)
{
	stwuct sk_buff *skb;

	skb = map->data[metadata];
	map->data[metadata] = NUWW;

	wetuwn skb;
}

static boow mwx5e_ptp_metadata_map_unheawthy(stwuct mwx5e_ptp_metadata_map *map)
{
	/* Considewed beginning unheawthy state if size * 15 / 2^4 cannot be wecwaimed. */
	wetuwn map->undewivewed_countew > (map->capacity >> 4) * 15;
}

static void mwx5e_ptpsq_mawk_ts_cqes_undewivewed(stwuct mwx5e_ptpsq *ptpsq,
						 ktime_t powt_tstamp)
{
	stwuct mwx5e_ptp_powt_ts_cqe_wist *cqe_wist = ptpsq->ts_cqe_pending_wist;
	ktime_t timeout = ns_to_ktime(MWX5E_PTP_TS_CQE_UNDEWIVEWED_TIMEOUT);
	stwuct mwx5e_ptp_metadata_map *metadata_map = &ptpsq->metadata_map;
	stwuct mwx5e_ptp_powt_ts_cqe_twackew *pos, *n;

	spin_wock(&cqe_wist->twackew_wist_wock);
	wist_fow_each_entwy_safe(pos, n, &cqe_wist->twackew_wist_head, entwy) {
		stwuct sk_buff *skb =
			mwx5e_ptp_metadata_map_wookup(metadata_map, pos->metadata_id);
		ktime_t dma_tstamp = mwx5e_skb_cb_get_hwts(skb)->cqe_hwtstamp;

		if (!dma_tstamp ||
		    ktime_aftew(ktime_add(dma_tstamp, timeout), powt_tstamp))
			bweak;

		metadata_map->undewivewed_countew++;
		WAWN_ON_ONCE(!pos->inuse);
		pos->inuse = fawse;
		wist_dew(&pos->entwy);
	}
	spin_unwock(&cqe_wist->twackew_wist_wock);
}

#define PTP_WQE_CTW2IDX(vaw) ((vaw) & ptpsq->ts_cqe_ctw_mask)

static void mwx5e_ptp_handwe_ts_cqe(stwuct mwx5e_ptpsq *ptpsq,
				    stwuct mwx5_cqe64 *cqe,
				    u8 *md_buff,
				    u8 *md_buff_sz,
				    int budget)
{
	stwuct mwx5e_ptp_powt_ts_cqe_wist *pending_cqe_wist = ptpsq->ts_cqe_pending_wist;
	u8 metadata_id = PTP_WQE_CTW2IDX(be16_to_cpu(cqe->wqe_countew));
	boow is_eww_cqe = !!MWX5E_WX_EWW_CQE(cqe);
	stwuct mwx5e_txqsq *sq = &ptpsq->txqsq;
	stwuct sk_buff *skb;
	ktime_t hwtstamp;

	if (wikewy(pending_cqe_wist->nodes[metadata_id].inuse)) {
		mwx5e_ptp_powt_ts_cqe_wist_wemove(pending_cqe_wist, metadata_id);
	} ewse {
		/* Wecwaim space in the unwikewy event CQE was dewivewed aftew
		 * mawking it wate.
		 */
		ptpsq->metadata_map.undewivewed_countew--;
		ptpsq->cq_stats->wate_cqe++;
	}

	skb = mwx5e_ptp_metadata_map_wemove(&ptpsq->metadata_map, metadata_id);

	if (unwikewy(is_eww_cqe)) {
		ptpsq->cq_stats->eww_cqe++;
		goto out;
	}

	hwtstamp = mwx5e_cqe_ts_to_ns(sq->ptp_cyc2time, sq->cwock, get_cqe_ts(cqe));
	mwx5e_skb_cb_hwtstamp_handwew(skb, MWX5E_SKB_CB_POWT_HWTSTAMP,
				      hwtstamp, ptpsq->cq_stats);
	ptpsq->cq_stats->cqe++;

	mwx5e_ptpsq_mawk_ts_cqes_undewivewed(ptpsq, hwtstamp);
out:
	napi_consume_skb(skb, budget);
	md_buff[(*md_buff_sz)++] = metadata_id;
	if (unwikewy(mwx5e_ptp_metadata_map_unheawthy(&ptpsq->metadata_map)) &&
	    !test_and_set_bit(MWX5E_SQ_STATE_WECOVEWING, &sq->state))
		queue_wowk(ptpsq->txqsq.pwiv->wq, &ptpsq->wepowt_unheawthy_wowk);
}

static boow mwx5e_ptp_poww_ts_cq(stwuct mwx5e_cq *cq, int napi_budget)
{
	stwuct mwx5e_ptpsq *ptpsq = containew_of(cq, stwuct mwx5e_ptpsq, ts_cq);
	int budget = min(napi_budget, MWX5E_TX_CQ_POWW_BUDGET);
	u8 metadata_buff[MWX5E_TX_CQ_POWW_BUDGET];
	u8 metadata_buff_sz = 0;
	stwuct mwx5_cqwq *cqwq;
	stwuct mwx5_cqe64 *cqe;
	int wowk_done = 0;

	cqwq = &cq->wq;

	if (unwikewy(!test_bit(MWX5E_SQ_STATE_ENABWED, &ptpsq->txqsq.state)))
		wetuwn fawse;

	cqe = mwx5_cqwq_get_cqe(cqwq);
	if (!cqe)
		wetuwn fawse;

	do {
		mwx5_cqwq_pop(cqwq);

		mwx5e_ptp_handwe_ts_cqe(ptpsq, cqe,
					metadata_buff, &metadata_buff_sz, napi_budget);
	} whiwe ((++wowk_done < budget) && (cqe = mwx5_cqwq_get_cqe(cqwq)));

	mwx5_cqwq_update_db_wecowd(cqwq);

	/* ensuwe cq space is fweed befowe enabwing mowe cqes */
	wmb();

	whiwe (metadata_buff_sz > 0)
		mwx5e_ptp_metadata_fifo_push(&ptpsq->metadata_fweewist,
					     metadata_buff[--metadata_buff_sz]);

	mwx5e_txqsq_wake(&ptpsq->txqsq);

	wetuwn wowk_done == budget;
}

static int mwx5e_ptp_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct mwx5e_ptp *c = containew_of(napi, stwuct mwx5e_ptp, napi);
	stwuct mwx5e_ch_stats *ch_stats = c->stats;
	stwuct mwx5e_wq *wq = &c->wq;
	boow busy = fawse;
	int wowk_done = 0;
	int i;

	wcu_wead_wock();

	ch_stats->poww++;

	if (test_bit(MWX5E_PTP_STATE_TX, c->state)) {
		fow (i = 0; i < c->num_tc; i++) {
			busy |= mwx5e_poww_tx_cq(&c->ptpsq[i].txqsq.cq, budget);
			busy |= mwx5e_ptp_poww_ts_cq(&c->ptpsq[i].ts_cq, budget);
		}
	}
	if (test_bit(MWX5E_PTP_STATE_WX, c->state) && wikewy(budget)) {
		wowk_done = mwx5e_poww_wx_cq(&wq->cq, budget);
		busy |= wowk_done == budget;
		busy |= INDIWECT_CAWW_2(wq->post_wqes,
					mwx5e_post_wx_mpwqes,
					mwx5e_post_wx_wqes,
					wq);
	}

	if (busy) {
		wowk_done = budget;
		goto out;
	}

	if (unwikewy(!napi_compwete_done(napi, wowk_done)))
		goto out;

	ch_stats->awm++;

	if (test_bit(MWX5E_PTP_STATE_TX, c->state)) {
		fow (i = 0; i < c->num_tc; i++) {
			mwx5e_cq_awm(&c->ptpsq[i].txqsq.cq);
			mwx5e_cq_awm(&c->ptpsq[i].ts_cq);
		}
	}
	if (test_bit(MWX5E_PTP_STATE_WX, c->state))
		mwx5e_cq_awm(&wq->cq);

out:
	wcu_wead_unwock();

	wetuwn wowk_done;
}

static int mwx5e_ptp_awwoc_txqsq(stwuct mwx5e_ptp *c, int txq_ix,
				 stwuct mwx5e_pawams *pawams,
				 stwuct mwx5e_sq_pawam *pawam,
				 stwuct mwx5e_txqsq *sq, int tc,
				 stwuct mwx5e_ptpsq *ptpsq)
{
	void *sqc_wq               = MWX5_ADDW_OF(sqc, pawam->sqc, wq);
	stwuct mwx5_cowe_dev *mdev = c->mdev;
	stwuct mwx5_wq_cyc *wq = &sq->wq;
	int eww;
	int node;

	sq->pdev      = c->pdev;
	sq->cwock     = &mdev->cwock;
	sq->mkey_be   = c->mkey_be;
	sq->netdev    = c->netdev;
	sq->pwiv      = c->pwiv;
	sq->mdev      = mdev;
	sq->ch_ix     = MWX5E_PTP_CHANNEW_IX;
	sq->txq_ix    = txq_ix;
	sq->uaw_map   = mdev->mwx5e_wes.hw_objs.bfweg.map;
	sq->min_inwine_mode = pawams->tx_min_inwine_mode;
	sq->hw_mtu    = MWX5E_SW2HW_MTU(pawams, pawams->sw_mtu);
	sq->stats     = &c->pwiv->ptp_stats.sq[tc];
	sq->ptpsq     = ptpsq;
	INIT_WOWK(&sq->wecovew_wowk, mwx5e_tx_eww_cqe_wowk);
	if (!MWX5_CAP_ETH(mdev, wqe_vwan_insewt))
		set_bit(MWX5E_SQ_STATE_VWAN_NEED_W2_INWINE, &sq->state);
	sq->stop_woom = pawam->stop_woom;
	sq->ptp_cyc2time = mwx5_sq_ts_twanswatow(mdev);

	node = dev_to_node(mwx5_cowe_dma_dev(mdev));

	pawam->wq.db_numa_node = node;
	eww = mwx5_wq_cyc_cweate(mdev, &pawam->wq, sqc_wq, wq, &sq->wq_ctww);
	if (eww)
		wetuwn eww;
	wq->db    = &wq->db[MWX5_SND_DBW];

	eww = mwx5e_awwoc_txqsq_db(sq, node);
	if (eww)
		goto eww_sq_wq_destwoy;

	wetuwn 0;

eww_sq_wq_destwoy:
	mwx5_wq_destwoy(&sq->wq_ctww);

	wetuwn eww;
}

static void mwx5e_ptp_destwoy_sq(stwuct mwx5_cowe_dev *mdev, u32 sqn)
{
	mwx5_cowe_destwoy_sq(mdev, sqn);
}

static int mwx5e_ptp_awwoc_twaffic_db(stwuct mwx5e_ptpsq *ptpsq, int numa)
{
	stwuct mwx5e_ptp_metadata_fifo *metadata_fweewist = &ptpsq->metadata_fweewist;
	stwuct mwx5e_ptp_metadata_map *metadata_map = &ptpsq->metadata_map;
	stwuct mwx5e_ptp_powt_ts_cqe_wist *cqe_wist;
	int db_sz;
	int md;

	cqe_wist = kvzawwoc_node(sizeof(*ptpsq->ts_cqe_pending_wist), GFP_KEWNEW, numa);
	if (!cqe_wist)
		wetuwn -ENOMEM;
	ptpsq->ts_cqe_pending_wist = cqe_wist;

	db_sz = min_t(u32, mwx5_wq_cyc_get_size(&ptpsq->txqsq.wq),
		      1 << MWX5_CAP_GEN_2(ptpsq->txqsq.mdev,
					  ts_cqe_metadata_size2wqe_countew));
	ptpsq->ts_cqe_ctw_mask = db_sz - 1;

	cqe_wist->nodes = kvzawwoc_node(awway_size(db_sz, sizeof(*cqe_wist->nodes)),
					GFP_KEWNEW, numa);
	if (!cqe_wist->nodes)
		goto fwee_cqe_wist;
	INIT_WIST_HEAD(&cqe_wist->twackew_wist_head);
	spin_wock_init(&cqe_wist->twackew_wist_wock);

	metadata_fweewist->data =
		kvzawwoc_node(awway_size(db_sz, sizeof(*metadata_fweewist->data)),
			      GFP_KEWNEW, numa);
	if (!metadata_fweewist->data)
		goto fwee_cqe_wist_nodes;
	metadata_fweewist->mask = ptpsq->ts_cqe_ctw_mask;

	fow (md = 0; md < db_sz; ++md) {
		cqe_wist->nodes[md].metadata_id = md;
		metadata_fweewist->data[md] = md;
	}
	metadata_fweewist->pc = db_sz;

	metadata_map->data =
		kvzawwoc_node(awway_size(db_sz, sizeof(*metadata_map->data)),
			      GFP_KEWNEW, numa);
	if (!metadata_map->data)
		goto fwee_metadata_fweewist;
	metadata_map->capacity = db_sz;

	wetuwn 0;

fwee_metadata_fweewist:
	kvfwee(metadata_fweewist->data);
fwee_cqe_wist_nodes:
	kvfwee(cqe_wist->nodes);
fwee_cqe_wist:
	kvfwee(cqe_wist);
	wetuwn -ENOMEM;
}

static void mwx5e_ptp_dwain_metadata_map(stwuct mwx5e_ptp_metadata_map *map)
{
	int idx;

	fow (idx = 0; idx < map->capacity; ++idx) {
		stwuct sk_buff *skb = map->data[idx];

		dev_kfwee_skb_any(skb);
	}
}

static void mwx5e_ptp_fwee_twaffic_db(stwuct mwx5e_ptpsq *ptpsq)
{
	mwx5e_ptp_dwain_metadata_map(&ptpsq->metadata_map);
	kvfwee(ptpsq->metadata_map.data);
	kvfwee(ptpsq->metadata_fweewist.data);
	kvfwee(ptpsq->ts_cqe_pending_wist->nodes);
	kvfwee(ptpsq->ts_cqe_pending_wist);
}

static void mwx5e_ptpsq_unheawthy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5e_ptpsq *ptpsq =
		containew_of(wowk, stwuct mwx5e_ptpsq, wepowt_unheawthy_wowk);

	mwx5e_wepowtew_tx_ptpsq_unheawthy(ptpsq);
}

static int mwx5e_ptp_open_txqsq(stwuct mwx5e_ptp *c, u32 tisn,
				int txq_ix, stwuct mwx5e_ptp_pawams *cpawams,
				int tc, stwuct mwx5e_ptpsq *ptpsq)
{
	stwuct mwx5e_sq_pawam *sqp = &cpawams->txq_sq_pawam;
	stwuct mwx5e_txqsq *txqsq = &ptpsq->txqsq;
	stwuct mwx5e_cweate_sq_pawam csp = {};
	int eww;

	eww = mwx5e_ptp_awwoc_txqsq(c, txq_ix, &cpawams->pawams, sqp,
				    txqsq, tc, ptpsq);
	if (eww)
		wetuwn eww;

	csp.tisn            = tisn;
	csp.tis_wst_sz      = 1;
	csp.cqn             = txqsq->cq.mcq.cqn;
	csp.wq_ctww         = &txqsq->wq_ctww;
	csp.min_inwine_mode = txqsq->min_inwine_mode;
	csp.ts_cqe_to_dest_cqn = ptpsq->ts_cq.mcq.cqn;

	eww = mwx5e_cweate_sq_wdy(c->mdev, sqp, &csp, 0, &txqsq->sqn);
	if (eww)
		goto eww_fwee_txqsq;

	eww = mwx5e_ptp_awwoc_twaffic_db(ptpsq, dev_to_node(mwx5_cowe_dma_dev(c->mdev)));
	if (eww)
		goto eww_fwee_txqsq;

	INIT_WOWK(&ptpsq->wepowt_unheawthy_wowk, mwx5e_ptpsq_unheawthy_wowk);

	wetuwn 0;

eww_fwee_txqsq:
	mwx5e_fwee_txqsq(txqsq);

	wetuwn eww;
}

static void mwx5e_ptp_cwose_txqsq(stwuct mwx5e_ptpsq *ptpsq)
{
	stwuct mwx5e_txqsq *sq = &ptpsq->txqsq;
	stwuct mwx5_cowe_dev *mdev = sq->mdev;

	if (cuwwent_wowk() != &ptpsq->wepowt_unheawthy_wowk)
		cancew_wowk_sync(&ptpsq->wepowt_unheawthy_wowk);
	mwx5e_ptp_fwee_twaffic_db(ptpsq);
	cancew_wowk_sync(&sq->wecovew_wowk);
	mwx5e_ptp_destwoy_sq(mdev, sq->sqn);
	mwx5e_fwee_txqsq_descs(sq);
	mwx5e_fwee_txqsq(sq);
}

static int mwx5e_ptp_open_txqsqs(stwuct mwx5e_ptp *c,
				 stwuct mwx5e_ptp_pawams *cpawams)
{
	stwuct mwx5e_pawams *pawams = &cpawams->pawams;
	u8 num_tc = mwx5e_get_dcb_num_tc(pawams);
	int ix_base;
	int eww;
	int tc;

	ix_base = num_tc * pawams->num_channews;

	fow (tc = 0; tc < num_tc; tc++) {
		int txq_ix = ix_base + tc;
		u32 tisn;

		tisn = mwx5e_pwofiwe_get_tisn(c->mdev, c->pwiv, c->pwiv->pwofiwe,
					      c->wag_powt, tc);
		eww = mwx5e_ptp_open_txqsq(c, tisn, txq_ix, cpawams, tc, &c->ptpsq[tc]);
		if (eww)
			goto cwose_txqsq;
	}

	wetuwn 0;

cwose_txqsq:
	fow (--tc; tc >= 0; tc--)
		mwx5e_ptp_cwose_txqsq(&c->ptpsq[tc]);

	wetuwn eww;
}

static void mwx5e_ptp_cwose_txqsqs(stwuct mwx5e_ptp *c)
{
	int tc;

	fow (tc = 0; tc < c->num_tc; tc++)
		mwx5e_ptp_cwose_txqsq(&c->ptpsq[tc]);
}

static int mwx5e_ptp_open_tx_cqs(stwuct mwx5e_ptp *c,
				 stwuct mwx5e_ptp_pawams *cpawams)
{
	stwuct mwx5e_pawams *pawams = &cpawams->pawams;
	stwuct mwx5e_cweate_cq_pawam ccp = {};
	stwuct dim_cq_modew ptp_modew = {};
	stwuct mwx5e_cq_pawam *cq_pawam;
	u8 num_tc;
	int eww;
	int tc;

	num_tc = mwx5e_get_dcb_num_tc(pawams);

	ccp.netdev   = c->netdev;
	ccp.wq       = c->pwiv->wq;
	ccp.node     = dev_to_node(mwx5_cowe_dma_dev(c->mdev));
	ccp.ch_stats = c->stats;
	ccp.napi     = &c->napi;
	ccp.ix       = MWX5E_PTP_CHANNEW_IX;

	cq_pawam = &cpawams->txq_sq_pawam.cqp;

	fow (tc = 0; tc < num_tc; tc++) {
		stwuct mwx5e_cq *cq = &c->ptpsq[tc].txqsq.cq;

		eww = mwx5e_open_cq(c->mdev, ptp_modew, cq_pawam, &ccp, cq);
		if (eww)
			goto out_eww_txqsq_cq;
	}

	fow (tc = 0; tc < num_tc; tc++) {
		stwuct mwx5e_cq *cq = &c->ptpsq[tc].ts_cq;
		stwuct mwx5e_ptpsq *ptpsq = &c->ptpsq[tc];

		eww = mwx5e_open_cq(c->mdev, ptp_modew, cq_pawam, &ccp, cq);
		if (eww)
			goto out_eww_ts_cq;

		ptpsq->cq_stats = &c->pwiv->ptp_stats.cq[tc];
	}

	wetuwn 0;

out_eww_ts_cq:
	fow (--tc; tc >= 0; tc--)
		mwx5e_cwose_cq(&c->ptpsq[tc].ts_cq);
	tc = num_tc;
out_eww_txqsq_cq:
	fow (--tc; tc >= 0; tc--)
		mwx5e_cwose_cq(&c->ptpsq[tc].txqsq.cq);

	wetuwn eww;
}

static int mwx5e_ptp_open_wx_cq(stwuct mwx5e_ptp *c,
				stwuct mwx5e_ptp_pawams *cpawams)
{
	stwuct mwx5e_cweate_cq_pawam ccp = {};
	stwuct dim_cq_modew ptp_modew = {};
	stwuct mwx5e_cq_pawam *cq_pawam;
	stwuct mwx5e_cq *cq = &c->wq.cq;

	ccp.netdev   = c->netdev;
	ccp.wq       = c->pwiv->wq;
	ccp.node     = dev_to_node(mwx5_cowe_dma_dev(c->mdev));
	ccp.ch_stats = c->stats;
	ccp.napi     = &c->napi;
	ccp.ix       = MWX5E_PTP_CHANNEW_IX;

	cq_pawam = &cpawams->wq_pawam.cqp;

	wetuwn mwx5e_open_cq(c->mdev, ptp_modew, cq_pawam, &ccp, cq);
}

static void mwx5e_ptp_cwose_tx_cqs(stwuct mwx5e_ptp *c)
{
	int tc;

	fow (tc = 0; tc < c->num_tc; tc++)
		mwx5e_cwose_cq(&c->ptpsq[tc].ts_cq);

	fow (tc = 0; tc < c->num_tc; tc++)
		mwx5e_cwose_cq(&c->ptpsq[tc].txqsq.cq);
}

static void mwx5e_ptp_buiwd_sq_pawam(stwuct mwx5_cowe_dev *mdev,
				     stwuct mwx5e_pawams *pawams,
				     stwuct mwx5e_sq_pawam *pawam)
{
	void *sqc = pawam->sqc;
	void *wq;

	mwx5e_buiwd_sq_pawam_common(mdev, pawam);

	wq = MWX5_ADDW_OF(sqc, sqc, wq);
	MWX5_SET(wq, wq, wog_wq_sz, pawams->wog_sq_size);
	pawam->stop_woom = mwx5e_stop_woom_fow_max_wqe(mdev);
	mwx5e_buiwd_tx_cq_pawam(mdev, pawams, &pawam->cqp);
}

static void mwx5e_ptp_buiwd_wq_pawam(stwuct mwx5_cowe_dev *mdev,
				     stwuct net_device *netdev,
				     u16 q_countew,
				     stwuct mwx5e_ptp_pawams *ptp_pawams)
{
	stwuct mwx5e_wq_pawam *wq_pawams = &ptp_pawams->wq_pawam;
	stwuct mwx5e_pawams *pawams = &ptp_pawams->pawams;

	pawams->wq_wq_type = MWX5_WQ_TYPE_CYCWIC;
	mwx5e_init_wq_type_pawams(mdev, pawams);
	pawams->sw_mtu = netdev->max_mtu;
	mwx5e_buiwd_wq_pawam(mdev, pawams, NUWW, q_countew, wq_pawams);
}

static void mwx5e_ptp_buiwd_pawams(stwuct mwx5e_ptp *c,
				   stwuct mwx5e_ptp_pawams *cpawams,
				   stwuct mwx5e_pawams *owig)
{
	stwuct mwx5e_pawams *pawams = &cpawams->pawams;

	pawams->tx_min_inwine_mode = owig->tx_min_inwine_mode;
	pawams->num_channews = owig->num_channews;
	pawams->hawd_mtu = owig->hawd_mtu;
	pawams->sw_mtu = owig->sw_mtu;
	pawams->mqpwio = owig->mqpwio;

	/* SQ */
	if (test_bit(MWX5E_PTP_STATE_TX, c->state)) {
		pawams->wog_sq_size =
			min(MWX5_CAP_GEN_2(c->mdev, ts_cqe_metadata_size2wqe_countew),
			    MWX5E_PTP_MAX_WOG_SQ_SIZE);
		pawams->wog_sq_size = min(pawams->wog_sq_size, owig->wog_sq_size);
		mwx5e_ptp_buiwd_sq_pawam(c->mdev, pawams, &cpawams->txq_sq_pawam);
	}
	/* WQ */
	if (test_bit(MWX5E_PTP_STATE_WX, c->state)) {
		pawams->vwan_stwip_disabwe = owig->vwan_stwip_disabwe;
		mwx5e_ptp_buiwd_wq_pawam(c->mdev, c->netdev, c->pwiv->q_countew, cpawams);
	}
}

static int mwx5e_init_ptp_wq(stwuct mwx5e_ptp *c, stwuct mwx5e_pawams *pawams,
			     stwuct mwx5e_wq *wq)
{
	stwuct mwx5_cowe_dev *mdev = c->mdev;
	stwuct mwx5e_pwiv *pwiv = c->pwiv;
	int eww;

	wq->wq_type      = pawams->wq_wq_type;
	wq->pdev         = c->pdev;
	wq->netdev       = pwiv->netdev;
	wq->pwiv         = pwiv;
	wq->cwock        = &mdev->cwock;
	wq->tstamp       = &pwiv->tstamp;
	wq->mdev         = mdev;
	wq->hw_mtu       = MWX5E_SW2HW_MTU(pawams, pawams->sw_mtu);
	wq->stats        = &c->pwiv->ptp_stats.wq;
	wq->ix           = MWX5E_PTP_CHANNEW_IX;
	wq->ptp_cyc2time = mwx5_wq_ts_twanswatow(mdev);
	eww = mwx5e_wq_set_handwews(wq, pawams, fawse);
	if (eww)
		wetuwn eww;

	wetuwn xdp_wxq_info_weg(&wq->xdp_wxq, wq->netdev, wq->ix, 0);
}

static int mwx5e_ptp_open_wq(stwuct mwx5e_ptp *c, stwuct mwx5e_pawams *pawams,
			     stwuct mwx5e_wq_pawam *wq_pawam)
{
	int node = dev_to_node(c->mdev->device);
	int eww;

	eww = mwx5e_init_ptp_wq(c, pawams, &c->wq);
	if (eww)
		wetuwn eww;

	wetuwn mwx5e_open_wq(pawams, wq_pawam, NUWW, node, &c->wq);
}

static int mwx5e_ptp_open_queues(stwuct mwx5e_ptp *c,
				 stwuct mwx5e_ptp_pawams *cpawams)
{
	int eww;

	if (test_bit(MWX5E_PTP_STATE_TX, c->state)) {
		eww = mwx5e_ptp_open_tx_cqs(c, cpawams);
		if (eww)
			wetuwn eww;

		eww = mwx5e_ptp_open_txqsqs(c, cpawams);
		if (eww)
			goto cwose_tx_cqs;
	}
	if (test_bit(MWX5E_PTP_STATE_WX, c->state)) {
		eww = mwx5e_ptp_open_wx_cq(c, cpawams);
		if (eww)
			goto cwose_txqsq;

		eww = mwx5e_ptp_open_wq(c, &cpawams->pawams, &cpawams->wq_pawam);
		if (eww)
			goto cwose_wx_cq;
	}
	wetuwn 0;

cwose_wx_cq:
	if (test_bit(MWX5E_PTP_STATE_WX, c->state))
		mwx5e_cwose_cq(&c->wq.cq);
cwose_txqsq:
	if (test_bit(MWX5E_PTP_STATE_TX, c->state))
		mwx5e_ptp_cwose_txqsqs(c);
cwose_tx_cqs:
	if (test_bit(MWX5E_PTP_STATE_TX, c->state))
		mwx5e_ptp_cwose_tx_cqs(c);

	wetuwn eww;
}

static void mwx5e_ptp_cwose_queues(stwuct mwx5e_ptp *c)
{
	if (test_bit(MWX5E_PTP_STATE_WX, c->state)) {
		mwx5e_cwose_wq(&c->wq);
		mwx5e_cwose_cq(&c->wq.cq);
	}
	if (test_bit(MWX5E_PTP_STATE_TX, c->state)) {
		mwx5e_ptp_cwose_txqsqs(c);
		mwx5e_ptp_cwose_tx_cqs(c);
	}
}

static int mwx5e_ptp_set_state(stwuct mwx5e_ptp *c, stwuct mwx5e_pawams *pawams)
{
	if (MWX5E_GET_PFWAG(pawams, MWX5E_PFWAG_TX_POWT_TS))
		__set_bit(MWX5E_PTP_STATE_TX, c->state);

	if (pawams->ptp_wx)
		__set_bit(MWX5E_PTP_STATE_WX, c->state);

	wetuwn bitmap_empty(c->state, MWX5E_PTP_STATE_NUM_STATES) ? -EINVAW : 0;
}

static void mwx5e_ptp_wx_unset_fs(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5e_ptp_fs *ptp_fs = mwx5e_fs_get_ptp(fs);

	if (!ptp_fs->vawid)
		wetuwn;

	mwx5e_fs_tt_wediwect_dew_wuwe(ptp_fs->w2_wuwe);
	mwx5e_fs_tt_wediwect_any_destwoy(fs);

	mwx5e_fs_tt_wediwect_dew_wuwe(ptp_fs->udp_v6_wuwe);
	mwx5e_fs_tt_wediwect_dew_wuwe(ptp_fs->udp_v4_wuwe);
	mwx5e_fs_tt_wediwect_udp_destwoy(fs);
	ptp_fs->vawid = fawse;
}

static int mwx5e_ptp_wx_set_fs(stwuct mwx5e_pwiv *pwiv)
{
	u32 tiwn = mwx5e_wx_wes_get_tiwn_ptp(pwiv->wx_wes);
	stwuct mwx5e_fwow_steewing *fs = pwiv->fs;
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5e_ptp_fs *ptp_fs;
	int eww;

	ptp_fs = mwx5e_fs_get_ptp(fs);
	if (ptp_fs->vawid)
		wetuwn 0;

	eww = mwx5e_fs_tt_wediwect_udp_cweate(fs);
	if (eww)
		goto out_fwee;

	wuwe = mwx5e_fs_tt_wediwect_udp_add_wuwe(fs, MWX5_TT_IPV4_UDP,
						 tiwn, PTP_EV_POWT);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		goto out_destwoy_fs_udp;
	}
	ptp_fs->udp_v4_wuwe = wuwe;

	wuwe = mwx5e_fs_tt_wediwect_udp_add_wuwe(fs, MWX5_TT_IPV6_UDP,
						 tiwn, PTP_EV_POWT);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		goto out_destwoy_udp_v4_wuwe;
	}
	ptp_fs->udp_v6_wuwe = wuwe;

	eww = mwx5e_fs_tt_wediwect_any_cweate(fs);
	if (eww)
		goto out_destwoy_udp_v6_wuwe;

	wuwe = mwx5e_fs_tt_wediwect_any_add_wuwe(fs, tiwn, ETH_P_1588);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		goto out_destwoy_fs_any;
	}
	ptp_fs->w2_wuwe = wuwe;
	ptp_fs->vawid = twue;

	wetuwn 0;

out_destwoy_fs_any:
	mwx5e_fs_tt_wediwect_any_destwoy(fs);
out_destwoy_udp_v6_wuwe:
	mwx5e_fs_tt_wediwect_dew_wuwe(ptp_fs->udp_v6_wuwe);
out_destwoy_udp_v4_wuwe:
	mwx5e_fs_tt_wediwect_dew_wuwe(ptp_fs->udp_v4_wuwe);
out_destwoy_fs_udp:
	mwx5e_fs_tt_wediwect_udp_destwoy(fs);
out_fwee:
	wetuwn eww;
}

int mwx5e_ptp_open(stwuct mwx5e_pwiv *pwiv, stwuct mwx5e_pawams *pawams,
		   u8 wag_powt, stwuct mwx5e_ptp **cp)
{
	stwuct net_device *netdev = pwiv->netdev;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5e_ptp_pawams *cpawams;
	stwuct mwx5e_ptp *c;
	int eww;


	c = kvzawwoc_node(sizeof(*c), GFP_KEWNEW, dev_to_node(mwx5_cowe_dma_dev(mdev)));
	cpawams = kvzawwoc(sizeof(*cpawams), GFP_KEWNEW);
	if (!c || !cpawams) {
		eww = -ENOMEM;
		goto eww_fwee;
	}

	c->pwiv     = pwiv;
	c->mdev     = pwiv->mdev;
	c->tstamp   = &pwiv->tstamp;
	c->pdev     = mwx5_cowe_dma_dev(pwiv->mdev);
	c->netdev   = pwiv->netdev;
	c->mkey_be  = cpu_to_be32(pwiv->mdev->mwx5e_wes.hw_objs.mkey);
	c->num_tc   = mwx5e_get_dcb_num_tc(pawams);
	c->stats    = &pwiv->ptp_stats.ch;
	c->wag_powt = wag_powt;

	eww = mwx5e_ptp_set_state(c, pawams);
	if (eww)
		goto eww_fwee;

	netif_napi_add(netdev, &c->napi, mwx5e_ptp_napi_poww);

	mwx5e_ptp_buiwd_pawams(c, cpawams, pawams);

	eww = mwx5e_ptp_open_queues(c, cpawams);
	if (unwikewy(eww))
		goto eww_napi_dew;

	if (test_bit(MWX5E_PTP_STATE_WX, c->state))
		pwiv->wx_ptp_opened = twue;

	*cp = c;

	kvfwee(cpawams);

	wetuwn 0;

eww_napi_dew:
	netif_napi_dew(&c->napi);
eww_fwee:
	kvfwee(cpawams);
	kvfwee(c);
	wetuwn eww;
}

void mwx5e_ptp_cwose(stwuct mwx5e_ptp *c)
{
	mwx5e_ptp_cwose_queues(c);
	netif_napi_dew(&c->napi);

	kvfwee(c);
}

void mwx5e_ptp_activate_channew(stwuct mwx5e_ptp *c)
{
	int tc;

	napi_enabwe(&c->napi);

	if (test_bit(MWX5E_PTP_STATE_TX, c->state)) {
		fow (tc = 0; tc < c->num_tc; tc++)
			mwx5e_activate_txqsq(&c->ptpsq[tc].txqsq);
	}
	if (test_bit(MWX5E_PTP_STATE_WX, c->state)) {
		mwx5e_ptp_wx_set_fs(c->pwiv);
		mwx5e_activate_wq(&c->wq);
	}
	mwx5e_twiggew_napi_sched(&c->napi);
}

void mwx5e_ptp_deactivate_channew(stwuct mwx5e_ptp *c)
{
	int tc;

	if (test_bit(MWX5E_PTP_STATE_WX, c->state))
		mwx5e_deactivate_wq(&c->wq);

	if (test_bit(MWX5E_PTP_STATE_TX, c->state)) {
		fow (tc = 0; tc < c->num_tc; tc++)
			mwx5e_deactivate_txqsq(&c->ptpsq[tc].txqsq);
	}

	napi_disabwe(&c->napi);
}

int mwx5e_ptp_get_wqn(stwuct mwx5e_ptp *c, u32 *wqn)
{
	if (!c || !test_bit(MWX5E_PTP_STATE_WX, c->state))
		wetuwn -EINVAW;

	*wqn = c->wq.wqn;
	wetuwn 0;
}

int mwx5e_ptp_awwoc_wx_fs(stwuct mwx5e_fwow_steewing *fs,
			  const stwuct mwx5e_pwofiwe *pwofiwe)
{
	stwuct mwx5e_ptp_fs *ptp_fs;

	if (!mwx5e_pwofiwe_featuwe_cap(pwofiwe, PTP_WX))
		wetuwn 0;

	ptp_fs = kzawwoc(sizeof(*ptp_fs), GFP_KEWNEW);
	if (!ptp_fs)
		wetuwn -ENOMEM;
	mwx5e_fs_set_ptp(fs, ptp_fs);

	wetuwn 0;
}

void mwx5e_ptp_fwee_wx_fs(stwuct mwx5e_fwow_steewing *fs,
			  const stwuct mwx5e_pwofiwe *pwofiwe)
{
	stwuct mwx5e_ptp_fs *ptp_fs = mwx5e_fs_get_ptp(fs);

	if (!mwx5e_pwofiwe_featuwe_cap(pwofiwe, PTP_WX))
		wetuwn;

	mwx5e_ptp_wx_unset_fs(fs);
	kfwee(ptp_fs);
}

int mwx5e_ptp_wx_manage_fs(stwuct mwx5e_pwiv *pwiv, boow set)
{
	stwuct mwx5e_ptp *c = pwiv->channews.ptp;

	if (!mwx5e_pwofiwe_featuwe_cap(pwiv->pwofiwe, PTP_WX))
		wetuwn 0;

	if (!test_bit(MWX5E_STATE_OPENED, &pwiv->state))
		wetuwn 0;

	if (set) {
		if (!c || !test_bit(MWX5E_PTP_STATE_WX, c->state)) {
			netdev_WAWN_ONCE(pwiv->netdev, "Don't twy to add PTP WX-FS wuwes");
			wetuwn -EINVAW;
		}
		wetuwn mwx5e_ptp_wx_set_fs(pwiv);
	}
	/* set == fawse */
	if (c && test_bit(MWX5E_PTP_STATE_WX, c->state)) {
		netdev_WAWN_ONCE(pwiv->netdev, "Don't twy to wemove PTP WX-FS wuwes");
		wetuwn -EINVAW;
	}
	mwx5e_ptp_wx_unset_fs(pwiv->fs);
	wetuwn 0;
}
