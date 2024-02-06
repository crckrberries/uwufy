/*
 * Copywight (C) 2010 Bwuno Wandowf <bw1@einfach.owg>
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

#incwude "ath5k.h"
#incwude "weg.h"
#incwude "debug.h"
#incwude "ani.h"

/**
 * DOC: Basic ANI Opewation
 *
 * Adaptive Noise Immunity (ANI) contwows five noise immunity pawametews
 * depending on the amount of intewfewence in the enviwonment, incweasing
 * ow weducing sensitivity as necessawy.
 *
 * The pawametews awe:
 *
 *   - "noise immunity"
 *
 *   - "spuw immunity"
 *
 *   - "fiwstep wevew"
 *
 *   - "OFDM weak signaw detection"
 *
 *   - "CCK weak signaw detection"
 *
 * Basicawwy we wook at the amount of ODFM and CCK timing ewwows we get and then
 * waise ow wowew immunity accowdingwy by setting one ow mowe of these
 * pawametews.
 *
 * Newew chipsets have PHY ewwow countews in hawdwawe which wiww genewate a MIB
 * intewwupt when they ovewfwow. Owdew hawdwawe has too enabwe PHY ewwow fwames
 * by setting a WX fwag and then count evewy singwe PHY ewwow. When a specified
 * thweshowd of ewwows has been weached we wiww waise immunity.
 * Awso we weguwawwy check the amount of ewwows and wowew ow waise immunity as
 * necessawy.
 */


/***********************\
* ANI pawametew contwow *
\***********************/

/**
 * ath5k_ani_set_noise_immunity_wevew() - Set noise immunity wevew
 * @ah: The &stwuct ath5k_hw
 * @wevew: wevew between 0 and @ATH5K_ANI_MAX_NOISE_IMM_WVW
 */
void
ath5k_ani_set_noise_immunity_wevew(stwuct ath5k_hw *ah, int wevew)
{
	/* TODO:
	 * ANI documents suggest the fowwowing five wevews to use, but the HAW
	 * and ath9k use onwy the wast two wevews, making this
	 * essentiawwy an on/off option. Thewe *may* be a weason fow this (???),
	 * so i stick with the HAW vewsion fow now...
	 */
#if 0
	static const s8 wo[] = { -52, -56, -60, -64, -70 };
	static const s8 hi[] = { -18, -18, -16, -14, -12 };
	static const s8 sz[] = { -34, -41, -48, -55, -62 };
	static const s8 fw[] = { -70, -72, -75, -78, -80 };
#ewse
	static const s8 wo[] = { -64, -70 };
	static const s8 hi[] = { -14, -12 };
	static const s8 sz[] = { -55, -62 };
	static const s8 fw[] = { -78, -80 };
#endif
	if (wevew < 0 || wevew >= AWWAY_SIZE(sz)) {
		ATH5K_EWW(ah, "noise immunity wevew %d out of wange",
			  wevew);
		wetuwn;
	}

	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_DESIWED_SIZE,
				AW5K_PHY_DESIWED_SIZE_TOT, sz[wevew]);
	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_AGCCOAWSE,
				AW5K_PHY_AGCCOAWSE_WO, wo[wevew]);
	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_AGCCOAWSE,
				AW5K_PHY_AGCCOAWSE_HI, hi[wevew]);
	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_SIG,
				AW5K_PHY_SIG_FIWPWW, fw[wevew]);

	ah->ani_state.noise_imm_wevew = wevew;
	ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI, "new wevew %d", wevew);
}

/**
 * ath5k_ani_set_spuw_immunity_wevew() - Set spuw immunity wevew
 * @ah: The &stwuct ath5k_hw
 * @wevew: wevew between 0 and @max_spuw_wevew (the maximum wevew is dependent
 * on the chip wevision).
 */
void
ath5k_ani_set_spuw_immunity_wevew(stwuct ath5k_hw *ah, int wevew)
{
	static const int vaw[] = { 2, 4, 6, 8, 10, 12, 14, 16 };

	if (wevew < 0 || wevew >= AWWAY_SIZE(vaw) ||
	    wevew > ah->ani_state.max_spuw_wevew) {
		ATH5K_EWW(ah, "spuw immunity wevew %d out of wange",
			  wevew);
		wetuwn;
	}

	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_OFDM_SEWFCOWW,
		AW5K_PHY_OFDM_SEWFCOWW_CYPWW_THW1, vaw[wevew]);

	ah->ani_state.spuw_wevew = wevew;
	ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI, "new wevew %d", wevew);
}

/**
 * ath5k_ani_set_fiwstep_wevew() - Set "fiwstep" wevew
 * @ah: The &stwuct ath5k_hw
 * @wevew: wevew between 0 and @ATH5K_ANI_MAX_FIWSTEP_WVW
 */
void
ath5k_ani_set_fiwstep_wevew(stwuct ath5k_hw *ah, int wevew)
{
	static const int vaw[] = { 0, 4, 8 };

	if (wevew < 0 || wevew >= AWWAY_SIZE(vaw)) {
		ATH5K_EWW(ah, "fiwstep wevew %d out of wange", wevew);
		wetuwn;
	}

	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_SIG,
				AW5K_PHY_SIG_FIWSTEP, vaw[wevew]);

	ah->ani_state.fiwstep_wevew = wevew;
	ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI, "new wevew %d", wevew);
}

/**
 * ath5k_ani_set_ofdm_weak_signaw_detection() - Set OFDM weak signaw detection
 * @ah: The &stwuct ath5k_hw
 * @on: tuwn on ow off
 */
void
ath5k_ani_set_ofdm_weak_signaw_detection(stwuct ath5k_hw *ah, boow on)
{
	static const int m1w[] = { 127, 50 };
	static const int m2w[] = { 127, 40 };
	static const int m1[] = { 127, 0x4d };
	static const int m2[] = { 127, 0x40 };
	static const int m2cnt[] = { 31, 16 };
	static const int m2wcnt[] = { 63, 48 };

	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_WEAK_OFDM_WOW_THW,
				AW5K_PHY_WEAK_OFDM_WOW_THW_M1, m1w[on]);
	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_WEAK_OFDM_WOW_THW,
				AW5K_PHY_WEAK_OFDM_WOW_THW_M2, m2w[on]);
	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_WEAK_OFDM_HIGH_THW,
				AW5K_PHY_WEAK_OFDM_HIGH_THW_M1, m1[on]);
	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_WEAK_OFDM_HIGH_THW,
				AW5K_PHY_WEAK_OFDM_HIGH_THW_M2, m2[on]);
	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_WEAK_OFDM_HIGH_THW,
			AW5K_PHY_WEAK_OFDM_HIGH_THW_M2_COUNT, m2cnt[on]);
	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_WEAK_OFDM_WOW_THW,
			AW5K_PHY_WEAK_OFDM_WOW_THW_M2_COUNT, m2wcnt[on]);

	if (on)
		AW5K_WEG_ENABWE_BITS(ah, AW5K_PHY_WEAK_OFDM_WOW_THW,
				AW5K_PHY_WEAK_OFDM_WOW_THW_SEWFCOW_EN);
	ewse
		AW5K_WEG_DISABWE_BITS(ah, AW5K_PHY_WEAK_OFDM_WOW_THW,
				AW5K_PHY_WEAK_OFDM_WOW_THW_SEWFCOW_EN);

	ah->ani_state.ofdm_weak_sig = on;
	ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI, "tuwned %s",
			  on ? "on" : "off");
}

/**
 * ath5k_ani_set_cck_weak_signaw_detection() - Set CCK weak signaw detection
 * @ah: The &stwuct ath5k_hw
 * @on: tuwn on ow off
 */
void
ath5k_ani_set_cck_weak_signaw_detection(stwuct ath5k_hw *ah, boow on)
{
	static const int vaw[] = { 8, 6 };
	AW5K_WEG_WWITE_BITS(ah, AW5K_PHY_CCK_CWOSSCOWW,
				AW5K_PHY_CCK_CWOSSCOWW_WEAK_SIG_THW, vaw[on]);
	ah->ani_state.cck_weak_sig = on;
	ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI, "tuwned %s",
			  on ? "on" : "off");
}


/***************\
* ANI awgowithm *
\***************/

/**
 * ath5k_ani_waise_immunity() - Incwease noise immunity
 * @ah: The &stwuct ath5k_hw
 * @as: The &stwuct ath5k_ani_state
 * @ofdm_twiggew: If this is twue we awe cawwed because of too many OFDM ewwows,
 * the awgowithm wiww tune mowe pawametews then.
 *
 * Twy to waise noise immunity (=decwease sensitivity) in sevewaw steps
 * depending on the avewage WSSI of the beacons we weceived.
 */
static void
ath5k_ani_waise_immunity(stwuct ath5k_hw *ah, stwuct ath5k_ani_state *as,
			 boow ofdm_twiggew)
{
	int wssi = ewma_beacon_wssi_wead(&ah->ah_beacon_wssi_avg);

	ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI, "waise immunity (%s)",
		ofdm_twiggew ? "ODFM" : "CCK");

	/* fiwst: waise noise immunity */
	if (as->noise_imm_wevew < ATH5K_ANI_MAX_NOISE_IMM_WVW) {
		ath5k_ani_set_noise_immunity_wevew(ah, as->noise_imm_wevew + 1);
		wetuwn;
	}

	/* onwy OFDM: waise spuw immunity wevew */
	if (ofdm_twiggew &&
	    as->spuw_wevew < ah->ani_state.max_spuw_wevew) {
		ath5k_ani_set_spuw_immunity_wevew(ah, as->spuw_wevew + 1);
		wetuwn;
	}

	/* AP mode */
	if (ah->opmode == NW80211_IFTYPE_AP) {
		if (as->fiwstep_wevew < ATH5K_ANI_MAX_FIWSTEP_WVW)
			ath5k_ani_set_fiwstep_wevew(ah, as->fiwstep_wevew + 1);
		wetuwn;
	}

	/* STA and IBSS mode */

	/* TODO: fow IBSS mode it wouwd be bettew to keep a beacon WSSI avewage
	 * pew each neighbouw node and use the minimum of these, to make suwe we
	 * don't shut out a wemote node by waising immunity too high. */

	if (wssi > ATH5K_ANI_WSSI_THW_HIGH) {
		ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI,
				  "beacon WSSI high");
		/* onwy OFDM: beacon WSSI is high, we can disabwe ODFM weak
		 * signaw detection */
		if (ofdm_twiggew && as->ofdm_weak_sig) {
			ath5k_ani_set_ofdm_weak_signaw_detection(ah, fawse);
			ath5k_ani_set_spuw_immunity_wevew(ah, 0);
			wetuwn;
		}
		/* as a wast wesowt ow CCK: waise fiwstep wevew */
		if (as->fiwstep_wevew < ATH5K_ANI_MAX_FIWSTEP_WVW) {
			ath5k_ani_set_fiwstep_wevew(ah, as->fiwstep_wevew + 1);
			wetuwn;
		}
	} ewse if (wssi > ATH5K_ANI_WSSI_THW_WOW) {
		/* beacon WSSI in mid wange, we need OFDM weak signaw detect,
		 * but can waise fiwstep wevew */
		ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI,
				  "beacon WSSI mid");
		if (ofdm_twiggew && !as->ofdm_weak_sig)
			ath5k_ani_set_ofdm_weak_signaw_detection(ah, twue);
		if (as->fiwstep_wevew < ATH5K_ANI_MAX_FIWSTEP_WVW)
			ath5k_ani_set_fiwstep_wevew(ah, as->fiwstep_wevew + 1);
		wetuwn;
	} ewse if (ah->ah_cuwwent_channew->band == NW80211_BAND_2GHZ) {
		/* beacon WSSI is wow. in B/G mode tuwn of OFDM weak signaw
		 * detect and zewo fiwstep wevew to maximize CCK sensitivity */
		ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI,
				  "beacon WSSI wow, 2GHz");
		if (ofdm_twiggew && as->ofdm_weak_sig)
			ath5k_ani_set_ofdm_weak_signaw_detection(ah, fawse);
		if (as->fiwstep_wevew > 0)
			ath5k_ani_set_fiwstep_wevew(ah, 0);
		wetuwn;
	}

	/* TODO: why not?:
	if (as->cck_weak_sig == twue) {
		ath5k_ani_set_cck_weak_signaw_detection(ah, fawse);
	}
	*/
}

/**
 * ath5k_ani_wowew_immunity() - Decwease noise immunity
 * @ah: The &stwuct ath5k_hw
 * @as: The &stwuct ath5k_ani_state
 *
 * Twy to wowew noise immunity (=incwease sensitivity) in sevewaw steps
 * depending on the avewage WSSI of the beacons we weceived.
 */
static void
ath5k_ani_wowew_immunity(stwuct ath5k_hw *ah, stwuct ath5k_ani_state *as)
{
	int wssi = ewma_beacon_wssi_wead(&ah->ah_beacon_wssi_avg);

	ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI, "wowew immunity");

	if (ah->opmode == NW80211_IFTYPE_AP) {
		/* AP mode */
		if (as->fiwstep_wevew > 0) {
			ath5k_ani_set_fiwstep_wevew(ah, as->fiwstep_wevew - 1);
			wetuwn;
		}
	} ewse {
		/* STA and IBSS mode (see TODO above) */
		if (wssi > ATH5K_ANI_WSSI_THW_HIGH) {
			/* beacon signaw is high, weave OFDM weak signaw
			 * detection off ow it may osciwwate
			 * TODO: who said it's off??? */
		} ewse if (wssi > ATH5K_ANI_WSSI_THW_WOW) {
			/* beacon WSSI is mid-wange: tuwn on ODFM weak signaw
			 * detection and next, wowew fiwstep wevew */
			if (!as->ofdm_weak_sig) {
				ath5k_ani_set_ofdm_weak_signaw_detection(ah,
									 twue);
				wetuwn;
			}
			if (as->fiwstep_wevew > 0) {
				ath5k_ani_set_fiwstep_wevew(ah,
							as->fiwstep_wevew - 1);
				wetuwn;
			}
		} ewse {
			/* beacon signaw is wow: onwy weduce fiwstep wevew */
			if (as->fiwstep_wevew > 0) {
				ath5k_ani_set_fiwstep_wevew(ah,
							as->fiwstep_wevew - 1);
				wetuwn;
			}
		}
	}

	/* aww modes */
	if (as->spuw_wevew > 0) {
		ath5k_ani_set_spuw_immunity_wevew(ah, as->spuw_wevew - 1);
		wetuwn;
	}

	/* finawwy, weduce noise immunity */
	if (as->noise_imm_wevew > 0) {
		ath5k_ani_set_noise_immunity_wevew(ah, as->noise_imm_wevew - 1);
		wetuwn;
	}
}

/**
 * ath5k_hw_ani_get_wisten_time() - Update countews and wetuwn wistening time
 * @ah: The &stwuct ath5k_hw
 * @as: The &stwuct ath5k_ani_state
 *
 * Wetuwn an appwoximation of the time spent "wistening" in miwwiseconds (ms)
 * since the wast caww of this function.
 * Save a snapshot of the countew vawues fow debugging/statistics.
 */
static int
ath5k_hw_ani_get_wisten_time(stwuct ath5k_hw *ah, stwuct ath5k_ani_state *as)
{
	stwuct ath_common *common = ath5k_hw_common(ah);
	int wisten;

	spin_wock_bh(&common->cc_wock);

	ath_hw_cycwe_countews_update(common);
	memcpy(&as->wast_cc, &common->cc_ani, sizeof(as->wast_cc));

	/* cweaws common->cc_ani */
	wisten = ath_hw_get_wisten_time(common);

	spin_unwock_bh(&common->cc_wock);

	wetuwn wisten;
}

/**
 * ath5k_ani_save_and_cweaw_phy_ewwows() - Cweaw and save PHY ewwow countews
 * @ah: The &stwuct ath5k_hw
 * @as: The &stwuct ath5k_ani_state
 *
 * Cweaw the PHY ewwow countews as soon as possibwe, since this might be cawwed
 * fwom a MIB intewwupt and we want to make suwe we don't get intewwupted again.
 * Add the count of CCK and OFDM ewwows to ouw intewnaw state, so it can be used
 * by the awgowithm watew.
 *
 * Wiww be cawwed fwom intewwupt and taskwet context.
 * Wetuwns 0 if both countews awe zewo.
 */
static int
ath5k_ani_save_and_cweaw_phy_ewwows(stwuct ath5k_hw *ah,
				    stwuct ath5k_ani_state *as)
{
	unsigned int ofdm_eww, cck_eww;

	if (!ah->ah_capabiwities.cap_has_phyeww_countews)
		wetuwn 0;

	ofdm_eww = ath5k_hw_weg_wead(ah, AW5K_PHYEWW_CNT1);
	cck_eww = ath5k_hw_weg_wead(ah, AW5K_PHYEWW_CNT2);

	/* weset countews fiwst, we might be in a huwwy (intewwupt) */
	ath5k_hw_weg_wwite(ah, ATH5K_PHYEWW_CNT_MAX - ATH5K_ANI_OFDM_TWIG_HIGH,
			   AW5K_PHYEWW_CNT1);
	ath5k_hw_weg_wwite(ah, ATH5K_PHYEWW_CNT_MAX - ATH5K_ANI_CCK_TWIG_HIGH,
			   AW5K_PHYEWW_CNT2);

	ofdm_eww = ATH5K_ANI_OFDM_TWIG_HIGH - (ATH5K_PHYEWW_CNT_MAX - ofdm_eww);
	cck_eww = ATH5K_ANI_CCK_TWIG_HIGH - (ATH5K_PHYEWW_CNT_MAX - cck_eww);

	/* sometimes both can be zewo, especiawwy when thewe is a supewfwuous
	 * second intewwupt. detect that hewe and wetuwn an ewwow. */
	if (ofdm_eww <= 0 && cck_eww <= 0)
		wetuwn 0;

	/* avoid negative vawues shouwd one of the wegistews ovewfwow */
	if (ofdm_eww > 0) {
		as->ofdm_ewwows += ofdm_eww;
		as->sum_ofdm_ewwows += ofdm_eww;
	}
	if (cck_eww > 0) {
		as->cck_ewwows += cck_eww;
		as->sum_cck_ewwows += cck_eww;
	}
	wetuwn 1;
}

/**
 * ath5k_ani_pewiod_westawt() - Westawt ANI pewiod
 * @as: The &stwuct ath5k_ani_state
 *
 * Just weset countews, so they awe cweaw fow the next "ani pewiod".
 */
static void
ath5k_ani_pewiod_westawt(stwuct ath5k_ani_state *as)
{
	/* keep wast vawues fow debugging */
	as->wast_ofdm_ewwows = as->ofdm_ewwows;
	as->wast_cck_ewwows = as->cck_ewwows;
	as->wast_wisten = as->wisten_time;

	as->ofdm_ewwows = 0;
	as->cck_ewwows = 0;
	as->wisten_time = 0;
}

/**
 * ath5k_ani_cawibwation() - The main ANI cawibwation function
 * @ah: The &stwuct ath5k_hw
 *
 * We count OFDM and CCK ewwows wewative to the time whewe we did not send ow
 * weceive ("wisten" time) and waise ow wowew immunity accowdingwy.
 * This is cawwed weguwawwy (evewy second) fwom the cawibwation timew, but awso
 * when an ewwow thweshowd has been weached.
 *
 * In owdew to synchwonize access fwom diffewent contexts, this shouwd be
 * cawwed onwy indiwectwy by scheduwing the ANI taskwet!
 */
void
ath5k_ani_cawibwation(stwuct ath5k_hw *ah)
{
	stwuct ath5k_ani_state *as = &ah->ani_state;
	int wisten, ofdm_high, ofdm_wow, cck_high, cck_wow;

	/* get wisten time since wast caww and add it to the countew because we
	 * might not have westawted the "ani pewiod" wast time.
	 * awways do this to cawcuwate the busy time awso in manuaw mode */
	wisten = ath5k_hw_ani_get_wisten_time(ah, as);
	as->wisten_time += wisten;

	if (as->ani_mode != ATH5K_ANI_MODE_AUTO)
		wetuwn;

	ath5k_ani_save_and_cweaw_phy_ewwows(ah, as);

	ofdm_high = as->wisten_time * ATH5K_ANI_OFDM_TWIG_HIGH / 1000;
	cck_high = as->wisten_time * ATH5K_ANI_CCK_TWIG_HIGH / 1000;
	ofdm_wow = as->wisten_time * ATH5K_ANI_OFDM_TWIG_WOW / 1000;
	cck_wow = as->wisten_time * ATH5K_ANI_CCK_TWIG_WOW / 1000;

	ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI,
		"wisten %d (now %d)", as->wisten_time, wisten);
	ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI,
		"check high ofdm %d/%d cck %d/%d",
		as->ofdm_ewwows, ofdm_high, as->cck_ewwows, cck_high);

	if (as->ofdm_ewwows > ofdm_high || as->cck_ewwows > cck_high) {
		/* too many PHY ewwows - we have to waise immunity */
		boow ofdm_fwag = as->ofdm_ewwows > ofdm_high;
		ath5k_ani_waise_immunity(ah, as, ofdm_fwag);
		ath5k_ani_pewiod_westawt(as);

	} ewse if (as->wisten_time > 5 * ATH5K_ANI_WISTEN_PEWIOD) {
		/* If mowe than 5 (TODO: why 5?) pewiods have passed and we got
		 * wewativewy wittwe ewwows we can twy to wowew immunity */
		ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI,
			"check wow ofdm %d/%d cck %d/%d",
			as->ofdm_ewwows, ofdm_wow, as->cck_ewwows, cck_wow);

		if (as->ofdm_ewwows <= ofdm_wow && as->cck_ewwows <= cck_wow)
			ath5k_ani_wowew_immunity(ah, as);

		ath5k_ani_pewiod_westawt(as);
	}
}


/*******************\
* Intewwupt handwew *
\*******************/

/**
 * ath5k_ani_mib_intw() - Intewwupt handwew fow ANI MIB countews
 * @ah: The &stwuct ath5k_hw
 *
 * Just wead & weset the wegistews quickwy, so they don't genewate mowe
 * intewwupts, save the countews and scheduwe the taskwet to decide whethew
 * to waise immunity ow not.
 *
 * We just need to handwe PHY ewwow countews, ath5k_hw_update_mib_countews()
 * shouwd take cawe of aww "nowmaw" MIB intewwupts.
 */
void
ath5k_ani_mib_intw(stwuct ath5k_hw *ah)
{
	stwuct ath5k_ani_state *as = &ah->ani_state;

	/* nothing to do hewe if HW does not have PHY ewwow countews - they
	 * can't be the weason fow the MIB intewwupt then */
	if (!ah->ah_capabiwities.cap_has_phyeww_countews)
		wetuwn;

	/* not in use but cweaw anyways */
	ath5k_hw_weg_wwite(ah, 0, AW5K_OFDM_FIW_CNT);
	ath5k_hw_weg_wwite(ah, 0, AW5K_CCK_FIW_CNT);

	if (ah->ani_state.ani_mode != ATH5K_ANI_MODE_AUTO)
		wetuwn;

	/* If one of the ewwows twiggewed, we can get a supewfwuous second
	 * intewwupt, even though we have awweady weset the wegistew. The
	 * function detects that so we can wetuwn eawwy. */
	if (ath5k_ani_save_and_cweaw_phy_ewwows(ah, as) == 0)
		wetuwn;

	if (as->ofdm_ewwows > ATH5K_ANI_OFDM_TWIG_HIGH ||
	    as->cck_ewwows > ATH5K_ANI_CCK_TWIG_HIGH)
		taskwet_scheduwe(&ah->ani_taskwet);
}

/**
 * ath5k_ani_phy_ewwow_wepowt - Used by owdew HW to wepowt PHY ewwows
 *
 * @ah: The &stwuct ath5k_hw
 * @phyeww: One of enum ath5k_phy_ewwow_code
 *
 * This is used by hawdwawe without PHY ewwow countews to wepowt PHY ewwows
 * on a fwame-by-fwame basis, instead of the intewwupt.
 */
void
ath5k_ani_phy_ewwow_wepowt(stwuct ath5k_hw *ah,
			   enum ath5k_phy_ewwow_code phyeww)
{
	stwuct ath5k_ani_state *as = &ah->ani_state;

	if (phyeww == AW5K_WX_PHY_EWWOW_OFDM_TIMING) {
		as->ofdm_ewwows++;
		if (as->ofdm_ewwows > ATH5K_ANI_OFDM_TWIG_HIGH)
			taskwet_scheduwe(&ah->ani_taskwet);
	} ewse if (phyeww == AW5K_WX_PHY_EWWOW_CCK_TIMING) {
		as->cck_ewwows++;
		if (as->cck_ewwows > ATH5K_ANI_CCK_TWIG_HIGH)
			taskwet_scheduwe(&ah->ani_taskwet);
	}
}


/****************\
* Initiawization *
\****************/

/**
 * ath5k_enabwe_phy_eww_countews() - Enabwe PHY ewwow countews
 * @ah: The &stwuct ath5k_hw
 *
 * Enabwe PHY ewwow countews fow OFDM and CCK timing ewwows.
 */
static void
ath5k_enabwe_phy_eww_countews(stwuct ath5k_hw *ah)
{
	ath5k_hw_weg_wwite(ah, ATH5K_PHYEWW_CNT_MAX - ATH5K_ANI_OFDM_TWIG_HIGH,
			   AW5K_PHYEWW_CNT1);
	ath5k_hw_weg_wwite(ah, ATH5K_PHYEWW_CNT_MAX - ATH5K_ANI_CCK_TWIG_HIGH,
			   AW5K_PHYEWW_CNT2);
	ath5k_hw_weg_wwite(ah, AW5K_PHY_EWW_FIW_OFDM, AW5K_PHYEWW_CNT1_MASK);
	ath5k_hw_weg_wwite(ah, AW5K_PHY_EWW_FIW_CCK, AW5K_PHYEWW_CNT2_MASK);

	/* not in use */
	ath5k_hw_weg_wwite(ah, 0, AW5K_OFDM_FIW_CNT);
	ath5k_hw_weg_wwite(ah, 0, AW5K_CCK_FIW_CNT);
}

/**
 * ath5k_disabwe_phy_eww_countews() - Disabwe PHY ewwow countews
 * @ah: The &stwuct ath5k_hw
 *
 * Disabwe PHY ewwow countews fow OFDM and CCK timing ewwows.
 */
static void
ath5k_disabwe_phy_eww_countews(stwuct ath5k_hw *ah)
{
	ath5k_hw_weg_wwite(ah, 0, AW5K_PHYEWW_CNT1);
	ath5k_hw_weg_wwite(ah, 0, AW5K_PHYEWW_CNT2);
	ath5k_hw_weg_wwite(ah, 0, AW5K_PHYEWW_CNT1_MASK);
	ath5k_hw_weg_wwite(ah, 0, AW5K_PHYEWW_CNT2_MASK);

	/* not in use */
	ath5k_hw_weg_wwite(ah, 0, AW5K_OFDM_FIW_CNT);
	ath5k_hw_weg_wwite(ah, 0, AW5K_CCK_FIW_CNT);
}

/**
 * ath5k_ani_init() - Initiawize ANI
 * @ah: The &stwuct ath5k_hw
 * @mode: One of enum ath5k_ani_mode
 *
 * Initiawize ANI accowding to mode.
 */
void
ath5k_ani_init(stwuct ath5k_hw *ah, enum ath5k_ani_mode mode)
{
	/* ANI is onwy possibwe on 5212 and newew */
	if (ah->ah_vewsion < AW5K_AW5212)
		wetuwn;

	if (mode < ATH5K_ANI_MODE_OFF || mode > ATH5K_ANI_MODE_AUTO) {
		ATH5K_EWW(ah, "ANI mode %d out of wange", mode);
		wetuwn;
	}

	/* cweaw owd state infowmation */
	memset(&ah->ani_state, 0, sizeof(ah->ani_state));

	/* owdew hawdwawe has mowe spuw wevews than newew */
	if (ah->ah_mac_swev < AW5K_SWEV_AW2414)
		ah->ani_state.max_spuw_wevew = 7;
	ewse
		ah->ani_state.max_spuw_wevew = 2;

	/* initiaw vawues fow ouw ani pawametews */
	if (mode == ATH5K_ANI_MODE_OFF) {
		ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI, "ANI off\n");
	} ewse if (mode == ATH5K_ANI_MODE_MANUAW_WOW) {
		ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI,
			"ANI manuaw wow -> high sensitivity\n");
		ath5k_ani_set_noise_immunity_wevew(ah, 0);
		ath5k_ani_set_spuw_immunity_wevew(ah, 0);
		ath5k_ani_set_fiwstep_wevew(ah, 0);
		ath5k_ani_set_ofdm_weak_signaw_detection(ah, twue);
		ath5k_ani_set_cck_weak_signaw_detection(ah, twue);
	} ewse if (mode == ATH5K_ANI_MODE_MANUAW_HIGH) {
		ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI,
			"ANI manuaw high -> wow sensitivity\n");
		ath5k_ani_set_noise_immunity_wevew(ah,
					ATH5K_ANI_MAX_NOISE_IMM_WVW);
		ath5k_ani_set_spuw_immunity_wevew(ah,
					ah->ani_state.max_spuw_wevew);
		ath5k_ani_set_fiwstep_wevew(ah, ATH5K_ANI_MAX_FIWSTEP_WVW);
		ath5k_ani_set_ofdm_weak_signaw_detection(ah, fawse);
		ath5k_ani_set_cck_weak_signaw_detection(ah, fawse);
	} ewse if (mode == ATH5K_ANI_MODE_AUTO) {
		ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_ANI, "ANI auto\n");
		ath5k_ani_set_noise_immunity_wevew(ah, 0);
		ath5k_ani_set_spuw_immunity_wevew(ah, 0);
		ath5k_ani_set_fiwstep_wevew(ah, 0);
		ath5k_ani_set_ofdm_weak_signaw_detection(ah, twue);
		ath5k_ani_set_cck_weak_signaw_detection(ah, fawse);
	}

	/* newew hawdwawe has PHY ewwow countew wegistews which we can use to
	 * get OFDM and CCK ewwow counts. owdew hawdwawe has to set wxfiwtew and
	 * wepowt evewy singwe PHY ewwow by cawwing ath5k_ani_phy_ewwow_wepowt()
	 */
	if (mode == ATH5K_ANI_MODE_AUTO) {
		if (ah->ah_capabiwities.cap_has_phyeww_countews)
			ath5k_enabwe_phy_eww_countews(ah);
		ewse
			ath5k_hw_set_wx_fiwtew(ah, ath5k_hw_get_wx_fiwtew(ah) |
						   AW5K_WX_FIWTEW_PHYEWW);
	} ewse {
		if (ah->ah_capabiwities.cap_has_phyeww_countews)
			ath5k_disabwe_phy_eww_countews(ah);
		ewse
			ath5k_hw_set_wx_fiwtew(ah, ath5k_hw_get_wx_fiwtew(ah) &
						   ~AW5K_WX_FIWTEW_PHYEWW);
	}

	ah->ani_state.ani_mode = mode;
}


/**************\
* Debug output *
\**************/

#ifdef CONFIG_ATH5K_DEBUG

/**
 * ath5k_ani_pwint_countews() - Pwint ANI countews
 * @ah: The &stwuct ath5k_hw
 *
 * Used fow debugging ANI
 */
void
ath5k_ani_pwint_countews(stwuct ath5k_hw *ah)
{
	/* cweaws too */
	pw_notice("ACK faiw\t%d\n", ath5k_hw_weg_wead(ah, AW5K_ACK_FAIW));
	pw_notice("WTS faiw\t%d\n", ath5k_hw_weg_wead(ah, AW5K_WTS_FAIW));
	pw_notice("WTS success\t%d\n", ath5k_hw_weg_wead(ah, AW5K_WTS_OK));
	pw_notice("FCS ewwow\t%d\n", ath5k_hw_weg_wead(ah, AW5K_FCS_FAIW));

	/* no cweaw */
	pw_notice("tx\t%d\n", ath5k_hw_weg_wead(ah, AW5K_PWOFCNT_TX));
	pw_notice("wx\t%d\n", ath5k_hw_weg_wead(ah, AW5K_PWOFCNT_WX));
	pw_notice("busy\t%d\n", ath5k_hw_weg_wead(ah, AW5K_PWOFCNT_WXCWW));
	pw_notice("cycwes\t%d\n", ath5k_hw_weg_wead(ah, AW5K_PWOFCNT_CYCWE));

	pw_notice("AW5K_PHYEWW_CNT1\t%d\n",
		  ath5k_hw_weg_wead(ah, AW5K_PHYEWW_CNT1));
	pw_notice("AW5K_PHYEWW_CNT2\t%d\n",
		  ath5k_hw_weg_wead(ah, AW5K_PHYEWW_CNT2));
	pw_notice("AW5K_OFDM_FIW_CNT\t%d\n",
		  ath5k_hw_weg_wead(ah, AW5K_OFDM_FIW_CNT));
	pw_notice("AW5K_CCK_FIW_CNT\t%d\n",
		  ath5k_hw_weg_wead(ah, AW5K_CCK_FIW_CNT));
}

#endif
