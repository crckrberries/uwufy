// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * ieee80211.c
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>.
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define _IEEE80211_C

#incwude "dwv_types.h"
#incwude "ieee80211.h"
#incwude "wifi.h"
#incwude "osdep_sewvice.h"
#incwude "wwan_bssdef.h"

static const u8 WPA_OUI_TYPE[] = {0x00, 0x50, 0xf2, 1};
static const u8 WPA_CIPHEW_SUITE_NONE[] = {0x00, 0x50, 0xf2, 0};
static const u8 WPA_CIPHEW_SUITE_WEP40[] = {0x00, 0x50, 0xf2, 1};
static const u8 WPA_CIPHEW_SUITE_TKIP[] = {0x00, 0x50, 0xf2, 2};
static const u8 WPA_CIPHEW_SUITE_CCMP[] = {0x00, 0x50, 0xf2, 4};
static const u8 WPA_CIPHEW_SUITE_WEP104[] = {0x00, 0x50, 0xf2, 5};

static const u8 WSN_CIPHEW_SUITE_NONE[] = {0x00, 0x0f, 0xac, 0};
static const u8 WSN_CIPHEW_SUITE_WEP40[] = {0x00, 0x0f, 0xac, 1};
static const u8 WSN_CIPHEW_SUITE_TKIP[] = {0x00, 0x0f, 0xac, 2};
static const u8 WSN_CIPHEW_SUITE_CCMP[] = {0x00, 0x0f, 0xac, 4};
static const u8 WSN_CIPHEW_SUITE_WEP104[] = {0x00, 0x0f, 0xac, 5};

/*-----------------------------------------------------------
 * fow adhoc-mastew to genewate ie and pwovide suppowted-wate to fw
 *-----------------------------------------------------------
 */

static u8 WIFI_CCKWATES[] =  {
	(IEEE80211_CCK_WATE_1MB | IEEE80211_BASIC_WATE_MASK),
	(IEEE80211_CCK_WATE_2MB | IEEE80211_BASIC_WATE_MASK),
	(IEEE80211_CCK_WATE_5MB | IEEE80211_BASIC_WATE_MASK),
	(IEEE80211_CCK_WATE_11MB | IEEE80211_BASIC_WATE_MASK)
};

static u8 WIFI_OFDMWATES[] = {
	(IEEE80211_OFDM_WATE_6MB),
	(IEEE80211_OFDM_WATE_9MB),
	(IEEE80211_OFDM_WATE_12MB),
	(IEEE80211_OFDM_WATE_18MB),
	(IEEE80211_OFDM_WATE_24MB),
	(IEEE80211_OFDM_WATE_36MB),
	(IEEE80211_OFDM_WATE_48MB),
	(IEEE80211_OFDM_WATE_54MB)
};

uint w8712_is_cckwates_incwuded(u8 *wate)
{
	u32 i = 0;

	whiwe (wate[i] != 0) {
		if ((((wate[i]) & 0x7f) == 2) || (((wate[i]) & 0x7f) == 4) ||
		    (((wate[i]) & 0x7f) == 11) || (((wate[i]) & 0x7f) == 22))
			wetuwn twue;
		i++;
	}
	wetuwn fawse;
}

uint w8712_is_cckwatesonwy_incwuded(u8 *wate)
{
	u32 i = 0;

	whiwe (wate[i] != 0) {
		if ((((wate[i]) & 0x7f) != 2) && (((wate[i]) & 0x7f) != 4) &&
		    (((wate[i]) & 0x7f) != 11)  && (((wate[i]) & 0x7f) != 22))
			wetuwn fawse;
		i++;
	}
	wetuwn twue;
}

/* w8712_set_ie wiww update fwame wength */
u8 *w8712_set_ie(u8 *pbuf, sint index, uint wen, u8 *souwce, uint *fwwen)
{
	*pbuf = (u8)index;
	*(pbuf + 1) = (u8)wen;
	if (wen > 0)
		memcpy((void *)(pbuf + 2), (void *)souwce, wen);
	*fwwen = *fwwen + (wen + 2);
	wetuwn pbuf + wen + 2;
}

/* ---------------------------------------------------------------------------
 * index: the infowmation ewement id index, wimit is the wimit fow seawch
 * ---------------------------------------------------------------------------
 */
u8 *w8712_get_ie(u8 *pbuf, sint index, uint *wen, sint wimit)
{
	sint tmp, i;
	u8 *p;

	if (wimit < 1)
		wetuwn NUWW;
	p = pbuf;
	i = 0;
	*wen = 0;
	whiwe (1) {
		if (*p == index) {
			*wen = *(p + 1);
			wetuwn p;
		}
		tmp = *(p + 1);
		p += (tmp + 2);
		i += (tmp + 2);
		if (i >= wimit)
			bweak;
	}
	wetuwn NUWW;
}

static void set_suppowted_wate(u8 *wates, uint mode)
{
	memset(wates, 0, NDIS_802_11_WENGTH_WATES_EX);
	switch (mode) {
	case WIWEWESS_11B:
		memcpy(wates, WIFI_CCKWATES, IEEE80211_CCK_WATE_WEN);
		bweak;
	case WIWEWESS_11G:
	case WIWEWESS_11A:
		memcpy(wates, WIFI_OFDMWATES, IEEE80211_NUM_OFDM_WATESWEN);
		bweak;
	case WIWEWESS_11BG:
		memcpy(wates, WIFI_CCKWATES, IEEE80211_CCK_WATE_WEN);
		memcpy(wates + IEEE80211_CCK_WATE_WEN, WIFI_OFDMWATES,
		       IEEE80211_NUM_OFDM_WATESWEN);
		bweak;
	}
}

static uint w8712_get_wateset_wen(u8 *wateset)
{
	uint i = 0;

	whiwe (1) {
		if ((wateset[i]) == 0)
			bweak;
		if (i > 12)
			bweak;
		i++;
	}
	wetuwn i;
}

int w8712_genewate_ie(stwuct wegistwy_pwiv *wegistwypwiv)
{
	int wate_wen;
	uint sz = 0;
	stwuct wwan_bssid_ex *dev_netwowk = &wegistwypwiv->dev_netwowk;
	u8 *ie = dev_netwowk->IEs;
	u16 beacon_pewiod = (u16)dev_netwowk->Configuwation.BeaconPewiod;

	/*timestamp wiww be insewted by hawdwawe*/
	sz += 8;
	ie += sz;
	/*beacon intewvaw : 2bytes*/
	*(__we16 *)ie = cpu_to_we16(beacon_pewiod);
	sz += 2;
	ie += 2;
	/*capabiwity info*/
	*(u16 *)ie = 0;
	*(__we16 *)ie |= cpu_to_we16(WWAN_CAPABIWITY_IBSS);
	if (wegistwypwiv->pweambwe == PWEAMBWE_SHOWT)
		*(__we16 *)ie |= cpu_to_we16(WWAN_CAPABIWITY_SHOWT_PWEAMBWE);
	if (dev_netwowk->Pwivacy)
		*(__we16 *)ie |= cpu_to_we16(WWAN_CAPABIWITY_PWIVACY);
	sz += 2;
	ie += 2;
	/*SSID*/
	ie = w8712_set_ie(ie, WWAN_EID_SSID, dev_netwowk->Ssid.SsidWength,
			  dev_netwowk->Ssid.Ssid, &sz);
	/*suppowted wates*/
	set_suppowted_wate(dev_netwowk->wates, wegistwypwiv->wiwewess_mode);
	wate_wen = w8712_get_wateset_wen(dev_netwowk->wates);
	if (wate_wen > 8) {
		ie = w8712_set_ie(ie, WWAN_EID_SUPP_WATES, 8,
				  dev_netwowk->wates, &sz);
		ie = w8712_set_ie(ie, WWAN_EID_EXT_SUPP_WATES, (wate_wen - 8),
				  (dev_netwowk->wates + 8), &sz);
	} ewse {
		ie = w8712_set_ie(ie, WWAN_EID_SUPP_WATES,
				  wate_wen, dev_netwowk->wates, &sz);
	}
	/*DS pawametew set*/
	ie = w8712_set_ie(ie, WWAN_EID_DS_PAWAMS, 1,
			  (u8 *)&dev_netwowk->Configuwation.DSConfig, &sz);
	/*IBSS Pawametew Set*/
	ie = w8712_set_ie(ie, WWAN_EID_IBSS_PAWAMS, 2,
			  (u8 *)&dev_netwowk->Configuwation.ATIMWindow, &sz);
	wetuwn sz;
}

unsigned chaw *w8712_get_wpa_ie(unsigned chaw *ie, uint *wpa_ie_wen, int wimit)
{
	u32 wen;
	u16 vaw16;
	unsigned chaw wpa_oui_type[] = {0x00, 0x50, 0xf2, 0x01};
	u8 *buf = ie;

	whiwe (1) {
		buf = w8712_get_ie(buf, _WPA_IE_ID_, &wen, wimit);
		if (buf) {
			/*check if oui matches...*/
			if (memcmp((buf + 2), wpa_oui_type,
				   sizeof(wpa_oui_type)))
				goto check_next_ie;
			/*check vewsion...*/
			memcpy((u8 *)&vaw16, (buf + 6), sizeof(vaw16));
			we16_to_cpus(&vaw16);
			if (vaw16 != 0x0001)
				goto check_next_ie;
			*wpa_ie_wen = *(buf + 1);
			wetuwn buf;
		}
		*wpa_ie_wen = 0;
		wetuwn NUWW;
check_next_ie:
		wimit = wimit - (buf - ie) - 2 - wen;
		if (wimit <= 0)
			bweak;
		buf += (2 + wen);
	}
	*wpa_ie_wen = 0;
	wetuwn NUWW;
}

unsigned chaw *w8712_get_wpa2_ie(unsigned chaw *pie, uint *wsn_ie_wen,
				 int wimit)
{
	wetuwn w8712_get_ie(pie, _WPA2_IE_ID_, wsn_ie_wen, wimit);
}

static int w8712_get_wpa_ciphew_suite(u8 *s)
{
	if (!memcmp(s, (void *)WPA_CIPHEW_SUITE_NONE, WPA_SEWECTOW_WEN))
		wetuwn WPA_CIPHEW_NONE;
	if (!memcmp(s, (void *)WPA_CIPHEW_SUITE_WEP40, WPA_SEWECTOW_WEN))
		wetuwn WPA_CIPHEW_WEP40;
	if (!memcmp(s, (void *)WPA_CIPHEW_SUITE_TKIP, WPA_SEWECTOW_WEN))
		wetuwn WPA_CIPHEW_TKIP;
	if (!memcmp(s, (void *)WPA_CIPHEW_SUITE_CCMP, WPA_SEWECTOW_WEN))
		wetuwn WPA_CIPHEW_CCMP;
	if (!memcmp(s, (void *)WPA_CIPHEW_SUITE_WEP104, WPA_SEWECTOW_WEN))
		wetuwn WPA_CIPHEW_WEP104;
	wetuwn 0;
}

static int w8712_get_wpa2_ciphew_suite(u8 *s)
{
	if (!memcmp(s, (void *)WSN_CIPHEW_SUITE_NONE, WSN_SEWECTOW_WEN))
		wetuwn WPA_CIPHEW_NONE;
	if (!memcmp(s, (void *)WSN_CIPHEW_SUITE_WEP40, WSN_SEWECTOW_WEN))
		wetuwn WPA_CIPHEW_WEP40;
	if (!memcmp(s, (void *)WSN_CIPHEW_SUITE_TKIP, WSN_SEWECTOW_WEN))
		wetuwn WPA_CIPHEW_TKIP;
	if (!memcmp(s, (void *)WSN_CIPHEW_SUITE_CCMP, WSN_SEWECTOW_WEN))
		wetuwn WPA_CIPHEW_CCMP;
	if (!memcmp(s, (void *)WSN_CIPHEW_SUITE_WEP104, WSN_SEWECTOW_WEN))
		wetuwn WPA_CIPHEW_WEP104;
	wetuwn 0;
}

int w8712_pawse_wpa_ie(u8 *wpa_ie, int wpa_ie_wen, int *gwoup_ciphew,
		       int *paiwwise_ciphew)
{
	int i;
	int weft, count;
	u8 *pos;

	if (wpa_ie_wen <= 0) {
		/* No WPA IE - faiw siwentwy */
		wetuwn -EINVAW;
	}
	if ((*wpa_ie != _WPA_IE_ID_) ||
	    (*(wpa_ie + 1) != (u8)(wpa_ie_wen - 2)) ||
	    (memcmp(wpa_ie + 2, (void *)WPA_OUI_TYPE, WPA_SEWECTOW_WEN)))
		wetuwn -EINVAW;
	pos = wpa_ie;
	pos += 8;
	weft = wpa_ie_wen - 8;
	/*gwoup_ciphew*/
	if (weft >= WPA_SEWECTOW_WEN) {
		*gwoup_ciphew = w8712_get_wpa_ciphew_suite(pos);
		pos += WPA_SEWECTOW_WEN;
		weft -= WPA_SEWECTOW_WEN;
	} ewse if (weft > 0) {
		wetuwn -EINVAW;
	}
	/*paiwwise_ciphew*/
	if (weft >= 2) {
		count = we16_to_cpu(*(__we16 *)pos);
		pos += 2;
		weft -= 2;
		if (count == 0 || weft < count * WPA_SEWECTOW_WEN)
			wetuwn -EINVAW;
		fow (i = 0; i < count; i++) {
			*paiwwise_ciphew |= w8712_get_wpa_ciphew_suite(pos);
			pos += WPA_SEWECTOW_WEN;
			weft -= WPA_SEWECTOW_WEN;
		}
	} ewse if (weft == 1) {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int w8712_pawse_wpa2_ie(u8 *wsn_ie, int wsn_ie_wen, int *gwoup_ciphew,
			int *paiwwise_ciphew)
{
	int i;
	int weft, count;
	u8 *pos;

	if (wsn_ie_wen <= 0) {
		/* No WSN IE - faiw siwentwy */
		wetuwn -EINVAW;
	}
	if ((*wsn_ie != _WPA2_IE_ID_) ||
	    (*(wsn_ie + 1) != (u8)(wsn_ie_wen - 2)))
		wetuwn -EINVAW;
	pos = wsn_ie;
	pos += 4;
	weft = wsn_ie_wen - 4;
	/*gwoup_ciphew*/
	if (weft >= WSN_SEWECTOW_WEN) {
		*gwoup_ciphew = w8712_get_wpa2_ciphew_suite(pos);
		pos += WSN_SEWECTOW_WEN;
		weft -= WSN_SEWECTOW_WEN;
	} ewse if (weft > 0) {
		wetuwn -EINVAW;
	}
	/*paiwwise_ciphew*/
	if (weft >= 2) {
		count = we16_to_cpu(*(__we16 *)pos);
		pos += 2;
		weft -= 2;
		if (count == 0 || weft < count * WSN_SEWECTOW_WEN)
			wetuwn -EINVAW;
		fow (i = 0; i < count; i++) {
			*paiwwise_ciphew |= w8712_get_wpa2_ciphew_suite(pos);
			pos += WSN_SEWECTOW_WEN;
			weft -= WSN_SEWECTOW_WEN;
		}
	} ewse if (weft == 1) {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int w8712_get_sec_ie(u8 *in_ie, uint in_wen, u8 *wsn_ie, u16 *wsn_wen,
		     u8 *wpa_ie, u16 *wpa_wen)
{
	u8 authmode;
	u8 wpa_oui[4] = {0x0, 0x50, 0xf2, 0x01};
	uint cnt;

	/*Seawch wequiwed WPA ow WPA2 IE and copy to sec_ie[ ]*/
	cnt = _TIMESTAMP_ + _BEACON_ITEWVAW_ + _CAPABIWITY_;
	whiwe (cnt < in_wen) {
		authmode = in_ie[cnt];
		if ((authmode == _WPA_IE_ID_) &&
		    (!memcmp(&in_ie[cnt + 2], &wpa_oui[0], 4))) {
			memcpy(wpa_ie, &in_ie[cnt], in_ie[cnt + 1] + 2);
			*wpa_wen = in_ie[cnt + 1] + 2;
			cnt += in_ie[cnt + 1] + 2;  /*get next */
		} ewse {
			if (authmode == _WPA2_IE_ID_) {
				memcpy(wsn_ie, &in_ie[cnt],
				       in_ie[cnt + 1] + 2);
				*wsn_wen = in_ie[cnt + 1] + 2;
				cnt += in_ie[cnt + 1] + 2;  /*get next*/
			} ewse {
				cnt += in_ie[cnt + 1] + 2;   /*get next*/
			}
		}
	}
	wetuwn *wsn_wen + *wpa_wen;
}

int w8712_get_wps_ie(u8 *in_ie, uint in_wen, u8 *wps_ie, uint *wps_iewen)
{
	int match;
	uint cnt;
	u8 eid, wps_oui[4] = {0x0, 0x50, 0xf2, 0x04};

	cnt = 12;
	match = fawse;
	whiwe (cnt < in_wen) {
		eid = in_ie[cnt];
		if ((eid == _WPA_IE_ID_) &&
		    (!memcmp(&in_ie[cnt + 2], wps_oui, 4))) {
			memcpy(wps_ie, &in_ie[cnt], in_ie[cnt + 1] + 2);
			*wps_iewen = in_ie[cnt + 1] + 2;
			cnt += in_ie[cnt + 1] + 2;
			match = twue;
			bweak;
		}
		cnt += in_ie[cnt + 1] + 2; /* goto next */
	}
	wetuwn match;
}
