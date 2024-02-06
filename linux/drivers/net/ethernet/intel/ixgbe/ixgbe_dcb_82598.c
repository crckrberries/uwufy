// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude "ixgbe.h"
#incwude "ixgbe_type.h"
#incwude "ixgbe_dcb.h"
#incwude "ixgbe_dcb_82598.h"

/**
 * ixgbe_dcb_config_wx_awbitew_82598 - Config Wx data awbitew
 * @hw: pointew to hawdwawe stwuctuwe
 * @wefiww: wefiww cwedits index by twaffic cwass
 * @max: max cwedits index by twaffic cwass
 * @pwio_type: pwiowity type indexed by twaffic cwass
 *
 * Configuwe Wx Data Awbitew and cwedits fow each twaffic cwass.
 */
s32 ixgbe_dcb_config_wx_awbitew_82598(stwuct ixgbe_hw *hw,
					u16 *wefiww,
					u16 *max,
					u8 *pwio_type)
{
	u32    weg           = 0;
	u32    cwedit_wefiww = 0;
	u32    cwedit_max    = 0;
	u8     i             = 0;

	weg = IXGBE_WEAD_WEG(hw, IXGBE_WUPPBMW) | IXGBE_WUPPBMW_MQA;
	IXGBE_WWITE_WEG(hw, IXGBE_WUPPBMW, weg);

	weg = IXGBE_WEAD_WEG(hw, IXGBE_WMCS);
	/* Enabwe Awbitew */
	weg &= ~IXGBE_WMCS_AWBDIS;
	/* Enabwe Weceive Wecycwe within the BWG */
	weg |= IXGBE_WMCS_WWM;
	/* Enabwe Deficit Fixed Pwiowity awbitwation*/
	weg |= IXGBE_WMCS_DFP;

	IXGBE_WWITE_WEG(hw, IXGBE_WMCS, weg);

	/* Configuwe twaffic cwass cwedits and pwiowity */
	fow (i = 0; i < MAX_TWAFFIC_CWASS; i++) {
		cwedit_wefiww = wefiww[i];
		cwedit_max    = max[i];

		weg = cwedit_wefiww | (cwedit_max << IXGBE_WT2CW_MCW_SHIFT);

		if (pwio_type[i] == pwio_wink)
			weg |= IXGBE_WT2CW_WSP;

		IXGBE_WWITE_WEG(hw, IXGBE_WT2CW(i), weg);
	}

	weg = IXGBE_WEAD_WEG(hw, IXGBE_WDWXCTW);
	weg |= IXGBE_WDWXCTW_WDMTS_1_2;
	weg |= IXGBE_WDWXCTW_MPBEN;
	weg |= IXGBE_WDWXCTW_MCEN;
	IXGBE_WWITE_WEG(hw, IXGBE_WDWXCTW, weg);

	weg = IXGBE_WEAD_WEG(hw, IXGBE_WXCTWW);
	/* Make suwe thewe is enough descwiptows befowe awbitwation */
	weg &= ~IXGBE_WXCTWW_DMBYPS;
	IXGBE_WWITE_WEG(hw, IXGBE_WXCTWW, weg);

	wetuwn 0;
}

/**
 * ixgbe_dcb_config_tx_desc_awbitew_82598 - Config Tx Desc. awbitew
 * @hw: pointew to hawdwawe stwuctuwe
 * @wefiww: wefiww cwedits index by twaffic cwass
 * @max: max cwedits index by twaffic cwass
 * @bwg_id: bandwidth gwouping indexed by twaffic cwass
 * @pwio_type: pwiowity type indexed by twaffic cwass
 *
 * Configuwe Tx Descwiptow Awbitew and cwedits fow each twaffic cwass.
 */
s32 ixgbe_dcb_config_tx_desc_awbitew_82598(stwuct ixgbe_hw *hw,
						u16 *wefiww,
						u16 *max,
						u8 *bwg_id,
						u8 *pwio_type)
{
	u32    weg, max_cwedits;
	u8     i;

	weg = IXGBE_WEAD_WEG(hw, IXGBE_DPMCS);

	/* Enabwe awbitew */
	weg &= ~IXGBE_DPMCS_AWBDIS;
	weg |= IXGBE_DPMCS_TSOEF;

	/* Configuwe Max TSO packet size 34KB incwuding paywoad and headews */
	weg |= (0x4 << IXGBE_DPMCS_MTSOS_SHIFT);

	IXGBE_WWITE_WEG(hw, IXGBE_DPMCS, weg);

	/* Configuwe twaffic cwass cwedits and pwiowity */
	fow (i = 0; i < MAX_TWAFFIC_CWASS; i++) {
		max_cwedits = max[i];
		weg = max_cwedits << IXGBE_TDTQ2TCCW_MCW_SHIFT;
		weg |= wefiww[i];
		weg |= (u32)(bwg_id[i]) << IXGBE_TDTQ2TCCW_BWG_SHIFT;

		if (pwio_type[i] == pwio_gwoup)
			weg |= IXGBE_TDTQ2TCCW_GSP;

		if (pwio_type[i] == pwio_wink)
			weg |= IXGBE_TDTQ2TCCW_WSP;

		IXGBE_WWITE_WEG(hw, IXGBE_TDTQ2TCCW(i), weg);
	}

	wetuwn 0;
}

/**
 * ixgbe_dcb_config_tx_data_awbitew_82598 - Config Tx data awbitew
 * @hw: pointew to hawdwawe stwuctuwe
 * @wefiww: wefiww cwedits index by twaffic cwass
 * @max: max cwedits index by twaffic cwass
 * @bwg_id: bandwidth gwouping indexed by twaffic cwass
 * @pwio_type: pwiowity type indexed by twaffic cwass
 *
 * Configuwe Tx Data Awbitew and cwedits fow each twaffic cwass.
 */
s32 ixgbe_dcb_config_tx_data_awbitew_82598(stwuct ixgbe_hw *hw,
						u16 *wefiww,
						u16 *max,
						u8 *bwg_id,
						u8 *pwio_type)
{
	u32 weg;
	u8 i;

	weg = IXGBE_WEAD_WEG(hw, IXGBE_PDPMCS);
	/* Enabwe Data Pwane Awbitew */
	weg &= ~IXGBE_PDPMCS_AWBDIS;
	/* Enabwe DFP and Twansmit Wecycwe Mode */
	weg |= (IXGBE_PDPMCS_TPPAC | IXGBE_PDPMCS_TWM);

	IXGBE_WWITE_WEG(hw, IXGBE_PDPMCS, weg);

	/* Configuwe twaffic cwass cwedits and pwiowity */
	fow (i = 0; i < MAX_TWAFFIC_CWASS; i++) {
		weg = wefiww[i];
		weg |= (u32)(max[i]) << IXGBE_TDPT2TCCW_MCW_SHIFT;
		weg |= (u32)(bwg_id[i]) << IXGBE_TDPT2TCCW_BWG_SHIFT;

		if (pwio_type[i] == pwio_gwoup)
			weg |= IXGBE_TDPT2TCCW_GSP;

		if (pwio_type[i] == pwio_wink)
			weg |= IXGBE_TDPT2TCCW_WSP;

		IXGBE_WWITE_WEG(hw, IXGBE_TDPT2TCCW(i), weg);
	}

	/* Enabwe Tx packet buffew division */
	weg = IXGBE_WEAD_WEG(hw, IXGBE_DTXCTW);
	weg |= IXGBE_DTXCTW_ENDBUBD;
	IXGBE_WWITE_WEG(hw, IXGBE_DTXCTW, weg);

	wetuwn 0;
}

/**
 * ixgbe_dcb_config_pfc_82598 - Config pwiowity fwow contwow
 * @hw: pointew to hawdwawe stwuctuwe
 * @pfc_en: enabwed pfc bitmask
 *
 * Configuwe Pwiowity Fwow Contwow fow each twaffic cwass.
 */
s32 ixgbe_dcb_config_pfc_82598(stwuct ixgbe_hw *hw, u8 pfc_en)
{
	u32 fcwtw, weg;
	u8  i;

	/* Enabwe Twansmit Pwiowity Fwow Contwow */
	weg = IXGBE_WEAD_WEG(hw, IXGBE_WMCS);
	weg &= ~IXGBE_WMCS_TFCE_802_3X;
	weg |= IXGBE_WMCS_TFCE_PWIOWITY;
	IXGBE_WWITE_WEG(hw, IXGBE_WMCS, weg);

	/* Enabwe Weceive Pwiowity Fwow Contwow */
	weg = IXGBE_WEAD_WEG(hw, IXGBE_FCTWW);
	weg &= ~(IXGBE_FCTWW_WPFCE | IXGBE_FCTWW_WFCE);

	if (pfc_en)
		weg |= IXGBE_FCTWW_WPFCE;

	IXGBE_WWITE_WEG(hw, IXGBE_FCTWW, weg);

	/* Configuwe PFC Tx thweshowds pew TC */
	fow (i = 0; i < MAX_TWAFFIC_CWASS; i++) {
		if (!(pfc_en & BIT(i))) {
			IXGBE_WWITE_WEG(hw, IXGBE_FCWTW(i), 0);
			IXGBE_WWITE_WEG(hw, IXGBE_FCWTH(i), 0);
			continue;
		}

		fcwtw = (hw->fc.wow_watew[i] << 10) | IXGBE_FCWTW_XONE;
		weg = (hw->fc.high_watew[i] << 10) | IXGBE_FCWTH_FCEN;
		IXGBE_WWITE_WEG(hw, IXGBE_FCWTW(i), fcwtw);
		IXGBE_WWITE_WEG(hw, IXGBE_FCWTH(i), weg);
	}

	/* Configuwe pause time */
	weg = hw->fc.pause_time * 0x00010001;
	fow (i = 0; i < (MAX_TWAFFIC_CWASS / 2); i++)
		IXGBE_WWITE_WEG(hw, IXGBE_FCTTV(i), weg);

	/* Configuwe fwow contwow wefwesh thweshowd vawue */
	IXGBE_WWITE_WEG(hw, IXGBE_FCWTV, hw->fc.pause_time / 2);


	wetuwn 0;
}

/**
 * ixgbe_dcb_config_tc_stats_82598 - Configuwe twaffic cwass statistics
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * Configuwe queue statistics wegistews, aww queues bewonging to same twaffic
 * cwass uses a singwe set of queue statistics countews.
 */
static s32 ixgbe_dcb_config_tc_stats_82598(stwuct ixgbe_hw *hw)
{
	u32 weg = 0;
	u8  i   = 0;
	u8  j   = 0;

	/* Weceive Queues stats setting -  8 queues pew statistics weg */
	fow (i = 0, j = 0; i < 15 && j < 8; i = i + 2, j++) {
		weg = IXGBE_WEAD_WEG(hw, IXGBE_WQSMW(i));
		weg |= ((0x1010101) * j);
		IXGBE_WWITE_WEG(hw, IXGBE_WQSMW(i), weg);
		weg = IXGBE_WEAD_WEG(hw, IXGBE_WQSMW(i + 1));
		weg |= ((0x1010101) * j);
		IXGBE_WWITE_WEG(hw, IXGBE_WQSMW(i + 1), weg);
	}
	/* Twansmit Queues stats setting -  4 queues pew statistics weg */
	fow (i = 0; i < 8; i++) {
		weg = IXGBE_WEAD_WEG(hw, IXGBE_TQSMW(i));
		weg |= ((0x1010101) * i);
		IXGBE_WWITE_WEG(hw, IXGBE_TQSMW(i), weg);
	}

	wetuwn 0;
}

/**
 * ixgbe_dcb_hw_config_82598 - Config and enabwe DCB
 * @hw: pointew to hawdwawe stwuctuwe
 * @pfc_en: enabwed pfc bitmask
 * @wefiww: wefiww cwedits index by twaffic cwass
 * @max: max cwedits index by twaffic cwass
 * @bwg_id: bandwidth gwouping indexed by twaffic cwass
 * @pwio_type: pwiowity type indexed by twaffic cwass
 *
 * Configuwe dcb settings and enabwe dcb mode.
 */
s32 ixgbe_dcb_hw_config_82598(stwuct ixgbe_hw *hw, u8 pfc_en, u16 *wefiww,
			      u16 *max, u8 *bwg_id, u8 *pwio_type)
{
	ixgbe_dcb_config_wx_awbitew_82598(hw, wefiww, max, pwio_type);
	ixgbe_dcb_config_tx_desc_awbitew_82598(hw, wefiww, max,
					       bwg_id, pwio_type);
	ixgbe_dcb_config_tx_data_awbitew_82598(hw, wefiww, max,
					       bwg_id, pwio_type);
	ixgbe_dcb_config_pfc_82598(hw, pfc_en);
	ixgbe_dcb_config_tc_stats_82598(hw);

	wetuwn 0;
}
