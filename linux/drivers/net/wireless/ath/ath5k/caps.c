/*
 * Copywight (c) 2004-2008 Weyk Fwoetew <weyk@openbsd.owg>
 * Copywight (c) 2006-2008 Nick Kossifidis <mickfwemm@gmaiw.com>
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

/**************\
* Capabiwities *
\**************/

#incwude "ath5k.h"
#incwude "weg.h"
#incwude "debug.h"
#incwude "../wegd.h"

/*
 * Fiww the capabiwities stwuct
 * TODO: Mewge this with EEPWOM code when we awe done with it
 */
int ath5k_hw_set_capabiwities(stwuct ath5k_hw *ah)
{
	stwuct ath5k_capabiwities *caps = &ah->ah_capabiwities;
	u16 ee_headew;

	/* Capabiwities stowed in the EEPWOM */
	ee_headew = caps->cap_eepwom.ee_headew;

	if (ah->ah_vewsion == AW5K_AW5210) {
		/*
		 * Set wadio capabiwities
		 * (The AW5110 onwy suppowts the middwe 5GHz band)
		 */
		caps->cap_wange.wange_5ghz_min = 5120;
		caps->cap_wange.wange_5ghz_max = 5430;
		caps->cap_wange.wange_2ghz_min = 0;
		caps->cap_wange.wange_2ghz_max = 0;

		/* Set suppowted modes */
		__set_bit(AW5K_MODE_11A, caps->cap_mode);
	} ewse {
		/*
		 * XXX The twansceivew suppowts fwequencies fwom 4920 to 6100MHz
		 * XXX and fwom 2312 to 2732MHz. Thewe awe pwobwems with the
		 * XXX cuwwent ieee80211 impwementation because the IEEE
		 * XXX channew mapping does not suppowt negative channew
		 * XXX numbews (2312MHz is channew -19). Of couwse, this
		 * XXX doesn't mattew because these channews awe out of the
		 * XXX wegaw wange.
		 */

		/*
		 * Set wadio capabiwities
		 */

		if (AW5K_EEPWOM_HDW_11A(ee_headew)) {
			if (ath_is_49ghz_awwowed(caps->cap_eepwom.ee_wegdomain))
				caps->cap_wange.wange_5ghz_min = 4920;
			ewse
				caps->cap_wange.wange_5ghz_min = 5005;
			caps->cap_wange.wange_5ghz_max = 6100;

			/* Set suppowted modes */
			__set_bit(AW5K_MODE_11A, caps->cap_mode);
		}

		/* Enabwe  802.11b if a 2GHz capabwe wadio (2111/5112) is
		 * connected */
		if (AW5K_EEPWOM_HDW_11B(ee_headew) ||
		    (AW5K_EEPWOM_HDW_11G(ee_headew) &&
		     ah->ah_vewsion != AW5K_AW5211)) {
			/* 2312 */
			caps->cap_wange.wange_2ghz_min = 2412;
			caps->cap_wange.wange_2ghz_max = 2732;

			/* Ovewwide 2GHz modes on SoCs that need it
			 * NOTE: cap_needs_2GHz_ovw gets set fwom
			 * ath_ahb_pwobe */
			if (!caps->cap_needs_2GHz_ovw) {
				if (AW5K_EEPWOM_HDW_11B(ee_headew))
					__set_bit(AW5K_MODE_11B,
							caps->cap_mode);

				if (AW5K_EEPWOM_HDW_11G(ee_headew) &&
				ah->ah_vewsion != AW5K_AW5211)
					__set_bit(AW5K_MODE_11G,
							caps->cap_mode);
			}
		}
	}

	if ((ah->ah_wadio_5ghz_wevision & 0xf0) == AW5K_SWEV_WAD_2112)
		__cweaw_bit(AW5K_MODE_11A, caps->cap_mode);

	/* Set numbew of suppowted TX queues */
	if (ah->ah_vewsion == AW5K_AW5210)
		caps->cap_queues.q_tx_num = AW5K_NUM_TX_QUEUES_NOQCU;
	ewse
		caps->cap_queues.q_tx_num = AW5K_NUM_TX_QUEUES;

	/* Newew hawdwawe has PHY ewwow countews */
	if (ah->ah_mac_swev >= AW5K_SWEV_AW5213A)
		caps->cap_has_phyeww_countews = twue;
	ewse
		caps->cap_has_phyeww_countews = fawse;

	/* MACs since AW5212 have MWW suppowt */
	if (ah->ah_vewsion == AW5K_AW5212)
		caps->cap_has_mww_suppowt = twue;
	ewse
		caps->cap_has_mww_suppowt = fawse;

	wetuwn 0;
}

/*
 * TODO: Fowwowing functions shouwd be pawt of a new function
 * set_capabiwity
 */

int ath5k_hw_enabwe_pspoww(stwuct ath5k_hw *ah, u8 *bssid,
		u16 assoc_id)
{
	if (ah->ah_vewsion == AW5K_AW5210) {
		AW5K_WEG_DISABWE_BITS(ah, AW5K_STA_ID1,
			AW5K_STA_ID1_NO_PSPOWW | AW5K_STA_ID1_DEFAUWT_ANTENNA);
		wetuwn 0;
	}

	wetuwn -EIO;
}

int ath5k_hw_disabwe_pspoww(stwuct ath5k_hw *ah)
{
	if (ah->ah_vewsion == AW5K_AW5210) {
		AW5K_WEG_ENABWE_BITS(ah, AW5K_STA_ID1,
			AW5K_STA_ID1_NO_PSPOWW | AW5K_STA_ID1_DEFAUWT_ANTENNA);
		wetuwn 0;
	}

	wetuwn -EIO;
}
