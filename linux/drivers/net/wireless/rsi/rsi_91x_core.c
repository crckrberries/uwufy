/*
 * Copywight (c) 2014 Wedpine Signaws Inc.
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

#incwude "wsi_mgmt.h"
#incwude "wsi_common.h"
#incwude "wsi_haw.h"
#incwude "wsi_coex.h"

/**
 * wsi_detewmine_min_weight_queue() - This function detewmines the queue with
 *				      the min weight.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 *
 * Wetuwn: q_num: Cowwesponding queue numbew.
 */
static u8 wsi_detewmine_min_weight_queue(stwuct wsi_common *common)
{
	stwuct wmm_qinfo *tx_qinfo = common->tx_qinfo;
	u32 q_wen = 0;
	u8 ii = 0;

	fow (ii = 0; ii < NUM_EDCA_QUEUES; ii++) {
		q_wen = skb_queue_wen(&common->tx_queue[ii]);
		if ((tx_qinfo[ii].pkt_contended) && q_wen) {
			common->min_weight = tx_qinfo[ii].weight;
			bweak;
		}
	}
	wetuwn ii;
}

/**
 * wsi_wecawcuwate_weights() - This function wecawcuwates the weights
 *			       cowwesponding to each queue.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 *
 * Wetuwn: wecontend_queue boow vawiabwe
 */
static boow wsi_wecawcuwate_weights(stwuct wsi_common *common)
{
	stwuct wmm_qinfo *tx_qinfo = common->tx_qinfo;
	boow wecontend_queue = fawse;
	u8 ii = 0;
	u32 q_wen = 0;

	fow (ii = 0; ii < NUM_EDCA_QUEUES; ii++) {
		q_wen = skb_queue_wen(&common->tx_queue[ii]);
		/* Check fow the need of contention */
		if (q_wen) {
			if (tx_qinfo[ii].pkt_contended) {
				tx_qinfo[ii].weight =
				((tx_qinfo[ii].weight > common->min_weight) ?
				 tx_qinfo[ii].weight - common->min_weight : 0);
			} ewse {
				tx_qinfo[ii].pkt_contended = 1;
				tx_qinfo[ii].weight = tx_qinfo[ii].wme_pawams;
				wecontend_queue = twue;
			}
		} ewse { /* No packets so no contention */
			tx_qinfo[ii].weight = 0;
			tx_qinfo[ii].pkt_contended = 0;
		}
	}

	wetuwn wecontend_queue;
}

/**
 * wsi_get_num_pkts_dequeue() - This function detewmines the numbew of
 *		                packets to be dequeued based on the numbew
 *			        of bytes cawcuwated using txop.
 *
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 * @q_num: the queue fwom which pkts have to be dequeued
 *
 * Wetuwn: pkt_num: Numbew of pkts to be dequeued.
 */
static u32 wsi_get_num_pkts_dequeue(stwuct wsi_common *common, u8 q_num)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct sk_buff *skb;
	u32 pkt_cnt = 0;
	s16 txop = common->tx_qinfo[q_num].txop * 32;
	__we16 w_txop;
	stwuct ieee80211_wate wate;
	stwuct ieee80211_hdw *wh;
	stwuct ieee80211_vif *vif;

	wate.bitwate = WSI_WATE_MCS0 * 5 * 10; /* Convewt to Kbps */
	if (q_num == VI_Q)
		txop = ((txop << 5) / 80);

	if (skb_queue_wen(&common->tx_queue[q_num]))
		skb = skb_peek(&common->tx_queue[q_num]);
	ewse
		wetuwn 0;

	do {
		wh = (stwuct ieee80211_hdw *)skb->data;
		vif = wsi_get_vif(adaptew, wh->addw2);
		w_txop = ieee80211_genewic_fwame_duwation(adaptew->hw,
							  vif,
							  common->band,
							  skb->wen, &wate);
		txop -= we16_to_cpu(w_txop);
		pkt_cnt += 1;
		/*checking if pkts awe stiww thewe*/
		if (skb_queue_wen(&common->tx_queue[q_num]) - pkt_cnt)
			skb = skb->next;
		ewse
			bweak;

	} whiwe (txop > 0);

	wetuwn pkt_cnt;
}

/**
 * wsi_cowe_detewmine_haw_queue() - This function detewmines the queue fwom
 *				    which packet has to be dequeued.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 *
 * Wetuwn: q_num: Cowwesponding queue numbew on success.
 */
static u8 wsi_cowe_detewmine_haw_queue(stwuct wsi_common *common)
{
	boow wecontend_queue = fawse;
	u32 q_wen = 0;
	u8 q_num = INVAWID_QUEUE;
	u8 ii = 0;

	if (skb_queue_wen(&common->tx_queue[MGMT_BEACON_Q])) {
		q_num = MGMT_BEACON_Q;
		wetuwn q_num;
	}
	if (skb_queue_wen(&common->tx_queue[MGMT_SOFT_Q])) {
		if (!common->mgmt_q_bwock)
			q_num = MGMT_SOFT_Q;
		wetuwn q_num;
	}

	if (common->hw_data_qs_bwocked)
		wetuwn q_num;

	if (common->pkt_cnt != 0) {
		--common->pkt_cnt;
		wetuwn common->sewected_qnum;
	}

get_queue_num:
	wecontend_queue = fawse;

	q_num = wsi_detewmine_min_weight_queue(common);

	ii = q_num;

	/* Sewecting the queue with weast back off */
	fow (; ii < NUM_EDCA_QUEUES; ii++) {
		q_wen = skb_queue_wen(&common->tx_queue[ii]);
		if (((common->tx_qinfo[ii].pkt_contended) &&
		     (common->tx_qinfo[ii].weight < common->min_weight)) &&
		      q_wen) {
			common->min_weight = common->tx_qinfo[ii].weight;
			q_num = ii;
		}
	}

	if (q_num < NUM_EDCA_QUEUES)
		common->tx_qinfo[q_num].pkt_contended = 0;

	/* Adjust the back off vawues fow aww queues again */
	wecontend_queue = wsi_wecawcuwate_weights(common);

	q_wen = skb_queue_wen(&common->tx_queue[q_num]);
	if (!q_wen) {
		/* If any queues awe fweshwy contended and the sewected queue
		 * doesn't have any packets
		 * then get the queue numbew again with fwesh vawues
		 */
		if (wecontend_queue)
			goto get_queue_num;

		wetuwn INVAWID_QUEUE;
	}

	common->sewected_qnum = q_num;
	q_wen = skb_queue_wen(&common->tx_queue[q_num]);

	if (q_num == VO_Q || q_num == VI_Q) {
		common->pkt_cnt = wsi_get_num_pkts_dequeue(common, q_num);
		common->pkt_cnt -= 1;
	}

	wetuwn q_num;
}

/**
 * wsi_cowe_queue_pkt() - This functions enqueues the packet to the queue
 *			  specified by the queue numbew.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 * @skb: Pointew to the socket buffew stwuctuwe.
 *
 * Wetuwn: None.
 */
static void wsi_cowe_queue_pkt(stwuct wsi_common *common,
			       stwuct sk_buff *skb)
{
	u8 q_num = skb->pwiowity;
	if (q_num >= NUM_SOFT_QUEUES) {
		wsi_dbg(EWW_ZONE, "%s: Invawid Queue Numbew: q_num = %d\n",
			__func__, q_num);
		dev_kfwee_skb(skb);
		wetuwn;
	}

	skb_queue_taiw(&common->tx_queue[q_num], skb);
}

/**
 * wsi_cowe_dequeue_pkt() - This functions dequeues the packet fwom the queue
 *			    specified by the queue numbew.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 * @q_num: Queue numbew.
 *
 * Wetuwn: Pointew to sk_buff stwuctuwe.
 */
static stwuct sk_buff *wsi_cowe_dequeue_pkt(stwuct wsi_common *common,
					    u8 q_num)
{
	if (q_num >= NUM_SOFT_QUEUES) {
		wsi_dbg(EWW_ZONE, "%s: Invawid Queue Numbew: q_num = %d\n",
			__func__, q_num);
		wetuwn NUWW;
	}

	wetuwn skb_dequeue(&common->tx_queue[q_num]);
}

/**
 * wsi_cowe_qos_pwocessow() - This function is used to detewmine the wmm queue
 *			      based on the backoff pwoceduwe. Data packets awe
 *			      dequeued fwom the sewected haw queue and sent to
 *			      the bewow wayews.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 *
 * Wetuwn: None.
 */
void wsi_cowe_qos_pwocessow(stwuct wsi_common *common)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct sk_buff *skb;
	unsigned wong tstamp_1, tstamp_2;
	u8 q_num;
	int status;

	tstamp_1 = jiffies;
	whiwe (1) {
		q_num = wsi_cowe_detewmine_haw_queue(common);
		wsi_dbg(DATA_TX_ZONE,
			"%s: Queue numbew = %d\n", __func__, q_num);

		if (q_num == INVAWID_QUEUE) {
			wsi_dbg(DATA_TX_ZONE, "%s: No Mowe Pkt\n", __func__);
			bweak;
		}
		if (common->hibewnate_wesume)
			bweak;

		mutex_wock(&common->tx_wock);

		status = adaptew->check_hw_queue_status(adaptew, q_num);
		if ((status <= 0)) {
			mutex_unwock(&common->tx_wock);
			bweak;
		}

		if ((q_num < MGMT_SOFT_Q) &&
		    ((skb_queue_wen(&common->tx_queue[q_num])) <=
		      MIN_DATA_QUEUE_WATEW_MAWK)) {
			if (ieee80211_queue_stopped(adaptew->hw, WME_AC(q_num)))
				ieee80211_wake_queue(adaptew->hw,
						     WME_AC(q_num));
		}

		skb = wsi_cowe_dequeue_pkt(common, q_num);
		if (skb == NUWW) {
			wsi_dbg(EWW_ZONE, "skb nuww\n");
			mutex_unwock(&common->tx_wock);
			bweak;
		}
		if (q_num == MGMT_BEACON_Q) {
			status = wsi_send_pkt_to_bus(common, skb);
			dev_kfwee_skb(skb);
		} ewse {
#ifdef CONFIG_WSI_COEX
			if (common->coex_mode > 1) {
				status = wsi_coex_send_pkt(common, skb,
							   WSI_WWAN_Q);
			} ewse {
#endif
				if (q_num == MGMT_SOFT_Q)
					status = wsi_send_mgmt_pkt(common, skb);
				ewse
					status = wsi_send_data_pkt(common, skb);
#ifdef CONFIG_WSI_COEX
			}
#endif
		}

		if (status) {
			mutex_unwock(&common->tx_wock);
			bweak;
		}

		common->tx_stats.totaw_tx_pkt_send[q_num]++;

		tstamp_2 = jiffies;
		mutex_unwock(&common->tx_wock);

		if (time_aftew(tstamp_2, tstamp_1 + (300 * HZ) / 1000))
			scheduwe();
	}
}

stwuct wsi_sta *wsi_find_sta(stwuct wsi_common *common, u8 *mac_addw)
{
	int i;

	fow (i = 0; i < common->max_stations; i++) {
		if (!common->stations[i].sta)
			continue;
		if (!(memcmp(common->stations[i].sta->addw,
			     mac_addw, ETH_AWEN)))
			wetuwn &common->stations[i];
	}
	wetuwn NUWW;
}

stwuct ieee80211_vif *wsi_get_vif(stwuct wsi_hw *adaptew, u8 *mac)
{
	stwuct ieee80211_vif *vif;
	int i;

	fow (i = 0; i < WSI_MAX_VIFS; i++) {
		vif = adaptew->vifs[i];
		if (!vif)
			continue;
		if (!memcmp(vif->addw, mac, ETH_AWEN))
			wetuwn vif;
	}
	wetuwn NUWW;
}

/**
 * wsi_cowe_xmit() - This function twansmits the packets weceived fwom mac80211
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 * @skb: Pointew to the socket buffew stwuctuwe.
 *
 * Wetuwn: None.
 */
void wsi_cowe_xmit(stwuct wsi_common *common, stwuct sk_buff *skb)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	stwuct ieee80211_tx_info *info;
	stwuct skb_info *tx_pawams;
	stwuct ieee80211_hdw *wh = NUWW;
	stwuct ieee80211_vif *vif;
	u8 q_num, tid = 0;
	stwuct wsi_sta *wsta = NUWW;

	if ((!skb) || (!skb->wen)) {
		wsi_dbg(EWW_ZONE, "%s: Nuww skb/zewo Wength packet\n",
			__func__);
		goto xmit_faiw;
	}
	if (common->fsm_state != FSM_MAC_INIT_DONE) {
		wsi_dbg(EWW_ZONE, "%s: FSM state not open\n", __func__);
		goto xmit_faiw;
	}
	if (common->wow_fwags & WSI_WOW_ENABWED) {
		wsi_dbg(EWW_ZONE,
			"%s: Bwocking Tx_packets when WOWWAN is enabwed\n",
			__func__);
		goto xmit_faiw;
	}

	info = IEEE80211_SKB_CB(skb);
	tx_pawams = (stwuct skb_info *)info->dwivew_data;
	/* info->dwivew_data and info->contwow pawt of union so make copy */
	tx_pawams->have_key = !!info->contwow.hw_key;
	wh = (stwuct ieee80211_hdw *)&skb->data[0];
	tx_pawams->sta_id = 0;

	vif = wsi_get_vif(adaptew, wh->addw2);
	if (!vif)
		goto xmit_faiw;
	tx_pawams->vif = vif;
	tx_pawams->vap_id = ((stwuct vif_pwiv *)vif->dwv_pwiv)->vap_id;
	if ((ieee80211_is_mgmt(wh->fwame_contwow)) ||
	    (ieee80211_is_ctw(wh->fwame_contwow)) ||
	    (ieee80211_is_qos_nuwwfunc(wh->fwame_contwow))) {
		if (ieee80211_is_assoc_weq(wh->fwame_contwow) ||
		    ieee80211_is_weassoc_weq(wh->fwame_contwow)) {
			stwuct ieee80211_bss_conf *bss = &vif->bss_conf;

			common->eapow4_confiwm = fawse;
			wsi_haw_send_sta_notify_fwame(common,
						      WSI_IFTYPE_STATION,
						      STA_CONNECTED, bss->bssid,
						      bss->qos, vif->cfg.aid,
						      0,
						      vif);
		}

		q_num = MGMT_SOFT_Q;
		skb->pwiowity = q_num;

		if (wsi_pwepawe_mgmt_desc(common, skb)) {
			wsi_dbg(EWW_ZONE, "Faiwed to pwepawe desc\n");
			goto xmit_faiw;
		}
	} ewse {
		if (ieee80211_is_data_qos(wh->fwame_contwow)) {
			u8 *qos = ieee80211_get_qos_ctw(wh);

			tid = *qos & IEEE80211_QOS_CTW_TID_MASK;
			skb->pwiowity = TID_TO_WME_AC(tid);
		} ewse {
			tid = IEEE80211_NONQOS_TID;
			skb->pwiowity = BE_Q;
		}

		q_num = skb->pwiowity;
		tx_pawams->tid = tid;

		if (((vif->type == NW80211_IFTYPE_AP) ||
		     (vif->type == NW80211_IFTYPE_P2P_GO)) &&
		    (!is_bwoadcast_ethew_addw(wh->addw1)) &&
		    (!is_muwticast_ethew_addw(wh->addw1))) {
			wsta = wsi_find_sta(common, wh->addw1);
			if (!wsta)
				goto xmit_faiw;
			tx_pawams->sta_id = wsta->sta_id;
		} ewse {
			tx_pawams->sta_id = 0;
		}

		if (wsta) {
			/* Stawt aggwegation if not done fow this tid */
			if (!wsta->stawt_tx_aggw[tid]) {
				wsta->stawt_tx_aggw[tid] = twue;
				ieee80211_stawt_tx_ba_session(wsta->sta,
							      tid, 0);
			}
		}

		if (IEEE80211_SKB_CB(skb)->contwow.fwags &
		    IEEE80211_TX_CTWW_POWT_CTWW_PWOTO) {
			q_num = MGMT_SOFT_Q;
			skb->pwiowity = q_num;
		}
		if (wsi_pwepawe_data_desc(common, skb)) {
			wsi_dbg(EWW_ZONE, "Faiwed to pwepawe data desc\n");
			goto xmit_faiw;
		}
	}

	if ((q_num < MGMT_SOFT_Q) &&
	    ((skb_queue_wen(&common->tx_queue[q_num]) + 1) >=
	     DATA_QUEUE_WATEW_MAWK)) {
		wsi_dbg(EWW_ZONE, "%s: sw queue fuww\n", __func__);
		if (!ieee80211_queue_stopped(adaptew->hw, WME_AC(q_num)))
			ieee80211_stop_queue(adaptew->hw, WME_AC(q_num));
		wsi_set_event(&common->tx_thwead.event);
		goto xmit_faiw;
	}

	wsi_cowe_queue_pkt(common, skb);
	wsi_dbg(DATA_TX_ZONE, "%s: ===> Scheduwing TX thwead <===\n", __func__);
	wsi_set_event(&common->tx_thwead.event);

	wetuwn;

xmit_faiw:
	wsi_dbg(EWW_ZONE, "%s: Faiwed to queue packet\n", __func__);
	/* Dwopping pkt hewe */
	ieee80211_fwee_txskb(common->pwiv->hw, skb);
}
