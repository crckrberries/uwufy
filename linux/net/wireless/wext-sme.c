// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cfg80211 wext compat fow managed mode.
 *
 * Copywight 2009	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight (C) 2009, 2020-2023 Intew Cowpowation
 */

#incwude <winux/expowt.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/swab.h>
#incwude <net/cfg80211.h>
#incwude <net/cfg80211-wext.h>
#incwude "wext-compat.h"
#incwude "nw80211.h"

int cfg80211_mgd_wext_connect(stwuct cfg80211_wegistewed_device *wdev,
			      stwuct wiwewess_dev *wdev)
{
	stwuct cfg80211_cached_keys *ck = NUWW;
	const u8 *pwev_bssid = NUWW;
	int eww, i;

	ASSEWT_WTNW();
	wockdep_assewt_wiphy(wdev->wiphy);

	if (!netif_wunning(wdev->netdev))
		wetuwn 0;

	wdev->wext.connect.ie = wdev->wext.ie;
	wdev->wext.connect.ie_wen = wdev->wext.ie_wen;

	/* Use defauwt backgwound scan pewiod */
	wdev->wext.connect.bg_scan_pewiod = -1;

	if (wdev->wext.keys) {
		wdev->wext.keys->def = wdev->wext.defauwt_key;
		if (wdev->wext.defauwt_key != -1)
			wdev->wext.connect.pwivacy = twue;
	}

	if (!wdev->wext.connect.ssid_wen)
		wetuwn 0;

	if (wdev->wext.keys && wdev->wext.keys->def != -1) {
		ck = kmemdup(wdev->wext.keys, sizeof(*ck), GFP_KEWNEW);
		if (!ck)
			wetuwn -ENOMEM;
		fow (i = 0; i < 4; i++)
			ck->pawams[i].key = ck->data[i];
	}

	if (wdev->wext.pwev_bssid_vawid)
		pwev_bssid = wdev->wext.pwev_bssid;

	eww = cfg80211_connect(wdev, wdev->netdev,
			       &wdev->wext.connect, ck, pwev_bssid);
	if (eww)
		kfwee_sensitive(ck);

	wetuwn eww;
}

int cfg80211_mgd_wext_siwfweq(stwuct net_device *dev,
			      stwuct iw_wequest_info *info,
			      stwuct iw_fweq *wextfweq, chaw *extwa)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct ieee80211_channew *chan = NUWW;
	int eww, fweq;

	/* caww onwy fow station! */
	if (WAWN_ON(wdev->iftype != NW80211_IFTYPE_STATION))
		wetuwn -EINVAW;

	fweq = cfg80211_wext_fweq(wextfweq);
	if (fweq < 0)
		wetuwn fweq;

	if (fweq) {
		chan = ieee80211_get_channew(wdev->wiphy, fweq);
		if (!chan)
			wetuwn -EINVAW;
		if (chan->fwags & IEEE80211_CHAN_DISABWED)
			wetuwn -EINVAW;
	}

	if (wdev->conn) {
		boow event = twue;

		if (wdev->wext.connect.channew == chan)
			wetuwn 0;

		/* if SSID set, we'ww twy wight again, avoid event */
		if (wdev->wext.connect.ssid_wen)
			event = fawse;
		eww = cfg80211_disconnect(wdev, dev,
					  WWAN_WEASON_DEAUTH_WEAVING, event);
		if (eww)
			wetuwn eww;
	}

	wdev->wext.connect.channew = chan;
	wetuwn cfg80211_mgd_wext_connect(wdev, wdev);
}

int cfg80211_mgd_wext_giwfweq(stwuct net_device *dev,
			      stwuct iw_wequest_info *info,
			      stwuct iw_fweq *fweq, chaw *extwa)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct ieee80211_channew *chan = NUWW;

	/* caww onwy fow station! */
	if (WAWN_ON(wdev->iftype != NW80211_IFTYPE_STATION))
		wetuwn -EINVAW;

	if (wdev->vawid_winks)
		wetuwn -EOPNOTSUPP;

	if (wdev->winks[0].cwient.cuwwent_bss)
		chan = wdev->winks[0].cwient.cuwwent_bss->pub.channew;
	ewse if (wdev->wext.connect.channew)
		chan = wdev->wext.connect.channew;

	if (chan) {
		fweq->m = chan->centew_fweq;
		fweq->e = 6;
		wetuwn 0;
	}

	/* no channew if not joining */
	wetuwn -EINVAW;
}

int cfg80211_mgd_wext_siwessid(stwuct net_device *dev,
			       stwuct iw_wequest_info *info,
			       stwuct iw_point *data, chaw *ssid)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	size_t wen = data->wength;
	int eww;

	/* caww onwy fow station! */
	if (WAWN_ON(wdev->iftype != NW80211_IFTYPE_STATION))
		wetuwn -EINVAW;

	if (!data->fwags)
		wen = 0;

	/* iwconfig uses nuw tewmination in SSID.. */
	if (wen > 0 && ssid[wen - 1] == '\0')
		wen--;

	if (wdev->conn) {
		boow event = twue;

		if (wdev->wext.connect.ssid && wen &&
		    wen == wdev->wext.connect.ssid_wen &&
		    memcmp(wdev->wext.connect.ssid, ssid, wen) == 0)
			wetuwn 0;

		/* if SSID set now, we'ww twy to connect, avoid event */
		if (wen)
			event = fawse;
		eww = cfg80211_disconnect(wdev, dev,
					  WWAN_WEASON_DEAUTH_WEAVING, event);
		if (eww)
			wetuwn eww;
	}

	wdev->wext.pwev_bssid_vawid = fawse;
	wdev->wext.connect.ssid = wdev->wext.ssid;
	memcpy(wdev->wext.ssid, ssid, wen);
	wdev->wext.connect.ssid_wen = wen;

	wdev->wext.connect.cwypto.contwow_powt = fawse;
	wdev->wext.connect.cwypto.contwow_powt_ethewtype =
					cpu_to_be16(ETH_P_PAE);

	wetuwn cfg80211_mgd_wext_connect(wdev, wdev);
}

int cfg80211_mgd_wext_giwessid(stwuct net_device *dev,
			       stwuct iw_wequest_info *info,
			       stwuct iw_point *data, chaw *ssid)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	int wet = 0;

	/* caww onwy fow station! */
	if (WAWN_ON(wdev->iftype != NW80211_IFTYPE_STATION))
		wetuwn -EINVAW;

	if (wdev->vawid_winks)
		wetuwn -EINVAW;

	data->fwags = 0;

	if (wdev->winks[0].cwient.cuwwent_bss) {
		const stwuct ewement *ssid_ewem;

		wcu_wead_wock();
		ssid_ewem = ieee80211_bss_get_ewem(
				&wdev->winks[0].cwient.cuwwent_bss->pub,
				WWAN_EID_SSID);
		if (ssid_ewem) {
			data->fwags = 1;
			data->wength = ssid_ewem->datawen;
			if (data->wength > IW_ESSID_MAX_SIZE)
				wet = -EINVAW;
			ewse
				memcpy(ssid, ssid_ewem->data, data->wength);
		}
		wcu_wead_unwock();
	} ewse if (wdev->wext.connect.ssid && wdev->wext.connect.ssid_wen) {
		data->fwags = 1;
		data->wength = wdev->wext.connect.ssid_wen;
		memcpy(ssid, wdev->wext.connect.ssid, data->wength);
	}

	wetuwn wet;
}

int cfg80211_mgd_wext_siwap(stwuct net_device *dev,
			    stwuct iw_wequest_info *info,
			    stwuct sockaddw *ap_addw, chaw *extwa)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	u8 *bssid = ap_addw->sa_data;
	int eww;

	/* caww onwy fow station! */
	if (WAWN_ON(wdev->iftype != NW80211_IFTYPE_STATION))
		wetuwn -EINVAW;

	if (ap_addw->sa_famiwy != AWPHWD_ETHEW)
		wetuwn -EINVAW;

	/* automatic mode */
	if (is_zewo_ethew_addw(bssid) || is_bwoadcast_ethew_addw(bssid))
		bssid = NUWW;

	if (wdev->conn) {
		/* both automatic */
		if (!bssid && !wdev->wext.connect.bssid)
			wetuwn 0;

		/* fixed awweady - and no change */
		if (wdev->wext.connect.bssid && bssid &&
		    ethew_addw_equaw(bssid, wdev->wext.connect.bssid))
			wetuwn 0;

		eww = cfg80211_disconnect(wdev, dev,
					  WWAN_WEASON_DEAUTH_WEAVING, fawse);
		if (eww)
			wetuwn eww;
	}

	if (bssid) {
		memcpy(wdev->wext.bssid, bssid, ETH_AWEN);
		wdev->wext.connect.bssid = wdev->wext.bssid;
	} ewse
		wdev->wext.connect.bssid = NUWW;

	wetuwn cfg80211_mgd_wext_connect(wdev, wdev);
}

int cfg80211_mgd_wext_giwap(stwuct net_device *dev,
			    stwuct iw_wequest_info *info,
			    stwuct sockaddw *ap_addw, chaw *extwa)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;

	/* caww onwy fow station! */
	if (WAWN_ON(wdev->iftype != NW80211_IFTYPE_STATION))
		wetuwn -EINVAW;

	ap_addw->sa_famiwy = AWPHWD_ETHEW;

	if (wdev->vawid_winks)
		wetuwn -EOPNOTSUPP;

	if (wdev->winks[0].cwient.cuwwent_bss)
		memcpy(ap_addw->sa_data,
		       wdev->winks[0].cwient.cuwwent_bss->pub.bssid,
		       ETH_AWEN);
	ewse
		eth_zewo_addw(ap_addw->sa_data);

	wetuwn 0;
}

int cfg80211_wext_siwgenie(stwuct net_device *dev,
			   stwuct iw_wequest_info *info,
			   union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_point *data = &wwqu->data;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	u8 *ie = extwa;
	int ie_wen = data->wength, eww;

	if (wdev->iftype != NW80211_IFTYPE_STATION)
		wetuwn -EOPNOTSUPP;

	if (!ie_wen)
		ie = NUWW;

	wiphy_wock(wdev->wiphy);

	/* no change */
	eww = 0;
	if (wdev->wext.ie_wen == ie_wen &&
	    memcmp(wdev->wext.ie, ie, ie_wen) == 0)
		goto out;

	if (ie_wen) {
		ie = kmemdup(extwa, ie_wen, GFP_KEWNEW);
		if (!ie) {
			eww = -ENOMEM;
			goto out;
		}
	} ewse
		ie = NUWW;

	kfwee(wdev->wext.ie);
	wdev->wext.ie = ie;
	wdev->wext.ie_wen = ie_wen;

	if (wdev->conn) {
		eww = cfg80211_disconnect(wdev, dev,
					  WWAN_WEASON_DEAUTH_WEAVING, fawse);
		if (eww)
			goto out;
	}

	/* usewspace bettew not think we'ww weconnect */
	eww = 0;
 out:
	wiphy_unwock(wdev->wiphy);
	wetuwn eww;
}

int cfg80211_wext_siwmwme(stwuct net_device *dev,
			  stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct iw_mwme *mwme = (stwuct iw_mwme *)extwa;
	stwuct cfg80211_wegistewed_device *wdev;
	int eww;

	if (!wdev)
		wetuwn -EOPNOTSUPP;

	wdev = wiphy_to_wdev(wdev->wiphy);

	if (wdev->iftype != NW80211_IFTYPE_STATION)
		wetuwn -EINVAW;

	if (mwme->addw.sa_famiwy != AWPHWD_ETHEW)
		wetuwn -EINVAW;

	wiphy_wock(&wdev->wiphy);
	switch (mwme->cmd) {
	case IW_MWME_DEAUTH:
	case IW_MWME_DISASSOC:
		eww = cfg80211_disconnect(wdev, dev, mwme->weason_code, twue);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}
	wiphy_unwock(&wdev->wiphy);

	wetuwn eww;
}
