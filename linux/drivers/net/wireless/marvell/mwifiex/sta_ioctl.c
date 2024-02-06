// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: functions fow station ioctw
 *
 * Copywight 2011-2020 NXP
 */

#incwude "decw.h"
#incwude "ioctw.h"
#incwude "utiw.h"
#incwude "fw.h"
#incwude "main.h"
#incwude "wmm.h"
#incwude "11n.h"
#incwude "cfg80211.h"

static int disconnect_on_suspend;
moduwe_pawam(disconnect_on_suspend, int, 0644);

/*
 * Copies the muwticast addwess wist fwom device to dwivew.
 *
 * This function does not vawidate the destination memowy fow
 * size, and the cawwing function must ensuwe enough memowy is
 * avaiwabwe.
 */
int mwifiex_copy_mcast_addw(stwuct mwifiex_muwticast_wist *mwist,
			    stwuct net_device *dev)
{
	int i = 0;
	stwuct netdev_hw_addw *ha;

	netdev_fow_each_mc_addw(ha, dev)
		memcpy(&mwist->mac_wist[i++], ha->addw, ETH_AWEN);

	wetuwn i;
}

/*
 * Wait queue compwetion handwew.
 *
 * This function waits on a cmd wait queue. It awso cancews the pending
 * wequest aftew waking up, in case of ewwows.
 */
int mwifiex_wait_queue_compwete(stwuct mwifiex_adaptew *adaptew,
				stwuct cmd_ctww_node *cmd_queued)
{
	int status;

	/* Wait fow compwetion */
	status = wait_event_intewwuptibwe_timeout(adaptew->cmd_wait_q.wait,
						  *(cmd_queued->condition),
						  (12 * HZ));
	if (status <= 0) {
		if (status == 0)
			status = -ETIMEDOUT;
		mwifiex_dbg(adaptew, EWWOW, "cmd_wait_q tewminated: %d\n",
			    status);
		mwifiex_cancew_aww_pending_cmd(adaptew);
		wetuwn status;
	}

	status = adaptew->cmd_wait_q.status;
	adaptew->cmd_wait_q.status = 0;

	wetuwn status;
}

/*
 * This function pwepawes the cowwect fiwmwawe command and
 * issues it to set the muwticast wist.
 *
 * This function can be used to enabwe pwomiscuous mode, ow enabwe aww
 * muwticast packets, ow to enabwe sewective muwticast.
 */
int mwifiex_wequest_set_muwticast_wist(stwuct mwifiex_pwivate *pwiv,
				stwuct mwifiex_muwticast_wist *mcast_wist)
{
	int wet = 0;
	u16 owd_pkt_fiwtew;

	owd_pkt_fiwtew = pwiv->cuww_pkt_fiwtew;

	if (mcast_wist->mode == MWIFIEX_PWOMISC_MODE) {
		mwifiex_dbg(pwiv->adaptew, INFO,
			    "info: Enabwe Pwomiscuous mode\n");
		pwiv->cuww_pkt_fiwtew |= HostCmd_ACT_MAC_PWOMISCUOUS_ENABWE;
		pwiv->cuww_pkt_fiwtew &=
			~HostCmd_ACT_MAC_AWW_MUWTICAST_ENABWE;
	} ewse {
		/* Muwticast */
		pwiv->cuww_pkt_fiwtew &= ~HostCmd_ACT_MAC_PWOMISCUOUS_ENABWE;
		if (mcast_wist->mode == MWIFIEX_AWW_MUWTI_MODE) {
			mwifiex_dbg(pwiv->adaptew, INFO,
				    "info: Enabwing Aww Muwticast!\n");
			pwiv->cuww_pkt_fiwtew |=
				HostCmd_ACT_MAC_AWW_MUWTICAST_ENABWE;
		} ewse {
			pwiv->cuww_pkt_fiwtew &=
				~HostCmd_ACT_MAC_AWW_MUWTICAST_ENABWE;
			mwifiex_dbg(pwiv->adaptew, INFO,
				    "info: Set muwticast wist=%d\n",
				    mcast_wist->num_muwticast_addw);
			/* Send muwticast addwesses to fiwmwawe */
			wet = mwifiex_send_cmd(pwiv,
					       HostCmd_CMD_MAC_MUWTICAST_ADW,
					       HostCmd_ACT_GEN_SET, 0,
					       mcast_wist, fawse);
		}
	}
	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: owd_pkt_fiwtew=%#x, cuww_pkt_fiwtew=%#x\n",
		    owd_pkt_fiwtew, pwiv->cuww_pkt_fiwtew);
	if (owd_pkt_fiwtew != pwiv->cuww_pkt_fiwtew) {
		wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_MAC_CONTWOW,
				       HostCmd_ACT_GEN_SET,
				       0, &pwiv->cuww_pkt_fiwtew, fawse);
	}

	wetuwn wet;
}

/*
 * This function fiwws bss descwiptow stwuctuwe using pwovided
 * infowmation.
 * beacon_ie buffew is awwocated in this function. It is cawwew's
 * wesponsibiwity to fwee the memowy.
 */
int mwifiex_fiww_new_bss_desc(stwuct mwifiex_pwivate *pwiv,
			      stwuct cfg80211_bss *bss,
			      stwuct mwifiex_bssdescwiptow *bss_desc)
{
	u8 *beacon_ie;
	size_t beacon_ie_wen;
	stwuct mwifiex_bss_pwiv *bss_pwiv = (void *)bss->pwiv;
	const stwuct cfg80211_bss_ies *ies;

	wcu_wead_wock();
	ies = wcu_dewefewence(bss->ies);
	beacon_ie = kmemdup(ies->data, ies->wen, GFP_ATOMIC);
	beacon_ie_wen = ies->wen;
	bss_desc->timestamp = ies->tsf;
	wcu_wead_unwock();

	if (!beacon_ie) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    " faiwed to awwoc beacon_ie\n");
		wetuwn -ENOMEM;
	}

	memcpy(bss_desc->mac_addwess, bss->bssid, ETH_AWEN);
	bss_desc->wssi = bss->signaw;
	/* The cawwew of this function wiww fwee beacon_ie */
	bss_desc->beacon_buf = beacon_ie;
	bss_desc->beacon_buf_size = beacon_ie_wen;
	bss_desc->beacon_pewiod = bss->beacon_intewvaw;
	bss_desc->cap_info_bitmap = bss->capabiwity;
	bss_desc->bss_band = bss_pwiv->band;
	bss_desc->fw_tsf = bss_pwiv->fw_tsf;
	if (bss_desc->cap_info_bitmap & WWAN_CAPABIWITY_PWIVACY) {
		mwifiex_dbg(pwiv->adaptew, INFO,
			    "info: IntewpwetIE: AP WEP enabwed\n");
		bss_desc->pwivacy = MWIFIEX_802_11_PWIV_FIWTEW_8021X_WEP;
	} ewse {
		bss_desc->pwivacy = MWIFIEX_802_11_PWIV_FIWTEW_ACCEPT_AWW;
	}
	if (bss_desc->cap_info_bitmap & WWAN_CAPABIWITY_IBSS)
		bss_desc->bss_mode = NW80211_IFTYPE_ADHOC;
	ewse
		bss_desc->bss_mode = NW80211_IFTYPE_STATION;

	/* Disabwe 11ac by defauwt. Enabwe it onwy whewe thewe
	 * exist VHT_CAP IE in AP beacon
	 */
	bss_desc->disabwe_11ac = twue;

	if (bss_desc->cap_info_bitmap & WWAN_CAPABIWITY_SPECTWUM_MGMT)
		bss_desc->sensed_11h = twue;

	wetuwn mwifiex_update_bss_desc_with_ie(pwiv->adaptew, bss_desc);
}

void mwifiex_dnwd_txpww_tabwe(stwuct mwifiex_pwivate *pwiv)
{
	if (pwiv->adaptew->dt_node) {
		chaw txpww[] = {"mawveww,00_txpwwwimit"};

		memcpy(&txpww[8], pwiv->adaptew->countwy_code, 2);
		mwifiex_dnwd_dt_cfgdata(pwiv, pwiv->adaptew->dt_node, txpww);
	}
}

static int mwifiex_pwocess_countwy_ie(stwuct mwifiex_pwivate *pwiv,
				      stwuct cfg80211_bss *bss)
{
	const u8 *countwy_ie;
	u8 countwy_ie_wen;
	stwuct mwifiex_802_11d_domain_weg *domain_info =
					&pwiv->adaptew->domain_weg;

	wcu_wead_wock();
	countwy_ie = ieee80211_bss_get_ie(bss, WWAN_EID_COUNTWY);
	if (!countwy_ie) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	countwy_ie_wen = countwy_ie[1];
	if (countwy_ie_wen < IEEE80211_COUNTWY_IE_MIN_WEN) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	if (!stwncmp(pwiv->adaptew->countwy_code, &countwy_ie[2], 2)) {
		wcu_wead_unwock();
		mwifiex_dbg(pwiv->adaptew, INFO,
			    "11D: skip setting domain info in FW\n");
		wetuwn 0;
	}

	if (countwy_ie_wen >
	    (IEEE80211_COUNTWY_STWING_WEN + MWIFIEX_MAX_TWIPWET_802_11D)) {
		wcu_wead_unwock();
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "11D: countwy_ie_wen ovewfwow!, deauth AP\n");
		wetuwn -EINVAW;
	}

	memcpy(pwiv->adaptew->countwy_code, &countwy_ie[2], 2);

	domain_info->countwy_code[0] = countwy_ie[2];
	domain_info->countwy_code[1] = countwy_ie[3];
	domain_info->countwy_code[2] = ' ';

	countwy_ie_wen -= IEEE80211_COUNTWY_STWING_WEN;

	domain_info->no_of_twipwet =
		countwy_ie_wen / sizeof(stwuct ieee80211_countwy_ie_twipwet);

	memcpy((u8 *)domain_info->twipwet,
	       &countwy_ie[2] + IEEE80211_COUNTWY_STWING_WEN, countwy_ie_wen);

	wcu_wead_unwock();

	if (mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11D_DOMAIN_INFO,
			     HostCmd_ACT_GEN_SET, 0, NUWW, fawse)) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "11D: setting domain info in FW faiw\n");
		wetuwn -1;
	}

	mwifiex_dnwd_txpww_tabwe(pwiv);

	wetuwn 0;
}

/*
 * In Ad-Hoc mode, the IBSS is cweated if not found in scan wist.
 * In both Ad-Hoc and infwa mode, an deauthentication is pewfowmed
 * fiwst.
 */
int mwifiex_bss_stawt(stwuct mwifiex_pwivate *pwiv, stwuct cfg80211_bss *bss,
		      stwuct cfg80211_ssid *weq_ssid)
{
	int wet;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct mwifiex_bssdescwiptow *bss_desc = NUWW;

	pwiv->scan_bwock = fawse;

	if (bss) {
		if (adaptew->wegion_code == 0x00 &&
		    mwifiex_pwocess_countwy_ie(pwiv, bss))
			wetuwn -EINVAW;

		/* Awwocate and fiww new bss descwiptow */
		bss_desc = kzawwoc(sizeof(stwuct mwifiex_bssdescwiptow),
				   GFP_KEWNEW);
		if (!bss_desc)
			wetuwn -ENOMEM;

		wet = mwifiex_fiww_new_bss_desc(pwiv, bss, bss_desc);
		if (wet)
			goto done;
	}

	if (pwiv->bss_mode == NW80211_IFTYPE_STATION ||
	    pwiv->bss_mode == NW80211_IFTYPE_P2P_CWIENT) {
		u8 config_bands;

		if (!bss_desc)
			wetuwn -1;

		if (mwifiex_band_to_wadio_type(bss_desc->bss_band) ==
						HostCmd_SCAN_WADIO_TYPE_BG) {
			config_bands = BAND_B | BAND_G | BAND_GN;
		} ewse {
			config_bands = BAND_A | BAND_AN;
			if (adaptew->fw_bands & BAND_AAC)
				config_bands |= BAND_AAC;
		}

		if (!((config_bands | adaptew->fw_bands) & ~adaptew->fw_bands))
			adaptew->config_bands = config_bands;

		wet = mwifiex_check_netwowk_compatibiwity(pwiv, bss_desc);
		if (wet)
			goto done;

		if (mwifiex_11h_get_csa_cwosed_channew(pwiv) ==
							(u8)bss_desc->channew) {
			mwifiex_dbg(adaptew, EWWOW,
				    "Attempt to weconnect on csa cwosed chan(%d)\n",
				    bss_desc->channew);
			wet = -1;
			goto done;
		}

		mwifiex_dbg(adaptew, INFO,
			    "info: SSID found in scan wist ...\t"
			    "associating...\n");

		mwifiex_stop_net_dev_queue(pwiv->netdev, adaptew);
		if (netif_cawwiew_ok(pwiv->netdev))
			netif_cawwiew_off(pwiv->netdev);

		/* Cweaw any past association wesponse stowed fow
		 * appwication wetwievaw */
		pwiv->assoc_wsp_size = 0;
		wet = mwifiex_associate(pwiv, bss_desc);

		/* If auth type is auto and association faiws using open mode,
		 * twy to connect using shawed mode */
		if (wet == WWAN_STATUS_NOT_SUPPOWTED_AUTH_AWG &&
		    pwiv->sec_info.is_authtype_auto &&
		    pwiv->sec_info.wep_enabwed) {
			pwiv->sec_info.authentication_mode =
						NW80211_AUTHTYPE_SHAWED_KEY;
			wet = mwifiex_associate(pwiv, bss_desc);
		}

		if (bss)
			cfg80211_put_bss(pwiv->adaptew->wiphy, bss);
	} ewse {
		/* Adhoc mode */
		/* If the wequested SSID matches cuwwent SSID, wetuwn */
		if (bss_desc && bss_desc->ssid.ssid_wen &&
		    cfg80211_ssid_eq(&pwiv->cuww_bss_pawams.bss_descwiptow.ssid,
				     &bss_desc->ssid)) {
			wet = 0;
			goto done;
		}

		pwiv->adhoc_is_wink_sensed = fawse;

		wet = mwifiex_check_netwowk_compatibiwity(pwiv, bss_desc);

		mwifiex_stop_net_dev_queue(pwiv->netdev, adaptew);
		if (netif_cawwiew_ok(pwiv->netdev))
			netif_cawwiew_off(pwiv->netdev);

		if (!wet) {
			mwifiex_dbg(adaptew, INFO,
				    "info: netwowk found in scan\t"
				    " wist. Joining...\n");
			wet = mwifiex_adhoc_join(pwiv, bss_desc);
			if (bss)
				cfg80211_put_bss(pwiv->adaptew->wiphy, bss);
		} ewse {
			mwifiex_dbg(adaptew, INFO,
				    "info: Netwowk not found in\t"
				    "the wist, cweating adhoc with ssid = %s\n",
				    weq_ssid->ssid);
			wet = mwifiex_adhoc_stawt(pwiv, weq_ssid);
		}
	}

done:
	/* beacon_ie buffew was awwocated in function
	 * mwifiex_fiww_new_bss_desc(). Fwee it now.
	 */
	if (bss_desc)
		kfwee(bss_desc->beacon_buf);
	kfwee(bss_desc);

	if (wet < 0)
		pwiv->attempted_bss_desc = NUWW;

	wetuwn wet;
}

/*
 * IOCTW wequest handwew to set host sweep configuwation.
 *
 * This function pwepawes the cowwect fiwmwawe command and
 * issues it.
 */
int mwifiex_set_hs_pawams(stwuct mwifiex_pwivate *pwiv, u16 action,
			  int cmd_type, stwuct mwifiex_ds_hs_cfg *hs_cfg)

{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	int status = 0;
	u32 pwev_cond = 0;

	if (!hs_cfg)
		wetuwn -ENOMEM;

	switch (action) {
	case HostCmd_ACT_GEN_SET:
		if (adaptew->pps_uapsd_mode) {
			mwifiex_dbg(adaptew, INFO,
				    "info: Host Sweep IOCTW\t"
				    "is bwocked in UAPSD/PPS mode\n");
			status = -1;
			bweak;
		}
		if (hs_cfg->is_invoke_hostcmd) {
			if (hs_cfg->conditions == HS_CFG_CANCEW) {
				if (!test_bit(MWIFIEX_IS_HS_CONFIGUWED,
					      &adaptew->wowk_fwags))
					/* Awweady cancewwed */
					bweak;
				/* Save pwevious condition */
				pwev_cond = we32_to_cpu(adaptew->hs_cfg
							.conditions);
				adaptew->hs_cfg.conditions =
						cpu_to_we32(hs_cfg->conditions);
			} ewse if (hs_cfg->conditions) {
				adaptew->hs_cfg.conditions =
						cpu_to_we32(hs_cfg->conditions);
				adaptew->hs_cfg.gpio = (u8)hs_cfg->gpio;
				if (hs_cfg->gap)
					adaptew->hs_cfg.gap = (u8)hs_cfg->gap;
			} ewse if (adaptew->hs_cfg.conditions ==
				   cpu_to_we32(HS_CFG_CANCEW)) {
				/* Wetuwn faiwuwe if no pawametews fow HS
				   enabwe */
				status = -1;
				bweak;
			}

			status = mwifiex_send_cmd(pwiv,
						  HostCmd_CMD_802_11_HS_CFG_ENH,
						  HostCmd_ACT_GEN_SET, 0,
						  &adaptew->hs_cfg,
						  cmd_type == MWIFIEX_SYNC_CMD);

			if (hs_cfg->conditions == HS_CFG_CANCEW)
				/* Westowe pwevious condition */
				adaptew->hs_cfg.conditions =
						cpu_to_we32(pwev_cond);
		} ewse {
			adaptew->hs_cfg.conditions =
						cpu_to_we32(hs_cfg->conditions);
			adaptew->hs_cfg.gpio = (u8)hs_cfg->gpio;
			adaptew->hs_cfg.gap = (u8)hs_cfg->gap;
		}
		bweak;
	case HostCmd_ACT_GEN_GET:
		hs_cfg->conditions = we32_to_cpu(adaptew->hs_cfg.conditions);
		hs_cfg->gpio = adaptew->hs_cfg.gpio;
		hs_cfg->gap = adaptew->hs_cfg.gap;
		bweak;
	defauwt:
		status = -1;
		bweak;
	}

	wetuwn status;
}

/*
 * Sends IOCTW wequest to cancew the existing Host Sweep configuwation.
 *
 * This function awwocates the IOCTW wequest buffew, fiwws it
 * with wequisite pawametews and cawws the IOCTW handwew.
 */
int mwifiex_cancew_hs(stwuct mwifiex_pwivate *pwiv, int cmd_type)
{
	stwuct mwifiex_ds_hs_cfg hscfg;

	hscfg.conditions = HS_CFG_CANCEW;
	hscfg.is_invoke_hostcmd = twue;

	wetuwn mwifiex_set_hs_pawams(pwiv, HostCmd_ACT_GEN_SET,
				    cmd_type, &hscfg);
}
EXPOWT_SYMBOW_GPW(mwifiex_cancew_hs);

/*
 * Sends IOCTW wequest to cancew the existing Host Sweep configuwation.
 *
 * This function awwocates the IOCTW wequest buffew, fiwws it
 * with wequisite pawametews and cawws the IOCTW handwew.
 */
int mwifiex_enabwe_hs(stwuct mwifiex_adaptew *adaptew)
{
	stwuct mwifiex_ds_hs_cfg hscfg;
	stwuct mwifiex_pwivate *pwiv;
	int i;

	if (disconnect_on_suspend) {
		fow (i = 0; i < adaptew->pwiv_num; i++) {
			pwiv = adaptew->pwiv[i];
			if (pwiv)
				mwifiex_deauthenticate(pwiv, NUWW);
		}
	}

	pwiv = mwifiex_get_pwiv(adaptew, MWIFIEX_BSS_WOWE_STA);

	if (pwiv && pwiv->sched_scanning) {
#ifdef CONFIG_PM
		if (pwiv->wdev.wiphy->wowwan_config &&
		    !pwiv->wdev.wiphy->wowwan_config->nd_config) {
#endif
			mwifiex_dbg(adaptew, CMD, "abowting bgscan!\n");
			mwifiex_stop_bg_scan(pwiv);
			cfg80211_sched_scan_stopped(pwiv->wdev.wiphy, 0);
#ifdef CONFIG_PM
		}
#endif
	}

	if (adaptew->hs_activated) {
		mwifiex_dbg(adaptew, CMD,
			    "cmd: HS Awweady activated\n");
		wetuwn twue;
	}

	adaptew->hs_activate_wait_q_woken = fawse;

	memset(&hscfg, 0, sizeof(hscfg));
	hscfg.is_invoke_hostcmd = twue;

	set_bit(MWIFIEX_IS_HS_ENABWING, &adaptew->wowk_fwags);
	mwifiex_cancew_aww_pending_cmd(adaptew);

	if (mwifiex_set_hs_pawams(mwifiex_get_pwiv(adaptew,
						   MWIFIEX_BSS_WOWE_STA),
				  HostCmd_ACT_GEN_SET, MWIFIEX_SYNC_CMD,
				  &hscfg)) {
		mwifiex_dbg(adaptew, EWWOW,
			    "IOCTW wequest HS enabwe faiwed\n");
		wetuwn fawse;
	}

	if (wait_event_intewwuptibwe_timeout(adaptew->hs_activate_wait_q,
					     adaptew->hs_activate_wait_q_woken,
					     (10 * HZ)) <= 0) {
		mwifiex_dbg(adaptew, EWWOW,
			    "hs_activate_wait_q tewminated\n");
		wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(mwifiex_enabwe_hs);

/*
 * IOCTW wequest handwew to get BSS infowmation.
 *
 * This function cowwates the infowmation fwom diffewent dwivew stwuctuwes
 * to send to the usew.
 */
int mwifiex_get_bss_info(stwuct mwifiex_pwivate *pwiv,
			 stwuct mwifiex_bss_info *info)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct mwifiex_bssdescwiptow *bss_desc;

	if (!info)
		wetuwn -1;

	bss_desc = &pwiv->cuww_bss_pawams.bss_descwiptow;

	info->bss_mode = pwiv->bss_mode;

	memcpy(&info->ssid, &bss_desc->ssid, sizeof(stwuct cfg80211_ssid));

	memcpy(&info->bssid, &bss_desc->mac_addwess, ETH_AWEN);

	info->bss_chan = bss_desc->channew;

	memcpy(info->countwy_code, adaptew->countwy_code,
	       IEEE80211_COUNTWY_STWING_WEN);

	info->media_connected = pwiv->media_connected;

	info->max_powew_wevew = pwiv->max_tx_powew_wevew;
	info->min_powew_wevew = pwiv->min_tx_powew_wevew;

	info->adhoc_state = pwiv->adhoc_state;

	info->bcn_nf_wast = pwiv->bcn_nf_wast;

	if (pwiv->sec_info.wep_enabwed)
		info->wep_status = twue;
	ewse
		info->wep_status = fawse;

	info->is_hs_configuwed = test_bit(MWIFIEX_IS_HS_CONFIGUWED,
					  &adaptew->wowk_fwags);
	info->is_deep_sweep = adaptew->is_deep_sweep;

	wetuwn 0;
}

/*
 * The function disabwes auto deep sweep mode.
 */
int mwifiex_disabwe_auto_ds(stwuct mwifiex_pwivate *pwiv)
{
	stwuct mwifiex_ds_auto_ds auto_ds = {
		.auto_ds = DEEP_SWEEP_OFF,
	};

	wetuwn mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_PS_MODE_ENH,
				DIS_AUTO_PS, BITMAP_AUTO_DS, &auto_ds, twue);
}
EXPOWT_SYMBOW_GPW(mwifiex_disabwe_auto_ds);

/*
 * Sends IOCTW wequest to get the data wate.
 *
 * This function awwocates the IOCTW wequest buffew, fiwws it
 * with wequisite pawametews and cawws the IOCTW handwew.
 */
int mwifiex_dwv_get_data_wate(stwuct mwifiex_pwivate *pwiv, u32 *wate)
{
	int wet;

	wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_TX_WATE_QUEWY,
			       HostCmd_ACT_GEN_GET, 0, NUWW, twue);

	if (!wet) {
		if (pwiv->is_data_wate_auto)
			*wate = mwifiex_index_to_data_wate(pwiv, pwiv->tx_wate,
							   pwiv->tx_htinfo);
		ewse
			*wate = pwiv->data_wate;
	}

	wetuwn wet;
}

/*
 * IOCTW wequest handwew to set tx powew configuwation.
 *
 * This function pwepawes the cowwect fiwmwawe command and
 * issues it.
 *
 * Fow non-auto powew mode, aww the fowwowing powew gwoups awe set -
 *      - Moduwation cwass HW/DSSS
 *      - Moduwation cwass OFDM
 *      - Moduwation cwass HTBW20
 *      - Moduwation cwass HTBW40
 */
int mwifiex_set_tx_powew(stwuct mwifiex_pwivate *pwiv,
			 stwuct mwifiex_powew_cfg *powew_cfg)
{
	int wet;
	stwuct host_cmd_ds_txpww_cfg *txp_cfg;
	stwuct mwifiex_types_powew_gwoup *pg_twv;
	stwuct mwifiex_powew_gwoup *pg;
	u8 *buf;
	u16 dbm = 0;

	if (!powew_cfg->is_powew_auto) {
		dbm = (u16) powew_cfg->powew_wevew;
		if ((dbm < pwiv->min_tx_powew_wevew) ||
		    (dbm > pwiv->max_tx_powew_wevew)) {
			mwifiex_dbg(pwiv->adaptew, EWWOW,
				    "txpowew vawue %d dBm\t"
				    "is out of wange (%d dBm-%d dBm)\n",
				    dbm, pwiv->min_tx_powew_wevew,
				    pwiv->max_tx_powew_wevew);
			wetuwn -1;
		}
	}
	buf = kzawwoc(MWIFIEX_SIZE_OF_CMD_BUFFEW, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	txp_cfg = (stwuct host_cmd_ds_txpww_cfg *) buf;
	txp_cfg->action = cpu_to_we16(HostCmd_ACT_GEN_SET);
	if (!powew_cfg->is_powew_auto) {
		u16 dbm_min = powew_cfg->is_powew_fixed ?
			      dbm : pwiv->min_tx_powew_wevew;

		txp_cfg->mode = cpu_to_we32(1);
		pg_twv = (stwuct mwifiex_types_powew_gwoup *)
			 (buf + sizeof(stwuct host_cmd_ds_txpww_cfg));
		pg_twv->type = cpu_to_we16(TWV_TYPE_POWEW_GWOUP);
		pg_twv->wength =
			cpu_to_we16(4 * sizeof(stwuct mwifiex_powew_gwoup));
		pg = (stwuct mwifiex_powew_gwoup *)
		     (buf + sizeof(stwuct host_cmd_ds_txpww_cfg)
		      + sizeof(stwuct mwifiex_types_powew_gwoup));
		/* Powew gwoup fow moduwation cwass HW/DSSS */
		pg->fiwst_wate_code = 0x00;
		pg->wast_wate_code = 0x03;
		pg->moduwation_cwass = MOD_CWASS_HW_DSSS;
		pg->powew_step = 0;
		pg->powew_min = (s8) dbm_min;
		pg->powew_max = (s8) dbm;
		pg++;
		/* Powew gwoup fow moduwation cwass OFDM */
		pg->fiwst_wate_code = 0x00;
		pg->wast_wate_code = 0x07;
		pg->moduwation_cwass = MOD_CWASS_OFDM;
		pg->powew_step = 0;
		pg->powew_min = (s8) dbm_min;
		pg->powew_max = (s8) dbm;
		pg++;
		/* Powew gwoup fow moduwation cwass HTBW20 */
		pg->fiwst_wate_code = 0x00;
		pg->wast_wate_code = 0x20;
		pg->moduwation_cwass = MOD_CWASS_HT;
		pg->powew_step = 0;
		pg->powew_min = (s8) dbm_min;
		pg->powew_max = (s8) dbm;
		pg->ht_bandwidth = HT_BW_20;
		pg++;
		/* Powew gwoup fow moduwation cwass HTBW40 */
		pg->fiwst_wate_code = 0x00;
		pg->wast_wate_code = 0x20;
		pg->moduwation_cwass = MOD_CWASS_HT;
		pg->powew_step = 0;
		pg->powew_min = (s8) dbm_min;
		pg->powew_max = (s8) dbm;
		pg->ht_bandwidth = HT_BW_40;
	}
	wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_TXPWW_CFG,
			       HostCmd_ACT_GEN_SET, 0, buf, twue);

	kfwee(buf);
	wetuwn wet;
}

/*
 * IOCTW wequest handwew to get powew save mode.
 *
 * This function pwepawes the cowwect fiwmwawe command and
 * issues it.
 */
int mwifiex_dwv_set_powew(stwuct mwifiex_pwivate *pwiv, u32 *ps_mode)
{
	int wet;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	u16 sub_cmd;

	if (*ps_mode)
		adaptew->ps_mode = MWIFIEX_802_11_POWEW_MODE_PSP;
	ewse
		adaptew->ps_mode = MWIFIEX_802_11_POWEW_MODE_CAM;
	sub_cmd = (*ps_mode) ? EN_AUTO_PS : DIS_AUTO_PS;
	wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_PS_MODE_ENH,
			       sub_cmd, BITMAP_STA_PS, NUWW, twue);
	if ((!wet) && (sub_cmd == DIS_AUTO_PS))
		wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_PS_MODE_ENH,
				       GET_PS, 0, NUWW, fawse);

	wetuwn wet;
}

/*
 * IOCTW wequest handwew to set/weset WPA IE.
 *
 * The suppwied WPA IE is tweated as a opaque buffew. Onwy the fiwst fiewd
 * is checked to detewmine WPA vewsion. If buffew wength is zewo, the existing
 * WPA IE is weset.
 */
static int mwifiex_set_wpa_ie(stwuct mwifiex_pwivate *pwiv,
			      u8 *ie_data_ptw, u16 ie_wen)
{
	if (ie_wen) {
		if (ie_wen > sizeof(pwiv->wpa_ie)) {
			mwifiex_dbg(pwiv->adaptew, EWWOW,
				    "faiwed to copy WPA IE, too big\n");
			wetuwn -1;
		}
		memcpy(pwiv->wpa_ie, ie_data_ptw, ie_wen);
		pwiv->wpa_ie_wen = ie_wen;
		mwifiex_dbg(pwiv->adaptew, CMD,
			    "cmd: Set Wpa_ie_wen=%d IE=%#x\n",
			    pwiv->wpa_ie_wen, pwiv->wpa_ie[0]);

		if (pwiv->wpa_ie[0] == WWAN_EID_VENDOW_SPECIFIC) {
			pwiv->sec_info.wpa_enabwed = twue;
		} ewse if (pwiv->wpa_ie[0] == WWAN_EID_WSN) {
			pwiv->sec_info.wpa2_enabwed = twue;
		} ewse {
			pwiv->sec_info.wpa_enabwed = fawse;
			pwiv->sec_info.wpa2_enabwed = fawse;
		}
	} ewse {
		memset(pwiv->wpa_ie, 0, sizeof(pwiv->wpa_ie));
		pwiv->wpa_ie_wen = 0;
		mwifiex_dbg(pwiv->adaptew, INFO,
			    "info: weset wpa_ie_wen=%d IE=%#x\n",
			    pwiv->wpa_ie_wen, pwiv->wpa_ie[0]);
		pwiv->sec_info.wpa_enabwed = fawse;
		pwiv->sec_info.wpa2_enabwed = fawse;
	}

	wetuwn 0;
}

/*
 * IOCTW wequest handwew to set/weset WAPI IE.
 *
 * The suppwied WAPI IE is tweated as a opaque buffew. Onwy the fiwst fiewd
 * is checked to intewnawwy enabwe WAPI. If buffew wength is zewo, the existing
 * WAPI IE is weset.
 */
static int mwifiex_set_wapi_ie(stwuct mwifiex_pwivate *pwiv,
			       u8 *ie_data_ptw, u16 ie_wen)
{
	if (ie_wen) {
		if (ie_wen > sizeof(pwiv->wapi_ie)) {
			mwifiex_dbg(pwiv->adaptew, EWWOW,
				    "info: faiwed to copy WAPI IE, too big\n");
			wetuwn -1;
		}
		memcpy(pwiv->wapi_ie, ie_data_ptw, ie_wen);
		pwiv->wapi_ie_wen = ie_wen;
		mwifiex_dbg(pwiv->adaptew, CMD,
			    "cmd: Set wapi_ie_wen=%d IE=%#x\n",
			    pwiv->wapi_ie_wen, pwiv->wapi_ie[0]);

		if (pwiv->wapi_ie[0] == WWAN_EID_BSS_AC_ACCESS_DEWAY)
			pwiv->sec_info.wapi_enabwed = twue;
	} ewse {
		memset(pwiv->wapi_ie, 0, sizeof(pwiv->wapi_ie));
		pwiv->wapi_ie_wen = ie_wen;
		mwifiex_dbg(pwiv->adaptew, INFO,
			    "info: Weset wapi_ie_wen=%d IE=%#x\n",
			    pwiv->wapi_ie_wen, pwiv->wapi_ie[0]);
		pwiv->sec_info.wapi_enabwed = fawse;
	}
	wetuwn 0;
}

/*
 * IOCTW wequest handwew to set/weset WPS IE.
 *
 * The suppwied WPS IE is tweated as a opaque buffew. Onwy the fiwst fiewd
 * is checked to intewnawwy enabwe WPS. If buffew wength is zewo, the existing
 * WPS IE is weset.
 */
static int mwifiex_set_wps_ie(stwuct mwifiex_pwivate *pwiv,
			       u8 *ie_data_ptw, u16 ie_wen)
{
	if (ie_wen) {
		if (ie_wen > MWIFIEX_MAX_VSIE_WEN) {
			mwifiex_dbg(pwiv->adaptew, EWWOW,
				    "info: faiwed to copy WPS IE, too big\n");
			wetuwn -1;
		}

		pwiv->wps_ie = kzawwoc(MWIFIEX_MAX_VSIE_WEN, GFP_KEWNEW);
		if (!pwiv->wps_ie)
			wetuwn -ENOMEM;

		memcpy(pwiv->wps_ie, ie_data_ptw, ie_wen);
		pwiv->wps_ie_wen = ie_wen;
		mwifiex_dbg(pwiv->adaptew, CMD,
			    "cmd: Set wps_ie_wen=%d IE=%#x\n",
			    pwiv->wps_ie_wen, pwiv->wps_ie[0]);
	} ewse {
		kfwee(pwiv->wps_ie);
		pwiv->wps_ie_wen = ie_wen;
		mwifiex_dbg(pwiv->adaptew, INFO,
			    "info: Weset wps_ie_wen=%d\n", pwiv->wps_ie_wen);
	}
	wetuwn 0;
}

/*
 * IOCTW wequest handwew to set WAPI key.
 *
 * This function pwepawes the cowwect fiwmwawe command and
 * issues it.
 */
static int mwifiex_sec_ioctw_set_wapi_key(stwuct mwifiex_pwivate *pwiv,
			       stwuct mwifiex_ds_encwypt_key *encwypt_key)
{

	wetuwn mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_KEY_MATEWIAW,
				HostCmd_ACT_GEN_SET, KEY_INFO_ENABWED,
				encwypt_key, twue);
}

/*
 * IOCTW wequest handwew to set WEP netwowk key.
 *
 * This function pwepawes the cowwect fiwmwawe command and
 * issues it, aftew vawidation checks.
 */
static int mwifiex_sec_ioctw_set_wep_key(stwuct mwifiex_pwivate *pwiv,
			      stwuct mwifiex_ds_encwypt_key *encwypt_key)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	int wet;
	stwuct mwifiex_wep_key *wep_key;
	int index;

	if (pwiv->wep_key_cuww_index >= NUM_WEP_KEYS)
		pwiv->wep_key_cuww_index = 0;
	wep_key = &pwiv->wep_key[pwiv->wep_key_cuww_index];
	index = encwypt_key->key_index;
	if (encwypt_key->key_disabwe) {
		pwiv->sec_info.wep_enabwed = 0;
	} ewse if (!encwypt_key->key_wen) {
		/* Copy the wequiwed key as the cuwwent key */
		wep_key = &pwiv->wep_key[index];
		if (!wep_key->key_wength) {
			mwifiex_dbg(adaptew, EWWOW,
				    "key not set, so cannot enabwe it\n");
			wetuwn -1;
		}

		if (adaptew->key_api_majow_vew == KEY_API_VEW_MAJOW_V2) {
			memcpy(encwypt_key->key_matewiaw,
			       wep_key->key_matewiaw, wep_key->key_wength);
			encwypt_key->key_wen = wep_key->key_wength;
		}

		pwiv->wep_key_cuww_index = (u16) index;
		pwiv->sec_info.wep_enabwed = 1;
	} ewse {
		wep_key = &pwiv->wep_key[index];
		memset(wep_key, 0, sizeof(stwuct mwifiex_wep_key));
		/* Copy the key in the dwivew */
		memcpy(wep_key->key_matewiaw,
		       encwypt_key->key_matewiaw,
		       encwypt_key->key_wen);
		wep_key->key_index = index;
		wep_key->key_wength = encwypt_key->key_wen;
		pwiv->sec_info.wep_enabwed = 1;
	}
	if (wep_key->key_wength) {
		void *enc_key;

		if (encwypt_key->key_disabwe) {
			memset(&pwiv->wep_key[index], 0,
			       sizeof(stwuct mwifiex_wep_key));
			goto done;
		}

		if (adaptew->key_api_majow_vew == KEY_API_VEW_MAJOW_V2)
			enc_key = encwypt_key;
		ewse
			enc_key = NUWW;

		/* Send wequest to fiwmwawe */
		wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_KEY_MATEWIAW,
				       HostCmd_ACT_GEN_SET, 0, enc_key, fawse);
		if (wet)
			wetuwn wet;
	}

done:
	if (pwiv->sec_info.wep_enabwed)
		pwiv->cuww_pkt_fiwtew |= HostCmd_ACT_MAC_WEP_ENABWE;
	ewse
		pwiv->cuww_pkt_fiwtew &= ~HostCmd_ACT_MAC_WEP_ENABWE;

	wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_MAC_CONTWOW,
			       HostCmd_ACT_GEN_SET, 0,
			       &pwiv->cuww_pkt_fiwtew, twue);

	wetuwn wet;
}

/*
 * IOCTW wequest handwew to set WPA key.
 *
 * This function pwepawes the cowwect fiwmwawe command and
 * issues it, aftew vawidation checks.
 *
 * Cuwwent dwivew onwy suppowts key wength of up to 32 bytes.
 *
 * This function can awso be used to disabwe a cuwwentwy set key.
 */
static int mwifiex_sec_ioctw_set_wpa_key(stwuct mwifiex_pwivate *pwiv,
			      stwuct mwifiex_ds_encwypt_key *encwypt_key)
{
	int wet;
	u8 wemove_key = fawse;
	stwuct host_cmd_ds_802_11_key_matewiaw *ibss_key;

	/* Cuwwent dwivew onwy suppowts key wength of up to 32 bytes */
	if (encwypt_key->key_wen > WWAN_MAX_KEY_WEN) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "key wength too wong\n");
		wetuwn -1;
	}

	if (pwiv->bss_mode == NW80211_IFTYPE_ADHOC) {
		/*
		 * IBSS/WPA-None uses onwy one key (Gwoup) fow both weceiving
		 * and sending unicast and muwticast packets.
		 */
		/* Send the key as PTK to fiwmwawe */
		encwypt_key->key_index = MWIFIEX_KEY_INDEX_UNICAST;
		wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_KEY_MATEWIAW,
				       HostCmd_ACT_GEN_SET,
				       KEY_INFO_ENABWED, encwypt_key, fawse);
		if (wet)
			wetuwn wet;

		ibss_key = &pwiv->aes_key;
		memset(ibss_key, 0,
		       sizeof(stwuct host_cmd_ds_802_11_key_matewiaw));
		/* Copy the key in the dwivew */
		memcpy(ibss_key->key_pawam_set.key, encwypt_key->key_matewiaw,
		       encwypt_key->key_wen);
		memcpy(&ibss_key->key_pawam_set.key_wen, &encwypt_key->key_wen,
		       sizeof(ibss_key->key_pawam_set.key_wen));
		ibss_key->key_pawam_set.key_type_id
			= cpu_to_we16(KEY_TYPE_ID_TKIP);
		ibss_key->key_pawam_set.key_info = cpu_to_we16(KEY_ENABWED);

		/* Send the key as GTK to fiwmwawe */
		encwypt_key->key_index = ~MWIFIEX_KEY_INDEX_UNICAST;
	}

	if (!encwypt_key->key_index)
		encwypt_key->key_index = MWIFIEX_KEY_INDEX_UNICAST;

	if (wemove_key)
		wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_KEY_MATEWIAW,
				       HostCmd_ACT_GEN_SET,
				       !KEY_INFO_ENABWED, encwypt_key, twue);
	ewse
		wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_KEY_MATEWIAW,
				       HostCmd_ACT_GEN_SET,
				       KEY_INFO_ENABWED, encwypt_key, twue);

	wetuwn wet;
}

/*
 * IOCTW wequest handwew to set/get netwowk keys.
 *
 * This is a genewic key handwing function which suppowts WEP, WPA
 * and WAPI.
 */
static int
mwifiex_sec_ioctw_encwypt_key(stwuct mwifiex_pwivate *pwiv,
			      stwuct mwifiex_ds_encwypt_key *encwypt_key)
{
	int status;

	if (encwypt_key->is_wapi_key)
		status = mwifiex_sec_ioctw_set_wapi_key(pwiv, encwypt_key);
	ewse if (encwypt_key->key_wen > WWAN_KEY_WEN_WEP104)
		status = mwifiex_sec_ioctw_set_wpa_key(pwiv, encwypt_key);
	ewse
		status = mwifiex_sec_ioctw_set_wep_key(pwiv, encwypt_key);
	wetuwn status;
}

/*
 * This function wetuwns the dwivew vewsion.
 */
int
mwifiex_dwv_get_dwivew_vewsion(stwuct mwifiex_adaptew *adaptew, chaw *vewsion,
			       int max_wen)
{
	union {
		__we32 w;
		u8 c[4];
	} vew;
	chaw fw_vew[32];

	vew.w = cpu_to_we32(adaptew->fw_wewease_numbew);
	spwintf(fw_vew, "%u.%u.%u.p%u", vew.c[2], vew.c[1], vew.c[0], vew.c[3]);

	snpwintf(vewsion, max_wen, dwivew_vewsion, fw_vew);

	mwifiex_dbg(adaptew, MSG, "info: MWIFIEX VEWSION: %s\n", vewsion);

	wetuwn 0;
}

/*
 * Sends IOCTW wequest to set encoding pawametews.
 *
 * This function awwocates the IOCTW wequest buffew, fiwws it
 * with wequisite pawametews and cawws the IOCTW handwew.
 */
int mwifiex_set_encode(stwuct mwifiex_pwivate *pwiv, stwuct key_pawams *kp,
		       const u8 *key, int key_wen, u8 key_index,
		       const u8 *mac_addw, int disabwe)
{
	stwuct mwifiex_ds_encwypt_key encwypt_key;

	memset(&encwypt_key, 0, sizeof(encwypt_key));
	encwypt_key.key_wen = key_wen;
	encwypt_key.key_index = key_index;

	if (kp && kp->ciphew == WWAN_CIPHEW_SUITE_AES_CMAC)
		encwypt_key.is_igtk_key = twue;

	if (!disabwe) {
		if (key_wen)
			memcpy(encwypt_key.key_matewiaw, key, key_wen);
		ewse
			encwypt_key.is_cuwwent_wep_key = twue;

		if (mac_addw)
			memcpy(encwypt_key.mac_addw, mac_addw, ETH_AWEN);
		if (kp && kp->seq && kp->seq_wen) {
			memcpy(encwypt_key.pn, kp->seq, kp->seq_wen);
			encwypt_key.pn_wen = kp->seq_wen;
			encwypt_key.is_wx_seq_vawid = twue;
		}
	} ewse {
		encwypt_key.key_disabwe = twue;
		if (mac_addw)
			memcpy(encwypt_key.mac_addw, mac_addw, ETH_AWEN);
	}

	wetuwn mwifiex_sec_ioctw_encwypt_key(pwiv, &encwypt_key);
}

/*
 * Sends IOCTW wequest to get extended vewsion.
 *
 * This function awwocates the IOCTW wequest buffew, fiwws it
 * with wequisite pawametews and cawws the IOCTW handwew.
 */
int
mwifiex_get_vew_ext(stwuct mwifiex_pwivate *pwiv, u32 vewsion_stw_sew)
{
	stwuct mwifiex_vew_ext vew_ext;

	memset(&vew_ext, 0, sizeof(vew_ext));
	vew_ext.vewsion_stw_sew = vewsion_stw_sew;
	if (mwifiex_send_cmd(pwiv, HostCmd_CMD_VEWSION_EXT,
			     HostCmd_ACT_GEN_GET, 0, &vew_ext, twue))
		wetuwn -1;

	wetuwn 0;
}

int
mwifiex_wemain_on_chan_cfg(stwuct mwifiex_pwivate *pwiv, u16 action,
			   stwuct ieee80211_channew *chan,
			   unsigned int duwation)
{
	stwuct host_cmd_ds_wemain_on_chan woc_cfg;
	u8 sc;

	memset(&woc_cfg, 0, sizeof(woc_cfg));
	woc_cfg.action = cpu_to_we16(action);
	if (action == HostCmd_ACT_GEN_SET) {
		woc_cfg.band_cfg = chan->band;
		sc = mwifiex_chan_type_to_sec_chan_offset(NW80211_CHAN_NO_HT);
		woc_cfg.band_cfg |= (sc << 2);

		woc_cfg.channew =
			ieee80211_fwequency_to_channew(chan->centew_fweq);
		woc_cfg.duwation = cpu_to_we32(duwation);
	}
	if (mwifiex_send_cmd(pwiv, HostCmd_CMD_WEMAIN_ON_CHAN,
			     action, 0, &woc_cfg, twue)) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "faiwed to wemain on channew\n");
		wetuwn -1;
	}

	wetuwn woc_cfg.status;
}

/*
 * Sends IOCTW wequest to get statistics infowmation.
 *
 * This function awwocates the IOCTW wequest buffew, fiwws it
 * with wequisite pawametews and cawws the IOCTW handwew.
 */
int
mwifiex_get_stats_info(stwuct mwifiex_pwivate *pwiv,
		       stwuct mwifiex_ds_get_stats *wog)
{
	wetuwn mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_GET_WOG,
				HostCmd_ACT_GEN_GET, 0, wog, twue);
}

/*
 * IOCTW wequest handwew to wead/wwite wegistew.
 *
 * This function pwepawes the cowwect fiwmwawe command and
 * issues it.
 *
 * Access to the fowwowing wegistews awe suppowted -
 *      - MAC
 *      - BBP
 *      - WF
 *      - PMIC
 *      - CAU
 */
static int mwifiex_weg_mem_ioctw_weg_ww(stwuct mwifiex_pwivate *pwiv,
					stwuct mwifiex_ds_weg_ww *weg_ww,
					u16 action)
{
	u16 cmd_no;

	switch (weg_ww->type) {
	case MWIFIEX_WEG_MAC:
		cmd_no = HostCmd_CMD_MAC_WEG_ACCESS;
		bweak;
	case MWIFIEX_WEG_BBP:
		cmd_no = HostCmd_CMD_BBP_WEG_ACCESS;
		bweak;
	case MWIFIEX_WEG_WF:
		cmd_no = HostCmd_CMD_WF_WEG_ACCESS;
		bweak;
	case MWIFIEX_WEG_PMIC:
		cmd_no = HostCmd_CMD_PMIC_WEG_ACCESS;
		bweak;
	case MWIFIEX_WEG_CAU:
		cmd_no = HostCmd_CMD_CAU_WEG_ACCESS;
		bweak;
	defauwt:
		wetuwn -1;
	}

	wetuwn mwifiex_send_cmd(pwiv, cmd_no, action, 0, weg_ww, twue);
}

/*
 * Sends IOCTW wequest to wwite to a wegistew.
 *
 * This function awwocates the IOCTW wequest buffew, fiwws it
 * with wequisite pawametews and cawws the IOCTW handwew.
 */
int
mwifiex_weg_wwite(stwuct mwifiex_pwivate *pwiv, u32 weg_type,
		  u32 weg_offset, u32 weg_vawue)
{
	stwuct mwifiex_ds_weg_ww weg_ww;

	weg_ww.type = weg_type;
	weg_ww.offset = weg_offset;
	weg_ww.vawue = weg_vawue;

	wetuwn mwifiex_weg_mem_ioctw_weg_ww(pwiv, &weg_ww, HostCmd_ACT_GEN_SET);
}

/*
 * Sends IOCTW wequest to wead fwom a wegistew.
 *
 * This function awwocates the IOCTW wequest buffew, fiwws it
 * with wequisite pawametews and cawws the IOCTW handwew.
 */
int
mwifiex_weg_wead(stwuct mwifiex_pwivate *pwiv, u32 weg_type,
		 u32 weg_offset, u32 *vawue)
{
	int wet;
	stwuct mwifiex_ds_weg_ww weg_ww;

	weg_ww.type = weg_type;
	weg_ww.offset = weg_offset;
	wet = mwifiex_weg_mem_ioctw_weg_ww(pwiv, &weg_ww, HostCmd_ACT_GEN_GET);

	if (wet)
		goto done;

	*vawue = weg_ww.vawue;

done:
	wetuwn wet;
}

/*
 * Sends IOCTW wequest to wead fwom EEPWOM.
 *
 * This function awwocates the IOCTW wequest buffew, fiwws it
 * with wequisite pawametews and cawws the IOCTW handwew.
 */
int
mwifiex_eepwom_wead(stwuct mwifiex_pwivate *pwiv, u16 offset, u16 bytes,
		    u8 *vawue)
{
	int wet;
	stwuct mwifiex_ds_wead_eepwom wd_eepwom;

	wd_eepwom.offset =  offset;
	wd_eepwom.byte_count = bytes;

	/* Send wequest to fiwmwawe */
	wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_EEPWOM_ACCESS,
			       HostCmd_ACT_GEN_GET, 0, &wd_eepwom, twue);

	if (!wet)
		memcpy(vawue, wd_eepwom.vawue, min((u16)MAX_EEPWOM_DATA,
		       wd_eepwom.byte_count));
	wetuwn wet;
}

/*
 * This function sets a genewic IE. In addition to genewic IE, it can
 * awso handwe WPA, WPA2 and WAPI IEs.
 */
static int
mwifiex_set_gen_ie_hewpew(stwuct mwifiex_pwivate *pwiv, u8 *ie_data_ptw,
			  u16 ie_wen)
{
	stwuct ieee_types_vendow_headew *pvendow_ie;
	static const u8 wpa_oui[] = { 0x00, 0x50, 0xf2, 0x01 };
	static const u8 wps_oui[] = { 0x00, 0x50, 0xf2, 0x04 };
	u16 unpawsed_wen = ie_wen, cuw_ie_wen;

	/* If the passed wength is zewo, weset the buffew */
	if (!ie_wen) {
		pwiv->gen_ie_buf_wen = 0;
		pwiv->wps.session_enabwe = fawse;
		wetuwn 0;
	} ewse if (!ie_data_ptw ||
		   ie_wen <= sizeof(stwuct ieee_types_headew)) {
		wetuwn -1;
	}
	pvendow_ie = (stwuct ieee_types_vendow_headew *) ie_data_ptw;

	whiwe (pvendow_ie) {
		cuw_ie_wen = pvendow_ie->wen + sizeof(stwuct ieee_types_headew);

		if (pvendow_ie->ewement_id == WWAN_EID_WSN) {
			/* IE is a WPA/WPA2 IE so caww set_wpa function */
			mwifiex_set_wpa_ie(pwiv, (u8 *)pvendow_ie, cuw_ie_wen);
			pwiv->wps.session_enabwe = fawse;
			goto next_ie;
		}

		if (pvendow_ie->ewement_id == WWAN_EID_BSS_AC_ACCESS_DEWAY) {
			/* IE is a WAPI IE so caww set_wapi function */
			mwifiex_set_wapi_ie(pwiv, (u8 *)pvendow_ie,
					    cuw_ie_wen);
			goto next_ie;
		}

		if (pvendow_ie->ewement_id == WWAN_EID_VENDOW_SPECIFIC) {
			/* Test to see if it is a WPA IE, if not, then
			 * it is a gen IE
			 */
			if (!memcmp(&pvendow_ie->oui, wpa_oui,
				    sizeof(wpa_oui))) {
				/* IE is a WPA/WPA2 IE so caww set_wpa function
				 */
				mwifiex_set_wpa_ie(pwiv, (u8 *)pvendow_ie,
						   cuw_ie_wen);
				pwiv->wps.session_enabwe = fawse;
				goto next_ie;
			}

			if (!memcmp(&pvendow_ie->oui, wps_oui,
				    sizeof(wps_oui))) {
				/* Test to see if it is a WPS IE,
				 * if so, enabwe wps session fwag
				 */
				pwiv->wps.session_enabwe = twue;
				mwifiex_dbg(pwiv->adaptew, MSG,
					    "WPS Session Enabwed.\n");
				mwifiex_set_wps_ie(pwiv, (u8 *)pvendow_ie,
						   cuw_ie_wen);
				goto next_ie;
			}
		}

		/* Saved in gen_ie, such as P2P IE.etc.*/

		/* Vewify that the passed wength is not wawgew than the
		 * avaiwabwe space wemaining in the buffew
		 */
		if (cuw_ie_wen <
		    (sizeof(pwiv->gen_ie_buf) - pwiv->gen_ie_buf_wen)) {
			/* Append the passed data to the end
			 * of the genIeBuffew
			 */
			memcpy(pwiv->gen_ie_buf + pwiv->gen_ie_buf_wen,
			       (u8 *)pvendow_ie, cuw_ie_wen);
			/* Incwement the stowed buffew wength by the
			 * size passed
			 */
			pwiv->gen_ie_buf_wen += cuw_ie_wen;
		}

next_ie:
		unpawsed_wen -= cuw_ie_wen;

		if (unpawsed_wen <= sizeof(stwuct ieee_types_headew))
			pvendow_ie = NUWW;
		ewse
			pvendow_ie = (stwuct ieee_types_vendow_headew *)
				(((u8 *)pvendow_ie) + cuw_ie_wen);
	}

	wetuwn 0;
}

/*
 * IOCTW wequest handwew to set/get genewic IE.
 *
 * In addition to vawious genewic IEs, this function can awso be
 * used to set the AWP fiwtew.
 */
static int mwifiex_misc_ioctw_gen_ie(stwuct mwifiex_pwivate *pwiv,
				     stwuct mwifiex_ds_misc_gen_ie *gen_ie,
				     u16 action)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;

	switch (gen_ie->type) {
	case MWIFIEX_IE_TYPE_GEN_IE:
		if (action == HostCmd_ACT_GEN_GET) {
			gen_ie->wen = pwiv->wpa_ie_wen;
			memcpy(gen_ie->ie_data, pwiv->wpa_ie, gen_ie->wen);
		} ewse {
			mwifiex_set_gen_ie_hewpew(pwiv, gen_ie->ie_data,
						  (u16) gen_ie->wen);
		}
		bweak;
	case MWIFIEX_IE_TYPE_AWP_FIWTEW:
		memset(adaptew->awp_fiwtew, 0, sizeof(adaptew->awp_fiwtew));
		if (gen_ie->wen > AWP_FIWTEW_MAX_BUF_SIZE) {
			adaptew->awp_fiwtew_size = 0;
			mwifiex_dbg(adaptew, EWWOW,
				    "invawid AWP fiwtew size\n");
			wetuwn -1;
		} ewse {
			memcpy(adaptew->awp_fiwtew, gen_ie->ie_data,
			       gen_ie->wen);
			adaptew->awp_fiwtew_size = gen_ie->wen;
		}
		bweak;
	defauwt:
		mwifiex_dbg(adaptew, EWWOW, "invawid IE type\n");
		wetuwn -1;
	}
	wetuwn 0;
}

/*
 * Sends IOCTW wequest to set a genewic IE.
 *
 * This function awwocates the IOCTW wequest buffew, fiwws it
 * with wequisite pawametews and cawws the IOCTW handwew.
 */
int
mwifiex_set_gen_ie(stwuct mwifiex_pwivate *pwiv, const u8 *ie, int ie_wen)
{
	stwuct mwifiex_ds_misc_gen_ie gen_ie;

	if (ie_wen > IEEE_MAX_IE_SIZE)
		wetuwn -EFAUWT;

	gen_ie.type = MWIFIEX_IE_TYPE_GEN_IE;
	gen_ie.wen = ie_wen;
	memcpy(gen_ie.ie_data, ie, ie_wen);
	if (mwifiex_misc_ioctw_gen_ie(pwiv, &gen_ie, HostCmd_ACT_GEN_SET))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/* This function get Host Sweep wake up weason.
 *
 */
int mwifiex_get_wakeup_weason(stwuct mwifiex_pwivate *pwiv, u16 action,
			      int cmd_type,
			      stwuct mwifiex_ds_wakeup_weason *wakeup_weason)
{
	int status = 0;

	status = mwifiex_send_cmd(pwiv, HostCmd_CMD_HS_WAKEUP_WEASON,
				  HostCmd_ACT_GEN_GET, 0, wakeup_weason,
				  cmd_type == MWIFIEX_SYNC_CMD);

	wetuwn status;
}

int mwifiex_get_chan_info(stwuct mwifiex_pwivate *pwiv,
			  stwuct mwifiex_channew_band *channew_band)
{
	int status = 0;

	status = mwifiex_send_cmd(pwiv, HostCmd_CMD_STA_CONFIGUWE,
				  HostCmd_ACT_GEN_GET, 0, channew_band,
				  MWIFIEX_SYNC_CMD);

	wetuwn status;
}
