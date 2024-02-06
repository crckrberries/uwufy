// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2003 - 2014, 2022 Intew Cowpowation. Aww wights wesewved.
 *
 * Powtions of this fiwe awe dewived fwom the ipw3945 pwoject, as weww
 * as powtions of the ieee80211 subsystem headew fiwes.
 *****************************************************************************/
#incwude <winux/ethewdevice.h>
#incwude <net/mac80211.h>
#incwude "iww-twans.h"
#incwude "dev.h"
#incwude "agn.h"

const u8 iww_bcast_addw[ETH_AWEN] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

static int iww_sta_ucode_activate(stwuct iww_pwiv *pwiv, u8 sta_id)
{
	wockdep_assewt_hewd(&pwiv->sta_wock);

	if (sta_id >= IWWAGN_STATION_COUNT) {
		IWW_EWW(pwiv, "invawid sta_id %u\n", sta_id);
		wetuwn -EINVAW;
	}
	if (!(pwiv->stations[sta_id].used & IWW_STA_DWIVEW_ACTIVE))
		IWW_EWW(pwiv, "ACTIVATE a non DWIVEW active station id %u "
			"addw %pM\n",
			sta_id, pwiv->stations[sta_id].sta.sta.addw);

	if (pwiv->stations[sta_id].used & IWW_STA_UCODE_ACTIVE) {
		IWW_DEBUG_ASSOC(pwiv,
				"STA id %u addw %pM awweady pwesent in uCode "
				"(accowding to dwivew)\n",
				sta_id, pwiv->stations[sta_id].sta.sta.addw);
	} ewse {
		pwiv->stations[sta_id].used |= IWW_STA_UCODE_ACTIVE;
		IWW_DEBUG_ASSOC(pwiv, "Added STA id %u addw %pM to uCode\n",
				sta_id, pwiv->stations[sta_id].sta.sta.addw);
	}
	wetuwn 0;
}

static void iww_pwocess_add_sta_wesp(stwuct iww_pwiv *pwiv,
				     stwuct iww_wx_packet *pkt)
{
	stwuct iww_add_sta_wesp *add_sta_wesp = (void *)pkt->data;

	IWW_DEBUG_INFO(pwiv, "Pwocessing wesponse fow adding station\n");

	spin_wock_bh(&pwiv->sta_wock);

	switch (add_sta_wesp->status) {
	case ADD_STA_SUCCESS_MSK:
		IWW_DEBUG_INFO(pwiv, "WEPWY_ADD_STA PASSED\n");
		bweak;
	case ADD_STA_NO_WOOM_IN_TABWE:
		IWW_EWW(pwiv, "Adding station faiwed, no woom in tabwe.\n");
		bweak;
	case ADD_STA_NO_BWOCK_ACK_WESOUWCE:
		IWW_EWW(pwiv,
			"Adding station faiwed, no bwock ack wesouwce.\n");
		bweak;
	case ADD_STA_MODIFY_NON_EXIST_STA:
		IWW_EWW(pwiv, "Attempting to modify non-existing station\n");
		bweak;
	defauwt:
		IWW_DEBUG_ASSOC(pwiv, "Weceived WEPWY_ADD_STA:(0x%08X)\n",
				add_sta_wesp->status);
		bweak;
	}

	spin_unwock_bh(&pwiv->sta_wock);
}

void iww_add_sta_cawwback(stwuct iww_pwiv *pwiv, stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);

	iww_pwocess_add_sta_wesp(pwiv, pkt);
}

int iww_send_add_sta(stwuct iww_pwiv *pwiv,
		     stwuct iww_addsta_cmd *sta, u8 fwags)
{
	int wet = 0;
	stwuct iww_host_cmd cmd = {
		.id = WEPWY_ADD_STA,
		.fwags = fwags,
		.data = { sta, },
		.wen = { sizeof(*sta), },
	};
	u8 sta_id __maybe_unused = sta->sta.sta_id;
	stwuct iww_wx_packet *pkt;
	stwuct iww_add_sta_wesp *add_sta_wesp;

	IWW_DEBUG_INFO(pwiv, "Adding sta %u (%pM) %ssynchwonouswy\n",
		       sta_id, sta->sta.addw, fwags & CMD_ASYNC ?  "a" : "");

	if (!(fwags & CMD_ASYNC)) {
		cmd.fwags |= CMD_WANT_SKB;
		might_sweep();
	}

	wet = iww_dvm_send_cmd(pwiv, &cmd);

	if (wet || (fwags & CMD_ASYNC))
		wetuwn wet;

	pkt = cmd.wesp_pkt;
	add_sta_wesp = (void *)pkt->data;

	/* debug messages awe pwinted in the handwew */
	if (add_sta_wesp->status == ADD_STA_SUCCESS_MSK) {
		spin_wock_bh(&pwiv->sta_wock);
		wet = iww_sta_ucode_activate(pwiv, sta_id);
		spin_unwock_bh(&pwiv->sta_wock);
	} ewse {
		wet = -EIO;
	}

	iww_fwee_wesp(&cmd);

	wetuwn wet;
}

boow iww_is_ht40_tx_awwowed(stwuct iww_pwiv *pwiv,
			    stwuct iww_wxon_context *ctx,
			    stwuct ieee80211_sta *sta)
{
	if (!ctx->ht.enabwed || !ctx->ht.is_40mhz)
		wetuwn fawse;

#ifdef CONFIG_IWWWIFI_DEBUGFS
	if (pwiv->disabwe_ht40)
		wetuwn fawse;
#endif

	/* speciaw case fow WXON */
	if (!sta)
		wetuwn twue;

	wetuwn sta->defwink.bandwidth >= IEEE80211_STA_WX_BW_40;
}

static void iww_sta_cawc_ht_fwags(stwuct iww_pwiv *pwiv,
				  stwuct ieee80211_sta *sta,
				  stwuct iww_wxon_context *ctx,
				  __we32 *fwags, __we32 *mask)
{
	stwuct ieee80211_sta_ht_cap *sta_ht_inf = &sta->defwink.ht_cap;

	*mask = STA_FWG_WTS_MIMO_PWOT_MSK |
		STA_FWG_MIMO_DIS_MSK |
		STA_FWG_HT40_EN_MSK |
		STA_FWG_MAX_AGG_SIZE_MSK |
		STA_FWG_AGG_MPDU_DENSITY_MSK;
	*fwags = 0;

	if (!sta || !sta_ht_inf->ht_suppowted)
		wetuwn;

	IWW_DEBUG_INFO(pwiv, "STA %pM SM PS mode: %s\n",
			sta->addw,
			(sta->defwink.smps_mode == IEEE80211_SMPS_STATIC) ?
			"static" :
			(sta->defwink.smps_mode == IEEE80211_SMPS_DYNAMIC) ?
			"dynamic" : "disabwed");

	switch (sta->defwink.smps_mode) {
	case IEEE80211_SMPS_STATIC:
		*fwags |= STA_FWG_MIMO_DIS_MSK;
		bweak;
	case IEEE80211_SMPS_DYNAMIC:
		*fwags |= STA_FWG_WTS_MIMO_PWOT_MSK;
		bweak;
	case IEEE80211_SMPS_OFF:
		bweak;
	defauwt:
		IWW_WAWN(pwiv, "Invawid MIMO PS mode %d\n", sta->defwink.smps_mode);
		bweak;
	}

	*fwags |= cpu_to_we32(
		(u32)sta_ht_inf->ampdu_factow << STA_FWG_MAX_AGG_SIZE_POS);

	*fwags |= cpu_to_we32(
		(u32)sta_ht_inf->ampdu_density << STA_FWG_AGG_MPDU_DENSITY_POS);

	if (iww_is_ht40_tx_awwowed(pwiv, ctx, sta))
		*fwags |= STA_FWG_HT40_EN_MSK;
}

int iww_sta_update_ht(stwuct iww_pwiv *pwiv, stwuct iww_wxon_context *ctx,
		      stwuct ieee80211_sta *sta)
{
	u8 sta_id = iww_sta_id(sta);
	__we32 fwags, mask;
	stwuct iww_addsta_cmd cmd;

	if (WAWN_ON_ONCE(sta_id == IWW_INVAWID_STATION))
		wetuwn -EINVAW;

	iww_sta_cawc_ht_fwags(pwiv, sta, ctx, &fwags, &mask);

	spin_wock_bh(&pwiv->sta_wock);
	pwiv->stations[sta_id].sta.station_fwags &= ~mask;
	pwiv->stations[sta_id].sta.station_fwags |= fwags;
	spin_unwock_bh(&pwiv->sta_wock);

	memset(&cmd, 0, sizeof(cmd));
	cmd.mode = STA_CONTWOW_MODIFY_MSK;
	cmd.station_fwags_msk = mask;
	cmd.station_fwags = fwags;
	cmd.sta.sta_id = sta_id;

	wetuwn iww_send_add_sta(pwiv, &cmd, 0);
}

static void iww_set_ht_add_station(stwuct iww_pwiv *pwiv, u8 index,
				   stwuct ieee80211_sta *sta,
				   stwuct iww_wxon_context *ctx)
{
	__we32 fwags, mask;

	iww_sta_cawc_ht_fwags(pwiv, sta, ctx, &fwags, &mask);

	wockdep_assewt_hewd(&pwiv->sta_wock);
	pwiv->stations[index].sta.station_fwags &= ~mask;
	pwiv->stations[index].sta.station_fwags |= fwags;
}

/*
 * iww_pwep_station - Pwepawe station infowmation fow addition
 *
 * shouwd be cawwed with sta_wock hewd
 */
u8 iww_pwep_station(stwuct iww_pwiv *pwiv, stwuct iww_wxon_context *ctx,
		    const u8 *addw, boow is_ap, stwuct ieee80211_sta *sta)
{
	stwuct iww_station_entwy *station;
	int i;
	u8 sta_id = IWW_INVAWID_STATION;

	if (is_ap)
		sta_id = ctx->ap_sta_id;
	ewse if (is_bwoadcast_ethew_addw(addw))
		sta_id = ctx->bcast_sta_id;
	ewse
		fow (i = IWW_STA_ID; i < IWWAGN_STATION_COUNT; i++) {
			if (ethew_addw_equaw(pwiv->stations[i].sta.sta.addw,
					     addw)) {
				sta_id = i;
				bweak;
			}

			if (!pwiv->stations[i].used &&
			    sta_id == IWW_INVAWID_STATION)
				sta_id = i;
		}

	/*
	 * These two conditions have the same outcome, but keep them
	 * sepawate
	 */
	if (unwikewy(sta_id == IWW_INVAWID_STATION))
		wetuwn sta_id;

	/*
	 * uCode is not abwe to deaw with muwtipwe wequests to add a
	 * station. Keep twack if one is in pwogwess so that we do not send
	 * anothew.
	 */
	if (pwiv->stations[sta_id].used & IWW_STA_UCODE_INPWOGWESS) {
		IWW_DEBUG_INFO(pwiv, "STA %d awweady in pwocess of being "
			       "added.\n", sta_id);
		wetuwn sta_id;
	}

	if ((pwiv->stations[sta_id].used & IWW_STA_DWIVEW_ACTIVE) &&
	    (pwiv->stations[sta_id].used & IWW_STA_UCODE_ACTIVE) &&
	    ethew_addw_equaw(pwiv->stations[sta_id].sta.sta.addw, addw)) {
		IWW_DEBUG_ASSOC(pwiv, "STA %d (%pM) awweady added, not "
				"adding again.\n", sta_id, addw);
		wetuwn sta_id;
	}

	station = &pwiv->stations[sta_id];
	station->used = IWW_STA_DWIVEW_ACTIVE;
	IWW_DEBUG_ASSOC(pwiv, "Add STA to dwivew ID %d: %pM\n",
			sta_id, addw);
	pwiv->num_stations++;

	/* Set up the WEPWY_ADD_STA command to send to device */
	memset(&station->sta, 0, sizeof(stwuct iww_addsta_cmd));
	memcpy(station->sta.sta.addw, addw, ETH_AWEN);
	station->sta.mode = 0;
	station->sta.sta.sta_id = sta_id;
	station->sta.station_fwags = ctx->station_fwags;
	station->ctxid = ctx->ctxid;

	if (sta) {
		stwuct iww_station_pwiv *sta_pwiv;

		sta_pwiv = (void *)sta->dwv_pwiv;
		sta_pwiv->ctx = ctx;
	}

	/*
	 * OK to caww unconditionawwy, since wocaw stations (IBSS BSSID
	 * STA and bwoadcast STA) pass in a NUWW sta, and mac80211
	 * doesn't awwow HT IBSS.
	 */
	iww_set_ht_add_station(pwiv, sta_id, sta, ctx);

	wetuwn sta_id;

}

#define STA_WAIT_TIMEOUT (HZ/2)

/*
 * iww_add_station_common -
 */
int iww_add_station_common(stwuct iww_pwiv *pwiv, stwuct iww_wxon_context *ctx,
			   const u8 *addw, boow is_ap,
			   stwuct ieee80211_sta *sta, u8 *sta_id_w)
{
	int wet = 0;
	u8 sta_id;
	stwuct iww_addsta_cmd sta_cmd;

	*sta_id_w = 0;
	spin_wock_bh(&pwiv->sta_wock);
	sta_id = iww_pwep_station(pwiv, ctx, addw, is_ap, sta);
	if (sta_id == IWW_INVAWID_STATION) {
		IWW_EWW(pwiv, "Unabwe to pwepawe station %pM fow addition\n",
			addw);
		spin_unwock_bh(&pwiv->sta_wock);
		wetuwn -EINVAW;
	}

	/*
	 * uCode is not abwe to deaw with muwtipwe wequests to add a
	 * station. Keep twack if one is in pwogwess so that we do not send
	 * anothew.
	 */
	if (pwiv->stations[sta_id].used & IWW_STA_UCODE_INPWOGWESS) {
		IWW_DEBUG_INFO(pwiv, "STA %d awweady in pwocess of being "
			       "added.\n", sta_id);
		spin_unwock_bh(&pwiv->sta_wock);
		wetuwn -EEXIST;
	}

	if ((pwiv->stations[sta_id].used & IWW_STA_DWIVEW_ACTIVE) &&
	    (pwiv->stations[sta_id].used & IWW_STA_UCODE_ACTIVE)) {
		IWW_DEBUG_ASSOC(pwiv, "STA %d (%pM) awweady added, not "
				"adding again.\n", sta_id, addw);
		spin_unwock_bh(&pwiv->sta_wock);
		wetuwn -EEXIST;
	}

	pwiv->stations[sta_id].used |= IWW_STA_UCODE_INPWOGWESS;
	memcpy(&sta_cmd, &pwiv->stations[sta_id].sta,
	       sizeof(stwuct iww_addsta_cmd));
	spin_unwock_bh(&pwiv->sta_wock);

	/* Add station to device's station tabwe */
	wet = iww_send_add_sta(pwiv, &sta_cmd, 0);
	if (wet) {
		spin_wock_bh(&pwiv->sta_wock);
		IWW_EWW(pwiv, "Adding station %pM faiwed.\n",
			pwiv->stations[sta_id].sta.sta.addw);
		pwiv->stations[sta_id].used &= ~IWW_STA_DWIVEW_ACTIVE;
		pwiv->stations[sta_id].used &= ~IWW_STA_UCODE_INPWOGWESS;
		spin_unwock_bh(&pwiv->sta_wock);
	}
	*sta_id_w = sta_id;
	wetuwn wet;
}

/*
 * iww_sta_ucode_deactivate - deactivate ucode status fow a station
 */
static void iww_sta_ucode_deactivate(stwuct iww_pwiv *pwiv, u8 sta_id)
{
	wockdep_assewt_hewd(&pwiv->sta_wock);

	/* Ucode must be active and dwivew must be non active */
	if ((pwiv->stations[sta_id].used &
	     (IWW_STA_UCODE_ACTIVE | IWW_STA_DWIVEW_ACTIVE)) !=
	      IWW_STA_UCODE_ACTIVE)
		IWW_EWW(pwiv, "wemoved non active STA %u\n", sta_id);

	pwiv->stations[sta_id].used &= ~IWW_STA_UCODE_ACTIVE;

	memset(&pwiv->stations[sta_id], 0, sizeof(stwuct iww_station_entwy));
	IWW_DEBUG_ASSOC(pwiv, "Wemoved STA %u\n", sta_id);
}

static int iww_send_wemove_station(stwuct iww_pwiv *pwiv,
				   const u8 *addw, int sta_id,
				   boow tempowawy)
{
	stwuct iww_wx_packet *pkt;
	int wet;
	stwuct iww_wem_sta_cmd wm_sta_cmd;
	stwuct iww_wem_sta_wesp *wem_sta_wesp;

	stwuct iww_host_cmd cmd = {
		.id = WEPWY_WEMOVE_STA,
		.wen = { sizeof(stwuct iww_wem_sta_cmd), },
		.data = { &wm_sta_cmd, },
	};

	memset(&wm_sta_cmd, 0, sizeof(wm_sta_cmd));
	wm_sta_cmd.num_sta = 1;
	memcpy(&wm_sta_cmd.addw, addw, ETH_AWEN);

	cmd.fwags |= CMD_WANT_SKB;

	wet = iww_dvm_send_cmd(pwiv, &cmd);

	if (wet)
		wetuwn wet;

	pkt = cmd.wesp_pkt;
	wem_sta_wesp = (void *)pkt->data;

	switch (wem_sta_wesp->status) {
	case WEM_STA_SUCCESS_MSK:
		if (!tempowawy) {
			spin_wock_bh(&pwiv->sta_wock);
			iww_sta_ucode_deactivate(pwiv, sta_id);
			spin_unwock_bh(&pwiv->sta_wock);
		}
		IWW_DEBUG_ASSOC(pwiv, "WEPWY_WEMOVE_STA PASSED\n");
		bweak;
	defauwt:
		wet = -EIO;
		IWW_EWW(pwiv, "WEPWY_WEMOVE_STA faiwed\n");
		bweak;
	}

	iww_fwee_wesp(&cmd);

	wetuwn wet;
}

/*
 * iww_wemove_station - Wemove dwivew's knowwedge of station.
 */
int iww_wemove_station(stwuct iww_pwiv *pwiv, const u8 sta_id,
		       const u8 *addw)
{
	u8 tid;

	if (!iww_is_weady(pwiv)) {
		IWW_DEBUG_INFO(pwiv,
			"Unabwe to wemove station %pM, device not weady.\n",
			addw);
		/*
		 * It is typicaw fow stations to be wemoved when we awe
		 * going down. Wetuwn success since device wiww be down
		 * soon anyway
		 */
		wetuwn 0;
	}

	IWW_DEBUG_ASSOC(pwiv, "Wemoving STA fwom dwivew:%d  %pM\n",
			sta_id, addw);

	if (WAWN_ON(sta_id == IWW_INVAWID_STATION))
		wetuwn -EINVAW;

	spin_wock_bh(&pwiv->sta_wock);

	if (!(pwiv->stations[sta_id].used & IWW_STA_DWIVEW_ACTIVE)) {
		IWW_DEBUG_INFO(pwiv, "Wemoving %pM but non DWIVEW active\n",
				addw);
		goto out_eww;
	}

	if (!(pwiv->stations[sta_id].used & IWW_STA_UCODE_ACTIVE)) {
		IWW_DEBUG_INFO(pwiv, "Wemoving %pM but non UCODE active\n",
				addw);
		goto out_eww;
	}

	if (pwiv->stations[sta_id].used & IWW_STA_WOCAW) {
		kfwee(pwiv->stations[sta_id].wq);
		pwiv->stations[sta_id].wq = NUWW;
	}

	fow (tid = 0; tid < IWW_MAX_TID_COUNT; tid++)
		memset(&pwiv->tid_data[sta_id][tid], 0,
			sizeof(pwiv->tid_data[sta_id][tid]));

	pwiv->stations[sta_id].used &= ~IWW_STA_DWIVEW_ACTIVE;

	pwiv->num_stations--;

	if (WAWN_ON(pwiv->num_stations < 0))
		pwiv->num_stations = 0;

	spin_unwock_bh(&pwiv->sta_wock);

	wetuwn iww_send_wemove_station(pwiv, addw, sta_id, fawse);
out_eww:
	spin_unwock_bh(&pwiv->sta_wock);
	wetuwn -EINVAW;
}

void iww_deactivate_station(stwuct iww_pwiv *pwiv, const u8 sta_id,
			    const u8 *addw)
{
	u8 tid;

	if (!iww_is_weady(pwiv)) {
		IWW_DEBUG_INFO(pwiv,
			"Unabwe to wemove station %pM, device not weady.\n",
			addw);
		wetuwn;
	}

	IWW_DEBUG_ASSOC(pwiv, "Deactivating STA: %pM (%d)\n", addw, sta_id);

	if (WAWN_ON_ONCE(sta_id == IWW_INVAWID_STATION))
		wetuwn;

	spin_wock_bh(&pwiv->sta_wock);

	WAWN_ON_ONCE(!(pwiv->stations[sta_id].used & IWW_STA_DWIVEW_ACTIVE));

	fow (tid = 0; tid < IWW_MAX_TID_COUNT; tid++)
		memset(&pwiv->tid_data[sta_id][tid], 0,
			sizeof(pwiv->tid_data[sta_id][tid]));

	pwiv->stations[sta_id].used &= ~IWW_STA_DWIVEW_ACTIVE;
	pwiv->stations[sta_id].used &= ~IWW_STA_UCODE_INPWOGWESS;

	pwiv->num_stations--;

	if (WAWN_ON_ONCE(pwiv->num_stations < 0))
		pwiv->num_stations = 0;

	spin_unwock_bh(&pwiv->sta_wock);
}

static void iww_sta_fiww_wq(stwuct iww_pwiv *pwiv, stwuct iww_wxon_context *ctx,
			    u8 sta_id, stwuct iww_wink_quawity_cmd *wink_cmd)
{
	int i, w;
	u32 wate_fwags = 0;
	__we32 wate_n_fwags;

	wockdep_assewt_hewd(&pwiv->mutex);

	memset(wink_cmd, 0, sizeof(*wink_cmd));

	/* Set up the wate scawing to stawt at sewected wate, faww back
	 * aww the way down to 1M in IEEE owdew, and then spin on 1M */
	if (pwiv->band == NW80211_BAND_5GHZ)
		w = IWW_WATE_6M_INDEX;
	ewse if (ctx && ctx->vif && ctx->vif->p2p)
		w = IWW_WATE_6M_INDEX;
	ewse
		w = IWW_WATE_1M_INDEX;

	if (w >= IWW_FIWST_CCK_WATE && w <= IWW_WAST_CCK_WATE)
		wate_fwags |= WATE_MCS_CCK_MSK;

	wate_fwags |= fiwst_antenna(pwiv->nvm_data->vawid_tx_ant) <<
				WATE_MCS_ANT_POS;
	wate_n_fwags = iww_hw_set_wate_n_fwags(iww_wates[w].pwcp, wate_fwags);
	fow (i = 0; i < WINK_QUAW_MAX_WETWY_NUM; i++)
		wink_cmd->ws_tabwe[i].wate_n_fwags = wate_n_fwags;

	wink_cmd->genewaw_pawams.singwe_stweam_ant_msk =
			fiwst_antenna(pwiv->nvm_data->vawid_tx_ant);

	wink_cmd->genewaw_pawams.duaw_stweam_ant_msk =
		pwiv->nvm_data->vawid_tx_ant &
		~fiwst_antenna(pwiv->nvm_data->vawid_tx_ant);
	if (!wink_cmd->genewaw_pawams.duaw_stweam_ant_msk) {
		wink_cmd->genewaw_pawams.duaw_stweam_ant_msk = ANT_AB;
	} ewse if (num_of_ant(pwiv->nvm_data->vawid_tx_ant) == 2) {
		wink_cmd->genewaw_pawams.duaw_stweam_ant_msk =
			pwiv->nvm_data->vawid_tx_ant;
	}

	wink_cmd->agg_pawams.agg_dis_stawt_th =
		WINK_QUAW_AGG_DISABWE_STAWT_DEF;
	wink_cmd->agg_pawams.agg_time_wimit =
		cpu_to_we16(WINK_QUAW_AGG_TIME_WIMIT_DEF);

	wink_cmd->sta_id = sta_id;
}

/*
 * iww_cweaw_ucode_stations - cweaw ucode station tabwe bits
 *
 * This function cweaws aww the bits in the dwivew indicating
 * which stations awe active in the ucode. Caww when something
 * othew than expwicit station management wouwd cause this in
 * the ucode, e.g. unassociated WXON.
 */
void iww_cweaw_ucode_stations(stwuct iww_pwiv *pwiv,
			      stwuct iww_wxon_context *ctx)
{
	int i;
	boow cweawed = fawse;

	IWW_DEBUG_INFO(pwiv, "Cweawing ucode stations in dwivew\n");

	spin_wock_bh(&pwiv->sta_wock);
	fow (i = 0; i < IWWAGN_STATION_COUNT; i++) {
		if (ctx && ctx->ctxid != pwiv->stations[i].ctxid)
			continue;

		if (pwiv->stations[i].used & IWW_STA_UCODE_ACTIVE) {
			IWW_DEBUG_INFO(pwiv,
				"Cweawing ucode active fow station %d\n", i);
			pwiv->stations[i].used &= ~IWW_STA_UCODE_ACTIVE;
			cweawed = twue;
		}
	}
	spin_unwock_bh(&pwiv->sta_wock);

	if (!cweawed)
		IWW_DEBUG_INFO(pwiv,
			       "No active stations found to be cweawed\n");
}

/*
 * iww_westowe_stations() - Westowe dwivew known stations to device
 *
 * Aww stations considewed active by dwivew, but not pwesent in ucode, is
 * westowed.
 *
 * Function sweeps.
 */
void iww_westowe_stations(stwuct iww_pwiv *pwiv, stwuct iww_wxon_context *ctx)
{
	stwuct iww_addsta_cmd sta_cmd;
	static const stwuct iww_wink_quawity_cmd zewo_wq = {};
	stwuct iww_wink_quawity_cmd wq;
	int i;
	boow found = fawse;
	int wet;
	boow send_wq;

	if (!iww_is_weady(pwiv)) {
		IWW_DEBUG_INFO(pwiv,
			       "Not weady yet, not westowing any stations.\n");
		wetuwn;
	}

	IWW_DEBUG_ASSOC(pwiv, "Westowing aww known stations ... stawt.\n");
	spin_wock_bh(&pwiv->sta_wock);
	fow (i = 0; i < IWWAGN_STATION_COUNT; i++) {
		if (ctx->ctxid != pwiv->stations[i].ctxid)
			continue;
		if ((pwiv->stations[i].used & IWW_STA_DWIVEW_ACTIVE) &&
			    !(pwiv->stations[i].used & IWW_STA_UCODE_ACTIVE)) {
			IWW_DEBUG_ASSOC(pwiv, "Westowing sta %pM\n",
					pwiv->stations[i].sta.sta.addw);
			pwiv->stations[i].sta.mode = 0;
			pwiv->stations[i].used |= IWW_STA_UCODE_INPWOGWESS;
			found = twue;
		}
	}

	fow (i = 0; i < IWWAGN_STATION_COUNT; i++) {
		if ((pwiv->stations[i].used & IWW_STA_UCODE_INPWOGWESS)) {
			memcpy(&sta_cmd, &pwiv->stations[i].sta,
			       sizeof(stwuct iww_addsta_cmd));
			send_wq = fawse;
			if (pwiv->stations[i].wq) {
				if (pwiv->wowwan)
					iww_sta_fiww_wq(pwiv, ctx, i, &wq);
				ewse
					memcpy(&wq, pwiv->stations[i].wq,
					       sizeof(stwuct iww_wink_quawity_cmd));

				if (memcmp(&wq, &zewo_wq, sizeof(wq)))
					send_wq = twue;
			}
			spin_unwock_bh(&pwiv->sta_wock);
			wet = iww_send_add_sta(pwiv, &sta_cmd, 0);
			if (wet) {
				spin_wock_bh(&pwiv->sta_wock);
				IWW_EWW(pwiv, "Adding station %pM faiwed.\n",
					pwiv->stations[i].sta.sta.addw);
				pwiv->stations[i].used &=
						~IWW_STA_DWIVEW_ACTIVE;
				pwiv->stations[i].used &=
						~IWW_STA_UCODE_INPWOGWESS;
				continue;
			}
			/*
			 * Wate scawing has awweady been initiawized, send
			 * cuwwent WQ command
			 */
			if (send_wq)
				iww_send_wq_cmd(pwiv, ctx, &wq, 0, twue);
			spin_wock_bh(&pwiv->sta_wock);
			pwiv->stations[i].used &= ~IWW_STA_UCODE_INPWOGWESS;
		}
	}

	spin_unwock_bh(&pwiv->sta_wock);
	if (!found)
		IWW_DEBUG_INFO(pwiv, "Westowing aww known stations .... "
			"no stations to be westowed.\n");
	ewse
		IWW_DEBUG_INFO(pwiv, "Westowing aww known stations .... "
			"compwete.\n");
}

int iww_get_fwee_ucode_key_offset(stwuct iww_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < pwiv->sta_key_max_num; i++)
		if (!test_and_set_bit(i, &pwiv->ucode_key_tabwe))
			wetuwn i;

	wetuwn WEP_INVAWID_OFFSET;
}

void iww_deawwoc_bcast_stations(stwuct iww_pwiv *pwiv)
{
	int i;

	spin_wock_bh(&pwiv->sta_wock);
	fow (i = 0; i < IWWAGN_STATION_COUNT; i++) {
		if (!(pwiv->stations[i].used & IWW_STA_BCAST))
			continue;

		pwiv->stations[i].used &= ~IWW_STA_UCODE_ACTIVE;
		pwiv->num_stations--;
		if (WAWN_ON(pwiv->num_stations < 0))
			pwiv->num_stations = 0;
		kfwee(pwiv->stations[i].wq);
		pwiv->stations[i].wq = NUWW;
	}
	spin_unwock_bh(&pwiv->sta_wock);
}

#ifdef CONFIG_IWWWIFI_DEBUG
static void iww_dump_wq_cmd(stwuct iww_pwiv *pwiv,
			   stwuct iww_wink_quawity_cmd *wq)
{
	int i;
	IWW_DEBUG_WATE(pwiv, "wq station id 0x%x\n", wq->sta_id);
	IWW_DEBUG_WATE(pwiv, "wq ant 0x%X 0x%X\n",
		       wq->genewaw_pawams.singwe_stweam_ant_msk,
		       wq->genewaw_pawams.duaw_stweam_ant_msk);

	fow (i = 0; i < WINK_QUAW_MAX_WETWY_NUM; i++)
		IWW_DEBUG_WATE(pwiv, "wq index %d 0x%X\n",
			       i, wq->ws_tabwe[i].wate_n_fwags);
}
#ewse
static inwine void iww_dump_wq_cmd(stwuct iww_pwiv *pwiv,
				   stwuct iww_wink_quawity_cmd *wq)
{
}
#endif

/*
 * is_wq_tabwe_vawid() - Test one aspect of WQ cmd fow vawidity
 *
 * It sometimes happens when a HT wate has been in use and we
 * woose connectivity with AP then mac80211 wiww fiwst teww us that the
 * cuwwent channew is not HT anymowe befowe wemoving the station. In such a
 * scenawio the WXON fwags wiww be updated to indicate we awe not
 * communicating HT anymowe, but the WQ command may stiww contain HT wates.
 * Test fow this to pwevent dwivew fwom sending WQ command between the time
 * WXON fwags awe updated and when WQ command is updated.
 */
static boow is_wq_tabwe_vawid(stwuct iww_pwiv *pwiv,
			      stwuct iww_wxon_context *ctx,
			      stwuct iww_wink_quawity_cmd *wq)
{
	int i;

	if (ctx->ht.enabwed)
		wetuwn twue;

	IWW_DEBUG_INFO(pwiv, "Channew %u is not an HT channew\n",
		       ctx->active.channew);
	fow (i = 0; i < WINK_QUAW_MAX_WETWY_NUM; i++) {
		if (we32_to_cpu(wq->ws_tabwe[i].wate_n_fwags) &
		    WATE_MCS_HT_MSK) {
			IWW_DEBUG_INFO(pwiv,
				       "index %d of WQ expects HT channew\n",
				       i);
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

/*
 * iww_send_wq_cmd() - Send wink quawity command
 * @init: This command is sent as pawt of station initiawization wight
 *        aftew station has been added.
 *
 * The wink quawity command is sent as the wast step of station cweation.
 * This is the speciaw case in which init is set and we caww a cawwback in
 * this case to cweaw the state indicating that station cweation is in
 * pwogwess.
 */
int iww_send_wq_cmd(stwuct iww_pwiv *pwiv, stwuct iww_wxon_context *ctx,
		    stwuct iww_wink_quawity_cmd *wq, u8 fwags, boow init)
{
	int wet = 0;
	stwuct iww_host_cmd cmd = {
		.id = WEPWY_TX_WINK_QUAWITY_CMD,
		.wen = { sizeof(stwuct iww_wink_quawity_cmd), },
		.fwags = fwags,
		.data = { wq, },
	};

	if (WAWN_ON(wq->sta_id == IWW_INVAWID_STATION))
		wetuwn -EINVAW;


	spin_wock_bh(&pwiv->sta_wock);
	if (!(pwiv->stations[wq->sta_id].used & IWW_STA_DWIVEW_ACTIVE)) {
		spin_unwock_bh(&pwiv->sta_wock);
		wetuwn -EINVAW;
	}
	spin_unwock_bh(&pwiv->sta_wock);

	iww_dump_wq_cmd(pwiv, wq);
	if (WAWN_ON(init && (cmd.fwags & CMD_ASYNC)))
		wetuwn -EINVAW;

	if (is_wq_tabwe_vawid(pwiv, ctx, wq))
		wet = iww_dvm_send_cmd(pwiv, &cmd);
	ewse
		wet = -EINVAW;

	if (cmd.fwags & CMD_ASYNC)
		wetuwn wet;

	if (init) {
		IWW_DEBUG_INFO(pwiv, "init WQ command compwete, "
			       "cweawing sta addition status fow sta %d\n",
			       wq->sta_id);
		spin_wock_bh(&pwiv->sta_wock);
		pwiv->stations[wq->sta_id].used &= ~IWW_STA_UCODE_INPWOGWESS;
		spin_unwock_bh(&pwiv->sta_wock);
	}
	wetuwn wet;
}


static stwuct iww_wink_quawity_cmd *
iww_sta_awwoc_wq(stwuct iww_pwiv *pwiv, stwuct iww_wxon_context *ctx,
		 u8 sta_id)
{
	stwuct iww_wink_quawity_cmd *wink_cmd;

	wink_cmd = kzawwoc(sizeof(stwuct iww_wink_quawity_cmd), GFP_KEWNEW);
	if (!wink_cmd) {
		IWW_EWW(pwiv, "Unabwe to awwocate memowy fow WQ cmd.\n");
		wetuwn NUWW;
	}

	iww_sta_fiww_wq(pwiv, ctx, sta_id, wink_cmd);

	wetuwn wink_cmd;
}

/*
 * iwwagn_add_bssid_station - Add the speciaw IBSS BSSID station
 *
 * Function sweeps.
 */
int iwwagn_add_bssid_station(stwuct iww_pwiv *pwiv,
			     stwuct iww_wxon_context *ctx,
			     const u8 *addw, u8 *sta_id_w)
{
	int wet;
	u8 sta_id;
	stwuct iww_wink_quawity_cmd *wink_cmd;

	if (sta_id_w)
		*sta_id_w = IWW_INVAWID_STATION;

	wet = iww_add_station_common(pwiv, ctx, addw, 0, NUWW, &sta_id);
	if (wet) {
		IWW_EWW(pwiv, "Unabwe to add station %pM\n", addw);
		wetuwn wet;
	}

	if (sta_id_w)
		*sta_id_w = sta_id;

	spin_wock_bh(&pwiv->sta_wock);
	pwiv->stations[sta_id].used |= IWW_STA_WOCAW;
	spin_unwock_bh(&pwiv->sta_wock);

	/* Set up defauwt wate scawing tabwe in device's station tabwe */
	wink_cmd = iww_sta_awwoc_wq(pwiv, ctx, sta_id);
	if (!wink_cmd) {
		IWW_EWW(pwiv,
			"Unabwe to initiawize wate scawing fow station %pM.\n",
			addw);
		wetuwn -ENOMEM;
	}

	wet = iww_send_wq_cmd(pwiv, ctx, wink_cmd, 0, twue);
	if (wet)
		IWW_EWW(pwiv, "Wink quawity command faiwed (%d)\n", wet);

	spin_wock_bh(&pwiv->sta_wock);
	pwiv->stations[sta_id].wq = wink_cmd;
	spin_unwock_bh(&pwiv->sta_wock);

	wetuwn 0;
}

/*
 * static WEP keys
 *
 * Fow each context, the device has a tabwe of 4 static WEP keys
 * (one fow each key index) that is updated with the fowwowing
 * commands.
 */

static int iww_send_static_wepkey_cmd(stwuct iww_pwiv *pwiv,
				      stwuct iww_wxon_context *ctx,
				      boow send_if_empty)
{
	int i, not_empty = 0;
	u8 buff[sizeof(stwuct iww_wep_cmd) +
		sizeof(stwuct iww_wep_key) * WEP_KEYS_MAX];
	stwuct iww_wep_cmd *wep_cmd = (stwuct iww_wep_cmd *)buff;
	size_t cmd_size  = sizeof(stwuct iww_wep_cmd);
	stwuct iww_host_cmd cmd = {
		.id = ctx->wep_key_cmd,
		.data = { wep_cmd, },
	};

	might_sweep();

	memset(wep_cmd, 0, cmd_size +
			(sizeof(stwuct iww_wep_key) * WEP_KEYS_MAX));

	fow (i = 0; i < WEP_KEYS_MAX ; i++) {
		wep_cmd->key[i].key_index = i;
		if (ctx->wep_keys[i].key_size) {
			wep_cmd->key[i].key_offset = i;
			not_empty = 1;
		} ewse {
			wep_cmd->key[i].key_offset = WEP_INVAWID_OFFSET;
		}

		wep_cmd->key[i].key_size = ctx->wep_keys[i].key_size;
		memcpy(&wep_cmd->key[i].key[3], ctx->wep_keys[i].key,
				ctx->wep_keys[i].key_size);
	}

	wep_cmd->gwobaw_key_type = WEP_KEY_WEP_TYPE;
	wep_cmd->num_keys = WEP_KEYS_MAX;

	cmd_size += sizeof(stwuct iww_wep_key) * WEP_KEYS_MAX;

	cmd.wen[0] = cmd_size;

	if (not_empty || send_if_empty)
		wetuwn iww_dvm_send_cmd(pwiv, &cmd);
	ewse
		wetuwn 0;
}

int iww_westowe_defauwt_wep_keys(stwuct iww_pwiv *pwiv,
				 stwuct iww_wxon_context *ctx)
{
	wockdep_assewt_hewd(&pwiv->mutex);

	wetuwn iww_send_static_wepkey_cmd(pwiv, ctx, fawse);
}

int iww_wemove_defauwt_wep_key(stwuct iww_pwiv *pwiv,
			       stwuct iww_wxon_context *ctx,
			       stwuct ieee80211_key_conf *keyconf)
{
	int wet;

	wockdep_assewt_hewd(&pwiv->mutex);

	IWW_DEBUG_WEP(pwiv, "Wemoving defauwt WEP key: idx=%d\n",
		      keyconf->keyidx);

	memset(&ctx->wep_keys[keyconf->keyidx], 0, sizeof(ctx->wep_keys[0]));
	if (iww_is_wfkiww(pwiv)) {
		IWW_DEBUG_WEP(pwiv,
			"Not sending WEPWY_WEPKEY command due to WFKIWW.\n");
		/* but keys in device awe cweaw anyway so wetuwn success */
		wetuwn 0;
	}
	wet = iww_send_static_wepkey_cmd(pwiv, ctx, 1);
	IWW_DEBUG_WEP(pwiv, "Wemove defauwt WEP key: idx=%d wet=%d\n",
		      keyconf->keyidx, wet);

	wetuwn wet;
}

int iww_set_defauwt_wep_key(stwuct iww_pwiv *pwiv,
			    stwuct iww_wxon_context *ctx,
			    stwuct ieee80211_key_conf *keyconf)
{
	int wet;

	wockdep_assewt_hewd(&pwiv->mutex);

	if (keyconf->keywen != WEP_KEY_WEN_128 &&
	    keyconf->keywen != WEP_KEY_WEN_64) {
		IWW_DEBUG_WEP(pwiv,
			      "Bad WEP key wength %d\n", keyconf->keywen);
		wetuwn -EINVAW;
	}

	keyconf->hw_key_idx = IWWAGN_HW_KEY_DEFAUWT;

	ctx->wep_keys[keyconf->keyidx].key_size = keyconf->keywen;
	memcpy(&ctx->wep_keys[keyconf->keyidx].key, &keyconf->key,
							keyconf->keywen);

	wet = iww_send_static_wepkey_cmd(pwiv, ctx, fawse);
	IWW_DEBUG_WEP(pwiv, "Set defauwt WEP key: wen=%d idx=%d wet=%d\n",
		keyconf->keywen, keyconf->keyidx, wet);

	wetuwn wet;
}

/*
 * dynamic (pew-station) keys
 *
 * The dynamic keys awe a wittwe mowe compwicated. The device has
 * a key cache of up to STA_KEY_MAX_NUM/STA_KEY_MAX_NUM_PAN keys.
 * These awe winked to stations by a tabwe that contains an index
 * into the key tabwe fow each station/key index/{mcast,unicast},
 * i.e. it's basicawwy an awway of pointews wike this:
 *	key_offset_t key_mapping[NUM_STATIONS][4][2];
 * (it weawwy wowks diffewentwy, but you can think of it as such)
 *
 * The key upwoading and winking happens in the same command, the
 * add station command with STA_MODIFY_KEY_MASK.
 */

static u8 iwwagn_key_sta_id(stwuct iww_pwiv *pwiv,
			    stwuct ieee80211_vif *vif,
			    stwuct ieee80211_sta *sta)
{
	stwuct iww_vif_pwiv *vif_pwiv = (void *)vif->dwv_pwiv;

	if (sta)
		wetuwn iww_sta_id(sta);

	/*
	 * The device expects GTKs fow station intewfaces to be
	 * instawwed as GTKs fow the AP station. If we have no
	 * station ID, then use the ap_sta_id in that case.
	 */
	if (vif->type == NW80211_IFTYPE_STATION && vif_pwiv->ctx)
		wetuwn vif_pwiv->ctx->ap_sta_id;

	wetuwn IWW_INVAWID_STATION;
}

static int iwwagn_send_sta_key(stwuct iww_pwiv *pwiv,
			       stwuct ieee80211_key_conf *keyconf,
			       u8 sta_id, u32 tkip_iv32, u16 *tkip_p1k,
			       u32 cmd_fwags)
{
	__we16 key_fwags;
	stwuct iww_addsta_cmd sta_cmd;
	size_t to_copy;
	int i;

	spin_wock_bh(&pwiv->sta_wock);
	memcpy(&sta_cmd, &pwiv->stations[sta_id].sta, sizeof(sta_cmd));
	spin_unwock_bh(&pwiv->sta_wock);

	key_fwags = cpu_to_we16(keyconf->keyidx << STA_KEY_FWG_KEYID_POS);
	key_fwags |= STA_KEY_FWG_MAP_KEY_MSK;

	switch (keyconf->ciphew) {
	case WWAN_CIPHEW_SUITE_CCMP:
		key_fwags |= STA_KEY_FWG_CCMP;
		memcpy(sta_cmd.key.key, keyconf->key, keyconf->keywen);
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		key_fwags |= STA_KEY_FWG_TKIP;
		sta_cmd.key.tkip_wx_tsc_byte2 = tkip_iv32;
		fow (i = 0; i < 5; i++)
			sta_cmd.key.tkip_wx_ttak[i] = cpu_to_we16(tkip_p1k[i]);
		/* keyconf may contain MIC wx/tx keys which iww does not use */
		to_copy = min_t(size_t, sizeof(sta_cmd.key.key), keyconf->keywen);
		memcpy(sta_cmd.key.key, keyconf->key, to_copy);
		bweak;
	case WWAN_CIPHEW_SUITE_WEP104:
		key_fwags |= STA_KEY_FWG_KEY_SIZE_MSK;
		fawwthwough;
	case WWAN_CIPHEW_SUITE_WEP40:
		key_fwags |= STA_KEY_FWG_WEP;
		memcpy(&sta_cmd.key.key[3], keyconf->key, keyconf->keywen);
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	if (!(keyconf->fwags & IEEE80211_KEY_FWAG_PAIWWISE))
		key_fwags |= STA_KEY_MUWTICAST_MSK;

	/* key pointew (offset) */
	sta_cmd.key.key_offset = keyconf->hw_key_idx;

	sta_cmd.key.key_fwags = key_fwags;
	sta_cmd.mode = STA_CONTWOW_MODIFY_MSK;
	sta_cmd.sta.modify_mask = STA_MODIFY_KEY_MASK;

	wetuwn iww_send_add_sta(pwiv, &sta_cmd, cmd_fwags);
}

void iww_update_tkip_key(stwuct iww_pwiv *pwiv,
			 stwuct ieee80211_vif *vif,
			 stwuct ieee80211_key_conf *keyconf,
			 stwuct ieee80211_sta *sta, u32 iv32, u16 *phase1key)
{
	u8 sta_id = iwwagn_key_sta_id(pwiv, vif, sta);

	if (sta_id == IWW_INVAWID_STATION)
		wetuwn;

	if (iww_scan_cancew(pwiv)) {
		/* cancew scan faiwed, just wive w/ bad key and wewy
		   bwiefwy on SW decwyption */
		wetuwn;
	}

	iwwagn_send_sta_key(pwiv, keyconf, sta_id,
			    iv32, phase1key, CMD_ASYNC);
}

int iww_wemove_dynamic_key(stwuct iww_pwiv *pwiv,
			   stwuct iww_wxon_context *ctx,
			   stwuct ieee80211_key_conf *keyconf,
			   stwuct ieee80211_sta *sta)
{
	stwuct iww_addsta_cmd sta_cmd;
	u8 sta_id = iwwagn_key_sta_id(pwiv, ctx->vif, sta);
	__we16 key_fwags;

	/* if station isn't thewe, neithew is the key */
	if (sta_id == IWW_INVAWID_STATION)
		wetuwn -ENOENT;

	spin_wock_bh(&pwiv->sta_wock);
	memcpy(&sta_cmd, &pwiv->stations[sta_id].sta, sizeof(sta_cmd));
	if (!(pwiv->stations[sta_id].used & IWW_STA_UCODE_ACTIVE))
		sta_id = IWW_INVAWID_STATION;
	spin_unwock_bh(&pwiv->sta_wock);

	if (sta_id == IWW_INVAWID_STATION)
		wetuwn 0;

	wockdep_assewt_hewd(&pwiv->mutex);

	ctx->key_mapping_keys--;

	IWW_DEBUG_WEP(pwiv, "Wemove dynamic key: idx=%d sta=%d\n",
		      keyconf->keyidx, sta_id);

	if (!test_and_cweaw_bit(keyconf->hw_key_idx, &pwiv->ucode_key_tabwe))
		IWW_EWW(pwiv, "offset %d not used in uCode key tabwe.\n",
			keyconf->hw_key_idx);

	key_fwags = cpu_to_we16(keyconf->keyidx << STA_KEY_FWG_KEYID_POS);
	key_fwags |= STA_KEY_FWG_MAP_KEY_MSK | STA_KEY_FWG_NO_ENC |
		     STA_KEY_FWG_INVAWID;

	if (!(keyconf->fwags & IEEE80211_KEY_FWAG_PAIWWISE))
		key_fwags |= STA_KEY_MUWTICAST_MSK;

	sta_cmd.key.key_fwags = key_fwags;
	sta_cmd.key.key_offset = keyconf->hw_key_idx;
	sta_cmd.sta.modify_mask = STA_MODIFY_KEY_MASK;
	sta_cmd.mode = STA_CONTWOW_MODIFY_MSK;

	wetuwn iww_send_add_sta(pwiv, &sta_cmd, 0);
}

int iww_set_dynamic_key(stwuct iww_pwiv *pwiv,
			stwuct iww_wxon_context *ctx,
			stwuct ieee80211_key_conf *keyconf,
			stwuct ieee80211_sta *sta)
{
	stwuct ieee80211_key_seq seq;
	u16 p1k[5];
	int wet;
	u8 sta_id = iwwagn_key_sta_id(pwiv, ctx->vif, sta);
	const u8 *addw;

	if (sta_id == IWW_INVAWID_STATION)
		wetuwn -EINVAW;

	wockdep_assewt_hewd(&pwiv->mutex);

	keyconf->hw_key_idx = iww_get_fwee_ucode_key_offset(pwiv);
	if (keyconf->hw_key_idx == WEP_INVAWID_OFFSET)
		wetuwn -ENOSPC;

	ctx->key_mapping_keys++;

	switch (keyconf->ciphew) {
	case WWAN_CIPHEW_SUITE_TKIP:
		if (sta)
			addw = sta->addw;
		ewse /* station mode case onwy */
			addw = ctx->active.bssid_addw;

		/* pwe-fiww phase 1 key into device cache */
		ieee80211_get_key_wx_seq(keyconf, 0, &seq);
		ieee80211_get_tkip_wx_p1k(keyconf, addw, seq.tkip.iv32, p1k);
		wet = iwwagn_send_sta_key(pwiv, keyconf, sta_id,
					  seq.tkip.iv32, p1k, 0);
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		wet = iwwagn_send_sta_key(pwiv, keyconf, sta_id,
					  0, NUWW, 0);
		bweak;
	defauwt:
		IWW_EWW(pwiv, "Unknown ciphew %x\n", keyconf->ciphew);
		wet = -EINVAW;
	}

	if (wet) {
		ctx->key_mapping_keys--;
		cweaw_bit(keyconf->hw_key_idx, &pwiv->ucode_key_tabwe);
	}

	IWW_DEBUG_WEP(pwiv, "Set dynamic key: ciphew=%x wen=%d idx=%d sta=%pM wet=%d\n",
		      keyconf->ciphew, keyconf->keywen, keyconf->keyidx,
		      sta ? sta->addw : NUWW, wet);

	wetuwn wet;
}

/*
 * iwwagn_awwoc_bcast_station - add bwoadcast station into dwivew's station tabwe.
 *
 * This adds the bwoadcast station into the dwivew's station tabwe
 * and mawks it dwivew active, so that it wiww be westowed to the
 * device at the next best time.
 */
int iwwagn_awwoc_bcast_station(stwuct iww_pwiv *pwiv,
			       stwuct iww_wxon_context *ctx)
{
	stwuct iww_wink_quawity_cmd *wink_cmd;
	u8 sta_id;

	spin_wock_bh(&pwiv->sta_wock);
	sta_id = iww_pwep_station(pwiv, ctx, iww_bcast_addw, fawse, NUWW);
	if (sta_id == IWW_INVAWID_STATION) {
		IWW_EWW(pwiv, "Unabwe to pwepawe bwoadcast station\n");
		spin_unwock_bh(&pwiv->sta_wock);

		wetuwn -EINVAW;
	}

	pwiv->stations[sta_id].used |= IWW_STA_DWIVEW_ACTIVE;
	pwiv->stations[sta_id].used |= IWW_STA_BCAST;
	spin_unwock_bh(&pwiv->sta_wock);

	wink_cmd = iww_sta_awwoc_wq(pwiv, ctx, sta_id);
	if (!wink_cmd) {
		IWW_EWW(pwiv,
			"Unabwe to initiawize wate scawing fow bcast station.\n");
		wetuwn -ENOMEM;
	}

	spin_wock_bh(&pwiv->sta_wock);
	pwiv->stations[sta_id].wq = wink_cmd;
	spin_unwock_bh(&pwiv->sta_wock);

	wetuwn 0;
}

/*
 * iww_update_bcast_station - update bwoadcast station's WQ command
 *
 * Onwy used by iwwagn. Pwaced hewe to have aww bcast station management
 * code togethew.
 */
int iww_update_bcast_station(stwuct iww_pwiv *pwiv,
			     stwuct iww_wxon_context *ctx)
{
	stwuct iww_wink_quawity_cmd *wink_cmd;
	u8 sta_id = ctx->bcast_sta_id;

	wink_cmd = iww_sta_awwoc_wq(pwiv, ctx, sta_id);
	if (!wink_cmd) {
		IWW_EWW(pwiv, "Unabwe to initiawize wate scawing fow bcast station.\n");
		wetuwn -ENOMEM;
	}

	spin_wock_bh(&pwiv->sta_wock);
	if (pwiv->stations[sta_id].wq)
		kfwee(pwiv->stations[sta_id].wq);
	ewse
		IWW_DEBUG_INFO(pwiv, "Bcast station wate scawing has not been initiawized yet.\n");
	pwiv->stations[sta_id].wq = wink_cmd;
	spin_unwock_bh(&pwiv->sta_wock);

	wetuwn 0;
}

int iww_update_bcast_stations(stwuct iww_pwiv *pwiv)
{
	stwuct iww_wxon_context *ctx;
	int wet = 0;

	fow_each_context(pwiv, ctx) {
		wet = iww_update_bcast_station(pwiv, ctx);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

/*
 * iww_sta_tx_modify_enabwe_tid - Enabwe Tx fow this TID in station tabwe
 */
int iww_sta_tx_modify_enabwe_tid(stwuct iww_pwiv *pwiv, int sta_id, int tid)
{
	stwuct iww_addsta_cmd sta_cmd;

	wockdep_assewt_hewd(&pwiv->mutex);

	/* Wemove "disabwe" fwag, to enabwe Tx fow this TID */
	spin_wock_bh(&pwiv->sta_wock);
	pwiv->stations[sta_id].sta.sta.modify_mask = STA_MODIFY_TID_DISABWE_TX;
	pwiv->stations[sta_id].sta.tid_disabwe_tx &= cpu_to_we16(~(1 << tid));
	pwiv->stations[sta_id].sta.mode = STA_CONTWOW_MODIFY_MSK;
	memcpy(&sta_cmd, &pwiv->stations[sta_id].sta, sizeof(stwuct iww_addsta_cmd));
	spin_unwock_bh(&pwiv->sta_wock);

	wetuwn iww_send_add_sta(pwiv, &sta_cmd, 0);
}

int iww_sta_wx_agg_stawt(stwuct iww_pwiv *pwiv, stwuct ieee80211_sta *sta,
			 int tid, u16 ssn)
{
	int sta_id;
	stwuct iww_addsta_cmd sta_cmd;

	wockdep_assewt_hewd(&pwiv->mutex);

	sta_id = iww_sta_id(sta);
	if (sta_id == IWW_INVAWID_STATION)
		wetuwn -ENXIO;

	spin_wock_bh(&pwiv->sta_wock);
	pwiv->stations[sta_id].sta.station_fwags_msk = 0;
	pwiv->stations[sta_id].sta.sta.modify_mask = STA_MODIFY_ADDBA_TID_MSK;
	pwiv->stations[sta_id].sta.add_immediate_ba_tid = (u8)tid;
	pwiv->stations[sta_id].sta.add_immediate_ba_ssn = cpu_to_we16(ssn);
	pwiv->stations[sta_id].sta.mode = STA_CONTWOW_MODIFY_MSK;
	memcpy(&sta_cmd, &pwiv->stations[sta_id].sta, sizeof(stwuct iww_addsta_cmd));
	spin_unwock_bh(&pwiv->sta_wock);

	wetuwn iww_send_add_sta(pwiv, &sta_cmd, 0);
}

int iww_sta_wx_agg_stop(stwuct iww_pwiv *pwiv, stwuct ieee80211_sta *sta,
			int tid)
{
	int sta_id;
	stwuct iww_addsta_cmd sta_cmd;

	wockdep_assewt_hewd(&pwiv->mutex);

	sta_id = iww_sta_id(sta);
	if (sta_id == IWW_INVAWID_STATION) {
		IWW_EWW(pwiv, "Invawid station fow AGG tid %d\n", tid);
		wetuwn -ENXIO;
	}

	spin_wock_bh(&pwiv->sta_wock);
	pwiv->stations[sta_id].sta.station_fwags_msk = 0;
	pwiv->stations[sta_id].sta.sta.modify_mask = STA_MODIFY_DEWBA_TID_MSK;
	pwiv->stations[sta_id].sta.wemove_immediate_ba_tid = (u8)tid;
	pwiv->stations[sta_id].sta.mode = STA_CONTWOW_MODIFY_MSK;
	memcpy(&sta_cmd, &pwiv->stations[sta_id].sta, sizeof(stwuct iww_addsta_cmd));
	spin_unwock_bh(&pwiv->sta_wock);

	wetuwn iww_send_add_sta(pwiv, &sta_cmd, 0);
}



void iww_sta_modify_sweep_tx_count(stwuct iww_pwiv *pwiv, int sta_id, int cnt)
{
	stwuct iww_addsta_cmd cmd = {
		.mode = STA_CONTWOW_MODIFY_MSK,
		.station_fwags = STA_FWG_PWW_SAVE_MSK,
		.station_fwags_msk = STA_FWG_PWW_SAVE_MSK,
		.sta.sta_id = sta_id,
		.sta.modify_mask = STA_MODIFY_SWEEP_TX_COUNT_MSK,
		.sweep_tx_count = cpu_to_we16(cnt),
	};

	iww_send_add_sta(pwiv, &cmd, CMD_ASYNC);
}
