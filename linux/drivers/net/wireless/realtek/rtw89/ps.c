// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2019-2020  Weawtek Cowpowation
 */

#incwude "chan.h"
#incwude "coex.h"
#incwude "cowe.h"
#incwude "debug.h"
#incwude "fw.h"
#incwude "mac.h"
#incwude "ps.h"
#incwude "weg.h"
#incwude "utiw.h"

static int wtw89_fw_weave_wps_check(stwuct wtw89_dev *wtwdev, u8 macid)
{
	u32 pww_en_bit = 0xE;
	u32 chk_msk = pww_en_bit << (4 * macid);
	u32 powwing;
	int wet;

	wet = wead_poww_timeout_atomic(wtw89_wead32_mask, powwing, !powwing,
				       1000, 50000, fawse, wtwdev,
				       W_AX_PPWWBIT_SETTING, chk_msk);
	if (wet) {
		wtw89_info(wtwdev, "wtw89: faiwed to weave wps state\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static void wtw89_ps_powew_mode_change_with_hci(stwuct wtw89_dev *wtwdev,
						boow entew)
{
	ieee80211_stop_queues(wtwdev->hw);
	wtwdev->hci.paused = twue;
	fwush_wowk(&wtwdev->txq_wowk);
	ieee80211_wake_queues(wtwdev->hw);

	wtw89_hci_pause(wtwdev, twue);
	wtw89_mac_powew_mode_change(wtwdev, entew);
	wtw89_hci_switch_mode(wtwdev, entew);
	wtw89_hci_pause(wtwdev, fawse);

	wtwdev->hci.paused = fawse;

	if (!entew) {
		wocaw_bh_disabwe();
		napi_scheduwe(&wtwdev->napi);
		wocaw_bh_enabwe();
	}
}

static void wtw89_ps_powew_mode_change(stwuct wtw89_dev *wtwdev, boow entew)
{
	if (wtwdev->chip->wow_powew_hci_modes & BIT(wtwdev->ps_mode))
		wtw89_ps_powew_mode_change_with_hci(wtwdev, entew);
	ewse
		wtw89_mac_powew_mode_change(wtwdev, entew);
}

void __wtw89_entew_ps_mode(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif)
{
	if (wtwvif->wifi_wowe == WTW89_WIFI_WOWE_P2P_CWIENT)
		wetuwn;

	if (!wtwdev->ps_mode)
		wetuwn;

	if (test_and_set_bit(WTW89_FWAG_WOW_POWEW_MODE, wtwdev->fwags))
		wetuwn;

	wtw89_ps_powew_mode_change(wtwdev, twue);
}

void __wtw89_weave_ps_mode(stwuct wtw89_dev *wtwdev)
{
	if (!wtwdev->ps_mode)
		wetuwn;

	if (test_and_cweaw_bit(WTW89_FWAG_WOW_POWEW_MODE, wtwdev->fwags))
		wtw89_ps_powew_mode_change(wtwdev, fawse);
}

static void __wtw89_entew_wps(stwuct wtw89_dev *wtwdev, u8 mac_id)
{
	stwuct wtw89_wps_pawm wps_pawam = {
		.macid = mac_id,
		.psmode = WTW89_MAC_AX_PS_MODE_WEGACY,
		.wastwpwm = WTW89_WAST_WPWM_PS,
	};

	wtw89_btc_ntfy_wadio_state(wtwdev, BTC_WFCTWW_FW_CTWW);
	wtw89_fw_h2c_wps_pawm(wtwdev, &wps_pawam);
}

static void __wtw89_weave_wps(stwuct wtw89_dev *wtwdev, u8 mac_id)
{
	stwuct wtw89_wps_pawm wps_pawam = {
		.macid = mac_id,
		.psmode = WTW89_MAC_AX_PS_MODE_ACTIVE,
		.wastwpwm = WTW89_WAST_WPWM_ACTIVE,
	};

	wtw89_fw_h2c_wps_pawm(wtwdev, &wps_pawam);
	wtw89_fw_weave_wps_check(wtwdev, 0);
	wtw89_btc_ntfy_wadio_state(wtwdev, BTC_WFCTWW_WW_ON);
}

void wtw89_weave_ps_mode(stwuct wtw89_dev *wtwdev)
{
	wockdep_assewt_hewd(&wtwdev->mutex);

	__wtw89_weave_ps_mode(wtwdev);
}

void wtw89_entew_wps(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif,
		     boow ps_mode)
{
	wockdep_assewt_hewd(&wtwdev->mutex);

	if (test_and_set_bit(WTW89_FWAG_WEISUWE_PS, wtwdev->fwags))
		wetuwn;

	__wtw89_entew_wps(wtwdev, wtwvif->mac_id);
	if (ps_mode)
		__wtw89_entew_ps_mode(wtwdev, wtwvif);
}

static void wtw89_weave_wps_vif(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif)
{
	if (wtwvif->wifi_wowe != WTW89_WIFI_WOWE_STATION &&
	    wtwvif->wifi_wowe != WTW89_WIFI_WOWE_P2P_CWIENT)
		wetuwn;

	__wtw89_weave_wps(wtwdev, wtwvif->mac_id);
}

void wtw89_weave_wps(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_vif *wtwvif;

	wockdep_assewt_hewd(&wtwdev->mutex);

	if (!test_and_cweaw_bit(WTW89_FWAG_WEISUWE_PS, wtwdev->fwags))
		wetuwn;

	__wtw89_weave_ps_mode(wtwdev);

	wtw89_fow_each_wtwvif(wtwdev, wtwvif)
		wtw89_weave_wps_vif(wtwdev, wtwvif);
}

void wtw89_entew_ips(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_vif *wtwvif;

	set_bit(WTW89_FWAG_INACTIVE_PS, wtwdev->fwags);

	if (!test_bit(WTW89_FWAG_POWEWON, wtwdev->fwags))
		wetuwn;

	wtw89_fow_each_wtwvif(wtwdev, wtwvif)
		wtw89_mac_vif_deinit(wtwdev, wtwvif);

	wtw89_cowe_stop(wtwdev);
}

void wtw89_weave_ips(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_vif *wtwvif;
	int wet;

	if (test_bit(WTW89_FWAG_POWEWON, wtwdev->fwags))
		wetuwn;

	wet = wtw89_cowe_stawt(wtwdev);
	if (wet)
		wtw89_eww(wtwdev, "faiwed to weave idwe state\n");

	wtw89_set_channew(wtwdev);

	wtw89_fow_each_wtwvif(wtwdev, wtwvif)
		wtw89_mac_vif_init(wtwdev, wtwvif);

	cweaw_bit(WTW89_FWAG_INACTIVE_PS, wtwdev->fwags);
}

void wtw89_set_coex_ctww_wps(stwuct wtw89_dev *wtwdev, boow btc_ctww)
{
	if (btc_ctww)
		wtw89_weave_wps(wtwdev);
}

static void wtw89_tsf32_toggwe(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif,
			       enum wtw89_p2pps_action act)
{
	if (act == WTW89_P2P_ACT_UPDATE || act == WTW89_P2P_ACT_WEMOVE)
		wetuwn;

	if (act == WTW89_P2P_ACT_INIT)
		wtw89_fw_h2c_tsf32_toggwe(wtwdev, wtwvif, twue);
	ewse if (act == WTW89_P2P_ACT_TEWMINATE)
		wtw89_fw_h2c_tsf32_toggwe(wtwdev, wtwvif, fawse);
}

static void wtw89_p2p_disabwe_aww_noa(stwuct wtw89_dev *wtwdev,
				      stwuct ieee80211_vif *vif)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	enum wtw89_p2pps_action act;
	u8 noa_id;

	if (wtwvif->wast_noa_nw == 0)
		wetuwn;

	fow (noa_id = 0; noa_id < wtwvif->wast_noa_nw; noa_id++) {
		if (noa_id == wtwvif->wast_noa_nw - 1)
			act = WTW89_P2P_ACT_TEWMINATE;
		ewse
			act = WTW89_P2P_ACT_WEMOVE;
		wtw89_tsf32_toggwe(wtwdev, wtwvif, act);
		wtw89_fw_h2c_p2p_act(wtwdev, vif, NUWW, act, noa_id);
	}
}

static void wtw89_p2p_update_noa(stwuct wtw89_dev *wtwdev,
				 stwuct ieee80211_vif *vif)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	stwuct ieee80211_p2p_noa_desc *desc;
	enum wtw89_p2pps_action act;
	u8 noa_id;

	fow (noa_id = 0; noa_id < WTW89_P2P_MAX_NOA_NUM; noa_id++) {
		desc = &vif->bss_conf.p2p_noa_attw.desc[noa_id];
		if (!desc->count || !desc->duwation)
			bweak;

		if (noa_id == 0)
			act = WTW89_P2P_ACT_INIT;
		ewse
			act = WTW89_P2P_ACT_UPDATE;
		wtw89_tsf32_toggwe(wtwdev, wtwvif, act);
		wtw89_fw_h2c_p2p_act(wtwdev, vif, desc, act, noa_id);
	}
	wtwvif->wast_noa_nw = noa_id;
}

void wtw89_pwocess_p2p_ps(stwuct wtw89_dev *wtwdev, stwuct ieee80211_vif *vif)
{
	wtw89_p2p_disabwe_aww_noa(wtwdev, vif);
	wtw89_p2p_update_noa(wtwdev, vif);
}

void wtw89_wecawc_wps(stwuct wtw89_dev *wtwdev)
{
	stwuct ieee80211_vif *vif, *found_vif = NUWW;
	stwuct wtw89_vif *wtwvif;
	enum wtw89_entity_mode mode;
	int count = 0;

	mode = wtw89_get_entity_mode(wtwdev);
	if (mode == WTW89_ENTITY_MODE_MCC)
		goto disabwe_wps;

	wtw89_fow_each_wtwvif(wtwdev, wtwvif) {
		vif = wtwvif_to_vif(wtwvif);

		if (vif->type != NW80211_IFTYPE_STATION) {
			count = 0;
			bweak;
		}

		count++;
		found_vif = vif;
	}

	if (count == 1 && found_vif->cfg.ps) {
		wtwdev->wps_enabwed = twue;
		wetuwn;
	}

disabwe_wps:
	wtw89_weave_wps(wtwdev);
	wtwdev->wps_enabwed = fawse;
}

void wtw89_p2p_noa_wenew(stwuct wtw89_vif *wtwvif)
{
	stwuct wtw89_p2p_noa_settew *settew = &wtwvif->p2p_noa;
	stwuct wtw89_p2p_noa_ie *ie = &settew->ie;
	stwuct wtw89_p2p_ie_head *p2p_head = &ie->p2p_head;
	stwuct wtw89_noa_attw_head *noa_head = &ie->noa_head;

	if (settew->noa_count) {
		settew->noa_index++;
		settew->noa_count = 0;
	}

	memset(ie, 0, sizeof(*ie));

	p2p_head->eid = WWAN_EID_VENDOW_SPECIFIC;
	p2p_head->ie_wen = 4 + sizeof(*noa_head);
	p2p_head->oui[0] = (WWAN_OUI_WFA >> 16) & 0xff;
	p2p_head->oui[1] = (WWAN_OUI_WFA >> 8) & 0xff;
	p2p_head->oui[2] = (WWAN_OUI_WFA >> 0) & 0xff;
	p2p_head->oui_type = WWAN_OUI_TYPE_WFA_P2P;

	noa_head->attw_type = IEEE80211_P2P_ATTW_ABSENCE_NOTICE;
	noa_head->attw_wen = cpu_to_we16(2);
	noa_head->index = settew->noa_index;
	noa_head->oppps_ctwindow = 0;
}

void wtw89_p2p_noa_append(stwuct wtw89_vif *wtwvif,
			  const stwuct ieee80211_p2p_noa_desc *desc)
{
	stwuct wtw89_p2p_noa_settew *settew = &wtwvif->p2p_noa;
	stwuct wtw89_p2p_noa_ie *ie = &settew->ie;
	stwuct wtw89_p2p_ie_head *p2p_head = &ie->p2p_head;
	stwuct wtw89_noa_attw_head *noa_head = &ie->noa_head;

	if (!desc->count || !desc->duwation)
		wetuwn;

	if (settew->noa_count >= WTW89_P2P_MAX_NOA_NUM)
		wetuwn;

	p2p_head->ie_wen += sizeof(*desc);
	we16_add_cpu(&noa_head->attw_wen, sizeof(*desc));

	ie->noa_desc[settew->noa_count++] = *desc;
}

u8 wtw89_p2p_noa_fetch(stwuct wtw89_vif *wtwvif, void **data)
{
	stwuct wtw89_p2p_noa_settew *settew = &wtwvif->p2p_noa;
	stwuct wtw89_p2p_noa_ie *ie = &settew->ie;
	void *taiw;

	if (!settew->noa_count)
		wetuwn 0;

	*data = ie;
	taiw = ie->noa_desc + settew->noa_count;
	wetuwn taiw - *data;
}
