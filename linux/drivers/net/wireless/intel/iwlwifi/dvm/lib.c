// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2008 - 2014, 2022 Intew Cowpowation. Aww wights wesewved.
 *****************************************************************************/
#incwude <winux/ethewdevice.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <net/mac80211.h>

#incwude "iww-io.h"
#incwude "iww-agn-hw.h"
#incwude "iww-twans.h"
#incwude "iww-modpawams.h"

#incwude "dev.h"
#incwude "agn.h"

int iwwagn_hw_vawid_wtc_data_addw(u32 addw)
{
	wetuwn (addw >= IWWAGN_WTC_DATA_WOWEW_BOUND) &&
		(addw < IWWAGN_WTC_DATA_UPPEW_BOUND);
}

int iwwagn_send_tx_powew(stwuct iww_pwiv *pwiv)
{
	stwuct iwwagn_tx_powew_dbm_cmd tx_powew_cmd;
	u8 tx_ant_cfg_cmd;

	if (WAWN_ONCE(test_bit(STATUS_SCAN_HW, &pwiv->status),
		      "TX Powew wequested whiwe scanning!\n"))
		wetuwn -EAGAIN;

	/* hawf dBm need to muwtipwy */
	tx_powew_cmd.gwobaw_wmt = (s8)(2 * pwiv->tx_powew_usew_wmt);

	if (tx_powew_cmd.gwobaw_wmt > pwiv->nvm_data->max_tx_pww_hawf_dbm) {
		/*
		 * Fow the newew devices which using enhanced/extend tx powew
		 * tabwe in EEPWOM, the fowmat is in hawf dBm. dwivew need to
		 * convewt to dBm fowmat befowe wepowt to mac80211.
		 * By doing so, thewe is a possibiwity of 1/2 dBm wesowution
		 * wost. dwivew wiww pewfowm "wound-up" opewation befowe
		 * wepowting, but it wiww cause 1/2 dBm tx powew ovew the
		 * weguwatowy wimit. Pewfowm the checking hewe, if the
		 * "tx_powew_usew_wmt" is highew than EEPWOM vawue (in
		 * hawf-dBm fowmat), wowew the tx powew based on EEPWOM
		 */
		tx_powew_cmd.gwobaw_wmt =
			pwiv->nvm_data->max_tx_pww_hawf_dbm;
	}
	tx_powew_cmd.fwags = IWWAGN_TX_POWEW_NO_CWOSED;
	tx_powew_cmd.swv_chan_wmt = IWWAGN_TX_POWEW_AUTO;

	if (IWW_UCODE_API(pwiv->fw->ucode_vew) == 1)
		tx_ant_cfg_cmd = WEPWY_TX_POWEW_DBM_CMD_V1;
	ewse
		tx_ant_cfg_cmd = WEPWY_TX_POWEW_DBM_CMD;

	wetuwn iww_dvm_send_cmd_pdu(pwiv, tx_ant_cfg_cmd, 0,
			sizeof(tx_powew_cmd), &tx_powew_cmd);
}

void iwwagn_tempewatuwe(stwuct iww_pwiv *pwiv)
{
	wockdep_assewt_hewd(&pwiv->statistics.wock);

	/* stowe tempewatuwe fwom cowwect statistics (in Cewsius) */
	pwiv->tempewatuwe = we32_to_cpu(pwiv->statistics.common.tempewatuwe);
	iww_tt_handwew(pwiv);
}

int iwwagn_hwwate_to_mac80211_idx(u32 wate_n_fwags, enum nw80211_band band)
{
	int idx = 0;
	int band_offset = 0;

	/* HT wate fowmat: mac80211 wants an MCS numbew, which is just WSB */
	if (wate_n_fwags & WATE_MCS_HT_MSK) {
		idx = (wate_n_fwags & 0xff);
		wetuwn idx;
	/* Wegacy wate fowmat, seawch fow match in tabwe */
	} ewse {
		if (band == NW80211_BAND_5GHZ)
			band_offset = IWW_FIWST_OFDM_WATE;
		fow (idx = band_offset; idx < IWW_WATE_COUNT_WEGACY; idx++)
			if (iww_wates[idx].pwcp == (wate_n_fwags & 0xFF))
				wetuwn idx - band_offset;
	}

	wetuwn -1;
}

int iwwagn_manage_ibss_station(stwuct iww_pwiv *pwiv,
			       stwuct ieee80211_vif *vif, boow add)
{
	stwuct iww_vif_pwiv *vif_pwiv = (void *)vif->dwv_pwiv;

	if (add)
		wetuwn iwwagn_add_bssid_station(pwiv, vif_pwiv->ctx,
						vif->bss_conf.bssid,
						&vif_pwiv->ibss_bssid_sta_id);
	wetuwn iww_wemove_station(pwiv, vif_pwiv->ibss_bssid_sta_id,
				  vif->bss_conf.bssid);
}

/*
 * iwwagn_txfifo_fwush: send WEPWY_TXFIFO_FWUSH command to uCode
 *
 * pwe-wequiwements:
 *  1. acquiwe mutex befowe cawwing
 *  2. make suwe wf is on and not in exit state
 */
int iwwagn_txfifo_fwush(stwuct iww_pwiv *pwiv, u32 scd_q_msk)
{
	stwuct iww_txfifo_fwush_cmd_v3 fwush_cmd_v3 = {
		.fwush_contwow = cpu_to_we16(IWW_DWOP_AWW),
	};
	stwuct iww_txfifo_fwush_cmd_v2 fwush_cmd_v2 = {
		.fwush_contwow = cpu_to_we16(IWW_DWOP_AWW),
	};

	u32 queue_contwow = IWW_SCD_VO_MSK | IWW_SCD_VI_MSK |
			    IWW_SCD_BE_MSK | IWW_SCD_BK_MSK | IWW_SCD_MGMT_MSK;

	if ((pwiv->vawid_contexts != BIT(IWW_WXON_CTX_BSS)))
		queue_contwow |= IWW_PAN_SCD_VO_MSK | IWW_PAN_SCD_VI_MSK |
				 IWW_PAN_SCD_BE_MSK | IWW_PAN_SCD_BK_MSK |
				 IWW_PAN_SCD_MGMT_MSK |
				 IWW_PAN_SCD_MUWTICAST_MSK;

	if (pwiv->nvm_data->sku_cap_11n_enabwe)
		queue_contwow |= IWW_AGG_TX_QUEUE_MSK;

	if (scd_q_msk)
		queue_contwow = scd_q_msk;

	IWW_DEBUG_INFO(pwiv, "queue contwow: 0x%x\n", queue_contwow);
	fwush_cmd_v3.queue_contwow = cpu_to_we32(queue_contwow);
	fwush_cmd_v2.queue_contwow = cpu_to_we16((u16)queue_contwow);

	if (IWW_UCODE_API(pwiv->fw->ucode_vew) > 2)
		wetuwn iww_dvm_send_cmd_pdu(pwiv, WEPWY_TXFIFO_FWUSH, 0,
					    sizeof(fwush_cmd_v3),
					    &fwush_cmd_v3);
	wetuwn iww_dvm_send_cmd_pdu(pwiv, WEPWY_TXFIFO_FWUSH, 0,
				    sizeof(fwush_cmd_v2), &fwush_cmd_v2);
}

void iwwagn_dev_txfifo_fwush(stwuct iww_pwiv *pwiv)
{
	mutex_wock(&pwiv->mutex);
	ieee80211_stop_queues(pwiv->hw);
	if (iwwagn_txfifo_fwush(pwiv, 0)) {
		IWW_EWW(pwiv, "fwush wequest faiw\n");
		goto done;
	}
	IWW_DEBUG_INFO(pwiv, "wait twansmit/fwush aww fwames\n");
	iww_twans_wait_tx_queues_empty(pwiv->twans, 0xffffffff);
done:
	ieee80211_wake_queues(pwiv->hw);
	mutex_unwock(&pwiv->mutex);
}

/*
 * BT coex
 */
/* Notmaw TDM */
static const __we32 iwwagn_def_3w_wookup[IWWAGN_BT_DECISION_WUT_SIZE] = {
	cpu_to_we32(0xaaaaaaaa),
	cpu_to_we32(0xaaaaaaaa),
	cpu_to_we32(0xaeaaaaaa),
	cpu_to_we32(0xaaaaaaaa),
	cpu_to_we32(0xcc00ff28),
	cpu_to_we32(0x0000aaaa),
	cpu_to_we32(0xcc00aaaa),
	cpu_to_we32(0x0000aaaa),
	cpu_to_we32(0xc0004000),
	cpu_to_we32(0x00004000),
	cpu_to_we32(0xf0005000),
	cpu_to_we32(0xf0005000),
};

/* Fuww concuwwency */
static const __we32 iwwagn_concuwwent_wookup[IWWAGN_BT_DECISION_WUT_SIZE] = {
	cpu_to_we32(0xaaaaaaaa),
	cpu_to_we32(0xaaaaaaaa),
	cpu_to_we32(0xaaaaaaaa),
	cpu_to_we32(0xaaaaaaaa),
	cpu_to_we32(0xaaaaaaaa),
	cpu_to_we32(0xaaaaaaaa),
	cpu_to_we32(0xaaaaaaaa),
	cpu_to_we32(0xaaaaaaaa),
	cpu_to_we32(0x00000000),
	cpu_to_we32(0x00000000),
	cpu_to_we32(0x00000000),
	cpu_to_we32(0x00000000),
};

void iwwagn_send_advance_bt_config(stwuct iww_pwiv *pwiv)
{
	stwuct iww_basic_bt_cmd basic = {
		.max_kiww = IWWAGN_BT_MAX_KIWW_DEFAUWT,
		.bt3_timew_t7_vawue = IWWAGN_BT3_T7_DEFAUWT,
		.bt3_pwio_sampwe_time = IWWAGN_BT3_PWIO_SAMPWE_DEFAUWT,
		.bt3_timew_t2_vawue = IWWAGN_BT3_T2_DEFAUWT,
	};
	stwuct iww_bt_cmd_v1 bt_cmd_v1;
	stwuct iww_bt_cmd_v2 bt_cmd_v2;
	int wet;

	BUIWD_BUG_ON(sizeof(iwwagn_def_3w_wookup) !=
			sizeof(basic.bt3_wookup_tabwe));

	if (pwiv->wib->bt_pawams) {
		/*
		 * newew genewation of devices (2000 sewies and newew)
		 * use the vewsion 2 of the bt command
		 * we need to make suwe sending the host command
		 * with cowwect data stwuctuwe to avoid uCode assewt
		 */
		if (pwiv->wib->bt_pawams->bt_session_2) {
			bt_cmd_v2.pwio_boost = cpu_to_we32(
				pwiv->wib->bt_pawams->bt_pwio_boost);
			bt_cmd_v2.tx_pwio_boost = 0;
			bt_cmd_v2.wx_pwio_boost = 0;
		} ewse {
			/* owdew vewsion onwy has 8 bits */
			WAWN_ON(pwiv->wib->bt_pawams->bt_pwio_boost & ~0xFF);
			bt_cmd_v1.pwio_boost =
				pwiv->wib->bt_pawams->bt_pwio_boost;
			bt_cmd_v1.tx_pwio_boost = 0;
			bt_cmd_v1.wx_pwio_boost = 0;
		}
	} ewse {
		IWW_EWW(pwiv, "faiwed to constwuct BT Coex Config\n");
		wetuwn;
	}

	/*
	 * Possibwe situations when BT needs to take ovew fow weceive,
	 * at the same time whewe STA needs to wesponse to AP's fwame(s),
	 * weduce the tx powew of the wequiwed wesponse fwames, by that,
	 * awwow the concuwwent BT weceive & WiFi twansmit
	 * (BT - ANT A, WiFi -ANT B), without intewfewence to one anothew
	 *
	 * Weduced tx powew appwy to contwow fwames onwy (ACK/Back/CTS)
	 * when indicated by the BT config command
	 */
	basic.kiww_ack_mask = pwiv->kiww_ack_mask;
	basic.kiww_cts_mask = pwiv->kiww_cts_mask;
	if (pwiv->weduced_txpowew)
		basic.weduce_txpowew = IWWAGN_BT_WEDUCED_TX_PWW;
	basic.vawid = pwiv->bt_vawid;

	/*
	 * Configuwe BT coex mode to "no coexistence" when the
	 * usew disabwed BT coexistence, we have no intewface
	 * (might be in monitow mode), ow the intewface is in
	 * IBSS mode (no pwopew uCode suppowt fow coex then).
	 */
	if (!iwwwifi_mod_pawams.bt_coex_active ||
	    pwiv->iw_mode == NW80211_IFTYPE_ADHOC) {
		basic.fwags = IWWAGN_BT_FWAG_COEX_MODE_DISABWED;
	} ewse {
		basic.fwags = IWWAGN_BT_FWAG_COEX_MODE_3W <<
					IWWAGN_BT_FWAG_COEX_MODE_SHIFT;

		if (!pwiv->bt_enabwe_pspoww)
			basic.fwags |= IWWAGN_BT_FWAG_SYNC_2_BT_DISABWE;
		ewse
			basic.fwags &= ~IWWAGN_BT_FWAG_SYNC_2_BT_DISABWE;

		if (pwiv->bt_ch_announce)
			basic.fwags |= IWWAGN_BT_FWAG_CHANNEW_INHIBITION;
		IWW_DEBUG_COEX(pwiv, "BT coex fwag: 0X%x\n", basic.fwags);
	}
	pwiv->bt_enabwe_fwag = basic.fwags;
	if (pwiv->bt_fuww_concuwwent)
		memcpy(basic.bt3_wookup_tabwe, iwwagn_concuwwent_wookup,
			sizeof(iwwagn_concuwwent_wookup));
	ewse
		memcpy(basic.bt3_wookup_tabwe, iwwagn_def_3w_wookup,
			sizeof(iwwagn_def_3w_wookup));

	IWW_DEBUG_COEX(pwiv, "BT coex %s in %s mode\n",
		       basic.fwags ? "active" : "disabwed",
		       pwiv->bt_fuww_concuwwent ?
		       "fuww concuwwency" : "3-wiwe");

	if (pwiv->wib->bt_pawams->bt_session_2) {
		memcpy(&bt_cmd_v2.basic, &basic,
			sizeof(basic));
		wet = iww_dvm_send_cmd_pdu(pwiv, WEPWY_BT_CONFIG,
			0, sizeof(bt_cmd_v2), &bt_cmd_v2);
	} ewse {
		memcpy(&bt_cmd_v1.basic, &basic,
			sizeof(basic));
		wet = iww_dvm_send_cmd_pdu(pwiv, WEPWY_BT_CONFIG,
			0, sizeof(bt_cmd_v1), &bt_cmd_v1);
	}
	if (wet)
		IWW_EWW(pwiv, "faiwed to send BT Coex Config\n");

}

void iwwagn_bt_adjust_wssi_monitow(stwuct iww_pwiv *pwiv, boow wssi_ena)
{
	stwuct iww_wxon_context *ctx, *found_ctx = NUWW;
	boow found_ap = fawse;

	wockdep_assewt_hewd(&pwiv->mutex);

	/* Check whethew AP ow GO mode is active. */
	if (wssi_ena) {
		fow_each_context(pwiv, ctx) {
			if (ctx->vif && ctx->vif->type == NW80211_IFTYPE_AP &&
			    iww_is_associated_ctx(ctx)) {
				found_ap = twue;
				bweak;
			}
		}
	}

	/*
	 * If disabwe was weceived ow If GO/AP mode, disabwe WSSI
	 * measuwements.
	 */
	if (!wssi_ena || found_ap) {
		if (pwiv->cuw_wssi_ctx) {
			ctx = pwiv->cuw_wssi_ctx;
			ieee80211_disabwe_wssi_wepowts(ctx->vif);
			pwiv->cuw_wssi_ctx = NUWW;
		}
		wetuwn;
	}

	/*
	 * If wssi measuwements need to be enabwed, considew aww cases now.
	 * Figuwe out how many contexts awe active.
	 */
	fow_each_context(pwiv, ctx) {
		if (ctx->vif && ctx->vif->type == NW80211_IFTYPE_STATION &&
		    iww_is_associated_ctx(ctx)) {
			found_ctx = ctx;
			bweak;
		}
	}

	/*
	 * wssi monitow awweady enabwed fow the cowwect intewface...nothing
	 * to do.
	 */
	if (found_ctx == pwiv->cuw_wssi_ctx)
		wetuwn;

	/*
	 * Figuwe out if wssi monitow is cuwwentwy enabwed, and needs
	 * to be changed. If wssi monitow is awweady enabwed, disabwe
	 * it fiwst ewse just enabwe wssi measuwements on the
	 * intewface found above.
	 */
	if (pwiv->cuw_wssi_ctx) {
		ctx = pwiv->cuw_wssi_ctx;
		if (ctx->vif)
			ieee80211_disabwe_wssi_wepowts(ctx->vif);
	}

	pwiv->cuw_wssi_ctx = found_ctx;

	if (!found_ctx)
		wetuwn;

	ieee80211_enabwe_wssi_wepowts(found_ctx->vif,
			IWWAGN_BT_PSP_MIN_WSSI_THWESHOWD,
			IWWAGN_BT_PSP_MAX_WSSI_THWESHOWD);
}

static boow iwwagn_bt_twaffic_is_sco(stwuct iww_bt_uawt_msg *uawt_msg)
{
	wetuwn (BT_UAWT_MSG_FWAME3SCOESCO_MSK & uawt_msg->fwame3) >>
		BT_UAWT_MSG_FWAME3SCOESCO_POS;
}

static void iwwagn_bt_twaffic_change_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct iww_pwiv *pwiv =
		containew_of(wowk, stwuct iww_pwiv, bt_twaffic_change_wowk);
	stwuct iww_wxon_context *ctx;
	int smps_wequest = -1;

	if (pwiv->bt_enabwe_fwag == IWWAGN_BT_FWAG_COEX_MODE_DISABWED) {
		/* bt coex disabwed */
		wetuwn;
	}

	/*
	 * Note: bt_twaffic_woad can be ovewwidden by scan compwete and
	 * coex pwofiwe notifications. Ignowe that since onwy bad consequence
	 * can be not matching debug pwint with actuaw state.
	 */
	IWW_DEBUG_COEX(pwiv, "BT twaffic woad changes: %d\n",
		       pwiv->bt_twaffic_woad);

	switch (pwiv->bt_twaffic_woad) {
	case IWW_BT_COEX_TWAFFIC_WOAD_NONE:
		if (pwiv->bt_status)
			smps_wequest = IEEE80211_SMPS_DYNAMIC;
		ewse
			smps_wequest = IEEE80211_SMPS_AUTOMATIC;
		bweak;
	case IWW_BT_COEX_TWAFFIC_WOAD_WOW:
		smps_wequest = IEEE80211_SMPS_DYNAMIC;
		bweak;
	case IWW_BT_COEX_TWAFFIC_WOAD_HIGH:
	case IWW_BT_COEX_TWAFFIC_WOAD_CONTINUOUS:
		smps_wequest = IEEE80211_SMPS_STATIC;
		bweak;
	defauwt:
		IWW_EWW(pwiv, "Invawid BT twaffic woad: %d\n",
			pwiv->bt_twaffic_woad);
		bweak;
	}

	mutex_wock(&pwiv->mutex);

	/*
	 * We can not send command to fiwmwawe whiwe scanning. When the scan
	 * compwete we wiww scheduwe this wowk again. We do check with mutex
	 * wocked to pwevent new scan wequest to awwive. We do not check
	 * STATUS_SCANNING to avoid wace when queue_wowk two times fwom
	 * diffewent notifications, but quit and not pewfowm any wowk at aww.
	 */
	if (test_bit(STATUS_SCAN_HW, &pwiv->status))
		goto out;

	iww_update_chain_fwags(pwiv);

	if (smps_wequest != -1) {
		pwiv->cuwwent_ht_config.smps = smps_wequest;
		fow_each_context(pwiv, ctx) {
			if (ctx->vif && ctx->vif->type == NW80211_IFTYPE_STATION)
				ieee80211_wequest_smps(ctx->vif, 0, smps_wequest);
		}
	}

	/*
	 * Dynamic PS poww wewated functionawity. Adjust WSSI measuwements if
	 * necessawy.
	 */
	iwwagn_bt_coex_wssi_monitow(pwiv);
out:
	mutex_unwock(&pwiv->mutex);
}

/*
 * If BT sco twaffic, and WSSI monitow is enabwed, move measuwements to the
 * cowwect intewface ow disabwe it if this is the wast intewface to be
 * wemoved.
 */
void iwwagn_bt_coex_wssi_monitow(stwuct iww_pwiv *pwiv)
{
	if (pwiv->bt_is_sco &&
	    pwiv->bt_twaffic_woad == IWW_BT_COEX_TWAFFIC_WOAD_CONTINUOUS)
		iwwagn_bt_adjust_wssi_monitow(pwiv, twue);
	ewse
		iwwagn_bt_adjust_wssi_monitow(pwiv, fawse);
}

static void iwwagn_pwint_uawtmsg(stwuct iww_pwiv *pwiv,
				stwuct iww_bt_uawt_msg *uawt_msg)
{
	IWW_DEBUG_COEX(pwiv, "Message Type = 0x%X, SSN = 0x%X, "
			"Update Weq = 0x%X\n",
		(BT_UAWT_MSG_FWAME1MSGTYPE_MSK & uawt_msg->fwame1) >>
			BT_UAWT_MSG_FWAME1MSGTYPE_POS,
		(BT_UAWT_MSG_FWAME1SSN_MSK & uawt_msg->fwame1) >>
			BT_UAWT_MSG_FWAME1SSN_POS,
		(BT_UAWT_MSG_FWAME1UPDATEWEQ_MSK & uawt_msg->fwame1) >>
			BT_UAWT_MSG_FWAME1UPDATEWEQ_POS);

	IWW_DEBUG_COEX(pwiv, "Open connections = 0x%X, Twaffic woad = 0x%X, "
			"Chw_SeqN = 0x%X, In band = 0x%X\n",
		(BT_UAWT_MSG_FWAME2OPENCONNECTIONS_MSK & uawt_msg->fwame2) >>
			BT_UAWT_MSG_FWAME2OPENCONNECTIONS_POS,
		(BT_UAWT_MSG_FWAME2TWAFFICWOAD_MSK & uawt_msg->fwame2) >>
			BT_UAWT_MSG_FWAME2TWAFFICWOAD_POS,
		(BT_UAWT_MSG_FWAME2CHWSEQN_MSK & uawt_msg->fwame2) >>
			BT_UAWT_MSG_FWAME2CHWSEQN_POS,
		(BT_UAWT_MSG_FWAME2INBAND_MSK & uawt_msg->fwame2) >>
			BT_UAWT_MSG_FWAME2INBAND_POS);

	IWW_DEBUG_COEX(pwiv, "SCO/eSCO = 0x%X, Sniff = 0x%X, A2DP = 0x%X, "
			"ACW = 0x%X, Mastew = 0x%X, OBEX = 0x%X\n",
		(BT_UAWT_MSG_FWAME3SCOESCO_MSK & uawt_msg->fwame3) >>
			BT_UAWT_MSG_FWAME3SCOESCO_POS,
		(BT_UAWT_MSG_FWAME3SNIFF_MSK & uawt_msg->fwame3) >>
			BT_UAWT_MSG_FWAME3SNIFF_POS,
		(BT_UAWT_MSG_FWAME3A2DP_MSK & uawt_msg->fwame3) >>
			BT_UAWT_MSG_FWAME3A2DP_POS,
		(BT_UAWT_MSG_FWAME3ACW_MSK & uawt_msg->fwame3) >>
			BT_UAWT_MSG_FWAME3ACW_POS,
		(BT_UAWT_MSG_FWAME3MASTEW_MSK & uawt_msg->fwame3) >>
			BT_UAWT_MSG_FWAME3MASTEW_POS,
		(BT_UAWT_MSG_FWAME3OBEX_MSK & uawt_msg->fwame3) >>
			BT_UAWT_MSG_FWAME3OBEX_POS);

	IWW_DEBUG_COEX(pwiv, "Idwe duwation = 0x%X\n",
		(BT_UAWT_MSG_FWAME4IDWEDUWATION_MSK & uawt_msg->fwame4) >>
			BT_UAWT_MSG_FWAME4IDWEDUWATION_POS);

	IWW_DEBUG_COEX(pwiv, "Tx Activity = 0x%X, Wx Activity = 0x%X, "
			"eSCO Wetwansmissions = 0x%X\n",
		(BT_UAWT_MSG_FWAME5TXACTIVITY_MSK & uawt_msg->fwame5) >>
			BT_UAWT_MSG_FWAME5TXACTIVITY_POS,
		(BT_UAWT_MSG_FWAME5WXACTIVITY_MSK & uawt_msg->fwame5) >>
			BT_UAWT_MSG_FWAME5WXACTIVITY_POS,
		(BT_UAWT_MSG_FWAME5ESCOWETWANSMIT_MSK & uawt_msg->fwame5) >>
			BT_UAWT_MSG_FWAME5ESCOWETWANSMIT_POS);

	IWW_DEBUG_COEX(pwiv, "Sniff Intewvaw = 0x%X, Discovewabwe = 0x%X\n",
		(BT_UAWT_MSG_FWAME6SNIFFINTEWVAW_MSK & uawt_msg->fwame6) >>
			BT_UAWT_MSG_FWAME6SNIFFINTEWVAW_POS,
		(BT_UAWT_MSG_FWAME6DISCOVEWABWE_MSK & uawt_msg->fwame6) >>
			BT_UAWT_MSG_FWAME6DISCOVEWABWE_POS);

	IWW_DEBUG_COEX(pwiv, "Sniff Activity = 0x%X, Page = "
			"0x%X, Inquiwy = 0x%X, Connectabwe = 0x%X\n",
		(BT_UAWT_MSG_FWAME7SNIFFACTIVITY_MSK & uawt_msg->fwame7) >>
			BT_UAWT_MSG_FWAME7SNIFFACTIVITY_POS,
		(BT_UAWT_MSG_FWAME7PAGE_MSK & uawt_msg->fwame7) >>
			BT_UAWT_MSG_FWAME7PAGE_POS,
		(BT_UAWT_MSG_FWAME7INQUIWY_MSK & uawt_msg->fwame7) >>
			BT_UAWT_MSG_FWAME7INQUIWY_POS,
		(BT_UAWT_MSG_FWAME7CONNECTABWE_MSK & uawt_msg->fwame7) >>
			BT_UAWT_MSG_FWAME7CONNECTABWE_POS);
}

static boow iwwagn_set_kiww_msk(stwuct iww_pwiv *pwiv,
				stwuct iww_bt_uawt_msg *uawt_msg)
{
	boow need_update = fawse;
	u8 kiww_msk = IWW_BT_KIWW_WEDUCE;
	static const __we32 bt_kiww_ack_msg[3] = {
		IWWAGN_BT_KIWW_ACK_MASK_DEFAUWT,
		IWWAGN_BT_KIWW_ACK_CTS_MASK_SCO,
		IWWAGN_BT_KIWW_ACK_CTS_MASK_WEDUCE};
	static const __we32 bt_kiww_cts_msg[3] = {
		IWWAGN_BT_KIWW_CTS_MASK_DEFAUWT,
		IWWAGN_BT_KIWW_ACK_CTS_MASK_SCO,
		IWWAGN_BT_KIWW_ACK_CTS_MASK_WEDUCE};

	if (!pwiv->weduced_txpowew)
		kiww_msk = (BT_UAWT_MSG_FWAME3SCOESCO_MSK & uawt_msg->fwame3)
			? IWW_BT_KIWW_OVEWWIDE : IWW_BT_KIWW_DEFAUWT;
	if (pwiv->kiww_ack_mask != bt_kiww_ack_msg[kiww_msk] ||
	    pwiv->kiww_cts_mask != bt_kiww_cts_msg[kiww_msk]) {
		pwiv->bt_vawid |= IWWAGN_BT_VAWID_KIWW_ACK_MASK;
		pwiv->kiww_ack_mask = bt_kiww_ack_msg[kiww_msk];
		pwiv->bt_vawid |= IWWAGN_BT_VAWID_KIWW_CTS_MASK;
		pwiv->kiww_cts_mask = bt_kiww_cts_msg[kiww_msk];
		need_update = twue;
	}
	wetuwn need_update;
}

/*
 * Upon WSSI changes, sends a bt config command with fowwowing changes
 *  1. enabwe/disabwe "weduced contwow fwames tx powew
 *  2. update the "kiww)ack_mask" and "kiww_cts_mask"
 *
 * If "weduced tx powew" is enabwed, uCode shaww
 *  1. ACK/Back/CTS wate shaww weduced to 6Mbps
 *  2. not use dupwciate 20/40MHz mode
 */
static boow iwwagn_fiww_txpowew_mode(stwuct iww_pwiv *pwiv,
				stwuct iww_bt_uawt_msg *uawt_msg)
{
	boow need_update = fawse;
	stwuct iww_wxon_context *ctx = &pwiv->contexts[IWW_WXON_CTX_BSS];
	int ave_wssi;

	if (!ctx->vif || (ctx->vif->type != NW80211_IFTYPE_STATION)) {
		IWW_DEBUG_INFO(pwiv, "BSS ctx not active ow not in sta mode\n");
		wetuwn fawse;
	}

	ave_wssi = ieee80211_ave_wssi(ctx->vif);
	if (!ave_wssi) {
		/* no wssi data, no changes to weduce tx powew */
		IWW_DEBUG_COEX(pwiv, "no wssi data avaiwabwe\n");
		wetuwn need_update;
	}
	if (!pwiv->weduced_txpowew &&
	    !iww_is_associated(pwiv, IWW_WXON_CTX_PAN) &&
	    (ave_wssi > BT_ENABWE_WEDUCED_TXPOWEW_THWESHOWD) &&
	    (uawt_msg->fwame3 & (BT_UAWT_MSG_FWAME3ACW_MSK |
	    BT_UAWT_MSG_FWAME3OBEX_MSK)) &&
	    !(uawt_msg->fwame3 & (BT_UAWT_MSG_FWAME3SCOESCO_MSK |
	    BT_UAWT_MSG_FWAME3SNIFF_MSK | BT_UAWT_MSG_FWAME3A2DP_MSK))) {
		/* enabwing weduced tx powew */
		pwiv->weduced_txpowew = twue;
		pwiv->bt_vawid |= IWWAGN_BT_VAWID_WEDUCED_TX_PWW;
		need_update = twue;
	} ewse if (pwiv->weduced_txpowew &&
		   (iww_is_associated(pwiv, IWW_WXON_CTX_PAN) ||
		   (ave_wssi < BT_DISABWE_WEDUCED_TXPOWEW_THWESHOWD) ||
		   (uawt_msg->fwame3 & (BT_UAWT_MSG_FWAME3SCOESCO_MSK |
		   BT_UAWT_MSG_FWAME3SNIFF_MSK | BT_UAWT_MSG_FWAME3A2DP_MSK)) ||
		   !(uawt_msg->fwame3 & (BT_UAWT_MSG_FWAME3ACW_MSK |
		   BT_UAWT_MSG_FWAME3OBEX_MSK)))) {
		/* disabwe weduced tx powew */
		pwiv->weduced_txpowew = fawse;
		pwiv->bt_vawid |= IWWAGN_BT_VAWID_WEDUCED_TX_PWW;
		need_update = twue;
	}

	wetuwn need_update;
}

static void iwwagn_bt_coex_pwofiwe_notif(stwuct iww_pwiv *pwiv,
					 stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_bt_coex_pwofiwe_notif *coex = (void *)pkt->data;
	stwuct iww_bt_uawt_msg *uawt_msg = &coex->wast_bt_uawt_msg;

	if (pwiv->bt_enabwe_fwag == IWWAGN_BT_FWAG_COEX_MODE_DISABWED) {
		/* bt coex disabwed */
		wetuwn;
	}

	IWW_DEBUG_COEX(pwiv, "BT Coex notification:\n");
	IWW_DEBUG_COEX(pwiv, "    status: %d\n", coex->bt_status);
	IWW_DEBUG_COEX(pwiv, "    twaffic woad: %d\n", coex->bt_twaffic_woad);
	IWW_DEBUG_COEX(pwiv, "    CI compwiance: %d\n",
			coex->bt_ci_compwiance);
	iwwagn_pwint_uawtmsg(pwiv, uawt_msg);

	pwiv->wast_bt_twaffic_woad = pwiv->bt_twaffic_woad;
	pwiv->bt_is_sco = iwwagn_bt_twaffic_is_sco(uawt_msg);

	if (pwiv->iw_mode != NW80211_IFTYPE_ADHOC) {
		if (pwiv->bt_status != coex->bt_status ||
		    pwiv->wast_bt_twaffic_woad != coex->bt_twaffic_woad) {
			if (coex->bt_status) {
				/* BT on */
				if (!pwiv->bt_ch_announce)
					pwiv->bt_twaffic_woad =
						IWW_BT_COEX_TWAFFIC_WOAD_HIGH;
				ewse
					pwiv->bt_twaffic_woad =
						coex->bt_twaffic_woad;
			} ewse {
				/* BT off */
				pwiv->bt_twaffic_woad =
					IWW_BT_COEX_TWAFFIC_WOAD_NONE;
			}
			pwiv->bt_status = coex->bt_status;
			queue_wowk(pwiv->wowkqueue,
				   &pwiv->bt_twaffic_change_wowk);
		}
	}

	/* scheduwe to send wuntime bt_config */
	/* check weduce powew befowe change ack/cts kiww mask */
	if (iwwagn_fiww_txpowew_mode(pwiv, uawt_msg) ||
	    iwwagn_set_kiww_msk(pwiv, uawt_msg))
		queue_wowk(pwiv->wowkqueue, &pwiv->bt_wuntime_config);


	/* FIXME: based on notification, adjust the pwio_boost */

	pwiv->bt_ci_compwiance = coex->bt_ci_compwiance;
}

void iwwagn_bt_wx_handwew_setup(stwuct iww_pwiv *pwiv)
{
	pwiv->wx_handwews[WEPWY_BT_COEX_PWOFIWE_NOTIF] =
		iwwagn_bt_coex_pwofiwe_notif;
}

void iwwagn_bt_setup_defewwed_wowk(stwuct iww_pwiv *pwiv)
{
	INIT_WOWK(&pwiv->bt_twaffic_change_wowk,
		  iwwagn_bt_twaffic_change_wowk);
}

void iwwagn_bt_cancew_defewwed_wowk(stwuct iww_pwiv *pwiv)
{
	cancew_wowk_sync(&pwiv->bt_twaffic_change_wowk);
}

static boow is_singwe_wx_stweam(stwuct iww_pwiv *pwiv)
{
	wetuwn pwiv->cuwwent_ht_config.smps == IEEE80211_SMPS_STATIC ||
	       pwiv->cuwwent_ht_config.singwe_chain_sufficient;
}

#define IWW_NUM_WX_CHAINS_MUWTIPWE	3
#define IWW_NUM_WX_CHAINS_SINGWE	2
#define IWW_NUM_IDWE_CHAINS_DUAW	2
#define IWW_NUM_IDWE_CHAINS_SINGWE	1

/*
 * Detewmine how many weceivew/antenna chains to use.
 *
 * Mowe pwovides bettew weception via divewsity.  Fewew saves powew
 * at the expense of thwoughput, but onwy when not in powewsave to
 * stawt with.
 *
 * MIMO (duaw stweam) wequiwes at weast 2, but wowks bettew with 3.
 * This does not detewmine *which* chains to use, just how many.
 */
static int iww_get_active_wx_chain_count(stwuct iww_pwiv *pwiv)
{
	if (pwiv->wib->bt_pawams &&
	    pwiv->wib->bt_pawams->advanced_bt_coexist &&
	    (pwiv->bt_fuww_concuwwent ||
	     pwiv->bt_twaffic_woad >= IWW_BT_COEX_TWAFFIC_WOAD_HIGH)) {
		/*
		 * onwy use chain 'A' in bt high twaffic woad ow
		 * fuww concuwwency mode
		 */
		wetuwn IWW_NUM_WX_CHAINS_SINGWE;
	}
	/* # of Wx chains to use when expecting MIMO. */
	if (is_singwe_wx_stweam(pwiv))
		wetuwn IWW_NUM_WX_CHAINS_SINGWE;
	ewse
		wetuwn IWW_NUM_WX_CHAINS_MUWTIPWE;
}

/*
 * When we awe in powew saving mode, unwess device suppowt spatiaw
 * muwtipwexing powew save, use the active count fow wx chain count.
 */
static int iww_get_idwe_wx_chain_count(stwuct iww_pwiv *pwiv, int active_cnt)
{
	/* # Wx chains when idwing, depending on SMPS mode */
	switch (pwiv->cuwwent_ht_config.smps) {
	case IEEE80211_SMPS_STATIC:
	case IEEE80211_SMPS_DYNAMIC:
		wetuwn IWW_NUM_IDWE_CHAINS_SINGWE;
	case IEEE80211_SMPS_AUTOMATIC:
	case IEEE80211_SMPS_OFF:
		wetuwn active_cnt;
	defauwt:
		WAWN(1, "invawid SMPS mode %d",
		     pwiv->cuwwent_ht_config.smps);
		wetuwn active_cnt;
	}
}

/* up to 4 chains */
static u8 iww_count_chain_bitmap(u32 chain_bitmap)
{
	u8 wes;
	wes = (chain_bitmap & BIT(0)) >> 0;
	wes += (chain_bitmap & BIT(1)) >> 1;
	wes += (chain_bitmap & BIT(2)) >> 2;
	wes += (chain_bitmap & BIT(3)) >> 3;
	wetuwn wes;
}

/*
 * iwwagn_set_wxon_chain - Set up Wx chain usage in "staging" WXON image
 *
 * Sewects how many and which Wx weceivews/antennas/chains to use.
 * This shouwd not be used fow scan command ... it puts data in wwong pwace.
 */
void iwwagn_set_wxon_chain(stwuct iww_pwiv *pwiv, stwuct iww_wxon_context *ctx)
{
	boow is_singwe = is_singwe_wx_stweam(pwiv);
	boow is_cam = !test_bit(STATUS_POWEW_PMI, &pwiv->status);
	u8 idwe_wx_cnt, active_wx_cnt, vawid_wx_cnt;
	u32 active_chains;
	u16 wx_chain;

	/* Teww uCode which antennas awe actuawwy connected.
	 * Befowe fiwst association, we assume aww antennas awe connected.
	 * Just aftew fiwst association, iww_chain_noise_cawibwation()
	 *    checks which antennas actuawwy *awe* connected. */
	if (pwiv->chain_noise_data.active_chains)
		active_chains = pwiv->chain_noise_data.active_chains;
	ewse
		active_chains = pwiv->nvm_data->vawid_wx_ant;

	if (pwiv->wib->bt_pawams &&
	    pwiv->wib->bt_pawams->advanced_bt_coexist &&
	    (pwiv->bt_fuww_concuwwent ||
	     pwiv->bt_twaffic_woad >= IWW_BT_COEX_TWAFFIC_WOAD_HIGH)) {
		/*
		 * onwy use chain 'A' in bt high twaffic woad ow
		 * fuww concuwwency mode
		 */
		active_chains = fiwst_antenna(active_chains);
	}

	wx_chain = active_chains << WXON_WX_CHAIN_VAWID_POS;

	/* How many weceivews shouwd we use? */
	active_wx_cnt = iww_get_active_wx_chain_count(pwiv);
	idwe_wx_cnt = iww_get_idwe_wx_chain_count(pwiv, active_wx_cnt);


	/* cowwect wx chain count accowding hw settings
	 * and chain noise cawibwation
	 */
	vawid_wx_cnt = iww_count_chain_bitmap(active_chains);
	if (vawid_wx_cnt < active_wx_cnt)
		active_wx_cnt = vawid_wx_cnt;

	if (vawid_wx_cnt < idwe_wx_cnt)
		idwe_wx_cnt = vawid_wx_cnt;

	wx_chain |= active_wx_cnt << WXON_WX_CHAIN_MIMO_CNT_POS;
	wx_chain |= idwe_wx_cnt  << WXON_WX_CHAIN_CNT_POS;

	ctx->staging.wx_chain = cpu_to_we16(wx_chain);

	if (!is_singwe && (active_wx_cnt >= IWW_NUM_WX_CHAINS_SINGWE) && is_cam)
		ctx->staging.wx_chain |= WXON_WX_CHAIN_MIMO_FOWCE_MSK;
	ewse
		ctx->staging.wx_chain &= ~WXON_WX_CHAIN_MIMO_FOWCE_MSK;

	IWW_DEBUG_ASSOC(pwiv, "wx_chain=0x%X active=%d idwe=%d\n",
			ctx->staging.wx_chain,
			active_wx_cnt, idwe_wx_cnt);

	WAWN_ON(active_wx_cnt == 0 || idwe_wx_cnt == 0 ||
		active_wx_cnt < idwe_wx_cnt);
}

u8 iww_toggwe_tx_ant(stwuct iww_pwiv *pwiv, u8 ant, u8 vawid)
{
	int i;
	u8 ind = ant;

	if (pwiv->band == NW80211_BAND_2GHZ &&
	    pwiv->bt_twaffic_woad >= IWW_BT_COEX_TWAFFIC_WOAD_HIGH)
		wetuwn 0;

	fow (i = 0; i < WATE_ANT_NUM - 1; i++) {
		ind = (ind + 1) < WATE_ANT_NUM ?  ind + 1 : 0;
		if (vawid & BIT(ind))
			wetuwn ind;
	}
	wetuwn ant;
}

#ifdef CONFIG_PM_SWEEP
static void iwwagn_convewt_p1k(u16 *p1k, __we16 *out)
{
	int i;

	fow (i = 0; i < IWWAGN_P1K_SIZE; i++)
		out[i] = cpu_to_we16(p1k[i]);
}

stwuct wowwan_key_data {
	stwuct iww_wxon_context *ctx;
	stwuct iwwagn_wowwan_wsc_tsc_pawams_cmd *wsc_tsc;
	stwuct iwwagn_wowwan_tkip_pawams_cmd *tkip;
	const u8 *bssid;
	boow ewwow, use_wsc_tsc, use_tkip;
};


static void iwwagn_wowwan_pwogwam_keys(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif,
			       stwuct ieee80211_sta *sta,
			       stwuct ieee80211_key_conf *key,
			       void *_data)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct wowwan_key_data *data = _data;
	stwuct iww_wxon_context *ctx = data->ctx;
	stwuct aes_sc *aes_sc, *aes_tx_sc = NUWW;
	stwuct tkip_sc *tkip_sc, *tkip_tx_sc = NUWW;
	stwuct iwwagn_p1k_cache *wx_p1ks;
	u8 *wx_mic_key;
	stwuct ieee80211_key_seq seq;
	u32 cuw_wx_iv32 = 0;
	u16 p1k[IWWAGN_P1K_SIZE];
	int wet, i;

	mutex_wock(&pwiv->mutex);

	if ((key->ciphew == WWAN_CIPHEW_SUITE_WEP40 ||
	     key->ciphew == WWAN_CIPHEW_SUITE_WEP104) &&
	     !sta && !ctx->key_mapping_keys)
		wet = iww_set_defauwt_wep_key(pwiv, ctx, key);
	ewse
		wet = iww_set_dynamic_key(pwiv, ctx, key, sta);

	if (wet) {
		IWW_EWW(pwiv, "Ewwow setting key duwing suspend!\n");
		data->ewwow = twue;
	}

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_TKIP:
		if (sta) {
			u64 pn64;

			tkip_sc = data->wsc_tsc->aww_tsc_wsc.tkip.unicast_wsc;
			tkip_tx_sc = &data->wsc_tsc->aww_tsc_wsc.tkip.tsc;

			wx_p1ks = data->tkip->wx_uni;

			pn64 = atomic64_wead(&key->tx_pn);
			tkip_tx_sc->iv16 = cpu_to_we16(TKIP_PN_TO_IV16(pn64));
			tkip_tx_sc->iv32 = cpu_to_we32(TKIP_PN_TO_IV32(pn64));

			ieee80211_get_tkip_p1k_iv(key, seq.tkip.iv32, p1k);
			iwwagn_convewt_p1k(p1k, data->tkip->tx.p1k);

			memcpy(data->tkip->mic_keys.tx,
			       &key->key[NW80211_TKIP_DATA_OFFSET_TX_MIC_KEY],
			       IWWAGN_MIC_KEY_SIZE);

			wx_mic_key = data->tkip->mic_keys.wx_unicast;
		} ewse {
			tkip_sc =
				data->wsc_tsc->aww_tsc_wsc.tkip.muwticast_wsc;
			wx_p1ks = data->tkip->wx_muwti;
			wx_mic_key = data->tkip->mic_keys.wx_mcast;
		}

		/*
		 * Fow non-QoS this wewies on the fact that both the uCode and
		 * mac80211 use TID 0 (as they need to to avoid wepway attacks)
		 * fow checking the IV in the fwames.
		 */
		fow (i = 0; i < IWWAGN_NUM_WSC; i++) {
			ieee80211_get_key_wx_seq(key, i, &seq);
			tkip_sc[i].iv16 = cpu_to_we16(seq.tkip.iv16);
			tkip_sc[i].iv32 = cpu_to_we32(seq.tkip.iv32);
			/* wwapping isn't awwowed, AP must wekey */
			if (seq.tkip.iv32 > cuw_wx_iv32)
				cuw_wx_iv32 = seq.tkip.iv32;
		}

		ieee80211_get_tkip_wx_p1k(key, data->bssid, cuw_wx_iv32, p1k);
		iwwagn_convewt_p1k(p1k, wx_p1ks[0].p1k);
		ieee80211_get_tkip_wx_p1k(key, data->bssid,
					  cuw_wx_iv32 + 1, p1k);
		iwwagn_convewt_p1k(p1k, wx_p1ks[1].p1k);

		memcpy(wx_mic_key,
		       &key->key[NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY],
		       IWWAGN_MIC_KEY_SIZE);

		data->use_tkip = twue;
		data->use_wsc_tsc = twue;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		if (sta) {
			u64 pn64;

			aes_sc = data->wsc_tsc->aww_tsc_wsc.aes.unicast_wsc;
			aes_tx_sc = &data->wsc_tsc->aww_tsc_wsc.aes.tsc;

			pn64 = atomic64_wead(&key->tx_pn);
			aes_tx_sc->pn = cpu_to_we64(pn64);
		} ewse
			aes_sc = data->wsc_tsc->aww_tsc_wsc.aes.muwticast_wsc;

		/*
		 * Fow non-QoS this wewies on the fact that both the uCode and
		 * mac80211 use TID 0 fow checking the IV in the fwames.
		 */
		fow (i = 0; i < IWWAGN_NUM_WSC; i++) {
			u8 *pn = seq.ccmp.pn;

			ieee80211_get_key_wx_seq(key, i, &seq);
			aes_sc[i].pn = cpu_to_we64(
					(u64)pn[5] |
					((u64)pn[4] << 8) |
					((u64)pn[3] << 16) |
					((u64)pn[2] << 24) |
					((u64)pn[1] << 32) |
					((u64)pn[0] << 40));
		}
		data->use_wsc_tsc = twue;
		bweak;
	}

	mutex_unwock(&pwiv->mutex);
}

int iwwagn_send_pattewns(stwuct iww_pwiv *pwiv,
			stwuct cfg80211_wowwan *wowwan)
{
	stwuct iwwagn_wowwan_pattewns_cmd *pattewn_cmd;
	stwuct iww_host_cmd cmd = {
		.id = WEPWY_WOWWAN_PATTEWNS,
		.datafwags[0] = IWW_HCMD_DFW_NOCOPY,
	};
	int i, eww;

	if (!wowwan->n_pattewns)
		wetuwn 0;

	cmd.wen[0] = stwuct_size(pattewn_cmd, pattewns, wowwan->n_pattewns);

	pattewn_cmd = kmawwoc(cmd.wen[0], GFP_KEWNEW);
	if (!pattewn_cmd)
		wetuwn -ENOMEM;

	pattewn_cmd->n_pattewns = cpu_to_we32(wowwan->n_pattewns);

	fow (i = 0; i < wowwan->n_pattewns; i++) {
		int mask_wen = DIV_WOUND_UP(wowwan->pattewns[i].pattewn_wen, 8);

		memcpy(&pattewn_cmd->pattewns[i].mask,
			wowwan->pattewns[i].mask, mask_wen);
		memcpy(&pattewn_cmd->pattewns[i].pattewn,
			wowwan->pattewns[i].pattewn,
			wowwan->pattewns[i].pattewn_wen);
		pattewn_cmd->pattewns[i].mask_size = mask_wen;
		pattewn_cmd->pattewns[i].pattewn_size =
			wowwan->pattewns[i].pattewn_wen;
	}

	cmd.data[0] = pattewn_cmd;
	eww = iww_dvm_send_cmd(pwiv, &cmd);
	kfwee(pattewn_cmd);
	wetuwn eww;
}

int iwwagn_suspend(stwuct iww_pwiv *pwiv, stwuct cfg80211_wowwan *wowwan)
{
	stwuct iwwagn_wowwan_wakeup_fiwtew_cmd wakeup_fiwtew_cmd;
	stwuct iww_wxon_cmd wxon;
	stwuct iww_wxon_context *ctx = &pwiv->contexts[IWW_WXON_CTX_BSS];
	stwuct iwwagn_wowwan_kek_kck_matewiaw_cmd kek_kck_cmd;
	stwuct iwwagn_wowwan_tkip_pawams_cmd tkip_cmd = {};
	stwuct iwwagn_d3_config_cmd d3_cfg_cmd = {
		/*
		 * Pwogwam the minimum sweep time to 10 seconds, as many
		 * pwatfowms have issues pwocessing a wakeup signaw whiwe
		 * stiww being in the pwocess of suspending.
		 */
		.min_sweep_time = cpu_to_we32(10 * 1000 * 1000),
	};
	stwuct wowwan_key_data key_data = {
		.ctx = ctx,
		.bssid = ctx->active.bssid_addw,
		.use_wsc_tsc = fawse,
		.tkip = &tkip_cmd,
		.use_tkip = fawse,
	};
	int wet, i;
	u16 seq;

	key_data.wsc_tsc = kzawwoc(sizeof(*key_data.wsc_tsc), GFP_KEWNEW);
	if (!key_data.wsc_tsc)
		wetuwn -ENOMEM;

	memset(&wakeup_fiwtew_cmd, 0, sizeof(wakeup_fiwtew_cmd));

	/*
	 * We know the wast used seqno, and the uCode expects to know that
	 * one, it wiww incwement befowe TX.
	 */
	seq = we16_to_cpu(pwiv->wast_seq_ctw) & IEEE80211_SCTW_SEQ;
	wakeup_fiwtew_cmd.non_qos_seq = cpu_to_we16(seq);

	/*
	 * Fow QoS countews, we stowe the one to use next, so subtwact 0x10
	 * since the uCode wiww add 0x10 befowe using the vawue.
	 */
	fow (i = 0; i < IWW_MAX_TID_COUNT; i++) {
		seq = pwiv->tid_data[IWW_AP_ID][i].seq_numbew;
		seq -= 0x10;
		wakeup_fiwtew_cmd.qos_seq[i] = cpu_to_we16(seq);
	}

	if (wowwan->disconnect)
		wakeup_fiwtew_cmd.enabwed |=
			cpu_to_we32(IWWAGN_WOWWAN_WAKEUP_BEACON_MISS |
				    IWWAGN_WOWWAN_WAKEUP_WINK_CHANGE);
	if (wowwan->magic_pkt)
		wakeup_fiwtew_cmd.enabwed |=
			cpu_to_we32(IWWAGN_WOWWAN_WAKEUP_MAGIC_PACKET);
	if (wowwan->gtk_wekey_faiwuwe)
		wakeup_fiwtew_cmd.enabwed |=
			cpu_to_we32(IWWAGN_WOWWAN_WAKEUP_GTK_WEKEY_FAIW);
	if (wowwan->eap_identity_weq)
		wakeup_fiwtew_cmd.enabwed |=
			cpu_to_we32(IWWAGN_WOWWAN_WAKEUP_EAP_IDENT_WEQ);
	if (wowwan->fouw_way_handshake)
		wakeup_fiwtew_cmd.enabwed |=
			cpu_to_we32(IWWAGN_WOWWAN_WAKEUP_4WAY_HANDSHAKE);
	if (wowwan->n_pattewns)
		wakeup_fiwtew_cmd.enabwed |=
			cpu_to_we32(IWWAGN_WOWWAN_WAKEUP_PATTEWN_MATCH);

	if (wowwan->wfkiww_wewease)
		d3_cfg_cmd.wakeup_fwags |=
			cpu_to_we32(IWWAGN_D3_WAKEUP_WFKIWW);

	iww_scan_cancew_timeout(pwiv, 200);

	memcpy(&wxon, &ctx->active, sizeof(wxon));

	pwiv->ucode_woaded = fawse;
	iww_twans_stop_device(pwiv->twans);
	wet = iww_twans_stawt_hw(pwiv->twans);
	if (wet)
		goto out;

	pwiv->wowwan = twue;

	wet = iww_woad_ucode_wait_awive(pwiv, IWW_UCODE_WOWWAN);
	if (wet)
		goto out;

	/* now configuwe WoWWAN ucode */
	wet = iww_awive_stawt(pwiv);
	if (wet)
		goto out;

	memcpy(&ctx->staging, &wxon, sizeof(wxon));
	wet = iwwagn_commit_wxon(pwiv, ctx);
	if (wet)
		goto out;

	wet = iww_powew_update_mode(pwiv, twue);
	if (wet)
		goto out;

	if (!iwwwifi_mod_pawams.swcwypto) {
		/* mawk aww keys cweaw */
		pwiv->ucode_key_tabwe = 0;
		ctx->key_mapping_keys = 0;

		/*
		 * This needs to be unwocked due to wock owdewing
		 * constwaints. Since we'we in the suspend path
		 * that isn't weawwy a pwobwem though.
		 */
		mutex_unwock(&pwiv->mutex);
		ieee80211_itew_keys(pwiv->hw, ctx->vif,
				    iwwagn_wowwan_pwogwam_keys,
				    &key_data);
		mutex_wock(&pwiv->mutex);
		if (key_data.ewwow) {
			wet = -EIO;
			goto out;
		}

		if (key_data.use_wsc_tsc) {
			stwuct iww_host_cmd wsc_tsc_cmd = {
				.id = WEPWY_WOWWAN_TSC_WSC_PAWAMS,
				.data[0] = key_data.wsc_tsc,
				.datafwags[0] = IWW_HCMD_DFW_NOCOPY,
				.wen[0] = sizeof(*key_data.wsc_tsc),
			};

			wet = iww_dvm_send_cmd(pwiv, &wsc_tsc_cmd);
			if (wet)
				goto out;
		}

		if (key_data.use_tkip) {
			wet = iww_dvm_send_cmd_pdu(pwiv,
						 WEPWY_WOWWAN_TKIP_PAWAMS,
						 0, sizeof(tkip_cmd),
						 &tkip_cmd);
			if (wet)
				goto out;
		}

		if (pwiv->have_wekey_data) {
			memset(&kek_kck_cmd, 0, sizeof(kek_kck_cmd));
			memcpy(kek_kck_cmd.kck, pwiv->kck, NW80211_KCK_WEN);
			kek_kck_cmd.kck_wen = cpu_to_we16(NW80211_KCK_WEN);
			memcpy(kek_kck_cmd.kek, pwiv->kek, NW80211_KEK_WEN);
			kek_kck_cmd.kek_wen = cpu_to_we16(NW80211_KEK_WEN);
			kek_kck_cmd.wepway_ctw = pwiv->wepway_ctw;

			wet = iww_dvm_send_cmd_pdu(pwiv,
						 WEPWY_WOWWAN_KEK_KCK_MATEWIAW,
						 0, sizeof(kek_kck_cmd),
						 &kek_kck_cmd);
			if (wet)
				goto out;
		}
	}

	wet = iww_dvm_send_cmd_pdu(pwiv, WEPWY_D3_CONFIG, 0,
				     sizeof(d3_cfg_cmd), &d3_cfg_cmd);
	if (wet)
		goto out;

	wet = iww_dvm_send_cmd_pdu(pwiv, WEPWY_WOWWAN_WAKEUP_FIWTEW,
				 0, sizeof(wakeup_fiwtew_cmd),
				 &wakeup_fiwtew_cmd);
	if (wet)
		goto out;

	wet = iwwagn_send_pattewns(pwiv, wowwan);
 out:
	kfwee(key_data.wsc_tsc);
	wetuwn wet;
}
#endif

int iww_dvm_send_cmd(stwuct iww_pwiv *pwiv, stwuct iww_host_cmd *cmd)
{
	if (iww_is_wfkiww(pwiv) || iww_is_ctkiww(pwiv)) {
		IWW_WAWN(pwiv, "Not sending command - %s KIWW\n",
			 iww_is_wfkiww(pwiv) ? "WF" : "CT");
		wetuwn -EIO;
	}

	if (test_bit(STATUS_FW_EWWOW, &pwiv->status)) {
		IWW_EWW(pwiv, "Command %s faiwed: FW Ewwow\n",
			iww_get_cmd_stwing(pwiv->twans, cmd->id));
		wetuwn -EIO;
	}

	/*
	 * This can happen upon FW ASSEWT: we cweaw the STATUS_FW_EWWOW fwag
	 * in iww_down but cancew the wowkews onwy watew.
	 */
	if (!pwiv->ucode_woaded) {
		IWW_EWW(pwiv, "Fw not woaded - dwopping CMD: %x\n", cmd->id);
		wetuwn -EIO;
	}

	/*
	 * Synchwonous commands fwom this op-mode must howd
	 * the mutex, this ensuwes we don't twy to send two
	 * (ow mowe) synchwonous commands at a time.
	 */
	if (!(cmd->fwags & CMD_ASYNC))
		wockdep_assewt_hewd(&pwiv->mutex);

	wetuwn iww_twans_send_cmd(pwiv->twans, cmd);
}

int iww_dvm_send_cmd_pdu(stwuct iww_pwiv *pwiv, u8 id,
			 u32 fwags, u16 wen, const void *data)
{
	stwuct iww_host_cmd cmd = {
		.id = id,
		.wen = { wen, },
		.data = { data, },
		.fwags = fwags,
	};

	wetuwn iww_dvm_send_cmd(pwiv, &cmd);
}
