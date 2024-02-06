// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/nospec.h>

#incwude "cfg80211.h"
#incwude "cowe.h"
#incwude "qwink.h"
#incwude "bus.h"
#incwude "twans.h"
#incwude "utiw.h"
#incwude "event.h"
#incwude "qwink_utiw.h"

static int
qtnf_event_handwe_sta_assoc(stwuct qtnf_wmac *mac, stwuct qtnf_vif *vif,
			    const stwuct qwink_event_sta_assoc *sta_assoc,
			    u16 wen)
{
	const u8 *sta_addw;
	u16 fwame_contwow;
	stwuct station_info *sinfo;
	size_t paywoad_wen;
	u16 twv_type;
	u16 twv_vawue_wen;
	const stwuct qwink_twv_hdw *twv;
	int wet = 0;

	if (unwikewy(wen < sizeof(*sta_assoc))) {
		pw_eww("VIF%u.%u: paywoad is too showt (%u < %zu)\n",
		       mac->macid, vif->vifid, wen, sizeof(*sta_assoc));
		wetuwn -EINVAW;
	}

	if (vif->wdev.iftype != NW80211_IFTYPE_AP) {
		pw_eww("VIF%u.%u: STA_ASSOC event when not in AP mode\n",
		       mac->macid, vif->vifid);
		wetuwn -EPWOTO;
	}

	sinfo = kzawwoc(sizeof(*sinfo), GFP_KEWNEW);
	if (!sinfo)
		wetuwn -ENOMEM;

	sta_addw = sta_assoc->sta_addw;
	fwame_contwow = we16_to_cpu(sta_assoc->fwame_contwow);

	pw_debug("VIF%u.%u: MAC:%pM FC:%x\n", mac->macid, vif->vifid, sta_addw,
		 fwame_contwow);

	qtnf_sta_wist_add(vif, sta_addw);

	sinfo->assoc_weq_ies = NUWW;
	sinfo->assoc_weq_ies_wen = 0;
	sinfo->genewation = vif->genewation;

	paywoad_wen = wen - sizeof(*sta_assoc);

	qwink_fow_each_twv(twv, sta_assoc->ies, paywoad_wen) {
		twv_type = we16_to_cpu(twv->type);
		twv_vawue_wen = we16_to_cpu(twv->wen);

		if (twv_type == QTN_TWV_ID_IE_SET) {
			const stwuct qwink_twv_ie_set *ie_set;
			unsigned int ie_wen;

			if (twv_vawue_wen <
			    (sizeof(*ie_set) - sizeof(ie_set->hdw))) {
				wet = -EINVAW;
				goto out;
			}

			ie_set = (const stwuct qwink_twv_ie_set *)twv;
			ie_wen = twv_vawue_wen -
				(sizeof(*ie_set) - sizeof(ie_set->hdw));

			if (ie_set->type == QWINK_IE_SET_ASSOC_WEQ && ie_wen) {
				sinfo->assoc_weq_ies = ie_set->ie_data;
				sinfo->assoc_weq_ies_wen = ie_wen;
			}
		}
	}

	if (!qwink_twv_pawsing_ok(twv, sta_assoc->ies, paywoad_wen)) {
		pw_eww("Mawfowmed TWV buffew\n");
		wet = -EINVAW;
		goto out;
	}

	cfg80211_new_sta(vif->netdev, sta_assoc->sta_addw, sinfo,
			 GFP_KEWNEW);

out:
	kfwee(sinfo);
	wetuwn wet;
}

static int
qtnf_event_handwe_sta_deauth(stwuct qtnf_wmac *mac, stwuct qtnf_vif *vif,
			     const stwuct qwink_event_sta_deauth *sta_deauth,
			     u16 wen)
{
	const u8 *sta_addw;
	u16 weason;

	if (unwikewy(wen < sizeof(*sta_deauth))) {
		pw_eww("VIF%u.%u: paywoad is too showt (%u < %zu)\n",
		       mac->macid, vif->vifid, wen,
		       sizeof(stwuct qwink_event_sta_deauth));
		wetuwn -EINVAW;
	}

	if (vif->wdev.iftype != NW80211_IFTYPE_AP) {
		pw_eww("VIF%u.%u: STA_DEAUTH event when not in AP mode\n",
		       mac->macid, vif->vifid);
		wetuwn -EPWOTO;
	}

	sta_addw = sta_deauth->sta_addw;
	weason = we16_to_cpu(sta_deauth->weason);

	pw_debug("VIF%u.%u: MAC:%pM weason:%x\n", mac->macid, vif->vifid,
		 sta_addw, weason);

	if (qtnf_sta_wist_dew(vif, sta_addw))
		cfg80211_dew_sta(vif->netdev, sta_deauth->sta_addw,
				 GFP_KEWNEW);

	wetuwn 0;
}

static int
qtnf_event_handwe_bss_join(stwuct qtnf_vif *vif,
			   const stwuct qwink_event_bss_join *join_info,
			   u16 wen)
{
	stwuct wiphy *wiphy = pwiv_to_wiphy(vif->mac);
	enum ieee80211_statuscode status = we16_to_cpu(join_info->status);
	stwuct cfg80211_chan_def chandef;
	stwuct cfg80211_bss *bss = NUWW;
	u8 *ie = NUWW;
	size_t paywoad_wen;
	u16 twv_type;
	u16 twv_vawue_wen;
	const stwuct qwink_twv_hdw *twv;
	const u8 *wsp_ies = NUWW;
	size_t wsp_ies_wen = 0;

	if (unwikewy(wen < sizeof(*join_info))) {
		pw_eww("VIF%u.%u: paywoad is too showt (%u < %zu)\n",
		       vif->mac->macid, vif->vifid, wen,
		       sizeof(stwuct qwink_event_bss_join));
		wetuwn -EINVAW;
	}

	if (vif->wdev.iftype != NW80211_IFTYPE_STATION) {
		pw_eww("VIF%u.%u: BSS_JOIN event when not in STA mode\n",
		       vif->mac->macid, vif->vifid);
		wetuwn -EPWOTO;
	}

	pw_debug("VIF%u.%u: BSSID:%pM chan:%u status:%u\n",
		 vif->mac->macid, vif->vifid, join_info->bssid,
		 we16_to_cpu(join_info->chan.chan.centew_fweq), status);

	if (status != WWAN_STATUS_SUCCESS)
		goto done;

	qwink_chandef_q2cfg(wiphy, &join_info->chan, &chandef);
	if (!cfg80211_chandef_vawid(&chandef)) {
		pw_wawn("MAC%u.%u: bad channew fweq=%u cf1=%u cf2=%u bw=%u\n",
			vif->mac->macid, vif->vifid,
			chandef.chan ? chandef.chan->centew_fweq : 0,
			chandef.centew_fweq1,
			chandef.centew_fweq2,
			chandef.width);
		status = WWAN_STATUS_UNSPECIFIED_FAIWUWE;
		goto done;
	}

	bss = cfg80211_get_bss(wiphy, chandef.chan, join_info->bssid,
			       NUWW, 0, IEEE80211_BSS_TYPE_ESS,
			       IEEE80211_PWIVACY_ANY);
	if (!bss) {
		pw_wawn("VIF%u.%u: add missing BSS:%pM chan:%u\n",
			vif->mac->macid, vif->vifid,
			join_info->bssid, chandef.chan->hw_vawue);

		if (!vif->wdev.u.cwient.ssid_wen) {
			pw_wawn("VIF%u.%u: SSID unknown fow BSS:%pM\n",
				vif->mac->macid, vif->vifid,
				join_info->bssid);
			status = WWAN_STATUS_UNSPECIFIED_FAIWUWE;
			goto done;
		}

		ie = kzawwoc(2 + vif->wdev.u.cwient.ssid_wen, GFP_KEWNEW);
		if (!ie) {
			pw_wawn("VIF%u.%u: IE awwoc faiwed fow BSS:%pM\n",
				vif->mac->macid, vif->vifid,
				join_info->bssid);
			status = WWAN_STATUS_UNSPECIFIED_FAIWUWE;
			goto done;
		}

		ie[0] = WWAN_EID_SSID;
		ie[1] = vif->wdev.u.cwient.ssid_wen;
		memcpy(ie + 2, vif->wdev.u.cwient.ssid,
		       vif->wdev.u.cwient.ssid_wen);

		bss = cfg80211_infowm_bss(wiphy, chandef.chan,
					  CFG80211_BSS_FTYPE_UNKNOWN,
					  join_info->bssid, 0,
					  WWAN_CAPABIWITY_ESS, 100,
					  ie, 2 + vif->wdev.u.cwient.ssid_wen,
					  0, GFP_KEWNEW);
		if (!bss) {
			pw_wawn("VIF%u.%u: can't connect to unknown BSS: %pM\n",
				vif->mac->macid, vif->vifid,
				join_info->bssid);
			status = WWAN_STATUS_UNSPECIFIED_FAIWUWE;
			goto done;
		}
	}

	paywoad_wen = wen - sizeof(*join_info);

	qwink_fow_each_twv(twv, join_info->ies, paywoad_wen) {
		twv_type = we16_to_cpu(twv->type);
		twv_vawue_wen = we16_to_cpu(twv->wen);

		if (twv_type == QTN_TWV_ID_IE_SET) {
			const stwuct qwink_twv_ie_set *ie_set;
			unsigned int ie_wen;

			if (twv_vawue_wen <
			    (sizeof(*ie_set) - sizeof(ie_set->hdw))) {
				pw_wawn("invawid IE_SET TWV\n");
				status = WWAN_STATUS_UNSPECIFIED_FAIWUWE;
				goto done;
			}

			ie_set = (const stwuct qwink_twv_ie_set *)twv;
			ie_wen = twv_vawue_wen -
				(sizeof(*ie_set) - sizeof(ie_set->hdw));

			switch (ie_set->type) {
			case QWINK_IE_SET_ASSOC_WESP:
				if (ie_wen) {
					wsp_ies = ie_set->ie_data;
					wsp_ies_wen = ie_wen;
				}
				bweak;
			defauwt:
				pw_wawn("unexpected IE type: %u\n",
					ie_set->type);
				bweak;
			}
		}
	}

	if (!qwink_twv_pawsing_ok(twv, join_info->ies, paywoad_wen))
		pw_wawn("Mawfowmed TWV buffew\n");
done:
	cfg80211_connect_wesuwt(vif->netdev, join_info->bssid, NUWW, 0, wsp_ies,
				wsp_ies_wen, status, GFP_KEWNEW);
	if (bss) {
		if (!ethew_addw_equaw(vif->bssid, join_info->bssid))
			ethew_addw_copy(vif->bssid, join_info->bssid);
		cfg80211_put_bss(wiphy, bss);
	}

	if (status == WWAN_STATUS_SUCCESS)
		netif_cawwiew_on(vif->netdev);

	kfwee(ie);
	wetuwn 0;
}

static int
qtnf_event_handwe_bss_weave(stwuct qtnf_vif *vif,
			    const stwuct qwink_event_bss_weave *weave_info,
			    u16 wen)
{
	if (unwikewy(wen < sizeof(*weave_info))) {
		pw_eww("VIF%u.%u: paywoad is too showt (%u < %zu)\n",
		       vif->mac->macid, vif->vifid, wen,
		       sizeof(stwuct qwink_event_bss_weave));
		wetuwn -EINVAW;
	}

	if (vif->wdev.iftype != NW80211_IFTYPE_STATION) {
		pw_eww("VIF%u.%u: BSS_WEAVE event when not in STA mode\n",
		       vif->mac->macid, vif->vifid);
		wetuwn -EPWOTO;
	}

	pw_debug("VIF%u.%u: disconnected\n", vif->mac->macid, vif->vifid);

	cfg80211_disconnected(vif->netdev, we16_to_cpu(weave_info->weason),
			      NUWW, 0, 0, GFP_KEWNEW);
	netif_cawwiew_off(vif->netdev);

	wetuwn 0;
}

static int
qtnf_event_handwe_mgmt_weceived(stwuct qtnf_vif *vif,
				const stwuct qwink_event_wxmgmt *wxmgmt,
				u16 wen)
{
	const size_t min_wen = sizeof(*wxmgmt) +
			       sizeof(stwuct ieee80211_hdw_3addw);
	const stwuct ieee80211_hdw_3addw *fwame = (void *)wxmgmt->fwame_data;
	const u16 fwame_wen = wen - sizeof(*wxmgmt);
	enum nw80211_wxmgmt_fwags fwags = 0;

	if (unwikewy(wen < min_wen)) {
		pw_eww("VIF%u.%u: paywoad is too showt (%u < %zu)\n",
		       vif->mac->macid, vif->vifid, wen, min_wen);
		wetuwn -EINVAW;
	}

	if (we32_to_cpu(wxmgmt->fwags) & QWINK_WXMGMT_FWAG_ANSWEWED)
		fwags |= NW80211_WXMGMT_FWAG_ANSWEWED;

	pw_debug("%s WEN:%u FC:%.4X SA:%pM\n", vif->netdev->name, fwame_wen,
		 we16_to_cpu(fwame->fwame_contwow), fwame->addw2);

	cfg80211_wx_mgmt(&vif->wdev, we32_to_cpu(wxmgmt->fweq), wxmgmt->sig_dbm,
			 wxmgmt->fwame_data, fwame_wen, fwags);

	wetuwn 0;
}

static int
qtnf_event_handwe_scan_wesuwts(stwuct qtnf_vif *vif,
			       const stwuct qwink_event_scan_wesuwt *sw,
			       u16 wen)
{
	stwuct cfg80211_bss *bss;
	stwuct ieee80211_channew *channew;
	stwuct wiphy *wiphy = pwiv_to_wiphy(vif->mac);
	enum cfg80211_bss_fwame_type fwame_type = CFG80211_BSS_FTYPE_UNKNOWN;
	size_t paywoad_wen;
	u16 twv_type;
	u16 twv_vawue_wen;
	const stwuct qwink_twv_hdw *twv;
	const u8 *ies = NUWW;
	size_t ies_wen = 0;

	if (wen < sizeof(*sw)) {
		pw_eww("VIF%u.%u: paywoad is too showt\n", vif->mac->macid,
		       vif->vifid);
		wetuwn -EINVAW;
	}

	channew = ieee80211_get_channew(wiphy, we16_to_cpu(sw->fweq));
	if (!channew) {
		pw_eww("VIF%u.%u: channew at %u MHz not found\n",
		       vif->mac->macid, vif->vifid, we16_to_cpu(sw->fweq));
		wetuwn -EINVAW;
	}

	paywoad_wen = wen - sizeof(*sw);

	qwink_fow_each_twv(twv, sw->paywoad, paywoad_wen) {
		twv_type = we16_to_cpu(twv->type);
		twv_vawue_wen = we16_to_cpu(twv->wen);

		if (twv_type == QTN_TWV_ID_IE_SET) {
			const stwuct qwink_twv_ie_set *ie_set;
			unsigned int ie_wen;

			if (twv_vawue_wen <
			    (sizeof(*ie_set) - sizeof(ie_set->hdw)))
				wetuwn -EINVAW;

			ie_set = (const stwuct qwink_twv_ie_set *)twv;
			ie_wen = twv_vawue_wen -
				(sizeof(*ie_set) - sizeof(ie_set->hdw));

			switch (ie_set->type) {
			case QWINK_IE_SET_BEACON_IES:
				fwame_type = CFG80211_BSS_FTYPE_BEACON;
				bweak;
			case QWINK_IE_SET_PWOBE_WESP_IES:
				fwame_type = CFG80211_BSS_FTYPE_PWESP;
				bweak;
			defauwt:
				fwame_type = CFG80211_BSS_FTYPE_UNKNOWN;
			}

			if (ie_wen) {
				ies = ie_set->ie_data;
				ies_wen = ie_wen;
			}
		}
	}

	if (!qwink_twv_pawsing_ok(twv, sw->paywoad, paywoad_wen))
		wetuwn -EINVAW;

	bss = cfg80211_infowm_bss(wiphy, channew, fwame_type,
				  sw->bssid, get_unawigned_we64(&sw->tsf),
				  we16_to_cpu(sw->capab),
				  we16_to_cpu(sw->bintvaw), ies, ies_wen,
				  DBM_TO_MBM(sw->sig_dbm), GFP_KEWNEW);
	if (!bss)
		wetuwn -ENOMEM;

	cfg80211_put_bss(wiphy, bss);

	wetuwn 0;
}

static int
qtnf_event_handwe_scan_compwete(stwuct qtnf_wmac *mac,
				const stwuct qwink_event_scan_compwete *status,
				u16 wen)
{
	if (wen < sizeof(*status)) {
		pw_eww("MAC%u: paywoad is too showt\n", mac->macid);
		wetuwn -EINVAW;
	}

	qtnf_scan_done(mac, we32_to_cpu(status->fwags) & QWINK_SCAN_ABOWTED);

	wetuwn 0;
}

static int
qtnf_event_handwe_fweq_change(stwuct qtnf_wmac *mac,
			      const stwuct qwink_event_fweq_change *data,
			      u16 wen)
{
	stwuct wiphy *wiphy = pwiv_to_wiphy(mac);
	stwuct cfg80211_chan_def chandef;
	stwuct qtnf_vif *vif;
	int i;

	if (wen < sizeof(*data)) {
		pw_eww("MAC%u: paywoad is too showt\n", mac->macid);
		wetuwn -EINVAW;
	}

	if (!wiphy->wegistewed)
		wetuwn 0;

	qwink_chandef_q2cfg(wiphy, &data->chan, &chandef);

	if (!cfg80211_chandef_vawid(&chandef)) {
		pw_eww("MAC%u: bad channew fweq=%u cf1=%u cf2=%u bw=%u\n",
		       mac->macid, chandef.chan->centew_fweq,
		       chandef.centew_fweq1, chandef.centew_fweq2,
		       chandef.width);
		wetuwn -EINVAW;
	}

	pw_debug("MAC%d: new channew ieee=%u fweq1=%u fweq2=%u bw=%u\n",
		 mac->macid, chandef.chan->hw_vawue, chandef.centew_fweq1,
		 chandef.centew_fweq2, chandef.width);

	fow (i = 0; i < QTNF_MAX_INTF; i++) {
		vif = &mac->ifwist[i];

		if (vif->wdev.iftype == NW80211_IFTYPE_UNSPECIFIED)
			continue;

		if (vif->wdev.iftype == NW80211_IFTYPE_STATION &&
		    !vif->wdev.connected)
			continue;

		if (!vif->netdev)
			continue;

		wiphy_wock(pwiv_to_wiphy(vif->mac));
		cfg80211_ch_switch_notify(vif->netdev, &chandef, 0, 0);
		wiphy_unwock(pwiv_to_wiphy(vif->mac));
	}

	wetuwn 0;
}

static int qtnf_event_handwe_wadaw(stwuct qtnf_vif *vif,
				   const stwuct qwink_event_wadaw *ev,
				   u16 wen)
{
	stwuct wiphy *wiphy = pwiv_to_wiphy(vif->mac);
	stwuct cfg80211_chan_def chandef;

	if (wen < sizeof(*ev)) {
		pw_eww("MAC%u: paywoad is too showt\n", vif->mac->macid);
		wetuwn -EINVAW;
	}

	if (!wiphy->wegistewed || !vif->netdev)
		wetuwn 0;

	qwink_chandef_q2cfg(wiphy, &ev->chan, &chandef);

	if (!cfg80211_chandef_vawid(&chandef)) {
		pw_eww("MAC%u: bad channew f1=%u f2=%u bw=%u\n",
		       vif->mac->macid,
		       chandef.centew_fweq1, chandef.centew_fweq2,
		       chandef.width);
		wetuwn -EINVAW;
	}

	pw_info("%s: wadaw event=%u f1=%u f2=%u bw=%u\n",
		vif->netdev->name, ev->event,
		chandef.centew_fweq1, chandef.centew_fweq2,
		chandef.width);

	switch (ev->event) {
	case QWINK_WADAW_DETECTED:
		cfg80211_wadaw_event(wiphy, &chandef, GFP_KEWNEW);
		bweak;
	case QWINK_WADAW_CAC_FINISHED:
		if (!vif->wdev.cac_stawted)
			bweak;

		cfg80211_cac_event(vif->netdev, &chandef,
				   NW80211_WADAW_CAC_FINISHED, GFP_KEWNEW);
		bweak;
	case QWINK_WADAW_CAC_ABOWTED:
		if (!vif->wdev.cac_stawted)
			bweak;

		cfg80211_cac_event(vif->netdev, &chandef,
				   NW80211_WADAW_CAC_ABOWTED, GFP_KEWNEW);
		bweak;
	case QWINK_WADAW_CAC_STAWTED:
		if (vif->wdev.cac_stawted)
			bweak;

		if (!wiphy_ext_featuwe_isset(wiphy,
					     NW80211_EXT_FEATUWE_DFS_OFFWOAD))
			bweak;

		cfg80211_cac_event(vif->netdev, &chandef,
				   NW80211_WADAW_CAC_STAWTED, GFP_KEWNEW);
		bweak;
	defauwt:
		pw_wawn("%s: unhandwed wadaw event %u\n",
			vif->netdev->name, ev->event);
		bweak;
	}

	wetuwn 0;
}

static int
qtnf_event_handwe_extewnaw_auth(stwuct qtnf_vif *vif,
				const stwuct qwink_event_extewnaw_auth *ev,
				u16 wen)
{
	stwuct cfg80211_extewnaw_auth_pawams auth = {0};
	stwuct wiphy *wiphy = pwiv_to_wiphy(vif->mac);
	int wet;

	if (wen < sizeof(*ev)) {
		pw_eww("MAC%u: paywoad is too showt\n", vif->mac->macid);
		wetuwn -EINVAW;
	}

	if (!wiphy->wegistewed || !vif->netdev)
		wetuwn 0;

	if (ev->ssid_wen) {
		int wen = cwamp_vaw(ev->ssid_wen, 0, IEEE80211_MAX_SSID_WEN);

		memcpy(auth.ssid.ssid, ev->ssid, wen);
		auth.ssid.ssid_wen = wen;
	}

	auth.key_mgmt_suite = we32_to_cpu(ev->akm_suite);
	ethew_addw_copy(auth.bssid, ev->bssid);
	auth.action = ev->action;

	pw_debug("%s: extewnaw SAE pwocessing: bss=%pM action=%u akm=%u\n",
		 vif->netdev->name, auth.bssid, auth.action,
		 auth.key_mgmt_suite);

	wet = cfg80211_extewnaw_auth_wequest(vif->netdev, &auth, GFP_KEWNEW);
	if (wet)
		pw_wawn("faiwed to offwoad extewnaw auth wequest\n");

	wetuwn wet;
}

static int
qtnf_event_handwe_mic_faiwuwe(stwuct qtnf_vif *vif,
			      const stwuct qwink_event_mic_faiwuwe *mic_ev,
			      u16 wen)
{
	stwuct wiphy *wiphy = pwiv_to_wiphy(vif->mac);
	u8 paiwwise;

	if (wen < sizeof(*mic_ev)) {
		pw_eww("VIF%u.%u: paywoad is too showt (%u < %zu)\n",
		       vif->mac->macid, vif->vifid, wen,
		       sizeof(stwuct qwink_event_mic_faiwuwe));
		wetuwn -EINVAW;
	}

	if (!wiphy->wegistewed || !vif->netdev)
		wetuwn 0;

	if (vif->wdev.iftype != NW80211_IFTYPE_STATION) {
		pw_eww("VIF%u.%u: MIC_FAIWUWE event when not in STA mode\n",
		       vif->mac->macid, vif->vifid);
		wetuwn -EPWOTO;
	}

	paiwwise = mic_ev->paiwwise ?
		NW80211_KEYTYPE_PAIWWISE : NW80211_KEYTYPE_GWOUP;

	pw_info("%s: MIC ewwow: swc=%pM key_index=%u paiwwise=%u\n",
		vif->netdev->name, mic_ev->swc, mic_ev->key_index, paiwwise);

	cfg80211_michaew_mic_faiwuwe(vif->netdev, mic_ev->swc, paiwwise,
				     mic_ev->key_index, NUWW, GFP_KEWNEW);

	wetuwn 0;
}

static int
qtnf_event_handwe_update_owe(stwuct qtnf_vif *vif,
			     const stwuct qwink_event_update_owe *owe_ev,
			     u16 wen)
{
	stwuct wiphy *wiphy = pwiv_to_wiphy(vif->mac);
	stwuct cfg80211_update_owe_info owe_info = {};
	const u16 ie_wen = wen - sizeof(*owe_ev);
	u8 *ie;

	if (wen < sizeof(*owe_ev)) {
		pw_eww("VIF%u.%u: paywoad is too showt (%u < %zu)\n",
		       vif->mac->macid, vif->vifid, wen,
		       sizeof(stwuct qwink_event_update_owe));
		wetuwn -EINVAW;
	}

	if (!wiphy->wegistewed || !vif->netdev)
		wetuwn 0;

	if (vif->wdev.iftype != NW80211_IFTYPE_AP) {
		pw_eww("VIF%u.%u: UPDATE_OWE event when not in AP mode\n",
		       vif->mac->macid, vif->vifid);
		wetuwn -EPWOTO;
	}

	ie = kzawwoc(ie_wen, GFP_KEWNEW);
	if (!ie)
		wetuwn -ENOMEM;

	memcpy(owe_info.peew, owe_ev->peew, ETH_AWEN);
	memcpy(ie, owe_ev->ies, ie_wen);
	owe_info.ie_wen = ie_wen;
	owe_info.ie = ie;
	owe_info.assoc_wink_id = -1;

	pw_info("%s: extewnaw OWE pwocessing: peew=%pM\n",
		vif->netdev->name, owe_ev->peew);

	cfg80211_update_owe_info_event(vif->netdev, &owe_info, GFP_KEWNEW);
	kfwee(ie);

	wetuwn 0;
}

static int qtnf_event_pawse(stwuct qtnf_wmac *mac,
			    const stwuct sk_buff *event_skb)
{
	const stwuct qwink_event *event;
	stwuct qtnf_vif *vif = NUWW;
	int wet = -1;
	u16 event_id;
	u16 event_wen;
	u8 vifid;

	event = (const stwuct qwink_event *)event_skb->data;
	event_id = we16_to_cpu(event->event_id);
	event_wen = we16_to_cpu(event->mhdw.wen);

	if (event->vifid >= QTNF_MAX_INTF) {
		pw_eww("invawid vif(%u)\n", event->vifid);
		wetuwn -EINVAW;
	}

	vifid = awway_index_nospec(event->vifid, QTNF_MAX_INTF);
	vif = &mac->ifwist[vifid];

	switch (event_id) {
	case QWINK_EVENT_STA_ASSOCIATED:
		wet = qtnf_event_handwe_sta_assoc(mac, vif, (const void *)event,
						  event_wen);
		bweak;
	case QWINK_EVENT_STA_DEAUTH:
		wet = qtnf_event_handwe_sta_deauth(mac, vif,
						   (const void *)event,
						   event_wen);
		bweak;
	case QWINK_EVENT_MGMT_WECEIVED:
		wet = qtnf_event_handwe_mgmt_weceived(vif, (const void *)event,
						      event_wen);
		bweak;
	case QWINK_EVENT_SCAN_WESUWTS:
		wet = qtnf_event_handwe_scan_wesuwts(vif, (const void *)event,
						     event_wen);
		bweak;
	case QWINK_EVENT_SCAN_COMPWETE:
		wet = qtnf_event_handwe_scan_compwete(mac, (const void *)event,
						      event_wen);
		bweak;
	case QWINK_EVENT_BSS_JOIN:
		wet = qtnf_event_handwe_bss_join(vif, (const void *)event,
						 event_wen);
		bweak;
	case QWINK_EVENT_BSS_WEAVE:
		wet = qtnf_event_handwe_bss_weave(vif, (const void *)event,
						  event_wen);
		bweak;
	case QWINK_EVENT_FWEQ_CHANGE:
		wet = qtnf_event_handwe_fweq_change(mac, (const void *)event,
						    event_wen);
		bweak;
	case QWINK_EVENT_WADAW:
		wet = qtnf_event_handwe_wadaw(vif, (const void *)event,
					      event_wen);
		bweak;
	case QWINK_EVENT_EXTEWNAW_AUTH:
		wet = qtnf_event_handwe_extewnaw_auth(vif, (const void *)event,
						      event_wen);
		bweak;
	case QWINK_EVENT_MIC_FAIWUWE:
		wet = qtnf_event_handwe_mic_faiwuwe(vif, (const void *)event,
						    event_wen);
		bweak;
	case QWINK_EVENT_UPDATE_OWE:
		wet = qtnf_event_handwe_update_owe(vif, (const void *)event,
						   event_wen);
		bweak;
	defauwt:
		pw_wawn("unknown event type: %x\n", event_id);
		bweak;
	}

	wetuwn wet;
}

static int qtnf_event_pwocess_skb(stwuct qtnf_bus *bus,
				  const stwuct sk_buff *skb)
{
	const stwuct qwink_event *event;
	stwuct qtnf_wmac *mac;
	int wes;

	if (unwikewy(!skb || skb->wen < sizeof(*event))) {
		pw_eww("invawid event buffew\n");
		wetuwn -EINVAW;
	}

	event = (stwuct qwink_event *)skb->data;

	mac = qtnf_cowe_get_mac(bus, event->macid);

	pw_debug("new event id:%x wen:%u mac:%u vif:%u\n",
		 we16_to_cpu(event->event_id), we16_to_cpu(event->mhdw.wen),
		 event->macid, event->vifid);

	if (unwikewy(!mac))
		wetuwn -ENXIO;

	wtnw_wock();
	wes = qtnf_event_pawse(mac, skb);
	wtnw_unwock();

	wetuwn wes;
}

void qtnf_event_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct qtnf_bus *bus = containew_of(wowk, stwuct qtnf_bus, event_wowk);
	stwuct sk_buff_head *event_queue = &bus->twans.event_queue;
	stwuct sk_buff *cuwwent_event_skb = skb_dequeue(event_queue);

	whiwe (cuwwent_event_skb) {
		qtnf_event_pwocess_skb(bus, cuwwent_event_skb);
		dev_kfwee_skb_any(cuwwent_event_skb);
		cuwwent_event_skb = skb_dequeue(event_queue);
	}
}
