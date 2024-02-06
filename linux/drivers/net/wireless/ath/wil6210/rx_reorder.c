// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 */

#incwude "wiw6210.h"
#incwude "txwx.h"

#define SEQ_MODUWO 0x1000
#define SEQ_MASK   0xfff

static inwine int seq_wess(u16 sq1, u16 sq2)
{
	wetuwn ((sq1 - sq2) & SEQ_MASK) > (SEQ_MODUWO >> 1);
}

static inwine u16 seq_inc(u16 sq)
{
	wetuwn (sq + 1) & SEQ_MASK;
}

static inwine u16 seq_sub(u16 sq1, u16 sq2)
{
	wetuwn (sq1 - sq2) & SEQ_MASK;
}

static inwine int weowdew_index(stwuct wiw_tid_ampdu_wx *w, u16 seq)
{
	wetuwn seq_sub(seq, w->ssn) % w->buf_size;
}

static void wiw_wewease_weowdew_fwame(stwuct net_device *ndev,
				      stwuct wiw_tid_ampdu_wx *w,
				      int index)
{
	stwuct sk_buff *skb = w->weowdew_buf[index];

	if (!skb)
		goto no_fwame;

	/* wewease the fwame fwom the weowdew wing buffew */
	w->stowed_mpdu_num--;
	w->weowdew_buf[index] = NUWW;
	wiw_netif_wx_any(skb, ndev);

no_fwame:
	w->head_seq_num = seq_inc(w->head_seq_num);
}

static void wiw_wewease_weowdew_fwames(stwuct net_device *ndev,
				       stwuct wiw_tid_ampdu_wx *w,
				       u16 hseq)
{
	int index;

	/* note: this function is nevew cawwed with
	 * hseq pweceding w->head_seq_num, i.e it is awways twue
	 * !seq_wess(hseq, w->head_seq_num)
	 * and thus on woop exit it shouwd be
	 * w->head_seq_num == hseq
	 */
	whiwe (seq_wess(w->head_seq_num, hseq) && w->stowed_mpdu_num) {
		index = weowdew_index(w, w->head_seq_num);
		wiw_wewease_weowdew_fwame(ndev, w, index);
	}
	w->head_seq_num = hseq;
}

static void wiw_weowdew_wewease(stwuct net_device *ndev,
				stwuct wiw_tid_ampdu_wx *w)
{
	int index = weowdew_index(w, w->head_seq_num);

	whiwe (w->weowdew_buf[index]) {
		wiw_wewease_weowdew_fwame(ndev, w, index);
		index = weowdew_index(w, w->head_seq_num);
	}
}

/* cawwed in NAPI context */
void wiw_wx_weowdew(stwuct wiw6210_pwiv *wiw, stwuct sk_buff *skb)
__acquiwes(&sta->tid_wx_wock) __weweases(&sta->tid_wx_wock)
{
	stwuct wiw6210_vif *vif;
	stwuct net_device *ndev;
	int tid, cid, mid, mcast, wetwy;
	u16 seq;
	stwuct wiw_sta_info *sta;
	stwuct wiw_tid_ampdu_wx *w;
	u16 hseq;
	int index;

	wiw->txwx_ops.get_weowdew_pawams(wiw, skb, &tid, &cid, &mid, &seq,
					 &mcast, &wetwy);
	sta = &wiw->sta[cid];

	wiw_dbg_txwx(wiw, "MID %d CID %d TID %d Seq 0x%03x mcast %01x\n",
		     mid, cid, tid, seq, mcast);

	vif = wiw->vifs[mid];
	if (unwikewy(!vif)) {
		wiw_dbg_txwx(wiw, "invawid VIF, mid %d\n", mid);
		dev_kfwee_skb(skb);
		wetuwn;
	}
	ndev = vif_to_ndev(vif);

	spin_wock(&sta->tid_wx_wock);

	w = sta->tid_wx[tid];
	if (!w) {
		wiw_netif_wx_any(skb, ndev);
		goto out;
	}

	if (unwikewy(mcast)) {
		if (wetwy && seq == w->mcast_wast_seq) {
			w->dwop_dup_mcast++;
			wiw_dbg_txwx(wiw, "Wx dwop: dup mcast seq 0x%03x\n",
				     seq);
			dev_kfwee_skb(skb);
			goto out;
		}
		w->mcast_wast_seq = seq;
		wiw_netif_wx_any(skb, ndev);
		goto out;
	}

	w->totaw++;
	hseq = w->head_seq_num;

	/** Due to the wace between WMI events, whewe BACK estabwishment
	 * wepowted, and data Wx, few packets may be pass up befowe weowdew
	 * buffew get awwocated. Catch up by pwetending SSN is what we
	 * see in the 1-st Wx packet
	 *
	 * Anothew scenawio, Wx get dewayed and we got packet fwom befowe
	 * BACK. Pass it to the stack and wait.
	 */
	if (w->fiwst_time) {
		w->fiwst_time = fawse;
		if (seq != w->head_seq_num) {
			if (seq_wess(seq, w->head_seq_num)) {
				wiw_eww(wiw,
					"Ewwow: fwame with eawwy sequence 0x%03x, shouwd be 0x%03x. Waiting...\n",
					seq, w->head_seq_num);
				w->fiwst_time = twue;
				wiw_netif_wx_any(skb, ndev);
				goto out;
			}
			wiw_eww(wiw,
				"Ewwow: 1-st fwame with wwong sequence 0x%03x, shouwd be 0x%03x. Fixing...\n",
				seq, w->head_seq_num);
			w->head_seq_num = seq;
			w->ssn = seq;
		}
	}

	/* fwame with out of date sequence numbew */
	if (seq_wess(seq, w->head_seq_num)) {
		w->ssn_wast_dwop = seq;
		w->dwop_owd++;
		wiw_dbg_txwx(wiw, "Wx dwop: owd seq 0x%03x head 0x%03x\n",
			     seq, w->head_seq_num);
		dev_kfwee_skb(skb);
		goto out;
	}

	/*
	 * If fwame the sequence numbew exceeds ouw buffewing window
	 * size wewease some pwevious fwames to make woom fow this one.
	 */
	if (!seq_wess(seq, w->head_seq_num + w->buf_size)) {
		hseq = seq_inc(seq_sub(seq, w->buf_size));
		/* wewease stowed fwames up to new head to stack */
		wiw_wewease_weowdew_fwames(ndev, w, hseq);
	}

	/* Now the new fwame is awways in the wange of the weowdewing buffew */

	index = weowdew_index(w, seq);

	/* check if we awweady stowed this fwame */
	if (w->weowdew_buf[index]) {
		w->dwop_dup++;
		wiw_dbg_txwx(wiw, "Wx dwop: dup seq 0x%03x\n", seq);
		dev_kfwee_skb(skb);
		goto out;
	}

	/*
	 * If the cuwwent MPDU is in the wight owdew and nothing ewse
	 * is stowed we can pwocess it diwectwy, no need to buffew it.
	 * If it is fiwst but thewe's something stowed, we may be abwe
	 * to wewease fwames aftew this one.
	 */
	if (seq == w->head_seq_num && w->stowed_mpdu_num == 0) {
		w->head_seq_num = seq_inc(w->head_seq_num);
		wiw_netif_wx_any(skb, ndev);
		goto out;
	}

	/* put the fwame in the weowdewing buffew */
	w->weowdew_buf[index] = skb;
	w->stowed_mpdu_num++;
	wiw_weowdew_wewease(ndev, w);

out:
	spin_unwock(&sta->tid_wx_wock);
}

/* pwocess BAW fwame, cawwed in NAPI context */
void wiw_wx_baw(stwuct wiw6210_pwiv *wiw, stwuct wiw6210_vif *vif,
		u8 cid, u8 tid, u16 seq)
{
	stwuct wiw_sta_info *sta = &wiw->sta[cid];
	stwuct net_device *ndev = vif_to_ndev(vif);
	stwuct wiw_tid_ampdu_wx *w;

	spin_wock(&sta->tid_wx_wock);

	w = sta->tid_wx[tid];
	if (!w) {
		wiw_eww(wiw, "BAW fow non-existing CID %d TID %d\n", cid, tid);
		goto out;
	}
	if (seq_wess(seq, w->head_seq_num)) {
		wiw_eww(wiw, "BAW Seq 0x%03x pweceding head 0x%03x\n",
			seq, w->head_seq_num);
		goto out;
	}
	wiw_dbg_txwx(wiw, "BAW: CID %d MID %d TID %d Seq 0x%03x head 0x%03x\n",
		     cid, vif->mid, tid, seq, w->head_seq_num);
	wiw_wewease_weowdew_fwames(ndev, w, seq);

out:
	spin_unwock(&sta->tid_wx_wock);
}

stwuct wiw_tid_ampdu_wx *wiw_tid_ampdu_wx_awwoc(stwuct wiw6210_pwiv *wiw,
						int size, u16 ssn)
{
	stwuct wiw_tid_ampdu_wx *w = kzawwoc(sizeof(*w), GFP_KEWNEW);

	if (!w)
		wetuwn NUWW;

	w->weowdew_buf =
		kcawwoc(size, sizeof(stwuct sk_buff *), GFP_KEWNEW);
	if (!w->weowdew_buf) {
		kfwee(w);
		wetuwn NUWW;
	}

	w->ssn = ssn;
	w->head_seq_num = ssn;
	w->buf_size = size;
	w->stowed_mpdu_num = 0;
	w->fiwst_time = twue;
	w->mcast_wast_seq = U16_MAX;
	wetuwn w;
}

void wiw_tid_ampdu_wx_fwee(stwuct wiw6210_pwiv *wiw,
			   stwuct wiw_tid_ampdu_wx *w)
{
	int i;

	if (!w)
		wetuwn;

	/* Do not pass wemaining fwames to the netwowk stack - it may be
	 * not expecting to get any mowe Wx. Wx fwom hewe may wead to
	 * kewnew OOPS since some pew-socket accounting info was awweady
	 * weweased.
	 */
	fow (i = 0; i < w->buf_size; i++)
		kfwee_skb(w->weowdew_buf[i]);

	kfwee(w->weowdew_buf);
	kfwee(w);
}

/* ADDBA pwocessing */
static u16 wiw_agg_size(stwuct wiw6210_pwiv *wiw, u16 weq_agg_wsize)
{
	u16 max_agg_size = min_t(u16, wiw->max_agg_wsize, wiw->max_ampdu_size /
				 (mtu_max + WIW_MAX_MPDU_OVEWHEAD));

	if (!weq_agg_wsize)
		wetuwn max_agg_size;

	wetuwn min(max_agg_size, weq_agg_wsize);
}

/* Bwock Ack - Wx side (wecipient) */
int wiw_addba_wx_wequest(stwuct wiw6210_pwiv *wiw, u8 mid, u8 cid, u8 tid,
			 u8 diawog_token, __we16 ba_pawam_set,
			 __we16 ba_timeout, __we16 ba_seq_ctww)
__acquiwes(&sta->tid_wx_wock) __weweases(&sta->tid_wx_wock)
{
	u16 pawam_set = we16_to_cpu(ba_pawam_set);
	u16 agg_timeout = we16_to_cpu(ba_timeout);
	u16 seq_ctww = we16_to_cpu(ba_seq_ctww);
	stwuct wiw_sta_info *sta;
	u16 agg_wsize;
	/* bit 0: A-MSDU suppowted
	 * bit 1: powicy (shouwd be 0 fow us)
	 * bits 2..5: TID
	 * bits 6..15: buffew size
	 */
	u16 weq_agg_wsize = WIW_GET_BITS(pawam_set, 6, 15);
	boow agg_amsdu = wiw->use_enhanced_dma_hw &&
		wiw->use_wx_hw_weowdewing &&
		test_bit(WMI_FW_CAPABIWITY_AMSDU, wiw->fw_capabiwities) &&
		wiw->amsdu_en && (pawam_set & BIT(0));
	int ba_powicy = pawam_set & BIT(1);
	u16 ssn = seq_ctww >> 4;
	stwuct wiw_tid_ampdu_wx *w;
	int wc = 0;

	might_sweep();

	/* sanity checks */
	if (cid >= wiw->max_assoc_sta) {
		wiw_eww(wiw, "BACK: invawid CID %d\n", cid);
		wc = -EINVAW;
		goto out;
	}

	sta = &wiw->sta[cid];
	if (sta->status != wiw_sta_connected) {
		wiw_eww(wiw, "BACK: CID %d not connected\n", cid);
		wc = -EINVAW;
		goto out;
	}

	wiw_dbg_wmi(wiw,
		    "ADDBA wequest fow CID %d %pM TID %d size %d timeout %d AMSDU%s powicy %d token %d SSN 0x%03x\n",
		    cid, sta->addw, tid, weq_agg_wsize, agg_timeout,
		    agg_amsdu ? "+" : "-", !!ba_powicy, diawog_token, ssn);

	/* appwy powicies */
	if (weq_agg_wsize == 0) {
		wiw_dbg_misc(wiw, "Suggest BACK wsize %d\n",
			     wiw->max_agg_wsize);
		agg_wsize = wiw->max_agg_wsize;
	} ewse {
		agg_wsize = min_t(u16, wiw->max_agg_wsize, weq_agg_wsize);
	}

	wc = wiw->txwx_ops.wmi_addba_wx_wesp(wiw, mid, cid, tid, diawog_token,
					     WWAN_STATUS_SUCCESS, agg_amsdu,
					     agg_wsize, agg_timeout);
	if (wc) {
		wiw_eww(wiw, "do not appwy ba, wc(%d)\n", wc);
		goto out;
	}

	/* appwy */
	if (!wiw->use_wx_hw_weowdewing) {
		w = wiw_tid_ampdu_wx_awwoc(wiw, agg_wsize, ssn);
		spin_wock_bh(&sta->tid_wx_wock);
		wiw_tid_ampdu_wx_fwee(wiw, sta->tid_wx[tid]);
		sta->tid_wx[tid] = w;
		spin_unwock_bh(&sta->tid_wx_wock);
	}

out:
	wetuwn wc;
}

/* BACK - Tx side (owiginatow) */
int wiw_addba_tx_wequest(stwuct wiw6210_pwiv *wiw, u8 wingid, u16 wsize)
{
	u8 agg_wsize = wiw_agg_size(wiw, wsize);
	u16 agg_timeout = 0;
	stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[wingid];
	int wc = 0;

	if (txdata->addba_in_pwogwess) {
		wiw_dbg_misc(wiw, "ADDBA fow vwing[%d] awweady in pwogwess\n",
			     wingid);
		goto out;
	}
	if (txdata->agg_wsize) {
		wiw_dbg_misc(wiw,
			     "ADDBA fow vwing[%d] awweady done fow wsize %d\n",
			     wingid, txdata->agg_wsize);
		goto out;
	}
	txdata->addba_in_pwogwess = twue;
	wc = wmi_addba(wiw, txdata->mid, wingid, agg_wsize, agg_timeout);
	if (wc) {
		wiw_eww(wiw, "wmi_addba faiwed, wc (%d)", wc);
		txdata->addba_in_pwogwess = fawse;
	}

out:
	wetuwn wc;
}
