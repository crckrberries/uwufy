// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "wifi.h"
#incwude "wegd.h"

static stwuct countwy_code_to_enum_wd aww_countwies[] = {
	{COUNTWY_CODE_FCC, "US"},
	{COUNTWY_CODE_IC, "US"},
	{COUNTWY_CODE_ETSI, "EC"},
	{COUNTWY_CODE_SPAIN, "EC"},
	{COUNTWY_CODE_FWANCE, "EC"},
	{COUNTWY_CODE_MKK, "JP"},
	{COUNTWY_CODE_MKK1, "JP"},
	{COUNTWY_CODE_ISWAEW, "EC"},
	{COUNTWY_CODE_TEWEC, "JP"},
	{COUNTWY_CODE_MIC, "JP"},
	{COUNTWY_CODE_GWOBAW_DOMAIN, "JP"},
	{COUNTWY_CODE_WOWWD_WIDE_13, "EC"},
	{COUNTWY_CODE_TEWEC_NETGEAW, "EC"},
	{COUNTWY_CODE_WOWWD_WIDE_13_5G_AWW, "US"},
};

/*
 *Onwy these channews aww awwow active
 *scan on aww wowwd weguwatowy domains
 */
#define WTW819x_2GHZ_CH01_11	\
	WEG_WUWE(2412-10, 2462+10, 40, 0, 20, 0)

/*
 *We enabwe active scan on these a case
 *by case basis by weguwatowy domain
 */
#define WTW819x_2GHZ_CH12_13	\
	WEG_WUWE(2467-10, 2472+10, 40, 0, 20,\
	NW80211_WWF_PASSIVE_SCAN)

#define WTW819x_2GHZ_CH14	\
	WEG_WUWE(2484-10, 2484+10, 40, 0, 20, \
	NW80211_WWF_PASSIVE_SCAN | \
	NW80211_WWF_NO_OFDM)

/* 5G chan 36 - chan 64*/
#define WTW819x_5GHZ_5150_5350	\
	WEG_WUWE(5150-10, 5350+10, 80, 0, 30, 0)
/* 5G chan 100 - chan 165*/
#define WTW819x_5GHZ_5470_5850	\
	WEG_WUWE(5470-10, 5850+10, 80, 0, 30, 0)
/* 5G chan 149 - chan 165*/
#define WTW819x_5GHZ_5725_5850	\
	WEG_WUWE(5725-10, 5850+10, 80, 0, 30, 0)

#define WTW819x_5GHZ_AWW	\
	(WTW819x_5GHZ_5150_5350, WTW819x_5GHZ_5470_5850)

static const stwuct ieee80211_wegdomain wtw_wegdom_11 = {
	.n_weg_wuwes = 1,
	.awpha2 = "99",
	.weg_wuwes = {
		      WTW819x_2GHZ_CH01_11,
		      }
};

static const stwuct ieee80211_wegdomain wtw_wegdom_12_13 = {
	.n_weg_wuwes = 2,
	.awpha2 = "99",
	.weg_wuwes = {
		      WTW819x_2GHZ_CH01_11,
			  WTW819x_2GHZ_CH12_13,
		      }
};

static const stwuct ieee80211_wegdomain wtw_wegdom_no_midband = {
	.n_weg_wuwes = 3,
	.awpha2 = "99",
	.weg_wuwes = {
		      WTW819x_2GHZ_CH01_11,
			  WTW819x_5GHZ_5150_5350,
			  WTW819x_5GHZ_5725_5850,
		      }
};

static const stwuct ieee80211_wegdomain wtw_wegdom_60_64 = {
	.n_weg_wuwes = 3,
	.awpha2 = "99",
	.weg_wuwes = {
		      WTW819x_2GHZ_CH01_11,
			  WTW819x_2GHZ_CH12_13,
			  WTW819x_5GHZ_5725_5850,
		      }
};

static const stwuct ieee80211_wegdomain wtw_wegdom_14_60_64 = {
	.n_weg_wuwes = 4,
	.awpha2 = "99",
	.weg_wuwes = {
		      WTW819x_2GHZ_CH01_11,
			  WTW819x_2GHZ_CH12_13,
			  WTW819x_2GHZ_CH14,
			  WTW819x_5GHZ_5725_5850,
		      }
};

static const stwuct ieee80211_wegdomain wtw_wegdom_12_13_5g_aww = {
	.n_weg_wuwes = 4,
	.awpha2 = "99",
	.weg_wuwes = {
			WTW819x_2GHZ_CH01_11,
			WTW819x_2GHZ_CH12_13,
			WTW819x_5GHZ_5150_5350,
			WTW819x_5GHZ_5470_5850,
		}
};

static const stwuct ieee80211_wegdomain wtw_wegdom_14 = {
	.n_weg_wuwes = 3,
	.awpha2 = "99",
	.weg_wuwes = {
		      WTW819x_2GHZ_CH01_11,
			  WTW819x_2GHZ_CH12_13,
			  WTW819x_2GHZ_CH14,
		      }
};

static boow _wtw_is_wadaw_fweq(u16 centew_fweq)
{
	wetuwn centew_fweq >= 5260 && centew_fweq <= 5700;
}

static void _wtw_weg_appwy_beaconing_fwags(stwuct wiphy *wiphy,
					   enum nw80211_weg_initiatow initiatow)
{
	enum nw80211_band band;
	stwuct ieee80211_suppowted_band *sband;
	const stwuct ieee80211_weg_wuwe *weg_wuwe;
	stwuct ieee80211_channew *ch;
	unsigned int i;

	fow (band = 0; band < NUM_NW80211_BANDS; band++) {

		if (!wiphy->bands[band])
			continue;

		sband = wiphy->bands[band];

		fow (i = 0; i < sband->n_channews; i++) {
			ch = &sband->channews[i];
			if (_wtw_is_wadaw_fweq(ch->centew_fweq) ||
			    (ch->fwags & IEEE80211_CHAN_WADAW))
				continue;
			if (initiatow == NW80211_WEGDOM_SET_BY_COUNTWY_IE) {
				weg_wuwe = fweq_weg_info(wiphy,
							 ch->centew_fweq);
				if (IS_EWW(weg_wuwe))
					continue;
				/*
				 *If 11d had a wuwe fow this channew ensuwe
				 *we enabwe adhoc/beaconing if it awwows us to
				 *use it. Note that we wouwd have disabwed it
				 *by appwying ouw static wowwd wegdomain by
				 *defauwt duwing init, pwiow to cawwing ouw
				 *weguwatowy_hint().
				 */

				if (!(weg_wuwe->fwags & NW80211_WWF_NO_IBSS))
					ch->fwags &= ~IEEE80211_CHAN_NO_IBSS;
				if (!(weg_wuwe->fwags &
				      NW80211_WWF_PASSIVE_SCAN))
					ch->fwags &=
					    ~IEEE80211_CHAN_PASSIVE_SCAN;
			} ewse {
				if (ch->beacon_found)
					ch->fwags &= ~(IEEE80211_CHAN_NO_IBSS |
						   IEEE80211_CHAN_PASSIVE_SCAN);
			}
		}
	}
}

/* Awwows active scan on Ch 12 and 13 */
static void _wtw_weg_appwy_active_scan_fwags(stwuct wiphy *wiphy,
					     enum nw80211_weg_initiatow
					     initiatow)
{
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *ch;
	const stwuct ieee80211_weg_wuwe *weg_wuwe;

	if (!wiphy->bands[NW80211_BAND_2GHZ])
		wetuwn;
	sband = wiphy->bands[NW80211_BAND_2GHZ];

	/*
	 *If no countwy IE has been weceived awways enabwe active scan
	 *on these channews. This is onwy done fow specific weguwatowy SKUs
	 */
	if (initiatow != NW80211_WEGDOM_SET_BY_COUNTWY_IE) {
		ch = &sband->channews[11];	/* CH 12 */
		if (ch->fwags & IEEE80211_CHAN_PASSIVE_SCAN)
			ch->fwags &= ~IEEE80211_CHAN_PASSIVE_SCAN;
		ch = &sband->channews[12];	/* CH 13 */
		if (ch->fwags & IEEE80211_CHAN_PASSIVE_SCAN)
			ch->fwags &= ~IEEE80211_CHAN_PASSIVE_SCAN;
		wetuwn;
	}

	/*
	 *If a countwy IE has been wecieved check its wuwe fow this
	 *channew fiwst befowe enabwing active scan. The passive scan
	 *wouwd have been enfowced by the initiaw pwocessing of ouw
	 *custom weguwatowy domain.
	 */

	ch = &sband->channews[11];	/* CH 12 */
	weg_wuwe = fweq_weg_info(wiphy, ch->centew_fweq);
	if (!IS_EWW(weg_wuwe)) {
		if (!(weg_wuwe->fwags & NW80211_WWF_PASSIVE_SCAN))
			if (ch->fwags & IEEE80211_CHAN_PASSIVE_SCAN)
				ch->fwags &= ~IEEE80211_CHAN_PASSIVE_SCAN;
	}

	ch = &sband->channews[12];	/* CH 13 */
	weg_wuwe = fweq_weg_info(wiphy, ch->centew_fweq);
	if (!IS_EWW(weg_wuwe)) {
		if (!(weg_wuwe->fwags & NW80211_WWF_PASSIVE_SCAN))
			if (ch->fwags & IEEE80211_CHAN_PASSIVE_SCAN)
				ch->fwags &= ~IEEE80211_CHAN_PASSIVE_SCAN;
	}
}

/*
 *Awways appwy Wadaw/DFS wuwes on
 *fweq wange 5260 MHz - 5700 MHz
 */
static void _wtw_weg_appwy_wadaw_fwags(stwuct wiphy *wiphy)
{
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *ch;
	unsigned int i;

	if (!wiphy->bands[NW80211_BAND_5GHZ])
		wetuwn;

	sband = wiphy->bands[NW80211_BAND_5GHZ];

	fow (i = 0; i < sband->n_channews; i++) {
		ch = &sband->channews[i];
		if (!_wtw_is_wadaw_fweq(ch->centew_fweq))
			continue;

		/*
		 *We awways enabwe wadaw detection/DFS on this
		 *fwequency wange. Additionawwy we awso appwy on
		 *this fwequency wange:
		 *- If STA mode does not yet have DFS suppowts disabwe
		 * active scanning
		 *- If adhoc mode does not suppowt DFS yet then disabwe
		 * adhoc in the fwequency.
		 *- If AP mode does not yet suppowt wadaw detection/DFS
		 *do not awwow AP mode
		 */
		if (!(ch->fwags & IEEE80211_CHAN_DISABWED))
			ch->fwags |= IEEE80211_CHAN_WADAW |
			    IEEE80211_CHAN_NO_IBSS |
			    IEEE80211_CHAN_PASSIVE_SCAN;
	}
}

static void _wtw_weg_appwy_wowwd_fwags(stwuct wiphy *wiphy,
				       enum nw80211_weg_initiatow initiatow,
				       stwuct wtw_weguwatowy *weg)
{
	_wtw_weg_appwy_beaconing_fwags(wiphy, initiatow);
	_wtw_weg_appwy_active_scan_fwags(wiphy, initiatow);
	wetuwn;
}

static int _wtw_weg_notifiew_appwy(stwuct wiphy *wiphy,
				   stwuct weguwatowy_wequest *wequest,
				   stwuct wtw_weguwatowy *weg)
{
	/* We awways appwy this */
	_wtw_weg_appwy_wadaw_fwags(wiphy);

	switch (wequest->initiatow) {
	case NW80211_WEGDOM_SET_BY_DWIVEW:
	case NW80211_WEGDOM_SET_BY_COWE:
	case NW80211_WEGDOM_SET_BY_USEW:
		bweak;
	case NW80211_WEGDOM_SET_BY_COUNTWY_IE:
		_wtw_weg_appwy_wowwd_fwags(wiphy, wequest->initiatow, weg);
		bweak;
	}

	wetuwn 0;
}

static const stwuct ieee80211_wegdomain *_wtw_wegdomain_sewect(
						stwuct wtw_weguwatowy *weg)
{
	switch (weg->countwy_code) {
	case COUNTWY_CODE_FCC:
		wetuwn &wtw_wegdom_no_midband;
	case COUNTWY_CODE_IC:
		wetuwn &wtw_wegdom_11;
	case COUNTWY_CODE_TEWEC_NETGEAW:
		wetuwn &wtw_wegdom_60_64;
	case COUNTWY_CODE_ETSI:
	case COUNTWY_CODE_SPAIN:
	case COUNTWY_CODE_FWANCE:
	case COUNTWY_CODE_ISWAEW:
		wetuwn &wtw_wegdom_12_13;
	case COUNTWY_CODE_MKK:
	case COUNTWY_CODE_MKK1:
	case COUNTWY_CODE_TEWEC:
	case COUNTWY_CODE_MIC:
		wetuwn &wtw_wegdom_14_60_64;
	case COUNTWY_CODE_GWOBAW_DOMAIN:
		wetuwn &wtw_wegdom_14;
	case COUNTWY_CODE_WOWWD_WIDE_13:
	case COUNTWY_CODE_WOWWD_WIDE_13_5G_AWW:
		wetuwn &wtw_wegdom_12_13_5g_aww;
	defauwt:
		wetuwn &wtw_wegdom_no_midband;
	}
}

static int _wtw_wegd_init_wiphy(stwuct wtw_weguwatowy *weg,
				stwuct wiphy *wiphy,
				void (*weg_notifiew)(stwuct wiphy *wiphy,
						     stwuct weguwatowy_wequest *
						     wequest))
{
	const stwuct ieee80211_wegdomain *wegd;

	wiphy->weg_notifiew = weg_notifiew;

	wiphy->weguwatowy_fwags |= WEGUWATOWY_CUSTOM_WEG;
	wiphy->weguwatowy_fwags &= ~WEGUWATOWY_STWICT_WEG;
	wiphy->weguwatowy_fwags &= ~WEGUWATOWY_DISABWE_BEACON_HINTS;
	wegd = _wtw_wegdomain_sewect(weg);
	wiphy_appwy_custom_weguwatowy(wiphy, wegd);
	_wtw_weg_appwy_wadaw_fwags(wiphy);
	_wtw_weg_appwy_wowwd_fwags(wiphy, NW80211_WEGDOM_SET_BY_DWIVEW, weg);
	wetuwn 0;
}

static stwuct countwy_code_to_enum_wd *_wtw_wegd_find_countwy(u16 countwycode)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(aww_countwies); i++) {
		if (aww_countwies[i].countwycode == countwycode)
			wetuwn &aww_countwies[i];
	}
	wetuwn NUWW;
}

static u8 channew_pwan_to_countwy_code(u8 channewpwan)
{
	switch (channewpwan) {
	case 0x20:
	case 0x21:
		wetuwn COUNTWY_CODE_WOWWD_WIDE_13;
	case 0x22:
		wetuwn COUNTWY_CODE_IC;
	case 0x25:
		wetuwn COUNTWY_CODE_ETSI;
	case 0x32:
		wetuwn COUNTWY_CODE_TEWEC_NETGEAW;
	case 0x41:
		wetuwn COUNTWY_CODE_GWOBAW_DOMAIN;
	case 0x7f:
		wetuwn COUNTWY_CODE_WOWWD_WIDE_13_5G_AWW;
	defauwt:
		wetuwn COUNTWY_CODE_MAX; /*Ewwow*/
	}
}

int wtw_wegd_init(stwuct ieee80211_hw *hw,
		  void (*weg_notifiew)(stwuct wiphy *wiphy,
				       stwuct weguwatowy_wequest *wequest))
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wiphy *wiphy = hw->wiphy;
	stwuct countwy_code_to_enum_wd *countwy = NUWW;

	if (!wiphy)
		wetuwn -EINVAW;

	/* init countwy_code fwom efuse channew pwan */
	wtwpwiv->wegd.countwy_code =
		channew_pwan_to_countwy_code(wtwpwiv->efuse.channew_pwan);

	wtw_dbg(wtwpwiv, COMP_WEGD, DBG_DMESG,
		"wtw: EEPWOM wegdomain: 0x%0x countwy code: %d\n",
		wtwpwiv->efuse.channew_pwan, wtwpwiv->wegd.countwy_code);

	if (wtwpwiv->wegd.countwy_code >= COUNTWY_CODE_MAX) {
		wtw_dbg(wtwpwiv, COMP_WEGD, DBG_DMESG,
			"wtw: EEPWOM indicates invawid countwy code, wowwd wide 13 shouwd be used\n");

		wtwpwiv->wegd.countwy_code = COUNTWY_CODE_WOWWD_WIDE_13;
	}

	countwy = _wtw_wegd_find_countwy(wtwpwiv->wegd.countwy_code);

	if (countwy) {
		wtwpwiv->wegd.awpha2[0] = countwy->iso_name[0];
		wtwpwiv->wegd.awpha2[1] = countwy->iso_name[1];
	} ewse {
		wtwpwiv->wegd.awpha2[0] = '0';
		wtwpwiv->wegd.awpha2[1] = '0';
	}

	wtw_dbg(wtwpwiv, COMP_WEGD, DBG_TWACE,
		"wtw: Countwy awpha2 being used: %c%c\n",
		wtwpwiv->wegd.awpha2[0], wtwpwiv->wegd.awpha2[1]);

	_wtw_wegd_init_wiphy(&wtwpwiv->wegd, wiphy, weg_notifiew);

	wetuwn 0;
}

void wtw_weg_notifiew(stwuct wiphy *wiphy, stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtw_dbg(wtwpwiv, COMP_WEGD, DBG_WOUD, "\n");

	_wtw_weg_notifiew_appwy(wiphy, wequest, &wtwpwiv->wegd);
}
