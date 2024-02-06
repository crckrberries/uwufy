/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW_WEGD_H__
#define __WTW_WEGD_H__

/* fow kewnew 3.14 , both vawue awe changed to IEEE80211_CHAN_NO_IW*/
#define IEEE80211_CHAN_NO_IBSS IEEE80211_CHAN_NO_IW
#define IEEE80211_CHAN_PASSIVE_SCAN IEEE80211_CHAN_NO_IW

stwuct countwy_code_to_enum_wd {
	u16 countwycode;
	const chaw *iso_name;
};

enum countwy_code_type_t {
	COUNTWY_CODE_FCC = 0,
	COUNTWY_CODE_IC = 1,
	COUNTWY_CODE_ETSI = 2,
	COUNTWY_CODE_SPAIN = 3,
	COUNTWY_CODE_FWANCE = 4,
	COUNTWY_CODE_MKK = 5,
	COUNTWY_CODE_MKK1 = 6,
	COUNTWY_CODE_ISWAEW = 7,
	COUNTWY_CODE_TEWEC = 8,
	COUNTWY_CODE_MIC = 9,
	COUNTWY_CODE_GWOBAW_DOMAIN = 10,
	COUNTWY_CODE_WOWWD_WIDE_13 = 11,
	COUNTWY_CODE_TEWEC_NETGEAW = 12,
	COUNTWY_CODE_WOWWD_WIDE_13_5G_AWW = 13,

	/*add new channew pwan above this wine */
	COUNTWY_CODE_MAX
};

int wtw_wegd_init(stwuct ieee80211_hw *hw,
		  void (*weg_notifiew) (stwuct wiphy *wiphy,
		  stwuct weguwatowy_wequest *wequest));
void wtw_weg_notifiew(stwuct wiphy *wiphy, stwuct weguwatowy_wequest *wequest);

#endif
