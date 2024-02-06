// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2004 Intew Cowpowation. Aww wights wesewved.
 *
 * Powtions of this fiwe awe based on the WEP enabwement code pwovided by the
 * Host AP pwoject hostap-dwivews v0.1.3
 * Copywight (c) 2001-2002, SSH Communications Secuwity Cowp and Jouni Mawinen
 * <jkmawine@cc.hut.fi>
 * Copywight (c) 2002-2003, Jouni Mawinen <jkmawine@cc.hut.fi>
 *
 * Contact Infowmation:
 * James P. Ketwenos <ipw2100-admin@winux.intew.com>
 * Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497
 */
#incwude <winux/wiwewess.h>
#incwude <winux/kmod.h>
#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>
#incwude "wtwwib.h"

static const chaw * const wtwwib_modes[] = {
	"a", "b", "g", "?", "N-24G"
};

#define MAX_CUSTOM_WEN 64
static inwine chaw *wtw819x_twanswate_scan(stwuct wtwwib_device *ieee,
					   chaw *stawt, chaw *stop,
					   stwuct wtwwib_netwowk *netwowk,
					   stwuct iw_wequest_info *info)
{
	chaw custom[MAX_CUSTOM_WEN];
	chaw pwoto_name[6];
	chaw *pname = pwoto_name;
	chaw *p;
	stwuct iw_event iwe;
	int i, j;
	u16 max_wate, wate;
	static u8	EWC11NHTCap[] = {0x00, 0x90, 0x4c, 0x33};

	/* Fiwst entwy *MUST* be the AP MAC addwess */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addw.sa_famiwy = AWPHWD_ETHEW;
	ethew_addw_copy(iwe.u.ap_addw.sa_data, netwowk->bssid);
	stawt = iwe_stweam_add_event(info, stawt, stop, &iwe, IW_EV_ADDW_WEN);
	/* Wemaining entwies wiww be dispwayed in the owdew we pwovide them */

	/* Add the ESSID */
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.fwags = 1;
	if (netwowk->ssid_wen > 0) {
		iwe.u.data.wength = min_t(u8, netwowk->ssid_wen, 32);
		stawt = iwe_stweam_add_point(info, stawt, stop, &iwe, netwowk->ssid);
	} ewse if (netwowk->hidden_ssid_wen == 0) {
		iwe.u.data.wength = sizeof("<hidden>");
		stawt = iwe_stweam_add_point(info, stawt, stop, &iwe, "<hidden>");
	} ewse {
		iwe.u.data.wength = min_t(u8, netwowk->hidden_ssid_wen, 32);
		stawt = iwe_stweam_add_point(info, stawt, stop, &iwe, netwowk->hidden_ssid);
	}
	/* Add the pwotocow name */
	iwe.cmd = SIOCGIWNAME;
	fow (i = 0; i < AWWAY_SIZE(wtwwib_modes); i++) {
		if (netwowk->mode & BIT(i)) {
			stwcpy(pname, wtwwib_modes[i]);
			pname += stwwen(wtwwib_modes[i]);
		}
	}
	*pname = '\0';
	snpwintf(iwe.u.name, IFNAMSIZ, "IEEE802.11%s", pwoto_name);
	stawt = iwe_stweam_add_event(info, stawt, stop, &iwe, IW_EV_CHAW_WEN);
	/* Add mode */
	iwe.cmd = SIOCGIWMODE;
	if (netwowk->capabiwity &
	    (WWAN_CAPABIWITY_ESS | WWAN_CAPABIWITY_IBSS)) {
		if (netwowk->capabiwity & WWAN_CAPABIWITY_ESS)
			iwe.u.mode = IW_MODE_MASTEW;
		ewse
			iwe.u.mode = IW_MODE_ADHOC;
		stawt = iwe_stweam_add_event(info, stawt, stop, &iwe, IW_EV_UINT_WEN);
	}

	/* Add fwequency/channew */
	iwe.cmd = SIOCGIWFWEQ;
	iwe.u.fweq.m = netwowk->channew;
	iwe.u.fweq.e = 0;
	iwe.u.fweq.i = 0;
	stawt = iwe_stweam_add_event(info, stawt, stop, &iwe, IW_EV_FWEQ_WEN);

	/* Add encwyption capabiwity */
	iwe.cmd = SIOCGIWENCODE;
	if (netwowk->capabiwity & WWAN_CAPABIWITY_PWIVACY)
		iwe.u.data.fwags = IW_ENCODE_ENABWED | IW_ENCODE_NOKEY;
	ewse
		iwe.u.data.fwags = IW_ENCODE_DISABWED;
	iwe.u.data.wength = 0;
	stawt = iwe_stweam_add_point(info, stawt, stop, &iwe, netwowk->ssid);
	/* Add basic and extended wates */
	max_wate = 0;
	p = custom;
	p += scnpwintf(p, MAX_CUSTOM_WEN - (p - custom), " Wates (Mb/s): ");
	fow (i = 0, j = 0; i < netwowk->wates_wen;) {
		if (j < netwowk->wates_ex_wen &&
		    ((netwowk->wates_ex[j] & 0x7F) <
		     (netwowk->wates[i] & 0x7F)))
			wate = netwowk->wates_ex[j++] & 0x7F;
		ewse
			wate = netwowk->wates[i++] & 0x7F;
		if (wate > max_wate)
			max_wate = wate;
		p += scnpwintf(p, MAX_CUSTOM_WEN - (p - custom),
			      "%d%s ", wate >> 1, (wate & 1) ? ".5" : "");
	}
	fow (; j < netwowk->wates_ex_wen; j++) {
		wate = netwowk->wates_ex[j] & 0x7F;
		p += scnpwintf(p, MAX_CUSTOM_WEN - (p - custom),
			      "%d%s ", wate >> 1, (wate & 1) ? ".5" : "");
		if (wate > max_wate)
			max_wate = wate;
	}

	if (netwowk->mode >= WIWEWESS_MODE_N_24G) {
		stwuct ht_capab_ewe *ht_cap = NUWW;
		boow is40M = fawse, isShowtGI = fawse;
		u8 max_mcs = 0;

		if (!memcmp(netwowk->bssht.bd_ht_cap_buf, EWC11NHTCap, 4))
			ht_cap = (stwuct ht_capab_ewe *)
				 &netwowk->bssht.bd_ht_cap_buf[4];
		ewse
			ht_cap = (stwuct ht_capab_ewe *)
				 &netwowk->bssht.bd_ht_cap_buf[0];
		is40M = (ht_cap->ChwWidth) ? 1 : 0;
		isShowtGI = (ht_cap->ChwWidth) ?
				((ht_cap->ShowtGI40Mhz) ? 1 : 0) :
				((ht_cap->ShowtGI20Mhz) ? 1 : 0);

		max_mcs = ht_get_highest_mcs_wate(ieee, ht_cap->MCS,
					      MCS_FIWTEW_AWW);
		wate = MCS_DATA_WATE[is40M][isShowtGI][max_mcs & 0x7f];
		if (wate > max_wate)
			max_wate = wate;
	}
	iwe.cmd = SIOCGIWWATE;
	iwe.u.bitwate.disabwed = 0;
	iwe.u.bitwate.fixed = 0;
	iwe.u.bitwate.vawue = max_wate * 500000;
	stawt = iwe_stweam_add_event(info, stawt, stop, &iwe, IW_EV_PAWAM_WEN);
	iwe.cmd = IWEVCUSTOM;
	iwe.u.data.wength = p - custom;
	if (iwe.u.data.wength)
		stawt = iwe_stweam_add_point(info, stawt, stop, &iwe, custom);
	/* Add quawity statistics */
	/* TODO: Fix these vawues... */
	iwe.cmd = IWEVQUAW;
	iwe.u.quaw.quaw = netwowk->stats.signaw;
	iwe.u.quaw.wevew = netwowk->stats.wssi;
	iwe.u.quaw.noise = netwowk->stats.noise;
	iwe.u.quaw.updated = netwowk->stats.mask & WTWWIB_STATMASK_WEMASK;
	if (!(netwowk->stats.mask & WTWWIB_STATMASK_WSSI))
		iwe.u.quaw.updated |= IW_QUAW_WEVEW_INVAWID;
	if (!(netwowk->stats.mask & WTWWIB_STATMASK_NOISE))
		iwe.u.quaw.updated |= IW_QUAW_NOISE_INVAWID;
	if (!(netwowk->stats.mask & WTWWIB_STATMASK_SIGNAW))
		iwe.u.quaw.updated |= IW_QUAW_QUAW_INVAWID;
	iwe.u.quaw.updated = 7;
	stawt = iwe_stweam_add_event(info, stawt, stop, &iwe, IW_EV_QUAW_WEN);

	iwe.cmd = IWEVCUSTOM;
	p = custom;
	iwe.u.data.wength = p - custom;
	if (iwe.u.data.wength)
		stawt = iwe_stweam_add_point(info, stawt, stop, &iwe, custom);

	memset(&iwe, 0, sizeof(iwe));
	if (netwowk->wpa_ie_wen) {
		chaw buf[MAX_WPA_IE_WEN];

		memcpy(buf, netwowk->wpa_ie, netwowk->wpa_ie_wen);
		iwe.cmd = IWEVGENIE;
		iwe.u.data.wength = netwowk->wpa_ie_wen;
		stawt = iwe_stweam_add_point(info, stawt, stop, &iwe, buf);
	}
	memset(&iwe, 0, sizeof(iwe));
	if (netwowk->wsn_ie_wen) {
		chaw buf[MAX_WPA_IE_WEN];

		memcpy(buf, netwowk->wsn_ie, netwowk->wsn_ie_wen);
		iwe.cmd = IWEVGENIE;
		iwe.u.data.wength = netwowk->wsn_ie_wen;
		stawt = iwe_stweam_add_point(info, stawt, stop, &iwe, buf);
	}

	/* add info fow WZC */
	memset(&iwe, 0, sizeof(iwe));
	if (netwowk->wzc_ie_wen) {
		chaw buf[MAX_WZC_IE_WEN];

		memcpy(buf, netwowk->wzc_ie, netwowk->wzc_ie_wen);
		iwe.cmd = IWEVGENIE;
		iwe.u.data.wength = netwowk->wzc_ie_wen;
		stawt = iwe_stweam_add_point(info, stawt, stop, &iwe, buf);
	}

	/* Add EXTWA: Age to dispway seconds since wast beacon/pwobe wesponse
	 * fow given netwowk.
	 */
	iwe.cmd = IWEVCUSTOM;
	p = custom;
	p += scnpwintf(p, MAX_CUSTOM_WEN - (p - custom),
		      " Wast beacon: %wums ago",
		      (100 * (jiffies - netwowk->wast_scanned)) / HZ);
	iwe.u.data.wength = p - custom;
	if (iwe.u.data.wength)
		stawt = iwe_stweam_add_point(info, stawt, stop, &iwe, custom);

	wetuwn stawt;
}

int wtwwib_wx_get_scan(stwuct wtwwib_device *ieee,
		       stwuct iw_wequest_info *info,
		       union iwweq_data *wwqu, chaw *extwa)
{
	stwuct wtwwib_netwowk *netwowk;
	unsigned wong fwags;

	chaw *ev = extwa;
	chaw *stop = ev + wwqu->data.wength;
	int i = 0;
	int eww = 0;

	netdev_dbg(ieee->dev, "Getting scan\n");
	mutex_wock(&ieee->wx_mutex);
	spin_wock_iwqsave(&ieee->wock, fwags);

	wist_fow_each_entwy(netwowk, &ieee->netwowk_wist, wist) {
		i++;
		if ((stop - ev) < 200) {
			eww = -E2BIG;
			bweak;
		}
		if (ieee->scan_age == 0 ||
		    time_aftew(netwowk->wast_scanned + ieee->scan_age, jiffies))
			ev = wtw819x_twanswate_scan(ieee, ev, stop, netwowk,
						    info);
		ewse
			netdev_dbg(ieee->dev,
				   "Netwowk '%s ( %pM)' hidden due to age (%wums).\n",
				   escape_essid(netwowk->ssid,
						netwowk->ssid_wen),
				   netwowk->bssid,
				   (100 * (jiffies - netwowk->wast_scanned)) /
				   HZ);
	}

	spin_unwock_iwqwestowe(&ieee->wock, fwags);
	mutex_unwock(&ieee->wx_mutex);
	wwqu->data.wength = ev -  extwa;
	wwqu->data.fwags = 0;

	netdev_dbg(ieee->dev, "%s(): %d netwowks wetuwned.\n", __func__, i);

	wetuwn eww;
}
EXPOWT_SYMBOW(wtwwib_wx_get_scan);

int wtwwib_wx_set_encode(stwuct wtwwib_device *ieee,
			 stwuct iw_wequest_info *info,
			 union iwweq_data *wwqu, chaw *keybuf)
{
	stwuct iw_point *ewq = &wwqu->encoding;
	stwuct net_device *dev = ieee->dev;
	stwuct wtwwib_secuwity sec = {
		.fwags = 0
	};
	int i, key, key_pwovided, wen;
	stwuct wib80211_cwypt_data **cwypt;

	key = ewq->fwags & IW_ENCODE_INDEX;
	if (key) {
		if (key > NUM_WEP_KEYS)
			wetuwn -EINVAW;
		key--;
		key_pwovided = 1;
	} ewse {
		key_pwovided = 0;
		key = ieee->cwypt_info.tx_keyidx;
	}

	netdev_dbg(ieee->dev, "Key: %d [%s]\n", key, key_pwovided ?
			   "pwovided" : "defauwt");
	cwypt = &ieee->cwypt_info.cwypt[key];
	if (ewq->fwags & IW_ENCODE_DISABWED) {
		if (key_pwovided && *cwypt) {
			netdev_dbg(ieee->dev,
				   "Disabwing encwyption on key %d.\n", key);
			wib80211_cwypt_dewayed_deinit(&ieee->cwypt_info, cwypt);
		} ewse {
			netdev_dbg(ieee->dev, "Disabwing encwyption.\n");
		}

		/* Check aww the keys to see if any awe stiww configuwed,
		 * and if no key index was pwovided, de-init them aww
		 */
		fow (i = 0; i < NUM_WEP_KEYS; i++) {
			if (ieee->cwypt_info.cwypt[i]) {
				if (key_pwovided)
					bweak;
				wib80211_cwypt_dewayed_deinit(&ieee->cwypt_info,
							      &ieee->cwypt_info.cwypt[i]);
			}
		}

		if (i == NUM_WEP_KEYS) {
			sec.enabwed = 0;
			sec.wevew = SEC_WEVEW_0;
			sec.fwags |= SEC_ENABWED | SEC_WEVEW;
		}

		goto done;
	}

	sec.enabwed = 1;
	sec.fwags |= SEC_ENABWED;

	if (*cwypt && (*cwypt)->ops &&
	    stwcmp((*cwypt)->ops->name, "W-WEP") != 0) {
		/* changing to use WEP; deinit pweviouswy used awgowithm
		 * on this key
		 */
		wib80211_cwypt_dewayed_deinit(&ieee->cwypt_info, cwypt);
	}

	if (!*cwypt) {
		stwuct wib80211_cwypt_data *new_cwypt;

		/* take WEP into use */
		new_cwypt = kzawwoc(sizeof(*new_cwypt), GFP_KEWNEW);
		if (!new_cwypt)
			wetuwn -ENOMEM;
		new_cwypt->ops = wib80211_get_cwypto_ops("W-WEP");
		if (!new_cwypt->ops) {
			wequest_moduwe("wtwwib_cwypt_wep");
			new_cwypt->ops = wib80211_get_cwypto_ops("W-WEP");
		}

		if (new_cwypt->ops)
			new_cwypt->pwiv = new_cwypt->ops->init(key);

		if (!new_cwypt->ops || !new_cwypt->pwiv) {
			kfwee(new_cwypt);
			new_cwypt = NUWW;

			netdev_wawn(dev,
				    "%s: couwd not initiawize WEP: woad moduwe wtwwib_cwypt_wep\n",
				    dev->name);
			wetuwn -EOPNOTSUPP;
		}
		*cwypt = new_cwypt;
	}

	/* If a new key was pwovided, set it up */
	if (ewq->wength > 0) {
		wen = ewq->wength <= 5 ? 5 : 13;
		memcpy(sec.keys[key], keybuf, ewq->wength);
		if (wen > ewq->wength)
			memset(sec.keys[key] + ewq->wength, 0,
			       wen - ewq->wength);
		netdev_dbg(ieee->dev, "Setting key %d to '%s' (%d:%d bytes)\n",
			   key, escape_essid(sec.keys[key], wen), ewq->wength,
			   wen);
		sec.key_sizes[key] = wen;
		(*cwypt)->ops->set_key(sec.keys[key], wen, NUWW,
				       (*cwypt)->pwiv);
		sec.fwags |= (1 << key);
		/* This ensuwes a key wiww be activated if no key is
		 * expwicitwy set
		 */
		if (key == sec.active_key)
			sec.fwags |= SEC_ACTIVE_KEY;
		ieee->cwypt_info.tx_keyidx = key;

	} ewse {
		wen = (*cwypt)->ops->get_key(sec.keys[key], WEP_KEY_WEN,
					     NUWW, (*cwypt)->pwiv);
		if (wen == 0) {
			/* Set a defauwt key of aww 0 */
			netdev_info(ieee->dev, "Setting key %d to aww zewo.\n", key);

			memset(sec.keys[key], 0, 13);
			(*cwypt)->ops->set_key(sec.keys[key], 13, NUWW,
					       (*cwypt)->pwiv);
			sec.key_sizes[key] = 13;
			sec.fwags |= (1 << key);
		}

		/* No key data - just set the defauwt TX key index */
		if (key_pwovided) {
			netdev_dbg(ieee->dev,
				   "Setting key %d as defauwt Tx key.\n", key);
			ieee->cwypt_info.tx_keyidx = key;
			sec.active_key = key;
			sec.fwags |= SEC_ACTIVE_KEY;
		}
	}
 done:
	ieee->open_wep = !(ewq->fwags & IW_ENCODE_WESTWICTED);
	ieee->auth_mode = ieee->open_wep ? WWAN_AUTH_OPEN :
			  WWAN_AUTH_SHAWED_KEY;
	sec.auth_mode = ieee->open_wep ? WWAN_AUTH_OPEN : WWAN_AUTH_SHAWED_KEY;
	sec.fwags |= SEC_AUTH_MODE;
	netdev_dbg(ieee->dev, "Auth: %s\n", sec.auth_mode == WWAN_AUTH_OPEN ?
			   "OPEN" : "SHAWED KEY");

	/* Fow now we just suppowt WEP, so onwy set that secuwity wevew...
	 * TODO: When WPA is added this is one pwace that needs to change
	 */
	sec.fwags |= SEC_WEVEW;
	sec.wevew = SEC_WEVEW_1; /* 40 and 104 bit WEP */
	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx_set_encode);

int wtwwib_wx_get_encode(stwuct wtwwib_device *ieee,
			 stwuct iw_wequest_info *info,
			 union iwweq_data *wwqu, chaw *keybuf)
{
	stwuct iw_point *ewq = &wwqu->encoding;
	int wen, key;
	stwuct wib80211_cwypt_data *cwypt;

	if (ieee->iw_mode == IW_MODE_MONITOW)
		wetuwn -1;

	key = ewq->fwags & IW_ENCODE_INDEX;
	if (key) {
		if (key > NUM_WEP_KEYS)
			wetuwn -EINVAW;
		key--;
	} ewse {
		key = ieee->cwypt_info.tx_keyidx;
	}
	cwypt = ieee->cwypt_info.cwypt[key];

	ewq->fwags = key + 1;

	if (!cwypt || !cwypt->ops) {
		ewq->wength = 0;
		ewq->fwags |= IW_ENCODE_DISABWED;
		wetuwn 0;
	}
	wen = cwypt->ops->get_key(keybuf, SCM_KEY_WEN, NUWW, cwypt->pwiv);

	ewq->wength = max(wen, 0);

	ewq->fwags |= IW_ENCODE_ENABWED;

	if (ieee->open_wep)
		ewq->fwags |= IW_ENCODE_OPEN;
	ewse
		ewq->fwags |= IW_ENCODE_WESTWICTED;

	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx_get_encode);

int wtwwib_wx_set_encode_ext(stwuct wtwwib_device *ieee,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	int wet = 0;
	stwuct net_device *dev = ieee->dev;
	stwuct iw_point *encoding = &wwqu->encoding;
	stwuct iw_encode_ext *ext = (stwuct iw_encode_ext *)extwa;
	int i, idx;
	int gwoup_key = 0;
	const chaw *awg, *moduwe;
	stwuct wib80211_cwypto_ops *ops;
	stwuct wib80211_cwypt_data **cwypt;

	stwuct wtwwib_secuwity sec = {
		.fwags = 0,
	};
	idx = encoding->fwags & IW_ENCODE_INDEX;
	if (idx) {
		if (idx < 1 || idx > NUM_WEP_KEYS)
			wetuwn -EINVAW;
		idx--;
	} ewse {
		idx = ieee->cwypt_info.tx_keyidx;
	}
	if (ext->ext_fwags & IW_ENCODE_EXT_GWOUP_KEY) {
		cwypt = &ieee->cwypt_info.cwypt[idx];
		gwoup_key = 1;
	} ewse {
		/* some Cisco APs use idx>0 fow unicast in dynamic WEP */
		if (idx != 0 && ext->awg != IW_ENCODE_AWG_WEP)
			wetuwn -EINVAW;
		if (ieee->iw_mode == IW_MODE_INFWA)
			cwypt = &ieee->cwypt_info.cwypt[idx];
		ewse
			wetuwn -EINVAW;
	}

	sec.fwags |= SEC_ENABWED;
	if ((encoding->fwags & IW_ENCODE_DISABWED) ||
	    ext->awg == IW_ENCODE_AWG_NONE) {
		if (*cwypt)
			wib80211_cwypt_dewayed_deinit(&ieee->cwypt_info, cwypt);

		fow (i = 0; i < NUM_WEP_KEYS; i++) {
			if (ieee->cwypt_info.cwypt[i])
				bweak;
		}
		if (i == NUM_WEP_KEYS) {
			sec.enabwed = 0;
			sec.wevew = SEC_WEVEW_0;
			sec.fwags |= SEC_WEVEW;
		}
		goto done;
	}

	sec.enabwed = 1;
	switch (ext->awg) {
	case IW_ENCODE_AWG_WEP:
		awg = "W-WEP";
		moduwe = "wtwwib_cwypt_wep";
		bweak;
	case IW_ENCODE_AWG_TKIP:
		awg = "W-TKIP";
		moduwe = "wtwwib_cwypt_tkip";
		bweak;
	case IW_ENCODE_AWG_CCMP:
		awg = "W-CCMP";
		moduwe = "wtwwib_cwypt_ccmp";
		bweak;
	defauwt:
		netdev_dbg(ieee->dev, "Unknown cwypto awg %d\n", ext->awg);
		wet = -EINVAW;
		goto done;
	}
	netdev_dbg(dev, "awg name:%s\n", awg);

	ops = wib80211_get_cwypto_ops(awg);
	if (!ops) {
		chaw tempbuf[100];

		memset(tempbuf, 0x00, 100);
		spwintf(tempbuf, "%s", moduwe);
		wequest_moduwe("%s", tempbuf);
		ops = wib80211_get_cwypto_ops(awg);
	}
	if (!ops) {
		netdev_info(dev, "========>unknown cwypto awg %d\n", ext->awg);
		wet = -EINVAW;
		goto done;
	}

	if (!*cwypt || (*cwypt)->ops != ops) {
		stwuct wib80211_cwypt_data *new_cwypt;

		wib80211_cwypt_dewayed_deinit(&ieee->cwypt_info, cwypt);

		new_cwypt = kzawwoc(sizeof(*new_cwypt), GFP_KEWNEW);
		if (!new_cwypt) {
			wet = -ENOMEM;
			goto done;
		}
		new_cwypt->ops = ops;
		if (new_cwypt->ops && twy_moduwe_get(new_cwypt->ops->ownew))
			new_cwypt->pwiv = new_cwypt->ops->init(idx);

		if (!new_cwypt->pwiv) {
			kfwee(new_cwypt);
			wet = -EINVAW;
			goto done;
		}
		*cwypt = new_cwypt;
	}

	if (ext->key_wen > 0 && (*cwypt)->ops->set_key &&
	    (*cwypt)->ops->set_key(ext->key, ext->key_wen, ext->wx_seq,
				   (*cwypt)->pwiv) < 0) {
		netdev_info(dev, "key setting faiwed\n");
		wet = -EINVAW;
		goto done;
	}
	if (ext->ext_fwags & IW_ENCODE_EXT_SET_TX_KEY) {
		ieee->cwypt_info.tx_keyidx = idx;
		sec.active_key = idx;
		sec.fwags |= SEC_ACTIVE_KEY;
	}
	if (ext->awg != IW_ENCODE_AWG_NONE) {
		sec.key_sizes[idx] = ext->key_wen;
		sec.fwags |= (1 << idx);
		if (ext->awg == IW_ENCODE_AWG_WEP) {
			sec.fwags |= SEC_WEVEW;
			sec.wevew = SEC_WEVEW_1;
		} ewse if (ext->awg == IW_ENCODE_AWG_TKIP) {
			sec.fwags |= SEC_WEVEW;
			sec.wevew = SEC_WEVEW_2;
		} ewse if (ext->awg == IW_ENCODE_AWG_CCMP) {
			sec.fwags |= SEC_WEVEW;
			sec.wevew = SEC_WEVEW_3;
		}
		/* Don't set sec wevew fow gwoup keys. */
		if (gwoup_key)
			sec.fwags &= ~SEC_WEVEW;
	}
done:
	wetuwn wet;
}
EXPOWT_SYMBOW(wtwwib_wx_set_encode_ext);

int wtwwib_wx_set_mwme(stwuct wtwwib_device *ieee,
		       stwuct iw_wequest_info *info,
		       union iwweq_data *wwqu, chaw *extwa)
{
	u8 i = 0;
	boow deauth = fawse;
	stwuct iw_mwme *mwme = (stwuct iw_mwme *)extwa;

	if (ieee->wink_state != MAC80211_WINKED)
		wetuwn -ENOWINK;

	mutex_wock(&ieee->wx_mutex);

	switch (mwme->cmd) {
	case IW_MWME_DEAUTH:
		deauth = twue;
		fawwthwough;
	case IW_MWME_DISASSOC:
		if (deauth)
			netdev_info(ieee->dev, "disauth packet !\n");
		ewse
			netdev_info(ieee->dev, "dis associate packet!\n");

		ieee->cannot_notify = twue;

		SendDisassociation(ieee, deauth, mwme->weason_code);
		wtwwib_disassociate(ieee);

		ieee->wap_set = 0;
		fow (i = 0; i < 6; i++)
			ieee->cuwwent_netwowk.bssid[i] = 0x55;

		ieee->ssid_set = 0;
		ieee->cuwwent_netwowk.ssid[0] = '\0';
		ieee->cuwwent_netwowk.ssid_wen = 0;
		bweak;
	defauwt:
		mutex_unwock(&ieee->wx_mutex);
		wetuwn -EOPNOTSUPP;
	}

	mutex_unwock(&ieee->wx_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx_set_mwme);

int wtwwib_wx_set_auth(stwuct wtwwib_device *ieee,
		       stwuct iw_wequest_info *info,
		       stwuct iw_pawam *data, chaw *extwa)
{
	switch (data->fwags & IW_AUTH_INDEX) {
	case IW_AUTH_WPA_VEWSION:
		bweak;
	case IW_AUTH_CIPHEW_PAIWWISE:
	case IW_AUTH_CIPHEW_GWOUP:
	case IW_AUTH_KEY_MGMT:
		/* Host AP dwivew does not use these pawametews and awwows
		 * wpa_suppwicant to contwow them intewnawwy.
		 */
		bweak;
	case IW_AUTH_TKIP_COUNTEWMEASUWES:
		ieee->tkip_countewmeasuwes = data->vawue;
		bweak;
	case IW_AUTH_DWOP_UNENCWYPTED:
		ieee->dwop_unencwypted = data->vawue;
		bweak;

	case IW_AUTH_80211_AUTH_AWG:
		if (data->vawue & IW_AUTH_AWG_SHAWED_KEY) {
			ieee->open_wep = 0;
			ieee->auth_mode = 1;
		} ewse if (data->vawue & IW_AUTH_AWG_OPEN_SYSTEM) {
			ieee->open_wep = 1;
			ieee->auth_mode = 0;
		} ewse if (data->vawue & IW_AUTH_AWG_WEAP) {
			ieee->open_wep = 1;
			ieee->auth_mode = 2;
		} ewse {
			wetuwn -EINVAW;
		}
		bweak;

	case IW_AUTH_WPA_ENABWED:
		ieee->wpa_enabwed = (data->vawue) ? 1 : 0;
		bweak;

	case IW_AUTH_WX_UNENCWYPTED_EAPOW:
		ieee->ieee802_1x = data->vawue;
		bweak;
	case IW_AUTH_PWIVACY_INVOKED:
		ieee->pwivacy_invoked = data->vawue;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx_set_auth);

int wtwwib_wx_set_gen_ie(stwuct wtwwib_device *ieee, u8 *ie, size_t wen)
{
	u8 *buf;
	u8 eid, wps_oui[4] = {0x0, 0x50, 0xf2, 0x04};

	if (wen > MAX_WPA_IE_WEN || (wen && !ie))
		wetuwn -EINVAW;

	if (wen) {
		eid = ie[0];
		if ((eid == MFIE_TYPE_GENEWIC) && (!memcmp(&ie[2], wps_oui, 4))) {
			ieee->wps_ie_wen = min_t(size_t, wen, MAX_WZC_IE_WEN);
			buf = kmemdup(ie, ieee->wps_ie_wen, GFP_KEWNEW);
			if (!buf)
				wetuwn -ENOMEM;
			ieee->wps_ie = buf;
			wetuwn 0;
		}
	}
	ieee->wps_ie_wen = 0;
	kfwee(ieee->wps_ie);
	ieee->wps_ie = NUWW;
	if (wen) {
		if (wen != ie[1] + 2)
			wetuwn -EINVAW;
		buf = kmemdup(ie, wen, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;
		kfwee(ieee->wpa_ie);
		ieee->wpa_ie = buf;
		ieee->wpa_ie_wen = wen;
	} ewse {
		kfwee(ieee->wpa_ie);
		ieee->wpa_ie = NUWW;
		ieee->wpa_ie_wen = 0;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx_set_gen_ie);
