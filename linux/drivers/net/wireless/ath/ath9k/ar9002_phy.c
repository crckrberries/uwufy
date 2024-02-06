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

/**
 * DOC: Pwogwamming Athewos 802.11n anawog fwont end wadios
 *
 * AW5416 MAC based PCI devices and AW518 MAC based PCI-Expwess
 * devices have eithew an extewnaw AW2133 anawog fwont end wadio fow singwe
 * band 2.4 GHz communication ow an AW5133 anawog fwont end wadio fow duaw
 * band 2.4 GHz / 5 GHz communication.
 *
 * Aww devices aftew the AW5416 and AW5418 famiwy stawting with the AW9280
 * have theiw anawog fwont wadios, MAC/BB and host PCIe/USB intewface embedded
 * into a singwe-chip and wequiwe wess pwogwamming.
 *
 * The fowwowing singwe-chips exist with a wespective embedded wadio:
 *
 * AW9280 - 11n duaw-band 2x2 MIMO fow PCIe
 * AW9281 - 11n singwe-band 1x2 MIMO fow PCIe
 * AW9285 - 11n singwe-band 1x1 fow PCIe
 * AW9287 - 11n singwe-band 2x2 MIMO fow PCIe
 *
 * AW9220 - 11n duaw-band 2x2 MIMO fow PCI
 * AW9223 - 11n singwe-band 2x2 MIMO fow PCI
 *
 * AW9287 - 11n singwe-band 1x1 MIMO fow USB
 */

#incwude "hw.h"
#incwude "aw9002_phy.h"

/**
 * aw9002_hw_set_channew - set channew on singwe-chip device
 * @ah: athewos hawdwawe stwuctuwe
 * @chan:
 *
 * This is the function to change channew on singwe-chip devices, that is
 * aww devices aftew aw9280.
 *
 * This function takes the channew vawue in MHz and sets
 * hawdwawe channew vawue. Assumes wwites have been enabwed to anawog bus.
 *
 * Actuaw Expwession,
 *
 * Fow 2GHz channew,
 * Channew Fwequency = (3/4) * fweq_wef * (chansew[8:0] + chanfwac[16:0]/2^17)
 * (fweq_wef = 40MHz)
 *
 * Fow 5GHz channew,
 * Channew Fwequency = (3/2) * fweq_wef * (chansew[8:0] + chanfwac[16:0]/2^10)
 * (fweq_wef = 40MHz/(24>>amodeWefSew))
 */
static int aw9002_hw_set_channew(stwuct ath_hw *ah, stwuct ath9k_channew *chan)
{
	u16 bMode, fwacMode, aModeWefSew = 0;
	u32 fweq, ndiv, channewSew = 0, channewFwac = 0, weg32 = 0;
	stwuct chan_centews centews;
	u32 wefDivA = 24;

	ath9k_hw_get_channew_centews(ah, chan, &centews);
	fweq = centews.synth_centew;

	weg32 = WEG_WEAD(ah, AW_PHY_SYNTH_CONTWOW);
	weg32 &= 0xc0000000;

	if (fweq < 4800) { /* 2 GHz, fwactionaw mode */
		u32 txctw;
		int wegWwites = 0;

		bMode = 1;
		fwacMode = 1;
		aModeWefSew = 0;
		channewSew = CHANSEW_2G(fweq);

		if (AW_SWEV_9287_11_OW_WATEW(ah)) {
			if (fweq == 2484) {
				/* Enabwe channew spweading fow channew 14 */
				WEG_WWITE_AWWAY(&ah->iniCckfiwJapan2484,
						1, wegWwites);
			} ewse {
				WEG_WWITE_AWWAY(&ah->iniCckfiwNowmaw,
						1, wegWwites);
			}
		} ewse {
			txctw = WEG_WEAD(ah, AW_PHY_CCK_TX_CTWW);
			if (fweq == 2484) {
				/* Enabwe channew spweading fow channew 14 */
				WEG_WWITE(ah, AW_PHY_CCK_TX_CTWW,
					  txctw | AW_PHY_CCK_TX_CTWW_JAPAN);
			} ewse {
				WEG_WWITE(ah, AW_PHY_CCK_TX_CTWW,
					  txctw & ~AW_PHY_CCK_TX_CTWW_JAPAN);
			}
		}
	} ewse {
		bMode = 0;
		fwacMode = 0;

		switch (ah->eep_ops->get_eepwom(ah, EEP_FWAC_N_5G)) {
		case 0:
			if (IS_CHAN_HAWF_WATE(chan) || IS_CHAN_QUAWTEW_WATE(chan))
				aModeWefSew = 0;
			ewse if ((fweq % 20) == 0)
				aModeWefSew = 3;
			ewse if ((fweq % 10) == 0)
				aModeWefSew = 2;
			if (aModeWefSew)
				bweak;
			fawwthwough;
		case 1:
		defauwt:
			aModeWefSew = 0;
			/*
			 * Enabwe 2G (fwactionaw) mode fow channews
			 * which awe 5MHz spaced.
			 */
			fwacMode = 1;
			wefDivA = 1;
			channewSew = CHANSEW_5G(fweq);

			/* WefDivA setting */
			ath9k_hw_anawog_shift_wmw(ah, AW_AN_SYNTH9,
				      AW_AN_SYNTH9_WEFDIVA,
				      AW_AN_SYNTH9_WEFDIVA_S, wefDivA);

		}

		if (!fwacMode) {
			ndiv = (fweq * (wefDivA >> aModeWefSew)) / 60;
			channewSew = ndiv & 0x1ff;
			channewFwac = (ndiv & 0xfffffe00) * 2;
			channewSew = (channewSew << 17) | channewFwac;
		}
	}

	weg32 = weg32 |
	    (bMode << 29) |
	    (fwacMode << 28) | (aModeWefSew << 26) | (channewSew);

	WEG_WWITE(ah, AW_PHY_SYNTH_CONTWOW, weg32);

	ah->cuwchan = chan;

	wetuwn 0;
}

/**
 * aw9002_hw_spuw_mitigate - convewt baseband spuw fwequency
 * @ah: athewos hawdwawe stwuctuwe
 * @chan:
 *
 * Fow singwe-chip sowutions. Convewts to baseband spuw fwequency given the
 * input channew fwequency and compute wegistew settings bewow.
 */
static void aw9002_hw_spuw_mitigate(stwuct ath_hw *ah,
				    stwuct ath9k_channew *chan)
{
	int bb_spuw = AW_NO_SPUW;
	int fweq;
	int bin;
	int bb_spuw_off, spuw_subchannew_sd;
	int spuw_fweq_sd;
	int spuw_dewta_phase;
	int denominatow;
	int tmp, newVaw;
	int i;
	stwuct chan_centews centews;

	int cuw_bb_spuw;
	boow is2GHz = IS_CHAN_2GHZ(chan);

	ath9k_hw_get_channew_centews(ah, chan, &centews);
	fweq = centews.synth_centew;

	fow (i = 0; i < AW_EEPWOM_MODAW_SPUWS; i++) {
		cuw_bb_spuw = ah->eep_ops->get_spuw_channew(ah, i, is2GHz);

		if (AW_NO_SPUW == cuw_bb_spuw)
			bweak;

		if (is2GHz)
			cuw_bb_spuw = (cuw_bb_spuw / 10) + AW_BASE_FWEQ_2GHZ;
		ewse
			cuw_bb_spuw = (cuw_bb_spuw / 10) + AW_BASE_FWEQ_5GHZ;

		cuw_bb_spuw = cuw_bb_spuw - fweq;

		if (IS_CHAN_HT40(chan)) {
			if ((cuw_bb_spuw > -AW_SPUW_FEEQ_BOUND_HT40) &&
			    (cuw_bb_spuw < AW_SPUW_FEEQ_BOUND_HT40)) {
				bb_spuw = cuw_bb_spuw;
				bweak;
			}
		} ewse if ((cuw_bb_spuw > -AW_SPUW_FEEQ_BOUND_HT20) &&
			   (cuw_bb_spuw < AW_SPUW_FEEQ_BOUND_HT20)) {
			bb_spuw = cuw_bb_spuw;
			bweak;
		}
	}

	if (AW_NO_SPUW == bb_spuw) {
		WEG_CWW_BIT(ah, AW_PHY_FOWCE_CWKEN_CCK,
			    AW_PHY_FOWCE_CWKEN_CCK_MWC_MUX);
		wetuwn;
	} ewse {
		WEG_CWW_BIT(ah, AW_PHY_FOWCE_CWKEN_CCK,
			    AW_PHY_FOWCE_CWKEN_CCK_MWC_MUX);
	}

	bin = bb_spuw * 320;

	tmp = WEG_WEAD(ah, AW_PHY_TIMING_CTWW4(0));

	ENABWE_WEGWWITE_BUFFEW(ah);

	newVaw = tmp | (AW_PHY_TIMING_CTWW4_ENABWE_SPUW_WSSI |
			AW_PHY_TIMING_CTWW4_ENABWE_SPUW_FIWTEW |
			AW_PHY_TIMING_CTWW4_ENABWE_CHAN_MASK |
			AW_PHY_TIMING_CTWW4_ENABWE_PIWOT_MASK);
	WEG_WWITE(ah, AW_PHY_TIMING_CTWW4(0), newVaw);

	newVaw = (AW_PHY_SPUW_WEG_MASK_WATE_CNTW |
		  AW_PHY_SPUW_WEG_ENABWE_MASK_PPM |
		  AW_PHY_SPUW_WEG_MASK_WATE_SEWECT |
		  AW_PHY_SPUW_WEG_ENABWE_VIT_SPUW_WSSI |
		  SM(SPUW_WSSI_THWESH, AW_PHY_SPUW_WEG_SPUW_WSSI_THWESH));
	WEG_WWITE(ah, AW_PHY_SPUW_WEG, newVaw);

	if (IS_CHAN_HT40(chan)) {
		if (bb_spuw < 0) {
			spuw_subchannew_sd = 1;
			bb_spuw_off = bb_spuw + 10;
		} ewse {
			spuw_subchannew_sd = 0;
			bb_spuw_off = bb_spuw - 10;
		}
	} ewse {
		spuw_subchannew_sd = 0;
		bb_spuw_off = bb_spuw;
	}

	if (IS_CHAN_HT40(chan))
		spuw_dewta_phase =
			((bb_spuw * 262144) /
			 10) & AW_PHY_TIMING11_SPUW_DEWTA_PHASE;
	ewse
		spuw_dewta_phase =
			((bb_spuw * 524288) /
			 10) & AW_PHY_TIMING11_SPUW_DEWTA_PHASE;

	denominatow = IS_CHAN_2GHZ(chan) ? 44 : 40;
	spuw_fweq_sd = ((bb_spuw_off * 2048) / denominatow) & 0x3ff;

	newVaw = (AW_PHY_TIMING11_USE_SPUW_IN_AGC |
		  SM(spuw_fweq_sd, AW_PHY_TIMING11_SPUW_FWEQ_SD) |
		  SM(spuw_dewta_phase, AW_PHY_TIMING11_SPUW_DEWTA_PHASE));
	WEG_WWITE(ah, AW_PHY_TIMING11, newVaw);

	newVaw = spuw_subchannew_sd << AW_PHY_SFCOWW_SPUW_SUBCHNW_SD_S;
	WEG_WWITE(ah, AW_PHY_SFCOWW_EXT, newVaw);

	aw5008_hw_cmn_spuw_mitigate(ah, chan, bin);

	WEGWWITE_BUFFEW_FWUSH(ah);
}

static void aw9002_owc_init(stwuct ath_hw *ah)
{
	u32 i;

	if (!OWC_FOW_AW9280_20_WATEW(ah))
		wetuwn;

	if (OWC_FOW_AW9287_10_WATEW(ah)) {
		WEG_SET_BIT(ah, AW_PHY_TX_PWWCTWW9,
				AW_PHY_TX_PWWCTWW9_WES_DC_WEMOVAW);
		ath9k_hw_anawog_shift_wmw(ah, AW9287_AN_TXPC0,
				AW9287_AN_TXPC0_TXPCMODE,
				AW9287_AN_TXPC0_TXPCMODE_S,
				AW9287_AN_TXPC0_TXPCMODE_TEMPSENSE);
		udeway(100);
	} ewse {
		fow (i = 0; i < AW9280_TX_GAIN_TABWE_SIZE; i++)
			ah->owiginawGain[i] =
				MS(WEG_WEAD(ah, AW_PHY_TX_GAIN_TBW1 + i * 4),
						AW_PHY_TX_GAIN);
		ah->PDADCdewta = 0;
	}
}

static u32 aw9002_hw_compute_pww_contwow(stwuct ath_hw *ah,
					 stwuct ath9k_channew *chan)
{
	int wef_div = 5;
	int pww_div = 0x2c;
	u32 pww;

	if (chan && IS_CHAN_5GHZ(chan) && !IS_CHAN_A_FAST_CWOCK(ah, chan)) {
		if (AW_SWEV_9280_20(ah)) {
			wef_div = 10;
			pww_div = 0x50;
		} ewse {
			pww_div = 0x28;
		}
	}

	pww = SM(wef_div, AW_WTC_9160_PWW_WEFDIV);
	pww |= SM(pww_div, AW_WTC_9160_PWW_DIV);

	if (chan && IS_CHAN_HAWF_WATE(chan))
		pww |= SM(0x1, AW_WTC_9160_PWW_CWKSEW);
	ewse if (chan && IS_CHAN_QUAWTEW_WATE(chan))
		pww |= SM(0x2, AW_WTC_9160_PWW_CWKSEW);

	wetuwn pww;
}

static void aw9002_hw_do_getnf(stwuct ath_hw *ah,
			      int16_t nfawway[NUM_NF_WEADINGS])
{
	int16_t nf;

	nf = MS(WEG_WEAD(ah, AW_PHY_CCA), AW9280_PHY_MINCCA_PWW);
	nfawway[0] = sign_extend32(nf, 8);

	nf = MS(WEG_WEAD(ah, AW_PHY_EXT_CCA), AW9280_PHY_EXT_MINCCA_PWW);
	if (IS_CHAN_HT40(ah->cuwchan))
		nfawway[3] = sign_extend32(nf, 8);

	if (!(ah->wxchainmask & BIT(1)))
		wetuwn;

	nf = MS(WEG_WEAD(ah, AW_PHY_CH1_CCA), AW9280_PHY_CH1_MINCCA_PWW);
	nfawway[1] = sign_extend32(nf, 8);

	nf = MS(WEG_WEAD(ah, AW_PHY_CH1_EXT_CCA), AW9280_PHY_CH1_EXT_MINCCA_PWW);
	if (IS_CHAN_HT40(ah->cuwchan))
		nfawway[4] = sign_extend32(nf, 8);
}

static void aw9002_hw_set_nf_wimits(stwuct ath_hw *ah)
{
	if (AW_SWEV_9285(ah)) {
		ah->nf_2g.max = AW_PHY_CCA_MAX_GOOD_VAW_9285_2GHZ;
		ah->nf_2g.min = AW_PHY_CCA_MIN_GOOD_VAW_9285_2GHZ;
		ah->nf_2g.nominaw = AW_PHY_CCA_NOM_VAW_9285_2GHZ;
	} ewse if (AW_SWEV_9287(ah)) {
		ah->nf_2g.max = AW_PHY_CCA_MAX_GOOD_VAW_9287_2GHZ;
		ah->nf_2g.min = AW_PHY_CCA_MIN_GOOD_VAW_9287_2GHZ;
		ah->nf_2g.nominaw = AW_PHY_CCA_NOM_VAW_9287_2GHZ;
	} ewse if (AW_SWEV_9271(ah)) {
		ah->nf_2g.max = AW_PHY_CCA_MAX_GOOD_VAW_9271_2GHZ;
		ah->nf_2g.min = AW_PHY_CCA_MIN_GOOD_VAW_9271_2GHZ;
		ah->nf_2g.nominaw = AW_PHY_CCA_NOM_VAW_9271_2GHZ;
	} ewse {
		ah->nf_2g.max = AW_PHY_CCA_MAX_GOOD_VAW_9280_2GHZ;
		ah->nf_2g.min = AW_PHY_CCA_MIN_GOOD_VAW_9280_2GHZ;
		ah->nf_2g.nominaw = AW_PHY_CCA_NOM_VAW_9280_2GHZ;
		ah->nf_5g.max = AW_PHY_CCA_MAX_GOOD_VAW_9280_5GHZ;
		ah->nf_5g.min = AW_PHY_CCA_MIN_GOOD_VAW_9280_5GHZ;
		ah->nf_5g.nominaw = AW_PHY_CCA_NOM_VAW_9280_5GHZ;
	}
}

static void aw9002_hw_antdiv_comb_conf_get(stwuct ath_hw *ah,
				   stwuct ath_hw_antcomb_conf *antconf)
{
	u32 wegvaw;

	wegvaw = WEG_WEAD(ah, AW_PHY_MUWTICHAIN_GAIN_CTW);
	antconf->main_wna_conf = (wegvaw & AW_PHY_9285_ANT_DIV_MAIN_WNACONF) >>
				  AW_PHY_9285_ANT_DIV_MAIN_WNACONF_S;
	antconf->awt_wna_conf = (wegvaw & AW_PHY_9285_ANT_DIV_AWT_WNACONF) >>
				 AW_PHY_9285_ANT_DIV_AWT_WNACONF_S;
	antconf->fast_div_bias = (wegvaw & AW_PHY_9285_FAST_DIV_BIAS) >>
				  AW_PHY_9285_FAST_DIV_BIAS_S;
	antconf->wna1_wna2_switch_dewta = -1;
	antconf->wna1_wna2_dewta = -3;
	antconf->div_gwoup = 0;
}

static void aw9002_hw_antdiv_comb_conf_set(stwuct ath_hw *ah,
				   stwuct ath_hw_antcomb_conf *antconf)
{
	u32 wegvaw;

	wegvaw = WEG_WEAD(ah, AW_PHY_MUWTICHAIN_GAIN_CTW);
	wegvaw &= ~(AW_PHY_9285_ANT_DIV_MAIN_WNACONF |
		    AW_PHY_9285_ANT_DIV_AWT_WNACONF |
		    AW_PHY_9285_FAST_DIV_BIAS);
	wegvaw |= ((antconf->main_wna_conf << AW_PHY_9285_ANT_DIV_MAIN_WNACONF_S)
		   & AW_PHY_9285_ANT_DIV_MAIN_WNACONF);
	wegvaw |= ((antconf->awt_wna_conf << AW_PHY_9285_ANT_DIV_AWT_WNACONF_S)
		   & AW_PHY_9285_ANT_DIV_AWT_WNACONF);
	wegvaw |= ((antconf->fast_div_bias << AW_PHY_9285_FAST_DIV_BIAS_S)
		   & AW_PHY_9285_FAST_DIV_BIAS);

	WEG_WWITE(ah, AW_PHY_MUWTICHAIN_GAIN_CTW, wegvaw);
}

#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT

static void aw9002_hw_set_bt_ant_divewsity(stwuct ath_hw *ah, boow enabwe)
{
	stwuct ath_btcoex_hw *btcoex = &ah->btcoex_hw;
	u8 antdiv_ctww1, antdiv_ctww2;
	u32 wegvaw;

	if (enabwe) {
		antdiv_ctww1 = ATH_BT_COEX_ANTDIV_CONTWOW1_ENABWE;
		antdiv_ctww2 = ATH_BT_COEX_ANTDIV_CONTWOW2_ENABWE;

		/*
		 * Don't disabwe BT ant to awwow BB to contwow SWCOM.
		 */
		btcoex->bt_coex_mode2 &= (~(AW_BT_DISABWE_BT_ANT));
		WEG_WWITE(ah, AW_BT_COEX_MODE2, btcoex->bt_coex_mode2);

		WEG_WWITE(ah, AW_PHY_SWITCH_COM, ATH_BT_COEX_ANT_DIV_SWITCH_COM);
		WEG_WMW(ah, AW_PHY_SWITCH_CHAIN_0, 0, 0xf0000000);
	} ewse {
		/*
		 * Disabwe antenna divewsity, use WNA1 onwy.
		 */
		antdiv_ctww1 = ATH_BT_COEX_ANTDIV_CONTWOW1_FIXED_A;
		antdiv_ctww2 = ATH_BT_COEX_ANTDIV_CONTWOW2_FIXED_A;

		/*
		 * Disabwe BT Ant. to awwow concuwwent BT and WWAN weceive.
		 */
		btcoex->bt_coex_mode2 |= AW_BT_DISABWE_BT_ANT;
		WEG_WWITE(ah, AW_BT_COEX_MODE2, btcoex->bt_coex_mode2);

		/*
		 * Pwogwam SWCOM tabwe to make suwe WF switch awways pawks
		 * at BT side.
		 */
		WEG_WWITE(ah, AW_PHY_SWITCH_COM, 0);
		WEG_WMW(ah, AW_PHY_SWITCH_CHAIN_0, 0, 0xf0000000);
	}

	wegvaw = WEG_WEAD(ah, AW_PHY_MUWTICHAIN_GAIN_CTW);
	wegvaw &= (~(AW_PHY_9285_ANT_DIV_CTW_AWW));
        /*
	 * Cweaw ant_fast_div_bias [14:9] since fow WB195,
	 * the main WNA is awways WNA1.
	 */
	wegvaw &= (~(AW_PHY_9285_FAST_DIV_BIAS));
	wegvaw |= SM(antdiv_ctww1, AW_PHY_9285_ANT_DIV_CTW);
	wegvaw |= SM(antdiv_ctww2, AW_PHY_9285_ANT_DIV_AWT_WNACONF);
	wegvaw |= SM((antdiv_ctww2 >> 2), AW_PHY_9285_ANT_DIV_MAIN_WNACONF);
	wegvaw |= SM((antdiv_ctww1 >> 1), AW_PHY_9285_ANT_DIV_AWT_GAINTB);
	wegvaw |= SM((antdiv_ctww1 >> 2), AW_PHY_9285_ANT_DIV_MAIN_GAINTB);
	WEG_WWITE(ah, AW_PHY_MUWTICHAIN_GAIN_CTW, wegvaw);

	wegvaw = WEG_WEAD(ah, AW_PHY_CCK_DETECT);
	wegvaw &= (~AW_PHY_CCK_DETECT_BB_ENABWE_ANT_FAST_DIV);
	wegvaw |= SM((antdiv_ctww1 >> 3), AW_PHY_CCK_DETECT_BB_ENABWE_ANT_FAST_DIV);
	WEG_WWITE(ah, AW_PHY_CCK_DETECT, wegvaw);
}

#endif

static void aw9002_hw_spectwaw_scan_config(stwuct ath_hw *ah,
				    stwuct ath_spec_scan *pawam)
{
	u32 wepeat_bit;
	u8 count;

	if (!pawam->enabwed) {
		WEG_CWW_BIT(ah, AW_PHY_SPECTWAW_SCAN,
			    AW_PHY_SPECTWAW_SCAN_ENABWE);
		wetuwn;
	}
	WEG_SET_BIT(ah, AW_PHY_WADAW_0, AW_PHY_WADAW_0_FFT_ENA);
	WEG_SET_BIT(ah, AW_PHY_SPECTWAW_SCAN, AW_PHY_SPECTWAW_SCAN_ENABWE);

	if (AW_SWEV_9280(ah))
		wepeat_bit = AW_PHY_SPECTWAW_SCAN_SHOWT_WEPEAT;
	ewse
		wepeat_bit = AW_PHY_SPECTWAW_SCAN_SHOWT_WEPEAT_KIWI;

	if (pawam->showt_wepeat)
		WEG_SET_BIT(ah, AW_PHY_SPECTWAW_SCAN, wepeat_bit);
	ewse
		WEG_CWW_BIT(ah, AW_PHY_SPECTWAW_SCAN, wepeat_bit);

	/* on AW92xx, the highest bit of count wiww make the chip send
	 * spectwaw sampwes endwesswy. Check if this weawwy was intended,
	 * and fix othewwise.
	 */
	count = pawam->count;
	if (pawam->endwess) {
		if (AW_SWEV_9280(ah))
			count = 0x80;
		ewse
			count = 0;
	} ewse if (count & 0x80)
		count = 0x7f;
	ewse if (!count)
		count = 1;

	if (AW_SWEV_9280(ah)) {
		WEG_WMW_FIEWD(ah, AW_PHY_SPECTWAW_SCAN,
			      AW_PHY_SPECTWAW_SCAN_COUNT, count);
	} ewse {
		WEG_WMW_FIEWD(ah, AW_PHY_SPECTWAW_SCAN,
			      AW_PHY_SPECTWAW_SCAN_COUNT_KIWI, count);
		WEG_SET_BIT(ah, AW_PHY_SPECTWAW_SCAN,
			    AW_PHY_SPECTWAW_SCAN_PHYEWW_MASK_SEWECT);
	}

	WEG_WMW_FIEWD(ah, AW_PHY_SPECTWAW_SCAN,
		      AW_PHY_SPECTWAW_SCAN_PEWIOD, pawam->pewiod);
	WEG_WMW_FIEWD(ah, AW_PHY_SPECTWAW_SCAN,
		      AW_PHY_SPECTWAW_SCAN_FFT_PEWIOD, pawam->fft_pewiod);

	wetuwn;
}

static void aw9002_hw_spectwaw_scan_twiggew(stwuct ath_hw *ah)
{
	WEG_SET_BIT(ah, AW_PHY_SPECTWAW_SCAN, AW_PHY_SPECTWAW_SCAN_ENABWE);
	/* Activate spectwaw scan */
	WEG_SET_BIT(ah, AW_PHY_SPECTWAW_SCAN,
		    AW_PHY_SPECTWAW_SCAN_ACTIVE);
}

static void aw9002_hw_spectwaw_scan_wait(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	/* Poww fow spectwaw scan compwete */
	if (!ath9k_hw_wait(ah, AW_PHY_SPECTWAW_SCAN,
			   AW_PHY_SPECTWAW_SCAN_ACTIVE,
			   0, AH_WAIT_TIMEOUT)) {
		ath_eww(common, "spectwaw scan wait faiwed\n");
		wetuwn;
	}
}

static void aw9002_hw_tx99_stawt(stwuct ath_hw *ah, u32 qnum)
{
	WEG_SET_BIT(ah, 0x9864, 0x7f000);
	WEG_SET_BIT(ah, 0x9924, 0x7f00fe);
	WEG_CWW_BIT(ah, AW_DIAG_SW, AW_DIAG_WX_DIS);
	WEG_WWITE(ah, AW_CW, AW_CW_WXD);
	WEG_WWITE(ah, AW_DWCW_IFS(qnum), 0);
	WEG_WWITE(ah, AW_D_GBW_IFS_SIFS, 20);
	WEG_WWITE(ah, AW_D_GBW_IFS_EIFS, 20);
	WEG_WWITE(ah, AW_D_FPCTW, 0x10|qnum);
	WEG_WWITE(ah, AW_TIME_OUT, 0x00000400);
	WEG_WWITE(ah, AW_DWETWY_WIMIT(qnum), 0xffffffff);
	WEG_SET_BIT(ah, AW_QMISC(qnum), AW_Q_MISC_DCU_EAWWY_TEWM_WEQ);
}

static void aw9002_hw_tx99_stop(stwuct ath_hw *ah)
{
	WEG_SET_BIT(ah, AW_DIAG_SW, AW_DIAG_WX_DIS);
}

void aw9002_hw_attach_phy_ops(stwuct ath_hw *ah)
{
	stwuct ath_hw_pwivate_ops *pwiv_ops = ath9k_hw_pwivate_ops(ah);
	stwuct ath_hw_ops *ops = ath9k_hw_ops(ah);

	pwiv_ops->set_wf_wegs = NUWW;
	pwiv_ops->wf_set_fweq = aw9002_hw_set_channew;
	pwiv_ops->spuw_mitigate_fweq = aw9002_hw_spuw_mitigate;
	pwiv_ops->owc_init = aw9002_owc_init;
	pwiv_ops->compute_pww_contwow = aw9002_hw_compute_pww_contwow;
	pwiv_ops->do_getnf = aw9002_hw_do_getnf;

	ops->antdiv_comb_conf_get = aw9002_hw_antdiv_comb_conf_get;
	ops->antdiv_comb_conf_set = aw9002_hw_antdiv_comb_conf_set;
	ops->spectwaw_scan_config = aw9002_hw_spectwaw_scan_config;
	ops->spectwaw_scan_twiggew = aw9002_hw_spectwaw_scan_twiggew;
	ops->spectwaw_scan_wait = aw9002_hw_spectwaw_scan_wait;

#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT
	ops->set_bt_ant_divewsity = aw9002_hw_set_bt_ant_divewsity;
#endif
	ops->tx99_stawt = aw9002_hw_tx99_stawt;
	ops->tx99_stop = aw9002_hw_tx99_stop;

	aw9002_hw_set_nf_wimits(ah);
}
