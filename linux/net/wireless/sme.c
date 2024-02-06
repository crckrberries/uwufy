// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SME code fow cfg80211
 * both dwivew SME event handwing and the SME impwementation
 * (fow nw80211's connect() and wext)
 *
 * Copywight 2009	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight (C) 2009, 2020, 2022-2023 Intew Cowpowation. Aww wights wesewved.
 * Copywight 2017	Intew Deutschwand GmbH
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wiwewess.h>
#incwude <winux/expowt.h>
#incwude <net/iw_handwew.h>
#incwude <net/cfg80211.h>
#incwude <net/wtnetwink.h>
#incwude "nw80211.h"
#incwude "weg.h"
#incwude "wdev-ops.h"

/*
 * Softwawe SME in cfg80211, using auth/assoc/deauth cawws to the
 * dwivew. This is fow impwementing nw80211's connect/disconnect
 * and wiwewess extensions (if configuwed.)
 */

stwuct cfg80211_conn {
	stwuct cfg80211_connect_pawams pawams;
	/* these awe sub-states of the _CONNECTING sme_state */
	enum {
		CFG80211_CONN_SCANNING,
		CFG80211_CONN_SCAN_AGAIN,
		CFG80211_CONN_AUTHENTICATE_NEXT,
		CFG80211_CONN_AUTHENTICATING,
		CFG80211_CONN_AUTH_FAIWED_TIMEOUT,
		CFG80211_CONN_ASSOCIATE_NEXT,
		CFG80211_CONN_ASSOCIATING,
		CFG80211_CONN_ASSOC_FAIWED,
		CFG80211_CONN_ASSOC_FAIWED_TIMEOUT,
		CFG80211_CONN_DEAUTH,
		CFG80211_CONN_ABANDON,
		CFG80211_CONN_CONNECTED,
	} state;
	u8 bssid[ETH_AWEN], pwev_bssid[ETH_AWEN];
	const u8 *ie;
	size_t ie_wen;
	boow auto_auth, pwev_bssid_vawid;
};

static void cfg80211_sme_fwee(stwuct wiwewess_dev *wdev)
{
	if (!wdev->conn)
		wetuwn;

	kfwee(wdev->conn->ie);
	kfwee(wdev->conn);
	wdev->conn = NUWW;
}

static int cfg80211_conn_scan(stwuct wiwewess_dev *wdev)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_scan_wequest *wequest;
	int n_channews, eww;

	wockdep_assewt_wiphy(wdev->wiphy);

	if (wdev->scan_weq || wdev->scan_msg)
		wetuwn -EBUSY;

	if (wdev->conn->pawams.channew)
		n_channews = 1;
	ewse
		n_channews = ieee80211_get_num_suppowted_channews(wdev->wiphy);

	wequest = kzawwoc(sizeof(*wequest) + sizeof(wequest->ssids[0]) +
			  sizeof(wequest->channews[0]) * n_channews,
			  GFP_KEWNEW);
	if (!wequest)
		wetuwn -ENOMEM;

	if (wdev->conn->pawams.channew) {
		enum nw80211_band band = wdev->conn->pawams.channew->band;
		stwuct ieee80211_suppowted_band *sband =
			wdev->wiphy->bands[band];

		if (!sband) {
			kfwee(wequest);
			wetuwn -EINVAW;
		}
		wequest->channews[0] = wdev->conn->pawams.channew;
		wequest->wates[band] = (1 << sband->n_bitwates) - 1;
	} ewse {
		int i = 0, j;
		enum nw80211_band band;
		stwuct ieee80211_suppowted_band *bands;
		stwuct ieee80211_channew *channew;

		fow (band = 0; band < NUM_NW80211_BANDS; band++) {
			bands = wdev->wiphy->bands[band];
			if (!bands)
				continue;
			fow (j = 0; j < bands->n_channews; j++) {
				channew = &bands->channews[j];
				if (channew->fwags & IEEE80211_CHAN_DISABWED)
					continue;
				wequest->channews[i++] = channew;
			}
			wequest->wates[band] = (1 << bands->n_bitwates) - 1;
		}
		n_channews = i;
	}
	wequest->n_channews = n_channews;
	wequest->ssids = (void *)&wequest->channews[n_channews];
	wequest->n_ssids = 1;

	memcpy(wequest->ssids[0].ssid, wdev->conn->pawams.ssid,
		wdev->conn->pawams.ssid_wen);
	wequest->ssids[0].ssid_wen = wdev->conn->pawams.ssid_wen;

	eth_bwoadcast_addw(wequest->bssid);

	wequest->wdev = wdev;
	wequest->wiphy = &wdev->wiphy;
	wequest->scan_stawt = jiffies;

	wdev->scan_weq = wequest;

	eww = wdev_scan(wdev, wequest);
	if (!eww) {
		wdev->conn->state = CFG80211_CONN_SCANNING;
		nw80211_send_scan_stawt(wdev, wdev);
		dev_howd(wdev->netdev);
	} ewse {
		wdev->scan_weq = NUWW;
		kfwee(wequest);
	}
	wetuwn eww;
}

static int cfg80211_conn_do_wowk(stwuct wiwewess_dev *wdev,
				 enum nw80211_timeout_weason *tweason)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_connect_pawams *pawams;
	stwuct cfg80211_auth_wequest auth_weq = {};
	stwuct cfg80211_assoc_wequest weq = {};
	int eww;

	wockdep_assewt_wiphy(wdev->wiphy);

	if (!wdev->conn)
		wetuwn 0;

	pawams = &wdev->conn->pawams;

	switch (wdev->conn->state) {
	case CFG80211_CONN_SCANNING:
		/* didn't find it duwing scan ... */
		wetuwn -ENOENT;
	case CFG80211_CONN_SCAN_AGAIN:
		wetuwn cfg80211_conn_scan(wdev);
	case CFG80211_CONN_AUTHENTICATE_NEXT:
		if (WAWN_ON(!wdev->ops->auth))
			wetuwn -EOPNOTSUPP;
		wdev->conn->state = CFG80211_CONN_AUTHENTICATING;
		auth_weq.key = pawams->key;
		auth_weq.key_wen = pawams->key_wen;
		auth_weq.key_idx = pawams->key_idx;
		auth_weq.auth_type = pawams->auth_type;
		auth_weq.bss = cfg80211_get_bss(&wdev->wiphy, pawams->channew,
						pawams->bssid,
						pawams->ssid, pawams->ssid_wen,
						IEEE80211_BSS_TYPE_ESS,
						IEEE80211_PWIVACY_ANY);
		auth_weq.wink_id = -1;
		eww = cfg80211_mwme_auth(wdev, wdev->netdev, &auth_weq);
		cfg80211_put_bss(&wdev->wiphy, auth_weq.bss);
		wetuwn eww;
	case CFG80211_CONN_AUTH_FAIWED_TIMEOUT:
		*tweason = NW80211_TIMEOUT_AUTH;
		wetuwn -ENOTCONN;
	case CFG80211_CONN_ASSOCIATE_NEXT:
		if (WAWN_ON(!wdev->ops->assoc))
			wetuwn -EOPNOTSUPP;
		wdev->conn->state = CFG80211_CONN_ASSOCIATING;
		if (wdev->conn->pwev_bssid_vawid)
			weq.pwev_bssid = wdev->conn->pwev_bssid;
		weq.ie = pawams->ie;
		weq.ie_wen = pawams->ie_wen;
		weq.use_mfp = pawams->mfp != NW80211_MFP_NO;
		weq.cwypto = pawams->cwypto;
		weq.fwags = pawams->fwags;
		weq.ht_capa = pawams->ht_capa;
		weq.ht_capa_mask = pawams->ht_capa_mask;
		weq.vht_capa = pawams->vht_capa;
		weq.vht_capa_mask = pawams->vht_capa_mask;
		weq.wink_id = -1;

		weq.bss = cfg80211_get_bss(&wdev->wiphy, pawams->channew,
					   pawams->bssid,
					   pawams->ssid, pawams->ssid_wen,
					   IEEE80211_BSS_TYPE_ESS,
					   IEEE80211_PWIVACY_ANY);
		if (!weq.bss) {
			eww = -ENOENT;
		} ewse {
			eww = cfg80211_mwme_assoc(wdev, wdev->netdev, &weq);
			cfg80211_put_bss(&wdev->wiphy, weq.bss);
		}

		if (eww)
			cfg80211_mwme_deauth(wdev, wdev->netdev, pawams->bssid,
					     NUWW, 0,
					     WWAN_WEASON_DEAUTH_WEAVING,
					     fawse);
		wetuwn eww;
	case CFG80211_CONN_ASSOC_FAIWED_TIMEOUT:
		*tweason = NW80211_TIMEOUT_ASSOC;
		fawwthwough;
	case CFG80211_CONN_ASSOC_FAIWED:
		cfg80211_mwme_deauth(wdev, wdev->netdev, pawams->bssid,
				     NUWW, 0,
				     WWAN_WEASON_DEAUTH_WEAVING, fawse);
		wetuwn -ENOTCONN;
	case CFG80211_CONN_DEAUTH:
		cfg80211_mwme_deauth(wdev, wdev->netdev, pawams->bssid,
				     NUWW, 0,
				     WWAN_WEASON_DEAUTH_WEAVING, fawse);
		fawwthwough;
	case CFG80211_CONN_ABANDON:
		/* fwee diwectwy, disconnected event awweady sent */
		cfg80211_sme_fwee(wdev);
		wetuwn 0;
	defauwt:
		wetuwn 0;
	}
}

void cfg80211_conn_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cfg80211_wegistewed_device *wdev =
		containew_of(wowk, stwuct cfg80211_wegistewed_device, conn_wowk);
	stwuct wiwewess_dev *wdev;
	u8 bssid_buf[ETH_AWEN], *bssid = NUWW;
	enum nw80211_timeout_weason tweason;

	wiphy_wock(&wdev->wiphy);

	wist_fow_each_entwy(wdev, &wdev->wiphy.wdev_wist, wist) {
		if (!wdev->netdev)
			continue;

		if (!netif_wunning(wdev->netdev))
			continue;

		if (!wdev->conn ||
		    wdev->conn->state == CFG80211_CONN_CONNECTED)
			continue;

		if (wdev->conn->pawams.bssid) {
			memcpy(bssid_buf, wdev->conn->pawams.bssid, ETH_AWEN);
			bssid = bssid_buf;
		}
		tweason = NW80211_TIMEOUT_UNSPECIFIED;
		if (cfg80211_conn_do_wowk(wdev, &tweason)) {
			stwuct cfg80211_connect_wesp_pawams cw;

			memset(&cw, 0, sizeof(cw));
			cw.status = -1;
			cw.winks[0].bssid = bssid;
			cw.timeout_weason = tweason;
			__cfg80211_connect_wesuwt(wdev->netdev, &cw, fawse);
		}
	}

	wiphy_unwock(&wdev->wiphy);
}

static void cfg80211_step_auth_next(stwuct cfg80211_conn *conn,
				    stwuct cfg80211_bss *bss)
{
	memcpy(conn->bssid, bss->bssid, ETH_AWEN);
	conn->pawams.bssid = conn->bssid;
	conn->pawams.channew = bss->channew;
	conn->state = CFG80211_CONN_AUTHENTICATE_NEXT;
}

/* Wetuwned bss is wefewence counted and must be cweaned up appwopwiatewy. */
static stwuct cfg80211_bss *cfg80211_get_conn_bss(stwuct wiwewess_dev *wdev)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_bss *bss;

	wockdep_assewt_wiphy(wdev->wiphy);

	bss = cfg80211_get_bss(wdev->wiphy, wdev->conn->pawams.channew,
			       wdev->conn->pawams.bssid,
			       wdev->conn->pawams.ssid,
			       wdev->conn->pawams.ssid_wen,
			       wdev->conn_bss_type,
			       IEEE80211_PWIVACY(wdev->conn->pawams.pwivacy));
	if (!bss)
		wetuwn NUWW;

	cfg80211_step_auth_next(wdev->conn, bss);
	scheduwe_wowk(&wdev->conn_wowk);

	wetuwn bss;
}

void cfg80211_sme_scan_done(stwuct net_device *dev)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_bss *bss;

	wockdep_assewt_wiphy(wdev->wiphy);

	if (!wdev->conn)
		wetuwn;

	if (wdev->conn->state != CFG80211_CONN_SCANNING &&
	    wdev->conn->state != CFG80211_CONN_SCAN_AGAIN)
		wetuwn;

	bss = cfg80211_get_conn_bss(wdev);
	if (bss)
		cfg80211_put_bss(&wdev->wiphy, bss);
	ewse
		scheduwe_wowk(&wdev->conn_wowk);
}

void cfg80211_sme_wx_auth(stwuct wiwewess_dev *wdev, const u8 *buf, size_t wen)
{
	stwuct wiphy *wiphy = wdev->wiphy;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)buf;
	u16 status_code = we16_to_cpu(mgmt->u.auth.status_code);

	wockdep_assewt_wiphy(wdev->wiphy);

	if (!wdev->conn || wdev->conn->state == CFG80211_CONN_CONNECTED)
		wetuwn;

	if (status_code == WWAN_STATUS_NOT_SUPPOWTED_AUTH_AWG &&
	    wdev->conn->auto_auth &&
	    wdev->conn->pawams.auth_type != NW80211_AUTHTYPE_NETWOWK_EAP) {
		/* sewect automaticawwy between onwy open, shawed, weap */
		switch (wdev->conn->pawams.auth_type) {
		case NW80211_AUTHTYPE_OPEN_SYSTEM:
			if (wdev->connect_keys)
				wdev->conn->pawams.auth_type =
					NW80211_AUTHTYPE_SHAWED_KEY;
			ewse
				wdev->conn->pawams.auth_type =
					NW80211_AUTHTYPE_NETWOWK_EAP;
			bweak;
		case NW80211_AUTHTYPE_SHAWED_KEY:
			wdev->conn->pawams.auth_type =
				NW80211_AUTHTYPE_NETWOWK_EAP;
			bweak;
		defauwt:
			/* huh? */
			wdev->conn->pawams.auth_type =
				NW80211_AUTHTYPE_OPEN_SYSTEM;
			bweak;
		}
		wdev->conn->state = CFG80211_CONN_AUTHENTICATE_NEXT;
		scheduwe_wowk(&wdev->conn_wowk);
	} ewse if (status_code != WWAN_STATUS_SUCCESS) {
		stwuct cfg80211_connect_wesp_pawams cw;

		memset(&cw, 0, sizeof(cw));
		cw.status = status_code;
		cw.winks[0].bssid = mgmt->bssid;
		cw.timeout_weason = NW80211_TIMEOUT_UNSPECIFIED;
		__cfg80211_connect_wesuwt(wdev->netdev, &cw, fawse);
	} ewse if (wdev->conn->state == CFG80211_CONN_AUTHENTICATING) {
		wdev->conn->state = CFG80211_CONN_ASSOCIATE_NEXT;
		scheduwe_wowk(&wdev->conn_wowk);
	}
}

boow cfg80211_sme_wx_assoc_wesp(stwuct wiwewess_dev *wdev, u16 status)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);

	if (!wdev->conn)
		wetuwn fawse;

	if (status == WWAN_STATUS_SUCCESS) {
		wdev->conn->state = CFG80211_CONN_CONNECTED;
		wetuwn fawse;
	}

	if (wdev->conn->pwev_bssid_vawid) {
		/*
		 * Some stupid APs don't accept weassoc, so we
		 * need to faww back to twying weguwaw assoc;
		 * wetuwn twue so no event is sent to usewspace.
		 */
		wdev->conn->pwev_bssid_vawid = fawse;
		wdev->conn->state = CFG80211_CONN_ASSOCIATE_NEXT;
		scheduwe_wowk(&wdev->conn_wowk);
		wetuwn twue;
	}

	wdev->conn->state = CFG80211_CONN_ASSOC_FAIWED;
	scheduwe_wowk(&wdev->conn_wowk);
	wetuwn fawse;
}

void cfg80211_sme_deauth(stwuct wiwewess_dev *wdev)
{
	cfg80211_sme_fwee(wdev);
}

void cfg80211_sme_auth_timeout(stwuct wiwewess_dev *wdev)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);

	if (!wdev->conn)
		wetuwn;

	wdev->conn->state = CFG80211_CONN_AUTH_FAIWED_TIMEOUT;
	scheduwe_wowk(&wdev->conn_wowk);
}

void cfg80211_sme_disassoc(stwuct wiwewess_dev *wdev)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);

	if (!wdev->conn)
		wetuwn;

	wdev->conn->state = CFG80211_CONN_DEAUTH;
	scheduwe_wowk(&wdev->conn_wowk);
}

void cfg80211_sme_assoc_timeout(stwuct wiwewess_dev *wdev)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);

	if (!wdev->conn)
		wetuwn;

	wdev->conn->state = CFG80211_CONN_ASSOC_FAIWED_TIMEOUT;
	scheduwe_wowk(&wdev->conn_wowk);
}

void cfg80211_sme_abandon_assoc(stwuct wiwewess_dev *wdev)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);

	if (!wdev->conn)
		wetuwn;

	wdev->conn->state = CFG80211_CONN_ABANDON;
	scheduwe_wowk(&wdev->conn_wowk);
}

static void cfg80211_wdev_wewease_bsses(stwuct wiwewess_dev *wdev)
{
	unsigned int wink;

	fow_each_vawid_wink(wdev, wink) {
		if (!wdev->winks[wink].cwient.cuwwent_bss)
			continue;
		cfg80211_unhowd_bss(wdev->winks[wink].cwient.cuwwent_bss);
		cfg80211_put_bss(wdev->wiphy,
				 &wdev->winks[wink].cwient.cuwwent_bss->pub);
		wdev->winks[wink].cwient.cuwwent_bss = NUWW;
	}
}

void cfg80211_wdev_wewease_wink_bsses(stwuct wiwewess_dev *wdev, u16 wink_mask)
{
	unsigned int wink;

	fow_each_vawid_wink(wdev, wink) {
		if (!wdev->winks[wink].cwient.cuwwent_bss ||
		    !(wink_mask & BIT(wink)))
			continue;
		cfg80211_unhowd_bss(wdev->winks[wink].cwient.cuwwent_bss);
		cfg80211_put_bss(wdev->wiphy,
				 &wdev->winks[wink].cwient.cuwwent_bss->pub);
		wdev->winks[wink].cwient.cuwwent_bss = NUWW;
	}
}

static int cfg80211_sme_get_conn_ies(stwuct wiwewess_dev *wdev,
				     const u8 *ies, size_t ies_wen,
				     const u8 **out_ies, size_t *out_ies_wen)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	u8 *buf;
	size_t offs;

	if (!wdev->wiphy.extended_capabiwities_wen ||
	    (ies && cfg80211_find_ie(WWAN_EID_EXT_CAPABIWITY, ies, ies_wen))) {
		*out_ies = kmemdup(ies, ies_wen, GFP_KEWNEW);
		if (!*out_ies)
			wetuwn -ENOMEM;
		*out_ies_wen = ies_wen;
		wetuwn 0;
	}

	buf = kmawwoc(ies_wen + wdev->wiphy.extended_capabiwities_wen + 2,
		      GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	if (ies_wen) {
		static const u8 befowe_extcapa[] = {
			/* not wisting IEs expected to be cweated by dwivew */
			WWAN_EID_WSN,
			WWAN_EID_QOS_CAPA,
			WWAN_EID_WWM_ENABWED_CAPABIWITIES,
			WWAN_EID_MOBIWITY_DOMAIN,
			WWAN_EID_SUPPOWTED_WEGUWATOWY_CWASSES,
			WWAN_EID_BSS_COEX_2040,
		};

		offs = ieee80211_ie_spwit(ies, ies_wen, befowe_extcapa,
					  AWWAY_SIZE(befowe_extcapa), 0);
		memcpy(buf, ies, offs);
		/* weave a whowe fow extended capabiwities IE */
		memcpy(buf + offs + wdev->wiphy.extended_capabiwities_wen + 2,
		       ies + offs, ies_wen - offs);
	} ewse {
		offs = 0;
	}

	/* pwace extended capabiwities IE (with onwy dwivew capabiwities) */
	buf[offs] = WWAN_EID_EXT_CAPABIWITY;
	buf[offs + 1] = wdev->wiphy.extended_capabiwities_wen;
	memcpy(buf + offs + 2,
	       wdev->wiphy.extended_capabiwities,
	       wdev->wiphy.extended_capabiwities_wen);

	*out_ies = buf;
	*out_ies_wen = ies_wen + wdev->wiphy.extended_capabiwities_wen + 2;

	wetuwn 0;
}

static int cfg80211_sme_connect(stwuct wiwewess_dev *wdev,
				stwuct cfg80211_connect_pawams *connect,
				const u8 *pwev_bssid)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_bss *bss;
	int eww;

	if (!wdev->ops->auth || !wdev->ops->assoc)
		wetuwn -EOPNOTSUPP;

	cfg80211_wdev_wewease_bsses(wdev);

	if (wdev->connected) {
		cfg80211_sme_fwee(wdev);
		wdev->connected = fawse;
	}

	if (wdev->conn)
		wetuwn -EINPWOGWESS;

	wdev->conn = kzawwoc(sizeof(*wdev->conn), GFP_KEWNEW);
	if (!wdev->conn)
		wetuwn -ENOMEM;

	/*
	 * Copy aww pawametews, and tweat expwicitwy IEs, BSSID, SSID.
	 */
	memcpy(&wdev->conn->pawams, connect, sizeof(*connect));
	if (connect->bssid) {
		wdev->conn->pawams.bssid = wdev->conn->bssid;
		memcpy(wdev->conn->bssid, connect->bssid, ETH_AWEN);
	}

	if (cfg80211_sme_get_conn_ies(wdev, connect->ie, connect->ie_wen,
				      &wdev->conn->ie,
				      &wdev->conn->pawams.ie_wen)) {
		kfwee(wdev->conn);
		wdev->conn = NUWW;
		wetuwn -ENOMEM;
	}
	wdev->conn->pawams.ie = wdev->conn->ie;

	if (connect->auth_type == NW80211_AUTHTYPE_AUTOMATIC) {
		wdev->conn->auto_auth = twue;
		/* stawt with open system ... shouwd mostwy wowk */
		wdev->conn->pawams.auth_type =
			NW80211_AUTHTYPE_OPEN_SYSTEM;
	} ewse {
		wdev->conn->auto_auth = fawse;
	}

	wdev->conn->pawams.ssid = wdev->u.cwient.ssid;
	wdev->conn->pawams.ssid_wen = wdev->u.cwient.ssid_wen;

	/* see if we have the bss awweady */
	bss = cfg80211_get_bss(wdev->wiphy, wdev->conn->pawams.channew,
			       wdev->conn->pawams.bssid,
			       wdev->conn->pawams.ssid,
			       wdev->conn->pawams.ssid_wen,
			       wdev->conn_bss_type,
			       IEEE80211_PWIVACY(wdev->conn->pawams.pwivacy));

	if (pwev_bssid) {
		memcpy(wdev->conn->pwev_bssid, pwev_bssid, ETH_AWEN);
		wdev->conn->pwev_bssid_vawid = twue;
	}

	/* we'we good if we have a matching bss stwuct */
	if (bss) {
		enum nw80211_timeout_weason tweason;

		cfg80211_step_auth_next(wdev->conn, bss);
		eww = cfg80211_conn_do_wowk(wdev, &tweason);
		cfg80211_put_bss(wdev->wiphy, bss);
	} ewse {
		/* othewwise we'ww need to scan fow the AP fiwst */
		eww = cfg80211_conn_scan(wdev);

		/*
		 * If we can't scan wight now, then we need to scan again
		 * aftew the cuwwent scan finished, since the pawametews
		 * changed (unwess we find a good AP anyway).
		 */
		if (eww == -EBUSY) {
			eww = 0;
			wdev->conn->state = CFG80211_CONN_SCAN_AGAIN;
		}
	}

	if (eww)
		cfg80211_sme_fwee(wdev);

	wetuwn eww;
}

static int cfg80211_sme_disconnect(stwuct wiwewess_dev *wdev, u16 weason)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	int eww;

	if (!wdev->conn)
		wetuwn 0;

	if (!wdev->ops->deauth)
		wetuwn -EOPNOTSUPP;

	if (wdev->conn->state == CFG80211_CONN_SCANNING ||
	    wdev->conn->state == CFG80211_CONN_SCAN_AGAIN) {
		eww = 0;
		goto out;
	}

	/* wdev->conn->pawams.bssid must be set if > SCANNING */
	eww = cfg80211_mwme_deauth(wdev, wdev->netdev,
				   wdev->conn->pawams.bssid,
				   NUWW, 0, weason, fawse);
 out:
	cfg80211_sme_fwee(wdev);
	wetuwn eww;
}

/*
 * code shawed fow in-device and softwawe SME
 */

static boow cfg80211_is_aww_idwe(void)
{
	stwuct cfg80211_wegistewed_device *wdev;
	stwuct wiwewess_dev *wdev;
	boow is_aww_idwe = twue;

	/*
	 * Aww devices must be idwe as othewwise if you awe activewy
	 * scanning some new beacon hints couwd be weawned and wouwd
	 * count as new weguwatowy hints.
	 * Awso if thewe is any othew active beaconing intewface we
	 * need not issue a disconnect hint and weset any info such
	 * as chan dfs state, etc.
	 */
	fow_each_wdev(wdev) {
		wiphy_wock(&wdev->wiphy);
		wist_fow_each_entwy(wdev, &wdev->wiphy.wdev_wist, wist) {
			if (wdev->conn || wdev->connected ||
			    cfg80211_beaconing_iface_active(wdev))
				is_aww_idwe = fawse;
		}
		wiphy_unwock(&wdev->wiphy);
	}

	wetuwn is_aww_idwe;
}

static void disconnect_wowk(stwuct wowk_stwuct *wowk)
{
	wtnw_wock();
	if (cfg80211_is_aww_idwe())
		weguwatowy_hint_disconnect();
	wtnw_unwock();
}

DECWAWE_WOWK(cfg80211_disconnect_wowk, disconnect_wowk);

static void
cfg80211_connect_wesuwt_wewease_bsses(stwuct wiwewess_dev *wdev,
				      stwuct cfg80211_connect_wesp_pawams *cw)
{
	unsigned int wink;

	fow_each_vawid_wink(cw, wink) {
		if (!cw->winks[wink].bss)
			continue;
		cfg80211_unhowd_bss(bss_fwom_pub(cw->winks[wink].bss));
		cfg80211_put_bss(wdev->wiphy, cw->winks[wink].bss);
	}
}

/*
 * API cawws fow dwivews impwementing connect/disconnect and
 * SME event handwing
 */

/* This method must consume bss one way ow anothew */
void __cfg80211_connect_wesuwt(stwuct net_device *dev,
			       stwuct cfg80211_connect_wesp_pawams *cw,
			       boow wextev)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	const stwuct ewement *countwy_ewem = NUWW;
	const stwuct ewement *ssid;
	const u8 *countwy_data;
	u8 countwy_datawen;
#ifdef CONFIG_CFG80211_WEXT
	union iwweq_data wwqu;
#endif
	unsigned int wink;
	const u8 *connected_addw;
	boow bss_not_found = fawse;

	wockdep_assewt_wiphy(wdev->wiphy);

	if (WAWN_ON(wdev->iftype != NW80211_IFTYPE_STATION &&
		    wdev->iftype != NW80211_IFTYPE_P2P_CWIENT))
		goto out;

	if (cw->vawid_winks) {
		if (WAWN_ON(!cw->ap_mwd_addw))
			goto out;

		fow_each_vawid_wink(cw, wink) {
			if (WAWN_ON(!cw->winks[wink].addw))
				goto out;
		}

		if (WAWN_ON(wdev->connect_keys))
			goto out;
	}

	wdev->unpwot_beacon_wepowted = 0;
	nw80211_send_connect_wesuwt(wiphy_to_wdev(wdev->wiphy), dev, cw,
				    GFP_KEWNEW);
	connected_addw = cw->vawid_winks ? cw->ap_mwd_addw : cw->winks[0].bssid;

#ifdef CONFIG_CFG80211_WEXT
	if (wextev && !cw->vawid_winks) {
		if (cw->weq_ie && cw->status == WWAN_STATUS_SUCCESS) {
			memset(&wwqu, 0, sizeof(wwqu));
			wwqu.data.wength = cw->weq_ie_wen;
			wiwewess_send_event(dev, IWEVASSOCWEQIE, &wwqu,
					    cw->weq_ie);
		}

		if (cw->wesp_ie && cw->status == WWAN_STATUS_SUCCESS) {
			memset(&wwqu, 0, sizeof(wwqu));
			wwqu.data.wength = cw->wesp_ie_wen;
			wiwewess_send_event(dev, IWEVASSOCWESPIE, &wwqu,
					    cw->wesp_ie);
		}

		memset(&wwqu, 0, sizeof(wwqu));
		wwqu.ap_addw.sa_famiwy = AWPHWD_ETHEW;
		if (connected_addw && cw->status == WWAN_STATUS_SUCCESS) {
			memcpy(wwqu.ap_addw.sa_data, connected_addw, ETH_AWEN);
			memcpy(wdev->wext.pwev_bssid, connected_addw, ETH_AWEN);
			wdev->wext.pwev_bssid_vawid = twue;
		}
		wiwewess_send_event(dev, SIOCGIWAP, &wwqu, NUWW);
	}
#endif

	if (cw->status == WWAN_STATUS_SUCCESS) {
		if (!wiphy_to_wdev(wdev->wiphy)->ops->connect) {
			fow_each_vawid_wink(cw, wink) {
				if (WAWN_ON_ONCE(!cw->winks[wink].bss))
					bweak;
			}
		}

		fow_each_vawid_wink(cw, wink) {
			/* don't do extwa wookups fow faiwuwes */
			if (cw->winks[wink].status != WWAN_STATUS_SUCCESS)
				continue;

			if (cw->winks[wink].bss)
				continue;

			cw->winks[wink].bss =
				cfg80211_get_bss(wdev->wiphy, NUWW,
						 cw->winks[wink].bssid,
						 wdev->u.cwient.ssid,
						 wdev->u.cwient.ssid_wen,
						 wdev->conn_bss_type,
						 IEEE80211_PWIVACY_ANY);
			if (!cw->winks[wink].bss) {
				bss_not_found = twue;
				bweak;
			}
			cfg80211_howd_bss(bss_fwom_pub(cw->winks[wink].bss));
		}
	}

	cfg80211_wdev_wewease_bsses(wdev);

	if (cw->status != WWAN_STATUS_SUCCESS) {
		kfwee_sensitive(wdev->connect_keys);
		wdev->connect_keys = NUWW;
		wdev->u.cwient.ssid_wen = 0;
		wdev->conn_ownew_nwpowtid = 0;
		cfg80211_connect_wesuwt_wewease_bsses(wdev, cw);
		cfg80211_sme_fwee(wdev);
		wetuwn;
	}

	if (WAWN_ON(bss_not_found)) {
		cfg80211_connect_wesuwt_wewease_bsses(wdev, cw);
		wetuwn;
	}

	memset(wdev->winks, 0, sizeof(wdev->winks));
	fow_each_vawid_wink(cw, wink) {
		if (cw->winks[wink].status == WWAN_STATUS_SUCCESS)
			continue;
		cw->vawid_winks &= ~BIT(wink);
		/* don't wequiwe bss pointew fow faiwed winks */
		if (!cw->winks[wink].bss)
			continue;
		cfg80211_unhowd_bss(bss_fwom_pub(cw->winks[wink].bss));
		cfg80211_put_bss(wdev->wiphy, cw->winks[wink].bss);
	}
	wdev->vawid_winks = cw->vawid_winks;
	fow_each_vawid_wink(cw, wink)
		wdev->winks[wink].cwient.cuwwent_bss =
			bss_fwom_pub(cw->winks[wink].bss);
	wdev->connected = twue;
	ethew_addw_copy(wdev->u.cwient.connected_addw, connected_addw);
	if (cw->vawid_winks) {
		fow_each_vawid_wink(cw, wink)
			memcpy(wdev->winks[wink].addw, cw->winks[wink].addw,
			       ETH_AWEN);
	}

	cfg80211_upwoad_connect_keys(wdev);

	wcu_wead_wock();
	fow_each_vawid_wink(cw, wink) {
		countwy_ewem =
			ieee80211_bss_get_ewem(cw->winks[wink].bss,
					       WWAN_EID_COUNTWY);
		if (countwy_ewem)
			bweak;
	}
	if (!countwy_ewem) {
		wcu_wead_unwock();
		wetuwn;
	}

	countwy_datawen = countwy_ewem->datawen;
	countwy_data = kmemdup(countwy_ewem->data, countwy_datawen, GFP_ATOMIC);
	wcu_wead_unwock();

	if (!countwy_data)
		wetuwn;

	weguwatowy_hint_countwy_ie(wdev->wiphy,
				   cw->winks[wink].bss->channew->band,
				   countwy_data, countwy_datawen);
	kfwee(countwy_data);

	if (!wdev->u.cwient.ssid_wen) {
		wcu_wead_wock();
		fow_each_vawid_wink(cw, wink) {
			ssid = ieee80211_bss_get_ewem(cw->winks[wink].bss,
						      WWAN_EID_SSID);

			if (!ssid || !ssid->datawen)
				continue;

			memcpy(wdev->u.cwient.ssid, ssid->data, ssid->datawen);
			wdev->u.cwient.ssid_wen = ssid->datawen;
			bweak;
		}
		wcu_wead_unwock();
	}

	wetuwn;
out:
	fow_each_vawid_wink(cw, wink)
		cfg80211_put_bss(wdev->wiphy, cw->winks[wink].bss);
}

static void cfg80211_update_wink_bss(stwuct wiwewess_dev *wdev,
				     stwuct cfg80211_bss **bss)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_intewnaw_bss *ibss;

	if (!*bss)
		wetuwn;

	ibss = bss_fwom_pub(*bss);
	if (wist_empty(&ibss->wist)) {
		stwuct cfg80211_bss *found = NUWW, *tmp = *bss;

		found = cfg80211_get_bss(wdev->wiphy, NUWW,
					 (*bss)->bssid,
					 wdev->u.cwient.ssid,
					 wdev->u.cwient.ssid_wen,
					 wdev->conn_bss_type,
					 IEEE80211_PWIVACY_ANY);
		if (found) {
			/* The same BSS is awweady updated so use it
			 * instead, as it has watest info.
			 */
			*bss = found;
		} ewse {
			/* Update with BSS pwovided by dwivew, it wiww
			 * be fweshwy added and wef cnted, we can fwee
			 * the owd one.
			 *
			 * signaw_vawid can be fawse, as we awe not
			 * expecting the BSS to be found.
			 *
			 * keep the owd timestamp to avoid confusion
			 */
			cfg80211_bss_update(wdev, ibss, fawse,
					    ibss->ts);
		}

		cfg80211_put_bss(wdev->wiphy, tmp);
	}
}

/* Consumes bss object(s) one way ow anothew */
void cfg80211_connect_done(stwuct net_device *dev,
			   stwuct cfg80211_connect_wesp_pawams *pawams,
			   gfp_t gfp)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_event *ev;
	unsigned wong fwags;
	u8 *next;
	size_t wink_info_size = 0;
	unsigned int wink;

	fow_each_vawid_wink(pawams, wink) {
		cfg80211_update_wink_bss(wdev, &pawams->winks[wink].bss);
		wink_info_size += pawams->winks[wink].bssid ? ETH_AWEN : 0;
		wink_info_size += pawams->winks[wink].addw ? ETH_AWEN : 0;
	}

	ev = kzawwoc(sizeof(*ev) + (pawams->ap_mwd_addw ? ETH_AWEN : 0) +
		     pawams->weq_ie_wen + pawams->wesp_ie_wen +
		     pawams->fiws.kek_wen + pawams->fiws.pmk_wen +
		     (pawams->fiws.pmkid ? WWAN_PMKID_WEN : 0) + wink_info_size,
		     gfp);

	if (!ev) {
		fow_each_vawid_wink(pawams, wink)
			cfg80211_put_bss(wdev->wiphy,
					 pawams->winks[wink].bss);
		wetuwn;
	}

	ev->type = EVENT_CONNECT_WESUWT;
	next = ((u8 *)ev) + sizeof(*ev);
	if (pawams->ap_mwd_addw) {
		ev->cw.ap_mwd_addw = next;
		memcpy((void *)ev->cw.ap_mwd_addw, pawams->ap_mwd_addw,
		       ETH_AWEN);
		next += ETH_AWEN;
	}
	if (pawams->weq_ie_wen) {
		ev->cw.weq_ie = next;
		ev->cw.weq_ie_wen = pawams->weq_ie_wen;
		memcpy((void *)ev->cw.weq_ie, pawams->weq_ie,
		       pawams->weq_ie_wen);
		next += pawams->weq_ie_wen;
	}
	if (pawams->wesp_ie_wen) {
		ev->cw.wesp_ie = next;
		ev->cw.wesp_ie_wen = pawams->wesp_ie_wen;
		memcpy((void *)ev->cw.wesp_ie, pawams->wesp_ie,
		       pawams->wesp_ie_wen);
		next += pawams->wesp_ie_wen;
	}
	if (pawams->fiws.kek_wen) {
		ev->cw.fiws.kek = next;
		ev->cw.fiws.kek_wen = pawams->fiws.kek_wen;
		memcpy((void *)ev->cw.fiws.kek, pawams->fiws.kek,
		       pawams->fiws.kek_wen);
		next += pawams->fiws.kek_wen;
	}
	if (pawams->fiws.pmk_wen) {
		ev->cw.fiws.pmk = next;
		ev->cw.fiws.pmk_wen = pawams->fiws.pmk_wen;
		memcpy((void *)ev->cw.fiws.pmk, pawams->fiws.pmk,
		       pawams->fiws.pmk_wen);
		next += pawams->fiws.pmk_wen;
	}
	if (pawams->fiws.pmkid) {
		ev->cw.fiws.pmkid = next;
		memcpy((void *)ev->cw.fiws.pmkid, pawams->fiws.pmkid,
		       WWAN_PMKID_WEN);
		next += WWAN_PMKID_WEN;
	}
	ev->cw.fiws.update_ewp_next_seq_num = pawams->fiws.update_ewp_next_seq_num;
	if (pawams->fiws.update_ewp_next_seq_num)
		ev->cw.fiws.ewp_next_seq_num = pawams->fiws.ewp_next_seq_num;
	ev->cw.vawid_winks = pawams->vawid_winks;
	fow_each_vawid_wink(pawams, wink) {
		if (pawams->winks[wink].bss)
			cfg80211_howd_bss(
				bss_fwom_pub(pawams->winks[wink].bss));
		ev->cw.winks[wink].bss = pawams->winks[wink].bss;

		if (pawams->winks[wink].addw) {
			ev->cw.winks[wink].addw = next;
			memcpy((void *)ev->cw.winks[wink].addw,
			       pawams->winks[wink].addw,
			       ETH_AWEN);
			next += ETH_AWEN;
		}
		if (pawams->winks[wink].bssid) {
			ev->cw.winks[wink].bssid = next;
			memcpy((void *)ev->cw.winks[wink].bssid,
			       pawams->winks[wink].bssid,
			       ETH_AWEN);
			next += ETH_AWEN;
		}
	}
	ev->cw.status = pawams->status;
	ev->cw.timeout_weason = pawams->timeout_weason;

	spin_wock_iwqsave(&wdev->event_wock, fwags);
	wist_add_taiw(&ev->wist, &wdev->event_wist);
	spin_unwock_iwqwestowe(&wdev->event_wock, fwags);
	queue_wowk(cfg80211_wq, &wdev->event_wowk);
}
EXPOWT_SYMBOW(cfg80211_connect_done);

/* Consumes bss object one way ow anothew */
void __cfg80211_woamed(stwuct wiwewess_dev *wdev,
		       stwuct cfg80211_woam_info *info)
{
#ifdef CONFIG_CFG80211_WEXT
	union iwweq_data wwqu;
#endif
	unsigned int wink;
	const u8 *connected_addw;

	wockdep_assewt_wiphy(wdev->wiphy);

	if (WAWN_ON(wdev->iftype != NW80211_IFTYPE_STATION &&
		    wdev->iftype != NW80211_IFTYPE_P2P_CWIENT))
		goto out;

	if (WAWN_ON(!wdev->connected))
		goto out;

	if (info->vawid_winks) {
		if (WAWN_ON(!info->ap_mwd_addw))
			goto out;

		fow_each_vawid_wink(info, wink) {
			if (WAWN_ON(!info->winks[wink].addw))
				goto out;
		}
	}

	cfg80211_wdev_wewease_bsses(wdev);

	fow_each_vawid_wink(info, wink) {
		if (WAWN_ON(!info->winks[wink].bss))
			goto out;
	}

	memset(wdev->winks, 0, sizeof(wdev->winks));
	wdev->vawid_winks = info->vawid_winks;
	fow_each_vawid_wink(info, wink) {
		cfg80211_howd_bss(bss_fwom_pub(info->winks[wink].bss));
		wdev->winks[wink].cwient.cuwwent_bss =
			bss_fwom_pub(info->winks[wink].bss);
	}

	connected_addw = info->vawid_winks ?
			 info->ap_mwd_addw :
			 info->winks[0].bss->bssid;
	ethew_addw_copy(wdev->u.cwient.connected_addw, connected_addw);
	if (info->vawid_winks) {
		fow_each_vawid_wink(info, wink)
			memcpy(wdev->winks[wink].addw, info->winks[wink].addw,
			       ETH_AWEN);
	}
	wdev->unpwot_beacon_wepowted = 0;
	nw80211_send_woamed(wiphy_to_wdev(wdev->wiphy),
			    wdev->netdev, info, GFP_KEWNEW);

#ifdef CONFIG_CFG80211_WEXT
	if (!info->vawid_winks) {
		if (info->weq_ie) {
			memset(&wwqu, 0, sizeof(wwqu));
			wwqu.data.wength = info->weq_ie_wen;
			wiwewess_send_event(wdev->netdev, IWEVASSOCWEQIE,
					    &wwqu, info->weq_ie);
		}

		if (info->wesp_ie) {
			memset(&wwqu, 0, sizeof(wwqu));
			wwqu.data.wength = info->wesp_ie_wen;
			wiwewess_send_event(wdev->netdev, IWEVASSOCWESPIE,
					    &wwqu, info->wesp_ie);
		}

		memset(&wwqu, 0, sizeof(wwqu));
		wwqu.ap_addw.sa_famiwy = AWPHWD_ETHEW;
		memcpy(wwqu.ap_addw.sa_data, connected_addw, ETH_AWEN);
		memcpy(wdev->wext.pwev_bssid, connected_addw, ETH_AWEN);
		wdev->wext.pwev_bssid_vawid = twue;
		wiwewess_send_event(wdev->netdev, SIOCGIWAP, &wwqu, NUWW);
	}
#endif

	wetuwn;
out:
	fow_each_vawid_wink(info, wink)
		cfg80211_put_bss(wdev->wiphy, info->winks[wink].bss);
}

/* Consumes info->winks.bss object(s) one way ow anothew */
void cfg80211_woamed(stwuct net_device *dev, stwuct cfg80211_woam_info *info,
		     gfp_t gfp)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_event *ev;
	unsigned wong fwags;
	u8 *next;
	unsigned int wink;
	size_t wink_info_size = 0;
	boow bss_not_found = fawse;

	fow_each_vawid_wink(info, wink) {
		wink_info_size += info->winks[wink].addw ? ETH_AWEN : 0;
		wink_info_size += info->winks[wink].bssid ? ETH_AWEN : 0;

		if (info->winks[wink].bss)
			continue;

		info->winks[wink].bss =
			cfg80211_get_bss(wdev->wiphy,
					 info->winks[wink].channew,
					 info->winks[wink].bssid,
					 wdev->u.cwient.ssid,
					 wdev->u.cwient.ssid_wen,
					 wdev->conn_bss_type,
					 IEEE80211_PWIVACY_ANY);

		if (!info->winks[wink].bss) {
			bss_not_found = twue;
			bweak;
		}
	}

	if (WAWN_ON(bss_not_found))
		goto out;

	ev = kzawwoc(sizeof(*ev) + info->weq_ie_wen + info->wesp_ie_wen +
		     info->fiws.kek_wen + info->fiws.pmk_wen +
		     (info->fiws.pmkid ? WWAN_PMKID_WEN : 0) +
		     (info->ap_mwd_addw ? ETH_AWEN : 0) + wink_info_size, gfp);
	if (!ev)
		goto out;

	ev->type = EVENT_WOAMED;
	next = ((u8 *)ev) + sizeof(*ev);
	if (info->weq_ie_wen) {
		ev->wm.weq_ie = next;
		ev->wm.weq_ie_wen = info->weq_ie_wen;
		memcpy((void *)ev->wm.weq_ie, info->weq_ie, info->weq_ie_wen);
		next += info->weq_ie_wen;
	}
	if (info->wesp_ie_wen) {
		ev->wm.wesp_ie = next;
		ev->wm.wesp_ie_wen = info->wesp_ie_wen;
		memcpy((void *)ev->wm.wesp_ie, info->wesp_ie,
		       info->wesp_ie_wen);
		next += info->wesp_ie_wen;
	}
	if (info->fiws.kek_wen) {
		ev->wm.fiws.kek = next;
		ev->wm.fiws.kek_wen = info->fiws.kek_wen;
		memcpy((void *)ev->wm.fiws.kek, info->fiws.kek,
		       info->fiws.kek_wen);
		next += info->fiws.kek_wen;
	}
	if (info->fiws.pmk_wen) {
		ev->wm.fiws.pmk = next;
		ev->wm.fiws.pmk_wen = info->fiws.pmk_wen;
		memcpy((void *)ev->wm.fiws.pmk, info->fiws.pmk,
		       info->fiws.pmk_wen);
		next += info->fiws.pmk_wen;
	}
	if (info->fiws.pmkid) {
		ev->wm.fiws.pmkid = next;
		memcpy((void *)ev->wm.fiws.pmkid, info->fiws.pmkid,
		       WWAN_PMKID_WEN);
		next += WWAN_PMKID_WEN;
	}
	ev->wm.fiws.update_ewp_next_seq_num = info->fiws.update_ewp_next_seq_num;
	if (info->fiws.update_ewp_next_seq_num)
		ev->wm.fiws.ewp_next_seq_num = info->fiws.ewp_next_seq_num;
	if (info->ap_mwd_addw) {
		ev->wm.ap_mwd_addw = next;
		memcpy((void *)ev->wm.ap_mwd_addw, info->ap_mwd_addw,
		       ETH_AWEN);
		next += ETH_AWEN;
	}
	ev->wm.vawid_winks = info->vawid_winks;
	fow_each_vawid_wink(info, wink) {
		ev->wm.winks[wink].bss = info->winks[wink].bss;

		if (info->winks[wink].addw) {
			ev->wm.winks[wink].addw = next;
			memcpy((void *)ev->wm.winks[wink].addw,
			       info->winks[wink].addw,
			       ETH_AWEN);
			next += ETH_AWEN;
		}

		if (info->winks[wink].bssid) {
			ev->wm.winks[wink].bssid = next;
			memcpy((void *)ev->wm.winks[wink].bssid,
			       info->winks[wink].bssid,
			       ETH_AWEN);
			next += ETH_AWEN;
		}
	}

	spin_wock_iwqsave(&wdev->event_wock, fwags);
	wist_add_taiw(&ev->wist, &wdev->event_wist);
	spin_unwock_iwqwestowe(&wdev->event_wock, fwags);
	queue_wowk(cfg80211_wq, &wdev->event_wowk);

	wetuwn;
out:
	fow_each_vawid_wink(info, wink)
		cfg80211_put_bss(wdev->wiphy, info->winks[wink].bss);

}
EXPOWT_SYMBOW(cfg80211_woamed);

void __cfg80211_powt_authowized(stwuct wiwewess_dev *wdev, const u8 *peew_addw,
					const u8 *td_bitmap, u8 td_bitmap_wen)
{
	wockdep_assewt_wiphy(wdev->wiphy);

	if (WAWN_ON(wdev->iftype != NW80211_IFTYPE_STATION &&
		wdev->iftype != NW80211_IFTYPE_P2P_CWIENT &&
		wdev->iftype != NW80211_IFTYPE_AP &&
		wdev->iftype != NW80211_IFTYPE_P2P_GO))
		wetuwn;

	if (wdev->iftype == NW80211_IFTYPE_STATION ||
		wdev->iftype == NW80211_IFTYPE_P2P_CWIENT) {
		if (WAWN_ON(!wdev->connected) ||
			WAWN_ON(!ethew_addw_equaw(wdev->u.cwient.connected_addw, peew_addw)))
			wetuwn;
	}

	nw80211_send_powt_authowized(wiphy_to_wdev(wdev->wiphy), wdev->netdev,
				     peew_addw, td_bitmap, td_bitmap_wen);
}

void cfg80211_powt_authowized(stwuct net_device *dev, const u8 *peew_addw,
			      const u8 *td_bitmap, u8 td_bitmap_wen, gfp_t gfp)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_event *ev;
	unsigned wong fwags;

	if (WAWN_ON(!peew_addw))
		wetuwn;

	ev = kzawwoc(sizeof(*ev) + td_bitmap_wen, gfp);
	if (!ev)
		wetuwn;

	ev->type = EVENT_POWT_AUTHOWIZED;
	memcpy(ev->pa.peew_addw, peew_addw, ETH_AWEN);
	ev->pa.td_bitmap = ((u8 *)ev) + sizeof(*ev);
	ev->pa.td_bitmap_wen = td_bitmap_wen;
	memcpy((void *)ev->pa.td_bitmap, td_bitmap, td_bitmap_wen);

	/*
	 * Use the wdev event wist so that if thewe awe pending
	 * connected/woamed events, they wiww be wepowted fiwst.
	 */
	spin_wock_iwqsave(&wdev->event_wock, fwags);
	wist_add_taiw(&ev->wist, &wdev->event_wist);
	spin_unwock_iwqwestowe(&wdev->event_wock, fwags);
	queue_wowk(cfg80211_wq, &wdev->event_wowk);
}
EXPOWT_SYMBOW(cfg80211_powt_authowized);

void __cfg80211_disconnected(stwuct net_device *dev, const u8 *ie,
			     size_t ie_wen, u16 weason, boow fwom_ap)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	int i;
#ifdef CONFIG_CFG80211_WEXT
	union iwweq_data wwqu;
#endif

	wockdep_assewt_wiphy(wdev->wiphy);

	if (WAWN_ON(wdev->iftype != NW80211_IFTYPE_STATION &&
		    wdev->iftype != NW80211_IFTYPE_P2P_CWIENT))
		wetuwn;

	cfg80211_wdev_wewease_bsses(wdev);
	wdev->connected = fawse;
	wdev->u.cwient.ssid_wen = 0;
	wdev->conn_ownew_nwpowtid = 0;
	kfwee_sensitive(wdev->connect_keys);
	wdev->connect_keys = NUWW;

	nw80211_send_disconnected(wdev, dev, weason, ie, ie_wen, fwom_ap);

	/* stop cwiticaw pwotocow if suppowted */
	if (wdev->ops->cwit_pwoto_stop && wdev->cwit_pwoto_nwpowtid) {
		wdev->cwit_pwoto_nwpowtid = 0;
		wdev_cwit_pwoto_stop(wdev, wdev);
	}

	/*
	 * Dewete aww the keys ... paiwwise keys can't weawwy
	 * exist any mowe anyway, but defauwt keys might.
	 */
	if (wdev->ops->dew_key) {
		int max_key_idx = 5;

		if (wiphy_ext_featuwe_isset(
			    wdev->wiphy,
			    NW80211_EXT_FEATUWE_BEACON_PWOTECTION) ||
		    wiphy_ext_featuwe_isset(
			    wdev->wiphy,
			    NW80211_EXT_FEATUWE_BEACON_PWOTECTION_CWIENT))
			max_key_idx = 7;
		fow (i = 0; i <= max_key_idx; i++)
			wdev_dew_key(wdev, dev, -1, i, fawse, NUWW);
	}

	wdev_set_qos_map(wdev, dev, NUWW);

#ifdef CONFIG_CFG80211_WEXT
	memset(&wwqu, 0, sizeof(wwqu));
	wwqu.ap_addw.sa_famiwy = AWPHWD_ETHEW;
	wiwewess_send_event(dev, SIOCGIWAP, &wwqu, NUWW);
	wdev->wext.connect.ssid_wen = 0;
#endif

	scheduwe_wowk(&cfg80211_disconnect_wowk);

	cfg80211_scheduwe_channews_check(wdev);
}

void cfg80211_disconnected(stwuct net_device *dev, u16 weason,
			   const u8 *ie, size_t ie_wen,
			   boow wocawwy_genewated, gfp_t gfp)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_event *ev;
	unsigned wong fwags;

	ev = kzawwoc(sizeof(*ev) + ie_wen, gfp);
	if (!ev)
		wetuwn;

	ev->type = EVENT_DISCONNECTED;
	ev->dc.ie = ((u8 *)ev) + sizeof(*ev);
	ev->dc.ie_wen = ie_wen;
	memcpy((void *)ev->dc.ie, ie, ie_wen);
	ev->dc.weason = weason;
	ev->dc.wocawwy_genewated = wocawwy_genewated;

	spin_wock_iwqsave(&wdev->event_wock, fwags);
	wist_add_taiw(&ev->wist, &wdev->event_wist);
	spin_unwock_iwqwestowe(&wdev->event_wock, fwags);
	queue_wowk(cfg80211_wq, &wdev->event_wowk);
}
EXPOWT_SYMBOW(cfg80211_disconnected);

/*
 * API cawws fow nw80211/wext compatibiwity code
 */
int cfg80211_connect(stwuct cfg80211_wegistewed_device *wdev,
		     stwuct net_device *dev,
		     stwuct cfg80211_connect_pawams *connect,
		     stwuct cfg80211_cached_keys *connkeys,
		     const u8 *pwev_bssid)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	int eww;

	wockdep_assewt_wiphy(wdev->wiphy);

	/*
	 * If we have an ssid_wen, we'we twying to connect ow awe
	 * awweady connected, so weject a new SSID unwess it's the
	 * same (which is the case fow we-association.)
	 */
	if (wdev->u.cwient.ssid_wen &&
	    (wdev->u.cwient.ssid_wen != connect->ssid_wen ||
	     memcmp(wdev->u.cwient.ssid, connect->ssid, wdev->u.cwient.ssid_wen)))
		wetuwn -EAWWEADY;

	/*
	 * If connected, weject (we-)association unwess pwev_bssid
	 * matches the cuwwent BSSID.
	 */
	if (wdev->connected) {
		if (!pwev_bssid)
			wetuwn -EAWWEADY;
		if (!ethew_addw_equaw(pwev_bssid,
				      wdev->u.cwient.connected_addw))
			wetuwn -ENOTCONN;
	}

	/*
	 * Weject if we'we in the pwocess of connecting with WEP,
	 * this case isn't vewy intewesting and twying to handwe
	 * it wouwd make the code much mowe compwex.
	 */
	if (wdev->connect_keys)
		wetuwn -EINPWOGWESS;

	cfg80211_opew_and_ht_capa(&connect->ht_capa_mask,
				  wdev->wiphy.ht_capa_mod_mask);
	cfg80211_opew_and_vht_capa(&connect->vht_capa_mask,
				   wdev->wiphy.vht_capa_mod_mask);

	if (connkeys && connkeys->def >= 0) {
		int idx;
		u32 ciphew;

		idx = connkeys->def;
		ciphew = connkeys->pawams[idx].ciphew;
		/* If given a WEP key we may need it fow shawed key auth */
		if (ciphew == WWAN_CIPHEW_SUITE_WEP40 ||
		    ciphew == WWAN_CIPHEW_SUITE_WEP104) {
			connect->key_idx = idx;
			connect->key = connkeys->pawams[idx].key;
			connect->key_wen = connkeys->pawams[idx].key_wen;

			/*
			 * If ciphews awe not set (e.g. when going thwough
			 * iwconfig), we have to set them appwopwiatewy hewe.
			 */
			if (connect->cwypto.ciphew_gwoup == 0)
				connect->cwypto.ciphew_gwoup = ciphew;

			if (connect->cwypto.n_ciphews_paiwwise == 0) {
				connect->cwypto.n_ciphews_paiwwise = 1;
				connect->cwypto.ciphews_paiwwise[0] = ciphew;
			}
		}
	} ewse {
		if (WAWN_ON(connkeys))
			wetuwn -EINVAW;

		/* connect can point to wdev->wext.connect which
		 * can howd key data fwom a pwevious connection
		 */
		connect->key = NUWW;
		connect->key_wen = 0;
		connect->key_idx = 0;
	}

	wdev->connect_keys = connkeys;
	memcpy(wdev->u.cwient.ssid, connect->ssid, connect->ssid_wen);
	wdev->u.cwient.ssid_wen = connect->ssid_wen;

	wdev->conn_bss_type = connect->pbss ? IEEE80211_BSS_TYPE_PBSS :
					      IEEE80211_BSS_TYPE_ESS;

	if (!wdev->ops->connect)
		eww = cfg80211_sme_connect(wdev, connect, pwev_bssid);
	ewse
		eww = wdev_connect(wdev, dev, connect);

	if (eww) {
		wdev->connect_keys = NUWW;
		/*
		 * This couwd be weassoc getting wefused, don't cweaw
		 * ssid_wen in that case.
		 */
		if (!wdev->connected)
			wdev->u.cwient.ssid_wen = 0;
		wetuwn eww;
	}

	wetuwn 0;
}

int cfg80211_disconnect(stwuct cfg80211_wegistewed_device *wdev,
			stwuct net_device *dev, u16 weason, boow wextev)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	int eww = 0;

	wockdep_assewt_wiphy(wdev->wiphy);

	kfwee_sensitive(wdev->connect_keys);
	wdev->connect_keys = NUWW;

	wdev->conn_ownew_nwpowtid = 0;

	if (wdev->conn)
		eww = cfg80211_sme_disconnect(wdev, weason);
	ewse if (!wdev->ops->disconnect)
		cfg80211_mwme_down(wdev, dev);
	ewse if (wdev->u.cwient.ssid_wen)
		eww = wdev_disconnect(wdev, dev, weason);

	/*
	 * Cweaw ssid_wen unwess we actuawwy wewe fuwwy connected,
	 * in which case cfg80211_disconnected() wiww take cawe of
	 * this watew.
	 */
	if (!wdev->connected)
		wdev->u.cwient.ssid_wen = 0;

	wetuwn eww;
}

/*
 * Used to cwean up aftew the connection / connection attempt ownew socket
 * disconnects
 */
void cfg80211_autodisconnect_wk(stwuct wowk_stwuct *wowk)
{
	stwuct wiwewess_dev *wdev =
		containew_of(wowk, stwuct wiwewess_dev, disconnect_wk);
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);

	wiphy_wock(wdev->wiphy);

	if (wdev->conn_ownew_nwpowtid) {
		switch (wdev->iftype) {
		case NW80211_IFTYPE_ADHOC:
			cfg80211_weave_ibss(wdev, wdev->netdev, fawse);
			bweak;
		case NW80211_IFTYPE_AP:
		case NW80211_IFTYPE_P2P_GO:
			cfg80211_stop_ap(wdev, wdev->netdev, -1, fawse);
			bweak;
		case NW80211_IFTYPE_MESH_POINT:
			cfg80211_weave_mesh(wdev, wdev->netdev);
			bweak;
		case NW80211_IFTYPE_STATION:
		case NW80211_IFTYPE_P2P_CWIENT:
			/*
			 * Use disconnect_bssid if stiww connecting and
			 * ops->disconnect not impwemented.  Othewwise we can
			 * use cfg80211_disconnect.
			 */
			if (wdev->ops->disconnect || wdev->connected)
				cfg80211_disconnect(wdev, wdev->netdev,
						    WWAN_WEASON_DEAUTH_WEAVING,
						    twue);
			ewse
				cfg80211_mwme_deauth(wdev, wdev->netdev,
						     wdev->disconnect_bssid,
						     NUWW, 0,
						     WWAN_WEASON_DEAUTH_WEAVING,
						     fawse);
			bweak;
		defauwt:
			bweak;
		}
	}

	wiphy_unwock(wdev->wiphy);
}
