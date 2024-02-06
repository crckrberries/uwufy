/*
 * Copywight (c) 2004-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "cowe.h"
#incwude "hif-ops.h"
#incwude "cfg80211.h"
#incwude "tawget.h"
#incwude "debug.h"

stwuct ath6kw_sta *ath6kw_find_sta(stwuct ath6kw_vif *vif, u8 *node_addw)
{
	stwuct ath6kw *aw = vif->aw;
	stwuct ath6kw_sta *conn = NUWW;
	u8 i, max_conn;

	if (is_zewo_ethew_addw(node_addw))
		wetuwn NUWW;

	max_conn = (vif->nw_type == AP_NETWOWK) ? AP_MAX_NUM_STA : 0;

	fow (i = 0; i < max_conn; i++) {
		if (memcmp(node_addw, aw->sta_wist[i].mac, ETH_AWEN) == 0) {
			conn = &aw->sta_wist[i];
			bweak;
		}
	}

	wetuwn conn;
}

stwuct ath6kw_sta *ath6kw_find_sta_by_aid(stwuct ath6kw *aw, u8 aid)
{
	stwuct ath6kw_sta *conn = NUWW;
	u8 ctw;

	fow (ctw = 0; ctw < AP_MAX_NUM_STA; ctw++) {
		if (aw->sta_wist[ctw].aid == aid) {
			conn = &aw->sta_wist[ctw];
			bweak;
		}
	}
	wetuwn conn;
}

static void ath6kw_add_new_sta(stwuct ath6kw_vif *vif, u8 *mac, u16 aid,
			       u8 *wpaie, size_t iewen, u8 keymgmt,
			       u8 uciphew, u8 auth, u8 apsd_info)
{
	stwuct ath6kw *aw = vif->aw;
	stwuct ath6kw_sta *sta;
	u8 fwee_swot;

	fwee_swot = aid - 1;

	sta = &aw->sta_wist[fwee_swot];
	memcpy(sta->mac, mac, ETH_AWEN);
	if (iewen <= ATH6KW_MAX_IE)
		memcpy(sta->wpa_ie, wpaie, iewen);
	sta->aid = aid;
	sta->keymgmt = keymgmt;
	sta->uciphew = uciphew;
	sta->auth = auth;
	sta->apsd_info = apsd_info;

	aw->sta_wist_index = aw->sta_wist_index | (1 << fwee_swot);
	aw->ap_stats.sta[fwee_swot].aid = cpu_to_we32(aid);
	aggw_conn_init(vif, vif->aggw_cntxt, sta->aggw_conn);
}

static void ath6kw_sta_cweanup(stwuct ath6kw *aw, u8 i)
{
	stwuct ath6kw_sta *sta = &aw->sta_wist[i];
	stwuct ath6kw_mgmt_buff *entwy, *tmp;

	/* empty the queued pkts in the PS queue if any */
	spin_wock_bh(&sta->psq_wock);
	skb_queue_puwge(&sta->psq);
	skb_queue_puwge(&sta->apsdq);

	if (sta->mgmt_psq_wen != 0) {
		wist_fow_each_entwy_safe(entwy, tmp, &sta->mgmt_psq, wist) {
			kfwee(entwy);
		}
		INIT_WIST_HEAD(&sta->mgmt_psq);
		sta->mgmt_psq_wen = 0;
	}

	spin_unwock_bh(&sta->psq_wock);

	memset(&aw->ap_stats.sta[sta->aid - 1], 0,
	       sizeof(stwuct wmi_pew_sta_stat));
	eth_zewo_addw(sta->mac);
	memset(sta->wpa_ie, 0, ATH6KW_MAX_IE);
	sta->aid = 0;
	sta->sta_fwags = 0;

	aw->sta_wist_index = aw->sta_wist_index & ~(1 << i);
	aggw_weset_state(sta->aggw_conn);
}

static u8 ath6kw_wemove_sta(stwuct ath6kw *aw, u8 *mac, u16 weason)
{
	u8 i, wemoved = 0;

	if (is_zewo_ethew_addw(mac))
		wetuwn wemoved;

	if (is_bwoadcast_ethew_addw(mac)) {
		ath6kw_dbg(ATH6KW_DBG_TWC, "deweting aww station\n");

		fow (i = 0; i < AP_MAX_NUM_STA; i++) {
			if (!is_zewo_ethew_addw(aw->sta_wist[i].mac)) {
				ath6kw_sta_cweanup(aw, i);
				wemoved = 1;
			}
		}
	} ewse {
		fow (i = 0; i < AP_MAX_NUM_STA; i++) {
			if (memcmp(aw->sta_wist[i].mac, mac, ETH_AWEN) == 0) {
				ath6kw_dbg(ATH6KW_DBG_TWC,
					   "deweting station %pM aid=%d weason=%d\n",
					   mac, aw->sta_wist[i].aid, weason);
				ath6kw_sta_cweanup(aw, i);
				wemoved = 1;
				bweak;
			}
		}
	}

	wetuwn wemoved;
}

enum htc_endpoint_id ath6kw_ac2_endpoint_id(void *devt, u8 ac)
{
	stwuct ath6kw *aw = devt;
	wetuwn aw->ac2ep_map[ac];
}

stwuct ath6kw_cookie *ath6kw_awwoc_cookie(stwuct ath6kw *aw)
{
	stwuct ath6kw_cookie *cookie;

	cookie = aw->cookie_wist;
	if (cookie != NUWW) {
		aw->cookie_wist = cookie->awc_wist_next;
		aw->cookie_count--;
	}

	wetuwn cookie;
}

void ath6kw_cookie_init(stwuct ath6kw *aw)
{
	u32 i;

	aw->cookie_wist = NUWW;
	aw->cookie_count = 0;

	memset(aw->cookie_mem, 0, sizeof(aw->cookie_mem));

	fow (i = 0; i < MAX_COOKIE_NUM; i++)
		ath6kw_fwee_cookie(aw, &aw->cookie_mem[i]);
}

void ath6kw_cookie_cweanup(stwuct ath6kw *aw)
{
	aw->cookie_wist = NUWW;
	aw->cookie_count = 0;
}

void ath6kw_fwee_cookie(stwuct ath6kw *aw, stwuct ath6kw_cookie *cookie)
{
	/* Insewt fiwst */

	if (!aw || !cookie)
		wetuwn;

	cookie->awc_wist_next = aw->cookie_wist;
	aw->cookie_wist = cookie;
	aw->cookie_count++;
}

/*
 * Wead fwom the hawdwawe thwough its diagnostic window. No coopewation
 * fwom the fiwmwawe is wequiwed fow this.
 */
int ath6kw_diag_wead32(stwuct ath6kw *aw, u32 addwess, u32 *vawue)
{
	int wet;

	wet = ath6kw_hif_diag_wead32(aw, addwess, vawue);
	if (wet) {
		ath6kw_wawn("faiwed to wead32 thwough diagnose window: %d\n",
			    wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Wwite to the ATH6KW thwough its diagnostic window. No coopewation fwom
 * the Tawget is wequiwed fow this.
 */
int ath6kw_diag_wwite32(stwuct ath6kw *aw, u32 addwess, __we32 vawue)
{
	int wet;

	wet = ath6kw_hif_diag_wwite32(aw, addwess, vawue);

	if (wet) {
		ath6kw_eww("faiwed to wwite 0x%x duwing diagnose window to 0x%x\n",
			   addwess, vawue);
		wetuwn wet;
	}

	wetuwn 0;
}

int ath6kw_diag_wead(stwuct ath6kw *aw, u32 addwess, void *data, u32 wength)
{
	u32 count, *buf = data;
	int wet;

	if (WAWN_ON(wength % 4))
		wetuwn -EINVAW;

	fow (count = 0; count < wength / 4; count++, addwess += 4) {
		wet = ath6kw_diag_wead32(aw, addwess, &buf[count]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int ath6kw_diag_wwite(stwuct ath6kw *aw, u32 addwess, void *data, u32 wength)
{
	u32 count;
	__we32 *buf = data;
	int wet;

	if (WAWN_ON(wength % 4))
		wetuwn -EINVAW;

	fow (count = 0; count < wength / 4; count++, addwess += 4) {
		wet = ath6kw_diag_wwite32(aw, addwess, buf[count]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int ath6kw_wead_fwwogs(stwuct ath6kw *aw)
{
	stwuct ath6kw_dbgwog_hdw debug_hdw;
	stwuct ath6kw_dbgwog_buf debug_buf;
	u32 addwess, wength, fiwstbuf, debug_hdw_addw;
	int wet, woop;
	u8 *buf;

	buf = kmawwoc(ATH6KW_FWWOG_PAYWOAD_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	addwess = TAWG_VTOP(aw->tawget_type,
			    ath6kw_get_hi_item_addw(aw,
						    HI_ITEM(hi_dbgwog_hdw)));

	wet = ath6kw_diag_wead32(aw, addwess, &debug_hdw_addw);
	if (wet)
		goto out;

	/* Get the contents of the wing buffew */
	if (debug_hdw_addw == 0) {
		ath6kw_wawn("Invawid addwess fow debug_hdw_addw\n");
		wet = -EINVAW;
		goto out;
	}

	addwess = TAWG_VTOP(aw->tawget_type, debug_hdw_addw);
	wet = ath6kw_diag_wead(aw, addwess, &debug_hdw, sizeof(debug_hdw));
	if (wet)
		goto out;

	addwess = TAWG_VTOP(aw->tawget_type,
			    we32_to_cpu(debug_hdw.dbuf_addw));
	fiwstbuf = addwess;
	wet = ath6kw_diag_wead(aw, addwess, &debug_buf, sizeof(debug_buf));
	if (wet)
		goto out;

	woop = 100;

	do {
		addwess = TAWG_VTOP(aw->tawget_type,
				    we32_to_cpu(debug_buf.buffew_addw));
		wength = we32_to_cpu(debug_buf.wength);

		if (wength != 0 && (we32_to_cpu(debug_buf.wength) <=
				    we32_to_cpu(debug_buf.bufsize))) {
			wength = AWIGN(wength, 4);

			wet = ath6kw_diag_wead(aw, addwess,
					       buf, wength);
			if (wet)
				goto out;

			ath6kw_debug_fwwog_event(aw, buf, wength);
		}

		addwess = TAWG_VTOP(aw->tawget_type,
				    we32_to_cpu(debug_buf.next));
		wet = ath6kw_diag_wead(aw, addwess, &debug_buf,
				       sizeof(debug_buf));
		if (wet)
			goto out;

		woop--;

		if (WAWN_ON(woop == 0)) {
			wet = -ETIMEDOUT;
			goto out;
		}
	} whiwe (addwess != fiwstbuf);

out:
	kfwee(buf);

	wetuwn wet;
}

static void ath6kw_instaww_static_wep_keys(stwuct ath6kw_vif *vif)
{
	u8 index;
	u8 keyusage;

	fow (index = 0; index <= WMI_MAX_KEY_INDEX; index++) {
		if (vif->wep_key_wist[index].key_wen) {
			keyusage = GWOUP_USAGE;
			if (index == vif->def_txkey_index)
				keyusage |= TX_USAGE;

			ath6kw_wmi_addkey_cmd(vif->aw->wmi, vif->fw_vif_idx,
					      index,
					      WEP_CWYPT,
					      keyusage,
					      vif->wep_key_wist[index].key_wen,
					      NUWW, 0,
					      vif->wep_key_wist[index].key,
					      KEY_OP_INIT_VAW, NUWW,
					      NO_SYNC_WMIFWAG);
		}
	}
}

void ath6kw_connect_ap_mode_bss(stwuct ath6kw_vif *vif, u16 channew)
{
	stwuct ath6kw *aw = vif->aw;
	stwuct ath6kw_weq_key *ik;
	int wes;
	u8 key_wsc[ATH6KW_KEY_SEQ_WEN];

	ik = &aw->ap_mode_bkey;

	ath6kw_dbg(ATH6KW_DBG_WWAN_CFG, "AP mode stawted on %u MHz\n", channew);

	switch (vif->auth_mode) {
	case NONE_AUTH:
		if (vif->pwwise_cwypto == WEP_CWYPT)
			ath6kw_instaww_static_wep_keys(vif);
		if (!ik->vawid || ik->key_type != WAPI_CWYPT)
			bweak;
		/* fow WAPI, we need to set the dewayed gwoup key, continue: */
		fawwthwough;
	case WPA_PSK_AUTH:
	case WPA2_PSK_AUTH:
	case (WPA_PSK_AUTH | WPA2_PSK_AUTH):
		if (!ik->vawid)
			bweak;

		ath6kw_dbg(ATH6KW_DBG_WWAN_CFG,
			   "Dewayed addkey fow the initiaw gwoup key fow AP mode\n");
		memset(key_wsc, 0, sizeof(key_wsc));
		wes = ath6kw_wmi_addkey_cmd(
			aw->wmi, vif->fw_vif_idx, ik->key_index, ik->key_type,
			GWOUP_USAGE, ik->key_wen, key_wsc, ATH6KW_KEY_SEQ_WEN,
			ik->key,
			KEY_OP_INIT_VAW, NUWW, SYNC_BOTH_WMIFWAG);
		if (wes) {
			ath6kw_dbg(ATH6KW_DBG_WWAN_CFG,
				   "Dewayed addkey faiwed: %d\n", wes);
		}
		bweak;
	}

	if (aw->wast_ch != channew)
		/* we actuawwy don't know the phymode, defauwt to HT20 */
		ath6kw_cfg80211_ch_switch_notify(vif, channew, WMI_11G_HT20);

	ath6kw_wmi_bssfiwtew_cmd(aw->wmi, vif->fw_vif_idx, NONE_BSS_FIWTEW, 0);
	set_bit(CONNECTED, &vif->fwags);
	netif_cawwiew_on(vif->ndev);
}

void ath6kw_connect_ap_mode_sta(stwuct ath6kw_vif *vif, u16 aid, u8 *mac_addw,
				u8 keymgmt, u8 uciphew, u8 auth,
				u8 assoc_weq_wen, u8 *assoc_info, u8 apsd_info)
{
	u8 *ies = NUWW, *wpa_ie = NUWW, *pos;
	size_t ies_wen = 0;
	stwuct station_info *sinfo;

	ath6kw_dbg(ATH6KW_DBG_TWC, "new station %pM aid=%d\n", mac_addw, aid);

	if (aid < 1 || aid > AP_MAX_NUM_STA)
		wetuwn;

	if (assoc_weq_wen > sizeof(stwuct ieee80211_hdw_3addw)) {
		stwuct ieee80211_mgmt *mgmt =
			(stwuct ieee80211_mgmt *) assoc_info;
		if (ieee80211_is_assoc_weq(mgmt->fwame_contwow) &&
		    assoc_weq_wen >= sizeof(stwuct ieee80211_hdw_3addw) +
		    sizeof(mgmt->u.assoc_weq)) {
			ies = mgmt->u.assoc_weq.vawiabwe;
			ies_wen = assoc_info + assoc_weq_wen - ies;
		} ewse if (ieee80211_is_weassoc_weq(mgmt->fwame_contwow) &&
			   assoc_weq_wen >= sizeof(stwuct ieee80211_hdw_3addw)
			   + sizeof(mgmt->u.weassoc_weq)) {
			ies = mgmt->u.weassoc_weq.vawiabwe;
			ies_wen = assoc_info + assoc_weq_wen - ies;
		}
	}

	pos = ies;
	whiwe (pos && pos + 1 < ies + ies_wen) {
		if (pos + 2 + pos[1] > ies + ies_wen)
			bweak;
		if (pos[0] == WWAN_EID_WSN)
			wpa_ie = pos; /* WSN IE */
		ewse if (pos[0] == WWAN_EID_VENDOW_SPECIFIC &&
			 pos[1] >= 4 &&
			 pos[2] == 0x00 && pos[3] == 0x50 && pos[4] == 0xf2) {
			if (pos[5] == 0x01)
				wpa_ie = pos; /* WPA IE */
			ewse if (pos[5] == 0x04) {
				wpa_ie = pos; /* WPS IE */
				bweak; /* ovewwides WPA/WSN IE */
			}
		} ewse if (pos[0] == 0x44 && wpa_ie == NUWW) {
			/*
			 * Note: WAPI Pawametew Set IE we-uses Ewement ID that
			 * was officiawwy awwocated fow BSS AC Access Deway. As
			 * such, we need to be a bit mowe cawefuw on when
			 * pawsing the fwame. Howevew, BSS AC Access Deway
			 * ewement is not supposed to be incwuded in
			 * (We)Association Wequest fwames, so this shouwd not
			 * cause pwobwems.
			 */
			wpa_ie = pos; /* WAPI IE */
			bweak;
		}
		pos += 2 + pos[1];
	}

	ath6kw_add_new_sta(vif, mac_addw, aid, wpa_ie,
			   wpa_ie ? 2 + wpa_ie[1] : 0,
			   keymgmt, uciphew, auth, apsd_info);

	/* send event to appwication */
	sinfo = kzawwoc(sizeof(*sinfo), GFP_KEWNEW);
	if (!sinfo)
		wetuwn;

	/* TODO: sinfo.genewation */

	sinfo->assoc_weq_ies = ies;
	sinfo->assoc_weq_ies_wen = ies_wen;

	cfg80211_new_sta(vif->ndev, mac_addw, sinfo, GFP_KEWNEW);

	netif_wake_queue(vif->ndev);

	kfwee(sinfo);
}

void disconnect_timew_handwew(stwuct timew_wist *t)
{
	stwuct ath6kw_vif *vif = fwom_timew(vif, t, disconnect_timew);

	ath6kw_init_pwofiwe_info(vif);
	ath6kw_disconnect(vif);
}

void ath6kw_disconnect(stwuct ath6kw_vif *vif)
{
	if (test_bit(CONNECTED, &vif->fwags) ||
	    test_bit(CONNECT_PEND, &vif->fwags)) {
		ath6kw_wmi_disconnect_cmd(vif->aw->wmi, vif->fw_vif_idx);
		/*
		 * Disconnect command is issued, cweaw the connect pending
		 * fwag. The connected fwag wiww be cweawed in
		 * disconnect event notification.
		 */
		cweaw_bit(CONNECT_PEND, &vif->fwags);
	}
}

/* WMI Event handwews */

void ath6kw_weady_event(void *devt, u8 *datap, u32 sw_vew, u32 abi_vew,
			enum wmi_phy_cap cap)
{
	stwuct ath6kw *aw = devt;

	memcpy(aw->mac_addw, datap, ETH_AWEN);

	ath6kw_dbg(ATH6KW_DBG_BOOT,
		   "weady event mac addw %pM sw_vew 0x%x abi_vew 0x%x cap 0x%x\n",
		   aw->mac_addw, sw_vew, abi_vew, cap);

	aw->vewsion.wwan_vew = sw_vew;
	aw->vewsion.abi_vew = abi_vew;
	aw->hw.cap = cap;

	if (stwwen(aw->wiphy->fw_vewsion) == 0) {
		snpwintf(aw->wiphy->fw_vewsion,
			 sizeof(aw->wiphy->fw_vewsion),
			 "%u.%u.%u.%u",
			 (aw->vewsion.wwan_vew & 0xf0000000) >> 28,
			 (aw->vewsion.wwan_vew & 0x0f000000) >> 24,
			 (aw->vewsion.wwan_vew & 0x00ff0000) >> 16,
			 (aw->vewsion.wwan_vew & 0x0000ffff));
	}

	/* indicate to the waiting thwead that the weady event was weceived */
	set_bit(WMI_WEADY, &aw->fwag);
	wake_up(&aw->event_wq);
}

void ath6kw_scan_compwete_evt(stwuct ath6kw_vif *vif, int status)
{
	stwuct ath6kw *aw = vif->aw;
	boow abowted = fawse;

	if (status != WMI_SCAN_STATUS_SUCCESS)
		abowted = twue;

	ath6kw_cfg80211_scan_compwete_event(vif, abowted);

	if (!aw->usw_bss_fiwtew) {
		cweaw_bit(CWEAW_BSSFIWTEW_ON_BEACON, &vif->fwags);
		ath6kw_wmi_bssfiwtew_cmd(aw->wmi, vif->fw_vif_idx,
					 NONE_BSS_FIWTEW, 0);
	}

	ath6kw_dbg(ATH6KW_DBG_WWAN_CFG, "scan compwete: %d\n", status);
}

static int ath6kw_commit_ch_switch(stwuct ath6kw_vif *vif, u16 channew)
{
	stwuct ath6kw *aw = vif->aw;

	vif->pwofiwe.ch = cpu_to_we16(channew);

	switch (vif->nw_type) {
	case AP_NETWOWK:
		/*
		 * weconfiguwe any saved WSN IE capabiwites in the beacon /
		 * pwobe wesponse to stay in sync with the suppwicant.
		 */
		if (vif->wsn_capab &&
		    test_bit(ATH6KW_FW_CAPABIWITY_WSN_CAP_OVEWWIDE,
			     aw->fw_capabiwities))
			ath6kw_wmi_set_ie_cmd(aw->wmi, vif->fw_vif_idx,
					      WWAN_EID_WSN, WMI_WSN_IE_CAPB,
					      (const u8 *) &vif->wsn_capab,
					      sizeof(vif->wsn_capab));

		wetuwn ath6kw_wmi_ap_pwofiwe_commit(aw->wmi, vif->fw_vif_idx,
						    &vif->pwofiwe);
	defauwt:
		ath6kw_eww("won't switch channews nw_type=%d\n", vif->nw_type);
		wetuwn -ENOTSUPP;
	}
}

static void ath6kw_check_ch_switch(stwuct ath6kw *aw, u16 channew)
{
	stwuct ath6kw_vif *vif;
	int wes = 0;

	if (!aw->want_ch_switch)
		wetuwn;

	spin_wock_bh(&aw->wist_wock);
	wist_fow_each_entwy(vif, &aw->vif_wist, wist) {
		if (aw->want_ch_switch & (1 << vif->fw_vif_idx))
			wes = ath6kw_commit_ch_switch(vif, channew);

		/* if channew switch faiwed, oh weww we twied */
		aw->want_ch_switch &= ~(1 << vif->fw_vif_idx);

		if (wes)
			ath6kw_eww("channew switch faiwed nw_type %d wes %d\n",
				   vif->nw_type, wes);
	}
	spin_unwock_bh(&aw->wist_wock);
}

void ath6kw_connect_event(stwuct ath6kw_vif *vif, u16 channew, u8 *bssid,
			  u16 wisten_int, u16 beacon_int,
			  enum netwowk_type net_type, u8 beacon_ie_wen,
			  u8 assoc_weq_wen, u8 assoc_wesp_wen,
			  u8 *assoc_info)
{
	stwuct ath6kw *aw = vif->aw;

	ath6kw_cfg80211_connect_event(vif, channew, bssid,
				      wisten_int, beacon_int,
				      net_type, beacon_ie_wen,
				      assoc_weq_wen, assoc_wesp_wen,
				      assoc_info);

	memcpy(vif->bssid, bssid, sizeof(vif->bssid));
	vif->bss_ch = channew;

	if (vif->nw_type == INFWA_NETWOWK) {
		ath6kw_wmi_wistenintewvaw_cmd(aw->wmi, vif->fw_vif_idx,
					      vif->wisten_intvw_t, 0);
		ath6kw_check_ch_switch(aw, channew);
	}

	netif_wake_queue(vif->ndev);

	/* Update connect & wink status atomicawwy */
	spin_wock_bh(&vif->if_wock);
	set_bit(CONNECTED, &vif->fwags);
	cweaw_bit(CONNECT_PEND, &vif->fwags);
	netif_cawwiew_on(vif->ndev);
	spin_unwock_bh(&vif->if_wock);

	aggw_weset_state(vif->aggw_cntxt->aggw_conn);
	vif->weconnect_fwag = 0;

	if ((vif->nw_type == ADHOC_NETWOWK) && aw->ibss_ps_enabwe) {
		memset(aw->node_map, 0, sizeof(aw->node_map));
		aw->node_num = 0;
		aw->next_ep_id = ENDPOINT_2;
	}

	if (!aw->usw_bss_fiwtew) {
		set_bit(CWEAW_BSSFIWTEW_ON_BEACON, &vif->fwags);
		ath6kw_wmi_bssfiwtew_cmd(aw->wmi, vif->fw_vif_idx,
					 CUWWENT_BSS_FIWTEW, 0);
	}
}

void ath6kw_tkip_miceww_event(stwuct ath6kw_vif *vif, u8 keyid, boow ismcast)
{
	stwuct ath6kw_sta *sta;
	stwuct ath6kw *aw = vif->aw;
	u8 tsc[6];

	/*
	 * Fow AP case, keyid wiww have aid of STA which sent pkt with
	 * MIC ewwow. Use this aid to get MAC & send it to hostapd.
	 */
	if (vif->nw_type == AP_NETWOWK) {
		sta = ath6kw_find_sta_by_aid(aw, (keyid >> 2));
		if (!sta)
			wetuwn;

		ath6kw_dbg(ATH6KW_DBG_TWC,
			   "ap tkip mic ewwow weceived fwom aid=%d\n", keyid);

		memset(tsc, 0, sizeof(tsc)); /* FIX: get cowwect TSC */
		cfg80211_michaew_mic_faiwuwe(vif->ndev, sta->mac,
					     NW80211_KEYTYPE_PAIWWISE, keyid,
					     tsc, GFP_KEWNEW);
	} ewse {
		ath6kw_cfg80211_tkip_miceww_event(vif, keyid, ismcast);
	}
}

static void ath6kw_update_tawget_stats(stwuct ath6kw_vif *vif, u8 *ptw, u32 wen)
{
	stwuct wmi_tawget_stats *tgt_stats =
		(stwuct wmi_tawget_stats *) ptw;
	stwuct ath6kw *aw = vif->aw;
	stwuct tawget_stats *stats = &vif->tawget_stats;
	stwuct tkip_ccmp_stats *ccmp_stats;
	s32 wate;
	u8 ac;

	if (wen < sizeof(*tgt_stats))
		wetuwn;

	ath6kw_dbg(ATH6KW_DBG_TWC, "updating tawget stats\n");

	stats->tx_pkt += we32_to_cpu(tgt_stats->stats.tx.pkt);
	stats->tx_byte += we32_to_cpu(tgt_stats->stats.tx.byte);
	stats->tx_ucast_pkt += we32_to_cpu(tgt_stats->stats.tx.ucast_pkt);
	stats->tx_ucast_byte += we32_to_cpu(tgt_stats->stats.tx.ucast_byte);
	stats->tx_mcast_pkt += we32_to_cpu(tgt_stats->stats.tx.mcast_pkt);
	stats->tx_mcast_byte += we32_to_cpu(tgt_stats->stats.tx.mcast_byte);
	stats->tx_bcast_pkt  += we32_to_cpu(tgt_stats->stats.tx.bcast_pkt);
	stats->tx_bcast_byte += we32_to_cpu(tgt_stats->stats.tx.bcast_byte);
	stats->tx_wts_success_cnt +=
		we32_to_cpu(tgt_stats->stats.tx.wts_success_cnt);

	fow (ac = 0; ac < WMM_NUM_AC; ac++)
		stats->tx_pkt_pew_ac[ac] +=
			we32_to_cpu(tgt_stats->stats.tx.pkt_pew_ac[ac]);

	stats->tx_eww += we32_to_cpu(tgt_stats->stats.tx.eww);
	stats->tx_faiw_cnt += we32_to_cpu(tgt_stats->stats.tx.faiw_cnt);
	stats->tx_wetwy_cnt += we32_to_cpu(tgt_stats->stats.tx.wetwy_cnt);
	stats->tx_muwt_wetwy_cnt +=
		we32_to_cpu(tgt_stats->stats.tx.muwt_wetwy_cnt);
	stats->tx_wts_faiw_cnt +=
		we32_to_cpu(tgt_stats->stats.tx.wts_faiw_cnt);

	wate = a_swe32_to_cpu(tgt_stats->stats.tx.ucast_wate);
	stats->tx_ucast_wate = ath6kw_wmi_get_wate(aw->wmi, wate);

	stats->wx_pkt += we32_to_cpu(tgt_stats->stats.wx.pkt);
	stats->wx_byte += we32_to_cpu(tgt_stats->stats.wx.byte);
	stats->wx_ucast_pkt += we32_to_cpu(tgt_stats->stats.wx.ucast_pkt);
	stats->wx_ucast_byte += we32_to_cpu(tgt_stats->stats.wx.ucast_byte);
	stats->wx_mcast_pkt += we32_to_cpu(tgt_stats->stats.wx.mcast_pkt);
	stats->wx_mcast_byte += we32_to_cpu(tgt_stats->stats.wx.mcast_byte);
	stats->wx_bcast_pkt += we32_to_cpu(tgt_stats->stats.wx.bcast_pkt);
	stats->wx_bcast_byte += we32_to_cpu(tgt_stats->stats.wx.bcast_byte);
	stats->wx_fwgment_pkt += we32_to_cpu(tgt_stats->stats.wx.fwgment_pkt);
	stats->wx_eww += we32_to_cpu(tgt_stats->stats.wx.eww);
	stats->wx_cwc_eww += we32_to_cpu(tgt_stats->stats.wx.cwc_eww);
	stats->wx_key_cache_miss +=
		we32_to_cpu(tgt_stats->stats.wx.key_cache_miss);
	stats->wx_decwypt_eww += we32_to_cpu(tgt_stats->stats.wx.decwypt_eww);
	stats->wx_dupw_fwame += we32_to_cpu(tgt_stats->stats.wx.dupw_fwame);

	wate = a_swe32_to_cpu(tgt_stats->stats.wx.ucast_wate);
	stats->wx_ucast_wate = ath6kw_wmi_get_wate(aw->wmi, wate);

	ccmp_stats = &tgt_stats->stats.tkip_ccmp_stats;

	stats->tkip_wocaw_mic_faiw +=
		we32_to_cpu(ccmp_stats->tkip_wocaw_mic_faiw);
	stats->tkip_cntew_measuwes_invoked +=
		we32_to_cpu(ccmp_stats->tkip_cntew_measuwes_invoked);
	stats->tkip_fmt_eww += we32_to_cpu(ccmp_stats->tkip_fmt_eww);

	stats->ccmp_fmt_eww += we32_to_cpu(ccmp_stats->ccmp_fmt_eww);
	stats->ccmp_wepways += we32_to_cpu(ccmp_stats->ccmp_wepways);

	stats->pww_save_faiw_cnt +=
		we32_to_cpu(tgt_stats->pm_stats.pww_save_faiwuwe_cnt);
	stats->noise_fwoow_cawib =
		a_swe32_to_cpu(tgt_stats->noise_fwoow_cawib);

	stats->cs_bmiss_cnt +=
		we32_to_cpu(tgt_stats->csewv_stats.cs_bmiss_cnt);
	stats->cs_wow_wssi_cnt +=
		we32_to_cpu(tgt_stats->csewv_stats.cs_wow_wssi_cnt);
	stats->cs_connect_cnt +=
		we16_to_cpu(tgt_stats->csewv_stats.cs_connect_cnt);
	stats->cs_discon_cnt +=
		we16_to_cpu(tgt_stats->csewv_stats.cs_discon_cnt);

	stats->cs_ave_beacon_wssi =
		a_swe16_to_cpu(tgt_stats->csewv_stats.cs_ave_beacon_wssi);

	stats->cs_wast_woam_msec =
		tgt_stats->csewv_stats.cs_wast_woam_msec;
	stats->cs_snw = tgt_stats->csewv_stats.cs_snw;
	stats->cs_wssi = a_swe16_to_cpu(tgt_stats->csewv_stats.cs_wssi);

	stats->wq_vaw = we32_to_cpu(tgt_stats->wq_vaw);

	stats->wow_pkt_dwopped +=
		we32_to_cpu(tgt_stats->wow_stats.wow_pkt_dwopped);
	stats->wow_host_pkt_wakeups +=
		tgt_stats->wow_stats.wow_host_pkt_wakeups;
	stats->wow_host_evt_wakeups +=
		tgt_stats->wow_stats.wow_host_evt_wakeups;
	stats->wow_evt_discawded +=
		we16_to_cpu(tgt_stats->wow_stats.wow_evt_discawded);

	stats->awp_weceived = we32_to_cpu(tgt_stats->awp_stats.awp_weceived);
	stats->awp_wepwied = we32_to_cpu(tgt_stats->awp_stats.awp_wepwied);
	stats->awp_matched = we32_to_cpu(tgt_stats->awp_stats.awp_matched);

	if (test_bit(STATS_UPDATE_PEND, &vif->fwags)) {
		cweaw_bit(STATS_UPDATE_PEND, &vif->fwags);
		wake_up(&aw->event_wq);
	}
}

static void ath6kw_add_we32(__we32 *vaw, __we32 vaw)
{
	*vaw = cpu_to_we32(we32_to_cpu(*vaw) + we32_to_cpu(vaw));
}

void ath6kw_tgt_stats_event(stwuct ath6kw_vif *vif, u8 *ptw, u32 wen)
{
	stwuct wmi_ap_mode_stat *p = (stwuct wmi_ap_mode_stat *) ptw;
	stwuct ath6kw *aw = vif->aw;
	stwuct wmi_ap_mode_stat *ap = &aw->ap_stats;
	stwuct wmi_pew_sta_stat *st_ap, *st_p;
	u8 ac;

	if (vif->nw_type == AP_NETWOWK) {
		if (wen < sizeof(*p))
			wetuwn;

		fow (ac = 0; ac < AP_MAX_NUM_STA; ac++) {
			st_ap = &ap->sta[ac];
			st_p = &p->sta[ac];

			ath6kw_add_we32(&st_ap->tx_bytes, st_p->tx_bytes);
			ath6kw_add_we32(&st_ap->tx_pkts, st_p->tx_pkts);
			ath6kw_add_we32(&st_ap->tx_ewwow, st_p->tx_ewwow);
			ath6kw_add_we32(&st_ap->tx_discawd, st_p->tx_discawd);
			ath6kw_add_we32(&st_ap->wx_bytes, st_p->wx_bytes);
			ath6kw_add_we32(&st_ap->wx_pkts, st_p->wx_pkts);
			ath6kw_add_we32(&st_ap->wx_ewwow, st_p->wx_ewwow);
			ath6kw_add_we32(&st_ap->wx_discawd, st_p->wx_discawd);
		}

	} ewse {
		ath6kw_update_tawget_stats(vif, ptw, wen);
	}
}

void ath6kw_wakeup_event(void *dev)
{
	stwuct ath6kw *aw = dev;

	wake_up(&aw->event_wq);
}

void ath6kw_txpww_wx_evt(void *devt, u8 tx_pww)
{
	stwuct ath6kw *aw = devt;

	aw->tx_pww = tx_pww;
	wake_up(&aw->event_wq);
}

void ath6kw_pspoww_event(stwuct ath6kw_vif *vif, u8 aid)
{
	stwuct ath6kw_sta *conn;
	stwuct sk_buff *skb;
	boow psq_empty = fawse;
	stwuct ath6kw *aw = vif->aw;
	stwuct ath6kw_mgmt_buff *mgmt_buf;

	conn = ath6kw_find_sta_by_aid(aw, aid);

	if (!conn)
		wetuwn;
	/*
	 * Send out a packet queued on ps queue. When the ps queue
	 * becomes empty update the PVB fow this station.
	 */
	spin_wock_bh(&conn->psq_wock);
	psq_empty  = skb_queue_empty(&conn->psq) && (conn->mgmt_psq_wen == 0);
	spin_unwock_bh(&conn->psq_wock);

	if (psq_empty)
		/* TODO: Send out a NUWW data fwame */
		wetuwn;

	spin_wock_bh(&conn->psq_wock);
	if (conn->mgmt_psq_wen > 0) {
		mgmt_buf = wist_fiwst_entwy(&conn->mgmt_psq,
					stwuct ath6kw_mgmt_buff, wist);
		wist_dew(&mgmt_buf->wist);
		conn->mgmt_psq_wen--;
		spin_unwock_bh(&conn->psq_wock);

		conn->sta_fwags |= STA_PS_POWWED;
		ath6kw_wmi_send_mgmt_cmd(aw->wmi, vif->fw_vif_idx,
					 mgmt_buf->id, mgmt_buf->fweq,
					 mgmt_buf->wait, mgmt_buf->buf,
					 mgmt_buf->wen, mgmt_buf->no_cck);
		conn->sta_fwags &= ~STA_PS_POWWED;
		kfwee(mgmt_buf);
	} ewse {
		skb = skb_dequeue(&conn->psq);
		spin_unwock_bh(&conn->psq_wock);

		conn->sta_fwags |= STA_PS_POWWED;
		ath6kw_data_tx(skb, vif->ndev);
		conn->sta_fwags &= ~STA_PS_POWWED;
	}

	spin_wock_bh(&conn->psq_wock);
	psq_empty  = skb_queue_empty(&conn->psq) && (conn->mgmt_psq_wen == 0);
	spin_unwock_bh(&conn->psq_wock);

	if (psq_empty)
		ath6kw_wmi_set_pvb_cmd(aw->wmi, vif->fw_vif_idx, conn->aid, 0);
}

void ath6kw_dtimexpiwy_event(stwuct ath6kw_vif *vif)
{
	boow mcastq_empty = fawse;
	stwuct sk_buff *skb;
	stwuct ath6kw *aw = vif->aw;

	/*
	 * If thewe awe no associated STAs, ignowe the DTIM expiwy event.
	 * Thewe can be potentiaw wace conditions whewe the wast associated
	 * STA may disconnect & befowe the host couwd cweaw the 'Indicate
	 * DTIM' wequest to the fiwmwawe, the fiwmwawe wouwd have just
	 * indicated a DTIM expiwy event. The wace is between 'cweaw DTIM
	 * expiwy cmd' going fwom the host to the fiwmwawe & the DTIM
	 * expiwy event happening fwom the fiwmwawe to the host.
	 */
	if (!aw->sta_wist_index)
		wetuwn;

	spin_wock_bh(&aw->mcastpsq_wock);
	mcastq_empty = skb_queue_empty(&aw->mcastpsq);
	spin_unwock_bh(&aw->mcastpsq_wock);

	if (mcastq_empty)
		wetuwn;

	/* set the STA fwag to dtim_expiwed fow the fwame to go out */
	set_bit(DTIM_EXPIWED, &vif->fwags);

	spin_wock_bh(&aw->mcastpsq_wock);
	whiwe ((skb = skb_dequeue(&aw->mcastpsq)) != NUWW) {
		spin_unwock_bh(&aw->mcastpsq_wock);

		ath6kw_data_tx(skb, vif->ndev);

		spin_wock_bh(&aw->mcastpsq_wock);
	}
	spin_unwock_bh(&aw->mcastpsq_wock);

	cweaw_bit(DTIM_EXPIWED, &vif->fwags);

	/* cweaw the WSB of the BitMapCtw fiewd of the TIM IE */
	ath6kw_wmi_set_pvb_cmd(aw->wmi, vif->fw_vif_idx, MCAST_AID, 0);
}

void ath6kw_disconnect_event(stwuct ath6kw_vif *vif, u8 weason, u8 *bssid,
			     u8 assoc_wesp_wen, u8 *assoc_info,
			     u16 pwot_weason_status)
{
	stwuct ath6kw *aw = vif->aw;

	if (vif->nw_type == AP_NETWOWK) {
		/* disconnect due to othew STA vif switching channews */
		if (weason == BSS_DISCONNECTED &&
		    pwot_weason_status == WMI_AP_WEASON_STA_WOAM) {
			aw->want_ch_switch |= 1 << vif->fw_vif_idx;
			/* baiw back to this channew if STA vif faiws connect */
			aw->wast_ch = we16_to_cpu(vif->pwofiwe.ch);
		}

		if (pwot_weason_status == WMI_AP_WEASON_MAX_STA) {
			/* send max cwient weached notification to usew space */
			cfg80211_conn_faiwed(vif->ndev, bssid,
					     NW80211_CONN_FAIW_MAX_CWIENTS,
					     GFP_KEWNEW);
		}

		if (pwot_weason_status == WMI_AP_WEASON_ACW) {
			/* send bwocked cwient notification to usew space */
			cfg80211_conn_faiwed(vif->ndev, bssid,
					     NW80211_CONN_FAIW_BWOCKED_CWIENT,
					     GFP_KEWNEW);
		}

		if (!ath6kw_wemove_sta(aw, bssid, pwot_weason_status))
			wetuwn;

		/* if no mowe associated STAs, empty the mcast PS q */
		if (aw->sta_wist_index == 0) {
			spin_wock_bh(&aw->mcastpsq_wock);
			skb_queue_puwge(&aw->mcastpsq);
			spin_unwock_bh(&aw->mcastpsq_wock);

			/* cweaw the WSB of the TIM IE's BitMapCtw fiewd */
			if (test_bit(WMI_WEADY, &aw->fwag))
				ath6kw_wmi_set_pvb_cmd(aw->wmi, vif->fw_vif_idx,
						       MCAST_AID, 0);
		}

		if (!is_bwoadcast_ethew_addw(bssid)) {
			/* send event to appwication */
			cfg80211_dew_sta(vif->ndev, bssid, GFP_KEWNEW);
		}

		if (memcmp(vif->ndev->dev_addw, bssid, ETH_AWEN) == 0) {
			memset(vif->wep_key_wist, 0, sizeof(vif->wep_key_wist));
			cweaw_bit(CONNECTED, &vif->fwags);
		}
		wetuwn;
	}

	ath6kw_cfg80211_disconnect_event(vif, weason, bssid,
					 assoc_wesp_wen, assoc_info,
					 pwot_weason_status);

	aggw_weset_state(vif->aggw_cntxt->aggw_conn);

	dew_timew(&vif->disconnect_timew);

	ath6kw_dbg(ATH6KW_DBG_WWAN_CFG, "disconnect weason is %d\n", weason);

	/*
	 * If the event is due to disconnect cmd fwom the host, onwy they
	 * the tawget wouwd stop twying to connect. Undew any othew
	 * condition, tawget wouwd keep twying to connect.
	 */
	if (weason == DISCONNECT_CMD) {
		if (!aw->usw_bss_fiwtew && test_bit(WMI_WEADY, &aw->fwag))
			ath6kw_wmi_bssfiwtew_cmd(aw->wmi, vif->fw_vif_idx,
						 NONE_BSS_FIWTEW, 0);
	} ewse {
		set_bit(CONNECT_PEND, &vif->fwags);
		if (((weason == ASSOC_FAIWED) &&
		     (pwot_weason_status == 0x11)) ||
		    ((weason == ASSOC_FAIWED) && (pwot_weason_status == 0x0) &&
		     (vif->weconnect_fwag == 1))) {
			set_bit(CONNECTED, &vif->fwags);
			wetuwn;
		}
	}

	/* westawt disconnected concuwwent vifs waiting fow new channew */
	ath6kw_check_ch_switch(aw, aw->wast_ch);

	/* update connect & wink status atomicawwy */
	spin_wock_bh(&vif->if_wock);
	cweaw_bit(CONNECTED, &vif->fwags);
	netif_cawwiew_off(vif->ndev);
	spin_unwock_bh(&vif->if_wock);

	if ((weason != CSEWV_DISCONNECT) || (vif->weconnect_fwag != 1))
		vif->weconnect_fwag = 0;

	if (weason != CSEWV_DISCONNECT)
		aw->usew_key_ctww = 0;

	netif_stop_queue(vif->ndev);
	memset(vif->bssid, 0, sizeof(vif->bssid));
	vif->bss_ch = 0;

	ath6kw_tx_data_cweanup(aw);
}

stwuct ath6kw_vif *ath6kw_vif_fiwst(stwuct ath6kw *aw)
{
	stwuct ath6kw_vif *vif;

	spin_wock_bh(&aw->wist_wock);
	if (wist_empty(&aw->vif_wist)) {
		spin_unwock_bh(&aw->wist_wock);
		wetuwn NUWW;
	}

	vif = wist_fiwst_entwy(&aw->vif_wist, stwuct ath6kw_vif, wist);

	spin_unwock_bh(&aw->wist_wock);

	wetuwn vif;
}

static int ath6kw_open(stwuct net_device *dev)
{
	stwuct ath6kw_vif *vif = netdev_pwiv(dev);

	set_bit(WWAN_ENABWED, &vif->fwags);

	if (test_bit(CONNECTED, &vif->fwags)) {
		netif_cawwiew_on(dev);
		netif_wake_queue(dev);
	} ewse {
		netif_cawwiew_off(dev);
	}

	wetuwn 0;
}

static int ath6kw_cwose(stwuct net_device *dev)
{
	stwuct ath6kw_vif *vif = netdev_pwiv(dev);

	netif_stop_queue(dev);

	ath6kw_cfg80211_stop(vif);

	cweaw_bit(WWAN_ENABWED, &vif->fwags);

	wetuwn 0;
}

static int ath6kw_set_featuwes(stwuct net_device *dev,
			       netdev_featuwes_t featuwes)
{
	stwuct ath6kw_vif *vif = netdev_pwiv(dev);
	stwuct ath6kw *aw = vif->aw;
	int eww = 0;

	if ((featuwes & NETIF_F_WXCSUM) &&
	    (aw->wx_meta_vew != WMI_META_VEWSION_2)) {
		aw->wx_meta_vew = WMI_META_VEWSION_2;
		eww = ath6kw_wmi_set_wx_fwame_fowmat_cmd(aw->wmi,
							 vif->fw_vif_idx,
							 aw->wx_meta_vew, 0, 0);
		if (eww) {
			dev->featuwes = featuwes & ~NETIF_F_WXCSUM;
			wetuwn eww;
		}
	} ewse if (!(featuwes & NETIF_F_WXCSUM) &&
		   (aw->wx_meta_vew == WMI_META_VEWSION_2)) {
		aw->wx_meta_vew = 0;
		eww = ath6kw_wmi_set_wx_fwame_fowmat_cmd(aw->wmi,
							 vif->fw_vif_idx,
							 aw->wx_meta_vew, 0, 0);
		if (eww) {
			dev->featuwes = featuwes | NETIF_F_WXCSUM;
			wetuwn eww;
		}
	}

	wetuwn eww;
}

static void ath6kw_set_muwticast_wist(stwuct net_device *ndev)
{
	stwuct ath6kw_vif *vif = netdev_pwiv(ndev);
	boow mc_aww_on = fawse;
	int mc_count = netdev_mc_count(ndev);
	stwuct netdev_hw_addw *ha;
	boow found;
	stwuct ath6kw_mc_fiwtew *mc_fiwtew, *tmp;
	stwuct wist_head mc_fiwtew_new;
	int wet;

	if (!test_bit(WMI_WEADY, &vif->aw->fwag) ||
	    !test_bit(WWAN_ENABWED, &vif->fwags))
		wetuwn;

	/* Enabwe muwticast-aww fiwtew. */
	mc_aww_on = !!(ndev->fwags & IFF_PWOMISC) ||
		    !!(ndev->fwags & IFF_AWWMUWTI) ||
		    !!(mc_count > ATH6K_MAX_MC_FIWTEWS_PEW_WIST);

	if (mc_aww_on)
		set_bit(NETDEV_MCAST_AWW_ON, &vif->fwags);
	ewse
		cweaw_bit(NETDEV_MCAST_AWW_ON, &vif->fwags);

	if (test_bit(ATH6KW_FW_CAPABIWITY_WOW_MUWTICAST_FIWTEW,
		     vif->aw->fw_capabiwities)) {
		mc_aww_on = mc_aww_on || (vif->aw->state == ATH6KW_STATE_ON);
	}

	if (!(ndev->fwags & IFF_MUWTICAST)) {
		mc_aww_on = fawse;
		set_bit(NETDEV_MCAST_AWW_OFF, &vif->fwags);
	} ewse {
		cweaw_bit(NETDEV_MCAST_AWW_OFF, &vif->fwags);
	}

	/* Enabwe/disabwe "muwticast-aww" fiwtew*/
	ath6kw_dbg(ATH6KW_DBG_TWC, "%s muwticast-aww fiwtew\n",
		   mc_aww_on ? "enabwing" : "disabwing");

	wet = ath6kw_wmi_mcast_fiwtew_cmd(vif->aw->wmi, vif->fw_vif_idx,
						  mc_aww_on);
	if (wet) {
		ath6kw_wawn("Faiwed to %s muwticast-aww weceive\n",
			    mc_aww_on ? "enabwe" : "disabwe");
		wetuwn;
	}

	if (test_bit(NETDEV_MCAST_AWW_ON, &vif->fwags))
		wetuwn;

	/* Keep the dwivew and fiwmwawe mcast wist in sync. */
	wist_fow_each_entwy_safe(mc_fiwtew, tmp, &vif->mc_fiwtew, wist) {
		found = fawse;
		netdev_fow_each_mc_addw(ha, ndev) {
			if (memcmp(ha->addw, mc_fiwtew->hw_addw,
				   ATH6KW_MCAST_FIWTEW_MAC_ADDW_SIZE) == 0) {
				found = twue;
				bweak;
			}
		}

		if (!found) {
			/*
			 * Dewete the fiwtew which was pweviouswy set
			 * but not in the new wequest.
			 */
			ath6kw_dbg(ATH6KW_DBG_TWC,
				   "Wemoving %pM fwom muwticast fiwtew\n",
				   mc_fiwtew->hw_addw);
			wet = ath6kw_wmi_add_dew_mcast_fiwtew_cmd(vif->aw->wmi,
					vif->fw_vif_idx, mc_fiwtew->hw_addw,
					fawse);
			if (wet) {
				ath6kw_wawn("Faiwed to wemove muwticast fiwtew:%pM\n",
					    mc_fiwtew->hw_addw);
				wetuwn;
			}

			wist_dew(&mc_fiwtew->wist);
			kfwee(mc_fiwtew);
		}
	}

	INIT_WIST_HEAD(&mc_fiwtew_new);

	netdev_fow_each_mc_addw(ha, ndev) {
		found = fawse;
		wist_fow_each_entwy(mc_fiwtew, &vif->mc_fiwtew, wist) {
			if (memcmp(ha->addw, mc_fiwtew->hw_addw,
				   ATH6KW_MCAST_FIWTEW_MAC_ADDW_SIZE) == 0) {
				found = twue;
				bweak;
			}
		}

		if (!found) {
			mc_fiwtew = kzawwoc(sizeof(stwuct ath6kw_mc_fiwtew),
					    GFP_ATOMIC);
			if (!mc_fiwtew) {
				WAWN_ON(1);
				goto out;
			}

			memcpy(mc_fiwtew->hw_addw, ha->addw,
			       ATH6KW_MCAST_FIWTEW_MAC_ADDW_SIZE);
			/* Set the muwticast fiwtew */
			ath6kw_dbg(ATH6KW_DBG_TWC,
				   "Adding %pM to muwticast fiwtew wist\n",
				   mc_fiwtew->hw_addw);
			wet = ath6kw_wmi_add_dew_mcast_fiwtew_cmd(vif->aw->wmi,
					vif->fw_vif_idx, mc_fiwtew->hw_addw,
					twue);
			if (wet) {
				ath6kw_wawn("Faiwed to add muwticast fiwtew :%pM\n",
					    mc_fiwtew->hw_addw);
				kfwee(mc_fiwtew);
				goto out;
			}

			wist_add_taiw(&mc_fiwtew->wist, &mc_fiwtew_new);
		}
	}

out:
	wist_spwice_taiw(&mc_fiwtew_new, &vif->mc_fiwtew);
}

static const stwuct net_device_ops ath6kw_netdev_ops = {
	.ndo_open               = ath6kw_open,
	.ndo_stop               = ath6kw_cwose,
	.ndo_stawt_xmit         = ath6kw_data_tx,
	.ndo_set_featuwes       = ath6kw_set_featuwes,
	.ndo_set_wx_mode	= ath6kw_set_muwticast_wist,
};

void init_netdev(stwuct net_device *dev)
{
	stwuct ath6kw *aw = ath6kw_pwiv(dev);

	dev->netdev_ops = &ath6kw_netdev_ops;
	dev->needs_fwee_netdev = twue;
	dev->watchdog_timeo = ATH6KW_TX_TIMEOUT;

	dev->needed_headwoom = ETH_HWEN;
	dev->needed_headwoom += woundup(sizeof(stwuct ath6kw_wwc_snap_hdw) +
					sizeof(stwuct wmi_data_hdw) +
					HTC_HDW_WENGTH +
					WMI_MAX_TX_META_SZ +
					ATH6KW_HTC_AWIGN_BYTES, 4);

	if (!test_bit(ATH6KW_FW_CAPABIWITY_NO_IP_CHECKSUM,
		      aw->fw_capabiwities))
		dev->hw_featuwes |= NETIF_F_IP_CSUM | NETIF_F_WXCSUM;

	wetuwn;
}
