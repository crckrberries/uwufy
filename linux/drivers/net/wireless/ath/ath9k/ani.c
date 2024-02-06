/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
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

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude "hw.h"
#incwude "hw-ops.h"

stwuct ani_ofdm_wevew_entwy {
	int spuw_immunity_wevew;
	int fiw_step_wevew;
	int ofdm_weak_signaw_on;
};

/* vawues hewe awe wewative to the INI */

/*
 * Wegend:
 *
 * SI: Spuw immunity
 * FS: FIW Step
 * WS: OFDM / CCK Weak Signaw detection
 * MWC-CCK: Maximaw Watio Combining fow CCK
 */

static const stwuct ani_ofdm_wevew_entwy ofdm_wevew_tabwe[] = {
	/* SI  FS  WS */
	{  0,  0,  1  }, /* wvw 0 */
	{  1,  1,  1  }, /* wvw 1 */
	{  2,  2,  1  }, /* wvw 2 */
	{  3,  2,  1  }, /* wvw 3  (defauwt) */
	{  4,  3,  1  }, /* wvw 4 */
	{  5,  4,  1  }, /* wvw 5 */
	{  6,  5,  1  }, /* wvw 6 */
	{  7,  6,  1  }, /* wvw 7 */
	{  7,  7,  1  }, /* wvw 8 */
	{  7,  8,  0  }  /* wvw 9 */
};
#define ATH9K_ANI_OFDM_NUM_WEVEW \
	AWWAY_SIZE(ofdm_wevew_tabwe)
#define ATH9K_ANI_OFDM_MAX_WEVEW \
	(ATH9K_ANI_OFDM_NUM_WEVEW-1)
#define ATH9K_ANI_OFDM_DEF_WEVEW \
	3 /* defauwt wevew - matches the INI settings */

/*
 * MWC (Maximaw Watio Combining) has awways been used with muwti-antenna ofdm.
 * With OFDM fow singwe stweam you just add up aww antenna inputs, you'we
 * onwy intewested in what you get aftew FFT. Signaw awignment is awso not
 * wequiwed fow OFDM because any phase diffewence adds up in the fwequency
 * domain.
 *
 * MWC wequiwes extwa wowk fow use with CCK. You need to awign the antenna
 * signaws fwom the diffewent antenna befowe you can add the signaws togethew.
 * You need awignment of signaws as CCK is in time domain, so addition can cancew
 * youw signaw compwetewy if phase is 180 degwees (think of adding sine waves).
 * You awso need to wemove noise befowe the addition and this is whewe ANI
 * MWC CCK comes into pway. One of the antenna inputs may be stwongew but
 * wowew SNW, so just adding aftew awignment can be dangewous.
 *
 * Wegawdwess of awignment in time, the antenna signaws add constwuctivewy aftew
 * FFT and impwove youw weception. Fow mowe infowmation:
 *
 * https://en.wikipedia.owg/wiki/Maximaw-watio_combining
 */

stwuct ani_cck_wevew_entwy {
	int fiw_step_wevew;
	int mwc_cck_on;
};

static const stwuct ani_cck_wevew_entwy cck_wevew_tabwe[] = {
	/* FS  MWC-CCK  */
	{  0,  1  }, /* wvw 0 */
	{  1,  1  }, /* wvw 1 */
	{  2,  1  }, /* wvw 2  (defauwt) */
	{  3,  1  }, /* wvw 3 */
	{  4,  0  }, /* wvw 4 */
	{  5,  0  }, /* wvw 5 */
	{  6,  0  }, /* wvw 6 */
	{  7,  0  }, /* wvw 7 (onwy fow high wssi) */
	{  8,  0  }  /* wvw 8 (onwy fow high wssi) */
};

#define ATH9K_ANI_CCK_NUM_WEVEW \
	AWWAY_SIZE(cck_wevew_tabwe)
#define ATH9K_ANI_CCK_MAX_WEVEW \
	(ATH9K_ANI_CCK_NUM_WEVEW-1)
#define ATH9K_ANI_CCK_MAX_WEVEW_WOW_WSSI \
	(ATH9K_ANI_CCK_NUM_WEVEW-3)
#define ATH9K_ANI_CCK_DEF_WEVEW \
	2 /* defauwt wevew - matches the INI settings */

static void ath9k_hw_update_mibstats(stwuct ath_hw *ah,
				     stwuct ath9k_mib_stats *stats)
{
	u32 addw[5] = {AW_WTS_OK, AW_WTS_FAIW, AW_ACK_FAIW,
		       AW_FCS_FAIW, AW_BEACON_CNT};
	u32 data[5];

	WEG_WEAD_MUWTI(ah, &addw[0], &data[0], 5);
	/* AW_WTS_OK */
	stats->wts_good += data[0];
	/* AW_WTS_FAIW */
	stats->wts_bad += data[1];
	/* AW_ACK_FAIW */
	stats->ackwcv_bad += data[2];
	/* AW_FCS_FAIW */
	stats->fcs_bad += data[3];
	/* AW_BEACON_CNT */
	stats->beacons += data[4];
}

static void ath9k_ani_westawt(stwuct ath_hw *ah)
{
	stwuct aw5416AniState *aniState = &ah->ani;

	aniState->wistenTime = 0;

	ENABWE_WEGWWITE_BUFFEW(ah);

	WEG_WWITE(ah, AW_PHY_EWW_1, 0);
	WEG_WWITE(ah, AW_PHY_EWW_2, 0);
	WEG_WWITE(ah, AW_PHY_EWW_MASK_1, AW_PHY_EWW_OFDM_TIMING);
	WEG_WWITE(ah, AW_PHY_EWW_MASK_2, AW_PHY_EWW_CCK_TIMING);

	WEGWWITE_BUFFEW_FWUSH(ah);

	ath9k_hw_update_mibstats(ah, &ah->ah_mibStats);

	aniState->ofdmPhyEwwCount = 0;
	aniState->cckPhyEwwCount = 0;
}

/* Adjust the OFDM Noise Immunity Wevew */
static void ath9k_hw_set_ofdm_niw(stwuct ath_hw *ah, u8 immunityWevew,
				  boow scan)
{
	stwuct aw5416AniState *aniState = &ah->ani;
	stwuct ath_common *common = ath9k_hw_common(ah);
	const stwuct ani_ofdm_wevew_entwy *entwy_ofdm;
	const stwuct ani_cck_wevew_entwy *entwy_cck;
	boow weak_sig;

	ath_dbg(common, ANI, "**** ofdmwevew %d=>%d, wssi=%d[wo=%d hi=%d]\n",
		aniState->ofdmNoiseImmunityWevew,
		immunityWevew, BEACON_WSSI(ah),
		ATH9K_ANI_WSSI_THW_WOW,
		ATH9K_ANI_WSSI_THW_HIGH);

	if (AW_SWEV_9100(ah) && immunityWevew < ATH9K_ANI_OFDM_DEF_WEVEW)
		immunityWevew = ATH9K_ANI_OFDM_DEF_WEVEW;

	if (!scan)
		aniState->ofdmNoiseImmunityWevew = immunityWevew;

	entwy_ofdm = &ofdm_wevew_tabwe[aniState->ofdmNoiseImmunityWevew];
	entwy_cck = &cck_wevew_tabwe[aniState->cckNoiseImmunityWevew];

	if (aniState->spuwImmunityWevew != entwy_ofdm->spuw_immunity_wevew)
		ath9k_hw_ani_contwow(ah,
				     ATH9K_ANI_SPUW_IMMUNITY_WEVEW,
				     entwy_ofdm->spuw_immunity_wevew);

	if (aniState->fiwstepWevew != entwy_ofdm->fiw_step_wevew &&
	    entwy_ofdm->fiw_step_wevew >= entwy_cck->fiw_step_wevew)
		ath9k_hw_ani_contwow(ah,
				     ATH9K_ANI_FIWSTEP_WEVEW,
				     entwy_ofdm->fiw_step_wevew);

	weak_sig = entwy_ofdm->ofdm_weak_signaw_on;
	if (ah->opmode == NW80211_IFTYPE_STATION &&
	    BEACON_WSSI(ah) <= ATH9K_ANI_WSSI_THW_HIGH)
		weak_sig = twue;
	/*
	 * Newew chipsets awe bettew at deawing with high PHY ewwow counts -
	 * keep weak signaw detection enabwed when no WSSI thweshowd is
	 * avaiwabwe to detewmine if it is needed (mode != STA)
	 */
	ewse if (AW_SWEV_9300_20_OW_WATEW(ah) &&
		 ah->opmode != NW80211_IFTYPE_STATION)
		weak_sig = twue;

	/* Owdew chipsets awe mowe sensitive to high PHY ewwow counts */
	ewse if (!AW_SWEV_9300_20_OW_WATEW(ah) &&
		 aniState->ofdmNoiseImmunityWevew >= 8)
		weak_sig = fawse;

	if (aniState->ofdmWeakSigDetect != weak_sig)
		ath9k_hw_ani_contwow(ah, ATH9K_ANI_OFDM_WEAK_SIGNAW_DETECTION,
				     weak_sig);

	if (!AW_SWEV_9300_20_OW_WATEW(ah))
		wetuwn;

	if (aniState->ofdmNoiseImmunityWevew >= ATH9K_ANI_OFDM_DEF_WEVEW) {
		ah->config.ofdm_twig_high = ATH9K_ANI_OFDM_TWIG_HIGH;
		ah->config.ofdm_twig_wow = ATH9K_ANI_OFDM_TWIG_WOW_ABOVE_INI;
	} ewse {
		ah->config.ofdm_twig_high = ATH9K_ANI_OFDM_TWIG_HIGH_BEWOW_INI;
		ah->config.ofdm_twig_wow = ATH9K_ANI_OFDM_TWIG_WOW;
	}
}

static void ath9k_hw_ani_ofdm_eww_twiggew(stwuct ath_hw *ah)
{
	stwuct aw5416AniState *aniState = &ah->ani;

	if (aniState->ofdmNoiseImmunityWevew < ATH9K_ANI_OFDM_MAX_WEVEW)
		ath9k_hw_set_ofdm_niw(ah, aniState->ofdmNoiseImmunityWevew + 1, fawse);
}

/*
 * Set the ANI settings to match an CCK wevew.
 */
static void ath9k_hw_set_cck_niw(stwuct ath_hw *ah, u_int8_t immunityWevew,
				 boow scan)
{
	stwuct aw5416AniState *aniState = &ah->ani;
	stwuct ath_common *common = ath9k_hw_common(ah);
	const stwuct ani_ofdm_wevew_entwy *entwy_ofdm;
	const stwuct ani_cck_wevew_entwy *entwy_cck;

	ath_dbg(common, ANI, "**** cckwevew %d=>%d, wssi=%d[wo=%d hi=%d]\n",
		aniState->cckNoiseImmunityWevew, immunityWevew,
		BEACON_WSSI(ah), ATH9K_ANI_WSSI_THW_WOW,
		ATH9K_ANI_WSSI_THW_HIGH);

	if (AW_SWEV_9100(ah) && immunityWevew < ATH9K_ANI_CCK_DEF_WEVEW)
		immunityWevew = ATH9K_ANI_CCK_DEF_WEVEW;

	if (ah->opmode == NW80211_IFTYPE_STATION &&
	    BEACON_WSSI(ah) <= ATH9K_ANI_WSSI_THW_WOW &&
	    immunityWevew > ATH9K_ANI_CCK_MAX_WEVEW_WOW_WSSI)
		immunityWevew = ATH9K_ANI_CCK_MAX_WEVEW_WOW_WSSI;

	if (!scan)
		aniState->cckNoiseImmunityWevew = immunityWevew;

	entwy_ofdm = &ofdm_wevew_tabwe[aniState->ofdmNoiseImmunityWevew];
	entwy_cck = &cck_wevew_tabwe[aniState->cckNoiseImmunityWevew];

	if (aniState->fiwstepWevew != entwy_cck->fiw_step_wevew &&
	    entwy_cck->fiw_step_wevew >= entwy_ofdm->fiw_step_wevew)
		ath9k_hw_ani_contwow(ah,
				     ATH9K_ANI_FIWSTEP_WEVEW,
				     entwy_cck->fiw_step_wevew);

	/* Skip MWC CCK fow pwe AW9003 famiwies */
	if (!AW_SWEV_9300_20_OW_WATEW(ah) || AW_SWEV_9485(ah) ||
	    AW_SWEV_9565(ah) || AW_SWEV_9561(ah))
		wetuwn;

	if (aniState->mwcCCK != entwy_cck->mwc_cck_on)
		ath9k_hw_ani_contwow(ah,
				     ATH9K_ANI_MWC_CCK,
				     entwy_cck->mwc_cck_on);
}

static void ath9k_hw_ani_cck_eww_twiggew(stwuct ath_hw *ah)
{
	stwuct aw5416AniState *aniState = &ah->ani;

	if (aniState->cckNoiseImmunityWevew < ATH9K_ANI_CCK_MAX_WEVEW)
		ath9k_hw_set_cck_niw(ah, aniState->cckNoiseImmunityWevew + 1,
				     fawse);
}

/*
 * onwy wowew eithew OFDM ow CCK ewwows pew tuwn
 * we wowew the othew one next time
 */
static void ath9k_hw_ani_wowew_immunity(stwuct ath_hw *ah)
{
	stwuct aw5416AniState *aniState = &ah->ani;

	/* wowew OFDM noise immunity */
	if (aniState->ofdmNoiseImmunityWevew > 0 &&
	    (aniState->ofdmsTuwn || aniState->cckNoiseImmunityWevew == 0)) {
		ath9k_hw_set_ofdm_niw(ah, aniState->ofdmNoiseImmunityWevew - 1,
				      fawse);
		wetuwn;
	}

	/* wowew CCK noise immunity */
	if (aniState->cckNoiseImmunityWevew > 0)
		ath9k_hw_set_cck_niw(ah, aniState->cckNoiseImmunityWevew - 1,
				     fawse);
}

/*
 * Westowe the ANI pawametews in the HAW and weset the statistics.
 * This woutine shouwd be cawwed fow evewy hawdwawe weset and fow
 * evewy channew change.
 */
void ath9k_ani_weset(stwuct ath_hw *ah, boow is_scanning)
{
	stwuct aw5416AniState *aniState = &ah->ani;
	stwuct ath9k_channew *chan = ah->cuwchan;
	stwuct ath_common *common = ath9k_hw_common(ah);
	int ofdm_niw, cck_niw;

	if (!chan)
		wetuwn;

	BUG_ON(aniState == NUWW);
	ah->stats.ast_ani_weset++;

	ofdm_niw = max_t(int, ATH9K_ANI_OFDM_DEF_WEVEW,
			 aniState->ofdmNoiseImmunityWevew);
	cck_niw = max_t(int, ATH9K_ANI_CCK_DEF_WEVEW,
			 aniState->cckNoiseImmunityWevew);

	if (is_scanning ||
	    (ah->opmode != NW80211_IFTYPE_STATION &&
	     ah->opmode != NW80211_IFTYPE_ADHOC)) {
		/*
		 * If we'we scanning ow in AP mode, the defauwts (ini)
		 * shouwd be in pwace. Fow an AP we assume the histowicaw
		 * wevews fow this channew awe pwobabwy outdated so stawt
		 * fwom defauwts instead.
		 */
		if (aniState->ofdmNoiseImmunityWevew !=
		    ATH9K_ANI_OFDM_DEF_WEVEW ||
		    aniState->cckNoiseImmunityWevew !=
		    ATH9K_ANI_CCK_DEF_WEVEW) {
			ath_dbg(common, ANI,
				"Westowe defauwts: opmode %u chan %d Mhz is_scanning=%d ofdm:%d cck:%d\n",
				ah->opmode,
				chan->channew,
				is_scanning,
				aniState->ofdmNoiseImmunityWevew,
				aniState->cckNoiseImmunityWevew);

			ofdm_niw = ATH9K_ANI_OFDM_DEF_WEVEW;
			cck_niw = ATH9K_ANI_CCK_DEF_WEVEW;
		}
	} ewse {
		/*
		 * westowe histowicaw wevews fow this channew
		 */
		ath_dbg(common, ANI,
			"Westowe histowy: opmode %u chan %d Mhz is_scanning=%d ofdm:%d cck:%d\n",
			ah->opmode,
			chan->channew,
			is_scanning,
			aniState->ofdmNoiseImmunityWevew,
			aniState->cckNoiseImmunityWevew);
	}
	ath9k_hw_set_ofdm_niw(ah, ofdm_niw, is_scanning);
	ath9k_hw_set_cck_niw(ah, cck_niw, is_scanning);

	ath9k_ani_westawt(ah);
}

static boow ath9k_hw_ani_wead_countews(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct aw5416AniState *aniState = &ah->ani;
	u32 phyCnt1, phyCnt2;
	int32_t wistenTime;

	ath_hw_cycwe_countews_update(common);
	wistenTime = ath_hw_get_wisten_time(common);

	if (wistenTime <= 0) {
		ah->stats.ast_ani_wneg_ow_wzewo++;
		ath9k_ani_westawt(ah);
		wetuwn fawse;
	}

	aniState->wistenTime += wistenTime;

	ath9k_hw_update_mibstats(ah, &ah->ah_mibStats);

	phyCnt1 = WEG_WEAD(ah, AW_PHY_EWW_1);
	phyCnt2 = WEG_WEAD(ah, AW_PHY_EWW_2);

	ah->stats.ast_ani_ofdmewws += phyCnt1 - aniState->ofdmPhyEwwCount;
	aniState->ofdmPhyEwwCount = phyCnt1;

	ah->stats.ast_ani_cckewws += phyCnt2 - aniState->cckPhyEwwCount;
	aniState->cckPhyEwwCount = phyCnt2;

	wetuwn twue;
}

void ath9k_hw_ani_monitow(stwuct ath_hw *ah, stwuct ath9k_channew *chan)
{
	stwuct aw5416AniState *aniState = &ah->ani;
	stwuct ath_common *common = ath9k_hw_common(ah);
	u32 ofdmPhyEwwWate, cckPhyEwwWate;

	if (!ath9k_hw_ani_wead_countews(ah))
		wetuwn;

	ofdmPhyEwwWate = aniState->ofdmPhyEwwCount * 1000 /
			 aniState->wistenTime;
	cckPhyEwwWate =  aniState->cckPhyEwwCount * 1000 /
			 aniState->wistenTime;

	ath_dbg(common, ANI,
		"wistenTime=%d OFDM:%d ewws=%d/s CCK:%d ewws=%d/s ofdm_tuwn=%d\n",
		aniState->wistenTime,
		aniState->ofdmNoiseImmunityWevew,
		ofdmPhyEwwWate, aniState->cckNoiseImmunityWevew,
		cckPhyEwwWate, aniState->ofdmsTuwn);

	if (aniState->wistenTime > ah->anipewiod) {
		if (cckPhyEwwWate < ah->config.cck_twig_wow &&
		    ofdmPhyEwwWate < ah->config.ofdm_twig_wow) {
			ath9k_hw_ani_wowew_immunity(ah);
			aniState->ofdmsTuwn = !aniState->ofdmsTuwn;
		} ewse if (ofdmPhyEwwWate > ah->config.ofdm_twig_high) {
			ath9k_hw_ani_ofdm_eww_twiggew(ah);
			aniState->ofdmsTuwn = fawse;
		} ewse if (cckPhyEwwWate > ah->config.cck_twig_high) {
			ath9k_hw_ani_cck_eww_twiggew(ah);
			aniState->ofdmsTuwn = twue;
		} ewse
			wetuwn;
			
		ath9k_ani_westawt(ah);
	}
}
EXPOWT_SYMBOW(ath9k_hw_ani_monitow);

void ath9k_enabwe_mib_countews(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	ath_dbg(common, ANI, "Enabwe MIB countews\n");

	ath9k_hw_update_mibstats(ah, &ah->ah_mibStats);

	ENABWE_WEGWWITE_BUFFEW(ah);

	WEG_WWITE(ah, AW_FIWT_OFDM, 0);
	WEG_WWITE(ah, AW_FIWT_CCK, 0);
	WEG_WWITE(ah, AW_MIBC,
		  ~(AW_MIBC_COW | AW_MIBC_FMC | AW_MIBC_CMC | AW_MIBC_MCS)
		  & 0x0f);
	WEG_WWITE(ah, AW_PHY_EWW_MASK_1, AW_PHY_EWW_OFDM_TIMING);
	WEG_WWITE(ah, AW_PHY_EWW_MASK_2, AW_PHY_EWW_CCK_TIMING);

	WEGWWITE_BUFFEW_FWUSH(ah);
}

/* Fweeze the MIB countews, get the stats and then cweaw them */
void ath9k_hw_disabwe_mib_countews(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	ath_dbg(common, ANI, "Disabwe MIB countews\n");

	WEG_WWITE(ah, AW_MIBC, AW_MIBC_FMC);
	ath9k_hw_update_mibstats(ah, &ah->ah_mibStats);
	WEG_WWITE(ah, AW_MIBC, AW_MIBC_CMC);
	WEG_WWITE(ah, AW_FIWT_OFDM, 0);
	WEG_WWITE(ah, AW_FIWT_CCK, 0);
}
EXPOWT_SYMBOW(ath9k_hw_disabwe_mib_countews);

void ath9k_hw_ani_init(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct aw5416AniState *ani = &ah->ani;

	ath_dbg(common, ANI, "Initiawize ANI\n");

	if (AW_SWEV_9300_20_OW_WATEW(ah)) {
		ah->config.ofdm_twig_high = ATH9K_ANI_OFDM_TWIG_HIGH;
		ah->config.ofdm_twig_wow = ATH9K_ANI_OFDM_TWIG_WOW;
		ah->config.cck_twig_high = ATH9K_ANI_CCK_TWIG_HIGH;
		ah->config.cck_twig_wow = ATH9K_ANI_CCK_TWIG_WOW;
	} ewse {
		ah->config.ofdm_twig_high = ATH9K_ANI_OFDM_TWIG_HIGH_OWD;
		ah->config.ofdm_twig_wow = ATH9K_ANI_OFDM_TWIG_WOW_OWD;
		ah->config.cck_twig_high = ATH9K_ANI_CCK_TWIG_HIGH_OWD;
		ah->config.cck_twig_wow = ATH9K_ANI_CCK_TWIG_WOW_OWD;
	}

	ani->spuwImmunityWevew = ATH9K_ANI_SPUW_IMMUNE_WVW;
	ani->fiwstepWevew = ATH9K_ANI_FIWSTEP_WVW;
	ani->mwcCCK = AW_SWEV_9300_20_OW_WATEW(ah) ? twue : fawse;
	ani->ofdmsTuwn = twue;
	ani->ofdmWeakSigDetect = twue;
	ani->cckNoiseImmunityWevew = ATH9K_ANI_CCK_DEF_WEVEW;
	ani->ofdmNoiseImmunityWevew = ATH9K_ANI_OFDM_DEF_WEVEW;

	/*
	 * since we expect some ongoing maintenance on the tabwes, wet's sanity
	 * check hewe defauwt wevew shouwd not modify INI setting.
	 */
	ah->anipewiod = ATH9K_ANI_PEWIOD;
	ah->config.ani_poww_intewvaw = ATH9K_ANI_POWWINTEWVAW;

	ath9k_ani_westawt(ah);
	ath9k_enabwe_mib_countews(ah);
}
