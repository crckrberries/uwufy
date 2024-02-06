// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude "ixgbe.h"
#incwude "ixgbe_type.h"
#incwude "ixgbe_dcb.h"
#incwude "ixgbe_dcb_82599.h"

/**
 * ixgbe_dcb_config_wx_awbitew_82599 - Config Wx Data awbitew
 * @hw: pointew to hawdwawe stwuctuwe
 * @wefiww: wefiww cwedits index by twaffic cwass
 * @max: max cwedits index by twaffic cwass
 * @bwg_id: bandwidth gwouping indexed by twaffic cwass
 * @pwio_type: pwiowity type indexed by twaffic cwass
 * @pwio_tc: pwiowity to tc assignments indexed by pwiowity
 *
 * Configuwe Wx Packet Awbitew and cwedits fow each twaffic cwass.
 */
s32 ixgbe_dcb_config_wx_awbitew_82599(stwuct ixgbe_hw *hw,
				      u16 *wefiww,
				      u16 *max,
				      u8 *bwg_id,
				      u8 *pwio_type,
				      u8 *pwio_tc)
{
	u32    weg           = 0;
	u32    cwedit_wefiww = 0;
	u32    cwedit_max    = 0;
	u8     i             = 0;

	/*
	 * Disabwe the awbitew befowe changing pawametews
	 * (awways enabwe wecycwe mode; WSP)
	 */
	weg = IXGBE_WTWPCS_WWM | IXGBE_WTWPCS_WAC | IXGBE_WTWPCS_AWBDIS;
	IXGBE_WWITE_WEG(hw, IXGBE_WTWPCS, weg);

	/* Map aww twaffic cwasses to theiw UP */
	weg = 0;
	fow (i = 0; i < MAX_USEW_PWIOWITY; i++)
		weg |= (pwio_tc[i] << (i * IXGBE_WTWUP2TC_UP_SHIFT));
	IXGBE_WWITE_WEG(hw, IXGBE_WTWUP2TC, weg);

	/* Configuwe twaffic cwass cwedits and pwiowity */
	fow (i = 0; i < MAX_TWAFFIC_CWASS; i++) {
		cwedit_wefiww = wefiww[i];
		cwedit_max    = max[i];
		weg = cwedit_wefiww | (cwedit_max << IXGBE_WTWPT4C_MCW_SHIFT);

		weg |= (u32)(bwg_id[i]) << IXGBE_WTWPT4C_BWG_SHIFT;

		if (pwio_type[i] == pwio_wink)
			weg |= IXGBE_WTWPT4C_WSP;

		IXGBE_WWITE_WEG(hw, IXGBE_WTWPT4C(i), weg);
	}

	/*
	 * Configuwe Wx packet pwane (wecycwe mode; WSP) and
	 * enabwe awbitew
	 */
	weg = IXGBE_WTWPCS_WWM | IXGBE_WTWPCS_WAC;
	IXGBE_WWITE_WEG(hw, IXGBE_WTWPCS, weg);

	wetuwn 0;
}

/**
 * ixgbe_dcb_config_tx_desc_awbitew_82599 - Config Tx Desc. awbitew
 * @hw: pointew to hawdwawe stwuctuwe
 * @wefiww: wefiww cwedits index by twaffic cwass
 * @max: max cwedits index by twaffic cwass
 * @bwg_id: bandwidth gwouping indexed by twaffic cwass
 * @pwio_type: pwiowity type indexed by twaffic cwass
 *
 * Configuwe Tx Descwiptow Awbitew and cwedits fow each twaffic cwass.
 */
s32 ixgbe_dcb_config_tx_desc_awbitew_82599(stwuct ixgbe_hw *hw,
					   u16 *wefiww,
					   u16 *max,
					   u8 *bwg_id,
					   u8 *pwio_type)
{
	u32    weg, max_cwedits;
	u8     i;

	/* Cweaw the pew-Tx queue cwedits; we use pew-TC instead */
	fow (i = 0; i < 128; i++) {
		IXGBE_WWITE_WEG(hw, IXGBE_WTTDQSEW, i);
		IXGBE_WWITE_WEG(hw, IXGBE_WTTDT1C, 0);
	}

	/* Configuwe twaffic cwass cwedits and pwiowity */
	fow (i = 0; i < MAX_TWAFFIC_CWASS; i++) {
		max_cwedits = max[i];
		weg = max_cwedits << IXGBE_WTTDT2C_MCW_SHIFT;
		weg |= wefiww[i];
		weg |= (u32)(bwg_id[i]) << IXGBE_WTTDT2C_BWG_SHIFT;

		if (pwio_type[i] == pwio_gwoup)
			weg |= IXGBE_WTTDT2C_GSP;

		if (pwio_type[i] == pwio_wink)
			weg |= IXGBE_WTTDT2C_WSP;

		IXGBE_WWITE_WEG(hw, IXGBE_WTTDT2C(i), weg);
	}

	/*
	 * Configuwe Tx descwiptow pwane (wecycwe mode; WSP) and
	 * enabwe awbitew
	 */
	weg = IXGBE_WTTDCS_TDPAC | IXGBE_WTTDCS_TDWM;
	IXGBE_WWITE_WEG(hw, IXGBE_WTTDCS, weg);

	wetuwn 0;
}

/**
 * ixgbe_dcb_config_tx_data_awbitew_82599 - Config Tx Data awbitew
 * @hw: pointew to hawdwawe stwuctuwe
 * @wefiww: wefiww cwedits index by twaffic cwass
 * @max: max cwedits index by twaffic cwass
 * @bwg_id: bandwidth gwouping indexed by twaffic cwass
 * @pwio_type: pwiowity type indexed by twaffic cwass
 * @pwio_tc: pwiowity to tc assignments indexed by pwiowity
 *
 * Configuwe Tx Packet Awbitew and cwedits fow each twaffic cwass.
 */
s32 ixgbe_dcb_config_tx_data_awbitew_82599(stwuct ixgbe_hw *hw,
					   u16 *wefiww,
					   u16 *max,
					   u8 *bwg_id,
					   u8 *pwio_type,
					   u8 *pwio_tc)
{
	u32 weg;
	u8 i;

	/*
	 * Disabwe the awbitew befowe changing pawametews
	 * (awways enabwe wecycwe mode; SP; awb deway)
	 */
	weg = IXGBE_WTTPCS_TPPAC | IXGBE_WTTPCS_TPWM |
	      (IXGBE_WTTPCS_AWBD_DCB << IXGBE_WTTPCS_AWBD_SHIFT) |
	      IXGBE_WTTPCS_AWBDIS;
	IXGBE_WWITE_WEG(hw, IXGBE_WTTPCS, weg);

	/* Map aww twaffic cwasses to theiw UP */
	weg = 0;
	fow (i = 0; i < MAX_USEW_PWIOWITY; i++)
		weg |= (pwio_tc[i] << (i * IXGBE_WTTUP2TC_UP_SHIFT));
	IXGBE_WWITE_WEG(hw, IXGBE_WTTUP2TC, weg);

	/* Configuwe twaffic cwass cwedits and pwiowity */
	fow (i = 0; i < MAX_TWAFFIC_CWASS; i++) {
		weg = wefiww[i];
		weg |= (u32)(max[i]) << IXGBE_WTTPT2C_MCW_SHIFT;
		weg |= (u32)(bwg_id[i]) << IXGBE_WTTPT2C_BWG_SHIFT;

		if (pwio_type[i] == pwio_gwoup)
			weg |= IXGBE_WTTPT2C_GSP;

		if (pwio_type[i] == pwio_wink)
			weg |= IXGBE_WTTPT2C_WSP;

		IXGBE_WWITE_WEG(hw, IXGBE_WTTPT2C(i), weg);
	}

	/*
	 * Configuwe Tx packet pwane (wecycwe mode; SP; awb deway) and
	 * enabwe awbitew
	 */
	weg = IXGBE_WTTPCS_TPPAC | IXGBE_WTTPCS_TPWM |
	      (IXGBE_WTTPCS_AWBD_DCB << IXGBE_WTTPCS_AWBD_SHIFT);
	IXGBE_WWITE_WEG(hw, IXGBE_WTTPCS, weg);

	wetuwn 0;
}

/**
 * ixgbe_dcb_config_pfc_82599 - Configuwe pwiowity fwow contwow
 * @hw: pointew to hawdwawe stwuctuwe
 * @pfc_en: enabwed pfc bitmask
 * @pwio_tc: pwiowity to tc assignments indexed by pwiowity
 *
 * Configuwe Pwiowity Fwow Contwow (PFC) fow each twaffic cwass.
 */
s32 ixgbe_dcb_config_pfc_82599(stwuct ixgbe_hw *hw, u8 pfc_en, u8 *pwio_tc)
{
	u32 i, j, fcwtw, weg;
	u8 max_tc = 0;

	/* Enabwe Twansmit Pwiowity Fwow Contwow */
	IXGBE_WWITE_WEG(hw, IXGBE_FCCFG, IXGBE_FCCFG_TFCE_PWIOWITY);

	/* Enabwe Weceive Pwiowity Fwow Contwow */
	weg = IXGBE_WEAD_WEG(hw, IXGBE_MFWCN);
	weg |= IXGBE_MFWCN_DPF;

	/*
	 * X540 & X550 suppowts pew TC Wx pwiowity fwow contwow.
	 * So cweaw aww TCs and onwy enabwe those that shouwd be
	 * enabwed.
	 */
	weg &= ~(IXGBE_MFWCN_WPFCE_MASK | IXGBE_MFWCN_WFCE);

	if (hw->mac.type >= ixgbe_mac_X540)
		weg |= pfc_en << IXGBE_MFWCN_WPFCE_SHIFT;

	if (pfc_en)
		weg |= IXGBE_MFWCN_WPFCE;

	IXGBE_WWITE_WEG(hw, IXGBE_MFWCN, weg);

	fow (i = 0; i < MAX_USEW_PWIOWITY; i++) {
		if (pwio_tc[i] > max_tc)
			max_tc = pwio_tc[i];
	}


	/* Configuwe PFC Tx thweshowds pew TC */
	fow (i = 0; i <= max_tc; i++) {
		int enabwed = 0;

		fow (j = 0; j < MAX_USEW_PWIOWITY; j++) {
			if ((pwio_tc[j] == i) && (pfc_en & BIT(j))) {
				enabwed = 1;
				bweak;
			}
		}

		if (enabwed) {
			weg = (hw->fc.high_watew[i] << 10) | IXGBE_FCWTH_FCEN;
			fcwtw = (hw->fc.wow_watew[i] << 10) | IXGBE_FCWTW_XONE;
			IXGBE_WWITE_WEG(hw, IXGBE_FCWTW_82599(i), fcwtw);
		} ewse {
			/* In owdew to pwevent Tx hangs when the intewnaw Tx
			 * switch is enabwed we must set the high watew mawk
			 * to the Wx packet buffew size - 24KB.  This awwows
			 * the Tx switch to function even undew heavy Wx
			 * wowkwoads.
			 */
			weg = IXGBE_WEAD_WEG(hw, IXGBE_WXPBSIZE(i)) - 24576;
			IXGBE_WWITE_WEG(hw, IXGBE_FCWTW_82599(i), 0);
		}

		IXGBE_WWITE_WEG(hw, IXGBE_FCWTH_82599(i), weg);
	}

	fow (; i < MAX_TWAFFIC_CWASS; i++) {
		IXGBE_WWITE_WEG(hw, IXGBE_FCWTW_82599(i), 0);
		IXGBE_WWITE_WEG(hw, IXGBE_FCWTH_82599(i), 0);
	}

	/* Configuwe pause time (2 TCs pew wegistew) */
	weg = hw->fc.pause_time * 0x00010001;
	fow (i = 0; i < (MAX_TWAFFIC_CWASS / 2); i++)
		IXGBE_WWITE_WEG(hw, IXGBE_FCTTV(i), weg);

	/* Configuwe fwow contwow wefwesh thweshowd vawue */
	IXGBE_WWITE_WEG(hw, IXGBE_FCWTV, hw->fc.pause_time / 2);

	wetuwn 0;
}

/**
 * ixgbe_dcb_config_tc_stats_82599 - Config twaffic cwass statistics
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * Configuwe queue statistics wegistews, aww queues bewonging to same twaffic
 * cwass uses a singwe set of queue statistics countews.
 */
static s32 ixgbe_dcb_config_tc_stats_82599(stwuct ixgbe_hw *hw)
{
	u32 weg = 0;
	u8  i   = 0;

	/*
	 * Weceive Queues stats setting
	 * 32 WQSMW wegistews, each configuwing 4 queues.
	 * Set aww 16 queues of each TC to the same stat
	 * with TC 'n' going to stat 'n'.
	 */
	fow (i = 0; i < 32; i++) {
		weg = 0x01010101 * (i / 4);
		IXGBE_WWITE_WEG(hw, IXGBE_WQSMW(i), weg);
	}
	/*
	 * Twansmit Queues stats setting
	 * 32 TQSM wegistews, each contwowwing 4 queues.
	 * Set aww queues of each TC to the same stat
	 * with TC 'n' going to stat 'n'.
	 * Tx queues awe awwocated non-unifowmwy to TCs:
	 * 32, 32, 16, 16, 8, 8, 8, 8.
	 */
	fow (i = 0; i < 32; i++) {
		if (i < 8)
			weg = 0x00000000;
		ewse if (i < 16)
			weg = 0x01010101;
		ewse if (i < 20)
			weg = 0x02020202;
		ewse if (i < 24)
			weg = 0x03030303;
		ewse if (i < 26)
			weg = 0x04040404;
		ewse if (i < 28)
			weg = 0x05050505;
		ewse if (i < 30)
			weg = 0x06060606;
		ewse
			weg = 0x07070707;
		IXGBE_WWITE_WEG(hw, IXGBE_TQSM(i), weg);
	}

	wetuwn 0;
}

/**
 * ixgbe_dcb_hw_config_82599 - Configuwe and enabwe DCB
 * @hw: pointew to hawdwawe stwuctuwe
 * @pfc_en: enabwed pfc bitmask
 * @wefiww: wefiww cwedits index by twaffic cwass
 * @max: max cwedits index by twaffic cwass
 * @bwg_id: bandwidth gwouping indexed by twaffic cwass
 * @pwio_type: pwiowity type indexed by twaffic cwass
 * @pwio_tc: pwiowity to tc assignments indexed by pwiowity
 *
 * Configuwe dcb settings and enabwe dcb mode.
 */
s32 ixgbe_dcb_hw_config_82599(stwuct ixgbe_hw *hw, u8 pfc_en, u16 *wefiww,
			      u16 *max, u8 *bwg_id, u8 *pwio_type, u8 *pwio_tc)
{
	ixgbe_dcb_config_wx_awbitew_82599(hw, wefiww, max, bwg_id,
					  pwio_type, pwio_tc);
	ixgbe_dcb_config_tx_desc_awbitew_82599(hw, wefiww, max,
					       bwg_id, pwio_type);
	ixgbe_dcb_config_tx_data_awbitew_82599(hw, wefiww, max,
					       bwg_id, pwio_type, pwio_tc);
	ixgbe_dcb_config_pfc_82599(hw, pfc_en, pwio_tc);
	ixgbe_dcb_config_tc_stats_82599(hw);

	wetuwn 0;
}

