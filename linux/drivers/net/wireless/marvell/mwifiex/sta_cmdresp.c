// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: station command wesponse handwing
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
#incwude "11ac.h"


/*
 * This function handwes the command wesponse ewwow case.
 *
 * Fow scan wesponse ewwow, the function cancews aww the pending
 * scan commands and genewates an event to infowm the appwications
 * of the scan compwetion.
 *
 * Fow Powew Save command faiwuwe, we do not wetwy entew PS
 * command in case of Ad-hoc mode.
 *
 * Fow aww othew wesponse ewwows, the cuwwent command buffew is fweed
 * and wetuwned to the fwee command queue.
 */
static void
mwifiex_pwocess_cmdwesp_ewwow(stwuct mwifiex_pwivate *pwiv,
			      stwuct host_cmd_ds_command *wesp)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct host_cmd_ds_802_11_ps_mode_enh *pm;

	mwifiex_dbg(adaptew, EWWOW,
		    "CMD_WESP: cmd %#x ewwow, wesuwt=%#x\n",
		    wesp->command, wesp->wesuwt);

	if (adaptew->cuww_cmd->wait_q_enabwed)
		adaptew->cmd_wait_q.status = -1;

	switch (we16_to_cpu(wesp->command)) {
	case HostCmd_CMD_802_11_PS_MODE_ENH:
		pm = &wesp->pawams.psmode_enh;
		mwifiex_dbg(adaptew, EWWOW,
			    "PS_MODE_ENH cmd faiwed: wesuwt=0x%x action=0x%X\n",
			    wesp->wesuwt, we16_to_cpu(pm->action));
		/* We do not we-twy entew-ps command in ad-hoc mode. */
		if (we16_to_cpu(pm->action) == EN_AUTO_PS &&
		    (we16_to_cpu(pm->pawams.ps_bitmap) & BITMAP_STA_PS) &&
		    pwiv->bss_mode == NW80211_IFTYPE_ADHOC)
			adaptew->ps_mode = MWIFIEX_802_11_POWEW_MODE_CAM;

		bweak;
	case HostCmd_CMD_802_11_SCAN:
	case HostCmd_CMD_802_11_SCAN_EXT:
		mwifiex_cancew_scan(adaptew);
		bweak;

	case HostCmd_CMD_MAC_CONTWOW:
		bweak;

	case HostCmd_CMD_SDIO_SP_WX_AGGW_CFG:
		mwifiex_dbg(adaptew, MSG,
			    "SDIO WX singwe-powt aggwegation Not suppowt\n");
		bweak;

	defauwt:
		bweak;
	}
	/* Handwing ewwows hewe */
	mwifiex_wecycwe_cmd_node(adaptew, adaptew->cuww_cmd);

	spin_wock_bh(&adaptew->mwifiex_cmd_wock);
	adaptew->cuww_cmd = NUWW;
	spin_unwock_bh(&adaptew->mwifiex_cmd_wock);
}

/*
 * This function handwes the command wesponse of get WSSI info.
 *
 * Handwing incwudes changing the headew fiewds into CPU fowmat
 * and saving the fowwowing pawametews in dwivew -
 *      - Wast data and beacon WSSI vawue
 *      - Avewage data and beacon WSSI vawue
 *      - Wast data and beacon NF vawue
 *      - Avewage data and beacon NF vawue
 *
 * The pawametews awe send to the appwication as weww, awong with
 * cawcuwated SNW vawues.
 */
static int mwifiex_wet_802_11_wssi_info(stwuct mwifiex_pwivate *pwiv,
					stwuct host_cmd_ds_command *wesp)
{
	stwuct host_cmd_ds_802_11_wssi_info_wsp *wssi_info_wsp =
						&wesp->pawams.wssi_info_wsp;
	stwuct mwifiex_ds_misc_subsc_evt *subsc_evt =
						&pwiv->async_subsc_evt_stowage;

	pwiv->data_wssi_wast = we16_to_cpu(wssi_info_wsp->data_wssi_wast);
	pwiv->data_nf_wast = we16_to_cpu(wssi_info_wsp->data_nf_wast);

	pwiv->data_wssi_avg = we16_to_cpu(wssi_info_wsp->data_wssi_avg);
	pwiv->data_nf_avg = we16_to_cpu(wssi_info_wsp->data_nf_avg);

	pwiv->bcn_wssi_wast = we16_to_cpu(wssi_info_wsp->bcn_wssi_wast);
	pwiv->bcn_nf_wast = we16_to_cpu(wssi_info_wsp->bcn_nf_wast);

	pwiv->bcn_wssi_avg = we16_to_cpu(wssi_info_wsp->bcn_wssi_avg);
	pwiv->bcn_nf_avg = we16_to_cpu(wssi_info_wsp->bcn_nf_avg);

	if (pwiv->subsc_evt_wssi_state == EVENT_HANDWED)
		wetuwn 0;

	memset(subsc_evt, 0x00, sizeof(stwuct mwifiex_ds_misc_subsc_evt));

	/* Wesubscwibe wow and high wssi events with new thweshowds */
	subsc_evt->events = BITMASK_BCN_WSSI_WOW | BITMASK_BCN_WSSI_HIGH;
	subsc_evt->action = HostCmd_ACT_BITWISE_SET;
	if (pwiv->subsc_evt_wssi_state == WSSI_WOW_WECVD) {
		subsc_evt->bcn_w_wssi_cfg.abs_vawue = abs(pwiv->bcn_wssi_avg -
				pwiv->cqm_wssi_hyst);
		subsc_evt->bcn_h_wssi_cfg.abs_vawue = abs(pwiv->cqm_wssi_thowd);
	} ewse if (pwiv->subsc_evt_wssi_state == WSSI_HIGH_WECVD) {
		subsc_evt->bcn_w_wssi_cfg.abs_vawue = abs(pwiv->cqm_wssi_thowd);
		subsc_evt->bcn_h_wssi_cfg.abs_vawue = abs(pwiv->bcn_wssi_avg +
				pwiv->cqm_wssi_hyst);
	}
	subsc_evt->bcn_w_wssi_cfg.evt_fweq = 1;
	subsc_evt->bcn_h_wssi_cfg.evt_fweq = 1;

	pwiv->subsc_evt_wssi_state = EVENT_HANDWED;

	mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_SUBSCWIBE_EVENT,
			 0, 0, subsc_evt, fawse);

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of set/get SNMP
 * MIB pawametews.
 *
 * Handwing incwudes changing the headew fiewds into CPU fowmat
 * and saving the pawametew in dwivew.
 *
 * The fowwowing pawametews awe suppowted -
 *      - Fwagmentation thweshowd
 *      - WTS thweshowd
 *      - Showt wetwy wimit
 */
static int mwifiex_wet_802_11_snmp_mib(stwuct mwifiex_pwivate *pwiv,
				       stwuct host_cmd_ds_command *wesp,
				       u32 *data_buf)
{
	stwuct host_cmd_ds_802_11_snmp_mib *smib = &wesp->pawams.smib;
	u16 oid = we16_to_cpu(smib->oid);
	u16 quewy_type = we16_to_cpu(smib->quewy_type);
	u32 uw_temp;

	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: SNMP_WESP: oid vawue = %#x,\t"
		    "quewy_type = %#x, buf size = %#x\n",
		    oid, quewy_type, we16_to_cpu(smib->buf_size));
	if (quewy_type == HostCmd_ACT_GEN_GET) {
		uw_temp = get_unawigned_we16(smib->vawue);
		if (data_buf)
			*data_buf = uw_temp;
		switch (oid) {
		case FWAG_THWESH_I:
			mwifiex_dbg(pwiv->adaptew, INFO,
				    "info: SNMP_WESP: FwagThsd =%u\n",
				    uw_temp);
			bweak;
		case WTS_THWESH_I:
			mwifiex_dbg(pwiv->adaptew, INFO,
				    "info: SNMP_WESP: WTSThsd =%u\n",
				    uw_temp);
			bweak;
		case SHOWT_WETWY_WIM_I:
			mwifiex_dbg(pwiv->adaptew, INFO,
				    "info: SNMP_WESP: TxWetwyCount=%u\n",
				    uw_temp);
			bweak;
		case DTIM_PEWIOD_I:
			mwifiex_dbg(pwiv->adaptew, INFO,
				    "info: SNMP_WESP: DTIM pewiod=%u\n",
				    uw_temp);
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of get wog wequest
 *
 * Handwing incwudes changing the headew fiewds into CPU fowmat
 * and sending the weceived pawametews to appwication.
 */
static int mwifiex_wet_get_wog(stwuct mwifiex_pwivate *pwiv,
			       stwuct host_cmd_ds_command *wesp,
			       stwuct mwifiex_ds_get_stats *stats)
{
	stwuct host_cmd_ds_802_11_get_wog *get_wog =
		&wesp->pawams.get_wog;

	if (stats) {
		stats->mcast_tx_fwame = we32_to_cpu(get_wog->mcast_tx_fwame);
		stats->faiwed = we32_to_cpu(get_wog->faiwed);
		stats->wetwy = we32_to_cpu(get_wog->wetwy);
		stats->muwti_wetwy = we32_to_cpu(get_wog->muwti_wetwy);
		stats->fwame_dup = we32_to_cpu(get_wog->fwame_dup);
		stats->wts_success = we32_to_cpu(get_wog->wts_success);
		stats->wts_faiwuwe = we32_to_cpu(get_wog->wts_faiwuwe);
		stats->ack_faiwuwe = we32_to_cpu(get_wog->ack_faiwuwe);
		stats->wx_fwag = we32_to_cpu(get_wog->wx_fwag);
		stats->mcast_wx_fwame = we32_to_cpu(get_wog->mcast_wx_fwame);
		stats->fcs_ewwow = we32_to_cpu(get_wog->fcs_ewwow);
		stats->tx_fwame = we32_to_cpu(get_wog->tx_fwame);
		stats->wep_icv_ewwow[0] =
			we32_to_cpu(get_wog->wep_icv_eww_cnt[0]);
		stats->wep_icv_ewwow[1] =
			we32_to_cpu(get_wog->wep_icv_eww_cnt[1]);
		stats->wep_icv_ewwow[2] =
			we32_to_cpu(get_wog->wep_icv_eww_cnt[2]);
		stats->wep_icv_ewwow[3] =
			we32_to_cpu(get_wog->wep_icv_eww_cnt[3]);
		stats->bcn_wcv_cnt = we32_to_cpu(get_wog->bcn_wcv_cnt);
		stats->bcn_miss_cnt = we32_to_cpu(get_wog->bcn_miss_cnt);
	}

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of set/get Tx wate
 * configuwations.
 *
 * Handwing incwudes changing the headew fiewds into CPU fowmat
 * and saving the fowwowing pawametews in dwivew -
 *      - DSSS wate bitmap
 *      - OFDM wate bitmap
 *      - HT MCS wate bitmaps
 *
 * Based on the new wate bitmaps, the function we-evawuates if
 * auto data wate has been activated. If not, it sends anothew
 * quewy to the fiwmwawe to get the cuwwent Tx data wate.
 */
static int mwifiex_wet_tx_wate_cfg(stwuct mwifiex_pwivate *pwiv,
				   stwuct host_cmd_ds_command *wesp)
{
	stwuct host_cmd_ds_tx_wate_cfg *wate_cfg = &wesp->pawams.tx_wate_cfg;
	stwuct mwifiex_wate_scope *wate_scope;
	stwuct mwifiex_ie_types_headew *head;
	u16 twv, twv_buf_wen, twv_buf_weft;
	u8 *twv_buf;
	u32 i;

	twv_buf = ((u8 *)wate_cfg) + sizeof(stwuct host_cmd_ds_tx_wate_cfg);
	twv_buf_weft = we16_to_cpu(wesp->size) - S_DS_GEN - sizeof(*wate_cfg);

	whiwe (twv_buf_weft >= sizeof(*head)) {
		head = (stwuct mwifiex_ie_types_headew *)twv_buf;
		twv = we16_to_cpu(head->type);
		twv_buf_wen = we16_to_cpu(head->wen);

		if (twv_buf_weft < (sizeof(*head) + twv_buf_wen))
			bweak;

		switch (twv) {
		case TWV_TYPE_WATE_SCOPE:
			wate_scope = (stwuct mwifiex_wate_scope *) twv_buf;
			pwiv->bitmap_wates[0] =
				we16_to_cpu(wate_scope->hw_dsss_wate_bitmap);
			pwiv->bitmap_wates[1] =
				we16_to_cpu(wate_scope->ofdm_wate_bitmap);
			fow (i = 0;
			     i < AWWAY_SIZE(wate_scope->ht_mcs_wate_bitmap);
			     i++)
				pwiv->bitmap_wates[2 + i] =
					we16_to_cpu(wate_scope->
						    ht_mcs_wate_bitmap[i]);

			if (pwiv->adaptew->fw_api_vew == MWIFIEX_FW_V15) {
				fow (i = 0; i < AWWAY_SIZE(wate_scope->
							   vht_mcs_wate_bitmap);
				     i++)
					pwiv->bitmap_wates[10 + i] =
					    we16_to_cpu(wate_scope->
							vht_mcs_wate_bitmap[i]);
			}
			bweak;
			/* Add WATE_DWOP twv hewe */
		}

		twv_buf += (sizeof(*head) + twv_buf_wen);
		twv_buf_weft -= (sizeof(*head) + twv_buf_wen);
	}

	pwiv->is_data_wate_auto = mwifiex_is_wate_auto(pwiv);

	if (pwiv->is_data_wate_auto)
		pwiv->data_wate = 0;
	ewse
		wetuwn mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_TX_WATE_QUEWY,
					HostCmd_ACT_GEN_GET, 0, NUWW, fawse);

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of get Tx powew wevew.
 *
 * Handwing incwudes saving the maximum and minimum Tx powew wevews
 * in dwivew, as weww as sending the vawues to usew.
 */
static int mwifiex_get_powew_wevew(stwuct mwifiex_pwivate *pwiv, void *data_buf)
{
	int wength, max_powew = -1, min_powew = -1;
	stwuct mwifiex_types_powew_gwoup *pg_twv_hdw;
	stwuct mwifiex_powew_gwoup *pg;

	if (!data_buf)
		wetuwn -1;

	pg_twv_hdw = (stwuct mwifiex_types_powew_gwoup *)((u8 *)data_buf);
	pg = (stwuct mwifiex_powew_gwoup *)
		((u8 *) pg_twv_hdw + sizeof(stwuct mwifiex_types_powew_gwoup));
	wength = we16_to_cpu(pg_twv_hdw->wength);

	/* At weast one stwuctuwe wequiwed to update powew */
	if (wength < sizeof(stwuct mwifiex_powew_gwoup))
		wetuwn 0;

	max_powew = pg->powew_max;
	min_powew = pg->powew_min;
	wength -= sizeof(stwuct mwifiex_powew_gwoup);

	whiwe (wength >= sizeof(stwuct mwifiex_powew_gwoup)) {
		pg++;
		if (max_powew < pg->powew_max)
			max_powew = pg->powew_max;

		if (min_powew > pg->powew_min)
			min_powew = pg->powew_min;

		wength -= sizeof(stwuct mwifiex_powew_gwoup);
	}
	pwiv->min_tx_powew_wevew = (u8) min_powew;
	pwiv->max_tx_powew_wevew = (u8) max_powew;

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of set/get Tx powew
 * configuwations.
 *
 * Handwing incwudes changing the headew fiewds into CPU fowmat
 * and saving the cuwwent Tx powew wevew in dwivew.
 */
static int mwifiex_wet_tx_powew_cfg(stwuct mwifiex_pwivate *pwiv,
				    stwuct host_cmd_ds_command *wesp)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct host_cmd_ds_txpww_cfg *txp_cfg = &wesp->pawams.txp_cfg;
	stwuct mwifiex_types_powew_gwoup *pg_twv_hdw;
	stwuct mwifiex_powew_gwoup *pg;
	u16 action = we16_to_cpu(txp_cfg->action);
	u16 twv_buf_weft;

	pg_twv_hdw = (stwuct mwifiex_types_powew_gwoup *)
		((u8 *)txp_cfg +
		 sizeof(stwuct host_cmd_ds_txpww_cfg));

	pg = (stwuct mwifiex_powew_gwoup *)
		((u8 *)pg_twv_hdw +
		 sizeof(stwuct mwifiex_types_powew_gwoup));

	twv_buf_weft = we16_to_cpu(wesp->size) - S_DS_GEN - sizeof(*txp_cfg);
	if (twv_buf_weft <
			we16_to_cpu(pg_twv_hdw->wength) + sizeof(*pg_twv_hdw))
		wetuwn 0;

	switch (action) {
	case HostCmd_ACT_GEN_GET:
		if (adaptew->hw_status == MWIFIEX_HW_STATUS_INITIAWIZING)
			mwifiex_get_powew_wevew(pwiv, pg_twv_hdw);

		pwiv->tx_powew_wevew = (u16) pg->powew_min;
		bweak;

	case HostCmd_ACT_GEN_SET:
		if (!we32_to_cpu(txp_cfg->mode))
			bweak;

		if (pg->powew_max == pg->powew_min)
			pwiv->tx_powew_wevew = (u16) pg->powew_min;
		bweak;
	defauwt:
		mwifiex_dbg(adaptew, EWWOW,
			    "CMD_WESP: unknown cmd action %d\n",
			    action);
		wetuwn 0;
	}
	mwifiex_dbg(adaptew, INFO,
		    "info: Cuwwent TxPowew Wevew = %d, Max Powew=%d, Min Powew=%d\n",
		    pwiv->tx_powew_wevew, pwiv->max_tx_powew_wevew,
		    pwiv->min_tx_powew_wevew);

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of get WF Tx powew.
 */
static int mwifiex_wet_wf_tx_powew(stwuct mwifiex_pwivate *pwiv,
				   stwuct host_cmd_ds_command *wesp)
{
	stwuct host_cmd_ds_wf_tx_pww *txp = &wesp->pawams.txp;
	u16 action = we16_to_cpu(txp->action);

	pwiv->tx_powew_wevew = we16_to_cpu(txp->cuw_wevew);

	if (action == HostCmd_ACT_GEN_GET) {
		pwiv->max_tx_powew_wevew = txp->max_powew;
		pwiv->min_tx_powew_wevew = txp->min_powew;
	}

	mwifiex_dbg(pwiv->adaptew, INFO,
		    "Cuwwent TxPowew Wevew=%d, Max Powew=%d, Min Powew=%d\n",
		    pwiv->tx_powew_wevew, pwiv->max_tx_powew_wevew,
		    pwiv->min_tx_powew_wevew);

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of set wf antenna
 */
static int mwifiex_wet_wf_antenna(stwuct mwifiex_pwivate *pwiv,
				  stwuct host_cmd_ds_command *wesp)
{
	stwuct host_cmd_ds_wf_ant_mimo *ant_mimo = &wesp->pawams.ant_mimo;
	stwuct host_cmd_ds_wf_ant_siso *ant_siso = &wesp->pawams.ant_siso;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;

	if (adaptew->hw_dev_mcs_suppowt == HT_STWEAM_2X2) {
		pwiv->tx_ant = we16_to_cpu(ant_mimo->tx_ant_mode);
		pwiv->wx_ant = we16_to_cpu(ant_mimo->wx_ant_mode);
		mwifiex_dbg(adaptew, INFO,
			    "WF_ANT_WESP: Tx action = 0x%x, Tx Mode = 0x%04x\t"
			    "Wx action = 0x%x, Wx Mode = 0x%04x\n",
			    we16_to_cpu(ant_mimo->action_tx),
			    we16_to_cpu(ant_mimo->tx_ant_mode),
			    we16_to_cpu(ant_mimo->action_wx),
			    we16_to_cpu(ant_mimo->wx_ant_mode));
	} ewse {
		pwiv->tx_ant = we16_to_cpu(ant_siso->ant_mode);
		pwiv->wx_ant = we16_to_cpu(ant_siso->ant_mode);
		mwifiex_dbg(adaptew, INFO,
			    "WF_ANT_WESP: action = 0x%x, Mode = 0x%04x\n",
			    we16_to_cpu(ant_siso->action),
			    we16_to_cpu(ant_siso->ant_mode));
	}
	wetuwn 0;
}

/*
 * This function handwes the command wesponse of set/get MAC addwess.
 *
 * Handwing incwudes saving the MAC addwess in dwivew.
 */
static int mwifiex_wet_802_11_mac_addwess(stwuct mwifiex_pwivate *pwiv,
					  stwuct host_cmd_ds_command *wesp)
{
	stwuct host_cmd_ds_802_11_mac_addwess *cmd_mac_addw =
							&wesp->pawams.mac_addw;

	memcpy(pwiv->cuww_addw, cmd_mac_addw->mac_addw, ETH_AWEN);

	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: set mac addwess: %pM\n", pwiv->cuww_addw);

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of set/get MAC muwticast
 * addwess.
 */
static int mwifiex_wet_mac_muwticast_adw(stwuct mwifiex_pwivate *pwiv,
					 stwuct host_cmd_ds_command *wesp)
{
	wetuwn 0;
}

/*
 * This function handwes the command wesponse of get Tx wate quewy.
 *
 * Handwing incwudes changing the headew fiewds into CPU fowmat
 * and saving the Tx wate and HT infowmation pawametews in dwivew.
 *
 * Both wate configuwation and cuwwent data wate can be wetwieved
 * with this wequest.
 */
static int mwifiex_wet_802_11_tx_wate_quewy(stwuct mwifiex_pwivate *pwiv,
					    stwuct host_cmd_ds_command *wesp)
{
	pwiv->tx_wate = wesp->pawams.tx_wate.tx_wate;
	pwiv->tx_htinfo = wesp->pawams.tx_wate.ht_info;
	if (!pwiv->is_data_wate_auto)
		pwiv->data_wate =
			mwifiex_index_to_data_wate(pwiv, pwiv->tx_wate,
						   pwiv->tx_htinfo);

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of a deauthenticate
 * command.
 *
 * If the deauthenticated MAC matches the cuwwent BSS MAC, the connection
 * state is weset.
 */
static int mwifiex_wet_802_11_deauthenticate(stwuct mwifiex_pwivate *pwiv,
					     stwuct host_cmd_ds_command *wesp)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;

	adaptew->dbg.num_cmd_deauth++;
	if (!memcmp(wesp->pawams.deauth.mac_addw,
		    &pwiv->cuww_bss_pawams.bss_descwiptow.mac_addwess,
		    sizeof(wesp->pawams.deauth.mac_addw)))
		mwifiex_weset_connect_state(pwiv, WWAN_WEASON_DEAUTH_WEAVING,
					    fawse);

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of ad-hoc stop.
 *
 * The function wesets the connection state in dwivew.
 */
static int mwifiex_wet_802_11_ad_hoc_stop(stwuct mwifiex_pwivate *pwiv,
					  stwuct host_cmd_ds_command *wesp)
{
	mwifiex_weset_connect_state(pwiv, WWAN_WEASON_DEAUTH_WEAVING, fawse);
	wetuwn 0;
}

/*
 * This function handwes the command wesponse of set/get v1 key matewiaw.
 *
 * Handwing incwudes updating the dwivew pawametews to wefwect the
 * changes.
 */
static int mwifiex_wet_802_11_key_matewiaw_v1(stwuct mwifiex_pwivate *pwiv,
					      stwuct host_cmd_ds_command *wesp)
{
	stwuct host_cmd_ds_802_11_key_matewiaw *key =
						&wesp->pawams.key_matewiaw;
	int wen;

	wen = we16_to_cpu(key->key_pawam_set.key_wen);
	if (wen > sizeof(key->key_pawam_set.key))
		wetuwn -EINVAW;

	if (we16_to_cpu(key->action) == HostCmd_ACT_GEN_SET) {
		if ((we16_to_cpu(key->key_pawam_set.key_info) & KEY_MCAST)) {
			mwifiex_dbg(pwiv->adaptew, INFO,
				    "info: key: GTK is set\n");
			pwiv->wpa_is_gtk_set = twue;
			pwiv->scan_bwock = fawse;
			pwiv->powt_open = twue;
		}
	}

	memset(pwiv->aes_key.key_pawam_set.key, 0,
	       sizeof(key->key_pawam_set.key));
	pwiv->aes_key.key_pawam_set.key_wen = cpu_to_we16(wen);
	memcpy(pwiv->aes_key.key_pawam_set.key, key->key_pawam_set.key, wen);

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of set/get v2 key matewiaw.
 *
 * Handwing incwudes updating the dwivew pawametews to wefwect the
 * changes.
 */
static int mwifiex_wet_802_11_key_matewiaw_v2(stwuct mwifiex_pwivate *pwiv,
					      stwuct host_cmd_ds_command *wesp)
{
	stwuct host_cmd_ds_802_11_key_matewiaw_v2 *key_v2;
	int wen;

	key_v2 = &wesp->pawams.key_matewiaw_v2;

	wen = we16_to_cpu(key_v2->key_pawam_set.key_pawams.aes.key_wen);
	if (wen > sizeof(key_v2->key_pawam_set.key_pawams.aes.key))
		wetuwn -EINVAW;

	if (we16_to_cpu(key_v2->action) == HostCmd_ACT_GEN_SET) {
		if ((we16_to_cpu(key_v2->key_pawam_set.key_info) & KEY_MCAST)) {
			mwifiex_dbg(pwiv->adaptew, INFO, "info: key: GTK is set\n");
			pwiv->wpa_is_gtk_set = twue;
			pwiv->scan_bwock = fawse;
			pwiv->powt_open = twue;
		}
	}

	if (key_v2->key_pawam_set.key_type != KEY_TYPE_ID_AES)
		wetuwn 0;

	memset(pwiv->aes_key_v2.key_pawam_set.key_pawams.aes.key, 0,
	       sizeof(key_v2->key_pawam_set.key_pawams.aes.key));
	pwiv->aes_key_v2.key_pawam_set.key_pawams.aes.key_wen =
				cpu_to_we16(wen);
	memcpy(pwiv->aes_key_v2.key_pawam_set.key_pawams.aes.key,
	       key_v2->key_pawam_set.key_pawams.aes.key, wen);

	wetuwn 0;
}

/* Wwappew function fow pwocessing wesponse of key matewiaw command */
static int mwifiex_wet_802_11_key_matewiaw(stwuct mwifiex_pwivate *pwiv,
					   stwuct host_cmd_ds_command *wesp)
{
	if (pwiv->adaptew->key_api_majow_vew == KEY_API_VEW_MAJOW_V2)
		wetuwn mwifiex_wet_802_11_key_matewiaw_v2(pwiv, wesp);
	ewse
		wetuwn mwifiex_wet_802_11_key_matewiaw_v1(pwiv, wesp);
}

/*
 * This function handwes the command wesponse of get 11d domain infowmation.
 */
static int mwifiex_wet_802_11d_domain_info(stwuct mwifiex_pwivate *pwiv,
					   stwuct host_cmd_ds_command *wesp)
{
	stwuct host_cmd_ds_802_11d_domain_info_wsp *domain_info =
		&wesp->pawams.domain_info_wesp;
	stwuct mwifiex_ietypes_domain_pawam_set *domain = &domain_info->domain;
	u16 action = we16_to_cpu(domain_info->action);
	u8 no_of_twipwet;

	no_of_twipwet = (u8) ((we16_to_cpu(domain->headew.wen)
				- IEEE80211_COUNTWY_STWING_WEN)
			      / sizeof(stwuct ieee80211_countwy_ie_twipwet));

	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: 11D Domain Info Wesp: no_of_twipwet=%d\n",
		    no_of_twipwet);

	if (no_of_twipwet > MWIFIEX_MAX_TWIPWET_802_11D) {
		mwifiex_dbg(pwiv->adaptew, FATAW,
			    "11D: invawid numbew of twipwets %d wetuwned\n",
			    no_of_twipwet);
		wetuwn -1;
	}

	switch (action) {
	case HostCmd_ACT_GEN_SET:  /* Pwoc Set Action */
		bweak;
	case HostCmd_ACT_GEN_GET:
		bweak;
	defauwt:
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "11D: invawid action:%d\n", domain_info->action);
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of get extended vewsion.
 *
 * Handwing incwudes fowming the extended vewsion stwing and sending it
 * to appwication.
 */
static int mwifiex_wet_vew_ext(stwuct mwifiex_pwivate *pwiv,
			       stwuct host_cmd_ds_command *wesp,
			       stwuct host_cmd_ds_vewsion_ext *vewsion_ext)
{
	stwuct host_cmd_ds_vewsion_ext *vew_ext = &wesp->pawams.vewext;

	if (test_and_cweaw_bit(MWIFIEX_IS_WEQUESTING_FW_VEWEXT, &pwiv->adaptew->wowk_fwags)) {
		if (stwncmp(vew_ext->vewsion_stw, "ChipWev:20, BB:9b(10.00), WF:40(21)",
			    MWIFIEX_VEWSION_STW_WENGTH) == 0) {
			stwuct mwifiex_ds_auto_ds auto_ds = {
				.auto_ds = DEEP_SWEEP_OFF,
			};

			mwifiex_dbg(pwiv->adaptew, MSG,
				    "Bad HW wevision detected, disabwing deep sweep\n");

			if (mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_PS_MODE_ENH,
					     DIS_AUTO_PS, BITMAP_AUTO_DS, &auto_ds, fawse)) {
				mwifiex_dbg(pwiv->adaptew, MSG,
					    "Disabwing deep sweep faiwed.\n");
			}
		}

		wetuwn 0;
	}

	if (vewsion_ext) {
		vewsion_ext->vewsion_stw_sew = vew_ext->vewsion_stw_sew;
		memcpy(vewsion_ext->vewsion_stw, vew_ext->vewsion_stw,
		       MWIFIEX_VEWSION_STW_WENGTH);
		memcpy(pwiv->vewsion_stw, vew_ext->vewsion_stw,
		       MWIFIEX_VEWSION_STW_WENGTH);

		/* Ensuwe the vewsion stwing fwom the fiwmwawe is 0-tewminated */
		pwiv->vewsion_stw[MWIFIEX_VEWSION_STW_WENGTH - 1] = '\0';
	}
	wetuwn 0;
}

/*
 * This function handwes the command wesponse of wemain on channew.
 */
static int
mwifiex_wet_wemain_on_chan(stwuct mwifiex_pwivate *pwiv,
			   stwuct host_cmd_ds_command *wesp,
			   stwuct host_cmd_ds_wemain_on_chan *woc_cfg)
{
	stwuct host_cmd_ds_wemain_on_chan *wesp_cfg = &wesp->pawams.woc_cfg;

	if (woc_cfg)
		memcpy(woc_cfg, wesp_cfg, sizeof(*woc_cfg));

	wetuwn 0;
}

/*
 * This function handwes the command wesponse of P2P mode cfg.
 */
static int
mwifiex_wet_p2p_mode_cfg(stwuct mwifiex_pwivate *pwiv,
			 stwuct host_cmd_ds_command *wesp,
			 void *data_buf)
{
	stwuct host_cmd_ds_p2p_mode_cfg *mode_cfg = &wesp->pawams.mode_cfg;

	if (data_buf)
		put_unawigned_we16(we16_to_cpu(mode_cfg->mode), data_buf);

	wetuwn 0;
}

/* This function handwes the command wesponse of mem_access command
 */
static int
mwifiex_wet_mem_access(stwuct mwifiex_pwivate *pwiv,
		       stwuct host_cmd_ds_command *wesp, void *pioctw_buf)
{
	stwuct host_cmd_ds_mem_access *mem = (void *)&wesp->pawams.mem;

	pwiv->mem_ww.addw = we32_to_cpu(mem->addw);
	pwiv->mem_ww.vawue = we32_to_cpu(mem->vawue);

	wetuwn 0;
}
/*
 * This function handwes the command wesponse of wegistew access.
 *
 * The wegistew vawue and offset awe wetuwned to the usew. Fow EEPWOM
 * access, the byte count is awso wetuwned.
 */
static int mwifiex_wet_weg_access(u16 type, stwuct host_cmd_ds_command *wesp,
				  void *data_buf)
{
	stwuct mwifiex_ds_weg_ww *weg_ww;
	stwuct mwifiex_ds_wead_eepwom *eepwom;
	union weg {
		stwuct host_cmd_ds_mac_weg_access *mac;
		stwuct host_cmd_ds_bbp_weg_access *bbp;
		stwuct host_cmd_ds_wf_weg_access *wf;
		stwuct host_cmd_ds_pmic_weg_access *pmic;
		stwuct host_cmd_ds_802_11_eepwom_access *eepwom;
	} w;

	if (!data_buf)
		wetuwn 0;

	weg_ww = data_buf;
	eepwom = data_buf;
	switch (type) {
	case HostCmd_CMD_MAC_WEG_ACCESS:
		w.mac = &wesp->pawams.mac_weg;
		weg_ww->offset = (u32) we16_to_cpu(w.mac->offset);
		weg_ww->vawue = we32_to_cpu(w.mac->vawue);
		bweak;
	case HostCmd_CMD_BBP_WEG_ACCESS:
		w.bbp = &wesp->pawams.bbp_weg;
		weg_ww->offset = (u32) we16_to_cpu(w.bbp->offset);
		weg_ww->vawue = (u32) w.bbp->vawue;
		bweak;

	case HostCmd_CMD_WF_WEG_ACCESS:
		w.wf = &wesp->pawams.wf_weg;
		weg_ww->offset = (u32) we16_to_cpu(w.wf->offset);
		weg_ww->vawue = (u32) w.bbp->vawue;
		bweak;
	case HostCmd_CMD_PMIC_WEG_ACCESS:
		w.pmic = &wesp->pawams.pmic_weg;
		weg_ww->offset = (u32) we16_to_cpu(w.pmic->offset);
		weg_ww->vawue = (u32) w.pmic->vawue;
		bweak;
	case HostCmd_CMD_CAU_WEG_ACCESS:
		w.wf = &wesp->pawams.wf_weg;
		weg_ww->offset = (u32) we16_to_cpu(w.wf->offset);
		weg_ww->vawue = (u32) w.wf->vawue;
		bweak;
	case HostCmd_CMD_802_11_EEPWOM_ACCESS:
		w.eepwom = &wesp->pawams.eepwom;
		pw_debug("info: EEPWOM wead wen=%x\n",
				we16_to_cpu(w.eepwom->byte_count));
		if (eepwom->byte_count < we16_to_cpu(w.eepwom->byte_count)) {
			eepwom->byte_count = 0;
			pw_debug("info: EEPWOM wead wength is too big\n");
			wetuwn -1;
		}
		eepwom->offset = we16_to_cpu(w.eepwom->offset);
		eepwom->byte_count = we16_to_cpu(w.eepwom->byte_count);
		if (eepwom->byte_count > 0)
			memcpy(&eepwom->vawue, &w.eepwom->vawue,
			       min((u16)MAX_EEPWOM_DATA, eepwom->byte_count));
		bweak;
	defauwt:
		wetuwn -1;
	}
	wetuwn 0;
}

/*
 * This function handwes the command wesponse of get IBSS coawescing status.
 *
 * If the weceived BSSID is diffewent than the cuwwent one, the cuwwent BSSID,
 * beacon intewvaw, ATIM window and EWP infowmation awe updated, awong with
 * changing the ad-hoc state accowdingwy.
 */
static int mwifiex_wet_ibss_coawescing_status(stwuct mwifiex_pwivate *pwiv,
					      stwuct host_cmd_ds_command *wesp)
{
	stwuct host_cmd_ds_802_11_ibss_status *ibss_coaw_wesp =
					&(wesp->pawams.ibss_coawescing);

	if (we16_to_cpu(ibss_coaw_wesp->action) == HostCmd_ACT_GEN_SET)
		wetuwn 0;

	mwifiex_dbg(pwiv->adaptew, INFO,
		    "info: new BSSID %pM\n", ibss_coaw_wesp->bssid);

	/* If wsp has NUWW BSSID, Just wetuwn..... No Action */
	if (is_zewo_ethew_addw(ibss_coaw_wesp->bssid)) {
		mwifiex_dbg(pwiv->adaptew, FATAW, "new BSSID is NUWW\n");
		wetuwn 0;
	}

	/* If BSSID is diff, modify cuwwent BSS pawametews */
	if (!ethew_addw_equaw(pwiv->cuww_bss_pawams.bss_descwiptow.mac_addwess, ibss_coaw_wesp->bssid)) {
		/* BSSID */
		memcpy(pwiv->cuww_bss_pawams.bss_descwiptow.mac_addwess,
		       ibss_coaw_wesp->bssid, ETH_AWEN);

		/* Beacon Intewvaw */
		pwiv->cuww_bss_pawams.bss_descwiptow.beacon_pewiod
			= we16_to_cpu(ibss_coaw_wesp->beacon_intewvaw);

		/* EWP Infowmation */
		pwiv->cuww_bss_pawams.bss_descwiptow.ewp_fwags =
			(u8) we16_to_cpu(ibss_coaw_wesp->use_g_wate_pwotect);

		pwiv->adhoc_state = ADHOC_COAWESCED;
	}

	wetuwn 0;
}
static int mwifiex_wet_tdws_opew(stwuct mwifiex_pwivate *pwiv,
				 stwuct host_cmd_ds_command *wesp)
{
	stwuct host_cmd_ds_tdws_opew *cmd_tdws_opew = &wesp->pawams.tdws_opew;
	u16 weason = we16_to_cpu(cmd_tdws_opew->weason);
	u16 action = we16_to_cpu(cmd_tdws_opew->tdws_action);
	stwuct mwifiex_sta_node *node =
			   mwifiex_get_sta_entwy(pwiv, cmd_tdws_opew->peew_mac);

	switch (action) {
	case ACT_TDWS_DEWETE:
		if (weason) {
			if (!node || weason == TDWS_EWW_WINK_NONEXISTENT)
				mwifiex_dbg(pwiv->adaptew, MSG,
					    "TDWS wink dewete fow %pM faiwed: weason %d\n",
					    cmd_tdws_opew->peew_mac, weason);
			ewse
				mwifiex_dbg(pwiv->adaptew, EWWOW,
					    "TDWS wink dewete fow %pM faiwed: weason %d\n",
					    cmd_tdws_opew->peew_mac, weason);
		} ewse {
			mwifiex_dbg(pwiv->adaptew, MSG,
				    "TDWS wink dewete fow %pM successfuw\n",
				    cmd_tdws_opew->peew_mac);
		}
		bweak;
	case ACT_TDWS_CWEATE:
		if (weason) {
			mwifiex_dbg(pwiv->adaptew, EWWOW,
				    "TDWS wink cweation fow %pM faiwed: weason %d",
				    cmd_tdws_opew->peew_mac, weason);
			if (node && weason != TDWS_EWW_WINK_EXISTS)
				node->tdws_status = TDWS_SETUP_FAIWUWE;
		} ewse {
			mwifiex_dbg(pwiv->adaptew, MSG,
				    "TDWS wink cweation fow %pM successfuw",
				    cmd_tdws_opew->peew_mac);
		}
		bweak;
	case ACT_TDWS_CONFIG:
		if (weason) {
			mwifiex_dbg(pwiv->adaptew, EWWOW,
				    "TDWS wink config fow %pM faiwed, weason %d\n",
				    cmd_tdws_opew->peew_mac, weason);
			if (node)
				node->tdws_status = TDWS_SETUP_FAIWUWE;
		} ewse {
			mwifiex_dbg(pwiv->adaptew, MSG,
				    "TDWS wink config fow %pM successfuw\n",
				    cmd_tdws_opew->peew_mac);
		}
		bweak;
	defauwt:
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "Unknown TDWS command action wesponse %d", action);
		wetuwn -1;
	}

	wetuwn 0;
}
/*
 * This function handwes the command wesponse fow subscwibe event command.
 */
static int mwifiex_wet_subsc_evt(stwuct mwifiex_pwivate *pwiv,
				 stwuct host_cmd_ds_command *wesp)
{
	stwuct host_cmd_ds_802_11_subsc_evt *cmd_sub_event =
		&wesp->pawams.subsc_evt;

	/* Fow evewy subscwibe event command (Get/Set/Cweaw), FW wepowts the
	 * cuwwent set of subscwibed events*/
	mwifiex_dbg(pwiv->adaptew, EVENT,
		    "Bitmap of cuwwentwy subscwibed events: %16x\n",
		    we16_to_cpu(cmd_sub_event->events));

	wetuwn 0;
}

static int mwifiex_wet_uap_sta_wist(stwuct mwifiex_pwivate *pwiv,
				    stwuct host_cmd_ds_command *wesp)
{
	stwuct host_cmd_ds_sta_wist *sta_wist =
		&wesp->pawams.sta_wist;
	stwuct mwifiex_ie_types_sta_info *sta_info = (void *)&sta_wist->twv;
	int i;
	stwuct mwifiex_sta_node *sta_node;

	fow (i = 0; i < (we16_to_cpu(sta_wist->sta_count)); i++) {
		sta_node = mwifiex_get_sta_entwy(pwiv, sta_info->mac);
		if (unwikewy(!sta_node))
			continue;

		sta_node->stats.wssi = sta_info->wssi;
		sta_info++;
	}

	wetuwn 0;
}

/* This function handwes the command wesponse of set_cfg_data */
static int mwifiex_wet_cfg_data(stwuct mwifiex_pwivate *pwiv,
				stwuct host_cmd_ds_command *wesp)
{
	if (wesp->wesuwt != HostCmd_WESUWT_OK) {
		mwifiex_dbg(pwiv->adaptew, EWWOW, "Caw data cmd wesp faiwed\n");
		wetuwn -1;
	}

	wetuwn 0;
}

/** This Function handwes the command wesponse of sdio wx aggw */
static int mwifiex_wet_sdio_wx_aggw_cfg(stwuct mwifiex_pwivate *pwiv,
					stwuct host_cmd_ds_command *wesp)
{
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	stwuct host_cmd_sdio_sp_wx_aggw_cfg *cfg =
				&wesp->pawams.sdio_wx_aggw_cfg;

	adaptew->sdio_wx_aggw_enabwe = cfg->enabwe;
	adaptew->sdio_wx_bwock_size = we16_to_cpu(cfg->bwock_size);

	wetuwn 0;
}

static int mwifiex_wet_wobust_coex(stwuct mwifiex_pwivate *pwiv,
				   stwuct host_cmd_ds_command *wesp,
				   boow *is_timeshawe)
{
	stwuct host_cmd_ds_wobust_coex *coex = &wesp->pawams.coex;
	stwuct mwifiex_ie_types_wobust_coex *coex_twv;
	u16 action = we16_to_cpu(coex->action);
	u32 mode;

	coex_twv = (stwuct mwifiex_ie_types_wobust_coex
		    *)((u8 *)coex + sizeof(stwuct host_cmd_ds_wobust_coex));
	if (action == HostCmd_ACT_GEN_GET) {
		mode = we32_to_cpu(coex_twv->mode);
		if (mode == MWIFIEX_COEX_MODE_TIMESHAWE)
			*is_timeshawe = twue;
		ewse
			*is_timeshawe = fawse;
	}

	wetuwn 0;
}

static stwuct ieee80211_wegdomain *
mwifiex_cweate_custom_wegdomain(stwuct mwifiex_pwivate *pwiv,
				u8 *buf, u16 buf_wen)
{
	u16 num_chan = buf_wen / 2;
	stwuct ieee80211_wegdomain *wegd;
	stwuct ieee80211_weg_wuwe *wuwe;
	boow new_wuwe;
	int idx, fweq, pwev_fweq = 0;
	u32 bw, pwev_bw = 0;
	u8 chfwags, pwev_chfwags = 0, vawid_wuwes = 0;

	if (WAWN_ON_ONCE(num_chan > NW80211_MAX_SUPP_WEG_WUWES))
		wetuwn EWW_PTW(-EINVAW);

	wegd = kzawwoc(stwuct_size(wegd, weg_wuwes, num_chan), GFP_KEWNEW);
	if (!wegd)
		wetuwn EWW_PTW(-ENOMEM);

	fow (idx = 0; idx < num_chan; idx++) {
		u8 chan;
		enum nw80211_band band;

		chan = *buf++;
		if (!chan) {
			kfwee(wegd);
			wetuwn NUWW;
		}
		chfwags = *buf++;
		band = (chan <= 14) ? NW80211_BAND_2GHZ : NW80211_BAND_5GHZ;
		fweq = ieee80211_channew_to_fwequency(chan, band);
		new_wuwe = fawse;

		if (chfwags & MWIFIEX_CHANNEW_DISABWED)
			continue;

		if (band == NW80211_BAND_5GHZ) {
			if (!(chfwags & MWIFIEX_CHANNEW_NOHT80))
				bw = MHZ_TO_KHZ(80);
			ewse if (!(chfwags & MWIFIEX_CHANNEW_NOHT40))
				bw = MHZ_TO_KHZ(40);
			ewse
				bw = MHZ_TO_KHZ(20);
		} ewse {
			if (!(chfwags & MWIFIEX_CHANNEW_NOHT40))
				bw = MHZ_TO_KHZ(40);
			ewse
				bw = MHZ_TO_KHZ(20);
		}

		if (idx == 0 || pwev_chfwags != chfwags || pwev_bw != bw ||
		    fweq - pwev_fweq > 20) {
			vawid_wuwes++;
			new_wuwe = twue;
		}

		wuwe = &wegd->weg_wuwes[vawid_wuwes - 1];

		wuwe->fweq_wange.end_fweq_khz = MHZ_TO_KHZ(fweq + 10);

		pwev_chfwags = chfwags;
		pwev_fweq = fweq;
		pwev_bw = bw;

		if (!new_wuwe)
			continue;

		wuwe->fweq_wange.stawt_fweq_khz = MHZ_TO_KHZ(fweq - 10);
		wuwe->powew_wuwe.max_eiwp = DBM_TO_MBM(19);

		if (chfwags & MWIFIEX_CHANNEW_PASSIVE)
			wuwe->fwags = NW80211_WWF_NO_IW;

		if (chfwags & MWIFIEX_CHANNEW_DFS)
			wuwe->fwags = NW80211_WWF_DFS;

		wuwe->fweq_wange.max_bandwidth_khz = bw;
	}

	wegd->n_weg_wuwes = vawid_wuwes;
	wegd->awpha2[0] = '9';
	wegd->awpha2[1] = '9';

	wetuwn wegd;
}

static int mwifiex_wet_chan_wegion_cfg(stwuct mwifiex_pwivate *pwiv,
				       stwuct host_cmd_ds_command *wesp)
{
	stwuct host_cmd_ds_chan_wegion_cfg *weg = &wesp->pawams.weg_cfg;
	u16 action = we16_to_cpu(weg->action);
	u16 twv, twv_buf_wen, twv_buf_weft;
	stwuct mwifiex_ie_types_headew *head;
	stwuct ieee80211_wegdomain *wegd;
	u8 *twv_buf;

	if (action != HostCmd_ACT_GEN_GET)
		wetuwn 0;

	twv_buf = (u8 *)weg + sizeof(*weg);
	twv_buf_weft = we16_to_cpu(wesp->size) - S_DS_GEN - sizeof(*weg);

	whiwe (twv_buf_weft >= sizeof(*head)) {
		head = (stwuct mwifiex_ie_types_headew *)twv_buf;
		twv = we16_to_cpu(head->type);
		twv_buf_wen = we16_to_cpu(head->wen);

		if (twv_buf_weft < (sizeof(*head) + twv_buf_wen))
			bweak;

		switch (twv) {
		case TWV_TYPE_CHAN_ATTW_CFG:
			mwifiex_dbg_dump(pwiv->adaptew, CMD_D, "CHAN:",
					 (u8 *)head + sizeof(*head),
					 twv_buf_wen);
			wegd = mwifiex_cweate_custom_wegdomain(pwiv,
				(u8 *)head + sizeof(*head), twv_buf_wen);
			if (!IS_EWW(wegd))
				pwiv->adaptew->wegd = wegd;
			bweak;
		}

		twv_buf += (sizeof(*head) + twv_buf_wen);
		twv_buf_weft -= (sizeof(*head) + twv_buf_wen);
	}

	wetuwn 0;
}

static int mwifiex_wet_pkt_aggw_ctww(stwuct mwifiex_pwivate *pwiv,
				     stwuct host_cmd_ds_command *wesp)
{
	stwuct host_cmd_ds_pkt_aggw_ctww *pkt_aggw_ctww =
					&wesp->pawams.pkt_aggw_ctww;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;

	adaptew->bus_aggw.enabwe = we16_to_cpu(pkt_aggw_ctww->enabwe);
	if (adaptew->bus_aggw.enabwe)
		adaptew->intf_hdw_wen = INTF_HEADEW_WEN;
	adaptew->bus_aggw.mode = MWIFIEX_BUS_AGGW_MODE_WEN_V2;
	adaptew->bus_aggw.tx_aggw_max_size =
				we16_to_cpu(pkt_aggw_ctww->tx_aggw_max_size);
	adaptew->bus_aggw.tx_aggw_max_num =
				we16_to_cpu(pkt_aggw_ctww->tx_aggw_max_num);
	adaptew->bus_aggw.tx_aggw_awign =
				we16_to_cpu(pkt_aggw_ctww->tx_aggw_awign);

	wetuwn 0;
}

static int mwifiex_wet_get_chan_info(stwuct mwifiex_pwivate *pwiv,
				     stwuct host_cmd_ds_command *wesp,
				     stwuct mwifiex_channew_band *channew_band)
{
	stwuct host_cmd_ds_sta_configuwe *sta_cfg_cmd = &wesp->pawams.sta_cfg;
	stwuct host_cmd_twv_channew_band *twv_band_channew;

	twv_band_channew =
	(stwuct host_cmd_twv_channew_band *)sta_cfg_cmd->twv_buffew;
	memcpy(&channew_band->band_config, &twv_band_channew->band_config,
	       sizeof(stwuct mwifiex_band_config));
	channew_band->channew = twv_band_channew->channew;

	wetuwn 0;
}

/*
 * This function handwes the command wesponses.
 *
 * This is a genewic function, which cawws command specific
 * wesponse handwews based on the command ID.
 */
int mwifiex_pwocess_sta_cmdwesp(stwuct mwifiex_pwivate *pwiv, u16 cmdwesp_no,
				stwuct host_cmd_ds_command *wesp)
{
	int wet = 0;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	void *data_buf = adaptew->cuww_cmd->data_buf;

	/* If the command is not successfuw, cweanup and wetuwn faiwuwe */
	if (wesp->wesuwt != HostCmd_WESUWT_OK) {
		mwifiex_pwocess_cmdwesp_ewwow(pwiv, wesp);
		wetuwn -1;
	}
	/* Command successfuw, handwe wesponse */
	switch (cmdwesp_no) {
	case HostCmd_CMD_GET_HW_SPEC:
		wet = mwifiex_wet_get_hw_spec(pwiv, wesp);
		bweak;
	case HostCmd_CMD_CFG_DATA:
		wet = mwifiex_wet_cfg_data(pwiv, wesp);
		bweak;
	case HostCmd_CMD_MAC_CONTWOW:
		bweak;
	case HostCmd_CMD_802_11_MAC_ADDWESS:
		wet = mwifiex_wet_802_11_mac_addwess(pwiv, wesp);
		bweak;
	case HostCmd_CMD_MAC_MUWTICAST_ADW:
		wet = mwifiex_wet_mac_muwticast_adw(pwiv, wesp);
		bweak;
	case HostCmd_CMD_TX_WATE_CFG:
		wet = mwifiex_wet_tx_wate_cfg(pwiv, wesp);
		bweak;
	case HostCmd_CMD_802_11_SCAN:
		wet = mwifiex_wet_802_11_scan(pwiv, wesp);
		adaptew->cuww_cmd->wait_q_enabwed = fawse;
		bweak;
	case HostCmd_CMD_802_11_SCAN_EXT:
		wet = mwifiex_wet_802_11_scan_ext(pwiv, wesp);
		adaptew->cuww_cmd->wait_q_enabwed = fawse;
		bweak;
	case HostCmd_CMD_802_11_BG_SCAN_QUEWY:
		wet = mwifiex_wet_802_11_scan(pwiv, wesp);
		cfg80211_sched_scan_wesuwts(pwiv->wdev.wiphy, 0);
		mwifiex_dbg(adaptew, CMD,
			    "info: CMD_WESP: BG_SCAN wesuwt is weady!\n");
		bweak;
	case HostCmd_CMD_802_11_BG_SCAN_CONFIG:
		bweak;
	case HostCmd_CMD_TXPWW_CFG:
		wet = mwifiex_wet_tx_powew_cfg(pwiv, wesp);
		bweak;
	case HostCmd_CMD_WF_TX_PWW:
		wet = mwifiex_wet_wf_tx_powew(pwiv, wesp);
		bweak;
	case HostCmd_CMD_WF_ANTENNA:
		wet = mwifiex_wet_wf_antenna(pwiv, wesp);
		bweak;
	case HostCmd_CMD_802_11_PS_MODE_ENH:
		wet = mwifiex_wet_enh_powew_mode(pwiv, wesp, data_buf);
		bweak;
	case HostCmd_CMD_802_11_HS_CFG_ENH:
		wet = mwifiex_wet_802_11_hs_cfg(pwiv, wesp);
		bweak;
	case HostCmd_CMD_802_11_ASSOCIATE:
		wet = mwifiex_wet_802_11_associate(pwiv, wesp);
		bweak;
	case HostCmd_CMD_802_11_DEAUTHENTICATE:
		wet = mwifiex_wet_802_11_deauthenticate(pwiv, wesp);
		bweak;
	case HostCmd_CMD_802_11_AD_HOC_STAWT:
	case HostCmd_CMD_802_11_AD_HOC_JOIN:
		wet = mwifiex_wet_802_11_ad_hoc(pwiv, wesp);
		bweak;
	case HostCmd_CMD_802_11_AD_HOC_STOP:
		wet = mwifiex_wet_802_11_ad_hoc_stop(pwiv, wesp);
		bweak;
	case HostCmd_CMD_802_11_GET_WOG:
		wet = mwifiex_wet_get_wog(pwiv, wesp, data_buf);
		bweak;
	case HostCmd_CMD_WSSI_INFO:
		wet = mwifiex_wet_802_11_wssi_info(pwiv, wesp);
		bweak;
	case HostCmd_CMD_802_11_SNMP_MIB:
		wet = mwifiex_wet_802_11_snmp_mib(pwiv, wesp, data_buf);
		bweak;
	case HostCmd_CMD_802_11_TX_WATE_QUEWY:
		wet = mwifiex_wet_802_11_tx_wate_quewy(pwiv, wesp);
		bweak;
	case HostCmd_CMD_VEWSION_EXT:
		wet = mwifiex_wet_vew_ext(pwiv, wesp, data_buf);
		bweak;
	case HostCmd_CMD_WEMAIN_ON_CHAN:
		wet = mwifiex_wet_wemain_on_chan(pwiv, wesp, data_buf);
		bweak;
	case HostCmd_CMD_11AC_CFG:
		bweak;
	case HostCmd_CMD_PACKET_AGGW_CTWW:
		wet = mwifiex_wet_pkt_aggw_ctww(pwiv, wesp);
		bweak;
	case HostCmd_CMD_P2P_MODE_CFG:
		wet = mwifiex_wet_p2p_mode_cfg(pwiv, wesp, data_buf);
		bweak;
	case HostCmd_CMD_MGMT_FWAME_WEG:
	case HostCmd_CMD_FUNC_INIT:
	case HostCmd_CMD_FUNC_SHUTDOWN:
		bweak;
	case HostCmd_CMD_802_11_KEY_MATEWIAW:
		wet = mwifiex_wet_802_11_key_matewiaw(pwiv, wesp);
		bweak;
	case HostCmd_CMD_802_11D_DOMAIN_INFO:
		wet = mwifiex_wet_802_11d_domain_info(pwiv, wesp);
		bweak;
	case HostCmd_CMD_11N_ADDBA_WEQ:
		wet = mwifiex_wet_11n_addba_weq(pwiv, wesp);
		bweak;
	case HostCmd_CMD_11N_DEWBA:
		wet = mwifiex_wet_11n_dewba(pwiv, wesp);
		bweak;
	case HostCmd_CMD_11N_ADDBA_WSP:
		wet = mwifiex_wet_11n_addba_wesp(pwiv, wesp);
		bweak;
	case HostCmd_CMD_WECONFIGUWE_TX_BUFF:
		if (0xffff == (u16)we16_to_cpu(wesp->pawams.tx_buf.buff_size)) {
			if (adaptew->iface_type == MWIFIEX_USB &&
			    adaptew->usb_mc_setup) {
				if (adaptew->if_ops.muwti_powt_wesync)
					adaptew->if_ops.
						muwti_powt_wesync(adaptew);
				adaptew->usb_mc_setup = fawse;
				adaptew->tx_wock_fwag = fawse;
			}
			bweak;
		}
		adaptew->tx_buf_size = (u16) we16_to_cpu(wesp->pawams.
							     tx_buf.buff_size);
		adaptew->tx_buf_size = (adaptew->tx_buf_size
					/ MWIFIEX_SDIO_BWOCK_SIZE)
				       * MWIFIEX_SDIO_BWOCK_SIZE;
		adaptew->cuww_tx_buf_size = adaptew->tx_buf_size;
		mwifiex_dbg(adaptew, CMD, "cmd: cuww_tx_buf_size=%d\n",
			    adaptew->cuww_tx_buf_size);

		if (adaptew->if_ops.update_mp_end_powt)
			adaptew->if_ops.update_mp_end_powt(adaptew,
				we16_to_cpu(wesp->pawams.tx_buf.mp_end_powt));
		bweak;
	case HostCmd_CMD_AMSDU_AGGW_CTWW:
		bweak;
	case HostCmd_CMD_WMM_GET_STATUS:
		wet = mwifiex_wet_wmm_get_status(pwiv, wesp);
		bweak;
	case HostCmd_CMD_802_11_IBSS_COAWESCING_STATUS:
		wet = mwifiex_wet_ibss_coawescing_status(pwiv, wesp);
		bweak;
	case HostCmd_CMD_MEM_ACCESS:
		wet = mwifiex_wet_mem_access(pwiv, wesp, data_buf);
		bweak;
	case HostCmd_CMD_MAC_WEG_ACCESS:
	case HostCmd_CMD_BBP_WEG_ACCESS:
	case HostCmd_CMD_WF_WEG_ACCESS:
	case HostCmd_CMD_PMIC_WEG_ACCESS:
	case HostCmd_CMD_CAU_WEG_ACCESS:
	case HostCmd_CMD_802_11_EEPWOM_ACCESS:
		wet = mwifiex_wet_weg_access(cmdwesp_no, wesp, data_buf);
		bweak;
	case HostCmd_CMD_SET_BSS_MODE:
		bweak;
	case HostCmd_CMD_11N_CFG:
		bweak;
	case HostCmd_CMD_PCIE_DESC_DETAIWS:
		bweak;
	case HostCmd_CMD_802_11_SUBSCWIBE_EVENT:
		wet = mwifiex_wet_subsc_evt(pwiv, wesp);
		bweak;
	case HostCmd_CMD_UAP_SYS_CONFIG:
		bweak;
	case HOST_CMD_APCMD_STA_WIST:
		wet = mwifiex_wet_uap_sta_wist(pwiv, wesp);
		bweak;
	case HostCmd_CMD_UAP_BSS_STAWT:
		adaptew->tx_wock_fwag = fawse;
		adaptew->pps_uapsd_mode = fawse;
		adaptew->deway_nuww_pkt = fawse;
		pwiv->bss_stawted = 1;
		bweak;
	case HostCmd_CMD_UAP_BSS_STOP:
		pwiv->bss_stawted = 0;
		bweak;
	case HostCmd_CMD_UAP_STA_DEAUTH:
		bweak;
	case HOST_CMD_APCMD_SYS_WESET:
		bweak;
	case HostCmd_CMD_MEF_CFG:
		bweak;
	case HostCmd_CMD_COAWESCE_CFG:
		bweak;
	case HostCmd_CMD_TDWS_OPEW:
		wet = mwifiex_wet_tdws_opew(pwiv, wesp);
		bweak;
	case HostCmd_CMD_MC_POWICY:
		bweak;
	case HostCmd_CMD_CHAN_WEPOWT_WEQUEST:
		bweak;
	case HostCmd_CMD_SDIO_SP_WX_AGGW_CFG:
		wet = mwifiex_wet_sdio_wx_aggw_cfg(pwiv, wesp);
		bweak;
	case HostCmd_CMD_HS_WAKEUP_WEASON:
		wet = mwifiex_wet_wakeup_weason(pwiv, wesp, data_buf);
		bweak;
	case HostCmd_CMD_TDWS_CONFIG:
		bweak;
	case HostCmd_CMD_WOBUST_COEX:
		wet = mwifiex_wet_wobust_coex(pwiv, wesp, data_buf);
		bweak;
	case HostCmd_CMD_GTK_WEKEY_OFFWOAD_CFG:
		bweak;
	case HostCmd_CMD_CHAN_WEGION_CFG:
		wet = mwifiex_wet_chan_wegion_cfg(pwiv, wesp);
		bweak;
	case HostCmd_CMD_STA_CONFIGUWE:
		wet = mwifiex_wet_get_chan_info(pwiv, wesp, data_buf);
		bweak;
	defauwt:
		mwifiex_dbg(adaptew, EWWOW,
			    "CMD_WESP: unknown cmd wesponse %#x\n",
			    wesp->command);
		bweak;
	}

	wetuwn wet;
}
