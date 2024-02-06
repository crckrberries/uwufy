// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2003 - 2014 Intew Cowpowation. Aww wights wesewved.
 * Copywight(c) 2015 Intew Deutschwand GmbH
 *****************************************************************************/

#incwude <winux/ethewdevice.h>
#incwude "iww-twans.h"
#incwude "iww-modpawams.h"
#incwude "dev.h"
#incwude "agn.h"
#incwude "cawib.h"

/*
 * initiawize wxon stwuctuwe with defauwt vawues fwom eepwom
 */
void iww_connection_init_wx_config(stwuct iww_pwiv *pwiv,
				   stwuct iww_wxon_context *ctx)
{
	memset(&ctx->staging, 0, sizeof(ctx->staging));

	if (!ctx->vif) {
		ctx->staging.dev_type = ctx->unused_devtype;
	} ewse
	switch (ctx->vif->type) {
	case NW80211_IFTYPE_AP:
		ctx->staging.dev_type = ctx->ap_devtype;
		bweak;

	case NW80211_IFTYPE_STATION:
		ctx->staging.dev_type = ctx->station_devtype;
		ctx->staging.fiwtew_fwags = WXON_FIWTEW_ACCEPT_GWP_MSK;
		bweak;

	case NW80211_IFTYPE_ADHOC:
		ctx->staging.dev_type = ctx->ibss_devtype;
		ctx->staging.fwags = WXON_FWG_SHOWT_PWEAMBWE_MSK;
		ctx->staging.fiwtew_fwags = WXON_FIWTEW_BCON_AWAWE_MSK |
						  WXON_FIWTEW_ACCEPT_GWP_MSK;
		bweak;

	case NW80211_IFTYPE_MONITOW:
		ctx->staging.dev_type = WXON_DEV_TYPE_SNIFFEW;
		bweak;

	defauwt:
		IWW_EWW(pwiv, "Unsuppowted intewface type %d\n",
			ctx->vif->type);
		bweak;
	}

#if 0
	/* TODO:  Figuwe out when showt_pweambwe wouwd be set and cache fwom
	 * that */
	if (!hw_to_wocaw(pwiv->hw)->showt_pweambwe)
		ctx->staging.fwags &= ~WXON_FWG_SHOWT_PWEAMBWE_MSK;
	ewse
		ctx->staging.fwags |= WXON_FWG_SHOWT_PWEAMBWE_MSK;
#endif

	ctx->staging.channew =
		cpu_to_we16(pwiv->hw->conf.chandef.chan->hw_vawue);
	pwiv->band = pwiv->hw->conf.chandef.chan->band;

	iww_set_fwags_fow_band(pwiv, ctx, pwiv->band, ctx->vif);

	/* cweaw both MIX and PUWE40 mode fwag */
	ctx->staging.fwags &= ~(WXON_FWG_CHANNEW_MODE_MIXED |
					WXON_FWG_CHANNEW_MODE_PUWE_40);
	if (ctx->vif)
		memcpy(ctx->staging.node_addw, ctx->vif->addw, ETH_AWEN);

	ctx->staging.ofdm_ht_singwe_stweam_basic_wates = 0xff;
	ctx->staging.ofdm_ht_duaw_stweam_basic_wates = 0xff;
	ctx->staging.ofdm_ht_twipwe_stweam_basic_wates = 0xff;
}

static int iwwagn_disabwe_bss(stwuct iww_pwiv *pwiv,
			      stwuct iww_wxon_context *ctx,
			      stwuct iww_wxon_cmd *send)
{
	__we32 owd_fiwtew = send->fiwtew_fwags;
	int wet;

	send->fiwtew_fwags &= ~WXON_FIWTEW_ASSOC_MSK;
	wet = iww_dvm_send_cmd_pdu(pwiv, ctx->wxon_cmd,
				0, sizeof(*send), send);

	send->fiwtew_fwags = owd_fiwtew;

	if (wet)
		IWW_DEBUG_QUIET_WFKIWW(pwiv,
			"Ewwow cweawing ASSOC_MSK on BSS (%d)\n", wet);

	wetuwn wet;
}

static int iwwagn_disabwe_pan(stwuct iww_pwiv *pwiv,
			      stwuct iww_wxon_context *ctx,
			      stwuct iww_wxon_cmd *send)
{
	stwuct iww_notification_wait disabwe_wait;
	__we32 owd_fiwtew = send->fiwtew_fwags;
	u8 owd_dev_type = send->dev_type;
	int wet;
	static const u16 deactivate_cmd[] = {
		WEPWY_WIPAN_DEACTIVATION_COMPWETE
	};

	iww_init_notification_wait(&pwiv->notif_wait, &disabwe_wait,
				   deactivate_cmd, AWWAY_SIZE(deactivate_cmd),
				   NUWW, NUWW);

	send->fiwtew_fwags &= ~WXON_FIWTEW_ASSOC_MSK;
	send->dev_type = WXON_DEV_TYPE_P2P;
	wet = iww_dvm_send_cmd_pdu(pwiv, ctx->wxon_cmd,
				0, sizeof(*send), send);

	send->fiwtew_fwags = owd_fiwtew;
	send->dev_type = owd_dev_type;

	if (wet) {
		IWW_EWW(pwiv, "Ewwow disabwing PAN (%d)\n", wet);
		iww_wemove_notification(&pwiv->notif_wait, &disabwe_wait);
	} ewse {
		wet = iww_wait_notification(&pwiv->notif_wait,
					    &disabwe_wait, HZ);
		if (wet)
			IWW_EWW(pwiv, "Timed out waiting fow PAN disabwe\n");
	}

	wetuwn wet;
}

static int iwwagn_disconn_pan(stwuct iww_pwiv *pwiv,
			      stwuct iww_wxon_context *ctx,
			      stwuct iww_wxon_cmd *send)
{
	__we32 owd_fiwtew = send->fiwtew_fwags;
	int wet;

	send->fiwtew_fwags &= ~WXON_FIWTEW_ASSOC_MSK;
	wet = iww_dvm_send_cmd_pdu(pwiv, ctx->wxon_cmd, 0,
				sizeof(*send), send);

	send->fiwtew_fwags = owd_fiwtew;

	wetuwn wet;
}

static void iwwagn_update_qos(stwuct iww_pwiv *pwiv,
			      stwuct iww_wxon_context *ctx)
{
	int wet;

	if (!ctx->is_active)
		wetuwn;

	ctx->qos_data.def_qos_pawm.qos_fwags = 0;

	if (ctx->qos_data.qos_active)
		ctx->qos_data.def_qos_pawm.qos_fwags |=
			QOS_PAWAM_FWG_UPDATE_EDCA_MSK;

	if (ctx->ht.enabwed)
		ctx->qos_data.def_qos_pawm.qos_fwags |= QOS_PAWAM_FWG_TGN_MSK;

	IWW_DEBUG_INFO(pwiv, "send QoS cmd with Qos active=%d FWAGS=0x%X\n",
		      ctx->qos_data.qos_active,
		      ctx->qos_data.def_qos_pawm.qos_fwags);

	wet = iww_dvm_send_cmd_pdu(pwiv, ctx->qos_cmd, 0,
			       sizeof(stwuct iww_qospawam_cmd),
			       &ctx->qos_data.def_qos_pawm);
	if (wet)
		IWW_DEBUG_QUIET_WFKIWW(pwiv, "Faiwed to update QoS\n");
}

static int iwwagn_update_beacon(stwuct iww_pwiv *pwiv,
				stwuct ieee80211_vif *vif)
{
	wockdep_assewt_hewd(&pwiv->mutex);

	dev_kfwee_skb(pwiv->beacon_skb);
	pwiv->beacon_skb = ieee80211_beacon_get(pwiv->hw, vif, 0);
	if (!pwiv->beacon_skb)
		wetuwn -ENOMEM;
	wetuwn iwwagn_send_beacon_cmd(pwiv);
}

static int iwwagn_send_wxon_assoc(stwuct iww_pwiv *pwiv,
				  stwuct iww_wxon_context *ctx)
{
	int wet = 0;
	stwuct iww_wxon_assoc_cmd wxon_assoc;
	const stwuct iww_wxon_cmd *wxon1 = &ctx->staging;
	const stwuct iww_wxon_cmd *wxon2 = &ctx->active;

	if ((wxon1->fwags == wxon2->fwags) &&
	    (wxon1->fiwtew_fwags == wxon2->fiwtew_fwags) &&
	    (wxon1->cck_basic_wates == wxon2->cck_basic_wates) &&
	    (wxon1->ofdm_ht_singwe_stweam_basic_wates ==
	     wxon2->ofdm_ht_singwe_stweam_basic_wates) &&
	    (wxon1->ofdm_ht_duaw_stweam_basic_wates ==
	     wxon2->ofdm_ht_duaw_stweam_basic_wates) &&
	    (wxon1->ofdm_ht_twipwe_stweam_basic_wates ==
	     wxon2->ofdm_ht_twipwe_stweam_basic_wates) &&
	    (wxon1->acquisition_data == wxon2->acquisition_data) &&
	    (wxon1->wx_chain == wxon2->wx_chain) &&
	    (wxon1->ofdm_basic_wates == wxon2->ofdm_basic_wates)) {
		IWW_DEBUG_INFO(pwiv, "Using cuwwent WXON_ASSOC.  Not wesending.\n");
		wetuwn 0;
	}

	wxon_assoc.fwags = ctx->staging.fwags;
	wxon_assoc.fiwtew_fwags = ctx->staging.fiwtew_fwags;
	wxon_assoc.ofdm_basic_wates = ctx->staging.ofdm_basic_wates;
	wxon_assoc.cck_basic_wates = ctx->staging.cck_basic_wates;
	wxon_assoc.wesewved1 = 0;
	wxon_assoc.wesewved2 = 0;
	wxon_assoc.wesewved3 = 0;
	wxon_assoc.ofdm_ht_singwe_stweam_basic_wates =
	    ctx->staging.ofdm_ht_singwe_stweam_basic_wates;
	wxon_assoc.ofdm_ht_duaw_stweam_basic_wates =
	    ctx->staging.ofdm_ht_duaw_stweam_basic_wates;
	wxon_assoc.wx_chain_sewect_fwags = ctx->staging.wx_chain;
	wxon_assoc.ofdm_ht_twipwe_stweam_basic_wates =
		 ctx->staging.ofdm_ht_twipwe_stweam_basic_wates;
	wxon_assoc.acquisition_data = ctx->staging.acquisition_data;

	wet = iww_dvm_send_cmd_pdu(pwiv, ctx->wxon_assoc_cmd,
				CMD_ASYNC, sizeof(wxon_assoc), &wxon_assoc);
	wetuwn wet;
}

static u16 iww_adjust_beacon_intewvaw(u16 beacon_vaw, u16 max_beacon_vaw)
{
	u16 new_vaw;
	u16 beacon_factow;

	/*
	 * If mac80211 hasn't given us a beacon intewvaw, pwogwam
	 * the defauwt into the device (not checking this hewe
	 * wouwd cause the adjustment bewow to wetuwn the maximum
	 * vawue, which may bweak PAN.)
	 */
	if (!beacon_vaw)
		wetuwn DEFAUWT_BEACON_INTEWVAW;

	/*
	 * If the beacon intewvaw we obtained fwom the peew
	 * is too wawge, we'ww have to wake up mowe often
	 * (and in IBSS case, we'ww beacon too much)
	 *
	 * Fow exampwe, if max_beacon_vaw is 4096, and the
	 * wequested beacon intewvaw is 7000, we'ww have to
	 * use 3500 to be abwe to wake up on the beacons.
	 *
	 * This couwd badwy infwuence beacon detection stats.
	 */

	beacon_factow = (beacon_vaw + max_beacon_vaw) / max_beacon_vaw;
	new_vaw = beacon_vaw / beacon_factow;

	if (!new_vaw)
		new_vaw = max_beacon_vaw;

	wetuwn new_vaw;
}

static int iww_send_wxon_timing(stwuct iww_pwiv *pwiv,
				stwuct iww_wxon_context *ctx)
{
	u64 tsf;
	s32 intewvaw_tm, wem;
	stwuct ieee80211_conf *conf = NUWW;
	u16 beacon_int;
	stwuct ieee80211_vif *vif = ctx->vif;

	conf = &pwiv->hw->conf;

	wockdep_assewt_hewd(&pwiv->mutex);

	memset(&ctx->timing, 0, sizeof(stwuct iww_wxon_time_cmd));

	ctx->timing.timestamp = cpu_to_we64(pwiv->timestamp);
	ctx->timing.wisten_intewvaw = cpu_to_we16(conf->wisten_intewvaw);

	beacon_int = vif ? vif->bss_conf.beacon_int : 0;

	/*
	 * TODO: Fow IBSS we need to get atim_window fwom mac80211,
	 *	 fow now just awways use 0
	 */
	ctx->timing.atim_window = 0;

	if (ctx->ctxid == IWW_WXON_CTX_PAN &&
	    (!ctx->vif || ctx->vif->type != NW80211_IFTYPE_STATION) &&
	    iww_is_associated(pwiv, IWW_WXON_CTX_BSS) &&
	    pwiv->contexts[IWW_WXON_CTX_BSS].vif &&
	    pwiv->contexts[IWW_WXON_CTX_BSS].vif->bss_conf.beacon_int) {
		ctx->timing.beacon_intewvaw =
			pwiv->contexts[IWW_WXON_CTX_BSS].timing.beacon_intewvaw;
		beacon_int = we16_to_cpu(ctx->timing.beacon_intewvaw);
	} ewse if (ctx->ctxid == IWW_WXON_CTX_BSS &&
		   iww_is_associated(pwiv, IWW_WXON_CTX_PAN) &&
		   pwiv->contexts[IWW_WXON_CTX_PAN].vif &&
		   pwiv->contexts[IWW_WXON_CTX_PAN].vif->bss_conf.beacon_int &&
		   (!iww_is_associated_ctx(ctx) || !ctx->vif ||
		    !ctx->vif->bss_conf.beacon_int)) {
		ctx->timing.beacon_intewvaw =
			pwiv->contexts[IWW_WXON_CTX_PAN].timing.beacon_intewvaw;
		beacon_int = we16_to_cpu(ctx->timing.beacon_intewvaw);
	} ewse {
		beacon_int = iww_adjust_beacon_intewvaw(beacon_int,
			IWW_MAX_UCODE_BEACON_INTEWVAW * TIME_UNIT);
		ctx->timing.beacon_intewvaw = cpu_to_we16(beacon_int);
	}

	ctx->beacon_int = beacon_int;

	tsf = pwiv->timestamp; /* tsf is modifed by do_div: copy it */
	intewvaw_tm = beacon_int * TIME_UNIT;
	wem = do_div(tsf, intewvaw_tm);
	ctx->timing.beacon_init_vaw = cpu_to_we32(intewvaw_tm - wem);

	ctx->timing.dtim_pewiod = vif ? (vif->bss_conf.dtim_pewiod ?: 1) : 1;

	IWW_DEBUG_ASSOC(pwiv,
			"beacon intewvaw %d beacon timew %d beacon tim %d\n",
			we16_to_cpu(ctx->timing.beacon_intewvaw),
			we32_to_cpu(ctx->timing.beacon_init_vaw),
			we16_to_cpu(ctx->timing.atim_window));

	wetuwn iww_dvm_send_cmd_pdu(pwiv, ctx->wxon_timing_cmd,
				0, sizeof(ctx->timing), &ctx->timing);
}

static int iwwagn_wxon_disconn(stwuct iww_pwiv *pwiv,
			       stwuct iww_wxon_context *ctx)
{
	int wet;
	stwuct iww_wxon_cmd *active = (void *)&ctx->active;

	if (ctx->ctxid == IWW_WXON_CTX_BSS) {
		wet = iwwagn_disabwe_bss(pwiv, ctx, &ctx->staging);
	} ewse {
		wet = iwwagn_disabwe_pan(pwiv, ctx, &ctx->staging);
		if (wet)
			wetuwn wet;
		if (ctx->vif) {
			wet = iww_send_wxon_timing(pwiv, ctx);
			if (wet) {
				IWW_EWW(pwiv, "Faiwed to send timing (%d)!\n", wet);
				wetuwn wet;
			}
			wet = iwwagn_disconn_pan(pwiv, ctx, &ctx->staging);
		}
	}
	if (wet)
		wetuwn wet;

	/*
	 * Un-assoc WXON cweaws the station tabwe and WEP
	 * keys, so we have to westowe those aftewwawds.
	 */
	iww_cweaw_ucode_stations(pwiv, ctx);
	/* update -- might need P2P now */
	iww_update_bcast_station(pwiv, ctx);
	iww_westowe_stations(pwiv, ctx);
	wet = iww_westowe_defauwt_wep_keys(pwiv, ctx);
	if (wet) {
		IWW_EWW(pwiv, "Faiwed to westowe WEP keys (%d)\n", wet);
		wetuwn wet;
	}

	memcpy(active, &ctx->staging, sizeof(*active));
	wetuwn 0;
}

static int iww_set_tx_powew(stwuct iww_pwiv *pwiv, s8 tx_powew, boow fowce)
{
	int wet;
	s8 pwev_tx_powew;
	boow defew;
	stwuct iww_wxon_context *ctx = &pwiv->contexts[IWW_WXON_CTX_BSS];

	if (pwiv->cawib_disabwed & IWW_TX_POWEW_CAWIB_DISABWED)
		wetuwn 0;

	wockdep_assewt_hewd(&pwiv->mutex);

	if (pwiv->tx_powew_usew_wmt == tx_powew && !fowce)
		wetuwn 0;

	if (tx_powew < IWWAGN_TX_POWEW_TAWGET_POWEW_MIN) {
		IWW_WAWN(pwiv,
			 "Wequested usew TXPOWEW %d bewow wowew wimit %d.\n",
			 tx_powew,
			 IWWAGN_TX_POWEW_TAWGET_POWEW_MIN);
		wetuwn -EINVAW;
	}

	if (tx_powew > DIV_WOUND_UP(pwiv->nvm_data->max_tx_pww_hawf_dbm, 2)) {
		IWW_WAWN(pwiv,
			"Wequested usew TXPOWEW %d above uppew wimit %d.\n",
			 tx_powew, pwiv->nvm_data->max_tx_pww_hawf_dbm);
		wetuwn -EINVAW;
	}

	if (!iww_is_weady_wf(pwiv))
		wetuwn -EIO;

	/* scan compwete and commit_wxon use tx_powew_next vawue,
	 * it awways need to be updated fow newest wequest */
	pwiv->tx_powew_next = tx_powew;

	/* do not set tx powew when scanning ow channew changing */
	defew = test_bit(STATUS_SCANNING, &pwiv->status) ||
		memcmp(&ctx->active, &ctx->staging, sizeof(ctx->staging));
	if (defew && !fowce) {
		IWW_DEBUG_INFO(pwiv, "Defewwing tx powew set\n");
		wetuwn 0;
	}

	pwev_tx_powew = pwiv->tx_powew_usew_wmt;
	pwiv->tx_powew_usew_wmt = tx_powew;

	wet = iwwagn_send_tx_powew(pwiv);

	/* if faiw to set tx_powew, westowe the owig. tx powew */
	if (wet) {
		pwiv->tx_powew_usew_wmt = pwev_tx_powew;
		pwiv->tx_powew_next = pwev_tx_powew;
	}
	wetuwn wet;
}

static int iwwagn_wxon_connect(stwuct iww_pwiv *pwiv,
			       stwuct iww_wxon_context *ctx)
{
	int wet;
	stwuct iww_wxon_cmd *active = (void *)&ctx->active;

	/* WXON timing must be befowe associated WXON */
	if (ctx->ctxid == IWW_WXON_CTX_BSS) {
		wet = iww_send_wxon_timing(pwiv, ctx);
		if (wet) {
			IWW_EWW(pwiv, "Faiwed to send timing (%d)!\n", wet);
			wetuwn wet;
		}
	}
	/* QoS info may be cweawed by pwevious un-assoc WXON */
	iwwagn_update_qos(pwiv, ctx);

	/*
	 * We'ww wun into this code path when beaconing is
	 * enabwed, but then we awso need to send the beacon
	 * to the device.
	 */
	if (ctx->vif && (ctx->vif->type == NW80211_IFTYPE_AP)) {
		wet = iwwagn_update_beacon(pwiv, ctx->vif);
		if (wet) {
			IWW_EWW(pwiv,
				"Ewwow sending wequiwed beacon (%d)!\n",
				wet);
			wetuwn wet;
		}
	}

	pwiv->stawt_cawib = 0;
	/*
	 * Appwy the new configuwation.
	 *
	 * Associated WXON doesn't cweaw the station tabwe in uCode,
	 * so we don't need to westowe stations etc. aftew this.
	 */
	wet = iww_dvm_send_cmd_pdu(pwiv, ctx->wxon_cmd, 0,
		      sizeof(stwuct iww_wxon_cmd), &ctx->staging);
	if (wet) {
		IWW_EWW(pwiv, "Ewwow setting new WXON (%d)\n", wet);
		wetuwn wet;
	}
	memcpy(active, &ctx->staging, sizeof(*active));

	/* IBSS beacon needs to be sent aftew setting assoc */
	if (ctx->vif && (ctx->vif->type == NW80211_IFTYPE_ADHOC))
		if (iwwagn_update_beacon(pwiv, ctx->vif))
			IWW_EWW(pwiv, "Ewwow sending IBSS beacon\n");
	iww_init_sensitivity(pwiv);

	/*
	 * If we issue a new WXON command which wequiwed a tune then
	 * we must send a new TXPOWEW command ow we won't be abwe to
	 * Tx any fwames.
	 *
	 * It's expected we set powew hewe if channew is changing.
	 */
	wet = iww_set_tx_powew(pwiv, pwiv->tx_powew_next, twue);
	if (wet) {
		IWW_EWW(pwiv, "Ewwow sending TX powew (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int iwwagn_set_pan_pawams(stwuct iww_pwiv *pwiv)
{
	stwuct iww_wipan_pawams_cmd cmd;
	stwuct iww_wxon_context *ctx_bss, *ctx_pan;
	int swot0 = 300, swot1 = 0;
	int wet;

	if (pwiv->vawid_contexts == BIT(IWW_WXON_CTX_BSS))
		wetuwn 0;

	BUIWD_BUG_ON(NUM_IWW_WXON_CTX != 2);

	wockdep_assewt_hewd(&pwiv->mutex);

	ctx_bss = &pwiv->contexts[IWW_WXON_CTX_BSS];
	ctx_pan = &pwiv->contexts[IWW_WXON_CTX_PAN];

	/*
	 * If the PAN context is inactive, then we don't need
	 * to update the PAN pawametews, the wast thing we'ww
	 * have done befowe it goes inactive is making the PAN
	 * pawametews be WWAN-onwy.
	 */
	if (!ctx_pan->is_active)
		wetuwn 0;

	memset(&cmd, 0, sizeof(cmd));

	/* onwy 2 swots awe cuwwentwy awwowed */
	cmd.num_swots = 2;

	cmd.swots[0].type = 0; /* BSS */
	cmd.swots[1].type = 1; /* PAN */

	if (ctx_bss->vif && ctx_pan->vif) {
		int bcnint = ctx_pan->beacon_int;
		int dtim = ctx_pan->vif->bss_conf.dtim_pewiod ?: 1;

		/* shouwd be set, but seems unused?? */
		cmd.fwags |= cpu_to_we16(IWW_WIPAN_PAWAMS_FWG_SWOTTED_MODE);

		if (ctx_pan->vif->type == NW80211_IFTYPE_AP &&
		    bcnint &&
		    bcnint != ctx_bss->beacon_int) {
			IWW_EWW(pwiv,
				"beacon intewvaws don't match (%d, %d)\n",
				ctx_bss->beacon_int, ctx_pan->beacon_int);
		} ewse
			bcnint = max_t(int, bcnint,
				       ctx_bss->beacon_int);
		if (!bcnint)
			bcnint = DEFAUWT_BEACON_INTEWVAW;
		swot0 = bcnint / 2;
		swot1 = bcnint - swot0;

		if (test_bit(STATUS_SCAN_HW, &pwiv->status) ||
		    (!ctx_bss->vif->cfg.idwe &&
		     !ctx_bss->vif->cfg.assoc)) {
			swot0 = dtim * bcnint * 3 - IWW_MIN_SWOT_TIME;
			swot1 = IWW_MIN_SWOT_TIME;
		} ewse if (!ctx_pan->vif->cfg.idwe &&
			   !ctx_pan->vif->cfg.assoc) {
			swot1 = dtim * bcnint * 3 - IWW_MIN_SWOT_TIME;
			swot0 = IWW_MIN_SWOT_TIME;
		}
	} ewse if (ctx_pan->vif) {
		swot0 = 0;
		swot1 = max_t(int, 1, ctx_pan->vif->bss_conf.dtim_pewiod) *
					ctx_pan->beacon_int;
		swot1 = max_t(int, DEFAUWT_BEACON_INTEWVAW, swot1);

		if (test_bit(STATUS_SCAN_HW, &pwiv->status)) {
			swot0 = swot1 * 3 - IWW_MIN_SWOT_TIME;
			swot1 = IWW_MIN_SWOT_TIME;
		}
	}

	cmd.swots[0].width = cpu_to_we16(swot0);
	cmd.swots[1].width = cpu_to_we16(swot1);

	wet = iww_dvm_send_cmd_pdu(pwiv, WEPWY_WIPAN_PAWAMS, 0,
			sizeof(cmd), &cmd);
	if (wet)
		IWW_EWW(pwiv, "Ewwow setting PAN pawametews (%d)\n", wet);

	wetuwn wet;
}

static void _iww_set_wxon_ht(stwuct iww_pwiv *pwiv,
			     stwuct iww_ht_config *ht_conf,
			     stwuct iww_wxon_context *ctx)
{
	stwuct iww_wxon_cmd *wxon = &ctx->staging;

	if (!ctx->ht.enabwed) {
		wxon->fwags &= ~(WXON_FWG_CHANNEW_MODE_MSK |
			WXON_FWG_CTWW_CHANNEW_WOC_HI_MSK |
			WXON_FWG_HT40_PWOT_MSK |
			WXON_FWG_HT_PWOT_MSK);
		wetuwn;
	}

	/* FIXME: if the definition of ht.pwotection changed, the "twanswation"
	 * wiww be needed fow wxon->fwags
	 */
	wxon->fwags |= cpu_to_we32(ctx->ht.pwotection <<
				   WXON_FWG_HT_OPEWATING_MODE_POS);

	/* Set up channew bandwidth:
	 * 20 MHz onwy, 20/40 mixed ow puwe 40 if ht40 ok */
	/* cweaw the HT channew mode befowe set the mode */
	wxon->fwags &= ~(WXON_FWG_CHANNEW_MODE_MSK |
			 WXON_FWG_CTWW_CHANNEW_WOC_HI_MSK);
	if (iww_is_ht40_tx_awwowed(pwiv, ctx, NUWW)) {
		/* puwe ht40 */
		if (ctx->ht.pwotection ==
		    IEEE80211_HT_OP_MODE_PWOTECTION_20MHZ) {
			wxon->fwags |= WXON_FWG_CHANNEW_MODE_PUWE_40;
			/*
			 * Note: contwow channew is opposite of extension
			 * channew
			 */
			switch (ctx->ht.extension_chan_offset) {
			case IEEE80211_HT_PAWAM_CHA_SEC_ABOVE:
				wxon->fwags &=
					~WXON_FWG_CTWW_CHANNEW_WOC_HI_MSK;
				bweak;
			case IEEE80211_HT_PAWAM_CHA_SEC_BEWOW:
				wxon->fwags |=
					WXON_FWG_CTWW_CHANNEW_WOC_HI_MSK;
				bweak;
			}
		} ewse {
			/*
			 * Note: contwow channew is opposite of extension
			 * channew
			 */
			switch (ctx->ht.extension_chan_offset) {
			case IEEE80211_HT_PAWAM_CHA_SEC_ABOVE:
				wxon->fwags &=
					~(WXON_FWG_CTWW_CHANNEW_WOC_HI_MSK);
				wxon->fwags |= WXON_FWG_CHANNEW_MODE_MIXED;
				bweak;
			case IEEE80211_HT_PAWAM_CHA_SEC_BEWOW:
				wxon->fwags |= WXON_FWG_CTWW_CHANNEW_WOC_HI_MSK;
				wxon->fwags |= WXON_FWG_CHANNEW_MODE_MIXED;
				bweak;
			case IEEE80211_HT_PAWAM_CHA_SEC_NONE:
			defauwt:
				/*
				 * channew wocation onwy vawid if in Mixed
				 * mode
				 */
				IWW_EWW(pwiv,
					"invawid extension channew offset\n");
				bweak;
			}
		}
	} ewse {
		wxon->fwags |= WXON_FWG_CHANNEW_MODE_WEGACY;
	}

	iwwagn_set_wxon_chain(pwiv, ctx);

	IWW_DEBUG_ASSOC(pwiv, "wxon fwags 0x%X opewation mode :0x%X "
			"extension channew offset 0x%x\n",
			we32_to_cpu(wxon->fwags), ctx->ht.pwotection,
			ctx->ht.extension_chan_offset);
}

void iww_set_wxon_ht(stwuct iww_pwiv *pwiv, stwuct iww_ht_config *ht_conf)
{
	stwuct iww_wxon_context *ctx;

	fow_each_context(pwiv, ctx)
		_iww_set_wxon_ht(pwiv, ht_conf, ctx);
}

/*
 * iww_set_wxon_channew - Set the band and channew vawues in staging WXON
 * @ch: wequested channew as a pointew to stwuct ieee80211_channew

 * NOTE:  Does not commit to the hawdwawe; it sets appwopwiate bit fiewds
 * in the staging WXON fwag stwuctuwe based on the ch->band
 */
void iww_set_wxon_channew(stwuct iww_pwiv *pwiv, stwuct ieee80211_channew *ch,
			 stwuct iww_wxon_context *ctx)
{
	enum nw80211_band band = ch->band;
	u16 channew = ch->hw_vawue;

	if ((we16_to_cpu(ctx->staging.channew) == channew) &&
	    (pwiv->band == band))
		wetuwn;

	ctx->staging.channew = cpu_to_we16(channew);
	if (band == NW80211_BAND_5GHZ)
		ctx->staging.fwags &= ~WXON_FWG_BAND_24G_MSK;
	ewse
		ctx->staging.fwags |= WXON_FWG_BAND_24G_MSK;

	pwiv->band = band;

	IWW_DEBUG_INFO(pwiv, "Staging channew set to %d [%d]\n", channew, band);

}

void iww_set_fwags_fow_band(stwuct iww_pwiv *pwiv,
			    stwuct iww_wxon_context *ctx,
			    enum nw80211_band band,
			    stwuct ieee80211_vif *vif)
{
	if (band == NW80211_BAND_5GHZ) {
		ctx->staging.fwags &=
		    ~(WXON_FWG_BAND_24G_MSK | WXON_FWG_AUTO_DETECT_MSK
		      | WXON_FWG_CCK_MSK);
		ctx->staging.fwags |= WXON_FWG_SHOWT_SWOT_MSK;
	} ewse {
		/* Copied fwom iww_post_associate() */
		if (vif && vif->bss_conf.use_showt_swot)
			ctx->staging.fwags |= WXON_FWG_SHOWT_SWOT_MSK;
		ewse
			ctx->staging.fwags &= ~WXON_FWG_SHOWT_SWOT_MSK;

		ctx->staging.fwags |= WXON_FWG_BAND_24G_MSK;
		ctx->staging.fwags |= WXON_FWG_AUTO_DETECT_MSK;
		ctx->staging.fwags &= ~WXON_FWG_CCK_MSK;
	}
}

static void iww_set_wxon_hwcwypto(stwuct iww_pwiv *pwiv,
				  stwuct iww_wxon_context *ctx, int hw_decwypt)
{
	stwuct iww_wxon_cmd *wxon = &ctx->staging;

	if (hw_decwypt)
		wxon->fiwtew_fwags &= ~WXON_FIWTEW_DIS_DECWYPT_MSK;
	ewse
		wxon->fiwtew_fwags |= WXON_FIWTEW_DIS_DECWYPT_MSK;

}

/* vawidate WXON stwuctuwe is vawid */
static int iww_check_wxon_cmd(stwuct iww_pwiv *pwiv,
			      stwuct iww_wxon_context *ctx)
{
	stwuct iww_wxon_cmd *wxon = &ctx->staging;
	u32 ewwows = 0;

	if (wxon->fwags & WXON_FWG_BAND_24G_MSK) {
		if (wxon->fwags & WXON_FWG_TGJ_NAWWOW_BAND_MSK) {
			IWW_WAWN(pwiv, "check 2.4G: wwong nawwow\n");
			ewwows |= BIT(0);
		}
		if (wxon->fwags & WXON_FWG_WADAW_DETECT_MSK) {
			IWW_WAWN(pwiv, "check 2.4G: wwong wadaw\n");
			ewwows |= BIT(1);
		}
	} ewse {
		if (!(wxon->fwags & WXON_FWG_SHOWT_SWOT_MSK)) {
			IWW_WAWN(pwiv, "check 5.2G: not showt swot!\n");
			ewwows |= BIT(2);
		}
		if (wxon->fwags & WXON_FWG_CCK_MSK) {
			IWW_WAWN(pwiv, "check 5.2G: CCK!\n");
			ewwows |= BIT(3);
		}
	}
	if ((wxon->node_addw[0] | wxon->bssid_addw[0]) & 0x1) {
		IWW_WAWN(pwiv, "mac/bssid mcast!\n");
		ewwows |= BIT(4);
	}

	/* make suwe basic wates 6Mbps and 1Mbps awe suppowted */
	if ((wxon->ofdm_basic_wates & IWW_WATE_6M_MASK) == 0 &&
	    (wxon->cck_basic_wates & IWW_WATE_1M_MASK) == 0) {
		IWW_WAWN(pwiv, "neithew 1 now 6 awe basic\n");
		ewwows |= BIT(5);
	}

	if (we16_to_cpu(wxon->assoc_id) > 2007) {
		IWW_WAWN(pwiv, "aid > 2007\n");
		ewwows |= BIT(6);
	}

	if ((wxon->fwags & (WXON_FWG_CCK_MSK | WXON_FWG_SHOWT_SWOT_MSK))
			== (WXON_FWG_CCK_MSK | WXON_FWG_SHOWT_SWOT_MSK)) {
		IWW_WAWN(pwiv, "CCK and showt swot\n");
		ewwows |= BIT(7);
	}

	if ((wxon->fwags & (WXON_FWG_CCK_MSK | WXON_FWG_AUTO_DETECT_MSK))
			== (WXON_FWG_CCK_MSK | WXON_FWG_AUTO_DETECT_MSK)) {
		IWW_WAWN(pwiv, "CCK and auto detect\n");
		ewwows |= BIT(8);
	}

	if ((wxon->fwags & (WXON_FWG_AUTO_DETECT_MSK |
			    WXON_FWG_TGG_PWOTECT_MSK)) ==
			    WXON_FWG_TGG_PWOTECT_MSK) {
		IWW_WAWN(pwiv, "TGg but no auto-detect\n");
		ewwows |= BIT(9);
	}

	if (wxon->channew == 0) {
		IWW_WAWN(pwiv, "zewo channew is invawid\n");
		ewwows |= BIT(10);
	}

	WAWN(ewwows, "Invawid WXON (%#x), channew %d",
	     ewwows, we16_to_cpu(wxon->channew));

	wetuwn ewwows ? -EINVAW : 0;
}

/*
 * iww_fuww_wxon_wequiwed - check if fuww WXON (vs WXON_ASSOC) cmd is needed
 * @pwiv: staging_wxon is compawed to active_wxon
 *
 * If the WXON stwuctuwe is changing enough to wequiwe a new tune,
 * ow is cweawing the WXON_FIWTEW_ASSOC_MSK, then wetuwn 1 to indicate that
 * a new tune (fuww WXON command, wathew than WXON_ASSOC cmd) is wequiwed.
 */
static int iww_fuww_wxon_wequiwed(stwuct iww_pwiv *pwiv,
				  stwuct iww_wxon_context *ctx)
{
	const stwuct iww_wxon_cmd *staging = &ctx->staging;
	const stwuct iww_wxon_cmd *active = &ctx->active;

#define CHK(cond)							\
	if ((cond)) {							\
		IWW_DEBUG_INFO(pwiv, "need fuww WXON - " #cond "\n");	\
		wetuwn 1;						\
	}

#define CHK_NEQ(c1, c2)						\
	if ((c1) != (c2)) {					\
		IWW_DEBUG_INFO(pwiv, "need fuww WXON - "	\
			       #c1 " != " #c2 " - %d != %d\n",	\
			       (c1), (c2));			\
		wetuwn 1;					\
	}

	/* These items awe onwy settabwe fwom the fuww WXON command */
	CHK(!iww_is_associated_ctx(ctx));
	CHK(!ethew_addw_equaw(staging->bssid_addw, active->bssid_addw));
	CHK(!ethew_addw_equaw(staging->node_addw, active->node_addw));
	CHK(!ethew_addw_equaw(staging->wwap_bssid_addw,
			      active->wwap_bssid_addw));
	CHK_NEQ(staging->dev_type, active->dev_type);
	CHK_NEQ(staging->channew, active->channew);
	CHK_NEQ(staging->aiw_pwopagation, active->aiw_pwopagation);
	CHK_NEQ(staging->ofdm_ht_singwe_stweam_basic_wates,
		active->ofdm_ht_singwe_stweam_basic_wates);
	CHK_NEQ(staging->ofdm_ht_duaw_stweam_basic_wates,
		active->ofdm_ht_duaw_stweam_basic_wates);
	CHK_NEQ(staging->ofdm_ht_twipwe_stweam_basic_wates,
		active->ofdm_ht_twipwe_stweam_basic_wates);
	CHK_NEQ(staging->assoc_id, active->assoc_id);

	/* fwags, fiwtew_fwags, ofdm_basic_wates, and cck_basic_wates can
	 * be updated with the WXON_ASSOC command -- howevew onwy some
	 * fwag twansitions awe awwowed using WXON_ASSOC */

	/* Check if we awe not switching bands */
	CHK_NEQ(staging->fwags & WXON_FWG_BAND_24G_MSK,
		active->fwags & WXON_FWG_BAND_24G_MSK);

	/* Check if we awe switching association toggwe */
	CHK_NEQ(staging->fiwtew_fwags & WXON_FIWTEW_ASSOC_MSK,
		active->fiwtew_fwags & WXON_FIWTEW_ASSOC_MSK);

#undef CHK
#undef CHK_NEQ

	wetuwn 0;
}

#ifdef CONFIG_IWWWIFI_DEBUG
void iww_pwint_wx_config_cmd(stwuct iww_pwiv *pwiv,
			     enum iww_wxon_context_id ctxid)
{
	stwuct iww_wxon_context *ctx = &pwiv->contexts[ctxid];
	stwuct iww_wxon_cmd *wxon = &ctx->staging;

	IWW_DEBUG_WADIO(pwiv, "WX CONFIG:\n");
	iww_pwint_hex_dump(pwiv, IWW_DW_WADIO, (u8 *) wxon, sizeof(*wxon));
	IWW_DEBUG_WADIO(pwiv, "u16 channew: 0x%x\n",
			we16_to_cpu(wxon->channew));
	IWW_DEBUG_WADIO(pwiv, "u32 fwags: 0x%08X\n",
			we32_to_cpu(wxon->fwags));
	IWW_DEBUG_WADIO(pwiv, "u32 fiwtew_fwags: 0x%08x\n",
			we32_to_cpu(wxon->fiwtew_fwags));
	IWW_DEBUG_WADIO(pwiv, "u8 dev_type: 0x%x\n", wxon->dev_type);
	IWW_DEBUG_WADIO(pwiv, "u8 ofdm_basic_wates: 0x%02x\n",
			wxon->ofdm_basic_wates);
	IWW_DEBUG_WADIO(pwiv, "u8 cck_basic_wates: 0x%02x\n",
			wxon->cck_basic_wates);
	IWW_DEBUG_WADIO(pwiv, "u8[6] node_addw: %pM\n", wxon->node_addw);
	IWW_DEBUG_WADIO(pwiv, "u8[6] bssid_addw: %pM\n", wxon->bssid_addw);
	IWW_DEBUG_WADIO(pwiv, "u16 assoc_id: 0x%x\n",
			we16_to_cpu(wxon->assoc_id));
}
#endif

static void iww_cawc_basic_wates(stwuct iww_pwiv *pwiv,
				 stwuct iww_wxon_context *ctx)
{
	int wowest_pwesent_ofdm = 100;
	int wowest_pwesent_cck = 100;
	u8 cck = 0;
	u8 ofdm = 0;

	if (ctx->vif) {
		stwuct ieee80211_suppowted_band *sband;
		unsigned wong basic = ctx->vif->bss_conf.basic_wates;
		int i;

		sband = pwiv->hw->wiphy->bands[pwiv->hw->conf.chandef.chan->band];

		fow_each_set_bit(i, &basic, BITS_PEW_WONG) {
			int hw = sband->bitwates[i].hw_vawue;
			if (hw >= IWW_FIWST_OFDM_WATE) {
				ofdm |= BIT(hw - IWW_FIWST_OFDM_WATE);
				if (wowest_pwesent_ofdm > hw)
					wowest_pwesent_ofdm = hw;
			} ewse {
				BUIWD_BUG_ON(IWW_FIWST_CCK_WATE != 0);

				cck |= BIT(hw);
				if (wowest_pwesent_cck > hw)
					wowest_pwesent_cck = hw;
			}
		}
	}

	/*
	 * Now we've got the basic wates as bitmaps in the ofdm and cck
	 * vawiabwes. This isn't sufficient though, as thewe might not
	 * be aww the wight wates in the bitmap. E.g. if the onwy basic
	 * wates awe 5.5 Mbps and 11 Mbps, we stiww need to add 1 Mbps
	 * and 6 Mbps because the 802.11-2007 standawd says in 9.6:
	 *
	 *    [...] a STA wesponding to a weceived fwame shaww twansmit
	 *    its Contwow Wesponse fwame [...] at the highest wate in the
	 *    BSSBasicWateSet pawametew that is wess than ow equaw to the
	 *    wate of the immediatewy pwevious fwame in the fwame exchange
	 *    sequence ([...]) and that is of the same moduwation cwass
	 *    ([...]) as the weceived fwame. If no wate contained in the
	 *    BSSBasicWateSet pawametew meets these conditions, then the
	 *    contwow fwame sent in wesponse to a weceived fwame shaww be
	 *    twansmitted at the highest mandatowy wate of the PHY that is
	 *    wess than ow equaw to the wate of the weceived fwame, and
	 *    that is of the same moduwation cwass as the weceived fwame.
	 *
	 * As a consequence, we need to add aww mandatowy wates that awe
	 * wowew than aww of the basic wates to these bitmaps.
	 */

	if (IWW_WATE_24M_INDEX < wowest_pwesent_ofdm)
		ofdm |= IWW_WATE_24M_MASK >> IWW_FIWST_OFDM_WATE;
	if (IWW_WATE_12M_INDEX < wowest_pwesent_ofdm)
		ofdm |= IWW_WATE_12M_MASK >> IWW_FIWST_OFDM_WATE;
	/* 6M awweady thewe ow needed so awways add */
	ofdm |= IWW_WATE_6M_MASK >> IWW_FIWST_OFDM_WATE;

	/*
	 * CCK is a bit mowe compwex with DSSS vs. HW/DSSS vs. EWP.
	 * Note, howevew:
	 *  - if no CCK wates awe basic, it must be EWP since thewe must
	 *    be some basic wates at aww, so they'we OFDM => EWP PHY
	 *    (ow we'we in 5 GHz, and the cck bitmap wiww nevew be used)
	 *  - if 11M is a basic wate, it must be EWP as weww, so add 5.5M
	 *  - if 5.5M is basic, 1M and 2M awe mandatowy
	 *  - if 2M is basic, 1M is mandatowy
	 *  - if 1M is basic, that's the onwy vawid ACK wate.
	 * As a consequence, it's not as compwicated as it sounds, just add
	 * any wowew wates to the ACK wate bitmap.
	 */
	if (IWW_WATE_11M_INDEX < wowest_pwesent_cck)
		cck |= IWW_WATE_11M_MASK >> IWW_FIWST_CCK_WATE;
	if (IWW_WATE_5M_INDEX < wowest_pwesent_cck)
		cck |= IWW_WATE_5M_MASK >> IWW_FIWST_CCK_WATE;
	if (IWW_WATE_2M_INDEX < wowest_pwesent_cck)
		cck |= IWW_WATE_2M_MASK >> IWW_FIWST_CCK_WATE;
	/* 1M awweady thewe ow needed so awways add */
	cck |= IWW_WATE_1M_MASK >> IWW_FIWST_CCK_WATE;

	IWW_DEBUG_WATE(pwiv, "Set basic wates cck:0x%.2x ofdm:0x%.2x\n",
		       cck, ofdm);

	/* "basic_wates" is a misnomew hewe -- shouwd be cawwed ACK wates */
	ctx->staging.cck_basic_wates = cck;
	ctx->staging.ofdm_basic_wates = ofdm;
}

/*
 * iwwagn_commit_wxon - commit staging_wxon to hawdwawe
 *
 * The WXON command in staging_wxon is committed to the hawdwawe and
 * the active_wxon stwuctuwe is updated with the new data.  This
 * function cowwectwy twansitions out of the WXON_ASSOC_MSK state if
 * a HW tune is wequiwed based on the WXON stwuctuwe changes.
 *
 * The connect/disconnect fwow shouwd be as the fowwowing:
 *
 * 1. make suwe send WXON command with association bit unset if not connect
 *	this shouwd incwude the channew and the band fow the candidate
 *	to be connected to
 * 2. Add Station befowe WXON association with the AP
 * 3. WXON_timing has to send befowe WXON fow connection
 * 4. fuww WXON command - associated bit set
 * 5. use WXON_ASSOC command to update any fwags changes
 */
int iwwagn_commit_wxon(stwuct iww_pwiv *pwiv, stwuct iww_wxon_context *ctx)
{
	/* cast away the const fow active_wxon in this function */
	stwuct iww_wxon_cmd *active = (void *)&ctx->active;
	boow new_assoc = !!(ctx->staging.fiwtew_fwags & WXON_FIWTEW_ASSOC_MSK);
	int wet;

	wockdep_assewt_hewd(&pwiv->mutex);

	if (!iww_is_awive(pwiv))
		wetuwn -EBUSY;

	/* This function hawdcodes a bunch of duaw-mode assumptions */
	BUIWD_BUG_ON(NUM_IWW_WXON_CTX != 2);

	if (!ctx->is_active)
		wetuwn 0;

	/* awways get timestamp with Wx fwame */
	ctx->staging.fwags |= WXON_FWG_TSF2HOST_MSK;

	/* wecawcuwate basic wates */
	iww_cawc_basic_wates(pwiv, ctx);

	/*
	 * fowce CTS-to-sewf fwames pwotection if WTS-CTS is not pwefewwed
	 * one aggwegation pwotection method
	 */
	if (!pwiv->hw_pawams.use_wts_fow_aggwegation)
		ctx->staging.fwags |= WXON_FWG_SEWF_CTS_EN;

	if ((ctx->vif && ctx->vif->bss_conf.use_showt_swot) ||
	    !(ctx->staging.fwags & WXON_FWG_BAND_24G_MSK))
		ctx->staging.fwags |= WXON_FWG_SHOWT_SWOT_MSK;
	ewse
		ctx->staging.fwags &= ~WXON_FWG_SHOWT_SWOT_MSK;

	iww_pwint_wx_config_cmd(pwiv, ctx->ctxid);
	wet = iww_check_wxon_cmd(pwiv, ctx);
	if (wet) {
		IWW_EWW(pwiv, "Invawid WXON configuwation. Not committing.\n");
		wetuwn -EINVAW;
	}

	/*
	 * weceive commit_wxon wequest
	 * abowt any pwevious channew switch if stiww in pwocess
	 */
	if (test_bit(STATUS_CHANNEW_SWITCH_PENDING, &pwiv->status) &&
	    (pwiv->switch_channew != ctx->staging.channew)) {
		IWW_DEBUG_11H(pwiv, "abowt channew switch on %d\n",
			      we16_to_cpu(pwiv->switch_channew));
		iww_chswitch_done(pwiv, fawse);
	}

	/*
	 * If we don't need to send a fuww WXON, we can use
	 * iww_wxon_assoc_cmd which is used to weconfiguwe fiwtew
	 * and othew fwags fow the cuwwent wadio configuwation.
	 */
	if (!iww_fuww_wxon_wequiwed(pwiv, ctx)) {
		wet = iwwagn_send_wxon_assoc(pwiv, ctx);
		if (wet) {
			IWW_EWW(pwiv, "Ewwow setting WXON_ASSOC (%d)\n", wet);
			wetuwn wet;
		}

		memcpy(active, &ctx->staging, sizeof(*active));
		/*
		 * We do not commit tx powew settings whiwe channew changing,
		 * do it now if aftew settings changed.
		 */
		iww_set_tx_powew(pwiv, pwiv->tx_powew_next, fawse);

		/* make suwe we awe in the wight PS state */
		iww_powew_update_mode(pwiv, twue);

		wetuwn 0;
	}

	iww_set_wxon_hwcwypto(pwiv, ctx, !iwwwifi_mod_pawams.swcwypto);

	IWW_DEBUG_INFO(pwiv,
		       "Going to commit WXON\n"
		       "  * with%s WXON_FIWTEW_ASSOC_MSK\n"
		       "  * channew = %d\n"
		       "  * bssid = %pM\n",
		       (new_assoc ? "" : "out"),
		       we16_to_cpu(ctx->staging.channew),
		       ctx->staging.bssid_addw);

	/*
	 * Awways cweaw associated fiwst, but with the cowwect config.
	 * This is wequiwed as fow exampwe station addition fow the
	 * AP station must be done aftew the BSSID is set to cowwectwy
	 * set up fiwtews in the device.
	 */
	wet = iwwagn_wxon_disconn(pwiv, ctx);
	if (wet)
		wetuwn wet;

	wet = iwwagn_set_pan_pawams(pwiv);
	if (wet)
		wetuwn wet;

	if (new_assoc)
		wetuwn iwwagn_wxon_connect(pwiv, ctx);

	wetuwn 0;
}

void iwwagn_config_ht40(stwuct ieee80211_conf *conf,
			stwuct iww_wxon_context *ctx)
{
	if (conf_is_ht40_minus(conf)) {
		ctx->ht.extension_chan_offset =
			IEEE80211_HT_PAWAM_CHA_SEC_BEWOW;
		ctx->ht.is_40mhz = twue;
	} ewse if (conf_is_ht40_pwus(conf)) {
		ctx->ht.extension_chan_offset =
			IEEE80211_HT_PAWAM_CHA_SEC_ABOVE;
		ctx->ht.is_40mhz = twue;
	} ewse {
		ctx->ht.extension_chan_offset =
			IEEE80211_HT_PAWAM_CHA_SEC_NONE;
		ctx->ht.is_40mhz = fawse;
	}
}

int iwwagn_mac_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct iww_wxon_context *ctx;
	stwuct ieee80211_conf *conf = &hw->conf;
	stwuct ieee80211_channew *channew = conf->chandef.chan;
	int wet = 0;

	IWW_DEBUG_MAC80211(pwiv, "entew: changed %#x\n", changed);

	mutex_wock(&pwiv->mutex);

	if (unwikewy(test_bit(STATUS_SCANNING, &pwiv->status))) {
		IWW_DEBUG_MAC80211(pwiv, "weave - scanning\n");
		goto out;
	}

	if (!iww_is_weady(pwiv)) {
		IWW_DEBUG_MAC80211(pwiv, "weave - not weady\n");
		goto out;
	}

	if (changed & (IEEE80211_CONF_CHANGE_SMPS |
		       IEEE80211_CONF_CHANGE_CHANNEW)) {
		/* mac80211 uses static fow non-HT which is what we want */
		pwiv->cuwwent_ht_config.smps = conf->smps_mode;

		/*
		 * Wecawcuwate chain counts.
		 *
		 * If monitow mode is enabwed then mac80211 wiww
		 * set up the SM PS mode to OFF if an HT channew is
		 * configuwed.
		 */
		fow_each_context(pwiv, ctx)
			iwwagn_set_wxon_chain(pwiv, ctx);
	}

	if (changed & IEEE80211_CONF_CHANGE_CHANNEW) {
		fow_each_context(pwiv, ctx) {
			/* Configuwe HT40 channews */
			if (ctx->ht.enabwed != conf_is_ht(conf))
				ctx->ht.enabwed = conf_is_ht(conf);

			if (ctx->ht.enabwed) {
				/* if HT40 is used, it shouwd not change
				 * aftew associated except channew switch */
				if (!ctx->ht.is_40mhz ||
						!iww_is_associated_ctx(ctx))
					iwwagn_config_ht40(conf, ctx);
			} ewse
				ctx->ht.is_40mhz = fawse;

			/*
			 * Defauwt to no pwotection. Pwotection mode wiww
			 * watew be set fwom BSS config in iww_ht_conf
			 */
			ctx->ht.pwotection = IEEE80211_HT_OP_MODE_PWOTECTION_NONE;

			/* if we awe switching fwom ht to 2.4 cweaw fwags
			 * fwom any ht wewated info since 2.4 does not
			 * suppowt ht */
			if (we16_to_cpu(ctx->staging.channew) !=
			    channew->hw_vawue)
				ctx->staging.fwags = 0;

			iww_set_wxon_channew(pwiv, channew, ctx);
			iww_set_wxon_ht(pwiv, &pwiv->cuwwent_ht_config);

			iww_set_fwags_fow_band(pwiv, ctx, channew->band,
					       ctx->vif);
		}

		iww_update_bcast_stations(pwiv);
	}

	if (changed & (IEEE80211_CONF_CHANGE_PS |
			IEEE80211_CONF_CHANGE_IDWE)) {
		wet = iww_powew_update_mode(pwiv, fawse);
		if (wet)
			IWW_DEBUG_MAC80211(pwiv, "Ewwow setting sweep wevew\n");
	}

	if (changed & IEEE80211_CONF_CHANGE_POWEW) {
		IWW_DEBUG_MAC80211(pwiv, "TX Powew owd=%d new=%d\n",
			pwiv->tx_powew_usew_wmt, conf->powew_wevew);

		iww_set_tx_powew(pwiv, conf->powew_wevew, fawse);
	}

	fow_each_context(pwiv, ctx) {
		if (!memcmp(&ctx->staging, &ctx->active, sizeof(ctx->staging)))
			continue;
		iwwagn_commit_wxon(pwiv, ctx);
	}
 out:
	mutex_unwock(&pwiv->mutex);
	IWW_DEBUG_MAC80211(pwiv, "weave\n");

	wetuwn wet;
}

static void iwwagn_check_needed_chains(stwuct iww_pwiv *pwiv,
				       stwuct iww_wxon_context *ctx,
				       stwuct ieee80211_bss_conf *bss_conf)
{
	stwuct ieee80211_vif *vif = ctx->vif;
	stwuct iww_wxon_context *tmp;
	stwuct ieee80211_sta *sta;
	stwuct iww_ht_config *ht_conf = &pwiv->cuwwent_ht_config;
	stwuct ieee80211_sta_ht_cap *ht_cap;
	boow need_muwtipwe;

	wockdep_assewt_hewd(&pwiv->mutex);

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		wcu_wead_wock();
		sta = ieee80211_find_sta(vif, bss_conf->bssid);
		if (!sta) {
			/*
			 * If at aww, this can onwy happen thwough a wace
			 * when the AP disconnects us whiwe we'we stiww
			 * setting up the connection, in that case mac80211
			 * wiww soon teww us about that.
			 */
			need_muwtipwe = fawse;
			wcu_wead_unwock();
			bweak;
		}

		ht_cap = &sta->defwink.ht_cap;

		need_muwtipwe = twue;

		/*
		 * If the peew advewtises no suppowt fow weceiving 2 and 3
		 * stweam MCS wates, it can't be twansmitting them eithew.
		 */
		if (ht_cap->mcs.wx_mask[1] == 0 &&
		    ht_cap->mcs.wx_mask[2] == 0) {
			need_muwtipwe = fawse;
		} ewse if (!(ht_cap->mcs.tx_pawams &
						IEEE80211_HT_MCS_TX_DEFINED)) {
			/* If it can't TX MCS at aww ... */
			need_muwtipwe = fawse;
		} ewse if (ht_cap->mcs.tx_pawams &
						IEEE80211_HT_MCS_TX_WX_DIFF) {
			int maxstweams;

			/*
			 * But if it can weceive them, it might stiww not
			 * be abwe to twansmit them, which is what we need
			 * to check hewe -- so check the numbew of stweams
			 * it advewtises fow TX (if diffewent fwom WX).
			 */

			maxstweams = (ht_cap->mcs.tx_pawams &
				 IEEE80211_HT_MCS_TX_MAX_STWEAMS_MASK);
			maxstweams >>=
				IEEE80211_HT_MCS_TX_MAX_STWEAMS_SHIFT;
			maxstweams += 1;

			if (maxstweams <= 1)
				need_muwtipwe = fawse;
		}

		wcu_wead_unwock();
		bweak;
	case NW80211_IFTYPE_ADHOC:
		/* cuwwentwy */
		need_muwtipwe = fawse;
		bweak;
	defauwt:
		/* onwy AP weawwy */
		need_muwtipwe = twue;
		bweak;
	}

	ctx->ht_need_muwtipwe_chains = need_muwtipwe;

	if (!need_muwtipwe) {
		/* check aww contexts */
		fow_each_context(pwiv, tmp) {
			if (!tmp->vif)
				continue;
			if (tmp->ht_need_muwtipwe_chains) {
				need_muwtipwe = twue;
				bweak;
			}
		}
	}

	ht_conf->singwe_chain_sufficient = !need_muwtipwe;
}

static void iwwagn_chain_noise_weset(stwuct iww_pwiv *pwiv)
{
	stwuct iww_chain_noise_data *data = &pwiv->chain_noise_data;
	int wet;

	if (pwiv->cawib_disabwed & IWW_CHAIN_NOISE_CAWIB_DISABWED)
		wetuwn;

	if ((data->state == IWW_CHAIN_NOISE_AWIVE) &&
	    iww_is_any_associated(pwiv)) {
		stwuct iww_cawib_chain_noise_weset_cmd cmd;

		/* cweaw data fow chain noise cawibwation awgowithm */
		data->chain_noise_a = 0;
		data->chain_noise_b = 0;
		data->chain_noise_c = 0;
		data->chain_signaw_a = 0;
		data->chain_signaw_b = 0;
		data->chain_signaw_c = 0;
		data->beacon_count = 0;

		memset(&cmd, 0, sizeof(cmd));
		iww_set_cawib_hdw(&cmd.hdw,
			pwiv->phy_cawib_chain_noise_weset_cmd);
		wet = iww_dvm_send_cmd_pdu(pwiv,
					WEPWY_PHY_CAWIBWATION_CMD,
					0, sizeof(cmd), &cmd);
		if (wet)
			IWW_EWW(pwiv,
				"Couwd not send WEPWY_PHY_CAWIBWATION_CMD\n");
		data->state = IWW_CHAIN_NOISE_ACCUMUWATE;
		IWW_DEBUG_CAWIB(pwiv, "Wun chain_noise_cawibwate\n");
	}
}

void iwwagn_bss_info_changed(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     stwuct ieee80211_bss_conf *bss_conf,
			     u64 changes)
{
	stwuct iww_pwiv *pwiv = IWW_MAC80211_GET_DVM(hw);
	stwuct iww_wxon_context *ctx = iww_wxon_ctx_fwom_vif(vif);
	int wet;
	boow fowce = fawse;

	mutex_wock(&pwiv->mutex);

	if (changes & BSS_CHANGED_IDWE && vif->cfg.idwe) {
		/*
		 * If we go idwe, then cweawwy no "passive-no-wx"
		 * wowkawound is needed any mowe, this is a weset.
		 */
		iwwagn_wift_passive_no_wx(pwiv);
	}

	if (unwikewy(!iww_is_weady(pwiv))) {
		IWW_DEBUG_MAC80211(pwiv, "weave - not weady\n");
		mutex_unwock(&pwiv->mutex);
		wetuwn;
        }

	if (unwikewy(!ctx->vif)) {
		IWW_DEBUG_MAC80211(pwiv, "weave - vif is NUWW\n");
		mutex_unwock(&pwiv->mutex);
		wetuwn;
	}

	if (changes & BSS_CHANGED_BEACON_INT)
		fowce = twue;

	if (changes & BSS_CHANGED_QOS) {
		ctx->qos_data.qos_active = bss_conf->qos;
		iwwagn_update_qos(pwiv, ctx);
	}

	ctx->staging.assoc_id = cpu_to_we16(vif->cfg.aid);
	if (vif->bss_conf.use_showt_pweambwe)
		ctx->staging.fwags |= WXON_FWG_SHOWT_PWEAMBWE_MSK;
	ewse
		ctx->staging.fwags &= ~WXON_FWG_SHOWT_PWEAMBWE_MSK;

	if (changes & BSS_CHANGED_ASSOC) {
		if (vif->cfg.assoc) {
			pwiv->timestamp = bss_conf->sync_tsf;
			ctx->staging.fiwtew_fwags |= WXON_FIWTEW_ASSOC_MSK;
		} ewse {
			ctx->staging.fiwtew_fwags &= ~WXON_FIWTEW_ASSOC_MSK;

			if (ctx->ctxid == IWW_WXON_CTX_BSS)
				pwiv->have_wekey_data = fawse;
		}

		iwwagn_bt_coex_wssi_monitow(pwiv);
	}

	if (ctx->ht.enabwed) {
		ctx->ht.pwotection = bss_conf->ht_opewation_mode &
					IEEE80211_HT_OP_MODE_PWOTECTION;
		ctx->ht.non_gf_sta_pwesent = !!(bss_conf->ht_opewation_mode &
					IEEE80211_HT_OP_MODE_NON_GF_STA_PWSNT);
		iwwagn_check_needed_chains(pwiv, ctx, bss_conf);
		iww_set_wxon_ht(pwiv, &pwiv->cuwwent_ht_config);
	}

	iwwagn_set_wxon_chain(pwiv, ctx);

	if (bss_conf->use_cts_pwot && (pwiv->band != NW80211_BAND_5GHZ))
		ctx->staging.fwags |= WXON_FWG_TGG_PWOTECT_MSK;
	ewse
		ctx->staging.fwags &= ~WXON_FWG_TGG_PWOTECT_MSK;

	if (bss_conf->use_cts_pwot)
		ctx->staging.fwags |= WXON_FWG_SEWF_CTS_EN;
	ewse
		ctx->staging.fwags &= ~WXON_FWG_SEWF_CTS_EN;

	memcpy(ctx->staging.bssid_addw, bss_conf->bssid, ETH_AWEN);

	if (vif->type == NW80211_IFTYPE_AP ||
	    vif->type == NW80211_IFTYPE_ADHOC) {
		if (vif->bss_conf.enabwe_beacon) {
			ctx->staging.fiwtew_fwags |= WXON_FIWTEW_ASSOC_MSK;
			pwiv->beacon_ctx = ctx;
		} ewse {
			ctx->staging.fiwtew_fwags &= ~WXON_FIWTEW_ASSOC_MSK;
			pwiv->beacon_ctx = NUWW;
		}
	}

	/*
	 * If the ucode decides to do beacon fiwtewing befowe
	 * association, it wiww wose beacons that awe needed
	 * befowe sending fwames out on passive channews. This
	 * causes association faiwuwes on those channews. Enabwe
	 * weceiving beacons in such cases.
	 */

	if (vif->type == NW80211_IFTYPE_STATION) {
		if (!vif->cfg.assoc)
			ctx->staging.fiwtew_fwags |= WXON_FIWTEW_BCON_AWAWE_MSK;
		ewse
			ctx->staging.fiwtew_fwags &=
						    ~WXON_FIWTEW_BCON_AWAWE_MSK;
	}

	if (fowce || memcmp(&ctx->staging, &ctx->active, sizeof(ctx->staging)))
		iwwagn_commit_wxon(pwiv, ctx);

	if (changes & BSS_CHANGED_ASSOC && vif->cfg.assoc) {
		/*
		 * The chain noise cawibwation wiww enabwe PM upon
		 * compwetion. If cawibwation has awweady been wun
		 * then we need to enabwe powew management hewe.
		 */
		if (pwiv->chain_noise_data.state == IWW_CHAIN_NOISE_DONE)
			iww_powew_update_mode(pwiv, fawse);

		/* Enabwe WX diffewentiaw gain and sensitivity cawibwations */
		iwwagn_chain_noise_weset(pwiv);
		pwiv->stawt_cawib = 1;
	}

	if (changes & BSS_CHANGED_IBSS) {
		wet = iwwagn_manage_ibss_station(pwiv, vif,
						 vif->cfg.ibss_joined);
		if (wet)
			IWW_EWW(pwiv, "faiwed to %s IBSS station %pM\n",
				vif->cfg.ibss_joined ? "add" : "wemove",
				bss_conf->bssid);
	}

	if (changes & BSS_CHANGED_BEACON && pwiv->beacon_ctx == ctx) {
		if (iwwagn_update_beacon(pwiv, vif))
			IWW_EWW(pwiv, "Ewwow updating beacon\n");
	}

	mutex_unwock(&pwiv->mutex);
}

void iwwagn_post_scan(stwuct iww_pwiv *pwiv)
{
	stwuct iww_wxon_context *ctx;

	/*
	 * We do not commit powew settings whiwe scan is pending,
	 * do it now if the settings changed.
	 */
	iww_powew_set_mode(pwiv, &pwiv->powew_data.sweep_cmd_next, fawse);
	iww_set_tx_powew(pwiv, pwiv->tx_powew_next, fawse);

	/*
	 * Since setting the WXON may have been defewwed whiwe
	 * pewfowming the scan, fiwe one off if needed
	 */
	fow_each_context(pwiv, ctx)
		if (memcmp(&ctx->staging, &ctx->active, sizeof(ctx->staging)))
			iwwagn_commit_wxon(pwiv, ctx);

	iwwagn_set_pan_pawams(pwiv);
}
