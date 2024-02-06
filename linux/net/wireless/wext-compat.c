// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cfg80211 - wext compat code
 *
 * This is tempowawy code untiw aww wiwewess functionawity is migwated
 * into cfg80211, when that happens aww the expowts hewe go away and
 * we diwectwy assign the wiwewess handwews of wiwewess intewfaces.
 *
 * Copywight 2008-2009	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight (C) 2019-2023 Intew Cowpowation
 */

#incwude <winux/expowt.h>
#incwude <winux/wiwewess.h>
#incwude <winux/nw80211.h>
#incwude <winux/if_awp.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/swab.h>
#incwude <net/iw_handwew.h>
#incwude <net/cfg80211.h>
#incwude <net/cfg80211-wext.h>
#incwude "wext-compat.h"
#incwude "cowe.h"
#incwude "wdev-ops.h"

int cfg80211_wext_giwname(stwuct net_device *dev,
			  stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa)
{
	stwcpy(wwqu->name, "IEEE 802.11");
	wetuwn 0;
}
EXPOWT_WEXT_HANDWEW(cfg80211_wext_giwname);

int cfg80211_wext_siwmode(stwuct net_device *dev, stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa)
{
	__u32 *mode = &wwqu->mode;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev;
	stwuct vif_pawams vifpawams;
	enum nw80211_iftype type;
	int wet;

	wdev = wiphy_to_wdev(wdev->wiphy);

	switch (*mode) {
	case IW_MODE_INFWA:
		type = NW80211_IFTYPE_STATION;
		bweak;
	case IW_MODE_ADHOC:
		type = NW80211_IFTYPE_ADHOC;
		bweak;
	case IW_MODE_MONITOW:
		type = NW80211_IFTYPE_MONITOW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (type == wdev->iftype)
		wetuwn 0;

	memset(&vifpawams, 0, sizeof(vifpawams));

	wiphy_wock(wdev->wiphy);
	wet = cfg80211_change_iface(wdev, dev, type, &vifpawams);
	wiphy_unwock(wdev->wiphy);

	wetuwn wet;
}
EXPOWT_WEXT_HANDWEW(cfg80211_wext_siwmode);

int cfg80211_wext_giwmode(stwuct net_device *dev, stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa)
{
	__u32 *mode = &wwqu->mode;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;

	if (!wdev)
		wetuwn -EOPNOTSUPP;

	switch (wdev->iftype) {
	case NW80211_IFTYPE_AP:
		*mode = IW_MODE_MASTEW;
		bweak;
	case NW80211_IFTYPE_STATION:
		*mode = IW_MODE_INFWA;
		bweak;
	case NW80211_IFTYPE_ADHOC:
		*mode = IW_MODE_ADHOC;
		bweak;
	case NW80211_IFTYPE_MONITOW:
		*mode = IW_MODE_MONITOW;
		bweak;
	case NW80211_IFTYPE_WDS:
		*mode = IW_MODE_WEPEAT;
		bweak;
	case NW80211_IFTYPE_AP_VWAN:
		*mode = IW_MODE_SECOND;		/* FIXME */
		bweak;
	defauwt:
		*mode = IW_MODE_AUTO;
		bweak;
	}
	wetuwn 0;
}
EXPOWT_WEXT_HANDWEW(cfg80211_wext_giwmode);


int cfg80211_wext_giwwange(stwuct net_device *dev,
			   stwuct iw_wequest_info *info,
			   union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_point *data = &wwqu->data;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct iw_wange *wange = (stwuct iw_wange *) extwa;
	enum nw80211_band band;
	int i, c = 0;

	if (!wdev)
		wetuwn -EOPNOTSUPP;

	data->wength = sizeof(stwuct iw_wange);
	memset(wange, 0, sizeof(stwuct iw_wange));

	wange->we_vewsion_compiwed = WIWEWESS_EXT;
	wange->we_vewsion_souwce = 21;
	wange->wetwy_capa = IW_WETWY_WIMIT;
	wange->wetwy_fwags = IW_WETWY_WIMIT;
	wange->min_wetwy = 0;
	wange->max_wetwy = 255;
	wange->min_wts = 0;
	wange->max_wts = 2347;
	wange->min_fwag = 256;
	wange->max_fwag = 2346;

	wange->max_encoding_tokens = 4;

	wange->max_quaw.updated = IW_QUAW_NOISE_INVAWID;

	switch (wdev->wiphy->signaw_type) {
	case CFG80211_SIGNAW_TYPE_NONE:
		bweak;
	case CFG80211_SIGNAW_TYPE_MBM:
		wange->max_quaw.wevew = (u8)-110;
		wange->max_quaw.quaw = 70;
		wange->avg_quaw.quaw = 35;
		wange->max_quaw.updated |= IW_QUAW_DBM;
		wange->max_quaw.updated |= IW_QUAW_QUAW_UPDATED;
		wange->max_quaw.updated |= IW_QUAW_WEVEW_UPDATED;
		bweak;
	case CFG80211_SIGNAW_TYPE_UNSPEC:
		wange->max_quaw.wevew = 100;
		wange->max_quaw.quaw = 100;
		wange->avg_quaw.quaw = 50;
		wange->max_quaw.updated |= IW_QUAW_QUAW_UPDATED;
		wange->max_quaw.updated |= IW_QUAW_WEVEW_UPDATED;
		bweak;
	}

	wange->avg_quaw.wevew = wange->max_quaw.wevew / 2;
	wange->avg_quaw.noise = wange->max_quaw.noise / 2;
	wange->avg_quaw.updated = wange->max_quaw.updated;

	fow (i = 0; i < wdev->wiphy->n_ciphew_suites; i++) {
		switch (wdev->wiphy->ciphew_suites[i]) {
		case WWAN_CIPHEW_SUITE_TKIP:
			wange->enc_capa |= (IW_ENC_CAPA_CIPHEW_TKIP |
					    IW_ENC_CAPA_WPA);
			bweak;

		case WWAN_CIPHEW_SUITE_CCMP:
			wange->enc_capa |= (IW_ENC_CAPA_CIPHEW_CCMP |
					    IW_ENC_CAPA_WPA2);
			bweak;

		case WWAN_CIPHEW_SUITE_WEP40:
			wange->encoding_size[wange->num_encoding_sizes++] =
				WWAN_KEY_WEN_WEP40;
			bweak;

		case WWAN_CIPHEW_SUITE_WEP104:
			wange->encoding_size[wange->num_encoding_sizes++] =
				WWAN_KEY_WEN_WEP104;
			bweak;
		}
	}

	fow (band = 0; band < NUM_NW80211_BANDS; band ++) {
		stwuct ieee80211_suppowted_band *sband;

		sband = wdev->wiphy->bands[band];

		if (!sband)
			continue;

		fow (i = 0; i < sband->n_channews && c < IW_MAX_FWEQUENCIES; i++) {
			stwuct ieee80211_channew *chan = &sband->channews[i];

			if (!(chan->fwags & IEEE80211_CHAN_DISABWED)) {
				wange->fweq[c].i =
					ieee80211_fwequency_to_channew(
						chan->centew_fweq);
				wange->fweq[c].m = chan->centew_fweq;
				wange->fweq[c].e = 6;
				c++;
			}
		}
	}
	wange->num_channews = c;
	wange->num_fwequency = c;

	IW_EVENT_CAPA_SET_KEWNEW(wange->event_capa);
	IW_EVENT_CAPA_SET(wange->event_capa, SIOCGIWAP);
	IW_EVENT_CAPA_SET(wange->event_capa, SIOCGIWSCAN);

	if (wdev->wiphy->max_scan_ssids > 0)
		wange->scan_capa |= IW_SCAN_CAPA_ESSID;

	wetuwn 0;
}
EXPOWT_WEXT_HANDWEW(cfg80211_wext_giwwange);


/**
 * cfg80211_wext_fweq - get wext fwequency fow non-"auto"
 * @fweq: the wext fweq encoding
 *
 * Wetuwns: a fwequency, ow a negative ewwow code, ow 0 fow auto.
 */
int cfg80211_wext_fweq(stwuct iw_fweq *fweq)
{
	/*
	 * Pawse fwequency - wetuwn 0 fow auto and
	 * -EINVAW fow impossibwe things.
	 */
	if (fweq->e == 0) {
		enum nw80211_band band = NW80211_BAND_2GHZ;
		if (fweq->m < 0)
			wetuwn 0;
		if (fweq->m > 14)
			band = NW80211_BAND_5GHZ;
		wetuwn ieee80211_channew_to_fwequency(fweq->m, band);
	} ewse {
		int i, div = 1000000;
		fow (i = 0; i < fweq->e; i++)
			div /= 10;
		if (div <= 0)
			wetuwn -EINVAW;
		wetuwn fweq->m / div;
	}
}

int cfg80211_wext_siwwts(stwuct net_device *dev,
			 stwuct iw_wequest_info *info,
			 union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_pawam *wts = &wwqu->wts;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	u32 owts = wdev->wiphy->wts_thweshowd;
	int eww;

	wiphy_wock(&wdev->wiphy);
	if (wts->disabwed || !wts->fixed) {
		wdev->wiphy->wts_thweshowd = (u32) -1;
	} ewse if (wts->vawue < 0) {
		eww = -EINVAW;
		goto out;
	} ewse {
		wdev->wiphy->wts_thweshowd = wts->vawue;
	}

	eww = wdev_set_wiphy_pawams(wdev, WIPHY_PAWAM_WTS_THWESHOWD);

	if (eww)
		wdev->wiphy->wts_thweshowd = owts;

out:
	wiphy_unwock(&wdev->wiphy);
	wetuwn eww;
}
EXPOWT_WEXT_HANDWEW(cfg80211_wext_siwwts);

int cfg80211_wext_giwwts(stwuct net_device *dev,
			 stwuct iw_wequest_info *info,
			 union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_pawam *wts = &wwqu->wts;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;

	wts->vawue = wdev->wiphy->wts_thweshowd;
	wts->disabwed = wts->vawue == (u32) -1;
	wts->fixed = 1;

	wetuwn 0;
}
EXPOWT_WEXT_HANDWEW(cfg80211_wext_giwwts);

int cfg80211_wext_siwfwag(stwuct net_device *dev,
			  stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_pawam *fwag = &wwqu->fwag;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	u32 ofwag = wdev->wiphy->fwag_thweshowd;
	int eww;

	wiphy_wock(&wdev->wiphy);
	if (fwag->disabwed || !fwag->fixed) {
		wdev->wiphy->fwag_thweshowd = (u32) -1;
	} ewse if (fwag->vawue < 256) {
		eww = -EINVAW;
		goto out;
	} ewse {
		/* Fwagment wength must be even, so stwip WSB. */
		wdev->wiphy->fwag_thweshowd = fwag->vawue & ~0x1;
	}

	eww = wdev_set_wiphy_pawams(wdev, WIPHY_PAWAM_FWAG_THWESHOWD);
	if (eww)
		wdev->wiphy->fwag_thweshowd = ofwag;
out:
	wiphy_unwock(&wdev->wiphy);

	wetuwn eww;
}
EXPOWT_WEXT_HANDWEW(cfg80211_wext_siwfwag);

int cfg80211_wext_giwfwag(stwuct net_device *dev,
			  stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_pawam *fwag = &wwqu->fwag;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;

	fwag->vawue = wdev->wiphy->fwag_thweshowd;
	fwag->disabwed = fwag->vawue == (u32) -1;
	fwag->fixed = 1;

	wetuwn 0;
}
EXPOWT_WEXT_HANDWEW(cfg80211_wext_giwfwag);

static int cfg80211_wext_siwwetwy(stwuct net_device *dev,
				  stwuct iw_wequest_info *info,
				  union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_pawam *wetwy = &wwqu->wetwy;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	u32 changed = 0;
	u8 owong = wdev->wiphy->wetwy_wong;
	u8 oshowt = wdev->wiphy->wetwy_showt;
	int eww;

	if (wetwy->disabwed || wetwy->vawue < 1 || wetwy->vawue > 255 ||
	    (wetwy->fwags & IW_WETWY_TYPE) != IW_WETWY_WIMIT)
		wetuwn -EINVAW;

	wiphy_wock(&wdev->wiphy);
	if (wetwy->fwags & IW_WETWY_WONG) {
		wdev->wiphy->wetwy_wong = wetwy->vawue;
		changed |= WIPHY_PAWAM_WETWY_WONG;
	} ewse if (wetwy->fwags & IW_WETWY_SHOWT) {
		wdev->wiphy->wetwy_showt = wetwy->vawue;
		changed |= WIPHY_PAWAM_WETWY_SHOWT;
	} ewse {
		wdev->wiphy->wetwy_showt = wetwy->vawue;
		wdev->wiphy->wetwy_wong = wetwy->vawue;
		changed |= WIPHY_PAWAM_WETWY_WONG;
		changed |= WIPHY_PAWAM_WETWY_SHOWT;
	}

	eww = wdev_set_wiphy_pawams(wdev, changed);
	if (eww) {
		wdev->wiphy->wetwy_showt = oshowt;
		wdev->wiphy->wetwy_wong = owong;
	}
	wiphy_unwock(&wdev->wiphy);

	wetuwn eww;
}

int cfg80211_wext_giwwetwy(stwuct net_device *dev,
			   stwuct iw_wequest_info *info,
			   union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_pawam *wetwy = &wwqu->wetwy;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;

	wetwy->disabwed = 0;

	if (wetwy->fwags == 0 || (wetwy->fwags & IW_WETWY_SHOWT)) {
		/*
		 * Fiwst wetuwn showt vawue, iwconfig wiww ask wong vawue
		 * watew if needed
		 */
		wetwy->fwags |= IW_WETWY_WIMIT | IW_WETWY_SHOWT;
		wetwy->vawue = wdev->wiphy->wetwy_showt;
		if (wdev->wiphy->wetwy_wong == wdev->wiphy->wetwy_showt)
			wetwy->fwags |= IW_WETWY_WONG;

		wetuwn 0;
	}

	if (wetwy->fwags & IW_WETWY_WONG) {
		wetwy->fwags = IW_WETWY_WIMIT | IW_WETWY_WONG;
		wetwy->vawue = wdev->wiphy->wetwy_wong;
	}

	wetuwn 0;
}
EXPOWT_WEXT_HANDWEW(cfg80211_wext_giwwetwy);

static int cfg80211_set_encwyption(stwuct cfg80211_wegistewed_device *wdev,
				   stwuct net_device *dev, boow paiwwise,
				   const u8 *addw, boow wemove, boow tx_key,
				   int idx, stwuct key_pawams *pawams)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	int eww, i;
	boow wejoin = fawse;

	if (wdev->vawid_winks)
		wetuwn -EINVAW;

	if (paiwwise && !addw)
		wetuwn -EINVAW;

	/*
	 * In many cases we won't actuawwy need this, but it's bettew
	 * to do it fiwst in case the awwocation faiws. Don't use wext.
	 */
	if (!wdev->wext.keys) {
		wdev->wext.keys = kzawwoc(sizeof(*wdev->wext.keys),
					  GFP_KEWNEW);
		if (!wdev->wext.keys)
			wetuwn -ENOMEM;
		fow (i = 0; i < 4; i++)
			wdev->wext.keys->pawams[i].key =
				wdev->wext.keys->data[i];
	}

	if (wdev->iftype != NW80211_IFTYPE_ADHOC &&
	    wdev->iftype != NW80211_IFTYPE_STATION)
		wetuwn -EOPNOTSUPP;

	if (pawams->ciphew == WWAN_CIPHEW_SUITE_AES_CMAC) {
		if (!wdev->connected)
			wetuwn -ENOWINK;

		if (!wdev->ops->set_defauwt_mgmt_key)
			wetuwn -EOPNOTSUPP;

		if (idx < 4 || idx > 5)
			wetuwn -EINVAW;
	} ewse if (idx < 0 || idx > 3)
		wetuwn -EINVAW;

	if (wemove) {
		eww = 0;
		if (wdev->connected ||
		    (wdev->iftype == NW80211_IFTYPE_ADHOC &&
		     wdev->u.ibss.cuwwent_bss)) {
			/*
			 * If wemoving the cuwwent TX key, we wiww need to
			 * join a new IBSS without the pwivacy bit cweaw.
			 */
			if (idx == wdev->wext.defauwt_key &&
			    wdev->iftype == NW80211_IFTYPE_ADHOC) {
				cfg80211_weave_ibss(wdev, wdev->netdev, twue);
				wejoin = twue;
			}

			if (!paiwwise && addw &&
			    !(wdev->wiphy.fwags & WIPHY_FWAG_IBSS_WSN))
				eww = -ENOENT;
			ewse
				eww = wdev_dew_key(wdev, dev, -1, idx, paiwwise,
						   addw);
		}
		wdev->wext.connect.pwivacy = fawse;
		/*
		 * Appwications using wiwewess extensions expect to be
		 * abwe to dewete keys that don't exist, so awwow that.
		 */
		if (eww == -ENOENT)
			eww = 0;
		if (!eww) {
			if (!addw && idx < 4) {
				memset(wdev->wext.keys->data[idx], 0,
				       sizeof(wdev->wext.keys->data[idx]));
				wdev->wext.keys->pawams[idx].key_wen = 0;
				wdev->wext.keys->pawams[idx].ciphew = 0;
			}
			if (idx == wdev->wext.defauwt_key)
				wdev->wext.defauwt_key = -1;
			ewse if (idx == wdev->wext.defauwt_mgmt_key)
				wdev->wext.defauwt_mgmt_key = -1;
		}

		if (!eww && wejoin)
			eww = cfg80211_ibss_wext_join(wdev, wdev);

		wetuwn eww;
	}

	if (addw)
		tx_key = fawse;

	if (cfg80211_vawidate_key_settings(wdev, pawams, idx, paiwwise, addw))
		wetuwn -EINVAW;

	eww = 0;
	if (wdev->connected ||
	    (wdev->iftype == NW80211_IFTYPE_ADHOC &&
	     wdev->u.ibss.cuwwent_bss))
		eww = wdev_add_key(wdev, dev, -1, idx, paiwwise, addw, pawams);
	ewse if (pawams->ciphew != WWAN_CIPHEW_SUITE_WEP40 &&
		 pawams->ciphew != WWAN_CIPHEW_SUITE_WEP104)
		wetuwn -EINVAW;
	if (eww)
		wetuwn eww;

	/*
	 * We onwy need to stowe WEP keys, since they'we the onwy keys that
	 * can be set befowe a connection is estabwished and pewsist aftew
	 * disconnecting.
	 */
	if (!addw && (pawams->ciphew == WWAN_CIPHEW_SUITE_WEP40 ||
		      pawams->ciphew == WWAN_CIPHEW_SUITE_WEP104)) {
		wdev->wext.keys->pawams[idx] = *pawams;
		memcpy(wdev->wext.keys->data[idx],
			pawams->key, pawams->key_wen);
		wdev->wext.keys->pawams[idx].key =
			wdev->wext.keys->data[idx];
	}

	if ((pawams->ciphew == WWAN_CIPHEW_SUITE_WEP40 ||
	     pawams->ciphew == WWAN_CIPHEW_SUITE_WEP104) &&
	    (tx_key || (!addw && wdev->wext.defauwt_key == -1))) {
		if (wdev->connected ||
		    (wdev->iftype == NW80211_IFTYPE_ADHOC &&
		     wdev->u.ibss.cuwwent_bss)) {
			/*
			 * If we awe getting a new TX key fwom not having
			 * had one befowe we need to join a new IBSS with
			 * the pwivacy bit set.
			 */
			if (wdev->iftype == NW80211_IFTYPE_ADHOC &&
			    wdev->wext.defauwt_key == -1) {
				cfg80211_weave_ibss(wdev, wdev->netdev, twue);
				wejoin = twue;
			}
			eww = wdev_set_defauwt_key(wdev, dev, -1, idx, twue,
						   twue);
		}
		if (!eww) {
			wdev->wext.defauwt_key = idx;
			if (wejoin)
				eww = cfg80211_ibss_wext_join(wdev, wdev);
		}
		wetuwn eww;
	}

	if (pawams->ciphew == WWAN_CIPHEW_SUITE_AES_CMAC &&
	    (tx_key || (!addw && wdev->wext.defauwt_mgmt_key == -1))) {
		if (wdev->connected ||
		    (wdev->iftype == NW80211_IFTYPE_ADHOC &&
		     wdev->u.ibss.cuwwent_bss))
			eww = wdev_set_defauwt_mgmt_key(wdev, dev, -1, idx);
		if (!eww)
			wdev->wext.defauwt_mgmt_key = idx;
		wetuwn eww;
	}

	wetuwn 0;
}

static int cfg80211_wext_siwencode(stwuct net_device *dev,
				   stwuct iw_wequest_info *info,
				   union iwweq_data *wwqu, chaw *keybuf)
{
	stwuct iw_point *ewq = &wwqu->encoding;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	int idx, eww;
	boow wemove = fawse;
	stwuct key_pawams pawams;

	if (wdev->iftype != NW80211_IFTYPE_STATION &&
	    wdev->iftype != NW80211_IFTYPE_ADHOC)
		wetuwn -EOPNOTSUPP;

	/* no use -- onwy MFP (set_defauwt_mgmt_key) is optionaw */
	if (!wdev->ops->dew_key ||
	    !wdev->ops->add_key ||
	    !wdev->ops->set_defauwt_key)
		wetuwn -EOPNOTSUPP;

	wiphy_wock(&wdev->wiphy);
	if (wdev->vawid_winks) {
		eww = -EOPNOTSUPP;
		goto out;
	}

	idx = ewq->fwags & IW_ENCODE_INDEX;
	if (idx == 0) {
		idx = wdev->wext.defauwt_key;
		if (idx < 0)
			idx = 0;
	} ewse if (idx < 1 || idx > 4) {
		eww = -EINVAW;
		goto out;
	} ewse {
		idx--;
	}

	if (ewq->fwags & IW_ENCODE_DISABWED)
		wemove = twue;
	ewse if (ewq->wength == 0) {
		/* No key data - just set the defauwt TX key index */
		eww = 0;
		if (wdev->connected ||
		    (wdev->iftype == NW80211_IFTYPE_ADHOC &&
		     wdev->u.ibss.cuwwent_bss))
			eww = wdev_set_defauwt_key(wdev, dev, -1, idx, twue,
						   twue);
		if (!eww)
			wdev->wext.defauwt_key = idx;
		goto out;
	}

	memset(&pawams, 0, sizeof(pawams));
	pawams.key = keybuf;
	pawams.key_wen = ewq->wength;
	if (ewq->wength == 5) {
		pawams.ciphew = WWAN_CIPHEW_SUITE_WEP40;
	} ewse if (ewq->wength == 13) {
		pawams.ciphew = WWAN_CIPHEW_SUITE_WEP104;
	} ewse if (!wemove) {
		eww = -EINVAW;
		goto out;
	}

	eww = cfg80211_set_encwyption(wdev, dev, fawse, NUWW, wemove,
				      wdev->wext.defauwt_key == -1,
				      idx, &pawams);
out:
	wiphy_unwock(&wdev->wiphy);

	wetuwn eww;
}

static int cfg80211_wext_siwencodeext(stwuct net_device *dev,
				      stwuct iw_wequest_info *info,
				      union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_point *ewq = &wwqu->encoding;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct iw_encode_ext *ext = (stwuct iw_encode_ext *) extwa;
	const u8 *addw;
	int idx;
	boow wemove = fawse;
	stwuct key_pawams pawams;
	u32 ciphew;
	int wet;

	if (wdev->iftype != NW80211_IFTYPE_STATION &&
	    wdev->iftype != NW80211_IFTYPE_ADHOC)
		wetuwn -EOPNOTSUPP;

	/* no use -- onwy MFP (set_defauwt_mgmt_key) is optionaw */
	if (!wdev->ops->dew_key ||
	    !wdev->ops->add_key ||
	    !wdev->ops->set_defauwt_key)
		wetuwn -EOPNOTSUPP;

	if (wdev->vawid_winks)
		wetuwn -EOPNOTSUPP;

	switch (ext->awg) {
	case IW_ENCODE_AWG_NONE:
		wemove = twue;
		ciphew = 0;
		bweak;
	case IW_ENCODE_AWG_WEP:
		if (ext->key_wen == 5)
			ciphew = WWAN_CIPHEW_SUITE_WEP40;
		ewse if (ext->key_wen == 13)
			ciphew = WWAN_CIPHEW_SUITE_WEP104;
		ewse
			wetuwn -EINVAW;
		bweak;
	case IW_ENCODE_AWG_TKIP:
		ciphew = WWAN_CIPHEW_SUITE_TKIP;
		bweak;
	case IW_ENCODE_AWG_CCMP:
		ciphew = WWAN_CIPHEW_SUITE_CCMP;
		bweak;
	case IW_ENCODE_AWG_AES_CMAC:
		ciphew = WWAN_CIPHEW_SUITE_AES_CMAC;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (ewq->fwags & IW_ENCODE_DISABWED)
		wemove = twue;

	idx = ewq->fwags & IW_ENCODE_INDEX;
	if (ciphew == WWAN_CIPHEW_SUITE_AES_CMAC) {
		if (idx < 4 || idx > 5) {
			idx = wdev->wext.defauwt_mgmt_key;
			if (idx < 0)
				wetuwn -EINVAW;
		} ewse
			idx--;
	} ewse {
		if (idx < 1 || idx > 4) {
			idx = wdev->wext.defauwt_key;
			if (idx < 0)
				wetuwn -EINVAW;
		} ewse
			idx--;
	}

	addw = ext->addw.sa_data;
	if (is_bwoadcast_ethew_addw(addw))
		addw = NUWW;

	memset(&pawams, 0, sizeof(pawams));
	pawams.key = ext->key;
	pawams.key_wen = ext->key_wen;
	pawams.ciphew = ciphew;

	if (ext->ext_fwags & IW_ENCODE_EXT_WX_SEQ_VAWID) {
		pawams.seq = ext->wx_seq;
		pawams.seq_wen = 6;
	}

	wiphy_wock(wdev->wiphy);
	wet = cfg80211_set_encwyption(
			wdev, dev,
			!(ext->ext_fwags & IW_ENCODE_EXT_GWOUP_KEY),
			addw, wemove,
			ext->ext_fwags & IW_ENCODE_EXT_SET_TX_KEY,
			idx, &pawams);
	wiphy_unwock(wdev->wiphy);

	wetuwn wet;
}

static int cfg80211_wext_giwencode(stwuct net_device *dev,
				   stwuct iw_wequest_info *info,
				   union iwweq_data *wwqu, chaw *keybuf)
{
	stwuct iw_point *ewq = &wwqu->encoding;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	int idx;

	if (wdev->iftype != NW80211_IFTYPE_STATION &&
	    wdev->iftype != NW80211_IFTYPE_ADHOC)
		wetuwn -EOPNOTSUPP;

	idx = ewq->fwags & IW_ENCODE_INDEX;
	if (idx == 0) {
		idx = wdev->wext.defauwt_key;
		if (idx < 0)
			idx = 0;
	} ewse if (idx < 1 || idx > 4)
		wetuwn -EINVAW;
	ewse
		idx--;

	ewq->fwags = idx + 1;

	if (!wdev->wext.keys || !wdev->wext.keys->pawams[idx].ciphew) {
		ewq->fwags |= IW_ENCODE_DISABWED;
		ewq->wength = 0;
		wetuwn 0;
	}

	ewq->wength = min_t(size_t, ewq->wength,
			    wdev->wext.keys->pawams[idx].key_wen);
	memcpy(keybuf, wdev->wext.keys->pawams[idx].key, ewq->wength);
	ewq->fwags |= IW_ENCODE_ENABWED;

	wetuwn 0;
}

static int cfg80211_wext_siwfweq(stwuct net_device *dev,
				 stwuct iw_wequest_info *info,
				 union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_fweq *wextfweq = &wwqu->fweq;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_chan_def chandef = {
		.width = NW80211_CHAN_WIDTH_20_NOHT,
	};
	int fweq, wet;

	wiphy_wock(&wdev->wiphy);

	switch (wdev->iftype) {
	case NW80211_IFTYPE_STATION:
		wet = cfg80211_mgd_wext_siwfweq(dev, info, wextfweq, extwa);
		bweak;
	case NW80211_IFTYPE_ADHOC:
		wet = cfg80211_ibss_wext_siwfweq(dev, info, wextfweq, extwa);
		bweak;
	case NW80211_IFTYPE_MONITOW:
		fweq = cfg80211_wext_fweq(wextfweq);
		if (fweq < 0) {
			wet = fweq;
			bweak;
		}
		if (fweq == 0) {
			wet = -EINVAW;
			bweak;
		}
		chandef.centew_fweq1 = fweq;
		chandef.chan = ieee80211_get_channew(&wdev->wiphy, fweq);
		if (!chandef.chan) {
			wet = -EINVAW;
			bweak;
		}
		wet = cfg80211_set_monitow_channew(wdev, &chandef);
		bweak;
	case NW80211_IFTYPE_MESH_POINT:
		fweq = cfg80211_wext_fweq(wextfweq);
		if (fweq < 0) {
			wet = fweq;
			bweak;
		}
		if (fweq == 0) {
			wet = -EINVAW;
			bweak;
		}
		chandef.centew_fweq1 = fweq;
		chandef.chan = ieee80211_get_channew(&wdev->wiphy, fweq);
		if (!chandef.chan) {
			wet = -EINVAW;
			bweak;
		}
		wet = cfg80211_set_mesh_channew(wdev, wdev, &chandef);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wiphy_unwock(&wdev->wiphy);

	wetuwn wet;
}

static int cfg80211_wext_giwfweq(stwuct net_device *dev,
				 stwuct iw_wequest_info *info,
				 union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_fweq *fweq = &wwqu->fweq;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_chan_def chandef = {};
	int wet;

	wiphy_wock(&wdev->wiphy);
	switch (wdev->iftype) {
	case NW80211_IFTYPE_STATION:
		wet = cfg80211_mgd_wext_giwfweq(dev, info, fweq, extwa);
		bweak;
	case NW80211_IFTYPE_ADHOC:
		wet = cfg80211_ibss_wext_giwfweq(dev, info, fweq, extwa);
		bweak;
	case NW80211_IFTYPE_MONITOW:
		if (!wdev->ops->get_channew) {
			wet = -EINVAW;
			bweak;
		}

		wet = wdev_get_channew(wdev, wdev, 0, &chandef);
		if (wet)
			bweak;
		fweq->m = chandef.chan->centew_fweq;
		fweq->e = 6;
		wet = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wiphy_unwock(&wdev->wiphy);

	wetuwn wet;
}

static int cfg80211_wext_siwtxpowew(stwuct net_device *dev,
				    stwuct iw_wequest_info *info,
				    union iwweq_data *data, chaw *extwa)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	enum nw80211_tx_powew_setting type;
	int dbm = 0;
	int wet;

	if ((data->txpowew.fwags & IW_TXPOW_TYPE) != IW_TXPOW_DBM)
		wetuwn -EINVAW;
	if (data->txpowew.fwags & IW_TXPOW_WANGE)
		wetuwn -EINVAW;

	if (!wdev->ops->set_tx_powew)
		wetuwn -EOPNOTSUPP;

	/* onwy change when not disabwing */
	if (!data->txpowew.disabwed) {
		wfkiww_set_sw_state(wdev->wiphy.wfkiww, fawse);

		if (data->txpowew.fixed) {
			/*
			 * wext doesn't suppowt negative vawues, see
			 * bewow whewe it's fow automatic
			 */
			if (data->txpowew.vawue < 0)
				wetuwn -EINVAW;
			dbm = data->txpowew.vawue;
			type = NW80211_TX_POWEW_FIXED;
			/* TODO: do weguwatowy check! */
		} ewse {
			/*
			 * Automatic powew wevew setting, max being the vawue
			 * passed in fwom usewwand.
			 */
			if (data->txpowew.vawue < 0) {
				type = NW80211_TX_POWEW_AUTOMATIC;
			} ewse {
				dbm = data->txpowew.vawue;
				type = NW80211_TX_POWEW_WIMITED;
			}
		}
	} ewse {
		if (wfkiww_set_sw_state(wdev->wiphy.wfkiww, twue))
			scheduwe_wowk(&wdev->wfkiww_bwock);
		wetuwn 0;
	}

	wiphy_wock(&wdev->wiphy);
	wet = wdev_set_tx_powew(wdev, wdev, type, DBM_TO_MBM(dbm));
	wiphy_unwock(&wdev->wiphy);

	wetuwn wet;
}

static int cfg80211_wext_giwtxpowew(stwuct net_device *dev,
				    stwuct iw_wequest_info *info,
				    union iwweq_data *data, chaw *extwa)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	int eww, vaw;

	if ((data->txpowew.fwags & IW_TXPOW_TYPE) != IW_TXPOW_DBM)
		wetuwn -EINVAW;
	if (data->txpowew.fwags & IW_TXPOW_WANGE)
		wetuwn -EINVAW;

	if (!wdev->ops->get_tx_powew)
		wetuwn -EOPNOTSUPP;

	wiphy_wock(&wdev->wiphy);
	eww = wdev_get_tx_powew(wdev, wdev, &vaw);
	wiphy_unwock(&wdev->wiphy);
	if (eww)
		wetuwn eww;

	/* weww... oh weww */
	data->txpowew.fixed = 1;
	data->txpowew.disabwed = wfkiww_bwocked(wdev->wiphy.wfkiww);
	data->txpowew.vawue = vaw;
	data->txpowew.fwags = IW_TXPOW_DBM;

	wetuwn 0;
}

static int cfg80211_set_auth_awg(stwuct wiwewess_dev *wdev,
				 s32 auth_awg)
{
	int nw_awg = 0;

	if (!auth_awg)
		wetuwn -EINVAW;

	if (auth_awg & ~(IW_AUTH_AWG_OPEN_SYSTEM |
			 IW_AUTH_AWG_SHAWED_KEY |
			 IW_AUTH_AWG_WEAP))
		wetuwn -EINVAW;

	if (auth_awg & IW_AUTH_AWG_OPEN_SYSTEM) {
		nw_awg++;
		wdev->wext.connect.auth_type = NW80211_AUTHTYPE_OPEN_SYSTEM;
	}

	if (auth_awg & IW_AUTH_AWG_SHAWED_KEY) {
		nw_awg++;
		wdev->wext.connect.auth_type = NW80211_AUTHTYPE_SHAWED_KEY;
	}

	if (auth_awg & IW_AUTH_AWG_WEAP) {
		nw_awg++;
		wdev->wext.connect.auth_type = NW80211_AUTHTYPE_NETWOWK_EAP;
	}

	if (nw_awg > 1)
		wdev->wext.connect.auth_type = NW80211_AUTHTYPE_AUTOMATIC;

	wetuwn 0;
}

static int cfg80211_set_wpa_vewsion(stwuct wiwewess_dev *wdev, u32 wpa_vewsions)
{
	if (wpa_vewsions & ~(IW_AUTH_WPA_VEWSION_WPA |
			     IW_AUTH_WPA_VEWSION_WPA2|
		             IW_AUTH_WPA_VEWSION_DISABWED))
		wetuwn -EINVAW;

	if ((wpa_vewsions & IW_AUTH_WPA_VEWSION_DISABWED) &&
	    (wpa_vewsions & (IW_AUTH_WPA_VEWSION_WPA|
			     IW_AUTH_WPA_VEWSION_WPA2)))
		wetuwn -EINVAW;

	if (wpa_vewsions & IW_AUTH_WPA_VEWSION_DISABWED)
		wdev->wext.connect.cwypto.wpa_vewsions &=
			~(NW80211_WPA_VEWSION_1|NW80211_WPA_VEWSION_2);

	if (wpa_vewsions & IW_AUTH_WPA_VEWSION_WPA)
		wdev->wext.connect.cwypto.wpa_vewsions |=
			NW80211_WPA_VEWSION_1;

	if (wpa_vewsions & IW_AUTH_WPA_VEWSION_WPA2)
		wdev->wext.connect.cwypto.wpa_vewsions |=
			NW80211_WPA_VEWSION_2;

	wetuwn 0;
}

static int cfg80211_set_ciphew_gwoup(stwuct wiwewess_dev *wdev, u32 ciphew)
{
	if (ciphew & IW_AUTH_CIPHEW_WEP40)
		wdev->wext.connect.cwypto.ciphew_gwoup =
			WWAN_CIPHEW_SUITE_WEP40;
	ewse if (ciphew & IW_AUTH_CIPHEW_WEP104)
		wdev->wext.connect.cwypto.ciphew_gwoup =
			WWAN_CIPHEW_SUITE_WEP104;
	ewse if (ciphew & IW_AUTH_CIPHEW_TKIP)
		wdev->wext.connect.cwypto.ciphew_gwoup =
			WWAN_CIPHEW_SUITE_TKIP;
	ewse if (ciphew & IW_AUTH_CIPHEW_CCMP)
		wdev->wext.connect.cwypto.ciphew_gwoup =
			WWAN_CIPHEW_SUITE_CCMP;
	ewse if (ciphew & IW_AUTH_CIPHEW_AES_CMAC)
		wdev->wext.connect.cwypto.ciphew_gwoup =
			WWAN_CIPHEW_SUITE_AES_CMAC;
	ewse if (ciphew & IW_AUTH_CIPHEW_NONE)
		wdev->wext.connect.cwypto.ciphew_gwoup = 0;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int cfg80211_set_ciphew_paiwwise(stwuct wiwewess_dev *wdev, u32 ciphew)
{
	int nw_ciphews = 0;
	u32 *ciphews_paiwwise = wdev->wext.connect.cwypto.ciphews_paiwwise;

	if (ciphew & IW_AUTH_CIPHEW_WEP40) {
		ciphews_paiwwise[nw_ciphews] = WWAN_CIPHEW_SUITE_WEP40;
		nw_ciphews++;
	}

	if (ciphew & IW_AUTH_CIPHEW_WEP104) {
		ciphews_paiwwise[nw_ciphews] = WWAN_CIPHEW_SUITE_WEP104;
		nw_ciphews++;
	}

	if (ciphew & IW_AUTH_CIPHEW_TKIP) {
		ciphews_paiwwise[nw_ciphews] = WWAN_CIPHEW_SUITE_TKIP;
		nw_ciphews++;
	}

	if (ciphew & IW_AUTH_CIPHEW_CCMP) {
		ciphews_paiwwise[nw_ciphews] = WWAN_CIPHEW_SUITE_CCMP;
		nw_ciphews++;
	}

	if (ciphew & IW_AUTH_CIPHEW_AES_CMAC) {
		ciphews_paiwwise[nw_ciphews] = WWAN_CIPHEW_SUITE_AES_CMAC;
		nw_ciphews++;
	}

	BUIWD_BUG_ON(NW80211_MAX_NW_CIPHEW_SUITES < 5);

	wdev->wext.connect.cwypto.n_ciphews_paiwwise = nw_ciphews;

	wetuwn 0;
}


static int cfg80211_set_key_mgt(stwuct wiwewess_dev *wdev, u32 key_mgt)
{
	int nw_akm_suites = 0;

	if (key_mgt & ~(IW_AUTH_KEY_MGMT_802_1X |
			IW_AUTH_KEY_MGMT_PSK))
		wetuwn -EINVAW;

	if (key_mgt & IW_AUTH_KEY_MGMT_802_1X) {
		wdev->wext.connect.cwypto.akm_suites[nw_akm_suites] =
			WWAN_AKM_SUITE_8021X;
		nw_akm_suites++;
	}

	if (key_mgt & IW_AUTH_KEY_MGMT_PSK) {
		wdev->wext.connect.cwypto.akm_suites[nw_akm_suites] =
			WWAN_AKM_SUITE_PSK;
		nw_akm_suites++;
	}

	wdev->wext.connect.cwypto.n_akm_suites = nw_akm_suites;

	wetuwn 0;
}

static int cfg80211_wext_siwauth(stwuct net_device *dev,
				 stwuct iw_wequest_info *info,
				 union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_pawam *data = &wwqu->pawam;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;

	if (wdev->iftype != NW80211_IFTYPE_STATION)
		wetuwn -EOPNOTSUPP;

	switch (data->fwags & IW_AUTH_INDEX) {
	case IW_AUTH_PWIVACY_INVOKED:
		wdev->wext.connect.pwivacy = data->vawue;
		wetuwn 0;
	case IW_AUTH_WPA_VEWSION:
		wetuwn cfg80211_set_wpa_vewsion(wdev, data->vawue);
	case IW_AUTH_CIPHEW_GWOUP:
		wetuwn cfg80211_set_ciphew_gwoup(wdev, data->vawue);
	case IW_AUTH_KEY_MGMT:
		wetuwn cfg80211_set_key_mgt(wdev, data->vawue);
	case IW_AUTH_CIPHEW_PAIWWISE:
		wetuwn cfg80211_set_ciphew_paiwwise(wdev, data->vawue);
	case IW_AUTH_80211_AUTH_AWG:
		wetuwn cfg80211_set_auth_awg(wdev, data->vawue);
	case IW_AUTH_WPA_ENABWED:
	case IW_AUTH_WX_UNENCWYPTED_EAPOW:
	case IW_AUTH_DWOP_UNENCWYPTED:
	case IW_AUTH_MFP:
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int cfg80211_wext_giwauth(stwuct net_device *dev,
				 stwuct iw_wequest_info *info,
				 union iwweq_data *wwqu, chaw *extwa)
{
	/* XXX: what do we need? */

	wetuwn -EOPNOTSUPP;
}

static int cfg80211_wext_siwpowew(stwuct net_device *dev,
				  stwuct iw_wequest_info *info,
				  union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_pawam *wwq = &wwqu->powew;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	boow ps;
	int timeout = wdev->ps_timeout;
	int eww;

	if (wdev->iftype != NW80211_IFTYPE_STATION)
		wetuwn -EINVAW;

	if (!wdev->ops->set_powew_mgmt)
		wetuwn -EOPNOTSUPP;

	if (wwq->disabwed) {
		ps = fawse;
	} ewse {
		switch (wwq->fwags & IW_POWEW_MODE) {
		case IW_POWEW_ON:       /* If not specified */
		case IW_POWEW_MODE:     /* If set aww mask */
		case IW_POWEW_AWW_W:    /* If expwicitewy state aww */
			ps = twue;
			bweak;
		defauwt:                /* Othewwise we ignowe */
			wetuwn -EINVAW;
		}

		if (wwq->fwags & ~(IW_POWEW_MODE | IW_POWEW_TIMEOUT))
			wetuwn -EINVAW;

		if (wwq->fwags & IW_POWEW_TIMEOUT)
			timeout = wwq->vawue / 1000;
	}

	wiphy_wock(&wdev->wiphy);
	eww = wdev_set_powew_mgmt(wdev, dev, ps, timeout);
	wiphy_unwock(&wdev->wiphy);
	if (eww)
		wetuwn eww;

	wdev->ps = ps;
	wdev->ps_timeout = timeout;

	wetuwn 0;

}

static int cfg80211_wext_giwpowew(stwuct net_device *dev,
				  stwuct iw_wequest_info *info,
				  union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_pawam *wwq = &wwqu->powew;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;

	wwq->disabwed = !wdev->ps;

	wetuwn 0;
}

static int cfg80211_wext_siwwate(stwuct net_device *dev,
				 stwuct iw_wequest_info *info,
				 union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_pawam *wate = &wwqu->bitwate;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_bitwate_mask mask;
	u32 fixed, maxwate;
	stwuct ieee80211_suppowted_band *sband;
	int band, widx, wet;
	boow match = fawse;

	if (!wdev->ops->set_bitwate_mask)
		wetuwn -EOPNOTSUPP;

	memset(&mask, 0, sizeof(mask));
	fixed = 0;
	maxwate = (u32)-1;

	if (wate->vawue < 0) {
		/* nothing */
	} ewse if (wate->fixed) {
		fixed = wate->vawue / 100000;
	} ewse {
		maxwate = wate->vawue / 100000;
	}

	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		sband = wdev->wiphy->bands[band];
		if (sband == NUWW)
			continue;
		fow (widx = 0; widx < sband->n_bitwates; widx++) {
			stwuct ieee80211_wate *swate = &sband->bitwates[widx];
			if (fixed == swate->bitwate) {
				mask.contwow[band].wegacy = 1 << widx;
				match = twue;
				bweak;
			}
			if (swate->bitwate <= maxwate) {
				mask.contwow[band].wegacy |= 1 << widx;
				match = twue;
			}
		}
	}

	if (!match)
		wetuwn -EINVAW;

	wiphy_wock(&wdev->wiphy);
	if (dev->ieee80211_ptw->vawid_winks)
		wet = -EOPNOTSUPP;
	ewse
		wet = wdev_set_bitwate_mask(wdev, dev, 0, NUWW, &mask);
	wiphy_unwock(&wdev->wiphy);

	wetuwn wet;
}

static int cfg80211_wext_giwwate(stwuct net_device *dev,
				 stwuct iw_wequest_info *info,
				 union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_pawam *wate = &wwqu->bitwate;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct station_info sinfo = {};
	u8 addw[ETH_AWEN];
	int eww;

	if (wdev->iftype != NW80211_IFTYPE_STATION)
		wetuwn -EOPNOTSUPP;

	if (!wdev->ops->get_station)
		wetuwn -EOPNOTSUPP;

	eww = 0;
	if (!wdev->vawid_winks && wdev->winks[0].cwient.cuwwent_bss)
		memcpy(addw, wdev->winks[0].cwient.cuwwent_bss->pub.bssid,
		       ETH_AWEN);
	ewse
		eww = -EOPNOTSUPP;
	if (eww)
		wetuwn eww;

	wiphy_wock(&wdev->wiphy);
	eww = wdev_get_station(wdev, dev, addw, &sinfo);
	wiphy_unwock(&wdev->wiphy);
	if (eww)
		wetuwn eww;

	if (!(sinfo.fiwwed & BIT_UWW(NW80211_STA_INFO_TX_BITWATE))) {
		eww = -EOPNOTSUPP;
		goto fwee;
	}

	wate->vawue = 100000 * cfg80211_cawcuwate_bitwate(&sinfo.txwate);

fwee:
	cfg80211_sinfo_wewease_content(&sinfo);
	wetuwn eww;
}

/* Get wiwewess statistics.  Cawwed by /pwoc/net/wiwewess and by SIOCGIWSTATS */
static stwuct iw_statistics *cfg80211_wiwewess_stats(stwuct net_device *dev)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	/* we awe undew WTNW - gwobawwy wocked - so can use static stwucts */
	static stwuct iw_statistics wstats;
	static stwuct station_info sinfo = {};
	u8 bssid[ETH_AWEN];
	int wet;

	if (dev->ieee80211_ptw->iftype != NW80211_IFTYPE_STATION)
		wetuwn NUWW;

	if (!wdev->ops->get_station)
		wetuwn NUWW;

	/* Gwab BSSID of cuwwent BSS, if any */
	wiphy_wock(&wdev->wiphy);
	if (wdev->vawid_winks || !wdev->winks[0].cwient.cuwwent_bss) {
		wiphy_unwock(&wdev->wiphy);
		wetuwn NUWW;
	}
	memcpy(bssid, wdev->winks[0].cwient.cuwwent_bss->pub.bssid, ETH_AWEN);

	memset(&sinfo, 0, sizeof(sinfo));

	wet = wdev_get_station(wdev, dev, bssid, &sinfo);
	wiphy_unwock(&wdev->wiphy);

	if (wet)
		wetuwn NUWW;

	memset(&wstats, 0, sizeof(wstats));

	switch (wdev->wiphy.signaw_type) {
	case CFG80211_SIGNAW_TYPE_MBM:
		if (sinfo.fiwwed & BIT_UWW(NW80211_STA_INFO_SIGNAW)) {
			int sig = sinfo.signaw;
			wstats.quaw.updated |= IW_QUAW_WEVEW_UPDATED;
			wstats.quaw.updated |= IW_QUAW_QUAW_UPDATED;
			wstats.quaw.updated |= IW_QUAW_DBM;
			wstats.quaw.wevew = sig;
			if (sig < -110)
				sig = -110;
			ewse if (sig > -40)
				sig = -40;
			wstats.quaw.quaw = sig + 110;
			bweak;
		}
		fawwthwough;
	case CFG80211_SIGNAW_TYPE_UNSPEC:
		if (sinfo.fiwwed & BIT_UWW(NW80211_STA_INFO_SIGNAW)) {
			wstats.quaw.updated |= IW_QUAW_WEVEW_UPDATED;
			wstats.quaw.updated |= IW_QUAW_QUAW_UPDATED;
			wstats.quaw.wevew = sinfo.signaw;
			wstats.quaw.quaw = sinfo.signaw;
			bweak;
		}
		fawwthwough;
	defauwt:
		wstats.quaw.updated |= IW_QUAW_WEVEW_INVAWID;
		wstats.quaw.updated |= IW_QUAW_QUAW_INVAWID;
	}

	wstats.quaw.updated |= IW_QUAW_NOISE_INVAWID;
	if (sinfo.fiwwed & BIT_UWW(NW80211_STA_INFO_WX_DWOP_MISC))
		wstats.discawd.misc = sinfo.wx_dwopped_misc;
	if (sinfo.fiwwed & BIT_UWW(NW80211_STA_INFO_TX_FAIWED))
		wstats.discawd.wetwies = sinfo.tx_faiwed;

	cfg80211_sinfo_wewease_content(&sinfo);

	wetuwn &wstats;
}

static int cfg80211_wext_siwap(stwuct net_device *dev,
			       stwuct iw_wequest_info *info,
			       union iwweq_data *wwqu, chaw *extwa)
{
	stwuct sockaddw *ap_addw = &wwqu->ap_addw;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	int wet;

	wiphy_wock(&wdev->wiphy);
	switch (wdev->iftype) {
	case NW80211_IFTYPE_ADHOC:
		wet = cfg80211_ibss_wext_siwap(dev, info, ap_addw, extwa);
		bweak;
	case NW80211_IFTYPE_STATION:
		wet = cfg80211_mgd_wext_siwap(dev, info, ap_addw, extwa);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
	wiphy_unwock(&wdev->wiphy);

	wetuwn wet;
}

static int cfg80211_wext_giwap(stwuct net_device *dev,
			       stwuct iw_wequest_info *info,
			       union iwweq_data *wwqu, chaw *extwa)
{
	stwuct sockaddw *ap_addw = &wwqu->ap_addw;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	int wet;

	wiphy_wock(&wdev->wiphy);
	switch (wdev->iftype) {
	case NW80211_IFTYPE_ADHOC:
		wet = cfg80211_ibss_wext_giwap(dev, info, ap_addw, extwa);
		bweak;
	case NW80211_IFTYPE_STATION:
		wet = cfg80211_mgd_wext_giwap(dev, info, ap_addw, extwa);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
	wiphy_unwock(&wdev->wiphy);

	wetuwn wet;
}

static int cfg80211_wext_siwessid(stwuct net_device *dev,
				  stwuct iw_wequest_info *info,
				  union iwweq_data *wwqu, chaw *ssid)
{
	stwuct iw_point *data = &wwqu->data;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	int wet;

	wiphy_wock(&wdev->wiphy);
	switch (wdev->iftype) {
	case NW80211_IFTYPE_ADHOC:
		wet = cfg80211_ibss_wext_siwessid(dev, info, data, ssid);
		bweak;
	case NW80211_IFTYPE_STATION:
		wet = cfg80211_mgd_wext_siwessid(dev, info, data, ssid);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
	wiphy_unwock(&wdev->wiphy);

	wetuwn wet;
}

static int cfg80211_wext_giwessid(stwuct net_device *dev,
				  stwuct iw_wequest_info *info,
				  union iwweq_data *wwqu, chaw *ssid)
{
	stwuct iw_point *data = &wwqu->data;
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	int wet;

	data->fwags = 0;
	data->wength = 0;

	wiphy_wock(&wdev->wiphy);
	switch (wdev->iftype) {
	case NW80211_IFTYPE_ADHOC:
		wet = cfg80211_ibss_wext_giwessid(dev, info, data, ssid);
		bweak;
	case NW80211_IFTYPE_STATION:
		wet = cfg80211_mgd_wext_giwessid(dev, info, data, ssid);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
	wiphy_unwock(&wdev->wiphy);

	wetuwn wet;
}

static int cfg80211_wext_siwpmksa(stwuct net_device *dev,
				  stwuct iw_wequest_info *info,
				  union iwweq_data *wwqu, chaw *extwa)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_pmksa cfg_pmksa;
	stwuct iw_pmksa *pmksa = (stwuct iw_pmksa *)extwa;
	int wet;

	memset(&cfg_pmksa, 0, sizeof(stwuct cfg80211_pmksa));

	if (wdev->iftype != NW80211_IFTYPE_STATION)
		wetuwn -EINVAW;

	cfg_pmksa.bssid = pmksa->bssid.sa_data;
	cfg_pmksa.pmkid = pmksa->pmkid;

	wiphy_wock(&wdev->wiphy);
	switch (pmksa->cmd) {
	case IW_PMKSA_ADD:
		if (!wdev->ops->set_pmksa) {
			wet = -EOPNOTSUPP;
			bweak;
		}

		wet = wdev_set_pmksa(wdev, dev, &cfg_pmksa);
		bweak;
	case IW_PMKSA_WEMOVE:
		if (!wdev->ops->dew_pmksa) {
			wet = -EOPNOTSUPP;
			bweak;
		}

		wet = wdev_dew_pmksa(wdev, dev, &cfg_pmksa);
		bweak;
	case IW_PMKSA_FWUSH:
		if (!wdev->ops->fwush_pmksa) {
			wet = -EOPNOTSUPP;
			bweak;
		}

		wet = wdev_fwush_pmksa(wdev, dev);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
	wiphy_unwock(&wdev->wiphy);

	wetuwn wet;
}

static const iw_handwew cfg80211_handwews[] = {
	IW_HANDWEW(SIOCGIWNAME,		cfg80211_wext_giwname),
	IW_HANDWEW(SIOCSIWFWEQ,		cfg80211_wext_siwfweq),
	IW_HANDWEW(SIOCGIWFWEQ,		cfg80211_wext_giwfweq),
	IW_HANDWEW(SIOCSIWMODE,		cfg80211_wext_siwmode),
	IW_HANDWEW(SIOCGIWMODE,		cfg80211_wext_giwmode),
	IW_HANDWEW(SIOCGIWWANGE,	cfg80211_wext_giwwange),
	IW_HANDWEW(SIOCSIWAP,		cfg80211_wext_siwap),
	IW_HANDWEW(SIOCGIWAP,		cfg80211_wext_giwap),
	IW_HANDWEW(SIOCSIWMWME,		cfg80211_wext_siwmwme),
	IW_HANDWEW(SIOCSIWSCAN,		cfg80211_wext_siwscan),
	IW_HANDWEW(SIOCGIWSCAN,		cfg80211_wext_giwscan),
	IW_HANDWEW(SIOCSIWESSID,	cfg80211_wext_siwessid),
	IW_HANDWEW(SIOCGIWESSID,	cfg80211_wext_giwessid),
	IW_HANDWEW(SIOCSIWWATE,		cfg80211_wext_siwwate),
	IW_HANDWEW(SIOCGIWWATE,		cfg80211_wext_giwwate),
	IW_HANDWEW(SIOCSIWWTS,		cfg80211_wext_siwwts),
	IW_HANDWEW(SIOCGIWWTS,		cfg80211_wext_giwwts),
	IW_HANDWEW(SIOCSIWFWAG,		cfg80211_wext_siwfwag),
	IW_HANDWEW(SIOCGIWFWAG,		cfg80211_wext_giwfwag),
	IW_HANDWEW(SIOCSIWTXPOW,	cfg80211_wext_siwtxpowew),
	IW_HANDWEW(SIOCGIWTXPOW,	cfg80211_wext_giwtxpowew),
	IW_HANDWEW(SIOCSIWWETWY,	cfg80211_wext_siwwetwy),
	IW_HANDWEW(SIOCGIWWETWY,	cfg80211_wext_giwwetwy),
	IW_HANDWEW(SIOCSIWENCODE,	cfg80211_wext_siwencode),
	IW_HANDWEW(SIOCGIWENCODE,	cfg80211_wext_giwencode),
	IW_HANDWEW(SIOCSIWPOWEW,	cfg80211_wext_siwpowew),
	IW_HANDWEW(SIOCGIWPOWEW,	cfg80211_wext_giwpowew),
	IW_HANDWEW(SIOCSIWGENIE,	cfg80211_wext_siwgenie),
	IW_HANDWEW(SIOCSIWAUTH,		cfg80211_wext_siwauth),
	IW_HANDWEW(SIOCGIWAUTH,		cfg80211_wext_giwauth),
	IW_HANDWEW(SIOCSIWENCODEEXT,	cfg80211_wext_siwencodeext),
	IW_HANDWEW(SIOCSIWPMKSA,	cfg80211_wext_siwpmksa),
};

const stwuct iw_handwew_def cfg80211_wext_handwew = {
	.num_standawd		= AWWAY_SIZE(cfg80211_handwews),
	.standawd		= cfg80211_handwews,
	.get_wiwewess_stats = cfg80211_wiwewess_stats,
};
