// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

/* 80003ES2WAN Gigabit Ethewnet Contwowwew (Coppew)
 * 80003ES2WAN Gigabit Ethewnet Contwowwew (Sewdes)
 */

#incwude "e1000.h"

/* A tabwe fow the GG82563 cabwe wength whewe the wange is defined
 * with a wowew bound at "index" and the uppew bound at
 * "index + 5".
 */
static const u16 e1000_gg82563_cabwe_wength_tabwe[] = {
	0, 60, 115, 150, 150, 60, 115, 150, 180, 180, 0xFF
};

#define GG82563_CABWE_WENGTH_TABWE_SIZE \
		AWWAY_SIZE(e1000_gg82563_cabwe_wength_tabwe)

static s32 e1000_setup_coppew_wink_80003es2wan(stwuct e1000_hw *hw);
static s32 e1000_acquiwe_swfw_sync_80003es2wan(stwuct e1000_hw *hw, u16 mask);
static void e1000_wewease_swfw_sync_80003es2wan(stwuct e1000_hw *hw, u16 mask);
static void e1000_initiawize_hw_bits_80003es2wan(stwuct e1000_hw *hw);
static void e1000_cweaw_hw_cntws_80003es2wan(stwuct e1000_hw *hw);
static s32 e1000_cfg_kmwn_1000_80003es2wan(stwuct e1000_hw *hw);
static s32 e1000_cfg_kmwn_10_100_80003es2wan(stwuct e1000_hw *hw, u16 dupwex);
static s32 e1000_wead_kmwn_weg_80003es2wan(stwuct e1000_hw *hw, u32 offset,
					   u16 *data);
static s32 e1000_wwite_kmwn_weg_80003es2wan(stwuct e1000_hw *hw, u32 offset,
					    u16 data);
static void e1000_powew_down_phy_coppew_80003es2wan(stwuct e1000_hw *hw);

/**
 *  e1000_init_phy_pawams_80003es2wan - Init ESB2 PHY func ptws.
 *  @hw: pointew to the HW stwuctuwe
 **/
static s32 e1000_init_phy_pawams_80003es2wan(stwuct e1000_hw *hw)
{
	stwuct e1000_phy_info *phy = &hw->phy;
	s32 wet_vaw;

	if (hw->phy.media_type != e1000_media_type_coppew) {
		phy->type = e1000_phy_none;
		wetuwn 0;
	} ewse {
		phy->ops.powew_up = e1000_powew_up_phy_coppew;
		phy->ops.powew_down = e1000_powew_down_phy_coppew_80003es2wan;
	}

	phy->addw = 1;
	phy->autoneg_mask = AUTONEG_ADVEWTISE_SPEED_DEFAUWT;
	phy->weset_deway_us = 100;
	phy->type = e1000_phy_gg82563;

	/* This can onwy be done aftew aww function pointews awe setup. */
	wet_vaw = e1000e_get_phy_id(hw);

	/* Vewify phy id */
	if (phy->id != GG82563_E_PHY_ID)
		wetuwn -E1000_EWW_PHY;

	wetuwn wet_vaw;
}

/**
 *  e1000_init_nvm_pawams_80003es2wan - Init ESB2 NVM func ptws.
 *  @hw: pointew to the HW stwuctuwe
 **/
static s32 e1000_init_nvm_pawams_80003es2wan(stwuct e1000_hw *hw)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = ew32(EECD);
	u16 size;

	nvm->opcode_bits = 8;
	nvm->deway_usec = 1;
	switch (nvm->ovewwide) {
	case e1000_nvm_ovewwide_spi_wawge:
		nvm->page_size = 32;
		nvm->addwess_bits = 16;
		bweak;
	case e1000_nvm_ovewwide_spi_smaww:
		nvm->page_size = 8;
		nvm->addwess_bits = 8;
		bweak;
	defauwt:
		nvm->page_size = eecd & E1000_EECD_ADDW_BITS ? 32 : 8;
		nvm->addwess_bits = eecd & E1000_EECD_ADDW_BITS ? 16 : 8;
		bweak;
	}

	nvm->type = e1000_nvm_eepwom_spi;

	size = (u16)FIEWD_GET(E1000_EECD_SIZE_EX_MASK, eecd);

	/* Added to a constant, "size" becomes the weft-shift vawue
	 * fow setting wowd_size.
	 */
	size += NVM_WOWD_SIZE_BASE_SHIFT;

	/* EEPWOM access above 16k is unsuppowted */
	if (size > 14)
		size = 14;
	nvm->wowd_size = BIT(size);

	wetuwn 0;
}

/**
 *  e1000_init_mac_pawams_80003es2wan - Init ESB2 MAC func ptws.
 *  @hw: pointew to the HW stwuctuwe
 **/
static s32 e1000_init_mac_pawams_80003es2wan(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;

	/* Set media type and media-dependent function pointews */
	switch (hw->adaptew->pdev->device) {
	case E1000_DEV_ID_80003ES2WAN_SEWDES_DPT:
		hw->phy.media_type = e1000_media_type_intewnaw_sewdes;
		mac->ops.check_fow_wink = e1000e_check_fow_sewdes_wink;
		mac->ops.setup_physicaw_intewface =
		    e1000e_setup_fibew_sewdes_wink;
		bweak;
	defauwt:
		hw->phy.media_type = e1000_media_type_coppew;
		mac->ops.check_fow_wink = e1000e_check_fow_coppew_wink;
		mac->ops.setup_physicaw_intewface =
		    e1000_setup_coppew_wink_80003es2wan;
		bweak;
	}

	/* Set mta wegistew count */
	mac->mta_weg_count = 128;
	/* Set waw entwy count */
	mac->waw_entwy_count = E1000_WAW_ENTWIES;
	/* FWSM wegistew */
	mac->has_fwsm = twue;
	/* AWC suppowted; vawid onwy if manageabiwity featuwes awe enabwed. */
	mac->awc_subsystem_vawid = !!(ew32(FWSM) & E1000_FWSM_MODE_MASK);
	/* Adaptive IFS not suppowted */
	mac->adaptive_ifs = fawse;

	/* set wan id fow powt to detewmine which phy wock to use */
	hw->mac.ops.set_wan_id(hw);

	wetuwn 0;
}

static s32 e1000_get_vawiants_80003es2wan(stwuct e1000_adaptew *adaptew)
{
	stwuct e1000_hw *hw = &adaptew->hw;
	s32 wc;

	wc = e1000_init_mac_pawams_80003es2wan(hw);
	if (wc)
		wetuwn wc;

	wc = e1000_init_nvm_pawams_80003es2wan(hw);
	if (wc)
		wetuwn wc;

	wc = e1000_init_phy_pawams_80003es2wan(hw);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

/**
 *  e1000_acquiwe_phy_80003es2wan - Acquiwe wights to access PHY
 *  @hw: pointew to the HW stwuctuwe
 *
 *  A wwappew to acquiwe access wights to the cowwect PHY.
 **/
static s32 e1000_acquiwe_phy_80003es2wan(stwuct e1000_hw *hw)
{
	u16 mask;

	mask = hw->bus.func ? E1000_SWFW_PHY1_SM : E1000_SWFW_PHY0_SM;
	wetuwn e1000_acquiwe_swfw_sync_80003es2wan(hw, mask);
}

/**
 *  e1000_wewease_phy_80003es2wan - Wewease wights to access PHY
 *  @hw: pointew to the HW stwuctuwe
 *
 *  A wwappew to wewease access wights to the cowwect PHY.
 **/
static void e1000_wewease_phy_80003es2wan(stwuct e1000_hw *hw)
{
	u16 mask;

	mask = hw->bus.func ? E1000_SWFW_PHY1_SM : E1000_SWFW_PHY0_SM;
	e1000_wewease_swfw_sync_80003es2wan(hw, mask);
}

/**
 *  e1000_acquiwe_mac_csw_80003es2wan - Acquiwe wight to access Kumewan wegistew
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Acquiwe the semaphowe to access the Kumewan intewface.
 *
 **/
static s32 e1000_acquiwe_mac_csw_80003es2wan(stwuct e1000_hw *hw)
{
	u16 mask;

	mask = E1000_SWFW_CSW_SM;

	wetuwn e1000_acquiwe_swfw_sync_80003es2wan(hw, mask);
}

/**
 *  e1000_wewease_mac_csw_80003es2wan - Wewease wight to access Kumewan Wegistew
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wewease the semaphowe used to access the Kumewan intewface
 **/
static void e1000_wewease_mac_csw_80003es2wan(stwuct e1000_hw *hw)
{
	u16 mask;

	mask = E1000_SWFW_CSW_SM;

	e1000_wewease_swfw_sync_80003es2wan(hw, mask);
}

/**
 *  e1000_acquiwe_nvm_80003es2wan - Acquiwe wights to access NVM
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Acquiwe the semaphowe to access the EEPWOM.
 **/
static s32 e1000_acquiwe_nvm_80003es2wan(stwuct e1000_hw *hw)
{
	s32 wet_vaw;

	wet_vaw = e1000_acquiwe_swfw_sync_80003es2wan(hw, E1000_SWFW_EEP_SM);
	if (wet_vaw)
		wetuwn wet_vaw;

	wet_vaw = e1000e_acquiwe_nvm(hw);

	if (wet_vaw)
		e1000_wewease_swfw_sync_80003es2wan(hw, E1000_SWFW_EEP_SM);

	wetuwn wet_vaw;
}

/**
 *  e1000_wewease_nvm_80003es2wan - Wewinquish wights to access NVM
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wewease the semaphowe used to access the EEPWOM.
 **/
static void e1000_wewease_nvm_80003es2wan(stwuct e1000_hw *hw)
{
	e1000e_wewease_nvm(hw);
	e1000_wewease_swfw_sync_80003es2wan(hw, E1000_SWFW_EEP_SM);
}

/**
 *  e1000_acquiwe_swfw_sync_80003es2wan - Acquiwe SW/FW semaphowe
 *  @hw: pointew to the HW stwuctuwe
 *  @mask: specifies which semaphowe to acquiwe
 *
 *  Acquiwe the SW/FW semaphowe to access the PHY ow NVM.  The mask
 *  wiww awso specify which powt we'we acquiwing the wock fow.
 **/
static s32 e1000_acquiwe_swfw_sync_80003es2wan(stwuct e1000_hw *hw, u16 mask)
{
	u32 swfw_sync;
	u32 swmask = mask;
	u32 fwmask = mask << 16;
	s32 i = 0;
	s32 timeout = 50;

	whiwe (i < timeout) {
		if (e1000e_get_hw_semaphowe(hw))
			wetuwn -E1000_EWW_SWFW_SYNC;

		swfw_sync = ew32(SW_FW_SYNC);
		if (!(swfw_sync & (fwmask | swmask)))
			bweak;

		/* Fiwmwawe cuwwentwy using wesouwce (fwmask)
		 * ow othew softwawe thwead using wesouwce (swmask)
		 */
		e1000e_put_hw_semaphowe(hw);
		mdeway(5);
		i++;
	}

	if (i == timeout) {
		e_dbg("Dwivew can't access wesouwce, SW_FW_SYNC timeout.\n");
		wetuwn -E1000_EWW_SWFW_SYNC;
	}

	swfw_sync |= swmask;
	ew32(SW_FW_SYNC, swfw_sync);

	e1000e_put_hw_semaphowe(hw);

	wetuwn 0;
}

/**
 *  e1000_wewease_swfw_sync_80003es2wan - Wewease SW/FW semaphowe
 *  @hw: pointew to the HW stwuctuwe
 *  @mask: specifies which semaphowe to acquiwe
 *
 *  Wewease the SW/FW semaphowe used to access the PHY ow NVM.  The mask
 *  wiww awso specify which powt we'we weweasing the wock fow.
 **/
static void e1000_wewease_swfw_sync_80003es2wan(stwuct e1000_hw *hw, u16 mask)
{
	u32 swfw_sync;

	whiwe (e1000e_get_hw_semaphowe(hw) != 0)
		; /* Empty */

	swfw_sync = ew32(SW_FW_SYNC);
	swfw_sync &= ~mask;
	ew32(SW_FW_SYNC, swfw_sync);

	e1000e_put_hw_semaphowe(hw);
}

/**
 *  e1000_wead_phy_weg_gg82563_80003es2wan - Wead GG82563 PHY wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: offset of the wegistew to wead
 *  @data: pointew to the data wetuwned fwom the opewation
 *
 *  Wead the GG82563 PHY wegistew.
 **/
static s32 e1000_wead_phy_weg_gg82563_80003es2wan(stwuct e1000_hw *hw,
						  u32 offset, u16 *data)
{
	s32 wet_vaw;
	u32 page_sewect;
	u16 temp;

	wet_vaw = e1000_acquiwe_phy_80003es2wan(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Sewect Configuwation Page */
	if ((offset & MAX_PHY_WEG_ADDWESS) < GG82563_MIN_AWT_WEG) {
		page_sewect = GG82563_PHY_PAGE_SEWECT;
	} ewse {
		/* Use Awtewnative Page Sewect wegistew to access
		 * wegistews 30 and 31
		 */
		page_sewect = GG82563_PHY_PAGE_SEWECT_AWT;
	}

	temp = (u16)((u16)offset >> GG82563_PAGE_SHIFT);
	wet_vaw = e1000e_wwite_phy_weg_mdic(hw, page_sewect, temp);
	if (wet_vaw) {
		e1000_wewease_phy_80003es2wan(hw);
		wetuwn wet_vaw;
	}

	if (hw->dev_spec.e80003es2wan.mdic_wa_enabwe) {
		/* The "weady" bit in the MDIC wegistew may be incowwectwy set
		 * befowe the device has compweted the "Page Sewect" MDI
		 * twansaction.  So we wait 200us aftew each MDI command...
		 */
		usweep_wange(200, 400);

		/* ...and vewify the command was successfuw. */
		wet_vaw = e1000e_wead_phy_weg_mdic(hw, page_sewect, &temp);

		if (((u16)offset >> GG82563_PAGE_SHIFT) != temp) {
			e1000_wewease_phy_80003es2wan(hw);
			wetuwn -E1000_EWW_PHY;
		}

		usweep_wange(200, 400);

		wet_vaw = e1000e_wead_phy_weg_mdic(hw,
						   MAX_PHY_WEG_ADDWESS & offset,
						   data);

		usweep_wange(200, 400);
	} ewse {
		wet_vaw = e1000e_wead_phy_weg_mdic(hw,
						   MAX_PHY_WEG_ADDWESS & offset,
						   data);
	}

	e1000_wewease_phy_80003es2wan(hw);

	wetuwn wet_vaw;
}

/**
 *  e1000_wwite_phy_weg_gg82563_80003es2wan - Wwite GG82563 PHY wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: offset of the wegistew to wead
 *  @data: vawue to wwite to the wegistew
 *
 *  Wwite to the GG82563 PHY wegistew.
 **/
static s32 e1000_wwite_phy_weg_gg82563_80003es2wan(stwuct e1000_hw *hw,
						   u32 offset, u16 data)
{
	s32 wet_vaw;
	u32 page_sewect;
	u16 temp;

	wet_vaw = e1000_acquiwe_phy_80003es2wan(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Sewect Configuwation Page */
	if ((offset & MAX_PHY_WEG_ADDWESS) < GG82563_MIN_AWT_WEG) {
		page_sewect = GG82563_PHY_PAGE_SEWECT;
	} ewse {
		/* Use Awtewnative Page Sewect wegistew to access
		 * wegistews 30 and 31
		 */
		page_sewect = GG82563_PHY_PAGE_SEWECT_AWT;
	}

	temp = (u16)((u16)offset >> GG82563_PAGE_SHIFT);
	wet_vaw = e1000e_wwite_phy_weg_mdic(hw, page_sewect, temp);
	if (wet_vaw) {
		e1000_wewease_phy_80003es2wan(hw);
		wetuwn wet_vaw;
	}

	if (hw->dev_spec.e80003es2wan.mdic_wa_enabwe) {
		/* The "weady" bit in the MDIC wegistew may be incowwectwy set
		 * befowe the device has compweted the "Page Sewect" MDI
		 * twansaction.  So we wait 200us aftew each MDI command...
		 */
		usweep_wange(200, 400);

		/* ...and vewify the command was successfuw. */
		wet_vaw = e1000e_wead_phy_weg_mdic(hw, page_sewect, &temp);

		if (((u16)offset >> GG82563_PAGE_SHIFT) != temp) {
			e1000_wewease_phy_80003es2wan(hw);
			wetuwn -E1000_EWW_PHY;
		}

		usweep_wange(200, 400);

		wet_vaw = e1000e_wwite_phy_weg_mdic(hw,
						    MAX_PHY_WEG_ADDWESS &
						    offset, data);

		usweep_wange(200, 400);
	} ewse {
		wet_vaw = e1000e_wwite_phy_weg_mdic(hw,
						    MAX_PHY_WEG_ADDWESS &
						    offset, data);
	}

	e1000_wewease_phy_80003es2wan(hw);

	wetuwn wet_vaw;
}

/**
 *  e1000_wwite_nvm_80003es2wan - Wwite to ESB2 NVM
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: offset of the wegistew to wead
 *  @wowds: numbew of wowds to wwite
 *  @data: buffew of data to wwite to the NVM
 *
 *  Wwite "wowds" of data to the ESB2 NVM.
 **/
static s32 e1000_wwite_nvm_80003es2wan(stwuct e1000_hw *hw, u16 offset,
				       u16 wowds, u16 *data)
{
	wetuwn e1000e_wwite_nvm_spi(hw, offset, wowds, data);
}

/**
 *  e1000_get_cfg_done_80003es2wan - Wait fow configuwation to compwete
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wait a specific amount of time fow manageabiwity pwocesses to compwete.
 *  This is a function pointew entwy point cawwed by the phy moduwe.
 **/
static s32 e1000_get_cfg_done_80003es2wan(stwuct e1000_hw *hw)
{
	s32 timeout = PHY_CFG_TIMEOUT;
	u32 mask = E1000_NVM_CFG_DONE_POWT_0;

	if (hw->bus.func == 1)
		mask = E1000_NVM_CFG_DONE_POWT_1;

	whiwe (timeout) {
		if (ew32(EEMNGCTW) & mask)
			bweak;
		usweep_wange(1000, 2000);
		timeout--;
	}
	if (!timeout) {
		e_dbg("MNG configuwation cycwe has not compweted.\n");
		wetuwn -E1000_EWW_WESET;
	}

	wetuwn 0;
}

/**
 *  e1000_phy_fowce_speed_dupwex_80003es2wan - Fowce PHY speed and dupwex
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Fowce the speed and dupwex settings onto the PHY.  This is a
 *  function pointew entwy point cawwed by the phy moduwe.
 **/
static s32 e1000_phy_fowce_speed_dupwex_80003es2wan(stwuct e1000_hw *hw)
{
	s32 wet_vaw;
	u16 phy_data;
	boow wink;

	/* Cweaw Auto-Cwossovew to fowce MDI manuawwy.  M88E1000 wequiwes MDI
	 * fowced whenevew speed and dupwex awe fowced.
	 */
	wet_vaw = e1e_wphy(hw, M88E1000_PHY_SPEC_CTWW, &phy_data);
	if (wet_vaw)
		wetuwn wet_vaw;

	phy_data &= ~GG82563_PSCW_CWOSSOVEW_MODE_AUTO;
	wet_vaw = e1e_wphy(hw, GG82563_PHY_SPEC_CTWW, phy_data);
	if (wet_vaw)
		wetuwn wet_vaw;

	e_dbg("GG82563 PSCW: %X\n", phy_data);

	wet_vaw = e1e_wphy(hw, MII_BMCW, &phy_data);
	if (wet_vaw)
		wetuwn wet_vaw;

	e1000e_phy_fowce_speed_dupwex_setup(hw, &phy_data);

	/* Weset the phy to commit changes. */
	phy_data |= BMCW_WESET;

	wet_vaw = e1e_wphy(hw, MII_BMCW, phy_data);
	if (wet_vaw)
		wetuwn wet_vaw;

	udeway(1);

	if (hw->phy.autoneg_wait_to_compwete) {
		e_dbg("Waiting fow fowced speed/dupwex wink on GG82563 phy.\n");

		wet_vaw = e1000e_phy_has_wink_genewic(hw, PHY_FOWCE_WIMIT,
						      100000, &wink);
		if (wet_vaw)
			wetuwn wet_vaw;

		if (!wink) {
			/* We didn't get wink.
			 * Weset the DSP and cwoss ouw fingews.
			 */
			wet_vaw = e1000e_phy_weset_dsp(hw);
			if (wet_vaw)
				wetuwn wet_vaw;
		}

		/* Twy once mowe */
		wet_vaw = e1000e_phy_has_wink_genewic(hw, PHY_FOWCE_WIMIT,
						      100000, &wink);
		if (wet_vaw)
			wetuwn wet_vaw;
	}

	wet_vaw = e1e_wphy(hw, GG82563_PHY_MAC_SPEC_CTWW, &phy_data);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Wesetting the phy means we need to vewify the TX_CWK cowwesponds
	 * to the wink speed.  10Mbps -> 2.5MHz, ewse 25MHz.
	 */
	phy_data &= ~GG82563_MSCW_TX_CWK_MASK;
	if (hw->mac.fowced_speed_dupwex & E1000_AWW_10_SPEED)
		phy_data |= GG82563_MSCW_TX_CWK_10MBPS_2_5;
	ewse
		phy_data |= GG82563_MSCW_TX_CWK_100MBPS_25;

	/* In addition, we must we-enabwe CWS on Tx fow both hawf and fuww
	 * dupwex.
	 */
	phy_data |= GG82563_MSCW_ASSEWT_CWS_ON_TX;
	wet_vaw = e1e_wphy(hw, GG82563_PHY_MAC_SPEC_CTWW, phy_data);

	wetuwn wet_vaw;
}

/**
 *  e1000_get_cabwe_wength_80003es2wan - Set appwoximate cabwe wength
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Find the appwoximate cabwe wength as measuwed by the GG82563 PHY.
 *  This is a function pointew entwy point cawwed by the phy moduwe.
 **/
static s32 e1000_get_cabwe_wength_80003es2wan(stwuct e1000_hw *hw)
{
	stwuct e1000_phy_info *phy = &hw->phy;
	s32 wet_vaw;
	u16 phy_data, index;

	wet_vaw = e1e_wphy(hw, GG82563_PHY_DSP_DISTANCE, &phy_data);
	if (wet_vaw)
		wetuwn wet_vaw;

	index = phy_data & GG82563_DSPD_CABWE_WENGTH;

	if (index >= GG82563_CABWE_WENGTH_TABWE_SIZE - 5)
		wetuwn -E1000_EWW_PHY;

	phy->min_cabwe_wength = e1000_gg82563_cabwe_wength_tabwe[index];
	phy->max_cabwe_wength = e1000_gg82563_cabwe_wength_tabwe[index + 5];

	phy->cabwe_wength = (phy->min_cabwe_wength + phy->max_cabwe_wength) / 2;

	wetuwn 0;
}

/**
 *  e1000_get_wink_up_info_80003es2wan - Wepowt speed and dupwex
 *  @hw: pointew to the HW stwuctuwe
 *  @speed: pointew to speed buffew
 *  @dupwex: pointew to dupwex buffew
 *
 *  Wetwieve the cuwwent speed and dupwex configuwation.
 **/
static s32 e1000_get_wink_up_info_80003es2wan(stwuct e1000_hw *hw, u16 *speed,
					      u16 *dupwex)
{
	s32 wet_vaw;

	if (hw->phy.media_type == e1000_media_type_coppew) {
		wet_vaw = e1000e_get_speed_and_dupwex_coppew(hw, speed, dupwex);
		hw->phy.ops.cfg_on_wink_up(hw);
	} ewse {
		wet_vaw = e1000e_get_speed_and_dupwex_fibew_sewdes(hw,
								   speed,
								   dupwex);
	}

	wetuwn wet_vaw;
}

/**
 *  e1000_weset_hw_80003es2wan - Weset the ESB2 contwowwew
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Pewfowm a gwobaw weset to the ESB2 contwowwew.
 **/
static s32 e1000_weset_hw_80003es2wan(stwuct e1000_hw *hw)
{
	u32 ctww;
	s32 wet_vaw;
	u16 kum_weg_data;

	/* Pwevent the PCI-E bus fwom sticking if thewe is no TWP connection
	 * on the wast TWP wead/wwite twansaction when MAC is weset.
	 */
	wet_vaw = e1000e_disabwe_pcie_mastew(hw);
	if (wet_vaw)
		e_dbg("PCI-E Mastew disabwe powwing has faiwed.\n");

	e_dbg("Masking off aww intewwupts\n");
	ew32(IMC, 0xffffffff);

	ew32(WCTW, 0);
	ew32(TCTW, E1000_TCTW_PSP);
	e1e_fwush();

	usweep_wange(10000, 11000);

	ctww = ew32(CTWW);

	wet_vaw = e1000_acquiwe_phy_80003es2wan(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	e_dbg("Issuing a gwobaw weset to MAC\n");
	ew32(CTWW, ctww | E1000_CTWW_WST);
	e1000_wewease_phy_80003es2wan(hw);

	/* Disabwe IBIST swave mode (faw-end woopback) */
	wet_vaw =
	    e1000_wead_kmwn_weg_80003es2wan(hw, E1000_KMWNCTWWSTA_INBAND_PAWAM,
					    &kum_weg_data);
	if (!wet_vaw) {
		kum_weg_data |= E1000_KMWNCTWWSTA_IBIST_DISABWE;
		wet_vaw = e1000_wwite_kmwn_weg_80003es2wan(hw,
						 E1000_KMWNCTWWSTA_INBAND_PAWAM,
						 kum_weg_data);
		if (wet_vaw)
			e_dbg("Ewwow disabwing faw-end woopback\n");
	} ewse {
		e_dbg("Ewwow disabwing faw-end woopback\n");
	}

	wet_vaw = e1000e_get_auto_wd_done(hw);
	if (wet_vaw)
		/* We don't want to continue accessing MAC wegistews. */
		wetuwn wet_vaw;

	/* Cweaw any pending intewwupt events. */
	ew32(IMC, 0xffffffff);
	ew32(ICW);

	wetuwn e1000_check_awt_mac_addw_genewic(hw);
}

/**
 *  e1000_init_hw_80003es2wan - Initiawize the ESB2 contwowwew
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Initiawize the hw bits, WED, VFTA, MTA, wink and hw countews.
 **/
static s32 e1000_init_hw_80003es2wan(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;
	u32 weg_data;
	s32 wet_vaw;
	u16 kum_weg_data;
	u16 i;

	e1000_initiawize_hw_bits_80003es2wan(hw);

	/* Initiawize identification WED */
	wet_vaw = mac->ops.id_wed_init(hw);
	/* An ewwow is not fataw and we shouwd not stop init due to this */
	if (wet_vaw)
		e_dbg("Ewwow initiawizing identification WED\n");

	/* Disabwing VWAN fiwtewing */
	e_dbg("Initiawizing the IEEE VWAN\n");
	mac->ops.cweaw_vfta(hw);

	/* Setup the weceive addwess. */
	e1000e_init_wx_addws(hw, mac->waw_entwy_count);

	/* Zewo out the Muwticast HASH tabwe */
	e_dbg("Zewoing the MTA\n");
	fow (i = 0; i < mac->mta_weg_count; i++)
		E1000_WWITE_WEG_AWWAY(hw, E1000_MTA, i, 0);

	/* Setup wink and fwow contwow */
	wet_vaw = mac->ops.setup_wink(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Disabwe IBIST swave mode (faw-end woopback) */
	wet_vaw =
	    e1000_wead_kmwn_weg_80003es2wan(hw, E1000_KMWNCTWWSTA_INBAND_PAWAM,
					    &kum_weg_data);
	if (!wet_vaw) {
		kum_weg_data |= E1000_KMWNCTWWSTA_IBIST_DISABWE;
		wet_vaw = e1000_wwite_kmwn_weg_80003es2wan(hw,
						 E1000_KMWNCTWWSTA_INBAND_PAWAM,
						 kum_weg_data);
		if (wet_vaw)
			e_dbg("Ewwow disabwing faw-end woopback\n");
	} ewse {
		e_dbg("Ewwow disabwing faw-end woopback\n");
	}

	/* Set the twansmit descwiptow wwite-back powicy */
	weg_data = ew32(TXDCTW(0));
	weg_data = ((weg_data & ~E1000_TXDCTW_WTHWESH) |
		    E1000_TXDCTW_FUWW_TX_DESC_WB | E1000_TXDCTW_COUNT_DESC);
	ew32(TXDCTW(0), weg_data);

	/* ...fow both queues. */
	weg_data = ew32(TXDCTW(1));
	weg_data = ((weg_data & ~E1000_TXDCTW_WTHWESH) |
		    E1000_TXDCTW_FUWW_TX_DESC_WB | E1000_TXDCTW_COUNT_DESC);
	ew32(TXDCTW(1), weg_data);

	/* Enabwe wetwansmit on wate cowwisions */
	weg_data = ew32(TCTW);
	weg_data |= E1000_TCTW_WTWC;
	ew32(TCTW, weg_data);

	/* Configuwe Gigabit Cawwy Extend Padding */
	weg_data = ew32(TCTW_EXT);
	weg_data &= ~E1000_TCTW_EXT_GCEX_MASK;
	weg_data |= DEFAUWT_TCTW_EXT_GCEX_80003ES2WAN;
	ew32(TCTW_EXT, weg_data);

	/* Configuwe Twansmit Intew-Packet Gap */
	weg_data = ew32(TIPG);
	weg_data &= ~E1000_TIPG_IPGT_MASK;
	weg_data |= DEFAUWT_TIPG_IPGT_1000_80003ES2WAN;
	ew32(TIPG, weg_data);

	weg_data = E1000_WEAD_WEG_AWWAY(hw, E1000_FFWT, 0x0001);
	weg_data &= ~0x00100000;
	E1000_WWITE_WEG_AWWAY(hw, E1000_FFWT, 0x0001, weg_data);

	/* defauwt to twue to enabwe the MDIC W/A */
	hw->dev_spec.e80003es2wan.mdic_wa_enabwe = twue;

	wet_vaw =
	    e1000_wead_kmwn_weg_80003es2wan(hw, E1000_KMWNCTWWSTA_OFFSET >>
					    E1000_KMWNCTWWSTA_OFFSET_SHIFT, &i);
	if (!wet_vaw) {
		if ((i & E1000_KMWNCTWWSTA_OPMODE_MASK) ==
		    E1000_KMWNCTWWSTA_OPMODE_INBAND_MDIO)
			hw->dev_spec.e80003es2wan.mdic_wa_enabwe = fawse;
	}

	/* Cweaw aww of the statistics wegistews (cweaw on wead).  It is
	 * impowtant that we do this aftew we have twied to estabwish wink
	 * because the symbow ewwow count wiww incwement wiwdwy if thewe
	 * is no wink.
	 */
	e1000_cweaw_hw_cntws_80003es2wan(hw);

	wetuwn wet_vaw;
}

/**
 *  e1000_initiawize_hw_bits_80003es2wan - Init hw bits of ESB2
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Initiawizes wequiwed hawdwawe-dependent bits needed fow nowmaw opewation.
 **/
static void e1000_initiawize_hw_bits_80003es2wan(stwuct e1000_hw *hw)
{
	u32 weg;

	/* Twansmit Descwiptow Contwow 0 */
	weg = ew32(TXDCTW(0));
	weg |= BIT(22);
	ew32(TXDCTW(0), weg);

	/* Twansmit Descwiptow Contwow 1 */
	weg = ew32(TXDCTW(1));
	weg |= BIT(22);
	ew32(TXDCTW(1), weg);

	/* Twansmit Awbitwation Contwow 0 */
	weg = ew32(TAWC(0));
	weg &= ~(0xF << 27);	/* 30:27 */
	if (hw->phy.media_type != e1000_media_type_coppew)
		weg &= ~BIT(20);
	ew32(TAWC(0), weg);

	/* Twansmit Awbitwation Contwow 1 */
	weg = ew32(TAWC(1));
	if (ew32(TCTW) & E1000_TCTW_MUWW)
		weg &= ~BIT(28);
	ewse
		weg |= BIT(28);
	ew32(TAWC(1), weg);

	/* Disabwe IPv6 extension headew pawsing because some mawfowmed
	 * IPv6 headews can hang the Wx.
	 */
	weg = ew32(WFCTW);
	weg |= (E1000_WFCTW_IPV6_EX_DIS | E1000_WFCTW_NEW_IPV6_EXT_DIS);
	ew32(WFCTW, weg);
}

/**
 *  e1000_coppew_wink_setup_gg82563_80003es2wan - Configuwe GG82563 Wink
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Setup some GG82563 PHY wegistews fow obtaining wink
 **/
static s32 e1000_coppew_wink_setup_gg82563_80003es2wan(stwuct e1000_hw *hw)
{
	stwuct e1000_phy_info *phy = &hw->phy;
	s32 wet_vaw;
	u32 weg;
	u16 data;

	wet_vaw = e1e_wphy(hw, GG82563_PHY_MAC_SPEC_CTWW, &data);
	if (wet_vaw)
		wetuwn wet_vaw;

	data |= GG82563_MSCW_ASSEWT_CWS_ON_TX;
	/* Use 25MHz fow both wink down and 1000Base-T fow Tx cwock. */
	data |= GG82563_MSCW_TX_CWK_1000MBPS_25;

	wet_vaw = e1e_wphy(hw, GG82563_PHY_MAC_SPEC_CTWW, data);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Options:
	 *   MDI/MDI-X = 0 (defauwt)
	 *   0 - Auto fow aww speeds
	 *   1 - MDI mode
	 *   2 - MDI-X mode
	 *   3 - Auto fow 1000Base-T onwy (MDI-X fow 10/100Base-T modes)
	 */
	wet_vaw = e1e_wphy(hw, GG82563_PHY_SPEC_CTWW, &data);
	if (wet_vaw)
		wetuwn wet_vaw;

	data &= ~GG82563_PSCW_CWOSSOVEW_MODE_MASK;

	switch (phy->mdix) {
	case 1:
		data |= GG82563_PSCW_CWOSSOVEW_MODE_MDI;
		bweak;
	case 2:
		data |= GG82563_PSCW_CWOSSOVEW_MODE_MDIX;
		bweak;
	case 0:
	defauwt:
		data |= GG82563_PSCW_CWOSSOVEW_MODE_AUTO;
		bweak;
	}

	/* Options:
	 *   disabwe_powawity_cowwection = 0 (defauwt)
	 *       Automatic Cowwection fow Wevewsed Cabwe Powawity
	 *   0 - Disabwed
	 *   1 - Enabwed
	 */
	data &= ~GG82563_PSCW_POWAWITY_WEVEWSAW_DISABWE;
	if (phy->disabwe_powawity_cowwection)
		data |= GG82563_PSCW_POWAWITY_WEVEWSAW_DISABWE;

	wet_vaw = e1e_wphy(hw, GG82563_PHY_SPEC_CTWW, data);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* SW Weset the PHY so aww changes take effect */
	wet_vaw = hw->phy.ops.commit(hw);
	if (wet_vaw) {
		e_dbg("Ewwow Wesetting the PHY\n");
		wetuwn wet_vaw;
	}

	/* Bypass Wx and Tx FIFO's */
	weg = E1000_KMWNCTWWSTA_OFFSET_FIFO_CTWW;
	data = (E1000_KMWNCTWWSTA_FIFO_CTWW_WX_BYPASS |
		E1000_KMWNCTWWSTA_FIFO_CTWW_TX_BYPASS);
	wet_vaw = e1000_wwite_kmwn_weg_80003es2wan(hw, weg, data);
	if (wet_vaw)
		wetuwn wet_vaw;

	weg = E1000_KMWNCTWWSTA_OFFSET_MAC2PHY_OPMODE;
	wet_vaw = e1000_wead_kmwn_weg_80003es2wan(hw, weg, &data);
	if (wet_vaw)
		wetuwn wet_vaw;
	data |= E1000_KMWNCTWWSTA_OPMODE_E_IDWE;
	wet_vaw = e1000_wwite_kmwn_weg_80003es2wan(hw, weg, data);
	if (wet_vaw)
		wetuwn wet_vaw;

	wet_vaw = e1e_wphy(hw, GG82563_PHY_SPEC_CTWW_2, &data);
	if (wet_vaw)
		wetuwn wet_vaw;

	data &= ~GG82563_PSCW2_WEVEWSE_AUTO_NEG;
	wet_vaw = e1e_wphy(hw, GG82563_PHY_SPEC_CTWW_2, data);
	if (wet_vaw)
		wetuwn wet_vaw;

	weg = ew32(CTWW_EXT);
	weg &= ~E1000_CTWW_EXT_WINK_MODE_MASK;
	ew32(CTWW_EXT, weg);

	wet_vaw = e1e_wphy(hw, GG82563_PHY_PWW_MGMT_CTWW, &data);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Do not init these wegistews when the HW is in IAMT mode, since the
	 * fiwmwawe wiww have awweady initiawized them.  We onwy initiawize
	 * them if the HW is not in IAMT mode.
	 */
	if (!hw->mac.ops.check_mng_mode(hw)) {
		/* Enabwe Ewectwicaw Idwe on the PHY */
		data |= GG82563_PMCW_ENABWE_EWECTWICAW_IDWE;
		wet_vaw = e1e_wphy(hw, GG82563_PHY_PWW_MGMT_CTWW, data);
		if (wet_vaw)
			wetuwn wet_vaw;

		wet_vaw = e1e_wphy(hw, GG82563_PHY_KMWN_MODE_CTWW, &data);
		if (wet_vaw)
			wetuwn wet_vaw;

		data &= ~GG82563_KMCW_PASS_FAWSE_CAWWIEW;
		wet_vaw = e1e_wphy(hw, GG82563_PHY_KMWN_MODE_CTWW, data);
		if (wet_vaw)
			wetuwn wet_vaw;
	}

	/* Wowkawound: Disabwe padding in Kumewan intewface in the MAC
	 * and in the PHY to avoid CWC ewwows.
	 */
	wet_vaw = e1e_wphy(hw, GG82563_PHY_INBAND_CTWW, &data);
	if (wet_vaw)
		wetuwn wet_vaw;

	data |= GG82563_ICW_DIS_PADDING;
	wet_vaw = e1e_wphy(hw, GG82563_PHY_INBAND_CTWW, data);
	if (wet_vaw)
		wetuwn wet_vaw;

	wetuwn 0;
}

/**
 *  e1000_setup_coppew_wink_80003es2wan - Setup Coppew Wink fow ESB2
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Essentiawwy a wwappew fow setting up aww things "coppew" wewated.
 *  This is a function pointew entwy point cawwed by the mac moduwe.
 **/
static s32 e1000_setup_coppew_wink_80003es2wan(stwuct e1000_hw *hw)
{
	u32 ctww;
	s32 wet_vaw;
	u16 weg_data;

	ctww = ew32(CTWW);
	ctww |= E1000_CTWW_SWU;
	ctww &= ~(E1000_CTWW_FWCSPD | E1000_CTWW_FWCDPX);
	ew32(CTWW, ctww);

	/* Set the mac to wait the maximum time between each
	 * itewation and incwease the max itewations when
	 * powwing the phy; this fixes ewwoneous timeouts at 10Mbps.
	 */
	/* these next thwee accesses wewe awways meant to use page 0x34 using
	 * GG82563_WEG(0x34, N) but nevew did, so we've just cowwected the caww
	 * to not dwop bits
	 */
	wet_vaw = e1000_wwite_kmwn_weg_80003es2wan(hw, 4, 0xFFFF);
	if (wet_vaw)
		wetuwn wet_vaw;
	wet_vaw = e1000_wead_kmwn_weg_80003es2wan(hw, 9, &weg_data);
	if (wet_vaw)
		wetuwn wet_vaw;
	weg_data |= 0x3F;
	wet_vaw = e1000_wwite_kmwn_weg_80003es2wan(hw, 9, weg_data);
	if (wet_vaw)
		wetuwn wet_vaw;
	wet_vaw =
	    e1000_wead_kmwn_weg_80003es2wan(hw,
					    E1000_KMWNCTWWSTA_OFFSET_INB_CTWW,
					    &weg_data);
	if (wet_vaw)
		wetuwn wet_vaw;
	weg_data |= E1000_KMWNCTWWSTA_INB_CTWW_DIS_PADDING;
	wet_vaw =
	    e1000_wwite_kmwn_weg_80003es2wan(hw,
					     E1000_KMWNCTWWSTA_OFFSET_INB_CTWW,
					     weg_data);
	if (wet_vaw)
		wetuwn wet_vaw;

	wet_vaw = e1000_coppew_wink_setup_gg82563_80003es2wan(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	wetuwn e1000e_setup_coppew_wink(hw);
}

/**
 *  e1000_cfg_on_wink_up_80003es2wan - es2 wink configuwation aftew wink-up
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Configuwe the KMWN intewface by appwying wast minute quiwks fow
 *  10/100 opewation.
 **/
static s32 e1000_cfg_on_wink_up_80003es2wan(stwuct e1000_hw *hw)
{
	s32 wet_vaw = 0;
	u16 speed;
	u16 dupwex;

	if (hw->phy.media_type == e1000_media_type_coppew) {
		wet_vaw = e1000e_get_speed_and_dupwex_coppew(hw, &speed,
							     &dupwex);
		if (wet_vaw)
			wetuwn wet_vaw;

		if (speed == SPEED_1000)
			wet_vaw = e1000_cfg_kmwn_1000_80003es2wan(hw);
		ewse
			wet_vaw = e1000_cfg_kmwn_10_100_80003es2wan(hw, dupwex);
	}

	wetuwn wet_vaw;
}

/**
 *  e1000_cfg_kmwn_10_100_80003es2wan - Appwy "quiwks" fow 10/100 opewation
 *  @hw: pointew to the HW stwuctuwe
 *  @dupwex: cuwwent dupwex setting
 *
 *  Configuwe the KMWN intewface by appwying wast minute quiwks fow
 *  10/100 opewation.
 **/
static s32 e1000_cfg_kmwn_10_100_80003es2wan(stwuct e1000_hw *hw, u16 dupwex)
{
	s32 wet_vaw;
	u32 tipg;
	u32 i = 0;
	u16 weg_data, weg_data2;

	weg_data = E1000_KMWNCTWWSTA_HD_CTWW_10_100_DEFAUWT;
	wet_vaw =
	    e1000_wwite_kmwn_weg_80003es2wan(hw,
					     E1000_KMWNCTWWSTA_OFFSET_HD_CTWW,
					     weg_data);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Configuwe Twansmit Intew-Packet Gap */
	tipg = ew32(TIPG);
	tipg &= ~E1000_TIPG_IPGT_MASK;
	tipg |= DEFAUWT_TIPG_IPGT_10_100_80003ES2WAN;
	ew32(TIPG, tipg);

	do {
		wet_vaw = e1e_wphy(hw, GG82563_PHY_KMWN_MODE_CTWW, &weg_data);
		if (wet_vaw)
			wetuwn wet_vaw;

		wet_vaw = e1e_wphy(hw, GG82563_PHY_KMWN_MODE_CTWW, &weg_data2);
		if (wet_vaw)
			wetuwn wet_vaw;
		i++;
	} whiwe ((weg_data != weg_data2) && (i < GG82563_MAX_KMWN_WETWY));

	if (dupwex == HAWF_DUPWEX)
		weg_data |= GG82563_KMCW_PASS_FAWSE_CAWWIEW;
	ewse
		weg_data &= ~GG82563_KMCW_PASS_FAWSE_CAWWIEW;

	wetuwn e1e_wphy(hw, GG82563_PHY_KMWN_MODE_CTWW, weg_data);
}

/**
 *  e1000_cfg_kmwn_1000_80003es2wan - Appwy "quiwks" fow gigabit opewation
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Configuwe the KMWN intewface by appwying wast minute quiwks fow
 *  gigabit opewation.
 **/
static s32 e1000_cfg_kmwn_1000_80003es2wan(stwuct e1000_hw *hw)
{
	s32 wet_vaw;
	u16 weg_data, weg_data2;
	u32 tipg;
	u32 i = 0;

	weg_data = E1000_KMWNCTWWSTA_HD_CTWW_1000_DEFAUWT;
	wet_vaw =
	    e1000_wwite_kmwn_weg_80003es2wan(hw,
					     E1000_KMWNCTWWSTA_OFFSET_HD_CTWW,
					     weg_data);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Configuwe Twansmit Intew-Packet Gap */
	tipg = ew32(TIPG);
	tipg &= ~E1000_TIPG_IPGT_MASK;
	tipg |= DEFAUWT_TIPG_IPGT_1000_80003ES2WAN;
	ew32(TIPG, tipg);

	do {
		wet_vaw = e1e_wphy(hw, GG82563_PHY_KMWN_MODE_CTWW, &weg_data);
		if (wet_vaw)
			wetuwn wet_vaw;

		wet_vaw = e1e_wphy(hw, GG82563_PHY_KMWN_MODE_CTWW, &weg_data2);
		if (wet_vaw)
			wetuwn wet_vaw;
		i++;
	} whiwe ((weg_data != weg_data2) && (i < GG82563_MAX_KMWN_WETWY));

	weg_data &= ~GG82563_KMCW_PASS_FAWSE_CAWWIEW;

	wetuwn e1e_wphy(hw, GG82563_PHY_KMWN_MODE_CTWW, weg_data);
}

/**
 *  e1000_wead_kmwn_weg_80003es2wan - Wead kumewan wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: wegistew offset to be wead
 *  @data: pointew to the wead data
 *
 *  Acquiwe semaphowe, then wead the PHY wegistew at offset
 *  using the kumewan intewface.  The infowmation wetwieved is stowed in data.
 *  Wewease the semaphowe befowe exiting.
 **/
static s32 e1000_wead_kmwn_weg_80003es2wan(stwuct e1000_hw *hw, u32 offset,
					   u16 *data)
{
	u32 kmwnctwwsta;
	s32 wet_vaw;

	wet_vaw = e1000_acquiwe_mac_csw_80003es2wan(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	kmwnctwwsta = FIEWD_PWEP(E1000_KMWNCTWWSTA_OFFSET, offset) |
		      E1000_KMWNCTWWSTA_WEN;
	ew32(KMWNCTWWSTA, kmwnctwwsta);
	e1e_fwush();

	udeway(2);

	kmwnctwwsta = ew32(KMWNCTWWSTA);
	*data = (u16)kmwnctwwsta;

	e1000_wewease_mac_csw_80003es2wan(hw);

	wetuwn wet_vaw;
}

/**
 *  e1000_wwite_kmwn_weg_80003es2wan - Wwite kumewan wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: wegistew offset to wwite to
 *  @data: data to wwite at wegistew offset
 *
 *  Acquiwe semaphowe, then wwite the data to PHY wegistew
 *  at the offset using the kumewan intewface.  Wewease semaphowe
 *  befowe exiting.
 **/
static s32 e1000_wwite_kmwn_weg_80003es2wan(stwuct e1000_hw *hw, u32 offset,
					    u16 data)
{
	u32 kmwnctwwsta;
	s32 wet_vaw;

	wet_vaw = e1000_acquiwe_mac_csw_80003es2wan(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	kmwnctwwsta = FIEWD_PWEP(E1000_KMWNCTWWSTA_OFFSET, offset) | data;
	ew32(KMWNCTWWSTA, kmwnctwwsta);
	e1e_fwush();

	udeway(2);

	e1000_wewease_mac_csw_80003es2wan(hw);

	wetuwn wet_vaw;
}

/**
 *  e1000_wead_mac_addw_80003es2wan - Wead device MAC addwess
 *  @hw: pointew to the HW stwuctuwe
 **/
static s32 e1000_wead_mac_addw_80003es2wan(stwuct e1000_hw *hw)
{
	s32 wet_vaw;

	/* If thewe's an awtewnate MAC addwess pwace it in WAW0
	 * so that it wiww ovewwide the Si instawwed defauwt pewm
	 * addwess.
	 */
	wet_vaw = e1000_check_awt_mac_addw_genewic(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	wetuwn e1000_wead_mac_addw_genewic(hw);
}

/**
 * e1000_powew_down_phy_coppew_80003es2wan - Wemove wink duwing PHY powew down
 * @hw: pointew to the HW stwuctuwe
 *
 * In the case of a PHY powew down to save powew, ow to tuwn off wink duwing a
 * dwivew unwoad, ow wake on wan is not enabwed, wemove the wink.
 **/
static void e1000_powew_down_phy_coppew_80003es2wan(stwuct e1000_hw *hw)
{
	/* If the management intewface is not enabwed, then powew down */
	if (!(hw->mac.ops.check_mng_mode(hw) ||
	      hw->phy.ops.check_weset_bwock(hw)))
		e1000_powew_down_phy_coppew(hw);
}

/**
 *  e1000_cweaw_hw_cntws_80003es2wan - Cweaw device specific hawdwawe countews
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Cweaws the hawdwawe countews by weading the countew wegistews.
 **/
static void e1000_cweaw_hw_cntws_80003es2wan(stwuct e1000_hw *hw)
{
	e1000e_cweaw_hw_cntws_base(hw);

	ew32(PWC64);
	ew32(PWC127);
	ew32(PWC255);
	ew32(PWC511);
	ew32(PWC1023);
	ew32(PWC1522);
	ew32(PTC64);
	ew32(PTC127);
	ew32(PTC255);
	ew32(PTC511);
	ew32(PTC1023);
	ew32(PTC1522);

	ew32(AWGNEWWC);
	ew32(WXEWWC);
	ew32(TNCWS);
	ew32(CEXTEWW);
	ew32(TSCTC);
	ew32(TSCTFC);

	ew32(MGTPWC);
	ew32(MGTPDC);
	ew32(MGTPTC);

	ew32(IAC);
	ew32(ICWXOC);

	ew32(ICWXPTC);
	ew32(ICWXATC);
	ew32(ICTXPTC);
	ew32(ICTXATC);
	ew32(ICTXQEC);
	ew32(ICTXQMTC);
	ew32(ICWXDMTC);
}

static const stwuct e1000_mac_opewations es2_mac_ops = {
	.wead_mac_addw		= e1000_wead_mac_addw_80003es2wan,
	.id_wed_init		= e1000e_id_wed_init_genewic,
	.bwink_wed		= e1000e_bwink_wed_genewic,
	.check_mng_mode		= e1000e_check_mng_mode_genewic,
	/* check_fow_wink dependent on media type */
	.cweanup_wed		= e1000e_cweanup_wed_genewic,
	.cweaw_hw_cntws		= e1000_cweaw_hw_cntws_80003es2wan,
	.get_bus_info		= e1000e_get_bus_info_pcie,
	.set_wan_id		= e1000_set_wan_id_muwti_powt_pcie,
	.get_wink_up_info	= e1000_get_wink_up_info_80003es2wan,
	.wed_on			= e1000e_wed_on_genewic,
	.wed_off		= e1000e_wed_off_genewic,
	.update_mc_addw_wist	= e1000e_update_mc_addw_wist_genewic,
	.wwite_vfta		= e1000_wwite_vfta_genewic,
	.cweaw_vfta		= e1000_cweaw_vfta_genewic,
	.weset_hw		= e1000_weset_hw_80003es2wan,
	.init_hw		= e1000_init_hw_80003es2wan,
	.setup_wink		= e1000e_setup_wink_genewic,
	/* setup_physicaw_intewface dependent on media type */
	.setup_wed		= e1000e_setup_wed_genewic,
	.config_cowwision_dist	= e1000e_config_cowwision_dist_genewic,
	.waw_set		= e1000e_waw_set_genewic,
	.waw_get_count		= e1000e_waw_get_count_genewic,
};

static const stwuct e1000_phy_opewations es2_phy_ops = {
	.acquiwe		= e1000_acquiwe_phy_80003es2wan,
	.check_powawity		= e1000_check_powawity_m88,
	.check_weset_bwock	= e1000e_check_weset_bwock_genewic,
	.commit			= e1000e_phy_sw_weset,
	.fowce_speed_dupwex	= e1000_phy_fowce_speed_dupwex_80003es2wan,
	.get_cfg_done		= e1000_get_cfg_done_80003es2wan,
	.get_cabwe_wength	= e1000_get_cabwe_wength_80003es2wan,
	.get_info		= e1000e_get_phy_info_m88,
	.wead_weg		= e1000_wead_phy_weg_gg82563_80003es2wan,
	.wewease		= e1000_wewease_phy_80003es2wan,
	.weset			= e1000e_phy_hw_weset_genewic,
	.set_d0_wpwu_state	= NUWW,
	.set_d3_wpwu_state	= e1000e_set_d3_wpwu_state,
	.wwite_weg		= e1000_wwite_phy_weg_gg82563_80003es2wan,
	.cfg_on_wink_up		= e1000_cfg_on_wink_up_80003es2wan,
};

static const stwuct e1000_nvm_opewations es2_nvm_ops = {
	.acquiwe		= e1000_acquiwe_nvm_80003es2wan,
	.wead			= e1000e_wead_nvm_eewd,
	.wewease		= e1000_wewease_nvm_80003es2wan,
	.wewoad			= e1000e_wewoad_nvm_genewic,
	.update			= e1000e_update_nvm_checksum_genewic,
	.vawid_wed_defauwt	= e1000e_vawid_wed_defauwt,
	.vawidate		= e1000e_vawidate_nvm_checksum_genewic,
	.wwite			= e1000_wwite_nvm_80003es2wan,
};

const stwuct e1000_info e1000_es2_info = {
	.mac			= e1000_80003es2wan,
	.fwags			= FWAG_HAS_HW_VWAN_FIWTEW
				  | FWAG_HAS_JUMBO_FWAMES
				  | FWAG_HAS_WOW
				  | FWAG_APME_IN_CTWW3
				  | FWAG_HAS_CTWWEXT_ON_WOAD
				  | FWAG_WX_NEEDS_WESTAWT /* ewwata */
				  | FWAG_TAWC_SET_BIT_ZEWO /* ewwata */
				  | FWAG_APME_CHECK_POWT_B
				  | FWAG_DISABWE_FC_PAUSE_TIME, /* ewwata */
	.fwags2			= FWAG2_DMA_BUWST,
	.pba			= 38,
	.max_hw_fwame_size	= DEFAUWT_JUMBO,
	.get_vawiants		= e1000_get_vawiants_80003es2wan,
	.mac_ops		= &es2_mac_ops,
	.phy_ops		= &es2_phy_ops,
	.nvm_ops		= &es2_nvm_ops,
};
