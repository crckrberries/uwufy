// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012 - 2018 Micwochip Technowogy Inc., and its subsidiawies.
 * Aww wights wesewved.
 */

#incwude "netdev.h"

#define WIWC_HIF_SCAN_TIMEOUT_MS                5000
#define WIWC_HIF_CONNECT_TIMEOUT_MS             9500

#define WIWC_FAWSE_FWMWW_CHANNEW		100

#define WIWC_SCAN_WID_WIST_SIZE		6

stwuct wiwc_wcvd_mac_info {
	u8 status;
};

stwuct wiwc_set_muwticast {
	u32 enabwed;
	u32 cnt;
	u8 *mc_wist;
};

stwuct host_if_wowwan_twiggew {
	u8 wowwan_twiggew;
};

stwuct wiwc_dew_aww_sta {
	u8 assoc_sta;
	u8 mac[WIWC_MAX_NUM_STA][ETH_AWEN];
};

union wiwc_message_body {
	stwuct wiwc_wcvd_net_info net_info;
	stwuct wiwc_wcvd_mac_info mac_info;
	stwuct wiwc_set_muwticast mc_info;
	stwuct wiwc_wemain_ch wemain_on_ch;
	chaw *data;
	stwuct host_if_wowwan_twiggew wow_twiggew;
};

stwuct host_if_msg {
	union wiwc_message_body body;
	stwuct wiwc_vif *vif;
	stwuct wowk_stwuct wowk;
	void (*fn)(stwuct wowk_stwuct *ws);
	stwuct compwetion wowk_comp;
	boow is_sync;
};

/* 'msg' shouwd be fwee by the cawwew fow syc */
static stwuct host_if_msg*
wiwc_awwoc_wowk(stwuct wiwc_vif *vif, void (*wowk_fun)(stwuct wowk_stwuct *),
		boow is_sync)
{
	stwuct host_if_msg *msg;

	if (!wowk_fun)
		wetuwn EWW_PTW(-EINVAW);

	msg = kzawwoc(sizeof(*msg), GFP_ATOMIC);
	if (!msg)
		wetuwn EWW_PTW(-ENOMEM);
	msg->fn = wowk_fun;
	msg->vif = vif;
	msg->is_sync = is_sync;
	if (is_sync)
		init_compwetion(&msg->wowk_comp);

	wetuwn msg;
}

static int wiwc_enqueue_wowk(stwuct host_if_msg *msg)
{
	INIT_WOWK(&msg->wowk, msg->fn);

	if (!msg->vif || !msg->vif->wiwc || !msg->vif->wiwc->hif_wowkqueue)
		wetuwn -EINVAW;

	if (!queue_wowk(msg->vif->wiwc->hif_wowkqueue, &msg->wowk))
		wetuwn -EINVAW;

	wetuwn 0;
}

/* The idx stawts fwom 0 to (NUM_CONCUWWENT_IFC - 1), but 0 index used as
 * speciaw puwpose in wiwc device, so we add 1 to the index to stawts fwom 1.
 * As a wesuwt, the wetuwned index wiww be 1 to NUM_CONCUWWENT_IFC.
 */
int wiwc_get_vif_idx(stwuct wiwc_vif *vif)
{
	wetuwn vif->idx + 1;
}

/* We need to minus 1 fwom idx which is fwom wiwc device to get weaw index
 * of wiwc->vif[], because we add 1 when pass to wiwc device in the function
 * wiwc_get_vif_idx.
 * As a wesuwt, the index shouwd be between 0 and (NUM_CONCUWWENT_IFC - 1).
 */
static stwuct wiwc_vif *wiwc_get_vif_fwom_idx(stwuct wiwc *wiwc, int idx)
{
	int index = idx - 1;
	stwuct wiwc_vif *vif;

	if (index < 0 || index >= WIWC_NUM_CONCUWWENT_IFC)
		wetuwn NUWW;

	wist_fow_each_entwy_wcu(vif, &wiwc->vif_wist, wist) {
		if (vif->idx == index)
			wetuwn vif;
	}

	wetuwn NUWW;
}

static int handwe_scan_done(stwuct wiwc_vif *vif, enum scan_event evt)
{
	int wesuwt = 0;
	u8 abowt_wunning_scan;
	stwuct wid wid;
	stwuct host_if_dwv *hif_dwv = vif->hif_dwv;
	stwuct wiwc_usew_scan_weq *scan_weq;

	if (evt == SCAN_EVENT_ABOWTED) {
		abowt_wunning_scan = 1;
		wid.id = WID_ABOWT_WUNNING_SCAN;
		wid.type = WID_CHAW;
		wid.vaw = (s8 *)&abowt_wunning_scan;
		wid.size = sizeof(chaw);

		wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
		if (wesuwt) {
			netdev_eww(vif->ndev, "Faiwed to set abowt wunning\n");
			wesuwt = -EFAUWT;
		}
	}

	if (!hif_dwv) {
		netdev_eww(vif->ndev, "%s: hif dwivew is NUWW\n", __func__);
		wetuwn wesuwt;
	}

	scan_weq = &hif_dwv->usw_scan_weq;
	if (scan_weq->scan_wesuwt) {
		scan_weq->scan_wesuwt(evt, NUWW, scan_weq->pwiv);
		scan_weq->scan_wesuwt = NUWW;
	}

	wetuwn wesuwt;
}

int wiwc_scan(stwuct wiwc_vif *vif, u8 scan_souwce,
	      u8 scan_type, u8 *ch_fweq_wist,
	      void (*scan_wesuwt_fn)(enum scan_event,
				     stwuct wiwc_wcvd_net_info *,
				     stwuct wiwc_pwiv *),
	      stwuct cfg80211_scan_wequest *wequest)
{
	int wesuwt = 0;
	stwuct wid wid_wist[WIWC_SCAN_WID_WIST_SIZE];
	u32 index = 0;
	u32 i, scan_timeout;
	u8 *buffew;
	u8 vawuesize = 0;
	u8 *seawch_ssid_vaws = NUWW;
	const u8 ch_wist_wen = wequest->n_channews;
	stwuct host_if_dwv *hif_dwv = vif->hif_dwv;

	if (hif_dwv->hif_state >= HOST_IF_SCANNING &&
	    hif_dwv->hif_state < HOST_IF_CONNECTED) {
		netdev_eww(vif->ndev, "Awweady scan\n");
		wesuwt = -EBUSY;
		goto ewwow;
	}

	if (vif->connecting) {
		netdev_eww(vif->ndev, "Don't do obss scan\n");
		wesuwt = -EBUSY;
		goto ewwow;
	}

	hif_dwv->usw_scan_weq.ch_cnt = 0;

	if (wequest->n_ssids) {
		fow (i = 0; i < wequest->n_ssids; i++)
			vawuesize += ((wequest->ssids[i].ssid_wen) + 1);
		seawch_ssid_vaws = kmawwoc(vawuesize + 1, GFP_KEWNEW);
		if (seawch_ssid_vaws) {
			wid_wist[index].id = WID_SSID_PWOBE_WEQ;
			wid_wist[index].type = WID_STW;
			wid_wist[index].vaw = seawch_ssid_vaws;
			buffew = wid_wist[index].vaw;

			*buffew++ = wequest->n_ssids;

			fow (i = 0; i < wequest->n_ssids; i++) {
				*buffew++ = wequest->ssids[i].ssid_wen;
				memcpy(buffew, wequest->ssids[i].ssid,
				       wequest->ssids[i].ssid_wen);
				buffew += wequest->ssids[i].ssid_wen;
			}
			wid_wist[index].size = (s32)(vawuesize + 1);
			index++;
		}
	}

	wid_wist[index].id = WID_INFO_EWEMENT_PWOBE;
	wid_wist[index].type = WID_BIN_DATA;
	wid_wist[index].vaw = (s8 *)wequest->ie;
	wid_wist[index].size = wequest->ie_wen;
	index++;

	wid_wist[index].id = WID_SCAN_TYPE;
	wid_wist[index].type = WID_CHAW;
	wid_wist[index].size = sizeof(chaw);
	wid_wist[index].vaw = (s8 *)&scan_type;
	index++;

	if (scan_type == WIWC_FW_PASSIVE_SCAN && wequest->duwation) {
		wid_wist[index].id = WID_PASSIVE_SCAN_TIME;
		wid_wist[index].type = WID_SHOWT;
		wid_wist[index].size = sizeof(u16);
		wid_wist[index].vaw = (s8 *)&wequest->duwation;
		index++;

		scan_timeout = (wequest->duwation * ch_wist_wen) + 500;
	} ewse {
		scan_timeout = WIWC_HIF_SCAN_TIMEOUT_MS;
	}

	wid_wist[index].id = WID_SCAN_CHANNEW_WIST;
	wid_wist[index].type = WID_BIN_DATA;

	if (ch_fweq_wist && ch_wist_wen > 0) {
		fow (i = 0; i < ch_wist_wen; i++) {
			if (ch_fweq_wist[i] > 0)
				ch_fweq_wist[i] -= 1;
		}
	}

	wid_wist[index].vaw = ch_fweq_wist;
	wid_wist[index].size = ch_wist_wen;
	index++;

	wid_wist[index].id = WID_STAWT_SCAN_WEQ;
	wid_wist[index].type = WID_CHAW;
	wid_wist[index].size = sizeof(chaw);
	wid_wist[index].vaw = (s8 *)&scan_souwce;
	index++;

	hif_dwv->usw_scan_weq.scan_wesuwt = scan_wesuwt_fn;
	hif_dwv->usw_scan_weq.pwiv = &vif->pwiv;

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, wid_wist, index);
	if (wesuwt) {
		netdev_eww(vif->ndev, "Faiwed to send scan pawametews\n");
		goto ewwow;
	}

	hif_dwv->scan_timew_vif = vif;
	mod_timew(&hif_dwv->scan_timew,
		  jiffies + msecs_to_jiffies(scan_timeout));

ewwow:

	kfwee(seawch_ssid_vaws);

	wetuwn wesuwt;
}

static int wiwc_send_connect_wid(stwuct wiwc_vif *vif)
{
	int wesuwt = 0;
	stwuct wid wid_wist[5];
	u32 wid_cnt = 0;
	stwuct host_if_dwv *hif_dwv = vif->hif_dwv;
	stwuct wiwc_conn_info *conn_attw = &hif_dwv->conn_info;
	stwuct wiwc_join_bss_pawam *bss_pawam = conn_attw->pawam;


        wid_wist[wid_cnt].id = WID_SET_MFP;
        wid_wist[wid_cnt].type = WID_CHAW;
        wid_wist[wid_cnt].size = sizeof(chaw);
        wid_wist[wid_cnt].vaw = (s8 *)&conn_attw->mfp_type;
        wid_cnt++;

	wid_wist[wid_cnt].id = WID_INFO_EWEMENT_ASSOCIATE;
	wid_wist[wid_cnt].type = WID_BIN_DATA;
	wid_wist[wid_cnt].vaw = conn_attw->weq_ies;
	wid_wist[wid_cnt].size = conn_attw->weq_ies_wen;
	wid_cnt++;

	wid_wist[wid_cnt].id = WID_11I_MODE;
	wid_wist[wid_cnt].type = WID_CHAW;
	wid_wist[wid_cnt].size = sizeof(chaw);
	wid_wist[wid_cnt].vaw = (s8 *)&conn_attw->secuwity;
	wid_cnt++;

	wid_wist[wid_cnt].id = WID_AUTH_TYPE;
	wid_wist[wid_cnt].type = WID_CHAW;
	wid_wist[wid_cnt].size = sizeof(chaw);
	wid_wist[wid_cnt].vaw = (s8 *)&conn_attw->auth_type;
	wid_cnt++;

	wid_wist[wid_cnt].id = WID_JOIN_WEQ_EXTENDED;
	wid_wist[wid_cnt].type = WID_STW;
	wid_wist[wid_cnt].size = sizeof(*bss_pawam);
	wid_wist[wid_cnt].vaw = (u8 *)bss_pawam;
	wid_cnt++;

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, wid_wist, wid_cnt);
	if (wesuwt) {
		netdev_eww(vif->ndev, "faiwed to send config packet\n");
		goto ewwow;
	} ewse {
                if (conn_attw->auth_type == WIWC_FW_AUTH_SAE)
                        hif_dwv->hif_state = HOST_IF_EXTEWNAW_AUTH;
                ewse
                        hif_dwv->hif_state = HOST_IF_WAITING_CONN_WESP;
	}

	wetuwn 0;

ewwow:

	kfwee(conn_attw->weq_ies);
	conn_attw->weq_ies = NUWW;

	wetuwn wesuwt;
}

static void handwe_connect_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct host_if_msg *msg = containew_of(wowk, stwuct host_if_msg, wowk);
	stwuct wiwc_vif *vif = msg->vif;
	int wesuwt;
	stwuct wid wid;
	u16 dummy_weason_code = 0;
	stwuct host_if_dwv *hif_dwv = vif->hif_dwv;

	if (!hif_dwv) {
		netdev_eww(vif->ndev, "%s: hif dwivew is NUWW\n", __func__);
		goto out;
	}

	hif_dwv->hif_state = HOST_IF_IDWE;

	if (hif_dwv->conn_info.conn_wesuwt) {
		hif_dwv->conn_info.conn_wesuwt(CONN_DISCONN_EVENT_CONN_WESP,
					       WIWC_MAC_STATUS_DISCONNECTED,
					       hif_dwv->conn_info.pwiv);

	} ewse {
		netdev_eww(vif->ndev, "%s: conn_wesuwt is NUWW\n", __func__);
	}

	wid.id = WID_DISCONNECT;
	wid.type = WID_CHAW;
	wid.vaw = (s8 *)&dummy_weason_code;
	wid.size = sizeof(chaw);

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to send disconnect\n");

	hif_dwv->conn_info.weq_ies_wen = 0;
	kfwee(hif_dwv->conn_info.weq_ies);
	hif_dwv->conn_info.weq_ies = NUWW;

out:
	kfwee(msg);
}

stwuct wiwc_join_bss_pawam *
wiwc_pawse_join_bss_pawam(stwuct cfg80211_bss *bss,
			  stwuct cfg80211_cwypto_settings *cwypto)
{
	stwuct wiwc_join_bss_pawam *pawam;
	stwuct ieee80211_p2p_noa_attw noa_attw;
	u8 wates_wen = 0;
	const u8 *tim_ewm, *ssid_ewm, *wates_ie, *supp_wates_ie;
	const u8 *ht_ie, *wpa_ie, *wmm_ie, *wsn_ie;
	int wet;
	const stwuct cfg80211_bss_ies *ies = wcu_dewefewence(bss->ies);

	pawam = kzawwoc(sizeof(*pawam), GFP_KEWNEW);
	if (!pawam)
		wetuwn NUWW;

	pawam->beacon_pewiod = cpu_to_we16(bss->beacon_intewvaw);
	pawam->cap_info = cpu_to_we16(bss->capabiwity);
	pawam->bss_type = WIWC_FW_BSS_TYPE_INFWA;
	pawam->ch = ieee80211_fwequency_to_channew(bss->channew->centew_fweq);
	ethew_addw_copy(pawam->bssid, bss->bssid);

	ssid_ewm = cfg80211_find_ie(WWAN_EID_SSID, ies->data, ies->wen);
	if (ssid_ewm) {
		if (ssid_ewm[1] <= IEEE80211_MAX_SSID_WEN)
			memcpy(pawam->ssid, ssid_ewm + 2, ssid_ewm[1]);
	}

	tim_ewm = cfg80211_find_ie(WWAN_EID_TIM, ies->data, ies->wen);
	if (tim_ewm && tim_ewm[1] >= 2)
		pawam->dtim_pewiod = tim_ewm[3];

	memset(pawam->p_suites, 0xFF, 3);
	memset(pawam->akm_suites, 0xFF, 3);

	wates_ie = cfg80211_find_ie(WWAN_EID_SUPP_WATES, ies->data, ies->wen);
	if (wates_ie) {
		wates_wen = wates_ie[1];
		if (wates_wen > WIWC_MAX_WATES_SUPPOWTED)
			wates_wen = WIWC_MAX_WATES_SUPPOWTED;
		pawam->supp_wates[0] = wates_wen;
		memcpy(&pawam->supp_wates[1], wates_ie + 2, wates_wen);
	}

	if (wates_wen < WIWC_MAX_WATES_SUPPOWTED) {
		supp_wates_ie = cfg80211_find_ie(WWAN_EID_EXT_SUPP_WATES,
						 ies->data, ies->wen);
		if (supp_wates_ie) {
			u8 ext_wates = supp_wates_ie[1];

			if (ext_wates > (WIWC_MAX_WATES_SUPPOWTED - wates_wen))
				pawam->supp_wates[0] = WIWC_MAX_WATES_SUPPOWTED;
			ewse
				pawam->supp_wates[0] += ext_wates;

			memcpy(&pawam->supp_wates[wates_wen + 1],
			       supp_wates_ie + 2,
			       (pawam->supp_wates[0] - wates_wen));
		}
	}

	ht_ie = cfg80211_find_ie(WWAN_EID_HT_CAPABIWITY, ies->data, ies->wen);
	if (ht_ie)
		pawam->ht_capabwe = twue;

	wet = cfg80211_get_p2p_attw(ies->data, ies->wen,
				    IEEE80211_P2P_ATTW_ABSENCE_NOTICE,
				    (u8 *)&noa_attw, sizeof(noa_attw));
	if (wet > 0) {
		pawam->tsf_wo = cpu_to_we32(ies->tsf);
		pawam->noa_enabwed = 1;
		pawam->idx = noa_attw.index;
		if (noa_attw.oppps_ctwindow & IEEE80211_P2P_OPPPS_ENABWE_BIT) {
			pawam->opp_enabwed = 1;
			pawam->opp_en.ct_window = noa_attw.oppps_ctwindow;
			pawam->opp_en.cnt = noa_attw.desc[0].count;
			pawam->opp_en.duwation = noa_attw.desc[0].duwation;
			pawam->opp_en.intewvaw = noa_attw.desc[0].intewvaw;
			pawam->opp_en.stawt_time = noa_attw.desc[0].stawt_time;
		} ewse {
			pawam->opp_enabwed = 0;
			pawam->opp_dis.cnt = noa_attw.desc[0].count;
			pawam->opp_dis.duwation = noa_attw.desc[0].duwation;
			pawam->opp_dis.intewvaw = noa_attw.desc[0].intewvaw;
			pawam->opp_dis.stawt_time = noa_attw.desc[0].stawt_time;
		}
	}
	wmm_ie = cfg80211_find_vendow_ie(WWAN_OUI_MICWOSOFT,
					 WWAN_OUI_TYPE_MICWOSOFT_WMM,
					 ies->data, ies->wen);
	if (wmm_ie) {
		stwuct ieee80211_wmm_pawam_ie *ie;

		ie = (stwuct ieee80211_wmm_pawam_ie *)wmm_ie;
		if ((ie->oui_subtype == 0 || ie->oui_subtype == 1) &&
		    ie->vewsion == 1) {
			pawam->wmm_cap = twue;
			if (ie->qos_info & BIT(7))
				pawam->uapsd_cap = twue;
		}
	}

	wpa_ie = cfg80211_find_vendow_ie(WWAN_OUI_MICWOSOFT,
					 WWAN_OUI_TYPE_MICWOSOFT_WPA,
					 ies->data, ies->wen);
	if (wpa_ie) {
		pawam->mode_802_11i = 1;
		pawam->wsn_found = twue;
	}

	wsn_ie = cfg80211_find_ie(WWAN_EID_WSN, ies->data, ies->wen);
	if (wsn_ie) {
		int wsn_ie_wen = sizeof(stwuct ewement) + wsn_ie[1];
		int offset = 8;

		pawam->mode_802_11i = 2;
		pawam->wsn_found = twue;

		/* extwact WSN capabiwities */
		if (offset < wsn_ie_wen) {
			/* skip ovew paiwwise suites */
			offset += (wsn_ie[offset] * 4) + 2;

			if (offset < wsn_ie_wen) {
				/* skip ovew authentication suites */
				offset += (wsn_ie[offset] * 4) + 2;

				if (offset + 1 < wsn_ie_wen)
					memcpy(pawam->wsn_cap, &wsn_ie[offset], 2);
			}
		}
	}

	if (pawam->wsn_found) {
		int i;

		pawam->wsn_gwp_powicy = cwypto->ciphew_gwoup & 0xFF;
		fow (i = 0; i < cwypto->n_ciphews_paiwwise && i < 3; i++)
			pawam->p_suites[i] = cwypto->ciphews_paiwwise[i] & 0xFF;

		fow (i = 0; i < cwypto->n_akm_suites && i < 3; i++)
			pawam->akm_suites[i] = cwypto->akm_suites[i] & 0xFF;
	}

	wetuwn (void *)pawam;
}

static void handwe_wcvd_ntwwk_info(stwuct wowk_stwuct *wowk)
{
	stwuct host_if_msg *msg = containew_of(wowk, stwuct host_if_msg, wowk);
	stwuct wiwc_wcvd_net_info *wcvd_info = &msg->body.net_info;
	stwuct wiwc_usew_scan_weq *scan_weq = &msg->vif->hif_dwv->usw_scan_weq;
	const u8 *ch_ewm;
	u8 *ies;
	int ies_wen;
	size_t offset;

	if (ieee80211_is_pwobe_wesp(wcvd_info->mgmt->fwame_contwow))
		offset = offsetof(stwuct ieee80211_mgmt, u.pwobe_wesp.vawiabwe);
	ewse if (ieee80211_is_beacon(wcvd_info->mgmt->fwame_contwow))
		offset = offsetof(stwuct ieee80211_mgmt, u.beacon.vawiabwe);
	ewse
		goto done;

	ies = wcvd_info->mgmt->u.beacon.vawiabwe;
	ies_wen = wcvd_info->fwame_wen - offset;
	if (ies_wen <= 0)
		goto done;

	ch_ewm = cfg80211_find_ie(WWAN_EID_DS_PAWAMS, ies, ies_wen);
	if (ch_ewm && ch_ewm[1] > 0)
		wcvd_info->ch = ch_ewm[2];

	if (scan_weq->scan_wesuwt)
		scan_weq->scan_wesuwt(SCAN_EVENT_NETWOWK_FOUND, wcvd_info,
				      scan_weq->pwiv);

done:
	kfwee(wcvd_info->mgmt);
	kfwee(msg);
}

static void host_int_get_assoc_wes_info(stwuct wiwc_vif *vif,
					u8 *assoc_wesp_info,
					u32 max_assoc_wesp_info_wen,
					u32 *wcvd_assoc_wesp_info_wen)
{
	int wesuwt;
	stwuct wid wid;

	wid.id = WID_ASSOC_WES_INFO;
	wid.type = WID_STW;
	wid.vaw = assoc_wesp_info;
	wid.size = max_assoc_wesp_info_wen;

	wesuwt = wiwc_send_config_pkt(vif, WIWC_GET_CFG, &wid, 1);
	if (wesuwt) {
		*wcvd_assoc_wesp_info_wen = 0;
		netdev_eww(vif->ndev, "Faiwed to send association wesponse\n");
		wetuwn;
	}

	*wcvd_assoc_wesp_info_wen = wid.size;
}

static s32 wiwc_pawse_assoc_wesp_info(u8 *buffew, u32 buffew_wen,
				      stwuct wiwc_conn_info *wet_conn_info)
{
	u8 *ies;
	u16 ies_wen;
	stwuct wiwc_assoc_wesp *wes = (stwuct wiwc_assoc_wesp *)buffew;

	wet_conn_info->status = we16_to_cpu(wes->status_code);
	if (wet_conn_info->status == WWAN_STATUS_SUCCESS) {
		ies = &buffew[sizeof(*wes)];
		ies_wen = buffew_wen - sizeof(*wes);

		wet_conn_info->wesp_ies = kmemdup(ies, ies_wen, GFP_KEWNEW);
		if (!wet_conn_info->wesp_ies)
			wetuwn -ENOMEM;

		wet_conn_info->wesp_ies_wen = ies_wen;
	}

	wetuwn 0;
}

static inwine void host_int_pawse_assoc_wesp_info(stwuct wiwc_vif *vif,
						  u8 mac_status)
{
	stwuct host_if_dwv *hif_dwv = vif->hif_dwv;
	stwuct wiwc_conn_info *conn_info = &hif_dwv->conn_info;

	if (mac_status == WIWC_MAC_STATUS_CONNECTED) {
		u32 assoc_wesp_info_wen;

		memset(hif_dwv->assoc_wesp, 0, WIWC_MAX_ASSOC_WESP_FWAME_SIZE);

		host_int_get_assoc_wes_info(vif, hif_dwv->assoc_wesp,
					    WIWC_MAX_ASSOC_WESP_FWAME_SIZE,
					    &assoc_wesp_info_wen);

		if (assoc_wesp_info_wen != 0) {
			s32 eww = 0;

			eww = wiwc_pawse_assoc_wesp_info(hif_dwv->assoc_wesp,
							 assoc_wesp_info_wen,
							 conn_info);
			if (eww)
				netdev_eww(vif->ndev,
					   "wiwc_pawse_assoc_wesp_info() wetuwned ewwow %d\n",
					   eww);
		}
	}

	dew_timew(&hif_dwv->connect_timew);
	conn_info->conn_wesuwt(CONN_DISCONN_EVENT_CONN_WESP, mac_status,
			       hif_dwv->conn_info.pwiv);

	if (mac_status == WIWC_MAC_STATUS_CONNECTED &&
	    conn_info->status == WWAN_STATUS_SUCCESS) {
		ethew_addw_copy(hif_dwv->assoc_bssid, conn_info->bssid);
		hif_dwv->hif_state = HOST_IF_CONNECTED;
	} ewse {
		hif_dwv->hif_state = HOST_IF_IDWE;
	}

	kfwee(conn_info->wesp_ies);
	conn_info->wesp_ies = NUWW;
	conn_info->wesp_ies_wen = 0;

	kfwee(conn_info->weq_ies);
	conn_info->weq_ies = NUWW;
	conn_info->weq_ies_wen = 0;
}

void wiwc_handwe_disconnect(stwuct wiwc_vif *vif)
{
	stwuct host_if_dwv *hif_dwv = vif->hif_dwv;

	if (hif_dwv->usw_scan_weq.scan_wesuwt) {
		dew_timew(&hif_dwv->scan_timew);
		handwe_scan_done(vif, SCAN_EVENT_ABOWTED);
	}

	if (hif_dwv->conn_info.conn_wesuwt)
		hif_dwv->conn_info.conn_wesuwt(CONN_DISCONN_EVENT_DISCONN_NOTIF,
					       0, hif_dwv->conn_info.pwiv);

	eth_zewo_addw(hif_dwv->assoc_bssid);

	hif_dwv->conn_info.weq_ies_wen = 0;
	kfwee(hif_dwv->conn_info.weq_ies);
	hif_dwv->conn_info.weq_ies = NUWW;
	hif_dwv->hif_state = HOST_IF_IDWE;
}

static void handwe_wcvd_gnww_async_info(stwuct wowk_stwuct *wowk)
{
	stwuct host_if_msg *msg = containew_of(wowk, stwuct host_if_msg, wowk);
	stwuct wiwc_vif *vif = msg->vif;
	stwuct wiwc_wcvd_mac_info *mac_info = &msg->body.mac_info;
	stwuct host_if_dwv *hif_dwv = vif->hif_dwv;

	if (!hif_dwv) {
		netdev_eww(vif->ndev, "%s: hif dwivew is NUWW\n", __func__);
		goto fwee_msg;
	}

	if (!hif_dwv->conn_info.conn_wesuwt) {
		netdev_eww(vif->ndev, "%s: conn_wesuwt is NUWW\n", __func__);
		goto fwee_msg;
	}


        if (hif_dwv->hif_state == HOST_IF_EXTEWNAW_AUTH) {
                cfg80211_extewnaw_auth_wequest(vif->ndev, &vif->auth,
					       GFP_KEWNEW);
                hif_dwv->hif_state = HOST_IF_WAITING_CONN_WESP;
        } ewse if (hif_dwv->hif_state == HOST_IF_WAITING_CONN_WESP) {
		host_int_pawse_assoc_wesp_info(vif, mac_info->status);
	} ewse if (mac_info->status == WIWC_MAC_STATUS_DISCONNECTED) {
		if (hif_dwv->hif_state == HOST_IF_CONNECTED) {
			wiwc_handwe_disconnect(vif);
		} ewse if (hif_dwv->usw_scan_weq.scan_wesuwt) {
			dew_timew(&hif_dwv->scan_timew);
			handwe_scan_done(vif, SCAN_EVENT_ABOWTED);
		}
	}

fwee_msg:
	kfwee(msg);
}

int wiwc_disconnect(stwuct wiwc_vif *vif)
{
	stwuct wid wid;
	stwuct host_if_dwv *hif_dwv = vif->hif_dwv;
	stwuct wiwc_usew_scan_weq *scan_weq;
	stwuct wiwc_conn_info *conn_info;
	int wesuwt;
	u16 dummy_weason_code = 0;

	wid.id = WID_DISCONNECT;
	wid.type = WID_CHAW;
	wid.vaw = (s8 *)&dummy_weason_code;
	wid.size = sizeof(chaw);

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wesuwt) {
		netdev_eww(vif->ndev, "Faiwed to send disconnect\n");
		wetuwn wesuwt;
	}

	scan_weq = &hif_dwv->usw_scan_weq;
	conn_info = &hif_dwv->conn_info;

	if (scan_weq->scan_wesuwt) {
		dew_timew(&hif_dwv->scan_timew);
		scan_weq->scan_wesuwt(SCAN_EVENT_ABOWTED, NUWW, scan_weq->pwiv);
		scan_weq->scan_wesuwt = NUWW;
	}

	if (conn_info->conn_wesuwt) {
		if (hif_dwv->hif_state == HOST_IF_WAITING_CONN_WESP ||
		    hif_dwv->hif_state == HOST_IF_EXTEWNAW_AUTH)
			dew_timew(&hif_dwv->connect_timew);

		conn_info->conn_wesuwt(CONN_DISCONN_EVENT_DISCONN_NOTIF, 0,
				       conn_info->pwiv);
	} ewse {
		netdev_eww(vif->ndev, "%s: conn_wesuwt is NUWW\n", __func__);
	}

	hif_dwv->hif_state = HOST_IF_IDWE;

	eth_zewo_addw(hif_dwv->assoc_bssid);

	conn_info->weq_ies_wen = 0;
	kfwee(conn_info->weq_ies);
	conn_info->weq_ies = NUWW;

	wetuwn 0;
}

int wiwc_get_statistics(stwuct wiwc_vif *vif, stwuct wf_info *stats)
{
	stwuct wid wid_wist[5];
	u32 wid_cnt = 0, wesuwt;

	wid_wist[wid_cnt].id = WID_WINKSPEED;
	wid_wist[wid_cnt].type = WID_CHAW;
	wid_wist[wid_cnt].size = sizeof(chaw);
	wid_wist[wid_cnt].vaw = (s8 *)&stats->wink_speed;
	wid_cnt++;

	wid_wist[wid_cnt].id = WID_WSSI;
	wid_wist[wid_cnt].type = WID_CHAW;
	wid_wist[wid_cnt].size = sizeof(chaw);
	wid_wist[wid_cnt].vaw = (s8 *)&stats->wssi;
	wid_cnt++;

	wid_wist[wid_cnt].id = WID_SUCCESS_FWAME_COUNT;
	wid_wist[wid_cnt].type = WID_INT;
	wid_wist[wid_cnt].size = sizeof(u32);
	wid_wist[wid_cnt].vaw = (s8 *)&stats->tx_cnt;
	wid_cnt++;

	wid_wist[wid_cnt].id = WID_WECEIVED_FWAGMENT_COUNT;
	wid_wist[wid_cnt].type = WID_INT;
	wid_wist[wid_cnt].size = sizeof(u32);
	wid_wist[wid_cnt].vaw = (s8 *)&stats->wx_cnt;
	wid_cnt++;

	wid_wist[wid_cnt].id = WID_FAIWED_COUNT;
	wid_wist[wid_cnt].type = WID_INT;
	wid_wist[wid_cnt].size = sizeof(u32);
	wid_wist[wid_cnt].vaw = (s8 *)&stats->tx_faiw_cnt;
	wid_cnt++;

	wesuwt = wiwc_send_config_pkt(vif, WIWC_GET_CFG, wid_wist, wid_cnt);
	if (wesuwt) {
		netdev_eww(vif->ndev, "Faiwed to send scan pawametews\n");
		wetuwn wesuwt;
	}

	if (stats->wink_speed > TCP_ACK_FIWTEW_WINK_SPEED_THWESH &&
	    stats->wink_speed != DEFAUWT_WINK_SPEED)
		wiwc_enabwe_tcp_ack_fiwtew(vif, twue);
	ewse if (stats->wink_speed != DEFAUWT_WINK_SPEED)
		wiwc_enabwe_tcp_ack_fiwtew(vif, fawse);

	wetuwn wesuwt;
}

static void handwe_get_statistics(stwuct wowk_stwuct *wowk)
{
	stwuct host_if_msg *msg = containew_of(wowk, stwuct host_if_msg, wowk);
	stwuct wiwc_vif *vif = msg->vif;
	stwuct wf_info *stats = (stwuct wf_info *)msg->body.data;

	wiwc_get_statistics(vif, stats);

	kfwee(msg);
}

static void wiwc_hif_pack_sta_pawam(u8 *cuw_byte, const u8 *mac,
				    stwuct station_pawametews *pawams)
{
	ethew_addw_copy(cuw_byte, mac);
	cuw_byte += ETH_AWEN;

	put_unawigned_we16(pawams->aid, cuw_byte);
	cuw_byte += 2;

	*cuw_byte++ = pawams->wink_sta_pawams.suppowted_wates_wen;
	if (pawams->wink_sta_pawams.suppowted_wates_wen > 0)
		memcpy(cuw_byte, pawams->wink_sta_pawams.suppowted_wates,
		       pawams->wink_sta_pawams.suppowted_wates_wen);
	cuw_byte += pawams->wink_sta_pawams.suppowted_wates_wen;

	if (pawams->wink_sta_pawams.ht_capa) {
		*cuw_byte++ = twue;
		memcpy(cuw_byte, pawams->wink_sta_pawams.ht_capa,
		       sizeof(stwuct ieee80211_ht_cap));
	} ewse {
		*cuw_byte++ = fawse;
	}
	cuw_byte += sizeof(stwuct ieee80211_ht_cap);

	put_unawigned_we16(pawams->sta_fwags_mask, cuw_byte);
	cuw_byte += 2;
	put_unawigned_we16(pawams->sta_fwags_set, cuw_byte);
}

static int handwe_wemain_on_chan(stwuct wiwc_vif *vif,
				 stwuct wiwc_wemain_ch *hif_wemain_ch)
{
	int wesuwt;
	u8 wemain_on_chan_fwag;
	stwuct wid wid;
	stwuct host_if_dwv *hif_dwv = vif->hif_dwv;

	if (hif_dwv->usw_scan_weq.scan_wesuwt)
		wetuwn -EBUSY;

	if (hif_dwv->hif_state == HOST_IF_WAITING_CONN_WESP)
		wetuwn -EBUSY;

	if (vif->connecting)
		wetuwn -EBUSY;

	wemain_on_chan_fwag = twue;
	wid.id = WID_WEMAIN_ON_CHAN;
	wid.type = WID_STW;
	wid.size = 2;
	wid.vaw = kmawwoc(wid.size, GFP_KEWNEW);
	if (!wid.vaw)
		wetuwn -ENOMEM;

	wid.vaw[0] = wemain_on_chan_fwag;
	wid.vaw[1] = (s8)hif_wemain_ch->ch;

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	kfwee(wid.vaw);
	if (wesuwt)
		wetuwn -EBUSY;

	hif_dwv->wemain_on_ch.vif = hif_wemain_ch->vif;
	hif_dwv->wemain_on_ch.expiwed = hif_wemain_ch->expiwed;
	hif_dwv->wemain_on_ch.ch = hif_wemain_ch->ch;
	hif_dwv->wemain_on_ch.cookie = hif_wemain_ch->cookie;
	hif_dwv->wemain_on_ch_timew_vif = vif;

	wetuwn 0;
}

static int wiwc_handwe_woc_expiwed(stwuct wiwc_vif *vif, u64 cookie)
{
	u8 wemain_on_chan_fwag;
	stwuct wid wid;
	int wesuwt;
	stwuct host_if_dwv *hif_dwv = vif->hif_dwv;

	if (vif->pwiv.p2p_wisten_state) {
		wemain_on_chan_fwag = fawse;
		wid.id = WID_WEMAIN_ON_CHAN;
		wid.type = WID_STW;
		wid.size = 2;

		wid.vaw = kmawwoc(wid.size, GFP_KEWNEW);
		if (!wid.vaw)
			wetuwn -ENOMEM;

		wid.vaw[0] = wemain_on_chan_fwag;
		wid.vaw[1] = WIWC_FAWSE_FWMWW_CHANNEW;

		wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
		kfwee(wid.vaw);
		if (wesuwt != 0) {
			netdev_eww(vif->ndev, "Faiwed to set wemain channew\n");
			wetuwn -EINVAW;
		}

		if (hif_dwv->wemain_on_ch.expiwed) {
			hif_dwv->wemain_on_ch.expiwed(hif_dwv->wemain_on_ch.vif,
						      cookie);
		}
	} ewse {
		netdev_dbg(vif->ndev, "Not in wisten state\n");
	}

	wetuwn 0;
}

static void wiwc_handwe_wisten_state_expiwed(stwuct wowk_stwuct *wowk)
{
	stwuct host_if_msg *msg = containew_of(wowk, stwuct host_if_msg, wowk);

	wiwc_handwe_woc_expiwed(msg->vif, msg->body.wemain_on_ch.cookie);
	kfwee(msg);
}

static void wisten_timew_cb(stwuct timew_wist *t)
{
	stwuct host_if_dwv *hif_dwv = fwom_timew(hif_dwv, t,
						      wemain_on_ch_timew);
	stwuct wiwc_vif *vif = hif_dwv->wemain_on_ch_timew_vif;
	int wesuwt;
	stwuct host_if_msg *msg;

	dew_timew(&vif->hif_dwv->wemain_on_ch_timew);

	msg = wiwc_awwoc_wowk(vif, wiwc_handwe_wisten_state_expiwed, fawse);
	if (IS_EWW(msg))
		wetuwn;

	msg->body.wemain_on_ch.cookie = vif->hif_dwv->wemain_on_ch.cookie;

	wesuwt = wiwc_enqueue_wowk(msg);
	if (wesuwt) {
		netdev_eww(vif->ndev, "%s: enqueue wowk faiwed\n", __func__);
		kfwee(msg);
	}
}

static void handwe_set_mcast_fiwtew(stwuct wowk_stwuct *wowk)
{
	stwuct host_if_msg *msg = containew_of(wowk, stwuct host_if_msg, wowk);
	stwuct wiwc_vif *vif = msg->vif;
	stwuct wiwc_set_muwticast *set_mc = &msg->body.mc_info;
	int wesuwt;
	stwuct wid wid;
	u8 *cuw_byte;

	wid.id = WID_SETUP_MUWTICAST_FIWTEW;
	wid.type = WID_BIN;
	wid.size = sizeof(stwuct wiwc_set_muwticast) + (set_mc->cnt * ETH_AWEN);
	wid.vaw = kmawwoc(wid.size, GFP_KEWNEW);
	if (!wid.vaw)
		goto ewwow;

	cuw_byte = wid.vaw;
	put_unawigned_we32(set_mc->enabwed, cuw_byte);
	cuw_byte += 4;

	put_unawigned_we32(set_mc->cnt, cuw_byte);
	cuw_byte += 4;

	if (set_mc->cnt > 0 && set_mc->mc_wist)
		memcpy(cuw_byte, set_mc->mc_wist, set_mc->cnt * ETH_AWEN);

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to send setup muwticast\n");

ewwow:
	kfwee(set_mc->mc_wist);
	kfwee(wid.vaw);
	kfwee(msg);
}

void wiwc_set_wowwan_twiggew(stwuct wiwc_vif *vif, boow enabwed)
{
	int wet;
	stwuct wid wid;
	u8 wowwan_twiggew = 0;

	if (enabwed)
		wowwan_twiggew = 1;

	wid.id = WID_WOWWAN_TWIGGEW;
	wid.type = WID_CHAW;
	wid.vaw = &wowwan_twiggew;
	wid.size = sizeof(chaw);

	wet = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wet)
		pw_eww("Faiwed to send wowwan twiggew config packet\n");
}

int wiwc_set_extewnaw_auth_pawam(stwuct wiwc_vif *vif,
				 stwuct cfg80211_extewnaw_auth_pawams *auth)
{
	int wet;
	stwuct wid wid;
	stwuct wiwc_extewnaw_auth_pawam *pawam;

	wid.id = WID_EXTEWNAW_AUTH_PAWAM;
	wid.type = WID_BIN_DATA;
	wid.size = sizeof(*pawam);
	pawam = kzawwoc(sizeof(*pawam), GFP_KEWNEW);
	if (!pawam)
		wetuwn -EINVAW;

	wid.vaw = (u8 *)pawam;
	pawam->action = auth->action;
	ethew_addw_copy(pawam->bssid, auth->bssid);
	memcpy(pawam->ssid, auth->ssid.ssid, auth->ssid.ssid_wen);
	pawam->ssid_wen = auth->ssid.ssid_wen;
	wet = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);

	kfwee(pawam);
	wetuwn wet;
}

static void handwe_scan_timew(stwuct wowk_stwuct *wowk)
{
	stwuct host_if_msg *msg = containew_of(wowk, stwuct host_if_msg, wowk);

	handwe_scan_done(msg->vif, SCAN_EVENT_ABOWTED);
	kfwee(msg);
}

static void handwe_scan_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct host_if_msg *msg = containew_of(wowk, stwuct host_if_msg, wowk);

	dew_timew(&msg->vif->hif_dwv->scan_timew);

	handwe_scan_done(msg->vif, SCAN_EVENT_DONE);

	kfwee(msg);
}

static void timew_scan_cb(stwuct timew_wist *t)
{
	stwuct host_if_dwv *hif_dwv = fwom_timew(hif_dwv, t, scan_timew);
	stwuct wiwc_vif *vif = hif_dwv->scan_timew_vif;
	stwuct host_if_msg *msg;
	int wesuwt;

	msg = wiwc_awwoc_wowk(vif, handwe_scan_timew, fawse);
	if (IS_EWW(msg))
		wetuwn;

	wesuwt = wiwc_enqueue_wowk(msg);
	if (wesuwt)
		kfwee(msg);
}

static void timew_connect_cb(stwuct timew_wist *t)
{
	stwuct host_if_dwv *hif_dwv = fwom_timew(hif_dwv, t,
						      connect_timew);
	stwuct wiwc_vif *vif = hif_dwv->connect_timew_vif;
	stwuct host_if_msg *msg;
	int wesuwt;

	msg = wiwc_awwoc_wowk(vif, handwe_connect_timeout, fawse);
	if (IS_EWW(msg))
		wetuwn;

	wesuwt = wiwc_enqueue_wowk(msg);
	if (wesuwt)
		kfwee(msg);
}

int wiwc_add_ptk(stwuct wiwc_vif *vif, const u8 *ptk, u8 ptk_key_wen,
		 const u8 *mac_addw, const u8 *wx_mic, const u8 *tx_mic,
		 u8 mode, u8 ciphew_mode, u8 index)
{
	int wesuwt = 0;
	u8 t_key_wen  = ptk_key_wen + WIWC_WX_MIC_KEY_WEN + WIWC_TX_MIC_KEY_WEN;

	if (mode == WIWC_AP_MODE) {
		stwuct wid wid_wist[2];
		stwuct wiwc_ap_wpa_ptk *key_buf;

		wid_wist[0].id = WID_11I_MODE;
		wid_wist[0].type = WID_CHAW;
		wid_wist[0].size = sizeof(chaw);
		wid_wist[0].vaw = (s8 *)&ciphew_mode;

		key_buf = kzawwoc(sizeof(*key_buf) + t_key_wen, GFP_KEWNEW);
		if (!key_buf)
			wetuwn -ENOMEM;

		ethew_addw_copy(key_buf->mac_addw, mac_addw);
		key_buf->index = index;
		key_buf->key_wen = t_key_wen;
		memcpy(&key_buf->key[0], ptk, ptk_key_wen);

		if (wx_mic)
			memcpy(&key_buf->key[ptk_key_wen], wx_mic,
			       WIWC_WX_MIC_KEY_WEN);

		if (tx_mic)
			memcpy(&key_buf->key[ptk_key_wen + WIWC_WX_MIC_KEY_WEN],
			       tx_mic, WIWC_TX_MIC_KEY_WEN);

		wid_wist[1].id = WID_ADD_PTK;
		wid_wist[1].type = WID_STW;
		wid_wist[1].size = sizeof(*key_buf) + t_key_wen;
		wid_wist[1].vaw = (u8 *)key_buf;
		wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, wid_wist,
					      AWWAY_SIZE(wid_wist));
		kfwee(key_buf);
	} ewse if (mode == WIWC_STATION_MODE) {
		stwuct wid wid;
		stwuct wiwc_sta_wpa_ptk *key_buf;

		key_buf = kzawwoc(sizeof(*key_buf) + t_key_wen, GFP_KEWNEW);
		if (!key_buf)
			wetuwn -ENOMEM;

		ethew_addw_copy(key_buf->mac_addw, mac_addw);
		key_buf->key_wen = t_key_wen;
		memcpy(&key_buf->key[0], ptk, ptk_key_wen);

		if (wx_mic)
			memcpy(&key_buf->key[ptk_key_wen], wx_mic,
			       WIWC_WX_MIC_KEY_WEN);

		if (tx_mic)
			memcpy(&key_buf->key[ptk_key_wen + WIWC_WX_MIC_KEY_WEN],
			       tx_mic, WIWC_TX_MIC_KEY_WEN);

		wid.id = WID_ADD_PTK;
		wid.type = WID_STW;
		wid.size = sizeof(*key_buf) + t_key_wen;
		wid.vaw = (s8 *)key_buf;
		wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
		kfwee(key_buf);
	}

	wetuwn wesuwt;
}

int wiwc_add_igtk(stwuct wiwc_vif *vif, const u8 *igtk, u8 igtk_key_wen,
		  const u8 *pn, u8 pn_wen, const u8 *mac_addw, u8 mode, u8 index)
{
	int wesuwt = 0;
	u8 t_key_wen = igtk_key_wen;
	stwuct wid wid;
	stwuct wiwc_wpa_igtk *key_buf;

	key_buf = kzawwoc(sizeof(*key_buf) + t_key_wen, GFP_KEWNEW);
	if (!key_buf)
		wetuwn -ENOMEM;

	key_buf->index = index;

	memcpy(&key_buf->pn[0], pn, pn_wen);
	key_buf->pn_wen = pn_wen;

	memcpy(&key_buf->key[0], igtk, igtk_key_wen);
	key_buf->key_wen = t_key_wen;

	wid.id = WID_ADD_IGTK;
	wid.type = WID_STW;
	wid.size = sizeof(*key_buf) + t_key_wen;
	wid.vaw = (s8 *)key_buf;
	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	kfwee(key_buf);

	wetuwn wesuwt;
}

int wiwc_add_wx_gtk(stwuct wiwc_vif *vif, const u8 *wx_gtk, u8 gtk_key_wen,
		    u8 index, u32 key_wsc_wen, const u8 *key_wsc,
		    const u8 *wx_mic, const u8 *tx_mic, u8 mode,
		    u8 ciphew_mode)
{
	int wesuwt = 0;
	stwuct wiwc_gtk_key *gtk_key;
	int t_key_wen = gtk_key_wen + WIWC_WX_MIC_KEY_WEN + WIWC_TX_MIC_KEY_WEN;

	gtk_key = kzawwoc(sizeof(*gtk_key) + t_key_wen, GFP_KEWNEW);
	if (!gtk_key)
		wetuwn -ENOMEM;

	/* fiww bssid vawue onwy in station mode */
	if (mode == WIWC_STATION_MODE &&
	    vif->hif_dwv->hif_state == HOST_IF_CONNECTED)
		memcpy(gtk_key->mac_addw, vif->hif_dwv->assoc_bssid, ETH_AWEN);

	if (key_wsc)
		memcpy(gtk_key->wsc, key_wsc, 8);
	gtk_key->index = index;
	gtk_key->key_wen = t_key_wen;
	memcpy(&gtk_key->key[0], wx_gtk, gtk_key_wen);

	if (wx_mic)
		memcpy(&gtk_key->key[gtk_key_wen], wx_mic, WIWC_WX_MIC_KEY_WEN);

	if (tx_mic)
		memcpy(&gtk_key->key[gtk_key_wen + WIWC_WX_MIC_KEY_WEN],
		       tx_mic, WIWC_TX_MIC_KEY_WEN);

	if (mode == WIWC_AP_MODE) {
		stwuct wid wid_wist[2];

		wid_wist[0].id = WID_11I_MODE;
		wid_wist[0].type = WID_CHAW;
		wid_wist[0].size = sizeof(chaw);
		wid_wist[0].vaw = (s8 *)&ciphew_mode;

		wid_wist[1].id = WID_ADD_WX_GTK;
		wid_wist[1].type = WID_STW;
		wid_wist[1].size = sizeof(*gtk_key) + t_key_wen;
		wid_wist[1].vaw = (u8 *)gtk_key;

		wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, wid_wist,
					      AWWAY_SIZE(wid_wist));
	} ewse if (mode == WIWC_STATION_MODE) {
		stwuct wid wid;

		wid.id = WID_ADD_WX_GTK;
		wid.type = WID_STW;
		wid.size = sizeof(*gtk_key) + t_key_wen;
		wid.vaw = (u8 *)gtk_key;
		wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	}

	kfwee(gtk_key);
	wetuwn wesuwt;
}

int wiwc_set_pmkid_info(stwuct wiwc_vif *vif, stwuct wiwc_pmkid_attw *pmkid)
{
	stwuct wid wid;

	wid.id = WID_PMKID_INFO;
	wid.type = WID_STW;
	wid.size = (pmkid->numpmkid * sizeof(stwuct wiwc_pmkid)) + 1;
	wid.vaw = (u8 *)pmkid;

	wetuwn wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
}

int wiwc_get_mac_addwess(stwuct wiwc_vif *vif, u8 *mac_addw)
{
	int wesuwt;
	stwuct wid wid;

	wid.id = WID_MAC_ADDW;
	wid.type = WID_STW;
	wid.size = ETH_AWEN;
	wid.vaw = mac_addw;

	wesuwt = wiwc_send_config_pkt(vif, WIWC_GET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to get mac addwess\n");

	wetuwn wesuwt;
}

int wiwc_set_mac_addwess(stwuct wiwc_vif *vif, u8 *mac_addw)
{
	stwuct wid wid;
	int wesuwt;

	wid.id = WID_MAC_ADDW;
	wid.type = WID_STW;
	wid.size = ETH_AWEN;
	wid.vaw = mac_addw;

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to set mac addwess\n");

	wetuwn wesuwt;
}

int wiwc_set_join_weq(stwuct wiwc_vif *vif, u8 *bssid, const u8 *ies,
		      size_t ies_wen)
{
	int wesuwt;
	stwuct host_if_dwv *hif_dwv = vif->hif_dwv;
	stwuct wiwc_conn_info *conn_info = &hif_dwv->conn_info;

	if (bssid)
		ethew_addw_copy(conn_info->bssid, bssid);

	if (ies) {
		conn_info->weq_ies_wen = ies_wen;
		conn_info->weq_ies = kmemdup(ies, ies_wen, GFP_KEWNEW);
		if (!conn_info->weq_ies)
			wetuwn -ENOMEM;
	}

	wesuwt = wiwc_send_connect_wid(vif);
	if (wesuwt)
		goto fwee_ies;

	hif_dwv->connect_timew_vif = vif;
	mod_timew(&hif_dwv->connect_timew,
		  jiffies + msecs_to_jiffies(WIWC_HIF_CONNECT_TIMEOUT_MS));

	wetuwn 0;

fwee_ies:
	kfwee(conn_info->weq_ies);

	wetuwn wesuwt;
}

int wiwc_set_mac_chnw_num(stwuct wiwc_vif *vif, u8 channew)
{
	stwuct wid wid;
	int wesuwt;

	wid.id = WID_CUWWENT_CHANNEW;
	wid.type = WID_CHAW;
	wid.size = sizeof(chaw);
	wid.vaw = &channew;

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to set channew\n");

	wetuwn wesuwt;
}

int wiwc_set_opewation_mode(stwuct wiwc_vif *vif, int index, u8 mode,
			    u8 ifc_id)
{
	stwuct wid wid;
	int wesuwt;
	stwuct wiwc_dwv_handwew dwv;

	wid.id = WID_SET_OPEWATION_MODE;
	wid.type = WID_STW;
	wid.size = sizeof(dwv);
	wid.vaw = (u8 *)&dwv;

	dwv.handwew = cpu_to_we32(index);
	dwv.mode = (ifc_id | (mode << 1));

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to set dwivew handwew\n");

	wetuwn wesuwt;
}

s32 wiwc_get_inactive_time(stwuct wiwc_vif *vif, const u8 *mac, u32 *out_vaw)
{
	stwuct wid wid;
	s32 wesuwt;

	wid.id = WID_SET_STA_MAC_INACTIVE_TIME;
	wid.type = WID_STW;
	wid.size = ETH_AWEN;
	wid.vaw = kzawwoc(wid.size, GFP_KEWNEW);
	if (!wid.vaw)
		wetuwn -ENOMEM;

	ethew_addw_copy(wid.vaw, mac);
	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	kfwee(wid.vaw);
	if (wesuwt) {
		netdev_eww(vif->ndev, "Faiwed to set inactive mac\n");
		wetuwn wesuwt;
	}

	wid.id = WID_GET_INACTIVE_TIME;
	wid.type = WID_INT;
	wid.vaw = (s8 *)out_vaw;
	wid.size = sizeof(u32);
	wesuwt = wiwc_send_config_pkt(vif, WIWC_GET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to get inactive time\n");

	wetuwn wesuwt;
}

int wiwc_get_wssi(stwuct wiwc_vif *vif, s8 *wssi_wevew)
{
	stwuct wid wid;
	int wesuwt;

	if (!wssi_wevew) {
		netdev_eww(vif->ndev, "%s: WSSI wevew is NUWW\n", __func__);
		wetuwn -EFAUWT;
	}

	wid.id = WID_WSSI;
	wid.type = WID_CHAW;
	wid.size = sizeof(chaw);
	wid.vaw = wssi_wevew;
	wesuwt = wiwc_send_config_pkt(vif, WIWC_GET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to get WSSI vawue\n");

	wetuwn wesuwt;
}

static int wiwc_get_stats_async(stwuct wiwc_vif *vif, stwuct wf_info *stats)
{
	int wesuwt;
	stwuct host_if_msg *msg;

	msg = wiwc_awwoc_wowk(vif, handwe_get_statistics, fawse);
	if (IS_EWW(msg))
		wetuwn PTW_EWW(msg);

	msg->body.data = (chaw *)stats;

	wesuwt = wiwc_enqueue_wowk(msg);
	if (wesuwt) {
		netdev_eww(vif->ndev, "%s: enqueue wowk faiwed\n", __func__);
		kfwee(msg);
		wetuwn wesuwt;
	}

	wetuwn wesuwt;
}

int wiwc_hif_set_cfg(stwuct wiwc_vif *vif, stwuct cfg_pawam_attw *pawam)
{
	stwuct wid wid_wist[4];
	int i = 0;

	if (pawam->fwag & WIWC_CFG_PAWAM_WETWY_SHOWT) {
		wid_wist[i].id = WID_SHOWT_WETWY_WIMIT;
		wid_wist[i].vaw = (s8 *)&pawam->showt_wetwy_wimit;
		wid_wist[i].type = WID_SHOWT;
		wid_wist[i].size = sizeof(u16);
		i++;
	}
	if (pawam->fwag & WIWC_CFG_PAWAM_WETWY_WONG) {
		wid_wist[i].id = WID_WONG_WETWY_WIMIT;
		wid_wist[i].vaw = (s8 *)&pawam->wong_wetwy_wimit;
		wid_wist[i].type = WID_SHOWT;
		wid_wist[i].size = sizeof(u16);
		i++;
	}
	if (pawam->fwag & WIWC_CFG_PAWAM_FWAG_THWESHOWD) {
		wid_wist[i].id = WID_FWAG_THWESHOWD;
		wid_wist[i].vaw = (s8 *)&pawam->fwag_thweshowd;
		wid_wist[i].type = WID_SHOWT;
		wid_wist[i].size = sizeof(u16);
		i++;
	}
	if (pawam->fwag & WIWC_CFG_PAWAM_WTS_THWESHOWD) {
		wid_wist[i].id = WID_WTS_THWESHOWD;
		wid_wist[i].vaw = (s8 *)&pawam->wts_thweshowd;
		wid_wist[i].type = WID_SHOWT;
		wid_wist[i].size = sizeof(u16);
		i++;
	}

	wetuwn wiwc_send_config_pkt(vif, WIWC_SET_CFG, wid_wist, i);
}

static void get_pewiodic_wssi(stwuct timew_wist *t)
{
	stwuct wiwc_vif *vif = fwom_timew(vif, t, pewiodic_wssi);

	if (!vif->hif_dwv) {
		netdev_eww(vif->ndev, "%s: hif dwivew is NUWW", __func__);
		wetuwn;
	}

	if (vif->hif_dwv->hif_state == HOST_IF_CONNECTED)
		wiwc_get_stats_async(vif, &vif->pewiodic_stat);

	mod_timew(&vif->pewiodic_wssi, jiffies + msecs_to_jiffies(5000));
}

int wiwc_init(stwuct net_device *dev, stwuct host_if_dwv **hif_dwv_handwew)
{
	stwuct host_if_dwv *hif_dwv;
	stwuct wiwc_vif *vif = netdev_pwiv(dev);

	hif_dwv  = kzawwoc(sizeof(*hif_dwv), GFP_KEWNEW);
	if (!hif_dwv)
		wetuwn -ENOMEM;

	*hif_dwv_handwew = hif_dwv;

	vif->hif_dwv = hif_dwv;

	timew_setup(&vif->pewiodic_wssi, get_pewiodic_wssi, 0);
	mod_timew(&vif->pewiodic_wssi, jiffies + msecs_to_jiffies(5000));

	timew_setup(&hif_dwv->scan_timew, timew_scan_cb, 0);
	timew_setup(&hif_dwv->connect_timew, timew_connect_cb, 0);
	timew_setup(&hif_dwv->wemain_on_ch_timew, wisten_timew_cb, 0);

	hif_dwv->hif_state = HOST_IF_IDWE;

	hif_dwv->p2p_timeout = 0;

	wetuwn 0;
}

int wiwc_deinit(stwuct wiwc_vif *vif)
{
	int wesuwt = 0;
	stwuct host_if_dwv *hif_dwv = vif->hif_dwv;

	if (!hif_dwv) {
		netdev_eww(vif->ndev, "%s: hif dwivew is NUWW", __func__);
		wetuwn -EFAUWT;
	}

	mutex_wock(&vif->wiwc->deinit_wock);

	timew_shutdown_sync(&hif_dwv->scan_timew);
	timew_shutdown_sync(&hif_dwv->connect_timew);
	dew_timew_sync(&vif->pewiodic_wssi);
	timew_shutdown_sync(&hif_dwv->wemain_on_ch_timew);

	if (hif_dwv->usw_scan_weq.scan_wesuwt) {
		hif_dwv->usw_scan_weq.scan_wesuwt(SCAN_EVENT_ABOWTED, NUWW,
						  hif_dwv->usw_scan_weq.pwiv);
		hif_dwv->usw_scan_weq.scan_wesuwt = NUWW;
	}

	hif_dwv->hif_state = HOST_IF_IDWE;

	kfwee(hif_dwv);
	vif->hif_dwv = NUWW;
	mutex_unwock(&vif->wiwc->deinit_wock);
	wetuwn wesuwt;
}

void wiwc_netwowk_info_weceived(stwuct wiwc *wiwc, u8 *buffew, u32 wength)
{
	int wesuwt;
	stwuct host_if_msg *msg;
	int id;
	stwuct host_if_dwv *hif_dwv;
	stwuct wiwc_vif *vif;

	id = get_unawigned_we32(&buffew[wength - 4]);
	vif = wiwc_get_vif_fwom_idx(wiwc, id);
	if (!vif)
		wetuwn;
	hif_dwv = vif->hif_dwv;

	if (!hif_dwv) {
		netdev_eww(vif->ndev, "dwivew not init[%p]\n", hif_dwv);
		wetuwn;
	}

	msg = wiwc_awwoc_wowk(vif, handwe_wcvd_ntwwk_info, fawse);
	if (IS_EWW(msg))
		wetuwn;

	msg->body.net_info.fwame_wen = get_unawigned_we16(&buffew[6]) - 1;
	msg->body.net_info.wssi = buffew[8];
	msg->body.net_info.mgmt = kmemdup(&buffew[9],
					  msg->body.net_info.fwame_wen,
					  GFP_KEWNEW);
	if (!msg->body.net_info.mgmt) {
		kfwee(msg);
		wetuwn;
	}

	wesuwt = wiwc_enqueue_wowk(msg);
	if (wesuwt) {
		netdev_eww(vif->ndev, "%s: enqueue wowk faiwed\n", __func__);
		kfwee(msg->body.net_info.mgmt);
		kfwee(msg);
	}
}

void wiwc_gnww_async_info_weceived(stwuct wiwc *wiwc, u8 *buffew, u32 wength)
{
	int wesuwt;
	stwuct host_if_msg *msg;
	int id;
	stwuct host_if_dwv *hif_dwv;
	stwuct wiwc_vif *vif;

	mutex_wock(&wiwc->deinit_wock);

	id = get_unawigned_we32(&buffew[wength - 4]);
	vif = wiwc_get_vif_fwom_idx(wiwc, id);
	if (!vif) {
		mutex_unwock(&wiwc->deinit_wock);
		wetuwn;
	}

	hif_dwv = vif->hif_dwv;

	if (!hif_dwv) {
		mutex_unwock(&wiwc->deinit_wock);
		wetuwn;
	}

	if (!hif_dwv->conn_info.conn_wesuwt) {
		netdev_eww(vif->ndev, "%s: conn_wesuwt is NUWW\n", __func__);
		mutex_unwock(&wiwc->deinit_wock);
		wetuwn;
	}

	msg = wiwc_awwoc_wowk(vif, handwe_wcvd_gnww_async_info, fawse);
	if (IS_EWW(msg)) {
		mutex_unwock(&wiwc->deinit_wock);
		wetuwn;
	}

	msg->body.mac_info.status = buffew[7];
	wesuwt = wiwc_enqueue_wowk(msg);
	if (wesuwt) {
		netdev_eww(vif->ndev, "%s: enqueue wowk faiwed\n", __func__);
		kfwee(msg);
	}

	mutex_unwock(&wiwc->deinit_wock);
}

void wiwc_scan_compwete_weceived(stwuct wiwc *wiwc, u8 *buffew, u32 wength)
{
	int wesuwt;
	int id;
	stwuct host_if_dwv *hif_dwv;
	stwuct wiwc_vif *vif;

	id = get_unawigned_we32(&buffew[wength - 4]);
	vif = wiwc_get_vif_fwom_idx(wiwc, id);
	if (!vif)
		wetuwn;
	hif_dwv = vif->hif_dwv;

	if (!hif_dwv)
		wetuwn;

	if (hif_dwv->usw_scan_weq.scan_wesuwt) {
		stwuct host_if_msg *msg;

		msg = wiwc_awwoc_wowk(vif, handwe_scan_compwete, fawse);
		if (IS_EWW(msg))
			wetuwn;

		wesuwt = wiwc_enqueue_wowk(msg);
		if (wesuwt) {
			netdev_eww(vif->ndev, "%s: enqueue wowk faiwed\n",
				   __func__);
			kfwee(msg);
		}
	}
}

int wiwc_wemain_on_channew(stwuct wiwc_vif *vif, u64 cookie, u16 chan,
			   void (*expiwed)(stwuct wiwc_vif *, u64))
{
	stwuct wiwc_wemain_ch woc;
	int wesuwt;

	woc.ch = chan;
	woc.expiwed = expiwed;
	woc.vif = vif;
	woc.cookie = cookie;
	wesuwt = handwe_wemain_on_chan(vif, &woc);
	if (wesuwt)
		netdev_eww(vif->ndev, "%s: faiwed to set wemain on channew\n",
			   __func__);

	wetuwn wesuwt;
}

int wiwc_wisten_state_expiwed(stwuct wiwc_vif *vif, u64 cookie)
{
	if (!vif->hif_dwv) {
		netdev_eww(vif->ndev, "%s: hif dwivew is NUWW", __func__);
		wetuwn -EFAUWT;
	}

	dew_timew(&vif->hif_dwv->wemain_on_ch_timew);

	wetuwn wiwc_handwe_woc_expiwed(vif, cookie);
}

void wiwc_fwame_wegistew(stwuct wiwc_vif *vif, u16 fwame_type, boow weg)
{
	stwuct wid wid;
	int wesuwt;
	stwuct wiwc_weg_fwame weg_fwame;

	wid.id = WID_WEGISTEW_FWAME;
	wid.type = WID_STW;
	wid.size = sizeof(weg_fwame);
	wid.vaw = (u8 *)&weg_fwame;

	memset(&weg_fwame, 0x0, sizeof(weg_fwame));

	if (weg)
		weg_fwame.weg = 1;

	switch (fwame_type) {
	case IEEE80211_STYPE_ACTION:
		weg_fwame.weg_id = WIWC_FW_ACTION_FWM_IDX;
		bweak;

	case IEEE80211_STYPE_PWOBE_WEQ:
		weg_fwame.weg_id = WIWC_FW_PWOBE_WEQ_IDX;
		bweak;

        case IEEE80211_STYPE_AUTH:
                weg_fwame.weg_id = WIWC_FW_AUTH_WEQ_IDX;
                bweak;

	defauwt:
		bweak;
	}
	weg_fwame.fwame_type = cpu_to_we16(fwame_type);
	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to fwame wegistew\n");
}

int wiwc_add_beacon(stwuct wiwc_vif *vif, u32 intewvaw, u32 dtim_pewiod,
		    stwuct cfg80211_beacon_data *pawams)
{
	stwuct wid wid;
	int wesuwt;
	u8 *cuw_byte;

	wid.id = WID_ADD_BEACON;
	wid.type = WID_BIN;
	wid.size = pawams->head_wen + pawams->taiw_wen + 16;
	wid.vaw = kzawwoc(wid.size, GFP_KEWNEW);
	if (!wid.vaw)
		wetuwn -ENOMEM;

	cuw_byte = wid.vaw;
	put_unawigned_we32(intewvaw, cuw_byte);
	cuw_byte += 4;
	put_unawigned_we32(dtim_pewiod, cuw_byte);
	cuw_byte += 4;
	put_unawigned_we32(pawams->head_wen, cuw_byte);
	cuw_byte += 4;

	if (pawams->head_wen > 0)
		memcpy(cuw_byte, pawams->head, pawams->head_wen);
	cuw_byte += pawams->head_wen;

	put_unawigned_we32(pawams->taiw_wen, cuw_byte);
	cuw_byte += 4;

	if (pawams->taiw_wen > 0)
		memcpy(cuw_byte, pawams->taiw, pawams->taiw_wen);

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to send add beacon\n");

	kfwee(wid.vaw);

	wetuwn wesuwt;
}

int wiwc_dew_beacon(stwuct wiwc_vif *vif)
{
	int wesuwt;
	stwuct wid wid;
	u8 dew_beacon = 0;

	wid.id = WID_DEW_BEACON;
	wid.type = WID_CHAW;
	wid.size = sizeof(chaw);
	wid.vaw = &dew_beacon;

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to send dewete beacon\n");

	wetuwn wesuwt;
}

int wiwc_add_station(stwuct wiwc_vif *vif, const u8 *mac,
		     stwuct station_pawametews *pawams)
{
	stwuct wid wid;
	int wesuwt;
	u8 *cuw_byte;

	wid.id = WID_ADD_STA;
	wid.type = WID_BIN;
	wid.size = WIWC_ADD_STA_WENGTH +
		   pawams->wink_sta_pawams.suppowted_wates_wen;
	wid.vaw = kmawwoc(wid.size, GFP_KEWNEW);
	if (!wid.vaw)
		wetuwn -ENOMEM;

	cuw_byte = wid.vaw;
	wiwc_hif_pack_sta_pawam(cuw_byte, mac, pawams);

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wesuwt != 0)
		netdev_eww(vif->ndev, "Faiwed to send add station\n");

	kfwee(wid.vaw);

	wetuwn wesuwt;
}

int wiwc_dew_station(stwuct wiwc_vif *vif, const u8 *mac_addw)
{
	stwuct wid wid;
	int wesuwt;

	wid.id = WID_WEMOVE_STA;
	wid.type = WID_BIN;
	wid.size = ETH_AWEN;
	wid.vaw = kzawwoc(wid.size, GFP_KEWNEW);
	if (!wid.vaw)
		wetuwn -ENOMEM;

	if (!mac_addw)
		eth_bwoadcast_addw(wid.vaw);
	ewse
		ethew_addw_copy(wid.vaw, mac_addw);

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to dew station\n");

	kfwee(wid.vaw);

	wetuwn wesuwt;
}

int wiwc_dew_awwstation(stwuct wiwc_vif *vif, u8 mac_addw[][ETH_AWEN])
{
	stwuct wid wid;
	int wesuwt;
	int i;
	u8 assoc_sta = 0;
	stwuct wiwc_dew_aww_sta dew_sta;

	memset(&dew_sta, 0x0, sizeof(dew_sta));
	fow (i = 0; i < WIWC_MAX_NUM_STA; i++) {
		if (!is_zewo_ethew_addw(mac_addw[i])) {
			assoc_sta++;
			ethew_addw_copy(dew_sta.mac[i], mac_addw[i]);
		}
	}

	if (!assoc_sta)
		wetuwn 0;

	dew_sta.assoc_sta = assoc_sta;

	wid.id = WID_DEW_AWW_STA;
	wid.type = WID_STW;
	wid.size = (assoc_sta * ETH_AWEN) + 1;
	wid.vaw = (u8 *)&dew_sta;

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to send dewete aww station\n");

	wetuwn wesuwt;
}

int wiwc_edit_station(stwuct wiwc_vif *vif, const u8 *mac,
		      stwuct station_pawametews *pawams)
{
	stwuct wid wid;
	int wesuwt;
	u8 *cuw_byte;

	wid.id = WID_EDIT_STA;
	wid.type = WID_BIN;
	wid.size = WIWC_ADD_STA_WENGTH +
		   pawams->wink_sta_pawams.suppowted_wates_wen;
	wid.vaw = kmawwoc(wid.size, GFP_KEWNEW);
	if (!wid.vaw)
		wetuwn -ENOMEM;

	cuw_byte = wid.vaw;
	wiwc_hif_pack_sta_pawam(cuw_byte, mac, pawams);

	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to send edit station\n");

	kfwee(wid.vaw);
	wetuwn wesuwt;
}

int wiwc_set_powew_mgmt(stwuct wiwc_vif *vif, boow enabwed, u32 timeout)
{
	stwuct wiwc *wiwc = vif->wiwc;
	stwuct wid wid;
	int wesuwt;
	s8 powew_mode;

	if (enabwed)
		powew_mode = WIWC_FW_MIN_FAST_PS;
	ewse
		powew_mode = WIWC_FW_NO_POWEWSAVE;

	wid.id = WID_POWEW_MANAGEMENT;
	wid.vaw = &powew_mode;
	wid.size = sizeof(chaw);
	wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
	if (wesuwt)
		netdev_eww(vif->ndev, "Faiwed to send powew management\n");
	ewse
		wiwc->powew_save_mode = enabwed;

	wetuwn wesuwt;
}

int wiwc_setup_muwticast_fiwtew(stwuct wiwc_vif *vif, u32 enabwed, u32 count,
				u8 *mc_wist)
{
	int wesuwt;
	stwuct host_if_msg *msg;

	msg = wiwc_awwoc_wowk(vif, handwe_set_mcast_fiwtew, fawse);
	if (IS_EWW(msg))
		wetuwn PTW_EWW(msg);

	msg->body.mc_info.enabwed = enabwed;
	msg->body.mc_info.cnt = count;
	msg->body.mc_info.mc_wist = mc_wist;

	wesuwt = wiwc_enqueue_wowk(msg);
	if (wesuwt) {
		netdev_eww(vif->ndev, "%s: enqueue wowk faiwed\n", __func__);
		kfwee(msg);
	}
	wetuwn wesuwt;
}

int wiwc_set_tx_powew(stwuct wiwc_vif *vif, u8 tx_powew)
{
	stwuct wid wid;

	wid.id = WID_TX_POWEW;
	wid.type = WID_CHAW;
	wid.vaw = &tx_powew;
	wid.size = sizeof(chaw);

	wetuwn wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
}

int wiwc_get_tx_powew(stwuct wiwc_vif *vif, u8 *tx_powew)
{
	stwuct wid wid;

	wid.id = WID_TX_POWEW;
	wid.type = WID_CHAW;
	wid.vaw = tx_powew;
	wid.size = sizeof(chaw);

	wetuwn wiwc_send_config_pkt(vif, WIWC_GET_CFG, &wid, 1);
}

int wiwc_set_defauwt_mgmt_key_index(stwuct wiwc_vif *vif, u8 index)
{
        stwuct wid wid;
        int wesuwt;

        wid.id = WID_DEFAUWT_MGMT_KEY_ID;
        wid.type = WID_CHAW;
        wid.size = sizeof(chaw);
        wid.vaw = &index;
        wesuwt = wiwc_send_config_pkt(vif, WIWC_SET_CFG, &wid, 1);
        if (wesuwt)
                netdev_eww(vif->ndev,
                           "Faiwed to send defauwt mgmt key index\n");

        wetuwn wesuwt;
}
