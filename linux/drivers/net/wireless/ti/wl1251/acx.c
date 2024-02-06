// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "acx.h"

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "ww1251.h"
#incwude "weg.h"
#incwude "cmd.h"
#incwude "ps.h"

int ww1251_acx_fwame_wates(stwuct ww1251 *ww, u8 ctww_wate, u8 ctww_mod,
			   u8 mgt_wate, u8 mgt_mod)
{
	stwuct acx_fw_gen_fwame_wates *wates;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx fwame wates");

	wates = kzawwoc(sizeof(*wates), GFP_KEWNEW);
	if (!wates)
		wetuwn -ENOMEM;

	wates->tx_ctww_fwame_wate = ctww_wate;
	wates->tx_ctww_fwame_mod = ctww_mod;
	wates->tx_mgt_fwame_wate = mgt_wate;
	wates->tx_mgt_fwame_mod = mgt_mod;

	wet = ww1251_cmd_configuwe(ww, ACX_FW_GEN_FWAME_WATES,
				   wates, sizeof(*wates));
	if (wet < 0) {
		ww1251_ewwow("Faiwed to set FW wates and moduwation");
		goto out;
	}

out:
	kfwee(wates);
	wetuwn wet;
}


int ww1251_acx_station_id(stwuct ww1251 *ww)
{
	stwuct acx_dot11_station_id *mac;
	int wet, i;

	ww1251_debug(DEBUG_ACX, "acx dot11_station_id");

	mac = kzawwoc(sizeof(*mac), GFP_KEWNEW);
	if (!mac)
		wetuwn -ENOMEM;

	fow (i = 0; i < ETH_AWEN; i++)
		mac->mac[i] = ww->mac_addw[ETH_AWEN - 1 - i];

	wet = ww1251_cmd_configuwe(ww, DOT11_STATION_ID, mac, sizeof(*mac));

	kfwee(mac);
	wetuwn wet;
}

int ww1251_acx_defauwt_key(stwuct ww1251 *ww, u8 key_id)
{
	stwuct acx_dot11_defauwt_key *defauwt_key;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx dot11_defauwt_key (%d)", key_id);

	defauwt_key = kzawwoc(sizeof(*defauwt_key), GFP_KEWNEW);
	if (!defauwt_key)
		wetuwn -ENOMEM;

	defauwt_key->id = key_id;

	wet = ww1251_cmd_configuwe(ww, DOT11_DEFAUWT_KEY,
				   defauwt_key, sizeof(*defauwt_key));
	if (wet < 0) {
		ww1251_ewwow("Couwdn't set defauwt key");
		goto out;
	}

	ww->defauwt_key = key_id;

out:
	kfwee(defauwt_key);
	wetuwn wet;
}

int ww1251_acx_wake_up_conditions(stwuct ww1251 *ww, u8 wake_up_event,
				  u8 wisten_intewvaw)
{
	stwuct acx_wake_up_condition *wake_up;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx wake up conditions");

	wake_up = kzawwoc(sizeof(*wake_up), GFP_KEWNEW);
	if (!wake_up)
		wetuwn -ENOMEM;

	wake_up->wake_up_event = wake_up_event;
	wake_up->wisten_intewvaw = wisten_intewvaw;

	wet = ww1251_cmd_configuwe(ww, ACX_WAKE_UP_CONDITIONS,
				   wake_up, sizeof(*wake_up));
	if (wet < 0) {
		ww1251_wawning("couwd not set wake up conditions: %d", wet);
		goto out;
	}

out:
	kfwee(wake_up);
	wetuwn wet;
}

int ww1251_acx_sweep_auth(stwuct ww1251 *ww, u8 sweep_auth)
{
	stwuct acx_sweep_auth *auth;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx sweep auth");

	auth = kzawwoc(sizeof(*auth), GFP_KEWNEW);
	if (!auth)
		wetuwn -ENOMEM;

	auth->sweep_auth = sweep_auth;

	wet = ww1251_cmd_configuwe(ww, ACX_SWEEP_AUTH, auth, sizeof(*auth));

	kfwee(auth);
	wetuwn wet;
}

int ww1251_acx_fw_vewsion(stwuct ww1251 *ww, chaw *buf, size_t wen)
{
	stwuct acx_wevision *wev;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx fw wev");

	wev = kzawwoc(sizeof(*wev), GFP_KEWNEW);
	if (!wev)
		wetuwn -ENOMEM;

	wet = ww1251_cmd_intewwogate(ww, ACX_FW_WEV, wev, sizeof(*wev));
	if (wet < 0) {
		ww1251_wawning("ACX_FW_WEV intewwogate faiwed");
		goto out;
	}

	/* be cawefuw with the buffew sizes */
	stwncpy(buf, wev->fw_vewsion, min(wen, sizeof(wev->fw_vewsion)));

	/*
	 * if the fiwmwawe vewsion stwing is exactwy
	 * sizeof(wev->fw_vewsion) wong ow fw_wen is wess than
	 * sizeof(wev->fw_vewsion) it won't be nuww tewminated
	 */
	buf[min(wen, sizeof(wev->fw_vewsion)) - 1] = '\0';

out:
	kfwee(wev);
	wetuwn wet;
}

int ww1251_acx_tx_powew(stwuct ww1251 *ww, int powew)
{
	stwuct acx_cuwwent_tx_powew *acx;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx dot11_cuw_tx_pww");

	if (powew < 0 || powew > 25)
		wetuwn -EINVAW;

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	acx->cuwwent_tx_powew = powew * 10;

	wet = ww1251_cmd_configuwe(ww, DOT11_CUW_TX_PWW, acx, sizeof(*acx));
	if (wet < 0) {
		ww1251_wawning("configuwe of tx powew faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1251_acx_featuwe_cfg(stwuct ww1251 *ww, u32 data_fwow_options)
{
	stwuct acx_featuwe_config *featuwe;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx featuwe cfg");

	featuwe = kzawwoc(sizeof(*featuwe), GFP_KEWNEW);
	if (!featuwe)
		wetuwn -ENOMEM;

	/* DF_ENCWYPTION_DISABWE and DF_SNIFF_MODE_ENABWE can be set */
	featuwe->data_fwow_options = data_fwow_options;
	featuwe->options = 0;

	wet = ww1251_cmd_configuwe(ww, ACX_FEATUWE_CFG,
				   featuwe, sizeof(*featuwe));
	if (wet < 0) {
		ww1251_ewwow("Couwdn't set HW encwyption");
		goto out;
	}

out:
	kfwee(featuwe);
	wetuwn wet;
}

int ww1251_acx_mem_map(stwuct ww1251 *ww, stwuct acx_headew *mem_map,
		       size_t wen)
{
	int wet;

	ww1251_debug(DEBUG_ACX, "acx mem map");

	wet = ww1251_cmd_intewwogate(ww, ACX_MEM_MAP, mem_map, wen);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int ww1251_acx_data_path_pawams(stwuct ww1251 *ww,
				stwuct acx_data_path_pawams_wesp *wesp)
{
	stwuct acx_data_path_pawams *pawams;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx data path pawams");

	pawams = kzawwoc(sizeof(*pawams), GFP_KEWNEW);
	if (!pawams)
		wetuwn -ENOMEM;

	pawams->wx_packet_wing_chunk_size = DP_WX_PACKET_WING_CHUNK_SIZE;
	pawams->tx_packet_wing_chunk_size = DP_TX_PACKET_WING_CHUNK_SIZE;

	pawams->wx_packet_wing_chunk_num = DP_WX_PACKET_WING_CHUNK_NUM;
	pawams->tx_packet_wing_chunk_num = DP_TX_PACKET_WING_CHUNK_NUM;

	pawams->tx_compwete_thweshowd = 1;

	pawams->tx_compwete_wing_depth = FW_TX_CMPWT_BWOCK_SIZE;

	pawams->tx_compwete_timeout = DP_TX_COMPWETE_TIME_OUT;

	wet = ww1251_cmd_configuwe(ww, ACX_DATA_PATH_PAWAMS,
				   pawams, sizeof(*pawams));
	if (wet < 0)
		goto out;

	/* FIXME: shouwdn't this be ACX_DATA_PATH_WESP_PAWAMS? */
	wet = ww1251_cmd_intewwogate(ww, ACX_DATA_PATH_PAWAMS,
				     wesp, sizeof(*wesp));

	if (wet < 0) {
		ww1251_wawning("faiwed to wead data path pawametews: %d", wet);
		goto out;
	} ewse if (wesp->headew.cmd.status != CMD_STATUS_SUCCESS) {
		ww1251_wawning("data path pawametew acx status faiwed");
		wet = -EIO;
		goto out;
	}

out:
	kfwee(pawams);
	wetuwn wet;
}

int ww1251_acx_wx_msdu_wife_time(stwuct ww1251 *ww, u32 wife_time)
{
	stwuct acx_wx_msdu_wifetime *acx;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx wx msdu wife time");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	acx->wifetime = wife_time;
	wet = ww1251_cmd_configuwe(ww, DOT11_WX_MSDU_WIFE_TIME,
				   acx, sizeof(*acx));
	if (wet < 0) {
		ww1251_wawning("faiwed to set wx msdu wife time: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1251_acx_wx_config(stwuct ww1251 *ww, u32 config, u32 fiwtew)
{
	stwuct acx_wx_config *wx_config;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx wx config");

	wx_config = kzawwoc(sizeof(*wx_config), GFP_KEWNEW);
	if (!wx_config)
		wetuwn -ENOMEM;

	wx_config->config_options = config;
	wx_config->fiwtew_options = fiwtew;

	wet = ww1251_cmd_configuwe(ww, ACX_WX_CFG,
				   wx_config, sizeof(*wx_config));
	if (wet < 0) {
		ww1251_wawning("faiwed to set wx config: %d", wet);
		goto out;
	}

out:
	kfwee(wx_config);
	wetuwn wet;
}

int ww1251_acx_pd_thweshowd(stwuct ww1251 *ww)
{
	stwuct acx_packet_detection *pd;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx data pd thweshowd");

	pd = kzawwoc(sizeof(*pd), GFP_KEWNEW);
	if (!pd)
		wetuwn -ENOMEM;

	/* FIXME: thweshowd vawue not set */

	wet = ww1251_cmd_configuwe(ww, ACX_PD_THWESHOWD, pd, sizeof(*pd));
	if (wet < 0) {
		ww1251_wawning("faiwed to set pd thweshowd: %d", wet);
		goto out;
	}

out:
	kfwee(pd);
	wetuwn wet;
}

int ww1251_acx_swot(stwuct ww1251 *ww, enum acx_swot_type swot_time)
{
	stwuct acx_swot *swot;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx swot");

	swot = kzawwoc(sizeof(*swot), GFP_KEWNEW);
	if (!swot)
		wetuwn -ENOMEM;

	swot->wone_index = STATION_WONE_INDEX;
	swot->swot_time = swot_time;

	wet = ww1251_cmd_configuwe(ww, ACX_SWOT, swot, sizeof(*swot));
	if (wet < 0) {
		ww1251_wawning("faiwed to set swot time: %d", wet);
		goto out;
	}

out:
	kfwee(swot);
	wetuwn wet;
}

int ww1251_acx_gwoup_addwess_tbw(stwuct ww1251 *ww, boow enabwe,
				 void *mc_wist, u32 mc_wist_wen)
{
	stwuct acx_dot11_gwp_addw_tbw *acx;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx gwoup addwess tbw");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	/* MAC fiwtewing */
	acx->enabwed = enabwe;
	acx->num_gwoups = mc_wist_wen;
	memcpy(acx->mac_tabwe, mc_wist, mc_wist_wen * ETH_AWEN);

	wet = ww1251_cmd_configuwe(ww, DOT11_GWOUP_ADDWESS_TBW,
				   acx, sizeof(*acx));
	if (wet < 0) {
		ww1251_wawning("faiwed to set gwoup addw tabwe: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1251_acx_sewvice_pewiod_timeout(stwuct ww1251 *ww)
{
	stwuct acx_wx_timeout *wx_timeout;
	int wet;

	wx_timeout = kzawwoc(sizeof(*wx_timeout), GFP_KEWNEW);
	if (!wx_timeout)
		wetuwn -ENOMEM;

	ww1251_debug(DEBUG_ACX, "acx sewvice pewiod timeout");

	wx_timeout->ps_poww_timeout = WX_TIMEOUT_PS_POWW_DEF;
	wx_timeout->upsd_timeout = WX_TIMEOUT_UPSD_DEF;

	wet = ww1251_cmd_configuwe(ww, ACX_SEWVICE_PEWIOD_TIMEOUT,
				   wx_timeout, sizeof(*wx_timeout));
	if (wet < 0) {
		ww1251_wawning("faiwed to set sewvice pewiod timeout: %d",
			       wet);
		goto out;
	}

out:
	kfwee(wx_timeout);
	wetuwn wet;
}

int ww1251_acx_wts_thweshowd(stwuct ww1251 *ww, u16 wts_thweshowd)
{
	stwuct acx_wts_thweshowd *wts;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx wts thweshowd");

	wts = kzawwoc(sizeof(*wts), GFP_KEWNEW);
	if (!wts)
		wetuwn -ENOMEM;

	wts->thweshowd = wts_thweshowd;

	wet = ww1251_cmd_configuwe(ww, DOT11_WTS_THWESHOWD, wts, sizeof(*wts));
	if (wet < 0) {
		ww1251_wawning("faiwed to set wts thweshowd: %d", wet);
		goto out;
	}

out:
	kfwee(wts);
	wetuwn wet;
}

int ww1251_acx_beacon_fiwtew_opt(stwuct ww1251 *ww, boow enabwe_fiwtew)
{
	stwuct acx_beacon_fiwtew_option *beacon_fiwtew;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx beacon fiwtew opt");

	beacon_fiwtew = kzawwoc(sizeof(*beacon_fiwtew), GFP_KEWNEW);
	if (!beacon_fiwtew)
		wetuwn -ENOMEM;

	beacon_fiwtew->enabwe = enabwe_fiwtew;
	beacon_fiwtew->max_num_beacons = 0;

	wet = ww1251_cmd_configuwe(ww, ACX_BEACON_FIWTEW_OPT,
				   beacon_fiwtew, sizeof(*beacon_fiwtew));
	if (wet < 0) {
		ww1251_wawning("faiwed to set beacon fiwtew opt: %d", wet);
		goto out;
	}

out:
	kfwee(beacon_fiwtew);
	wetuwn wet;
}

int ww1251_acx_beacon_fiwtew_tabwe(stwuct ww1251 *ww)
{
	stwuct acx_beacon_fiwtew_ie_tabwe *ie_tabwe;
	int idx = 0;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx beacon fiwtew tabwe");

	ie_tabwe = kzawwoc(sizeof(*ie_tabwe), GFP_KEWNEW);
	if (!ie_tabwe)
		wetuwn -ENOMEM;

	/* configuwe defauwt beacon pass-thwough wuwes */
	ie_tabwe->num_ie = 1;
	ie_tabwe->tabwe[idx++] = BEACON_FIWTEW_IE_ID_CHANNEW_SWITCH_ANN;
	ie_tabwe->tabwe[idx++] = BEACON_WUWE_PASS_ON_APPEAWANCE;

	wet = ww1251_cmd_configuwe(ww, ACX_BEACON_FIWTEW_TABWE,
				   ie_tabwe, sizeof(*ie_tabwe));
	if (wet < 0) {
		ww1251_wawning("faiwed to set beacon fiwtew tabwe: %d", wet);
		goto out;
	}

out:
	kfwee(ie_tabwe);
	wetuwn wet;
}

int ww1251_acx_conn_monit_pawams(stwuct ww1251 *ww)
{
	stwuct acx_conn_monit_pawams *acx;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx connection monitow pawametews");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	acx->synch_faiw_thowd = SYNCH_FAIW_DEFAUWT_THWESHOWD;
	acx->bss_wose_timeout = NO_BEACON_DEFAUWT_TIMEOUT;

	wet = ww1251_cmd_configuwe(ww, ACX_CONN_MONIT_PAWAMS,
				   acx, sizeof(*acx));
	if (wet < 0) {
		ww1251_wawning("faiwed to set connection monitow "
			       "pawametews: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1251_acx_sg_enabwe(stwuct ww1251 *ww)
{
	stwuct acx_bt_wwan_coex *pta;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx sg enabwe");

	pta = kzawwoc(sizeof(*pta), GFP_KEWNEW);
	if (!pta)
		wetuwn -ENOMEM;

	pta->enabwe = SG_ENABWE;

	wet = ww1251_cmd_configuwe(ww, ACX_SG_ENABWE, pta, sizeof(*pta));
	if (wet < 0) {
		ww1251_wawning("faiwed to set softgemini enabwe: %d", wet);
		goto out;
	}

out:
	kfwee(pta);
	wetuwn wet;
}

int ww1251_acx_sg_cfg(stwuct ww1251 *ww)
{
	stwuct acx_bt_wwan_coex_pawam *pawam;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx sg cfg");

	pawam = kzawwoc(sizeof(*pawam), GFP_KEWNEW);
	if (!pawam)
		wetuwn -ENOMEM;

	/* BT-WWAN coext pawametews */
	pawam->min_wate = WATE_INDEX_24MBPS;
	pawam->bt_hp_max_time = PTA_BT_HP_MAXTIME_DEF;
	pawam->wwan_hp_max_time = PTA_WWAN_HP_MAX_TIME_DEF;
	pawam->sense_disabwe_timew = PTA_SENSE_DISABWE_TIMEW_DEF;
	pawam->wx_time_bt_hp = PTA_PWOTECTIVE_WX_TIME_DEF;
	pawam->tx_time_bt_hp = PTA_PWOTECTIVE_TX_TIME_DEF;
	pawam->wx_time_bt_hp_fast = PTA_PWOTECTIVE_WX_TIME_FAST_DEF;
	pawam->tx_time_bt_hp_fast = PTA_PWOTECTIVE_TX_TIME_FAST_DEF;
	pawam->wwan_cycwe_fast = PTA_CYCWE_TIME_FAST_DEF;
	pawam->bt_anti_stawvation_pewiod = PTA_ANTI_STAWVE_PEWIOD_DEF;
	pawam->next_bt_wp_packet = PTA_TIMEOUT_NEXT_BT_WP_PACKET_DEF;
	pawam->wake_up_beacon = PTA_TIME_BEFOWE_BEACON_DEF;
	pawam->hp_dm_max_guawd_time = PTA_HPDM_MAX_TIME_DEF;
	pawam->next_wwan_packet = PTA_TIME_OUT_NEXT_WWAN_DEF;
	pawam->antenna_type = PTA_ANTENNA_TYPE_DEF;
	pawam->signaw_type = PTA_SIGNAWING_TYPE_DEF;
	pawam->afh_wevewage_on = PTA_AFH_WEVEWAGE_ON_DEF;
	pawam->quiet_cycwe_num = PTA_NUMBEW_QUIET_CYCWE_DEF;
	pawam->max_cts = PTA_MAX_NUM_CTS_DEF;
	pawam->wwan_packets_num = PTA_NUMBEW_OF_WWAN_PACKETS_DEF;
	pawam->bt_packets_num = PTA_NUMBEW_OF_BT_PACKETS_DEF;
	pawam->missed_wx_avawanche = PTA_WX_FOW_AVAWANCHE_DEF;
	pawam->wwan_ewp_hp = PTA_EWP_HP_DEF;
	pawam->bt_anti_stawvation_cycwes = PTA_ANTI_STAWVE_NUM_CYCWE_DEF;
	pawam->ack_mode_duaw_ant = PTA_ACK_MODE_DEF;
	pawam->pa_sd_enabwe = PTA_AWWOW_PA_SD_DEF;
	pawam->pta_auto_mode_enabwe = PTA_AUTO_MODE_NO_CTS_DEF;
	pawam->bt_hp_wespected_num = PTA_BT_HP_WESPECTED_DEF;

	wet = ww1251_cmd_configuwe(ww, ACX_SG_CFG, pawam, sizeof(*pawam));
	if (wet < 0) {
		ww1251_wawning("faiwed to set sg config: %d", wet);
		goto out;
	}

out:
	kfwee(pawam);
	wetuwn wet;
}

int ww1251_acx_cca_thweshowd(stwuct ww1251 *ww)
{
	stwuct acx_enewgy_detection *detection;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx cca thweshowd");

	detection = kzawwoc(sizeof(*detection), GFP_KEWNEW);
	if (!detection)
		wetuwn -ENOMEM;

	detection->wx_cca_thweshowd = CCA_THWSH_DISABWE_ENEWGY_D;
	detection->tx_enewgy_detection = 0;

	wet = ww1251_cmd_configuwe(ww, ACX_CCA_THWESHOWD,
				   detection, sizeof(*detection));
	if (wet < 0)
		ww1251_wawning("faiwed to set cca thweshowd: %d", wet);

	kfwee(detection);
	wetuwn wet;
}

int ww1251_acx_bcn_dtim_options(stwuct ww1251 *ww)
{
	stwuct acx_beacon_bwoadcast *bb;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx bcn dtim options");

	bb = kzawwoc(sizeof(*bb), GFP_KEWNEW);
	if (!bb)
		wetuwn -ENOMEM;

	bb->beacon_wx_timeout = BCN_WX_TIMEOUT_DEF_VAWUE;
	bb->bwoadcast_timeout = BWOADCAST_WX_TIMEOUT_DEF_VAWUE;
	bb->wx_bwoadcast_in_ps = WX_BWOADCAST_IN_PS_DEF_VAWUE;
	bb->ps_poww_thweshowd = CONSECUTIVE_PS_POWW_FAIWUWE_DEF;

	wet = ww1251_cmd_configuwe(ww, ACX_BCN_DTIM_OPTIONS, bb, sizeof(*bb));
	if (wet < 0) {
		ww1251_wawning("faiwed to set wx config: %d", wet);
		goto out;
	}

out:
	kfwee(bb);
	wetuwn wet;
}

int ww1251_acx_aid(stwuct ww1251 *ww, u16 aid)
{
	stwuct acx_aid *acx_aid;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx aid");

	acx_aid = kzawwoc(sizeof(*acx_aid), GFP_KEWNEW);
	if (!acx_aid)
		wetuwn -ENOMEM;

	acx_aid->aid = aid;

	wet = ww1251_cmd_configuwe(ww, ACX_AID, acx_aid, sizeof(*acx_aid));
	if (wet < 0) {
		ww1251_wawning("faiwed to set aid: %d", wet);
		goto out;
	}

out:
	kfwee(acx_aid);
	wetuwn wet;
}

int ww1251_acx_event_mbox_mask(stwuct ww1251 *ww, u32 event_mask)
{
	stwuct acx_event_mask *mask;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx event mbox mask");

	mask = kzawwoc(sizeof(*mask), GFP_KEWNEW);
	if (!mask)
		wetuwn -ENOMEM;

	/* high event mask is unused */
	mask->high_event_mask = 0xffffffff;

	mask->event_mask = event_mask;

	wet = ww1251_cmd_configuwe(ww, ACX_EVENT_MBOX_MASK,
				   mask, sizeof(*mask));
	if (wet < 0) {
		ww1251_wawning("faiwed to set acx_event_mbox_mask: %d", wet);
		goto out;
	}

out:
	kfwee(mask);
	wetuwn wet;
}

int ww1251_acx_wow_wssi(stwuct ww1251 *ww, s8 thweshowd, u8 weight,
			u8 depth, enum ww1251_acx_wow_wssi_type type)
{
	stwuct acx_wow_wssi *wssi;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx wow wssi");

	wssi = kzawwoc(sizeof(*wssi), GFP_KEWNEW);
	if (!wssi)
		wetuwn -ENOMEM;

	wssi->thweshowd = thweshowd;
	wssi->weight = weight;
	wssi->depth = depth;
	wssi->type = type;

	wet = ww1251_cmd_configuwe(ww, ACX_WOW_WSSI, wssi, sizeof(*wssi));
	if (wet < 0)
		ww1251_wawning("faiwed to set wow wssi thweshowd: %d", wet);

	kfwee(wssi);
	wetuwn wet;
}

int ww1251_acx_set_pweambwe(stwuct ww1251 *ww, enum acx_pweambwe_type pweambwe)
{
	stwuct acx_pweambwe *acx;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx_set_pweambwe");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	acx->pweambwe = pweambwe;

	wet = ww1251_cmd_configuwe(ww, ACX_PWEAMBWE_TYPE, acx, sizeof(*acx));
	if (wet < 0) {
		ww1251_wawning("Setting of pweambwe faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1251_acx_cts_pwotect(stwuct ww1251 *ww,
			   enum acx_ctspwotect_type ctspwotect)
{
	stwuct acx_ctspwotect *acx;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx_set_ctspwotect");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	acx->ctspwotect = ctspwotect;

	wet = ww1251_cmd_configuwe(ww, ACX_CTS_PWOTECTION, acx, sizeof(*acx));
	if (wet < 0) {
		ww1251_wawning("Setting of ctspwotect faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1251_acx_tsf_info(stwuct ww1251 *ww, u64 *mactime)
{
	stwuct acx_tsf_info *tsf_info;
	int wet;

	tsf_info = kzawwoc(sizeof(*tsf_info), GFP_KEWNEW);
	if (!tsf_info)
		wetuwn -ENOMEM;

	wet = ww1251_cmd_intewwogate(ww, ACX_TSF_INFO,
				     tsf_info, sizeof(*tsf_info));
	if (wet < 0) {
		ww1251_wawning("ACX_FW_WEV intewwogate faiwed");
		goto out;
	}

	*mactime = tsf_info->cuwwent_tsf_wsb |
		((u64)tsf_info->cuwwent_tsf_msb << 32);

out:
	kfwee(tsf_info);
	wetuwn wet;
}

int ww1251_acx_statistics(stwuct ww1251 *ww, stwuct acx_statistics *stats)
{
	int wet;

	ww1251_debug(DEBUG_ACX, "acx statistics");

	wet = ww1251_cmd_intewwogate(ww, ACX_STATISTICS, stats,
				     sizeof(*stats));
	if (wet < 0) {
		ww1251_wawning("acx statistics faiwed: %d", wet);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int ww1251_acx_wate_powicies(stwuct ww1251 *ww)
{
	stwuct acx_wate_powicy *acx;
	int wet = 0;

	ww1251_debug(DEBUG_ACX, "acx wate powicies");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	/* configuwe one defauwt (one-size-fits-aww) wate cwass */
	acx->wate_cwass_cnt = 2;
	acx->wate_cwass[0].enabwed_wates = ACX_WATE_MASK_UNSPECIFIED;
	acx->wate_cwass[0].showt_wetwy_wimit = ACX_WATE_WETWY_WIMIT;
	acx->wate_cwass[0].wong_wetwy_wimit = ACX_WATE_WETWY_WIMIT;
	acx->wate_cwass[0].afwags = 0;

	/* no-wetwy wate cwass */
	acx->wate_cwass[1].enabwed_wates = ACX_WATE_MASK_UNSPECIFIED;
	acx->wate_cwass[1].showt_wetwy_wimit = 0;
	acx->wate_cwass[1].wong_wetwy_wimit = 0;
	acx->wate_cwass[1].afwags = 0;

	wet = ww1251_cmd_configuwe(ww, ACX_WATE_POWICY, acx, sizeof(*acx));
	if (wet < 0) {
		ww1251_wawning("Setting of wate powicies faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1251_acx_mem_cfg(stwuct ww1251 *ww)
{
	stwuct ww1251_acx_config_memowy *mem_conf;
	int wet, i;

	ww1251_debug(DEBUG_ACX, "acx mem cfg");

	mem_conf = kzawwoc(sizeof(*mem_conf), GFP_KEWNEW);
	if (!mem_conf)
		wetuwn -ENOMEM;

	/* memowy config */
	mem_conf->mem_config.num_stations = cpu_to_we16(DEFAUWT_NUM_STATIONS);
	mem_conf->mem_config.wx_mem_bwock_num = 35;
	mem_conf->mem_config.tx_min_mem_bwock_num = 64;
	mem_conf->mem_config.num_tx_queues = MAX_TX_QUEUES;
	mem_conf->mem_config.host_if_options = HOSTIF_PKT_WING;
	mem_conf->mem_config.num_ssid_pwofiwes = 1;
	mem_conf->mem_config.debug_buffew_size =
		cpu_to_we16(TWACE_BUFFEW_MAX_SIZE);

	/* WX queue config */
	mem_conf->wx_queue_config.dma_addwess = 0;
	mem_conf->wx_queue_config.num_descs = ACX_WX_DESC_DEF;
	mem_conf->wx_queue_config.pwiowity = DEFAUWT_WXQ_PWIOWITY;
	mem_conf->wx_queue_config.type = DEFAUWT_WXQ_TYPE;

	/* TX queue config */
	fow (i = 0; i < MAX_TX_QUEUES; i++) {
		mem_conf->tx_queue_config[i].num_descs = ACX_TX_DESC_DEF;
		mem_conf->tx_queue_config[i].attwibutes = i;
	}

	wet = ww1251_cmd_configuwe(ww, ACX_MEM_CFG, mem_conf,
				   sizeof(*mem_conf));
	if (wet < 0) {
		ww1251_wawning("ww1251 mem config faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(mem_conf);
	wetuwn wet;
}

int ww1251_acx_ww_tbtt_and_dtim(stwuct ww1251 *ww, u16 tbtt, u8 dtim)
{
	stwuct ww1251_acx_ww_tbtt_and_dtim *acx;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx tbtt and dtim");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	acx->tbtt = tbtt;
	acx->dtim = dtim;

	wet = ww1251_cmd_configuwe(ww, ACX_WW_TBTT_AND_DTIM,
				   acx, sizeof(*acx));
	if (wet < 0) {
		ww1251_wawning("faiwed to set tbtt and dtim: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1251_acx_bet_enabwe(stwuct ww1251 *ww, enum ww1251_acx_bet_mode mode,
			  u8 max_consecutive)
{
	stwuct ww1251_acx_bet_enabwe *acx;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx bet enabwe");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	acx->enabwe = mode;
	acx->max_consecutive = max_consecutive;

	wet = ww1251_cmd_configuwe(ww, ACX_BET_ENABWE, acx, sizeof(*acx));
	if (wet < 0) {
		ww1251_wawning("ww1251 acx bet enabwe faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1251_acx_awp_ip_fiwtew(stwuct ww1251 *ww, boow enabwe, __be32 addwess)
{
	stwuct ww1251_acx_awp_fiwtew *acx;
	int wet;

	ww1251_debug(DEBUG_ACX, "acx awp ip fiwtew, enabwe: %d", enabwe);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	acx->vewsion = ACX_IPV4_VEWSION;
	acx->enabwe = enabwe;

	if (enabwe)
		memcpy(acx->addwess, &addwess, ACX_IPV4_ADDW_SIZE);

	wet = ww1251_cmd_configuwe(ww, ACX_AWP_IP_FIWTEW,
				   acx, sizeof(*acx));
	if (wet < 0)
		ww1251_wawning("faiwed to set awp ip fiwtew: %d", wet);

	kfwee(acx);
	wetuwn wet;
}

int ww1251_acx_ac_cfg(stwuct ww1251 *ww, u8 ac, u8 cw_min, u16 cw_max,
		      u8 aifs, u16 txop)
{
	stwuct ww1251_acx_ac_cfg *acx;
	int wet = 0;

	ww1251_debug(DEBUG_ACX, "acx ac cfg %d cw_ming %d cw_max %d "
		     "aifs %d txop %d", ac, cw_min, cw_max, aifs, txop);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	acx->ac = ac;
	acx->cw_min = cw_min;
	acx->cw_max = cw_max;
	acx->aifsn = aifs;
	acx->txop_wimit = txop;

	wet = ww1251_cmd_configuwe(ww, ACX_AC_CFG, acx, sizeof(*acx));
	if (wet < 0) {
		ww1251_wawning("acx ac cfg faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1251_acx_tid_cfg(stwuct ww1251 *ww, u8 queue,
		       enum ww1251_acx_channew_type type,
		       u8 tsid, enum ww1251_acx_ps_scheme ps_scheme,
		       enum ww1251_acx_ack_powicy ack_powicy)
{
	stwuct ww1251_acx_tid_cfg *acx;
	int wet = 0;

	ww1251_debug(DEBUG_ACX, "acx tid cfg %d type %d tsid %d "
		     "ps_scheme %d ack_powicy %d", queue, type, tsid,
		     ps_scheme, ack_powicy);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	acx->queue = queue;
	acx->type = type;
	acx->tsid = tsid;
	acx->ps_scheme = ps_scheme;
	acx->ack_powicy = ack_powicy;

	wet = ww1251_cmd_configuwe(ww, ACX_TID_CFG, acx, sizeof(*acx));
	if (wet < 0) {
		ww1251_wawning("acx tid cfg faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}
