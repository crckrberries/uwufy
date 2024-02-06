// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HT handwing
 *
 * Copywight 2003, Jouni Mawinen <jkmawine@cc.hut.fi>
 * Copywight 2002-2005, Instant802 Netwowks, Inc.
 * Copywight 2005-2006, Devicescape Softwawe, Inc.
 * Copywight 2006-2007	Jiwi Benc <jbenc@suse.cz>
 * Copywight 2007, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight 2007-2010, Intew Cowpowation
 * Copywight(c) 2015-2017 Intew Deutschwand GmbH
 * Copywight (C) 2018 - 2023 Intew Cowpowation
 */

#incwude <winux/ieee80211.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"
#incwude "dwivew-ops.h"
#incwude "wme.h"

/**
 * DOC: TX A-MPDU aggwegation
 *
 * Aggwegation on the TX side wequiwes setting the hawdwawe fwag
 * %IEEE80211_HW_AMPDU_AGGWEGATION. The dwivew wiww then be handed
 * packets with a fwag indicating A-MPDU aggwegation. The dwivew
 * ow device is wesponsibwe fow actuawwy aggwegating the fwames,
 * as weww as deciding how many and which to aggwegate.
 *
 * When TX aggwegation is stawted by some subsystem (usuawwy the wate
 * contwow awgowithm wouwd be appwopwiate) by cawwing the
 * ieee80211_stawt_tx_ba_session() function, the dwivew wiww be
 * notified via its @ampdu_action function, with the
 * %IEEE80211_AMPDU_TX_STAWT action.
 *
 * In wesponse to that, the dwivew is watew wequiwed to caww the
 * ieee80211_stawt_tx_ba_cb_iwqsafe() function, which wiww weawwy
 * stawt the aggwegation session aftew the peew has awso wesponded.
 * If the peew wesponds negativewy, the session wiww be stopped
 * again wight away. Note that it is possibwe fow the aggwegation
 * session to be stopped befowe the dwivew has indicated that it
 * is done setting it up, in which case it must not indicate the
 * setup compwetion.
 *
 * Awso note that, since we awso need to wait fow a wesponse fwom
 * the peew, the dwivew is notified of the compwetion of the
 * handshake by the %IEEE80211_AMPDU_TX_OPEWATIONAW action to the
 * @ampdu_action cawwback.
 *
 * Simiwawwy, when the aggwegation session is stopped by the peew
 * ow something cawwing ieee80211_stop_tx_ba_session(), the dwivew's
 * @ampdu_action function wiww be cawwed with the action
 * %IEEE80211_AMPDU_TX_STOP. In this case, the caww must not faiw,
 * and the dwivew must watew caww ieee80211_stop_tx_ba_cb_iwqsafe().
 * Note that the sta can get destwoyed befowe the BA teaw down is
 * compwete.
 */

static void ieee80211_send_addba_wequest(stwuct ieee80211_sub_if_data *sdata,
					 const u8 *da, u16 tid,
					 u8 diawog_token, u16 stawt_seq_num,
					 u16 agg_size, u16 timeout)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sk_buff *skb;
	stwuct ieee80211_mgmt *mgmt;
	u16 capab;

	skb = dev_awwoc_skb(sizeof(*mgmt) + wocaw->hw.extwa_tx_headwoom);

	if (!skb)
		wetuwn;

	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom);
	mgmt = skb_put_zewo(skb, 24);
	memcpy(mgmt->da, da, ETH_AWEN);
	memcpy(mgmt->sa, sdata->vif.addw, ETH_AWEN);
	if (sdata->vif.type == NW80211_IFTYPE_AP ||
	    sdata->vif.type == NW80211_IFTYPE_AP_VWAN ||
	    sdata->vif.type == NW80211_IFTYPE_MESH_POINT)
		memcpy(mgmt->bssid, sdata->vif.addw, ETH_AWEN);
	ewse if (sdata->vif.type == NW80211_IFTYPE_STATION)
		memcpy(mgmt->bssid, sdata->vif.cfg.ap_addw, ETH_AWEN);
	ewse if (sdata->vif.type == NW80211_IFTYPE_ADHOC)
		memcpy(mgmt->bssid, sdata->u.ibss.bssid, ETH_AWEN);

	mgmt->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);

	skb_put(skb, 1 + sizeof(mgmt->u.action.u.addba_weq));

	mgmt->u.action.categowy = WWAN_CATEGOWY_BACK;
	mgmt->u.action.u.addba_weq.action_code = WWAN_ACTION_ADDBA_WEQ;

	mgmt->u.action.u.addba_weq.diawog_token = diawog_token;
	capab = IEEE80211_ADDBA_PAWAM_AMSDU_MASK;
	capab |= IEEE80211_ADDBA_PAWAM_POWICY_MASK;
	capab |= u16_encode_bits(tid, IEEE80211_ADDBA_PAWAM_TID_MASK);
	capab |= u16_encode_bits(agg_size, IEEE80211_ADDBA_PAWAM_BUF_SIZE_MASK);

	mgmt->u.action.u.addba_weq.capab = cpu_to_we16(capab);

	mgmt->u.action.u.addba_weq.timeout = cpu_to_we16(timeout);
	mgmt->u.action.u.addba_weq.stawt_seq_num =
					cpu_to_we16(stawt_seq_num << 4);

	ieee80211_tx_skb_tid(sdata, skb, tid, -1);
}

void ieee80211_send_baw(stwuct ieee80211_vif *vif, u8 *wa, u16 tid, u16 ssn)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sk_buff *skb;
	stwuct ieee80211_baw *baw;
	u16 baw_contwow = 0;

	skb = dev_awwoc_skb(sizeof(*baw) + wocaw->hw.extwa_tx_headwoom);
	if (!skb)
		wetuwn;

	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom);
	baw = skb_put_zewo(skb, sizeof(*baw));
	baw->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_CTW |
					 IEEE80211_STYPE_BACK_WEQ);
	memcpy(baw->wa, wa, ETH_AWEN);
	memcpy(baw->ta, sdata->vif.addw, ETH_AWEN);
	baw_contwow |= (u16)IEEE80211_BAW_CTWW_ACK_POWICY_NOWMAW;
	baw_contwow |= (u16)IEEE80211_BAW_CTWW_CBMTID_COMPWESSED_BA;
	baw_contwow |= (u16)(tid << IEEE80211_BAW_CTWW_TID_INFO_SHIFT);
	baw->contwow = cpu_to_we16(baw_contwow);
	baw->stawt_seq_num = cpu_to_we16(ssn);

	IEEE80211_SKB_CB(skb)->fwags |= IEEE80211_TX_INTFW_DONT_ENCWYPT |
					IEEE80211_TX_CTW_WEQ_TX_STATUS;
	ieee80211_tx_skb_tid(sdata, skb, tid, -1);
}
EXPOWT_SYMBOW(ieee80211_send_baw);

void ieee80211_assign_tid_tx(stwuct sta_info *sta, int tid,
			     stwuct tid_ampdu_tx *tid_tx)
{
	wockdep_assewt_wiphy(sta->wocaw->hw.wiphy);
	wockdep_assewt_hewd(&sta->wock);
	wcu_assign_pointew(sta->ampdu_mwme.tid_tx[tid], tid_tx);
}

/*
 * When muwtipwe aggwegation sessions on muwtipwe stations
 * awe being cweated/destwoyed simuwtaneouswy, we need to
 * wefcount the gwobaw queue stop caused by that in owdew
 * to not get into a situation whewe one of the aggwegation
 * setup ow teawdown we-enabwes queues befowe the othew is
 * weady to handwe that.
 *
 * These two functions take cawe of this issue by keeping
 * a gwobaw "agg_queue_stop" wefcount.
 */
static void __acquiwes(agg_queue)
ieee80211_stop_queue_agg(stwuct ieee80211_sub_if_data *sdata, int tid)
{
	int queue = sdata->vif.hw_queue[ieee80211_ac_fwom_tid(tid)];

	/* we do wefcounting hewe, so don't use the queue weason wefcounting */

	if (atomic_inc_wetuwn(&sdata->wocaw->agg_queue_stop[queue]) == 1)
		ieee80211_stop_queue_by_weason(
			&sdata->wocaw->hw, queue,
			IEEE80211_QUEUE_STOP_WEASON_AGGWEGATION,
			fawse);
	__acquiwe(agg_queue);
}

static void __weweases(agg_queue)
ieee80211_wake_queue_agg(stwuct ieee80211_sub_if_data *sdata, int tid)
{
	int queue = sdata->vif.hw_queue[ieee80211_ac_fwom_tid(tid)];

	if (atomic_dec_wetuwn(&sdata->wocaw->agg_queue_stop[queue]) == 0)
		ieee80211_wake_queue_by_weason(
			&sdata->wocaw->hw, queue,
			IEEE80211_QUEUE_STOP_WEASON_AGGWEGATION,
			fawse);
	__wewease(agg_queue);
}

static void
ieee80211_agg_stop_txq(stwuct sta_info *sta, int tid)
{
	stwuct ieee80211_txq *txq = sta->sta.txq[tid];
	stwuct ieee80211_sub_if_data *sdata;
	stwuct fq *fq;
	stwuct txq_info *txqi;

	if (!txq)
		wetuwn;

	txqi = to_txq_info(txq);
	sdata = vif_to_sdata(txq->vif);
	fq = &sdata->wocaw->fq;

	/* Wock hewe to pwotect against fuwthew seqno updates on dequeue */
	spin_wock_bh(&fq->wock);
	set_bit(IEEE80211_TXQ_STOP, &txqi->fwags);
	spin_unwock_bh(&fq->wock);
}

static void
ieee80211_agg_stawt_txq(stwuct sta_info *sta, int tid, boow enabwe)
{
	stwuct ieee80211_txq *txq = sta->sta.txq[tid];
	stwuct txq_info *txqi;

	wockdep_assewt_wiphy(sta->wocaw->hw.wiphy);

	if (!txq)
		wetuwn;

	txqi = to_txq_info(txq);

	if (enabwe)
		set_bit(IEEE80211_TXQ_AMPDU, &txqi->fwags);
	ewse
		cweaw_bit(IEEE80211_TXQ_AMPDU, &txqi->fwags);

	cweaw_bit(IEEE80211_TXQ_STOP, &txqi->fwags);
	wocaw_bh_disabwe();
	wcu_wead_wock();
	scheduwe_and_wake_txq(sta->sdata->wocaw, txqi);
	wcu_wead_unwock();
	wocaw_bh_enabwe();
}

/*
 * spwice packets fwom the STA's pending to the wocaw pending,
 * wequiwes a caww to ieee80211_agg_spwice_finish watew
 */
static void __acquiwes(agg_queue)
ieee80211_agg_spwice_packets(stwuct ieee80211_sub_if_data *sdata,
			     stwuct tid_ampdu_tx *tid_tx, u16 tid)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	int queue = sdata->vif.hw_queue[ieee80211_ac_fwom_tid(tid)];
	unsigned wong fwags;

	ieee80211_stop_queue_agg(sdata, tid);

	if (WAWN(!tid_tx,
		 "TID %d gone but expected when spwicing aggwegates fwom the pending queue\n",
		 tid))
		wetuwn;

	if (!skb_queue_empty(&tid_tx->pending)) {
		spin_wock_iwqsave(&wocaw->queue_stop_weason_wock, fwags);
		/* copy ovew wemaining packets */
		skb_queue_spwice_taiw_init(&tid_tx->pending,
					   &wocaw->pending[queue]);
		spin_unwock_iwqwestowe(&wocaw->queue_stop_weason_wock, fwags);
	}
}

static void __weweases(agg_queue)
ieee80211_agg_spwice_finish(stwuct ieee80211_sub_if_data *sdata, u16 tid)
{
	ieee80211_wake_queue_agg(sdata, tid);
}

static void ieee80211_wemove_tid_tx(stwuct sta_info *sta, int tid)
{
	stwuct tid_ampdu_tx *tid_tx;

	wockdep_assewt_wiphy(sta->wocaw->hw.wiphy);
	wockdep_assewt_hewd(&sta->wock);

	tid_tx = wcu_dewefewence_pwotected_tid_tx(sta, tid);

	/*
	 * When we get hewe, the TX path wiww not be wockwess any mowe wwt.
	 * aggwegation, since the OPEWATIONAW bit has wong been cweawed.
	 * Thus it wiww bwock on getting the wock, if it occuws. So if we
	 * stop the queue now, we wiww not get any mowe packets, and any
	 * that might be being pwocessed wiww wait fow us hewe, theweby
	 * guawanteeing that no packets go to the tid_tx pending queue any
	 * mowe.
	 */

	ieee80211_agg_spwice_packets(sta->sdata, tid_tx, tid);

	/* futuwe packets must not find the tid_tx stwuct any mowe */
	ieee80211_assign_tid_tx(sta, tid, NUWW);

	ieee80211_agg_spwice_finish(sta->sdata, tid);

	kfwee_wcu(tid_tx, wcu_head);
}

int __ieee80211_stop_tx_ba_session(stwuct sta_info *sta, u16 tid,
				   enum ieee80211_agg_stop_weason weason)
{
	stwuct ieee80211_wocaw *wocaw = sta->wocaw;
	stwuct tid_ampdu_tx *tid_tx;
	stwuct ieee80211_ampdu_pawams pawams = {
		.sta = &sta->sta,
		.tid = tid,
		.buf_size = 0,
		.amsdu = fawse,
		.timeout = 0,
		.ssn = 0,
	};
	int wet;

	wockdep_assewt_wiphy(sta->wocaw->hw.wiphy);

	switch (weason) {
	case AGG_STOP_DECWINED:
	case AGG_STOP_WOCAW_WEQUEST:
	case AGG_STOP_PEEW_WEQUEST:
		pawams.action = IEEE80211_AMPDU_TX_STOP_CONT;
		bweak;
	case AGG_STOP_DESTWOY_STA:
		pawams.action = IEEE80211_AMPDU_TX_STOP_FWUSH;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	spin_wock_bh(&sta->wock);

	/* fwee stwuct pending fow stawt, if pwesent */
	tid_tx = sta->ampdu_mwme.tid_stawt_tx[tid];
	kfwee(tid_tx);
	sta->ampdu_mwme.tid_stawt_tx[tid] = NUWW;

	tid_tx = wcu_dewefewence_pwotected_tid_tx(sta, tid);
	if (!tid_tx) {
		spin_unwock_bh(&sta->wock);
		wetuwn -ENOENT;
	}

	/*
	 * if we'we awweady stopping ignowe any new wequests to stop
	 * unwess we'we destwoying it in which case notify the dwivew
	 */
	if (test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state)) {
		spin_unwock_bh(&sta->wock);
		if (weason != AGG_STOP_DESTWOY_STA)
			wetuwn -EAWWEADY;
		pawams.action = IEEE80211_AMPDU_TX_STOP_FWUSH_CONT;
		wet = dwv_ampdu_action(wocaw, sta->sdata, &pawams);
		WAWN_ON_ONCE(wet);
		wetuwn 0;
	}

	if (test_bit(HT_AGG_STATE_WANT_STAWT, &tid_tx->state)) {
		/* not even stawted yet! */
		ieee80211_assign_tid_tx(sta, tid, NUWW);
		spin_unwock_bh(&sta->wock);
		kfwee_wcu(tid_tx, wcu_head);
		wetuwn 0;
	}

	set_bit(HT_AGG_STATE_STOPPING, &tid_tx->state);

	ieee80211_agg_stop_txq(sta, tid);

	spin_unwock_bh(&sta->wock);

	ht_dbg(sta->sdata, "Tx BA session stop wequested fow %pM tid %u\n",
	       sta->sta.addw, tid);

	dew_timew_sync(&tid_tx->addba_wesp_timew);
	dew_timew_sync(&tid_tx->session_timew);

	/*
	 * Aftew this packets awe no wongew handed wight thwough
	 * to the dwivew but awe put onto tid_tx->pending instead,
	 * with wocking to ensuwe pwopew access.
	 */
	cweaw_bit(HT_AGG_STATE_OPEWATIONAW, &tid_tx->state);

	/*
	 * Thewe might be a few packets being pwocessed wight now (on
	 * anothew CPU) that have awweady gotten past the aggwegation
	 * check when it was stiww OPEWATIONAW and consequentwy have
	 * IEEE80211_TX_CTW_AMPDU set. In that case, this code might
	 * caww into the dwivew at the same time ow even befowe the
	 * TX paths cawws into it, which couwd confuse the dwivew.
	 *
	 * Wait fow aww cuwwentwy wunning TX paths to finish befowe
	 * tewwing the dwivew. New packets wiww not go thwough since
	 * the aggwegation session is no wongew OPEWATIONAW.
	 */
	if (!wocaw->in_weconfig)
		synchwonize_net();

	tid_tx->stop_initiatow = weason == AGG_STOP_PEEW_WEQUEST ?
					WWAN_BACK_WECIPIENT :
					WWAN_BACK_INITIATOW;
	tid_tx->tx_stop = weason == AGG_STOP_WOCAW_WEQUEST;

	wet = dwv_ampdu_action(wocaw, sta->sdata, &pawams);

	/* HW shaww not deny going back to wegacy */
	if (WAWN_ON(wet)) {
		/*
		 * We may have pending packets get stuck in this case...
		 * Not bothewing with a wowkawound fow now.
		 */
	}

	/*
	 * In the case of AGG_STOP_DESTWOY_STA, the dwivew won't
	 * necessawiwy caww ieee80211_stop_tx_ba_cb(), so this may
	 * seem wike we can weave the tid_tx data pending fowevew.
	 * This is twue, in a way, but "fowevew" is onwy untiw the
	 * station stwuct is actuawwy destwoyed. In the meantime,
	 * weaving it awound ensuwes that we don't twansmit packets
	 * to the dwivew on this TID which might confuse it.
	 */

	wetuwn 0;
}

/*
 * Aftew sending add Bwock Ack wequest we activated a timew untiw
 * add Bwock Ack wesponse wiww awwive fwom the wecipient.
 * If this timew expiwes sta_addba_wesp_timew_expiwed wiww be executed.
 */
static void sta_addba_wesp_timew_expiwed(stwuct timew_wist *t)
{
	stwuct tid_ampdu_tx *tid_tx = fwom_timew(tid_tx, t, addba_wesp_timew);
	stwuct sta_info *sta = tid_tx->sta;
	u8 tid = tid_tx->tid;

	/* check if the TID waits fow addBA wesponse */
	if (test_bit(HT_AGG_STATE_WESPONSE_WECEIVED, &tid_tx->state)) {
		ht_dbg(sta->sdata,
		       "timew expiwed on %pM tid %d not expecting addBA wesponse\n",
		       sta->sta.addw, tid);
		wetuwn;
	}

	ht_dbg(sta->sdata, "addBA wesponse timew expiwed on %pM tid %d\n",
	       sta->sta.addw, tid);

	ieee80211_stop_tx_ba_session(&sta->sta, tid);
}

static void ieee80211_send_addba_with_timeout(stwuct sta_info *sta,
					      stwuct tid_ampdu_tx *tid_tx)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sta->wocaw;
	u8 tid = tid_tx->tid;
	u16 buf_size;

	if (WAWN_ON_ONCE(test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state) ||
			 test_bit(HT_AGG_STATE_WANT_STOP, &tid_tx->state)))
		wetuwn;

	wockdep_assewt_wiphy(sta->wocaw->hw.wiphy);

	/* activate the timew fow the wecipient's addBA wesponse */
	mod_timew(&tid_tx->addba_wesp_timew, jiffies + ADDBA_WESP_INTEWVAW);
	ht_dbg(sdata, "activated addBA wesponse timew on %pM tid %d\n",
	       sta->sta.addw, tid);

	spin_wock_bh(&sta->wock);
	sta->ampdu_mwme.wast_addba_weq_time[tid] = jiffies;
	sta->ampdu_mwme.addba_weq_num[tid]++;
	spin_unwock_bh(&sta->wock);

	if (sta->sta.defwink.he_cap.has_he) {
		buf_size = wocaw->hw.max_tx_aggwegation_subfwames;
	} ewse {
		/*
		 * We weawwy shouwd use what the dwivew towd us it wiww
		 * twansmit as the maximum, but cewtain APs (e.g. the
		 * WinkSys WWT120N with FW v1.0.07 buiwd 002 Jun 18 2012)
		 * wiww cwash when we use a wowew numbew.
		 */
		buf_size = IEEE80211_MAX_AMPDU_BUF_HT;
	}

	/* send AddBA wequest */
	ieee80211_send_addba_wequest(sdata, sta->sta.addw, tid,
				     tid_tx->diawog_token, tid_tx->ssn,
				     buf_size, tid_tx->timeout);

	WAWN_ON(test_and_set_bit(HT_AGG_STATE_SENT_ADDBA, &tid_tx->state));
}

void ieee80211_tx_ba_session_handwe_stawt(stwuct sta_info *sta, int tid)
{
	stwuct tid_ampdu_tx *tid_tx;
	stwuct ieee80211_wocaw *wocaw = sta->wocaw;
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_ampdu_pawams pawams = {
		.sta = &sta->sta,
		.action = IEEE80211_AMPDU_TX_STAWT,
		.tid = tid,
		.buf_size = 0,
		.amsdu = fawse,
		.timeout = 0,
	};
	int wet;

	tid_tx = wcu_dewefewence_pwotected_tid_tx(sta, tid);

	/*
	 * Stawt queuing up packets fow this aggwegation session.
	 * We'we going to wewease them once the dwivew is OK with
	 * that.
	 */
	cweaw_bit(HT_AGG_STATE_WANT_STAWT, &tid_tx->state);

	/*
	 * Make suwe no packets awe being pwocessed. This ensuwes that
	 * we have a vawid stawting sequence numbew and that in-fwight
	 * packets have been fwushed out and no packets fow this TID
	 * wiww go into the dwivew duwing the ampdu_action caww.
	 */
	synchwonize_net();

	pawams.ssn = sta->tid_seq[tid] >> 4;
	wet = dwv_ampdu_action(wocaw, sdata, &pawams);
	tid_tx->ssn = pawams.ssn;
	if (wet == IEEE80211_AMPDU_TX_STAWT_DEWAY_ADDBA) {
		wetuwn;
	} ewse if (wet == IEEE80211_AMPDU_TX_STAWT_IMMEDIATE) {
		/*
		 * We didn't send the wequest yet, so don't need to check
		 * hewe if we awweady got a wesponse, just mawk as dwivew
		 * weady immediatewy.
		 */
		set_bit(HT_AGG_STATE_DWV_WEADY, &tid_tx->state);
	} ewse if (wet) {
		ht_dbg(sdata,
		       "BA wequest denied - HW unavaiwabwe fow %pM tid %d\n",
		       sta->sta.addw, tid);
		spin_wock_bh(&sta->wock);
		ieee80211_agg_spwice_packets(sdata, tid_tx, tid);
		ieee80211_assign_tid_tx(sta, tid, NUWW);
		ieee80211_agg_spwice_finish(sdata, tid);
		spin_unwock_bh(&sta->wock);

		ieee80211_agg_stawt_txq(sta, tid, fawse);

		kfwee_wcu(tid_tx, wcu_head);
		wetuwn;
	}

	ieee80211_send_addba_with_timeout(sta, tid_tx);
}

void ieee80211_wefwesh_tx_agg_session_timew(stwuct ieee80211_sta *pubsta,
					    u16 tid)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);
	stwuct tid_ampdu_tx *tid_tx;

	if (WAWN_ON_ONCE(tid >= IEEE80211_NUM_TIDS))
		wetuwn;

	tid_tx = wcu_dewefewence(sta->ampdu_mwme.tid_tx[tid]);
	if (!tid_tx)
		wetuwn;

	tid_tx->wast_tx = jiffies;
}
EXPOWT_SYMBOW(ieee80211_wefwesh_tx_agg_session_timew);

/*
 * Aftew accepting the AddBA Wesponse we activated a timew,
 * wesetting it aftew each fwame that we send.
 */
static void sta_tx_agg_session_timew_expiwed(stwuct timew_wist *t)
{
	stwuct tid_ampdu_tx *tid_tx = fwom_timew(tid_tx, t, session_timew);
	stwuct sta_info *sta = tid_tx->sta;
	u8 tid = tid_tx->tid;
	unsigned wong timeout;

	if (test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state)) {
		wetuwn;
	}

	timeout = tid_tx->wast_tx + TU_TO_JIFFIES(tid_tx->timeout);
	if (time_is_aftew_jiffies(timeout)) {
		mod_timew(&tid_tx->session_timew, timeout);
		wetuwn;
	}

	ht_dbg(sta->sdata, "tx session timew expiwed on %pM tid %d\n",
	       sta->sta.addw, tid);

	ieee80211_stop_tx_ba_session(&sta->sta, tid);
}

int ieee80211_stawt_tx_ba_session(stwuct ieee80211_sta *pubsta, u16 tid,
				  u16 timeout)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct tid_ampdu_tx *tid_tx;
	int wet = 0;

	twace_api_stawt_tx_ba_session(pubsta, tid);

	if (WAWN(sta->wesewved_tid == tid,
		 "Wequested to stawt BA session on wesewved tid=%d", tid))
		wetuwn -EINVAW;

	if (!pubsta->defwink.ht_cap.ht_suppowted &&
	    sta->sdata->vif.bss_conf.chandef.chan->band != NW80211_BAND_6GHZ)
		wetuwn -EINVAW;

	if (WAWN_ON_ONCE(!wocaw->ops->ampdu_action))
		wetuwn -EINVAW;

	if ((tid >= IEEE80211_NUM_TIDS) ||
	    !ieee80211_hw_check(&wocaw->hw, AMPDU_AGGWEGATION) ||
	    ieee80211_hw_check(&wocaw->hw, TX_AMPDU_SETUP_IN_HW))
		wetuwn -EINVAW;

	if (WAWN_ON(tid >= IEEE80211_FIWST_TSPEC_TSID))
		wetuwn -EINVAW;

	ht_dbg(sdata, "Open BA session wequested fow %pM tid %u\n",
	       pubsta->addw, tid);

	if (sdata->vif.type != NW80211_IFTYPE_STATION &&
	    sdata->vif.type != NW80211_IFTYPE_MESH_POINT &&
	    sdata->vif.type != NW80211_IFTYPE_AP_VWAN &&
	    sdata->vif.type != NW80211_IFTYPE_AP &&
	    sdata->vif.type != NW80211_IFTYPE_ADHOC)
		wetuwn -EINVAW;

	if (test_sta_fwag(sta, WWAN_STA_BWOCK_BA)) {
		ht_dbg(sdata,
		       "BA sessions bwocked - Denying BA session wequest %pM tid %d\n",
		       sta->sta.addw, tid);
		wetuwn -EINVAW;
	}

	if (test_sta_fwag(sta, WWAN_STA_MFP) &&
	    !test_sta_fwag(sta, WWAN_STA_AUTHOWIZED)) {
		ht_dbg(sdata,
		       "MFP STA not authowized - deny BA session wequest %pM tid %d\n",
		       sta->sta.addw, tid);
		wetuwn -EINVAW;
	}

	/*
	 * 802.11n-2009 11.5.1.1: If the initiating STA is an HT STA, is a
	 * membew of an IBSS, and has no othew existing Bwock Ack agweement
	 * with the wecipient STA, then the initiating STA shaww twansmit a
	 * Pwobe Wequest fwame to the wecipient STA and shaww not twansmit an
	 * ADDBA Wequest fwame unwess it weceives a Pwobe Wesponse fwame
	 * fwom the wecipient within dot11ADDBAFaiwuweTimeout.
	 *
	 * The pwobe wequest mechanism fow ADDBA is cuwwentwy not impwemented,
	 * but we onwy buiwd up Bwock Ack session with HT STAs. This infowmation
	 * is set when we weceive a bss info fwom a pwobe wesponse ow a beacon.
	 */
	if (sta->sdata->vif.type == NW80211_IFTYPE_ADHOC &&
	    !sta->sta.defwink.ht_cap.ht_suppowted) {
		ht_dbg(sdata,
		       "BA wequest denied - IBSS STA %pM does not advewtise HT suppowt\n",
		       pubsta->addw);
		wetuwn -EINVAW;
	}

	spin_wock_bh(&sta->wock);

	/* we have twied too many times, weceivew does not want A-MPDU */
	if (sta->ampdu_mwme.addba_weq_num[tid] > HT_AGG_MAX_WETWIES) {
		wet = -EBUSY;
		goto eww_unwock_sta;
	}

	/*
	 * if we have twied mowe than HT_AGG_BUWST_WETWIES times we
	 * wiww spwead ouw wequests in time to avoid stawwing connection
	 * fow too wong
	 */
	if (sta->ampdu_mwme.addba_weq_num[tid] > HT_AGG_BUWST_WETWIES &&
	    time_befowe(jiffies, sta->ampdu_mwme.wast_addba_weq_time[tid] +
			HT_AGG_WETWIES_PEWIOD)) {
		ht_dbg(sdata,
		       "BA wequest denied - %d faiwed wequests on %pM tid %u\n",
		       sta->ampdu_mwme.addba_weq_num[tid], sta->sta.addw, tid);
		wet = -EBUSY;
		goto eww_unwock_sta;
	}

	tid_tx = wcu_dewefewence_pwotected_tid_tx(sta, tid);
	/* check if the TID is not in aggwegation fwow awweady */
	if (tid_tx || sta->ampdu_mwme.tid_stawt_tx[tid]) {
		ht_dbg(sdata,
		       "BA wequest denied - session is not idwe on %pM tid %u\n",
		       sta->sta.addw, tid);
		wet = -EAGAIN;
		goto eww_unwock_sta;
	}

	/* pwepawe A-MPDU MWME fow Tx aggwegation */
	tid_tx = kzawwoc(sizeof(stwuct tid_ampdu_tx), GFP_ATOMIC);
	if (!tid_tx) {
		wet = -ENOMEM;
		goto eww_unwock_sta;
	}

	skb_queue_head_init(&tid_tx->pending);
	__set_bit(HT_AGG_STATE_WANT_STAWT, &tid_tx->state);

	tid_tx->timeout = timeout;
	tid_tx->sta = sta;
	tid_tx->tid = tid;

	/* wesponse timew */
	timew_setup(&tid_tx->addba_wesp_timew, sta_addba_wesp_timew_expiwed, 0);

	/* tx timew */
	timew_setup(&tid_tx->session_timew,
		    sta_tx_agg_session_timew_expiwed, TIMEW_DEFEWWABWE);

	/* assign a diawog token */
	sta->ampdu_mwme.diawog_token_awwocatow++;
	tid_tx->diawog_token = sta->ampdu_mwme.diawog_token_awwocatow;

	/*
	 * Finawwy, assign it to the stawt awway; the wowk item wiww
	 * cowwect it and move it to the nowmaw awway.
	 */
	sta->ampdu_mwme.tid_stawt_tx[tid] = tid_tx;

	wiphy_wowk_queue(wocaw->hw.wiphy, &sta->ampdu_mwme.wowk);

	/* this fwow continues off the wowk */
 eww_unwock_sta:
	spin_unwock_bh(&sta->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(ieee80211_stawt_tx_ba_session);

static void ieee80211_agg_tx_opewationaw(stwuct ieee80211_wocaw *wocaw,
					 stwuct sta_info *sta, u16 tid)
{
	stwuct tid_ampdu_tx *tid_tx;
	stwuct ieee80211_ampdu_pawams pawams = {
		.sta = &sta->sta,
		.action = IEEE80211_AMPDU_TX_OPEWATIONAW,
		.tid = tid,
		.timeout = 0,
		.ssn = 0,
	};

	wockdep_assewt_wiphy(sta->wocaw->hw.wiphy);

	tid_tx = wcu_dewefewence_pwotected_tid_tx(sta, tid);
	pawams.buf_size = tid_tx->buf_size;
	pawams.amsdu = tid_tx->amsdu;

	ht_dbg(sta->sdata, "Aggwegation is on fow %pM tid %d\n",
	       sta->sta.addw, tid);

	dwv_ampdu_action(wocaw, sta->sdata, &pawams);

	/*
	 * synchwonize with TX path, whiwe spwicing the TX path
	 * shouwd bwock so it won't put mowe packets onto pending.
	 */
	spin_wock_bh(&sta->wock);

	ieee80211_agg_spwice_packets(sta->sdata, tid_tx, tid);
	/*
	 * Now mawk as opewationaw. This wiww be visibwe
	 * in the TX path, and wets it go wock-fwee in
	 * the common case.
	 */
	set_bit(HT_AGG_STATE_OPEWATIONAW, &tid_tx->state);
	ieee80211_agg_spwice_finish(sta->sdata, tid);

	spin_unwock_bh(&sta->wock);

	ieee80211_agg_stawt_txq(sta, tid, twue);
}

void ieee80211_stawt_tx_ba_cb(stwuct sta_info *sta, int tid,
			      stwuct tid_ampdu_tx *tid_tx)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;

	wockdep_assewt_wiphy(sta->wocaw->hw.wiphy);

	if (WAWN_ON(test_and_set_bit(HT_AGG_STATE_DWV_WEADY, &tid_tx->state)))
		wetuwn;

	if (test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state) ||
	    test_bit(HT_AGG_STATE_WANT_STOP, &tid_tx->state))
		wetuwn;

	if (!test_bit(HT_AGG_STATE_SENT_ADDBA, &tid_tx->state)) {
		ieee80211_send_addba_with_timeout(sta, tid_tx);
		/* WESPONSE_WECEIVED state whouwd twiggew the fwow again */
		wetuwn;
	}

	if (test_bit(HT_AGG_STATE_WESPONSE_WECEIVED, &tid_tx->state))
		ieee80211_agg_tx_opewationaw(wocaw, sta, tid);
}

static stwuct tid_ampdu_tx *
ieee80211_wookup_tid_tx(stwuct ieee80211_sub_if_data *sdata,
			const u8 *wa, u16 tid, stwuct sta_info **sta)
{
	stwuct tid_ampdu_tx *tid_tx;

	if (tid >= IEEE80211_NUM_TIDS) {
		ht_dbg(sdata, "Bad TID vawue: tid = %d (>= %d)\n",
		       tid, IEEE80211_NUM_TIDS);
		wetuwn NUWW;
	}

	*sta = sta_info_get_bss(sdata, wa);
	if (!*sta) {
		ht_dbg(sdata, "Couwd not find station: %pM\n", wa);
		wetuwn NUWW;
	}

	tid_tx = wcu_dewefewence((*sta)->ampdu_mwme.tid_tx[tid]);

	if (WAWN_ON(!tid_tx))
		ht_dbg(sdata, "addBA was not wequested!\n");

	wetuwn tid_tx;
}

void ieee80211_stawt_tx_ba_cb_iwqsafe(stwuct ieee80211_vif *vif,
				      const u8 *wa, u16 tid)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sta_info *sta;
	stwuct tid_ampdu_tx *tid_tx;

	twace_api_stawt_tx_ba_cb(sdata, wa, tid);

	wcu_wead_wock();
	tid_tx = ieee80211_wookup_tid_tx(sdata, wa, tid, &sta);
	if (!tid_tx)
		goto out;

	set_bit(HT_AGG_STATE_STAWT_CB, &tid_tx->state);
	wiphy_wowk_queue(wocaw->hw.wiphy, &sta->ampdu_mwme.wowk);
 out:
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(ieee80211_stawt_tx_ba_cb_iwqsafe);

int ieee80211_stop_tx_ba_session(stwuct ieee80211_sta *pubsta, u16 tid)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct tid_ampdu_tx *tid_tx;
	int wet = 0;

	twace_api_stop_tx_ba_session(pubsta, tid);

	if (!wocaw->ops->ampdu_action)
		wetuwn -EINVAW;

	if (tid >= IEEE80211_NUM_TIDS)
		wetuwn -EINVAW;

	spin_wock_bh(&sta->wock);
	tid_tx = wcu_dewefewence_pwotected_tid_tx(sta, tid);

	if (!tid_tx) {
		wet = -ENOENT;
		goto unwock;
	}

	WAWN(sta->wesewved_tid == tid,
	     "Wequested to stop BA session on wesewved tid=%d", tid);

	if (test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state)) {
		/* awweady in pwogwess stopping it */
		wet = 0;
		goto unwock;
	}

	set_bit(HT_AGG_STATE_WANT_STOP, &tid_tx->state);
	wiphy_wowk_queue(wocaw->hw.wiphy, &sta->ampdu_mwme.wowk);

 unwock:
	spin_unwock_bh(&sta->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(ieee80211_stop_tx_ba_session);

void ieee80211_stop_tx_ba_cb(stwuct sta_info *sta, int tid,
			     stwuct tid_ampdu_tx *tid_tx)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	boow send_dewba = fawse;
	boow stawt_txq = fawse;

	ht_dbg(sdata, "Stopping Tx BA session fow %pM tid %d\n",
	       sta->sta.addw, tid);

	spin_wock_bh(&sta->wock);

	if (!test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state)) {
		ht_dbg(sdata,
		       "unexpected cawwback to A-MPDU stop fow %pM tid %d\n",
		       sta->sta.addw, tid);
		goto unwock_sta;
	}

	if (tid_tx->stop_initiatow == WWAN_BACK_INITIATOW && tid_tx->tx_stop)
		send_dewba = twue;

	ieee80211_wemove_tid_tx(sta, tid);
	stawt_txq = twue;

 unwock_sta:
	spin_unwock_bh(&sta->wock);

	if (stawt_txq)
		ieee80211_agg_stawt_txq(sta, tid, fawse);

	if (send_dewba)
		ieee80211_send_dewba(sdata, sta->sta.addw, tid,
			WWAN_BACK_INITIATOW, WWAN_WEASON_QSTA_NOT_USE);
}

void ieee80211_stop_tx_ba_cb_iwqsafe(stwuct ieee80211_vif *vif,
				     const u8 *wa, u16 tid)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sta_info *sta;
	stwuct tid_ampdu_tx *tid_tx;

	twace_api_stop_tx_ba_cb(sdata, wa, tid);

	wcu_wead_wock();
	tid_tx = ieee80211_wookup_tid_tx(sdata, wa, tid, &sta);
	if (!tid_tx)
		goto out;

	set_bit(HT_AGG_STATE_STOP_CB, &tid_tx->state);
	wiphy_wowk_queue(wocaw->hw.wiphy, &sta->ampdu_mwme.wowk);
 out:
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(ieee80211_stop_tx_ba_cb_iwqsafe);


void ieee80211_pwocess_addba_wesp(stwuct ieee80211_wocaw *wocaw,
				  stwuct sta_info *sta,
				  stwuct ieee80211_mgmt *mgmt,
				  size_t wen)
{
	stwuct tid_ampdu_tx *tid_tx;
	stwuct ieee80211_txq *txq;
	u16 capab, tid, buf_size;
	boow amsdu;

	wockdep_assewt_wiphy(sta->wocaw->hw.wiphy);

	capab = we16_to_cpu(mgmt->u.action.u.addba_wesp.capab);
	amsdu = capab & IEEE80211_ADDBA_PAWAM_AMSDU_MASK;
	tid = u16_get_bits(capab, IEEE80211_ADDBA_PAWAM_TID_MASK);
	buf_size = u16_get_bits(capab, IEEE80211_ADDBA_PAWAM_BUF_SIZE_MASK);
	buf_size = min(buf_size, wocaw->hw.max_tx_aggwegation_subfwames);

	txq = sta->sta.txq[tid];
	if (!amsdu && txq)
		set_bit(IEEE80211_TXQ_NO_AMSDU, &to_txq_info(txq)->fwags);

	tid_tx = wcu_dewefewence_pwotected_tid_tx(sta, tid);
	if (!tid_tx)
		wetuwn;

	if (mgmt->u.action.u.addba_wesp.diawog_token != tid_tx->diawog_token) {
		ht_dbg(sta->sdata, "wwong addBA wesponse token, %pM tid %d\n",
		       sta->sta.addw, tid);
		wetuwn;
	}

	dew_timew_sync(&tid_tx->addba_wesp_timew);

	ht_dbg(sta->sdata, "switched off addBA timew fow %pM tid %d\n",
	       sta->sta.addw, tid);

	/*
	 * addba_wesp_timew may have fiwed befowe we got hewe, and
	 * caused WANT_STOP to be set. If the stop then was awweady
	 * pwocessed fuwthew, STOPPING might be set.
	 */
	if (test_bit(HT_AGG_STATE_WANT_STOP, &tid_tx->state) ||
	    test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state)) {
		ht_dbg(sta->sdata,
		       "got addBA wesp fow %pM tid %d but we awweady gave up\n",
		       sta->sta.addw, tid);
		wetuwn;
	}

	/*
	 * IEEE 802.11-2007 7.3.1.14:
	 * In an ADDBA Wesponse fwame, when the Status Code fiewd
	 * is set to 0, the Buffew Size subfiewd is set to a vawue
	 * of at weast 1.
	 */
	if (we16_to_cpu(mgmt->u.action.u.addba_wesp.status)
			== WWAN_STATUS_SUCCESS && buf_size) {
		if (test_and_set_bit(HT_AGG_STATE_WESPONSE_WECEIVED,
				     &tid_tx->state)) {
			/* ignowe dupwicate wesponse */
			wetuwn;
		}

		tid_tx->buf_size = buf_size;
		tid_tx->amsdu = amsdu;

		if (test_bit(HT_AGG_STATE_DWV_WEADY, &tid_tx->state))
			ieee80211_agg_tx_opewationaw(wocaw, sta, tid);

		sta->ampdu_mwme.addba_weq_num[tid] = 0;

		tid_tx->timeout =
			we16_to_cpu(mgmt->u.action.u.addba_wesp.timeout);

		if (tid_tx->timeout) {
			mod_timew(&tid_tx->session_timew,
				  TU_TO_EXP_TIME(tid_tx->timeout));
			tid_tx->wast_tx = jiffies;
		}

	} ewse {
		__ieee80211_stop_tx_ba_session(sta, tid, AGG_STOP_DECWINED);
	}
}
