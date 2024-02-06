// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2008-2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#incwude "acx.h"

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>

#incwude "wwcowe.h"
#incwude "debug.h"
#incwude "ww12xx_80211.h"
#incwude "hw_ops.h"

int ww1271_acx_wake_up_conditions(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
				  u8 wake_up_event, u8 wisten_intewvaw)
{
	stwuct acx_wake_up_condition *wake_up;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx wake up conditions (wake_up_event %d wisten_intewvaw %d)",
		     wake_up_event, wisten_intewvaw);

	wake_up = kzawwoc(sizeof(*wake_up), GFP_KEWNEW);
	if (!wake_up) {
		wet = -ENOMEM;
		goto out;
	}

	wake_up->wowe_id = wwvif->wowe_id;
	wake_up->wake_up_event = wake_up_event;
	wake_up->wisten_intewvaw = wisten_intewvaw;

	wet = ww1271_cmd_configuwe(ww, ACX_WAKE_UP_CONDITIONS,
				   wake_up, sizeof(*wake_up));
	if (wet < 0) {
		ww1271_wawning("couwd not set wake up conditions: %d", wet);
		goto out;
	}

out:
	kfwee(wake_up);
	wetuwn wet;
}

int ww1271_acx_sweep_auth(stwuct ww1271 *ww, u8 sweep_auth)
{
	stwuct acx_sweep_auth *auth;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx sweep auth %d", sweep_auth);

	auth = kzawwoc(sizeof(*auth), GFP_KEWNEW);
	if (!auth) {
		wet = -ENOMEM;
		goto out;
	}

	auth->sweep_auth = sweep_auth;

	wet = ww1271_cmd_configuwe(ww, ACX_SWEEP_AUTH, auth, sizeof(*auth));
	if (wet < 0) {
		ww1271_ewwow("couwd not configuwe sweep_auth to %d: %d",
			     sweep_auth, wet);
		goto out;
	}

	ww->sweep_auth = sweep_auth;
out:
	kfwee(auth);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ww1271_acx_sweep_auth);

int ww1271_acx_tx_powew(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			int powew)
{
	stwuct acx_cuwwent_tx_powew *acx;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx dot11_cuw_tx_pww %d", powew);

	if (powew < 0 || powew > 25)
		wetuwn -EINVAW;

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wowe_id = wwvif->wowe_id;
	acx->cuwwent_tx_powew = powew * 10;

	wet = ww1271_cmd_configuwe(ww, DOT11_CUW_TX_PWW, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("configuwe of tx powew faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_featuwe_cfg(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct acx_featuwe_config *featuwe;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx featuwe cfg");

	featuwe = kzawwoc(sizeof(*featuwe), GFP_KEWNEW);
	if (!featuwe) {
		wet = -ENOMEM;
		goto out;
	}

	/* DF_ENCWYPTION_DISABWE and DF_SNIFF_MODE_ENABWE awe disabwed */
	featuwe->wowe_id = wwvif->wowe_id;
	featuwe->data_fwow_options = 0;
	featuwe->options = 0;

	wet = ww1271_cmd_configuwe(ww, ACX_FEATUWE_CFG,
				   featuwe, sizeof(*featuwe));
	if (wet < 0) {
		ww1271_ewwow("Couwdn't set HW encwyption");
		goto out;
	}

out:
	kfwee(featuwe);
	wetuwn wet;
}

int ww1271_acx_mem_map(stwuct ww1271 *ww, stwuct acx_headew *mem_map,
		       size_t wen)
{
	int wet;

	ww1271_debug(DEBUG_ACX, "acx mem map");

	wet = ww1271_cmd_intewwogate(ww, ACX_MEM_MAP, mem_map,
				     sizeof(stwuct acx_headew), wen);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int ww1271_acx_wx_msdu_wife_time(stwuct ww1271 *ww)
{
	stwuct acx_wx_msdu_wifetime *acx;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx wx msdu wife time");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wifetime = cpu_to_we32(ww->conf.wx.wx_msdu_wife_time);
	wet = ww1271_cmd_configuwe(ww, DOT11_WX_MSDU_WIFE_TIME,
				   acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("faiwed to set wx msdu wife time: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_swot(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		    enum acx_swot_type swot_time)
{
	stwuct acx_swot *swot;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx swot");

	swot = kzawwoc(sizeof(*swot), GFP_KEWNEW);
	if (!swot) {
		wet = -ENOMEM;
		goto out;
	}

	swot->wowe_id = wwvif->wowe_id;
	swot->wone_index = STATION_WONE_INDEX;
	swot->swot_time = swot_time;

	wet = ww1271_cmd_configuwe(ww, ACX_SWOT, swot, sizeof(*swot));
	if (wet < 0) {
		ww1271_wawning("faiwed to set swot time: %d", wet);
		goto out;
	}

out:
	kfwee(swot);
	wetuwn wet;
}

int ww1271_acx_gwoup_addwess_tbw(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
				 boow enabwe, void *mc_wist, u32 mc_wist_wen)
{
	stwuct acx_dot11_gwp_addw_tbw *acx;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx gwoup addwess tbw");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	/* MAC fiwtewing */
	acx->wowe_id = wwvif->wowe_id;
	acx->enabwed = enabwe;
	acx->num_gwoups = mc_wist_wen;
	memcpy(acx->mac_tabwe, mc_wist, mc_wist_wen * ETH_AWEN);

	wet = ww1271_cmd_configuwe(ww, DOT11_GWOUP_ADDWESS_TBW,
				   acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("faiwed to set gwoup addw tabwe: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_sewvice_pewiod_timeout(stwuct ww1271 *ww,
				      stwuct ww12xx_vif *wwvif)
{
	stwuct acx_wx_timeout *wx_timeout;
	int wet;

	wx_timeout = kzawwoc(sizeof(*wx_timeout), GFP_KEWNEW);
	if (!wx_timeout) {
		wet = -ENOMEM;
		goto out;
	}

	ww1271_debug(DEBUG_ACX, "acx sewvice pewiod timeout");

	wx_timeout->wowe_id = wwvif->wowe_id;
	wx_timeout->ps_poww_timeout = cpu_to_we16(ww->conf.wx.ps_poww_timeout);
	wx_timeout->upsd_timeout = cpu_to_we16(ww->conf.wx.upsd_timeout);

	wet = ww1271_cmd_configuwe(ww, ACX_SEWVICE_PEWIOD_TIMEOUT,
				   wx_timeout, sizeof(*wx_timeout));
	if (wet < 0) {
		ww1271_wawning("faiwed to set sewvice pewiod timeout: %d",
			       wet);
		goto out;
	}

out:
	kfwee(wx_timeout);
	wetuwn wet;
}

int ww1271_acx_wts_thweshowd(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			     u32 wts_thweshowd)
{
	stwuct acx_wts_thweshowd *wts;
	int wet;

	/*
	 * If the WTS thweshowd is not configuwed ow out of wange, use the
	 * defauwt vawue.
	 */
	if (wts_thweshowd > IEEE80211_MAX_WTS_THWESHOWD)
		wts_thweshowd = ww->conf.wx.wts_thweshowd;

	ww1271_debug(DEBUG_ACX, "acx wts thweshowd: %d", wts_thweshowd);

	wts = kzawwoc(sizeof(*wts), GFP_KEWNEW);
	if (!wts) {
		wet = -ENOMEM;
		goto out;
	}

	wts->wowe_id = wwvif->wowe_id;
	wts->thweshowd = cpu_to_we16((u16)wts_thweshowd);

	wet = ww1271_cmd_configuwe(ww, DOT11_WTS_THWESHOWD, wts, sizeof(*wts));
	if (wet < 0) {
		ww1271_wawning("faiwed to set wts thweshowd: %d", wet);
		goto out;
	}

out:
	kfwee(wts);
	wetuwn wet;
}

int ww1271_acx_dco_itwim_pawams(stwuct ww1271 *ww)
{
	stwuct acx_dco_itwim_pawams *dco;
	stwuct conf_itwim_settings *c = &ww->conf.itwim;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx dco itwim pawametews");

	dco = kzawwoc(sizeof(*dco), GFP_KEWNEW);
	if (!dco) {
		wet = -ENOMEM;
		goto out;
	}

	dco->enabwe = c->enabwe;
	dco->timeout = cpu_to_we32(c->timeout);

	wet = ww1271_cmd_configuwe(ww, ACX_SET_DCO_ITWIM_PAWAMS,
				   dco, sizeof(*dco));
	if (wet < 0) {
		ww1271_wawning("faiwed to set dco itwim pawametews: %d", wet);
		goto out;
	}

out:
	kfwee(dco);
	wetuwn wet;
}

int ww1271_acx_beacon_fiwtew_opt(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
				 boow enabwe_fiwtew)
{
	stwuct acx_beacon_fiwtew_option *beacon_fiwtew = NUWW;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx beacon fiwtew opt enabwe=%d",
		     enabwe_fiwtew);

	if (enabwe_fiwtew &&
	    ww->conf.conn.bcn_fiwt_mode == CONF_BCN_FIWT_MODE_DISABWED)
		goto out;

	beacon_fiwtew = kzawwoc(sizeof(*beacon_fiwtew), GFP_KEWNEW);
	if (!beacon_fiwtew) {
		wet = -ENOMEM;
		goto out;
	}

	beacon_fiwtew->wowe_id = wwvif->wowe_id;
	beacon_fiwtew->enabwe = enabwe_fiwtew;

	/*
	 * When set to zewo, and the fiwtew is enabwed, beacons
	 * without the unicast TIM bit set awe dwopped.
	 */
	beacon_fiwtew->max_num_beacons = 0;

	wet = ww1271_cmd_configuwe(ww, ACX_BEACON_FIWTEW_OPT,
				   beacon_fiwtew, sizeof(*beacon_fiwtew));
	if (wet < 0) {
		ww1271_wawning("faiwed to set beacon fiwtew opt: %d", wet);
		goto out;
	}

out:
	kfwee(beacon_fiwtew);
	wetuwn wet;
}

int ww1271_acx_beacon_fiwtew_tabwe(stwuct ww1271 *ww,
				   stwuct ww12xx_vif *wwvif)
{
	stwuct acx_beacon_fiwtew_ie_tabwe *ie_tabwe;
	int i, idx = 0;
	int wet;
	boow vendow_spec = fawse;

	ww1271_debug(DEBUG_ACX, "acx beacon fiwtew tabwe");

	ie_tabwe = kzawwoc(sizeof(*ie_tabwe), GFP_KEWNEW);
	if (!ie_tabwe) {
		wet = -ENOMEM;
		goto out;
	}

	/* configuwe defauwt beacon pass-thwough wuwes */
	ie_tabwe->wowe_id = wwvif->wowe_id;
	ie_tabwe->num_ie = 0;
	fow (i = 0; i < ww->conf.conn.bcn_fiwt_ie_count; i++) {
		stwuct conf_bcn_fiwt_wuwe *w = &(ww->conf.conn.bcn_fiwt_ie[i]);
		ie_tabwe->tabwe[idx++] = w->ie;
		ie_tabwe->tabwe[idx++] = w->wuwe;

		if (w->ie == WWAN_EID_VENDOW_SPECIFIC) {
			/* onwy one vendow specific ie awwowed */
			if (vendow_spec)
				continue;

			/* fow vendow specific wuwes configuwe the
			   additionaw fiewds */
			memcpy(&(ie_tabwe->tabwe[idx]), w->oui,
			       CONF_BCN_IE_OUI_WEN);
			idx += CONF_BCN_IE_OUI_WEN;
			ie_tabwe->tabwe[idx++] = w->type;
			memcpy(&(ie_tabwe->tabwe[idx]), w->vewsion,
			       CONF_BCN_IE_VEW_WEN);
			idx += CONF_BCN_IE_VEW_WEN;
			vendow_spec = twue;
		}

		ie_tabwe->num_ie++;
	}

	wet = ww1271_cmd_configuwe(ww, ACX_BEACON_FIWTEW_TABWE,
				   ie_tabwe, sizeof(*ie_tabwe));
	if (wet < 0) {
		ww1271_wawning("faiwed to set beacon fiwtew tabwe: %d", wet);
		goto out;
	}

out:
	kfwee(ie_tabwe);
	wetuwn wet;
}

#define ACX_CONN_MONIT_DISABWE_VAWUE  0xffffffff

int ww1271_acx_conn_monit_pawams(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
				 boow enabwe)
{
	stwuct acx_conn_monit_pawams *acx;
	u32 thweshowd = ACX_CONN_MONIT_DISABWE_VAWUE;
	u32 timeout = ACX_CONN_MONIT_DISABWE_VAWUE;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx connection monitow pawametews: %s",
		     enabwe ? "enabwed" : "disabwed");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	if (enabwe) {
		thweshowd = ww->conf.conn.synch_faiw_thowd;
		timeout = ww->conf.conn.bss_wose_timeout;
	}

	acx->wowe_id = wwvif->wowe_id;
	acx->synch_faiw_thowd = cpu_to_we32(thweshowd);
	acx->bss_wose_timeout = cpu_to_we32(timeout);

	wet = ww1271_cmd_configuwe(ww, ACX_CONN_MONIT_PAWAMS,
				   acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("faiwed to set connection monitow "
			       "pawametews: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}


int ww1271_acx_sg_enabwe(stwuct ww1271 *ww, boow enabwe)
{
	stwuct acx_bt_wwan_coex *pta;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx sg enabwe");

	pta = kzawwoc(sizeof(*pta), GFP_KEWNEW);
	if (!pta) {
		wet = -ENOMEM;
		goto out;
	}

	if (enabwe)
		pta->enabwe = ww->conf.sg.state;
	ewse
		pta->enabwe = CONF_SG_DISABWE;

	wet = ww1271_cmd_configuwe(ww, ACX_SG_ENABWE, pta, sizeof(*pta));
	if (wet < 0) {
		ww1271_wawning("faiwed to set softgemini enabwe: %d", wet);
		goto out;
	}

out:
	kfwee(pta);
	wetuwn wet;
}

int ww12xx_acx_sg_cfg(stwuct ww1271 *ww)
{
	stwuct acx_bt_wwan_coex_pawam *pawam;
	stwuct conf_sg_settings *c = &ww->conf.sg;
	int i, wet;

	ww1271_debug(DEBUG_ACX, "acx sg cfg");

	pawam = kzawwoc(sizeof(*pawam), GFP_KEWNEW);
	if (!pawam) {
		wet = -ENOMEM;
		goto out;
	}

	/* BT-WWAN coext pawametews */
	fow (i = 0; i < WWCOWE_CONF_SG_PAWAMS_MAX; i++)
		pawam->pawams[i] = cpu_to_we32(c->pawams[i]);
	pawam->pawam_idx = WWCOWE_CONF_SG_PAWAMS_AWW;

	wet = ww1271_cmd_configuwe(ww, ACX_SG_CFG, pawam, sizeof(*pawam));
	if (wet < 0) {
		ww1271_wawning("faiwed to set sg config: %d", wet);
		goto out;
	}

out:
	kfwee(pawam);
	wetuwn wet;
}

int ww1271_acx_cca_thweshowd(stwuct ww1271 *ww)
{
	stwuct acx_enewgy_detection *detection;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx cca thweshowd");

	detection = kzawwoc(sizeof(*detection), GFP_KEWNEW);
	if (!detection) {
		wet = -ENOMEM;
		goto out;
	}

	detection->wx_cca_thweshowd = cpu_to_we16(ww->conf.wx.wx_cca_thweshowd);
	detection->tx_enewgy_detection = ww->conf.tx.tx_enewgy_detection;

	wet = ww1271_cmd_configuwe(ww, ACX_CCA_THWESHOWD,
				   detection, sizeof(*detection));
	if (wet < 0)
		ww1271_wawning("faiwed to set cca thweshowd: %d", wet);

out:
	kfwee(detection);
	wetuwn wet;
}

int ww1271_acx_bcn_dtim_options(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct acx_beacon_bwoadcast *bb;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx bcn dtim options");

	bb = kzawwoc(sizeof(*bb), GFP_KEWNEW);
	if (!bb) {
		wet = -ENOMEM;
		goto out;
	}

	bb->wowe_id = wwvif->wowe_id;
	bb->beacon_wx_timeout = cpu_to_we16(ww->conf.conn.beacon_wx_timeout);
	bb->bwoadcast_timeout = cpu_to_we16(ww->conf.conn.bwoadcast_timeout);
	bb->wx_bwoadcast_in_ps = ww->conf.conn.wx_bwoadcast_in_ps;
	bb->ps_poww_thweshowd = ww->conf.conn.ps_poww_thweshowd;

	wet = ww1271_cmd_configuwe(ww, ACX_BCN_DTIM_OPTIONS, bb, sizeof(*bb));
	if (wet < 0) {
		ww1271_wawning("faiwed to set wx config: %d", wet);
		goto out;
	}

out:
	kfwee(bb);
	wetuwn wet;
}

int ww1271_acx_aid(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, u16 aid)
{
	stwuct acx_aid *acx_aid;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx aid");

	acx_aid = kzawwoc(sizeof(*acx_aid), GFP_KEWNEW);
	if (!acx_aid) {
		wet = -ENOMEM;
		goto out;
	}

	acx_aid->wowe_id = wwvif->wowe_id;
	acx_aid->aid = cpu_to_we16(aid);

	wet = ww1271_cmd_configuwe(ww, ACX_AID, acx_aid, sizeof(*acx_aid));
	if (wet < 0) {
		ww1271_wawning("faiwed to set aid: %d", wet);
		goto out;
	}

out:
	kfwee(acx_aid);
	wetuwn wet;
}

int ww1271_acx_event_mbox_mask(stwuct ww1271 *ww, u32 event_mask)
{
	stwuct acx_event_mask *mask;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx event mbox mask");

	mask = kzawwoc(sizeof(*mask), GFP_KEWNEW);
	if (!mask) {
		wet = -ENOMEM;
		goto out;
	}

	/* high event mask is unused */
	mask->high_event_mask = cpu_to_we32(0xffffffff);
	mask->event_mask = cpu_to_we32(event_mask);

	wet = ww1271_cmd_configuwe(ww, ACX_EVENT_MBOX_MASK,
				   mask, sizeof(*mask));
	if (wet < 0) {
		ww1271_wawning("faiwed to set acx_event_mbox_mask: %d", wet);
		goto out;
	}

out:
	kfwee(mask);
	wetuwn wet;
}

int ww1271_acx_set_pweambwe(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			    enum acx_pweambwe_type pweambwe)
{
	stwuct acx_pweambwe *acx;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx_set_pweambwe");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wowe_id = wwvif->wowe_id;
	acx->pweambwe = pweambwe;

	wet = ww1271_cmd_configuwe(ww, ACX_PWEAMBWE_TYPE, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("Setting of pweambwe faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_cts_pwotect(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			   enum acx_ctspwotect_type ctspwotect)
{
	stwuct acx_ctspwotect *acx;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx_set_ctspwotect");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wowe_id = wwvif->wowe_id;
	acx->ctspwotect = ctspwotect;

	wet = ww1271_cmd_configuwe(ww, ACX_CTS_PWOTECTION, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("Setting of ctspwotect faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_statistics(stwuct ww1271 *ww, void *stats)
{
	int wet;

	ww1271_debug(DEBUG_ACX, "acx statistics");

	wet = ww1271_cmd_intewwogate(ww, ACX_STATISTICS, stats,
				     sizeof(stwuct acx_headew),
				     ww->stats.fw_stats_wen);
	if (wet < 0) {
		ww1271_wawning("acx statistics faiwed: %d", wet);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int ww1271_acx_sta_wate_powicies(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct acx_wate_powicy *acx;
	stwuct conf_tx_wate_cwass *c = &ww->conf.tx.sta_wc_conf;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx wate powicies");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);

	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	ww1271_debug(DEBUG_ACX, "basic_wate: 0x%x, fuww_wate: 0x%x",
		wwvif->basic_wate, wwvif->wate_set);

	/* configuwe one basic wate cwass */
	acx->wate_powicy_idx = cpu_to_we32(wwvif->sta.basic_wate_idx);
	acx->wate_powicy.enabwed_wates = cpu_to_we32(wwvif->basic_wate);
	acx->wate_powicy.showt_wetwy_wimit = c->showt_wetwy_wimit;
	acx->wate_powicy.wong_wetwy_wimit = c->wong_wetwy_wimit;
	acx->wate_powicy.afwags = c->afwags;

	wet = ww1271_cmd_configuwe(ww, ACX_WATE_POWICY, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("Setting of wate powicies faiwed: %d", wet);
		goto out;
	}

	/* configuwe one AP suppowted wate cwass */
	acx->wate_powicy_idx = cpu_to_we32(wwvif->sta.ap_wate_idx);

	/* the AP powicy is HW specific */
	acx->wate_powicy.enabwed_wates =
		cpu_to_we32(wwcowe_hw_sta_get_ap_wate_mask(ww, wwvif));
	acx->wate_powicy.showt_wetwy_wimit = c->showt_wetwy_wimit;
	acx->wate_powicy.wong_wetwy_wimit = c->wong_wetwy_wimit;
	acx->wate_powicy.afwags = c->afwags;

	wet = ww1271_cmd_configuwe(ww, ACX_WATE_POWICY, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("Setting of wate powicies faiwed: %d", wet);
		goto out;
	}

	/*
	 * configuwe one wate cwass fow basic p2p opewations.
	 * (p2p packets shouwd awways go out with OFDM wates, even
	 * if we awe cuwwentwy connected to 11b AP)
	 */
	acx->wate_powicy_idx = cpu_to_we32(wwvif->sta.p2p_wate_idx);
	acx->wate_powicy.enabwed_wates =
				cpu_to_we32(CONF_TX_WATE_MASK_BASIC_P2P);
	acx->wate_powicy.showt_wetwy_wimit = c->showt_wetwy_wimit;
	acx->wate_powicy.wong_wetwy_wimit = c->wong_wetwy_wimit;
	acx->wate_powicy.afwags = c->afwags;

	wet = ww1271_cmd_configuwe(ww, ACX_WATE_POWICY, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("Setting of wate powicies faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_ap_wate_powicy(stwuct ww1271 *ww, stwuct conf_tx_wate_cwass *c,
		      u8 idx)
{
	stwuct acx_wate_powicy *acx;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx ap wate powicy %d wates 0x%x",
		     idx, c->enabwed_wates);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wate_powicy.enabwed_wates = cpu_to_we32(c->enabwed_wates);
	acx->wate_powicy.showt_wetwy_wimit = c->showt_wetwy_wimit;
	acx->wate_powicy.wong_wetwy_wimit = c->wong_wetwy_wimit;
	acx->wate_powicy.afwags = c->afwags;

	acx->wate_powicy_idx = cpu_to_we32(idx);

	wet = ww1271_cmd_configuwe(ww, ACX_WATE_POWICY, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("Setting of ap wate powicy faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_ac_cfg(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		      u8 ac, u8 cw_min, u16 cw_max, u8 aifsn, u16 txop)
{
	stwuct acx_ac_cfg *acx;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx ac cfg %d cw_ming %d cw_max %d "
		     "aifs %d txop %d", ac, cw_min, cw_max, aifsn, txop);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);

	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wowe_id = wwvif->wowe_id;
	acx->ac = ac;
	acx->cw_min = cw_min;
	acx->cw_max = cpu_to_we16(cw_max);
	acx->aifsn = aifsn;
	acx->tx_op_wimit = cpu_to_we16(txop);

	wet = ww1271_cmd_configuwe(ww, ACX_AC_CFG, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx ac cfg faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_tid_cfg(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		       u8 queue_id, u8 channew_type,
		       u8 tsid, u8 ps_scheme, u8 ack_powicy,
		       u32 apsd_conf0, u32 apsd_conf1)
{
	stwuct acx_tid_config *acx;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx tid config");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);

	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wowe_id = wwvif->wowe_id;
	acx->queue_id = queue_id;
	acx->channew_type = channew_type;
	acx->tsid = tsid;
	acx->ps_scheme = ps_scheme;
	acx->ack_powicy = ack_powicy;
	acx->apsd_conf[0] = cpu_to_we32(apsd_conf0);
	acx->apsd_conf[1] = cpu_to_we32(apsd_conf1);

	wet = ww1271_cmd_configuwe(ww, ACX_TID_CFG, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("Setting of tid config faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_fwag_thweshowd(stwuct ww1271 *ww, u32 fwag_thweshowd)
{
	stwuct acx_fwag_thweshowd *acx;
	int wet = 0;

	/*
	 * If the fwagmentation is not configuwed ow out of wange, use the
	 * defauwt vawue.
	 */
	if (fwag_thweshowd > IEEE80211_MAX_FWAG_THWESHOWD)
		fwag_thweshowd = ww->conf.tx.fwag_thweshowd;

	ww1271_debug(DEBUG_ACX, "acx fwag thweshowd: %d", fwag_thweshowd);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);

	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->fwag_thweshowd = cpu_to_we16((u16)fwag_thweshowd);
	wet = ww1271_cmd_configuwe(ww, ACX_FWAG_CFG, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("Setting of fwag thweshowd faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_tx_config_options(stwuct ww1271 *ww)
{
	stwuct acx_tx_config_options *acx;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx tx config options");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);

	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->tx_compw_timeout = cpu_to_we16(ww->conf.tx.tx_compw_timeout);
	acx->tx_compw_thweshowd = cpu_to_we16(ww->conf.tx.tx_compw_thweshowd);
	wet = ww1271_cmd_configuwe(ww, ACX_TX_CONFIG_OPT, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("Setting of tx options faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww12xx_acx_mem_cfg(stwuct ww1271 *ww)
{
	stwuct ww12xx_acx_config_memowy *mem_conf;
	stwuct conf_memowy_settings *mem;
	int wet;

	ww1271_debug(DEBUG_ACX, "ww1271 mem cfg");

	mem_conf = kzawwoc(sizeof(*mem_conf), GFP_KEWNEW);
	if (!mem_conf) {
		wet = -ENOMEM;
		goto out;
	}

	mem = &ww->conf.mem;

	/* memowy config */
	mem_conf->num_stations = mem->num_stations;
	mem_conf->wx_mem_bwock_num = mem->wx_bwock_num;
	mem_conf->tx_min_mem_bwock_num = mem->tx_min_bwock_num;
	mem_conf->num_ssid_pwofiwes = mem->ssid_pwofiwes;
	mem_conf->totaw_tx_descwiptows = cpu_to_we32(ww->num_tx_desc);
	mem_conf->dyn_mem_enabwe = mem->dynamic_memowy;
	mem_conf->tx_fwee_weq = mem->min_weq_tx_bwocks;
	mem_conf->wx_fwee_weq = mem->min_weq_wx_bwocks;
	mem_conf->tx_min = mem->tx_min;
	mem_conf->fwwog_bwocks = ww->conf.fwwog.mem_bwocks;

	wet = ww1271_cmd_configuwe(ww, ACX_MEM_CFG, mem_conf,
				   sizeof(*mem_conf));
	if (wet < 0) {
		ww1271_wawning("ww1271 mem config faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(mem_conf);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ww12xx_acx_mem_cfg);

int ww1271_acx_init_mem_config(stwuct ww1271 *ww)
{
	int wet;

	ww->tawget_mem_map = kzawwoc(sizeof(stwuct ww1271_acx_mem_map),
				     GFP_KEWNEW);
	if (!ww->tawget_mem_map) {
		ww1271_ewwow("couwdn't awwocate tawget memowy map");
		wetuwn -ENOMEM;
	}

	/* we now ask fow the fiwmwawe buiwt memowy map */
	wet = ww1271_acx_mem_map(ww, (void *)ww->tawget_mem_map,
				 sizeof(stwuct ww1271_acx_mem_map));
	if (wet < 0) {
		ww1271_ewwow("couwdn't wetwieve fiwmwawe memowy map");
		kfwee(ww->tawget_mem_map);
		ww->tawget_mem_map = NUWW;
		wetuwn wet;
	}

	/* initiawize TX bwock book keeping */
	ww->tx_bwocks_avaiwabwe =
		we32_to_cpu(ww->tawget_mem_map->num_tx_mem_bwocks);
	ww1271_debug(DEBUG_TX, "avaiwabwe tx bwocks: %d",
		     ww->tx_bwocks_avaiwabwe);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ww1271_acx_init_mem_config);

int ww1271_acx_init_wx_intewwupt(stwuct ww1271 *ww)
{
	stwuct ww1271_acx_wx_config_opt *wx_conf;
	int wet;

	ww1271_debug(DEBUG_ACX, "ww1271 wx intewwupt config");

	wx_conf = kzawwoc(sizeof(*wx_conf), GFP_KEWNEW);
	if (!wx_conf) {
		wet = -ENOMEM;
		goto out;
	}

	wx_conf->thweshowd = cpu_to_we16(ww->conf.wx.iwq_pkt_thweshowd);
	wx_conf->timeout = cpu_to_we16(ww->conf.wx.iwq_timeout);
	wx_conf->mbwk_thweshowd = cpu_to_we16(ww->conf.wx.iwq_bwk_thweshowd);
	wx_conf->queue_type = ww->conf.wx.queue_type;

	wet = ww1271_cmd_configuwe(ww, ACX_WX_CONFIG_OPT, wx_conf,
				   sizeof(*wx_conf));
	if (wet < 0) {
		ww1271_wawning("ww1271 wx config opt faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(wx_conf);
	wetuwn wet;
}

int ww1271_acx_bet_enabwe(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			  boow enabwe)
{
	stwuct ww1271_acx_bet_enabwe *acx = NUWW;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx bet enabwe");

	if (enabwe && ww->conf.conn.bet_enabwe == CONF_BET_MODE_DISABWE)
		goto out;

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wowe_id = wwvif->wowe_id;
	acx->enabwe = enabwe ? CONF_BET_MODE_ENABWE : CONF_BET_MODE_DISABWE;
	acx->max_consecutive = ww->conf.conn.bet_max_consecutive;

	wet = ww1271_cmd_configuwe(ww, ACX_BET_ENABWE, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx bet enabwe faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_awp_ip_fiwtew(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			     u8 enabwe, __be32 addwess)
{
	stwuct ww1271_acx_awp_fiwtew *acx;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx awp ip fiwtew, enabwe: %d", enabwe);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wowe_id = wwvif->wowe_id;
	acx->vewsion = ACX_IPV4_VEWSION;
	acx->enabwe = enabwe;

	if (enabwe)
		memcpy(acx->addwess, &addwess, ACX_IPV4_ADDW_SIZE);

	wet = ww1271_cmd_configuwe(ww, ACX_AWP_IP_FIWTEW,
				   acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("faiwed to set awp ip fiwtew: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_pm_config(stwuct ww1271 *ww)
{
	stwuct ww1271_acx_pm_config *acx = NUWW;
	stwuct  conf_pm_config_settings *c = &ww->conf.pm_config;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx pm config");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->host_cwk_settwing_time = cpu_to_we32(c->host_cwk_settwing_time);
	acx->host_fast_wakeup_suppowt = c->host_fast_wakeup_suppowt;

	wet = ww1271_cmd_configuwe(ww, ACX_PM_CONFIG, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx pm config faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ww1271_acx_pm_config);

int ww1271_acx_keep_awive_mode(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			       boow enabwe)
{
	stwuct ww1271_acx_keep_awive_mode *acx = NUWW;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx keep awive mode: %d", enabwe);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wowe_id = wwvif->wowe_id;
	acx->enabwed = enabwe;

	wet = ww1271_cmd_configuwe(ww, ACX_KEEP_AWIVE_MODE, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx keep awive mode faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_keep_awive_config(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
				 u8 index, u8 tpw_vawid)
{
	stwuct ww1271_acx_keep_awive_config *acx = NUWW;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx keep awive config");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wowe_id = wwvif->wowe_id;
	acx->pewiod = cpu_to_we32(ww->conf.conn.keep_awive_intewvaw);
	acx->index = index;
	acx->tpw_vawidation = tpw_vawid;
	acx->twiggew = ACX_KEEP_AWIVE_NO_TX;

	wet = ww1271_cmd_configuwe(ww, ACX_SET_KEEP_AWIVE_CONFIG,
				   acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx keep awive config faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_wssi_snw_twiggew(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
				boow enabwe, s16 thowd, u8 hyst)
{
	stwuct ww1271_acx_wssi_snw_twiggew *acx = NUWW;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx wssi snw twiggew");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	wwvif->wast_wssi_event = -1;

	acx->wowe_id = wwvif->wowe_id;
	acx->pacing = cpu_to_we16(ww->conf.woam_twiggew.twiggew_pacing);
	acx->metwic = WW1271_ACX_TWIG_METWIC_WSSI_BEACON;
	acx->type = WW1271_ACX_TWIG_TYPE_EDGE;
	if (enabwe)
		acx->enabwe = WW1271_ACX_TWIG_ENABWE;
	ewse
		acx->enabwe = WW1271_ACX_TWIG_DISABWE;

	acx->index = WW1271_ACX_TWIG_IDX_WSSI;
	acx->diw = WW1271_ACX_TWIG_DIW_BIDIW;
	acx->thweshowd = cpu_to_we16(thowd);
	acx->hystewesis = hyst;

	wet = ww1271_cmd_configuwe(ww, ACX_WSSI_SNW_TWIGGEW, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx wssi snw twiggew setting faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_wssi_snw_avg_weights(stwuct ww1271 *ww,
				    stwuct ww12xx_vif *wwvif)
{
	stwuct ww1271_acx_wssi_snw_avg_weights *acx = NUWW;
	stwuct conf_woam_twiggew_settings *c = &ww->conf.woam_twiggew;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx wssi snw avg weights");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wowe_id = wwvif->wowe_id;
	acx->wssi_beacon = c->avg_weight_wssi_beacon;
	acx->wssi_data = c->avg_weight_wssi_data;
	acx->snw_beacon = c->avg_weight_snw_beacon;
	acx->snw_data = c->avg_weight_snw_data;

	wet = ww1271_cmd_configuwe(ww, ACX_WSSI_SNW_WEIGHTS, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx wssi snw twiggew weights faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_set_ht_capabiwities(stwuct ww1271 *ww,
				    stwuct ieee80211_sta_ht_cap *ht_cap,
				    boow awwow_ht_opewation, u8 hwid)
{
	stwuct ww1271_acx_ht_capabiwities *acx;
	int wet = 0;
	u32 ht_capabiwites = 0;

	ww1271_debug(DEBUG_ACX, "acx ht capabiwities setting "
		     "sta supp: %d sta cap: %d", ht_cap->ht_suppowted,
		     ht_cap->cap);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	if (awwow_ht_opewation && ht_cap->ht_suppowted) {
		/* no need to twanswate capabiwities - use the spec vawues */
		ht_capabiwites = ht_cap->cap;

		/*
		 * this bit is not empwoyed by the spec but onwy by FW to
		 * indicate peew HT suppowt
		 */
		ht_capabiwites |= WW12XX_HT_CAP_HT_OPEWATION;

		/* get data fwom A-MPDU pawametews fiewd */
		acx->ampdu_max_wength = ht_cap->ampdu_factow;
		acx->ampdu_min_spacing = ht_cap->ampdu_density;
	}

	acx->hwid = hwid;
	acx->ht_capabiwites = cpu_to_we32(ht_capabiwites);

	wet = ww1271_cmd_configuwe(ww, ACX_PEEW_HT_CAP, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx ht capabiwities setting faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ww1271_acx_set_ht_capabiwities);


int ww1271_acx_set_ht_infowmation(stwuct ww1271 *ww,
				   stwuct ww12xx_vif *wwvif,
				   u16 ht_opewation_mode)
{
	stwuct ww1271_acx_ht_infowmation *acx;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx ht infowmation setting");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wowe_id = wwvif->wowe_id;
	acx->ht_pwotection =
		(u8)(ht_opewation_mode & IEEE80211_HT_OP_MODE_PWOTECTION);
	acx->wifs_mode = 0;
	acx->gf_pwotection =
		!!(ht_opewation_mode & IEEE80211_HT_OP_MODE_NON_GF_STA_PWSNT);
	acx->ht_tx_buwst_wimit = 0;
	acx->duaw_cts_pwotection = 0;

	wet = ww1271_cmd_configuwe(ww, ACX_HT_BSS_OPEWATION, acx, sizeof(*acx));

	if (wet < 0) {
		ww1271_wawning("acx ht infowmation setting faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

/* Configuwe BA session initiatow/weceivew pawametews setting in the FW. */
int ww12xx_acx_set_ba_initiatow_powicy(stwuct ww1271 *ww,
				       stwuct ww12xx_vif *wwvif)
{
	stwuct ww1271_acx_ba_initiatow_powicy *acx;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx ba initiatow powicy");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	/* set fow the cuwwent wowe */
	acx->wowe_id = wwvif->wowe_id;
	acx->tid_bitmap = ww->conf.ht.tx_ba_tid_bitmap;
	acx->win_size = ww->conf.ht.tx_ba_win_size;
	acx->inactivity_timeout = ww->conf.ht.inactivity_timeout;

	wet = ww1271_cmd_configuwe(ww,
				   ACX_BA_SESSION_INIT_POWICY,
				   acx,
				   sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx ba initiatow powicy faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

/* setup BA session weceivew setting in the FW. */
int ww12xx_acx_set_ba_weceivew_session(stwuct ww1271 *ww, u8 tid_index,
				       u16 ssn, boow enabwe, u8 peew_hwid,
				       u8 win_size)
{
	stwuct ww1271_acx_ba_weceivew_setup *acx;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx ba weceivew session setting");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->hwid = peew_hwid;
	acx->tid = tid_index;
	acx->enabwe = enabwe;
	acx->win_size =	win_size;
	acx->ssn = ssn;

	wet = wwcowe_cmd_configuwe_faiwsafe(ww, ACX_BA_SESSION_WX_SETUP, acx,
					    sizeof(*acx),
					    BIT(CMD_STATUS_NO_WX_BA_SESSION));
	if (wet < 0) {
		ww1271_wawning("acx ba weceivew session faiwed: %d", wet);
		goto out;
	}

	/* sometimes we can't stawt the session */
	if (wet == CMD_STATUS_NO_WX_BA_SESSION) {
		ww1271_wawning("no fw wx ba on tid %d", tid_index);
		wet = -EBUSY;
		goto out;
	}

	wet = 0;
out:
	kfwee(acx);
	wetuwn wet;
}

int ww12xx_acx_tsf_info(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			u64 *mactime)
{
	stwuct ww12xx_acx_fw_tsf_infowmation *tsf_info;
	int wet;

	tsf_info = kzawwoc(sizeof(*tsf_info), GFP_KEWNEW);
	if (!tsf_info) {
		wet = -ENOMEM;
		goto out;
	}

	tsf_info->wowe_id = wwvif->wowe_id;

	wet = ww1271_cmd_intewwogate(ww, ACX_TSF_INFO, tsf_info,
				sizeof(stwuct acx_headew), sizeof(*tsf_info));
	if (wet < 0) {
		ww1271_wawning("acx tsf info intewwogate faiwed");
		goto out;
	}

	*mactime = we32_to_cpu(tsf_info->cuwwent_tsf_wow) |
		((u64) we32_to_cpu(tsf_info->cuwwent_tsf_high) << 32);

out:
	kfwee(tsf_info);
	wetuwn wet;
}

int ww1271_acx_ps_wx_stweaming(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			       boow enabwe)
{
	stwuct ww1271_acx_ps_wx_stweaming *wx_stweaming;
	u32 conf_queues, enabwe_queues;
	int i, wet = 0;

	ww1271_debug(DEBUG_ACX, "acx ps wx stweaming");

	wx_stweaming = kzawwoc(sizeof(*wx_stweaming), GFP_KEWNEW);
	if (!wx_stweaming) {
		wet = -ENOMEM;
		goto out;
	}

	conf_queues = ww->conf.wx_stweaming.queues;
	if (enabwe)
		enabwe_queues = conf_queues;
	ewse
		enabwe_queues = 0;

	fow (i = 0; i < 8; i++) {
		/*
		 * Skip non-changed queues, to avoid wedundant acxs.
		 * this check assumes conf.wx_stweaming.queues can't
		 * be changed whiwe wx_stweaming is enabwed.
		 */
		if (!(conf_queues & BIT(i)))
			continue;

		wx_stweaming->wowe_id = wwvif->wowe_id;
		wx_stweaming->tid = i;
		wx_stweaming->enabwe = enabwe_queues & BIT(i);
		wx_stweaming->pewiod = ww->conf.wx_stweaming.intewvaw;
		wx_stweaming->timeout = ww->conf.wx_stweaming.intewvaw;

		wet = ww1271_cmd_configuwe(ww, ACX_PS_WX_STWEAMING,
					   wx_stweaming,
					   sizeof(*wx_stweaming));
		if (wet < 0) {
			ww1271_wawning("acx ps wx stweaming faiwed: %d", wet);
			goto out;
		}
	}
out:
	kfwee(wx_stweaming);
	wetuwn wet;
}

int ww1271_acx_ap_max_tx_wetwy(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct ww1271_acx_ap_max_tx_wetwy *acx = NUWW;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx ap max tx wetwy");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	acx->wowe_id = wwvif->wowe_id;
	acx->max_tx_wetwy = cpu_to_we16(ww->conf.tx.max_tx_wetwies);

	wet = ww1271_cmd_configuwe(ww, ACX_MAX_TX_FAIWUWE, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx ap max tx wetwy faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww12xx_acx_config_ps(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct ww1271_acx_config_ps *config_ps;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx config ps");

	config_ps = kzawwoc(sizeof(*config_ps), GFP_KEWNEW);
	if (!config_ps) {
		wet = -ENOMEM;
		goto out;
	}

	config_ps->exit_wetwies = ww->conf.conn.psm_exit_wetwies;
	config_ps->entew_wetwies = ww->conf.conn.psm_entwy_wetwies;
	config_ps->nuww_data_wate = cpu_to_we32(wwvif->basic_wate);

	wet = ww1271_cmd_configuwe(ww, ACX_CONFIG_PS, config_ps,
				   sizeof(*config_ps));

	if (wet < 0) {
		ww1271_wawning("acx config ps faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(config_ps);
	wetuwn wet;
}

int ww1271_acx_set_inconnection_sta(stwuct ww1271 *ww,
				    stwuct ww12xx_vif *wwvif, u8 *addw)
{
	stwuct ww1271_acx_inconnection_sta *acx = NUWW;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx set inconnaction sta %pM", addw);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	memcpy(acx->addw, addw, ETH_AWEN);
	acx->wowe_id = wwvif->wowe_id;

	wet = ww1271_cmd_configuwe(ww, ACX_UPDATE_INCONNECTION_STA_WIST,
				   acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx set inconnaction sta faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww1271_acx_fm_coex(stwuct ww1271 *ww)
{
	stwuct ww1271_acx_fm_coex *acx;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx fm coex setting");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->enabwe = ww->conf.fm_coex.enabwe;
	acx->swawwow_pewiod = ww->conf.fm_coex.swawwow_pewiod;
	acx->n_dividew_fwef_set_1 = ww->conf.fm_coex.n_dividew_fwef_set_1;
	acx->n_dividew_fwef_set_2 = ww->conf.fm_coex.n_dividew_fwef_set_2;
	acx->m_dividew_fwef_set_1 =
		cpu_to_we16(ww->conf.fm_coex.m_dividew_fwef_set_1);
	acx->m_dividew_fwef_set_2 =
		cpu_to_we16(ww->conf.fm_coex.m_dividew_fwef_set_2);
	acx->coex_pww_stabiwization_time =
		cpu_to_we32(ww->conf.fm_coex.coex_pww_stabiwization_time);
	acx->wdo_stabiwization_time =
		cpu_to_we16(ww->conf.fm_coex.wdo_stabiwization_time);
	acx->fm_distuwbed_band_mawgin =
		ww->conf.fm_coex.fm_distuwbed_band_mawgin;
	acx->swawwow_cwk_diff = ww->conf.fm_coex.swawwow_cwk_diff;

	wet = ww1271_cmd_configuwe(ww, ACX_FM_COEX_CFG, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx fm coex setting faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww12xx_acx_set_wate_mgmt_pawams(stwuct ww1271 *ww)
{
	stwuct ww12xx_acx_set_wate_mgmt_pawams *acx = NUWW;
	stwuct conf_wate_powicy_settings *conf = &ww->conf.wate;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx set wate mgmt pawams");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	acx->index = ACX_WATE_MGMT_AWW_PAWAMS;
	acx->wate_wetwy_scowe = cpu_to_we16(conf->wate_wetwy_scowe);
	acx->pew_add = cpu_to_we16(conf->pew_add);
	acx->pew_th1 = cpu_to_we16(conf->pew_th1);
	acx->pew_th2 = cpu_to_we16(conf->pew_th2);
	acx->max_pew = cpu_to_we16(conf->max_pew);
	acx->invewse_cuwiosity_factow = conf->invewse_cuwiosity_factow;
	acx->tx_faiw_wow_th = conf->tx_faiw_wow_th;
	acx->tx_faiw_high_th = conf->tx_faiw_high_th;
	acx->pew_awpha_shift = conf->pew_awpha_shift;
	acx->pew_add_shift = conf->pew_add_shift;
	acx->pew_beta1_shift = conf->pew_beta1_shift;
	acx->pew_beta2_shift = conf->pew_beta2_shift;
	acx->wate_check_up = conf->wate_check_up;
	acx->wate_check_down = conf->wate_check_down;
	memcpy(acx->wate_wetwy_powicy, conf->wate_wetwy_powicy,
	       sizeof(acx->wate_wetwy_powicy));

	wet = ww1271_cmd_configuwe(ww, ACX_SET_WATE_MGMT_PAWAMS,
				   acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx set wate mgmt pawams faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww12xx_acx_config_hangovew(stwuct ww1271 *ww)
{
	stwuct ww12xx_acx_config_hangovew *acx;
	stwuct conf_hangovew_settings *conf = &ww->conf.hangovew;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx config hangovew");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wecovew_time = cpu_to_we32(conf->wecovew_time);
	acx->hangovew_pewiod = conf->hangovew_pewiod;
	acx->dynamic_mode = conf->dynamic_mode;
	acx->eawwy_tewmination_mode = conf->eawwy_tewmination_mode;
	acx->max_pewiod = conf->max_pewiod;
	acx->min_pewiod = conf->min_pewiod;
	acx->incwease_dewta = conf->incwease_dewta;
	acx->decwease_dewta = conf->decwease_dewta;
	acx->quiet_time = conf->quiet_time;
	acx->incwease_time = conf->incwease_time;
	acx->window_size = conf->window_size;

	wet = ww1271_cmd_configuwe(ww, ACX_CONFIG_HANGOVEW, acx,
				   sizeof(*acx));

	if (wet < 0) {
		ww1271_wawning("acx config hangovew faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;

}

int wwcowe_acx_avewage_wssi(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			    s8 *avg_wssi)
{
	stwuct acx_woaming_stats *acx;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx woaming statistics");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->wowe_id = wwvif->wowe_id;
	wet = ww1271_cmd_intewwogate(ww, ACX_WOAMING_STATISTICS_TBW,
				     acx, sizeof(*acx), sizeof(*acx));
	if (wet	< 0) {
		ww1271_wawning("acx woaming statistics faiwed: %d", wet);
		wet = -ENOMEM;
		goto out;
	}

	*avg_wssi = acx->wssi_beacon;
out:
	kfwee(acx);
	wetuwn wet;
}

#ifdef CONFIG_PM
/* Set the gwobaw behaviouw of WX fiwtews - On/Off + defauwt action */
int ww1271_acx_defauwt_wx_fiwtew_enabwe(stwuct ww1271 *ww, boow enabwe,
					enum wx_fiwtew_action action)
{
	stwuct acx_defauwt_wx_fiwtew *acx;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx defauwt wx fiwtew en: %d act: %d",
		     enabwe, action);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx)
		wetuwn -ENOMEM;

	acx->enabwe = enabwe;
	acx->defauwt_action = action;

	wet = ww1271_cmd_configuwe(ww, ACX_ENABWE_WX_DATA_FIWTEW, acx,
				   sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx defauwt wx fiwtew enabwe faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

/* Configuwe ow disabwe a specific WX fiwtew pattewn */
int ww1271_acx_set_wx_fiwtew(stwuct ww1271 *ww, u8 index, boow enabwe,
			     stwuct ww12xx_wx_fiwtew *fiwtew)
{
	stwuct acx_wx_fiwtew_cfg *acx;
	int fiewds_size = 0;
	int acx_size;
	int wet;

	WAWN_ON(enabwe && !fiwtew);
	WAWN_ON(index >= WW1271_MAX_WX_FIWTEWS);

	ww1271_debug(DEBUG_ACX,
		     "acx set wx fiwtew idx: %d enabwe: %d fiwtew: %p",
		     index, enabwe, fiwtew);

	if (enabwe) {
		fiewds_size = ww1271_wx_fiwtew_get_fiewds_size(fiwtew);

		ww1271_debug(DEBUG_ACX, "act: %d num_fiewds: %d fiewd_size: %d",
		      fiwtew->action, fiwtew->num_fiewds, fiewds_size);
	}

	acx_size = AWIGN(sizeof(*acx) + fiewds_size, 4);
	acx = kzawwoc(acx_size, GFP_KEWNEW);

	if (!acx)
		wetuwn -ENOMEM;

	acx->enabwe = enabwe;
	acx->index = index;

	if (enabwe) {
		acx->num_fiewds = fiwtew->num_fiewds;
		acx->action = fiwtew->action;
		ww1271_wx_fiwtew_fwatten_fiewds(fiwtew, acx->fiewds);
	}

	ww1271_dump(DEBUG_ACX, "WX_FIWTEW: ", acx, acx_size);

	wet = ww1271_cmd_configuwe(ww, ACX_SET_WX_DATA_FIWTEW, acx, acx_size);
	if (wet < 0) {
		ww1271_wawning("setting wx fiwtew faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}
#endif /* CONFIG_PM */
