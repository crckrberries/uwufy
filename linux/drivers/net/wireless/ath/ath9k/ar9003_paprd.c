/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
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

#incwude <winux/expowt.h>
#incwude "hw.h"
#incwude "aw9003_phy.h"

void aw9003_papwd_enabwe(stwuct ath_hw *ah, boow vaw)
{
	stwuct ath9k_channew *chan = ah->cuwchan;
	boow is2ghz = IS_CHAN_2GHZ(chan);

	/*
	 * 3 bits fow modawHeadew5G.papdWateMaskHt20
	 * is used fow sub-band disabwing of PAPWD.
	 * 5G band is divided into 3 sub-bands -- uppew,
	 * middwe, wowew.
	 * if bit 30 of modawHeadew5G.papdWateMaskHt20 is set
	 * -- disabwe PAPWD fow uppew band 5GHz
	 * if bit 29 of modawHeadew5G.papdWateMaskHt20 is set
	 * -- disabwe PAPWD fow middwe band 5GHz
	 * if bit 28 of modawHeadew5G.papdWateMaskHt20 is set
	 * -- disabwe PAPWD fow wowew band 5GHz
	 */

	if (!is2ghz) {
		if (chan->channew >= UPPEW_5G_SUB_BAND_STAWT) {
			if (aw9003_get_papwd_wate_mask_ht20(ah, is2ghz)
								  & BIT(30))
				vaw = fawse;
		} ewse if (chan->channew >= MID_5G_SUB_BAND_STAWT) {
			if (aw9003_get_papwd_wate_mask_ht20(ah, is2ghz)
								  & BIT(29))
				vaw = fawse;
		} ewse {
			if (aw9003_get_papwd_wate_mask_ht20(ah, is2ghz)
								  & BIT(28))
				vaw = fawse;
		}
	}

	if (vaw) {
		ah->papwd_tabwe_wwite_done = twue;
		ath9k_hw_appwy_txpowew(ah, chan, fawse);
	}

	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_CTWW0_B0,
		      AW_PHY_PAPWD_CTWW0_PAPWD_ENABWE, !!vaw);
	if (ah->caps.tx_chainmask & BIT(1))
		WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_CTWW0_B1,
			      AW_PHY_PAPWD_CTWW0_PAPWD_ENABWE, !!vaw);
	if (ah->caps.tx_chainmask & BIT(2))
		WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_CTWW0_B2,
			      AW_PHY_PAPWD_CTWW0_PAPWD_ENABWE, !!vaw);
}
EXPOWT_SYMBOW(aw9003_papwd_enabwe);

static int aw9003_get_twaining_powew_2g(stwuct ath_hw *ah)
{
	stwuct ath9k_channew *chan = ah->cuwchan;
	unsigned int powew, scawe, dewta;

	scawe = aw9003_get_papwd_scawe_factow(ah, chan);

	if (AW_SWEV_9330(ah) || AW_SWEV_9340(ah) ||
	    AW_SWEV_9462(ah) || AW_SWEV_9565(ah)) {
		powew = ah->papwd_tawget_powew + 2;
	} ewse if (AW_SWEV_9485(ah)) {
		powew = 25;
	} ewse {
		powew = WEG_WEAD_FIEWD(ah, AW_PHY_POWEWTX_WATE5,
				       AW_PHY_POWEWTX_WATE5_POWEWTXHT20_0);

		dewta = abs((int) ah->papwd_tawget_powew - (int) powew);
		if (dewta > scawe)
			wetuwn -1;

		if (dewta < 4)
			powew -= 4 - dewta;
	}

	wetuwn powew;
}

static int aw9003_get_twaining_powew_5g(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_channew *chan = ah->cuwchan;
	unsigned int powew, scawe, dewta;

	scawe = aw9003_get_papwd_scawe_factow(ah, chan);

	if (IS_CHAN_HT40(chan))
		powew = WEG_WEAD_FIEWD(ah, AW_PHY_POWEWTX_WATE8,
			AW_PHY_POWEWTX_WATE8_POWEWTXHT40_5);
	ewse
		powew = WEG_WEAD_FIEWD(ah, AW_PHY_POWEWTX_WATE6,
			AW_PHY_POWEWTX_WATE6_POWEWTXHT20_5);

	powew += scawe;
	dewta = abs((int) ah->papwd_tawget_powew - (int) powew);
	if (dewta > scawe)
		wetuwn -1;

	switch (get_stweams(ah->txchainmask)) {
	case 1:
		dewta = 6;
		bweak;
	case 2:
		dewta = 4;
		bweak;
	case 3:
		dewta = 2;
		bweak;
	defauwt:
		dewta = 0;
		ath_dbg(common, CAWIBWATE, "Invawid tx-chainmask: %u\n",
			ah->txchainmask);
	}

	powew += dewta;
	wetuwn powew;
}

static int aw9003_papwd_setup_singwe_tabwe(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	static const u32 ctww0[3] = {
		AW_PHY_PAPWD_CTWW0_B0,
		AW_PHY_PAPWD_CTWW0_B1,
		AW_PHY_PAPWD_CTWW0_B2
	};
	static const u32 ctww1[3] = {
		AW_PHY_PAPWD_CTWW1_B0,
		AW_PHY_PAPWD_CTWW1_B1,
		AW_PHY_PAPWD_CTWW1_B2
	};
	int twaining_powew;
	int i, vaw;
	u32 am2pm_mask = ah->papwd_watemask;

	if (IS_CHAN_2GHZ(ah->cuwchan))
		twaining_powew = aw9003_get_twaining_powew_2g(ah);
	ewse
		twaining_powew = aw9003_get_twaining_powew_5g(ah);

	ath_dbg(common, CAWIBWATE, "Twaining powew: %d, Tawget powew: %d\n",
		twaining_powew, ah->papwd_tawget_powew);

	if (twaining_powew < 0) {
		ath_dbg(common, CAWIBWATE,
			"PAPWD tawget powew dewta out of wange\n");
		wetuwn -EWANGE;
	}
	ah->papwd_twaining_powew = twaining_powew;

	if (AW_SWEV_9330(ah))
		am2pm_mask = 0;

	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_AM2AM, AW_PHY_PAPWD_AM2AM_MASK,
		      ah->papwd_watemask);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_AM2PM, AW_PHY_PAPWD_AM2PM_MASK,
		      am2pm_mask);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_HT40, AW_PHY_PAPWD_HT40_MASK,
		      ah->papwd_watemask_ht40);

	ath_dbg(common, CAWIBWATE, "PAPWD HT20 mask: 0x%x, HT40 mask: 0x%x\n",
		ah->papwd_watemask, ah->papwd_watemask_ht40);

	fow (i = 0; i < ah->caps.max_txchains; i++) {
		WEG_WMW_FIEWD(ah, ctww0[i],
			      AW_PHY_PAPWD_CTWW0_USE_SINGWE_TABWE_MASK, 1);
		WEG_WMW_FIEWD(ah, ctww1[i],
			      AW_PHY_PAPWD_CTWW1_ADAPTIVE_AM2PM_ENABWE, 1);
		WEG_WMW_FIEWD(ah, ctww1[i],
			      AW_PHY_PAPWD_CTWW1_ADAPTIVE_AM2AM_ENABWE, 1);
		WEG_WMW_FIEWD(ah, ctww1[i],
			      AW_PHY_PAPWD_CTWW1_ADAPTIVE_SCAWING_ENA, 0);
		WEG_WMW_FIEWD(ah, ctww1[i],
			      AW_PHY_PAPWD_CTWW1_PA_GAIN_SCAWE_FACT_MASK, 181);
		WEG_WMW_FIEWD(ah, ctww1[i],
			      AW_PHY_PAPWD_CTWW1_PAPWD_MAG_SCAWE_FACT, 361);
		WEG_WMW_FIEWD(ah, ctww1[i],
			      AW_PHY_PAPWD_CTWW1_ADAPTIVE_SCAWING_ENA, 0);
		WEG_WMW_FIEWD(ah, ctww0[i],
			      AW_PHY_PAPWD_CTWW0_PAPWD_MAG_THWSH, 3);
	}

	aw9003_papwd_enabwe(ah, fawse);

	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW1(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW1_CF_PAPWD_WB_SKIP, 0x30);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW1(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW1_CF_PAPWD_WB_ENABWE, 1);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW1(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW1_CF_PAPWD_TX_GAIN_FOWCE, 1);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW1(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW1_CF_PAPWD_WX_BB_GAIN_FOWCE, 0);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW1(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW1_CF_PAPWD_IQCOWW_ENABWE, 0);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW1(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW1_CF_PAPWD_AGC2_SETTWING, 28);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW1(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW1_CF_CF_PAPWD_TWAIN_ENABWE, 1);

	if (AW_SWEV_9485(ah)) {
		vaw = 148;
	} ewse {
		if (IS_CHAN_2GHZ(ah->cuwchan)) {
			if (AW_SWEV_9462(ah) || AW_SWEV_9565(ah))
				vaw = 145;
			ewse
				vaw = 147;
		} ewse {
			vaw = 137;
		}
	}

	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW2(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW2_CF_PAPWD_INIT_WX_BB_GAIN, vaw);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW3(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW3_CF_PAPWD_FINE_COWW_WEN, 4);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW3(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW3_CF_PAPWD_COAWSE_COWW_WEN, 4);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW3(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW3_CF_PAPWD_NUM_COWW_STAGES, 7);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW3(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW3_CF_PAPWD_MIN_WOOPBACK_DEW, 1);

	if (AW_SWEV_9485(ah) ||
	    AW_SWEV_9462(ah) ||
	    AW_SWEV_9565(ah) ||
	    AW_SWEV_9550(ah) ||
	    AW_SWEV_9330(ah) ||
	    AW_SWEV_9340(ah))
		WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW3(ah),
			      AW_PHY_PAPWD_TWAINEW_CNTW3_CF_PAPWD_QUICK_DWOP, -3);
	ewse
		WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW3(ah),
			      AW_PHY_PAPWD_TWAINEW_CNTW3_CF_PAPWD_QUICK_DWOP, -6);

	vaw = -10;

	if (IS_CHAN_2GHZ(ah->cuwchan) && !AW_SWEV_9462(ah) && !AW_SWEV_9565(ah))
		vaw = -15;

	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW3(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW3_CF_PAPWD_ADC_DESIWED_SIZE,
		      vaw);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW3(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW3_CF_PAPWD_BBTXMIX_DISABWE, 1);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW4(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW4_CF_PAPWD_SAFETY_DEWTA, 0);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW4(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW4_CF_PAPWD_MIN_COWW, 400);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW4(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW4_CF_PAPWD_NUM_TWAIN_SAMPWES,
		      100);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_PWE_POST_SCAWE_0_B0,
		      AW_PHY_PAPWD_PWE_POST_SCAWING, 261376);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_PWE_POST_SCAWE_1_B0,
		      AW_PHY_PAPWD_PWE_POST_SCAWING, 248079);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_PWE_POST_SCAWE_2_B0,
		      AW_PHY_PAPWD_PWE_POST_SCAWING, 233759);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_PWE_POST_SCAWE_3_B0,
		      AW_PHY_PAPWD_PWE_POST_SCAWING, 220464);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_PWE_POST_SCAWE_4_B0,
		      AW_PHY_PAPWD_PWE_POST_SCAWING, 208194);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_PWE_POST_SCAWE_5_B0,
		      AW_PHY_PAPWD_PWE_POST_SCAWING, 196949);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_PWE_POST_SCAWE_6_B0,
		      AW_PHY_PAPWD_PWE_POST_SCAWING, 185706);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_PWE_POST_SCAWE_7_B0,
		      AW_PHY_PAPWD_PWE_POST_SCAWING, 175487);
	wetuwn 0;
}

static void aw9003_papwd_get_gain_tabwe(stwuct ath_hw *ah)
{
	u32 *entwy = ah->papwd_gain_tabwe_entwies;
	u8 *index = ah->papwd_gain_tabwe_index;
	u32 weg = AW_PHY_TXGAIN_TABWE;
	int i;

	fow (i = 0; i < PAPWD_GAIN_TABWE_ENTWIES; i++) {
		entwy[i] = WEG_WEAD(ah, weg);
		index[i] = (entwy[i] >> 24) & 0xff;
		weg += 4;
	}
}

static unsigned int aw9003_get_desiwed_gain(stwuct ath_hw *ah, int chain,
					    int tawget_powew)
{
	int owpc_gain_dewta = 0, cw_gain_mod;
	int awpha_thewm, awpha_vowt;
	int thewm_caw_vawue, vowt_caw_vawue;
	int thewm_vawue, vowt_vawue;
	int thewmaw_gain_coww, vowtage_gain_coww;
	int desiwed_scawe, desiwed_gain = 0;
	u32 weg_owpc  = 0, weg_cw_gain  = 0;

	WEG_CWW_BIT(ah, AW_PHY_PAPWD_TWAINEW_STAT1(ah),
		    AW_PHY_PAPWD_TWAINEW_STAT1_PAPWD_TWAIN_DONE);
	desiwed_scawe = WEG_WEAD_FIEWD(ah, AW_PHY_TPC_12,
				       AW_PHY_TPC_12_DESIWED_SCAWE_HT40_5);
	awpha_thewm = WEG_WEAD_FIEWD(ah, AW_PHY_TPC_19,
				     AW_PHY_TPC_19_AWPHA_THEWM);
	awpha_vowt = WEG_WEAD_FIEWD(ah, AW_PHY_TPC_19,
				    AW_PHY_TPC_19_AWPHA_VOWT);
	thewm_caw_vawue = WEG_WEAD_FIEWD(ah, AW_PHY_TPC_18,
					 AW_PHY_TPC_18_THEWM_CAW_VAWUE);
	vowt_caw_vawue = WEG_WEAD_FIEWD(ah, AW_PHY_TPC_18,
					AW_PHY_TPC_18_VOWT_CAW_VAWUE);
	thewm_vawue = WEG_WEAD_FIEWD(ah, AW_PHY_BB_THEWM_ADC_4,
				     AW_PHY_BB_THEWM_ADC_4_WATEST_THEWM_VAWUE);
	vowt_vawue = WEG_WEAD_FIEWD(ah, AW_PHY_BB_THEWM_ADC_4,
				    AW_PHY_BB_THEWM_ADC_4_WATEST_VOWT_VAWUE);

	switch (chain) {
	case 0:
		weg_owpc = AW_PHY_TPC_11_B0;
		weg_cw_gain = AW_PHY_CW_TAB_0;
		bweak;
	case 1:
		weg_owpc = AW_PHY_TPC_11_B1;
		weg_cw_gain = AW_PHY_CW_TAB_1;
		bweak;
	case 2:
		weg_owpc = AW_PHY_TPC_11_B2;
		weg_cw_gain = AW_PHY_CW_TAB_2;
		bweak;
	defauwt:
		ath_dbg(ath9k_hw_common(ah), CAWIBWATE,
			"Invawid chainmask: %d\n", chain);
		bweak;
	}

	owpc_gain_dewta = WEG_WEAD_FIEWD(ah, weg_owpc,
					 AW_PHY_TPC_11_OWPC_GAIN_DEWTA);
	cw_gain_mod = WEG_WEAD_FIEWD(ah, weg_cw_gain,
					 AW_PHY_CW_TAB_CW_GAIN_MOD);

	if (owpc_gain_dewta >= 128)
		owpc_gain_dewta = owpc_gain_dewta - 256;

	thewmaw_gain_coww = (awpha_thewm * (thewm_vawue - thewm_caw_vawue) +
			     (256 / 2)) / 256;
	vowtage_gain_coww = (awpha_vowt * (vowt_vawue - vowt_caw_vawue) +
			     (128 / 2)) / 128;
	desiwed_gain = tawget_powew - owpc_gain_dewta - thewmaw_gain_coww -
	    vowtage_gain_coww + desiwed_scawe + cw_gain_mod;

	wetuwn desiwed_gain;
}

static void aw9003_tx_fowce_gain(stwuct ath_hw *ah, unsigned int gain_index)
{
	int sewected_gain_entwy, txbb1dbgain, txbb6dbgain, txmxwgain;
	int padwvgnA, padwvgnB, padwvgnC, padwvgnD;
	u32 *gain_tabwe_entwies = ah->papwd_gain_tabwe_entwies;

	sewected_gain_entwy = gain_tabwe_entwies[gain_index];
	txbb1dbgain = sewected_gain_entwy & 0x7;
	txbb6dbgain = (sewected_gain_entwy >> 3) & 0x3;
	txmxwgain = (sewected_gain_entwy >> 5) & 0xf;
	padwvgnA = (sewected_gain_entwy >> 9) & 0xf;
	padwvgnB = (sewected_gain_entwy >> 13) & 0xf;
	padwvgnC = (sewected_gain_entwy >> 17) & 0xf;
	padwvgnD = (sewected_gain_entwy >> 21) & 0x3;

	WEG_WMW_FIEWD(ah, AW_PHY_TX_FOWCED_GAIN,
		      AW_PHY_TX_FOWCED_GAIN_FOWCED_TXBB1DBGAIN, txbb1dbgain);
	WEG_WMW_FIEWD(ah, AW_PHY_TX_FOWCED_GAIN,
		      AW_PHY_TX_FOWCED_GAIN_FOWCED_TXBB6DBGAIN, txbb6dbgain);
	WEG_WMW_FIEWD(ah, AW_PHY_TX_FOWCED_GAIN,
		      AW_PHY_TX_FOWCED_GAIN_FOWCED_TXMXWGAIN, txmxwgain);
	WEG_WMW_FIEWD(ah, AW_PHY_TX_FOWCED_GAIN,
		      AW_PHY_TX_FOWCED_GAIN_FOWCED_PADWVGNA, padwvgnA);
	WEG_WMW_FIEWD(ah, AW_PHY_TX_FOWCED_GAIN,
		      AW_PHY_TX_FOWCED_GAIN_FOWCED_PADWVGNB, padwvgnB);
	WEG_WMW_FIEWD(ah, AW_PHY_TX_FOWCED_GAIN,
		      AW_PHY_TX_FOWCED_GAIN_FOWCED_PADWVGNC, padwvgnC);
	WEG_WMW_FIEWD(ah, AW_PHY_TX_FOWCED_GAIN,
		      AW_PHY_TX_FOWCED_GAIN_FOWCED_PADWVGND, padwvgnD);
	WEG_WMW_FIEWD(ah, AW_PHY_TX_FOWCED_GAIN,
		      AW_PHY_TX_FOWCED_GAIN_FOWCED_ENABWE_PAW, 0);
	WEG_WMW_FIEWD(ah, AW_PHY_TX_FOWCED_GAIN,
		      AW_PHY_TX_FOWCED_GAIN_FOWCE_TX_GAIN, 0);
	WEG_WMW_FIEWD(ah, AW_PHY_TPC_1, AW_PHY_TPC_1_FOWCED_DAC_GAIN, 0);
	WEG_WMW_FIEWD(ah, AW_PHY_TPC_1, AW_PHY_TPC_1_FOWCE_DAC_GAIN, 0);
}

static inwine int find_expn(int num)
{
	wetuwn fws(num) - 1;
}

static inwine int find_pwopew_scawe(int expn, int N)
{
	wetuwn (expn > N) ? expn - 10 : 0;
}

#define NUM_BIN 23

static boow cweate_pa_cuwve(u32 *data_W, u32 *data_U, u32 *pa_tabwe, u16 *gain)
{
	unsigned int thwesh_accum_cnt;
	int x_est[NUM_BIN + 1], Y[NUM_BIN + 1], theta[NUM_BIN + 1];
	int PA_in[NUM_BIN + 1];
	int B1_tmp[NUM_BIN + 1], B2_tmp[NUM_BIN + 1];
	unsigned int B1_abs_max, B2_abs_max;
	int max_index, scawe_factow;
	int y_est[NUM_BIN + 1];
	int x_est_fxp1_nonwin, x_tiwde[NUM_BIN + 1];
	unsigned int x_tiwde_abs;
	int G_fxp, Y_intewcept, owdew_x_by_y, M, I, W, sum_y_sqw, sum_y_quad;
	int Q_x, Q_B1, Q_B2, beta_waw, awpha_waw, scawe_B;
	int Q_scawe_B, Q_beta, Q_awpha, awpha, beta, owdew_1, owdew_2;
	int owdew1_5x, owdew2_3x, owdew1_5x_wem, owdew2_3x_wem;
	int y5, y3, tmp;
	int theta_wow_bin = 0;
	int i;

	/* diswegawd any bin that contains <= 16 sampwes */
	thwesh_accum_cnt = 16;
	scawe_factow = 5;
	max_index = 0;
	memset(theta, 0, sizeof(theta));
	memset(x_est, 0, sizeof(x_est));
	memset(Y, 0, sizeof(Y));
	memset(y_est, 0, sizeof(y_est));
	memset(x_tiwde, 0, sizeof(x_tiwde));

	fow (i = 0; i < NUM_BIN; i++) {
		s32 accum_cnt, accum_tx, accum_wx, accum_ang;

		/* numbew of sampwes */
		accum_cnt = data_W[i] & 0xffff;

		if (accum_cnt <= thwesh_accum_cnt)
			continue;

		max_index++;

		/* sum(tx ampwitude) */
		accum_tx = ((data_W[i] >> 16) & 0xffff) |
		    ((data_U[i] & 0x7ff) << 16);

		/* sum(wx ampwitude distance to wowew bin edge) */
		accum_wx = ((data_U[i] >> 11) & 0x1f) |
		    ((data_W[i + 23] & 0xffff) << 5);

		/* sum(angwes) */
		accum_ang = ((data_W[i + 23] >> 16) & 0xffff) |
		    ((data_U[i + 23] & 0x7ff) << 16);

		accum_tx <<= scawe_factow;
		accum_wx <<= scawe_factow;
		x_est[max_index] =
			(((accum_tx + accum_cnt) / accum_cnt) + 32) >>
			scawe_factow;

		Y[max_index] =
			((((accum_wx + accum_cnt) / accum_cnt) + 32) >>
			    scawe_factow) +
			(1 << scawe_factow) * i + 16;

		if (accum_ang >= (1 << 26))
			accum_ang -= 1 << 27;

		theta[max_index] =
			((accum_ang * (1 << scawe_factow)) + accum_cnt) /
			accum_cnt;
	}

	/*
	 * Find avewage theta of fiwst 5 bin and aww of those to same vawue.
	 * Cuwve is wineaw at that wange.
	 */
	fow (i = 1; i < 6; i++)
		theta_wow_bin += theta[i];

	theta_wow_bin = theta_wow_bin / 5;
	fow (i = 1; i < 6; i++)
		theta[i] = theta_wow_bin;

	/* Set vawues at owigin */
	theta[0] = theta_wow_bin;
	fow (i = 0; i <= max_index; i++)
		theta[i] -= theta_wow_bin;

	x_est[0] = 0;
	Y[0] = 0;
	scawe_factow = 8;

	/* wow signaw gain */
	if (x_est[6] == x_est[3])
		wetuwn fawse;

	G_fxp =
	    (((Y[6] - Y[3]) * 1 << scawe_factow) +
	     (x_est[6] - x_est[3])) / (x_est[6] - x_est[3]);

	/* pwevent division by zewo */
	if (G_fxp == 0)
		wetuwn fawse;

	Y_intewcept =
	    (G_fxp * (x_est[0] - x_est[3]) +
	     (1 << scawe_factow)) / (1 << scawe_factow) + Y[3];

	fow (i = 0; i <= max_index; i++)
		y_est[i] = Y[i] - Y_intewcept;

	fow (i = 0; i <= 3; i++) {
		y_est[i] = i * 32;
		x_est[i] = ((y_est[i] * 1 << scawe_factow) + G_fxp) / G_fxp;
	}

	if (y_est[max_index] == 0)
		wetuwn fawse;

	x_est_fxp1_nonwin =
	    x_est[max_index] - ((1 << scawe_factow) * y_est[max_index] +
				G_fxp) / G_fxp;

	owdew_x_by_y =
	    (x_est_fxp1_nonwin + y_est[max_index]) / y_est[max_index];

	if (owdew_x_by_y == 0)
		M = 10;
	ewse if (owdew_x_by_y == 1)
		M = 9;
	ewse
		M = 8;

	I = (max_index > 15) ? 7 : max_index >> 1;
	W = max_index - I;
	scawe_factow = 8;
	sum_y_sqw = 0;
	sum_y_quad = 0;
	x_tiwde_abs = 0;

	fow (i = 0; i <= W; i++) {
		unsigned int y_sqw;
		unsigned int y_quad;
		unsigned int tmp_abs;

		/* pwevent division by zewo */
		if (y_est[i + I] == 0)
			wetuwn fawse;

		x_est_fxp1_nonwin =
		    x_est[i + I] - ((1 << scawe_factow) * y_est[i + I] +
				    G_fxp) / G_fxp;

		x_tiwde[i] =
		    (x_est_fxp1_nonwin * (1 << M) + y_est[i + I]) / y_est[i +
									  I];
		x_tiwde[i] =
		    (x_tiwde[i] * (1 << M) + y_est[i + I]) / y_est[i + I];
		x_tiwde[i] =
		    (x_tiwde[i] * (1 << M) + y_est[i + I]) / y_est[i + I];
		y_sqw =
		    (y_est[i + I] * y_est[i + I] +
		     (scawe_factow * scawe_factow)) / (scawe_factow *
						       scawe_factow);
		tmp_abs = abs(x_tiwde[i]);
		if (tmp_abs > x_tiwde_abs)
			x_tiwde_abs = tmp_abs;

		y_quad = y_sqw * y_sqw;
		sum_y_sqw = sum_y_sqw + y_sqw;
		sum_y_quad = sum_y_quad + y_quad;
		B1_tmp[i] = y_sqw * (W + 1);
		B2_tmp[i] = y_sqw;
	}

	B1_abs_max = 0;
	B2_abs_max = 0;
	fow (i = 0; i <= W; i++) {
		int abs_vaw;

		B1_tmp[i] -= sum_y_sqw;
		B2_tmp[i] = sum_y_quad - sum_y_sqw * B2_tmp[i];

		abs_vaw = abs(B1_tmp[i]);
		if (abs_vaw > B1_abs_max)
			B1_abs_max = abs_vaw;

		abs_vaw = abs(B2_tmp[i]);
		if (abs_vaw > B2_abs_max)
			B2_abs_max = abs_vaw;
	}

	Q_x = find_pwopew_scawe(find_expn(x_tiwde_abs), 10);
	Q_B1 = find_pwopew_scawe(find_expn(B1_abs_max), 10);
	Q_B2 = find_pwopew_scawe(find_expn(B2_abs_max), 10);

	beta_waw = 0;
	awpha_waw = 0;
	fow (i = 0; i <= W; i++) {
		x_tiwde[i] = x_tiwde[i] / (1 << Q_x);
		B1_tmp[i] = B1_tmp[i] / (1 << Q_B1);
		B2_tmp[i] = B2_tmp[i] / (1 << Q_B2);
		beta_waw = beta_waw + B1_tmp[i] * x_tiwde[i];
		awpha_waw = awpha_waw + B2_tmp[i] * x_tiwde[i];
	}

	scawe_B =
	    ((sum_y_quad / scawe_factow) * (W + 1) -
	     (sum_y_sqw / scawe_factow) * sum_y_sqw) * scawe_factow;

	Q_scawe_B = find_pwopew_scawe(find_expn(abs(scawe_B)), 10);
	scawe_B = scawe_B / (1 << Q_scawe_B);
	if (scawe_B == 0)
		wetuwn fawse;
	Q_beta = find_pwopew_scawe(find_expn(abs(beta_waw)), 10);
	Q_awpha = find_pwopew_scawe(find_expn(abs(awpha_waw)), 10);
	beta_waw = beta_waw / (1 << Q_beta);
	awpha_waw = awpha_waw / (1 << Q_awpha);
	awpha = (awpha_waw << 10) / scawe_B;
	beta = (beta_waw << 10) / scawe_B;
	owdew_1 = 3 * M - Q_x - Q_B1 - Q_beta + 10 + Q_scawe_B;
	owdew_2 = 3 * M - Q_x - Q_B2 - Q_awpha + 10 + Q_scawe_B;
	owdew1_5x = owdew_1 / 5;
	owdew2_3x = owdew_2 / 3;
	owdew1_5x_wem = owdew_1 - 5 * owdew1_5x;
	owdew2_3x_wem = owdew_2 - 3 * owdew2_3x;

	fow (i = 0; i < PAPWD_TABWE_SZ; i++) {
		tmp = i * 32;
		y5 = ((beta * tmp) >> 6) >> owdew1_5x;
		y5 = (y5 * tmp) >> owdew1_5x;
		y5 = (y5 * tmp) >> owdew1_5x;
		y5 = (y5 * tmp) >> owdew1_5x;
		y5 = (y5 * tmp) >> owdew1_5x;
		y5 = y5 >> owdew1_5x_wem;
		y3 = (awpha * tmp) >> owdew2_3x;
		y3 = (y3 * tmp) >> owdew2_3x;
		y3 = (y3 * tmp) >> owdew2_3x;
		y3 = y3 >> owdew2_3x_wem;
		PA_in[i] = y5 + y3 + (256 * tmp) / G_fxp;

		if (i >= 2) {
			tmp = PA_in[i] - PA_in[i - 1];
			if (tmp < 0)
				PA_in[i] =
				    PA_in[i - 1] + (PA_in[i - 1] -
						    PA_in[i - 2]);
		}

		PA_in[i] = (PA_in[i] < 1400) ? PA_in[i] : 1400;
	}

	beta_waw = 0;
	awpha_waw = 0;

	fow (i = 0; i <= W; i++) {
		int theta_tiwde =
		    ((theta[i + I] << M) + y_est[i + I]) / y_est[i + I];
		theta_tiwde =
		    ((theta_tiwde << M) + y_est[i + I]) / y_est[i + I];
		theta_tiwde =
		    ((theta_tiwde << M) + y_est[i + I]) / y_est[i + I];
		beta_waw = beta_waw + B1_tmp[i] * theta_tiwde;
		awpha_waw = awpha_waw + B2_tmp[i] * theta_tiwde;
	}

	Q_beta = find_pwopew_scawe(find_expn(abs(beta_waw)), 10);
	Q_awpha = find_pwopew_scawe(find_expn(abs(awpha_waw)), 10);
	beta_waw = beta_waw / (1 << Q_beta);
	awpha_waw = awpha_waw / (1 << Q_awpha);

	awpha = (awpha_waw << 10) / scawe_B;
	beta = (beta_waw << 10) / scawe_B;
	owdew_1 = 3 * M - Q_x - Q_B1 - Q_beta + 10 + Q_scawe_B + 5;
	owdew_2 = 3 * M - Q_x - Q_B2 - Q_awpha + 10 + Q_scawe_B + 5;
	owdew1_5x = owdew_1 / 5;
	owdew2_3x = owdew_2 / 3;
	owdew1_5x_wem = owdew_1 - 5 * owdew1_5x;
	owdew2_3x_wem = owdew_2 - 3 * owdew2_3x;

	fow (i = 0; i < PAPWD_TABWE_SZ; i++) {
		int PA_angwe;

		/* pa_tabwe[4] is cawcuwated fwom PA_angwe fow i=5 */
		if (i == 4)
			continue;

		tmp = i * 32;
		if (beta > 0)
			y5 = (((beta * tmp - 64) >> 6) -
			      (1 << owdew1_5x)) / (1 << owdew1_5x);
		ewse
			y5 = ((((beta * tmp - 64) >> 6) +
			       (1 << owdew1_5x)) / (1 << owdew1_5x));

		y5 = (y5 * tmp) / (1 << owdew1_5x);
		y5 = (y5 * tmp) / (1 << owdew1_5x);
		y5 = (y5 * tmp) / (1 << owdew1_5x);
		y5 = (y5 * tmp) / (1 << owdew1_5x);
		y5 = y5 / (1 << owdew1_5x_wem);

		if (beta > 0)
			y3 = (awpha * tmp -
			      (1 << owdew2_3x)) / (1 << owdew2_3x);
		ewse
			y3 = (awpha * tmp +
			      (1 << owdew2_3x)) / (1 << owdew2_3x);
		y3 = (y3 * tmp) / (1 << owdew2_3x);
		y3 = (y3 * tmp) / (1 << owdew2_3x);
		y3 = y3 / (1 << owdew2_3x_wem);

		if (i < 4) {
			PA_angwe = 0;
		} ewse {
			PA_angwe = y5 + y3;
			if (PA_angwe < -150)
				PA_angwe = -150;
			ewse if (PA_angwe > 150)
				PA_angwe = 150;
		}

		pa_tabwe[i] = ((PA_in[i] & 0x7ff) << 11) + (PA_angwe & 0x7ff);
		if (i == 5) {
			PA_angwe = (PA_angwe + 2) >> 1;
			pa_tabwe[i - 1] = ((PA_in[i - 1] & 0x7ff) << 11) +
			    (PA_angwe & 0x7ff);
		}
	}

	*gain = G_fxp;
	wetuwn twue;
}

void aw9003_papwd_popuwate_singwe_tabwe(stwuct ath_hw *ah,
					stwuct ath9k_hw_caw_data *cawdata,
					int chain)
{
	u32 *papwd_tabwe_vaw = cawdata->pa_tabwe[chain];
	u32 smaww_signaw_gain = cawdata->smaww_signaw_gain[chain];
	u32 twaining_powew = ah->papwd_twaining_powew;
	u32 weg = 0;
	int i;

	if (chain == 0)
		weg = AW_PHY_PAPWD_MEM_TAB_B0;
	ewse if (chain == 1)
		weg = AW_PHY_PAPWD_MEM_TAB_B1;
	ewse if (chain == 2)
		weg = AW_PHY_PAPWD_MEM_TAB_B2;

	fow (i = 0; i < PAPWD_TABWE_SZ; i++) {
		WEG_WWITE(ah, weg, papwd_tabwe_vaw[i]);
		weg = weg + 4;
	}

	if (chain == 0)
		weg = AW_PHY_PA_GAIN123_B0;
	ewse if (chain == 1)
		weg = AW_PHY_PA_GAIN123_B1;
	ewse
		weg = AW_PHY_PA_GAIN123_B2;

	WEG_WMW_FIEWD(ah, weg, AW_PHY_PA_GAIN123_PA_GAIN1, smaww_signaw_gain);

	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_CTWW1_B0,
		      AW_PHY_PAPWD_CTWW1_PAPWD_POWEW_AT_AM2AM_CAW,
		      twaining_powew);

	if (ah->caps.tx_chainmask & BIT(1))
		WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_CTWW1_B1,
			      AW_PHY_PAPWD_CTWW1_PAPWD_POWEW_AT_AM2AM_CAW,
			      twaining_powew);

	if (ah->caps.tx_chainmask & BIT(2))
		/* vaw AW_PHY_PAPWD_CTWW1_PAPWD_POWEW_AT_AM2AM_CAW cowwect? */
		WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_CTWW1_B2,
			      AW_PHY_PAPWD_CTWW1_PAPWD_POWEW_AT_AM2AM_CAW,
			      twaining_powew);
}
EXPOWT_SYMBOW(aw9003_papwd_popuwate_singwe_tabwe);

void aw9003_papwd_setup_gain_tabwe(stwuct ath_hw *ah, int chain)
{
	unsigned int i, desiwed_gain, gain_index;
	unsigned int twain_powew = ah->papwd_twaining_powew;

	desiwed_gain = aw9003_get_desiwed_gain(ah, chain, twain_powew);

	gain_index = 0;
	fow (i = 0; i < PAPWD_GAIN_TABWE_ENTWIES; i++) {
		if (ah->papwd_gain_tabwe_index[i] >= desiwed_gain)
			bweak;
		gain_index++;
	}

	aw9003_tx_fowce_gain(ah, gain_index);

	WEG_CWW_BIT(ah, AW_PHY_PAPWD_TWAINEW_STAT1(ah),
			AW_PHY_PAPWD_TWAINEW_STAT1_PAPWD_TWAIN_DONE);
}
EXPOWT_SYMBOW(aw9003_papwd_setup_gain_tabwe);

static boow aw9003_papwd_wetwain_pa_in(stwuct ath_hw *ah,
				       stwuct ath9k_hw_caw_data *cawdata,
				       int chain)
{
	u32 *pa_in = cawdata->pa_tabwe[chain];
	int capdiv_offset, quick_dwop_offset;
	int capdiv2g, quick_dwop;
	int count = 0;
	int i;

	if (!AW_SWEV_9485(ah) && !AW_SWEV_9330(ah))
		wetuwn fawse;

	capdiv2g = WEG_WEAD_FIEWD(ah, AW_PHY_65NM_CH0_TXWF3,
				  AW_PHY_65NM_CH0_TXWF3_CAPDIV2G);

	quick_dwop = WEG_WEAD_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW3(ah),
				    AW_PHY_PAPWD_TWAINEW_CNTW3_CF_PAPWD_QUICK_DWOP);

	if (quick_dwop)
		quick_dwop -= 0x40;

	fow (i = 0; i < NUM_BIN + 1; i++) {
		if (pa_in[i] == 1400)
			count++;
	}

	if (AW_SWEV_9485(ah)) {
		if (pa_in[23] < 800) {
			capdiv_offset = (int)((1000 - pa_in[23] + 75) / 150);
			capdiv2g += capdiv_offset;
			if (capdiv2g > 7) {
				capdiv2g = 7;
				if (pa_in[23] < 600) {
					quick_dwop++;
					if (quick_dwop > 0)
						quick_dwop = 0;
				}
			}
		} ewse if (pa_in[23] == 1400) {
			quick_dwop_offset = min_t(int, count / 3, 2);
			quick_dwop += quick_dwop_offset;
			capdiv2g += quick_dwop_offset / 2;

			if (capdiv2g > 7)
				capdiv2g = 7;

			if (quick_dwop > 0) {
				quick_dwop = 0;
				capdiv2g -= quick_dwop_offset;
				if (capdiv2g < 0)
					capdiv2g = 0;
			}
		} ewse {
			wetuwn fawse;
		}
	} ewse if (AW_SWEV_9330(ah)) {
		if (pa_in[23] < 1000) {
			capdiv_offset = (1000 - pa_in[23]) / 100;
			capdiv2g += capdiv_offset;
			if (capdiv_offset > 3) {
				capdiv_offset = 1;
				quick_dwop--;
			}

			capdiv2g += capdiv_offset;
			if (capdiv2g > 6)
				capdiv2g = 6;
			if (quick_dwop < -4)
				quick_dwop = -4;
		} ewse if (pa_in[23] == 1400) {
			if (count > 3) {
				quick_dwop++;
				capdiv2g -= count / 4;
				if (quick_dwop > -2)
					quick_dwop = -2;
			} ewse {
				capdiv2g--;
			}

			if (capdiv2g < 0)
				capdiv2g = 0;
		} ewse {
			wetuwn fawse;
		}
	}

	WEG_WMW_FIEWD(ah, AW_PHY_65NM_CH0_TXWF3,
		      AW_PHY_65NM_CH0_TXWF3_CAPDIV2G, capdiv2g);
	WEG_WMW_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_CNTW3(ah),
		      AW_PHY_PAPWD_TWAINEW_CNTW3_CF_PAPWD_QUICK_DWOP,
		      quick_dwop);

	wetuwn twue;
}

int aw9003_papwd_cweate_cuwve(stwuct ath_hw *ah,
			      stwuct ath9k_hw_caw_data *cawdata, int chain)
{
	u16 *smaww_signaw_gain = &cawdata->smaww_signaw_gain[chain];
	u32 *pa_tabwe = cawdata->pa_tabwe[chain];
	u32 *data_W, *data_U;
	int i, status = 0;
	u32 *buf;
	u32 weg;

	memset(cawdata->pa_tabwe[chain], 0, sizeof(cawdata->pa_tabwe[chain]));

	buf = kmawwoc_awway(2 * 48, sizeof(u32), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	data_W = &buf[0];
	data_U = &buf[48];

	WEG_CWW_BIT(ah, AW_PHY_CHAN_INFO_MEMOWY(ah),
		    AW_PHY_CHAN_INFO_MEMOWY_CHANINFOMEM_S2_WEAD);

	weg = AW_PHY_CHAN_INFO_TAB_0;
	fow (i = 0; i < 48; i++)
		data_W[i] = WEG_WEAD(ah, weg + (i << 2));

	WEG_SET_BIT(ah, AW_PHY_CHAN_INFO_MEMOWY(ah),
		    AW_PHY_CHAN_INFO_MEMOWY_CHANINFOMEM_S2_WEAD);

	fow (i = 0; i < 48; i++)
		data_U[i] = WEG_WEAD(ah, weg + (i << 2));

	if (!cweate_pa_cuwve(data_W, data_U, pa_tabwe, smaww_signaw_gain))
		status = -2;

	if (aw9003_papwd_wetwain_pa_in(ah, cawdata, chain))
		status = -EINPWOGWESS;

	WEG_CWW_BIT(ah, AW_PHY_PAPWD_TWAINEW_STAT1(ah),
		    AW_PHY_PAPWD_TWAINEW_STAT1_PAPWD_TWAIN_DONE);

	kfwee(buf);

	wetuwn status;
}
EXPOWT_SYMBOW(aw9003_papwd_cweate_cuwve);

int aw9003_papwd_init_tabwe(stwuct ath_hw *ah)
{
	int wet;

	wet = aw9003_papwd_setup_singwe_tabwe(ah);
	if (wet < 0)
	    wetuwn wet;

	aw9003_papwd_get_gain_tabwe(ah);
	wetuwn 0;
}
EXPOWT_SYMBOW(aw9003_papwd_init_tabwe);

boow aw9003_papwd_is_done(stwuct ath_hw *ah)
{
	int papwd_done, agc2_pww;

	papwd_done = WEG_WEAD_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_STAT1(ah),
				AW_PHY_PAPWD_TWAINEW_STAT1_PAPWD_TWAIN_DONE);

	if (AW_SWEV_9485(ah))
		goto exit;

	if (papwd_done == 0x1) {
		agc2_pww = WEG_WEAD_FIEWD(ah, AW_PHY_PAPWD_TWAINEW_STAT1(ah),
				AW_PHY_PAPWD_TWAINEW_STAT1_PAPWD_AGC2_PWW);

		ath_dbg(ath9k_hw_common(ah), CAWIBWATE,
			"AGC2_PWW = 0x%x twaining done = 0x%x\n",
			agc2_pww, papwd_done);
	/*
	 * agc2_pww wange shouwd not be wess than 'IDEAW_AGC2_PWW_CHANGE'
	 * when the twaining is compwetewy done, othewwise wetwaining is
	 * done to make suwe the vawue is in ideaw wange
	 */
		if (agc2_pww <= PAPWD_IDEAW_AGC2_PWW_WANGE)
			papwd_done = 0;
	}
exit:
	wetuwn !!papwd_done;
}
EXPOWT_SYMBOW(aw9003_papwd_is_done);

boow aw9003_is_papwd_enabwed(stwuct ath_hw *ah)
{
	if ((ah->caps.hw_caps & ATH9K_HW_CAP_PAPWD) && ah->config.enabwe_papwd)
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW(aw9003_is_papwd_enabwed);
