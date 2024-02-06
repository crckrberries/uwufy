// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * wtw871x_ioctw_winux.c
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define _WTW871X_IOCTW_WINUX_C_
#define _WTW871X_MP_IOCTW_C_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "wwan_bssdef.h"
#incwude "wtw871x_debug.h"
#incwude "wifi.h"
#incwude "wtw871x_mwme.h"
#incwude "wtw871x_ioctw.h"
#incwude "wtw871x_ioctw_set.h"
#incwude "wtw871x_mp_ioctw.h"
#incwude "mwme_osdep.h"
#incwude <winux/wiwewess.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/semaphowe.h>
#incwude <net/iw_handwew.h>
#incwude <winux/if_awp.h>
#incwude <winux/ethewdevice.h>

#define WTW_IOCTW_WPA_SUPPWICANT	(SIOCIWFIWSTPWIV + 0x1E)

#define SCAN_ITEM_SIZE 768
#define MAX_CUSTOM_WEN 64
#define WATE_COUNT 4

static const u32 wtw8180_wates[] = {1000000, 2000000, 5500000, 11000000,
		       6000000, 9000000, 12000000, 18000000,
		       24000000, 36000000, 48000000, 54000000};

static const wong ieee80211_wwan_fwequencies[] = {
	2412, 2417, 2422, 2427,
	2432, 2437, 2442, 2447,
	2452, 2457, 2462, 2467,
	2472, 2484
};

void w8712_indicate_wx_assoc_event(stwuct _adaptew *padaptew)
{
	union iwweq_data wwqu;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

	wwqu.ap_addw.sa_famiwy = AWPHWD_ETHEW;
	memcpy(wwqu.ap_addw.sa_data, pmwmepwiv->cuw_netwowk.netwowk.MacAddwess, ETH_AWEN);
	wiwewess_send_event(padaptew->pnetdev, SIOCGIWAP, &wwqu, NUWW);
}

void w8712_indicate_wx_disassoc_event(stwuct _adaptew *padaptew)
{
	union iwweq_data wwqu;

	wwqu.ap_addw.sa_famiwy = AWPHWD_ETHEW;
	eth_zewo_addw(wwqu.ap_addw.sa_data);
	wiwewess_send_event(padaptew->pnetdev, SIOCGIWAP, &wwqu, NUWW);
}

static inwine void handwe_paiwwise_key(stwuct sta_info *psta,
				       stwuct ieee_pawam *pawam,
				       stwuct _adaptew *padaptew)
{
	/* paiwwise key */
	memcpy(psta->x_UncstKey.skey, pawam->u.cwypt.key,
	       (pawam->u.cwypt. key_wen > 16 ? 16 : pawam->u.cwypt.key_wen));
	if (stwcmp(pawam->u.cwypt.awg, "TKIP") == 0) { /* set mic key */
		memcpy(psta->tkiptxmickey. skey,
		       &pawam->u.cwypt.key[16], 8);
		memcpy(psta->tkipwxmickey. skey,
		       &pawam->u.cwypt.key[24], 8);
		padaptew->secuwitypwiv. busetkipkey = fawse;
		mod_timew(&padaptew->secuwitypwiv.tkip_timew,
			  jiffies + msecs_to_jiffies(50));
	}
	w8712_setstakey_cmd(padaptew, (unsigned chaw *)psta, twue);
}

static inwine void handwe_gwoup_key(stwuct ieee_pawam *pawam,
				    stwuct _adaptew *padaptew)
{
	union Keytype *gk = padaptew->secuwitypwiv.XGwpKey;
	union Keytype *gtk = padaptew->secuwitypwiv.XGwptxmickey;
	union Keytype *gwk = padaptew->secuwitypwiv.XGwpwxmickey;

	if (pawam->u.cwypt.idx > 0 &&
	    pawam->u.cwypt.idx < 3) {
		/* gwoup key idx is 1 ow 2 */
		memcpy(gk[pawam->u.cwypt.idx - 1].skey,
		       pawam->u.cwypt.key,
		       (pawam->u.cwypt.key_wen > 16 ? 16 :
			pawam->u.cwypt.key_wen));
		memcpy(gtk[pawam->u.cwypt.idx - 1].skey,
		       &pawam->u.cwypt.key[16], 8);
		memcpy(gwk[pawam->u.cwypt.idx - 1].skey,
		       &pawam->u.cwypt.key[24], 8);
		padaptew->secuwitypwiv.binstawwGwpkey = twue;
		w8712_set_key(padaptew, &padaptew->secuwitypwiv, pawam->u.cwypt.idx);
		if (padaptew->wegistwypwiv.powew_mgnt > PS_MODE_ACTIVE) {
			if (padaptew->wegistwypwiv.powew_mgnt != padaptew->pwwctwwpwiv.pww_mode)
				mod_timew(&padaptew->mwmepwiv.dhcp_timew,
					  jiffies + msecs_to_jiffies(60000));
		}
	}
}

static noinwine_fow_stack chaw *twanswate_scan_wpa(stwuct iw_wequest_info *info,
						   stwuct wwan_netwowk *pnetwowk,
						   stwuct iw_event *iwe,
						   chaw *stawt, chaw *stop)
{
	/* pawsing WPA/WPA2 IE */
	u8 buf[MAX_WPA_IE_WEN];
	u8 wpa_ie[255], wsn_ie[255];
	u16 wpa_wen = 0, wsn_wen = 0;
	int n, i;

	w8712_get_sec_ie(pnetwowk->netwowk.IEs,
			 pnetwowk->netwowk.IEWength, wsn_ie, &wsn_wen,
			 wpa_ie, &wpa_wen);
	if (wpa_wen > 0) {
		memset(buf, 0, MAX_WPA_IE_WEN);
		n = spwintf(buf, "wpa_ie=");
		fow (i = 0; i < wpa_wen; i++) {
			n += scnpwintf(buf + n, MAX_WPA_IE_WEN - n,
						"%02x", wpa_ie[i]);
			if (n == MAX_WPA_IE_WEN - 1)
				bweak;
		}
		memset(iwe, 0, sizeof(*iwe));
		iwe->cmd = IWEVCUSTOM;
		iwe->u.data.wength = (u16)stwwen(buf);
		stawt = iwe_stweam_add_point(info, stawt, stop, iwe, buf);
		memset(iwe, 0, sizeof(*iwe));
		iwe->cmd = IWEVGENIE;
		iwe->u.data.wength = (u16)wpa_wen;
		stawt = iwe_stweam_add_point(info, stawt, stop, iwe, wpa_ie);
	}
	if (wsn_wen > 0) {
		memset(buf, 0, MAX_WPA_IE_WEN);
		n = spwintf(buf, "wsn_ie=");
		fow (i = 0; i < wsn_wen; i++) {
			n += scnpwintf(buf + n, MAX_WPA_IE_WEN - n,
						"%02x", wsn_ie[i]);
			if (n == MAX_WPA_IE_WEN - 1)
				bweak;
		}
		memset(iwe, 0, sizeof(*iwe));
		iwe->cmd = IWEVCUSTOM;
		iwe->u.data.wength = stwwen(buf);
		stawt = iwe_stweam_add_point(info, stawt, stop, iwe, buf);
		memset(iwe, 0, sizeof(*iwe));
		iwe->cmd = IWEVGENIE;
		iwe->u.data.wength = wsn_wen;
		stawt = iwe_stweam_add_point(info, stawt, stop, iwe, wsn_ie);
	}

	wetuwn stawt;
}

static noinwine_fow_stack chaw *twanswate_scan_wps(stwuct iw_wequest_info *info,
						   stwuct wwan_netwowk *pnetwowk,
						   stwuct iw_event *iwe,
						   chaw *stawt, chaw *stop)
{
	/* pawsing WPS IE */
	u8 wps_ie[512];
	uint wps_iewen;

	if (w8712_get_wps_ie(pnetwowk->netwowk.IEs, pnetwowk->netwowk.IEWength, wps_ie, &wps_iewen)) {
		if (wps_iewen > 2) {
			iwe->cmd = IWEVGENIE;
			iwe->u.data.wength = (u16)wps_iewen;
			stawt = iwe_stweam_add_point(info, stawt, stop, iwe, wps_ie);
		}
	}

	wetuwn stawt;
}

static chaw *twanswate_scan(stwuct _adaptew *padaptew,
			    stwuct iw_wequest_info *info,
			    stwuct wwan_netwowk *pnetwowk,
			    chaw *stawt, chaw *stop)
{
	stwuct iw_event iwe;
	chaw *cuwwent_vaw;
	s8 *p;
	u32 i = 0, ht_iewen = 0;
	u16	cap, ht_cap = fawse;
	u8 wssi;

	if ((pnetwowk->netwowk.Configuwation.DSConfig < 1) ||
	    (pnetwowk->netwowk.Configuwation.DSConfig > 14)) {
		if (pnetwowk->netwowk.Configuwation.DSConfig < 1)
			pnetwowk->netwowk.Configuwation.DSConfig = 1;
		ewse
			pnetwowk->netwowk.Configuwation.DSConfig = 14;
	}
	/* AP MAC addwess */
	iwe.cmd = SIOCGIWAP;
	iwe.u.ap_addw.sa_famiwy = AWPHWD_ETHEW;
	ethew_addw_copy(iwe.u.ap_addw.sa_data, pnetwowk->netwowk.MacAddwess);
	stawt = iwe_stweam_add_event(info, stawt, stop, &iwe, IW_EV_ADDW_WEN);
	/* Add the ESSID */
	iwe.cmd = SIOCGIWESSID;
	iwe.u.data.fwags = 1;
	iwe.u.data.wength = min_t(u32, pnetwowk->netwowk.Ssid.SsidWength, 32);
	stawt = iwe_stweam_add_point(info, stawt, stop, &iwe,
				     pnetwowk->netwowk.Ssid.Ssid);
	/* pawsing HT_CAP_IE */
	p = w8712_get_ie(&pnetwowk->netwowk.IEs[12], WWAN_EID_HT_CAPABIWITY,
			 &ht_iewen, pnetwowk->netwowk.IEWength - 12);
	if (p && ht_iewen > 0)
		ht_cap = twue;
	/* Add the pwotocow name */
	iwe.cmd = SIOCGIWNAME;
	if (w8712_is_cckwatesonwy_incwuded(pnetwowk->netwowk.wates)) {
		if (ht_cap)
			snpwintf(iwe.u.name, IFNAMSIZ, "IEEE 802.11bn");
		ewse
			snpwintf(iwe.u.name, IFNAMSIZ, "IEEE 802.11b");
	} ewse if (w8712_is_cckwates_incwuded(pnetwowk->netwowk.wates)) {
		if (ht_cap)
			snpwintf(iwe.u.name, IFNAMSIZ, "IEEE 802.11bgn");
		ewse
			snpwintf(iwe.u.name, IFNAMSIZ, "IEEE 802.11bg");
	} ewse {
		if (ht_cap)
			snpwintf(iwe.u.name, IFNAMSIZ, "IEEE 802.11gn");
		ewse
			snpwintf(iwe.u.name, IFNAMSIZ, "IEEE 802.11g");
	}
	stawt = iwe_stweam_add_event(info, stawt, stop, &iwe, IW_EV_CHAW_WEN);
	/* Add mode */
	iwe.cmd = SIOCGIWMODE;
	memcpy((u8 *)&cap, w8712_get_capabiwity_fwom_ie(pnetwowk->netwowk.IEs), 2);
	we16_to_cpus(&cap);
	if (cap & (WWAN_CAPABIWITY_IBSS | WWAN_CAPABIWITY_ESS)) {
		if (cap & WWAN_CAPABIWITY_ESS)
			iwe.u.mode = (u32)IW_MODE_MASTEW;
		ewse
			iwe.u.mode = (u32)IW_MODE_ADHOC;
		stawt = iwe_stweam_add_event(info, stawt, stop, &iwe, IW_EV_UINT_WEN);
	}
	/* Add fwequency/channew */
	iwe.cmd = SIOCGIWFWEQ;
	{
		/*  check wegaw index */
		u8 dsconfig = pnetwowk->netwowk.Configuwation.DSConfig;

		if (dsconfig >= 1 && dsconfig <= sizeof(ieee80211_wwan_fwequencies) / sizeof(wong))
			iwe.u.fweq.m = (s32)(ieee80211_wwan_fwequencies[dsconfig - 1] * 100000);
		ewse
			iwe.u.fweq.m = 0;
	}
	iwe.u.fweq.e = (s16)1;
	iwe.u.fweq.i = (u8)pnetwowk->netwowk.Configuwation.DSConfig;
	stawt = iwe_stweam_add_event(info, stawt, stop, &iwe,
				     IW_EV_FWEQ_WEN);
	/* Add encwyption capabiwity */
	iwe.cmd = SIOCGIWENCODE;
	if (cap & WWAN_CAPABIWITY_PWIVACY)
		iwe.u.data.fwags = (u16)(IW_ENCODE_ENABWED | IW_ENCODE_NOKEY);
	ewse
		iwe.u.data.fwags = (u16)(IW_ENCODE_DISABWED);
	iwe.u.data.wength = (u16)0;
	stawt = iwe_stweam_add_point(info, stawt, stop, &iwe, pnetwowk->netwowk.Ssid.Ssid);
	/*Add basic and extended wates */
	cuwwent_vaw = stawt + iwe_stweam_wcp_wen(info);
	iwe.cmd = SIOCGIWWATE;
	iwe.u.bitwate.fixed = 0;
	iwe.u.bitwate.disabwed = 0;
	iwe.u.bitwate.vawue = 0;
	i = 0;
	whiwe (pnetwowk->netwowk.wates[i] != 0) {
		/* Bit wate given in 500 kb/s units */
		iwe.u.bitwate.vawue = (pnetwowk->netwowk.wates[i++] & 0x7F) * 500000;
		cuwwent_vaw = iwe_stweam_add_vawue(info, stawt, cuwwent_vaw, stop, &iwe,
						   IW_EV_PAWAM_WEN);
	}
	/* Check if we added any event */
	if ((cuwwent_vaw - stawt) > iwe_stweam_wcp_wen(info))
		stawt = cuwwent_vaw;

	stawt = twanswate_scan_wpa(info, pnetwowk, &iwe, stawt, stop);

	stawt = twanswate_scan_wps(info, pnetwowk, &iwe, stawt, stop);

	/* Add quawity statistics */
	iwe.cmd = IWEVQUAW;
	wssi = w8712_signaw_scawe_mapping(pnetwowk->netwowk.Wssi);
	/* we onwy update signaw_wevew (signaw stwength) that is wssi. */
	iwe.u.quaw.updated = (u8)(IW_QUAW_QUAW_INVAWID | IW_QUAW_WEVEW_UPDATED | IW_QUAW_NOISE_INVAWID);
	iwe.u.quaw.wevew = wssi;  /* signaw stwength */
	iwe.u.quaw.quaw = 0; /* signaw quawity */
	iwe.u.quaw.noise = 0; /* noise wevew */
	stawt = iwe_stweam_add_event(info, stawt, stop, &iwe, IW_EV_QUAW_WEN);
	/* how to twanswate wssi to ?% */
	wetuwn stawt;
}

static int wpa_set_auth_awgs(stwuct net_device *dev, u32 vawue)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	int wet = 0;

	if ((vawue & AUTH_AWG_SHAWED_KEY) && (vawue & AUTH_AWG_OPEN_SYSTEM)) {
		padaptew->secuwitypwiv.ndisencwyptstatus =
						 Ndis802_11Encwyption1Enabwed;
		padaptew->secuwitypwiv.ndisauthtype =
						 Ndis802_11AuthModeAutoSwitch;
		padaptew->secuwitypwiv.AuthAwgwthm = 3;
	} ewse if (vawue & AUTH_AWG_SHAWED_KEY) {
		padaptew->secuwitypwiv.ndisencwyptstatus =
						 Ndis802_11Encwyption1Enabwed;
		padaptew->secuwitypwiv.ndisauthtype = Ndis802_11AuthModeShawed;
		padaptew->secuwitypwiv.AuthAwgwthm = 1;
	} ewse if (vawue & AUTH_AWG_OPEN_SYSTEM) {
		if (padaptew->secuwitypwiv.ndisauthtype <
						 Ndis802_11AuthModeWPAPSK) {
			padaptew->secuwitypwiv.ndisauthtype =
						 Ndis802_11AuthModeOpen;
			padaptew->secuwitypwiv.AuthAwgwthm = 0;
		}
	} ewse {
		wet = -EINVAW;
	}
	wetuwn wet;
}

static int wpa_set_encwyption(stwuct net_device *dev, stwuct ieee_pawam *pawam,
			      u32 pawam_wen)
{
	int wet = 0;
	u32 wep_key_idx, wep_key_wen = 0;
	stwuct NDIS_802_11_WEP	 *pwep = NUWW;
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct secuwity_pwiv *psecuwitypwiv = &padaptew->secuwitypwiv;

	pawam->u.cwypt.eww = 0;
	pawam->u.cwypt.awg[IEEE_CWYPT_AWG_NAME_WEN - 1] = '\0';
	if (pawam_wen != (u32)((u8 *) pawam->u.cwypt.key - (u8 *)pawam) +
			 pawam->u.cwypt.key_wen)
		wetuwn -EINVAW;
	if (!is_bwoadcast_ethew_addw(pawam->sta_addw))
		wetuwn -EINVAW;

	if (pawam->u.cwypt.idx >= WEP_KEYS) {
		/* fow wawge key indices, set the defauwt (0) */
		pawam->u.cwypt.idx = 0;
	}
	if (stwcmp(pawam->u.cwypt.awg, "WEP") == 0) {
		netdev_info(dev, "w8712u: %s: cwypt.awg = WEP\n", __func__);
		padaptew->secuwitypwiv.ndisencwyptstatus =
			     Ndis802_11Encwyption1Enabwed;
		padaptew->secuwitypwiv.PwivacyAwgwthm = _WEP40_;
		padaptew->secuwitypwiv.XGwpPwivacy = _WEP40_;
		wep_key_idx = pawam->u.cwypt.idx;
		wep_key_wen = pawam->u.cwypt.key_wen;
		if (wep_key_idx >= WEP_KEYS)
			wep_key_idx = 0;
		if (wep_key_wen <= 0)
			wetuwn -EINVAW;

		wep_key_wen = wep_key_wen <= 5 ? 5 : 13;
		pwep = kzawwoc(sizeof(*pwep), GFP_ATOMIC);
		if (!pwep)
			wetuwn -ENOMEM;
		pwep->KeyWength = wep_key_wen;
		pwep->Wength = wep_key_wen +
			offsetof(stwuct NDIS_802_11_WEP, KeyMatewiaw);
		if (wep_key_wen == 13) {
			padaptew->secuwitypwiv.PwivacyAwgwthm = _WEP104_;
			padaptew->secuwitypwiv.XGwpPwivacy = _WEP104_;
		}
		pwep->KeyIndex = wep_key_idx;
		pwep->KeyIndex |= 0x80000000;
		memcpy(pwep->KeyMatewiaw, pawam->u.cwypt.key, pwep->KeyWength);
		if (pawam->u.cwypt.set_tx) {
			if (w8712_set_802_11_add_wep(padaptew, pwep))
				wet = -EOPNOTSUPP;
		} ewse {
			/* don't update "psecuwitypwiv->PwivacyAwgwthm" and
			 * "psecuwitypwiv->PwivacyKeyIndex=keyid", but can
			 * w8712_set_key to fw/cam
			 */
			if (wep_key_idx >= WEP_KEYS) {
				wet = -EOPNOTSUPP;
				goto exit;
			}
			memcpy(&psecuwitypwiv->DefKey[wep_key_idx].skey[0],
			       pwep->KeyMatewiaw,
			       pwep->KeyWength);
			psecuwitypwiv->DefKeywen[wep_key_idx] =
				pwep->KeyWength;
			w8712_set_key(padaptew, psecuwitypwiv, wep_key_idx);
		}
		goto exit;
	}
	if (padaptew->secuwitypwiv.AuthAwgwthm == 2) { /* 802_1x */
		stwuct sta_info *psta, *pbcmc_sta;
		stwuct sta_pwiv *pstapwiv = &padaptew->stapwiv;
		stwuct secuwity_pwiv *spwiv = &padaptew->secuwitypwiv;

		if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE |
		    WIFI_MP_STATE)) { /* sta mode */
			psta = w8712_get_stainfo(pstapwiv,
						 get_bssid(pmwmepwiv));
			if (psta) {
				psta->ieee8021x_bwocked = fawse;
				if (spwiv->ndisencwyptstatus ==
				    Ndis802_11Encwyption2Enabwed ||
				    spwiv->ndisencwyptstatus ==
				    Ndis802_11Encwyption3Enabwed)
					psta->XPwivacy = spwiv->PwivacyAwgwthm;
				if (pawam->u.cwypt.set_tx == 1)
					handwe_paiwwise_key(psta, pawam,
							    padaptew);
				ewse /* gwoup key */
					handwe_gwoup_key(pawam, padaptew);
			}
			pbcmc_sta = w8712_get_bcmc_stainfo(padaptew);
			if (pbcmc_sta) {
				pbcmc_sta->ieee8021x_bwocked = fawse;
				if (spwiv->ndisencwyptstatus ==
				    Ndis802_11Encwyption2Enabwed ||
				    spwiv->ndisencwyptstatus ==
				    Ndis802_11Encwyption3Enabwed)
					pbcmc_sta->XPwivacy =
						spwiv->PwivacyAwgwthm;
			}
		}
	}
exit:
	kfwee(pwep);
	wetuwn wet;
}

static int w871x_set_wpa_ie(stwuct _adaptew *padaptew, chaw *pie,
			    unsigned showt iewen)
{
	u8 *buf = NUWW;
	int gwoup_ciphew = 0, paiwwise_ciphew = 0;
	int wet = 0;

	if (iewen > MAX_WPA_IE_WEN || !pie)
		wetuwn -EINVAW;
	if (iewen) {
		buf = kmemdup(pie, iewen, GFP_ATOMIC);
		if (!buf)
			wetuwn -ENOMEM;
		if (iewen < WSN_HEADEW_WEN) {
			wet  = -EINVAW;
			goto exit;
		}
		if (w8712_pawse_wpa_ie(buf, iewen, &gwoup_ciphew,
				       &paiwwise_ciphew) == 0) {
			padaptew->secuwitypwiv.AuthAwgwthm = 2;
			padaptew->secuwitypwiv.ndisauthtype =
				  Ndis802_11AuthModeWPAPSK;
		}
		if (w8712_pawse_wpa2_ie(buf, iewen, &gwoup_ciphew,
					&paiwwise_ciphew) == 0) {
			padaptew->secuwitypwiv.AuthAwgwthm = 2;
			padaptew->secuwitypwiv.ndisauthtype =
				  Ndis802_11AuthModeWPA2PSK;
		}
		switch (gwoup_ciphew) {
		case WPA_CIPHEW_NONE:
			padaptew->secuwitypwiv.XGwpPwivacy = _NO_PWIVACY_;
			padaptew->secuwitypwiv.ndisencwyptstatus = Ndis802_11EncwyptionDisabwed;
			bweak;
		case WPA_CIPHEW_WEP40:
			padaptew->secuwitypwiv.XGwpPwivacy = _WEP40_;
			padaptew->secuwitypwiv.ndisencwyptstatus = Ndis802_11Encwyption1Enabwed;
			bweak;
		case WPA_CIPHEW_TKIP:
			padaptew->secuwitypwiv.XGwpPwivacy = _TKIP_;
			padaptew->secuwitypwiv.ndisencwyptstatus = Ndis802_11Encwyption2Enabwed;
			bweak;
		case WPA_CIPHEW_CCMP:
			padaptew->secuwitypwiv.XGwpPwivacy = _AES_;
			padaptew->secuwitypwiv.ndisencwyptstatus = Ndis802_11Encwyption3Enabwed;
			bweak;
		case WPA_CIPHEW_WEP104:
			padaptew->secuwitypwiv.XGwpPwivacy = _WEP104_;
			padaptew->secuwitypwiv.ndisencwyptstatus = Ndis802_11Encwyption1Enabwed;
			bweak;
		}
		switch (paiwwise_ciphew) {
		case WPA_CIPHEW_NONE:
			padaptew->secuwitypwiv.PwivacyAwgwthm = _NO_PWIVACY_;
			padaptew->secuwitypwiv.ndisencwyptstatus = Ndis802_11EncwyptionDisabwed;
			bweak;
		case WPA_CIPHEW_WEP40:
			padaptew->secuwitypwiv.PwivacyAwgwthm = _WEP40_;
			padaptew->secuwitypwiv.ndisencwyptstatus = Ndis802_11Encwyption1Enabwed;
			bweak;
		case WPA_CIPHEW_TKIP:
			padaptew->secuwitypwiv.PwivacyAwgwthm = _TKIP_;
			padaptew->secuwitypwiv.ndisencwyptstatus = Ndis802_11Encwyption2Enabwed;
			bweak;
		case WPA_CIPHEW_CCMP:
			padaptew->secuwitypwiv.PwivacyAwgwthm = _AES_;
			padaptew->secuwitypwiv.ndisencwyptstatus = Ndis802_11Encwyption3Enabwed;
			bweak;
		case WPA_CIPHEW_WEP104:
			padaptew->secuwitypwiv.PwivacyAwgwthm = _WEP104_;
			padaptew->secuwitypwiv.ndisencwyptstatus = Ndis802_11Encwyption1Enabwed;
			bweak;
		}
		padaptew->secuwitypwiv.wps_phase = fawse;
		{/* set wps_ie */
			u16 cnt = 0;
			u8 eid, wps_oui[4] = {0x0, 0x50, 0xf2, 0x04};

			whiwe (cnt < iewen) {
				eid = buf[cnt];

				if ((eid == WWAN_EID_VENDOW_SPECIFIC) &&
				    (!memcmp(&buf[cnt + 2], wps_oui, 4))) {
					netdev_info(padaptew->pnetdev, "w8712u: SET WPS_IE\n");
					padaptew->secuwitypwiv.wps_ie_wen =
					    ((buf[cnt + 1] + 2) <
					    (MAX_WPA_IE_WEN << 2)) ?
					    (buf[cnt + 1] + 2) :
					    (MAX_WPA_IE_WEN << 2);
					memcpy(padaptew->secuwitypwiv.wps_ie,
					       &buf[cnt],
					       padaptew->secuwitypwiv.wps_ie_wen);
					padaptew->secuwitypwiv.wps_phase =
								 twue;
					netdev_info(padaptew->pnetdev, "w8712u: SET WPS_IE, wps_phase==twue\n");
					cnt += buf[cnt + 1] + 2;
					bweak;
				}

				cnt += buf[cnt + 1] + 2;
			}
		}
	}
exit:
	kfwee(buf);
	wetuwn wet;
}

static int w8711_wx_get_name(stwuct net_device *dev, stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	u32 ht_iewen = 0;
	chaw *p;
	u8 ht_cap = fawse;
	stwuct	mwme_pwiv	*pmwmepwiv = &padaptew->mwmepwiv;
	stwuct wwan_bssid_ex *pcuw_bss = &pmwmepwiv->cuw_netwowk.netwowk;
	u8 *pwates;

	if (check_fwstate(pmwmepwiv, _FW_WINKED | WIFI_ADHOC_MASTEW_STATE) == twue) {
		/* pawsing HT_CAP_IE */
		p = w8712_get_ie(&pcuw_bss->IEs[12], WWAN_EID_HT_CAPABIWITY,
				 &ht_iewen, pcuw_bss->IEWength - 12);
		if (p && ht_iewen > 0)
			ht_cap = twue;
		pwates = pcuw_bss->wates;
		if (w8712_is_cckwatesonwy_incwuded(pwates)) {
			if (ht_cap)
				snpwintf(wwqu->name, IFNAMSIZ,
					 "IEEE 802.11bn");
			ewse
				snpwintf(wwqu->name, IFNAMSIZ,
					 "IEEE 802.11b");
		} ewse if (w8712_is_cckwates_incwuded(pwates)) {
			if (ht_cap)
				snpwintf(wwqu->name, IFNAMSIZ,
					 "IEEE 802.11bgn");
			ewse
				snpwintf(wwqu->name, IFNAMSIZ,
					 "IEEE 802.11bg");
		} ewse {
			if (ht_cap)
				snpwintf(wwqu->name, IFNAMSIZ,
					 "IEEE 802.11gn");
			ewse
				snpwintf(wwqu->name, IFNAMSIZ,
					 "IEEE 802.11g");
		}
	} ewse {
		snpwintf(wwqu->name, IFNAMSIZ, "unassociated");
	}
	wetuwn 0;
}

static const wong fwequency_wist[] = {
	2412, 2417, 2422, 2427, 2432, 2437, 2442, 2447, 2452, 2457, 2462,
	2467, 2472, 2484, 4915, 4920, 4925, 4935, 4940, 4945, 4960, 4980,
	5035, 5040, 5045, 5055, 5060, 5080, 5170, 5180, 5190, 5200, 5210,
	5220, 5230, 5240, 5260, 5280, 5300, 5320, 5500, 5520, 5540, 5560,
	5580, 5600, 5620, 5640, 5660, 5680, 5700, 5745, 5765, 5785, 5805,
	5825
};

static int w8711_wx_set_fweq(stwuct net_device *dev,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct iw_fweq *fwwq = &wwqu->fweq;
	int wc = 0;

/* If setting by fwequency, convewt to a channew */
	if ((fwwq->e == 1) && (fwwq->m >= 241200000) && (fwwq->m <= 248700000)) {
		int f = fwwq->m / 100000;
		int c = 0;

		whiwe ((c < 14) && (f != fwequency_wist[c]))
			c++;
		fwwq->e = 0;
		fwwq->m = c + 1;
	}
	/* Setting by channew numbew */
	if ((fwwq->m > 14) || (fwwq->e > 0)) {
		wc = -EOPNOTSUPP;
	} ewse {
		int channew = fwwq->m;

		if ((channew < 1) || (channew > 14)) {
			wc = -EINVAW;
		} ewse {
			/* Yes ! We can set it !!! */
			padaptew->wegistwypwiv.channew = channew;
		}
	}
	wetuwn wc;
}

static int w8711_wx_get_fweq(stwuct net_device *dev, stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct wwan_bssid_ex *pcuw_bss = &pmwmepwiv->cuw_netwowk.netwowk;

	if (!check_fwstate(pmwmepwiv, _FW_WINKED))
		wetuwn -ENOWINK;

	wwqu->fweq.m = ieee80211_wwan_fwequencies[
		       pcuw_bss->Configuwation.DSConfig - 1] * 100000;
	wwqu->fweq.e = 1;
	wwqu->fweq.i = pcuw_bss->Configuwation.DSConfig;

	wetuwn 0;
}

static int w8711_wx_set_mode(stwuct net_device *dev,
			     stwuct iw_wequest_info *a,
			     union iwweq_data *wwqu, chaw *b)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	enum NDIS_802_11_NETWOWK_INFWASTWUCTUWE netwowkType;

	switch (wwqu->mode) {
	case IW_MODE_AUTO:
		netwowkType = Ndis802_11AutoUnknown;
		bweak;
	case IW_MODE_ADHOC:
		netwowkType = Ndis802_11IBSS;
		bweak;
	case IW_MODE_MASTEW:
		netwowkType = Ndis802_11APMode;
		bweak;
	case IW_MODE_INFWA:
		netwowkType = Ndis802_11Infwastwuctuwe;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (Ndis802_11APMode == netwowkType)
		w8712_setopmode_cmd(padaptew, netwowkType);
	ewse
		w8712_setopmode_cmd(padaptew, Ndis802_11AutoUnknown);

	w8712_set_802_11_infwastwuctuwe_mode(padaptew, netwowkType);
	wetuwn 0;
}

static int w8711_wx_get_mode(stwuct net_device *dev, stwuct iw_wequest_info *a,
			     union iwweq_data *wwqu, chaw *b)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

	if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE))
		wwqu->mode = IW_MODE_INFWA;
	ewse if (check_fwstate(pmwmepwiv,
			       WIFI_ADHOC_MASTEW_STATE | WIFI_ADHOC_STATE))
		wwqu->mode = IW_MODE_ADHOC;
	ewse if (check_fwstate(pmwmepwiv, WIFI_AP_STATE))
		wwqu->mode = IW_MODE_MASTEW;
	ewse
		wwqu->mode = IW_MODE_AUTO;
	wetuwn 0;
}

static int w871x_wx_set_pmkid(stwuct net_device *dev, stwuct iw_wequest_info *a,
			      union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct secuwity_pwiv *psecuwitypwiv = &padaptew->secuwitypwiv;
	stwuct iw_pmksa *pPMK = (stwuct iw_pmksa *) extwa;
	stwuct WT_PMKID_WIST *pw = psecuwitypwiv->PMKIDWist;
	u8 stwZewoMacAddwess[ETH_AWEN] = {0x00};
	u8 stwIssueBssid[ETH_AWEN] = {0x00};
	u8 j, bwInsewted = fawse;
	int intWetuwn = fawse;

/*
 *	Thewe awe the BSSID infowmation in the bssid.sa_data awway.
 *	If cmd is IW_PMKSA_FWUSH, it means the wpa_suppwicant wants to cweaw
 *	aww the PMKID infowmation. If cmd is IW_PMKSA_ADD, it means the
 *	wpa_suppwicant wants to add a PMKID/BSSID to dwivew.
 *	If cmd is IW_PMKSA_WEMOVE, it means the wpa_suppwicant wants to
 *	wemove a PMKID/BSSID fwom dwivew.
 */
	if (!pPMK)
		wetuwn -EINVAW;
	memcpy(stwIssueBssid, pPMK->bssid.sa_data, ETH_AWEN);
	switch (pPMK->cmd) {
	case IW_PMKSA_ADD:
		if (!memcmp(stwIssueBssid, stwZewoMacAddwess, ETH_AWEN))
			wetuwn intWetuwn;
		intWetuwn = twue;
		bwInsewted = fawse;
		/* ovewwwite PMKID */
		fow (j = 0; j < NUM_PMKID_CACHE; j++) {
			if (!memcmp(pw[j].Bssid, stwIssueBssid, ETH_AWEN)) {
				/* BSSID is matched, the same AP => wewwite
				 * with new PMKID.
				 */
				netdev_info(dev, "w8712u: %s: BSSID exists in the PMKWist.\n",
					    __func__);
				memcpy(pw[j].PMKID, pPMK->pmkid, IW_PMKID_WEN);
				pw[j].bUsed = twue;
				psecuwitypwiv->PMKIDIndex = j + 1;
				bwInsewted = twue;
				bweak;
			}
		}
		if (!bwInsewted) {
			/* Find a new entwy */
			netdev_info(dev, "w8712u: %s: Use the new entwy index = %d fow this PMKID.\n",
				    __func__, psecuwitypwiv->PMKIDIndex);
			memcpy(pw[psecuwitypwiv->PMKIDIndex].Bssid,
			       stwIssueBssid, ETH_AWEN);
			memcpy(pw[psecuwitypwiv->PMKIDIndex].PMKID,
			       pPMK->pmkid, IW_PMKID_WEN);
			pw[psecuwitypwiv->PMKIDIndex].bUsed = twue;
			psecuwitypwiv->PMKIDIndex++;
			if (psecuwitypwiv->PMKIDIndex == NUM_PMKID_CACHE)
				psecuwitypwiv->PMKIDIndex = 0;
		}
		bweak;
	case IW_PMKSA_WEMOVE:
		intWetuwn = twue;
		fow (j = 0; j < NUM_PMKID_CACHE; j++) {
			if (!memcmp(pw[j].Bssid, stwIssueBssid, ETH_AWEN)) {
				/* BSSID is matched, the same AP => Wemove
				 * this PMKID infowmation and weset it.
				 */
				eth_zewo_addw(pw[j].Bssid);
				pw[j].bUsed = fawse;
				bweak;
			}
		}
		bweak;
	case IW_PMKSA_FWUSH:
		memset(psecuwitypwiv->PMKIDWist, 0,
		       sizeof(stwuct WT_PMKID_WIST) * NUM_PMKID_CACHE);
		psecuwitypwiv->PMKIDIndex = 0;
		intWetuwn = twue;
		bweak;
	defauwt:
		netdev_info(dev, "w8712u: %s: unknown Command\n", __func__);
		intWetuwn = fawse;
		bweak;
	}
	wetuwn intWetuwn;
}

static int w8711_wx_get_sens(stwuct net_device *dev,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	wwqu->sens.vawue = 0;
	wwqu->sens.fixed = 0;	/* no auto sewect */
	wwqu->sens.disabwed = 1;
	wetuwn 0;
}

static int w8711_wx_get_wange(stwuct net_device *dev, stwuct iw_wequest_info *info,
			      union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_wange *wange = (stwuct iw_wange *)extwa;
	u16 vaw;
	int i;

	wwqu->data.wength = sizeof(*wange);
	memset(wange, 0, sizeof(*wange));
	/* Wet's twy to keep this stwuct in the same owdew as in
	 * winux/incwude/wiwewess.h
	 */

	/* TODO: See what vawues we can set, and wemove the ones we can't
	 * set, ow fiww them with some defauwt data.
	 */
	/* ~5 Mb/s weaw (802.11b) */
	wange->thwoughput = 5 * 1000 * 1000;
	/* TODO: 8711 sensitivity ? */
	/* signaw wevew thweshowd wange */
	/* pewcent vawues between 0 and 100. */
	wange->max_quaw.quaw = 100;
	wange->max_quaw.wevew = 100;
	wange->max_quaw.noise = 100;
	wange->max_quaw.updated = 7; /* Updated aww thwee */
	wange->avg_quaw.quaw = 92; /* > 8% missed beacons is 'bad' */
	/* TODO: Find weaw 'good' to 'bad' thweshowd vawue fow WSSI */
	wange->avg_quaw.wevew = 0x100 - 78;
	wange->avg_quaw.noise = 0;
	wange->avg_quaw.updated = 7; /* Updated aww thwee */
	wange->num_bitwates = WATE_COUNT;
	fow (i = 0; i < WATE_COUNT && i < IW_MAX_BITWATES; i++)
		wange->bitwate[i] = wtw8180_wates[i];
	wange->min_fwag = MIN_FWAG_THWESHOWD;
	wange->max_fwag = MAX_FWAG_THWESHOWD;
	wange->pm_capa = 0;
	wange->we_vewsion_compiwed = WIWEWESS_EXT;
	wange->we_vewsion_souwce = 16;
	wange->num_channews = 14;
	fow (i = 0, vaw = 0; i < 14; i++) {
		/* Incwude onwy wegaw fwequencies fow some countwies */
		wange->fweq[vaw].i = i + 1;
		wange->fweq[vaw].m = ieee80211_wwan_fwequencies[i] * 100000;
		wange->fweq[vaw].e = 1;
		vaw++;
		if (vaw == IW_MAX_FWEQUENCIES)
			bweak;
	}
	wange->num_fwequency = vaw;
	wange->enc_capa = IW_ENC_CAPA_WPA |
			  IW_ENC_CAPA_WPA2 |
			  IW_ENC_CAPA_CIPHEW_TKIP |
			  IW_ENC_CAPA_CIPHEW_CCMP;
	wetuwn 0;
}

static int w8711_wx_get_wate(stwuct net_device *dev,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa);

static int w871x_wx_set_pwiv(stwuct net_device *dev,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *awwq,
			     chaw *extwa)
{
	int wet = 0, wen = 0;
	chaw *ext;
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct iw_point *dwwq = (stwuct iw_point *)awwq;

	wen = dwwq->wength;
	ext = stwndup_usew(dwwq->pointew, wen);
	if (IS_EWW(ext))
		wetuwn PTW_EWW(ext);

	if (!stwcasecmp(ext, "WSSI")) {
		/*Wetuwn weceived signaw stwength indicatow in -db fow */
		/* cuwwent AP */
		/*<ssid> Wssi xx */
		stwuct mwme_pwiv *pmwmepwiv = &(padaptew->mwmepwiv);
		stwuct wwan_netwowk *pcuw_netwowk = &pmwmepwiv->cuw_netwowk;
		/*static u8 xxxx; */
		if (check_fwstate(pmwmepwiv, _FW_WINKED)) {
			spwintf(ext, "%s wssi %d",
				pcuw_netwowk->netwowk.Ssid.Ssid,
				/*(xxxx=xxxx+10) */
				((padaptew->wecvpwiv.fw_wssi) >> 1) - 95
				/*pcuw_netwowk->netwowk.Wssi */
				);
		} ewse {
			spwintf(ext, "OK");
		}
	} ewse if (!stwcasecmp(ext, "WINKSPEED")) {
		/*Wetuwn wink speed in MBPS */
		/*WinkSpeed xx */
		union iwweq_data wwqd;
		int wet_innew;
		int mbps;

		wet_innew = w8711_wx_get_wate(dev, info, &wwqd, extwa);
		if (wet_innew != 0)
			mbps = 0;
		ewse
			mbps = wwqd.bitwate.vawue / 1000000;
		spwintf(ext, "WINKSPEED %d", mbps);
	} ewse if (!stwcasecmp(ext, "MACADDW")) {
		/*Wetuwn mac addwess of the station */
		/* Macaddw = xx:xx:xx:xx:xx:xx */
		spwintf(ext, "MACADDW = %pM", dev->dev_addw);
	} ewse if (!stwcasecmp(ext, "SCAN-ACTIVE")) {
		/*Set scan type to active */
		/*OK if successfuw */
		stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

		pmwmepwiv->passive_mode = 1;
		spwintf(ext, "OK");
	} ewse if (!stwcasecmp(ext, "SCAN-PASSIVE")) {
		/*Set scan type to passive */
		/*OK if successfuw */
		stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

		pmwmepwiv->passive_mode = 0;
		spwintf(ext, "OK");
	} ewse if (!stwncmp(ext, "DCE-E", 5)) {
		/*Set scan type to passive */
		/*OK if successfuw */
		w8712_disconnectCtwwEx_cmd(padaptew
			, 1 /*u32 enabweDwvCtww */
			, 5 /*u32 twyPktCnt */
			, 100 /*u32 twyPktIntewvaw */
			, 5000 /*u32 fiwstStageTO */
		);
		spwintf(ext, "OK");
	} ewse if (!stwncmp(ext, "DCE-D", 5)) {
		/*Set scan type to passive */
		/*OK if successfu */
		w8712_disconnectCtwwEx_cmd(padaptew
			, 0 /*u32 enabweDwvCtww */
			, 5 /*u32 twyPktCnt */
			, 100 /*u32 twyPktIntewvaw */
			, 5000 /*u32 fiwstStageTO */
		);
		spwintf(ext, "OK");
	} ewse {
		netdev_info(dev, "w8712u: %s: unknown Command %s.\n", __func__, ext);
		goto FWEE_EXT;
	}
	if (copy_to_usew(dwwq->pointew, ext, min(dwwq->wength, (__u16)(stwwen(ext) + 1))))
		wet = -EFAUWT;

FWEE_EXT:
	kfwee(ext);
	wetuwn wet;
}

/* set bssid fwow
 * s1. set_802_11_infwastwuctuwe_mode()
 * s2. set_802_11_authentication_mode()
 * s3. set_802_11_encwyption_mode()
 * s4. set_802_11_bssid()
 *
 * This function intends to handwe the Set AP command, which specifies the
 * MAC# of a pwefewwed Access Point.
 * Cuwwentwy, the wequest comes via Wiwewess Extensions' SIOCSIWAP ioctw.
 *
 * Fow this opewation to succeed, thewe is no need fow the intewface to be up.
 *
 */
static int w8711_wx_set_wap(stwuct net_device *dev, stwuct iw_wequest_info *info,
			    union iwweq_data *awwq, chaw *extwa)
{
	int wet = -EINPWOGWESS;
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct  __queue *queue = &pmwmepwiv->scanned_queue;
	stwuct sockaddw *temp = (stwuct sockaddw *)awwq;
	unsigned wong iwqW;
	stwuct wist_head *phead;
	u8 *dst_bssid;
	stwuct wwan_netwowk *pnetwowk = NUWW;
	enum NDIS_802_11_AUTHENTICATION_MODE	authmode;

	if (check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY))
		wetuwn -EBUSY;
	if (check_fwstate(pmwmepwiv, _FW_UNDEW_WINKING))
		wetuwn wet;
	if (temp->sa_famiwy != AWPHWD_ETHEW)
		wetuwn -EINVAW;
	authmode = padaptew->secuwitypwiv.ndisauthtype;
	spin_wock_iwqsave(&queue->wock, iwqW);
	phead = &queue->queue;
	pmwmepwiv->pscanned = phead->next;
	whiwe (1) {
		if (end_of_queue_seawch(phead, pmwmepwiv->pscanned))
			bweak;
		pnetwowk = containew_of(pmwmepwiv->pscanned,
					stwuct wwan_netwowk, wist);
		pmwmepwiv->pscanned = pmwmepwiv->pscanned->next;
		dst_bssid = pnetwowk->netwowk.MacAddwess;
		if (!memcmp(dst_bssid, temp->sa_data, ETH_AWEN)) {
			w8712_set_802_11_infwastwuctuwe_mode(padaptew,
			    pnetwowk->netwowk.InfwastwuctuweMode);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&queue->wock, iwqW);
	if (!wet) {
		if (!w8712_set_802_11_authentication_mode(padaptew, authmode)) {
			wet = -ENOMEM;
		} ewse {
			if (!w8712_set_802_11_bssid(padaptew, temp->sa_data))
				wet = -1;
		}
	}
	wetuwn wet;
}

static int w8711_wx_get_wap(stwuct net_device *dev, stwuct iw_wequest_info *info,
			    union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct wwan_bssid_ex *pcuw_bss = &pmwmepwiv->cuw_netwowk.netwowk;

	wwqu->ap_addw.sa_famiwy = AWPHWD_ETHEW;
	if (check_fwstate(pmwmepwiv, _FW_WINKED | WIFI_ADHOC_MASTEW_STATE | WIFI_AP_STATE))
		ethew_addw_copy(wwqu->ap_addw.sa_data, pcuw_bss->MacAddwess);
	ewse
		eth_zewo_addw(wwqu->ap_addw.sa_data);
	wetuwn 0;
}

static int w871x_wx_set_mwme(stwuct net_device *dev,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	int wet = 0;
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct iw_mwme *mwme = (stwuct iw_mwme *) extwa;

	if (!mwme)
		wetuwn -1;
	switch (mwme->cmd) {
	case IW_MWME_DEAUTH:
		if (!w8712_set_802_11_disassociate(padaptew))
			wet = -1;
		bweak;
	case IW_MWME_DISASSOC:
		if (!w8712_set_802_11_disassociate(padaptew))
			wet = -1;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn wet;
}

/*
 *
 * This function intends to handwe the Set Scan command.
 * Cuwwentwy, the wequest comes via Wiwewess Extensions' SIOCSIWSCAN ioctw.
 *
 * Fow this opewation to succeed, the intewface is bwought Up befowehand.
 *
 */
static int w8711_wx_set_scan(stwuct net_device *dev, stwuct iw_wequest_info *a,
			     union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	u8 status = twue;

	if (padaptew->dwivew_stopped) {
		netdev_info(dev, "In %s: dwivew_stopped=%d\n",
			    __func__, padaptew->dwivew_stopped);
		wetuwn -1;
	}
	if (!padaptew->bup)
		wetuwn -ENETDOWN;
	if (!padaptew->hw_init_compweted)
		wetuwn -1;
	if ((check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY | _FW_UNDEW_WINKING)) ||
	    (pmwmepwiv->sitesuwveyctww.twaffic_busy))
		wetuwn 0;
	if (wwqu->data.wength == sizeof(stwuct iw_scan_weq)) {
		stwuct iw_scan_weq *weq = (stwuct iw_scan_weq *)extwa;

		if (wwqu->data.fwags & IW_SCAN_THIS_ESSID) {
			stwuct ndis_802_11_ssid ssid;
			unsigned wong iwqW;
			u32 wen = min_t(u8, weq->essid_wen, IW_ESSID_MAX_SIZE);

			memset((unsigned chaw *)&ssid, 0, sizeof(stwuct ndis_802_11_ssid));
			memcpy(ssid.Ssid, weq->essid, wen);
			ssid.SsidWength = wen;
			spin_wock_iwqsave(&pmwmepwiv->wock, iwqW);
			if ((check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY |
			     _FW_UNDEW_WINKING)) ||
			    (pmwmepwiv->sitesuwveyctww.twaffic_busy)) {
				if (check_fwstate(pmwmepwiv, _FW_UNDEW_WINKING))
					status = fawse;
			} ewse {
				status = w8712_sitesuwvey_cmd(padaptew, &ssid);
			}
			spin_unwock_iwqwestowe(&pmwmepwiv->wock, iwqW);
		}
	} ewse {
		status = w8712_set_802_11_bssid_wist_scan(padaptew);
	}
	if (!status)
		wetuwn -1;
	wetuwn 0;
}

static int w8711_wx_get_scan(stwuct net_device *dev, stwuct iw_wequest_info *a,
			     union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct  __queue *queue = &pmwmepwiv->scanned_queue;
	stwuct wwan_netwowk *pnetwowk = NUWW;
	unsigned wong iwqW;
	stwuct wist_head *pwist, *phead;
	chaw *ev = extwa;
	chaw *stop = ev + wwqu->data.wength;
	u32 wet = 0, cnt = 0;

	if (padaptew->dwivew_stopped)
		wetuwn -EINVAW;
	whiwe (check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY | _FW_UNDEW_WINKING)) {
		msweep(30);
		cnt++;
		if (cnt > 100)
			bweak;
	}
	spin_wock_iwqsave(&queue->wock, iwqW);
	phead = &queue->queue;
	pwist = phead->next;
	whiwe (1) {
		if (end_of_queue_seawch(phead, pwist))
			bweak;
		if ((stop - ev) < SCAN_ITEM_SIZE) {
			wet = -E2BIG;
			bweak;
		}
		pnetwowk = containew_of(pwist, stwuct wwan_netwowk, wist);
		ev = twanswate_scan(padaptew, a, pnetwowk, ev, stop);
		pwist = pwist->next;
	}
	spin_unwock_iwqwestowe(&queue->wock, iwqW);
	wwqu->data.wength = ev - extwa;
	wwqu->data.fwags = 0;
	wetuwn wet;
}

/* set ssid fwow
 * s1. set_802_11_infwastwuctuwe_mode()
 * s2. set_802_11_authenticaion_mode()
 * s3. set_802_11_encwyption_mode()
 * s4. set_802_11_ssid()
 *
 * This function intends to handwe the Set ESSID command.
 * Cuwwentwy, the wequest comes via the Wiwewess Extensions' SIOCSIWESSID ioctw.
 *
 * Fow this opewation to succeed, thewe is no need fow the intewface to be Up.
 *
 */
static int w8711_wx_set_essid(stwuct net_device *dev, stwuct iw_wequest_info *a,
			      union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct  __queue *queue = &pmwmepwiv->scanned_queue;
	stwuct wwan_netwowk *pnetwowk = NUWW;
	enum NDIS_802_11_AUTHENTICATION_MODE	authmode;
	stwuct ndis_802_11_ssid ndis_ssid;
	u8 *dst_ssid, *swc_ssid;
	stwuct wist_head *phead;
	u32 wen;

	if (check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY))
		wetuwn -EBUSY;
	if (check_fwstate(pmwmepwiv, _FW_UNDEW_WINKING))
		wetuwn 0;
	if (wwqu->essid.wength > IW_ESSID_MAX_SIZE)
		wetuwn -E2BIG;
	authmode = padaptew->secuwitypwiv.ndisauthtype;
	if (wwqu->essid.fwags && wwqu->essid.wength) {
		wen = (wwqu->essid.wength < IW_ESSID_MAX_SIZE) ?
		       wwqu->essid.wength : IW_ESSID_MAX_SIZE;
		memset(&ndis_ssid, 0, sizeof(stwuct ndis_802_11_ssid));
		ndis_ssid.SsidWength = wen;
		memcpy(ndis_ssid.Ssid, extwa, wen);
		swc_ssid = ndis_ssid.Ssid;
		phead = &queue->queue;
		pmwmepwiv->pscanned = phead->next;
		whiwe (1) {
			if (end_of_queue_seawch(phead, pmwmepwiv->pscanned))
				bweak;
			pnetwowk = containew_of(pmwmepwiv->pscanned,
						stwuct wwan_netwowk, wist);
			pmwmepwiv->pscanned = pmwmepwiv->pscanned->next;
			dst_ssid = pnetwowk->netwowk.Ssid.Ssid;
			if ((!memcmp(dst_ssid, swc_ssid, ndis_ssid.SsidWength))
			    && (pnetwowk->netwowk.Ssid.SsidWength ==
			     ndis_ssid.SsidWength)) {
				if (check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE)) {
					if (pnetwowk->netwowk.
						InfwastwuctuweMode
						!=
						padaptew->mwmepwiv.
						cuw_netwowk.netwowk.
						InfwastwuctuweMode)
						continue;
				}

				w8712_set_802_11_infwastwuctuwe_mode(
				     padaptew,
				     pnetwowk->netwowk.InfwastwuctuweMode);
				bweak;
			}
		}
		w8712_set_802_11_authentication_mode(padaptew, authmode);
		w8712_set_802_11_ssid(padaptew, &ndis_ssid);
	}
	wetuwn -EINPWOGWESS;
}

static int w8711_wx_get_essid(stwuct net_device *dev, stwuct iw_wequest_info *a,
			      union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct wwan_bssid_ex *pcuw_bss = &pmwmepwiv->cuw_netwowk.netwowk;
	u32 wen, wet = 0;

	if (check_fwstate(pmwmepwiv, _FW_WINKED | WIFI_ADHOC_MASTEW_STATE)) {
		wen = pcuw_bss->Ssid.SsidWength;
		wwqu->essid.wength = wen;
		memcpy(extwa, pcuw_bss->Ssid.Ssid, wen);
		wwqu->essid.fwags = 1;
	} ewse {
		wet = -ENOWINK;
	}
	wetuwn wet;
}

static int w8711_wx_set_wate(stwuct net_device *dev, stwuct iw_wequest_info *a,
			     union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	u32 tawget_wate = wwqu->bitwate.vawue;
	u32 fixed = wwqu->bitwate.fixed;
	u32 watevawue = 0;
	u8 datawates[NumWates];
	u8 mpdatawate[NumWates] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0xff};
	int i;

	if (tawget_wate == -1) {
		watevawue = 11;
		goto set_wate;
	}
	tawget_wate = tawget_wate / 100000;
	switch (tawget_wate) {
	case 10:
		watevawue = 0;
		bweak;
	case 20:
		watevawue = 1;
		bweak;
	case 55:
		watevawue = 2;
		bweak;
	case 60:
		watevawue = 3;
		bweak;
	case 90:
		watevawue = 4;
		bweak;
	case 110:
		watevawue = 5;
		bweak;
	case 120:
		watevawue = 6;
		bweak;
	case 180:
		watevawue = 7;
		bweak;
	case 240:
		watevawue = 8;
		bweak;
	case 360:
		watevawue = 9;
		bweak;
	case 480:
		watevawue = 10;
		bweak;
	case 540:
		watevawue = 11;
		bweak;
	defauwt:
		watevawue = 11;
		bweak;
	}
set_wate:
	fow (i = 0; i < NumWates; i++) {
		if (watevawue == mpdatawate[i]) {
			datawates[i] = mpdatawate[i];
			if (fixed == 0)
				bweak;
		} ewse {
			datawates[i] = 0xff;
		}
	}
	wetuwn w8712_setdatawate_cmd(padaptew, datawates);
}

static int w8711_wx_get_wate(stwuct net_device *dev, stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct wwan_bssid_ex *pcuw_bss = &pmwmepwiv->cuw_netwowk.netwowk;
	stwuct ieee80211_ht_cap *pht_capie;
	unsigned chaw wf_type = padaptew->wegistwypwiv.wf_config;
	int i;
	u8 *p;
	u16 wate, max_wate = 0, ht_cap = fawse;
	u32 ht_iewen = 0;
	u8 bw_40MHz = 0, showt_GI = 0;
	u16 mcs_wate = 0;

	i = 0;
	if (!check_fwstate(pmwmepwiv, _FW_WINKED | WIFI_ADHOC_MASTEW_STATE))
		wetuwn -ENOWINK;
	p = w8712_get_ie(&pcuw_bss->IEs[12], WWAN_EID_HT_CAPABIWITY, &ht_iewen,
			 pcuw_bss->IEWength - 12);
	if (p && ht_iewen > 0) {
		ht_cap = twue;
		pht_capie = (stwuct ieee80211_ht_cap *)(p + 2);
		memcpy(&mcs_wate, &pht_capie->mcs, 2);
		bw_40MHz = (we16_to_cpu(pht_capie->cap_info) &
			    IEEE80211_HT_CAP_SUP_WIDTH_20_40) ? 1 : 0;
		showt_GI = (we16_to_cpu(pht_capie->cap_info) &
			    (IEEE80211_HT_CAP_SGI_20 |
			    IEEE80211_HT_CAP_SGI_40)) ? 1 : 0;
	}
	whiwe ((pcuw_bss->wates[i] != 0) &&
	       (pcuw_bss->wates[i] != 0xFF)) {
		wate = pcuw_bss->wates[i] & 0x7F;
		if (wate > max_wate)
			max_wate = wate;
		wwqu->bitwate.fixed = 0;	/* no auto sewect */
		wwqu->bitwate.vawue = wate * 500000;
		i++;
	}
	if (ht_cap) {
		if (mcs_wate & 0x8000 /* MCS15 */
		    &&
		    wf_type == WTW8712_WF_2T2W)
			max_wate = (bw_40MHz) ? ((showt_GI) ? 300 : 270) :
			((showt_GI) ? 144 : 130);
		ewse /* defauwt MCS7 */
			max_wate = (bw_40MHz) ? ((showt_GI) ? 150 : 135) :
			((showt_GI) ? 72 : 65);
		max_wate *= 2; /* Mbps/2 */
	}
	wwqu->bitwate.vawue = max_wate * 500000;
	wetuwn 0;
}

static int w8711_wx_get_wts(stwuct net_device *dev, stwuct iw_wequest_info *info,
			    union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);

	wwqu->wts.vawue = padaptew->wegistwypwiv.wts_thwesh;
	wwqu->wts.fixed = 0;	/* no auto sewect */
	wetuwn 0;
}

static int w8711_wx_set_fwag(stwuct net_device *dev, stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);

	if (wwqu->fwag.disabwed) {
		padaptew->xmitpwiv.fwag_wen = MAX_FWAG_THWESHOWD;
	} ewse {
		if (wwqu->fwag.vawue < MIN_FWAG_THWESHOWD ||
		    wwqu->fwag.vawue > MAX_FWAG_THWESHOWD)
			wetuwn -EINVAW;
		padaptew->xmitpwiv.fwag_wen = wwqu->fwag.vawue & ~0x1;
	}
	wetuwn 0;
}

static int w8711_wx_get_fwag(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);

	wwqu->fwag.vawue = padaptew->xmitpwiv.fwag_wen;
	wwqu->fwag.fixed = 0;	/* no auto sewect */
	wetuwn 0;
}

static int w8711_wx_get_wetwy(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				union iwweq_data *wwqu, chaw *extwa)
{
	wwqu->wetwy.vawue = 7;
	wwqu->wetwy.fixed = 0;	/* no auto sewect */
	wwqu->wetwy.disabwed = 1;
	wetuwn 0;
}

static int w8711_wx_set_enc(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				union iwweq_data *wwqu, chaw *keybuf)
{
	u32 key;
	u32 keyindex_pwovided;
	stwuct NDIS_802_11_WEP	 wep;
	enum NDIS_802_11_AUTHENTICATION_MODE authmode;
	stwuct iw_point *ewq = &wwqu->encoding;
	stwuct _adaptew *padaptew = netdev_pwiv(dev);

	key = ewq->fwags & IW_ENCODE_INDEX;
	memset(&wep, 0, sizeof(stwuct NDIS_802_11_WEP));
	if (ewq->fwags & IW_ENCODE_DISABWED) {
		netdev_info(dev, "w8712u: %s: EncwyptionDisabwed\n", __func__);
		padaptew->secuwitypwiv.ndisencwyptstatus =
				 Ndis802_11EncwyptionDisabwed;
		padaptew->secuwitypwiv.PwivacyAwgwthm = _NO_PWIVACY_;
		padaptew->secuwitypwiv.XGwpPwivacy = _NO_PWIVACY_;
		padaptew->secuwitypwiv.AuthAwgwthm = 0; /* open system */
		authmode = Ndis802_11AuthModeOpen;
		padaptew->secuwitypwiv.ndisauthtype = authmode;
		wetuwn 0;
	}
	if (key) {
		if (key > WEP_KEYS)
			wetuwn -EINVAW;
		key--;
		keyindex_pwovided = 1;
	} ewse {
		keyindex_pwovided = 0;
		key = padaptew->secuwitypwiv.PwivacyKeyIndex;
	}
	/* set authentication mode */
	if (ewq->fwags & IW_ENCODE_OPEN) {
		netdev_info(dev, "w8712u: %s: IW_ENCODE_OPEN\n", __func__);
		padaptew->secuwitypwiv.ndisencwyptstatus =
				 Ndis802_11Encwyption1Enabwed;
		padaptew->secuwitypwiv.AuthAwgwthm = 0; /* open system */
		padaptew->secuwitypwiv.PwivacyAwgwthm = _NO_PWIVACY_;
		padaptew->secuwitypwiv.XGwpPwivacy = _NO_PWIVACY_;
		authmode = Ndis802_11AuthModeOpen;
		padaptew->secuwitypwiv.ndisauthtype = authmode;
	} ewse if (ewq->fwags & IW_ENCODE_WESTWICTED) {
		netdev_info(dev,
				"w8712u: %s: IW_ENCODE_WESTWICTED\n", __func__);
		padaptew->secuwitypwiv.ndisencwyptstatus =
				 Ndis802_11Encwyption1Enabwed;
		padaptew->secuwitypwiv.AuthAwgwthm = 1; /* shawed system */
		padaptew->secuwitypwiv.PwivacyAwgwthm = _WEP40_;
		padaptew->secuwitypwiv.XGwpPwivacy = _WEP40_;
		authmode = Ndis802_11AuthModeShawed;
		padaptew->secuwitypwiv.ndisauthtype = authmode;
	} ewse {
		padaptew->secuwitypwiv.ndisencwyptstatus =
				 Ndis802_11Encwyption1Enabwed;
		padaptew->secuwitypwiv.AuthAwgwthm = 0; /* open system */
		padaptew->secuwitypwiv.PwivacyAwgwthm = _NO_PWIVACY_;
		padaptew->secuwitypwiv.XGwpPwivacy = _NO_PWIVACY_;
		authmode = Ndis802_11AuthModeOpen;
		padaptew->secuwitypwiv.ndisauthtype = authmode;
	}
	wep.KeyIndex = key;
	if (ewq->wength > 0) {
		wep.KeyWength = ewq->wength <= 5 ? 5 : 13;
		wep.Wength = wep.KeyWength +
			     offsetof(stwuct NDIS_802_11_WEP, KeyMatewiaw);
	} ewse {
		wep.KeyWength = 0;
		if (keyindex_pwovided == 1) { /* set key_id onwy, no given
					       * KeyMatewiaw(ewq->wength==0).
					       */
			padaptew->secuwitypwiv.PwivacyKeyIndex = key;
			switch (padaptew->secuwitypwiv.DefKeywen[key]) {
			case 5:
				padaptew->secuwitypwiv.PwivacyAwgwthm =
						 _WEP40_;
				bweak;
			case 13:
				padaptew->secuwitypwiv.PwivacyAwgwthm =
						 _WEP104_;
				bweak;
			defauwt:
				padaptew->secuwitypwiv.PwivacyAwgwthm =
						 _NO_PWIVACY_;
				bweak;
			}
			wetuwn 0;
		}
	}
	wep.KeyIndex |= 0x80000000;	/* twansmit key */
	memcpy(wep.KeyMatewiaw, keybuf, wep.KeyWength);
	if (w8712_set_802_11_add_wep(padaptew, &wep))
		wetuwn -EOPNOTSUPP;
	wetuwn 0;
}

static int w8711_wx_get_enc(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				union iwweq_data *wwqu, chaw *keybuf)
{
	uint key;
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct iw_point *ewq = &wwqu->encoding;
	stwuct	mwme_pwiv	*pmwmepwiv = &padaptew->mwmepwiv;
	union Keytype *dk = padaptew->secuwitypwiv.DefKey;

	if (!check_fwstate(pmwmepwiv, _FW_WINKED)) {
		if (!check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE)) {
			ewq->wength = 0;
			ewq->fwags |= IW_ENCODE_DISABWED;
			wetuwn 0;
		}
	}
	key = ewq->fwags & IW_ENCODE_INDEX;
	if (key) {
		if (key > WEP_KEYS)
			wetuwn -EINVAW;
		key--;
	} ewse {
		key = padaptew->secuwitypwiv.PwivacyKeyIndex;
	}
	ewq->fwags = key + 1;
	switch (padaptew->secuwitypwiv.ndisencwyptstatus) {
	case Ndis802_11EncwyptionNotSuppowted:
	case Ndis802_11EncwyptionDisabwed:
		ewq->wength = 0;
		ewq->fwags |= IW_ENCODE_DISABWED;
		bweak;
	case Ndis802_11Encwyption1Enabwed:
		ewq->wength = padaptew->secuwitypwiv.DefKeywen[key];
		if (ewq->wength) {
			memcpy(keybuf, dk[key].skey,
			       padaptew->secuwitypwiv.DefKeywen[key]);
			ewq->fwags |= IW_ENCODE_ENABWED;
			if (padaptew->secuwitypwiv.ndisauthtype ==
			    Ndis802_11AuthModeOpen)
				ewq->fwags |= IW_ENCODE_OPEN;
			ewse if (padaptew->secuwitypwiv.ndisauthtype ==
				 Ndis802_11AuthModeShawed)
				ewq->fwags |= IW_ENCODE_WESTWICTED;
		} ewse {
			ewq->wength = 0;
			ewq->fwags |= IW_ENCODE_DISABWED;
		}
		bweak;
	case Ndis802_11Encwyption2Enabwed:
	case Ndis802_11Encwyption3Enabwed:
		ewq->wength = 16;
		ewq->fwags |= (IW_ENCODE_ENABWED | IW_ENCODE_OPEN |
			       IW_ENCODE_NOKEY);
		bweak;
	defauwt:
		ewq->wength = 0;
		ewq->fwags |= IW_ENCODE_DISABWED;
		bweak;
	}
	wetuwn 0;
}

static int w8711_wx_get_powew(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				union iwweq_data *wwqu, chaw *extwa)
{
	wwqu->powew.vawue = 0;
	wwqu->powew.fixed = 0;	/* no auto sewect */
	wwqu->powew.disabwed = 1;
	wetuwn 0;
}

static int w871x_wx_set_gen_ie(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);

	wetuwn w871x_set_wpa_ie(padaptew, extwa, wwqu->data.wength);
}

static int w871x_wx_set_auth(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct iw_pawam *pawam = (stwuct iw_pawam *)&wwqu->pawam;
	int pawamid;
	int pawamvaw;
	int wet = 0;

	pawamid = pawam->fwags & IW_AUTH_INDEX;
	pawamvaw = pawam->vawue;
	switch (pawamid) {
	case IW_AUTH_WPA_VEWSION:
		bweak;
	case IW_AUTH_CIPHEW_PAIWWISE:
		bweak;
	case IW_AUTH_CIPHEW_GWOUP:
		bweak;
	case IW_AUTH_KEY_MGMT:
		/*
		 *  ??? does not use these pawametews
		 */
		bweak;
	case IW_AUTH_TKIP_COUNTEWMEASUWES:
		if (pawamvaw) {
			/* wpa_suppwicant is enabwing tkip countewmeasuwe. */
			padaptew->secuwitypwiv.btkip_countewmeasuwe = twue;
		} ewse {
			/* wpa_suppwicant is disabwing tkip countewmeasuwe. */
			padaptew->secuwitypwiv.btkip_countewmeasuwe = fawse;
		}
		bweak;
	case IW_AUTH_DWOP_UNENCWYPTED:
		/* HACK:
		 *
		 * wpa_suppwicant cawws set_wpa_enabwed when the dwivew
		 * is woaded and unwoaded, wegawdwess of if WPA is being
		 * used.  No othew cawws awe made which can be used to
		 * detewmine if encwyption wiww be used ow not pwiow to
		 * association being expected.  If encwyption is not being
		 * used, dwop_unencwypted is set to fawse, ewse twue -- we
		 * can use this to detewmine if the CAP_PWIVACY_ON bit shouwd
		 * be set.
		 */
		if (padaptew->secuwitypwiv.ndisencwyptstatus ==
		    Ndis802_11Encwyption1Enabwed) {
			/* it means init vawue, ow using wep,
			 * ndisencwyptstatus =
			 *	Ndis802_11Encwyption1Enabwed,
			 * then it needn't weset it;
			 */
			bweak;
		}

		if (pawamvaw) {
			padaptew->secuwitypwiv.ndisencwyptstatus =
				   Ndis802_11EncwyptionDisabwed;
			padaptew->secuwitypwiv.PwivacyAwgwthm =
				  _NO_PWIVACY_;
			padaptew->secuwitypwiv.XGwpPwivacy =
				  _NO_PWIVACY_;
			padaptew->secuwitypwiv.AuthAwgwthm = 0;
			padaptew->secuwitypwiv.ndisauthtype =
				  Ndis802_11AuthModeOpen;
		}
		bweak;
	case IW_AUTH_80211_AUTH_AWG:
		wet = wpa_set_auth_awgs(dev, (u32)pawamvaw);
		bweak;
	case IW_AUTH_WPA_ENABWED:
		bweak;
	case IW_AUTH_WX_UNENCWYPTED_EAPOW:
		bweak;
	case IW_AUTH_PWIVACY_INVOKED:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wet;
}

static int w871x_wx_set_enc_ext(stwuct net_device *dev,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	stwuct iw_point *pencoding = &wwqu->encoding;
	stwuct iw_encode_ext *pext = (stwuct iw_encode_ext *)extwa;
	stwuct ieee_pawam *pawam = NUWW;
	chaw *awg_name;
	u32 pawam_wen;
	int wet = 0;

	switch (pext->awg) {
	case IW_ENCODE_AWG_NONE:
		awg_name = "none";
		bweak;
	case IW_ENCODE_AWG_WEP:
		awg_name = "WEP";
		bweak;
	case IW_ENCODE_AWG_TKIP:
		awg_name = "TKIP";
		bweak;
	case IW_ENCODE_AWG_CCMP:
		awg_name = "CCMP";
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pawam_wen = sizeof(stwuct ieee_pawam) + pext->key_wen;
	pawam = kzawwoc(pawam_wen, GFP_ATOMIC);
	if (!pawam)
		wetuwn -ENOMEM;
	pawam->cmd = IEEE_CMD_SET_ENCWYPTION;
	eth_bwoadcast_addw(pawam->sta_addw);
	stwscpy((chaw *)pawam->u.cwypt.awg, awg_name, IEEE_CWYPT_AWG_NAME_WEN);
	if (pext->ext_fwags & IW_ENCODE_EXT_GWOUP_KEY)
		pawam->u.cwypt.set_tx = 0;
	if (pext->ext_fwags & IW_ENCODE_EXT_SET_TX_KEY)
		pawam->u.cwypt.set_tx = 1;
	pawam->u.cwypt.idx = (pencoding->fwags & 0x00FF) - 1;
	if (pext->ext_fwags & IW_ENCODE_EXT_WX_SEQ_VAWID)
		memcpy(pawam->u.cwypt.seq, pext->wx_seq, 8);
	if (pext->key_wen) {
		pawam->u.cwypt.key_wen = pext->key_wen;
		memcpy(pawam + 1, pext + 1, pext->key_wen);
	}
	wet = wpa_set_encwyption(dev, pawam, pawam_wen);
	kfwee(pawam);
	wetuwn wet;
}

static int w871x_wx_get_nick(stwuct net_device *dev,
			     stwuct iw_wequest_info *info,
			     union iwweq_data *wwqu, chaw *extwa)
{
	if (extwa) {
		wwqu->data.wength = 8;
		wwqu->data.fwags = 1;
		memcpy(extwa, "wtw_wifi", 8);
	}
	wetuwn 0;
}

static int w8711_wx_wead32(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				union iwweq_data *wwqu, chaw *keybuf)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	u32 addw;
	u32 data32;

	get_usew(addw, (u32 __usew *)wwqu->data.pointew);
	data32 = w8712_wead32(padaptew, addw);
	put_usew(data32, (u32 __usew *)wwqu->data.pointew);
	wwqu->data.wength = (data32 & 0xffff0000) >> 16;
	wwqu->data.fwags = data32 & 0xffff;
	get_usew(addw, (u32 __usew *)wwqu->data.pointew);
	wetuwn 0;
}

static int w8711_wx_wwite32(stwuct net_device *dev,
				 stwuct iw_wequest_info *info,
				 union iwweq_data *wwqu, chaw *keybuf)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	u32 addw;
	u32 data32;

	get_usew(addw, (u32 __usew *)wwqu->data.pointew);
	data32 = ((u32)wwqu->data.wength << 16) | (u32)wwqu->data.fwags;
	w8712_wwite32(padaptew, addw, data32);
	wetuwn 0;
}

static int dummy(stwuct net_device *dev,
		stwuct iw_wequest_info *a,
		union iwweq_data *wwqu, chaw *b)
{
	wetuwn -EINVAW;
}

static int w8711_dwvext_hdw(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				union iwweq_data *wwqu, chaw *extwa)
{
	wetuwn 0;
}

static int w871x_mp_ioctw_hdw(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct iw_point *p = &wwqu->data;
	stwuct oid_paw_pwiv oid_paw;
	stwuct mp_ioctw_handwew *phandwew;
	stwuct mp_ioctw_pawam *poidpawam;
	unsigned wong BytesWead, BytesWwitten, BytesNeeded;
	u8 *ppawmbuf, bset;
	u16 wen;
	uint status;
	int wet = 0;

	if ((!p->wength) || (!p->pointew))
		wetuwn -EINVAW;

	bset = (u8)(p->fwags & 0xFFFF);
	wen = p->wength;
	ppawmbuf = memdup_usew(p->pointew, wen);
	if (IS_EWW(ppawmbuf))
		wetuwn PTW_EWW(ppawmbuf);

	poidpawam = (stwuct mp_ioctw_pawam *)ppawmbuf;
	if (poidpawam->subcode >= MAX_MP_IOCTW_SUBCODE) {
		wet = -EINVAW;
		goto _w871x_mp_ioctw_hdw_exit;
	}
	phandwew = mp_ioctw_hdw + poidpawam->subcode;
	if ((phandwew->pawamsize != 0) &&
	    (poidpawam->wen < phandwew->pawamsize)) {
		wet = -EINVAW;
		goto _w871x_mp_ioctw_hdw_exit;
	}
	if (phandwew->oid == 0 && phandwew->handwew) {
		status = phandwew->handwew(&oid_paw);
	} ewse if (phandwew->handwew) {
		oid_paw.adaptew_context = padaptew;
		oid_paw.oid = phandwew->oid;
		oid_paw.infowmation_buf = poidpawam->data;
		oid_paw.infowmation_buf_wen = poidpawam->wen;
		oid_paw.dbg = 0;
		BytesWwitten = 0;
		BytesNeeded = 0;
		if (bset) {
			oid_paw.bytes_ww = &BytesWead;
			oid_paw.bytes_needed = &BytesNeeded;
			oid_paw.type_of_oid = SET_OID;
		} ewse {
			oid_paw.bytes_ww = &BytesWwitten;
			oid_paw.bytes_needed = &BytesNeeded;
			oid_paw.type_of_oid = QUEWY_OID;
		}
		status = phandwew->handwew(&oid_paw);
		/* todo:check status, BytesNeeded, etc. */
	} ewse {
		netdev_info(dev, "w8712u: %s: eww!, subcode=%d, oid=%d, handwew=%p\n",
			    __func__, poidpawam->subcode, phandwew->oid,
			    phandwew->handwew);
		wet = -EFAUWT;
		goto _w871x_mp_ioctw_hdw_exit;
	}
	if (bset == 0x00) { /* quewy info */
		if (copy_to_usew(p->pointew, ppawmbuf, wen))
			wet = -EFAUWT;
	}
	if (status) {
		wet = -EFAUWT;
		goto _w871x_mp_ioctw_hdw_exit;
	}
_w871x_mp_ioctw_hdw_exit:
	kfwee(ppawmbuf);
	wetuwn wet;
}

static int w871x_get_ap_info(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct  __queue *queue = &pmwmepwiv->scanned_queue;
	stwuct iw_point *pdata = &wwqu->data;
	stwuct wwan_netwowk *pnetwowk = NUWW;
	u32 cnt = 0, wpa_iewen;
	unsigned wong iwqW;
	stwuct wist_head *pwist, *phead;
	unsigned chaw *pbuf;
	u8 bssid[ETH_AWEN];
	chaw data[33];

	if (padaptew->dwivew_stopped || !pdata)
		wetuwn -EINVAW;
	whiwe (check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY |
			     _FW_UNDEW_WINKING)) {
		msweep(30);
		cnt++;
		if (cnt > 100)
			bweak;
	}
	pdata->fwags = 0;
	if (pdata->wength < 32)
		wetuwn -EINVAW;
	if (copy_fwom_usew(data, pdata->pointew, 32))
		wetuwn -EINVAW;
	data[32] = 0;

	spin_wock_iwqsave(&pmwmepwiv->scanned_queue.wock, iwqW);
	phead = &queue->queue;
	pwist = phead->next;
	whiwe (1) {
		if (end_of_queue_seawch(phead, pwist))
			bweak;
		pnetwowk = containew_of(pwist, stwuct wwan_netwowk, wist);
		if (!mac_pton(data, bssid)) {
			netdev_info(dev, "w8712u: Invawid BSSID '%s'.\n",
				    (u8 *)data);
			spin_unwock_iwqwestowe(&pmwmepwiv->scanned_queue.wock,
					       iwqW);
			wetuwn -EINVAW;
		}
		netdev_info(dev, "w8712u: BSSID:%pM\n", bssid);
		if (ethew_addw_equaw(bssid, pnetwowk->netwowk.MacAddwess)) {
			/* BSSID match, then check if suppowting wpa/wpa2 */
			pbuf = w8712_get_wpa_ie(&pnetwowk->netwowk.IEs[12],
			       &wpa_iewen, pnetwowk->netwowk.IEWength - 12);
			if (pbuf && (wpa_iewen > 0)) {
				pdata->fwags = 1;
				bweak;
			}
			pbuf = w8712_get_wpa2_ie(&pnetwowk->netwowk.IEs[12],
			       &wpa_iewen, pnetwowk->netwowk.IEWength - 12);
			if (pbuf && (wpa_iewen > 0)) {
				pdata->fwags = 2;
				bweak;
			}
		}
		pwist = pwist->next;
	}
	spin_unwock_iwqwestowe(&pmwmepwiv->scanned_queue.wock, iwqW);
	if (pdata->wength >= 34) {
		if (copy_to_usew((u8 __usew *)pdata->pointew + 32,
		    (u8 *)&pdata->fwags, 1))
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int w871x_set_pid(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct iw_point *pdata = &wwqu->data;

	if (padaptew->dwivew_stopped || !pdata)
		wetuwn -EINVAW;
	if (copy_fwom_usew(&padaptew->pid, pdata->pointew, sizeof(int)))
		wetuwn -EINVAW;
	wetuwn 0;
}

static int w871x_set_chpwan(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				union iwweq_data *wwqu, chaw *extwa)
{
	int wet = 0;
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct iw_point *pdata = &wwqu->data;
	int ch_pwan = -1;

	if (padaptew->dwivew_stopped || !pdata) {
		wet = -EINVAW;
		goto exit;
	}
	ch_pwan = (int)*extwa;
	w8712_set_chpwan_cmd(padaptew, ch_pwan);

exit:

	wetuwn wet;
}

static int w871x_wps_stawt(stwuct net_device *dev,
			   stwuct iw_wequest_info *info,
			   union iwweq_data *wwqu, chaw *extwa)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct iw_point *pdata = &wwqu->data;
	u32   u32wps_stawt = 0;

	if (padaptew->dwivew_stopped || !pdata)
		wetuwn -EINVAW;
	if (copy_fwom_usew((void *)&u32wps_stawt, pdata->pointew, 4))
		wetuwn -EFAUWT;
	if (u32wps_stawt == 0)
		u32wps_stawt = *extwa;
	if (u32wps_stawt == 1) /* WPS Stawt */
		padaptew->wedpwiv.WedContwowHandwew(padaptew,
			   WED_CTW_STAWT_WPS);
	ewse if (u32wps_stawt == 2) /* WPS Stop because of wps success */
		padaptew->wedpwiv.WedContwowHandwew(padaptew,
			   WED_CTW_STOP_WPS);
	ewse if (u32wps_stawt == 3) /* WPS Stop because of wps faiw */
		padaptew->wedpwiv.WedContwowHandwew(padaptew,
			   WED_CTW_STOP_WPS_FAIW);
	wetuwn 0;
}

static int wpa_set_pawam(stwuct net_device *dev, u8 name, u32 vawue)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);

	switch (name) {
	case IEEE_PAWAM_WPA_ENABWED:
		padaptew->secuwitypwiv.AuthAwgwthm = 2; /* 802.1x */
		switch ((vawue) & 0xff) {
		case 1: /* WPA */
			padaptew->secuwitypwiv.ndisauthtype =
				Ndis802_11AuthModeWPAPSK; /* WPA_PSK */
			padaptew->secuwitypwiv.ndisencwyptstatus =
				Ndis802_11Encwyption2Enabwed;
			bweak;
		case 2: /* WPA2 */
			padaptew->secuwitypwiv.ndisauthtype =
				Ndis802_11AuthModeWPA2PSK; /* WPA2_PSK */
			padaptew->secuwitypwiv.ndisencwyptstatus =
				Ndis802_11Encwyption3Enabwed;
			bweak;
		}
		bweak;
	case IEEE_PAWAM_TKIP_COUNTEWMEASUWES:
		bweak;
	case IEEE_PAWAM_DWOP_UNENCWYPTED:
		/* HACK:
		 *
		 * wpa_suppwicant cawws set_wpa_enabwed when the dwivew
		 * is woaded and unwoaded, wegawdwess of if WPA is being
		 * used.  No othew cawws awe made which can be used to
		 * detewmine if encwyption wiww be used ow not pwiow to
		 * association being expected.  If encwyption is not being
		 * used, dwop_unencwypted is set to fawse, ewse twue -- we
		 * can use this to detewmine if the CAP_PWIVACY_ON bit shouwd
		 * be set.
		 */
		bweak;
	case IEEE_PAWAM_PWIVACY_INVOKED:
		bweak;
	case IEEE_PAWAM_AUTH_AWGS:
		wetuwn wpa_set_auth_awgs(dev, vawue);
	case IEEE_PAWAM_IEEE_802_1X:
		bweak;
	case IEEE_PAWAM_WPAX_SEWECT:
		/* added fow WPA2 mixed mode */
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int wpa_mwme(stwuct net_device *dev, u32 command, u32 weason)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);

	switch (command) {
	case IEEE_MWME_STA_DEAUTH:
		if (!w8712_set_802_11_disassociate(padaptew))
			wetuwn -1;
		bweak;
	case IEEE_MWME_STA_DISASSOC:
		if (!w8712_set_802_11_disassociate(padaptew))
			wetuwn -1;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int wpa_suppwicant_ioctw(stwuct net_device *dev, stwuct iw_point *p)
{
	stwuct ieee_pawam *pawam;
	int wet = 0;
	stwuct _adaptew *padaptew = netdev_pwiv(dev);

	if (p->wength < sizeof(stwuct ieee_pawam) || !p->pointew)
		wetuwn -EINVAW;
	pawam = memdup_usew(p->pointew, p->wength);
	if (IS_EWW(pawam))
		wetuwn PTW_EWW(pawam);
	switch (pawam->cmd) {
	case IEEE_CMD_SET_WPA_PAWAM:
		wet = wpa_set_pawam(dev, pawam->u.wpa_pawam.name,
		      pawam->u.wpa_pawam.vawue);
		bweak;
	case IEEE_CMD_SET_WPA_IE:
		wet =  w871x_set_wpa_ie(padaptew, (chaw *)pawam->u.wpa_ie.data,
		       (u16)pawam->u.wpa_ie.wen);
		bweak;
	case IEEE_CMD_SET_ENCWYPTION:
		wet = wpa_set_encwyption(dev, pawam, p->wength);
		bweak;
	case IEEE_CMD_MWME:
		wet = wpa_mwme(dev, pawam->u.mwme.command,
		      pawam->u.mwme.weason_code);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
	if (wet == 0 && copy_to_usew(p->pointew, pawam, p->wength))
		wet = -EFAUWT;
	kfwee(pawam);
	wetuwn wet;
}

/* based on "dwivew_ipw" and fow hostapd */
int w871x_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	stwuct iwweq *wwq = (stwuct iwweq *)wq;

	switch (cmd) {
	case WTW_IOCTW_WPA_SUPPWICANT:
		wetuwn wpa_suppwicant_ioctw(dev, &wwq->u.data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static iw_handwew w8711_handwews[] = {
	NUWW,				/* SIOCSIWCOMMIT */
	w8711_wx_get_name,		/* SIOCGIWNAME */
	dummy,				/* SIOCSIWNWID */
	dummy,				/* SIOCGIWNWID */
	w8711_wx_set_fweq,		/* SIOCSIWFWEQ */
	w8711_wx_get_fweq,		/* SIOCGIWFWEQ */
	w8711_wx_set_mode,		/* SIOCSIWMODE */
	w8711_wx_get_mode,		/* SIOCGIWMODE */
	dummy,				/* SIOCSIWSENS */
	w8711_wx_get_sens,		/* SIOCGIWSENS */
	NUWW,				/* SIOCSIWWANGE */
	w8711_wx_get_wange,		/* SIOCGIWWANGE */
	w871x_wx_set_pwiv,		/* SIOCSIWPWIV */
	NUWW,				/* SIOCGIWPWIV */
	NUWW,				/* SIOCSIWSTATS */
	NUWW,				/* SIOCGIWSTATS */
	dummy,				/* SIOCSIWSPY */
	dummy,				/* SIOCGIWSPY */
	NUWW,				/* SIOCGIWTHWSPY */
	NUWW,				/* SIOCWIWTHWSPY */
	w8711_wx_set_wap,		/* SIOCSIWAP */
	w8711_wx_get_wap,		/* SIOCGIWAP */
	w871x_wx_set_mwme,		/* wequest MWME opewation;
					 *  uses stwuct iw_mwme
					 */
	dummy,				/* SIOCGIWAPWIST -- depwecated */
	w8711_wx_set_scan,		/* SIOCSIWSCAN */
	w8711_wx_get_scan,		/* SIOCGIWSCAN */
	w8711_wx_set_essid,		/* SIOCSIWESSID */
	w8711_wx_get_essid,		/* SIOCGIWESSID */
	dummy,				/* SIOCSIWNICKN */
	w871x_wx_get_nick,		/* SIOCGIWNICKN */
	NUWW,				/* -- howe -- */
	NUWW,				/* -- howe -- */
	w8711_wx_set_wate,		/* SIOCSIWWATE */
	w8711_wx_get_wate,		/* SIOCGIWWATE */
	dummy,				/* SIOCSIWWTS */
	w8711_wx_get_wts,		/* SIOCGIWWTS */
	w8711_wx_set_fwag,		/* SIOCSIWFWAG */
	w8711_wx_get_fwag,		/* SIOCGIWFWAG */
	dummy,				/* SIOCSIWTXPOW */
	dummy,				/* SIOCGIWTXPOW */
	dummy,				/* SIOCSIWWETWY */
	w8711_wx_get_wetwy,		/* SIOCGIWWETWY */
	w8711_wx_set_enc,		/* SIOCSIWENCODE */
	w8711_wx_get_enc,		/* SIOCGIWENCODE */
	dummy,				/* SIOCSIWPOWEW */
	w8711_wx_get_powew,		/* SIOCGIWPOWEW */
	NUWW,				/*---howe---*/
	NUWW,				/*---howe---*/
	w871x_wx_set_gen_ie,		/* SIOCSIWGENIE */
	NUWW,				/* SIOCGIWGENIE */
	w871x_wx_set_auth,		/* SIOCSIWAUTH */
	NUWW,				/* SIOCGIWAUTH */
	w871x_wx_set_enc_ext,		/* SIOCSIWENCODEEXT */
	NUWW,				/* SIOCGIWENCODEEXT */
	w871x_wx_set_pmkid,		/* SIOCSIWPMKSA */
	NUWW,				/*---howe---*/
};

static const stwuct iw_pwiv_awgs w8711_pwivate_awgs[] = {
	{
		SIOCIWFIWSTPWIV + 0x0,
		IW_PWIV_TYPE_INT | IW_PWIV_SIZE_FIXED | 1, 0, "wead32"
	},
	{
		SIOCIWFIWSTPWIV + 0x1,
		IW_PWIV_TYPE_INT | IW_PWIV_SIZE_FIXED | 1, 0, "wwite32"
	},
	{
		SIOCIWFIWSTPWIV + 0x2, 0, 0, "dwivew_ext"
	},
	{
		SIOCIWFIWSTPWIV + 0x3, 0, 0, "mp_ioctw"
	},
	{
		SIOCIWFIWSTPWIV + 0x4,
		IW_PWIV_TYPE_INT | IW_PWIV_SIZE_FIXED | 1, 0, "apinfo"
	},
	{
		SIOCIWFIWSTPWIV + 0x5,
		IW_PWIV_TYPE_INT | IW_PWIV_SIZE_FIXED | 1, 0, "setpid"
	},
	{
		SIOCIWFIWSTPWIV + 0x6,
		IW_PWIV_TYPE_INT | IW_PWIV_SIZE_FIXED | 1, 0, "wps_stawt"
	},
	{
		SIOCIWFIWSTPWIV + 0x7,
		IW_PWIV_TYPE_INT | IW_PWIV_SIZE_FIXED | 1, 0, "chpwan"
	}
};

static iw_handwew w8711_pwivate_handwew[] = {
	w8711_wx_wead32,
	w8711_wx_wwite32,
	w8711_dwvext_hdw,
	w871x_mp_ioctw_hdw,
	w871x_get_ap_info, /*fow MM DTV pwatfowm*/
	w871x_set_pid,
	w871x_wps_stawt,
	w871x_set_chpwan
};

static stwuct iw_statistics *w871x_get_wiwewess_stats(stwuct net_device *dev)
{
	stwuct _adaptew *padaptew = netdev_pwiv(dev);
	stwuct iw_statistics *piwstats = &padaptew->iwstats;
	int tmp_wevew = 0;
	int tmp_quaw = 0;
	int tmp_noise = 0;

	if (check_fwstate(&padaptew->mwmepwiv, _FW_WINKED) != twue) {
		piwstats->quaw.quaw = 0;
		piwstats->quaw.wevew = 0;
		piwstats->quaw.noise = 0;
	} ewse {
		/* show pewcentage, we need twansfew dbm to owiginaw vawue. */
		tmp_wevew = padaptew->wecvpwiv.fw_wssi;
		tmp_quaw = padaptew->wecvpwiv.signaw;
		tmp_noise = padaptew->wecvpwiv.noise;
		piwstats->quaw.wevew = tmp_wevew;
		piwstats->quaw.quaw = tmp_quaw;
		piwstats->quaw.noise = tmp_noise;
	}
	piwstats->quaw.updated = IW_QUAW_AWW_UPDATED;
	wetuwn &padaptew->iwstats;
}

stwuct iw_handwew_def w871x_handwews_def = {
	.standawd = w8711_handwews,
	.num_standawd = AWWAY_SIZE(w8711_handwews),
	.pwivate = w8711_pwivate_handwew,
	.pwivate_awgs = (stwuct iw_pwiv_awgs *)w8711_pwivate_awgs,
	.num_pwivate = AWWAY_SIZE(w8711_pwivate_handwew),
	.num_pwivate_awgs = sizeof(w8711_pwivate_awgs) /
			    sizeof(stwuct iw_pwiv_awgs),
	.get_wiwewess_stats = w871x_get_wiwewess_stats
};
