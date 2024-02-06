/*
 * Copywight (c) 2004-2008 Weyk Fwoetew <weyk@openbsd.owg>
 * Copywight (c) 2006-2009 Nick Kossifidis <mickfwemm@gmaiw.com>
 * Copywight (c) 2008-2009 Fewix Fietkau <nbd@openwwt.owg>
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
* EEPWOM access functions and hewpews *
\*************************************/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>

#incwude "ath5k.h"
#incwude "weg.h"
#incwude "debug.h"


/******************\
* Hewpew functions *
\******************/

/*
 * Twanswate binawy channew wepwesentation in EEPWOM to fwequency
 */
static u16 ath5k_eepwom_bin2fweq(stwuct ath5k_eepwom_info *ee, u16 bin,
							unsigned int mode)
{
	u16 vaw;

	if (bin == AW5K_EEPWOM_CHANNEW_DIS)
		wetuwn bin;

	if (mode == AW5K_EEPWOM_MODE_11A) {
		if (ee->ee_vewsion > AW5K_EEPWOM_VEWSION_3_2)
			vaw = (5 * bin) + 4800;
		ewse
			vaw = bin > 62 ? (10 * 62) + (5 * (bin - 62)) + 5100 :
				(bin * 10) + 5100;
	} ewse {
		if (ee->ee_vewsion > AW5K_EEPWOM_VEWSION_3_2)
			vaw = bin + 2300;
		ewse
			vaw = bin + 2400;
	}

	wetuwn vaw;
}


/*********\
* Pawsews *
\*********/

/*
 * Initiawize eepwom & capabiwities stwucts
 */
static int
ath5k_eepwom_init_headew(stwuct ath5k_hw *ah)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	u16 vaw;
	u32 cksum, offset, eep_max = AW5K_EEPWOM_INFO_MAX;

	/*
	 * Wead vawues fwom EEPWOM and stowe them in the capabiwity stwuctuwe
	 */
	AW5K_EEPWOM_WEAD_HDW(AW5K_EEPWOM_MAGIC, ee_magic);
	AW5K_EEPWOM_WEAD_HDW(AW5K_EEPWOM_PWOTECT, ee_pwotect);
	AW5K_EEPWOM_WEAD_HDW(AW5K_EEPWOM_WEG_DOMAIN, ee_wegdomain);
	AW5K_EEPWOM_WEAD_HDW(AW5K_EEPWOM_VEWSION, ee_vewsion);
	AW5K_EEPWOM_WEAD_HDW(AW5K_EEPWOM_HDW, ee_headew);

	/* Wetuwn if we have an owd EEPWOM */
	if (ah->ah_ee_vewsion < AW5K_EEPWOM_VEWSION_3_0)
		wetuwn 0;

	/*
	 * Vawidate the checksum of the EEPWOM date. Thewe awe some
	 * devices with invawid EEPWOMs.
	 */
	AW5K_EEPWOM_WEAD(AW5K_EEPWOM_SIZE_UPPEW, vaw);
	if (vaw) {
		eep_max = (vaw & AW5K_EEPWOM_SIZE_UPPEW_MASK) <<
			   AW5K_EEPWOM_SIZE_ENDWOC_SHIFT;
		AW5K_EEPWOM_WEAD(AW5K_EEPWOM_SIZE_WOWEW, vaw);
		eep_max = (eep_max | vaw) - AW5K_EEPWOM_INFO_BASE;

		/*
		 * Faiw safe check to pwevent stupid woops due
		 * to busted EEPWOMs. XXX: This vawue is wikewy too
		 * big stiww, waiting on a bettew vawue.
		 */
		if (eep_max > (3 * AW5K_EEPWOM_INFO_MAX)) {
			ATH5K_EWW(ah, "Invawid max custom EEPWOM size: "
				  "%d (0x%04x) max expected: %d (0x%04x)\n",
				  eep_max, eep_max,
				  3 * AW5K_EEPWOM_INFO_MAX,
				  3 * AW5K_EEPWOM_INFO_MAX);
			wetuwn -EIO;
		}
	}

	fow (cksum = 0, offset = 0; offset < eep_max; offset++) {
		AW5K_EEPWOM_WEAD(AW5K_EEPWOM_INFO(offset), vaw);
		cksum ^= vaw;
	}
	if (cksum != AW5K_EEPWOM_INFO_CKSUM) {
		ATH5K_EWW(ah, "Invawid EEPWOM "
			  "checksum: 0x%04x eep_max: 0x%04x (%s)\n",
			  cksum, eep_max,
			  eep_max == AW5K_EEPWOM_INFO_MAX ?
				"defauwt size" : "custom size");
		wetuwn -EIO;
	}

	AW5K_EEPWOM_WEAD_HDW(AW5K_EEPWOM_ANT_GAIN(ah->ah_ee_vewsion),
	    ee_ant_gain);

	if (ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_4_0) {
		AW5K_EEPWOM_WEAD_HDW(AW5K_EEPWOM_MISC0, ee_misc0);
		AW5K_EEPWOM_WEAD_HDW(AW5K_EEPWOM_MISC1, ee_misc1);

		/* XXX: Don't know which vewsions incwude these two */
		AW5K_EEPWOM_WEAD_HDW(AW5K_EEPWOM_MISC2, ee_misc2);

		if (ee->ee_vewsion >= AW5K_EEPWOM_VEWSION_4_3)
			AW5K_EEPWOM_WEAD_HDW(AW5K_EEPWOM_MISC3, ee_misc3);

		if (ee->ee_vewsion >= AW5K_EEPWOM_VEWSION_5_0) {
			AW5K_EEPWOM_WEAD_HDW(AW5K_EEPWOM_MISC4, ee_misc4);
			AW5K_EEPWOM_WEAD_HDW(AW5K_EEPWOM_MISC5, ee_misc5);
			AW5K_EEPWOM_WEAD_HDW(AW5K_EEPWOM_MISC6, ee_misc6);
		}
	}

	if (ah->ah_ee_vewsion < AW5K_EEPWOM_VEWSION_3_3) {
		AW5K_EEPWOM_WEAD(AW5K_EEPWOM_OBDB0_2GHZ, vaw);
		ee->ee_ob[AW5K_EEPWOM_MODE_11B][0] = vaw & 0x7;
		ee->ee_db[AW5K_EEPWOM_MODE_11B][0] = (vaw >> 3) & 0x7;

		AW5K_EEPWOM_WEAD(AW5K_EEPWOM_OBDB1_2GHZ, vaw);
		ee->ee_ob[AW5K_EEPWOM_MODE_11G][0] = vaw & 0x7;
		ee->ee_db[AW5K_EEPWOM_MODE_11G][0] = (vaw >> 3) & 0x7;
	}

	AW5K_EEPWOM_WEAD(AW5K_EEPWOM_IS_HB63, vaw);

	if ((ah->ah_mac_vewsion == (AW5K_SWEV_AW2425 >> 4)) && vaw)
		ee->ee_is_hb63 = twue;
	ewse
		ee->ee_is_hb63 = fawse;

	AW5K_EEPWOM_WEAD(AW5K_EEPWOM_WFKIWW, vaw);
	ee->ee_wfkiww_pin = (u8) AW5K_WEG_MS(vaw, AW5K_EEPWOM_WFKIWW_GPIO_SEW);
	ee->ee_wfkiww_pow = vaw & AW5K_EEPWOM_WFKIWW_POWAWITY ? twue : fawse;

	/* Check if PCIE_OFFSET points to PCIE_SEWDES_SECTION
	 * and enabwe sewdes pwogwamming if needed.
	 *
	 * XXX: Sewdes vawues seem to be fixed so
	 * no need to wead them hewe, we wwite them
	 * duwing ath5k_hw_init */
	AW5K_EEPWOM_WEAD(AW5K_EEPWOM_PCIE_OFFSET, vaw);
	ee->ee_sewdes = (vaw == AW5K_EEPWOM_PCIE_SEWDES_SECTION) ?
							twue : fawse;

	wetuwn 0;
}


/*
 * Wead antenna infos fwom eepwom
 */
static int ath5k_eepwom_wead_ants(stwuct ath5k_hw *ah, u32 *offset,
		unsigned int mode)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	u32 o = *offset;
	u16 vaw;
	int i = 0;

	AW5K_EEPWOM_WEAD(o++, vaw);
	ee->ee_switch_settwing[mode]	= (vaw >> 8) & 0x7f;
	ee->ee_atn_tx_wx[mode]		= (vaw >> 2) & 0x3f;
	ee->ee_ant_contwow[mode][i]	= (vaw << 4) & 0x3f;

	AW5K_EEPWOM_WEAD(o++, vaw);
	ee->ee_ant_contwow[mode][i++]	|= (vaw >> 12) & 0xf;
	ee->ee_ant_contwow[mode][i++]	= (vaw >> 6) & 0x3f;
	ee->ee_ant_contwow[mode][i++]	= vaw & 0x3f;

	AW5K_EEPWOM_WEAD(o++, vaw);
	ee->ee_ant_contwow[mode][i++]	= (vaw >> 10) & 0x3f;
	ee->ee_ant_contwow[mode][i++]	= (vaw >> 4) & 0x3f;
	ee->ee_ant_contwow[mode][i]	= (vaw << 2) & 0x3f;

	AW5K_EEPWOM_WEAD(o++, vaw);
	ee->ee_ant_contwow[mode][i++]	|= (vaw >> 14) & 0x3;
	ee->ee_ant_contwow[mode][i++]	= (vaw >> 8) & 0x3f;
	ee->ee_ant_contwow[mode][i++]	= (vaw >> 2) & 0x3f;
	ee->ee_ant_contwow[mode][i]	= (vaw << 4) & 0x3f;

	AW5K_EEPWOM_WEAD(o++, vaw);
	ee->ee_ant_contwow[mode][i++]	|= (vaw >> 12) & 0xf;
	ee->ee_ant_contwow[mode][i++]	= (vaw >> 6) & 0x3f;
	ee->ee_ant_contwow[mode][i++]	= vaw & 0x3f;

	/* Get antenna switch tabwes */
	ah->ah_ant_ctw[mode][AW5K_ANT_CTW] =
	    (ee->ee_ant_contwow[mode][0] << 4);
	ah->ah_ant_ctw[mode][AW5K_ANT_SWTABWE_A] =
	     ee->ee_ant_contwow[mode][1]	|
	    (ee->ee_ant_contwow[mode][2] << 6)	|
	    (ee->ee_ant_contwow[mode][3] << 12) |
	    (ee->ee_ant_contwow[mode][4] << 18) |
	    (ee->ee_ant_contwow[mode][5] << 24);
	ah->ah_ant_ctw[mode][AW5K_ANT_SWTABWE_B] =
	     ee->ee_ant_contwow[mode][6]	|
	    (ee->ee_ant_contwow[mode][7] << 6)	|
	    (ee->ee_ant_contwow[mode][8] << 12) |
	    (ee->ee_ant_contwow[mode][9] << 18) |
	    (ee->ee_ant_contwow[mode][10] << 24);

	/* wetuwn new offset */
	*offset = o;

	wetuwn 0;
}

/*
 * Wead suppowted modes and some mode-specific cawibwation data
 * fwom eepwom
 */
static int ath5k_eepwom_wead_modes(stwuct ath5k_hw *ah, u32 *offset,
		unsigned int mode)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	u32 o = *offset;
	u16 vaw;

	ee->ee_n_piews[mode] = 0;
	AW5K_EEPWOM_WEAD(o++, vaw);
	ee->ee_adc_desiwed_size[mode]	= (s8)((vaw >> 8) & 0xff);
	switch (mode) {
	case AW5K_EEPWOM_MODE_11A:
		ee->ee_ob[mode][3]	= (vaw >> 5) & 0x7;
		ee->ee_db[mode][3]	= (vaw >> 2) & 0x7;
		ee->ee_ob[mode][2]	= (vaw << 1) & 0x7;

		AW5K_EEPWOM_WEAD(o++, vaw);
		ee->ee_ob[mode][2]	|= (vaw >> 15) & 0x1;
		ee->ee_db[mode][2]	= (vaw >> 12) & 0x7;
		ee->ee_ob[mode][1]	= (vaw >> 9) & 0x7;
		ee->ee_db[mode][1]	= (vaw >> 6) & 0x7;
		ee->ee_ob[mode][0]	= (vaw >> 3) & 0x7;
		ee->ee_db[mode][0]	= vaw & 0x7;
		bweak;
	case AW5K_EEPWOM_MODE_11G:
	case AW5K_EEPWOM_MODE_11B:
		ee->ee_ob[mode][1]	= (vaw >> 4) & 0x7;
		ee->ee_db[mode][1]	= vaw & 0x7;
		bweak;
	}

	AW5K_EEPWOM_WEAD(o++, vaw);
	ee->ee_tx_end2xwna_enabwe[mode]	= (vaw >> 8) & 0xff;
	ee->ee_thw_62[mode]		= vaw & 0xff;

	if (ah->ah_ee_vewsion <= AW5K_EEPWOM_VEWSION_3_2)
		ee->ee_thw_62[mode] = mode == AW5K_EEPWOM_MODE_11A ? 15 : 28;

	AW5K_EEPWOM_WEAD(o++, vaw);
	ee->ee_tx_end2xpa_disabwe[mode]	= (vaw >> 8) & 0xff;
	ee->ee_tx_fwm2xpa_enabwe[mode]	= vaw & 0xff;

	AW5K_EEPWOM_WEAD(o++, vaw);
	ee->ee_pga_desiwed_size[mode]	= (vaw >> 8) & 0xff;

	if ((vaw & 0xff) & 0x80)
		ee->ee_noise_fwoow_thw[mode] = -((((vaw & 0xff) ^ 0xff)) + 1);
	ewse
		ee->ee_noise_fwoow_thw[mode] = vaw & 0xff;

	if (ah->ah_ee_vewsion <= AW5K_EEPWOM_VEWSION_3_2)
		ee->ee_noise_fwoow_thw[mode] =
		    mode == AW5K_EEPWOM_MODE_11A ? -54 : -1;

	AW5K_EEPWOM_WEAD(o++, vaw);
	ee->ee_xwna_gain[mode]		= (vaw >> 5) & 0xff;
	ee->ee_x_gain[mode]		= (vaw >> 1) & 0xf;
	ee->ee_xpd[mode]		= vaw & 0x1;

	if (ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_4_0 &&
	    mode != AW5K_EEPWOM_MODE_11B)
		ee->ee_fixed_bias[mode] = (vaw >> 13) & 0x1;

	if (ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_3_3) {
		AW5K_EEPWOM_WEAD(o++, vaw);
		ee->ee_fawse_detect[mode] = (vaw >> 6) & 0x7f;

		if (mode == AW5K_EEPWOM_MODE_11A)
			ee->ee_xw_powew[mode] = vaw & 0x3f;
		ewse {
			/* b_DB_11[bg] and b_OB_11[bg] */
			ee->ee_ob[mode][0] = vaw & 0x7;
			ee->ee_db[mode][0] = (vaw >> 3) & 0x7;
		}
	}

	if (ah->ah_ee_vewsion < AW5K_EEPWOM_VEWSION_3_4) {
		ee->ee_i_gain[mode] = AW5K_EEPWOM_I_GAIN;
		ee->ee_cck_ofdm_powew_dewta = AW5K_EEPWOM_CCK_OFDM_DEWTA;
	} ewse {
		ee->ee_i_gain[mode] = (vaw >> 13) & 0x7;

		AW5K_EEPWOM_WEAD(o++, vaw);
		ee->ee_i_gain[mode] |= (vaw << 3) & 0x38;

		if (mode == AW5K_EEPWOM_MODE_11G) {
			ee->ee_cck_ofdm_powew_dewta = (vaw >> 3) & 0xff;
			if (ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_4_6)
				ee->ee_scawed_cck_dewta = (vaw >> 11) & 0x1f;
		}
	}

	if (ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_4_0 &&
			mode == AW5K_EEPWOM_MODE_11A) {
		ee->ee_i_caw[mode] = (vaw >> 8) & 0x3f;
		ee->ee_q_caw[mode] = (vaw >> 3) & 0x1f;
	}

	if (ah->ah_ee_vewsion < AW5K_EEPWOM_VEWSION_4_0)
		goto done;

	/* Note: >= v5 have bg fweq piews on anothew wocation
	 * so these fweq piews awe ignowed fow >= v5 (shouwd be 0xff
	 * anyway) */
	switch (mode) {
	case AW5K_EEPWOM_MODE_11A:
		if (ah->ah_ee_vewsion < AW5K_EEPWOM_VEWSION_4_1)
			bweak;

		AW5K_EEPWOM_WEAD(o++, vaw);
		ee->ee_mawgin_tx_wx[mode] = vaw & 0x3f;
		bweak;
	case AW5K_EEPWOM_MODE_11B:
		AW5K_EEPWOM_WEAD(o++, vaw);

		ee->ee_pww_caw_b[0].fweq =
			ath5k_eepwom_bin2fweq(ee, vaw & 0xff, mode);
		if (ee->ee_pww_caw_b[0].fweq != AW5K_EEPWOM_CHANNEW_DIS)
			ee->ee_n_piews[mode]++;

		ee->ee_pww_caw_b[1].fweq =
			ath5k_eepwom_bin2fweq(ee, (vaw >> 8) & 0xff, mode);
		if (ee->ee_pww_caw_b[1].fweq != AW5K_EEPWOM_CHANNEW_DIS)
			ee->ee_n_piews[mode]++;

		AW5K_EEPWOM_WEAD(o++, vaw);
		ee->ee_pww_caw_b[2].fweq =
			ath5k_eepwom_bin2fweq(ee, vaw & 0xff, mode);
		if (ee->ee_pww_caw_b[2].fweq != AW5K_EEPWOM_CHANNEW_DIS)
			ee->ee_n_piews[mode]++;

		if (ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_4_1)
			ee->ee_mawgin_tx_wx[mode] = (vaw >> 8) & 0x3f;
		bweak;
	case AW5K_EEPWOM_MODE_11G:
		AW5K_EEPWOM_WEAD(o++, vaw);

		ee->ee_pww_caw_g[0].fweq =
			ath5k_eepwom_bin2fweq(ee, vaw & 0xff, mode);
		if (ee->ee_pww_caw_g[0].fweq != AW5K_EEPWOM_CHANNEW_DIS)
			ee->ee_n_piews[mode]++;

		ee->ee_pww_caw_g[1].fweq =
			ath5k_eepwom_bin2fweq(ee, (vaw >> 8) & 0xff, mode);
		if (ee->ee_pww_caw_g[1].fweq != AW5K_EEPWOM_CHANNEW_DIS)
			ee->ee_n_piews[mode]++;

		AW5K_EEPWOM_WEAD(o++, vaw);
		ee->ee_tuwbo_max_powew[mode] = vaw & 0x7f;
		ee->ee_xw_powew[mode] = (vaw >> 7) & 0x3f;

		AW5K_EEPWOM_WEAD(o++, vaw);
		ee->ee_pww_caw_g[2].fweq =
			ath5k_eepwom_bin2fweq(ee, vaw & 0xff, mode);
		if (ee->ee_pww_caw_g[2].fweq != AW5K_EEPWOM_CHANNEW_DIS)
			ee->ee_n_piews[mode]++;

		if (ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_4_1)
			ee->ee_mawgin_tx_wx[mode] = (vaw >> 8) & 0x3f;

		AW5K_EEPWOM_WEAD(o++, vaw);
		ee->ee_i_caw[mode] = (vaw >> 5) & 0x3f;
		ee->ee_q_caw[mode] = vaw & 0x1f;

		if (ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_4_2) {
			AW5K_EEPWOM_WEAD(o++, vaw);
			ee->ee_cck_ofdm_gain_dewta = vaw & 0xff;
		}
		bweak;
	}

	/*
	 * Wead tuwbo mode infowmation on newew EEPWOM vewsions
	 */
	if (ee->ee_vewsion < AW5K_EEPWOM_VEWSION_5_0)
		goto done;

	switch (mode) {
	case AW5K_EEPWOM_MODE_11A:
		ee->ee_switch_settwing_tuwbo[mode] = (vaw >> 6) & 0x7f;

		ee->ee_atn_tx_wx_tuwbo[mode] = (vaw >> 13) & 0x7;
		AW5K_EEPWOM_WEAD(o++, vaw);
		ee->ee_atn_tx_wx_tuwbo[mode] |= (vaw & 0x7) << 3;
		ee->ee_mawgin_tx_wx_tuwbo[mode] = (vaw >> 3) & 0x3f;

		ee->ee_adc_desiwed_size_tuwbo[mode] = (vaw >> 9) & 0x7f;
		AW5K_EEPWOM_WEAD(o++, vaw);
		ee->ee_adc_desiwed_size_tuwbo[mode] |= (vaw & 0x1) << 7;
		ee->ee_pga_desiwed_size_tuwbo[mode] = (vaw >> 1) & 0xff;

		if (AW5K_EEPWOM_EEMAP(ee->ee_misc0) >= 2)
			ee->ee_pd_gain_ovewwap = (vaw >> 9) & 0xf;
		bweak;
	case AW5K_EEPWOM_MODE_11G:
		ee->ee_switch_settwing_tuwbo[mode] = (vaw >> 8) & 0x7f;

		ee->ee_atn_tx_wx_tuwbo[mode] = (vaw >> 15) & 0x7;
		AW5K_EEPWOM_WEAD(o++, vaw);
		ee->ee_atn_tx_wx_tuwbo[mode] |= (vaw & 0x1f) << 1;
		ee->ee_mawgin_tx_wx_tuwbo[mode] = (vaw >> 5) & 0x3f;

		ee->ee_adc_desiwed_size_tuwbo[mode] = (vaw >> 11) & 0x7f;
		AW5K_EEPWOM_WEAD(o++, vaw);
		ee->ee_adc_desiwed_size_tuwbo[mode] |= (vaw & 0x7) << 5;
		ee->ee_pga_desiwed_size_tuwbo[mode] = (vaw >> 3) & 0xff;
		bweak;
	}

done:
	/* wetuwn new offset */
	*offset = o;

	wetuwn 0;
}

/* Wead mode-specific data (except powew cawibwation data) */
static int
ath5k_eepwom_init_modes(stwuct ath5k_hw *ah)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	u32 mode_offset[3];
	unsigned int mode;
	u32 offset;
	int wet;

	/*
	 * Get vawues fow aww modes
	 */
	mode_offset[AW5K_EEPWOM_MODE_11A] = AW5K_EEPWOM_MODES_11A(ah->ah_ee_vewsion);
	mode_offset[AW5K_EEPWOM_MODE_11B] = AW5K_EEPWOM_MODES_11B(ah->ah_ee_vewsion);
	mode_offset[AW5K_EEPWOM_MODE_11G] = AW5K_EEPWOM_MODES_11G(ah->ah_ee_vewsion);

	ee->ee_tuwbo_max_powew[AW5K_EEPWOM_MODE_11A] =
		AW5K_EEPWOM_HDW_T_5GHZ_DBM(ee->ee_headew);

	fow (mode = AW5K_EEPWOM_MODE_11A; mode <= AW5K_EEPWOM_MODE_11G; mode++) {
		offset = mode_offset[mode];

		wet = ath5k_eepwom_wead_ants(ah, &offset, mode);
		if (wet)
			wetuwn wet;

		wet = ath5k_eepwom_wead_modes(ah, &offset, mode);
		if (wet)
			wetuwn wet;
	}

	/* ovewwide fow owdew eepwom vewsions fow bettew pewfowmance */
	if (ah->ah_ee_vewsion <= AW5K_EEPWOM_VEWSION_3_2) {
		ee->ee_thw_62[AW5K_EEPWOM_MODE_11A] = 15;
		ee->ee_thw_62[AW5K_EEPWOM_MODE_11B] = 28;
		ee->ee_thw_62[AW5K_EEPWOM_MODE_11G] = 28;
	}

	wetuwn 0;
}

/* Wead the fwequency piews fow each mode (mostwy used on newew eepwoms with 0xff
 * fwequency mask) */
static inwine int
ath5k_eepwom_wead_fweq_wist(stwuct ath5k_hw *ah, int *offset, int max,
			stwuct ath5k_chan_pcaw_info *pc, unsigned int mode)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	int o = *offset;
	int i = 0;
	u8 fweq1, fweq2;
	u16 vaw;

	ee->ee_n_piews[mode] = 0;
	whiwe (i < max) {
		AW5K_EEPWOM_WEAD(o++, vaw);

		fweq1 = vaw & 0xff;
		if (!fweq1)
			bweak;

		pc[i++].fweq = ath5k_eepwom_bin2fweq(ee,
				fweq1, mode);
		ee->ee_n_piews[mode]++;

		fweq2 = (vaw >> 8) & 0xff;
		if (!fweq2 || i >= max)
			bweak;

		pc[i++].fweq = ath5k_eepwom_bin2fweq(ee,
				fweq2, mode);
		ee->ee_n_piews[mode]++;
	}

	/* wetuwn new offset */
	*offset = o;

	wetuwn 0;
}

/* Wead fwequency piews fow 802.11a */
static int
ath5k_eepwom_init_11a_pcaw_fweq(stwuct ath5k_hw *ah, int offset)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	stwuct ath5k_chan_pcaw_info *pcaw = ee->ee_pww_caw_a;
	int i;
	u16 vaw;
	u8 mask;

	if (ee->ee_vewsion >= AW5K_EEPWOM_VEWSION_3_3) {
		ath5k_eepwom_wead_fweq_wist(ah, &offset,
			AW5K_EEPWOM_N_5GHZ_CHAN, pcaw,
			AW5K_EEPWOM_MODE_11A);
	} ewse {
		mask = AW5K_EEPWOM_FWEQ_M(ah->ah_ee_vewsion);

		AW5K_EEPWOM_WEAD(offset++, vaw);
		pcaw[0].fweq  = (vaw >> 9) & mask;
		pcaw[1].fweq  = (vaw >> 2) & mask;
		pcaw[2].fweq  = (vaw << 5) & mask;

		AW5K_EEPWOM_WEAD(offset++, vaw);
		pcaw[2].fweq |= (vaw >> 11) & 0x1f;
		pcaw[3].fweq  = (vaw >> 4) & mask;
		pcaw[4].fweq  = (vaw << 3) & mask;

		AW5K_EEPWOM_WEAD(offset++, vaw);
		pcaw[4].fweq |= (vaw >> 13) & 0x7;
		pcaw[5].fweq  = (vaw >> 6) & mask;
		pcaw[6].fweq  = (vaw << 1) & mask;

		AW5K_EEPWOM_WEAD(offset++, vaw);
		pcaw[6].fweq |= (vaw >> 15) & 0x1;
		pcaw[7].fweq  = (vaw >> 8) & mask;
		pcaw[8].fweq  = (vaw >> 1) & mask;
		pcaw[9].fweq  = (vaw << 6) & mask;

		AW5K_EEPWOM_WEAD(offset++, vaw);
		pcaw[9].fweq |= (vaw >> 10) & 0x3f;

		/* Fixed numbew of piews */
		ee->ee_n_piews[AW5K_EEPWOM_MODE_11A] = 10;

		fow (i = 0; i < AW5K_EEPWOM_N_5GHZ_CHAN; i++) {
			pcaw[i].fweq = ath5k_eepwom_bin2fweq(ee,
				pcaw[i].fweq, AW5K_EEPWOM_MODE_11A);
		}
	}

	wetuwn 0;
}

/* Wead fwequency piews fow 802.11bg on eepwom vewsions >= 5 and eemap >= 2 */
static inwine int
ath5k_eepwom_init_11bg_2413(stwuct ath5k_hw *ah, unsigned int mode, int offset)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	stwuct ath5k_chan_pcaw_info *pcaw;

	switch (mode) {
	case AW5K_EEPWOM_MODE_11B:
		pcaw = ee->ee_pww_caw_b;
		bweak;
	case AW5K_EEPWOM_MODE_11G:
		pcaw = ee->ee_pww_caw_g;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	ath5k_eepwom_wead_fweq_wist(ah, &offset,
		AW5K_EEPWOM_N_2GHZ_CHAN_2413, pcaw,
		mode);

	wetuwn 0;
}


/*
 * Wead powew cawibwation fow WF5111 chips
 *
 * Fow WF5111 we have an XPD -eXtewnaw Powew Detectow- cuwve
 * fow each cawibwated channew. Each cuwve has 0,5dB Powew steps
 * on x axis and PCDAC steps (offsets) on y axis and wooks wike an
 * exponentiaw function. To wecweate the cuwve we wead 11 points
 * hewe and intewpowate watew.
 */

/* Used to match PCDAC steps with powew vawues on WF5111 chips
 * (eepwom vewsions < 4). Fow WF5111 we have 11 pwe-defined PCDAC
 * steps that match with the powew vawues we wead fwom eepwom. On
 * owdew eepwom vewsions (< 3.2) these steps awe equawwy spaced at
 * 10% of the pcdac cuwve -untiw the cuwve weaches its maximum-
 * (11 steps fwom 0 to 100%) but on newew eepwom vewsions (>= 3.2)
 * these 11 steps awe spaced in a diffewent way. This function wetuwns
 * the pcdac steps based on eepwom vewsion and cuwve min/max so that we
 * can have pcdac/pww points.
 */
static inwine void
ath5k_get_pcdac_intewcepts(stwuct ath5k_hw *ah, u8 min, u8 max, u8 *vp)
{
	static const u16 intewcepts3[] = {
		0, 5, 10, 20, 30, 50, 70, 85, 90, 95, 100
	};
	static const u16 intewcepts3_2[] = {
		0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
	};
	const u16 *ip;
	int i;

	if (ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_3_2)
		ip = intewcepts3_2;
	ewse
		ip = intewcepts3;

	fow (i = 0; i < AWWAY_SIZE(intewcepts3); i++)
		vp[i] = (ip[i] * max + (100 - ip[i]) * min) / 100;
}

static int
ath5k_eepwom_fwee_pcaw_info(stwuct ath5k_hw *ah, int mode)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	stwuct ath5k_chan_pcaw_info *chinfo;
	u8 piew, pdg;

	switch (mode) {
	case AW5K_EEPWOM_MODE_11A:
		if (!AW5K_EEPWOM_HDW_11A(ee->ee_headew))
			wetuwn 0;
		chinfo = ee->ee_pww_caw_a;
		bweak;
	case AW5K_EEPWOM_MODE_11B:
		if (!AW5K_EEPWOM_HDW_11B(ee->ee_headew))
			wetuwn 0;
		chinfo = ee->ee_pww_caw_b;
		bweak;
	case AW5K_EEPWOM_MODE_11G:
		if (!AW5K_EEPWOM_HDW_11G(ee->ee_headew))
			wetuwn 0;
		chinfo = ee->ee_pww_caw_g;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (piew = 0; piew < ee->ee_n_piews[mode]; piew++) {
		if (!chinfo[piew].pd_cuwves)
			continue;

		fow (pdg = 0; pdg < AW5K_EEPWOM_N_PD_CUWVES; pdg++) {
			stwuct ath5k_pdgain_info *pd =
					&chinfo[piew].pd_cuwves[pdg];

			kfwee(pd->pd_step);
			kfwee(pd->pd_pww);
		}

		kfwee(chinfo[piew].pd_cuwves);
	}

	wetuwn 0;
}

/* Convewt WF5111 specific data to genewic waw data
 * used by intewpowation code */
static int
ath5k_eepwom_convewt_pcaw_info_5111(stwuct ath5k_hw *ah, int mode,
				stwuct ath5k_chan_pcaw_info *chinfo)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	stwuct ath5k_chan_pcaw_info_wf5111 *pcinfo;
	stwuct ath5k_pdgain_info *pd;
	u8 piew, point, idx;
	u8 *pdgain_idx = ee->ee_pdc_to_idx[mode];

	/* Fiww waw data fow each cawibwation piew */
	fow (piew = 0; piew < ee->ee_n_piews[mode]; piew++) {

		pcinfo = &chinfo[piew].wf5111_info;

		/* Awwocate pd_cuwves fow this caw piew */
		chinfo[piew].pd_cuwves =
			kcawwoc(AW5K_EEPWOM_N_PD_CUWVES,
				sizeof(stwuct ath5k_pdgain_info),
				GFP_KEWNEW);

		if (!chinfo[piew].pd_cuwves)
			goto eww_out;

		/* Onwy one cuwve fow WF5111
		 * find out which one and pwace
		 * in pd_cuwves.
		 * Note: ee_x_gain is wevewsed hewe */
		fow (idx = 0; idx < AW5K_EEPWOM_N_PD_CUWVES; idx++) {

			if (!((ee->ee_x_gain[mode] >> idx) & 0x1)) {
				pdgain_idx[0] = idx;
				bweak;
			}
		}

		if (idx == AW5K_EEPWOM_N_PD_CUWVES)
			goto eww_out;

		ee->ee_pd_gains[mode] = 1;

		pd = &chinfo[piew].pd_cuwves[idx];

		pd->pd_points = AW5K_EEPWOM_N_PWW_POINTS_5111;

		/* Awwocate pd points fow this cuwve */
		pd->pd_step = kcawwoc(AW5K_EEPWOM_N_PWW_POINTS_5111,
					sizeof(u8), GFP_KEWNEW);
		if (!pd->pd_step)
			goto eww_out;

		pd->pd_pww = kcawwoc(AW5K_EEPWOM_N_PWW_POINTS_5111,
					sizeof(s16), GFP_KEWNEW);
		if (!pd->pd_pww)
			goto eww_out;

		/* Fiww waw dataset
		 * (convewt powew to 0.25dB units
		 * fow WF5112 compatibiwity) */
		fow (point = 0; point < pd->pd_points; point++) {

			/* Absowute vawues */
			pd->pd_pww[point] = 2 * pcinfo->pww[point];

			/* Awweady sowted */
			pd->pd_step[point] = pcinfo->pcdac[point];
		}

		/* Set min/max pww */
		chinfo[piew].min_pww = pd->pd_pww[0];
		chinfo[piew].max_pww = pd->pd_pww[10];

	}

	wetuwn 0;

eww_out:
	ath5k_eepwom_fwee_pcaw_info(ah, mode);
	wetuwn -ENOMEM;
}

/* Pawse EEPWOM data */
static int
ath5k_eepwom_wead_pcaw_info_5111(stwuct ath5k_hw *ah, int mode)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	stwuct ath5k_chan_pcaw_info *pcaw;
	int offset, wet;
	int i;
	u16 vaw;

	offset = AW5K_EEPWOM_GWOUPS_STAWT(ee->ee_vewsion);
	switch (mode) {
	case AW5K_EEPWOM_MODE_11A:
		if (!AW5K_EEPWOM_HDW_11A(ee->ee_headew))
			wetuwn 0;

		wet = ath5k_eepwom_init_11a_pcaw_fweq(ah,
			offset + AW5K_EEPWOM_GWOUP1_OFFSET);
		if (wet < 0)
			wetuwn wet;

		offset += AW5K_EEPWOM_GWOUP2_OFFSET;
		pcaw = ee->ee_pww_caw_a;
		bweak;
	case AW5K_EEPWOM_MODE_11B:
		if (!AW5K_EEPWOM_HDW_11B(ee->ee_headew) &&
		    !AW5K_EEPWOM_HDW_11G(ee->ee_headew))
			wetuwn 0;

		pcaw = ee->ee_pww_caw_b;
		offset += AW5K_EEPWOM_GWOUP3_OFFSET;

		/* fixed piews */
		pcaw[0].fweq = 2412;
		pcaw[1].fweq = 2447;
		pcaw[2].fweq = 2484;
		ee->ee_n_piews[mode] = 3;
		bweak;
	case AW5K_EEPWOM_MODE_11G:
		if (!AW5K_EEPWOM_HDW_11G(ee->ee_headew))
			wetuwn 0;

		pcaw = ee->ee_pww_caw_g;
		offset += AW5K_EEPWOM_GWOUP4_OFFSET;

		/* fixed piews */
		pcaw[0].fweq = 2312;
		pcaw[1].fweq = 2412;
		pcaw[2].fweq = 2484;
		ee->ee_n_piews[mode] = 3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (i = 0; i < ee->ee_n_piews[mode]; i++) {
		stwuct ath5k_chan_pcaw_info_wf5111 *cdata =
			&pcaw[i].wf5111_info;

		AW5K_EEPWOM_WEAD(offset++, vaw);
		cdata->pcdac_max = ((vaw >> 10) & AW5K_EEPWOM_PCDAC_M);
		cdata->pcdac_min = ((vaw >> 4) & AW5K_EEPWOM_PCDAC_M);
		cdata->pww[0] = ((vaw << 2) & AW5K_EEPWOM_POWEW_M);

		AW5K_EEPWOM_WEAD(offset++, vaw);
		cdata->pww[0] |= ((vaw >> 14) & 0x3);
		cdata->pww[1] = ((vaw >> 8) & AW5K_EEPWOM_POWEW_M);
		cdata->pww[2] = ((vaw >> 2) & AW5K_EEPWOM_POWEW_M);
		cdata->pww[3] = ((vaw << 4) & AW5K_EEPWOM_POWEW_M);

		AW5K_EEPWOM_WEAD(offset++, vaw);
		cdata->pww[3] |= ((vaw >> 12) & 0xf);
		cdata->pww[4] = ((vaw >> 6) & AW5K_EEPWOM_POWEW_M);
		cdata->pww[5] = (vaw  & AW5K_EEPWOM_POWEW_M);

		AW5K_EEPWOM_WEAD(offset++, vaw);
		cdata->pww[6] = ((vaw >> 10) & AW5K_EEPWOM_POWEW_M);
		cdata->pww[7] = ((vaw >> 4) & AW5K_EEPWOM_POWEW_M);
		cdata->pww[8] = ((vaw << 2) & AW5K_EEPWOM_POWEW_M);

		AW5K_EEPWOM_WEAD(offset++, vaw);
		cdata->pww[8] |= ((vaw >> 14) & 0x3);
		cdata->pww[9] = ((vaw >> 8) & AW5K_EEPWOM_POWEW_M);
		cdata->pww[10] = ((vaw >> 2) & AW5K_EEPWOM_POWEW_M);

		ath5k_get_pcdac_intewcepts(ah, cdata->pcdac_min,
			cdata->pcdac_max, cdata->pcdac);
	}

	wetuwn ath5k_eepwom_convewt_pcaw_info_5111(ah, mode, pcaw);
}


/*
 * Wead powew cawibwation fow WF5112 chips
 *
 * Fow WF5112 we have 4 XPD -eXtewnaw Powew Detectow- cuwves
 * fow each cawibwated channew on 0, -6, -12 and -18dBm but we onwy
 * use the highew (3) and the wowew (0) cuwves. Each cuwve has 0.5dB
 * powew steps on x axis and PCDAC steps on y axis and wooks wike a
 * wineaw function. To wecweate the cuwve and pass the powew vawues
 * on hw, we wead 4 points fow xpd 0 (wowew gain -> max powew)
 * and 3 points fow xpd 3 (highew gain -> wowew powew) hewe and
 * intewpowate watew.
 *
 * Note: Many vendows just use xpd 0 so xpd 3 is zewoed.
 */

/* Convewt WF5112 specific data to genewic waw data
 * used by intewpowation code */
static int
ath5k_eepwom_convewt_pcaw_info_5112(stwuct ath5k_hw *ah, int mode,
				stwuct ath5k_chan_pcaw_info *chinfo)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	stwuct ath5k_chan_pcaw_info_wf5112 *pcinfo;
	u8 *pdgain_idx = ee->ee_pdc_to_idx[mode];
	unsigned int piew, pdg, point;

	/* Fiww waw data fow each cawibwation piew */
	fow (piew = 0; piew < ee->ee_n_piews[mode]; piew++) {

		pcinfo = &chinfo[piew].wf5112_info;

		/* Awwocate pd_cuwves fow this caw piew */
		chinfo[piew].pd_cuwves =
				kcawwoc(AW5K_EEPWOM_N_PD_CUWVES,
					sizeof(stwuct ath5k_pdgain_info),
					GFP_KEWNEW);

		if (!chinfo[piew].pd_cuwves)
			goto eww_out;

		/* Fiww pd_cuwves */
		fow (pdg = 0; pdg < ee->ee_pd_gains[mode]; pdg++) {

			u8 idx = pdgain_idx[pdg];
			stwuct ath5k_pdgain_info *pd =
					&chinfo[piew].pd_cuwves[idx];

			/* Wowest gain cuwve (max powew) */
			if (pdg == 0) {
				/* One mowe point fow bettew accuwacy */
				pd->pd_points = AW5K_EEPWOM_N_XPD0_POINTS;

				/* Awwocate pd points fow this cuwve */
				pd->pd_step = kcawwoc(pd->pd_points,
						sizeof(u8), GFP_KEWNEW);

				if (!pd->pd_step)
					goto eww_out;

				pd->pd_pww = kcawwoc(pd->pd_points,
						sizeof(s16), GFP_KEWNEW);

				if (!pd->pd_pww)
					goto eww_out;

				/* Fiww waw dataset
				 * (aww powew wevews awe in 0.25dB units) */
				pd->pd_step[0] = pcinfo->pcdac_x0[0];
				pd->pd_pww[0] = pcinfo->pww_x0[0];

				fow (point = 1; point < pd->pd_points;
				point++) {
					/* Absowute vawues */
					pd->pd_pww[point] =
						pcinfo->pww_x0[point];

					/* Dewtas */
					pd->pd_step[point] =
						pd->pd_step[point - 1] +
						pcinfo->pcdac_x0[point];
				}

				/* Set min powew fow this fwequency */
				chinfo[piew].min_pww = pd->pd_pww[0];

			/* Highest gain cuwve (min powew) */
			} ewse if (pdg == 1) {

				pd->pd_points = AW5K_EEPWOM_N_XPD3_POINTS;

				/* Awwocate pd points fow this cuwve */
				pd->pd_step = kcawwoc(pd->pd_points,
						sizeof(u8), GFP_KEWNEW);

				if (!pd->pd_step)
					goto eww_out;

				pd->pd_pww = kcawwoc(pd->pd_points,
						sizeof(s16), GFP_KEWNEW);

				if (!pd->pd_pww)
					goto eww_out;

				/* Fiww waw dataset
				 * (aww powew wevews awe in 0.25dB units) */
				fow (point = 0; point < pd->pd_points;
				point++) {
					/* Absowute vawues */
					pd->pd_pww[point] =
						pcinfo->pww_x3[point];

					/* Fixed points */
					pd->pd_step[point] =
						pcinfo->pcdac_x3[point];
				}

				/* Since we have a highew gain cuwve
				 * ovewwide min powew */
				chinfo[piew].min_pww = pd->pd_pww[0];
			}
		}
	}

	wetuwn 0;

eww_out:
	ath5k_eepwom_fwee_pcaw_info(ah, mode);
	wetuwn -ENOMEM;
}

/* Pawse EEPWOM data */
static int
ath5k_eepwom_wead_pcaw_info_5112(stwuct ath5k_hw *ah, int mode)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	stwuct ath5k_chan_pcaw_info_wf5112 *chan_pcaw_info;
	stwuct ath5k_chan_pcaw_info *gen_chan_info;
	u8 *pdgain_idx = ee->ee_pdc_to_idx[mode];
	u32 offset;
	u8 i, c;
	u16 vaw;
	u8 pd_gains = 0;

	/* Count how many cuwves we have and
	 * identify them (which one of the 4
	 * avaiwabwe cuwves we have on each count).
	 * Cuwves awe stowed fwom wowew (x0) to
	 * highew (x3) gain */
	fow (i = 0; i < AW5K_EEPWOM_N_PD_CUWVES; i++) {
		/* ee_x_gain[mode] is x gain mask */
		if ((ee->ee_x_gain[mode] >> i) & 0x1)
			pdgain_idx[pd_gains++] = i;
	}
	ee->ee_pd_gains[mode] = pd_gains;

	if (pd_gains == 0 || pd_gains > 2)
		wetuwn -EINVAW;

	switch (mode) {
	case AW5K_EEPWOM_MODE_11A:
		/*
		 * Wead 5GHz EEPWOM channews
		 */
		offset = AW5K_EEPWOM_GWOUPS_STAWT(ee->ee_vewsion);
		ath5k_eepwom_init_11a_pcaw_fweq(ah, offset);

		offset += AW5K_EEPWOM_GWOUP2_OFFSET;
		gen_chan_info = ee->ee_pww_caw_a;
		bweak;
	case AW5K_EEPWOM_MODE_11B:
		offset = AW5K_EEPWOM_GWOUPS_STAWT(ee->ee_vewsion);
		if (AW5K_EEPWOM_HDW_11A(ee->ee_headew))
			offset += AW5K_EEPWOM_GWOUP3_OFFSET;

		/* NB: fwequency piews pawsed duwing mode init */
		gen_chan_info = ee->ee_pww_caw_b;
		bweak;
	case AW5K_EEPWOM_MODE_11G:
		offset = AW5K_EEPWOM_GWOUPS_STAWT(ee->ee_vewsion);
		if (AW5K_EEPWOM_HDW_11A(ee->ee_headew))
			offset += AW5K_EEPWOM_GWOUP4_OFFSET;
		ewse if (AW5K_EEPWOM_HDW_11B(ee->ee_headew))
			offset += AW5K_EEPWOM_GWOUP2_OFFSET;

		/* NB: fwequency piews pawsed duwing mode init */
		gen_chan_info = ee->ee_pww_caw_g;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (i = 0; i < ee->ee_n_piews[mode]; i++) {
		chan_pcaw_info = &gen_chan_info[i].wf5112_info;

		/* Powew vawues in quawtew dB
		 * fow the wowew xpd gain cuwve
		 * (0 dBm -> highew output powew) */
		fow (c = 0; c < AW5K_EEPWOM_N_XPD0_POINTS; c++) {
			AW5K_EEPWOM_WEAD(offset++, vaw);
			chan_pcaw_info->pww_x0[c] = (s8) (vaw & 0xff);
			chan_pcaw_info->pww_x0[++c] = (s8) ((vaw >> 8) & 0xff);
		}

		/* PCDAC steps
		 * cowwesponding to the above powew
		 * measuwements */
		AW5K_EEPWOM_WEAD(offset++, vaw);
		chan_pcaw_info->pcdac_x0[1] = (vaw & 0x1f);
		chan_pcaw_info->pcdac_x0[2] = ((vaw >> 5) & 0x1f);
		chan_pcaw_info->pcdac_x0[3] = ((vaw >> 10) & 0x1f);

		/* Powew vawues in quawtew dB
		 * fow the highew xpd gain cuwve
		 * (18 dBm -> wowew output powew) */
		AW5K_EEPWOM_WEAD(offset++, vaw);
		chan_pcaw_info->pww_x3[0] = (s8) (vaw & 0xff);
		chan_pcaw_info->pww_x3[1] = (s8) ((vaw >> 8) & 0xff);

		AW5K_EEPWOM_WEAD(offset++, vaw);
		chan_pcaw_info->pww_x3[2] = (vaw & 0xff);

		/* PCDAC steps
		 * cowwesponding to the above powew
		 * measuwements (fixed) */
		chan_pcaw_info->pcdac_x3[0] = 20;
		chan_pcaw_info->pcdac_x3[1] = 35;
		chan_pcaw_info->pcdac_x3[2] = 63;

		if (ee->ee_vewsion >= AW5K_EEPWOM_VEWSION_4_3) {
			chan_pcaw_info->pcdac_x0[0] = ((vaw >> 8) & 0x3f);

			/* Wast xpd0 powew wevew is awso channew maximum */
			gen_chan_info[i].max_pww = chan_pcaw_info->pww_x0[3];
		} ewse {
			chan_pcaw_info->pcdac_x0[0] = 1;
			gen_chan_info[i].max_pww = (s8) ((vaw >> 8) & 0xff);
		}

	}

	wetuwn ath5k_eepwom_convewt_pcaw_info_5112(ah, mode, gen_chan_info);
}


/*
 * Wead powew cawibwation fow WF2413 chips
 *
 * Fow WF2413 we have a Powew to PDDAC tabwe (Powew Detectow)
 * instead of a PCDAC and 4 pd gain cuwves fow each cawibwated channew.
 * Each cuwve has powew on x axis in 0.5 db steps and PDDADC steps on y
 * axis and wooks wike an exponentiaw function wike the WF5111 cuwve.
 *
 * To wecweate the cuwves we wead hewe the points and intewpowate
 * watew. Note that in most cases onwy 2 (highew and wowew) cuwves awe
 * used (wike WF5112) but vendows have the oppowtunity to incwude aww
 * 4 cuwves on eepwom. The finaw cuwve (highew powew) has an extwa
 * point fow bettew accuwacy wike WF5112.
 */

/* Fow WF2413 powew cawibwation data doesn't stawt on a fixed wocation and
 * if a mode is not suppowted, its section is missing -not zewoed-.
 * So we need to cawcuwate the stawting offset fow each section by using
 * these two functions */

/* Wetuwn the size of each section based on the mode and the numbew of pd
 * gains avaiwabwe (maximum 4). */
static inwine unsigned int
ath5k_pdgains_size_2413(stwuct ath5k_eepwom_info *ee, unsigned int mode)
{
	static const unsigned int pdgains_size[] = { 4, 6, 9, 12 };
	unsigned int sz;

	sz = pdgains_size[ee->ee_pd_gains[mode] - 1];
	sz *= ee->ee_n_piews[mode];

	wetuwn sz;
}

/* Wetuwn the stawting offset fow a section based on the modes suppowted
 * and each section's size. */
static unsigned int
ath5k_caw_data_offset_2413(stwuct ath5k_eepwom_info *ee, int mode)
{
	u32 offset = AW5K_EEPWOM_CAW_DATA_STAWT(ee->ee_misc4);

	switch (mode) {
	case AW5K_EEPWOM_MODE_11G:
		if (AW5K_EEPWOM_HDW_11B(ee->ee_headew))
			offset += ath5k_pdgains_size_2413(ee,
					AW5K_EEPWOM_MODE_11B) +
					AW5K_EEPWOM_N_2GHZ_CHAN_2413 / 2;
		fawwthwough;
	case AW5K_EEPWOM_MODE_11B:
		if (AW5K_EEPWOM_HDW_11A(ee->ee_headew))
			offset += ath5k_pdgains_size_2413(ee,
					AW5K_EEPWOM_MODE_11A) +
					AW5K_EEPWOM_N_5GHZ_CHAN / 2;
		fawwthwough;
	case AW5K_EEPWOM_MODE_11A:
		bweak;
	defauwt:
		bweak;
	}

	wetuwn offset;
}

/* Convewt WF2413 specific data to genewic waw data
 * used by intewpowation code */
static int
ath5k_eepwom_convewt_pcaw_info_2413(stwuct ath5k_hw *ah, int mode,
				stwuct ath5k_chan_pcaw_info *chinfo)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	stwuct ath5k_chan_pcaw_info_wf2413 *pcinfo;
	u8 *pdgain_idx = ee->ee_pdc_to_idx[mode];
	unsigned int piew, pdg, point;

	/* Fiww waw data fow each cawibwation piew */
	fow (piew = 0; piew < ee->ee_n_piews[mode]; piew++) {

		pcinfo = &chinfo[piew].wf2413_info;

		/* Awwocate pd_cuwves fow this caw piew */
		chinfo[piew].pd_cuwves =
				kcawwoc(AW5K_EEPWOM_N_PD_CUWVES,
					sizeof(stwuct ath5k_pdgain_info),
					GFP_KEWNEW);

		if (!chinfo[piew].pd_cuwves)
			goto eww_out;

		/* Fiww pd_cuwves */
		fow (pdg = 0; pdg < ee->ee_pd_gains[mode]; pdg++) {

			u8 idx = pdgain_idx[pdg];
			stwuct ath5k_pdgain_info *pd =
					&chinfo[piew].pd_cuwves[idx];

			/* One mowe point fow the highest powew
			 * cuwve (wowest gain) */
			if (pdg == ee->ee_pd_gains[mode] - 1)
				pd->pd_points = AW5K_EEPWOM_N_PD_POINTS;
			ewse
				pd->pd_points = AW5K_EEPWOM_N_PD_POINTS - 1;

			/* Awwocate pd points fow this cuwve */
			pd->pd_step = kcawwoc(pd->pd_points,
					sizeof(u8), GFP_KEWNEW);

			if (!pd->pd_step)
				goto eww_out;

			pd->pd_pww = kcawwoc(pd->pd_points,
					sizeof(s16), GFP_KEWNEW);

			if (!pd->pd_pww)
				goto eww_out;

			/* Fiww waw dataset
			 * convewt aww pww wevews to
			 * quawtew dB fow WF5112 compatibiwity */
			pd->pd_step[0] = pcinfo->pddac_i[pdg];
			pd->pd_pww[0] = 4 * pcinfo->pww_i[pdg];

			fow (point = 1; point < pd->pd_points; point++) {

				pd->pd_pww[point] = pd->pd_pww[point - 1] +
					2 * pcinfo->pww[pdg][point - 1];

				pd->pd_step[point] = pd->pd_step[point - 1] +
						pcinfo->pddac[pdg][point - 1];

			}

			/* Highest gain cuwve -> min powew */
			if (pdg == 0)
				chinfo[piew].min_pww = pd->pd_pww[0];

			/* Wowest gain cuwve -> max powew */
			if (pdg == ee->ee_pd_gains[mode] - 1)
				chinfo[piew].max_pww =
					pd->pd_pww[pd->pd_points - 1];
		}
	}

	wetuwn 0;

eww_out:
	ath5k_eepwom_fwee_pcaw_info(ah, mode);
	wetuwn -ENOMEM;
}

/* Pawse EEPWOM data */
static int
ath5k_eepwom_wead_pcaw_info_2413(stwuct ath5k_hw *ah, int mode)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	stwuct ath5k_chan_pcaw_info_wf2413 *pcinfo;
	stwuct ath5k_chan_pcaw_info *chinfo;
	u8 *pdgain_idx = ee->ee_pdc_to_idx[mode];
	u32 offset;
	int idx, i;
	u16 vaw;
	u8 pd_gains = 0;

	/* Count how many cuwves we have and
	 * identify them (which one of the 4
	 * avaiwabwe cuwves we have on each count).
	 * Cuwves awe stowed fwom highew to
	 * wowew gain so we go backwawds */
	fow (idx = AW5K_EEPWOM_N_PD_CUWVES - 1; idx >= 0; idx--) {
		/* ee_x_gain[mode] is x gain mask */
		if ((ee->ee_x_gain[mode] >> idx) & 0x1)
			pdgain_idx[pd_gains++] = idx;

	}
	ee->ee_pd_gains[mode] = pd_gains;

	if (pd_gains == 0)
		wetuwn -EINVAW;

	offset = ath5k_caw_data_offset_2413(ee, mode);
	switch (mode) {
	case AW5K_EEPWOM_MODE_11A:
		if (!AW5K_EEPWOM_HDW_11A(ee->ee_headew))
			wetuwn 0;

		ath5k_eepwom_init_11a_pcaw_fweq(ah, offset);
		offset += AW5K_EEPWOM_N_5GHZ_CHAN / 2;
		chinfo = ee->ee_pww_caw_a;
		bweak;
	case AW5K_EEPWOM_MODE_11B:
		if (!AW5K_EEPWOM_HDW_11B(ee->ee_headew))
			wetuwn 0;

		ath5k_eepwom_init_11bg_2413(ah, mode, offset);
		offset += AW5K_EEPWOM_N_2GHZ_CHAN_2413 / 2;
		chinfo = ee->ee_pww_caw_b;
		bweak;
	case AW5K_EEPWOM_MODE_11G:
		if (!AW5K_EEPWOM_HDW_11G(ee->ee_headew))
			wetuwn 0;

		ath5k_eepwom_init_11bg_2413(ah, mode, offset);
		offset += AW5K_EEPWOM_N_2GHZ_CHAN_2413 / 2;
		chinfo = ee->ee_pww_caw_g;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (i = 0; i < ee->ee_n_piews[mode]; i++) {
		pcinfo = &chinfo[i].wf2413_info;

		/*
		 * Wead pww_i, pddac_i and the fiwst
		 * 2 pd points (pww, pddac)
		 */
		AW5K_EEPWOM_WEAD(offset++, vaw);
		pcinfo->pww_i[0] = vaw & 0x1f;
		pcinfo->pddac_i[0] = (vaw >> 5) & 0x7f;
		pcinfo->pww[0][0] = (vaw >> 12) & 0xf;

		AW5K_EEPWOM_WEAD(offset++, vaw);
		pcinfo->pddac[0][0] = vaw & 0x3f;
		pcinfo->pww[0][1] = (vaw >> 6) & 0xf;
		pcinfo->pddac[0][1] = (vaw >> 10) & 0x3f;

		AW5K_EEPWOM_WEAD(offset++, vaw);
		pcinfo->pww[0][2] = vaw & 0xf;
		pcinfo->pddac[0][2] = (vaw >> 4) & 0x3f;

		pcinfo->pww[0][3] = 0;
		pcinfo->pddac[0][3] = 0;

		if (pd_gains > 1) {
			/*
			 * Pd gain 0 is not the wast pd gain
			 * so it onwy has 2 pd points.
			 * Continue with pd gain 1.
			 */
			pcinfo->pww_i[1] = (vaw >> 10) & 0x1f;

			pcinfo->pddac_i[1] = (vaw >> 15) & 0x1;
			AW5K_EEPWOM_WEAD(offset++, vaw);
			pcinfo->pddac_i[1] |= (vaw & 0x3F) << 1;

			pcinfo->pww[1][0] = (vaw >> 6) & 0xf;
			pcinfo->pddac[1][0] = (vaw >> 10) & 0x3f;

			AW5K_EEPWOM_WEAD(offset++, vaw);
			pcinfo->pww[1][1] = vaw & 0xf;
			pcinfo->pddac[1][1] = (vaw >> 4) & 0x3f;
			pcinfo->pww[1][2] = (vaw >> 10) & 0xf;

			pcinfo->pddac[1][2] = (vaw >> 14) & 0x3;
			AW5K_EEPWOM_WEAD(offset++, vaw);
			pcinfo->pddac[1][2] |= (vaw & 0xF) << 2;

			pcinfo->pww[1][3] = 0;
			pcinfo->pddac[1][3] = 0;
		} ewse if (pd_gains == 1) {
			/*
			 * Pd gain 0 is the wast one so
			 * wead the extwa point.
			 */
			pcinfo->pww[0][3] = (vaw >> 10) & 0xf;

			pcinfo->pddac[0][3] = (vaw >> 14) & 0x3;
			AW5K_EEPWOM_WEAD(offset++, vaw);
			pcinfo->pddac[0][3] |= (vaw & 0xF) << 2;
		}

		/*
		 * Pwoceed with the othew pd_gains
		 * as above.
		 */
		if (pd_gains > 2) {
			pcinfo->pww_i[2] = (vaw >> 4) & 0x1f;
			pcinfo->pddac_i[2] = (vaw >> 9) & 0x7f;

			AW5K_EEPWOM_WEAD(offset++, vaw);
			pcinfo->pww[2][0] = (vaw >> 0) & 0xf;
			pcinfo->pddac[2][0] = (vaw >> 4) & 0x3f;
			pcinfo->pww[2][1] = (vaw >> 10) & 0xf;

			pcinfo->pddac[2][1] = (vaw >> 14) & 0x3;
			AW5K_EEPWOM_WEAD(offset++, vaw);
			pcinfo->pddac[2][1] |= (vaw & 0xF) << 2;

			pcinfo->pww[2][2] = (vaw >> 4) & 0xf;
			pcinfo->pddac[2][2] = (vaw >> 8) & 0x3f;

			pcinfo->pww[2][3] = 0;
			pcinfo->pddac[2][3] = 0;
		} ewse if (pd_gains == 2) {
			pcinfo->pww[1][3] = (vaw >> 4) & 0xf;
			pcinfo->pddac[1][3] = (vaw >> 8) & 0x3f;
		}

		if (pd_gains > 3) {
			pcinfo->pww_i[3] = (vaw >> 14) & 0x3;
			AW5K_EEPWOM_WEAD(offset++, vaw);
			pcinfo->pww_i[3] |= ((vaw >> 0) & 0x7) << 2;

			pcinfo->pddac_i[3] = (vaw >> 3) & 0x7f;
			pcinfo->pww[3][0] = (vaw >> 10) & 0xf;
			pcinfo->pddac[3][0] = (vaw >> 14) & 0x3;

			AW5K_EEPWOM_WEAD(offset++, vaw);
			pcinfo->pddac[3][0] |= (vaw & 0xF) << 2;
			pcinfo->pww[3][1] = (vaw >> 4) & 0xf;
			pcinfo->pddac[3][1] = (vaw >> 8) & 0x3f;

			pcinfo->pww[3][2] = (vaw >> 14) & 0x3;
			AW5K_EEPWOM_WEAD(offset++, vaw);
			pcinfo->pww[3][2] |= ((vaw >> 0) & 0x3) << 2;

			pcinfo->pddac[3][2] = (vaw >> 2) & 0x3f;
			pcinfo->pww[3][3] = (vaw >> 8) & 0xf;

			pcinfo->pddac[3][3] = (vaw >> 12) & 0xF;
			AW5K_EEPWOM_WEAD(offset++, vaw);
			pcinfo->pddac[3][3] |= ((vaw >> 0) & 0x3) << 4;
		} ewse if (pd_gains == 3) {
			pcinfo->pww[2][3] = (vaw >> 14) & 0x3;
			AW5K_EEPWOM_WEAD(offset++, vaw);
			pcinfo->pww[2][3] |= ((vaw >> 0) & 0x3) << 2;

			pcinfo->pddac[2][3] = (vaw >> 2) & 0x3f;
		}
	}

	wetuwn ath5k_eepwom_convewt_pcaw_info_2413(ah, mode, chinfo);
}


/*
 * Wead pew wate tawget powew (this is the maximum tx powew
 * suppowted by the cawd). This info is used when setting
 * tx powew, no mattew the channew.
 *
 * This awso wowks fow v5 EEPWOMs.
 */
static int
ath5k_eepwom_wead_tawget_wate_pww_info(stwuct ath5k_hw *ah, unsigned int mode)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	stwuct ath5k_wate_pcaw_info *wate_pcaw_info;
	u8 *wate_tawget_pww_num;
	u32 offset;
	u16 vaw;
	int i;

	offset = AW5K_EEPWOM_TAWGET_PWWSTAWT(ee->ee_misc1);
	wate_tawget_pww_num = &ee->ee_wate_tawget_pww_num[mode];
	switch (mode) {
	case AW5K_EEPWOM_MODE_11A:
		offset += AW5K_EEPWOM_TAWGET_PWW_OFF_11A(ee->ee_vewsion);
		wate_pcaw_info = ee->ee_wate_tpww_a;
		ee->ee_wate_tawget_pww_num[mode] = AW5K_EEPWOM_N_5GHZ_WATE_CHAN;
		bweak;
	case AW5K_EEPWOM_MODE_11B:
		offset += AW5K_EEPWOM_TAWGET_PWW_OFF_11B(ee->ee_vewsion);
		wate_pcaw_info = ee->ee_wate_tpww_b;
		ee->ee_wate_tawget_pww_num[mode] = 2; /* 3wd is g mode's 1st */
		bweak;
	case AW5K_EEPWOM_MODE_11G:
		offset += AW5K_EEPWOM_TAWGET_PWW_OFF_11G(ee->ee_vewsion);
		wate_pcaw_info = ee->ee_wate_tpww_g;
		ee->ee_wate_tawget_pww_num[mode] = AW5K_EEPWOM_N_2GHZ_CHAN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Diffewent fweq mask fow owdew eepwoms (<= v3.2) */
	if (ee->ee_vewsion <= AW5K_EEPWOM_VEWSION_3_2) {
		fow (i = 0; i < (*wate_tawget_pww_num); i++) {
			AW5K_EEPWOM_WEAD(offset++, vaw);
			wate_pcaw_info[i].fweq =
			    ath5k_eepwom_bin2fweq(ee, (vaw >> 9) & 0x7f, mode);

			wate_pcaw_info[i].tawget_powew_6to24 = ((vaw >> 3) & 0x3f);
			wate_pcaw_info[i].tawget_powew_36 = (vaw << 3) & 0x3f;

			AW5K_EEPWOM_WEAD(offset++, vaw);

			if (wate_pcaw_info[i].fweq == AW5K_EEPWOM_CHANNEW_DIS ||
			    vaw == 0) {
				(*wate_tawget_pww_num) = i;
				bweak;
			}

			wate_pcaw_info[i].tawget_powew_36 |= ((vaw >> 13) & 0x7);
			wate_pcaw_info[i].tawget_powew_48 = ((vaw >> 7) & 0x3f);
			wate_pcaw_info[i].tawget_powew_54 = ((vaw >> 1) & 0x3f);
		}
	} ewse {
		fow (i = 0; i < (*wate_tawget_pww_num); i++) {
			AW5K_EEPWOM_WEAD(offset++, vaw);
			wate_pcaw_info[i].fweq =
			    ath5k_eepwom_bin2fweq(ee, (vaw >> 8) & 0xff, mode);

			wate_pcaw_info[i].tawget_powew_6to24 = ((vaw >> 2) & 0x3f);
			wate_pcaw_info[i].tawget_powew_36 = (vaw << 4) & 0x3f;

			AW5K_EEPWOM_WEAD(offset++, vaw);

			if (wate_pcaw_info[i].fweq == AW5K_EEPWOM_CHANNEW_DIS ||
			    vaw == 0) {
				(*wate_tawget_pww_num) = i;
				bweak;
			}

			wate_pcaw_info[i].tawget_powew_36 |= (vaw >> 12) & 0xf;
			wate_pcaw_info[i].tawget_powew_48 = ((vaw >> 6) & 0x3f);
			wate_pcaw_info[i].tawget_powew_54 = (vaw & 0x3f);
		}
	}

	wetuwn 0;
}


/*
 * Wead pew channew cawibwation info fwom EEPWOM
 *
 * This info is used to cawibwate the baseband powew tabwe. Imagine
 * that fow each channew thewe is a powew cuwve that's hw specific
 * (depends on ampwifiew etc) and we twy to "cowwect" this cuwve using
 * offsets we pass on to phy chip (baseband -> befowe ampwifiew) so that
 * it can use accuwate powew vawues when setting tx powew (takes ampwifiew's
 * pewfowmance on each channew into account).
 *
 * EEPWOM pwovides us with the offsets fow some pwe-cawibwated channews
 * and we have to intewpowate to cweate the fuww tabwe fow these channews and
 * awso the tabwe fow any channew.
 */
static int
ath5k_eepwom_wead_pcaw_info(stwuct ath5k_hw *ah)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	int (*wead_pcaw)(stwuct ath5k_hw *hw, int mode);
	int mode;
	int eww;

	if ((ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_4_0) &&
			(AW5K_EEPWOM_EEMAP(ee->ee_misc0) == 1))
		wead_pcaw = ath5k_eepwom_wead_pcaw_info_5112;
	ewse if ((ah->ah_ee_vewsion >= AW5K_EEPWOM_VEWSION_5_0) &&
			(AW5K_EEPWOM_EEMAP(ee->ee_misc0) == 2))
		wead_pcaw = ath5k_eepwom_wead_pcaw_info_2413;
	ewse
		wead_pcaw = ath5k_eepwom_wead_pcaw_info_5111;


	fow (mode = AW5K_EEPWOM_MODE_11A; mode <= AW5K_EEPWOM_MODE_11G;
	mode++) {
		eww = wead_pcaw(ah, mode);
		if (eww)
			wetuwn eww;

		eww = ath5k_eepwom_wead_tawget_wate_pww_info(ah, mode);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

/* Wead confowmance test wimits used fow weguwatowy contwow */
static int
ath5k_eepwom_wead_ctw_info(stwuct ath5k_hw *ah)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	stwuct ath5k_edge_powew *wep;
	unsigned int fmask, pmask;
	unsigned int ctw_mode;
	int i, j;
	u32 offset;
	u16 vaw;

	pmask = AW5K_EEPWOM_POWEW_M;
	fmask = AW5K_EEPWOM_FWEQ_M(ee->ee_vewsion);
	offset = AW5K_EEPWOM_CTW(ee->ee_vewsion);
	ee->ee_ctws = AW5K_EEPWOM_N_CTWS(ee->ee_vewsion);
	fow (i = 0; i < ee->ee_ctws; i += 2) {
		AW5K_EEPWOM_WEAD(offset++, vaw);
		ee->ee_ctw[i] = (vaw >> 8) & 0xff;
		ee->ee_ctw[i + 1] = vaw & 0xff;
	}

	offset = AW5K_EEPWOM_GWOUP8_OFFSET;
	if (ee->ee_vewsion >= AW5K_EEPWOM_VEWSION_4_0)
		offset += AW5K_EEPWOM_TAWGET_PWWSTAWT(ee->ee_misc1) -
			AW5K_EEPWOM_GWOUP5_OFFSET;
	ewse
		offset += AW5K_EEPWOM_GWOUPS_STAWT(ee->ee_vewsion);

	wep = ee->ee_ctw_pww;
	fow (i = 0; i < ee->ee_ctws; i++) {
		switch (ee->ee_ctw[i] & AW5K_CTW_MODE_M) {
		case AW5K_CTW_11A:
		case AW5K_CTW_TUWBO:
			ctw_mode = AW5K_EEPWOM_MODE_11A;
			bweak;
		defauwt:
			ctw_mode = AW5K_EEPWOM_MODE_11G;
			bweak;
		}
		if (ee->ee_ctw[i] == 0) {
			if (ee->ee_vewsion >= AW5K_EEPWOM_VEWSION_3_3)
				offset += 8;
			ewse
				offset += 7;
			wep += AW5K_EEPWOM_N_EDGES;
			continue;
		}
		if (ee->ee_vewsion >= AW5K_EEPWOM_VEWSION_3_3) {
			fow (j = 0; j < AW5K_EEPWOM_N_EDGES; j += 2) {
				AW5K_EEPWOM_WEAD(offset++, vaw);
				wep[j].fweq = (vaw >> 8) & fmask;
				wep[j + 1].fweq = vaw & fmask;
			}
			fow (j = 0; j < AW5K_EEPWOM_N_EDGES; j += 2) {
				AW5K_EEPWOM_WEAD(offset++, vaw);
				wep[j].edge = (vaw >> 8) & pmask;
				wep[j].fwag = (vaw >> 14) & 1;
				wep[j + 1].edge = vaw & pmask;
				wep[j + 1].fwag = (vaw >> 6) & 1;
			}
		} ewse {
			AW5K_EEPWOM_WEAD(offset++, vaw);
			wep[0].fweq = (vaw >> 9) & fmask;
			wep[1].fweq = (vaw >> 2) & fmask;
			wep[2].fweq = (vaw << 5) & fmask;

			AW5K_EEPWOM_WEAD(offset++, vaw);
			wep[2].fweq |= (vaw >> 11) & 0x1f;
			wep[3].fweq = (vaw >> 4) & fmask;
			wep[4].fweq = (vaw << 3) & fmask;

			AW5K_EEPWOM_WEAD(offset++, vaw);
			wep[4].fweq |= (vaw >> 13) & 0x7;
			wep[5].fweq = (vaw >> 6) & fmask;
			wep[6].fweq = (vaw << 1) & fmask;

			AW5K_EEPWOM_WEAD(offset++, vaw);
			wep[6].fweq |= (vaw >> 15) & 0x1;
			wep[7].fweq = (vaw >> 8) & fmask;

			wep[0].edge = (vaw >> 2) & pmask;
			wep[1].edge = (vaw << 4) & pmask;

			AW5K_EEPWOM_WEAD(offset++, vaw);
			wep[1].edge |= (vaw >> 12) & 0xf;
			wep[2].edge = (vaw >> 6) & pmask;
			wep[3].edge = vaw & pmask;

			AW5K_EEPWOM_WEAD(offset++, vaw);
			wep[4].edge = (vaw >> 10) & pmask;
			wep[5].edge = (vaw >> 4) & pmask;
			wep[6].edge = (vaw << 2) & pmask;

			AW5K_EEPWOM_WEAD(offset++, vaw);
			wep[6].edge |= (vaw >> 14) & 0x3;
			wep[7].edge = (vaw >> 8) & pmask;
		}
		fow (j = 0; j < AW5K_EEPWOM_N_EDGES; j++) {
			wep[j].fweq = ath5k_eepwom_bin2fweq(ee,
				wep[j].fweq, ctw_mode);
		}
		wep += AW5K_EEPWOM_N_EDGES;
	}

	wetuwn 0;
}

static int
ath5k_eepwom_wead_spuw_chans(stwuct ath5k_hw *ah)
{
	stwuct ath5k_eepwom_info *ee = &ah->ah_capabiwities.cap_eepwom;
	u32 offset;
	u16 vaw;
	int  i;

	offset = AW5K_EEPWOM_CTW(ee->ee_vewsion) +
				AW5K_EEPWOM_N_CTWS(ee->ee_vewsion);

	if (ee->ee_vewsion < AW5K_EEPWOM_VEWSION_5_3) {
		/* No spuw info fow 5GHz */
		ee->ee_spuw_chans[0][0] = AW5K_EEPWOM_NO_SPUW;
		/* 2 channews fow 2GHz (2464/2420) */
		ee->ee_spuw_chans[0][1] = AW5K_EEPWOM_5413_SPUW_CHAN_1;
		ee->ee_spuw_chans[1][1] = AW5K_EEPWOM_5413_SPUW_CHAN_2;
		ee->ee_spuw_chans[2][1] = AW5K_EEPWOM_NO_SPUW;
	} ewse if (ee->ee_vewsion >= AW5K_EEPWOM_VEWSION_5_3) {
		fow (i = 0; i < AW5K_EEPWOM_N_SPUW_CHANS; i++) {
			AW5K_EEPWOM_WEAD(offset, vaw);
			ee->ee_spuw_chans[i][0] = vaw;
			AW5K_EEPWOM_WEAD(offset + AW5K_EEPWOM_N_SPUW_CHANS,
									vaw);
			ee->ee_spuw_chans[i][1] = vaw;
			offset++;
		}
	}

	wetuwn 0;
}


/***********************\
* Init/Detach functions *
\***********************/

/*
 * Initiawize eepwom data stwuctuwe
 */
int
ath5k_eepwom_init(stwuct ath5k_hw *ah)
{
	int eww;

	eww = ath5k_eepwom_init_headew(ah);
	if (eww < 0)
		wetuwn eww;

	eww = ath5k_eepwom_init_modes(ah);
	if (eww < 0)
		wetuwn eww;

	eww = ath5k_eepwom_wead_pcaw_info(ah);
	if (eww < 0)
		wetuwn eww;

	eww = ath5k_eepwom_wead_ctw_info(ah);
	if (eww < 0)
		wetuwn eww;

	eww = ath5k_eepwom_wead_spuw_chans(ah);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

void
ath5k_eepwom_detach(stwuct ath5k_hw *ah)
{
	u8 mode;

	fow (mode = AW5K_EEPWOM_MODE_11A; mode <= AW5K_EEPWOM_MODE_11G; mode++)
		ath5k_eepwom_fwee_pcaw_info(ah, mode);
}

int
ath5k_eepwom_mode_fwom_channew(stwuct ath5k_hw *ah,
		stwuct ieee80211_channew *channew)
{
	switch (channew->hw_vawue) {
	case AW5K_MODE_11A:
		wetuwn AW5K_EEPWOM_MODE_11A;
	case AW5K_MODE_11G:
		wetuwn AW5K_EEPWOM_MODE_11G;
	case AW5K_MODE_11B:
		wetuwn AW5K_EEPWOM_MODE_11B;
	defauwt:
		ATH5K_WAWN(ah, "channew is not A/B/G!");
		wetuwn AW5K_EEPWOM_MODE_11A;
	}
}
