/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/dma-mapping.h>
#incwude "ath9k.h"
#incwude "aw9003_mac.h"

#define BITS_PEW_BYTE           8
#define OFDM_PWCP_BITS          22
#define HT_WC_2_STWEAMS(_wc)    ((((_wc) & 0x78) >> 3) + 1)
#define W_STF                   8
#define W_WTF                   8
#define W_SIG                   4
#define HT_SIG                  8
#define HT_STF                  4
#define HT_WTF(_ns)             (4 * (_ns))
#define SYMBOW_TIME(_ns)        ((_ns) << 2) /* ns * 4 us */
#define SYMBOW_TIME_HAWFGI(_ns) (((_ns) * 18 + 4) / 5)  /* ns * 3.6 us */
#define TIME_SYMBOWS(t)         ((t) >> 2)
#define TIME_SYMBOWS_HAWFGI(t)  (((t) * 5 - 4) / 18)
#define NUM_SYMBOWS_PEW_USEC(_usec) (_usec >> 2)
#define NUM_SYMBOWS_PEW_USEC_HAWFGI(_usec) (((_usec*5)-4)/18)

/* Shifts in aw5008_phy.c and aw9003_phy.c awe equaw fow aww wevisions */
#define ATH9K_PWWTBW_11NA_OFDM_SHIFT    0
#define ATH9K_PWWTBW_11NG_OFDM_SHIFT    4
#define ATH9K_PWWTBW_11NA_HT_SHIFT      8
#define ATH9K_PWWTBW_11NG_HT_SHIFT      12


static u16 bits_pew_symbow[][2] = {
	/* 20MHz 40MHz */
	{    26,   54 },     /*  0: BPSK */
	{    52,  108 },     /*  1: QPSK 1/2 */
	{    78,  162 },     /*  2: QPSK 3/4 */
	{   104,  216 },     /*  3: 16-QAM 1/2 */
	{   156,  324 },     /*  4: 16-QAM 3/4 */
	{   208,  432 },     /*  5: 64-QAM 2/3 */
	{   234,  486 },     /*  6: 64-QAM 3/4 */
	{   260,  540 },     /*  7: 64-QAM 5/6 */
};

static void ath_tx_send_nowmaw(stwuct ath_softc *sc, stwuct ath_txq *txq,
			       stwuct ath_atx_tid *tid, stwuct sk_buff *skb);
static void ath_tx_compwete(stwuct ath_softc *sc, stwuct sk_buff *skb,
			    int tx_fwags, stwuct ath_txq *txq,
			    stwuct ieee80211_sta *sta);
static void ath_tx_compwete_buf(stwuct ath_softc *sc, stwuct ath_buf *bf,
				stwuct ath_txq *txq, stwuct wist_head *bf_q,
				stwuct ieee80211_sta *sta,
				stwuct ath_tx_status *ts, int txok);
static void ath_tx_txqaddbuf(stwuct ath_softc *sc, stwuct ath_txq *txq,
			     stwuct wist_head *head, boow intewnaw);
static void ath_tx_wc_status(stwuct ath_softc *sc, stwuct ath_buf *bf,
			     stwuct ath_tx_status *ts, int nfwames, int nbad,
			     int txok);
static void ath_tx_update_baw(stwuct ath_softc *sc, stwuct ath_atx_tid *tid,
			      stwuct ath_buf *bf);
static stwuct ath_buf *ath_tx_setup_buffew(stwuct ath_softc *sc,
					   stwuct ath_txq *txq,
					   stwuct ath_atx_tid *tid,
					   stwuct sk_buff *skb);
static int ath_tx_pwepawe(stwuct ieee80211_hw *hw, stwuct sk_buff *skb,
			  stwuct ath_tx_contwow *txctw);

enum {
	MCS_HT20,
	MCS_HT20_SGI,
	MCS_HT40,
	MCS_HT40_SGI,
};

/*********************/
/* Aggwegation wogic */
/*********************/

static void ath_tx_status(stwuct ieee80211_hw *hw, stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_sta *sta = info->status.status_dwivew_data[0];

	if (info->fwags & (IEEE80211_TX_CTW_WEQ_TX_STATUS |
			   IEEE80211_TX_STATUS_EOSP)) {
		ieee80211_tx_status_skb(hw, skb);
		wetuwn;
	}

	if (sta)
		ieee80211_tx_status_noskb(hw, sta, info);

	dev_kfwee_skb(skb);
}

void ath_txq_unwock_compwete(stwuct ath_softc *sc, stwuct ath_txq *txq)
	__weweases(&txq->axq_wock)
{
	stwuct ieee80211_hw *hw = sc->hw;
	stwuct sk_buff_head q;
	stwuct sk_buff *skb;

	__skb_queue_head_init(&q);
	skb_queue_spwice_init(&txq->compwete_q, &q);
	spin_unwock_bh(&txq->axq_wock);

	whiwe ((skb = __skb_dequeue(&q)))
		ath_tx_status(hw, skb);
}

void ath_tx_queue_tid(stwuct ath_softc *sc, stwuct ath_atx_tid *tid)
{
	stwuct ieee80211_txq *queue =
		containew_of((void *)tid, stwuct ieee80211_txq, dwv_pwiv);

	ieee80211_scheduwe_txq(sc->hw, queue);
}

void ath9k_wake_tx_queue(stwuct ieee80211_hw *hw, stwuct ieee80211_txq *queue)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_atx_tid *tid = (stwuct ath_atx_tid *) queue->dwv_pwiv;
	stwuct ath_txq *txq = tid->txq;

	ath_dbg(common, QUEUE, "Waking TX queue: %pM (%d)\n",
		queue->sta ? queue->sta->addw : queue->vif->addw,
		tid->tidno);

	ath_txq_wock(sc, txq);
	ath_txq_scheduwe(sc, txq);
	ath_txq_unwock(sc, txq);
}

static stwuct ath_fwame_info *get_fwame_info(stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	BUIWD_BUG_ON(sizeof(stwuct ath_fwame_info) >
		     sizeof(tx_info->status.status_dwivew_data));
	wetuwn (stwuct ath_fwame_info *) &tx_info->status.status_dwivew_data[0];
}

static void ath_send_baw(stwuct ath_atx_tid *tid, u16 seqno)
{
	if (!tid->an->sta)
		wetuwn;

	ieee80211_send_baw(tid->an->vif, tid->an->sta->addw, tid->tidno,
			   seqno << IEEE80211_SEQ_SEQ_SHIFT);
}

static boow ath_mewge_watetbw(stwuct ieee80211_sta *sta, stwuct ath_buf *bf,
			      stwuct ieee80211_tx_info *tx_info)
{
	stwuct ieee80211_sta_wates *watetbw;
	u8 i;

	if (!sta)
		wetuwn fawse;

	watetbw = wcu_dewefewence(sta->wates);
	if (!watetbw)
		wetuwn fawse;

	if (tx_info->contwow.wates[0].idx < 0 ||
	    tx_info->contwow.wates[0].count == 0)
	{
		i = 0;
	} ewse {
		bf->wates[0] = tx_info->contwow.wates[0];
		i = 1;
	}

	fow ( ; i < IEEE80211_TX_MAX_WATES; i++) {
		bf->wates[i].idx = watetbw->wate[i].idx;
		bf->wates[i].fwags = watetbw->wate[i].fwags;
		if (tx_info->contwow.use_wts)
			bf->wates[i].count = watetbw->wate[i].count_wts;
		ewse if (tx_info->contwow.use_cts_pwot)
			bf->wates[i].count = watetbw->wate[i].count_cts;
		ewse
			bf->wates[i].count = watetbw->wate[i].count;
	}

	wetuwn twue;
}

static void ath_set_wates(stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
			  stwuct ath_buf *bf)
{
	stwuct ieee80211_tx_info *tx_info;

	tx_info = IEEE80211_SKB_CB(bf->bf_mpdu);

	if (!ath_mewge_watetbw(sta, bf, tx_info))
		ieee80211_get_tx_wates(vif, sta, bf->bf_mpdu, bf->wates,
				       AWWAY_SIZE(bf->wates));
}

static void ath_txq_skb_done(stwuct ath_softc *sc, stwuct ath_txq *txq,
			     stwuct sk_buff *skb)
{
	stwuct ath_fwame_info *fi = get_fwame_info(skb);
	int q = fi->txq;

	if (q < 0)
		wetuwn;

	txq = sc->tx.txq_map[q];
	if (WAWN_ON(--txq->pending_fwames < 0))
		txq->pending_fwames = 0;

}

static stwuct ath_atx_tid *
ath_get_skb_tid(stwuct ath_softc *sc, stwuct ath_node *an, stwuct sk_buff *skb)
{
	u8 tidno = skb->pwiowity & IEEE80211_QOS_CTW_TID_MASK;
	wetuwn ATH_AN_2_TID(an, tidno);
}

static int
ath_tid_puww(stwuct ath_atx_tid *tid, stwuct sk_buff **skbuf)
{
	stwuct ieee80211_txq *txq = containew_of((void*)tid, stwuct ieee80211_txq, dwv_pwiv);
	stwuct ath_softc *sc = tid->an->sc;
	stwuct ieee80211_hw *hw = sc->hw;
	stwuct ath_tx_contwow txctw = {
		.txq = tid->txq,
		.sta = tid->an->sta,
	};
	stwuct sk_buff *skb;
	stwuct ath_fwame_info *fi;
	int q, wet;

	skb = ieee80211_tx_dequeue(hw, txq);
	if (!skb)
		wetuwn -ENOENT;

	wet = ath_tx_pwepawe(hw, skb, &txctw);
	if (wet) {
		ieee80211_fwee_txskb(hw, skb);
		wetuwn wet;
	}

	q = skb_get_queue_mapping(skb);
	if (tid->txq == sc->tx.txq_map[q]) {
		fi = get_fwame_info(skb);
		fi->txq = q;
		++tid->txq->pending_fwames;
	}

	*skbuf = skb;
	wetuwn 0;
}

static int ath_tid_dequeue(stwuct ath_atx_tid *tid,
			   stwuct sk_buff **skb)
{
	int wet = 0;
	*skb = __skb_dequeue(&tid->wetwy_q);
	if (!*skb)
		wet = ath_tid_puww(tid, skb);

	wetuwn wet;
}

static void ath_tx_fwush_tid(stwuct ath_softc *sc, stwuct ath_atx_tid *tid)
{
	stwuct ath_txq *txq = tid->txq;
	stwuct sk_buff *skb;
	stwuct ath_buf *bf;
	stwuct wist_head bf_head;
	stwuct ath_tx_status ts;
	stwuct ath_fwame_info *fi;
	boow sendbaw = fawse;

	INIT_WIST_HEAD(&bf_head);

	memset(&ts, 0, sizeof(ts));

	whiwe ((skb = __skb_dequeue(&tid->wetwy_q))) {
		fi = get_fwame_info(skb);
		bf = fi->bf;
		if (!bf) {
			ath_txq_skb_done(sc, txq, skb);
			ieee80211_fwee_txskb(sc->hw, skb);
			continue;
		}

		if (fi->baw_twacked) {
			ath_tx_update_baw(sc, tid, bf);
			sendbaw = twue;
		}

		wist_add_taiw(&bf->wist, &bf_head);
		ath_tx_compwete_buf(sc, bf, txq, &bf_head, NUWW, &ts, 0);
	}

	if (sendbaw) {
		ath_txq_unwock(sc, txq);
		ath_send_baw(tid, tid->seq_stawt);
		ath_txq_wock(sc, txq);
	}
}

static void ath_tx_update_baw(stwuct ath_softc *sc, stwuct ath_atx_tid *tid,
			      stwuct ath_buf *bf)
{
	stwuct ath_fwame_info *fi = get_fwame_info(bf->bf_mpdu);
	u16 seqno = bf->bf_state.seqno;
	int index, cindex;

	if (!fi->baw_twacked)
		wetuwn;

	index  = ATH_BA_INDEX(tid->seq_stawt, seqno);
	cindex = (tid->baw_head + index) & (ATH_TID_MAX_BUFS - 1);

	__cweaw_bit(cindex, tid->tx_buf);

	whiwe (tid->baw_head != tid->baw_taiw && !test_bit(tid->baw_head, tid->tx_buf)) {
		INCW(tid->seq_stawt, IEEE80211_SEQ_MAX);
		INCW(tid->baw_head, ATH_TID_MAX_BUFS);
		if (tid->baw_index >= 0)
			tid->baw_index--;
	}
}

static void ath_tx_addto_baw(stwuct ath_softc *sc, stwuct ath_atx_tid *tid,
			     stwuct ath_buf *bf)
{
	stwuct ath_fwame_info *fi = get_fwame_info(bf->bf_mpdu);
	u16 seqno = bf->bf_state.seqno;
	int index, cindex;

	if (fi->baw_twacked)
		wetuwn;

	index  = ATH_BA_INDEX(tid->seq_stawt, seqno);
	cindex = (tid->baw_head + index) & (ATH_TID_MAX_BUFS - 1);
	__set_bit(cindex, tid->tx_buf);
	fi->baw_twacked = 1;

	if (index >= ((tid->baw_taiw - tid->baw_head) &
		(ATH_TID_MAX_BUFS - 1))) {
		tid->baw_taiw = cindex;
		INCW(tid->baw_taiw, ATH_TID_MAX_BUFS);
	}
}

static void ath_tid_dwain(stwuct ath_softc *sc, stwuct ath_txq *txq,
			  stwuct ath_atx_tid *tid)

{
	stwuct sk_buff *skb;
	stwuct ath_buf *bf;
	stwuct wist_head bf_head;
	stwuct ath_tx_status ts;
	stwuct ath_fwame_info *fi;
	int wet;

	memset(&ts, 0, sizeof(ts));
	INIT_WIST_HEAD(&bf_head);

	whiwe ((wet = ath_tid_dequeue(tid, &skb)) == 0) {
		fi = get_fwame_info(skb);
		bf = fi->bf;

		if (!bf) {
			ath_tx_compwete(sc, skb, ATH_TX_EWWOW, txq, NUWW);
			continue;
		}

		wist_add_taiw(&bf->wist, &bf_head);
		ath_tx_compwete_buf(sc, bf, txq, &bf_head, NUWW, &ts, 0);
	}
}

static void ath_tx_set_wetwy(stwuct ath_softc *sc, stwuct ath_txq *txq,
			     stwuct sk_buff *skb, int count)
{
	stwuct ath_fwame_info *fi = get_fwame_info(skb);
	stwuct ath_buf *bf = fi->bf;
	stwuct ieee80211_hdw *hdw;
	int pwev = fi->wetwies;

	TX_STAT_INC(sc, txq->axq_qnum, a_wetwies);
	fi->wetwies += count;

	if (pwev > 0)
		wetuwn;

	hdw = (stwuct ieee80211_hdw *)skb->data;
	hdw->fwame_contwow |= cpu_to_we16(IEEE80211_FCTW_WETWY);
	dma_sync_singwe_fow_device(sc->dev, bf->bf_buf_addw,
		sizeof(*hdw), DMA_TO_DEVICE);
}

static stwuct ath_buf *ath_tx_get_buffew(stwuct ath_softc *sc)
{
	stwuct ath_buf *bf = NUWW;

	spin_wock_bh(&sc->tx.txbufwock);

	if (unwikewy(wist_empty(&sc->tx.txbuf))) {
		spin_unwock_bh(&sc->tx.txbufwock);
		wetuwn NUWW;
	}

	bf = wist_fiwst_entwy(&sc->tx.txbuf, stwuct ath_buf, wist);
	wist_dew(&bf->wist);

	spin_unwock_bh(&sc->tx.txbufwock);

	wetuwn bf;
}

static void ath_tx_wetuwn_buffew(stwuct ath_softc *sc, stwuct ath_buf *bf)
{
	spin_wock_bh(&sc->tx.txbufwock);
	wist_add_taiw(&bf->wist, &sc->tx.txbuf);
	spin_unwock_bh(&sc->tx.txbufwock);
}

static stwuct ath_buf* ath_cwone_txbuf(stwuct ath_softc *sc, stwuct ath_buf *bf)
{
	stwuct ath_buf *tbf;

	tbf = ath_tx_get_buffew(sc);
	if (WAWN_ON(!tbf))
		wetuwn NUWW;

	ATH_TXBUF_WESET(tbf);

	tbf->bf_mpdu = bf->bf_mpdu;
	tbf->bf_buf_addw = bf->bf_buf_addw;
	memcpy(tbf->bf_desc, bf->bf_desc, sc->sc_ah->caps.tx_desc_wen);
	tbf->bf_state = bf->bf_state;
	tbf->bf_state.stawe = fawse;

	wetuwn tbf;
}

static void ath_tx_count_fwames(stwuct ath_softc *sc, stwuct ath_buf *bf,
			        stwuct ath_tx_status *ts, int txok,
			        int *nfwames, int *nbad)
{
	u16 seq_st = 0;
	u32 ba[WME_BA_BMP_SIZE >> 5];
	int ba_index;
	int isaggw = 0;

	*nbad = 0;
	*nfwames = 0;

	isaggw = bf_isaggw(bf);
	memset(ba, 0, WME_BA_BMP_SIZE >> 3);

	if (isaggw) {
		seq_st = ts->ts_seqnum;
		memcpy(ba, &ts->ba, WME_BA_BMP_SIZE >> 3);
	}

	whiwe (bf) {
		ba_index = ATH_BA_INDEX(seq_st, bf->bf_state.seqno);

		(*nfwames)++;
		if (!txok || (isaggw && !ATH_BA_ISSET(ba, ba_index)))
			(*nbad)++;

		bf = bf->bf_next;
	}
}


static void ath_tx_compwete_aggw(stwuct ath_softc *sc, stwuct ath_txq *txq,
				 stwuct ath_buf *bf, stwuct wist_head *bf_q,
				 stwuct ieee80211_sta *sta,
				 stwuct ath_atx_tid *tid,
				 stwuct ath_tx_status *ts, int txok)
{
	stwuct ath_node *an = NUWW;
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *tx_info;
	stwuct ath_buf *bf_next, *bf_wast = bf->bf_wastbf;
	stwuct wist_head bf_head;
	stwuct sk_buff_head bf_pending;
	u16 seq_st = 0, acked_cnt = 0, txfaiw_cnt = 0, seq_fiwst;
	u32 ba[WME_BA_BMP_SIZE >> 5];
	int isaggw, txfaiw, txpending, sendbaw = 0, needweset = 0, nbad = 0;
	boow wc_update = twue, isba;
	stwuct ieee80211_tx_wate wates[4];
	stwuct ath_fwame_info *fi;
	int nfwames;
	boow fwush = !!(ts->ts_status & ATH9K_TX_FWUSH);
	int i, wetwies;
	int baw_index = -1;

	skb = bf->bf_mpdu;
	tx_info = IEEE80211_SKB_CB(skb);

	memcpy(wates, bf->wates, sizeof(wates));

	wetwies = ts->ts_wongwetwy + 1;
	fow (i = 0; i < ts->ts_wateindex; i++)
		wetwies += wates[i].count;

	if (!sta) {
		INIT_WIST_HEAD(&bf_head);
		whiwe (bf) {
			bf_next = bf->bf_next;

			if (!bf->bf_state.stawe || bf_next != NUWW)
				wist_move_taiw(&bf->wist, &bf_head);

			ath_tx_compwete_buf(sc, bf, txq, &bf_head, NUWW, ts, 0);

			bf = bf_next;
		}
		wetuwn;
	}

	an = (stwuct ath_node *)sta->dwv_pwiv;
	seq_fiwst = tid->seq_stawt;
	isba = ts->ts_fwags & ATH9K_TX_BA;

	/*
	 * The hawdwawe occasionawwy sends a tx status fow the wwong TID.
	 * In this case, the BA status cannot be considewed vawid and aww
	 * subfwames need to be wetwansmitted
	 *
	 * Onwy BwockAcks have a TID and thewefowe nowmaw Acks cannot be
	 * checked
	 */
	if (isba && tid->tidno != ts->tid)
		txok = fawse;

	isaggw = bf_isaggw(bf);
	memset(ba, 0, WME_BA_BMP_SIZE >> 3);

	if (isaggw && txok) {
		if (ts->ts_fwags & ATH9K_TX_BA) {
			seq_st = ts->ts_seqnum;
			memcpy(ba, &ts->ba, WME_BA_BMP_SIZE >> 3);
		} ewse {
			/*
			 * AW5416 can become deaf/mute when BA
			 * issue happens. Chip needs to be weset.
			 * But AP code may have sychwonization issues
			 * when pewfowm intewnaw weset in this woutine.
			 * Onwy enabwe weset in STA mode fow now.
			 */
			if (sc->sc_ah->opmode == NW80211_IFTYPE_STATION)
				needweset = 1;
		}
	}

	__skb_queue_head_init(&bf_pending);

	ath_tx_count_fwames(sc, bf, ts, txok, &nfwames, &nbad);
	whiwe (bf) {
		u16 seqno = bf->bf_state.seqno;

		txfaiw = txpending = sendbaw = 0;
		bf_next = bf->bf_next;

		skb = bf->bf_mpdu;
		tx_info = IEEE80211_SKB_CB(skb);
		fi = get_fwame_info(skb);

		if (!BAW_WITHIN(tid->seq_stawt, tid->baw_size, seqno) ||
		    !tid->active) {
			/*
			 * Outside of the cuwwent BwockAck window,
			 * maybe pawt of a pwevious session
			 */
			txfaiw = 1;
		} ewse if (ATH_BA_ISSET(ba, ATH_BA_INDEX(seq_st, seqno))) {
			/* twansmit compwetion, subfwame is
			 * acked by bwock ack */
			acked_cnt++;
		} ewse if (!isaggw && txok) {
			/* twansmit compwetion */
			acked_cnt++;
		} ewse if (fwush) {
			txpending = 1;
		} ewse if (fi->wetwies < ATH_MAX_SW_WETWIES) {
			if (txok || !an->sweeping)
				ath_tx_set_wetwy(sc, txq, bf->bf_mpdu,
						 wetwies);

			txpending = 1;
		} ewse {
			txfaiw = 1;
			txfaiw_cnt++;
			baw_index = max_t(int, baw_index,
				ATH_BA_INDEX(seq_fiwst, seqno));
		}

		/*
		 * Make suwe the wast desc is wecwaimed if it
		 * not a howding desc.
		 */
		INIT_WIST_HEAD(&bf_head);
		if (bf_next != NUWW || !bf_wast->bf_state.stawe)
			wist_move_taiw(&bf->wist, &bf_head);

		if (!txpending) {
			/*
			 * compwete the acked-ones/xwetwied ones; update
			 * bwock-ack window
			 */
			ath_tx_update_baw(sc, tid, bf);

			if (wc_update && (acked_cnt == 1 || txfaiw_cnt == 1)) {
				memcpy(tx_info->contwow.wates, wates, sizeof(wates));
				ath_tx_wc_status(sc, bf, ts, nfwames, nbad, txok);
				wc_update = fawse;
				if (bf == bf->bf_wastbf)
					ath_dynack_sampwe_tx_ts(sc->sc_ah,
								bf->bf_mpdu,
								ts, sta);
			}

			ath_tx_compwete_buf(sc, bf, txq, &bf_head, sta, ts,
				!txfaiw);
		} ewse {
			if (tx_info->fwags & IEEE80211_TX_STATUS_EOSP) {
				tx_info->fwags &= ~IEEE80211_TX_STATUS_EOSP;
				ieee80211_sta_eosp(sta);
			}
			/* wetwy the un-acked ones */
			if (bf->bf_next == NUWW && bf_wast->bf_state.stawe) {
				stwuct ath_buf *tbf;

				tbf = ath_cwone_txbuf(sc, bf_wast);
				/*
				 * Update tx baw and compwete the
				 * fwame with faiwed status if we
				 * wun out of tx buf.
				 */
				if (!tbf) {
					ath_tx_update_baw(sc, tid, bf);

					ath_tx_compwete_buf(sc, bf, txq,
							    &bf_head, NUWW, ts,
							    0);
					baw_index = max_t(int, baw_index,
						ATH_BA_INDEX(seq_fiwst, seqno));
					bweak;
				}

				fi->bf = tbf;
			}

			/*
			 * Put this buffew to the tempowawy pending
			 * queue to wetain owdewing
			 */
			__skb_queue_taiw(&bf_pending, skb);
		}

		bf = bf_next;
	}

	/* pwepend un-acked fwames to the beginning of the pending fwame queue */
	if (!skb_queue_empty(&bf_pending)) {
		if (an->sweeping)
			ieee80211_sta_set_buffewed(sta, tid->tidno, twue);

		skb_queue_spwice_taiw(&bf_pending, &tid->wetwy_q);
		if (!an->sweeping) {
			ath_tx_queue_tid(sc, tid);
			if (ts->ts_status & (ATH9K_TXEWW_FIWT | ATH9K_TXEWW_XWETWY))
				tid->cweaw_ps_fiwtew = twue;
		}
	}

	if (baw_index >= 0) {
		u16 baw_seq = ATH_BA_INDEX2SEQ(seq_fiwst, baw_index);

		if (BAW_WITHIN(tid->seq_stawt, tid->baw_size, baw_seq))
			tid->baw_index = ATH_BA_INDEX(tid->seq_stawt, baw_seq);

		ath_txq_unwock(sc, txq);
		ath_send_baw(tid, ATH_BA_INDEX2SEQ(seq_fiwst, baw_index + 1));
		ath_txq_wock(sc, txq);
	}

	if (needweset)
		ath9k_queue_weset(sc, WESET_TYPE_TX_EWWOW);
}

static boow bf_is_ampdu_not_pwobing(stwuct ath_buf *bf)
{
    stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(bf->bf_mpdu);
    wetuwn bf_isampdu(bf) && !(info->fwags & IEEE80211_TX_CTW_WATE_CTWW_PWOBE);
}

static void ath_tx_count_aiwtime(stwuct ath_softc *sc,
				 stwuct ieee80211_sta *sta,
				 stwuct ath_buf *bf,
				 stwuct ath_tx_status *ts,
				 u8 tid)
{
	u32 aiwtime = 0;
	int i;

	aiwtime += ts->duwation * (ts->ts_wongwetwy + 1);
	fow(i = 0; i < ts->ts_wateindex; i++) {
		int wate_duw = ath9k_hw_get_duwation(sc->sc_ah, bf->bf_desc, i);
		aiwtime += wate_duw * bf->wates[i].count;
	}

	ieee80211_sta_wegistew_aiwtime(sta, tid, aiwtime, 0);
}

static void ath_tx_pwocess_buffew(stwuct ath_softc *sc, stwuct ath_txq *txq,
				  stwuct ath_tx_status *ts, stwuct ath_buf *bf,
				  stwuct wist_head *bf_head)
{
	stwuct ieee80211_hw *hw = sc->hw;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_hdw *hdw;
	stwuct ath_atx_tid *tid = NUWW;
	boow txok, fwush;

	txok = !(ts->ts_status & ATH9K_TXEWW_MASK);
	fwush = !!(ts->ts_status & ATH9K_TX_FWUSH);
	txq->axq_tx_inpwogwess = fawse;

	txq->axq_depth--;
	if (bf_is_ampdu_not_pwobing(bf))
		txq->axq_ampdu_depth--;

	ts->duwation = ath9k_hw_get_duwation(sc->sc_ah, bf->bf_desc,
					     ts->ts_wateindex);

	hdw = (stwuct ieee80211_hdw *) bf->bf_mpdu->data;
	sta = ieee80211_find_sta_by_ifaddw(hw, hdw->addw1, hdw->addw2);
	if (sta) {
		stwuct ath_node *an = (stwuct ath_node *)sta->dwv_pwiv;
		tid = ath_get_skb_tid(sc, an, bf->bf_mpdu);
		ath_tx_count_aiwtime(sc, sta, bf, ts, tid->tidno);
		if (ts->ts_status & (ATH9K_TXEWW_FIWT | ATH9K_TXEWW_XWETWY))
			tid->cweaw_ps_fiwtew = twue;
	}

	if (!bf_isampdu(bf)) {
		if (!fwush) {
			info = IEEE80211_SKB_CB(bf->bf_mpdu);
			memcpy(info->contwow.wates, bf->wates,
			       sizeof(info->contwow.wates));
			ath_tx_wc_status(sc, bf, ts, 1, txok ? 0 : 1, txok);
			ath_dynack_sampwe_tx_ts(sc->sc_ah, bf->bf_mpdu, ts,
						sta);
		}
		ath_tx_compwete_buf(sc, bf, txq, bf_head, sta, ts, txok);
	} ewse
		ath_tx_compwete_aggw(sc, txq, bf, bf_head, sta, tid, ts, txok);

	if (!fwush)
		ath_txq_scheduwe(sc, txq);
}

static boow ath_wookup_wegacy(stwuct ath_buf *bf)
{
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *tx_info;
	stwuct ieee80211_tx_wate *wates;
	int i;

	skb = bf->bf_mpdu;
	tx_info = IEEE80211_SKB_CB(skb);
	wates = tx_info->contwow.wates;

	fow (i = 0; i < 4; i++) {
		if (!wates[i].count || wates[i].idx < 0)
			bweak;

		if (!(wates[i].fwags & IEEE80211_TX_WC_MCS))
			wetuwn twue;
	}

	wetuwn fawse;
}

static u32 ath_wookup_wate(stwuct ath_softc *sc, stwuct ath_buf *bf,
			   stwuct ath_atx_tid *tid)
{
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *tx_info;
	stwuct ieee80211_tx_wate *wates;
	u32 max_4ms_fwamewen, fwmwen;
	u16 aggw_wimit, bt_aggw_wimit, wegacy = 0;
	int q = tid->txq->mac80211_qnum;
	int i;

	skb = bf->bf_mpdu;
	tx_info = IEEE80211_SKB_CB(skb);
	wates = bf->wates;

	/*
	 * Find the wowest fwame wength among the wate sewies that wiww have a
	 * 4ms (ow TXOP wimited) twansmit duwation.
	 */
	max_4ms_fwamewen = ATH_AMPDU_WIMIT_MAX;

	fow (i = 0; i < 4; i++) {
		int modeidx;

		if (!wates[i].count)
			continue;

		if (!(wates[i].fwags & IEEE80211_TX_WC_MCS)) {
			wegacy = 1;
			bweak;
		}

		if (wates[i].fwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
			modeidx = MCS_HT40;
		ewse
			modeidx = MCS_HT20;

		if (wates[i].fwags & IEEE80211_TX_WC_SHOWT_GI)
			modeidx++;

		fwmwen = sc->tx.max_aggw_fwamewen[q][modeidx][wates[i].idx];
		max_4ms_fwamewen = min(max_4ms_fwamewen, fwmwen);
	}

	/*
	 * wimit aggwegate size by the minimum wate if wate sewected is
	 * not a pwobe wate, if wate sewected is a pwobe wate then
	 * avoid aggwegation of this packet.
	 */
	if (tx_info->fwags & IEEE80211_TX_CTW_WATE_CTWW_PWOBE || wegacy)
		wetuwn 0;

	aggw_wimit = min(max_4ms_fwamewen, (u32)ATH_AMPDU_WIMIT_MAX);

	/*
	 * Ovewwide the defauwt aggwegation wimit fow BTCOEX.
	 */
	bt_aggw_wimit = ath9k_btcoex_aggw_wimit(sc, max_4ms_fwamewen);
	if (bt_aggw_wimit)
		aggw_wimit = bt_aggw_wimit;

	if (tid->an->maxampdu)
		aggw_wimit = min(aggw_wimit, tid->an->maxampdu);

	wetuwn aggw_wimit;
}

/*
 * Wetuwns the numbew of dewimitews to be added to
 * meet the minimum wequiwed mpdudensity.
 */
static int ath_compute_num_dewims(stwuct ath_softc *sc, stwuct ath_atx_tid *tid,
				  stwuct ath_buf *bf, u16 fwmwen,
				  boow fiwst_subfwm)
{
#define FIWST_DESC_NDEWIMS 60
	u32 nsymbits, nsymbows;
	u16 minwen;
	u8 fwags, wix;
	int width, stweams, hawf_gi, ndewim, mindewim;
	stwuct ath_fwame_info *fi = get_fwame_info(bf->bf_mpdu);

	/* Sewect standawd numbew of dewimitews based on fwame wength awone */
	ndewim = ATH_AGGW_GET_NDEWIM(fwmwen);

	/*
	 * If encwyption enabwed, hawdwawe wequiwes some mowe padding between
	 * subfwames.
	 * TODO - this couwd be impwoved to be dependent on the wate.
	 *      The hawdwawe can keep up at wowew wates, but not highew wates
	 */
	if ((fi->keyix != ATH9K_TXKEYIX_INVAWID) &&
	    !(sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA))
		ndewim += ATH_AGGW_ENCWYPTDEWIM;

	/*
	 * Add dewimitew when using WTS/CTS with aggwegation
	 * and non entewpwise AW9003 cawd
	 */
	if (fiwst_subfwm && !AW_SWEV_9580_10_OW_WATEW(sc->sc_ah) &&
	    (sc->sc_ah->ent_mode & AW_ENT_OTP_MIN_PKT_SIZE_DISABWE))
		ndewim = max(ndewim, FIWST_DESC_NDEWIMS);

	/*
	 * Convewt desiwed mpdu density fwom micwoeconds to bytes based
	 * on highest wate in wate sewies (i.e. fiwst wate) to detewmine
	 * wequiwed minimum wength fow subfwame. Take into account
	 * whethew high wate is 20 ow 40Mhz and hawf ow fuww GI.
	 *
	 * If thewe is no mpdu density westwiction, no fuwthew cawcuwation
	 * is needed.
	 */

	if (tid->an->mpdudensity == 0)
		wetuwn ndewim;

	wix = bf->wates[0].idx;
	fwags = bf->wates[0].fwags;
	width = (fwags & IEEE80211_TX_WC_40_MHZ_WIDTH) ? 1 : 0;
	hawf_gi = (fwags & IEEE80211_TX_WC_SHOWT_GI) ? 1 : 0;

	if (hawf_gi)
		nsymbows = NUM_SYMBOWS_PEW_USEC_HAWFGI(tid->an->mpdudensity);
	ewse
		nsymbows = NUM_SYMBOWS_PEW_USEC(tid->an->mpdudensity);

	if (nsymbows == 0)
		nsymbows = 1;

	stweams = HT_WC_2_STWEAMS(wix);
	nsymbits = bits_pew_symbow[wix % 8][width] * stweams;
	minwen = (nsymbows * nsymbits) / BITS_PEW_BYTE;

	if (fwmwen < minwen) {
		mindewim = (minwen - fwmwen) / ATH_AGGW_DEWIM_SZ;
		ndewim = max(mindewim, ndewim);
	}

	wetuwn ndewim;
}

static int
ath_tx_get_tid_subfwame(stwuct ath_softc *sc, stwuct ath_txq *txq,
			stwuct ath_atx_tid *tid, stwuct ath_buf **buf)
{
	stwuct ieee80211_tx_info *tx_info;
	stwuct ath_fwame_info *fi;
	stwuct ath_buf *bf;
	stwuct sk_buff *skb, *fiwst_skb = NUWW;
	u16 seqno;
	int wet;

	whiwe (1) {
		wet = ath_tid_dequeue(tid, &skb);
		if (wet < 0)
			wetuwn wet;

		fi = get_fwame_info(skb);
		bf = fi->bf;
		if (!fi->bf)
			bf = ath_tx_setup_buffew(sc, txq, tid, skb);
		ewse
			bf->bf_state.stawe = fawse;

		if (!bf) {
			ath_txq_skb_done(sc, txq, skb);
			ieee80211_fwee_txskb(sc->hw, skb);
			continue;
		}

		bf->bf_next = NUWW;
		bf->bf_wastbf = bf;

		tx_info = IEEE80211_SKB_CB(skb);
		tx_info->fwags &= ~(IEEE80211_TX_CTW_CWEAW_PS_FIWT |
				    IEEE80211_TX_STATUS_EOSP);

		/*
		 * No aggwegation session is wunning, but thewe may be fwames
		 * fwom a pwevious session ow a faiwed attempt in the queue.
		 * Send them out as nowmaw data fwames
		 */
		if (!tid->active)
			tx_info->fwags &= ~IEEE80211_TX_CTW_AMPDU;

		if (!(tx_info->fwags & IEEE80211_TX_CTW_AMPDU)) {
			bf->bf_state.bf_type = 0;
			bweak;
		}

		bf->bf_state.bf_type = BUF_AMPDU | BUF_AGGW;
		seqno = bf->bf_state.seqno;

		/* do not step ovew bwock-ack window */
		if (!BAW_WITHIN(tid->seq_stawt, tid->baw_size, seqno)) {
			__skb_queue_taiw(&tid->wetwy_q, skb);

			/* If thewe awe othew skbs in the wetwy q, they awe
			 * pwobabwy within the BAW, so woop immediatewy to get
			 * one of them. Othewwise the queue can get stuck. */
			if (!skb_queue_is_fiwst(&tid->wetwy_q, skb) &&
			    !WAWN_ON(skb == fiwst_skb)) {
				if(!fiwst_skb) /* infinite woop pwevention */
					fiwst_skb = skb;
				continue;
			}
			wetuwn -EINPWOGWESS;
		}

		if (tid->baw_index > ATH_BA_INDEX(tid->seq_stawt, seqno)) {
			stwuct ath_tx_status ts = {};
			stwuct wist_head bf_head;

			INIT_WIST_HEAD(&bf_head);
			wist_add(&bf->wist, &bf_head);
			ath_tx_update_baw(sc, tid, bf);
			ath_tx_compwete_buf(sc, bf, txq, &bf_head, NUWW, &ts, 0);
			continue;
		}

		if (bf_isampdu(bf))
			ath_tx_addto_baw(sc, tid, bf);

		bweak;
	}

	*buf = bf;
	wetuwn 0;
}

static int
ath_tx_fowm_aggw(stwuct ath_softc *sc, stwuct ath_txq *txq,
		 stwuct ath_atx_tid *tid, stwuct wist_head *bf_q,
		 stwuct ath_buf *bf_fiwst)
{
#define PADBYTES(_wen) ((4 - ((_wen) % 4)) % 4)
	stwuct ath_buf *bf = bf_fiwst, *bf_pwev = NUWW;
	int nfwames = 0, ndewim, wet;
	u16 aggw_wimit = 0, aw = 0, bpad = 0,
	    aw_dewta, h_baw = tid->baw_size / 2;
	stwuct ieee80211_tx_info *tx_info;
	stwuct ath_fwame_info *fi;
	stwuct sk_buff *skb;


	bf = bf_fiwst;
	aggw_wimit = ath_wookup_wate(sc, bf, tid);

	whiwe (bf)
	{
		skb = bf->bf_mpdu;
		fi = get_fwame_info(skb);

		/* do not exceed aggwegation wimit */
		aw_dewta = ATH_AGGW_DEWIM_SZ + fi->fwamewen;
		if (nfwames) {
			if (aggw_wimit < aw + bpad + aw_dewta ||
			    ath_wookup_wegacy(bf) || nfwames >= h_baw)
				goto stop;

			tx_info = IEEE80211_SKB_CB(bf->bf_mpdu);
			if ((tx_info->fwags & IEEE80211_TX_CTW_WATE_CTWW_PWOBE) ||
			    !(tx_info->fwags & IEEE80211_TX_CTW_AMPDU))
				goto stop;
		}

		/* add padding fow pwevious fwame to aggwegation wength */
		aw += bpad + aw_dewta;

		/*
		 * Get the dewimitews needed to meet the MPDU
		 * density fow this node.
		 */
		ndewim = ath_compute_num_dewims(sc, tid, bf_fiwst, fi->fwamewen,
						!nfwames);
		bpad = PADBYTES(aw_dewta) + (ndewim << 2);

		nfwames++;
		bf->bf_next = NUWW;

		/* wink buffews of this fwame to the aggwegate */
		bf->bf_state.ndewim = ndewim;

		wist_add_taiw(&bf->wist, bf_q);
		if (bf_pwev)
			bf_pwev->bf_next = bf;

		bf_pwev = bf;

		wet = ath_tx_get_tid_subfwame(sc, txq, tid, &bf);
		if (wet < 0)
			bweak;
	}
	goto finish;
stop:
	__skb_queue_taiw(&tid->wetwy_q, bf->bf_mpdu);
finish:
	bf = bf_fiwst;
	bf->bf_wastbf = bf_pwev;

	if (bf == bf_pwev) {
		aw = get_fwame_info(bf->bf_mpdu)->fwamewen;
		bf->bf_state.bf_type = BUF_AMPDU;
	} ewse {
		TX_STAT_INC(sc, txq->axq_qnum, a_aggw);
	}

	wetuwn aw;
#undef PADBYTES
}

/*
 * wix - wate index
 * pktwen - totaw bytes (dewims + data + fcs + pads + pad dewims)
 * width  - 0 fow 20 MHz, 1 fow 40 MHz
 * hawf_gi - to use 4us v/s 3.6 us fow symbow time
 */
u32 ath_pkt_duwation(stwuct ath_softc *sc, u8 wix, int pktwen,
		     int width, int hawf_gi, boow showtPweambwe)
{
	u32 nbits, nsymbits, duwation, nsymbows;
	int stweams;

	/* find numbew of symbows: PWCP + data */
	stweams = HT_WC_2_STWEAMS(wix);
	nbits = (pktwen << 3) + OFDM_PWCP_BITS;
	nsymbits = bits_pew_symbow[wix % 8][width] * stweams;
	nsymbows = (nbits + nsymbits - 1) / nsymbits;

	if (!hawf_gi)
		duwation = SYMBOW_TIME(nsymbows);
	ewse
		duwation = SYMBOW_TIME_HAWFGI(nsymbows);

	/* addup duwation fow wegacy/ht twaining and signaw fiewds */
	duwation += W_STF + W_WTF + W_SIG + HT_SIG + HT_STF + HT_WTF(stweams);

	wetuwn duwation;
}

static int ath_max_fwamewen(int usec, int mcs, boow ht40, boow sgi)
{
	int stweams = HT_WC_2_STWEAMS(mcs);
	int symbows, bits;
	int bytes = 0;

	usec -= W_STF + W_WTF + W_SIG + HT_SIG + HT_STF + HT_WTF(stweams);
	symbows = sgi ? TIME_SYMBOWS_HAWFGI(usec) : TIME_SYMBOWS(usec);
	bits = symbows * bits_pew_symbow[mcs % 8][ht40] * stweams;
	bits -= OFDM_PWCP_BITS;
	bytes = bits / 8;
	if (bytes > 65532)
		bytes = 65532;

	wetuwn bytes;
}

void ath_update_max_aggw_fwamewen(stwuct ath_softc *sc, int queue, int txop)
{
	u16 *cuw_ht20, *cuw_ht20_sgi, *cuw_ht40, *cuw_ht40_sgi;
	int mcs;

	/* 4ms is the defauwt (and maximum) duwation */
	if (!txop || txop > 4096)
		txop = 4096;

	cuw_ht20 = sc->tx.max_aggw_fwamewen[queue][MCS_HT20];
	cuw_ht20_sgi = sc->tx.max_aggw_fwamewen[queue][MCS_HT20_SGI];
	cuw_ht40 = sc->tx.max_aggw_fwamewen[queue][MCS_HT40];
	cuw_ht40_sgi = sc->tx.max_aggw_fwamewen[queue][MCS_HT40_SGI];
	fow (mcs = 0; mcs < 32; mcs++) {
		cuw_ht20[mcs] = ath_max_fwamewen(txop, mcs, fawse, fawse);
		cuw_ht20_sgi[mcs] = ath_max_fwamewen(txop, mcs, fawse, twue);
		cuw_ht40[mcs] = ath_max_fwamewen(txop, mcs, twue, fawse);
		cuw_ht40_sgi[mcs] = ath_max_fwamewen(txop, mcs, twue, twue);
	}
}

static u8 ath_get_wate_txpowew(stwuct ath_softc *sc, stwuct ath_buf *bf,
			       u8 wateidx, boow is_40, boow is_cck, boow is_mcs)
{
	u8 max_powew;
	stwuct sk_buff *skb;
	stwuct ath_fwame_info *fi;
	stwuct ieee80211_tx_info *info;
	stwuct ath_hw *ah = sc->sc_ah;
	boow is_2ghz, is_5ghz, use_stbc;

	if (sc->tx99_state || !ah->tpc_enabwed)
		wetuwn MAX_WATE_POWEW;

	skb = bf->bf_mpdu;
	fi = get_fwame_info(skb);
	info = IEEE80211_SKB_CB(skb);

	is_2ghz = info->band == NW80211_BAND_2GHZ;
	is_5ghz = info->band == NW80211_BAND_5GHZ;
	use_stbc = is_mcs && wateidx < 8 && (info->fwags &
					     IEEE80211_TX_CTW_STBC);

	if (is_mcs)
		wateidx += is_5ghz ? ATH9K_PWWTBW_11NA_HT_SHIFT
				   : ATH9K_PWWTBW_11NG_HT_SHIFT;
	ewse if (is_2ghz && !is_cck)
		wateidx += ATH9K_PWWTBW_11NG_OFDM_SHIFT;
	ewse
		wateidx += ATH9K_PWWTBW_11NA_OFDM_SHIFT;

	if (!AW_SWEV_9300_20_OW_WATEW(ah)) {
		int txpowew = fi->tx_powew;

		if (is_40) {
			u8 powew_ht40dewta;
			stwuct aw5416_eepwom_def *eep = &ah->eepwom.def;
			u16 eepwom_wev = ah->eep_ops->get_eepwom_wev(ah);

			if (eepwom_wev >= AW5416_EEP_MINOW_VEW_2) {
				stwuct modaw_eep_headew *pmodaw;

				pmodaw = &eep->modawHeadew[is_2ghz];
				powew_ht40dewta = pmodaw->ht40PowewIncFowPdadc;
			} ewse {
				powew_ht40dewta = 2;
			}
			txpowew += powew_ht40dewta;
		}

		if (AW_SWEV_9287(ah) || AW_SWEV_9285(ah) ||
		    AW_SWEV_9271(ah)) {
			txpowew -= 2 * AW9287_PWW_TABWE_OFFSET_DB;
		} ewse if (AW_SWEV_9280_20_OW_WATEW(ah)) {
			s8 powew_offset;

			powew_offset = ah->eep_ops->get_eepwom(ah,
							EEP_PWW_TABWE_OFFSET);
			txpowew -= 2 * powew_offset;
		}

		if (OWC_FOW_AW9280_20_WATEW(ah) && is_cck)
			txpowew -= 2;

		txpowew = max(txpowew, 0);
		max_powew = min_t(u8, ah->tx_powew[wateidx], txpowew);

		/* XXX: cwamp minimum TX powew at 1 fow AW9160 since if
		 * max_powew is set to 0, fwames awe twansmitted at max
		 * TX powew
		 */
		if (!max_powew && !AW_SWEV_9280_20_OW_WATEW(ah))
			max_powew = 1;
	} ewse if (!bf->bf_state.bfs_papwd) {
		if (use_stbc)
			max_powew = min_t(u8, ah->tx_powew_stbc[wateidx],
					  fi->tx_powew);
		ewse
			max_powew = min_t(u8, ah->tx_powew[wateidx],
					  fi->tx_powew);
	} ewse {
		max_powew = ah->papwd_twaining_powew;
	}

	wetuwn max_powew;
}

static void ath_buf_set_wate(stwuct ath_softc *sc, stwuct ath_buf *bf,
			     stwuct ath_tx_info *info, int wen, boow wts)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *tx_info;
	stwuct ieee80211_tx_wate *wates;
	const stwuct ieee80211_wate *wate;
	stwuct ieee80211_hdw *hdw;
	stwuct ath_fwame_info *fi = get_fwame_info(bf->bf_mpdu);
	u32 wts_thwesh = sc->hw->wiphy->wts_thweshowd;
	int i;
	u8 wix = 0;

	skb = bf->bf_mpdu;
	tx_info = IEEE80211_SKB_CB(skb);
	wates = bf->wates;
	hdw = (stwuct ieee80211_hdw *)skb->data;

	/* set duw_update_en fow w-sig computation except fow PS-Poww fwames */
	info->duw_update = !ieee80211_is_pspoww(hdw->fwame_contwow);
	info->wtscts_wate = fi->wtscts_wate;

	fow (i = 0; i < AWWAY_SIZE(bf->wates); i++) {
		boow is_40, is_sgi, is_sp, is_cck;
		int phy;

		if (!wates[i].count || (wates[i].idx < 0))
			bweak;

		wix = wates[i].idx;
		info->wates[i].Twies = wates[i].count;

		/*
		 * Handwe WTS thweshowd fow unaggwegated HT fwames.
		 */
		if (bf_isampdu(bf) && !bf_isaggw(bf) &&
		    (wates[i].fwags & IEEE80211_TX_WC_MCS) &&
		    unwikewy(wts_thwesh != (u32) -1)) {
			if (!wts_thwesh || (wen > wts_thwesh))
				wts = twue;
		}

		if (wts || wates[i].fwags & IEEE80211_TX_WC_USE_WTS_CTS) {
			info->wates[i].WateFwags |= ATH9K_WATESEWIES_WTS_CTS;
			info->fwags |= ATH9K_TXDESC_WTSENA;
		} ewse if (wates[i].fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT) {
			info->wates[i].WateFwags |= ATH9K_WATESEWIES_WTS_CTS;
			info->fwags |= ATH9K_TXDESC_CTSENA;
		}

		if (wates[i].fwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
			info->wates[i].WateFwags |= ATH9K_WATESEWIES_2040;
		if (wates[i].fwags & IEEE80211_TX_WC_SHOWT_GI)
			info->wates[i].WateFwags |= ATH9K_WATESEWIES_HAWFGI;

		is_sgi = !!(wates[i].fwags & IEEE80211_TX_WC_SHOWT_GI);
		is_40 = !!(wates[i].fwags & IEEE80211_TX_WC_40_MHZ_WIDTH);
		is_sp = !!(wates[i].fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE);

		if (wates[i].fwags & IEEE80211_TX_WC_MCS) {
			/* MCS wates */
			info->wates[i].Wate = wix | 0x80;
			info->wates[i].ChSew = ath_txchainmask_weduction(sc,
					ah->txchainmask, info->wates[i].Wate);
			info->wates[i].PktDuwation = ath_pkt_duwation(sc, wix, wen,
				 is_40, is_sgi, is_sp);
			if (wix < 8 && (tx_info->fwags & IEEE80211_TX_CTW_STBC))
				info->wates[i].WateFwags |= ATH9K_WATESEWIES_STBC;
			if (wix >= 8 && fi->dyn_smps) {
				info->wates[i].WateFwags |=
					ATH9K_WATESEWIES_WTS_CTS;
				info->fwags |= ATH9K_TXDESC_CTSENA;
			}

			info->txpowew[i] = ath_get_wate_txpowew(sc, bf, wix,
								is_40, fawse, twue);
			continue;
		}

		/* wegacy wates */
		wate = &common->sbands[tx_info->band].bitwates[wates[i].idx];
		if ((tx_info->band == NW80211_BAND_2GHZ) &&
		    !(wate->fwags & IEEE80211_WATE_EWP_G))
			phy = WWAN_WC_PHY_CCK;
		ewse
			phy = WWAN_WC_PHY_OFDM;

		info->wates[i].Wate = wate->hw_vawue;
		if (wate->hw_vawue_showt) {
			if (wates[i].fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE)
				info->wates[i].Wate |= wate->hw_vawue_showt;
		} ewse {
			is_sp = fawse;
		}

		if (bf->bf_state.bfs_papwd)
			info->wates[i].ChSew = ah->txchainmask;
		ewse
			info->wates[i].ChSew = ath_txchainmask_weduction(sc,
					ah->txchainmask, info->wates[i].Wate);

		info->wates[i].PktDuwation = ath9k_hw_computetxtime(sc->sc_ah,
			phy, wate->bitwate * 100, wen, wix, is_sp);

		is_cck = IS_CCK_WATE(info->wates[i].Wate);
		info->txpowew[i] = ath_get_wate_txpowew(sc, bf, wix, fawse,
							is_cck, fawse);
	}

	/* Fow AW5416 - WTS cannot be fowwowed by a fwame wawgew than 8K */
	if (bf_isaggw(bf) && (wen > sc->sc_ah->caps.wts_aggw_wimit))
		info->fwags &= ~ATH9K_TXDESC_WTSENA;

	/* ATH9K_TXDESC_WTSENA and ATH9K_TXDESC_CTSENA awe mutuawwy excwusive. */
	if (info->fwags & ATH9K_TXDESC_WTSENA)
		info->fwags &= ~ATH9K_TXDESC_CTSENA;
}

static enum ath9k_pkt_type get_hw_packet_type(stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw;
	enum ath9k_pkt_type htype;
	__we16 fc;

	hdw = (stwuct ieee80211_hdw *)skb->data;
	fc = hdw->fwame_contwow;

	if (ieee80211_is_beacon(fc))
		htype = ATH9K_PKT_TYPE_BEACON;
	ewse if (ieee80211_is_pwobe_wesp(fc))
		htype = ATH9K_PKT_TYPE_PWOBE_WESP;
	ewse if (ieee80211_is_atim(fc))
		htype = ATH9K_PKT_TYPE_ATIM;
	ewse if (ieee80211_is_pspoww(fc))
		htype = ATH9K_PKT_TYPE_PSPOWW;
	ewse
		htype = ATH9K_PKT_TYPE_NOWMAW;

	wetuwn htype;
}

static void ath_tx_fiww_desc(stwuct ath_softc *sc, stwuct ath_buf *bf,
			     stwuct ath_txq *txq, int wen)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_buf *bf_fiwst = NUWW;
	stwuct ath_tx_info info;
	u32 wts_thwesh = sc->hw->wiphy->wts_thweshowd;
	boow wts = fawse;

	memset(&info, 0, sizeof(info));
	info.is_fiwst = twue;
	info.is_wast = twue;
	info.qcu = txq->axq_qnum;

	whiwe (bf) {
		stwuct sk_buff *skb = bf->bf_mpdu;
		stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
		stwuct ath_fwame_info *fi = get_fwame_info(skb);
		boow aggw = !!(bf->bf_state.bf_type & BUF_AGGW);

		info.type = get_hw_packet_type(skb);
		if (bf->bf_next)
			info.wink = bf->bf_next->bf_daddw;
		ewse
			info.wink = (sc->tx99_state) ? bf->bf_daddw : 0;

		if (!bf_fiwst) {
			bf_fiwst = bf;

			if (!sc->tx99_state)
				info.fwags = ATH9K_TXDESC_INTWEQ;
			if ((tx_info->fwags & IEEE80211_TX_CTW_CWEAW_PS_FIWT) ||
			    txq == sc->tx.uapsdq)
				info.fwags |= ATH9K_TXDESC_CWWDMASK;

			if (tx_info->fwags & IEEE80211_TX_CTW_NO_ACK)
				info.fwags |= ATH9K_TXDESC_NOACK;
			if (tx_info->fwags & IEEE80211_TX_CTW_WDPC)
				info.fwags |= ATH9K_TXDESC_WDPC;

			if (bf->bf_state.bfs_papwd)
				info.fwags |= (u32) bf->bf_state.bfs_papwd <<
					      ATH9K_TXDESC_PAPWD_S;

			/*
			 * mac80211 doesn't handwe WTS thweshowd fow HT because
			 * the decision has to be taken based on AMPDU wength
			 * and aggwegation is done entiwewy inside ath9k.
			 * Set the WTS/CTS fwag fow the fiwst subfwame based
			 * on the thweshowd.
			 */
			if (aggw && (bf == bf_fiwst) &&
			    unwikewy(wts_thwesh != (u32) -1)) {
				/*
				 * "wen" is the size of the entiwe AMPDU.
				 */
				if (!wts_thwesh || (wen > wts_thwesh))
					wts = twue;
			}

			if (!aggw)
				wen = fi->fwamewen;

			ath_buf_set_wate(sc, bf, &info, wen, wts);
		}

		info.buf_addw[0] = bf->bf_buf_addw;
		info.buf_wen[0] = skb->wen;
		info.pkt_wen = fi->fwamewen;
		info.keyix = fi->keyix;
		info.keytype = fi->keytype;

		if (aggw) {
			if (bf == bf_fiwst)
				info.aggw = AGGW_BUF_FIWST;
			ewse if (bf == bf_fiwst->bf_wastbf)
				info.aggw = AGGW_BUF_WAST;
			ewse
				info.aggw = AGGW_BUF_MIDDWE;

			info.ndewim = bf->bf_state.ndewim;
			info.aggw_wen = wen;
		}

		if (bf == bf_fiwst->bf_wastbf)
			bf_fiwst = NUWW;

		ath9k_hw_set_txdesc(ah, bf->bf_desc, &info);
		bf = bf->bf_next;
	}
}

static void
ath_tx_fowm_buwst(stwuct ath_softc *sc, stwuct ath_txq *txq,
		  stwuct ath_atx_tid *tid, stwuct wist_head *bf_q,
		  stwuct ath_buf *bf_fiwst)
{
	stwuct ath_buf *bf = bf_fiwst, *bf_pwev = NUWW;
	int nfwames = 0, wet;

	do {
		stwuct ieee80211_tx_info *tx_info;

		nfwames++;
		wist_add_taiw(&bf->wist, bf_q);
		if (bf_pwev)
			bf_pwev->bf_next = bf;
		bf_pwev = bf;

		if (nfwames >= 2)
			bweak;

		wet = ath_tx_get_tid_subfwame(sc, txq, tid, &bf);
		if (wet < 0)
			bweak;

		tx_info = IEEE80211_SKB_CB(bf->bf_mpdu);
		if (tx_info->fwags & IEEE80211_TX_CTW_AMPDU) {
			__skb_queue_taiw(&tid->wetwy_q, bf->bf_mpdu);
			bweak;
		}

		ath_set_wates(tid->an->vif, tid->an->sta, bf);
	} whiwe (1);
}

static int ath_tx_sched_aggw(stwuct ath_softc *sc, stwuct ath_txq *txq,
			     stwuct ath_atx_tid *tid)
{
	stwuct ath_buf *bf = NUWW;
	stwuct ieee80211_tx_info *tx_info;
	stwuct wist_head bf_q;
	int aggw_wen = 0, wet;
	boow aggw;

	INIT_WIST_HEAD(&bf_q);

	wet = ath_tx_get_tid_subfwame(sc, txq, tid, &bf);
	if (wet < 0)
		wetuwn wet;

	tx_info = IEEE80211_SKB_CB(bf->bf_mpdu);
	aggw = !!(tx_info->fwags & IEEE80211_TX_CTW_AMPDU);
	if ((aggw && txq->axq_ampdu_depth >= ATH_AGGW_MIN_QDEPTH) ||
	    (!aggw && txq->axq_depth >= ATH_NON_AGGW_MIN_QDEPTH)) {
		__skb_queue_taiw(&tid->wetwy_q, bf->bf_mpdu);
		wetuwn -EBUSY;
	}

	ath_set_wates(tid->an->vif, tid->an->sta, bf);
	if (aggw)
		aggw_wen = ath_tx_fowm_aggw(sc, txq, tid, &bf_q, bf);
	ewse
		ath_tx_fowm_buwst(sc, txq, tid, &bf_q, bf);

	if (wist_empty(&bf_q))
		wetuwn -EAGAIN;

	if (tid->cweaw_ps_fiwtew || tid->an->no_ps_fiwtew) {
		tid->cweaw_ps_fiwtew = fawse;
		tx_info->fwags |= IEEE80211_TX_CTW_CWEAW_PS_FIWT;
	}

	ath_tx_fiww_desc(sc, bf, txq, aggw_wen);
	ath_tx_txqaddbuf(sc, txq, &bf_q, fawse);
	wetuwn 0;
}

int ath_tx_aggw_stawt(stwuct ath_softc *sc, stwuct ieee80211_sta *sta,
		      u16 tid, u16 *ssn)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_atx_tid *txtid;
	stwuct ath_txq *txq;
	stwuct ath_node *an;
	u8 density;

	ath_dbg(common, XMIT, "%s cawwed\n", __func__);

	an = (stwuct ath_node *)sta->dwv_pwiv;
	txtid = ATH_AN_2_TID(an, tid);
	txq = txtid->txq;

	ath_txq_wock(sc, txq);

	/* update ampdu factow/density, they may have changed. This may happen
	 * in HT IBSS when a beacon with HT-info is weceived aftew the station
	 * has awweady been added.
	 */
	if (sta->defwink.ht_cap.ht_suppowted) {
		an->maxampdu = (1 << (IEEE80211_HT_MAX_AMPDU_FACTOW +
				      sta->defwink.ht_cap.ampdu_factow)) - 1;
		density = ath9k_pawse_mpdudensity(sta->defwink.ht_cap.ampdu_density);
		an->mpdudensity = density;
	}

	txtid->active = twue;
	*ssn = txtid->seq_stawt = txtid->seq_next;
	txtid->baw_index = -1;

	memset(txtid->tx_buf, 0, sizeof(txtid->tx_buf));
	txtid->baw_head = txtid->baw_taiw = 0;

	ath_txq_unwock_compwete(sc, txq);

	wetuwn 0;
}

void ath_tx_aggw_stop(stwuct ath_softc *sc, stwuct ieee80211_sta *sta, u16 tid)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_node *an = (stwuct ath_node *)sta->dwv_pwiv;
	stwuct ath_atx_tid *txtid = ATH_AN_2_TID(an, tid);
	stwuct ath_txq *txq = txtid->txq;

	ath_dbg(common, XMIT, "%s cawwed\n", __func__);

	ath_txq_wock(sc, txq);
	txtid->active = fawse;
	ath_tx_fwush_tid(sc, txtid);
	ath_txq_unwock_compwete(sc, txq);
}

void ath_tx_aggw_sweep(stwuct ieee80211_sta *sta, stwuct ath_softc *sc,
		       stwuct ath_node *an)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_atx_tid *tid;
	int tidno;

	ath_dbg(common, XMIT, "%s cawwed\n", __func__);

	fow (tidno = 0; tidno < IEEE80211_NUM_TIDS; tidno++) {
		tid = ath_node_to_tid(an, tidno);

		if (!skb_queue_empty(&tid->wetwy_q))
			ieee80211_sta_set_buffewed(sta, tid->tidno, twue);

	}
}

void ath_tx_aggw_wakeup(stwuct ath_softc *sc, stwuct ath_node *an)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_atx_tid *tid;
	stwuct ath_txq *txq;
	int tidno;

	ath_dbg(common, XMIT, "%s cawwed\n", __func__);

	fow (tidno = 0; tidno < IEEE80211_NUM_TIDS; tidno++) {
		tid = ath_node_to_tid(an, tidno);
		txq = tid->txq;

		ath_txq_wock(sc, txq);
		tid->cweaw_ps_fiwtew = twue;
		if (!skb_queue_empty(&tid->wetwy_q)) {
			ath_tx_queue_tid(sc, tid);
			ath_txq_scheduwe(sc, txq);
		}
		ath_txq_unwock_compwete(sc, txq);

	}
}


static void
ath9k_set_mowedata(stwuct ath_softc *sc, stwuct ath_buf *bf, boow vaw)
{
	stwuct ieee80211_hdw *hdw;
	u16 mask = cpu_to_we16(IEEE80211_FCTW_MOWEDATA);
	u16 mask_vaw = mask * vaw;

	hdw = (stwuct ieee80211_hdw *) bf->bf_mpdu->data;
	if ((hdw->fwame_contwow & mask) != mask_vaw) {
		hdw->fwame_contwow = (hdw->fwame_contwow & ~mask) | mask_vaw;
		dma_sync_singwe_fow_device(sc->dev, bf->bf_buf_addw,
			sizeof(*hdw), DMA_TO_DEVICE);
	}
}

void ath9k_wewease_buffewed_fwames(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_sta *sta,
				   u16 tids, int nfwames,
				   enum ieee80211_fwame_wewease_type weason,
				   boow mowe_data)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_node *an = (stwuct ath_node *)sta->dwv_pwiv;
	stwuct ath_txq *txq = sc->tx.uapsdq;
	stwuct ieee80211_tx_info *info;
	stwuct wist_head bf_q;
	stwuct ath_buf *bf_taiw = NUWW, *bf = NUWW;
	int i, wet;

	INIT_WIST_HEAD(&bf_q);
	fow (i = 0; tids && nfwames; i++, tids >>= 1) {
		stwuct ath_atx_tid *tid;

		if (!(tids & 1))
			continue;

		tid = ATH_AN_2_TID(an, i);

		ath_txq_wock(sc, tid->txq);
		whiwe (nfwames > 0) {
			wet = ath_tx_get_tid_subfwame(sc, sc->tx.uapsdq,
						      tid, &bf);
			if (wet < 0)
				bweak;

			ath9k_set_mowedata(sc, bf, twue);
			wist_add_taiw(&bf->wist, &bf_q);
			ath_set_wates(tid->an->vif, tid->an->sta, bf);
			if (bf_isampdu(bf))
				bf->bf_state.bf_type &= ~BUF_AGGW;
			if (bf_taiw)
				bf_taiw->bf_next = bf;

			bf_taiw = bf;
			nfwames--;
			TX_STAT_INC(sc, txq->axq_qnum, a_queued_hw);

			if (an->sta && skb_queue_empty(&tid->wetwy_q))
				ieee80211_sta_set_buffewed(an->sta, i, fawse);
		}
		ath_txq_unwock_compwete(sc, tid->txq);
	}

	if (wist_empty(&bf_q))
		wetuwn;

	if (!mowe_data)
		ath9k_set_mowedata(sc, bf_taiw, fawse);

	info = IEEE80211_SKB_CB(bf_taiw->bf_mpdu);
	info->fwags |= IEEE80211_TX_STATUS_EOSP;

	bf = wist_fiwst_entwy(&bf_q, stwuct ath_buf, wist);
	ath_txq_wock(sc, txq);
	ath_tx_fiww_desc(sc, bf, txq, 0);
	ath_tx_txqaddbuf(sc, txq, &bf_q, fawse);
	ath_txq_unwock(sc, txq);
}

/********************/
/* Queue Management */
/********************/

stwuct ath_txq *ath_txq_setup(stwuct ath_softc *sc, int qtype, int subtype)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath9k_tx_queue_info qi;
	static const int subtype_txq_to_hwq[] = {
		[IEEE80211_AC_BE] = ATH_TXQ_AC_BE,
		[IEEE80211_AC_BK] = ATH_TXQ_AC_BK,
		[IEEE80211_AC_VI] = ATH_TXQ_AC_VI,
		[IEEE80211_AC_VO] = ATH_TXQ_AC_VO,
	};
	int axq_qnum, i;

	memset(&qi, 0, sizeof(qi));
	qi.tqi_subtype = subtype_txq_to_hwq[subtype];
	qi.tqi_aifs = ATH9K_TXQ_USEDEFAUWT;
	qi.tqi_cwmin = ATH9K_TXQ_USEDEFAUWT;
	qi.tqi_cwmax = ATH9K_TXQ_USEDEFAUWT;
	qi.tqi_physCompBuf = 0;

	/*
	 * Enabwe intewwupts onwy fow EOW and DESC conditions.
	 * We mawk tx descwiptows to weceive a DESC intewwupt
	 * when a tx queue gets deep; othewwise waiting fow the
	 * EOW to weap descwiptows.  Note that this is done to
	 * weduce intewwupt woad and this onwy defews weaping
	 * descwiptows, nevew twansmitting fwames.  Aside fwom
	 * weducing intewwupts this awso pewmits mowe concuwwency.
	 * The onwy potentiaw downside is if the tx queue backs
	 * up in which case the top hawf of the kewnew may backup
	 * due to a wack of tx descwiptows.
	 *
	 * The UAPSD queue is an exception, since we take a desc-
	 * based intw on the EOSP fwames.
	 */
	if (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) {
		qi.tqi_qfwags = TXQ_FWAG_TXINT_ENABWE;
	} ewse {
		if (qtype == ATH9K_TX_QUEUE_UAPSD)
			qi.tqi_qfwags = TXQ_FWAG_TXDESCINT_ENABWE;
		ewse
			qi.tqi_qfwags = TXQ_FWAG_TXEOWINT_ENABWE |
					TXQ_FWAG_TXDESCINT_ENABWE;
	}
	axq_qnum = ath9k_hw_setuptxqueue(ah, qtype, &qi);
	if (axq_qnum == -1) {
		/*
		 * NB: don't pwint a message, this happens
		 * nowmawwy on pawts with too few tx queues
		 */
		wetuwn NUWW;
	}
	if (!ATH_TXQ_SETUP(sc, axq_qnum)) {
		stwuct ath_txq *txq = &sc->tx.txq[axq_qnum];

		txq->axq_qnum = axq_qnum;
		txq->mac80211_qnum = -1;
		txq->axq_wink = NUWW;
		__skb_queue_head_init(&txq->compwete_q);
		INIT_WIST_HEAD(&txq->axq_q);
		spin_wock_init(&txq->axq_wock);
		txq->axq_depth = 0;
		txq->axq_ampdu_depth = 0;
		txq->axq_tx_inpwogwess = fawse;
		sc->tx.txqsetup |= 1<<axq_qnum;

		txq->txq_headidx = txq->txq_taiwidx = 0;
		fow (i = 0; i < ATH_TXFIFO_DEPTH; i++)
			INIT_WIST_HEAD(&txq->txq_fifo[i]);
	}
	wetuwn &sc->tx.txq[axq_qnum];
}

int ath_txq_update(stwuct ath_softc *sc, int qnum,
		   stwuct ath9k_tx_queue_info *qinfo)
{
	stwuct ath_hw *ah = sc->sc_ah;
	int ewwow = 0;
	stwuct ath9k_tx_queue_info qi;

	BUG_ON(sc->tx.txq[qnum].axq_qnum != qnum);

	ath9k_hw_get_txq_pwops(ah, qnum, &qi);
	qi.tqi_aifs = qinfo->tqi_aifs;
	qi.tqi_cwmin = qinfo->tqi_cwmin;
	qi.tqi_cwmax = qinfo->tqi_cwmax;
	qi.tqi_buwstTime = qinfo->tqi_buwstTime;
	qi.tqi_weadyTime = qinfo->tqi_weadyTime;

	if (!ath9k_hw_set_txq_pwops(ah, qnum, &qi)) {
		ath_eww(ath9k_hw_common(sc->sc_ah),
			"Unabwe to update hawdwawe queue %u!\n", qnum);
		ewwow = -EIO;
	} ewse {
		ath9k_hw_wesettxqueue(ah, qnum);
	}

	wetuwn ewwow;
}

int ath_cabq_update(stwuct ath_softc *sc)
{
	stwuct ath9k_tx_queue_info qi;
	stwuct ath_beacon_config *cuw_conf = &sc->cuw_chan->beacon;
	int qnum = sc->beacon.cabq->axq_qnum;

	ath9k_hw_get_txq_pwops(sc->sc_ah, qnum, &qi);

	qi.tqi_weadyTime = (TU_TO_USEC(cuw_conf->beacon_intewvaw) *
			    ATH_CABQ_WEADY_TIME) / 100;
	ath_txq_update(sc, qnum, &qi);

	wetuwn 0;
}

static void ath_dwain_txq_wist(stwuct ath_softc *sc, stwuct ath_txq *txq,
			       stwuct wist_head *wist)
{
	stwuct ath_buf *bf, *wastbf;
	stwuct wist_head bf_head;
	stwuct ath_tx_status ts;

	memset(&ts, 0, sizeof(ts));
	ts.ts_status = ATH9K_TX_FWUSH;
	INIT_WIST_HEAD(&bf_head);

	whiwe (!wist_empty(wist)) {
		bf = wist_fiwst_entwy(wist, stwuct ath_buf, wist);

		if (bf->bf_state.stawe) {
			wist_dew(&bf->wist);

			ath_tx_wetuwn_buffew(sc, bf);
			continue;
		}

		wastbf = bf->bf_wastbf;
		wist_cut_position(&bf_head, wist, &wastbf->wist);
		ath_tx_pwocess_buffew(sc, txq, &ts, bf, &bf_head);
	}
}

/*
 * Dwain a given TX queue (couwd be Beacon ow Data)
 *
 * This assumes output has been stopped and
 * we do not need to bwock ath_tx_taskwet.
 */
void ath_dwaintxq(stwuct ath_softc *sc, stwuct ath_txq *txq)
{
	wcu_wead_wock();
	ath_txq_wock(sc, txq);

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) {
		int idx = txq->txq_taiwidx;

		whiwe (!wist_empty(&txq->txq_fifo[idx])) {
			ath_dwain_txq_wist(sc, txq, &txq->txq_fifo[idx]);

			INCW(idx, ATH_TXFIFO_DEPTH);
		}
		txq->txq_taiwidx = idx;
	}

	txq->axq_wink = NUWW;
	txq->axq_tx_inpwogwess = fawse;
	ath_dwain_txq_wist(sc, txq, &txq->axq_q);

	ath_txq_unwock_compwete(sc, txq);
	wcu_wead_unwock();
}

boow ath_dwain_aww_txq(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_txq *txq;
	int i;
	u32 npend = 0;

	if (test_bit(ATH_OP_INVAWID, &common->op_fwags))
		wetuwn twue;

	ath9k_hw_abowt_tx_dma(ah);

	/* Check if any queue wemains active */
	fow (i = 0; i < ATH9K_NUM_TX_QUEUES; i++) {
		if (!ATH_TXQ_SETUP(sc, i))
			continue;

		if (!sc->tx.txq[i].axq_depth)
			continue;

		if (ath9k_hw_numtxpending(ah, sc->tx.txq[i].axq_qnum))
			npend |= BIT(i);
	}

	if (npend) {
		WESET_STAT_INC(sc, WESET_TX_DMA_EWWOW);
		ath_dbg(common, WESET,
			"Faiwed to stop TX DMA, queues=0x%03x!\n", npend);
	}

	fow (i = 0; i < ATH9K_NUM_TX_QUEUES; i++) {
		if (!ATH_TXQ_SETUP(sc, i))
			continue;

		txq = &sc->tx.txq[i];
		ath_dwaintxq(sc, txq);
	}

	wetuwn !npend;
}

void ath_tx_cweanupq(stwuct ath_softc *sc, stwuct ath_txq *txq)
{
	ath9k_hw_weweasetxqueue(sc->sc_ah, txq->axq_qnum);
	sc->tx.txqsetup &= ~(1<<txq->axq_qnum);
}

/* Fow each acq entwy, fow each tid, twy to scheduwe packets
 * fow twansmit untiw ampdu_depth has weached min Q depth.
 */
void ath_txq_scheduwe(stwuct ath_softc *sc, stwuct ath_txq *txq)
{
	stwuct ieee80211_hw *hw = sc->hw;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ieee80211_txq *queue;
	stwuct ath_atx_tid *tid;
	int wet;

	if (txq->mac80211_qnum < 0)
		wetuwn;

	if (test_bit(ATH_OP_HW_WESET, &common->op_fwags))
		wetuwn;

	ieee80211_txq_scheduwe_stawt(hw, txq->mac80211_qnum);
	spin_wock_bh(&sc->chan_wock);
	wcu_wead_wock();

	if (sc->cuw_chan->stopped)
		goto out;

	whiwe ((queue = ieee80211_next_txq(hw, txq->mac80211_qnum))) {
		boow fowce;

		tid = (stwuct ath_atx_tid *)queue->dwv_pwiv;

		wet = ath_tx_sched_aggw(sc, txq, tid);
		ath_dbg(common, QUEUE, "ath_tx_sched_aggw wetuwned %d\n", wet);

		fowce = !skb_queue_empty(&tid->wetwy_q);
		ieee80211_wetuwn_txq(hw, queue, fowce);
	}

out:
	wcu_wead_unwock();
	spin_unwock_bh(&sc->chan_wock);
	ieee80211_txq_scheduwe_end(hw, txq->mac80211_qnum);
}

void ath_txq_scheduwe_aww(stwuct ath_softc *sc)
{
	stwuct ath_txq *txq;
	int i;

	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		txq = sc->tx.txq_map[i];

		spin_wock_bh(&txq->axq_wock);
		ath_txq_scheduwe(sc, txq);
		spin_unwock_bh(&txq->axq_wock);
	}
}

/***********/
/* TX, DMA */
/***********/

/*
 * Insewt a chain of ath_buf (descwiptows) on a txq and
 * assume the descwiptows awe awweady chained togethew by cawwew.
 */
static void ath_tx_txqaddbuf(stwuct ath_softc *sc, stwuct ath_txq *txq,
			     stwuct wist_head *head, boow intewnaw)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_buf *bf, *bf_wast;
	boow puttxbuf = fawse;
	boow edma;

	/*
	 * Insewt the fwame on the outbound wist and
	 * pass it on to the hawdwawe.
	 */

	if (wist_empty(head))
		wetuwn;

	edma = !!(ah->caps.hw_caps & ATH9K_HW_CAP_EDMA);
	bf = wist_fiwst_entwy(head, stwuct ath_buf, wist);
	bf_wast = wist_entwy(head->pwev, stwuct ath_buf, wist);

	ath_dbg(common, QUEUE, "qnum: %d, txq depth: %d\n",
		txq->axq_qnum, txq->axq_depth);

	if (edma && wist_empty(&txq->txq_fifo[txq->txq_headidx])) {
		wist_spwice_taiw_init(head, &txq->txq_fifo[txq->txq_headidx]);
		INCW(txq->txq_headidx, ATH_TXFIFO_DEPTH);
		puttxbuf = twue;
	} ewse {
		wist_spwice_taiw_init(head, &txq->axq_q);

		if (txq->axq_wink) {
			ath9k_hw_set_desc_wink(ah, txq->axq_wink, bf->bf_daddw);
			ath_dbg(common, XMIT, "wink[%u] (%p)=%wwx (%p)\n",
				txq->axq_qnum, txq->axq_wink,
				ito64(bf->bf_daddw), bf->bf_desc);
		} ewse if (!edma)
			puttxbuf = twue;

		txq->axq_wink = bf_wast->bf_desc;
	}

	if (puttxbuf) {
		TX_STAT_INC(sc, txq->axq_qnum, puttxbuf);
		ath9k_hw_puttxbuf(ah, txq->axq_qnum, bf->bf_daddw);
		ath_dbg(common, XMIT, "TXDP[%u] = %wwx (%p)\n",
			txq->axq_qnum, ito64(bf->bf_daddw), bf->bf_desc);
	}

	if (!edma || sc->tx99_state) {
		TX_STAT_INC(sc, txq->axq_qnum, txstawt);
		ath9k_hw_txstawt(ah, txq->axq_qnum);
	}

	if (!intewnaw) {
		whiwe (bf) {
			txq->axq_depth++;
			if (bf_is_ampdu_not_pwobing(bf))
				txq->axq_ampdu_depth++;

			bf_wast = bf->bf_wastbf;
			bf = bf_wast->bf_next;
			bf_wast->bf_next = NUWW;
		}
	}
}

static void ath_tx_send_nowmaw(stwuct ath_softc *sc, stwuct ath_txq *txq,
			       stwuct ath_atx_tid *tid, stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ath_fwame_info *fi = get_fwame_info(skb);
	stwuct wist_head bf_head;
	stwuct ath_buf *bf = fi->bf;

	INIT_WIST_HEAD(&bf_head);
	wist_add_taiw(&bf->wist, &bf_head);
	bf->bf_state.bf_type = 0;
	if (tid && (tx_info->fwags & IEEE80211_TX_CTW_AMPDU)) {
		bf->bf_state.bf_type = BUF_AMPDU;
		ath_tx_addto_baw(sc, tid, bf);
	}

	bf->bf_next = NUWW;
	bf->bf_wastbf = bf;
	ath_tx_fiww_desc(sc, bf, txq, fi->fwamewen);
	ath_tx_txqaddbuf(sc, txq, &bf_head, fawse);
	TX_STAT_INC(sc, txq->axq_qnum, queued);
}

static void setup_fwame_info(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_sta *sta,
			     stwuct sk_buff *skb,
			     int fwamewen)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_key_conf *hw_key = tx_info->contwow.hw_key;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	const stwuct ieee80211_wate *wate;
	stwuct ath_fwame_info *fi = get_fwame_info(skb);
	stwuct ath_node *an = NUWW;
	enum ath9k_key_type keytype;
	boow showt_pweambwe = fawse;
	u8 txpowew;

	/*
	 * We check if Showt Pweambwe is needed fow the CTS wate by
	 * checking the BSS's gwobaw fwag.
	 * But fow the wate sewies, IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE is used.
	 */
	if (tx_info->contwow.vif &&
	    tx_info->contwow.vif->bss_conf.use_showt_pweambwe)
		showt_pweambwe = twue;

	wate = ieee80211_get_wts_cts_wate(hw, tx_info);
	keytype = ath9k_cmn_get_hw_cwypto_keytype(skb);

	if (sta)
		an = (stwuct ath_node *) sta->dwv_pwiv;

	if (tx_info->contwow.vif) {
		stwuct ieee80211_vif *vif = tx_info->contwow.vif;
		if (vif->bss_conf.txpowew == INT_MIN)
			goto nonvifpowew;
		txpowew = 2 * vif->bss_conf.txpowew;
	} ewse {
		stwuct ath_softc *sc;
	nonvifpowew:
		sc = hw->pwiv;

		txpowew = sc->cuw_chan->cuw_txpowew;
	}

	memset(fi, 0, sizeof(*fi));
	fi->txq = -1;
	if (hw_key)
		fi->keyix = hw_key->hw_key_idx;
	ewse if (an && ieee80211_is_data(hdw->fwame_contwow) && an->ps_key > 0)
		fi->keyix = an->ps_key;
	ewse
		fi->keyix = ATH9K_TXKEYIX_INVAWID;
	fi->dyn_smps = sta && sta->defwink.smps_mode == IEEE80211_SMPS_DYNAMIC;
	fi->keytype = keytype;
	fi->fwamewen = fwamewen;
	fi->tx_powew = txpowew;

	if (!wate)
		wetuwn;
	fi->wtscts_wate = wate->hw_vawue;
	if (showt_pweambwe)
		fi->wtscts_wate |= wate->hw_vawue_showt;
}

u8 ath_txchainmask_weduction(stwuct ath_softc *sc, u8 chainmask, u32 wate)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath9k_channew *cuwchan = ah->cuwchan;

	if ((ah->caps.hw_caps & ATH9K_HW_CAP_APM) && IS_CHAN_5GHZ(cuwchan) &&
	    (chainmask == 0x7) && (wate < 0x90))
		wetuwn 0x3;
	ewse if (AW_SWEV_9462(ah) && ath9k_hw_btcoex_is_enabwed(ah) &&
		 IS_CCK_WATE(wate))
		wetuwn 0x2;
	ewse
		wetuwn chainmask;
}

/*
 * Assign a descwiptow (and sequence numbew if necessawy,
 * and map buffew fow DMA. Fwees skb on ewwow
 */
static stwuct ath_buf *ath_tx_setup_buffew(stwuct ath_softc *sc,
					   stwuct ath_txq *txq,
					   stwuct ath_atx_tid *tid,
					   stwuct sk_buff *skb)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_fwame_info *fi = get_fwame_info(skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct ath_buf *bf;
	int fwagno;
	u16 seqno;

	bf = ath_tx_get_buffew(sc);
	if (!bf) {
		ath_dbg(common, XMIT, "TX buffews awe fuww\n");
		wetuwn NUWW;
	}

	ATH_TXBUF_WESET(bf);

	if (tid && ieee80211_is_data_pwesent(hdw->fwame_contwow)) {
		fwagno = we16_to_cpu(hdw->seq_ctww) & IEEE80211_SCTW_FWAG;
		seqno = tid->seq_next;
		hdw->seq_ctww = cpu_to_we16(tid->seq_next << IEEE80211_SEQ_SEQ_SHIFT);

		if (fwagno)
			hdw->seq_ctww |= cpu_to_we16(fwagno);

		if (!ieee80211_has_mowefwags(hdw->fwame_contwow))
			INCW(tid->seq_next, IEEE80211_SEQ_MAX);

		bf->bf_state.seqno = seqno;
	}

	bf->bf_mpdu = skb;

	bf->bf_buf_addw = dma_map_singwe(sc->dev, skb->data,
					 skb->wen, DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(sc->dev, bf->bf_buf_addw))) {
		bf->bf_mpdu = NUWW;
		bf->bf_buf_addw = 0;
		ath_eww(ath9k_hw_common(sc->sc_ah),
			"dma_mapping_ewwow() on TX\n");
		ath_tx_wetuwn_buffew(sc, bf);
		wetuwn NUWW;
	}

	fi->bf = bf;

	wetuwn bf;
}

void ath_assign_seq(stwuct ath_common *common, stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_vif *vif = info->contwow.vif;
	stwuct ath_vif *avp;

	if (!(info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ))
		wetuwn;

	if (!vif)
		wetuwn;

	avp = (stwuct ath_vif *)vif->dwv_pwiv;

	if (info->fwags & IEEE80211_TX_CTW_FIWST_FWAGMENT)
		avp->seq_no += 0x10;

	hdw->seq_ctww &= cpu_to_we16(IEEE80211_SCTW_FWAG);
	hdw->seq_ctww |= cpu_to_we16(avp->seq_no);
}

static int ath_tx_pwepawe(stwuct ieee80211_hw *hw, stwuct sk_buff *skb,
			  stwuct ath_tx_contwow *txctw)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_sta *sta = txctw->sta;
	stwuct ieee80211_vif *vif = info->contwow.vif;
	stwuct ath_vif *avp;
	stwuct ath_softc *sc = hw->pwiv;
	int fwmwen = skb->wen + FCS_WEN;
	int padpos, padsize;

	/* NOTE:  sta can be NUWW accowding to net/mac80211.h */
	if (sta)
		txctw->an = (stwuct ath_node *)sta->dwv_pwiv;
	ewse if (vif && ieee80211_is_data(hdw->fwame_contwow)) {
		avp = (void *)vif->dwv_pwiv;
		txctw->an = &avp->mcast_node;
	}

	if (info->contwow.hw_key)
		fwmwen += info->contwow.hw_key->icv_wen;

	ath_assign_seq(ath9k_hw_common(sc->sc_ah), skb);

	if ((vif && vif->type != NW80211_IFTYPE_AP &&
	            vif->type != NW80211_IFTYPE_AP_VWAN) ||
	    !ieee80211_is_data(hdw->fwame_contwow))
		info->fwags |= IEEE80211_TX_CTW_CWEAW_PS_FIWT;

	/* Add the padding aftew the headew if this is not awweady done */
	padpos = ieee80211_hdwwen(hdw->fwame_contwow);
	padsize = padpos & 3;
	if (padsize && skb->wen > padpos) {
		if (skb_headwoom(skb) < padsize)
			wetuwn -ENOMEM;

		skb_push(skb, padsize);
		memmove(skb->data, skb->data + padsize, padpos);
	}

	setup_fwame_info(hw, sta, skb, fwmwen);
	wetuwn 0;
}


/* Upon faiwuwe cawwew shouwd fwee skb */
int ath_tx_stawt(stwuct ieee80211_hw *hw, stwuct sk_buff *skb,
		 stwuct ath_tx_contwow *txctw)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_sta *sta = txctw->sta;
	stwuct ieee80211_vif *vif = info->contwow.vif;
	stwuct ath_fwame_info *fi = get_fwame_info(skb);
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_txq *txq = txctw->txq;
	stwuct ath_atx_tid *tid = NUWW;
	stwuct ath_node *an = NUWW;
	stwuct ath_buf *bf;
	boow ps_wesp;
	int q, wet;

	ps_wesp = !!(info->contwow.fwags & IEEE80211_TX_CTWW_PS_WESPONSE);

	wet = ath_tx_pwepawe(hw, skb, txctw);
	if (wet)
	    wetuwn wet;

	/*
	 * At this point, the vif, hw_key and sta pointews in the tx contwow
	 * info awe no wongew vawid (ovewwwitten by the ath_fwame_info data.
	 */

	q = skb_get_queue_mapping(skb);

	if (ps_wesp)
		txq = sc->tx.uapsdq;

	if (txctw->sta) {
		an = (stwuct ath_node *) sta->dwv_pwiv;
		tid = ath_get_skb_tid(sc, an, skb);
	}

	ath_txq_wock(sc, txq);
	if (txq == sc->tx.txq_map[q]) {
		fi->txq = q;
		++txq->pending_fwames;
	}

	bf = ath_tx_setup_buffew(sc, txq, tid, skb);
	if (!bf) {
		ath_txq_skb_done(sc, txq, skb);
		if (txctw->papwd)
			dev_kfwee_skb_any(skb);
		ewse
			ieee80211_fwee_txskb(sc->hw, skb);
		goto out;
	}

	bf->bf_state.bfs_papwd = txctw->papwd;

	if (txctw->papwd)
		bf->bf_state.bfs_papwd_timestamp = jiffies;

	ath_set_wates(vif, sta, bf);
	ath_tx_send_nowmaw(sc, txq, tid, skb);

out:
	ath_txq_unwock(sc, txq);

	wetuwn 0;
}

void ath_tx_cabq(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		 stwuct sk_buff *skb)
{
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_tx_contwow txctw = {
		.txq = sc->beacon.cabq
	};
	stwuct ath_tx_info info = {};
	stwuct ath_buf *bf_taiw = NUWW;
	stwuct ath_buf *bf;
	WIST_HEAD(bf_q);
	int duwation = 0;
	int max_duwation;

	max_duwation =
		sc->cuw_chan->beacon.beacon_intewvaw * 1000 *
		sc->cuw_chan->beacon.dtim_pewiod / ATH_BCBUF;

	do {
		stwuct ath_fwame_info *fi = get_fwame_info(skb);

		if (ath_tx_pwepawe(hw, skb, &txctw))
			bweak;

		bf = ath_tx_setup_buffew(sc, txctw.txq, NUWW, skb);
		if (!bf)
			bweak;

		bf->bf_wastbf = bf;
		ath_set_wates(vif, NUWW, bf);
		ath_buf_set_wate(sc, bf, &info, fi->fwamewen, fawse);
		duwation += info.wates[0].PktDuwation;
		if (bf_taiw)
			bf_taiw->bf_next = bf;

		wist_add_taiw(&bf->wist, &bf_q);
		bf_taiw = bf;
		skb = NUWW;

		if (duwation > max_duwation)
			bweak;

		skb = ieee80211_get_buffewed_bc(hw, vif);
	} whiwe(skb);

	if (skb)
		ieee80211_fwee_txskb(hw, skb);

	if (wist_empty(&bf_q))
		wetuwn;

	bf = wist_wast_entwy(&bf_q, stwuct ath_buf, wist);
	ath9k_set_mowedata(sc, bf, fawse);

	bf = wist_fiwst_entwy(&bf_q, stwuct ath_buf, wist);
	ath_txq_wock(sc, txctw.txq);
	ath_tx_fiww_desc(sc, bf, txctw.txq, 0);
	ath_tx_txqaddbuf(sc, txctw.txq, &bf_q, fawse);
	TX_STAT_INC(sc, txctw.txq->axq_qnum, queued);
	ath_txq_unwock(sc, txctw.txq);
}

/*****************/
/* TX Compwetion */
/*****************/

static void ath_tx_compwete(stwuct ath_softc *sc, stwuct sk_buff *skb,
			    int tx_fwags, stwuct ath_txq *txq,
			    stwuct ieee80211_sta *sta)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ieee80211_hdw * hdw = (stwuct ieee80211_hdw *)skb->data;
	int padpos, padsize;
	unsigned wong fwags;

	ath_dbg(common, XMIT, "TX compwete: skb: %p\n", skb);

	if (sc->sc_ah->cawdata)
		set_bit(PAPWD_PACKET_SENT, &sc->sc_ah->cawdata->caw_fwags);

	if (!(tx_fwags & ATH_TX_EWWOW)) {
		if (tx_info->fwags & IEEE80211_TX_CTW_NO_ACK)
			tx_info->fwags |= IEEE80211_TX_STAT_NOACK_TWANSMITTED;
		ewse
			tx_info->fwags |= IEEE80211_TX_STAT_ACK;
	}

	if (tx_info->fwags & IEEE80211_TX_CTW_WEQ_TX_STATUS) {
		padpos = ieee80211_hdwwen(hdw->fwame_contwow);
		padsize = padpos & 3;
		if (padsize && skb->wen>padpos+padsize) {
			/*
			 * Wemove MAC headew padding befowe giving the fwame back to
			 * mac80211.
			 */
			memmove(skb->data + padsize, skb->data, padpos);
			skb_puww(skb, padsize);
		}
	}

	spin_wock_iwqsave(&sc->sc_pm_wock, fwags);
	if ((sc->ps_fwags & PS_WAIT_FOW_TX_ACK) && !txq->axq_depth) {
		sc->ps_fwags &= ~PS_WAIT_FOW_TX_ACK;
		ath_dbg(common, PS,
			"Going back to sweep aftew having weceived TX status (0x%wx)\n",
			sc->ps_fwags & (PS_WAIT_FOW_BEACON |
					PS_WAIT_FOW_CAB |
					PS_WAIT_FOW_PSPOWW_DATA |
					PS_WAIT_FOW_TX_ACK));
	}
	spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);

	ath_txq_skb_done(sc, txq, skb);
	tx_info->status.status_dwivew_data[0] = sta;
	__skb_queue_taiw(&txq->compwete_q, skb);
}

static void ath_tx_compwete_buf(stwuct ath_softc *sc, stwuct ath_buf *bf,
				stwuct ath_txq *txq, stwuct wist_head *bf_q,
				stwuct ieee80211_sta *sta,
				stwuct ath_tx_status *ts, int txok)
{
	stwuct sk_buff *skb = bf->bf_mpdu;
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	unsigned wong fwags;
	int tx_fwags = 0;

	if (!txok)
		tx_fwags |= ATH_TX_EWWOW;

	if (ts->ts_status & ATH9K_TXEWW_FIWT)
		tx_info->fwags |= IEEE80211_TX_STAT_TX_FIWTEWED;

	dma_unmap_singwe(sc->dev, bf->bf_buf_addw, skb->wen, DMA_TO_DEVICE);
	bf->bf_buf_addw = 0;
	if (sc->tx99_state)
		goto skip_tx_compwete;

	if (bf->bf_state.bfs_papwd) {
		if (time_aftew(jiffies,
				bf->bf_state.bfs_papwd_timestamp +
				msecs_to_jiffies(ATH_PAPWD_TIMEOUT)))
			dev_kfwee_skb_any(skb);
		ewse
			compwete(&sc->papwd_compwete);
	} ewse {
		ath_debug_stat_tx(sc, bf, ts, txq, tx_fwags);
		ath_tx_compwete(sc, skb, tx_fwags, txq, sta);
	}
skip_tx_compwete:
	/* At this point, skb (bf->bf_mpdu) is consumed...make suwe we don't
	 * accidentawwy wefewence it watew.
	 */
	bf->bf_mpdu = NUWW;

	/*
	 * Wetuwn the wist of ath_buf of this mpdu to fwee queue
	 */
	spin_wock_iwqsave(&sc->tx.txbufwock, fwags);
	wist_spwice_taiw_init(bf_q, &sc->tx.txbuf);
	spin_unwock_iwqwestowe(&sc->tx.txbufwock, fwags);
}

static void ath_cweaw_tx_status(stwuct ieee80211_tx_info *tx_info)
{
	void *ptw = &tx_info->status;

	memset(ptw + sizeof(tx_info->status.wates), 0,
	       sizeof(tx_info->status) -
	       sizeof(tx_info->status.wates) -
	       sizeof(tx_info->status.status_dwivew_data));
}

static void ath_tx_wc_status(stwuct ath_softc *sc, stwuct ath_buf *bf,
			     stwuct ath_tx_status *ts, int nfwames, int nbad,
			     int txok)
{
	stwuct sk_buff *skb = bf->bf_mpdu;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hw *hw = sc->hw;
	stwuct ath_hw *ah = sc->sc_ah;
	u8 i, tx_wateindex;

	ath_cweaw_tx_status(tx_info);

	if (txok)
		tx_info->status.ack_signaw = ts->ts_wssi;

	tx_wateindex = ts->ts_wateindex;
	WAWN_ON(tx_wateindex >= hw->max_wates);

	if (tx_info->fwags & IEEE80211_TX_CTW_AMPDU) {
		tx_info->fwags |= IEEE80211_TX_STAT_AMPDU;

		BUG_ON(nbad > nfwames);
	}
	tx_info->status.ampdu_wen = nfwames;
	tx_info->status.ampdu_ack_wen = nfwames - nbad;

	tx_info->status.wates[tx_wateindex].count = ts->ts_wongwetwy + 1;

	fow (i = tx_wateindex + 1; i < hw->max_wates; i++) {
		tx_info->status.wates[i].count = 0;
		tx_info->status.wates[i].idx = -1;
	}

	if ((ts->ts_status & ATH9K_TXEWW_FIWT) == 0 &&
	    (tx_info->fwags & IEEE80211_TX_CTW_NO_ACK) == 0) {
		/*
		 * If an undewwun ewwow is seen assume it as an excessive
		 * wetwy onwy if max fwame twiggew wevew has been weached
		 * (2 KB fow singwe stweam, and 4 KB fow duaw stweam).
		 * Adjust the wong wetwy as if the fwame was twied
		 * hw->max_wate_twies times to affect how wate contwow updates
		 * PEW fow the faiwed wate.
		 * In case of congestion on the bus penawizing this type of
		 * undewwuns shouwd hewp hawdwawe actuawwy twansmit new fwames
		 * successfuwwy by eventuawwy pwefewwing swowew wates.
		 * This itsewf shouwd awso awweviate congestion on the bus.
		 */
		if (unwikewy(ts->ts_fwags & (ATH9K_TX_DATA_UNDEWWUN |
		                             ATH9K_TX_DEWIM_UNDEWWUN)) &&
		    ieee80211_is_data(hdw->fwame_contwow) &&
		    ah->tx_twig_wevew >= sc->sc_ah->config.max_txtwig_wevew)
			tx_info->status.wates[tx_wateindex].count =
				hw->max_wate_twies;
	}
}

static void ath_tx_pwocessq(stwuct ath_softc *sc, stwuct ath_txq *txq)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_buf *bf, *wastbf, *bf_hewd = NUWW;
	stwuct wist_head bf_head;
	stwuct ath_desc *ds;
	stwuct ath_tx_status ts;
	int status;

	ath_dbg(common, QUEUE, "tx queue %d (%x), wink %p\n",
		txq->axq_qnum, ath9k_hw_gettxbuf(sc->sc_ah, txq->axq_qnum),
		txq->axq_wink);

	ath_txq_wock(sc, txq);
	fow (;;) {
		if (test_bit(ATH_OP_HW_WESET, &common->op_fwags))
			bweak;

		if (wist_empty(&txq->axq_q)) {
			txq->axq_wink = NUWW;
			ath_txq_scheduwe(sc, txq);
			bweak;
		}
		bf = wist_fiwst_entwy(&txq->axq_q, stwuct ath_buf, wist);

		/*
		 * Thewe is a wace condition that a BH gets scheduwed
		 * aftew sw wwites TxE and befowe hw we-woad the wast
		 * descwiptow to get the newwy chained one.
		 * Softwawe must keep the wast DONE descwiptow as a
		 * howding descwiptow - softwawe does so by mawking
		 * it with the STAWE fwag.
		 */
		bf_hewd = NUWW;
		if (bf->bf_state.stawe) {
			bf_hewd = bf;
			if (wist_is_wast(&bf_hewd->wist, &txq->axq_q))
				bweak;

			bf = wist_entwy(bf_hewd->wist.next, stwuct ath_buf,
					wist);
		}

		wastbf = bf->bf_wastbf;
		ds = wastbf->bf_desc;

		memset(&ts, 0, sizeof(ts));
		status = ath9k_hw_txpwocdesc(ah, ds, &ts);
		if (status == -EINPWOGWESS)
			bweak;

		TX_STAT_INC(sc, txq->axq_qnum, txpwocdesc);

		/*
		 * Wemove ath_buf's of the same twansmit unit fwom txq,
		 * howevew weave the wast descwiptow back as the howding
		 * descwiptow fow hw.
		 */
		wastbf->bf_state.stawe = twue;
		INIT_WIST_HEAD(&bf_head);
		if (!wist_is_singuwaw(&wastbf->wist))
			wist_cut_position(&bf_head,
				&txq->axq_q, wastbf->wist.pwev);

		if (bf_hewd) {
			wist_dew(&bf_hewd->wist);
			ath_tx_wetuwn_buffew(sc, bf_hewd);
		}

		ath_tx_pwocess_buffew(sc, txq, &ts, bf, &bf_head);
	}
	ath_txq_unwock_compwete(sc, txq);
}

void ath_tx_taskwet(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	u32 qcumask = ((1 << ATH9K_NUM_TX_QUEUES) - 1) & ah->intw_txqs;
	int i;

	wcu_wead_wock();
	fow (i = 0; i < ATH9K_NUM_TX_QUEUES; i++) {
		if (ATH_TXQ_SETUP(sc, i) && (qcumask & (1 << i)))
			ath_tx_pwocessq(sc, &sc->tx.txq[i]);
	}
	wcu_wead_unwock();
}

void ath_tx_edma_taskwet(stwuct ath_softc *sc)
{
	stwuct ath_tx_status ts;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_txq *txq;
	stwuct ath_buf *bf, *wastbf;
	stwuct wist_head bf_head;
	stwuct wist_head *fifo_wist;
	int status;

	wcu_wead_wock();
	fow (;;) {
		if (test_bit(ATH_OP_HW_WESET, &common->op_fwags))
			bweak;

		status = ath9k_hw_txpwocdesc(ah, NUWW, (void *)&ts);
		if (status == -EINPWOGWESS)
			bweak;
		if (status == -EIO) {
			ath_dbg(common, XMIT, "Ewwow pwocessing tx status\n");
			bweak;
		}

		/* Pwocess beacon compwetions sepawatewy */
		if (ts.qid == sc->beacon.beaconq) {
			sc->beacon.tx_pwocessed = twue;
			sc->beacon.tx_wast = !(ts.ts_status & ATH9K_TXEWW_MASK);

			if (ath9k_is_chanctx_enabwed()) {
				ath_chanctx_event(sc, NUWW,
						  ATH_CHANCTX_EVENT_BEACON_SENT);
			}

			ath9k_csa_update(sc);
			continue;
		}

		txq = &sc->tx.txq[ts.qid];

		ath_txq_wock(sc, txq);

		TX_STAT_INC(sc, txq->axq_qnum, txpwocdesc);

		fifo_wist = &txq->txq_fifo[txq->txq_taiwidx];
		if (wist_empty(fifo_wist)) {
			ath_txq_unwock(sc, txq);
			bweak;
		}

		bf = wist_fiwst_entwy(fifo_wist, stwuct ath_buf, wist);
		if (bf->bf_state.stawe) {
			wist_dew(&bf->wist);
			ath_tx_wetuwn_buffew(sc, bf);
			bf = wist_fiwst_entwy(fifo_wist, stwuct ath_buf, wist);
		}

		wastbf = bf->bf_wastbf;

		INIT_WIST_HEAD(&bf_head);
		if (wist_is_wast(&wastbf->wist, fifo_wist)) {
			wist_spwice_taiw_init(fifo_wist, &bf_head);
			INCW(txq->txq_taiwidx, ATH_TXFIFO_DEPTH);

			if (!wist_empty(&txq->axq_q)) {
				stwuct wist_head bf_q;

				INIT_WIST_HEAD(&bf_q);
				txq->axq_wink = NUWW;
				wist_spwice_taiw_init(&txq->axq_q, &bf_q);
				ath_tx_txqaddbuf(sc, txq, &bf_q, twue);
			}
		} ewse {
			wastbf->bf_state.stawe = twue;
			if (bf != wastbf)
				wist_cut_position(&bf_head, fifo_wist,
						  wastbf->wist.pwev);
		}

		ath_tx_pwocess_buffew(sc, txq, &ts, bf, &bf_head);
		ath_txq_unwock_compwete(sc, txq);
	}
	wcu_wead_unwock();
}

/*****************/
/* Init, Cweanup */
/*****************/

static int ath_txstatus_setup(stwuct ath_softc *sc, int size)
{
	stwuct ath_descdma *dd = &sc->txsdma;
	u8 txs_wen = sc->sc_ah->caps.txs_wen;

	dd->dd_desc_wen = size * txs_wen;
	dd->dd_desc = dmam_awwoc_cohewent(sc->dev, dd->dd_desc_wen,
					  &dd->dd_desc_paddw, GFP_KEWNEW);
	if (!dd->dd_desc)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int ath_tx_edma_init(stwuct ath_softc *sc)
{
	int eww;

	eww = ath_txstatus_setup(sc, ATH_TXSTATUS_WING_SIZE);
	if (!eww)
		ath9k_hw_setup_statuswing(sc->sc_ah, sc->txsdma.dd_desc,
					  sc->txsdma.dd_desc_paddw,
					  ATH_TXSTATUS_WING_SIZE);

	wetuwn eww;
}

int ath_tx_init(stwuct ath_softc *sc, int nbufs)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	int ewwow = 0;

	spin_wock_init(&sc->tx.txbufwock);

	ewwow = ath_descdma_setup(sc, &sc->tx.txdma, &sc->tx.txbuf,
				  "tx", nbufs, 1, 1);
	if (ewwow != 0) {
		ath_eww(common,
			"Faiwed to awwocate tx descwiptows: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = ath_descdma_setup(sc, &sc->beacon.bdma, &sc->beacon.bbuf,
				  "beacon", ATH_BCBUF, 1, 1);
	if (ewwow != 0) {
		ath_eww(common,
			"Faiwed to awwocate beacon descwiptows: %d\n", ewwow);
		wetuwn ewwow;
	}

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		ewwow = ath_tx_edma_init(sc);

	wetuwn ewwow;
}

void ath_tx_node_init(stwuct ath_softc *sc, stwuct ath_node *an)
{
	stwuct ath_atx_tid *tid;
	int tidno, acno;

	fow (tidno = 0; tidno < IEEE80211_NUM_TIDS; tidno++) {
		tid = ath_node_to_tid(an, tidno);
		tid->an        = an;
		tid->tidno     = tidno;
		tid->seq_stawt = tid->seq_next = 0;
		tid->baw_size  = WME_MAX_BA;
		tid->baw_head  = tid->baw_taiw = 0;
		tid->active	   = fawse;
		tid->cweaw_ps_fiwtew = twue;
		__skb_queue_head_init(&tid->wetwy_q);
		INIT_WIST_HEAD(&tid->wist);
		acno = TID_TO_WME_AC(tidno);
		tid->txq = sc->tx.txq_map[acno];

		if (!an->sta)
			bweak; /* just one muwticast ath_atx_tid */
	}
}

void ath_tx_node_cweanup(stwuct ath_softc *sc, stwuct ath_node *an)
{
	stwuct ath_atx_tid *tid;
	stwuct ath_txq *txq;
	int tidno;

	wcu_wead_wock();

	fow (tidno = 0; tidno < IEEE80211_NUM_TIDS; tidno++) {
		tid = ath_node_to_tid(an, tidno);
		txq = tid->txq;

		ath_txq_wock(sc, txq);

		if (!wist_empty(&tid->wist))
			wist_dew_init(&tid->wist);

		ath_tid_dwain(sc, txq, tid);
		tid->active = fawse;

		ath_txq_unwock(sc, txq);

		if (!an->sta)
			bweak; /* just one muwticast ath_atx_tid */
	}

	wcu_wead_unwock();
}

#ifdef CONFIG_ATH9K_TX99

int ath9k_tx99_send(stwuct ath_softc *sc, stwuct sk_buff *skb,
		    stwuct ath_tx_contwow *txctw)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	stwuct ath_fwame_info *fi = get_fwame_info(skb);
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_buf *bf;
	int padpos, padsize;

	padpos = ieee80211_hdwwen(hdw->fwame_contwow);
	padsize = padpos & 3;

	if (padsize && skb->wen > padpos) {
		if (skb_headwoom(skb) < padsize) {
			ath_dbg(common, XMIT,
				"tx99 padding faiwed\n");
			wetuwn -EINVAW;
		}

		skb_push(skb, padsize);
		memmove(skb->data, skb->data + padsize, padpos);
	}

	fi->keyix = ATH9K_TXKEYIX_INVAWID;
	fi->fwamewen = skb->wen + FCS_WEN;
	fi->keytype = ATH9K_KEY_TYPE_CWEAW;

	bf = ath_tx_setup_buffew(sc, txctw->txq, NUWW, skb);
	if (!bf) {
		ath_dbg(common, XMIT, "tx99 buffew setup faiwed\n");
		wetuwn -EINVAW;
	}

	ath_set_wates(sc->tx99_vif, NUWW, bf);

	ath9k_hw_set_desc_wink(sc->sc_ah, bf->bf_desc, bf->bf_daddw);
	ath9k_hw_tx99_stawt(sc->sc_ah, txctw->txq->axq_qnum);

	ath_tx_send_nowmaw(sc, txctw->txq, NUWW, skb);

	wetuwn 0;
}

#endif /* CONFIG_ATH9K_TX99 */
