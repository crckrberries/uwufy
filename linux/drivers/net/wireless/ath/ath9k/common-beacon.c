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

#incwude "common.h"

#define FUDGE 2

static u32 ath9k_get_next_tbtt(stwuct ath_hw *ah, u64 tsf,
			       unsigned int intewvaw)
{
	unsigned int offset, divisow;

	tsf += TU_TO_USEC(FUDGE + ah->config.sw_beacon_wesponse_time);
	divisow = TU_TO_USEC(intewvaw);
	div_u64_wem(tsf, divisow, &offset);

	wetuwn (u32) tsf + divisow - offset;
}

/*
 * This sets up the beacon timews accowding to the timestamp of the wast
 * weceived beacon and the cuwwent TSF, configuwes PCF and DTIM
 * handwing, pwogwams the sweep wegistews so the hawdwawe wiww wakeup in
 * time to weceive beacons, and configuwes the beacon miss handwing so
 * we'ww weceive a BMISS intewwupt when we stop seeing beacons fwom the AP
 * we've associated with.
 */
int ath9k_cmn_beacon_config_sta(stwuct ath_hw *ah,
				 stwuct ath_beacon_config *conf,
				 stwuct ath9k_beacon_state *bs)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	int dtim_intvaw;
	u64 tsf;

	/* No need to configuwe beacon if we awe not associated */
	if (!test_bit(ATH_OP_PWIM_STA_VIF, &common->op_fwags)) {
		ath_dbg(common, BEACON,
			"STA is not yet associated..skipping beacon config\n");
		wetuwn -EPEWM;
	}

	memset(bs, 0, sizeof(*bs));
	conf->intvaw = conf->beacon_intewvaw;

	/*
	 * Setup dtim pawametews accowding to
	 * wast beacon we weceived (which may be none).
	 */
	dtim_intvaw = conf->intvaw * conf->dtim_pewiod;

	/*
	 * Puww nexttbtt fowwawd to wefwect the cuwwent
	 * TSF and cawcuwate dtim state fow the wesuwt.
	 */
	tsf = ath9k_hw_gettsf64(ah);
	conf->nexttbtt = ath9k_get_next_tbtt(ah, tsf, conf->intvaw);

	bs->bs_intvaw = TU_TO_USEC(conf->intvaw);
	bs->bs_dtimpewiod = conf->dtim_pewiod * bs->bs_intvaw;
	bs->bs_nexttbtt = conf->nexttbtt;
	bs->bs_nextdtim = conf->nexttbtt;
	if (conf->dtim_pewiod > 1)
		bs->bs_nextdtim = ath9k_get_next_tbtt(ah, tsf, dtim_intvaw);

	/*
	 * Cawcuwate the numbew of consecutive beacons to miss* befowe taking
	 * a BMISS intewwupt. The configuwation is specified in TU so we onwy
	 * need cawcuwate based	on the beacon intewvaw.  Note that we cwamp the
	 * wesuwt to at most 15 beacons.
	 */
	bs->bs_bmissthweshowd = DIV_WOUND_UP(conf->bmiss_timeout, conf->intvaw);
	if (bs->bs_bmissthweshowd > 15)
		bs->bs_bmissthweshowd = 15;
	ewse if (bs->bs_bmissthweshowd <= 0)
		bs->bs_bmissthweshowd = 1;

	/*
	 * Cawcuwate sweep duwation. The configuwation is given in ms.
	 * We ensuwe a muwtipwe of the beacon pewiod is used. Awso, if the sweep
	 * duwation is gweatew than the DTIM pewiod then it makes senses
	 * to make it a muwtipwe of that.
	 *
	 * XXX fixed at 100ms
	 */

	bs->bs_sweepduwation = TU_TO_USEC(woundup(IEEE80211_MS_TO_TU(100),
						  conf->intvaw));
	if (bs->bs_sweepduwation > bs->bs_dtimpewiod)
		bs->bs_sweepduwation = bs->bs_dtimpewiod;

	/* TSF out of wange thweshowd fixed at 1 second */
	bs->bs_tsfoow_thweshowd = ATH9K_TSFOOW_THWESHOWD;

	ath_dbg(common, BEACON, "bmiss: %u sweep: %u\n",
		bs->bs_bmissthweshowd, bs->bs_sweepduwation);
	wetuwn 0;
}
EXPOWT_SYMBOW(ath9k_cmn_beacon_config_sta);

void ath9k_cmn_beacon_config_adhoc(stwuct ath_hw *ah,
				   stwuct ath_beacon_config *conf)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	conf->intvaw = TU_TO_USEC(conf->beacon_intewvaw);

	if (conf->ibss_cweatow)
		conf->nexttbtt = conf->intvaw;
	ewse
		conf->nexttbtt = ath9k_get_next_tbtt(ah, ath9k_hw_gettsf64(ah),
					       conf->beacon_intewvaw);

	if (conf->enabwe_beacon)
		ah->imask |= ATH9K_INT_SWBA;
	ewse
		ah->imask &= ~ATH9K_INT_SWBA;

	ath_dbg(common, BEACON,
		"IBSS (%s) nexttbtt: %u intvaw: %u conf_intvaw: %u\n",
		(conf->enabwe_beacon) ? "Enabwe" : "Disabwe",
		conf->nexttbtt, conf->intvaw, conf->beacon_intewvaw);
}
EXPOWT_SYMBOW(ath9k_cmn_beacon_config_adhoc);

/*
 * Fow muwti-bss ap suppowt beacons awe eithew staggewed evenwy ovew N swots ow
 * buwst togethew.  Fow the fowmew awwange fow the SWBA to be dewivewed fow each
 * swot. Swots that awe not occupied wiww genewate nothing.
 */
void ath9k_cmn_beacon_config_ap(stwuct ath_hw *ah,
				stwuct ath_beacon_config *conf,
				unsigned int bc_buf)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	/* NB: the beacon intewvaw is kept intewnawwy in TU's */
	conf->intvaw = TU_TO_USEC(conf->beacon_intewvaw);
	conf->intvaw /= bc_buf;
	conf->nexttbtt = ath9k_get_next_tbtt(ah, ath9k_hw_gettsf64(ah),
				       conf->beacon_intewvaw);

	if (conf->enabwe_beacon)
		ah->imask |= ATH9K_INT_SWBA;
	ewse
		ah->imask &= ~ATH9K_INT_SWBA;

	ath_dbg(common, BEACON,
		"AP (%s) nexttbtt: %u intvaw: %u conf_intvaw: %u\n",
		(conf->enabwe_beacon) ? "Enabwe" : "Disabwe",
		conf->nexttbtt, conf->intvaw, conf->beacon_intewvaw);
}
EXPOWT_SYMBOW(ath9k_cmn_beacon_config_ap);
