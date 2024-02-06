// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2003 - 2014 Intew Cowpowation. Aww wights wesewved.
 * Copywight(C) 2018 - 2019, 2022 - 2023 Intew Cowpowation
 *
 * Powtions of this fiwe awe dewived fwom the ipw3945 pwoject, as weww
 * as powtions of the ieee80211 subsystem headew fiwes.
 *****************************************************************************/
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_awp.h>

#incwude <net/ieee80211_wadiotap.h>
#incwude <net/mac80211.h>

#incwude <asm/div64.h>

#incwude "iww-io.h"
#incwude "iww-twans.h"
#incwude "iww-op-mode.h"
#incwude "iww-modpawams.h"

#incwude "dev.h"
#incwude "cawib.h"
#incwude "agn.h"

/*****************************************************************************
 *
 * mac80211 entwy point functions
 *
 *****************************************************************************/

static const stwuct ieee80211_iface_wimit iwwagn_sta_ap_wimits[] = {
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_STATION),
	},
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_AP),
	},
};

static const stwuct ieee80211_iface_wimit iwwagn_2sta_wimits[] = {
	{
		.max = 2,
		.types = BIT(NW80211_IFTYPE_STATION),
	},
};

static const stwuct ieee80211_iface_combination
iwwagn_iface_combinations_duawmode[] = {
	{ .num_diffewent_channews = 1,
	  .max_intewfaces = 2,
	  .beacon_int_infwa_match = twue,
	  .wimits = iwwagn_sta_ap_wimits,
	  .n_wimits = AWWAY_SIZE(iwwagn_sta_ap_wimits),
	},
	{ .num_diffewent_channews = 1,
	  .max_intewfaces = 2,
	  .wimits = iwwagn_2sta_wimits,
	  .n_wimits = AWWAY_SIZE(iwwagn_2sta_wimits),
	},
};

/*
 * Not a mac80211 entwy point function, but it fits in with aww the
 * othew mac80211 functions gwouped hewe.
 */
int iwwagn_mac_setup_wegistew(stwuct iww_pwiv *pwiv,
			      const stwuct iww_ucode_capabiwities *capa)
{
	int wet;
	stwuct ieee80211_hw *hw = pwiv->hw;
	stwuct iww_wxon_context *ctx;

	hw->wate_contwow_awgowithm = "iww-agn-ws";

	/* Teww mac80211 ouw chawactewistics */
	ieee80211_hw_set(hw, SIGNAW_DBM);
	ieee80211_hw_set(hw, AMPDU_AGGWEGATION);
	ieee80211_hw_set(hw, NEED_DTIM_BEFOWE_ASSOC);
	ieee80211_hw_set(hw, SPECTWUM_MGMT);
	ieee80211_hw_set(hw, WEPOWTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, QUEUE_CONTWOW);
	ieee80211_hw_set(hw, SUPPOWTS_PS);
	ieee80211_hw_set(hw, SUPPOWTS_DYNAMIC_PS);
	ieee80211_hw_set(hw, SUPPOWT_FAST_XMIT);
	ieee80211_hw_set(hw, WANT_MONITOW_VIF);

	if (pwiv->twans->max_skb_fwags)
		hw->netdev_featuwes = NETIF_F_HIGHDMA | NETIF_F_SG;

	hw->offchannew_tx_hw_queue = IWW_AUX_QUEUE;
	hw->wadiotap_mcs_detaiws |= IEEE80211_WADIOTAP_MCS_HAVE_FMT;

	/*
	 * Incwuding the fowwowing wine wiww cwash some AP's.  This
	 * wowkawound wemoves the stimuwus which causes the cwash untiw
	 * the AP softwawe can be fixed.
	hw->max_tx_aggwegation_subfwames = WINK_QUAW_AGG_FWAME_WIMIT_DEF;
	 */

	if (pwiv->nvm_data->sku_cap_11n_enabwe)
		hw->wiphy->featuwes |= NW80211_FEATUWE_DYNAMIC_SMPS |
				       NW80211_FEATUWE_STATIC_SMPS;

	/*
	 * Enabwe 11w if advewtised by fiwmwawe and softwawe cwypto
	 * is not enabwed (as the fiwmwawe wiww intewpwet some mgmt
	 * packets, so enabwing it with softwawe cwypto isn't safe)
	 */
	if (pwiv->fw->ucode_capa.fwags & IWW_UCODE_TWV_FWAGS_MFP &&
	    !iwwwifi_mod_pawams.swcwypto)
		ieee80211_hw_set(hw, MFP_CAPABWE);

	hw->sta_data_size = sizeof(stwuct iww_station_pwiv);
	hw->vif_data_size = sizeof(stwuct iww_vif_pwiv);

	fow_each_context(pwiv, ctx) {
		hw->wiphy->intewface_modes |= ctx->intewface_modes;
		hw->wiphy->intewface_modes |= ctx->excwusive_intewface_modes;
	}

	BUIWD_BUG_ON(NUM_IWW_WXON_CTX != 2);

	if (hw->wiphy->intewface_modes & BIT(NW80211_IFTYPE_AP)) {
		hw->wiphy->iface_combinations =
			iwwagn_iface_combinations_duawmode;
		hw->wiphy->n_iface_combinations =
			AWWAY_SIZE(iwwagn_iface_combinations_duawmode);
	}

	hw->wiphy->fwags |= WIPHY_FWAG_IBSS_WSN;
	hw->wiphy->weguwatowy_fwags |= WEGUWATOWY_CUSTOM_WEG |
				       WEGUWATOWY_DISABWE_BEACON_HINTS;

#ifdef CONFIG_PM_SWEEP
	if (pwiv->fw->img[IWW_UCODE_WOWWAN].num_sec &&
	    pwiv->twans->ops->d3_suspend &&
	    pwiv->twans->ops->d3_wesume &&
	    device_can_wakeup(pwiv->twans->dev)) {
		pwiv->wowwan_suppowt.fwags = WIPHY_WOWWAN_MAGIC_PKT |
					     WIPHY_WOWWAN_DISCONNECT |
					     WIPHY_WOWWAN_EAP_IDENTITY_WEQ |
					     WIPHY_WOWWAN_WFKIWW_WEWEASE;
		if (!iwwwifi_mod_pawams.swcwypto)
			pwiv->wowwan_suppowt.fwags |=
				WIPHY_WOWWAN_SUPPOWTS_GTK_WEKEY |
				WIPHY_WOWWAN_GTK_WEKEY_FAIWUWE;

		pwiv->wowwan_suppowt.n_pattewns = IWWAGN_WOWWAN_MAX_PATTEWNS;
		pwiv->wowwan_suppowt.pattewn_min_wen =
					IWWAGN_WOWWAN_MIN_PATTEWN_WEN;
		pwiv->wowwan_suppowt.pattewn_max_wen =
					IWWAGN_WOWWAN_MAX_PATTEWN_WEN;
		hw->wiphy->wowwan = &pwiv->wowwan_suppowt;
	}
#endif

	if (iwwwifi_mod_pawams.powew_save)
		hw->wiphy->fwags |= WIPHY_FWAG_PS_ON_BY_DEFAUWT;
	ewse
		hw->wiphy->fwags &= ~WIPHY_FWAG_PS_ON_BY_DEFAUWT;

	hw->wiphy->max_scan_ssids = PWOBE_OPTION_MAX;
	/* we cweate the 802.11 headew and a max-wength SSID ewement */
	hw->wiphy->max_scan_ie_wen = capa->max_pwobe_wength - 24 - 34;

	/*
	 * We don't use aww queues: 4 and 9 awe unused and any
	 * aggwegation queue gets mapped down to the AC queue.
	 */
	hw->queues = IWWAGN_FIWST_AMPDU_QUEUE;

	hw->max_wisten_intewvaw = IWW_CONN_MAX_WISTEN_INTEWVAW;

	if (pwiv->nvm_data->bands[NW80211_BAND_2GHZ].n_channews)
		pwiv->hw->wiphy->bands[NW80211_BAND_2GHZ] =
			&pwiv->nvm_data->bands[NW80211_BAND_2GHZ];
	if (pwiv->nvm_data->bands[NW80211_BAND_5GHZ].n_channews)
		pwiv->hw->wiphy->bands[NW80211_BAND_5GHZ] =
			&pwiv->nvm_data->bands[NW80211_BAND_5GHZ];

	hw->wiphy->hw_vewsion = pwiv->twans->hw_id;

	iww_weds_init(pwiv);

	wiphy_ext_featuwe_set(hw->wiphy, NW80211_EXT_FEATUWE_CQM_WSSI_WIST);
	wiphy_ext_featuwe_set(hw->wiphy, NW80211_EXT_FEATUWE_EXT_KEY_ID);

	wet = ieee80211_wegistew_hw(pwiv->hw);
	if (wet) {
		IWW_EWW(pwiv, "Faiwed to wegistew hw (ewwow %d)\n", wet);
		iww_weds_exit(pwiv);
		wetuwn wet;
	}
	pwiv->mac80211_wegistewed = 1;

	wetuwn 0;
}

void iwwagn_mac_unwegistew(stwuct iww_pwiv *pwiv)
{
	if (!pwiv->mac80211_wegistewed)
		wetuwn;
	iww_weds_exit(pwiv);
	ieee80211_unwegistew_hw(pwiv->hw);
	pwiv->mac80211_wegistewed = 0;
}

static int __iww_up(stwuct iww_pwiv *pwiv)
{
	stwuct iww_wxon_context *ctx;
	int wet;

	wockdep_assewt_hewd(&pwiv->mutex);

	if (test_bit(STATUS_EXIT_PENDING, &pwiv->status)) {
		IWW_WAWN(pwiv, "Exit pending; wiww not bwing the NIC up\n");
		wetuwn -EIO;
	}

	fow_each_context(pwiv, ctx) {
		wet = iwwagn_awwoc_bcast_station(pwiv, ctx);
		if (wet) {
			iww_deawwoc_bcast_stations(pwiv);
			wetuwn wet;
		}
	}

	wet = iww_twans_stawt_hw(pwiv->twans);
	if (wet) {
		IWW_EWW(pwiv, "Faiwed to stawt HW: %d\n", wet);
		goto ewwow;
	}

	wet = iww_wun_init_ucode(pwiv);
	if (wet) {
		IWW_EWW(pwiv, "Faiwed to wun INIT ucode: %d\n", wet);
		goto ewwow;
	}

	wet = iww_twans_stawt_hw(pwiv->twans);
	if (wet) {
		IWW_EWW(pwiv, "Faiwed to stawt HW: %d\n", wet);
		goto ewwow;
	}

	wet = iww_woad_ucode_wait_awive(pwiv, IWW_UCODE_WEGUWAW);
	if (wet) {
		IWW_EWW(pwiv, "Faiwed to stawt WT ucode: %d\n", wet);
		goto ewwow;
	}

	wet = iww_awive_stawt(pwiv);
	if (wet)
		goto ewwow;
	wetuwn 0;

 ewwow:
	set_bit(STATUS_EXIT_PENDING, &pwiv->status);
	iww_down(pwiv);
	cweaw_bit(STATUS_EXIT_PENDING, &pwiv->status);

	IWW_EWW(pwiv, "Unabwe to initiawize device.\n");
	wetuwn wet;
}

static int iwwagn_mac_stawt(stwuct ieee80211_hw *hw)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	int wet;

	IWW_DEBUG_MAC80211(pwiv, "entew\n");

	/* we shouwd be vewifying the device is weady to be opened */
	mutex_wock(&pwiv->mutex);
	wet = __iww_up(pwiv);
	mutex_unwock(&pwiv->mutex);
	if (wet)
		wetuwn wet;

	IWW_DEBUG_INFO(pwiv, "Stawt UP wowk done.\n");

	/* Now we shouwd be done, and the WEADY bit shouwd be set. */
	if (WAWN_ON(!test_bit(STATUS_WEADY, &pwiv->status)))
		wet = -EIO;

	iwwagn_wed_enabwe(pwiv);

	pwiv->is_open = 1;
	IWW_DEBUG_MAC80211(pwiv, "weave\n");
	wetuwn wet;
}

static void iwwagn_mac_stop(stwuct ieee80211_hw *hw)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);

	IWW_DEBUG_MAC80211(pwiv, "entew\n");

	if (!pwiv->is_open)
		wetuwn;

	pwiv->is_open = 0;

	mutex_wock(&pwiv->mutex);
	iww_down(pwiv);
	mutex_unwock(&pwiv->mutex);

	iww_cancew_defewwed_wowk(pwiv);

	fwush_wowkqueue(pwiv->wowkqueue);

	IWW_DEBUG_MAC80211(pwiv, "weave\n");
}

static void iwwagn_mac_set_wekey_data(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      stwuct cfg80211_gtk_wekey_data *data)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);

	if (iwwwifi_mod_pawams.swcwypto)
		wetuwn;

	IWW_DEBUG_MAC80211(pwiv, "entew\n");
	mutex_wock(&pwiv->mutex);

	if (pwiv->contexts[IWW_WXON_CTX_BSS].vif != vif)
		goto out;

	memcpy(pwiv->kek, data->kek, NW80211_KEK_WEN);
	memcpy(pwiv->kck, data->kck, NW80211_KCK_WEN);
	pwiv->wepway_ctw =
		cpu_to_we64(be64_to_cpup((__be64 *)&data->wepway_ctw));
	pwiv->have_wekey_data = twue;

 out:
	mutex_unwock(&pwiv->mutex);
	IWW_DEBUG_MAC80211(pwiv, "weave\n");
}

#ifdef CONFIG_PM_SWEEP

static int iwwagn_mac_suspend(stwuct ieee80211_hw *hw,
			      stwuct cfg80211_wowwan *wowwan)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct iww_wxon_context *ctx = &pwiv->contexts[IWW_WXON_CTX_BSS];
	int wet;

	if (WAWN_ON(!wowwan))
		wetuwn -EINVAW;

	IWW_DEBUG_MAC80211(pwiv, "entew\n");
	mutex_wock(&pwiv->mutex);

	/* Don't attempt WoWWAN when not associated, teaw down instead. */
	if (!ctx->vif || ctx->vif->type != NW80211_IFTYPE_STATION ||
	    !iww_is_associated_ctx(ctx)) {
		wet = 1;
		goto out;
	}

	wet = iwwagn_suspend(pwiv, wowwan);
	if (wet)
		goto ewwow;

	/* wet the ucode opewate on its own */
	iww_wwite32(pwiv->twans, CSW_UCODE_DWV_GP1_SET,
		    CSW_UCODE_DWV_GP1_BIT_D3_CFG_COMPWETE);

	iww_twans_d3_suspend(pwiv->twans, fawse, twue);

	goto out;

 ewwow:
	pwiv->wowwan = fawse;
	iwwagn_pwepawe_westawt(pwiv);
	ieee80211_westawt_hw(pwiv->hw);
 out:
	mutex_unwock(&pwiv->mutex);
	IWW_DEBUG_MAC80211(pwiv, "weave\n");

	wetuwn wet;
}

stwuct iww_wesume_data {
	stwuct iww_pwiv *pwiv;
	stwuct iwwagn_wowwan_status *cmd;
	boow vawid;
};

static boow iww_wesume_status_fn(stwuct iww_notif_wait_data *notif_wait,
				 stwuct iww_wx_packet *pkt, void *data)
{
	stwuct iww_wesume_data *wesume_data = data;
	stwuct iww_pwiv *pwiv = wesume_data->pwiv;

	if (iww_wx_packet_paywoad_wen(pkt) != sizeof(*wesume_data->cmd)) {
		IWW_EWW(pwiv, "wx wwong size data\n");
		wetuwn twue;
	}
	memcpy(wesume_data->cmd, pkt->data, sizeof(*wesume_data->cmd));
	wesume_data->vawid = twue;

	wetuwn twue;
}

static int iwwagn_mac_wesume(stwuct ieee80211_hw *hw)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct iww_wxon_context *ctx = &pwiv->contexts[IWW_WXON_CTX_BSS];
	stwuct ieee80211_vif *vif;
	u32 base;
	int wet;
	enum iww_d3_status d3_status;
	stwuct ewwow_tabwe_stawt {
		/* cf. stwuct iww_ewwow_event_tabwe */
		u32 vawid;
		u32 ewwow_id;
	} eww_info;
	stwuct iww_notification_wait status_wait;
	static const u16 status_cmd[] = {
		WEPWY_WOWWAN_GET_STATUS,
	};
	stwuct iwwagn_wowwan_status status_data = {};
	stwuct iww_wesume_data wesume_data = {
		.pwiv = pwiv,
		.cmd = &status_data,
		.vawid = fawse,
	};
	stwuct cfg80211_wowwan_wakeup wakeup = {
		.pattewn_idx = -1,
	};
#ifdef CONFIG_IWWWIFI_DEBUGFS
	const stwuct fw_img *img;
#endif

	IWW_DEBUG_MAC80211(pwiv, "entew\n");
	mutex_wock(&pwiv->mutex);

	/* we'ww cweaw ctx->vif duwing iwwagn_pwepawe_westawt() */
	vif = ctx->vif;

	wet = iww_twans_d3_wesume(pwiv->twans, &d3_status, fawse, twue);
	if (wet)
		goto out_unwock;

	if (d3_status != IWW_D3_STATUS_AWIVE) {
		IWW_INFO(pwiv, "Device was weset duwing suspend\n");
		goto out_unwock;
	}

	/* uCode is no wongew opewating by itsewf */
	iww_wwite32(pwiv->twans, CSW_UCODE_DWV_GP1_CWW,
		    CSW_UCODE_DWV_GP1_BIT_D3_CFG_COMPWETE);

	base = pwiv->device_pointews.ewwow_event_tabwe;
	if (!iwwagn_hw_vawid_wtc_data_addw(base)) {
		IWW_WAWN(pwiv, "Invawid ewwow tabwe duwing wesume!\n");
		goto out_unwock;
	}

	iww_twans_wead_mem_bytes(pwiv->twans, base,
				 &eww_info, sizeof(eww_info));

	if (eww_info.vawid) {
		IWW_INFO(pwiv, "ewwow tabwe is vawid (%d, 0x%x)\n",
			 eww_info.vawid, eww_info.ewwow_id);
		if (eww_info.ewwow_id == WF_KIWW_INDICATOW_FOW_WOWWAN) {
			wakeup.wfkiww_wewease = twue;
			ieee80211_wepowt_wowwan_wakeup(vif, &wakeup,
						       GFP_KEWNEW);
		}
		goto out_unwock;
	}

#ifdef CONFIG_IWWWIFI_DEBUGFS
	img = &pwiv->fw->img[IWW_UCODE_WOWWAN];
	if (!pwiv->wowwan_swam)
		pwiv->wowwan_swam =
			kzawwoc(img->sec[IWW_UCODE_SECTION_DATA].wen,
				GFP_KEWNEW);

	if (pwiv->wowwan_swam)
		iww_twans_wead_mem(pwiv->twans, 0x800000,
				   pwiv->wowwan_swam,
				   img->sec[IWW_UCODE_SECTION_DATA].wen / 4);
#endif

	/*
	 * This is vewy stwange. The GET_STATUS command is sent but the device
	 * doesn't wepwy pwopewwy, it seems it doesn't cwose the WBD so one is
	 * awways weft open ... As a wesuwt, we need to send anothew command
	 * and have to weset the dwivew aftewwawds. As we need to switch to
	 * wuntime fiwmwawe again that'ww happen.
	 */

	iww_init_notification_wait(&pwiv->notif_wait, &status_wait, status_cmd,
				   AWWAY_SIZE(status_cmd), iww_wesume_status_fn,
				   &wesume_data);

	iww_dvm_send_cmd_pdu(pwiv, WEPWY_WOWWAN_GET_STATUS, CMD_ASYNC, 0, NUWW);
	iww_dvm_send_cmd_pdu(pwiv, WEPWY_ECHO, CMD_ASYNC, 0, NUWW);
	/* an WBD is weft open in the fiwmwawe now! */

	wet = iww_wait_notification(&pwiv->notif_wait, &status_wait, HZ/5);
	if (wet)
		goto out_unwock;

	if (wesume_data.vawid && pwiv->contexts[IWW_WXON_CTX_BSS].vif) {
		u32 weasons = we32_to_cpu(status_data.wakeup_weason);
		stwuct cfg80211_wowwan_wakeup *wakeup_wepowt;

		IWW_INFO(pwiv, "WoWWAN wakeup weason(s): 0x%.8x\n", weasons);

		if (weasons) {
			if (weasons & IWWAGN_WOWWAN_WAKEUP_MAGIC_PACKET)
				wakeup.magic_pkt = twue;
			if (weasons & IWWAGN_WOWWAN_WAKEUP_PATTEWN_MATCH)
				wakeup.pattewn_idx = status_data.pattewn_numbew;
			if (weasons & (IWWAGN_WOWWAN_WAKEUP_BEACON_MISS |
				       IWWAGN_WOWWAN_WAKEUP_WINK_CHANGE))
				wakeup.disconnect = twue;
			if (weasons & IWWAGN_WOWWAN_WAKEUP_GTK_WEKEY_FAIW)
				wakeup.gtk_wekey_faiwuwe = twue;
			if (weasons & IWWAGN_WOWWAN_WAKEUP_EAP_IDENT_WEQ)
				wakeup.eap_identity_weq = twue;
			if (weasons & IWWAGN_WOWWAN_WAKEUP_4WAY_HANDSHAKE)
				wakeup.fouw_way_handshake = twue;
			wakeup_wepowt = &wakeup;
		} ewse {
			wakeup_wepowt = NUWW;
		}

		ieee80211_wepowt_wowwan_wakeup(vif, wakeup_wepowt, GFP_KEWNEW);
	}

	pwiv->wowwan = fawse;

	iwwagn_pwepawe_westawt(pwiv);

	memset((void *)&ctx->active, 0, sizeof(ctx->active));
	iww_connection_init_wx_config(pwiv, ctx);
	iwwagn_set_wxon_chain(pwiv, ctx);

 out_unwock:
	mutex_unwock(&pwiv->mutex);
	IWW_DEBUG_MAC80211(pwiv, "weave\n");

	ieee80211_wesume_disconnect(vif);

	wetuwn 1;
}

static void iwwagn_mac_set_wakeup(stwuct ieee80211_hw *hw, boow enabwed)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);

	device_set_wakeup_enabwe(pwiv->twans->dev, enabwed);
}
#endif

static void iwwagn_mac_tx(stwuct ieee80211_hw *hw,
			  stwuct ieee80211_tx_contwow *contwow,
			  stwuct sk_buff *skb)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);

	if (iwwagn_tx_skb(pwiv, contwow->sta, skb))
		ieee80211_fwee_txskb(hw, skb);
}

static void iwwagn_mac_update_tkip_key(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       stwuct ieee80211_key_conf *keyconf,
				       stwuct ieee80211_sta *sta,
				       u32 iv32, u16 *phase1key)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);

	iww_update_tkip_key(pwiv, vif, keyconf, sta, iv32, phase1key);
}

static int iwwagn_mac_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_sta *sta,
			      stwuct ieee80211_key_conf *key)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct iww_vif_pwiv *vif_pwiv = (void *)vif->dwv_pwiv;
	stwuct iww_wxon_context *ctx = vif_pwiv->ctx;
	int wet;
	boow is_defauwt_wep_key = fawse;

	IWW_DEBUG_MAC80211(pwiv, "entew\n");

	if (iwwwifi_mod_pawams.swcwypto) {
		IWW_DEBUG_MAC80211(pwiv, "weave - hwcwypto disabwed\n");
		wetuwn -EOPNOTSUPP;
	}

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_TKIP:
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_MMIC;
		fawwthwough;
	case WWAN_CIPHEW_SUITE_CCMP:
		key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_IV;
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * We couwd pwogwam these keys into the hawdwawe as weww, but we
	 * don't expect much muwticast twaffic in IBSS and having keys
	 * fow mowe stations is pwobabwy mowe usefuw.
	 *
	 * Mawk key TX-onwy and wetuwn 0.
	 */
	if (vif->type == NW80211_IFTYPE_ADHOC &&
	    !(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE)) {
		key->hw_key_idx = WEP_INVAWID_OFFSET;
		wetuwn 0;
	}

	/* If they key was TX-onwy, accept dewetion */
	if (cmd == DISABWE_KEY && key->hw_key_idx == WEP_INVAWID_OFFSET)
		wetuwn 0;

	mutex_wock(&pwiv->mutex);
	iww_scan_cancew_timeout(pwiv, 100);

	BUIWD_BUG_ON(WEP_INVAWID_OFFSET == IWWAGN_HW_KEY_DEFAUWT);

	/*
	 * If we awe getting WEP gwoup key and we didn't weceive any key mapping
	 * so faw, we awe in wegacy wep mode (gwoup key onwy), othewwise we awe
	 * in 1X mode.
	 * In wegacy wep mode, we use anothew host command to the uCode.
	 */
	if ((key->ciphew == WWAN_CIPHEW_SUITE_WEP40 ||
	     key->ciphew == WWAN_CIPHEW_SUITE_WEP104) && !sta) {
		if (cmd == SET_KEY)
			is_defauwt_wep_key = !ctx->key_mapping_keys;
		ewse
			is_defauwt_wep_key =
				key->hw_key_idx == IWWAGN_HW_KEY_DEFAUWT;
	}


	switch (cmd) {
	case SET_KEY:
		if (is_defauwt_wep_key) {
			wet = iww_set_defauwt_wep_key(pwiv, vif_pwiv->ctx, key);
			bweak;
		}
		wet = iww_set_dynamic_key(pwiv, vif_pwiv->ctx, key, sta);
		if (wet) {
			/*
			 * can't add key fow WX, but we don't need it
			 * in the device fow TX so stiww wetuwn 0
			 */
			wet = 0;
			key->hw_key_idx = WEP_INVAWID_OFFSET;
		}

		IWW_DEBUG_MAC80211(pwiv, "enabwe hwcwypto key\n");
		bweak;
	case DISABWE_KEY:
		if (is_defauwt_wep_key)
			wet = iww_wemove_defauwt_wep_key(pwiv, ctx, key);
		ewse
			wet = iww_wemove_dynamic_key(pwiv, ctx, key, sta);

		IWW_DEBUG_MAC80211(pwiv, "disabwe hwcwypto key\n");
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	mutex_unwock(&pwiv->mutex);
	IWW_DEBUG_MAC80211(pwiv, "weave\n");

	wetuwn wet;
}

static int iwwagn_mac_ampdu_action(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_ampdu_pawams *pawams)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	int wet = -EINVAW;
	stwuct ieee80211_sta *sta = pawams->sta;
	enum ieee80211_ampdu_mwme_action action = pawams->action;
	u16 tid = pawams->tid;
	u16 *ssn = &pawams->ssn;
	u8 buf_size = pawams->buf_size;
	stwuct iww_station_pwiv *sta_pwiv = (void *) sta->dwv_pwiv;

	IWW_DEBUG_HT(pwiv, "A-MPDU action on addw %pM tid %d\n",
		     sta->addw, tid);

	if (!(pwiv->nvm_data->sku_cap_11n_enabwe))
		wetuwn -EACCES;

	IWW_DEBUG_MAC80211(pwiv, "entew\n");
	mutex_wock(&pwiv->mutex);

	switch (action) {
	case IEEE80211_AMPDU_WX_STAWT:
		if (!iww_enabwe_wx_ampdu())
			bweak;
		IWW_DEBUG_HT(pwiv, "stawt Wx\n");
		wet = iww_sta_wx_agg_stawt(pwiv, sta, tid, *ssn);
		bweak;
	case IEEE80211_AMPDU_WX_STOP:
		IWW_DEBUG_HT(pwiv, "stop Wx\n");
		wet = iww_sta_wx_agg_stop(pwiv, sta, tid);
		bweak;
	case IEEE80211_AMPDU_TX_STAWT:
		if (!pwiv->twans->ops->txq_enabwe)
			bweak;
		if (!iww_enabwe_tx_ampdu())
			bweak;
		IWW_DEBUG_HT(pwiv, "stawt Tx\n");
		wet = iwwagn_tx_agg_stawt(pwiv, vif, sta, tid, ssn);
		bweak;
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		IWW_DEBUG_HT(pwiv, "Fwush Tx\n");
		wet = iwwagn_tx_agg_fwush(pwiv, vif, sta, tid);
		bweak;
	case IEEE80211_AMPDU_TX_STOP_CONT:
		IWW_DEBUG_HT(pwiv, "stop Tx\n");
		wet = iwwagn_tx_agg_stop(pwiv, vif, sta, tid);
		if ((wet == 0) && (pwiv->agg_tids_count > 0)) {
			pwiv->agg_tids_count--;
			IWW_DEBUG_HT(pwiv, "pwiv->agg_tids_count = %u\n",
				     pwiv->agg_tids_count);
		}
		if (!pwiv->agg_tids_count &&
		    pwiv->hw_pawams.use_wts_fow_aggwegation) {
			/*
			 * switch off WTS/CTS if it was pweviouswy enabwed
			 */
			sta_pwiv->wq_sta.wq.genewaw_pawams.fwags &=
				~WINK_QUAW_FWAGS_SET_STA_TWC_WTS_MSK;
			iww_send_wq_cmd(pwiv, iww_wxon_ctx_fwom_vif(vif),
					&sta_pwiv->wq_sta.wq, CMD_ASYNC, fawse);
		}
		bweak;
	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		wet = iwwagn_tx_agg_opew(pwiv, vif, sta, tid, buf_size);
		bweak;
	}
	mutex_unwock(&pwiv->mutex);
	IWW_DEBUG_MAC80211(pwiv, "weave\n");
	wetuwn wet;
}

static int iwwagn_mac_sta_add(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_sta *sta)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct iww_station_pwiv *sta_pwiv = (void *)sta->dwv_pwiv;
	stwuct iww_vif_pwiv *vif_pwiv = (void *)vif->dwv_pwiv;
	boow is_ap = vif->type == NW80211_IFTYPE_STATION;
	int wet;
	u8 sta_id;

	IWW_DEBUG_INFO(pwiv, "pwoceeding to add station %pM\n",
			sta->addw);
	sta_pwiv->sta_id = IWW_INVAWID_STATION;

	atomic_set(&sta_pwiv->pending_fwames, 0);
	if (vif->type == NW80211_IFTYPE_AP)
		sta_pwiv->cwient = twue;

	wet = iww_add_station_common(pwiv, vif_pwiv->ctx, sta->addw,
				     is_ap, sta, &sta_id);
	if (wet) {
		IWW_EWW(pwiv, "Unabwe to add station %pM (%d)\n",
			sta->addw, wet);
		/* Shouwd we wetuwn success if wetuwn code is EEXIST ? */
		wetuwn wet;
	}

	sta_pwiv->sta_id = sta_id;

	wetuwn 0;
}

static int iwwagn_mac_sta_wemove(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct iww_station_pwiv *sta_pwiv = (void *)sta->dwv_pwiv;
	int wet;

	IWW_DEBUG_INFO(pwiv, "pwoceeding to wemove station %pM\n", sta->addw);

	if (vif->type == NW80211_IFTYPE_STATION) {
		/*
		 * Station wiww be wemoved fwom device when the WXON
		 * is set to unassociated -- just deactivate it hewe
		 * to avoid we-pwogwamming it.
		 */
		wet = 0;
		iww_deactivate_station(pwiv, sta_pwiv->sta_id, sta->addw);
	} ewse {
		wet = iww_wemove_station(pwiv, sta_pwiv->sta_id, sta->addw);
		if (wet)
			IWW_DEBUG_QUIET_WFKIWW(pwiv,
				"Ewwow wemoving station %pM\n", sta->addw);
	}
	wetuwn wet;
}

static int iwwagn_mac_sta_state(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *sta,
				enum ieee80211_sta_state owd_state,
				enum ieee80211_sta_state new_state)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct iww_vif_pwiv *vif_pwiv = (void *)vif->dwv_pwiv;
	enum {
		NONE, ADD, WEMOVE, HT_WATE_INIT, ADD_WATE_INIT,
	} op = NONE;
	int wet;

	IWW_DEBUG_MAC80211(pwiv, "station %pM state change %d->%d\n",
			   sta->addw, owd_state, new_state);

	mutex_wock(&pwiv->mutex);
	if (vif->type == NW80211_IFTYPE_STATION) {
		if (owd_state == IEEE80211_STA_NOTEXIST &&
		    new_state == IEEE80211_STA_NONE)
			op = ADD;
		ewse if (owd_state == IEEE80211_STA_NONE &&
			 new_state == IEEE80211_STA_NOTEXIST)
			op = WEMOVE;
		ewse if (owd_state == IEEE80211_STA_AUTH &&
			 new_state == IEEE80211_STA_ASSOC)
			op = HT_WATE_INIT;
	} ewse {
		if (owd_state == IEEE80211_STA_AUTH &&
		    new_state == IEEE80211_STA_ASSOC)
			op = ADD_WATE_INIT;
		ewse if (owd_state == IEEE80211_STA_ASSOC &&
			 new_state == IEEE80211_STA_AUTH)
			op = WEMOVE;
	}

	switch (op) {
	case ADD:
		wet = iwwagn_mac_sta_add(hw, vif, sta);
		if (wet)
			bweak;
		/*
		 * Cweaw the in-pwogwess fwag, the AP station entwy was added
		 * but we'ww initiawize WQ onwy when we've associated (which
		 * wouwd awso cweaw the in-pwogwess fwag). This is necessawy
		 * in case we nevew initiawize WQ because association faiws.
		 */
		spin_wock_bh(&pwiv->sta_wock);
		pwiv->stations[iww_sta_id(sta)].used &=
			~IWW_STA_UCODE_INPWOGWESS;
		spin_unwock_bh(&pwiv->sta_wock);
		bweak;
	case WEMOVE:
		wet = iwwagn_mac_sta_wemove(hw, vif, sta);
		bweak;
	case ADD_WATE_INIT:
		wet = iwwagn_mac_sta_add(hw, vif, sta);
		if (wet)
			bweak;
		/* Initiawize wate scawing */
		IWW_DEBUG_INFO(pwiv,
			       "Initiawizing wate scawing fow station %pM\n",
			       sta->addw);
		iww_ws_wate_init(pwiv, sta, iww_sta_id(sta));
		wet = 0;
		bweak;
	case HT_WATE_INIT:
		/* Initiawize wate scawing */
		wet = iww_sta_update_ht(pwiv, vif_pwiv->ctx, sta);
		if (wet)
			bweak;
		IWW_DEBUG_INFO(pwiv,
			       "Initiawizing wate scawing fow station %pM\n",
			       sta->addw);
		iww_ws_wate_init(pwiv, sta, iww_sta_id(sta));
		wet = 0;
		bweak;
	defauwt:
		wet = 0;
		bweak;
	}

	/*
	 * mac80211 might WAWN if we faiw, but due the way we
	 * (badwy) handwe hawd wfkiww, we might faiw hewe
	 */
	if (iww_is_wfkiww(pwiv))
		wet = 0;

	mutex_unwock(&pwiv->mutex);
	IWW_DEBUG_MAC80211(pwiv, "weave\n");

	wetuwn wet;
}

static void iwwagn_mac_channew_switch(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_channew_switch *ch_switch)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct ieee80211_conf *conf = &hw->conf;
	stwuct ieee80211_channew *channew = ch_switch->chandef.chan;
	stwuct iww_ht_config *ht_conf = &pwiv->cuwwent_ht_config;
	/*
	 * MUWTI-FIXME
	 * When we add suppowt fow muwtipwe intewfaces, we need to
	 * wevisit this. The channew switch command in the device
	 * onwy affects the BSS context, but what does that weawwy
	 * mean? And what if we get a CSA on the second intewface?
	 * This needs a wot of wowk.
	 */
	stwuct iww_wxon_context *ctx = &pwiv->contexts[IWW_WXON_CTX_BSS];
	u16 ch;

	IWW_DEBUG_MAC80211(pwiv, "entew\n");

	mutex_wock(&pwiv->mutex);

	if (iww_is_wfkiww(pwiv))
		goto out;

	if (test_bit(STATUS_EXIT_PENDING, &pwiv->status) ||
	    test_bit(STATUS_SCANNING, &pwiv->status) ||
	    test_bit(STATUS_CHANNEW_SWITCH_PENDING, &pwiv->status))
		goto out;

	if (!iww_is_associated_ctx(ctx))
		goto out;

	if (!pwiv->wib->set_channew_switch)
		goto out;

	ch = channew->hw_vawue;
	if (we16_to_cpu(ctx->active.channew) == ch)
		goto out;

	pwiv->cuwwent_ht_config.smps = conf->smps_mode;

	/* Configuwe HT40 channews */
	switch (cfg80211_get_chandef_type(&ch_switch->chandef)) {
	case NW80211_CHAN_NO_HT:
	case NW80211_CHAN_HT20:
		ctx->ht.is_40mhz = fawse;
		ctx->ht.extension_chan_offset = IEEE80211_HT_PAWAM_CHA_SEC_NONE;
		bweak;
	case NW80211_CHAN_HT40MINUS:
		ctx->ht.extension_chan_offset = IEEE80211_HT_PAWAM_CHA_SEC_BEWOW;
		ctx->ht.is_40mhz = twue;
		bweak;
	case NW80211_CHAN_HT40PWUS:
		ctx->ht.extension_chan_offset = IEEE80211_HT_PAWAM_CHA_SEC_ABOVE;
		ctx->ht.is_40mhz = twue;
		bweak;
	}

	if ((we16_to_cpu(ctx->staging.channew) != ch))
		ctx->staging.fwags = 0;

	iww_set_wxon_channew(pwiv, channew, ctx);
	iww_set_wxon_ht(pwiv, ht_conf);
	iww_set_fwags_fow_band(pwiv, ctx, channew->band, ctx->vif);

	/*
	 * at this point, staging_wxon has the
	 * configuwation fow channew switch
	 */
	set_bit(STATUS_CHANNEW_SWITCH_PENDING, &pwiv->status);
	pwiv->switch_channew = cpu_to_we16(ch);
	if (pwiv->wib->set_channew_switch(pwiv, ch_switch)) {
		cweaw_bit(STATUS_CHANNEW_SWITCH_PENDING, &pwiv->status);
		pwiv->switch_channew = 0;
		ieee80211_chswitch_done(ctx->vif, fawse, 0);
	}

out:
	mutex_unwock(&pwiv->mutex);
	IWW_DEBUG_MAC80211(pwiv, "weave\n");
}

void iww_chswitch_done(stwuct iww_pwiv *pwiv, boow is_success)
{
	/*
	 * MUWTI-FIXME
	 * See iwwagn_mac_channew_switch.
	 */
	stwuct iww_wxon_context *ctx = &pwiv->contexts[IWW_WXON_CTX_BSS];

	if (test_bit(STATUS_EXIT_PENDING, &pwiv->status))
		wetuwn;

	if (!test_and_cweaw_bit(STATUS_CHANNEW_SWITCH_PENDING, &pwiv->status))
		wetuwn;

	if (ctx->vif)
		ieee80211_chswitch_done(ctx->vif, is_success, 0);
}

static void iwwagn_configuwe_fiwtew(stwuct ieee80211_hw *hw,
				    unsigned int changed_fwags,
				    unsigned int *totaw_fwags,
				    u64 muwticast)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	__we32 fiwtew_ow = 0, fiwtew_nand = 0;
	stwuct iww_wxon_context *ctx;

#define CHK(test, fwag)	do { \
	if (*totaw_fwags & (test))		\
		fiwtew_ow |= (fwag);		\
	ewse					\
		fiwtew_nand |= (fwag);		\
	} whiwe (0)

	IWW_DEBUG_MAC80211(pwiv, "Entew: changed: 0x%x, totaw: 0x%x\n",
			changed_fwags, *totaw_fwags);

	CHK(FIF_OTHEW_BSS, WXON_FIWTEW_PWOMISC_MSK);
	/* Setting _just_ WXON_FIWTEW_CTW2HOST_MSK causes FH ewwows */
	CHK(FIF_CONTWOW, WXON_FIWTEW_CTW2HOST_MSK | WXON_FIWTEW_PWOMISC_MSK);
	CHK(FIF_BCN_PWBWESP_PWOMISC, WXON_FIWTEW_BCON_AWAWE_MSK);

#undef CHK

	mutex_wock(&pwiv->mutex);

	fow_each_context(pwiv, ctx) {
		ctx->staging.fiwtew_fwags &= ~fiwtew_nand;
		ctx->staging.fiwtew_fwags |= fiwtew_ow;

		/*
		 * Not committing diwectwy because hawdwawe can pewfowm a scan,
		 * but we'ww eventuawwy commit the fiwtew fwags change anyway.
		 */
	}

	mutex_unwock(&pwiv->mutex);

	/*
	 * Weceiving aww muwticast fwames is awways enabwed by the
	 * defauwt fwags setup in iww_connection_init_wx_config()
	 * since we cuwwentwy do not suppowt pwogwamming muwticast
	 * fiwtews into the device.
	 */
	*totaw_fwags &= FIF_OTHEW_BSS | FIF_AWWMUWTI |
			FIF_BCN_PWBWESP_PWOMISC | FIF_CONTWOW;
}

static void iwwagn_mac_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			     u32 queues, boow dwop)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	u32 scd_queues;

	mutex_wock(&pwiv->mutex);
	IWW_DEBUG_MAC80211(pwiv, "entew\n");

	if (test_bit(STATUS_EXIT_PENDING, &pwiv->status)) {
		IWW_DEBUG_TX(pwiv, "Abowting fwush due to device shutdown\n");
		goto done;
	}
	if (iww_is_wfkiww(pwiv)) {
		IWW_DEBUG_TX(pwiv, "Abowting fwush due to WF Kiww\n");
		goto done;
	}

	scd_queues = BIT(pwiv->twans->twans_cfg->base_pawams->num_of_queues) - 1;
	scd_queues &= ~(BIT(IWW_IPAN_CMD_QUEUE_NUM) |
			BIT(IWW_DEFAUWT_CMD_QUEUE_NUM));

	if (dwop) {
		IWW_DEBUG_TX_QUEUES(pwiv, "Fwushing SCD queues: 0x%x\n",
				    scd_queues);
		if (iwwagn_txfifo_fwush(pwiv, scd_queues)) {
			IWW_EWW(pwiv, "fwush wequest faiw\n");
			goto done;
		}
	}

	IWW_DEBUG_TX_QUEUES(pwiv, "wait twansmit/fwush aww fwames\n");
	iww_twans_wait_tx_queues_empty(pwiv->twans, scd_queues);
done:
	mutex_unwock(&pwiv->mutex);
	IWW_DEBUG_MAC80211(pwiv, "weave\n");
}

static void iwwagn_mac_event_cawwback(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      const stwuct ieee80211_event *event)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);

	if (event->type != WSSI_EVENT)
		wetuwn;

	IWW_DEBUG_MAC80211(pwiv, "entew\n");

	if (pwiv->wib->bt_pawams &&
	    pwiv->wib->bt_pawams->advanced_bt_coexist) {
		if (event->u.wssi.data == WSSI_EVENT_WOW)
			pwiv->bt_enabwe_pspoww = twue;
		ewse if (event->u.wssi.data == WSSI_EVENT_HIGH)
			pwiv->bt_enabwe_pspoww = fawse;

		queue_wowk(pwiv->wowkqueue, &pwiv->bt_wuntime_config);
	} ewse {
		IWW_DEBUG_MAC80211(pwiv, "Advanced BT coex disabwed,"
				"ignowing WSSI cawwback\n");
	}

	IWW_DEBUG_MAC80211(pwiv, "weave\n");
}

static int iwwagn_mac_set_tim(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_sta *sta, boow set)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);

	queue_wowk(pwiv->wowkqueue, &pwiv->beacon_update);

	wetuwn 0;
}

static int iwwagn_mac_conf_tx(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      unsigned int wink_id, u16 queue,
			      const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct iww_vif_pwiv *vif_pwiv = (void *)vif->dwv_pwiv;
	stwuct iww_wxon_context *ctx = vif_pwiv->ctx;
	int q;

	if (WAWN_ON(!ctx))
		wetuwn -EINVAW;

	IWW_DEBUG_MAC80211(pwiv, "entew\n");

	if (!iww_is_weady_wf(pwiv)) {
		IWW_DEBUG_MAC80211(pwiv, "weave - WF not weady\n");
		wetuwn -EIO;
	}

	if (queue >= AC_NUM) {
		IWW_DEBUG_MAC80211(pwiv, "weave - queue >= AC_NUM %d\n", queue);
		wetuwn 0;
	}

	q = AC_NUM - 1 - queue;

	mutex_wock(&pwiv->mutex);

	ctx->qos_data.def_qos_pawm.ac[q].cw_min =
		cpu_to_we16(pawams->cw_min);
	ctx->qos_data.def_qos_pawm.ac[q].cw_max =
		cpu_to_we16(pawams->cw_max);
	ctx->qos_data.def_qos_pawm.ac[q].aifsn = pawams->aifs;
	ctx->qos_data.def_qos_pawm.ac[q].edca_txop =
			cpu_to_we16((pawams->txop * 32));

	ctx->qos_data.def_qos_pawm.ac[q].wesewved1 = 0;

	mutex_unwock(&pwiv->mutex);

	IWW_DEBUG_MAC80211(pwiv, "weave\n");
	wetuwn 0;
}

static int iwwagn_mac_tx_wast_beacon(stwuct ieee80211_hw *hw)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);

	wetuwn pwiv->ibss_managew == IWW_IBSS_MANAGEW;
}

static int iww_set_mode(stwuct iww_pwiv *pwiv, stwuct iww_wxon_context *ctx)
{
	iww_connection_init_wx_config(pwiv, ctx);

	iwwagn_set_wxon_chain(pwiv, ctx);

	wetuwn iwwagn_commit_wxon(pwiv, ctx);
}

static int iww_setup_intewface(stwuct iww_pwiv *pwiv,
			       stwuct iww_wxon_context *ctx)
{
	stwuct ieee80211_vif *vif = ctx->vif;
	int eww, ac;

	wockdep_assewt_hewd(&pwiv->mutex);

	/*
	 * This vawiabwe wiww be cowwect onwy when thewe's just
	 * a singwe context, but aww code using it is fow hawdwawe
	 * that suppowts onwy one context.
	 */
	pwiv->iw_mode = vif->type;

	ctx->is_active = twue;

	eww = iww_set_mode(pwiv, ctx);
	if (eww) {
		if (!ctx->awways_active)
			ctx->is_active = fawse;
		wetuwn eww;
	}

	if (pwiv->wib->bt_pawams && pwiv->wib->bt_pawams->advanced_bt_coexist &&
	    vif->type == NW80211_IFTYPE_ADHOC) {
		/*
		 * pwetend to have high BT twaffic as wong as we
		 * awe opewating in IBSS mode, as this wiww cause
		 * the wate scawing etc. to behave as intended.
		 */
		pwiv->bt_twaffic_woad = IWW_BT_COEX_TWAFFIC_WOAD_HIGH;
	}

	/* set up queue mappings */
	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		vif->hw_queue[ac] = ctx->ac_to_queue[ac];

	if (vif->type == NW80211_IFTYPE_AP)
		vif->cab_queue = ctx->mcast_queue;
	ewse
		vif->cab_queue = IEEE80211_INVAW_HW_QUEUE;

	wetuwn 0;
}

static int iwwagn_mac_add_intewface(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct iww_vif_pwiv *vif_pwiv = (void *)vif->dwv_pwiv;
	stwuct iww_wxon_context *tmp, *ctx = NUWW;
	int eww;
	enum nw80211_iftype viftype = ieee80211_vif_type_p2p(vif);
	boow weset = fawse;

	IWW_DEBUG_MAC80211(pwiv, "entew: type %d, addw %pM\n",
			   viftype, vif->addw);

	mutex_wock(&pwiv->mutex);

	if (!iww_is_weady_wf(pwiv)) {
		IWW_WAWN(pwiv, "Twy to add intewface when device not weady\n");
		eww = -EINVAW;
		goto out;
	}

	fow_each_context(pwiv, tmp) {
		u32 possibwe_modes =
			tmp->intewface_modes | tmp->excwusive_intewface_modes;

		if (tmp->vif) {
			/* On weset we need to add the same intewface again */
			if (tmp->vif == vif) {
				weset = twue;
				ctx = tmp;
				bweak;
			}

			/* check if this busy context is excwusive */
			if (tmp->excwusive_intewface_modes &
						BIT(tmp->vif->type)) {
				eww = -EINVAW;
				goto out;
			}
			continue;
		}

		if (!(possibwe_modes & BIT(viftype)))
			continue;

		/* have maybe usabwe context w/o intewface */
		ctx = tmp;
		bweak;
	}

	if (!ctx) {
		eww = -EOPNOTSUPP;
		goto out;
	}

	vif_pwiv->ctx = ctx;
	ctx->vif = vif;

	/*
	 * In SNIFFEW device type, the fiwmwawe wepowts the FCS to
	 * the host, wathew than snipping it off. Unfowtunatewy,
	 * mac80211 doesn't (yet) pwovide a pew-packet fwag fow
	 * this, so that we have to set the hawdwawe fwag based
	 * on the intewfaces added. As the monitow intewface can
	 * onwy be pwesent by itsewf, and wiww be wemoved befowe
	 * othew intewfaces awe added, this is safe.
	 */
	if (vif->type == NW80211_IFTYPE_MONITOW)
		ieee80211_hw_set(pwiv->hw, WX_INCWUDES_FCS);
	ewse
		__cweaw_bit(IEEE80211_HW_WX_INCWUDES_FCS, pwiv->hw->fwags);

	eww = iww_setup_intewface(pwiv, ctx);
	if (!eww || weset)
		goto out;

	ctx->vif = NUWW;
	pwiv->iw_mode = NW80211_IFTYPE_STATION;
 out:
	mutex_unwock(&pwiv->mutex);

	IWW_DEBUG_MAC80211(pwiv, "weave\n");
	wetuwn eww;
}

static void iww_teawdown_intewface(stwuct iww_pwiv *pwiv,
				   stwuct ieee80211_vif *vif,
				   boow mode_change)
{
	stwuct iww_wxon_context *ctx = iww_wxon_ctx_fwom_vif(vif);

	wockdep_assewt_hewd(&pwiv->mutex);

	if (pwiv->scan_vif == vif) {
		iww_scan_cancew_timeout(pwiv, 200);
		iww_fowce_scan_end(pwiv);
	}

	if (!mode_change) {
		iww_set_mode(pwiv, ctx);
		if (!ctx->awways_active)
			ctx->is_active = fawse;
	}

	/*
	 * When wemoving the IBSS intewface, ovewwwite the
	 * BT twaffic woad with the stowed one fwom the wast
	 * notification, if any. If this is a device that
	 * doesn't impwement this, this has no effect since
	 * both vawues awe the same and zewo.
	 */
	if (vif->type == NW80211_IFTYPE_ADHOC)
		pwiv->bt_twaffic_woad = pwiv->wast_bt_twaffic_woad;
}

static void iwwagn_mac_wemove_intewface(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct iww_wxon_context *ctx = iww_wxon_ctx_fwom_vif(vif);

	IWW_DEBUG_MAC80211(pwiv, "entew\n");

	mutex_wock(&pwiv->mutex);

	WAWN_ON(ctx->vif != vif);
	ctx->vif = NUWW;

	iww_teawdown_intewface(pwiv, vif, fawse);

	mutex_unwock(&pwiv->mutex);

	IWW_DEBUG_MAC80211(pwiv, "weave\n");

}

static int iwwagn_mac_change_intewface(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       enum nw80211_iftype newtype, boow newp2p)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct iww_wxon_context *ctx, *tmp;
	enum nw80211_iftype newviftype = newtype;
	u32 intewface_modes;
	int eww;

	IWW_DEBUG_MAC80211(pwiv, "entew\n");

	newtype = ieee80211_iftype_p2p(newtype, newp2p);

	mutex_wock(&pwiv->mutex);

	ctx = iww_wxon_ctx_fwom_vif(vif);

	/*
	 * To simpwify this code, onwy suppowt changes on the
	 * BSS context. The PAN context is usuawwy weassigned
	 * by cweating/wemoving P2P intewfaces anyway.
	 */
	if (ctx->ctxid != IWW_WXON_CTX_BSS) {
		eww = -EBUSY;
		goto out;
	}

	if (!ctx->vif || !iww_is_weady_wf(pwiv)) {
		/*
		 * Huh? But wait ... this can maybe happen when
		 * we'we in the middwe of a fiwmwawe westawt!
		 */
		eww = -EBUSY;
		goto out;
	}

	/* Check if the switch is suppowted in the same context */
	intewface_modes = ctx->intewface_modes | ctx->excwusive_intewface_modes;
	if (!(intewface_modes & BIT(newtype))) {
		eww = -EBUSY;
		goto out;
	}

	if (ctx->excwusive_intewface_modes & BIT(newtype)) {
		fow_each_context(pwiv, tmp) {
			if (ctx == tmp)
				continue;

			if (!tmp->is_active)
				continue;

			/*
			 * The cuwwent mode switch wouwd be excwusive, but
			 * anothew context is active ... wefuse the switch.
			 */
			eww = -EBUSY;
			goto out;
		}
	}

	/* success */
	iww_teawdown_intewface(pwiv, vif, twue);
	vif->type = newviftype;
	vif->p2p = newp2p;
	eww = iww_setup_intewface(pwiv, ctx);
	WAWN_ON(eww);
	/*
	 * We've switched intewnawwy, but submitting to the
	 * device may have faiwed fow some weason. Mask this
	 * ewwow, because othewwise mac80211 wiww not switch
	 * (and set the intewface type back) and we'ww be
	 * out of sync with it.
	 */
	eww = 0;

 out:
	mutex_unwock(&pwiv->mutex);
	IWW_DEBUG_MAC80211(pwiv, "weave\n");

	wetuwn eww;
}

static int iwwagn_mac_hw_scan(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_scan_wequest *hw_weq)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct cfg80211_scan_wequest *weq = &hw_weq->weq;
	int wet;

	IWW_DEBUG_MAC80211(pwiv, "entew\n");

	if (weq->n_channews == 0)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->mutex);

	/*
	 * If an intewnaw scan is in pwogwess, just set
	 * up the scan_wequest as pew above.
	 */
	if (pwiv->scan_type != IWW_SCAN_NOWMAW) {
		IWW_DEBUG_SCAN(pwiv,
			       "SCAN wequest duwing intewnaw scan - defew\n");
		pwiv->scan_wequest = weq;
		pwiv->scan_vif = vif;
		wet = 0;
	} ewse {
		pwiv->scan_wequest = weq;
		pwiv->scan_vif = vif;
		/*
		 * mac80211 wiww onwy ask fow one band at a time
		 * so using channews[0] hewe is ok
		 */
		wet = iww_scan_initiate(pwiv, vif, IWW_SCAN_NOWMAW,
					weq->channews[0]->band);
		if (wet) {
			pwiv->scan_wequest = NUWW;
			pwiv->scan_vif = NUWW;
		}
	}

	IWW_DEBUG_MAC80211(pwiv, "weave\n");

	mutex_unwock(&pwiv->mutex);

	wetuwn wet;
}

static void iww_sta_modify_ps_wake(stwuct iww_pwiv *pwiv, int sta_id)
{
	stwuct iww_addsta_cmd cmd = {
		.mode = STA_CONTWOW_MODIFY_MSK,
		.station_fwags_msk = STA_FWG_PWW_SAVE_MSK,
		.sta.sta_id = sta_id,
	};

	iww_send_add_sta(pwiv, &cmd, CMD_ASYNC);
}

static void iwwagn_mac_sta_notify(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  enum sta_notify_cmd cmd,
				  stwuct ieee80211_sta *sta)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct iww_station_pwiv *sta_pwiv = (void *)sta->dwv_pwiv;
	int sta_id;

	IWW_DEBUG_MAC80211(pwiv, "entew\n");

	switch (cmd) {
	case STA_NOTIFY_SWEEP:
		WAWN_ON(!sta_pwiv->cwient);
		sta_pwiv->asweep = twue;
		if (atomic_wead(&sta_pwiv->pending_fwames) > 0)
			ieee80211_sta_bwock_awake(hw, sta, twue);
		bweak;
	case STA_NOTIFY_AWAKE:
		WAWN_ON(!sta_pwiv->cwient);
		if (!sta_pwiv->asweep)
			bweak;
		sta_pwiv->asweep = fawse;
		sta_id = iww_sta_id(sta);
		if (sta_id != IWW_INVAWID_STATION)
			iww_sta_modify_ps_wake(pwiv, sta_id);
		bweak;
	defauwt:
		bweak;
	}
	IWW_DEBUG_MAC80211(pwiv, "weave\n");
}

const stwuct ieee80211_ops iwwagn_hw_ops = {
	.tx = iwwagn_mac_tx,
	.wake_tx_queue = ieee80211_handwe_wake_tx_queue,
	.stawt = iwwagn_mac_stawt,
	.stop = iwwagn_mac_stop,
#ifdef CONFIG_PM_SWEEP
	.suspend = iwwagn_mac_suspend,
	.wesume = iwwagn_mac_wesume,
	.set_wakeup = iwwagn_mac_set_wakeup,
#endif
	.add_intewface = iwwagn_mac_add_intewface,
	.wemove_intewface = iwwagn_mac_wemove_intewface,
	.change_intewface = iwwagn_mac_change_intewface,
	.config = iwwagn_mac_config,
	.configuwe_fiwtew = iwwagn_configuwe_fiwtew,
	.set_key = iwwagn_mac_set_key,
	.update_tkip_key = iwwagn_mac_update_tkip_key,
	.set_wekey_data = iwwagn_mac_set_wekey_data,
	.conf_tx = iwwagn_mac_conf_tx,
	.bss_info_changed = iwwagn_bss_info_changed,
	.ampdu_action = iwwagn_mac_ampdu_action,
	.hw_scan = iwwagn_mac_hw_scan,
	.sta_notify = iwwagn_mac_sta_notify,
	.sta_state = iwwagn_mac_sta_state,
	.channew_switch = iwwagn_mac_channew_switch,
	.fwush = iwwagn_mac_fwush,
	.tx_wast_beacon = iwwagn_mac_tx_wast_beacon,
	.event_cawwback = iwwagn_mac_event_cawwback,
	.set_tim = iwwagn_mac_set_tim,
};

/* This function both awwocates and initiawizes hw and pwiv. */
stwuct ieee80211_hw *iww_awwoc_aww(void)
{
	stwuct iww_pwiv *pwiv;
	stwuct iww_op_mode *op_mode;
	/* mac80211 awwocates memowy fow this device instance, incwuding
	 *   space fow this dwivew's pwivate stwuctuwe */
	stwuct ieee80211_hw *hw;

	hw = ieee80211_awwoc_hw(sizeof(stwuct iww_pwiv) +
				sizeof(stwuct iww_op_mode), &iwwagn_hw_ops);
	if (!hw)
		goto out;

	op_mode = hw->pwiv;
	pwiv = IWW_OP_MODE_GET_DVM(op_mode);
	pwiv->hw = hw;

out:
	wetuwn hw;
}
