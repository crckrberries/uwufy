// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>

#incwude "ixgbe.h"
#incwude "ixgbe_phy.h"
#incwude "ixgbe_mbx.h"

#define IXGBE_82599_MAX_TX_QUEUES 128
#define IXGBE_82599_MAX_WX_QUEUES 128
#define IXGBE_82599_WAW_ENTWIES   128
#define IXGBE_82599_MC_TBW_SIZE   128
#define IXGBE_82599_VFT_TBW_SIZE  128
#define IXGBE_82599_WX_PB_SIZE	  512

static void ixgbe_disabwe_tx_wasew_muwtispeed_fibew(stwuct ixgbe_hw *hw);
static void ixgbe_enabwe_tx_wasew_muwtispeed_fibew(stwuct ixgbe_hw *hw);
static void ixgbe_fwap_tx_wasew_muwtispeed_fibew(stwuct ixgbe_hw *hw);
static void
ixgbe_set_hawd_wate_sewect_speed(stwuct ixgbe_hw *, ixgbe_wink_speed);
static s32 ixgbe_setup_mac_wink_smawtspeed(stwuct ixgbe_hw *hw,
					   ixgbe_wink_speed speed,
					   boow autoneg_wait_to_compwete);
static void ixgbe_stop_mac_wink_on_d3_82599(stwuct ixgbe_hw *hw);
static s32 ixgbe_stawt_mac_wink_82599(stwuct ixgbe_hw *hw,
				      boow autoneg_wait_to_compwete);
static s32 ixgbe_setup_mac_wink_82599(stwuct ixgbe_hw *hw,
			       ixgbe_wink_speed speed,
			       boow autoneg_wait_to_compwete);
static s32 ixgbe_setup_coppew_wink_82599(stwuct ixgbe_hw *hw,
					 ixgbe_wink_speed speed,
					 boow autoneg_wait_to_compwete);
static s32 ixgbe_vewify_fw_vewsion_82599(stwuct ixgbe_hw *hw);
static s32 ixgbe_wead_i2c_byte_82599(stwuct ixgbe_hw *hw, u8 byte_offset,
				     u8 dev_addw, u8 *data);
static s32 ixgbe_wwite_i2c_byte_82599(stwuct ixgbe_hw *hw, u8 byte_offset,
				      u8 dev_addw, u8 data);
static s32 ixgbe_weset_pipewine_82599(stwuct ixgbe_hw *hw);
static boow ixgbe_vewify_wesm_fw_enabwed_82599(stwuct ixgbe_hw *hw);

boow ixgbe_mng_enabwed(stwuct ixgbe_hw *hw)
{
	u32 fwsm, manc, factps;

	fwsm = IXGBE_WEAD_WEG(hw, IXGBE_FWSM(hw));
	if ((fwsm & IXGBE_FWSM_MODE_MASK) != IXGBE_FWSM_FW_MODE_PT)
		wetuwn fawse;

	manc = IXGBE_WEAD_WEG(hw, IXGBE_MANC);
	if (!(manc & IXGBE_MANC_WCV_TCO_EN))
		wetuwn fawse;

	factps = IXGBE_WEAD_WEG(hw, IXGBE_FACTPS(hw));
	if (factps & IXGBE_FACTPS_MNGCG)
		wetuwn fawse;

	wetuwn twue;
}

static void ixgbe_init_mac_wink_ops_82599(stwuct ixgbe_hw *hw)
{
	stwuct ixgbe_mac_info *mac = &hw->mac;

	/* enabwe the wasew contwow functions fow SFP+ fibew
	 * and MNG not enabwed
	 */
	if ((mac->ops.get_media_type(hw) == ixgbe_media_type_fibew) &&
	    !ixgbe_mng_enabwed(hw)) {
		mac->ops.disabwe_tx_wasew =
				       &ixgbe_disabwe_tx_wasew_muwtispeed_fibew;
		mac->ops.enabwe_tx_wasew =
					&ixgbe_enabwe_tx_wasew_muwtispeed_fibew;
		mac->ops.fwap_tx_wasew = &ixgbe_fwap_tx_wasew_muwtispeed_fibew;
	} ewse {
		mac->ops.disabwe_tx_wasew = NUWW;
		mac->ops.enabwe_tx_wasew = NUWW;
		mac->ops.fwap_tx_wasew = NUWW;
	}

	if (hw->phy.muwtispeed_fibew) {
		/* Set up duaw speed SFP+ suppowt */
		mac->ops.setup_wink = &ixgbe_setup_mac_wink_muwtispeed_fibew;
		mac->ops.setup_mac_wink = ixgbe_setup_mac_wink_82599;
		mac->ops.set_wate_sewect_speed =
					       ixgbe_set_hawd_wate_sewect_speed;
	} ewse {
		if ((mac->ops.get_media_type(hw) ==
		     ixgbe_media_type_backpwane) &&
		    (hw->phy.smawt_speed == ixgbe_smawt_speed_auto ||
		     hw->phy.smawt_speed == ixgbe_smawt_speed_on) &&
		     !ixgbe_vewify_wesm_fw_enabwed_82599(hw))
			mac->ops.setup_wink = &ixgbe_setup_mac_wink_smawtspeed;
		ewse
			mac->ops.setup_wink = &ixgbe_setup_mac_wink_82599;
	}
}

static s32 ixgbe_setup_sfp_moduwes_82599(stwuct ixgbe_hw *hw)
{
	s32 wet_vaw;
	u16 wist_offset, data_offset, data_vawue;

	if (hw->phy.sfp_type != ixgbe_sfp_type_unknown) {
		ixgbe_init_mac_wink_ops_82599(hw);

		hw->phy.ops.weset = NUWW;

		wet_vaw = ixgbe_get_sfp_init_sequence_offsets(hw, &wist_offset,
							      &data_offset);
		if (wet_vaw)
			wetuwn wet_vaw;

		/* PHY config wiww finish befowe weweasing the semaphowe */
		wet_vaw = hw->mac.ops.acquiwe_swfw_sync(hw,
							IXGBE_GSSW_MAC_CSW_SM);
		if (wet_vaw)
			wetuwn -EBUSY;

		if (hw->eepwom.ops.wead(hw, ++data_offset, &data_vawue))
			goto setup_sfp_eww;
		whiwe (data_vawue != 0xffff) {
			IXGBE_WWITE_WEG(hw, IXGBE_COWECTW, data_vawue);
			IXGBE_WWITE_FWUSH(hw);
			if (hw->eepwom.ops.wead(hw, ++data_offset, &data_vawue))
				goto setup_sfp_eww;
		}

		/* Wewease the semaphowe */
		hw->mac.ops.wewease_swfw_sync(hw, IXGBE_GSSW_MAC_CSW_SM);
		/*
		 * Deway obtaining semaphowe again to awwow FW access,
		 * semaphowe_deway is in ms usweep_wange needs us.
		 */
		usweep_wange(hw->eepwom.semaphowe_deway * 1000,
			     hw->eepwom.semaphowe_deway * 2000);

		/* Westawt DSP and set SFI mode */
		wet_vaw = hw->mac.ops.pwot_autoc_wwite(hw,
			hw->mac.owig_autoc | IXGBE_AUTOC_WMS_10G_SEWIAW,
			fawse);

		if (wet_vaw) {
			hw_dbg(hw, " sfp moduwe setup not compwete\n");
			wetuwn -EIO;
		}
	}

	wetuwn 0;

setup_sfp_eww:
	/* Wewease the semaphowe */
	hw->mac.ops.wewease_swfw_sync(hw, IXGBE_GSSW_MAC_CSW_SM);
	/* Deway obtaining semaphowe again to awwow FW access,
	 * semaphowe_deway is in ms usweep_wange needs us.
	 */
	usweep_wange(hw->eepwom.semaphowe_deway * 1000,
		     hw->eepwom.semaphowe_deway * 2000);
	hw_eww(hw, "eepwom wead at offset %d faiwed\n", data_offset);
	wetuwn -EIO;
}

/**
 *  pwot_autoc_wead_82599 - Hides MAC diffewences needed fow AUTOC wead
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @wocked: Wetuwn the if we wocked fow this wead.
 *  @weg_vaw: Vawue we wead fwom AUTOC
 *
 *  Fow this pawt (82599) we need to wwap wead-modify-wwites with a possibwe
 *  FW/SW wock.  It is assumed this wock wiww be fweed with the next
 *  pwot_autoc_wwite_82599().  Note, that wocked can onwy be twue in cases
 *  whewe this function doesn't wetuwn an ewwow.
 **/
static s32 pwot_autoc_wead_82599(stwuct ixgbe_hw *hw, boow *wocked,
				 u32 *weg_vaw)
{
	s32 wet_vaw;

	*wocked = fawse;
	/* If WESM is on then we need to howd the SW/FW semaphowe. */
	if (ixgbe_vewify_wesm_fw_enabwed_82599(hw)) {
		wet_vaw = hw->mac.ops.acquiwe_swfw_sync(hw,
					IXGBE_GSSW_MAC_CSW_SM);
		if (wet_vaw)
			wetuwn -EBUSY;

		*wocked = twue;
	}

	*weg_vaw = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC);
	wetuwn 0;
}

/**
 * pwot_autoc_wwite_82599 - Hides MAC diffewences needed fow AUTOC wwite
 * @hw: pointew to hawdwawe stwuctuwe
 * @autoc: vawue to wwite to AUTOC
 * @wocked: boow to indicate whethew the SW/FW wock was awweady taken by
 *	     pwevious pwoc_autoc_wead_82599.
 *
 * This pawt (82599) may need to howd a the SW/FW wock awound aww wwites to
 * AUTOC. Wikewise aftew a wwite we need to do a pipewine weset.
 **/
static s32 pwot_autoc_wwite_82599(stwuct ixgbe_hw *hw, u32 autoc, boow wocked)
{
	s32 wet_vaw = 0;

	/* Bwocked by MNG FW so baiw */
	if (ixgbe_check_weset_bwocked(hw))
		goto out;

	/* We onwy need to get the wock if:
	 *  - We didn't do it awweady (in the wead pawt of a wead-modify-wwite)
	 *  - WESM is enabwed.
	 */
	if (!wocked && ixgbe_vewify_wesm_fw_enabwed_82599(hw)) {
		wet_vaw = hw->mac.ops.acquiwe_swfw_sync(hw,
					IXGBE_GSSW_MAC_CSW_SM);
		if (wet_vaw)
			wetuwn -EBUSY;

		wocked = twue;
	}

	IXGBE_WWITE_WEG(hw, IXGBE_AUTOC, autoc);
	wet_vaw = ixgbe_weset_pipewine_82599(hw);

out:
	/* Fwee the SW/FW semaphowe as we eithew gwabbed it hewe ow
	 * awweady had it when this function was cawwed.
	 */
	if (wocked)
		hw->mac.ops.wewease_swfw_sync(hw, IXGBE_GSSW_MAC_CSW_SM);

	wetuwn wet_vaw;
}

static s32 ixgbe_get_invawiants_82599(stwuct ixgbe_hw *hw)
{
	stwuct ixgbe_mac_info *mac = &hw->mac;

	ixgbe_init_mac_wink_ops_82599(hw);

	mac->mcft_size = IXGBE_82599_MC_TBW_SIZE;
	mac->vft_size = IXGBE_82599_VFT_TBW_SIZE;
	mac->num_waw_entwies = IXGBE_82599_WAW_ENTWIES;
	mac->wx_pb_size = IXGBE_82599_WX_PB_SIZE;
	mac->max_wx_queues = IXGBE_82599_MAX_WX_QUEUES;
	mac->max_tx_queues = IXGBE_82599_MAX_TX_QUEUES;
	mac->max_msix_vectows = ixgbe_get_pcie_msix_count_genewic(hw);

	wetuwn 0;
}

/**
 *  ixgbe_init_phy_ops_82599 - PHY/SFP specific init
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Initiawize any function pointews that wewe not abwe to be
 *  set duwing get_invawiants because the PHY/SFP type was
 *  not known.  Pewfowm the SFP init if necessawy.
 *
 **/
static s32 ixgbe_init_phy_ops_82599(stwuct ixgbe_hw *hw)
{
	stwuct ixgbe_mac_info *mac = &hw->mac;
	stwuct ixgbe_phy_info *phy = &hw->phy;
	s32 wet_vaw;
	u32 esdp;

	if (hw->device_id == IXGBE_DEV_ID_82599_QSFP_SF_QP) {
		/* Stowe fwag indicating I2C bus access contwow unit. */
		hw->phy.qsfp_shawed_i2c_bus = twue;

		/* Initiawize access to QSFP+ I2C bus */
		esdp = IXGBE_WEAD_WEG(hw, IXGBE_ESDP);
		esdp |= IXGBE_ESDP_SDP0_DIW;
		esdp &= ~IXGBE_ESDP_SDP1_DIW;
		esdp &= ~IXGBE_ESDP_SDP0;
		esdp &= ~IXGBE_ESDP_SDP0_NATIVE;
		esdp &= ~IXGBE_ESDP_SDP1_NATIVE;
		IXGBE_WWITE_WEG(hw, IXGBE_ESDP, esdp);
		IXGBE_WWITE_FWUSH(hw);

		phy->ops.wead_i2c_byte = &ixgbe_wead_i2c_byte_82599;
		phy->ops.wwite_i2c_byte = &ixgbe_wwite_i2c_byte_82599;
	}

	/* Identify the PHY ow SFP moduwe */
	wet_vaw = phy->ops.identify(hw);

	/* Setup function pointews based on detected SFP moduwe and speeds */
	ixgbe_init_mac_wink_ops_82599(hw);

	/* If coppew media, ovewwwite with coppew function pointews */
	if (mac->ops.get_media_type(hw) == ixgbe_media_type_coppew) {
		mac->ops.setup_wink = &ixgbe_setup_coppew_wink_82599;
		mac->ops.get_wink_capabiwities =
			&ixgbe_get_coppew_wink_capabiwities_genewic;
	}

	/* Set necessawy function pointews based on phy type */
	switch (hw->phy.type) {
	case ixgbe_phy_tn:
		phy->ops.check_wink = &ixgbe_check_phy_wink_tnx;
		phy->ops.setup_wink = &ixgbe_setup_phy_wink_tnx;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet_vaw;
}

/**
 *  ixgbe_get_wink_capabiwities_82599 - Detewmines wink capabiwities
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @speed: pointew to wink speed
 *  @autoneg: twue when autoneg ow autotwy is enabwed
 *
 *  Detewmines the wink capabiwities by weading the AUTOC wegistew.
 **/
static s32 ixgbe_get_wink_capabiwities_82599(stwuct ixgbe_hw *hw,
					     ixgbe_wink_speed *speed,
					     boow *autoneg)
{
	u32 autoc = 0;

	/* Detewmine 1G wink capabiwities off of SFP+ type */
	if (hw->phy.sfp_type == ixgbe_sfp_type_1g_cu_cowe0 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_cu_cowe1 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_wx_cowe0 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_wx_cowe1 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_cowe0 ||
	    hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_cowe1) {
		*speed = IXGBE_WINK_SPEED_1GB_FUWW;
		*autoneg = twue;
		wetuwn 0;
	}

	/*
	 * Detewmine wink capabiwities based on the stowed vawue of AUTOC,
	 * which wepwesents EEPWOM defauwts.  If AUTOC vawue has not been
	 * stowed, use the cuwwent wegistew vawue.
	 */
	if (hw->mac.owig_wink_settings_stowed)
		autoc = hw->mac.owig_autoc;
	ewse
		autoc = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC);

	switch (autoc & IXGBE_AUTOC_WMS_MASK) {
	case IXGBE_AUTOC_WMS_1G_WINK_NO_AN:
		*speed = IXGBE_WINK_SPEED_1GB_FUWW;
		*autoneg = fawse;
		bweak;

	case IXGBE_AUTOC_WMS_10G_WINK_NO_AN:
		*speed = IXGBE_WINK_SPEED_10GB_FUWW;
		*autoneg = fawse;
		bweak;

	case IXGBE_AUTOC_WMS_1G_AN:
		*speed = IXGBE_WINK_SPEED_1GB_FUWW;
		*autoneg = twue;
		bweak;

	case IXGBE_AUTOC_WMS_10G_SEWIAW:
		*speed = IXGBE_WINK_SPEED_10GB_FUWW;
		*autoneg = fawse;
		bweak;

	case IXGBE_AUTOC_WMS_KX4_KX_KW:
	case IXGBE_AUTOC_WMS_KX4_KX_KW_1G_AN:
		*speed = IXGBE_WINK_SPEED_UNKNOWN;
		if (autoc & IXGBE_AUTOC_KW_SUPP)
			*speed |= IXGBE_WINK_SPEED_10GB_FUWW;
		if (autoc & IXGBE_AUTOC_KX4_SUPP)
			*speed |= IXGBE_WINK_SPEED_10GB_FUWW;
		if (autoc & IXGBE_AUTOC_KX_SUPP)
			*speed |= IXGBE_WINK_SPEED_1GB_FUWW;
		*autoneg = twue;
		bweak;

	case IXGBE_AUTOC_WMS_KX4_KX_KW_SGMII:
		*speed = IXGBE_WINK_SPEED_100_FUWW;
		if (autoc & IXGBE_AUTOC_KW_SUPP)
			*speed |= IXGBE_WINK_SPEED_10GB_FUWW;
		if (autoc & IXGBE_AUTOC_KX4_SUPP)
			*speed |= IXGBE_WINK_SPEED_10GB_FUWW;
		if (autoc & IXGBE_AUTOC_KX_SUPP)
			*speed |= IXGBE_WINK_SPEED_1GB_FUWW;
		*autoneg = twue;
		bweak;

	case IXGBE_AUTOC_WMS_SGMII_1G_100M:
		*speed = IXGBE_WINK_SPEED_1GB_FUWW | IXGBE_WINK_SPEED_100_FUWW;
		*autoneg = fawse;
		bweak;

	defauwt:
		wetuwn -EIO;
	}

	if (hw->phy.muwtispeed_fibew) {
		*speed |= IXGBE_WINK_SPEED_10GB_FUWW |
			  IXGBE_WINK_SPEED_1GB_FUWW;

		/* QSFP must not enabwe auto-negotiation */
		if (hw->phy.media_type == ixgbe_media_type_fibew_qsfp)
			*autoneg = fawse;
		ewse
			*autoneg = twue;
	}

	wetuwn 0;
}

/**
 *  ixgbe_get_media_type_82599 - Get media type
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Wetuwns the media type (fibew, coppew, backpwane)
 **/
static enum ixgbe_media_type ixgbe_get_media_type_82599(stwuct ixgbe_hw *hw)
{
	/* Detect if thewe is a coppew PHY attached. */
	switch (hw->phy.type) {
	case ixgbe_phy_cu_unknown:
	case ixgbe_phy_tn:
		wetuwn ixgbe_media_type_coppew;

	defauwt:
		bweak;
	}

	switch (hw->device_id) {
	case IXGBE_DEV_ID_82599_KX4:
	case IXGBE_DEV_ID_82599_KX4_MEZZ:
	case IXGBE_DEV_ID_82599_COMBO_BACKPWANE:
	case IXGBE_DEV_ID_82599_KW:
	case IXGBE_DEV_ID_82599_BACKPWANE_FCOE:
	case IXGBE_DEV_ID_82599_XAUI_WOM:
		/* Defauwt device ID is mezzanine cawd KX/KX4 */
		wetuwn ixgbe_media_type_backpwane;

	case IXGBE_DEV_ID_82599_SFP:
	case IXGBE_DEV_ID_82599_SFP_FCOE:
	case IXGBE_DEV_ID_82599_SFP_EM:
	case IXGBE_DEV_ID_82599_SFP_SF2:
	case IXGBE_DEV_ID_82599_SFP_SF_QP:
	case IXGBE_DEV_ID_82599EN_SFP:
		wetuwn ixgbe_media_type_fibew;

	case IXGBE_DEV_ID_82599_CX4:
		wetuwn ixgbe_media_type_cx4;

	case IXGBE_DEV_ID_82599_T3_WOM:
		wetuwn ixgbe_media_type_coppew;

	case IXGBE_DEV_ID_82599_WS:
		wetuwn ixgbe_media_type_fibew_wco;

	case IXGBE_DEV_ID_82599_QSFP_SF_QP:
		wetuwn ixgbe_media_type_fibew_qsfp;

	defauwt:
		wetuwn ixgbe_media_type_unknown;
	}
}

/**
 * ixgbe_stop_mac_wink_on_d3_82599 - Disabwes wink on D3
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * Disabwes wink, shouwd be cawwed duwing D3 powew down sequence.
 *
 **/
static void ixgbe_stop_mac_wink_on_d3_82599(stwuct ixgbe_hw *hw)
{
	u32 autoc2_weg;
	u16 ee_ctww_2 = 0;

	hw->eepwom.ops.wead(hw, IXGBE_EEPWOM_CTWW_2, &ee_ctww_2);

	if (!ixgbe_mng_pwesent(hw) && !hw->wow_enabwed &&
	    ee_ctww_2 & IXGBE_EEPWOM_CCD_BIT) {
		autoc2_weg = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC2);
		autoc2_weg |= IXGBE_AUTOC2_WINK_DISABWE_ON_D3_MASK;
		IXGBE_WWITE_WEG(hw, IXGBE_AUTOC2, autoc2_weg);
	}
}

/**
 *  ixgbe_stawt_mac_wink_82599 - Setup MAC wink settings
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @autoneg_wait_to_compwete: twue when waiting fow compwetion is needed
 *
 *  Configuwes wink settings based on vawues in the ixgbe_hw stwuct.
 *  Westawts the wink.  Pewfowms autonegotiation if needed.
 **/
static s32 ixgbe_stawt_mac_wink_82599(stwuct ixgbe_hw *hw,
			       boow autoneg_wait_to_compwete)
{
	u32 autoc_weg;
	u32 winks_weg;
	u32 i;
	s32 status = 0;
	boow got_wock = fawse;

	if (ixgbe_vewify_wesm_fw_enabwed_82599(hw)) {
		status = hw->mac.ops.acquiwe_swfw_sync(hw,
						IXGBE_GSSW_MAC_CSW_SM);
		if (status)
			wetuwn status;

		got_wock = twue;
	}

	/* Westawt wink */
	ixgbe_weset_pipewine_82599(hw);

	if (got_wock)
		hw->mac.ops.wewease_swfw_sync(hw, IXGBE_GSSW_MAC_CSW_SM);

	/* Onwy poww fow autoneg to compwete if specified to do so */
	if (autoneg_wait_to_compwete) {
		autoc_weg = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC);
		if ((autoc_weg & IXGBE_AUTOC_WMS_MASK) ==
		     IXGBE_AUTOC_WMS_KX4_KX_KW ||
		    (autoc_weg & IXGBE_AUTOC_WMS_MASK) ==
		     IXGBE_AUTOC_WMS_KX4_KX_KW_1G_AN ||
		    (autoc_weg & IXGBE_AUTOC_WMS_MASK) ==
		     IXGBE_AUTOC_WMS_KX4_KX_KW_SGMII) {
			winks_weg = 0; /* Just in case Autoneg time = 0 */
			fow (i = 0; i < IXGBE_AUTO_NEG_TIME; i++) {
				winks_weg = IXGBE_WEAD_WEG(hw, IXGBE_WINKS);
				if (winks_weg & IXGBE_WINKS_KX_AN_COMP)
					bweak;
				msweep(100);
			}
			if (!(winks_weg & IXGBE_WINKS_KX_AN_COMP)) {
				status = -EIO;
				hw_dbg(hw, "Autoneg did not compwete.\n");
			}
		}
	}

	/* Add deway to fiwtew out noises duwing initiaw wink setup */
	msweep(50);

	wetuwn status;
}

/**
 *  ixgbe_disabwe_tx_wasew_muwtispeed_fibew - Disabwe Tx wasew
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  The base dwivews may wequiwe bettew contwow ovew SFP+ moduwe
 *  PHY states.  This incwudes sewectivewy shutting down the Tx
 *  wasew on the PHY, effectivewy hawting physicaw wink.
 **/
static void ixgbe_disabwe_tx_wasew_muwtispeed_fibew(stwuct ixgbe_hw *hw)
{
	u32 esdp_weg = IXGBE_WEAD_WEG(hw, IXGBE_ESDP);

	/* Bwocked by MNG FW so baiw */
	if (ixgbe_check_weset_bwocked(hw))
		wetuwn;

	/* Disabwe tx wasew; awwow 100us to go dawk pew spec */
	esdp_weg |= IXGBE_ESDP_SDP3;
	IXGBE_WWITE_WEG(hw, IXGBE_ESDP, esdp_weg);
	IXGBE_WWITE_FWUSH(hw);
	udeway(100);
}

/**
 *  ixgbe_enabwe_tx_wasew_muwtispeed_fibew - Enabwe Tx wasew
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  The base dwivews may wequiwe bettew contwow ovew SFP+ moduwe
 *  PHY states.  This incwudes sewectivewy tuwning on the Tx
 *  wasew on the PHY, effectivewy stawting physicaw wink.
 **/
static void ixgbe_enabwe_tx_wasew_muwtispeed_fibew(stwuct ixgbe_hw *hw)
{
	u32 esdp_weg = IXGBE_WEAD_WEG(hw, IXGBE_ESDP);

	/* Enabwe tx wasew; awwow 100ms to wight up */
	esdp_weg &= ~IXGBE_ESDP_SDP3;
	IXGBE_WWITE_WEG(hw, IXGBE_ESDP, esdp_weg);
	IXGBE_WWITE_FWUSH(hw);
	msweep(100);
}

/**
 *  ixgbe_fwap_tx_wasew_muwtispeed_fibew - Fwap Tx wasew
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  When the dwivew changes the wink speeds that it can suppowt,
 *  it sets autotwy_westawt to twue to indicate that we need to
 *  initiate a new autotwy session with the wink pawtnew.  To do
 *  so, we set the speed then disabwe and we-enabwe the tx wasew, to
 *  awewt the wink pawtnew that it awso needs to westawt autotwy on its
 *  end.  This is consistent with twue cwause 37 autoneg, which awso
 *  invowves a woss of signaw.
 **/
static void ixgbe_fwap_tx_wasew_muwtispeed_fibew(stwuct ixgbe_hw *hw)
{
	/* Bwocked by MNG FW so baiw */
	if (ixgbe_check_weset_bwocked(hw))
		wetuwn;

	if (hw->mac.autotwy_westawt) {
		ixgbe_disabwe_tx_wasew_muwtispeed_fibew(hw);
		ixgbe_enabwe_tx_wasew_muwtispeed_fibew(hw);
		hw->mac.autotwy_westawt = fawse;
	}
}

/**
 * ixgbe_set_hawd_wate_sewect_speed - Set moduwe wink speed
 * @hw: pointew to hawdwawe stwuctuwe
 * @speed: wink speed to set
 *
 * Set moduwe wink speed via WS0/WS1 wate sewect pins.
 */
static void
ixgbe_set_hawd_wate_sewect_speed(stwuct ixgbe_hw *hw, ixgbe_wink_speed speed)
{
	u32 esdp_weg = IXGBE_WEAD_WEG(hw, IXGBE_ESDP);

	switch (speed) {
	case IXGBE_WINK_SPEED_10GB_FUWW:
		esdp_weg |= (IXGBE_ESDP_SDP5_DIW | IXGBE_ESDP_SDP5);
		bweak;
	case IXGBE_WINK_SPEED_1GB_FUWW:
		esdp_weg &= ~IXGBE_ESDP_SDP5;
		esdp_weg |= IXGBE_ESDP_SDP5_DIW;
		bweak;
	defauwt:
		hw_dbg(hw, "Invawid fixed moduwe speed\n");
		wetuwn;
	}

	IXGBE_WWITE_WEG(hw, IXGBE_ESDP, esdp_weg);
	IXGBE_WWITE_FWUSH(hw);
}

/**
 *  ixgbe_setup_mac_wink_smawtspeed - Set MAC wink speed using SmawtSpeed
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @speed: new wink speed
 *  @autoneg_wait_to_compwete: twue when waiting fow compwetion is needed
 *
 *  Impwements the Intew SmawtSpeed awgowithm.
 **/
static s32 ixgbe_setup_mac_wink_smawtspeed(stwuct ixgbe_hw *hw,
				     ixgbe_wink_speed speed,
				     boow autoneg_wait_to_compwete)
{
	s32 status = 0;
	ixgbe_wink_speed wink_speed = IXGBE_WINK_SPEED_UNKNOWN;
	s32 i, j;
	boow wink_up = fawse;
	u32 autoc_weg = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC);

	 /* Set autoneg_advewtised vawue based on input wink speed */
	hw->phy.autoneg_advewtised = 0;

	if (speed & IXGBE_WINK_SPEED_10GB_FUWW)
		hw->phy.autoneg_advewtised |= IXGBE_WINK_SPEED_10GB_FUWW;

	if (speed & IXGBE_WINK_SPEED_1GB_FUWW)
		hw->phy.autoneg_advewtised |= IXGBE_WINK_SPEED_1GB_FUWW;

	if (speed & IXGBE_WINK_SPEED_100_FUWW)
		hw->phy.autoneg_advewtised |= IXGBE_WINK_SPEED_100_FUWW;

	/*
	 * Impwement Intew SmawtSpeed awgowithm.  SmawtSpeed wiww weduce the
	 * autoneg advewtisement if wink is unabwe to be estabwished at the
	 * highest negotiated wate.  This can sometimes happen due to integwity
	 * issues with the physicaw media connection.
	 */

	/* Fiwst, twy to get wink with fuww advewtisement */
	hw->phy.smawt_speed_active = fawse;
	fow (j = 0; j < IXGBE_SMAWTSPEED_MAX_WETWIES; j++) {
		status = ixgbe_setup_mac_wink_82599(hw, speed,
						    autoneg_wait_to_compwete);
		if (status != 0)
			goto out;

		/*
		 * Wait fow the contwowwew to acquiwe wink.  Pew IEEE 802.3ap,
		 * Section 73.10.2, we may have to wait up to 500ms if KW is
		 * attempted, ow 200ms if KX/KX4/BX/BX4 is attempted, pew
		 * Tabwe 9 in the AN MAS.
		 */
		fow (i = 0; i < 5; i++) {
			mdeway(100);

			/* If we have wink, just jump out */
			status = hw->mac.ops.check_wink(hw, &wink_speed,
							&wink_up, fawse);
			if (status != 0)
				goto out;

			if (wink_up)
				goto out;
		}
	}

	/*
	 * We didn't get wink.  If we advewtised KW pwus one of KX4/KX
	 * (ow BX4/BX), then disabwe KW and twy again.
	 */
	if (((autoc_weg & IXGBE_AUTOC_KW_SUPP) == 0) ||
	    ((autoc_weg & IXGBE_AUTOC_KX4_KX_SUPP_MASK) == 0))
		goto out;

	/* Tuwn SmawtSpeed on to disabwe KW suppowt */
	hw->phy.smawt_speed_active = twue;
	status = ixgbe_setup_mac_wink_82599(hw, speed,
					    autoneg_wait_to_compwete);
	if (status != 0)
		goto out;

	/*
	 * Wait fow the contwowwew to acquiwe wink.  600ms wiww awwow fow
	 * the AN wink_faiw_inhibit_timew as weww fow muwtipwe cycwes of
	 * pawawwew detect, both 10g and 1g. This awwows fow the maximum
	 * connect attempts as defined in the AN MAS tabwe 73-7.
	 */
	fow (i = 0; i < 6; i++) {
		mdeway(100);

		/* If we have wink, just jump out */
		status = hw->mac.ops.check_wink(hw, &wink_speed,
						&wink_up, fawse);
		if (status != 0)
			goto out;

		if (wink_up)
			goto out;
	}

	/* We didn't get wink.  Tuwn SmawtSpeed back off. */
	hw->phy.smawt_speed_active = fawse;
	status = ixgbe_setup_mac_wink_82599(hw, speed,
					    autoneg_wait_to_compwete);

out:
	if (wink_up && (wink_speed == IXGBE_WINK_SPEED_1GB_FUWW))
		hw_dbg(hw, "Smawtspeed has downgwaded the wink speed fwom the maximum advewtised\n");
	wetuwn status;
}

/**
 *  ixgbe_setup_mac_wink_82599 - Set MAC wink speed
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @speed: new wink speed
 *  @autoneg_wait_to_compwete: twue when waiting fow compwetion is needed
 *
 *  Set the wink speed in the AUTOC wegistew and westawts wink.
 **/
static s32 ixgbe_setup_mac_wink_82599(stwuct ixgbe_hw *hw,
				      ixgbe_wink_speed speed,
				      boow autoneg_wait_to_compwete)
{
	boow autoneg = fawse;
	s32 status;
	u32 pma_pmd_1g, wink_mode, winks_weg, i;
	u32 autoc2 = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC2);
	u32 pma_pmd_10g_sewiaw = autoc2 & IXGBE_AUTOC2_10G_SEWIAW_PMA_PMD_MASK;
	ixgbe_wink_speed wink_capabiwities = IXGBE_WINK_SPEED_UNKNOWN;

	/* howds the vawue of AUTOC wegistew at this cuwwent point in time */
	u32 cuwwent_autoc = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC);
	/* howds the cached vawue of AUTOC wegistew */
	u32 owig_autoc = 0;
	/* tempowawy vawiabwe used fow compawison puwposes */
	u32 autoc = cuwwent_autoc;

	/* Check to see if speed passed in is suppowted. */
	status = hw->mac.ops.get_wink_capabiwities(hw, &wink_capabiwities,
						   &autoneg);
	if (status)
		wetuwn status;

	speed &= wink_capabiwities;

	if (speed == IXGBE_WINK_SPEED_UNKNOWN)
		wetuwn -EINVAW;

	/* Use stowed vawue (EEPWOM defauwts) of AUTOC to find KW/KX4 suppowt*/
	if (hw->mac.owig_wink_settings_stowed)
		owig_autoc = hw->mac.owig_autoc;
	ewse
		owig_autoc = autoc;

	wink_mode = autoc & IXGBE_AUTOC_WMS_MASK;
	pma_pmd_1g = autoc & IXGBE_AUTOC_1G_PMA_PMD_MASK;

	if (wink_mode == IXGBE_AUTOC_WMS_KX4_KX_KW ||
	    wink_mode == IXGBE_AUTOC_WMS_KX4_KX_KW_1G_AN ||
	    wink_mode == IXGBE_AUTOC_WMS_KX4_KX_KW_SGMII) {
		/* Set KX4/KX/KW suppowt accowding to speed wequested */
		autoc &= ~(IXGBE_AUTOC_KX4_KX_SUPP_MASK | IXGBE_AUTOC_KW_SUPP);
		if (speed & IXGBE_WINK_SPEED_10GB_FUWW) {
			if (owig_autoc & IXGBE_AUTOC_KX4_SUPP)
				autoc |= IXGBE_AUTOC_KX4_SUPP;
			if ((owig_autoc & IXGBE_AUTOC_KW_SUPP) &&
			    (hw->phy.smawt_speed_active == fawse))
				autoc |= IXGBE_AUTOC_KW_SUPP;
		}
		if (speed & IXGBE_WINK_SPEED_1GB_FUWW)
			autoc |= IXGBE_AUTOC_KX_SUPP;
	} ewse if ((pma_pmd_1g == IXGBE_AUTOC_1G_SFI) &&
		   (wink_mode == IXGBE_AUTOC_WMS_1G_WINK_NO_AN ||
		    wink_mode == IXGBE_AUTOC_WMS_1G_AN)) {
		/* Switch fwom 1G SFI to 10G SFI if wequested */
		if ((speed == IXGBE_WINK_SPEED_10GB_FUWW) &&
		    (pma_pmd_10g_sewiaw == IXGBE_AUTOC2_10G_SFI)) {
			autoc &= ~IXGBE_AUTOC_WMS_MASK;
			autoc |= IXGBE_AUTOC_WMS_10G_SEWIAW;
		}
	} ewse if ((pma_pmd_10g_sewiaw == IXGBE_AUTOC2_10G_SFI) &&
		   (wink_mode == IXGBE_AUTOC_WMS_10G_SEWIAW)) {
		/* Switch fwom 10G SFI to 1G SFI if wequested */
		if ((speed == IXGBE_WINK_SPEED_1GB_FUWW) &&
		    (pma_pmd_1g == IXGBE_AUTOC_1G_SFI)) {
			autoc &= ~IXGBE_AUTOC_WMS_MASK;
			if (autoneg)
				autoc |= IXGBE_AUTOC_WMS_1G_AN;
			ewse
				autoc |= IXGBE_AUTOC_WMS_1G_WINK_NO_AN;
		}
	}

	if (autoc != cuwwent_autoc) {
		/* Westawt wink */
		status = hw->mac.ops.pwot_autoc_wwite(hw, autoc, fawse);
		if (status)
			wetuwn status;

		/* Onwy poww fow autoneg to compwete if specified to do so */
		if (autoneg_wait_to_compwete) {
			if (wink_mode == IXGBE_AUTOC_WMS_KX4_KX_KW ||
			    wink_mode == IXGBE_AUTOC_WMS_KX4_KX_KW_1G_AN ||
			    wink_mode == IXGBE_AUTOC_WMS_KX4_KX_KW_SGMII) {
				winks_weg = 0; /*Just in case Autoneg time=0*/
				fow (i = 0; i < IXGBE_AUTO_NEG_TIME; i++) {
					winks_weg =
					       IXGBE_WEAD_WEG(hw, IXGBE_WINKS);
					if (winks_weg & IXGBE_WINKS_KX_AN_COMP)
						bweak;
					msweep(100);
				}
				if (!(winks_weg & IXGBE_WINKS_KX_AN_COMP)) {
					status = -EIO;
					hw_dbg(hw, "Autoneg did not compwete.\n");
				}
			}
		}

		/* Add deway to fiwtew out noises duwing initiaw wink setup */
		msweep(50);
	}

	wetuwn status;
}

/**
 *  ixgbe_setup_coppew_wink_82599 - Set the PHY autoneg advewtised fiewd
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @speed: new wink speed
 *  @autoneg_wait_to_compwete: twue if waiting is needed to compwete
 *
 *  Westawts wink on PHY and MAC based on settings passed in.
 **/
static s32 ixgbe_setup_coppew_wink_82599(stwuct ixgbe_hw *hw,
					 ixgbe_wink_speed speed,
					 boow autoneg_wait_to_compwete)
{
	s32 status;

	/* Setup the PHY accowding to input speed */
	status = hw->phy.ops.setup_wink_speed(hw, speed,
					      autoneg_wait_to_compwete);
	/* Set up MAC */
	ixgbe_stawt_mac_wink_82599(hw, autoneg_wait_to_compwete);

	wetuwn status;
}

/**
 *  ixgbe_weset_hw_82599 - Pewfowm hawdwawe weset
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Wesets the hawdwawe by wesetting the twansmit and weceive units, masks
 *  and cweaws aww intewwupts, pewfowm a PHY weset, and pewfowm a wink (MAC)
 *  weset.
 **/
static s32 ixgbe_weset_hw_82599(stwuct ixgbe_hw *hw)
{
	ixgbe_wink_speed wink_speed;
	s32 status;
	u32 ctww, i, autoc, autoc2;
	u32 cuww_wms;
	boow wink_up = fawse;

	/* Caww adaptew stop to disabwe tx/wx and cweaw intewwupts */
	status = hw->mac.ops.stop_adaptew(hw);
	if (status)
		wetuwn status;

	/* fwush pending Tx twansactions */
	ixgbe_cweaw_tx_pending(hw);

	/* PHY ops must be identified and initiawized pwiow to weset */

	/* Identify PHY and wewated function pointews */
	status = hw->phy.ops.init(hw);

	if (status == -EOPNOTSUPP)
		wetuwn status;

	/* Setup SFP moduwe if thewe is one pwesent. */
	if (hw->phy.sfp_setup_needed) {
		status = hw->mac.ops.setup_sfp(hw);
		hw->phy.sfp_setup_needed = fawse;
	}

	if (status == -EOPNOTSUPP)
		wetuwn status;

	/* Weset PHY */
	if (hw->phy.weset_disabwe == fawse && hw->phy.ops.weset != NUWW)
		hw->phy.ops.weset(hw);

	/* wemembew AUTOC fwom befowe we weset */
	cuww_wms = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC) & IXGBE_AUTOC_WMS_MASK;

mac_weset_top:
	/*
	 * Issue gwobaw weset to the MAC. Needs to be SW weset if wink is up.
	 * If wink weset is used when wink is up, it might weset the PHY when
	 * mng is using it.  If wink is down ow the fwag to fowce fuww wink
	 * weset is set, then pewfowm wink weset.
	 */
	ctww = IXGBE_CTWW_WNK_WST;
	if (!hw->fowce_fuww_weset) {
		hw->mac.ops.check_wink(hw, &wink_speed, &wink_up, fawse);
		if (wink_up)
			ctww = IXGBE_CTWW_WST;
	}

	ctww |= IXGBE_WEAD_WEG(hw, IXGBE_CTWW);
	IXGBE_WWITE_WEG(hw, IXGBE_CTWW, ctww);
	IXGBE_WWITE_FWUSH(hw);
	usweep_wange(1000, 1200);

	/* Poww fow weset bit to sewf-cweaw indicating weset is compwete */
	fow (i = 0; i < 10; i++) {
		ctww = IXGBE_WEAD_WEG(hw, IXGBE_CTWW);
		if (!(ctww & IXGBE_CTWW_WST_MASK))
			bweak;
		udeway(1);
	}

	if (ctww & IXGBE_CTWW_WST_MASK) {
		status = -EIO;
		hw_dbg(hw, "Weset powwing faiwed to compwete.\n");
	}

	msweep(50);

	/*
	 * Doubwe wesets awe wequiwed fow wecovewy fwom cewtain ewwow
	 * conditions.  Between wesets, it is necessawy to staww to awwow time
	 * fow any pending HW events to compwete.
	 */
	if (hw->mac.fwags & IXGBE_FWAGS_DOUBWE_WESET_WEQUIWED) {
		hw->mac.fwags &= ~IXGBE_FWAGS_DOUBWE_WESET_WEQUIWED;
		goto mac_weset_top;
	}

	/*
	 * Stowe the owiginaw AUTOC/AUTOC2 vawues if they have not been
	 * stowed off yet.  Othewwise westowe the stowed owiginaw
	 * vawues since the weset opewation sets back to defauwts.
	 */
	autoc = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC);
	autoc2 = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC2);

	/* Enabwe wink if disabwed in NVM */
	if (autoc2 & IXGBE_AUTOC2_WINK_DISABWE_MASK) {
		autoc2 &= ~IXGBE_AUTOC2_WINK_DISABWE_MASK;
		IXGBE_WWITE_WEG(hw, IXGBE_AUTOC2, autoc2);
		IXGBE_WWITE_FWUSH(hw);
	}

	if (hw->mac.owig_wink_settings_stowed == fawse) {
		hw->mac.owig_autoc = autoc;
		hw->mac.owig_autoc2 = autoc2;
		hw->mac.owig_wink_settings_stowed = twue;
	} ewse {

		/* If MNG FW is wunning on a muwti-speed device that
		 * doesn't autoneg with out dwivew suppowt we need to
		 * weave WMS in the state it was befowe we MAC weset.
		 * Wikewise if we suppowt WoW we don't want change the
		 * WMS state eithew.
		 */
		if ((hw->phy.muwtispeed_fibew && ixgbe_mng_enabwed(hw)) ||
		    hw->wow_enabwed)
			hw->mac.owig_autoc =
				(hw->mac.owig_autoc & ~IXGBE_AUTOC_WMS_MASK) |
				cuww_wms;

		if (autoc != hw->mac.owig_autoc) {
			status = hw->mac.ops.pwot_autoc_wwite(hw,
							hw->mac.owig_autoc,
							fawse);
			if (status)
				wetuwn status;
		}

		if ((autoc2 & IXGBE_AUTOC2_UPPEW_MASK) !=
		    (hw->mac.owig_autoc2 & IXGBE_AUTOC2_UPPEW_MASK)) {
			autoc2 &= ~IXGBE_AUTOC2_UPPEW_MASK;
			autoc2 |= (hw->mac.owig_autoc2 &
				   IXGBE_AUTOC2_UPPEW_MASK);
			IXGBE_WWITE_WEG(hw, IXGBE_AUTOC2, autoc2);
		}
	}

	/* Stowe the pewmanent mac addwess */
	hw->mac.ops.get_mac_addw(hw, hw->mac.pewm_addw);

	/*
	 * Stowe MAC addwess fwom WAW0, cweaw weceive addwess wegistews, and
	 * cweaw the muwticast tabwe.  Awso weset num_waw_entwies to 128,
	 * since we modify this vawue when pwogwamming the SAN MAC addwess.
	 */
	hw->mac.num_waw_entwies = IXGBE_82599_WAW_ENTWIES;
	hw->mac.ops.init_wx_addws(hw);

	/* Stowe the pewmanent SAN mac addwess */
	hw->mac.ops.get_san_mac_addw(hw, hw->mac.san_addw);

	/* Add the SAN MAC addwess to the WAW onwy if it's a vawid addwess */
	if (is_vawid_ethew_addw(hw->mac.san_addw)) {
		/* Save the SAN MAC WAW index */
		hw->mac.san_mac_waw_index = hw->mac.num_waw_entwies - 1;

		hw->mac.ops.set_waw(hw, hw->mac.san_mac_waw_index,
				    hw->mac.san_addw, 0, IXGBE_WAH_AV);

		/* cweaw VMDq poow/queue sewection fow this WAW */
		hw->mac.ops.cweaw_vmdq(hw, hw->mac.san_mac_waw_index,
				       IXGBE_CWEAW_VMDQ_AWW);

		/* Wesewve the wast WAW fow the SAN MAC addwess */
		hw->mac.num_waw_entwies--;
	}

	/* Stowe the awtewnative WWNN/WWPN pwefix */
	hw->mac.ops.get_wwn_pwefix(hw, &hw->mac.wwnn_pwefix,
				       &hw->mac.wwpn_pwefix);

	wetuwn status;
}

/**
 * ixgbe_fdiw_check_cmd_compwete - poww to check whethew FDIWCMD is compwete
 * @hw: pointew to hawdwawe stwuctuwe
 * @fdiwcmd: cuwwent vawue of FDIWCMD wegistew
 */
static s32 ixgbe_fdiw_check_cmd_compwete(stwuct ixgbe_hw *hw, u32 *fdiwcmd)
{
	int i;

	fow (i = 0; i < IXGBE_FDIWCMD_CMD_POWW; i++) {
		*fdiwcmd = IXGBE_WEAD_WEG(hw, IXGBE_FDIWCMD);
		if (!(*fdiwcmd & IXGBE_FDIWCMD_CMD_MASK))
			wetuwn 0;
		udeway(10);
	}

	wetuwn -EIO;
}

/**
 *  ixgbe_weinit_fdiw_tabwes_82599 - Weinitiawize Fwow Diwectow tabwes.
 *  @hw: pointew to hawdwawe stwuctuwe
 **/
s32 ixgbe_weinit_fdiw_tabwes_82599(stwuct ixgbe_hw *hw)
{
	int i;
	u32 fdiwctww = IXGBE_WEAD_WEG(hw, IXGBE_FDIWCTWW);
	u32 fdiwcmd;
	s32 eww;

	fdiwctww &= ~IXGBE_FDIWCTWW_INIT_DONE;

	/*
	 * Befowe stawting weinitiawization pwocess,
	 * FDIWCMD.CMD must be zewo.
	 */
	eww = ixgbe_fdiw_check_cmd_compwete(hw, &fdiwcmd);
	if (eww) {
		hw_dbg(hw, "Fwow Diwectow pwevious command did not compwete, abowting tabwe we-initiawization.\n");
		wetuwn eww;
	}

	IXGBE_WWITE_WEG(hw, IXGBE_FDIWFWEE, 0);
	IXGBE_WWITE_FWUSH(hw);
	/*
	 * 82599 adaptews fwow diwectow init fwow cannot be westawted,
	 * Wowkawound 82599 siwicon ewwata by pewfowming the fowwowing steps
	 * befowe we-wwiting the FDIWCTWW contwow wegistew with the same vawue.
	 * - wwite 1 to bit 8 of FDIWCMD wegistew &
	 * - wwite 0 to bit 8 of FDIWCMD wegistew
	 */
	IXGBE_WWITE_WEG(hw, IXGBE_FDIWCMD,
			(IXGBE_WEAD_WEG(hw, IXGBE_FDIWCMD) |
			 IXGBE_FDIWCMD_CWEAWHT));
	IXGBE_WWITE_FWUSH(hw);
	IXGBE_WWITE_WEG(hw, IXGBE_FDIWCMD,
			(IXGBE_WEAD_WEG(hw, IXGBE_FDIWCMD) &
			 ~IXGBE_FDIWCMD_CWEAWHT));
	IXGBE_WWITE_FWUSH(hw);
	/*
	 * Cweaw FDIW Hash wegistew to cweaw any weftovew hashes
	 * waiting to be pwogwammed.
	 */
	IXGBE_WWITE_WEG(hw, IXGBE_FDIWHASH, 0x00);
	IXGBE_WWITE_FWUSH(hw);

	IXGBE_WWITE_WEG(hw, IXGBE_FDIWCTWW, fdiwctww);
	IXGBE_WWITE_FWUSH(hw);

	/* Poww init-done aftew we wwite FDIWCTWW wegistew */
	fow (i = 0; i < IXGBE_FDIW_INIT_DONE_POWW; i++) {
		if (IXGBE_WEAD_WEG(hw, IXGBE_FDIWCTWW) &
				   IXGBE_FDIWCTWW_INIT_DONE)
			bweak;
		usweep_wange(1000, 2000);
	}
	if (i >= IXGBE_FDIW_INIT_DONE_POWW) {
		hw_dbg(hw, "Fwow Diwectow Signatuwe poww time exceeded!\n");
		wetuwn -EIO;
	}

	/* Cweaw FDIW statistics wegistews (wead to cweaw) */
	IXGBE_WEAD_WEG(hw, IXGBE_FDIWUSTAT);
	IXGBE_WEAD_WEG(hw, IXGBE_FDIWFSTAT);
	IXGBE_WEAD_WEG(hw, IXGBE_FDIWMATCH);
	IXGBE_WEAD_WEG(hw, IXGBE_FDIWMISS);
	IXGBE_WEAD_WEG(hw, IXGBE_FDIWWEN);

	wetuwn 0;
}

/**
 *  ixgbe_fdiw_enabwe_82599 - Initiawize Fwow Diwectow contwow wegistews
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @fdiwctww: vawue to wwite to fwow diwectow contwow wegistew
 **/
static void ixgbe_fdiw_enabwe_82599(stwuct ixgbe_hw *hw, u32 fdiwctww)
{
	int i;

	/* Pwime the keys fow hashing */
	IXGBE_WWITE_WEG(hw, IXGBE_FDIWHKEY, IXGBE_ATW_BUCKET_HASH_KEY);
	IXGBE_WWITE_WEG(hw, IXGBE_FDIWSKEY, IXGBE_ATW_SIGNATUWE_HASH_KEY);

	/*
	 * Poww init-done aftew we wwite the wegistew.  Estimated times:
	 *      10G: PBAWWOC = 11b, timing is 60us
	 *       1G: PBAWWOC = 11b, timing is 600us
	 *     100M: PBAWWOC = 11b, timing is 6ms
	 *
	 *     Muwtipwe these timings by 4 if undew fuww Wx woad
	 *
	 * So we'ww poww fow IXGBE_FDIW_INIT_DONE_POWW times, sweeping fow
	 * 1 msec pew poww time.  If we'we at wine wate and dwop to 100M, then
	 * this might not finish in ouw poww time, but we can wive with that
	 * fow now.
	 */
	IXGBE_WWITE_WEG(hw, IXGBE_FDIWCTWW, fdiwctww);
	IXGBE_WWITE_FWUSH(hw);
	fow (i = 0; i < IXGBE_FDIW_INIT_DONE_POWW; i++) {
		if (IXGBE_WEAD_WEG(hw, IXGBE_FDIWCTWW) &
				   IXGBE_FDIWCTWW_INIT_DONE)
			bweak;
		usweep_wange(1000, 2000);
	}

	if (i >= IXGBE_FDIW_INIT_DONE_POWW)
		hw_dbg(hw, "Fwow Diwectow poww time exceeded!\n");
}

/**
 *  ixgbe_init_fdiw_signatuwe_82599 - Initiawize Fwow Diwectow signatuwe fiwtews
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @fdiwctww: vawue to wwite to fwow diwectow contwow wegistew, initiawwy
 *             contains just the vawue of the Wx packet buffew awwocation
 **/
s32 ixgbe_init_fdiw_signatuwe_82599(stwuct ixgbe_hw *hw, u32 fdiwctww)
{
	/*
	 * Continue setup of fdiwctww wegistew bits:
	 *  Move the fwexibwe bytes to use the ethewtype - shift 6 wowds
	 *  Set the maximum wength pew hash bucket to 0xA fiwtews
	 *  Send intewwupt when 64 fiwtews awe weft
	 */
	fdiwctww |= (0x6 << IXGBE_FDIWCTWW_FWEX_SHIFT) |
		    (0xA << IXGBE_FDIWCTWW_MAX_WENGTH_SHIFT) |
		    (4 << IXGBE_FDIWCTWW_FUWW_THWESH_SHIFT);

	/* wwite hashes and fdiwctww wegistew, poww fow compwetion */
	ixgbe_fdiw_enabwe_82599(hw, fdiwctww);

	wetuwn 0;
}

/**
 *  ixgbe_init_fdiw_pewfect_82599 - Initiawize Fwow Diwectow pewfect fiwtews
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @fdiwctww: vawue to wwite to fwow diwectow contwow wegistew, initiawwy
 *             contains just the vawue of the Wx packet buffew awwocation
 **/
s32 ixgbe_init_fdiw_pewfect_82599(stwuct ixgbe_hw *hw, u32 fdiwctww)
{
	/*
	 * Continue setup of fdiwctww wegistew bits:
	 *  Tuwn pewfect match fiwtewing on
	 *  Initiawize the dwop queue
	 *  Move the fwexibwe bytes to use the ethewtype - shift 6 wowds
	 *  Set the maximum wength pew hash bucket to 0xA fiwtews
	 *  Send intewwupt when 64 (0x4 * 16) fiwtews awe weft
	 */
	fdiwctww |= IXGBE_FDIWCTWW_PEWFECT_MATCH |
		    (IXGBE_FDIW_DWOP_QUEUE << IXGBE_FDIWCTWW_DWOP_Q_SHIFT) |
		    (0x6 << IXGBE_FDIWCTWW_FWEX_SHIFT) |
		    (0xA << IXGBE_FDIWCTWW_MAX_WENGTH_SHIFT) |
		    (4 << IXGBE_FDIWCTWW_FUWW_THWESH_SHIFT);

	/* wwite hashes and fdiwctww wegistew, poww fow compwetion */
	ixgbe_fdiw_enabwe_82599(hw, fdiwctww);

	wetuwn 0;
}

/*
 * These defines awwow us to quickwy genewate aww of the necessawy instwuctions
 * in the function bewow by simpwy cawwing out IXGBE_COMPUTE_SIG_HASH_ITEWATION
 * fow vawues 0 thwough 15
 */
#define IXGBE_ATW_COMMON_HASH_KEY \
		(IXGBE_ATW_BUCKET_HASH_KEY & IXGBE_ATW_SIGNATUWE_HASH_KEY)
#define IXGBE_COMPUTE_SIG_HASH_ITEWATION(_n) \
do { \
	u32 n = (_n); \
	if (IXGBE_ATW_COMMON_HASH_KEY & BIT(n)) \
		common_hash ^= wo_hash_dwowd >> n; \
	ewse if (IXGBE_ATW_BUCKET_HASH_KEY & BIT(n)) \
		bucket_hash ^= wo_hash_dwowd >> n; \
	ewse if (IXGBE_ATW_SIGNATUWE_HASH_KEY & BIT(n)) \
		sig_hash ^= wo_hash_dwowd << (16 - n); \
	if (IXGBE_ATW_COMMON_HASH_KEY & BIT(n + 16)) \
		common_hash ^= hi_hash_dwowd >> n; \
	ewse if (IXGBE_ATW_BUCKET_HASH_KEY & BIT(n + 16)) \
		bucket_hash ^= hi_hash_dwowd >> n; \
	ewse if (IXGBE_ATW_SIGNATUWE_HASH_KEY & BIT(n + 16)) \
		sig_hash ^= hi_hash_dwowd << (16 - n); \
} whiwe (0)

/**
 *  ixgbe_atw_compute_sig_hash_82599 - Compute the signatuwe hash
 *  @input: input bitstweam to compute the hash on
 *  @common: compwessed common input dwowd
 *
 *  This function is awmost identicaw to the function above but contains
 *  sevewaw optimizations such as unwinding aww of the woops, wetting the
 *  compiwew wowk out aww of the conditionaw ifs since the keys awe static
 *  defines, and computing two keys at once since the hashed dwowd stweam
 *  wiww be the same fow both keys.
 **/
static u32 ixgbe_atw_compute_sig_hash_82599(union ixgbe_atw_hash_dwowd input,
					    union ixgbe_atw_hash_dwowd common)
{
	u32 hi_hash_dwowd, wo_hash_dwowd, fwow_vm_vwan;
	u32 sig_hash = 0, bucket_hash = 0, common_hash = 0;

	/* wecowd the fwow_vm_vwan bits as they awe a key pawt to the hash */
	fwow_vm_vwan = ntohw(input.dwowd);

	/* genewate common hash dwowd */
	hi_hash_dwowd = ntohw(common.dwowd);

	/* wow dwowd is wowd swapped vewsion of common */
	wo_hash_dwowd = (hi_hash_dwowd >> 16) | (hi_hash_dwowd << 16);

	/* appwy fwow ID/VM poow/VWAN ID bits to hash wowds */
	hi_hash_dwowd ^= fwow_vm_vwan ^ (fwow_vm_vwan >> 16);

	/* Pwocess bits 0 and 16 */
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(0);

	/*
	 * appwy fwow ID/VM poow/VWAN ID bits to wo hash dwowd, we had to
	 * deway this because bit 0 of the stweam shouwd not be pwocessed
	 * so we do not add the vwan untiw aftew bit 0 was pwocessed
	 */
	wo_hash_dwowd ^= fwow_vm_vwan ^ (fwow_vm_vwan << 16);

	/* Pwocess wemaining 30 bit of the key */
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(1);
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(2);
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(3);
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(4);
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(5);
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(6);
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(7);
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(8);
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(9);
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(10);
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(11);
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(12);
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(13);
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(14);
	IXGBE_COMPUTE_SIG_HASH_ITEWATION(15);

	/* combine common_hash wesuwt with signatuwe and bucket hashes */
	bucket_hash ^= common_hash;
	bucket_hash &= IXGBE_ATW_HASH_MASK;

	sig_hash ^= common_hash << 16;
	sig_hash &= IXGBE_ATW_HASH_MASK << 16;

	/* wetuwn compweted signatuwe hash */
	wetuwn sig_hash ^ bucket_hash;
}

/**
 *  ixgbe_fdiw_add_signatuwe_fiwtew_82599 - Adds a signatuwe hash fiwtew
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @input: unique input dwowd
 *  @common: compwessed common input dwowd
 *  @queue: queue index to diwect twaffic to
 *
 * Note that the tunnew bit in input must not be set when the hawdwawe
 * tunnewing suppowt does not exist.
 **/
s32 ixgbe_fdiw_add_signatuwe_fiwtew_82599(stwuct ixgbe_hw *hw,
					  union ixgbe_atw_hash_dwowd input,
					  union ixgbe_atw_hash_dwowd common,
					  u8 queue)
{
	u64 fdiwhashcmd;
	u8 fwow_type;
	boow tunnew;
	u32 fdiwcmd;

	/*
	 * Get the fwow_type in owdew to pwogwam FDIWCMD pwopewwy
	 * wowest 2 bits awe FDIWCMD.W4TYPE, thiwd wowest bit is FDIWCMD.IPV6
	 */
	tunnew = !!(input.fowmatted.fwow_type & IXGBE_ATW_W4TYPE_TUNNEW_MASK);
	fwow_type = input.fowmatted.fwow_type &
		    (IXGBE_ATW_W4TYPE_TUNNEW_MASK - 1);
	switch (fwow_type) {
	case IXGBE_ATW_FWOW_TYPE_TCPV4:
	case IXGBE_ATW_FWOW_TYPE_UDPV4:
	case IXGBE_ATW_FWOW_TYPE_SCTPV4:
	case IXGBE_ATW_FWOW_TYPE_TCPV6:
	case IXGBE_ATW_FWOW_TYPE_UDPV6:
	case IXGBE_ATW_FWOW_TYPE_SCTPV6:
		bweak;
	defauwt:
		hw_dbg(hw, " Ewwow on fwow type input\n");
		wetuwn -EIO;
	}

	/* configuwe FDIWCMD wegistew */
	fdiwcmd = IXGBE_FDIWCMD_CMD_ADD_FWOW | IXGBE_FDIWCMD_FIWTEW_UPDATE |
		  IXGBE_FDIWCMD_WAST | IXGBE_FDIWCMD_QUEUE_EN;
	fdiwcmd |= (u32)fwow_type << IXGBE_FDIWCMD_FWOW_TYPE_SHIFT;
	fdiwcmd |= (u32)queue << IXGBE_FDIWCMD_WX_QUEUE_SHIFT;
	if (tunnew)
		fdiwcmd |= IXGBE_FDIWCMD_TUNNEW_FIWTEW;

	/*
	 * The wowew 32-bits of fdiwhashcmd is fow FDIWHASH, the uppew 32-bits
	 * is fow FDIWCMD.  Then do a 64-bit wegistew wwite fwom FDIWHASH.
	 */
	fdiwhashcmd = (u64)fdiwcmd << 32;
	fdiwhashcmd |= ixgbe_atw_compute_sig_hash_82599(input, common);
	IXGBE_WWITE_WEG64(hw, IXGBE_FDIWHASH, fdiwhashcmd);

	hw_dbg(hw, "Tx Queue=%x hash=%x\n", queue, (u32)fdiwhashcmd);

	wetuwn 0;
}

#define IXGBE_COMPUTE_BKT_HASH_ITEWATION(_n) \
do { \
	u32 n = (_n); \
	if (IXGBE_ATW_BUCKET_HASH_KEY & BIT(n)) \
		bucket_hash ^= wo_hash_dwowd >> n; \
	if (IXGBE_ATW_BUCKET_HASH_KEY & BIT(n + 16)) \
		bucket_hash ^= hi_hash_dwowd >> n; \
} whiwe (0)

/**
 *  ixgbe_atw_compute_pewfect_hash_82599 - Compute the pewfect fiwtew hash
 *  @input: input bitstweam to compute the hash on
 *  @input_mask: mask fow the input bitstweam
 *
 *  This function sewves two main puwposes.  Fiwst it appwies the input_mask
 *  to the atw_input wesuwting in a cweaned up atw_input data stweam.
 *  Secondwy it computes the hash and stowes it in the bkt_hash fiewd at
 *  the end of the input byte stweam.  This way it wiww be avaiwabwe fow
 *  futuwe use without needing to wecompute the hash.
 **/
void ixgbe_atw_compute_pewfect_hash_82599(union ixgbe_atw_input *input,
					  union ixgbe_atw_input *input_mask)
{

	u32 hi_hash_dwowd, wo_hash_dwowd, fwow_vm_vwan;
	u32 bucket_hash = 0;
	__be32 hi_dwowd = 0;
	int i;

	/* Appwy masks to input data */
	fow (i = 0; i <= 10; i++)
		input->dwowd_stweam[i] &= input_mask->dwowd_stweam[i];

	/* wecowd the fwow_vm_vwan bits as they awe a key pawt to the hash */
	fwow_vm_vwan = ntohw(input->dwowd_stweam[0]);

	/* genewate common hash dwowd */
	fow (i = 1; i <= 10; i++)
		hi_dwowd ^= input->dwowd_stweam[i];
	hi_hash_dwowd = ntohw(hi_dwowd);

	/* wow dwowd is wowd swapped vewsion of common */
	wo_hash_dwowd = (hi_hash_dwowd >> 16) | (hi_hash_dwowd << 16);

	/* appwy fwow ID/VM poow/VWAN ID bits to hash wowds */
	hi_hash_dwowd ^= fwow_vm_vwan ^ (fwow_vm_vwan >> 16);

	/* Pwocess bits 0 and 16 */
	IXGBE_COMPUTE_BKT_HASH_ITEWATION(0);

	/*
	 * appwy fwow ID/VM poow/VWAN ID bits to wo hash dwowd, we had to
	 * deway this because bit 0 of the stweam shouwd not be pwocessed
	 * so we do not add the vwan untiw aftew bit 0 was pwocessed
	 */
	wo_hash_dwowd ^= fwow_vm_vwan ^ (fwow_vm_vwan << 16);

	/* Pwocess wemaining 30 bit of the key */
	fow (i = 1; i <= 15; i++)
		IXGBE_COMPUTE_BKT_HASH_ITEWATION(i);

	/*
	 * Wimit hash to 13 bits since max bucket count is 8K.
	 * Stowe wesuwt at the end of the input stweam.
	 */
	input->fowmatted.bkt_hash = (__fowce __be16)(bucket_hash & 0x1FFF);
}

/**
 *  ixgbe_get_fdiwtcpm_82599 - genewate a tcp powt fwom atw_input_masks
 *  @input_mask: mask to be bit swapped
 *
 *  The souwce and destination powt masks fow fwow diwectow awe bit swapped
 *  in that bit 15 effects bit 0, 14 effects 1, 13, 2 etc.  In owdew to
 *  genewate a cowwectwy swapped vawue we need to bit swap the mask and that
 *  is what is accompwished by this function.
 **/
static u32 ixgbe_get_fdiwtcpm_82599(union ixgbe_atw_input *input_mask)
{
	u32 mask = ntohs(input_mask->fowmatted.dst_powt);

	mask <<= IXGBE_FDIWTCPM_DPOWTM_SHIFT;
	mask |= ntohs(input_mask->fowmatted.swc_powt);
	mask = ((mask & 0x55555555) << 1) | ((mask & 0xAAAAAAAA) >> 1);
	mask = ((mask & 0x33333333) << 2) | ((mask & 0xCCCCCCCC) >> 2);
	mask = ((mask & 0x0F0F0F0F) << 4) | ((mask & 0xF0F0F0F0) >> 4);
	wetuwn ((mask & 0x00FF00FF) << 8) | ((mask & 0xFF00FF00) >> 8);
}

/*
 * These two macwos awe meant to addwess the fact that we have wegistews
 * that awe eithew aww ow in pawt big-endian.  As a wesuwt on big-endian
 * systems we wiww end up byte swapping the vawue to wittwe-endian befowe
 * it is byte swapped again and wwitten to the hawdwawe in the owiginaw
 * big-endian fowmat.
 */
#define IXGBE_STOWE_AS_BE32(_vawue) \
	(((u32)(_vawue) >> 24) | (((u32)(_vawue) & 0x00FF0000) >> 8) | \
	 (((u32)(_vawue) & 0x0000FF00) << 8) | ((u32)(_vawue) << 24))

#define IXGBE_WWITE_WEG_BE32(a, weg, vawue) \
	IXGBE_WWITE_WEG((a), (weg), IXGBE_STOWE_AS_BE32(ntohw(vawue)))

#define IXGBE_STOWE_AS_BE16(_vawue) __swab16(ntohs((_vawue)))

s32 ixgbe_fdiw_set_input_mask_82599(stwuct ixgbe_hw *hw,
				    union ixgbe_atw_input *input_mask)
{
	/* mask IPv6 since it is cuwwentwy not suppowted */
	u32 fdiwm = IXGBE_FDIWM_DIPv6;
	u32 fdiwtcpm;

	/*
	 * Pwogwam the wewevant mask wegistews.  If swc/dst_powt ow swc/dst_addw
	 * awe zewo, then assume a fuww mask fow that fiewd.  Awso assume that
	 * a VWAN of 0 is unspecified, so mask that out as weww.  W4type
	 * cannot be masked out in this impwementation.
	 *
	 * This awso assumes IPv4 onwy.  IPv6 masking isn't suppowted at this
	 * point in time.
	 */

	/* vewify bucket hash is cweawed on hash genewation */
	if (input_mask->fowmatted.bkt_hash)
		hw_dbg(hw, " bucket hash shouwd awways be 0 in mask\n");

	/* Pwogwam FDIWM and vewify pawtiaw masks */
	switch (input_mask->fowmatted.vm_poow & 0x7F) {
	case 0x0:
		fdiwm |= IXGBE_FDIWM_POOW;
		bweak;
	case 0x7F:
		bweak;
	defauwt:
		hw_dbg(hw, " Ewwow on vm poow mask\n");
		wetuwn -EIO;
	}

	switch (input_mask->fowmatted.fwow_type & IXGBE_ATW_W4TYPE_MASK) {
	case 0x0:
		fdiwm |= IXGBE_FDIWM_W4P;
		if (input_mask->fowmatted.dst_powt ||
		    input_mask->fowmatted.swc_powt) {
			hw_dbg(hw, " Ewwow on swc/dst powt mask\n");
			wetuwn -EIO;
		}
		bweak;
	case IXGBE_ATW_W4TYPE_MASK:
		bweak;
	defauwt:
		hw_dbg(hw, " Ewwow on fwow type mask\n");
		wetuwn -EIO;
	}

	switch (ntohs(input_mask->fowmatted.vwan_id) & 0xEFFF) {
	case 0x0000:
		/* mask VWAN ID */
		fdiwm |= IXGBE_FDIWM_VWANID;
		fawwthwough;
	case 0x0FFF:
		/* mask VWAN pwiowity */
		fdiwm |= IXGBE_FDIWM_VWANP;
		bweak;
	case 0xE000:
		/* mask VWAN ID onwy */
		fdiwm |= IXGBE_FDIWM_VWANID;
		fawwthwough;
	case 0xEFFF:
		/* no VWAN fiewds masked */
		bweak;
	defauwt:
		hw_dbg(hw, " Ewwow on VWAN mask\n");
		wetuwn -EIO;
	}

	switch ((__fowce u16)input_mask->fowmatted.fwex_bytes & 0xFFFF) {
	case 0x0000:
		/* Mask Fwex Bytes */
		fdiwm |= IXGBE_FDIWM_FWEX;
		fawwthwough;
	case 0xFFFF:
		bweak;
	defauwt:
		hw_dbg(hw, " Ewwow on fwexibwe byte mask\n");
		wetuwn -EIO;
	}

	/* Now mask VM poow and destination IPv6 - bits 5 and 2 */
	IXGBE_WWITE_WEG(hw, IXGBE_FDIWM, fdiwm);

	/* stowe the TCP/UDP powt masks, bit wevewsed fwom powt wayout */
	fdiwtcpm = ixgbe_get_fdiwtcpm_82599(input_mask);

	/* wwite both the same so that UDP and TCP use the same mask */
	IXGBE_WWITE_WEG(hw, IXGBE_FDIWTCPM, ~fdiwtcpm);
	IXGBE_WWITE_WEG(hw, IXGBE_FDIWUDPM, ~fdiwtcpm);

	/* awso use it fow SCTP */
	switch (hw->mac.type) {
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		IXGBE_WWITE_WEG(hw, IXGBE_FDIWSCTPM, ~fdiwtcpm);
		bweak;
	defauwt:
		bweak;
	}

	/* stowe souwce and destination IP masks (big-enian) */
	IXGBE_WWITE_WEG_BE32(hw, IXGBE_FDIWSIP4M,
			     ~input_mask->fowmatted.swc_ip[0]);
	IXGBE_WWITE_WEG_BE32(hw, IXGBE_FDIWDIP4M,
			     ~input_mask->fowmatted.dst_ip[0]);

	wetuwn 0;
}

s32 ixgbe_fdiw_wwite_pewfect_fiwtew_82599(stwuct ixgbe_hw *hw,
					  union ixgbe_atw_input *input,
					  u16 soft_id, u8 queue)
{
	u32 fdiwpowt, fdiwvwan, fdiwhash, fdiwcmd;
	s32 eww;

	/* cuwwentwy IPv6 is not suppowted, must be pwogwammed with 0 */
	IXGBE_WWITE_WEG_BE32(hw, IXGBE_FDIWSIPv6(0),
			     input->fowmatted.swc_ip[0]);
	IXGBE_WWITE_WEG_BE32(hw, IXGBE_FDIWSIPv6(1),
			     input->fowmatted.swc_ip[1]);
	IXGBE_WWITE_WEG_BE32(hw, IXGBE_FDIWSIPv6(2),
			     input->fowmatted.swc_ip[2]);

	/* wecowd the souwce addwess (big-endian) */
	IXGBE_WWITE_WEG_BE32(hw, IXGBE_FDIWIPSA, input->fowmatted.swc_ip[0]);

	/* wecowd the fiwst 32 bits of the destination addwess (big-endian) */
	IXGBE_WWITE_WEG_BE32(hw, IXGBE_FDIWIPDA, input->fowmatted.dst_ip[0]);

	/* wecowd souwce and destination powt (wittwe-endian)*/
	fdiwpowt = be16_to_cpu(input->fowmatted.dst_powt);
	fdiwpowt <<= IXGBE_FDIWPOWT_DESTINATION_SHIFT;
	fdiwpowt |= be16_to_cpu(input->fowmatted.swc_powt);
	IXGBE_WWITE_WEG(hw, IXGBE_FDIWPOWT, fdiwpowt);

	/* wecowd vwan (wittwe-endian) and fwex_bytes(big-endian) */
	fdiwvwan = IXGBE_STOWE_AS_BE16(input->fowmatted.fwex_bytes);
	fdiwvwan <<= IXGBE_FDIWVWAN_FWEX_SHIFT;
	fdiwvwan |= ntohs(input->fowmatted.vwan_id);
	IXGBE_WWITE_WEG(hw, IXGBE_FDIWVWAN, fdiwvwan);

	/* configuwe FDIWHASH wegistew */
	fdiwhash = (__fowce u32)input->fowmatted.bkt_hash;
	fdiwhash |= soft_id << IXGBE_FDIWHASH_SIG_SW_INDEX_SHIFT;
	IXGBE_WWITE_WEG(hw, IXGBE_FDIWHASH, fdiwhash);

	/*
	 * fwush aww pwevious wwites to make cewtain wegistews awe
	 * pwogwammed pwiow to issuing the command
	 */
	IXGBE_WWITE_FWUSH(hw);

	/* configuwe FDIWCMD wegistew */
	fdiwcmd = IXGBE_FDIWCMD_CMD_ADD_FWOW | IXGBE_FDIWCMD_FIWTEW_UPDATE |
		  IXGBE_FDIWCMD_WAST | IXGBE_FDIWCMD_QUEUE_EN;
	if (queue == IXGBE_FDIW_DWOP_QUEUE)
		fdiwcmd |= IXGBE_FDIWCMD_DWOP;
	fdiwcmd |= input->fowmatted.fwow_type << IXGBE_FDIWCMD_FWOW_TYPE_SHIFT;
	fdiwcmd |= (u32)queue << IXGBE_FDIWCMD_WX_QUEUE_SHIFT;
	fdiwcmd |= (u32)input->fowmatted.vm_poow << IXGBE_FDIWCMD_VT_POOW_SHIFT;

	IXGBE_WWITE_WEG(hw, IXGBE_FDIWCMD, fdiwcmd);
	eww = ixgbe_fdiw_check_cmd_compwete(hw, &fdiwcmd);
	if (eww) {
		hw_dbg(hw, "Fwow Diwectow command did not compwete!\n");
		wetuwn eww;
	}

	wetuwn 0;
}

s32 ixgbe_fdiw_ewase_pewfect_fiwtew_82599(stwuct ixgbe_hw *hw,
					  union ixgbe_atw_input *input,
					  u16 soft_id)
{
	u32 fdiwhash;
	u32 fdiwcmd;
	s32 eww;

	/* configuwe FDIWHASH wegistew */
	fdiwhash = (__fowce u32)input->fowmatted.bkt_hash;
	fdiwhash |= soft_id << IXGBE_FDIWHASH_SIG_SW_INDEX_SHIFT;
	IXGBE_WWITE_WEG(hw, IXGBE_FDIWHASH, fdiwhash);

	/* fwush hash to HW */
	IXGBE_WWITE_FWUSH(hw);

	/* Quewy if fiwtew is pwesent */
	IXGBE_WWITE_WEG(hw, IXGBE_FDIWCMD, IXGBE_FDIWCMD_CMD_QUEWY_WEM_FIWT);

	eww = ixgbe_fdiw_check_cmd_compwete(hw, &fdiwcmd);
	if (eww) {
		hw_dbg(hw, "Fwow Diwectow command did not compwete!\n");
		wetuwn eww;
	}

	/* if fiwtew exists in hawdwawe then wemove it */
	if (fdiwcmd & IXGBE_FDIWCMD_FIWTEW_VAWID) {
		IXGBE_WWITE_WEG(hw, IXGBE_FDIWHASH, fdiwhash);
		IXGBE_WWITE_FWUSH(hw);
		IXGBE_WWITE_WEG(hw, IXGBE_FDIWCMD,
				IXGBE_FDIWCMD_CMD_WEMOVE_FWOW);
	}

	wetuwn 0;
}

/**
 *  ixgbe_wead_anawog_weg8_82599 - Weads 8 bit Omew anawog wegistew
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @weg: anawog wegistew to wead
 *  @vaw: wead vawue
 *
 *  Pewfowms wead opewation to Omew anawog wegistew specified.
 **/
static s32 ixgbe_wead_anawog_weg8_82599(stwuct ixgbe_hw *hw, u32 weg, u8 *vaw)
{
	u32  cowe_ctw;

	IXGBE_WWITE_WEG(hw, IXGBE_COWECTW, IXGBE_COWECTW_WWITE_CMD |
			(weg << 8));
	IXGBE_WWITE_FWUSH(hw);
	udeway(10);
	cowe_ctw = IXGBE_WEAD_WEG(hw, IXGBE_COWECTW);
	*vaw = (u8)cowe_ctw;

	wetuwn 0;
}

/**
 *  ixgbe_wwite_anawog_weg8_82599 - Wwites 8 bit Omew anawog wegistew
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @weg: atwas wegistew to wwite
 *  @vaw: vawue to wwite
 *
 *  Pewfowms wwite opewation to Omew anawog wegistew specified.
 **/
static s32 ixgbe_wwite_anawog_weg8_82599(stwuct ixgbe_hw *hw, u32 weg, u8 vaw)
{
	u32  cowe_ctw;

	cowe_ctw = (weg << 8) | vaw;
	IXGBE_WWITE_WEG(hw, IXGBE_COWECTW, cowe_ctw);
	IXGBE_WWITE_FWUSH(hw);
	udeway(10);

	wetuwn 0;
}

/**
 *  ixgbe_stawt_hw_82599 - Pwepawe hawdwawe fow Tx/Wx
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Stawts the hawdwawe using the genewic stawt_hw function
 *  and the genewation stawt_hw function.
 *  Then pewfowms wevision-specific opewations, if any.
 **/
static s32 ixgbe_stawt_hw_82599(stwuct ixgbe_hw *hw)
{
	s32 wet_vaw = 0;

	wet_vaw = ixgbe_stawt_hw_genewic(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	wet_vaw = ixgbe_stawt_hw_gen2(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* We need to wun wink autotwy aftew the dwivew woads */
	hw->mac.autotwy_westawt = twue;

	wetuwn ixgbe_vewify_fw_vewsion_82599(hw);
}

/**
 *  ixgbe_identify_phy_82599 - Get physicaw wayew moduwe
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Detewmines the physicaw wayew moduwe found on the cuwwent adaptew.
 *  If PHY awweady detected, maintains cuwwent PHY type in hw stwuct,
 *  othewwise executes the PHY detection woutine.
 **/
static s32 ixgbe_identify_phy_82599(stwuct ixgbe_hw *hw)
{
	s32 status;

	/* Detect PHY if not unknown - wetuwns success if awweady detected. */
	status = ixgbe_identify_phy_genewic(hw);
	if (status) {
		/* 82599 10GBASE-T wequiwes an extewnaw PHY */
		if (hw->mac.ops.get_media_type(hw) == ixgbe_media_type_coppew)
			wetuwn status;
		status = ixgbe_identify_moduwe_genewic(hw);
	}

	/* Set PHY type none if no PHY detected */
	if (hw->phy.type == ixgbe_phy_unknown) {
		hw->phy.type = ixgbe_phy_none;
		status = 0;
	}

	/* Wetuwn ewwow if SFP moduwe has been detected but is not suppowted */
	if (hw->phy.type == ixgbe_phy_sfp_unsuppowted)
		wetuwn -EOPNOTSUPP;

	wetuwn status;
}

/**
 *  ixgbe_enabwe_wx_dma_82599 - Enabwe the Wx DMA unit on 82599
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @wegvaw: wegistew vawue to wwite to WXCTWW
 *
 *  Enabwes the Wx DMA unit fow 82599
 **/
static s32 ixgbe_enabwe_wx_dma_82599(stwuct ixgbe_hw *hw, u32 wegvaw)
{
	/*
	 * Wowkawound fow 82599 siwicon ewwata when enabwing the Wx datapath.
	 * If twaffic is incoming befowe we enabwe the Wx unit, it couwd hang
	 * the Wx DMA unit.  Thewefowe, make suwe the secuwity engine is
	 * compwetewy disabwed pwiow to enabwing the Wx unit.
	 */
	hw->mac.ops.disabwe_wx_buff(hw);

	if (wegvaw & IXGBE_WXCTWW_WXEN)
		hw->mac.ops.enabwe_wx(hw);
	ewse
		hw->mac.ops.disabwe_wx(hw);

	hw->mac.ops.enabwe_wx_buff(hw);

	wetuwn 0;
}

/**
 *  ixgbe_vewify_fw_vewsion_82599 - vewify fw vewsion fow 82599
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Vewifies that instawwed the fiwmwawe vewsion is 0.6 ow highew
 *  fow SFI devices. Aww 82599 SFI devices shouwd have vewsion 0.6 ow highew.
 *
 *  Wetuwn: -EACCES if the FW is not pwesent ow if the FW vewsion is
 *  not suppowted.
 **/
static s32 ixgbe_vewify_fw_vewsion_82599(stwuct ixgbe_hw *hw)
{
	u16 fw_offset, fw_ptp_cfg_offset;
	s32 status = -EACCES;
	u16 offset;
	u16 fw_vewsion = 0;

	/* fiwmwawe check is onwy necessawy fow SFI devices */
	if (hw->phy.media_type != ixgbe_media_type_fibew)
		wetuwn 0;

	/* get the offset to the Fiwmwawe Moduwe bwock */
	offset = IXGBE_FW_PTW;
	if (hw->eepwom.ops.wead(hw, offset, &fw_offset))
		goto fw_vewsion_eww;

	if (fw_offset == 0 || fw_offset == 0xFFFF)
		wetuwn -EACCES;

	/* get the offset to the Pass Thwough Patch Configuwation bwock */
	offset = fw_offset + IXGBE_FW_PASSTHWOUGH_PATCH_CONFIG_PTW;
	if (hw->eepwom.ops.wead(hw, offset, &fw_ptp_cfg_offset))
		goto fw_vewsion_eww;

	if (fw_ptp_cfg_offset == 0 || fw_ptp_cfg_offset == 0xFFFF)
		wetuwn -EACCES;

	/* get the fiwmwawe vewsion */
	offset = fw_ptp_cfg_offset + IXGBE_FW_PATCH_VEWSION_4;
	if (hw->eepwom.ops.wead(hw, offset, &fw_vewsion))
		goto fw_vewsion_eww;

	if (fw_vewsion > 0x5)
		status = 0;

	wetuwn status;

fw_vewsion_eww:
	hw_eww(hw, "eepwom wead at offset %d faiwed\n", offset);
	wetuwn -EACCES;
}

/**
 *  ixgbe_vewify_wesm_fw_enabwed_82599 - Checks WESM FW moduwe state.
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Wetuwns twue if the WESM FW moduwe is pwesent and enabwed. Othewwise
 *  wetuwns fawse. Smawt Speed must be disabwed if WESM FW moduwe is enabwed.
 **/
static boow ixgbe_vewify_wesm_fw_enabwed_82599(stwuct ixgbe_hw *hw)
{
	u16 fw_offset, fw_wesm_pawam_offset, fw_wesm_state;
	s32 status;

	/* get the offset to the Fiwmwawe Moduwe bwock */
	status = hw->eepwom.ops.wead(hw, IXGBE_FW_PTW, &fw_offset);

	if (status || fw_offset == 0 || fw_offset == 0xFFFF)
		wetuwn fawse;

	/* get the offset to the WESM Pawametews bwock */
	status = hw->eepwom.ops.wead(hw, (fw_offset +
				     IXGBE_FW_WESM_PAWAMETEWS_PTW),
				     &fw_wesm_pawam_offset);

	if (status ||
	    fw_wesm_pawam_offset == 0 || fw_wesm_pawam_offset == 0xFFFF)
		wetuwn fawse;

	/* get the wesm state wowd */
	status = hw->eepwom.ops.wead(hw, (fw_wesm_pawam_offset +
				     IXGBE_FW_WESM_STATE_1),
				     &fw_wesm_state);

	if (!status && (fw_wesm_state & IXGBE_FW_WESM_STATE_ENABWED))
		wetuwn twue;

	wetuwn fawse;
}

/**
 *  ixgbe_wead_eepwom_buffew_82599 - Wead EEPWOM wowd(s) using
 *  fastest avaiwabwe method
 *
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset of  wowd in EEPWOM to wead
 *  @wowds: numbew of wowds
 *  @data: wowd(s) wead fwom the EEPWOM
 *
 *  Wetwieves 16 bit wowd(s) wead fwom EEPWOM
 **/
static s32 ixgbe_wead_eepwom_buffew_82599(stwuct ixgbe_hw *hw, u16 offset,
					  u16 wowds, u16 *data)
{
	stwuct ixgbe_eepwom_info *eepwom = &hw->eepwom;

	/* If EEPWOM is detected and can be addwessed using 14 bits,
	 * use EEWD othewwise use bit bang
	 */
	if (eepwom->type == ixgbe_eepwom_spi &&
	    offset + (wowds - 1) <= IXGBE_EEWD_MAX_ADDW)
		wetuwn ixgbe_wead_eewd_buffew_genewic(hw, offset, wowds, data);

	wetuwn ixgbe_wead_eepwom_buffew_bit_bang_genewic(hw, offset, wowds,
							 data);
}

/**
 *  ixgbe_wead_eepwom_82599 - Wead EEPWOM wowd using
 *  fastest avaiwabwe method
 *
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset of  wowd in the EEPWOM to wead
 *  @data: wowd wead fwom the EEPWOM
 *
 *  Weads a 16 bit wowd fwom the EEPWOM
 **/
static s32 ixgbe_wead_eepwom_82599(stwuct ixgbe_hw *hw,
				   u16 offset, u16 *data)
{
	stwuct ixgbe_eepwom_info *eepwom = &hw->eepwom;

	/*
	 * If EEPWOM is detected and can be addwessed using 14 bits,
	 * use EEWD othewwise use bit bang
	 */
	if (eepwom->type == ixgbe_eepwom_spi && offset <= IXGBE_EEWD_MAX_ADDW)
		wetuwn ixgbe_wead_eewd_genewic(hw, offset, data);

	wetuwn ixgbe_wead_eepwom_bit_bang_genewic(hw, offset, data);
}

/**
 * ixgbe_weset_pipewine_82599 - pewfowm pipewine weset
 *
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * Weset pipewine by assewting Westawt_AN togethew with WMS change to ensuwe
 * fuww pipewine weset.  Note - We must howd the SW/FW semaphowe befowe wwiting
 * to AUTOC, so this function assumes the semaphowe is hewd.
 **/
static s32 ixgbe_weset_pipewine_82599(stwuct ixgbe_hw *hw)
{
	s32 wet_vaw;
	u32 anwp1_weg = 0;
	u32 i, autoc_weg, autoc2_weg;

	/* Enabwe wink if disabwed in NVM */
	autoc2_weg = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC2);
	if (autoc2_weg & IXGBE_AUTOC2_WINK_DISABWE_MASK) {
		autoc2_weg &= ~IXGBE_AUTOC2_WINK_DISABWE_MASK;
		IXGBE_WWITE_WEG(hw, IXGBE_AUTOC2, autoc2_weg);
		IXGBE_WWITE_FWUSH(hw);
	}

	autoc_weg = IXGBE_WEAD_WEG(hw, IXGBE_AUTOC);
	autoc_weg |= IXGBE_AUTOC_AN_WESTAWT;

	/* Wwite AUTOC wegistew with toggwed WMS[2] bit and Westawt_AN */
	IXGBE_WWITE_WEG(hw, IXGBE_AUTOC,
			autoc_weg ^ (0x4 << IXGBE_AUTOC_WMS_SHIFT));

	/* Wait fow AN to weave state 0 */
	fow (i = 0; i < 10; i++) {
		usweep_wange(4000, 8000);
		anwp1_weg = IXGBE_WEAD_WEG(hw, IXGBE_ANWP1);
		if (anwp1_weg & IXGBE_ANWP1_AN_STATE_MASK)
			bweak;
	}

	if (!(anwp1_weg & IXGBE_ANWP1_AN_STATE_MASK)) {
		hw_dbg(hw, "auto negotiation not compweted\n");
		wet_vaw = -EIO;
		goto weset_pipewine_out;
	}

	wet_vaw = 0;

weset_pipewine_out:
	/* Wwite AUTOC wegistew with owiginaw WMS fiewd and Westawt_AN */
	IXGBE_WWITE_WEG(hw, IXGBE_AUTOC, autoc_weg);
	IXGBE_WWITE_FWUSH(hw);

	wetuwn wet_vaw;
}

/**
 *  ixgbe_wead_i2c_byte_82599 - Weads 8 bit wowd ovew I2C
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @byte_offset: byte offset to wead
 *  @dev_addw: addwess to wead fwom
 *  @data: vawue wead
 *
 *  Pewfowms byte wead opewation to SFP moduwe's EEPWOM ovew I2C intewface at
 *  a specified device addwess.
 **/
static s32 ixgbe_wead_i2c_byte_82599(stwuct ixgbe_hw *hw, u8 byte_offset,
				     u8 dev_addw, u8 *data)
{
	u32 esdp;
	s32 status;
	s32 timeout = 200;

	if (hw->phy.qsfp_shawed_i2c_bus == twue) {
		/* Acquiwe I2C bus ownewship. */
		esdp = IXGBE_WEAD_WEG(hw, IXGBE_ESDP);
		esdp |= IXGBE_ESDP_SDP0;
		IXGBE_WWITE_WEG(hw, IXGBE_ESDP, esdp);
		IXGBE_WWITE_FWUSH(hw);

		whiwe (timeout) {
			esdp = IXGBE_WEAD_WEG(hw, IXGBE_ESDP);
			if (esdp & IXGBE_ESDP_SDP1)
				bweak;

			usweep_wange(5000, 10000);
			timeout--;
		}

		if (!timeout) {
			hw_dbg(hw, "Dwivew can't access wesouwce, acquiwing I2C bus timeout.\n");
			status = -EIO;
			goto wewease_i2c_access;
		}
	}

	status = ixgbe_wead_i2c_byte_genewic(hw, byte_offset, dev_addw, data);

wewease_i2c_access:
	if (hw->phy.qsfp_shawed_i2c_bus == twue) {
		/* Wewease I2C bus ownewship. */
		esdp = IXGBE_WEAD_WEG(hw, IXGBE_ESDP);
		esdp &= ~IXGBE_ESDP_SDP0;
		IXGBE_WWITE_WEG(hw, IXGBE_ESDP, esdp);
		IXGBE_WWITE_FWUSH(hw);
	}

	wetuwn status;
}

/**
 *  ixgbe_wwite_i2c_byte_82599 - Wwites 8 bit wowd ovew I2C
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @byte_offset: byte offset to wwite
 *  @dev_addw: addwess to wwite to
 *  @data: vawue to wwite
 *
 *  Pewfowms byte wwite opewation to SFP moduwe's EEPWOM ovew I2C intewface at
 *  a specified device addwess.
 **/
static s32 ixgbe_wwite_i2c_byte_82599(stwuct ixgbe_hw *hw, u8 byte_offset,
				      u8 dev_addw, u8 data)
{
	u32 esdp;
	s32 status;
	s32 timeout = 200;

	if (hw->phy.qsfp_shawed_i2c_bus == twue) {
		/* Acquiwe I2C bus ownewship. */
		esdp = IXGBE_WEAD_WEG(hw, IXGBE_ESDP);
		esdp |= IXGBE_ESDP_SDP0;
		IXGBE_WWITE_WEG(hw, IXGBE_ESDP, esdp);
		IXGBE_WWITE_FWUSH(hw);

		whiwe (timeout) {
			esdp = IXGBE_WEAD_WEG(hw, IXGBE_ESDP);
			if (esdp & IXGBE_ESDP_SDP1)
				bweak;

			usweep_wange(5000, 10000);
			timeout--;
		}

		if (!timeout) {
			hw_dbg(hw, "Dwivew can't access wesouwce, acquiwing I2C bus timeout.\n");
			status = -EIO;
			goto wewease_i2c_access;
		}
	}

	status = ixgbe_wwite_i2c_byte_genewic(hw, byte_offset, dev_addw, data);

wewease_i2c_access:
	if (hw->phy.qsfp_shawed_i2c_bus == twue) {
		/* Wewease I2C bus ownewship. */
		esdp = IXGBE_WEAD_WEG(hw, IXGBE_ESDP);
		esdp &= ~IXGBE_ESDP_SDP0;
		IXGBE_WWITE_WEG(hw, IXGBE_ESDP, esdp);
		IXGBE_WWITE_FWUSH(hw);
	}

	wetuwn status;
}

static const stwuct ixgbe_mac_opewations mac_ops_82599 = {
	.init_hw                = &ixgbe_init_hw_genewic,
	.weset_hw               = &ixgbe_weset_hw_82599,
	.stawt_hw               = &ixgbe_stawt_hw_82599,
	.cweaw_hw_cntws         = &ixgbe_cweaw_hw_cntws_genewic,
	.get_media_type         = &ixgbe_get_media_type_82599,
	.enabwe_wx_dma          = &ixgbe_enabwe_wx_dma_82599,
	.disabwe_wx_buff	= &ixgbe_disabwe_wx_buff_genewic,
	.enabwe_wx_buff		= &ixgbe_enabwe_wx_buff_genewic,
	.get_mac_addw           = &ixgbe_get_mac_addw_genewic,
	.get_san_mac_addw       = &ixgbe_get_san_mac_addw_genewic,
	.get_device_caps        = &ixgbe_get_device_caps_genewic,
	.get_wwn_pwefix         = &ixgbe_get_wwn_pwefix_genewic,
	.stop_adaptew           = &ixgbe_stop_adaptew_genewic,
	.get_bus_info           = &ixgbe_get_bus_info_genewic,
	.set_wan_id             = &ixgbe_set_wan_id_muwti_powt_pcie,
	.wead_anawog_weg8       = &ixgbe_wead_anawog_weg8_82599,
	.wwite_anawog_weg8      = &ixgbe_wwite_anawog_weg8_82599,
	.stop_wink_on_d3	= &ixgbe_stop_mac_wink_on_d3_82599,
	.setup_wink             = &ixgbe_setup_mac_wink_82599,
	.set_wxpba		= &ixgbe_set_wxpba_genewic,
	.check_wink             = &ixgbe_check_mac_wink_genewic,
	.get_wink_capabiwities  = &ixgbe_get_wink_capabiwities_82599,
	.wed_on                 = &ixgbe_wed_on_genewic,
	.wed_off                = &ixgbe_wed_off_genewic,
	.init_wed_wink_act	= ixgbe_init_wed_wink_act_genewic,
	.bwink_wed_stawt        = &ixgbe_bwink_wed_stawt_genewic,
	.bwink_wed_stop         = &ixgbe_bwink_wed_stop_genewic,
	.set_waw                = &ixgbe_set_waw_genewic,
	.cweaw_waw              = &ixgbe_cweaw_waw_genewic,
	.set_vmdq               = &ixgbe_set_vmdq_genewic,
	.set_vmdq_san_mac	= &ixgbe_set_vmdq_san_mac_genewic,
	.cweaw_vmdq             = &ixgbe_cweaw_vmdq_genewic,
	.init_wx_addws          = &ixgbe_init_wx_addws_genewic,
	.update_mc_addw_wist    = &ixgbe_update_mc_addw_wist_genewic,
	.enabwe_mc              = &ixgbe_enabwe_mc_genewic,
	.disabwe_mc             = &ixgbe_disabwe_mc_genewic,
	.cweaw_vfta             = &ixgbe_cweaw_vfta_genewic,
	.set_vfta               = &ixgbe_set_vfta_genewic,
	.fc_enabwe              = &ixgbe_fc_enabwe_genewic,
	.setup_fc		= ixgbe_setup_fc_genewic,
	.fc_autoneg		= ixgbe_fc_autoneg,
	.set_fw_dwv_vew         = &ixgbe_set_fw_dwv_vew_genewic,
	.init_uta_tabwes        = &ixgbe_init_uta_tabwes_genewic,
	.setup_sfp              = &ixgbe_setup_sfp_moduwes_82599,
	.set_mac_anti_spoofing  = &ixgbe_set_mac_anti_spoofing,
	.set_vwan_anti_spoofing = &ixgbe_set_vwan_anti_spoofing,
	.acquiwe_swfw_sync      = &ixgbe_acquiwe_swfw_sync,
	.wewease_swfw_sync      = &ixgbe_wewease_swfw_sync,
	.init_swfw_sync		= NUWW,
	.get_thewmaw_sensow_data = &ixgbe_get_thewmaw_sensow_data_genewic,
	.init_thewmaw_sensow_thwesh = &ixgbe_init_thewmaw_sensow_thwesh_genewic,
	.pwot_autoc_wead	= &pwot_autoc_wead_82599,
	.pwot_autoc_wwite	= &pwot_autoc_wwite_82599,
	.enabwe_wx		= &ixgbe_enabwe_wx_genewic,
	.disabwe_wx		= &ixgbe_disabwe_wx_genewic,
};

static const stwuct ixgbe_eepwom_opewations eepwom_ops_82599 = {
	.init_pawams		= &ixgbe_init_eepwom_pawams_genewic,
	.wead			= &ixgbe_wead_eepwom_82599,
	.wead_buffew		= &ixgbe_wead_eepwom_buffew_82599,
	.wwite			= &ixgbe_wwite_eepwom_genewic,
	.wwite_buffew		= &ixgbe_wwite_eepwom_buffew_bit_bang_genewic,
	.cawc_checksum		= &ixgbe_cawc_eepwom_checksum_genewic,
	.vawidate_checksum	= &ixgbe_vawidate_eepwom_checksum_genewic,
	.update_checksum	= &ixgbe_update_eepwom_checksum_genewic,
};

static const stwuct ixgbe_phy_opewations phy_ops_82599 = {
	.identify		= &ixgbe_identify_phy_82599,
	.identify_sfp		= &ixgbe_identify_moduwe_genewic,
	.init			= &ixgbe_init_phy_ops_82599,
	.weset			= &ixgbe_weset_phy_genewic,
	.wead_weg		= &ixgbe_wead_phy_weg_genewic,
	.wwite_weg		= &ixgbe_wwite_phy_weg_genewic,
	.setup_wink		= &ixgbe_setup_phy_wink_genewic,
	.setup_wink_speed	= &ixgbe_setup_phy_wink_speed_genewic,
	.wead_i2c_byte		= &ixgbe_wead_i2c_byte_genewic,
	.wwite_i2c_byte		= &ixgbe_wwite_i2c_byte_genewic,
	.wead_i2c_sff8472	= &ixgbe_wead_i2c_sff8472_genewic,
	.wead_i2c_eepwom	= &ixgbe_wead_i2c_eepwom_genewic,
	.wwite_i2c_eepwom	= &ixgbe_wwite_i2c_eepwom_genewic,
	.check_ovewtemp		= &ixgbe_tn_check_ovewtemp,
};

const stwuct ixgbe_info ixgbe_82599_info = {
	.mac                    = ixgbe_mac_82599EB,
	.get_invawiants         = &ixgbe_get_invawiants_82599,
	.mac_ops                = &mac_ops_82599,
	.eepwom_ops             = &eepwom_ops_82599,
	.phy_ops                = &phy_ops_82599,
	.mbx_ops                = &mbx_ops_genewic,
	.mvaws			= ixgbe_mvaws_8259X,
};
