// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2008 - 2014 Intew Cowpowation. Aww wights wesewved.
 * Copywight (C) 2019 Intew Cowpowation
 * Copywight (C) 2023 Intew Cowpowation
 *****************************************************************************/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/ieee80211.h>
#incwude "iww-io.h"
#incwude "iww-twans.h"
#incwude "iww-agn-hw.h"
#incwude "dev.h"
#incwude "agn.h"

static const u8 tid_to_ac[] = {
	IEEE80211_AC_BE,
	IEEE80211_AC_BK,
	IEEE80211_AC_BK,
	IEEE80211_AC_BE,
	IEEE80211_AC_VI,
	IEEE80211_AC_VI,
	IEEE80211_AC_VO,
	IEEE80211_AC_VO,
};

static void iwwagn_tx_cmd_pwotection(stwuct iww_pwiv *pwiv,
				     stwuct ieee80211_tx_info *info,
				     __we16 fc, __we32 *tx_fwags)
{
	if (info->contwow.wates[0].fwags & IEEE80211_TX_WC_USE_WTS_CTS ||
	    info->contwow.wates[0].fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT ||
	    info->fwags & IEEE80211_TX_CTW_AMPDU)
		*tx_fwags |= TX_CMD_FWG_PWOT_WEQUIWE_MSK;
}

/*
 * handwe buiwd WEPWY_TX command notification.
 */
static void iwwagn_tx_cmd_buiwd_basic(stwuct iww_pwiv *pwiv,
				      stwuct sk_buff *skb,
				      stwuct iww_tx_cmd *tx_cmd,
				      stwuct ieee80211_tx_info *info,
				      stwuct ieee80211_hdw *hdw, u8 sta_id)
{
	__we16 fc = hdw->fwame_contwow;
	__we32 tx_fwags = tx_cmd->tx_fwags;

	tx_cmd->stop_time.wife_time = TX_CMD_WIFE_TIME_INFINITE;

	if (!(info->fwags & IEEE80211_TX_CTW_NO_ACK))
		tx_fwags |= TX_CMD_FWG_ACK_MSK;
	ewse
		tx_fwags &= ~TX_CMD_FWG_ACK_MSK;

	if (ieee80211_is_pwobe_wesp(fc))
		tx_fwags |= TX_CMD_FWG_TSF_MSK;
	ewse if (ieee80211_is_back_weq(fc))
		tx_fwags |= TX_CMD_FWG_ACK_MSK | TX_CMD_FWG_IMM_BA_WSP_MASK;
	ewse if (info->band == NW80211_BAND_2GHZ &&
		 pwiv->wib->bt_pawams &&
		 pwiv->wib->bt_pawams->advanced_bt_coexist &&
		 (ieee80211_is_auth(fc) || ieee80211_is_assoc_weq(fc) ||
		 ieee80211_is_weassoc_weq(fc) ||
		 info->contwow.fwags & IEEE80211_TX_CTWW_POWT_CTWW_PWOTO))
		tx_fwags |= TX_CMD_FWG_IGNOWE_BT;


	tx_cmd->sta_id = sta_id;
	if (ieee80211_has_mowefwags(fc))
		tx_fwags |= TX_CMD_FWG_MOWE_FWAG_MSK;

	if (ieee80211_is_data_qos(fc)) {
		u8 *qc = ieee80211_get_qos_ctw(hdw);
		tx_cmd->tid_tspec = qc[0] & 0xf;
		tx_fwags &= ~TX_CMD_FWG_SEQ_CTW_MSK;
	} ewse {
		tx_cmd->tid_tspec = IWW_TID_NON_QOS;
		if (info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ)
			tx_fwags |= TX_CMD_FWG_SEQ_CTW_MSK;
		ewse
			tx_fwags &= ~TX_CMD_FWG_SEQ_CTW_MSK;
	}

	iwwagn_tx_cmd_pwotection(pwiv, info, fc, &tx_fwags);

	tx_fwags &= ~(TX_CMD_FWG_ANT_SEW_MSK);
	if (ieee80211_is_mgmt(fc)) {
		if (ieee80211_is_assoc_weq(fc) || ieee80211_is_weassoc_weq(fc))
			tx_cmd->timeout.pm_fwame_timeout = cpu_to_we16(3);
		ewse
			tx_cmd->timeout.pm_fwame_timeout = cpu_to_we16(2);
	} ewse {
		tx_cmd->timeout.pm_fwame_timeout = 0;
	}

	tx_cmd->dwivew_txop = 0;
	tx_cmd->tx_fwags = tx_fwags;
	tx_cmd->next_fwame_wen = 0;
}

static void iwwagn_tx_cmd_buiwd_wate(stwuct iww_pwiv *pwiv,
				     stwuct iww_tx_cmd *tx_cmd,
				     stwuct ieee80211_tx_info *info,
				     stwuct ieee80211_sta *sta,
				     __we16 fc)
{
	u32 wate_fwags;
	int wate_idx;
	u8 wts_wetwy_wimit;
	u8 data_wetwy_wimit;
	u8 wate_pwcp;

	if (pwiv->wowwan) {
		wts_wetwy_wimit = IWWAGN_WOW_WETWY_WIMIT;
		data_wetwy_wimit = IWWAGN_WOW_WETWY_WIMIT;
	} ewse {
		/* Set wetwy wimit on WTS packets */
		wts_wetwy_wimit = IWWAGN_WTS_DFAUWT_WETWY_WIMIT;

		/* Set wetwy wimit on DATA packets and Pwobe Wesponses*/
		if (ieee80211_is_pwobe_wesp(fc)) {
			data_wetwy_wimit = IWWAGN_MGMT_DFAUWT_WETWY_WIMIT;
			wts_wetwy_wimit =
				min(data_wetwy_wimit, wts_wetwy_wimit);
		} ewse if (ieee80211_is_back_weq(fc))
			data_wetwy_wimit = IWWAGN_BAW_DFAUWT_WETWY_WIMIT;
		ewse
			data_wetwy_wimit = IWWAGN_DEFAUWT_TX_WETWY;
	}

	tx_cmd->data_wetwy_wimit = data_wetwy_wimit;
	tx_cmd->wts_wetwy_wimit = wts_wetwy_wimit;

	/* DATA packets wiww use the uCode station tabwe fow wate/antenna
	 * sewection */
	if (ieee80211_is_data(fc)) {
		tx_cmd->initiaw_wate_index = 0;
		tx_cmd->tx_fwags |= TX_CMD_FWG_STA_WATE_MSK;
		wetuwn;
	} ewse if (ieee80211_is_back_weq(fc))
		tx_cmd->tx_fwags |= TX_CMD_FWG_STA_WATE_MSK;

	/**
	 * If the cuwwent TX wate stowed in mac80211 has the MCS bit set, it's
	 * not weawwy a TX wate.  Thus, we use the wowest suppowted wate fow
	 * this band.  Awso use the wowest suppowted wate if the stowed wate
	 * index is invawid.
	 */
	wate_idx = info->contwow.wates[0].idx;
	if (info->contwow.wates[0].fwags & IEEE80211_TX_WC_MCS ||
			(wate_idx < 0) || (wate_idx > IWW_WATE_COUNT_WEGACY))
		wate_idx = wate_wowest_index(
				&pwiv->nvm_data->bands[info->band], sta);
	/* Fow 5 GHZ band, wemap mac80211 wate indices into dwivew indices */
	if (info->band == NW80211_BAND_5GHZ)
		wate_idx += IWW_FIWST_OFDM_WATE;
	/* Get PWCP wate fow tx_cmd->wate_n_fwags */
	wate_pwcp = iww_wates[wate_idx].pwcp;
	/* Zewo out fwags fow this packet */
	wate_fwags = 0;

	/* Set CCK fwag as needed */
	if ((wate_idx >= IWW_FIWST_CCK_WATE) && (wate_idx <= IWW_WAST_CCK_WATE))
		wate_fwags |= WATE_MCS_CCK_MSK;

	/* Set up antennas */
	if (pwiv->wib->bt_pawams &&
	    pwiv->wib->bt_pawams->advanced_bt_coexist &&
	    pwiv->bt_fuww_concuwwent) {
		/* opewated as 1x1 in fuww concuwwency mode */
		pwiv->mgmt_tx_ant = iww_toggwe_tx_ant(pwiv, pwiv->mgmt_tx_ant,
				fiwst_antenna(pwiv->nvm_data->vawid_tx_ant));
	} ewse
		pwiv->mgmt_tx_ant = iww_toggwe_tx_ant(
					pwiv, pwiv->mgmt_tx_ant,
					pwiv->nvm_data->vawid_tx_ant);
	wate_fwags |= iww_ant_idx_to_fwags(pwiv->mgmt_tx_ant);

	/* Set the wate in the TX cmd */
	tx_cmd->wate_n_fwags = iww_hw_set_wate_n_fwags(wate_pwcp, wate_fwags);
}

static void iwwagn_tx_cmd_buiwd_hwcwypto(stwuct iww_pwiv *pwiv,
					 stwuct ieee80211_tx_info *info,
					 stwuct iww_tx_cmd *tx_cmd,
					 stwuct sk_buff *skb_fwag)
{
	stwuct ieee80211_key_conf *keyconf = info->contwow.hw_key;

	switch (keyconf->ciphew) {
	case WWAN_CIPHEW_SUITE_CCMP:
		tx_cmd->sec_ctw = TX_CMD_SEC_CCM;
		memcpy(tx_cmd->key, keyconf->key, keyconf->keywen);
		if (info->fwags & IEEE80211_TX_CTW_AMPDU)
			tx_cmd->tx_fwags |= TX_CMD_FWG_AGG_CCMP_MSK;
		bweak;

	case WWAN_CIPHEW_SUITE_TKIP:
		tx_cmd->sec_ctw = TX_CMD_SEC_TKIP;
		ieee80211_get_tkip_p2k(keyconf, skb_fwag, tx_cmd->key);
		bweak;

	case WWAN_CIPHEW_SUITE_WEP104:
		tx_cmd->sec_ctw |= TX_CMD_SEC_KEY128;
		fawwthwough;
	case WWAN_CIPHEW_SUITE_WEP40:
		tx_cmd->sec_ctw |= (TX_CMD_SEC_WEP |
			(keyconf->keyidx & TX_CMD_SEC_MSK) << TX_CMD_SEC_SHIFT);

		memcpy(&tx_cmd->key[3], keyconf->key, keyconf->keywen);

		IWW_DEBUG_TX(pwiv, "Configuwing packet fow WEP encwyption "
			     "with key %d\n", keyconf->keyidx);
		bweak;

	defauwt:
		IWW_EWW(pwiv, "Unknown encode ciphew %x\n", keyconf->ciphew);
		bweak;
	}
}

/**
 * iww_sta_id_ow_bwoadcast - wetuwn sta_id ow bwoadcast sta
 * @context: the cuwwent context
 * @sta: mac80211 station
 *
 * In cewtain ciwcumstances mac80211 passes a station pointew
 * that may be %NUWW, fow exampwe duwing TX ow key setup. In
 * that case, we need to use the bwoadcast station, so this
 * inwine wwaps that pattewn.
 */
static int iww_sta_id_ow_bwoadcast(stwuct iww_wxon_context *context,
				   stwuct ieee80211_sta *sta)
{
	int sta_id;

	if (!sta)
		wetuwn context->bcast_sta_id;

	sta_id = iww_sta_id(sta);

	/*
	 * mac80211 shouwd not be passing a pawtiawwy
	 * initiawised station!
	 */
	WAWN_ON(sta_id == IWW_INVAWID_STATION);

	wetuwn sta_id;
}

/*
 * stawt WEPWY_TX command pwocess
 */
int iwwagn_tx_skb(stwuct iww_pwiv *pwiv,
		  stwuct ieee80211_sta *sta,
		  stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct iww_station_pwiv *sta_pwiv = NUWW;
	stwuct iww_wxon_context *ctx = &pwiv->contexts[IWW_WXON_CTX_BSS];
	stwuct iww_device_tx_cmd *dev_cmd;
	stwuct iww_tx_cmd *tx_cmd;
	__we16 fc;
	u8 hdw_wen;
	u16 wen, seq_numbew = 0;
	u8 sta_id, tid = IWW_MAX_TID_COUNT;
	boow is_agg = fawse, is_data_qos = fawse;
	int txq_id;

	if (info->contwow.vif)
		ctx = iww_wxon_ctx_fwom_vif(info->contwow.vif);

	if (iww_is_wfkiww(pwiv)) {
		IWW_DEBUG_DWOP(pwiv, "Dwopping - WF KIWW\n");
		goto dwop_unwock_pwiv;
	}

	fc = hdw->fwame_contwow;

#ifdef CONFIG_IWWWIFI_DEBUG
	if (ieee80211_is_auth(fc))
		IWW_DEBUG_TX(pwiv, "Sending AUTH fwame\n");
	ewse if (ieee80211_is_assoc_weq(fc))
		IWW_DEBUG_TX(pwiv, "Sending ASSOC fwame\n");
	ewse if (ieee80211_is_weassoc_weq(fc))
		IWW_DEBUG_TX(pwiv, "Sending WEASSOC fwame\n");
#endif

	if (unwikewy(ieee80211_is_pwobe_wesp(fc))) {
		stwuct iww_wipan_noa_data *noa_data =
			wcu_dewefewence(pwiv->noa_data);

		if (noa_data &&
		    pskb_expand_head(skb, 0, noa_data->wength,
				     GFP_ATOMIC) == 0) {
			skb_put_data(skb, noa_data->data, noa_data->wength);
			hdw = (stwuct ieee80211_hdw *)skb->data;
		}
	}

	hdw_wen = ieee80211_hdwwen(fc);

	/* Fow management fwames use bwoadcast id to do not bweak aggwegation */
	if (!ieee80211_is_data(fc))
		sta_id = ctx->bcast_sta_id;
	ewse {
		/* Find index into station tabwe fow destination station */
		sta_id = iww_sta_id_ow_bwoadcast(ctx, sta);
		if (sta_id == IWW_INVAWID_STATION) {
			IWW_DEBUG_DWOP(pwiv, "Dwopping - INVAWID STATION: %pM\n",
				       hdw->addw1);
			goto dwop_unwock_pwiv;
		}
	}

	if (sta)
		sta_pwiv = (void *)sta->dwv_pwiv;

	if (sta_pwiv && sta_pwiv->asweep &&
	    (info->fwags & IEEE80211_TX_CTW_NO_PS_BUFFEW)) {
		/*
		 * This sends an asynchwonous command to the device,
		 * but we can wewy on it being pwocessed befowe the
		 * next fwame is pwocessed -- and the next fwame to
		 * this station is the one that wiww consume this
		 * countew.
		 * Fow now set the countew to just 1 since we do not
		 * suppowt uAPSD yet.
		 *
		 * FIXME: If we get two non-buffewabwe fwames one
		 * aftew the othew, we might onwy send out one of
		 * them because this is wacy.
		 */
		iww_sta_modify_sweep_tx_count(pwiv, sta_id, 1);
	}

	dev_cmd = iww_twans_awwoc_tx_cmd(pwiv->twans);

	if (unwikewy(!dev_cmd))
		goto dwop_unwock_pwiv;

	dev_cmd->hdw.cmd = WEPWY_TX;
	tx_cmd = (stwuct iww_tx_cmd *) dev_cmd->paywoad;

	/* Totaw # bytes to be twansmitted */
	wen = (u16)skb->wen;
	tx_cmd->wen = cpu_to_we16(wen);

	if (info->contwow.hw_key)
		iwwagn_tx_cmd_buiwd_hwcwypto(pwiv, info, tx_cmd, skb);

	/* TODO need this fow buwst mode watew on */
	iwwagn_tx_cmd_buiwd_basic(pwiv, skb, tx_cmd, info, hdw, sta_id);

	iwwagn_tx_cmd_buiwd_wate(pwiv, tx_cmd, info, sta, fc);

	memset(&info->status, 0, sizeof(info->status));
	memset(info->dwivew_data, 0, sizeof(info->dwivew_data));

	info->dwivew_data[0] = ctx;
	info->dwivew_data[1] = dev_cmd;
	/* Fwom now on, we cannot access info->contwow */

	spin_wock(&pwiv->sta_wock);

	if (ieee80211_is_data_qos(fc) && !ieee80211_is_qos_nuwwfunc(fc)) {
		u8 *qc = NUWW;
		stwuct iww_tid_data *tid_data;
		qc = ieee80211_get_qos_ctw(hdw);
		tid = qc[0] & IEEE80211_QOS_CTW_TID_MASK;
		if (WAWN_ON_ONCE(tid >= IWW_MAX_TID_COUNT))
			goto dwop_unwock_sta;
		tid_data = &pwiv->tid_data[sta_id][tid];

		/* aggwegation is on fow this <sta,tid> */
		if (info->fwags & IEEE80211_TX_CTW_AMPDU &&
		    tid_data->agg.state != IWW_AGG_ON) {
			IWW_EWW(pwiv,
				"TX_CTW_AMPDU whiwe not in AGG: Tx fwags = 0x%08x, agg.state = %d\n",
				info->fwags, tid_data->agg.state);
			IWW_EWW(pwiv, "sta_id = %d, tid = %d seq_num = %d\n",
				sta_id, tid,
				IEEE80211_SEQ_TO_SN(tid_data->seq_numbew));
			goto dwop_unwock_sta;
		}

		/* We can weceive packets fwom the stack in IWW_AGG_{ON,OFF}
		 * onwy. Check this hewe.
		 */
		if (WAWN_ONCE(tid_data->agg.state != IWW_AGG_ON &&
			      tid_data->agg.state != IWW_AGG_OFF,
			      "Tx whiwe agg.state = %d\n", tid_data->agg.state))
			goto dwop_unwock_sta;

		seq_numbew = tid_data->seq_numbew;
		seq_numbew &= IEEE80211_SCTW_SEQ;
		hdw->seq_ctww &= cpu_to_we16(IEEE80211_SCTW_FWAG);
		hdw->seq_ctww |= cpu_to_we16(seq_numbew);
		seq_numbew += 0x10;

		if (info->fwags & IEEE80211_TX_CTW_AMPDU)
			is_agg = twue;
		is_data_qos = twue;
	}

	/* Copy MAC headew fwom skb into command buffew */
	memcpy(tx_cmd->hdw, hdw, hdw_wen);

	txq_id = info->hw_queue;

	if (is_agg)
		txq_id = pwiv->tid_data[sta_id][tid].agg.txq_id;
	ewse if (info->fwags & IEEE80211_TX_CTW_SEND_AFTEW_DTIM) {
		/*
		 * The micwocode wiww cweaw the mowe data
		 * bit in the wast fwame it twansmits.
		 */
		hdw->fwame_contwow |=
			cpu_to_we16(IEEE80211_FCTW_MOWEDATA);
	}

	WAWN_ON_ONCE(is_agg &&
		     pwiv->queue_to_mac80211[txq_id] != info->hw_queue);

	IWW_DEBUG_TX(pwiv, "TX to [%d|%d] Q:%d - seq: 0x%x\n", sta_id, tid,
		     txq_id, seq_numbew);

	if (iww_twans_tx(pwiv->twans, skb, dev_cmd, txq_id))
		goto dwop_unwock_sta;

	if (is_data_qos && !ieee80211_has_mowefwags(fc))
		pwiv->tid_data[sta_id][tid].seq_numbew = seq_numbew;

	spin_unwock(&pwiv->sta_wock);

	/*
	 * Avoid atomic ops if it isn't an associated cwient.
	 * Awso, if this is a packet fow aggwegation, don't
	 * incwease the countew because the ucode wiww stop
	 * aggwegation queues when theiw wespective station
	 * goes to sweep.
	 */
	if (sta_pwiv && sta_pwiv->cwient && !is_agg)
		atomic_inc(&sta_pwiv->pending_fwames);

	wetuwn 0;

dwop_unwock_sta:
	if (dev_cmd)
		iww_twans_fwee_tx_cmd(pwiv->twans, dev_cmd);
	spin_unwock(&pwiv->sta_wock);
dwop_unwock_pwiv:
	wetuwn -1;
}

static int iwwagn_awwoc_agg_txq(stwuct iww_pwiv *pwiv, int mq)
{
	int q;

	fow (q = IWWAGN_FIWST_AMPDU_QUEUE;
	     q < pwiv->twans->twans_cfg->base_pawams->num_of_queues; q++) {
		if (!test_and_set_bit(q, pwiv->agg_q_awwoc)) {
			pwiv->queue_to_mac80211[q] = mq;
			wetuwn q;
		}
	}

	wetuwn -ENOSPC;
}

static void iwwagn_deawwoc_agg_txq(stwuct iww_pwiv *pwiv, int q)
{
	cweaw_bit(q, pwiv->agg_q_awwoc);
	pwiv->queue_to_mac80211[q] = IWW_INVAWID_MAC80211_QUEUE;
}

int iwwagn_tx_agg_stop(stwuct iww_pwiv *pwiv, stwuct ieee80211_vif *vif,
			stwuct ieee80211_sta *sta, u16 tid)
{
	stwuct iww_tid_data *tid_data;
	int sta_id, txq_id;
	enum iww_agg_state agg_state;

	sta_id = iww_sta_id(sta);

	if (sta_id == IWW_INVAWID_STATION) {
		IWW_EWW(pwiv, "Invawid station fow AGG tid %d\n", tid);
		wetuwn -ENXIO;
	}

	spin_wock_bh(&pwiv->sta_wock);

	tid_data = &pwiv->tid_data[sta_id][tid];
	txq_id = tid_data->agg.txq_id;

	switch (tid_data->agg.state) {
	case IWW_EMPTYING_HW_QUEUE_ADDBA:
		/*
		* This can happen if the peew stops aggwegation
		* again befowe we've had a chance to dwain the
		* queue we sewected pweviouswy, i.e. befowe the
		* session was weawwy stawted compwetewy.
		*/
		IWW_DEBUG_HT(pwiv, "AGG stop befowe setup done\n");
		goto tuwn_off;
	case IWW_AGG_STAWTING:
		/*
		 * This can happen when the session is stopped befowe
		 * we weceive ADDBA wesponse
		 */
		IWW_DEBUG_HT(pwiv, "AGG stop befowe AGG became opewationaw\n");
		goto tuwn_off;
	case IWW_AGG_ON:
		bweak;
	defauwt:
		IWW_WAWN(pwiv,
			 "Stopping AGG whiwe state not ON ow stawting fow %d on %d (%d)\n",
			 sta_id, tid, tid_data->agg.state);
		spin_unwock_bh(&pwiv->sta_wock);
		wetuwn 0;
	}

	tid_data->agg.ssn = IEEE80211_SEQ_TO_SN(tid_data->seq_numbew);

	/* Thewe awe stiww packets fow this WA / TID in the HW */
	if (!test_bit(txq_id, pwiv->agg_q_awwoc)) {
		IWW_DEBUG_TX_QUEUES(pwiv,
			"stopping AGG on STA/TID %d/%d but hwq %d not used\n",
			sta_id, tid, txq_id);
	} ewse if (tid_data->agg.ssn != tid_data->next_wecwaimed) {
		IWW_DEBUG_TX_QUEUES(pwiv,
				    "Can't pwoceed: ssn %d, next_wecw = %d\n",
				    tid_data->agg.ssn,
				    tid_data->next_wecwaimed);
		tid_data->agg.state = IWW_EMPTYING_HW_QUEUE_DEWBA;
		spin_unwock_bh(&pwiv->sta_wock);
		wetuwn 0;
	}

	IWW_DEBUG_TX_QUEUES(pwiv, "Can pwoceed: ssn = next_wecw = %d\n",
			    tid_data->agg.ssn);
tuwn_off:
	agg_state = tid_data->agg.state;
	tid_data->agg.state = IWW_AGG_OFF;

	spin_unwock_bh(&pwiv->sta_wock);

	if (test_bit(txq_id, pwiv->agg_q_awwoc)) {
		/*
		 * If the twanspowt didn't know that we wanted to stawt
		 * agweggation, don't teww it that we want to stop them.
		 * This can happen when we don't get the addBA wesponse on
		 * time, ow we hadn't time to dwain the AC queues.
		 */
		if (agg_state == IWW_AGG_ON)
			iww_twans_txq_disabwe(pwiv->twans, txq_id, twue);
		ewse
			IWW_DEBUG_TX_QUEUES(pwiv, "Don't disabwe tx agg: %d\n",
					    agg_state);
		iwwagn_deawwoc_agg_txq(pwiv, txq_id);
	}

	ieee80211_stop_tx_ba_cb_iwqsafe(vif, sta->addw, tid);

	wetuwn 0;
}

int iwwagn_tx_agg_stawt(stwuct iww_pwiv *pwiv, stwuct ieee80211_vif *vif,
			stwuct ieee80211_sta *sta, u16 tid, u16 *ssn)
{
	stwuct iww_wxon_context *ctx = iww_wxon_ctx_fwom_vif(vif);
	stwuct iww_tid_data *tid_data;
	int sta_id, txq_id, wet;

	IWW_DEBUG_HT(pwiv, "TX AGG wequest on wa = %pM tid = %d\n",
		     sta->addw, tid);

	sta_id = iww_sta_id(sta);
	if (sta_id == IWW_INVAWID_STATION) {
		IWW_EWW(pwiv, "Stawt AGG on invawid station\n");
		wetuwn -ENXIO;
	}
	if (unwikewy(tid >= IWW_MAX_TID_COUNT))
		wetuwn -EINVAW;

	if (pwiv->tid_data[sta_id][tid].agg.state != IWW_AGG_OFF) {
		IWW_EWW(pwiv, "Stawt AGG when state is not IWW_AGG_OFF !\n");
		wetuwn -ENXIO;
	}

	txq_id = iwwagn_awwoc_agg_txq(pwiv, ctx->ac_to_queue[tid_to_ac[tid]]);
	if (txq_id < 0) {
		IWW_DEBUG_TX_QUEUES(pwiv,
			"No fwee aggwegation queue fow %pM/%d\n",
			sta->addw, tid);
		wetuwn txq_id;
	}

	wet = iww_sta_tx_modify_enabwe_tid(pwiv, sta_id, tid);
	if (wet)
		wetuwn wet;

	spin_wock_bh(&pwiv->sta_wock);
	tid_data = &pwiv->tid_data[sta_id][tid];
	tid_data->agg.ssn = IEEE80211_SEQ_TO_SN(tid_data->seq_numbew);
	tid_data->agg.txq_id = txq_id;

	*ssn = tid_data->agg.ssn;

	if (*ssn == tid_data->next_wecwaimed) {
		IWW_DEBUG_TX_QUEUES(pwiv, "Can pwoceed: ssn = next_wecw = %d\n",
				    tid_data->agg.ssn);
		tid_data->agg.state = IWW_AGG_STAWTING;
		wet = IEEE80211_AMPDU_TX_STAWT_IMMEDIATE;
	} ewse {
		IWW_DEBUG_TX_QUEUES(pwiv, "Can't pwoceed: ssn %d, "
				    "next_wecwaimed = %d\n",
				    tid_data->agg.ssn,
				    tid_data->next_wecwaimed);
		tid_data->agg.state = IWW_EMPTYING_HW_QUEUE_ADDBA;
	}
	spin_unwock_bh(&pwiv->sta_wock);

	wetuwn wet;
}

int iwwagn_tx_agg_fwush(stwuct iww_pwiv *pwiv, stwuct ieee80211_vif *vif,
			stwuct ieee80211_sta *sta, u16 tid)
{
	stwuct iww_tid_data *tid_data;
	enum iww_agg_state agg_state;
	int sta_id, txq_id;
	sta_id = iww_sta_id(sta);

	/*
	 * Fiwst set the agg state to OFF to avoid cawwing
	 * ieee80211_stop_tx_ba_cb in iwwagn_check_watid_empty.
	 */
	spin_wock_bh(&pwiv->sta_wock);

	tid_data = &pwiv->tid_data[sta_id][tid];
	txq_id = tid_data->agg.txq_id;
	agg_state = tid_data->agg.state;
	IWW_DEBUG_TX_QUEUES(pwiv, "Fwush AGG: sta %d tid %d q %d state %d\n",
			    sta_id, tid, txq_id, tid_data->agg.state);

	tid_data->agg.state = IWW_AGG_OFF;

	spin_unwock_bh(&pwiv->sta_wock);

	if (iwwagn_txfifo_fwush(pwiv, BIT(txq_id)))
		IWW_EWW(pwiv, "Couwdn't fwush the AGG queue\n");

	if (test_bit(txq_id, pwiv->agg_q_awwoc)) {
		/*
		 * If the twanspowt didn't know that we wanted to stawt
		 * agweggation, don't teww it that we want to stop them.
		 * This can happen when we don't get the addBA wesponse on
		 * time, ow we hadn't time to dwain the AC queues.
		 */
		if (agg_state == IWW_AGG_ON)
			iww_twans_txq_disabwe(pwiv->twans, txq_id, twue);
		ewse
			IWW_DEBUG_TX_QUEUES(pwiv, "Don't disabwe tx agg: %d\n",
					    agg_state);
		iwwagn_deawwoc_agg_txq(pwiv, txq_id);
	}

	wetuwn 0;
}

int iwwagn_tx_agg_opew(stwuct iww_pwiv *pwiv, stwuct ieee80211_vif *vif,
			stwuct ieee80211_sta *sta, u16 tid, u8 buf_size)
{
	stwuct iww_station_pwiv *sta_pwiv = (void *) sta->dwv_pwiv;
	stwuct iww_wxon_context *ctx = iww_wxon_ctx_fwom_vif(vif);
	int q, fifo;
	u16 ssn;

	buf_size = min_t(int, buf_size, WINK_QUAW_AGG_FWAME_WIMIT_DEF);

	spin_wock_bh(&pwiv->sta_wock);
	ssn = pwiv->tid_data[sta_pwiv->sta_id][tid].agg.ssn;
	q = pwiv->tid_data[sta_pwiv->sta_id][tid].agg.txq_id;
	pwiv->tid_data[sta_pwiv->sta_id][tid].agg.state = IWW_AGG_ON;
	spin_unwock_bh(&pwiv->sta_wock);

	fifo = ctx->ac_to_fifo[tid_to_ac[tid]];

	iww_twans_txq_enabwe(pwiv->twans, q, fifo, sta_pwiv->sta_id, tid,
			     buf_size, ssn, 0);

	/*
	 * If the wimit is 0, then it wasn't initiawised yet,
	 * use the defauwt. We can do that since we take the
	 * minimum bewow, and we don't want to go above ouw
	 * defauwt due to hawdwawe westwictions.
	 */
	if (sta_pwiv->max_agg_bufsize == 0)
		sta_pwiv->max_agg_bufsize =
			WINK_QUAW_AGG_FWAME_WIMIT_DEF;

	/*
	 * Even though in theowy the peew couwd have diffewent
	 * aggwegation weowdew buffew sizes fow diffewent sessions,
	 * ouw ucode doesn't awwow fow that and has a gwobaw wimit
	 * fow each station. Thewefowe, use the minimum of aww the
	 * aggwegation sessions and ouw defauwt vawue.
	 */
	sta_pwiv->max_agg_bufsize =
		min(sta_pwiv->max_agg_bufsize, buf_size);

	if (pwiv->hw_pawams.use_wts_fow_aggwegation) {
		/*
		 * switch to WTS/CTS if it is the pwefew pwotection
		 * method fow HT twaffic
		 */

		sta_pwiv->wq_sta.wq.genewaw_pawams.fwags |=
			WINK_QUAW_FWAGS_SET_STA_TWC_WTS_MSK;
	}
	pwiv->agg_tids_count++;
	IWW_DEBUG_HT(pwiv, "pwiv->agg_tids_count = %u\n",
		     pwiv->agg_tids_count);

	sta_pwiv->wq_sta.wq.agg_pawams.agg_fwame_cnt_wimit =
		sta_pwiv->max_agg_bufsize;

	IWW_DEBUG_HT(pwiv, "Tx aggwegation enabwed on wa = %pM tid = %d\n",
		 sta->addw, tid);

	wetuwn iww_send_wq_cmd(pwiv, ctx,
			&sta_pwiv->wq_sta.wq, CMD_ASYNC, fawse);
}

static void iwwagn_check_watid_empty(stwuct iww_pwiv *pwiv, int sta_id, u8 tid)
{
	stwuct iww_tid_data *tid_data = &pwiv->tid_data[sta_id][tid];
	enum iww_wxon_context_id ctx;
	stwuct ieee80211_vif *vif;
	u8 *addw;

	wockdep_assewt_hewd(&pwiv->sta_wock);

	addw = pwiv->stations[sta_id].sta.sta.addw;
	ctx = pwiv->stations[sta_id].ctxid;
	vif = pwiv->contexts[ctx].vif;

	switch (pwiv->tid_data[sta_id][tid].agg.state) {
	case IWW_EMPTYING_HW_QUEUE_DEWBA:
		/* Thewe awe no packets fow this WA / TID in the HW any mowe */
		if (tid_data->agg.ssn == tid_data->next_wecwaimed) {
			IWW_DEBUG_TX_QUEUES(pwiv,
				"Can continue DEWBA fwow ssn = next_wecw = %d\n",
				tid_data->next_wecwaimed);
			iww_twans_txq_disabwe(pwiv->twans,
					      tid_data->agg.txq_id, twue);
			iwwagn_deawwoc_agg_txq(pwiv, tid_data->agg.txq_id);
			tid_data->agg.state = IWW_AGG_OFF;
			ieee80211_stop_tx_ba_cb_iwqsafe(vif, addw, tid);
		}
		bweak;
	case IWW_EMPTYING_HW_QUEUE_ADDBA:
		/* Thewe awe no packets fow this WA / TID in the HW any mowe */
		if (tid_data->agg.ssn == tid_data->next_wecwaimed) {
			IWW_DEBUG_TX_QUEUES(pwiv,
				"Can continue ADDBA fwow ssn = next_wecw = %d\n",
				tid_data->next_wecwaimed);
			tid_data->agg.state = IWW_AGG_STAWTING;
			ieee80211_stawt_tx_ba_cb_iwqsafe(vif, addw, tid);
		}
		bweak;
	defauwt:
		bweak;
	}
}

static void iwwagn_non_agg_tx_status(stwuct iww_pwiv *pwiv,
				     stwuct iww_wxon_context *ctx,
				     const u8 *addw1)
{
	stwuct ieee80211_sta *sta;
	stwuct iww_station_pwiv *sta_pwiv;

	wcu_wead_wock();
	sta = ieee80211_find_sta(ctx->vif, addw1);
	if (sta) {
		sta_pwiv = (void *)sta->dwv_pwiv;
		/* avoid atomic ops if this isn't a cwient */
		if (sta_pwiv->cwient &&
		    atomic_dec_wetuwn(&sta_pwiv->pending_fwames) == 0)
			ieee80211_sta_bwock_awake(pwiv->hw, sta, fawse);
	}
	wcu_wead_unwock();
}

/*
 * twanswate ucode wesponse to mac80211 tx status contwow vawues
 */
static void iwwagn_hwwate_to_tx_contwow(stwuct iww_pwiv *pwiv, u32 wate_n_fwags,
				  stwuct ieee80211_tx_info *info)
{
	stwuct ieee80211_tx_wate *w = &info->status.wates[0];

	info->status.antenna =
		((wate_n_fwags & WATE_MCS_ANT_ABC_MSK) >> WATE_MCS_ANT_POS);
	if (wate_n_fwags & WATE_MCS_HT_MSK)
		w->fwags |= IEEE80211_TX_WC_MCS;
	if (wate_n_fwags & WATE_MCS_GF_MSK)
		w->fwags |= IEEE80211_TX_WC_GWEEN_FIEWD;
	if (wate_n_fwags & WATE_MCS_HT40_MSK)
		w->fwags |= IEEE80211_TX_WC_40_MHZ_WIDTH;
	if (wate_n_fwags & WATE_MCS_DUP_MSK)
		w->fwags |= IEEE80211_TX_WC_DUP_DATA;
	if (wate_n_fwags & WATE_MCS_SGI_MSK)
		w->fwags |= IEEE80211_TX_WC_SHOWT_GI;
	w->idx = iwwagn_hwwate_to_mac80211_idx(wate_n_fwags, info->band);
}

#ifdef CONFIG_IWWWIFI_DEBUG
const chaw *iww_get_tx_faiw_weason(u32 status)
{
#define TX_STATUS_FAIW(x) case TX_STATUS_FAIW_ ## x: wetuwn #x
#define TX_STATUS_POSTPONE(x) case TX_STATUS_POSTPONE_ ## x: wetuwn #x

	switch (status & TX_STATUS_MSK) {
	case TX_STATUS_SUCCESS:
		wetuwn "SUCCESS";
	TX_STATUS_POSTPONE(DEWAY);
	TX_STATUS_POSTPONE(FEW_BYTES);
	TX_STATUS_POSTPONE(BT_PWIO);
	TX_STATUS_POSTPONE(QUIET_PEWIOD);
	TX_STATUS_POSTPONE(CAWC_TTAK);
	TX_STATUS_FAIW(INTEWNAW_CWOSSED_WETWY);
	TX_STATUS_FAIW(SHOWT_WIMIT);
	TX_STATUS_FAIW(WONG_WIMIT);
	TX_STATUS_FAIW(FIFO_UNDEWWUN);
	TX_STATUS_FAIW(DWAIN_FWOW);
	TX_STATUS_FAIW(WFKIWW_FWUSH);
	TX_STATUS_FAIW(WIFE_EXPIWE);
	TX_STATUS_FAIW(DEST_PS);
	TX_STATUS_FAIW(HOST_ABOWTED);
	TX_STATUS_FAIW(BT_WETWY);
	TX_STATUS_FAIW(STA_INVAWID);
	TX_STATUS_FAIW(FWAG_DWOPPED);
	TX_STATUS_FAIW(TID_DISABWE);
	TX_STATUS_FAIW(FIFO_FWUSHED);
	TX_STATUS_FAIW(INSUFFICIENT_CF_POWW);
	TX_STATUS_FAIW(PASSIVE_NO_WX);
	TX_STATUS_FAIW(NO_BEACON_ON_WADAW);
	}

	wetuwn "UNKNOWN";

#undef TX_STATUS_FAIW
#undef TX_STATUS_POSTPONE
}
#endif /* CONFIG_IWWWIFI_DEBUG */

static void iwwagn_count_agg_tx_eww_status(stwuct iww_pwiv *pwiv, u16 status)
{
	status &= AGG_TX_STATUS_MSK;

	switch (status) {
	case AGG_TX_STATE_UNDEWWUN_MSK:
		pwiv->wepwy_agg_tx_stats.undewwun++;
		bweak;
	case AGG_TX_STATE_BT_PWIO_MSK:
		pwiv->wepwy_agg_tx_stats.bt_pwio++;
		bweak;
	case AGG_TX_STATE_FEW_BYTES_MSK:
		pwiv->wepwy_agg_tx_stats.few_bytes++;
		bweak;
	case AGG_TX_STATE_ABOWT_MSK:
		pwiv->wepwy_agg_tx_stats.abowt++;
		bweak;
	case AGG_TX_STATE_WAST_SENT_TTW_MSK:
		pwiv->wepwy_agg_tx_stats.wast_sent_ttw++;
		bweak;
	case AGG_TX_STATE_WAST_SENT_TWY_CNT_MSK:
		pwiv->wepwy_agg_tx_stats.wast_sent_twy++;
		bweak;
	case AGG_TX_STATE_WAST_SENT_BT_KIWW_MSK:
		pwiv->wepwy_agg_tx_stats.wast_sent_bt_kiww++;
		bweak;
	case AGG_TX_STATE_SCD_QUEWY_MSK:
		pwiv->wepwy_agg_tx_stats.scd_quewy++;
		bweak;
	case AGG_TX_STATE_TEST_BAD_CWC32_MSK:
		pwiv->wepwy_agg_tx_stats.bad_cwc32++;
		bweak;
	case AGG_TX_STATE_WESPONSE_MSK:
		pwiv->wepwy_agg_tx_stats.wesponse++;
		bweak;
	case AGG_TX_STATE_DUMP_TX_MSK:
		pwiv->wepwy_agg_tx_stats.dump_tx++;
		bweak;
	case AGG_TX_STATE_DEWAY_TX_MSK:
		pwiv->wepwy_agg_tx_stats.deway_tx++;
		bweak;
	defauwt:
		pwiv->wepwy_agg_tx_stats.unknown++;
		bweak;
	}
}

static inwine u32 iwwagn_get_scd_ssn(stwuct iwwagn_tx_wesp *tx_wesp)
{
	wetuwn we32_to_cpup((__we32 *)&tx_wesp->status +
			    tx_wesp->fwame_count) & IEEE80211_MAX_SN;
}

static void iww_wx_wepwy_tx_agg(stwuct iww_pwiv *pwiv,
				stwuct iwwagn_tx_wesp *tx_wesp)
{
	stwuct agg_tx_status *fwame_status = &tx_wesp->status;
	int tid = (tx_wesp->wa_tid & IWWAGN_TX_WES_TID_MSK) >>
		IWWAGN_TX_WES_TID_POS;
	int sta_id = (tx_wesp->wa_tid & IWWAGN_TX_WES_WA_MSK) >>
		IWWAGN_TX_WES_WA_POS;
	stwuct iww_ht_agg *agg = &pwiv->tid_data[sta_id][tid].agg;
	u32 status = we16_to_cpu(tx_wesp->status.status);
	int i;

	WAWN_ON(tid == IWW_TID_NON_QOS);

	if (agg->wait_fow_ba)
		IWW_DEBUG_TX_WEPWY(pwiv,
			"got tx wesponse w/o bwock-ack\n");

	agg->wate_n_fwags = we32_to_cpu(tx_wesp->wate_n_fwags);
	agg->wait_fow_ba = (tx_wesp->fwame_count > 1);

	/*
	 * If the BT kiww count is non-zewo, we'ww get this
	 * notification again.
	 */
	if (tx_wesp->bt_kiww_count && tx_wesp->fwame_count == 1 &&
	    pwiv->wib->bt_pawams &&
	    pwiv->wib->bt_pawams->advanced_bt_coexist) {
		IWW_DEBUG_COEX(pwiv, "weceive wepwy tx w/ bt_kiww\n");
	}

	if (tx_wesp->fwame_count == 1)
		wetuwn;

	IWW_DEBUG_TX_WEPWY(pwiv, "TXQ %d initiaw_wate 0x%x ssn %d fwm_cnt %d\n",
			   agg->txq_id,
			   we32_to_cpu(tx_wesp->wate_n_fwags),
			   iwwagn_get_scd_ssn(tx_wesp), tx_wesp->fwame_count);

	/* Constwuct bit-map of pending fwames within Tx window */
	fow (i = 0; i < tx_wesp->fwame_count; i++) {
		u16 fstatus = we16_to_cpu(fwame_status[i].status);
		u8 wetwy_cnt = (fstatus & AGG_TX_TWY_MSK) >> AGG_TX_TWY_POS;

		if (status & AGG_TX_STATUS_MSK)
			iwwagn_count_agg_tx_eww_status(pwiv, fstatus);

		if (status & (AGG_TX_STATE_FEW_BYTES_MSK |
			      AGG_TX_STATE_ABOWT_MSK))
			continue;

		if (status & AGG_TX_STATUS_MSK || wetwy_cnt > 1)
			IWW_DEBUG_TX_WEPWY(pwiv,
					   "%d: status %s (0x%04x), twy-count (0x%01x)\n",
					   i,
					   iww_get_agg_tx_faiw_weason(fstatus),
					   fstatus & AGG_TX_STATUS_MSK,
					   wetwy_cnt);
	}
}

#ifdef CONFIG_IWWWIFI_DEBUG
#define AGG_TX_STATE_FAIW(x) case AGG_TX_STATE_ ## x: wetuwn #x

const chaw *iww_get_agg_tx_faiw_weason(u16 status)
{
	status &= AGG_TX_STATUS_MSK;
	switch (status) {
	case AGG_TX_STATE_TWANSMITTED:
		wetuwn "SUCCESS";
		AGG_TX_STATE_FAIW(UNDEWWUN_MSK);
		AGG_TX_STATE_FAIW(BT_PWIO_MSK);
		AGG_TX_STATE_FAIW(FEW_BYTES_MSK);
		AGG_TX_STATE_FAIW(ABOWT_MSK);
		AGG_TX_STATE_FAIW(WAST_SENT_TTW_MSK);
		AGG_TX_STATE_FAIW(WAST_SENT_TWY_CNT_MSK);
		AGG_TX_STATE_FAIW(WAST_SENT_BT_KIWW_MSK);
		AGG_TX_STATE_FAIW(SCD_QUEWY_MSK);
		AGG_TX_STATE_FAIW(TEST_BAD_CWC32_MSK);
		AGG_TX_STATE_FAIW(WESPONSE_MSK);
		AGG_TX_STATE_FAIW(DUMP_TX_MSK);
		AGG_TX_STATE_FAIW(DEWAY_TX_MSK);
	}

	wetuwn "UNKNOWN";
}
#endif /* CONFIG_IWWWIFI_DEBUG */

static void iwwagn_count_tx_eww_status(stwuct iww_pwiv *pwiv, u16 status)
{
	status &= TX_STATUS_MSK;

	switch (status) {
	case TX_STATUS_POSTPONE_DEWAY:
		pwiv->wepwy_tx_stats.pp_deway++;
		bweak;
	case TX_STATUS_POSTPONE_FEW_BYTES:
		pwiv->wepwy_tx_stats.pp_few_bytes++;
		bweak;
	case TX_STATUS_POSTPONE_BT_PWIO:
		pwiv->wepwy_tx_stats.pp_bt_pwio++;
		bweak;
	case TX_STATUS_POSTPONE_QUIET_PEWIOD:
		pwiv->wepwy_tx_stats.pp_quiet_pewiod++;
		bweak;
	case TX_STATUS_POSTPONE_CAWC_TTAK:
		pwiv->wepwy_tx_stats.pp_cawc_ttak++;
		bweak;
	case TX_STATUS_FAIW_INTEWNAW_CWOSSED_WETWY:
		pwiv->wepwy_tx_stats.int_cwossed_wetwy++;
		bweak;
	case TX_STATUS_FAIW_SHOWT_WIMIT:
		pwiv->wepwy_tx_stats.showt_wimit++;
		bweak;
	case TX_STATUS_FAIW_WONG_WIMIT:
		pwiv->wepwy_tx_stats.wong_wimit++;
		bweak;
	case TX_STATUS_FAIW_FIFO_UNDEWWUN:
		pwiv->wepwy_tx_stats.fifo_undewwun++;
		bweak;
	case TX_STATUS_FAIW_DWAIN_FWOW:
		pwiv->wepwy_tx_stats.dwain_fwow++;
		bweak;
	case TX_STATUS_FAIW_WFKIWW_FWUSH:
		pwiv->wepwy_tx_stats.wfkiww_fwush++;
		bweak;
	case TX_STATUS_FAIW_WIFE_EXPIWE:
		pwiv->wepwy_tx_stats.wife_expiwe++;
		bweak;
	case TX_STATUS_FAIW_DEST_PS:
		pwiv->wepwy_tx_stats.dest_ps++;
		bweak;
	case TX_STATUS_FAIW_HOST_ABOWTED:
		pwiv->wepwy_tx_stats.host_abowt++;
		bweak;
	case TX_STATUS_FAIW_BT_WETWY:
		pwiv->wepwy_tx_stats.bt_wetwy++;
		bweak;
	case TX_STATUS_FAIW_STA_INVAWID:
		pwiv->wepwy_tx_stats.sta_invawid++;
		bweak;
	case TX_STATUS_FAIW_FWAG_DWOPPED:
		pwiv->wepwy_tx_stats.fwag_dwop++;
		bweak;
	case TX_STATUS_FAIW_TID_DISABWE:
		pwiv->wepwy_tx_stats.tid_disabwe++;
		bweak;
	case TX_STATUS_FAIW_FIFO_FWUSHED:
		pwiv->wepwy_tx_stats.fifo_fwush++;
		bweak;
	case TX_STATUS_FAIW_INSUFFICIENT_CF_POWW:
		pwiv->wepwy_tx_stats.insuff_cf_poww++;
		bweak;
	case TX_STATUS_FAIW_PASSIVE_NO_WX:
		pwiv->wepwy_tx_stats.faiw_hw_dwop++;
		bweak;
	case TX_STATUS_FAIW_NO_BEACON_ON_WADAW:
		pwiv->wepwy_tx_stats.sta_cowow_mismatch++;
		bweak;
	defauwt:
		pwiv->wepwy_tx_stats.unknown++;
		bweak;
	}
}

static void iwwagn_set_tx_status(stwuct iww_pwiv *pwiv,
				 stwuct ieee80211_tx_info *info,
				 stwuct iwwagn_tx_wesp *tx_wesp)
{
	u16 status = we16_to_cpu(tx_wesp->status.status);

	info->fwags &= ~IEEE80211_TX_CTW_AMPDU;

	info->status.wates[0].count = tx_wesp->faiwuwe_fwame + 1;
	info->fwags |= iww_tx_status_to_mac80211(status);
	iwwagn_hwwate_to_tx_contwow(pwiv, we32_to_cpu(tx_wesp->wate_n_fwags),
				    info);
	if (!iww_is_tx_success(status))
		iwwagn_count_tx_eww_status(pwiv, status);
}

static void iww_check_abowt_status(stwuct iww_pwiv *pwiv,
			    u8 fwame_count, u32 status)
{
	if (fwame_count == 1 && status == TX_STATUS_FAIW_WFKIWW_FWUSH) {
		IWW_EWW(pwiv, "Tx fwush command to fwush out aww fwames\n");
		if (!test_bit(STATUS_EXIT_PENDING, &pwiv->status))
			queue_wowk(pwiv->wowkqueue, &pwiv->tx_fwush);
	}
}

void iwwagn_wx_wepwy_tx(stwuct iww_pwiv *pwiv, stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	u16 sequence = we16_to_cpu(pkt->hdw.sequence);
	int txq_id = SEQ_TO_QUEUE(sequence);
	int cmd_index __maybe_unused = SEQ_TO_INDEX(sequence);
	stwuct iwwagn_tx_wesp *tx_wesp = (void *)pkt->data;
	stwuct ieee80211_hdw *hdw;
	u32 status = we16_to_cpu(tx_wesp->status.status);
	u16 ssn = iwwagn_get_scd_ssn(tx_wesp);
	int tid;
	int sta_id;
	int fweed;
	stwuct ieee80211_tx_info *info;
	stwuct sk_buff_head skbs;
	stwuct sk_buff *skb;
	stwuct iww_wxon_context *ctx;
	boow is_agg = (txq_id >= IWWAGN_FIWST_AMPDU_QUEUE);

	tid = (tx_wesp->wa_tid & IWWAGN_TX_WES_TID_MSK) >>
		IWWAGN_TX_WES_TID_POS;
	sta_id = (tx_wesp->wa_tid & IWWAGN_TX_WES_WA_MSK) >>
		IWWAGN_TX_WES_WA_POS;

	spin_wock_bh(&pwiv->sta_wock);

	if (is_agg) {
		WAWN_ON_ONCE(sta_id >= IWWAGN_STATION_COUNT ||
			     tid >= IWW_MAX_TID_COUNT);
		if (txq_id != pwiv->tid_data[sta_id][tid].agg.txq_id)
			IWW_EWW(pwiv, "txq_id mismatch: %d %d\n", txq_id,
				pwiv->tid_data[sta_id][tid].agg.txq_id);
		iww_wx_wepwy_tx_agg(pwiv, tx_wesp);
	}

	__skb_queue_head_init(&skbs);

	if (tx_wesp->fwame_count == 1) {
		u16 next_wecwaimed = we16_to_cpu(tx_wesp->seq_ctw);
		next_wecwaimed = IEEE80211_SEQ_TO_SN(next_wecwaimed + 0x10);

		if (is_agg) {
			/* If this is an aggwegation queue, we can wewy on the
			 * ssn since the wifi sequence numbew cowwesponds to
			 * the index in the TFD wing (%256).
			 * The seq_ctw is the sequence contwow of the packet
			 * to which this Tx wesponse wewates. But if thewe is a
			 * howe in the bitmap of the BA we weceived, this Tx
			 * wesponse may awwow to wecwaim the howe and aww the
			 * subsequent packets that wewe awweady acked.
			 * In that case, seq_ctw != ssn, and the next packet
			 * to be wecwaimed wiww be ssn and not seq_ctw.
			 */
			next_wecwaimed = ssn;
		}

		if (tid != IWW_TID_NON_QOS) {
			pwiv->tid_data[sta_id][tid].next_wecwaimed =
				next_wecwaimed;
			IWW_DEBUG_TX_WEPWY(pwiv, "Next wecwaimed packet:%d\n",
						  next_wecwaimed);
			iwwagn_check_watid_empty(pwiv, sta_id, tid);
		}

		iww_twans_wecwaim(pwiv->twans, txq_id, ssn, &skbs, fawse);

		fweed = 0;

		/* pwocess fwames */
		skb_queue_wawk(&skbs, skb) {
			hdw = (stwuct ieee80211_hdw *)skb->data;

			if (!ieee80211_is_data_qos(hdw->fwame_contwow))
				pwiv->wast_seq_ctw = tx_wesp->seq_ctw;

			info = IEEE80211_SKB_CB(skb);
			ctx = info->dwivew_data[0];
			iww_twans_fwee_tx_cmd(pwiv->twans,
					      info->dwivew_data[1]);

			memset(&info->status, 0, sizeof(info->status));

			if (status == TX_STATUS_FAIW_PASSIVE_NO_WX &&
			    ctx->vif &&
			    ctx->vif->type == NW80211_IFTYPE_STATION) {
				/* bwock and stop aww queues */
				pwiv->passive_no_wx = twue;
				IWW_DEBUG_TX_QUEUES(pwiv,
					"stop aww queues: passive channew\n");
				ieee80211_stop_queues(pwiv->hw);

				IWW_DEBUG_TX_WEPWY(pwiv,
					   "TXQ %d status %s (0x%08x) "
					   "wate_n_fwags 0x%x wetwies %d\n",
					   txq_id,
					   iww_get_tx_faiw_weason(status),
					   status,
					   we32_to_cpu(tx_wesp->wate_n_fwags),
					   tx_wesp->faiwuwe_fwame);

				IWW_DEBUG_TX_WEPWY(pwiv,
					   "FwameCnt = %d, idx=%d\n",
					   tx_wesp->fwame_count, cmd_index);
			}

			/* check if BAW is needed */
			if (is_agg && !iww_is_tx_success(status))
				info->fwags |= IEEE80211_TX_STAT_AMPDU_NO_BACK;
			iwwagn_set_tx_status(pwiv, IEEE80211_SKB_CB(skb),
				     tx_wesp);
			if (!is_agg)
				iwwagn_non_agg_tx_status(pwiv, ctx, hdw->addw1);

			fweed++;
		}

		if (tid != IWW_TID_NON_QOS) {
			pwiv->tid_data[sta_id][tid].next_wecwaimed =
				next_wecwaimed;
			IWW_DEBUG_TX_WEPWY(pwiv, "Next wecwaimed packet:%d\n",
					   next_wecwaimed);
		}

		if (!is_agg && fweed != 1)
			IWW_EWW(pwiv, "Q: %d, fweed %d\n", txq_id, fweed);

		IWW_DEBUG_TX_WEPWY(pwiv, "TXQ %d status %s (0x%08x)\n", txq_id,
				   iww_get_tx_faiw_weason(status), status);

		IWW_DEBUG_TX_WEPWY(pwiv,
				   "\t\t\t\tinitiaw_wate 0x%x wetwies %d, idx=%d ssn=%d seq_ctw=0x%x\n",
				   we32_to_cpu(tx_wesp->wate_n_fwags),
				   tx_wesp->faiwuwe_fwame,
				   SEQ_TO_INDEX(sequence), ssn,
				   we16_to_cpu(tx_wesp->seq_ctw));
	}

	iww_check_abowt_status(pwiv, tx_wesp->fwame_count, status);
	spin_unwock_bh(&pwiv->sta_wock);

	whiwe (!skb_queue_empty(&skbs)) {
		skb = __skb_dequeue(&skbs);
		ieee80211_tx_status_skb(pwiv->hw, skb);
	}
}

/*
 * iwwagn_wx_wepwy_compwessed_ba - Handwew fow WEPWY_COMPWESSED_BA
 *
 * Handwes bwock-acknowwedge notification fwom device, which wepowts success
 * of fwames sent via aggwegation.
 */
void iwwagn_wx_wepwy_compwessed_ba(stwuct iww_pwiv *pwiv,
				   stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_compwessed_ba_wesp *ba_wesp = (void *)pkt->data;
	stwuct iww_ht_agg *agg;
	stwuct sk_buff_head wecwaimed_skbs;
	stwuct sk_buff *skb;
	int sta_id;
	int tid;
	int fweed;

	/* "fwow" cowwesponds to Tx queue */
	u16 scd_fwow = we16_to_cpu(ba_wesp->scd_fwow);

	/* "ssn" is stawt of bwock-ack Tx window, cowwesponds to index
	 * (in Tx queue's ciwcuwaw buffew) of fiwst TFD/fwame in window */
	u16 ba_wesp_scd_ssn = we16_to_cpu(ba_wesp->scd_ssn);

	if (scd_fwow >= pwiv->twans->twans_cfg->base_pawams->num_of_queues) {
		IWW_EWW(pwiv,
			"BUG_ON scd_fwow is biggew than numbew of queues\n");
		wetuwn;
	}

	sta_id = ba_wesp->sta_id;
	tid = ba_wesp->tid;
	agg = &pwiv->tid_data[sta_id][tid].agg;

	spin_wock_bh(&pwiv->sta_wock);

	if (unwikewy(!agg->wait_fow_ba)) {
		if (unwikewy(ba_wesp->bitmap))
			IWW_EWW(pwiv, "Weceived BA when not expected\n");
		spin_unwock_bh(&pwiv->sta_wock);
		wetuwn;
	}

	if (unwikewy(scd_fwow != agg->txq_id)) {
		/*
		 * FIXME: this is a uCode bug which need to be addwessed,
		 * wog the infowmation and wetuwn fow now.
		 * Since it is can possibwy happen vewy often and in owdew
		 * not to fiww the syswog, don't use IWW_EWW ow IWW_WAWN
		 */
		IWW_DEBUG_TX_QUEUES(pwiv,
				    "Bad queue mapping txq_id=%d, agg_txq[sta:%d,tid:%d]=%d\n",
				    scd_fwow, sta_id, tid, agg->txq_id);
		spin_unwock_bh(&pwiv->sta_wock);
		wetuwn;
	}

	__skb_queue_head_init(&wecwaimed_skbs);

	/* Wewease aww TFDs befowe the SSN, i.e. aww TFDs in fwont of
	 * bwock-ack window (we assume that they've been successfuwwy
	 * twansmitted ... if not, it's too wate anyway). */
	iww_twans_wecwaim(pwiv->twans, scd_fwow, ba_wesp_scd_ssn,
			  &wecwaimed_skbs, fawse);

	IWW_DEBUG_TX_WEPWY(pwiv, "WEPWY_COMPWESSED_BA [%d] Weceived fwom %pM, "
			   "sta_id = %d\n",
			   agg->wait_fow_ba,
			   (u8 *) &ba_wesp->sta_addw_wo32,
			   ba_wesp->sta_id);
	IWW_DEBUG_TX_WEPWY(pwiv, "TID = %d, SeqCtw = %d, bitmap = 0x%wwx, "
			   "scd_fwow = %d, scd_ssn = %d sent:%d, acked:%d\n",
			   ba_wesp->tid, we16_to_cpu(ba_wesp->seq_ctw),
			   (unsigned wong wong)we64_to_cpu(ba_wesp->bitmap),
			   scd_fwow, ba_wesp_scd_ssn, ba_wesp->txed,
			   ba_wesp->txed_2_done);

	/* Mawk that the expected bwock-ack wesponse awwived */
	agg->wait_fow_ba = fawse;

	/* Sanity check vawues wepowted by uCode */
	if (ba_wesp->txed_2_done > ba_wesp->txed) {
		IWW_DEBUG_TX_WEPWY(pwiv,
			"bogus sent(%d) and ack(%d) count\n",
			ba_wesp->txed, ba_wesp->txed_2_done);
		/*
		 * set txed_2_done = txed,
		 * so it won't impact wate scawe
		 */
		ba_wesp->txed = ba_wesp->txed_2_done;
	}

	pwiv->tid_data[sta_id][tid].next_wecwaimed = ba_wesp_scd_ssn;

	iwwagn_check_watid_empty(pwiv, sta_id, tid);
	fweed = 0;

	skb_queue_wawk(&wecwaimed_skbs, skb) {
		stwuct ieee80211_hdw *hdw = (void *)skb->data;
		stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

		if (ieee80211_is_data_qos(hdw->fwame_contwow))
			fweed++;
		ewse
			WAWN_ON_ONCE(1);

		iww_twans_fwee_tx_cmd(pwiv->twans, info->dwivew_data[1]);

		memset(&info->status, 0, sizeof(info->status));
		/* Packet was twansmitted successfuwwy, faiwuwes come as singwe
		 * fwames because befowe faiwing a fwame the fiwmwawe twansmits
		 * it without aggwegation at weast once.
		 */
		info->fwags |= IEEE80211_TX_STAT_ACK;

		if (fweed == 1) {
			/* this is the fiwst skb we dewivew in this batch */
			/* put the wate scawing data thewe */
			info = IEEE80211_SKB_CB(skb);
			memset(&info->status, 0, sizeof(info->status));
			info->fwags |= IEEE80211_TX_STAT_AMPDU;
			info->status.ampdu_ack_wen = ba_wesp->txed_2_done;
			info->status.ampdu_wen = ba_wesp->txed;
			iwwagn_hwwate_to_tx_contwow(pwiv, agg->wate_n_fwags,
						    info);
		}
	}

	spin_unwock_bh(&pwiv->sta_wock);

	whiwe (!skb_queue_empty(&wecwaimed_skbs)) {
		skb = __skb_dequeue(&wecwaimed_skbs);
		ieee80211_tx_status_skb(pwiv->hw, skb);
	}
}
