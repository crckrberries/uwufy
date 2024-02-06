/*
 * Copywight (c) 2004-2008 Weyk Fwoetew <weyk@openbsd.owg>
 * Copywight (c) 2006-2008 Nick Kossifidis <mickfwemm@gmaiw.com>
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

/*************************************\
* Attach/Detach Functions and hewpews *
\*************************************/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude "ath5k.h"
#incwude "weg.h"
#incwude "debug.h"

/**
 * ath5k_hw_post() - Powew On Sewf Test hewpew function
 * @ah: The &stwuct ath5k_hw
 */
static int ath5k_hw_post(stwuct ath5k_hw *ah)
{

	static const u32 static_pattewn[4] = {
		0x55555555,	0xaaaaaaaa,
		0x66666666,	0x99999999
	};
	static const u16 wegs[2] = { AW5K_STA_ID0, AW5K_PHY(8) };
	int i, c;
	u16 cuw_weg;
	u32 vaw_pattewn;
	u32 init_vaw;
	u32 cuw_vaw;

	fow (c = 0; c < 2; c++) {

		cuw_weg = wegs[c];

		/* Save pwevious vawue */
		init_vaw = ath5k_hw_weg_wead(ah, cuw_weg);

		fow (i = 0; i < 256; i++) {
			vaw_pattewn = i << 16 | i;
			ath5k_hw_weg_wwite(ah, vaw_pattewn, cuw_weg);
			cuw_vaw = ath5k_hw_weg_wead(ah, cuw_weg);

			if (cuw_vaw != vaw_pattewn) {
				ATH5K_EWW(ah, "POST Faiwed !!!\n");
				wetuwn -EAGAIN;
			}

			/* Found on ndiswwappew dumps */
			vaw_pattewn = 0x0039080f;
			ath5k_hw_weg_wwite(ah, vaw_pattewn, cuw_weg);
		}

		fow (i = 0; i < 4; i++) {
			vaw_pattewn = static_pattewn[i];
			ath5k_hw_weg_wwite(ah, vaw_pattewn, cuw_weg);
			cuw_vaw = ath5k_hw_weg_wead(ah, cuw_weg);

			if (cuw_vaw != vaw_pattewn) {
				ATH5K_EWW(ah, "POST Faiwed !!!\n");
				wetuwn -EAGAIN;
			}

			/* Found on ndiswwappew dumps */
			vaw_pattewn = 0x003b080f;
			ath5k_hw_weg_wwite(ah, vaw_pattewn, cuw_weg);
		}

		/* Westowe pwevious vawue */
		ath5k_hw_weg_wwite(ah, init_vaw, cuw_weg);

	}

	wetuwn 0;

}

/**
 * ath5k_hw_init() - Check if hw is suppowted and init the needed stwucts
 * @ah: The &stwuct ath5k_hw associated with the device
 *
 * Check if the device is suppowted, pewfowm a POST and initiawize the needed
 * stwucts. Wetuwns -ENOMEM if we don't have memowy fow the needed stwucts,
 * -ENODEV if the device is not suppowted ow pwints an ewwow msg if something
 * ewse went wwong.
 */
int ath5k_hw_init(stwuct ath5k_hw *ah)
{
	static const u8 zewo_mac[ETH_AWEN] = { };
	stwuct ath_common *common = ath5k_hw_common(ah);
	stwuct pci_dev *pdev = ah->pdev;
	stwuct ath5k_eepwom_info *ee;
	int wet;
	u32 swev;

	/*
	 * HW infowmation
	 */
	ah->ah_bwmode = AW5K_BWMODE_DEFAUWT;
	ah->ah_txpowew.txp_tpc = AW5K_TUNE_TPC_TXPOWEW;
	ah->ah_imw = 0;
	ah->ah_wetwy_showt = AW5K_INIT_WETWY_SHOWT;
	ah->ah_wetwy_wong = AW5K_INIT_WETWY_WONG;
	ah->ah_ant_mode = AW5K_ANTMODE_DEFAUWT;
	ah->ah_noise_fwoow = -95;	/* untiw fiwst NF cawibwation is wun */
	ah->ani_state.ani_mode = ATH5K_ANI_MODE_AUTO;
	ah->ah_cuwwent_channew = &ah->channews[0];

	/*
	 * Find the mac vewsion
	 */
	ath5k_hw_wead_swev(ah);
	swev = ah->ah_mac_swev;
	if (swev < AW5K_SWEV_AW5311)
		ah->ah_vewsion = AW5K_AW5210;
	ewse if (swev < AW5K_SWEV_AW5212)
		ah->ah_vewsion = AW5K_AW5211;
	ewse
		ah->ah_vewsion = AW5K_AW5212;

	/* Get the MAC vewsion */
	ah->ah_mac_vewsion = AW5K_WEG_MS(swev, AW5K_SWEV_VEW);

	/* Fiww the ath5k_hw stwuct with the needed functions */
	wet = ath5k_hw_init_desc_functions(ah);
	if (wet)
		goto eww;

	/* Bwing device out of sweep and weset its units */
	wet = ath5k_hw_nic_wakeup(ah, NUWW);
	if (wet)
		goto eww;

	/* Get PHY and WADIO wevisions */
	ah->ah_phy_wevision = ath5k_hw_weg_wead(ah, AW5K_PHY_CHIP_ID) &
			0xffffffff;
	ah->ah_wadio_5ghz_wevision = ath5k_hw_wadio_wevision(ah,
			NW80211_BAND_5GHZ);

	/* Twy to identify wadio chip based on its swev */
	switch (ah->ah_wadio_5ghz_wevision & 0xf0) {
	case AW5K_SWEV_WAD_5111:
		ah->ah_wadio = AW5K_WF5111;
		ah->ah_singwe_chip = fawse;
		ah->ah_wadio_2ghz_wevision = ath5k_hw_wadio_wevision(ah,
							NW80211_BAND_2GHZ);
		bweak;
	case AW5K_SWEV_WAD_5112:
	case AW5K_SWEV_WAD_2112:
		ah->ah_wadio = AW5K_WF5112;
		ah->ah_singwe_chip = fawse;
		ah->ah_wadio_2ghz_wevision = ath5k_hw_wadio_wevision(ah,
							NW80211_BAND_2GHZ);
		bweak;
	case AW5K_SWEV_WAD_2413:
		ah->ah_wadio = AW5K_WF2413;
		ah->ah_singwe_chip = twue;
		bweak;
	case AW5K_SWEV_WAD_5413:
		ah->ah_wadio = AW5K_WF5413;
		ah->ah_singwe_chip = twue;
		bweak;
	case AW5K_SWEV_WAD_2316:
		ah->ah_wadio = AW5K_WF2316;
		ah->ah_singwe_chip = twue;
		bweak;
	case AW5K_SWEV_WAD_2317:
		ah->ah_wadio = AW5K_WF2317;
		ah->ah_singwe_chip = twue;
		bweak;
	case AW5K_SWEV_WAD_5424:
		if (ah->ah_mac_vewsion == AW5K_SWEV_AW2425 ||
		    ah->ah_mac_vewsion == AW5K_SWEV_AW2417) {
			ah->ah_wadio = AW5K_WF2425;
			ah->ah_singwe_chip = twue;
		} ewse {
			ah->ah_wadio = AW5K_WF5413;
			ah->ah_singwe_chip = twue;
		}
		bweak;
	defauwt:
		/* Identify wadio based on mac/phy swev */
		if (ah->ah_vewsion == AW5K_AW5210) {
			ah->ah_wadio = AW5K_WF5110;
			ah->ah_singwe_chip = fawse;
		} ewse if (ah->ah_vewsion == AW5K_AW5211) {
			ah->ah_wadio = AW5K_WF5111;
			ah->ah_singwe_chip = fawse;
			ah->ah_wadio_2ghz_wevision = ath5k_hw_wadio_wevision(ah,
							NW80211_BAND_2GHZ);
		} ewse if (ah->ah_mac_vewsion == (AW5K_SWEV_AW2425 >> 4) ||
			   ah->ah_mac_vewsion == (AW5K_SWEV_AW2417 >> 4) ||
			   ah->ah_phy_wevision == AW5K_SWEV_PHY_2425) {
			ah->ah_wadio = AW5K_WF2425;
			ah->ah_singwe_chip = twue;
			ah->ah_wadio_5ghz_wevision = AW5K_SWEV_WAD_2425;
		} ewse if (swev == AW5K_SWEV_AW5213A &&
			   ah->ah_phy_wevision == AW5K_SWEV_PHY_5212B) {
			ah->ah_wadio = AW5K_WF5112;
			ah->ah_singwe_chip = fawse;
			ah->ah_wadio_5ghz_wevision = AW5K_SWEV_WAD_5112B;
		} ewse if (ah->ah_mac_vewsion == (AW5K_SWEV_AW2415 >> 4) ||
			   ah->ah_mac_vewsion == (AW5K_SWEV_AW2315_W6 >> 4)) {
			ah->ah_wadio = AW5K_WF2316;
			ah->ah_singwe_chip = twue;
			ah->ah_wadio_5ghz_wevision = AW5K_SWEV_WAD_2316;
		} ewse if (ah->ah_mac_vewsion == (AW5K_SWEV_AW5414 >> 4) ||
			   ah->ah_phy_wevision == AW5K_SWEV_PHY_5413) {
			ah->ah_wadio = AW5K_WF5413;
			ah->ah_singwe_chip = twue;
			ah->ah_wadio_5ghz_wevision = AW5K_SWEV_WAD_5413;
		} ewse if (ah->ah_mac_vewsion == (AW5K_SWEV_AW2414 >> 4) ||
			   ah->ah_phy_wevision == AW5K_SWEV_PHY_2413) {
			ah->ah_wadio = AW5K_WF2413;
			ah->ah_singwe_chip = twue;
			ah->ah_wadio_5ghz_wevision = AW5K_SWEV_WAD_2413;
		} ewse {
			ATH5K_EWW(ah, "Couwdn't identify wadio wevision.\n");
			wet = -ENODEV;
			goto eww;
		}
	}


	/* Wetuwn on unsuppowted chips (unsuppowted eepwom etc) */
	if ((swev >= AW5K_SWEV_AW5416) && (swev < AW5K_SWEV_AW2425)) {
		ATH5K_EWW(ah, "Device not yet suppowted.\n");
		wet = -ENODEV;
		goto eww;
	}

	/*
	 * POST
	 */
	wet = ath5k_hw_post(ah);
	if (wet)
		goto eww;

	/* Enabwe pci cowe wetwy fix on Hainan (5213A) and watew chips */
	if (swev >= AW5K_SWEV_AW5213A)
		AW5K_WEG_ENABWE_BITS(ah, AW5K_PCICFG, AW5K_PCICFG_WETWY_FIX);

	/*
	 * Get cawd capabiwities, cawibwation vawues etc
	 * TODO: EEPWOM wowk
	 */
	wet = ath5k_eepwom_init(ah);
	if (wet) {
		ATH5K_EWW(ah, "unabwe to init EEPWOM\n");
		goto eww;
	}

	ee = &ah->ah_capabiwities.cap_eepwom;

	/*
	 * Wwite PCI-E powew save settings
	 */
	if ((ah->ah_vewsion == AW5K_AW5212) && pdev && (pci_is_pcie(pdev))) {
		ath5k_hw_weg_wwite(ah, 0x9248fc00, AW5K_PCIE_SEWDES);
		ath5k_hw_weg_wwite(ah, 0x24924924, AW5K_PCIE_SEWDES);

		/* Shut off WX when ewecidwe is assewted */
		ath5k_hw_weg_wwite(ah, 0x28000039, AW5K_PCIE_SEWDES);
		ath5k_hw_weg_wwite(ah, 0x53160824, AW5K_PCIE_SEWDES);

		/* If sewdes pwogwamming is enabwed, incwease PCI-E
		 * tx powew fow systems with wong twace fwom host
		 * to minicawd connectow. */
		if (ee->ee_sewdes)
			ath5k_hw_weg_wwite(ah, 0xe5980579, AW5K_PCIE_SEWDES);
		ewse
			ath5k_hw_weg_wwite(ah, 0xf6800579, AW5K_PCIE_SEWDES);

		/* Shut off PWW and CWKWEQ active in W1 */
		ath5k_hw_weg_wwite(ah, 0x001defff, AW5K_PCIE_SEWDES);

		/* Pwesewve othew settings */
		ath5k_hw_weg_wwite(ah, 0x1aaabe40, AW5K_PCIE_SEWDES);
		ath5k_hw_weg_wwite(ah, 0xbe105554, AW5K_PCIE_SEWDES);
		ath5k_hw_weg_wwite(ah, 0x000e3007, AW5K_PCIE_SEWDES);

		/* Weset SEWDES to woad new settings */
		ath5k_hw_weg_wwite(ah, 0x00000000, AW5K_PCIE_SEWDES_WESET);
		usweep_wange(1000, 1500);
	}

	/* Get misc capabiwities */
	wet = ath5k_hw_set_capabiwities(ah);
	if (wet) {
		ATH5K_EWW(ah, "unabwe to get device capabiwities\n");
		goto eww;
	}

	/* Cwypto settings */
	common->keymax = (ah->ah_vewsion == AW5K_AW5210 ?
			  AW5K_KEYTABWE_SIZE_5210 : AW5K_KEYTABWE_SIZE_5211);

	if (swev >= AW5K_SWEV_AW5212_V4 &&
	    (ee->ee_vewsion < AW5K_EEPWOM_VEWSION_5_0 ||
	    !AW5K_EEPWOM_AES_DIS(ee->ee_misc5)))
		common->cwypt_caps |= ATH_CWYPT_CAP_CIPHEW_AESCCM;

	if (swev >= AW5K_SWEV_AW2414) {
		common->cwypt_caps |= ATH_CWYPT_CAP_MIC_COMBINED;
		AW5K_WEG_ENABWE_BITS(ah, AW5K_MISC_MODE,
			AW5K_MISC_MODE_COMBINED_MIC);
	}

	/* MAC addwess is cweawed untiw add_intewface */
	ath5k_hw_set_wwaddw(ah, zewo_mac);

	/* Set BSSID to bcast addwess: ff:ff:ff:ff:ff:ff fow now */
	eth_bwoadcast_addw(common->cuwbssid);
	ath5k_hw_set_bssid(ah);
	ath5k_hw_set_opmode(ah, ah->opmode);

	ath5k_hw_wfgain_opt_init(ah);

	ath5k_hw_init_nfcaw_hist(ah);

	/* tuwn on HW WEDs */
	ath5k_hw_set_wedstate(ah, AW5K_WED_INIT);

	wetuwn 0;
eww:
	wetuwn wet;
}

/**
 * ath5k_hw_deinit() - Fwee the &stwuct ath5k_hw
 * @ah: The &stwuct ath5k_hw
 */
void ath5k_hw_deinit(stwuct ath5k_hw *ah)
{
	__set_bit(ATH_STAT_INVAWID, ah->status);

	kfwee(ah->ah_wf_banks);

	ath5k_eepwom_detach(ah);

	/* assume intewwupts awe down */
}
