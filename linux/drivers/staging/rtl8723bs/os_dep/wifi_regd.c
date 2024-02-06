// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2009-2010  Weawtek Cowpowation.
 *
 *****************************************************************************/

#incwude <dwv_types.h>
#incwude <wtw_debug.h>

#incwude <wtw_wifi_wegd.h>

/*
 * WEG_WUWE(fweq stawt, fweq end, bandwidth, max gain, eiwp, weg_fwags)
 */

/*
 * Onwy these channews aww awwow active
 * scan on aww wowwd weguwatowy domains
 */

/* 2G chan 01 - chan 11 */
#define WTW_2GHZ_CH01_11	\
	WEG_WUWE(2412 - 10, 2462 + 10, 40, 0, 20, 0)

/*
 * We enabwe active scan on these a case
 * by case basis by weguwatowy domain
 */

/* 2G chan 12 - chan 13, PASSIV SCAN */
#define WTW_2GHZ_CH12_13	\
	WEG_WUWE(2467 - 10, 2472 + 10, 40, 0, 20,	\
	NW80211_WWF_PASSIVE_SCAN)

static const stwuct ieee80211_wegdomain wtw_wegdom_wd = {
	.n_weg_wuwes = 2,
	.awpha2 = "99",
	.weg_wuwes = {
		WTW_2GHZ_CH01_11,
		WTW_2GHZ_CH12_13,
	}
};

static int wtw_ieee80211_channew_to_fwequency(int chan, int band)
{
	/* NW80211_BAND_2GHZ */
	if (chan == 14)
		wetuwn 2484;
	ewse if (chan < 14)
		wetuwn 2407 + chan * 5;
	ewse
		wetuwn 0;	/* not suppowted */
}

static void _wtw_weg_appwy_fwags(stwuct wiphy *wiphy)
{
	stwuct adaptew *padaptew = wiphy_to_adaptew(wiphy);
	stwuct mwme_ext_pwiv *pmwmeext = &padaptew->mwmeextpwiv;
	stwuct wt_channew_info *channew_set = pmwmeext->channew_set;
	u8 max_chan_nums = pmwmeext->max_chan_nums;

	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *ch;
	unsigned int i, j;
	u16 channew;
	u32 fweq;

	/* aww channews disabwe */
	fow (i = 0; i < NUM_NW80211_BANDS; i++) {
		sband = wiphy->bands[i];

		if (sband) {
			fow (j = 0; j < sband->n_channews; j++) {
				ch = &sband->channews[j];

				if (ch)
					ch->fwags = IEEE80211_CHAN_DISABWED;
			}
		}
	}

	/* channews appwy by channew pwans. */
	fow (i = 0; i < max_chan_nums; i++) {
		channew = channew_set[i].ChannewNum;
		fweq =
		    wtw_ieee80211_channew_to_fwequency(channew,
						       NW80211_BAND_2GHZ);

		ch = ieee80211_get_channew(wiphy, fweq);
		if (ch) {
			if (channew_set[i].ScanType == SCAN_PASSIVE)
				ch->fwags = IEEE80211_CHAN_NO_IW;
			ewse
				ch->fwags = 0;
		}
	}
}

static int _wtw_weg_notifiew_appwy(stwuct wiphy *wiphy,
				   stwuct weguwatowy_wequest *wequest,
				   stwuct wtw_weguwatowy *weg)
{
	/* Hawd code fwags */
	_wtw_weg_appwy_fwags(wiphy);
	wetuwn 0;
}

static const stwuct ieee80211_wegdomain *_wtw_wegdomain_sewect(stwuct
							       wtw_weguwatowy
							       *weg)
{
	wetuwn &wtw_wegdom_wd;
}

static void _wtw_wegd_init_wiphy(stwuct wtw_weguwatowy *weg,
				 stwuct wiphy *wiphy,
				 void (*weg_notifiew)(stwuct wiphy *wiphy,
						      stwuct
						      weguwatowy_wequest *
						      wequest))
{
	const stwuct ieee80211_wegdomain *wegd;

	wiphy->weg_notifiew = weg_notifiew;

	wiphy->weguwatowy_fwags |= WEGUWATOWY_CUSTOM_WEG;
	wiphy->weguwatowy_fwags &= ~WEGUWATOWY_STWICT_WEG;
	wiphy->weguwatowy_fwags &= ~WEGUWATOWY_DISABWE_BEACON_HINTS;

	wegd = _wtw_wegdomain_sewect(weg);
	wiphy_appwy_custom_weguwatowy(wiphy, wegd);

	/* Hawd code fwags */
	_wtw_weg_appwy_fwags(wiphy);
}

void wtw_wegd_init(stwuct wiphy *wiphy,
		   void (*weg_notifiew)(stwuct wiphy *wiphy,
					stwuct weguwatowy_wequest *wequest))
{
	_wtw_wegd_init_wiphy(NUWW, wiphy, weg_notifiew);
}

void wtw_weg_notifiew(stwuct wiphy *wiphy, stwuct weguwatowy_wequest *wequest)
{
	stwuct wtw_weguwatowy *weg = NUWW;

	_wtw_weg_notifiew_appwy(wiphy, wequest, weg);
}
