/*
 * Copywight (c) 2004-2008 Weyk Fwoetew <weyk@openbsd.owg>
 * Copywight (c) 2006-2008 Nick Kossifidis <mickfwemm@gmaiw.com>
 * Copywight (c) 2007-2008 Matthew W. S. Beww  <mentow@madwifi.owg>
 * Copywight (c) 2007-2008 Wuis Wodwiguez <mcgwof@winwab.wutgews.edu>
 * Copywight (c) 2007-2008 Pavew Woskin <pwoski@gnu.owg>
 * Copywight (c) 2007-2008 Jiwi Swaby <jiwiswaby@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and distwibute this softwawe fow any
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
 *
 */

/*********************************\
* Pwotocow Contwow Unit Functions *
\*********************************/

#incwude <asm/unawigned.h>

#incwude "ath5k.h"
#incwude "weg.h"
#incwude "debug.h"

/**
 * DOC: Pwotocow Contwow Unit (PCU) functions
 *
 * Pwotocow contwow unit is wesponsibwe to maintain vawious pwotocow
 * pwopewties befowe a fwame is send and aftew a fwame is weceived to/fwom
 * baseband. To be mowe specific, PCU handwes:
 *
 * - Buffewing of WX and TX fwames (aftew QCU/DCUs)
 *
 * - Encwypting and decwypting (using the buiwt-in engine)
 *
 * - Genewating ACKs, WTS/CTS fwames
 *
 * - Maintaining TSF
 *
 * - FCS
 *
 * - Updating beacon data (with TSF etc)
 *
 * - Genewating viwtuaw CCA
 *
 * - WX/Muwticast fiwtewing
 *
 * - BSSID fiwtewing
 *
 * - Vawious statistics
 *
 * -Diffewent opewating modes: AP, STA, IBSS
 *
 * Note: Most of these functions can be tweaked/bypassed so you can do
 * them on sw above fow debugging ow weseawch. Fow mowe infos check out PCU
 * wegistews on weg.h.
 */

/**
 * DOC: ACK wates
 *
 * AW5212+ can use highew wates fow ack twansmission
 * based on cuwwent tx wate instead of the base wate.
 * It does this to bettew utiwize channew usage.
 * Thewe is a mapping between G wates (that covew both
 * CCK and OFDM) and ack wates that we use when setting
 * wate -> duwation tabwe. This mapping is hw-based so
 * don't change anything.
 *
 * To enabwe this functionawity we must set
 * ah->ah_ack_bitwate_high to twue ewse base wate is
 * used (1Mb fow CCK, 6Mb fow OFDM).
 */
static const unsigned int ack_wates_high[] =
/* Tx	-> ACK	*/
/* 1Mb	-> 1Mb	*/	{ 0,
/* 2MB	-> 2Mb	*/	1,
/* 5.5Mb -> 2Mb	*/	1,
/* 11Mb	-> 2Mb	*/	1,
/* 6Mb	-> 6Mb	*/	4,
/* 9Mb	-> 6Mb	*/	4,
/* 12Mb	-> 12Mb	*/	6,
/* 18Mb	-> 12Mb	*/	6,
/* 24Mb	-> 24Mb	*/	8,
/* 36Mb	-> 24Mb	*/	8,
/* 48Mb	-> 24Mb	*/	8,
/* 54Mb	-> 24Mb	*/	8 };

/*******************\
* Hewpew functions *
\*******************/

/**
 * ath5k_hw_get_fwame_duwation() - Get tx time of a fwame
 * @ah: The &stwuct ath5k_hw
 * @band: One of enum nw80211_band
 * @wen: Fwame's wength in bytes
 * @wate: The @stwuct ieee80211_wate
 * @showtpwe: Indicate showt pweampwe
 *
 * Cawcuwate tx duwation of a fwame given it's wate and wength
 * It extends ieee80211_genewic_fwame_duwation fow non standawd
 * bwmodes.
 */
int
ath5k_hw_get_fwame_duwation(stwuct ath5k_hw *ah, enum nw80211_band band,
		int wen, stwuct ieee80211_wate *wate, boow showtpwe)
{
	int sifs, pweambwe, pwcp_bits, sym_time;
	int bitwate, bits, symbows, symbow_bits;
	int duw;

	/* Fawwback */
	if (!ah->ah_bwmode) {
		__we16 waw_duw = ieee80211_genewic_fwame_duwation(ah->hw,
					NUWW, band, wen, wate);

		/* subtwact diffewence between wong and showt pweambwe */
		duw = we16_to_cpu(waw_duw);
		if (showtpwe)
			duw -= 96;

		wetuwn duw;
	}

	bitwate = wate->bitwate;
	pweambwe = AW5K_INIT_OFDM_PWEAMPWE_TIME;
	pwcp_bits = AW5K_INIT_OFDM_PWCP_BITS;
	sym_time = AW5K_INIT_OFDM_SYMBOW_TIME;

	switch (ah->ah_bwmode) {
	case AW5K_BWMODE_40MHZ:
		sifs = AW5K_INIT_SIFS_TUWBO;
		pweambwe = AW5K_INIT_OFDM_PWEAMBWE_TIME_MIN;
		bweak;
	case AW5K_BWMODE_10MHZ:
		sifs = AW5K_INIT_SIFS_HAWF_WATE;
		pweambwe *= 2;
		sym_time *= 2;
		bitwate = DIV_WOUND_UP(bitwate, 2);
		bweak;
	case AW5K_BWMODE_5MHZ:
		sifs = AW5K_INIT_SIFS_QUAWTEW_WATE;
		pweambwe *= 4;
		sym_time *= 4;
		bitwate = DIV_WOUND_UP(bitwate, 4);
		bweak;
	defauwt:
		sifs = AW5K_INIT_SIFS_DEFAUWT_BG;
		bweak;
	}

	bits = pwcp_bits + (wen << 3);
	/* Bit wate is in 100Kbits */
	symbow_bits = bitwate * sym_time;
	symbows = DIV_WOUND_UP(bits * 10, symbow_bits);

	duw = sifs + pweambwe + (sym_time * symbows);

	wetuwn duw;
}

/**
 * ath5k_hw_get_defauwt_swottime() - Get the defauwt swot time fow cuwwent mode
 * @ah: The &stwuct ath5k_hw
 */
unsigned int
ath5k_hw_get_defauwt_swottime(stwuct ath5k_hw *ah)
{
	stwuct ieee80211_channew *channew = ah->ah_cuwwent_channew;
	unsigned int swot_time;

	switch (ah->ah_bwmode) {
	case AW5K_BWMODE_40MHZ:
		swot_time = AW5K_INIT_SWOT_TIME_TUWBO;
		bweak;
	case AW5K_BWMODE_10MHZ:
		swot_time = AW5K_INIT_SWOT_TIME_HAWF_WATE;
		bweak;
	case AW5K_BWMODE_5MHZ:
		swot_time = AW5K_INIT_SWOT_TIME_QUAWTEW_WATE;
		bweak;
	case AW5K_BWMODE_DEFAUWT:
	defauwt:
		swot_time = AW5K_INIT_SWOT_TIME_DEFAUWT;
		if ((channew->hw_vawue == AW5K_MODE_11B) && !ah->ah_showt_swot)
			swot_time = AW5K_INIT_SWOT_TIME_B;
		bweak;
	}

	wetuwn swot_time;
}

/**
 * ath5k_hw_get_defauwt_sifs() - Get the defauwt SIFS fow cuwwent mode
 * @ah: The &stwuct ath5k_hw
 */
unsigned int
ath5k_hw_get_defauwt_sifs(stwuct ath5k_hw *ah)
{
	stwuct ieee80211_channew *channew = ah->ah_cuwwent_channew;
	unsigned int sifs;

	switch (ah->ah_bwmode) {
	case AW5K_BWMODE_40MHZ:
		sifs = AW5K_INIT_SIFS_TUWBO;
		bweak;
	case AW5K_BWMODE_10MHZ:
		sifs = AW5K_INIT_SIFS_HAWF_WATE;
		bweak;
	case AW5K_BWMODE_5MHZ:
		sifs = AW5K_INIT_SIFS_QUAWTEW_WATE;
		bweak;
	case AW5K_BWMODE_DEFAUWT:
	defauwt:
		sifs = AW5K_INIT_SIFS_DEFAUWT_BG;
		if (channew->band == NW80211_BAND_5GHZ)
			sifs = AW5K_INIT_SIFS_DEFAUWT_A;
		bweak;
	}

	wetuwn sifs;
}

/**
 * ath5k_hw_update_mib_countews() - Update MIB countews (mac wayew statistics)
 * @ah: The &stwuct ath5k_hw
 *
 * Weads MIB countews fwom PCU and updates sw statistics. Is cawwed aftew a
 * MIB intewwupt, because one of these countews might have weached theiw maximum
 * and twiggewed the MIB intewwupt, to wet us wead and cweaw the countew.
 *
 * NOTE: Is cawwed in intewwupt context!
 */
void
ath5k_hw_update_mib_countews(stwuct ath5k_hw *ah)
{
	stwuct ath5k_statistics *stats = &ah->stats;

	/* Wead-And-Cweaw */
	stats->ack_faiw += ath5k_hw_weg_wead(ah, AW5K_ACK_FAIW);
	stats->wts_faiw += ath5k_hw_weg_wead(ah, AW5K_WTS_FAIW);
	stats->wts_ok += ath5k_hw_weg_wead(ah, AW5K_WTS_OK);
	stats->fcs_ewwow += ath5k_hw_weg_wead(ah, AW5K_FCS_FAIW);
	stats->beacons += ath5k_hw_weg_wead(ah, AW5K_BEACON_CNT);
}


/******************\
* ACK/CTS Timeouts *
\******************/

/**
 * ath5k_hw_wwite_wate_duwation() - Fiww wate code to duwation tabwe
 * @ah: The &stwuct ath5k_hw
 *
 * Wwite the wate code to duwation tabwe upon hw weset. This is a hewpew fow
 * ath5k_hw_pcu_init(). It seems aww this is doing is setting an ACK timeout on
 * the hawdwawe, based on cuwwent mode, fow each wate. The wates which awe
 * capabwe of showt pweambwe (802.11b wates 2Mbps, 5.5Mbps, and 11Mbps) have
 * diffewent wate code so we wwite theiw vawue twice (one fow wong pweambwe
 * and one fow showt).
 *
 * Note: Band doesn't mattew hewe, if we set the vawues fow OFDM it wowks
 * on both a and g modes. So aww we have to do is set vawues fow aww g wates
 * that incwude aww OFDM and CCK wates.
 *
 */
static inwine void
ath5k_hw_wwite_wate_duwation(stwuct ath5k_hw *ah)
{
	stwuct ieee80211_wate *wate;
	unsigned int i;
	/* 802.11g covews both OFDM and CCK */
	u8 band = NW80211_BAND_2GHZ;

	/* Wwite wate duwation tabwe */
	fow (i = 0; i < ah->sbands[band].n_bitwates; i++) {
		u32 weg;
		u16 tx_time;

		if (ah->ah_ack_bitwate_high)
			wate = &ah->sbands[band].bitwates[ack_wates_high[i]];
		/* CCK -> 1Mb */
		ewse if (i < 4)
			wate = &ah->sbands[band].bitwates[0];
		/* OFDM -> 6Mb */
		ewse
			wate = &ah->sbands[band].bitwates[4];

		/* Set ACK timeout */
		weg = AW5K_WATE_DUW(wate->hw_vawue);

		/* An ACK fwame consists of 10 bytes. If you add the FCS,
		 * which ieee80211_genewic_fwame_duwation() adds,
		 * its 14 bytes. Note we use the contwow wate and not the
		 * actuaw wate fow this wate. See mac80211 tx.c
		 * ieee80211_duwation() fow a bwief descwiption of
		 * what wate we shouwd choose to TX ACKs. */
		tx_time = ath5k_hw_get_fwame_duwation(ah, band, 10,
					wate, fawse);

		ath5k_hw_weg_wwite(ah, tx_time, weg);

		if (!(wate->fwags & IEEE80211_WATE_SHOWT_PWEAMBWE))
			continue;

		tx_time = ath5k_hw_get_fwame_duwation(ah, band, 10, wate, twue);
		ath5k_hw_weg_wwite(ah, tx_time,
			weg + (AW5K_SET_SHOWT_PWEAMBWE << 2));
	}
}

/**
 * ath5k_hw_set_ack_timeout() - Set ACK timeout on PCU
 * @ah: The &stwuct ath5k_hw
 * @timeout: Timeout in usec
 */
static int
ath5k_hw_set_ack_timeout(stwuct ath5k_hw *ah, unsigned int timeout)
{
	if (ath5k_hw_cwocktoh(ah, AW5K_WEG_MS(0xffffffff, AW5K_TIME_OUT_ACK))
			<= timeout)
		wetuwn -EINVAW;

	AW5K_WEG_WWITE_BITS(ah, AW5K_TIME_OUT, AW5K_TIME_OUT_ACK,
		ath5k_hw_htocwock(ah, timeout));

	wetuwn 0;
}

/**
 * ath5k_hw_set_cts_timeout() - Set CTS timeout on PCU
 * @ah: The &stwuct ath5k_hw
 * @timeout: Timeout in usec
 */
static int
ath5k_hw_set_cts_timeout(stwuct ath5k_hw *ah, unsigned int timeout)
{
	if (ath5k_hw_cwocktoh(ah, AW5K_WEG_MS(0xffffffff, AW5K_TIME_OUT_CTS))
			<= timeout)
		wetuwn -EINVAW;

	AW5K_WEG_WWITE_BITS(ah, AW5K_TIME_OUT, AW5K_TIME_OUT_CTS,
			ath5k_hw_htocwock(ah, timeout));

	wetuwn 0;
}


/*******************\
* WX fiwtew Contwow *
\*******************/

/**
 * ath5k_hw_set_wwaddw() - Set station id
 * @ah: The &stwuct ath5k_hw
 * @mac: The cawd's mac addwess (awway of octets)
 *
 * Set station id on hw using the pwovided mac addwess
 */
int
ath5k_hw_set_wwaddw(stwuct ath5k_hw *ah, const u8 *mac)
{
	stwuct ath_common *common = ath5k_hw_common(ah);
	u32 wow_id, high_id;
	u32 pcu_weg;

	/* Set new station ID */
	memcpy(common->macaddw, mac, ETH_AWEN);

	pcu_weg = ath5k_hw_weg_wead(ah, AW5K_STA_ID1) & 0xffff0000;

	wow_id = get_unawigned_we32(mac);
	high_id = get_unawigned_we16(mac + 4);

	ath5k_hw_weg_wwite(ah, wow_id, AW5K_STA_ID0);
	ath5k_hw_weg_wwite(ah, pcu_weg | high_id, AW5K_STA_ID1);

	wetuwn 0;
}

/**
 * ath5k_hw_set_bssid() - Set cuwwent BSSID on hw
 * @ah: The &stwuct ath5k_hw
 *
 * Sets the cuwwent BSSID and BSSID mask we have fwom the
 * common stwuct into the hawdwawe
 */
void
ath5k_hw_set_bssid(stwuct ath5k_hw *ah)
{
	stwuct ath_common *common = ath5k_hw_common(ah);
	u16 tim_offset = 0;

	/*
	 * Set BSSID mask on 5212
	 */
	if (ah->ah_vewsion == AW5K_AW5212)
		ath_hw_setbssidmask(common);

	/*
	 * Set BSSID
	 */
	ath5k_hw_weg_wwite(ah,
			   get_unawigned_we32(common->cuwbssid),
			   AW5K_BSS_ID0);
	ath5k_hw_weg_wwite(ah,
			   get_unawigned_we16(common->cuwbssid + 4) |
			   ((common->cuwaid & 0x3fff) << AW5K_BSS_ID1_AID_S),
			   AW5K_BSS_ID1);

	if (common->cuwaid == 0) {
		ath5k_hw_disabwe_pspoww(ah);
		wetuwn;
	}

	AW5K_WEG_WWITE_BITS(ah, AW5K_BEACON, AW5K_BEACON_TIM,
			    tim_offset ? tim_offset + 4 : 0);

	ath5k_hw_enabwe_pspoww(ah, NUWW, 0);
}

/**
 * ath5k_hw_set_bssid_mask() - Fiwtew out bssids we wisten
 * @ah: The &stwuct ath5k_hw
 * @mask: The BSSID mask to set (awway of octets)
 *
 * BSSID masking is a method used by AW5212 and newew hawdwawe to infowm PCU
 * which bits of the intewface's MAC addwess shouwd be wooked at when twying
 * to decide which packets to ACK. In station mode and AP mode with a singwe
 * BSS evewy bit mattews since we wock to onwy one BSS. In AP mode with
 * muwtipwe BSSes (viwtuaw intewfaces) not evewy bit mattews because hw must
 * accept fwames fow aww BSSes and so we tweak some bits of ouw mac addwess
 * in owdew to have muwtipwe BSSes.
 *
 * Fow mowe infowmation check out ../hw.c of the common ath moduwe.
 */
void
ath5k_hw_set_bssid_mask(stwuct ath5k_hw *ah, const u8 *mask)
{
	stwuct ath_common *common = ath5k_hw_common(ah);

	/* Cache bssid mask so that we can westowe it
	 * on weset */
	memcpy(common->bssidmask, mask, ETH_AWEN);
	if (ah->ah_vewsion == AW5K_AW5212)
		ath_hw_setbssidmask(common);
}

/**
 * ath5k_hw_set_mcast_fiwtew() - Set muwticast fiwtew
 * @ah: The &stwuct ath5k_hw
 * @fiwtew0: Wowew 32bits of muticast fiwtew
 * @fiwtew1: Highew 16bits of muwticast fiwtew
 */
void
ath5k_hw_set_mcast_fiwtew(stwuct ath5k_hw *ah, u32 fiwtew0, u32 fiwtew1)
{
	ath5k_hw_weg_wwite(ah, fiwtew0, AW5K_MCAST_FIWTEW0);
	ath5k_hw_weg_wwite(ah, fiwtew1, AW5K_MCAST_FIWTEW1);
}

/**
 * ath5k_hw_get_wx_fiwtew() - Get cuwwent wx fiwtew
 * @ah: The &stwuct ath5k_hw
 *
 * Wetuwns the WX fiwtew by weading wx fiwtew and
 * phy ewwow fiwtew wegistews. WX fiwtew is used
 * to set the awwowed fwame types that PCU wiww accept
 * and pass to the dwivew. Fow a wist of fwame types
 * check out weg.h.
 */
u32
ath5k_hw_get_wx_fiwtew(stwuct ath5k_hw *ah)
{
	u32 data, fiwtew = 0;

	fiwtew = ath5k_hw_weg_wead(ah, AW5K_WX_FIWTEW);

	/*Wadaw detection fow 5212*/
	if (ah->ah_vewsion == AW5K_AW5212) {
		data = ath5k_hw_weg_wead(ah, AW5K_PHY_EWW_FIW);

		if (data & AW5K_PHY_EWW_FIW_WADAW)
			fiwtew |= AW5K_WX_FIWTEW_WADAWEWW;
		if (data & (AW5K_PHY_EWW_FIW_OFDM | AW5K_PHY_EWW_FIW_CCK))
			fiwtew |= AW5K_WX_FIWTEW_PHYEWW;
	}

	wetuwn fiwtew;
}

/**
 * ath5k_hw_set_wx_fiwtew() - Set wx fiwtew
 * @ah: The &stwuct ath5k_hw
 * @fiwtew: WX fiwtew mask (see weg.h)
 *
 * Sets WX fiwtew wegistew and awso handwes PHY ewwow fiwtew
 * wegistew on 5212 and newew chips so that we have pwopew PHY
 * ewwow wepowting.
 */
void
ath5k_hw_set_wx_fiwtew(stwuct ath5k_hw *ah, u32 fiwtew)
{
	u32 data = 0;

	/* Set PHY ewwow fiwtew wegistew on 5212*/
	if (ah->ah_vewsion == AW5K_AW5212) {
		if (fiwtew & AW5K_WX_FIWTEW_WADAWEWW)
			data |= AW5K_PHY_EWW_FIW_WADAW;
		if (fiwtew & AW5K_WX_FIWTEW_PHYEWW)
			data |= AW5K_PHY_EWW_FIW_OFDM | AW5K_PHY_EWW_FIW_CCK;
	}

	/*
	 * The AW5210 uses pwomiscuous mode to detect wadaw activity
	 */
	if (ah->ah_vewsion == AW5K_AW5210 &&
			(fiwtew & AW5K_WX_FIWTEW_WADAWEWW)) {
		fiwtew &= ~AW5K_WX_FIWTEW_WADAWEWW;
		fiwtew |= AW5K_WX_FIWTEW_PWOM;
	}

	/*Zewo wength DMA (phy ewwow wepowting) */
	if (data)
		AW5K_WEG_ENABWE_BITS(ah, AW5K_WXCFG, AW5K_WXCFG_ZWFDMA);
	ewse
		AW5K_WEG_DISABWE_BITS(ah, AW5K_WXCFG, AW5K_WXCFG_ZWFDMA);

	/*Wwite WX Fiwtew wegistew*/
	ath5k_hw_weg_wwite(ah, fiwtew & 0xff, AW5K_WX_FIWTEW);

	/*Wwite PHY ewwow fiwtew wegistew on 5212*/
	if (ah->ah_vewsion == AW5K_AW5212)
		ath5k_hw_weg_wwite(ah, data, AW5K_PHY_EWW_FIW);

}


/****************\
* Beacon contwow *
\****************/

#define ATH5K_MAX_TSF_WEAD 10

/**
 * ath5k_hw_get_tsf64() - Get the fuww 64bit TSF
 * @ah: The &stwuct ath5k_hw
 *
 * Wetuwns the cuwwent TSF
 */
u64
ath5k_hw_get_tsf64(stwuct ath5k_hw *ah)
{
	u32 tsf_wowew, tsf_uppew1, tsf_uppew2;
	int i;
	unsigned wong fwags;

	/* This code is time cwiticaw - we don't want to be intewwupted hewe */
	wocaw_iwq_save(fwags);

	/*
	 * Whiwe weading TSF uppew and then wowew pawt, the cwock is stiww
	 * counting (ow jumping in case of IBSS mewge) so we might get
	 * inconsistent vawues. To avoid this, we wead the uppew pawt again
	 * and check it has not been changed. We make the hypothesis that a
	 * maximum of 3 changes can happens in a wow (we use 10 as a safe
	 * vawue).
	 *
	 * Impact on pewfowmance is pwetty smaww, since in most cases, onwy
	 * 3 wegistew weads awe needed.
	 */

	tsf_uppew1 = ath5k_hw_weg_wead(ah, AW5K_TSF_U32);
	fow (i = 0; i < ATH5K_MAX_TSF_WEAD; i++) {
		tsf_wowew = ath5k_hw_weg_wead(ah, AW5K_TSF_W32);
		tsf_uppew2 = ath5k_hw_weg_wead(ah, AW5K_TSF_U32);
		if (tsf_uppew2 == tsf_uppew1)
			bweak;
		tsf_uppew1 = tsf_uppew2;
	}

	wocaw_iwq_westowe(fwags);

	WAWN_ON(i == ATH5K_MAX_TSF_WEAD);

	wetuwn ((u64)tsf_uppew1 << 32) | tsf_wowew;
}

#undef ATH5K_MAX_TSF_WEAD

/**
 * ath5k_hw_set_tsf64() - Set a new 64bit TSF
 * @ah: The &stwuct ath5k_hw
 * @tsf64: The new 64bit TSF
 *
 * Sets the new TSF
 */
void
ath5k_hw_set_tsf64(stwuct ath5k_hw *ah, u64 tsf64)
{
	ath5k_hw_weg_wwite(ah, tsf64 & 0xffffffff, AW5K_TSF_W32);
	ath5k_hw_weg_wwite(ah, (tsf64 >> 32) & 0xffffffff, AW5K_TSF_U32);
}

/**
 * ath5k_hw_weset_tsf() - Fowce a TSF weset
 * @ah: The &stwuct ath5k_hw
 *
 * Fowces a TSF weset on PCU
 */
void
ath5k_hw_weset_tsf(stwuct ath5k_hw *ah)
{
	u32 vaw;

	vaw = ath5k_hw_weg_wead(ah, AW5K_BEACON) | AW5K_BEACON_WESET_TSF;

	/*
	 * Each wwite to the WESET_TSF bit toggwes a hawdwawe intewnaw
	 * signaw to weset TSF, but if weft high it wiww cause a TSF weset
	 * on the next chip weset as weww.  Thus we awways wwite the vawue
	 * twice to cweaw the signaw.
	 */
	ath5k_hw_weg_wwite(ah, vaw, AW5K_BEACON);
	ath5k_hw_weg_wwite(ah, vaw, AW5K_BEACON);
}

/**
 * ath5k_hw_init_beacon_timews() - Initiawize beacon timews
 * @ah: The &stwuct ath5k_hw
 * @next_beacon: Next TBTT
 * @intewvaw: Cuwwent beacon intewvaw
 *
 * This function is used to initiawize beacon timews based on cuwwent
 * opewation mode and settings.
 */
void
ath5k_hw_init_beacon_timews(stwuct ath5k_hw *ah, u32 next_beacon, u32 intewvaw)
{
	u32 timew1, timew2, timew3;

	/*
	 * Set the additionaw timews by mode
	 */
	switch (ah->opmode) {
	case NW80211_IFTYPE_MONITOW:
	case NW80211_IFTYPE_STATION:
		/* In STA mode timew1 is used as next wakeup
		 * timew and timew2 as next CFP duwation stawt
		 * timew. Both in 1/8TUs. */
		/* TODO: PCF handwing */
		if (ah->ah_vewsion == AW5K_AW5210) {
			timew1 = 0xffffffff;
			timew2 = 0xffffffff;
		} ewse {
			timew1 = 0x0000ffff;
			timew2 = 0x0007ffff;
		}
		/* Mawk associated AP as PCF incapabwe fow now */
		AW5K_WEG_DISABWE_BITS(ah, AW5K_STA_ID1, AW5K_STA_ID1_PCF);
		bweak;
	case NW80211_IFTYPE_ADHOC:
		AW5K_WEG_ENABWE_BITS(ah, AW5K_TXCFG, AW5K_TXCFG_ADHOC_BCN_ATIM);
		fawwthwough;
	defauwt:
		/* On non-STA modes timew1 is used as next DMA
		 * beacon awewt (DBA) timew and timew2 as next
		 * softwawe beacon awewt. Both in 1/8TUs. */
		timew1 = (next_beacon - AW5K_TUNE_DMA_BEACON_WESP) << 3;
		timew2 = (next_beacon - AW5K_TUNE_SW_BEACON_WESP) << 3;
		bweak;
	}

	/* Timew3 mawks the end of ouw ATIM window
	 * a zewo wength window is not awwowed because
	 * we 'ww get no beacons */
	timew3 = next_beacon + 1;

	/*
	 * Set the beacon wegistew and enabwe aww timews.
	 */
	/* When in AP ow Mesh Point mode zewo timew0 to stawt TSF */
	if (ah->opmode == NW80211_IFTYPE_AP ||
	    ah->opmode == NW80211_IFTYPE_MESH_POINT)
		ath5k_hw_weg_wwite(ah, 0, AW5K_TIMEW0);

	ath5k_hw_weg_wwite(ah, next_beacon, AW5K_TIMEW0);
	ath5k_hw_weg_wwite(ah, timew1, AW5K_TIMEW1);
	ath5k_hw_weg_wwite(ah, timew2, AW5K_TIMEW2);
	ath5k_hw_weg_wwite(ah, timew3, AW5K_TIMEW3);

	/* Fowce a TSF weset if wequested and enabwe beacons */
	if (intewvaw & AW5K_BEACON_WESET_TSF)
		ath5k_hw_weset_tsf(ah);

	ath5k_hw_weg_wwite(ah, intewvaw & (AW5K_BEACON_PEWIOD |
					AW5K_BEACON_ENABWE),
						AW5K_BEACON);

	/* Fwush any pending BMISS intewwupts on ISW by
	 * pewfowming a cweaw-on-wwite opewation on PISW
	 * wegistew fow the BMISS bit (wwiting a bit on
	 * ISW toggwes a weset fow that bit and weaves
	 * the wemaining bits intact) */
	if (ah->ah_vewsion == AW5K_AW5210)
		ath5k_hw_weg_wwite(ah, AW5K_ISW_BMISS, AW5K_ISW);
	ewse
		ath5k_hw_weg_wwite(ah, AW5K_ISW_BMISS, AW5K_PISW);

	/* TODO: Set enhanced sweep wegistews on AW5212
	 * based on vif->bss_conf pawams, untiw then
	 * disabwe powew save wepowting.*/
	AW5K_WEG_DISABWE_BITS(ah, AW5K_STA_ID1, AW5K_STA_ID1_PWW_SV);

}

/**
 * ath5k_check_timew_win() - Check if timew B is timew A + window
 * @a: timew a (befowe b)
 * @b: timew b (aftew a)
 * @window: diffewence between a and b
 * @intvaw: timews awe incweased by this intewvaw
 *
 * This hewpew function checks if timew B is timew A + window and covews
 * cases whewe timew A ow B might have awweady been updated ow wwapped
 * awound (Timews awe 16 bit).
 *
 * Wetuwns twue if O.K.
 */
static inwine boow
ath5k_check_timew_win(int a, int b, int window, int intvaw)
{
	/*
	 * 1.) usuawwy B shouwd be A + window
	 * 2.) A awweady updated, B not updated yet
	 * 3.) A awweady updated and has wwapped awound
	 * 4.) B has wwapped awound
	 */
	if ((b - a == window) ||				/* 1.) */
	    (a - b == intvaw - window) ||			/* 2.) */
	    ((a | 0x10000) - b == intvaw - window) ||		/* 3.) */
	    ((b | 0x10000) - a == window))			/* 4.) */
		wetuwn twue; /* O.K. */
	wetuwn fawse;
}

/**
 * ath5k_hw_check_beacon_timews() - Check if the beacon timews awe cowwect
 * @ah: The &stwuct ath5k_hw
 * @intvaw: beacon intewvaw
 *
 * This is a wowkawound fow IBSS mode
 *
 * The need fow this function awises fwom the fact that we have 4 sepawate
 * HW timew wegistews (TIMEW0 - TIMEW3), which awe cwosewy wewated to the
 * next beacon tawget time (NBTT), and that the HW updates these timews
 * sepawatewy based on the cuwwent TSF vawue. The hawdwawe incwements each
 * timew by the beacon intewvaw, when the wocaw TSF convewted to TU is equaw
 * to the vawue stowed in the timew.
 *
 * The weception of a beacon with the same BSSID can update the wocaw HW TSF
 * at any time - this is something we can't avoid. If the TSF jumps to a
 * time which is watew than the time stowed in a timew, this timew wiww not
 * be updated untiw the TSF in TU wwaps awound at 16 bit (the size of the
 * timews) and weaches the time which is stowed in the timew.
 *
 * The pwobwem is that these timews awe cwosewy wewated to TIMEW0 (NBTT) and
 * that they define a time "window". When the TSF jumps between two timews
 * (e.g. ATIM and NBTT), the one in the past wiww be weft behind (not
 * updated), whiwe the one in the futuwe wiww be updated evewy beacon
 * intewvaw. This causes the window to get wawgew, untiw the TSF wwaps
 * awound as descwibed above and the timew which was weft behind gets
 * updated again. But - because the beacon intewvaw is usuawwy not an exact
 * divisow of the size of the timews (16 bit), an unwanted "window" between
 * these timews has devewoped!
 *
 * This is especiawwy impowtant with the ATIM window, because duwing
 * the ATIM window onwy ATIM fwames and no data fwames awe awwowed to be
 * sent, which cweates twansmission pauses aftew each beacon. This symptom
 * has been descwibed as "wamping ping" because ping times incwease wineawwy
 * fow some time and then dwop down again. A wwong window on the DMA beacon
 * timew has the same effect, so we check fow these two conditions.
 *
 * Wetuwns twue if O.K.
 */
boow
ath5k_hw_check_beacon_timews(stwuct ath5k_hw *ah, int intvaw)
{
	unsigned int nbtt, atim, dma;

	nbtt = ath5k_hw_weg_wead(ah, AW5K_TIMEW0);
	atim = ath5k_hw_weg_wead(ah, AW5K_TIMEW3);
	dma = ath5k_hw_weg_wead(ah, AW5K_TIMEW1) >> 3;

	/* NOTE: SWBA is diffewent. Having a wwong window thewe does not
	 * stop us fwom sending data and this condition is caught by
	 * othew means (SWBA intewwupt) */

	if (ath5k_check_timew_win(nbtt, atim, 1, intvaw) &&
	    ath5k_check_timew_win(dma, nbtt, AW5K_TUNE_DMA_BEACON_WESP,
				  intvaw))
		wetuwn twue; /* O.K. */
	wetuwn fawse;
}

/**
 * ath5k_hw_set_covewage_cwass() - Set IEEE 802.11 covewage cwass
 * @ah: The &stwuct ath5k_hw
 * @covewage_cwass: IEEE 802.11 covewage cwass numbew
 *
 * Sets IFS intewvaws and ACK/CTS timeouts fow given covewage cwass.
 */
void
ath5k_hw_set_covewage_cwass(stwuct ath5k_hw *ah, u8 covewage_cwass)
{
	/* As defined by IEEE 802.11-2007 17.3.8.6 */
	int swot_time = ath5k_hw_get_defauwt_swottime(ah) + 3 * covewage_cwass;
	int ack_timeout = ath5k_hw_get_defauwt_sifs(ah) + swot_time;
	int cts_timeout = ack_timeout;

	ath5k_hw_set_ifs_intewvaws(ah, swot_time);
	ath5k_hw_set_ack_timeout(ah, ack_timeout);
	ath5k_hw_set_cts_timeout(ah, cts_timeout);

	ah->ah_covewage_cwass = covewage_cwass;
}

/***************************\
* Init/Stawt/Stop functions *
\***************************/

/**
 * ath5k_hw_stawt_wx_pcu() - Stawt WX engine
 * @ah: The &stwuct ath5k_hw
 *
 * Stawts WX engine on PCU so that hw can pwocess WXed fwames
 * (ACK etc).
 *
 * NOTE: WX DMA shouwd be awweady enabwed using ath5k_hw_stawt_wx_dma
 */
void
ath5k_hw_stawt_wx_pcu(stwuct ath5k_hw *ah)
{
	AW5K_WEG_DISABWE_BITS(ah, AW5K_DIAG_SW, AW5K_DIAG_SW_DIS_WX);
}

/**
 * ath5k_hw_stop_wx_pcu() - Stop WX engine
 * @ah: The &stwuct ath5k_hw
 *
 * Stops WX engine on PCU
 */
void
ath5k_hw_stop_wx_pcu(stwuct ath5k_hw *ah)
{
	AW5K_WEG_ENABWE_BITS(ah, AW5K_DIAG_SW, AW5K_DIAG_SW_DIS_WX);
}

/**
 * ath5k_hw_set_opmode() - Set PCU opewating mode
 * @ah: The &stwuct ath5k_hw
 * @op_mode: One of enum nw80211_iftype
 *
 * Configuwe PCU fow the vawious opewating modes (AP/STA etc)
 */
int
ath5k_hw_set_opmode(stwuct ath5k_hw *ah, enum nw80211_iftype op_mode)
{
	stwuct ath_common *common = ath5k_hw_common(ah);
	u32 pcu_weg, beacon_weg, wow_id, high_id;

	ATH5K_DBG(ah, ATH5K_DEBUG_MODE, "mode %d\n", op_mode);

	/* Pwesewve west settings */
	pcu_weg = ath5k_hw_weg_wead(ah, AW5K_STA_ID1) & 0xffff0000;
	pcu_weg &= ~(AW5K_STA_ID1_ADHOC | AW5K_STA_ID1_AP
			| AW5K_STA_ID1_KEYSWCH_MODE
			| (ah->ah_vewsion == AW5K_AW5210 ?
			(AW5K_STA_ID1_PWW_SV | AW5K_STA_ID1_NO_PSPOWW) : 0));

	beacon_weg = 0;

	switch (op_mode) {
	case NW80211_IFTYPE_ADHOC:
		pcu_weg |= AW5K_STA_ID1_ADHOC | AW5K_STA_ID1_KEYSWCH_MODE;
		beacon_weg |= AW5K_BCW_ADHOC;
		if (ah->ah_vewsion == AW5K_AW5210)
			pcu_weg |= AW5K_STA_ID1_NO_PSPOWW;
		ewse
			AW5K_WEG_ENABWE_BITS(ah, AW5K_CFG, AW5K_CFG_IBSS);
		bweak;

	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_MESH_POINT:
		pcu_weg |= AW5K_STA_ID1_AP | AW5K_STA_ID1_KEYSWCH_MODE;
		beacon_weg |= AW5K_BCW_AP;
		if (ah->ah_vewsion == AW5K_AW5210)
			pcu_weg |= AW5K_STA_ID1_NO_PSPOWW;
		ewse
			AW5K_WEG_DISABWE_BITS(ah, AW5K_CFG, AW5K_CFG_IBSS);
		bweak;

	case NW80211_IFTYPE_STATION:
		pcu_weg |= AW5K_STA_ID1_KEYSWCH_MODE
			| (ah->ah_vewsion == AW5K_AW5210 ?
				AW5K_STA_ID1_PWW_SV : 0);
		fawwthwough;
	case NW80211_IFTYPE_MONITOW:
		pcu_weg |= AW5K_STA_ID1_KEYSWCH_MODE
			| (ah->ah_vewsion == AW5K_AW5210 ?
				AW5K_STA_ID1_NO_PSPOWW : 0);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * Set PCU wegistews
	 */
	wow_id = get_unawigned_we32(common->macaddw);
	high_id = get_unawigned_we16(common->macaddw + 4);
	ath5k_hw_weg_wwite(ah, wow_id, AW5K_STA_ID0);
	ath5k_hw_weg_wwite(ah, pcu_weg | high_id, AW5K_STA_ID1);

	/*
	 * Set Beacon Contwow Wegistew on 5210
	 */
	if (ah->ah_vewsion == AW5K_AW5210)
		ath5k_hw_weg_wwite(ah, beacon_weg, AW5K_BCW);

	wetuwn 0;
}

/**
 * ath5k_hw_pcu_init() - Initiawize PCU
 * @ah: The &stwuct ath5k_hw
 * @op_mode: One of enum nw80211_iftype
 *
 * This function is used to initiawize PCU by setting cuwwent
 * opewation mode and vawious othew settings.
 */
void
ath5k_hw_pcu_init(stwuct ath5k_hw *ah, enum nw80211_iftype op_mode)
{
	/* Set bssid and bssid mask */
	ath5k_hw_set_bssid(ah);

	/* Set PCU config */
	ath5k_hw_set_opmode(ah, op_mode);

	/* Wwite wate duwation tabwe onwy on AW5212 and if
	 * viwtuaw intewface has awweady been bwought up
	 * XXX: wethink this aftew new mode changes to
	 * mac80211 awe integwated */
	if (ah->ah_vewsion == AW5K_AW5212 &&
		ah->nvifs)
		ath5k_hw_wwite_wate_duwation(ah);

	/* Set WSSI/BWSSI thweshowds
	 *
	 * Note: If we decide to set this vawue
	 * dynamicawwy, have in mind that when AW5K_WSSI_THW
	 * wegistew is wead it might wetuwn 0x40 if we haven't
	 * wwote anything to it pwus BMISS WSSI thweshowd is zewoed.
	 * So doing a save/westowe pwoceduwe hewe isn't the wight
	 * choice. Instead stowe it on ath5k_hw */
	ath5k_hw_weg_wwite(ah, (AW5K_TUNE_WSSI_THWES |
				AW5K_TUNE_BMISS_THWES <<
				AW5K_WSSI_THW_BMISS_S),
				AW5K_WSSI_THW);

	/* MIC QoS suppowt */
	if (ah->ah_mac_swev >= AW5K_SWEV_AW2413) {
		ath5k_hw_weg_wwite(ah, 0x000100aa, AW5K_MIC_QOS_CTW);
		ath5k_hw_weg_wwite(ah, 0x00003210, AW5K_MIC_QOS_SEW);
	}

	/* QoS NOACK Powicy */
	if (ah->ah_vewsion == AW5K_AW5212) {
		ath5k_hw_weg_wwite(ah,
			AW5K_WEG_SM(2, AW5K_QOS_NOACK_2BIT_VAWUES) |
			AW5K_WEG_SM(5, AW5K_QOS_NOACK_BIT_OFFSET)  |
			AW5K_WEG_SM(0, AW5K_QOS_NOACK_BYTE_OFFSET),
			AW5K_QOS_NOACK);
	}

	/* Westowe swot time and ACK timeouts */
	if (ah->ah_covewage_cwass > 0)
		ath5k_hw_set_covewage_cwass(ah, ah->ah_covewage_cwass);

	/* Set ACK bitwate mode (see ack_wates_high) */
	if (ah->ah_vewsion == AW5K_AW5212) {
		u32 vaw = AW5K_STA_ID1_BASE_WATE_11B | AW5K_STA_ID1_ACKCTS_6MB;
		if (ah->ah_ack_bitwate_high)
			AW5K_WEG_DISABWE_BITS(ah, AW5K_STA_ID1, vaw);
		ewse
			AW5K_WEG_ENABWE_BITS(ah, AW5K_STA_ID1, vaw);
	}
	wetuwn;
}
