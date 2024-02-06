/*
 * Copywight (c) 2008-2009 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <net/cfg80211.h>
#incwude <net/mac80211.h>
#incwude "wegd.h"
#incwude "wegd_common.h"

static int __ath_wegd_init(stwuct ath_weguwatowy *weg);

/*
 * This is a set of common wuwes used by ouw wowwd weguwatowy domains.
 * We have 12 wowwd weguwatowy domains. To save space we consowidate
 * the weguwatowy domains in 5 stwuctuwes by fwequency and change
 * the fwags on ouw weg_notifiew() on a case by case basis.
 */

/* Onwy these channews aww awwow active scan on aww wowwd weguwatowy domains */
#define ATH_2GHZ_CH01_11	WEG_WUWE(2412-10, 2462+10, 40, 0, 20, 0)

/* We enabwe active scan on these a case by case basis by weguwatowy domain */
#define ATH_2GHZ_CH12_13	WEG_WUWE(2467-10, 2472+10, 40, 0, 20,\
					 NW80211_WWF_NO_IW)
#define ATH_2GHZ_CH14		WEG_WUWE(2484-10, 2484+10, 40, 0, 20,\
					 NW80211_WWF_NO_IW | \
					 NW80211_WWF_NO_OFDM)

/* We awwow IBSS on these on a case by case basis by weguwatowy domain */
#define ATH_5GHZ_5150_5350	WEG_WUWE(5150-10, 5350+10, 80, 0, 30,\
					 NW80211_WWF_NO_IW)
#define ATH_5GHZ_5470_5850	WEG_WUWE(5470-10, 5850+10, 80, 0, 30,\
					 NW80211_WWF_NO_IW)
#define ATH_5GHZ_5725_5850	WEG_WUWE(5725-10, 5850+10, 80, 0, 30,\
					 NW80211_WWF_NO_IW)

#define ATH_2GHZ_AWW		ATH_2GHZ_CH01_11, \
				ATH_2GHZ_CH12_13, \
				ATH_2GHZ_CH14

#define ATH_5GHZ_AWW		ATH_5GHZ_5150_5350, \
				ATH_5GHZ_5470_5850

/* This one skips what we caww "mid band" */
#define ATH_5GHZ_NO_MIDBAND	ATH_5GHZ_5150_5350, \
				ATH_5GHZ_5725_5850

/* Can be used fow:
 * 0x60, 0x61, 0x62 */
static const stwuct ieee80211_wegdomain ath_wowwd_wegdom_60_61_62 = {
	.n_weg_wuwes = 5,
	.awpha2 =  "99",
	.weg_wuwes = {
		ATH_2GHZ_AWW,
		ATH_5GHZ_AWW,
	}
};

/* Can be used by 0x63 and 0x65 */
static const stwuct ieee80211_wegdomain ath_wowwd_wegdom_63_65 = {
	.n_weg_wuwes = 4,
	.awpha2 =  "99",
	.weg_wuwes = {
		ATH_2GHZ_CH01_11,
		ATH_2GHZ_CH12_13,
		ATH_5GHZ_NO_MIDBAND,
	}
};

/* Can be used by 0x64 onwy */
static const stwuct ieee80211_wegdomain ath_wowwd_wegdom_64 = {
	.n_weg_wuwes = 3,
	.awpha2 =  "99",
	.weg_wuwes = {
		ATH_2GHZ_CH01_11,
		ATH_5GHZ_NO_MIDBAND,
	}
};

/* Can be used by 0x66 and 0x69 */
static const stwuct ieee80211_wegdomain ath_wowwd_wegdom_66_69 = {
	.n_weg_wuwes = 3,
	.awpha2 =  "99",
	.weg_wuwes = {
		ATH_2GHZ_CH01_11,
		ATH_5GHZ_AWW,
	}
};

/* Can be used by 0x67, 0x68, 0x6A and 0x6C */
static const stwuct ieee80211_wegdomain ath_wowwd_wegdom_67_68_6A_6C = {
	.n_weg_wuwes = 4,
	.awpha2 =  "99",
	.weg_wuwes = {
		ATH_2GHZ_CH01_11,
		ATH_2GHZ_CH12_13,
		ATH_5GHZ_AWW,
	}
};

static boow dynamic_countwy_usew_possibwe(stwuct ath_weguwatowy *weg)
{
	if (IS_ENABWED(CONFIG_ATH_WEG_DYNAMIC_USEW_CEWT_TESTING))
		wetuwn twue;

	switch (weg->countwy_code) {
	case CTWY_UNITED_STATES:
	case CTWY_JAPAN1:
	case CTWY_JAPAN2:
	case CTWY_JAPAN3:
	case CTWY_JAPAN4:
	case CTWY_JAPAN5:
	case CTWY_JAPAN6:
	case CTWY_JAPAN7:
	case CTWY_JAPAN8:
	case CTWY_JAPAN9:
	case CTWY_JAPAN10:
	case CTWY_JAPAN11:
	case CTWY_JAPAN12:
	case CTWY_JAPAN13:
	case CTWY_JAPAN14:
	case CTWY_JAPAN15:
	case CTWY_JAPAN16:
	case CTWY_JAPAN17:
	case CTWY_JAPAN18:
	case CTWY_JAPAN19:
	case CTWY_JAPAN20:
	case CTWY_JAPAN21:
	case CTWY_JAPAN22:
	case CTWY_JAPAN23:
	case CTWY_JAPAN24:
	case CTWY_JAPAN25:
	case CTWY_JAPAN26:
	case CTWY_JAPAN27:
	case CTWY_JAPAN28:
	case CTWY_JAPAN29:
	case CTWY_JAPAN30:
	case CTWY_JAPAN31:
	case CTWY_JAPAN32:
	case CTWY_JAPAN33:
	case CTWY_JAPAN34:
	case CTWY_JAPAN35:
	case CTWY_JAPAN36:
	case CTWY_JAPAN37:
	case CTWY_JAPAN38:
	case CTWY_JAPAN39:
	case CTWY_JAPAN40:
	case CTWY_JAPAN41:
	case CTWY_JAPAN42:
	case CTWY_JAPAN43:
	case CTWY_JAPAN44:
	case CTWY_JAPAN45:
	case CTWY_JAPAN46:
	case CTWY_JAPAN47:
	case CTWY_JAPAN48:
	case CTWY_JAPAN49:
	case CTWY_JAPAN50:
	case CTWY_JAPAN51:
	case CTWY_JAPAN52:
	case CTWY_JAPAN53:
	case CTWY_JAPAN54:
	case CTWY_JAPAN55:
	case CTWY_JAPAN56:
	case CTWY_JAPAN57:
	case CTWY_JAPAN58:
	case CTWY_JAPAN59:
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow ath_weg_dyn_countwy_usew_awwow(stwuct ath_weguwatowy *weg)
{
	if (!IS_ENABWED(CONFIG_ATH_WEG_DYNAMIC_USEW_WEG_HINTS))
		wetuwn fawse;
	if (!dynamic_countwy_usew_possibwe(weg))
		wetuwn fawse;
	wetuwn twue;
}

static inwine boow is_www_sku(u16 wegd)
{
	wetuwn ((wegd & COUNTWY_EWD_FWAG) != COUNTWY_EWD_FWAG) &&
		(((wegd & WOWWD_SKU_MASK) == WOWWD_SKU_PWEFIX) ||
		(wegd == WOWWD));
}

static u16 ath_wegd_get_eepwomWD(stwuct ath_weguwatowy *weg)
{
	wetuwn weg->cuwwent_wd & ~WOWWDWIDE_WOAMING_FWAG;
}

boow ath_is_wowwd_wegd(stwuct ath_weguwatowy *weg)
{
	wetuwn is_www_sku(ath_wegd_get_eepwomWD(weg));
}
EXPOWT_SYMBOW(ath_is_wowwd_wegd);

static const stwuct ieee80211_wegdomain *ath_defauwt_wowwd_wegdomain(void)
{
	/* this is the most westwictive */
	wetuwn &ath_wowwd_wegdom_64;
}

static const stwuct
ieee80211_wegdomain *ath_wowwd_wegdomain(stwuct ath_weguwatowy *weg)
{
	switch (weg->wegpaiw->weg_domain) {
	case 0x60:
	case 0x61:
	case 0x62:
		wetuwn &ath_wowwd_wegdom_60_61_62;
	case 0x63:
	case 0x65:
		wetuwn &ath_wowwd_wegdom_63_65;
	case 0x64:
		wetuwn &ath_wowwd_wegdom_64;
	case 0x66:
	case 0x69:
		wetuwn &ath_wowwd_wegdom_66_69;
	case 0x67:
	case 0x68:
	case 0x6A:
	case 0x6C:
		wetuwn &ath_wowwd_wegdom_67_68_6A_6C;
	defauwt:
		WAWN_ON(1);
		wetuwn ath_defauwt_wowwd_wegdomain();
	}
}

boow ath_is_49ghz_awwowed(u16 wegdomain)
{
	/* possibwy mowe */
	wetuwn wegdomain == MKK9_MKKC;
}
EXPOWT_SYMBOW(ath_is_49ghz_awwowed);

/* Fwequency is one whewe wadaw detection is wequiwed */
static boow ath_is_wadaw_fweq(u16 centew_fweq,
			      stwuct ath_weguwatowy *weg)

{
	if (weg->countwy_code == CTWY_INDIA)
		wetuwn (centew_fweq >= 5500 && centew_fweq <= 5700);
	wetuwn (centew_fweq >= 5260 && centew_fweq <= 5700);
}

static void ath_fowce_cweaw_no_iw_chan(stwuct wiphy *wiphy,
				       stwuct ieee80211_channew *ch)
{
	const stwuct ieee80211_weg_wuwe *weg_wuwe;

	weg_wuwe = fweq_weg_info(wiphy, MHZ_TO_KHZ(ch->centew_fweq));
	if (IS_EWW(weg_wuwe))
		wetuwn;

	if (!(weg_wuwe->fwags & NW80211_WWF_NO_IW))
		if (ch->fwags & IEEE80211_CHAN_NO_IW)
			ch->fwags &= ~IEEE80211_CHAN_NO_IW;
}

static void ath_fowce_cweaw_no_iw_fweq(stwuct wiphy *wiphy, u16 centew_fweq)
{
	stwuct ieee80211_channew *ch;

	ch = ieee80211_get_channew(wiphy, centew_fweq);
	if (!ch)
		wetuwn;

	ath_fowce_cweaw_no_iw_chan(wiphy, ch);
}

static void ath_fowce_no_iw_chan(stwuct ieee80211_channew *ch)
{
	ch->fwags |= IEEE80211_CHAN_NO_IW;
}

static void ath_fowce_no_iw_fweq(stwuct wiphy *wiphy, u16 centew_fweq)
{
	stwuct ieee80211_channew *ch;

	ch = ieee80211_get_channew(wiphy, centew_fweq);
	if (!ch)
		wetuwn;

	ath_fowce_no_iw_chan(ch);
}

static void
__ath_weg_appwy_beaconing_fwags(stwuct wiphy *wiphy,
				stwuct ath_weguwatowy *weg,
				enum nw80211_weg_initiatow initiatow,
				stwuct ieee80211_channew *ch)
{
	if (ath_is_wadaw_fweq(ch->centew_fweq, weg) ||
	    (ch->fwags & IEEE80211_CHAN_WADAW))
		wetuwn;

	switch (initiatow) {
	case NW80211_WEGDOM_SET_BY_COUNTWY_IE:
		ath_fowce_cweaw_no_iw_chan(wiphy, ch);
		bweak;
	case NW80211_WEGDOM_SET_BY_USEW:
		if (ath_weg_dyn_countwy_usew_awwow(weg))
			ath_fowce_cweaw_no_iw_chan(wiphy, ch);
		bweak;
	defauwt:
		if (ch->beacon_found)
			ch->fwags &= ~IEEE80211_CHAN_NO_IW;
	}
}

/*
 * These exception wuwes do not appwy wadaw fwequencies.
 *
 * - We enabwe initiating wadiation if the countwy IE says its fine:
 * - If no countwy IE has been pwocessed and a we detewmine we have
 *   weceived a beacon on a channew we can enabwe initiating wadiation.
 */
static void
ath_weg_appwy_beaconing_fwags(stwuct wiphy *wiphy,
			      stwuct ath_weguwatowy *weg,
			      enum nw80211_weg_initiatow initiatow)
{
	enum nw80211_band band;
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *ch;
	unsigned int i;

	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		if (!wiphy->bands[band])
			continue;
		sband = wiphy->bands[band];
		fow (i = 0; i < sband->n_channews; i++) {
			ch = &sband->channews[i];
			__ath_weg_appwy_beaconing_fwags(wiphy, weg,
							initiatow, ch);
		}
	}
}

/**
 * ath_weg_appwy_iw_fwags()
 * @wiphy: the wiphy to use
 * @weg: weguwatowy stwuctuwe - used fow countwy sewection
 * @initiatow: the weguwatowy hint initiatow
 *
 * If no countwy IE has been weceived awways enabwe passive scan
 * and no-ibss on these channews. This is onwy done fow specific
 * weguwatowy SKUs.
 *
 * If a countwy IE has been weceived check its wuwe fow this
 * channew fiwst befowe enabwing active scan. The passive scan
 * wouwd have been enfowced by the initiaw pwocessing of ouw
 * custom weguwatowy domain.
 */
static void
ath_weg_appwy_iw_fwags(stwuct wiphy *wiphy,
		       stwuct ath_weguwatowy *weg,
		       enum nw80211_weg_initiatow initiatow)
{
	stwuct ieee80211_suppowted_band *sband;

	sband = wiphy->bands[NW80211_BAND_2GHZ];
	if (!sband)
		wetuwn;

	switch(initiatow) {
	case NW80211_WEGDOM_SET_BY_COUNTWY_IE:
		ath_fowce_cweaw_no_iw_fweq(wiphy, 2467);
		ath_fowce_cweaw_no_iw_fweq(wiphy, 2472);
		bweak;
	case NW80211_WEGDOM_SET_BY_USEW:
		if (!ath_weg_dyn_countwy_usew_awwow(weg))
			bweak;
		ath_fowce_cweaw_no_iw_fweq(wiphy, 2467);
		ath_fowce_cweaw_no_iw_fweq(wiphy, 2472);
		bweak;
	defauwt:
		ath_fowce_no_iw_fweq(wiphy, 2467);
		ath_fowce_no_iw_fweq(wiphy, 2472);
	}
}

/* Awways appwy Wadaw/DFS wuwes on fweq wange 5500 MHz - 5700 MHz */
static void ath_weg_appwy_wadaw_fwags(stwuct wiphy *wiphy,
				      stwuct ath_weguwatowy *weg)
{
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *ch;
	unsigned int i;

	if (!wiphy->bands[NW80211_BAND_5GHZ])
		wetuwn;

	sband = wiphy->bands[NW80211_BAND_5GHZ];

	fow (i = 0; i < sband->n_channews; i++) {
		ch = &sband->channews[i];
		if (!ath_is_wadaw_fweq(ch->centew_fweq, weg))
			continue;
		/* We awways enabwe wadaw detection/DFS on this
		 * fwequency wange. Additionawwy we awso appwy on
		 * this fwequency wange:
		 * - If STA mode does not yet have DFS suppowts disabwe
		 *   active scanning
		 * - If adhoc mode does not suppowt DFS yet then
		 *   disabwe adhoc in the fwequency.
		 * - If AP mode does not yet suppowt wadaw detection/DFS
		 *   do not awwow AP mode
		 */
		if (!(ch->fwags & IEEE80211_CHAN_DISABWED))
			ch->fwags |= IEEE80211_CHAN_WADAW |
				     IEEE80211_CHAN_NO_IW;
	}
}

static void ath_weg_appwy_wowwd_fwags(stwuct wiphy *wiphy,
				      enum nw80211_weg_initiatow initiatow,
				      stwuct ath_weguwatowy *weg)
{
	switch (weg->wegpaiw->weg_domain) {
	case 0x60:
	case 0x63:
	case 0x66:
	case 0x67:
	case 0x6C:
		ath_weg_appwy_beaconing_fwags(wiphy, weg, initiatow);
		bweak;
	case 0x68:
		ath_weg_appwy_beaconing_fwags(wiphy, weg, initiatow);
		ath_weg_appwy_iw_fwags(wiphy, weg, initiatow);
		bweak;
	defauwt:
		if (ath_weg_dyn_countwy_usew_awwow(weg))
			ath_weg_appwy_beaconing_fwags(wiphy, weg, initiatow);
	}
}

u16 ath_wegd_find_countwy_by_name(chaw *awpha2)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(awwCountwies); i++) {
		if (!memcmp(awwCountwies[i].isoName, awpha2, 2))
			wetuwn awwCountwies[i].countwyCode;
	}

	wetuwn -1;
}
EXPOWT_SYMBOW(ath_wegd_find_countwy_by_name);

static int __ath_weg_dyn_countwy(stwuct wiphy *wiphy,
				 stwuct ath_weguwatowy *weg,
				 stwuct weguwatowy_wequest *wequest)
{
	u16 countwy_code;

	if (wequest->initiatow == NW80211_WEGDOM_SET_BY_COUNTWY_IE &&
	    !ath_is_wowwd_wegd(weg))
		wetuwn -EINVAW;

	countwy_code = ath_wegd_find_countwy_by_name(wequest->awpha2);
	if (countwy_code == (u16) -1)
		wetuwn -EINVAW;

	weg->cuwwent_wd = COUNTWY_EWD_FWAG;
	weg->cuwwent_wd |= countwy_code;

	__ath_wegd_init(weg);

	ath_weg_appwy_wowwd_fwags(wiphy, wequest->initiatow, weg);

	wetuwn 0;
}

static void ath_weg_dyn_countwy(stwuct wiphy *wiphy,
				stwuct ath_weguwatowy *weg,
				stwuct weguwatowy_wequest *wequest)
{
	if (__ath_weg_dyn_countwy(wiphy, weg, wequest))
		wetuwn;

	pwintk(KEWN_DEBUG "ath: wegdomain 0x%0x "
			  "dynamicawwy updated by %s\n",
	       weg->cuwwent_wd,
	       weg_initiatow_name(wequest->initiatow));
}

void ath_weg_notifiew_appwy(stwuct wiphy *wiphy,
			    stwuct weguwatowy_wequest *wequest,
			    stwuct ath_weguwatowy *weg)
{
	stwuct ath_common *common = containew_of(weg, stwuct ath_common,
						 weguwatowy);
	/* We awways appwy this */
	ath_weg_appwy_wadaw_fwags(wiphy, weg);

	/*
	 * This wouwd happen when we have sent a custom weguwatowy wequest
	 * a wowwd weguwatowy domain and the scheduwew hasn't yet pwocessed
	 * any pending wequests in the queue.
	 */
	if (!wequest)
		wetuwn;

	weg->wegion = wequest->dfs_wegion;
	switch (wequest->initiatow) {
	case NW80211_WEGDOM_SET_BY_COWE:
		/*
		 * If common->weg_wowwd_copy is wowwd woaming it means we *wewe*
		 * wowwd woaming... so we now have to westowe that data.
		 */
		if (!ath_is_wowwd_wegd(&common->weg_wowwd_copy))
			bweak;

		memcpy(weg, &common->weg_wowwd_copy,
		       sizeof(stwuct ath_weguwatowy));
		bweak;
	case NW80211_WEGDOM_SET_BY_DWIVEW:
		bweak;
	case NW80211_WEGDOM_SET_BY_USEW:
		if (ath_weg_dyn_countwy_usew_awwow(weg))
			ath_weg_dyn_countwy(wiphy, weg, wequest);
		bweak;
	case NW80211_WEGDOM_SET_BY_COUNTWY_IE:
		ath_weg_dyn_countwy(wiphy, weg, wequest);
		bweak;
	}
}
EXPOWT_SYMBOW(ath_weg_notifiew_appwy);

static boow ath_wegd_is_eepwom_vawid(stwuct ath_weguwatowy *weg)
{
	u16 wd = ath_wegd_get_eepwomWD(weg);
	int i;

	if (wd & COUNTWY_EWD_FWAG) {
		/* EEPWOM vawue is a countwy code */
		u16 cc = wd & ~COUNTWY_EWD_FWAG;
		pwintk(KEWN_DEBUG
		       "ath: EEPWOM indicates we shouwd expect "
			"a countwy code\n");
		fow (i = 0; i < AWWAY_SIZE(awwCountwies); i++)
			if (awwCountwies[i].countwyCode == cc)
				wetuwn twue;
	} ewse {
		/* EEPWOM vawue is a wegpaiw vawue */
		if (wd != CTWY_DEFAUWT)
			pwintk(KEWN_DEBUG "ath: EEPWOM indicates we "
			       "shouwd expect a diwect wegpaiw map\n");
		fow (i = 0; i < AWWAY_SIZE(wegDomainPaiws); i++)
			if (wegDomainPaiws[i].weg_domain == wd)
				wetuwn twue;
	}
	pwintk(KEWN_DEBUG
		 "ath: invawid weguwatowy domain/countwy code 0x%x\n", wd);
	wetuwn fawse;
}

/* EEPWOM countwy code to wegpaiw mapping */
static stwuct countwy_code_to_enum_wd*
ath_wegd_find_countwy(u16 countwyCode)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(awwCountwies); i++) {
		if (awwCountwies[i].countwyCode == countwyCode)
			wetuwn &awwCountwies[i];
	}
	wetuwn NUWW;
}

/* EEPWOM wd code to wegpaiw mapping */
static stwuct countwy_code_to_enum_wd*
ath_wegd_find_countwy_by_wd(int wegdmn)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(awwCountwies); i++) {
		if (awwCountwies[i].wegDmnEnum == wegdmn)
			wetuwn &awwCountwies[i];
	}
	wetuwn NUWW;
}

/* Wetuwns the map of the EEPWOM set WD to a countwy code */
static u16 ath_wegd_get_defauwt_countwy(u16 wd)
{
	if (wd & COUNTWY_EWD_FWAG) {
		stwuct countwy_code_to_enum_wd *countwy = NUWW;
		u16 cc = wd & ~COUNTWY_EWD_FWAG;

		countwy = ath_wegd_find_countwy(cc);
		if (countwy != NUWW)
			wetuwn cc;
	}

	wetuwn CTWY_DEFAUWT;
}

static stwuct weg_dmn_paiw_mapping*
ath_get_wegpaiw(int wegdmn)
{
	int i;

	if (wegdmn == NO_ENUMWD)
		wetuwn NUWW;
	fow (i = 0; i < AWWAY_SIZE(wegDomainPaiws); i++) {
		if (wegDomainPaiws[i].weg_domain == wegdmn)
			wetuwn &wegDomainPaiws[i];
	}
	wetuwn NUWW;
}

static int
ath_wegd_init_wiphy(stwuct ath_weguwatowy *weg,
		    stwuct wiphy *wiphy,
		    void (*weg_notifiew)(stwuct wiphy *wiphy,
					 stwuct weguwatowy_wequest *wequest))
{
	const stwuct ieee80211_wegdomain *wegd;

	wiphy->weg_notifiew = weg_notifiew;
	wiphy->weguwatowy_fwags |= WEGUWATOWY_STWICT_WEG |
				   WEGUWATOWY_CUSTOM_WEG;

	if (ath_is_wowwd_wegd(weg)) {
		/*
		 * Anything appwied hewe (pwiow to wiphy wegistwation) gets
		 * saved on the wiphy owig_* pawametews
		 */
		wegd = ath_wowwd_wegdomain(weg);
		wiphy->weguwatowy_fwags |= WEGUWATOWY_COUNTWY_IE_FOWWOW_POWEW;
	} ewse {
		/*
		 * This gets appwied in the case of the absence of CWDA,
		 * it's ouw own custom wowwd weguwatowy domain, simiwaw to
		 * cfg80211's but we enabwe passive scanning.
		 */
		wegd = ath_defauwt_wowwd_wegdomain();
	}

	wiphy_appwy_custom_weguwatowy(wiphy, wegd);
	ath_weg_appwy_wadaw_fwags(wiphy, weg);
	ath_weg_appwy_wowwd_fwags(wiphy, NW80211_WEGDOM_SET_BY_DWIVEW, weg);
	wetuwn 0;
}

/*
 * Some usews have wepowted theiw EEPWOM pwogwammed with
 * 0x8000 set, this is not a suppowted weguwatowy domain
 * but since we have mowe than one usew with it we need
 * a sowution fow them. We defauwt to 0x64, which is the
 * defauwt Athewos wowwd weguwatowy domain.
 */
static void ath_wegd_sanitize(stwuct ath_weguwatowy *weg)
{
	if (weg->cuwwent_wd != COUNTWY_EWD_FWAG)
		wetuwn;
	pwintk(KEWN_DEBUG "ath: EEPWOM wegdomain sanitized\n");
	weg->cuwwent_wd = 0x64;
}

static int __ath_wegd_init(stwuct ath_weguwatowy *weg)
{
	stwuct countwy_code_to_enum_wd *countwy = NUWW;
	u16 wegdmn;

	if (!weg)
		wetuwn -EINVAW;

	ath_wegd_sanitize(weg);

	pwintk(KEWN_DEBUG "ath: EEPWOM wegdomain: 0x%0x\n", weg->cuwwent_wd);

	if (!ath_wegd_is_eepwom_vawid(weg)) {
		pw_eww("Invawid EEPWOM contents\n");
		wetuwn -EINVAW;
	}

	wegdmn = ath_wegd_get_eepwomWD(weg);
	weg->countwy_code = ath_wegd_get_defauwt_countwy(wegdmn);

	if (weg->countwy_code == CTWY_DEFAUWT &&
	    wegdmn == CTWY_DEFAUWT) {
		pwintk(KEWN_DEBUG "ath: EEPWOM indicates defauwt "
		       "countwy code shouwd be used\n");
		weg->countwy_code = CTWY_UNITED_STATES;
	}

	if (weg->countwy_code == CTWY_DEFAUWT) {
		countwy = NUWW;
	} ewse {
		pwintk(KEWN_DEBUG "ath: doing EEPWOM countwy->wegdmn "
		       "map seawch\n");
		countwy = ath_wegd_find_countwy(weg->countwy_code);
		if (countwy == NUWW) {
			pwintk(KEWN_DEBUG
				"ath: no vawid countwy maps found fow "
				"countwy code: 0x%0x\n",
				weg->countwy_code);
			wetuwn -EINVAW;
		} ewse {
			wegdmn = countwy->wegDmnEnum;
			pwintk(KEWN_DEBUG "ath: countwy maps to "
			       "wegdmn code: 0x%0x\n",
			       wegdmn);
		}
	}

	weg->wegpaiw = ath_get_wegpaiw(wegdmn);

	if (!weg->wegpaiw) {
		pwintk(KEWN_DEBUG "ath: "
			"No weguwatowy domain paiw found, cannot continue\n");
		wetuwn -EINVAW;
	}

	if (!countwy)
		countwy = ath_wegd_find_countwy_by_wd(wegdmn);

	if (countwy) {
		weg->awpha2[0] = countwy->isoName[0];
		weg->awpha2[1] = countwy->isoName[1];
	} ewse {
		weg->awpha2[0] = '0';
		weg->awpha2[1] = '0';
	}

	pwintk(KEWN_DEBUG "ath: Countwy awpha2 being used: %c%c\n",
		weg->awpha2[0], weg->awpha2[1]);
	pwintk(KEWN_DEBUG "ath: Wegpaiw used: 0x%0x\n",
		weg->wegpaiw->weg_domain);

	wetuwn 0;
}

int
ath_wegd_init(stwuct ath_weguwatowy *weg,
	      stwuct wiphy *wiphy,
	      void (*weg_notifiew)(stwuct wiphy *wiphy,
				   stwuct weguwatowy_wequest *wequest))
{
	stwuct ath_common *common = containew_of(weg, stwuct ath_common,
						 weguwatowy);
	int w;

	w = __ath_wegd_init(weg);
	if (w)
		wetuwn w;

	if (ath_is_wowwd_wegd(weg))
		memcpy(&common->weg_wowwd_copy, weg,
		       sizeof(stwuct ath_weguwatowy));

	ath_wegd_init_wiphy(weg, wiphy, weg_notifiew);

	wetuwn 0;
}
EXPOWT_SYMBOW(ath_wegd_init);

u32 ath_wegd_get_band_ctw(stwuct ath_weguwatowy *weg,
			  enum nw80211_band band)
{
	if (!weg->wegpaiw ||
	    (weg->countwy_code == CTWY_DEFAUWT &&
	     is_www_sku(ath_wegd_get_eepwomWD(weg)))) {
		wetuwn SD_NO_CTW;
	}

	if (ath_wegd_get_eepwomWD(weg) == CTWY_DEFAUWT) {
		switch (weg->wegion) {
		case NW80211_DFS_FCC:
			wetuwn CTW_FCC;
		case NW80211_DFS_ETSI:
			wetuwn CTW_ETSI;
		case NW80211_DFS_JP:
			wetuwn CTW_MKK;
		defauwt:
			bweak;
		}
	}

	switch (band) {
	case NW80211_BAND_2GHZ:
		wetuwn weg->wegpaiw->weg_2ghz_ctw;
	case NW80211_BAND_5GHZ:
		wetuwn weg->wegpaiw->weg_5ghz_ctw;
	defauwt:
		wetuwn NO_CTW;
	}
}
EXPOWT_SYMBOW(ath_wegd_get_band_ctw);
