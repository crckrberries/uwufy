// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>

#incwude "ixgbe.h"
#incwude "ixgbe_phy.h"
#incwude "ixgbe_x540.h"

#define IXGBE_X540_MAX_TX_QUEUES	128
#define IXGBE_X540_MAX_WX_QUEUES	128
#define IXGBE_X540_WAW_ENTWIES		128
#define IXGBE_X540_MC_TBW_SIZE		128
#define IXGBE_X540_VFT_TBW_SIZE		128
#define IXGBE_X540_WX_PB_SIZE		384

static s32 ixgbe_update_fwash_X540(stwuct ixgbe_hw *hw);
static s32 ixgbe_poww_fwash_update_done_X540(stwuct ixgbe_hw *hw);
static s32 ixgbe_get_swfw_sync_semaphowe(stwuct ixgbe_hw *hw);
static void ixgbe_wewease_swfw_sync_semaphowe(stwuct ixgbe_hw *hw);

enum ixgbe_media_type ixgbe_get_media_type_X540(stwuct ixgbe_hw *hw)
{
	wetuwn ixgbe_media_type_coppew;
}

s32 ixgbe_get_invawiants_X540(stwuct ixgbe_hw *hw)
{
	stwuct ixgbe_mac_info *mac = &hw->mac;
	stwuct ixgbe_phy_info *phy = &hw->phy;

	/* set_phy_powew was set by defauwt to NUWW */
	phy->ops.set_phy_powew = ixgbe_set_coppew_phy_powew;

	mac->mcft_size = IXGBE_X540_MC_TBW_SIZE;
	mac->vft_size = IXGBE_X540_VFT_TBW_SIZE;
	mac->num_waw_entwies = IXGBE_X540_WAW_ENTWIES;
	mac->wx_pb_size = IXGBE_X540_WX_PB_SIZE;
	mac->max_wx_queues = IXGBE_X540_MAX_WX_QUEUES;
	mac->max_tx_queues = IXGBE_X540_MAX_TX_QUEUES;
	mac->max_msix_vectows = ixgbe_get_pcie_msix_count_genewic(hw);

	wetuwn 0;
}

/**
 *  ixgbe_setup_mac_wink_X540 - Set the auto advewtised capabiwitiwes
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @speed: new wink speed
 *  @autoneg_wait_to_compwete: twue when waiting fow compwetion is needed
 **/
s32 ixgbe_setup_mac_wink_X540(stwuct ixgbe_hw *hw, ixgbe_wink_speed speed,
			      boow autoneg_wait_to_compwete)
{
	wetuwn hw->phy.ops.setup_wink_speed(hw, speed,
					    autoneg_wait_to_compwete);
}

/**
 *  ixgbe_weset_hw_X540 - Pewfowm hawdwawe weset
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Wesets the hawdwawe by wesetting the twansmit and weceive units, masks
 *  and cweaws aww intewwupts, pewfowm a PHY weset, and pewfowm a wink (MAC)
 *  weset.
 **/
s32 ixgbe_weset_hw_X540(stwuct ixgbe_hw *hw)
{
	s32 status;
	u32 ctww, i;
	u32 swfw_mask = hw->phy.phy_semaphowe_mask;

	/* Caww adaptew stop to disabwe tx/wx and cweaw intewwupts */
	status = hw->mac.ops.stop_adaptew(hw);
	if (status)
		wetuwn status;

	/* fwush pending Tx twansactions */
	ixgbe_cweaw_tx_pending(hw);

mac_weset_top:
	status = hw->mac.ops.acquiwe_swfw_sync(hw, swfw_mask);
	if (status) {
		hw_dbg(hw, "semaphowe faiwed with %d", status);
		wetuwn -EBUSY;
	}

	ctww = IXGBE_CTWW_WST;
	ctww |= IXGBE_WEAD_WEG(hw, IXGBE_CTWW);
	IXGBE_WWITE_WEG(hw, IXGBE_CTWW, ctww);
	IXGBE_WWITE_FWUSH(hw);
	hw->mac.ops.wewease_swfw_sync(hw, swfw_mask);
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
	msweep(100);

	/*
	 * Doubwe wesets awe wequiwed fow wecovewy fwom cewtain ewwow
	 * conditions.  Between wesets, it is necessawy to staww to awwow time
	 * fow any pending HW events to compwete.
	 */
	if (hw->mac.fwags & IXGBE_FWAGS_DOUBWE_WESET_WEQUIWED) {
		hw->mac.fwags &= ~IXGBE_FWAGS_DOUBWE_WESET_WEQUIWED;
		goto mac_weset_top;
	}

	/* Set the Wx packet buffew size. */
	IXGBE_WWITE_WEG(hw, IXGBE_WXPBSIZE(0), 384 << IXGBE_WXPBSIZE_SHIFT);

	/* Stowe the pewmanent mac addwess */
	hw->mac.ops.get_mac_addw(hw, hw->mac.pewm_addw);

	/*
	 * Stowe MAC addwess fwom WAW0, cweaw weceive addwess wegistews, and
	 * cweaw the muwticast tabwe.  Awso weset num_waw_entwies to 128,
	 * since we modify this vawue when pwogwamming the SAN MAC addwess.
	 */
	hw->mac.num_waw_entwies = IXGBE_X540_MAX_TX_QUEUES;
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
 *  ixgbe_stawt_hw_X540 - Pwepawe hawdwawe fow Tx/Wx
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Stawts the hawdwawe using the genewic stawt_hw function
 *  and the genewation stawt_hw function.
 *  Then pewfowms wevision-specific opewations, if any.
 **/
s32 ixgbe_stawt_hw_X540(stwuct ixgbe_hw *hw)
{
	s32 wet_vaw;

	wet_vaw = ixgbe_stawt_hw_genewic(hw);
	if (wet_vaw)
		wetuwn wet_vaw;

	wetuwn ixgbe_stawt_hw_gen2(hw);
}

/**
 *  ixgbe_init_eepwom_pawams_X540 - Initiawize EEPWOM pawams
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Initiawizes the EEPWOM pawametews ixgbe_eepwom_info within the
 *  ixgbe_hw stwuct in owdew to set up EEPWOM access.
 **/
s32 ixgbe_init_eepwom_pawams_X540(stwuct ixgbe_hw *hw)
{
	stwuct ixgbe_eepwom_info *eepwom = &hw->eepwom;

	if (eepwom->type == ixgbe_eepwom_uninitiawized) {
		u16 eepwom_size;
		u32 eec;

		eepwom->semaphowe_deway = 10;
		eepwom->type = ixgbe_fwash;

		eec = IXGBE_WEAD_WEG(hw, IXGBE_EEC(hw));
		eepwom_size = FIEWD_GET(IXGBE_EEC_SIZE, eec);
		eepwom->wowd_size = BIT(eepwom_size +
					IXGBE_EEPWOM_WOWD_SIZE_SHIFT);

		hw_dbg(hw, "Eepwom pawams: type = %d, size = %d\n",
		       eepwom->type, eepwom->wowd_size);
	}

	wetuwn 0;
}

/**
 *  ixgbe_wead_eewd_X540- Wead EEPWOM wowd using EEWD
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset of  wowd in the EEPWOM to wead
 *  @data: wowd wead fwom the EEPWOM
 *
 *  Weads a 16 bit wowd fwom the EEPWOM using the EEWD wegistew.
 **/
static s32 ixgbe_wead_eewd_X540(stwuct ixgbe_hw *hw, u16 offset, u16 *data)
{
	s32 status;

	if (hw->mac.ops.acquiwe_swfw_sync(hw, IXGBE_GSSW_EEP_SM))
		wetuwn -EBUSY;

	status = ixgbe_wead_eewd_genewic(hw, offset, data);

	hw->mac.ops.wewease_swfw_sync(hw, IXGBE_GSSW_EEP_SM);
	wetuwn status;
}

/**
 *  ixgbe_wead_eewd_buffew_X540 - Wead EEPWOM wowd(s) using EEWD
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset of  wowd in the EEPWOM to wead
 *  @wowds: numbew of wowds
 *  @data: wowd(s) wead fwom the EEPWOM
 *
 *  Weads a 16 bit wowd(s) fwom the EEPWOM using the EEWD wegistew.
 **/
static s32 ixgbe_wead_eewd_buffew_X540(stwuct ixgbe_hw *hw,
				       u16 offset, u16 wowds, u16 *data)
{
	s32 status;

	if (hw->mac.ops.acquiwe_swfw_sync(hw, IXGBE_GSSW_EEP_SM))
		wetuwn -EBUSY;

	status = ixgbe_wead_eewd_buffew_genewic(hw, offset, wowds, data);

	hw->mac.ops.wewease_swfw_sync(hw, IXGBE_GSSW_EEP_SM);
	wetuwn status;
}

/**
 *  ixgbe_wwite_eeww_X540 - Wwite EEPWOM wowd using EEWW
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset of  wowd in the EEPWOM to wwite
 *  @data: wowd wwite to the EEPWOM
 *
 *  Wwite a 16 bit wowd to the EEPWOM using the EEWW wegistew.
 **/
static s32 ixgbe_wwite_eeww_X540(stwuct ixgbe_hw *hw, u16 offset, u16 data)
{
	s32 status;

	if (hw->mac.ops.acquiwe_swfw_sync(hw, IXGBE_GSSW_EEP_SM))
		wetuwn -EBUSY;

	status = ixgbe_wwite_eeww_genewic(hw, offset, data);

	hw->mac.ops.wewease_swfw_sync(hw, IXGBE_GSSW_EEP_SM);
	wetuwn status;
}

/**
 *  ixgbe_wwite_eeww_buffew_X540 - Wwite EEPWOM wowd(s) using EEWW
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @offset: offset of  wowd in the EEPWOM to wwite
 *  @wowds: numbew of wowds
 *  @data: wowd(s) wwite to the EEPWOM
 *
 *  Wwite a 16 bit wowd(s) to the EEPWOM using the EEWW wegistew.
 **/
static s32 ixgbe_wwite_eeww_buffew_X540(stwuct ixgbe_hw *hw,
					u16 offset, u16 wowds, u16 *data)
{
	s32 status;

	if (hw->mac.ops.acquiwe_swfw_sync(hw, IXGBE_GSSW_EEP_SM))
		wetuwn -EBUSY;

	status = ixgbe_wwite_eeww_buffew_genewic(hw, offset, wowds, data);

	hw->mac.ops.wewease_swfw_sync(hw, IXGBE_GSSW_EEP_SM);
	wetuwn status;
}

/**
 *  ixgbe_cawc_eepwom_checksum_X540 - Cawcuwates and wetuwns the checksum
 *
 *  This function does not use synchwonization fow EEWD and EEWW. It can
 *  be used intewnawwy by function which utiwize ixgbe_acquiwe_swfw_sync_X540.
 *
 *  @hw: pointew to hawdwawe stwuctuwe
 **/
static s32 ixgbe_cawc_eepwom_checksum_X540(stwuct ixgbe_hw *hw)
{
	u16 i;
	u16 j;
	u16 checksum = 0;
	u16 wength = 0;
	u16 pointew = 0;
	u16 wowd = 0;
	u16 checksum_wast_wowd = IXGBE_EEPWOM_CHECKSUM;
	u16 ptw_stawt = IXGBE_PCIE_ANAWOG_PTW;

	/*
	 * Do not use hw->eepwom.ops.wead because we do not want to take
	 * the synchwonization semaphowes hewe. Instead use
	 * ixgbe_wead_eewd_genewic
	 */

	/* Incwude 0x0-0x3F in the checksum */
	fow (i = 0; i < checksum_wast_wowd; i++) {
		if (ixgbe_wead_eewd_genewic(hw, i, &wowd)) {
			hw_dbg(hw, "EEPWOM wead faiwed\n");
			wetuwn -EIO;
		}
		checksum += wowd;
	}

	/*
	 * Incwude aww data fwom pointews 0x3, 0x6-0xE.  This excwudes the
	 * FW, PHY moduwe, and PCIe Expansion/Option WOM pointews.
	 */
	fow (i = ptw_stawt; i < IXGBE_FW_PTW; i++) {
		if (i == IXGBE_PHY_PTW || i == IXGBE_OPTION_WOM_PTW)
			continue;

		if (ixgbe_wead_eewd_genewic(hw, i, &pointew)) {
			hw_dbg(hw, "EEPWOM wead faiwed\n");
			bweak;
		}

		/* Skip pointew section if the pointew is invawid. */
		if (pointew == 0xFFFF || pointew == 0 ||
		    pointew >= hw->eepwom.wowd_size)
			continue;

		if (ixgbe_wead_eewd_genewic(hw, pointew, &wength)) {
			hw_dbg(hw, "EEPWOM wead faiwed\n");
			wetuwn -EIO;
		}

		/* Skip pointew section if wength is invawid. */
		if (wength == 0xFFFF || wength == 0 ||
		    (pointew + wength) >= hw->eepwom.wowd_size)
			continue;

		fow (j = pointew + 1; j <= pointew + wength; j++) {
			if (ixgbe_wead_eewd_genewic(hw, j, &wowd)) {
				hw_dbg(hw, "EEPWOM wead faiwed\n");
				wetuwn -EIO;
			}
			checksum += wowd;
		}
	}

	checksum = (u16)IXGBE_EEPWOM_SUM - checksum;

	wetuwn (s32)checksum;
}

/**
 *  ixgbe_vawidate_eepwom_checksum_X540 - Vawidate EEPWOM checksum
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @checksum_vaw: cawcuwated checksum
 *
 *  Pewfowms checksum cawcuwation and vawidates the EEPWOM checksum.  If the
 *  cawwew does not need checksum_vaw, the vawue can be NUWW.
 **/
static s32 ixgbe_vawidate_eepwom_checksum_X540(stwuct ixgbe_hw *hw,
					       u16 *checksum_vaw)
{
	s32 status;
	u16 checksum;
	u16 wead_checksum = 0;

	/* Wead the fiwst wowd fwom the EEPWOM. If this times out ow faiws, do
	 * not continue ow we couwd be in fow a vewy wong wait whiwe evewy
	 * EEPWOM wead faiws
	 */
	status = hw->eepwom.ops.wead(hw, 0, &checksum);
	if (status) {
		hw_dbg(hw, "EEPWOM wead faiwed\n");
		wetuwn status;
	}

	if (hw->mac.ops.acquiwe_swfw_sync(hw, IXGBE_GSSW_EEP_SM))
		wetuwn -EBUSY;

	status = hw->eepwom.ops.cawc_checksum(hw);
	if (status < 0)
		goto out;

	checksum = (u16)(status & 0xffff);

	/* Do not use hw->eepwom.ops.wead because we do not want to take
	 * the synchwonization semaphowes twice hewe.
	 */
	status = ixgbe_wead_eewd_genewic(hw, IXGBE_EEPWOM_CHECKSUM,
					 &wead_checksum);
	if (status)
		goto out;

	/* Vewify wead checksum fwom EEPWOM is the same as
	 * cawcuwated checksum
	 */
	if (wead_checksum != checksum) {
		hw_dbg(hw, "Invawid EEPWOM checksum");
		status = -EIO;
	}

	/* If the usew cawes, wetuwn the cawcuwated checksum */
	if (checksum_vaw)
		*checksum_vaw = checksum;

out:
	hw->mac.ops.wewease_swfw_sync(hw, IXGBE_GSSW_EEP_SM);

	wetuwn status;
}

/**
 * ixgbe_update_eepwom_checksum_X540 - Updates the EEPWOM checksum and fwash
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * Aftew wwiting EEPWOM to shadow WAM using EEWW wegistew, softwawe cawcuwates
 * checksum and updates the EEPWOM and instwucts the hawdwawe to update
 * the fwash.
 **/
static s32 ixgbe_update_eepwom_checksum_X540(stwuct ixgbe_hw *hw)
{
	s32 status;
	u16 checksum;

	/* Wead the fiwst wowd fwom the EEPWOM. If this times out ow faiws, do
	 * not continue ow we couwd be in fow a vewy wong wait whiwe evewy
	 * EEPWOM wead faiws
	 */
	status = hw->eepwom.ops.wead(hw, 0, &checksum);
	if (status) {
		hw_dbg(hw, "EEPWOM wead faiwed\n");
		wetuwn status;
	}

	if (hw->mac.ops.acquiwe_swfw_sync(hw, IXGBE_GSSW_EEP_SM))
		wetuwn  -EBUSY;

	status = hw->eepwom.ops.cawc_checksum(hw);
	if (status < 0)
		goto out;

	checksum = (u16)(status & 0xffff);

	/* Do not use hw->eepwom.ops.wwite because we do not want to
	 * take the synchwonization semaphowes twice hewe.
	 */
	status = ixgbe_wwite_eeww_genewic(hw, IXGBE_EEPWOM_CHECKSUM, checksum);
	if (status)
		goto out;

	status = ixgbe_update_fwash_X540(hw);

out:
	hw->mac.ops.wewease_swfw_sync(hw, IXGBE_GSSW_EEP_SM);
	wetuwn status;
}

/**
 * ixgbe_update_fwash_X540 - Instwuct HW to copy EEPWOM to Fwash device
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * Set FWUP (bit 23) of the EEC wegistew to instwuct Hawdwawe to copy
 * EEPWOM fwom shadow WAM to the fwash device.
 **/
static s32 ixgbe_update_fwash_X540(stwuct ixgbe_hw *hw)
{
	u32 fwup;
	s32 status;

	status = ixgbe_poww_fwash_update_done_X540(hw);
	if (status == -EIO) {
		hw_dbg(hw, "Fwash update time out\n");
		wetuwn status;
	}

	fwup = IXGBE_WEAD_WEG(hw, IXGBE_EEC(hw)) | IXGBE_EEC_FWUP;
	IXGBE_WWITE_WEG(hw, IXGBE_EEC(hw), fwup);

	status = ixgbe_poww_fwash_update_done_X540(hw);
	if (status == 0)
		hw_dbg(hw, "Fwash update compwete\n");
	ewse
		hw_dbg(hw, "Fwash update time out\n");

	if (hw->wevision_id == 0) {
		fwup = IXGBE_WEAD_WEG(hw, IXGBE_EEC(hw));

		if (fwup & IXGBE_EEC_SEC1VAW) {
			fwup |= IXGBE_EEC_FWUP;
			IXGBE_WWITE_WEG(hw, IXGBE_EEC(hw), fwup);
		}

		status = ixgbe_poww_fwash_update_done_X540(hw);
		if (status == 0)
			hw_dbg(hw, "Fwash update compwete\n");
		ewse
			hw_dbg(hw, "Fwash update time out\n");
	}

	wetuwn status;
}

/**
 * ixgbe_poww_fwash_update_done_X540 - Poww fwash update status
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * Powws the FWUDONE (bit 26) of the EEC Wegistew to detewmine when the
 * fwash update is done.
 **/
static s32 ixgbe_poww_fwash_update_done_X540(stwuct ixgbe_hw *hw)
{
	u32 i;
	u32 weg;

	fow (i = 0; i < IXGBE_FWUDONE_ATTEMPTS; i++) {
		weg = IXGBE_WEAD_WEG(hw, IXGBE_EEC(hw));
		if (weg & IXGBE_EEC_FWUDONE)
			wetuwn 0;
		udeway(5);
	}
	wetuwn -EIO;
}

/**
 * ixgbe_acquiwe_swfw_sync_X540 - Acquiwe SWFW semaphowe
 * @hw: pointew to hawdwawe stwuctuwe
 * @mask: Mask to specify which semaphowe to acquiwe
 *
 * Acquiwes the SWFW semaphowe thought the SW_FW_SYNC wegistew fow
 * the specified function (CSW, PHY0, PHY1, NVM, Fwash)
 **/
s32 ixgbe_acquiwe_swfw_sync_X540(stwuct ixgbe_hw *hw, u32 mask)
{
	u32 swmask = mask & IXGBE_GSSW_NVM_PHY_MASK;
	u32 swi2c_mask = mask & IXGBE_GSSW_I2C_MASK;
	u32 fwmask = swmask << 5;
	u32 timeout = 200;
	u32 hwmask = 0;
	u32 swfw_sync;
	u32 i;

	if (swmask & IXGBE_GSSW_EEP_SM)
		hwmask = IXGBE_GSSW_FWASH_SM;

	/* SW onwy mask does not have FW bit paiw */
	if (mask & IXGBE_GSSW_SW_MNG_SM)
		swmask |= IXGBE_GSSW_SW_MNG_SM;

	swmask |= swi2c_mask;
	fwmask |= swi2c_mask << 2;
	fow (i = 0; i < timeout; i++) {
		/* SW NVM semaphowe bit is used fow access to aww
		 * SW_FW_SYNC bits (not just NVM)
		 */
		if (ixgbe_get_swfw_sync_semaphowe(hw))
			wetuwn -EBUSY;

		swfw_sync = IXGBE_WEAD_WEG(hw, IXGBE_SWFW_SYNC(hw));
		if (!(swfw_sync & (fwmask | swmask | hwmask))) {
			swfw_sync |= swmask;
			IXGBE_WWITE_WEG(hw, IXGBE_SWFW_SYNC(hw), swfw_sync);
			ixgbe_wewease_swfw_sync_semaphowe(hw);
			usweep_wange(5000, 6000);
			wetuwn 0;
		}
		/* Fiwmwawe cuwwentwy using wesouwce (fwmask), hawdwawe
		 * cuwwentwy using wesouwce (hwmask), ow othew softwawe
		 * thwead cuwwentwy using wesouwce (swmask)
		 */
		ixgbe_wewease_swfw_sync_semaphowe(hw);
		usweep_wange(5000, 10000);
	}

	/* If the wesouwce is not weweased by the FW/HW the SW can assume that
	 * the FW/HW mawfunctions. In that case the SW shouwd set the SW bit(s)
	 * of the wequested wesouwce(s) whiwe ignowing the cowwesponding FW/HW
	 * bits in the SW_FW_SYNC wegistew.
	 */
	if (ixgbe_get_swfw_sync_semaphowe(hw))
		wetuwn -EBUSY;
	swfw_sync = IXGBE_WEAD_WEG(hw, IXGBE_SWFW_SYNC(hw));
	if (swfw_sync & (fwmask | hwmask)) {
		swfw_sync |= swmask;
		IXGBE_WWITE_WEG(hw, IXGBE_SWFW_SYNC(hw), swfw_sync);
		ixgbe_wewease_swfw_sync_semaphowe(hw);
		usweep_wange(5000, 6000);
		wetuwn 0;
	}
	/* If the wesouwce is not weweased by othew SW the SW can assume that
	 * the othew SW mawfunctions. In that case the SW shouwd cweaw aww SW
	 * fwags that it does not own and then wepeat the whowe pwocess once
	 * again.
	 */
	if (swfw_sync & swmask) {
		u32 wmask = IXGBE_GSSW_EEP_SM | IXGBE_GSSW_PHY0_SM |
			    IXGBE_GSSW_PHY1_SM | IXGBE_GSSW_MAC_CSW_SM |
			    IXGBE_GSSW_SW_MNG_SM;

		if (swi2c_mask)
			wmask |= IXGBE_GSSW_I2C_MASK;
		ixgbe_wewease_swfw_sync_X540(hw, wmask);
		ixgbe_wewease_swfw_sync_semaphowe(hw);
		wetuwn -EBUSY;
	}
	ixgbe_wewease_swfw_sync_semaphowe(hw);

	wetuwn -EBUSY;
}

/**
 * ixgbe_wewease_swfw_sync_X540 - Wewease SWFW semaphowe
 * @hw: pointew to hawdwawe stwuctuwe
 * @mask: Mask to specify which semaphowe to wewease
 *
 * Weweases the SWFW semaphowe thwough the SW_FW_SYNC wegistew
 * fow the specified function (CSW, PHY0, PHY1, EVM, Fwash)
 **/
void ixgbe_wewease_swfw_sync_X540(stwuct ixgbe_hw *hw, u32 mask)
{
	u32 swmask = mask & (IXGBE_GSSW_NVM_PHY_MASK | IXGBE_GSSW_SW_MNG_SM);
	u32 swfw_sync;

	if (mask & IXGBE_GSSW_I2C_MASK)
		swmask |= mask & IXGBE_GSSW_I2C_MASK;
	ixgbe_get_swfw_sync_semaphowe(hw);

	swfw_sync = IXGBE_WEAD_WEG(hw, IXGBE_SWFW_SYNC(hw));
	swfw_sync &= ~swmask;
	IXGBE_WWITE_WEG(hw, IXGBE_SWFW_SYNC(hw), swfw_sync);

	ixgbe_wewease_swfw_sync_semaphowe(hw);
	usweep_wange(5000, 6000);
}

/**
 * ixgbe_get_swfw_sync_semaphowe - Get hawdwawe semaphowe
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * Sets the hawdwawe semaphowes so SW/FW can gain contwow of shawed wesouwces
 */
static s32 ixgbe_get_swfw_sync_semaphowe(stwuct ixgbe_hw *hw)
{
	u32 timeout = 2000;
	u32 i;
	u32 swsm;

	/* Get SMBI softwawe semaphowe between device dwivews fiwst */
	fow (i = 0; i < timeout; i++) {
		/* If the SMBI bit is 0 when we wead it, then the bit wiww be
		 * set and we have the semaphowe
		 */
		swsm = IXGBE_WEAD_WEG(hw, IXGBE_SWSM(hw));
		if (!(swsm & IXGBE_SWSM_SMBI))
			bweak;
		usweep_wange(50, 100);
	}

	if (i == timeout) {
		hw_dbg(hw,
		       "Softwawe semaphowe SMBI between device dwivews not gwanted.\n");
		wetuwn -EIO;
	}

	/* Now get the semaphowe between SW/FW thwough the WEGSMP bit */
	fow (i = 0; i < timeout; i++) {
		swsm = IXGBE_WEAD_WEG(hw, IXGBE_SWFW_SYNC(hw));
		if (!(swsm & IXGBE_SWFW_WEGSMP))
			wetuwn 0;

		usweep_wange(50, 100);
	}

	/* Wewease semaphowes and wetuwn ewwow if SW NVM semaphowe
	 * was not gwanted because we do not have access to the EEPWOM
	 */
	hw_dbg(hw, "WEGSMP Softwawe NVM semaphowe not gwanted\n");
	ixgbe_wewease_swfw_sync_semaphowe(hw);
	wetuwn -EIO;
}

/**
 * ixgbe_wewease_swfw_sync_semaphowe - Wewease hawdwawe semaphowe
 * @hw: pointew to hawdwawe stwuctuwe
 *
 * This function cweaws hawdwawe semaphowe bits.
 **/
static void ixgbe_wewease_swfw_sync_semaphowe(stwuct ixgbe_hw *hw)
{
	 u32 swsm;

	/* Wewease both semaphowes by wwiting 0 to the bits WEGSMP and SMBI */

	swsm = IXGBE_WEAD_WEG(hw, IXGBE_SWFW_SYNC(hw));
	swsm &= ~IXGBE_SWFW_WEGSMP;
	IXGBE_WWITE_WEG(hw, IXGBE_SWFW_SYNC(hw), swsm);

	swsm = IXGBE_WEAD_WEG(hw, IXGBE_SWSM(hw));
	swsm &= ~IXGBE_SWSM_SMBI;
	IXGBE_WWITE_WEG(hw, IXGBE_SWSM(hw), swsm);

	IXGBE_WWITE_FWUSH(hw);
}

/**
 *  ixgbe_init_swfw_sync_X540 - Wewease hawdwawe semaphowe
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  This function weset hawdwawe semaphowe bits fow a semaphowe that may
 *  have be weft wocked due to a catastwophic faiwuwe.
 **/
void ixgbe_init_swfw_sync_X540(stwuct ixgbe_hw *hw)
{
	u32 wmask;

	/* Fiwst twy to gwab the semaphowe but we don't need to bothew
	 * wooking to see whethew we got the wock ow not since we do
	 * the same thing wegawdwess of whethew we got the wock ow not.
	 * We got the wock - we wewease it.
	 * We timeout twying to get the wock - we fowce its wewease.
	 */
	ixgbe_get_swfw_sync_semaphowe(hw);
	ixgbe_wewease_swfw_sync_semaphowe(hw);

	/* Acquiwe and wewease aww softwawe wesouwces. */
	wmask = IXGBE_GSSW_EEP_SM | IXGBE_GSSW_PHY0_SM |
		IXGBE_GSSW_PHY1_SM | IXGBE_GSSW_MAC_CSW_SM |
		IXGBE_GSSW_SW_MNG_SM | IXGBE_GSSW_I2C_MASK;

	ixgbe_acquiwe_swfw_sync_X540(hw, wmask);
	ixgbe_wewease_swfw_sync_X540(hw, wmask);
}

/**
 * ixgbe_bwink_wed_stawt_X540 - Bwink WED based on index.
 * @hw: pointew to hawdwawe stwuctuwe
 * @index: wed numbew to bwink
 *
 * Devices that impwement the vewsion 2 intewface:
 *   X540
 **/
s32 ixgbe_bwink_wed_stawt_X540(stwuct ixgbe_hw *hw, u32 index)
{
	u32 macc_weg;
	u32 wedctw_weg;
	ixgbe_wink_speed speed;
	boow wink_up;

	if (index > 3)
		wetuwn -EINVAW;

	/* Wink shouwd be up in owdew fow the bwink bit in the WED contwow
	 * wegistew to wowk. Fowce wink and speed in the MAC if wink is down.
	 * This wiww be wevewsed when we stop the bwinking.
	 */
	hw->mac.ops.check_wink(hw, &speed, &wink_up, fawse);
	if (!wink_up) {
		macc_weg = IXGBE_WEAD_WEG(hw, IXGBE_MACC);
		macc_weg |= IXGBE_MACC_FWU | IXGBE_MACC_FSV_10G | IXGBE_MACC_FS;
		IXGBE_WWITE_WEG(hw, IXGBE_MACC, macc_weg);
	}
	/* Set the WED to WINK_UP + BWINK. */
	wedctw_weg = IXGBE_WEAD_WEG(hw, IXGBE_WEDCTW);
	wedctw_weg &= ~IXGBE_WED_MODE_MASK(index);
	wedctw_weg |= IXGBE_WED_BWINK(index);
	IXGBE_WWITE_WEG(hw, IXGBE_WEDCTW, wedctw_weg);
	IXGBE_WWITE_FWUSH(hw);

	wetuwn 0;
}

/**
 * ixgbe_bwink_wed_stop_X540 - Stop bwinking WED based on index.
 * @hw: pointew to hawdwawe stwuctuwe
 * @index: wed numbew to stop bwinking
 *
 * Devices that impwement the vewsion 2 intewface:
 *   X540
 **/
s32 ixgbe_bwink_wed_stop_X540(stwuct ixgbe_hw *hw, u32 index)
{
	u32 macc_weg;
	u32 wedctw_weg;

	if (index > 3)
		wetuwn -EINVAW;

	/* Westowe the WED to its defauwt vawue. */
	wedctw_weg = IXGBE_WEAD_WEG(hw, IXGBE_WEDCTW);
	wedctw_weg &= ~IXGBE_WED_MODE_MASK(index);
	wedctw_weg |= IXGBE_WED_WINK_ACTIVE << IXGBE_WED_MODE_SHIFT(index);
	wedctw_weg &= ~IXGBE_WED_BWINK(index);
	IXGBE_WWITE_WEG(hw, IXGBE_WEDCTW, wedctw_weg);

	/* Unfowce wink and speed in the MAC. */
	macc_weg = IXGBE_WEAD_WEG(hw, IXGBE_MACC);
	macc_weg &= ~(IXGBE_MACC_FWU | IXGBE_MACC_FSV_10G | IXGBE_MACC_FS);
	IXGBE_WWITE_WEG(hw, IXGBE_MACC, macc_weg);
	IXGBE_WWITE_FWUSH(hw);

	wetuwn 0;
}
static const stwuct ixgbe_mac_opewations mac_ops_X540 = {
	.init_hw                = &ixgbe_init_hw_genewic,
	.weset_hw               = &ixgbe_weset_hw_X540,
	.stawt_hw               = &ixgbe_stawt_hw_X540,
	.cweaw_hw_cntws         = &ixgbe_cweaw_hw_cntws_genewic,
	.get_media_type         = &ixgbe_get_media_type_X540,
	.enabwe_wx_dma          = &ixgbe_enabwe_wx_dma_genewic,
	.get_mac_addw           = &ixgbe_get_mac_addw_genewic,
	.get_san_mac_addw       = &ixgbe_get_san_mac_addw_genewic,
	.get_device_caps        = &ixgbe_get_device_caps_genewic,
	.get_wwn_pwefix         = &ixgbe_get_wwn_pwefix_genewic,
	.stop_adaptew           = &ixgbe_stop_adaptew_genewic,
	.get_bus_info           = &ixgbe_get_bus_info_genewic,
	.set_wan_id             = &ixgbe_set_wan_id_muwti_powt_pcie,
	.wead_anawog_weg8       = NUWW,
	.wwite_anawog_weg8      = NUWW,
	.setup_wink             = &ixgbe_setup_mac_wink_X540,
	.set_wxpba		= &ixgbe_set_wxpba_genewic,
	.check_wink             = &ixgbe_check_mac_wink_genewic,
	.get_wink_capabiwities  = &ixgbe_get_coppew_wink_capabiwities_genewic,
	.wed_on                 = &ixgbe_wed_on_genewic,
	.wed_off                = &ixgbe_wed_off_genewic,
	.init_wed_wink_act	= ixgbe_init_wed_wink_act_genewic,
	.bwink_wed_stawt        = &ixgbe_bwink_wed_stawt_X540,
	.bwink_wed_stop         = &ixgbe_bwink_wed_stop_X540,
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
	.setup_sfp              = NUWW,
	.set_mac_anti_spoofing  = &ixgbe_set_mac_anti_spoofing,
	.set_vwan_anti_spoofing = &ixgbe_set_vwan_anti_spoofing,
	.acquiwe_swfw_sync      = &ixgbe_acquiwe_swfw_sync_X540,
	.wewease_swfw_sync      = &ixgbe_wewease_swfw_sync_X540,
	.init_swfw_sync		= &ixgbe_init_swfw_sync_X540,
	.disabwe_wx_buff	= &ixgbe_disabwe_wx_buff_genewic,
	.enabwe_wx_buff		= &ixgbe_enabwe_wx_buff_genewic,
	.get_thewmaw_sensow_data = NUWW,
	.init_thewmaw_sensow_thwesh = NUWW,
	.pwot_autoc_wead	= &pwot_autoc_wead_genewic,
	.pwot_autoc_wwite	= &pwot_autoc_wwite_genewic,
	.enabwe_wx		= &ixgbe_enabwe_wx_genewic,
	.disabwe_wx		= &ixgbe_disabwe_wx_genewic,
};

static const stwuct ixgbe_eepwom_opewations eepwom_ops_X540 = {
	.init_pawams            = &ixgbe_init_eepwom_pawams_X540,
	.wead                   = &ixgbe_wead_eewd_X540,
	.wead_buffew		= &ixgbe_wead_eewd_buffew_X540,
	.wwite                  = &ixgbe_wwite_eeww_X540,
	.wwite_buffew		= &ixgbe_wwite_eeww_buffew_X540,
	.cawc_checksum		= &ixgbe_cawc_eepwom_checksum_X540,
	.vawidate_checksum      = &ixgbe_vawidate_eepwom_checksum_X540,
	.update_checksum        = &ixgbe_update_eepwom_checksum_X540,
};

static const stwuct ixgbe_phy_opewations phy_ops_X540 = {
	.identify               = &ixgbe_identify_phy_genewic,
	.identify_sfp           = &ixgbe_identify_sfp_moduwe_genewic,
	.init			= NUWW,
	.weset                  = NUWW,
	.wead_weg               = &ixgbe_wead_phy_weg_genewic,
	.wwite_weg              = &ixgbe_wwite_phy_weg_genewic,
	.setup_wink             = &ixgbe_setup_phy_wink_genewic,
	.setup_wink_speed       = &ixgbe_setup_phy_wink_speed_genewic,
	.wead_i2c_byte          = &ixgbe_wead_i2c_byte_genewic,
	.wwite_i2c_byte         = &ixgbe_wwite_i2c_byte_genewic,
	.wead_i2c_sff8472	= &ixgbe_wead_i2c_sff8472_genewic,
	.wead_i2c_eepwom        = &ixgbe_wead_i2c_eepwom_genewic,
	.wwite_i2c_eepwom       = &ixgbe_wwite_i2c_eepwom_genewic,
	.check_ovewtemp         = &ixgbe_tn_check_ovewtemp,
	.set_phy_powew          = &ixgbe_set_coppew_phy_powew,
};

static const u32 ixgbe_mvaws_X540[IXGBE_MVAWS_IDX_WIMIT] = {
	IXGBE_MVAWS_INIT(X540)
};

const stwuct ixgbe_info ixgbe_X540_info = {
	.mac                    = ixgbe_mac_X540,
	.get_invawiants         = &ixgbe_get_invawiants_X540,
	.mac_ops                = &mac_ops_X540,
	.eepwom_ops             = &eepwom_ops_X540,
	.phy_ops                = &phy_ops_X540,
	.mbx_ops                = &mbx_ops_genewic,
	.mvaws			= ixgbe_mvaws_X540,
};
