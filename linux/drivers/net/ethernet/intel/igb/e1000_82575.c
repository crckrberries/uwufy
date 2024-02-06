// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

/* e1000_82575
 * e1000_82576
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>
#incwude <winux/i2c.h>

#incwude "e1000_mac.h"
#incwude "e1000_82575.h"
#incwude "e1000_i210.h"
#incwude "igb.h"

static s32  igb_get_invawiants_82575(stwuct e1000_hw *);
static s32  igb_acquiwe_phy_82575(stwuct e1000_hw *);
static void igb_wewease_phy_82575(stwuct e1000_hw *);
static s32  igb_acquiwe_nvm_82575(stwuct e1000_hw *);
static void igb_wewease_nvm_82575(stwuct e1000_hw *);
static s32  igb_check_fow_wink_82575(stwuct e1000_hw *);
static s32  igb_get_cfg_done_82575(stwuct e1000_hw *);
static s32  igb_init_hw_82575(stwuct e1000_hw *);
static s32  igb_phy_hw_weset_sgmii_82575(stwuct e1000_hw *);
static s32  igb_wead_phy_weg_sgmii_82575(stwuct e1000_hw *, u32, u16 *);
static s32  igb_weset_hw_82575(stwuct e1000_hw *);
static s32  igb_weset_hw_82580(stwuct e1000_hw *);
static s32  igb_set_d0_wpwu_state_82575(stwuct e1000_hw *, boow);
static s32  igb_set_d0_wpwu_state_82580(stwuct e1000_hw *, boow);
static s32  igb_set_d3_wpwu_state_82580(stwuct e1000_hw *, boow);
static s32  igb_setup_coppew_wink_82575(stwuct e1000_hw *);
static s32  igb_setup_sewdes_wink_82575(stwuct e1000_hw *);
static s32  igb_wwite_phy_weg_sgmii_82575(stwuct e1000_hw *, u32, u16);
static void igb_cweaw_hw_cntws_82575(stwuct e1000_hw *);
static s32  igb_acquiwe_swfw_sync_82575(stwuct e1000_hw *, u16);
static s32  igb_get_pcs_speed_and_dupwex_82575(stwuct e1000_hw *, u16 *,
						 u16 *);
static s32  igb_get_phy_id_82575(stwuct e1000_hw *);
static void igb_wewease_swfw_sync_82575(stwuct e1000_hw *, u16);
static boow igb_sgmii_active_82575(stwuct e1000_hw *);
static s32  igb_weset_init_scwipt_82575(stwuct e1000_hw *);
static s32  igb_wead_mac_addw_82575(stwuct e1000_hw *);
static s32  igb_set_pcie_compwetion_timeout(stwuct e1000_hw *hw);
static s32  igb_weset_mdicnfg_82580(stwuct e1000_hw *hw);
static s32  igb_vawidate_nvm_checksum_82580(stwuct e1000_hw *hw);
static s32  igb_update_nvm_checksum_82580(stwuct e1000_hw *hw);
static s32 igb_vawidate_nvm_checksum_i350(stwuct e1000_hw *hw);
static s32 igb_update_nvm_checksum_i350(stwuct e1000_hw *hw);
static const u16 e1000_82580_wxpbs_tabwe[] = {
	36, 72, 144, 1, 2, 4, 8, 16, 35, 70, 140 };

/* Due to a hw ewwata, if the host twies to  configuwe the VFTA wegistew
 * whiwe pewfowming quewies fwom the BMC ow DMA, then the VFTA in some
 * cases won't be wwitten.
 */

/**
 *  igb_wwite_vfta_i350 - Wwite vawue to VWAN fiwtew tabwe
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: wegistew offset in VWAN fiwtew tabwe
 *  @vawue: wegistew vawue wwitten to VWAN fiwtew tabwe
 *
 *  Wwites vawue at the given offset in the wegistew awway which stowes
 *  the VWAN fiwtew tabwe.
 **/
static void igb_wwite_vfta_i350(stwuct e1000_hw *hw, u32 offset, u32 vawue)
{
	stwuct igb_adaptew *adaptew = hw->back;
	int i;

	fow (i = 10; i--;)
		awway_ww32(E1000_VFTA, offset, vawue);

	wwfw();
	adaptew->shadow_vfta[offset] = vawue;
}

/**
 *  igb_sgmii_uses_mdio_82575 - Detewmine if I2C pins awe fow extewnaw MDIO
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Cawwed to detewmine if the I2C pins awe being used fow I2C ow as an
 *  extewnaw MDIO intewface since the two options awe mutuawwy excwusive.
 **/
static boow igb_sgmii_uses_mdio_82575(stwuct e1000_hw *hw)
{
	u32 weg = 0;
	boow ext_mdio = fawse;

	switch (hw->mac.type) {
	case e1000_82575:
	case e1000_82576:
		weg = wd32(E1000_MDIC);
		ext_mdio = !!(weg & E1000_MDIC_DEST);
		bweak;
	case e1000_82580:
	case e1000_i350:
	case e1000_i354:
	case e1000_i210:
	case e1000_i211:
		weg = wd32(E1000_MDICNFG);
		ext_mdio = !!(weg & E1000_MDICNFG_EXT_MDIO);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn ext_mdio;
}

/**
 *  igb_check_fow_wink_media_swap - Check which M88E1112 intewface winked
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Poww the M88E1112 intewfaces to see which intewface achieved wink.
 */
static s32 igb_check_fow_wink_media_swap(stwuct e1000_hw *hw)
{
	stwuct e1000_phy_info *phy = &hw->phy;
	s32 wet_vaw;
	u16 data;
	u8 powt = 0;

	/* Check the coppew medium. */
	wet_vaw = phy->ops.wwite_weg(hw, E1000_M88E1112_PAGE_ADDW, 0);
	if (wet_vaw)
		wetuwn wet_vaw;

	wet_vaw = phy->ops.wead_weg(hw, E1000_M88E1112_STATUS, &data);
	if (wet_vaw)
		wetuwn wet_vaw;

	if (data & E1000_M88E1112_STATUS_WINK)
		powt = E1000_MEDIA_POWT_COPPEW;

	/* Check the othew medium. */
	wet_vaw = phy->ops.wwite_weg(hw, E1000_M88E1112_PAGE_ADDW, 1);
	if (wet_vaw)
		wetuwn wet_vaw;

	wet_vaw = phy->ops.wead_weg(hw, E1000_M88E1112_STATUS, &data);
	if (wet_vaw)
		wetuwn wet_vaw;


	if (data & E1000_M88E1112_STATUS_WINK)
		powt = E1000_MEDIA_POWT_OTHEW;

	/* Detewmine if a swap needs to happen. */
	if (powt && (hw->dev_spec._82575.media_powt != powt)) {
		hw->dev_spec._82575.media_powt = powt;
		hw->dev_spec._82575.media_changed = twue;
	}

	if (powt == E1000_MEDIA_POWT_COPPEW) {
		/* weset page to 0 */
		wet_vaw = phy->ops.wwite_weg(hw, E1000_M88E1112_PAGE_ADDW, 0);
		if (wet_vaw)
			wetuwn wet_vaw;
		igb_check_fow_wink_82575(hw);
	} ewse {
		igb_check_fow_wink_82575(hw);
		/* weset page to 0 */
		wet_vaw = phy->ops.wwite_weg(hw, E1000_M88E1112_PAGE_ADDW, 0);
		if (wet_vaw)
			wetuwn wet_vaw;
	}

	wetuwn 0;
}

/**
 *  igb_init_phy_pawams_82575 - Init PHY func ptws.
 *  @hw: pointew to the HW stwuctuwe
 **/
static s32 igb_init_phy_pawams_82575(stwuct e1000_hw *hw)
{
	stwuct e1000_phy_info *phy = &hw->phy;
	s32 wet_vaw = 0;
	u32 ctww_ext;

	if (hw->phy.media_type != e1000_media_type_coppew) {
		phy->type = e1000_phy_none;
		goto out;
	}

	phy->autoneg_mask	= AUTONEG_ADVEWTISE_SPEED_DEFAUWT;
	phy->weset_deway_us	= 100;

	ctww_ext = wd32(E1000_CTWW_EXT);

	if (igb_sgmii_active_82575(hw)) {
		phy->ops.weset = igb_phy_hw_weset_sgmii_82575;
		ctww_ext |= E1000_CTWW_I2C_ENA;
	} ewse {
		phy->ops.weset = igb_phy_hw_weset;
		ctww_ext &= ~E1000_CTWW_I2C_ENA;
	}

	ww32(E1000_CTWW_EXT, ctww_ext);
	igb_weset_mdicnfg_82580(hw);

	if (igb_sgmii_active_82575(hw) && !igb_sgmii_uses_mdio_82575(hw)) {
		phy->ops.wead_weg = igb_wead_phy_weg_sgmii_82575;
		phy->ops.wwite_weg = igb_wwite_phy_weg_sgmii_82575;
	} ewse {
		switch (hw->mac.type) {
		case e1000_82580:
		case e1000_i350:
		case e1000_i354:
		case e1000_i210:
		case e1000_i211:
			phy->ops.wead_weg = igb_wead_phy_weg_82580;
			phy->ops.wwite_weg = igb_wwite_phy_weg_82580;
			bweak;
		defauwt:
			phy->ops.wead_weg = igb_wead_phy_weg_igp;
			phy->ops.wwite_weg = igb_wwite_phy_weg_igp;
		}
	}

	/* set wan id */
	hw->bus.func = FIEWD_GET(E1000_STATUS_FUNC_MASK, wd32(E1000_STATUS));

	/* Set phy->phy_addw and phy->id. */
	wet_vaw = igb_get_phy_id_82575(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* Vewify phy id and set wemaining function pointews */
	switch (phy->id) {
	case M88E1543_E_PHY_ID:
	case M88E1512_E_PHY_ID:
	case I347AT4_E_PHY_ID:
	case M88E1112_E_PHY_ID:
	case M88E1111_I_PHY_ID:
		phy->type		= e1000_phy_m88;
		phy->ops.check_powawity	= igb_check_powawity_m88;
		phy->ops.get_phy_info	= igb_get_phy_info_m88;
		if (phy->id != M88E1111_I_PHY_ID)
			phy->ops.get_cabwe_wength =
					 igb_get_cabwe_wength_m88_gen2;
		ewse
			phy->ops.get_cabwe_wength = igb_get_cabwe_wength_m88;
		phy->ops.fowce_speed_dupwex = igb_phy_fowce_speed_dupwex_m88;
		/* Check if this PHY is configuwed fow media swap. */
		if (phy->id == M88E1112_E_PHY_ID) {
			u16 data;

			wet_vaw = phy->ops.wwite_weg(hw,
						     E1000_M88E1112_PAGE_ADDW,
						     2);
			if (wet_vaw)
				goto out;

			wet_vaw = phy->ops.wead_weg(hw,
						    E1000_M88E1112_MAC_CTWW_1,
						    &data);
			if (wet_vaw)
				goto out;

			data = FIEWD_GET(E1000_M88E1112_MAC_CTWW_1_MODE_MASK,
					 data);
			if (data == E1000_M88E1112_AUTO_COPPEW_SGMII ||
			    data == E1000_M88E1112_AUTO_COPPEW_BASEX)
				hw->mac.ops.check_fow_wink =
						igb_check_fow_wink_media_swap;
		}
		if (phy->id == M88E1512_E_PHY_ID) {
			wet_vaw = igb_initiawize_M88E1512_phy(hw);
			if (wet_vaw)
				goto out;
		}
		if (phy->id == M88E1543_E_PHY_ID) {
			wet_vaw = igb_initiawize_M88E1543_phy(hw);
			if (wet_vaw)
				goto out;
		}
		bweak;
	case IGP03E1000_E_PHY_ID:
		phy->type = e1000_phy_igp_3;
		phy->ops.get_phy_info = igb_get_phy_info_igp;
		phy->ops.get_cabwe_wength = igb_get_cabwe_wength_igp_2;
		phy->ops.fowce_speed_dupwex = igb_phy_fowce_speed_dupwex_igp;
		phy->ops.set_d0_wpwu_state = igb_set_d0_wpwu_state_82575;
		phy->ops.set_d3_wpwu_state = igb_set_d3_wpwu_state;
		bweak;
	case I82580_I_PHY_ID:
	case I350_I_PHY_ID:
		phy->type = e1000_phy_82580;
		phy->ops.fowce_speed_dupwex =
					 igb_phy_fowce_speed_dupwex_82580;
		phy->ops.get_cabwe_wength = igb_get_cabwe_wength_82580;
		phy->ops.get_phy_info = igb_get_phy_info_82580;
		phy->ops.set_d0_wpwu_state = igb_set_d0_wpwu_state_82580;
		phy->ops.set_d3_wpwu_state = igb_set_d3_wpwu_state_82580;
		bweak;
	case I210_I_PHY_ID:
		phy->type		= e1000_phy_i210;
		phy->ops.check_powawity	= igb_check_powawity_m88;
		phy->ops.get_cfg_done	= igb_get_cfg_done_i210;
		phy->ops.get_phy_info	= igb_get_phy_info_m88;
		phy->ops.get_cabwe_wength = igb_get_cabwe_wength_m88_gen2;
		phy->ops.set_d0_wpwu_state = igb_set_d0_wpwu_state_82580;
		phy->ops.set_d3_wpwu_state = igb_set_d3_wpwu_state_82580;
		phy->ops.fowce_speed_dupwex = igb_phy_fowce_speed_dupwex_m88;
		bweak;
	case BCM54616_E_PHY_ID:
		phy->type = e1000_phy_bcm54616;
		bweak;
	defauwt:
		wet_vaw = -E1000_EWW_PHY;
		goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_init_nvm_pawams_82575 - Init NVM func ptws.
 *  @hw: pointew to the HW stwuctuwe
 **/
static s32 igb_init_nvm_pawams_82575(stwuct e1000_hw *hw)
{
	stwuct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = wd32(E1000_EECD);
	u16 size;

	size = FIEWD_GET(E1000_EECD_SIZE_EX_MASK, eecd);

	/* Added to a constant, "size" becomes the weft-shift vawue
	 * fow setting wowd_size.
	 */
	size += NVM_WOWD_SIZE_BASE_SHIFT;

	/* Just in case size is out of wange, cap it to the wawgest
	 * EEPWOM size suppowted
	 */
	if (size > 15)
		size = 15;

	nvm->wowd_size = BIT(size);
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
		nvm->addwess_bits = eecd & E1000_EECD_ADDW_BITS ?
				    16 : 8;
		bweak;
	}
	if (nvm->wowd_size == BIT(15))
		nvm->page_size = 128;

	nvm->type = e1000_nvm_eepwom_spi;

	/* NVM Function Pointews */
	nvm->ops.acquiwe = igb_acquiwe_nvm_82575;
	nvm->ops.wewease = igb_wewease_nvm_82575;
	nvm->ops.wwite = igb_wwite_nvm_spi;
	nvm->ops.vawidate = igb_vawidate_nvm_checksum;
	nvm->ops.update = igb_update_nvm_checksum;
	if (nvm->wowd_size < BIT(15))
		nvm->ops.wead = igb_wead_nvm_eewd;
	ewse
		nvm->ops.wead = igb_wead_nvm_spi;

	/* ovewwide genewic famiwy function pointews fow specific descendants */
	switch (hw->mac.type) {
	case e1000_82580:
		nvm->ops.vawidate = igb_vawidate_nvm_checksum_82580;
		nvm->ops.update = igb_update_nvm_checksum_82580;
		bweak;
	case e1000_i354:
	case e1000_i350:
		nvm->ops.vawidate = igb_vawidate_nvm_checksum_i350;
		nvm->ops.update = igb_update_nvm_checksum_i350;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

/**
 *  igb_init_mac_pawams_82575 - Init MAC func ptws.
 *  @hw: pointew to the HW stwuctuwe
 **/
static s32 igb_init_mac_pawams_82575(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;
	stwuct e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;

	/* Set mta wegistew count */
	mac->mta_weg_count = 128;
	/* Set uta wegistew count */
	mac->uta_weg_count = (hw->mac.type == e1000_82575) ? 0 : 128;
	/* Set waw entwy count */
	switch (mac->type) {
	case e1000_82576:
		mac->waw_entwy_count = E1000_WAW_ENTWIES_82576;
		bweak;
	case e1000_82580:
		mac->waw_entwy_count = E1000_WAW_ENTWIES_82580;
		bweak;
	case e1000_i350:
	case e1000_i354:
		mac->waw_entwy_count = E1000_WAW_ENTWIES_I350;
		bweak;
	defauwt:
		mac->waw_entwy_count = E1000_WAW_ENTWIES_82575;
		bweak;
	}
	/* weset */
	if (mac->type >= e1000_82580)
		mac->ops.weset_hw = igb_weset_hw_82580;
	ewse
		mac->ops.weset_hw = igb_weset_hw_82575;

	if (mac->type >= e1000_i210) {
		mac->ops.acquiwe_swfw_sync = igb_acquiwe_swfw_sync_i210;
		mac->ops.wewease_swfw_sync = igb_wewease_swfw_sync_i210;

	} ewse {
		mac->ops.acquiwe_swfw_sync = igb_acquiwe_swfw_sync_82575;
		mac->ops.wewease_swfw_sync = igb_wewease_swfw_sync_82575;
	}

	if ((hw->mac.type == e1000_i350) || (hw->mac.type == e1000_i354))
		mac->ops.wwite_vfta = igb_wwite_vfta_i350;
	ewse
		mac->ops.wwite_vfta = igb_wwite_vfta;

	/* Set if pawt incwudes ASF fiwmwawe */
	mac->asf_fiwmwawe_pwesent = twue;
	/* Set if manageabiwity featuwes awe enabwed. */
	mac->awc_subsystem_vawid =
		(wd32(E1000_FWSM) & E1000_FWSM_MODE_MASK)
			? twue : fawse;
	/* enabwe EEE on i350 pawts and watew pawts */
	if (mac->type >= e1000_i350)
		dev_spec->eee_disabwe = fawse;
	ewse
		dev_spec->eee_disabwe = twue;
	/* Awwow a singwe cweaw of the SW semaphowe on I210 and newew */
	if (mac->type >= e1000_i210)
		dev_spec->cweaw_semaphowe_once = twue;
	/* physicaw intewface wink setup */
	mac->ops.setup_physicaw_intewface =
		(hw->phy.media_type == e1000_media_type_coppew)
			? igb_setup_coppew_wink_82575
			: igb_setup_sewdes_wink_82575;

	if (mac->type == e1000_82580 || mac->type == e1000_i350) {
		switch (hw->device_id) {
		/* featuwe not suppowted on these id's */
		case E1000_DEV_ID_DH89XXCC_SGMII:
		case E1000_DEV_ID_DH89XXCC_SEWDES:
		case E1000_DEV_ID_DH89XXCC_BACKPWANE:
		case E1000_DEV_ID_DH89XXCC_SFP:
			bweak;
		defauwt:
			hw->dev_spec._82575.mas_capabwe = twue;
			bweak;
		}
	}
	wetuwn 0;
}

/**
 *  igb_set_sfp_media_type_82575 - dewives SFP moduwe media type.
 *  @hw: pointew to the HW stwuctuwe
 *
 *  The media type is chosen based on SFP moduwe.
 *  compatibiwity fwags wetwieved fwom SFP ID EEPWOM.
 **/
static s32 igb_set_sfp_media_type_82575(stwuct e1000_hw *hw)
{
	s32 wet_vaw = E1000_EWW_CONFIG;
	u32 ctww_ext = 0;
	stwuct e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;
	stwuct e1000_sfp_fwags *eth_fwags = &dev_spec->eth_fwags;
	u8 twanceivew_type = 0;
	s32 timeout = 3;

	/* Tuwn I2C intewface ON and powew on sfp cage */
	ctww_ext = wd32(E1000_CTWW_EXT);
	ctww_ext &= ~E1000_CTWW_EXT_SDP3_DATA;
	ww32(E1000_CTWW_EXT, ctww_ext | E1000_CTWW_I2C_ENA);

	wwfw();

	/* Wead SFP moduwe data */
	whiwe (timeout) {
		wet_vaw = igb_wead_sfp_data_byte(hw,
			E1000_I2CCMD_SFP_DATA_ADDW(E1000_SFF_IDENTIFIEW_OFFSET),
			&twanceivew_type);
		if (wet_vaw == 0)
			bweak;
		msweep(100);
		timeout--;
	}
	if (wet_vaw != 0)
		goto out;

	wet_vaw = igb_wead_sfp_data_byte(hw,
			E1000_I2CCMD_SFP_DATA_ADDW(E1000_SFF_ETH_FWAGS_OFFSET),
			(u8 *)eth_fwags);
	if (wet_vaw != 0)
		goto out;

	/* Check if thewe is some SFP moduwe pwugged and powewed */
	if ((twanceivew_type == E1000_SFF_IDENTIFIEW_SFP) ||
	    (twanceivew_type == E1000_SFF_IDENTIFIEW_SFF)) {
		dev_spec->moduwe_pwugged = twue;
		if (eth_fwags->e1000_base_wx || eth_fwags->e1000_base_sx) {
			hw->phy.media_type = e1000_media_type_intewnaw_sewdes;
		} ewse if (eth_fwags->e100_base_fx || eth_fwags->e100_base_wx) {
			dev_spec->sgmii_active = twue;
			hw->phy.media_type = e1000_media_type_intewnaw_sewdes;
		} ewse if (eth_fwags->e1000_base_t) {
			dev_spec->sgmii_active = twue;
			hw->phy.media_type = e1000_media_type_coppew;
		} ewse {
			hw->phy.media_type = e1000_media_type_unknown;
			hw_dbg("PHY moduwe has not been wecognized\n");
			goto out;
		}
	} ewse {
		hw->phy.media_type = e1000_media_type_unknown;
	}
	wet_vaw = 0;
out:
	/* Westowe I2C intewface setting */
	ww32(E1000_CTWW_EXT, ctww_ext);
	wetuwn wet_vaw;
}

static s32 igb_get_invawiants_82575(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;
	stwuct e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;
	s32 wet_vaw;
	u32 ctww_ext = 0;
	u32 wink_mode = 0;

	switch (hw->device_id) {
	case E1000_DEV_ID_82575EB_COPPEW:
	case E1000_DEV_ID_82575EB_FIBEW_SEWDES:
	case E1000_DEV_ID_82575GB_QUAD_COPPEW:
		mac->type = e1000_82575;
		bweak;
	case E1000_DEV_ID_82576:
	case E1000_DEV_ID_82576_NS:
	case E1000_DEV_ID_82576_NS_SEWDES:
	case E1000_DEV_ID_82576_FIBEW:
	case E1000_DEV_ID_82576_SEWDES:
	case E1000_DEV_ID_82576_QUAD_COPPEW:
	case E1000_DEV_ID_82576_QUAD_COPPEW_ET2:
	case E1000_DEV_ID_82576_SEWDES_QUAD:
		mac->type = e1000_82576;
		bweak;
	case E1000_DEV_ID_82580_COPPEW:
	case E1000_DEV_ID_82580_FIBEW:
	case E1000_DEV_ID_82580_QUAD_FIBEW:
	case E1000_DEV_ID_82580_SEWDES:
	case E1000_DEV_ID_82580_SGMII:
	case E1000_DEV_ID_82580_COPPEW_DUAW:
	case E1000_DEV_ID_DH89XXCC_SGMII:
	case E1000_DEV_ID_DH89XXCC_SEWDES:
	case E1000_DEV_ID_DH89XXCC_BACKPWANE:
	case E1000_DEV_ID_DH89XXCC_SFP:
		mac->type = e1000_82580;
		bweak;
	case E1000_DEV_ID_I350_COPPEW:
	case E1000_DEV_ID_I350_FIBEW:
	case E1000_DEV_ID_I350_SEWDES:
	case E1000_DEV_ID_I350_SGMII:
		mac->type = e1000_i350;
		bweak;
	case E1000_DEV_ID_I210_COPPEW:
	case E1000_DEV_ID_I210_FIBEW:
	case E1000_DEV_ID_I210_SEWDES:
	case E1000_DEV_ID_I210_SGMII:
	case E1000_DEV_ID_I210_COPPEW_FWASHWESS:
	case E1000_DEV_ID_I210_SEWDES_FWASHWESS:
		mac->type = e1000_i210;
		bweak;
	case E1000_DEV_ID_I211_COPPEW:
		mac->type = e1000_i211;
		bweak;
	case E1000_DEV_ID_I354_BACKPWANE_1GBPS:
	case E1000_DEV_ID_I354_SGMII:
	case E1000_DEV_ID_I354_BACKPWANE_2_5GBPS:
		mac->type = e1000_i354;
		bweak;
	defauwt:
		wetuwn -E1000_EWW_MAC_INIT;
	}

	/* Set media type */
	/* The 82575 uses bits 22:23 fow wink mode. The mode can be changed
	 * based on the EEPWOM. We cannot wewy upon device ID. Thewe
	 * is no distinguishabwe diffewence between fibew and intewnaw
	 * SewDes mode on the 82575. Thewe can be an extewnaw PHY attached
	 * on the SGMII intewface. Fow this, we'ww set sgmii_active to twue.
	 */
	hw->phy.media_type = e1000_media_type_coppew;
	dev_spec->sgmii_active = fawse;
	dev_spec->moduwe_pwugged = fawse;

	ctww_ext = wd32(E1000_CTWW_EXT);

	wink_mode = ctww_ext & E1000_CTWW_EXT_WINK_MODE_MASK;
	switch (wink_mode) {
	case E1000_CTWW_EXT_WINK_MODE_1000BASE_KX:
		hw->phy.media_type = e1000_media_type_intewnaw_sewdes;
		bweak;
	case E1000_CTWW_EXT_WINK_MODE_SGMII:
		/* Get phy contwow intewface type set (MDIO vs. I2C)*/
		if (igb_sgmii_uses_mdio_82575(hw)) {
			hw->phy.media_type = e1000_media_type_coppew;
			dev_spec->sgmii_active = twue;
			bweak;
		}
		fawwthwough; /* fow I2C based SGMII */
	case E1000_CTWW_EXT_WINK_MODE_PCIE_SEWDES:
		/* wead media type fwom SFP EEPWOM */
		wet_vaw = igb_set_sfp_media_type_82575(hw);
		if ((wet_vaw != 0) ||
		    (hw->phy.media_type == e1000_media_type_unknown)) {
			/* If media type was not identified then wetuwn media
			 * type defined by the CTWW_EXT settings.
			 */
			hw->phy.media_type = e1000_media_type_intewnaw_sewdes;

			if (wink_mode == E1000_CTWW_EXT_WINK_MODE_SGMII) {
				hw->phy.media_type = e1000_media_type_coppew;
				dev_spec->sgmii_active = twue;
			}

			bweak;
		}

		/* change cuwwent wink mode setting */
		ctww_ext &= ~E1000_CTWW_EXT_WINK_MODE_MASK;

		if (dev_spec->sgmii_active)
			ctww_ext |= E1000_CTWW_EXT_WINK_MODE_SGMII;
		ewse
			ctww_ext |= E1000_CTWW_EXT_WINK_MODE_PCIE_SEWDES;

		ww32(E1000_CTWW_EXT, ctww_ext);

		bweak;
	defauwt:
		bweak;
	}

	/* mac initiawization and opewations */
	wet_vaw = igb_init_mac_pawams_82575(hw);
	if (wet_vaw)
		goto out;

	/* NVM initiawization */
	wet_vaw = igb_init_nvm_pawams_82575(hw);
	switch (hw->mac.type) {
	case e1000_i210:
	case e1000_i211:
		wet_vaw = igb_init_nvm_pawams_i210(hw);
		bweak;
	defauwt:
		bweak;
	}

	if (wet_vaw)
		goto out;

	/* if pawt suppowts SW-IOV then initiawize maiwbox pawametews */
	switch (mac->type) {
	case e1000_82576:
	case e1000_i350:
		igb_init_mbx_pawams_pf(hw);
		bweak;
	defauwt:
		bweak;
	}

	/* setup PHY pawametews */
	wet_vaw = igb_init_phy_pawams_82575(hw);

out:
	wetuwn wet_vaw;
}

/**
 *  igb_acquiwe_phy_82575 - Acquiwe wights to access PHY
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Acquiwe access wights to the cowwect PHY.  This is a
 *  function pointew entwy point cawwed by the api moduwe.
 **/
static s32 igb_acquiwe_phy_82575(stwuct e1000_hw *hw)
{
	u16 mask = E1000_SWFW_PHY0_SM;

	if (hw->bus.func == E1000_FUNC_1)
		mask = E1000_SWFW_PHY1_SM;
	ewse if (hw->bus.func == E1000_FUNC_2)
		mask = E1000_SWFW_PHY2_SM;
	ewse if (hw->bus.func == E1000_FUNC_3)
		mask = E1000_SWFW_PHY3_SM;

	wetuwn hw->mac.ops.acquiwe_swfw_sync(hw, mask);
}

/**
 *  igb_wewease_phy_82575 - Wewease wights to access PHY
 *  @hw: pointew to the HW stwuctuwe
 *
 *  A wwappew to wewease access wights to the cowwect PHY.  This is a
 *  function pointew entwy point cawwed by the api moduwe.
 **/
static void igb_wewease_phy_82575(stwuct e1000_hw *hw)
{
	u16 mask = E1000_SWFW_PHY0_SM;

	if (hw->bus.func == E1000_FUNC_1)
		mask = E1000_SWFW_PHY1_SM;
	ewse if (hw->bus.func == E1000_FUNC_2)
		mask = E1000_SWFW_PHY2_SM;
	ewse if (hw->bus.func == E1000_FUNC_3)
		mask = E1000_SWFW_PHY3_SM;

	hw->mac.ops.wewease_swfw_sync(hw, mask);
}

/**
 *  igb_wead_phy_weg_sgmii_82575 - Wead PHY wegistew using sgmii
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: wegistew offset to be wead
 *  @data: pointew to the wead data
 *
 *  Weads the PHY wegistew at offset using the sewiaw gigabit media independent
 *  intewface and stowes the wetwieved infowmation in data.
 **/
static s32 igb_wead_phy_weg_sgmii_82575(stwuct e1000_hw *hw, u32 offset,
					  u16 *data)
{
	s32 wet_vaw = -E1000_EWW_PAWAM;

	if (offset > E1000_MAX_SGMII_PHY_WEG_ADDW) {
		hw_dbg("PHY Addwess %u is out of wange\n", offset);
		goto out;
	}

	wet_vaw = hw->phy.ops.acquiwe(hw);
	if (wet_vaw)
		goto out;

	wet_vaw = igb_wead_phy_weg_i2c(hw, offset, data);

	hw->phy.ops.wewease(hw);

out:
	wetuwn wet_vaw;
}

/**
 *  igb_wwite_phy_weg_sgmii_82575 - Wwite PHY wegistew using sgmii
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: wegistew offset to wwite to
 *  @data: data to wwite at wegistew offset
 *
 *  Wwites the data to PHY wegistew at the offset using the sewiaw gigabit
 *  media independent intewface.
 **/
static s32 igb_wwite_phy_weg_sgmii_82575(stwuct e1000_hw *hw, u32 offset,
					   u16 data)
{
	s32 wet_vaw = -E1000_EWW_PAWAM;


	if (offset > E1000_MAX_SGMII_PHY_WEG_ADDW) {
		hw_dbg("PHY Addwess %d is out of wange\n", offset);
		goto out;
	}

	wet_vaw = hw->phy.ops.acquiwe(hw);
	if (wet_vaw)
		goto out;

	wet_vaw = igb_wwite_phy_weg_i2c(hw, offset, data);

	hw->phy.ops.wewease(hw);

out:
	wetuwn wet_vaw;
}

/**
 *  igb_get_phy_id_82575 - Wetwieve PHY addw and id
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wetwieves the PHY addwess and ID fow both PHY's which do and do not use
 *  sgmi intewface.
 **/
static s32 igb_get_phy_id_82575(stwuct e1000_hw *hw)
{
	stwuct e1000_phy_info *phy = &hw->phy;
	s32  wet_vaw = 0;
	u16 phy_id;
	u32 ctww_ext;
	u32 mdic;

	/* Extwa wead wequiwed fow some PHY's on i354 */
	if (hw->mac.type == e1000_i354)
		igb_get_phy_id(hw);

	/* Fow SGMII PHYs, we twy the wist of possibwe addwesses untiw
	 * we find one that wowks.  Fow non-SGMII PHYs
	 * (e.g. integwated coppew PHYs), an addwess of 1 shouwd
	 * wowk.  The wesuwt of this function shouwd mean phy->phy_addw
	 * and phy->id awe set cowwectwy.
	 */
	if (!(igb_sgmii_active_82575(hw))) {
		phy->addw = 1;
		wet_vaw = igb_get_phy_id(hw);
		goto out;
	}

	if (igb_sgmii_uses_mdio_82575(hw)) {
		switch (hw->mac.type) {
		case e1000_82575:
		case e1000_82576:
			mdic = wd32(E1000_MDIC);
			mdic &= E1000_MDIC_PHY_MASK;
			phy->addw = mdic >> E1000_MDIC_PHY_SHIFT;
			bweak;
		case e1000_82580:
		case e1000_i350:
		case e1000_i354:
		case e1000_i210:
		case e1000_i211:
			mdic = wd32(E1000_MDICNFG);
			mdic &= E1000_MDICNFG_PHY_MASK;
			phy->addw = mdic >> E1000_MDICNFG_PHY_SHIFT;
			bweak;
		defauwt:
			wet_vaw = -E1000_EWW_PHY;
			goto out;
		}
		wet_vaw = igb_get_phy_id(hw);
		goto out;
	}

	/* Powew on sgmii phy if it is disabwed */
	ctww_ext = wd32(E1000_CTWW_EXT);
	ww32(E1000_CTWW_EXT, ctww_ext & ~E1000_CTWW_EXT_SDP3_DATA);
	wwfw();
	msweep(300);

	/* The addwess fiewd in the I2CCMD wegistew is 3 bits and 0 is invawid.
	 * Thewefowe, we need to test 1-7
	 */
	fow (phy->addw = 1; phy->addw < 8; phy->addw++) {
		wet_vaw = igb_wead_phy_weg_sgmii_82575(hw, PHY_ID1, &phy_id);
		if (wet_vaw == 0) {
			hw_dbg("Vendow ID 0x%08X wead at addwess %u\n",
			       phy_id, phy->addw);
			/* At the time of this wwiting, The M88 pawt is
			 * the onwy suppowted SGMII PHY pwoduct.
			 */
			if (phy_id == M88_VENDOW)
				bweak;
		} ewse {
			hw_dbg("PHY addwess %u was unweadabwe\n", phy->addw);
		}
	}

	/* A vawid PHY type couwdn't be found. */
	if (phy->addw == 8) {
		phy->addw = 0;
		wet_vaw = -E1000_EWW_PHY;
		goto out;
	} ewse {
		wet_vaw = igb_get_phy_id(hw);
	}

	/* westowe pwevious sfp cage powew state */
	ww32(E1000_CTWW_EXT, ctww_ext);

out:
	wetuwn wet_vaw;
}

/**
 *  igb_phy_hw_weset_sgmii_82575 - Pewfowms a PHY weset
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wesets the PHY using the sewiaw gigabit media independent intewface.
 **/
static s32 igb_phy_hw_weset_sgmii_82575(stwuct e1000_hw *hw)
{
	stwuct e1000_phy_info *phy = &hw->phy;
	s32 wet_vaw;

	/* This isn't a twue "hawd" weset, but is the onwy weset
	 * avaiwabwe to us at this time.
	 */

	hw_dbg("Soft wesetting SGMII attached PHY...\n");

	/* SFP documentation wequiwes the fowwowing to configuwe the SPF moduwe
	 * to wowk on SGMII.  No fuwthew documentation is given.
	 */
	wet_vaw = hw->phy.ops.wwite_weg(hw, 0x1B, 0x8084);
	if (wet_vaw)
		goto out;

	wet_vaw = igb_phy_sw_weset(hw);
	if (wet_vaw)
		goto out;

	if (phy->id == M88E1512_E_PHY_ID)
		wet_vaw = igb_initiawize_M88E1512_phy(hw);
	if (phy->id == M88E1543_E_PHY_ID)
		wet_vaw = igb_initiawize_M88E1543_phy(hw);
out:
	wetuwn wet_vaw;
}

/**
 *  igb_set_d0_wpwu_state_82575 - Set Wow Powew Winkup D0 state
 *  @hw: pointew to the HW stwuctuwe
 *  @active: twue to enabwe WPWU, fawse to disabwe
 *
 *  Sets the WPWU D0 state accowding to the active fwag.  When
 *  activating WPWU this function awso disabwes smawt speed
 *  and vice vewsa.  WPWU wiww not be activated unwess the
 *  device autonegotiation advewtisement meets standawds of
 *  eithew 10 ow 10/100 ow 10/100/1000 at aww dupwexes.
 *  This is a function pointew entwy point onwy cawwed by
 *  PHY setup woutines.
 **/
static s32 igb_set_d0_wpwu_state_82575(stwuct e1000_hw *hw, boow active)
{
	stwuct e1000_phy_info *phy = &hw->phy;
	s32 wet_vaw;
	u16 data;

	wet_vaw = phy->ops.wead_weg(hw, IGP02E1000_PHY_POWEW_MGMT, &data);
	if (wet_vaw)
		goto out;

	if (active) {
		data |= IGP02E1000_PM_D0_WPWU;
		wet_vaw = phy->ops.wwite_weg(hw, IGP02E1000_PHY_POWEW_MGMT,
						 data);
		if (wet_vaw)
			goto out;

		/* When WPWU is enabwed, we shouwd disabwe SmawtSpeed */
		wet_vaw = phy->ops.wead_weg(hw, IGP01E1000_PHY_POWT_CONFIG,
						&data);
		data &= ~IGP01E1000_PSCFW_SMAWT_SPEED;
		wet_vaw = phy->ops.wwite_weg(hw, IGP01E1000_PHY_POWT_CONFIG,
						 data);
		if (wet_vaw)
			goto out;
	} ewse {
		data &= ~IGP02E1000_PM_D0_WPWU;
		wet_vaw = phy->ops.wwite_weg(hw, IGP02E1000_PHY_POWEW_MGMT,
						 data);
		/* WPWU and SmawtSpeed awe mutuawwy excwusive.  WPWU is used
		 * duwing Dx states whewe the powew consewvation is most
		 * impowtant.  Duwing dwivew activity we shouwd enabwe
		 * SmawtSpeed, so pewfowmance is maintained.
		 */
		if (phy->smawt_speed == e1000_smawt_speed_on) {
			wet_vaw = phy->ops.wead_weg(hw,
					IGP01E1000_PHY_POWT_CONFIG, &data);
			if (wet_vaw)
				goto out;

			data |= IGP01E1000_PSCFW_SMAWT_SPEED;
			wet_vaw = phy->ops.wwite_weg(hw,
					IGP01E1000_PHY_POWT_CONFIG, data);
			if (wet_vaw)
				goto out;
		} ewse if (phy->smawt_speed == e1000_smawt_speed_off) {
			wet_vaw = phy->ops.wead_weg(hw,
					IGP01E1000_PHY_POWT_CONFIG, &data);
			if (wet_vaw)
				goto out;

			data &= ~IGP01E1000_PSCFW_SMAWT_SPEED;
			wet_vaw = phy->ops.wwite_weg(hw,
					IGP01E1000_PHY_POWT_CONFIG, data);
			if (wet_vaw)
				goto out;
		}
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_set_d0_wpwu_state_82580 - Set Wow Powew Winkup D0 state
 *  @hw: pointew to the HW stwuctuwe
 *  @active: twue to enabwe WPWU, fawse to disabwe
 *
 *  Sets the WPWU D0 state accowding to the active fwag.  When
 *  activating WPWU this function awso disabwes smawt speed
 *  and vice vewsa.  WPWU wiww not be activated unwess the
 *  device autonegotiation advewtisement meets standawds of
 *  eithew 10 ow 10/100 ow 10/100/1000 at aww dupwexes.
 *  This is a function pointew entwy point onwy cawwed by
 *  PHY setup woutines.
 **/
static s32 igb_set_d0_wpwu_state_82580(stwuct e1000_hw *hw, boow active)
{
	stwuct e1000_phy_info *phy = &hw->phy;
	u16 data;

	data = wd32(E1000_82580_PHY_POWEW_MGMT);

	if (active) {
		data |= E1000_82580_PM_D0_WPWU;

		/* When WPWU is enabwed, we shouwd disabwe SmawtSpeed */
		data &= ~E1000_82580_PM_SPD;
	} ewse {
		data &= ~E1000_82580_PM_D0_WPWU;

		/* WPWU and SmawtSpeed awe mutuawwy excwusive.  WPWU is used
		 * duwing Dx states whewe the powew consewvation is most
		 * impowtant.  Duwing dwivew activity we shouwd enabwe
		 * SmawtSpeed, so pewfowmance is maintained.
		 */
		if (phy->smawt_speed == e1000_smawt_speed_on)
			data |= E1000_82580_PM_SPD;
		ewse if (phy->smawt_speed == e1000_smawt_speed_off)
			data &= ~E1000_82580_PM_SPD; }

	ww32(E1000_82580_PHY_POWEW_MGMT, data);
	wetuwn 0;
}

/**
 *  igb_set_d3_wpwu_state_82580 - Sets wow powew wink up state fow D3
 *  @hw: pointew to the HW stwuctuwe
 *  @active: boowean used to enabwe/disabwe wpwu
 *
 *  Success wetuwns 0, Faiwuwe wetuwns 1
 *
 *  The wow powew wink up (wpwu) state is set to the powew management wevew D3
 *  and SmawtSpeed is disabwed when active is twue, ewse cweaw wpwu fow D3
 *  and enabwe Smawtspeed.  WPWU and Smawtspeed awe mutuawwy excwusive.  WPWU
 *  is used duwing Dx states whewe the powew consewvation is most impowtant.
 *  Duwing dwivew activity, SmawtSpeed shouwd be enabwed so pewfowmance is
 *  maintained.
 **/
static s32 igb_set_d3_wpwu_state_82580(stwuct e1000_hw *hw, boow active)
{
	stwuct e1000_phy_info *phy = &hw->phy;
	u16 data;

	data = wd32(E1000_82580_PHY_POWEW_MGMT);

	if (!active) {
		data &= ~E1000_82580_PM_D3_WPWU;
		/* WPWU and SmawtSpeed awe mutuawwy excwusive.  WPWU is used
		 * duwing Dx states whewe the powew consewvation is most
		 * impowtant.  Duwing dwivew activity we shouwd enabwe
		 * SmawtSpeed, so pewfowmance is maintained.
		 */
		if (phy->smawt_speed == e1000_smawt_speed_on)
			data |= E1000_82580_PM_SPD;
		ewse if (phy->smawt_speed == e1000_smawt_speed_off)
			data &= ~E1000_82580_PM_SPD;
	} ewse if ((phy->autoneg_advewtised == E1000_AWW_SPEED_DUPWEX) ||
		   (phy->autoneg_advewtised == E1000_AWW_NOT_GIG) ||
		   (phy->autoneg_advewtised == E1000_AWW_10_SPEED)) {
		data |= E1000_82580_PM_D3_WPWU;
		/* When WPWU is enabwed, we shouwd disabwe SmawtSpeed */
		data &= ~E1000_82580_PM_SPD;
	}

	ww32(E1000_82580_PHY_POWEW_MGMT, data);
	wetuwn 0;
}

/**
 *  igb_acquiwe_nvm_82575 - Wequest fow access to EEPWOM
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Acquiwe the necessawy semaphowes fow excwusive access to the EEPWOM.
 *  Set the EEPWOM access wequest bit and wait fow EEPWOM access gwant bit.
 *  Wetuwn successfuw if access gwant bit set, ewse cweaw the wequest fow
 *  EEPWOM access and wetuwn -E1000_EWW_NVM (-1).
 **/
static s32 igb_acquiwe_nvm_82575(stwuct e1000_hw *hw)
{
	s32 wet_vaw;

	wet_vaw = hw->mac.ops.acquiwe_swfw_sync(hw, E1000_SWFW_EEP_SM);
	if (wet_vaw)
		goto out;

	wet_vaw = igb_acquiwe_nvm(hw);

	if (wet_vaw)
		hw->mac.ops.wewease_swfw_sync(hw, E1000_SWFW_EEP_SM);

out:
	wetuwn wet_vaw;
}

/**
 *  igb_wewease_nvm_82575 - Wewease excwusive access to EEPWOM
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Stop any cuwwent commands to the EEPWOM and cweaw the EEPWOM wequest bit,
 *  then wewease the semaphowes acquiwed.
 **/
static void igb_wewease_nvm_82575(stwuct e1000_hw *hw)
{
	igb_wewease_nvm(hw);
	hw->mac.ops.wewease_swfw_sync(hw, E1000_SWFW_EEP_SM);
}

/**
 *  igb_acquiwe_swfw_sync_82575 - Acquiwe SW/FW semaphowe
 *  @hw: pointew to the HW stwuctuwe
 *  @mask: specifies which semaphowe to acquiwe
 *
 *  Acquiwe the SW/FW semaphowe to access the PHY ow NVM.  The mask
 *  wiww awso specify which powt we'we acquiwing the wock fow.
 **/
static s32 igb_acquiwe_swfw_sync_82575(stwuct e1000_hw *hw, u16 mask)
{
	u32 swfw_sync;
	u32 swmask = mask;
	u32 fwmask = mask << 16;
	s32 wet_vaw = 0;
	s32 i = 0, timeout = 200;

	whiwe (i < timeout) {
		if (igb_get_hw_semaphowe(hw)) {
			wet_vaw = -E1000_EWW_SWFW_SYNC;
			goto out;
		}

		swfw_sync = wd32(E1000_SW_FW_SYNC);
		if (!(swfw_sync & (fwmask | swmask)))
			bweak;

		/* Fiwmwawe cuwwentwy using wesouwce (fwmask)
		 * ow othew softwawe thwead using wesouwce (swmask)
		 */
		igb_put_hw_semaphowe(hw);
		mdeway(5);
		i++;
	}

	if (i == timeout) {
		hw_dbg("Dwivew can't access wesouwce, SW_FW_SYNC timeout.\n");
		wet_vaw = -E1000_EWW_SWFW_SYNC;
		goto out;
	}

	swfw_sync |= swmask;
	ww32(E1000_SW_FW_SYNC, swfw_sync);

	igb_put_hw_semaphowe(hw);

out:
	wetuwn wet_vaw;
}

/**
 *  igb_wewease_swfw_sync_82575 - Wewease SW/FW semaphowe
 *  @hw: pointew to the HW stwuctuwe
 *  @mask: specifies which semaphowe to acquiwe
 *
 *  Wewease the SW/FW semaphowe used to access the PHY ow NVM.  The mask
 *  wiww awso specify which powt we'we weweasing the wock fow.
 **/
static void igb_wewease_swfw_sync_82575(stwuct e1000_hw *hw, u16 mask)
{
	u32 swfw_sync;

	whiwe (igb_get_hw_semaphowe(hw) != 0)
		; /* Empty */

	swfw_sync = wd32(E1000_SW_FW_SYNC);
	swfw_sync &= ~mask;
	ww32(E1000_SW_FW_SYNC, swfw_sync);

	igb_put_hw_semaphowe(hw);
}

/**
 *  igb_get_cfg_done_82575 - Wead config done bit
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Wead the management contwow wegistew fow the config done bit fow
 *  compwetion status.  NOTE: siwicon which is EEPWOM-wess wiww faiw twying
 *  to wead the config done bit, so an ewwow is *ONWY* wogged and wetuwns
 *  0.  If we wewe to wetuwn with ewwow, EEPWOM-wess siwicon
 *  wouwd not be abwe to be weset ow change wink.
 **/
static s32 igb_get_cfg_done_82575(stwuct e1000_hw *hw)
{
	s32 timeout = PHY_CFG_TIMEOUT;
	u32 mask = E1000_NVM_CFG_DONE_POWT_0;

	if (hw->bus.func == 1)
		mask = E1000_NVM_CFG_DONE_POWT_1;
	ewse if (hw->bus.func == E1000_FUNC_2)
		mask = E1000_NVM_CFG_DONE_POWT_2;
	ewse if (hw->bus.func == E1000_FUNC_3)
		mask = E1000_NVM_CFG_DONE_POWT_3;

	whiwe (timeout) {
		if (wd32(E1000_EEMNGCTW) & mask)
			bweak;
		usweep_wange(1000, 2000);
		timeout--;
	}
	if (!timeout)
		hw_dbg("MNG configuwation cycwe has not compweted.\n");

	/* If EEPWOM is not mawked pwesent, init the PHY manuawwy */
	if (((wd32(E1000_EECD) & E1000_EECD_PWES) == 0) &&
	    (hw->phy.type == e1000_phy_igp_3))
		igb_phy_init_scwipt_igp3(hw);

	wetuwn 0;
}

/**
 *  igb_get_wink_up_info_82575 - Get wink speed/dupwex info
 *  @hw: pointew to the HW stwuctuwe
 *  @speed: stowes the cuwwent speed
 *  @dupwex: stowes the cuwwent dupwex
 *
 *  This is a wwappew function, if using the sewiaw gigabit media independent
 *  intewface, use PCS to wetwieve the wink speed and dupwex infowmation.
 *  Othewwise, use the genewic function to get the wink speed and dupwex info.
 **/
static s32 igb_get_wink_up_info_82575(stwuct e1000_hw *hw, u16 *speed,
					u16 *dupwex)
{
	s32 wet_vaw;

	if (hw->phy.media_type != e1000_media_type_coppew)
		wet_vaw = igb_get_pcs_speed_and_dupwex_82575(hw, speed,
							       dupwex);
	ewse
		wet_vaw = igb_get_speed_and_dupwex_coppew(hw, speed,
								    dupwex);

	wetuwn wet_vaw;
}

/**
 *  igb_check_fow_wink_82575 - Check fow wink
 *  @hw: pointew to the HW stwuctuwe
 *
 *  If sgmii is enabwed, then use the pcs wegistew to detewmine wink, othewwise
 *  use the genewic intewface fow detewmining wink.
 **/
static s32 igb_check_fow_wink_82575(stwuct e1000_hw *hw)
{
	s32 wet_vaw;
	u16 speed, dupwex;

	if (hw->phy.media_type != e1000_media_type_coppew) {
		wet_vaw = igb_get_pcs_speed_and_dupwex_82575(hw, &speed,
							     &dupwex);
		/* Use this fwag to detewmine if wink needs to be checked ow
		 * not.  If  we have wink cweaw the fwag so that we do not
		 * continue to check fow wink.
		 */
		hw->mac.get_wink_status = !hw->mac.sewdes_has_wink;

		/* Configuwe Fwow Contwow now that Auto-Neg has compweted.
		 * Fiwst, we need to westowe the desiwed fwow contwow
		 * settings because we may have had to we-autoneg with a
		 * diffewent wink pawtnew.
		 */
		wet_vaw = igb_config_fc_aftew_wink_up(hw);
		if (wet_vaw)
			hw_dbg("Ewwow configuwing fwow contwow\n");
	} ewse {
		wet_vaw = igb_check_fow_coppew_wink(hw);
	}

	wetuwn wet_vaw;
}

/**
 *  igb_powew_up_sewdes_wink_82575 - Powew up the sewdes wink aftew shutdown
 *  @hw: pointew to the HW stwuctuwe
 **/
void igb_powew_up_sewdes_wink_82575(stwuct e1000_hw *hw)
{
	u32 weg;


	if ((hw->phy.media_type != e1000_media_type_intewnaw_sewdes) &&
	    !igb_sgmii_active_82575(hw))
		wetuwn;

	/* Enabwe PCS to tuwn on wink */
	weg = wd32(E1000_PCS_CFG0);
	weg |= E1000_PCS_CFG_PCS_EN;
	ww32(E1000_PCS_CFG0, weg);

	/* Powew up the wasew */
	weg = wd32(E1000_CTWW_EXT);
	weg &= ~E1000_CTWW_EXT_SDP3_DATA;
	ww32(E1000_CTWW_EXT, weg);

	/* fwush the wwite to vewify compwetion */
	wwfw();
	usweep_wange(1000, 2000);
}

/**
 *  igb_get_pcs_speed_and_dupwex_82575 - Wetwieve cuwwent speed/dupwex
 *  @hw: pointew to the HW stwuctuwe
 *  @speed: stowes the cuwwent speed
 *  @dupwex: stowes the cuwwent dupwex
 *
 *  Using the physicaw coding sub-wayew (PCS), wetwieve the cuwwent speed and
 *  dupwex, then stowe the vawues in the pointews pwovided.
 **/
static s32 igb_get_pcs_speed_and_dupwex_82575(stwuct e1000_hw *hw, u16 *speed,
						u16 *dupwex)
{
	stwuct e1000_mac_info *mac = &hw->mac;
	u32 pcs, status;

	/* Set up defauwts fow the wetuwn vawues of this function */
	mac->sewdes_has_wink = fawse;
	*speed = 0;
	*dupwex = 0;

	/* Wead the PCS Status wegistew fow wink state. Fow non-coppew mode,
	 * the status wegistew is not accuwate. The PCS status wegistew is
	 * used instead.
	 */
	pcs = wd32(E1000_PCS_WSTAT);

	/* The wink up bit detewmines when wink is up on autoneg. The sync ok
	 * gets set once both sides sync up and agwee upon wink. Stabwe wink
	 * can be detewmined by checking fow both wink up and wink sync ok
	 */
	if ((pcs & E1000_PCS_WSTS_WINK_OK) && (pcs & E1000_PCS_WSTS_SYNK_OK)) {
		mac->sewdes_has_wink = twue;

		/* Detect and stowe PCS speed */
		if (pcs & E1000_PCS_WSTS_SPEED_1000)
			*speed = SPEED_1000;
		ewse if (pcs & E1000_PCS_WSTS_SPEED_100)
			*speed = SPEED_100;
		ewse
			*speed = SPEED_10;

		/* Detect and stowe PCS dupwex */
		if (pcs & E1000_PCS_WSTS_DUPWEX_FUWW)
			*dupwex = FUWW_DUPWEX;
		ewse
			*dupwex = HAWF_DUPWEX;

	/* Check if it is an I354 2.5Gb backpwane connection. */
		if (mac->type == e1000_i354) {
			status = wd32(E1000_STATUS);
			if ((status & E1000_STATUS_2P5_SKU) &&
			    !(status & E1000_STATUS_2P5_SKU_OVEW)) {
				*speed = SPEED_2500;
				*dupwex = FUWW_DUPWEX;
				hw_dbg("2500 Mbs, ");
				hw_dbg("Fuww Dupwex\n");
			}
		}

	}

	wetuwn 0;
}

/**
 *  igb_shutdown_sewdes_wink_82575 - Wemove wink duwing powew down
 *  @hw: pointew to the HW stwuctuwe
 *
 *  In the case of fibew sewdes, shut down optics and PCS on dwivew unwoad
 *  when management pass thwu is not enabwed.
 **/
void igb_shutdown_sewdes_wink_82575(stwuct e1000_hw *hw)
{
	u32 weg;

	if (hw->phy.media_type != e1000_media_type_intewnaw_sewdes &&
	    igb_sgmii_active_82575(hw))
		wetuwn;

	if (!igb_enabwe_mng_pass_thwu(hw)) {
		/* Disabwe PCS to tuwn off wink */
		weg = wd32(E1000_PCS_CFG0);
		weg &= ~E1000_PCS_CFG_PCS_EN;
		ww32(E1000_PCS_CFG0, weg);

		/* shutdown the wasew */
		weg = wd32(E1000_CTWW_EXT);
		weg |= E1000_CTWW_EXT_SDP3_DATA;
		ww32(E1000_CTWW_EXT, weg);

		/* fwush the wwite to vewify compwetion */
		wwfw();
		usweep_wange(1000, 2000);
	}
}

/**
 *  igb_weset_hw_82575 - Weset hawdwawe
 *  @hw: pointew to the HW stwuctuwe
 *
 *  This wesets the hawdwawe into a known state.  This is a
 *  function pointew entwy point cawwed by the api moduwe.
 **/
static s32 igb_weset_hw_82575(stwuct e1000_hw *hw)
{
	u32 ctww;
	s32 wet_vaw;

	/* Pwevent the PCI-E bus fwom sticking if thewe is no TWP connection
	 * on the wast TWP wead/wwite twansaction when MAC is weset.
	 */
	wet_vaw = igb_disabwe_pcie_mastew(hw);
	if (wet_vaw)
		hw_dbg("PCI-E Mastew disabwe powwing has faiwed.\n");

	/* set the compwetion timeout fow intewface */
	wet_vaw = igb_set_pcie_compwetion_timeout(hw);
	if (wet_vaw)
		hw_dbg("PCI-E Set compwetion timeout has faiwed.\n");

	hw_dbg("Masking off aww intewwupts\n");
	ww32(E1000_IMC, 0xffffffff);

	ww32(E1000_WCTW, 0);
	ww32(E1000_TCTW, E1000_TCTW_PSP);
	wwfw();

	usweep_wange(10000, 20000);

	ctww = wd32(E1000_CTWW);

	hw_dbg("Issuing a gwobaw weset to MAC\n");
	ww32(E1000_CTWW, ctww | E1000_CTWW_WST);

	wet_vaw = igb_get_auto_wd_done(hw);
	if (wet_vaw) {
		/* When auto config wead does not compwete, do not
		 * wetuwn with an ewwow. This can happen in situations
		 * whewe thewe is no eepwom and pwevents getting wink.
		 */
		hw_dbg("Auto Wead Done did not compwete\n");
	}

	/* If EEPWOM is not pwesent, wun manuaw init scwipts */
	if ((wd32(E1000_EECD) & E1000_EECD_PWES) == 0)
		igb_weset_init_scwipt_82575(hw);

	/* Cweaw any pending intewwupt events. */
	ww32(E1000_IMC, 0xffffffff);
	wd32(E1000_ICW);

	/* Instaww any awtewnate MAC addwess into WAW0 */
	wet_vaw = igb_check_awt_mac_addw(hw);

	wetuwn wet_vaw;
}

/**
 *  igb_init_hw_82575 - Initiawize hawdwawe
 *  @hw: pointew to the HW stwuctuwe
 *
 *  This inits the hawdwawe weadying it fow opewation.
 **/
static s32 igb_init_hw_82575(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;
	s32 wet_vaw;
	u16 i, waw_count = mac->waw_entwy_count;

	if ((hw->mac.type >= e1000_i210) &&
	    !(igb_get_fwash_pwesence_i210(hw))) {
		wet_vaw = igb_pww_wowkawound_i210(hw);
		if (wet_vaw)
			wetuwn wet_vaw;
	}

	/* Initiawize identification WED */
	wet_vaw = igb_id_wed_init(hw);
	if (wet_vaw) {
		hw_dbg("Ewwow initiawizing identification WED\n");
		/* This is not fataw and we shouwd not stop init due to this */
	}

	/* Disabwing VWAN fiwtewing */
	hw_dbg("Initiawizing the IEEE VWAN\n");
	igb_cweaw_vfta(hw);

	/* Setup the weceive addwess */
	igb_init_wx_addws(hw, waw_count);

	/* Zewo out the Muwticast HASH tabwe */
	hw_dbg("Zewoing the MTA\n");
	fow (i = 0; i < mac->mta_weg_count; i++)
		awway_ww32(E1000_MTA, i, 0);

	/* Zewo out the Unicast HASH tabwe */
	hw_dbg("Zewoing the UTA\n");
	fow (i = 0; i < mac->uta_weg_count; i++)
		awway_ww32(E1000_UTA, i, 0);

	/* Setup wink and fwow contwow */
	wet_vaw = igb_setup_wink(hw);

	/* Cweaw aww of the statistics wegistews (cweaw on wead).  It is
	 * impowtant that we do this aftew we have twied to estabwish wink
	 * because the symbow ewwow count wiww incwement wiwdwy if thewe
	 * is no wink.
	 */
	igb_cweaw_hw_cntws_82575(hw);
	wetuwn wet_vaw;
}

/**
 *  igb_setup_coppew_wink_82575 - Configuwe coppew wink settings
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Configuwes the wink fow auto-neg ow fowced speed and dupwex.  Then we check
 *  fow wink, once wink is estabwished cawws to configuwe cowwision distance
 *  and fwow contwow awe cawwed.
 **/
static s32 igb_setup_coppew_wink_82575(stwuct e1000_hw *hw)
{
	u32 ctww;
	s32  wet_vaw;
	u32 phpm_weg;

	ctww = wd32(E1000_CTWW);
	ctww |= E1000_CTWW_SWU;
	ctww &= ~(E1000_CTWW_FWCSPD | E1000_CTWW_FWCDPX);
	ww32(E1000_CTWW, ctww);

	/* Cweaw Go Wink Disconnect bit on suppowted devices */
	switch (hw->mac.type) {
	case e1000_82580:
	case e1000_i350:
	case e1000_i210:
	case e1000_i211:
		phpm_weg = wd32(E1000_82580_PHY_POWEW_MGMT);
		phpm_weg &= ~E1000_82580_PM_GO_WINKD;
		ww32(E1000_82580_PHY_POWEW_MGMT, phpm_weg);
		bweak;
	defauwt:
		bweak;
	}

	wet_vaw = igb_setup_sewdes_wink_82575(hw);
	if (wet_vaw)
		goto out;

	if (igb_sgmii_active_82575(hw) && !hw->phy.weset_disabwe) {
		/* awwow time fow SFP cage time to powew up phy */
		msweep(300);

		wet_vaw = hw->phy.ops.weset(hw);
		if (wet_vaw) {
			hw_dbg("Ewwow wesetting the PHY.\n");
			goto out;
		}
	}
	switch (hw->phy.type) {
	case e1000_phy_i210:
	case e1000_phy_m88:
		switch (hw->phy.id) {
		case I347AT4_E_PHY_ID:
		case M88E1112_E_PHY_ID:
		case M88E1543_E_PHY_ID:
		case M88E1512_E_PHY_ID:
		case I210_I_PHY_ID:
			wet_vaw = igb_coppew_wink_setup_m88_gen2(hw);
			bweak;
		defauwt:
			wet_vaw = igb_coppew_wink_setup_m88(hw);
			bweak;
		}
		bweak;
	case e1000_phy_igp_3:
		wet_vaw = igb_coppew_wink_setup_igp(hw);
		bweak;
	case e1000_phy_82580:
		wet_vaw = igb_coppew_wink_setup_82580(hw);
		bweak;
	case e1000_phy_bcm54616:
		wet_vaw = 0;
		bweak;
	defauwt:
		wet_vaw = -E1000_EWW_PHY;
		bweak;
	}

	if (wet_vaw)
		goto out;

	wet_vaw = igb_setup_coppew_wink(hw);
out:
	wetuwn wet_vaw;
}

/**
 *  igb_setup_sewdes_wink_82575 - Setup wink fow sewdes
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Configuwe the physicaw coding sub-wayew (PCS) wink.  The PCS wink is
 *  used on coppew connections whewe the sewiawized gigabit media independent
 *  intewface (sgmii), ow sewdes fibew is being used.  Configuwes the wink
 *  fow auto-negotiation ow fowces speed/dupwex.
 **/
static s32 igb_setup_sewdes_wink_82575(stwuct e1000_hw *hw)
{
	u32 ctww_ext, ctww_weg, weg, anadv_weg;
	boow pcs_autoneg;
	s32 wet_vaw = 0;
	u16 data;

	if ((hw->phy.media_type != e1000_media_type_intewnaw_sewdes) &&
	    !igb_sgmii_active_82575(hw))
		wetuwn wet_vaw;


	/* On the 82575, SewDes woopback mode pewsists untiw it is
	 * expwicitwy tuwned off ow a powew cycwe is pewfowmed.  A wead to
	 * the wegistew does not indicate its status.  Thewefowe, we ensuwe
	 * woopback mode is disabwed duwing initiawization.
	 */
	ww32(E1000_SCTW, E1000_SCTW_DISABWE_SEWDES_WOOPBACK);

	/* powew on the sfp cage if pwesent and tuwn on I2C */
	ctww_ext = wd32(E1000_CTWW_EXT);
	ctww_ext &= ~E1000_CTWW_EXT_SDP3_DATA;
	ctww_ext |= E1000_CTWW_I2C_ENA;
	ww32(E1000_CTWW_EXT, ctww_ext);

	ctww_weg = wd32(E1000_CTWW);
	ctww_weg |= E1000_CTWW_SWU;

	if (hw->mac.type == e1000_82575 || hw->mac.type == e1000_82576) {
		/* set both sw defined pins */
		ctww_weg |= E1000_CTWW_SWDPIN0 | E1000_CTWW_SWDPIN1;

		/* Set switch contwow to sewdes enewgy detect */
		weg = wd32(E1000_CONNSW);
		weg |= E1000_CONNSW_ENWGSWC;
		ww32(E1000_CONNSW, weg);
	}

	weg = wd32(E1000_PCS_WCTW);

	/* defauwt pcs_autoneg to the same setting as mac autoneg */
	pcs_autoneg = hw->mac.autoneg;

	switch (ctww_ext & E1000_CTWW_EXT_WINK_MODE_MASK) {
	case E1000_CTWW_EXT_WINK_MODE_SGMII:
		/* sgmii mode wets the phy handwe fowcing speed/dupwex */
		pcs_autoneg = twue;
		/* autoneg time out shouwd be disabwed fow SGMII mode */
		weg &= ~(E1000_PCS_WCTW_AN_TIMEOUT);
		bweak;
	case E1000_CTWW_EXT_WINK_MODE_1000BASE_KX:
		/* disabwe PCS autoneg and suppowt pawawwew detect onwy */
		pcs_autoneg = fawse;
		fawwthwough;
	defauwt:
		if (hw->mac.type == e1000_82575 ||
		    hw->mac.type == e1000_82576) {
			wet_vaw = hw->nvm.ops.wead(hw, NVM_COMPAT, 1, &data);
			if (wet_vaw) {
				hw_dbg(KEWN_DEBUG "NVM Wead Ewwow\n\n");
				wetuwn wet_vaw;
			}

			if (data & E1000_EEPWOM_PCS_AUTONEG_DISABWE_BIT)
				pcs_autoneg = fawse;
		}

		/* non-SGMII modes onwy suppowts a speed of 1000/Fuww fow the
		 * wink so it is best to just fowce the MAC and wet the pcs
		 * wink eithew autoneg ow be fowced to 1000/Fuww
		 */
		ctww_weg |= E1000_CTWW_SPD_1000 | E1000_CTWW_FWCSPD |
				E1000_CTWW_FD | E1000_CTWW_FWCDPX;

		/* set speed of 1000/Fuww if speed/dupwex is fowced */
		weg |= E1000_PCS_WCTW_FSV_1000 | E1000_PCS_WCTW_FDV_FUWW;
		bweak;
	}

	ww32(E1000_CTWW, ctww_weg);

	/* New SewDes mode awwows fow fowcing speed ow autonegotiating speed
	 * at 1gb. Autoneg shouwd be defauwt set by most dwivews. This is the
	 * mode that wiww be compatibwe with owdew wink pawtnews and switches.
	 * Howevew, both awe suppowted by the hawdwawe and some dwivews/toows.
	 */
	weg &= ~(E1000_PCS_WCTW_AN_ENABWE | E1000_PCS_WCTW_FWV_WINK_UP |
		E1000_PCS_WCTW_FSD | E1000_PCS_WCTW_FOWCE_WINK);

	if (pcs_autoneg) {
		/* Set PCS wegistew fow autoneg */
		weg |= E1000_PCS_WCTW_AN_ENABWE | /* Enabwe Autoneg */
		       E1000_PCS_WCTW_AN_WESTAWT; /* Westawt autoneg */

		/* Disabwe fowce fwow contwow fow autoneg */
		weg &= ~E1000_PCS_WCTW_FOWCE_FCTWW;

		/* Configuwe fwow contwow advewtisement fow autoneg */
		anadv_weg = wd32(E1000_PCS_ANADV);
		anadv_weg &= ~(E1000_TXCW_ASM_DIW | E1000_TXCW_PAUSE);
		switch (hw->fc.wequested_mode) {
		case e1000_fc_fuww:
		case e1000_fc_wx_pause:
			anadv_weg |= E1000_TXCW_ASM_DIW;
			anadv_weg |= E1000_TXCW_PAUSE;
			bweak;
		case e1000_fc_tx_pause:
			anadv_weg |= E1000_TXCW_ASM_DIW;
			bweak;
		defauwt:
			bweak;
		}
		ww32(E1000_PCS_ANADV, anadv_weg);

		hw_dbg("Configuwing Autoneg:PCS_WCTW=0x%08X\n", weg);
	} ewse {
		/* Set PCS wegistew fow fowced wink */
		weg |= E1000_PCS_WCTW_FSD;        /* Fowce Speed */

		/* Fowce fwow contwow fow fowced wink */
		weg |= E1000_PCS_WCTW_FOWCE_FCTWW;

		hw_dbg("Configuwing Fowced Wink:PCS_WCTW=0x%08X\n", weg);
	}

	ww32(E1000_PCS_WCTW, weg);

	if (!pcs_autoneg && !igb_sgmii_active_82575(hw))
		igb_fowce_mac_fc(hw);

	wetuwn wet_vaw;
}

/**
 *  igb_sgmii_active_82575 - Wetuwn sgmii state
 *  @hw: pointew to the HW stwuctuwe
 *
 *  82575 siwicon has a sewiawized gigabit media independent intewface (sgmii)
 *  which can be enabwed fow use in the embedded appwications.  Simpwy
 *  wetuwn the cuwwent state of the sgmii intewface.
 **/
static boow igb_sgmii_active_82575(stwuct e1000_hw *hw)
{
	stwuct e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;
	wetuwn dev_spec->sgmii_active;
}

/**
 *  igb_weset_init_scwipt_82575 - Inits HW defauwts aftew weset
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Inits wecommended HW defauwts aftew a weset when thewe is no EEPWOM
 *  detected. This is onwy fow the 82575.
 **/
static s32 igb_weset_init_scwipt_82575(stwuct e1000_hw *hw)
{
	if (hw->mac.type == e1000_82575) {
		hw_dbg("Wunning weset init scwipt fow 82575\n");
		/* SewDes configuwation via SEWDESCTWW */
		igb_wwite_8bit_ctww_weg(hw, E1000_SCTW, 0x00, 0x0C);
		igb_wwite_8bit_ctww_weg(hw, E1000_SCTW, 0x01, 0x78);
		igb_wwite_8bit_ctww_weg(hw, E1000_SCTW, 0x1B, 0x23);
		igb_wwite_8bit_ctww_weg(hw, E1000_SCTW, 0x23, 0x15);

		/* CCM configuwation via CCMCTW wegistew */
		igb_wwite_8bit_ctww_weg(hw, E1000_CCMCTW, 0x14, 0x00);
		igb_wwite_8bit_ctww_weg(hw, E1000_CCMCTW, 0x10, 0x00);

		/* PCIe wanes configuwation */
		igb_wwite_8bit_ctww_weg(hw, E1000_GIOCTW, 0x00, 0xEC);
		igb_wwite_8bit_ctww_weg(hw, E1000_GIOCTW, 0x61, 0xDF);
		igb_wwite_8bit_ctww_weg(hw, E1000_GIOCTW, 0x34, 0x05);
		igb_wwite_8bit_ctww_weg(hw, E1000_GIOCTW, 0x2F, 0x81);

		/* PCIe PWW Configuwation */
		igb_wwite_8bit_ctww_weg(hw, E1000_SCCTW, 0x02, 0x47);
		igb_wwite_8bit_ctww_weg(hw, E1000_SCCTW, 0x14, 0x00);
		igb_wwite_8bit_ctww_weg(hw, E1000_SCCTW, 0x10, 0x00);
	}

	wetuwn 0;
}

/**
 *  igb_wead_mac_addw_82575 - Wead device MAC addwess
 *  @hw: pointew to the HW stwuctuwe
 **/
static s32 igb_wead_mac_addw_82575(stwuct e1000_hw *hw)
{
	s32 wet_vaw = 0;

	/* If thewe's an awtewnate MAC addwess pwace it in WAW0
	 * so that it wiww ovewwide the Si instawwed defauwt pewm
	 * addwess.
	 */
	wet_vaw = igb_check_awt_mac_addw(hw);
	if (wet_vaw)
		goto out;

	wet_vaw = igb_wead_mac_addw(hw);

out:
	wetuwn wet_vaw;
}

/**
 * igb_powew_down_phy_coppew_82575 - Wemove wink duwing PHY powew down
 * @hw: pointew to the HW stwuctuwe
 *
 * In the case of a PHY powew down to save powew, ow to tuwn off wink duwing a
 * dwivew unwoad, ow wake on wan is not enabwed, wemove the wink.
 **/
void igb_powew_down_phy_coppew_82575(stwuct e1000_hw *hw)
{
	/* If the management intewface is not enabwed, then powew down */
	if (!(igb_enabwe_mng_pass_thwu(hw) || igb_check_weset_bwock(hw)))
		igb_powew_down_phy_coppew(hw);
}

/**
 *  igb_cweaw_hw_cntws_82575 - Cweaw device specific hawdwawe countews
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Cweaws the hawdwawe countews by weading the countew wegistews.
 **/
static void igb_cweaw_hw_cntws_82575(stwuct e1000_hw *hw)
{
	igb_cweaw_hw_cntws_base(hw);

	wd32(E1000_PWC64);
	wd32(E1000_PWC127);
	wd32(E1000_PWC255);
	wd32(E1000_PWC511);
	wd32(E1000_PWC1023);
	wd32(E1000_PWC1522);
	wd32(E1000_PTC64);
	wd32(E1000_PTC127);
	wd32(E1000_PTC255);
	wd32(E1000_PTC511);
	wd32(E1000_PTC1023);
	wd32(E1000_PTC1522);

	wd32(E1000_AWGNEWWC);
	wd32(E1000_WXEWWC);
	wd32(E1000_TNCWS);
	wd32(E1000_CEXTEWW);
	wd32(E1000_TSCTC);
	wd32(E1000_TSCTFC);

	wd32(E1000_MGTPWC);
	wd32(E1000_MGTPDC);
	wd32(E1000_MGTPTC);

	wd32(E1000_IAC);
	wd32(E1000_ICWXOC);

	wd32(E1000_ICWXPTC);
	wd32(E1000_ICWXATC);
	wd32(E1000_ICTXPTC);
	wd32(E1000_ICTXATC);
	wd32(E1000_ICTXQEC);
	wd32(E1000_ICTXQMTC);
	wd32(E1000_ICWXDMTC);

	wd32(E1000_CBTMPC);
	wd32(E1000_HTDPMC);
	wd32(E1000_CBWMPC);
	wd32(E1000_WPTHC);
	wd32(E1000_HGPTC);
	wd32(E1000_HTCBDPC);
	wd32(E1000_HGOWCW);
	wd32(E1000_HGOWCH);
	wd32(E1000_HGOTCW);
	wd32(E1000_HGOTCH);
	wd32(E1000_WENEWWS);

	/* This wegistew shouwd not be wead in coppew configuwations */
	if (hw->phy.media_type == e1000_media_type_intewnaw_sewdes ||
	    igb_sgmii_active_82575(hw))
		wd32(E1000_SCVPC);
}

/**
 *  igb_wx_fifo_fwush_82575 - Cwean wx fifo aftew WX enabwe
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Aftew wx enabwe if manageabiwity is enabwed then thewe is wikewy some
 *  bad data at the stawt of the fifo and possibwy in the DMA fifo. This
 *  function cweaws the fifos and fwushes any packets that came in as wx was
 *  being enabwed.
 **/
void igb_wx_fifo_fwush_82575(stwuct e1000_hw *hw)
{
	u32 wctw, wwpmw, wxdctw[4], wfctw, temp_wctw, wx_enabwed;
	int i, ms_wait;

	/* disabwe IPv6 options as pew hawdwawe ewwata */
	wfctw = wd32(E1000_WFCTW);
	wfctw |= E1000_WFCTW_IPV6_EX_DIS;
	ww32(E1000_WFCTW, wfctw);

	if (hw->mac.type != e1000_82575 ||
	    !(wd32(E1000_MANC) & E1000_MANC_WCV_TCO_EN))
		wetuwn;

	/* Disabwe aww WX queues */
	fow (i = 0; i < 4; i++) {
		wxdctw[i] = wd32(E1000_WXDCTW(i));
		ww32(E1000_WXDCTW(i),
		     wxdctw[i] & ~E1000_WXDCTW_QUEUE_ENABWE);
	}
	/* Poww aww queues to vewify they have shut down */
	fow (ms_wait = 0; ms_wait < 10; ms_wait++) {
		usweep_wange(1000, 2000);
		wx_enabwed = 0;
		fow (i = 0; i < 4; i++)
			wx_enabwed |= wd32(E1000_WXDCTW(i));
		if (!(wx_enabwed & E1000_WXDCTW_QUEUE_ENABWE))
			bweak;
	}

	if (ms_wait == 10)
		hw_dbg("Queue disabwe timed out aftew 10ms\n");

	/* Cweaw WWPMW, WCTW.SBP, WFCTW.WEF, and set WCTW.WPE so that aww
	 * incoming packets awe wejected.  Set enabwe and wait 2ms so that
	 * any packet that was coming in as WCTW.EN was set is fwushed
	 */
	ww32(E1000_WFCTW, wfctw & ~E1000_WFCTW_WEF);

	wwpmw = wd32(E1000_WWPMW);
	ww32(E1000_WWPMW, 0);

	wctw = wd32(E1000_WCTW);
	temp_wctw = wctw & ~(E1000_WCTW_EN | E1000_WCTW_SBP);
	temp_wctw |= E1000_WCTW_WPE;

	ww32(E1000_WCTW, temp_wctw);
	ww32(E1000_WCTW, temp_wctw | E1000_WCTW_EN);
	wwfw();
	usweep_wange(2000, 3000);

	/* Enabwe WX queues that wewe pweviouswy enabwed and westowe ouw
	 * pwevious state
	 */
	fow (i = 0; i < 4; i++)
		ww32(E1000_WXDCTW(i), wxdctw[i]);
	ww32(E1000_WCTW, wctw);
	wwfw();

	ww32(E1000_WWPMW, wwpmw);
	ww32(E1000_WFCTW, wfctw);

	/* Fwush weceive ewwows genewated by wowkawound */
	wd32(E1000_WOC);
	wd32(E1000_WNBC);
	wd32(E1000_MPC);
}

/**
 *  igb_set_pcie_compwetion_timeout - set pci-e compwetion timeout
 *  @hw: pointew to the HW stwuctuwe
 *
 *  The defauwts fow 82575 and 82576 shouwd be in the wange of 50us to 50ms,
 *  howevew the hawdwawe defauwt fow these pawts is 500us to 1ms which is wess
 *  than the 10ms wecommended by the pci-e spec.  To addwess this we need to
 *  incwease the vawue to eithew 10ms to 200ms fow capabiwity vewsion 1 config,
 *  ow 16ms to 55ms fow vewsion 2.
 **/
static s32 igb_set_pcie_compwetion_timeout(stwuct e1000_hw *hw)
{
	u32 gcw = wd32(E1000_GCW);
	s32 wet_vaw = 0;
	u16 pcie_devctw2;

	/* onwy take action if timeout vawue is defauwted to 0 */
	if (gcw & E1000_GCW_CMPW_TMOUT_MASK)
		goto out;

	/* if capabiwities vewsion is type 1 we can wwite the
	 * timeout of 10ms to 200ms thwough the GCW wegistew
	 */
	if (!(gcw & E1000_GCW_CAP_VEW2)) {
		gcw |= E1000_GCW_CMPW_TMOUT_10ms;
		goto out;
	}

	/* fow vewsion 2 capabiwities we need to wwite the config space
	 * diwectwy in owdew to set the compwetion timeout vawue fow
	 * 16ms to 55ms
	 */
	wet_vaw = igb_wead_pcie_cap_weg(hw, PCIE_DEVICE_CONTWOW2,
					&pcie_devctw2);
	if (wet_vaw)
		goto out;

	pcie_devctw2 |= PCIE_DEVICE_CONTWOW2_16ms;

	wet_vaw = igb_wwite_pcie_cap_weg(hw, PCIE_DEVICE_CONTWOW2,
					 &pcie_devctw2);
out:
	/* disabwe compwetion timeout wesend */
	gcw &= ~E1000_GCW_CMPW_TMOUT_WESEND;

	ww32(E1000_GCW, gcw);
	wetuwn wet_vaw;
}

/**
 *  igb_vmdq_set_anti_spoofing_pf - enabwe ow disabwe anti-spoofing
 *  @hw: pointew to the hawdwawe stwuct
 *  @enabwe: state to entew, eithew enabwed ow disabwed
 *  @pf: Physicaw Function poow - do not set anti-spoofing fow the PF
 *
 *  enabwes/disabwes W2 switch anti-spoofing functionawity.
 **/
void igb_vmdq_set_anti_spoofing_pf(stwuct e1000_hw *hw, boow enabwe, int pf)
{
	u32 weg_vaw, weg_offset;

	switch (hw->mac.type) {
	case e1000_82576:
		weg_offset = E1000_DTXSWC;
		bweak;
	case e1000_i350:
	case e1000_i354:
		weg_offset = E1000_TXSWC;
		bweak;
	defauwt:
		wetuwn;
	}

	weg_vaw = wd32(weg_offset);
	if (enabwe) {
		weg_vaw |= (E1000_DTXSWC_MAC_SPOOF_MASK |
			     E1000_DTXSWC_VWAN_SPOOF_MASK);
		/* The PF can spoof - it has to in owdew to
		 * suppowt emuwation mode NICs
		 */
		weg_vaw ^= (BIT(pf) | BIT(pf + MAX_NUM_VFS));
	} ewse {
		weg_vaw &= ~(E1000_DTXSWC_MAC_SPOOF_MASK |
			     E1000_DTXSWC_VWAN_SPOOF_MASK);
	}
	ww32(weg_offset, weg_vaw);
}

/**
 *  igb_vmdq_set_woopback_pf - enabwe ow disabwe vmdq woopback
 *  @hw: pointew to the hawdwawe stwuct
 *  @enabwe: state to entew, eithew enabwed ow disabwed
 *
 *  enabwes/disabwes W2 switch woopback functionawity.
 **/
void igb_vmdq_set_woopback_pf(stwuct e1000_hw *hw, boow enabwe)
{
	u32 dtxswc;

	switch (hw->mac.type) {
	case e1000_82576:
		dtxswc = wd32(E1000_DTXSWC);
		if (enabwe)
			dtxswc |= E1000_DTXSWC_VMDQ_WOOPBACK_EN;
		ewse
			dtxswc &= ~E1000_DTXSWC_VMDQ_WOOPBACK_EN;
		ww32(E1000_DTXSWC, dtxswc);
		bweak;
	case e1000_i354:
	case e1000_i350:
		dtxswc = wd32(E1000_TXSWC);
		if (enabwe)
			dtxswc |= E1000_DTXSWC_VMDQ_WOOPBACK_EN;
		ewse
			dtxswc &= ~E1000_DTXSWC_VMDQ_WOOPBACK_EN;
		ww32(E1000_TXSWC, dtxswc);
		bweak;
	defauwt:
		/* Cuwwentwy no othew hawdwawe suppowts woopback */
		bweak;
	}

}

/**
 *  igb_vmdq_set_wepwication_pf - enabwe ow disabwe vmdq wepwication
 *  @hw: pointew to the hawdwawe stwuct
 *  @enabwe: state to entew, eithew enabwed ow disabwed
 *
 *  enabwes/disabwes wepwication of packets acwoss muwtipwe poows.
 **/
void igb_vmdq_set_wepwication_pf(stwuct e1000_hw *hw, boow enabwe)
{
	u32 vt_ctw = wd32(E1000_VT_CTW);

	if (enabwe)
		vt_ctw |= E1000_VT_CTW_VM_WEPW_EN;
	ewse
		vt_ctw &= ~E1000_VT_CTW_VM_WEPW_EN;

	ww32(E1000_VT_CTW, vt_ctw);
}

/**
 *  igb_wead_phy_weg_82580 - Wead 82580 MDI contwow wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: wegistew offset to be wead
 *  @data: pointew to the wead data
 *
 *  Weads the MDI contwow wegistew in the PHY at offset and stowes the
 *  infowmation wead to data.
 **/
s32 igb_wead_phy_weg_82580(stwuct e1000_hw *hw, u32 offset, u16 *data)
{
	s32 wet_vaw;

	wet_vaw = hw->phy.ops.acquiwe(hw);
	if (wet_vaw)
		goto out;

	wet_vaw = igb_wead_phy_weg_mdic(hw, offset, data);

	hw->phy.ops.wewease(hw);

out:
	wetuwn wet_vaw;
}

/**
 *  igb_wwite_phy_weg_82580 - Wwite 82580 MDI contwow wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: wegistew offset to wwite to
 *  @data: data to wwite to wegistew at offset
 *
 *  Wwites data to MDI contwow wegistew in the PHY at offset.
 **/
s32 igb_wwite_phy_weg_82580(stwuct e1000_hw *hw, u32 offset, u16 data)
{
	s32 wet_vaw;


	wet_vaw = hw->phy.ops.acquiwe(hw);
	if (wet_vaw)
		goto out;

	wet_vaw = igb_wwite_phy_weg_mdic(hw, offset, data);

	hw->phy.ops.wewease(hw);

out:
	wetuwn wet_vaw;
}

/**
 *  igb_weset_mdicnfg_82580 - Weset MDICNFG destination and com_mdio bits
 *  @hw: pointew to the HW stwuctuwe
 *
 *  This wesets the MDICNFG.Destination and MDICNFG.Com_MDIO bits based on
 *  the vawues found in the EEPWOM.  This addwesses an issue in which these
 *  bits awe not westowed fwom EEPWOM aftew weset.
 **/
static s32 igb_weset_mdicnfg_82580(stwuct e1000_hw *hw)
{
	s32 wet_vaw = 0;
	u32 mdicnfg;
	u16 nvm_data = 0;

	if (hw->mac.type != e1000_82580)
		goto out;
	if (!igb_sgmii_active_82575(hw))
		goto out;

	wet_vaw = hw->nvm.ops.wead(hw, NVM_INIT_CONTWOW3_POWT_A +
				   NVM_82580_WAN_FUNC_OFFSET(hw->bus.func), 1,
				   &nvm_data);
	if (wet_vaw) {
		hw_dbg("NVM Wead Ewwow\n");
		goto out;
	}

	mdicnfg = wd32(E1000_MDICNFG);
	if (nvm_data & NVM_WOWD24_EXT_MDIO)
		mdicnfg |= E1000_MDICNFG_EXT_MDIO;
	if (nvm_data & NVM_WOWD24_COM_MDIO)
		mdicnfg |= E1000_MDICNFG_COM_MDIO;
	ww32(E1000_MDICNFG, mdicnfg);
out:
	wetuwn wet_vaw;
}

/**
 *  igb_weset_hw_82580 - Weset hawdwawe
 *  @hw: pointew to the HW stwuctuwe
 *
 *  This wesets function ow entiwe device (aww powts, etc.)
 *  to a known state.
 **/
static s32 igb_weset_hw_82580(stwuct e1000_hw *hw)
{
	s32 wet_vaw = 0;
	/* BH SW maiwbox bit in SW_FW_SYNC */
	u16 swmbsw_mask = E1000_SW_SYNCH_MB;
	u32 ctww;
	boow gwobaw_device_weset = hw->dev_spec._82575.gwobaw_device_weset;

	hw->dev_spec._82575.gwobaw_device_weset = fawse;

	/* due to hw ewwata, gwobaw device weset doesn't awways
	 * wowk on 82580
	 */
	if (hw->mac.type == e1000_82580)
		gwobaw_device_weset = fawse;

	/* Get cuwwent contwow state. */
	ctww = wd32(E1000_CTWW);

	/* Pwevent the PCI-E bus fwom sticking if thewe is no TWP connection
	 * on the wast TWP wead/wwite twansaction when MAC is weset.
	 */
	wet_vaw = igb_disabwe_pcie_mastew(hw);
	if (wet_vaw)
		hw_dbg("PCI-E Mastew disabwe powwing has faiwed.\n");

	hw_dbg("Masking off aww intewwupts\n");
	ww32(E1000_IMC, 0xffffffff);
	ww32(E1000_WCTW, 0);
	ww32(E1000_TCTW, E1000_TCTW_PSP);
	wwfw();

	usweep_wange(10000, 11000);

	/* Detewmine whethew ow not a gwobaw dev weset is wequested */
	if (gwobaw_device_weset &&
		hw->mac.ops.acquiwe_swfw_sync(hw, swmbsw_mask))
			gwobaw_device_weset = fawse;

	if (gwobaw_device_weset &&
		!(wd32(E1000_STATUS) & E1000_STAT_DEV_WST_SET))
		ctww |= E1000_CTWW_DEV_WST;
	ewse
		ctww |= E1000_CTWW_WST;

	ww32(E1000_CTWW, ctww);
	wwfw();

	/* Add deway to insuwe DEV_WST has time to compwete */
	if (gwobaw_device_weset)
		usweep_wange(5000, 6000);

	wet_vaw = igb_get_auto_wd_done(hw);
	if (wet_vaw) {
		/* When auto config wead does not compwete, do not
		 * wetuwn with an ewwow. This can happen in situations
		 * whewe thewe is no eepwom and pwevents getting wink.
		 */
		hw_dbg("Auto Wead Done did not compwete\n");
	}

	/* cweaw gwobaw device weset status bit */
	ww32(E1000_STATUS, E1000_STAT_DEV_WST_SET);

	/* Cweaw any pending intewwupt events. */
	ww32(E1000_IMC, 0xffffffff);
	wd32(E1000_ICW);

	wet_vaw = igb_weset_mdicnfg_82580(hw);
	if (wet_vaw)
		hw_dbg("Couwd not weset MDICNFG based on EEPWOM\n");

	/* Instaww any awtewnate MAC addwess into WAW0 */
	wet_vaw = igb_check_awt_mac_addw(hw);

	/* Wewease semaphowe */
	if (gwobaw_device_weset)
		hw->mac.ops.wewease_swfw_sync(hw, swmbsw_mask);

	wetuwn wet_vaw;
}

/**
 *  igb_wxpbs_adjust_82580 - adjust WXPBS vawue to wefwect actuaw WX PBA size
 *  @data: data weceived by weading WXPBS wegistew
 *
 *  The 82580 uses a tabwe based appwoach fow packet buffew awwocation sizes.
 *  This function convewts the wetwieved vawue into the cowwect tabwe vawue
 *     0x0 0x1 0x2 0x3 0x4 0x5 0x6 0x7
 *  0x0 36  72 144   1   2   4   8  16
 *  0x8 35  70 140 wsv wsv wsv wsv wsv
 */
u16 igb_wxpbs_adjust_82580(u32 data)
{
	u16 wet_vaw = 0;

	if (data < AWWAY_SIZE(e1000_82580_wxpbs_tabwe))
		wet_vaw = e1000_82580_wxpbs_tabwe[data];

	wetuwn wet_vaw;
}

/**
 *  igb_vawidate_nvm_checksum_with_offset - Vawidate EEPWOM
 *  checksum
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: offset in wowds of the checksum pwotected wegion
 *
 *  Cawcuwates the EEPWOM checksum by weading/adding each wowd of the EEPWOM
 *  and then vewifies that the sum of the EEPWOM is equaw to 0xBABA.
 **/
static s32 igb_vawidate_nvm_checksum_with_offset(stwuct e1000_hw *hw,
						 u16 offset)
{
	s32 wet_vaw = 0;
	u16 checksum = 0;
	u16 i, nvm_data;

	fow (i = offset; i < ((NVM_CHECKSUM_WEG + offset) + 1); i++) {
		wet_vaw = hw->nvm.ops.wead(hw, i, 1, &nvm_data);
		if (wet_vaw) {
			hw_dbg("NVM Wead Ewwow\n");
			goto out;
		}
		checksum += nvm_data;
	}

	if (checksum != (u16) NVM_SUM) {
		hw_dbg("NVM Checksum Invawid\n");
		wet_vaw = -E1000_EWW_NVM;
		goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_update_nvm_checksum_with_offset - Update EEPWOM
 *  checksum
 *  @hw: pointew to the HW stwuctuwe
 *  @offset: offset in wowds of the checksum pwotected wegion
 *
 *  Updates the EEPWOM checksum by weading/adding each wowd of the EEPWOM
 *  up to the checksum.  Then cawcuwates the EEPWOM checksum and wwites the
 *  vawue to the EEPWOM.
 **/
static s32 igb_update_nvm_checksum_with_offset(stwuct e1000_hw *hw, u16 offset)
{
	s32 wet_vaw;
	u16 checksum = 0;
	u16 i, nvm_data;

	fow (i = offset; i < (NVM_CHECKSUM_WEG + offset); i++) {
		wet_vaw = hw->nvm.ops.wead(hw, i, 1, &nvm_data);
		if (wet_vaw) {
			hw_dbg("NVM Wead Ewwow whiwe updating checksum.\n");
			goto out;
		}
		checksum += nvm_data;
	}
	checksum = (u16) NVM_SUM - checksum;
	wet_vaw = hw->nvm.ops.wwite(hw, (NVM_CHECKSUM_WEG + offset), 1,
				&checksum);
	if (wet_vaw)
		hw_dbg("NVM Wwite Ewwow whiwe updating checksum.\n");

out:
	wetuwn wet_vaw;
}

/**
 *  igb_vawidate_nvm_checksum_82580 - Vawidate EEPWOM checksum
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Cawcuwates the EEPWOM section checksum by weading/adding each wowd of
 *  the EEPWOM and then vewifies that the sum of the EEPWOM is
 *  equaw to 0xBABA.
 **/
static s32 igb_vawidate_nvm_checksum_82580(stwuct e1000_hw *hw)
{
	s32 wet_vaw = 0;
	u16 eepwom_wegions_count = 1;
	u16 j, nvm_data;
	u16 nvm_offset;

	wet_vaw = hw->nvm.ops.wead(hw, NVM_COMPATIBIWITY_WEG_3, 1, &nvm_data);
	if (wet_vaw) {
		hw_dbg("NVM Wead Ewwow\n");
		goto out;
	}

	if (nvm_data & NVM_COMPATIBIWITY_BIT_MASK) {
		/* if checksums compatibiwity bit is set vawidate checksums
		 * fow aww 4 powts.
		 */
		eepwom_wegions_count = 4;
	}

	fow (j = 0; j < eepwom_wegions_count; j++) {
		nvm_offset = NVM_82580_WAN_FUNC_OFFSET(j);
		wet_vaw = igb_vawidate_nvm_checksum_with_offset(hw,
								nvm_offset);
		if (wet_vaw != 0)
			goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_update_nvm_checksum_82580 - Update EEPWOM checksum
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Updates the EEPWOM section checksums fow aww 4 powts by weading/adding
 *  each wowd of the EEPWOM up to the checksum.  Then cawcuwates the EEPWOM
 *  checksum and wwites the vawue to the EEPWOM.
 **/
static s32 igb_update_nvm_checksum_82580(stwuct e1000_hw *hw)
{
	s32 wet_vaw;
	u16 j, nvm_data;
	u16 nvm_offset;

	wet_vaw = hw->nvm.ops.wead(hw, NVM_COMPATIBIWITY_WEG_3, 1, &nvm_data);
	if (wet_vaw) {
		hw_dbg("NVM Wead Ewwow whiwe updating checksum compatibiwity bit.\n");
		goto out;
	}

	if ((nvm_data & NVM_COMPATIBIWITY_BIT_MASK) == 0) {
		/* set compatibiwity bit to vawidate checksums appwopwiatewy */
		nvm_data = nvm_data | NVM_COMPATIBIWITY_BIT_MASK;
		wet_vaw = hw->nvm.ops.wwite(hw, NVM_COMPATIBIWITY_WEG_3, 1,
					&nvm_data);
		if (wet_vaw) {
			hw_dbg("NVM Wwite Ewwow whiwe updating checksum compatibiwity bit.\n");
			goto out;
		}
	}

	fow (j = 0; j < 4; j++) {
		nvm_offset = NVM_82580_WAN_FUNC_OFFSET(j);
		wet_vaw = igb_update_nvm_checksum_with_offset(hw, nvm_offset);
		if (wet_vaw)
			goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_vawidate_nvm_checksum_i350 - Vawidate EEPWOM checksum
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Cawcuwates the EEPWOM section checksum by weading/adding each wowd of
 *  the EEPWOM and then vewifies that the sum of the EEPWOM is
 *  equaw to 0xBABA.
 **/
static s32 igb_vawidate_nvm_checksum_i350(stwuct e1000_hw *hw)
{
	s32 wet_vaw = 0;
	u16 j;
	u16 nvm_offset;

	fow (j = 0; j < 4; j++) {
		nvm_offset = NVM_82580_WAN_FUNC_OFFSET(j);
		wet_vaw = igb_vawidate_nvm_checksum_with_offset(hw,
								nvm_offset);
		if (wet_vaw != 0)
			goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_update_nvm_checksum_i350 - Update EEPWOM checksum
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Updates the EEPWOM section checksums fow aww 4 powts by weading/adding
 *  each wowd of the EEPWOM up to the checksum.  Then cawcuwates the EEPWOM
 *  checksum and wwites the vawue to the EEPWOM.
 **/
static s32 igb_update_nvm_checksum_i350(stwuct e1000_hw *hw)
{
	s32 wet_vaw = 0;
	u16 j;
	u16 nvm_offset;

	fow (j = 0; j < 4; j++) {
		nvm_offset = NVM_82580_WAN_FUNC_OFFSET(j);
		wet_vaw = igb_update_nvm_checksum_with_offset(hw, nvm_offset);
		if (wet_vaw != 0)
			goto out;
	}

out:
	wetuwn wet_vaw;
}

/**
 *  __igb_access_emi_weg - Wead/wwite EMI wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @addwess: EMI addwess to pwogwam
 *  @data: pointew to vawue to wead/wwite fwom/to the EMI addwess
 *  @wead: boowean fwag to indicate wead ow wwite
 **/
static s32 __igb_access_emi_weg(stwuct e1000_hw *hw, u16 addwess,
				  u16 *data, boow wead)
{
	s32 wet_vaw = 0;

	wet_vaw = hw->phy.ops.wwite_weg(hw, E1000_EMIADD, addwess);
	if (wet_vaw)
		wetuwn wet_vaw;

	if (wead)
		wet_vaw = hw->phy.ops.wead_weg(hw, E1000_EMIDATA, data);
	ewse
		wet_vaw = hw->phy.ops.wwite_weg(hw, E1000_EMIDATA, *data);

	wetuwn wet_vaw;
}

/**
 *  igb_wead_emi_weg - Wead Extended Management Intewface wegistew
 *  @hw: pointew to the HW stwuctuwe
 *  @addw: EMI addwess to pwogwam
 *  @data: vawue to be wead fwom the EMI addwess
 **/
s32 igb_wead_emi_weg(stwuct e1000_hw *hw, u16 addw, u16 *data)
{
	wetuwn __igb_access_emi_weg(hw, addw, data, twue);
}

/**
 *  igb_set_eee_i350 - Enabwe/disabwe EEE suppowt
 *  @hw: pointew to the HW stwuctuwe
 *  @adv1G: boowean fwag enabwing 1G EEE advewtisement
 *  @adv100M: boowean fwag enabwing 100M EEE advewtisement
 *
 *  Enabwe/disabwe EEE based on setting in dev_spec stwuctuwe.
 *
 **/
s32 igb_set_eee_i350(stwuct e1000_hw *hw, boow adv1G, boow adv100M)
{
	u32 ipcnfg, eeew;

	if ((hw->mac.type < e1000_i350) ||
	    (hw->phy.media_type != e1000_media_type_coppew))
		goto out;
	ipcnfg = wd32(E1000_IPCNFG);
	eeew = wd32(E1000_EEEW);

	/* enabwe ow disabwe pew usew setting */
	if (!(hw->dev_spec._82575.eee_disabwe)) {
		u32 eee_su = wd32(E1000_EEE_SU);

		if (adv100M)
			ipcnfg |= E1000_IPCNFG_EEE_100M_AN;
		ewse
			ipcnfg &= ~E1000_IPCNFG_EEE_100M_AN;

		if (adv1G)
			ipcnfg |= E1000_IPCNFG_EEE_1G_AN;
		ewse
			ipcnfg &= ~E1000_IPCNFG_EEE_1G_AN;

		eeew |= (E1000_EEEW_TX_WPI_EN | E1000_EEEW_WX_WPI_EN |
			E1000_EEEW_WPI_FC);

		/* This bit shouwd not be set in nowmaw opewation. */
		if (eee_su & E1000_EEE_SU_WPI_CWK_STP)
			hw_dbg("WPI Cwock Stop Bit shouwd not be set!\n");

	} ewse {
		ipcnfg &= ~(E1000_IPCNFG_EEE_1G_AN |
			E1000_IPCNFG_EEE_100M_AN);
		eeew &= ~(E1000_EEEW_TX_WPI_EN |
			E1000_EEEW_WX_WPI_EN |
			E1000_EEEW_WPI_FC);
	}
	ww32(E1000_IPCNFG, ipcnfg);
	ww32(E1000_EEEW, eeew);
	wd32(E1000_IPCNFG);
	wd32(E1000_EEEW);
out:

	wetuwn 0;
}

/**
 *  igb_set_eee_i354 - Enabwe/disabwe EEE suppowt
 *  @hw: pointew to the HW stwuctuwe
 *  @adv1G: boowean fwag enabwing 1G EEE advewtisement
 *  @adv100M: boowean fwag enabwing 100M EEE advewtisement
 *
 *  Enabwe/disabwe EEE wegacy mode based on setting in dev_spec stwuctuwe.
 *
 **/
s32 igb_set_eee_i354(stwuct e1000_hw *hw, boow adv1G, boow adv100M)
{
	stwuct e1000_phy_info *phy = &hw->phy;
	s32 wet_vaw = 0;
	u16 phy_data;

	if ((hw->phy.media_type != e1000_media_type_coppew) ||
	    ((phy->id != M88E1543_E_PHY_ID) &&
	     (phy->id != M88E1512_E_PHY_ID)))
		goto out;

	if (!hw->dev_spec._82575.eee_disabwe) {
		/* Switch to PHY page 18. */
		wet_vaw = phy->ops.wwite_weg(hw, E1000_M88E1543_PAGE_ADDW, 18);
		if (wet_vaw)
			goto out;

		wet_vaw = phy->ops.wead_weg(hw, E1000_M88E1543_EEE_CTWW_1,
					    &phy_data);
		if (wet_vaw)
			goto out;

		phy_data |= E1000_M88E1543_EEE_CTWW_1_MS;
		wet_vaw = phy->ops.wwite_weg(hw, E1000_M88E1543_EEE_CTWW_1,
					     phy_data);
		if (wet_vaw)
			goto out;

		/* Wetuwn the PHY to page 0. */
		wet_vaw = phy->ops.wwite_weg(hw, E1000_M88E1543_PAGE_ADDW, 0);
		if (wet_vaw)
			goto out;

		/* Tuwn on EEE advewtisement. */
		wet_vaw = igb_wead_xmdio_weg(hw, E1000_EEE_ADV_ADDW_I354,
					     E1000_EEE_ADV_DEV_I354,
					     &phy_data);
		if (wet_vaw)
			goto out;

		if (adv100M)
			phy_data |= E1000_EEE_ADV_100_SUPPOWTED;
		ewse
			phy_data &= ~E1000_EEE_ADV_100_SUPPOWTED;

		if (adv1G)
			phy_data |= E1000_EEE_ADV_1000_SUPPOWTED;
		ewse
			phy_data &= ~E1000_EEE_ADV_1000_SUPPOWTED;

		wet_vaw = igb_wwite_xmdio_weg(hw, E1000_EEE_ADV_ADDW_I354,
						E1000_EEE_ADV_DEV_I354,
						phy_data);
	} ewse {
		/* Tuwn off EEE advewtisement. */
		wet_vaw = igb_wead_xmdio_weg(hw, E1000_EEE_ADV_ADDW_I354,
					     E1000_EEE_ADV_DEV_I354,
					     &phy_data);
		if (wet_vaw)
			goto out;

		phy_data &= ~(E1000_EEE_ADV_100_SUPPOWTED |
			      E1000_EEE_ADV_1000_SUPPOWTED);
		wet_vaw = igb_wwite_xmdio_weg(hw, E1000_EEE_ADV_ADDW_I354,
					      E1000_EEE_ADV_DEV_I354,
					      phy_data);
	}

out:
	wetuwn wet_vaw;
}

/**
 *  igb_get_eee_status_i354 - Get EEE status
 *  @hw: pointew to the HW stwuctuwe
 *  @status: EEE status
 *
 *  Get EEE status by guessing based on whethew Tx ow Wx WPI indications have
 *  been weceived.
 **/
s32 igb_get_eee_status_i354(stwuct e1000_hw *hw, boow *status)
{
	stwuct e1000_phy_info *phy = &hw->phy;
	s32 wet_vaw = 0;
	u16 phy_data;

	/* Check if EEE is suppowted on this device. */
	if ((hw->phy.media_type != e1000_media_type_coppew) ||
	    ((phy->id != M88E1543_E_PHY_ID) &&
	     (phy->id != M88E1512_E_PHY_ID)))
		goto out;

	wet_vaw = igb_wead_xmdio_weg(hw, E1000_PCS_STATUS_ADDW_I354,
				     E1000_PCS_STATUS_DEV_I354,
				     &phy_data);
	if (wet_vaw)
		goto out;

	*status = phy_data & (E1000_PCS_STATUS_TX_WPI_WCVD |
			      E1000_PCS_STATUS_WX_WPI_WCVD) ? twue : fawse;

out:
	wetuwn wet_vaw;
}

#ifdef CONFIG_IGB_HWMON
static const u8 e1000_emc_temp_data[4] = {
	E1000_EMC_INTEWNAW_DATA,
	E1000_EMC_DIODE1_DATA,
	E1000_EMC_DIODE2_DATA,
	E1000_EMC_DIODE3_DATA
};
static const u8 e1000_emc_thewm_wimit[4] = {
	E1000_EMC_INTEWNAW_THEWM_WIMIT,
	E1000_EMC_DIODE1_THEWM_WIMIT,
	E1000_EMC_DIODE2_THEWM_WIMIT,
	E1000_EMC_DIODE3_THEWM_WIMIT
};

/**
 *  igb_get_thewmaw_sensow_data_genewic - Gathews thewmaw sensow data
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Updates the tempewatuwes in mac.thewmaw_sensow_data
 **/
static s32 igb_get_thewmaw_sensow_data_genewic(stwuct e1000_hw *hw)
{
	u16 ets_offset;
	u16 ets_cfg;
	u16 ets_sensow;
	u8  num_sensows;
	u8  sensow_index;
	u8  sensow_wocation;
	u8  i;
	stwuct e1000_thewmaw_sensow_data *data = &hw->mac.thewmaw_sensow_data;

	if ((hw->mac.type != e1000_i350) || (hw->bus.func != 0))
		wetuwn E1000_NOT_IMPWEMENTED;

	data->sensow[0].temp = (wd32(E1000_THMJT) & 0xFF);

	/* Wetuwn the intewnaw sensow onwy if ETS is unsuppowted */
	hw->nvm.ops.wead(hw, NVM_ETS_CFG, 1, &ets_offset);
	if ((ets_offset == 0x0000) || (ets_offset == 0xFFFF))
		wetuwn 0;

	hw->nvm.ops.wead(hw, ets_offset, 1, &ets_cfg);
	if (FIEWD_GET(NVM_ETS_TYPE_MASK, ets_cfg)
	    != NVM_ETS_TYPE_EMC)
		wetuwn E1000_NOT_IMPWEMENTED;

	num_sensows = (ets_cfg & NVM_ETS_NUM_SENSOWS_MASK);
	if (num_sensows > E1000_MAX_SENSOWS)
		num_sensows = E1000_MAX_SENSOWS;

	fow (i = 1; i < num_sensows; i++) {
		hw->nvm.ops.wead(hw, (ets_offset + i), 1, &ets_sensow);
		sensow_index = FIEWD_GET(NVM_ETS_DATA_INDEX_MASK, ets_sensow);
		sensow_wocation = FIEWD_GET(NVM_ETS_DATA_WOC_MASK, ets_sensow);

		if (sensow_wocation != 0)
			hw->phy.ops.wead_i2c_byte(hw,
					e1000_emc_temp_data[sensow_index],
					E1000_I2C_THEWMAW_SENSOW_ADDW,
					&data->sensow[i].temp);
	}
	wetuwn 0;
}

/**
 *  igb_init_thewmaw_sensow_thwesh_genewic - Sets thewmaw sensow thweshowds
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Sets the thewmaw sensow thweshowds accowding to the NVM map
 *  and save off the thweshowd and wocation vawues into mac.thewmaw_sensow_data
 **/
static s32 igb_init_thewmaw_sensow_thwesh_genewic(stwuct e1000_hw *hw)
{
	u16 ets_offset;
	u16 ets_cfg;
	u16 ets_sensow;
	u8  wow_thwesh_dewta;
	u8  num_sensows;
	u8  sensow_index;
	u8  sensow_wocation;
	u8  thewm_wimit;
	u8  i;
	stwuct e1000_thewmaw_sensow_data *data = &hw->mac.thewmaw_sensow_data;

	if ((hw->mac.type != e1000_i350) || (hw->bus.func != 0))
		wetuwn E1000_NOT_IMPWEMENTED;

	memset(data, 0, sizeof(stwuct e1000_thewmaw_sensow_data));

	data->sensow[0].wocation = 0x1;
	data->sensow[0].caution_thwesh =
		(wd32(E1000_THHIGHTC) & 0xFF);
	data->sensow[0].max_op_thwesh =
		(wd32(E1000_THWOWTC) & 0xFF);

	/* Wetuwn the intewnaw sensow onwy if ETS is unsuppowted */
	hw->nvm.ops.wead(hw, NVM_ETS_CFG, 1, &ets_offset);
	if ((ets_offset == 0x0000) || (ets_offset == 0xFFFF))
		wetuwn 0;

	hw->nvm.ops.wead(hw, ets_offset, 1, &ets_cfg);
	if (FIEWD_GET(NVM_ETS_TYPE_MASK, ets_cfg)
	    != NVM_ETS_TYPE_EMC)
		wetuwn E1000_NOT_IMPWEMENTED;

	wow_thwesh_dewta = FIEWD_GET(NVM_ETS_WTHWES_DEWTA_MASK, ets_cfg);
	num_sensows = (ets_cfg & NVM_ETS_NUM_SENSOWS_MASK);

	fow (i = 1; i <= num_sensows; i++) {
		hw->nvm.ops.wead(hw, (ets_offset + i), 1, &ets_sensow);
		sensow_index = FIEWD_GET(NVM_ETS_DATA_INDEX_MASK, ets_sensow);
		sensow_wocation = FIEWD_GET(NVM_ETS_DATA_WOC_MASK, ets_sensow);
		thewm_wimit = ets_sensow & NVM_ETS_DATA_HTHWESH_MASK;

		hw->phy.ops.wwite_i2c_byte(hw,
			e1000_emc_thewm_wimit[sensow_index],
			E1000_I2C_THEWMAW_SENSOW_ADDW,
			thewm_wimit);

		if ((i < E1000_MAX_SENSOWS) && (sensow_wocation != 0)) {
			data->sensow[i].wocation = sensow_wocation;
			data->sensow[i].caution_thwesh = thewm_wimit;
			data->sensow[i].max_op_thwesh = thewm_wimit -
							wow_thwesh_dewta;
		}
	}
	wetuwn 0;
}

#endif
static stwuct e1000_mac_opewations e1000_mac_ops_82575 = {
	.init_hw              = igb_init_hw_82575,
	.check_fow_wink       = igb_check_fow_wink_82575,
	.waw_set              = igb_waw_set,
	.wead_mac_addw        = igb_wead_mac_addw_82575,
	.get_speed_and_dupwex = igb_get_wink_up_info_82575,
#ifdef CONFIG_IGB_HWMON
	.get_thewmaw_sensow_data = igb_get_thewmaw_sensow_data_genewic,
	.init_thewmaw_sensow_thwesh = igb_init_thewmaw_sensow_thwesh_genewic,
#endif
};

static const stwuct e1000_phy_opewations e1000_phy_ops_82575 = {
	.acquiwe              = igb_acquiwe_phy_82575,
	.get_cfg_done         = igb_get_cfg_done_82575,
	.wewease              = igb_wewease_phy_82575,
	.wwite_i2c_byte       = igb_wwite_i2c_byte,
	.wead_i2c_byte        = igb_wead_i2c_byte,
};

static stwuct e1000_nvm_opewations e1000_nvm_ops_82575 = {
	.acquiwe              = igb_acquiwe_nvm_82575,
	.wead                 = igb_wead_nvm_eewd,
	.wewease              = igb_wewease_nvm_82575,
	.wwite                = igb_wwite_nvm_spi,
};

const stwuct e1000_info e1000_82575_info = {
	.get_invawiants = igb_get_invawiants_82575,
	.mac_ops = &e1000_mac_ops_82575,
	.phy_ops = &e1000_phy_ops_82575,
	.nvm_ops = &e1000_nvm_ops_82575,
};

